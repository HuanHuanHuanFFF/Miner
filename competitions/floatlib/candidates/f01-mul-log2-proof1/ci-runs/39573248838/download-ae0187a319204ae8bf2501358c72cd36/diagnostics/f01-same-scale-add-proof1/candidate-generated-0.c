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
uint64_t lean_uint64_mul(uint64_t, uint64_t);
lean_object* lp_floatlib_FloatLib_Floats_Formats_BinaryInterchange_Model_MulBackend_word___at___00FloatLib_Floats_Formats_BinaryInterchange_Configured_Plan_softwareMul32Certified_spec__1(lean_object*, lean_object*);
uint32_t lean_uint32_of_nat(lean_object*);
uint8_t lean_uint32_dec_le(uint32_t, uint32_t);
lean_object* lean_array_get_size(lean_object*);
uint8_t lean_nat_dec_lt(lean_object*, lean_object*);
uint8_t lean_nat_dec_le(lean_object*, lean_object*);
size_t lean_usize_of_nat(lean_object*);
uint8_t lean_usize_dec_eq(size_t, size_t);
lean_object* lean_array_uget_borrowed(lean_object*, size_t);
lean_object* lp_floatlib_FloatLib_Floats_Formats_BinaryInterchange_Model_AddBackend_word___at___00FloatLib_Floats_Formats_BinaryInterchange_Configured_Plan_softwareAdd32Certified_spec__1(lean_object*, lean_object*);
uint32_t lean_uint32_sub(uint32_t, uint32_t);
size_t lean_usize_add(size_t, size_t);
lean_object* lean_nat_add(lean_object*, lean_object*);
lean_object* lean_nat_mul(lean_object*, lean_object*);
lean_object* lean_array_fget_borrowed(lean_object*, lean_object*);
lean_object* lp_competition_Competition_bmmDecodeC(lean_object*, lean_object*, lean_object*);
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
LEAN_EXPORT uint32_t lp_competition_Submission_RebuiltAdd_round24(uint8_t, uint64_t, uint64_t);
LEAN_EXPORT lean_object* lp_competition_Submission_RebuiltAdd_round24___boxed(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT uint32_t lp_competition_Submission_RebuiltAdd_core(uint32_t, uint32_t);
LEAN_EXPORT lean_object* lp_competition_Submission_RebuiltAdd_core___boxed(lean_object*, lean_object*);
LEAN_EXPORT uint32_t lp_competition_Submission_RebuiltAdd_add(uint32_t, uint32_t);
LEAN_EXPORT lean_object* lp_competition_Submission_RebuiltAdd_add___boxed(lean_object*, lean_object*);
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
LEAN_EXPORT uint32_t lp_competition_Fin_foldl_loop___at___00Submission_bmm_spec__0(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, uint32_t, lean_object*);
LEAN_EXPORT lean_object* lp_competition_Fin_foldl_loop___at___00Submission_bmm_spec__0___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT uint32_t lp_competition_Submission_bmm___lam__0(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_Submission_bmm___lam__0___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
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
LEAN_EXPORT uint32_t lp_competition_Submission_RebuiltAdd_round24(uint8_t v_sign_1976_, uint64_t v_product_1977_, uint64_t v_scale_1978_){
_start:
{
uint32_t v___y_1980_; uint32_t v___y_1981_; uint32_t v___y_1982_; uint32_t v___y_1992_; uint32_t v___y_1993_; uint32_t v___y_1997_; uint64_t v___y_1998_; uint8_t v___y_2005_; uint64_t v___y_2006_; uint64_t v___y_2007_; uint64_t v___x_2016_; uint64_t v___y_2018_; uint64_t v_quotient_2024_; uint64_t v_remainder_2025_; uint8_t v___x_2026_; 
v___x_2016_ = 1ULL;
v_quotient_2024_ = lean_uint64_shift_right(v_product_1977_, v___x_2016_);
v_remainder_2025_ = lean_uint64_land(v_product_1977_, v___x_2016_);
v___x_2026_ = lean_uint64_dec_lt(v_remainder_2025_, v___x_2016_);
if (v___x_2026_ == 0)
{
uint8_t v___x_2027_; 
v___x_2027_ = lean_uint64_dec_lt(v___x_2016_, v_remainder_2025_);
if (v___x_2027_ == 0)
{
uint64_t v___x_2028_; uint64_t v___x_2029_; uint8_t v___x_2030_; 
v___x_2028_ = lean_uint64_land(v_quotient_2024_, v___x_2016_);
v___x_2029_ = 0ULL;
v___x_2030_ = lean_uint64_dec_eq(v___x_2028_, v___x_2029_);
if (v___x_2030_ == 0)
{
uint64_t v___x_2031_; 
v___x_2031_ = lean_uint64_add(v_quotient_2024_, v___x_2016_);
v___y_2018_ = v___x_2031_;
goto v___jp_2017_;
}
else
{
v___y_2018_ = v_quotient_2024_;
goto v___jp_2017_;
}
}
else
{
uint64_t v___x_2032_; 
v___x_2032_ = lean_uint64_add(v_quotient_2024_, v___x_2016_);
v___y_2018_ = v___x_2032_;
goto v___jp_2017_;
}
}
else
{
v___y_2018_ = v_quotient_2024_;
goto v___jp_2017_;
}
v___jp_1979_:
{
uint32_t v___x_1983_; uint32_t v___x_1984_; uint32_t v___x_1985_; uint32_t v___x_1986_; uint32_t v___x_1987_; uint32_t v___x_1988_; uint32_t v___x_1989_; uint32_t v___x_1990_; 
v___x_1983_ = 255;
v___x_1984_ = lean_uint32_land(v___y_1980_, v___x_1983_);
v___x_1985_ = 23;
v___x_1986_ = lean_uint32_shift_left(v___x_1984_, v___x_1985_);
v___x_1987_ = lean_uint32_lor(v___y_1982_, v___x_1986_);
v___x_1988_ = 8388607;
v___x_1989_ = lean_uint32_land(v___y_1981_, v___x_1988_);
v___x_1990_ = lean_uint32_lor(v___x_1987_, v___x_1989_);
return v___x_1990_;
}
v___jp_1991_:
{
if (v_sign_1976_ == 0)
{
uint32_t v___x_1994_; 
v___x_1994_ = 0;
v___y_1980_ = v___y_1992_;
v___y_1981_ = v___y_1993_;
v___y_1982_ = v___x_1994_;
goto v___jp_1979_;
}
else
{
uint32_t v___x_1995_; 
v___x_1995_ = 2147483648;
v___y_1980_ = v___y_1992_;
v___y_1981_ = v___y_1993_;
v___y_1982_ = v___x_1995_;
goto v___jp_1979_;
}
}
v___jp_1996_:
{
uint64_t v___x_1999_; uint8_t v___x_2000_; 
v___x_1999_ = 8388608ULL;
v___x_2000_ = lean_uint64_dec_lt(v___y_1998_, v___x_1999_);
if (v___x_2000_ == 0)
{
uint64_t v___x_2001_; uint32_t v___x_2002_; 
v___x_2001_ = lean_uint64_sub(v___y_1998_, v___x_1999_);
v___x_2002_ = lean_uint64_to_uint32(v___x_2001_);
v___y_1992_ = v___y_1997_;
v___y_1993_ = v___x_2002_;
goto v___jp_1991_;
}
else
{
uint32_t v___x_2003_; 
v___x_2003_ = lean_uint32_once(&lp_competition_Submission_TunedAdd_fracW___closed__0, &lp_competition_Submission_TunedAdd_fracW___closed__0_once, _init_lp_competition_Submission_TunedAdd_fracW___closed__0);
v___y_1992_ = v___y_1997_;
v___y_1993_ = v___x_2003_;
goto v___jp_1991_;
}
}
v___jp_2004_:
{
uint64_t v___x_2008_; uint8_t v___x_2009_; 
v___x_2008_ = 425ULL;
v___x_2009_ = lean_uint64_dec_lt(v___x_2008_, v___y_2007_);
if (v___x_2009_ == 0)
{
uint64_t v___x_2010_; uint64_t v___x_2011_; uint32_t v___x_2012_; 
v___x_2010_ = 171ULL;
v___x_2011_ = lean_uint64_sub(v___y_2007_, v___x_2010_);
v___x_2012_ = lean_uint64_to_uint32(v___x_2011_);
if (v___y_2005_ == 0)
{
v___y_1997_ = v___x_2012_;
v___y_1998_ = v___y_2006_;
goto v___jp_1996_;
}
else
{
uint64_t v___x_2013_; 
v___x_2013_ = 8388608ULL;
v___y_1997_ = v___x_2012_;
v___y_1998_ = v___x_2013_;
goto v___jp_1996_;
}
}
else
{
if (v_sign_1976_ == 0)
{
uint32_t v___x_2014_; 
v___x_2014_ = 2139095040;
return v___x_2014_;
}
else
{
uint32_t v___x_2015_; 
v___x_2015_ = 4286578688;
return v___x_2015_;
}
}
}
v___jp_2017_:
{
uint64_t v___x_2019_; uint8_t v_carry_2020_; uint64_t v___x_2021_; uint64_t v_position_2022_; 
v___x_2019_ = 16777216ULL;
v_carry_2020_ = lean_uint64_dec_eq(v___y_2018_, v___x_2019_);
v___x_2021_ = 24ULL;
v_position_2022_ = lean_uint64_add(v___x_2021_, v_scale_1978_);
if (v_carry_2020_ == 0)
{
v___y_2005_ = v_carry_2020_;
v___y_2006_ = v___y_2018_;
v___y_2007_ = v_position_2022_;
goto v___jp_2004_;
}
else
{
uint64_t v___x_2023_; 
v___x_2023_ = lean_uint64_add(v_position_2022_, v___x_2016_);
v___y_2005_ = v_carry_2020_;
v___y_2006_ = v___y_2018_;
v___y_2007_ = v___x_2023_;
goto v___jp_2004_;
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_RebuiltAdd_round24___boxed(lean_object* v_sign_2033_, lean_object* v_product_2034_, lean_object* v_scale_2035_){
_start:
{
uint8_t v_sign_boxed_2036_; uint64_t v_product_boxed_2037_; uint64_t v_scale_boxed_2038_; uint32_t v_res_2039_; lean_object* v_r_2040_; 
v_sign_boxed_2036_ = lean_unbox(v_sign_2033_);
v_product_boxed_2037_ = lean_unbox_uint64(v_product_2034_);
lean_dec_ref(v_product_2034_);
v_scale_boxed_2038_ = lean_unbox_uint64(v_scale_2035_);
lean_dec_ref(v_scale_2035_);
v_res_2039_ = lp_competition_Submission_RebuiltAdd_round24(v_sign_boxed_2036_, v_product_boxed_2037_, v_scale_boxed_2038_);
v_r_2040_ = lean_box_uint32(v_res_2039_);
return v_r_2040_;
}
}
LEAN_EXPORT uint32_t lp_competition_Submission_RebuiltAdd_core(uint32_t v_a_2041_, uint32_t v_b_2042_){
_start:
{
uint32_t v___y_2044_; uint32_t v___y_2045_; uint32_t v___y_2050_; uint32_t v___y_2051_; uint32_t v___y_2056_; uint32_t v___y_2057_; uint32_t v___y_2062_; uint32_t v___y_2063_; uint32_t v___y_2068_; uint32_t v___y_2069_; uint32_t v___y_2074_; uint32_t v___y_2075_; uint32_t v___y_2080_; uint32_t v___y_2081_; uint32_t v___y_2086_; uint32_t v___y_2087_; uint32_t v___y_2092_; uint64_t v___y_2096_; lean_object* v___y_2097_; uint64_t v___y_2098_; uint32_t v___y_2113_; uint64_t v___y_2117_; lean_object* v___y_2118_; uint64_t v___y_2119_; uint32_t v___y_2134_; lean_object* v___y_2138_; uint64_t v___y_2139_; uint64_t v___y_2140_; uint32_t v___y_2155_; lean_object* v___y_2159_; uint64_t v___y_2160_; uint64_t v___y_2161_; uint32_t v___y_2176_; uint64_t v___y_2180_; lean_object* v___y_2181_; uint64_t v___y_2182_; uint32_t v___y_2197_; lean_object* v___y_2201_; uint64_t v___y_2202_; uint64_t v___y_2203_; uint32_t v___y_2218_; lean_object* v___y_2222_; uint64_t v___y_2223_; uint64_t v___y_2224_; uint32_t v___y_2239_; lean_object* v___y_2243_; uint64_t v___y_2244_; uint64_t v___y_2245_; uint32_t v___x_2259_; uint32_t v___x_2260_; uint32_t v___x_2261_; uint32_t v___y_2263_; uint32_t v___y_2264_; uint32_t v___y_2265_; uint32_t v___y_2273_; lean_object* v___y_2274_; uint32_t v___y_2275_; uint64_t v___y_2280_; lean_object* v___y_2281_; uint64_t v___y_2282_; uint64_t v___y_2283_; uint64_t v___y_2293_; uint8_t v___y_2294_; uint64_t v___y_2295_; lean_object* v___y_2296_; uint64_t v___y_2297_; uint64_t v___y_2305_; uint64_t v___y_2306_; lean_object* v___y_2307_; uint64_t v___y_2308_; lean_object* v___y_2314_; uint64_t v___y_2315_; uint64_t v___y_2316_; uint64_t v___y_2317_; lean_object* v___y_2318_; uint64_t v___y_2319_; lean_object* v___y_2383_; uint64_t v___y_2384_; uint64_t v___y_2385_; uint64_t v___y_2386_; uint64_t v___y_2387_; lean_object* v___y_2388_; uint64_t v___y_2389_; uint64_t v___y_2395_; lean_object* v___y_2396_; uint64_t v___y_2397_; uint64_t v___y_2398_; uint64_t v___y_2399_; uint64_t v___y_2400_; uint64_t v___y_2401_; lean_object* v___y_2402_; uint64_t v___y_2403_; lean_object* v___y_2408_; uint64_t v___y_2409_; uint64_t v___y_2410_; uint64_t v___y_2411_; uint64_t v___y_2412_; lean_object* v___y_2413_; uint64_t v___y_2414_; uint64_t v___y_2419_; uint64_t v___y_2420_; lean_object* v___y_2421_; uint64_t v___y_2422_; uint64_t v___y_2423_; uint64_t v___y_2424_; uint64_t v___y_2425_; lean_object* v___y_2426_; uint64_t v___y_2427_; uint64_t v___y_2432_; lean_object* v___y_2433_; uint64_t v___y_2434_; uint64_t v___y_2435_; uint64_t v___y_2436_; lean_object* v___y_2437_; uint64_t v___y_2438_; lean_object* v___y_2443_; uint64_t v___y_2444_; uint64_t v___y_2445_; uint64_t v___y_2446_; uint64_t v___y_2447_; uint64_t v___y_2448_; lean_object* v___y_2449_; uint64_t v___y_2450_; uint64_t v___y_2451_; lean_object* v___y_2456_; uint64_t v___y_2457_; uint64_t v___y_2458_; uint64_t v___y_2459_; uint64_t v___y_2460_; lean_object* v___y_2461_; uint64_t v___y_2462_; lean_object* v___y_2467_; uint64_t v___y_2468_; uint64_t v___y_2469_; uint64_t v___y_2470_; uint64_t v___y_2471_; uint64_t v___y_2472_; lean_object* v___y_2473_; uint64_t v___y_2474_; uint64_t v___y_2475_; lean_object* v___y_2480_; uint64_t v___y_2481_; uint64_t v___y_2482_; uint64_t v___y_2483_; uint64_t v___y_2484_; lean_object* v___y_2485_; uint64_t v___y_2486_; lean_object* v___y_2491_; uint64_t v___y_2492_; uint64_t v___y_2493_; uint64_t v___y_2494_; uint64_t v___y_2495_; lean_object* v___y_2496_; uint64_t v___y_2497_; uint64_t v___y_2502_; lean_object* v_fst_2503_; lean_object* v_snd_2504_; uint64_t v___y_2519_; uint64_t v___y_2520_; uint8_t v___y_2521_; uint64_t v___y_2522_; uint8_t v___y_2523_; uint8_t v___y_2524_; uint64_t v___y_2536_; uint64_t v___y_2537_; uint64_t v___y_2538_; uint8_t v___y_2539_; uint8_t v___y_2540_; uint8_t v___y_2541_; uint32_t v___y_2546_; uint32_t v___y_2547_; uint32_t v___y_2548_; uint32_t v___y_2556_; lean_object* v___y_2557_; uint32_t v___y_2558_; uint64_t v___y_2563_; uint64_t v___y_2564_; lean_object* v___y_2565_; uint64_t v___y_2566_; uint64_t v___y_2576_; uint64_t v___y_2577_; uint8_t v___y_2578_; lean_object* v___y_2579_; uint64_t v___y_2580_; uint64_t v___y_2588_; uint64_t v___y_2589_; lean_object* v___y_2590_; uint64_t v___y_2591_; uint64_t v___y_2597_; uint64_t v___y_2598_; uint64_t v___y_2599_; lean_object* v___y_2600_; lean_object* v___y_2601_; uint64_t v___y_2602_; uint64_t v___y_2666_; uint64_t v___y_2667_; uint64_t v___y_2668_; uint64_t v___y_2669_; lean_object* v___y_2670_; lean_object* v___y_2671_; uint64_t v___y_2672_; uint64_t v___y_2678_; uint64_t v___y_2679_; uint64_t v___y_2680_; uint64_t v___y_2681_; uint64_t v___y_2682_; uint64_t v___y_2683_; lean_object* v___y_2684_; lean_object* v___y_2685_; uint64_t v___y_2686_; uint64_t v___y_2691_; uint64_t v___y_2692_; uint64_t v___y_2693_; uint64_t v___y_2694_; lean_object* v___y_2695_; lean_object* v___y_2696_; uint64_t v___y_2697_; uint64_t v___y_2702_; uint64_t v___y_2703_; uint64_t v___y_2704_; uint64_t v___y_2705_; uint64_t v___y_2706_; uint64_t v___y_2707_; lean_object* v___y_2708_; lean_object* v___y_2709_; uint64_t v___y_2710_; uint64_t v___y_2715_; uint64_t v___y_2716_; uint64_t v___y_2717_; uint64_t v___y_2718_; lean_object* v___y_2719_; lean_object* v___y_2720_; uint64_t v___y_2721_; uint64_t v___y_2726_; uint64_t v___y_2727_; uint64_t v___y_2728_; uint64_t v___y_2729_; uint64_t v___y_2730_; uint64_t v___y_2731_; lean_object* v___y_2732_; lean_object* v___y_2733_; uint64_t v___y_2734_; uint64_t v___y_2739_; uint64_t v___y_2740_; uint64_t v___y_2741_; uint64_t v___y_2742_; lean_object* v___y_2743_; lean_object* v___y_2744_; uint64_t v___y_2745_; uint64_t v___y_2750_; uint64_t v___y_2751_; uint64_t v___y_2752_; uint64_t v___y_2753_; lean_object* v___y_2754_; lean_object* v___y_2755_; uint64_t v___y_2756_; uint64_t v___y_2757_; uint64_t v___y_2758_; uint64_t v___y_2763_; uint64_t v___y_2764_; uint64_t v___y_2765_; uint64_t v___y_2766_; lean_object* v___y_2767_; lean_object* v___y_2768_; uint64_t v___y_2769_; uint64_t v___y_2774_; uint64_t v___y_2775_; uint64_t v___y_2776_; uint64_t v___y_2777_; lean_object* v___y_2778_; lean_object* v___y_2779_; uint64_t v___y_2780_; uint64_t v___y_2785_; lean_object* v_fst_2786_; lean_object* v_snd_2787_; uint64_t v___y_2802_; uint64_t v___y_2803_; uint8_t v___y_2804_; uint8_t v___y_2805_; uint64_t v___y_2806_; uint8_t v___y_2807_; uint64_t v___y_2819_; uint64_t v___y_2820_; uint8_t v___y_2821_; uint8_t v___y_2822_; uint64_t v___y_2823_; uint8_t v___y_2824_; uint64_t v___y_2829_; uint64_t v___y_2830_; uint8_t v___y_2831_; uint8_t v___y_2832_; uint64_t v___y_2833_; uint64_t v___y_2834_; uint32_t v___y_2845_; uint64_t v___y_2846_; uint8_t v___y_2847_; uint8_t v___y_2848_; uint64_t v___y_2849_; uint64_t v___y_2850_; uint32_t v___y_2857_; uint32_t v___y_2858_; uint32_t v___y_2859_; lean_object* v___y_2867_; uint32_t v___y_2868_; uint32_t v___y_2869_; uint64_t v___y_2874_; lean_object* v___y_2875_; uint64_t v___y_2876_; uint64_t v___y_2877_; uint8_t v___y_2887_; uint64_t v___y_2888_; lean_object* v___y_2889_; uint64_t v___y_2890_; uint64_t v___y_2891_; lean_object* v___y_2899_; uint64_t v___y_2900_; uint64_t v___y_2901_; uint64_t v___y_2902_; lean_object* v___y_2908_; lean_object* v___y_2909_; uint64_t v___y_2910_; uint64_t v___y_2911_; uint64_t v___y_2912_; uint64_t v___y_2913_; lean_object* v___y_2977_; lean_object* v___y_2978_; uint64_t v___y_2979_; uint64_t v___y_2980_; uint64_t v___y_2981_; uint64_t v___y_2982_; uint64_t v___y_2983_; uint64_t v___y_2989_; lean_object* v___y_2990_; lean_object* v___y_2991_; uint64_t v___y_2992_; uint64_t v___y_2993_; uint64_t v___y_2994_; uint64_t v___y_2995_; uint64_t v___y_2996_; uint64_t v___y_2997_; uint64_t v___y_3002_; lean_object* v___y_3003_; lean_object* v___y_3004_; uint64_t v___y_3005_; uint64_t v___y_3006_; uint64_t v___y_3007_; uint64_t v___y_3008_; uint64_t v___y_3013_; lean_object* v___y_3014_; lean_object* v___y_3015_; uint64_t v___y_3016_; uint64_t v___y_3017_; uint64_t v___y_3018_; uint64_t v___y_3019_; uint64_t v___y_3020_; uint64_t v___y_3021_; uint64_t v___y_3026_; lean_object* v___y_3027_; lean_object* v___y_3028_; uint64_t v___y_3029_; uint64_t v___y_3030_; uint64_t v___y_3031_; uint64_t v___y_3032_; uint64_t v___y_3037_; lean_object* v___y_3038_; lean_object* v___y_3039_; uint64_t v___y_3040_; uint64_t v___y_3041_; uint64_t v___y_3042_; uint64_t v___y_3043_; uint64_t v___y_3044_; uint64_t v___y_3045_; lean_object* v___y_3050_; lean_object* v___y_3051_; uint64_t v___y_3052_; uint64_t v___y_3053_; uint64_t v___y_3054_; uint64_t v___y_3055_; uint64_t v___y_3056_; uint64_t v___y_3061_; lean_object* v___y_3062_; lean_object* v___y_3063_; uint64_t v___y_3064_; uint64_t v___y_3065_; uint64_t v___y_3066_; uint64_t v___y_3067_; uint64_t v___y_3068_; uint64_t v___y_3069_; uint64_t v___y_3074_; lean_object* v___y_3075_; lean_object* v___y_3076_; uint64_t v___y_3077_; uint64_t v___y_3078_; uint64_t v___y_3079_; uint64_t v___y_3080_; lean_object* v___y_3085_; lean_object* v___y_3086_; uint64_t v___y_3087_; uint64_t v___y_3088_; uint64_t v___y_3089_; uint64_t v___y_3090_; uint64_t v___y_3091_; uint64_t v___y_3096_; lean_object* v_fst_3097_; lean_object* v_snd_3098_; uint64_t v___y_3113_; uint64_t v___y_3114_; uint8_t v___y_3115_; uint8_t v___y_3116_; uint64_t v___y_3117_; uint8_t v___y_3118_; uint64_t v___y_3130_; uint64_t v___y_3131_; uint8_t v___y_3132_; uint8_t v___y_3133_; uint64_t v___y_3134_; uint8_t v___y_3135_; uint32_t v___y_3140_; uint32_t v___y_3141_; uint32_t v___y_3142_; lean_object* v___y_3150_; uint32_t v___y_3151_; uint32_t v___y_3152_; lean_object* v___y_3157_; uint64_t v___y_3158_; uint64_t v___y_3159_; uint64_t v___y_3160_; uint64_t v___y_3170_; lean_object* v___y_3171_; uint8_t v___y_3172_; uint64_t v___y_3173_; uint64_t v___y_3174_; lean_object* v___y_3182_; uint64_t v___y_3183_; uint64_t v___y_3184_; uint64_t v___y_3185_; uint64_t v___y_3191_; lean_object* v___y_3192_; lean_object* v___y_3193_; uint64_t v___y_3194_; uint64_t v___y_3195_; uint64_t v___y_3196_; uint64_t v___y_3260_; lean_object* v___y_3261_; lean_object* v___y_3262_; uint64_t v___y_3263_; uint64_t v___y_3264_; uint64_t v___y_3265_; uint64_t v___y_3266_; uint64_t v___y_3272_; lean_object* v___y_3273_; uint64_t v___y_3274_; uint64_t v___y_3275_; lean_object* v___y_3276_; uint64_t v___y_3277_; uint64_t v___y_3278_; uint64_t v___y_3279_; uint64_t v___y_3280_; uint64_t v___y_3285_; lean_object* v___y_3286_; uint64_t v___y_3287_; lean_object* v___y_3288_; uint64_t v___y_3289_; uint64_t v___y_3290_; uint64_t v___y_3291_; uint64_t v___y_3296_; uint64_t v___y_3297_; lean_object* v___y_3298_; uint64_t v___y_3299_; lean_object* v___y_3300_; uint64_t v___y_3301_; uint64_t v___y_3302_; uint64_t v___y_3303_; uint64_t v___y_3304_; uint64_t v___y_3309_; lean_object* v___y_3310_; uint64_t v___y_3311_; lean_object* v___y_3312_; uint64_t v___y_3313_; uint64_t v___y_3314_; uint64_t v___y_3315_; uint64_t v___y_3320_; uint64_t v___y_3321_; uint64_t v___y_3322_; lean_object* v___y_3323_; uint64_t v___y_3324_; lean_object* v___y_3325_; uint64_t v___y_3326_; uint64_t v___y_3327_; uint64_t v___y_3328_; uint64_t v___y_3333_; lean_object* v___y_3334_; uint64_t v___y_3335_; lean_object* v___y_3336_; uint64_t v___y_3337_; uint64_t v___y_3338_; uint64_t v___y_3339_; uint64_t v___y_3344_; lean_object* v___y_3345_; uint64_t v___y_3346_; uint64_t v___y_3347_; uint64_t v___y_3348_; lean_object* v___y_3349_; uint64_t v___y_3350_; uint64_t v___y_3351_; uint64_t v___y_3352_; uint64_t v___y_3357_; lean_object* v___y_3358_; uint64_t v___y_3359_; lean_object* v___y_3360_; uint64_t v___y_3361_; uint64_t v___y_3362_; uint64_t v___y_3363_; uint64_t v___y_3368_; uint64_t v___y_3369_; lean_object* v___y_3370_; lean_object* v___y_3371_; uint64_t v___y_3372_; uint64_t v___y_3373_; uint64_t v___y_3374_; uint64_t v___y_3379_; lean_object* v_fst_3380_; lean_object* v_snd_3381_; uint64_t v___y_3396_; uint64_t v___y_3397_; uint8_t v___y_3398_; uint8_t v___y_3399_; uint64_t v___y_3400_; uint8_t v___y_3401_; uint64_t v___y_3413_; uint64_t v___y_3414_; uint8_t v___y_3415_; uint8_t v___y_3416_; uint64_t v___y_3417_; uint8_t v___y_3418_; uint64_t v___y_3423_; uint64_t v___y_3424_; uint64_t v___y_3425_; uint8_t v___y_3426_; uint8_t v___y_3427_; uint64_t v___y_3428_; uint64_t v___y_3439_; uint32_t v___y_3440_; uint64_t v___y_3441_; uint8_t v___y_3442_; uint8_t v___y_3443_; uint64_t v___y_3444_; uint32_t v___y_3451_; uint32_t v___y_3452_; uint32_t v___y_3453_; uint8_t v___y_3461_; uint32_t v___y_3462_; uint32_t v___y_3463_; uint8_t v___y_3467_; uint32_t v___y_3468_; uint64_t v___y_3469_; uint64_t v___y_3476_; uint8_t v___y_3477_; uint8_t v___y_3478_; uint64_t v___y_3479_; uint64_t v___y_3489_; uint64_t v___y_3490_; uint8_t v___y_3491_; uint64_t v___y_3492_; uint32_t v___y_3497_; uint32_t v___y_3498_; uint32_t v___y_3499_; lean_object* v___y_3507_; uint32_t v___y_3508_; uint32_t v___y_3509_; lean_object* v___y_3514_; uint64_t v___y_3515_; uint64_t v___y_3516_; uint64_t v___y_3517_; uint8_t v___y_3527_; lean_object* v___y_3528_; uint64_t v___y_3529_; uint64_t v___y_3530_; uint64_t v___y_3531_; uint64_t v___y_3539_; lean_object* v___y_3540_; uint64_t v___y_3541_; uint64_t v___y_3542_; uint64_t v___y_3543_; uint64_t v___y_3548_; lean_object* v___y_3549_; lean_object* v___y_3550_; uint64_t v___y_3551_; uint64_t v___y_3552_; uint64_t v___y_3553_; uint64_t v___y_3554_; uint64_t v___y_3555_; uint64_t v___y_3614_; uint64_t v___y_3615_; lean_object* v___y_3616_; lean_object* v___y_3617_; uint64_t v___y_3618_; uint64_t v___y_3619_; uint64_t v___y_3620_; uint64_t v___y_3621_; uint64_t v___y_3622_; uint64_t v___y_3627_; uint64_t v___y_3628_; uint64_t v___y_3629_; uint64_t v___y_3630_; lean_object* v___y_3631_; lean_object* v___y_3632_; uint64_t v___y_3633_; uint64_t v___y_3634_; uint64_t v___y_3635_; uint64_t v___y_3636_; uint64_t v___y_3637_; uint64_t v___y_3642_; lean_object* v___y_3643_; lean_object* v___y_3644_; uint64_t v___y_3645_; uint64_t v___y_3646_; uint64_t v___y_3647_; uint64_t v___y_3648_; uint64_t v___y_3649_; uint64_t v___y_3650_; uint64_t v___y_3655_; uint64_t v___y_3656_; uint64_t v___y_3657_; lean_object* v___y_3658_; lean_object* v___y_3659_; uint64_t v___y_3660_; uint64_t v___y_3661_; uint64_t v___y_3662_; uint64_t v___y_3663_; uint64_t v___y_3664_; uint64_t v___y_3665_; uint64_t v___y_3670_; lean_object* v___y_3671_; lean_object* v___y_3672_; uint64_t v___y_3673_; uint64_t v___y_3674_; uint64_t v___y_3675_; uint64_t v___y_3676_; uint64_t v___y_3677_; uint64_t v___y_3678_; uint64_t v___y_3683_; uint64_t v___y_3684_; uint64_t v___y_3685_; lean_object* v___y_3686_; lean_object* v___y_3687_; uint64_t v___y_3688_; uint64_t v___y_3689_; uint64_t v___y_3690_; uint64_t v___y_3691_; uint64_t v___y_3692_; uint64_t v___y_3693_; uint64_t v___y_3698_; lean_object* v___y_3699_; lean_object* v___y_3700_; uint64_t v___y_3701_; uint64_t v___y_3702_; uint64_t v___y_3703_; uint64_t v___y_3704_; uint64_t v___y_3705_; uint64_t v___y_3706_; uint64_t v___y_3711_; uint64_t v___y_3712_; uint64_t v___y_3713_; lean_object* v___y_3714_; lean_object* v___y_3715_; uint64_t v___y_3716_; uint64_t v___y_3717_; uint64_t v___y_3718_; uint64_t v___y_3719_; uint64_t v___y_3720_; uint64_t v___y_3721_; uint64_t v___y_3726_; lean_object* v___y_3727_; lean_object* v___y_3728_; uint64_t v___y_3729_; uint64_t v___y_3730_; uint64_t v___y_3731_; uint64_t v___y_3732_; uint64_t v___y_3733_; uint64_t v___y_3734_; uint64_t v___y_3739_; uint64_t v___y_3740_; lean_object* v___y_3741_; lean_object* v___y_3742_; uint64_t v___y_3743_; uint64_t v___y_3744_; uint64_t v___y_3745_; uint64_t v___y_3746_; uint64_t v___y_3747_; uint64_t v___y_3752_; uint64_t v___y_3753_; uint64_t v___y_3754_; uint64_t v___y_3755_; lean_object* v_fst_3756_; lean_object* v_snd_3757_; uint64_t v___y_3771_; uint64_t v___y_3772_; uint8_t v___y_3773_; uint64_t v___y_3774_; uint64_t v___y_3775_; uint64_t v___y_3776_; uint64_t v___y_3777_; uint8_t v___y_3778_; uint8_t v___y_3779_; uint64_t v___y_3791_; uint64_t v___y_3792_; uint8_t v___y_3793_; uint64_t v___y_3794_; uint64_t v___y_3795_; uint64_t v___y_3796_; uint64_t v___y_3797_; uint8_t v___y_3798_; uint8_t v___y_3799_; uint32_t v___y_3804_; uint32_t v___y_3805_; uint32_t v___y_3806_; uint32_t v___y_3814_; lean_object* v___y_3815_; uint32_t v___y_3816_; uint64_t v___y_3821_; uint64_t v___y_3822_; lean_object* v___y_3823_; uint64_t v___y_3824_; uint64_t v___y_3834_; lean_object* v___y_3835_; uint64_t v___y_3836_; uint8_t v___y_3837_; uint64_t v___y_3838_; uint64_t v___y_3846_; uint64_t v___y_3847_; uint64_t v___y_3848_; lean_object* v___y_3849_; uint64_t v___y_3850_; uint64_t v___y_3855_; uint64_t v___y_3856_; uint64_t v___y_3857_; uint64_t v___y_3858_; lean_object* v___y_3859_; lean_object* v___y_3860_; uint64_t v___y_3861_; uint64_t v___y_3862_; uint64_t v___y_3921_; uint64_t v___y_3922_; uint64_t v___y_3923_; uint64_t v___y_3924_; uint64_t v___y_3925_; lean_object* v___y_3926_; lean_object* v___y_3927_; uint64_t v___y_3928_; uint64_t v___y_3929_; uint64_t v___y_3934_; uint64_t v___y_3935_; uint64_t v___y_3936_; uint64_t v___y_3937_; uint64_t v___y_3938_; uint64_t v___y_3939_; uint64_t v___y_3940_; lean_object* v___y_3941_; lean_object* v___y_3942_; uint64_t v___y_3943_; uint64_t v___y_3944_; uint64_t v___y_3949_; uint64_t v___y_3950_; uint64_t v___y_3951_; uint64_t v___y_3952_; uint64_t v___y_3953_; lean_object* v___y_3954_; lean_object* v___y_3955_; uint64_t v___y_3956_; uint64_t v___y_3957_; uint64_t v___y_3962_; uint64_t v___y_3963_; uint64_t v___y_3964_; uint64_t v___y_3965_; uint64_t v___y_3966_; uint64_t v___y_3967_; lean_object* v___y_3968_; lean_object* v___y_3969_; uint64_t v___y_3970_; uint64_t v___y_3971_; uint64_t v___y_3972_; uint64_t v___y_3977_; uint64_t v___y_3978_; uint64_t v___y_3979_; uint64_t v___y_3980_; uint64_t v___y_3981_; lean_object* v___y_3982_; lean_object* v___y_3983_; uint64_t v___y_3984_; uint64_t v___y_3985_; uint64_t v___y_3990_; uint64_t v___y_3991_; uint64_t v___y_3992_; uint64_t v___y_3993_; uint64_t v___y_3994_; uint64_t v___y_3995_; lean_object* v___y_3996_; lean_object* v___y_3997_; uint64_t v___y_3998_; uint64_t v___y_3999_; uint64_t v___y_4000_; uint64_t v___y_4005_; uint64_t v___y_4006_; uint64_t v___y_4007_; uint64_t v___y_4008_; lean_object* v___y_4009_; lean_object* v___y_4010_; uint64_t v___y_4011_; uint64_t v___y_4012_; uint64_t v___y_4013_; uint64_t v___y_4018_; uint64_t v___y_4019_; uint64_t v___y_4020_; uint64_t v___y_4021_; uint64_t v___y_4022_; lean_object* v___y_4023_; lean_object* v___y_4024_; uint64_t v___y_4025_; uint64_t v___y_4026_; uint64_t v___y_4027_; uint64_t v___y_4028_; uint64_t v___y_4033_; uint64_t v___y_4034_; uint64_t v___y_4035_; uint64_t v___y_4036_; lean_object* v___y_4037_; lean_object* v___y_4038_; uint64_t v___y_4039_; uint64_t v___y_4040_; uint64_t v___y_4041_; uint64_t v___y_4046_; uint64_t v___y_4047_; uint64_t v___y_4048_; uint64_t v___y_4049_; uint64_t v___y_4050_; lean_object* v___y_4051_; lean_object* v___y_4052_; uint64_t v___y_4053_; uint64_t v___y_4054_; uint64_t v___y_4059_; uint64_t v___y_4060_; uint64_t v___y_4061_; uint64_t v___y_4062_; lean_object* v_fst_4063_; lean_object* v_snd_4064_; uint64_t v___y_4078_; uint64_t v___y_4079_; uint64_t v___y_4080_; uint8_t v___y_4081_; uint64_t v___y_4082_; uint64_t v___y_4083_; uint8_t v___y_4084_; uint64_t v___y_4085_; uint8_t v___y_4086_; uint64_t v___y_4098_; uint64_t v___y_4099_; uint64_t v___y_4100_; uint8_t v___y_4101_; uint64_t v___y_4102_; uint64_t v___y_4103_; uint8_t v___y_4104_; uint64_t v___y_4105_; uint8_t v___y_4106_; uint64_t v___y_4111_; uint64_t v___y_4112_; uint64_t v___y_4113_; uint8_t v___y_4114_; uint64_t v___y_4115_; uint64_t v___y_4116_; uint64_t v___y_4117_; uint8_t v___y_4118_; uint64_t v___y_4119_; uint64_t v___y_4130_; uint32_t v___y_4131_; uint64_t v___y_4132_; uint64_t v___y_4133_; uint8_t v___y_4134_; uint64_t v___y_4135_; uint64_t v___y_4136_; uint8_t v___y_4137_; uint64_t v___y_4138_; uint32_t v___y_4144_; uint32_t v___y_4145_; uint32_t v___y_4146_; uint32_t v___y_4154_; lean_object* v___y_4155_; uint32_t v___y_4156_; lean_object* v___y_4161_; uint64_t v___y_4162_; uint64_t v___y_4163_; uint64_t v___y_4164_; lean_object* v___y_4174_; uint64_t v___y_4175_; uint8_t v___y_4176_; uint64_t v___y_4177_; uint64_t v___y_4178_; lean_object* v___y_4186_; uint64_t v___y_4187_; uint64_t v___y_4188_; uint64_t v___y_4189_; uint64_t v___y_4190_; lean_object* v___y_4195_; uint64_t v___y_4196_; lean_object* v___y_4197_; uint64_t v___y_4198_; uint64_t v___y_4199_; uint64_t v___y_4200_; uint64_t v___y_4201_; lean_object* v___y_4261_; uint64_t v___y_4262_; uint64_t v___y_4263_; lean_object* v___y_4264_; uint64_t v___y_4265_; uint64_t v___y_4266_; uint64_t v___y_4267_; uint64_t v___y_4268_; uint64_t v___y_4273_; lean_object* v___y_4274_; uint64_t v___y_4275_; lean_object* v___y_4276_; uint64_t v___y_4277_; uint64_t v___y_4278_; uint64_t v___y_4279_; uint64_t v___y_4280_; uint64_t v___y_4281_; uint64_t v___y_4282_; uint64_t v___y_4287_; lean_object* v___y_4288_; uint64_t v___y_4289_; lean_object* v___y_4290_; uint64_t v___y_4291_; uint64_t v___y_4292_; uint64_t v___y_4293_; uint64_t v___y_4294_; lean_object* v___y_4299_; uint64_t v___y_4300_; uint64_t v___y_4301_; lean_object* v___y_4302_; uint64_t v___y_4303_; uint64_t v___y_4304_; uint64_t v___y_4305_; uint64_t v___y_4306_; uint64_t v___y_4307_; uint64_t v___y_4308_; lean_object* v___y_4313_; uint64_t v___y_4314_; lean_object* v___y_4315_; uint64_t v___y_4316_; uint64_t v___y_4317_; uint64_t v___y_4318_; uint64_t v___y_4319_; uint64_t v___y_4320_; lean_object* v___y_4325_; uint64_t v___y_4326_; uint64_t v___y_4327_; uint64_t v___y_4328_; lean_object* v___y_4329_; uint64_t v___y_4330_; uint64_t v___y_4331_; uint64_t v___y_4332_; uint64_t v___y_4333_; uint64_t v___y_4334_; lean_object* v___y_4339_; uint64_t v___y_4340_; lean_object* v___y_4341_; uint64_t v___y_4342_; uint64_t v___y_4343_; uint64_t v___y_4344_; uint64_t v___y_4345_; uint64_t v___y_4346_; uint64_t v___y_4351_; uint64_t v___y_4352_; lean_object* v___y_4353_; uint64_t v___y_4354_; uint64_t v___y_4355_; lean_object* v___y_4356_; uint64_t v___y_4357_; uint64_t v___y_4358_; uint64_t v___y_4359_; uint64_t v___y_4360_; uint64_t v___y_4365_; lean_object* v___y_4366_; uint64_t v___y_4367_; lean_object* v___y_4368_; uint64_t v___y_4369_; uint64_t v___y_4370_; uint64_t v___y_4371_; uint64_t v___y_4372_; lean_object* v___y_4377_; uint64_t v___y_4378_; lean_object* v___y_4379_; uint64_t v___y_4380_; uint64_t v___y_4381_; uint64_t v___y_4382_; uint64_t v___y_4383_; uint64_t v___y_4384_; uint64_t v___y_4389_; uint64_t v___y_4390_; lean_object* v_fst_4391_; lean_object* v_snd_4392_; uint64_t v___y_4407_; uint8_t v___y_4408_; uint64_t v___y_4409_; uint64_t v___y_4410_; uint8_t v___y_4411_; uint64_t v___y_4412_; uint8_t v___y_4413_; uint64_t v___y_4425_; uint64_t v___y_4426_; uint8_t v___y_4427_; uint64_t v___y_4428_; uint8_t v___y_4429_; uint64_t v___y_4430_; uint8_t v___y_4431_; uint32_t v___y_4436_; uint32_t v___y_4437_; uint32_t v___y_4438_; uint32_t v___y_4446_; lean_object* v___y_4447_; uint32_t v___y_4448_; uint64_t v___y_4453_; uint64_t v___y_4454_; lean_object* v___y_4455_; uint64_t v___y_4456_; lean_object* v___y_4466_; uint64_t v___y_4467_; uint64_t v___y_4468_; uint8_t v___y_4469_; uint64_t v___y_4470_; uint64_t v___y_4478_; uint64_t v___y_4479_; uint64_t v___y_4480_; lean_object* v___y_4481_; uint64_t v___y_4482_; uint64_t v___y_4487_; lean_object* v___y_4488_; uint64_t v___y_4489_; lean_object* v___y_4490_; uint64_t v___y_4491_; uint64_t v___y_4492_; uint64_t v___y_4493_; uint64_t v___y_4553_; uint64_t v___y_4554_; lean_object* v___y_4555_; uint64_t v___y_4556_; uint64_t v___y_4557_; lean_object* v___y_4558_; uint64_t v___y_4559_; uint64_t v___y_4560_; uint64_t v___y_4565_; uint64_t v___y_4566_; lean_object* v___y_4567_; uint64_t v___y_4568_; uint64_t v___y_4569_; lean_object* v___y_4570_; uint64_t v___y_4571_; uint64_t v___y_4572_; uint64_t v___y_4573_; uint64_t v___y_4574_; uint64_t v___y_4579_; lean_object* v___y_4580_; uint64_t v___y_4581_; uint64_t v___y_4582_; uint64_t v___y_4583_; lean_object* v___y_4584_; uint64_t v___y_4585_; uint64_t v___y_4586_; uint64_t v___y_4591_; uint64_t v___y_4592_; uint64_t v___y_4593_; uint64_t v___y_4594_; lean_object* v___y_4595_; lean_object* v___y_4596_; uint64_t v___y_4597_; uint64_t v___y_4598_; uint64_t v___y_4599_; uint64_t v___y_4600_; uint64_t v___y_4605_; uint64_t v___y_4606_; lean_object* v___y_4607_; uint64_t v___y_4608_; uint64_t v___y_4609_; lean_object* v___y_4610_; uint64_t v___y_4611_; uint64_t v___y_4612_; uint64_t v___y_4617_; uint64_t v___y_4618_; uint64_t v___y_4619_; uint64_t v___y_4620_; lean_object* v___y_4621_; uint64_t v___y_4622_; lean_object* v___y_4623_; uint64_t v___y_4624_; uint64_t v___y_4625_; uint64_t v___y_4626_; uint64_t v___y_4631_; uint64_t v___y_4632_; lean_object* v___y_4633_; uint64_t v___y_4634_; uint64_t v___y_4635_; lean_object* v___y_4636_; uint64_t v___y_4637_; uint64_t v___y_4638_; uint64_t v___y_4643_; uint64_t v___y_4644_; uint64_t v___y_4645_; lean_object* v___y_4646_; uint64_t v___y_4647_; lean_object* v___y_4648_; uint64_t v___y_4649_; uint64_t v___y_4650_; uint64_t v___y_4651_; uint64_t v___y_4652_; uint64_t v___y_4657_; uint64_t v___y_4658_; lean_object* v___y_4659_; uint64_t v___y_4660_; uint64_t v___y_4661_; lean_object* v___y_4662_; uint64_t v___y_4663_; uint64_t v___y_4664_; uint64_t v___y_4669_; uint64_t v___y_4670_; uint64_t v___y_4671_; lean_object* v___y_4672_; lean_object* v___y_4673_; uint64_t v___y_4674_; uint64_t v___y_4675_; uint64_t v___y_4676_; uint64_t v___y_4681_; uint64_t v___y_4682_; lean_object* v_fst_4683_; lean_object* v_snd_4684_; uint64_t v___y_4699_; uint8_t v___y_4700_; uint64_t v___y_4701_; uint8_t v___y_4702_; uint64_t v___y_4703_; uint64_t v___y_4704_; uint8_t v___y_4705_; uint64_t v___y_4717_; uint8_t v___y_4718_; uint64_t v___y_4719_; uint64_t v___y_4720_; uint8_t v___y_4721_; uint64_t v___y_4722_; uint8_t v___y_4723_; uint64_t v___y_4728_; uint64_t v___y_4729_; uint8_t v___y_4730_; uint64_t v___y_4731_; uint8_t v___y_4732_; uint64_t v___y_4733_; uint64_t v___y_4734_; uint64_t v___y_4745_; uint32_t v___y_4746_; uint8_t v___y_4747_; uint64_t v___y_4748_; uint8_t v___y_4749_; uint64_t v___y_4750_; uint64_t v___y_4751_; uint32_t v___x_4756_; uint8_t v___y_4758_; uint32_t v___y_4759_; uint64_t v___y_4760_; uint8_t v___y_4761_; uint64_t v___y_4762_; uint64_t v___y_4763_; uint32_t v___y_4769_; uint8_t v___y_4770_; uint64_t v___y_4771_; uint8_t v___y_4772_; uint64_t v___y_4773_; uint32_t v___y_4783_; uint64_t v___y_4784_; uint8_t v___y_4785_; uint8_t v___y_4786_; uint32_t v___y_4796_; uint64_t v___y_4797_; uint8_t v___y_4798_; uint8_t v___y_4799_; uint8_t v___y_4800_; uint64_t v___y_4806_; uint32_t v___y_4807_; uint64_t v___y_4808_; uint64_t v___y_4809_; uint8_t v___y_4810_; uint64_t v___y_4811_; uint8_t v___y_4812_; uint64_t v___y_4813_; uint64_t v___y_4819_; uint32_t v___y_4820_; uint64_t v___y_4821_; uint8_t v___y_4822_; uint64_t v___y_4823_; uint8_t v___y_4824_; uint64_t v___y_4825_; uint64_t v___y_4835_; uint32_t v___y_4836_; uint64_t v___y_4837_; uint64_t v___y_4838_; uint8_t v___y_4839_; uint8_t v___y_4840_; uint64_t v___y_4850_; uint32_t v___y_4851_; uint64_t v___y_4852_; uint8_t v___y_4853_; uint8_t v___y_4854_; uint64_t v___y_4855_; uint8_t v___y_4856_; uint32_t v___y_4862_; uint8_t v___y_4863_; uint64_t v___y_4864_; uint64_t v___y_4865_; uint8_t v___y_4866_; uint64_t v___y_4867_; uint32_t v___y_4896_; uint8_t v___y_4897_; uint64_t v___y_4898_; uint8_t v___y_4899_; uint64_t v___y_4900_; uint32_t v___y_4910_; uint8_t v___y_4911_; uint64_t v___y_4912_; uint8_t v___y_4913_; uint32_t v___y_4923_; uint64_t v___y_4924_; uint8_t v___y_4925_; uint8_t v___y_4926_; uint64_t v___y_4927_; uint32_t v___y_4934_; uint8_t v___y_4935_; uint8_t v___y_4936_; uint64_t v___y_4937_; uint32_t v___y_4947_; uint8_t v___y_4948_; uint8_t v___y_4949_; uint32_t v___y_4959_; uint8_t v___y_4960_; uint8_t v___y_4961_; uint8_t v___y_4962_; uint32_t v___y_4968_; uint8_t v___y_4969_; uint8_t v___y_4970_; uint32_t v___y_4976_; uint8_t v___y_4977_; uint8_t v___y_4978_; uint64_t v___y_4979_; uint8_t v___y_4980_; uint32_t v___y_4983_; uint8_t v___y_4984_; uint64_t v___y_4985_; uint8_t v___y_4986_; uint32_t v___y_4993_; uint8_t v___y_4994_; uint8_t v___y_4995_; uint64_t v___y_4996_; uint64_t v___y_4997_; uint32_t v___y_5004_; uint8_t v___y_5005_; uint8_t v___y_5006_; uint64_t v___y_5007_; uint32_t v___y_5017_; uint8_t v___y_5018_; uint8_t v___y_5019_; uint32_t v___y_5029_; uint8_t v___y_5030_; uint8_t v___y_5031_; uint32_t v___y_5038_; uint64_t v___y_5039_; uint64_t v___y_5040_; uint64_t v___y_5053_; uint64_t v___x_5061_; uint64_t v___x_5062_; uint8_t v___x_5063_; 
v___x_2259_ = 23;
v___x_2260_ = lean_uint32_shift_right(v_a_2041_, v___x_2259_);
v___x_2261_ = 255;
v___x_4756_ = lean_uint32_land(v___x_2260_, v___x_2261_);
v___x_5061_ = lean_uint32_to_uint64(v___x_4756_);
v___x_5062_ = 0ULL;
v___x_5063_ = lean_uint64_dec_eq(v___x_5061_, v___x_5062_);
if (v___x_5063_ == 0)
{
uint64_t v___x_5064_; uint64_t v___x_5065_; 
v___x_5064_ = 1ULL;
v___x_5065_ = lean_uint64_sub(v___x_5061_, v___x_5064_);
v___y_5053_ = v___x_5065_;
goto v___jp_5052_;
}
else
{
v___y_5053_ = v___x_5062_;
goto v___jp_5052_;
}
v___jp_2043_:
{
uint32_t v___x_2046_; uint32_t v___x_2047_; uint32_t v___x_2048_; 
v___x_2046_ = 8388607;
v___x_2047_ = lean_uint32_land(v___y_2044_, v___x_2046_);
v___x_2048_ = lean_uint32_lor(v___y_2045_, v___x_2047_);
return v___x_2048_;
}
v___jp_2049_:
{
uint32_t v___x_2052_; uint32_t v___x_2053_; uint32_t v___x_2054_; 
v___x_2052_ = 8388607;
v___x_2053_ = lean_uint32_land(v___y_2050_, v___x_2052_);
v___x_2054_ = lean_uint32_lor(v___y_2051_, v___x_2053_);
return v___x_2054_;
}
v___jp_2055_:
{
uint32_t v___x_2058_; uint32_t v___x_2059_; uint32_t v___x_2060_; 
v___x_2058_ = 8388607;
v___x_2059_ = lean_uint32_land(v___y_2056_, v___x_2058_);
v___x_2060_ = lean_uint32_lor(v___y_2057_, v___x_2059_);
return v___x_2060_;
}
v___jp_2061_:
{
uint32_t v___x_2064_; uint32_t v___x_2065_; uint32_t v___x_2066_; 
v___x_2064_ = 8388607;
v___x_2065_ = lean_uint32_land(v___y_2062_, v___x_2064_);
v___x_2066_ = lean_uint32_lor(v___y_2063_, v___x_2065_);
return v___x_2066_;
}
v___jp_2067_:
{
uint32_t v___x_2070_; uint32_t v___x_2071_; uint32_t v___x_2072_; 
v___x_2070_ = 8388607;
v___x_2071_ = lean_uint32_land(v___y_2068_, v___x_2070_);
v___x_2072_ = lean_uint32_lor(v___y_2069_, v___x_2071_);
return v___x_2072_;
}
v___jp_2073_:
{
uint32_t v___x_2076_; uint32_t v___x_2077_; uint32_t v___x_2078_; 
v___x_2076_ = 8388607;
v___x_2077_ = lean_uint32_land(v___y_2074_, v___x_2076_);
v___x_2078_ = lean_uint32_lor(v___y_2075_, v___x_2077_);
return v___x_2078_;
}
v___jp_2079_:
{
uint32_t v___x_2082_; uint32_t v___x_2083_; uint32_t v___x_2084_; 
v___x_2082_ = 8388607;
v___x_2083_ = lean_uint32_land(v___y_2080_, v___x_2082_);
v___x_2084_ = lean_uint32_lor(v___y_2081_, v___x_2083_);
return v___x_2084_;
}
v___jp_2085_:
{
uint32_t v___x_2088_; uint32_t v___x_2089_; uint32_t v___x_2090_; 
v___x_2088_ = 8388607;
v___x_2089_ = lean_uint32_land(v___y_2086_, v___x_2088_);
v___x_2090_ = lean_uint32_lor(v___y_2087_, v___x_2089_);
return v___x_2090_;
}
v___jp_2091_:
{
uint32_t v___x_2093_; uint32_t v___x_2094_; 
v___x_2093_ = 8388608;
v___x_2094_ = lean_uint32_lor(v___y_2092_, v___x_2093_);
return v___x_2094_;
}
v___jp_2095_:
{
uint8_t v___x_2099_; 
v___x_2099_ = lean_uint64_dec_eq(v___y_2098_, v___y_2096_);
if (v___x_2099_ == 0)
{
uint64_t v___x_2100_; uint8_t v___x_2101_; 
v___x_2100_ = 8388608ULL;
v___x_2101_ = lean_uint64_dec_eq(v___y_2098_, v___x_2100_);
if (v___x_2101_ == 0)
{
uint32_t v___x_2102_; uint8_t v___x_2103_; 
v___x_2102_ = lean_uint64_to_uint32(v___y_2098_);
v___x_2103_ = lean_unbox(v___y_2097_);
lean_dec(v___y_2097_);
if (v___x_2103_ == 0)
{
uint32_t v___x_2104_; 
v___x_2104_ = 0;
v___y_2050_ = v___x_2102_;
v___y_2051_ = v___x_2104_;
goto v___jp_2049_;
}
else
{
uint32_t v___x_2105_; 
v___x_2105_ = 2147483648;
v___y_2050_ = v___x_2102_;
v___y_2051_ = v___x_2105_;
goto v___jp_2049_;
}
}
else
{
uint8_t v___x_2106_; 
v___x_2106_ = lean_unbox(v___y_2097_);
lean_dec(v___y_2097_);
if (v___x_2106_ == 0)
{
uint32_t v___x_2107_; 
v___x_2107_ = 0;
v___y_2092_ = v___x_2107_;
goto v___jp_2091_;
}
else
{
uint32_t v___x_2108_; 
v___x_2108_ = 2147483648;
v___y_2092_ = v___x_2108_;
goto v___jp_2091_;
}
}
}
else
{
uint8_t v___x_2109_; 
v___x_2109_ = lean_unbox(v___y_2097_);
lean_dec(v___y_2097_);
if (v___x_2109_ == 0)
{
uint32_t v___x_2110_; 
v___x_2110_ = 0;
return v___x_2110_;
}
else
{
uint32_t v___x_2111_; 
v___x_2111_ = 2147483648;
return v___x_2111_;
}
}
}
v___jp_2112_:
{
uint32_t v___x_2114_; uint32_t v___x_2115_; 
v___x_2114_ = 8388608;
v___x_2115_ = lean_uint32_lor(v___y_2113_, v___x_2114_);
return v___x_2115_;
}
v___jp_2116_:
{
uint8_t v___x_2120_; 
v___x_2120_ = lean_uint64_dec_eq(v___y_2119_, v___y_2117_);
if (v___x_2120_ == 0)
{
uint64_t v___x_2121_; uint8_t v___x_2122_; 
v___x_2121_ = 8388608ULL;
v___x_2122_ = lean_uint64_dec_eq(v___y_2119_, v___x_2121_);
if (v___x_2122_ == 0)
{
uint32_t v___x_2123_; uint8_t v___x_2124_; 
v___x_2123_ = lean_uint64_to_uint32(v___y_2119_);
v___x_2124_ = lean_unbox(v___y_2118_);
lean_dec(v___y_2118_);
if (v___x_2124_ == 0)
{
uint32_t v___x_2125_; 
v___x_2125_ = 0;
v___y_2044_ = v___x_2123_;
v___y_2045_ = v___x_2125_;
goto v___jp_2043_;
}
else
{
uint32_t v___x_2126_; 
v___x_2126_ = 2147483648;
v___y_2044_ = v___x_2123_;
v___y_2045_ = v___x_2126_;
goto v___jp_2043_;
}
}
else
{
uint8_t v___x_2127_; 
v___x_2127_ = lean_unbox(v___y_2118_);
lean_dec(v___y_2118_);
if (v___x_2127_ == 0)
{
uint32_t v___x_2128_; 
v___x_2128_ = 0;
v___y_2113_ = v___x_2128_;
goto v___jp_2112_;
}
else
{
uint32_t v___x_2129_; 
v___x_2129_ = 2147483648;
v___y_2113_ = v___x_2129_;
goto v___jp_2112_;
}
}
}
else
{
uint8_t v___x_2130_; 
v___x_2130_ = lean_unbox(v___y_2118_);
lean_dec(v___y_2118_);
if (v___x_2130_ == 0)
{
uint32_t v___x_2131_; 
v___x_2131_ = 0;
return v___x_2131_;
}
else
{
uint32_t v___x_2132_; 
v___x_2132_ = 2147483648;
return v___x_2132_;
}
}
}
v___jp_2133_:
{
uint32_t v___x_2135_; uint32_t v___x_2136_; 
v___x_2135_ = 8388608;
v___x_2136_ = lean_uint32_lor(v___y_2134_, v___x_2135_);
return v___x_2136_;
}
v___jp_2137_:
{
uint8_t v___x_2141_; 
v___x_2141_ = lean_uint64_dec_eq(v___y_2140_, v___y_2139_);
if (v___x_2141_ == 0)
{
uint64_t v___x_2142_; uint8_t v___x_2143_; 
v___x_2142_ = 8388608ULL;
v___x_2143_ = lean_uint64_dec_eq(v___y_2140_, v___x_2142_);
if (v___x_2143_ == 0)
{
uint32_t v___x_2144_; uint8_t v___x_2145_; 
v___x_2144_ = lean_uint64_to_uint32(v___y_2140_);
v___x_2145_ = lean_unbox(v___y_2138_);
lean_dec(v___y_2138_);
if (v___x_2145_ == 0)
{
uint32_t v___x_2146_; 
v___x_2146_ = 0;
v___y_2062_ = v___x_2144_;
v___y_2063_ = v___x_2146_;
goto v___jp_2061_;
}
else
{
uint32_t v___x_2147_; 
v___x_2147_ = 2147483648;
v___y_2062_ = v___x_2144_;
v___y_2063_ = v___x_2147_;
goto v___jp_2061_;
}
}
else
{
uint8_t v___x_2148_; 
v___x_2148_ = lean_unbox(v___y_2138_);
lean_dec(v___y_2138_);
if (v___x_2148_ == 0)
{
uint32_t v___x_2149_; 
v___x_2149_ = 0;
v___y_2134_ = v___x_2149_;
goto v___jp_2133_;
}
else
{
uint32_t v___x_2150_; 
v___x_2150_ = 2147483648;
v___y_2134_ = v___x_2150_;
goto v___jp_2133_;
}
}
}
else
{
uint8_t v___x_2151_; 
v___x_2151_ = lean_unbox(v___y_2138_);
lean_dec(v___y_2138_);
if (v___x_2151_ == 0)
{
uint32_t v___x_2152_; 
v___x_2152_ = 0;
return v___x_2152_;
}
else
{
uint32_t v___x_2153_; 
v___x_2153_ = 2147483648;
return v___x_2153_;
}
}
}
v___jp_2154_:
{
uint32_t v___x_2156_; uint32_t v___x_2157_; 
v___x_2156_ = 8388608;
v___x_2157_ = lean_uint32_lor(v___y_2155_, v___x_2156_);
return v___x_2157_;
}
v___jp_2158_:
{
uint8_t v___x_2162_; 
v___x_2162_ = lean_uint64_dec_eq(v___y_2161_, v___y_2160_);
if (v___x_2162_ == 0)
{
uint64_t v___x_2163_; uint8_t v___x_2164_; 
v___x_2163_ = 8388608ULL;
v___x_2164_ = lean_uint64_dec_eq(v___y_2161_, v___x_2163_);
if (v___x_2164_ == 0)
{
uint32_t v___x_2165_; uint8_t v___x_2166_; 
v___x_2165_ = lean_uint64_to_uint32(v___y_2161_);
v___x_2166_ = lean_unbox(v___y_2159_);
lean_dec(v___y_2159_);
if (v___x_2166_ == 0)
{
uint32_t v___x_2167_; 
v___x_2167_ = 0;
v___y_2056_ = v___x_2165_;
v___y_2057_ = v___x_2167_;
goto v___jp_2055_;
}
else
{
uint32_t v___x_2168_; 
v___x_2168_ = 2147483648;
v___y_2056_ = v___x_2165_;
v___y_2057_ = v___x_2168_;
goto v___jp_2055_;
}
}
else
{
uint8_t v___x_2169_; 
v___x_2169_ = lean_unbox(v___y_2159_);
lean_dec(v___y_2159_);
if (v___x_2169_ == 0)
{
uint32_t v___x_2170_; 
v___x_2170_ = 0;
v___y_2155_ = v___x_2170_;
goto v___jp_2154_;
}
else
{
uint32_t v___x_2171_; 
v___x_2171_ = 2147483648;
v___y_2155_ = v___x_2171_;
goto v___jp_2154_;
}
}
}
else
{
uint8_t v___x_2172_; 
v___x_2172_ = lean_unbox(v___y_2159_);
lean_dec(v___y_2159_);
if (v___x_2172_ == 0)
{
uint32_t v___x_2173_; 
v___x_2173_ = 0;
return v___x_2173_;
}
else
{
uint32_t v___x_2174_; 
v___x_2174_ = 2147483648;
return v___x_2174_;
}
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
uint8_t v___x_2183_; 
v___x_2183_ = lean_uint64_dec_eq(v___y_2182_, v___y_2180_);
if (v___x_2183_ == 0)
{
uint64_t v___x_2184_; uint8_t v___x_2185_; 
v___x_2184_ = 8388608ULL;
v___x_2185_ = lean_uint64_dec_eq(v___y_2182_, v___x_2184_);
if (v___x_2185_ == 0)
{
uint32_t v___x_2186_; uint8_t v___x_2187_; 
v___x_2186_ = lean_uint64_to_uint32(v___y_2182_);
v___x_2187_ = lean_unbox(v___y_2181_);
lean_dec(v___y_2181_);
if (v___x_2187_ == 0)
{
uint32_t v___x_2188_; 
v___x_2188_ = 0;
v___y_2074_ = v___x_2186_;
v___y_2075_ = v___x_2188_;
goto v___jp_2073_;
}
else
{
uint32_t v___x_2189_; 
v___x_2189_ = 2147483648;
v___y_2074_ = v___x_2186_;
v___y_2075_ = v___x_2189_;
goto v___jp_2073_;
}
}
else
{
uint8_t v___x_2190_; 
v___x_2190_ = lean_unbox(v___y_2181_);
lean_dec(v___y_2181_);
if (v___x_2190_ == 0)
{
uint32_t v___x_2191_; 
v___x_2191_ = 0;
v___y_2176_ = v___x_2191_;
goto v___jp_2175_;
}
else
{
uint32_t v___x_2192_; 
v___x_2192_ = 2147483648;
v___y_2176_ = v___x_2192_;
goto v___jp_2175_;
}
}
}
else
{
uint8_t v___x_2193_; 
v___x_2193_ = lean_unbox(v___y_2181_);
lean_dec(v___y_2181_);
if (v___x_2193_ == 0)
{
uint32_t v___x_2194_; 
v___x_2194_ = 0;
return v___x_2194_;
}
else
{
uint32_t v___x_2195_; 
v___x_2195_ = 2147483648;
return v___x_2195_;
}
}
}
v___jp_2196_:
{
uint32_t v___x_2198_; uint32_t v___x_2199_; 
v___x_2198_ = 8388608;
v___x_2199_ = lean_uint32_lor(v___y_2197_, v___x_2198_);
return v___x_2199_;
}
v___jp_2200_:
{
uint8_t v___x_2204_; 
v___x_2204_ = lean_uint64_dec_eq(v___y_2203_, v___y_2202_);
if (v___x_2204_ == 0)
{
uint64_t v___x_2205_; uint8_t v___x_2206_; 
v___x_2205_ = 8388608ULL;
v___x_2206_ = lean_uint64_dec_eq(v___y_2203_, v___x_2205_);
if (v___x_2206_ == 0)
{
uint32_t v___x_2207_; uint8_t v___x_2208_; 
v___x_2207_ = lean_uint64_to_uint32(v___y_2203_);
v___x_2208_ = lean_unbox(v___y_2201_);
lean_dec(v___y_2201_);
if (v___x_2208_ == 0)
{
uint32_t v___x_2209_; 
v___x_2209_ = 0;
v___y_2068_ = v___x_2207_;
v___y_2069_ = v___x_2209_;
goto v___jp_2067_;
}
else
{
uint32_t v___x_2210_; 
v___x_2210_ = 2147483648;
v___y_2068_ = v___x_2207_;
v___y_2069_ = v___x_2210_;
goto v___jp_2067_;
}
}
else
{
uint8_t v___x_2211_; 
v___x_2211_ = lean_unbox(v___y_2201_);
lean_dec(v___y_2201_);
if (v___x_2211_ == 0)
{
uint32_t v___x_2212_; 
v___x_2212_ = 0;
v___y_2197_ = v___x_2212_;
goto v___jp_2196_;
}
else
{
uint32_t v___x_2213_; 
v___x_2213_ = 2147483648;
v___y_2197_ = v___x_2213_;
goto v___jp_2196_;
}
}
}
else
{
uint8_t v___x_2214_; 
v___x_2214_ = lean_unbox(v___y_2201_);
lean_dec(v___y_2201_);
if (v___x_2214_ == 0)
{
uint32_t v___x_2215_; 
v___x_2215_ = 0;
return v___x_2215_;
}
else
{
uint32_t v___x_2216_; 
v___x_2216_ = 2147483648;
return v___x_2216_;
}
}
}
v___jp_2217_:
{
uint32_t v___x_2219_; uint32_t v___x_2220_; 
v___x_2219_ = 8388608;
v___x_2220_ = lean_uint32_lor(v___y_2218_, v___x_2219_);
return v___x_2220_;
}
v___jp_2221_:
{
uint8_t v___x_2225_; 
v___x_2225_ = lean_uint64_dec_eq(v___y_2224_, v___y_2223_);
if (v___x_2225_ == 0)
{
uint64_t v___x_2226_; uint8_t v___x_2227_; 
v___x_2226_ = 8388608ULL;
v___x_2227_ = lean_uint64_dec_eq(v___y_2224_, v___x_2226_);
if (v___x_2227_ == 0)
{
uint32_t v___x_2228_; uint8_t v___x_2229_; 
v___x_2228_ = lean_uint64_to_uint32(v___y_2224_);
v___x_2229_ = lean_unbox(v___y_2222_);
lean_dec(v___y_2222_);
if (v___x_2229_ == 0)
{
uint32_t v___x_2230_; 
v___x_2230_ = 0;
v___y_2080_ = v___x_2228_;
v___y_2081_ = v___x_2230_;
goto v___jp_2079_;
}
else
{
uint32_t v___x_2231_; 
v___x_2231_ = 2147483648;
v___y_2080_ = v___x_2228_;
v___y_2081_ = v___x_2231_;
goto v___jp_2079_;
}
}
else
{
uint8_t v___x_2232_; 
v___x_2232_ = lean_unbox(v___y_2222_);
lean_dec(v___y_2222_);
if (v___x_2232_ == 0)
{
uint32_t v___x_2233_; 
v___x_2233_ = 0;
v___y_2218_ = v___x_2233_;
goto v___jp_2217_;
}
else
{
uint32_t v___x_2234_; 
v___x_2234_ = 2147483648;
v___y_2218_ = v___x_2234_;
goto v___jp_2217_;
}
}
}
else
{
uint8_t v___x_2235_; 
v___x_2235_ = lean_unbox(v___y_2222_);
lean_dec(v___y_2222_);
if (v___x_2235_ == 0)
{
uint32_t v___x_2236_; 
v___x_2236_ = 0;
return v___x_2236_;
}
else
{
uint32_t v___x_2237_; 
v___x_2237_ = 2147483648;
return v___x_2237_;
}
}
}
v___jp_2238_:
{
uint32_t v___x_2240_; uint32_t v___x_2241_; 
v___x_2240_ = 8388608;
v___x_2241_ = lean_uint32_lor(v___y_2239_, v___x_2240_);
return v___x_2241_;
}
v___jp_2242_:
{
uint8_t v___x_2246_; 
v___x_2246_ = lean_uint64_dec_eq(v___y_2245_, v___y_2244_);
if (v___x_2246_ == 0)
{
uint64_t v___x_2247_; uint8_t v___x_2248_; 
v___x_2247_ = 8388608ULL;
v___x_2248_ = lean_uint64_dec_eq(v___y_2245_, v___x_2247_);
if (v___x_2248_ == 0)
{
uint32_t v___x_2249_; uint8_t v___x_2250_; 
v___x_2249_ = lean_uint64_to_uint32(v___y_2245_);
v___x_2250_ = lean_unbox(v___y_2243_);
lean_dec(v___y_2243_);
if (v___x_2250_ == 0)
{
uint32_t v___x_2251_; 
v___x_2251_ = 0;
v___y_2086_ = v___x_2249_;
v___y_2087_ = v___x_2251_;
goto v___jp_2085_;
}
else
{
uint32_t v___x_2252_; 
v___x_2252_ = 2147483648;
v___y_2086_ = v___x_2249_;
v___y_2087_ = v___x_2252_;
goto v___jp_2085_;
}
}
else
{
uint8_t v___x_2253_; 
v___x_2253_ = lean_unbox(v___y_2243_);
lean_dec(v___y_2243_);
if (v___x_2253_ == 0)
{
uint32_t v___x_2254_; 
v___x_2254_ = 0;
v___y_2239_ = v___x_2254_;
goto v___jp_2238_;
}
else
{
uint32_t v___x_2255_; 
v___x_2255_ = 2147483648;
v___y_2239_ = v___x_2255_;
goto v___jp_2238_;
}
}
}
else
{
uint8_t v___x_2256_; 
v___x_2256_ = lean_unbox(v___y_2243_);
lean_dec(v___y_2243_);
if (v___x_2256_ == 0)
{
uint32_t v___x_2257_; 
v___x_2257_ = 0;
return v___x_2257_;
}
else
{
uint32_t v___x_2258_; 
v___x_2258_ = 2147483648;
return v___x_2258_;
}
}
}
v___jp_2262_:
{
uint32_t v___x_2266_; uint32_t v___x_2267_; uint32_t v___x_2268_; uint32_t v___x_2269_; uint32_t v___x_2270_; uint32_t v___x_2271_; 
v___x_2266_ = lean_uint32_land(v___y_2263_, v___x_2261_);
v___x_2267_ = lean_uint32_shift_left(v___x_2266_, v___x_2259_);
v___x_2268_ = lean_uint32_lor(v___y_2265_, v___x_2267_);
v___x_2269_ = 8388607;
v___x_2270_ = lean_uint32_land(v___y_2264_, v___x_2269_);
v___x_2271_ = lean_uint32_lor(v___x_2268_, v___x_2270_);
return v___x_2271_;
}
v___jp_2272_:
{
uint8_t v___x_2276_; 
v___x_2276_ = lean_unbox(v___y_2274_);
lean_dec(v___y_2274_);
if (v___x_2276_ == 0)
{
uint32_t v___x_2277_; 
v___x_2277_ = 0;
v___y_2263_ = v___y_2273_;
v___y_2264_ = v___y_2275_;
v___y_2265_ = v___x_2277_;
goto v___jp_2262_;
}
else
{
uint32_t v___x_2278_; 
v___x_2278_ = 2147483648;
v___y_2263_ = v___y_2273_;
v___y_2264_ = v___y_2275_;
v___y_2265_ = v___x_2278_;
goto v___jp_2262_;
}
}
v___jp_2279_:
{
uint64_t v___x_2284_; uint64_t v_encodedExponent_2285_; uint32_t v___x_2286_; uint64_t v___x_2287_; uint8_t v___x_2288_; 
v___x_2284_ = 171ULL;
v_encodedExponent_2285_ = lean_uint64_sub(v___y_2282_, v___x_2284_);
v___x_2286_ = lean_uint64_to_uint32(v_encodedExponent_2285_);
v___x_2287_ = 8388608ULL;
v___x_2288_ = lean_uint64_dec_lt(v___y_2283_, v___x_2287_);
if (v___x_2288_ == 0)
{
uint64_t v___x_2289_; uint32_t v___x_2290_; 
v___x_2289_ = lean_uint64_sub(v___y_2283_, v___x_2287_);
v___x_2290_ = lean_uint64_to_uint32(v___x_2289_);
v___y_2273_ = v___x_2286_;
v___y_2274_ = v___y_2281_;
v___y_2275_ = v___x_2290_;
goto v___jp_2272_;
}
else
{
uint32_t v___x_2291_; 
v___x_2291_ = lean_uint64_to_uint32(v___y_2280_);
v___y_2273_ = v___x_2286_;
v___y_2274_ = v___y_2281_;
v___y_2275_ = v___x_2291_;
goto v___jp_2272_;
}
}
v___jp_2292_:
{
uint64_t v___x_2298_; uint8_t v___x_2299_; 
v___x_2298_ = 425ULL;
v___x_2299_ = lean_uint64_dec_lt(v___x_2298_, v___y_2297_);
if (v___x_2299_ == 0)
{
if (v___y_2294_ == 0)
{
v___y_2280_ = v___y_2295_;
v___y_2281_ = v___y_2296_;
v___y_2282_ = v___y_2297_;
v___y_2283_ = v___y_2293_;
goto v___jp_2279_;
}
else
{
uint64_t v___x_2300_; 
v___x_2300_ = 8388608ULL;
v___y_2280_ = v___y_2295_;
v___y_2281_ = v___y_2296_;
v___y_2282_ = v___y_2297_;
v___y_2283_ = v___x_2300_;
goto v___jp_2279_;
}
}
else
{
uint8_t v___x_2301_; 
v___x_2301_ = lean_unbox(v___y_2296_);
lean_dec(v___y_2296_);
if (v___x_2301_ == 0)
{
uint32_t v___x_2302_; 
v___x_2302_ = 2139095040;
return v___x_2302_;
}
else
{
uint32_t v___x_2303_; 
v___x_2303_ = 4286578688;
return v___x_2303_;
}
}
}
v___jp_2304_:
{
uint64_t v___x_2309_; uint8_t v_carry_2310_; 
v___x_2309_ = 16777216ULL;
v_carry_2310_ = lean_uint64_dec_eq(v___y_2308_, v___x_2309_);
if (v_carry_2310_ == 0)
{
v___y_2293_ = v___y_2308_;
v___y_2294_ = v_carry_2310_;
v___y_2295_ = v___y_2306_;
v___y_2296_ = v___y_2307_;
v___y_2297_ = v___y_2305_;
goto v___jp_2292_;
}
else
{
uint64_t v___x_2311_; uint64_t v___x_2312_; 
v___x_2311_ = 1ULL;
v___x_2312_ = lean_uint64_add(v___y_2305_, v___x_2311_);
v___y_2293_ = v___y_2308_;
v___y_2294_ = v_carry_2310_;
v___y_2295_ = v___y_2306_;
v___y_2296_ = v___y_2307_;
v___y_2297_ = v___x_2312_;
goto v___jp_2292_;
}
}
v___jp_2313_:
{
uint64_t v_position_2320_; uint64_t v___x_2321_; uint8_t v___x_2322_; 
v_position_2320_ = lean_uint64_add(v___y_2319_, v___y_2315_);
v___x_2321_ = 172ULL;
v___x_2322_ = lean_uint64_dec_lt(v_position_2320_, v___x_2321_);
if (v___x_2322_ == 0)
{
uint64_t v___x_2323_; uint8_t v___x_2324_; 
v___x_2323_ = 23ULL;
v___x_2324_ = lean_uint64_dec_lt(v___y_2319_, v___x_2323_);
if (v___x_2324_ == 0)
{
uint64_t v___x_2325_; uint8_t v___x_2326_; 
v___x_2325_ = lean_uint64_sub(v___y_2319_, v___x_2323_);
v___x_2326_ = lean_uint64_dec_eq(v___x_2325_, v___y_2317_);
if (v___x_2326_ == 0)
{
uint64_t v___x_2327_; uint8_t v___x_2328_; 
v___x_2327_ = 64ULL;
v___x_2328_ = lean_uint64_dec_lt(v___x_2325_, v___x_2327_);
if (v___x_2328_ == 0)
{
uint8_t v___x_2329_; 
v___x_2329_ = lean_uint64_dec_eq(v___x_2325_, v___x_2327_);
if (v___x_2329_ == 0)
{
lean_dec(v___y_2314_);
v___y_2305_ = v_position_2320_;
v___y_2306_ = v___y_2317_;
v___y_2307_ = v___y_2318_;
v___y_2308_ = v___y_2317_;
goto v___jp_2304_;
}
else
{
uint64_t v___x_2330_; uint64_t v___x_2331_; uint8_t v___x_2332_; 
v___x_2330_ = 9223372036854775808ULL;
v___x_2331_ = lean_unbox_uint64(v___y_2314_);
lean_dec(v___y_2314_);
v___x_2332_ = lean_uint64_dec_lt(v___x_2330_, v___x_2331_);
if (v___x_2332_ == 0)
{
v___y_2305_ = v_position_2320_;
v___y_2306_ = v___y_2317_;
v___y_2307_ = v___y_2318_;
v___y_2308_ = v___y_2317_;
goto v___jp_2304_;
}
else
{
uint64_t v___x_2333_; 
v___x_2333_ = 1ULL;
v___y_2305_ = v_position_2320_;
v___y_2306_ = v___y_2317_;
v___y_2307_ = v___y_2318_;
v___y_2308_ = v___x_2333_;
goto v___jp_2304_;
}
}
}
else
{
uint64_t v___x_2334_; uint64_t v_quotient_2335_; uint64_t v___x_2336_; uint64_t v___x_2337_; uint64_t v___x_2338_; uint64_t v___x_2339_; uint64_t v_remainder_2340_; uint64_t v___x_2341_; uint64_t v_half_2342_; uint8_t v___x_2343_; 
v___x_2334_ = lean_unbox_uint64(v___y_2314_);
v_quotient_2335_ = lean_uint64_shift_right(v___x_2334_, v___x_2325_);
v___x_2336_ = 1ULL;
v___x_2337_ = lean_uint64_shift_left(v___x_2336_, v___x_2325_);
v___x_2338_ = lean_uint64_sub(v___x_2337_, v___x_2336_);
v___x_2339_ = lean_unbox_uint64(v___y_2314_);
lean_dec(v___y_2314_);
v_remainder_2340_ = lean_uint64_land(v___x_2339_, v___x_2338_);
v___x_2341_ = lean_uint64_sub(v___x_2325_, v___x_2336_);
v_half_2342_ = lean_uint64_shift_left(v___x_2336_, v___x_2341_);
v___x_2343_ = lean_uint64_dec_lt(v_remainder_2340_, v_half_2342_);
if (v___x_2343_ == 0)
{
uint8_t v___x_2344_; 
v___x_2344_ = lean_uint64_dec_lt(v_half_2342_, v_remainder_2340_);
if (v___x_2344_ == 0)
{
uint64_t v___x_2345_; uint8_t v___x_2346_; 
v___x_2345_ = lean_uint64_land(v_quotient_2335_, v___x_2336_);
v___x_2346_ = lean_uint64_dec_eq(v___x_2345_, v___y_2317_);
if (v___x_2346_ == 0)
{
uint64_t v___x_2347_; 
v___x_2347_ = lean_uint64_add(v_quotient_2335_, v___x_2336_);
v___y_2305_ = v_position_2320_;
v___y_2306_ = v___y_2317_;
v___y_2307_ = v___y_2318_;
v___y_2308_ = v___x_2347_;
goto v___jp_2304_;
}
else
{
v___y_2305_ = v_position_2320_;
v___y_2306_ = v___y_2317_;
v___y_2307_ = v___y_2318_;
v___y_2308_ = v_quotient_2335_;
goto v___jp_2304_;
}
}
else
{
uint64_t v___x_2348_; 
v___x_2348_ = lean_uint64_add(v_quotient_2335_, v___x_2336_);
v___y_2305_ = v_position_2320_;
v___y_2306_ = v___y_2317_;
v___y_2307_ = v___y_2318_;
v___y_2308_ = v___x_2348_;
goto v___jp_2304_;
}
}
else
{
v___y_2305_ = v_position_2320_;
v___y_2306_ = v___y_2317_;
v___y_2307_ = v___y_2318_;
v___y_2308_ = v_quotient_2335_;
goto v___jp_2304_;
}
}
}
else
{
uint64_t v___x_2349_; 
v___x_2349_ = lean_unbox_uint64(v___y_2314_);
lean_dec(v___y_2314_);
v___y_2305_ = v_position_2320_;
v___y_2306_ = v___y_2317_;
v___y_2307_ = v___y_2318_;
v___y_2308_ = v___x_2349_;
goto v___jp_2304_;
}
}
else
{
uint64_t v___x_2350_; uint64_t v___x_2351_; uint64_t v___x_2352_; 
v___x_2350_ = lean_uint64_sub(v___x_2323_, v___y_2319_);
v___x_2351_ = lean_unbox_uint64(v___y_2314_);
lean_dec(v___y_2314_);
v___x_2352_ = lean_uint64_shift_left(v___x_2351_, v___x_2350_);
v___y_2305_ = v_position_2320_;
v___y_2306_ = v___y_2317_;
v___y_2307_ = v___y_2318_;
v___y_2308_ = v___x_2352_;
goto v___jp_2304_;
}
}
else
{
uint8_t v___x_2353_; 
v___x_2353_ = lean_uint64_dec_lt(v___y_2315_, v___y_2316_);
if (v___x_2353_ == 0)
{
uint64_t v___x_2354_; uint64_t v___x_2355_; uint64_t v___x_2356_; 
v___x_2354_ = lean_uint64_sub(v___y_2315_, v___y_2316_);
v___x_2355_ = lean_unbox_uint64(v___y_2314_);
lean_dec(v___y_2314_);
v___x_2356_ = lean_uint64_shift_left(v___x_2355_, v___x_2354_);
v___y_2117_ = v___y_2317_;
v___y_2118_ = v___y_2318_;
v___y_2119_ = v___x_2356_;
goto v___jp_2116_;
}
else
{
uint64_t v___x_2357_; uint8_t v___x_2358_; 
v___x_2357_ = lean_uint64_sub(v___y_2316_, v___y_2315_);
v___x_2358_ = lean_uint64_dec_eq(v___x_2357_, v___y_2317_);
if (v___x_2358_ == 0)
{
uint64_t v___x_2359_; uint8_t v___x_2360_; 
v___x_2359_ = 64ULL;
v___x_2360_ = lean_uint64_dec_lt(v___x_2357_, v___x_2359_);
if (v___x_2360_ == 0)
{
uint8_t v___x_2361_; 
v___x_2361_ = lean_uint64_dec_eq(v___x_2357_, v___x_2359_);
if (v___x_2361_ == 0)
{
lean_dec(v___y_2314_);
v___y_2117_ = v___y_2317_;
v___y_2118_ = v___y_2318_;
v___y_2119_ = v___y_2317_;
goto v___jp_2116_;
}
else
{
uint64_t v___x_2362_; uint64_t v___x_2363_; uint8_t v___x_2364_; 
v___x_2362_ = 9223372036854775808ULL;
v___x_2363_ = lean_unbox_uint64(v___y_2314_);
lean_dec(v___y_2314_);
v___x_2364_ = lean_uint64_dec_lt(v___x_2362_, v___x_2363_);
if (v___x_2364_ == 0)
{
v___y_2117_ = v___y_2317_;
v___y_2118_ = v___y_2318_;
v___y_2119_ = v___y_2317_;
goto v___jp_2116_;
}
else
{
uint64_t v___x_2365_; 
v___x_2365_ = 1ULL;
v___y_2117_ = v___y_2317_;
v___y_2118_ = v___y_2318_;
v___y_2119_ = v___x_2365_;
goto v___jp_2116_;
}
}
}
else
{
uint64_t v___x_2366_; uint64_t v_quotient_2367_; uint64_t v___x_2368_; uint64_t v___x_2369_; uint64_t v___x_2370_; uint64_t v___x_2371_; uint64_t v_remainder_2372_; uint64_t v___x_2373_; uint64_t v_half_2374_; uint8_t v___x_2375_; 
v___x_2366_ = lean_unbox_uint64(v___y_2314_);
v_quotient_2367_ = lean_uint64_shift_right(v___x_2366_, v___x_2357_);
v___x_2368_ = 1ULL;
v___x_2369_ = lean_uint64_shift_left(v___x_2368_, v___x_2357_);
v___x_2370_ = lean_uint64_sub(v___x_2369_, v___x_2368_);
v___x_2371_ = lean_unbox_uint64(v___y_2314_);
lean_dec(v___y_2314_);
v_remainder_2372_ = lean_uint64_land(v___x_2371_, v___x_2370_);
v___x_2373_ = lean_uint64_sub(v___x_2357_, v___x_2368_);
v_half_2374_ = lean_uint64_shift_left(v___x_2368_, v___x_2373_);
v___x_2375_ = lean_uint64_dec_lt(v_remainder_2372_, v_half_2374_);
if (v___x_2375_ == 0)
{
uint8_t v___x_2376_; 
v___x_2376_ = lean_uint64_dec_lt(v_half_2374_, v_remainder_2372_);
if (v___x_2376_ == 0)
{
uint64_t v___x_2377_; uint8_t v___x_2378_; 
v___x_2377_ = lean_uint64_land(v_quotient_2367_, v___x_2368_);
v___x_2378_ = lean_uint64_dec_eq(v___x_2377_, v___y_2317_);
if (v___x_2378_ == 0)
{
uint64_t v___x_2379_; 
v___x_2379_ = lean_uint64_add(v_quotient_2367_, v___x_2368_);
v___y_2117_ = v___y_2317_;
v___y_2118_ = v___y_2318_;
v___y_2119_ = v___x_2379_;
goto v___jp_2116_;
}
else
{
v___y_2117_ = v___y_2317_;
v___y_2118_ = v___y_2318_;
v___y_2119_ = v_quotient_2367_;
goto v___jp_2116_;
}
}
else
{
uint64_t v___x_2380_; 
v___x_2380_ = lean_uint64_add(v_quotient_2367_, v___x_2368_);
v___y_2117_ = v___y_2317_;
v___y_2118_ = v___y_2318_;
v___y_2119_ = v___x_2380_;
goto v___jp_2116_;
}
}
else
{
v___y_2117_ = v___y_2317_;
v___y_2118_ = v___y_2318_;
v___y_2119_ = v_quotient_2367_;
goto v___jp_2116_;
}
}
}
else
{
uint64_t v___x_2381_; 
v___x_2381_ = lean_unbox_uint64(v___y_2314_);
lean_dec(v___y_2314_);
v___y_2117_ = v___y_2317_;
v___y_2118_ = v___y_2318_;
v___y_2119_ = v___x_2381_;
goto v___jp_2116_;
}
}
}
}
v___jp_2382_:
{
uint64_t v___x_2390_; uint64_t v___x_2391_; uint8_t v___x_2392_; 
v___x_2390_ = 1ULL;
v___x_2391_ = lean_uint64_shift_right(v___y_2385_, v___x_2390_);
v___x_2392_ = lean_uint64_dec_eq(v___x_2391_, v___y_2387_);
if (v___x_2392_ == 0)
{
uint64_t v___x_2393_; 
v___x_2393_ = lean_uint64_add(v___y_2389_, v___x_2390_);
v___y_2314_ = v___y_2383_;
v___y_2315_ = v___y_2384_;
v___y_2316_ = v___y_2386_;
v___y_2317_ = v___y_2387_;
v___y_2318_ = v___y_2388_;
v___y_2319_ = v___x_2393_;
goto v___jp_2313_;
}
else
{
v___y_2314_ = v___y_2383_;
v___y_2315_ = v___y_2384_;
v___y_2316_ = v___y_2386_;
v___y_2317_ = v___y_2387_;
v___y_2318_ = v___y_2388_;
v___y_2319_ = v___y_2389_;
goto v___jp_2313_;
}
}
v___jp_2394_:
{
uint64_t v___x_2404_; uint8_t v___x_2405_; 
v___x_2404_ = lean_uint64_shift_right(v___y_2399_, v___y_2395_);
v___x_2405_ = lean_uint64_dec_eq(v___x_2404_, v___y_2401_);
if (v___x_2405_ == 0)
{
uint64_t v___x_2406_; 
v___x_2406_ = lean_uint64_add(v___y_2400_, v___y_2395_);
v___y_2383_ = v___y_2396_;
v___y_2384_ = v___y_2397_;
v___y_2385_ = v___y_2403_;
v___y_2386_ = v___y_2398_;
v___y_2387_ = v___y_2401_;
v___y_2388_ = v___y_2402_;
v___y_2389_ = v___x_2406_;
goto v___jp_2382_;
}
else
{
v___y_2383_ = v___y_2396_;
v___y_2384_ = v___y_2397_;
v___y_2385_ = v___y_2403_;
v___y_2386_ = v___y_2398_;
v___y_2387_ = v___y_2401_;
v___y_2388_ = v___y_2402_;
v___y_2389_ = v___y_2400_;
goto v___jp_2382_;
}
}
v___jp_2407_:
{
uint64_t v___x_2415_; uint64_t v___x_2416_; uint8_t v___x_2417_; 
v___x_2415_ = 2ULL;
v___x_2416_ = lean_uint64_shift_right(v___y_2411_, v___x_2415_);
v___x_2417_ = lean_uint64_dec_eq(v___x_2416_, v___y_2412_);
if (v___x_2417_ == 0)
{
v___y_2395_ = v___x_2415_;
v___y_2396_ = v___y_2408_;
v___y_2397_ = v___y_2409_;
v___y_2398_ = v___y_2410_;
v___y_2399_ = v___y_2411_;
v___y_2400_ = v___y_2414_;
v___y_2401_ = v___y_2412_;
v___y_2402_ = v___y_2413_;
v___y_2403_ = v___x_2416_;
goto v___jp_2394_;
}
else
{
v___y_2395_ = v___x_2415_;
v___y_2396_ = v___y_2408_;
v___y_2397_ = v___y_2409_;
v___y_2398_ = v___y_2410_;
v___y_2399_ = v___y_2411_;
v___y_2400_ = v___y_2414_;
v___y_2401_ = v___y_2412_;
v___y_2402_ = v___y_2413_;
v___y_2403_ = v___y_2411_;
goto v___jp_2394_;
}
}
v___jp_2418_:
{
uint64_t v___x_2428_; uint8_t v___x_2429_; 
v___x_2428_ = lean_uint64_shift_right(v___y_2420_, v___y_2419_);
v___x_2429_ = lean_uint64_dec_eq(v___x_2428_, v___y_2425_);
if (v___x_2429_ == 0)
{
uint64_t v___x_2430_; 
v___x_2430_ = lean_uint64_add(v___y_2424_, v___y_2419_);
v___y_2408_ = v___y_2421_;
v___y_2409_ = v___y_2422_;
v___y_2410_ = v___y_2423_;
v___y_2411_ = v___y_2427_;
v___y_2412_ = v___y_2425_;
v___y_2413_ = v___y_2426_;
v___y_2414_ = v___x_2430_;
goto v___jp_2407_;
}
else
{
v___y_2408_ = v___y_2421_;
v___y_2409_ = v___y_2422_;
v___y_2410_ = v___y_2423_;
v___y_2411_ = v___y_2427_;
v___y_2412_ = v___y_2425_;
v___y_2413_ = v___y_2426_;
v___y_2414_ = v___y_2424_;
goto v___jp_2407_;
}
}
v___jp_2431_:
{
uint64_t v___x_2439_; uint64_t v___x_2440_; uint8_t v___x_2441_; 
v___x_2439_ = 4ULL;
v___x_2440_ = lean_uint64_shift_right(v___y_2432_, v___x_2439_);
v___x_2441_ = lean_uint64_dec_eq(v___x_2440_, v___y_2436_);
if (v___x_2441_ == 0)
{
v___y_2419_ = v___x_2439_;
v___y_2420_ = v___y_2432_;
v___y_2421_ = v___y_2433_;
v___y_2422_ = v___y_2434_;
v___y_2423_ = v___y_2435_;
v___y_2424_ = v___y_2438_;
v___y_2425_ = v___y_2436_;
v___y_2426_ = v___y_2437_;
v___y_2427_ = v___x_2440_;
goto v___jp_2418_;
}
else
{
v___y_2419_ = v___x_2439_;
v___y_2420_ = v___y_2432_;
v___y_2421_ = v___y_2433_;
v___y_2422_ = v___y_2434_;
v___y_2423_ = v___y_2435_;
v___y_2424_ = v___y_2438_;
v___y_2425_ = v___y_2436_;
v___y_2426_ = v___y_2437_;
v___y_2427_ = v___y_2432_;
goto v___jp_2418_;
}
}
v___jp_2442_:
{
uint64_t v___x_2452_; uint8_t v___x_2453_; 
v___x_2452_ = lean_uint64_shift_right(v___y_2448_, v___y_2446_);
v___x_2453_ = lean_uint64_dec_eq(v___x_2452_, v___y_2447_);
if (v___x_2453_ == 0)
{
uint64_t v___x_2454_; 
v___x_2454_ = lean_uint64_add(v___y_2450_, v___y_2446_);
v___y_2432_ = v___y_2451_;
v___y_2433_ = v___y_2443_;
v___y_2434_ = v___y_2444_;
v___y_2435_ = v___y_2445_;
v___y_2436_ = v___y_2447_;
v___y_2437_ = v___y_2449_;
v___y_2438_ = v___x_2454_;
goto v___jp_2431_;
}
else
{
v___y_2432_ = v___y_2451_;
v___y_2433_ = v___y_2443_;
v___y_2434_ = v___y_2444_;
v___y_2435_ = v___y_2445_;
v___y_2436_ = v___y_2447_;
v___y_2437_ = v___y_2449_;
v___y_2438_ = v___y_2450_;
goto v___jp_2431_;
}
}
v___jp_2455_:
{
uint64_t v___x_2463_; uint64_t v___x_2464_; uint8_t v___x_2465_; 
v___x_2463_ = 8ULL;
v___x_2464_ = lean_uint64_shift_right(v___y_2460_, v___x_2463_);
v___x_2465_ = lean_uint64_dec_eq(v___x_2464_, v___y_2459_);
if (v___x_2465_ == 0)
{
v___y_2443_ = v___y_2456_;
v___y_2444_ = v___y_2457_;
v___y_2445_ = v___y_2458_;
v___y_2446_ = v___x_2463_;
v___y_2447_ = v___y_2459_;
v___y_2448_ = v___y_2460_;
v___y_2449_ = v___y_2461_;
v___y_2450_ = v___y_2462_;
v___y_2451_ = v___x_2464_;
goto v___jp_2442_;
}
else
{
v___y_2443_ = v___y_2456_;
v___y_2444_ = v___y_2457_;
v___y_2445_ = v___y_2458_;
v___y_2446_ = v___x_2463_;
v___y_2447_ = v___y_2459_;
v___y_2448_ = v___y_2460_;
v___y_2449_ = v___y_2461_;
v___y_2450_ = v___y_2462_;
v___y_2451_ = v___y_2460_;
goto v___jp_2442_;
}
}
v___jp_2466_:
{
uint64_t v___x_2476_; uint8_t v___x_2477_; 
v___x_2476_ = lean_uint64_shift_right(v___y_2470_, v___y_2471_);
v___x_2477_ = lean_uint64_dec_eq(v___x_2476_, v___y_2472_);
if (v___x_2477_ == 0)
{
uint64_t v___x_2478_; 
v___x_2478_ = lean_uint64_add(v___y_2474_, v___y_2471_);
v___y_2456_ = v___y_2467_;
v___y_2457_ = v___y_2468_;
v___y_2458_ = v___y_2469_;
v___y_2459_ = v___y_2472_;
v___y_2460_ = v___y_2475_;
v___y_2461_ = v___y_2473_;
v___y_2462_ = v___x_2478_;
goto v___jp_2455_;
}
else
{
v___y_2456_ = v___y_2467_;
v___y_2457_ = v___y_2468_;
v___y_2458_ = v___y_2469_;
v___y_2459_ = v___y_2472_;
v___y_2460_ = v___y_2475_;
v___y_2461_ = v___y_2473_;
v___y_2462_ = v___y_2474_;
goto v___jp_2455_;
}
}
v___jp_2479_:
{
uint64_t v___x_2487_; uint64_t v___x_2488_; uint8_t v___x_2489_; 
v___x_2487_ = 16ULL;
v___x_2488_ = lean_uint64_shift_right(v___y_2483_, v___x_2487_);
v___x_2489_ = lean_uint64_dec_eq(v___x_2488_, v___y_2484_);
if (v___x_2489_ == 0)
{
v___y_2467_ = v___y_2480_;
v___y_2468_ = v___y_2481_;
v___y_2469_ = v___y_2482_;
v___y_2470_ = v___y_2483_;
v___y_2471_ = v___x_2487_;
v___y_2472_ = v___y_2484_;
v___y_2473_ = v___y_2485_;
v___y_2474_ = v___y_2486_;
v___y_2475_ = v___x_2488_;
goto v___jp_2466_;
}
else
{
v___y_2467_ = v___y_2480_;
v___y_2468_ = v___y_2481_;
v___y_2469_ = v___y_2482_;
v___y_2470_ = v___y_2483_;
v___y_2471_ = v___x_2487_;
v___y_2472_ = v___y_2484_;
v___y_2473_ = v___y_2485_;
v___y_2474_ = v___y_2486_;
v___y_2475_ = v___y_2483_;
goto v___jp_2466_;
}
}
v___jp_2490_:
{
uint64_t v___x_2498_; uint64_t v___x_2499_; uint8_t v___x_2500_; 
v___x_2498_ = lean_unbox_uint64(v___y_2491_);
v___x_2499_ = lean_uint64_shift_right(v___x_2498_, v___y_2494_);
v___x_2500_ = lean_uint64_dec_eq(v___x_2499_, v___y_2495_);
if (v___x_2500_ == 0)
{
v___y_2480_ = v___y_2491_;
v___y_2481_ = v___y_2492_;
v___y_2482_ = v___y_2493_;
v___y_2483_ = v___y_2497_;
v___y_2484_ = v___y_2495_;
v___y_2485_ = v___y_2496_;
v___y_2486_ = v___y_2494_;
goto v___jp_2479_;
}
else
{
v___y_2480_ = v___y_2491_;
v___y_2481_ = v___y_2492_;
v___y_2482_ = v___y_2493_;
v___y_2483_ = v___y_2497_;
v___y_2484_ = v___y_2495_;
v___y_2485_ = v___y_2496_;
v___y_2486_ = v___y_2495_;
goto v___jp_2479_;
}
}
v___jp_2501_:
{
uint64_t v___x_2505_; uint64_t v___x_2506_; uint8_t v___x_2507_; 
v___x_2505_ = 0ULL;
v___x_2506_ = lean_unbox_uint64(v_snd_2504_);
v___x_2507_ = lean_uint64_dec_eq(v___x_2506_, v___x_2505_);
if (v___x_2507_ == 0)
{
uint64_t v___x_2508_; uint64_t v___x_2509_; uint64_t v___x_2510_; uint64_t v___x_2511_; uint64_t v___x_2512_; uint8_t v___x_2513_; 
v___x_2508_ = 149ULL;
v___x_2509_ = lean_uint64_add(v___y_2502_, v___x_2508_);
v___x_2510_ = 32ULL;
v___x_2511_ = lean_unbox_uint64(v_snd_2504_);
v___x_2512_ = lean_uint64_shift_right(v___x_2511_, v___x_2510_);
v___x_2513_ = lean_uint64_dec_eq(v___x_2512_, v___x_2505_);
if (v___x_2513_ == 0)
{
v___y_2491_ = v_snd_2504_;
v___y_2492_ = v___x_2509_;
v___y_2493_ = v___x_2508_;
v___y_2494_ = v___x_2510_;
v___y_2495_ = v___x_2505_;
v___y_2496_ = v_fst_2503_;
v___y_2497_ = v___x_2512_;
goto v___jp_2490_;
}
else
{
uint64_t v___x_2514_; 
v___x_2514_ = lean_unbox_uint64(v_snd_2504_);
v___y_2491_ = v_snd_2504_;
v___y_2492_ = v___x_2509_;
v___y_2493_ = v___x_2508_;
v___y_2494_ = v___x_2510_;
v___y_2495_ = v___x_2505_;
v___y_2496_ = v_fst_2503_;
v___y_2497_ = v___x_2514_;
goto v___jp_2490_;
}
}
else
{
uint8_t v___x_2515_; 
lean_dec(v_snd_2504_);
v___x_2515_ = lean_unbox(v_fst_2503_);
lean_dec(v_fst_2503_);
if (v___x_2515_ == 0)
{
uint32_t v___x_2516_; 
v___x_2516_ = 0;
return v___x_2516_;
}
else
{
uint32_t v___x_2517_; 
v___x_2517_ = 2147483648;
return v___x_2517_;
}
}
}
v___jp_2518_:
{
uint8_t v___x_2525_; 
v___x_2525_ = lean_uint64_dec_eq(v___y_2522_, v___y_2520_);
if (v___x_2525_ == 0)
{
uint8_t v___x_2526_; 
v___x_2526_ = lean_uint64_dec_lt(v___y_2522_, v___y_2520_);
if (v___x_2526_ == 0)
{
uint64_t v___x_2527_; lean_object* v___x_2528_; lean_object* v___x_2529_; 
v___x_2527_ = lean_uint64_sub(v___y_2522_, v___y_2520_);
v___x_2528_ = lean_box(v___y_2523_);
v___x_2529_ = lean_box_uint64(v___x_2527_);
v___y_2502_ = v___y_2519_;
v_fst_2503_ = v___x_2528_;
v_snd_2504_ = v___x_2529_;
goto v___jp_2501_;
}
else
{
uint64_t v___x_2530_; lean_object* v___x_2531_; lean_object* v___x_2532_; 
v___x_2530_ = lean_uint64_sub(v___y_2520_, v___y_2522_);
v___x_2531_ = lean_box(v___y_2521_);
v___x_2532_ = lean_box_uint64(v___x_2530_);
v___y_2502_ = v___y_2519_;
v_fst_2503_ = v___x_2531_;
v_snd_2504_ = v___x_2532_;
goto v___jp_2501_;
}
}
else
{
lean_object* v___x_2533_; lean_object* v___x_2534_; 
v___x_2533_ = lean_box(v___y_2524_);
v___x_2534_ = ((lean_object*)(lp_competition_Submission_TunedAdd_core___boxed__const__1));
v___y_2502_ = v___y_2519_;
v_fst_2503_ = v___x_2533_;
v_snd_2504_ = v___x_2534_;
goto v___jp_2501_;
}
}
v___jp_2535_:
{
if (v___y_2541_ == 0)
{
v___y_2519_ = v___y_2536_;
v___y_2520_ = v___y_2537_;
v___y_2521_ = v___y_2539_;
v___y_2522_ = v___y_2538_;
v___y_2523_ = v___y_2540_;
v___y_2524_ = v___y_2541_;
goto v___jp_2518_;
}
else
{
uint64_t v___x_2542_; lean_object* v___x_2543_; lean_object* v___x_2544_; 
v___x_2542_ = lean_uint64_add(v___y_2538_, v___y_2537_);
v___x_2543_ = lean_box(v___y_2540_);
v___x_2544_ = lean_box_uint64(v___x_2542_);
v___y_2502_ = v___y_2536_;
v_fst_2503_ = v___x_2543_;
v_snd_2504_ = v___x_2544_;
goto v___jp_2501_;
}
}
v___jp_2545_:
{
uint32_t v___x_2549_; uint32_t v___x_2550_; uint32_t v___x_2551_; uint32_t v___x_2552_; uint32_t v___x_2553_; uint32_t v___x_2554_; 
v___x_2549_ = lean_uint32_land(v___y_2547_, v___x_2261_);
v___x_2550_ = lean_uint32_shift_left(v___x_2549_, v___x_2259_);
v___x_2551_ = lean_uint32_lor(v___y_2548_, v___x_2550_);
v___x_2552_ = 8388607;
v___x_2553_ = lean_uint32_land(v___y_2546_, v___x_2552_);
v___x_2554_ = lean_uint32_lor(v___x_2551_, v___x_2553_);
return v___x_2554_;
}
v___jp_2555_:
{
uint8_t v___x_2559_; 
v___x_2559_ = lean_unbox(v___y_2557_);
lean_dec(v___y_2557_);
if (v___x_2559_ == 0)
{
uint32_t v___x_2560_; 
v___x_2560_ = 0;
v___y_2546_ = v___y_2558_;
v___y_2547_ = v___y_2556_;
v___y_2548_ = v___x_2560_;
goto v___jp_2545_;
}
else
{
uint32_t v___x_2561_; 
v___x_2561_ = 2147483648;
v___y_2546_ = v___y_2558_;
v___y_2547_ = v___y_2556_;
v___y_2548_ = v___x_2561_;
goto v___jp_2545_;
}
}
v___jp_2562_:
{
uint64_t v___x_2567_; uint64_t v_encodedExponent_2568_; uint32_t v___x_2569_; uint64_t v___x_2570_; uint8_t v___x_2571_; 
v___x_2567_ = 171ULL;
v_encodedExponent_2568_ = lean_uint64_sub(v___y_2563_, v___x_2567_);
v___x_2569_ = lean_uint64_to_uint32(v_encodedExponent_2568_);
v___x_2570_ = 8388608ULL;
v___x_2571_ = lean_uint64_dec_lt(v___y_2566_, v___x_2570_);
if (v___x_2571_ == 0)
{
uint64_t v___x_2572_; uint32_t v___x_2573_; 
v___x_2572_ = lean_uint64_sub(v___y_2566_, v___x_2570_);
v___x_2573_ = lean_uint64_to_uint32(v___x_2572_);
v___y_2556_ = v___x_2569_;
v___y_2557_ = v___y_2565_;
v___y_2558_ = v___x_2573_;
goto v___jp_2555_;
}
else
{
uint32_t v___x_2574_; 
v___x_2574_ = lean_uint64_to_uint32(v___y_2564_);
v___y_2556_ = v___x_2569_;
v___y_2557_ = v___y_2565_;
v___y_2558_ = v___x_2574_;
goto v___jp_2555_;
}
}
v___jp_2575_:
{
uint64_t v___x_2581_; uint8_t v___x_2582_; 
v___x_2581_ = 425ULL;
v___x_2582_ = lean_uint64_dec_lt(v___x_2581_, v___y_2580_);
if (v___x_2582_ == 0)
{
if (v___y_2578_ == 0)
{
v___y_2563_ = v___y_2580_;
v___y_2564_ = v___y_2576_;
v___y_2565_ = v___y_2579_;
v___y_2566_ = v___y_2577_;
goto v___jp_2562_;
}
else
{
uint64_t v___x_2583_; 
v___x_2583_ = 8388608ULL;
v___y_2563_ = v___y_2580_;
v___y_2564_ = v___y_2576_;
v___y_2565_ = v___y_2579_;
v___y_2566_ = v___x_2583_;
goto v___jp_2562_;
}
}
else
{
uint8_t v___x_2584_; 
v___x_2584_ = lean_unbox(v___y_2579_);
lean_dec(v___y_2579_);
if (v___x_2584_ == 0)
{
uint32_t v___x_2585_; 
v___x_2585_ = 2139095040;
return v___x_2585_;
}
else
{
uint32_t v___x_2586_; 
v___x_2586_ = 4286578688;
return v___x_2586_;
}
}
}
v___jp_2587_:
{
uint64_t v___x_2592_; uint8_t v_carry_2593_; 
v___x_2592_ = 16777216ULL;
v_carry_2593_ = lean_uint64_dec_eq(v___y_2591_, v___x_2592_);
if (v_carry_2593_ == 0)
{
v___y_2576_ = v___y_2588_;
v___y_2577_ = v___y_2591_;
v___y_2578_ = v_carry_2593_;
v___y_2579_ = v___y_2590_;
v___y_2580_ = v___y_2589_;
goto v___jp_2575_;
}
else
{
uint64_t v___x_2594_; uint64_t v___x_2595_; 
v___x_2594_ = 1ULL;
v___x_2595_ = lean_uint64_add(v___y_2589_, v___x_2594_);
v___y_2576_ = v___y_2588_;
v___y_2577_ = v___y_2591_;
v___y_2578_ = v_carry_2593_;
v___y_2579_ = v___y_2590_;
v___y_2580_ = v___x_2595_;
goto v___jp_2575_;
}
}
v___jp_2596_:
{
uint64_t v_position_2603_; uint64_t v___x_2604_; uint8_t v___x_2605_; 
v_position_2603_ = lean_uint64_add(v___y_2602_, v___y_2599_);
v___x_2604_ = 172ULL;
v___x_2605_ = lean_uint64_dec_lt(v_position_2603_, v___x_2604_);
if (v___x_2605_ == 0)
{
uint64_t v___x_2606_; uint8_t v___x_2607_; 
v___x_2606_ = 23ULL;
v___x_2607_ = lean_uint64_dec_lt(v___y_2602_, v___x_2606_);
if (v___x_2607_ == 0)
{
uint64_t v___x_2608_; uint8_t v___x_2609_; 
v___x_2608_ = lean_uint64_sub(v___y_2602_, v___x_2606_);
v___x_2609_ = lean_uint64_dec_eq(v___x_2608_, v___y_2597_);
if (v___x_2609_ == 0)
{
uint64_t v___x_2610_; uint8_t v___x_2611_; 
v___x_2610_ = 64ULL;
v___x_2611_ = lean_uint64_dec_lt(v___x_2608_, v___x_2610_);
if (v___x_2611_ == 0)
{
uint8_t v___x_2612_; 
v___x_2612_ = lean_uint64_dec_eq(v___x_2608_, v___x_2610_);
if (v___x_2612_ == 0)
{
lean_dec(v___y_2601_);
v___y_2588_ = v___y_2597_;
v___y_2589_ = v_position_2603_;
v___y_2590_ = v___y_2600_;
v___y_2591_ = v___y_2597_;
goto v___jp_2587_;
}
else
{
uint64_t v___x_2613_; uint64_t v___x_2614_; uint8_t v___x_2615_; 
v___x_2613_ = 9223372036854775808ULL;
v___x_2614_ = lean_unbox_uint64(v___y_2601_);
lean_dec(v___y_2601_);
v___x_2615_ = lean_uint64_dec_lt(v___x_2613_, v___x_2614_);
if (v___x_2615_ == 0)
{
v___y_2588_ = v___y_2597_;
v___y_2589_ = v_position_2603_;
v___y_2590_ = v___y_2600_;
v___y_2591_ = v___y_2597_;
goto v___jp_2587_;
}
else
{
uint64_t v___x_2616_; 
v___x_2616_ = 1ULL;
v___y_2588_ = v___y_2597_;
v___y_2589_ = v_position_2603_;
v___y_2590_ = v___y_2600_;
v___y_2591_ = v___x_2616_;
goto v___jp_2587_;
}
}
}
else
{
uint64_t v___x_2617_; uint64_t v_quotient_2618_; uint64_t v___x_2619_; uint64_t v___x_2620_; uint64_t v___x_2621_; uint64_t v___x_2622_; uint64_t v_remainder_2623_; uint64_t v___x_2624_; uint64_t v_half_2625_; uint8_t v___x_2626_; 
v___x_2617_ = lean_unbox_uint64(v___y_2601_);
v_quotient_2618_ = lean_uint64_shift_right(v___x_2617_, v___x_2608_);
v___x_2619_ = 1ULL;
v___x_2620_ = lean_uint64_shift_left(v___x_2619_, v___x_2608_);
v___x_2621_ = lean_uint64_sub(v___x_2620_, v___x_2619_);
v___x_2622_ = lean_unbox_uint64(v___y_2601_);
lean_dec(v___y_2601_);
v_remainder_2623_ = lean_uint64_land(v___x_2622_, v___x_2621_);
v___x_2624_ = lean_uint64_sub(v___x_2608_, v___x_2619_);
v_half_2625_ = lean_uint64_shift_left(v___x_2619_, v___x_2624_);
v___x_2626_ = lean_uint64_dec_lt(v_remainder_2623_, v_half_2625_);
if (v___x_2626_ == 0)
{
uint8_t v___x_2627_; 
v___x_2627_ = lean_uint64_dec_lt(v_half_2625_, v_remainder_2623_);
if (v___x_2627_ == 0)
{
uint64_t v___x_2628_; uint8_t v___x_2629_; 
v___x_2628_ = lean_uint64_land(v_quotient_2618_, v___x_2619_);
v___x_2629_ = lean_uint64_dec_eq(v___x_2628_, v___y_2597_);
if (v___x_2629_ == 0)
{
uint64_t v___x_2630_; 
v___x_2630_ = lean_uint64_add(v_quotient_2618_, v___x_2619_);
v___y_2588_ = v___y_2597_;
v___y_2589_ = v_position_2603_;
v___y_2590_ = v___y_2600_;
v___y_2591_ = v___x_2630_;
goto v___jp_2587_;
}
else
{
v___y_2588_ = v___y_2597_;
v___y_2589_ = v_position_2603_;
v___y_2590_ = v___y_2600_;
v___y_2591_ = v_quotient_2618_;
goto v___jp_2587_;
}
}
else
{
uint64_t v___x_2631_; 
v___x_2631_ = lean_uint64_add(v_quotient_2618_, v___x_2619_);
v___y_2588_ = v___y_2597_;
v___y_2589_ = v_position_2603_;
v___y_2590_ = v___y_2600_;
v___y_2591_ = v___x_2631_;
goto v___jp_2587_;
}
}
else
{
v___y_2588_ = v___y_2597_;
v___y_2589_ = v_position_2603_;
v___y_2590_ = v___y_2600_;
v___y_2591_ = v_quotient_2618_;
goto v___jp_2587_;
}
}
}
else
{
uint64_t v___x_2632_; 
v___x_2632_ = lean_unbox_uint64(v___y_2601_);
lean_dec(v___y_2601_);
v___y_2588_ = v___y_2597_;
v___y_2589_ = v_position_2603_;
v___y_2590_ = v___y_2600_;
v___y_2591_ = v___x_2632_;
goto v___jp_2587_;
}
}
else
{
uint64_t v___x_2633_; uint64_t v___x_2634_; uint64_t v___x_2635_; 
v___x_2633_ = lean_uint64_sub(v___x_2606_, v___y_2602_);
v___x_2634_ = lean_unbox_uint64(v___y_2601_);
lean_dec(v___y_2601_);
v___x_2635_ = lean_uint64_shift_left(v___x_2634_, v___x_2633_);
v___y_2588_ = v___y_2597_;
v___y_2589_ = v_position_2603_;
v___y_2590_ = v___y_2600_;
v___y_2591_ = v___x_2635_;
goto v___jp_2587_;
}
}
else
{
uint8_t v___x_2636_; 
v___x_2636_ = lean_uint64_dec_lt(v___y_2599_, v___y_2598_);
if (v___x_2636_ == 0)
{
uint64_t v___x_2637_; uint64_t v___x_2638_; uint64_t v___x_2639_; 
v___x_2637_ = lean_uint64_sub(v___y_2599_, v___y_2598_);
v___x_2638_ = lean_unbox_uint64(v___y_2601_);
lean_dec(v___y_2601_);
v___x_2639_ = lean_uint64_shift_left(v___x_2638_, v___x_2637_);
v___y_2096_ = v___y_2597_;
v___y_2097_ = v___y_2600_;
v___y_2098_ = v___x_2639_;
goto v___jp_2095_;
}
else
{
uint64_t v___x_2640_; uint8_t v___x_2641_; 
v___x_2640_ = lean_uint64_sub(v___y_2598_, v___y_2599_);
v___x_2641_ = lean_uint64_dec_eq(v___x_2640_, v___y_2597_);
if (v___x_2641_ == 0)
{
uint64_t v___x_2642_; uint8_t v___x_2643_; 
v___x_2642_ = 64ULL;
v___x_2643_ = lean_uint64_dec_lt(v___x_2640_, v___x_2642_);
if (v___x_2643_ == 0)
{
uint8_t v___x_2644_; 
v___x_2644_ = lean_uint64_dec_eq(v___x_2640_, v___x_2642_);
if (v___x_2644_ == 0)
{
lean_dec(v___y_2601_);
v___y_2096_ = v___y_2597_;
v___y_2097_ = v___y_2600_;
v___y_2098_ = v___y_2597_;
goto v___jp_2095_;
}
else
{
uint64_t v___x_2645_; uint64_t v___x_2646_; uint8_t v___x_2647_; 
v___x_2645_ = 9223372036854775808ULL;
v___x_2646_ = lean_unbox_uint64(v___y_2601_);
lean_dec(v___y_2601_);
v___x_2647_ = lean_uint64_dec_lt(v___x_2645_, v___x_2646_);
if (v___x_2647_ == 0)
{
v___y_2096_ = v___y_2597_;
v___y_2097_ = v___y_2600_;
v___y_2098_ = v___y_2597_;
goto v___jp_2095_;
}
else
{
uint64_t v___x_2648_; 
v___x_2648_ = 1ULL;
v___y_2096_ = v___y_2597_;
v___y_2097_ = v___y_2600_;
v___y_2098_ = v___x_2648_;
goto v___jp_2095_;
}
}
}
else
{
uint64_t v___x_2649_; uint64_t v_quotient_2650_; uint64_t v___x_2651_; uint64_t v___x_2652_; uint64_t v___x_2653_; uint64_t v___x_2654_; uint64_t v_remainder_2655_; uint64_t v___x_2656_; uint64_t v_half_2657_; uint8_t v___x_2658_; 
v___x_2649_ = lean_unbox_uint64(v___y_2601_);
v_quotient_2650_ = lean_uint64_shift_right(v___x_2649_, v___x_2640_);
v___x_2651_ = 1ULL;
v___x_2652_ = lean_uint64_shift_left(v___x_2651_, v___x_2640_);
v___x_2653_ = lean_uint64_sub(v___x_2652_, v___x_2651_);
v___x_2654_ = lean_unbox_uint64(v___y_2601_);
lean_dec(v___y_2601_);
v_remainder_2655_ = lean_uint64_land(v___x_2654_, v___x_2653_);
v___x_2656_ = lean_uint64_sub(v___x_2640_, v___x_2651_);
v_half_2657_ = lean_uint64_shift_left(v___x_2651_, v___x_2656_);
v___x_2658_ = lean_uint64_dec_lt(v_remainder_2655_, v_half_2657_);
if (v___x_2658_ == 0)
{
uint8_t v___x_2659_; 
v___x_2659_ = lean_uint64_dec_lt(v_half_2657_, v_remainder_2655_);
if (v___x_2659_ == 0)
{
uint64_t v___x_2660_; uint8_t v___x_2661_; 
v___x_2660_ = lean_uint64_land(v_quotient_2650_, v___x_2651_);
v___x_2661_ = lean_uint64_dec_eq(v___x_2660_, v___y_2597_);
if (v___x_2661_ == 0)
{
uint64_t v___x_2662_; 
v___x_2662_ = lean_uint64_add(v_quotient_2650_, v___x_2651_);
v___y_2096_ = v___y_2597_;
v___y_2097_ = v___y_2600_;
v___y_2098_ = v___x_2662_;
goto v___jp_2095_;
}
else
{
v___y_2096_ = v___y_2597_;
v___y_2097_ = v___y_2600_;
v___y_2098_ = v_quotient_2650_;
goto v___jp_2095_;
}
}
else
{
uint64_t v___x_2663_; 
v___x_2663_ = lean_uint64_add(v_quotient_2650_, v___x_2651_);
v___y_2096_ = v___y_2597_;
v___y_2097_ = v___y_2600_;
v___y_2098_ = v___x_2663_;
goto v___jp_2095_;
}
}
else
{
v___y_2096_ = v___y_2597_;
v___y_2097_ = v___y_2600_;
v___y_2098_ = v_quotient_2650_;
goto v___jp_2095_;
}
}
}
else
{
uint64_t v___x_2664_; 
v___x_2664_ = lean_unbox_uint64(v___y_2601_);
lean_dec(v___y_2601_);
v___y_2096_ = v___y_2597_;
v___y_2097_ = v___y_2600_;
v___y_2098_ = v___x_2664_;
goto v___jp_2095_;
}
}
}
}
v___jp_2665_:
{
uint64_t v___x_2673_; uint64_t v___x_2674_; uint8_t v___x_2675_; 
v___x_2673_ = 1ULL;
v___x_2674_ = lean_uint64_shift_right(v___y_2668_, v___x_2673_);
v___x_2675_ = lean_uint64_dec_eq(v___x_2674_, v___y_2666_);
if (v___x_2675_ == 0)
{
uint64_t v___x_2676_; 
v___x_2676_ = lean_uint64_add(v___y_2672_, v___x_2673_);
v___y_2597_ = v___y_2666_;
v___y_2598_ = v___y_2667_;
v___y_2599_ = v___y_2669_;
v___y_2600_ = v___y_2670_;
v___y_2601_ = v___y_2671_;
v___y_2602_ = v___x_2676_;
goto v___jp_2596_;
}
else
{
v___y_2597_ = v___y_2666_;
v___y_2598_ = v___y_2667_;
v___y_2599_ = v___y_2669_;
v___y_2600_ = v___y_2670_;
v___y_2601_ = v___y_2671_;
v___y_2602_ = v___y_2672_;
goto v___jp_2596_;
}
}
v___jp_2677_:
{
uint64_t v___x_2687_; uint8_t v___x_2688_; 
v___x_2687_ = lean_uint64_shift_right(v___y_2682_, v___y_2678_);
v___x_2688_ = lean_uint64_dec_eq(v___x_2687_, v___y_2679_);
if (v___x_2688_ == 0)
{
uint64_t v___x_2689_; 
v___x_2689_ = lean_uint64_add(v___y_2681_, v___y_2678_);
v___y_2666_ = v___y_2679_;
v___y_2667_ = v___y_2680_;
v___y_2668_ = v___y_2686_;
v___y_2669_ = v___y_2683_;
v___y_2670_ = v___y_2684_;
v___y_2671_ = v___y_2685_;
v___y_2672_ = v___x_2689_;
goto v___jp_2665_;
}
else
{
v___y_2666_ = v___y_2679_;
v___y_2667_ = v___y_2680_;
v___y_2668_ = v___y_2686_;
v___y_2669_ = v___y_2683_;
v___y_2670_ = v___y_2684_;
v___y_2671_ = v___y_2685_;
v___y_2672_ = v___y_2681_;
goto v___jp_2665_;
}
}
v___jp_2690_:
{
uint64_t v___x_2698_; uint64_t v___x_2699_; uint8_t v___x_2700_; 
v___x_2698_ = 2ULL;
v___x_2699_ = lean_uint64_shift_right(v___y_2694_, v___x_2698_);
v___x_2700_ = lean_uint64_dec_eq(v___x_2699_, v___y_2691_);
if (v___x_2700_ == 0)
{
v___y_2678_ = v___x_2698_;
v___y_2679_ = v___y_2691_;
v___y_2680_ = v___y_2692_;
v___y_2681_ = v___y_2697_;
v___y_2682_ = v___y_2694_;
v___y_2683_ = v___y_2693_;
v___y_2684_ = v___y_2695_;
v___y_2685_ = v___y_2696_;
v___y_2686_ = v___x_2699_;
goto v___jp_2677_;
}
else
{
v___y_2678_ = v___x_2698_;
v___y_2679_ = v___y_2691_;
v___y_2680_ = v___y_2692_;
v___y_2681_ = v___y_2697_;
v___y_2682_ = v___y_2694_;
v___y_2683_ = v___y_2693_;
v___y_2684_ = v___y_2695_;
v___y_2685_ = v___y_2696_;
v___y_2686_ = v___y_2694_;
goto v___jp_2677_;
}
}
v___jp_2701_:
{
uint64_t v___x_2711_; uint8_t v___x_2712_; 
v___x_2711_ = lean_uint64_shift_right(v___y_2706_, v___y_2703_);
v___x_2712_ = lean_uint64_dec_eq(v___x_2711_, v___y_2704_);
if (v___x_2712_ == 0)
{
uint64_t v___x_2713_; 
v___x_2713_ = lean_uint64_add(v___y_2702_, v___y_2703_);
v___y_2691_ = v___y_2704_;
v___y_2692_ = v___y_2705_;
v___y_2693_ = v___y_2707_;
v___y_2694_ = v___y_2710_;
v___y_2695_ = v___y_2708_;
v___y_2696_ = v___y_2709_;
v___y_2697_ = v___x_2713_;
goto v___jp_2690_;
}
else
{
v___y_2691_ = v___y_2704_;
v___y_2692_ = v___y_2705_;
v___y_2693_ = v___y_2707_;
v___y_2694_ = v___y_2710_;
v___y_2695_ = v___y_2708_;
v___y_2696_ = v___y_2709_;
v___y_2697_ = v___y_2702_;
goto v___jp_2690_;
}
}
v___jp_2714_:
{
uint64_t v___x_2722_; uint64_t v___x_2723_; uint8_t v___x_2724_; 
v___x_2722_ = 4ULL;
v___x_2723_ = lean_uint64_shift_right(v___y_2717_, v___x_2722_);
v___x_2724_ = lean_uint64_dec_eq(v___x_2723_, v___y_2715_);
if (v___x_2724_ == 0)
{
v___y_2702_ = v___y_2721_;
v___y_2703_ = v___x_2722_;
v___y_2704_ = v___y_2715_;
v___y_2705_ = v___y_2716_;
v___y_2706_ = v___y_2717_;
v___y_2707_ = v___y_2718_;
v___y_2708_ = v___y_2719_;
v___y_2709_ = v___y_2720_;
v___y_2710_ = v___x_2723_;
goto v___jp_2701_;
}
else
{
v___y_2702_ = v___y_2721_;
v___y_2703_ = v___x_2722_;
v___y_2704_ = v___y_2715_;
v___y_2705_ = v___y_2716_;
v___y_2706_ = v___y_2717_;
v___y_2707_ = v___y_2718_;
v___y_2708_ = v___y_2719_;
v___y_2709_ = v___y_2720_;
v___y_2710_ = v___y_2717_;
goto v___jp_2701_;
}
}
v___jp_2725_:
{
uint64_t v___x_2735_; uint8_t v___x_2736_; 
v___x_2735_ = lean_uint64_shift_right(v___y_2731_, v___y_2726_);
v___x_2736_ = lean_uint64_dec_eq(v___x_2735_, v___y_2728_);
if (v___x_2736_ == 0)
{
uint64_t v___x_2737_; 
v___x_2737_ = lean_uint64_add(v___y_2727_, v___y_2726_);
v___y_2715_ = v___y_2728_;
v___y_2716_ = v___y_2729_;
v___y_2717_ = v___y_2734_;
v___y_2718_ = v___y_2730_;
v___y_2719_ = v___y_2732_;
v___y_2720_ = v___y_2733_;
v___y_2721_ = v___x_2737_;
goto v___jp_2714_;
}
else
{
v___y_2715_ = v___y_2728_;
v___y_2716_ = v___y_2729_;
v___y_2717_ = v___y_2734_;
v___y_2718_ = v___y_2730_;
v___y_2719_ = v___y_2732_;
v___y_2720_ = v___y_2733_;
v___y_2721_ = v___y_2727_;
goto v___jp_2714_;
}
}
v___jp_2738_:
{
uint64_t v___x_2746_; uint64_t v___x_2747_; uint8_t v___x_2748_; 
v___x_2746_ = 8ULL;
v___x_2747_ = lean_uint64_shift_right(v___y_2742_, v___x_2746_);
v___x_2748_ = lean_uint64_dec_eq(v___x_2747_, v___y_2739_);
if (v___x_2748_ == 0)
{
v___y_2726_ = v___x_2746_;
v___y_2727_ = v___y_2745_;
v___y_2728_ = v___y_2739_;
v___y_2729_ = v___y_2740_;
v___y_2730_ = v___y_2741_;
v___y_2731_ = v___y_2742_;
v___y_2732_ = v___y_2743_;
v___y_2733_ = v___y_2744_;
v___y_2734_ = v___x_2747_;
goto v___jp_2725_;
}
else
{
v___y_2726_ = v___x_2746_;
v___y_2727_ = v___y_2745_;
v___y_2728_ = v___y_2739_;
v___y_2729_ = v___y_2740_;
v___y_2730_ = v___y_2741_;
v___y_2731_ = v___y_2742_;
v___y_2732_ = v___y_2743_;
v___y_2733_ = v___y_2744_;
v___y_2734_ = v___y_2742_;
goto v___jp_2725_;
}
}
v___jp_2749_:
{
uint64_t v___x_2759_; uint8_t v___x_2760_; 
v___x_2759_ = lean_uint64_shift_right(v___y_2752_, v___y_2757_);
v___x_2760_ = lean_uint64_dec_eq(v___x_2759_, v___y_2750_);
if (v___x_2760_ == 0)
{
uint64_t v___x_2761_; 
v___x_2761_ = lean_uint64_add(v___y_2756_, v___y_2757_);
v___y_2739_ = v___y_2750_;
v___y_2740_ = v___y_2751_;
v___y_2741_ = v___y_2753_;
v___y_2742_ = v___y_2758_;
v___y_2743_ = v___y_2754_;
v___y_2744_ = v___y_2755_;
v___y_2745_ = v___x_2761_;
goto v___jp_2738_;
}
else
{
v___y_2739_ = v___y_2750_;
v___y_2740_ = v___y_2751_;
v___y_2741_ = v___y_2753_;
v___y_2742_ = v___y_2758_;
v___y_2743_ = v___y_2754_;
v___y_2744_ = v___y_2755_;
v___y_2745_ = v___y_2756_;
goto v___jp_2738_;
}
}
v___jp_2762_:
{
uint64_t v___x_2770_; uint64_t v___x_2771_; uint8_t v___x_2772_; 
v___x_2770_ = 16ULL;
v___x_2771_ = lean_uint64_shift_right(v___y_2765_, v___x_2770_);
v___x_2772_ = lean_uint64_dec_eq(v___x_2771_, v___y_2763_);
if (v___x_2772_ == 0)
{
v___y_2750_ = v___y_2763_;
v___y_2751_ = v___y_2764_;
v___y_2752_ = v___y_2765_;
v___y_2753_ = v___y_2766_;
v___y_2754_ = v___y_2767_;
v___y_2755_ = v___y_2768_;
v___y_2756_ = v___y_2769_;
v___y_2757_ = v___x_2770_;
v___y_2758_ = v___x_2771_;
goto v___jp_2749_;
}
else
{
v___y_2750_ = v___y_2763_;
v___y_2751_ = v___y_2764_;
v___y_2752_ = v___y_2765_;
v___y_2753_ = v___y_2766_;
v___y_2754_ = v___y_2767_;
v___y_2755_ = v___y_2768_;
v___y_2756_ = v___y_2769_;
v___y_2757_ = v___x_2770_;
v___y_2758_ = v___y_2765_;
goto v___jp_2749_;
}
}
v___jp_2773_:
{
uint64_t v___x_2781_; uint64_t v___x_2782_; uint8_t v___x_2783_; 
v___x_2781_ = lean_unbox_uint64(v___y_2779_);
v___x_2782_ = lean_uint64_shift_right(v___x_2781_, v___y_2776_);
v___x_2783_ = lean_uint64_dec_eq(v___x_2782_, v___y_2774_);
if (v___x_2783_ == 0)
{
v___y_2763_ = v___y_2774_;
v___y_2764_ = v___y_2775_;
v___y_2765_ = v___y_2780_;
v___y_2766_ = v___y_2777_;
v___y_2767_ = v___y_2778_;
v___y_2768_ = v___y_2779_;
v___y_2769_ = v___y_2776_;
goto v___jp_2762_;
}
else
{
v___y_2763_ = v___y_2774_;
v___y_2764_ = v___y_2775_;
v___y_2765_ = v___y_2780_;
v___y_2766_ = v___y_2777_;
v___y_2767_ = v___y_2778_;
v___y_2768_ = v___y_2779_;
v___y_2769_ = v___y_2774_;
goto v___jp_2762_;
}
}
v___jp_2784_:
{
uint64_t v___x_2788_; uint64_t v___x_2789_; uint8_t v___x_2790_; 
v___x_2788_ = 0ULL;
v___x_2789_ = lean_unbox_uint64(v_snd_2787_);
v___x_2790_ = lean_uint64_dec_eq(v___x_2789_, v___x_2788_);
if (v___x_2790_ == 0)
{
uint64_t v___x_2791_; uint64_t v___x_2792_; uint64_t v___x_2793_; uint64_t v___x_2794_; uint64_t v___x_2795_; uint8_t v___x_2796_; 
v___x_2791_ = 149ULL;
v___x_2792_ = lean_uint64_add(v___y_2785_, v___x_2791_);
v___x_2793_ = 32ULL;
v___x_2794_ = lean_unbox_uint64(v_snd_2787_);
v___x_2795_ = lean_uint64_shift_right(v___x_2794_, v___x_2793_);
v___x_2796_ = lean_uint64_dec_eq(v___x_2795_, v___x_2788_);
if (v___x_2796_ == 0)
{
v___y_2774_ = v___x_2788_;
v___y_2775_ = v___x_2791_;
v___y_2776_ = v___x_2793_;
v___y_2777_ = v___x_2792_;
v___y_2778_ = v_fst_2786_;
v___y_2779_ = v_snd_2787_;
v___y_2780_ = v___x_2795_;
goto v___jp_2773_;
}
else
{
uint64_t v___x_2797_; 
v___x_2797_ = lean_unbox_uint64(v_snd_2787_);
v___y_2774_ = v___x_2788_;
v___y_2775_ = v___x_2791_;
v___y_2776_ = v___x_2793_;
v___y_2777_ = v___x_2792_;
v___y_2778_ = v_fst_2786_;
v___y_2779_ = v_snd_2787_;
v___y_2780_ = v___x_2797_;
goto v___jp_2773_;
}
}
else
{
uint8_t v___x_2798_; 
lean_dec(v_snd_2787_);
v___x_2798_ = lean_unbox(v_fst_2786_);
lean_dec(v_fst_2786_);
if (v___x_2798_ == 0)
{
uint32_t v___x_2799_; 
v___x_2799_ = 0;
return v___x_2799_;
}
else
{
uint32_t v___x_2800_; 
v___x_2800_ = 2147483648;
return v___x_2800_;
}
}
}
v___jp_2801_:
{
uint8_t v___x_2808_; 
v___x_2808_ = lean_uint64_dec_eq(v___y_2806_, v___y_2802_);
if (v___x_2808_ == 0)
{
uint8_t v___x_2809_; 
v___x_2809_ = lean_uint64_dec_lt(v___y_2806_, v___y_2802_);
if (v___x_2809_ == 0)
{
uint64_t v___x_2810_; lean_object* v___x_2811_; lean_object* v___x_2812_; 
v___x_2810_ = lean_uint64_sub(v___y_2806_, v___y_2802_);
v___x_2811_ = lean_box(v___y_2805_);
v___x_2812_ = lean_box_uint64(v___x_2810_);
v___y_2785_ = v___y_2803_;
v_fst_2786_ = v___x_2811_;
v_snd_2787_ = v___x_2812_;
goto v___jp_2784_;
}
else
{
uint64_t v___x_2813_; lean_object* v___x_2814_; lean_object* v___x_2815_; 
v___x_2813_ = lean_uint64_sub(v___y_2802_, v___y_2806_);
v___x_2814_ = lean_box(v___y_2804_);
v___x_2815_ = lean_box_uint64(v___x_2813_);
v___y_2785_ = v___y_2803_;
v_fst_2786_ = v___x_2814_;
v_snd_2787_ = v___x_2815_;
goto v___jp_2784_;
}
}
else
{
lean_object* v___x_2816_; lean_object* v___x_2817_; 
v___x_2816_ = lean_box(v___y_2807_);
v___x_2817_ = ((lean_object*)(lp_competition_Submission_TunedAdd_core___boxed__const__1));
v___y_2785_ = v___y_2803_;
v_fst_2786_ = v___x_2816_;
v_snd_2787_ = v___x_2817_;
goto v___jp_2784_;
}
}
v___jp_2818_:
{
if (v___y_2824_ == 0)
{
v___y_2802_ = v___y_2819_;
v___y_2803_ = v___y_2820_;
v___y_2804_ = v___y_2821_;
v___y_2805_ = v___y_2822_;
v___y_2806_ = v___y_2823_;
v___y_2807_ = v___y_2824_;
goto v___jp_2801_;
}
else
{
uint64_t v___x_2825_; lean_object* v___x_2826_; lean_object* v___x_2827_; 
v___x_2825_ = lean_uint64_add(v___y_2823_, v___y_2819_);
v___x_2826_ = lean_box(v___y_2822_);
v___x_2827_ = lean_box_uint64(v___x_2825_);
v___y_2785_ = v___y_2820_;
v_fst_2786_ = v___x_2826_;
v_snd_2787_ = v___x_2827_;
goto v___jp_2784_;
}
}
v___jp_2828_:
{
uint8_t v___x_2835_; 
v___x_2835_ = lean_uint64_dec_le(v___y_2830_, v___y_2834_);
if (v___x_2835_ == 0)
{
uint64_t v_shift_2836_; uint64_t v___x_2837_; uint8_t v___x_2838_; 
v_shift_2836_ = lean_uint64_sub(v___y_2830_, v___y_2834_);
v___x_2837_ = 39ULL;
v___x_2838_ = lean_uint64_dec_le(v_shift_2836_, v___x_2837_);
if (v___x_2838_ == 0)
{
return v_a_2041_;
}
else
{
uint64_t v___x_2839_; 
v___x_2839_ = lean_uint64_shift_left(v___y_2833_, v_shift_2836_);
if (v___y_2832_ == 0)
{
if (v___y_2831_ == 0)
{
v___y_2536_ = v___y_2834_;
v___y_2537_ = v___y_2829_;
v___y_2538_ = v___x_2839_;
v___y_2539_ = v___y_2831_;
v___y_2540_ = v___y_2832_;
v___y_2541_ = v___x_2838_;
goto v___jp_2535_;
}
else
{
v___y_2519_ = v___y_2834_;
v___y_2520_ = v___y_2829_;
v___y_2521_ = v___y_2831_;
v___y_2522_ = v___x_2839_;
v___y_2523_ = v___y_2832_;
v___y_2524_ = v___y_2832_;
goto v___jp_2518_;
}
}
else
{
v___y_2536_ = v___y_2834_;
v___y_2537_ = v___y_2829_;
v___y_2538_ = v___x_2839_;
v___y_2539_ = v___y_2831_;
v___y_2540_ = v___y_2832_;
v___y_2541_ = v___y_2831_;
goto v___jp_2535_;
}
}
}
else
{
uint64_t v_shift_2840_; uint64_t v___x_2841_; uint8_t v___x_2842_; 
v_shift_2840_ = lean_uint64_sub(v___y_2834_, v___y_2830_);
v___x_2841_ = 39ULL;
v___x_2842_ = lean_uint64_dec_le(v_shift_2840_, v___x_2841_);
if (v___x_2842_ == 0)
{
return v_b_2042_;
}
else
{
uint64_t v___x_2843_; 
v___x_2843_ = lean_uint64_shift_left(v___y_2829_, v_shift_2840_);
if (v___y_2832_ == 0)
{
if (v___y_2831_ == 0)
{
v___y_2819_ = v___x_2843_;
v___y_2820_ = v___y_2830_;
v___y_2821_ = v___y_2831_;
v___y_2822_ = v___y_2832_;
v___y_2823_ = v___y_2833_;
v___y_2824_ = v___x_2842_;
goto v___jp_2818_;
}
else
{
v___y_2802_ = v___x_2843_;
v___y_2803_ = v___y_2830_;
v___y_2804_ = v___y_2831_;
v___y_2805_ = v___y_2832_;
v___y_2806_ = v___y_2833_;
v___y_2807_ = v___y_2832_;
goto v___jp_2801_;
}
}
else
{
v___y_2819_ = v___x_2843_;
v___y_2820_ = v___y_2830_;
v___y_2821_ = v___y_2831_;
v___y_2822_ = v___y_2832_;
v___y_2823_ = v___y_2833_;
v___y_2824_ = v___y_2831_;
goto v___jp_2818_;
}
}
}
}
v___jp_2844_:
{
uint64_t v___x_2851_; uint64_t v___x_2852_; uint8_t v___x_2853_; 
v___x_2851_ = lean_uint32_to_uint64(v___y_2845_);
v___x_2852_ = 0ULL;
v___x_2853_ = lean_uint64_dec_eq(v___x_2851_, v___x_2852_);
if (v___x_2853_ == 0)
{
uint64_t v___x_2854_; uint64_t v___x_2855_; 
v___x_2854_ = 1ULL;
v___x_2855_ = lean_uint64_sub(v___x_2851_, v___x_2854_);
v___y_2829_ = v___y_2846_;
v___y_2830_ = v___y_2850_;
v___y_2831_ = v___y_2847_;
v___y_2832_ = v___y_2848_;
v___y_2833_ = v___y_2849_;
v___y_2834_ = v___x_2855_;
goto v___jp_2828_;
}
else
{
v___y_2829_ = v___y_2846_;
v___y_2830_ = v___y_2850_;
v___y_2831_ = v___y_2847_;
v___y_2832_ = v___y_2848_;
v___y_2833_ = v___y_2849_;
v___y_2834_ = v___x_2852_;
goto v___jp_2828_;
}
}
v___jp_2856_:
{
uint32_t v___x_2860_; uint32_t v___x_2861_; uint32_t v___x_2862_; uint32_t v___x_2863_; uint32_t v___x_2864_; uint32_t v___x_2865_; 
v___x_2860_ = lean_uint32_land(v___y_2858_, v___x_2261_);
v___x_2861_ = lean_uint32_shift_left(v___x_2860_, v___x_2259_);
v___x_2862_ = lean_uint32_lor(v___y_2859_, v___x_2861_);
v___x_2863_ = 8388607;
v___x_2864_ = lean_uint32_land(v___y_2857_, v___x_2863_);
v___x_2865_ = lean_uint32_lor(v___x_2862_, v___x_2864_);
return v___x_2865_;
}
v___jp_2866_:
{
uint8_t v___x_2870_; 
v___x_2870_ = lean_unbox(v___y_2867_);
lean_dec(v___y_2867_);
if (v___x_2870_ == 0)
{
uint32_t v___x_2871_; 
v___x_2871_ = 0;
v___y_2857_ = v___y_2869_;
v___y_2858_ = v___y_2868_;
v___y_2859_ = v___x_2871_;
goto v___jp_2856_;
}
else
{
uint32_t v___x_2872_; 
v___x_2872_ = 2147483648;
v___y_2857_ = v___y_2869_;
v___y_2858_ = v___y_2868_;
v___y_2859_ = v___x_2872_;
goto v___jp_2856_;
}
}
v___jp_2873_:
{
uint64_t v___x_2878_; uint64_t v_encodedExponent_2879_; uint32_t v___x_2880_; uint64_t v___x_2881_; uint8_t v___x_2882_; 
v___x_2878_ = 171ULL;
v_encodedExponent_2879_ = lean_uint64_sub(v___y_2874_, v___x_2878_);
v___x_2880_ = lean_uint64_to_uint32(v_encodedExponent_2879_);
v___x_2881_ = 8388608ULL;
v___x_2882_ = lean_uint64_dec_lt(v___y_2877_, v___x_2881_);
if (v___x_2882_ == 0)
{
uint64_t v___x_2883_; uint32_t v___x_2884_; 
v___x_2883_ = lean_uint64_sub(v___y_2877_, v___x_2881_);
v___x_2884_ = lean_uint64_to_uint32(v___x_2883_);
v___y_2867_ = v___y_2875_;
v___y_2868_ = v___x_2880_;
v___y_2869_ = v___x_2884_;
goto v___jp_2866_;
}
else
{
uint32_t v___x_2885_; 
v___x_2885_ = lean_uint64_to_uint32(v___y_2876_);
v___y_2867_ = v___y_2875_;
v___y_2868_ = v___x_2880_;
v___y_2869_ = v___x_2885_;
goto v___jp_2866_;
}
}
v___jp_2886_:
{
uint64_t v___x_2892_; uint8_t v___x_2893_; 
v___x_2892_ = 425ULL;
v___x_2893_ = lean_uint64_dec_lt(v___x_2892_, v___y_2891_);
if (v___x_2893_ == 0)
{
if (v___y_2887_ == 0)
{
v___y_2874_ = v___y_2891_;
v___y_2875_ = v___y_2889_;
v___y_2876_ = v___y_2890_;
v___y_2877_ = v___y_2888_;
goto v___jp_2873_;
}
else
{
uint64_t v___x_2894_; 
v___x_2894_ = 8388608ULL;
v___y_2874_ = v___y_2891_;
v___y_2875_ = v___y_2889_;
v___y_2876_ = v___y_2890_;
v___y_2877_ = v___x_2894_;
goto v___jp_2873_;
}
}
else
{
uint8_t v___x_2895_; 
v___x_2895_ = lean_unbox(v___y_2889_);
lean_dec(v___y_2889_);
if (v___x_2895_ == 0)
{
uint32_t v___x_2896_; 
v___x_2896_ = 2139095040;
return v___x_2896_;
}
else
{
uint32_t v___x_2897_; 
v___x_2897_ = 4286578688;
return v___x_2897_;
}
}
}
v___jp_2898_:
{
uint64_t v___x_2903_; uint8_t v_carry_2904_; 
v___x_2903_ = 16777216ULL;
v_carry_2904_ = lean_uint64_dec_eq(v___y_2902_, v___x_2903_);
if (v_carry_2904_ == 0)
{
v___y_2887_ = v_carry_2904_;
v___y_2888_ = v___y_2902_;
v___y_2889_ = v___y_2899_;
v___y_2890_ = v___y_2901_;
v___y_2891_ = v___y_2900_;
goto v___jp_2886_;
}
else
{
uint64_t v___x_2905_; uint64_t v___x_2906_; 
v___x_2905_ = 1ULL;
v___x_2906_ = lean_uint64_add(v___y_2900_, v___x_2905_);
v___y_2887_ = v_carry_2904_;
v___y_2888_ = v___y_2902_;
v___y_2889_ = v___y_2899_;
v___y_2890_ = v___y_2901_;
v___y_2891_ = v___x_2906_;
goto v___jp_2886_;
}
}
v___jp_2907_:
{
uint64_t v_position_2914_; uint64_t v___x_2915_; uint8_t v___x_2916_; 
v_position_2914_ = lean_uint64_add(v___y_2913_, v___y_2912_);
v___x_2915_ = 172ULL;
v___x_2916_ = lean_uint64_dec_lt(v_position_2914_, v___x_2915_);
if (v___x_2916_ == 0)
{
uint64_t v___x_2917_; uint8_t v___x_2918_; 
v___x_2917_ = 23ULL;
v___x_2918_ = lean_uint64_dec_lt(v___y_2913_, v___x_2917_);
if (v___x_2918_ == 0)
{
uint64_t v___x_2919_; uint8_t v___x_2920_; 
v___x_2919_ = lean_uint64_sub(v___y_2913_, v___x_2917_);
v___x_2920_ = lean_uint64_dec_eq(v___x_2919_, v___y_2910_);
if (v___x_2920_ == 0)
{
uint64_t v___x_2921_; uint8_t v___x_2922_; 
v___x_2921_ = 64ULL;
v___x_2922_ = lean_uint64_dec_lt(v___x_2919_, v___x_2921_);
if (v___x_2922_ == 0)
{
uint8_t v___x_2923_; 
v___x_2923_ = lean_uint64_dec_eq(v___x_2919_, v___x_2921_);
if (v___x_2923_ == 0)
{
lean_dec(v___y_2909_);
v___y_2899_ = v___y_2908_;
v___y_2900_ = v_position_2914_;
v___y_2901_ = v___y_2910_;
v___y_2902_ = v___y_2910_;
goto v___jp_2898_;
}
else
{
uint64_t v___x_2924_; uint64_t v___x_2925_; uint8_t v___x_2926_; 
v___x_2924_ = 9223372036854775808ULL;
v___x_2925_ = lean_unbox_uint64(v___y_2909_);
lean_dec(v___y_2909_);
v___x_2926_ = lean_uint64_dec_lt(v___x_2924_, v___x_2925_);
if (v___x_2926_ == 0)
{
v___y_2899_ = v___y_2908_;
v___y_2900_ = v_position_2914_;
v___y_2901_ = v___y_2910_;
v___y_2902_ = v___y_2910_;
goto v___jp_2898_;
}
else
{
uint64_t v___x_2927_; 
v___x_2927_ = 1ULL;
v___y_2899_ = v___y_2908_;
v___y_2900_ = v_position_2914_;
v___y_2901_ = v___y_2910_;
v___y_2902_ = v___x_2927_;
goto v___jp_2898_;
}
}
}
else
{
uint64_t v___x_2928_; uint64_t v_quotient_2929_; uint64_t v___x_2930_; uint64_t v___x_2931_; uint64_t v___x_2932_; uint64_t v___x_2933_; uint64_t v_remainder_2934_; uint64_t v___x_2935_; uint64_t v_half_2936_; uint8_t v___x_2937_; 
v___x_2928_ = lean_unbox_uint64(v___y_2909_);
v_quotient_2929_ = lean_uint64_shift_right(v___x_2928_, v___x_2919_);
v___x_2930_ = 1ULL;
v___x_2931_ = lean_uint64_shift_left(v___x_2930_, v___x_2919_);
v___x_2932_ = lean_uint64_sub(v___x_2931_, v___x_2930_);
v___x_2933_ = lean_unbox_uint64(v___y_2909_);
lean_dec(v___y_2909_);
v_remainder_2934_ = lean_uint64_land(v___x_2933_, v___x_2932_);
v___x_2935_ = lean_uint64_sub(v___x_2919_, v___x_2930_);
v_half_2936_ = lean_uint64_shift_left(v___x_2930_, v___x_2935_);
v___x_2937_ = lean_uint64_dec_lt(v_remainder_2934_, v_half_2936_);
if (v___x_2937_ == 0)
{
uint8_t v___x_2938_; 
v___x_2938_ = lean_uint64_dec_lt(v_half_2936_, v_remainder_2934_);
if (v___x_2938_ == 0)
{
uint64_t v___x_2939_; uint8_t v___x_2940_; 
v___x_2939_ = lean_uint64_land(v_quotient_2929_, v___x_2930_);
v___x_2940_ = lean_uint64_dec_eq(v___x_2939_, v___y_2910_);
if (v___x_2940_ == 0)
{
uint64_t v___x_2941_; 
v___x_2941_ = lean_uint64_add(v_quotient_2929_, v___x_2930_);
v___y_2899_ = v___y_2908_;
v___y_2900_ = v_position_2914_;
v___y_2901_ = v___y_2910_;
v___y_2902_ = v___x_2941_;
goto v___jp_2898_;
}
else
{
v___y_2899_ = v___y_2908_;
v___y_2900_ = v_position_2914_;
v___y_2901_ = v___y_2910_;
v___y_2902_ = v_quotient_2929_;
goto v___jp_2898_;
}
}
else
{
uint64_t v___x_2942_; 
v___x_2942_ = lean_uint64_add(v_quotient_2929_, v___x_2930_);
v___y_2899_ = v___y_2908_;
v___y_2900_ = v_position_2914_;
v___y_2901_ = v___y_2910_;
v___y_2902_ = v___x_2942_;
goto v___jp_2898_;
}
}
else
{
v___y_2899_ = v___y_2908_;
v___y_2900_ = v_position_2914_;
v___y_2901_ = v___y_2910_;
v___y_2902_ = v_quotient_2929_;
goto v___jp_2898_;
}
}
}
else
{
uint64_t v___x_2943_; 
v___x_2943_ = lean_unbox_uint64(v___y_2909_);
lean_dec(v___y_2909_);
v___y_2899_ = v___y_2908_;
v___y_2900_ = v_position_2914_;
v___y_2901_ = v___y_2910_;
v___y_2902_ = v___x_2943_;
goto v___jp_2898_;
}
}
else
{
uint64_t v___x_2944_; uint64_t v___x_2945_; uint64_t v___x_2946_; 
v___x_2944_ = lean_uint64_sub(v___x_2917_, v___y_2913_);
v___x_2945_ = lean_unbox_uint64(v___y_2909_);
lean_dec(v___y_2909_);
v___x_2946_ = lean_uint64_shift_left(v___x_2945_, v___x_2944_);
v___y_2899_ = v___y_2908_;
v___y_2900_ = v_position_2914_;
v___y_2901_ = v___y_2910_;
v___y_2902_ = v___x_2946_;
goto v___jp_2898_;
}
}
else
{
uint8_t v___x_2947_; 
v___x_2947_ = lean_uint64_dec_lt(v___y_2912_, v___y_2911_);
if (v___x_2947_ == 0)
{
uint64_t v___x_2948_; uint64_t v___x_2949_; uint64_t v___x_2950_; 
v___x_2948_ = lean_uint64_sub(v___y_2912_, v___y_2911_);
v___x_2949_ = lean_unbox_uint64(v___y_2909_);
lean_dec(v___y_2909_);
v___x_2950_ = lean_uint64_shift_left(v___x_2949_, v___x_2948_);
v___y_2159_ = v___y_2908_;
v___y_2160_ = v___y_2910_;
v___y_2161_ = v___x_2950_;
goto v___jp_2158_;
}
else
{
uint64_t v___x_2951_; uint8_t v___x_2952_; 
v___x_2951_ = lean_uint64_sub(v___y_2911_, v___y_2912_);
v___x_2952_ = lean_uint64_dec_eq(v___x_2951_, v___y_2910_);
if (v___x_2952_ == 0)
{
uint64_t v___x_2953_; uint8_t v___x_2954_; 
v___x_2953_ = 64ULL;
v___x_2954_ = lean_uint64_dec_lt(v___x_2951_, v___x_2953_);
if (v___x_2954_ == 0)
{
uint8_t v___x_2955_; 
v___x_2955_ = lean_uint64_dec_eq(v___x_2951_, v___x_2953_);
if (v___x_2955_ == 0)
{
lean_dec(v___y_2909_);
v___y_2159_ = v___y_2908_;
v___y_2160_ = v___y_2910_;
v___y_2161_ = v___y_2910_;
goto v___jp_2158_;
}
else
{
uint64_t v___x_2956_; uint64_t v___x_2957_; uint8_t v___x_2958_; 
v___x_2956_ = 9223372036854775808ULL;
v___x_2957_ = lean_unbox_uint64(v___y_2909_);
lean_dec(v___y_2909_);
v___x_2958_ = lean_uint64_dec_lt(v___x_2956_, v___x_2957_);
if (v___x_2958_ == 0)
{
v___y_2159_ = v___y_2908_;
v___y_2160_ = v___y_2910_;
v___y_2161_ = v___y_2910_;
goto v___jp_2158_;
}
else
{
uint64_t v___x_2959_; 
v___x_2959_ = 1ULL;
v___y_2159_ = v___y_2908_;
v___y_2160_ = v___y_2910_;
v___y_2161_ = v___x_2959_;
goto v___jp_2158_;
}
}
}
else
{
uint64_t v___x_2960_; uint64_t v_quotient_2961_; uint64_t v___x_2962_; uint64_t v___x_2963_; uint64_t v___x_2964_; uint64_t v___x_2965_; uint64_t v_remainder_2966_; uint64_t v___x_2967_; uint64_t v_half_2968_; uint8_t v___x_2969_; 
v___x_2960_ = lean_unbox_uint64(v___y_2909_);
v_quotient_2961_ = lean_uint64_shift_right(v___x_2960_, v___x_2951_);
v___x_2962_ = 1ULL;
v___x_2963_ = lean_uint64_shift_left(v___x_2962_, v___x_2951_);
v___x_2964_ = lean_uint64_sub(v___x_2963_, v___x_2962_);
v___x_2965_ = lean_unbox_uint64(v___y_2909_);
lean_dec(v___y_2909_);
v_remainder_2966_ = lean_uint64_land(v___x_2965_, v___x_2964_);
v___x_2967_ = lean_uint64_sub(v___x_2951_, v___x_2962_);
v_half_2968_ = lean_uint64_shift_left(v___x_2962_, v___x_2967_);
v___x_2969_ = lean_uint64_dec_lt(v_remainder_2966_, v_half_2968_);
if (v___x_2969_ == 0)
{
uint8_t v___x_2970_; 
v___x_2970_ = lean_uint64_dec_lt(v_half_2968_, v_remainder_2966_);
if (v___x_2970_ == 0)
{
uint64_t v___x_2971_; uint8_t v___x_2972_; 
v___x_2971_ = lean_uint64_land(v_quotient_2961_, v___x_2962_);
v___x_2972_ = lean_uint64_dec_eq(v___x_2971_, v___y_2910_);
if (v___x_2972_ == 0)
{
uint64_t v___x_2973_; 
v___x_2973_ = lean_uint64_add(v_quotient_2961_, v___x_2962_);
v___y_2159_ = v___y_2908_;
v___y_2160_ = v___y_2910_;
v___y_2161_ = v___x_2973_;
goto v___jp_2158_;
}
else
{
v___y_2159_ = v___y_2908_;
v___y_2160_ = v___y_2910_;
v___y_2161_ = v_quotient_2961_;
goto v___jp_2158_;
}
}
else
{
uint64_t v___x_2974_; 
v___x_2974_ = lean_uint64_add(v_quotient_2961_, v___x_2962_);
v___y_2159_ = v___y_2908_;
v___y_2160_ = v___y_2910_;
v___y_2161_ = v___x_2974_;
goto v___jp_2158_;
}
}
else
{
v___y_2159_ = v___y_2908_;
v___y_2160_ = v___y_2910_;
v___y_2161_ = v_quotient_2961_;
goto v___jp_2158_;
}
}
}
else
{
uint64_t v___x_2975_; 
v___x_2975_ = lean_unbox_uint64(v___y_2909_);
lean_dec(v___y_2909_);
v___y_2159_ = v___y_2908_;
v___y_2160_ = v___y_2910_;
v___y_2161_ = v___x_2975_;
goto v___jp_2158_;
}
}
}
}
v___jp_2976_:
{
uint64_t v___x_2984_; uint64_t v___x_2985_; uint8_t v___x_2986_; 
v___x_2984_ = 1ULL;
v___x_2985_ = lean_uint64_shift_right(v___y_2981_, v___x_2984_);
v___x_2986_ = lean_uint64_dec_eq(v___x_2985_, v___y_2979_);
if (v___x_2986_ == 0)
{
uint64_t v___x_2987_; 
v___x_2987_ = lean_uint64_add(v___y_2983_, v___x_2984_);
v___y_2908_ = v___y_2977_;
v___y_2909_ = v___y_2978_;
v___y_2910_ = v___y_2979_;
v___y_2911_ = v___y_2980_;
v___y_2912_ = v___y_2982_;
v___y_2913_ = v___x_2987_;
goto v___jp_2907_;
}
else
{
v___y_2908_ = v___y_2977_;
v___y_2909_ = v___y_2978_;
v___y_2910_ = v___y_2979_;
v___y_2911_ = v___y_2980_;
v___y_2912_ = v___y_2982_;
v___y_2913_ = v___y_2983_;
goto v___jp_2907_;
}
}
v___jp_2988_:
{
uint64_t v___x_2998_; uint8_t v___x_2999_; 
v___x_2998_ = lean_uint64_shift_right(v___y_2989_, v___y_2995_);
v___x_2999_ = lean_uint64_dec_eq(v___x_2998_, v___y_2993_);
if (v___x_2999_ == 0)
{
uint64_t v___x_3000_; 
v___x_3000_ = lean_uint64_add(v___y_2992_, v___y_2995_);
v___y_2977_ = v___y_2990_;
v___y_2978_ = v___y_2991_;
v___y_2979_ = v___y_2993_;
v___y_2980_ = v___y_2994_;
v___y_2981_ = v___y_2997_;
v___y_2982_ = v___y_2996_;
v___y_2983_ = v___x_3000_;
goto v___jp_2976_;
}
else
{
v___y_2977_ = v___y_2990_;
v___y_2978_ = v___y_2991_;
v___y_2979_ = v___y_2993_;
v___y_2980_ = v___y_2994_;
v___y_2981_ = v___y_2997_;
v___y_2982_ = v___y_2996_;
v___y_2983_ = v___y_2992_;
goto v___jp_2976_;
}
}
v___jp_3001_:
{
uint64_t v___x_3009_; uint64_t v___x_3010_; uint8_t v___x_3011_; 
v___x_3009_ = 2ULL;
v___x_3010_ = lean_uint64_shift_right(v___y_3002_, v___x_3009_);
v___x_3011_ = lean_uint64_dec_eq(v___x_3010_, v___y_3005_);
if (v___x_3011_ == 0)
{
v___y_2989_ = v___y_3002_;
v___y_2990_ = v___y_3003_;
v___y_2991_ = v___y_3004_;
v___y_2992_ = v___y_3008_;
v___y_2993_ = v___y_3005_;
v___y_2994_ = v___y_3006_;
v___y_2995_ = v___x_3009_;
v___y_2996_ = v___y_3007_;
v___y_2997_ = v___x_3010_;
goto v___jp_2988_;
}
else
{
v___y_2989_ = v___y_3002_;
v___y_2990_ = v___y_3003_;
v___y_2991_ = v___y_3004_;
v___y_2992_ = v___y_3008_;
v___y_2993_ = v___y_3005_;
v___y_2994_ = v___y_3006_;
v___y_2995_ = v___x_3009_;
v___y_2996_ = v___y_3007_;
v___y_2997_ = v___y_3002_;
goto v___jp_2988_;
}
}
v___jp_3012_:
{
uint64_t v___x_3022_; uint8_t v___x_3023_; 
v___x_3022_ = lean_uint64_shift_right(v___y_3013_, v___y_3018_);
v___x_3023_ = lean_uint64_dec_eq(v___x_3022_, v___y_3016_);
if (v___x_3023_ == 0)
{
uint64_t v___x_3024_; 
v___x_3024_ = lean_uint64_add(v___y_3019_, v___y_3018_);
v___y_3002_ = v___y_3021_;
v___y_3003_ = v___y_3014_;
v___y_3004_ = v___y_3015_;
v___y_3005_ = v___y_3016_;
v___y_3006_ = v___y_3017_;
v___y_3007_ = v___y_3020_;
v___y_3008_ = v___x_3024_;
goto v___jp_3001_;
}
else
{
v___y_3002_ = v___y_3021_;
v___y_3003_ = v___y_3014_;
v___y_3004_ = v___y_3015_;
v___y_3005_ = v___y_3016_;
v___y_3006_ = v___y_3017_;
v___y_3007_ = v___y_3020_;
v___y_3008_ = v___y_3019_;
goto v___jp_3001_;
}
}
v___jp_3025_:
{
uint64_t v___x_3033_; uint64_t v___x_3034_; uint8_t v___x_3035_; 
v___x_3033_ = 4ULL;
v___x_3034_ = lean_uint64_shift_right(v___y_3026_, v___x_3033_);
v___x_3035_ = lean_uint64_dec_eq(v___x_3034_, v___y_3029_);
if (v___x_3035_ == 0)
{
v___y_3013_ = v___y_3026_;
v___y_3014_ = v___y_3027_;
v___y_3015_ = v___y_3028_;
v___y_3016_ = v___y_3029_;
v___y_3017_ = v___y_3030_;
v___y_3018_ = v___x_3033_;
v___y_3019_ = v___y_3032_;
v___y_3020_ = v___y_3031_;
v___y_3021_ = v___x_3034_;
goto v___jp_3012_;
}
else
{
v___y_3013_ = v___y_3026_;
v___y_3014_ = v___y_3027_;
v___y_3015_ = v___y_3028_;
v___y_3016_ = v___y_3029_;
v___y_3017_ = v___y_3030_;
v___y_3018_ = v___x_3033_;
v___y_3019_ = v___y_3032_;
v___y_3020_ = v___y_3031_;
v___y_3021_ = v___y_3026_;
goto v___jp_3012_;
}
}
v___jp_3036_:
{
uint64_t v___x_3046_; uint8_t v___x_3047_; 
v___x_3046_ = lean_uint64_shift_right(v___y_3042_, v___y_3043_);
v___x_3047_ = lean_uint64_dec_eq(v___x_3046_, v___y_3040_);
if (v___x_3047_ == 0)
{
uint64_t v___x_3048_; 
v___x_3048_ = lean_uint64_add(v___y_3037_, v___y_3043_);
v___y_3026_ = v___y_3045_;
v___y_3027_ = v___y_3038_;
v___y_3028_ = v___y_3039_;
v___y_3029_ = v___y_3040_;
v___y_3030_ = v___y_3041_;
v___y_3031_ = v___y_3044_;
v___y_3032_ = v___x_3048_;
goto v___jp_3025_;
}
else
{
v___y_3026_ = v___y_3045_;
v___y_3027_ = v___y_3038_;
v___y_3028_ = v___y_3039_;
v___y_3029_ = v___y_3040_;
v___y_3030_ = v___y_3041_;
v___y_3031_ = v___y_3044_;
v___y_3032_ = v___y_3037_;
goto v___jp_3025_;
}
}
v___jp_3049_:
{
uint64_t v___x_3057_; uint64_t v___x_3058_; uint8_t v___x_3059_; 
v___x_3057_ = 8ULL;
v___x_3058_ = lean_uint64_shift_right(v___y_3054_, v___x_3057_);
v___x_3059_ = lean_uint64_dec_eq(v___x_3058_, v___y_3052_);
if (v___x_3059_ == 0)
{
v___y_3037_ = v___y_3056_;
v___y_3038_ = v___y_3050_;
v___y_3039_ = v___y_3051_;
v___y_3040_ = v___y_3052_;
v___y_3041_ = v___y_3053_;
v___y_3042_ = v___y_3054_;
v___y_3043_ = v___x_3057_;
v___y_3044_ = v___y_3055_;
v___y_3045_ = v___x_3058_;
goto v___jp_3036_;
}
else
{
v___y_3037_ = v___y_3056_;
v___y_3038_ = v___y_3050_;
v___y_3039_ = v___y_3051_;
v___y_3040_ = v___y_3052_;
v___y_3041_ = v___y_3053_;
v___y_3042_ = v___y_3054_;
v___y_3043_ = v___x_3057_;
v___y_3044_ = v___y_3055_;
v___y_3045_ = v___y_3054_;
goto v___jp_3036_;
}
}
v___jp_3060_:
{
uint64_t v___x_3070_; uint8_t v___x_3071_; 
v___x_3070_ = lean_uint64_shift_right(v___y_3061_, v___y_3065_);
v___x_3071_ = lean_uint64_dec_eq(v___x_3070_, v___y_3066_);
if (v___x_3071_ == 0)
{
uint64_t v___x_3072_; 
v___x_3072_ = lean_uint64_add(v___y_3064_, v___y_3065_);
v___y_3050_ = v___y_3062_;
v___y_3051_ = v___y_3063_;
v___y_3052_ = v___y_3066_;
v___y_3053_ = v___y_3067_;
v___y_3054_ = v___y_3069_;
v___y_3055_ = v___y_3068_;
v___y_3056_ = v___x_3072_;
goto v___jp_3049_;
}
else
{
v___y_3050_ = v___y_3062_;
v___y_3051_ = v___y_3063_;
v___y_3052_ = v___y_3066_;
v___y_3053_ = v___y_3067_;
v___y_3054_ = v___y_3069_;
v___y_3055_ = v___y_3068_;
v___y_3056_ = v___y_3064_;
goto v___jp_3049_;
}
}
v___jp_3073_:
{
uint64_t v___x_3081_; uint64_t v___x_3082_; uint8_t v___x_3083_; 
v___x_3081_ = 16ULL;
v___x_3082_ = lean_uint64_shift_right(v___y_3074_, v___x_3081_);
v___x_3083_ = lean_uint64_dec_eq(v___x_3082_, v___y_3077_);
if (v___x_3083_ == 0)
{
v___y_3061_ = v___y_3074_;
v___y_3062_ = v___y_3075_;
v___y_3063_ = v___y_3076_;
v___y_3064_ = v___y_3080_;
v___y_3065_ = v___x_3081_;
v___y_3066_ = v___y_3077_;
v___y_3067_ = v___y_3078_;
v___y_3068_ = v___y_3079_;
v___y_3069_ = v___x_3082_;
goto v___jp_3060_;
}
else
{
v___y_3061_ = v___y_3074_;
v___y_3062_ = v___y_3075_;
v___y_3063_ = v___y_3076_;
v___y_3064_ = v___y_3080_;
v___y_3065_ = v___x_3081_;
v___y_3066_ = v___y_3077_;
v___y_3067_ = v___y_3078_;
v___y_3068_ = v___y_3079_;
v___y_3069_ = v___y_3074_;
goto v___jp_3060_;
}
}
v___jp_3084_:
{
uint64_t v___x_3092_; uint64_t v___x_3093_; uint8_t v___x_3094_; 
v___x_3092_ = lean_unbox_uint64(v___y_3086_);
v___x_3093_ = lean_uint64_shift_right(v___x_3092_, v___y_3089_);
v___x_3094_ = lean_uint64_dec_eq(v___x_3093_, v___y_3087_);
if (v___x_3094_ == 0)
{
v___y_3074_ = v___y_3091_;
v___y_3075_ = v___y_3085_;
v___y_3076_ = v___y_3086_;
v___y_3077_ = v___y_3087_;
v___y_3078_ = v___y_3088_;
v___y_3079_ = v___y_3090_;
v___y_3080_ = v___y_3089_;
goto v___jp_3073_;
}
else
{
v___y_3074_ = v___y_3091_;
v___y_3075_ = v___y_3085_;
v___y_3076_ = v___y_3086_;
v___y_3077_ = v___y_3087_;
v___y_3078_ = v___y_3088_;
v___y_3079_ = v___y_3090_;
v___y_3080_ = v___y_3087_;
goto v___jp_3073_;
}
}
v___jp_3095_:
{
uint64_t v___x_3099_; uint64_t v___x_3100_; uint8_t v___x_3101_; 
v___x_3099_ = 0ULL;
v___x_3100_ = lean_unbox_uint64(v_snd_3098_);
v___x_3101_ = lean_uint64_dec_eq(v___x_3100_, v___x_3099_);
if (v___x_3101_ == 0)
{
uint64_t v___x_3102_; uint64_t v___x_3103_; uint64_t v___x_3104_; uint64_t v___x_3105_; uint64_t v___x_3106_; uint8_t v___x_3107_; 
v___x_3102_ = 149ULL;
v___x_3103_ = lean_uint64_add(v___y_3096_, v___x_3102_);
v___x_3104_ = 32ULL;
v___x_3105_ = lean_unbox_uint64(v_snd_3098_);
v___x_3106_ = lean_uint64_shift_right(v___x_3105_, v___x_3104_);
v___x_3107_ = lean_uint64_dec_eq(v___x_3106_, v___x_3099_);
if (v___x_3107_ == 0)
{
v___y_3085_ = v_fst_3097_;
v___y_3086_ = v_snd_3098_;
v___y_3087_ = v___x_3099_;
v___y_3088_ = v___x_3102_;
v___y_3089_ = v___x_3104_;
v___y_3090_ = v___x_3103_;
v___y_3091_ = v___x_3106_;
goto v___jp_3084_;
}
else
{
uint64_t v___x_3108_; 
v___x_3108_ = lean_unbox_uint64(v_snd_3098_);
v___y_3085_ = v_fst_3097_;
v___y_3086_ = v_snd_3098_;
v___y_3087_ = v___x_3099_;
v___y_3088_ = v___x_3102_;
v___y_3089_ = v___x_3104_;
v___y_3090_ = v___x_3103_;
v___y_3091_ = v___x_3108_;
goto v___jp_3084_;
}
}
else
{
uint8_t v___x_3109_; 
lean_dec(v_snd_3098_);
v___x_3109_ = lean_unbox(v_fst_3097_);
lean_dec(v_fst_3097_);
if (v___x_3109_ == 0)
{
uint32_t v___x_3110_; 
v___x_3110_ = 0;
return v___x_3110_;
}
else
{
uint32_t v___x_3111_; 
v___x_3111_ = 2147483648;
return v___x_3111_;
}
}
}
v___jp_3112_:
{
uint8_t v___x_3119_; 
v___x_3119_ = lean_uint64_dec_eq(v___y_3114_, v___y_3113_);
if (v___x_3119_ == 0)
{
uint8_t v___x_3120_; 
v___x_3120_ = lean_uint64_dec_lt(v___y_3114_, v___y_3113_);
if (v___x_3120_ == 0)
{
uint64_t v___x_3121_; lean_object* v___x_3122_; lean_object* v___x_3123_; 
v___x_3121_ = lean_uint64_sub(v___y_3114_, v___y_3113_);
v___x_3122_ = lean_box(v___y_3116_);
v___x_3123_ = lean_box_uint64(v___x_3121_);
v___y_3096_ = v___y_3117_;
v_fst_3097_ = v___x_3122_;
v_snd_3098_ = v___x_3123_;
goto v___jp_3095_;
}
else
{
uint64_t v___x_3124_; lean_object* v___x_3125_; lean_object* v___x_3126_; 
v___x_3124_ = lean_uint64_sub(v___y_3113_, v___y_3114_);
v___x_3125_ = lean_box(v___y_3115_);
v___x_3126_ = lean_box_uint64(v___x_3124_);
v___y_3096_ = v___y_3117_;
v_fst_3097_ = v___x_3125_;
v_snd_3098_ = v___x_3126_;
goto v___jp_3095_;
}
}
else
{
lean_object* v___x_3127_; lean_object* v___x_3128_; 
v___x_3127_ = lean_box(v___y_3118_);
v___x_3128_ = ((lean_object*)(lp_competition_Submission_TunedAdd_core___boxed__const__1));
v___y_3096_ = v___y_3117_;
v_fst_3097_ = v___x_3127_;
v_snd_3098_ = v___x_3128_;
goto v___jp_3095_;
}
}
v___jp_3129_:
{
if (v___y_3135_ == 0)
{
v___y_3113_ = v___y_3130_;
v___y_3114_ = v___y_3131_;
v___y_3115_ = v___y_3133_;
v___y_3116_ = v___y_3132_;
v___y_3117_ = v___y_3134_;
v___y_3118_ = v___y_3135_;
goto v___jp_3112_;
}
else
{
uint64_t v___x_3136_; lean_object* v___x_3137_; lean_object* v___x_3138_; 
v___x_3136_ = lean_uint64_add(v___y_3131_, v___y_3130_);
v___x_3137_ = lean_box(v___y_3132_);
v___x_3138_ = lean_box_uint64(v___x_3136_);
v___y_3096_ = v___y_3134_;
v_fst_3097_ = v___x_3137_;
v_snd_3098_ = v___x_3138_;
goto v___jp_3095_;
}
}
v___jp_3139_:
{
uint32_t v___x_3143_; uint32_t v___x_3144_; uint32_t v___x_3145_; uint32_t v___x_3146_; uint32_t v___x_3147_; uint32_t v___x_3148_; 
v___x_3143_ = lean_uint32_land(v___y_3141_, v___x_2261_);
v___x_3144_ = lean_uint32_shift_left(v___x_3143_, v___x_2259_);
v___x_3145_ = lean_uint32_lor(v___y_3142_, v___x_3144_);
v___x_3146_ = 8388607;
v___x_3147_ = lean_uint32_land(v___y_3140_, v___x_3146_);
v___x_3148_ = lean_uint32_lor(v___x_3145_, v___x_3147_);
return v___x_3148_;
}
v___jp_3149_:
{
uint8_t v___x_3153_; 
v___x_3153_ = lean_unbox(v___y_3150_);
lean_dec(v___y_3150_);
if (v___x_3153_ == 0)
{
uint32_t v___x_3154_; 
v___x_3154_ = 0;
v___y_3140_ = v___y_3152_;
v___y_3141_ = v___y_3151_;
v___y_3142_ = v___x_3154_;
goto v___jp_3139_;
}
else
{
uint32_t v___x_3155_; 
v___x_3155_ = 2147483648;
v___y_3140_ = v___y_3152_;
v___y_3141_ = v___y_3151_;
v___y_3142_ = v___x_3155_;
goto v___jp_3139_;
}
}
v___jp_3156_:
{
uint64_t v___x_3161_; uint64_t v_encodedExponent_3162_; uint32_t v___x_3163_; uint64_t v___x_3164_; uint8_t v___x_3165_; 
v___x_3161_ = 171ULL;
v_encodedExponent_3162_ = lean_uint64_sub(v___y_3158_, v___x_3161_);
v___x_3163_ = lean_uint64_to_uint32(v_encodedExponent_3162_);
v___x_3164_ = 8388608ULL;
v___x_3165_ = lean_uint64_dec_lt(v___y_3160_, v___x_3164_);
if (v___x_3165_ == 0)
{
uint64_t v___x_3166_; uint32_t v___x_3167_; 
v___x_3166_ = lean_uint64_sub(v___y_3160_, v___x_3164_);
v___x_3167_ = lean_uint64_to_uint32(v___x_3166_);
v___y_3150_ = v___y_3157_;
v___y_3151_ = v___x_3163_;
v___y_3152_ = v___x_3167_;
goto v___jp_3149_;
}
else
{
uint32_t v___x_3168_; 
v___x_3168_ = lean_uint64_to_uint32(v___y_3159_);
v___y_3150_ = v___y_3157_;
v___y_3151_ = v___x_3163_;
v___y_3152_ = v___x_3168_;
goto v___jp_3149_;
}
}
v___jp_3169_:
{
uint64_t v___x_3175_; uint8_t v___x_3176_; 
v___x_3175_ = 425ULL;
v___x_3176_ = lean_uint64_dec_lt(v___x_3175_, v___y_3174_);
if (v___x_3176_ == 0)
{
if (v___y_3172_ == 0)
{
v___y_3157_ = v___y_3171_;
v___y_3158_ = v___y_3174_;
v___y_3159_ = v___y_3173_;
v___y_3160_ = v___y_3170_;
goto v___jp_3156_;
}
else
{
uint64_t v___x_3177_; 
v___x_3177_ = 8388608ULL;
v___y_3157_ = v___y_3171_;
v___y_3158_ = v___y_3174_;
v___y_3159_ = v___y_3173_;
v___y_3160_ = v___x_3177_;
goto v___jp_3156_;
}
}
else
{
uint8_t v___x_3178_; 
v___x_3178_ = lean_unbox(v___y_3171_);
lean_dec(v___y_3171_);
if (v___x_3178_ == 0)
{
uint32_t v___x_3179_; 
v___x_3179_ = 2139095040;
return v___x_3179_;
}
else
{
uint32_t v___x_3180_; 
v___x_3180_ = 4286578688;
return v___x_3180_;
}
}
}
v___jp_3181_:
{
uint64_t v___x_3186_; uint8_t v_carry_3187_; 
v___x_3186_ = 16777216ULL;
v_carry_3187_ = lean_uint64_dec_eq(v___y_3185_, v___x_3186_);
if (v_carry_3187_ == 0)
{
v___y_3170_ = v___y_3185_;
v___y_3171_ = v___y_3182_;
v___y_3172_ = v_carry_3187_;
v___y_3173_ = v___y_3184_;
v___y_3174_ = v___y_3183_;
goto v___jp_3169_;
}
else
{
uint64_t v___x_3188_; uint64_t v___x_3189_; 
v___x_3188_ = 1ULL;
v___x_3189_ = lean_uint64_add(v___y_3183_, v___x_3188_);
v___y_3170_ = v___y_3185_;
v___y_3171_ = v___y_3182_;
v___y_3172_ = v_carry_3187_;
v___y_3173_ = v___y_3184_;
v___y_3174_ = v___x_3189_;
goto v___jp_3169_;
}
}
v___jp_3190_:
{
uint64_t v_position_3197_; uint64_t v___x_3198_; uint8_t v___x_3199_; 
v_position_3197_ = lean_uint64_add(v___y_3196_, v___y_3191_);
v___x_3198_ = 172ULL;
v___x_3199_ = lean_uint64_dec_lt(v_position_3197_, v___x_3198_);
if (v___x_3199_ == 0)
{
uint64_t v___x_3200_; uint8_t v___x_3201_; 
v___x_3200_ = 23ULL;
v___x_3201_ = lean_uint64_dec_lt(v___y_3196_, v___x_3200_);
if (v___x_3201_ == 0)
{
uint64_t v___x_3202_; uint8_t v___x_3203_; 
v___x_3202_ = lean_uint64_sub(v___y_3196_, v___x_3200_);
v___x_3203_ = lean_uint64_dec_eq(v___x_3202_, v___y_3195_);
if (v___x_3203_ == 0)
{
uint64_t v___x_3204_; uint8_t v___x_3205_; 
v___x_3204_ = 64ULL;
v___x_3205_ = lean_uint64_dec_lt(v___x_3202_, v___x_3204_);
if (v___x_3205_ == 0)
{
uint8_t v___x_3206_; 
v___x_3206_ = lean_uint64_dec_eq(v___x_3202_, v___x_3204_);
if (v___x_3206_ == 0)
{
lean_dec(v___y_3193_);
v___y_3182_ = v___y_3192_;
v___y_3183_ = v_position_3197_;
v___y_3184_ = v___y_3195_;
v___y_3185_ = v___y_3195_;
goto v___jp_3181_;
}
else
{
uint64_t v___x_3207_; uint64_t v___x_3208_; uint8_t v___x_3209_; 
v___x_3207_ = 9223372036854775808ULL;
v___x_3208_ = lean_unbox_uint64(v___y_3193_);
lean_dec(v___y_3193_);
v___x_3209_ = lean_uint64_dec_lt(v___x_3207_, v___x_3208_);
if (v___x_3209_ == 0)
{
v___y_3182_ = v___y_3192_;
v___y_3183_ = v_position_3197_;
v___y_3184_ = v___y_3195_;
v___y_3185_ = v___y_3195_;
goto v___jp_3181_;
}
else
{
uint64_t v___x_3210_; 
v___x_3210_ = 1ULL;
v___y_3182_ = v___y_3192_;
v___y_3183_ = v_position_3197_;
v___y_3184_ = v___y_3195_;
v___y_3185_ = v___x_3210_;
goto v___jp_3181_;
}
}
}
else
{
uint64_t v___x_3211_; uint64_t v_quotient_3212_; uint64_t v___x_3213_; uint64_t v___x_3214_; uint64_t v___x_3215_; uint64_t v___x_3216_; uint64_t v_remainder_3217_; uint64_t v___x_3218_; uint64_t v_half_3219_; uint8_t v___x_3220_; 
v___x_3211_ = lean_unbox_uint64(v___y_3193_);
v_quotient_3212_ = lean_uint64_shift_right(v___x_3211_, v___x_3202_);
v___x_3213_ = 1ULL;
v___x_3214_ = lean_uint64_shift_left(v___x_3213_, v___x_3202_);
v___x_3215_ = lean_uint64_sub(v___x_3214_, v___x_3213_);
v___x_3216_ = lean_unbox_uint64(v___y_3193_);
lean_dec(v___y_3193_);
v_remainder_3217_ = lean_uint64_land(v___x_3216_, v___x_3215_);
v___x_3218_ = lean_uint64_sub(v___x_3202_, v___x_3213_);
v_half_3219_ = lean_uint64_shift_left(v___x_3213_, v___x_3218_);
v___x_3220_ = lean_uint64_dec_lt(v_remainder_3217_, v_half_3219_);
if (v___x_3220_ == 0)
{
uint8_t v___x_3221_; 
v___x_3221_ = lean_uint64_dec_lt(v_half_3219_, v_remainder_3217_);
if (v___x_3221_ == 0)
{
uint64_t v___x_3222_; uint8_t v___x_3223_; 
v___x_3222_ = lean_uint64_land(v_quotient_3212_, v___x_3213_);
v___x_3223_ = lean_uint64_dec_eq(v___x_3222_, v___y_3195_);
if (v___x_3223_ == 0)
{
uint64_t v___x_3224_; 
v___x_3224_ = lean_uint64_add(v_quotient_3212_, v___x_3213_);
v___y_3182_ = v___y_3192_;
v___y_3183_ = v_position_3197_;
v___y_3184_ = v___y_3195_;
v___y_3185_ = v___x_3224_;
goto v___jp_3181_;
}
else
{
v___y_3182_ = v___y_3192_;
v___y_3183_ = v_position_3197_;
v___y_3184_ = v___y_3195_;
v___y_3185_ = v_quotient_3212_;
goto v___jp_3181_;
}
}
else
{
uint64_t v___x_3225_; 
v___x_3225_ = lean_uint64_add(v_quotient_3212_, v___x_3213_);
v___y_3182_ = v___y_3192_;
v___y_3183_ = v_position_3197_;
v___y_3184_ = v___y_3195_;
v___y_3185_ = v___x_3225_;
goto v___jp_3181_;
}
}
else
{
v___y_3182_ = v___y_3192_;
v___y_3183_ = v_position_3197_;
v___y_3184_ = v___y_3195_;
v___y_3185_ = v_quotient_3212_;
goto v___jp_3181_;
}
}
}
else
{
uint64_t v___x_3226_; 
v___x_3226_ = lean_unbox_uint64(v___y_3193_);
lean_dec(v___y_3193_);
v___y_3182_ = v___y_3192_;
v___y_3183_ = v_position_3197_;
v___y_3184_ = v___y_3195_;
v___y_3185_ = v___x_3226_;
goto v___jp_3181_;
}
}
else
{
uint64_t v___x_3227_; uint64_t v___x_3228_; uint64_t v___x_3229_; 
v___x_3227_ = lean_uint64_sub(v___x_3200_, v___y_3196_);
v___x_3228_ = lean_unbox_uint64(v___y_3193_);
lean_dec(v___y_3193_);
v___x_3229_ = lean_uint64_shift_left(v___x_3228_, v___x_3227_);
v___y_3182_ = v___y_3192_;
v___y_3183_ = v_position_3197_;
v___y_3184_ = v___y_3195_;
v___y_3185_ = v___x_3229_;
goto v___jp_3181_;
}
}
else
{
uint8_t v___x_3230_; 
v___x_3230_ = lean_uint64_dec_lt(v___y_3191_, v___y_3194_);
if (v___x_3230_ == 0)
{
uint64_t v___x_3231_; uint64_t v___x_3232_; uint64_t v___x_3233_; 
v___x_3231_ = lean_uint64_sub(v___y_3191_, v___y_3194_);
v___x_3232_ = lean_unbox_uint64(v___y_3193_);
lean_dec(v___y_3193_);
v___x_3233_ = lean_uint64_shift_left(v___x_3232_, v___x_3231_);
v___y_2138_ = v___y_3192_;
v___y_2139_ = v___y_3195_;
v___y_2140_ = v___x_3233_;
goto v___jp_2137_;
}
else
{
uint64_t v___x_3234_; uint8_t v___x_3235_; 
v___x_3234_ = lean_uint64_sub(v___y_3194_, v___y_3191_);
v___x_3235_ = lean_uint64_dec_eq(v___x_3234_, v___y_3195_);
if (v___x_3235_ == 0)
{
uint64_t v___x_3236_; uint8_t v___x_3237_; 
v___x_3236_ = 64ULL;
v___x_3237_ = lean_uint64_dec_lt(v___x_3234_, v___x_3236_);
if (v___x_3237_ == 0)
{
uint8_t v___x_3238_; 
v___x_3238_ = lean_uint64_dec_eq(v___x_3234_, v___x_3236_);
if (v___x_3238_ == 0)
{
lean_dec(v___y_3193_);
v___y_2138_ = v___y_3192_;
v___y_2139_ = v___y_3195_;
v___y_2140_ = v___y_3195_;
goto v___jp_2137_;
}
else
{
uint64_t v___x_3239_; uint64_t v___x_3240_; uint8_t v___x_3241_; 
v___x_3239_ = 9223372036854775808ULL;
v___x_3240_ = lean_unbox_uint64(v___y_3193_);
lean_dec(v___y_3193_);
v___x_3241_ = lean_uint64_dec_lt(v___x_3239_, v___x_3240_);
if (v___x_3241_ == 0)
{
v___y_2138_ = v___y_3192_;
v___y_2139_ = v___y_3195_;
v___y_2140_ = v___y_3195_;
goto v___jp_2137_;
}
else
{
uint64_t v___x_3242_; 
v___x_3242_ = 1ULL;
v___y_2138_ = v___y_3192_;
v___y_2139_ = v___y_3195_;
v___y_2140_ = v___x_3242_;
goto v___jp_2137_;
}
}
}
else
{
uint64_t v___x_3243_; uint64_t v_quotient_3244_; uint64_t v___x_3245_; uint64_t v___x_3246_; uint64_t v___x_3247_; uint64_t v___x_3248_; uint64_t v_remainder_3249_; uint64_t v___x_3250_; uint64_t v_half_3251_; uint8_t v___x_3252_; 
v___x_3243_ = lean_unbox_uint64(v___y_3193_);
v_quotient_3244_ = lean_uint64_shift_right(v___x_3243_, v___x_3234_);
v___x_3245_ = 1ULL;
v___x_3246_ = lean_uint64_shift_left(v___x_3245_, v___x_3234_);
v___x_3247_ = lean_uint64_sub(v___x_3246_, v___x_3245_);
v___x_3248_ = lean_unbox_uint64(v___y_3193_);
lean_dec(v___y_3193_);
v_remainder_3249_ = lean_uint64_land(v___x_3248_, v___x_3247_);
v___x_3250_ = lean_uint64_sub(v___x_3234_, v___x_3245_);
v_half_3251_ = lean_uint64_shift_left(v___x_3245_, v___x_3250_);
v___x_3252_ = lean_uint64_dec_lt(v_remainder_3249_, v_half_3251_);
if (v___x_3252_ == 0)
{
uint8_t v___x_3253_; 
v___x_3253_ = lean_uint64_dec_lt(v_half_3251_, v_remainder_3249_);
if (v___x_3253_ == 0)
{
uint64_t v___x_3254_; uint8_t v___x_3255_; 
v___x_3254_ = lean_uint64_land(v_quotient_3244_, v___x_3245_);
v___x_3255_ = lean_uint64_dec_eq(v___x_3254_, v___y_3195_);
if (v___x_3255_ == 0)
{
uint64_t v___x_3256_; 
v___x_3256_ = lean_uint64_add(v_quotient_3244_, v___x_3245_);
v___y_2138_ = v___y_3192_;
v___y_2139_ = v___y_3195_;
v___y_2140_ = v___x_3256_;
goto v___jp_2137_;
}
else
{
v___y_2138_ = v___y_3192_;
v___y_2139_ = v___y_3195_;
v___y_2140_ = v_quotient_3244_;
goto v___jp_2137_;
}
}
else
{
uint64_t v___x_3257_; 
v___x_3257_ = lean_uint64_add(v_quotient_3244_, v___x_3245_);
v___y_2138_ = v___y_3192_;
v___y_2139_ = v___y_3195_;
v___y_2140_ = v___x_3257_;
goto v___jp_2137_;
}
}
else
{
v___y_2138_ = v___y_3192_;
v___y_2139_ = v___y_3195_;
v___y_2140_ = v_quotient_3244_;
goto v___jp_2137_;
}
}
}
else
{
uint64_t v___x_3258_; 
v___x_3258_ = lean_unbox_uint64(v___y_3193_);
lean_dec(v___y_3193_);
v___y_2138_ = v___y_3192_;
v___y_2139_ = v___y_3195_;
v___y_2140_ = v___x_3258_;
goto v___jp_2137_;
}
}
}
}
v___jp_3259_:
{
uint64_t v___x_3267_; uint64_t v___x_3268_; uint8_t v___x_3269_; 
v___x_3267_ = 1ULL;
v___x_3268_ = lean_uint64_shift_right(v___y_3264_, v___x_3267_);
v___x_3269_ = lean_uint64_dec_eq(v___x_3268_, v___y_3265_);
if (v___x_3269_ == 0)
{
uint64_t v___x_3270_; 
v___x_3270_ = lean_uint64_add(v___y_3266_, v___x_3267_);
v___y_3191_ = v___y_3260_;
v___y_3192_ = v___y_3261_;
v___y_3193_ = v___y_3262_;
v___y_3194_ = v___y_3263_;
v___y_3195_ = v___y_3265_;
v___y_3196_ = v___x_3270_;
goto v___jp_3190_;
}
else
{
v___y_3191_ = v___y_3260_;
v___y_3192_ = v___y_3261_;
v___y_3193_ = v___y_3262_;
v___y_3194_ = v___y_3263_;
v___y_3195_ = v___y_3265_;
v___y_3196_ = v___y_3266_;
goto v___jp_3190_;
}
}
v___jp_3271_:
{
uint64_t v___x_3281_; uint8_t v___x_3282_; 
v___x_3281_ = lean_uint64_shift_right(v___y_3275_, v___y_3274_);
v___x_3282_ = lean_uint64_dec_eq(v___x_3281_, v___y_3279_);
if (v___x_3282_ == 0)
{
uint64_t v___x_3283_; 
v___x_3283_ = lean_uint64_add(v___y_3278_, v___y_3274_);
v___y_3260_ = v___y_3272_;
v___y_3261_ = v___y_3273_;
v___y_3262_ = v___y_3276_;
v___y_3263_ = v___y_3277_;
v___y_3264_ = v___y_3280_;
v___y_3265_ = v___y_3279_;
v___y_3266_ = v___x_3283_;
goto v___jp_3259_;
}
else
{
v___y_3260_ = v___y_3272_;
v___y_3261_ = v___y_3273_;
v___y_3262_ = v___y_3276_;
v___y_3263_ = v___y_3277_;
v___y_3264_ = v___y_3280_;
v___y_3265_ = v___y_3279_;
v___y_3266_ = v___y_3278_;
goto v___jp_3259_;
}
}
v___jp_3284_:
{
uint64_t v___x_3292_; uint64_t v___x_3293_; uint8_t v___x_3294_; 
v___x_3292_ = 2ULL;
v___x_3293_ = lean_uint64_shift_right(v___y_3287_, v___x_3292_);
v___x_3294_ = lean_uint64_dec_eq(v___x_3293_, v___y_3290_);
if (v___x_3294_ == 0)
{
v___y_3272_ = v___y_3285_;
v___y_3273_ = v___y_3286_;
v___y_3274_ = v___x_3292_;
v___y_3275_ = v___y_3287_;
v___y_3276_ = v___y_3288_;
v___y_3277_ = v___y_3289_;
v___y_3278_ = v___y_3291_;
v___y_3279_ = v___y_3290_;
v___y_3280_ = v___x_3293_;
goto v___jp_3271_;
}
else
{
v___y_3272_ = v___y_3285_;
v___y_3273_ = v___y_3286_;
v___y_3274_ = v___x_3292_;
v___y_3275_ = v___y_3287_;
v___y_3276_ = v___y_3288_;
v___y_3277_ = v___y_3289_;
v___y_3278_ = v___y_3291_;
v___y_3279_ = v___y_3290_;
v___y_3280_ = v___y_3287_;
goto v___jp_3271_;
}
}
v___jp_3295_:
{
uint64_t v___x_3305_; uint8_t v___x_3306_; 
v___x_3305_ = lean_uint64_shift_right(v___y_3299_, v___y_3302_);
v___x_3306_ = lean_uint64_dec_eq(v___x_3305_, v___y_3303_);
if (v___x_3306_ == 0)
{
uint64_t v___x_3307_; 
v___x_3307_ = lean_uint64_add(v___y_3296_, v___y_3302_);
v___y_3285_ = v___y_3297_;
v___y_3286_ = v___y_3298_;
v___y_3287_ = v___y_3304_;
v___y_3288_ = v___y_3300_;
v___y_3289_ = v___y_3301_;
v___y_3290_ = v___y_3303_;
v___y_3291_ = v___x_3307_;
goto v___jp_3284_;
}
else
{
v___y_3285_ = v___y_3297_;
v___y_3286_ = v___y_3298_;
v___y_3287_ = v___y_3304_;
v___y_3288_ = v___y_3300_;
v___y_3289_ = v___y_3301_;
v___y_3290_ = v___y_3303_;
v___y_3291_ = v___y_3296_;
goto v___jp_3284_;
}
}
v___jp_3308_:
{
uint64_t v___x_3316_; uint64_t v___x_3317_; uint8_t v___x_3318_; 
v___x_3316_ = 4ULL;
v___x_3317_ = lean_uint64_shift_right(v___y_3311_, v___x_3316_);
v___x_3318_ = lean_uint64_dec_eq(v___x_3317_, v___y_3314_);
if (v___x_3318_ == 0)
{
v___y_3296_ = v___y_3315_;
v___y_3297_ = v___y_3309_;
v___y_3298_ = v___y_3310_;
v___y_3299_ = v___y_3311_;
v___y_3300_ = v___y_3312_;
v___y_3301_ = v___y_3313_;
v___y_3302_ = v___x_3316_;
v___y_3303_ = v___y_3314_;
v___y_3304_ = v___x_3317_;
goto v___jp_3295_;
}
else
{
v___y_3296_ = v___y_3315_;
v___y_3297_ = v___y_3309_;
v___y_3298_ = v___y_3310_;
v___y_3299_ = v___y_3311_;
v___y_3300_ = v___y_3312_;
v___y_3301_ = v___y_3313_;
v___y_3302_ = v___x_3316_;
v___y_3303_ = v___y_3314_;
v___y_3304_ = v___y_3311_;
goto v___jp_3295_;
}
}
v___jp_3319_:
{
uint64_t v___x_3329_; uint8_t v___x_3330_; 
v___x_3329_ = lean_uint64_shift_right(v___y_3324_, v___y_3321_);
v___x_3330_ = lean_uint64_dec_eq(v___x_3329_, v___y_3327_);
if (v___x_3330_ == 0)
{
uint64_t v___x_3331_; 
v___x_3331_ = lean_uint64_add(v___y_3320_, v___y_3321_);
v___y_3309_ = v___y_3322_;
v___y_3310_ = v___y_3323_;
v___y_3311_ = v___y_3328_;
v___y_3312_ = v___y_3325_;
v___y_3313_ = v___y_3326_;
v___y_3314_ = v___y_3327_;
v___y_3315_ = v___x_3331_;
goto v___jp_3308_;
}
else
{
v___y_3309_ = v___y_3322_;
v___y_3310_ = v___y_3323_;
v___y_3311_ = v___y_3328_;
v___y_3312_ = v___y_3325_;
v___y_3313_ = v___y_3326_;
v___y_3314_ = v___y_3327_;
v___y_3315_ = v___y_3320_;
goto v___jp_3308_;
}
}
v___jp_3332_:
{
uint64_t v___x_3340_; uint64_t v___x_3341_; uint8_t v___x_3342_; 
v___x_3340_ = 8ULL;
v___x_3341_ = lean_uint64_shift_right(v___y_3335_, v___x_3340_);
v___x_3342_ = lean_uint64_dec_eq(v___x_3341_, v___y_3338_);
if (v___x_3342_ == 0)
{
v___y_3320_ = v___y_3339_;
v___y_3321_ = v___x_3340_;
v___y_3322_ = v___y_3333_;
v___y_3323_ = v___y_3334_;
v___y_3324_ = v___y_3335_;
v___y_3325_ = v___y_3336_;
v___y_3326_ = v___y_3337_;
v___y_3327_ = v___y_3338_;
v___y_3328_ = v___x_3341_;
goto v___jp_3319_;
}
else
{
v___y_3320_ = v___y_3339_;
v___y_3321_ = v___x_3340_;
v___y_3322_ = v___y_3333_;
v___y_3323_ = v___y_3334_;
v___y_3324_ = v___y_3335_;
v___y_3325_ = v___y_3336_;
v___y_3326_ = v___y_3337_;
v___y_3327_ = v___y_3338_;
v___y_3328_ = v___y_3335_;
goto v___jp_3319_;
}
}
v___jp_3343_:
{
uint64_t v___x_3353_; uint8_t v___x_3354_; 
v___x_3353_ = lean_uint64_shift_right(v___y_3348_, v___y_3347_);
v___x_3354_ = lean_uint64_dec_eq(v___x_3353_, v___y_3351_);
if (v___x_3354_ == 0)
{
uint64_t v___x_3355_; 
v___x_3355_ = lean_uint64_add(v___y_3346_, v___y_3347_);
v___y_3333_ = v___y_3344_;
v___y_3334_ = v___y_3345_;
v___y_3335_ = v___y_3352_;
v___y_3336_ = v___y_3349_;
v___y_3337_ = v___y_3350_;
v___y_3338_ = v___y_3351_;
v___y_3339_ = v___x_3355_;
goto v___jp_3332_;
}
else
{
v___y_3333_ = v___y_3344_;
v___y_3334_ = v___y_3345_;
v___y_3335_ = v___y_3352_;
v___y_3336_ = v___y_3349_;
v___y_3337_ = v___y_3350_;
v___y_3338_ = v___y_3351_;
v___y_3339_ = v___y_3346_;
goto v___jp_3332_;
}
}
v___jp_3356_:
{
uint64_t v___x_3364_; uint64_t v___x_3365_; uint8_t v___x_3366_; 
v___x_3364_ = 16ULL;
v___x_3365_ = lean_uint64_shift_right(v___y_3359_, v___x_3364_);
v___x_3366_ = lean_uint64_dec_eq(v___x_3365_, v___y_3362_);
if (v___x_3366_ == 0)
{
v___y_3344_ = v___y_3357_;
v___y_3345_ = v___y_3358_;
v___y_3346_ = v___y_3363_;
v___y_3347_ = v___x_3364_;
v___y_3348_ = v___y_3359_;
v___y_3349_ = v___y_3360_;
v___y_3350_ = v___y_3361_;
v___y_3351_ = v___y_3362_;
v___y_3352_ = v___x_3365_;
goto v___jp_3343_;
}
else
{
v___y_3344_ = v___y_3357_;
v___y_3345_ = v___y_3358_;
v___y_3346_ = v___y_3363_;
v___y_3347_ = v___x_3364_;
v___y_3348_ = v___y_3359_;
v___y_3349_ = v___y_3360_;
v___y_3350_ = v___y_3361_;
v___y_3351_ = v___y_3362_;
v___y_3352_ = v___y_3359_;
goto v___jp_3343_;
}
}
v___jp_3367_:
{
uint64_t v___x_3375_; uint64_t v___x_3376_; uint8_t v___x_3377_; 
v___x_3375_ = lean_unbox_uint64(v___y_3371_);
v___x_3376_ = lean_uint64_shift_right(v___x_3375_, v___y_3368_);
v___x_3377_ = lean_uint64_dec_eq(v___x_3376_, v___y_3373_);
if (v___x_3377_ == 0)
{
v___y_3357_ = v___y_3369_;
v___y_3358_ = v___y_3370_;
v___y_3359_ = v___y_3374_;
v___y_3360_ = v___y_3371_;
v___y_3361_ = v___y_3372_;
v___y_3362_ = v___y_3373_;
v___y_3363_ = v___y_3368_;
goto v___jp_3356_;
}
else
{
v___y_3357_ = v___y_3369_;
v___y_3358_ = v___y_3370_;
v___y_3359_ = v___y_3374_;
v___y_3360_ = v___y_3371_;
v___y_3361_ = v___y_3372_;
v___y_3362_ = v___y_3373_;
v___y_3363_ = v___y_3373_;
goto v___jp_3356_;
}
}
v___jp_3378_:
{
uint64_t v___x_3382_; uint64_t v___x_3383_; uint8_t v___x_3384_; 
v___x_3382_ = 0ULL;
v___x_3383_ = lean_unbox_uint64(v_snd_3381_);
v___x_3384_ = lean_uint64_dec_eq(v___x_3383_, v___x_3382_);
if (v___x_3384_ == 0)
{
uint64_t v___x_3385_; uint64_t v___x_3386_; uint64_t v___x_3387_; uint64_t v___x_3388_; uint64_t v___x_3389_; uint8_t v___x_3390_; 
v___x_3385_ = 149ULL;
v___x_3386_ = lean_uint64_add(v___y_3379_, v___x_3385_);
v___x_3387_ = 32ULL;
v___x_3388_ = lean_unbox_uint64(v_snd_3381_);
v___x_3389_ = lean_uint64_shift_right(v___x_3388_, v___x_3387_);
v___x_3390_ = lean_uint64_dec_eq(v___x_3389_, v___x_3382_);
if (v___x_3390_ == 0)
{
v___y_3368_ = v___x_3387_;
v___y_3369_ = v___x_3386_;
v___y_3370_ = v_fst_3380_;
v___y_3371_ = v_snd_3381_;
v___y_3372_ = v___x_3385_;
v___y_3373_ = v___x_3382_;
v___y_3374_ = v___x_3389_;
goto v___jp_3367_;
}
else
{
uint64_t v___x_3391_; 
v___x_3391_ = lean_unbox_uint64(v_snd_3381_);
v___y_3368_ = v___x_3387_;
v___y_3369_ = v___x_3386_;
v___y_3370_ = v_fst_3380_;
v___y_3371_ = v_snd_3381_;
v___y_3372_ = v___x_3385_;
v___y_3373_ = v___x_3382_;
v___y_3374_ = v___x_3391_;
goto v___jp_3367_;
}
}
else
{
uint8_t v___x_3392_; 
lean_dec(v_snd_3381_);
v___x_3392_ = lean_unbox(v_fst_3380_);
lean_dec(v_fst_3380_);
if (v___x_3392_ == 0)
{
uint32_t v___x_3393_; 
v___x_3393_ = 0;
return v___x_3393_;
}
else
{
uint32_t v___x_3394_; 
v___x_3394_ = 2147483648;
return v___x_3394_;
}
}
}
v___jp_3395_:
{
uint8_t v___x_3402_; 
v___x_3402_ = lean_uint64_dec_eq(v___y_3397_, v___y_3400_);
if (v___x_3402_ == 0)
{
uint8_t v___x_3403_; 
v___x_3403_ = lean_uint64_dec_lt(v___y_3397_, v___y_3400_);
if (v___x_3403_ == 0)
{
uint64_t v___x_3404_; lean_object* v___x_3405_; lean_object* v___x_3406_; 
v___x_3404_ = lean_uint64_sub(v___y_3397_, v___y_3400_);
v___x_3405_ = lean_box(v___y_3399_);
v___x_3406_ = lean_box_uint64(v___x_3404_);
v___y_3379_ = v___y_3396_;
v_fst_3380_ = v___x_3405_;
v_snd_3381_ = v___x_3406_;
goto v___jp_3378_;
}
else
{
uint64_t v___x_3407_; lean_object* v___x_3408_; lean_object* v___x_3409_; 
v___x_3407_ = lean_uint64_sub(v___y_3400_, v___y_3397_);
v___x_3408_ = lean_box(v___y_3398_);
v___x_3409_ = lean_box_uint64(v___x_3407_);
v___y_3379_ = v___y_3396_;
v_fst_3380_ = v___x_3408_;
v_snd_3381_ = v___x_3409_;
goto v___jp_3378_;
}
}
else
{
lean_object* v___x_3410_; lean_object* v___x_3411_; 
v___x_3410_ = lean_box(v___y_3401_);
v___x_3411_ = ((lean_object*)(lp_competition_Submission_TunedAdd_core___boxed__const__1));
v___y_3379_ = v___y_3396_;
v_fst_3380_ = v___x_3410_;
v_snd_3381_ = v___x_3411_;
goto v___jp_3378_;
}
}
v___jp_3412_:
{
if (v___y_3418_ == 0)
{
v___y_3396_ = v___y_3413_;
v___y_3397_ = v___y_3414_;
v___y_3398_ = v___y_3416_;
v___y_3399_ = v___y_3415_;
v___y_3400_ = v___y_3417_;
v___y_3401_ = v___y_3418_;
goto v___jp_3395_;
}
else
{
uint64_t v___x_3419_; lean_object* v___x_3420_; lean_object* v___x_3421_; 
v___x_3419_ = lean_uint64_add(v___y_3414_, v___y_3417_);
v___x_3420_ = lean_box(v___y_3415_);
v___x_3421_ = lean_box_uint64(v___x_3419_);
v___y_3379_ = v___y_3413_;
v_fst_3380_ = v___x_3420_;
v_snd_3381_ = v___x_3421_;
goto v___jp_3378_;
}
}
v___jp_3422_:
{
uint8_t v___x_3429_; 
v___x_3429_ = lean_uint64_dec_le(v___y_3424_, v___y_3428_);
if (v___x_3429_ == 0)
{
uint64_t v_shift_3430_; uint64_t v___x_3431_; uint8_t v___x_3432_; 
v_shift_3430_ = lean_uint64_sub(v___y_3424_, v___y_3428_);
v___x_3431_ = 39ULL;
v___x_3432_ = lean_uint64_dec_le(v_shift_3430_, v___x_3431_);
if (v___x_3432_ == 0)
{
return v_a_2041_;
}
else
{
uint64_t v___x_3433_; 
v___x_3433_ = lean_uint64_shift_left(v___y_3425_, v_shift_3430_);
if (v___y_3426_ == 0)
{
if (v___y_3427_ == 0)
{
v___y_3130_ = v___y_3423_;
v___y_3131_ = v___x_3433_;
v___y_3132_ = v___y_3426_;
v___y_3133_ = v___y_3427_;
v___y_3134_ = v___y_3428_;
v___y_3135_ = v___x_3432_;
goto v___jp_3129_;
}
else
{
v___y_3113_ = v___y_3423_;
v___y_3114_ = v___x_3433_;
v___y_3115_ = v___y_3427_;
v___y_3116_ = v___y_3426_;
v___y_3117_ = v___y_3428_;
v___y_3118_ = v___y_3426_;
goto v___jp_3112_;
}
}
else
{
v___y_3130_ = v___y_3423_;
v___y_3131_ = v___x_3433_;
v___y_3132_ = v___y_3426_;
v___y_3133_ = v___y_3427_;
v___y_3134_ = v___y_3428_;
v___y_3135_ = v___y_3427_;
goto v___jp_3129_;
}
}
}
else
{
uint64_t v_shift_3434_; uint64_t v___x_3435_; uint8_t v___x_3436_; 
v_shift_3434_ = lean_uint64_sub(v___y_3428_, v___y_3424_);
v___x_3435_ = 39ULL;
v___x_3436_ = lean_uint64_dec_le(v_shift_3434_, v___x_3435_);
if (v___x_3436_ == 0)
{
return v_b_2042_;
}
else
{
uint64_t v___x_3437_; 
v___x_3437_ = lean_uint64_shift_left(v___y_3423_, v_shift_3434_);
if (v___y_3426_ == 0)
{
if (v___y_3427_ == 0)
{
v___y_3413_ = v___y_3424_;
v___y_3414_ = v___y_3425_;
v___y_3415_ = v___y_3426_;
v___y_3416_ = v___y_3427_;
v___y_3417_ = v___x_3437_;
v___y_3418_ = v___x_3436_;
goto v___jp_3412_;
}
else
{
v___y_3396_ = v___y_3424_;
v___y_3397_ = v___y_3425_;
v___y_3398_ = v___y_3427_;
v___y_3399_ = v___y_3426_;
v___y_3400_ = v___x_3437_;
v___y_3401_ = v___y_3426_;
goto v___jp_3395_;
}
}
else
{
v___y_3413_ = v___y_3424_;
v___y_3414_ = v___y_3425_;
v___y_3415_ = v___y_3426_;
v___y_3416_ = v___y_3427_;
v___y_3417_ = v___x_3437_;
v___y_3418_ = v___y_3427_;
goto v___jp_3412_;
}
}
}
}
v___jp_3438_:
{
uint64_t v___x_3445_; uint64_t v___x_3446_; uint8_t v___x_3447_; 
v___x_3445_ = lean_uint32_to_uint64(v___y_3440_);
v___x_3446_ = 0ULL;
v___x_3447_ = lean_uint64_dec_eq(v___x_3445_, v___x_3446_);
if (v___x_3447_ == 0)
{
uint64_t v___x_3448_; uint64_t v___x_3449_; 
v___x_3448_ = 1ULL;
v___x_3449_ = lean_uint64_sub(v___x_3445_, v___x_3448_);
v___y_3423_ = v___y_3439_;
v___y_3424_ = v___y_3444_;
v___y_3425_ = v___y_3441_;
v___y_3426_ = v___y_3443_;
v___y_3427_ = v___y_3442_;
v___y_3428_ = v___x_3449_;
goto v___jp_3422_;
}
else
{
v___y_3423_ = v___y_3439_;
v___y_3424_ = v___y_3444_;
v___y_3425_ = v___y_3441_;
v___y_3426_ = v___y_3443_;
v___y_3427_ = v___y_3442_;
v___y_3428_ = v___x_3446_;
goto v___jp_3422_;
}
}
v___jp_3450_:
{
uint32_t v___x_3454_; uint32_t v___x_3455_; uint32_t v___x_3456_; uint32_t v___x_3457_; uint32_t v___x_3458_; uint32_t v___x_3459_; 
v___x_3454_ = lean_uint32_land(v___y_3452_, v___x_2261_);
v___x_3455_ = lean_uint32_shift_left(v___x_3454_, v___x_2259_);
v___x_3456_ = lean_uint32_lor(v___y_3453_, v___x_3455_);
v___x_3457_ = 8388607;
v___x_3458_ = lean_uint32_land(v___y_3451_, v___x_3457_);
v___x_3459_ = lean_uint32_lor(v___x_3456_, v___x_3458_);
return v___x_3459_;
}
v___jp_3460_:
{
if (v___y_3461_ == 0)
{
uint32_t v___x_3464_; 
v___x_3464_ = 0;
v___y_3451_ = v___y_3463_;
v___y_3452_ = v___y_3462_;
v___y_3453_ = v___x_3464_;
goto v___jp_3450_;
}
else
{
uint32_t v___x_3465_; 
v___x_3465_ = 2147483648;
v___y_3451_ = v___y_3463_;
v___y_3452_ = v___y_3462_;
v___y_3453_ = v___x_3465_;
goto v___jp_3450_;
}
}
v___jp_3466_:
{
uint64_t v___x_3470_; uint8_t v___x_3471_; 
v___x_3470_ = 8388608ULL;
v___x_3471_ = lean_uint64_dec_lt(v___y_3469_, v___x_3470_);
if (v___x_3471_ == 0)
{
uint64_t v___x_3472_; uint32_t v___x_3473_; 
v___x_3472_ = lean_uint64_sub(v___y_3469_, v___x_3470_);
v___x_3473_ = lean_uint64_to_uint32(v___x_3472_);
v___y_3461_ = v___y_3467_;
v___y_3462_ = v___y_3468_;
v___y_3463_ = v___x_3473_;
goto v___jp_3460_;
}
else
{
uint32_t v___x_3474_; 
v___x_3474_ = lean_uint32_once(&lp_competition_Submission_TunedAdd_fracW___closed__0, &lp_competition_Submission_TunedAdd_fracW___closed__0_once, _init_lp_competition_Submission_TunedAdd_fracW___closed__0);
v___y_3461_ = v___y_3467_;
v___y_3462_ = v___y_3468_;
v___y_3463_ = v___x_3474_;
goto v___jp_3460_;
}
}
v___jp_3475_:
{
uint64_t v___x_3480_; uint8_t v___x_3481_; 
v___x_3480_ = 425ULL;
v___x_3481_ = lean_uint64_dec_lt(v___x_3480_, v___y_3479_);
if (v___x_3481_ == 0)
{
uint64_t v___x_3482_; uint64_t v___x_3483_; uint32_t v___x_3484_; 
v___x_3482_ = 171ULL;
v___x_3483_ = lean_uint64_sub(v___y_3479_, v___x_3482_);
v___x_3484_ = lean_uint64_to_uint32(v___x_3483_);
if (v___y_3478_ == 0)
{
v___y_3467_ = v___y_3477_;
v___y_3468_ = v___x_3484_;
v___y_3469_ = v___y_3476_;
goto v___jp_3466_;
}
else
{
uint64_t v___x_3485_; 
v___x_3485_ = 8388608ULL;
v___y_3467_ = v___y_3477_;
v___y_3468_ = v___x_3484_;
v___y_3469_ = v___x_3485_;
goto v___jp_3466_;
}
}
else
{
if (v___y_3477_ == 0)
{
uint32_t v___x_3486_; 
v___x_3486_ = 2139095040;
return v___x_3486_;
}
else
{
uint32_t v___x_3487_; 
v___x_3487_ = 4286578688;
return v___x_3487_;
}
}
}
v___jp_3488_:
{
uint64_t v___x_3493_; uint8_t v_carry_3494_; 
v___x_3493_ = 16777216ULL;
v_carry_3494_ = lean_uint64_dec_eq(v___y_3492_, v___x_3493_);
if (v_carry_3494_ == 0)
{
v___y_3476_ = v___y_3492_;
v___y_3477_ = v___y_3491_;
v___y_3478_ = v_carry_3494_;
v___y_3479_ = v___y_3489_;
goto v___jp_3475_;
}
else
{
uint64_t v___x_3495_; 
v___x_3495_ = lean_uint64_add(v___y_3489_, v___y_3490_);
v___y_3476_ = v___y_3492_;
v___y_3477_ = v___y_3491_;
v___y_3478_ = v_carry_3494_;
v___y_3479_ = v___x_3495_;
goto v___jp_3475_;
}
}
v___jp_3496_:
{
uint32_t v___x_3500_; uint32_t v___x_3501_; uint32_t v___x_3502_; uint32_t v___x_3503_; uint32_t v___x_3504_; uint32_t v___x_3505_; 
v___x_3500_ = lean_uint32_land(v___y_3498_, v___x_2261_);
v___x_3501_ = lean_uint32_shift_left(v___x_3500_, v___x_2259_);
v___x_3502_ = lean_uint32_lor(v___y_3499_, v___x_3501_);
v___x_3503_ = 8388607;
v___x_3504_ = lean_uint32_land(v___y_3497_, v___x_3503_);
v___x_3505_ = lean_uint32_lor(v___x_3502_, v___x_3504_);
return v___x_3505_;
}
v___jp_3506_:
{
uint8_t v___x_3510_; 
v___x_3510_ = lean_unbox(v___y_3507_);
lean_dec(v___y_3507_);
if (v___x_3510_ == 0)
{
uint32_t v___x_3511_; 
v___x_3511_ = 0;
v___y_3497_ = v___y_3509_;
v___y_3498_ = v___y_3508_;
v___y_3499_ = v___x_3511_;
goto v___jp_3496_;
}
else
{
uint32_t v___x_3512_; 
v___x_3512_ = 2147483648;
v___y_3497_ = v___y_3509_;
v___y_3498_ = v___y_3508_;
v___y_3499_ = v___x_3512_;
goto v___jp_3496_;
}
}
v___jp_3513_:
{
uint64_t v___x_3518_; uint64_t v_encodedExponent_3519_; uint32_t v___x_3520_; uint64_t v___x_3521_; uint8_t v___x_3522_; 
v___x_3518_ = 171ULL;
v_encodedExponent_3519_ = lean_uint64_sub(v___y_3516_, v___x_3518_);
v___x_3520_ = lean_uint64_to_uint32(v_encodedExponent_3519_);
v___x_3521_ = 8388608ULL;
v___x_3522_ = lean_uint64_dec_lt(v___y_3517_, v___x_3521_);
if (v___x_3522_ == 0)
{
uint64_t v___x_3523_; uint32_t v___x_3524_; 
v___x_3523_ = lean_uint64_sub(v___y_3517_, v___x_3521_);
v___x_3524_ = lean_uint64_to_uint32(v___x_3523_);
v___y_3507_ = v___y_3514_;
v___y_3508_ = v___x_3520_;
v___y_3509_ = v___x_3524_;
goto v___jp_3506_;
}
else
{
uint32_t v___x_3525_; 
v___x_3525_ = lean_uint64_to_uint32(v___y_3515_);
v___y_3507_ = v___y_3514_;
v___y_3508_ = v___x_3520_;
v___y_3509_ = v___x_3525_;
goto v___jp_3506_;
}
}
v___jp_3526_:
{
uint64_t v___x_3532_; uint8_t v___x_3533_; 
v___x_3532_ = 425ULL;
v___x_3533_ = lean_uint64_dec_lt(v___x_3532_, v___y_3531_);
if (v___x_3533_ == 0)
{
if (v___y_3527_ == 0)
{
v___y_3514_ = v___y_3528_;
v___y_3515_ = v___y_3529_;
v___y_3516_ = v___y_3531_;
v___y_3517_ = v___y_3530_;
goto v___jp_3513_;
}
else
{
uint64_t v___x_3534_; 
v___x_3534_ = 8388608ULL;
v___y_3514_ = v___y_3528_;
v___y_3515_ = v___y_3529_;
v___y_3516_ = v___y_3531_;
v___y_3517_ = v___x_3534_;
goto v___jp_3513_;
}
}
else
{
uint8_t v___x_3535_; 
v___x_3535_ = lean_unbox(v___y_3528_);
lean_dec(v___y_3528_);
if (v___x_3535_ == 0)
{
uint32_t v___x_3536_; 
v___x_3536_ = 2139095040;
return v___x_3536_;
}
else
{
uint32_t v___x_3537_; 
v___x_3537_ = 4286578688;
return v___x_3537_;
}
}
}
v___jp_3538_:
{
uint64_t v___x_3544_; uint8_t v_carry_3545_; 
v___x_3544_ = 16777216ULL;
v_carry_3545_ = lean_uint64_dec_eq(v___y_3543_, v___x_3544_);
if (v_carry_3545_ == 0)
{
v___y_3527_ = v_carry_3545_;
v___y_3528_ = v___y_3540_;
v___y_3529_ = v___y_3542_;
v___y_3530_ = v___y_3543_;
v___y_3531_ = v___y_3541_;
goto v___jp_3526_;
}
else
{
uint64_t v___x_3546_; 
v___x_3546_ = lean_uint64_add(v___y_3541_, v___y_3539_);
v___y_3527_ = v_carry_3545_;
v___y_3528_ = v___y_3540_;
v___y_3529_ = v___y_3542_;
v___y_3530_ = v___y_3543_;
v___y_3531_ = v___x_3546_;
goto v___jp_3526_;
}
}
v___jp_3547_:
{
uint64_t v_position_3556_; uint8_t v___x_3557_; 
v_position_3556_ = lean_uint64_add(v___y_3555_, v___y_3553_);
v___x_3557_ = lean_uint64_dec_lt(v_position_3556_, v___y_3548_);
if (v___x_3557_ == 0)
{
uint64_t v___x_3558_; uint8_t v___x_3559_; 
v___x_3558_ = 23ULL;
v___x_3559_ = lean_uint64_dec_lt(v___y_3555_, v___x_3558_);
if (v___x_3559_ == 0)
{
uint64_t v___x_3560_; uint8_t v___x_3561_; 
v___x_3560_ = lean_uint64_sub(v___y_3555_, v___x_3558_);
v___x_3561_ = lean_uint64_dec_eq(v___x_3560_, v___y_3552_);
if (v___x_3561_ == 0)
{
uint64_t v___x_3562_; uint8_t v___x_3563_; 
v___x_3562_ = 64ULL;
v___x_3563_ = lean_uint64_dec_lt(v___x_3560_, v___x_3562_);
if (v___x_3563_ == 0)
{
uint8_t v___x_3564_; 
v___x_3564_ = lean_uint64_dec_eq(v___x_3560_, v___x_3562_);
if (v___x_3564_ == 0)
{
lean_dec(v___y_3549_);
v___y_3539_ = v___y_3551_;
v___y_3540_ = v___y_3550_;
v___y_3541_ = v_position_3556_;
v___y_3542_ = v___y_3552_;
v___y_3543_ = v___y_3552_;
goto v___jp_3538_;
}
else
{
uint64_t v___x_3565_; uint64_t v___x_3566_; uint8_t v___x_3567_; 
v___x_3565_ = 9223372036854775808ULL;
v___x_3566_ = lean_unbox_uint64(v___y_3549_);
lean_dec(v___y_3549_);
v___x_3567_ = lean_uint64_dec_lt(v___x_3565_, v___x_3566_);
if (v___x_3567_ == 0)
{
v___y_3539_ = v___y_3551_;
v___y_3540_ = v___y_3550_;
v___y_3541_ = v_position_3556_;
v___y_3542_ = v___y_3552_;
v___y_3543_ = v___y_3552_;
goto v___jp_3538_;
}
else
{
v___y_3539_ = v___y_3551_;
v___y_3540_ = v___y_3550_;
v___y_3541_ = v_position_3556_;
v___y_3542_ = v___y_3552_;
v___y_3543_ = v___y_3551_;
goto v___jp_3538_;
}
}
}
else
{
uint64_t v___x_3568_; uint64_t v_quotient_3569_; uint64_t v___x_3570_; uint64_t v___x_3571_; uint64_t v___x_3572_; uint64_t v_remainder_3573_; uint64_t v___x_3574_; uint64_t v_half_3575_; uint8_t v___x_3576_; 
v___x_3568_ = lean_unbox_uint64(v___y_3549_);
v_quotient_3569_ = lean_uint64_shift_right(v___x_3568_, v___x_3560_);
v___x_3570_ = lean_uint64_shift_left(v___y_3551_, v___x_3560_);
v___x_3571_ = lean_uint64_sub(v___x_3570_, v___y_3551_);
v___x_3572_ = lean_unbox_uint64(v___y_3549_);
lean_dec(v___y_3549_);
v_remainder_3573_ = lean_uint64_land(v___x_3572_, v___x_3571_);
v___x_3574_ = lean_uint64_sub(v___x_3560_, v___y_3551_);
v_half_3575_ = lean_uint64_shift_left(v___y_3551_, v___x_3574_);
v___x_3576_ = lean_uint64_dec_lt(v_remainder_3573_, v_half_3575_);
if (v___x_3576_ == 0)
{
uint8_t v___x_3577_; 
v___x_3577_ = lean_uint64_dec_lt(v_half_3575_, v_remainder_3573_);
if (v___x_3577_ == 0)
{
uint64_t v___x_3578_; uint8_t v___x_3579_; 
v___x_3578_ = lean_uint64_land(v_quotient_3569_, v___y_3551_);
v___x_3579_ = lean_uint64_dec_eq(v___x_3578_, v___y_3552_);
if (v___x_3579_ == 0)
{
uint64_t v___x_3580_; 
v___x_3580_ = lean_uint64_add(v_quotient_3569_, v___y_3551_);
v___y_3539_ = v___y_3551_;
v___y_3540_ = v___y_3550_;
v___y_3541_ = v_position_3556_;
v___y_3542_ = v___y_3552_;
v___y_3543_ = v___x_3580_;
goto v___jp_3538_;
}
else
{
v___y_3539_ = v___y_3551_;
v___y_3540_ = v___y_3550_;
v___y_3541_ = v_position_3556_;
v___y_3542_ = v___y_3552_;
v___y_3543_ = v_quotient_3569_;
goto v___jp_3538_;
}
}
else
{
uint64_t v___x_3581_; 
v___x_3581_ = lean_uint64_add(v_quotient_3569_, v___y_3551_);
v___y_3539_ = v___y_3551_;
v___y_3540_ = v___y_3550_;
v___y_3541_ = v_position_3556_;
v___y_3542_ = v___y_3552_;
v___y_3543_ = v___x_3581_;
goto v___jp_3538_;
}
}
else
{
v___y_3539_ = v___y_3551_;
v___y_3540_ = v___y_3550_;
v___y_3541_ = v_position_3556_;
v___y_3542_ = v___y_3552_;
v___y_3543_ = v_quotient_3569_;
goto v___jp_3538_;
}
}
}
else
{
uint64_t v___x_3582_; 
v___x_3582_ = lean_unbox_uint64(v___y_3549_);
lean_dec(v___y_3549_);
v___y_3539_ = v___y_3551_;
v___y_3540_ = v___y_3550_;
v___y_3541_ = v_position_3556_;
v___y_3542_ = v___y_3552_;
v___y_3543_ = v___x_3582_;
goto v___jp_3538_;
}
}
else
{
uint64_t v___x_3583_; uint64_t v___x_3584_; uint64_t v___x_3585_; 
v___x_3583_ = lean_uint64_sub(v___x_3558_, v___y_3555_);
v___x_3584_ = lean_unbox_uint64(v___y_3549_);
lean_dec(v___y_3549_);
v___x_3585_ = lean_uint64_shift_left(v___x_3584_, v___x_3583_);
v___y_3539_ = v___y_3551_;
v___y_3540_ = v___y_3550_;
v___y_3541_ = v_position_3556_;
v___y_3542_ = v___y_3552_;
v___y_3543_ = v___x_3585_;
goto v___jp_3538_;
}
}
else
{
uint8_t v___x_3586_; 
v___x_3586_ = lean_uint64_dec_lt(v___y_3553_, v___y_3554_);
if (v___x_3586_ == 0)
{
uint64_t v___x_3587_; uint64_t v___x_3588_; uint64_t v___x_3589_; 
v___x_3587_ = lean_uint64_sub(v___y_3553_, v___y_3554_);
v___x_3588_ = lean_unbox_uint64(v___y_3549_);
lean_dec(v___y_3549_);
v___x_3589_ = lean_uint64_shift_left(v___x_3588_, v___x_3587_);
v___y_2201_ = v___y_3550_;
v___y_2202_ = v___y_3552_;
v___y_2203_ = v___x_3589_;
goto v___jp_2200_;
}
else
{
uint64_t v___x_3590_; uint8_t v___x_3591_; 
v___x_3590_ = lean_uint64_sub(v___y_3554_, v___y_3553_);
v___x_3591_ = lean_uint64_dec_eq(v___x_3590_, v___y_3552_);
if (v___x_3591_ == 0)
{
uint64_t v___x_3592_; uint8_t v___x_3593_; 
v___x_3592_ = 64ULL;
v___x_3593_ = lean_uint64_dec_lt(v___x_3590_, v___x_3592_);
if (v___x_3593_ == 0)
{
uint8_t v___x_3594_; 
v___x_3594_ = lean_uint64_dec_eq(v___x_3590_, v___x_3592_);
if (v___x_3594_ == 0)
{
lean_dec(v___y_3549_);
v___y_2201_ = v___y_3550_;
v___y_2202_ = v___y_3552_;
v___y_2203_ = v___y_3552_;
goto v___jp_2200_;
}
else
{
uint64_t v___x_3595_; uint64_t v___x_3596_; uint8_t v___x_3597_; 
v___x_3595_ = 9223372036854775808ULL;
v___x_3596_ = lean_unbox_uint64(v___y_3549_);
lean_dec(v___y_3549_);
v___x_3597_ = lean_uint64_dec_lt(v___x_3595_, v___x_3596_);
if (v___x_3597_ == 0)
{
v___y_2201_ = v___y_3550_;
v___y_2202_ = v___y_3552_;
v___y_2203_ = v___y_3552_;
goto v___jp_2200_;
}
else
{
v___y_2201_ = v___y_3550_;
v___y_2202_ = v___y_3552_;
v___y_2203_ = v___y_3551_;
goto v___jp_2200_;
}
}
}
else
{
uint64_t v___x_3598_; uint64_t v_quotient_3599_; uint64_t v___x_3600_; uint64_t v___x_3601_; uint64_t v___x_3602_; uint64_t v_remainder_3603_; uint64_t v___x_3604_; uint64_t v_half_3605_; uint8_t v___x_3606_; 
v___x_3598_ = lean_unbox_uint64(v___y_3549_);
v_quotient_3599_ = lean_uint64_shift_right(v___x_3598_, v___x_3590_);
v___x_3600_ = lean_uint64_shift_left(v___y_3551_, v___x_3590_);
v___x_3601_ = lean_uint64_sub(v___x_3600_, v___y_3551_);
v___x_3602_ = lean_unbox_uint64(v___y_3549_);
lean_dec(v___y_3549_);
v_remainder_3603_ = lean_uint64_land(v___x_3602_, v___x_3601_);
v___x_3604_ = lean_uint64_sub(v___x_3590_, v___y_3551_);
v_half_3605_ = lean_uint64_shift_left(v___y_3551_, v___x_3604_);
v___x_3606_ = lean_uint64_dec_lt(v_remainder_3603_, v_half_3605_);
if (v___x_3606_ == 0)
{
uint8_t v___x_3607_; 
v___x_3607_ = lean_uint64_dec_lt(v_half_3605_, v_remainder_3603_);
if (v___x_3607_ == 0)
{
uint64_t v___x_3608_; uint8_t v___x_3609_; 
v___x_3608_ = lean_uint64_land(v_quotient_3599_, v___y_3551_);
v___x_3609_ = lean_uint64_dec_eq(v___x_3608_, v___y_3552_);
if (v___x_3609_ == 0)
{
uint64_t v___x_3610_; 
v___x_3610_ = lean_uint64_add(v_quotient_3599_, v___y_3551_);
v___y_2201_ = v___y_3550_;
v___y_2202_ = v___y_3552_;
v___y_2203_ = v___x_3610_;
goto v___jp_2200_;
}
else
{
v___y_2201_ = v___y_3550_;
v___y_2202_ = v___y_3552_;
v___y_2203_ = v_quotient_3599_;
goto v___jp_2200_;
}
}
else
{
uint64_t v___x_3611_; 
v___x_3611_ = lean_uint64_add(v_quotient_3599_, v___y_3551_);
v___y_2201_ = v___y_3550_;
v___y_2202_ = v___y_3552_;
v___y_2203_ = v___x_3611_;
goto v___jp_2200_;
}
}
else
{
v___y_2201_ = v___y_3550_;
v___y_2202_ = v___y_3552_;
v___y_2203_ = v_quotient_3599_;
goto v___jp_2200_;
}
}
}
else
{
uint64_t v___x_3612_; 
v___x_3612_ = lean_unbox_uint64(v___y_3549_);
lean_dec(v___y_3549_);
v___y_2201_ = v___y_3550_;
v___y_2202_ = v___y_3552_;
v___y_2203_ = v___x_3612_;
goto v___jp_2200_;
}
}
}
}
v___jp_3613_:
{
uint64_t v___x_3623_; uint8_t v___x_3624_; 
v___x_3623_ = lean_uint64_shift_right(v___y_3615_, v___y_3618_);
v___x_3624_ = lean_uint64_dec_eq(v___x_3623_, v___y_3620_);
if (v___x_3624_ == 0)
{
uint64_t v___x_3625_; 
v___x_3625_ = lean_uint64_add(v___y_3622_, v___y_3618_);
v___y_3548_ = v___y_3614_;
v___y_3549_ = v___y_3617_;
v___y_3550_ = v___y_3616_;
v___y_3551_ = v___y_3618_;
v___y_3552_ = v___y_3620_;
v___y_3553_ = v___y_3619_;
v___y_3554_ = v___y_3621_;
v___y_3555_ = v___x_3625_;
goto v___jp_3547_;
}
else
{
v___y_3548_ = v___y_3614_;
v___y_3549_ = v___y_3617_;
v___y_3550_ = v___y_3616_;
v___y_3551_ = v___y_3618_;
v___y_3552_ = v___y_3620_;
v___y_3553_ = v___y_3619_;
v___y_3554_ = v___y_3621_;
v___y_3555_ = v___y_3622_;
goto v___jp_3547_;
}
}
v___jp_3626_:
{
uint64_t v___x_3638_; uint8_t v___x_3639_; 
v___x_3638_ = lean_uint64_shift_right(v___y_3629_, v___y_3628_);
v___x_3639_ = lean_uint64_dec_eq(v___x_3638_, v___y_3633_);
if (v___x_3639_ == 0)
{
uint64_t v___x_3640_; 
v___x_3640_ = lean_uint64_add(v___y_3635_, v___y_3628_);
v___y_3614_ = v___y_3627_;
v___y_3615_ = v___y_3637_;
v___y_3616_ = v___y_3632_;
v___y_3617_ = v___y_3631_;
v___y_3618_ = v___y_3630_;
v___y_3619_ = v___y_3634_;
v___y_3620_ = v___y_3633_;
v___y_3621_ = v___y_3636_;
v___y_3622_ = v___x_3640_;
goto v___jp_3613_;
}
else
{
v___y_3614_ = v___y_3627_;
v___y_3615_ = v___y_3637_;
v___y_3616_ = v___y_3632_;
v___y_3617_ = v___y_3631_;
v___y_3618_ = v___y_3630_;
v___y_3619_ = v___y_3634_;
v___y_3620_ = v___y_3633_;
v___y_3621_ = v___y_3636_;
v___y_3622_ = v___y_3635_;
goto v___jp_3613_;
}
}
v___jp_3641_:
{
uint64_t v___x_3651_; uint64_t v___x_3652_; uint8_t v___x_3653_; 
v___x_3651_ = 2ULL;
v___x_3652_ = lean_uint64_shift_right(v___y_3646_, v___x_3651_);
v___x_3653_ = lean_uint64_dec_eq(v___x_3652_, v___y_3648_);
if (v___x_3653_ == 0)
{
v___y_3627_ = v___y_3642_;
v___y_3628_ = v___x_3651_;
v___y_3629_ = v___y_3646_;
v___y_3630_ = v___y_3645_;
v___y_3631_ = v___y_3644_;
v___y_3632_ = v___y_3643_;
v___y_3633_ = v___y_3648_;
v___y_3634_ = v___y_3647_;
v___y_3635_ = v___y_3650_;
v___y_3636_ = v___y_3649_;
v___y_3637_ = v___x_3652_;
goto v___jp_3626_;
}
else
{
v___y_3627_ = v___y_3642_;
v___y_3628_ = v___x_3651_;
v___y_3629_ = v___y_3646_;
v___y_3630_ = v___y_3645_;
v___y_3631_ = v___y_3644_;
v___y_3632_ = v___y_3643_;
v___y_3633_ = v___y_3648_;
v___y_3634_ = v___y_3647_;
v___y_3635_ = v___y_3650_;
v___y_3636_ = v___y_3649_;
v___y_3637_ = v___y_3646_;
goto v___jp_3626_;
}
}
v___jp_3654_:
{
uint64_t v___x_3666_; uint8_t v___x_3667_; 
v___x_3666_ = lean_uint64_shift_right(v___y_3663_, v___y_3656_);
v___x_3667_ = lean_uint64_dec_eq(v___x_3666_, v___y_3661_);
if (v___x_3667_ == 0)
{
uint64_t v___x_3668_; 
v___x_3668_ = lean_uint64_add(v___y_3660_, v___y_3656_);
v___y_3642_ = v___y_3655_;
v___y_3643_ = v___y_3659_;
v___y_3644_ = v___y_3658_;
v___y_3645_ = v___y_3657_;
v___y_3646_ = v___y_3665_;
v___y_3647_ = v___y_3662_;
v___y_3648_ = v___y_3661_;
v___y_3649_ = v___y_3664_;
v___y_3650_ = v___x_3668_;
goto v___jp_3641_;
}
else
{
v___y_3642_ = v___y_3655_;
v___y_3643_ = v___y_3659_;
v___y_3644_ = v___y_3658_;
v___y_3645_ = v___y_3657_;
v___y_3646_ = v___y_3665_;
v___y_3647_ = v___y_3662_;
v___y_3648_ = v___y_3661_;
v___y_3649_ = v___y_3664_;
v___y_3650_ = v___y_3660_;
goto v___jp_3641_;
}
}
v___jp_3669_:
{
uint64_t v___x_3679_; uint64_t v___x_3680_; uint8_t v___x_3681_; 
v___x_3679_ = 4ULL;
v___x_3680_ = lean_uint64_shift_right(v___y_3677_, v___x_3679_);
v___x_3681_ = lean_uint64_dec_eq(v___x_3680_, v___y_3675_);
if (v___x_3681_ == 0)
{
v___y_3655_ = v___y_3670_;
v___y_3656_ = v___x_3679_;
v___y_3657_ = v___y_3673_;
v___y_3658_ = v___y_3672_;
v___y_3659_ = v___y_3671_;
v___y_3660_ = v___y_3678_;
v___y_3661_ = v___y_3675_;
v___y_3662_ = v___y_3674_;
v___y_3663_ = v___y_3677_;
v___y_3664_ = v___y_3676_;
v___y_3665_ = v___x_3680_;
goto v___jp_3654_;
}
else
{
v___y_3655_ = v___y_3670_;
v___y_3656_ = v___x_3679_;
v___y_3657_ = v___y_3673_;
v___y_3658_ = v___y_3672_;
v___y_3659_ = v___y_3671_;
v___y_3660_ = v___y_3678_;
v___y_3661_ = v___y_3675_;
v___y_3662_ = v___y_3674_;
v___y_3663_ = v___y_3677_;
v___y_3664_ = v___y_3676_;
v___y_3665_ = v___y_3677_;
goto v___jp_3654_;
}
}
v___jp_3682_:
{
uint64_t v___x_3694_; uint8_t v___x_3695_; 
v___x_3694_ = lean_uint64_shift_right(v___y_3688_, v___y_3683_);
v___x_3695_ = lean_uint64_dec_eq(v___x_3694_, v___y_3689_);
if (v___x_3695_ == 0)
{
uint64_t v___x_3696_; 
v___x_3696_ = lean_uint64_add(v___y_3691_, v___y_3683_);
v___y_3670_ = v___y_3684_;
v___y_3671_ = v___y_3687_;
v___y_3672_ = v___y_3686_;
v___y_3673_ = v___y_3685_;
v___y_3674_ = v___y_3690_;
v___y_3675_ = v___y_3689_;
v___y_3676_ = v___y_3692_;
v___y_3677_ = v___y_3693_;
v___y_3678_ = v___x_3696_;
goto v___jp_3669_;
}
else
{
v___y_3670_ = v___y_3684_;
v___y_3671_ = v___y_3687_;
v___y_3672_ = v___y_3686_;
v___y_3673_ = v___y_3685_;
v___y_3674_ = v___y_3690_;
v___y_3675_ = v___y_3689_;
v___y_3676_ = v___y_3692_;
v___y_3677_ = v___y_3693_;
v___y_3678_ = v___y_3691_;
goto v___jp_3669_;
}
}
v___jp_3697_:
{
uint64_t v___x_3707_; uint64_t v___x_3708_; uint8_t v___x_3709_; 
v___x_3707_ = 8ULL;
v___x_3708_ = lean_uint64_shift_right(v___y_3702_, v___x_3707_);
v___x_3709_ = lean_uint64_dec_eq(v___x_3708_, v___y_3704_);
if (v___x_3709_ == 0)
{
v___y_3683_ = v___x_3707_;
v___y_3684_ = v___y_3698_;
v___y_3685_ = v___y_3701_;
v___y_3686_ = v___y_3700_;
v___y_3687_ = v___y_3699_;
v___y_3688_ = v___y_3702_;
v___y_3689_ = v___y_3704_;
v___y_3690_ = v___y_3703_;
v___y_3691_ = v___y_3706_;
v___y_3692_ = v___y_3705_;
v___y_3693_ = v___x_3708_;
goto v___jp_3682_;
}
else
{
v___y_3683_ = v___x_3707_;
v___y_3684_ = v___y_3698_;
v___y_3685_ = v___y_3701_;
v___y_3686_ = v___y_3700_;
v___y_3687_ = v___y_3699_;
v___y_3688_ = v___y_3702_;
v___y_3689_ = v___y_3704_;
v___y_3690_ = v___y_3703_;
v___y_3691_ = v___y_3706_;
v___y_3692_ = v___y_3705_;
v___y_3693_ = v___y_3702_;
goto v___jp_3682_;
}
}
v___jp_3710_:
{
uint64_t v___x_3722_; uint8_t v___x_3723_; 
v___x_3722_ = lean_uint64_shift_right(v___y_3720_, v___y_3719_);
v___x_3723_ = lean_uint64_dec_eq(v___x_3722_, v___y_3716_);
if (v___x_3723_ == 0)
{
uint64_t v___x_3724_; 
v___x_3724_ = lean_uint64_add(v___y_3712_, v___y_3719_);
v___y_3698_ = v___y_3711_;
v___y_3699_ = v___y_3715_;
v___y_3700_ = v___y_3714_;
v___y_3701_ = v___y_3713_;
v___y_3702_ = v___y_3721_;
v___y_3703_ = v___y_3717_;
v___y_3704_ = v___y_3716_;
v___y_3705_ = v___y_3718_;
v___y_3706_ = v___x_3724_;
goto v___jp_3697_;
}
else
{
v___y_3698_ = v___y_3711_;
v___y_3699_ = v___y_3715_;
v___y_3700_ = v___y_3714_;
v___y_3701_ = v___y_3713_;
v___y_3702_ = v___y_3721_;
v___y_3703_ = v___y_3717_;
v___y_3704_ = v___y_3716_;
v___y_3705_ = v___y_3718_;
v___y_3706_ = v___y_3712_;
goto v___jp_3697_;
}
}
v___jp_3725_:
{
uint64_t v___x_3735_; uint64_t v___x_3736_; uint8_t v___x_3737_; 
v___x_3735_ = 16ULL;
v___x_3736_ = lean_uint64_shift_right(v___y_3733_, v___x_3735_);
v___x_3737_ = lean_uint64_dec_eq(v___x_3736_, v___y_3731_);
if (v___x_3737_ == 0)
{
v___y_3711_ = v___y_3726_;
v___y_3712_ = v___y_3734_;
v___y_3713_ = v___y_3729_;
v___y_3714_ = v___y_3728_;
v___y_3715_ = v___y_3727_;
v___y_3716_ = v___y_3731_;
v___y_3717_ = v___y_3730_;
v___y_3718_ = v___y_3732_;
v___y_3719_ = v___x_3735_;
v___y_3720_ = v___y_3733_;
v___y_3721_ = v___x_3736_;
goto v___jp_3710_;
}
else
{
v___y_3711_ = v___y_3726_;
v___y_3712_ = v___y_3734_;
v___y_3713_ = v___y_3729_;
v___y_3714_ = v___y_3728_;
v___y_3715_ = v___y_3727_;
v___y_3716_ = v___y_3731_;
v___y_3717_ = v___y_3730_;
v___y_3718_ = v___y_3732_;
v___y_3719_ = v___x_3735_;
v___y_3720_ = v___y_3733_;
v___y_3721_ = v___y_3733_;
goto v___jp_3710_;
}
}
v___jp_3738_:
{
uint64_t v___x_3748_; uint64_t v___x_3749_; uint8_t v___x_3750_; 
v___x_3748_ = lean_unbox_uint64(v___y_3741_);
v___x_3749_ = lean_uint64_shift_right(v___x_3748_, v___y_3743_);
v___x_3750_ = lean_uint64_dec_eq(v___x_3749_, v___y_3744_);
if (v___x_3750_ == 0)
{
v___y_3726_ = v___y_3739_;
v___y_3727_ = v___y_3742_;
v___y_3728_ = v___y_3741_;
v___y_3729_ = v___y_3740_;
v___y_3730_ = v___y_3745_;
v___y_3731_ = v___y_3744_;
v___y_3732_ = v___y_3746_;
v___y_3733_ = v___y_3747_;
v___y_3734_ = v___y_3743_;
goto v___jp_3725_;
}
else
{
v___y_3726_ = v___y_3739_;
v___y_3727_ = v___y_3742_;
v___y_3728_ = v___y_3741_;
v___y_3729_ = v___y_3740_;
v___y_3730_ = v___y_3745_;
v___y_3731_ = v___y_3744_;
v___y_3732_ = v___y_3746_;
v___y_3733_ = v___y_3747_;
v___y_3734_ = v___y_3744_;
goto v___jp_3725_;
}
}
v___jp_3751_:
{
uint64_t v___x_3758_; uint64_t v___x_3759_; uint8_t v___x_3760_; 
v___x_3758_ = 0ULL;
v___x_3759_ = lean_unbox_uint64(v_snd_3757_);
v___x_3760_ = lean_uint64_dec_eq(v___x_3759_, v___x_3758_);
if (v___x_3760_ == 0)
{
uint64_t v___x_3761_; uint64_t v___x_3762_; uint64_t v___x_3763_; uint64_t v___x_3764_; uint8_t v___x_3765_; 
v___x_3761_ = lean_uint64_add(v___y_3754_, v___y_3755_);
v___x_3762_ = 32ULL;
v___x_3763_ = lean_unbox_uint64(v_snd_3757_);
v___x_3764_ = lean_uint64_shift_right(v___x_3763_, v___x_3762_);
v___x_3765_ = lean_uint64_dec_eq(v___x_3764_, v___x_3758_);
if (v___x_3765_ == 0)
{
v___y_3739_ = v___y_3752_;
v___y_3740_ = v___y_3753_;
v___y_3741_ = v_snd_3757_;
v___y_3742_ = v_fst_3756_;
v___y_3743_ = v___x_3762_;
v___y_3744_ = v___x_3758_;
v___y_3745_ = v___x_3761_;
v___y_3746_ = v___y_3755_;
v___y_3747_ = v___x_3764_;
goto v___jp_3738_;
}
else
{
uint64_t v___x_3766_; 
v___x_3766_ = lean_unbox_uint64(v_snd_3757_);
v___y_3739_ = v___y_3752_;
v___y_3740_ = v___y_3753_;
v___y_3741_ = v_snd_3757_;
v___y_3742_ = v_fst_3756_;
v___y_3743_ = v___x_3762_;
v___y_3744_ = v___x_3758_;
v___y_3745_ = v___x_3761_;
v___y_3746_ = v___y_3755_;
v___y_3747_ = v___x_3766_;
goto v___jp_3738_;
}
}
else
{
uint8_t v___x_3767_; 
lean_dec(v_snd_3757_);
v___x_3767_ = lean_unbox(v_fst_3756_);
lean_dec(v_fst_3756_);
if (v___x_3767_ == 0)
{
uint32_t v___x_3768_; 
v___x_3768_ = 0;
return v___x_3768_;
}
else
{
uint32_t v___x_3769_; 
v___x_3769_ = 2147483648;
return v___x_3769_;
}
}
}
v___jp_3770_:
{
uint8_t v___x_3780_; 
v___x_3780_ = lean_uint64_dec_eq(v___y_3774_, v___y_3775_);
if (v___x_3780_ == 0)
{
uint8_t v___x_3781_; 
v___x_3781_ = lean_uint64_dec_lt(v___y_3774_, v___y_3775_);
if (v___x_3781_ == 0)
{
uint64_t v___x_3782_; lean_object* v___x_3783_; lean_object* v___x_3784_; 
v___x_3782_ = lean_uint64_sub(v___y_3774_, v___y_3775_);
v___x_3783_ = lean_box(v___y_3778_);
v___x_3784_ = lean_box_uint64(v___x_3782_);
v___y_3752_ = v___y_3771_;
v___y_3753_ = v___y_3772_;
v___y_3754_ = v___y_3776_;
v___y_3755_ = v___y_3777_;
v_fst_3756_ = v___x_3783_;
v_snd_3757_ = v___x_3784_;
goto v___jp_3751_;
}
else
{
uint64_t v___x_3785_; lean_object* v___x_3786_; lean_object* v___x_3787_; 
v___x_3785_ = lean_uint64_sub(v___y_3775_, v___y_3774_);
v___x_3786_ = lean_box(v___y_3773_);
v___x_3787_ = lean_box_uint64(v___x_3785_);
v___y_3752_ = v___y_3771_;
v___y_3753_ = v___y_3772_;
v___y_3754_ = v___y_3776_;
v___y_3755_ = v___y_3777_;
v_fst_3756_ = v___x_3786_;
v_snd_3757_ = v___x_3787_;
goto v___jp_3751_;
}
}
else
{
lean_object* v___x_3788_; lean_object* v___x_3789_; 
v___x_3788_ = lean_box(v___y_3779_);
v___x_3789_ = ((lean_object*)(lp_competition_Submission_TunedAdd_core___boxed__const__1));
v___y_3752_ = v___y_3771_;
v___y_3753_ = v___y_3772_;
v___y_3754_ = v___y_3776_;
v___y_3755_ = v___y_3777_;
v_fst_3756_ = v___x_3788_;
v_snd_3757_ = v___x_3789_;
goto v___jp_3751_;
}
}
v___jp_3790_:
{
if (v___y_3799_ == 0)
{
v___y_3771_ = v___y_3791_;
v___y_3772_ = v___y_3792_;
v___y_3773_ = v___y_3793_;
v___y_3774_ = v___y_3794_;
v___y_3775_ = v___y_3795_;
v___y_3776_ = v___y_3796_;
v___y_3777_ = v___y_3797_;
v___y_3778_ = v___y_3798_;
v___y_3779_ = v___y_3799_;
goto v___jp_3770_;
}
else
{
uint64_t v___x_3800_; lean_object* v___x_3801_; lean_object* v___x_3802_; 
v___x_3800_ = lean_uint64_add(v___y_3794_, v___y_3795_);
v___x_3801_ = lean_box(v___y_3798_);
v___x_3802_ = lean_box_uint64(v___x_3800_);
v___y_3752_ = v___y_3791_;
v___y_3753_ = v___y_3792_;
v___y_3754_ = v___y_3796_;
v___y_3755_ = v___y_3797_;
v_fst_3756_ = v___x_3801_;
v_snd_3757_ = v___x_3802_;
goto v___jp_3751_;
}
}
v___jp_3803_:
{
uint32_t v___x_3807_; uint32_t v___x_3808_; uint32_t v___x_3809_; uint32_t v___x_3810_; uint32_t v___x_3811_; uint32_t v___x_3812_; 
v___x_3807_ = lean_uint32_land(v___y_3804_, v___x_2261_);
v___x_3808_ = lean_uint32_shift_left(v___x_3807_, v___x_2259_);
v___x_3809_ = lean_uint32_lor(v___y_3806_, v___x_3808_);
v___x_3810_ = 8388607;
v___x_3811_ = lean_uint32_land(v___y_3805_, v___x_3810_);
v___x_3812_ = lean_uint32_lor(v___x_3809_, v___x_3811_);
return v___x_3812_;
}
v___jp_3813_:
{
uint8_t v___x_3817_; 
v___x_3817_ = lean_unbox(v___y_3815_);
lean_dec(v___y_3815_);
if (v___x_3817_ == 0)
{
uint32_t v___x_3818_; 
v___x_3818_ = 0;
v___y_3804_ = v___y_3814_;
v___y_3805_ = v___y_3816_;
v___y_3806_ = v___x_3818_;
goto v___jp_3803_;
}
else
{
uint32_t v___x_3819_; 
v___x_3819_ = 2147483648;
v___y_3804_ = v___y_3814_;
v___y_3805_ = v___y_3816_;
v___y_3806_ = v___x_3819_;
goto v___jp_3803_;
}
}
v___jp_3820_:
{
uint64_t v___x_3825_; uint64_t v_encodedExponent_3826_; uint32_t v___x_3827_; uint64_t v___x_3828_; uint8_t v___x_3829_; 
v___x_3825_ = 171ULL;
v_encodedExponent_3826_ = lean_uint64_sub(v___y_3821_, v___x_3825_);
v___x_3827_ = lean_uint64_to_uint32(v_encodedExponent_3826_);
v___x_3828_ = 8388608ULL;
v___x_3829_ = lean_uint64_dec_lt(v___y_3824_, v___x_3828_);
if (v___x_3829_ == 0)
{
uint64_t v___x_3830_; uint32_t v___x_3831_; 
v___x_3830_ = lean_uint64_sub(v___y_3824_, v___x_3828_);
v___x_3831_ = lean_uint64_to_uint32(v___x_3830_);
v___y_3814_ = v___x_3827_;
v___y_3815_ = v___y_3823_;
v___y_3816_ = v___x_3831_;
goto v___jp_3813_;
}
else
{
uint32_t v___x_3832_; 
v___x_3832_ = lean_uint64_to_uint32(v___y_3822_);
v___y_3814_ = v___x_3827_;
v___y_3815_ = v___y_3823_;
v___y_3816_ = v___x_3832_;
goto v___jp_3813_;
}
}
v___jp_3833_:
{
uint64_t v___x_3839_; uint8_t v___x_3840_; 
v___x_3839_ = 425ULL;
v___x_3840_ = lean_uint64_dec_lt(v___x_3839_, v___y_3838_);
if (v___x_3840_ == 0)
{
if (v___y_3837_ == 0)
{
v___y_3821_ = v___y_3838_;
v___y_3822_ = v___y_3834_;
v___y_3823_ = v___y_3835_;
v___y_3824_ = v___y_3836_;
goto v___jp_3820_;
}
else
{
uint64_t v___x_3841_; 
v___x_3841_ = 8388608ULL;
v___y_3821_ = v___y_3838_;
v___y_3822_ = v___y_3834_;
v___y_3823_ = v___y_3835_;
v___y_3824_ = v___x_3841_;
goto v___jp_3820_;
}
}
else
{
uint8_t v___x_3842_; 
v___x_3842_ = lean_unbox(v___y_3835_);
lean_dec(v___y_3835_);
if (v___x_3842_ == 0)
{
uint32_t v___x_3843_; 
v___x_3843_ = 2139095040;
return v___x_3843_;
}
else
{
uint32_t v___x_3844_; 
v___x_3844_ = 4286578688;
return v___x_3844_;
}
}
}
v___jp_3845_:
{
uint64_t v___x_3851_; uint8_t v_carry_3852_; 
v___x_3851_ = 16777216ULL;
v_carry_3852_ = lean_uint64_dec_eq(v___y_3850_, v___x_3851_);
if (v_carry_3852_ == 0)
{
v___y_3834_ = v___y_3848_;
v___y_3835_ = v___y_3849_;
v___y_3836_ = v___y_3850_;
v___y_3837_ = v_carry_3852_;
v___y_3838_ = v___y_3846_;
goto v___jp_3833_;
}
else
{
uint64_t v___x_3853_; 
v___x_3853_ = lean_uint64_add(v___y_3846_, v___y_3847_);
v___y_3834_ = v___y_3848_;
v___y_3835_ = v___y_3849_;
v___y_3836_ = v___y_3850_;
v___y_3837_ = v_carry_3852_;
v___y_3838_ = v___x_3853_;
goto v___jp_3833_;
}
}
v___jp_3854_:
{
uint64_t v_position_3863_; uint8_t v___x_3864_; 
v_position_3863_ = lean_uint64_add(v___y_3862_, v___y_3856_);
v___x_3864_ = lean_uint64_dec_lt(v_position_3863_, v___y_3855_);
if (v___x_3864_ == 0)
{
uint64_t v___x_3865_; uint8_t v___x_3866_; 
v___x_3865_ = 23ULL;
v___x_3866_ = lean_uint64_dec_lt(v___y_3862_, v___x_3865_);
if (v___x_3866_ == 0)
{
uint64_t v___x_3867_; uint8_t v___x_3868_; 
v___x_3867_ = lean_uint64_sub(v___y_3862_, v___x_3865_);
v___x_3868_ = lean_uint64_dec_eq(v___x_3867_, v___y_3858_);
if (v___x_3868_ == 0)
{
uint64_t v___x_3869_; uint8_t v___x_3870_; 
v___x_3869_ = 64ULL;
v___x_3870_ = lean_uint64_dec_lt(v___x_3867_, v___x_3869_);
if (v___x_3870_ == 0)
{
uint8_t v___x_3871_; 
v___x_3871_ = lean_uint64_dec_eq(v___x_3867_, v___x_3869_);
if (v___x_3871_ == 0)
{
lean_dec(v___y_3859_);
v___y_3846_ = v_position_3863_;
v___y_3847_ = v___y_3857_;
v___y_3848_ = v___y_3858_;
v___y_3849_ = v___y_3860_;
v___y_3850_ = v___y_3858_;
goto v___jp_3845_;
}
else
{
uint64_t v___x_3872_; uint64_t v___x_3873_; uint8_t v___x_3874_; 
v___x_3872_ = 9223372036854775808ULL;
v___x_3873_ = lean_unbox_uint64(v___y_3859_);
lean_dec(v___y_3859_);
v___x_3874_ = lean_uint64_dec_lt(v___x_3872_, v___x_3873_);
if (v___x_3874_ == 0)
{
v___y_3846_ = v_position_3863_;
v___y_3847_ = v___y_3857_;
v___y_3848_ = v___y_3858_;
v___y_3849_ = v___y_3860_;
v___y_3850_ = v___y_3858_;
goto v___jp_3845_;
}
else
{
v___y_3846_ = v_position_3863_;
v___y_3847_ = v___y_3857_;
v___y_3848_ = v___y_3858_;
v___y_3849_ = v___y_3860_;
v___y_3850_ = v___y_3857_;
goto v___jp_3845_;
}
}
}
else
{
uint64_t v___x_3875_; uint64_t v_quotient_3876_; uint64_t v___x_3877_; uint64_t v___x_3878_; uint64_t v___x_3879_; uint64_t v_remainder_3880_; uint64_t v___x_3881_; uint64_t v_half_3882_; uint8_t v___x_3883_; 
v___x_3875_ = lean_unbox_uint64(v___y_3859_);
v_quotient_3876_ = lean_uint64_shift_right(v___x_3875_, v___x_3867_);
v___x_3877_ = lean_uint64_shift_left(v___y_3857_, v___x_3867_);
v___x_3878_ = lean_uint64_sub(v___x_3877_, v___y_3857_);
v___x_3879_ = lean_unbox_uint64(v___y_3859_);
lean_dec(v___y_3859_);
v_remainder_3880_ = lean_uint64_land(v___x_3879_, v___x_3878_);
v___x_3881_ = lean_uint64_sub(v___x_3867_, v___y_3857_);
v_half_3882_ = lean_uint64_shift_left(v___y_3857_, v___x_3881_);
v___x_3883_ = lean_uint64_dec_lt(v_remainder_3880_, v_half_3882_);
if (v___x_3883_ == 0)
{
uint8_t v___x_3884_; 
v___x_3884_ = lean_uint64_dec_lt(v_half_3882_, v_remainder_3880_);
if (v___x_3884_ == 0)
{
uint64_t v___x_3885_; uint8_t v___x_3886_; 
v___x_3885_ = lean_uint64_land(v_quotient_3876_, v___y_3857_);
v___x_3886_ = lean_uint64_dec_eq(v___x_3885_, v___y_3858_);
if (v___x_3886_ == 0)
{
uint64_t v___x_3887_; 
v___x_3887_ = lean_uint64_add(v_quotient_3876_, v___y_3857_);
v___y_3846_ = v_position_3863_;
v___y_3847_ = v___y_3857_;
v___y_3848_ = v___y_3858_;
v___y_3849_ = v___y_3860_;
v___y_3850_ = v___x_3887_;
goto v___jp_3845_;
}
else
{
v___y_3846_ = v_position_3863_;
v___y_3847_ = v___y_3857_;
v___y_3848_ = v___y_3858_;
v___y_3849_ = v___y_3860_;
v___y_3850_ = v_quotient_3876_;
goto v___jp_3845_;
}
}
else
{
uint64_t v___x_3888_; 
v___x_3888_ = lean_uint64_add(v_quotient_3876_, v___y_3857_);
v___y_3846_ = v_position_3863_;
v___y_3847_ = v___y_3857_;
v___y_3848_ = v___y_3858_;
v___y_3849_ = v___y_3860_;
v___y_3850_ = v___x_3888_;
goto v___jp_3845_;
}
}
else
{
v___y_3846_ = v_position_3863_;
v___y_3847_ = v___y_3857_;
v___y_3848_ = v___y_3858_;
v___y_3849_ = v___y_3860_;
v___y_3850_ = v_quotient_3876_;
goto v___jp_3845_;
}
}
}
else
{
uint64_t v___x_3889_; 
v___x_3889_ = lean_unbox_uint64(v___y_3859_);
lean_dec(v___y_3859_);
v___y_3846_ = v_position_3863_;
v___y_3847_ = v___y_3857_;
v___y_3848_ = v___y_3858_;
v___y_3849_ = v___y_3860_;
v___y_3850_ = v___x_3889_;
goto v___jp_3845_;
}
}
else
{
uint64_t v___x_3890_; uint64_t v___x_3891_; uint64_t v___x_3892_; 
v___x_3890_ = lean_uint64_sub(v___x_3865_, v___y_3862_);
v___x_3891_ = lean_unbox_uint64(v___y_3859_);
lean_dec(v___y_3859_);
v___x_3892_ = lean_uint64_shift_left(v___x_3891_, v___x_3890_);
v___y_3846_ = v_position_3863_;
v___y_3847_ = v___y_3857_;
v___y_3848_ = v___y_3858_;
v___y_3849_ = v___y_3860_;
v___y_3850_ = v___x_3892_;
goto v___jp_3845_;
}
}
else
{
uint8_t v___x_3893_; 
v___x_3893_ = lean_uint64_dec_lt(v___y_3856_, v___y_3861_);
if (v___x_3893_ == 0)
{
uint64_t v___x_3894_; uint64_t v___x_3895_; uint64_t v___x_3896_; 
v___x_3894_ = lean_uint64_sub(v___y_3856_, v___y_3861_);
v___x_3895_ = lean_unbox_uint64(v___y_3859_);
lean_dec(v___y_3859_);
v___x_3896_ = lean_uint64_shift_left(v___x_3895_, v___x_3894_);
v___y_2180_ = v___y_3858_;
v___y_2181_ = v___y_3860_;
v___y_2182_ = v___x_3896_;
goto v___jp_2179_;
}
else
{
uint64_t v___x_3897_; uint8_t v___x_3898_; 
v___x_3897_ = lean_uint64_sub(v___y_3861_, v___y_3856_);
v___x_3898_ = lean_uint64_dec_eq(v___x_3897_, v___y_3858_);
if (v___x_3898_ == 0)
{
uint64_t v___x_3899_; uint8_t v___x_3900_; 
v___x_3899_ = 64ULL;
v___x_3900_ = lean_uint64_dec_lt(v___x_3897_, v___x_3899_);
if (v___x_3900_ == 0)
{
uint8_t v___x_3901_; 
v___x_3901_ = lean_uint64_dec_eq(v___x_3897_, v___x_3899_);
if (v___x_3901_ == 0)
{
lean_dec(v___y_3859_);
v___y_2180_ = v___y_3858_;
v___y_2181_ = v___y_3860_;
v___y_2182_ = v___y_3858_;
goto v___jp_2179_;
}
else
{
uint64_t v___x_3902_; uint64_t v___x_3903_; uint8_t v___x_3904_; 
v___x_3902_ = 9223372036854775808ULL;
v___x_3903_ = lean_unbox_uint64(v___y_3859_);
lean_dec(v___y_3859_);
v___x_3904_ = lean_uint64_dec_lt(v___x_3902_, v___x_3903_);
if (v___x_3904_ == 0)
{
v___y_2180_ = v___y_3858_;
v___y_2181_ = v___y_3860_;
v___y_2182_ = v___y_3858_;
goto v___jp_2179_;
}
else
{
v___y_2180_ = v___y_3858_;
v___y_2181_ = v___y_3860_;
v___y_2182_ = v___y_3857_;
goto v___jp_2179_;
}
}
}
else
{
uint64_t v___x_3905_; uint64_t v_quotient_3906_; uint64_t v___x_3907_; uint64_t v___x_3908_; uint64_t v___x_3909_; uint64_t v_remainder_3910_; uint64_t v___x_3911_; uint64_t v_half_3912_; uint8_t v___x_3913_; 
v___x_3905_ = lean_unbox_uint64(v___y_3859_);
v_quotient_3906_ = lean_uint64_shift_right(v___x_3905_, v___x_3897_);
v___x_3907_ = lean_uint64_shift_left(v___y_3857_, v___x_3897_);
v___x_3908_ = lean_uint64_sub(v___x_3907_, v___y_3857_);
v___x_3909_ = lean_unbox_uint64(v___y_3859_);
lean_dec(v___y_3859_);
v_remainder_3910_ = lean_uint64_land(v___x_3909_, v___x_3908_);
v___x_3911_ = lean_uint64_sub(v___x_3897_, v___y_3857_);
v_half_3912_ = lean_uint64_shift_left(v___y_3857_, v___x_3911_);
v___x_3913_ = lean_uint64_dec_lt(v_remainder_3910_, v_half_3912_);
if (v___x_3913_ == 0)
{
uint8_t v___x_3914_; 
v___x_3914_ = lean_uint64_dec_lt(v_half_3912_, v_remainder_3910_);
if (v___x_3914_ == 0)
{
uint64_t v___x_3915_; uint8_t v___x_3916_; 
v___x_3915_ = lean_uint64_land(v_quotient_3906_, v___y_3857_);
v___x_3916_ = lean_uint64_dec_eq(v___x_3915_, v___y_3858_);
if (v___x_3916_ == 0)
{
uint64_t v___x_3917_; 
v___x_3917_ = lean_uint64_add(v_quotient_3906_, v___y_3857_);
v___y_2180_ = v___y_3858_;
v___y_2181_ = v___y_3860_;
v___y_2182_ = v___x_3917_;
goto v___jp_2179_;
}
else
{
v___y_2180_ = v___y_3858_;
v___y_2181_ = v___y_3860_;
v___y_2182_ = v_quotient_3906_;
goto v___jp_2179_;
}
}
else
{
uint64_t v___x_3918_; 
v___x_3918_ = lean_uint64_add(v_quotient_3906_, v___y_3857_);
v___y_2180_ = v___y_3858_;
v___y_2181_ = v___y_3860_;
v___y_2182_ = v___x_3918_;
goto v___jp_2179_;
}
}
else
{
v___y_2180_ = v___y_3858_;
v___y_2181_ = v___y_3860_;
v___y_2182_ = v_quotient_3906_;
goto v___jp_2179_;
}
}
}
else
{
uint64_t v___x_3919_; 
v___x_3919_ = lean_unbox_uint64(v___y_3859_);
lean_dec(v___y_3859_);
v___y_2180_ = v___y_3858_;
v___y_2181_ = v___y_3860_;
v___y_2182_ = v___x_3919_;
goto v___jp_2179_;
}
}
}
}
v___jp_3920_:
{
uint64_t v___x_3930_; uint8_t v___x_3931_; 
v___x_3930_ = lean_uint64_shift_right(v___y_3922_, v___y_3924_);
v___x_3931_ = lean_uint64_dec_eq(v___x_3930_, v___y_3925_);
if (v___x_3931_ == 0)
{
uint64_t v___x_3932_; 
v___x_3932_ = lean_uint64_add(v___y_3929_, v___y_3924_);
v___y_3855_ = v___y_3921_;
v___y_3856_ = v___y_3923_;
v___y_3857_ = v___y_3924_;
v___y_3858_ = v___y_3925_;
v___y_3859_ = v___y_3927_;
v___y_3860_ = v___y_3926_;
v___y_3861_ = v___y_3928_;
v___y_3862_ = v___x_3932_;
goto v___jp_3854_;
}
else
{
v___y_3855_ = v___y_3921_;
v___y_3856_ = v___y_3923_;
v___y_3857_ = v___y_3924_;
v___y_3858_ = v___y_3925_;
v___y_3859_ = v___y_3927_;
v___y_3860_ = v___y_3926_;
v___y_3861_ = v___y_3928_;
v___y_3862_ = v___y_3929_;
goto v___jp_3854_;
}
}
v___jp_3933_:
{
uint64_t v___x_3945_; uint8_t v___x_3946_; 
v___x_3945_ = lean_uint64_shift_right(v___y_3935_, v___y_3940_);
v___x_3946_ = lean_uint64_dec_eq(v___x_3945_, v___y_3939_);
if (v___x_3946_ == 0)
{
uint64_t v___x_3947_; 
v___x_3947_ = lean_uint64_add(v___y_3937_, v___y_3940_);
v___y_3921_ = v___y_3934_;
v___y_3922_ = v___y_3944_;
v___y_3923_ = v___y_3936_;
v___y_3924_ = v___y_3938_;
v___y_3925_ = v___y_3939_;
v___y_3926_ = v___y_3942_;
v___y_3927_ = v___y_3941_;
v___y_3928_ = v___y_3943_;
v___y_3929_ = v___x_3947_;
goto v___jp_3920_;
}
else
{
v___y_3921_ = v___y_3934_;
v___y_3922_ = v___y_3944_;
v___y_3923_ = v___y_3936_;
v___y_3924_ = v___y_3938_;
v___y_3925_ = v___y_3939_;
v___y_3926_ = v___y_3942_;
v___y_3927_ = v___y_3941_;
v___y_3928_ = v___y_3943_;
v___y_3929_ = v___y_3937_;
goto v___jp_3920_;
}
}
v___jp_3948_:
{
uint64_t v___x_3958_; uint64_t v___x_3959_; uint8_t v___x_3960_; 
v___x_3958_ = 2ULL;
v___x_3959_ = lean_uint64_shift_right(v___y_3951_, v___x_3958_);
v___x_3960_ = lean_uint64_dec_eq(v___x_3959_, v___y_3953_);
if (v___x_3960_ == 0)
{
v___y_3934_ = v___y_3949_;
v___y_3935_ = v___y_3951_;
v___y_3936_ = v___y_3950_;
v___y_3937_ = v___y_3957_;
v___y_3938_ = v___y_3952_;
v___y_3939_ = v___y_3953_;
v___y_3940_ = v___x_3958_;
v___y_3941_ = v___y_3955_;
v___y_3942_ = v___y_3954_;
v___y_3943_ = v___y_3956_;
v___y_3944_ = v___x_3959_;
goto v___jp_3933_;
}
else
{
v___y_3934_ = v___y_3949_;
v___y_3935_ = v___y_3951_;
v___y_3936_ = v___y_3950_;
v___y_3937_ = v___y_3957_;
v___y_3938_ = v___y_3952_;
v___y_3939_ = v___y_3953_;
v___y_3940_ = v___x_3958_;
v___y_3941_ = v___y_3955_;
v___y_3942_ = v___y_3954_;
v___y_3943_ = v___y_3956_;
v___y_3944_ = v___y_3951_;
goto v___jp_3933_;
}
}
v___jp_3961_:
{
uint64_t v___x_3973_; uint8_t v___x_3974_; 
v___x_3973_ = lean_uint64_shift_right(v___y_3962_, v___y_3967_);
v___x_3974_ = lean_uint64_dec_eq(v___x_3973_, v___y_3966_);
if (v___x_3974_ == 0)
{
uint64_t v___x_3975_; 
v___x_3975_ = lean_uint64_add(v___y_3971_, v___y_3967_);
v___y_3949_ = v___y_3963_;
v___y_3950_ = v___y_3964_;
v___y_3951_ = v___y_3972_;
v___y_3952_ = v___y_3965_;
v___y_3953_ = v___y_3966_;
v___y_3954_ = v___y_3969_;
v___y_3955_ = v___y_3968_;
v___y_3956_ = v___y_3970_;
v___y_3957_ = v___x_3975_;
goto v___jp_3948_;
}
else
{
v___y_3949_ = v___y_3963_;
v___y_3950_ = v___y_3964_;
v___y_3951_ = v___y_3972_;
v___y_3952_ = v___y_3965_;
v___y_3953_ = v___y_3966_;
v___y_3954_ = v___y_3969_;
v___y_3955_ = v___y_3968_;
v___y_3956_ = v___y_3970_;
v___y_3957_ = v___y_3971_;
goto v___jp_3948_;
}
}
v___jp_3976_:
{
uint64_t v___x_3986_; uint64_t v___x_3987_; uint8_t v___x_3988_; 
v___x_3986_ = 4ULL;
v___x_3987_ = lean_uint64_shift_right(v___y_3978_, v___x_3986_);
v___x_3988_ = lean_uint64_dec_eq(v___x_3987_, v___y_3981_);
if (v___x_3988_ == 0)
{
v___y_3962_ = v___y_3978_;
v___y_3963_ = v___y_3977_;
v___y_3964_ = v___y_3979_;
v___y_3965_ = v___y_3980_;
v___y_3966_ = v___y_3981_;
v___y_3967_ = v___x_3986_;
v___y_3968_ = v___y_3983_;
v___y_3969_ = v___y_3982_;
v___y_3970_ = v___y_3984_;
v___y_3971_ = v___y_3985_;
v___y_3972_ = v___x_3987_;
goto v___jp_3961_;
}
else
{
v___y_3962_ = v___y_3978_;
v___y_3963_ = v___y_3977_;
v___y_3964_ = v___y_3979_;
v___y_3965_ = v___y_3980_;
v___y_3966_ = v___y_3981_;
v___y_3967_ = v___x_3986_;
v___y_3968_ = v___y_3983_;
v___y_3969_ = v___y_3982_;
v___y_3970_ = v___y_3984_;
v___y_3971_ = v___y_3985_;
v___y_3972_ = v___y_3978_;
goto v___jp_3961_;
}
}
v___jp_3989_:
{
uint64_t v___x_4001_; uint8_t v___x_4002_; 
v___x_4001_ = lean_uint64_shift_right(v___y_3995_, v___y_3994_);
v___x_4002_ = lean_uint64_dec_eq(v___x_4001_, v___y_3993_);
if (v___x_4002_ == 0)
{
uint64_t v___x_4003_; 
v___x_4003_ = lean_uint64_add(v___y_3998_, v___y_3994_);
v___y_3977_ = v___y_3990_;
v___y_3978_ = v___y_4000_;
v___y_3979_ = v___y_3991_;
v___y_3980_ = v___y_3992_;
v___y_3981_ = v___y_3993_;
v___y_3982_ = v___y_3997_;
v___y_3983_ = v___y_3996_;
v___y_3984_ = v___y_3999_;
v___y_3985_ = v___x_4003_;
goto v___jp_3976_;
}
else
{
v___y_3977_ = v___y_3990_;
v___y_3978_ = v___y_4000_;
v___y_3979_ = v___y_3991_;
v___y_3980_ = v___y_3992_;
v___y_3981_ = v___y_3993_;
v___y_3982_ = v___y_3997_;
v___y_3983_ = v___y_3996_;
v___y_3984_ = v___y_3999_;
v___y_3985_ = v___y_3998_;
goto v___jp_3976_;
}
}
v___jp_4004_:
{
uint64_t v___x_4014_; uint64_t v___x_4015_; uint8_t v___x_4016_; 
v___x_4014_ = 8ULL;
v___x_4015_ = lean_uint64_shift_right(v___y_4011_, v___x_4014_);
v___x_4016_ = lean_uint64_dec_eq(v___x_4015_, v___y_4008_);
if (v___x_4016_ == 0)
{
v___y_3990_ = v___y_4005_;
v___y_3991_ = v___y_4006_;
v___y_3992_ = v___y_4007_;
v___y_3993_ = v___y_4008_;
v___y_3994_ = v___x_4014_;
v___y_3995_ = v___y_4011_;
v___y_3996_ = v___y_4010_;
v___y_3997_ = v___y_4009_;
v___y_3998_ = v___y_4013_;
v___y_3999_ = v___y_4012_;
v___y_4000_ = v___x_4015_;
goto v___jp_3989_;
}
else
{
v___y_3990_ = v___y_4005_;
v___y_3991_ = v___y_4006_;
v___y_3992_ = v___y_4007_;
v___y_3993_ = v___y_4008_;
v___y_3994_ = v___x_4014_;
v___y_3995_ = v___y_4011_;
v___y_3996_ = v___y_4010_;
v___y_3997_ = v___y_4009_;
v___y_3998_ = v___y_4013_;
v___y_3999_ = v___y_4012_;
v___y_4000_ = v___y_4011_;
goto v___jp_3989_;
}
}
v___jp_4017_:
{
uint64_t v___x_4029_; uint8_t v___x_4030_; 
v___x_4029_ = lean_uint64_shift_right(v___y_4026_, v___y_4020_);
v___x_4030_ = lean_uint64_dec_eq(v___x_4029_, v___y_4022_);
if (v___x_4030_ == 0)
{
uint64_t v___x_4031_; 
v___x_4031_ = lean_uint64_add(v___y_4025_, v___y_4020_);
v___y_4005_ = v___y_4018_;
v___y_4006_ = v___y_4019_;
v___y_4007_ = v___y_4021_;
v___y_4008_ = v___y_4022_;
v___y_4009_ = v___y_4024_;
v___y_4010_ = v___y_4023_;
v___y_4011_ = v___y_4028_;
v___y_4012_ = v___y_4027_;
v___y_4013_ = v___x_4031_;
goto v___jp_4004_;
}
else
{
v___y_4005_ = v___y_4018_;
v___y_4006_ = v___y_4019_;
v___y_4007_ = v___y_4021_;
v___y_4008_ = v___y_4022_;
v___y_4009_ = v___y_4024_;
v___y_4010_ = v___y_4023_;
v___y_4011_ = v___y_4028_;
v___y_4012_ = v___y_4027_;
v___y_4013_ = v___y_4025_;
goto v___jp_4004_;
}
}
v___jp_4032_:
{
uint64_t v___x_4042_; uint64_t v___x_4043_; uint8_t v___x_4044_; 
v___x_4042_ = 16ULL;
v___x_4043_ = lean_uint64_shift_right(v___y_4039_, v___x_4042_);
v___x_4044_ = lean_uint64_dec_eq(v___x_4043_, v___y_4036_);
if (v___x_4044_ == 0)
{
v___y_4018_ = v___y_4033_;
v___y_4019_ = v___y_4034_;
v___y_4020_ = v___x_4042_;
v___y_4021_ = v___y_4035_;
v___y_4022_ = v___y_4036_;
v___y_4023_ = v___y_4038_;
v___y_4024_ = v___y_4037_;
v___y_4025_ = v___y_4041_;
v___y_4026_ = v___y_4039_;
v___y_4027_ = v___y_4040_;
v___y_4028_ = v___x_4043_;
goto v___jp_4017_;
}
else
{
v___y_4018_ = v___y_4033_;
v___y_4019_ = v___y_4034_;
v___y_4020_ = v___x_4042_;
v___y_4021_ = v___y_4035_;
v___y_4022_ = v___y_4036_;
v___y_4023_ = v___y_4038_;
v___y_4024_ = v___y_4037_;
v___y_4025_ = v___y_4041_;
v___y_4026_ = v___y_4039_;
v___y_4027_ = v___y_4040_;
v___y_4028_ = v___y_4039_;
goto v___jp_4017_;
}
}
v___jp_4045_:
{
uint64_t v___x_4055_; uint64_t v___x_4056_; uint8_t v___x_4057_; 
v___x_4055_ = lean_unbox_uint64(v___y_4051_);
v___x_4056_ = lean_uint64_shift_right(v___x_4055_, v___y_4050_);
v___x_4057_ = lean_uint64_dec_eq(v___x_4056_, v___y_4049_);
if (v___x_4057_ == 0)
{
v___y_4033_ = v___y_4046_;
v___y_4034_ = v___y_4047_;
v___y_4035_ = v___y_4048_;
v___y_4036_ = v___y_4049_;
v___y_4037_ = v___y_4052_;
v___y_4038_ = v___y_4051_;
v___y_4039_ = v___y_4054_;
v___y_4040_ = v___y_4053_;
v___y_4041_ = v___y_4050_;
goto v___jp_4032_;
}
else
{
v___y_4033_ = v___y_4046_;
v___y_4034_ = v___y_4047_;
v___y_4035_ = v___y_4048_;
v___y_4036_ = v___y_4049_;
v___y_4037_ = v___y_4052_;
v___y_4038_ = v___y_4051_;
v___y_4039_ = v___y_4054_;
v___y_4040_ = v___y_4053_;
v___y_4041_ = v___y_4049_;
goto v___jp_4032_;
}
}
v___jp_4058_:
{
uint64_t v___x_4065_; uint64_t v___x_4066_; uint8_t v___x_4067_; 
v___x_4065_ = 0ULL;
v___x_4066_ = lean_unbox_uint64(v_snd_4064_);
v___x_4067_ = lean_uint64_dec_eq(v___x_4066_, v___x_4065_);
if (v___x_4067_ == 0)
{
uint64_t v___x_4068_; uint64_t v___x_4069_; uint64_t v___x_4070_; uint64_t v___x_4071_; uint8_t v___x_4072_; 
v___x_4068_ = lean_uint64_add(v___y_4061_, v___y_4062_);
v___x_4069_ = 32ULL;
v___x_4070_ = lean_unbox_uint64(v_snd_4064_);
v___x_4071_ = lean_uint64_shift_right(v___x_4070_, v___x_4069_);
v___x_4072_ = lean_uint64_dec_eq(v___x_4071_, v___x_4065_);
if (v___x_4072_ == 0)
{
v___y_4046_ = v___y_4059_;
v___y_4047_ = v___x_4068_;
v___y_4048_ = v___y_4060_;
v___y_4049_ = v___x_4065_;
v___y_4050_ = v___x_4069_;
v___y_4051_ = v_snd_4064_;
v___y_4052_ = v_fst_4063_;
v___y_4053_ = v___y_4062_;
v___y_4054_ = v___x_4071_;
goto v___jp_4045_;
}
else
{
uint64_t v___x_4073_; 
v___x_4073_ = lean_unbox_uint64(v_snd_4064_);
v___y_4046_ = v___y_4059_;
v___y_4047_ = v___x_4068_;
v___y_4048_ = v___y_4060_;
v___y_4049_ = v___x_4065_;
v___y_4050_ = v___x_4069_;
v___y_4051_ = v_snd_4064_;
v___y_4052_ = v_fst_4063_;
v___y_4053_ = v___y_4062_;
v___y_4054_ = v___x_4073_;
goto v___jp_4045_;
}
}
else
{
uint8_t v___x_4074_; 
lean_dec(v_snd_4064_);
v___x_4074_ = lean_unbox(v_fst_4063_);
lean_dec(v_fst_4063_);
if (v___x_4074_ == 0)
{
uint32_t v___x_4075_; 
v___x_4075_ = 0;
return v___x_4075_;
}
else
{
uint32_t v___x_4076_; 
v___x_4076_ = 2147483648;
return v___x_4076_;
}
}
}
v___jp_4077_:
{
uint8_t v___x_4087_; 
v___x_4087_ = lean_uint64_dec_eq(v___y_4080_, v___y_4085_);
if (v___x_4087_ == 0)
{
uint8_t v___x_4088_; 
v___x_4088_ = lean_uint64_dec_lt(v___y_4080_, v___y_4085_);
if (v___x_4088_ == 0)
{
uint64_t v___x_4089_; lean_object* v___x_4090_; lean_object* v___x_4091_; 
v___x_4089_ = lean_uint64_sub(v___y_4080_, v___y_4085_);
v___x_4090_ = lean_box(v___y_4084_);
v___x_4091_ = lean_box_uint64(v___x_4089_);
v___y_4059_ = v___y_4078_;
v___y_4060_ = v___y_4079_;
v___y_4061_ = v___y_4082_;
v___y_4062_ = v___y_4083_;
v_fst_4063_ = v___x_4090_;
v_snd_4064_ = v___x_4091_;
goto v___jp_4058_;
}
else
{
uint64_t v___x_4092_; lean_object* v___x_4093_; lean_object* v___x_4094_; 
v___x_4092_ = lean_uint64_sub(v___y_4085_, v___y_4080_);
v___x_4093_ = lean_box(v___y_4081_);
v___x_4094_ = lean_box_uint64(v___x_4092_);
v___y_4059_ = v___y_4078_;
v___y_4060_ = v___y_4079_;
v___y_4061_ = v___y_4082_;
v___y_4062_ = v___y_4083_;
v_fst_4063_ = v___x_4093_;
v_snd_4064_ = v___x_4094_;
goto v___jp_4058_;
}
}
else
{
lean_object* v___x_4095_; lean_object* v___x_4096_; 
v___x_4095_ = lean_box(v___y_4086_);
v___x_4096_ = ((lean_object*)(lp_competition_Submission_TunedAdd_core___boxed__const__1));
v___y_4059_ = v___y_4078_;
v___y_4060_ = v___y_4079_;
v___y_4061_ = v___y_4082_;
v___y_4062_ = v___y_4083_;
v_fst_4063_ = v___x_4095_;
v_snd_4064_ = v___x_4096_;
goto v___jp_4058_;
}
}
v___jp_4097_:
{
if (v___y_4106_ == 0)
{
v___y_4078_ = v___y_4098_;
v___y_4079_ = v___y_4100_;
v___y_4080_ = v___y_4099_;
v___y_4081_ = v___y_4101_;
v___y_4082_ = v___y_4102_;
v___y_4083_ = v___y_4103_;
v___y_4084_ = v___y_4104_;
v___y_4085_ = v___y_4105_;
v___y_4086_ = v___y_4106_;
goto v___jp_4077_;
}
else
{
uint64_t v___x_4107_; lean_object* v___x_4108_; lean_object* v___x_4109_; 
v___x_4107_ = lean_uint64_add(v___y_4099_, v___y_4105_);
v___x_4108_ = lean_box(v___y_4104_);
v___x_4109_ = lean_box_uint64(v___x_4107_);
v___y_4059_ = v___y_4098_;
v___y_4060_ = v___y_4100_;
v___y_4061_ = v___y_4102_;
v___y_4062_ = v___y_4103_;
v_fst_4063_ = v___x_4108_;
v_snd_4064_ = v___x_4109_;
goto v___jp_4058_;
}
}
v___jp_4110_:
{
uint8_t v___x_4120_; 
v___x_4120_ = lean_uint64_dec_le(v___y_4115_, v___y_4119_);
if (v___x_4120_ == 0)
{
uint64_t v_shift_4121_; uint64_t v___x_4122_; uint8_t v___x_4123_; 
v_shift_4121_ = lean_uint64_sub(v___y_4115_, v___y_4119_);
v___x_4122_ = 39ULL;
v___x_4123_ = lean_uint64_dec_le(v_shift_4121_, v___x_4122_);
if (v___x_4123_ == 0)
{
return v_a_2041_;
}
else
{
uint64_t v___x_4124_; 
v___x_4124_ = lean_uint64_shift_left(v___y_4112_, v_shift_4121_);
if (v___y_4118_ == 0)
{
if (v___y_4114_ == 0)
{
v___y_3791_ = v___y_4111_;
v___y_3792_ = v___y_4113_;
v___y_3793_ = v___y_4114_;
v___y_3794_ = v___x_4124_;
v___y_3795_ = v___y_4116_;
v___y_3796_ = v___y_4119_;
v___y_3797_ = v___y_4117_;
v___y_3798_ = v___y_4118_;
v___y_3799_ = v___x_4123_;
goto v___jp_3790_;
}
else
{
v___y_3771_ = v___y_4111_;
v___y_3772_ = v___y_4113_;
v___y_3773_ = v___y_4114_;
v___y_3774_ = v___x_4124_;
v___y_3775_ = v___y_4116_;
v___y_3776_ = v___y_4119_;
v___y_3777_ = v___y_4117_;
v___y_3778_ = v___y_4118_;
v___y_3779_ = v___y_4118_;
goto v___jp_3770_;
}
}
else
{
v___y_3791_ = v___y_4111_;
v___y_3792_ = v___y_4113_;
v___y_3793_ = v___y_4114_;
v___y_3794_ = v___x_4124_;
v___y_3795_ = v___y_4116_;
v___y_3796_ = v___y_4119_;
v___y_3797_ = v___y_4117_;
v___y_3798_ = v___y_4118_;
v___y_3799_ = v___y_4114_;
goto v___jp_3790_;
}
}
}
else
{
uint64_t v_shift_4125_; uint64_t v___x_4126_; uint8_t v___x_4127_; 
v_shift_4125_ = lean_uint64_sub(v___y_4119_, v___y_4115_);
v___x_4126_ = 39ULL;
v___x_4127_ = lean_uint64_dec_le(v_shift_4125_, v___x_4126_);
if (v___x_4127_ == 0)
{
return v_b_2042_;
}
else
{
uint64_t v___x_4128_; 
v___x_4128_ = lean_uint64_shift_left(v___y_4116_, v_shift_4125_);
if (v___y_4118_ == 0)
{
if (v___y_4114_ == 0)
{
v___y_4098_ = v___y_4111_;
v___y_4099_ = v___y_4112_;
v___y_4100_ = v___y_4113_;
v___y_4101_ = v___y_4114_;
v___y_4102_ = v___y_4115_;
v___y_4103_ = v___y_4117_;
v___y_4104_ = v___y_4118_;
v___y_4105_ = v___x_4128_;
v___y_4106_ = v___x_4127_;
goto v___jp_4097_;
}
else
{
v___y_4078_ = v___y_4111_;
v___y_4079_ = v___y_4113_;
v___y_4080_ = v___y_4112_;
v___y_4081_ = v___y_4114_;
v___y_4082_ = v___y_4115_;
v___y_4083_ = v___y_4117_;
v___y_4084_ = v___y_4118_;
v___y_4085_ = v___x_4128_;
v___y_4086_ = v___y_4118_;
goto v___jp_4077_;
}
}
else
{
v___y_4098_ = v___y_4111_;
v___y_4099_ = v___y_4112_;
v___y_4100_ = v___y_4113_;
v___y_4101_ = v___y_4114_;
v___y_4102_ = v___y_4115_;
v___y_4103_ = v___y_4117_;
v___y_4104_ = v___y_4118_;
v___y_4105_ = v___x_4128_;
v___y_4106_ = v___y_4114_;
goto v___jp_4097_;
}
}
}
}
v___jp_4129_:
{
uint64_t v___x_4139_; uint64_t v___x_4140_; uint8_t v___x_4141_; 
v___x_4139_ = lean_uint32_to_uint64(v___y_4131_);
v___x_4140_ = 0ULL;
v___x_4141_ = lean_uint64_dec_eq(v___x_4139_, v___x_4140_);
if (v___x_4141_ == 0)
{
uint64_t v___x_4142_; 
v___x_4142_ = lean_uint64_sub(v___x_4139_, v___y_4133_);
v___y_4111_ = v___y_4130_;
v___y_4112_ = v___y_4132_;
v___y_4113_ = v___y_4133_;
v___y_4114_ = v___y_4134_;
v___y_4115_ = v___y_4138_;
v___y_4116_ = v___y_4135_;
v___y_4117_ = v___y_4136_;
v___y_4118_ = v___y_4137_;
v___y_4119_ = v___x_4142_;
goto v___jp_4110_;
}
else
{
v___y_4111_ = v___y_4130_;
v___y_4112_ = v___y_4132_;
v___y_4113_ = v___y_4133_;
v___y_4114_ = v___y_4134_;
v___y_4115_ = v___y_4138_;
v___y_4116_ = v___y_4135_;
v___y_4117_ = v___y_4136_;
v___y_4118_ = v___y_4137_;
v___y_4119_ = v___x_4140_;
goto v___jp_4110_;
}
}
v___jp_4143_:
{
uint32_t v___x_4147_; uint32_t v___x_4148_; uint32_t v___x_4149_; uint32_t v___x_4150_; uint32_t v___x_4151_; uint32_t v___x_4152_; 
v___x_4147_ = lean_uint32_land(v___y_4144_, v___x_2261_);
v___x_4148_ = lean_uint32_shift_left(v___x_4147_, v___x_2259_);
v___x_4149_ = lean_uint32_lor(v___y_4146_, v___x_4148_);
v___x_4150_ = 8388607;
v___x_4151_ = lean_uint32_land(v___y_4145_, v___x_4150_);
v___x_4152_ = lean_uint32_lor(v___x_4149_, v___x_4151_);
return v___x_4152_;
}
v___jp_4153_:
{
uint8_t v___x_4157_; 
v___x_4157_ = lean_unbox(v___y_4155_);
lean_dec(v___y_4155_);
if (v___x_4157_ == 0)
{
uint32_t v___x_4158_; 
v___x_4158_ = 0;
v___y_4144_ = v___y_4154_;
v___y_4145_ = v___y_4156_;
v___y_4146_ = v___x_4158_;
goto v___jp_4143_;
}
else
{
uint32_t v___x_4159_; 
v___x_4159_ = 2147483648;
v___y_4144_ = v___y_4154_;
v___y_4145_ = v___y_4156_;
v___y_4146_ = v___x_4159_;
goto v___jp_4143_;
}
}
v___jp_4160_:
{
uint64_t v___x_4165_; uint64_t v_encodedExponent_4166_; uint32_t v___x_4167_; uint64_t v___x_4168_; uint8_t v___x_4169_; 
v___x_4165_ = 171ULL;
v_encodedExponent_4166_ = lean_uint64_sub(v___y_4162_, v___x_4165_);
v___x_4167_ = lean_uint64_to_uint32(v_encodedExponent_4166_);
v___x_4168_ = 8388608ULL;
v___x_4169_ = lean_uint64_dec_lt(v___y_4164_, v___x_4168_);
if (v___x_4169_ == 0)
{
uint64_t v___x_4170_; uint32_t v___x_4171_; 
v___x_4170_ = lean_uint64_sub(v___y_4164_, v___x_4168_);
v___x_4171_ = lean_uint64_to_uint32(v___x_4170_);
v___y_4154_ = v___x_4167_;
v___y_4155_ = v___y_4161_;
v___y_4156_ = v___x_4171_;
goto v___jp_4153_;
}
else
{
uint32_t v___x_4172_; 
v___x_4172_ = lean_uint64_to_uint32(v___y_4163_);
v___y_4154_ = v___x_4167_;
v___y_4155_ = v___y_4161_;
v___y_4156_ = v___x_4172_;
goto v___jp_4153_;
}
}
v___jp_4173_:
{
uint64_t v___x_4179_; uint8_t v___x_4180_; 
v___x_4179_ = 425ULL;
v___x_4180_ = lean_uint64_dec_lt(v___x_4179_, v___y_4178_);
if (v___x_4180_ == 0)
{
if (v___y_4176_ == 0)
{
v___y_4161_ = v___y_4174_;
v___y_4162_ = v___y_4178_;
v___y_4163_ = v___y_4177_;
v___y_4164_ = v___y_4175_;
goto v___jp_4160_;
}
else
{
uint64_t v___x_4181_; 
v___x_4181_ = 8388608ULL;
v___y_4161_ = v___y_4174_;
v___y_4162_ = v___y_4178_;
v___y_4163_ = v___y_4177_;
v___y_4164_ = v___x_4181_;
goto v___jp_4160_;
}
}
else
{
uint8_t v___x_4182_; 
v___x_4182_ = lean_unbox(v___y_4174_);
lean_dec(v___y_4174_);
if (v___x_4182_ == 0)
{
uint32_t v___x_4183_; 
v___x_4183_ = 2139095040;
return v___x_4183_;
}
else
{
uint32_t v___x_4184_; 
v___x_4184_ = 4286578688;
return v___x_4184_;
}
}
}
v___jp_4185_:
{
uint64_t v___x_4191_; uint8_t v_carry_4192_; 
v___x_4191_ = 16777216ULL;
v_carry_4192_ = lean_uint64_dec_eq(v___y_4190_, v___x_4191_);
if (v_carry_4192_ == 0)
{
v___y_4174_ = v___y_4186_;
v___y_4175_ = v___y_4190_;
v___y_4176_ = v_carry_4192_;
v___y_4177_ = v___y_4188_;
v___y_4178_ = v___y_4189_;
goto v___jp_4173_;
}
else
{
uint64_t v___x_4193_; 
v___x_4193_ = lean_uint64_add(v___y_4189_, v___y_4187_);
v___y_4174_ = v___y_4186_;
v___y_4175_ = v___y_4190_;
v___y_4176_ = v_carry_4192_;
v___y_4177_ = v___y_4188_;
v___y_4178_ = v___x_4193_;
goto v___jp_4173_;
}
}
v___jp_4194_:
{
uint64_t v_position_4202_; uint64_t v___x_4203_; uint8_t v___x_4204_; 
v_position_4202_ = lean_uint64_add(v___y_4201_, v___y_4200_);
v___x_4203_ = 172ULL;
v___x_4204_ = lean_uint64_dec_lt(v_position_4202_, v___x_4203_);
if (v___x_4204_ == 0)
{
uint64_t v___x_4205_; uint8_t v___x_4206_; 
v___x_4205_ = 23ULL;
v___x_4206_ = lean_uint64_dec_lt(v___y_4201_, v___x_4205_);
if (v___x_4206_ == 0)
{
uint64_t v___x_4207_; uint8_t v___x_4208_; 
v___x_4207_ = lean_uint64_sub(v___y_4201_, v___x_4205_);
v___x_4208_ = lean_uint64_dec_eq(v___x_4207_, v___y_4198_);
if (v___x_4208_ == 0)
{
uint64_t v___x_4209_; uint8_t v___x_4210_; 
v___x_4209_ = 64ULL;
v___x_4210_ = lean_uint64_dec_lt(v___x_4207_, v___x_4209_);
if (v___x_4210_ == 0)
{
uint8_t v___x_4211_; 
v___x_4211_ = lean_uint64_dec_eq(v___x_4207_, v___x_4209_);
if (v___x_4211_ == 0)
{
lean_dec(v___y_4197_);
v___y_4186_ = v___y_4195_;
v___y_4187_ = v___y_4196_;
v___y_4188_ = v___y_4198_;
v___y_4189_ = v_position_4202_;
v___y_4190_ = v___y_4198_;
goto v___jp_4185_;
}
else
{
uint64_t v___x_4212_; uint64_t v___x_4213_; uint8_t v___x_4214_; 
v___x_4212_ = 9223372036854775808ULL;
v___x_4213_ = lean_unbox_uint64(v___y_4197_);
lean_dec(v___y_4197_);
v___x_4214_ = lean_uint64_dec_lt(v___x_4212_, v___x_4213_);
if (v___x_4214_ == 0)
{
v___y_4186_ = v___y_4195_;
v___y_4187_ = v___y_4196_;
v___y_4188_ = v___y_4198_;
v___y_4189_ = v_position_4202_;
v___y_4190_ = v___y_4198_;
goto v___jp_4185_;
}
else
{
v___y_4186_ = v___y_4195_;
v___y_4187_ = v___y_4196_;
v___y_4188_ = v___y_4198_;
v___y_4189_ = v_position_4202_;
v___y_4190_ = v___y_4196_;
goto v___jp_4185_;
}
}
}
else
{
uint64_t v___x_4215_; uint64_t v_quotient_4216_; uint64_t v___x_4217_; uint64_t v___x_4218_; uint64_t v___x_4219_; uint64_t v_remainder_4220_; uint64_t v___x_4221_; uint64_t v_half_4222_; uint8_t v___x_4223_; 
v___x_4215_ = lean_unbox_uint64(v___y_4197_);
v_quotient_4216_ = lean_uint64_shift_right(v___x_4215_, v___x_4207_);
v___x_4217_ = lean_uint64_shift_left(v___y_4196_, v___x_4207_);
v___x_4218_ = lean_uint64_sub(v___x_4217_, v___y_4196_);
v___x_4219_ = lean_unbox_uint64(v___y_4197_);
lean_dec(v___y_4197_);
v_remainder_4220_ = lean_uint64_land(v___x_4219_, v___x_4218_);
v___x_4221_ = lean_uint64_sub(v___x_4207_, v___y_4196_);
v_half_4222_ = lean_uint64_shift_left(v___y_4196_, v___x_4221_);
v___x_4223_ = lean_uint64_dec_lt(v_remainder_4220_, v_half_4222_);
if (v___x_4223_ == 0)
{
uint8_t v___x_4224_; 
v___x_4224_ = lean_uint64_dec_lt(v_half_4222_, v_remainder_4220_);
if (v___x_4224_ == 0)
{
uint64_t v___x_4225_; uint8_t v___x_4226_; 
v___x_4225_ = lean_uint64_land(v_quotient_4216_, v___y_4196_);
v___x_4226_ = lean_uint64_dec_eq(v___x_4225_, v___y_4198_);
if (v___x_4226_ == 0)
{
uint64_t v___x_4227_; 
v___x_4227_ = lean_uint64_add(v_quotient_4216_, v___y_4196_);
v___y_4186_ = v___y_4195_;
v___y_4187_ = v___y_4196_;
v___y_4188_ = v___y_4198_;
v___y_4189_ = v_position_4202_;
v___y_4190_ = v___x_4227_;
goto v___jp_4185_;
}
else
{
v___y_4186_ = v___y_4195_;
v___y_4187_ = v___y_4196_;
v___y_4188_ = v___y_4198_;
v___y_4189_ = v_position_4202_;
v___y_4190_ = v_quotient_4216_;
goto v___jp_4185_;
}
}
else
{
uint64_t v___x_4228_; 
v___x_4228_ = lean_uint64_add(v_quotient_4216_, v___y_4196_);
v___y_4186_ = v___y_4195_;
v___y_4187_ = v___y_4196_;
v___y_4188_ = v___y_4198_;
v___y_4189_ = v_position_4202_;
v___y_4190_ = v___x_4228_;
goto v___jp_4185_;
}
}
else
{
v___y_4186_ = v___y_4195_;
v___y_4187_ = v___y_4196_;
v___y_4188_ = v___y_4198_;
v___y_4189_ = v_position_4202_;
v___y_4190_ = v_quotient_4216_;
goto v___jp_4185_;
}
}
}
else
{
uint64_t v___x_4229_; 
v___x_4229_ = lean_unbox_uint64(v___y_4197_);
lean_dec(v___y_4197_);
v___y_4186_ = v___y_4195_;
v___y_4187_ = v___y_4196_;
v___y_4188_ = v___y_4198_;
v___y_4189_ = v_position_4202_;
v___y_4190_ = v___x_4229_;
goto v___jp_4185_;
}
}
else
{
uint64_t v___x_4230_; uint64_t v___x_4231_; uint64_t v___x_4232_; 
v___x_4230_ = lean_uint64_sub(v___x_4205_, v___y_4201_);
v___x_4231_ = lean_unbox_uint64(v___y_4197_);
lean_dec(v___y_4197_);
v___x_4232_ = lean_uint64_shift_left(v___x_4231_, v___x_4230_);
v___y_4186_ = v___y_4195_;
v___y_4187_ = v___y_4196_;
v___y_4188_ = v___y_4198_;
v___y_4189_ = v_position_4202_;
v___y_4190_ = v___x_4232_;
goto v___jp_4185_;
}
}
else
{
uint8_t v___x_4233_; 
v___x_4233_ = lean_uint64_dec_lt(v___y_4200_, v___y_4199_);
if (v___x_4233_ == 0)
{
uint64_t v___x_4234_; uint64_t v___x_4235_; uint64_t v___x_4236_; 
v___x_4234_ = lean_uint64_sub(v___y_4200_, v___y_4199_);
v___x_4235_ = lean_unbox_uint64(v___y_4197_);
lean_dec(v___y_4197_);
v___x_4236_ = lean_uint64_shift_left(v___x_4235_, v___x_4234_);
v___y_2222_ = v___y_4195_;
v___y_2223_ = v___y_4198_;
v___y_2224_ = v___x_4236_;
goto v___jp_2221_;
}
else
{
uint64_t v___x_4237_; uint8_t v___x_4238_; 
v___x_4237_ = lean_uint64_sub(v___y_4199_, v___y_4200_);
v___x_4238_ = lean_uint64_dec_eq(v___x_4237_, v___y_4198_);
if (v___x_4238_ == 0)
{
uint64_t v___x_4239_; uint8_t v___x_4240_; 
v___x_4239_ = 64ULL;
v___x_4240_ = lean_uint64_dec_lt(v___x_4237_, v___x_4239_);
if (v___x_4240_ == 0)
{
uint8_t v___x_4241_; 
v___x_4241_ = lean_uint64_dec_eq(v___x_4237_, v___x_4239_);
if (v___x_4241_ == 0)
{
lean_dec(v___y_4197_);
v___y_2222_ = v___y_4195_;
v___y_2223_ = v___y_4198_;
v___y_2224_ = v___y_4198_;
goto v___jp_2221_;
}
else
{
uint64_t v___x_4242_; uint64_t v___x_4243_; uint8_t v___x_4244_; 
v___x_4242_ = 9223372036854775808ULL;
v___x_4243_ = lean_unbox_uint64(v___y_4197_);
lean_dec(v___y_4197_);
v___x_4244_ = lean_uint64_dec_lt(v___x_4242_, v___x_4243_);
if (v___x_4244_ == 0)
{
v___y_2222_ = v___y_4195_;
v___y_2223_ = v___y_4198_;
v___y_2224_ = v___y_4198_;
goto v___jp_2221_;
}
else
{
v___y_2222_ = v___y_4195_;
v___y_2223_ = v___y_4198_;
v___y_2224_ = v___y_4196_;
goto v___jp_2221_;
}
}
}
else
{
uint64_t v___x_4245_; uint64_t v_quotient_4246_; uint64_t v___x_4247_; uint64_t v___x_4248_; uint64_t v___x_4249_; uint64_t v_remainder_4250_; uint64_t v___x_4251_; uint64_t v_half_4252_; uint8_t v___x_4253_; 
v___x_4245_ = lean_unbox_uint64(v___y_4197_);
v_quotient_4246_ = lean_uint64_shift_right(v___x_4245_, v___x_4237_);
v___x_4247_ = lean_uint64_shift_left(v___y_4196_, v___x_4237_);
v___x_4248_ = lean_uint64_sub(v___x_4247_, v___y_4196_);
v___x_4249_ = lean_unbox_uint64(v___y_4197_);
lean_dec(v___y_4197_);
v_remainder_4250_ = lean_uint64_land(v___x_4249_, v___x_4248_);
v___x_4251_ = lean_uint64_sub(v___x_4237_, v___y_4196_);
v_half_4252_ = lean_uint64_shift_left(v___y_4196_, v___x_4251_);
v___x_4253_ = lean_uint64_dec_lt(v_remainder_4250_, v_half_4252_);
if (v___x_4253_ == 0)
{
uint8_t v___x_4254_; 
v___x_4254_ = lean_uint64_dec_lt(v_half_4252_, v_remainder_4250_);
if (v___x_4254_ == 0)
{
uint64_t v___x_4255_; uint8_t v___x_4256_; 
v___x_4255_ = lean_uint64_land(v_quotient_4246_, v___y_4196_);
v___x_4256_ = lean_uint64_dec_eq(v___x_4255_, v___y_4198_);
if (v___x_4256_ == 0)
{
uint64_t v___x_4257_; 
v___x_4257_ = lean_uint64_add(v_quotient_4246_, v___y_4196_);
v___y_2222_ = v___y_4195_;
v___y_2223_ = v___y_4198_;
v___y_2224_ = v___x_4257_;
goto v___jp_2221_;
}
else
{
v___y_2222_ = v___y_4195_;
v___y_2223_ = v___y_4198_;
v___y_2224_ = v_quotient_4246_;
goto v___jp_2221_;
}
}
else
{
uint64_t v___x_4258_; 
v___x_4258_ = lean_uint64_add(v_quotient_4246_, v___y_4196_);
v___y_2222_ = v___y_4195_;
v___y_2223_ = v___y_4198_;
v___y_2224_ = v___x_4258_;
goto v___jp_2221_;
}
}
else
{
v___y_2222_ = v___y_4195_;
v___y_2223_ = v___y_4198_;
v___y_2224_ = v_quotient_4246_;
goto v___jp_2221_;
}
}
}
else
{
uint64_t v___x_4259_; 
v___x_4259_ = lean_unbox_uint64(v___y_4197_);
lean_dec(v___y_4197_);
v___y_2222_ = v___y_4195_;
v___y_2223_ = v___y_4198_;
v___y_2224_ = v___x_4259_;
goto v___jp_2221_;
}
}
}
}
v___jp_4260_:
{
uint64_t v___x_4269_; uint8_t v___x_4270_; 
v___x_4269_ = lean_uint64_shift_right(v___y_4263_, v___y_4262_);
v___x_4270_ = lean_uint64_dec_eq(v___x_4269_, v___y_4265_);
if (v___x_4270_ == 0)
{
uint64_t v___x_4271_; 
v___x_4271_ = lean_uint64_add(v___y_4268_, v___y_4262_);
v___y_4195_ = v___y_4261_;
v___y_4196_ = v___y_4262_;
v___y_4197_ = v___y_4264_;
v___y_4198_ = v___y_4265_;
v___y_4199_ = v___y_4266_;
v___y_4200_ = v___y_4267_;
v___y_4201_ = v___x_4271_;
goto v___jp_4194_;
}
else
{
v___y_4195_ = v___y_4261_;
v___y_4196_ = v___y_4262_;
v___y_4197_ = v___y_4264_;
v___y_4198_ = v___y_4265_;
v___y_4199_ = v___y_4266_;
v___y_4200_ = v___y_4267_;
v___y_4201_ = v___y_4268_;
goto v___jp_4194_;
}
}
v___jp_4272_:
{
uint64_t v___x_4283_; uint8_t v___x_4284_; 
v___x_4283_ = lean_uint64_shift_right(v___y_4273_, v___y_4281_);
v___x_4284_ = lean_uint64_dec_eq(v___x_4283_, v___y_4277_);
if (v___x_4284_ == 0)
{
uint64_t v___x_4285_; 
v___x_4285_ = lean_uint64_add(v___y_4278_, v___y_4281_);
v___y_4261_ = v___y_4274_;
v___y_4262_ = v___y_4275_;
v___y_4263_ = v___y_4282_;
v___y_4264_ = v___y_4276_;
v___y_4265_ = v___y_4277_;
v___y_4266_ = v___y_4279_;
v___y_4267_ = v___y_4280_;
v___y_4268_ = v___x_4285_;
goto v___jp_4260_;
}
else
{
v___y_4261_ = v___y_4274_;
v___y_4262_ = v___y_4275_;
v___y_4263_ = v___y_4282_;
v___y_4264_ = v___y_4276_;
v___y_4265_ = v___y_4277_;
v___y_4266_ = v___y_4279_;
v___y_4267_ = v___y_4280_;
v___y_4268_ = v___y_4278_;
goto v___jp_4260_;
}
}
v___jp_4286_:
{
uint64_t v___x_4295_; uint64_t v___x_4296_; uint8_t v___x_4297_; 
v___x_4295_ = 2ULL;
v___x_4296_ = lean_uint64_shift_right(v___y_4287_, v___x_4295_);
v___x_4297_ = lean_uint64_dec_eq(v___x_4296_, v___y_4291_);
if (v___x_4297_ == 0)
{
v___y_4273_ = v___y_4287_;
v___y_4274_ = v___y_4288_;
v___y_4275_ = v___y_4289_;
v___y_4276_ = v___y_4290_;
v___y_4277_ = v___y_4291_;
v___y_4278_ = v___y_4294_;
v___y_4279_ = v___y_4292_;
v___y_4280_ = v___y_4293_;
v___y_4281_ = v___x_4295_;
v___y_4282_ = v___x_4296_;
goto v___jp_4272_;
}
else
{
v___y_4273_ = v___y_4287_;
v___y_4274_ = v___y_4288_;
v___y_4275_ = v___y_4289_;
v___y_4276_ = v___y_4290_;
v___y_4277_ = v___y_4291_;
v___y_4278_ = v___y_4294_;
v___y_4279_ = v___y_4292_;
v___y_4280_ = v___y_4293_;
v___y_4281_ = v___x_4295_;
v___y_4282_ = v___y_4287_;
goto v___jp_4272_;
}
}
v___jp_4298_:
{
uint64_t v___x_4309_; uint8_t v___x_4310_; 
v___x_4309_ = lean_uint64_shift_right(v___y_4301_, v___y_4303_);
v___x_4310_ = lean_uint64_dec_eq(v___x_4309_, v___y_4304_);
if (v___x_4310_ == 0)
{
uint64_t v___x_4311_; 
v___x_4311_ = lean_uint64_add(v___y_4305_, v___y_4303_);
v___y_4287_ = v___y_4308_;
v___y_4288_ = v___y_4299_;
v___y_4289_ = v___y_4300_;
v___y_4290_ = v___y_4302_;
v___y_4291_ = v___y_4304_;
v___y_4292_ = v___y_4306_;
v___y_4293_ = v___y_4307_;
v___y_4294_ = v___x_4311_;
goto v___jp_4286_;
}
else
{
v___y_4287_ = v___y_4308_;
v___y_4288_ = v___y_4299_;
v___y_4289_ = v___y_4300_;
v___y_4290_ = v___y_4302_;
v___y_4291_ = v___y_4304_;
v___y_4292_ = v___y_4306_;
v___y_4293_ = v___y_4307_;
v___y_4294_ = v___y_4305_;
goto v___jp_4286_;
}
}
v___jp_4312_:
{
uint64_t v___x_4321_; uint64_t v___x_4322_; uint8_t v___x_4323_; 
v___x_4321_ = 4ULL;
v___x_4322_ = lean_uint64_shift_right(v___y_4316_, v___x_4321_);
v___x_4323_ = lean_uint64_dec_eq(v___x_4322_, v___y_4317_);
if (v___x_4323_ == 0)
{
v___y_4299_ = v___y_4313_;
v___y_4300_ = v___y_4314_;
v___y_4301_ = v___y_4316_;
v___y_4302_ = v___y_4315_;
v___y_4303_ = v___x_4321_;
v___y_4304_ = v___y_4317_;
v___y_4305_ = v___y_4320_;
v___y_4306_ = v___y_4318_;
v___y_4307_ = v___y_4319_;
v___y_4308_ = v___x_4322_;
goto v___jp_4298_;
}
else
{
v___y_4299_ = v___y_4313_;
v___y_4300_ = v___y_4314_;
v___y_4301_ = v___y_4316_;
v___y_4302_ = v___y_4315_;
v___y_4303_ = v___x_4321_;
v___y_4304_ = v___y_4317_;
v___y_4305_ = v___y_4320_;
v___y_4306_ = v___y_4318_;
v___y_4307_ = v___y_4319_;
v___y_4308_ = v___y_4316_;
goto v___jp_4298_;
}
}
v___jp_4324_:
{
uint64_t v___x_4335_; uint8_t v___x_4336_; 
v___x_4335_ = lean_uint64_shift_right(v___y_4332_, v___y_4326_);
v___x_4336_ = lean_uint64_dec_eq(v___x_4335_, v___y_4330_);
if (v___x_4336_ == 0)
{
uint64_t v___x_4337_; 
v___x_4337_ = lean_uint64_add(v___y_4328_, v___y_4326_);
v___y_4313_ = v___y_4325_;
v___y_4314_ = v___y_4327_;
v___y_4315_ = v___y_4329_;
v___y_4316_ = v___y_4334_;
v___y_4317_ = v___y_4330_;
v___y_4318_ = v___y_4331_;
v___y_4319_ = v___y_4333_;
v___y_4320_ = v___x_4337_;
goto v___jp_4312_;
}
else
{
v___y_4313_ = v___y_4325_;
v___y_4314_ = v___y_4327_;
v___y_4315_ = v___y_4329_;
v___y_4316_ = v___y_4334_;
v___y_4317_ = v___y_4330_;
v___y_4318_ = v___y_4331_;
v___y_4319_ = v___y_4333_;
v___y_4320_ = v___y_4328_;
goto v___jp_4312_;
}
}
v___jp_4338_:
{
uint64_t v___x_4347_; uint64_t v___x_4348_; uint8_t v___x_4349_; 
v___x_4347_ = 8ULL;
v___x_4348_ = lean_uint64_shift_right(v___y_4344_, v___x_4347_);
v___x_4349_ = lean_uint64_dec_eq(v___x_4348_, v___y_4342_);
if (v___x_4349_ == 0)
{
v___y_4325_ = v___y_4339_;
v___y_4326_ = v___x_4347_;
v___y_4327_ = v___y_4340_;
v___y_4328_ = v___y_4346_;
v___y_4329_ = v___y_4341_;
v___y_4330_ = v___y_4342_;
v___y_4331_ = v___y_4343_;
v___y_4332_ = v___y_4344_;
v___y_4333_ = v___y_4345_;
v___y_4334_ = v___x_4348_;
goto v___jp_4324_;
}
else
{
v___y_4325_ = v___y_4339_;
v___y_4326_ = v___x_4347_;
v___y_4327_ = v___y_4340_;
v___y_4328_ = v___y_4346_;
v___y_4329_ = v___y_4341_;
v___y_4330_ = v___y_4342_;
v___y_4331_ = v___y_4343_;
v___y_4332_ = v___y_4344_;
v___y_4333_ = v___y_4345_;
v___y_4334_ = v___y_4344_;
goto v___jp_4324_;
}
}
v___jp_4350_:
{
uint64_t v___x_4361_; uint8_t v___x_4362_; 
v___x_4361_ = lean_uint64_shift_right(v___y_4352_, v___y_4355_);
v___x_4362_ = lean_uint64_dec_eq(v___x_4361_, v___y_4357_);
if (v___x_4362_ == 0)
{
uint64_t v___x_4363_; 
v___x_4363_ = lean_uint64_add(v___y_4351_, v___y_4355_);
v___y_4339_ = v___y_4353_;
v___y_4340_ = v___y_4354_;
v___y_4341_ = v___y_4356_;
v___y_4342_ = v___y_4357_;
v___y_4343_ = v___y_4358_;
v___y_4344_ = v___y_4360_;
v___y_4345_ = v___y_4359_;
v___y_4346_ = v___x_4363_;
goto v___jp_4338_;
}
else
{
v___y_4339_ = v___y_4353_;
v___y_4340_ = v___y_4354_;
v___y_4341_ = v___y_4356_;
v___y_4342_ = v___y_4357_;
v___y_4343_ = v___y_4358_;
v___y_4344_ = v___y_4360_;
v___y_4345_ = v___y_4359_;
v___y_4346_ = v___y_4351_;
goto v___jp_4338_;
}
}
v___jp_4364_:
{
uint64_t v___x_4373_; uint64_t v___x_4374_; uint8_t v___x_4375_; 
v___x_4373_ = 16ULL;
v___x_4374_ = lean_uint64_shift_right(v___y_4365_, v___x_4373_);
v___x_4375_ = lean_uint64_dec_eq(v___x_4374_, v___y_4369_);
if (v___x_4375_ == 0)
{
v___y_4351_ = v___y_4372_;
v___y_4352_ = v___y_4365_;
v___y_4353_ = v___y_4366_;
v___y_4354_ = v___y_4367_;
v___y_4355_ = v___x_4373_;
v___y_4356_ = v___y_4368_;
v___y_4357_ = v___y_4369_;
v___y_4358_ = v___y_4370_;
v___y_4359_ = v___y_4371_;
v___y_4360_ = v___x_4374_;
goto v___jp_4350_;
}
else
{
v___y_4351_ = v___y_4372_;
v___y_4352_ = v___y_4365_;
v___y_4353_ = v___y_4366_;
v___y_4354_ = v___y_4367_;
v___y_4355_ = v___x_4373_;
v___y_4356_ = v___y_4368_;
v___y_4357_ = v___y_4369_;
v___y_4358_ = v___y_4370_;
v___y_4359_ = v___y_4371_;
v___y_4360_ = v___y_4365_;
goto v___jp_4350_;
}
}
v___jp_4376_:
{
uint64_t v___x_4385_; uint64_t v___x_4386_; uint8_t v___x_4387_; 
v___x_4385_ = lean_unbox_uint64(v___y_4379_);
v___x_4386_ = lean_uint64_shift_right(v___x_4385_, v___y_4382_);
v___x_4387_ = lean_uint64_dec_eq(v___x_4386_, v___y_4380_);
if (v___x_4387_ == 0)
{
v___y_4365_ = v___y_4384_;
v___y_4366_ = v___y_4377_;
v___y_4367_ = v___y_4378_;
v___y_4368_ = v___y_4379_;
v___y_4369_ = v___y_4380_;
v___y_4370_ = v___y_4381_;
v___y_4371_ = v___y_4383_;
v___y_4372_ = v___y_4382_;
goto v___jp_4364_;
}
else
{
v___y_4365_ = v___y_4384_;
v___y_4366_ = v___y_4377_;
v___y_4367_ = v___y_4378_;
v___y_4368_ = v___y_4379_;
v___y_4369_ = v___y_4380_;
v___y_4370_ = v___y_4381_;
v___y_4371_ = v___y_4383_;
v___y_4372_ = v___y_4380_;
goto v___jp_4364_;
}
}
v___jp_4388_:
{
uint64_t v___x_4393_; uint64_t v___x_4394_; uint8_t v___x_4395_; 
v___x_4393_ = 0ULL;
v___x_4394_ = lean_unbox_uint64(v_snd_4392_);
v___x_4395_ = lean_uint64_dec_eq(v___x_4394_, v___x_4393_);
if (v___x_4395_ == 0)
{
uint64_t v___x_4396_; uint64_t v___x_4397_; uint64_t v___x_4398_; uint64_t v___x_4399_; uint64_t v___x_4400_; uint8_t v___x_4401_; 
v___x_4396_ = 149ULL;
v___x_4397_ = lean_uint64_add(v___y_4390_, v___x_4396_);
v___x_4398_ = 32ULL;
v___x_4399_ = lean_unbox_uint64(v_snd_4392_);
v___x_4400_ = lean_uint64_shift_right(v___x_4399_, v___x_4398_);
v___x_4401_ = lean_uint64_dec_eq(v___x_4400_, v___x_4393_);
if (v___x_4401_ == 0)
{
v___y_4377_ = v_fst_4391_;
v___y_4378_ = v___y_4389_;
v___y_4379_ = v_snd_4392_;
v___y_4380_ = v___x_4393_;
v___y_4381_ = v___x_4396_;
v___y_4382_ = v___x_4398_;
v___y_4383_ = v___x_4397_;
v___y_4384_ = v___x_4400_;
goto v___jp_4376_;
}
else
{
uint64_t v___x_4402_; 
v___x_4402_ = lean_unbox_uint64(v_snd_4392_);
v___y_4377_ = v_fst_4391_;
v___y_4378_ = v___y_4389_;
v___y_4379_ = v_snd_4392_;
v___y_4380_ = v___x_4393_;
v___y_4381_ = v___x_4396_;
v___y_4382_ = v___x_4398_;
v___y_4383_ = v___x_4397_;
v___y_4384_ = v___x_4402_;
goto v___jp_4376_;
}
}
else
{
uint8_t v___x_4403_; 
lean_dec(v_snd_4392_);
v___x_4403_ = lean_unbox(v_fst_4391_);
lean_dec(v_fst_4391_);
if (v___x_4403_ == 0)
{
uint32_t v___x_4404_; 
v___x_4404_ = 0;
return v___x_4404_;
}
else
{
uint32_t v___x_4405_; 
v___x_4405_ = 2147483648;
return v___x_4405_;
}
}
}
v___jp_4406_:
{
uint8_t v___x_4414_; 
v___x_4414_ = lean_uint64_dec_eq(v___y_4409_, v___y_4407_);
if (v___x_4414_ == 0)
{
uint8_t v___x_4415_; 
v___x_4415_ = lean_uint64_dec_lt(v___y_4409_, v___y_4407_);
if (v___x_4415_ == 0)
{
uint64_t v___x_4416_; lean_object* v___x_4417_; lean_object* v___x_4418_; 
v___x_4416_ = lean_uint64_sub(v___y_4409_, v___y_4407_);
v___x_4417_ = lean_box(v___y_4411_);
v___x_4418_ = lean_box_uint64(v___x_4416_);
v___y_4389_ = v___y_4410_;
v___y_4390_ = v___y_4412_;
v_fst_4391_ = v___x_4417_;
v_snd_4392_ = v___x_4418_;
goto v___jp_4388_;
}
else
{
uint64_t v___x_4419_; lean_object* v___x_4420_; lean_object* v___x_4421_; 
v___x_4419_ = lean_uint64_sub(v___y_4407_, v___y_4409_);
v___x_4420_ = lean_box(v___y_4408_);
v___x_4421_ = lean_box_uint64(v___x_4419_);
v___y_4389_ = v___y_4410_;
v___y_4390_ = v___y_4412_;
v_fst_4391_ = v___x_4420_;
v_snd_4392_ = v___x_4421_;
goto v___jp_4388_;
}
}
else
{
lean_object* v___x_4422_; lean_object* v___x_4423_; 
v___x_4422_ = lean_box(v___y_4413_);
v___x_4423_ = ((lean_object*)(lp_competition_Submission_TunedAdd_core___boxed__const__1));
v___y_4389_ = v___y_4410_;
v___y_4390_ = v___y_4412_;
v_fst_4391_ = v___x_4422_;
v_snd_4392_ = v___x_4423_;
goto v___jp_4388_;
}
}
v___jp_4424_:
{
if (v___y_4431_ == 0)
{
v___y_4407_ = v___y_4425_;
v___y_4408_ = v___y_4427_;
v___y_4409_ = v___y_4426_;
v___y_4410_ = v___y_4428_;
v___y_4411_ = v___y_4429_;
v___y_4412_ = v___y_4430_;
v___y_4413_ = v___y_4431_;
goto v___jp_4406_;
}
else
{
uint64_t v___x_4432_; lean_object* v___x_4433_; lean_object* v___x_4434_; 
v___x_4432_ = lean_uint64_add(v___y_4426_, v___y_4425_);
v___x_4433_ = lean_box(v___y_4429_);
v___x_4434_ = lean_box_uint64(v___x_4432_);
v___y_4389_ = v___y_4428_;
v___y_4390_ = v___y_4430_;
v_fst_4391_ = v___x_4433_;
v_snd_4392_ = v___x_4434_;
goto v___jp_4388_;
}
}
v___jp_4435_:
{
uint32_t v___x_4439_; uint32_t v___x_4440_; uint32_t v___x_4441_; uint32_t v___x_4442_; uint32_t v___x_4443_; uint32_t v___x_4444_; 
v___x_4439_ = lean_uint32_land(v___y_4436_, v___x_2261_);
v___x_4440_ = lean_uint32_shift_left(v___x_4439_, v___x_2259_);
v___x_4441_ = lean_uint32_lor(v___y_4438_, v___x_4440_);
v___x_4442_ = 8388607;
v___x_4443_ = lean_uint32_land(v___y_4437_, v___x_4442_);
v___x_4444_ = lean_uint32_lor(v___x_4441_, v___x_4443_);
return v___x_4444_;
}
v___jp_4445_:
{
uint8_t v___x_4449_; 
v___x_4449_ = lean_unbox(v___y_4447_);
lean_dec(v___y_4447_);
if (v___x_4449_ == 0)
{
uint32_t v___x_4450_; 
v___x_4450_ = 0;
v___y_4436_ = v___y_4446_;
v___y_4437_ = v___y_4448_;
v___y_4438_ = v___x_4450_;
goto v___jp_4435_;
}
else
{
uint32_t v___x_4451_; 
v___x_4451_ = 2147483648;
v___y_4436_ = v___y_4446_;
v___y_4437_ = v___y_4448_;
v___y_4438_ = v___x_4451_;
goto v___jp_4435_;
}
}
v___jp_4452_:
{
uint64_t v___x_4457_; uint64_t v_encodedExponent_4458_; uint32_t v___x_4459_; uint64_t v___x_4460_; uint8_t v___x_4461_; 
v___x_4457_ = 171ULL;
v_encodedExponent_4458_ = lean_uint64_sub(v___y_4453_, v___x_4457_);
v___x_4459_ = lean_uint64_to_uint32(v_encodedExponent_4458_);
v___x_4460_ = 8388608ULL;
v___x_4461_ = lean_uint64_dec_lt(v___y_4456_, v___x_4460_);
if (v___x_4461_ == 0)
{
uint64_t v___x_4462_; uint32_t v___x_4463_; 
v___x_4462_ = lean_uint64_sub(v___y_4456_, v___x_4460_);
v___x_4463_ = lean_uint64_to_uint32(v___x_4462_);
v___y_4446_ = v___x_4459_;
v___y_4447_ = v___y_4455_;
v___y_4448_ = v___x_4463_;
goto v___jp_4445_;
}
else
{
uint32_t v___x_4464_; 
v___x_4464_ = lean_uint64_to_uint32(v___y_4454_);
v___y_4446_ = v___x_4459_;
v___y_4447_ = v___y_4455_;
v___y_4448_ = v___x_4464_;
goto v___jp_4445_;
}
}
v___jp_4465_:
{
uint64_t v___x_4471_; uint8_t v___x_4472_; 
v___x_4471_ = 425ULL;
v___x_4472_ = lean_uint64_dec_lt(v___x_4471_, v___y_4470_);
if (v___x_4472_ == 0)
{
if (v___y_4469_ == 0)
{
v___y_4453_ = v___y_4470_;
v___y_4454_ = v___y_4467_;
v___y_4455_ = v___y_4466_;
v___y_4456_ = v___y_4468_;
goto v___jp_4452_;
}
else
{
uint64_t v___x_4473_; 
v___x_4473_ = 8388608ULL;
v___y_4453_ = v___y_4470_;
v___y_4454_ = v___y_4467_;
v___y_4455_ = v___y_4466_;
v___y_4456_ = v___x_4473_;
goto v___jp_4452_;
}
}
else
{
uint8_t v___x_4474_; 
v___x_4474_ = lean_unbox(v___y_4466_);
lean_dec(v___y_4466_);
if (v___x_4474_ == 0)
{
uint32_t v___x_4475_; 
v___x_4475_ = 2139095040;
return v___x_4475_;
}
else
{
uint32_t v___x_4476_; 
v___x_4476_ = 4286578688;
return v___x_4476_;
}
}
}
v___jp_4477_:
{
uint64_t v___x_4483_; uint8_t v_carry_4484_; 
v___x_4483_ = 16777216ULL;
v_carry_4484_ = lean_uint64_dec_eq(v___y_4482_, v___x_4483_);
if (v_carry_4484_ == 0)
{
v___y_4466_ = v___y_4481_;
v___y_4467_ = v___y_4480_;
v___y_4468_ = v___y_4482_;
v___y_4469_ = v_carry_4484_;
v___y_4470_ = v___y_4478_;
goto v___jp_4465_;
}
else
{
uint64_t v___x_4485_; 
v___x_4485_ = lean_uint64_add(v___y_4478_, v___y_4479_);
v___y_4466_ = v___y_4481_;
v___y_4467_ = v___y_4480_;
v___y_4468_ = v___y_4482_;
v___y_4469_ = v_carry_4484_;
v___y_4470_ = v___x_4485_;
goto v___jp_4465_;
}
}
v___jp_4486_:
{
uint64_t v_position_4494_; uint64_t v___x_4495_; uint8_t v___x_4496_; 
v_position_4494_ = lean_uint64_add(v___y_4493_, v___y_4491_);
v___x_4495_ = 172ULL;
v___x_4496_ = lean_uint64_dec_lt(v_position_4494_, v___x_4495_);
if (v___x_4496_ == 0)
{
uint64_t v___x_4497_; uint8_t v___x_4498_; 
v___x_4497_ = 23ULL;
v___x_4498_ = lean_uint64_dec_lt(v___y_4493_, v___x_4497_);
if (v___x_4498_ == 0)
{
uint64_t v___x_4499_; uint8_t v___x_4500_; 
v___x_4499_ = lean_uint64_sub(v___y_4493_, v___x_4497_);
v___x_4500_ = lean_uint64_dec_eq(v___x_4499_, v___y_4489_);
if (v___x_4500_ == 0)
{
uint64_t v___x_4501_; uint8_t v___x_4502_; 
v___x_4501_ = 64ULL;
v___x_4502_ = lean_uint64_dec_lt(v___x_4499_, v___x_4501_);
if (v___x_4502_ == 0)
{
uint8_t v___x_4503_; 
v___x_4503_ = lean_uint64_dec_eq(v___x_4499_, v___x_4501_);
if (v___x_4503_ == 0)
{
lean_dec(v___y_4490_);
v___y_4478_ = v_position_4494_;
v___y_4479_ = v___y_4487_;
v___y_4480_ = v___y_4489_;
v___y_4481_ = v___y_4488_;
v___y_4482_ = v___y_4489_;
goto v___jp_4477_;
}
else
{
uint64_t v___x_4504_; uint64_t v___x_4505_; uint8_t v___x_4506_; 
v___x_4504_ = 9223372036854775808ULL;
v___x_4505_ = lean_unbox_uint64(v___y_4490_);
lean_dec(v___y_4490_);
v___x_4506_ = lean_uint64_dec_lt(v___x_4504_, v___x_4505_);
if (v___x_4506_ == 0)
{
v___y_4478_ = v_position_4494_;
v___y_4479_ = v___y_4487_;
v___y_4480_ = v___y_4489_;
v___y_4481_ = v___y_4488_;
v___y_4482_ = v___y_4489_;
goto v___jp_4477_;
}
else
{
v___y_4478_ = v_position_4494_;
v___y_4479_ = v___y_4487_;
v___y_4480_ = v___y_4489_;
v___y_4481_ = v___y_4488_;
v___y_4482_ = v___y_4487_;
goto v___jp_4477_;
}
}
}
else
{
uint64_t v___x_4507_; uint64_t v_quotient_4508_; uint64_t v___x_4509_; uint64_t v___x_4510_; uint64_t v___x_4511_; uint64_t v_remainder_4512_; uint64_t v___x_4513_; uint64_t v_half_4514_; uint8_t v___x_4515_; 
v___x_4507_ = lean_unbox_uint64(v___y_4490_);
v_quotient_4508_ = lean_uint64_shift_right(v___x_4507_, v___x_4499_);
v___x_4509_ = lean_uint64_shift_left(v___y_4487_, v___x_4499_);
v___x_4510_ = lean_uint64_sub(v___x_4509_, v___y_4487_);
v___x_4511_ = lean_unbox_uint64(v___y_4490_);
lean_dec(v___y_4490_);
v_remainder_4512_ = lean_uint64_land(v___x_4511_, v___x_4510_);
v___x_4513_ = lean_uint64_sub(v___x_4499_, v___y_4487_);
v_half_4514_ = lean_uint64_shift_left(v___y_4487_, v___x_4513_);
v___x_4515_ = lean_uint64_dec_lt(v_remainder_4512_, v_half_4514_);
if (v___x_4515_ == 0)
{
uint8_t v___x_4516_; 
v___x_4516_ = lean_uint64_dec_lt(v_half_4514_, v_remainder_4512_);
if (v___x_4516_ == 0)
{
uint64_t v___x_4517_; uint8_t v___x_4518_; 
v___x_4517_ = lean_uint64_land(v_quotient_4508_, v___y_4487_);
v___x_4518_ = lean_uint64_dec_eq(v___x_4517_, v___y_4489_);
if (v___x_4518_ == 0)
{
uint64_t v___x_4519_; 
v___x_4519_ = lean_uint64_add(v_quotient_4508_, v___y_4487_);
v___y_4478_ = v_position_4494_;
v___y_4479_ = v___y_4487_;
v___y_4480_ = v___y_4489_;
v___y_4481_ = v___y_4488_;
v___y_4482_ = v___x_4519_;
goto v___jp_4477_;
}
else
{
v___y_4478_ = v_position_4494_;
v___y_4479_ = v___y_4487_;
v___y_4480_ = v___y_4489_;
v___y_4481_ = v___y_4488_;
v___y_4482_ = v_quotient_4508_;
goto v___jp_4477_;
}
}
else
{
uint64_t v___x_4520_; 
v___x_4520_ = lean_uint64_add(v_quotient_4508_, v___y_4487_);
v___y_4478_ = v_position_4494_;
v___y_4479_ = v___y_4487_;
v___y_4480_ = v___y_4489_;
v___y_4481_ = v___y_4488_;
v___y_4482_ = v___x_4520_;
goto v___jp_4477_;
}
}
else
{
v___y_4478_ = v_position_4494_;
v___y_4479_ = v___y_4487_;
v___y_4480_ = v___y_4489_;
v___y_4481_ = v___y_4488_;
v___y_4482_ = v_quotient_4508_;
goto v___jp_4477_;
}
}
}
else
{
uint64_t v___x_4521_; 
v___x_4521_ = lean_unbox_uint64(v___y_4490_);
lean_dec(v___y_4490_);
v___y_4478_ = v_position_4494_;
v___y_4479_ = v___y_4487_;
v___y_4480_ = v___y_4489_;
v___y_4481_ = v___y_4488_;
v___y_4482_ = v___x_4521_;
goto v___jp_4477_;
}
}
else
{
uint64_t v___x_4522_; uint64_t v___x_4523_; uint64_t v___x_4524_; 
v___x_4522_ = lean_uint64_sub(v___x_4497_, v___y_4493_);
v___x_4523_ = lean_unbox_uint64(v___y_4490_);
lean_dec(v___y_4490_);
v___x_4524_ = lean_uint64_shift_left(v___x_4523_, v___x_4522_);
v___y_4478_ = v_position_4494_;
v___y_4479_ = v___y_4487_;
v___y_4480_ = v___y_4489_;
v___y_4481_ = v___y_4488_;
v___y_4482_ = v___x_4524_;
goto v___jp_4477_;
}
}
else
{
uint8_t v___x_4525_; 
v___x_4525_ = lean_uint64_dec_lt(v___y_4491_, v___y_4492_);
if (v___x_4525_ == 0)
{
uint64_t v___x_4526_; uint64_t v___x_4527_; uint64_t v___x_4528_; 
v___x_4526_ = lean_uint64_sub(v___y_4491_, v___y_4492_);
v___x_4527_ = lean_unbox_uint64(v___y_4490_);
lean_dec(v___y_4490_);
v___x_4528_ = lean_uint64_shift_left(v___x_4527_, v___x_4526_);
v___y_2243_ = v___y_4488_;
v___y_2244_ = v___y_4489_;
v___y_2245_ = v___x_4528_;
goto v___jp_2242_;
}
else
{
uint64_t v___x_4529_; uint8_t v___x_4530_; 
v___x_4529_ = lean_uint64_sub(v___y_4492_, v___y_4491_);
v___x_4530_ = lean_uint64_dec_eq(v___x_4529_, v___y_4489_);
if (v___x_4530_ == 0)
{
uint64_t v___x_4531_; uint8_t v___x_4532_; 
v___x_4531_ = 64ULL;
v___x_4532_ = lean_uint64_dec_lt(v___x_4529_, v___x_4531_);
if (v___x_4532_ == 0)
{
uint8_t v___x_4533_; 
v___x_4533_ = lean_uint64_dec_eq(v___x_4529_, v___x_4531_);
if (v___x_4533_ == 0)
{
lean_dec(v___y_4490_);
v___y_2243_ = v___y_4488_;
v___y_2244_ = v___y_4489_;
v___y_2245_ = v___y_4489_;
goto v___jp_2242_;
}
else
{
uint64_t v___x_4534_; uint64_t v___x_4535_; uint8_t v___x_4536_; 
v___x_4534_ = 9223372036854775808ULL;
v___x_4535_ = lean_unbox_uint64(v___y_4490_);
lean_dec(v___y_4490_);
v___x_4536_ = lean_uint64_dec_lt(v___x_4534_, v___x_4535_);
if (v___x_4536_ == 0)
{
v___y_2243_ = v___y_4488_;
v___y_2244_ = v___y_4489_;
v___y_2245_ = v___y_4489_;
goto v___jp_2242_;
}
else
{
v___y_2243_ = v___y_4488_;
v___y_2244_ = v___y_4489_;
v___y_2245_ = v___y_4487_;
goto v___jp_2242_;
}
}
}
else
{
uint64_t v___x_4537_; uint64_t v_quotient_4538_; uint64_t v___x_4539_; uint64_t v___x_4540_; uint64_t v___x_4541_; uint64_t v_remainder_4542_; uint64_t v___x_4543_; uint64_t v_half_4544_; uint8_t v___x_4545_; 
v___x_4537_ = lean_unbox_uint64(v___y_4490_);
v_quotient_4538_ = lean_uint64_shift_right(v___x_4537_, v___x_4529_);
v___x_4539_ = lean_uint64_shift_left(v___y_4487_, v___x_4529_);
v___x_4540_ = lean_uint64_sub(v___x_4539_, v___y_4487_);
v___x_4541_ = lean_unbox_uint64(v___y_4490_);
lean_dec(v___y_4490_);
v_remainder_4542_ = lean_uint64_land(v___x_4541_, v___x_4540_);
v___x_4543_ = lean_uint64_sub(v___x_4529_, v___y_4487_);
v_half_4544_ = lean_uint64_shift_left(v___y_4487_, v___x_4543_);
v___x_4545_ = lean_uint64_dec_lt(v_remainder_4542_, v_half_4544_);
if (v___x_4545_ == 0)
{
uint8_t v___x_4546_; 
v___x_4546_ = lean_uint64_dec_lt(v_half_4544_, v_remainder_4542_);
if (v___x_4546_ == 0)
{
uint64_t v___x_4547_; uint8_t v___x_4548_; 
v___x_4547_ = lean_uint64_land(v_quotient_4538_, v___y_4487_);
v___x_4548_ = lean_uint64_dec_eq(v___x_4547_, v___y_4489_);
if (v___x_4548_ == 0)
{
uint64_t v___x_4549_; 
v___x_4549_ = lean_uint64_add(v_quotient_4538_, v___y_4487_);
v___y_2243_ = v___y_4488_;
v___y_2244_ = v___y_4489_;
v___y_2245_ = v___x_4549_;
goto v___jp_2242_;
}
else
{
v___y_2243_ = v___y_4488_;
v___y_2244_ = v___y_4489_;
v___y_2245_ = v_quotient_4538_;
goto v___jp_2242_;
}
}
else
{
uint64_t v___x_4550_; 
v___x_4550_ = lean_uint64_add(v_quotient_4538_, v___y_4487_);
v___y_2243_ = v___y_4488_;
v___y_2244_ = v___y_4489_;
v___y_2245_ = v___x_4550_;
goto v___jp_2242_;
}
}
else
{
v___y_2243_ = v___y_4488_;
v___y_2244_ = v___y_4489_;
v___y_2245_ = v_quotient_4538_;
goto v___jp_2242_;
}
}
}
else
{
uint64_t v___x_4551_; 
v___x_4551_ = lean_unbox_uint64(v___y_4490_);
lean_dec(v___y_4490_);
v___y_2243_ = v___y_4488_;
v___y_2244_ = v___y_4489_;
v___y_2245_ = v___x_4551_;
goto v___jp_2242_;
}
}
}
}
v___jp_4552_:
{
uint64_t v___x_4561_; uint8_t v___x_4562_; 
v___x_4561_ = lean_uint64_shift_right(v___y_4554_, v___y_4553_);
v___x_4562_ = lean_uint64_dec_eq(v___x_4561_, v___y_4556_);
if (v___x_4562_ == 0)
{
uint64_t v___x_4563_; 
v___x_4563_ = lean_uint64_add(v___y_4560_, v___y_4553_);
v___y_4487_ = v___y_4553_;
v___y_4488_ = v___y_4555_;
v___y_4489_ = v___y_4556_;
v___y_4490_ = v___y_4558_;
v___y_4491_ = v___y_4557_;
v___y_4492_ = v___y_4559_;
v___y_4493_ = v___x_4563_;
goto v___jp_4486_;
}
else
{
v___y_4487_ = v___y_4553_;
v___y_4488_ = v___y_4555_;
v___y_4489_ = v___y_4556_;
v___y_4490_ = v___y_4558_;
v___y_4491_ = v___y_4557_;
v___y_4492_ = v___y_4559_;
v___y_4493_ = v___y_4560_;
goto v___jp_4486_;
}
}
v___jp_4564_:
{
uint64_t v___x_4575_; uint8_t v___x_4576_; 
v___x_4575_ = lean_uint64_shift_right(v___y_4569_, v___y_4568_);
v___x_4576_ = lean_uint64_dec_eq(v___x_4575_, v___y_4566_);
if (v___x_4576_ == 0)
{
uint64_t v___x_4577_; 
v___x_4577_ = lean_uint64_add(v___y_4573_, v___y_4568_);
v___y_4553_ = v___y_4565_;
v___y_4554_ = v___y_4574_;
v___y_4555_ = v___y_4567_;
v___y_4556_ = v___y_4566_;
v___y_4557_ = v___y_4571_;
v___y_4558_ = v___y_4570_;
v___y_4559_ = v___y_4572_;
v___y_4560_ = v___x_4577_;
goto v___jp_4552_;
}
else
{
v___y_4553_ = v___y_4565_;
v___y_4554_ = v___y_4574_;
v___y_4555_ = v___y_4567_;
v___y_4556_ = v___y_4566_;
v___y_4557_ = v___y_4571_;
v___y_4558_ = v___y_4570_;
v___y_4559_ = v___y_4572_;
v___y_4560_ = v___y_4573_;
goto v___jp_4552_;
}
}
v___jp_4578_:
{
uint64_t v___x_4587_; uint64_t v___x_4588_; uint8_t v___x_4589_; 
v___x_4587_ = 2ULL;
v___x_4588_ = lean_uint64_shift_right(v___y_4582_, v___x_4587_);
v___x_4589_ = lean_uint64_dec_eq(v___x_4588_, v___y_4581_);
if (v___x_4589_ == 0)
{
v___y_4565_ = v___y_4579_;
v___y_4566_ = v___y_4581_;
v___y_4567_ = v___y_4580_;
v___y_4568_ = v___x_4587_;
v___y_4569_ = v___y_4582_;
v___y_4570_ = v___y_4584_;
v___y_4571_ = v___y_4583_;
v___y_4572_ = v___y_4585_;
v___y_4573_ = v___y_4586_;
v___y_4574_ = v___x_4588_;
goto v___jp_4564_;
}
else
{
v___y_4565_ = v___y_4579_;
v___y_4566_ = v___y_4581_;
v___y_4567_ = v___y_4580_;
v___y_4568_ = v___x_4587_;
v___y_4569_ = v___y_4582_;
v___y_4570_ = v___y_4584_;
v___y_4571_ = v___y_4583_;
v___y_4572_ = v___y_4585_;
v___y_4573_ = v___y_4586_;
v___y_4574_ = v___y_4582_;
goto v___jp_4564_;
}
}
v___jp_4590_:
{
uint64_t v___x_4601_; uint8_t v___x_4602_; 
v___x_4601_ = lean_uint64_shift_right(v___y_4591_, v___y_4592_);
v___x_4602_ = lean_uint64_dec_eq(v___x_4601_, v___y_4594_);
if (v___x_4602_ == 0)
{
uint64_t v___x_4603_; 
v___x_4603_ = lean_uint64_add(v___y_4599_, v___y_4592_);
v___y_4579_ = v___y_4593_;
v___y_4580_ = v___y_4595_;
v___y_4581_ = v___y_4594_;
v___y_4582_ = v___y_4600_;
v___y_4583_ = v___y_4597_;
v___y_4584_ = v___y_4596_;
v___y_4585_ = v___y_4598_;
v___y_4586_ = v___x_4603_;
goto v___jp_4578_;
}
else
{
v___y_4579_ = v___y_4593_;
v___y_4580_ = v___y_4595_;
v___y_4581_ = v___y_4594_;
v___y_4582_ = v___y_4600_;
v___y_4583_ = v___y_4597_;
v___y_4584_ = v___y_4596_;
v___y_4585_ = v___y_4598_;
v___y_4586_ = v___y_4599_;
goto v___jp_4578_;
}
}
v___jp_4604_:
{
uint64_t v___x_4613_; uint64_t v___x_4614_; uint8_t v___x_4615_; 
v___x_4613_ = 4ULL;
v___x_4614_ = lean_uint64_shift_right(v___y_4605_, v___x_4613_);
v___x_4615_ = lean_uint64_dec_eq(v___x_4614_, v___y_4608_);
if (v___x_4615_ == 0)
{
v___y_4591_ = v___y_4605_;
v___y_4592_ = v___x_4613_;
v___y_4593_ = v___y_4606_;
v___y_4594_ = v___y_4608_;
v___y_4595_ = v___y_4607_;
v___y_4596_ = v___y_4610_;
v___y_4597_ = v___y_4609_;
v___y_4598_ = v___y_4611_;
v___y_4599_ = v___y_4612_;
v___y_4600_ = v___x_4614_;
goto v___jp_4590_;
}
else
{
v___y_4591_ = v___y_4605_;
v___y_4592_ = v___x_4613_;
v___y_4593_ = v___y_4606_;
v___y_4594_ = v___y_4608_;
v___y_4595_ = v___y_4607_;
v___y_4596_ = v___y_4610_;
v___y_4597_ = v___y_4609_;
v___y_4598_ = v___y_4611_;
v___y_4599_ = v___y_4612_;
v___y_4600_ = v___y_4605_;
goto v___jp_4590_;
}
}
v___jp_4616_:
{
uint64_t v___x_4627_; uint8_t v___x_4628_; 
v___x_4627_ = lean_uint64_shift_right(v___y_4619_, v___y_4622_);
v___x_4628_ = lean_uint64_dec_eq(v___x_4627_, v___y_4620_);
if (v___x_4628_ == 0)
{
uint64_t v___x_4629_; 
v___x_4629_ = lean_uint64_add(v___y_4617_, v___y_4622_);
v___y_4605_ = v___y_4626_;
v___y_4606_ = v___y_4618_;
v___y_4607_ = v___y_4621_;
v___y_4608_ = v___y_4620_;
v___y_4609_ = v___y_4624_;
v___y_4610_ = v___y_4623_;
v___y_4611_ = v___y_4625_;
v___y_4612_ = v___x_4629_;
goto v___jp_4604_;
}
else
{
v___y_4605_ = v___y_4626_;
v___y_4606_ = v___y_4618_;
v___y_4607_ = v___y_4621_;
v___y_4608_ = v___y_4620_;
v___y_4609_ = v___y_4624_;
v___y_4610_ = v___y_4623_;
v___y_4611_ = v___y_4625_;
v___y_4612_ = v___y_4617_;
goto v___jp_4604_;
}
}
v___jp_4630_:
{
uint64_t v___x_4639_; uint64_t v___x_4640_; uint8_t v___x_4641_; 
v___x_4639_ = 8ULL;
v___x_4640_ = lean_uint64_shift_right(v___y_4632_, v___x_4639_);
v___x_4641_ = lean_uint64_dec_eq(v___x_4640_, v___y_4634_);
if (v___x_4641_ == 0)
{
v___y_4617_ = v___y_4638_;
v___y_4618_ = v___y_4631_;
v___y_4619_ = v___y_4632_;
v___y_4620_ = v___y_4634_;
v___y_4621_ = v___y_4633_;
v___y_4622_ = v___x_4639_;
v___y_4623_ = v___y_4636_;
v___y_4624_ = v___y_4635_;
v___y_4625_ = v___y_4637_;
v___y_4626_ = v___x_4640_;
goto v___jp_4616_;
}
else
{
v___y_4617_ = v___y_4638_;
v___y_4618_ = v___y_4631_;
v___y_4619_ = v___y_4632_;
v___y_4620_ = v___y_4634_;
v___y_4621_ = v___y_4633_;
v___y_4622_ = v___x_4639_;
v___y_4623_ = v___y_4636_;
v___y_4624_ = v___y_4635_;
v___y_4625_ = v___y_4637_;
v___y_4626_ = v___y_4632_;
goto v___jp_4616_;
}
}
v___jp_4642_:
{
uint64_t v___x_4653_; uint8_t v___x_4654_; 
v___x_4653_ = lean_uint64_shift_right(v___y_4643_, v___y_4650_);
v___x_4654_ = lean_uint64_dec_eq(v___x_4653_, v___y_4645_);
if (v___x_4654_ == 0)
{
uint64_t v___x_4655_; 
v___x_4655_ = lean_uint64_add(v___y_4647_, v___y_4650_);
v___y_4631_ = v___y_4644_;
v___y_4632_ = v___y_4652_;
v___y_4633_ = v___y_4646_;
v___y_4634_ = v___y_4645_;
v___y_4635_ = v___y_4649_;
v___y_4636_ = v___y_4648_;
v___y_4637_ = v___y_4651_;
v___y_4638_ = v___x_4655_;
goto v___jp_4630_;
}
else
{
v___y_4631_ = v___y_4644_;
v___y_4632_ = v___y_4652_;
v___y_4633_ = v___y_4646_;
v___y_4634_ = v___y_4645_;
v___y_4635_ = v___y_4649_;
v___y_4636_ = v___y_4648_;
v___y_4637_ = v___y_4651_;
v___y_4638_ = v___y_4647_;
goto v___jp_4630_;
}
}
v___jp_4656_:
{
uint64_t v___x_4665_; uint64_t v___x_4666_; uint8_t v___x_4667_; 
v___x_4665_ = 16ULL;
v___x_4666_ = lean_uint64_shift_right(v___y_4657_, v___x_4665_);
v___x_4667_ = lean_uint64_dec_eq(v___x_4666_, v___y_4660_);
if (v___x_4667_ == 0)
{
v___y_4643_ = v___y_4657_;
v___y_4644_ = v___y_4658_;
v___y_4645_ = v___y_4660_;
v___y_4646_ = v___y_4659_;
v___y_4647_ = v___y_4664_;
v___y_4648_ = v___y_4662_;
v___y_4649_ = v___y_4661_;
v___y_4650_ = v___x_4665_;
v___y_4651_ = v___y_4663_;
v___y_4652_ = v___x_4666_;
goto v___jp_4642_;
}
else
{
v___y_4643_ = v___y_4657_;
v___y_4644_ = v___y_4658_;
v___y_4645_ = v___y_4660_;
v___y_4646_ = v___y_4659_;
v___y_4647_ = v___y_4664_;
v___y_4648_ = v___y_4662_;
v___y_4649_ = v___y_4661_;
v___y_4650_ = v___x_4665_;
v___y_4651_ = v___y_4663_;
v___y_4652_ = v___y_4657_;
goto v___jp_4642_;
}
}
v___jp_4668_:
{
uint64_t v___x_4677_; uint64_t v___x_4678_; uint8_t v___x_4679_; 
v___x_4677_ = lean_unbox_uint64(v___y_4673_);
v___x_4678_ = lean_uint64_shift_right(v___x_4677_, v___y_4669_);
v___x_4679_ = lean_uint64_dec_eq(v___x_4678_, v___y_4671_);
if (v___x_4679_ == 0)
{
v___y_4657_ = v___y_4676_;
v___y_4658_ = v___y_4670_;
v___y_4659_ = v___y_4672_;
v___y_4660_ = v___y_4671_;
v___y_4661_ = v___y_4674_;
v___y_4662_ = v___y_4673_;
v___y_4663_ = v___y_4675_;
v___y_4664_ = v___y_4669_;
goto v___jp_4656_;
}
else
{
v___y_4657_ = v___y_4676_;
v___y_4658_ = v___y_4670_;
v___y_4659_ = v___y_4672_;
v___y_4660_ = v___y_4671_;
v___y_4661_ = v___y_4674_;
v___y_4662_ = v___y_4673_;
v___y_4663_ = v___y_4675_;
v___y_4664_ = v___y_4671_;
goto v___jp_4656_;
}
}
v___jp_4680_:
{
uint64_t v___x_4685_; uint64_t v___x_4686_; uint8_t v___x_4687_; 
v___x_4685_ = 0ULL;
v___x_4686_ = lean_unbox_uint64(v_snd_4684_);
v___x_4687_ = lean_uint64_dec_eq(v___x_4686_, v___x_4685_);
if (v___x_4687_ == 0)
{
uint64_t v___x_4688_; uint64_t v___x_4689_; uint64_t v___x_4690_; uint64_t v___x_4691_; uint64_t v___x_4692_; uint8_t v___x_4693_; 
v___x_4688_ = 149ULL;
v___x_4689_ = lean_uint64_add(v___y_4681_, v___x_4688_);
v___x_4690_ = 32ULL;
v___x_4691_ = lean_unbox_uint64(v_snd_4684_);
v___x_4692_ = lean_uint64_shift_right(v___x_4691_, v___x_4690_);
v___x_4693_ = lean_uint64_dec_eq(v___x_4692_, v___x_4685_);
if (v___x_4693_ == 0)
{
v___y_4669_ = v___x_4690_;
v___y_4670_ = v___y_4682_;
v___y_4671_ = v___x_4685_;
v___y_4672_ = v_fst_4683_;
v___y_4673_ = v_snd_4684_;
v___y_4674_ = v___x_4689_;
v___y_4675_ = v___x_4688_;
v___y_4676_ = v___x_4692_;
goto v___jp_4668_;
}
else
{
uint64_t v___x_4694_; 
v___x_4694_ = lean_unbox_uint64(v_snd_4684_);
v___y_4669_ = v___x_4690_;
v___y_4670_ = v___y_4682_;
v___y_4671_ = v___x_4685_;
v___y_4672_ = v_fst_4683_;
v___y_4673_ = v_snd_4684_;
v___y_4674_ = v___x_4689_;
v___y_4675_ = v___x_4688_;
v___y_4676_ = v___x_4694_;
goto v___jp_4668_;
}
}
else
{
uint8_t v___x_4695_; 
lean_dec(v_snd_4684_);
v___x_4695_ = lean_unbox(v_fst_4683_);
lean_dec(v_fst_4683_);
if (v___x_4695_ == 0)
{
uint32_t v___x_4696_; 
v___x_4696_ = 0;
return v___x_4696_;
}
else
{
uint32_t v___x_4697_; 
v___x_4697_ = 2147483648;
return v___x_4697_;
}
}
}
v___jp_4698_:
{
uint8_t v___x_4706_; 
v___x_4706_ = lean_uint64_dec_eq(v___y_4704_, v___y_4703_);
if (v___x_4706_ == 0)
{
uint8_t v___x_4707_; 
v___x_4707_ = lean_uint64_dec_lt(v___y_4704_, v___y_4703_);
if (v___x_4707_ == 0)
{
uint64_t v___x_4708_; lean_object* v___x_4709_; lean_object* v___x_4710_; 
v___x_4708_ = lean_uint64_sub(v___y_4704_, v___y_4703_);
v___x_4709_ = lean_box(v___y_4702_);
v___x_4710_ = lean_box_uint64(v___x_4708_);
v___y_4681_ = v___y_4699_;
v___y_4682_ = v___y_4701_;
v_fst_4683_ = v___x_4709_;
v_snd_4684_ = v___x_4710_;
goto v___jp_4680_;
}
else
{
uint64_t v___x_4711_; lean_object* v___x_4712_; lean_object* v___x_4713_; 
v___x_4711_ = lean_uint64_sub(v___y_4703_, v___y_4704_);
v___x_4712_ = lean_box(v___y_4700_);
v___x_4713_ = lean_box_uint64(v___x_4711_);
v___y_4681_ = v___y_4699_;
v___y_4682_ = v___y_4701_;
v_fst_4683_ = v___x_4712_;
v_snd_4684_ = v___x_4713_;
goto v___jp_4680_;
}
}
else
{
lean_object* v___x_4714_; lean_object* v___x_4715_; 
v___x_4714_ = lean_box(v___y_4705_);
v___x_4715_ = ((lean_object*)(lp_competition_Submission_TunedAdd_core___boxed__const__1));
v___y_4681_ = v___y_4699_;
v___y_4682_ = v___y_4701_;
v_fst_4683_ = v___x_4714_;
v_snd_4684_ = v___x_4715_;
goto v___jp_4680_;
}
}
v___jp_4716_:
{
if (v___y_4723_ == 0)
{
v___y_4699_ = v___y_4717_;
v___y_4700_ = v___y_4718_;
v___y_4701_ = v___y_4719_;
v___y_4702_ = v___y_4721_;
v___y_4703_ = v___y_4720_;
v___y_4704_ = v___y_4722_;
v___y_4705_ = v___y_4723_;
goto v___jp_4698_;
}
else
{
uint64_t v___x_4724_; lean_object* v___x_4725_; lean_object* v___x_4726_; 
v___x_4724_ = lean_uint64_add(v___y_4722_, v___y_4720_);
v___x_4725_ = lean_box(v___y_4721_);
v___x_4726_ = lean_box_uint64(v___x_4724_);
v___y_4681_ = v___y_4717_;
v___y_4682_ = v___y_4719_;
v_fst_4683_ = v___x_4725_;
v_snd_4684_ = v___x_4726_;
goto v___jp_4680_;
}
}
v___jp_4727_:
{
uint8_t v___x_4735_; 
v___x_4735_ = lean_uint64_dec_le(v___y_4728_, v___y_4734_);
if (v___x_4735_ == 0)
{
uint64_t v_shift_4736_; uint64_t v___x_4737_; uint8_t v___x_4738_; 
v_shift_4736_ = lean_uint64_sub(v___y_4728_, v___y_4734_);
v___x_4737_ = 39ULL;
v___x_4738_ = lean_uint64_dec_le(v_shift_4736_, v___x_4737_);
if (v___x_4738_ == 0)
{
return v_a_2041_;
}
else
{
uint64_t v___x_4739_; 
v___x_4739_ = lean_uint64_shift_left(v___y_4733_, v_shift_4736_);
if (v___y_4732_ == 0)
{
if (v___y_4730_ == 0)
{
v___y_4425_ = v___y_4729_;
v___y_4426_ = v___x_4739_;
v___y_4427_ = v___y_4730_;
v___y_4428_ = v___y_4731_;
v___y_4429_ = v___y_4732_;
v___y_4430_ = v___y_4734_;
v___y_4431_ = v___x_4738_;
goto v___jp_4424_;
}
else
{
v___y_4407_ = v___y_4729_;
v___y_4408_ = v___y_4730_;
v___y_4409_ = v___x_4739_;
v___y_4410_ = v___y_4731_;
v___y_4411_ = v___y_4732_;
v___y_4412_ = v___y_4734_;
v___y_4413_ = v___y_4732_;
goto v___jp_4406_;
}
}
else
{
v___y_4425_ = v___y_4729_;
v___y_4426_ = v___x_4739_;
v___y_4427_ = v___y_4730_;
v___y_4428_ = v___y_4731_;
v___y_4429_ = v___y_4732_;
v___y_4430_ = v___y_4734_;
v___y_4431_ = v___y_4730_;
goto v___jp_4424_;
}
}
}
else
{
uint64_t v_shift_4740_; uint64_t v___x_4741_; uint8_t v___x_4742_; 
v_shift_4740_ = lean_uint64_sub(v___y_4734_, v___y_4728_);
v___x_4741_ = 39ULL;
v___x_4742_ = lean_uint64_dec_le(v_shift_4740_, v___x_4741_);
if (v___x_4742_ == 0)
{
return v_b_2042_;
}
else
{
uint64_t v___x_4743_; 
v___x_4743_ = lean_uint64_shift_left(v___y_4729_, v_shift_4740_);
if (v___y_4732_ == 0)
{
if (v___y_4730_ == 0)
{
v___y_4717_ = v___y_4728_;
v___y_4718_ = v___y_4730_;
v___y_4719_ = v___y_4731_;
v___y_4720_ = v___x_4743_;
v___y_4721_ = v___y_4732_;
v___y_4722_ = v___y_4733_;
v___y_4723_ = v___x_4742_;
goto v___jp_4716_;
}
else
{
v___y_4699_ = v___y_4728_;
v___y_4700_ = v___y_4730_;
v___y_4701_ = v___y_4731_;
v___y_4702_ = v___y_4732_;
v___y_4703_ = v___x_4743_;
v___y_4704_ = v___y_4733_;
v___y_4705_ = v___y_4732_;
goto v___jp_4698_;
}
}
else
{
v___y_4717_ = v___y_4728_;
v___y_4718_ = v___y_4730_;
v___y_4719_ = v___y_4731_;
v___y_4720_ = v___x_4743_;
v___y_4721_ = v___y_4732_;
v___y_4722_ = v___y_4733_;
v___y_4723_ = v___y_4730_;
goto v___jp_4716_;
}
}
}
}
v___jp_4744_:
{
uint64_t v___x_4752_; uint64_t v___x_4753_; uint8_t v___x_4754_; 
v___x_4752_ = lean_uint32_to_uint64(v___y_4746_);
v___x_4753_ = 0ULL;
v___x_4754_ = lean_uint64_dec_eq(v___x_4752_, v___x_4753_);
if (v___x_4754_ == 0)
{
uint64_t v___x_4755_; 
v___x_4755_ = lean_uint64_sub(v___x_4752_, v___y_4748_);
v___y_4728_ = v___y_4751_;
v___y_4729_ = v___y_4745_;
v___y_4730_ = v___y_4747_;
v___y_4731_ = v___y_4748_;
v___y_4732_ = v___y_4749_;
v___y_4733_ = v___y_4750_;
v___y_4734_ = v___x_4755_;
goto v___jp_4727_;
}
else
{
v___y_4728_ = v___y_4751_;
v___y_4729_ = v___y_4745_;
v___y_4730_ = v___y_4747_;
v___y_4731_ = v___y_4748_;
v___y_4732_ = v___y_4749_;
v___y_4733_ = v___y_4750_;
v___y_4734_ = v___x_4753_;
goto v___jp_4727_;
}
}
v___jp_4757_:
{
uint64_t v___x_4764_; uint64_t v___x_4765_; uint8_t v___x_4766_; 
v___x_4764_ = lean_uint32_to_uint64(v___x_4756_);
v___x_4765_ = 0ULL;
v___x_4766_ = lean_uint64_dec_eq(v___x_4764_, v___x_4765_);
if (v___x_4766_ == 0)
{
uint64_t v___x_4767_; 
v___x_4767_ = lean_uint64_sub(v___x_4764_, v___y_4760_);
v___y_4745_ = v___y_4763_;
v___y_4746_ = v___y_4759_;
v___y_4747_ = v___y_4758_;
v___y_4748_ = v___y_4760_;
v___y_4749_ = v___y_4761_;
v___y_4750_ = v___y_4762_;
v___y_4751_ = v___x_4767_;
goto v___jp_4744_;
}
else
{
v___y_4745_ = v___y_4763_;
v___y_4746_ = v___y_4759_;
v___y_4747_ = v___y_4758_;
v___y_4748_ = v___y_4760_;
v___y_4749_ = v___y_4761_;
v___y_4750_ = v___y_4762_;
v___y_4751_ = v___x_4765_;
goto v___jp_4744_;
}
}
v___jp_4768_:
{
uint32_t v___x_4774_; uint32_t v___x_4775_; uint32_t v___x_4776_; uint8_t v___x_4777_; 
v___x_4774_ = 8388607;
v___x_4775_ = lean_uint32_land(v_b_2042_, v___x_4774_);
v___x_4776_ = 0;
v___x_4777_ = lean_uint32_dec_eq(v___y_4769_, v___x_4776_);
if (v___x_4777_ == 0)
{
uint64_t v___x_4778_; uint64_t v___x_4779_; uint64_t v___x_4780_; 
v___x_4778_ = lean_uint32_to_uint64(v___x_4775_);
v___x_4779_ = 8388608ULL;
v___x_4780_ = lean_uint64_lor(v___x_4778_, v___x_4779_);
v___y_4758_ = v___y_4770_;
v___y_4759_ = v___y_4769_;
v___y_4760_ = v___y_4771_;
v___y_4761_ = v___y_4772_;
v___y_4762_ = v___y_4773_;
v___y_4763_ = v___x_4780_;
goto v___jp_4757_;
}
else
{
uint64_t v___x_4781_; 
v___x_4781_ = lean_uint32_to_uint64(v___x_4775_);
v___y_4758_ = v___y_4770_;
v___y_4759_ = v___y_4769_;
v___y_4760_ = v___y_4771_;
v___y_4761_ = v___y_4772_;
v___y_4762_ = v___y_4773_;
v___y_4763_ = v___x_4781_;
goto v___jp_4757_;
}
}
v___jp_4782_:
{
uint32_t v___x_4787_; uint32_t v___x_4788_; uint32_t v___x_4789_; uint8_t v___x_4790_; 
v___x_4787_ = 8388607;
v___x_4788_ = lean_uint32_land(v_a_2041_, v___x_4787_);
v___x_4789_ = 0;
v___x_4790_ = lean_uint32_dec_eq(v___x_4756_, v___x_4789_);
if (v___x_4790_ == 0)
{
uint64_t v___x_4791_; uint64_t v___x_4792_; uint64_t v___x_4793_; 
v___x_4791_ = lean_uint32_to_uint64(v___x_4788_);
v___x_4792_ = 8388608ULL;
v___x_4793_ = lean_uint64_lor(v___x_4791_, v___x_4792_);
v___y_4769_ = v___y_4783_;
v___y_4770_ = v___y_4786_;
v___y_4771_ = v___y_4784_;
v___y_4772_ = v___y_4785_;
v___y_4773_ = v___x_4793_;
goto v___jp_4768_;
}
else
{
uint64_t v___x_4794_; 
v___x_4794_ = lean_uint32_to_uint64(v___x_4788_);
v___y_4769_ = v___y_4783_;
v___y_4770_ = v___y_4786_;
v___y_4771_ = v___y_4784_;
v___y_4772_ = v___y_4785_;
v___y_4773_ = v___x_4794_;
goto v___jp_4768_;
}
}
v___jp_4795_:
{
uint32_t v___x_4801_; uint32_t v___x_4802_; uint32_t v___x_4803_; uint8_t v___x_4804_; 
v___x_4801_ = 2147483648;
v___x_4802_ = lean_uint32_land(v_b_2042_, v___x_4801_);
v___x_4803_ = 0;
v___x_4804_ = lean_uint32_dec_eq(v___x_4802_, v___x_4803_);
if (v___x_4804_ == 0)
{
v___y_4783_ = v___y_4796_;
v___y_4784_ = v___y_4797_;
v___y_4785_ = v___y_4800_;
v___y_4786_ = v___y_4799_;
goto v___jp_4782_;
}
else
{
v___y_4783_ = v___y_4796_;
v___y_4784_ = v___y_4797_;
v___y_4785_ = v___y_4800_;
v___y_4786_ = v___y_4798_;
goto v___jp_4782_;
}
}
v___jp_4805_:
{
uint64_t v___x_4814_; uint64_t v___x_4815_; uint8_t v___x_4816_; 
v___x_4814_ = lean_uint32_to_uint64(v___x_4756_);
v___x_4815_ = 0ULL;
v___x_4816_ = lean_uint64_dec_eq(v___x_4814_, v___x_4815_);
if (v___x_4816_ == 0)
{
uint64_t v___x_4817_; 
v___x_4817_ = lean_uint64_sub(v___x_4814_, v___y_4808_);
v___y_4130_ = v___y_4806_;
v___y_4131_ = v___y_4807_;
v___y_4132_ = v___y_4809_;
v___y_4133_ = v___y_4808_;
v___y_4134_ = v___y_4810_;
v___y_4135_ = v___y_4813_;
v___y_4136_ = v___y_4811_;
v___y_4137_ = v___y_4812_;
v___y_4138_ = v___x_4817_;
goto v___jp_4129_;
}
else
{
v___y_4130_ = v___y_4806_;
v___y_4131_ = v___y_4807_;
v___y_4132_ = v___y_4809_;
v___y_4133_ = v___y_4808_;
v___y_4134_ = v___y_4810_;
v___y_4135_ = v___y_4813_;
v___y_4136_ = v___y_4811_;
v___y_4137_ = v___y_4812_;
v___y_4138_ = v___x_4815_;
goto v___jp_4129_;
}
}
v___jp_4818_:
{
uint32_t v___x_4826_; uint32_t v___x_4827_; uint32_t v___x_4828_; uint8_t v___x_4829_; 
v___x_4826_ = 8388607;
v___x_4827_ = lean_uint32_land(v_b_2042_, v___x_4826_);
v___x_4828_ = 0;
v___x_4829_ = lean_uint32_dec_eq(v___y_4820_, v___x_4828_);
if (v___x_4829_ == 0)
{
uint64_t v___x_4830_; uint64_t v___x_4831_; uint64_t v___x_4832_; 
v___x_4830_ = lean_uint32_to_uint64(v___x_4827_);
v___x_4831_ = 8388608ULL;
v___x_4832_ = lean_uint64_lor(v___x_4830_, v___x_4831_);
v___y_4806_ = v___y_4819_;
v___y_4807_ = v___y_4820_;
v___y_4808_ = v___y_4821_;
v___y_4809_ = v___y_4825_;
v___y_4810_ = v___y_4822_;
v___y_4811_ = v___y_4823_;
v___y_4812_ = v___y_4824_;
v___y_4813_ = v___x_4832_;
goto v___jp_4805_;
}
else
{
uint64_t v___x_4833_; 
v___x_4833_ = lean_uint32_to_uint64(v___x_4827_);
v___y_4806_ = v___y_4819_;
v___y_4807_ = v___y_4820_;
v___y_4808_ = v___y_4821_;
v___y_4809_ = v___y_4825_;
v___y_4810_ = v___y_4822_;
v___y_4811_ = v___y_4823_;
v___y_4812_ = v___y_4824_;
v___y_4813_ = v___x_4833_;
goto v___jp_4805_;
}
}
v___jp_4834_:
{
uint32_t v___x_4841_; uint32_t v___x_4842_; uint32_t v___x_4843_; uint8_t v___x_4844_; 
v___x_4841_ = 8388607;
v___x_4842_ = lean_uint32_land(v_a_2041_, v___x_4841_);
v___x_4843_ = 0;
v___x_4844_ = lean_uint32_dec_eq(v___x_4756_, v___x_4843_);
if (v___x_4844_ == 0)
{
uint64_t v___x_4845_; uint64_t v___x_4846_; uint64_t v___x_4847_; 
v___x_4845_ = lean_uint32_to_uint64(v___x_4842_);
v___x_4846_ = 8388608ULL;
v___x_4847_ = lean_uint64_lor(v___x_4845_, v___x_4846_);
v___y_4819_ = v___y_4835_;
v___y_4820_ = v___y_4836_;
v___y_4821_ = v___y_4837_;
v___y_4822_ = v___y_4840_;
v___y_4823_ = v___y_4838_;
v___y_4824_ = v___y_4839_;
v___y_4825_ = v___x_4847_;
goto v___jp_4818_;
}
else
{
uint64_t v___x_4848_; 
v___x_4848_ = lean_uint32_to_uint64(v___x_4842_);
v___y_4819_ = v___y_4835_;
v___y_4820_ = v___y_4836_;
v___y_4821_ = v___y_4837_;
v___y_4822_ = v___y_4840_;
v___y_4823_ = v___y_4838_;
v___y_4824_ = v___y_4839_;
v___y_4825_ = v___x_4848_;
goto v___jp_4818_;
}
}
v___jp_4849_:
{
uint32_t v___x_4857_; uint32_t v___x_4858_; uint32_t v___x_4859_; uint8_t v___x_4860_; 
v___x_4857_ = 2147483648;
v___x_4858_ = lean_uint32_land(v_b_2042_, v___x_4857_);
v___x_4859_ = 0;
v___x_4860_ = lean_uint32_dec_eq(v___x_4858_, v___x_4859_);
if (v___x_4860_ == 0)
{
v___y_4835_ = v___y_4850_;
v___y_4836_ = v___y_4851_;
v___y_4837_ = v___y_4852_;
v___y_4838_ = v___y_4855_;
v___y_4839_ = v___y_4856_;
v___y_4840_ = v___y_4853_;
goto v___jp_4834_;
}
else
{
v___y_4835_ = v___y_4850_;
v___y_4836_ = v___y_4851_;
v___y_4837_ = v___y_4852_;
v___y_4838_ = v___y_4855_;
v___y_4839_ = v___y_4856_;
v___y_4840_ = v___y_4854_;
goto v___jp_4834_;
}
}
v___jp_4861_:
{
uint64_t v_product_4868_; uint64_t v___x_4869_; uint64_t v___x_4870_; uint64_t v___x_4871_; uint8_t v___x_4872_; 
v_product_4868_ = lean_uint64_add(v___y_4865_, v___y_4867_);
v___x_4869_ = 24ULL;
v___x_4870_ = lean_uint64_shift_right(v_product_4868_, v___x_4869_);
v___x_4871_ = 1ULL;
v___x_4872_ = lean_uint64_dec_eq(v___x_4870_, v___x_4871_);
if (v___x_4872_ == 0)
{
uint32_t v___x_4873_; uint32_t v___x_4874_; uint32_t v___x_4875_; uint8_t v___x_4876_; 
v___x_4873_ = 2147483648;
v___x_4874_ = lean_uint32_land(v_a_2041_, v___x_4873_);
v___x_4875_ = 0;
v___x_4876_ = lean_uint32_dec_eq(v___x_4874_, v___x_4875_);
if (v___x_4876_ == 0)
{
v___y_4796_ = v___y_4862_;
v___y_4797_ = v___x_4871_;
v___y_4798_ = v___x_4872_;
v___y_4799_ = v___y_4866_;
v___y_4800_ = v___y_4866_;
goto v___jp_4795_;
}
else
{
v___y_4796_ = v___y_4862_;
v___y_4797_ = v___x_4871_;
v___y_4798_ = v___x_4872_;
v___y_4799_ = v___y_4866_;
v___y_4800_ = v___x_4872_;
goto v___jp_4795_;
}
}
else
{
uint64_t v___x_4877_; uint64_t v___x_4878_; uint64_t v___x_4879_; uint64_t v___x_4880_; uint8_t v___x_4881_; 
v___x_4877_ = 172ULL;
v___x_4878_ = 149ULL;
v___x_4879_ = lean_uint64_add(v___y_4864_, v___x_4878_);
v___x_4880_ = lean_uint64_add(v___x_4869_, v___x_4879_);
v___x_4881_ = lean_uint64_dec_le(v___x_4877_, v___x_4880_);
if (v___x_4881_ == 0)
{
uint32_t v___x_4882_; uint32_t v___x_4883_; uint32_t v___x_4884_; uint8_t v___x_4885_; 
v___x_4882_ = 2147483648;
v___x_4883_ = lean_uint32_land(v_a_2041_, v___x_4882_);
v___x_4884_ = 0;
v___x_4885_ = lean_uint32_dec_eq(v___x_4883_, v___x_4884_);
if (v___x_4885_ == 0)
{
v___y_4850_ = v___x_4877_;
v___y_4851_ = v___y_4862_;
v___y_4852_ = v___x_4871_;
v___y_4853_ = v___x_4872_;
v___y_4854_ = v___x_4881_;
v___y_4855_ = v___x_4878_;
v___y_4856_ = v___x_4872_;
goto v___jp_4849_;
}
else
{
v___y_4850_ = v___x_4877_;
v___y_4851_ = v___y_4862_;
v___y_4852_ = v___x_4871_;
v___y_4853_ = v___x_4872_;
v___y_4854_ = v___x_4881_;
v___y_4855_ = v___x_4878_;
v___y_4856_ = v___x_4881_;
goto v___jp_4849_;
}
}
else
{
uint64_t v_quotient_4886_; uint64_t v_remainder_4887_; uint8_t v___x_4888_; 
v_quotient_4886_ = lean_uint64_shift_right(v_product_4868_, v___x_4871_);
v_remainder_4887_ = lean_uint64_land(v_product_4868_, v___x_4871_);
v___x_4888_ = lean_uint64_dec_lt(v_remainder_4887_, v___x_4871_);
if (v___x_4888_ == 0)
{
uint8_t v___x_4889_; 
v___x_4889_ = lean_uint64_dec_lt(v___x_4871_, v_remainder_4887_);
if (v___x_4889_ == 0)
{
uint64_t v___x_4890_; uint64_t v___x_4891_; uint8_t v___x_4892_; 
v___x_4890_ = lean_uint64_land(v_quotient_4886_, v___x_4871_);
v___x_4891_ = 0ULL;
v___x_4892_ = lean_uint64_dec_eq(v___x_4890_, v___x_4891_);
if (v___x_4892_ == 0)
{
uint64_t v___x_4893_; 
v___x_4893_ = lean_uint64_add(v_quotient_4886_, v___x_4871_);
v___y_3489_ = v___x_4880_;
v___y_3490_ = v___x_4871_;
v___y_3491_ = v___y_4863_;
v___y_3492_ = v___x_4893_;
goto v___jp_3488_;
}
else
{
v___y_3489_ = v___x_4880_;
v___y_3490_ = v___x_4871_;
v___y_3491_ = v___y_4863_;
v___y_3492_ = v_quotient_4886_;
goto v___jp_3488_;
}
}
else
{
uint64_t v___x_4894_; 
v___x_4894_ = lean_uint64_add(v_quotient_4886_, v___x_4871_);
v___y_3489_ = v___x_4880_;
v___y_3490_ = v___x_4871_;
v___y_3491_ = v___y_4863_;
v___y_3492_ = v___x_4894_;
goto v___jp_3488_;
}
}
else
{
v___y_3489_ = v___x_4880_;
v___y_3490_ = v___x_4871_;
v___y_3491_ = v___y_4863_;
v___y_3492_ = v_quotient_4886_;
goto v___jp_3488_;
}
}
}
}
v___jp_4895_:
{
uint32_t v___x_4901_; uint32_t v___x_4902_; uint32_t v___x_4903_; uint8_t v___x_4904_; 
v___x_4901_ = 8388607;
v___x_4902_ = lean_uint32_land(v_b_2042_, v___x_4901_);
v___x_4903_ = 0;
v___x_4904_ = lean_uint32_dec_eq(v___y_4896_, v___x_4903_);
if (v___x_4904_ == 0)
{
uint64_t v___x_4905_; uint64_t v___x_4906_; uint64_t v___x_4907_; 
v___x_4905_ = lean_uint32_to_uint64(v___x_4902_);
v___x_4906_ = 8388608ULL;
v___x_4907_ = lean_uint64_lor(v___x_4905_, v___x_4906_);
v___y_4862_ = v___y_4896_;
v___y_4863_ = v___y_4897_;
v___y_4864_ = v___y_4898_;
v___y_4865_ = v___y_4900_;
v___y_4866_ = v___y_4899_;
v___y_4867_ = v___x_4907_;
goto v___jp_4861_;
}
else
{
uint64_t v___x_4908_; 
v___x_4908_ = lean_uint32_to_uint64(v___x_4902_);
v___y_4862_ = v___y_4896_;
v___y_4863_ = v___y_4897_;
v___y_4864_ = v___y_4898_;
v___y_4865_ = v___y_4900_;
v___y_4866_ = v___y_4899_;
v___y_4867_ = v___x_4908_;
goto v___jp_4861_;
}
}
v___jp_4909_:
{
uint32_t v___x_4914_; uint32_t v___x_4915_; uint32_t v___x_4916_; uint8_t v___x_4917_; 
v___x_4914_ = 8388607;
v___x_4915_ = lean_uint32_land(v_a_2041_, v___x_4914_);
v___x_4916_ = 0;
v___x_4917_ = lean_uint32_dec_eq(v___x_4756_, v___x_4916_);
if (v___x_4917_ == 0)
{
uint64_t v___x_4918_; uint64_t v___x_4919_; uint64_t v___x_4920_; 
v___x_4918_ = lean_uint32_to_uint64(v___x_4915_);
v___x_4919_ = 8388608ULL;
v___x_4920_ = lean_uint64_lor(v___x_4918_, v___x_4919_);
v___y_4896_ = v___y_4910_;
v___y_4897_ = v___y_4911_;
v___y_4898_ = v___y_4912_;
v___y_4899_ = v___y_4913_;
v___y_4900_ = v___x_4920_;
goto v___jp_4895_;
}
else
{
uint64_t v___x_4921_; 
v___x_4921_ = lean_uint32_to_uint64(v___x_4915_);
v___y_4896_ = v___y_4910_;
v___y_4897_ = v___y_4911_;
v___y_4898_ = v___y_4912_;
v___y_4899_ = v___y_4913_;
v___y_4900_ = v___x_4921_;
goto v___jp_4895_;
}
}
v___jp_4922_:
{
uint64_t v___x_4928_; uint64_t v___x_4929_; uint8_t v___x_4930_; 
v___x_4928_ = lean_uint32_to_uint64(v___x_4756_);
v___x_4929_ = 0ULL;
v___x_4930_ = lean_uint64_dec_eq(v___x_4928_, v___x_4929_);
if (v___x_4930_ == 0)
{
uint64_t v___x_4931_; uint64_t v___x_4932_; 
v___x_4931_ = 1ULL;
v___x_4932_ = lean_uint64_sub(v___x_4928_, v___x_4931_);
v___y_3439_ = v___y_4927_;
v___y_3440_ = v___y_4923_;
v___y_3441_ = v___y_4924_;
v___y_3442_ = v___y_4926_;
v___y_3443_ = v___y_4925_;
v___y_3444_ = v___x_4932_;
goto v___jp_3438_;
}
else
{
v___y_3439_ = v___y_4927_;
v___y_3440_ = v___y_4923_;
v___y_3441_ = v___y_4924_;
v___y_3442_ = v___y_4926_;
v___y_3443_ = v___y_4925_;
v___y_3444_ = v___x_4929_;
goto v___jp_3438_;
}
}
v___jp_4933_:
{
uint32_t v___x_4938_; uint32_t v___x_4939_; uint32_t v___x_4940_; uint8_t v___x_4941_; 
v___x_4938_ = 8388607;
v___x_4939_ = lean_uint32_land(v_b_2042_, v___x_4938_);
v___x_4940_ = 0;
v___x_4941_ = lean_uint32_dec_eq(v___y_4934_, v___x_4940_);
if (v___x_4941_ == 0)
{
uint64_t v___x_4942_; uint64_t v___x_4943_; uint64_t v___x_4944_; 
v___x_4942_ = lean_uint32_to_uint64(v___x_4939_);
v___x_4943_ = 8388608ULL;
v___x_4944_ = lean_uint64_lor(v___x_4942_, v___x_4943_);
v___y_4923_ = v___y_4934_;
v___y_4924_ = v___y_4937_;
v___y_4925_ = v___y_4936_;
v___y_4926_ = v___y_4935_;
v___y_4927_ = v___x_4944_;
goto v___jp_4922_;
}
else
{
uint64_t v___x_4945_; 
v___x_4945_ = lean_uint32_to_uint64(v___x_4939_);
v___y_4923_ = v___y_4934_;
v___y_4924_ = v___y_4937_;
v___y_4925_ = v___y_4936_;
v___y_4926_ = v___y_4935_;
v___y_4927_ = v___x_4945_;
goto v___jp_4922_;
}
}
v___jp_4946_:
{
uint32_t v___x_4950_; uint32_t v___x_4951_; uint32_t v___x_4952_; uint8_t v___x_4953_; 
v___x_4950_ = 8388607;
v___x_4951_ = lean_uint32_land(v_a_2041_, v___x_4950_);
v___x_4952_ = 0;
v___x_4953_ = lean_uint32_dec_eq(v___x_4756_, v___x_4952_);
if (v___x_4953_ == 0)
{
uint64_t v___x_4954_; uint64_t v___x_4955_; uint64_t v___x_4956_; 
v___x_4954_ = lean_uint32_to_uint64(v___x_4951_);
v___x_4955_ = 8388608ULL;
v___x_4956_ = lean_uint64_lor(v___x_4954_, v___x_4955_);
v___y_4934_ = v___y_4947_;
v___y_4935_ = v___y_4949_;
v___y_4936_ = v___y_4948_;
v___y_4937_ = v___x_4956_;
goto v___jp_4933_;
}
else
{
uint64_t v___x_4957_; 
v___x_4957_ = lean_uint32_to_uint64(v___x_4951_);
v___y_4934_ = v___y_4947_;
v___y_4935_ = v___y_4949_;
v___y_4936_ = v___y_4948_;
v___y_4937_ = v___x_4957_;
goto v___jp_4933_;
}
}
v___jp_4958_:
{
uint32_t v___x_4963_; uint32_t v___x_4964_; uint32_t v___x_4965_; uint8_t v___x_4966_; 
v___x_4963_ = 2147483648;
v___x_4964_ = lean_uint32_land(v_b_2042_, v___x_4963_);
v___x_4965_ = 0;
v___x_4966_ = lean_uint32_dec_eq(v___x_4964_, v___x_4965_);
if (v___x_4966_ == 0)
{
v___y_4947_ = v___y_4959_;
v___y_4948_ = v___y_4962_;
v___y_4949_ = v___y_4960_;
goto v___jp_4946_;
}
else
{
v___y_4947_ = v___y_4959_;
v___y_4948_ = v___y_4962_;
v___y_4949_ = v___y_4961_;
goto v___jp_4946_;
}
}
v___jp_4967_:
{
uint32_t v___x_4971_; uint32_t v___x_4972_; uint32_t v___x_4973_; uint8_t v___x_4974_; 
v___x_4971_ = 2147483648;
v___x_4972_ = lean_uint32_land(v_a_2041_, v___x_4971_);
v___x_4973_ = 0;
v___x_4974_ = lean_uint32_dec_eq(v___x_4972_, v___x_4973_);
if (v___x_4974_ == 0)
{
v___y_4959_ = v___y_4968_;
v___y_4960_ = v___y_4969_;
v___y_4961_ = v___y_4970_;
v___y_4962_ = v___y_4969_;
goto v___jp_4958_;
}
else
{
v___y_4959_ = v___y_4968_;
v___y_4960_ = v___y_4969_;
v___y_4961_ = v___y_4970_;
v___y_4962_ = v___y_4970_;
goto v___jp_4958_;
}
}
v___jp_4975_:
{
if (v___y_4978_ == 0)
{
if (v___y_4980_ == 0)
{
uint8_t v___x_4981_; 
v___x_4981_ = 1;
v___y_4910_ = v___y_4976_;
v___y_4911_ = v___y_4978_;
v___y_4912_ = v___y_4979_;
v___y_4913_ = v___x_4981_;
goto v___jp_4909_;
}
else
{
v___y_4968_ = v___y_4976_;
v___y_4969_ = v___y_4977_;
v___y_4970_ = v___y_4978_;
goto v___jp_4967_;
}
}
else
{
if (v___y_4980_ == 0)
{
v___y_4968_ = v___y_4976_;
v___y_4969_ = v___y_4977_;
v___y_4970_ = v___y_4980_;
goto v___jp_4967_;
}
else
{
v___y_4910_ = v___y_4976_;
v___y_4911_ = v___y_4978_;
v___y_4912_ = v___y_4979_;
v___y_4913_ = v___y_4980_;
goto v___jp_4909_;
}
}
}
v___jp_4982_:
{
uint32_t v___x_4987_; uint32_t v___x_4988_; uint32_t v___x_4989_; uint8_t v___x_4990_; 
v___x_4987_ = 2147483648;
v___x_4988_ = lean_uint32_land(v_b_2042_, v___x_4987_);
v___x_4989_ = 0;
v___x_4990_ = lean_uint32_dec_eq(v___x_4988_, v___x_4989_);
if (v___x_4990_ == 0)
{
v___y_4976_ = v___y_4983_;
v___y_4977_ = v___y_4984_;
v___y_4978_ = v___y_4986_;
v___y_4979_ = v___y_4985_;
v___y_4980_ = v___y_4984_;
goto v___jp_4975_;
}
else
{
uint8_t v___x_4991_; 
v___x_4991_ = 0;
v___y_4976_ = v___y_4983_;
v___y_4977_ = v___y_4984_;
v___y_4978_ = v___y_4986_;
v___y_4979_ = v___y_4985_;
v___y_4980_ = v___x_4991_;
goto v___jp_4975_;
}
}
v___jp_4992_:
{
uint64_t v___x_4998_; uint64_t v___x_4999_; uint8_t v___x_5000_; 
v___x_4998_ = lean_uint32_to_uint64(v___x_4756_);
v___x_4999_ = 0ULL;
v___x_5000_ = lean_uint64_dec_eq(v___x_4998_, v___x_4999_);
if (v___x_5000_ == 0)
{
uint64_t v___x_5001_; uint64_t v___x_5002_; 
v___x_5001_ = 1ULL;
v___x_5002_ = lean_uint64_sub(v___x_4998_, v___x_5001_);
v___y_2845_ = v___y_4993_;
v___y_2846_ = v___y_4997_;
v___y_2847_ = v___y_4994_;
v___y_2848_ = v___y_4995_;
v___y_2849_ = v___y_4996_;
v___y_2850_ = v___x_5002_;
goto v___jp_2844_;
}
else
{
v___y_2845_ = v___y_4993_;
v___y_2846_ = v___y_4997_;
v___y_2847_ = v___y_4994_;
v___y_2848_ = v___y_4995_;
v___y_2849_ = v___y_4996_;
v___y_2850_ = v___x_4999_;
goto v___jp_2844_;
}
}
v___jp_5003_:
{
uint32_t v___x_5008_; uint32_t v___x_5009_; uint32_t v___x_5010_; uint8_t v___x_5011_; 
v___x_5008_ = 8388607;
v___x_5009_ = lean_uint32_land(v_b_2042_, v___x_5008_);
v___x_5010_ = 0;
v___x_5011_ = lean_uint32_dec_eq(v___y_5004_, v___x_5010_);
if (v___x_5011_ == 0)
{
uint64_t v___x_5012_; uint64_t v___x_5013_; uint64_t v___x_5014_; 
v___x_5012_ = lean_uint32_to_uint64(v___x_5009_);
v___x_5013_ = 8388608ULL;
v___x_5014_ = lean_uint64_lor(v___x_5012_, v___x_5013_);
v___y_4993_ = v___y_5004_;
v___y_4994_ = v___y_5005_;
v___y_4995_ = v___y_5006_;
v___y_4996_ = v___y_5007_;
v___y_4997_ = v___x_5014_;
goto v___jp_4992_;
}
else
{
uint64_t v___x_5015_; 
v___x_5015_ = lean_uint32_to_uint64(v___x_5009_);
v___y_4993_ = v___y_5004_;
v___y_4994_ = v___y_5005_;
v___y_4995_ = v___y_5006_;
v___y_4996_ = v___y_5007_;
v___y_4997_ = v___x_5015_;
goto v___jp_4992_;
}
}
v___jp_5016_:
{
uint32_t v___x_5020_; uint32_t v___x_5021_; uint32_t v___x_5022_; uint8_t v___x_5023_; 
v___x_5020_ = 8388607;
v___x_5021_ = lean_uint32_land(v_a_2041_, v___x_5020_);
v___x_5022_ = 0;
v___x_5023_ = lean_uint32_dec_eq(v___x_4756_, v___x_5022_);
if (v___x_5023_ == 0)
{
uint64_t v___x_5024_; uint64_t v___x_5025_; uint64_t v___x_5026_; 
v___x_5024_ = lean_uint32_to_uint64(v___x_5021_);
v___x_5025_ = 8388608ULL;
v___x_5026_ = lean_uint64_lor(v___x_5024_, v___x_5025_);
v___y_5004_ = v___y_5017_;
v___y_5005_ = v___y_5019_;
v___y_5006_ = v___y_5018_;
v___y_5007_ = v___x_5026_;
goto v___jp_5003_;
}
else
{
uint64_t v___x_5027_; 
v___x_5027_ = lean_uint32_to_uint64(v___x_5021_);
v___y_5004_ = v___y_5017_;
v___y_5005_ = v___y_5019_;
v___y_5006_ = v___y_5018_;
v___y_5007_ = v___x_5027_;
goto v___jp_5003_;
}
}
v___jp_5028_:
{
uint32_t v___x_5032_; uint32_t v___x_5033_; uint32_t v___x_5034_; uint8_t v___x_5035_; 
v___x_5032_ = 2147483648;
v___x_5033_ = lean_uint32_land(v_b_2042_, v___x_5032_);
v___x_5034_ = 0;
v___x_5035_ = lean_uint32_dec_eq(v___x_5033_, v___x_5034_);
if (v___x_5035_ == 0)
{
uint8_t v___x_5036_; 
v___x_5036_ = 1;
v___y_5017_ = v___y_5029_;
v___y_5018_ = v___y_5031_;
v___y_5019_ = v___x_5036_;
goto v___jp_5016_;
}
else
{
v___y_5017_ = v___y_5029_;
v___y_5018_ = v___y_5031_;
v___y_5019_ = v___y_5030_;
goto v___jp_5016_;
}
}
v___jp_5037_:
{
uint8_t v___x_5041_; 
v___x_5041_ = lean_uint64_dec_eq(v___y_5039_, v___y_5040_);
if (v___x_5041_ == 0)
{
uint32_t v___x_5042_; uint32_t v___x_5043_; uint32_t v___x_5044_; uint8_t v___x_5045_; 
v___x_5042_ = 2147483648;
v___x_5043_ = lean_uint32_land(v_a_2041_, v___x_5042_);
v___x_5044_ = 0;
v___x_5045_ = lean_uint32_dec_eq(v___x_5043_, v___x_5044_);
if (v___x_5045_ == 0)
{
uint8_t v___x_5046_; 
v___x_5046_ = 1;
v___y_5029_ = v___y_5038_;
v___y_5030_ = v___x_5041_;
v___y_5031_ = v___x_5046_;
goto v___jp_5028_;
}
else
{
v___y_5029_ = v___y_5038_;
v___y_5030_ = v___x_5041_;
v___y_5031_ = v___x_5041_;
goto v___jp_5028_;
}
}
else
{
uint32_t v___x_5047_; uint32_t v___x_5048_; uint32_t v___x_5049_; uint8_t v___x_5050_; 
v___x_5047_ = 2147483648;
v___x_5048_ = lean_uint32_land(v_a_2041_, v___x_5047_);
v___x_5049_ = 0;
v___x_5050_ = lean_uint32_dec_eq(v___x_5048_, v___x_5049_);
if (v___x_5050_ == 0)
{
v___y_4983_ = v___y_5038_;
v___y_4984_ = v___x_5041_;
v___y_4985_ = v___y_5039_;
v___y_4986_ = v___x_5041_;
goto v___jp_4982_;
}
else
{
uint8_t v___x_5051_; 
v___x_5051_ = 0;
v___y_4983_ = v___y_5038_;
v___y_4984_ = v___x_5041_;
v___y_4985_ = v___y_5039_;
v___y_4986_ = v___x_5051_;
goto v___jp_4982_;
}
}
}
v___jp_5052_:
{
uint32_t v___x_5054_; uint32_t v___x_5055_; uint64_t v___x_5056_; uint64_t v___x_5057_; uint8_t v___x_5058_; 
v___x_5054_ = lean_uint32_shift_right(v_b_2042_, v___x_2259_);
v___x_5055_ = lean_uint32_land(v___x_5054_, v___x_2261_);
v___x_5056_ = lean_uint32_to_uint64(v___x_5055_);
v___x_5057_ = 0ULL;
v___x_5058_ = lean_uint64_dec_eq(v___x_5056_, v___x_5057_);
if (v___x_5058_ == 0)
{
uint64_t v___x_5059_; uint64_t v___x_5060_; 
v___x_5059_ = 1ULL;
v___x_5060_ = lean_uint64_sub(v___x_5056_, v___x_5059_);
v___y_5038_ = v___x_5055_;
v___y_5039_ = v___y_5053_;
v___y_5040_ = v___x_5060_;
goto v___jp_5037_;
}
else
{
v___y_5038_ = v___x_5055_;
v___y_5039_ = v___y_5053_;
v___y_5040_ = v___x_5057_;
goto v___jp_5037_;
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_RebuiltAdd_core___boxed(lean_object* v_a_5066_, lean_object* v_b_5067_){
_start:
{
uint32_t v_a_boxed_5068_; uint32_t v_b_boxed_5069_; uint32_t v_res_5070_; lean_object* v_r_5071_; 
v_a_boxed_5068_ = lean_unbox_uint32(v_a_5066_);
lean_dec(v_a_5066_);
v_b_boxed_5069_ = lean_unbox_uint32(v_b_5067_);
lean_dec(v_b_5067_);
v_res_5070_ = lp_competition_Submission_RebuiltAdd_core(v_a_boxed_5068_, v_b_boxed_5069_);
v_r_5071_ = lean_box_uint32(v_res_5070_);
return v_r_5071_;
}
}
LEAN_EXPORT uint32_t lp_competition_Submission_RebuiltAdd_add(uint32_t v_x_5072_, uint32_t v_y_5073_){
_start:
{
uint32_t v___y_5075_; uint32_t v___y_5079_; uint32_t v___y_5083_; uint32_t v___y_5087_; uint32_t v___y_5091_; uint32_t v___y_5095_; uint32_t v___y_5099_; uint32_t v___y_5103_; uint32_t v___y_5107_; uint32_t v___y_5108_; uint64_t v___y_5113_; lean_object* v___y_5114_; uint64_t v___y_5115_; uint32_t v___y_5130_; uint32_t v___y_5131_; uint32_t v___y_5132_; uint32_t v___y_5133_; uint32_t v___y_5134_; uint32_t v___y_5142_; uint32_t v___y_5143_; lean_object* v___y_5144_; uint32_t v___y_5145_; uint32_t v___y_5146_; uint64_t v___y_5151_; uint32_t v___y_5152_; uint64_t v___y_5153_; lean_object* v___y_5154_; uint32_t v___y_5155_; uint64_t v___y_5156_; uint32_t v___y_5166_; uint64_t v___y_5167_; lean_object* v___y_5168_; uint64_t v___y_5169_; uint8_t v___y_5170_; uint32_t v___y_5171_; uint64_t v___y_5172_; uint32_t v___y_5180_; uint64_t v___y_5181_; uint64_t v___y_5182_; uint64_t v___y_5183_; lean_object* v___y_5184_; uint32_t v___y_5185_; uint64_t v___y_5186_; uint32_t v___y_5191_; uint64_t v___y_5192_; uint64_t v___y_5193_; lean_object* v___y_5194_; uint64_t v___y_5195_; uint64_t v___y_5196_; lean_object* v___y_5197_; uint32_t v___y_5198_; uint64_t v___y_5199_; uint32_t v___y_5259_; uint64_t v___y_5260_; uint64_t v___y_5261_; lean_object* v___y_5262_; uint64_t v___y_5263_; uint64_t v___y_5264_; uint64_t v___y_5265_; lean_object* v___y_5266_; uint32_t v___y_5267_; uint64_t v___y_5268_; uint32_t v___y_5273_; uint64_t v___y_5274_; uint64_t v___y_5275_; uint64_t v___y_5276_; uint64_t v___y_5277_; lean_object* v___y_5278_; uint64_t v___y_5279_; lean_object* v___y_5280_; uint64_t v___y_5281_; uint64_t v___y_5282_; uint32_t v___y_5283_; uint64_t v___y_5284_; uint32_t v___y_5289_; uint64_t v___y_5290_; lean_object* v___y_5291_; uint64_t v___y_5292_; uint64_t v___y_5293_; uint64_t v___y_5294_; uint64_t v___y_5295_; lean_object* v___y_5296_; uint32_t v___y_5297_; uint64_t v___y_5298_; uint32_t v___y_5303_; uint64_t v___y_5304_; uint64_t v___y_5305_; uint64_t v___y_5306_; uint64_t v___y_5307_; lean_object* v___y_5308_; uint64_t v___y_5309_; lean_object* v___y_5310_; uint32_t v___y_5311_; uint64_t v___y_5312_; uint64_t v___y_5313_; uint64_t v___y_5314_; uint32_t v___y_5319_; uint64_t v___y_5320_; uint64_t v___y_5321_; lean_object* v___y_5322_; uint64_t v___y_5323_; uint64_t v___y_5324_; uint64_t v___y_5325_; lean_object* v___y_5326_; uint32_t v___y_5327_; uint64_t v___y_5328_; uint64_t v___y_5333_; uint64_t v___y_5334_; uint32_t v___y_5335_; uint64_t v___y_5336_; uint64_t v___y_5337_; uint64_t v___y_5338_; lean_object* v___y_5339_; uint64_t v___y_5340_; uint64_t v___y_5341_; lean_object* v___y_5342_; uint32_t v___y_5343_; uint64_t v___y_5344_; uint64_t v___y_5349_; uint32_t v___y_5350_; uint64_t v___y_5351_; lean_object* v___y_5352_; uint64_t v___y_5353_; uint64_t v___y_5354_; uint64_t v___y_5355_; lean_object* v___y_5356_; uint32_t v___y_5357_; uint64_t v___y_5358_; uint32_t v___y_5363_; uint64_t v___y_5364_; uint64_t v___y_5365_; uint64_t v___y_5366_; uint64_t v___y_5367_; lean_object* v___y_5368_; uint64_t v___y_5369_; uint64_t v___y_5370_; lean_object* v___y_5371_; uint32_t v___y_5372_; uint64_t v___y_5373_; uint64_t v___y_5374_; uint32_t v___y_5379_; uint64_t v___y_5380_; lean_object* v___y_5381_; uint64_t v___y_5382_; uint64_t v___y_5383_; uint64_t v___y_5384_; lean_object* v___y_5385_; uint64_t v___y_5386_; uint32_t v___y_5387_; uint64_t v___y_5388_; uint32_t v___y_5393_; uint64_t v___y_5394_; uint64_t v___y_5395_; uint64_t v___y_5396_; lean_object* v___y_5397_; uint64_t v___y_5398_; lean_object* v___y_5399_; uint64_t v___y_5400_; uint32_t v___y_5401_; uint64_t v___y_5402_; uint32_t v___y_5407_; uint64_t v___y_5408_; uint64_t v___y_5409_; uint32_t v___y_5410_; lean_object* v_fst_5411_; lean_object* v_snd_5412_; uint32_t v___y_5427_; uint32_t v___y_5428_; uint64_t v___y_5433_; lean_object* v___y_5434_; uint64_t v___y_5435_; uint32_t v___y_5450_; uint32_t v___y_5451_; uint32_t v___y_5452_; uint32_t v___y_5453_; uint32_t v___y_5454_; uint32_t v___y_5462_; uint32_t v___y_5463_; lean_object* v___y_5464_; uint32_t v___y_5465_; uint32_t v___y_5466_; uint64_t v___y_5471_; uint32_t v___y_5472_; lean_object* v___y_5473_; uint32_t v___y_5474_; uint64_t v___y_5475_; uint64_t v___y_5476_; uint64_t v___y_5486_; uint8_t v___y_5487_; uint32_t v___y_5488_; uint64_t v___y_5489_; lean_object* v___y_5490_; uint32_t v___y_5491_; uint64_t v___y_5492_; uint64_t v___y_5500_; uint32_t v___y_5501_; uint64_t v___y_5502_; lean_object* v___y_5503_; uint32_t v___y_5504_; uint64_t v___y_5505_; uint64_t v___y_5506_; lean_object* v___y_5511_; uint64_t v___y_5512_; uint32_t v___y_5513_; uint64_t v___y_5514_; uint64_t v___y_5515_; lean_object* v___y_5516_; uint64_t v___y_5517_; uint32_t v___y_5518_; uint64_t v___y_5519_; lean_object* v___y_5579_; uint64_t v___y_5580_; uint32_t v___y_5581_; uint64_t v___y_5582_; uint64_t v___y_5583_; lean_object* v___y_5584_; uint64_t v___y_5585_; uint32_t v___y_5586_; uint64_t v___y_5587_; uint64_t v___y_5588_; uint64_t v___y_5593_; lean_object* v___y_5594_; uint64_t v___y_5595_; uint32_t v___y_5596_; uint64_t v___y_5597_; uint64_t v___y_5598_; uint64_t v___y_5599_; uint64_t v___y_5600_; lean_object* v___y_5601_; uint64_t v___y_5602_; uint32_t v___y_5603_; uint64_t v___y_5604_; lean_object* v___y_5609_; uint64_t v___y_5610_; uint32_t v___y_5611_; uint64_t v___y_5612_; uint64_t v___y_5613_; lean_object* v___y_5614_; uint64_t v___y_5615_; uint64_t v___y_5616_; uint32_t v___y_5617_; uint64_t v___y_5618_; uint64_t v___y_5623_; lean_object* v___y_5624_; uint64_t v___y_5625_; uint32_t v___y_5626_; uint64_t v___y_5627_; uint64_t v___y_5628_; uint64_t v___y_5629_; lean_object* v___y_5630_; uint64_t v___y_5631_; uint64_t v___y_5632_; uint32_t v___y_5633_; uint64_t v___y_5634_; lean_object* v___y_5639_; uint64_t v___y_5640_; uint32_t v___y_5641_; uint64_t v___y_5642_; uint64_t v___y_5643_; lean_object* v___y_5644_; uint64_t v___y_5645_; uint64_t v___y_5646_; uint32_t v___y_5647_; uint64_t v___y_5648_; uint64_t v___y_5653_; lean_object* v___y_5654_; uint64_t v___y_5655_; uint32_t v___y_5656_; uint64_t v___y_5657_; uint64_t v___y_5658_; uint64_t v___y_5659_; uint64_t v___y_5660_; lean_object* v___y_5661_; uint64_t v___y_5662_; uint32_t v___y_5663_; uint64_t v___y_5664_; lean_object* v___y_5669_; uint64_t v___y_5670_; uint32_t v___y_5671_; uint64_t v___y_5672_; uint64_t v___y_5673_; uint64_t v___y_5674_; lean_object* v___y_5675_; uint64_t v___y_5676_; uint32_t v___y_5677_; uint64_t v___y_5678_; uint64_t v___y_5683_; lean_object* v___y_5684_; uint64_t v___y_5685_; uint32_t v___y_5686_; uint64_t v___y_5687_; uint64_t v___y_5688_; uint64_t v___y_5689_; lean_object* v___y_5690_; uint64_t v___y_5691_; uint32_t v___y_5692_; uint64_t v___y_5693_; uint64_t v___y_5694_; lean_object* v___y_5699_; uint64_t v___y_5700_; uint64_t v___y_5701_; uint32_t v___y_5702_; uint64_t v___y_5703_; uint64_t v___y_5704_; lean_object* v___y_5705_; uint64_t v___y_5706_; uint32_t v___y_5707_; uint64_t v___y_5708_; uint64_t v___y_5713_; lean_object* v___y_5714_; uint32_t v___y_5715_; uint64_t v___y_5716_; uint64_t v___y_5717_; lean_object* v___y_5718_; uint64_t v___y_5719_; uint64_t v___y_5720_; uint32_t v___y_5721_; uint64_t v___y_5722_; uint32_t v___y_5727_; uint64_t v___y_5728_; uint64_t v___y_5729_; uint32_t v___y_5730_; lean_object* v_fst_5731_; lean_object* v_snd_5732_; uint32_t v___y_5747_; uint8_t v___y_5748_; uint64_t v___y_5749_; uint64_t v___y_5750_; uint64_t v___y_5751_; uint8_t v___y_5752_; uint32_t v___y_5753_; uint64_t v___y_5754_; uint8_t v___y_5755_; uint32_t v___y_5767_; uint64_t v___y_5768_; uint8_t v___y_5769_; uint64_t v___y_5770_; uint64_t v___y_5771_; uint8_t v___y_5772_; uint64_t v___y_5773_; uint32_t v___y_5774_; uint8_t v___y_5775_; uint64_t v___y_5780_; uint64_t v___y_5781_; uint32_t v___y_5782_; uint8_t v___y_5783_; uint64_t v___y_5784_; uint8_t v___y_5785_; uint64_t v___y_5786_; uint32_t v___y_5787_; uint8_t v___y_5788_; uint64_t v___y_5800_; uint64_t v___y_5801_; uint32_t v___y_5802_; uint8_t v___y_5803_; uint64_t v___y_5804_; uint64_t v___y_5805_; uint8_t v___y_5806_; uint32_t v___y_5807_; uint8_t v___y_5808_; uint64_t v___y_5813_; uint32_t v___y_5814_; uint64_t v___y_5815_; uint8_t v___y_5816_; uint64_t v___y_5817_; uint8_t v___y_5818_; uint64_t v___y_5819_; uint32_t v___y_5820_; uint64_t v___y_5821_; uint64_t v___y_5832_; uint32_t v___y_5833_; uint32_t v___y_5834_; uint8_t v___y_5835_; uint64_t v___y_5836_; uint64_t v___y_5837_; uint8_t v___y_5838_; uint32_t v___y_5839_; uint64_t v___y_5840_; uint32_t v___y_5846_; uint64_t v___y_5847_; uint32_t v___y_5848_; uint32_t v___y_5849_; uint8_t v___y_5850_; uint64_t v___y_5851_; uint8_t v___y_5852_; uint32_t v___y_5853_; uint64_t v___y_5854_; uint32_t v___y_5860_; uint32_t v___y_5861_; uint32_t v___y_5862_; uint8_t v___y_5863_; uint64_t v___y_5864_; uint8_t v___y_5865_; uint32_t v___y_5866_; uint64_t v___y_5867_; uint32_t v___y_5877_; uint32_t v___y_5878_; uint32_t v___y_5879_; uint8_t v___y_5880_; uint64_t v___y_5881_; uint32_t v___y_5882_; uint8_t v___y_5883_; uint32_t v___y_5893_; uint32_t v___y_5894_; uint8_t v___y_5895_; uint32_t v___y_5896_; uint64_t v___y_5897_; uint8_t v___y_5898_; uint32_t v___y_5899_; uint8_t v___y_5900_; uint32_t v___y_5906_; uint32_t v___y_5907_; uint64_t v___y_5912_; lean_object* v___y_5913_; uint64_t v___y_5914_; uint32_t v___y_5929_; uint32_t v___y_5930_; uint32_t v___y_5931_; uint32_t v___y_5932_; uint32_t v___y_5933_; uint32_t v___y_5941_; uint32_t v___y_5942_; uint32_t v___y_5943_; lean_object* v___y_5944_; uint32_t v___y_5945_; uint64_t v___y_5950_; uint64_t v___y_5951_; uint32_t v___y_5952_; uint32_t v___y_5953_; lean_object* v___y_5954_; uint64_t v___y_5955_; uint64_t v___y_5965_; uint32_t v___y_5966_; uint64_t v___y_5967_; uint8_t v___y_5968_; uint32_t v___y_5969_; lean_object* v___y_5970_; uint64_t v___y_5971_; uint64_t v___y_5979_; uint32_t v___y_5980_; uint64_t v___y_5981_; uint64_t v___y_5982_; uint32_t v___y_5983_; lean_object* v___y_5984_; uint64_t v___y_5985_; uint64_t v___y_5990_; lean_object* v___y_5991_; uint32_t v___y_5992_; uint64_t v___y_5993_; uint64_t v___y_5994_; uint64_t v___y_5995_; uint64_t v___y_5996_; uint32_t v___y_5997_; lean_object* v___y_5998_; uint64_t v___y_5999_; uint64_t v___y_6058_; uint64_t v___y_6059_; lean_object* v___y_6060_; uint32_t v___y_6061_; uint64_t v___y_6062_; uint64_t v___y_6063_; uint64_t v___y_6064_; uint64_t v___y_6065_; uint32_t v___y_6066_; lean_object* v___y_6067_; uint64_t v___y_6068_; uint64_t v___y_6073_; lean_object* v___y_6074_; uint32_t v___y_6075_; uint64_t v___y_6076_; uint64_t v___y_6077_; uint64_t v___y_6078_; uint64_t v___y_6079_; uint64_t v___y_6080_; uint64_t v___y_6081_; uint64_t v___y_6082_; uint32_t v___y_6083_; lean_object* v___y_6084_; uint64_t v___y_6085_; uint64_t v___y_6090_; lean_object* v___y_6091_; uint32_t v___y_6092_; uint64_t v___y_6093_; uint64_t v___y_6094_; uint64_t v___y_6095_; uint64_t v___y_6096_; uint64_t v___y_6097_; uint32_t v___y_6098_; lean_object* v___y_6099_; uint64_t v___y_6100_; uint64_t v___y_6105_; lean_object* v___y_6106_; uint64_t v___y_6107_; uint32_t v___y_6108_; uint64_t v___y_6109_; uint64_t v___y_6110_; uint64_t v___y_6111_; uint64_t v___y_6112_; uint64_t v___y_6113_; uint32_t v___y_6114_; lean_object* v___y_6115_; uint64_t v___y_6116_; uint64_t v___y_6117_; uint64_t v___y_6122_; lean_object* v___y_6123_; uint32_t v___y_6124_; uint64_t v___y_6125_; uint64_t v___y_6126_; uint64_t v___y_6127_; uint64_t v___y_6128_; uint64_t v___y_6129_; uint32_t v___y_6130_; lean_object* v___y_6131_; uint64_t v___y_6132_; uint64_t v___y_6137_; lean_object* v___y_6138_; uint32_t v___y_6139_; uint64_t v___y_6140_; uint64_t v___y_6141_; uint64_t v___y_6142_; uint64_t v___y_6143_; uint64_t v___y_6144_; uint64_t v___y_6145_; uint64_t v___y_6146_; uint32_t v___y_6147_; lean_object* v___y_6148_; uint64_t v___y_6149_; uint64_t v___y_6154_; lean_object* v___y_6155_; uint32_t v___y_6156_; uint64_t v___y_6157_; uint64_t v___y_6158_; uint64_t v___y_6159_; uint64_t v___y_6160_; uint64_t v___y_6161_; uint32_t v___y_6162_; lean_object* v___y_6163_; uint64_t v___y_6164_; uint64_t v___y_6169_; lean_object* v___y_6170_; uint64_t v___y_6171_; uint32_t v___y_6172_; uint64_t v___y_6173_; uint64_t v___y_6174_; uint64_t v___y_6175_; uint64_t v___y_6176_; uint64_t v___y_6177_; uint32_t v___y_6178_; lean_object* v___y_6179_; uint64_t v___y_6180_; uint64_t v___y_6181_; uint64_t v___y_6186_; lean_object* v___y_6187_; uint32_t v___y_6188_; uint64_t v___y_6189_; uint64_t v___y_6190_; uint64_t v___y_6191_; uint64_t v___y_6192_; uint32_t v___y_6193_; lean_object* v___y_6194_; uint64_t v___y_6195_; uint64_t v___y_6196_; uint64_t v___y_6201_; lean_object* v___y_6202_; uint32_t v___y_6203_; uint64_t v___y_6204_; uint64_t v___y_6205_; uint64_t v___y_6206_; uint64_t v___y_6207_; uint64_t v___y_6208_; uint32_t v___y_6209_; lean_object* v___y_6210_; uint64_t v___y_6211_; uint32_t v___y_6216_; uint64_t v___y_6217_; uint64_t v___y_6218_; uint64_t v___y_6219_; uint64_t v___y_6220_; uint32_t v___y_6221_; lean_object* v_fst_6222_; lean_object* v_snd_6223_; uint32_t v___y_6237_; uint32_t v___y_6238_; lean_object* v___y_6243_; uint64_t v___y_6244_; uint64_t v___y_6245_; uint32_t v___y_6260_; uint32_t v___y_6261_; uint32_t v___y_6262_; uint32_t v___y_6263_; uint32_t v___y_6264_; lean_object* v___y_6272_; uint32_t v___y_6273_; uint32_t v___y_6274_; uint32_t v___y_6275_; uint32_t v___y_6276_; lean_object* v___y_6281_; uint32_t v___y_6282_; uint64_t v___y_6283_; uint64_t v___y_6284_; uint32_t v___y_6285_; uint64_t v___y_6286_; lean_object* v___y_6296_; uint32_t v___y_6297_; uint64_t v___y_6298_; uint8_t v___y_6299_; uint32_t v___y_6300_; uint64_t v___y_6301_; uint64_t v___y_6302_; lean_object* v___y_6310_; uint32_t v___y_6311_; uint64_t v___y_6312_; uint64_t v___y_6313_; uint64_t v___y_6314_; uint32_t v___y_6315_; uint64_t v___y_6316_; lean_object* v___y_6321_; uint32_t v___y_6322_; uint64_t v___y_6323_; uint64_t v___y_6324_; uint64_t v___y_6325_; uint64_t v___y_6326_; lean_object* v___y_6327_; uint32_t v___y_6328_; uint64_t v___y_6329_; uint64_t v___y_6330_; lean_object* v___y_6389_; uint32_t v___y_6390_; uint64_t v___y_6391_; uint64_t v___y_6392_; uint64_t v___y_6393_; uint64_t v___y_6394_; uint64_t v___y_6395_; uint32_t v___y_6396_; lean_object* v___y_6397_; uint64_t v___y_6398_; uint64_t v___y_6399_; lean_object* v___y_6404_; uint32_t v___y_6405_; uint64_t v___y_6406_; uint64_t v___y_6407_; uint64_t v___y_6408_; uint64_t v___y_6409_; uint64_t v___y_6410_; uint64_t v___y_6411_; uint64_t v___y_6412_; lean_object* v___y_6413_; uint32_t v___y_6414_; uint64_t v___y_6415_; uint64_t v___y_6416_; lean_object* v___y_6421_; uint32_t v___y_6422_; uint64_t v___y_6423_; uint64_t v___y_6424_; uint64_t v___y_6425_; uint64_t v___y_6426_; uint64_t v___y_6427_; uint32_t v___y_6428_; lean_object* v___y_6429_; uint64_t v___y_6430_; uint64_t v___y_6431_; uint64_t v___y_6436_; uint64_t v___y_6437_; lean_object* v___y_6438_; uint32_t v___y_6439_; uint64_t v___y_6440_; uint64_t v___y_6441_; uint64_t v___y_6442_; uint64_t v___y_6443_; uint64_t v___y_6444_; uint64_t v___y_6445_; lean_object* v___y_6446_; uint32_t v___y_6447_; uint64_t v___y_6448_; uint64_t v___y_6453_; lean_object* v___y_6454_; uint32_t v___y_6455_; uint64_t v___y_6456_; uint64_t v___y_6457_; uint64_t v___y_6458_; uint64_t v___y_6459_; uint32_t v___y_6460_; lean_object* v___y_6461_; uint64_t v___y_6462_; uint64_t v___y_6463_; lean_object* v___y_6468_; uint64_t v___y_6469_; uint32_t v___y_6470_; uint64_t v___y_6471_; uint64_t v___y_6472_; uint64_t v___y_6473_; uint64_t v___y_6474_; uint64_t v___y_6475_; uint64_t v___y_6476_; lean_object* v___y_6477_; uint32_t v___y_6478_; uint64_t v___y_6479_; uint64_t v___y_6480_; lean_object* v___y_6485_; uint32_t v___y_6486_; uint64_t v___y_6487_; uint64_t v___y_6488_; uint64_t v___y_6489_; uint64_t v___y_6490_; uint32_t v___y_6491_; lean_object* v___y_6492_; uint64_t v___y_6493_; uint64_t v___y_6494_; uint64_t v___y_6495_; lean_object* v___y_6500_; uint32_t v___y_6501_; uint64_t v___y_6502_; uint64_t v___y_6503_; uint64_t v___y_6504_; uint64_t v___y_6505_; uint64_t v___y_6506_; uint64_t v___y_6507_; uint64_t v___y_6508_; uint64_t v___y_6509_; lean_object* v___y_6510_; uint32_t v___y_6511_; uint64_t v___y_6512_; lean_object* v___y_6517_; uint32_t v___y_6518_; uint64_t v___y_6519_; uint64_t v___y_6520_; uint64_t v___y_6521_; uint64_t v___y_6522_; uint64_t v___y_6523_; uint32_t v___y_6524_; lean_object* v___y_6525_; uint64_t v___y_6526_; uint64_t v___y_6527_; lean_object* v___y_6532_; uint32_t v___y_6533_; uint64_t v___y_6534_; uint64_t v___y_6535_; uint64_t v___y_6536_; uint64_t v___y_6537_; uint64_t v___y_6538_; uint64_t v___y_6539_; lean_object* v___y_6540_; uint32_t v___y_6541_; uint64_t v___y_6542_; uint32_t v___y_6547_; uint64_t v___y_6548_; uint64_t v___y_6549_; uint64_t v___y_6550_; uint64_t v___y_6551_; uint32_t v___y_6552_; lean_object* v_fst_6553_; lean_object* v_snd_6554_; uint8_t v___y_6568_; uint64_t v___y_6569_; uint32_t v___y_6570_; uint64_t v___y_6571_; uint8_t v___y_6572_; uint64_t v___y_6573_; uint64_t v___y_6574_; uint64_t v___y_6575_; uint32_t v___y_6576_; uint64_t v___y_6577_; uint8_t v___y_6578_; uint8_t v___y_6590_; uint64_t v___y_6591_; uint32_t v___y_6592_; uint64_t v___y_6593_; uint64_t v___y_6594_; uint64_t v___y_6595_; uint8_t v___y_6596_; uint64_t v___y_6597_; uint32_t v___y_6598_; uint64_t v___y_6599_; uint8_t v___y_6600_; uint8_t v___y_6605_; uint64_t v___y_6606_; uint32_t v___y_6607_; uint64_t v___y_6608_; uint64_t v___y_6609_; uint64_t v___y_6610_; uint8_t v___y_6611_; uint64_t v___y_6612_; uint64_t v___y_6613_; uint32_t v___y_6614_; uint8_t v___y_6615_; uint8_t v___y_6627_; uint64_t v___y_6628_; uint32_t v___y_6629_; uint64_t v___y_6630_; uint64_t v___y_6631_; uint64_t v___y_6632_; uint64_t v___y_6633_; uint8_t v___y_6634_; uint64_t v___y_6635_; uint32_t v___y_6636_; uint8_t v___y_6637_; uint8_t v___y_6642_; uint64_t v___y_6643_; uint32_t v___y_6644_; uint64_t v___y_6645_; uint64_t v___y_6646_; uint8_t v___y_6647_; uint64_t v___y_6648_; uint64_t v___y_6649_; uint32_t v___y_6650_; uint64_t v___y_6651_; uint64_t v___y_6652_; uint8_t v___y_6663_; uint64_t v___y_6664_; uint32_t v___y_6665_; uint32_t v___y_6666_; uint64_t v___y_6667_; uint8_t v___y_6668_; uint64_t v___y_6669_; uint64_t v___y_6670_; uint32_t v___y_6671_; uint64_t v___y_6672_; uint64_t v___y_6673_; uint32_t v___y_6679_; uint8_t v___y_6680_; uint64_t v___y_6681_; uint32_t v___y_6682_; uint64_t v___y_6683_; uint32_t v___y_6684_; uint64_t v___y_6685_; uint8_t v___y_6686_; uint64_t v___y_6687_; uint32_t v___y_6688_; uint64_t v___y_6689_; uint8_t v___y_6695_; uint32_t v___y_6696_; uint32_t v___y_6697_; uint32_t v___y_6698_; uint64_t v___y_6699_; uint8_t v___y_6700_; uint64_t v___y_6701_; uint64_t v___y_6702_; uint32_t v___y_6703_; uint64_t v___y_6704_; uint32_t v___y_6714_; uint8_t v___y_6715_; uint32_t v___y_6716_; uint64_t v___y_6717_; uint32_t v___y_6718_; uint64_t v___y_6719_; uint64_t v___y_6720_; uint32_t v___y_6721_; uint8_t v___y_6722_; uint32_t v___y_6732_; uint32_t v___y_6733_; uint8_t v___y_6734_; uint32_t v___y_6735_; uint64_t v___y_6736_; uint64_t v___y_6737_; uint64_t v___y_6738_; uint8_t v___y_6739_; uint32_t v___y_6740_; uint8_t v___y_6741_; uint32_t v___y_6747_; uint32_t v___y_6748_; uint32_t v___y_6749_; uint32_t v___y_6750_; uint32_t v___y_6751_; uint32_t v___y_6759_; uint8_t v___y_6760_; uint32_t v___y_6761_; uint32_t v___y_6762_; uint32_t v___y_6763_; uint32_t v___y_6767_; uint8_t v___y_6768_; uint32_t v___y_6769_; uint32_t v___y_6770_; uint64_t v___y_6771_; uint8_t v___y_6778_; uint32_t v___y_6779_; uint64_t v___y_6780_; uint8_t v___y_6781_; uint32_t v___y_6782_; uint64_t v___y_6783_; uint8_t v___y_6793_; uint64_t v___y_6794_; uint32_t v___y_6795_; uint64_t v___y_6796_; uint32_t v___y_6797_; uint64_t v___y_6798_; uint32_t v___y_6803_; uint8_t v___y_6804_; uint32_t v___y_6805_; uint64_t v___y_6806_; uint32_t v___y_6807_; uint64_t v___y_6808_; uint8_t v___y_6809_; uint8_t v___y_6810_; uint32_t v___y_6811_; uint64_t v___y_6812_; uint32_t v___y_6841_; uint8_t v___y_6842_; uint32_t v___y_6843_; uint32_t v___y_6844_; uint64_t v___y_6845_; uint8_t v___y_6846_; uint8_t v___y_6847_; uint32_t v___y_6848_; uint64_t v___y_6849_; uint32_t v___y_6859_; uint32_t v___y_6860_; lean_object* v___y_6865_; uint64_t v___y_6866_; uint64_t v___y_6867_; uint32_t v___y_6882_; uint32_t v___y_6883_; uint32_t v___y_6884_; uint32_t v___y_6885_; uint32_t v___y_6886_; uint32_t v___y_6894_; uint32_t v___y_6895_; lean_object* v___y_6896_; uint32_t v___y_6897_; uint32_t v___y_6898_; uint32_t v___y_6903_; uint64_t v___y_6904_; lean_object* v___y_6905_; uint32_t v___y_6906_; uint64_t v___y_6907_; uint64_t v___y_6908_; uint32_t v___y_6918_; uint8_t v___y_6919_; uint64_t v___y_6920_; lean_object* v___y_6921_; uint32_t v___y_6922_; uint64_t v___y_6923_; uint64_t v___y_6924_; uint32_t v___y_6932_; lean_object* v___y_6933_; uint64_t v___y_6934_; uint32_t v___y_6935_; uint64_t v___y_6936_; uint64_t v___y_6937_; lean_object* v___y_6943_; uint32_t v___y_6944_; uint64_t v___y_6945_; lean_object* v___y_6946_; uint32_t v___y_6947_; uint64_t v___y_6948_; uint64_t v___y_6949_; uint64_t v___y_6950_; lean_object* v___y_7014_; uint32_t v___y_7015_; uint64_t v___y_7016_; uint64_t v___y_7017_; lean_object* v___y_7018_; uint64_t v___y_7019_; uint32_t v___y_7020_; uint64_t v___y_7021_; uint64_t v___y_7022_; uint64_t v___y_7028_; lean_object* v___y_7029_; uint32_t v___y_7030_; uint64_t v___y_7031_; uint64_t v___y_7032_; uint64_t v___y_7033_; lean_object* v___y_7034_; uint32_t v___y_7035_; uint64_t v___y_7036_; uint64_t v___y_7037_; uint64_t v___y_7038_; uint64_t v___y_7043_; lean_object* v___y_7044_; uint32_t v___y_7045_; uint64_t v___y_7046_; lean_object* v___y_7047_; uint64_t v___y_7048_; uint32_t v___y_7049_; uint64_t v___y_7050_; uint64_t v___y_7051_; lean_object* v___y_7056_; uint32_t v___y_7057_; uint64_t v___y_7058_; uint64_t v___y_7059_; lean_object* v___y_7060_; uint64_t v___y_7061_; uint32_t v___y_7062_; uint64_t v___y_7063_; uint64_t v___y_7064_; uint64_t v___y_7065_; uint64_t v___y_7066_; lean_object* v___y_7071_; uint32_t v___y_7072_; uint64_t v___y_7073_; lean_object* v___y_7074_; uint64_t v___y_7075_; uint32_t v___y_7076_; uint64_t v___y_7077_; uint64_t v___y_7078_; uint64_t v___y_7079_; lean_object* v___y_7084_; uint32_t v___y_7085_; uint64_t v___y_7086_; lean_object* v___y_7087_; uint64_t v___y_7088_; uint32_t v___y_7089_; uint64_t v___y_7090_; uint64_t v___y_7091_; uint64_t v___y_7092_; uint64_t v___y_7093_; uint64_t v___y_7094_; lean_object* v___y_7099_; uint32_t v___y_7100_; uint64_t v___y_7101_; lean_object* v___y_7102_; uint64_t v___y_7103_; uint32_t v___y_7104_; uint64_t v___y_7105_; uint64_t v___y_7106_; uint64_t v___y_7107_; uint64_t v___y_7112_; lean_object* v___y_7113_; uint32_t v___y_7114_; uint64_t v___y_7115_; uint64_t v___y_7116_; uint64_t v___y_7117_; lean_object* v___y_7118_; uint32_t v___y_7119_; uint64_t v___y_7120_; uint64_t v___y_7121_; uint64_t v___y_7122_; lean_object* v___y_7127_; uint64_t v___y_7128_; uint32_t v___y_7129_; uint64_t v___y_7130_; lean_object* v___y_7131_; uint64_t v___y_7132_; uint32_t v___y_7133_; uint64_t v___y_7134_; uint64_t v___y_7135_; lean_object* v___y_7140_; uint32_t v___y_7141_; uint64_t v___y_7142_; uint64_t v___y_7143_; lean_object* v___y_7144_; uint32_t v___y_7145_; uint64_t v___y_7146_; uint64_t v___y_7147_; uint64_t v___y_7148_; uint32_t v___y_7153_; uint32_t v___y_7154_; uint64_t v___y_7155_; lean_object* v_fst_7156_; lean_object* v_snd_7157_; uint32_t v___y_7172_; uint32_t v___y_7173_; lean_object* v___y_7178_; uint64_t v___y_7179_; uint64_t v___y_7180_; uint32_t v___y_7195_; uint32_t v___y_7196_; uint32_t v___y_7197_; uint32_t v___y_7198_; uint32_t v___y_7199_; uint32_t v___y_7207_; uint32_t v___y_7208_; lean_object* v___y_7209_; uint32_t v___y_7210_; uint32_t v___y_7211_; uint32_t v___y_7216_; lean_object* v___y_7217_; uint64_t v___y_7218_; uint64_t v___y_7219_; uint32_t v___y_7220_; uint64_t v___y_7221_; uint32_t v___y_7231_; lean_object* v___y_7232_; uint64_t v___y_7233_; uint8_t v___y_7234_; uint64_t v___y_7235_; uint32_t v___y_7236_; uint64_t v___y_7237_; uint64_t v___y_7245_; uint32_t v___y_7246_; lean_object* v___y_7247_; uint64_t v___y_7248_; uint32_t v___y_7249_; uint64_t v___y_7250_; uint32_t v___y_7256_; lean_object* v___y_7257_; lean_object* v___y_7258_; uint64_t v___y_7259_; uint64_t v___y_7260_; uint64_t v___y_7261_; uint32_t v___y_7262_; uint64_t v___y_7263_; uint32_t v___y_7327_; lean_object* v___y_7328_; lean_object* v___y_7329_; uint64_t v___y_7330_; uint64_t v___y_7331_; uint64_t v___y_7332_; uint32_t v___y_7333_; uint64_t v___y_7334_; uint64_t v___y_7335_; uint32_t v___y_7341_; lean_object* v___y_7342_; uint64_t v___y_7343_; lean_object* v___y_7344_; uint64_t v___y_7345_; uint64_t v___y_7346_; uint64_t v___y_7347_; uint64_t v___y_7348_; uint32_t v___y_7349_; uint64_t v___y_7350_; uint64_t v___y_7351_; uint32_t v___y_7356_; lean_object* v___y_7357_; lean_object* v___y_7358_; uint64_t v___y_7359_; uint64_t v___y_7360_; uint64_t v___y_7361_; uint32_t v___y_7362_; uint64_t v___y_7363_; uint64_t v___y_7364_; uint32_t v___y_7369_; lean_object* v___y_7370_; lean_object* v___y_7371_; uint64_t v___y_7372_; uint64_t v___y_7373_; uint64_t v___y_7374_; uint64_t v___y_7375_; uint64_t v___y_7376_; uint32_t v___y_7377_; uint64_t v___y_7378_; uint64_t v___y_7379_; uint32_t v___y_7384_; lean_object* v___y_7385_; lean_object* v___y_7386_; uint64_t v___y_7387_; uint64_t v___y_7388_; uint64_t v___y_7389_; uint32_t v___y_7390_; uint64_t v___y_7391_; uint64_t v___y_7392_; uint32_t v___y_7397_; uint64_t v___y_7398_; lean_object* v___y_7399_; lean_object* v___y_7400_; uint64_t v___y_7401_; uint64_t v___y_7402_; uint64_t v___y_7403_; uint64_t v___y_7404_; uint32_t v___y_7405_; uint64_t v___y_7406_; uint64_t v___y_7407_; uint32_t v___y_7412_; lean_object* v___y_7413_; lean_object* v___y_7414_; uint64_t v___y_7415_; uint64_t v___y_7416_; uint64_t v___y_7417_; uint64_t v___y_7418_; uint32_t v___y_7419_; uint64_t v___y_7420_; uint64_t v___y_7425_; uint32_t v___y_7426_; lean_object* v___y_7427_; lean_object* v___y_7428_; uint64_t v___y_7429_; uint64_t v___y_7430_; uint64_t v___y_7431_; uint64_t v___y_7432_; uint32_t v___y_7433_; uint64_t v___y_7434_; uint64_t v___y_7435_; uint32_t v___y_7440_; lean_object* v___y_7441_; lean_object* v___y_7442_; uint64_t v___y_7443_; uint64_t v___y_7444_; uint64_t v___y_7445_; uint64_t v___y_7446_; uint32_t v___y_7447_; uint64_t v___y_7448_; uint32_t v___y_7453_; lean_object* v___y_7454_; lean_object* v___y_7455_; uint64_t v___y_7456_; uint64_t v___y_7457_; uint64_t v___y_7458_; uint64_t v___y_7459_; uint32_t v___y_7460_; uint64_t v___y_7461_; uint64_t v___y_7466_; uint32_t v___y_7467_; uint32_t v___y_7468_; lean_object* v_fst_7469_; lean_object* v_snd_7470_; uint64_t v___y_7485_; uint32_t v___y_7486_; uint8_t v___y_7487_; uint64_t v___y_7488_; uint64_t v___y_7489_; uint8_t v___y_7490_; uint32_t v___y_7491_; uint8_t v___y_7492_; uint64_t v___y_7504_; uint64_t v___y_7505_; uint8_t v___y_7506_; uint32_t v___y_7507_; uint64_t v___y_7508_; uint8_t v___y_7509_; uint32_t v___y_7510_; uint8_t v___y_7511_; uint64_t v___y_7516_; uint32_t v___y_7517_; uint8_t v___y_7518_; uint64_t v___y_7519_; uint8_t v___y_7520_; uint32_t v___y_7521_; uint64_t v___y_7522_; uint8_t v___y_7523_; uint64_t v___y_7535_; uint8_t v___y_7536_; uint32_t v___y_7537_; uint64_t v___y_7538_; uint8_t v___y_7539_; uint32_t v___y_7540_; uint64_t v___y_7541_; uint8_t v___y_7542_; uint64_t v___y_7547_; uint8_t v___y_7548_; uint32_t v___y_7549_; uint64_t v___y_7550_; uint8_t v___y_7551_; uint32_t v___y_7552_; uint64_t v___y_7553_; uint64_t v___y_7554_; uint8_t v___y_7565_; uint64_t v___y_7566_; uint32_t v___y_7567_; uint32_t v___y_7568_; uint64_t v___y_7569_; uint8_t v___y_7570_; uint32_t v___y_7571_; uint64_t v___y_7572_; uint32_t v___y_7579_; uint32_t v___y_7580_; uint8_t v___y_7581_; uint64_t v___y_7582_; uint32_t v___y_7583_; uint8_t v___y_7584_; uint32_t v___y_7585_; uint64_t v___y_7586_; uint32_t v___y_7593_; uint8_t v___y_7594_; uint32_t v___y_7595_; uint32_t v___y_7596_; uint8_t v___y_7597_; uint32_t v___y_7598_; uint64_t v___y_7599_; uint32_t v___y_7609_; uint32_t v___y_7610_; uint8_t v___y_7611_; uint32_t v___y_7612_; uint32_t v___y_7613_; uint8_t v___y_7614_; uint32_t v___y_7624_; uint32_t v___y_7625_; uint32_t v___y_7626_; uint8_t v___y_7627_; uint8_t v___y_7628_; uint32_t v___y_7629_; uint8_t v___y_7630_; uint32_t v___y_7636_; uint32_t v___y_7637_; uint32_t v___y_7638_; uint8_t v___y_7639_; uint32_t v___y_7640_; uint8_t v___y_7641_; uint32_t v___y_7647_; uint8_t v___y_7648_; uint32_t v___y_7649_; uint32_t v___y_7650_; uint64_t v___y_7651_; uint8_t v___y_7652_; uint32_t v___y_7653_; uint8_t v___y_7654_; uint32_t v___y_7664_; uint8_t v___y_7665_; uint32_t v___y_7666_; uint32_t v___y_7667_; uint64_t v___y_7668_; uint8_t v___y_7669_; uint8_t v___y_7670_; uint32_t v___y_7671_; uint8_t v___y_7672_; uint32_t v___y_7675_; uint32_t v___y_7676_; uint32_t v___y_7677_; uint64_t v___y_7678_; uint8_t v___y_7679_; uint8_t v___y_7680_; uint32_t v___y_7681_; uint8_t v___y_7682_; uint32_t v___y_7688_; uint32_t v___y_7689_; uint64_t v___y_7694_; lean_object* v___y_7695_; uint64_t v___y_7696_; uint32_t v___y_7711_; uint32_t v___y_7712_; uint32_t v___y_7713_; uint32_t v___y_7714_; uint32_t v___y_7715_; uint32_t v___y_7723_; uint32_t v___y_7724_; lean_object* v___y_7725_; uint32_t v___y_7726_; uint32_t v___y_7727_; uint64_t v___y_7732_; uint32_t v___y_7733_; uint64_t v___y_7734_; lean_object* v___y_7735_; uint32_t v___y_7736_; uint64_t v___y_7737_; uint64_t v___y_7747_; uint32_t v___y_7748_; uint64_t v___y_7749_; uint8_t v___y_7750_; lean_object* v___y_7751_; uint32_t v___y_7752_; uint64_t v___y_7753_; uint64_t v___y_7761_; uint32_t v___y_7762_; lean_object* v___y_7763_; uint32_t v___y_7764_; uint64_t v___y_7765_; uint64_t v___y_7766_; uint64_t v___y_7772_; lean_object* v___y_7773_; uint32_t v___y_7774_; uint64_t v___y_7775_; lean_object* v___y_7776_; uint32_t v___y_7777_; uint64_t v___y_7778_; uint64_t v___y_7779_; uint64_t v___y_7843_; uint32_t v___y_7844_; lean_object* v___y_7845_; uint64_t v___y_7846_; lean_object* v___y_7847_; uint64_t v___y_7848_; uint32_t v___y_7849_; uint64_t v___y_7850_; uint64_t v___y_7851_; uint64_t v___y_7857_; uint64_t v___y_7858_; uint64_t v___y_7859_; lean_object* v___y_7860_; uint32_t v___y_7861_; uint64_t v___y_7862_; lean_object* v___y_7863_; uint32_t v___y_7864_; uint64_t v___y_7865_; uint64_t v___y_7866_; uint64_t v___y_7867_; uint64_t v___y_7872_; uint64_t v___y_7873_; uint32_t v___y_7874_; lean_object* v___y_7875_; uint64_t v___y_7876_; lean_object* v___y_7877_; uint32_t v___y_7878_; uint64_t v___y_7879_; uint64_t v___y_7880_; uint64_t v___y_7885_; lean_object* v___y_7886_; uint32_t v___y_7887_; uint64_t v___y_7888_; lean_object* v___y_7889_; uint64_t v___y_7890_; uint64_t v___y_7891_; uint64_t v___y_7892_; uint32_t v___y_7893_; uint64_t v___y_7894_; uint64_t v___y_7895_; uint64_t v___y_7900_; uint32_t v___y_7901_; lean_object* v___y_7902_; uint64_t v___y_7903_; lean_object* v___y_7904_; uint64_t v___y_7905_; uint32_t v___y_7906_; uint64_t v___y_7907_; uint64_t v___y_7908_; uint64_t v___y_7913_; lean_object* v___y_7914_; uint32_t v___y_7915_; uint64_t v___y_7916_; uint64_t v___y_7917_; uint64_t v___y_7918_; lean_object* v___y_7919_; uint64_t v___y_7920_; uint32_t v___y_7921_; uint64_t v___y_7922_; uint64_t v___y_7923_; uint64_t v___y_7928_; uint32_t v___y_7929_; lean_object* v___y_7930_; uint64_t v___y_7931_; uint64_t v___y_7932_; lean_object* v___y_7933_; uint32_t v___y_7934_; uint64_t v___y_7935_; uint64_t v___y_7936_; uint64_t v___y_7941_; uint64_t v___y_7942_; lean_object* v___y_7943_; uint32_t v___y_7944_; uint64_t v___y_7945_; uint64_t v___y_7946_; lean_object* v___y_7947_; uint64_t v___y_7948_; uint32_t v___y_7949_; uint64_t v___y_7950_; uint64_t v___y_7951_; uint64_t v___y_7956_; uint32_t v___y_7957_; lean_object* v___y_7958_; uint64_t v___y_7959_; lean_object* v___y_7960_; uint32_t v___y_7961_; uint64_t v___y_7962_; uint64_t v___y_7963_; uint64_t v___y_7964_; uint64_t v___y_7969_; lean_object* v___y_7970_; uint32_t v___y_7971_; uint64_t v___y_7972_; uint64_t v___y_7973_; lean_object* v___y_7974_; uint32_t v___y_7975_; uint64_t v___y_7976_; uint64_t v___y_7977_; uint32_t v___y_7982_; uint64_t v___y_7983_; uint32_t v___y_7984_; lean_object* v_fst_7985_; lean_object* v_snd_7986_; uint32_t v___y_8001_; uint32_t v___y_8002_; lean_object* v___y_8007_; uint64_t v___y_8008_; uint64_t v___y_8009_; uint32_t v___y_8024_; uint32_t v___y_8025_; uint32_t v___y_8026_; uint32_t v___y_8027_; uint32_t v___y_8028_; uint32_t v___y_8036_; uint32_t v___y_8037_; lean_object* v___y_8038_; uint32_t v___y_8039_; uint32_t v___y_8040_; uint32_t v___y_8045_; uint64_t v___y_8046_; lean_object* v___y_8047_; uint64_t v___y_8048_; uint32_t v___y_8049_; uint64_t v___y_8050_; uint8_t v___y_8060_; uint32_t v___y_8061_; uint64_t v___y_8062_; lean_object* v___y_8063_; uint64_t v___y_8064_; uint32_t v___y_8065_; uint64_t v___y_8066_; uint32_t v___y_8074_; uint64_t v___y_8075_; lean_object* v___y_8076_; uint64_t v___y_8077_; uint32_t v___y_8078_; uint64_t v___y_8079_; uint64_t v___y_8085_; uint32_t v___y_8086_; lean_object* v___y_8087_; uint64_t v___y_8088_; lean_object* v___y_8089_; uint64_t v___y_8090_; uint32_t v___y_8091_; uint64_t v___y_8092_; uint64_t v___y_8156_; uint32_t v___y_8157_; uint64_t v___y_8158_; lean_object* v___y_8159_; lean_object* v___y_8160_; uint64_t v___y_8161_; uint64_t v___y_8162_; uint32_t v___y_8163_; uint64_t v___y_8164_; uint64_t v___y_8170_; uint64_t v___y_8171_; uint32_t v___y_8172_; uint64_t v___y_8173_; lean_object* v___y_8174_; uint64_t v___y_8175_; uint64_t v___y_8176_; lean_object* v___y_8177_; uint64_t v___y_8178_; uint32_t v___y_8179_; uint64_t v___y_8180_; uint64_t v___y_8185_; uint32_t v___y_8186_; lean_object* v___y_8187_; uint64_t v___y_8188_; lean_object* v___y_8189_; uint64_t v___y_8190_; uint64_t v___y_8191_; uint32_t v___y_8192_; uint64_t v___y_8193_; uint64_t v___y_8198_; uint64_t v___y_8199_; uint32_t v___y_8200_; lean_object* v___y_8201_; uint64_t v___y_8202_; uint64_t v___y_8203_; lean_object* v___y_8204_; uint64_t v___y_8205_; uint64_t v___y_8206_; uint32_t v___y_8207_; uint64_t v___y_8208_; uint64_t v___y_8213_; uint64_t v___y_8214_; uint32_t v___y_8215_; lean_object* v___y_8216_; lean_object* v___y_8217_; uint64_t v___y_8218_; uint64_t v___y_8219_; uint32_t v___y_8220_; uint64_t v___y_8221_; uint64_t v___y_8226_; uint64_t v___y_8227_; uint64_t v___y_8228_; uint32_t v___y_8229_; uint64_t v___y_8230_; lean_object* v___y_8231_; uint64_t v___y_8232_; lean_object* v___y_8233_; uint64_t v___y_8234_; uint32_t v___y_8235_; uint64_t v___y_8236_; uint64_t v___y_8241_; uint64_t v___y_8242_; uint32_t v___y_8243_; lean_object* v___y_8244_; lean_object* v___y_8245_; uint64_t v___y_8246_; uint64_t v___y_8247_; uint32_t v___y_8248_; uint64_t v___y_8249_; uint64_t v___y_8254_; uint32_t v___y_8255_; uint64_t v___y_8256_; lean_object* v___y_8257_; uint64_t v___y_8258_; uint64_t v___y_8259_; lean_object* v___y_8260_; uint64_t v___y_8261_; uint32_t v___y_8262_; uint64_t v___y_8263_; uint64_t v___y_8264_; uint64_t v___y_8269_; uint32_t v___y_8270_; lean_object* v___y_8271_; uint64_t v___y_8272_; lean_object* v___y_8273_; uint64_t v___y_8274_; uint64_t v___y_8275_; uint32_t v___y_8276_; uint64_t v___y_8277_; uint64_t v___y_8282_; uint32_t v___y_8283_; uint64_t v___y_8284_; lean_object* v___y_8285_; uint64_t v___y_8286_; lean_object* v___y_8287_; uint64_t v___y_8288_; uint32_t v___y_8289_; uint64_t v___y_8290_; uint64_t v___y_8295_; uint32_t v___y_8296_; uint32_t v___y_8297_; lean_object* v_fst_8298_; lean_object* v_snd_8299_; uint64_t v___y_8314_; uint8_t v___y_8315_; uint64_t v___y_8316_; uint32_t v___y_8317_; uint8_t v___y_8318_; uint64_t v___y_8319_; uint32_t v___y_8320_; uint8_t v___y_8321_; uint64_t v___y_8333_; uint64_t v___y_8334_; uint8_t v___y_8335_; uint32_t v___y_8336_; uint8_t v___y_8337_; uint64_t v___y_8338_; uint32_t v___y_8339_; uint8_t v___y_8340_; uint8_t v___y_8345_; uint64_t v___y_8346_; uint32_t v___y_8347_; uint8_t v___y_8348_; uint64_t v___y_8349_; uint64_t v___y_8350_; uint32_t v___y_8351_; uint8_t v___y_8352_; uint64_t v___y_8364_; uint8_t v___y_8365_; uint32_t v___y_8366_; uint8_t v___y_8367_; uint64_t v___y_8368_; uint64_t v___y_8369_; uint32_t v___y_8370_; uint8_t v___y_8371_; uint8_t v___y_8376_; uint32_t v___y_8377_; uint8_t v___y_8378_; uint64_t v___y_8379_; uint64_t v___y_8380_; uint64_t v___y_8381_; uint32_t v___y_8382_; uint64_t v___y_8383_; uint8_t v___y_8394_; uint32_t v___y_8395_; uint32_t v___y_8396_; uint8_t v___y_8397_; uint64_t v___y_8398_; uint64_t v___y_8399_; uint32_t v___y_8400_; uint64_t v___y_8401_; uint32_t v___y_8408_; uint8_t v___y_8409_; uint32_t v___y_8410_; uint32_t v___y_8411_; uint8_t v___y_8412_; uint64_t v___y_8413_; uint32_t v___y_8414_; uint64_t v___y_8415_; uint32_t v___y_8422_; uint8_t v___y_8423_; uint32_t v___y_8424_; uint32_t v___y_8425_; uint8_t v___y_8426_; uint32_t v___y_8427_; uint64_t v___y_8428_; uint32_t v___y_8438_; uint32_t v___y_8439_; uint32_t v___y_8440_; uint8_t v___y_8441_; uint32_t v___y_8442_; uint8_t v___y_8443_; uint32_t v___y_8453_; uint32_t v___y_8454_; uint32_t v___y_8455_; uint8_t v___y_8456_; uint32_t v___y_8457_; uint8_t v___y_8458_; uint32_t v___y_8465_; uint32_t v___y_8466_; uint32_t v___y_8467_; uint64_t v___y_8468_; uint8_t v___y_8469_; uint32_t v___y_8470_; uint64_t v___y_8471_; uint32_t v___y_8483_; uint32_t v___y_8484_; uint8_t v___y_8485_; uint32_t v___y_8486_; uint64_t v___y_8487_; uint8_t v___y_8496_; uint32_t v___x_8510_; uint32_t v___x_8511_; uint32_t v___x_8512_; uint32_t v___x_8513_; uint8_t v___x_8514_; 
v___x_8510_ = 4278190079;
v___x_8511_ = 1;
v___x_8512_ = lean_uint32_shift_left(v_x_5072_, v___x_8511_);
v___x_8513_ = lean_uint32_sub(v___x_8512_, v___x_8511_);
v___x_8514_ = lean_uint32_dec_le(v___x_8510_, v___x_8513_);
if (v___x_8514_ == 0)
{
uint32_t v___x_8515_; uint32_t v___x_8516_; uint8_t v___x_8517_; 
v___x_8515_ = lean_uint32_shift_left(v_y_5073_, v___x_8511_);
v___x_8516_ = lean_uint32_sub(v___x_8515_, v___x_8511_);
v___x_8517_ = lean_uint32_dec_le(v___x_8510_, v___x_8516_);
v___y_8496_ = v___x_8517_;
goto v___jp_8495_;
}
else
{
v___y_8496_ = v___x_8514_;
goto v___jp_8495_;
}
v___jp_5074_:
{
uint32_t v___x_5076_; uint32_t v___x_5077_; 
v___x_5076_ = 8388608;
v___x_5077_ = lean_uint32_lor(v___y_5075_, v___x_5076_);
return v___x_5077_;
}
v___jp_5078_:
{
uint32_t v___x_5080_; uint32_t v___x_5081_; 
v___x_5080_ = 8388608;
v___x_5081_ = lean_uint32_lor(v___y_5079_, v___x_5080_);
return v___x_5081_;
}
v___jp_5082_:
{
uint32_t v___x_5084_; uint32_t v___x_5085_; 
v___x_5084_ = 8388608;
v___x_5085_ = lean_uint32_lor(v___y_5083_, v___x_5084_);
return v___x_5085_;
}
v___jp_5086_:
{
uint32_t v___x_5088_; uint32_t v___x_5089_; 
v___x_5088_ = 8388608;
v___x_5089_ = lean_uint32_lor(v___y_5087_, v___x_5088_);
return v___x_5089_;
}
v___jp_5090_:
{
uint32_t v___x_5092_; uint32_t v___x_5093_; 
v___x_5092_ = 8388608;
v___x_5093_ = lean_uint32_lor(v___y_5091_, v___x_5092_);
return v___x_5093_;
}
v___jp_5094_:
{
uint32_t v___x_5096_; uint32_t v___x_5097_; 
v___x_5096_ = 8388608;
v___x_5097_ = lean_uint32_lor(v___y_5095_, v___x_5096_);
return v___x_5097_;
}
v___jp_5098_:
{
uint32_t v___x_5100_; uint32_t v___x_5101_; 
v___x_5100_ = 8388608;
v___x_5101_ = lean_uint32_lor(v___y_5099_, v___x_5100_);
return v___x_5101_;
}
v___jp_5102_:
{
uint32_t v___x_5104_; uint32_t v___x_5105_; 
v___x_5104_ = 8388608;
v___x_5105_ = lean_uint32_lor(v___y_5103_, v___x_5104_);
return v___x_5105_;
}
v___jp_5106_:
{
uint32_t v___x_5109_; uint32_t v___x_5110_; uint32_t v___x_5111_; 
v___x_5109_ = 8388607;
v___x_5110_ = lean_uint32_land(v___y_5107_, v___x_5109_);
v___x_5111_ = lean_uint32_lor(v___y_5108_, v___x_5110_);
return v___x_5111_;
}
v___jp_5112_:
{
uint8_t v___x_5116_; 
v___x_5116_ = lean_uint64_dec_eq(v___y_5115_, v___y_5113_);
if (v___x_5116_ == 0)
{
uint64_t v___x_5117_; uint8_t v___x_5118_; 
v___x_5117_ = 8388608ULL;
v___x_5118_ = lean_uint64_dec_eq(v___y_5115_, v___x_5117_);
if (v___x_5118_ == 0)
{
uint32_t v___x_5119_; uint8_t v___x_5120_; 
v___x_5119_ = lean_uint64_to_uint32(v___y_5115_);
v___x_5120_ = lean_unbox(v___y_5114_);
lean_dec(v___y_5114_);
if (v___x_5120_ == 0)
{
uint32_t v___x_5121_; 
v___x_5121_ = 0;
v___y_5107_ = v___x_5119_;
v___y_5108_ = v___x_5121_;
goto v___jp_5106_;
}
else
{
uint32_t v___x_5122_; 
v___x_5122_ = 2147483648;
v___y_5107_ = v___x_5119_;
v___y_5108_ = v___x_5122_;
goto v___jp_5106_;
}
}
else
{
uint8_t v___x_5123_; 
v___x_5123_ = lean_unbox(v___y_5114_);
lean_dec(v___y_5114_);
if (v___x_5123_ == 0)
{
uint32_t v___x_5124_; 
v___x_5124_ = 0;
v___y_5075_ = v___x_5124_;
goto v___jp_5074_;
}
else
{
uint32_t v___x_5125_; 
v___x_5125_ = 2147483648;
v___y_5075_ = v___x_5125_;
goto v___jp_5074_;
}
}
}
else
{
uint8_t v___x_5126_; 
v___x_5126_ = lean_unbox(v___y_5114_);
lean_dec(v___y_5114_);
if (v___x_5126_ == 0)
{
uint32_t v___x_5127_; 
v___x_5127_ = 0;
return v___x_5127_;
}
else
{
uint32_t v___x_5128_; 
v___x_5128_ = 2147483648;
return v___x_5128_;
}
}
}
v___jp_5129_:
{
uint32_t v___x_5135_; uint32_t v___x_5136_; uint32_t v___x_5137_; uint32_t v___x_5138_; uint32_t v___x_5139_; uint32_t v___x_5140_; 
v___x_5135_ = lean_uint32_land(v___y_5132_, v___y_5131_);
v___x_5136_ = lean_uint32_shift_left(v___x_5135_, v___y_5133_);
v___x_5137_ = lean_uint32_lor(v___y_5134_, v___x_5136_);
v___x_5138_ = 8388607;
v___x_5139_ = lean_uint32_land(v___y_5130_, v___x_5138_);
v___x_5140_ = lean_uint32_lor(v___x_5137_, v___x_5139_);
return v___x_5140_;
}
v___jp_5141_:
{
uint8_t v___x_5147_; 
v___x_5147_ = lean_unbox(v___y_5144_);
lean_dec(v___y_5144_);
if (v___x_5147_ == 0)
{
uint32_t v___x_5148_; 
v___x_5148_ = 0;
v___y_5130_ = v___y_5146_;
v___y_5131_ = v___y_5143_;
v___y_5132_ = v___y_5142_;
v___y_5133_ = v___y_5145_;
v___y_5134_ = v___x_5148_;
goto v___jp_5129_;
}
else
{
uint32_t v___x_5149_; 
v___x_5149_ = 2147483648;
v___y_5130_ = v___y_5146_;
v___y_5131_ = v___y_5143_;
v___y_5132_ = v___y_5142_;
v___y_5133_ = v___y_5145_;
v___y_5134_ = v___x_5149_;
goto v___jp_5129_;
}
}
v___jp_5150_:
{
uint64_t v___x_5157_; uint64_t v_encodedExponent_5158_; uint32_t v___x_5159_; uint64_t v___x_5160_; uint8_t v___x_5161_; 
v___x_5157_ = 171ULL;
v_encodedExponent_5158_ = lean_uint64_sub(v___y_5151_, v___x_5157_);
v___x_5159_ = lean_uint64_to_uint32(v_encodedExponent_5158_);
v___x_5160_ = 8388608ULL;
v___x_5161_ = lean_uint64_dec_lt(v___y_5156_, v___x_5160_);
if (v___x_5161_ == 0)
{
uint64_t v___x_5162_; uint32_t v___x_5163_; 
v___x_5162_ = lean_uint64_sub(v___y_5156_, v___x_5160_);
v___x_5163_ = lean_uint64_to_uint32(v___x_5162_);
v___y_5142_ = v___x_5159_;
v___y_5143_ = v___y_5152_;
v___y_5144_ = v___y_5154_;
v___y_5145_ = v___y_5155_;
v___y_5146_ = v___x_5163_;
goto v___jp_5141_;
}
else
{
uint32_t v___x_5164_; 
v___x_5164_ = lean_uint64_to_uint32(v___y_5153_);
v___y_5142_ = v___x_5159_;
v___y_5143_ = v___y_5152_;
v___y_5144_ = v___y_5154_;
v___y_5145_ = v___y_5155_;
v___y_5146_ = v___x_5164_;
goto v___jp_5141_;
}
}
v___jp_5165_:
{
uint64_t v___x_5173_; uint8_t v___x_5174_; 
v___x_5173_ = 425ULL;
v___x_5174_ = lean_uint64_dec_lt(v___x_5173_, v___y_5172_);
if (v___x_5174_ == 0)
{
if (v___y_5170_ == 0)
{
v___y_5151_ = v___y_5172_;
v___y_5152_ = v___y_5166_;
v___y_5153_ = v___y_5167_;
v___y_5154_ = v___y_5168_;
v___y_5155_ = v___y_5171_;
v___y_5156_ = v___y_5169_;
goto v___jp_5150_;
}
else
{
uint64_t v___x_5175_; 
v___x_5175_ = 8388608ULL;
v___y_5151_ = v___y_5172_;
v___y_5152_ = v___y_5166_;
v___y_5153_ = v___y_5167_;
v___y_5154_ = v___y_5168_;
v___y_5155_ = v___y_5171_;
v___y_5156_ = v___x_5175_;
goto v___jp_5150_;
}
}
else
{
uint8_t v___x_5176_; 
v___x_5176_ = lean_unbox(v___y_5168_);
lean_dec(v___y_5168_);
if (v___x_5176_ == 0)
{
uint32_t v___x_5177_; 
v___x_5177_ = 2139095040;
return v___x_5177_;
}
else
{
uint32_t v___x_5178_; 
v___x_5178_ = 4286578688;
return v___x_5178_;
}
}
}
v___jp_5179_:
{
uint64_t v___x_5187_; uint8_t v_carry_5188_; 
v___x_5187_ = 16777216ULL;
v_carry_5188_ = lean_uint64_dec_eq(v___y_5186_, v___x_5187_);
if (v_carry_5188_ == 0)
{
v___y_5166_ = v___y_5180_;
v___y_5167_ = v___y_5181_;
v___y_5168_ = v___y_5184_;
v___y_5169_ = v___y_5186_;
v___y_5170_ = v_carry_5188_;
v___y_5171_ = v___y_5185_;
v___y_5172_ = v___y_5183_;
goto v___jp_5165_;
}
else
{
uint64_t v___x_5189_; 
v___x_5189_ = lean_uint64_add(v___y_5183_, v___y_5182_);
v___y_5166_ = v___y_5180_;
v___y_5167_ = v___y_5181_;
v___y_5168_ = v___y_5184_;
v___y_5169_ = v___y_5186_;
v___y_5170_ = v_carry_5188_;
v___y_5171_ = v___y_5185_;
v___y_5172_ = v___x_5189_;
goto v___jp_5165_;
}
}
v___jp_5190_:
{
uint64_t v_position_5200_; uint64_t v___x_5201_; uint8_t v___x_5202_; 
v_position_5200_ = lean_uint64_add(v___y_5199_, v___y_5196_);
v___x_5201_ = 172ULL;
v___x_5202_ = lean_uint64_dec_lt(v_position_5200_, v___x_5201_);
if (v___x_5202_ == 0)
{
uint64_t v___x_5203_; uint8_t v___x_5204_; 
v___x_5203_ = 23ULL;
v___x_5204_ = lean_uint64_dec_lt(v___y_5199_, v___x_5203_);
if (v___x_5204_ == 0)
{
uint64_t v___x_5205_; uint8_t v___x_5206_; 
v___x_5205_ = lean_uint64_sub(v___y_5199_, v___x_5203_);
v___x_5206_ = lean_uint64_dec_eq(v___x_5205_, v___y_5192_);
if (v___x_5206_ == 0)
{
uint64_t v___x_5207_; uint8_t v___x_5208_; 
v___x_5207_ = 64ULL;
v___x_5208_ = lean_uint64_dec_lt(v___x_5205_, v___x_5207_);
if (v___x_5208_ == 0)
{
uint8_t v___x_5209_; 
v___x_5209_ = lean_uint64_dec_eq(v___x_5205_, v___x_5207_);
if (v___x_5209_ == 0)
{
lean_dec(v___y_5194_);
v___y_5180_ = v___y_5191_;
v___y_5181_ = v___y_5192_;
v___y_5182_ = v___y_5195_;
v___y_5183_ = v_position_5200_;
v___y_5184_ = v___y_5197_;
v___y_5185_ = v___y_5198_;
v___y_5186_ = v___y_5192_;
goto v___jp_5179_;
}
else
{
uint64_t v___x_5210_; uint64_t v___x_5211_; uint8_t v___x_5212_; 
v___x_5210_ = 9223372036854775808ULL;
v___x_5211_ = lean_unbox_uint64(v___y_5194_);
lean_dec(v___y_5194_);
v___x_5212_ = lean_uint64_dec_lt(v___x_5210_, v___x_5211_);
if (v___x_5212_ == 0)
{
v___y_5180_ = v___y_5191_;
v___y_5181_ = v___y_5192_;
v___y_5182_ = v___y_5195_;
v___y_5183_ = v_position_5200_;
v___y_5184_ = v___y_5197_;
v___y_5185_ = v___y_5198_;
v___y_5186_ = v___y_5192_;
goto v___jp_5179_;
}
else
{
v___y_5180_ = v___y_5191_;
v___y_5181_ = v___y_5192_;
v___y_5182_ = v___y_5195_;
v___y_5183_ = v_position_5200_;
v___y_5184_ = v___y_5197_;
v___y_5185_ = v___y_5198_;
v___y_5186_ = v___y_5195_;
goto v___jp_5179_;
}
}
}
else
{
uint64_t v___x_5213_; uint64_t v_quotient_5214_; uint64_t v___x_5215_; uint64_t v___x_5216_; uint64_t v___x_5217_; uint64_t v_remainder_5218_; uint64_t v___x_5219_; uint64_t v_half_5220_; uint8_t v___x_5221_; 
v___x_5213_ = lean_unbox_uint64(v___y_5194_);
v_quotient_5214_ = lean_uint64_shift_right(v___x_5213_, v___x_5205_);
v___x_5215_ = lean_uint64_shift_left(v___y_5195_, v___x_5205_);
v___x_5216_ = lean_uint64_sub(v___x_5215_, v___y_5195_);
v___x_5217_ = lean_unbox_uint64(v___y_5194_);
lean_dec(v___y_5194_);
v_remainder_5218_ = lean_uint64_land(v___x_5217_, v___x_5216_);
v___x_5219_ = lean_uint64_sub(v___x_5205_, v___y_5195_);
v_half_5220_ = lean_uint64_shift_left(v___y_5195_, v___x_5219_);
v___x_5221_ = lean_uint64_dec_lt(v_remainder_5218_, v_half_5220_);
if (v___x_5221_ == 0)
{
uint8_t v___x_5222_; 
v___x_5222_ = lean_uint64_dec_lt(v_half_5220_, v_remainder_5218_);
if (v___x_5222_ == 0)
{
uint64_t v___x_5223_; uint8_t v___x_5224_; 
v___x_5223_ = lean_uint64_land(v_quotient_5214_, v___y_5195_);
v___x_5224_ = lean_uint64_dec_eq(v___x_5223_, v___y_5192_);
if (v___x_5224_ == 0)
{
uint64_t v___x_5225_; 
v___x_5225_ = lean_uint64_add(v_quotient_5214_, v___y_5195_);
v___y_5180_ = v___y_5191_;
v___y_5181_ = v___y_5192_;
v___y_5182_ = v___y_5195_;
v___y_5183_ = v_position_5200_;
v___y_5184_ = v___y_5197_;
v___y_5185_ = v___y_5198_;
v___y_5186_ = v___x_5225_;
goto v___jp_5179_;
}
else
{
v___y_5180_ = v___y_5191_;
v___y_5181_ = v___y_5192_;
v___y_5182_ = v___y_5195_;
v___y_5183_ = v_position_5200_;
v___y_5184_ = v___y_5197_;
v___y_5185_ = v___y_5198_;
v___y_5186_ = v_quotient_5214_;
goto v___jp_5179_;
}
}
else
{
uint64_t v___x_5226_; 
v___x_5226_ = lean_uint64_add(v_quotient_5214_, v___y_5195_);
v___y_5180_ = v___y_5191_;
v___y_5181_ = v___y_5192_;
v___y_5182_ = v___y_5195_;
v___y_5183_ = v_position_5200_;
v___y_5184_ = v___y_5197_;
v___y_5185_ = v___y_5198_;
v___y_5186_ = v___x_5226_;
goto v___jp_5179_;
}
}
else
{
v___y_5180_ = v___y_5191_;
v___y_5181_ = v___y_5192_;
v___y_5182_ = v___y_5195_;
v___y_5183_ = v_position_5200_;
v___y_5184_ = v___y_5197_;
v___y_5185_ = v___y_5198_;
v___y_5186_ = v_quotient_5214_;
goto v___jp_5179_;
}
}
}
else
{
uint64_t v___x_5227_; 
v___x_5227_ = lean_unbox_uint64(v___y_5194_);
lean_dec(v___y_5194_);
v___y_5180_ = v___y_5191_;
v___y_5181_ = v___y_5192_;
v___y_5182_ = v___y_5195_;
v___y_5183_ = v_position_5200_;
v___y_5184_ = v___y_5197_;
v___y_5185_ = v___y_5198_;
v___y_5186_ = v___x_5227_;
goto v___jp_5179_;
}
}
else
{
uint64_t v___x_5228_; uint64_t v___x_5229_; uint64_t v___x_5230_; 
v___x_5228_ = lean_uint64_sub(v___x_5203_, v___y_5199_);
v___x_5229_ = lean_unbox_uint64(v___y_5194_);
lean_dec(v___y_5194_);
v___x_5230_ = lean_uint64_shift_left(v___x_5229_, v___x_5228_);
v___y_5180_ = v___y_5191_;
v___y_5181_ = v___y_5192_;
v___y_5182_ = v___y_5195_;
v___y_5183_ = v_position_5200_;
v___y_5184_ = v___y_5197_;
v___y_5185_ = v___y_5198_;
v___y_5186_ = v___x_5230_;
goto v___jp_5179_;
}
}
else
{
uint8_t v___x_5231_; 
v___x_5231_ = lean_uint64_dec_lt(v___y_5196_, v___y_5193_);
if (v___x_5231_ == 0)
{
uint64_t v___x_5232_; uint64_t v___x_5233_; uint64_t v___x_5234_; 
v___x_5232_ = lean_uint64_sub(v___y_5196_, v___y_5193_);
v___x_5233_ = lean_unbox_uint64(v___y_5194_);
lean_dec(v___y_5194_);
v___x_5234_ = lean_uint64_shift_left(v___x_5233_, v___x_5232_);
v___y_5113_ = v___y_5192_;
v___y_5114_ = v___y_5197_;
v___y_5115_ = v___x_5234_;
goto v___jp_5112_;
}
else
{
uint64_t v___x_5235_; uint8_t v___x_5236_; 
v___x_5235_ = lean_uint64_sub(v___y_5193_, v___y_5196_);
v___x_5236_ = lean_uint64_dec_eq(v___x_5235_, v___y_5192_);
if (v___x_5236_ == 0)
{
uint64_t v___x_5237_; uint8_t v___x_5238_; 
v___x_5237_ = 64ULL;
v___x_5238_ = lean_uint64_dec_lt(v___x_5235_, v___x_5237_);
if (v___x_5238_ == 0)
{
uint8_t v___x_5239_; 
v___x_5239_ = lean_uint64_dec_eq(v___x_5235_, v___x_5237_);
if (v___x_5239_ == 0)
{
lean_dec(v___y_5194_);
v___y_5113_ = v___y_5192_;
v___y_5114_ = v___y_5197_;
v___y_5115_ = v___y_5192_;
goto v___jp_5112_;
}
else
{
uint64_t v___x_5240_; uint64_t v___x_5241_; uint8_t v___x_5242_; 
v___x_5240_ = 9223372036854775808ULL;
v___x_5241_ = lean_unbox_uint64(v___y_5194_);
lean_dec(v___y_5194_);
v___x_5242_ = lean_uint64_dec_lt(v___x_5240_, v___x_5241_);
if (v___x_5242_ == 0)
{
v___y_5113_ = v___y_5192_;
v___y_5114_ = v___y_5197_;
v___y_5115_ = v___y_5192_;
goto v___jp_5112_;
}
else
{
v___y_5113_ = v___y_5192_;
v___y_5114_ = v___y_5197_;
v___y_5115_ = v___y_5195_;
goto v___jp_5112_;
}
}
}
else
{
uint64_t v___x_5243_; uint64_t v_quotient_5244_; uint64_t v___x_5245_; uint64_t v___x_5246_; uint64_t v___x_5247_; uint64_t v_remainder_5248_; uint64_t v___x_5249_; uint64_t v_half_5250_; uint8_t v___x_5251_; 
v___x_5243_ = lean_unbox_uint64(v___y_5194_);
v_quotient_5244_ = lean_uint64_shift_right(v___x_5243_, v___x_5235_);
v___x_5245_ = lean_uint64_shift_left(v___y_5195_, v___x_5235_);
v___x_5246_ = lean_uint64_sub(v___x_5245_, v___y_5195_);
v___x_5247_ = lean_unbox_uint64(v___y_5194_);
lean_dec(v___y_5194_);
v_remainder_5248_ = lean_uint64_land(v___x_5247_, v___x_5246_);
v___x_5249_ = lean_uint64_sub(v___x_5235_, v___y_5195_);
v_half_5250_ = lean_uint64_shift_left(v___y_5195_, v___x_5249_);
v___x_5251_ = lean_uint64_dec_lt(v_remainder_5248_, v_half_5250_);
if (v___x_5251_ == 0)
{
uint8_t v___x_5252_; 
v___x_5252_ = lean_uint64_dec_lt(v_half_5250_, v_remainder_5248_);
if (v___x_5252_ == 0)
{
uint64_t v___x_5253_; uint8_t v___x_5254_; 
v___x_5253_ = lean_uint64_land(v_quotient_5244_, v___y_5195_);
v___x_5254_ = lean_uint64_dec_eq(v___x_5253_, v___y_5192_);
if (v___x_5254_ == 0)
{
uint64_t v___x_5255_; 
v___x_5255_ = lean_uint64_add(v_quotient_5244_, v___y_5195_);
v___y_5113_ = v___y_5192_;
v___y_5114_ = v___y_5197_;
v___y_5115_ = v___x_5255_;
goto v___jp_5112_;
}
else
{
v___y_5113_ = v___y_5192_;
v___y_5114_ = v___y_5197_;
v___y_5115_ = v_quotient_5244_;
goto v___jp_5112_;
}
}
else
{
uint64_t v___x_5256_; 
v___x_5256_ = lean_uint64_add(v_quotient_5244_, v___y_5195_);
v___y_5113_ = v___y_5192_;
v___y_5114_ = v___y_5197_;
v___y_5115_ = v___x_5256_;
goto v___jp_5112_;
}
}
else
{
v___y_5113_ = v___y_5192_;
v___y_5114_ = v___y_5197_;
v___y_5115_ = v_quotient_5244_;
goto v___jp_5112_;
}
}
}
else
{
uint64_t v___x_5257_; 
v___x_5257_ = lean_unbox_uint64(v___y_5194_);
lean_dec(v___y_5194_);
v___y_5113_ = v___y_5192_;
v___y_5114_ = v___y_5197_;
v___y_5115_ = v___x_5257_;
goto v___jp_5112_;
}
}
}
}
v___jp_5258_:
{
uint64_t v___x_5269_; uint8_t v___x_5270_; 
v___x_5269_ = lean_uint64_shift_right(v___y_5260_, v___y_5264_);
v___x_5270_ = lean_uint64_dec_eq(v___x_5269_, v___y_5261_);
if (v___x_5270_ == 0)
{
uint64_t v___x_5271_; 
v___x_5271_ = lean_uint64_add(v___y_5268_, v___y_5264_);
v___y_5191_ = v___y_5259_;
v___y_5192_ = v___y_5261_;
v___y_5193_ = v___y_5263_;
v___y_5194_ = v___y_5262_;
v___y_5195_ = v___y_5264_;
v___y_5196_ = v___y_5265_;
v___y_5197_ = v___y_5266_;
v___y_5198_ = v___y_5267_;
v___y_5199_ = v___x_5271_;
goto v___jp_5190_;
}
else
{
v___y_5191_ = v___y_5259_;
v___y_5192_ = v___y_5261_;
v___y_5193_ = v___y_5263_;
v___y_5194_ = v___y_5262_;
v___y_5195_ = v___y_5264_;
v___y_5196_ = v___y_5265_;
v___y_5197_ = v___y_5266_;
v___y_5198_ = v___y_5267_;
v___y_5199_ = v___y_5268_;
goto v___jp_5190_;
}
}
v___jp_5272_:
{
uint64_t v___x_5285_; uint8_t v___x_5286_; 
v___x_5285_ = lean_uint64_shift_right(v___y_5275_, v___y_5281_);
v___x_5286_ = lean_uint64_dec_eq(v___x_5285_, v___y_5274_);
if (v___x_5286_ == 0)
{
uint64_t v___x_5287_; 
v___x_5287_ = lean_uint64_add(v___y_5282_, v___y_5281_);
v___y_5259_ = v___y_5273_;
v___y_5260_ = v___y_5284_;
v___y_5261_ = v___y_5274_;
v___y_5262_ = v___y_5278_;
v___y_5263_ = v___y_5277_;
v___y_5264_ = v___y_5276_;
v___y_5265_ = v___y_5279_;
v___y_5266_ = v___y_5280_;
v___y_5267_ = v___y_5283_;
v___y_5268_ = v___x_5287_;
goto v___jp_5258_;
}
else
{
v___y_5259_ = v___y_5273_;
v___y_5260_ = v___y_5284_;
v___y_5261_ = v___y_5274_;
v___y_5262_ = v___y_5278_;
v___y_5263_ = v___y_5277_;
v___y_5264_ = v___y_5276_;
v___y_5265_ = v___y_5279_;
v___y_5266_ = v___y_5280_;
v___y_5267_ = v___y_5283_;
v___y_5268_ = v___y_5282_;
goto v___jp_5258_;
}
}
v___jp_5288_:
{
uint64_t v___x_5299_; uint64_t v___x_5300_; uint8_t v___x_5301_; 
v___x_5299_ = 2ULL;
v___x_5300_ = lean_uint64_shift_right(v___y_5294_, v___x_5299_);
v___x_5301_ = lean_uint64_dec_eq(v___x_5300_, v___y_5290_);
if (v___x_5301_ == 0)
{
v___y_5273_ = v___y_5289_;
v___y_5274_ = v___y_5290_;
v___y_5275_ = v___y_5294_;
v___y_5276_ = v___y_5293_;
v___y_5277_ = v___y_5292_;
v___y_5278_ = v___y_5291_;
v___y_5279_ = v___y_5295_;
v___y_5280_ = v___y_5296_;
v___y_5281_ = v___x_5299_;
v___y_5282_ = v___y_5298_;
v___y_5283_ = v___y_5297_;
v___y_5284_ = v___x_5300_;
goto v___jp_5272_;
}
else
{
v___y_5273_ = v___y_5289_;
v___y_5274_ = v___y_5290_;
v___y_5275_ = v___y_5294_;
v___y_5276_ = v___y_5293_;
v___y_5277_ = v___y_5292_;
v___y_5278_ = v___y_5291_;
v___y_5279_ = v___y_5295_;
v___y_5280_ = v___y_5296_;
v___y_5281_ = v___x_5299_;
v___y_5282_ = v___y_5298_;
v___y_5283_ = v___y_5297_;
v___y_5284_ = v___y_5294_;
goto v___jp_5272_;
}
}
v___jp_5302_:
{
uint64_t v___x_5315_; uint8_t v___x_5316_; 
v___x_5315_ = lean_uint64_shift_right(v___y_5304_, v___y_5313_);
v___x_5316_ = lean_uint64_dec_eq(v___x_5315_, v___y_5305_);
if (v___x_5316_ == 0)
{
uint64_t v___x_5317_; 
v___x_5317_ = lean_uint64_add(v___y_5312_, v___y_5313_);
v___y_5289_ = v___y_5303_;
v___y_5290_ = v___y_5305_;
v___y_5291_ = v___y_5308_;
v___y_5292_ = v___y_5307_;
v___y_5293_ = v___y_5306_;
v___y_5294_ = v___y_5314_;
v___y_5295_ = v___y_5309_;
v___y_5296_ = v___y_5310_;
v___y_5297_ = v___y_5311_;
v___y_5298_ = v___x_5317_;
goto v___jp_5288_;
}
else
{
v___y_5289_ = v___y_5303_;
v___y_5290_ = v___y_5305_;
v___y_5291_ = v___y_5308_;
v___y_5292_ = v___y_5307_;
v___y_5293_ = v___y_5306_;
v___y_5294_ = v___y_5314_;
v___y_5295_ = v___y_5309_;
v___y_5296_ = v___y_5310_;
v___y_5297_ = v___y_5311_;
v___y_5298_ = v___y_5312_;
goto v___jp_5288_;
}
}
v___jp_5318_:
{
uint64_t v___x_5329_; uint64_t v___x_5330_; uint8_t v___x_5331_; 
v___x_5329_ = 4ULL;
v___x_5330_ = lean_uint64_shift_right(v___y_5321_, v___x_5329_);
v___x_5331_ = lean_uint64_dec_eq(v___x_5330_, v___y_5320_);
if (v___x_5331_ == 0)
{
v___y_5303_ = v___y_5319_;
v___y_5304_ = v___y_5321_;
v___y_5305_ = v___y_5320_;
v___y_5306_ = v___y_5324_;
v___y_5307_ = v___y_5323_;
v___y_5308_ = v___y_5322_;
v___y_5309_ = v___y_5325_;
v___y_5310_ = v___y_5326_;
v___y_5311_ = v___y_5327_;
v___y_5312_ = v___y_5328_;
v___y_5313_ = v___x_5329_;
v___y_5314_ = v___x_5330_;
goto v___jp_5302_;
}
else
{
v___y_5303_ = v___y_5319_;
v___y_5304_ = v___y_5321_;
v___y_5305_ = v___y_5320_;
v___y_5306_ = v___y_5324_;
v___y_5307_ = v___y_5323_;
v___y_5308_ = v___y_5322_;
v___y_5309_ = v___y_5325_;
v___y_5310_ = v___y_5326_;
v___y_5311_ = v___y_5327_;
v___y_5312_ = v___y_5328_;
v___y_5313_ = v___x_5329_;
v___y_5314_ = v___y_5321_;
goto v___jp_5302_;
}
}
v___jp_5332_:
{
uint64_t v___x_5345_; uint8_t v___x_5346_; 
v___x_5345_ = lean_uint64_shift_right(v___y_5333_, v___y_5340_);
v___x_5346_ = lean_uint64_dec_eq(v___x_5345_, v___y_5336_);
if (v___x_5346_ == 0)
{
uint64_t v___x_5347_; 
v___x_5347_ = lean_uint64_add(v___y_5334_, v___y_5340_);
v___y_5319_ = v___y_5335_;
v___y_5320_ = v___y_5336_;
v___y_5321_ = v___y_5344_;
v___y_5322_ = v___y_5339_;
v___y_5323_ = v___y_5338_;
v___y_5324_ = v___y_5337_;
v___y_5325_ = v___y_5341_;
v___y_5326_ = v___y_5342_;
v___y_5327_ = v___y_5343_;
v___y_5328_ = v___x_5347_;
goto v___jp_5318_;
}
else
{
v___y_5319_ = v___y_5335_;
v___y_5320_ = v___y_5336_;
v___y_5321_ = v___y_5344_;
v___y_5322_ = v___y_5339_;
v___y_5323_ = v___y_5338_;
v___y_5324_ = v___y_5337_;
v___y_5325_ = v___y_5341_;
v___y_5326_ = v___y_5342_;
v___y_5327_ = v___y_5343_;
v___y_5328_ = v___y_5334_;
goto v___jp_5318_;
}
}
v___jp_5348_:
{
uint64_t v___x_5359_; uint64_t v___x_5360_; uint8_t v___x_5361_; 
v___x_5359_ = 8ULL;
v___x_5360_ = lean_uint64_shift_right(v___y_5349_, v___x_5359_);
v___x_5361_ = lean_uint64_dec_eq(v___x_5360_, v___y_5351_);
if (v___x_5361_ == 0)
{
v___y_5333_ = v___y_5349_;
v___y_5334_ = v___y_5358_;
v___y_5335_ = v___y_5350_;
v___y_5336_ = v___y_5351_;
v___y_5337_ = v___y_5354_;
v___y_5338_ = v___y_5353_;
v___y_5339_ = v___y_5352_;
v___y_5340_ = v___x_5359_;
v___y_5341_ = v___y_5355_;
v___y_5342_ = v___y_5356_;
v___y_5343_ = v___y_5357_;
v___y_5344_ = v___x_5360_;
goto v___jp_5332_;
}
else
{
v___y_5333_ = v___y_5349_;
v___y_5334_ = v___y_5358_;
v___y_5335_ = v___y_5350_;
v___y_5336_ = v___y_5351_;
v___y_5337_ = v___y_5354_;
v___y_5338_ = v___y_5353_;
v___y_5339_ = v___y_5352_;
v___y_5340_ = v___x_5359_;
v___y_5341_ = v___y_5355_;
v___y_5342_ = v___y_5356_;
v___y_5343_ = v___y_5357_;
v___y_5344_ = v___y_5349_;
goto v___jp_5332_;
}
}
v___jp_5362_:
{
uint64_t v___x_5375_; uint8_t v___x_5376_; 
v___x_5375_ = lean_uint64_shift_right(v___y_5370_, v___y_5373_);
v___x_5376_ = lean_uint64_dec_eq(v___x_5375_, v___y_5364_);
if (v___x_5376_ == 0)
{
uint64_t v___x_5377_; 
v___x_5377_ = lean_uint64_add(v___y_5365_, v___y_5373_);
v___y_5349_ = v___y_5374_;
v___y_5350_ = v___y_5363_;
v___y_5351_ = v___y_5364_;
v___y_5352_ = v___y_5368_;
v___y_5353_ = v___y_5367_;
v___y_5354_ = v___y_5366_;
v___y_5355_ = v___y_5369_;
v___y_5356_ = v___y_5371_;
v___y_5357_ = v___y_5372_;
v___y_5358_ = v___x_5377_;
goto v___jp_5348_;
}
else
{
v___y_5349_ = v___y_5374_;
v___y_5350_ = v___y_5363_;
v___y_5351_ = v___y_5364_;
v___y_5352_ = v___y_5368_;
v___y_5353_ = v___y_5367_;
v___y_5354_ = v___y_5366_;
v___y_5355_ = v___y_5369_;
v___y_5356_ = v___y_5371_;
v___y_5357_ = v___y_5372_;
v___y_5358_ = v___y_5365_;
goto v___jp_5348_;
}
}
v___jp_5378_:
{
uint64_t v___x_5389_; uint64_t v___x_5390_; uint8_t v___x_5391_; 
v___x_5389_ = 16ULL;
v___x_5390_ = lean_uint64_shift_right(v___y_5386_, v___x_5389_);
v___x_5391_ = lean_uint64_dec_eq(v___x_5390_, v___y_5380_);
if (v___x_5391_ == 0)
{
v___y_5363_ = v___y_5379_;
v___y_5364_ = v___y_5380_;
v___y_5365_ = v___y_5388_;
v___y_5366_ = v___y_5383_;
v___y_5367_ = v___y_5382_;
v___y_5368_ = v___y_5381_;
v___y_5369_ = v___y_5384_;
v___y_5370_ = v___y_5386_;
v___y_5371_ = v___y_5385_;
v___y_5372_ = v___y_5387_;
v___y_5373_ = v___x_5389_;
v___y_5374_ = v___x_5390_;
goto v___jp_5362_;
}
else
{
v___y_5363_ = v___y_5379_;
v___y_5364_ = v___y_5380_;
v___y_5365_ = v___y_5388_;
v___y_5366_ = v___y_5383_;
v___y_5367_ = v___y_5382_;
v___y_5368_ = v___y_5381_;
v___y_5369_ = v___y_5384_;
v___y_5370_ = v___y_5386_;
v___y_5371_ = v___y_5385_;
v___y_5372_ = v___y_5387_;
v___y_5373_ = v___x_5389_;
v___y_5374_ = v___y_5386_;
goto v___jp_5362_;
}
}
v___jp_5392_:
{
uint64_t v___x_5403_; uint64_t v___x_5404_; uint8_t v___x_5405_; 
v___x_5403_ = lean_unbox_uint64(v___y_5397_);
v___x_5404_ = lean_uint64_shift_right(v___x_5403_, v___y_5400_);
v___x_5405_ = lean_uint64_dec_eq(v___x_5404_, v___y_5394_);
if (v___x_5405_ == 0)
{
v___y_5379_ = v___y_5393_;
v___y_5380_ = v___y_5394_;
v___y_5381_ = v___y_5397_;
v___y_5382_ = v___y_5396_;
v___y_5383_ = v___y_5395_;
v___y_5384_ = v___y_5398_;
v___y_5385_ = v___y_5399_;
v___y_5386_ = v___y_5402_;
v___y_5387_ = v___y_5401_;
v___y_5388_ = v___y_5400_;
goto v___jp_5378_;
}
else
{
v___y_5379_ = v___y_5393_;
v___y_5380_ = v___y_5394_;
v___y_5381_ = v___y_5397_;
v___y_5382_ = v___y_5396_;
v___y_5383_ = v___y_5395_;
v___y_5384_ = v___y_5398_;
v___y_5385_ = v___y_5399_;
v___y_5386_ = v___y_5402_;
v___y_5387_ = v___y_5401_;
v___y_5388_ = v___y_5394_;
goto v___jp_5378_;
}
}
v___jp_5406_:
{
uint64_t v___x_5413_; uint64_t v___x_5414_; uint8_t v___x_5415_; 
v___x_5413_ = 0ULL;
v___x_5414_ = lean_unbox_uint64(v_snd_5412_);
v___x_5415_ = lean_uint64_dec_eq(v___x_5414_, v___x_5413_);
if (v___x_5415_ == 0)
{
uint64_t v___x_5416_; uint64_t v___x_5417_; uint64_t v___x_5418_; uint64_t v___x_5419_; uint64_t v___x_5420_; uint8_t v___x_5421_; 
v___x_5416_ = 149ULL;
v___x_5417_ = lean_uint64_add(v___y_5409_, v___x_5416_);
v___x_5418_ = 32ULL;
v___x_5419_ = lean_unbox_uint64(v_snd_5412_);
v___x_5420_ = lean_uint64_shift_right(v___x_5419_, v___x_5418_);
v___x_5421_ = lean_uint64_dec_eq(v___x_5420_, v___x_5413_);
if (v___x_5421_ == 0)
{
v___y_5393_ = v___y_5407_;
v___y_5394_ = v___x_5413_;
v___y_5395_ = v___y_5408_;
v___y_5396_ = v___x_5416_;
v___y_5397_ = v_snd_5412_;
v___y_5398_ = v___x_5417_;
v___y_5399_ = v_fst_5411_;
v___y_5400_ = v___x_5418_;
v___y_5401_ = v___y_5410_;
v___y_5402_ = v___x_5420_;
goto v___jp_5392_;
}
else
{
uint64_t v___x_5422_; 
v___x_5422_ = lean_unbox_uint64(v_snd_5412_);
v___y_5393_ = v___y_5407_;
v___y_5394_ = v___x_5413_;
v___y_5395_ = v___y_5408_;
v___y_5396_ = v___x_5416_;
v___y_5397_ = v_snd_5412_;
v___y_5398_ = v___x_5417_;
v___y_5399_ = v_fst_5411_;
v___y_5400_ = v___x_5418_;
v___y_5401_ = v___y_5410_;
v___y_5402_ = v___x_5422_;
goto v___jp_5392_;
}
}
else
{
uint8_t v___x_5423_; 
lean_dec(v_snd_5412_);
v___x_5423_ = lean_unbox(v_fst_5411_);
lean_dec(v_fst_5411_);
if (v___x_5423_ == 0)
{
uint32_t v___x_5424_; 
v___x_5424_ = 0;
return v___x_5424_;
}
else
{
uint32_t v___x_5425_; 
v___x_5425_ = 2147483648;
return v___x_5425_;
}
}
}
v___jp_5426_:
{
uint32_t v___x_5429_; uint32_t v___x_5430_; uint32_t v___x_5431_; 
v___x_5429_ = 8388607;
v___x_5430_ = lean_uint32_land(v___y_5427_, v___x_5429_);
v___x_5431_ = lean_uint32_lor(v___y_5428_, v___x_5430_);
return v___x_5431_;
}
v___jp_5432_:
{
uint8_t v___x_5436_; 
v___x_5436_ = lean_uint64_dec_eq(v___y_5435_, v___y_5433_);
if (v___x_5436_ == 0)
{
uint64_t v___x_5437_; uint8_t v___x_5438_; 
v___x_5437_ = 8388608ULL;
v___x_5438_ = lean_uint64_dec_eq(v___y_5435_, v___x_5437_);
if (v___x_5438_ == 0)
{
uint32_t v___x_5439_; uint8_t v___x_5440_; 
v___x_5439_ = lean_uint64_to_uint32(v___y_5435_);
v___x_5440_ = lean_unbox(v___y_5434_);
lean_dec(v___y_5434_);
if (v___x_5440_ == 0)
{
uint32_t v___x_5441_; 
v___x_5441_ = 0;
v___y_5427_ = v___x_5439_;
v___y_5428_ = v___x_5441_;
goto v___jp_5426_;
}
else
{
uint32_t v___x_5442_; 
v___x_5442_ = 2147483648;
v___y_5427_ = v___x_5439_;
v___y_5428_ = v___x_5442_;
goto v___jp_5426_;
}
}
else
{
uint8_t v___x_5443_; 
v___x_5443_ = lean_unbox(v___y_5434_);
lean_dec(v___y_5434_);
if (v___x_5443_ == 0)
{
uint32_t v___x_5444_; 
v___x_5444_ = 0;
v___y_5079_ = v___x_5444_;
goto v___jp_5078_;
}
else
{
uint32_t v___x_5445_; 
v___x_5445_ = 2147483648;
v___y_5079_ = v___x_5445_;
goto v___jp_5078_;
}
}
}
else
{
uint8_t v___x_5446_; 
v___x_5446_ = lean_unbox(v___y_5434_);
lean_dec(v___y_5434_);
if (v___x_5446_ == 0)
{
uint32_t v___x_5447_; 
v___x_5447_ = 0;
return v___x_5447_;
}
else
{
uint32_t v___x_5448_; 
v___x_5448_ = 2147483648;
return v___x_5448_;
}
}
}
v___jp_5449_:
{
uint32_t v___x_5455_; uint32_t v___x_5456_; uint32_t v___x_5457_; uint32_t v___x_5458_; uint32_t v___x_5459_; uint32_t v___x_5460_; 
v___x_5455_ = lean_uint32_land(v___y_5452_, v___y_5450_);
v___x_5456_ = lean_uint32_shift_left(v___x_5455_, v___y_5453_);
v___x_5457_ = lean_uint32_lor(v___y_5454_, v___x_5456_);
v___x_5458_ = 8388607;
v___x_5459_ = lean_uint32_land(v___y_5451_, v___x_5458_);
v___x_5460_ = lean_uint32_lor(v___x_5457_, v___x_5459_);
return v___x_5460_;
}
v___jp_5461_:
{
uint8_t v___x_5467_; 
v___x_5467_ = lean_unbox(v___y_5464_);
lean_dec(v___y_5464_);
if (v___x_5467_ == 0)
{
uint32_t v___x_5468_; 
v___x_5468_ = 0;
v___y_5450_ = v___y_5462_;
v___y_5451_ = v___y_5466_;
v___y_5452_ = v___y_5463_;
v___y_5453_ = v___y_5465_;
v___y_5454_ = v___x_5468_;
goto v___jp_5449_;
}
else
{
uint32_t v___x_5469_; 
v___x_5469_ = 2147483648;
v___y_5450_ = v___y_5462_;
v___y_5451_ = v___y_5466_;
v___y_5452_ = v___y_5463_;
v___y_5453_ = v___y_5465_;
v___y_5454_ = v___x_5469_;
goto v___jp_5449_;
}
}
v___jp_5470_:
{
uint64_t v___x_5477_; uint64_t v_encodedExponent_5478_; uint32_t v___x_5479_; uint64_t v___x_5480_; uint8_t v___x_5481_; 
v___x_5477_ = 171ULL;
v_encodedExponent_5478_ = lean_uint64_sub(v___y_5475_, v___x_5477_);
v___x_5479_ = lean_uint64_to_uint32(v_encodedExponent_5478_);
v___x_5480_ = 8388608ULL;
v___x_5481_ = lean_uint64_dec_lt(v___y_5476_, v___x_5480_);
if (v___x_5481_ == 0)
{
uint64_t v___x_5482_; uint32_t v___x_5483_; 
v___x_5482_ = lean_uint64_sub(v___y_5476_, v___x_5480_);
v___x_5483_ = lean_uint64_to_uint32(v___x_5482_);
v___y_5462_ = v___y_5472_;
v___y_5463_ = v___x_5479_;
v___y_5464_ = v___y_5473_;
v___y_5465_ = v___y_5474_;
v___y_5466_ = v___x_5483_;
goto v___jp_5461_;
}
else
{
uint32_t v___x_5484_; 
v___x_5484_ = lean_uint64_to_uint32(v___y_5471_);
v___y_5462_ = v___y_5472_;
v___y_5463_ = v___x_5479_;
v___y_5464_ = v___y_5473_;
v___y_5465_ = v___y_5474_;
v___y_5466_ = v___x_5484_;
goto v___jp_5461_;
}
}
v___jp_5485_:
{
uint64_t v___x_5493_; uint8_t v___x_5494_; 
v___x_5493_ = 425ULL;
v___x_5494_ = lean_uint64_dec_lt(v___x_5493_, v___y_5492_);
if (v___x_5494_ == 0)
{
if (v___y_5487_ == 0)
{
v___y_5471_ = v___y_5486_;
v___y_5472_ = v___y_5488_;
v___y_5473_ = v___y_5490_;
v___y_5474_ = v___y_5491_;
v___y_5475_ = v___y_5492_;
v___y_5476_ = v___y_5489_;
goto v___jp_5470_;
}
else
{
uint64_t v___x_5495_; 
v___x_5495_ = 8388608ULL;
v___y_5471_ = v___y_5486_;
v___y_5472_ = v___y_5488_;
v___y_5473_ = v___y_5490_;
v___y_5474_ = v___y_5491_;
v___y_5475_ = v___y_5492_;
v___y_5476_ = v___x_5495_;
goto v___jp_5470_;
}
}
else
{
uint8_t v___x_5496_; 
v___x_5496_ = lean_unbox(v___y_5490_);
lean_dec(v___y_5490_);
if (v___x_5496_ == 0)
{
uint32_t v___x_5497_; 
v___x_5497_ = 2139095040;
return v___x_5497_;
}
else
{
uint32_t v___x_5498_; 
v___x_5498_ = 4286578688;
return v___x_5498_;
}
}
}
v___jp_5499_:
{
uint64_t v___x_5507_; uint8_t v_carry_5508_; 
v___x_5507_ = 16777216ULL;
v_carry_5508_ = lean_uint64_dec_eq(v___y_5506_, v___x_5507_);
if (v_carry_5508_ == 0)
{
v___y_5486_ = v___y_5500_;
v___y_5487_ = v_carry_5508_;
v___y_5488_ = v___y_5501_;
v___y_5489_ = v___y_5506_;
v___y_5490_ = v___y_5503_;
v___y_5491_ = v___y_5504_;
v___y_5492_ = v___y_5505_;
goto v___jp_5485_;
}
else
{
uint64_t v___x_5509_; 
v___x_5509_ = lean_uint64_add(v___y_5505_, v___y_5502_);
v___y_5486_ = v___y_5500_;
v___y_5487_ = v_carry_5508_;
v___y_5488_ = v___y_5501_;
v___y_5489_ = v___y_5506_;
v___y_5490_ = v___y_5503_;
v___y_5491_ = v___y_5504_;
v___y_5492_ = v___x_5509_;
goto v___jp_5485_;
}
}
v___jp_5510_:
{
uint64_t v_position_5520_; uint64_t v___x_5521_; uint8_t v___x_5522_; 
v_position_5520_ = lean_uint64_add(v___y_5519_, v___y_5517_);
v___x_5521_ = 172ULL;
v___x_5522_ = lean_uint64_dec_lt(v_position_5520_, v___x_5521_);
if (v___x_5522_ == 0)
{
uint64_t v___x_5523_; uint8_t v___x_5524_; 
v___x_5523_ = 23ULL;
v___x_5524_ = lean_uint64_dec_lt(v___y_5519_, v___x_5523_);
if (v___x_5524_ == 0)
{
uint64_t v___x_5525_; uint8_t v___x_5526_; 
v___x_5525_ = lean_uint64_sub(v___y_5519_, v___x_5523_);
v___x_5526_ = lean_uint64_dec_eq(v___x_5525_, v___y_5512_);
if (v___x_5526_ == 0)
{
uint64_t v___x_5527_; uint8_t v___x_5528_; 
v___x_5527_ = 64ULL;
v___x_5528_ = lean_uint64_dec_lt(v___x_5525_, v___x_5527_);
if (v___x_5528_ == 0)
{
uint8_t v___x_5529_; 
v___x_5529_ = lean_uint64_dec_eq(v___x_5525_, v___x_5527_);
if (v___x_5529_ == 0)
{
lean_dec(v___y_5511_);
v___y_5500_ = v___y_5512_;
v___y_5501_ = v___y_5513_;
v___y_5502_ = v___y_5514_;
v___y_5503_ = v___y_5516_;
v___y_5504_ = v___y_5518_;
v___y_5505_ = v_position_5520_;
v___y_5506_ = v___y_5512_;
goto v___jp_5499_;
}
else
{
uint64_t v___x_5530_; uint64_t v___x_5531_; uint8_t v___x_5532_; 
v___x_5530_ = 9223372036854775808ULL;
v___x_5531_ = lean_unbox_uint64(v___y_5511_);
lean_dec(v___y_5511_);
v___x_5532_ = lean_uint64_dec_lt(v___x_5530_, v___x_5531_);
if (v___x_5532_ == 0)
{
v___y_5500_ = v___y_5512_;
v___y_5501_ = v___y_5513_;
v___y_5502_ = v___y_5514_;
v___y_5503_ = v___y_5516_;
v___y_5504_ = v___y_5518_;
v___y_5505_ = v_position_5520_;
v___y_5506_ = v___y_5512_;
goto v___jp_5499_;
}
else
{
v___y_5500_ = v___y_5512_;
v___y_5501_ = v___y_5513_;
v___y_5502_ = v___y_5514_;
v___y_5503_ = v___y_5516_;
v___y_5504_ = v___y_5518_;
v___y_5505_ = v_position_5520_;
v___y_5506_ = v___y_5514_;
goto v___jp_5499_;
}
}
}
else
{
uint64_t v___x_5533_; uint64_t v_quotient_5534_; uint64_t v___x_5535_; uint64_t v___x_5536_; uint64_t v___x_5537_; uint64_t v_remainder_5538_; uint64_t v___x_5539_; uint64_t v_half_5540_; uint8_t v___x_5541_; 
v___x_5533_ = lean_unbox_uint64(v___y_5511_);
v_quotient_5534_ = lean_uint64_shift_right(v___x_5533_, v___x_5525_);
v___x_5535_ = lean_uint64_shift_left(v___y_5514_, v___x_5525_);
v___x_5536_ = lean_uint64_sub(v___x_5535_, v___y_5514_);
v___x_5537_ = lean_unbox_uint64(v___y_5511_);
lean_dec(v___y_5511_);
v_remainder_5538_ = lean_uint64_land(v___x_5537_, v___x_5536_);
v___x_5539_ = lean_uint64_sub(v___x_5525_, v___y_5514_);
v_half_5540_ = lean_uint64_shift_left(v___y_5514_, v___x_5539_);
v___x_5541_ = lean_uint64_dec_lt(v_remainder_5538_, v_half_5540_);
if (v___x_5541_ == 0)
{
uint8_t v___x_5542_; 
v___x_5542_ = lean_uint64_dec_lt(v_half_5540_, v_remainder_5538_);
if (v___x_5542_ == 0)
{
uint64_t v___x_5543_; uint8_t v___x_5544_; 
v___x_5543_ = lean_uint64_land(v_quotient_5534_, v___y_5514_);
v___x_5544_ = lean_uint64_dec_eq(v___x_5543_, v___y_5512_);
if (v___x_5544_ == 0)
{
uint64_t v___x_5545_; 
v___x_5545_ = lean_uint64_add(v_quotient_5534_, v___y_5514_);
v___y_5500_ = v___y_5512_;
v___y_5501_ = v___y_5513_;
v___y_5502_ = v___y_5514_;
v___y_5503_ = v___y_5516_;
v___y_5504_ = v___y_5518_;
v___y_5505_ = v_position_5520_;
v___y_5506_ = v___x_5545_;
goto v___jp_5499_;
}
else
{
v___y_5500_ = v___y_5512_;
v___y_5501_ = v___y_5513_;
v___y_5502_ = v___y_5514_;
v___y_5503_ = v___y_5516_;
v___y_5504_ = v___y_5518_;
v___y_5505_ = v_position_5520_;
v___y_5506_ = v_quotient_5534_;
goto v___jp_5499_;
}
}
else
{
uint64_t v___x_5546_; 
v___x_5546_ = lean_uint64_add(v_quotient_5534_, v___y_5514_);
v___y_5500_ = v___y_5512_;
v___y_5501_ = v___y_5513_;
v___y_5502_ = v___y_5514_;
v___y_5503_ = v___y_5516_;
v___y_5504_ = v___y_5518_;
v___y_5505_ = v_position_5520_;
v___y_5506_ = v___x_5546_;
goto v___jp_5499_;
}
}
else
{
v___y_5500_ = v___y_5512_;
v___y_5501_ = v___y_5513_;
v___y_5502_ = v___y_5514_;
v___y_5503_ = v___y_5516_;
v___y_5504_ = v___y_5518_;
v___y_5505_ = v_position_5520_;
v___y_5506_ = v_quotient_5534_;
goto v___jp_5499_;
}
}
}
else
{
uint64_t v___x_5547_; 
v___x_5547_ = lean_unbox_uint64(v___y_5511_);
lean_dec(v___y_5511_);
v___y_5500_ = v___y_5512_;
v___y_5501_ = v___y_5513_;
v___y_5502_ = v___y_5514_;
v___y_5503_ = v___y_5516_;
v___y_5504_ = v___y_5518_;
v___y_5505_ = v_position_5520_;
v___y_5506_ = v___x_5547_;
goto v___jp_5499_;
}
}
else
{
uint64_t v___x_5548_; uint64_t v___x_5549_; uint64_t v___x_5550_; 
v___x_5548_ = lean_uint64_sub(v___x_5523_, v___y_5519_);
v___x_5549_ = lean_unbox_uint64(v___y_5511_);
lean_dec(v___y_5511_);
v___x_5550_ = lean_uint64_shift_left(v___x_5549_, v___x_5548_);
v___y_5500_ = v___y_5512_;
v___y_5501_ = v___y_5513_;
v___y_5502_ = v___y_5514_;
v___y_5503_ = v___y_5516_;
v___y_5504_ = v___y_5518_;
v___y_5505_ = v_position_5520_;
v___y_5506_ = v___x_5550_;
goto v___jp_5499_;
}
}
else
{
uint8_t v___x_5551_; 
v___x_5551_ = lean_uint64_dec_lt(v___y_5517_, v___y_5515_);
if (v___x_5551_ == 0)
{
uint64_t v___x_5552_; uint64_t v___x_5553_; uint64_t v___x_5554_; 
v___x_5552_ = lean_uint64_sub(v___y_5517_, v___y_5515_);
v___x_5553_ = lean_unbox_uint64(v___y_5511_);
lean_dec(v___y_5511_);
v___x_5554_ = lean_uint64_shift_left(v___x_5553_, v___x_5552_);
v___y_5433_ = v___y_5512_;
v___y_5434_ = v___y_5516_;
v___y_5435_ = v___x_5554_;
goto v___jp_5432_;
}
else
{
uint64_t v___x_5555_; uint8_t v___x_5556_; 
v___x_5555_ = lean_uint64_sub(v___y_5515_, v___y_5517_);
v___x_5556_ = lean_uint64_dec_eq(v___x_5555_, v___y_5512_);
if (v___x_5556_ == 0)
{
uint64_t v___x_5557_; uint8_t v___x_5558_; 
v___x_5557_ = 64ULL;
v___x_5558_ = lean_uint64_dec_lt(v___x_5555_, v___x_5557_);
if (v___x_5558_ == 0)
{
uint8_t v___x_5559_; 
v___x_5559_ = lean_uint64_dec_eq(v___x_5555_, v___x_5557_);
if (v___x_5559_ == 0)
{
lean_dec(v___y_5511_);
v___y_5433_ = v___y_5512_;
v___y_5434_ = v___y_5516_;
v___y_5435_ = v___y_5512_;
goto v___jp_5432_;
}
else
{
uint64_t v___x_5560_; uint64_t v___x_5561_; uint8_t v___x_5562_; 
v___x_5560_ = 9223372036854775808ULL;
v___x_5561_ = lean_unbox_uint64(v___y_5511_);
lean_dec(v___y_5511_);
v___x_5562_ = lean_uint64_dec_lt(v___x_5560_, v___x_5561_);
if (v___x_5562_ == 0)
{
v___y_5433_ = v___y_5512_;
v___y_5434_ = v___y_5516_;
v___y_5435_ = v___y_5512_;
goto v___jp_5432_;
}
else
{
v___y_5433_ = v___y_5512_;
v___y_5434_ = v___y_5516_;
v___y_5435_ = v___y_5514_;
goto v___jp_5432_;
}
}
}
else
{
uint64_t v___x_5563_; uint64_t v_quotient_5564_; uint64_t v___x_5565_; uint64_t v___x_5566_; uint64_t v___x_5567_; uint64_t v_remainder_5568_; uint64_t v___x_5569_; uint64_t v_half_5570_; uint8_t v___x_5571_; 
v___x_5563_ = lean_unbox_uint64(v___y_5511_);
v_quotient_5564_ = lean_uint64_shift_right(v___x_5563_, v___x_5555_);
v___x_5565_ = lean_uint64_shift_left(v___y_5514_, v___x_5555_);
v___x_5566_ = lean_uint64_sub(v___x_5565_, v___y_5514_);
v___x_5567_ = lean_unbox_uint64(v___y_5511_);
lean_dec(v___y_5511_);
v_remainder_5568_ = lean_uint64_land(v___x_5567_, v___x_5566_);
v___x_5569_ = lean_uint64_sub(v___x_5555_, v___y_5514_);
v_half_5570_ = lean_uint64_shift_left(v___y_5514_, v___x_5569_);
v___x_5571_ = lean_uint64_dec_lt(v_remainder_5568_, v_half_5570_);
if (v___x_5571_ == 0)
{
uint8_t v___x_5572_; 
v___x_5572_ = lean_uint64_dec_lt(v_half_5570_, v_remainder_5568_);
if (v___x_5572_ == 0)
{
uint64_t v___x_5573_; uint8_t v___x_5574_; 
v___x_5573_ = lean_uint64_land(v_quotient_5564_, v___y_5514_);
v___x_5574_ = lean_uint64_dec_eq(v___x_5573_, v___y_5512_);
if (v___x_5574_ == 0)
{
uint64_t v___x_5575_; 
v___x_5575_ = lean_uint64_add(v_quotient_5564_, v___y_5514_);
v___y_5433_ = v___y_5512_;
v___y_5434_ = v___y_5516_;
v___y_5435_ = v___x_5575_;
goto v___jp_5432_;
}
else
{
v___y_5433_ = v___y_5512_;
v___y_5434_ = v___y_5516_;
v___y_5435_ = v_quotient_5564_;
goto v___jp_5432_;
}
}
else
{
uint64_t v___x_5576_; 
v___x_5576_ = lean_uint64_add(v_quotient_5564_, v___y_5514_);
v___y_5433_ = v___y_5512_;
v___y_5434_ = v___y_5516_;
v___y_5435_ = v___x_5576_;
goto v___jp_5432_;
}
}
else
{
v___y_5433_ = v___y_5512_;
v___y_5434_ = v___y_5516_;
v___y_5435_ = v_quotient_5564_;
goto v___jp_5432_;
}
}
}
else
{
uint64_t v___x_5577_; 
v___x_5577_ = lean_unbox_uint64(v___y_5511_);
lean_dec(v___y_5511_);
v___y_5433_ = v___y_5512_;
v___y_5434_ = v___y_5516_;
v___y_5435_ = v___x_5577_;
goto v___jp_5432_;
}
}
}
}
v___jp_5578_:
{
uint64_t v___x_5589_; uint8_t v___x_5590_; 
v___x_5589_ = lean_uint64_shift_right(v___y_5587_, v___y_5582_);
v___x_5590_ = lean_uint64_dec_eq(v___x_5589_, v___y_5580_);
if (v___x_5590_ == 0)
{
uint64_t v___x_5591_; 
v___x_5591_ = lean_uint64_add(v___y_5588_, v___y_5582_);
v___y_5511_ = v___y_5579_;
v___y_5512_ = v___y_5580_;
v___y_5513_ = v___y_5581_;
v___y_5514_ = v___y_5582_;
v___y_5515_ = v___y_5583_;
v___y_5516_ = v___y_5584_;
v___y_5517_ = v___y_5585_;
v___y_5518_ = v___y_5586_;
v___y_5519_ = v___x_5591_;
goto v___jp_5510_;
}
else
{
v___y_5511_ = v___y_5579_;
v___y_5512_ = v___y_5580_;
v___y_5513_ = v___y_5581_;
v___y_5514_ = v___y_5582_;
v___y_5515_ = v___y_5583_;
v___y_5516_ = v___y_5584_;
v___y_5517_ = v___y_5585_;
v___y_5518_ = v___y_5586_;
v___y_5519_ = v___y_5588_;
goto v___jp_5510_;
}
}
v___jp_5592_:
{
uint64_t v___x_5605_; uint8_t v___x_5606_; 
v___x_5605_ = lean_uint64_shift_right(v___y_5600_, v___y_5598_);
v___x_5606_ = lean_uint64_dec_eq(v___x_5605_, v___y_5593_);
if (v___x_5606_ == 0)
{
uint64_t v___x_5607_; 
v___x_5607_ = lean_uint64_add(v___y_5595_, v___y_5598_);
v___y_5579_ = v___y_5594_;
v___y_5580_ = v___y_5593_;
v___y_5581_ = v___y_5596_;
v___y_5582_ = v___y_5597_;
v___y_5583_ = v___y_5599_;
v___y_5584_ = v___y_5601_;
v___y_5585_ = v___y_5602_;
v___y_5586_ = v___y_5603_;
v___y_5587_ = v___y_5604_;
v___y_5588_ = v___x_5607_;
goto v___jp_5578_;
}
else
{
v___y_5579_ = v___y_5594_;
v___y_5580_ = v___y_5593_;
v___y_5581_ = v___y_5596_;
v___y_5582_ = v___y_5597_;
v___y_5583_ = v___y_5599_;
v___y_5584_ = v___y_5601_;
v___y_5585_ = v___y_5602_;
v___y_5586_ = v___y_5603_;
v___y_5587_ = v___y_5604_;
v___y_5588_ = v___y_5595_;
goto v___jp_5578_;
}
}
v___jp_5608_:
{
uint64_t v___x_5619_; uint64_t v___x_5620_; uint8_t v___x_5621_; 
v___x_5619_ = 2ULL;
v___x_5620_ = lean_uint64_shift_right(v___y_5615_, v___x_5619_);
v___x_5621_ = lean_uint64_dec_eq(v___x_5620_, v___y_5610_);
if (v___x_5621_ == 0)
{
v___y_5593_ = v___y_5610_;
v___y_5594_ = v___y_5609_;
v___y_5595_ = v___y_5618_;
v___y_5596_ = v___y_5611_;
v___y_5597_ = v___y_5612_;
v___y_5598_ = v___x_5619_;
v___y_5599_ = v___y_5613_;
v___y_5600_ = v___y_5615_;
v___y_5601_ = v___y_5614_;
v___y_5602_ = v___y_5616_;
v___y_5603_ = v___y_5617_;
v___y_5604_ = v___x_5620_;
goto v___jp_5592_;
}
else
{
v___y_5593_ = v___y_5610_;
v___y_5594_ = v___y_5609_;
v___y_5595_ = v___y_5618_;
v___y_5596_ = v___y_5611_;
v___y_5597_ = v___y_5612_;
v___y_5598_ = v___x_5619_;
v___y_5599_ = v___y_5613_;
v___y_5600_ = v___y_5615_;
v___y_5601_ = v___y_5614_;
v___y_5602_ = v___y_5616_;
v___y_5603_ = v___y_5617_;
v___y_5604_ = v___y_5615_;
goto v___jp_5592_;
}
}
v___jp_5622_:
{
uint64_t v___x_5635_; uint8_t v___x_5636_; 
v___x_5635_ = lean_uint64_shift_right(v___y_5631_, v___y_5625_);
v___x_5636_ = lean_uint64_dec_eq(v___x_5635_, v___y_5623_);
if (v___x_5636_ == 0)
{
uint64_t v___x_5637_; 
v___x_5637_ = lean_uint64_add(v___y_5629_, v___y_5625_);
v___y_5609_ = v___y_5624_;
v___y_5610_ = v___y_5623_;
v___y_5611_ = v___y_5626_;
v___y_5612_ = v___y_5627_;
v___y_5613_ = v___y_5628_;
v___y_5614_ = v___y_5630_;
v___y_5615_ = v___y_5634_;
v___y_5616_ = v___y_5632_;
v___y_5617_ = v___y_5633_;
v___y_5618_ = v___x_5637_;
goto v___jp_5608_;
}
else
{
v___y_5609_ = v___y_5624_;
v___y_5610_ = v___y_5623_;
v___y_5611_ = v___y_5626_;
v___y_5612_ = v___y_5627_;
v___y_5613_ = v___y_5628_;
v___y_5614_ = v___y_5630_;
v___y_5615_ = v___y_5634_;
v___y_5616_ = v___y_5632_;
v___y_5617_ = v___y_5633_;
v___y_5618_ = v___y_5629_;
goto v___jp_5608_;
}
}
v___jp_5638_:
{
uint64_t v___x_5649_; uint64_t v___x_5650_; uint8_t v___x_5651_; 
v___x_5649_ = 4ULL;
v___x_5650_ = lean_uint64_shift_right(v___y_5645_, v___x_5649_);
v___x_5651_ = lean_uint64_dec_eq(v___x_5650_, v___y_5640_);
if (v___x_5651_ == 0)
{
v___y_5623_ = v___y_5640_;
v___y_5624_ = v___y_5639_;
v___y_5625_ = v___x_5649_;
v___y_5626_ = v___y_5641_;
v___y_5627_ = v___y_5642_;
v___y_5628_ = v___y_5643_;
v___y_5629_ = v___y_5648_;
v___y_5630_ = v___y_5644_;
v___y_5631_ = v___y_5645_;
v___y_5632_ = v___y_5646_;
v___y_5633_ = v___y_5647_;
v___y_5634_ = v___x_5650_;
goto v___jp_5622_;
}
else
{
v___y_5623_ = v___y_5640_;
v___y_5624_ = v___y_5639_;
v___y_5625_ = v___x_5649_;
v___y_5626_ = v___y_5641_;
v___y_5627_ = v___y_5642_;
v___y_5628_ = v___y_5643_;
v___y_5629_ = v___y_5648_;
v___y_5630_ = v___y_5644_;
v___y_5631_ = v___y_5645_;
v___y_5632_ = v___y_5646_;
v___y_5633_ = v___y_5647_;
v___y_5634_ = v___y_5645_;
goto v___jp_5622_;
}
}
v___jp_5652_:
{
uint64_t v___x_5665_; uint8_t v___x_5666_; 
v___x_5665_ = lean_uint64_shift_right(v___y_5658_, v___y_5657_);
v___x_5666_ = lean_uint64_dec_eq(v___x_5665_, v___y_5653_);
if (v___x_5666_ == 0)
{
uint64_t v___x_5667_; 
v___x_5667_ = lean_uint64_add(v___y_5655_, v___y_5657_);
v___y_5639_ = v___y_5654_;
v___y_5640_ = v___y_5653_;
v___y_5641_ = v___y_5656_;
v___y_5642_ = v___y_5659_;
v___y_5643_ = v___y_5660_;
v___y_5644_ = v___y_5661_;
v___y_5645_ = v___y_5664_;
v___y_5646_ = v___y_5662_;
v___y_5647_ = v___y_5663_;
v___y_5648_ = v___x_5667_;
goto v___jp_5638_;
}
else
{
v___y_5639_ = v___y_5654_;
v___y_5640_ = v___y_5653_;
v___y_5641_ = v___y_5656_;
v___y_5642_ = v___y_5659_;
v___y_5643_ = v___y_5660_;
v___y_5644_ = v___y_5661_;
v___y_5645_ = v___y_5664_;
v___y_5646_ = v___y_5662_;
v___y_5647_ = v___y_5663_;
v___y_5648_ = v___y_5655_;
goto v___jp_5638_;
}
}
v___jp_5668_:
{
uint64_t v___x_5679_; uint64_t v___x_5680_; uint8_t v___x_5681_; 
v___x_5679_ = 8ULL;
v___x_5680_ = lean_uint64_shift_right(v___y_5672_, v___x_5679_);
v___x_5681_ = lean_uint64_dec_eq(v___x_5680_, v___y_5670_);
if (v___x_5681_ == 0)
{
v___y_5653_ = v___y_5670_;
v___y_5654_ = v___y_5669_;
v___y_5655_ = v___y_5678_;
v___y_5656_ = v___y_5671_;
v___y_5657_ = v___x_5679_;
v___y_5658_ = v___y_5672_;
v___y_5659_ = v___y_5673_;
v___y_5660_ = v___y_5674_;
v___y_5661_ = v___y_5675_;
v___y_5662_ = v___y_5676_;
v___y_5663_ = v___y_5677_;
v___y_5664_ = v___x_5680_;
goto v___jp_5652_;
}
else
{
v___y_5653_ = v___y_5670_;
v___y_5654_ = v___y_5669_;
v___y_5655_ = v___y_5678_;
v___y_5656_ = v___y_5671_;
v___y_5657_ = v___x_5679_;
v___y_5658_ = v___y_5672_;
v___y_5659_ = v___y_5673_;
v___y_5660_ = v___y_5674_;
v___y_5661_ = v___y_5675_;
v___y_5662_ = v___y_5676_;
v___y_5663_ = v___y_5677_;
v___y_5664_ = v___y_5672_;
goto v___jp_5652_;
}
}
v___jp_5682_:
{
uint64_t v___x_5695_; uint8_t v___x_5696_; 
v___x_5695_ = lean_uint64_shift_right(v___y_5685_, v___y_5688_);
v___x_5696_ = lean_uint64_dec_eq(v___x_5695_, v___y_5683_);
if (v___x_5696_ == 0)
{
uint64_t v___x_5697_; 
v___x_5697_ = lean_uint64_add(v___y_5693_, v___y_5688_);
v___y_5669_ = v___y_5684_;
v___y_5670_ = v___y_5683_;
v___y_5671_ = v___y_5686_;
v___y_5672_ = v___y_5694_;
v___y_5673_ = v___y_5687_;
v___y_5674_ = v___y_5689_;
v___y_5675_ = v___y_5690_;
v___y_5676_ = v___y_5691_;
v___y_5677_ = v___y_5692_;
v___y_5678_ = v___x_5697_;
goto v___jp_5668_;
}
else
{
v___y_5669_ = v___y_5684_;
v___y_5670_ = v___y_5683_;
v___y_5671_ = v___y_5686_;
v___y_5672_ = v___y_5694_;
v___y_5673_ = v___y_5687_;
v___y_5674_ = v___y_5689_;
v___y_5675_ = v___y_5690_;
v___y_5676_ = v___y_5691_;
v___y_5677_ = v___y_5692_;
v___y_5678_ = v___y_5693_;
goto v___jp_5668_;
}
}
v___jp_5698_:
{
uint64_t v___x_5709_; uint64_t v___x_5710_; uint8_t v___x_5711_; 
v___x_5709_ = 16ULL;
v___x_5710_ = lean_uint64_shift_right(v___y_5701_, v___x_5709_);
v___x_5711_ = lean_uint64_dec_eq(v___x_5710_, v___y_5700_);
if (v___x_5711_ == 0)
{
v___y_5683_ = v___y_5700_;
v___y_5684_ = v___y_5699_;
v___y_5685_ = v___y_5701_;
v___y_5686_ = v___y_5702_;
v___y_5687_ = v___y_5703_;
v___y_5688_ = v___x_5709_;
v___y_5689_ = v___y_5704_;
v___y_5690_ = v___y_5705_;
v___y_5691_ = v___y_5706_;
v___y_5692_ = v___y_5707_;
v___y_5693_ = v___y_5708_;
v___y_5694_ = v___x_5710_;
goto v___jp_5682_;
}
else
{
v___y_5683_ = v___y_5700_;
v___y_5684_ = v___y_5699_;
v___y_5685_ = v___y_5701_;
v___y_5686_ = v___y_5702_;
v___y_5687_ = v___y_5703_;
v___y_5688_ = v___x_5709_;
v___y_5689_ = v___y_5704_;
v___y_5690_ = v___y_5705_;
v___y_5691_ = v___y_5706_;
v___y_5692_ = v___y_5707_;
v___y_5693_ = v___y_5708_;
v___y_5694_ = v___y_5701_;
goto v___jp_5682_;
}
}
v___jp_5712_:
{
uint64_t v___x_5723_; uint64_t v___x_5724_; uint8_t v___x_5725_; 
v___x_5723_ = lean_unbox_uint64(v___y_5714_);
v___x_5724_ = lean_uint64_shift_right(v___x_5723_, v___y_5720_);
v___x_5725_ = lean_uint64_dec_eq(v___x_5724_, v___y_5713_);
if (v___x_5725_ == 0)
{
v___y_5699_ = v___y_5714_;
v___y_5700_ = v___y_5713_;
v___y_5701_ = v___y_5722_;
v___y_5702_ = v___y_5715_;
v___y_5703_ = v___y_5716_;
v___y_5704_ = v___y_5717_;
v___y_5705_ = v___y_5718_;
v___y_5706_ = v___y_5719_;
v___y_5707_ = v___y_5721_;
v___y_5708_ = v___y_5720_;
goto v___jp_5698_;
}
else
{
v___y_5699_ = v___y_5714_;
v___y_5700_ = v___y_5713_;
v___y_5701_ = v___y_5722_;
v___y_5702_ = v___y_5715_;
v___y_5703_ = v___y_5716_;
v___y_5704_ = v___y_5717_;
v___y_5705_ = v___y_5718_;
v___y_5706_ = v___y_5719_;
v___y_5707_ = v___y_5721_;
v___y_5708_ = v___y_5713_;
goto v___jp_5698_;
}
}
v___jp_5726_:
{
uint64_t v___x_5733_; uint64_t v___x_5734_; uint8_t v___x_5735_; 
v___x_5733_ = 0ULL;
v___x_5734_ = lean_unbox_uint64(v_snd_5732_);
v___x_5735_ = lean_uint64_dec_eq(v___x_5734_, v___x_5733_);
if (v___x_5735_ == 0)
{
uint64_t v___x_5736_; uint64_t v___x_5737_; uint64_t v___x_5738_; uint64_t v___x_5739_; uint64_t v___x_5740_; uint8_t v___x_5741_; 
v___x_5736_ = 149ULL;
v___x_5737_ = lean_uint64_add(v___y_5729_, v___x_5736_);
v___x_5738_ = 32ULL;
v___x_5739_ = lean_unbox_uint64(v_snd_5732_);
v___x_5740_ = lean_uint64_shift_right(v___x_5739_, v___x_5738_);
v___x_5741_ = lean_uint64_dec_eq(v___x_5740_, v___x_5733_);
if (v___x_5741_ == 0)
{
v___y_5713_ = v___x_5733_;
v___y_5714_ = v_snd_5732_;
v___y_5715_ = v___y_5727_;
v___y_5716_ = v___y_5728_;
v___y_5717_ = v___x_5736_;
v___y_5718_ = v_fst_5731_;
v___y_5719_ = v___x_5737_;
v___y_5720_ = v___x_5738_;
v___y_5721_ = v___y_5730_;
v___y_5722_ = v___x_5740_;
goto v___jp_5712_;
}
else
{
uint64_t v___x_5742_; 
v___x_5742_ = lean_unbox_uint64(v_snd_5732_);
v___y_5713_ = v___x_5733_;
v___y_5714_ = v_snd_5732_;
v___y_5715_ = v___y_5727_;
v___y_5716_ = v___y_5728_;
v___y_5717_ = v___x_5736_;
v___y_5718_ = v_fst_5731_;
v___y_5719_ = v___x_5737_;
v___y_5720_ = v___x_5738_;
v___y_5721_ = v___y_5730_;
v___y_5722_ = v___x_5742_;
goto v___jp_5712_;
}
}
else
{
uint8_t v___x_5743_; 
lean_dec(v_snd_5732_);
v___x_5743_ = lean_unbox(v_fst_5731_);
lean_dec(v_fst_5731_);
if (v___x_5743_ == 0)
{
uint32_t v___x_5744_; 
v___x_5744_ = 0;
return v___x_5744_;
}
else
{
uint32_t v___x_5745_; 
v___x_5745_ = 2147483648;
return v___x_5745_;
}
}
}
v___jp_5746_:
{
uint8_t v___x_5756_; 
v___x_5756_ = lean_uint64_dec_eq(v___y_5754_, v___y_5749_);
if (v___x_5756_ == 0)
{
uint8_t v___x_5757_; 
v___x_5757_ = lean_uint64_dec_lt(v___y_5754_, v___y_5749_);
if (v___x_5757_ == 0)
{
uint64_t v___x_5758_; lean_object* v___x_5759_; lean_object* v___x_5760_; 
v___x_5758_ = lean_uint64_sub(v___y_5754_, v___y_5749_);
v___x_5759_ = lean_box(v___y_5748_);
v___x_5760_ = lean_box_uint64(v___x_5758_);
v___y_5727_ = v___y_5747_;
v___y_5728_ = v___y_5750_;
v___y_5729_ = v___y_5751_;
v___y_5730_ = v___y_5753_;
v_fst_5731_ = v___x_5759_;
v_snd_5732_ = v___x_5760_;
goto v___jp_5726_;
}
else
{
uint64_t v___x_5761_; lean_object* v___x_5762_; lean_object* v___x_5763_; 
v___x_5761_ = lean_uint64_sub(v___y_5749_, v___y_5754_);
v___x_5762_ = lean_box(v___y_5752_);
v___x_5763_ = lean_box_uint64(v___x_5761_);
v___y_5727_ = v___y_5747_;
v___y_5728_ = v___y_5750_;
v___y_5729_ = v___y_5751_;
v___y_5730_ = v___y_5753_;
v_fst_5731_ = v___x_5762_;
v_snd_5732_ = v___x_5763_;
goto v___jp_5726_;
}
}
else
{
lean_object* v___x_5764_; lean_object* v___x_5765_; 
v___x_5764_ = lean_box(v___y_5755_);
v___x_5765_ = ((lean_object*)(lp_competition_Submission_TunedAdd_core___boxed__const__1));
v___y_5727_ = v___y_5747_;
v___y_5728_ = v___y_5750_;
v___y_5729_ = v___y_5751_;
v___y_5730_ = v___y_5753_;
v_fst_5731_ = v___x_5764_;
v_snd_5732_ = v___x_5765_;
goto v___jp_5726_;
}
}
v___jp_5766_:
{
if (v___y_5775_ == 0)
{
v___y_5747_ = v___y_5767_;
v___y_5748_ = v___y_5769_;
v___y_5749_ = v___y_5768_;
v___y_5750_ = v___y_5770_;
v___y_5751_ = v___y_5771_;
v___y_5752_ = v___y_5772_;
v___y_5753_ = v___y_5774_;
v___y_5754_ = v___y_5773_;
v___y_5755_ = v___y_5775_;
goto v___jp_5746_;
}
else
{
uint64_t v___x_5776_; lean_object* v___x_5777_; lean_object* v___x_5778_; 
v___x_5776_ = lean_uint64_add(v___y_5773_, v___y_5768_);
v___x_5777_ = lean_box(v___y_5769_);
v___x_5778_ = lean_box_uint64(v___x_5776_);
v___y_5727_ = v___y_5767_;
v___y_5728_ = v___y_5770_;
v___y_5729_ = v___y_5771_;
v___y_5730_ = v___y_5774_;
v_fst_5731_ = v___x_5777_;
v_snd_5732_ = v___x_5778_;
goto v___jp_5726_;
}
}
v___jp_5779_:
{
uint8_t v___x_5789_; 
v___x_5789_ = lean_uint64_dec_eq(v___y_5780_, v___y_5781_);
if (v___x_5789_ == 0)
{
uint8_t v___x_5790_; 
v___x_5790_ = lean_uint64_dec_lt(v___y_5780_, v___y_5781_);
if (v___x_5790_ == 0)
{
uint64_t v___x_5791_; lean_object* v___x_5792_; lean_object* v___x_5793_; 
v___x_5791_ = lean_uint64_sub(v___y_5780_, v___y_5781_);
v___x_5792_ = lean_box(v___y_5783_);
v___x_5793_ = lean_box_uint64(v___x_5791_);
v___y_5407_ = v___y_5782_;
v___y_5408_ = v___y_5784_;
v___y_5409_ = v___y_5786_;
v___y_5410_ = v___y_5787_;
v_fst_5411_ = v___x_5792_;
v_snd_5412_ = v___x_5793_;
goto v___jp_5406_;
}
else
{
uint64_t v___x_5794_; lean_object* v___x_5795_; lean_object* v___x_5796_; 
v___x_5794_ = lean_uint64_sub(v___y_5781_, v___y_5780_);
v___x_5795_ = lean_box(v___y_5785_);
v___x_5796_ = lean_box_uint64(v___x_5794_);
v___y_5407_ = v___y_5782_;
v___y_5408_ = v___y_5784_;
v___y_5409_ = v___y_5786_;
v___y_5410_ = v___y_5787_;
v_fst_5411_ = v___x_5795_;
v_snd_5412_ = v___x_5796_;
goto v___jp_5406_;
}
}
else
{
lean_object* v___x_5797_; lean_object* v___x_5798_; 
v___x_5797_ = lean_box(v___y_5788_);
v___x_5798_ = ((lean_object*)(lp_competition_Submission_TunedAdd_core___boxed__const__1));
v___y_5407_ = v___y_5782_;
v___y_5408_ = v___y_5784_;
v___y_5409_ = v___y_5786_;
v___y_5410_ = v___y_5787_;
v_fst_5411_ = v___x_5797_;
v_snd_5412_ = v___x_5798_;
goto v___jp_5406_;
}
}
v___jp_5799_:
{
if (v___y_5808_ == 0)
{
v___y_5780_ = v___y_5800_;
v___y_5781_ = v___y_5801_;
v___y_5782_ = v___y_5802_;
v___y_5783_ = v___y_5803_;
v___y_5784_ = v___y_5804_;
v___y_5785_ = v___y_5806_;
v___y_5786_ = v___y_5805_;
v___y_5787_ = v___y_5807_;
v___y_5788_ = v___y_5808_;
goto v___jp_5779_;
}
else
{
uint64_t v___x_5809_; lean_object* v___x_5810_; lean_object* v___x_5811_; 
v___x_5809_ = lean_uint64_add(v___y_5800_, v___y_5801_);
v___x_5810_ = lean_box(v___y_5803_);
v___x_5811_ = lean_box_uint64(v___x_5809_);
v___y_5407_ = v___y_5802_;
v___y_5408_ = v___y_5804_;
v___y_5409_ = v___y_5805_;
v___y_5410_ = v___y_5807_;
v_fst_5411_ = v___x_5810_;
v_snd_5412_ = v___x_5811_;
goto v___jp_5406_;
}
}
v___jp_5812_:
{
uint8_t v___x_5822_; 
v___x_5822_ = lean_uint64_dec_le(v___y_5819_, v___y_5821_);
if (v___x_5822_ == 0)
{
uint64_t v_shift_5823_; uint64_t v___x_5824_; uint8_t v___x_5825_; 
v_shift_5823_ = lean_uint64_sub(v___y_5819_, v___y_5821_);
v___x_5824_ = 39ULL;
v___x_5825_ = lean_uint64_dec_le(v_shift_5823_, v___x_5824_);
if (v___x_5825_ == 0)
{
return v_x_5072_;
}
else
{
uint64_t v___x_5826_; 
v___x_5826_ = lean_uint64_shift_left(v___y_5813_, v_shift_5823_);
if (v___y_5816_ == 0)
{
if (v___y_5818_ == 0)
{
v___y_5767_ = v___y_5814_;
v___y_5768_ = v___y_5815_;
v___y_5769_ = v___y_5816_;
v___y_5770_ = v___y_5817_;
v___y_5771_ = v___y_5821_;
v___y_5772_ = v___y_5818_;
v___y_5773_ = v___x_5826_;
v___y_5774_ = v___y_5820_;
v___y_5775_ = v___x_5825_;
goto v___jp_5766_;
}
else
{
v___y_5747_ = v___y_5814_;
v___y_5748_ = v___y_5816_;
v___y_5749_ = v___y_5815_;
v___y_5750_ = v___y_5817_;
v___y_5751_ = v___y_5821_;
v___y_5752_ = v___y_5818_;
v___y_5753_ = v___y_5820_;
v___y_5754_ = v___x_5826_;
v___y_5755_ = v___y_5816_;
goto v___jp_5746_;
}
}
else
{
v___y_5767_ = v___y_5814_;
v___y_5768_ = v___y_5815_;
v___y_5769_ = v___y_5816_;
v___y_5770_ = v___y_5817_;
v___y_5771_ = v___y_5821_;
v___y_5772_ = v___y_5818_;
v___y_5773_ = v___x_5826_;
v___y_5774_ = v___y_5820_;
v___y_5775_ = v___y_5818_;
goto v___jp_5766_;
}
}
}
else
{
uint64_t v_shift_5827_; uint64_t v___x_5828_; uint8_t v___x_5829_; 
v_shift_5827_ = lean_uint64_sub(v___y_5821_, v___y_5819_);
v___x_5828_ = 39ULL;
v___x_5829_ = lean_uint64_dec_le(v_shift_5827_, v___x_5828_);
if (v___x_5829_ == 0)
{
return v_y_5073_;
}
else
{
uint64_t v___x_5830_; 
v___x_5830_ = lean_uint64_shift_left(v___y_5815_, v_shift_5827_);
if (v___y_5816_ == 0)
{
if (v___y_5818_ == 0)
{
v___y_5800_ = v___y_5813_;
v___y_5801_ = v___x_5830_;
v___y_5802_ = v___y_5814_;
v___y_5803_ = v___y_5816_;
v___y_5804_ = v___y_5817_;
v___y_5805_ = v___y_5819_;
v___y_5806_ = v___y_5818_;
v___y_5807_ = v___y_5820_;
v___y_5808_ = v___x_5829_;
goto v___jp_5799_;
}
else
{
v___y_5780_ = v___y_5813_;
v___y_5781_ = v___x_5830_;
v___y_5782_ = v___y_5814_;
v___y_5783_ = v___y_5816_;
v___y_5784_ = v___y_5817_;
v___y_5785_ = v___y_5818_;
v___y_5786_ = v___y_5819_;
v___y_5787_ = v___y_5820_;
v___y_5788_ = v___y_5816_;
goto v___jp_5779_;
}
}
else
{
v___y_5800_ = v___y_5813_;
v___y_5801_ = v___x_5830_;
v___y_5802_ = v___y_5814_;
v___y_5803_ = v___y_5816_;
v___y_5804_ = v___y_5817_;
v___y_5805_ = v___y_5819_;
v___y_5806_ = v___y_5818_;
v___y_5807_ = v___y_5820_;
v___y_5808_ = v___y_5818_;
goto v___jp_5799_;
}
}
}
}
v___jp_5831_:
{
uint64_t v___x_5841_; uint64_t v___x_5842_; uint8_t v___x_5843_; 
v___x_5841_ = lean_uint32_to_uint64(v___y_5834_);
v___x_5842_ = 0ULL;
v___x_5843_ = lean_uint64_dec_eq(v___x_5841_, v___x_5842_);
if (v___x_5843_ == 0)
{
uint64_t v___x_5844_; 
v___x_5844_ = lean_uint64_sub(v___x_5841_, v___y_5837_);
v___y_5813_ = v___y_5832_;
v___y_5814_ = v___y_5833_;
v___y_5815_ = v___y_5836_;
v___y_5816_ = v___y_5835_;
v___y_5817_ = v___y_5837_;
v___y_5818_ = v___y_5838_;
v___y_5819_ = v___y_5840_;
v___y_5820_ = v___y_5839_;
v___y_5821_ = v___x_5844_;
goto v___jp_5812_;
}
else
{
v___y_5813_ = v___y_5832_;
v___y_5814_ = v___y_5833_;
v___y_5815_ = v___y_5836_;
v___y_5816_ = v___y_5835_;
v___y_5817_ = v___y_5837_;
v___y_5818_ = v___y_5838_;
v___y_5819_ = v___y_5840_;
v___y_5820_ = v___y_5839_;
v___y_5821_ = v___x_5842_;
goto v___jp_5812_;
}
}
v___jp_5845_:
{
uint64_t v___x_5855_; uint64_t v___x_5856_; uint8_t v___x_5857_; 
v___x_5855_ = lean_uint32_to_uint64(v___y_5846_);
v___x_5856_ = 0ULL;
v___x_5857_ = lean_uint64_dec_eq(v___x_5855_, v___x_5856_);
if (v___x_5857_ == 0)
{
uint64_t v___x_5858_; 
v___x_5858_ = lean_uint64_sub(v___x_5855_, v___y_5851_);
v___y_5832_ = v___y_5847_;
v___y_5833_ = v___y_5848_;
v___y_5834_ = v___y_5849_;
v___y_5835_ = v___y_5850_;
v___y_5836_ = v___y_5854_;
v___y_5837_ = v___y_5851_;
v___y_5838_ = v___y_5852_;
v___y_5839_ = v___y_5853_;
v___y_5840_ = v___x_5858_;
goto v___jp_5831_;
}
else
{
v___y_5832_ = v___y_5847_;
v___y_5833_ = v___y_5848_;
v___y_5834_ = v___y_5849_;
v___y_5835_ = v___y_5850_;
v___y_5836_ = v___y_5854_;
v___y_5837_ = v___y_5851_;
v___y_5838_ = v___y_5852_;
v___y_5839_ = v___y_5853_;
v___y_5840_ = v___x_5856_;
goto v___jp_5831_;
}
}
v___jp_5859_:
{
uint32_t v___x_5868_; uint32_t v___x_5869_; uint32_t v___x_5870_; uint8_t v___x_5871_; 
v___x_5868_ = 8388607;
v___x_5869_ = lean_uint32_land(v_y_5073_, v___x_5868_);
v___x_5870_ = 0;
v___x_5871_ = lean_uint32_dec_eq(v___y_5862_, v___x_5870_);
if (v___x_5871_ == 0)
{
uint64_t v___x_5872_; uint64_t v___x_5873_; uint64_t v___x_5874_; 
v___x_5872_ = lean_uint32_to_uint64(v___x_5869_);
v___x_5873_ = 8388608ULL;
v___x_5874_ = lean_uint64_lor(v___x_5872_, v___x_5873_);
v___y_5846_ = v___y_5860_;
v___y_5847_ = v___y_5867_;
v___y_5848_ = v___y_5861_;
v___y_5849_ = v___y_5862_;
v___y_5850_ = v___y_5863_;
v___y_5851_ = v___y_5864_;
v___y_5852_ = v___y_5865_;
v___y_5853_ = v___y_5866_;
v___y_5854_ = v___x_5874_;
goto v___jp_5845_;
}
else
{
uint64_t v___x_5875_; 
v___x_5875_ = lean_uint32_to_uint64(v___x_5869_);
v___y_5846_ = v___y_5860_;
v___y_5847_ = v___y_5867_;
v___y_5848_ = v___y_5861_;
v___y_5849_ = v___y_5862_;
v___y_5850_ = v___y_5863_;
v___y_5851_ = v___y_5864_;
v___y_5852_ = v___y_5865_;
v___y_5853_ = v___y_5866_;
v___y_5854_ = v___x_5875_;
goto v___jp_5845_;
}
}
v___jp_5876_:
{
uint32_t v___x_5884_; uint32_t v___x_5885_; uint32_t v___x_5886_; uint8_t v___x_5887_; 
v___x_5884_ = 8388607;
v___x_5885_ = lean_uint32_land(v_x_5072_, v___x_5884_);
v___x_5886_ = 0;
v___x_5887_ = lean_uint32_dec_eq(v___y_5877_, v___x_5886_);
if (v___x_5887_ == 0)
{
uint64_t v___x_5888_; uint64_t v___x_5889_; uint64_t v___x_5890_; 
v___x_5888_ = lean_uint32_to_uint64(v___x_5885_);
v___x_5889_ = 8388608ULL;
v___x_5890_ = lean_uint64_lor(v___x_5888_, v___x_5889_);
v___y_5860_ = v___y_5877_;
v___y_5861_ = v___y_5878_;
v___y_5862_ = v___y_5879_;
v___y_5863_ = v___y_5880_;
v___y_5864_ = v___y_5881_;
v___y_5865_ = v___y_5883_;
v___y_5866_ = v___y_5882_;
v___y_5867_ = v___x_5890_;
goto v___jp_5859_;
}
else
{
uint64_t v___x_5891_; 
v___x_5891_ = lean_uint32_to_uint64(v___x_5885_);
v___y_5860_ = v___y_5877_;
v___y_5861_ = v___y_5878_;
v___y_5862_ = v___y_5879_;
v___y_5863_ = v___y_5880_;
v___y_5864_ = v___y_5881_;
v___y_5865_ = v___y_5883_;
v___y_5866_ = v___y_5882_;
v___y_5867_ = v___x_5891_;
goto v___jp_5859_;
}
}
v___jp_5892_:
{
uint32_t v___x_5901_; uint32_t v___x_5902_; uint32_t v___x_5903_; uint8_t v___x_5904_; 
v___x_5901_ = 2147483648;
v___x_5902_ = lean_uint32_land(v_y_5073_, v___x_5901_);
v___x_5903_ = 0;
v___x_5904_ = lean_uint32_dec_eq(v___x_5902_, v___x_5903_);
if (v___x_5904_ == 0)
{
v___y_5877_ = v___y_5893_;
v___y_5878_ = v___y_5894_;
v___y_5879_ = v___y_5896_;
v___y_5880_ = v___y_5900_;
v___y_5881_ = v___y_5897_;
v___y_5882_ = v___y_5899_;
v___y_5883_ = v___y_5898_;
goto v___jp_5876_;
}
else
{
v___y_5877_ = v___y_5893_;
v___y_5878_ = v___y_5894_;
v___y_5879_ = v___y_5896_;
v___y_5880_ = v___y_5900_;
v___y_5881_ = v___y_5897_;
v___y_5882_ = v___y_5899_;
v___y_5883_ = v___y_5895_;
goto v___jp_5876_;
}
}
v___jp_5905_:
{
uint32_t v___x_5908_; uint32_t v___x_5909_; uint32_t v___x_5910_; 
v___x_5908_ = 8388607;
v___x_5909_ = lean_uint32_land(v___y_5906_, v___x_5908_);
v___x_5910_ = lean_uint32_lor(v___y_5907_, v___x_5909_);
return v___x_5910_;
}
v___jp_5911_:
{
uint8_t v___x_5915_; 
v___x_5915_ = lean_uint64_dec_eq(v___y_5914_, v___y_5912_);
if (v___x_5915_ == 0)
{
uint64_t v___x_5916_; uint8_t v___x_5917_; 
v___x_5916_ = 8388608ULL;
v___x_5917_ = lean_uint64_dec_eq(v___y_5914_, v___x_5916_);
if (v___x_5917_ == 0)
{
uint32_t v___x_5918_; uint8_t v___x_5919_; 
v___x_5918_ = lean_uint64_to_uint32(v___y_5914_);
v___x_5919_ = lean_unbox(v___y_5913_);
lean_dec(v___y_5913_);
if (v___x_5919_ == 0)
{
uint32_t v___x_5920_; 
v___x_5920_ = 0;
v___y_5906_ = v___x_5918_;
v___y_5907_ = v___x_5920_;
goto v___jp_5905_;
}
else
{
uint32_t v___x_5921_; 
v___x_5921_ = 2147483648;
v___y_5906_ = v___x_5918_;
v___y_5907_ = v___x_5921_;
goto v___jp_5905_;
}
}
else
{
uint8_t v___x_5922_; 
v___x_5922_ = lean_unbox(v___y_5913_);
lean_dec(v___y_5913_);
if (v___x_5922_ == 0)
{
uint32_t v___x_5923_; 
v___x_5923_ = 0;
v___y_5087_ = v___x_5923_;
goto v___jp_5086_;
}
else
{
uint32_t v___x_5924_; 
v___x_5924_ = 2147483648;
v___y_5087_ = v___x_5924_;
goto v___jp_5086_;
}
}
}
else
{
uint8_t v___x_5925_; 
v___x_5925_ = lean_unbox(v___y_5913_);
lean_dec(v___y_5913_);
if (v___x_5925_ == 0)
{
uint32_t v___x_5926_; 
v___x_5926_ = 0;
return v___x_5926_;
}
else
{
uint32_t v___x_5927_; 
v___x_5927_ = 2147483648;
return v___x_5927_;
}
}
}
v___jp_5928_:
{
uint32_t v___x_5934_; uint32_t v___x_5935_; uint32_t v___x_5936_; uint32_t v___x_5937_; uint32_t v___x_5938_; uint32_t v___x_5939_; 
v___x_5934_ = lean_uint32_land(v___y_5932_, v___y_5930_);
v___x_5935_ = lean_uint32_shift_left(v___x_5934_, v___y_5931_);
v___x_5936_ = lean_uint32_lor(v___y_5933_, v___x_5935_);
v___x_5937_ = 8388607;
v___x_5938_ = lean_uint32_land(v___y_5929_, v___x_5937_);
v___x_5939_ = lean_uint32_lor(v___x_5936_, v___x_5938_);
return v___x_5939_;
}
v___jp_5940_:
{
uint8_t v___x_5946_; 
v___x_5946_ = lean_unbox(v___y_5944_);
lean_dec(v___y_5944_);
if (v___x_5946_ == 0)
{
uint32_t v___x_5947_; 
v___x_5947_ = 0;
v___y_5929_ = v___y_5945_;
v___y_5930_ = v___y_5941_;
v___y_5931_ = v___y_5943_;
v___y_5932_ = v___y_5942_;
v___y_5933_ = v___x_5947_;
goto v___jp_5928_;
}
else
{
uint32_t v___x_5948_; 
v___x_5948_ = 2147483648;
v___y_5929_ = v___y_5945_;
v___y_5930_ = v___y_5941_;
v___y_5931_ = v___y_5943_;
v___y_5932_ = v___y_5942_;
v___y_5933_ = v___x_5948_;
goto v___jp_5928_;
}
}
v___jp_5949_:
{
uint64_t v___x_5956_; uint64_t v_encodedExponent_5957_; uint32_t v___x_5958_; uint64_t v___x_5959_; uint8_t v___x_5960_; 
v___x_5956_ = 171ULL;
v_encodedExponent_5957_ = lean_uint64_sub(v___y_5951_, v___x_5956_);
v___x_5958_ = lean_uint64_to_uint32(v_encodedExponent_5957_);
v___x_5959_ = 8388608ULL;
v___x_5960_ = lean_uint64_dec_lt(v___y_5955_, v___x_5959_);
if (v___x_5960_ == 0)
{
uint64_t v___x_5961_; uint32_t v___x_5962_; 
v___x_5961_ = lean_uint64_sub(v___y_5955_, v___x_5959_);
v___x_5962_ = lean_uint64_to_uint32(v___x_5961_);
v___y_5941_ = v___y_5952_;
v___y_5942_ = v___x_5958_;
v___y_5943_ = v___y_5953_;
v___y_5944_ = v___y_5954_;
v___y_5945_ = v___x_5962_;
goto v___jp_5940_;
}
else
{
uint32_t v___x_5963_; 
v___x_5963_ = lean_uint64_to_uint32(v___y_5950_);
v___y_5941_ = v___y_5952_;
v___y_5942_ = v___x_5958_;
v___y_5943_ = v___y_5953_;
v___y_5944_ = v___y_5954_;
v___y_5945_ = v___x_5963_;
goto v___jp_5940_;
}
}
v___jp_5964_:
{
uint64_t v___x_5972_; uint8_t v___x_5973_; 
v___x_5972_ = 425ULL;
v___x_5973_ = lean_uint64_dec_lt(v___x_5972_, v___y_5971_);
if (v___x_5973_ == 0)
{
if (v___y_5968_ == 0)
{
v___y_5950_ = v___y_5965_;
v___y_5951_ = v___y_5971_;
v___y_5952_ = v___y_5966_;
v___y_5953_ = v___y_5969_;
v___y_5954_ = v___y_5970_;
v___y_5955_ = v___y_5967_;
goto v___jp_5949_;
}
else
{
uint64_t v___x_5974_; 
v___x_5974_ = 8388608ULL;
v___y_5950_ = v___y_5965_;
v___y_5951_ = v___y_5971_;
v___y_5952_ = v___y_5966_;
v___y_5953_ = v___y_5969_;
v___y_5954_ = v___y_5970_;
v___y_5955_ = v___x_5974_;
goto v___jp_5949_;
}
}
else
{
uint8_t v___x_5975_; 
v___x_5975_ = lean_unbox(v___y_5970_);
lean_dec(v___y_5970_);
if (v___x_5975_ == 0)
{
uint32_t v___x_5976_; 
v___x_5976_ = 2139095040;
return v___x_5976_;
}
else
{
uint32_t v___x_5977_; 
v___x_5977_ = 4286578688;
return v___x_5977_;
}
}
}
v___jp_5978_:
{
uint64_t v___x_5986_; uint8_t v_carry_5987_; 
v___x_5986_ = 16777216ULL;
v_carry_5987_ = lean_uint64_dec_eq(v___y_5985_, v___x_5986_);
if (v_carry_5987_ == 0)
{
v___y_5965_ = v___y_5979_;
v___y_5966_ = v___y_5980_;
v___y_5967_ = v___y_5985_;
v___y_5968_ = v_carry_5987_;
v___y_5969_ = v___y_5983_;
v___y_5970_ = v___y_5984_;
v___y_5971_ = v___y_5982_;
goto v___jp_5964_;
}
else
{
uint64_t v___x_5988_; 
v___x_5988_ = lean_uint64_add(v___y_5982_, v___y_5981_);
v___y_5965_ = v___y_5979_;
v___y_5966_ = v___y_5980_;
v___y_5967_ = v___y_5985_;
v___y_5968_ = v_carry_5987_;
v___y_5969_ = v___y_5983_;
v___y_5970_ = v___y_5984_;
v___y_5971_ = v___x_5988_;
goto v___jp_5964_;
}
}
v___jp_5989_:
{
uint64_t v_position_6000_; uint8_t v___x_6001_; 
v_position_6000_ = lean_uint64_add(v___y_5999_, v___y_5994_);
v___x_6001_ = lean_uint64_dec_lt(v_position_6000_, v___y_5996_);
if (v___x_6001_ == 0)
{
uint64_t v___x_6002_; uint8_t v___x_6003_; 
v___x_6002_ = 23ULL;
v___x_6003_ = lean_uint64_dec_lt(v___y_5999_, v___x_6002_);
if (v___x_6003_ == 0)
{
uint64_t v___x_6004_; uint8_t v___x_6005_; 
v___x_6004_ = lean_uint64_sub(v___y_5999_, v___x_6002_);
v___x_6005_ = lean_uint64_dec_eq(v___x_6004_, v___y_5990_);
if (v___x_6005_ == 0)
{
uint64_t v___x_6006_; uint8_t v___x_6007_; 
v___x_6006_ = 64ULL;
v___x_6007_ = lean_uint64_dec_lt(v___x_6004_, v___x_6006_);
if (v___x_6007_ == 0)
{
uint8_t v___x_6008_; 
v___x_6008_ = lean_uint64_dec_eq(v___x_6004_, v___x_6006_);
if (v___x_6008_ == 0)
{
lean_dec(v___y_5991_);
v___y_5979_ = v___y_5990_;
v___y_5980_ = v___y_5992_;
v___y_5981_ = v___y_5995_;
v___y_5982_ = v_position_6000_;
v___y_5983_ = v___y_5997_;
v___y_5984_ = v___y_5998_;
v___y_5985_ = v___y_5990_;
goto v___jp_5978_;
}
else
{
uint64_t v___x_6009_; uint64_t v___x_6010_; uint8_t v___x_6011_; 
v___x_6009_ = 9223372036854775808ULL;
v___x_6010_ = lean_unbox_uint64(v___y_5991_);
lean_dec(v___y_5991_);
v___x_6011_ = lean_uint64_dec_lt(v___x_6009_, v___x_6010_);
if (v___x_6011_ == 0)
{
v___y_5979_ = v___y_5990_;
v___y_5980_ = v___y_5992_;
v___y_5981_ = v___y_5995_;
v___y_5982_ = v_position_6000_;
v___y_5983_ = v___y_5997_;
v___y_5984_ = v___y_5998_;
v___y_5985_ = v___y_5990_;
goto v___jp_5978_;
}
else
{
v___y_5979_ = v___y_5990_;
v___y_5980_ = v___y_5992_;
v___y_5981_ = v___y_5995_;
v___y_5982_ = v_position_6000_;
v___y_5983_ = v___y_5997_;
v___y_5984_ = v___y_5998_;
v___y_5985_ = v___y_5995_;
goto v___jp_5978_;
}
}
}
else
{
uint64_t v___x_6012_; uint64_t v_quotient_6013_; uint64_t v___x_6014_; uint64_t v___x_6015_; uint64_t v___x_6016_; uint64_t v_remainder_6017_; uint64_t v___x_6018_; uint64_t v_half_6019_; uint8_t v___x_6020_; 
v___x_6012_ = lean_unbox_uint64(v___y_5991_);
v_quotient_6013_ = lean_uint64_shift_right(v___x_6012_, v___x_6004_);
v___x_6014_ = lean_uint64_shift_left(v___y_5995_, v___x_6004_);
v___x_6015_ = lean_uint64_sub(v___x_6014_, v___y_5995_);
v___x_6016_ = lean_unbox_uint64(v___y_5991_);
lean_dec(v___y_5991_);
v_remainder_6017_ = lean_uint64_land(v___x_6016_, v___x_6015_);
v___x_6018_ = lean_uint64_sub(v___x_6004_, v___y_5995_);
v_half_6019_ = lean_uint64_shift_left(v___y_5995_, v___x_6018_);
v___x_6020_ = lean_uint64_dec_lt(v_remainder_6017_, v_half_6019_);
if (v___x_6020_ == 0)
{
uint8_t v___x_6021_; 
v___x_6021_ = lean_uint64_dec_lt(v_half_6019_, v_remainder_6017_);
if (v___x_6021_ == 0)
{
uint64_t v___x_6022_; uint8_t v___x_6023_; 
v___x_6022_ = lean_uint64_land(v_quotient_6013_, v___y_5995_);
v___x_6023_ = lean_uint64_dec_eq(v___x_6022_, v___y_5990_);
if (v___x_6023_ == 0)
{
uint64_t v___x_6024_; 
v___x_6024_ = lean_uint64_add(v_quotient_6013_, v___y_5995_);
v___y_5979_ = v___y_5990_;
v___y_5980_ = v___y_5992_;
v___y_5981_ = v___y_5995_;
v___y_5982_ = v_position_6000_;
v___y_5983_ = v___y_5997_;
v___y_5984_ = v___y_5998_;
v___y_5985_ = v___x_6024_;
goto v___jp_5978_;
}
else
{
v___y_5979_ = v___y_5990_;
v___y_5980_ = v___y_5992_;
v___y_5981_ = v___y_5995_;
v___y_5982_ = v_position_6000_;
v___y_5983_ = v___y_5997_;
v___y_5984_ = v___y_5998_;
v___y_5985_ = v_quotient_6013_;
goto v___jp_5978_;
}
}
else
{
uint64_t v___x_6025_; 
v___x_6025_ = lean_uint64_add(v_quotient_6013_, v___y_5995_);
v___y_5979_ = v___y_5990_;
v___y_5980_ = v___y_5992_;
v___y_5981_ = v___y_5995_;
v___y_5982_ = v_position_6000_;
v___y_5983_ = v___y_5997_;
v___y_5984_ = v___y_5998_;
v___y_5985_ = v___x_6025_;
goto v___jp_5978_;
}
}
else
{
v___y_5979_ = v___y_5990_;
v___y_5980_ = v___y_5992_;
v___y_5981_ = v___y_5995_;
v___y_5982_ = v_position_6000_;
v___y_5983_ = v___y_5997_;
v___y_5984_ = v___y_5998_;
v___y_5985_ = v_quotient_6013_;
goto v___jp_5978_;
}
}
}
else
{
uint64_t v___x_6026_; 
v___x_6026_ = lean_unbox_uint64(v___y_5991_);
lean_dec(v___y_5991_);
v___y_5979_ = v___y_5990_;
v___y_5980_ = v___y_5992_;
v___y_5981_ = v___y_5995_;
v___y_5982_ = v_position_6000_;
v___y_5983_ = v___y_5997_;
v___y_5984_ = v___y_5998_;
v___y_5985_ = v___x_6026_;
goto v___jp_5978_;
}
}
else
{
uint64_t v___x_6027_; uint64_t v___x_6028_; uint64_t v___x_6029_; 
v___x_6027_ = lean_uint64_sub(v___x_6002_, v___y_5999_);
v___x_6028_ = lean_unbox_uint64(v___y_5991_);
lean_dec(v___y_5991_);
v___x_6029_ = lean_uint64_shift_left(v___x_6028_, v___x_6027_);
v___y_5979_ = v___y_5990_;
v___y_5980_ = v___y_5992_;
v___y_5981_ = v___y_5995_;
v___y_5982_ = v_position_6000_;
v___y_5983_ = v___y_5997_;
v___y_5984_ = v___y_5998_;
v___y_5985_ = v___x_6029_;
goto v___jp_5978_;
}
}
else
{
uint8_t v___x_6030_; 
v___x_6030_ = lean_uint64_dec_lt(v___y_5994_, v___y_5993_);
if (v___x_6030_ == 0)
{
uint64_t v___x_6031_; uint64_t v___x_6032_; uint64_t v___x_6033_; 
v___x_6031_ = lean_uint64_sub(v___y_5994_, v___y_5993_);
v___x_6032_ = lean_unbox_uint64(v___y_5991_);
lean_dec(v___y_5991_);
v___x_6033_ = lean_uint64_shift_left(v___x_6032_, v___x_6031_);
v___y_5912_ = v___y_5990_;
v___y_5913_ = v___y_5998_;
v___y_5914_ = v___x_6033_;
goto v___jp_5911_;
}
else
{
uint64_t v___x_6034_; uint8_t v___x_6035_; 
v___x_6034_ = lean_uint64_sub(v___y_5993_, v___y_5994_);
v___x_6035_ = lean_uint64_dec_eq(v___x_6034_, v___y_5990_);
if (v___x_6035_ == 0)
{
uint64_t v___x_6036_; uint8_t v___x_6037_; 
v___x_6036_ = 64ULL;
v___x_6037_ = lean_uint64_dec_lt(v___x_6034_, v___x_6036_);
if (v___x_6037_ == 0)
{
uint8_t v___x_6038_; 
v___x_6038_ = lean_uint64_dec_eq(v___x_6034_, v___x_6036_);
if (v___x_6038_ == 0)
{
lean_dec(v___y_5991_);
v___y_5912_ = v___y_5990_;
v___y_5913_ = v___y_5998_;
v___y_5914_ = v___y_5990_;
goto v___jp_5911_;
}
else
{
uint64_t v___x_6039_; uint64_t v___x_6040_; uint8_t v___x_6041_; 
v___x_6039_ = 9223372036854775808ULL;
v___x_6040_ = lean_unbox_uint64(v___y_5991_);
lean_dec(v___y_5991_);
v___x_6041_ = lean_uint64_dec_lt(v___x_6039_, v___x_6040_);
if (v___x_6041_ == 0)
{
v___y_5912_ = v___y_5990_;
v___y_5913_ = v___y_5998_;
v___y_5914_ = v___y_5990_;
goto v___jp_5911_;
}
else
{
v___y_5912_ = v___y_5990_;
v___y_5913_ = v___y_5998_;
v___y_5914_ = v___y_5995_;
goto v___jp_5911_;
}
}
}
else
{
uint64_t v___x_6042_; uint64_t v_quotient_6043_; uint64_t v___x_6044_; uint64_t v___x_6045_; uint64_t v___x_6046_; uint64_t v_remainder_6047_; uint64_t v___x_6048_; uint64_t v_half_6049_; uint8_t v___x_6050_; 
v___x_6042_ = lean_unbox_uint64(v___y_5991_);
v_quotient_6043_ = lean_uint64_shift_right(v___x_6042_, v___x_6034_);
v___x_6044_ = lean_uint64_shift_left(v___y_5995_, v___x_6034_);
v___x_6045_ = lean_uint64_sub(v___x_6044_, v___y_5995_);
v___x_6046_ = lean_unbox_uint64(v___y_5991_);
lean_dec(v___y_5991_);
v_remainder_6047_ = lean_uint64_land(v___x_6046_, v___x_6045_);
v___x_6048_ = lean_uint64_sub(v___x_6034_, v___y_5995_);
v_half_6049_ = lean_uint64_shift_left(v___y_5995_, v___x_6048_);
v___x_6050_ = lean_uint64_dec_lt(v_remainder_6047_, v_half_6049_);
if (v___x_6050_ == 0)
{
uint8_t v___x_6051_; 
v___x_6051_ = lean_uint64_dec_lt(v_half_6049_, v_remainder_6047_);
if (v___x_6051_ == 0)
{
uint64_t v___x_6052_; uint8_t v___x_6053_; 
v___x_6052_ = lean_uint64_land(v_quotient_6043_, v___y_5995_);
v___x_6053_ = lean_uint64_dec_eq(v___x_6052_, v___y_5990_);
if (v___x_6053_ == 0)
{
uint64_t v___x_6054_; 
v___x_6054_ = lean_uint64_add(v_quotient_6043_, v___y_5995_);
v___y_5912_ = v___y_5990_;
v___y_5913_ = v___y_5998_;
v___y_5914_ = v___x_6054_;
goto v___jp_5911_;
}
else
{
v___y_5912_ = v___y_5990_;
v___y_5913_ = v___y_5998_;
v___y_5914_ = v_quotient_6043_;
goto v___jp_5911_;
}
}
else
{
uint64_t v___x_6055_; 
v___x_6055_ = lean_uint64_add(v_quotient_6043_, v___y_5995_);
v___y_5912_ = v___y_5990_;
v___y_5913_ = v___y_5998_;
v___y_5914_ = v___x_6055_;
goto v___jp_5911_;
}
}
else
{
v___y_5912_ = v___y_5990_;
v___y_5913_ = v___y_5998_;
v___y_5914_ = v_quotient_6043_;
goto v___jp_5911_;
}
}
}
else
{
uint64_t v___x_6056_; 
v___x_6056_ = lean_unbox_uint64(v___y_5991_);
lean_dec(v___y_5991_);
v___y_5912_ = v___y_5990_;
v___y_5913_ = v___y_5998_;
v___y_5914_ = v___x_6056_;
goto v___jp_5911_;
}
}
}
}
v___jp_6057_:
{
uint64_t v___x_6069_; uint8_t v___x_6070_; 
v___x_6069_ = lean_uint64_shift_right(v___y_6059_, v___y_6064_);
v___x_6070_ = lean_uint64_dec_eq(v___x_6069_, v___y_6058_);
if (v___x_6070_ == 0)
{
uint64_t v___x_6071_; 
v___x_6071_ = lean_uint64_add(v___y_6068_, v___y_6064_);
v___y_5990_ = v___y_6058_;
v___y_5991_ = v___y_6060_;
v___y_5992_ = v___y_6061_;
v___y_5993_ = v___y_6063_;
v___y_5994_ = v___y_6062_;
v___y_5995_ = v___y_6064_;
v___y_5996_ = v___y_6065_;
v___y_5997_ = v___y_6066_;
v___y_5998_ = v___y_6067_;
v___y_5999_ = v___x_6071_;
goto v___jp_5989_;
}
else
{
v___y_5990_ = v___y_6058_;
v___y_5991_ = v___y_6060_;
v___y_5992_ = v___y_6061_;
v___y_5993_ = v___y_6063_;
v___y_5994_ = v___y_6062_;
v___y_5995_ = v___y_6064_;
v___y_5996_ = v___y_6065_;
v___y_5997_ = v___y_6066_;
v___y_5998_ = v___y_6067_;
v___y_5999_ = v___y_6068_;
goto v___jp_5989_;
}
}
v___jp_6072_:
{
uint64_t v___x_6086_; uint8_t v___x_6087_; 
v___x_6086_ = lean_uint64_shift_right(v___y_6078_, v___y_6082_);
v___x_6087_ = lean_uint64_dec_eq(v___x_6086_, v___y_6073_);
if (v___x_6087_ == 0)
{
uint64_t v___x_6088_; 
v___x_6088_ = lean_uint64_add(v___y_6080_, v___y_6082_);
v___y_6058_ = v___y_6073_;
v___y_6059_ = v___y_6085_;
v___y_6060_ = v___y_6074_;
v___y_6061_ = v___y_6075_;
v___y_6062_ = v___y_6077_;
v___y_6063_ = v___y_6076_;
v___y_6064_ = v___y_6079_;
v___y_6065_ = v___y_6081_;
v___y_6066_ = v___y_6083_;
v___y_6067_ = v___y_6084_;
v___y_6068_ = v___x_6088_;
goto v___jp_6057_;
}
else
{
v___y_6058_ = v___y_6073_;
v___y_6059_ = v___y_6085_;
v___y_6060_ = v___y_6074_;
v___y_6061_ = v___y_6075_;
v___y_6062_ = v___y_6077_;
v___y_6063_ = v___y_6076_;
v___y_6064_ = v___y_6079_;
v___y_6065_ = v___y_6081_;
v___y_6066_ = v___y_6083_;
v___y_6067_ = v___y_6084_;
v___y_6068_ = v___y_6080_;
goto v___jp_6057_;
}
}
v___jp_6089_:
{
uint64_t v___x_6101_; uint64_t v___x_6102_; uint8_t v___x_6103_; 
v___x_6101_ = 2ULL;
v___x_6102_ = lean_uint64_shift_right(v___y_6095_, v___x_6101_);
v___x_6103_ = lean_uint64_dec_eq(v___x_6102_, v___y_6090_);
if (v___x_6103_ == 0)
{
v___y_6073_ = v___y_6090_;
v___y_6074_ = v___y_6091_;
v___y_6075_ = v___y_6092_;
v___y_6076_ = v___y_6094_;
v___y_6077_ = v___y_6093_;
v___y_6078_ = v___y_6095_;
v___y_6079_ = v___y_6096_;
v___y_6080_ = v___y_6100_;
v___y_6081_ = v___y_6097_;
v___y_6082_ = v___x_6101_;
v___y_6083_ = v___y_6098_;
v___y_6084_ = v___y_6099_;
v___y_6085_ = v___x_6102_;
goto v___jp_6072_;
}
else
{
v___y_6073_ = v___y_6090_;
v___y_6074_ = v___y_6091_;
v___y_6075_ = v___y_6092_;
v___y_6076_ = v___y_6094_;
v___y_6077_ = v___y_6093_;
v___y_6078_ = v___y_6095_;
v___y_6079_ = v___y_6096_;
v___y_6080_ = v___y_6100_;
v___y_6081_ = v___y_6097_;
v___y_6082_ = v___x_6101_;
v___y_6083_ = v___y_6098_;
v___y_6084_ = v___y_6099_;
v___y_6085_ = v___y_6095_;
goto v___jp_6072_;
}
}
v___jp_6104_:
{
uint64_t v___x_6118_; uint8_t v___x_6119_; 
v___x_6118_ = lean_uint64_shift_right(v___y_6109_, v___y_6107_);
v___x_6119_ = lean_uint64_dec_eq(v___x_6118_, v___y_6105_);
if (v___x_6119_ == 0)
{
uint64_t v___x_6120_; 
v___x_6120_ = lean_uint64_add(v___y_6116_, v___y_6107_);
v___y_6090_ = v___y_6105_;
v___y_6091_ = v___y_6106_;
v___y_6092_ = v___y_6108_;
v___y_6093_ = v___y_6111_;
v___y_6094_ = v___y_6110_;
v___y_6095_ = v___y_6117_;
v___y_6096_ = v___y_6112_;
v___y_6097_ = v___y_6113_;
v___y_6098_ = v___y_6114_;
v___y_6099_ = v___y_6115_;
v___y_6100_ = v___x_6120_;
goto v___jp_6089_;
}
else
{
v___y_6090_ = v___y_6105_;
v___y_6091_ = v___y_6106_;
v___y_6092_ = v___y_6108_;
v___y_6093_ = v___y_6111_;
v___y_6094_ = v___y_6110_;
v___y_6095_ = v___y_6117_;
v___y_6096_ = v___y_6112_;
v___y_6097_ = v___y_6113_;
v___y_6098_ = v___y_6114_;
v___y_6099_ = v___y_6115_;
v___y_6100_ = v___y_6116_;
goto v___jp_6089_;
}
}
v___jp_6121_:
{
uint64_t v___x_6133_; uint64_t v___x_6134_; uint8_t v___x_6135_; 
v___x_6133_ = 4ULL;
v___x_6134_ = lean_uint64_shift_right(v___y_6127_, v___x_6133_);
v___x_6135_ = lean_uint64_dec_eq(v___x_6134_, v___y_6122_);
if (v___x_6135_ == 0)
{
v___y_6105_ = v___y_6122_;
v___y_6106_ = v___y_6123_;
v___y_6107_ = v___x_6133_;
v___y_6108_ = v___y_6124_;
v___y_6109_ = v___y_6127_;
v___y_6110_ = v___y_6126_;
v___y_6111_ = v___y_6125_;
v___y_6112_ = v___y_6128_;
v___y_6113_ = v___y_6129_;
v___y_6114_ = v___y_6130_;
v___y_6115_ = v___y_6131_;
v___y_6116_ = v___y_6132_;
v___y_6117_ = v___x_6134_;
goto v___jp_6104_;
}
else
{
v___y_6105_ = v___y_6122_;
v___y_6106_ = v___y_6123_;
v___y_6107_ = v___x_6133_;
v___y_6108_ = v___y_6124_;
v___y_6109_ = v___y_6127_;
v___y_6110_ = v___y_6126_;
v___y_6111_ = v___y_6125_;
v___y_6112_ = v___y_6128_;
v___y_6113_ = v___y_6129_;
v___y_6114_ = v___y_6130_;
v___y_6115_ = v___y_6131_;
v___y_6116_ = v___y_6132_;
v___y_6117_ = v___y_6127_;
goto v___jp_6104_;
}
}
v___jp_6136_:
{
uint64_t v___x_6150_; uint8_t v___x_6151_; 
v___x_6150_ = lean_uint64_shift_right(v___y_6144_, v___y_6143_);
v___x_6151_ = lean_uint64_dec_eq(v___x_6150_, v___y_6137_);
if (v___x_6151_ == 0)
{
uint64_t v___x_6152_; 
v___x_6152_ = lean_uint64_add(v___y_6142_, v___y_6143_);
v___y_6122_ = v___y_6137_;
v___y_6123_ = v___y_6138_;
v___y_6124_ = v___y_6139_;
v___y_6125_ = v___y_6141_;
v___y_6126_ = v___y_6140_;
v___y_6127_ = v___y_6149_;
v___y_6128_ = v___y_6145_;
v___y_6129_ = v___y_6146_;
v___y_6130_ = v___y_6147_;
v___y_6131_ = v___y_6148_;
v___y_6132_ = v___x_6152_;
goto v___jp_6121_;
}
else
{
v___y_6122_ = v___y_6137_;
v___y_6123_ = v___y_6138_;
v___y_6124_ = v___y_6139_;
v___y_6125_ = v___y_6141_;
v___y_6126_ = v___y_6140_;
v___y_6127_ = v___y_6149_;
v___y_6128_ = v___y_6145_;
v___y_6129_ = v___y_6146_;
v___y_6130_ = v___y_6147_;
v___y_6131_ = v___y_6148_;
v___y_6132_ = v___y_6142_;
goto v___jp_6121_;
}
}
v___jp_6153_:
{
uint64_t v___x_6165_; uint64_t v___x_6166_; uint8_t v___x_6167_; 
v___x_6165_ = 8ULL;
v___x_6166_ = lean_uint64_shift_right(v___y_6160_, v___x_6165_);
v___x_6167_ = lean_uint64_dec_eq(v___x_6166_, v___y_6154_);
if (v___x_6167_ == 0)
{
v___y_6137_ = v___y_6154_;
v___y_6138_ = v___y_6155_;
v___y_6139_ = v___y_6156_;
v___y_6140_ = v___y_6158_;
v___y_6141_ = v___y_6157_;
v___y_6142_ = v___y_6164_;
v___y_6143_ = v___x_6165_;
v___y_6144_ = v___y_6160_;
v___y_6145_ = v___y_6159_;
v___y_6146_ = v___y_6161_;
v___y_6147_ = v___y_6162_;
v___y_6148_ = v___y_6163_;
v___y_6149_ = v___x_6166_;
goto v___jp_6136_;
}
else
{
v___y_6137_ = v___y_6154_;
v___y_6138_ = v___y_6155_;
v___y_6139_ = v___y_6156_;
v___y_6140_ = v___y_6158_;
v___y_6141_ = v___y_6157_;
v___y_6142_ = v___y_6164_;
v___y_6143_ = v___x_6165_;
v___y_6144_ = v___y_6160_;
v___y_6145_ = v___y_6159_;
v___y_6146_ = v___y_6161_;
v___y_6147_ = v___y_6162_;
v___y_6148_ = v___y_6163_;
v___y_6149_ = v___y_6160_;
goto v___jp_6136_;
}
}
v___jp_6168_:
{
uint64_t v___x_6182_; uint8_t v___x_6183_; 
v___x_6182_ = lean_uint64_shift_right(v___y_6180_, v___y_6171_);
v___x_6183_ = lean_uint64_dec_eq(v___x_6182_, v___y_6169_);
if (v___x_6183_ == 0)
{
uint64_t v___x_6184_; 
v___x_6184_ = lean_uint64_add(v___y_6177_, v___y_6171_);
v___y_6154_ = v___y_6169_;
v___y_6155_ = v___y_6170_;
v___y_6156_ = v___y_6172_;
v___y_6157_ = v___y_6174_;
v___y_6158_ = v___y_6173_;
v___y_6159_ = v___y_6175_;
v___y_6160_ = v___y_6181_;
v___y_6161_ = v___y_6176_;
v___y_6162_ = v___y_6178_;
v___y_6163_ = v___y_6179_;
v___y_6164_ = v___x_6184_;
goto v___jp_6153_;
}
else
{
v___y_6154_ = v___y_6169_;
v___y_6155_ = v___y_6170_;
v___y_6156_ = v___y_6172_;
v___y_6157_ = v___y_6174_;
v___y_6158_ = v___y_6173_;
v___y_6159_ = v___y_6175_;
v___y_6160_ = v___y_6181_;
v___y_6161_ = v___y_6176_;
v___y_6162_ = v___y_6178_;
v___y_6163_ = v___y_6179_;
v___y_6164_ = v___y_6177_;
goto v___jp_6153_;
}
}
v___jp_6185_:
{
uint64_t v___x_6197_; uint64_t v___x_6198_; uint8_t v___x_6199_; 
v___x_6197_ = 16ULL;
v___x_6198_ = lean_uint64_shift_right(v___y_6195_, v___x_6197_);
v___x_6199_ = lean_uint64_dec_eq(v___x_6198_, v___y_6186_);
if (v___x_6199_ == 0)
{
v___y_6169_ = v___y_6186_;
v___y_6170_ = v___y_6187_;
v___y_6171_ = v___x_6197_;
v___y_6172_ = v___y_6188_;
v___y_6173_ = v___y_6190_;
v___y_6174_ = v___y_6189_;
v___y_6175_ = v___y_6191_;
v___y_6176_ = v___y_6192_;
v___y_6177_ = v___y_6196_;
v___y_6178_ = v___y_6193_;
v___y_6179_ = v___y_6194_;
v___y_6180_ = v___y_6195_;
v___y_6181_ = v___x_6198_;
goto v___jp_6168_;
}
else
{
v___y_6169_ = v___y_6186_;
v___y_6170_ = v___y_6187_;
v___y_6171_ = v___x_6197_;
v___y_6172_ = v___y_6188_;
v___y_6173_ = v___y_6190_;
v___y_6174_ = v___y_6189_;
v___y_6175_ = v___y_6191_;
v___y_6176_ = v___y_6192_;
v___y_6177_ = v___y_6196_;
v___y_6178_ = v___y_6193_;
v___y_6179_ = v___y_6194_;
v___y_6180_ = v___y_6195_;
v___y_6181_ = v___y_6195_;
goto v___jp_6168_;
}
}
v___jp_6200_:
{
uint64_t v___x_6212_; uint64_t v___x_6213_; uint8_t v___x_6214_; 
v___x_6212_ = lean_unbox_uint64(v___y_6202_);
v___x_6213_ = lean_uint64_shift_right(v___x_6212_, v___y_6208_);
v___x_6214_ = lean_uint64_dec_eq(v___x_6213_, v___y_6201_);
if (v___x_6214_ == 0)
{
v___y_6186_ = v___y_6201_;
v___y_6187_ = v___y_6202_;
v___y_6188_ = v___y_6203_;
v___y_6189_ = v___y_6205_;
v___y_6190_ = v___y_6204_;
v___y_6191_ = v___y_6206_;
v___y_6192_ = v___y_6207_;
v___y_6193_ = v___y_6209_;
v___y_6194_ = v___y_6210_;
v___y_6195_ = v___y_6211_;
v___y_6196_ = v___y_6208_;
goto v___jp_6185_;
}
else
{
v___y_6186_ = v___y_6201_;
v___y_6187_ = v___y_6202_;
v___y_6188_ = v___y_6203_;
v___y_6189_ = v___y_6205_;
v___y_6190_ = v___y_6204_;
v___y_6191_ = v___y_6206_;
v___y_6192_ = v___y_6207_;
v___y_6193_ = v___y_6209_;
v___y_6194_ = v___y_6210_;
v___y_6195_ = v___y_6211_;
v___y_6196_ = v___y_6201_;
goto v___jp_6185_;
}
}
v___jp_6215_:
{
uint64_t v___x_6224_; uint64_t v___x_6225_; uint8_t v___x_6226_; 
v___x_6224_ = 0ULL;
v___x_6225_ = lean_unbox_uint64(v_snd_6223_);
v___x_6226_ = lean_uint64_dec_eq(v___x_6225_, v___x_6224_);
if (v___x_6226_ == 0)
{
uint64_t v___x_6227_; uint64_t v___x_6228_; uint64_t v___x_6229_; uint64_t v___x_6230_; uint8_t v___x_6231_; 
v___x_6227_ = lean_uint64_add(v___y_6218_, v___y_6217_);
v___x_6228_ = 32ULL;
v___x_6229_ = lean_unbox_uint64(v_snd_6223_);
v___x_6230_ = lean_uint64_shift_right(v___x_6229_, v___x_6228_);
v___x_6231_ = lean_uint64_dec_eq(v___x_6230_, v___x_6224_);
if (v___x_6231_ == 0)
{
v___y_6201_ = v___x_6224_;
v___y_6202_ = v_snd_6223_;
v___y_6203_ = v___y_6216_;
v___y_6204_ = v___y_6217_;
v___y_6205_ = v___x_6227_;
v___y_6206_ = v___y_6219_;
v___y_6207_ = v___y_6220_;
v___y_6208_ = v___x_6228_;
v___y_6209_ = v___y_6221_;
v___y_6210_ = v_fst_6222_;
v___y_6211_ = v___x_6230_;
goto v___jp_6200_;
}
else
{
uint64_t v___x_6232_; 
v___x_6232_ = lean_unbox_uint64(v_snd_6223_);
v___y_6201_ = v___x_6224_;
v___y_6202_ = v_snd_6223_;
v___y_6203_ = v___y_6216_;
v___y_6204_ = v___y_6217_;
v___y_6205_ = v___x_6227_;
v___y_6206_ = v___y_6219_;
v___y_6207_ = v___y_6220_;
v___y_6208_ = v___x_6228_;
v___y_6209_ = v___y_6221_;
v___y_6210_ = v_fst_6222_;
v___y_6211_ = v___x_6232_;
goto v___jp_6200_;
}
}
else
{
uint8_t v___x_6233_; 
lean_dec(v_snd_6223_);
v___x_6233_ = lean_unbox(v_fst_6222_);
lean_dec(v_fst_6222_);
if (v___x_6233_ == 0)
{
uint32_t v___x_6234_; 
v___x_6234_ = 0;
return v___x_6234_;
}
else
{
uint32_t v___x_6235_; 
v___x_6235_ = 2147483648;
return v___x_6235_;
}
}
}
v___jp_6236_:
{
uint32_t v___x_6239_; uint32_t v___x_6240_; uint32_t v___x_6241_; 
v___x_6239_ = 8388607;
v___x_6240_ = lean_uint32_land(v___y_6237_, v___x_6239_);
v___x_6241_ = lean_uint32_lor(v___y_6238_, v___x_6240_);
return v___x_6241_;
}
v___jp_6242_:
{
uint8_t v___x_6246_; 
v___x_6246_ = lean_uint64_dec_eq(v___y_6245_, v___y_6244_);
if (v___x_6246_ == 0)
{
uint64_t v___x_6247_; uint8_t v___x_6248_; 
v___x_6247_ = 8388608ULL;
v___x_6248_ = lean_uint64_dec_eq(v___y_6245_, v___x_6247_);
if (v___x_6248_ == 0)
{
uint32_t v___x_6249_; uint8_t v___x_6250_; 
v___x_6249_ = lean_uint64_to_uint32(v___y_6245_);
v___x_6250_ = lean_unbox(v___y_6243_);
lean_dec(v___y_6243_);
if (v___x_6250_ == 0)
{
uint32_t v___x_6251_; 
v___x_6251_ = 0;
v___y_6237_ = v___x_6249_;
v___y_6238_ = v___x_6251_;
goto v___jp_6236_;
}
else
{
uint32_t v___x_6252_; 
v___x_6252_ = 2147483648;
v___y_6237_ = v___x_6249_;
v___y_6238_ = v___x_6252_;
goto v___jp_6236_;
}
}
else
{
uint8_t v___x_6253_; 
v___x_6253_ = lean_unbox(v___y_6243_);
lean_dec(v___y_6243_);
if (v___x_6253_ == 0)
{
uint32_t v___x_6254_; 
v___x_6254_ = 0;
v___y_5083_ = v___x_6254_;
goto v___jp_5082_;
}
else
{
uint32_t v___x_6255_; 
v___x_6255_ = 2147483648;
v___y_5083_ = v___x_6255_;
goto v___jp_5082_;
}
}
}
else
{
uint8_t v___x_6256_; 
v___x_6256_ = lean_unbox(v___y_6243_);
lean_dec(v___y_6243_);
if (v___x_6256_ == 0)
{
uint32_t v___x_6257_; 
v___x_6257_ = 0;
return v___x_6257_;
}
else
{
uint32_t v___x_6258_; 
v___x_6258_ = 2147483648;
return v___x_6258_;
}
}
}
v___jp_6259_:
{
uint32_t v___x_6265_; uint32_t v___x_6266_; uint32_t v___x_6267_; uint32_t v___x_6268_; uint32_t v___x_6269_; uint32_t v___x_6270_; 
v___x_6265_ = lean_uint32_land(v___y_6262_, v___y_6260_);
v___x_6266_ = lean_uint32_shift_left(v___x_6265_, v___y_6263_);
v___x_6267_ = lean_uint32_lor(v___y_6264_, v___x_6266_);
v___x_6268_ = 8388607;
v___x_6269_ = lean_uint32_land(v___y_6261_, v___x_6268_);
v___x_6270_ = lean_uint32_lor(v___x_6267_, v___x_6269_);
return v___x_6270_;
}
v___jp_6271_:
{
uint8_t v___x_6277_; 
v___x_6277_ = lean_unbox(v___y_6272_);
lean_dec(v___y_6272_);
if (v___x_6277_ == 0)
{
uint32_t v___x_6278_; 
v___x_6278_ = 0;
v___y_6260_ = v___y_6273_;
v___y_6261_ = v___y_6276_;
v___y_6262_ = v___y_6274_;
v___y_6263_ = v___y_6275_;
v___y_6264_ = v___x_6278_;
goto v___jp_6259_;
}
else
{
uint32_t v___x_6279_; 
v___x_6279_ = 2147483648;
v___y_6260_ = v___y_6273_;
v___y_6261_ = v___y_6276_;
v___y_6262_ = v___y_6274_;
v___y_6263_ = v___y_6275_;
v___y_6264_ = v___x_6279_;
goto v___jp_6259_;
}
}
v___jp_6280_:
{
uint64_t v___x_6287_; uint64_t v_encodedExponent_6288_; uint32_t v___x_6289_; uint64_t v___x_6290_; uint8_t v___x_6291_; 
v___x_6287_ = 171ULL;
v_encodedExponent_6288_ = lean_uint64_sub(v___y_6283_, v___x_6287_);
v___x_6289_ = lean_uint64_to_uint32(v_encodedExponent_6288_);
v___x_6290_ = 8388608ULL;
v___x_6291_ = lean_uint64_dec_lt(v___y_6286_, v___x_6290_);
if (v___x_6291_ == 0)
{
uint64_t v___x_6292_; uint32_t v___x_6293_; 
v___x_6292_ = lean_uint64_sub(v___y_6286_, v___x_6290_);
v___x_6293_ = lean_uint64_to_uint32(v___x_6292_);
v___y_6272_ = v___y_6281_;
v___y_6273_ = v___y_6282_;
v___y_6274_ = v___x_6289_;
v___y_6275_ = v___y_6285_;
v___y_6276_ = v___x_6293_;
goto v___jp_6271_;
}
else
{
uint32_t v___x_6294_; 
v___x_6294_ = lean_uint64_to_uint32(v___y_6284_);
v___y_6272_ = v___y_6281_;
v___y_6273_ = v___y_6282_;
v___y_6274_ = v___x_6289_;
v___y_6275_ = v___y_6285_;
v___y_6276_ = v___x_6294_;
goto v___jp_6271_;
}
}
v___jp_6295_:
{
uint64_t v___x_6303_; uint8_t v___x_6304_; 
v___x_6303_ = 425ULL;
v___x_6304_ = lean_uint64_dec_lt(v___x_6303_, v___y_6302_);
if (v___x_6304_ == 0)
{
if (v___y_6299_ == 0)
{
v___y_6281_ = v___y_6296_;
v___y_6282_ = v___y_6297_;
v___y_6283_ = v___y_6302_;
v___y_6284_ = v___y_6301_;
v___y_6285_ = v___y_6300_;
v___y_6286_ = v___y_6298_;
goto v___jp_6280_;
}
else
{
uint64_t v___x_6305_; 
v___x_6305_ = 8388608ULL;
v___y_6281_ = v___y_6296_;
v___y_6282_ = v___y_6297_;
v___y_6283_ = v___y_6302_;
v___y_6284_ = v___y_6301_;
v___y_6285_ = v___y_6300_;
v___y_6286_ = v___x_6305_;
goto v___jp_6280_;
}
}
else
{
uint8_t v___x_6306_; 
v___x_6306_ = lean_unbox(v___y_6296_);
lean_dec(v___y_6296_);
if (v___x_6306_ == 0)
{
uint32_t v___x_6307_; 
v___x_6307_ = 2139095040;
return v___x_6307_;
}
else
{
uint32_t v___x_6308_; 
v___x_6308_ = 4286578688;
return v___x_6308_;
}
}
}
v___jp_6309_:
{
uint64_t v___x_6317_; uint8_t v_carry_6318_; 
v___x_6317_ = 16777216ULL;
v_carry_6318_ = lean_uint64_dec_eq(v___y_6316_, v___x_6317_);
if (v_carry_6318_ == 0)
{
v___y_6296_ = v___y_6310_;
v___y_6297_ = v___y_6311_;
v___y_6298_ = v___y_6316_;
v___y_6299_ = v_carry_6318_;
v___y_6300_ = v___y_6315_;
v___y_6301_ = v___y_6314_;
v___y_6302_ = v___y_6312_;
goto v___jp_6295_;
}
else
{
uint64_t v___x_6319_; 
v___x_6319_ = lean_uint64_add(v___y_6312_, v___y_6313_);
v___y_6296_ = v___y_6310_;
v___y_6297_ = v___y_6311_;
v___y_6298_ = v___y_6316_;
v___y_6299_ = v_carry_6318_;
v___y_6300_ = v___y_6315_;
v___y_6301_ = v___y_6314_;
v___y_6302_ = v___x_6319_;
goto v___jp_6295_;
}
}
v___jp_6320_:
{
uint64_t v_position_6331_; uint8_t v___x_6332_; 
v_position_6331_ = lean_uint64_add(v___y_6330_, v___y_6326_);
v___x_6332_ = lean_uint64_dec_lt(v_position_6331_, v___y_6325_);
if (v___x_6332_ == 0)
{
uint64_t v___x_6333_; uint8_t v___x_6334_; 
v___x_6333_ = 23ULL;
v___x_6334_ = lean_uint64_dec_lt(v___y_6330_, v___x_6333_);
if (v___x_6334_ == 0)
{
uint64_t v___x_6335_; uint8_t v___x_6336_; 
v___x_6335_ = lean_uint64_sub(v___y_6330_, v___x_6333_);
v___x_6336_ = lean_uint64_dec_eq(v___x_6335_, v___y_6329_);
if (v___x_6336_ == 0)
{
uint64_t v___x_6337_; uint8_t v___x_6338_; 
v___x_6337_ = 64ULL;
v___x_6338_ = lean_uint64_dec_lt(v___x_6335_, v___x_6337_);
if (v___x_6338_ == 0)
{
uint8_t v___x_6339_; 
v___x_6339_ = lean_uint64_dec_eq(v___x_6335_, v___x_6337_);
if (v___x_6339_ == 0)
{
lean_dec(v___y_6327_);
v___y_6310_ = v___y_6321_;
v___y_6311_ = v___y_6322_;
v___y_6312_ = v_position_6331_;
v___y_6313_ = v___y_6324_;
v___y_6314_ = v___y_6329_;
v___y_6315_ = v___y_6328_;
v___y_6316_ = v___y_6329_;
goto v___jp_6309_;
}
else
{
uint64_t v___x_6340_; uint64_t v___x_6341_; uint8_t v___x_6342_; 
v___x_6340_ = 9223372036854775808ULL;
v___x_6341_ = lean_unbox_uint64(v___y_6327_);
lean_dec(v___y_6327_);
v___x_6342_ = lean_uint64_dec_lt(v___x_6340_, v___x_6341_);
if (v___x_6342_ == 0)
{
v___y_6310_ = v___y_6321_;
v___y_6311_ = v___y_6322_;
v___y_6312_ = v_position_6331_;
v___y_6313_ = v___y_6324_;
v___y_6314_ = v___y_6329_;
v___y_6315_ = v___y_6328_;
v___y_6316_ = v___y_6329_;
goto v___jp_6309_;
}
else
{
v___y_6310_ = v___y_6321_;
v___y_6311_ = v___y_6322_;
v___y_6312_ = v_position_6331_;
v___y_6313_ = v___y_6324_;
v___y_6314_ = v___y_6329_;
v___y_6315_ = v___y_6328_;
v___y_6316_ = v___y_6324_;
goto v___jp_6309_;
}
}
}
else
{
uint64_t v___x_6343_; uint64_t v_quotient_6344_; uint64_t v___x_6345_; uint64_t v___x_6346_; uint64_t v___x_6347_; uint64_t v_remainder_6348_; uint64_t v___x_6349_; uint64_t v_half_6350_; uint8_t v___x_6351_; 
v___x_6343_ = lean_unbox_uint64(v___y_6327_);
v_quotient_6344_ = lean_uint64_shift_right(v___x_6343_, v___x_6335_);
v___x_6345_ = lean_uint64_shift_left(v___y_6324_, v___x_6335_);
v___x_6346_ = lean_uint64_sub(v___x_6345_, v___y_6324_);
v___x_6347_ = lean_unbox_uint64(v___y_6327_);
lean_dec(v___y_6327_);
v_remainder_6348_ = lean_uint64_land(v___x_6347_, v___x_6346_);
v___x_6349_ = lean_uint64_sub(v___x_6335_, v___y_6324_);
v_half_6350_ = lean_uint64_shift_left(v___y_6324_, v___x_6349_);
v___x_6351_ = lean_uint64_dec_lt(v_remainder_6348_, v_half_6350_);
if (v___x_6351_ == 0)
{
uint8_t v___x_6352_; 
v___x_6352_ = lean_uint64_dec_lt(v_half_6350_, v_remainder_6348_);
if (v___x_6352_ == 0)
{
uint64_t v___x_6353_; uint8_t v___x_6354_; 
v___x_6353_ = lean_uint64_land(v_quotient_6344_, v___y_6324_);
v___x_6354_ = lean_uint64_dec_eq(v___x_6353_, v___y_6329_);
if (v___x_6354_ == 0)
{
uint64_t v___x_6355_; 
v___x_6355_ = lean_uint64_add(v_quotient_6344_, v___y_6324_);
v___y_6310_ = v___y_6321_;
v___y_6311_ = v___y_6322_;
v___y_6312_ = v_position_6331_;
v___y_6313_ = v___y_6324_;
v___y_6314_ = v___y_6329_;
v___y_6315_ = v___y_6328_;
v___y_6316_ = v___x_6355_;
goto v___jp_6309_;
}
else
{
v___y_6310_ = v___y_6321_;
v___y_6311_ = v___y_6322_;
v___y_6312_ = v_position_6331_;
v___y_6313_ = v___y_6324_;
v___y_6314_ = v___y_6329_;
v___y_6315_ = v___y_6328_;
v___y_6316_ = v_quotient_6344_;
goto v___jp_6309_;
}
}
else
{
uint64_t v___x_6356_; 
v___x_6356_ = lean_uint64_add(v_quotient_6344_, v___y_6324_);
v___y_6310_ = v___y_6321_;
v___y_6311_ = v___y_6322_;
v___y_6312_ = v_position_6331_;
v___y_6313_ = v___y_6324_;
v___y_6314_ = v___y_6329_;
v___y_6315_ = v___y_6328_;
v___y_6316_ = v___x_6356_;
goto v___jp_6309_;
}
}
else
{
v___y_6310_ = v___y_6321_;
v___y_6311_ = v___y_6322_;
v___y_6312_ = v_position_6331_;
v___y_6313_ = v___y_6324_;
v___y_6314_ = v___y_6329_;
v___y_6315_ = v___y_6328_;
v___y_6316_ = v_quotient_6344_;
goto v___jp_6309_;
}
}
}
else
{
uint64_t v___x_6357_; 
v___x_6357_ = lean_unbox_uint64(v___y_6327_);
lean_dec(v___y_6327_);
v___y_6310_ = v___y_6321_;
v___y_6311_ = v___y_6322_;
v___y_6312_ = v_position_6331_;
v___y_6313_ = v___y_6324_;
v___y_6314_ = v___y_6329_;
v___y_6315_ = v___y_6328_;
v___y_6316_ = v___x_6357_;
goto v___jp_6309_;
}
}
else
{
uint64_t v___x_6358_; uint64_t v___x_6359_; uint64_t v___x_6360_; 
v___x_6358_ = lean_uint64_sub(v___x_6333_, v___y_6330_);
v___x_6359_ = lean_unbox_uint64(v___y_6327_);
lean_dec(v___y_6327_);
v___x_6360_ = lean_uint64_shift_left(v___x_6359_, v___x_6358_);
v___y_6310_ = v___y_6321_;
v___y_6311_ = v___y_6322_;
v___y_6312_ = v_position_6331_;
v___y_6313_ = v___y_6324_;
v___y_6314_ = v___y_6329_;
v___y_6315_ = v___y_6328_;
v___y_6316_ = v___x_6360_;
goto v___jp_6309_;
}
}
else
{
uint8_t v___x_6361_; 
v___x_6361_ = lean_uint64_dec_lt(v___y_6326_, v___y_6323_);
if (v___x_6361_ == 0)
{
uint64_t v___x_6362_; uint64_t v___x_6363_; uint64_t v___x_6364_; 
v___x_6362_ = lean_uint64_sub(v___y_6326_, v___y_6323_);
v___x_6363_ = lean_unbox_uint64(v___y_6327_);
lean_dec(v___y_6327_);
v___x_6364_ = lean_uint64_shift_left(v___x_6363_, v___x_6362_);
v___y_6243_ = v___y_6321_;
v___y_6244_ = v___y_6329_;
v___y_6245_ = v___x_6364_;
goto v___jp_6242_;
}
else
{
uint64_t v___x_6365_; uint8_t v___x_6366_; 
v___x_6365_ = lean_uint64_sub(v___y_6323_, v___y_6326_);
v___x_6366_ = lean_uint64_dec_eq(v___x_6365_, v___y_6329_);
if (v___x_6366_ == 0)
{
uint64_t v___x_6367_; uint8_t v___x_6368_; 
v___x_6367_ = 64ULL;
v___x_6368_ = lean_uint64_dec_lt(v___x_6365_, v___x_6367_);
if (v___x_6368_ == 0)
{
uint8_t v___x_6369_; 
v___x_6369_ = lean_uint64_dec_eq(v___x_6365_, v___x_6367_);
if (v___x_6369_ == 0)
{
lean_dec(v___y_6327_);
v___y_6243_ = v___y_6321_;
v___y_6244_ = v___y_6329_;
v___y_6245_ = v___y_6329_;
goto v___jp_6242_;
}
else
{
uint64_t v___x_6370_; uint64_t v___x_6371_; uint8_t v___x_6372_; 
v___x_6370_ = 9223372036854775808ULL;
v___x_6371_ = lean_unbox_uint64(v___y_6327_);
lean_dec(v___y_6327_);
v___x_6372_ = lean_uint64_dec_lt(v___x_6370_, v___x_6371_);
if (v___x_6372_ == 0)
{
v___y_6243_ = v___y_6321_;
v___y_6244_ = v___y_6329_;
v___y_6245_ = v___y_6329_;
goto v___jp_6242_;
}
else
{
v___y_6243_ = v___y_6321_;
v___y_6244_ = v___y_6329_;
v___y_6245_ = v___y_6324_;
goto v___jp_6242_;
}
}
}
else
{
uint64_t v___x_6373_; uint64_t v_quotient_6374_; uint64_t v___x_6375_; uint64_t v___x_6376_; uint64_t v___x_6377_; uint64_t v_remainder_6378_; uint64_t v___x_6379_; uint64_t v_half_6380_; uint8_t v___x_6381_; 
v___x_6373_ = lean_unbox_uint64(v___y_6327_);
v_quotient_6374_ = lean_uint64_shift_right(v___x_6373_, v___x_6365_);
v___x_6375_ = lean_uint64_shift_left(v___y_6324_, v___x_6365_);
v___x_6376_ = lean_uint64_sub(v___x_6375_, v___y_6324_);
v___x_6377_ = lean_unbox_uint64(v___y_6327_);
lean_dec(v___y_6327_);
v_remainder_6378_ = lean_uint64_land(v___x_6377_, v___x_6376_);
v___x_6379_ = lean_uint64_sub(v___x_6365_, v___y_6324_);
v_half_6380_ = lean_uint64_shift_left(v___y_6324_, v___x_6379_);
v___x_6381_ = lean_uint64_dec_lt(v_remainder_6378_, v_half_6380_);
if (v___x_6381_ == 0)
{
uint8_t v___x_6382_; 
v___x_6382_ = lean_uint64_dec_lt(v_half_6380_, v_remainder_6378_);
if (v___x_6382_ == 0)
{
uint64_t v___x_6383_; uint8_t v___x_6384_; 
v___x_6383_ = lean_uint64_land(v_quotient_6374_, v___y_6324_);
v___x_6384_ = lean_uint64_dec_eq(v___x_6383_, v___y_6329_);
if (v___x_6384_ == 0)
{
uint64_t v___x_6385_; 
v___x_6385_ = lean_uint64_add(v_quotient_6374_, v___y_6324_);
v___y_6243_ = v___y_6321_;
v___y_6244_ = v___y_6329_;
v___y_6245_ = v___x_6385_;
goto v___jp_6242_;
}
else
{
v___y_6243_ = v___y_6321_;
v___y_6244_ = v___y_6329_;
v___y_6245_ = v_quotient_6374_;
goto v___jp_6242_;
}
}
else
{
uint64_t v___x_6386_; 
v___x_6386_ = lean_uint64_add(v_quotient_6374_, v___y_6324_);
v___y_6243_ = v___y_6321_;
v___y_6244_ = v___y_6329_;
v___y_6245_ = v___x_6386_;
goto v___jp_6242_;
}
}
else
{
v___y_6243_ = v___y_6321_;
v___y_6244_ = v___y_6329_;
v___y_6245_ = v_quotient_6374_;
goto v___jp_6242_;
}
}
}
else
{
uint64_t v___x_6387_; 
v___x_6387_ = lean_unbox_uint64(v___y_6327_);
lean_dec(v___y_6327_);
v___y_6243_ = v___y_6321_;
v___y_6244_ = v___y_6329_;
v___y_6245_ = v___x_6387_;
goto v___jp_6242_;
}
}
}
}
v___jp_6388_:
{
uint64_t v___x_6400_; uint8_t v___x_6401_; 
v___x_6400_ = lean_uint64_shift_right(v___y_6391_, v___y_6393_);
v___x_6401_ = lean_uint64_dec_eq(v___x_6400_, v___y_6398_);
if (v___x_6401_ == 0)
{
uint64_t v___x_6402_; 
v___x_6402_ = lean_uint64_add(v___y_6399_, v___y_6393_);
v___y_6321_ = v___y_6389_;
v___y_6322_ = v___y_6390_;
v___y_6323_ = v___y_6392_;
v___y_6324_ = v___y_6393_;
v___y_6325_ = v___y_6394_;
v___y_6326_ = v___y_6395_;
v___y_6327_ = v___y_6397_;
v___y_6328_ = v___y_6396_;
v___y_6329_ = v___y_6398_;
v___y_6330_ = v___x_6402_;
goto v___jp_6320_;
}
else
{
v___y_6321_ = v___y_6389_;
v___y_6322_ = v___y_6390_;
v___y_6323_ = v___y_6392_;
v___y_6324_ = v___y_6393_;
v___y_6325_ = v___y_6394_;
v___y_6326_ = v___y_6395_;
v___y_6327_ = v___y_6397_;
v___y_6328_ = v___y_6396_;
v___y_6329_ = v___y_6398_;
v___y_6330_ = v___y_6399_;
goto v___jp_6320_;
}
}
v___jp_6403_:
{
uint64_t v___x_6417_; uint8_t v___x_6418_; 
v___x_6417_ = lean_uint64_shift_right(v___y_6408_, v___y_6415_);
v___x_6418_ = lean_uint64_dec_eq(v___x_6417_, v___y_6412_);
if (v___x_6418_ == 0)
{
uint64_t v___x_6419_; 
v___x_6419_ = lean_uint64_add(v___y_6409_, v___y_6415_);
v___y_6389_ = v___y_6404_;
v___y_6390_ = v___y_6405_;
v___y_6391_ = v___y_6416_;
v___y_6392_ = v___y_6406_;
v___y_6393_ = v___y_6407_;
v___y_6394_ = v___y_6410_;
v___y_6395_ = v___y_6411_;
v___y_6396_ = v___y_6414_;
v___y_6397_ = v___y_6413_;
v___y_6398_ = v___y_6412_;
v___y_6399_ = v___x_6419_;
goto v___jp_6388_;
}
else
{
v___y_6389_ = v___y_6404_;
v___y_6390_ = v___y_6405_;
v___y_6391_ = v___y_6416_;
v___y_6392_ = v___y_6406_;
v___y_6393_ = v___y_6407_;
v___y_6394_ = v___y_6410_;
v___y_6395_ = v___y_6411_;
v___y_6396_ = v___y_6414_;
v___y_6397_ = v___y_6413_;
v___y_6398_ = v___y_6412_;
v___y_6399_ = v___y_6409_;
goto v___jp_6388_;
}
}
v___jp_6420_:
{
uint64_t v___x_6432_; uint64_t v___x_6433_; uint8_t v___x_6434_; 
v___x_6432_ = 2ULL;
v___x_6433_ = lean_uint64_shift_right(v___y_6425_, v___x_6432_);
v___x_6434_ = lean_uint64_dec_eq(v___x_6433_, v___y_6430_);
if (v___x_6434_ == 0)
{
v___y_6404_ = v___y_6421_;
v___y_6405_ = v___y_6422_;
v___y_6406_ = v___y_6423_;
v___y_6407_ = v___y_6424_;
v___y_6408_ = v___y_6425_;
v___y_6409_ = v___y_6431_;
v___y_6410_ = v___y_6426_;
v___y_6411_ = v___y_6427_;
v___y_6412_ = v___y_6430_;
v___y_6413_ = v___y_6429_;
v___y_6414_ = v___y_6428_;
v___y_6415_ = v___x_6432_;
v___y_6416_ = v___x_6433_;
goto v___jp_6403_;
}
else
{
v___y_6404_ = v___y_6421_;
v___y_6405_ = v___y_6422_;
v___y_6406_ = v___y_6423_;
v___y_6407_ = v___y_6424_;
v___y_6408_ = v___y_6425_;
v___y_6409_ = v___y_6431_;
v___y_6410_ = v___y_6426_;
v___y_6411_ = v___y_6427_;
v___y_6412_ = v___y_6430_;
v___y_6413_ = v___y_6429_;
v___y_6414_ = v___y_6428_;
v___y_6415_ = v___x_6432_;
v___y_6416_ = v___y_6425_;
goto v___jp_6403_;
}
}
v___jp_6435_:
{
uint64_t v___x_6449_; uint8_t v___x_6450_; 
v___x_6449_ = lean_uint64_shift_right(v___y_6437_, v___y_6441_);
v___x_6450_ = lean_uint64_dec_eq(v___x_6449_, v___y_6445_);
if (v___x_6450_ == 0)
{
uint64_t v___x_6451_; 
v___x_6451_ = lean_uint64_add(v___y_6436_, v___y_6441_);
v___y_6421_ = v___y_6438_;
v___y_6422_ = v___y_6439_;
v___y_6423_ = v___y_6440_;
v___y_6424_ = v___y_6442_;
v___y_6425_ = v___y_6448_;
v___y_6426_ = v___y_6443_;
v___y_6427_ = v___y_6444_;
v___y_6428_ = v___y_6447_;
v___y_6429_ = v___y_6446_;
v___y_6430_ = v___y_6445_;
v___y_6431_ = v___x_6451_;
goto v___jp_6420_;
}
else
{
v___y_6421_ = v___y_6438_;
v___y_6422_ = v___y_6439_;
v___y_6423_ = v___y_6440_;
v___y_6424_ = v___y_6442_;
v___y_6425_ = v___y_6448_;
v___y_6426_ = v___y_6443_;
v___y_6427_ = v___y_6444_;
v___y_6428_ = v___y_6447_;
v___y_6429_ = v___y_6446_;
v___y_6430_ = v___y_6445_;
v___y_6431_ = v___y_6436_;
goto v___jp_6420_;
}
}
v___jp_6452_:
{
uint64_t v___x_6464_; uint64_t v___x_6465_; uint8_t v___x_6466_; 
v___x_6464_ = 4ULL;
v___x_6465_ = lean_uint64_shift_right(v___y_6453_, v___x_6464_);
v___x_6466_ = lean_uint64_dec_eq(v___x_6465_, v___y_6462_);
if (v___x_6466_ == 0)
{
v___y_6436_ = v___y_6463_;
v___y_6437_ = v___y_6453_;
v___y_6438_ = v___y_6454_;
v___y_6439_ = v___y_6455_;
v___y_6440_ = v___y_6456_;
v___y_6441_ = v___x_6464_;
v___y_6442_ = v___y_6457_;
v___y_6443_ = v___y_6458_;
v___y_6444_ = v___y_6459_;
v___y_6445_ = v___y_6462_;
v___y_6446_ = v___y_6461_;
v___y_6447_ = v___y_6460_;
v___y_6448_ = v___x_6465_;
goto v___jp_6435_;
}
else
{
v___y_6436_ = v___y_6463_;
v___y_6437_ = v___y_6453_;
v___y_6438_ = v___y_6454_;
v___y_6439_ = v___y_6455_;
v___y_6440_ = v___y_6456_;
v___y_6441_ = v___x_6464_;
v___y_6442_ = v___y_6457_;
v___y_6443_ = v___y_6458_;
v___y_6444_ = v___y_6459_;
v___y_6445_ = v___y_6462_;
v___y_6446_ = v___y_6461_;
v___y_6447_ = v___y_6460_;
v___y_6448_ = v___y_6453_;
goto v___jp_6435_;
}
}
v___jp_6467_:
{
uint64_t v___x_6481_; uint8_t v___x_6482_; 
v___x_6481_ = lean_uint64_shift_right(v___y_6479_, v___y_6475_);
v___x_6482_ = lean_uint64_dec_eq(v___x_6481_, v___y_6476_);
if (v___x_6482_ == 0)
{
uint64_t v___x_6483_; 
v___x_6483_ = lean_uint64_add(v___y_6469_, v___y_6475_);
v___y_6453_ = v___y_6480_;
v___y_6454_ = v___y_6468_;
v___y_6455_ = v___y_6470_;
v___y_6456_ = v___y_6471_;
v___y_6457_ = v___y_6472_;
v___y_6458_ = v___y_6473_;
v___y_6459_ = v___y_6474_;
v___y_6460_ = v___y_6478_;
v___y_6461_ = v___y_6477_;
v___y_6462_ = v___y_6476_;
v___y_6463_ = v___x_6483_;
goto v___jp_6452_;
}
else
{
v___y_6453_ = v___y_6480_;
v___y_6454_ = v___y_6468_;
v___y_6455_ = v___y_6470_;
v___y_6456_ = v___y_6471_;
v___y_6457_ = v___y_6472_;
v___y_6458_ = v___y_6473_;
v___y_6459_ = v___y_6474_;
v___y_6460_ = v___y_6478_;
v___y_6461_ = v___y_6477_;
v___y_6462_ = v___y_6476_;
v___y_6463_ = v___y_6469_;
goto v___jp_6452_;
}
}
v___jp_6484_:
{
uint64_t v___x_6496_; uint64_t v___x_6497_; uint8_t v___x_6498_; 
v___x_6496_ = 8ULL;
v___x_6497_ = lean_uint64_shift_right(v___y_6494_, v___x_6496_);
v___x_6498_ = lean_uint64_dec_eq(v___x_6497_, v___y_6493_);
if (v___x_6498_ == 0)
{
v___y_6468_ = v___y_6485_;
v___y_6469_ = v___y_6495_;
v___y_6470_ = v___y_6486_;
v___y_6471_ = v___y_6487_;
v___y_6472_ = v___y_6488_;
v___y_6473_ = v___y_6489_;
v___y_6474_ = v___y_6490_;
v___y_6475_ = v___x_6496_;
v___y_6476_ = v___y_6493_;
v___y_6477_ = v___y_6492_;
v___y_6478_ = v___y_6491_;
v___y_6479_ = v___y_6494_;
v___y_6480_ = v___x_6497_;
goto v___jp_6467_;
}
else
{
v___y_6468_ = v___y_6485_;
v___y_6469_ = v___y_6495_;
v___y_6470_ = v___y_6486_;
v___y_6471_ = v___y_6487_;
v___y_6472_ = v___y_6488_;
v___y_6473_ = v___y_6489_;
v___y_6474_ = v___y_6490_;
v___y_6475_ = v___x_6496_;
v___y_6476_ = v___y_6493_;
v___y_6477_ = v___y_6492_;
v___y_6478_ = v___y_6491_;
v___y_6479_ = v___y_6494_;
v___y_6480_ = v___y_6494_;
goto v___jp_6467_;
}
}
v___jp_6499_:
{
uint64_t v___x_6513_; uint8_t v___x_6514_; 
v___x_6513_ = lean_uint64_shift_right(v___y_6503_, v___y_6508_);
v___x_6514_ = lean_uint64_dec_eq(v___x_6513_, v___y_6509_);
if (v___x_6514_ == 0)
{
uint64_t v___x_6515_; 
v___x_6515_ = lean_uint64_add(v___y_6505_, v___y_6508_);
v___y_6485_ = v___y_6500_;
v___y_6486_ = v___y_6501_;
v___y_6487_ = v___y_6502_;
v___y_6488_ = v___y_6504_;
v___y_6489_ = v___y_6506_;
v___y_6490_ = v___y_6507_;
v___y_6491_ = v___y_6511_;
v___y_6492_ = v___y_6510_;
v___y_6493_ = v___y_6509_;
v___y_6494_ = v___y_6512_;
v___y_6495_ = v___x_6515_;
goto v___jp_6484_;
}
else
{
v___y_6485_ = v___y_6500_;
v___y_6486_ = v___y_6501_;
v___y_6487_ = v___y_6502_;
v___y_6488_ = v___y_6504_;
v___y_6489_ = v___y_6506_;
v___y_6490_ = v___y_6507_;
v___y_6491_ = v___y_6511_;
v___y_6492_ = v___y_6510_;
v___y_6493_ = v___y_6509_;
v___y_6494_ = v___y_6512_;
v___y_6495_ = v___y_6505_;
goto v___jp_6484_;
}
}
v___jp_6516_:
{
uint64_t v___x_6528_; uint64_t v___x_6529_; uint8_t v___x_6530_; 
v___x_6528_ = 16ULL;
v___x_6529_ = lean_uint64_shift_right(v___y_6520_, v___x_6528_);
v___x_6530_ = lean_uint64_dec_eq(v___x_6529_, v___y_6526_);
if (v___x_6530_ == 0)
{
v___y_6500_ = v___y_6517_;
v___y_6501_ = v___y_6518_;
v___y_6502_ = v___y_6519_;
v___y_6503_ = v___y_6520_;
v___y_6504_ = v___y_6521_;
v___y_6505_ = v___y_6527_;
v___y_6506_ = v___y_6522_;
v___y_6507_ = v___y_6523_;
v___y_6508_ = v___x_6528_;
v___y_6509_ = v___y_6526_;
v___y_6510_ = v___y_6525_;
v___y_6511_ = v___y_6524_;
v___y_6512_ = v___x_6529_;
goto v___jp_6499_;
}
else
{
v___y_6500_ = v___y_6517_;
v___y_6501_ = v___y_6518_;
v___y_6502_ = v___y_6519_;
v___y_6503_ = v___y_6520_;
v___y_6504_ = v___y_6521_;
v___y_6505_ = v___y_6527_;
v___y_6506_ = v___y_6522_;
v___y_6507_ = v___y_6523_;
v___y_6508_ = v___x_6528_;
v___y_6509_ = v___y_6526_;
v___y_6510_ = v___y_6525_;
v___y_6511_ = v___y_6524_;
v___y_6512_ = v___y_6520_;
goto v___jp_6499_;
}
}
v___jp_6531_:
{
uint64_t v___x_6543_; uint64_t v___x_6544_; uint8_t v___x_6545_; 
v___x_6543_ = lean_unbox_uint64(v___y_6540_);
v___x_6544_ = lean_uint64_shift_right(v___x_6543_, v___y_6536_);
v___x_6545_ = lean_uint64_dec_eq(v___x_6544_, v___y_6539_);
if (v___x_6545_ == 0)
{
v___y_6517_ = v___y_6532_;
v___y_6518_ = v___y_6533_;
v___y_6519_ = v___y_6534_;
v___y_6520_ = v___y_6542_;
v___y_6521_ = v___y_6535_;
v___y_6522_ = v___y_6537_;
v___y_6523_ = v___y_6538_;
v___y_6524_ = v___y_6541_;
v___y_6525_ = v___y_6540_;
v___y_6526_ = v___y_6539_;
v___y_6527_ = v___y_6536_;
goto v___jp_6516_;
}
else
{
v___y_6517_ = v___y_6532_;
v___y_6518_ = v___y_6533_;
v___y_6519_ = v___y_6534_;
v___y_6520_ = v___y_6542_;
v___y_6521_ = v___y_6535_;
v___y_6522_ = v___y_6537_;
v___y_6523_ = v___y_6538_;
v___y_6524_ = v___y_6541_;
v___y_6525_ = v___y_6540_;
v___y_6526_ = v___y_6539_;
v___y_6527_ = v___y_6539_;
goto v___jp_6516_;
}
}
v___jp_6546_:
{
uint64_t v___x_6555_; uint64_t v___x_6556_; uint8_t v___x_6557_; 
v___x_6555_ = 0ULL;
v___x_6556_ = lean_unbox_uint64(v_snd_6554_);
v___x_6557_ = lean_uint64_dec_eq(v___x_6556_, v___x_6555_);
if (v___x_6557_ == 0)
{
uint64_t v___x_6558_; uint64_t v___x_6559_; uint64_t v___x_6560_; uint64_t v___x_6561_; uint8_t v___x_6562_; 
v___x_6558_ = lean_uint64_add(v___y_6550_, v___y_6548_);
v___x_6559_ = 32ULL;
v___x_6560_ = lean_unbox_uint64(v_snd_6554_);
v___x_6561_ = lean_uint64_shift_right(v___x_6560_, v___x_6559_);
v___x_6562_ = lean_uint64_dec_eq(v___x_6561_, v___x_6555_);
if (v___x_6562_ == 0)
{
v___y_6532_ = v_fst_6553_;
v___y_6533_ = v___y_6547_;
v___y_6534_ = v___y_6548_;
v___y_6535_ = v___y_6549_;
v___y_6536_ = v___x_6559_;
v___y_6537_ = v___y_6551_;
v___y_6538_ = v___x_6558_;
v___y_6539_ = v___x_6555_;
v___y_6540_ = v_snd_6554_;
v___y_6541_ = v___y_6552_;
v___y_6542_ = v___x_6561_;
goto v___jp_6531_;
}
else
{
uint64_t v___x_6563_; 
v___x_6563_ = lean_unbox_uint64(v_snd_6554_);
v___y_6532_ = v_fst_6553_;
v___y_6533_ = v___y_6547_;
v___y_6534_ = v___y_6548_;
v___y_6535_ = v___y_6549_;
v___y_6536_ = v___x_6559_;
v___y_6537_ = v___y_6551_;
v___y_6538_ = v___x_6558_;
v___y_6539_ = v___x_6555_;
v___y_6540_ = v_snd_6554_;
v___y_6541_ = v___y_6552_;
v___y_6542_ = v___x_6563_;
goto v___jp_6531_;
}
}
else
{
uint8_t v___x_6564_; 
lean_dec(v_snd_6554_);
v___x_6564_ = lean_unbox(v_fst_6553_);
lean_dec(v_fst_6553_);
if (v___x_6564_ == 0)
{
uint32_t v___x_6565_; 
v___x_6565_ = 0;
return v___x_6565_;
}
else
{
uint32_t v___x_6566_; 
v___x_6566_ = 2147483648;
return v___x_6566_;
}
}
}
v___jp_6567_:
{
uint8_t v___x_6579_; 
v___x_6579_ = lean_uint64_dec_eq(v___y_6569_, v___y_6577_);
if (v___x_6579_ == 0)
{
uint8_t v___x_6580_; 
v___x_6580_ = lean_uint64_dec_lt(v___y_6569_, v___y_6577_);
if (v___x_6580_ == 0)
{
uint64_t v___x_6581_; lean_object* v___x_6582_; lean_object* v___x_6583_; 
v___x_6581_ = lean_uint64_sub(v___y_6569_, v___y_6577_);
v___x_6582_ = lean_box(v___y_6568_);
v___x_6583_ = lean_box_uint64(v___x_6581_);
v___y_6547_ = v___y_6570_;
v___y_6548_ = v___y_6571_;
v___y_6549_ = v___y_6574_;
v___y_6550_ = v___y_6573_;
v___y_6551_ = v___y_6575_;
v___y_6552_ = v___y_6576_;
v_fst_6553_ = v___x_6582_;
v_snd_6554_ = v___x_6583_;
goto v___jp_6546_;
}
else
{
uint64_t v___x_6584_; lean_object* v___x_6585_; lean_object* v___x_6586_; 
v___x_6584_ = lean_uint64_sub(v___y_6577_, v___y_6569_);
v___x_6585_ = lean_box(v___y_6572_);
v___x_6586_ = lean_box_uint64(v___x_6584_);
v___y_6547_ = v___y_6570_;
v___y_6548_ = v___y_6571_;
v___y_6549_ = v___y_6574_;
v___y_6550_ = v___y_6573_;
v___y_6551_ = v___y_6575_;
v___y_6552_ = v___y_6576_;
v_fst_6553_ = v___x_6585_;
v_snd_6554_ = v___x_6586_;
goto v___jp_6546_;
}
}
else
{
lean_object* v___x_6587_; lean_object* v___x_6588_; 
v___x_6587_ = lean_box(v___y_6578_);
v___x_6588_ = ((lean_object*)(lp_competition_Submission_TunedAdd_core___boxed__const__1));
v___y_6547_ = v___y_6570_;
v___y_6548_ = v___y_6571_;
v___y_6549_ = v___y_6574_;
v___y_6550_ = v___y_6573_;
v___y_6551_ = v___y_6575_;
v___y_6552_ = v___y_6576_;
v_fst_6553_ = v___x_6587_;
v_snd_6554_ = v___x_6588_;
goto v___jp_6546_;
}
}
v___jp_6589_:
{
if (v___y_6600_ == 0)
{
v___y_6568_ = v___y_6590_;
v___y_6569_ = v___y_6591_;
v___y_6570_ = v___y_6592_;
v___y_6571_ = v___y_6593_;
v___y_6572_ = v___y_6596_;
v___y_6573_ = v___y_6595_;
v___y_6574_ = v___y_6594_;
v___y_6575_ = v___y_6597_;
v___y_6576_ = v___y_6598_;
v___y_6577_ = v___y_6599_;
v___y_6578_ = v___y_6600_;
goto v___jp_6567_;
}
else
{
uint64_t v___x_6601_; lean_object* v___x_6602_; lean_object* v___x_6603_; 
v___x_6601_ = lean_uint64_add(v___y_6591_, v___y_6599_);
v___x_6602_ = lean_box(v___y_6590_);
v___x_6603_ = lean_box_uint64(v___x_6601_);
v___y_6547_ = v___y_6592_;
v___y_6548_ = v___y_6593_;
v___y_6549_ = v___y_6594_;
v___y_6550_ = v___y_6595_;
v___y_6551_ = v___y_6597_;
v___y_6552_ = v___y_6598_;
v_fst_6553_ = v___x_6602_;
v_snd_6554_ = v___x_6603_;
goto v___jp_6546_;
}
}
v___jp_6604_:
{
uint8_t v___x_6616_; 
v___x_6616_ = lean_uint64_dec_eq(v___y_6606_, v___y_6610_);
if (v___x_6616_ == 0)
{
uint8_t v___x_6617_; 
v___x_6617_ = lean_uint64_dec_lt(v___y_6606_, v___y_6610_);
if (v___x_6617_ == 0)
{
uint64_t v___x_6618_; lean_object* v___x_6619_; lean_object* v___x_6620_; 
v___x_6618_ = lean_uint64_sub(v___y_6606_, v___y_6610_);
v___x_6619_ = lean_box(v___y_6605_);
v___x_6620_ = lean_box_uint64(v___x_6618_);
v___y_6216_ = v___y_6607_;
v___y_6217_ = v___y_6609_;
v___y_6218_ = v___y_6608_;
v___y_6219_ = v___y_6612_;
v___y_6220_ = v___y_6613_;
v___y_6221_ = v___y_6614_;
v_fst_6222_ = v___x_6619_;
v_snd_6223_ = v___x_6620_;
goto v___jp_6215_;
}
else
{
uint64_t v___x_6621_; lean_object* v___x_6622_; lean_object* v___x_6623_; 
v___x_6621_ = lean_uint64_sub(v___y_6610_, v___y_6606_);
v___x_6622_ = lean_box(v___y_6611_);
v___x_6623_ = lean_box_uint64(v___x_6621_);
v___y_6216_ = v___y_6607_;
v___y_6217_ = v___y_6609_;
v___y_6218_ = v___y_6608_;
v___y_6219_ = v___y_6612_;
v___y_6220_ = v___y_6613_;
v___y_6221_ = v___y_6614_;
v_fst_6222_ = v___x_6622_;
v_snd_6223_ = v___x_6623_;
goto v___jp_6215_;
}
}
else
{
lean_object* v___x_6624_; lean_object* v___x_6625_; 
v___x_6624_ = lean_box(v___y_6615_);
v___x_6625_ = ((lean_object*)(lp_competition_Submission_TunedAdd_core___boxed__const__1));
v___y_6216_ = v___y_6607_;
v___y_6217_ = v___y_6609_;
v___y_6218_ = v___y_6608_;
v___y_6219_ = v___y_6612_;
v___y_6220_ = v___y_6613_;
v___y_6221_ = v___y_6614_;
v_fst_6222_ = v___x_6624_;
v_snd_6223_ = v___x_6625_;
goto v___jp_6215_;
}
}
v___jp_6626_:
{
if (v___y_6637_ == 0)
{
v___y_6605_ = v___y_6627_;
v___y_6606_ = v___y_6628_;
v___y_6607_ = v___y_6629_;
v___y_6608_ = v___y_6632_;
v___y_6609_ = v___y_6631_;
v___y_6610_ = v___y_6630_;
v___y_6611_ = v___y_6634_;
v___y_6612_ = v___y_6633_;
v___y_6613_ = v___y_6635_;
v___y_6614_ = v___y_6636_;
v___y_6615_ = v___y_6637_;
goto v___jp_6604_;
}
else
{
uint64_t v___x_6638_; lean_object* v___x_6639_; lean_object* v___x_6640_; 
v___x_6638_ = lean_uint64_add(v___y_6628_, v___y_6630_);
v___x_6639_ = lean_box(v___y_6627_);
v___x_6640_ = lean_box_uint64(v___x_6638_);
v___y_6216_ = v___y_6629_;
v___y_6217_ = v___y_6631_;
v___y_6218_ = v___y_6632_;
v___y_6219_ = v___y_6633_;
v___y_6220_ = v___y_6635_;
v___y_6221_ = v___y_6636_;
v_fst_6222_ = v___x_6639_;
v_snd_6223_ = v___x_6640_;
goto v___jp_6215_;
}
}
v___jp_6641_:
{
uint8_t v___x_6653_; 
v___x_6653_ = lean_uint64_dec_le(v___y_6645_, v___y_6652_);
if (v___x_6653_ == 0)
{
uint64_t v_shift_6654_; uint64_t v___x_6655_; uint8_t v___x_6656_; 
v_shift_6654_ = lean_uint64_sub(v___y_6645_, v___y_6652_);
v___x_6655_ = 39ULL;
v___x_6656_ = lean_uint64_dec_le(v_shift_6654_, v___x_6655_);
if (v___x_6656_ == 0)
{
return v_x_5072_;
}
else
{
uint64_t v___x_6657_; 
v___x_6657_ = lean_uint64_shift_left(v___y_6643_, v_shift_6654_);
if (v___y_6642_ == 0)
{
if (v___y_6647_ == 0)
{
v___y_6590_ = v___y_6642_;
v___y_6591_ = v___x_6657_;
v___y_6592_ = v___y_6644_;
v___y_6593_ = v___y_6646_;
v___y_6594_ = v___y_6648_;
v___y_6595_ = v___y_6652_;
v___y_6596_ = v___y_6647_;
v___y_6597_ = v___y_6649_;
v___y_6598_ = v___y_6650_;
v___y_6599_ = v___y_6651_;
v___y_6600_ = v___x_6656_;
goto v___jp_6589_;
}
else
{
v___y_6568_ = v___y_6642_;
v___y_6569_ = v___x_6657_;
v___y_6570_ = v___y_6644_;
v___y_6571_ = v___y_6646_;
v___y_6572_ = v___y_6647_;
v___y_6573_ = v___y_6652_;
v___y_6574_ = v___y_6648_;
v___y_6575_ = v___y_6649_;
v___y_6576_ = v___y_6650_;
v___y_6577_ = v___y_6651_;
v___y_6578_ = v___y_6642_;
goto v___jp_6567_;
}
}
else
{
v___y_6590_ = v___y_6642_;
v___y_6591_ = v___x_6657_;
v___y_6592_ = v___y_6644_;
v___y_6593_ = v___y_6646_;
v___y_6594_ = v___y_6648_;
v___y_6595_ = v___y_6652_;
v___y_6596_ = v___y_6647_;
v___y_6597_ = v___y_6649_;
v___y_6598_ = v___y_6650_;
v___y_6599_ = v___y_6651_;
v___y_6600_ = v___y_6647_;
goto v___jp_6589_;
}
}
}
else
{
uint64_t v_shift_6658_; uint64_t v___x_6659_; uint8_t v___x_6660_; 
v_shift_6658_ = lean_uint64_sub(v___y_6652_, v___y_6645_);
v___x_6659_ = 39ULL;
v___x_6660_ = lean_uint64_dec_le(v_shift_6658_, v___x_6659_);
if (v___x_6660_ == 0)
{
return v_y_5073_;
}
else
{
uint64_t v___x_6661_; 
v___x_6661_ = lean_uint64_shift_left(v___y_6651_, v_shift_6658_);
if (v___y_6642_ == 0)
{
if (v___y_6647_ == 0)
{
v___y_6627_ = v___y_6642_;
v___y_6628_ = v___y_6643_;
v___y_6629_ = v___y_6644_;
v___y_6630_ = v___x_6661_;
v___y_6631_ = v___y_6646_;
v___y_6632_ = v___y_6645_;
v___y_6633_ = v___y_6648_;
v___y_6634_ = v___y_6647_;
v___y_6635_ = v___y_6649_;
v___y_6636_ = v___y_6650_;
v___y_6637_ = v___x_6660_;
goto v___jp_6626_;
}
else
{
v___y_6605_ = v___y_6642_;
v___y_6606_ = v___y_6643_;
v___y_6607_ = v___y_6644_;
v___y_6608_ = v___y_6645_;
v___y_6609_ = v___y_6646_;
v___y_6610_ = v___x_6661_;
v___y_6611_ = v___y_6647_;
v___y_6612_ = v___y_6648_;
v___y_6613_ = v___y_6649_;
v___y_6614_ = v___y_6650_;
v___y_6615_ = v___y_6642_;
goto v___jp_6604_;
}
}
else
{
v___y_6627_ = v___y_6642_;
v___y_6628_ = v___y_6643_;
v___y_6629_ = v___y_6644_;
v___y_6630_ = v___x_6661_;
v___y_6631_ = v___y_6646_;
v___y_6632_ = v___y_6645_;
v___y_6633_ = v___y_6648_;
v___y_6634_ = v___y_6647_;
v___y_6635_ = v___y_6649_;
v___y_6636_ = v___y_6650_;
v___y_6637_ = v___y_6647_;
goto v___jp_6626_;
}
}
}
}
v___jp_6662_:
{
uint64_t v___x_6674_; uint64_t v___x_6675_; uint8_t v___x_6676_; 
v___x_6674_ = lean_uint32_to_uint64(v___y_6666_);
v___x_6675_ = 0ULL;
v___x_6676_ = lean_uint64_dec_eq(v___x_6674_, v___x_6675_);
if (v___x_6676_ == 0)
{
uint64_t v___x_6677_; 
v___x_6677_ = lean_uint64_sub(v___x_6674_, v___y_6669_);
v___y_6642_ = v___y_6663_;
v___y_6643_ = v___y_6664_;
v___y_6644_ = v___y_6665_;
v___y_6645_ = v___y_6673_;
v___y_6646_ = v___y_6667_;
v___y_6647_ = v___y_6668_;
v___y_6648_ = v___y_6669_;
v___y_6649_ = v___y_6670_;
v___y_6650_ = v___y_6671_;
v___y_6651_ = v___y_6672_;
v___y_6652_ = v___x_6677_;
goto v___jp_6641_;
}
else
{
v___y_6642_ = v___y_6663_;
v___y_6643_ = v___y_6664_;
v___y_6644_ = v___y_6665_;
v___y_6645_ = v___y_6673_;
v___y_6646_ = v___y_6667_;
v___y_6647_ = v___y_6668_;
v___y_6648_ = v___y_6669_;
v___y_6649_ = v___y_6670_;
v___y_6650_ = v___y_6671_;
v___y_6651_ = v___y_6672_;
v___y_6652_ = v___x_6675_;
goto v___jp_6641_;
}
}
v___jp_6678_:
{
uint64_t v___x_6690_; uint64_t v___x_6691_; uint8_t v___x_6692_; 
v___x_6690_ = lean_uint32_to_uint64(v___y_6679_);
v___x_6691_ = 0ULL;
v___x_6692_ = lean_uint64_dec_eq(v___x_6690_, v___x_6691_);
if (v___x_6692_ == 0)
{
uint64_t v___x_6693_; 
v___x_6693_ = lean_uint64_sub(v___x_6690_, v___y_6685_);
v___y_6663_ = v___y_6680_;
v___y_6664_ = v___y_6681_;
v___y_6665_ = v___y_6682_;
v___y_6666_ = v___y_6684_;
v___y_6667_ = v___y_6683_;
v___y_6668_ = v___y_6686_;
v___y_6669_ = v___y_6685_;
v___y_6670_ = v___y_6687_;
v___y_6671_ = v___y_6688_;
v___y_6672_ = v___y_6689_;
v___y_6673_ = v___x_6693_;
goto v___jp_6662_;
}
else
{
v___y_6663_ = v___y_6680_;
v___y_6664_ = v___y_6681_;
v___y_6665_ = v___y_6682_;
v___y_6666_ = v___y_6684_;
v___y_6667_ = v___y_6683_;
v___y_6668_ = v___y_6686_;
v___y_6669_ = v___y_6685_;
v___y_6670_ = v___y_6687_;
v___y_6671_ = v___y_6688_;
v___y_6672_ = v___y_6689_;
v___y_6673_ = v___x_6691_;
goto v___jp_6662_;
}
}
v___jp_6694_:
{
uint32_t v___x_6705_; uint32_t v___x_6706_; uint32_t v___x_6707_; uint8_t v___x_6708_; 
v___x_6705_ = 8388607;
v___x_6706_ = lean_uint32_land(v_y_5073_, v___x_6705_);
v___x_6707_ = 0;
v___x_6708_ = lean_uint32_dec_eq(v___y_6698_, v___x_6707_);
if (v___x_6708_ == 0)
{
uint64_t v___x_6709_; uint64_t v___x_6710_; uint64_t v___x_6711_; 
v___x_6709_ = lean_uint32_to_uint64(v___x_6706_);
v___x_6710_ = 8388608ULL;
v___x_6711_ = lean_uint64_lor(v___x_6709_, v___x_6710_);
v___y_6679_ = v___y_6696_;
v___y_6680_ = v___y_6695_;
v___y_6681_ = v___y_6704_;
v___y_6682_ = v___y_6697_;
v___y_6683_ = v___y_6699_;
v___y_6684_ = v___y_6698_;
v___y_6685_ = v___y_6701_;
v___y_6686_ = v___y_6700_;
v___y_6687_ = v___y_6702_;
v___y_6688_ = v___y_6703_;
v___y_6689_ = v___x_6711_;
goto v___jp_6678_;
}
else
{
uint64_t v___x_6712_; 
v___x_6712_ = lean_uint32_to_uint64(v___x_6706_);
v___y_6679_ = v___y_6696_;
v___y_6680_ = v___y_6695_;
v___y_6681_ = v___y_6704_;
v___y_6682_ = v___y_6697_;
v___y_6683_ = v___y_6699_;
v___y_6684_ = v___y_6698_;
v___y_6685_ = v___y_6701_;
v___y_6686_ = v___y_6700_;
v___y_6687_ = v___y_6702_;
v___y_6688_ = v___y_6703_;
v___y_6689_ = v___x_6712_;
goto v___jp_6678_;
}
}
v___jp_6713_:
{
uint32_t v___x_6723_; uint32_t v___x_6724_; uint32_t v___x_6725_; uint8_t v___x_6726_; 
v___x_6723_ = 8388607;
v___x_6724_ = lean_uint32_land(v_x_5072_, v___x_6723_);
v___x_6725_ = 0;
v___x_6726_ = lean_uint32_dec_eq(v___y_6714_, v___x_6725_);
if (v___x_6726_ == 0)
{
uint64_t v___x_6727_; uint64_t v___x_6728_; uint64_t v___x_6729_; 
v___x_6727_ = lean_uint32_to_uint64(v___x_6724_);
v___x_6728_ = 8388608ULL;
v___x_6729_ = lean_uint64_lor(v___x_6727_, v___x_6728_);
v___y_6695_ = v___y_6715_;
v___y_6696_ = v___y_6714_;
v___y_6697_ = v___y_6716_;
v___y_6698_ = v___y_6718_;
v___y_6699_ = v___y_6717_;
v___y_6700_ = v___y_6722_;
v___y_6701_ = v___y_6719_;
v___y_6702_ = v___y_6720_;
v___y_6703_ = v___y_6721_;
v___y_6704_ = v___x_6729_;
goto v___jp_6694_;
}
else
{
uint64_t v___x_6730_; 
v___x_6730_ = lean_uint32_to_uint64(v___x_6724_);
v___y_6695_ = v___y_6715_;
v___y_6696_ = v___y_6714_;
v___y_6697_ = v___y_6716_;
v___y_6698_ = v___y_6718_;
v___y_6699_ = v___y_6717_;
v___y_6700_ = v___y_6722_;
v___y_6701_ = v___y_6719_;
v___y_6702_ = v___y_6720_;
v___y_6703_ = v___y_6721_;
v___y_6704_ = v___x_6730_;
goto v___jp_6694_;
}
}
v___jp_6731_:
{
uint32_t v___x_6742_; uint32_t v___x_6743_; uint32_t v___x_6744_; uint8_t v___x_6745_; 
v___x_6742_ = 2147483648;
v___x_6743_ = lean_uint32_land(v_y_5073_, v___x_6742_);
v___x_6744_ = 0;
v___x_6745_ = lean_uint32_dec_eq(v___x_6743_, v___x_6744_);
if (v___x_6745_ == 0)
{
v___y_6714_ = v___y_6732_;
v___y_6715_ = v___y_6741_;
v___y_6716_ = v___y_6733_;
v___y_6717_ = v___y_6736_;
v___y_6718_ = v___y_6735_;
v___y_6719_ = v___y_6737_;
v___y_6720_ = v___y_6738_;
v___y_6721_ = v___y_6740_;
v___y_6722_ = v___y_6734_;
goto v___jp_6713_;
}
else
{
v___y_6714_ = v___y_6732_;
v___y_6715_ = v___y_6741_;
v___y_6716_ = v___y_6733_;
v___y_6717_ = v___y_6736_;
v___y_6718_ = v___y_6735_;
v___y_6719_ = v___y_6737_;
v___y_6720_ = v___y_6738_;
v___y_6721_ = v___y_6740_;
v___y_6722_ = v___y_6739_;
goto v___jp_6713_;
}
}
v___jp_6746_:
{
uint32_t v___x_6752_; uint32_t v___x_6753_; uint32_t v___x_6754_; uint32_t v___x_6755_; uint32_t v___x_6756_; uint32_t v___x_6757_; 
v___x_6752_ = lean_uint32_land(v___y_6747_, v___y_6748_);
v___x_6753_ = lean_uint32_shift_left(v___x_6752_, v___y_6750_);
v___x_6754_ = lean_uint32_lor(v___y_6751_, v___x_6753_);
v___x_6755_ = 8388607;
v___x_6756_ = lean_uint32_land(v___y_6749_, v___x_6755_);
v___x_6757_ = lean_uint32_lor(v___x_6754_, v___x_6756_);
return v___x_6757_;
}
v___jp_6758_:
{
if (v___y_6760_ == 0)
{
uint32_t v___x_6764_; 
v___x_6764_ = 0;
v___y_6747_ = v___y_6759_;
v___y_6748_ = v___y_6761_;
v___y_6749_ = v___y_6763_;
v___y_6750_ = v___y_6762_;
v___y_6751_ = v___x_6764_;
goto v___jp_6746_;
}
else
{
uint32_t v___x_6765_; 
v___x_6765_ = 2147483648;
v___y_6747_ = v___y_6759_;
v___y_6748_ = v___y_6761_;
v___y_6749_ = v___y_6763_;
v___y_6750_ = v___y_6762_;
v___y_6751_ = v___x_6765_;
goto v___jp_6746_;
}
}
v___jp_6766_:
{
uint64_t v___x_6772_; uint8_t v___x_6773_; 
v___x_6772_ = 8388608ULL;
v___x_6773_ = lean_uint64_dec_lt(v___y_6771_, v___x_6772_);
if (v___x_6773_ == 0)
{
uint64_t v___x_6774_; uint32_t v___x_6775_; 
v___x_6774_ = lean_uint64_sub(v___y_6771_, v___x_6772_);
v___x_6775_ = lean_uint64_to_uint32(v___x_6774_);
v___y_6759_ = v___y_6767_;
v___y_6760_ = v___y_6768_;
v___y_6761_ = v___y_6769_;
v___y_6762_ = v___y_6770_;
v___y_6763_ = v___x_6775_;
goto v___jp_6758_;
}
else
{
uint32_t v___x_6776_; 
v___x_6776_ = lean_uint32_once(&lp_competition_Submission_TunedAdd_fracW___closed__0, &lp_competition_Submission_TunedAdd_fracW___closed__0_once, _init_lp_competition_Submission_TunedAdd_fracW___closed__0);
v___y_6759_ = v___y_6767_;
v___y_6760_ = v___y_6768_;
v___y_6761_ = v___y_6769_;
v___y_6762_ = v___y_6770_;
v___y_6763_ = v___x_6776_;
goto v___jp_6758_;
}
}
v___jp_6777_:
{
uint64_t v___x_6784_; uint8_t v___x_6785_; 
v___x_6784_ = 425ULL;
v___x_6785_ = lean_uint64_dec_lt(v___x_6784_, v___y_6783_);
if (v___x_6785_ == 0)
{
uint64_t v___x_6786_; uint64_t v___x_6787_; uint32_t v___x_6788_; 
v___x_6786_ = 171ULL;
v___x_6787_ = lean_uint64_sub(v___y_6783_, v___x_6786_);
v___x_6788_ = lean_uint64_to_uint32(v___x_6787_);
if (v___y_6781_ == 0)
{
v___y_6767_ = v___x_6788_;
v___y_6768_ = v___y_6778_;
v___y_6769_ = v___y_6779_;
v___y_6770_ = v___y_6782_;
v___y_6771_ = v___y_6780_;
goto v___jp_6766_;
}
else
{
uint64_t v___x_6789_; 
v___x_6789_ = 8388608ULL;
v___y_6767_ = v___x_6788_;
v___y_6768_ = v___y_6778_;
v___y_6769_ = v___y_6779_;
v___y_6770_ = v___y_6782_;
v___y_6771_ = v___x_6789_;
goto v___jp_6766_;
}
}
else
{
if (v___y_6778_ == 0)
{
uint32_t v___x_6790_; 
v___x_6790_ = 2139095040;
return v___x_6790_;
}
else
{
uint32_t v___x_6791_; 
v___x_6791_ = 4286578688;
return v___x_6791_;
}
}
}
v___jp_6792_:
{
uint64_t v___x_6799_; uint8_t v_carry_6800_; 
v___x_6799_ = 16777216ULL;
v_carry_6800_ = lean_uint64_dec_eq(v___y_6798_, v___x_6799_);
if (v_carry_6800_ == 0)
{
v___y_6778_ = v___y_6793_;
v___y_6779_ = v___y_6795_;
v___y_6780_ = v___y_6798_;
v___y_6781_ = v_carry_6800_;
v___y_6782_ = v___y_6797_;
v___y_6783_ = v___y_6794_;
goto v___jp_6777_;
}
else
{
uint64_t v___x_6801_; 
v___x_6801_ = lean_uint64_add(v___y_6794_, v___y_6796_);
v___y_6778_ = v___y_6793_;
v___y_6779_ = v___y_6795_;
v___y_6780_ = v___y_6798_;
v___y_6781_ = v_carry_6800_;
v___y_6782_ = v___y_6797_;
v___y_6783_ = v___x_6801_;
goto v___jp_6777_;
}
}
v___jp_6802_:
{
uint64_t v_product_6813_; uint64_t v___x_6814_; uint64_t v___x_6815_; uint64_t v___x_6816_; uint8_t v___x_6817_; 
v_product_6813_ = lean_uint64_add(v___y_6806_, v___y_6812_);
v___x_6814_ = 24ULL;
v___x_6815_ = lean_uint64_shift_right(v_product_6813_, v___x_6814_);
v___x_6816_ = 1ULL;
v___x_6817_ = lean_uint64_dec_eq(v___x_6815_, v___x_6816_);
if (v___x_6817_ == 0)
{
uint32_t v___x_6818_; uint32_t v___x_6819_; uint32_t v___x_6820_; uint8_t v___x_6821_; 
v___x_6818_ = 2147483648;
v___x_6819_ = lean_uint32_land(v_x_5072_, v___x_6818_);
v___x_6820_ = 0;
v___x_6821_ = lean_uint32_dec_eq(v___x_6819_, v___x_6820_);
if (v___x_6821_ == 0)
{
v___y_5893_ = v___y_6803_;
v___y_5894_ = v___y_6805_;
v___y_5895_ = v___x_6817_;
v___y_5896_ = v___y_6807_;
v___y_5897_ = v___x_6816_;
v___y_5898_ = v___y_6809_;
v___y_5899_ = v___y_6811_;
v___y_5900_ = v___y_6809_;
goto v___jp_5892_;
}
else
{
v___y_5893_ = v___y_6803_;
v___y_5894_ = v___y_6805_;
v___y_5895_ = v___x_6817_;
v___y_5896_ = v___y_6807_;
v___y_5897_ = v___x_6816_;
v___y_5898_ = v___y_6809_;
v___y_5899_ = v___y_6811_;
v___y_5900_ = v___x_6817_;
goto v___jp_5892_;
}
}
else
{
uint64_t v___x_6822_; uint64_t v___x_6823_; uint64_t v___x_6824_; uint64_t v___x_6825_; uint8_t v___x_6826_; 
v___x_6822_ = 172ULL;
v___x_6823_ = 149ULL;
v___x_6824_ = lean_uint64_add(v___y_6808_, v___x_6823_);
v___x_6825_ = lean_uint64_add(v___x_6814_, v___x_6824_);
v___x_6826_ = lean_uint64_dec_le(v___x_6822_, v___x_6825_);
if (v___x_6826_ == 0)
{
uint32_t v___x_6827_; uint32_t v___x_6828_; uint32_t v___x_6829_; uint8_t v___x_6830_; 
v___x_6827_ = 2147483648;
v___x_6828_ = lean_uint32_land(v_x_5072_, v___x_6827_);
v___x_6829_ = 0;
v___x_6830_ = lean_uint32_dec_eq(v___x_6828_, v___x_6829_);
if (v___x_6830_ == 0)
{
v___y_6732_ = v___y_6803_;
v___y_6733_ = v___y_6805_;
v___y_6734_ = v___x_6817_;
v___y_6735_ = v___y_6807_;
v___y_6736_ = v___x_6823_;
v___y_6737_ = v___x_6816_;
v___y_6738_ = v___x_6822_;
v___y_6739_ = v___y_6810_;
v___y_6740_ = v___y_6811_;
v___y_6741_ = v___x_6817_;
goto v___jp_6731_;
}
else
{
v___y_6732_ = v___y_6803_;
v___y_6733_ = v___y_6805_;
v___y_6734_ = v___x_6817_;
v___y_6735_ = v___y_6807_;
v___y_6736_ = v___x_6823_;
v___y_6737_ = v___x_6816_;
v___y_6738_ = v___x_6822_;
v___y_6739_ = v___y_6810_;
v___y_6740_ = v___y_6811_;
v___y_6741_ = v___y_6810_;
goto v___jp_6731_;
}
}
else
{
uint64_t v_quotient_6831_; uint64_t v_remainder_6832_; uint8_t v___x_6833_; 
v_quotient_6831_ = lean_uint64_shift_right(v_product_6813_, v___x_6816_);
v_remainder_6832_ = lean_uint64_land(v_product_6813_, v___x_6816_);
v___x_6833_ = lean_uint64_dec_lt(v_remainder_6832_, v___x_6816_);
if (v___x_6833_ == 0)
{
uint8_t v___x_6834_; 
v___x_6834_ = lean_uint64_dec_lt(v___x_6816_, v_remainder_6832_);
if (v___x_6834_ == 0)
{
uint64_t v___x_6835_; uint64_t v___x_6836_; uint8_t v___x_6837_; 
v___x_6835_ = lean_uint64_land(v_quotient_6831_, v___x_6816_);
v___x_6836_ = 0ULL;
v___x_6837_ = lean_uint64_dec_eq(v___x_6835_, v___x_6836_);
if (v___x_6837_ == 0)
{
uint64_t v___x_6838_; 
v___x_6838_ = lean_uint64_add(v_quotient_6831_, v___x_6816_);
v___y_6793_ = v___y_6804_;
v___y_6794_ = v___x_6825_;
v___y_6795_ = v___y_6805_;
v___y_6796_ = v___x_6816_;
v___y_6797_ = v___y_6811_;
v___y_6798_ = v___x_6838_;
goto v___jp_6792_;
}
else
{
v___y_6793_ = v___y_6804_;
v___y_6794_ = v___x_6825_;
v___y_6795_ = v___y_6805_;
v___y_6796_ = v___x_6816_;
v___y_6797_ = v___y_6811_;
v___y_6798_ = v_quotient_6831_;
goto v___jp_6792_;
}
}
else
{
uint64_t v___x_6839_; 
v___x_6839_ = lean_uint64_add(v_quotient_6831_, v___x_6816_);
v___y_6793_ = v___y_6804_;
v___y_6794_ = v___x_6825_;
v___y_6795_ = v___y_6805_;
v___y_6796_ = v___x_6816_;
v___y_6797_ = v___y_6811_;
v___y_6798_ = v___x_6839_;
goto v___jp_6792_;
}
}
else
{
v___y_6793_ = v___y_6804_;
v___y_6794_ = v___x_6825_;
v___y_6795_ = v___y_6805_;
v___y_6796_ = v___x_6816_;
v___y_6797_ = v___y_6811_;
v___y_6798_ = v_quotient_6831_;
goto v___jp_6792_;
}
}
}
}
v___jp_6840_:
{
uint32_t v___x_6850_; uint32_t v___x_6851_; uint32_t v___x_6852_; uint8_t v___x_6853_; 
v___x_6850_ = 8388607;
v___x_6851_ = lean_uint32_land(v_y_5073_, v___x_6850_);
v___x_6852_ = 0;
v___x_6853_ = lean_uint32_dec_eq(v___y_6844_, v___x_6852_);
if (v___x_6853_ == 0)
{
uint64_t v___x_6854_; uint64_t v___x_6855_; uint64_t v___x_6856_; 
v___x_6854_ = lean_uint32_to_uint64(v___x_6851_);
v___x_6855_ = 8388608ULL;
v___x_6856_ = lean_uint64_lor(v___x_6854_, v___x_6855_);
v___y_6803_ = v___y_6841_;
v___y_6804_ = v___y_6842_;
v___y_6805_ = v___y_6843_;
v___y_6806_ = v___y_6849_;
v___y_6807_ = v___y_6844_;
v___y_6808_ = v___y_6845_;
v___y_6809_ = v___y_6846_;
v___y_6810_ = v___y_6847_;
v___y_6811_ = v___y_6848_;
v___y_6812_ = v___x_6856_;
goto v___jp_6802_;
}
else
{
uint64_t v___x_6857_; 
v___x_6857_ = lean_uint32_to_uint64(v___x_6851_);
v___y_6803_ = v___y_6841_;
v___y_6804_ = v___y_6842_;
v___y_6805_ = v___y_6843_;
v___y_6806_ = v___y_6849_;
v___y_6807_ = v___y_6844_;
v___y_6808_ = v___y_6845_;
v___y_6809_ = v___y_6846_;
v___y_6810_ = v___y_6847_;
v___y_6811_ = v___y_6848_;
v___y_6812_ = v___x_6857_;
goto v___jp_6802_;
}
}
v___jp_6858_:
{
uint32_t v___x_6861_; uint32_t v___x_6862_; uint32_t v___x_6863_; 
v___x_6861_ = 8388607;
v___x_6862_ = lean_uint32_land(v___y_6859_, v___x_6861_);
v___x_6863_ = lean_uint32_lor(v___y_6860_, v___x_6862_);
return v___x_6863_;
}
v___jp_6864_:
{
uint8_t v___x_6868_; 
v___x_6868_ = lean_uint64_dec_eq(v___y_6867_, v___y_6866_);
if (v___x_6868_ == 0)
{
uint64_t v___x_6869_; uint8_t v___x_6870_; 
v___x_6869_ = 8388608ULL;
v___x_6870_ = lean_uint64_dec_eq(v___y_6867_, v___x_6869_);
if (v___x_6870_ == 0)
{
uint32_t v___x_6871_; uint8_t v___x_6872_; 
v___x_6871_ = lean_uint64_to_uint32(v___y_6867_);
v___x_6872_ = lean_unbox(v___y_6865_);
lean_dec(v___y_6865_);
if (v___x_6872_ == 0)
{
uint32_t v___x_6873_; 
v___x_6873_ = 0;
v___y_6859_ = v___x_6871_;
v___y_6860_ = v___x_6873_;
goto v___jp_6858_;
}
else
{
uint32_t v___x_6874_; 
v___x_6874_ = 2147483648;
v___y_6859_ = v___x_6871_;
v___y_6860_ = v___x_6874_;
goto v___jp_6858_;
}
}
else
{
uint8_t v___x_6875_; 
v___x_6875_ = lean_unbox(v___y_6865_);
lean_dec(v___y_6865_);
if (v___x_6875_ == 0)
{
uint32_t v___x_6876_; 
v___x_6876_ = 0;
v___y_5095_ = v___x_6876_;
goto v___jp_5094_;
}
else
{
uint32_t v___x_6877_; 
v___x_6877_ = 2147483648;
v___y_5095_ = v___x_6877_;
goto v___jp_5094_;
}
}
}
else
{
uint8_t v___x_6878_; 
v___x_6878_ = lean_unbox(v___y_6865_);
lean_dec(v___y_6865_);
if (v___x_6878_ == 0)
{
uint32_t v___x_6879_; 
v___x_6879_ = 0;
return v___x_6879_;
}
else
{
uint32_t v___x_6880_; 
v___x_6880_ = 2147483648;
return v___x_6880_;
}
}
}
v___jp_6881_:
{
uint32_t v___x_6887_; uint32_t v___x_6888_; uint32_t v___x_6889_; uint32_t v___x_6890_; uint32_t v___x_6891_; uint32_t v___x_6892_; 
v___x_6887_ = lean_uint32_land(v___y_6883_, v___y_6882_);
v___x_6888_ = lean_uint32_shift_left(v___x_6887_, v___y_6885_);
v___x_6889_ = lean_uint32_lor(v___y_6886_, v___x_6888_);
v___x_6890_ = 8388607;
v___x_6891_ = lean_uint32_land(v___y_6884_, v___x_6890_);
v___x_6892_ = lean_uint32_lor(v___x_6889_, v___x_6891_);
return v___x_6892_;
}
v___jp_6893_:
{
uint8_t v___x_6899_; 
v___x_6899_ = lean_unbox(v___y_6896_);
lean_dec(v___y_6896_);
if (v___x_6899_ == 0)
{
uint32_t v___x_6900_; 
v___x_6900_ = 0;
v___y_6882_ = v___y_6894_;
v___y_6883_ = v___y_6895_;
v___y_6884_ = v___y_6898_;
v___y_6885_ = v___y_6897_;
v___y_6886_ = v___x_6900_;
goto v___jp_6881_;
}
else
{
uint32_t v___x_6901_; 
v___x_6901_ = 2147483648;
v___y_6882_ = v___y_6894_;
v___y_6883_ = v___y_6895_;
v___y_6884_ = v___y_6898_;
v___y_6885_ = v___y_6897_;
v___y_6886_ = v___x_6901_;
goto v___jp_6881_;
}
}
v___jp_6902_:
{
uint64_t v___x_6909_; uint64_t v_encodedExponent_6910_; uint32_t v___x_6911_; uint64_t v___x_6912_; uint8_t v___x_6913_; 
v___x_6909_ = 171ULL;
v_encodedExponent_6910_ = lean_uint64_sub(v___y_6904_, v___x_6909_);
v___x_6911_ = lean_uint64_to_uint32(v_encodedExponent_6910_);
v___x_6912_ = 8388608ULL;
v___x_6913_ = lean_uint64_dec_lt(v___y_6908_, v___x_6912_);
if (v___x_6913_ == 0)
{
uint64_t v___x_6914_; uint32_t v___x_6915_; 
v___x_6914_ = lean_uint64_sub(v___y_6908_, v___x_6912_);
v___x_6915_ = lean_uint64_to_uint32(v___x_6914_);
v___y_6894_ = v___y_6903_;
v___y_6895_ = v___x_6911_;
v___y_6896_ = v___y_6905_;
v___y_6897_ = v___y_6906_;
v___y_6898_ = v___x_6915_;
goto v___jp_6893_;
}
else
{
uint32_t v___x_6916_; 
v___x_6916_ = lean_uint64_to_uint32(v___y_6907_);
v___y_6894_ = v___y_6903_;
v___y_6895_ = v___x_6911_;
v___y_6896_ = v___y_6905_;
v___y_6897_ = v___y_6906_;
v___y_6898_ = v___x_6916_;
goto v___jp_6893_;
}
}
v___jp_6917_:
{
uint64_t v___x_6925_; uint8_t v___x_6926_; 
v___x_6925_ = 425ULL;
v___x_6926_ = lean_uint64_dec_lt(v___x_6925_, v___y_6924_);
if (v___x_6926_ == 0)
{
if (v___y_6919_ == 0)
{
v___y_6903_ = v___y_6918_;
v___y_6904_ = v___y_6924_;
v___y_6905_ = v___y_6921_;
v___y_6906_ = v___y_6922_;
v___y_6907_ = v___y_6923_;
v___y_6908_ = v___y_6920_;
goto v___jp_6902_;
}
else
{
uint64_t v___x_6927_; 
v___x_6927_ = 8388608ULL;
v___y_6903_ = v___y_6918_;
v___y_6904_ = v___y_6924_;
v___y_6905_ = v___y_6921_;
v___y_6906_ = v___y_6922_;
v___y_6907_ = v___y_6923_;
v___y_6908_ = v___x_6927_;
goto v___jp_6902_;
}
}
else
{
uint8_t v___x_6928_; 
v___x_6928_ = lean_unbox(v___y_6921_);
lean_dec(v___y_6921_);
if (v___x_6928_ == 0)
{
uint32_t v___x_6929_; 
v___x_6929_ = 2139095040;
return v___x_6929_;
}
else
{
uint32_t v___x_6930_; 
v___x_6930_ = 4286578688;
return v___x_6930_;
}
}
}
v___jp_6931_:
{
uint64_t v___x_6938_; uint8_t v_carry_6939_; 
v___x_6938_ = 16777216ULL;
v_carry_6939_ = lean_uint64_dec_eq(v___y_6937_, v___x_6938_);
if (v_carry_6939_ == 0)
{
v___y_6918_ = v___y_6932_;
v___y_6919_ = v_carry_6939_;
v___y_6920_ = v___y_6937_;
v___y_6921_ = v___y_6933_;
v___y_6922_ = v___y_6935_;
v___y_6923_ = v___y_6936_;
v___y_6924_ = v___y_6934_;
goto v___jp_6917_;
}
else
{
uint64_t v___x_6940_; uint64_t v___x_6941_; 
v___x_6940_ = 1ULL;
v___x_6941_ = lean_uint64_add(v___y_6934_, v___x_6940_);
v___y_6918_ = v___y_6932_;
v___y_6919_ = v_carry_6939_;
v___y_6920_ = v___y_6937_;
v___y_6921_ = v___y_6933_;
v___y_6922_ = v___y_6935_;
v___y_6923_ = v___y_6936_;
v___y_6924_ = v___x_6941_;
goto v___jp_6917_;
}
}
v___jp_6942_:
{
uint64_t v_position_6951_; uint64_t v___x_6952_; uint8_t v___x_6953_; 
v_position_6951_ = lean_uint64_add(v___y_6950_, v___y_6948_);
v___x_6952_ = 172ULL;
v___x_6953_ = lean_uint64_dec_lt(v_position_6951_, v___x_6952_);
if (v___x_6953_ == 0)
{
uint64_t v___x_6954_; uint8_t v___x_6955_; 
v___x_6954_ = 23ULL;
v___x_6955_ = lean_uint64_dec_lt(v___y_6950_, v___x_6954_);
if (v___x_6955_ == 0)
{
uint64_t v___x_6956_; uint8_t v___x_6957_; 
v___x_6956_ = lean_uint64_sub(v___y_6950_, v___x_6954_);
v___x_6957_ = lean_uint64_dec_eq(v___x_6956_, v___y_6949_);
if (v___x_6957_ == 0)
{
uint64_t v___x_6958_; uint8_t v___x_6959_; 
v___x_6958_ = 64ULL;
v___x_6959_ = lean_uint64_dec_lt(v___x_6956_, v___x_6958_);
if (v___x_6959_ == 0)
{
uint8_t v___x_6960_; 
v___x_6960_ = lean_uint64_dec_eq(v___x_6956_, v___x_6958_);
if (v___x_6960_ == 0)
{
lean_dec(v___y_6943_);
v___y_6932_ = v___y_6944_;
v___y_6933_ = v___y_6946_;
v___y_6934_ = v_position_6951_;
v___y_6935_ = v___y_6947_;
v___y_6936_ = v___y_6949_;
v___y_6937_ = v___y_6949_;
goto v___jp_6931_;
}
else
{
uint64_t v___x_6961_; uint64_t v___x_6962_; uint8_t v___x_6963_; 
v___x_6961_ = 9223372036854775808ULL;
v___x_6962_ = lean_unbox_uint64(v___y_6943_);
lean_dec(v___y_6943_);
v___x_6963_ = lean_uint64_dec_lt(v___x_6961_, v___x_6962_);
if (v___x_6963_ == 0)
{
v___y_6932_ = v___y_6944_;
v___y_6933_ = v___y_6946_;
v___y_6934_ = v_position_6951_;
v___y_6935_ = v___y_6947_;
v___y_6936_ = v___y_6949_;
v___y_6937_ = v___y_6949_;
goto v___jp_6931_;
}
else
{
uint64_t v___x_6964_; 
v___x_6964_ = 1ULL;
v___y_6932_ = v___y_6944_;
v___y_6933_ = v___y_6946_;
v___y_6934_ = v_position_6951_;
v___y_6935_ = v___y_6947_;
v___y_6936_ = v___y_6949_;
v___y_6937_ = v___x_6964_;
goto v___jp_6931_;
}
}
}
else
{
uint64_t v___x_6965_; uint64_t v_quotient_6966_; uint64_t v___x_6967_; uint64_t v___x_6968_; uint64_t v___x_6969_; uint64_t v___x_6970_; uint64_t v_remainder_6971_; uint64_t v___x_6972_; uint64_t v_half_6973_; uint8_t v___x_6974_; 
v___x_6965_ = lean_unbox_uint64(v___y_6943_);
v_quotient_6966_ = lean_uint64_shift_right(v___x_6965_, v___x_6956_);
v___x_6967_ = 1ULL;
v___x_6968_ = lean_uint64_shift_left(v___x_6967_, v___x_6956_);
v___x_6969_ = lean_uint64_sub(v___x_6968_, v___x_6967_);
v___x_6970_ = lean_unbox_uint64(v___y_6943_);
lean_dec(v___y_6943_);
v_remainder_6971_ = lean_uint64_land(v___x_6970_, v___x_6969_);
v___x_6972_ = lean_uint64_sub(v___x_6956_, v___x_6967_);
v_half_6973_ = lean_uint64_shift_left(v___x_6967_, v___x_6972_);
v___x_6974_ = lean_uint64_dec_lt(v_remainder_6971_, v_half_6973_);
if (v___x_6974_ == 0)
{
uint8_t v___x_6975_; 
v___x_6975_ = lean_uint64_dec_lt(v_half_6973_, v_remainder_6971_);
if (v___x_6975_ == 0)
{
uint64_t v___x_6976_; uint8_t v___x_6977_; 
v___x_6976_ = lean_uint64_land(v_quotient_6966_, v___x_6967_);
v___x_6977_ = lean_uint64_dec_eq(v___x_6976_, v___y_6949_);
if (v___x_6977_ == 0)
{
uint64_t v___x_6978_; 
v___x_6978_ = lean_uint64_add(v_quotient_6966_, v___x_6967_);
v___y_6932_ = v___y_6944_;
v___y_6933_ = v___y_6946_;
v___y_6934_ = v_position_6951_;
v___y_6935_ = v___y_6947_;
v___y_6936_ = v___y_6949_;
v___y_6937_ = v___x_6978_;
goto v___jp_6931_;
}
else
{
v___y_6932_ = v___y_6944_;
v___y_6933_ = v___y_6946_;
v___y_6934_ = v_position_6951_;
v___y_6935_ = v___y_6947_;
v___y_6936_ = v___y_6949_;
v___y_6937_ = v_quotient_6966_;
goto v___jp_6931_;
}
}
else
{
uint64_t v___x_6979_; 
v___x_6979_ = lean_uint64_add(v_quotient_6966_, v___x_6967_);
v___y_6932_ = v___y_6944_;
v___y_6933_ = v___y_6946_;
v___y_6934_ = v_position_6951_;
v___y_6935_ = v___y_6947_;
v___y_6936_ = v___y_6949_;
v___y_6937_ = v___x_6979_;
goto v___jp_6931_;
}
}
else
{
v___y_6932_ = v___y_6944_;
v___y_6933_ = v___y_6946_;
v___y_6934_ = v_position_6951_;
v___y_6935_ = v___y_6947_;
v___y_6936_ = v___y_6949_;
v___y_6937_ = v_quotient_6966_;
goto v___jp_6931_;
}
}
}
else
{
uint64_t v___x_6980_; 
v___x_6980_ = lean_unbox_uint64(v___y_6943_);
lean_dec(v___y_6943_);
v___y_6932_ = v___y_6944_;
v___y_6933_ = v___y_6946_;
v___y_6934_ = v_position_6951_;
v___y_6935_ = v___y_6947_;
v___y_6936_ = v___y_6949_;
v___y_6937_ = v___x_6980_;
goto v___jp_6931_;
}
}
else
{
uint64_t v___x_6981_; uint64_t v___x_6982_; uint64_t v___x_6983_; 
v___x_6981_ = lean_uint64_sub(v___x_6954_, v___y_6950_);
v___x_6982_ = lean_unbox_uint64(v___y_6943_);
lean_dec(v___y_6943_);
v___x_6983_ = lean_uint64_shift_left(v___x_6982_, v___x_6981_);
v___y_6932_ = v___y_6944_;
v___y_6933_ = v___y_6946_;
v___y_6934_ = v_position_6951_;
v___y_6935_ = v___y_6947_;
v___y_6936_ = v___y_6949_;
v___y_6937_ = v___x_6983_;
goto v___jp_6931_;
}
}
else
{
uint8_t v___x_6984_; 
v___x_6984_ = lean_uint64_dec_lt(v___y_6948_, v___y_6945_);
if (v___x_6984_ == 0)
{
uint64_t v___x_6985_; uint64_t v___x_6986_; uint64_t v___x_6987_; 
v___x_6985_ = lean_uint64_sub(v___y_6948_, v___y_6945_);
v___x_6986_ = lean_unbox_uint64(v___y_6943_);
lean_dec(v___y_6943_);
v___x_6987_ = lean_uint64_shift_left(v___x_6986_, v___x_6985_);
v___y_6865_ = v___y_6946_;
v___y_6866_ = v___y_6949_;
v___y_6867_ = v___x_6987_;
goto v___jp_6864_;
}
else
{
uint64_t v___x_6988_; uint8_t v___x_6989_; 
v___x_6988_ = lean_uint64_sub(v___y_6945_, v___y_6948_);
v___x_6989_ = lean_uint64_dec_eq(v___x_6988_, v___y_6949_);
if (v___x_6989_ == 0)
{
uint64_t v___x_6990_; uint8_t v___x_6991_; 
v___x_6990_ = 64ULL;
v___x_6991_ = lean_uint64_dec_lt(v___x_6988_, v___x_6990_);
if (v___x_6991_ == 0)
{
uint8_t v___x_6992_; 
v___x_6992_ = lean_uint64_dec_eq(v___x_6988_, v___x_6990_);
if (v___x_6992_ == 0)
{
lean_dec(v___y_6943_);
v___y_6865_ = v___y_6946_;
v___y_6866_ = v___y_6949_;
v___y_6867_ = v___y_6949_;
goto v___jp_6864_;
}
else
{
uint64_t v___x_6993_; uint64_t v___x_6994_; uint8_t v___x_6995_; 
v___x_6993_ = 9223372036854775808ULL;
v___x_6994_ = lean_unbox_uint64(v___y_6943_);
lean_dec(v___y_6943_);
v___x_6995_ = lean_uint64_dec_lt(v___x_6993_, v___x_6994_);
if (v___x_6995_ == 0)
{
v___y_6865_ = v___y_6946_;
v___y_6866_ = v___y_6949_;
v___y_6867_ = v___y_6949_;
goto v___jp_6864_;
}
else
{
uint64_t v___x_6996_; 
v___x_6996_ = 1ULL;
v___y_6865_ = v___y_6946_;
v___y_6866_ = v___y_6949_;
v___y_6867_ = v___x_6996_;
goto v___jp_6864_;
}
}
}
else
{
uint64_t v___x_6997_; uint64_t v_quotient_6998_; uint64_t v___x_6999_; uint64_t v___x_7000_; uint64_t v___x_7001_; uint64_t v___x_7002_; uint64_t v_remainder_7003_; uint64_t v___x_7004_; uint64_t v_half_7005_; uint8_t v___x_7006_; 
v___x_6997_ = lean_unbox_uint64(v___y_6943_);
v_quotient_6998_ = lean_uint64_shift_right(v___x_6997_, v___x_6988_);
v___x_6999_ = 1ULL;
v___x_7000_ = lean_uint64_shift_left(v___x_6999_, v___x_6988_);
v___x_7001_ = lean_uint64_sub(v___x_7000_, v___x_6999_);
v___x_7002_ = lean_unbox_uint64(v___y_6943_);
lean_dec(v___y_6943_);
v_remainder_7003_ = lean_uint64_land(v___x_7002_, v___x_7001_);
v___x_7004_ = lean_uint64_sub(v___x_6988_, v___x_6999_);
v_half_7005_ = lean_uint64_shift_left(v___x_6999_, v___x_7004_);
v___x_7006_ = lean_uint64_dec_lt(v_remainder_7003_, v_half_7005_);
if (v___x_7006_ == 0)
{
uint8_t v___x_7007_; 
v___x_7007_ = lean_uint64_dec_lt(v_half_7005_, v_remainder_7003_);
if (v___x_7007_ == 0)
{
uint64_t v___x_7008_; uint8_t v___x_7009_; 
v___x_7008_ = lean_uint64_land(v_quotient_6998_, v___x_6999_);
v___x_7009_ = lean_uint64_dec_eq(v___x_7008_, v___y_6949_);
if (v___x_7009_ == 0)
{
uint64_t v___x_7010_; 
v___x_7010_ = lean_uint64_add(v_quotient_6998_, v___x_6999_);
v___y_6865_ = v___y_6946_;
v___y_6866_ = v___y_6949_;
v___y_6867_ = v___x_7010_;
goto v___jp_6864_;
}
else
{
v___y_6865_ = v___y_6946_;
v___y_6866_ = v___y_6949_;
v___y_6867_ = v_quotient_6998_;
goto v___jp_6864_;
}
}
else
{
uint64_t v___x_7011_; 
v___x_7011_ = lean_uint64_add(v_quotient_6998_, v___x_6999_);
v___y_6865_ = v___y_6946_;
v___y_6866_ = v___y_6949_;
v___y_6867_ = v___x_7011_;
goto v___jp_6864_;
}
}
else
{
v___y_6865_ = v___y_6946_;
v___y_6866_ = v___y_6949_;
v___y_6867_ = v_quotient_6998_;
goto v___jp_6864_;
}
}
}
else
{
uint64_t v___x_7012_; 
v___x_7012_ = lean_unbox_uint64(v___y_6943_);
lean_dec(v___y_6943_);
v___y_6865_ = v___y_6946_;
v___y_6866_ = v___y_6949_;
v___y_6867_ = v___x_7012_;
goto v___jp_6864_;
}
}
}
}
v___jp_7013_:
{
uint64_t v___x_7023_; uint64_t v___x_7024_; uint8_t v___x_7025_; 
v___x_7023_ = 1ULL;
v___x_7024_ = lean_uint64_shift_right(v___y_7017_, v___x_7023_);
v___x_7025_ = lean_uint64_dec_eq(v___x_7024_, v___y_7021_);
if (v___x_7025_ == 0)
{
uint64_t v___x_7026_; 
v___x_7026_ = lean_uint64_add(v___y_7022_, v___x_7023_);
v___y_6943_ = v___y_7014_;
v___y_6944_ = v___y_7015_;
v___y_6945_ = v___y_7016_;
v___y_6946_ = v___y_7018_;
v___y_6947_ = v___y_7020_;
v___y_6948_ = v___y_7019_;
v___y_6949_ = v___y_7021_;
v___y_6950_ = v___x_7026_;
goto v___jp_6942_;
}
else
{
v___y_6943_ = v___y_7014_;
v___y_6944_ = v___y_7015_;
v___y_6945_ = v___y_7016_;
v___y_6946_ = v___y_7018_;
v___y_6947_ = v___y_7020_;
v___y_6948_ = v___y_7019_;
v___y_6949_ = v___y_7021_;
v___y_6950_ = v___y_7022_;
goto v___jp_6942_;
}
}
v___jp_7027_:
{
uint64_t v___x_7039_; uint8_t v___x_7040_; 
v___x_7039_ = lean_uint64_shift_right(v___y_7028_, v___y_7033_);
v___x_7040_ = lean_uint64_dec_eq(v___x_7039_, v___y_7037_);
if (v___x_7040_ == 0)
{
uint64_t v___x_7041_; 
v___x_7041_ = lean_uint64_add(v___y_7031_, v___y_7033_);
v___y_7014_ = v___y_7029_;
v___y_7015_ = v___y_7030_;
v___y_7016_ = v___y_7032_;
v___y_7017_ = v___y_7038_;
v___y_7018_ = v___y_7034_;
v___y_7019_ = v___y_7036_;
v___y_7020_ = v___y_7035_;
v___y_7021_ = v___y_7037_;
v___y_7022_ = v___x_7041_;
goto v___jp_7013_;
}
else
{
v___y_7014_ = v___y_7029_;
v___y_7015_ = v___y_7030_;
v___y_7016_ = v___y_7032_;
v___y_7017_ = v___y_7038_;
v___y_7018_ = v___y_7034_;
v___y_7019_ = v___y_7036_;
v___y_7020_ = v___y_7035_;
v___y_7021_ = v___y_7037_;
v___y_7022_ = v___y_7031_;
goto v___jp_7013_;
}
}
v___jp_7042_:
{
uint64_t v___x_7052_; uint64_t v___x_7053_; uint8_t v___x_7054_; 
v___x_7052_ = 2ULL;
v___x_7053_ = lean_uint64_shift_right(v___y_7043_, v___x_7052_);
v___x_7054_ = lean_uint64_dec_eq(v___x_7053_, v___y_7050_);
if (v___x_7054_ == 0)
{
v___y_7028_ = v___y_7043_;
v___y_7029_ = v___y_7044_;
v___y_7030_ = v___y_7045_;
v___y_7031_ = v___y_7051_;
v___y_7032_ = v___y_7046_;
v___y_7033_ = v___x_7052_;
v___y_7034_ = v___y_7047_;
v___y_7035_ = v___y_7049_;
v___y_7036_ = v___y_7048_;
v___y_7037_ = v___y_7050_;
v___y_7038_ = v___x_7053_;
goto v___jp_7027_;
}
else
{
v___y_7028_ = v___y_7043_;
v___y_7029_ = v___y_7044_;
v___y_7030_ = v___y_7045_;
v___y_7031_ = v___y_7051_;
v___y_7032_ = v___y_7046_;
v___y_7033_ = v___x_7052_;
v___y_7034_ = v___y_7047_;
v___y_7035_ = v___y_7049_;
v___y_7036_ = v___y_7048_;
v___y_7037_ = v___y_7050_;
v___y_7038_ = v___y_7043_;
goto v___jp_7027_;
}
}
v___jp_7055_:
{
uint64_t v___x_7067_; uint8_t v___x_7068_; 
v___x_7067_ = lean_uint64_shift_right(v___y_7064_, v___y_7061_);
v___x_7068_ = lean_uint64_dec_eq(v___x_7067_, v___y_7065_);
if (v___x_7068_ == 0)
{
uint64_t v___x_7069_; 
v___x_7069_ = lean_uint64_add(v___y_7059_, v___y_7061_);
v___y_7043_ = v___y_7066_;
v___y_7044_ = v___y_7056_;
v___y_7045_ = v___y_7057_;
v___y_7046_ = v___y_7058_;
v___y_7047_ = v___y_7060_;
v___y_7048_ = v___y_7063_;
v___y_7049_ = v___y_7062_;
v___y_7050_ = v___y_7065_;
v___y_7051_ = v___x_7069_;
goto v___jp_7042_;
}
else
{
v___y_7043_ = v___y_7066_;
v___y_7044_ = v___y_7056_;
v___y_7045_ = v___y_7057_;
v___y_7046_ = v___y_7058_;
v___y_7047_ = v___y_7060_;
v___y_7048_ = v___y_7063_;
v___y_7049_ = v___y_7062_;
v___y_7050_ = v___y_7065_;
v___y_7051_ = v___y_7059_;
goto v___jp_7042_;
}
}
v___jp_7070_:
{
uint64_t v___x_7080_; uint64_t v___x_7081_; uint8_t v___x_7082_; 
v___x_7080_ = 4ULL;
v___x_7081_ = lean_uint64_shift_right(v___y_7077_, v___x_7080_);
v___x_7082_ = lean_uint64_dec_eq(v___x_7081_, v___y_7078_);
if (v___x_7082_ == 0)
{
v___y_7056_ = v___y_7071_;
v___y_7057_ = v___y_7072_;
v___y_7058_ = v___y_7073_;
v___y_7059_ = v___y_7079_;
v___y_7060_ = v___y_7074_;
v___y_7061_ = v___x_7080_;
v___y_7062_ = v___y_7076_;
v___y_7063_ = v___y_7075_;
v___y_7064_ = v___y_7077_;
v___y_7065_ = v___y_7078_;
v___y_7066_ = v___x_7081_;
goto v___jp_7055_;
}
else
{
v___y_7056_ = v___y_7071_;
v___y_7057_ = v___y_7072_;
v___y_7058_ = v___y_7073_;
v___y_7059_ = v___y_7079_;
v___y_7060_ = v___y_7074_;
v___y_7061_ = v___x_7080_;
v___y_7062_ = v___y_7076_;
v___y_7063_ = v___y_7075_;
v___y_7064_ = v___y_7077_;
v___y_7065_ = v___y_7078_;
v___y_7066_ = v___y_7077_;
goto v___jp_7055_;
}
}
v___jp_7083_:
{
uint64_t v___x_7095_; uint8_t v___x_7096_; 
v___x_7095_ = lean_uint64_shift_right(v___y_7091_, v___y_7088_);
v___x_7096_ = lean_uint64_dec_eq(v___x_7095_, v___y_7093_);
if (v___x_7096_ == 0)
{
uint64_t v___x_7097_; 
v___x_7097_ = lean_uint64_add(v___y_7092_, v___y_7088_);
v___y_7071_ = v___y_7084_;
v___y_7072_ = v___y_7085_;
v___y_7073_ = v___y_7086_;
v___y_7074_ = v___y_7087_;
v___y_7075_ = v___y_7090_;
v___y_7076_ = v___y_7089_;
v___y_7077_ = v___y_7094_;
v___y_7078_ = v___y_7093_;
v___y_7079_ = v___x_7097_;
goto v___jp_7070_;
}
else
{
v___y_7071_ = v___y_7084_;
v___y_7072_ = v___y_7085_;
v___y_7073_ = v___y_7086_;
v___y_7074_ = v___y_7087_;
v___y_7075_ = v___y_7090_;
v___y_7076_ = v___y_7089_;
v___y_7077_ = v___y_7094_;
v___y_7078_ = v___y_7093_;
v___y_7079_ = v___y_7092_;
goto v___jp_7070_;
}
}
v___jp_7098_:
{
uint64_t v___x_7108_; uint64_t v___x_7109_; uint8_t v___x_7110_; 
v___x_7108_ = 8ULL;
v___x_7109_ = lean_uint64_shift_right(v___y_7105_, v___x_7108_);
v___x_7110_ = lean_uint64_dec_eq(v___x_7109_, v___y_7106_);
if (v___x_7110_ == 0)
{
v___y_7084_ = v___y_7099_;
v___y_7085_ = v___y_7100_;
v___y_7086_ = v___y_7101_;
v___y_7087_ = v___y_7102_;
v___y_7088_ = v___x_7108_;
v___y_7089_ = v___y_7104_;
v___y_7090_ = v___y_7103_;
v___y_7091_ = v___y_7105_;
v___y_7092_ = v___y_7107_;
v___y_7093_ = v___y_7106_;
v___y_7094_ = v___x_7109_;
goto v___jp_7083_;
}
else
{
v___y_7084_ = v___y_7099_;
v___y_7085_ = v___y_7100_;
v___y_7086_ = v___y_7101_;
v___y_7087_ = v___y_7102_;
v___y_7088_ = v___x_7108_;
v___y_7089_ = v___y_7104_;
v___y_7090_ = v___y_7103_;
v___y_7091_ = v___y_7105_;
v___y_7092_ = v___y_7107_;
v___y_7093_ = v___y_7106_;
v___y_7094_ = v___y_7105_;
goto v___jp_7083_;
}
}
v___jp_7111_:
{
uint64_t v___x_7123_; uint8_t v___x_7124_; 
v___x_7123_ = lean_uint64_shift_right(v___y_7112_, v___y_7115_);
v___x_7124_ = lean_uint64_dec_eq(v___x_7123_, v___y_7121_);
if (v___x_7124_ == 0)
{
uint64_t v___x_7125_; 
v___x_7125_ = lean_uint64_add(v___y_7117_, v___y_7115_);
v___y_7099_ = v___y_7113_;
v___y_7100_ = v___y_7114_;
v___y_7101_ = v___y_7116_;
v___y_7102_ = v___y_7118_;
v___y_7103_ = v___y_7120_;
v___y_7104_ = v___y_7119_;
v___y_7105_ = v___y_7122_;
v___y_7106_ = v___y_7121_;
v___y_7107_ = v___x_7125_;
goto v___jp_7098_;
}
else
{
v___y_7099_ = v___y_7113_;
v___y_7100_ = v___y_7114_;
v___y_7101_ = v___y_7116_;
v___y_7102_ = v___y_7118_;
v___y_7103_ = v___y_7120_;
v___y_7104_ = v___y_7119_;
v___y_7105_ = v___y_7122_;
v___y_7106_ = v___y_7121_;
v___y_7107_ = v___y_7117_;
goto v___jp_7098_;
}
}
v___jp_7126_:
{
uint64_t v___x_7136_; uint64_t v___x_7137_; uint8_t v___x_7138_; 
v___x_7136_ = 16ULL;
v___x_7137_ = lean_uint64_shift_right(v___y_7128_, v___x_7136_);
v___x_7138_ = lean_uint64_dec_eq(v___x_7137_, v___y_7134_);
if (v___x_7138_ == 0)
{
v___y_7112_ = v___y_7128_;
v___y_7113_ = v___y_7127_;
v___y_7114_ = v___y_7129_;
v___y_7115_ = v___x_7136_;
v___y_7116_ = v___y_7130_;
v___y_7117_ = v___y_7135_;
v___y_7118_ = v___y_7131_;
v___y_7119_ = v___y_7133_;
v___y_7120_ = v___y_7132_;
v___y_7121_ = v___y_7134_;
v___y_7122_ = v___x_7137_;
goto v___jp_7111_;
}
else
{
v___y_7112_ = v___y_7128_;
v___y_7113_ = v___y_7127_;
v___y_7114_ = v___y_7129_;
v___y_7115_ = v___x_7136_;
v___y_7116_ = v___y_7130_;
v___y_7117_ = v___y_7135_;
v___y_7118_ = v___y_7131_;
v___y_7119_ = v___y_7133_;
v___y_7120_ = v___y_7132_;
v___y_7121_ = v___y_7134_;
v___y_7122_ = v___y_7128_;
goto v___jp_7111_;
}
}
v___jp_7139_:
{
uint64_t v___x_7149_; uint64_t v___x_7150_; uint8_t v___x_7151_; 
v___x_7149_ = lean_unbox_uint64(v___y_7140_);
v___x_7150_ = lean_uint64_shift_right(v___x_7149_, v___y_7143_);
v___x_7151_ = lean_uint64_dec_eq(v___x_7150_, v___y_7147_);
if (v___x_7151_ == 0)
{
v___y_7127_ = v___y_7140_;
v___y_7128_ = v___y_7148_;
v___y_7129_ = v___y_7141_;
v___y_7130_ = v___y_7142_;
v___y_7131_ = v___y_7144_;
v___y_7132_ = v___y_7146_;
v___y_7133_ = v___y_7145_;
v___y_7134_ = v___y_7147_;
v___y_7135_ = v___y_7143_;
goto v___jp_7126_;
}
else
{
v___y_7127_ = v___y_7140_;
v___y_7128_ = v___y_7148_;
v___y_7129_ = v___y_7141_;
v___y_7130_ = v___y_7142_;
v___y_7131_ = v___y_7144_;
v___y_7132_ = v___y_7146_;
v___y_7133_ = v___y_7145_;
v___y_7134_ = v___y_7147_;
v___y_7135_ = v___y_7147_;
goto v___jp_7126_;
}
}
v___jp_7152_:
{
uint64_t v___x_7158_; uint64_t v___x_7159_; uint8_t v___x_7160_; 
v___x_7158_ = 0ULL;
v___x_7159_ = lean_unbox_uint64(v_snd_7157_);
v___x_7160_ = lean_uint64_dec_eq(v___x_7159_, v___x_7158_);
if (v___x_7160_ == 0)
{
uint64_t v___x_7161_; uint64_t v___x_7162_; uint64_t v___x_7163_; uint64_t v___x_7164_; uint64_t v___x_7165_; uint8_t v___x_7166_; 
v___x_7161_ = 149ULL;
v___x_7162_ = lean_uint64_add(v___y_7155_, v___x_7161_);
v___x_7163_ = 32ULL;
v___x_7164_ = lean_unbox_uint64(v_snd_7157_);
v___x_7165_ = lean_uint64_shift_right(v___x_7164_, v___x_7163_);
v___x_7166_ = lean_uint64_dec_eq(v___x_7165_, v___x_7158_);
if (v___x_7166_ == 0)
{
v___y_7140_ = v_snd_7157_;
v___y_7141_ = v___y_7153_;
v___y_7142_ = v___x_7161_;
v___y_7143_ = v___x_7163_;
v___y_7144_ = v_fst_7156_;
v___y_7145_ = v___y_7154_;
v___y_7146_ = v___x_7162_;
v___y_7147_ = v___x_7158_;
v___y_7148_ = v___x_7165_;
goto v___jp_7139_;
}
else
{
uint64_t v___x_7167_; 
v___x_7167_ = lean_unbox_uint64(v_snd_7157_);
v___y_7140_ = v_snd_7157_;
v___y_7141_ = v___y_7153_;
v___y_7142_ = v___x_7161_;
v___y_7143_ = v___x_7163_;
v___y_7144_ = v_fst_7156_;
v___y_7145_ = v___y_7154_;
v___y_7146_ = v___x_7162_;
v___y_7147_ = v___x_7158_;
v___y_7148_ = v___x_7167_;
goto v___jp_7139_;
}
}
else
{
uint8_t v___x_7168_; 
lean_dec(v_snd_7157_);
v___x_7168_ = lean_unbox(v_fst_7156_);
lean_dec(v_fst_7156_);
if (v___x_7168_ == 0)
{
uint32_t v___x_7169_; 
v___x_7169_ = 0;
return v___x_7169_;
}
else
{
uint32_t v___x_7170_; 
v___x_7170_ = 2147483648;
return v___x_7170_;
}
}
}
v___jp_7171_:
{
uint32_t v___x_7174_; uint32_t v___x_7175_; uint32_t v___x_7176_; 
v___x_7174_ = 8388607;
v___x_7175_ = lean_uint32_land(v___y_7172_, v___x_7174_);
v___x_7176_ = lean_uint32_lor(v___y_7173_, v___x_7175_);
return v___x_7176_;
}
v___jp_7177_:
{
uint8_t v___x_7181_; 
v___x_7181_ = lean_uint64_dec_eq(v___y_7180_, v___y_7179_);
if (v___x_7181_ == 0)
{
uint64_t v___x_7182_; uint8_t v___x_7183_; 
v___x_7182_ = 8388608ULL;
v___x_7183_ = lean_uint64_dec_eq(v___y_7180_, v___x_7182_);
if (v___x_7183_ == 0)
{
uint32_t v___x_7184_; uint8_t v___x_7185_; 
v___x_7184_ = lean_uint64_to_uint32(v___y_7180_);
v___x_7185_ = lean_unbox(v___y_7178_);
lean_dec(v___y_7178_);
if (v___x_7185_ == 0)
{
uint32_t v___x_7186_; 
v___x_7186_ = 0;
v___y_7172_ = v___x_7184_;
v___y_7173_ = v___x_7186_;
goto v___jp_7171_;
}
else
{
uint32_t v___x_7187_; 
v___x_7187_ = 2147483648;
v___y_7172_ = v___x_7184_;
v___y_7173_ = v___x_7187_;
goto v___jp_7171_;
}
}
else
{
uint8_t v___x_7188_; 
v___x_7188_ = lean_unbox(v___y_7178_);
lean_dec(v___y_7178_);
if (v___x_7188_ == 0)
{
uint32_t v___x_7189_; 
v___x_7189_ = 0;
v___y_5091_ = v___x_7189_;
goto v___jp_5090_;
}
else
{
uint32_t v___x_7190_; 
v___x_7190_ = 2147483648;
v___y_5091_ = v___x_7190_;
goto v___jp_5090_;
}
}
}
else
{
uint8_t v___x_7191_; 
v___x_7191_ = lean_unbox(v___y_7178_);
lean_dec(v___y_7178_);
if (v___x_7191_ == 0)
{
uint32_t v___x_7192_; 
v___x_7192_ = 0;
return v___x_7192_;
}
else
{
uint32_t v___x_7193_; 
v___x_7193_ = 2147483648;
return v___x_7193_;
}
}
}
v___jp_7194_:
{
uint32_t v___x_7200_; uint32_t v___x_7201_; uint32_t v___x_7202_; uint32_t v___x_7203_; uint32_t v___x_7204_; uint32_t v___x_7205_; 
v___x_7200_ = lean_uint32_land(v___y_7195_, v___y_7197_);
v___x_7201_ = lean_uint32_shift_left(v___x_7200_, v___y_7198_);
v___x_7202_ = lean_uint32_lor(v___y_7199_, v___x_7201_);
v___x_7203_ = 8388607;
v___x_7204_ = lean_uint32_land(v___y_7196_, v___x_7203_);
v___x_7205_ = lean_uint32_lor(v___x_7202_, v___x_7204_);
return v___x_7205_;
}
v___jp_7206_:
{
uint8_t v___x_7212_; 
v___x_7212_ = lean_unbox(v___y_7209_);
lean_dec(v___y_7209_);
if (v___x_7212_ == 0)
{
uint32_t v___x_7213_; 
v___x_7213_ = 0;
v___y_7195_ = v___y_7207_;
v___y_7196_ = v___y_7211_;
v___y_7197_ = v___y_7208_;
v___y_7198_ = v___y_7210_;
v___y_7199_ = v___x_7213_;
goto v___jp_7194_;
}
else
{
uint32_t v___x_7214_; 
v___x_7214_ = 2147483648;
v___y_7195_ = v___y_7207_;
v___y_7196_ = v___y_7211_;
v___y_7197_ = v___y_7208_;
v___y_7198_ = v___y_7210_;
v___y_7199_ = v___x_7214_;
goto v___jp_7194_;
}
}
v___jp_7215_:
{
uint64_t v___x_7222_; uint64_t v_encodedExponent_7223_; uint32_t v___x_7224_; uint64_t v___x_7225_; uint8_t v___x_7226_; 
v___x_7222_ = 171ULL;
v_encodedExponent_7223_ = lean_uint64_sub(v___y_7218_, v___x_7222_);
v___x_7224_ = lean_uint64_to_uint32(v_encodedExponent_7223_);
v___x_7225_ = 8388608ULL;
v___x_7226_ = lean_uint64_dec_lt(v___y_7221_, v___x_7225_);
if (v___x_7226_ == 0)
{
uint64_t v___x_7227_; uint32_t v___x_7228_; 
v___x_7227_ = lean_uint64_sub(v___y_7221_, v___x_7225_);
v___x_7228_ = lean_uint64_to_uint32(v___x_7227_);
v___y_7207_ = v___x_7224_;
v___y_7208_ = v___y_7216_;
v___y_7209_ = v___y_7217_;
v___y_7210_ = v___y_7220_;
v___y_7211_ = v___x_7228_;
goto v___jp_7206_;
}
else
{
uint32_t v___x_7229_; 
v___x_7229_ = lean_uint64_to_uint32(v___y_7219_);
v___y_7207_ = v___x_7224_;
v___y_7208_ = v___y_7216_;
v___y_7209_ = v___y_7217_;
v___y_7210_ = v___y_7220_;
v___y_7211_ = v___x_7229_;
goto v___jp_7206_;
}
}
v___jp_7230_:
{
uint64_t v___x_7238_; uint8_t v___x_7239_; 
v___x_7238_ = 425ULL;
v___x_7239_ = lean_uint64_dec_lt(v___x_7238_, v___y_7237_);
if (v___x_7239_ == 0)
{
if (v___y_7234_ == 0)
{
v___y_7216_ = v___y_7231_;
v___y_7217_ = v___y_7232_;
v___y_7218_ = v___y_7237_;
v___y_7219_ = v___y_7235_;
v___y_7220_ = v___y_7236_;
v___y_7221_ = v___y_7233_;
goto v___jp_7215_;
}
else
{
uint64_t v___x_7240_; 
v___x_7240_ = 8388608ULL;
v___y_7216_ = v___y_7231_;
v___y_7217_ = v___y_7232_;
v___y_7218_ = v___y_7237_;
v___y_7219_ = v___y_7235_;
v___y_7220_ = v___y_7236_;
v___y_7221_ = v___x_7240_;
goto v___jp_7215_;
}
}
else
{
uint8_t v___x_7241_; 
v___x_7241_ = lean_unbox(v___y_7232_);
lean_dec(v___y_7232_);
if (v___x_7241_ == 0)
{
uint32_t v___x_7242_; 
v___x_7242_ = 2139095040;
return v___x_7242_;
}
else
{
uint32_t v___x_7243_; 
v___x_7243_ = 4286578688;
return v___x_7243_;
}
}
}
v___jp_7244_:
{
uint64_t v___x_7251_; uint8_t v_carry_7252_; 
v___x_7251_ = 16777216ULL;
v_carry_7252_ = lean_uint64_dec_eq(v___y_7250_, v___x_7251_);
if (v_carry_7252_ == 0)
{
v___y_7231_ = v___y_7246_;
v___y_7232_ = v___y_7247_;
v___y_7233_ = v___y_7250_;
v___y_7234_ = v_carry_7252_;
v___y_7235_ = v___y_7248_;
v___y_7236_ = v___y_7249_;
v___y_7237_ = v___y_7245_;
goto v___jp_7230_;
}
else
{
uint64_t v___x_7253_; uint64_t v___x_7254_; 
v___x_7253_ = 1ULL;
v___x_7254_ = lean_uint64_add(v___y_7245_, v___x_7253_);
v___y_7231_ = v___y_7246_;
v___y_7232_ = v___y_7247_;
v___y_7233_ = v___y_7250_;
v___y_7234_ = v_carry_7252_;
v___y_7235_ = v___y_7248_;
v___y_7236_ = v___y_7249_;
v___y_7237_ = v___x_7254_;
goto v___jp_7230_;
}
}
v___jp_7255_:
{
uint64_t v_position_7264_; uint64_t v___x_7265_; uint8_t v___x_7266_; 
v_position_7264_ = lean_uint64_add(v___y_7263_, v___y_7260_);
v___x_7265_ = 172ULL;
v___x_7266_ = lean_uint64_dec_lt(v_position_7264_, v___x_7265_);
if (v___x_7266_ == 0)
{
uint64_t v___x_7267_; uint8_t v___x_7268_; 
v___x_7267_ = 23ULL;
v___x_7268_ = lean_uint64_dec_lt(v___y_7263_, v___x_7267_);
if (v___x_7268_ == 0)
{
uint64_t v___x_7269_; uint8_t v___x_7270_; 
v___x_7269_ = lean_uint64_sub(v___y_7263_, v___x_7267_);
v___x_7270_ = lean_uint64_dec_eq(v___x_7269_, v___y_7261_);
if (v___x_7270_ == 0)
{
uint64_t v___x_7271_; uint8_t v___x_7272_; 
v___x_7271_ = 64ULL;
v___x_7272_ = lean_uint64_dec_lt(v___x_7269_, v___x_7271_);
if (v___x_7272_ == 0)
{
uint8_t v___x_7273_; 
v___x_7273_ = lean_uint64_dec_eq(v___x_7269_, v___x_7271_);
if (v___x_7273_ == 0)
{
lean_dec(v___y_7258_);
v___y_7245_ = v_position_7264_;
v___y_7246_ = v___y_7256_;
v___y_7247_ = v___y_7257_;
v___y_7248_ = v___y_7261_;
v___y_7249_ = v___y_7262_;
v___y_7250_ = v___y_7261_;
goto v___jp_7244_;
}
else
{
uint64_t v___x_7274_; uint64_t v___x_7275_; uint8_t v___x_7276_; 
v___x_7274_ = 9223372036854775808ULL;
v___x_7275_ = lean_unbox_uint64(v___y_7258_);
lean_dec(v___y_7258_);
v___x_7276_ = lean_uint64_dec_lt(v___x_7274_, v___x_7275_);
if (v___x_7276_ == 0)
{
v___y_7245_ = v_position_7264_;
v___y_7246_ = v___y_7256_;
v___y_7247_ = v___y_7257_;
v___y_7248_ = v___y_7261_;
v___y_7249_ = v___y_7262_;
v___y_7250_ = v___y_7261_;
goto v___jp_7244_;
}
else
{
uint64_t v___x_7277_; 
v___x_7277_ = 1ULL;
v___y_7245_ = v_position_7264_;
v___y_7246_ = v___y_7256_;
v___y_7247_ = v___y_7257_;
v___y_7248_ = v___y_7261_;
v___y_7249_ = v___y_7262_;
v___y_7250_ = v___x_7277_;
goto v___jp_7244_;
}
}
}
else
{
uint64_t v___x_7278_; uint64_t v_quotient_7279_; uint64_t v___x_7280_; uint64_t v___x_7281_; uint64_t v___x_7282_; uint64_t v___x_7283_; uint64_t v_remainder_7284_; uint64_t v___x_7285_; uint64_t v_half_7286_; uint8_t v___x_7287_; 
v___x_7278_ = lean_unbox_uint64(v___y_7258_);
v_quotient_7279_ = lean_uint64_shift_right(v___x_7278_, v___x_7269_);
v___x_7280_ = 1ULL;
v___x_7281_ = lean_uint64_shift_left(v___x_7280_, v___x_7269_);
v___x_7282_ = lean_uint64_sub(v___x_7281_, v___x_7280_);
v___x_7283_ = lean_unbox_uint64(v___y_7258_);
lean_dec(v___y_7258_);
v_remainder_7284_ = lean_uint64_land(v___x_7283_, v___x_7282_);
v___x_7285_ = lean_uint64_sub(v___x_7269_, v___x_7280_);
v_half_7286_ = lean_uint64_shift_left(v___x_7280_, v___x_7285_);
v___x_7287_ = lean_uint64_dec_lt(v_remainder_7284_, v_half_7286_);
if (v___x_7287_ == 0)
{
uint8_t v___x_7288_; 
v___x_7288_ = lean_uint64_dec_lt(v_half_7286_, v_remainder_7284_);
if (v___x_7288_ == 0)
{
uint64_t v___x_7289_; uint8_t v___x_7290_; 
v___x_7289_ = lean_uint64_land(v_quotient_7279_, v___x_7280_);
v___x_7290_ = lean_uint64_dec_eq(v___x_7289_, v___y_7261_);
if (v___x_7290_ == 0)
{
uint64_t v___x_7291_; 
v___x_7291_ = lean_uint64_add(v_quotient_7279_, v___x_7280_);
v___y_7245_ = v_position_7264_;
v___y_7246_ = v___y_7256_;
v___y_7247_ = v___y_7257_;
v___y_7248_ = v___y_7261_;
v___y_7249_ = v___y_7262_;
v___y_7250_ = v___x_7291_;
goto v___jp_7244_;
}
else
{
v___y_7245_ = v_position_7264_;
v___y_7246_ = v___y_7256_;
v___y_7247_ = v___y_7257_;
v___y_7248_ = v___y_7261_;
v___y_7249_ = v___y_7262_;
v___y_7250_ = v_quotient_7279_;
goto v___jp_7244_;
}
}
else
{
uint64_t v___x_7292_; 
v___x_7292_ = lean_uint64_add(v_quotient_7279_, v___x_7280_);
v___y_7245_ = v_position_7264_;
v___y_7246_ = v___y_7256_;
v___y_7247_ = v___y_7257_;
v___y_7248_ = v___y_7261_;
v___y_7249_ = v___y_7262_;
v___y_7250_ = v___x_7292_;
goto v___jp_7244_;
}
}
else
{
v___y_7245_ = v_position_7264_;
v___y_7246_ = v___y_7256_;
v___y_7247_ = v___y_7257_;
v___y_7248_ = v___y_7261_;
v___y_7249_ = v___y_7262_;
v___y_7250_ = v_quotient_7279_;
goto v___jp_7244_;
}
}
}
else
{
uint64_t v___x_7293_; 
v___x_7293_ = lean_unbox_uint64(v___y_7258_);
lean_dec(v___y_7258_);
v___y_7245_ = v_position_7264_;
v___y_7246_ = v___y_7256_;
v___y_7247_ = v___y_7257_;
v___y_7248_ = v___y_7261_;
v___y_7249_ = v___y_7262_;
v___y_7250_ = v___x_7293_;
goto v___jp_7244_;
}
}
else
{
uint64_t v___x_7294_; uint64_t v___x_7295_; uint64_t v___x_7296_; 
v___x_7294_ = lean_uint64_sub(v___x_7267_, v___y_7263_);
v___x_7295_ = lean_unbox_uint64(v___y_7258_);
lean_dec(v___y_7258_);
v___x_7296_ = lean_uint64_shift_left(v___x_7295_, v___x_7294_);
v___y_7245_ = v_position_7264_;
v___y_7246_ = v___y_7256_;
v___y_7247_ = v___y_7257_;
v___y_7248_ = v___y_7261_;
v___y_7249_ = v___y_7262_;
v___y_7250_ = v___x_7296_;
goto v___jp_7244_;
}
}
else
{
uint8_t v___x_7297_; 
v___x_7297_ = lean_uint64_dec_lt(v___y_7260_, v___y_7259_);
if (v___x_7297_ == 0)
{
uint64_t v___x_7298_; uint64_t v___x_7299_; uint64_t v___x_7300_; 
v___x_7298_ = lean_uint64_sub(v___y_7260_, v___y_7259_);
v___x_7299_ = lean_unbox_uint64(v___y_7258_);
lean_dec(v___y_7258_);
v___x_7300_ = lean_uint64_shift_left(v___x_7299_, v___x_7298_);
v___y_7178_ = v___y_7257_;
v___y_7179_ = v___y_7261_;
v___y_7180_ = v___x_7300_;
goto v___jp_7177_;
}
else
{
uint64_t v___x_7301_; uint8_t v___x_7302_; 
v___x_7301_ = lean_uint64_sub(v___y_7259_, v___y_7260_);
v___x_7302_ = lean_uint64_dec_eq(v___x_7301_, v___y_7261_);
if (v___x_7302_ == 0)
{
uint64_t v___x_7303_; uint8_t v___x_7304_; 
v___x_7303_ = 64ULL;
v___x_7304_ = lean_uint64_dec_lt(v___x_7301_, v___x_7303_);
if (v___x_7304_ == 0)
{
uint8_t v___x_7305_; 
v___x_7305_ = lean_uint64_dec_eq(v___x_7301_, v___x_7303_);
if (v___x_7305_ == 0)
{
lean_dec(v___y_7258_);
v___y_7178_ = v___y_7257_;
v___y_7179_ = v___y_7261_;
v___y_7180_ = v___y_7261_;
goto v___jp_7177_;
}
else
{
uint64_t v___x_7306_; uint64_t v___x_7307_; uint8_t v___x_7308_; 
v___x_7306_ = 9223372036854775808ULL;
v___x_7307_ = lean_unbox_uint64(v___y_7258_);
lean_dec(v___y_7258_);
v___x_7308_ = lean_uint64_dec_lt(v___x_7306_, v___x_7307_);
if (v___x_7308_ == 0)
{
v___y_7178_ = v___y_7257_;
v___y_7179_ = v___y_7261_;
v___y_7180_ = v___y_7261_;
goto v___jp_7177_;
}
else
{
uint64_t v___x_7309_; 
v___x_7309_ = 1ULL;
v___y_7178_ = v___y_7257_;
v___y_7179_ = v___y_7261_;
v___y_7180_ = v___x_7309_;
goto v___jp_7177_;
}
}
}
else
{
uint64_t v___x_7310_; uint64_t v_quotient_7311_; uint64_t v___x_7312_; uint64_t v___x_7313_; uint64_t v___x_7314_; uint64_t v___x_7315_; uint64_t v_remainder_7316_; uint64_t v___x_7317_; uint64_t v_half_7318_; uint8_t v___x_7319_; 
v___x_7310_ = lean_unbox_uint64(v___y_7258_);
v_quotient_7311_ = lean_uint64_shift_right(v___x_7310_, v___x_7301_);
v___x_7312_ = 1ULL;
v___x_7313_ = lean_uint64_shift_left(v___x_7312_, v___x_7301_);
v___x_7314_ = lean_uint64_sub(v___x_7313_, v___x_7312_);
v___x_7315_ = lean_unbox_uint64(v___y_7258_);
lean_dec(v___y_7258_);
v_remainder_7316_ = lean_uint64_land(v___x_7315_, v___x_7314_);
v___x_7317_ = lean_uint64_sub(v___x_7301_, v___x_7312_);
v_half_7318_ = lean_uint64_shift_left(v___x_7312_, v___x_7317_);
v___x_7319_ = lean_uint64_dec_lt(v_remainder_7316_, v_half_7318_);
if (v___x_7319_ == 0)
{
uint8_t v___x_7320_; 
v___x_7320_ = lean_uint64_dec_lt(v_half_7318_, v_remainder_7316_);
if (v___x_7320_ == 0)
{
uint64_t v___x_7321_; uint8_t v___x_7322_; 
v___x_7321_ = lean_uint64_land(v_quotient_7311_, v___x_7312_);
v___x_7322_ = lean_uint64_dec_eq(v___x_7321_, v___y_7261_);
if (v___x_7322_ == 0)
{
uint64_t v___x_7323_; 
v___x_7323_ = lean_uint64_add(v_quotient_7311_, v___x_7312_);
v___y_7178_ = v___y_7257_;
v___y_7179_ = v___y_7261_;
v___y_7180_ = v___x_7323_;
goto v___jp_7177_;
}
else
{
v___y_7178_ = v___y_7257_;
v___y_7179_ = v___y_7261_;
v___y_7180_ = v_quotient_7311_;
goto v___jp_7177_;
}
}
else
{
uint64_t v___x_7324_; 
v___x_7324_ = lean_uint64_add(v_quotient_7311_, v___x_7312_);
v___y_7178_ = v___y_7257_;
v___y_7179_ = v___y_7261_;
v___y_7180_ = v___x_7324_;
goto v___jp_7177_;
}
}
else
{
v___y_7178_ = v___y_7257_;
v___y_7179_ = v___y_7261_;
v___y_7180_ = v_quotient_7311_;
goto v___jp_7177_;
}
}
}
else
{
uint64_t v___x_7325_; 
v___x_7325_ = lean_unbox_uint64(v___y_7258_);
lean_dec(v___y_7258_);
v___y_7178_ = v___y_7257_;
v___y_7179_ = v___y_7261_;
v___y_7180_ = v___x_7325_;
goto v___jp_7177_;
}
}
}
}
v___jp_7326_:
{
uint64_t v___x_7336_; uint64_t v___x_7337_; uint8_t v___x_7338_; 
v___x_7336_ = 1ULL;
v___x_7337_ = lean_uint64_shift_right(v___y_7334_, v___x_7336_);
v___x_7338_ = lean_uint64_dec_eq(v___x_7337_, v___y_7332_);
if (v___x_7338_ == 0)
{
uint64_t v___x_7339_; 
v___x_7339_ = lean_uint64_add(v___y_7335_, v___x_7336_);
v___y_7256_ = v___y_7327_;
v___y_7257_ = v___y_7328_;
v___y_7258_ = v___y_7329_;
v___y_7259_ = v___y_7330_;
v___y_7260_ = v___y_7331_;
v___y_7261_ = v___y_7332_;
v___y_7262_ = v___y_7333_;
v___y_7263_ = v___x_7339_;
goto v___jp_7255_;
}
else
{
v___y_7256_ = v___y_7327_;
v___y_7257_ = v___y_7328_;
v___y_7258_ = v___y_7329_;
v___y_7259_ = v___y_7330_;
v___y_7260_ = v___y_7331_;
v___y_7261_ = v___y_7332_;
v___y_7262_ = v___y_7333_;
v___y_7263_ = v___y_7335_;
goto v___jp_7255_;
}
}
v___jp_7340_:
{
uint64_t v___x_7352_; uint8_t v___x_7353_; 
v___x_7352_ = lean_uint64_shift_right(v___y_7348_, v___y_7350_);
v___x_7353_ = lean_uint64_dec_eq(v___x_7352_, v___y_7347_);
if (v___x_7353_ == 0)
{
uint64_t v___x_7354_; 
v___x_7354_ = lean_uint64_add(v___y_7343_, v___y_7350_);
v___y_7327_ = v___y_7341_;
v___y_7328_ = v___y_7342_;
v___y_7329_ = v___y_7344_;
v___y_7330_ = v___y_7345_;
v___y_7331_ = v___y_7346_;
v___y_7332_ = v___y_7347_;
v___y_7333_ = v___y_7349_;
v___y_7334_ = v___y_7351_;
v___y_7335_ = v___x_7354_;
goto v___jp_7326_;
}
else
{
v___y_7327_ = v___y_7341_;
v___y_7328_ = v___y_7342_;
v___y_7329_ = v___y_7344_;
v___y_7330_ = v___y_7345_;
v___y_7331_ = v___y_7346_;
v___y_7332_ = v___y_7347_;
v___y_7333_ = v___y_7349_;
v___y_7334_ = v___y_7351_;
v___y_7335_ = v___y_7343_;
goto v___jp_7326_;
}
}
v___jp_7355_:
{
uint64_t v___x_7365_; uint64_t v___x_7366_; uint8_t v___x_7367_; 
v___x_7365_ = 2ULL;
v___x_7366_ = lean_uint64_shift_right(v___y_7363_, v___x_7365_);
v___x_7367_ = lean_uint64_dec_eq(v___x_7366_, v___y_7361_);
if (v___x_7367_ == 0)
{
v___y_7341_ = v___y_7356_;
v___y_7342_ = v___y_7357_;
v___y_7343_ = v___y_7364_;
v___y_7344_ = v___y_7358_;
v___y_7345_ = v___y_7359_;
v___y_7346_ = v___y_7360_;
v___y_7347_ = v___y_7361_;
v___y_7348_ = v___y_7363_;
v___y_7349_ = v___y_7362_;
v___y_7350_ = v___x_7365_;
v___y_7351_ = v___x_7366_;
goto v___jp_7340_;
}
else
{
v___y_7341_ = v___y_7356_;
v___y_7342_ = v___y_7357_;
v___y_7343_ = v___y_7364_;
v___y_7344_ = v___y_7358_;
v___y_7345_ = v___y_7359_;
v___y_7346_ = v___y_7360_;
v___y_7347_ = v___y_7361_;
v___y_7348_ = v___y_7363_;
v___y_7349_ = v___y_7362_;
v___y_7350_ = v___x_7365_;
v___y_7351_ = v___y_7363_;
goto v___jp_7340_;
}
}
v___jp_7368_:
{
uint64_t v___x_7380_; uint8_t v___x_7381_; 
v___x_7380_ = lean_uint64_shift_right(v___y_7376_, v___y_7374_);
v___x_7381_ = lean_uint64_dec_eq(v___x_7380_, v___y_7375_);
if (v___x_7381_ == 0)
{
uint64_t v___x_7382_; 
v___x_7382_ = lean_uint64_add(v___y_7378_, v___y_7374_);
v___y_7356_ = v___y_7369_;
v___y_7357_ = v___y_7370_;
v___y_7358_ = v___y_7371_;
v___y_7359_ = v___y_7372_;
v___y_7360_ = v___y_7373_;
v___y_7361_ = v___y_7375_;
v___y_7362_ = v___y_7377_;
v___y_7363_ = v___y_7379_;
v___y_7364_ = v___x_7382_;
goto v___jp_7355_;
}
else
{
v___y_7356_ = v___y_7369_;
v___y_7357_ = v___y_7370_;
v___y_7358_ = v___y_7371_;
v___y_7359_ = v___y_7372_;
v___y_7360_ = v___y_7373_;
v___y_7361_ = v___y_7375_;
v___y_7362_ = v___y_7377_;
v___y_7363_ = v___y_7379_;
v___y_7364_ = v___y_7378_;
goto v___jp_7355_;
}
}
v___jp_7383_:
{
uint64_t v___x_7393_; uint64_t v___x_7394_; uint8_t v___x_7395_; 
v___x_7393_ = 4ULL;
v___x_7394_ = lean_uint64_shift_right(v___y_7391_, v___x_7393_);
v___x_7395_ = lean_uint64_dec_eq(v___x_7394_, v___y_7389_);
if (v___x_7395_ == 0)
{
v___y_7369_ = v___y_7384_;
v___y_7370_ = v___y_7385_;
v___y_7371_ = v___y_7386_;
v___y_7372_ = v___y_7387_;
v___y_7373_ = v___y_7388_;
v___y_7374_ = v___x_7393_;
v___y_7375_ = v___y_7389_;
v___y_7376_ = v___y_7391_;
v___y_7377_ = v___y_7390_;
v___y_7378_ = v___y_7392_;
v___y_7379_ = v___x_7394_;
goto v___jp_7368_;
}
else
{
v___y_7369_ = v___y_7384_;
v___y_7370_ = v___y_7385_;
v___y_7371_ = v___y_7386_;
v___y_7372_ = v___y_7387_;
v___y_7373_ = v___y_7388_;
v___y_7374_ = v___x_7393_;
v___y_7375_ = v___y_7389_;
v___y_7376_ = v___y_7391_;
v___y_7377_ = v___y_7390_;
v___y_7378_ = v___y_7392_;
v___y_7379_ = v___y_7391_;
goto v___jp_7368_;
}
}
v___jp_7396_:
{
uint64_t v___x_7408_; uint8_t v___x_7409_; 
v___x_7408_ = lean_uint64_shift_right(v___y_7403_, v___y_7406_);
v___x_7409_ = lean_uint64_dec_eq(v___x_7408_, v___y_7404_);
if (v___x_7409_ == 0)
{
uint64_t v___x_7410_; 
v___x_7410_ = lean_uint64_add(v___y_7398_, v___y_7406_);
v___y_7384_ = v___y_7397_;
v___y_7385_ = v___y_7399_;
v___y_7386_ = v___y_7400_;
v___y_7387_ = v___y_7401_;
v___y_7388_ = v___y_7402_;
v___y_7389_ = v___y_7404_;
v___y_7390_ = v___y_7405_;
v___y_7391_ = v___y_7407_;
v___y_7392_ = v___x_7410_;
goto v___jp_7383_;
}
else
{
v___y_7384_ = v___y_7397_;
v___y_7385_ = v___y_7399_;
v___y_7386_ = v___y_7400_;
v___y_7387_ = v___y_7401_;
v___y_7388_ = v___y_7402_;
v___y_7389_ = v___y_7404_;
v___y_7390_ = v___y_7405_;
v___y_7391_ = v___y_7407_;
v___y_7392_ = v___y_7398_;
goto v___jp_7383_;
}
}
v___jp_7411_:
{
uint64_t v___x_7421_; uint64_t v___x_7422_; uint8_t v___x_7423_; 
v___x_7421_ = 8ULL;
v___x_7422_ = lean_uint64_shift_right(v___y_7418_, v___x_7421_);
v___x_7423_ = lean_uint64_dec_eq(v___x_7422_, v___y_7417_);
if (v___x_7423_ == 0)
{
v___y_7397_ = v___y_7412_;
v___y_7398_ = v___y_7420_;
v___y_7399_ = v___y_7413_;
v___y_7400_ = v___y_7414_;
v___y_7401_ = v___y_7415_;
v___y_7402_ = v___y_7416_;
v___y_7403_ = v___y_7418_;
v___y_7404_ = v___y_7417_;
v___y_7405_ = v___y_7419_;
v___y_7406_ = v___x_7421_;
v___y_7407_ = v___x_7422_;
goto v___jp_7396_;
}
else
{
v___y_7397_ = v___y_7412_;
v___y_7398_ = v___y_7420_;
v___y_7399_ = v___y_7413_;
v___y_7400_ = v___y_7414_;
v___y_7401_ = v___y_7415_;
v___y_7402_ = v___y_7416_;
v___y_7403_ = v___y_7418_;
v___y_7404_ = v___y_7417_;
v___y_7405_ = v___y_7419_;
v___y_7406_ = v___x_7421_;
v___y_7407_ = v___y_7418_;
goto v___jp_7396_;
}
}
v___jp_7424_:
{
uint64_t v___x_7436_; uint8_t v___x_7437_; 
v___x_7436_ = lean_uint64_shift_right(v___y_7430_, v___y_7434_);
v___x_7437_ = lean_uint64_dec_eq(v___x_7436_, v___y_7432_);
if (v___x_7437_ == 0)
{
uint64_t v___x_7438_; 
v___x_7438_ = lean_uint64_add(v___y_7425_, v___y_7434_);
v___y_7412_ = v___y_7426_;
v___y_7413_ = v___y_7427_;
v___y_7414_ = v___y_7428_;
v___y_7415_ = v___y_7429_;
v___y_7416_ = v___y_7431_;
v___y_7417_ = v___y_7432_;
v___y_7418_ = v___y_7435_;
v___y_7419_ = v___y_7433_;
v___y_7420_ = v___x_7438_;
goto v___jp_7411_;
}
else
{
v___y_7412_ = v___y_7426_;
v___y_7413_ = v___y_7427_;
v___y_7414_ = v___y_7428_;
v___y_7415_ = v___y_7429_;
v___y_7416_ = v___y_7431_;
v___y_7417_ = v___y_7432_;
v___y_7418_ = v___y_7435_;
v___y_7419_ = v___y_7433_;
v___y_7420_ = v___y_7425_;
goto v___jp_7411_;
}
}
v___jp_7439_:
{
uint64_t v___x_7449_; uint64_t v___x_7450_; uint8_t v___x_7451_; 
v___x_7449_ = 16ULL;
v___x_7450_ = lean_uint64_shift_right(v___y_7445_, v___x_7449_);
v___x_7451_ = lean_uint64_dec_eq(v___x_7450_, v___y_7446_);
if (v___x_7451_ == 0)
{
v___y_7425_ = v___y_7448_;
v___y_7426_ = v___y_7440_;
v___y_7427_ = v___y_7441_;
v___y_7428_ = v___y_7442_;
v___y_7429_ = v___y_7443_;
v___y_7430_ = v___y_7445_;
v___y_7431_ = v___y_7444_;
v___y_7432_ = v___y_7446_;
v___y_7433_ = v___y_7447_;
v___y_7434_ = v___x_7449_;
v___y_7435_ = v___x_7450_;
goto v___jp_7424_;
}
else
{
v___y_7425_ = v___y_7448_;
v___y_7426_ = v___y_7440_;
v___y_7427_ = v___y_7441_;
v___y_7428_ = v___y_7442_;
v___y_7429_ = v___y_7443_;
v___y_7430_ = v___y_7445_;
v___y_7431_ = v___y_7444_;
v___y_7432_ = v___y_7446_;
v___y_7433_ = v___y_7447_;
v___y_7434_ = v___x_7449_;
v___y_7435_ = v___y_7445_;
goto v___jp_7424_;
}
}
v___jp_7452_:
{
uint64_t v___x_7462_; uint64_t v___x_7463_; uint8_t v___x_7464_; 
v___x_7462_ = lean_unbox_uint64(v___y_7455_);
v___x_7463_ = lean_uint64_shift_right(v___x_7462_, v___y_7457_);
v___x_7464_ = lean_uint64_dec_eq(v___x_7463_, v___y_7459_);
if (v___x_7464_ == 0)
{
v___y_7440_ = v___y_7453_;
v___y_7441_ = v___y_7454_;
v___y_7442_ = v___y_7455_;
v___y_7443_ = v___y_7456_;
v___y_7444_ = v___y_7458_;
v___y_7445_ = v___y_7461_;
v___y_7446_ = v___y_7459_;
v___y_7447_ = v___y_7460_;
v___y_7448_ = v___y_7457_;
goto v___jp_7439_;
}
else
{
v___y_7440_ = v___y_7453_;
v___y_7441_ = v___y_7454_;
v___y_7442_ = v___y_7455_;
v___y_7443_ = v___y_7456_;
v___y_7444_ = v___y_7458_;
v___y_7445_ = v___y_7461_;
v___y_7446_ = v___y_7459_;
v___y_7447_ = v___y_7460_;
v___y_7448_ = v___y_7459_;
goto v___jp_7439_;
}
}
v___jp_7465_:
{
uint64_t v___x_7471_; uint64_t v___x_7472_; uint8_t v___x_7473_; 
v___x_7471_ = 0ULL;
v___x_7472_ = lean_unbox_uint64(v_snd_7470_);
v___x_7473_ = lean_uint64_dec_eq(v___x_7472_, v___x_7471_);
if (v___x_7473_ == 0)
{
uint64_t v___x_7474_; uint64_t v___x_7475_; uint64_t v___x_7476_; uint64_t v___x_7477_; uint64_t v___x_7478_; uint8_t v___x_7479_; 
v___x_7474_ = 149ULL;
v___x_7475_ = lean_uint64_add(v___y_7466_, v___x_7474_);
v___x_7476_ = 32ULL;
v___x_7477_ = lean_unbox_uint64(v_snd_7470_);
v___x_7478_ = lean_uint64_shift_right(v___x_7477_, v___x_7476_);
v___x_7479_ = lean_uint64_dec_eq(v___x_7478_, v___x_7471_);
if (v___x_7479_ == 0)
{
v___y_7453_ = v___y_7467_;
v___y_7454_ = v_fst_7469_;
v___y_7455_ = v_snd_7470_;
v___y_7456_ = v___x_7474_;
v___y_7457_ = v___x_7476_;
v___y_7458_ = v___x_7475_;
v___y_7459_ = v___x_7471_;
v___y_7460_ = v___y_7468_;
v___y_7461_ = v___x_7478_;
goto v___jp_7452_;
}
else
{
uint64_t v___x_7480_; 
v___x_7480_ = lean_unbox_uint64(v_snd_7470_);
v___y_7453_ = v___y_7467_;
v___y_7454_ = v_fst_7469_;
v___y_7455_ = v_snd_7470_;
v___y_7456_ = v___x_7474_;
v___y_7457_ = v___x_7476_;
v___y_7458_ = v___x_7475_;
v___y_7459_ = v___x_7471_;
v___y_7460_ = v___y_7468_;
v___y_7461_ = v___x_7480_;
goto v___jp_7452_;
}
}
else
{
uint8_t v___x_7481_; 
lean_dec(v_snd_7470_);
v___x_7481_ = lean_unbox(v_fst_7469_);
lean_dec(v_fst_7469_);
if (v___x_7481_ == 0)
{
uint32_t v___x_7482_; 
v___x_7482_ = 0;
return v___x_7482_;
}
else
{
uint32_t v___x_7483_; 
v___x_7483_ = 2147483648;
return v___x_7483_;
}
}
}
v___jp_7484_:
{
uint8_t v___x_7493_; 
v___x_7493_ = lean_uint64_dec_eq(v___y_7489_, v___y_7488_);
if (v___x_7493_ == 0)
{
uint8_t v___x_7494_; 
v___x_7494_ = lean_uint64_dec_lt(v___y_7489_, v___y_7488_);
if (v___x_7494_ == 0)
{
uint64_t v___x_7495_; lean_object* v___x_7496_; lean_object* v___x_7497_; 
v___x_7495_ = lean_uint64_sub(v___y_7489_, v___y_7488_);
v___x_7496_ = lean_box(v___y_7487_);
v___x_7497_ = lean_box_uint64(v___x_7495_);
v___y_7466_ = v___y_7485_;
v___y_7467_ = v___y_7486_;
v___y_7468_ = v___y_7491_;
v_fst_7469_ = v___x_7496_;
v_snd_7470_ = v___x_7497_;
goto v___jp_7465_;
}
else
{
uint64_t v___x_7498_; lean_object* v___x_7499_; lean_object* v___x_7500_; 
v___x_7498_ = lean_uint64_sub(v___y_7488_, v___y_7489_);
v___x_7499_ = lean_box(v___y_7490_);
v___x_7500_ = lean_box_uint64(v___x_7498_);
v___y_7466_ = v___y_7485_;
v___y_7467_ = v___y_7486_;
v___y_7468_ = v___y_7491_;
v_fst_7469_ = v___x_7499_;
v_snd_7470_ = v___x_7500_;
goto v___jp_7465_;
}
}
else
{
lean_object* v___x_7501_; lean_object* v___x_7502_; 
v___x_7501_ = lean_box(v___y_7492_);
v___x_7502_ = ((lean_object*)(lp_competition_Submission_TunedAdd_core___boxed__const__1));
v___y_7466_ = v___y_7485_;
v___y_7467_ = v___y_7486_;
v___y_7468_ = v___y_7491_;
v_fst_7469_ = v___x_7501_;
v_snd_7470_ = v___x_7502_;
goto v___jp_7465_;
}
}
v___jp_7503_:
{
if (v___y_7511_ == 0)
{
v___y_7485_ = v___y_7504_;
v___y_7486_ = v___y_7507_;
v___y_7487_ = v___y_7506_;
v___y_7488_ = v___y_7505_;
v___y_7489_ = v___y_7508_;
v___y_7490_ = v___y_7509_;
v___y_7491_ = v___y_7510_;
v___y_7492_ = v___y_7511_;
goto v___jp_7484_;
}
else
{
uint64_t v___x_7512_; lean_object* v___x_7513_; lean_object* v___x_7514_; 
v___x_7512_ = lean_uint64_add(v___y_7508_, v___y_7505_);
v___x_7513_ = lean_box(v___y_7506_);
v___x_7514_ = lean_box_uint64(v___x_7512_);
v___y_7466_ = v___y_7504_;
v___y_7467_ = v___y_7507_;
v___y_7468_ = v___y_7510_;
v_fst_7469_ = v___x_7513_;
v_snd_7470_ = v___x_7514_;
goto v___jp_7465_;
}
}
v___jp_7515_:
{
uint8_t v___x_7524_; 
v___x_7524_ = lean_uint64_dec_eq(v___y_7519_, v___y_7516_);
if (v___x_7524_ == 0)
{
uint8_t v___x_7525_; 
v___x_7525_ = lean_uint64_dec_lt(v___y_7519_, v___y_7516_);
if (v___x_7525_ == 0)
{
uint64_t v___x_7526_; lean_object* v___x_7527_; lean_object* v___x_7528_; 
v___x_7526_ = lean_uint64_sub(v___y_7519_, v___y_7516_);
v___x_7527_ = lean_box(v___y_7518_);
v___x_7528_ = lean_box_uint64(v___x_7526_);
v___y_7153_ = v___y_7517_;
v___y_7154_ = v___y_7521_;
v___y_7155_ = v___y_7522_;
v_fst_7156_ = v___x_7527_;
v_snd_7157_ = v___x_7528_;
goto v___jp_7152_;
}
else
{
uint64_t v___x_7529_; lean_object* v___x_7530_; lean_object* v___x_7531_; 
v___x_7529_ = lean_uint64_sub(v___y_7516_, v___y_7519_);
v___x_7530_ = lean_box(v___y_7520_);
v___x_7531_ = lean_box_uint64(v___x_7529_);
v___y_7153_ = v___y_7517_;
v___y_7154_ = v___y_7521_;
v___y_7155_ = v___y_7522_;
v_fst_7156_ = v___x_7530_;
v_snd_7157_ = v___x_7531_;
goto v___jp_7152_;
}
}
else
{
lean_object* v___x_7532_; lean_object* v___x_7533_; 
v___x_7532_ = lean_box(v___y_7523_);
v___x_7533_ = ((lean_object*)(lp_competition_Submission_TunedAdd_core___boxed__const__1));
v___y_7153_ = v___y_7517_;
v___y_7154_ = v___y_7521_;
v___y_7155_ = v___y_7522_;
v_fst_7156_ = v___x_7532_;
v_snd_7157_ = v___x_7533_;
goto v___jp_7152_;
}
}
v___jp_7534_:
{
if (v___y_7542_ == 0)
{
v___y_7516_ = v___y_7535_;
v___y_7517_ = v___y_7537_;
v___y_7518_ = v___y_7536_;
v___y_7519_ = v___y_7538_;
v___y_7520_ = v___y_7539_;
v___y_7521_ = v___y_7540_;
v___y_7522_ = v___y_7541_;
v___y_7523_ = v___y_7542_;
goto v___jp_7515_;
}
else
{
uint64_t v___x_7543_; lean_object* v___x_7544_; lean_object* v___x_7545_; 
v___x_7543_ = lean_uint64_add(v___y_7538_, v___y_7535_);
v___x_7544_ = lean_box(v___y_7536_);
v___x_7545_ = lean_box_uint64(v___x_7543_);
v___y_7153_ = v___y_7537_;
v___y_7154_ = v___y_7540_;
v___y_7155_ = v___y_7541_;
v_fst_7156_ = v___x_7544_;
v_snd_7157_ = v___x_7545_;
goto v___jp_7152_;
}
}
v___jp_7546_:
{
uint8_t v___x_7555_; 
v___x_7555_ = lean_uint64_dec_le(v___y_7553_, v___y_7554_);
if (v___x_7555_ == 0)
{
uint64_t v_shift_7556_; uint64_t v___x_7557_; uint8_t v___x_7558_; 
v_shift_7556_ = lean_uint64_sub(v___y_7553_, v___y_7554_);
v___x_7557_ = 39ULL;
v___x_7558_ = lean_uint64_dec_le(v_shift_7556_, v___x_7557_);
if (v___x_7558_ == 0)
{
return v_x_5072_;
}
else
{
uint64_t v___x_7559_; 
v___x_7559_ = lean_uint64_shift_left(v___y_7550_, v_shift_7556_);
if (v___y_7548_ == 0)
{
if (v___y_7551_ == 0)
{
v___y_7504_ = v___y_7554_;
v___y_7505_ = v___y_7547_;
v___y_7506_ = v___y_7548_;
v___y_7507_ = v___y_7549_;
v___y_7508_ = v___x_7559_;
v___y_7509_ = v___y_7551_;
v___y_7510_ = v___y_7552_;
v___y_7511_ = v___x_7558_;
goto v___jp_7503_;
}
else
{
v___y_7485_ = v___y_7554_;
v___y_7486_ = v___y_7549_;
v___y_7487_ = v___y_7548_;
v___y_7488_ = v___y_7547_;
v___y_7489_ = v___x_7559_;
v___y_7490_ = v___y_7551_;
v___y_7491_ = v___y_7552_;
v___y_7492_ = v___y_7548_;
goto v___jp_7484_;
}
}
else
{
v___y_7504_ = v___y_7554_;
v___y_7505_ = v___y_7547_;
v___y_7506_ = v___y_7548_;
v___y_7507_ = v___y_7549_;
v___y_7508_ = v___x_7559_;
v___y_7509_ = v___y_7551_;
v___y_7510_ = v___y_7552_;
v___y_7511_ = v___y_7551_;
goto v___jp_7503_;
}
}
}
else
{
uint64_t v_shift_7560_; uint64_t v___x_7561_; uint8_t v___x_7562_; 
v_shift_7560_ = lean_uint64_sub(v___y_7554_, v___y_7553_);
v___x_7561_ = 39ULL;
v___x_7562_ = lean_uint64_dec_le(v_shift_7560_, v___x_7561_);
if (v___x_7562_ == 0)
{
return v_y_5073_;
}
else
{
uint64_t v___x_7563_; 
v___x_7563_ = lean_uint64_shift_left(v___y_7547_, v_shift_7560_);
if (v___y_7548_ == 0)
{
if (v___y_7551_ == 0)
{
v___y_7535_ = v___x_7563_;
v___y_7536_ = v___y_7548_;
v___y_7537_ = v___y_7549_;
v___y_7538_ = v___y_7550_;
v___y_7539_ = v___y_7551_;
v___y_7540_ = v___y_7552_;
v___y_7541_ = v___y_7553_;
v___y_7542_ = v___x_7562_;
goto v___jp_7534_;
}
else
{
v___y_7516_ = v___x_7563_;
v___y_7517_ = v___y_7549_;
v___y_7518_ = v___y_7548_;
v___y_7519_ = v___y_7550_;
v___y_7520_ = v___y_7551_;
v___y_7521_ = v___y_7552_;
v___y_7522_ = v___y_7553_;
v___y_7523_ = v___y_7548_;
goto v___jp_7515_;
}
}
else
{
v___y_7535_ = v___x_7563_;
v___y_7536_ = v___y_7548_;
v___y_7537_ = v___y_7549_;
v___y_7538_ = v___y_7550_;
v___y_7539_ = v___y_7551_;
v___y_7540_ = v___y_7552_;
v___y_7541_ = v___y_7553_;
v___y_7542_ = v___y_7551_;
goto v___jp_7534_;
}
}
}
}
v___jp_7564_:
{
uint64_t v___x_7573_; uint64_t v___x_7574_; uint8_t v___x_7575_; 
v___x_7573_ = lean_uint32_to_uint64(v___y_7568_);
v___x_7574_ = 0ULL;
v___x_7575_ = lean_uint64_dec_eq(v___x_7573_, v___x_7574_);
if (v___x_7575_ == 0)
{
uint64_t v___x_7576_; uint64_t v___x_7577_; 
v___x_7576_ = 1ULL;
v___x_7577_ = lean_uint64_sub(v___x_7573_, v___x_7576_);
v___y_7547_ = v___y_7566_;
v___y_7548_ = v___y_7565_;
v___y_7549_ = v___y_7567_;
v___y_7550_ = v___y_7569_;
v___y_7551_ = v___y_7570_;
v___y_7552_ = v___y_7571_;
v___y_7553_ = v___y_7572_;
v___y_7554_ = v___x_7577_;
goto v___jp_7546_;
}
else
{
v___y_7547_ = v___y_7566_;
v___y_7548_ = v___y_7565_;
v___y_7549_ = v___y_7567_;
v___y_7550_ = v___y_7569_;
v___y_7551_ = v___y_7570_;
v___y_7552_ = v___y_7571_;
v___y_7553_ = v___y_7572_;
v___y_7554_ = v___x_7574_;
goto v___jp_7546_;
}
}
v___jp_7578_:
{
uint64_t v___x_7587_; uint64_t v___x_7588_; uint8_t v___x_7589_; 
v___x_7587_ = lean_uint32_to_uint64(v___y_7579_);
v___x_7588_ = 0ULL;
v___x_7589_ = lean_uint64_dec_eq(v___x_7587_, v___x_7588_);
if (v___x_7589_ == 0)
{
uint64_t v___x_7590_; uint64_t v___x_7591_; 
v___x_7590_ = 1ULL;
v___x_7591_ = lean_uint64_sub(v___x_7587_, v___x_7590_);
v___y_7565_ = v___y_7581_;
v___y_7566_ = v___y_7586_;
v___y_7567_ = v___y_7580_;
v___y_7568_ = v___y_7583_;
v___y_7569_ = v___y_7582_;
v___y_7570_ = v___y_7584_;
v___y_7571_ = v___y_7585_;
v___y_7572_ = v___x_7591_;
goto v___jp_7564_;
}
else
{
v___y_7565_ = v___y_7581_;
v___y_7566_ = v___y_7586_;
v___y_7567_ = v___y_7580_;
v___y_7568_ = v___y_7583_;
v___y_7569_ = v___y_7582_;
v___y_7570_ = v___y_7584_;
v___y_7571_ = v___y_7585_;
v___y_7572_ = v___x_7588_;
goto v___jp_7564_;
}
}
v___jp_7592_:
{
uint32_t v___x_7600_; uint32_t v___x_7601_; uint32_t v___x_7602_; uint8_t v___x_7603_; 
v___x_7600_ = 8388607;
v___x_7601_ = lean_uint32_land(v_y_5073_, v___x_7600_);
v___x_7602_ = 0;
v___x_7603_ = lean_uint32_dec_eq(v___y_7596_, v___x_7602_);
if (v___x_7603_ == 0)
{
uint64_t v___x_7604_; uint64_t v___x_7605_; uint64_t v___x_7606_; 
v___x_7604_ = lean_uint32_to_uint64(v___x_7601_);
v___x_7605_ = 8388608ULL;
v___x_7606_ = lean_uint64_lor(v___x_7604_, v___x_7605_);
v___y_7579_ = v___y_7593_;
v___y_7580_ = v___y_7595_;
v___y_7581_ = v___y_7594_;
v___y_7582_ = v___y_7599_;
v___y_7583_ = v___y_7596_;
v___y_7584_ = v___y_7597_;
v___y_7585_ = v___y_7598_;
v___y_7586_ = v___x_7606_;
goto v___jp_7578_;
}
else
{
uint64_t v___x_7607_; 
v___x_7607_ = lean_uint32_to_uint64(v___x_7601_);
v___y_7579_ = v___y_7593_;
v___y_7580_ = v___y_7595_;
v___y_7581_ = v___y_7594_;
v___y_7582_ = v___y_7599_;
v___y_7583_ = v___y_7596_;
v___y_7584_ = v___y_7597_;
v___y_7585_ = v___y_7598_;
v___y_7586_ = v___x_7607_;
goto v___jp_7578_;
}
}
v___jp_7608_:
{
uint32_t v___x_7615_; uint32_t v___x_7616_; uint32_t v___x_7617_; uint8_t v___x_7618_; 
v___x_7615_ = 8388607;
v___x_7616_ = lean_uint32_land(v_x_5072_, v___x_7615_);
v___x_7617_ = 0;
v___x_7618_ = lean_uint32_dec_eq(v___y_7609_, v___x_7617_);
if (v___x_7618_ == 0)
{
uint64_t v___x_7619_; uint64_t v___x_7620_; uint64_t v___x_7621_; 
v___x_7619_ = lean_uint32_to_uint64(v___x_7616_);
v___x_7620_ = 8388608ULL;
v___x_7621_ = lean_uint64_lor(v___x_7619_, v___x_7620_);
v___y_7593_ = v___y_7609_;
v___y_7594_ = v___y_7611_;
v___y_7595_ = v___y_7610_;
v___y_7596_ = v___y_7612_;
v___y_7597_ = v___y_7614_;
v___y_7598_ = v___y_7613_;
v___y_7599_ = v___x_7621_;
goto v___jp_7592_;
}
else
{
uint64_t v___x_7622_; 
v___x_7622_ = lean_uint32_to_uint64(v___x_7616_);
v___y_7593_ = v___y_7609_;
v___y_7594_ = v___y_7611_;
v___y_7595_ = v___y_7610_;
v___y_7596_ = v___y_7612_;
v___y_7597_ = v___y_7614_;
v___y_7598_ = v___y_7613_;
v___y_7599_ = v___x_7622_;
goto v___jp_7592_;
}
}
v___jp_7623_:
{
uint32_t v___x_7631_; uint32_t v___x_7632_; uint32_t v___x_7633_; uint8_t v___x_7634_; 
v___x_7631_ = 2147483648;
v___x_7632_ = lean_uint32_land(v_y_5073_, v___x_7631_);
v___x_7633_ = 0;
v___x_7634_ = lean_uint32_dec_eq(v___x_7632_, v___x_7633_);
if (v___x_7634_ == 0)
{
v___y_7609_ = v___y_7624_;
v___y_7610_ = v___y_7625_;
v___y_7611_ = v___y_7630_;
v___y_7612_ = v___y_7626_;
v___y_7613_ = v___y_7629_;
v___y_7614_ = v___y_7628_;
goto v___jp_7608_;
}
else
{
v___y_7609_ = v___y_7624_;
v___y_7610_ = v___y_7625_;
v___y_7611_ = v___y_7630_;
v___y_7612_ = v___y_7626_;
v___y_7613_ = v___y_7629_;
v___y_7614_ = v___y_7627_;
goto v___jp_7608_;
}
}
v___jp_7635_:
{
uint32_t v___x_7642_; uint32_t v___x_7643_; uint32_t v___x_7644_; uint8_t v___x_7645_; 
v___x_7642_ = 2147483648;
v___x_7643_ = lean_uint32_land(v_x_5072_, v___x_7642_);
v___x_7644_ = 0;
v___x_7645_ = lean_uint32_dec_eq(v___x_7643_, v___x_7644_);
if (v___x_7645_ == 0)
{
v___y_7624_ = v___y_7636_;
v___y_7625_ = v___y_7637_;
v___y_7626_ = v___y_7638_;
v___y_7627_ = v___y_7641_;
v___y_7628_ = v___y_7639_;
v___y_7629_ = v___y_7640_;
v___y_7630_ = v___y_7639_;
goto v___jp_7623_;
}
else
{
v___y_7624_ = v___y_7636_;
v___y_7625_ = v___y_7637_;
v___y_7626_ = v___y_7638_;
v___y_7627_ = v___y_7641_;
v___y_7628_ = v___y_7639_;
v___y_7629_ = v___y_7640_;
v___y_7630_ = v___y_7641_;
goto v___jp_7623_;
}
}
v___jp_7646_:
{
uint32_t v___x_7655_; uint32_t v___x_7656_; uint32_t v___x_7657_; uint8_t v___x_7658_; 
v___x_7655_ = 8388607;
v___x_7656_ = lean_uint32_land(v_x_5072_, v___x_7655_);
v___x_7657_ = 0;
v___x_7658_ = lean_uint32_dec_eq(v___y_7647_, v___x_7657_);
if (v___x_7658_ == 0)
{
uint64_t v___x_7659_; uint64_t v___x_7660_; uint64_t v___x_7661_; 
v___x_7659_ = lean_uint32_to_uint64(v___x_7656_);
v___x_7660_ = 8388608ULL;
v___x_7661_ = lean_uint64_lor(v___x_7659_, v___x_7660_);
v___y_6841_ = v___y_7647_;
v___y_6842_ = v___y_7648_;
v___y_6843_ = v___y_7649_;
v___y_6844_ = v___y_7650_;
v___y_6845_ = v___y_7651_;
v___y_6846_ = v___y_7654_;
v___y_6847_ = v___y_7652_;
v___y_6848_ = v___y_7653_;
v___y_6849_ = v___x_7661_;
goto v___jp_6840_;
}
else
{
uint64_t v___x_7662_; 
v___x_7662_ = lean_uint32_to_uint64(v___x_7656_);
v___y_6841_ = v___y_7647_;
v___y_6842_ = v___y_7648_;
v___y_6843_ = v___y_7649_;
v___y_6844_ = v___y_7650_;
v___y_6845_ = v___y_7651_;
v___y_6846_ = v___y_7654_;
v___y_6847_ = v___y_7652_;
v___y_6848_ = v___y_7653_;
v___y_6849_ = v___x_7662_;
goto v___jp_6840_;
}
}
v___jp_7663_:
{
if (v___y_7665_ == 0)
{
if (v___y_7672_ == 0)
{
uint8_t v___x_7673_; 
v___x_7673_ = 1;
v___y_7647_ = v___y_7664_;
v___y_7648_ = v___y_7665_;
v___y_7649_ = v___y_7666_;
v___y_7650_ = v___y_7667_;
v___y_7651_ = v___y_7668_;
v___y_7652_ = v___y_7669_;
v___y_7653_ = v___y_7671_;
v___y_7654_ = v___x_7673_;
goto v___jp_7646_;
}
else
{
v___y_7636_ = v___y_7664_;
v___y_7637_ = v___y_7666_;
v___y_7638_ = v___y_7667_;
v___y_7639_ = v___y_7670_;
v___y_7640_ = v___y_7671_;
v___y_7641_ = v___y_7665_;
goto v___jp_7635_;
}
}
else
{
if (v___y_7672_ == 0)
{
v___y_7636_ = v___y_7664_;
v___y_7637_ = v___y_7666_;
v___y_7638_ = v___y_7667_;
v___y_7639_ = v___y_7670_;
v___y_7640_ = v___y_7671_;
v___y_7641_ = v___y_7672_;
goto v___jp_7635_;
}
else
{
v___y_7647_ = v___y_7664_;
v___y_7648_ = v___y_7665_;
v___y_7649_ = v___y_7666_;
v___y_7650_ = v___y_7667_;
v___y_7651_ = v___y_7668_;
v___y_7652_ = v___y_7669_;
v___y_7653_ = v___y_7671_;
v___y_7654_ = v___y_7672_;
goto v___jp_7646_;
}
}
}
v___jp_7674_:
{
uint32_t v___x_7683_; uint32_t v___x_7684_; uint32_t v___x_7685_; uint8_t v___x_7686_; 
v___x_7683_ = 2147483648;
v___x_7684_ = lean_uint32_land(v_y_5073_, v___x_7683_);
v___x_7685_ = 0;
v___x_7686_ = lean_uint32_dec_eq(v___x_7684_, v___x_7685_);
if (v___x_7686_ == 0)
{
v___y_7664_ = v___y_7675_;
v___y_7665_ = v___y_7682_;
v___y_7666_ = v___y_7676_;
v___y_7667_ = v___y_7677_;
v___y_7668_ = v___y_7678_;
v___y_7669_ = v___y_7679_;
v___y_7670_ = v___y_7680_;
v___y_7671_ = v___y_7681_;
v___y_7672_ = v___y_7680_;
goto v___jp_7663_;
}
else
{
v___y_7664_ = v___y_7675_;
v___y_7665_ = v___y_7682_;
v___y_7666_ = v___y_7676_;
v___y_7667_ = v___y_7677_;
v___y_7668_ = v___y_7678_;
v___y_7669_ = v___y_7679_;
v___y_7670_ = v___y_7680_;
v___y_7671_ = v___y_7681_;
v___y_7672_ = v___y_7679_;
goto v___jp_7663_;
}
}
v___jp_7687_:
{
uint32_t v___x_7690_; uint32_t v___x_7691_; uint32_t v___x_7692_; 
v___x_7690_ = 8388607;
v___x_7691_ = lean_uint32_land(v___y_7688_, v___x_7690_);
v___x_7692_ = lean_uint32_lor(v___y_7689_, v___x_7691_);
return v___x_7692_;
}
v___jp_7693_:
{
uint8_t v___x_7697_; 
v___x_7697_ = lean_uint64_dec_eq(v___y_7696_, v___y_7694_);
if (v___x_7697_ == 0)
{
uint64_t v___x_7698_; uint8_t v___x_7699_; 
v___x_7698_ = 8388608ULL;
v___x_7699_ = lean_uint64_dec_eq(v___y_7696_, v___x_7698_);
if (v___x_7699_ == 0)
{
uint32_t v___x_7700_; uint8_t v___x_7701_; 
v___x_7700_ = lean_uint64_to_uint32(v___y_7696_);
v___x_7701_ = lean_unbox(v___y_7695_);
lean_dec(v___y_7695_);
if (v___x_7701_ == 0)
{
uint32_t v___x_7702_; 
v___x_7702_ = 0;
v___y_7688_ = v___x_7700_;
v___y_7689_ = v___x_7702_;
goto v___jp_7687_;
}
else
{
uint32_t v___x_7703_; 
v___x_7703_ = 2147483648;
v___y_7688_ = v___x_7700_;
v___y_7689_ = v___x_7703_;
goto v___jp_7687_;
}
}
else
{
uint8_t v___x_7704_; 
v___x_7704_ = lean_unbox(v___y_7695_);
lean_dec(v___y_7695_);
if (v___x_7704_ == 0)
{
uint32_t v___x_7705_; 
v___x_7705_ = 0;
v___y_5103_ = v___x_7705_;
goto v___jp_5102_;
}
else
{
uint32_t v___x_7706_; 
v___x_7706_ = 2147483648;
v___y_5103_ = v___x_7706_;
goto v___jp_5102_;
}
}
}
else
{
uint8_t v___x_7707_; 
v___x_7707_ = lean_unbox(v___y_7695_);
lean_dec(v___y_7695_);
if (v___x_7707_ == 0)
{
uint32_t v___x_7708_; 
v___x_7708_ = 0;
return v___x_7708_;
}
else
{
uint32_t v___x_7709_; 
v___x_7709_ = 2147483648;
return v___x_7709_;
}
}
}
v___jp_7710_:
{
uint32_t v___x_7716_; uint32_t v___x_7717_; uint32_t v___x_7718_; uint32_t v___x_7719_; uint32_t v___x_7720_; uint32_t v___x_7721_; 
v___x_7716_ = lean_uint32_land(v___y_7711_, v___y_7712_);
v___x_7717_ = lean_uint32_shift_left(v___x_7716_, v___y_7714_);
v___x_7718_ = lean_uint32_lor(v___y_7715_, v___x_7717_);
v___x_7719_ = 8388607;
v___x_7720_ = lean_uint32_land(v___y_7713_, v___x_7719_);
v___x_7721_ = lean_uint32_lor(v___x_7718_, v___x_7720_);
return v___x_7721_;
}
v___jp_7722_:
{
uint8_t v___x_7728_; 
v___x_7728_ = lean_unbox(v___y_7725_);
lean_dec(v___y_7725_);
if (v___x_7728_ == 0)
{
uint32_t v___x_7729_; 
v___x_7729_ = 0;
v___y_7711_ = v___y_7723_;
v___y_7712_ = v___y_7724_;
v___y_7713_ = v___y_7727_;
v___y_7714_ = v___y_7726_;
v___y_7715_ = v___x_7729_;
goto v___jp_7710_;
}
else
{
uint32_t v___x_7730_; 
v___x_7730_ = 2147483648;
v___y_7711_ = v___y_7723_;
v___y_7712_ = v___y_7724_;
v___y_7713_ = v___y_7727_;
v___y_7714_ = v___y_7726_;
v___y_7715_ = v___x_7730_;
goto v___jp_7710_;
}
}
v___jp_7731_:
{
uint64_t v___x_7738_; uint64_t v_encodedExponent_7739_; uint32_t v___x_7740_; uint64_t v___x_7741_; uint8_t v___x_7742_; 
v___x_7738_ = 171ULL;
v_encodedExponent_7739_ = lean_uint64_sub(v___y_7734_, v___x_7738_);
v___x_7740_ = lean_uint64_to_uint32(v_encodedExponent_7739_);
v___x_7741_ = 8388608ULL;
v___x_7742_ = lean_uint64_dec_lt(v___y_7737_, v___x_7741_);
if (v___x_7742_ == 0)
{
uint64_t v___x_7743_; uint32_t v___x_7744_; 
v___x_7743_ = lean_uint64_sub(v___y_7737_, v___x_7741_);
v___x_7744_ = lean_uint64_to_uint32(v___x_7743_);
v___y_7723_ = v___x_7740_;
v___y_7724_ = v___y_7733_;
v___y_7725_ = v___y_7735_;
v___y_7726_ = v___y_7736_;
v___y_7727_ = v___x_7744_;
goto v___jp_7722_;
}
else
{
uint32_t v___x_7745_; 
v___x_7745_ = lean_uint64_to_uint32(v___y_7732_);
v___y_7723_ = v___x_7740_;
v___y_7724_ = v___y_7733_;
v___y_7725_ = v___y_7735_;
v___y_7726_ = v___y_7736_;
v___y_7727_ = v___x_7745_;
goto v___jp_7722_;
}
}
v___jp_7746_:
{
uint64_t v___x_7754_; uint8_t v___x_7755_; 
v___x_7754_ = 425ULL;
v___x_7755_ = lean_uint64_dec_lt(v___x_7754_, v___y_7753_);
if (v___x_7755_ == 0)
{
if (v___y_7750_ == 0)
{
v___y_7732_ = v___y_7747_;
v___y_7733_ = v___y_7748_;
v___y_7734_ = v___y_7753_;
v___y_7735_ = v___y_7751_;
v___y_7736_ = v___y_7752_;
v___y_7737_ = v___y_7749_;
goto v___jp_7731_;
}
else
{
uint64_t v___x_7756_; 
v___x_7756_ = 8388608ULL;
v___y_7732_ = v___y_7747_;
v___y_7733_ = v___y_7748_;
v___y_7734_ = v___y_7753_;
v___y_7735_ = v___y_7751_;
v___y_7736_ = v___y_7752_;
v___y_7737_ = v___x_7756_;
goto v___jp_7731_;
}
}
else
{
uint8_t v___x_7757_; 
v___x_7757_ = lean_unbox(v___y_7751_);
lean_dec(v___y_7751_);
if (v___x_7757_ == 0)
{
uint32_t v___x_7758_; 
v___x_7758_ = 2139095040;
return v___x_7758_;
}
else
{
uint32_t v___x_7759_; 
v___x_7759_ = 4286578688;
return v___x_7759_;
}
}
}
v___jp_7760_:
{
uint64_t v___x_7767_; uint8_t v_carry_7768_; 
v___x_7767_ = 16777216ULL;
v_carry_7768_ = lean_uint64_dec_eq(v___y_7766_, v___x_7767_);
if (v_carry_7768_ == 0)
{
v___y_7747_ = v___y_7761_;
v___y_7748_ = v___y_7762_;
v___y_7749_ = v___y_7766_;
v___y_7750_ = v_carry_7768_;
v___y_7751_ = v___y_7763_;
v___y_7752_ = v___y_7764_;
v___y_7753_ = v___y_7765_;
goto v___jp_7746_;
}
else
{
uint64_t v___x_7769_; uint64_t v___x_7770_; 
v___x_7769_ = 1ULL;
v___x_7770_ = lean_uint64_add(v___y_7765_, v___x_7769_);
v___y_7747_ = v___y_7761_;
v___y_7748_ = v___y_7762_;
v___y_7749_ = v___y_7766_;
v___y_7750_ = v_carry_7768_;
v___y_7751_ = v___y_7763_;
v___y_7752_ = v___y_7764_;
v___y_7753_ = v___x_7770_;
goto v___jp_7746_;
}
}
v___jp_7771_:
{
uint64_t v_position_7780_; uint64_t v___x_7781_; uint8_t v___x_7782_; 
v_position_7780_ = lean_uint64_add(v___y_7779_, v___y_7778_);
v___x_7781_ = 172ULL;
v___x_7782_ = lean_uint64_dec_lt(v_position_7780_, v___x_7781_);
if (v___x_7782_ == 0)
{
uint64_t v___x_7783_; uint8_t v___x_7784_; 
v___x_7783_ = 23ULL;
v___x_7784_ = lean_uint64_dec_lt(v___y_7779_, v___x_7783_);
if (v___x_7784_ == 0)
{
uint64_t v___x_7785_; uint8_t v___x_7786_; 
v___x_7785_ = lean_uint64_sub(v___y_7779_, v___x_7783_);
v___x_7786_ = lean_uint64_dec_eq(v___x_7785_, v___y_7772_);
if (v___x_7786_ == 0)
{
uint64_t v___x_7787_; uint8_t v___x_7788_; 
v___x_7787_ = 64ULL;
v___x_7788_ = lean_uint64_dec_lt(v___x_7785_, v___x_7787_);
if (v___x_7788_ == 0)
{
uint8_t v___x_7789_; 
v___x_7789_ = lean_uint64_dec_eq(v___x_7785_, v___x_7787_);
if (v___x_7789_ == 0)
{
lean_dec(v___y_7773_);
v___y_7761_ = v___y_7772_;
v___y_7762_ = v___y_7774_;
v___y_7763_ = v___y_7776_;
v___y_7764_ = v___y_7777_;
v___y_7765_ = v_position_7780_;
v___y_7766_ = v___y_7772_;
goto v___jp_7760_;
}
else
{
uint64_t v___x_7790_; uint64_t v___x_7791_; uint8_t v___x_7792_; 
v___x_7790_ = 9223372036854775808ULL;
v___x_7791_ = lean_unbox_uint64(v___y_7773_);
lean_dec(v___y_7773_);
v___x_7792_ = lean_uint64_dec_lt(v___x_7790_, v___x_7791_);
if (v___x_7792_ == 0)
{
v___y_7761_ = v___y_7772_;
v___y_7762_ = v___y_7774_;
v___y_7763_ = v___y_7776_;
v___y_7764_ = v___y_7777_;
v___y_7765_ = v_position_7780_;
v___y_7766_ = v___y_7772_;
goto v___jp_7760_;
}
else
{
uint64_t v___x_7793_; 
v___x_7793_ = 1ULL;
v___y_7761_ = v___y_7772_;
v___y_7762_ = v___y_7774_;
v___y_7763_ = v___y_7776_;
v___y_7764_ = v___y_7777_;
v___y_7765_ = v_position_7780_;
v___y_7766_ = v___x_7793_;
goto v___jp_7760_;
}
}
}
else
{
uint64_t v___x_7794_; uint64_t v_quotient_7795_; uint64_t v___x_7796_; uint64_t v___x_7797_; uint64_t v___x_7798_; uint64_t v___x_7799_; uint64_t v_remainder_7800_; uint64_t v___x_7801_; uint64_t v_half_7802_; uint8_t v___x_7803_; 
v___x_7794_ = lean_unbox_uint64(v___y_7773_);
v_quotient_7795_ = lean_uint64_shift_right(v___x_7794_, v___x_7785_);
v___x_7796_ = 1ULL;
v___x_7797_ = lean_uint64_shift_left(v___x_7796_, v___x_7785_);
v___x_7798_ = lean_uint64_sub(v___x_7797_, v___x_7796_);
v___x_7799_ = lean_unbox_uint64(v___y_7773_);
lean_dec(v___y_7773_);
v_remainder_7800_ = lean_uint64_land(v___x_7799_, v___x_7798_);
v___x_7801_ = lean_uint64_sub(v___x_7785_, v___x_7796_);
v_half_7802_ = lean_uint64_shift_left(v___x_7796_, v___x_7801_);
v___x_7803_ = lean_uint64_dec_lt(v_remainder_7800_, v_half_7802_);
if (v___x_7803_ == 0)
{
uint8_t v___x_7804_; 
v___x_7804_ = lean_uint64_dec_lt(v_half_7802_, v_remainder_7800_);
if (v___x_7804_ == 0)
{
uint64_t v___x_7805_; uint8_t v___x_7806_; 
v___x_7805_ = lean_uint64_land(v_quotient_7795_, v___x_7796_);
v___x_7806_ = lean_uint64_dec_eq(v___x_7805_, v___y_7772_);
if (v___x_7806_ == 0)
{
uint64_t v___x_7807_; 
v___x_7807_ = lean_uint64_add(v_quotient_7795_, v___x_7796_);
v___y_7761_ = v___y_7772_;
v___y_7762_ = v___y_7774_;
v___y_7763_ = v___y_7776_;
v___y_7764_ = v___y_7777_;
v___y_7765_ = v_position_7780_;
v___y_7766_ = v___x_7807_;
goto v___jp_7760_;
}
else
{
v___y_7761_ = v___y_7772_;
v___y_7762_ = v___y_7774_;
v___y_7763_ = v___y_7776_;
v___y_7764_ = v___y_7777_;
v___y_7765_ = v_position_7780_;
v___y_7766_ = v_quotient_7795_;
goto v___jp_7760_;
}
}
else
{
uint64_t v___x_7808_; 
v___x_7808_ = lean_uint64_add(v_quotient_7795_, v___x_7796_);
v___y_7761_ = v___y_7772_;
v___y_7762_ = v___y_7774_;
v___y_7763_ = v___y_7776_;
v___y_7764_ = v___y_7777_;
v___y_7765_ = v_position_7780_;
v___y_7766_ = v___x_7808_;
goto v___jp_7760_;
}
}
else
{
v___y_7761_ = v___y_7772_;
v___y_7762_ = v___y_7774_;
v___y_7763_ = v___y_7776_;
v___y_7764_ = v___y_7777_;
v___y_7765_ = v_position_7780_;
v___y_7766_ = v_quotient_7795_;
goto v___jp_7760_;
}
}
}
else
{
uint64_t v___x_7809_; 
v___x_7809_ = lean_unbox_uint64(v___y_7773_);
lean_dec(v___y_7773_);
v___y_7761_ = v___y_7772_;
v___y_7762_ = v___y_7774_;
v___y_7763_ = v___y_7776_;
v___y_7764_ = v___y_7777_;
v___y_7765_ = v_position_7780_;
v___y_7766_ = v___x_7809_;
goto v___jp_7760_;
}
}
else
{
uint64_t v___x_7810_; uint64_t v___x_7811_; uint64_t v___x_7812_; 
v___x_7810_ = lean_uint64_sub(v___x_7783_, v___y_7779_);
v___x_7811_ = lean_unbox_uint64(v___y_7773_);
lean_dec(v___y_7773_);
v___x_7812_ = lean_uint64_shift_left(v___x_7811_, v___x_7810_);
v___y_7761_ = v___y_7772_;
v___y_7762_ = v___y_7774_;
v___y_7763_ = v___y_7776_;
v___y_7764_ = v___y_7777_;
v___y_7765_ = v_position_7780_;
v___y_7766_ = v___x_7812_;
goto v___jp_7760_;
}
}
else
{
uint8_t v___x_7813_; 
v___x_7813_ = lean_uint64_dec_lt(v___y_7778_, v___y_7775_);
if (v___x_7813_ == 0)
{
uint64_t v___x_7814_; uint64_t v___x_7815_; uint64_t v___x_7816_; 
v___x_7814_ = lean_uint64_sub(v___y_7778_, v___y_7775_);
v___x_7815_ = lean_unbox_uint64(v___y_7773_);
lean_dec(v___y_7773_);
v___x_7816_ = lean_uint64_shift_left(v___x_7815_, v___x_7814_);
v___y_7694_ = v___y_7772_;
v___y_7695_ = v___y_7776_;
v___y_7696_ = v___x_7816_;
goto v___jp_7693_;
}
else
{
uint64_t v___x_7817_; uint8_t v___x_7818_; 
v___x_7817_ = lean_uint64_sub(v___y_7775_, v___y_7778_);
v___x_7818_ = lean_uint64_dec_eq(v___x_7817_, v___y_7772_);
if (v___x_7818_ == 0)
{
uint64_t v___x_7819_; uint8_t v___x_7820_; 
v___x_7819_ = 64ULL;
v___x_7820_ = lean_uint64_dec_lt(v___x_7817_, v___x_7819_);
if (v___x_7820_ == 0)
{
uint8_t v___x_7821_; 
v___x_7821_ = lean_uint64_dec_eq(v___x_7817_, v___x_7819_);
if (v___x_7821_ == 0)
{
lean_dec(v___y_7773_);
v___y_7694_ = v___y_7772_;
v___y_7695_ = v___y_7776_;
v___y_7696_ = v___y_7772_;
goto v___jp_7693_;
}
else
{
uint64_t v___x_7822_; uint64_t v___x_7823_; uint8_t v___x_7824_; 
v___x_7822_ = 9223372036854775808ULL;
v___x_7823_ = lean_unbox_uint64(v___y_7773_);
lean_dec(v___y_7773_);
v___x_7824_ = lean_uint64_dec_lt(v___x_7822_, v___x_7823_);
if (v___x_7824_ == 0)
{
v___y_7694_ = v___y_7772_;
v___y_7695_ = v___y_7776_;
v___y_7696_ = v___y_7772_;
goto v___jp_7693_;
}
else
{
uint64_t v___x_7825_; 
v___x_7825_ = 1ULL;
v___y_7694_ = v___y_7772_;
v___y_7695_ = v___y_7776_;
v___y_7696_ = v___x_7825_;
goto v___jp_7693_;
}
}
}
else
{
uint64_t v___x_7826_; uint64_t v_quotient_7827_; uint64_t v___x_7828_; uint64_t v___x_7829_; uint64_t v___x_7830_; uint64_t v___x_7831_; uint64_t v_remainder_7832_; uint64_t v___x_7833_; uint64_t v_half_7834_; uint8_t v___x_7835_; 
v___x_7826_ = lean_unbox_uint64(v___y_7773_);
v_quotient_7827_ = lean_uint64_shift_right(v___x_7826_, v___x_7817_);
v___x_7828_ = 1ULL;
v___x_7829_ = lean_uint64_shift_left(v___x_7828_, v___x_7817_);
v___x_7830_ = lean_uint64_sub(v___x_7829_, v___x_7828_);
v___x_7831_ = lean_unbox_uint64(v___y_7773_);
lean_dec(v___y_7773_);
v_remainder_7832_ = lean_uint64_land(v___x_7831_, v___x_7830_);
v___x_7833_ = lean_uint64_sub(v___x_7817_, v___x_7828_);
v_half_7834_ = lean_uint64_shift_left(v___x_7828_, v___x_7833_);
v___x_7835_ = lean_uint64_dec_lt(v_remainder_7832_, v_half_7834_);
if (v___x_7835_ == 0)
{
uint8_t v___x_7836_; 
v___x_7836_ = lean_uint64_dec_lt(v_half_7834_, v_remainder_7832_);
if (v___x_7836_ == 0)
{
uint64_t v___x_7837_; uint8_t v___x_7838_; 
v___x_7837_ = lean_uint64_land(v_quotient_7827_, v___x_7828_);
v___x_7838_ = lean_uint64_dec_eq(v___x_7837_, v___y_7772_);
if (v___x_7838_ == 0)
{
uint64_t v___x_7839_; 
v___x_7839_ = lean_uint64_add(v_quotient_7827_, v___x_7828_);
v___y_7694_ = v___y_7772_;
v___y_7695_ = v___y_7776_;
v___y_7696_ = v___x_7839_;
goto v___jp_7693_;
}
else
{
v___y_7694_ = v___y_7772_;
v___y_7695_ = v___y_7776_;
v___y_7696_ = v_quotient_7827_;
goto v___jp_7693_;
}
}
else
{
uint64_t v___x_7840_; 
v___x_7840_ = lean_uint64_add(v_quotient_7827_, v___x_7828_);
v___y_7694_ = v___y_7772_;
v___y_7695_ = v___y_7776_;
v___y_7696_ = v___x_7840_;
goto v___jp_7693_;
}
}
else
{
v___y_7694_ = v___y_7772_;
v___y_7695_ = v___y_7776_;
v___y_7696_ = v_quotient_7827_;
goto v___jp_7693_;
}
}
}
else
{
uint64_t v___x_7841_; 
v___x_7841_ = lean_unbox_uint64(v___y_7773_);
lean_dec(v___y_7773_);
v___y_7694_ = v___y_7772_;
v___y_7695_ = v___y_7776_;
v___y_7696_ = v___x_7841_;
goto v___jp_7693_;
}
}
}
}
v___jp_7842_:
{
uint64_t v___x_7852_; uint64_t v___x_7853_; uint8_t v___x_7854_; 
v___x_7852_ = 1ULL;
v___x_7853_ = lean_uint64_shift_right(v___y_7848_, v___x_7852_);
v___x_7854_ = lean_uint64_dec_eq(v___x_7853_, v___y_7843_);
if (v___x_7854_ == 0)
{
uint64_t v___x_7855_; 
v___x_7855_ = lean_uint64_add(v___y_7851_, v___x_7852_);
v___y_7772_ = v___y_7843_;
v___y_7773_ = v___y_7845_;
v___y_7774_ = v___y_7844_;
v___y_7775_ = v___y_7846_;
v___y_7776_ = v___y_7847_;
v___y_7777_ = v___y_7849_;
v___y_7778_ = v___y_7850_;
v___y_7779_ = v___x_7855_;
goto v___jp_7771_;
}
else
{
v___y_7772_ = v___y_7843_;
v___y_7773_ = v___y_7845_;
v___y_7774_ = v___y_7844_;
v___y_7775_ = v___y_7846_;
v___y_7776_ = v___y_7847_;
v___y_7777_ = v___y_7849_;
v___y_7778_ = v___y_7850_;
v___y_7779_ = v___y_7851_;
goto v___jp_7771_;
}
}
v___jp_7856_:
{
uint64_t v___x_7868_; uint8_t v___x_7869_; 
v___x_7868_ = lean_uint64_shift_right(v___y_7857_, v___y_7859_);
v___x_7869_ = lean_uint64_dec_eq(v___x_7868_, v___y_7858_);
if (v___x_7869_ == 0)
{
uint64_t v___x_7870_; 
v___x_7870_ = lean_uint64_add(v___y_7865_, v___y_7859_);
v___y_7843_ = v___y_7858_;
v___y_7844_ = v___y_7861_;
v___y_7845_ = v___y_7860_;
v___y_7846_ = v___y_7862_;
v___y_7847_ = v___y_7863_;
v___y_7848_ = v___y_7867_;
v___y_7849_ = v___y_7864_;
v___y_7850_ = v___y_7866_;
v___y_7851_ = v___x_7870_;
goto v___jp_7842_;
}
else
{
v___y_7843_ = v___y_7858_;
v___y_7844_ = v___y_7861_;
v___y_7845_ = v___y_7860_;
v___y_7846_ = v___y_7862_;
v___y_7847_ = v___y_7863_;
v___y_7848_ = v___y_7867_;
v___y_7849_ = v___y_7864_;
v___y_7850_ = v___y_7866_;
v___y_7851_ = v___y_7865_;
goto v___jp_7842_;
}
}
v___jp_7871_:
{
uint64_t v___x_7881_; uint64_t v___x_7882_; uint8_t v___x_7883_; 
v___x_7881_ = 2ULL;
v___x_7882_ = lean_uint64_shift_right(v___y_7872_, v___x_7881_);
v___x_7883_ = lean_uint64_dec_eq(v___x_7882_, v___y_7873_);
if (v___x_7883_ == 0)
{
v___y_7857_ = v___y_7872_;
v___y_7858_ = v___y_7873_;
v___y_7859_ = v___x_7881_;
v___y_7860_ = v___y_7875_;
v___y_7861_ = v___y_7874_;
v___y_7862_ = v___y_7876_;
v___y_7863_ = v___y_7877_;
v___y_7864_ = v___y_7878_;
v___y_7865_ = v___y_7880_;
v___y_7866_ = v___y_7879_;
v___y_7867_ = v___x_7882_;
goto v___jp_7856_;
}
else
{
v___y_7857_ = v___y_7872_;
v___y_7858_ = v___y_7873_;
v___y_7859_ = v___x_7881_;
v___y_7860_ = v___y_7875_;
v___y_7861_ = v___y_7874_;
v___y_7862_ = v___y_7876_;
v___y_7863_ = v___y_7877_;
v___y_7864_ = v___y_7878_;
v___y_7865_ = v___y_7880_;
v___y_7866_ = v___y_7879_;
v___y_7867_ = v___y_7872_;
goto v___jp_7856_;
}
}
v___jp_7884_:
{
uint64_t v___x_7896_; uint8_t v___x_7897_; 
v___x_7896_ = lean_uint64_shift_right(v___y_7890_, v___y_7892_);
v___x_7897_ = lean_uint64_dec_eq(v___x_7896_, v___y_7885_);
if (v___x_7897_ == 0)
{
uint64_t v___x_7898_; 
v___x_7898_ = lean_uint64_add(v___y_7891_, v___y_7892_);
v___y_7872_ = v___y_7895_;
v___y_7873_ = v___y_7885_;
v___y_7874_ = v___y_7887_;
v___y_7875_ = v___y_7886_;
v___y_7876_ = v___y_7888_;
v___y_7877_ = v___y_7889_;
v___y_7878_ = v___y_7893_;
v___y_7879_ = v___y_7894_;
v___y_7880_ = v___x_7898_;
goto v___jp_7871_;
}
else
{
v___y_7872_ = v___y_7895_;
v___y_7873_ = v___y_7885_;
v___y_7874_ = v___y_7887_;
v___y_7875_ = v___y_7886_;
v___y_7876_ = v___y_7888_;
v___y_7877_ = v___y_7889_;
v___y_7878_ = v___y_7893_;
v___y_7879_ = v___y_7894_;
v___y_7880_ = v___y_7891_;
goto v___jp_7871_;
}
}
v___jp_7899_:
{
uint64_t v___x_7909_; uint64_t v___x_7910_; uint8_t v___x_7911_; 
v___x_7909_ = 4ULL;
v___x_7910_ = lean_uint64_shift_right(v___y_7905_, v___x_7909_);
v___x_7911_ = lean_uint64_dec_eq(v___x_7910_, v___y_7900_);
if (v___x_7911_ == 0)
{
v___y_7885_ = v___y_7900_;
v___y_7886_ = v___y_7902_;
v___y_7887_ = v___y_7901_;
v___y_7888_ = v___y_7903_;
v___y_7889_ = v___y_7904_;
v___y_7890_ = v___y_7905_;
v___y_7891_ = v___y_7908_;
v___y_7892_ = v___x_7909_;
v___y_7893_ = v___y_7906_;
v___y_7894_ = v___y_7907_;
v___y_7895_ = v___x_7910_;
goto v___jp_7884_;
}
else
{
v___y_7885_ = v___y_7900_;
v___y_7886_ = v___y_7902_;
v___y_7887_ = v___y_7901_;
v___y_7888_ = v___y_7903_;
v___y_7889_ = v___y_7904_;
v___y_7890_ = v___y_7905_;
v___y_7891_ = v___y_7908_;
v___y_7892_ = v___x_7909_;
v___y_7893_ = v___y_7906_;
v___y_7894_ = v___y_7907_;
v___y_7895_ = v___y_7905_;
goto v___jp_7884_;
}
}
v___jp_7912_:
{
uint64_t v___x_7924_; uint8_t v___x_7925_; 
v___x_7924_ = lean_uint64_shift_right(v___y_7917_, v___y_7918_);
v___x_7925_ = lean_uint64_dec_eq(v___x_7924_, v___y_7913_);
if (v___x_7925_ == 0)
{
uint64_t v___x_7926_; 
v___x_7926_ = lean_uint64_add(v___y_7920_, v___y_7918_);
v___y_7900_ = v___y_7913_;
v___y_7901_ = v___y_7915_;
v___y_7902_ = v___y_7914_;
v___y_7903_ = v___y_7916_;
v___y_7904_ = v___y_7919_;
v___y_7905_ = v___y_7923_;
v___y_7906_ = v___y_7921_;
v___y_7907_ = v___y_7922_;
v___y_7908_ = v___x_7926_;
goto v___jp_7899_;
}
else
{
v___y_7900_ = v___y_7913_;
v___y_7901_ = v___y_7915_;
v___y_7902_ = v___y_7914_;
v___y_7903_ = v___y_7916_;
v___y_7904_ = v___y_7919_;
v___y_7905_ = v___y_7923_;
v___y_7906_ = v___y_7921_;
v___y_7907_ = v___y_7922_;
v___y_7908_ = v___y_7920_;
goto v___jp_7899_;
}
}
v___jp_7927_:
{
uint64_t v___x_7937_; uint64_t v___x_7938_; uint8_t v___x_7939_; 
v___x_7937_ = 8ULL;
v___x_7938_ = lean_uint64_shift_right(v___y_7932_, v___x_7937_);
v___x_7939_ = lean_uint64_dec_eq(v___x_7938_, v___y_7928_);
if (v___x_7939_ == 0)
{
v___y_7913_ = v___y_7928_;
v___y_7914_ = v___y_7930_;
v___y_7915_ = v___y_7929_;
v___y_7916_ = v___y_7931_;
v___y_7917_ = v___y_7932_;
v___y_7918_ = v___x_7937_;
v___y_7919_ = v___y_7933_;
v___y_7920_ = v___y_7936_;
v___y_7921_ = v___y_7934_;
v___y_7922_ = v___y_7935_;
v___y_7923_ = v___x_7938_;
goto v___jp_7912_;
}
else
{
v___y_7913_ = v___y_7928_;
v___y_7914_ = v___y_7930_;
v___y_7915_ = v___y_7929_;
v___y_7916_ = v___y_7931_;
v___y_7917_ = v___y_7932_;
v___y_7918_ = v___x_7937_;
v___y_7919_ = v___y_7933_;
v___y_7920_ = v___y_7936_;
v___y_7921_ = v___y_7934_;
v___y_7922_ = v___y_7935_;
v___y_7923_ = v___y_7932_;
goto v___jp_7912_;
}
}
v___jp_7940_:
{
uint64_t v___x_7952_; uint8_t v___x_7953_; 
v___x_7952_ = lean_uint64_shift_right(v___y_7948_, v___y_7945_);
v___x_7953_ = lean_uint64_dec_eq(v___x_7952_, v___y_7942_);
if (v___x_7953_ == 0)
{
uint64_t v___x_7954_; 
v___x_7954_ = lean_uint64_add(v___y_7941_, v___y_7945_);
v___y_7928_ = v___y_7942_;
v___y_7929_ = v___y_7944_;
v___y_7930_ = v___y_7943_;
v___y_7931_ = v___y_7946_;
v___y_7932_ = v___y_7951_;
v___y_7933_ = v___y_7947_;
v___y_7934_ = v___y_7949_;
v___y_7935_ = v___y_7950_;
v___y_7936_ = v___x_7954_;
goto v___jp_7927_;
}
else
{
v___y_7928_ = v___y_7942_;
v___y_7929_ = v___y_7944_;
v___y_7930_ = v___y_7943_;
v___y_7931_ = v___y_7946_;
v___y_7932_ = v___y_7951_;
v___y_7933_ = v___y_7947_;
v___y_7934_ = v___y_7949_;
v___y_7935_ = v___y_7950_;
v___y_7936_ = v___y_7941_;
goto v___jp_7927_;
}
}
v___jp_7955_:
{
uint64_t v___x_7965_; uint64_t v___x_7966_; uint8_t v___x_7967_; 
v___x_7965_ = 16ULL;
v___x_7966_ = lean_uint64_shift_right(v___y_7962_, v___x_7965_);
v___x_7967_ = lean_uint64_dec_eq(v___x_7966_, v___y_7956_);
if (v___x_7967_ == 0)
{
v___y_7941_ = v___y_7964_;
v___y_7942_ = v___y_7956_;
v___y_7943_ = v___y_7958_;
v___y_7944_ = v___y_7957_;
v___y_7945_ = v___x_7965_;
v___y_7946_ = v___y_7959_;
v___y_7947_ = v___y_7960_;
v___y_7948_ = v___y_7962_;
v___y_7949_ = v___y_7961_;
v___y_7950_ = v___y_7963_;
v___y_7951_ = v___x_7966_;
goto v___jp_7940_;
}
else
{
v___y_7941_ = v___y_7964_;
v___y_7942_ = v___y_7956_;
v___y_7943_ = v___y_7958_;
v___y_7944_ = v___y_7957_;
v___y_7945_ = v___x_7965_;
v___y_7946_ = v___y_7959_;
v___y_7947_ = v___y_7960_;
v___y_7948_ = v___y_7962_;
v___y_7949_ = v___y_7961_;
v___y_7950_ = v___y_7963_;
v___y_7951_ = v___y_7962_;
goto v___jp_7940_;
}
}
v___jp_7968_:
{
uint64_t v___x_7978_; uint64_t v___x_7979_; uint8_t v___x_7980_; 
v___x_7978_ = lean_unbox_uint64(v___y_7970_);
v___x_7979_ = lean_uint64_shift_right(v___x_7978_, v___y_7972_);
v___x_7980_ = lean_uint64_dec_eq(v___x_7979_, v___y_7969_);
if (v___x_7980_ == 0)
{
v___y_7956_ = v___y_7969_;
v___y_7957_ = v___y_7971_;
v___y_7958_ = v___y_7970_;
v___y_7959_ = v___y_7973_;
v___y_7960_ = v___y_7974_;
v___y_7961_ = v___y_7975_;
v___y_7962_ = v___y_7977_;
v___y_7963_ = v___y_7976_;
v___y_7964_ = v___y_7972_;
goto v___jp_7955_;
}
else
{
v___y_7956_ = v___y_7969_;
v___y_7957_ = v___y_7971_;
v___y_7958_ = v___y_7970_;
v___y_7959_ = v___y_7973_;
v___y_7960_ = v___y_7974_;
v___y_7961_ = v___y_7975_;
v___y_7962_ = v___y_7977_;
v___y_7963_ = v___y_7976_;
v___y_7964_ = v___y_7969_;
goto v___jp_7955_;
}
}
v___jp_7981_:
{
uint64_t v___x_7987_; uint64_t v___x_7988_; uint8_t v___x_7989_; 
v___x_7987_ = 0ULL;
v___x_7988_ = lean_unbox_uint64(v_snd_7986_);
v___x_7989_ = lean_uint64_dec_eq(v___x_7988_, v___x_7987_);
if (v___x_7989_ == 0)
{
uint64_t v___x_7990_; uint64_t v___x_7991_; uint64_t v___x_7992_; uint64_t v___x_7993_; uint64_t v___x_7994_; uint8_t v___x_7995_; 
v___x_7990_ = 149ULL;
v___x_7991_ = lean_uint64_add(v___y_7983_, v___x_7990_);
v___x_7992_ = 32ULL;
v___x_7993_ = lean_unbox_uint64(v_snd_7986_);
v___x_7994_ = lean_uint64_shift_right(v___x_7993_, v___x_7992_);
v___x_7995_ = lean_uint64_dec_eq(v___x_7994_, v___x_7987_);
if (v___x_7995_ == 0)
{
v___y_7969_ = v___x_7987_;
v___y_7970_ = v_snd_7986_;
v___y_7971_ = v___y_7982_;
v___y_7972_ = v___x_7992_;
v___y_7973_ = v___x_7990_;
v___y_7974_ = v_fst_7985_;
v___y_7975_ = v___y_7984_;
v___y_7976_ = v___x_7991_;
v___y_7977_ = v___x_7994_;
goto v___jp_7968_;
}
else
{
uint64_t v___x_7996_; 
v___x_7996_ = lean_unbox_uint64(v_snd_7986_);
v___y_7969_ = v___x_7987_;
v___y_7970_ = v_snd_7986_;
v___y_7971_ = v___y_7982_;
v___y_7972_ = v___x_7992_;
v___y_7973_ = v___x_7990_;
v___y_7974_ = v_fst_7985_;
v___y_7975_ = v___y_7984_;
v___y_7976_ = v___x_7991_;
v___y_7977_ = v___x_7996_;
goto v___jp_7968_;
}
}
else
{
uint8_t v___x_7997_; 
lean_dec(v_snd_7986_);
v___x_7997_ = lean_unbox(v_fst_7985_);
lean_dec(v_fst_7985_);
if (v___x_7997_ == 0)
{
uint32_t v___x_7998_; 
v___x_7998_ = 0;
return v___x_7998_;
}
else
{
uint32_t v___x_7999_; 
v___x_7999_ = 2147483648;
return v___x_7999_;
}
}
}
v___jp_8000_:
{
uint32_t v___x_8003_; uint32_t v___x_8004_; uint32_t v___x_8005_; 
v___x_8003_ = 8388607;
v___x_8004_ = lean_uint32_land(v___y_8001_, v___x_8003_);
v___x_8005_ = lean_uint32_lor(v___y_8002_, v___x_8004_);
return v___x_8005_;
}
v___jp_8006_:
{
uint8_t v___x_8010_; 
v___x_8010_ = lean_uint64_dec_eq(v___y_8009_, v___y_8008_);
if (v___x_8010_ == 0)
{
uint64_t v___x_8011_; uint8_t v___x_8012_; 
v___x_8011_ = 8388608ULL;
v___x_8012_ = lean_uint64_dec_eq(v___y_8009_, v___x_8011_);
if (v___x_8012_ == 0)
{
uint32_t v___x_8013_; uint8_t v___x_8014_; 
v___x_8013_ = lean_uint64_to_uint32(v___y_8009_);
v___x_8014_ = lean_unbox(v___y_8007_);
lean_dec(v___y_8007_);
if (v___x_8014_ == 0)
{
uint32_t v___x_8015_; 
v___x_8015_ = 0;
v___y_8001_ = v___x_8013_;
v___y_8002_ = v___x_8015_;
goto v___jp_8000_;
}
else
{
uint32_t v___x_8016_; 
v___x_8016_ = 2147483648;
v___y_8001_ = v___x_8013_;
v___y_8002_ = v___x_8016_;
goto v___jp_8000_;
}
}
else
{
uint8_t v___x_8017_; 
v___x_8017_ = lean_unbox(v___y_8007_);
lean_dec(v___y_8007_);
if (v___x_8017_ == 0)
{
uint32_t v___x_8018_; 
v___x_8018_ = 0;
v___y_5099_ = v___x_8018_;
goto v___jp_5098_;
}
else
{
uint32_t v___x_8019_; 
v___x_8019_ = 2147483648;
v___y_5099_ = v___x_8019_;
goto v___jp_5098_;
}
}
}
else
{
uint8_t v___x_8020_; 
v___x_8020_ = lean_unbox(v___y_8007_);
lean_dec(v___y_8007_);
if (v___x_8020_ == 0)
{
uint32_t v___x_8021_; 
v___x_8021_ = 0;
return v___x_8021_;
}
else
{
uint32_t v___x_8022_; 
v___x_8022_ = 2147483648;
return v___x_8022_;
}
}
}
v___jp_8023_:
{
uint32_t v___x_8029_; uint32_t v___x_8030_; uint32_t v___x_8031_; uint32_t v___x_8032_; uint32_t v___x_8033_; uint32_t v___x_8034_; 
v___x_8029_ = lean_uint32_land(v___y_8025_, v___y_8024_);
v___x_8030_ = lean_uint32_shift_left(v___x_8029_, v___y_8026_);
v___x_8031_ = lean_uint32_lor(v___y_8028_, v___x_8030_);
v___x_8032_ = 8388607;
v___x_8033_ = lean_uint32_land(v___y_8027_, v___x_8032_);
v___x_8034_ = lean_uint32_lor(v___x_8031_, v___x_8033_);
return v___x_8034_;
}
v___jp_8035_:
{
uint8_t v___x_8041_; 
v___x_8041_ = lean_unbox(v___y_8038_);
lean_dec(v___y_8038_);
if (v___x_8041_ == 0)
{
uint32_t v___x_8042_; 
v___x_8042_ = 0;
v___y_8024_ = v___y_8036_;
v___y_8025_ = v___y_8037_;
v___y_8026_ = v___y_8039_;
v___y_8027_ = v___y_8040_;
v___y_8028_ = v___x_8042_;
goto v___jp_8023_;
}
else
{
uint32_t v___x_8043_; 
v___x_8043_ = 2147483648;
v___y_8024_ = v___y_8036_;
v___y_8025_ = v___y_8037_;
v___y_8026_ = v___y_8039_;
v___y_8027_ = v___y_8040_;
v___y_8028_ = v___x_8043_;
goto v___jp_8023_;
}
}
v___jp_8044_:
{
uint64_t v___x_8051_; uint64_t v_encodedExponent_8052_; uint32_t v___x_8053_; uint64_t v___x_8054_; uint8_t v___x_8055_; 
v___x_8051_ = 171ULL;
v_encodedExponent_8052_ = lean_uint64_sub(v___y_8046_, v___x_8051_);
v___x_8053_ = lean_uint64_to_uint32(v_encodedExponent_8052_);
v___x_8054_ = 8388608ULL;
v___x_8055_ = lean_uint64_dec_lt(v___y_8050_, v___x_8054_);
if (v___x_8055_ == 0)
{
uint64_t v___x_8056_; uint32_t v___x_8057_; 
v___x_8056_ = lean_uint64_sub(v___y_8050_, v___x_8054_);
v___x_8057_ = lean_uint64_to_uint32(v___x_8056_);
v___y_8036_ = v___y_8045_;
v___y_8037_ = v___x_8053_;
v___y_8038_ = v___y_8047_;
v___y_8039_ = v___y_8049_;
v___y_8040_ = v___x_8057_;
goto v___jp_8035_;
}
else
{
uint32_t v___x_8058_; 
v___x_8058_ = lean_uint64_to_uint32(v___y_8048_);
v___y_8036_ = v___y_8045_;
v___y_8037_ = v___x_8053_;
v___y_8038_ = v___y_8047_;
v___y_8039_ = v___y_8049_;
v___y_8040_ = v___x_8058_;
goto v___jp_8035_;
}
}
v___jp_8059_:
{
uint64_t v___x_8067_; uint8_t v___x_8068_; 
v___x_8067_ = 425ULL;
v___x_8068_ = lean_uint64_dec_lt(v___x_8067_, v___y_8066_);
if (v___x_8068_ == 0)
{
if (v___y_8060_ == 0)
{
v___y_8045_ = v___y_8061_;
v___y_8046_ = v___y_8066_;
v___y_8047_ = v___y_8063_;
v___y_8048_ = v___y_8064_;
v___y_8049_ = v___y_8065_;
v___y_8050_ = v___y_8062_;
goto v___jp_8044_;
}
else
{
uint64_t v___x_8069_; 
v___x_8069_ = 8388608ULL;
v___y_8045_ = v___y_8061_;
v___y_8046_ = v___y_8066_;
v___y_8047_ = v___y_8063_;
v___y_8048_ = v___y_8064_;
v___y_8049_ = v___y_8065_;
v___y_8050_ = v___x_8069_;
goto v___jp_8044_;
}
}
else
{
uint8_t v___x_8070_; 
v___x_8070_ = lean_unbox(v___y_8063_);
lean_dec(v___y_8063_);
if (v___x_8070_ == 0)
{
uint32_t v___x_8071_; 
v___x_8071_ = 2139095040;
return v___x_8071_;
}
else
{
uint32_t v___x_8072_; 
v___x_8072_ = 4286578688;
return v___x_8072_;
}
}
}
v___jp_8073_:
{
uint64_t v___x_8080_; uint8_t v_carry_8081_; 
v___x_8080_ = 16777216ULL;
v_carry_8081_ = lean_uint64_dec_eq(v___y_8079_, v___x_8080_);
if (v_carry_8081_ == 0)
{
v___y_8060_ = v_carry_8081_;
v___y_8061_ = v___y_8074_;
v___y_8062_ = v___y_8079_;
v___y_8063_ = v___y_8076_;
v___y_8064_ = v___y_8077_;
v___y_8065_ = v___y_8078_;
v___y_8066_ = v___y_8075_;
goto v___jp_8059_;
}
else
{
uint64_t v___x_8082_; uint64_t v___x_8083_; 
v___x_8082_ = 1ULL;
v___x_8083_ = lean_uint64_add(v___y_8075_, v___x_8082_);
v___y_8060_ = v_carry_8081_;
v___y_8061_ = v___y_8074_;
v___y_8062_ = v___y_8079_;
v___y_8063_ = v___y_8076_;
v___y_8064_ = v___y_8077_;
v___y_8065_ = v___y_8078_;
v___y_8066_ = v___x_8083_;
goto v___jp_8059_;
}
}
v___jp_8084_:
{
uint64_t v_position_8093_; uint64_t v___x_8094_; uint8_t v___x_8095_; 
v_position_8093_ = lean_uint64_add(v___y_8092_, v___y_8085_);
v___x_8094_ = 172ULL;
v___x_8095_ = lean_uint64_dec_lt(v_position_8093_, v___x_8094_);
if (v___x_8095_ == 0)
{
uint64_t v___x_8096_; uint8_t v___x_8097_; 
v___x_8096_ = 23ULL;
v___x_8097_ = lean_uint64_dec_lt(v___y_8092_, v___x_8096_);
if (v___x_8097_ == 0)
{
uint64_t v___x_8098_; uint8_t v___x_8099_; 
v___x_8098_ = lean_uint64_sub(v___y_8092_, v___x_8096_);
v___x_8099_ = lean_uint64_dec_eq(v___x_8098_, v___y_8090_);
if (v___x_8099_ == 0)
{
uint64_t v___x_8100_; uint8_t v___x_8101_; 
v___x_8100_ = 64ULL;
v___x_8101_ = lean_uint64_dec_lt(v___x_8098_, v___x_8100_);
if (v___x_8101_ == 0)
{
uint8_t v___x_8102_; 
v___x_8102_ = lean_uint64_dec_eq(v___x_8098_, v___x_8100_);
if (v___x_8102_ == 0)
{
lean_dec(v___y_8087_);
v___y_8074_ = v___y_8086_;
v___y_8075_ = v_position_8093_;
v___y_8076_ = v___y_8089_;
v___y_8077_ = v___y_8090_;
v___y_8078_ = v___y_8091_;
v___y_8079_ = v___y_8090_;
goto v___jp_8073_;
}
else
{
uint64_t v___x_8103_; uint64_t v___x_8104_; uint8_t v___x_8105_; 
v___x_8103_ = 9223372036854775808ULL;
v___x_8104_ = lean_unbox_uint64(v___y_8087_);
lean_dec(v___y_8087_);
v___x_8105_ = lean_uint64_dec_lt(v___x_8103_, v___x_8104_);
if (v___x_8105_ == 0)
{
v___y_8074_ = v___y_8086_;
v___y_8075_ = v_position_8093_;
v___y_8076_ = v___y_8089_;
v___y_8077_ = v___y_8090_;
v___y_8078_ = v___y_8091_;
v___y_8079_ = v___y_8090_;
goto v___jp_8073_;
}
else
{
uint64_t v___x_8106_; 
v___x_8106_ = 1ULL;
v___y_8074_ = v___y_8086_;
v___y_8075_ = v_position_8093_;
v___y_8076_ = v___y_8089_;
v___y_8077_ = v___y_8090_;
v___y_8078_ = v___y_8091_;
v___y_8079_ = v___x_8106_;
goto v___jp_8073_;
}
}
}
else
{
uint64_t v___x_8107_; uint64_t v_quotient_8108_; uint64_t v___x_8109_; uint64_t v___x_8110_; uint64_t v___x_8111_; uint64_t v___x_8112_; uint64_t v_remainder_8113_; uint64_t v___x_8114_; uint64_t v_half_8115_; uint8_t v___x_8116_; 
v___x_8107_ = lean_unbox_uint64(v___y_8087_);
v_quotient_8108_ = lean_uint64_shift_right(v___x_8107_, v___x_8098_);
v___x_8109_ = 1ULL;
v___x_8110_ = lean_uint64_shift_left(v___x_8109_, v___x_8098_);
v___x_8111_ = lean_uint64_sub(v___x_8110_, v___x_8109_);
v___x_8112_ = lean_unbox_uint64(v___y_8087_);
lean_dec(v___y_8087_);
v_remainder_8113_ = lean_uint64_land(v___x_8112_, v___x_8111_);
v___x_8114_ = lean_uint64_sub(v___x_8098_, v___x_8109_);
v_half_8115_ = lean_uint64_shift_left(v___x_8109_, v___x_8114_);
v___x_8116_ = lean_uint64_dec_lt(v_remainder_8113_, v_half_8115_);
if (v___x_8116_ == 0)
{
uint8_t v___x_8117_; 
v___x_8117_ = lean_uint64_dec_lt(v_half_8115_, v_remainder_8113_);
if (v___x_8117_ == 0)
{
uint64_t v___x_8118_; uint8_t v___x_8119_; 
v___x_8118_ = lean_uint64_land(v_quotient_8108_, v___x_8109_);
v___x_8119_ = lean_uint64_dec_eq(v___x_8118_, v___y_8090_);
if (v___x_8119_ == 0)
{
uint64_t v___x_8120_; 
v___x_8120_ = lean_uint64_add(v_quotient_8108_, v___x_8109_);
v___y_8074_ = v___y_8086_;
v___y_8075_ = v_position_8093_;
v___y_8076_ = v___y_8089_;
v___y_8077_ = v___y_8090_;
v___y_8078_ = v___y_8091_;
v___y_8079_ = v___x_8120_;
goto v___jp_8073_;
}
else
{
v___y_8074_ = v___y_8086_;
v___y_8075_ = v_position_8093_;
v___y_8076_ = v___y_8089_;
v___y_8077_ = v___y_8090_;
v___y_8078_ = v___y_8091_;
v___y_8079_ = v_quotient_8108_;
goto v___jp_8073_;
}
}
else
{
uint64_t v___x_8121_; 
v___x_8121_ = lean_uint64_add(v_quotient_8108_, v___x_8109_);
v___y_8074_ = v___y_8086_;
v___y_8075_ = v_position_8093_;
v___y_8076_ = v___y_8089_;
v___y_8077_ = v___y_8090_;
v___y_8078_ = v___y_8091_;
v___y_8079_ = v___x_8121_;
goto v___jp_8073_;
}
}
else
{
v___y_8074_ = v___y_8086_;
v___y_8075_ = v_position_8093_;
v___y_8076_ = v___y_8089_;
v___y_8077_ = v___y_8090_;
v___y_8078_ = v___y_8091_;
v___y_8079_ = v_quotient_8108_;
goto v___jp_8073_;
}
}
}
else
{
uint64_t v___x_8122_; 
v___x_8122_ = lean_unbox_uint64(v___y_8087_);
lean_dec(v___y_8087_);
v___y_8074_ = v___y_8086_;
v___y_8075_ = v_position_8093_;
v___y_8076_ = v___y_8089_;
v___y_8077_ = v___y_8090_;
v___y_8078_ = v___y_8091_;
v___y_8079_ = v___x_8122_;
goto v___jp_8073_;
}
}
else
{
uint64_t v___x_8123_; uint64_t v___x_8124_; uint64_t v___x_8125_; 
v___x_8123_ = lean_uint64_sub(v___x_8096_, v___y_8092_);
v___x_8124_ = lean_unbox_uint64(v___y_8087_);
lean_dec(v___y_8087_);
v___x_8125_ = lean_uint64_shift_left(v___x_8124_, v___x_8123_);
v___y_8074_ = v___y_8086_;
v___y_8075_ = v_position_8093_;
v___y_8076_ = v___y_8089_;
v___y_8077_ = v___y_8090_;
v___y_8078_ = v___y_8091_;
v___y_8079_ = v___x_8125_;
goto v___jp_8073_;
}
}
else
{
uint8_t v___x_8126_; 
v___x_8126_ = lean_uint64_dec_lt(v___y_8085_, v___y_8088_);
if (v___x_8126_ == 0)
{
uint64_t v___x_8127_; uint64_t v___x_8128_; uint64_t v___x_8129_; 
v___x_8127_ = lean_uint64_sub(v___y_8085_, v___y_8088_);
v___x_8128_ = lean_unbox_uint64(v___y_8087_);
lean_dec(v___y_8087_);
v___x_8129_ = lean_uint64_shift_left(v___x_8128_, v___x_8127_);
v___y_8007_ = v___y_8089_;
v___y_8008_ = v___y_8090_;
v___y_8009_ = v___x_8129_;
goto v___jp_8006_;
}
else
{
uint64_t v___x_8130_; uint8_t v___x_8131_; 
v___x_8130_ = lean_uint64_sub(v___y_8088_, v___y_8085_);
v___x_8131_ = lean_uint64_dec_eq(v___x_8130_, v___y_8090_);
if (v___x_8131_ == 0)
{
uint64_t v___x_8132_; uint8_t v___x_8133_; 
v___x_8132_ = 64ULL;
v___x_8133_ = lean_uint64_dec_lt(v___x_8130_, v___x_8132_);
if (v___x_8133_ == 0)
{
uint8_t v___x_8134_; 
v___x_8134_ = lean_uint64_dec_eq(v___x_8130_, v___x_8132_);
if (v___x_8134_ == 0)
{
lean_dec(v___y_8087_);
v___y_8007_ = v___y_8089_;
v___y_8008_ = v___y_8090_;
v___y_8009_ = v___y_8090_;
goto v___jp_8006_;
}
else
{
uint64_t v___x_8135_; uint64_t v___x_8136_; uint8_t v___x_8137_; 
v___x_8135_ = 9223372036854775808ULL;
v___x_8136_ = lean_unbox_uint64(v___y_8087_);
lean_dec(v___y_8087_);
v___x_8137_ = lean_uint64_dec_lt(v___x_8135_, v___x_8136_);
if (v___x_8137_ == 0)
{
v___y_8007_ = v___y_8089_;
v___y_8008_ = v___y_8090_;
v___y_8009_ = v___y_8090_;
goto v___jp_8006_;
}
else
{
uint64_t v___x_8138_; 
v___x_8138_ = 1ULL;
v___y_8007_ = v___y_8089_;
v___y_8008_ = v___y_8090_;
v___y_8009_ = v___x_8138_;
goto v___jp_8006_;
}
}
}
else
{
uint64_t v___x_8139_; uint64_t v_quotient_8140_; uint64_t v___x_8141_; uint64_t v___x_8142_; uint64_t v___x_8143_; uint64_t v___x_8144_; uint64_t v_remainder_8145_; uint64_t v___x_8146_; uint64_t v_half_8147_; uint8_t v___x_8148_; 
v___x_8139_ = lean_unbox_uint64(v___y_8087_);
v_quotient_8140_ = lean_uint64_shift_right(v___x_8139_, v___x_8130_);
v___x_8141_ = 1ULL;
v___x_8142_ = lean_uint64_shift_left(v___x_8141_, v___x_8130_);
v___x_8143_ = lean_uint64_sub(v___x_8142_, v___x_8141_);
v___x_8144_ = lean_unbox_uint64(v___y_8087_);
lean_dec(v___y_8087_);
v_remainder_8145_ = lean_uint64_land(v___x_8144_, v___x_8143_);
v___x_8146_ = lean_uint64_sub(v___x_8130_, v___x_8141_);
v_half_8147_ = lean_uint64_shift_left(v___x_8141_, v___x_8146_);
v___x_8148_ = lean_uint64_dec_lt(v_remainder_8145_, v_half_8147_);
if (v___x_8148_ == 0)
{
uint8_t v___x_8149_; 
v___x_8149_ = lean_uint64_dec_lt(v_half_8147_, v_remainder_8145_);
if (v___x_8149_ == 0)
{
uint64_t v___x_8150_; uint8_t v___x_8151_; 
v___x_8150_ = lean_uint64_land(v_quotient_8140_, v___x_8141_);
v___x_8151_ = lean_uint64_dec_eq(v___x_8150_, v___y_8090_);
if (v___x_8151_ == 0)
{
uint64_t v___x_8152_; 
v___x_8152_ = lean_uint64_add(v_quotient_8140_, v___x_8141_);
v___y_8007_ = v___y_8089_;
v___y_8008_ = v___y_8090_;
v___y_8009_ = v___x_8152_;
goto v___jp_8006_;
}
else
{
v___y_8007_ = v___y_8089_;
v___y_8008_ = v___y_8090_;
v___y_8009_ = v_quotient_8140_;
goto v___jp_8006_;
}
}
else
{
uint64_t v___x_8153_; 
v___x_8153_ = lean_uint64_add(v_quotient_8140_, v___x_8141_);
v___y_8007_ = v___y_8089_;
v___y_8008_ = v___y_8090_;
v___y_8009_ = v___x_8153_;
goto v___jp_8006_;
}
}
else
{
v___y_8007_ = v___y_8089_;
v___y_8008_ = v___y_8090_;
v___y_8009_ = v_quotient_8140_;
goto v___jp_8006_;
}
}
}
else
{
uint64_t v___x_8154_; 
v___x_8154_ = lean_unbox_uint64(v___y_8087_);
lean_dec(v___y_8087_);
v___y_8007_ = v___y_8089_;
v___y_8008_ = v___y_8090_;
v___y_8009_ = v___x_8154_;
goto v___jp_8006_;
}
}
}
}
v___jp_8155_:
{
uint64_t v___x_8165_; uint64_t v___x_8166_; uint8_t v___x_8167_; 
v___x_8165_ = 1ULL;
v___x_8166_ = lean_uint64_shift_right(v___y_8158_, v___x_8165_);
v___x_8167_ = lean_uint64_dec_eq(v___x_8166_, v___y_8162_);
if (v___x_8167_ == 0)
{
uint64_t v___x_8168_; 
v___x_8168_ = lean_uint64_add(v___y_8164_, v___x_8165_);
v___y_8085_ = v___y_8156_;
v___y_8086_ = v___y_8157_;
v___y_8087_ = v___y_8159_;
v___y_8088_ = v___y_8161_;
v___y_8089_ = v___y_8160_;
v___y_8090_ = v___y_8162_;
v___y_8091_ = v___y_8163_;
v___y_8092_ = v___x_8168_;
goto v___jp_8084_;
}
else
{
v___y_8085_ = v___y_8156_;
v___y_8086_ = v___y_8157_;
v___y_8087_ = v___y_8159_;
v___y_8088_ = v___y_8161_;
v___y_8089_ = v___y_8160_;
v___y_8090_ = v___y_8162_;
v___y_8091_ = v___y_8163_;
v___y_8092_ = v___y_8164_;
goto v___jp_8084_;
}
}
v___jp_8169_:
{
uint64_t v___x_8181_; uint8_t v___x_8182_; 
v___x_8181_ = lean_uint64_shift_right(v___y_8175_, v___y_8173_);
v___x_8182_ = lean_uint64_dec_eq(v___x_8181_, v___y_8178_);
if (v___x_8182_ == 0)
{
uint64_t v___x_8183_; 
v___x_8183_ = lean_uint64_add(v___y_8171_, v___y_8173_);
v___y_8156_ = v___y_8170_;
v___y_8157_ = v___y_8172_;
v___y_8158_ = v___y_8180_;
v___y_8159_ = v___y_8174_;
v___y_8160_ = v___y_8177_;
v___y_8161_ = v___y_8176_;
v___y_8162_ = v___y_8178_;
v___y_8163_ = v___y_8179_;
v___y_8164_ = v___x_8183_;
goto v___jp_8155_;
}
else
{
v___y_8156_ = v___y_8170_;
v___y_8157_ = v___y_8172_;
v___y_8158_ = v___y_8180_;
v___y_8159_ = v___y_8174_;
v___y_8160_ = v___y_8177_;
v___y_8161_ = v___y_8176_;
v___y_8162_ = v___y_8178_;
v___y_8163_ = v___y_8179_;
v___y_8164_ = v___y_8171_;
goto v___jp_8155_;
}
}
v___jp_8184_:
{
uint64_t v___x_8194_; uint64_t v___x_8195_; uint8_t v___x_8196_; 
v___x_8194_ = 2ULL;
v___x_8195_ = lean_uint64_shift_right(v___y_8188_, v___x_8194_);
v___x_8196_ = lean_uint64_dec_eq(v___x_8195_, v___y_8191_);
if (v___x_8196_ == 0)
{
v___y_8170_ = v___y_8185_;
v___y_8171_ = v___y_8193_;
v___y_8172_ = v___y_8186_;
v___y_8173_ = v___x_8194_;
v___y_8174_ = v___y_8187_;
v___y_8175_ = v___y_8188_;
v___y_8176_ = v___y_8190_;
v___y_8177_ = v___y_8189_;
v___y_8178_ = v___y_8191_;
v___y_8179_ = v___y_8192_;
v___y_8180_ = v___x_8195_;
goto v___jp_8169_;
}
else
{
v___y_8170_ = v___y_8185_;
v___y_8171_ = v___y_8193_;
v___y_8172_ = v___y_8186_;
v___y_8173_ = v___x_8194_;
v___y_8174_ = v___y_8187_;
v___y_8175_ = v___y_8188_;
v___y_8176_ = v___y_8190_;
v___y_8177_ = v___y_8189_;
v___y_8178_ = v___y_8191_;
v___y_8179_ = v___y_8192_;
v___y_8180_ = v___y_8188_;
goto v___jp_8169_;
}
}
v___jp_8197_:
{
uint64_t v___x_8209_; uint8_t v___x_8210_; 
v___x_8209_ = lean_uint64_shift_right(v___y_8198_, v___y_8205_);
v___x_8210_ = lean_uint64_dec_eq(v___x_8209_, v___y_8206_);
if (v___x_8210_ == 0)
{
uint64_t v___x_8211_; 
v___x_8211_ = lean_uint64_add(v___y_8202_, v___y_8205_);
v___y_8185_ = v___y_8199_;
v___y_8186_ = v___y_8200_;
v___y_8187_ = v___y_8201_;
v___y_8188_ = v___y_8208_;
v___y_8189_ = v___y_8204_;
v___y_8190_ = v___y_8203_;
v___y_8191_ = v___y_8206_;
v___y_8192_ = v___y_8207_;
v___y_8193_ = v___x_8211_;
goto v___jp_8184_;
}
else
{
v___y_8185_ = v___y_8199_;
v___y_8186_ = v___y_8200_;
v___y_8187_ = v___y_8201_;
v___y_8188_ = v___y_8208_;
v___y_8189_ = v___y_8204_;
v___y_8190_ = v___y_8203_;
v___y_8191_ = v___y_8206_;
v___y_8192_ = v___y_8207_;
v___y_8193_ = v___y_8202_;
goto v___jp_8184_;
}
}
v___jp_8212_:
{
uint64_t v___x_8222_; uint64_t v___x_8223_; uint8_t v___x_8224_; 
v___x_8222_ = 4ULL;
v___x_8223_ = lean_uint64_shift_right(v___y_8213_, v___x_8222_);
v___x_8224_ = lean_uint64_dec_eq(v___x_8223_, v___y_8219_);
if (v___x_8224_ == 0)
{
v___y_8198_ = v___y_8213_;
v___y_8199_ = v___y_8214_;
v___y_8200_ = v___y_8215_;
v___y_8201_ = v___y_8216_;
v___y_8202_ = v___y_8221_;
v___y_8203_ = v___y_8218_;
v___y_8204_ = v___y_8217_;
v___y_8205_ = v___x_8222_;
v___y_8206_ = v___y_8219_;
v___y_8207_ = v___y_8220_;
v___y_8208_ = v___x_8223_;
goto v___jp_8197_;
}
else
{
v___y_8198_ = v___y_8213_;
v___y_8199_ = v___y_8214_;
v___y_8200_ = v___y_8215_;
v___y_8201_ = v___y_8216_;
v___y_8202_ = v___y_8221_;
v___y_8203_ = v___y_8218_;
v___y_8204_ = v___y_8217_;
v___y_8205_ = v___x_8222_;
v___y_8206_ = v___y_8219_;
v___y_8207_ = v___y_8220_;
v___y_8208_ = v___y_8213_;
goto v___jp_8197_;
}
}
v___jp_8225_:
{
uint64_t v___x_8237_; uint8_t v___x_8238_; 
v___x_8237_ = lean_uint64_shift_right(v___y_8227_, v___y_8226_);
v___x_8238_ = lean_uint64_dec_eq(v___x_8237_, v___y_8234_);
if (v___x_8238_ == 0)
{
uint64_t v___x_8239_; 
v___x_8239_ = lean_uint64_add(v___y_8230_, v___y_8226_);
v___y_8213_ = v___y_8236_;
v___y_8214_ = v___y_8228_;
v___y_8215_ = v___y_8229_;
v___y_8216_ = v___y_8231_;
v___y_8217_ = v___y_8233_;
v___y_8218_ = v___y_8232_;
v___y_8219_ = v___y_8234_;
v___y_8220_ = v___y_8235_;
v___y_8221_ = v___x_8239_;
goto v___jp_8212_;
}
else
{
v___y_8213_ = v___y_8236_;
v___y_8214_ = v___y_8228_;
v___y_8215_ = v___y_8229_;
v___y_8216_ = v___y_8231_;
v___y_8217_ = v___y_8233_;
v___y_8218_ = v___y_8232_;
v___y_8219_ = v___y_8234_;
v___y_8220_ = v___y_8235_;
v___y_8221_ = v___y_8230_;
goto v___jp_8212_;
}
}
v___jp_8240_:
{
uint64_t v___x_8250_; uint64_t v___x_8251_; uint8_t v___x_8252_; 
v___x_8250_ = 8ULL;
v___x_8251_ = lean_uint64_shift_right(v___y_8242_, v___x_8250_);
v___x_8252_ = lean_uint64_dec_eq(v___x_8251_, v___y_8247_);
if (v___x_8252_ == 0)
{
v___y_8226_ = v___x_8250_;
v___y_8227_ = v___y_8242_;
v___y_8228_ = v___y_8241_;
v___y_8229_ = v___y_8243_;
v___y_8230_ = v___y_8249_;
v___y_8231_ = v___y_8244_;
v___y_8232_ = v___y_8246_;
v___y_8233_ = v___y_8245_;
v___y_8234_ = v___y_8247_;
v___y_8235_ = v___y_8248_;
v___y_8236_ = v___x_8251_;
goto v___jp_8225_;
}
else
{
v___y_8226_ = v___x_8250_;
v___y_8227_ = v___y_8242_;
v___y_8228_ = v___y_8241_;
v___y_8229_ = v___y_8243_;
v___y_8230_ = v___y_8249_;
v___y_8231_ = v___y_8244_;
v___y_8232_ = v___y_8246_;
v___y_8233_ = v___y_8245_;
v___y_8234_ = v___y_8247_;
v___y_8235_ = v___y_8248_;
v___y_8236_ = v___y_8242_;
goto v___jp_8225_;
}
}
v___jp_8253_:
{
uint64_t v___x_8265_; uint8_t v___x_8266_; 
v___x_8265_ = lean_uint64_shift_right(v___y_8258_, v___y_8263_);
v___x_8266_ = lean_uint64_dec_eq(v___x_8265_, v___y_8261_);
if (v___x_8266_ == 0)
{
uint64_t v___x_8267_; 
v___x_8267_ = lean_uint64_add(v___y_8256_, v___y_8263_);
v___y_8241_ = v___y_8254_;
v___y_8242_ = v___y_8264_;
v___y_8243_ = v___y_8255_;
v___y_8244_ = v___y_8257_;
v___y_8245_ = v___y_8260_;
v___y_8246_ = v___y_8259_;
v___y_8247_ = v___y_8261_;
v___y_8248_ = v___y_8262_;
v___y_8249_ = v___x_8267_;
goto v___jp_8240_;
}
else
{
v___y_8241_ = v___y_8254_;
v___y_8242_ = v___y_8264_;
v___y_8243_ = v___y_8255_;
v___y_8244_ = v___y_8257_;
v___y_8245_ = v___y_8260_;
v___y_8246_ = v___y_8259_;
v___y_8247_ = v___y_8261_;
v___y_8248_ = v___y_8262_;
v___y_8249_ = v___y_8256_;
goto v___jp_8240_;
}
}
v___jp_8268_:
{
uint64_t v___x_8278_; uint64_t v___x_8279_; uint8_t v___x_8280_; 
v___x_8278_ = 16ULL;
v___x_8279_ = lean_uint64_shift_right(v___y_8272_, v___x_8278_);
v___x_8280_ = lean_uint64_dec_eq(v___x_8279_, v___y_8275_);
if (v___x_8280_ == 0)
{
v___y_8254_ = v___y_8269_;
v___y_8255_ = v___y_8270_;
v___y_8256_ = v___y_8277_;
v___y_8257_ = v___y_8271_;
v___y_8258_ = v___y_8272_;
v___y_8259_ = v___y_8274_;
v___y_8260_ = v___y_8273_;
v___y_8261_ = v___y_8275_;
v___y_8262_ = v___y_8276_;
v___y_8263_ = v___x_8278_;
v___y_8264_ = v___x_8279_;
goto v___jp_8253_;
}
else
{
v___y_8254_ = v___y_8269_;
v___y_8255_ = v___y_8270_;
v___y_8256_ = v___y_8277_;
v___y_8257_ = v___y_8271_;
v___y_8258_ = v___y_8272_;
v___y_8259_ = v___y_8274_;
v___y_8260_ = v___y_8273_;
v___y_8261_ = v___y_8275_;
v___y_8262_ = v___y_8276_;
v___y_8263_ = v___x_8278_;
v___y_8264_ = v___y_8272_;
goto v___jp_8253_;
}
}
v___jp_8281_:
{
uint64_t v___x_8291_; uint64_t v___x_8292_; uint8_t v___x_8293_; 
v___x_8291_ = lean_unbox_uint64(v___y_8285_);
v___x_8292_ = lean_uint64_shift_right(v___x_8291_, v___y_8284_);
v___x_8293_ = lean_uint64_dec_eq(v___x_8292_, v___y_8288_);
if (v___x_8293_ == 0)
{
v___y_8269_ = v___y_8282_;
v___y_8270_ = v___y_8283_;
v___y_8271_ = v___y_8285_;
v___y_8272_ = v___y_8290_;
v___y_8273_ = v___y_8287_;
v___y_8274_ = v___y_8286_;
v___y_8275_ = v___y_8288_;
v___y_8276_ = v___y_8289_;
v___y_8277_ = v___y_8284_;
goto v___jp_8268_;
}
else
{
v___y_8269_ = v___y_8282_;
v___y_8270_ = v___y_8283_;
v___y_8271_ = v___y_8285_;
v___y_8272_ = v___y_8290_;
v___y_8273_ = v___y_8287_;
v___y_8274_ = v___y_8286_;
v___y_8275_ = v___y_8288_;
v___y_8276_ = v___y_8289_;
v___y_8277_ = v___y_8288_;
goto v___jp_8268_;
}
}
v___jp_8294_:
{
uint64_t v___x_8300_; uint64_t v___x_8301_; uint8_t v___x_8302_; 
v___x_8300_ = 0ULL;
v___x_8301_ = lean_unbox_uint64(v_snd_8299_);
v___x_8302_ = lean_uint64_dec_eq(v___x_8301_, v___x_8300_);
if (v___x_8302_ == 0)
{
uint64_t v___x_8303_; uint64_t v___x_8304_; uint64_t v___x_8305_; uint64_t v___x_8306_; uint64_t v___x_8307_; uint8_t v___x_8308_; 
v___x_8303_ = 149ULL;
v___x_8304_ = lean_uint64_add(v___y_8295_, v___x_8303_);
v___x_8305_ = 32ULL;
v___x_8306_ = lean_unbox_uint64(v_snd_8299_);
v___x_8307_ = lean_uint64_shift_right(v___x_8306_, v___x_8305_);
v___x_8308_ = lean_uint64_dec_eq(v___x_8307_, v___x_8300_);
if (v___x_8308_ == 0)
{
v___y_8282_ = v___x_8304_;
v___y_8283_ = v___y_8296_;
v___y_8284_ = v___x_8305_;
v___y_8285_ = v_snd_8299_;
v___y_8286_ = v___x_8303_;
v___y_8287_ = v_fst_8298_;
v___y_8288_ = v___x_8300_;
v___y_8289_ = v___y_8297_;
v___y_8290_ = v___x_8307_;
goto v___jp_8281_;
}
else
{
uint64_t v___x_8309_; 
v___x_8309_ = lean_unbox_uint64(v_snd_8299_);
v___y_8282_ = v___x_8304_;
v___y_8283_ = v___y_8296_;
v___y_8284_ = v___x_8305_;
v___y_8285_ = v_snd_8299_;
v___y_8286_ = v___x_8303_;
v___y_8287_ = v_fst_8298_;
v___y_8288_ = v___x_8300_;
v___y_8289_ = v___y_8297_;
v___y_8290_ = v___x_8309_;
goto v___jp_8281_;
}
}
else
{
uint8_t v___x_8310_; 
lean_dec(v_snd_8299_);
v___x_8310_ = lean_unbox(v_fst_8298_);
lean_dec(v_fst_8298_);
if (v___x_8310_ == 0)
{
uint32_t v___x_8311_; 
v___x_8311_ = 0;
return v___x_8311_;
}
else
{
uint32_t v___x_8312_; 
v___x_8312_ = 2147483648;
return v___x_8312_;
}
}
}
v___jp_8313_:
{
uint8_t v___x_8322_; 
v___x_8322_ = lean_uint64_dec_eq(v___y_8314_, v___y_8319_);
if (v___x_8322_ == 0)
{
uint8_t v___x_8323_; 
v___x_8323_ = lean_uint64_dec_lt(v___y_8314_, v___y_8319_);
if (v___x_8323_ == 0)
{
uint64_t v___x_8324_; lean_object* v___x_8325_; lean_object* v___x_8326_; 
v___x_8324_ = lean_uint64_sub(v___y_8314_, v___y_8319_);
v___x_8325_ = lean_box(v___y_8318_);
v___x_8326_ = lean_box_uint64(v___x_8324_);
v___y_8295_ = v___y_8316_;
v___y_8296_ = v___y_8317_;
v___y_8297_ = v___y_8320_;
v_fst_8298_ = v___x_8325_;
v_snd_8299_ = v___x_8326_;
goto v___jp_8294_;
}
else
{
uint64_t v___x_8327_; lean_object* v___x_8328_; lean_object* v___x_8329_; 
v___x_8327_ = lean_uint64_sub(v___y_8319_, v___y_8314_);
v___x_8328_ = lean_box(v___y_8315_);
v___x_8329_ = lean_box_uint64(v___x_8327_);
v___y_8295_ = v___y_8316_;
v___y_8296_ = v___y_8317_;
v___y_8297_ = v___y_8320_;
v_fst_8298_ = v___x_8328_;
v_snd_8299_ = v___x_8329_;
goto v___jp_8294_;
}
}
else
{
lean_object* v___x_8330_; lean_object* v___x_8331_; 
v___x_8330_ = lean_box(v___y_8321_);
v___x_8331_ = ((lean_object*)(lp_competition_Submission_TunedAdd_core___boxed__const__1));
v___y_8295_ = v___y_8316_;
v___y_8296_ = v___y_8317_;
v___y_8297_ = v___y_8320_;
v_fst_8298_ = v___x_8330_;
v_snd_8299_ = v___x_8331_;
goto v___jp_8294_;
}
}
v___jp_8332_:
{
if (v___y_8340_ == 0)
{
v___y_8314_ = v___y_8333_;
v___y_8315_ = v___y_8335_;
v___y_8316_ = v___y_8334_;
v___y_8317_ = v___y_8336_;
v___y_8318_ = v___y_8337_;
v___y_8319_ = v___y_8338_;
v___y_8320_ = v___y_8339_;
v___y_8321_ = v___y_8340_;
goto v___jp_8313_;
}
else
{
uint64_t v___x_8341_; lean_object* v___x_8342_; lean_object* v___x_8343_; 
v___x_8341_ = lean_uint64_add(v___y_8333_, v___y_8338_);
v___x_8342_ = lean_box(v___y_8337_);
v___x_8343_ = lean_box_uint64(v___x_8341_);
v___y_8295_ = v___y_8334_;
v___y_8296_ = v___y_8336_;
v___y_8297_ = v___y_8339_;
v_fst_8298_ = v___x_8342_;
v_snd_8299_ = v___x_8343_;
goto v___jp_8294_;
}
}
v___jp_8344_:
{
uint8_t v___x_8353_; 
v___x_8353_ = lean_uint64_dec_eq(v___y_8350_, v___y_8346_);
if (v___x_8353_ == 0)
{
uint8_t v___x_8354_; 
v___x_8354_ = lean_uint64_dec_lt(v___y_8350_, v___y_8346_);
if (v___x_8354_ == 0)
{
uint64_t v___x_8355_; lean_object* v___x_8356_; lean_object* v___x_8357_; 
v___x_8355_ = lean_uint64_sub(v___y_8350_, v___y_8346_);
v___x_8356_ = lean_box(v___y_8348_);
v___x_8357_ = lean_box_uint64(v___x_8355_);
v___y_7982_ = v___y_8347_;
v___y_7983_ = v___y_8349_;
v___y_7984_ = v___y_8351_;
v_fst_7985_ = v___x_8356_;
v_snd_7986_ = v___x_8357_;
goto v___jp_7981_;
}
else
{
uint64_t v___x_8358_; lean_object* v___x_8359_; lean_object* v___x_8360_; 
v___x_8358_ = lean_uint64_sub(v___y_8346_, v___y_8350_);
v___x_8359_ = lean_box(v___y_8345_);
v___x_8360_ = lean_box_uint64(v___x_8358_);
v___y_7982_ = v___y_8347_;
v___y_7983_ = v___y_8349_;
v___y_7984_ = v___y_8351_;
v_fst_7985_ = v___x_8359_;
v_snd_7986_ = v___x_8360_;
goto v___jp_7981_;
}
}
else
{
lean_object* v___x_8361_; lean_object* v___x_8362_; 
v___x_8361_ = lean_box(v___y_8352_);
v___x_8362_ = ((lean_object*)(lp_competition_Submission_TunedAdd_core___boxed__const__1));
v___y_7982_ = v___y_8347_;
v___y_7983_ = v___y_8349_;
v___y_7984_ = v___y_8351_;
v_fst_7985_ = v___x_8361_;
v_snd_7986_ = v___x_8362_;
goto v___jp_7981_;
}
}
v___jp_8363_:
{
if (v___y_8371_ == 0)
{
v___y_8345_ = v___y_8365_;
v___y_8346_ = v___y_8364_;
v___y_8347_ = v___y_8366_;
v___y_8348_ = v___y_8367_;
v___y_8349_ = v___y_8369_;
v___y_8350_ = v___y_8368_;
v___y_8351_ = v___y_8370_;
v___y_8352_ = v___y_8371_;
goto v___jp_8344_;
}
else
{
uint64_t v___x_8372_; lean_object* v___x_8373_; lean_object* v___x_8374_; 
v___x_8372_ = lean_uint64_add(v___y_8368_, v___y_8364_);
v___x_8373_ = lean_box(v___y_8367_);
v___x_8374_ = lean_box_uint64(v___x_8372_);
v___y_7982_ = v___y_8366_;
v___y_7983_ = v___y_8369_;
v___y_7984_ = v___y_8370_;
v_fst_7985_ = v___x_8373_;
v_snd_7986_ = v___x_8374_;
goto v___jp_7981_;
}
}
v___jp_8375_:
{
uint8_t v___x_8384_; 
v___x_8384_ = lean_uint64_dec_le(v___y_8381_, v___y_8383_);
if (v___x_8384_ == 0)
{
uint64_t v_shift_8385_; uint64_t v___x_8386_; uint8_t v___x_8387_; 
v_shift_8385_ = lean_uint64_sub(v___y_8381_, v___y_8383_);
v___x_8386_ = 39ULL;
v___x_8387_ = lean_uint64_dec_le(v_shift_8385_, v___x_8386_);
if (v___x_8387_ == 0)
{
return v_x_5072_;
}
else
{
uint64_t v___x_8388_; 
v___x_8388_ = lean_uint64_shift_left(v___y_8380_, v_shift_8385_);
if (v___y_8378_ == 0)
{
if (v___y_8376_ == 0)
{
v___y_8333_ = v___x_8388_;
v___y_8334_ = v___y_8383_;
v___y_8335_ = v___y_8376_;
v___y_8336_ = v___y_8377_;
v___y_8337_ = v___y_8378_;
v___y_8338_ = v___y_8379_;
v___y_8339_ = v___y_8382_;
v___y_8340_ = v___x_8387_;
goto v___jp_8332_;
}
else
{
v___y_8314_ = v___x_8388_;
v___y_8315_ = v___y_8376_;
v___y_8316_ = v___y_8383_;
v___y_8317_ = v___y_8377_;
v___y_8318_ = v___y_8378_;
v___y_8319_ = v___y_8379_;
v___y_8320_ = v___y_8382_;
v___y_8321_ = v___y_8378_;
goto v___jp_8313_;
}
}
else
{
v___y_8333_ = v___x_8388_;
v___y_8334_ = v___y_8383_;
v___y_8335_ = v___y_8376_;
v___y_8336_ = v___y_8377_;
v___y_8337_ = v___y_8378_;
v___y_8338_ = v___y_8379_;
v___y_8339_ = v___y_8382_;
v___y_8340_ = v___y_8376_;
goto v___jp_8332_;
}
}
}
else
{
uint64_t v_shift_8389_; uint64_t v___x_8390_; uint8_t v___x_8391_; 
v_shift_8389_ = lean_uint64_sub(v___y_8383_, v___y_8381_);
v___x_8390_ = 39ULL;
v___x_8391_ = lean_uint64_dec_le(v_shift_8389_, v___x_8390_);
if (v___x_8391_ == 0)
{
return v_y_5073_;
}
else
{
uint64_t v___x_8392_; 
v___x_8392_ = lean_uint64_shift_left(v___y_8379_, v_shift_8389_);
if (v___y_8378_ == 0)
{
if (v___y_8376_ == 0)
{
v___y_8364_ = v___x_8392_;
v___y_8365_ = v___y_8376_;
v___y_8366_ = v___y_8377_;
v___y_8367_ = v___y_8378_;
v___y_8368_ = v___y_8380_;
v___y_8369_ = v___y_8381_;
v___y_8370_ = v___y_8382_;
v___y_8371_ = v___x_8391_;
goto v___jp_8363_;
}
else
{
v___y_8345_ = v___y_8376_;
v___y_8346_ = v___x_8392_;
v___y_8347_ = v___y_8377_;
v___y_8348_ = v___y_8378_;
v___y_8349_ = v___y_8381_;
v___y_8350_ = v___y_8380_;
v___y_8351_ = v___y_8382_;
v___y_8352_ = v___y_8378_;
goto v___jp_8344_;
}
}
else
{
v___y_8364_ = v___x_8392_;
v___y_8365_ = v___y_8376_;
v___y_8366_ = v___y_8377_;
v___y_8367_ = v___y_8378_;
v___y_8368_ = v___y_8380_;
v___y_8369_ = v___y_8381_;
v___y_8370_ = v___y_8382_;
v___y_8371_ = v___y_8376_;
goto v___jp_8363_;
}
}
}
}
v___jp_8393_:
{
uint64_t v___x_8402_; uint64_t v___x_8403_; uint8_t v___x_8404_; 
v___x_8402_ = lean_uint32_to_uint64(v___y_8396_);
v___x_8403_ = 0ULL;
v___x_8404_ = lean_uint64_dec_eq(v___x_8402_, v___x_8403_);
if (v___x_8404_ == 0)
{
uint64_t v___x_8405_; uint64_t v___x_8406_; 
v___x_8405_ = 1ULL;
v___x_8406_ = lean_uint64_sub(v___x_8402_, v___x_8405_);
v___y_8376_ = v___y_8394_;
v___y_8377_ = v___y_8395_;
v___y_8378_ = v___y_8397_;
v___y_8379_ = v___y_8399_;
v___y_8380_ = v___y_8398_;
v___y_8381_ = v___y_8401_;
v___y_8382_ = v___y_8400_;
v___y_8383_ = v___x_8406_;
goto v___jp_8375_;
}
else
{
v___y_8376_ = v___y_8394_;
v___y_8377_ = v___y_8395_;
v___y_8378_ = v___y_8397_;
v___y_8379_ = v___y_8399_;
v___y_8380_ = v___y_8398_;
v___y_8381_ = v___y_8401_;
v___y_8382_ = v___y_8400_;
v___y_8383_ = v___x_8403_;
goto v___jp_8375_;
}
}
v___jp_8407_:
{
uint64_t v___x_8416_; uint64_t v___x_8417_; uint8_t v___x_8418_; 
v___x_8416_ = lean_uint32_to_uint64(v___y_8408_);
v___x_8417_ = 0ULL;
v___x_8418_ = lean_uint64_dec_eq(v___x_8416_, v___x_8417_);
if (v___x_8418_ == 0)
{
uint64_t v___x_8419_; uint64_t v___x_8420_; 
v___x_8419_ = 1ULL;
v___x_8420_ = lean_uint64_sub(v___x_8416_, v___x_8419_);
v___y_8394_ = v___y_8409_;
v___y_8395_ = v___y_8410_;
v___y_8396_ = v___y_8411_;
v___y_8397_ = v___y_8412_;
v___y_8398_ = v___y_8413_;
v___y_8399_ = v___y_8415_;
v___y_8400_ = v___y_8414_;
v___y_8401_ = v___x_8420_;
goto v___jp_8393_;
}
else
{
v___y_8394_ = v___y_8409_;
v___y_8395_ = v___y_8410_;
v___y_8396_ = v___y_8411_;
v___y_8397_ = v___y_8412_;
v___y_8398_ = v___y_8413_;
v___y_8399_ = v___y_8415_;
v___y_8400_ = v___y_8414_;
v___y_8401_ = v___x_8417_;
goto v___jp_8393_;
}
}
v___jp_8421_:
{
uint32_t v___x_8429_; uint32_t v___x_8430_; uint32_t v___x_8431_; uint8_t v___x_8432_; 
v___x_8429_ = 8388607;
v___x_8430_ = lean_uint32_land(v_y_5073_, v___x_8429_);
v___x_8431_ = 0;
v___x_8432_ = lean_uint32_dec_eq(v___y_8425_, v___x_8431_);
if (v___x_8432_ == 0)
{
uint64_t v___x_8433_; uint64_t v___x_8434_; uint64_t v___x_8435_; 
v___x_8433_ = lean_uint32_to_uint64(v___x_8430_);
v___x_8434_ = 8388608ULL;
v___x_8435_ = lean_uint64_lor(v___x_8433_, v___x_8434_);
v___y_8408_ = v___y_8422_;
v___y_8409_ = v___y_8423_;
v___y_8410_ = v___y_8424_;
v___y_8411_ = v___y_8425_;
v___y_8412_ = v___y_8426_;
v___y_8413_ = v___y_8428_;
v___y_8414_ = v___y_8427_;
v___y_8415_ = v___x_8435_;
goto v___jp_8407_;
}
else
{
uint64_t v___x_8436_; 
v___x_8436_ = lean_uint32_to_uint64(v___x_8430_);
v___y_8408_ = v___y_8422_;
v___y_8409_ = v___y_8423_;
v___y_8410_ = v___y_8424_;
v___y_8411_ = v___y_8425_;
v___y_8412_ = v___y_8426_;
v___y_8413_ = v___y_8428_;
v___y_8414_ = v___y_8427_;
v___y_8415_ = v___x_8436_;
goto v___jp_8407_;
}
}
v___jp_8437_:
{
uint32_t v___x_8444_; uint32_t v___x_8445_; uint32_t v___x_8446_; uint8_t v___x_8447_; 
v___x_8444_ = 8388607;
v___x_8445_ = lean_uint32_land(v_x_5072_, v___x_8444_);
v___x_8446_ = 0;
v___x_8447_ = lean_uint32_dec_eq(v___y_8438_, v___x_8446_);
if (v___x_8447_ == 0)
{
uint64_t v___x_8448_; uint64_t v___x_8449_; uint64_t v___x_8450_; 
v___x_8448_ = lean_uint32_to_uint64(v___x_8445_);
v___x_8449_ = 8388608ULL;
v___x_8450_ = lean_uint64_lor(v___x_8448_, v___x_8449_);
v___y_8422_ = v___y_8438_;
v___y_8423_ = v___y_8443_;
v___y_8424_ = v___y_8439_;
v___y_8425_ = v___y_8440_;
v___y_8426_ = v___y_8441_;
v___y_8427_ = v___y_8442_;
v___y_8428_ = v___x_8450_;
goto v___jp_8421_;
}
else
{
uint64_t v___x_8451_; 
v___x_8451_ = lean_uint32_to_uint64(v___x_8445_);
v___y_8422_ = v___y_8438_;
v___y_8423_ = v___y_8443_;
v___y_8424_ = v___y_8439_;
v___y_8425_ = v___y_8440_;
v___y_8426_ = v___y_8441_;
v___y_8427_ = v___y_8442_;
v___y_8428_ = v___x_8451_;
goto v___jp_8421_;
}
}
v___jp_8452_:
{
uint32_t v___x_8459_; uint32_t v___x_8460_; uint32_t v___x_8461_; uint8_t v___x_8462_; 
v___x_8459_ = 2147483648;
v___x_8460_ = lean_uint32_land(v_y_5073_, v___x_8459_);
v___x_8461_ = 0;
v___x_8462_ = lean_uint32_dec_eq(v___x_8460_, v___x_8461_);
if (v___x_8462_ == 0)
{
uint8_t v___x_8463_; 
v___x_8463_ = 1;
v___y_8438_ = v___y_8453_;
v___y_8439_ = v___y_8454_;
v___y_8440_ = v___y_8455_;
v___y_8441_ = v___y_8458_;
v___y_8442_ = v___y_8457_;
v___y_8443_ = v___x_8463_;
goto v___jp_8437_;
}
else
{
v___y_8438_ = v___y_8453_;
v___y_8439_ = v___y_8454_;
v___y_8440_ = v___y_8455_;
v___y_8441_ = v___y_8458_;
v___y_8442_ = v___y_8457_;
v___y_8443_ = v___y_8456_;
goto v___jp_8437_;
}
}
v___jp_8464_:
{
uint8_t v___x_8472_; 
v___x_8472_ = lean_uint64_dec_eq(v___y_8468_, v___y_8471_);
if (v___x_8472_ == 0)
{
uint32_t v___x_8473_; uint32_t v___x_8474_; uint32_t v___x_8475_; uint8_t v___x_8476_; 
v___x_8473_ = 2147483648;
v___x_8474_ = lean_uint32_land(v_x_5072_, v___x_8473_);
v___x_8475_ = 0;
v___x_8476_ = lean_uint32_dec_eq(v___x_8474_, v___x_8475_);
if (v___x_8476_ == 0)
{
uint8_t v___x_8477_; 
v___x_8477_ = 1;
v___y_8453_ = v___y_8465_;
v___y_8454_ = v___y_8466_;
v___y_8455_ = v___y_8467_;
v___y_8456_ = v___x_8472_;
v___y_8457_ = v___y_8470_;
v___y_8458_ = v___x_8477_;
goto v___jp_8452_;
}
else
{
v___y_8453_ = v___y_8465_;
v___y_8454_ = v___y_8466_;
v___y_8455_ = v___y_8467_;
v___y_8456_ = v___x_8472_;
v___y_8457_ = v___y_8470_;
v___y_8458_ = v___x_8472_;
goto v___jp_8452_;
}
}
else
{
uint32_t v___x_8478_; uint32_t v___x_8479_; uint32_t v___x_8480_; uint8_t v___x_8481_; 
v___x_8478_ = 2147483648;
v___x_8479_ = lean_uint32_land(v_x_5072_, v___x_8478_);
v___x_8480_ = 0;
v___x_8481_ = lean_uint32_dec_eq(v___x_8479_, v___x_8480_);
if (v___x_8481_ == 0)
{
v___y_7675_ = v___y_8465_;
v___y_7676_ = v___y_8466_;
v___y_7677_ = v___y_8467_;
v___y_7678_ = v___y_8468_;
v___y_7679_ = v___y_8469_;
v___y_7680_ = v___x_8472_;
v___y_7681_ = v___y_8470_;
v___y_7682_ = v___x_8472_;
goto v___jp_7674_;
}
else
{
v___y_7675_ = v___y_8465_;
v___y_7676_ = v___y_8466_;
v___y_7677_ = v___y_8467_;
v___y_7678_ = v___y_8468_;
v___y_7679_ = v___y_8469_;
v___y_7680_ = v___x_8472_;
v___y_7681_ = v___y_8470_;
v___y_7682_ = v___y_8469_;
goto v___jp_7674_;
}
}
}
v___jp_8482_:
{
uint32_t v___x_8488_; uint32_t v___x_8489_; uint64_t v___x_8490_; uint64_t v___x_8491_; uint8_t v___x_8492_; 
v___x_8488_ = lean_uint32_shift_right(v_y_5073_, v___y_8486_);
v___x_8489_ = lean_uint32_land(v___x_8488_, v___y_8484_);
v___x_8490_ = lean_uint32_to_uint64(v___x_8489_);
v___x_8491_ = 0ULL;
v___x_8492_ = lean_uint64_dec_eq(v___x_8490_, v___x_8491_);
if (v___x_8492_ == 0)
{
uint64_t v___x_8493_; uint64_t v___x_8494_; 
v___x_8493_ = 1ULL;
v___x_8494_ = lean_uint64_sub(v___x_8490_, v___x_8493_);
v___y_8465_ = v___y_8483_;
v___y_8466_ = v___y_8484_;
v___y_8467_ = v___x_8489_;
v___y_8468_ = v___y_8487_;
v___y_8469_ = v___y_8485_;
v___y_8470_ = v___y_8486_;
v___y_8471_ = v___x_8494_;
goto v___jp_8464_;
}
else
{
v___y_8465_ = v___y_8483_;
v___y_8466_ = v___y_8484_;
v___y_8467_ = v___x_8489_;
v___y_8468_ = v___y_8487_;
v___y_8469_ = v___y_8485_;
v___y_8470_ = v___y_8486_;
v___y_8471_ = v___x_8491_;
goto v___jp_8464_;
}
}
v___jp_8495_:
{
if (v___y_8496_ == 0)
{
uint32_t v___x_8497_; uint32_t v___x_8498_; uint32_t v___x_8499_; uint32_t v___x_8500_; uint64_t v___x_8501_; uint64_t v___x_8502_; uint8_t v___x_8503_; 
v___x_8497_ = 23;
v___x_8498_ = lean_uint32_shift_right(v_x_5072_, v___x_8497_);
v___x_8499_ = 255;
v___x_8500_ = lean_uint32_land(v___x_8498_, v___x_8499_);
v___x_8501_ = lean_uint32_to_uint64(v___x_8500_);
v___x_8502_ = 0ULL;
v___x_8503_ = lean_uint64_dec_eq(v___x_8501_, v___x_8502_);
if (v___x_8503_ == 0)
{
uint64_t v___x_8504_; uint64_t v___x_8505_; 
v___x_8504_ = 1ULL;
v___x_8505_ = lean_uint64_sub(v___x_8501_, v___x_8504_);
v___y_8483_ = v___x_8500_;
v___y_8484_ = v___x_8499_;
v___y_8485_ = v___y_8496_;
v___y_8486_ = v___x_8497_;
v___y_8487_ = v___x_8505_;
goto v___jp_8482_;
}
else
{
v___y_8483_ = v___x_8500_;
v___y_8484_ = v___x_8499_;
v___y_8485_ = v___y_8496_;
v___y_8486_ = v___x_8497_;
v___y_8487_ = v___x_8502_;
goto v___jp_8482_;
}
}
else
{
lean_object* v___x_8506_; lean_object* v___x_8507_; lean_object* v___x_8508_; uint32_t v___x_8509_; 
v___x_8506_ = lean_uint32_to_nat(v_x_5072_);
v___x_8507_ = lean_uint32_to_nat(v_y_5073_);
v___x_8508_ = lp_floatlib_FloatLib_Floats_Formats_BinaryInterchange_Model_AddBackend_word___at___00FloatLib_Floats_Formats_BinaryInterchange_Configured_Plan_softwareAdd32Certified_spec__1(v___x_8506_, v___x_8507_);
v___x_8509_ = lean_uint32_of_nat(v___x_8508_);
lean_dec(v___x_8508_);
return v___x_8509_;
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_RebuiltAdd_add___boxed(lean_object* v_x_8518_, lean_object* v_y_8519_){
_start:
{
uint32_t v_x_boxed_8520_; uint32_t v_y_boxed_8521_; uint32_t v_res_8522_; lean_object* v_r_8523_; 
v_x_boxed_8520_ = lean_unbox_uint32(v_x_8518_);
lean_dec(v_x_8518_);
v_y_boxed_8521_ = lean_unbox_uint32(v_y_8519_);
lean_dec(v_y_8519_);
v_res_8522_ = lp_competition_Submission_RebuiltAdd_add(v_x_boxed_8520_, v_y_boxed_8521_);
v_r_8523_ = lean_box_uint32(v_res_8522_);
return v_r_8523_;
}
}
LEAN_EXPORT uint64_t lp_competition_Submission_FastMul_sx(uint64_t v_k_8524_, uint64_t v_x_8525_){
_start:
{
uint64_t v___x_8526_; uint64_t v___x_8527_; uint8_t v___x_8528_; 
v___x_8526_ = lean_uint64_shift_right(v_x_8525_, v_k_8524_);
v___x_8527_ = 0ULL;
v___x_8528_ = lean_uint64_dec_eq(v___x_8526_, v___x_8527_);
if (v___x_8528_ == 0)
{
return v___x_8526_;
}
else
{
return v_x_8525_;
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_FastMul_sx___boxed(lean_object* v_k_8529_, lean_object* v_x_8530_){
_start:
{
uint64_t v_k_boxed_8531_; uint64_t v_x_boxed_8532_; uint64_t v_res_8533_; lean_object* v_r_8534_; 
v_k_boxed_8531_ = lean_unbox_uint64(v_k_8529_);
lean_dec_ref(v_k_8529_);
v_x_boxed_8532_ = lean_unbox_uint64(v_x_8530_);
lean_dec_ref(v_x_8530_);
v_res_8533_ = lp_competition_Submission_FastMul_sx(v_k_boxed_8531_, v_x_boxed_8532_);
v_r_8534_ = lean_box_uint64(v_res_8533_);
return v_r_8534_;
}
}
LEAN_EXPORT uint64_t lp_competition_Submission_FastMul_sr(uint64_t v_k_8535_, uint64_t v_x_8536_, uint64_t v_r_8537_){
_start:
{
uint64_t v___x_8538_; uint64_t v___x_8539_; uint8_t v___x_8540_; 
v___x_8538_ = lean_uint64_shift_right(v_x_8536_, v_k_8535_);
v___x_8539_ = 0ULL;
v___x_8540_ = lean_uint64_dec_eq(v___x_8538_, v___x_8539_);
if (v___x_8540_ == 0)
{
uint64_t v___x_8541_; 
v___x_8541_ = lean_uint64_add(v_r_8537_, v_k_8535_);
return v___x_8541_;
}
else
{
return v_r_8537_;
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_FastMul_sr___boxed(lean_object* v_k_8542_, lean_object* v_x_8543_, lean_object* v_r_8544_){
_start:
{
uint64_t v_k_boxed_8545_; uint64_t v_x_boxed_8546_; uint64_t v_r_boxed_8547_; uint64_t v_res_8548_; lean_object* v_r_8549_; 
v_k_boxed_8545_ = lean_unbox_uint64(v_k_8542_);
lean_dec_ref(v_k_8542_);
v_x_boxed_8546_ = lean_unbox_uint64(v_x_8543_);
lean_dec_ref(v_x_8543_);
v_r_boxed_8547_ = lean_unbox_uint64(v_r_8544_);
lean_dec_ref(v_r_8544_);
v_res_8548_ = lp_competition_Submission_FastMul_sr(v_k_boxed_8545_, v_x_boxed_8546_, v_r_boxed_8547_);
v_r_8549_ = lean_box_uint64(v_res_8548_);
return v_r_8549_;
}
}
LEAN_EXPORT uint64_t lp_competition_Submission_FastMul_fastLog2(uint64_t v_x0_8550_){
_start:
{
uint64_t v___y_8552_; uint64_t v___y_8553_; uint64_t v___y_8560_; uint64_t v___y_8561_; uint64_t v___y_8562_; uint64_t v___y_8563_; uint64_t v___y_8569_; uint64_t v___y_8570_; uint64_t v___y_8576_; uint64_t v___y_8577_; uint64_t v___y_8578_; uint64_t v___y_8579_; uint64_t v___y_8585_; uint64_t v___y_8586_; uint64_t v___y_8592_; uint64_t v___y_8593_; uint64_t v___y_8594_; uint64_t v___y_8595_; uint64_t v___y_8601_; uint64_t v___y_8602_; uint64_t v___y_8608_; uint64_t v___y_8609_; uint64_t v___y_8610_; uint64_t v___y_8611_; uint64_t v___y_8617_; uint64_t v___y_8618_; uint64_t v___x_8623_; uint64_t v___y_8625_; uint64_t v___x_8629_; uint64_t v___x_8630_; uint8_t v___x_8631_; 
v___x_8623_ = 32ULL;
v___x_8629_ = lean_uint64_shift_right(v_x0_8550_, v___x_8623_);
v___x_8630_ = 0ULL;
v___x_8631_ = lean_uint64_dec_eq(v___x_8629_, v___x_8630_);
if (v___x_8631_ == 0)
{
v___y_8625_ = v___x_8629_;
goto v___jp_8624_;
}
else
{
v___y_8625_ = v_x0_8550_;
goto v___jp_8624_;
}
v___jp_8551_:
{
uint64_t v___x_8554_; uint64_t v___x_8555_; uint64_t v___x_8556_; uint8_t v___x_8557_; 
v___x_8554_ = 1ULL;
v___x_8555_ = lean_uint64_shift_right(v___y_8552_, v___x_8554_);
v___x_8556_ = 0ULL;
v___x_8557_ = lean_uint64_dec_eq(v___x_8555_, v___x_8556_);
if (v___x_8557_ == 0)
{
uint64_t v___x_8558_; 
v___x_8558_ = lean_uint64_add(v___y_8553_, v___x_8554_);
return v___x_8558_;
}
else
{
return v___y_8553_;
}
}
v___jp_8559_:
{
uint64_t v___x_8564_; uint64_t v___x_8565_; uint8_t v___x_8566_; 
v___x_8564_ = lean_uint64_shift_right(v___y_8560_, v___y_8562_);
v___x_8565_ = 0ULL;
v___x_8566_ = lean_uint64_dec_eq(v___x_8564_, v___x_8565_);
if (v___x_8566_ == 0)
{
uint64_t v___x_8567_; 
v___x_8567_ = lean_uint64_add(v___y_8561_, v___y_8562_);
v___y_8552_ = v___y_8563_;
v___y_8553_ = v___x_8567_;
goto v___jp_8551_;
}
else
{
v___y_8552_ = v___y_8563_;
v___y_8553_ = v___y_8561_;
goto v___jp_8551_;
}
}
v___jp_8568_:
{
uint64_t v___x_8571_; uint64_t v___x_8572_; uint64_t v___x_8573_; uint8_t v___x_8574_; 
v___x_8571_ = 2ULL;
v___x_8572_ = lean_uint64_shift_right(v___y_8569_, v___x_8571_);
v___x_8573_ = 0ULL;
v___x_8574_ = lean_uint64_dec_eq(v___x_8572_, v___x_8573_);
if (v___x_8574_ == 0)
{
v___y_8560_ = v___y_8569_;
v___y_8561_ = v___y_8570_;
v___y_8562_ = v___x_8571_;
v___y_8563_ = v___x_8572_;
goto v___jp_8559_;
}
else
{
v___y_8560_ = v___y_8569_;
v___y_8561_ = v___y_8570_;
v___y_8562_ = v___x_8571_;
v___y_8563_ = v___y_8569_;
goto v___jp_8559_;
}
}
v___jp_8575_:
{
uint64_t v___x_8580_; uint64_t v___x_8581_; uint8_t v___x_8582_; 
v___x_8580_ = lean_uint64_shift_right(v___y_8578_, v___y_8577_);
v___x_8581_ = 0ULL;
v___x_8582_ = lean_uint64_dec_eq(v___x_8580_, v___x_8581_);
if (v___x_8582_ == 0)
{
uint64_t v___x_8583_; 
v___x_8583_ = lean_uint64_add(v___y_8576_, v___y_8577_);
v___y_8569_ = v___y_8579_;
v___y_8570_ = v___x_8583_;
goto v___jp_8568_;
}
else
{
v___y_8569_ = v___y_8579_;
v___y_8570_ = v___y_8576_;
goto v___jp_8568_;
}
}
v___jp_8584_:
{
uint64_t v___x_8587_; uint64_t v___x_8588_; uint64_t v___x_8589_; uint8_t v___x_8590_; 
v___x_8587_ = 4ULL;
v___x_8588_ = lean_uint64_shift_right(v___y_8585_, v___x_8587_);
v___x_8589_ = 0ULL;
v___x_8590_ = lean_uint64_dec_eq(v___x_8588_, v___x_8589_);
if (v___x_8590_ == 0)
{
v___y_8576_ = v___y_8586_;
v___y_8577_ = v___x_8587_;
v___y_8578_ = v___y_8585_;
v___y_8579_ = v___x_8588_;
goto v___jp_8575_;
}
else
{
v___y_8576_ = v___y_8586_;
v___y_8577_ = v___x_8587_;
v___y_8578_ = v___y_8585_;
v___y_8579_ = v___y_8585_;
goto v___jp_8575_;
}
}
v___jp_8591_:
{
uint64_t v___x_8596_; uint64_t v___x_8597_; uint8_t v___x_8598_; 
v___x_8596_ = lean_uint64_shift_right(v___y_8594_, v___y_8593_);
v___x_8597_ = 0ULL;
v___x_8598_ = lean_uint64_dec_eq(v___x_8596_, v___x_8597_);
if (v___x_8598_ == 0)
{
uint64_t v___x_8599_; 
v___x_8599_ = lean_uint64_add(v___y_8592_, v___y_8593_);
v___y_8585_ = v___y_8595_;
v___y_8586_ = v___x_8599_;
goto v___jp_8584_;
}
else
{
v___y_8585_ = v___y_8595_;
v___y_8586_ = v___y_8592_;
goto v___jp_8584_;
}
}
v___jp_8600_:
{
uint64_t v___x_8603_; uint64_t v___x_8604_; uint64_t v___x_8605_; uint8_t v___x_8606_; 
v___x_8603_ = 8ULL;
v___x_8604_ = lean_uint64_shift_right(v___y_8601_, v___x_8603_);
v___x_8605_ = 0ULL;
v___x_8606_ = lean_uint64_dec_eq(v___x_8604_, v___x_8605_);
if (v___x_8606_ == 0)
{
v___y_8592_ = v___y_8602_;
v___y_8593_ = v___x_8603_;
v___y_8594_ = v___y_8601_;
v___y_8595_ = v___x_8604_;
goto v___jp_8591_;
}
else
{
v___y_8592_ = v___y_8602_;
v___y_8593_ = v___x_8603_;
v___y_8594_ = v___y_8601_;
v___y_8595_ = v___y_8601_;
goto v___jp_8591_;
}
}
v___jp_8607_:
{
uint64_t v___x_8612_; uint64_t v___x_8613_; uint8_t v___x_8614_; 
v___x_8612_ = lean_uint64_shift_right(v___y_8609_, v___y_8610_);
v___x_8613_ = 0ULL;
v___x_8614_ = lean_uint64_dec_eq(v___x_8612_, v___x_8613_);
if (v___x_8614_ == 0)
{
uint64_t v___x_8615_; 
v___x_8615_ = lean_uint64_add(v___y_8608_, v___y_8610_);
v___y_8601_ = v___y_8611_;
v___y_8602_ = v___x_8615_;
goto v___jp_8600_;
}
else
{
v___y_8601_ = v___y_8611_;
v___y_8602_ = v___y_8608_;
goto v___jp_8600_;
}
}
v___jp_8616_:
{
uint64_t v___x_8619_; uint64_t v___x_8620_; uint64_t v___x_8621_; uint8_t v___x_8622_; 
v___x_8619_ = 16ULL;
v___x_8620_ = lean_uint64_shift_right(v___y_8617_, v___x_8619_);
v___x_8621_ = 0ULL;
v___x_8622_ = lean_uint64_dec_eq(v___x_8620_, v___x_8621_);
if (v___x_8622_ == 0)
{
v___y_8608_ = v___y_8618_;
v___y_8609_ = v___y_8617_;
v___y_8610_ = v___x_8619_;
v___y_8611_ = v___x_8620_;
goto v___jp_8607_;
}
else
{
v___y_8608_ = v___y_8618_;
v___y_8609_ = v___y_8617_;
v___y_8610_ = v___x_8619_;
v___y_8611_ = v___y_8617_;
goto v___jp_8607_;
}
}
v___jp_8624_:
{
uint64_t v___x_8626_; uint64_t v___x_8627_; uint8_t v___x_8628_; 
v___x_8626_ = lean_uint64_shift_right(v_x0_8550_, v___x_8623_);
v___x_8627_ = 0ULL;
v___x_8628_ = lean_uint64_dec_eq(v___x_8626_, v___x_8627_);
if (v___x_8628_ == 0)
{
v___y_8617_ = v___y_8625_;
v___y_8618_ = v___x_8623_;
goto v___jp_8616_;
}
else
{
v___y_8617_ = v___y_8625_;
v___y_8618_ = v___x_8627_;
goto v___jp_8616_;
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_FastMul_fastLog2___boxed(lean_object* v_x0_8632_){
_start:
{
uint64_t v_x0_boxed_8633_; uint64_t v_res_8634_; lean_object* v_r_8635_; 
v_x0_boxed_8633_ = lean_unbox_uint64(v_x0_8632_);
lean_dec_ref(v_x0_8632_);
v_res_8634_ = lp_competition_Submission_FastMul_fastLog2(v_x0_boxed_8633_);
v_r_8635_ = lean_box_uint64(v_res_8634_);
return v_r_8635_;
}
}
LEAN_EXPORT uint64_t lp_competition_Submission_FastMul_rse(uint64_t v_value_8636_, uint64_t v_shift_8637_){
_start:
{
uint64_t v_quotient_8638_; uint64_t v___x_8639_; uint64_t v___x_8640_; uint64_t v___x_8641_; uint64_t v_remainder_8642_; uint64_t v___x_8643_; uint64_t v_half_8644_; uint8_t v___x_8645_; 
v_quotient_8638_ = lean_uint64_shift_right(v_value_8636_, v_shift_8637_);
v___x_8639_ = 1ULL;
v___x_8640_ = lean_uint64_shift_left(v___x_8639_, v_shift_8637_);
v___x_8641_ = lean_uint64_sub(v___x_8640_, v___x_8639_);
v_remainder_8642_ = lean_uint64_land(v_value_8636_, v___x_8641_);
v___x_8643_ = lean_uint64_sub(v_shift_8637_, v___x_8639_);
v_half_8644_ = lean_uint64_shift_left(v___x_8639_, v___x_8643_);
v___x_8645_ = lean_uint64_dec_lt(v_remainder_8642_, v_half_8644_);
if (v___x_8645_ == 0)
{
uint8_t v___x_8646_; 
v___x_8646_ = lean_uint64_dec_lt(v_half_8644_, v_remainder_8642_);
if (v___x_8646_ == 0)
{
uint64_t v___x_8647_; uint64_t v___x_8648_; uint8_t v___x_8649_; 
v___x_8647_ = lean_uint64_land(v_quotient_8638_, v___x_8639_);
v___x_8648_ = 0ULL;
v___x_8649_ = lean_uint64_dec_eq(v___x_8647_, v___x_8648_);
if (v___x_8649_ == 0)
{
uint64_t v___x_8650_; 
v___x_8650_ = lean_uint64_add(v_quotient_8638_, v___x_8639_);
return v___x_8650_;
}
else
{
return v_quotient_8638_;
}
}
else
{
uint64_t v___x_8651_; 
v___x_8651_ = lean_uint64_add(v_quotient_8638_, v___x_8639_);
return v___x_8651_;
}
}
else
{
return v_quotient_8638_;
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_FastMul_rse___boxed(lean_object* v_value_8652_, lean_object* v_shift_8653_){
_start:
{
uint64_t v_value_boxed_8654_; uint64_t v_shift_boxed_8655_; uint64_t v_res_8656_; lean_object* v_r_8657_; 
v_value_boxed_8654_ = lean_unbox_uint64(v_value_8652_);
lean_dec_ref(v_value_8652_);
v_shift_boxed_8655_ = lean_unbox_uint64(v_shift_8653_);
lean_dec_ref(v_shift_8653_);
v_res_8656_ = lp_competition_Submission_FastMul_rse(v_value_boxed_8654_, v_shift_boxed_8655_);
v_r_8657_ = lean_box_uint64(v_res_8656_);
return v_r_8657_;
}
}
LEAN_EXPORT uint64_t lp_competition_Submission_FastMul_rseAny(uint64_t v_value_8658_, uint64_t v_shift_8659_){
_start:
{
uint64_t v___x_8660_; uint8_t v___x_8661_; 
v___x_8660_ = 0ULL;
v___x_8661_ = lean_uint64_dec_eq(v_shift_8659_, v___x_8660_);
if (v___x_8661_ == 0)
{
uint64_t v___x_8662_; uint8_t v___x_8663_; 
v___x_8662_ = 64ULL;
v___x_8663_ = lean_uint64_dec_lt(v_shift_8659_, v___x_8662_);
if (v___x_8663_ == 0)
{
uint8_t v___x_8664_; 
v___x_8664_ = lean_uint64_dec_eq(v_shift_8659_, v___x_8662_);
if (v___x_8664_ == 0)
{
return v___x_8660_;
}
else
{
uint64_t v___x_8665_; uint8_t v___x_8666_; 
v___x_8665_ = 9223372036854775808ULL;
v___x_8666_ = lean_uint64_dec_lt(v___x_8665_, v_value_8658_);
if (v___x_8666_ == 0)
{
return v___x_8660_;
}
else
{
uint64_t v___x_8667_; 
v___x_8667_ = 1ULL;
return v___x_8667_;
}
}
}
else
{
uint64_t v_quotient_8668_; uint64_t v___x_8669_; uint64_t v___x_8670_; uint64_t v___x_8671_; uint64_t v_remainder_8672_; uint64_t v___x_8673_; uint64_t v_half_8674_; uint8_t v___x_8675_; 
v_quotient_8668_ = lean_uint64_shift_right(v_value_8658_, v_shift_8659_);
v___x_8669_ = 1ULL;
v___x_8670_ = lean_uint64_shift_left(v___x_8669_, v_shift_8659_);
v___x_8671_ = lean_uint64_sub(v___x_8670_, v___x_8669_);
v_remainder_8672_ = lean_uint64_land(v_value_8658_, v___x_8671_);
v___x_8673_ = lean_uint64_sub(v_shift_8659_, v___x_8669_);
v_half_8674_ = lean_uint64_shift_left(v___x_8669_, v___x_8673_);
v___x_8675_ = lean_uint64_dec_lt(v_remainder_8672_, v_half_8674_);
if (v___x_8675_ == 0)
{
uint8_t v___x_8676_; 
v___x_8676_ = lean_uint64_dec_lt(v_half_8674_, v_remainder_8672_);
if (v___x_8676_ == 0)
{
uint64_t v___x_8677_; uint8_t v___x_8678_; 
v___x_8677_ = lean_uint64_land(v_quotient_8668_, v___x_8669_);
v___x_8678_ = lean_uint64_dec_eq(v___x_8677_, v___x_8660_);
if (v___x_8678_ == 0)
{
uint64_t v___x_8679_; 
v___x_8679_ = lean_uint64_add(v_quotient_8668_, v___x_8669_);
return v___x_8679_;
}
else
{
return v_quotient_8668_;
}
}
else
{
uint64_t v___x_8680_; 
v___x_8680_ = lean_uint64_add(v_quotient_8668_, v___x_8669_);
return v___x_8680_;
}
}
else
{
return v_quotient_8668_;
}
}
}
else
{
return v_value_8658_;
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_FastMul_rseAny___boxed(lean_object* v_value_8681_, lean_object* v_shift_8682_){
_start:
{
uint64_t v_value_boxed_8683_; uint64_t v_shift_boxed_8684_; uint64_t v_res_8685_; lean_object* v_r_8686_; 
v_value_boxed_8683_ = lean_unbox_uint64(v_value_8681_);
lean_dec_ref(v_value_8681_);
v_shift_boxed_8684_ = lean_unbox_uint64(v_shift_8682_);
lean_dec_ref(v_shift_8682_);
v_res_8685_ = lp_competition_Submission_FastMul_rseAny(v_value_boxed_8683_, v_shift_boxed_8684_);
v_r_8686_ = lean_box_uint64(v_res_8685_);
return v_r_8686_;
}
}
LEAN_EXPORT uint32_t lp_competition_Submission_FastMul_mkW(uint8_t v_sign_8687_, uint32_t v_e_8688_, uint32_t v_f_8689_){
_start:
{
uint32_t v___y_8691_; 
if (v_sign_8687_ == 0)
{
uint32_t v___x_8700_; 
v___x_8700_ = 0;
v___y_8691_ = v___x_8700_;
goto v___jp_8690_;
}
else
{
uint32_t v___x_8701_; 
v___x_8701_ = 2147483648;
v___y_8691_ = v___x_8701_;
goto v___jp_8690_;
}
v___jp_8690_:
{
uint32_t v___x_8692_; uint32_t v___x_8693_; uint32_t v___x_8694_; uint32_t v___x_8695_; uint32_t v___x_8696_; uint32_t v___x_8697_; uint32_t v___x_8698_; uint32_t v___x_8699_; 
v___x_8692_ = 255;
v___x_8693_ = lean_uint32_land(v_e_8688_, v___x_8692_);
v___x_8694_ = 23;
v___x_8695_ = lean_uint32_shift_left(v___x_8693_, v___x_8694_);
v___x_8696_ = lean_uint32_lor(v___y_8691_, v___x_8695_);
v___x_8697_ = 8388607;
v___x_8698_ = lean_uint32_land(v_f_8689_, v___x_8697_);
v___x_8699_ = lean_uint32_lor(v___x_8696_, v___x_8698_);
return v___x_8699_;
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_FastMul_mkW___boxed(lean_object* v_sign_8702_, lean_object* v_e_8703_, lean_object* v_f_8704_){
_start:
{
uint8_t v_sign_boxed_8705_; uint32_t v_e_boxed_8706_; uint32_t v_f_boxed_8707_; uint32_t v_res_8708_; lean_object* v_r_8709_; 
v_sign_boxed_8705_ = lean_unbox(v_sign_8702_);
v_e_boxed_8706_ = lean_unbox_uint32(v_e_8703_);
lean_dec(v_e_8703_);
v_f_boxed_8707_ = lean_unbox_uint32(v_f_8704_);
lean_dec(v_f_8704_);
v_res_8708_ = lp_competition_Submission_FastMul_mkW(v_sign_boxed_8705_, v_e_boxed_8706_, v_f_boxed_8707_);
v_r_8709_ = lean_box_uint32(v_res_8708_);
return v_r_8709_;
}
}
LEAN_EXPORT uint32_t lp_competition_Submission_FastMul_fracW(uint64_t v_n_8710_){
_start:
{
uint64_t v___x_8711_; uint8_t v___x_8712_; 
v___x_8711_ = 8388608ULL;
v___x_8712_ = lean_uint64_dec_lt(v_n_8710_, v___x_8711_);
if (v___x_8712_ == 0)
{
uint64_t v___x_8713_; uint32_t v___x_8714_; 
v___x_8713_ = lean_uint64_sub(v_n_8710_, v___x_8711_);
v___x_8714_ = lean_uint64_to_uint32(v___x_8713_);
return v___x_8714_;
}
else
{
uint32_t v___x_8715_; 
v___x_8715_ = lean_uint32_once(&lp_competition_Submission_TunedAdd_fracW___closed__0, &lp_competition_Submission_TunedAdd_fracW___closed__0_once, _init_lp_competition_Submission_TunedAdd_fracW___closed__0);
return v___x_8715_;
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_FastMul_fracW___boxed(lean_object* v_n_8716_){
_start:
{
uint64_t v_n_boxed_8717_; uint32_t v_res_8718_; lean_object* v_r_8719_; 
v_n_boxed_8717_ = lean_unbox_uint64(v_n_8716_);
lean_dec_ref(v_n_8716_);
v_res_8718_ = lp_competition_Submission_FastMul_fracW(v_n_boxed_8717_);
v_r_8719_ = lean_box_uint32(v_res_8718_);
return v_r_8719_;
}
}
LEAN_EXPORT uint32_t lp_competition_Submission_FastMul_roundP(uint8_t v_sign_8720_, uint64_t v_product_8721_, uint64_t v_scale_8722_){
_start:
{
uint32_t v___y_8724_; uint32_t v___y_8728_; uint32_t v___y_8729_; uint32_t v___y_8734_; uint32_t v___y_8735_; uint32_t v___y_8736_; uint32_t v___y_8746_; uint32_t v___y_8747_; uint64_t v___x_8750_; uint64_t v___y_8752_; uint64_t v___y_8764_; uint64_t v___y_8765_; uint64_t v___y_8775_; uint8_t v___y_8776_; uint64_t v___y_8777_; uint64_t v___y_8784_; uint64_t v___y_8785_; uint64_t v___y_8791_; uint64_t v___y_8846_; uint64_t v___y_8847_; uint64_t v___y_8853_; uint64_t v___y_8854_; uint64_t v___y_8855_; uint64_t v___y_8856_; uint64_t v___y_8861_; uint64_t v___y_8862_; uint64_t v___y_8867_; uint64_t v___y_8868_; uint64_t v___y_8869_; uint64_t v___y_8870_; uint64_t v___y_8875_; uint64_t v___y_8876_; uint64_t v___y_8881_; uint64_t v___y_8882_; uint64_t v___y_8883_; uint64_t v___y_8884_; uint64_t v___y_8889_; uint64_t v___y_8890_; uint64_t v___y_8895_; uint64_t v___y_8896_; uint64_t v___y_8897_; uint64_t v___y_8898_; uint64_t v___y_8903_; uint64_t v___y_8904_; uint8_t v___x_8908_; 
v___x_8750_ = 0ULL;
v___x_8908_ = lean_uint64_dec_eq(v_product_8721_, v___x_8750_);
if (v___x_8908_ == 0)
{
uint64_t v___x_8909_; uint64_t v___y_8911_; uint64_t v___x_8914_; uint8_t v___x_8915_; 
v___x_8909_ = 32ULL;
v___x_8914_ = lean_uint64_shift_right(v_product_8721_, v___x_8909_);
v___x_8915_ = lean_uint64_dec_eq(v___x_8914_, v___x_8750_);
if (v___x_8915_ == 0)
{
v___y_8911_ = v___x_8914_;
goto v___jp_8910_;
}
else
{
v___y_8911_ = v_product_8721_;
goto v___jp_8910_;
}
v___jp_8910_:
{
uint64_t v___x_8912_; uint8_t v___x_8913_; 
v___x_8912_ = lean_uint64_shift_right(v_product_8721_, v___x_8909_);
v___x_8913_ = lean_uint64_dec_eq(v___x_8912_, v___x_8750_);
if (v___x_8913_ == 0)
{
v___y_8903_ = v___y_8911_;
v___y_8904_ = v___x_8909_;
goto v___jp_8902_;
}
else
{
v___y_8903_ = v___y_8911_;
v___y_8904_ = v___x_8750_;
goto v___jp_8902_;
}
}
}
else
{
if (v_sign_8720_ == 0)
{
uint32_t v___x_8916_; 
v___x_8916_ = 0;
return v___x_8916_;
}
else
{
uint32_t v___x_8917_; 
v___x_8917_ = 2147483648;
return v___x_8917_;
}
}
v___jp_8723_:
{
uint32_t v___x_8725_; uint32_t v___x_8726_; 
v___x_8725_ = 8388608;
v___x_8726_ = lean_uint32_lor(v___y_8724_, v___x_8725_);
return v___x_8726_;
}
v___jp_8727_:
{
uint32_t v___x_8730_; uint32_t v___x_8731_; uint32_t v___x_8732_; 
v___x_8730_ = 8388607;
v___x_8731_ = lean_uint32_land(v___y_8728_, v___x_8730_);
v___x_8732_ = lean_uint32_lor(v___y_8729_, v___x_8731_);
return v___x_8732_;
}
v___jp_8733_:
{
uint32_t v___x_8737_; uint32_t v___x_8738_; uint32_t v___x_8739_; uint32_t v___x_8740_; uint32_t v___x_8741_; uint32_t v___x_8742_; uint32_t v___x_8743_; uint32_t v___x_8744_; 
v___x_8737_ = 255;
v___x_8738_ = lean_uint32_land(v___y_8735_, v___x_8737_);
v___x_8739_ = 23;
v___x_8740_ = lean_uint32_shift_left(v___x_8738_, v___x_8739_);
v___x_8741_ = lean_uint32_lor(v___y_8736_, v___x_8740_);
v___x_8742_ = 8388607;
v___x_8743_ = lean_uint32_land(v___y_8734_, v___x_8742_);
v___x_8744_ = lean_uint32_lor(v___x_8741_, v___x_8743_);
return v___x_8744_;
}
v___jp_8745_:
{
if (v_sign_8720_ == 0)
{
uint32_t v___x_8748_; 
v___x_8748_ = 0;
v___y_8734_ = v___y_8747_;
v___y_8735_ = v___y_8746_;
v___y_8736_ = v___x_8748_;
goto v___jp_8733_;
}
else
{
uint32_t v___x_8749_; 
v___x_8749_ = 2147483648;
v___y_8734_ = v___y_8747_;
v___y_8735_ = v___y_8746_;
v___y_8736_ = v___x_8749_;
goto v___jp_8733_;
}
}
v___jp_8751_:
{
uint8_t v___x_8753_; 
v___x_8753_ = lean_uint64_dec_eq(v___y_8752_, v___x_8750_);
if (v___x_8753_ == 0)
{
uint64_t v___x_8754_; uint8_t v___x_8755_; 
v___x_8754_ = 8388608ULL;
v___x_8755_ = lean_uint64_dec_eq(v___y_8752_, v___x_8754_);
if (v___x_8755_ == 0)
{
uint32_t v___x_8756_; 
v___x_8756_ = lean_uint64_to_uint32(v___y_8752_);
if (v_sign_8720_ == 0)
{
uint32_t v___x_8757_; 
v___x_8757_ = 0;
v___y_8728_ = v___x_8756_;
v___y_8729_ = v___x_8757_;
goto v___jp_8727_;
}
else
{
uint32_t v___x_8758_; 
v___x_8758_ = 2147483648;
v___y_8728_ = v___x_8756_;
v___y_8729_ = v___x_8758_;
goto v___jp_8727_;
}
}
else
{
if (v_sign_8720_ == 0)
{
uint32_t v___x_8759_; 
v___x_8759_ = 0;
v___y_8724_ = v___x_8759_;
goto v___jp_8723_;
}
else
{
uint32_t v___x_8760_; 
v___x_8760_ = 2147483648;
v___y_8724_ = v___x_8760_;
goto v___jp_8723_;
}
}
}
else
{
if (v_sign_8720_ == 0)
{
uint32_t v___x_8761_; 
v___x_8761_ = 0;
return v___x_8761_;
}
else
{
uint32_t v___x_8762_; 
v___x_8762_ = 2147483648;
return v___x_8762_;
}
}
}
v___jp_8763_:
{
uint64_t v___x_8766_; uint64_t v_encodedExponent_8767_; uint32_t v___x_8768_; uint64_t v___x_8769_; uint8_t v___x_8770_; 
v___x_8766_ = 171ULL;
v_encodedExponent_8767_ = lean_uint64_sub(v___y_8764_, v___x_8766_);
v___x_8768_ = lean_uint64_to_uint32(v_encodedExponent_8767_);
v___x_8769_ = 8388608ULL;
v___x_8770_ = lean_uint64_dec_lt(v___y_8765_, v___x_8769_);
if (v___x_8770_ == 0)
{
uint64_t v___x_8771_; uint32_t v___x_8772_; 
v___x_8771_ = lean_uint64_sub(v___y_8765_, v___x_8769_);
v___x_8772_ = lean_uint64_to_uint32(v___x_8771_);
v___y_8746_ = v___x_8768_;
v___y_8747_ = v___x_8772_;
goto v___jp_8745_;
}
else
{
uint32_t v___x_8773_; 
v___x_8773_ = lean_uint32_once(&lp_competition_Submission_TunedAdd_fracW___closed__0, &lp_competition_Submission_TunedAdd_fracW___closed__0_once, _init_lp_competition_Submission_TunedAdd_fracW___closed__0);
v___y_8746_ = v___x_8768_;
v___y_8747_ = v___x_8773_;
goto v___jp_8745_;
}
}
v___jp_8774_:
{
uint64_t v___x_8778_; uint8_t v___x_8779_; 
v___x_8778_ = 425ULL;
v___x_8779_ = lean_uint64_dec_lt(v___x_8778_, v___y_8777_);
if (v___x_8779_ == 0)
{
if (v___y_8776_ == 0)
{
v___y_8764_ = v___y_8777_;
v___y_8765_ = v___y_8775_;
goto v___jp_8763_;
}
else
{
uint64_t v___x_8780_; 
v___x_8780_ = 8388608ULL;
v___y_8764_ = v___y_8777_;
v___y_8765_ = v___x_8780_;
goto v___jp_8763_;
}
}
else
{
if (v_sign_8720_ == 0)
{
uint32_t v___x_8781_; 
v___x_8781_ = 2139095040;
return v___x_8781_;
}
else
{
uint32_t v___x_8782_; 
v___x_8782_ = 4286578688;
return v___x_8782_;
}
}
}
v___jp_8783_:
{
uint64_t v___x_8786_; uint8_t v_carry_8787_; 
v___x_8786_ = 16777216ULL;
v_carry_8787_ = lean_uint64_dec_eq(v___y_8785_, v___x_8786_);
if (v_carry_8787_ == 0)
{
v___y_8775_ = v___y_8785_;
v___y_8776_ = v_carry_8787_;
v___y_8777_ = v___y_8784_;
goto v___jp_8774_;
}
else
{
uint64_t v___x_8788_; uint64_t v___x_8789_; 
v___x_8788_ = 1ULL;
v___x_8789_ = lean_uint64_add(v___y_8784_, v___x_8788_);
v___y_8775_ = v___y_8785_;
v___y_8776_ = v_carry_8787_;
v___y_8777_ = v___x_8789_;
goto v___jp_8774_;
}
}
v___jp_8790_:
{
uint64_t v_position_8792_; uint64_t v___x_8793_; uint8_t v___x_8794_; 
v_position_8792_ = lean_uint64_add(v___y_8791_, v_scale_8722_);
v___x_8793_ = 172ULL;
v___x_8794_ = lean_uint64_dec_lt(v_position_8792_, v___x_8793_);
if (v___x_8794_ == 0)
{
uint64_t v___x_8795_; uint8_t v___x_8796_; 
v___x_8795_ = 23ULL;
v___x_8796_ = lean_uint64_dec_lt(v___y_8791_, v___x_8795_);
if (v___x_8796_ == 0)
{
uint64_t v___x_8797_; uint8_t v___x_8798_; 
v___x_8797_ = lean_uint64_sub(v___y_8791_, v___x_8795_);
v___x_8798_ = lean_uint64_dec_eq(v___x_8797_, v___x_8750_);
if (v___x_8798_ == 0)
{
uint64_t v___x_8799_; uint8_t v___x_8800_; 
v___x_8799_ = 64ULL;
v___x_8800_ = lean_uint64_dec_lt(v___x_8797_, v___x_8799_);
if (v___x_8800_ == 0)
{
uint8_t v___x_8801_; 
v___x_8801_ = lean_uint64_dec_eq(v___x_8797_, v___x_8799_);
if (v___x_8801_ == 0)
{
v___y_8784_ = v_position_8792_;
v___y_8785_ = v___x_8750_;
goto v___jp_8783_;
}
else
{
uint64_t v___x_8802_; uint8_t v___x_8803_; 
v___x_8802_ = 9223372036854775808ULL;
v___x_8803_ = lean_uint64_dec_lt(v___x_8802_, v_product_8721_);
if (v___x_8803_ == 0)
{
v___y_8784_ = v_position_8792_;
v___y_8785_ = v___x_8750_;
goto v___jp_8783_;
}
else
{
uint64_t v___x_8804_; 
v___x_8804_ = 1ULL;
v___y_8784_ = v_position_8792_;
v___y_8785_ = v___x_8804_;
goto v___jp_8783_;
}
}
}
else
{
uint64_t v_quotient_8805_; uint64_t v___x_8806_; uint64_t v___x_8807_; uint64_t v___x_8808_; uint64_t v_remainder_8809_; uint64_t v___x_8810_; uint64_t v_half_8811_; uint8_t v___x_8812_; 
v_quotient_8805_ = lean_uint64_shift_right(v_product_8721_, v___x_8797_);
v___x_8806_ = 1ULL;
v___x_8807_ = lean_uint64_shift_left(v___x_8806_, v___x_8797_);
v___x_8808_ = lean_uint64_sub(v___x_8807_, v___x_8806_);
v_remainder_8809_ = lean_uint64_land(v_product_8721_, v___x_8808_);
v___x_8810_ = lean_uint64_sub(v___x_8797_, v___x_8806_);
v_half_8811_ = lean_uint64_shift_left(v___x_8806_, v___x_8810_);
v___x_8812_ = lean_uint64_dec_lt(v_remainder_8809_, v_half_8811_);
if (v___x_8812_ == 0)
{
uint8_t v___x_8813_; 
v___x_8813_ = lean_uint64_dec_lt(v_half_8811_, v_remainder_8809_);
if (v___x_8813_ == 0)
{
uint64_t v___x_8814_; uint8_t v___x_8815_; 
v___x_8814_ = lean_uint64_land(v_quotient_8805_, v___x_8806_);
v___x_8815_ = lean_uint64_dec_eq(v___x_8814_, v___x_8750_);
if (v___x_8815_ == 0)
{
uint64_t v___x_8816_; 
v___x_8816_ = lean_uint64_add(v_quotient_8805_, v___x_8806_);
v___y_8784_ = v_position_8792_;
v___y_8785_ = v___x_8816_;
goto v___jp_8783_;
}
else
{
v___y_8784_ = v_position_8792_;
v___y_8785_ = v_quotient_8805_;
goto v___jp_8783_;
}
}
else
{
uint64_t v___x_8817_; 
v___x_8817_ = lean_uint64_add(v_quotient_8805_, v___x_8806_);
v___y_8784_ = v_position_8792_;
v___y_8785_ = v___x_8817_;
goto v___jp_8783_;
}
}
else
{
v___y_8784_ = v_position_8792_;
v___y_8785_ = v_quotient_8805_;
goto v___jp_8783_;
}
}
}
else
{
v___y_8784_ = v_position_8792_;
v___y_8785_ = v_product_8721_;
goto v___jp_8783_;
}
}
else
{
uint64_t v___x_8818_; uint64_t v___x_8819_; 
v___x_8818_ = lean_uint64_sub(v___x_8795_, v___y_8791_);
v___x_8819_ = lean_uint64_shift_left(v_product_8721_, v___x_8818_);
v___y_8784_ = v_position_8792_;
v___y_8785_ = v___x_8819_;
goto v___jp_8783_;
}
}
else
{
uint64_t v___x_8820_; uint8_t v___x_8821_; 
v___x_8820_ = 149ULL;
v___x_8821_ = lean_uint64_dec_lt(v_scale_8722_, v___x_8820_);
if (v___x_8821_ == 0)
{
uint64_t v___x_8822_; uint64_t v___x_8823_; 
v___x_8822_ = lean_uint64_sub(v_scale_8722_, v___x_8820_);
v___x_8823_ = lean_uint64_shift_left(v_product_8721_, v___x_8822_);
v___y_8752_ = v___x_8823_;
goto v___jp_8751_;
}
else
{
uint64_t v___x_8824_; uint8_t v___x_8825_; 
v___x_8824_ = lean_uint64_sub(v___x_8820_, v_scale_8722_);
v___x_8825_ = lean_uint64_dec_eq(v___x_8824_, v___x_8750_);
if (v___x_8825_ == 0)
{
uint64_t v___x_8826_; uint8_t v___x_8827_; 
v___x_8826_ = 64ULL;
v___x_8827_ = lean_uint64_dec_lt(v___x_8824_, v___x_8826_);
if (v___x_8827_ == 0)
{
uint8_t v___x_8828_; 
v___x_8828_ = lean_uint64_dec_eq(v___x_8824_, v___x_8826_);
if (v___x_8828_ == 0)
{
v___y_8752_ = v___x_8750_;
goto v___jp_8751_;
}
else
{
uint64_t v___x_8829_; uint8_t v___x_8830_; 
v___x_8829_ = 9223372036854775808ULL;
v___x_8830_ = lean_uint64_dec_lt(v___x_8829_, v_product_8721_);
if (v___x_8830_ == 0)
{
v___y_8752_ = v___x_8750_;
goto v___jp_8751_;
}
else
{
uint64_t v___x_8831_; 
v___x_8831_ = 1ULL;
v___y_8752_ = v___x_8831_;
goto v___jp_8751_;
}
}
}
else
{
uint64_t v_quotient_8832_; uint64_t v___x_8833_; uint64_t v___x_8834_; uint64_t v___x_8835_; uint64_t v_remainder_8836_; uint64_t v___x_8837_; uint64_t v_half_8838_; uint8_t v___x_8839_; 
v_quotient_8832_ = lean_uint64_shift_right(v_product_8721_, v___x_8824_);
v___x_8833_ = 1ULL;
v___x_8834_ = lean_uint64_shift_left(v___x_8833_, v___x_8824_);
v___x_8835_ = lean_uint64_sub(v___x_8834_, v___x_8833_);
v_remainder_8836_ = lean_uint64_land(v_product_8721_, v___x_8835_);
v___x_8837_ = lean_uint64_sub(v___x_8824_, v___x_8833_);
v_half_8838_ = lean_uint64_shift_left(v___x_8833_, v___x_8837_);
v___x_8839_ = lean_uint64_dec_lt(v_remainder_8836_, v_half_8838_);
if (v___x_8839_ == 0)
{
uint8_t v___x_8840_; 
v___x_8840_ = lean_uint64_dec_lt(v_half_8838_, v_remainder_8836_);
if (v___x_8840_ == 0)
{
uint64_t v___x_8841_; uint8_t v___x_8842_; 
v___x_8841_ = lean_uint64_land(v_quotient_8832_, v___x_8833_);
v___x_8842_ = lean_uint64_dec_eq(v___x_8841_, v___x_8750_);
if (v___x_8842_ == 0)
{
uint64_t v___x_8843_; 
v___x_8843_ = lean_uint64_add(v_quotient_8832_, v___x_8833_);
v___y_8752_ = v___x_8843_;
goto v___jp_8751_;
}
else
{
v___y_8752_ = v_quotient_8832_;
goto v___jp_8751_;
}
}
else
{
uint64_t v___x_8844_; 
v___x_8844_ = lean_uint64_add(v_quotient_8832_, v___x_8833_);
v___y_8752_ = v___x_8844_;
goto v___jp_8751_;
}
}
else
{
v___y_8752_ = v_quotient_8832_;
goto v___jp_8751_;
}
}
}
else
{
v___y_8752_ = v_product_8721_;
goto v___jp_8751_;
}
}
}
}
v___jp_8845_:
{
uint64_t v___x_8848_; uint64_t v___x_8849_; uint8_t v___x_8850_; 
v___x_8848_ = 1ULL;
v___x_8849_ = lean_uint64_shift_right(v___y_8846_, v___x_8848_);
v___x_8850_ = lean_uint64_dec_eq(v___x_8849_, v___x_8750_);
if (v___x_8850_ == 0)
{
uint64_t v___x_8851_; 
v___x_8851_ = lean_uint64_add(v___y_8847_, v___x_8848_);
v___y_8791_ = v___x_8851_;
goto v___jp_8790_;
}
else
{
v___y_8791_ = v___y_8847_;
goto v___jp_8790_;
}
}
v___jp_8852_:
{
uint64_t v___x_8857_; uint8_t v___x_8858_; 
v___x_8857_ = lean_uint64_shift_right(v___y_8853_, v___y_8854_);
v___x_8858_ = lean_uint64_dec_eq(v___x_8857_, v___x_8750_);
if (v___x_8858_ == 0)
{
uint64_t v___x_8859_; 
v___x_8859_ = lean_uint64_add(v___y_8855_, v___y_8854_);
v___y_8846_ = v___y_8856_;
v___y_8847_ = v___x_8859_;
goto v___jp_8845_;
}
else
{
v___y_8846_ = v___y_8856_;
v___y_8847_ = v___y_8855_;
goto v___jp_8845_;
}
}
v___jp_8860_:
{
uint64_t v___x_8863_; uint64_t v___x_8864_; uint8_t v___x_8865_; 
v___x_8863_ = 2ULL;
v___x_8864_ = lean_uint64_shift_right(v___y_8861_, v___x_8863_);
v___x_8865_ = lean_uint64_dec_eq(v___x_8864_, v___x_8750_);
if (v___x_8865_ == 0)
{
v___y_8853_ = v___y_8861_;
v___y_8854_ = v___x_8863_;
v___y_8855_ = v___y_8862_;
v___y_8856_ = v___x_8864_;
goto v___jp_8852_;
}
else
{
v___y_8853_ = v___y_8861_;
v___y_8854_ = v___x_8863_;
v___y_8855_ = v___y_8862_;
v___y_8856_ = v___y_8861_;
goto v___jp_8852_;
}
}
v___jp_8866_:
{
uint64_t v___x_8871_; uint8_t v___x_8872_; 
v___x_8871_ = lean_uint64_shift_right(v___y_8869_, v___y_8868_);
v___x_8872_ = lean_uint64_dec_eq(v___x_8871_, v___x_8750_);
if (v___x_8872_ == 0)
{
uint64_t v___x_8873_; 
v___x_8873_ = lean_uint64_add(v___y_8867_, v___y_8868_);
v___y_8861_ = v___y_8870_;
v___y_8862_ = v___x_8873_;
goto v___jp_8860_;
}
else
{
v___y_8861_ = v___y_8870_;
v___y_8862_ = v___y_8867_;
goto v___jp_8860_;
}
}
v___jp_8874_:
{
uint64_t v___x_8877_; uint64_t v___x_8878_; uint8_t v___x_8879_; 
v___x_8877_ = 4ULL;
v___x_8878_ = lean_uint64_shift_right(v___y_8875_, v___x_8877_);
v___x_8879_ = lean_uint64_dec_eq(v___x_8878_, v___x_8750_);
if (v___x_8879_ == 0)
{
v___y_8867_ = v___y_8876_;
v___y_8868_ = v___x_8877_;
v___y_8869_ = v___y_8875_;
v___y_8870_ = v___x_8878_;
goto v___jp_8866_;
}
else
{
v___y_8867_ = v___y_8876_;
v___y_8868_ = v___x_8877_;
v___y_8869_ = v___y_8875_;
v___y_8870_ = v___y_8875_;
goto v___jp_8866_;
}
}
v___jp_8880_:
{
uint64_t v___x_8885_; uint8_t v___x_8886_; 
v___x_8885_ = lean_uint64_shift_right(v___y_8881_, v___y_8882_);
v___x_8886_ = lean_uint64_dec_eq(v___x_8885_, v___x_8750_);
if (v___x_8886_ == 0)
{
uint64_t v___x_8887_; 
v___x_8887_ = lean_uint64_add(v___y_8883_, v___y_8882_);
v___y_8875_ = v___y_8884_;
v___y_8876_ = v___x_8887_;
goto v___jp_8874_;
}
else
{
v___y_8875_ = v___y_8884_;
v___y_8876_ = v___y_8883_;
goto v___jp_8874_;
}
}
v___jp_8888_:
{
uint64_t v___x_8891_; uint64_t v___x_8892_; uint8_t v___x_8893_; 
v___x_8891_ = 8ULL;
v___x_8892_ = lean_uint64_shift_right(v___y_8889_, v___x_8891_);
v___x_8893_ = lean_uint64_dec_eq(v___x_8892_, v___x_8750_);
if (v___x_8893_ == 0)
{
v___y_8881_ = v___y_8889_;
v___y_8882_ = v___x_8891_;
v___y_8883_ = v___y_8890_;
v___y_8884_ = v___x_8892_;
goto v___jp_8880_;
}
else
{
v___y_8881_ = v___y_8889_;
v___y_8882_ = v___x_8891_;
v___y_8883_ = v___y_8890_;
v___y_8884_ = v___y_8889_;
goto v___jp_8880_;
}
}
v___jp_8894_:
{
uint64_t v___x_8899_; uint8_t v___x_8900_; 
v___x_8899_ = lean_uint64_shift_right(v___y_8897_, v___y_8895_);
v___x_8900_ = lean_uint64_dec_eq(v___x_8899_, v___x_8750_);
if (v___x_8900_ == 0)
{
uint64_t v___x_8901_; 
v___x_8901_ = lean_uint64_add(v___y_8896_, v___y_8895_);
v___y_8889_ = v___y_8898_;
v___y_8890_ = v___x_8901_;
goto v___jp_8888_;
}
else
{
v___y_8889_ = v___y_8898_;
v___y_8890_ = v___y_8896_;
goto v___jp_8888_;
}
}
v___jp_8902_:
{
uint64_t v___x_8905_; uint64_t v___x_8906_; uint8_t v___x_8907_; 
v___x_8905_ = 16ULL;
v___x_8906_ = lean_uint64_shift_right(v___y_8903_, v___x_8905_);
v___x_8907_ = lean_uint64_dec_eq(v___x_8906_, v___x_8750_);
if (v___x_8907_ == 0)
{
v___y_8895_ = v___x_8905_;
v___y_8896_ = v___y_8904_;
v___y_8897_ = v___y_8903_;
v___y_8898_ = v___x_8906_;
goto v___jp_8894_;
}
else
{
v___y_8895_ = v___x_8905_;
v___y_8896_ = v___y_8904_;
v___y_8897_ = v___y_8903_;
v___y_8898_ = v___y_8903_;
goto v___jp_8894_;
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_FastMul_roundP___boxed(lean_object* v_sign_8918_, lean_object* v_product_8919_, lean_object* v_scale_8920_){
_start:
{
uint8_t v_sign_boxed_8921_; uint64_t v_product_boxed_8922_; uint64_t v_scale_boxed_8923_; uint32_t v_res_8924_; lean_object* v_r_8925_; 
v_sign_boxed_8921_ = lean_unbox(v_sign_8918_);
v_product_boxed_8922_ = lean_unbox_uint64(v_product_8919_);
lean_dec_ref(v_product_8919_);
v_scale_boxed_8923_ = lean_unbox_uint64(v_scale_8920_);
lean_dec_ref(v_scale_8920_);
v_res_8924_ = lp_competition_Submission_FastMul_roundP(v_sign_boxed_8921_, v_product_boxed_8922_, v_scale_boxed_8923_);
v_r_8925_ = lean_box_uint32(v_res_8924_);
return v_r_8925_;
}
}
LEAN_EXPORT uint32_t lp_competition_Submission_FastMul_core(uint32_t v_xBits_8926_, uint32_t v_yBits_8927_){
_start:
{
uint32_t v___y_8929_; uint32_t v___y_8933_; uint32_t v___y_8934_; uint32_t v___y_8935_; uint8_t v___y_8939_; uint32_t v___y_8940_; uint64_t v___y_8941_; uint64_t v___y_8942_; uint32_t v___x_8953_; uint32_t v___x_8954_; uint32_t v___x_8955_; uint32_t v___y_8957_; uint32_t v___y_8958_; uint32_t v___y_8959_; uint32_t v___y_8960_; uint8_t v___y_8967_; uint32_t v___y_8968_; uint32_t v___y_8969_; uint32_t v___y_8970_; uint8_t v___y_8974_; uint32_t v___y_8975_; uint64_t v___y_8976_; uint64_t v___y_8977_; uint64_t v___y_8978_; uint8_t v___y_8988_; uint64_t v___y_8989_; uint32_t v___y_8990_; uint8_t v___y_8991_; uint64_t v___y_8992_; uint64_t v___y_8993_; uint8_t v___y_9000_; uint32_t v___y_9001_; uint64_t v___y_9002_; uint64_t v___y_9003_; uint64_t v___y_9004_; uint8_t v___y_9010_; uint32_t v___y_9011_; uint64_t v___y_9012_; uint64_t v___y_9013_; uint64_t v___y_9014_; uint64_t v___y_9015_; uint8_t v___y_9070_; uint32_t v___y_9071_; uint64_t v___y_9072_; uint64_t v___y_9073_; uint64_t v___y_9074_; uint64_t v___y_9075_; uint64_t v___y_9076_; uint64_t v___y_9082_; uint8_t v___y_9083_; uint64_t v___y_9084_; uint32_t v___y_9085_; uint64_t v___y_9086_; uint64_t v___y_9087_; uint64_t v___y_9088_; uint64_t v___y_9089_; uint64_t v___y_9090_; uint8_t v___y_9095_; uint32_t v___y_9096_; uint64_t v___y_9097_; uint64_t v___y_9098_; uint64_t v___y_9099_; uint64_t v___y_9100_; uint64_t v___y_9101_; uint8_t v___y_9106_; uint32_t v___y_9107_; uint64_t v___y_9108_; uint64_t v___y_9109_; uint64_t v___y_9110_; uint64_t v___y_9111_; uint64_t v___y_9112_; uint64_t v___y_9113_; uint64_t v___y_9114_; uint8_t v___y_9119_; uint32_t v___y_9120_; uint64_t v___y_9121_; uint64_t v___y_9122_; uint64_t v___y_9123_; uint64_t v___y_9124_; uint64_t v___y_9125_; uint64_t v___y_9130_; uint64_t v___y_9131_; uint8_t v___y_9132_; uint32_t v___y_9133_; uint64_t v___y_9134_; uint64_t v___y_9135_; uint64_t v___y_9136_; uint64_t v___y_9137_; uint64_t v___y_9138_; uint64_t v___y_9143_; uint8_t v___y_9144_; uint32_t v___y_9145_; uint64_t v___y_9146_; uint64_t v___y_9147_; uint64_t v___y_9148_; uint64_t v___y_9149_; uint8_t v___y_9154_; uint32_t v___y_9155_; uint64_t v___y_9156_; uint64_t v___y_9157_; uint64_t v___y_9158_; uint64_t v___y_9159_; uint64_t v___y_9160_; uint64_t v___y_9161_; uint64_t v___y_9162_; uint8_t v___y_9167_; uint32_t v___y_9168_; uint64_t v___y_9169_; uint64_t v___y_9170_; uint64_t v___y_9171_; uint64_t v___y_9172_; uint64_t v___y_9173_; uint8_t v___y_9178_; uint32_t v___y_9179_; uint64_t v___y_9180_; uint64_t v___y_9181_; uint64_t v___y_9182_; uint64_t v___y_9183_; uint64_t v___y_9184_; uint64_t v___y_9188_; uint8_t v___y_9189_; uint32_t v___y_9190_; uint64_t v___y_9191_; uint64_t v___y_9192_; uint64_t v___y_9193_; uint32_t v_xExponent_9203_; uint32_t v___x_9204_; uint32_t v_yExponent_9205_; uint8_t v___y_9207_; uint32_t v___y_9208_; uint64_t v___y_9209_; uint64_t v___y_9210_; uint64_t v___y_9211_; uint8_t v___y_9218_; uint32_t v___y_9219_; uint64_t v___y_9220_; uint64_t v___y_9221_; uint8_t v___y_9228_; uint32_t v___y_9229_; uint32_t v___y_9230_; uint64_t v___y_9231_; uint8_t v___y_9239_; uint8_t v___y_9254_; uint8_t v___y_9255_; uint8_t v___y_9257_; uint32_t v___x_9264_; uint32_t v___x_9265_; uint32_t v___x_9266_; uint8_t v___x_9267_; 
v___x_8953_ = 23;
v___x_8954_ = lean_uint32_shift_right(v_xBits_8926_, v___x_8953_);
v___x_8955_ = 255;
v_xExponent_9203_ = lean_uint32_land(v___x_8954_, v___x_8955_);
v___x_9204_ = lean_uint32_shift_right(v_yBits_8927_, v___x_8953_);
v_yExponent_9205_ = lean_uint32_land(v___x_9204_, v___x_8955_);
v___x_9264_ = 2147483648;
v___x_9265_ = lean_uint32_land(v_xBits_8926_, v___x_9264_);
v___x_9266_ = 0;
v___x_9267_ = lean_uint32_dec_eq(v___x_9265_, v___x_9266_);
if (v___x_9267_ == 0)
{
uint8_t v___x_9268_; 
v___x_9268_ = 1;
v___y_9257_ = v___x_9268_;
goto v___jp_9256_;
}
else
{
uint8_t v___x_9269_; 
v___x_9269_ = 0;
v___y_9257_ = v___x_9269_;
goto v___jp_9256_;
}
v___jp_8928_:
{
uint32_t v___x_8930_; uint32_t v___x_8931_; 
v___x_8930_ = 8388608;
v___x_8931_ = lean_uint32_lor(v___y_8929_, v___x_8930_);
return v___x_8931_;
}
v___jp_8932_:
{
uint32_t v___x_8936_; uint32_t v___x_8937_; 
v___x_8936_ = lean_uint32_land(v___y_8934_, v___y_8933_);
v___x_8937_ = lean_uint32_lor(v___y_8935_, v___x_8936_);
return v___x_8937_;
}
v___jp_8938_:
{
uint8_t v___x_8943_; 
v___x_8943_ = lean_uint64_dec_eq(v___y_8942_, v___y_8941_);
if (v___x_8943_ == 0)
{
uint64_t v___x_8944_; uint8_t v___x_8945_; 
v___x_8944_ = 8388608ULL;
v___x_8945_ = lean_uint64_dec_eq(v___y_8942_, v___x_8944_);
if (v___x_8945_ == 0)
{
uint32_t v___x_8946_; 
v___x_8946_ = lean_uint64_to_uint32(v___y_8942_);
if (v___y_8939_ == 0)
{
uint32_t v___x_8947_; 
v___x_8947_ = 0;
v___y_8933_ = v___y_8940_;
v___y_8934_ = v___x_8946_;
v___y_8935_ = v___x_8947_;
goto v___jp_8932_;
}
else
{
uint32_t v___x_8948_; 
v___x_8948_ = 2147483648;
v___y_8933_ = v___y_8940_;
v___y_8934_ = v___x_8946_;
v___y_8935_ = v___x_8948_;
goto v___jp_8932_;
}
}
else
{
if (v___y_8939_ == 0)
{
uint32_t v___x_8949_; 
v___x_8949_ = 0;
v___y_8929_ = v___x_8949_;
goto v___jp_8928_;
}
else
{
uint32_t v___x_8950_; 
v___x_8950_ = 2147483648;
v___y_8929_ = v___x_8950_;
goto v___jp_8928_;
}
}
}
else
{
if (v___y_8939_ == 0)
{
uint32_t v___x_8951_; 
v___x_8951_ = 0;
return v___x_8951_;
}
else
{
uint32_t v___x_8952_; 
v___x_8952_ = 2147483648;
return v___x_8952_;
}
}
}
v___jp_8956_:
{
uint32_t v___x_8961_; uint32_t v___x_8962_; uint32_t v___x_8963_; uint32_t v___x_8964_; uint32_t v___x_8965_; 
v___x_8961_ = lean_uint32_land(v___y_8959_, v___x_8955_);
v___x_8962_ = lean_uint32_shift_left(v___x_8961_, v___x_8953_);
v___x_8963_ = lean_uint32_lor(v___y_8960_, v___x_8962_);
v___x_8964_ = lean_uint32_land(v___y_8958_, v___y_8957_);
v___x_8965_ = lean_uint32_lor(v___x_8963_, v___x_8964_);
return v___x_8965_;
}
v___jp_8966_:
{
if (v___y_8967_ == 0)
{
uint32_t v___x_8971_; 
v___x_8971_ = 0;
v___y_8957_ = v___y_8968_;
v___y_8958_ = v___y_8970_;
v___y_8959_ = v___y_8969_;
v___y_8960_ = v___x_8971_;
goto v___jp_8956_;
}
else
{
uint32_t v___x_8972_; 
v___x_8972_ = 2147483648;
v___y_8957_ = v___y_8968_;
v___y_8958_ = v___y_8970_;
v___y_8959_ = v___y_8969_;
v___y_8960_ = v___x_8972_;
goto v___jp_8956_;
}
}
v___jp_8973_:
{
uint64_t v___x_8979_; uint64_t v_encodedExponent_8980_; uint32_t v___x_8981_; uint64_t v___x_8982_; uint8_t v___x_8983_; 
v___x_8979_ = 171ULL;
v_encodedExponent_8980_ = lean_uint64_sub(v___y_8977_, v___x_8979_);
v___x_8981_ = lean_uint64_to_uint32(v_encodedExponent_8980_);
v___x_8982_ = 8388608ULL;
v___x_8983_ = lean_uint64_dec_lt(v___y_8978_, v___x_8982_);
if (v___x_8983_ == 0)
{
uint64_t v___x_8984_; uint32_t v___x_8985_; 
v___x_8984_ = lean_uint64_sub(v___y_8978_, v___x_8982_);
v___x_8985_ = lean_uint64_to_uint32(v___x_8984_);
v___y_8967_ = v___y_8974_;
v___y_8968_ = v___y_8975_;
v___y_8969_ = v___x_8981_;
v___y_8970_ = v___x_8985_;
goto v___jp_8966_;
}
else
{
uint32_t v___x_8986_; 
v___x_8986_ = lean_uint64_to_uint32(v___y_8976_);
v___y_8967_ = v___y_8974_;
v___y_8968_ = v___y_8975_;
v___y_8969_ = v___x_8981_;
v___y_8970_ = v___x_8986_;
goto v___jp_8966_;
}
}
v___jp_8987_:
{
uint64_t v___x_8994_; uint8_t v___x_8995_; 
v___x_8994_ = 425ULL;
v___x_8995_ = lean_uint64_dec_lt(v___x_8994_, v___y_8993_);
if (v___x_8995_ == 0)
{
if (v___y_8991_ == 0)
{
v___y_8974_ = v___y_8988_;
v___y_8975_ = v___y_8990_;
v___y_8976_ = v___y_8992_;
v___y_8977_ = v___y_8993_;
v___y_8978_ = v___y_8989_;
goto v___jp_8973_;
}
else
{
uint64_t v___x_8996_; 
v___x_8996_ = 8388608ULL;
v___y_8974_ = v___y_8988_;
v___y_8975_ = v___y_8990_;
v___y_8976_ = v___y_8992_;
v___y_8977_ = v___y_8993_;
v___y_8978_ = v___x_8996_;
goto v___jp_8973_;
}
}
else
{
if (v___y_8988_ == 0)
{
uint32_t v___x_8997_; 
v___x_8997_ = 2139095040;
return v___x_8997_;
}
else
{
uint32_t v___x_8998_; 
v___x_8998_ = 4286578688;
return v___x_8998_;
}
}
}
v___jp_8999_:
{
uint64_t v___x_9005_; uint8_t v_carry_9006_; 
v___x_9005_ = 16777216ULL;
v_carry_9006_ = lean_uint64_dec_eq(v___y_9004_, v___x_9005_);
if (v_carry_9006_ == 0)
{
v___y_8988_ = v___y_9000_;
v___y_8989_ = v___y_9004_;
v___y_8990_ = v___y_9001_;
v___y_8991_ = v_carry_9006_;
v___y_8992_ = v___y_9002_;
v___y_8993_ = v___y_9003_;
goto v___jp_8987_;
}
else
{
uint64_t v___x_9007_; uint64_t v___x_9008_; 
v___x_9007_ = 1ULL;
v___x_9008_ = lean_uint64_add(v___y_9003_, v___x_9007_);
v___y_8988_ = v___y_9000_;
v___y_8989_ = v___y_9004_;
v___y_8990_ = v___y_9001_;
v___y_8991_ = v_carry_9006_;
v___y_8992_ = v___y_9002_;
v___y_8993_ = v___x_9008_;
goto v___jp_8987_;
}
}
v___jp_9009_:
{
uint64_t v_position_9016_; uint64_t v___x_9017_; uint8_t v___x_9018_; 
v_position_9016_ = lean_uint64_add(v___y_9015_, v___y_9013_);
v___x_9017_ = 172ULL;
v___x_9018_ = lean_uint64_dec_lt(v_position_9016_, v___x_9017_);
if (v___x_9018_ == 0)
{
uint64_t v___x_9019_; uint8_t v___x_9020_; 
v___x_9019_ = 23ULL;
v___x_9020_ = lean_uint64_dec_lt(v___y_9015_, v___x_9019_);
if (v___x_9020_ == 0)
{
uint64_t v___x_9021_; uint8_t v___x_9022_; 
v___x_9021_ = lean_uint64_sub(v___y_9015_, v___x_9019_);
v___x_9022_ = lean_uint64_dec_eq(v___x_9021_, v___y_9012_);
if (v___x_9022_ == 0)
{
uint64_t v___x_9023_; uint8_t v___x_9024_; 
v___x_9023_ = 64ULL;
v___x_9024_ = lean_uint64_dec_lt(v___x_9021_, v___x_9023_);
if (v___x_9024_ == 0)
{
uint8_t v___x_9025_; 
v___x_9025_ = lean_uint64_dec_eq(v___x_9021_, v___x_9023_);
if (v___x_9025_ == 0)
{
v___y_9000_ = v___y_9010_;
v___y_9001_ = v___y_9011_;
v___y_9002_ = v___y_9012_;
v___y_9003_ = v_position_9016_;
v___y_9004_ = v___y_9012_;
goto v___jp_8999_;
}
else
{
uint64_t v___x_9026_; uint8_t v___x_9027_; 
v___x_9026_ = 9223372036854775808ULL;
v___x_9027_ = lean_uint64_dec_lt(v___x_9026_, v___y_9014_);
if (v___x_9027_ == 0)
{
v___y_9000_ = v___y_9010_;
v___y_9001_ = v___y_9011_;
v___y_9002_ = v___y_9012_;
v___y_9003_ = v_position_9016_;
v___y_9004_ = v___y_9012_;
goto v___jp_8999_;
}
else
{
uint64_t v___x_9028_; 
v___x_9028_ = 1ULL;
v___y_9000_ = v___y_9010_;
v___y_9001_ = v___y_9011_;
v___y_9002_ = v___y_9012_;
v___y_9003_ = v_position_9016_;
v___y_9004_ = v___x_9028_;
goto v___jp_8999_;
}
}
}
else
{
uint64_t v_quotient_9029_; uint64_t v___x_9030_; uint64_t v___x_9031_; uint64_t v___x_9032_; uint64_t v_remainder_9033_; uint64_t v___x_9034_; uint64_t v_half_9035_; uint8_t v___x_9036_; 
v_quotient_9029_ = lean_uint64_shift_right(v___y_9014_, v___x_9021_);
v___x_9030_ = 1ULL;
v___x_9031_ = lean_uint64_shift_left(v___x_9030_, v___x_9021_);
v___x_9032_ = lean_uint64_sub(v___x_9031_, v___x_9030_);
v_remainder_9033_ = lean_uint64_land(v___y_9014_, v___x_9032_);
v___x_9034_ = lean_uint64_sub(v___x_9021_, v___x_9030_);
v_half_9035_ = lean_uint64_shift_left(v___x_9030_, v___x_9034_);
v___x_9036_ = lean_uint64_dec_lt(v_remainder_9033_, v_half_9035_);
if (v___x_9036_ == 0)
{
uint8_t v___x_9037_; 
v___x_9037_ = lean_uint64_dec_lt(v_half_9035_, v_remainder_9033_);
if (v___x_9037_ == 0)
{
uint64_t v___x_9038_; uint8_t v___x_9039_; 
v___x_9038_ = lean_uint64_land(v_quotient_9029_, v___x_9030_);
v___x_9039_ = lean_uint64_dec_eq(v___x_9038_, v___y_9012_);
if (v___x_9039_ == 0)
{
uint64_t v___x_9040_; 
v___x_9040_ = lean_uint64_add(v_quotient_9029_, v___x_9030_);
v___y_9000_ = v___y_9010_;
v___y_9001_ = v___y_9011_;
v___y_9002_ = v___y_9012_;
v___y_9003_ = v_position_9016_;
v___y_9004_ = v___x_9040_;
goto v___jp_8999_;
}
else
{
v___y_9000_ = v___y_9010_;
v___y_9001_ = v___y_9011_;
v___y_9002_ = v___y_9012_;
v___y_9003_ = v_position_9016_;
v___y_9004_ = v_quotient_9029_;
goto v___jp_8999_;
}
}
else
{
uint64_t v___x_9041_; 
v___x_9041_ = lean_uint64_add(v_quotient_9029_, v___x_9030_);
v___y_9000_ = v___y_9010_;
v___y_9001_ = v___y_9011_;
v___y_9002_ = v___y_9012_;
v___y_9003_ = v_position_9016_;
v___y_9004_ = v___x_9041_;
goto v___jp_8999_;
}
}
else
{
v___y_9000_ = v___y_9010_;
v___y_9001_ = v___y_9011_;
v___y_9002_ = v___y_9012_;
v___y_9003_ = v_position_9016_;
v___y_9004_ = v_quotient_9029_;
goto v___jp_8999_;
}
}
}
else
{
v___y_9000_ = v___y_9010_;
v___y_9001_ = v___y_9011_;
v___y_9002_ = v___y_9012_;
v___y_9003_ = v_position_9016_;
v___y_9004_ = v___y_9014_;
goto v___jp_8999_;
}
}
else
{
uint64_t v___x_9042_; uint64_t v___x_9043_; 
v___x_9042_ = lean_uint64_sub(v___x_9019_, v___y_9015_);
v___x_9043_ = lean_uint64_shift_left(v___y_9014_, v___x_9042_);
v___y_9000_ = v___y_9010_;
v___y_9001_ = v___y_9011_;
v___y_9002_ = v___y_9012_;
v___y_9003_ = v_position_9016_;
v___y_9004_ = v___x_9043_;
goto v___jp_8999_;
}
}
else
{
uint64_t v___x_9044_; uint8_t v___x_9045_; 
v___x_9044_ = 149ULL;
v___x_9045_ = lean_uint64_dec_lt(v___y_9013_, v___x_9044_);
if (v___x_9045_ == 0)
{
uint64_t v___x_9046_; uint64_t v___x_9047_; 
v___x_9046_ = lean_uint64_sub(v___y_9013_, v___x_9044_);
v___x_9047_ = lean_uint64_shift_left(v___y_9014_, v___x_9046_);
v___y_8939_ = v___y_9010_;
v___y_8940_ = v___y_9011_;
v___y_8941_ = v___y_9012_;
v___y_8942_ = v___x_9047_;
goto v___jp_8938_;
}
else
{
uint64_t v___x_9048_; uint8_t v___x_9049_; 
v___x_9048_ = lean_uint64_sub(v___x_9044_, v___y_9013_);
v___x_9049_ = lean_uint64_dec_eq(v___x_9048_, v___y_9012_);
if (v___x_9049_ == 0)
{
uint64_t v___x_9050_; uint8_t v___x_9051_; 
v___x_9050_ = 64ULL;
v___x_9051_ = lean_uint64_dec_lt(v___x_9048_, v___x_9050_);
if (v___x_9051_ == 0)
{
uint8_t v___x_9052_; 
v___x_9052_ = lean_uint64_dec_eq(v___x_9048_, v___x_9050_);
if (v___x_9052_ == 0)
{
v___y_8939_ = v___y_9010_;
v___y_8940_ = v___y_9011_;
v___y_8941_ = v___y_9012_;
v___y_8942_ = v___y_9012_;
goto v___jp_8938_;
}
else
{
uint64_t v___x_9053_; uint8_t v___x_9054_; 
v___x_9053_ = 9223372036854775808ULL;
v___x_9054_ = lean_uint64_dec_lt(v___x_9053_, v___y_9014_);
if (v___x_9054_ == 0)
{
v___y_8939_ = v___y_9010_;
v___y_8940_ = v___y_9011_;
v___y_8941_ = v___y_9012_;
v___y_8942_ = v___y_9012_;
goto v___jp_8938_;
}
else
{
uint64_t v___x_9055_; 
v___x_9055_ = 1ULL;
v___y_8939_ = v___y_9010_;
v___y_8940_ = v___y_9011_;
v___y_8941_ = v___y_9012_;
v___y_8942_ = v___x_9055_;
goto v___jp_8938_;
}
}
}
else
{
uint64_t v_quotient_9056_; uint64_t v___x_9057_; uint64_t v___x_9058_; uint64_t v___x_9059_; uint64_t v_remainder_9060_; uint64_t v___x_9061_; uint64_t v_half_9062_; uint8_t v___x_9063_; 
v_quotient_9056_ = lean_uint64_shift_right(v___y_9014_, v___x_9048_);
v___x_9057_ = 1ULL;
v___x_9058_ = lean_uint64_shift_left(v___x_9057_, v___x_9048_);
v___x_9059_ = lean_uint64_sub(v___x_9058_, v___x_9057_);
v_remainder_9060_ = lean_uint64_land(v___y_9014_, v___x_9059_);
v___x_9061_ = lean_uint64_sub(v___x_9048_, v___x_9057_);
v_half_9062_ = lean_uint64_shift_left(v___x_9057_, v___x_9061_);
v___x_9063_ = lean_uint64_dec_lt(v_remainder_9060_, v_half_9062_);
if (v___x_9063_ == 0)
{
uint8_t v___x_9064_; 
v___x_9064_ = lean_uint64_dec_lt(v_half_9062_, v_remainder_9060_);
if (v___x_9064_ == 0)
{
uint64_t v___x_9065_; uint8_t v___x_9066_; 
v___x_9065_ = lean_uint64_land(v_quotient_9056_, v___x_9057_);
v___x_9066_ = lean_uint64_dec_eq(v___x_9065_, v___y_9012_);
if (v___x_9066_ == 0)
{
uint64_t v___x_9067_; 
v___x_9067_ = lean_uint64_add(v_quotient_9056_, v___x_9057_);
v___y_8939_ = v___y_9010_;
v___y_8940_ = v___y_9011_;
v___y_8941_ = v___y_9012_;
v___y_8942_ = v___x_9067_;
goto v___jp_8938_;
}
else
{
v___y_8939_ = v___y_9010_;
v___y_8940_ = v___y_9011_;
v___y_8941_ = v___y_9012_;
v___y_8942_ = v_quotient_9056_;
goto v___jp_8938_;
}
}
else
{
uint64_t v___x_9068_; 
v___x_9068_ = lean_uint64_add(v_quotient_9056_, v___x_9057_);
v___y_8939_ = v___y_9010_;
v___y_8940_ = v___y_9011_;
v___y_8941_ = v___y_9012_;
v___y_8942_ = v___x_9068_;
goto v___jp_8938_;
}
}
else
{
v___y_8939_ = v___y_9010_;
v___y_8940_ = v___y_9011_;
v___y_8941_ = v___y_9012_;
v___y_8942_ = v_quotient_9056_;
goto v___jp_8938_;
}
}
}
else
{
v___y_8939_ = v___y_9010_;
v___y_8940_ = v___y_9011_;
v___y_8941_ = v___y_9012_;
v___y_8942_ = v___y_9014_;
goto v___jp_8938_;
}
}
}
}
v___jp_9069_:
{
uint64_t v___x_9077_; uint64_t v___x_9078_; uint8_t v___x_9079_; 
v___x_9077_ = 1ULL;
v___x_9078_ = lean_uint64_shift_right(v___y_9074_, v___x_9077_);
v___x_9079_ = lean_uint64_dec_eq(v___x_9078_, v___y_9072_);
if (v___x_9079_ == 0)
{
uint64_t v___x_9080_; 
v___x_9080_ = lean_uint64_add(v___y_9076_, v___x_9077_);
v___y_9010_ = v___y_9070_;
v___y_9011_ = v___y_9071_;
v___y_9012_ = v___y_9072_;
v___y_9013_ = v___y_9073_;
v___y_9014_ = v___y_9075_;
v___y_9015_ = v___x_9080_;
goto v___jp_9009_;
}
else
{
v___y_9010_ = v___y_9070_;
v___y_9011_ = v___y_9071_;
v___y_9012_ = v___y_9072_;
v___y_9013_ = v___y_9073_;
v___y_9014_ = v___y_9075_;
v___y_9015_ = v___y_9076_;
goto v___jp_9009_;
}
}
v___jp_9081_:
{
uint64_t v___x_9091_; uint8_t v___x_9092_; 
v___x_9091_ = lean_uint64_shift_right(v___y_9084_, v___y_9082_);
v___x_9092_ = lean_uint64_dec_eq(v___x_9091_, v___y_9086_);
if (v___x_9092_ == 0)
{
uint64_t v___x_9093_; 
v___x_9093_ = lean_uint64_add(v___y_9088_, v___y_9082_);
v___y_9070_ = v___y_9083_;
v___y_9071_ = v___y_9085_;
v___y_9072_ = v___y_9086_;
v___y_9073_ = v___y_9087_;
v___y_9074_ = v___y_9090_;
v___y_9075_ = v___y_9089_;
v___y_9076_ = v___x_9093_;
goto v___jp_9069_;
}
else
{
v___y_9070_ = v___y_9083_;
v___y_9071_ = v___y_9085_;
v___y_9072_ = v___y_9086_;
v___y_9073_ = v___y_9087_;
v___y_9074_ = v___y_9090_;
v___y_9075_ = v___y_9089_;
v___y_9076_ = v___y_9088_;
goto v___jp_9069_;
}
}
v___jp_9094_:
{
uint64_t v___x_9102_; uint64_t v___x_9103_; uint8_t v___x_9104_; 
v___x_9102_ = 2ULL;
v___x_9103_ = lean_uint64_shift_right(v___y_9097_, v___x_9102_);
v___x_9104_ = lean_uint64_dec_eq(v___x_9103_, v___y_9098_);
if (v___x_9104_ == 0)
{
v___y_9082_ = v___x_9102_;
v___y_9083_ = v___y_9095_;
v___y_9084_ = v___y_9097_;
v___y_9085_ = v___y_9096_;
v___y_9086_ = v___y_9098_;
v___y_9087_ = v___y_9099_;
v___y_9088_ = v___y_9101_;
v___y_9089_ = v___y_9100_;
v___y_9090_ = v___x_9103_;
goto v___jp_9081_;
}
else
{
v___y_9082_ = v___x_9102_;
v___y_9083_ = v___y_9095_;
v___y_9084_ = v___y_9097_;
v___y_9085_ = v___y_9096_;
v___y_9086_ = v___y_9098_;
v___y_9087_ = v___y_9099_;
v___y_9088_ = v___y_9101_;
v___y_9089_ = v___y_9100_;
v___y_9090_ = v___y_9097_;
goto v___jp_9081_;
}
}
v___jp_9105_:
{
uint64_t v___x_9115_; uint8_t v___x_9116_; 
v___x_9115_ = lean_uint64_shift_right(v___y_9111_, v___y_9112_);
v___x_9116_ = lean_uint64_dec_eq(v___x_9115_, v___y_9108_);
if (v___x_9116_ == 0)
{
uint64_t v___x_9117_; 
v___x_9117_ = lean_uint64_add(v___y_9109_, v___y_9112_);
v___y_9095_ = v___y_9106_;
v___y_9096_ = v___y_9107_;
v___y_9097_ = v___y_9114_;
v___y_9098_ = v___y_9108_;
v___y_9099_ = v___y_9110_;
v___y_9100_ = v___y_9113_;
v___y_9101_ = v___x_9117_;
goto v___jp_9094_;
}
else
{
v___y_9095_ = v___y_9106_;
v___y_9096_ = v___y_9107_;
v___y_9097_ = v___y_9114_;
v___y_9098_ = v___y_9108_;
v___y_9099_ = v___y_9110_;
v___y_9100_ = v___y_9113_;
v___y_9101_ = v___y_9109_;
goto v___jp_9094_;
}
}
v___jp_9118_:
{
uint64_t v___x_9126_; uint64_t v___x_9127_; uint8_t v___x_9128_; 
v___x_9126_ = 4ULL;
v___x_9127_ = lean_uint64_shift_right(v___y_9123_, v___x_9126_);
v___x_9128_ = lean_uint64_dec_eq(v___x_9127_, v___y_9121_);
if (v___x_9128_ == 0)
{
v___y_9106_ = v___y_9119_;
v___y_9107_ = v___y_9120_;
v___y_9108_ = v___y_9121_;
v___y_9109_ = v___y_9125_;
v___y_9110_ = v___y_9122_;
v___y_9111_ = v___y_9123_;
v___y_9112_ = v___x_9126_;
v___y_9113_ = v___y_9124_;
v___y_9114_ = v___x_9127_;
goto v___jp_9105_;
}
else
{
v___y_9106_ = v___y_9119_;
v___y_9107_ = v___y_9120_;
v___y_9108_ = v___y_9121_;
v___y_9109_ = v___y_9125_;
v___y_9110_ = v___y_9122_;
v___y_9111_ = v___y_9123_;
v___y_9112_ = v___x_9126_;
v___y_9113_ = v___y_9124_;
v___y_9114_ = v___y_9123_;
goto v___jp_9105_;
}
}
v___jp_9129_:
{
uint64_t v___x_9139_; uint8_t v___x_9140_; 
v___x_9139_ = lean_uint64_shift_right(v___y_9130_, v___y_9131_);
v___x_9140_ = lean_uint64_dec_eq(v___x_9139_, v___y_9134_);
if (v___x_9140_ == 0)
{
uint64_t v___x_9141_; 
v___x_9141_ = lean_uint64_add(v___y_9136_, v___y_9131_);
v___y_9119_ = v___y_9132_;
v___y_9120_ = v___y_9133_;
v___y_9121_ = v___y_9134_;
v___y_9122_ = v___y_9135_;
v___y_9123_ = v___y_9138_;
v___y_9124_ = v___y_9137_;
v___y_9125_ = v___x_9141_;
goto v___jp_9118_;
}
else
{
v___y_9119_ = v___y_9132_;
v___y_9120_ = v___y_9133_;
v___y_9121_ = v___y_9134_;
v___y_9122_ = v___y_9135_;
v___y_9123_ = v___y_9138_;
v___y_9124_ = v___y_9137_;
v___y_9125_ = v___y_9136_;
goto v___jp_9118_;
}
}
v___jp_9142_:
{
uint64_t v___x_9150_; uint64_t v___x_9151_; uint8_t v___x_9152_; 
v___x_9150_ = 8ULL;
v___x_9151_ = lean_uint64_shift_right(v___y_9143_, v___x_9150_);
v___x_9152_ = lean_uint64_dec_eq(v___x_9151_, v___y_9146_);
if (v___x_9152_ == 0)
{
v___y_9130_ = v___y_9143_;
v___y_9131_ = v___x_9150_;
v___y_9132_ = v___y_9144_;
v___y_9133_ = v___y_9145_;
v___y_9134_ = v___y_9146_;
v___y_9135_ = v___y_9147_;
v___y_9136_ = v___y_9149_;
v___y_9137_ = v___y_9148_;
v___y_9138_ = v___x_9151_;
goto v___jp_9129_;
}
else
{
v___y_9130_ = v___y_9143_;
v___y_9131_ = v___x_9150_;
v___y_9132_ = v___y_9144_;
v___y_9133_ = v___y_9145_;
v___y_9134_ = v___y_9146_;
v___y_9135_ = v___y_9147_;
v___y_9136_ = v___y_9149_;
v___y_9137_ = v___y_9148_;
v___y_9138_ = v___y_9143_;
goto v___jp_9129_;
}
}
v___jp_9153_:
{
uint64_t v___x_9163_; uint8_t v___x_9164_; 
v___x_9163_ = lean_uint64_shift_right(v___y_9156_, v___y_9160_);
v___x_9164_ = lean_uint64_dec_eq(v___x_9163_, v___y_9157_);
if (v___x_9164_ == 0)
{
uint64_t v___x_9165_; 
v___x_9165_ = lean_uint64_add(v___y_9158_, v___y_9160_);
v___y_9143_ = v___y_9162_;
v___y_9144_ = v___y_9154_;
v___y_9145_ = v___y_9155_;
v___y_9146_ = v___y_9157_;
v___y_9147_ = v___y_9159_;
v___y_9148_ = v___y_9161_;
v___y_9149_ = v___x_9165_;
goto v___jp_9142_;
}
else
{
v___y_9143_ = v___y_9162_;
v___y_9144_ = v___y_9154_;
v___y_9145_ = v___y_9155_;
v___y_9146_ = v___y_9157_;
v___y_9147_ = v___y_9159_;
v___y_9148_ = v___y_9161_;
v___y_9149_ = v___y_9158_;
goto v___jp_9142_;
}
}
v___jp_9166_:
{
uint64_t v___x_9174_; uint64_t v___x_9175_; uint8_t v___x_9176_; 
v___x_9174_ = 16ULL;
v___x_9175_ = lean_uint64_shift_right(v___y_9170_, v___x_9174_);
v___x_9176_ = lean_uint64_dec_eq(v___x_9175_, v___y_9169_);
if (v___x_9176_ == 0)
{
v___y_9154_ = v___y_9167_;
v___y_9155_ = v___y_9168_;
v___y_9156_ = v___y_9170_;
v___y_9157_ = v___y_9169_;
v___y_9158_ = v___y_9173_;
v___y_9159_ = v___y_9171_;
v___y_9160_ = v___x_9174_;
v___y_9161_ = v___y_9172_;
v___y_9162_ = v___x_9175_;
goto v___jp_9153_;
}
else
{
v___y_9154_ = v___y_9167_;
v___y_9155_ = v___y_9168_;
v___y_9156_ = v___y_9170_;
v___y_9157_ = v___y_9169_;
v___y_9158_ = v___y_9173_;
v___y_9159_ = v___y_9171_;
v___y_9160_ = v___x_9174_;
v___y_9161_ = v___y_9172_;
v___y_9162_ = v___y_9170_;
goto v___jp_9153_;
}
}
v___jp_9177_:
{
uint64_t v___x_9185_; uint8_t v___x_9186_; 
v___x_9185_ = lean_uint64_shift_right(v___y_9183_, v___y_9181_);
v___x_9186_ = lean_uint64_dec_eq(v___x_9185_, v___y_9180_);
if (v___x_9186_ == 0)
{
v___y_9167_ = v___y_9178_;
v___y_9168_ = v___y_9179_;
v___y_9169_ = v___y_9180_;
v___y_9170_ = v___y_9184_;
v___y_9171_ = v___y_9182_;
v___y_9172_ = v___y_9183_;
v___y_9173_ = v___y_9181_;
goto v___jp_9166_;
}
else
{
v___y_9167_ = v___y_9178_;
v___y_9168_ = v___y_9179_;
v___y_9169_ = v___y_9180_;
v___y_9170_ = v___y_9184_;
v___y_9171_ = v___y_9182_;
v___y_9172_ = v___y_9183_;
v___y_9173_ = v___y_9180_;
goto v___jp_9166_;
}
}
v___jp_9187_:
{
uint64_t v___x_9194_; uint64_t v___x_9195_; uint8_t v___x_9196_; 
v___x_9194_ = lean_uint64_mul(v___y_9192_, v___y_9191_);
v___x_9195_ = 0ULL;
v___x_9196_ = lean_uint64_dec_eq(v___x_9194_, v___x_9195_);
if (v___x_9196_ == 0)
{
uint64_t v___x_9197_; uint64_t v___x_9198_; uint64_t v___x_9199_; uint8_t v___x_9200_; 
v___x_9197_ = lean_uint64_add(v___y_9188_, v___y_9193_);
v___x_9198_ = 32ULL;
v___x_9199_ = lean_uint64_shift_right(v___x_9194_, v___x_9198_);
v___x_9200_ = lean_uint64_dec_eq(v___x_9199_, v___x_9195_);
if (v___x_9200_ == 0)
{
v___y_9178_ = v___y_9189_;
v___y_9179_ = v___y_9190_;
v___y_9180_ = v___x_9195_;
v___y_9181_ = v___x_9198_;
v___y_9182_ = v___x_9197_;
v___y_9183_ = v___x_9194_;
v___y_9184_ = v___x_9199_;
goto v___jp_9177_;
}
else
{
v___y_9178_ = v___y_9189_;
v___y_9179_ = v___y_9190_;
v___y_9180_ = v___x_9195_;
v___y_9181_ = v___x_9198_;
v___y_9182_ = v___x_9197_;
v___y_9183_ = v___x_9194_;
v___y_9184_ = v___x_9194_;
goto v___jp_9177_;
}
}
else
{
if (v___y_9189_ == 0)
{
uint32_t v___x_9201_; 
v___x_9201_ = 0;
return v___x_9201_;
}
else
{
uint32_t v___x_9202_; 
v___x_9202_ = 2147483648;
return v___x_9202_;
}
}
}
v___jp_9206_:
{
uint64_t v___x_9212_; uint64_t v___x_9213_; uint8_t v___x_9214_; 
v___x_9212_ = lean_uint32_to_uint64(v_yExponent_9205_);
v___x_9213_ = 0ULL;
v___x_9214_ = lean_uint64_dec_eq(v___x_9212_, v___x_9213_);
if (v___x_9214_ == 0)
{
uint64_t v___x_9215_; uint64_t v___x_9216_; 
v___x_9215_ = 1ULL;
v___x_9216_ = lean_uint64_sub(v___x_9212_, v___x_9215_);
v___y_9188_ = v___y_9211_;
v___y_9189_ = v___y_9207_;
v___y_9190_ = v___y_9208_;
v___y_9191_ = v___y_9210_;
v___y_9192_ = v___y_9209_;
v___y_9193_ = v___x_9216_;
goto v___jp_9187_;
}
else
{
v___y_9188_ = v___y_9211_;
v___y_9189_ = v___y_9207_;
v___y_9190_ = v___y_9208_;
v___y_9191_ = v___y_9210_;
v___y_9192_ = v___y_9209_;
v___y_9193_ = v___x_9213_;
goto v___jp_9187_;
}
}
v___jp_9217_:
{
uint64_t v___x_9222_; uint64_t v___x_9223_; uint8_t v___x_9224_; 
v___x_9222_ = lean_uint32_to_uint64(v_xExponent_9203_);
v___x_9223_ = 0ULL;
v___x_9224_ = lean_uint64_dec_eq(v___x_9222_, v___x_9223_);
if (v___x_9224_ == 0)
{
uint64_t v___x_9225_; uint64_t v___x_9226_; 
v___x_9225_ = 1ULL;
v___x_9226_ = lean_uint64_sub(v___x_9222_, v___x_9225_);
v___y_9207_ = v___y_9218_;
v___y_9208_ = v___y_9219_;
v___y_9209_ = v___y_9220_;
v___y_9210_ = v___y_9221_;
v___y_9211_ = v___x_9226_;
goto v___jp_9206_;
}
else
{
v___y_9207_ = v___y_9218_;
v___y_9208_ = v___y_9219_;
v___y_9209_ = v___y_9220_;
v___y_9210_ = v___y_9221_;
v___y_9211_ = v___x_9223_;
goto v___jp_9206_;
}
}
v___jp_9227_:
{
uint32_t v___x_9232_; uint8_t v___x_9233_; 
v___x_9232_ = 0;
v___x_9233_ = lean_uint32_dec_eq(v_yExponent_9205_, v___x_9232_);
if (v___x_9233_ == 0)
{
uint64_t v___x_9234_; uint64_t v___x_9235_; uint64_t v___x_9236_; 
v___x_9234_ = lean_uint32_to_uint64(v___y_9230_);
v___x_9235_ = 8388608ULL;
v___x_9236_ = lean_uint64_lor(v___x_9234_, v___x_9235_);
v___y_9218_ = v___y_9228_;
v___y_9219_ = v___y_9229_;
v___y_9220_ = v___y_9231_;
v___y_9221_ = v___x_9236_;
goto v___jp_9217_;
}
else
{
uint64_t v___x_9237_; 
v___x_9237_ = lean_uint32_to_uint64(v___y_9230_);
v___y_9218_ = v___y_9228_;
v___y_9219_ = v___y_9229_;
v___y_9220_ = v___y_9231_;
v___y_9221_ = v___x_9237_;
goto v___jp_9217_;
}
}
v___jp_9238_:
{
uint32_t v___x_9240_; uint32_t v_xFraction_9241_; uint32_t v_yFraction_9242_; uint32_t v___x_9243_; uint8_t v___x_9244_; 
v___x_9240_ = 8388607;
v_xFraction_9241_ = lean_uint32_land(v_xBits_8926_, v___x_9240_);
v_yFraction_9242_ = lean_uint32_land(v_yBits_8927_, v___x_9240_);
v___x_9243_ = 0;
v___x_9244_ = lean_uint32_dec_eq(v_xExponent_9203_, v___x_9243_);
if (v___x_9244_ == 0)
{
uint64_t v___x_9245_; uint64_t v___x_9246_; uint64_t v___x_9247_; 
v___x_9245_ = lean_uint32_to_uint64(v_xFraction_9241_);
v___x_9246_ = 8388608ULL;
v___x_9247_ = lean_uint64_lor(v___x_9245_, v___x_9246_);
v___y_9228_ = v___y_9239_;
v___y_9229_ = v___x_9240_;
v___y_9230_ = v_yFraction_9242_;
v___y_9231_ = v___x_9247_;
goto v___jp_9227_;
}
else
{
uint64_t v___x_9248_; 
v___x_9248_ = lean_uint32_to_uint64(v_xFraction_9241_);
v___y_9228_ = v___y_9239_;
v___y_9229_ = v___x_9240_;
v___y_9230_ = v_yFraction_9242_;
v___y_9231_ = v___x_9248_;
goto v___jp_9227_;
}
}
v___jp_9249_:
{
uint8_t v___x_9250_; 
v___x_9250_ = 1;
v___y_9239_ = v___x_9250_;
goto v___jp_9238_;
}
v___jp_9251_:
{
uint8_t v___x_9252_; 
v___x_9252_ = 0;
v___y_9239_ = v___x_9252_;
goto v___jp_9238_;
}
v___jp_9253_:
{
if (v___y_9254_ == 0)
{
if (v___y_9255_ == 0)
{
goto v___jp_9251_;
}
else
{
goto v___jp_9249_;
}
}
else
{
if (v___y_9255_ == 0)
{
goto v___jp_9249_;
}
else
{
goto v___jp_9251_;
}
}
}
v___jp_9256_:
{
uint32_t v___x_9258_; uint32_t v___x_9259_; uint32_t v___x_9260_; uint8_t v___x_9261_; 
v___x_9258_ = 2147483648;
v___x_9259_ = lean_uint32_land(v_yBits_8927_, v___x_9258_);
v___x_9260_ = 0;
v___x_9261_ = lean_uint32_dec_eq(v___x_9259_, v___x_9260_);
if (v___x_9261_ == 0)
{
uint8_t v___x_9262_; 
v___x_9262_ = 1;
v___y_9254_ = v___y_9257_;
v___y_9255_ = v___x_9262_;
goto v___jp_9253_;
}
else
{
uint8_t v___x_9263_; 
v___x_9263_ = 0;
v___y_9254_ = v___y_9257_;
v___y_9255_ = v___x_9263_;
goto v___jp_9253_;
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_FastMul_core___boxed(lean_object* v_xBits_9270_, lean_object* v_yBits_9271_){
_start:
{
uint32_t v_xBits_boxed_9272_; uint32_t v_yBits_boxed_9273_; uint32_t v_res_9274_; lean_object* v_r_9275_; 
v_xBits_boxed_9272_ = lean_unbox_uint32(v_xBits_9270_);
lean_dec(v_xBits_9270_);
v_yBits_boxed_9273_ = lean_unbox_uint32(v_yBits_9271_);
lean_dec(v_yBits_9271_);
v_res_9274_ = lp_competition_Submission_FastMul_core(v_xBits_boxed_9272_, v_yBits_boxed_9273_);
v_r_9275_ = lean_box_uint32(v_res_9274_);
return v_r_9275_;
}
}
LEAN_EXPORT uint8_t lp_competition_Submission_FastMul_sm1(uint32_t v_a_9276_){
_start:
{
uint32_t v___x_9277_; uint32_t v___x_9278_; uint32_t v___x_9279_; uint8_t v___x_9280_; 
v___x_9277_ = 4278190080;
v___x_9278_ = 1;
v___x_9279_ = lean_uint32_shift_left(v_a_9276_, v___x_9278_);
v___x_9280_ = lean_uint32_dec_le(v___x_9277_, v___x_9279_);
return v___x_9280_;
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_FastMul_sm1___boxed(lean_object* v_a_9281_){
_start:
{
uint32_t v_a_boxed_9282_; uint8_t v_res_9283_; lean_object* v_r_9284_; 
v_a_boxed_9282_ = lean_unbox_uint32(v_a_9281_);
lean_dec(v_a_9281_);
v_res_9283_ = lp_competition_Submission_FastMul_sm1(v_a_boxed_9282_);
v_r_9284_ = lean_box(v_res_9283_);
return v_r_9284_;
}
}
LEAN_EXPORT uint8_t lp_competition_Submission_FastMul_special(uint32_t v_a_9285_, uint32_t v_b_9286_){
_start:
{
uint32_t v___x_9287_; uint32_t v___x_9288_; uint32_t v___x_9289_; uint8_t v___x_9290_; 
v___x_9287_ = 4278190080;
v___x_9288_ = 1;
v___x_9289_ = lean_uint32_shift_left(v_a_9285_, v___x_9288_);
v___x_9290_ = lean_uint32_dec_le(v___x_9287_, v___x_9289_);
if (v___x_9290_ == 0)
{
uint32_t v___x_9291_; uint8_t v___x_9292_; 
v___x_9291_ = lean_uint32_shift_left(v_b_9286_, v___x_9288_);
v___x_9292_ = lean_uint32_dec_le(v___x_9287_, v___x_9291_);
return v___x_9292_;
}
else
{
return v___x_9290_;
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_FastMul_special___boxed(lean_object* v_a_9293_, lean_object* v_b_9294_){
_start:
{
uint32_t v_a_boxed_9295_; uint32_t v_b_boxed_9296_; uint8_t v_res_9297_; lean_object* v_r_9298_; 
v_a_boxed_9295_ = lean_unbox_uint32(v_a_9293_);
lean_dec(v_a_9293_);
v_b_boxed_9296_ = lean_unbox_uint32(v_b_9294_);
lean_dec(v_b_9294_);
v_res_9297_ = lp_competition_Submission_FastMul_special(v_a_boxed_9295_, v_b_boxed_9296_);
v_r_9298_ = lean_box(v_res_9297_);
return v_r_9298_;
}
}
LEAN_EXPORT uint32_t lp_competition_Submission_FastMul_ofBits(uint32_t v_w_9299_){
_start:
{
return v_w_9299_;
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_FastMul_ofBits___boxed(lean_object* v_w_9300_){
_start:
{
uint32_t v_w_boxed_9301_; uint32_t v_res_9302_; lean_object* v_r_9303_; 
v_w_boxed_9301_ = lean_unbox_uint32(v_w_9300_);
lean_dec(v_w_9300_);
v_res_9302_ = lp_competition_Submission_FastMul_ofBits(v_w_boxed_9301_);
v_r_9303_ = lean_box_uint32(v_res_9302_);
return v_r_9303_;
}
}
LEAN_EXPORT uint32_t lp_competition_Submission_FastMul_mul(uint32_t v_x_9304_, uint32_t v_y_9305_){
_start:
{
uint32_t v___y_9307_; uint32_t v___y_9311_; uint32_t v___y_9312_; uint32_t v___y_9313_; uint32_t v___y_9317_; uint8_t v___y_9318_; uint64_t v___y_9319_; uint64_t v___y_9320_; uint32_t v___y_9332_; uint32_t v___y_9333_; uint32_t v___y_9334_; uint32_t v___y_9335_; uint32_t v___y_9336_; uint32_t v___y_9337_; uint32_t v___y_9344_; uint32_t v___y_9345_; uint8_t v___y_9346_; uint32_t v___y_9347_; uint32_t v___y_9348_; uint32_t v___y_9349_; uint32_t v___y_9353_; uint8_t v___y_9354_; uint64_t v___y_9355_; uint32_t v___y_9356_; uint32_t v___y_9357_; uint64_t v___y_9358_; uint64_t v___y_9359_; uint32_t v___y_9369_; uint8_t v___y_9370_; uint32_t v___y_9371_; uint64_t v___y_9372_; uint64_t v___y_9373_; uint8_t v___y_9374_; uint32_t v___y_9375_; uint64_t v___y_9376_; uint32_t v___y_9383_; uint8_t v___y_9384_; uint64_t v___y_9385_; uint32_t v___y_9386_; uint32_t v___y_9387_; uint64_t v___y_9388_; uint64_t v___y_9389_; uint32_t v___y_9395_; uint8_t v___y_9396_; uint64_t v___y_9397_; uint32_t v___y_9398_; uint64_t v___y_9399_; uint64_t v___y_9400_; uint32_t v___y_9401_; uint64_t v___y_9402_; uint64_t v___y_9457_; uint32_t v___y_9458_; uint8_t v___y_9459_; uint32_t v___y_9460_; uint64_t v___y_9461_; uint64_t v___y_9462_; uint64_t v___y_9463_; uint32_t v___y_9464_; uint64_t v___y_9465_; uint64_t v___y_9471_; uint32_t v___y_9472_; uint8_t v___y_9473_; uint64_t v___y_9474_; uint64_t v___y_9475_; uint32_t v___y_9476_; uint64_t v___y_9477_; uint64_t v___y_9478_; uint32_t v___y_9479_; uint64_t v___y_9480_; uint64_t v___y_9481_; uint64_t v___y_9486_; uint32_t v___y_9487_; uint8_t v___y_9488_; uint32_t v___y_9489_; uint64_t v___y_9490_; uint64_t v___y_9491_; uint64_t v___y_9492_; uint32_t v___y_9493_; uint64_t v___y_9494_; uint32_t v___y_9499_; uint8_t v___y_9500_; uint64_t v___y_9501_; uint64_t v___y_9502_; uint32_t v___y_9503_; uint64_t v___y_9504_; uint64_t v___y_9505_; uint64_t v___y_9506_; uint32_t v___y_9507_; uint64_t v___y_9508_; uint64_t v___y_9509_; uint32_t v___y_9514_; uint8_t v___y_9515_; uint32_t v___y_9516_; uint64_t v___y_9517_; uint64_t v___y_9518_; uint64_t v___y_9519_; uint64_t v___y_9520_; uint32_t v___y_9521_; uint64_t v___y_9522_; uint64_t v___y_9527_; uint32_t v___y_9528_; uint8_t v___y_9529_; uint64_t v___y_9530_; uint64_t v___y_9531_; uint64_t v___y_9532_; uint64_t v___y_9533_; uint32_t v___y_9534_; uint64_t v___y_9535_; uint32_t v___y_9536_; uint64_t v___y_9537_; uint32_t v___y_9542_; uint8_t v___y_9543_; uint64_t v___y_9544_; uint32_t v___y_9545_; uint64_t v___y_9546_; uint64_t v___y_9547_; uint64_t v___y_9548_; uint32_t v___y_9549_; uint64_t v___y_9550_; uint32_t v___y_9555_; uint64_t v___y_9556_; uint64_t v___y_9557_; uint8_t v___y_9558_; uint64_t v___y_9559_; uint64_t v___y_9560_; uint64_t v___y_9561_; uint32_t v___y_9562_; uint64_t v___y_9563_; uint32_t v___y_9564_; uint64_t v___y_9565_; uint32_t v___y_9570_; uint8_t v___y_9571_; uint64_t v___y_9572_; uint32_t v___y_9573_; uint64_t v___y_9574_; uint64_t v___y_9575_; uint64_t v___y_9576_; uint32_t v___y_9577_; uint64_t v___y_9578_; uint32_t v___y_9583_; uint8_t v___y_9584_; uint64_t v___y_9585_; uint64_t v___y_9586_; uint64_t v___y_9587_; uint32_t v___y_9588_; uint64_t v___y_9589_; uint32_t v___y_9590_; uint64_t v___y_9591_; uint64_t v___y_9595_; uint32_t v___y_9596_; uint8_t v___y_9597_; uint32_t v___y_9598_; uint64_t v___y_9599_; uint32_t v___y_9600_; uint64_t v___y_9601_; uint64_t v___y_9602_; uint32_t v___y_9613_; uint32_t v___y_9614_; uint8_t v___y_9615_; uint32_t v___y_9616_; uint64_t v___y_9617_; uint32_t v___y_9618_; uint64_t v___y_9619_; uint64_t v___y_9620_; uint32_t v___y_9627_; uint32_t v___y_9628_; uint8_t v___y_9629_; uint32_t v___y_9630_; uint32_t v___y_9631_; uint64_t v___y_9632_; uint32_t v___y_9633_; uint64_t v___y_9634_; uint32_t v___y_9641_; uint32_t v___y_9642_; uint8_t v___y_9643_; uint32_t v___y_9644_; uint32_t v___y_9645_; uint32_t v___y_9646_; uint32_t v___y_9647_; uint64_t v___y_9648_; uint32_t v___y_9656_; uint32_t v___y_9657_; uint32_t v___y_9658_; uint32_t v___y_9659_; uint8_t v___y_9660_; uint32_t v___y_9671_; uint32_t v___y_9672_; uint32_t v___y_9673_; uint32_t v___y_9674_; uint32_t v___y_9677_; uint8_t v___y_9678_; uint32_t v___y_9679_; uint32_t v___y_9680_; uint32_t v___y_9681_; uint8_t v___y_9682_; uint8_t v___y_9683_; uint32_t v___y_9685_; uint32_t v___y_9686_; uint32_t v___y_9687_; uint8_t v___y_9688_; uint32_t v___y_9689_; uint8_t v___y_9690_; uint8_t v___y_9697_; uint32_t v___x_9713_; uint32_t v___x_9714_; uint32_t v___x_9715_; uint8_t v___x_9716_; 
v___x_9713_ = 4278190080;
v___x_9714_ = 1;
v___x_9715_ = lean_uint32_shift_left(v_x_9304_, v___x_9714_);
v___x_9716_ = lean_uint32_dec_le(v___x_9713_, v___x_9715_);
if (v___x_9716_ == 0)
{
uint32_t v___x_9717_; uint8_t v___x_9718_; 
v___x_9717_ = lean_uint32_shift_left(v_y_9305_, v___x_9714_);
v___x_9718_ = lean_uint32_dec_le(v___x_9713_, v___x_9717_);
v___y_9697_ = v___x_9718_;
goto v___jp_9696_;
}
else
{
v___y_9697_ = v___x_9716_;
goto v___jp_9696_;
}
v___jp_9306_:
{
uint32_t v___x_9308_; uint32_t v___x_9309_; 
v___x_9308_ = 8388608;
v___x_9309_ = lean_uint32_lor(v___y_9307_, v___x_9308_);
return v___x_9309_;
}
v___jp_9310_:
{
uint32_t v___x_9314_; uint32_t v___x_9315_; 
v___x_9314_ = lean_uint32_land(v___y_9312_, v___y_9311_);
v___x_9315_ = lean_uint32_lor(v___y_9313_, v___x_9314_);
return v___x_9315_;
}
v___jp_9316_:
{
uint8_t v___x_9321_; 
v___x_9321_ = lean_uint64_dec_eq(v___y_9320_, v___y_9319_);
if (v___x_9321_ == 0)
{
uint64_t v___x_9322_; uint8_t v___x_9323_; 
v___x_9322_ = 8388608ULL;
v___x_9323_ = lean_uint64_dec_eq(v___y_9320_, v___x_9322_);
if (v___x_9323_ == 0)
{
uint32_t v___x_9324_; 
v___x_9324_ = lean_uint64_to_uint32(v___y_9320_);
if (v___y_9318_ == 0)
{
uint32_t v___x_9325_; 
v___x_9325_ = 0;
v___y_9311_ = v___y_9317_;
v___y_9312_ = v___x_9324_;
v___y_9313_ = v___x_9325_;
goto v___jp_9310_;
}
else
{
uint32_t v___x_9326_; 
v___x_9326_ = 2147483648;
v___y_9311_ = v___y_9317_;
v___y_9312_ = v___x_9324_;
v___y_9313_ = v___x_9326_;
goto v___jp_9310_;
}
}
else
{
if (v___y_9318_ == 0)
{
uint32_t v___x_9327_; 
v___x_9327_ = 0;
v___y_9307_ = v___x_9327_;
goto v___jp_9306_;
}
else
{
uint32_t v___x_9328_; 
v___x_9328_ = 2147483648;
v___y_9307_ = v___x_9328_;
goto v___jp_9306_;
}
}
}
else
{
if (v___y_9318_ == 0)
{
uint32_t v___x_9329_; 
v___x_9329_ = 0;
return v___x_9329_;
}
else
{
uint32_t v___x_9330_; 
v___x_9330_ = 2147483648;
return v___x_9330_;
}
}
}
v___jp_9331_:
{
uint32_t v___x_9338_; uint32_t v___x_9339_; uint32_t v___x_9340_; uint32_t v___x_9341_; uint32_t v___x_9342_; 
v___x_9338_ = lean_uint32_land(v___y_9333_, v___y_9335_);
v___x_9339_ = lean_uint32_shift_left(v___x_9338_, v___y_9336_);
v___x_9340_ = lean_uint32_lor(v___y_9337_, v___x_9339_);
v___x_9341_ = lean_uint32_land(v___y_9332_, v___y_9334_);
v___x_9342_ = lean_uint32_lor(v___x_9340_, v___x_9341_);
return v___x_9342_;
}
v___jp_9343_:
{
if (v___y_9346_ == 0)
{
uint32_t v___x_9350_; 
v___x_9350_ = 0;
v___y_9332_ = v___y_9349_;
v___y_9333_ = v___y_9344_;
v___y_9334_ = v___y_9345_;
v___y_9335_ = v___y_9347_;
v___y_9336_ = v___y_9348_;
v___y_9337_ = v___x_9350_;
goto v___jp_9331_;
}
else
{
uint32_t v___x_9351_; 
v___x_9351_ = 2147483648;
v___y_9332_ = v___y_9349_;
v___y_9333_ = v___y_9344_;
v___y_9334_ = v___y_9345_;
v___y_9335_ = v___y_9347_;
v___y_9336_ = v___y_9348_;
v___y_9337_ = v___x_9351_;
goto v___jp_9331_;
}
}
v___jp_9352_:
{
uint64_t v___x_9360_; uint64_t v_encodedExponent_9361_; uint32_t v___x_9362_; uint64_t v___x_9363_; uint8_t v___x_9364_; 
v___x_9360_ = 171ULL;
v_encodedExponent_9361_ = lean_uint64_sub(v___y_9358_, v___x_9360_);
v___x_9362_ = lean_uint64_to_uint32(v_encodedExponent_9361_);
v___x_9363_ = 8388608ULL;
v___x_9364_ = lean_uint64_dec_lt(v___y_9359_, v___x_9363_);
if (v___x_9364_ == 0)
{
uint64_t v___x_9365_; uint32_t v___x_9366_; 
v___x_9365_ = lean_uint64_sub(v___y_9359_, v___x_9363_);
v___x_9366_ = lean_uint64_to_uint32(v___x_9365_);
v___y_9344_ = v___x_9362_;
v___y_9345_ = v___y_9353_;
v___y_9346_ = v___y_9354_;
v___y_9347_ = v___y_9356_;
v___y_9348_ = v___y_9357_;
v___y_9349_ = v___x_9366_;
goto v___jp_9343_;
}
else
{
uint32_t v___x_9367_; 
v___x_9367_ = lean_uint64_to_uint32(v___y_9355_);
v___y_9344_ = v___x_9362_;
v___y_9345_ = v___y_9353_;
v___y_9346_ = v___y_9354_;
v___y_9347_ = v___y_9356_;
v___y_9348_ = v___y_9357_;
v___y_9349_ = v___x_9367_;
goto v___jp_9343_;
}
}
v___jp_9368_:
{
uint64_t v___x_9377_; uint8_t v___x_9378_; 
v___x_9377_ = 425ULL;
v___x_9378_ = lean_uint64_dec_lt(v___x_9377_, v___y_9376_);
if (v___x_9378_ == 0)
{
if (v___y_9374_ == 0)
{
v___y_9353_ = v___y_9369_;
v___y_9354_ = v___y_9370_;
v___y_9355_ = v___y_9372_;
v___y_9356_ = v___y_9371_;
v___y_9357_ = v___y_9375_;
v___y_9358_ = v___y_9376_;
v___y_9359_ = v___y_9373_;
goto v___jp_9352_;
}
else
{
uint64_t v___x_9379_; 
v___x_9379_ = 8388608ULL;
v___y_9353_ = v___y_9369_;
v___y_9354_ = v___y_9370_;
v___y_9355_ = v___y_9372_;
v___y_9356_ = v___y_9371_;
v___y_9357_ = v___y_9375_;
v___y_9358_ = v___y_9376_;
v___y_9359_ = v___x_9379_;
goto v___jp_9352_;
}
}
else
{
if (v___y_9370_ == 0)
{
uint32_t v___x_9380_; 
v___x_9380_ = 2139095040;
return v___x_9380_;
}
else
{
uint32_t v___x_9381_; 
v___x_9381_ = 4286578688;
return v___x_9381_;
}
}
}
v___jp_9382_:
{
uint64_t v___x_9390_; uint8_t v_carry_9391_; 
v___x_9390_ = 16777216ULL;
v_carry_9391_ = lean_uint64_dec_eq(v___y_9389_, v___x_9390_);
if (v_carry_9391_ == 0)
{
v___y_9369_ = v___y_9383_;
v___y_9370_ = v___y_9384_;
v___y_9371_ = v___y_9386_;
v___y_9372_ = v___y_9385_;
v___y_9373_ = v___y_9389_;
v___y_9374_ = v_carry_9391_;
v___y_9375_ = v___y_9387_;
v___y_9376_ = v___y_9388_;
goto v___jp_9368_;
}
else
{
uint64_t v___x_9392_; uint64_t v___x_9393_; 
v___x_9392_ = 1ULL;
v___x_9393_ = lean_uint64_add(v___y_9388_, v___x_9392_);
v___y_9369_ = v___y_9383_;
v___y_9370_ = v___y_9384_;
v___y_9371_ = v___y_9386_;
v___y_9372_ = v___y_9385_;
v___y_9373_ = v___y_9389_;
v___y_9374_ = v_carry_9391_;
v___y_9375_ = v___y_9387_;
v___y_9376_ = v___x_9393_;
goto v___jp_9368_;
}
}
v___jp_9394_:
{
uint64_t v_position_9403_; uint64_t v___x_9404_; uint8_t v___x_9405_; 
v_position_9403_ = lean_uint64_add(v___y_9402_, v___y_9400_);
v___x_9404_ = 172ULL;
v___x_9405_ = lean_uint64_dec_lt(v_position_9403_, v___x_9404_);
if (v___x_9405_ == 0)
{
uint64_t v___x_9406_; uint8_t v___x_9407_; 
v___x_9406_ = 23ULL;
v___x_9407_ = lean_uint64_dec_lt(v___y_9402_, v___x_9406_);
if (v___x_9407_ == 0)
{
uint64_t v___x_9408_; uint8_t v___x_9409_; 
v___x_9408_ = lean_uint64_sub(v___y_9402_, v___x_9406_);
v___x_9409_ = lean_uint64_dec_eq(v___x_9408_, v___y_9399_);
if (v___x_9409_ == 0)
{
uint64_t v___x_9410_; uint8_t v___x_9411_; 
v___x_9410_ = 64ULL;
v___x_9411_ = lean_uint64_dec_lt(v___x_9408_, v___x_9410_);
if (v___x_9411_ == 0)
{
uint8_t v___x_9412_; 
v___x_9412_ = lean_uint64_dec_eq(v___x_9408_, v___x_9410_);
if (v___x_9412_ == 0)
{
v___y_9383_ = v___y_9395_;
v___y_9384_ = v___y_9396_;
v___y_9385_ = v___y_9399_;
v___y_9386_ = v___y_9398_;
v___y_9387_ = v___y_9401_;
v___y_9388_ = v_position_9403_;
v___y_9389_ = v___y_9399_;
goto v___jp_9382_;
}
else
{
uint64_t v___x_9413_; uint8_t v___x_9414_; 
v___x_9413_ = 9223372036854775808ULL;
v___x_9414_ = lean_uint64_dec_lt(v___x_9413_, v___y_9397_);
if (v___x_9414_ == 0)
{
v___y_9383_ = v___y_9395_;
v___y_9384_ = v___y_9396_;
v___y_9385_ = v___y_9399_;
v___y_9386_ = v___y_9398_;
v___y_9387_ = v___y_9401_;
v___y_9388_ = v_position_9403_;
v___y_9389_ = v___y_9399_;
goto v___jp_9382_;
}
else
{
uint64_t v___x_9415_; 
v___x_9415_ = 1ULL;
v___y_9383_ = v___y_9395_;
v___y_9384_ = v___y_9396_;
v___y_9385_ = v___y_9399_;
v___y_9386_ = v___y_9398_;
v___y_9387_ = v___y_9401_;
v___y_9388_ = v_position_9403_;
v___y_9389_ = v___x_9415_;
goto v___jp_9382_;
}
}
}
else
{
uint64_t v_quotient_9416_; uint64_t v___x_9417_; uint64_t v___x_9418_; uint64_t v___x_9419_; uint64_t v_remainder_9420_; uint64_t v___x_9421_; uint64_t v_half_9422_; uint8_t v___x_9423_; 
v_quotient_9416_ = lean_uint64_shift_right(v___y_9397_, v___x_9408_);
v___x_9417_ = 1ULL;
v___x_9418_ = lean_uint64_shift_left(v___x_9417_, v___x_9408_);
v___x_9419_ = lean_uint64_sub(v___x_9418_, v___x_9417_);
v_remainder_9420_ = lean_uint64_land(v___y_9397_, v___x_9419_);
v___x_9421_ = lean_uint64_sub(v___x_9408_, v___x_9417_);
v_half_9422_ = lean_uint64_shift_left(v___x_9417_, v___x_9421_);
v___x_9423_ = lean_uint64_dec_lt(v_remainder_9420_, v_half_9422_);
if (v___x_9423_ == 0)
{
uint8_t v___x_9424_; 
v___x_9424_ = lean_uint64_dec_lt(v_half_9422_, v_remainder_9420_);
if (v___x_9424_ == 0)
{
uint64_t v___x_9425_; uint8_t v___x_9426_; 
v___x_9425_ = lean_uint64_land(v_quotient_9416_, v___x_9417_);
v___x_9426_ = lean_uint64_dec_eq(v___x_9425_, v___y_9399_);
if (v___x_9426_ == 0)
{
uint64_t v___x_9427_; 
v___x_9427_ = lean_uint64_add(v_quotient_9416_, v___x_9417_);
v___y_9383_ = v___y_9395_;
v___y_9384_ = v___y_9396_;
v___y_9385_ = v___y_9399_;
v___y_9386_ = v___y_9398_;
v___y_9387_ = v___y_9401_;
v___y_9388_ = v_position_9403_;
v___y_9389_ = v___x_9427_;
goto v___jp_9382_;
}
else
{
v___y_9383_ = v___y_9395_;
v___y_9384_ = v___y_9396_;
v___y_9385_ = v___y_9399_;
v___y_9386_ = v___y_9398_;
v___y_9387_ = v___y_9401_;
v___y_9388_ = v_position_9403_;
v___y_9389_ = v_quotient_9416_;
goto v___jp_9382_;
}
}
else
{
uint64_t v___x_9428_; 
v___x_9428_ = lean_uint64_add(v_quotient_9416_, v___x_9417_);
v___y_9383_ = v___y_9395_;
v___y_9384_ = v___y_9396_;
v___y_9385_ = v___y_9399_;
v___y_9386_ = v___y_9398_;
v___y_9387_ = v___y_9401_;
v___y_9388_ = v_position_9403_;
v___y_9389_ = v___x_9428_;
goto v___jp_9382_;
}
}
else
{
v___y_9383_ = v___y_9395_;
v___y_9384_ = v___y_9396_;
v___y_9385_ = v___y_9399_;
v___y_9386_ = v___y_9398_;
v___y_9387_ = v___y_9401_;
v___y_9388_ = v_position_9403_;
v___y_9389_ = v_quotient_9416_;
goto v___jp_9382_;
}
}
}
else
{
v___y_9383_ = v___y_9395_;
v___y_9384_ = v___y_9396_;
v___y_9385_ = v___y_9399_;
v___y_9386_ = v___y_9398_;
v___y_9387_ = v___y_9401_;
v___y_9388_ = v_position_9403_;
v___y_9389_ = v___y_9397_;
goto v___jp_9382_;
}
}
else
{
uint64_t v___x_9429_; uint64_t v___x_9430_; 
v___x_9429_ = lean_uint64_sub(v___x_9406_, v___y_9402_);
v___x_9430_ = lean_uint64_shift_left(v___y_9397_, v___x_9429_);
v___y_9383_ = v___y_9395_;
v___y_9384_ = v___y_9396_;
v___y_9385_ = v___y_9399_;
v___y_9386_ = v___y_9398_;
v___y_9387_ = v___y_9401_;
v___y_9388_ = v_position_9403_;
v___y_9389_ = v___x_9430_;
goto v___jp_9382_;
}
}
else
{
uint64_t v___x_9431_; uint8_t v___x_9432_; 
v___x_9431_ = 149ULL;
v___x_9432_ = lean_uint64_dec_lt(v___y_9400_, v___x_9431_);
if (v___x_9432_ == 0)
{
uint64_t v___x_9433_; uint64_t v___x_9434_; 
v___x_9433_ = lean_uint64_sub(v___y_9400_, v___x_9431_);
v___x_9434_ = lean_uint64_shift_left(v___y_9397_, v___x_9433_);
v___y_9317_ = v___y_9395_;
v___y_9318_ = v___y_9396_;
v___y_9319_ = v___y_9399_;
v___y_9320_ = v___x_9434_;
goto v___jp_9316_;
}
else
{
uint64_t v___x_9435_; uint8_t v___x_9436_; 
v___x_9435_ = lean_uint64_sub(v___x_9431_, v___y_9400_);
v___x_9436_ = lean_uint64_dec_eq(v___x_9435_, v___y_9399_);
if (v___x_9436_ == 0)
{
uint64_t v___x_9437_; uint8_t v___x_9438_; 
v___x_9437_ = 64ULL;
v___x_9438_ = lean_uint64_dec_lt(v___x_9435_, v___x_9437_);
if (v___x_9438_ == 0)
{
uint8_t v___x_9439_; 
v___x_9439_ = lean_uint64_dec_eq(v___x_9435_, v___x_9437_);
if (v___x_9439_ == 0)
{
v___y_9317_ = v___y_9395_;
v___y_9318_ = v___y_9396_;
v___y_9319_ = v___y_9399_;
v___y_9320_ = v___y_9399_;
goto v___jp_9316_;
}
else
{
uint64_t v___x_9440_; uint8_t v___x_9441_; 
v___x_9440_ = 9223372036854775808ULL;
v___x_9441_ = lean_uint64_dec_lt(v___x_9440_, v___y_9397_);
if (v___x_9441_ == 0)
{
v___y_9317_ = v___y_9395_;
v___y_9318_ = v___y_9396_;
v___y_9319_ = v___y_9399_;
v___y_9320_ = v___y_9399_;
goto v___jp_9316_;
}
else
{
uint64_t v___x_9442_; 
v___x_9442_ = 1ULL;
v___y_9317_ = v___y_9395_;
v___y_9318_ = v___y_9396_;
v___y_9319_ = v___y_9399_;
v___y_9320_ = v___x_9442_;
goto v___jp_9316_;
}
}
}
else
{
uint64_t v_quotient_9443_; uint64_t v___x_9444_; uint64_t v___x_9445_; uint64_t v___x_9446_; uint64_t v_remainder_9447_; uint64_t v___x_9448_; uint64_t v_half_9449_; uint8_t v___x_9450_; 
v_quotient_9443_ = lean_uint64_shift_right(v___y_9397_, v___x_9435_);
v___x_9444_ = 1ULL;
v___x_9445_ = lean_uint64_shift_left(v___x_9444_, v___x_9435_);
v___x_9446_ = lean_uint64_sub(v___x_9445_, v___x_9444_);
v_remainder_9447_ = lean_uint64_land(v___y_9397_, v___x_9446_);
v___x_9448_ = lean_uint64_sub(v___x_9435_, v___x_9444_);
v_half_9449_ = lean_uint64_shift_left(v___x_9444_, v___x_9448_);
v___x_9450_ = lean_uint64_dec_lt(v_remainder_9447_, v_half_9449_);
if (v___x_9450_ == 0)
{
uint8_t v___x_9451_; 
v___x_9451_ = lean_uint64_dec_lt(v_half_9449_, v_remainder_9447_);
if (v___x_9451_ == 0)
{
uint64_t v___x_9452_; uint8_t v___x_9453_; 
v___x_9452_ = lean_uint64_land(v_quotient_9443_, v___x_9444_);
v___x_9453_ = lean_uint64_dec_eq(v___x_9452_, v___y_9399_);
if (v___x_9453_ == 0)
{
uint64_t v___x_9454_; 
v___x_9454_ = lean_uint64_add(v_quotient_9443_, v___x_9444_);
v___y_9317_ = v___y_9395_;
v___y_9318_ = v___y_9396_;
v___y_9319_ = v___y_9399_;
v___y_9320_ = v___x_9454_;
goto v___jp_9316_;
}
else
{
v___y_9317_ = v___y_9395_;
v___y_9318_ = v___y_9396_;
v___y_9319_ = v___y_9399_;
v___y_9320_ = v_quotient_9443_;
goto v___jp_9316_;
}
}
else
{
uint64_t v___x_9455_; 
v___x_9455_ = lean_uint64_add(v_quotient_9443_, v___x_9444_);
v___y_9317_ = v___y_9395_;
v___y_9318_ = v___y_9396_;
v___y_9319_ = v___y_9399_;
v___y_9320_ = v___x_9455_;
goto v___jp_9316_;
}
}
else
{
v___y_9317_ = v___y_9395_;
v___y_9318_ = v___y_9396_;
v___y_9319_ = v___y_9399_;
v___y_9320_ = v_quotient_9443_;
goto v___jp_9316_;
}
}
}
else
{
v___y_9317_ = v___y_9395_;
v___y_9318_ = v___y_9396_;
v___y_9319_ = v___y_9399_;
v___y_9320_ = v___y_9397_;
goto v___jp_9316_;
}
}
}
}
v___jp_9456_:
{
uint64_t v___x_9466_; uint64_t v___x_9467_; uint8_t v___x_9468_; 
v___x_9466_ = 1ULL;
v___x_9467_ = lean_uint64_shift_right(v___y_9457_, v___x_9466_);
v___x_9468_ = lean_uint64_dec_eq(v___x_9467_, v___y_9462_);
if (v___x_9468_ == 0)
{
uint64_t v___x_9469_; 
v___x_9469_ = lean_uint64_add(v___y_9465_, v___x_9466_);
v___y_9395_ = v___y_9458_;
v___y_9396_ = v___y_9459_;
v___y_9397_ = v___y_9461_;
v___y_9398_ = v___y_9460_;
v___y_9399_ = v___y_9462_;
v___y_9400_ = v___y_9463_;
v___y_9401_ = v___y_9464_;
v___y_9402_ = v___x_9469_;
goto v___jp_9394_;
}
else
{
v___y_9395_ = v___y_9458_;
v___y_9396_ = v___y_9459_;
v___y_9397_ = v___y_9461_;
v___y_9398_ = v___y_9460_;
v___y_9399_ = v___y_9462_;
v___y_9400_ = v___y_9463_;
v___y_9401_ = v___y_9464_;
v___y_9402_ = v___y_9465_;
goto v___jp_9394_;
}
}
v___jp_9470_:
{
uint64_t v___x_9482_; uint8_t v___x_9483_; 
v___x_9482_ = lean_uint64_shift_right(v___y_9471_, v___y_9477_);
v___x_9483_ = lean_uint64_dec_eq(v___x_9482_, v___y_9474_);
if (v___x_9483_ == 0)
{
uint64_t v___x_9484_; 
v___x_9484_ = lean_uint64_add(v___y_9480_, v___y_9477_);
v___y_9457_ = v___y_9481_;
v___y_9458_ = v___y_9472_;
v___y_9459_ = v___y_9473_;
v___y_9460_ = v___y_9476_;
v___y_9461_ = v___y_9475_;
v___y_9462_ = v___y_9474_;
v___y_9463_ = v___y_9478_;
v___y_9464_ = v___y_9479_;
v___y_9465_ = v___x_9484_;
goto v___jp_9456_;
}
else
{
v___y_9457_ = v___y_9481_;
v___y_9458_ = v___y_9472_;
v___y_9459_ = v___y_9473_;
v___y_9460_ = v___y_9476_;
v___y_9461_ = v___y_9475_;
v___y_9462_ = v___y_9474_;
v___y_9463_ = v___y_9478_;
v___y_9464_ = v___y_9479_;
v___y_9465_ = v___y_9480_;
goto v___jp_9456_;
}
}
v___jp_9485_:
{
uint64_t v___x_9495_; uint64_t v___x_9496_; uint8_t v___x_9497_; 
v___x_9495_ = 2ULL;
v___x_9496_ = lean_uint64_shift_right(v___y_9486_, v___x_9495_);
v___x_9497_ = lean_uint64_dec_eq(v___x_9496_, v___y_9491_);
if (v___x_9497_ == 0)
{
v___y_9471_ = v___y_9486_;
v___y_9472_ = v___y_9487_;
v___y_9473_ = v___y_9488_;
v___y_9474_ = v___y_9491_;
v___y_9475_ = v___y_9490_;
v___y_9476_ = v___y_9489_;
v___y_9477_ = v___x_9495_;
v___y_9478_ = v___y_9492_;
v___y_9479_ = v___y_9493_;
v___y_9480_ = v___y_9494_;
v___y_9481_ = v___x_9496_;
goto v___jp_9470_;
}
else
{
v___y_9471_ = v___y_9486_;
v___y_9472_ = v___y_9487_;
v___y_9473_ = v___y_9488_;
v___y_9474_ = v___y_9491_;
v___y_9475_ = v___y_9490_;
v___y_9476_ = v___y_9489_;
v___y_9477_ = v___x_9495_;
v___y_9478_ = v___y_9492_;
v___y_9479_ = v___y_9493_;
v___y_9480_ = v___y_9494_;
v___y_9481_ = v___y_9486_;
goto v___jp_9470_;
}
}
v___jp_9498_:
{
uint64_t v___x_9510_; uint8_t v___x_9511_; 
v___x_9510_ = lean_uint64_shift_right(v___y_9506_, v___y_9505_);
v___x_9511_ = lean_uint64_dec_eq(v___x_9510_, v___y_9501_);
if (v___x_9511_ == 0)
{
uint64_t v___x_9512_; 
v___x_9512_ = lean_uint64_add(v___y_9508_, v___y_9505_);
v___y_9486_ = v___y_9509_;
v___y_9487_ = v___y_9499_;
v___y_9488_ = v___y_9500_;
v___y_9489_ = v___y_9503_;
v___y_9490_ = v___y_9502_;
v___y_9491_ = v___y_9501_;
v___y_9492_ = v___y_9504_;
v___y_9493_ = v___y_9507_;
v___y_9494_ = v___x_9512_;
goto v___jp_9485_;
}
else
{
v___y_9486_ = v___y_9509_;
v___y_9487_ = v___y_9499_;
v___y_9488_ = v___y_9500_;
v___y_9489_ = v___y_9503_;
v___y_9490_ = v___y_9502_;
v___y_9491_ = v___y_9501_;
v___y_9492_ = v___y_9504_;
v___y_9493_ = v___y_9507_;
v___y_9494_ = v___y_9508_;
goto v___jp_9485_;
}
}
v___jp_9513_:
{
uint64_t v___x_9523_; uint64_t v___x_9524_; uint8_t v___x_9525_; 
v___x_9523_ = 4ULL;
v___x_9524_ = lean_uint64_shift_right(v___y_9520_, v___x_9523_);
v___x_9525_ = lean_uint64_dec_eq(v___x_9524_, v___y_9518_);
if (v___x_9525_ == 0)
{
v___y_9499_ = v___y_9514_;
v___y_9500_ = v___y_9515_;
v___y_9501_ = v___y_9518_;
v___y_9502_ = v___y_9517_;
v___y_9503_ = v___y_9516_;
v___y_9504_ = v___y_9519_;
v___y_9505_ = v___x_9523_;
v___y_9506_ = v___y_9520_;
v___y_9507_ = v___y_9521_;
v___y_9508_ = v___y_9522_;
v___y_9509_ = v___x_9524_;
goto v___jp_9498_;
}
else
{
v___y_9499_ = v___y_9514_;
v___y_9500_ = v___y_9515_;
v___y_9501_ = v___y_9518_;
v___y_9502_ = v___y_9517_;
v___y_9503_ = v___y_9516_;
v___y_9504_ = v___y_9519_;
v___y_9505_ = v___x_9523_;
v___y_9506_ = v___y_9520_;
v___y_9507_ = v___y_9521_;
v___y_9508_ = v___y_9522_;
v___y_9509_ = v___y_9520_;
goto v___jp_9498_;
}
}
v___jp_9526_:
{
uint64_t v___x_9538_; uint8_t v___x_9539_; 
v___x_9538_ = lean_uint64_shift_right(v___y_9530_, v___y_9527_);
v___x_9539_ = lean_uint64_dec_eq(v___x_9538_, v___y_9532_);
if (v___x_9539_ == 0)
{
uint64_t v___x_9540_; 
v___x_9540_ = lean_uint64_add(v___y_9531_, v___y_9527_);
v___y_9514_ = v___y_9528_;
v___y_9515_ = v___y_9529_;
v___y_9516_ = v___y_9534_;
v___y_9517_ = v___y_9533_;
v___y_9518_ = v___y_9532_;
v___y_9519_ = v___y_9535_;
v___y_9520_ = v___y_9537_;
v___y_9521_ = v___y_9536_;
v___y_9522_ = v___x_9540_;
goto v___jp_9513_;
}
else
{
v___y_9514_ = v___y_9528_;
v___y_9515_ = v___y_9529_;
v___y_9516_ = v___y_9534_;
v___y_9517_ = v___y_9533_;
v___y_9518_ = v___y_9532_;
v___y_9519_ = v___y_9535_;
v___y_9520_ = v___y_9537_;
v___y_9521_ = v___y_9536_;
v___y_9522_ = v___y_9531_;
goto v___jp_9513_;
}
}
v___jp_9541_:
{
uint64_t v___x_9551_; uint64_t v___x_9552_; uint8_t v___x_9553_; 
v___x_9551_ = 8ULL;
v___x_9552_ = lean_uint64_shift_right(v___y_9544_, v___x_9551_);
v___x_9553_ = lean_uint64_dec_eq(v___x_9552_, v___y_9547_);
if (v___x_9553_ == 0)
{
v___y_9527_ = v___x_9551_;
v___y_9528_ = v___y_9542_;
v___y_9529_ = v___y_9543_;
v___y_9530_ = v___y_9544_;
v___y_9531_ = v___y_9550_;
v___y_9532_ = v___y_9547_;
v___y_9533_ = v___y_9546_;
v___y_9534_ = v___y_9545_;
v___y_9535_ = v___y_9548_;
v___y_9536_ = v___y_9549_;
v___y_9537_ = v___x_9552_;
goto v___jp_9526_;
}
else
{
v___y_9527_ = v___x_9551_;
v___y_9528_ = v___y_9542_;
v___y_9529_ = v___y_9543_;
v___y_9530_ = v___y_9544_;
v___y_9531_ = v___y_9550_;
v___y_9532_ = v___y_9547_;
v___y_9533_ = v___y_9546_;
v___y_9534_ = v___y_9545_;
v___y_9535_ = v___y_9548_;
v___y_9536_ = v___y_9549_;
v___y_9537_ = v___y_9544_;
goto v___jp_9526_;
}
}
v___jp_9554_:
{
uint64_t v___x_9566_; uint8_t v___x_9567_; 
v___x_9566_ = lean_uint64_shift_right(v___y_9559_, v___y_9557_);
v___x_9567_ = lean_uint64_dec_eq(v___x_9566_, v___y_9560_);
if (v___x_9567_ == 0)
{
uint64_t v___x_9568_; 
v___x_9568_ = lean_uint64_add(v___y_9556_, v___y_9557_);
v___y_9542_ = v___y_9555_;
v___y_9543_ = v___y_9558_;
v___y_9544_ = v___y_9565_;
v___y_9545_ = v___y_9562_;
v___y_9546_ = v___y_9561_;
v___y_9547_ = v___y_9560_;
v___y_9548_ = v___y_9563_;
v___y_9549_ = v___y_9564_;
v___y_9550_ = v___x_9568_;
goto v___jp_9541_;
}
else
{
v___y_9542_ = v___y_9555_;
v___y_9543_ = v___y_9558_;
v___y_9544_ = v___y_9565_;
v___y_9545_ = v___y_9562_;
v___y_9546_ = v___y_9561_;
v___y_9547_ = v___y_9560_;
v___y_9548_ = v___y_9563_;
v___y_9549_ = v___y_9564_;
v___y_9550_ = v___y_9556_;
goto v___jp_9541_;
}
}
v___jp_9569_:
{
uint64_t v___x_9579_; uint64_t v___x_9580_; uint8_t v___x_9581_; 
v___x_9579_ = 16ULL;
v___x_9580_ = lean_uint64_shift_right(v___y_9572_, v___x_9579_);
v___x_9581_ = lean_uint64_dec_eq(v___x_9580_, v___y_9575_);
if (v___x_9581_ == 0)
{
v___y_9555_ = v___y_9570_;
v___y_9556_ = v___y_9578_;
v___y_9557_ = v___x_9579_;
v___y_9558_ = v___y_9571_;
v___y_9559_ = v___y_9572_;
v___y_9560_ = v___y_9575_;
v___y_9561_ = v___y_9574_;
v___y_9562_ = v___y_9573_;
v___y_9563_ = v___y_9576_;
v___y_9564_ = v___y_9577_;
v___y_9565_ = v___x_9580_;
goto v___jp_9554_;
}
else
{
v___y_9555_ = v___y_9570_;
v___y_9556_ = v___y_9578_;
v___y_9557_ = v___x_9579_;
v___y_9558_ = v___y_9571_;
v___y_9559_ = v___y_9572_;
v___y_9560_ = v___y_9575_;
v___y_9561_ = v___y_9574_;
v___y_9562_ = v___y_9573_;
v___y_9563_ = v___y_9576_;
v___y_9564_ = v___y_9577_;
v___y_9565_ = v___y_9572_;
goto v___jp_9554_;
}
}
v___jp_9582_:
{
uint64_t v___x_9592_; uint8_t v___x_9593_; 
v___x_9592_ = lean_uint64_shift_right(v___y_9587_, v___y_9585_);
v___x_9593_ = lean_uint64_dec_eq(v___x_9592_, v___y_9586_);
if (v___x_9593_ == 0)
{
v___y_9570_ = v___y_9583_;
v___y_9571_ = v___y_9584_;
v___y_9572_ = v___y_9591_;
v___y_9573_ = v___y_9588_;
v___y_9574_ = v___y_9587_;
v___y_9575_ = v___y_9586_;
v___y_9576_ = v___y_9589_;
v___y_9577_ = v___y_9590_;
v___y_9578_ = v___y_9585_;
goto v___jp_9569_;
}
else
{
v___y_9570_ = v___y_9583_;
v___y_9571_ = v___y_9584_;
v___y_9572_ = v___y_9591_;
v___y_9573_ = v___y_9588_;
v___y_9574_ = v___y_9587_;
v___y_9575_ = v___y_9586_;
v___y_9576_ = v___y_9589_;
v___y_9577_ = v___y_9590_;
v___y_9578_ = v___y_9586_;
goto v___jp_9569_;
}
}
v___jp_9594_:
{
uint64_t v___x_9603_; uint64_t v___x_9604_; uint8_t v___x_9605_; 
v___x_9603_ = lean_uint64_mul(v___y_9599_, v___y_9601_);
v___x_9604_ = 0ULL;
v___x_9605_ = lean_uint64_dec_eq(v___x_9603_, v___x_9604_);
if (v___x_9605_ == 0)
{
uint64_t v___x_9606_; uint64_t v___x_9607_; uint64_t v___x_9608_; uint8_t v___x_9609_; 
v___x_9606_ = lean_uint64_add(v___y_9595_, v___y_9602_);
v___x_9607_ = 32ULL;
v___x_9608_ = lean_uint64_shift_right(v___x_9603_, v___x_9607_);
v___x_9609_ = lean_uint64_dec_eq(v___x_9608_, v___x_9604_);
if (v___x_9609_ == 0)
{
v___y_9583_ = v___y_9596_;
v___y_9584_ = v___y_9597_;
v___y_9585_ = v___x_9607_;
v___y_9586_ = v___x_9604_;
v___y_9587_ = v___x_9603_;
v___y_9588_ = v___y_9598_;
v___y_9589_ = v___x_9606_;
v___y_9590_ = v___y_9600_;
v___y_9591_ = v___x_9608_;
goto v___jp_9582_;
}
else
{
v___y_9583_ = v___y_9596_;
v___y_9584_ = v___y_9597_;
v___y_9585_ = v___x_9607_;
v___y_9586_ = v___x_9604_;
v___y_9587_ = v___x_9603_;
v___y_9588_ = v___y_9598_;
v___y_9589_ = v___x_9606_;
v___y_9590_ = v___y_9600_;
v___y_9591_ = v___x_9603_;
goto v___jp_9582_;
}
}
else
{
if (v___y_9597_ == 0)
{
uint32_t v___x_9610_; 
v___x_9610_ = 0;
return v___x_9610_;
}
else
{
uint32_t v___x_9611_; 
v___x_9611_ = 2147483648;
return v___x_9611_;
}
}
}
v___jp_9612_:
{
uint64_t v___x_9621_; uint64_t v___x_9622_; uint8_t v___x_9623_; 
v___x_9621_ = lean_uint32_to_uint64(v___y_9613_);
v___x_9622_ = 0ULL;
v___x_9623_ = lean_uint64_dec_eq(v___x_9621_, v___x_9622_);
if (v___x_9623_ == 0)
{
uint64_t v___x_9624_; uint64_t v___x_9625_; 
v___x_9624_ = 1ULL;
v___x_9625_ = lean_uint64_sub(v___x_9621_, v___x_9624_);
v___y_9595_ = v___y_9620_;
v___y_9596_ = v___y_9614_;
v___y_9597_ = v___y_9615_;
v___y_9598_ = v___y_9616_;
v___y_9599_ = v___y_9617_;
v___y_9600_ = v___y_9618_;
v___y_9601_ = v___y_9619_;
v___y_9602_ = v___x_9625_;
goto v___jp_9594_;
}
else
{
v___y_9595_ = v___y_9620_;
v___y_9596_ = v___y_9614_;
v___y_9597_ = v___y_9615_;
v___y_9598_ = v___y_9616_;
v___y_9599_ = v___y_9617_;
v___y_9600_ = v___y_9618_;
v___y_9601_ = v___y_9619_;
v___y_9602_ = v___x_9622_;
goto v___jp_9594_;
}
}
v___jp_9626_:
{
uint64_t v___x_9635_; uint64_t v___x_9636_; uint8_t v___x_9637_; 
v___x_9635_ = lean_uint32_to_uint64(v___y_9631_);
v___x_9636_ = 0ULL;
v___x_9637_ = lean_uint64_dec_eq(v___x_9635_, v___x_9636_);
if (v___x_9637_ == 0)
{
uint64_t v___x_9638_; uint64_t v___x_9639_; 
v___x_9638_ = 1ULL;
v___x_9639_ = lean_uint64_sub(v___x_9635_, v___x_9638_);
v___y_9613_ = v___y_9627_;
v___y_9614_ = v___y_9628_;
v___y_9615_ = v___y_9629_;
v___y_9616_ = v___y_9630_;
v___y_9617_ = v___y_9632_;
v___y_9618_ = v___y_9633_;
v___y_9619_ = v___y_9634_;
v___y_9620_ = v___x_9639_;
goto v___jp_9612_;
}
else
{
v___y_9613_ = v___y_9627_;
v___y_9614_ = v___y_9628_;
v___y_9615_ = v___y_9629_;
v___y_9616_ = v___y_9630_;
v___y_9617_ = v___y_9632_;
v___y_9618_ = v___y_9633_;
v___y_9619_ = v___y_9634_;
v___y_9620_ = v___x_9636_;
goto v___jp_9612_;
}
}
v___jp_9640_:
{
uint32_t v___x_9649_; uint8_t v___x_9650_; 
v___x_9649_ = 0;
v___x_9650_ = lean_uint32_dec_eq(v___y_9641_, v___x_9649_);
if (v___x_9650_ == 0)
{
uint64_t v___x_9651_; uint64_t v___x_9652_; uint64_t v___x_9653_; 
v___x_9651_ = lean_uint32_to_uint64(v___y_9646_);
v___x_9652_ = 8388608ULL;
v___x_9653_ = lean_uint64_lor(v___x_9651_, v___x_9652_);
v___y_9627_ = v___y_9641_;
v___y_9628_ = v___y_9642_;
v___y_9629_ = v___y_9643_;
v___y_9630_ = v___y_9644_;
v___y_9631_ = v___y_9645_;
v___y_9632_ = v___y_9648_;
v___y_9633_ = v___y_9647_;
v___y_9634_ = v___x_9653_;
goto v___jp_9626_;
}
else
{
uint64_t v___x_9654_; 
v___x_9654_ = lean_uint32_to_uint64(v___y_9646_);
v___y_9627_ = v___y_9641_;
v___y_9628_ = v___y_9642_;
v___y_9629_ = v___y_9643_;
v___y_9630_ = v___y_9644_;
v___y_9631_ = v___y_9645_;
v___y_9632_ = v___y_9648_;
v___y_9633_ = v___y_9647_;
v___y_9634_ = v___x_9654_;
goto v___jp_9626_;
}
}
v___jp_9655_:
{
uint32_t v___x_9661_; uint32_t v_xFraction_9662_; uint32_t v_yFraction_9663_; uint32_t v___x_9664_; uint8_t v___x_9665_; 
v___x_9661_ = 8388607;
v_xFraction_9662_ = lean_uint32_land(v_x_9304_, v___x_9661_);
v_yFraction_9663_ = lean_uint32_land(v_y_9305_, v___x_9661_);
v___x_9664_ = 0;
v___x_9665_ = lean_uint32_dec_eq(v___y_9658_, v___x_9664_);
if (v___x_9665_ == 0)
{
uint64_t v___x_9666_; uint64_t v___x_9667_; uint64_t v___x_9668_; 
v___x_9666_ = lean_uint32_to_uint64(v_xFraction_9662_);
v___x_9667_ = 8388608ULL;
v___x_9668_ = lean_uint64_lor(v___x_9666_, v___x_9667_);
v___y_9641_ = v___y_9656_;
v___y_9642_ = v___x_9661_;
v___y_9643_ = v___y_9660_;
v___y_9644_ = v___y_9657_;
v___y_9645_ = v___y_9658_;
v___y_9646_ = v_yFraction_9663_;
v___y_9647_ = v___y_9659_;
v___y_9648_ = v___x_9668_;
goto v___jp_9640_;
}
else
{
uint64_t v___x_9669_; 
v___x_9669_ = lean_uint32_to_uint64(v_xFraction_9662_);
v___y_9641_ = v___y_9656_;
v___y_9642_ = v___x_9661_;
v___y_9643_ = v___y_9660_;
v___y_9644_ = v___y_9657_;
v___y_9645_ = v___y_9658_;
v___y_9646_ = v_yFraction_9663_;
v___y_9647_ = v___y_9659_;
v___y_9648_ = v___x_9669_;
goto v___jp_9640_;
}
}
v___jp_9670_:
{
uint8_t v___x_9675_; 
v___x_9675_ = 1;
v___y_9656_ = v___y_9671_;
v___y_9657_ = v___y_9672_;
v___y_9658_ = v___y_9673_;
v___y_9659_ = v___y_9674_;
v___y_9660_ = v___x_9675_;
goto v___jp_9655_;
}
v___jp_9676_:
{
if (v___y_9678_ == 0)
{
if (v___y_9683_ == 0)
{
v___y_9656_ = v___y_9677_;
v___y_9657_ = v___y_9679_;
v___y_9658_ = v___y_9680_;
v___y_9659_ = v___y_9681_;
v___y_9660_ = v___y_9682_;
goto v___jp_9655_;
}
else
{
v___y_9671_ = v___y_9677_;
v___y_9672_ = v___y_9679_;
v___y_9673_ = v___y_9680_;
v___y_9674_ = v___y_9681_;
goto v___jp_9670_;
}
}
else
{
if (v___y_9683_ == 0)
{
v___y_9671_ = v___y_9677_;
v___y_9672_ = v___y_9679_;
v___y_9673_ = v___y_9680_;
v___y_9674_ = v___y_9681_;
goto v___jp_9670_;
}
else
{
v___y_9656_ = v___y_9677_;
v___y_9657_ = v___y_9679_;
v___y_9658_ = v___y_9680_;
v___y_9659_ = v___y_9681_;
v___y_9660_ = v___y_9682_;
goto v___jp_9655_;
}
}
}
v___jp_9684_:
{
uint32_t v___x_9691_; uint32_t v___x_9692_; uint32_t v___x_9693_; uint8_t v___x_9694_; 
v___x_9691_ = 2147483648;
v___x_9692_ = lean_uint32_land(v_y_9305_, v___x_9691_);
v___x_9693_ = 0;
v___x_9694_ = lean_uint32_dec_eq(v___x_9692_, v___x_9693_);
if (v___x_9694_ == 0)
{
uint8_t v___x_9695_; 
v___x_9695_ = 1;
v___y_9677_ = v___y_9685_;
v___y_9678_ = v___y_9690_;
v___y_9679_ = v___y_9686_;
v___y_9680_ = v___y_9687_;
v___y_9681_ = v___y_9689_;
v___y_9682_ = v___y_9688_;
v___y_9683_ = v___x_9695_;
goto v___jp_9676_;
}
else
{
v___y_9677_ = v___y_9685_;
v___y_9678_ = v___y_9690_;
v___y_9679_ = v___y_9686_;
v___y_9680_ = v___y_9687_;
v___y_9681_ = v___y_9689_;
v___y_9682_ = v___y_9688_;
v___y_9683_ = v___y_9688_;
goto v___jp_9676_;
}
}
v___jp_9696_:
{
if (v___y_9697_ == 0)
{
uint32_t v___x_9698_; uint32_t v___x_9699_; uint32_t v___x_9700_; uint32_t v_xExponent_9701_; uint32_t v___x_9702_; uint32_t v_yExponent_9703_; uint32_t v___x_9704_; uint32_t v___x_9705_; uint32_t v___x_9706_; uint8_t v___x_9707_; 
v___x_9698_ = 23;
v___x_9699_ = lean_uint32_shift_right(v_x_9304_, v___x_9698_);
v___x_9700_ = 255;
v_xExponent_9701_ = lean_uint32_land(v___x_9699_, v___x_9700_);
v___x_9702_ = lean_uint32_shift_right(v_y_9305_, v___x_9698_);
v_yExponent_9703_ = lean_uint32_land(v___x_9702_, v___x_9700_);
v___x_9704_ = 2147483648;
v___x_9705_ = lean_uint32_land(v_x_9304_, v___x_9704_);
v___x_9706_ = 0;
v___x_9707_ = lean_uint32_dec_eq(v___x_9705_, v___x_9706_);
if (v___x_9707_ == 0)
{
uint8_t v___x_9708_; 
v___x_9708_ = 1;
v___y_9685_ = v_yExponent_9703_;
v___y_9686_ = v___x_9700_;
v___y_9687_ = v_xExponent_9701_;
v___y_9688_ = v___y_9697_;
v___y_9689_ = v___x_9698_;
v___y_9690_ = v___x_9708_;
goto v___jp_9684_;
}
else
{
v___y_9685_ = v_yExponent_9703_;
v___y_9686_ = v___x_9700_;
v___y_9687_ = v_xExponent_9701_;
v___y_9688_ = v___y_9697_;
v___y_9689_ = v___x_9698_;
v___y_9690_ = v___y_9697_;
goto v___jp_9684_;
}
}
else
{
lean_object* v___x_9709_; lean_object* v___x_9710_; lean_object* v___x_9711_; uint32_t v___x_9712_; 
v___x_9709_ = lean_uint32_to_nat(v_x_9304_);
v___x_9710_ = lean_uint32_to_nat(v_y_9305_);
v___x_9711_ = lp_floatlib_FloatLib_Floats_Formats_BinaryInterchange_Model_MulBackend_word___at___00FloatLib_Floats_Formats_BinaryInterchange_Configured_Plan_softwareMul32Certified_spec__1(v___x_9709_, v___x_9710_);
v___x_9712_ = lean_uint32_of_nat(v___x_9711_);
lean_dec(v___x_9711_);
return v___x_9712_;
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_FastMul_mul___boxed(lean_object* v_x_9719_, lean_object* v_y_9720_){
_start:
{
uint32_t v_x_boxed_9721_; uint32_t v_y_boxed_9722_; uint32_t v_res_9723_; lean_object* v_r_9724_; 
v_x_boxed_9721_ = lean_unbox_uint32(v_x_9719_);
lean_dec(v_x_9719_);
v_y_boxed_9722_ = lean_unbox_uint32(v_y_9720_);
lean_dec(v_y_9720_);
v_res_9723_ = lp_competition_Submission_FastMul_mul(v_x_boxed_9721_, v_y_boxed_9722_);
v_r_9724_ = lean_box_uint32(v_res_9723_);
return v_r_9724_;
}
}
static uint8_t _init_lp_competition_Submission_FastMul_Plan(void){
_start:
{
uint8_t v___x_9726_; 
v___x_9726_ = 2;
return v___x_9726_;
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_FastMul_dec(uint32_t v_z_9727_){
_start:
{
lean_object* v___x_9728_; 
v___x_9728_ = lean_uint32_to_nat(v_z_9727_);
return v___x_9728_;
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_FastMul_dec___boxed(lean_object* v_z_9729_){
_start:
{
uint32_t v_z_boxed_9730_; lean_object* v_res_9731_; 
v_z_boxed_9730_ = lean_unbox_uint32(v_z_9729_);
lean_dec(v_z_9729_);
v_res_9731_ = lp_competition_Submission_FastMul_dec(v_z_boxed_9730_);
return v_res_9731_;
}
}
LEAN_EXPORT uint32_t lp_competition_Submission_add(uint32_t v_x_9732_, uint32_t v_y_9733_){
_start:
{
uint32_t v___x_9734_; 
v___x_9734_ = lp_competition_Submission_RebuiltAdd_add(v_x_9732_, v_y_9733_);
return v___x_9734_;
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_add___boxed(lean_object* v_x_9735_, lean_object* v_y_9736_){
_start:
{
uint32_t v_x_boxed_9737_; uint32_t v_y_boxed_9738_; uint32_t v_res_9739_; lean_object* v_r_9740_; 
v_x_boxed_9737_ = lean_unbox_uint32(v_x_9735_);
lean_dec(v_x_9735_);
v_y_boxed_9738_ = lean_unbox_uint32(v_y_9736_);
lean_dec(v_y_9736_);
v_res_9739_ = lp_competition_Submission_add(v_x_boxed_9737_, v_y_boxed_9738_);
v_r_9740_ = lean_box_uint32(v_res_9739_);
return v_r_9740_;
}
}
LEAN_EXPORT uint32_t lp_competition_Submission_mul(uint32_t v_x_9741_, uint32_t v_y_9742_){
_start:
{
uint32_t v___x_9743_; 
v___x_9743_ = lp_competition_Submission_FastMul_mul(v_x_9741_, v_y_9742_);
return v___x_9743_;
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_mul___boxed(lean_object* v_x_9744_, lean_object* v_y_9745_){
_start:
{
uint32_t v_x_boxed_9746_; uint32_t v_y_boxed_9747_; uint32_t v_res_9748_; lean_object* v_r_9749_; 
v_x_boxed_9746_ = lean_unbox_uint32(v_x_9744_);
lean_dec(v_x_9744_);
v_y_boxed_9747_ = lean_unbox_uint32(v_y_9745_);
lean_dec(v_y_9745_);
v_res_9748_ = lp_competition_Submission_mul(v_x_boxed_9746_, v_y_boxed_9747_);
v_r_9749_ = lean_box_uint32(v_res_9748_);
return v_r_9749_;
}
}
LEAN_EXPORT uint32_t lp_competition___private_Init_Data_Array_Basic_0__Array_foldlMUnsafe_fold___at___00Submission_sum_spec__0(lean_object* v_as_9750_, size_t v_i_9751_, size_t v_stop_9752_, uint32_t v_b_9753_){
_start:
{
uint8_t v___x_9754_; 
v___x_9754_ = lean_usize_dec_eq(v_i_9751_, v_stop_9752_);
if (v___x_9754_ == 0)
{
lean_object* v___x_9755_; uint32_t v___x_9756_; uint32_t v___x_9757_; size_t v___x_9758_; size_t v___x_9759_; 
v___x_9755_ = lean_array_uget_borrowed(v_as_9750_, v_i_9751_);
v___x_9756_ = lean_unbox_uint32(v___x_9755_);
v___x_9757_ = lp_competition_Submission_RebuiltAdd_add(v_b_9753_, v___x_9756_);
v___x_9758_ = ((size_t)1ULL);
v___x_9759_ = lean_usize_add(v_i_9751_, v___x_9758_);
v_i_9751_ = v___x_9759_;
v_b_9753_ = v___x_9757_;
goto _start;
}
else
{
return v_b_9753_;
}
}
}
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_foldlMUnsafe_fold___at___00Submission_sum_spec__0___boxed(lean_object* v_as_9761_, lean_object* v_i_9762_, lean_object* v_stop_9763_, lean_object* v_b_9764_){
_start:
{
size_t v_i_boxed_9765_; size_t v_stop_boxed_9766_; uint32_t v_b_boxed_9767_; uint32_t v_res_9768_; lean_object* v_r_9769_; 
v_i_boxed_9765_ = lean_unbox_usize(v_i_9762_);
lean_dec(v_i_9762_);
v_stop_boxed_9766_ = lean_unbox_usize(v_stop_9763_);
lean_dec(v_stop_9763_);
v_b_boxed_9767_ = lean_unbox_uint32(v_b_9764_);
lean_dec(v_b_9764_);
v_res_9768_ = lp_competition___private_Init_Data_Array_Basic_0__Array_foldlMUnsafe_fold___at___00Submission_sum_spec__0(v_as_9761_, v_i_boxed_9765_, v_stop_boxed_9766_, v_b_boxed_9767_);
lean_dec_ref(v_as_9761_);
v_r_9769_ = lean_box_uint32(v_res_9768_);
return v_r_9769_;
}
}
static lean_object* _init_lp_competition_Submission_sum___redArg___closed__0(void){
_start:
{
lean_object* v___x_9770_; lean_object* v___x_9771_; lean_object* v___x_9772_; 
v___x_9770_ = lean_unsigned_to_nat(0u);
v___x_9771_ = lean_unsigned_to_nat(32u);
v___x_9772_ = l_BitVec_ofNat(v___x_9771_, v___x_9770_);
return v___x_9772_;
}
}
static uint32_t _init_lp_competition_Submission_sum___redArg___closed__1(void){
_start:
{
lean_object* v___x_9773_; uint32_t v___x_9774_; 
v___x_9773_ = lean_obj_once(&lp_competition_Submission_sum___redArg___closed__0, &lp_competition_Submission_sum___redArg___closed__0_once, _init_lp_competition_Submission_sum___redArg___closed__0);
v___x_9774_ = lean_uint32_of_nat(v___x_9773_);
return v___x_9774_;
}
}
LEAN_EXPORT uint32_t lp_competition_Submission_sum___redArg(lean_object* v_x_9775_){
_start:
{
lean_object* v___x_9776_; uint32_t v___x_9777_; lean_object* v___x_9778_; uint8_t v___x_9779_; 
v___x_9776_ = lean_unsigned_to_nat(0u);
v___x_9777_ = lean_uint32_once(&lp_competition_Submission_sum___redArg___closed__1, &lp_competition_Submission_sum___redArg___closed__1_once, _init_lp_competition_Submission_sum___redArg___closed__1);
v___x_9778_ = lean_array_get_size(v_x_9775_);
v___x_9779_ = lean_nat_dec_lt(v___x_9776_, v___x_9778_);
if (v___x_9779_ == 0)
{
return v___x_9777_;
}
else
{
uint8_t v___x_9780_; 
v___x_9780_ = lean_nat_dec_le(v___x_9778_, v___x_9778_);
if (v___x_9780_ == 0)
{
if (v___x_9779_ == 0)
{
return v___x_9777_;
}
else
{
size_t v___x_9781_; size_t v___x_9782_; uint32_t v___x_9783_; 
v___x_9781_ = ((size_t)0ULL);
v___x_9782_ = lean_usize_of_nat(v___x_9778_);
v___x_9783_ = lp_competition___private_Init_Data_Array_Basic_0__Array_foldlMUnsafe_fold___at___00Submission_sum_spec__0(v_x_9775_, v___x_9781_, v___x_9782_, v___x_9777_);
return v___x_9783_;
}
}
else
{
size_t v___x_9784_; size_t v___x_9785_; uint32_t v___x_9786_; 
v___x_9784_ = ((size_t)0ULL);
v___x_9785_ = lean_usize_of_nat(v___x_9778_);
v___x_9786_ = lp_competition___private_Init_Data_Array_Basic_0__Array_foldlMUnsafe_fold___at___00Submission_sum_spec__0(v_x_9775_, v___x_9784_, v___x_9785_, v___x_9777_);
return v___x_9786_;
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_sum___redArg___boxed(lean_object* v_x_9787_){
_start:
{
uint32_t v_res_9788_; lean_object* v_r_9789_; 
v_res_9788_ = lp_competition_Submission_sum___redArg(v_x_9787_);
lean_dec_ref(v_x_9787_);
v_r_9789_ = lean_box_uint32(v_res_9788_);
return v_r_9789_;
}
}
LEAN_EXPORT uint32_t lp_competition_Submission_sum(lean_object* v_n_9790_, lean_object* v_x_9791_){
_start:
{
uint32_t v___x_9792_; 
v___x_9792_ = lp_competition_Submission_sum___redArg(v_x_9791_);
return v___x_9792_;
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_sum___boxed(lean_object* v_n_9793_, lean_object* v_x_9794_){
_start:
{
uint32_t v_res_9795_; lean_object* v_r_9796_; 
v_res_9795_ = lp_competition_Submission_sum(v_n_9793_, v_x_9794_);
lean_dec_ref(v_x_9794_);
lean_dec(v_n_9793_);
v_r_9796_ = lean_box_uint32(v_res_9795_);
return v_r_9796_;
}
}
LEAN_EXPORT uint32_t lp_competition_Fin_foldl_loop___at___00Submission_bmm_spec__0(lean_object* v_A_9797_, lean_object* v_fst_9798_, lean_object* v_m_9799_, lean_object* v_fst_9800_, lean_object* v_n_9801_, lean_object* v_B_9802_, lean_object* v_p_9803_, lean_object* v_snd_9804_, lean_object* v_n_9805_, uint32_t v_x_9806_, lean_object* v_i_9807_){
_start:
{
uint32_t v___y_9809_; uint32_t v___y_9810_; uint8_t v___x_9816_; 
v___x_9816_ = lean_nat_dec_lt(v_i_9807_, v_n_9805_);
if (v___x_9816_ == 0)
{
lean_dec(v_i_9807_);
return v_x_9806_;
}
else
{
lean_object* v___x_9817_; lean_object* v___x_9818_; lean_object* v___x_9819_; lean_object* v___x_9820_; uint32_t v___x_9821_; uint32_t v___y_9823_; lean_object* v___x_9832_; uint8_t v___x_9833_; 
v___x_9817_ = lean_nat_mul(v_fst_9798_, v_m_9799_);
v___x_9818_ = lean_nat_add(v___x_9817_, v_fst_9800_);
lean_dec(v___x_9817_);
v___x_9819_ = lean_nat_mul(v___x_9818_, v_n_9801_);
lean_dec(v___x_9818_);
v___x_9820_ = lean_nat_add(v___x_9819_, v_i_9807_);
lean_dec(v___x_9819_);
v___x_9821_ = lean_uint32_once(&lp_competition_Submission_sum___redArg___closed__1, &lp_competition_Submission_sum___redArg___closed__1_once, _init_lp_competition_Submission_sum___redArg___closed__1);
v___x_9832_ = lean_array_get_size(v_A_9797_);
v___x_9833_ = lean_nat_dec_lt(v___x_9820_, v___x_9832_);
if (v___x_9833_ == 0)
{
lean_dec(v___x_9820_);
v___y_9823_ = v___x_9821_;
goto v___jp_9822_;
}
else
{
lean_object* v___x_9834_; uint32_t v___x_9835_; 
v___x_9834_ = lean_array_fget_borrowed(v_A_9797_, v___x_9820_);
lean_dec(v___x_9820_);
v___x_9835_ = lean_unbox_uint32(v___x_9834_);
v___y_9823_ = v___x_9835_;
goto v___jp_9822_;
}
v___jp_9822_:
{
lean_object* v___x_9824_; lean_object* v___x_9825_; lean_object* v___x_9826_; lean_object* v___x_9827_; lean_object* v___x_9828_; uint8_t v___x_9829_; 
v___x_9824_ = lean_nat_mul(v_fst_9798_, v_n_9801_);
v___x_9825_ = lean_nat_add(v___x_9824_, v_i_9807_);
lean_dec(v___x_9824_);
v___x_9826_ = lean_nat_mul(v___x_9825_, v_p_9803_);
lean_dec(v___x_9825_);
v___x_9827_ = lean_nat_add(v___x_9826_, v_snd_9804_);
lean_dec(v___x_9826_);
v___x_9828_ = lean_array_get_size(v_B_9802_);
v___x_9829_ = lean_nat_dec_lt(v___x_9827_, v___x_9828_);
if (v___x_9829_ == 0)
{
lean_dec(v___x_9827_);
v___y_9809_ = v___y_9823_;
v___y_9810_ = v___x_9821_;
goto v___jp_9808_;
}
else
{
lean_object* v___x_9830_; uint32_t v___x_9831_; 
v___x_9830_ = lean_array_fget_borrowed(v_B_9802_, v___x_9827_);
lean_dec(v___x_9827_);
v___x_9831_ = lean_unbox_uint32(v___x_9830_);
v___y_9809_ = v___y_9823_;
v___y_9810_ = v___x_9831_;
goto v___jp_9808_;
}
}
}
v___jp_9808_:
{
uint32_t v___x_9811_; uint32_t v___x_9812_; lean_object* v___x_9813_; lean_object* v___x_9814_; 
v___x_9811_ = lp_competition_Submission_FastMul_mul(v___y_9809_, v___y_9810_);
v___x_9812_ = lp_competition_Submission_RebuiltAdd_add(v_x_9806_, v___x_9811_);
v___x_9813_ = lean_unsigned_to_nat(1u);
v___x_9814_ = lean_nat_add(v_i_9807_, v___x_9813_);
lean_dec(v_i_9807_);
v_x_9806_ = v___x_9812_;
v_i_9807_ = v___x_9814_;
goto _start;
}
}
}
LEAN_EXPORT lean_object* lp_competition_Fin_foldl_loop___at___00Submission_bmm_spec__0___boxed(lean_object* v_A_9836_, lean_object* v_fst_9837_, lean_object* v_m_9838_, lean_object* v_fst_9839_, lean_object* v_n_9840_, lean_object* v_B_9841_, lean_object* v_p_9842_, lean_object* v_snd_9843_, lean_object* v_n_9844_, lean_object* v_x_9845_, lean_object* v_i_9846_){
_start:
{
uint32_t v_x_boxed_9847_; uint32_t v_res_9848_; lean_object* v_r_9849_; 
v_x_boxed_9847_ = lean_unbox_uint32(v_x_9845_);
lean_dec(v_x_9845_);
v_res_9848_ = lp_competition_Fin_foldl_loop___at___00Submission_bmm_spec__0(v_A_9836_, v_fst_9837_, v_m_9838_, v_fst_9839_, v_n_9840_, v_B_9841_, v_p_9842_, v_snd_9843_, v_n_9844_, v_x_boxed_9847_, v_i_9846_);
lean_dec(v_n_9844_);
lean_dec(v_snd_9843_);
lean_dec(v_p_9842_);
lean_dec_ref(v_B_9841_);
lean_dec(v_n_9840_);
lean_dec(v_fst_9839_);
lean_dec(v_m_9838_);
lean_dec(v_fst_9837_);
lean_dec_ref(v_A_9836_);
v_r_9849_ = lean_box_uint32(v_res_9848_);
return v_r_9849_;
}
}
LEAN_EXPORT uint32_t lp_competition_Submission_bmm___lam__0(lean_object* v_m_9850_, lean_object* v_p_9851_, lean_object* v_A_9852_, lean_object* v_n_9853_, lean_object* v_B_9854_, lean_object* v_q_9855_){
_start:
{
lean_object* v___x_9856_; lean_object* v_snd_9857_; lean_object* v_fst_9858_; lean_object* v_fst_9859_; lean_object* v_snd_9860_; lean_object* v___x_9861_; uint32_t v___x_9862_; uint32_t v___x_9863_; 
v___x_9856_ = lp_competition_Competition_bmmDecodeC(v_m_9850_, v_p_9851_, v_q_9855_);
v_snd_9857_ = lean_ctor_get(v___x_9856_, 1);
lean_inc(v_snd_9857_);
v_fst_9858_ = lean_ctor_get(v___x_9856_, 0);
lean_inc(v_fst_9858_);
lean_dec_ref(v___x_9856_);
v_fst_9859_ = lean_ctor_get(v_snd_9857_, 0);
lean_inc(v_fst_9859_);
v_snd_9860_ = lean_ctor_get(v_snd_9857_, 1);
lean_inc(v_snd_9860_);
lean_dec(v_snd_9857_);
v___x_9861_ = lean_unsigned_to_nat(0u);
v___x_9862_ = lean_uint32_once(&lp_competition_Submission_sum___redArg___closed__1, &lp_competition_Submission_sum___redArg___closed__1_once, _init_lp_competition_Submission_sum___redArg___closed__1);
v___x_9863_ = lp_competition_Fin_foldl_loop___at___00Submission_bmm_spec__0(v_A_9852_, v_fst_9858_, v_m_9850_, v_fst_9859_, v_n_9853_, v_B_9854_, v_p_9851_, v_snd_9860_, v_n_9853_, v___x_9862_, v___x_9861_);
lean_dec(v_snd_9860_);
lean_dec(v_fst_9859_);
lean_dec(v_fst_9858_);
return v___x_9863_;
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_bmm___lam__0___boxed(lean_object* v_m_9864_, lean_object* v_p_9865_, lean_object* v_A_9866_, lean_object* v_n_9867_, lean_object* v_B_9868_, lean_object* v_q_9869_){
_start:
{
uint32_t v_res_9870_; lean_object* v_r_9871_; 
v_res_9870_ = lp_competition_Submission_bmm___lam__0(v_m_9864_, v_p_9865_, v_A_9866_, v_n_9867_, v_B_9868_, v_q_9869_);
lean_dec(v_q_9869_);
lean_dec_ref(v_B_9868_);
lean_dec(v_n_9867_);
lean_dec_ref(v_A_9866_);
lean_dec(v_p_9865_);
lean_dec(v_m_9864_);
v_r_9871_ = lean_box_uint32(v_res_9870_);
return v_r_9871_;
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_bmm(lean_object* v_batch_9872_, lean_object* v_m_9873_, lean_object* v_n_9874_, lean_object* v_p_9875_, lean_object* v_A_9876_, lean_object* v_B_9877_){
_start:
{
lean_object* v___f_9878_; lean_object* v___x_9879_; lean_object* v___x_9880_; lean_object* v___x_9881_; 
lean_inc(v_p_9875_);
lean_inc(v_m_9873_);
v___f_9878_ = lean_alloc_closure((void*)(lp_competition_Submission_bmm___lam__0___boxed), 6, 5);
lean_closure_set(v___f_9878_, 0, v_m_9873_);
lean_closure_set(v___f_9878_, 1, v_p_9875_);
lean_closure_set(v___f_9878_, 2, v_A_9876_);
lean_closure_set(v___f_9878_, 3, v_n_9874_);
lean_closure_set(v___f_9878_, 4, v_B_9877_);
v___x_9879_ = lean_nat_mul(v_batch_9872_, v_m_9873_);
lean_dec(v_m_9873_);
v___x_9880_ = lean_nat_mul(v___x_9879_, v_p_9875_);
lean_dec(v_p_9875_);
lean_dec(v___x_9879_);
v___x_9881_ = l_Array_ofFn___redArg(v___x_9880_, v___f_9878_);
return v___x_9881_;
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_bmm___boxed(lean_object* v_batch_9882_, lean_object* v_m_9883_, lean_object* v_n_9884_, lean_object* v_p_9885_, lean_object* v_A_9886_, lean_object* v_B_9887_){
_start:
{
lean_object* v_res_9888_; 
v_res_9888_ = lp_competition_Submission_bmm(v_batch_9882_, v_m_9883_, v_n_9884_, v_p_9885_, v_A_9886_, v_B_9887_);
lean_dec(v_batch_9882_);
return v_res_9888_;
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
