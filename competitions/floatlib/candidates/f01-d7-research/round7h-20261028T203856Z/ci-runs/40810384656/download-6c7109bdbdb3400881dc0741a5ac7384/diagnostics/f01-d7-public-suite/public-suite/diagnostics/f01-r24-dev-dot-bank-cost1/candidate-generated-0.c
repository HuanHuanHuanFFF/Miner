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
lean_object* lean_array_get_size(lean_object*);
uint8_t lean_nat_dec_lt(lean_object*, lean_object*);
lean_object* lean_mk_empty_float_array(lean_object*);
size_t lean_array_size(lean_object*);
size_t lean_usize_add(size_t, size_t);
uint8_t lean_usize_dec_lt(size_t, size_t);
double lean_float_of_bits(uint64_t);
lean_object* lean_float_array_push(lean_object*, double);
uint64_t lean_uint64_add(uint64_t, uint64_t);
uint64_t lean_uint64_shift_left(uint64_t, uint64_t);
uint64_t lean_uint64_lor(uint64_t, uint64_t);
uint64_t lean_uint64_sub(uint64_t, uint64_t);
uint64_t lean_uint64_shift_right(uint64_t, uint64_t);
uint8_t lean_uint64_dec_eq(uint64_t, uint64_t);
lean_object* lean_array_uget_borrowed(lean_object*, size_t);
uint32_t lean_uint32_shift_right(uint32_t, uint32_t);
uint32_t lean_uint32_land(uint32_t, uint32_t);
uint8_t lean_uint32_dec_eq(uint32_t, uint32_t);
uint64_t lean_uint32_to_uint64(uint32_t);
uint64_t lean_uint64_land(uint64_t, uint64_t);
uint8_t lean_uint32_dec_lt(uint32_t, uint32_t);
uint32_t lean_uint32_sub(uint32_t, uint32_t);
uint8_t lean_uint64_dec_lt(uint64_t, uint64_t);
uint64_t lean_uint64_xor(uint64_t, uint64_t);
double lean_float_sub(double, double);
uint64_t lean_float_to_bits(double);
double lean_float_add(double, double);
uint8_t lean_nat_dec_eq(lean_object*, lean_object*);
lean_object* lean_nat_sub(lean_object*, lean_object*);
lean_object* lean_nat_add(lean_object*, lean_object*);
double lean_float_array_get(lean_object*, lean_object*);
double lean_float_mul(double, double);
uint32_t lean_uint64_to_uint32(uint64_t);
uint32_t lean_uint32_lor(uint32_t, uint32_t);
uint8_t lean_nat_dec_le(lean_object*, lean_object*);
uint64_t lean_uint64_of_nat(lean_object*);
lean_object* lean_uint32_to_nat(uint32_t);
lean_object* lean_mk_empty_array_with_capacity(lean_object*);
lean_object* lean_array_push(lean_object*, lean_object*);
lean_object* lean_uint64_to_nat(uint64_t);
lean_object* l_BitVec_ofNat(lean_object*, lean_object*);
uint32_t lean_uint32_shift_left(uint32_t, uint32_t);
uint8_t lean_uint64_dec_le(uint64_t, uint64_t);
uint64_t lean_uint64_mul(uint64_t, uint64_t);
lean_object* lp_floatlib_FloatLib_Floats_Formats_BinaryInterchange_Model_MulBackend_word___at___00FloatLib_Floats_Formats_BinaryInterchange_Configured_Plan_softwareMul32Certified_spec__1(lean_object*, lean_object*);
uint32_t lean_uint32_of_nat(lean_object*);
uint8_t lean_uint32_dec_le(uint32_t, uint32_t);
size_t lean_usize_of_nat(lean_object*);
uint8_t lean_usize_dec_eq(size_t, size_t);
lean_object* lp_floatlib_FloatLib_Floats_Formats_BinaryInterchange_Model_AddBackend_word___at___00FloatLib_Floats_Formats_BinaryInterchange_Configured_Plan_softwareAdd32Certified_spec__1(lean_object*, lean_object*);
lean_object* lean_nat_to_int(lean_object*);
lean_object* lean_int_sub(lean_object*, lean_object*);
lean_object* lean_int_add(lean_object*, lean_object*);
uint8_t lean_int_dec_le(lean_object*, lean_object*);
lean_object* l_Int_toNat(lean_object*);
uint8_t lean_int_dec_lt(lean_object*, lean_object*);
lean_object* lean_int_neg(lean_object*);
lean_object* lean_array_get_borrowed(lean_object*, lean_object*, lean_object*);
uint32_t lean_uint32_add(uint32_t, uint32_t);
lean_object* lean_nat_abs(lean_object*);
lean_object* lean_nat_log2(lean_object*);
lean_object* lean_nat_shiftl(lean_object*, lean_object*);
lean_object* lean_nat_shiftr(lean_object*, lean_object*);
lean_object* lean_nat_mod(lean_object*, lean_object*);
uint8_t lean_int_dec_eq(lean_object*, lean_object*);
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
LEAN_EXPORT uint32_t lp_competition_Submission_R24ExactDotCost_rawExp(uint32_t);
LEAN_EXPORT lean_object* lp_competition_Submission_R24ExactDotCost_rawExp___boxed(lean_object*);
LEAN_EXPORT uint32_t lp_competition_Submission_R24ExactDotCost_rawFrac(uint32_t);
LEAN_EXPORT lean_object* lp_competition_Submission_R24ExactDotCost_rawFrac___boxed(lean_object*);
LEAN_EXPORT uint8_t lp_competition_Submission_R24ExactDotCost_neg(uint32_t);
LEAN_EXPORT lean_object* lp_competition_Submission_R24ExactDotCost_neg___boxed(lean_object*);
LEAN_EXPORT uint64_t lp_competition_Submission_R24ExactDotCost_rawMant(uint32_t);
LEAN_EXPORT lean_object* lp_competition_Submission_R24ExactDotCost_rawMant___boxed(lean_object*);
LEAN_EXPORT uint32_t lp_competition_Submission_R24ExactDotCost_rawIdx(uint32_t);
LEAN_EXPORT lean_object* lp_competition_Submission_R24ExactDotCost_rawIdx___boxed(lean_object*);
LEAN_EXPORT uint32_t lp_competition_Submission_R24ExactDotCost_idx(uint32_t);
LEAN_EXPORT lean_object* lp_competition_Submission_R24ExactDotCost_idx___boxed(lean_object*);
LEAN_EXPORT uint64_t lp_competition_Submission_R24ExactDotCost_mant(uint32_t);
LEAN_EXPORT lean_object* lp_competition_Submission_R24ExactDotCost_mant___boxed(lean_object*);
LEAN_EXPORT uint32_t lp_competition_Submission_R24ExactDotCost_encode(uint32_t);
LEAN_EXPORT lean_object* lp_competition_Submission_R24ExactDotCost_encode___boxed(lean_object*);
LEAN_EXPORT uint8_t lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00Submission_R24ExactDotCost_prepareOperand_spec__0___lam__0(uint32_t, uint32_t, uint8_t, uint8_t, lean_object*);
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00Submission_R24ExactDotCost_prepareOperand_spec__0___lam__0___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00Submission_R24ExactDotCost_prepareOperand_spec__0(lean_object*, size_t, size_t, lean_object*);
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00Submission_R24ExactDotCost_prepareOperand_spec__0___boxed(lean_object*, lean_object*, lean_object*, lean_object*);
static const lean_ctor_object lp_competition_Submission_R24ExactDotCost_prepareOperand___closed__0_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_ctor_object) + sizeof(void*)*2 + 0, .m_other = 2, .m_tag = 0}, .m_objs = {((lean_object*)(((size_t)(1) << 1) | 1)),((lean_object*)(((size_t)(0) << 1) | 1))}};
static const lean_object* lp_competition_Submission_R24ExactDotCost_prepareOperand___closed__0 = (const lean_object*)&lp_competition_Submission_R24ExactDotCost_prepareOperand___closed__0_value;
static const lean_ctor_object lp_competition_Submission_R24ExactDotCost_prepareOperand___closed__1_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_ctor_object) + sizeof(void*)*2 + 0, .m_other = 2, .m_tag = 0}, .m_objs = {((lean_object*)(((size_t)(1) << 1) | 1)),((lean_object*)&lp_competition_Submission_R24ExactDotCost_prepareOperand___closed__0_value)}};
static const lean_object* lp_competition_Submission_R24ExactDotCost_prepareOperand___closed__1 = (const lean_object*)&lp_competition_Submission_R24ExactDotCost_prepareOperand___closed__1_value;
LEAN_EXPORT lean_object* lp_competition_Submission_R24ExactDotCost_prepareOperand___closed__2___boxed__const__1;
static lean_once_cell_t lp_competition_Submission_R24ExactDotCost_prepareOperand___closed__2_once = LEAN_ONCE_CELL_INITIALIZER;
static lean_object* lp_competition_Submission_R24ExactDotCost_prepareOperand___closed__2;
LEAN_EXPORT lean_object* lp_competition_Submission_R24ExactDotCost_prepareOperand___closed__3___boxed__const__1;
static lean_once_cell_t lp_competition_Submission_R24ExactDotCost_prepareOperand___closed__3_once = LEAN_ONCE_CELL_INITIALIZER;
static lean_object* lp_competition_Submission_R24ExactDotCost_prepareOperand___closed__3;
LEAN_EXPORT lean_object* lp_competition_Submission_R24ExactDotCost_prepareOperand(lean_object*);
LEAN_EXPORT lean_object* lp_competition_Submission_R24ExactDotCost_pair(lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_Submission_R24ExactDotCost_prepare(lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_Submission_R24ExactDotCost_Cache_rawA(lean_object*);
LEAN_EXPORT lean_object* lp_competition_Submission_R24ExactDotCost_Cache_rawA___boxed(lean_object*);
LEAN_EXPORT lean_object* lp_competition_Submission_R24ExactDotCost_Cache_rawB(lean_object*);
LEAN_EXPORT lean_object* lp_competition_Submission_R24ExactDotCost_Cache_rawB___boxed(lean_object*);
LEAN_EXPORT lean_object* lp_competition_Submission_R24ExactDotCost_Cache_a(lean_object*);
LEAN_EXPORT lean_object* lp_competition_Submission_R24ExactDotCost_Cache_a___boxed(lean_object*);
LEAN_EXPORT lean_object* lp_competition_Submission_R24ExactDotCost_Cache_b(lean_object*);
LEAN_EXPORT lean_object* lp_competition_Submission_R24ExactDotCost_Cache_b___boxed(lean_object*);
LEAN_EXPORT uint8_t lp_competition_Submission_R24ExactDotCost_Cache_normal(lean_object*);
LEAN_EXPORT lean_object* lp_competition_Submission_R24ExactDotCost_Cache_normal___boxed(lean_object*);
LEAN_EXPORT uint8_t lp_competition_Submission_R24ExactDotCost_Cache_finite(lean_object*);
LEAN_EXPORT lean_object* lp_competition_Submission_R24ExactDotCost_Cache_finite___boxed(lean_object*);
LEAN_EXPORT lean_object* lp_competition_Submission_R24ExactDotCost_ceilLog2(lean_object*);
LEAN_EXPORT lean_object* lp_competition_Submission_R24ExactDotCost_ceilLog2___boxed(lean_object*);
LEAN_EXPORT uint8_t lp_competition_Submission_R24ExactDotCost_fastEligible(lean_object*);
LEAN_EXPORT lean_object* lp_competition_Submission_R24ExactDotCost_fastEligible___boxed(lean_object*);
LEAN_EXPORT uint32_t lp_competition_Submission_R24ExactDotCost_signWord(uint8_t);
LEAN_EXPORT lean_object* lp_competition_Submission_R24ExactDotCost_signWord___boxed(lean_object*);
LEAN_EXPORT uint32_t lp_competition_Submission_R24ExactDotCost_pack(uint8_t, uint32_t, uint32_t);
LEAN_EXPORT lean_object* lp_competition_Submission_R24ExactDotCost_pack___boxed(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT uint64_t lp_competition_Submission_R24ExactDotCost_quotientLo(uint64_t, uint64_t, uint64_t);
LEAN_EXPORT lean_object* lp_competition_Submission_R24ExactDotCost_quotientLo___boxed(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT uint64_t lp_competition_Submission_R24ExactDotCost_roundRight128(uint64_t, uint64_t, uint64_t);
LEAN_EXPORT lean_object* lp_competition_Submission_R24ExactDotCost_roundRight128___boxed(lean_object*, lean_object*, lean_object*);
static lean_once_cell_t lp_competition_Submission_R24ExactDotCost_round128___closed__0_once = LEAN_ONCE_CELL_INITIALIZER;
static lean_object* lp_competition_Submission_R24ExactDotCost_round128___closed__0;
static lean_once_cell_t lp_competition_Submission_R24ExactDotCost_round128___closed__1_once = LEAN_ONCE_CELL_INITIALIZER;
static lean_object* lp_competition_Submission_R24ExactDotCost_round128___closed__1;
static lean_once_cell_t lp_competition_Submission_R24ExactDotCost_round128___closed__2_once = LEAN_ONCE_CELL_INITIALIZER;
static lean_object* lp_competition_Submission_R24ExactDotCost_round128___closed__2;
static lean_once_cell_t lp_competition_Submission_R24ExactDotCost_round128___closed__3_once = LEAN_ONCE_CELL_INITIALIZER;
static lean_object* lp_competition_Submission_R24ExactDotCost_round128___closed__3;
static lean_once_cell_t lp_competition_Submission_R24ExactDotCost_round128___closed__4_once = LEAN_ONCE_CELL_INITIALIZER;
static lean_object* lp_competition_Submission_R24ExactDotCost_round128___closed__4;
static lean_once_cell_t lp_competition_Submission_R24ExactDotCost_round128___closed__5_once = LEAN_ONCE_CELL_INITIALIZER;
static lean_object* lp_competition_Submission_R24ExactDotCost_round128___closed__5;
static lean_once_cell_t lp_competition_Submission_R24ExactDotCost_round128___closed__6_once = LEAN_ONCE_CELL_INITIALIZER;
static lean_object* lp_competition_Submission_R24ExactDotCost_round128___closed__6;
static lean_once_cell_t lp_competition_Submission_R24ExactDotCost_round128___closed__7_once = LEAN_ONCE_CELL_INITIALIZER;
static lean_object* lp_competition_Submission_R24ExactDotCost_round128___closed__7;
static lean_once_cell_t lp_competition_Submission_R24ExactDotCost_round128___closed__8_once = LEAN_ONCE_CELL_INITIALIZER;
static lean_object* lp_competition_Submission_R24ExactDotCost_round128___closed__8;
LEAN_EXPORT uint32_t lp_competition_Submission_R24ExactDotCost_round128(uint8_t, uint64_t, uint64_t, lean_object*);
LEAN_EXPORT lean_object* lp_competition_Submission_R24ExactDotCost_round128___boxed(lean_object*, lean_object*, lean_object*, lean_object*);
static lean_once_cell_t lp_competition_Submission_R24ExactDotCost_finish___closed__0_once = LEAN_ONCE_CELL_INITIALIZER;
static lean_object* lp_competition_Submission_R24ExactDotCost_finish___closed__0;
LEAN_EXPORT uint32_t lp_competition_Submission_R24ExactDotCost_finish(uint32_t, uint8_t, uint64_t, uint64_t, uint64_t, uint64_t);
LEAN_EXPORT lean_object* lp_competition_Submission_R24ExactDotCost_finish___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT uint32_t lp_competition_Submission_R24ExactDotCost_nativeLoop(lean_object*, lean_object*, uint32_t, lean_object*, uint8_t, uint64_t, uint64_t, uint64_t, uint64_t, lean_object*);
LEAN_EXPORT lean_object* lp_competition_Submission_R24ExactDotCost_nativeLoop___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00__private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00Submission_R24ExactDotCost_referencePrepared_spec__0_spec__0___redArg(lean_object*, lean_object*, uint8_t, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00__private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00Submission_R24ExactDotCost_referencePrepared_spec__0_spec__0___redArg___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00Submission_R24ExactDotCost_referencePrepared_spec__0___redArg(lean_object*, lean_object*, uint8_t, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00Submission_R24ExactDotCost_referencePrepared_spec__0___redArg___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
static lean_once_cell_t lp_competition_Submission_R24ExactDotCost_referencePrepared___closed__0_once = LEAN_ONCE_CELL_INITIALIZER;
static lean_object* lp_competition_Submission_R24ExactDotCost_referencePrepared___closed__0;
static lean_once_cell_t lp_competition_Submission_R24ExactDotCost_referencePrepared___closed__1_once = LEAN_ONCE_CELL_INITIALIZER;
static lean_object* lp_competition_Submission_R24ExactDotCost_referencePrepared___closed__1;
LEAN_EXPORT uint32_t lp_competition_Submission_R24ExactDotCost_referencePrepared(lean_object*);
LEAN_EXPORT lean_object* lp_competition_Submission_R24ExactDotCost_referencePrepared___boxed(lean_object*);
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00Submission_R24ExactDotCost_referencePrepared_spec__0(lean_object*, lean_object*, uint8_t, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00Submission_R24ExactDotCost_referencePrepared_spec__0___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00__private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00Submission_R24ExactDotCost_referencePrepared_spec__0_spec__0(lean_object*, lean_object*, uint8_t, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00__private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00Submission_R24ExactDotCost_referencePrepared_spec__0_spec__0___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT uint32_t lp_competition_Submission_R24ExactDotCost_exactPrepared(lean_object*);
LEAN_EXPORT lean_object* lp_competition_Submission_R24ExactDotCost_exactPrepared___boxed(lean_object*);
LEAN_EXPORT uint32_t lp_competition_Submission_R24ExactDotCost_full(lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_Submission_R24ExactDotCost_full___boxed(lean_object*, lean_object*);
LEAN_EXPORT uint32_t lp_competition_Submission_R24ExactDotCost_prepared2(lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_Submission_R24ExactDotCost_prepared2___boxed(lean_object*, lean_object*);
LEAN_EXPORT uint8_t lp_competition_Submission_R24ExactDotTiered_eligible64(lean_object*);
LEAN_EXPORT lean_object* lp_competition_Submission_R24ExactDotTiered_eligible64___boxed(lean_object*);
LEAN_EXPORT uint32_t lp_competition_Submission_R24ExactDotTiered_finish64(uint32_t, uint8_t, uint64_t);
LEAN_EXPORT lean_object* lp_competition_Submission_R24ExactDotTiered_finish64___boxed(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT uint32_t lp_competition_Submission_R24ExactDotTiered_native64Loop(lean_object*, lean_object*, uint32_t, lean_object*, uint8_t, uint64_t, lean_object*);
LEAN_EXPORT lean_object* lp_competition_Submission_R24ExactDotTiered_native64Loop___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT uint32_t lp_competition_Submission_R24ExactDotTiered_exactPreparedV2(lean_object*);
LEAN_EXPORT lean_object* lp_competition_Submission_R24ExactDotTiered_exactPreparedV2___boxed(lean_object*);
LEAN_EXPORT uint32_t lp_competition_Submission_R24ExactDotTiered_fullv2(lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_Submission_R24ExactDotTiered_fullv2___boxed(lean_object*, lean_object*);
LEAN_EXPORT uint32_t lp_competition_Submission_R24ExactDotTiered_prepared2v2(lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_Submission_R24ExactDotTiered_prepared2v2___boxed(lean_object*, lean_object*);
LEAN_EXPORT uint32_t lp_competition_Submission_R24PortableF64_index32(uint32_t);
LEAN_EXPORT lean_object* lp_competition_Submission_R24PortableF64_index32___boxed(lean_object*);
LEAN_EXPORT uint64_t lp_competition_Submission_R24PortableF64_widenBits(uint32_t);
LEAN_EXPORT lean_object* lp_competition_Submission_R24PortableF64_widenBits___boxed(lean_object*);
static lean_once_cell_t lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00Submission_R24PortableF64_prepare_spec__0___closed__0_once = LEAN_ONCE_CELL_INITIALIZER;
static double lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00Submission_R24PortableF64_prepare_spec__0___closed__0;
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00Submission_R24PortableF64_prepare_spec__0(lean_object*, size_t, size_t, lean_object*);
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00Submission_R24PortableF64_prepare_spec__0___boxed(lean_object*, lean_object*, lean_object*, lean_object*);
static lean_once_cell_t lp_competition_Submission_R24PortableF64_prepare___closed__0_once = LEAN_ONCE_CELL_INITIALIZER;
static lean_object* lp_competition_Submission_R24PortableF64_prepare___closed__0;
static lean_once_cell_t lp_competition_Submission_R24PortableF64_prepare___closed__1_once = LEAN_ONCE_CELL_INITIALIZER;
static lean_object* lp_competition_Submission_R24PortableF64_prepare___closed__1;
LEAN_EXPORT lean_object* lp_competition_Submission_R24PortableF64_prepare(lean_object*);
LEAN_EXPORT uint64_t lp_competition_Submission_R24PortableF64_ceilLog2(lean_object*);
LEAN_EXPORT lean_object* lp_competition_Submission_R24PortableF64_ceilLog2___boxed(lean_object*);
LEAN_EXPORT uint8_t lp_competition_Submission_R24PortableF64_finite64(uint64_t);
LEAN_EXPORT lean_object* lp_competition_Submission_R24PortableF64_finite64___boxed(lean_object*);
LEAN_EXPORT uint32_t lp_competition_Submission_R24PortableF64_proposal(uint64_t);
LEAN_EXPORT lean_object* lp_competition_Submission_R24PortableF64_proposal___boxed(lean_object*);
LEAN_EXPORT uint64_t lp_competition_Submission_R24PortableF64_orderKey(uint64_t);
LEAN_EXPORT lean_object* lp_competition_Submission_R24PortableF64_orderKey___boxed(lean_object*);
LEAN_EXPORT uint8_t lp_competition_Submission_R24PortableF64_certify(double, double, uint64_t, uint32_t);
LEAN_EXPORT lean_object* lp_competition_Submission_R24PortableF64_certify___boxed(lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT double lp_competition_Submission_R24PortableF64_sumRemaining(lean_object*, lean_object*, lean_object*, double, lean_object*);
LEAN_EXPORT lean_object* lp_competition_Submission_R24PortableF64_sumRemaining___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT uint32_t lp_competition_Submission_R24PortableF64_attemptPrepared(lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_Submission_R24PortableF64_attemptPrepared___boxed(lean_object*, lean_object*);
LEAN_EXPORT uint32_t lp_competition_Submission_R24PortableF64_attemptCold(lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_Submission_R24PortableF64_attemptCold___boxed(lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_Submission_R24DotProbe_prepareEagerOperand(lean_object*);
LEAN_EXPORT uint32_t lp_competition_Submission_R24DotProbe_exactFull(lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_Submission_R24DotProbe_exactFull___boxed(lean_object*, lean_object*);
LEAN_EXPORT uint32_t lp_competition_Submission_R24DotProbe_exactPrepared(lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_Submission_R24DotProbe_exactPrepared___boxed(lean_object*, lean_object*);
LEAN_EXPORT uint32_t lp_competition_Submission_R24DotProbe_eagerPrepared(lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_Submission_R24DotProbe_eagerPrepared___boxed(lean_object*, lean_object*);
LEAN_EXPORT uint32_t lp_competition_Submission_R24DotProbe_eagerFull(lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_Submission_R24DotProbe_eagerFull___boxed(lean_object*, lean_object*);
LEAN_EXPORT uint32_t lp_competition_Submission_R24DotProbe_lazyPrepared(lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_Submission_R24DotProbe_lazyPrepared___boxed(lean_object*, lean_object*);
LEAN_EXPORT uint32_t lp_competition_Submission_R24DotProbe_lazyFull(lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_Submission_R24DotProbe_lazyFull___boxed(lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00Submission_R24GenericDotBank_exactBank_spec__1(lean_object*, lean_object*, size_t, size_t, lean_object*);
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00Submission_R24GenericDotBank_exactBank_spec__1___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00Submission_R24GenericDotBank_exactBank_spec__2(lean_object*, lean_object*, size_t, size_t, lean_object*);
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00Submission_R24GenericDotBank_exactBank_spec__2___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00Submission_R24GenericDotBank_exactBank_spec__0(lean_object*, size_t, size_t, lean_object*);
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00Submission_R24GenericDotBank_exactBank_spec__0___boxed(lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_Submission_R24GenericDotBank_exactBank(lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_Submission_R24GenericDotBank_exactBank___boxed(lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00Submission_R24GenericDotBank_eagerBank_spec__0(lean_object*, size_t, size_t, lean_object*);
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00Submission_R24GenericDotBank_eagerBank_spec__0___boxed(lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00Submission_R24GenericDotBank_eagerBank_spec__1(lean_object*, lean_object*, size_t, size_t, lean_object*);
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00Submission_R24GenericDotBank_eagerBank_spec__1___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00Submission_R24GenericDotBank_eagerBank_spec__2(lean_object*, lean_object*, size_t, size_t, lean_object*);
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00Submission_R24GenericDotBank_eagerBank_spec__2___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_Submission_R24GenericDotBank_eagerBank(lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_Submission_R24GenericDotBank_eagerBank___boxed(lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00Submission_R24GenericDotBank_lazyBank_spec__0(lean_object*, size_t, size_t, lean_object*);
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00Submission_R24GenericDotBank_lazyBank_spec__0___boxed(lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00Submission_R24GenericDotBank_lazyBank_spec__1(lean_object*, lean_object*, size_t, size_t, lean_object*);
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00Submission_R24GenericDotBank_lazyBank_spec__1___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00Submission_R24GenericDotBank_lazyBank_spec__2(lean_object*, lean_object*, size_t, size_t, lean_object*);
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00Submission_R24GenericDotBank_lazyBank_spec__2___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_Submission_R24GenericDotBank_lazyBank(lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_Submission_R24GenericDotBank_lazyBank___boxed(lean_object*, lean_object*);
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
LEAN_EXPORT uint32_t lp_competition_Fin_foldl_loop___at___00Submission_bmm_spec__0(lean_object* v_A_3249_, lean_object* v_fst_3250_, lean_object* v_m_3251_, lean_object* v_fst_3252_, lean_object* v_n_3253_, lean_object* v_B_3254_, lean_object* v_p_3255_, lean_object* v_snd_3256_, lean_object* v_n_3257_, uint32_t v_x_3258_, lean_object* v_i_3259_){
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
LEAN_EXPORT lean_object* lp_competition_Fin_foldl_loop___at___00Submission_bmm_spec__0___boxed(lean_object* v_A_3288_, lean_object* v_fst_3289_, lean_object* v_m_3290_, lean_object* v_fst_3291_, lean_object* v_n_3292_, lean_object* v_B_3293_, lean_object* v_p_3294_, lean_object* v_snd_3295_, lean_object* v_n_3296_, lean_object* v_x_3297_, lean_object* v_i_3298_){
_start:
{
uint32_t v_x_boxed_3299_; uint32_t v_res_3300_; lean_object* v_r_3301_; 
v_x_boxed_3299_ = lean_unbox_uint32(v_x_3297_);
lean_dec(v_x_3297_);
v_res_3300_ = lp_competition_Fin_foldl_loop___at___00Submission_bmm_spec__0(v_A_3288_, v_fst_3289_, v_m_3290_, v_fst_3291_, v_n_3292_, v_B_3293_, v_p_3294_, v_snd_3295_, v_n_3296_, v_x_boxed_3299_, v_i_3298_);
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
LEAN_EXPORT uint32_t lp_competition_Submission_bmm___lam__0(lean_object* v_m_3302_, lean_object* v_p_3303_, lean_object* v_A_3304_, lean_object* v_n_3305_, lean_object* v_B_3306_, lean_object* v_q_3307_){
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
v___x_3315_ = lp_competition_Fin_foldl_loop___at___00Submission_bmm_spec__0(v_A_3304_, v_fst_3310_, v_m_3302_, v_fst_3311_, v_n_3305_, v_B_3306_, v_p_3303_, v_snd_3312_, v_n_3305_, v___x_3314_, v___x_3313_);
lean_dec(v_snd_3312_);
lean_dec(v_fst_3311_);
lean_dec(v_fst_3310_);
return v___x_3315_;
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_bmm___lam__0___boxed(lean_object* v_m_3316_, lean_object* v_p_3317_, lean_object* v_A_3318_, lean_object* v_n_3319_, lean_object* v_B_3320_, lean_object* v_q_3321_){
_start:
{
uint32_t v_res_3322_; lean_object* v_r_3323_; 
v_res_3322_ = lp_competition_Submission_bmm___lam__0(v_m_3316_, v_p_3317_, v_A_3318_, v_n_3319_, v_B_3320_, v_q_3321_);
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
LEAN_EXPORT lean_object* lp_competition_Submission_bmm(lean_object* v_batch_3324_, lean_object* v_m_3325_, lean_object* v_n_3326_, lean_object* v_p_3327_, lean_object* v_A_3328_, lean_object* v_B_3329_){
_start:
{
lean_object* v___f_3330_; lean_object* v___x_3331_; lean_object* v___x_3332_; lean_object* v___x_3333_; 
lean_inc(v_p_3327_);
lean_inc(v_m_3325_);
v___f_3330_ = lean_alloc_closure((void*)(lp_competition_Submission_bmm___lam__0___boxed), 6, 5);
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
LEAN_EXPORT lean_object* lp_competition_Submission_bmm___boxed(lean_object* v_batch_3334_, lean_object* v_m_3335_, lean_object* v_n_3336_, lean_object* v_p_3337_, lean_object* v_A_3338_, lean_object* v_B_3339_){
_start:
{
lean_object* v_res_3340_; 
v_res_3340_ = lp_competition_Submission_bmm(v_batch_3334_, v_m_3335_, v_n_3336_, v_p_3337_, v_A_3338_, v_B_3339_);
lean_dec(v_batch_3334_);
return v_res_3340_;
}
}
LEAN_EXPORT uint32_t lp_competition_Submission_R24ExactDotCost_rawExp(uint32_t v_w_3341_){
_start:
{
uint32_t v___x_3342_; uint32_t v___x_3343_; uint32_t v___x_3344_; uint32_t v___x_3345_; 
v___x_3342_ = 23;
v___x_3343_ = lean_uint32_shift_right(v_w_3341_, v___x_3342_);
v___x_3344_ = 255;
v___x_3345_ = lean_uint32_land(v___x_3343_, v___x_3344_);
return v___x_3345_;
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_R24ExactDotCost_rawExp___boxed(lean_object* v_w_3346_){
_start:
{
uint32_t v_w_boxed_3347_; uint32_t v_res_3348_; lean_object* v_r_3349_; 
v_w_boxed_3347_ = lean_unbox_uint32(v_w_3346_);
lean_dec(v_w_3346_);
v_res_3348_ = lp_competition_Submission_R24ExactDotCost_rawExp(v_w_boxed_3347_);
v_r_3349_ = lean_box_uint32(v_res_3348_);
return v_r_3349_;
}
}
LEAN_EXPORT uint32_t lp_competition_Submission_R24ExactDotCost_rawFrac(uint32_t v_w_3350_){
_start:
{
uint32_t v___x_3351_; uint32_t v___x_3352_; 
v___x_3351_ = 8388607;
v___x_3352_ = lean_uint32_land(v_w_3350_, v___x_3351_);
return v___x_3352_;
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_R24ExactDotCost_rawFrac___boxed(lean_object* v_w_3353_){
_start:
{
uint32_t v_w_boxed_3354_; uint32_t v_res_3355_; lean_object* v_r_3356_; 
v_w_boxed_3354_ = lean_unbox_uint32(v_w_3353_);
lean_dec(v_w_3353_);
v_res_3355_ = lp_competition_Submission_R24ExactDotCost_rawFrac(v_w_boxed_3354_);
v_r_3356_ = lean_box_uint32(v_res_3355_);
return v_r_3356_;
}
}
LEAN_EXPORT uint8_t lp_competition_Submission_R24ExactDotCost_neg(uint32_t v_w_3357_){
_start:
{
uint32_t v___x_3358_; uint32_t v___x_3359_; uint32_t v___x_3360_; uint8_t v___x_3361_; 
v___x_3358_ = 2147483648;
v___x_3359_ = lean_uint32_land(v_w_3357_, v___x_3358_);
v___x_3360_ = 0;
v___x_3361_ = lean_uint32_dec_eq(v___x_3359_, v___x_3360_);
if (v___x_3361_ == 0)
{
uint8_t v___x_3362_; 
v___x_3362_ = 1;
return v___x_3362_;
}
else
{
uint8_t v___x_3363_; 
v___x_3363_ = 0;
return v___x_3363_;
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_R24ExactDotCost_neg___boxed(lean_object* v_w_3364_){
_start:
{
uint32_t v_w_boxed_3365_; uint8_t v_res_3366_; lean_object* v_r_3367_; 
v_w_boxed_3365_ = lean_unbox_uint32(v_w_3364_);
lean_dec(v_w_3364_);
v_res_3366_ = lp_competition_Submission_R24ExactDotCost_neg(v_w_boxed_3365_);
v_r_3367_ = lean_box(v_res_3366_);
return v_r_3367_;
}
}
LEAN_EXPORT uint64_t lp_competition_Submission_R24ExactDotCost_rawMant(uint32_t v_w_3368_){
_start:
{
uint32_t v___x_3369_; uint32_t v___x_3370_; uint32_t v___x_3371_; uint32_t v___x_3372_; uint32_t v___x_3373_; uint8_t v___x_3374_; 
v___x_3369_ = 23;
v___x_3370_ = lean_uint32_shift_right(v_w_3368_, v___x_3369_);
v___x_3371_ = 255;
v___x_3372_ = lean_uint32_land(v___x_3370_, v___x_3371_);
v___x_3373_ = 0;
v___x_3374_ = lean_uint32_dec_eq(v___x_3372_, v___x_3373_);
if (v___x_3374_ == 0)
{
uint32_t v___x_3375_; uint32_t v___x_3376_; uint32_t v___x_3377_; uint32_t v___x_3378_; uint64_t v___x_3379_; 
v___x_3375_ = 8388607;
v___x_3376_ = lean_uint32_land(v_w_3368_, v___x_3375_);
v___x_3377_ = 8388608;
v___x_3378_ = lean_uint32_lor(v___x_3376_, v___x_3377_);
v___x_3379_ = lean_uint32_to_uint64(v___x_3378_);
return v___x_3379_;
}
else
{
uint32_t v___x_3380_; uint32_t v___x_3381_; uint64_t v___x_3382_; 
v___x_3380_ = 8388607;
v___x_3381_ = lean_uint32_land(v_w_3368_, v___x_3380_);
v___x_3382_ = lean_uint32_to_uint64(v___x_3381_);
return v___x_3382_;
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_R24ExactDotCost_rawMant___boxed(lean_object* v_w_3383_){
_start:
{
uint32_t v_w_boxed_3384_; uint64_t v_res_3385_; lean_object* v_r_3386_; 
v_w_boxed_3384_ = lean_unbox_uint32(v_w_3383_);
lean_dec(v_w_3383_);
v_res_3385_ = lp_competition_Submission_R24ExactDotCost_rawMant(v_w_boxed_3384_);
v_r_3386_ = lean_box_uint64(v_res_3385_);
return v_r_3386_;
}
}
LEAN_EXPORT uint32_t lp_competition_Submission_R24ExactDotCost_rawIdx(uint32_t v_w_3387_){
_start:
{
uint32_t v___x_3388_; uint32_t v___x_3389_; uint32_t v___x_3390_; uint32_t v___x_3391_; uint32_t v___x_3392_; uint8_t v___x_3393_; 
v___x_3388_ = 23;
v___x_3389_ = lean_uint32_shift_right(v_w_3387_, v___x_3388_);
v___x_3390_ = 255;
v___x_3391_ = lean_uint32_land(v___x_3389_, v___x_3390_);
v___x_3392_ = 0;
v___x_3393_ = lean_uint32_dec_eq(v___x_3391_, v___x_3392_);
if (v___x_3393_ == 0)
{
uint32_t v___x_3394_; uint32_t v___x_3395_; 
v___x_3394_ = 1;
v___x_3395_ = lean_uint32_sub(v___x_3391_, v___x_3394_);
return v___x_3395_;
}
else
{
return v___x_3392_;
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_R24ExactDotCost_rawIdx___boxed(lean_object* v_w_3396_){
_start:
{
uint32_t v_w_boxed_3397_; uint32_t v_res_3398_; lean_object* v_r_3399_; 
v_w_boxed_3397_ = lean_unbox_uint32(v_w_3396_);
lean_dec(v_w_3396_);
v_res_3398_ = lp_competition_Submission_R24ExactDotCost_rawIdx(v_w_boxed_3397_);
v_r_3399_ = lean_box_uint32(v_res_3398_);
return v_r_3399_;
}
}
LEAN_EXPORT uint32_t lp_competition_Submission_R24ExactDotCost_idx(uint32_t v_w_3400_){
_start:
{
uint32_t v___x_3401_; uint32_t v___x_3402_; uint32_t v___x_3403_; uint32_t v___x_3404_; 
v___x_3401_ = 23;
v___x_3402_ = lean_uint32_shift_right(v_w_3400_, v___x_3401_);
v___x_3403_ = 255;
v___x_3404_ = lean_uint32_land(v___x_3402_, v___x_3403_);
return v___x_3404_;
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_R24ExactDotCost_idx___boxed(lean_object* v_w_3405_){
_start:
{
uint32_t v_w_boxed_3406_; uint32_t v_res_3407_; lean_object* v_r_3408_; 
v_w_boxed_3406_ = lean_unbox_uint32(v_w_3405_);
lean_dec(v_w_3405_);
v_res_3407_ = lp_competition_Submission_R24ExactDotCost_idx(v_w_boxed_3406_);
v_r_3408_ = lean_box_uint32(v_res_3407_);
return v_r_3408_;
}
}
LEAN_EXPORT uint64_t lp_competition_Submission_R24ExactDotCost_mant(uint32_t v_w_3409_){
_start:
{
uint32_t v___x_3410_; uint32_t v___x_3411_; uint32_t v___x_3412_; uint32_t v___x_3413_; uint32_t v___x_3414_; uint8_t v___x_3415_; 
v___x_3410_ = 23;
v___x_3411_ = lean_uint32_shift_right(v_w_3409_, v___x_3410_);
v___x_3412_ = 255;
v___x_3413_ = lean_uint32_land(v___x_3411_, v___x_3412_);
v___x_3414_ = 254;
v___x_3415_ = lean_uint32_dec_eq(v___x_3413_, v___x_3414_);
if (v___x_3415_ == 0)
{
uint32_t v___x_3416_; uint32_t v___x_3417_; uint32_t v___x_3418_; uint32_t v___x_3419_; uint64_t v___x_3420_; 
v___x_3416_ = 8388607;
v___x_3417_ = lean_uint32_land(v_w_3409_, v___x_3416_);
v___x_3418_ = 8388608;
v___x_3419_ = lean_uint32_lor(v___x_3417_, v___x_3418_);
v___x_3420_ = lean_uint32_to_uint64(v___x_3419_);
return v___x_3420_;
}
else
{
uint64_t v___x_3421_; 
v___x_3421_ = 0ULL;
return v___x_3421_;
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_R24ExactDotCost_mant___boxed(lean_object* v_w_3422_){
_start:
{
uint32_t v_w_boxed_3423_; uint64_t v_res_3424_; lean_object* v_r_3425_; 
v_w_boxed_3423_ = lean_unbox_uint32(v_w_3422_);
lean_dec(v_w_3422_);
v_res_3424_ = lp_competition_Submission_R24ExactDotCost_mant(v_w_boxed_3423_);
v_r_3425_ = lean_box_uint64(v_res_3424_);
return v_r_3425_;
}
}
LEAN_EXPORT uint32_t lp_competition_Submission_R24ExactDotCost_encode(uint32_t v_w_3426_){
_start:
{
uint64_t v___y_3428_; uint32_t v___x_3437_; uint32_t v___x_3438_; uint32_t v___x_3439_; uint32_t v___x_3440_; uint32_t v___x_3441_; uint8_t v___x_3442_; 
v___x_3437_ = 23;
v___x_3438_ = lean_uint32_shift_right(v_w_3426_, v___x_3437_);
v___x_3439_ = 255;
v___x_3440_ = lean_uint32_land(v___x_3438_, v___x_3439_);
v___x_3441_ = 0;
v___x_3442_ = lean_uint32_dec_eq(v___x_3440_, v___x_3441_);
if (v___x_3442_ == 0)
{
uint32_t v___x_3443_; uint32_t v___x_3444_; uint32_t v___x_3445_; uint32_t v___x_3446_; uint64_t v___x_3447_; 
v___x_3443_ = 8388607;
v___x_3444_ = lean_uint32_land(v_w_3426_, v___x_3443_);
v___x_3445_ = 8388608;
v___x_3446_ = lean_uint32_lor(v___x_3444_, v___x_3445_);
v___x_3447_ = lean_uint32_to_uint64(v___x_3446_);
v___y_3428_ = v___x_3447_;
goto v___jp_3427_;
}
else
{
uint32_t v___x_3448_; uint32_t v___x_3449_; uint64_t v___x_3450_; 
v___x_3448_ = 8388607;
v___x_3449_ = lean_uint32_land(v_w_3426_, v___x_3448_);
v___x_3450_ = lean_uint32_to_uint64(v___x_3449_);
v___y_3428_ = v___x_3450_;
goto v___jp_3427_;
}
v___jp_3427_:
{
uint64_t v___x_3429_; uint8_t v___x_3430_; 
v___x_3429_ = 0ULL;
v___x_3430_ = lean_uint64_dec_eq(v___y_3428_, v___x_3429_);
if (v___x_3430_ == 0)
{
uint32_t v___x_3431_; uint32_t v___x_3432_; 
v___x_3431_ = 8388608;
v___x_3432_ = lean_uint32_sub(v_w_3426_, v___x_3431_);
return v___x_3432_;
}
else
{
uint32_t v___x_3433_; uint32_t v___x_3434_; uint32_t v___x_3435_; uint32_t v___x_3436_; 
v___x_3433_ = 2147483648;
v___x_3434_ = lean_uint32_land(v_w_3426_, v___x_3433_);
v___x_3435_ = 2130706432;
v___x_3436_ = lean_uint32_lor(v___x_3434_, v___x_3435_);
return v___x_3436_;
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_R24ExactDotCost_encode___boxed(lean_object* v_w_3451_){
_start:
{
uint32_t v_w_boxed_3452_; uint32_t v_res_3453_; lean_object* v_r_3454_; 
v_w_boxed_3452_ = lean_unbox_uint32(v_w_3451_);
lean_dec(v_w_3451_);
v_res_3453_ = lp_competition_Submission_R24ExactDotCost_encode(v_w_boxed_3452_);
v_r_3454_ = lean_box_uint32(v_res_3453_);
return v_r_3454_;
}
}
LEAN_EXPORT uint8_t lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00Submission_R24ExactDotCost_prepareOperand_spec__0___lam__0(uint32_t v___x_3455_, uint32_t v_low_3456_, uint8_t v_normal_3457_, uint8_t v_seen_3458_, lean_object* v_00___3459_){
_start:
{
uint8_t v___x_3460_; 
v___x_3460_ = lean_uint32_dec_eq(v___x_3455_, v_low_3456_);
if (v___x_3460_ == 0)
{
return v_normal_3457_;
}
else
{
return v_seen_3458_;
}
}
}
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00Submission_R24ExactDotCost_prepareOperand_spec__0___lam__0___boxed(lean_object* v___x_3461_, lean_object* v_low_3462_, lean_object* v_normal_3463_, lean_object* v_seen_3464_, lean_object* v_00___3465_){
_start:
{
uint32_t v___x_1370__boxed_3466_; uint32_t v_low_boxed_3467_; uint8_t v_normal_boxed_3468_; uint8_t v_seen_boxed_3469_; uint8_t v_res_3470_; lean_object* v_r_3471_; 
v___x_1370__boxed_3466_ = lean_unbox_uint32(v___x_3461_);
lean_dec(v___x_3461_);
v_low_boxed_3467_ = lean_unbox_uint32(v_low_3462_);
lean_dec(v_low_3462_);
v_normal_boxed_3468_ = lean_unbox(v_normal_3463_);
v_seen_boxed_3469_ = lean_unbox(v_seen_3464_);
v_res_3470_ = lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00Submission_R24ExactDotCost_prepareOperand_spec__0___lam__0(v___x_1370__boxed_3466_, v_low_boxed_3467_, v_normal_boxed_3468_, v_seen_boxed_3469_, v_00___3465_);
v_r_3471_ = lean_box(v_res_3470_);
return v_r_3471_;
}
}
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00Submission_R24ExactDotCost_prepareOperand_spec__0(lean_object* v_as_3472_, size_t v_sz_3473_, size_t v_i_3474_, lean_object* v_b_3475_){
_start:
{
lean_object* v_a_3477_; uint8_t v_normal_3481_; uint8_t v___y_3483_; uint32_t v___y_3484_; lean_object* v___y_3485_; uint8_t v___y_3486_; uint32_t v___y_3487_; 
v_normal_3481_ = lean_usize_dec_lt(v_i_3474_, v_sz_3473_);
if (v_normal_3481_ == 0)
{
return v_b_3475_;
}
else
{
lean_object* v_snd_3498_; lean_object* v_snd_3499_; lean_object* v_fst_3500_; lean_object* v___x_3502_; uint8_t v_isShared_3503_; uint8_t v_isSharedCheck_3631_; 
v_snd_3498_ = lean_ctor_get(v_b_3475_, 1);
lean_inc(v_snd_3498_);
v_snd_3499_ = lean_ctor_get(v_snd_3498_, 1);
lean_inc(v_snd_3499_);
v_fst_3500_ = lean_ctor_get(v_b_3475_, 0);
v_isSharedCheck_3631_ = !lean_is_exclusive(v_b_3475_);
if (v_isSharedCheck_3631_ == 0)
{
lean_object* v_unused_3632_; 
v_unused_3632_ = lean_ctor_get(v_b_3475_, 1);
lean_dec(v_unused_3632_);
v___x_3502_ = v_b_3475_;
v_isShared_3503_ = v_isSharedCheck_3631_;
goto v_resetjp_3501_;
}
else
{
lean_inc(v_fst_3500_);
lean_dec(v_b_3475_);
v___x_3502_ = lean_box(0);
v_isShared_3503_ = v_isSharedCheck_3631_;
goto v_resetjp_3501_;
}
v_resetjp_3501_:
{
lean_object* v_fst_3504_; lean_object* v___x_3506_; uint8_t v_isShared_3507_; uint8_t v_isSharedCheck_3629_; 
v_fst_3504_ = lean_ctor_get(v_snd_3498_, 0);
v_isSharedCheck_3629_ = !lean_is_exclusive(v_snd_3498_);
if (v_isSharedCheck_3629_ == 0)
{
lean_object* v_unused_3630_; 
v_unused_3630_ = lean_ctor_get(v_snd_3498_, 1);
lean_dec(v_unused_3630_);
v___x_3506_ = v_snd_3498_;
v_isShared_3507_ = v_isSharedCheck_3629_;
goto v_resetjp_3505_;
}
else
{
lean_inc(v_fst_3504_);
lean_dec(v_snd_3498_);
v___x_3506_ = lean_box(0);
v_isShared_3507_ = v_isSharedCheck_3629_;
goto v_resetjp_3505_;
}
v_resetjp_3505_:
{
lean_object* v_fst_3508_; lean_object* v_snd_3509_; lean_object* v___x_3511_; uint8_t v_isShared_3512_; uint8_t v_isSharedCheck_3628_; 
v_fst_3508_ = lean_ctor_get(v_snd_3499_, 0);
v_snd_3509_ = lean_ctor_get(v_snd_3499_, 1);
v_isSharedCheck_3628_ = !lean_is_exclusive(v_snd_3499_);
if (v_isSharedCheck_3628_ == 0)
{
v___x_3511_ = v_snd_3499_;
v_isShared_3512_ = v_isSharedCheck_3628_;
goto v_resetjp_3510_;
}
else
{
lean_inc(v_snd_3509_);
lean_inc(v_fst_3508_);
lean_dec(v_snd_3499_);
v___x_3511_ = lean_box(0);
v_isShared_3512_ = v_isSharedCheck_3628_;
goto v_resetjp_3510_;
}
v_resetjp_3510_:
{
uint8_t v___y_3514_; lean_object* v___y_3515_; uint8_t v___y_3516_; uint32_t v___y_3517_; uint32_t v___y_3518_; uint8_t v___y_3523_; lean_object* v___y_3524_; uint8_t v___y_3525_; uint32_t v___y_3526_; lean_object* v_snd_3530_; lean_object* v_fst_3531_; lean_object* v___x_3533_; uint8_t v_isShared_3534_; uint8_t v_isSharedCheck_3627_; 
v_snd_3530_ = lean_ctor_get(v_snd_3509_, 1);
v_fst_3531_ = lean_ctor_get(v_snd_3509_, 0);
v_isSharedCheck_3627_ = !lean_is_exclusive(v_snd_3509_);
if (v_isSharedCheck_3627_ == 0)
{
v___x_3533_ = v_snd_3509_;
v_isShared_3534_ = v_isSharedCheck_3627_;
goto v_resetjp_3532_;
}
else
{
lean_inc(v_snd_3530_);
lean_inc(v_fst_3531_);
lean_dec(v_snd_3509_);
v___x_3533_ = lean_box(0);
v_isShared_3534_ = v_isSharedCheck_3627_;
goto v_resetjp_3532_;
}
v___jp_3513_:
{
uint32_t v___x_3519_; uint8_t v___x_3520_; 
v___x_3519_ = lean_unbox_uint32(v_fst_3508_);
v___x_3520_ = lean_uint32_dec_lt(v___x_3519_, v___y_3517_);
if (v___x_3520_ == 0)
{
uint32_t v___x_3521_; 
v___x_3521_ = lean_unbox_uint32(v_fst_3508_);
lean_dec(v_fst_3508_);
v___y_3483_ = v___y_3514_;
v___y_3484_ = v___y_3518_;
v___y_3485_ = v___y_3515_;
v___y_3486_ = v___y_3516_;
v___y_3487_ = v___x_3521_;
goto v___jp_3482_;
}
else
{
lean_dec(v_fst_3508_);
v___y_3483_ = v___y_3514_;
v___y_3484_ = v___y_3518_;
v___y_3485_ = v___y_3515_;
v___y_3486_ = v___y_3516_;
v___y_3487_ = v___y_3517_;
goto v___jp_3482_;
}
}
v___jp_3522_:
{
uint32_t v___x_3527_; uint8_t v___x_3528_; 
v___x_3527_ = lean_unbox_uint32(v_fst_3504_);
v___x_3528_ = lean_uint32_dec_lt(v___y_3526_, v___x_3527_);
if (v___x_3528_ == 0)
{
uint32_t v___x_3529_; 
v___x_3529_ = lean_unbox_uint32(v_fst_3504_);
lean_dec(v_fst_3504_);
v___y_3514_ = v___y_3523_;
v___y_3515_ = v___y_3524_;
v___y_3516_ = v___y_3525_;
v___y_3517_ = v___y_3526_;
v___y_3518_ = v___x_3529_;
goto v___jp_3513_;
}
else
{
lean_dec(v_fst_3504_);
v___y_3514_ = v___y_3523_;
v___y_3515_ = v___y_3524_;
v___y_3516_ = v___y_3525_;
v___y_3517_ = v___y_3526_;
v___y_3518_ = v___y_3526_;
goto v___jp_3513_;
}
}
v_resetjp_3532_:
{
lean_object* v_fst_3535_; lean_object* v_snd_3536_; lean_object* v___x_3538_; uint8_t v_isShared_3539_; uint8_t v_isSharedCheck_3626_; 
v_fst_3535_ = lean_ctor_get(v_snd_3530_, 0);
v_snd_3536_ = lean_ctor_get(v_snd_3530_, 1);
v_isSharedCheck_3626_ = !lean_is_exclusive(v_snd_3530_);
if (v_isSharedCheck_3626_ == 0)
{
v___x_3538_ = v_snd_3530_;
v_isShared_3539_ = v_isSharedCheck_3626_;
goto v_resetjp_3537_;
}
else
{
lean_inc(v_snd_3536_);
lean_inc(v_fst_3535_);
lean_dec(v_snd_3530_);
v___x_3538_ = lean_box(0);
v_isShared_3539_ = v_isSharedCheck_3626_;
goto v_resetjp_3537_;
}
v_resetjp_3537_:
{
uint8_t v___y_3541_; lean_object* v___y_3542_; uint8_t v___y_3543_; uint32_t v_low_3561_; uint8_t v_seen_3562_; uint32_t v_high_3563_; lean_object* v_a_3564_; uint32_t v___x_3565_; uint32_t v___x_3566_; uint32_t v___x_3567_; uint32_t v___x_3568_; uint8_t v___y_3570_; lean_object* v___y_3571_; uint8_t v___y_3572_; uint64_t v___y_3573_; uint32_t v___x_3579_; uint32_t v___x_3580_; uint32_t v___x_3581_; uint8_t v___y_3583_; uint8_t v___y_3584_; uint32_t v___y_3585_; uint8_t v___y_3595_; uint8_t v___y_3596_; uint64_t v___y_3597_; uint8_t v___y_3609_; uint8_t v___y_3610_; uint8_t v___y_3617_; uint8_t v___x_3623_; 
v_low_3561_ = 255;
v_seen_3562_ = 0;
v_high_3563_ = 0;
v_a_3564_ = lean_array_uget_borrowed(v_as_3472_, v_i_3474_);
v___x_3565_ = 23;
v___x_3566_ = lean_unbox_uint32(v_a_3564_);
v___x_3567_ = lean_uint32_shift_right(v___x_3566_, v___x_3565_);
v___x_3568_ = lean_uint32_land(v___x_3567_, v_low_3561_);
v___x_3579_ = 8388607;
v___x_3580_ = lean_unbox_uint32(v_a_3564_);
v___x_3581_ = lean_uint32_land(v___x_3580_, v___x_3579_);
v___x_3623_ = lean_unbox(v_fst_3535_);
lean_dec(v_fst_3535_);
if (v___x_3623_ == 0)
{
v___y_3617_ = v_seen_3562_;
goto v___jp_3616_;
}
else
{
lean_object* v___x_3624_; uint8_t v___x_3625_; 
v___x_3624_ = lean_box(0);
v___x_3625_ = lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00Submission_R24ExactDotCost_prepareOperand_spec__0___lam__0(v___x_3568_, v_low_3561_, v_normal_3481_, v_seen_3562_, v___x_3624_);
v___y_3617_ = v___x_3625_;
goto v___jp_3616_;
}
v___jp_3540_:
{
lean_object* v___x_3544_; lean_object* v___x_3546_; 
v___x_3544_ = lean_box(v___y_3543_);
if (v_isShared_3539_ == 0)
{
lean_ctor_set(v___x_3538_, 0, v___x_3544_);
v___x_3546_ = v___x_3538_;
goto v_reusejp_3545_;
}
else
{
lean_object* v_reuseFailAlloc_3560_; 
v_reuseFailAlloc_3560_ = lean_alloc_ctor(0, 2, 0);
lean_ctor_set(v_reuseFailAlloc_3560_, 0, v___x_3544_);
lean_ctor_set(v_reuseFailAlloc_3560_, 1, v_snd_3536_);
v___x_3546_ = v_reuseFailAlloc_3560_;
goto v_reusejp_3545_;
}
v_reusejp_3545_:
{
lean_object* v___x_3547_; lean_object* v___x_3549_; 
v___x_3547_ = lean_box(v___y_3541_);
if (v_isShared_3534_ == 0)
{
lean_ctor_set(v___x_3533_, 1, v___x_3546_);
lean_ctor_set(v___x_3533_, 0, v___x_3547_);
v___x_3549_ = v___x_3533_;
goto v_reusejp_3548_;
}
else
{
lean_object* v_reuseFailAlloc_3559_; 
v_reuseFailAlloc_3559_ = lean_alloc_ctor(0, 2, 0);
lean_ctor_set(v_reuseFailAlloc_3559_, 0, v___x_3547_);
lean_ctor_set(v_reuseFailAlloc_3559_, 1, v___x_3546_);
v___x_3549_ = v_reuseFailAlloc_3559_;
goto v_reusejp_3548_;
}
v_reusejp_3548_:
{
lean_object* v___x_3551_; 
if (v_isShared_3512_ == 0)
{
lean_ctor_set(v___x_3511_, 1, v___x_3549_);
v___x_3551_ = v___x_3511_;
goto v_reusejp_3550_;
}
else
{
lean_object* v_reuseFailAlloc_3558_; 
v_reuseFailAlloc_3558_ = lean_alloc_ctor(0, 2, 0);
lean_ctor_set(v_reuseFailAlloc_3558_, 0, v_fst_3508_);
lean_ctor_set(v_reuseFailAlloc_3558_, 1, v___x_3549_);
v___x_3551_ = v_reuseFailAlloc_3558_;
goto v_reusejp_3550_;
}
v_reusejp_3550_:
{
lean_object* v___x_3553_; 
if (v_isShared_3507_ == 0)
{
lean_ctor_set(v___x_3506_, 1, v___x_3551_);
v___x_3553_ = v___x_3506_;
goto v_reusejp_3552_;
}
else
{
lean_object* v_reuseFailAlloc_3557_; 
v_reuseFailAlloc_3557_ = lean_alloc_ctor(0, 2, 0);
lean_ctor_set(v_reuseFailAlloc_3557_, 0, v_fst_3504_);
lean_ctor_set(v_reuseFailAlloc_3557_, 1, v___x_3551_);
v___x_3553_ = v_reuseFailAlloc_3557_;
goto v_reusejp_3552_;
}
v_reusejp_3552_:
{
lean_object* v___x_3555_; 
if (v_isShared_3503_ == 0)
{
lean_ctor_set(v___x_3502_, 1, v___x_3553_);
lean_ctor_set(v___x_3502_, 0, v___y_3542_);
v___x_3555_ = v___x_3502_;
goto v_reusejp_3554_;
}
else
{
lean_object* v_reuseFailAlloc_3556_; 
v_reuseFailAlloc_3556_ = lean_alloc_ctor(0, 2, 0);
lean_ctor_set(v_reuseFailAlloc_3556_, 0, v___y_3542_);
lean_ctor_set(v_reuseFailAlloc_3556_, 1, v___x_3553_);
v___x_3555_ = v_reuseFailAlloc_3556_;
goto v_reusejp_3554_;
}
v_reusejp_3554_:
{
v_a_3477_ = v___x_3555_;
goto v___jp_3476_;
}
}
}
}
}
}
v___jp_3569_:
{
uint64_t v___x_3574_; uint8_t v___x_3575_; 
v___x_3574_ = 0ULL;
v___x_3575_ = lean_uint64_dec_eq(v___y_3573_, v___x_3574_);
if (v___x_3575_ == 0)
{
uint8_t v___x_3576_; 
lean_del_object(v___x_3538_);
lean_dec(v_snd_3536_);
lean_del_object(v___x_3533_);
lean_del_object(v___x_3511_);
lean_del_object(v___x_3506_);
lean_del_object(v___x_3502_);
v___x_3576_ = lean_uint32_dec_eq(v___x_3568_, v_high_3563_);
if (v___x_3576_ == 0)
{
uint32_t v___x_3577_; uint32_t v___x_3578_; 
v___x_3577_ = 1;
v___x_3578_ = lean_uint32_sub(v___x_3568_, v___x_3577_);
v___y_3523_ = v___y_3570_;
v___y_3524_ = v___y_3571_;
v___y_3525_ = v___y_3572_;
v___y_3526_ = v___x_3578_;
goto v___jp_3522_;
}
else
{
v___y_3523_ = v___y_3570_;
v___y_3524_ = v___y_3571_;
v___y_3525_ = v___y_3572_;
v___y_3526_ = v_high_3563_;
goto v___jp_3522_;
}
}
else
{
v___y_3541_ = v___y_3570_;
v___y_3542_ = v___y_3571_;
v___y_3543_ = v___y_3572_;
goto v___jp_3540_;
}
}
v___jp_3582_:
{
lean_object* v___x_3586_; lean_object* v___x_3587_; uint8_t v___x_3588_; 
v___x_3586_ = lean_box_uint32(v___y_3585_);
v___x_3587_ = lean_array_push(v_fst_3500_, v___x_3586_);
v___x_3588_ = lean_uint32_dec_eq(v___x_3568_, v_low_3561_);
if (v___x_3588_ == 0)
{
uint8_t v___x_3589_; 
v___x_3589_ = lean_uint32_dec_eq(v___x_3568_, v_high_3563_);
if (v___x_3589_ == 0)
{
uint32_t v___x_3590_; uint32_t v___x_3591_; uint64_t v___x_3592_; 
v___x_3590_ = 8388608;
v___x_3591_ = lean_uint32_lor(v___x_3581_, v___x_3590_);
v___x_3592_ = lean_uint32_to_uint64(v___x_3591_);
v___y_3570_ = v___y_3583_;
v___y_3571_ = v___x_3587_;
v___y_3572_ = v___y_3584_;
v___y_3573_ = v___x_3592_;
goto v___jp_3569_;
}
else
{
uint64_t v___x_3593_; 
v___x_3593_ = lean_uint32_to_uint64(v___x_3581_);
v___y_3570_ = v___y_3583_;
v___y_3571_ = v___x_3587_;
v___y_3572_ = v___y_3584_;
v___y_3573_ = v___x_3593_;
goto v___jp_3569_;
}
}
else
{
v___y_3541_ = v___y_3583_;
v___y_3542_ = v___x_3587_;
v___y_3543_ = v___y_3584_;
goto v___jp_3540_;
}
}
v___jp_3594_:
{
uint64_t v___x_3598_; uint8_t v___x_3599_; 
v___x_3598_ = 0ULL;
v___x_3599_ = lean_uint64_dec_eq(v___y_3597_, v___x_3598_);
if (v___x_3599_ == 0)
{
uint32_t v___x_3600_; uint32_t v___x_3601_; uint32_t v___x_3602_; 
v___x_3600_ = 8388608;
v___x_3601_ = lean_unbox_uint32(v_a_3564_);
v___x_3602_ = lean_uint32_sub(v___x_3601_, v___x_3600_);
v___y_3583_ = v___y_3595_;
v___y_3584_ = v___y_3596_;
v___y_3585_ = v___x_3602_;
goto v___jp_3582_;
}
else
{
uint32_t v___x_3603_; uint32_t v___x_3604_; uint32_t v___x_3605_; uint32_t v___x_3606_; uint32_t v___x_3607_; 
v___x_3603_ = 2147483648;
v___x_3604_ = lean_unbox_uint32(v_a_3564_);
v___x_3605_ = lean_uint32_land(v___x_3604_, v___x_3603_);
v___x_3606_ = 2130706432;
v___x_3607_ = lean_uint32_lor(v___x_3605_, v___x_3606_);
v___y_3583_ = v___y_3595_;
v___y_3584_ = v___y_3596_;
v___y_3585_ = v___x_3607_;
goto v___jp_3582_;
}
}
v___jp_3608_:
{
uint8_t v___x_3611_; 
v___x_3611_ = lean_uint32_dec_eq(v___x_3568_, v_high_3563_);
if (v___x_3611_ == 0)
{
uint32_t v___x_3612_; uint32_t v___x_3613_; uint64_t v___x_3614_; 
v___x_3612_ = 8388608;
v___x_3613_ = lean_uint32_lor(v___x_3581_, v___x_3612_);
v___x_3614_ = lean_uint32_to_uint64(v___x_3613_);
v___y_3595_ = v___y_3610_;
v___y_3596_ = v___y_3609_;
v___y_3597_ = v___x_3614_;
goto v___jp_3594_;
}
else
{
uint64_t v___x_3615_; 
v___x_3615_ = lean_uint32_to_uint64(v___x_3581_);
v___y_3595_ = v___y_3610_;
v___y_3596_ = v___y_3609_;
v___y_3597_ = v___x_3615_;
goto v___jp_3594_;
}
}
v___jp_3616_:
{
uint8_t v___x_3618_; 
v___x_3618_ = lean_unbox(v_fst_3531_);
lean_dec(v_fst_3531_);
if (v___x_3618_ == 0)
{
v___y_3609_ = v___y_3617_;
v___y_3610_ = v_seen_3562_;
goto v___jp_3608_;
}
else
{
lean_object* v___x_3619_; uint8_t v___x_3620_; 
v___x_3619_ = lean_box(0);
v___x_3620_ = lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00Submission_R24ExactDotCost_prepareOperand_spec__0___lam__0(v___x_3568_, v_low_3561_, v_normal_3481_, v_seen_3562_, v___x_3619_);
if (v___x_3620_ == 0)
{
v___y_3609_ = v___y_3617_;
v___y_3610_ = v_seen_3562_;
goto v___jp_3608_;
}
else
{
uint8_t v___x_3621_; 
v___x_3621_ = lean_uint32_dec_eq(v___x_3568_, v_high_3563_);
if (v___x_3621_ == 0)
{
v___y_3609_ = v___y_3617_;
v___y_3610_ = v_normal_3481_;
goto v___jp_3608_;
}
else
{
uint8_t v___x_3622_; 
v___x_3622_ = lean_uint32_dec_eq(v___x_3581_, v_high_3563_);
v___y_3609_ = v___y_3617_;
v___y_3610_ = v___x_3622_;
goto v___jp_3608_;
}
}
}
}
}
}
}
}
}
}
v___jp_3476_:
{
size_t v___x_3478_; size_t v___x_3479_; 
v___x_3478_ = ((size_t)1ULL);
v___x_3479_ = lean_usize_add(v_i_3474_, v___x_3478_);
v_i_3474_ = v___x_3479_;
v_b_3475_ = v_a_3477_;
goto _start;
}
v___jp_3482_:
{
lean_object* v___x_3488_; lean_object* v___x_3489_; lean_object* v___x_3490_; lean_object* v___x_3491_; lean_object* v___x_3492_; lean_object* v___x_3493_; lean_object* v___x_3494_; lean_object* v___x_3495_; lean_object* v___x_3496_; lean_object* v___x_3497_; 
v___x_3488_ = lean_box(v___y_3486_);
v___x_3489_ = lean_box(v_normal_3481_);
v___x_3490_ = lean_alloc_ctor(0, 2, 0);
lean_ctor_set(v___x_3490_, 0, v___x_3488_);
lean_ctor_set(v___x_3490_, 1, v___x_3489_);
v___x_3491_ = lean_box(v___y_3483_);
v___x_3492_ = lean_alloc_ctor(0, 2, 0);
lean_ctor_set(v___x_3492_, 0, v___x_3491_);
lean_ctor_set(v___x_3492_, 1, v___x_3490_);
v___x_3493_ = lean_box_uint32(v___y_3487_);
v___x_3494_ = lean_alloc_ctor(0, 2, 0);
lean_ctor_set(v___x_3494_, 0, v___x_3493_);
lean_ctor_set(v___x_3494_, 1, v___x_3492_);
v___x_3495_ = lean_box_uint32(v___y_3484_);
v___x_3496_ = lean_alloc_ctor(0, 2, 0);
lean_ctor_set(v___x_3496_, 0, v___x_3495_);
lean_ctor_set(v___x_3496_, 1, v___x_3494_);
v___x_3497_ = lean_alloc_ctor(0, 2, 0);
lean_ctor_set(v___x_3497_, 0, v___y_3485_);
lean_ctor_set(v___x_3497_, 1, v___x_3496_);
v_a_3477_ = v___x_3497_;
goto v___jp_3476_;
}
}
}
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00Submission_R24ExactDotCost_prepareOperand_spec__0___boxed(lean_object* v_as_3633_, lean_object* v_sz_3634_, lean_object* v_i_3635_, lean_object* v_b_3636_){
_start:
{
size_t v_sz_boxed_3637_; size_t v_i_boxed_3638_; lean_object* v_res_3639_; 
v_sz_boxed_3637_ = lean_unbox_usize(v_sz_3634_);
lean_dec(v_sz_3634_);
v_i_boxed_3638_ = lean_unbox_usize(v_i_3635_);
lean_dec(v_i_3635_);
v_res_3639_ = lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00Submission_R24ExactDotCost_prepareOperand_spec__0(v_as_3633_, v_sz_boxed_3637_, v_i_boxed_3638_, v_b_3636_);
lean_dec_ref(v_as_3633_);
return v_res_3639_;
}
}
static lean_object* _init_lp_competition_Submission_R24ExactDotCost_prepareOperand___closed__2___boxed__const__1(void){
_start:
{
uint32_t v___x_3649_; lean_object* v___x_3650_; 
v___x_3649_ = 0;
v___x_3650_ = lean_box_uint32(v___x_3649_);
return v___x_3650_;
}
}
static lean_object* _init_lp_competition_Submission_R24ExactDotCost_prepareOperand___closed__2(void){
_start:
{
lean_object* v___x_3651_; lean_object* v___x_3652_; lean_object* v___x_3653_; 
v___x_3651_ = ((lean_object*)(lp_competition_Submission_R24ExactDotCost_prepareOperand___closed__1));
v___x_3652_ = lp_competition_Submission_R24ExactDotCost_prepareOperand___closed__2___boxed__const__1;
v___x_3653_ = lean_alloc_ctor(0, 2, 0);
lean_ctor_set(v___x_3653_, 0, v___x_3652_);
lean_ctor_set(v___x_3653_, 1, v___x_3651_);
return v___x_3653_;
}
}
static lean_object* _init_lp_competition_Submission_R24ExactDotCost_prepareOperand___closed__3___boxed__const__1(void){
_start:
{
uint32_t v___x_3654_; lean_object* v___x_3655_; 
v___x_3654_ = 255;
v___x_3655_ = lean_box_uint32(v___x_3654_);
return v___x_3655_;
}
}
static lean_object* _init_lp_competition_Submission_R24ExactDotCost_prepareOperand___closed__3(void){
_start:
{
lean_object* v___x_3656_; lean_object* v___x_3657_; lean_object* v___x_3658_; 
v___x_3656_ = lean_obj_once(&lp_competition_Submission_R24ExactDotCost_prepareOperand___closed__2, &lp_competition_Submission_R24ExactDotCost_prepareOperand___closed__2_once, _init_lp_competition_Submission_R24ExactDotCost_prepareOperand___closed__2);
v___x_3657_ = lp_competition_Submission_R24ExactDotCost_prepareOperand___closed__3___boxed__const__1;
v___x_3658_ = lean_alloc_ctor(0, 2, 0);
lean_ctor_set(v___x_3658_, 0, v___x_3657_);
lean_ctor_set(v___x_3658_, 1, v___x_3656_);
return v___x_3658_;
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_R24ExactDotCost_prepareOperand(lean_object* v_raw_3659_){
_start:
{
lean_object* v___x_3660_; lean_object* v_data_3661_; uint32_t v_high_3662_; lean_object* v___x_3663_; lean_object* v___x_3664_; size_t v_sz_3665_; size_t v___x_3666_; lean_object* v___x_3667_; lean_object* v_snd_3668_; lean_object* v_snd_3669_; lean_object* v_snd_3670_; lean_object* v_snd_3671_; lean_object* v_fst_3672_; lean_object* v_fst_3673_; lean_object* v_fst_3674_; lean_object* v_fst_3675_; lean_object* v_fst_3676_; lean_object* v_snd_3677_; uint32_t v___y_3679_; uint8_t v___x_3690_; 
v___x_3660_ = lean_array_get_size(v_raw_3659_);
v_data_3661_ = lean_mk_empty_array_with_capacity(v___x_3660_);
v_high_3662_ = 0;
v___x_3663_ = lean_obj_once(&lp_competition_Submission_R24ExactDotCost_prepareOperand___closed__3, &lp_competition_Submission_R24ExactDotCost_prepareOperand___closed__3_once, _init_lp_competition_Submission_R24ExactDotCost_prepareOperand___closed__3);
v___x_3664_ = lean_alloc_ctor(0, 2, 0);
lean_ctor_set(v___x_3664_, 0, v_data_3661_);
lean_ctor_set(v___x_3664_, 1, v___x_3663_);
v_sz_3665_ = lean_array_size(v_raw_3659_);
v___x_3666_ = ((size_t)0ULL);
v___x_3667_ = lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00Submission_R24ExactDotCost_prepareOperand_spec__0(v_raw_3659_, v_sz_3665_, v___x_3666_, v___x_3664_);
v_snd_3668_ = lean_ctor_get(v___x_3667_, 1);
lean_inc(v_snd_3668_);
v_snd_3669_ = lean_ctor_get(v_snd_3668_, 1);
lean_inc(v_snd_3669_);
v_snd_3670_ = lean_ctor_get(v_snd_3669_, 1);
lean_inc(v_snd_3670_);
v_snd_3671_ = lean_ctor_get(v_snd_3670_, 1);
lean_inc(v_snd_3671_);
v_fst_3672_ = lean_ctor_get(v___x_3667_, 0);
lean_inc(v_fst_3672_);
lean_dec_ref(v___x_3667_);
v_fst_3673_ = lean_ctor_get(v_snd_3668_, 0);
lean_inc(v_fst_3673_);
lean_dec(v_snd_3668_);
v_fst_3674_ = lean_ctor_get(v_snd_3669_, 0);
lean_inc(v_fst_3674_);
lean_dec(v_snd_3669_);
v_fst_3675_ = lean_ctor_get(v_snd_3670_, 0);
lean_inc(v_fst_3675_);
lean_dec(v_snd_3670_);
v_fst_3676_ = lean_ctor_get(v_snd_3671_, 0);
lean_inc(v_fst_3676_);
v_snd_3677_ = lean_ctor_get(v_snd_3671_, 1);
lean_inc(v_snd_3677_);
lean_dec(v_snd_3671_);
v___x_3690_ = lean_unbox(v_snd_3677_);
if (v___x_3690_ == 0)
{
lean_dec(v_fst_3673_);
v___y_3679_ = v_high_3662_;
goto v___jp_3678_;
}
else
{
uint32_t v___x_3691_; 
v___x_3691_ = lean_unbox_uint32(v_fst_3673_);
lean_dec(v_fst_3673_);
v___y_3679_ = v___x_3691_;
goto v___jp_3678_;
}
v___jp_3678_:
{
uint8_t v___x_3680_; 
v___x_3680_ = lean_unbox(v_snd_3677_);
if (v___x_3680_ == 0)
{
lean_object* v___x_3681_; uint8_t v___x_3682_; uint8_t v___x_3683_; uint8_t v___x_3684_; 
lean_dec(v_fst_3674_);
v___x_3681_ = lean_alloc_ctor(0, 2, 11);
lean_ctor_set(v___x_3681_, 0, v_raw_3659_);
lean_ctor_set(v___x_3681_, 1, v_fst_3672_);
lean_ctor_set_uint32(v___x_3681_, sizeof(void*)*2, v___y_3679_);
lean_ctor_set_uint32(v___x_3681_, sizeof(void*)*2 + 4, v_high_3662_);
v___x_3682_ = lean_unbox(v_fst_3675_);
lean_dec(v_fst_3675_);
lean_ctor_set_uint8(v___x_3681_, sizeof(void*)*2 + 8, v___x_3682_);
v___x_3683_ = lean_unbox(v_fst_3676_);
lean_dec(v_fst_3676_);
lean_ctor_set_uint8(v___x_3681_, sizeof(void*)*2 + 9, v___x_3683_);
v___x_3684_ = lean_unbox(v_snd_3677_);
lean_dec(v_snd_3677_);
lean_ctor_set_uint8(v___x_3681_, sizeof(void*)*2 + 10, v___x_3684_);
return v___x_3681_;
}
else
{
lean_object* v___x_3685_; uint32_t v___x_3686_; uint8_t v___x_3687_; uint8_t v___x_3688_; uint8_t v___x_3689_; 
v___x_3685_ = lean_alloc_ctor(0, 2, 11);
lean_ctor_set(v___x_3685_, 0, v_raw_3659_);
lean_ctor_set(v___x_3685_, 1, v_fst_3672_);
lean_ctor_set_uint32(v___x_3685_, sizeof(void*)*2, v___y_3679_);
v___x_3686_ = lean_unbox_uint32(v_fst_3674_);
lean_dec(v_fst_3674_);
lean_ctor_set_uint32(v___x_3685_, sizeof(void*)*2 + 4, v___x_3686_);
v___x_3687_ = lean_unbox(v_fst_3675_);
lean_dec(v_fst_3675_);
lean_ctor_set_uint8(v___x_3685_, sizeof(void*)*2 + 8, v___x_3687_);
v___x_3688_ = lean_unbox(v_fst_3676_);
lean_dec(v_fst_3676_);
lean_ctor_set_uint8(v___x_3685_, sizeof(void*)*2 + 9, v___x_3688_);
v___x_3689_ = lean_unbox(v_snd_3677_);
lean_dec(v_snd_3677_);
lean_ctor_set_uint8(v___x_3685_, sizeof(void*)*2 + 10, v___x_3689_);
return v___x_3685_;
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_R24ExactDotCost_pair(lean_object* v_left_3692_, lean_object* v_right_3693_){
_start:
{
lean_object* v_raw_3694_; uint32_t v_minIdx_3695_; uint32_t v_maxIdx_3696_; uint8_t v_hasNonzero_3697_; uint32_t v___y_3699_; uint32_t v___y_3700_; 
v_raw_3694_ = lean_ctor_get(v_left_3692_, 0);
v_minIdx_3695_ = lean_ctor_get_uint32(v_left_3692_, sizeof(void*)*2);
v_maxIdx_3696_ = lean_ctor_get_uint32(v_left_3692_, sizeof(void*)*2 + 4);
v_hasNonzero_3697_ = lean_ctor_get_uint8(v_left_3692_, sizeof(void*)*2 + 10);
if (v_hasNonzero_3697_ == 0)
{
goto v___jp_3706_;
}
else
{
uint8_t v_hasNonzero_3708_; 
v_hasNonzero_3708_ = lean_ctor_get_uint8(v_right_3693_, sizeof(void*)*2 + 10);
if (v_hasNonzero_3708_ == 0)
{
goto v___jp_3706_;
}
else
{
uint32_t v_minIdx_3709_; uint32_t v_maxIdx_3710_; uint32_t v___x_3711_; uint32_t v___x_3712_; 
v_minIdx_3709_ = lean_ctor_get_uint32(v_right_3693_, sizeof(void*)*2);
v_maxIdx_3710_ = lean_ctor_get_uint32(v_right_3693_, sizeof(void*)*2 + 4);
v___x_3711_ = lean_uint32_add(v_minIdx_3695_, v_minIdx_3709_);
v___x_3712_ = lean_uint32_add(v_maxIdx_3696_, v_maxIdx_3710_);
v___y_3699_ = v___x_3711_;
v___y_3700_ = v___x_3712_;
goto v___jp_3698_;
}
}
v___jp_3698_:
{
lean_object* v_raw_3701_; lean_object* v___x_3702_; lean_object* v___x_3703_; uint8_t v___x_3704_; lean_object* v___x_3705_; 
v_raw_3701_ = lean_ctor_get(v_right_3693_, 0);
v___x_3702_ = lean_array_get_size(v_raw_3694_);
v___x_3703_ = lean_array_get_size(v_raw_3701_);
v___x_3704_ = lean_nat_dec_eq(v___x_3702_, v___x_3703_);
v___x_3705_ = lean_alloc_ctor(0, 2, 9);
lean_ctor_set(v___x_3705_, 0, v_left_3692_);
lean_ctor_set(v___x_3705_, 1, v_right_3693_);
lean_ctor_set_uint32(v___x_3705_, sizeof(void*)*2, v___y_3699_);
lean_ctor_set_uint32(v___x_3705_, sizeof(void*)*2 + 4, v___y_3700_);
lean_ctor_set_uint8(v___x_3705_, sizeof(void*)*2 + 8, v___x_3704_);
return v___x_3705_;
}
v___jp_3706_:
{
uint32_t v___x_3707_; 
v___x_3707_ = 0;
v___y_3699_ = v___x_3707_;
v___y_3700_ = v___x_3707_;
goto v___jp_3698_;
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_R24ExactDotCost_prepare(lean_object* v_rawA_3713_, lean_object* v_rawB_3714_){
_start:
{
lean_object* v___x_3715_; uint8_t v_hasNonzero_3716_; lean_object* v___x_3717_; uint32_t v___y_3719_; uint32_t v___y_3720_; 
v___x_3715_ = lp_competition_Submission_R24ExactDotCost_prepareOperand(v_rawA_3713_);
v_hasNonzero_3716_ = lean_ctor_get_uint8(v___x_3715_, sizeof(void*)*2 + 10);
v___x_3717_ = lp_competition_Submission_R24ExactDotCost_prepareOperand(v_rawB_3714_);
if (v_hasNonzero_3716_ == 0)
{
goto v___jp_3727_;
}
else
{
uint8_t v_hasNonzero_3729_; 
v_hasNonzero_3729_ = lean_ctor_get_uint8(v___x_3717_, sizeof(void*)*2 + 10);
if (v_hasNonzero_3729_ == 0)
{
goto v___jp_3727_;
}
else
{
uint32_t v_minIdx_3730_; uint32_t v_minIdx_3731_; uint32_t v_maxIdx_3732_; uint32_t v_maxIdx_3733_; uint32_t v___x_3734_; uint32_t v___x_3735_; 
v_minIdx_3730_ = lean_ctor_get_uint32(v___x_3715_, sizeof(void*)*2);
v_minIdx_3731_ = lean_ctor_get_uint32(v___x_3717_, sizeof(void*)*2);
v_maxIdx_3732_ = lean_ctor_get_uint32(v___x_3715_, sizeof(void*)*2 + 4);
v_maxIdx_3733_ = lean_ctor_get_uint32(v___x_3717_, sizeof(void*)*2 + 4);
v___x_3734_ = lean_uint32_add(v_minIdx_3730_, v_minIdx_3731_);
v___x_3735_ = lean_uint32_add(v_maxIdx_3732_, v_maxIdx_3733_);
v___y_3719_ = v___x_3734_;
v___y_3720_ = v___x_3735_;
goto v___jp_3718_;
}
}
v___jp_3718_:
{
lean_object* v_raw_3721_; lean_object* v_raw_3722_; lean_object* v___x_3723_; lean_object* v___x_3724_; uint8_t v___x_3725_; lean_object* v___x_3726_; 
v_raw_3721_ = lean_ctor_get(v___x_3715_, 0);
lean_inc_ref(v_raw_3721_);
v_raw_3722_ = lean_ctor_get(v___x_3717_, 0);
lean_inc_ref(v_raw_3722_);
v___x_3723_ = lean_array_get_size(v_raw_3721_);
lean_dec_ref(v_raw_3721_);
v___x_3724_ = lean_array_get_size(v_raw_3722_);
lean_dec_ref(v_raw_3722_);
v___x_3725_ = lean_nat_dec_eq(v___x_3723_, v___x_3724_);
v___x_3726_ = lean_alloc_ctor(0, 2, 9);
lean_ctor_set(v___x_3726_, 0, v___x_3715_);
lean_ctor_set(v___x_3726_, 1, v___x_3717_);
lean_ctor_set_uint32(v___x_3726_, sizeof(void*)*2, v___y_3719_);
lean_ctor_set_uint32(v___x_3726_, sizeof(void*)*2 + 4, v___y_3720_);
lean_ctor_set_uint8(v___x_3726_, sizeof(void*)*2 + 8, v___x_3725_);
return v___x_3726_;
}
v___jp_3727_:
{
uint32_t v___x_3728_; 
v___x_3728_ = 0;
v___y_3719_ = v___x_3728_;
v___y_3720_ = v___x_3728_;
goto v___jp_3718_;
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_R24ExactDotCost_Cache_rawA(lean_object* v_c_3736_){
_start:
{
lean_object* v_left_3737_; lean_object* v_raw_3738_; 
v_left_3737_ = lean_ctor_get(v_c_3736_, 0);
v_raw_3738_ = lean_ctor_get(v_left_3737_, 0);
lean_inc_ref(v_raw_3738_);
return v_raw_3738_;
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_R24ExactDotCost_Cache_rawA___boxed(lean_object* v_c_3739_){
_start:
{
lean_object* v_res_3740_; 
v_res_3740_ = lp_competition_Submission_R24ExactDotCost_Cache_rawA(v_c_3739_);
lean_dec_ref(v_c_3739_);
return v_res_3740_;
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_R24ExactDotCost_Cache_rawB(lean_object* v_c_3741_){
_start:
{
lean_object* v_right_3742_; lean_object* v_raw_3743_; 
v_right_3742_ = lean_ctor_get(v_c_3741_, 1);
v_raw_3743_ = lean_ctor_get(v_right_3742_, 0);
lean_inc_ref(v_raw_3743_);
return v_raw_3743_;
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_R24ExactDotCost_Cache_rawB___boxed(lean_object* v_c_3744_){
_start:
{
lean_object* v_res_3745_; 
v_res_3745_ = lp_competition_Submission_R24ExactDotCost_Cache_rawB(v_c_3744_);
lean_dec_ref(v_c_3744_);
return v_res_3745_;
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_R24ExactDotCost_Cache_a(lean_object* v_c_3746_){
_start:
{
lean_object* v_left_3747_; lean_object* v_data_3748_; 
v_left_3747_ = lean_ctor_get(v_c_3746_, 0);
v_data_3748_ = lean_ctor_get(v_left_3747_, 1);
lean_inc_ref(v_data_3748_);
return v_data_3748_;
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_R24ExactDotCost_Cache_a___boxed(lean_object* v_c_3749_){
_start:
{
lean_object* v_res_3750_; 
v_res_3750_ = lp_competition_Submission_R24ExactDotCost_Cache_a(v_c_3749_);
lean_dec_ref(v_c_3749_);
return v_res_3750_;
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_R24ExactDotCost_Cache_b(lean_object* v_c_3751_){
_start:
{
lean_object* v_right_3752_; lean_object* v_data_3753_; 
v_right_3752_ = lean_ctor_get(v_c_3751_, 1);
v_data_3753_ = lean_ctor_get(v_right_3752_, 1);
lean_inc_ref(v_data_3753_);
return v_data_3753_;
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_R24ExactDotCost_Cache_b___boxed(lean_object* v_c_3754_){
_start:
{
lean_object* v_res_3755_; 
v_res_3755_ = lp_competition_Submission_R24ExactDotCost_Cache_b(v_c_3754_);
lean_dec_ref(v_c_3754_);
return v_res_3755_;
}
}
LEAN_EXPORT uint8_t lp_competition_Submission_R24ExactDotCost_Cache_normal(lean_object* v_c_3756_){
_start:
{
lean_object* v_left_3757_; uint8_t v_normal_3758_; 
v_left_3757_ = lean_ctor_get(v_c_3756_, 0);
v_normal_3758_ = lean_ctor_get_uint8(v_left_3757_, sizeof(void*)*2 + 8);
if (v_normal_3758_ == 0)
{
return v_normal_3758_;
}
else
{
lean_object* v_right_3759_; uint8_t v_normal_3760_; 
v_right_3759_ = lean_ctor_get(v_c_3756_, 1);
v_normal_3760_ = lean_ctor_get_uint8(v_right_3759_, sizeof(void*)*2 + 8);
return v_normal_3760_;
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_R24ExactDotCost_Cache_normal___boxed(lean_object* v_c_3761_){
_start:
{
uint8_t v_res_3762_; lean_object* v_r_3763_; 
v_res_3762_ = lp_competition_Submission_R24ExactDotCost_Cache_normal(v_c_3761_);
lean_dec_ref(v_c_3761_);
v_r_3763_ = lean_box(v_res_3762_);
return v_r_3763_;
}
}
LEAN_EXPORT uint8_t lp_competition_Submission_R24ExactDotCost_Cache_finite(lean_object* v_c_3764_){
_start:
{
lean_object* v_left_3765_; uint8_t v_finite_3766_; 
v_left_3765_ = lean_ctor_get(v_c_3764_, 0);
v_finite_3766_ = lean_ctor_get_uint8(v_left_3765_, sizeof(void*)*2 + 9);
if (v_finite_3766_ == 0)
{
return v_finite_3766_;
}
else
{
lean_object* v_right_3767_; uint8_t v_finite_3768_; 
v_right_3767_ = lean_ctor_get(v_c_3764_, 1);
v_finite_3768_ = lean_ctor_get_uint8(v_right_3767_, sizeof(void*)*2 + 9);
return v_finite_3768_;
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_R24ExactDotCost_Cache_finite___boxed(lean_object* v_c_3769_){
_start:
{
uint8_t v_res_3770_; lean_object* v_r_3771_; 
v_res_3770_ = lp_competition_Submission_R24ExactDotCost_Cache_finite(v_c_3769_);
lean_dec_ref(v_c_3769_);
v_r_3771_ = lean_box(v_res_3770_);
return v_r_3771_;
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_R24ExactDotCost_ceilLog2(lean_object* v_n_3772_){
_start:
{
lean_object* v___x_3773_; uint64_t v___y_3775_; uint64_t v___y_3779_; uint64_t v___y_3780_; uint64_t v___y_3787_; uint64_t v___y_3788_; uint64_t v___y_3789_; uint64_t v___y_3790_; uint64_t v___y_3796_; uint64_t v___y_3797_; uint64_t v___y_3803_; uint64_t v___y_3804_; uint64_t v___y_3805_; uint64_t v___y_3806_; uint64_t v___y_3812_; uint64_t v___y_3813_; uint64_t v___y_3819_; uint64_t v___y_3820_; uint64_t v___y_3821_; uint64_t v___y_3822_; uint64_t v___y_3828_; uint64_t v___y_3829_; uint64_t v___y_3835_; uint64_t v___y_3836_; uint64_t v___y_3837_; uint64_t v___y_3838_; uint64_t v___y_3844_; uint64_t v___y_3845_; uint8_t v___x_3850_; 
v___x_3773_ = lean_unsigned_to_nat(1u);
v___x_3850_ = lean_nat_dec_le(v_n_3772_, v___x_3773_);
if (v___x_3850_ == 0)
{
lean_object* v___x_3851_; uint64_t v___x_3852_; uint64_t v___x_3853_; uint64_t v___y_3855_; uint64_t v___x_3859_; uint64_t v___x_3860_; uint8_t v___x_3861_; 
v___x_3851_ = lean_nat_sub(v_n_3772_, v___x_3773_);
v___x_3852_ = lean_uint64_of_nat(v___x_3851_);
lean_dec(v___x_3851_);
v___x_3853_ = 32ULL;
v___x_3859_ = lean_uint64_shift_right(v___x_3852_, v___x_3853_);
v___x_3860_ = 0ULL;
v___x_3861_ = lean_uint64_dec_eq(v___x_3859_, v___x_3860_);
if (v___x_3861_ == 0)
{
v___y_3855_ = v___x_3859_;
goto v___jp_3854_;
}
else
{
v___y_3855_ = v___x_3852_;
goto v___jp_3854_;
}
v___jp_3854_:
{
uint64_t v___x_3856_; uint64_t v___x_3857_; uint8_t v___x_3858_; 
v___x_3856_ = lean_uint64_shift_right(v___x_3852_, v___x_3853_);
v___x_3857_ = 0ULL;
v___x_3858_ = lean_uint64_dec_eq(v___x_3856_, v___x_3857_);
if (v___x_3858_ == 0)
{
v___y_3844_ = v___y_3855_;
v___y_3845_ = v___x_3853_;
goto v___jp_3843_;
}
else
{
v___y_3844_ = v___y_3855_;
v___y_3845_ = v___x_3857_;
goto v___jp_3843_;
}
}
}
else
{
lean_object* v___x_3862_; 
v___x_3862_ = lean_unsigned_to_nat(0u);
return v___x_3862_;
}
v___jp_3774_:
{
lean_object* v___x_3776_; lean_object* v___x_3777_; 
v___x_3776_ = lean_uint64_to_nat(v___y_3775_);
v___x_3777_ = lean_nat_add(v___x_3776_, v___x_3773_);
lean_dec(v___x_3776_);
return v___x_3777_;
}
v___jp_3778_:
{
uint64_t v___x_3781_; uint64_t v___x_3782_; uint64_t v___x_3783_; uint8_t v___x_3784_; 
v___x_3781_ = 1ULL;
v___x_3782_ = lean_uint64_shift_right(v___y_3779_, v___x_3781_);
v___x_3783_ = 0ULL;
v___x_3784_ = lean_uint64_dec_eq(v___x_3782_, v___x_3783_);
if (v___x_3784_ == 0)
{
uint64_t v___x_3785_; 
v___x_3785_ = lean_uint64_add(v___y_3780_, v___x_3781_);
v___y_3775_ = v___x_3785_;
goto v___jp_3774_;
}
else
{
v___y_3775_ = v___y_3780_;
goto v___jp_3774_;
}
}
v___jp_3786_:
{
uint64_t v___x_3791_; uint64_t v___x_3792_; uint8_t v___x_3793_; 
v___x_3791_ = lean_uint64_shift_right(v___y_3788_, v___y_3787_);
v___x_3792_ = 0ULL;
v___x_3793_ = lean_uint64_dec_eq(v___x_3791_, v___x_3792_);
if (v___x_3793_ == 0)
{
uint64_t v___x_3794_; 
v___x_3794_ = lean_uint64_add(v___y_3789_, v___y_3787_);
v___y_3779_ = v___y_3790_;
v___y_3780_ = v___x_3794_;
goto v___jp_3778_;
}
else
{
v___y_3779_ = v___y_3790_;
v___y_3780_ = v___y_3789_;
goto v___jp_3778_;
}
}
v___jp_3795_:
{
uint64_t v___x_3798_; uint64_t v___x_3799_; uint64_t v___x_3800_; uint8_t v___x_3801_; 
v___x_3798_ = 2ULL;
v___x_3799_ = lean_uint64_shift_right(v___y_3796_, v___x_3798_);
v___x_3800_ = 0ULL;
v___x_3801_ = lean_uint64_dec_eq(v___x_3799_, v___x_3800_);
if (v___x_3801_ == 0)
{
v___y_3787_ = v___x_3798_;
v___y_3788_ = v___y_3796_;
v___y_3789_ = v___y_3797_;
v___y_3790_ = v___x_3799_;
goto v___jp_3786_;
}
else
{
v___y_3787_ = v___x_3798_;
v___y_3788_ = v___y_3796_;
v___y_3789_ = v___y_3797_;
v___y_3790_ = v___y_3796_;
goto v___jp_3786_;
}
}
v___jp_3802_:
{
uint64_t v___x_3807_; uint64_t v___x_3808_; uint8_t v___x_3809_; 
v___x_3807_ = lean_uint64_shift_right(v___y_3804_, v___y_3805_);
v___x_3808_ = 0ULL;
v___x_3809_ = lean_uint64_dec_eq(v___x_3807_, v___x_3808_);
if (v___x_3809_ == 0)
{
uint64_t v___x_3810_; 
v___x_3810_ = lean_uint64_add(v___y_3803_, v___y_3805_);
v___y_3796_ = v___y_3806_;
v___y_3797_ = v___x_3810_;
goto v___jp_3795_;
}
else
{
v___y_3796_ = v___y_3806_;
v___y_3797_ = v___y_3803_;
goto v___jp_3795_;
}
}
v___jp_3811_:
{
uint64_t v___x_3814_; uint64_t v___x_3815_; uint64_t v___x_3816_; uint8_t v___x_3817_; 
v___x_3814_ = 4ULL;
v___x_3815_ = lean_uint64_shift_right(v___y_3812_, v___x_3814_);
v___x_3816_ = 0ULL;
v___x_3817_ = lean_uint64_dec_eq(v___x_3815_, v___x_3816_);
if (v___x_3817_ == 0)
{
v___y_3803_ = v___y_3813_;
v___y_3804_ = v___y_3812_;
v___y_3805_ = v___x_3814_;
v___y_3806_ = v___x_3815_;
goto v___jp_3802_;
}
else
{
v___y_3803_ = v___y_3813_;
v___y_3804_ = v___y_3812_;
v___y_3805_ = v___x_3814_;
v___y_3806_ = v___y_3812_;
goto v___jp_3802_;
}
}
v___jp_3818_:
{
uint64_t v___x_3823_; uint64_t v___x_3824_; uint8_t v___x_3825_; 
v___x_3823_ = lean_uint64_shift_right(v___y_3821_, v___y_3820_);
v___x_3824_ = 0ULL;
v___x_3825_ = lean_uint64_dec_eq(v___x_3823_, v___x_3824_);
if (v___x_3825_ == 0)
{
uint64_t v___x_3826_; 
v___x_3826_ = lean_uint64_add(v___y_3819_, v___y_3820_);
v___y_3812_ = v___y_3822_;
v___y_3813_ = v___x_3826_;
goto v___jp_3811_;
}
else
{
v___y_3812_ = v___y_3822_;
v___y_3813_ = v___y_3819_;
goto v___jp_3811_;
}
}
v___jp_3827_:
{
uint64_t v___x_3830_; uint64_t v___x_3831_; uint64_t v___x_3832_; uint8_t v___x_3833_; 
v___x_3830_ = 8ULL;
v___x_3831_ = lean_uint64_shift_right(v___y_3828_, v___x_3830_);
v___x_3832_ = 0ULL;
v___x_3833_ = lean_uint64_dec_eq(v___x_3831_, v___x_3832_);
if (v___x_3833_ == 0)
{
v___y_3819_ = v___y_3829_;
v___y_3820_ = v___x_3830_;
v___y_3821_ = v___y_3828_;
v___y_3822_ = v___x_3831_;
goto v___jp_3818_;
}
else
{
v___y_3819_ = v___y_3829_;
v___y_3820_ = v___x_3830_;
v___y_3821_ = v___y_3828_;
v___y_3822_ = v___y_3828_;
goto v___jp_3818_;
}
}
v___jp_3834_:
{
uint64_t v___x_3839_; uint64_t v___x_3840_; uint8_t v___x_3841_; 
v___x_3839_ = lean_uint64_shift_right(v___y_3835_, v___y_3836_);
v___x_3840_ = 0ULL;
v___x_3841_ = lean_uint64_dec_eq(v___x_3839_, v___x_3840_);
if (v___x_3841_ == 0)
{
uint64_t v___x_3842_; 
v___x_3842_ = lean_uint64_add(v___y_3837_, v___y_3836_);
v___y_3828_ = v___y_3838_;
v___y_3829_ = v___x_3842_;
goto v___jp_3827_;
}
else
{
v___y_3828_ = v___y_3838_;
v___y_3829_ = v___y_3837_;
goto v___jp_3827_;
}
}
v___jp_3843_:
{
uint64_t v___x_3846_; uint64_t v___x_3847_; uint64_t v___x_3848_; uint8_t v___x_3849_; 
v___x_3846_ = 16ULL;
v___x_3847_ = lean_uint64_shift_right(v___y_3844_, v___x_3846_);
v___x_3848_ = 0ULL;
v___x_3849_ = lean_uint64_dec_eq(v___x_3847_, v___x_3848_);
if (v___x_3849_ == 0)
{
v___y_3835_ = v___y_3844_;
v___y_3836_ = v___x_3846_;
v___y_3837_ = v___y_3845_;
v___y_3838_ = v___x_3847_;
goto v___jp_3834_;
}
else
{
v___y_3835_ = v___y_3844_;
v___y_3836_ = v___x_3846_;
v___y_3837_ = v___y_3845_;
v___y_3838_ = v___y_3844_;
goto v___jp_3834_;
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_R24ExactDotCost_ceilLog2___boxed(lean_object* v_n_3863_){
_start:
{
lean_object* v_res_3864_; 
v_res_3864_ = lp_competition_Submission_R24ExactDotCost_ceilLog2(v_n_3863_);
lean_dec(v_n_3863_);
return v_res_3864_;
}
}
LEAN_EXPORT uint8_t lp_competition_Submission_R24ExactDotCost_fastEligible(lean_object* v_c_3865_){
_start:
{
uint8_t v_matched_3866_; 
v_matched_3866_ = lean_ctor_get_uint8(v_c_3865_, sizeof(void*)*2 + 8);
if (v_matched_3866_ == 0)
{
return v_matched_3866_;
}
else
{
lean_object* v_left_3867_; uint8_t v_normal_3868_; 
v_left_3867_ = lean_ctor_get(v_c_3865_, 0);
v_normal_3868_ = lean_ctor_get_uint8(v_left_3867_, sizeof(void*)*2 + 8);
if (v_normal_3868_ == 0)
{
return v_normal_3868_;
}
else
{
lean_object* v_right_3869_; uint8_t v_normal_3870_; 
v_right_3869_ = lean_ctor_get(v_c_3865_, 1);
v_normal_3870_ = lean_ctor_get_uint8(v_right_3869_, sizeof(void*)*2 + 8);
if (v_normal_3870_ == 0)
{
return v_normal_3870_;
}
else
{
uint32_t v_minScale_3871_; uint32_t v_maxScale_3872_; lean_object* v_data_3873_; lean_object* v___x_3874_; lean_object* v___x_3875_; uint8_t v___x_3876_; 
v_minScale_3871_ = lean_ctor_get_uint32(v_c_3865_, sizeof(void*)*2);
v_maxScale_3872_ = lean_ctor_get_uint32(v_c_3865_, sizeof(void*)*2 + 4);
v_data_3873_ = lean_ctor_get(v_left_3867_, 1);
v___x_3874_ = lean_array_get_size(v_data_3873_);
v___x_3875_ = lean_unsigned_to_nat(1048576u);
v___x_3876_ = lean_nat_dec_le(v___x_3874_, v___x_3875_);
if (v___x_3876_ == 0)
{
return v___x_3876_;
}
else
{
lean_object* v___x_3877_; lean_object* v___x_3878_; lean_object* v___x_3879_; lean_object* v___x_3880_; lean_object* v___x_3881_; lean_object* v___y_3883_; lean_object* v___x_3887_; uint64_t v___y_3889_; uint64_t v___y_3893_; uint64_t v___y_3894_; uint64_t v___y_3901_; uint64_t v___y_3902_; uint64_t v___y_3903_; uint64_t v___y_3904_; uint64_t v___y_3910_; uint64_t v___y_3911_; uint64_t v___y_3917_; uint64_t v___y_3918_; uint64_t v___y_3919_; uint64_t v___y_3920_; uint64_t v___y_3926_; uint64_t v___y_3927_; uint64_t v___y_3933_; uint64_t v___y_3934_; uint64_t v___y_3935_; uint64_t v___y_3936_; uint64_t v___y_3942_; uint64_t v___y_3943_; uint64_t v___y_3949_; uint64_t v___y_3950_; uint64_t v___y_3951_; uint64_t v___y_3952_; uint64_t v___y_3958_; uint64_t v___y_3959_; uint8_t v___x_3964_; 
v___x_3877_ = lean_unsigned_to_nat(48u);
v___x_3878_ = lean_uint32_to_nat(v_maxScale_3872_);
v___x_3879_ = lean_uint32_to_nat(v_minScale_3871_);
v___x_3880_ = lean_nat_sub(v___x_3878_, v___x_3879_);
lean_dec(v___x_3879_);
lean_dec(v___x_3878_);
v___x_3881_ = lean_nat_add(v___x_3877_, v___x_3880_);
lean_dec(v___x_3880_);
v___x_3887_ = lean_unsigned_to_nat(1u);
v___x_3964_ = lean_nat_dec_le(v___x_3874_, v___x_3887_);
if (v___x_3964_ == 0)
{
lean_object* v___x_3965_; uint64_t v___x_3966_; uint64_t v___x_3967_; uint64_t v___y_3969_; uint64_t v___x_3973_; uint64_t v___x_3974_; uint8_t v___x_3975_; 
v___x_3965_ = lean_nat_sub(v___x_3874_, v___x_3887_);
v___x_3966_ = lean_uint64_of_nat(v___x_3965_);
lean_dec(v___x_3965_);
v___x_3967_ = 32ULL;
v___x_3973_ = lean_uint64_shift_right(v___x_3966_, v___x_3967_);
v___x_3974_ = 0ULL;
v___x_3975_ = lean_uint64_dec_eq(v___x_3973_, v___x_3974_);
if (v___x_3975_ == 0)
{
v___y_3969_ = v___x_3973_;
goto v___jp_3968_;
}
else
{
v___y_3969_ = v___x_3966_;
goto v___jp_3968_;
}
v___jp_3968_:
{
uint64_t v___x_3970_; uint64_t v___x_3971_; uint8_t v___x_3972_; 
v___x_3970_ = lean_uint64_shift_right(v___x_3966_, v___x_3967_);
v___x_3971_ = 0ULL;
v___x_3972_ = lean_uint64_dec_eq(v___x_3970_, v___x_3971_);
if (v___x_3972_ == 0)
{
v___y_3958_ = v___y_3969_;
v___y_3959_ = v___x_3967_;
goto v___jp_3957_;
}
else
{
v___y_3958_ = v___y_3969_;
v___y_3959_ = v___x_3971_;
goto v___jp_3957_;
}
}
}
else
{
lean_object* v___x_3976_; 
v___x_3976_ = lean_unsigned_to_nat(0u);
v___y_3883_ = v___x_3976_;
goto v___jp_3882_;
}
v___jp_3882_:
{
lean_object* v___x_3884_; lean_object* v___x_3885_; uint8_t v___x_3886_; 
v___x_3884_ = lean_nat_add(v___x_3881_, v___y_3883_);
lean_dec(v___y_3883_);
lean_dec(v___x_3881_);
v___x_3885_ = lean_unsigned_to_nat(128u);
v___x_3886_ = lean_nat_dec_le(v___x_3884_, v___x_3885_);
lean_dec(v___x_3884_);
return v___x_3886_;
}
v___jp_3888_:
{
lean_object* v___x_3890_; lean_object* v___x_3891_; 
v___x_3890_ = lean_uint64_to_nat(v___y_3889_);
v___x_3891_ = lean_nat_add(v___x_3890_, v___x_3887_);
lean_dec(v___x_3890_);
v___y_3883_ = v___x_3891_;
goto v___jp_3882_;
}
v___jp_3892_:
{
uint64_t v___x_3895_; uint64_t v___x_3896_; uint64_t v___x_3897_; uint8_t v___x_3898_; 
v___x_3895_ = 1ULL;
v___x_3896_ = lean_uint64_shift_right(v___y_3893_, v___x_3895_);
v___x_3897_ = 0ULL;
v___x_3898_ = lean_uint64_dec_eq(v___x_3896_, v___x_3897_);
if (v___x_3898_ == 0)
{
uint64_t v___x_3899_; 
v___x_3899_ = lean_uint64_add(v___y_3894_, v___x_3895_);
v___y_3889_ = v___x_3899_;
goto v___jp_3888_;
}
else
{
v___y_3889_ = v___y_3894_;
goto v___jp_3888_;
}
}
v___jp_3900_:
{
uint64_t v___x_3905_; uint64_t v___x_3906_; uint8_t v___x_3907_; 
v___x_3905_ = lean_uint64_shift_right(v___y_3901_, v___y_3903_);
v___x_3906_ = 0ULL;
v___x_3907_ = lean_uint64_dec_eq(v___x_3905_, v___x_3906_);
if (v___x_3907_ == 0)
{
uint64_t v___x_3908_; 
v___x_3908_ = lean_uint64_add(v___y_3902_, v___y_3903_);
v___y_3893_ = v___y_3904_;
v___y_3894_ = v___x_3908_;
goto v___jp_3892_;
}
else
{
v___y_3893_ = v___y_3904_;
v___y_3894_ = v___y_3902_;
goto v___jp_3892_;
}
}
v___jp_3909_:
{
uint64_t v___x_3912_; uint64_t v___x_3913_; uint64_t v___x_3914_; uint8_t v___x_3915_; 
v___x_3912_ = 2ULL;
v___x_3913_ = lean_uint64_shift_right(v___y_3910_, v___x_3912_);
v___x_3914_ = 0ULL;
v___x_3915_ = lean_uint64_dec_eq(v___x_3913_, v___x_3914_);
if (v___x_3915_ == 0)
{
v___y_3901_ = v___y_3910_;
v___y_3902_ = v___y_3911_;
v___y_3903_ = v___x_3912_;
v___y_3904_ = v___x_3913_;
goto v___jp_3900_;
}
else
{
v___y_3901_ = v___y_3910_;
v___y_3902_ = v___y_3911_;
v___y_3903_ = v___x_3912_;
v___y_3904_ = v___y_3910_;
goto v___jp_3900_;
}
}
v___jp_3916_:
{
uint64_t v___x_3921_; uint64_t v___x_3922_; uint8_t v___x_3923_; 
v___x_3921_ = lean_uint64_shift_right(v___y_3919_, v___y_3917_);
v___x_3922_ = 0ULL;
v___x_3923_ = lean_uint64_dec_eq(v___x_3921_, v___x_3922_);
if (v___x_3923_ == 0)
{
uint64_t v___x_3924_; 
v___x_3924_ = lean_uint64_add(v___y_3918_, v___y_3917_);
v___y_3910_ = v___y_3920_;
v___y_3911_ = v___x_3924_;
goto v___jp_3909_;
}
else
{
v___y_3910_ = v___y_3920_;
v___y_3911_ = v___y_3918_;
goto v___jp_3909_;
}
}
v___jp_3925_:
{
uint64_t v___x_3928_; uint64_t v___x_3929_; uint64_t v___x_3930_; uint8_t v___x_3931_; 
v___x_3928_ = 4ULL;
v___x_3929_ = lean_uint64_shift_right(v___y_3926_, v___x_3928_);
v___x_3930_ = 0ULL;
v___x_3931_ = lean_uint64_dec_eq(v___x_3929_, v___x_3930_);
if (v___x_3931_ == 0)
{
v___y_3917_ = v___x_3928_;
v___y_3918_ = v___y_3927_;
v___y_3919_ = v___y_3926_;
v___y_3920_ = v___x_3929_;
goto v___jp_3916_;
}
else
{
v___y_3917_ = v___x_3928_;
v___y_3918_ = v___y_3927_;
v___y_3919_ = v___y_3926_;
v___y_3920_ = v___y_3926_;
goto v___jp_3916_;
}
}
v___jp_3932_:
{
uint64_t v___x_3937_; uint64_t v___x_3938_; uint8_t v___x_3939_; 
v___x_3937_ = lean_uint64_shift_right(v___y_3933_, v___y_3934_);
v___x_3938_ = 0ULL;
v___x_3939_ = lean_uint64_dec_eq(v___x_3937_, v___x_3938_);
if (v___x_3939_ == 0)
{
uint64_t v___x_3940_; 
v___x_3940_ = lean_uint64_add(v___y_3935_, v___y_3934_);
v___y_3926_ = v___y_3936_;
v___y_3927_ = v___x_3940_;
goto v___jp_3925_;
}
else
{
v___y_3926_ = v___y_3936_;
v___y_3927_ = v___y_3935_;
goto v___jp_3925_;
}
}
v___jp_3941_:
{
uint64_t v___x_3944_; uint64_t v___x_3945_; uint64_t v___x_3946_; uint8_t v___x_3947_; 
v___x_3944_ = 8ULL;
v___x_3945_ = lean_uint64_shift_right(v___y_3942_, v___x_3944_);
v___x_3946_ = 0ULL;
v___x_3947_ = lean_uint64_dec_eq(v___x_3945_, v___x_3946_);
if (v___x_3947_ == 0)
{
v___y_3933_ = v___y_3942_;
v___y_3934_ = v___x_3944_;
v___y_3935_ = v___y_3943_;
v___y_3936_ = v___x_3945_;
goto v___jp_3932_;
}
else
{
v___y_3933_ = v___y_3942_;
v___y_3934_ = v___x_3944_;
v___y_3935_ = v___y_3943_;
v___y_3936_ = v___y_3942_;
goto v___jp_3932_;
}
}
v___jp_3948_:
{
uint64_t v___x_3953_; uint64_t v___x_3954_; uint8_t v___x_3955_; 
v___x_3953_ = lean_uint64_shift_right(v___y_3949_, v___y_3950_);
v___x_3954_ = 0ULL;
v___x_3955_ = lean_uint64_dec_eq(v___x_3953_, v___x_3954_);
if (v___x_3955_ == 0)
{
uint64_t v___x_3956_; 
v___x_3956_ = lean_uint64_add(v___y_3951_, v___y_3950_);
v___y_3942_ = v___y_3952_;
v___y_3943_ = v___x_3956_;
goto v___jp_3941_;
}
else
{
v___y_3942_ = v___y_3952_;
v___y_3943_ = v___y_3951_;
goto v___jp_3941_;
}
}
v___jp_3957_:
{
uint64_t v___x_3960_; uint64_t v___x_3961_; uint64_t v___x_3962_; uint8_t v___x_3963_; 
v___x_3960_ = 16ULL;
v___x_3961_ = lean_uint64_shift_right(v___y_3958_, v___x_3960_);
v___x_3962_ = 0ULL;
v___x_3963_ = lean_uint64_dec_eq(v___x_3961_, v___x_3962_);
if (v___x_3963_ == 0)
{
v___y_3949_ = v___y_3958_;
v___y_3950_ = v___x_3960_;
v___y_3951_ = v___y_3959_;
v___y_3952_ = v___x_3961_;
goto v___jp_3948_;
}
else
{
v___y_3949_ = v___y_3958_;
v___y_3950_ = v___x_3960_;
v___y_3951_ = v___y_3959_;
v___y_3952_ = v___y_3958_;
goto v___jp_3948_;
}
}
}
}
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_R24ExactDotCost_fastEligible___boxed(lean_object* v_c_3977_){
_start:
{
uint8_t v_res_3978_; lean_object* v_r_3979_; 
v_res_3978_ = lp_competition_Submission_R24ExactDotCost_fastEligible(v_c_3977_);
lean_dec_ref(v_c_3977_);
v_r_3979_ = lean_box(v_res_3978_);
return v_r_3979_;
}
}
LEAN_EXPORT uint32_t lp_competition_Submission_R24ExactDotCost_signWord(uint8_t v_negative_3980_){
_start:
{
if (v_negative_3980_ == 0)
{
uint32_t v___x_3981_; 
v___x_3981_ = 0;
return v___x_3981_;
}
else
{
uint32_t v___x_3982_; 
v___x_3982_ = 2147483648;
return v___x_3982_;
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_R24ExactDotCost_signWord___boxed(lean_object* v_negative_3983_){
_start:
{
uint8_t v_negative_boxed_3984_; uint32_t v_res_3985_; lean_object* v_r_3986_; 
v_negative_boxed_3984_ = lean_unbox(v_negative_3983_);
v_res_3985_ = lp_competition_Submission_R24ExactDotCost_signWord(v_negative_boxed_3984_);
v_r_3986_ = lean_box_uint32(v_res_3985_);
return v_r_3986_;
}
}
LEAN_EXPORT uint32_t lp_competition_Submission_R24ExactDotCost_pack(uint8_t v_negative_3987_, uint32_t v_exponent_3988_, uint32_t v_fraction_3989_){
_start:
{
uint32_t v___y_3991_; 
if (v_negative_3987_ == 0)
{
uint32_t v___x_3996_; 
v___x_3996_ = 0;
v___y_3991_ = v___x_3996_;
goto v___jp_3990_;
}
else
{
uint32_t v___x_3997_; 
v___x_3997_ = 2147483648;
v___y_3991_ = v___x_3997_;
goto v___jp_3990_;
}
v___jp_3990_:
{
uint32_t v___x_3992_; uint32_t v___x_3993_; uint32_t v___x_3994_; uint32_t v___x_3995_; 
v___x_3992_ = 23;
v___x_3993_ = lean_uint32_shift_left(v_exponent_3988_, v___x_3992_);
v___x_3994_ = lean_uint32_lor(v___y_3991_, v___x_3993_);
v___x_3995_ = lean_uint32_lor(v___x_3994_, v_fraction_3989_);
return v___x_3995_;
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_R24ExactDotCost_pack___boxed(lean_object* v_negative_3998_, lean_object* v_exponent_3999_, lean_object* v_fraction_4000_){
_start:
{
uint8_t v_negative_boxed_4001_; uint32_t v_exponent_boxed_4002_; uint32_t v_fraction_boxed_4003_; uint32_t v_res_4004_; lean_object* v_r_4005_; 
v_negative_boxed_4001_ = lean_unbox(v_negative_3998_);
v_exponent_boxed_4002_ = lean_unbox_uint32(v_exponent_3999_);
lean_dec(v_exponent_3999_);
v_fraction_boxed_4003_ = lean_unbox_uint32(v_fraction_4000_);
lean_dec(v_fraction_4000_);
v_res_4004_ = lp_competition_Submission_R24ExactDotCost_pack(v_negative_boxed_4001_, v_exponent_boxed_4002_, v_fraction_boxed_4003_);
v_r_4005_ = lean_box_uint32(v_res_4004_);
return v_r_4005_;
}
}
LEAN_EXPORT uint64_t lp_competition_Submission_R24ExactDotCost_quotientLo(uint64_t v_lo_4006_, uint64_t v_hi_4007_, uint64_t v_shift_4008_){
_start:
{
uint64_t v___x_4009_; uint8_t v___x_4010_; 
v___x_4009_ = 0ULL;
v___x_4010_ = lean_uint64_dec_eq(v_shift_4008_, v___x_4009_);
if (v___x_4010_ == 0)
{
uint64_t v___x_4011_; uint8_t v___x_4012_; 
v___x_4011_ = 64ULL;
v___x_4012_ = lean_uint64_dec_lt(v_shift_4008_, v___x_4011_);
if (v___x_4012_ == 0)
{
uint8_t v___x_4013_; 
v___x_4013_ = lean_uint64_dec_eq(v_shift_4008_, v___x_4011_);
if (v___x_4013_ == 0)
{
uint64_t v___x_4014_; uint8_t v___x_4015_; 
v___x_4014_ = 128ULL;
v___x_4015_ = lean_uint64_dec_lt(v_shift_4008_, v___x_4014_);
if (v___x_4015_ == 0)
{
return v___x_4009_;
}
else
{
uint64_t v___x_4016_; uint64_t v___x_4017_; 
v___x_4016_ = lean_uint64_sub(v_shift_4008_, v___x_4011_);
v___x_4017_ = lean_uint64_shift_right(v_hi_4007_, v___x_4016_);
return v___x_4017_;
}
}
else
{
return v_hi_4007_;
}
}
else
{
uint64_t v___x_4018_; uint64_t v___x_4019_; uint64_t v___x_4020_; uint64_t v___x_4021_; 
v___x_4018_ = lean_uint64_shift_right(v_lo_4006_, v_shift_4008_);
v___x_4019_ = lean_uint64_sub(v___x_4011_, v_shift_4008_);
v___x_4020_ = lean_uint64_shift_left(v_hi_4007_, v___x_4019_);
v___x_4021_ = lean_uint64_lor(v___x_4018_, v___x_4020_);
return v___x_4021_;
}
}
else
{
return v_lo_4006_;
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_R24ExactDotCost_quotientLo___boxed(lean_object* v_lo_4022_, lean_object* v_hi_4023_, lean_object* v_shift_4024_){
_start:
{
uint64_t v_lo_boxed_4025_; uint64_t v_hi_boxed_4026_; uint64_t v_shift_boxed_4027_; uint64_t v_res_4028_; lean_object* v_r_4029_; 
v_lo_boxed_4025_ = lean_unbox_uint64(v_lo_4022_);
lean_dec_ref(v_lo_4022_);
v_hi_boxed_4026_ = lean_unbox_uint64(v_hi_4023_);
lean_dec_ref(v_hi_4023_);
v_shift_boxed_4027_ = lean_unbox_uint64(v_shift_4024_);
lean_dec_ref(v_shift_4024_);
v_res_4028_ = lp_competition_Submission_R24ExactDotCost_quotientLo(v_lo_boxed_4025_, v_hi_boxed_4026_, v_shift_boxed_4027_);
v_r_4029_ = lean_box_uint64(v_res_4028_);
return v_r_4029_;
}
}
LEAN_EXPORT uint64_t lp_competition_Submission_R24ExactDotCost_roundRight128(uint64_t v_lo_4030_, uint64_t v_hi_4031_, uint64_t v_shift_4032_){
_start:
{
uint64_t v___y_4034_; uint64_t v___x_4037_; uint8_t v___y_4039_; uint64_t v___y_4040_; uint8_t v___y_4041_; uint8_t v___x_4045_; 
v___x_4037_ = 0ULL;
v___x_4045_ = lean_uint64_dec_eq(v_shift_4032_, v___x_4037_);
if (v___x_4045_ == 0)
{
uint64_t v___x_4046_; uint8_t v___x_4047_; 
v___x_4046_ = 128ULL;
v___x_4047_ = lean_uint64_dec_lt(v___x_4046_, v_shift_4032_);
if (v___x_4047_ == 0)
{
uint8_t v___x_4048_; uint8_t v___y_4050_; uint64_t v___y_4051_; uint8_t v___y_4052_; uint64_t v___y_4068_; 
v___x_4048_ = 1;
if (v___x_4045_ == 0)
{
uint64_t v___x_4082_; uint8_t v___x_4083_; 
v___x_4082_ = 64ULL;
v___x_4083_ = lean_uint64_dec_lt(v_shift_4032_, v___x_4082_);
if (v___x_4083_ == 0)
{
uint8_t v___x_4084_; 
v___x_4084_ = lean_uint64_dec_eq(v_shift_4032_, v___x_4082_);
if (v___x_4084_ == 0)
{
uint8_t v___x_4085_; 
v___x_4085_ = lean_uint64_dec_lt(v_shift_4032_, v___x_4046_);
if (v___x_4085_ == 0)
{
v___y_4068_ = v___x_4037_;
goto v___jp_4067_;
}
else
{
uint64_t v___x_4086_; uint64_t v___x_4087_; 
v___x_4086_ = lean_uint64_sub(v_shift_4032_, v___x_4082_);
v___x_4087_ = lean_uint64_shift_right(v_hi_4031_, v___x_4086_);
v___y_4068_ = v___x_4087_;
goto v___jp_4067_;
}
}
else
{
v___y_4068_ = v_hi_4031_;
goto v___jp_4067_;
}
}
else
{
uint64_t v___x_4088_; uint64_t v___x_4089_; uint64_t v___x_4090_; uint64_t v___x_4091_; 
v___x_4088_ = lean_uint64_shift_right(v_lo_4030_, v_shift_4032_);
v___x_4089_ = lean_uint64_sub(v___x_4082_, v_shift_4032_);
v___x_4090_ = lean_uint64_shift_left(v_hi_4031_, v___x_4089_);
v___x_4091_ = lean_uint64_lor(v___x_4088_, v___x_4090_);
v___y_4068_ = v___x_4091_;
goto v___jp_4067_;
}
}
else
{
v___y_4068_ = v_lo_4030_;
goto v___jp_4067_;
}
v___jp_4049_:
{
if (v___y_4050_ == 0)
{
uint8_t v___x_4053_; 
v___x_4053_ = lean_uint64_dec_eq(v_lo_4030_, v___x_4037_);
if (v___x_4053_ == 0)
{
v___y_4039_ = v___y_4052_;
v___y_4040_ = v___y_4051_;
v___y_4041_ = v___x_4048_;
goto v___jp_4038_;
}
else
{
uint64_t v___x_4054_; uint64_t v___x_4055_; uint64_t v___x_4056_; uint64_t v___x_4057_; uint64_t v___x_4058_; uint64_t v___x_4059_; uint8_t v___x_4060_; 
v___x_4054_ = 1ULL;
v___x_4055_ = 65ULL;
v___x_4056_ = lean_uint64_sub(v_shift_4032_, v___x_4055_);
v___x_4057_ = lean_uint64_shift_left(v___x_4054_, v___x_4056_);
v___x_4058_ = lean_uint64_sub(v___x_4057_, v___x_4054_);
v___x_4059_ = lean_uint64_land(v_hi_4031_, v___x_4058_);
v___x_4060_ = lean_uint64_dec_eq(v___x_4059_, v___x_4037_);
if (v___x_4060_ == 0)
{
v___y_4039_ = v___y_4052_;
v___y_4040_ = v___y_4051_;
v___y_4041_ = v___x_4053_;
goto v___jp_4038_;
}
else
{
v___y_4039_ = v___y_4052_;
v___y_4040_ = v___y_4051_;
v___y_4041_ = v___x_4045_;
goto v___jp_4038_;
}
}
}
else
{
uint64_t v___x_4061_; uint64_t v___x_4062_; uint64_t v___x_4063_; uint64_t v___x_4064_; uint64_t v___x_4065_; uint8_t v___x_4066_; 
v___x_4061_ = 1ULL;
v___x_4062_ = lean_uint64_sub(v_shift_4032_, v___x_4061_);
v___x_4063_ = lean_uint64_shift_left(v___x_4061_, v___x_4062_);
v___x_4064_ = lean_uint64_sub(v___x_4063_, v___x_4061_);
v___x_4065_ = lean_uint64_land(v_lo_4030_, v___x_4064_);
v___x_4066_ = lean_uint64_dec_eq(v___x_4065_, v___x_4037_);
if (v___x_4066_ == 0)
{
v___y_4039_ = v___y_4052_;
v___y_4040_ = v___y_4051_;
v___y_4041_ = v___x_4048_;
goto v___jp_4038_;
}
else
{
v___y_4039_ = v___y_4052_;
v___y_4040_ = v___y_4051_;
v___y_4041_ = v___x_4045_;
goto v___jp_4038_;
}
}
}
v___jp_4067_:
{
uint64_t v___x_4069_; uint8_t v___x_4070_; 
v___x_4069_ = 64ULL;
v___x_4070_ = lean_uint64_dec_le(v_shift_4032_, v___x_4069_);
if (v___x_4070_ == 0)
{
uint64_t v___x_4071_; uint64_t v___x_4072_; uint64_t v___x_4073_; uint64_t v___x_4074_; uint64_t v___x_4075_; uint8_t v___x_4076_; 
v___x_4071_ = 65ULL;
v___x_4072_ = lean_uint64_sub(v_shift_4032_, v___x_4071_);
v___x_4073_ = lean_uint64_shift_right(v_hi_4031_, v___x_4072_);
v___x_4074_ = 1ULL;
v___x_4075_ = lean_uint64_land(v___x_4073_, v___x_4074_);
v___x_4076_ = lean_uint64_dec_eq(v___x_4075_, v___x_4037_);
if (v___x_4076_ == 0)
{
v___y_4050_ = v___x_4070_;
v___y_4051_ = v___y_4068_;
v___y_4052_ = v___x_4048_;
goto v___jp_4049_;
}
else
{
v___y_4050_ = v___x_4070_;
v___y_4051_ = v___y_4068_;
v___y_4052_ = v___x_4045_;
goto v___jp_4049_;
}
}
else
{
uint64_t v___x_4077_; uint64_t v___x_4078_; uint64_t v___x_4079_; uint64_t v___x_4080_; uint8_t v___x_4081_; 
v___x_4077_ = 1ULL;
v___x_4078_ = lean_uint64_sub(v_shift_4032_, v___x_4077_);
v___x_4079_ = lean_uint64_shift_right(v_lo_4030_, v___x_4078_);
v___x_4080_ = lean_uint64_land(v___x_4079_, v___x_4077_);
v___x_4081_ = lean_uint64_dec_eq(v___x_4080_, v___x_4037_);
if (v___x_4081_ == 0)
{
v___y_4050_ = v___x_4070_;
v___y_4051_ = v___y_4068_;
v___y_4052_ = v___x_4048_;
goto v___jp_4049_;
}
else
{
v___y_4050_ = v___x_4070_;
v___y_4051_ = v___y_4068_;
v___y_4052_ = v___x_4045_;
goto v___jp_4049_;
}
}
}
}
else
{
return v___x_4037_;
}
}
else
{
return v_lo_4030_;
}
v___jp_4033_:
{
uint64_t v___x_4035_; uint64_t v___x_4036_; 
v___x_4035_ = 1ULL;
v___x_4036_ = lean_uint64_add(v___y_4034_, v___x_4035_);
return v___x_4036_;
}
v___jp_4038_:
{
if (v___y_4039_ == 0)
{
return v___y_4040_;
}
else
{
if (v___y_4041_ == 0)
{
uint64_t v___x_4042_; uint64_t v___x_4043_; uint8_t v___x_4044_; 
v___x_4042_ = 1ULL;
v___x_4043_ = lean_uint64_land(v___y_4040_, v___x_4042_);
v___x_4044_ = lean_uint64_dec_eq(v___x_4043_, v___x_4037_);
if (v___x_4044_ == 0)
{
v___y_4034_ = v___y_4040_;
goto v___jp_4033_;
}
else
{
return v___y_4040_;
}
}
else
{
v___y_4034_ = v___y_4040_;
goto v___jp_4033_;
}
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_R24ExactDotCost_roundRight128___boxed(lean_object* v_lo_4092_, lean_object* v_hi_4093_, lean_object* v_shift_4094_){
_start:
{
uint64_t v_lo_boxed_4095_; uint64_t v_hi_boxed_4096_; uint64_t v_shift_boxed_4097_; uint64_t v_res_4098_; lean_object* v_r_4099_; 
v_lo_boxed_4095_ = lean_unbox_uint64(v_lo_4092_);
lean_dec_ref(v_lo_4092_);
v_hi_boxed_4096_ = lean_unbox_uint64(v_hi_4093_);
lean_dec_ref(v_hi_4093_);
v_shift_boxed_4097_ = lean_unbox_uint64(v_shift_4094_);
lean_dec_ref(v_shift_4094_);
v_res_4098_ = lp_competition_Submission_R24ExactDotCost_roundRight128(v_lo_boxed_4095_, v_hi_boxed_4096_, v_shift_boxed_4097_);
v_r_4099_ = lean_box_uint64(v_res_4098_);
return v_r_4099_;
}
}
static lean_object* _init_lp_competition_Submission_R24ExactDotCost_round128___closed__0(void){
_start:
{
lean_object* v___x_4100_; lean_object* v___x_4101_; 
v___x_4100_ = lean_unsigned_to_nat(255u);
v___x_4101_ = lean_nat_to_int(v___x_4100_);
return v___x_4101_;
}
}
static lean_object* _init_lp_competition_Submission_R24ExactDotCost_round128___closed__1(void){
_start:
{
lean_object* v___x_4102_; lean_object* v___x_4103_; 
v___x_4102_ = lean_unsigned_to_nat(150u);
v___x_4103_ = lean_nat_to_int(v___x_4102_);
return v___x_4103_;
}
}
static lean_object* _init_lp_competition_Submission_R24ExactDotCost_round128___closed__2(void){
_start:
{
lean_object* v___x_4104_; lean_object* v___x_4105_; 
v___x_4104_ = lean_unsigned_to_nat(1u);
v___x_4105_ = lean_nat_to_int(v___x_4104_);
return v___x_4105_;
}
}
static lean_object* _init_lp_competition_Submission_R24ExactDotCost_round128___closed__3(void){
_start:
{
lean_object* v___x_4106_; lean_object* v___x_4107_; 
v___x_4106_ = lean_unsigned_to_nat(0u);
v___x_4107_ = lean_nat_to_int(v___x_4106_);
return v___x_4107_;
}
}
static lean_object* _init_lp_competition_Submission_R24ExactDotCost_round128___closed__4(void){
_start:
{
lean_object* v___x_4108_; lean_object* v___x_4109_; 
v___x_4108_ = lean_unsigned_to_nat(128u);
v___x_4109_ = lean_nat_to_int(v___x_4108_);
return v___x_4109_;
}
}
static lean_object* _init_lp_competition_Submission_R24ExactDotCost_round128___closed__5(void){
_start:
{
lean_object* v___x_4110_; lean_object* v___x_4111_; 
v___x_4110_ = lean_unsigned_to_nat(127u);
v___x_4111_ = lean_nat_to_int(v___x_4110_);
return v___x_4111_;
}
}
static lean_object* _init_lp_competition_Submission_R24ExactDotCost_round128___closed__6(void){
_start:
{
lean_object* v___x_4112_; lean_object* v___x_4113_; 
v___x_4112_ = lean_unsigned_to_nat(23u);
v___x_4113_ = lean_nat_to_int(v___x_4112_);
return v___x_4113_;
}
}
static lean_object* _init_lp_competition_Submission_R24ExactDotCost_round128___closed__7(void){
_start:
{
lean_object* v___x_4114_; lean_object* v___x_4115_; 
v___x_4114_ = lean_unsigned_to_nat(149u);
v___x_4115_ = lean_nat_to_int(v___x_4114_);
return v___x_4115_;
}
}
static lean_object* _init_lp_competition_Submission_R24ExactDotCost_round128___closed__8(void){
_start:
{
lean_object* v___x_4116_; lean_object* v___x_4117_; 
v___x_4116_ = lean_obj_once(&lp_competition_Submission_R24ExactDotCost_round128___closed__7, &lp_competition_Submission_R24ExactDotCost_round128___closed__7_once, _init_lp_competition_Submission_R24ExactDotCost_round128___closed__7);
v___x_4117_ = lean_int_neg(v___x_4116_);
return v___x_4117_;
}
}
LEAN_EXPORT uint32_t lp_competition_Submission_R24ExactDotCost_round128(uint8_t v_negative_4118_, uint64_t v_lo_4119_, uint64_t v_hi_4120_, lean_object* v_base_4121_){
_start:
{
uint32_t v___y_4123_; uint32_t v___y_4127_; uint32_t v___y_4131_; uint32_t v___y_4132_; uint32_t v___y_4133_; lean_object* v___y_4139_; uint64_t v___y_4140_; lean_object* v___y_4141_; lean_object* v___y_4159_; uint8_t v___y_4160_; lean_object* v___y_4161_; uint64_t v___y_4162_; lean_object* v___y_4167_; lean_object* v___y_4168_; uint64_t v___y_4169_; lean_object* v___y_4175_; lean_object* v___y_4176_; uint64_t v___y_4177_; uint64_t v___x_4180_; lean_object* v___y_4182_; uint8_t v___y_4183_; lean_object* v___y_4184_; uint64_t v___y_4185_; uint8_t v___y_4186_; lean_object* v___y_4191_; uint64_t v___y_4192_; uint8_t v___y_4193_; uint8_t v___y_4194_; uint8_t v___y_4195_; uint64_t v___y_4196_; lean_object* v___y_4197_; uint8_t v___y_4198_; lean_object* v___y_4214_; uint64_t v___y_4215_; uint8_t v___y_4216_; uint8_t v___y_4217_; lean_object* v___y_4218_; uint64_t v___y_4219_; lean_object* v___y_4234_; lean_object* v___y_4261_; uint64_t v___y_4273_; uint64_t v___y_4276_; uint64_t v___y_4277_; uint64_t v___y_4283_; uint64_t v___y_4284_; uint64_t v___y_4285_; uint64_t v___y_4286_; uint64_t v___y_4291_; uint64_t v___y_4292_; uint64_t v___y_4297_; uint64_t v___y_4298_; uint64_t v___y_4299_; uint64_t v___y_4300_; uint64_t v___y_4305_; uint64_t v___y_4306_; uint64_t v___y_4311_; uint64_t v___y_4312_; uint64_t v___y_4313_; uint64_t v___y_4314_; uint64_t v___y_4319_; uint64_t v___y_4320_; uint64_t v___y_4325_; uint64_t v___y_4326_; uint64_t v___y_4327_; uint64_t v___y_4328_; uint64_t v___y_4333_; uint64_t v___y_4334_; uint64_t v___y_4339_; uint64_t v___y_4340_; lean_object* v___y_4344_; uint64_t v___y_4345_; lean_object* v___y_4349_; uint64_t v___y_4350_; uint64_t v___y_4351_; uint64_t v___y_4357_; uint64_t v___y_4358_; lean_object* v___y_4359_; uint64_t v___y_4360_; uint64_t v___y_4361_; lean_object* v___y_4366_; uint64_t v___y_4367_; uint64_t v___y_4368_; uint64_t v___y_4373_; uint64_t v___y_4374_; lean_object* v___y_4375_; uint64_t v___y_4376_; uint64_t v___y_4377_; uint64_t v___y_4382_; lean_object* v___y_4383_; uint64_t v___y_4384_; uint64_t v___y_4389_; uint64_t v___y_4390_; lean_object* v___y_4391_; uint64_t v___y_4392_; uint64_t v___y_4393_; uint64_t v___y_4398_; lean_object* v___y_4399_; uint64_t v___y_4400_; uint64_t v___y_4405_; uint64_t v___y_4406_; uint64_t v___y_4407_; lean_object* v___y_4408_; uint64_t v___y_4409_; uint64_t v___y_4414_; lean_object* v___y_4415_; uint64_t v___y_4416_; lean_object* v___y_4421_; uint64_t v___y_4422_; uint64_t v___y_4423_; uint8_t v___y_4427_; uint8_t v___x_4438_; 
v___x_4180_ = 0ULL;
v___x_4438_ = lean_uint64_dec_eq(v_lo_4119_, v___x_4180_);
if (v___x_4438_ == 0)
{
v___y_4427_ = v___x_4438_;
goto v___jp_4426_;
}
else
{
uint8_t v___x_4439_; 
v___x_4439_ = lean_uint64_dec_eq(v_hi_4120_, v___x_4180_);
v___y_4427_ = v___x_4439_;
goto v___jp_4426_;
}
v___jp_4122_:
{
uint32_t v___x_4124_; uint32_t v___x_4125_; 
v___x_4124_ = 2139095040;
v___x_4125_ = lean_uint32_lor(v___y_4123_, v___x_4124_);
return v___x_4125_;
}
v___jp_4126_:
{
uint32_t v___x_4128_; uint32_t v___x_4129_; 
v___x_4128_ = 2139095040;
v___x_4129_ = lean_uint32_lor(v___y_4127_, v___x_4128_);
return v___x_4129_;
}
v___jp_4130_:
{
uint32_t v___x_4134_; uint32_t v___x_4135_; uint32_t v___x_4136_; uint32_t v___x_4137_; 
v___x_4134_ = 23;
v___x_4135_ = lean_uint32_shift_left(v___y_4131_, v___x_4134_);
v___x_4136_ = lean_uint32_lor(v___y_4133_, v___x_4135_);
v___x_4137_ = lean_uint32_lor(v___x_4136_, v___y_4132_);
return v___x_4137_;
}
v___jp_4138_:
{
uint64_t v___x_4142_; uint8_t v___x_4143_; 
v___x_4142_ = 8388608ULL;
v___x_4143_ = lean_uint64_dec_lt(v___y_4140_, v___x_4142_);
if (v___x_4143_ == 0)
{
lean_object* v_encoded_4144_; lean_object* v___x_4145_; uint8_t v___x_4146_; 
v_encoded_4144_ = lean_int_add(v___y_4139_, v___y_4141_);
lean_dec(v___y_4139_);
v___x_4145_ = lean_obj_once(&lp_competition_Submission_R24ExactDotCost_round128___closed__0, &lp_competition_Submission_R24ExactDotCost_round128___closed__0_once, _init_lp_competition_Submission_R24ExactDotCost_round128___closed__0);
v___x_4146_ = lean_int_dec_le(v___x_4145_, v_encoded_4144_);
if (v___x_4146_ == 0)
{
lean_object* v___x_4147_; uint32_t v___x_4148_; uint64_t v___x_4149_; uint32_t v___x_4150_; 
v___x_4147_ = l_Int_toNat(v_encoded_4144_);
lean_dec(v_encoded_4144_);
v___x_4148_ = lean_uint32_of_nat(v___x_4147_);
lean_dec(v___x_4147_);
v___x_4149_ = lean_uint64_sub(v___y_4140_, v___x_4142_);
v___x_4150_ = lean_uint64_to_uint32(v___x_4149_);
if (v_negative_4118_ == 0)
{
uint32_t v___x_4151_; 
v___x_4151_ = 0;
v___y_4131_ = v___x_4148_;
v___y_4132_ = v___x_4150_;
v___y_4133_ = v___x_4151_;
goto v___jp_4130_;
}
else
{
uint32_t v___x_4152_; 
v___x_4152_ = 2147483648;
v___y_4131_ = v___x_4148_;
v___y_4132_ = v___x_4150_;
v___y_4133_ = v___x_4152_;
goto v___jp_4130_;
}
}
else
{
lean_dec(v_encoded_4144_);
if (v_negative_4118_ == 0)
{
uint32_t v___x_4153_; 
v___x_4153_ = 0;
v___y_4123_ = v___x_4153_;
goto v___jp_4122_;
}
else
{
uint32_t v___x_4154_; 
v___x_4154_ = 2147483648;
v___y_4123_ = v___x_4154_;
goto v___jp_4122_;
}
}
}
else
{
uint32_t v___x_4155_; 
lean_dec(v___y_4139_);
v___x_4155_ = lean_uint64_to_uint32(v___y_4140_);
if (v_negative_4118_ == 0)
{
return v___x_4155_;
}
else
{
uint32_t v___x_4156_; uint32_t v___x_4157_; 
v___x_4156_ = 2147483648;
v___x_4157_ = lean_uint32_lor(v___x_4156_, v___x_4155_);
return v___x_4157_;
}
}
}
v___jp_4158_:
{
lean_object* v___x_4163_; lean_object* v___x_4164_; 
v___x_4163_ = lean_obj_once(&lp_competition_Submission_R24ExactDotCost_round128___closed__1, &lp_competition_Submission_R24ExactDotCost_round128___closed__1_once, _init_lp_competition_Submission_R24ExactDotCost_round128___closed__1);
v___x_4164_ = lean_int_add(v___y_4161_, v___x_4163_);
lean_dec(v___y_4161_);
if (v___y_4160_ == 0)
{
v___y_4139_ = v___x_4164_;
v___y_4140_ = v___y_4162_;
v___y_4141_ = v___y_4159_;
goto v___jp_4138_;
}
else
{
lean_object* v___x_4165_; 
v___x_4165_ = lean_obj_once(&lp_competition_Submission_R24ExactDotCost_round128___closed__2, &lp_competition_Submission_R24ExactDotCost_round128___closed__2_once, _init_lp_competition_Submission_R24ExactDotCost_round128___closed__2);
v___y_4139_ = v___x_4164_;
v___y_4140_ = v___y_4162_;
v___y_4141_ = v___x_4165_;
goto v___jp_4138_;
}
}
v___jp_4166_:
{
uint64_t v___x_4170_; uint8_t v_carry_4171_; 
v___x_4170_ = 16777216ULL;
v_carry_4171_ = lean_uint64_dec_eq(v___y_4169_, v___x_4170_);
if (v_carry_4171_ == 0)
{
v___y_4159_ = v___y_4167_;
v___y_4160_ = v_carry_4171_;
v___y_4161_ = v___y_4168_;
v___y_4162_ = v___y_4169_;
goto v___jp_4158_;
}
else
{
uint64_t v___x_4172_; uint64_t v___x_4173_; 
v___x_4172_ = 1ULL;
v___x_4173_ = lean_uint64_shift_right(v___y_4169_, v___x_4172_);
v___y_4159_ = v___y_4167_;
v___y_4160_ = v_carry_4171_;
v___y_4161_ = v___y_4168_;
v___y_4162_ = v___x_4173_;
goto v___jp_4158_;
}
}
v___jp_4174_:
{
uint64_t v___x_4178_; uint64_t v___x_4179_; 
v___x_4178_ = 1ULL;
v___x_4179_ = lean_uint64_add(v___y_4177_, v___x_4178_);
v___y_4167_ = v___y_4175_;
v___y_4168_ = v___y_4176_;
v___y_4169_ = v___x_4179_;
goto v___jp_4166_;
}
v___jp_4181_:
{
if (v___y_4183_ == 0)
{
v___y_4167_ = v___y_4182_;
v___y_4168_ = v___y_4184_;
v___y_4169_ = v___y_4185_;
goto v___jp_4166_;
}
else
{
if (v___y_4186_ == 0)
{
uint64_t v___x_4187_; uint64_t v___x_4188_; uint8_t v___x_4189_; 
v___x_4187_ = 1ULL;
v___x_4188_ = lean_uint64_land(v___y_4185_, v___x_4187_);
v___x_4189_ = lean_uint64_dec_eq(v___x_4188_, v___x_4180_);
if (v___x_4189_ == 0)
{
v___y_4175_ = v___y_4182_;
v___y_4176_ = v___y_4184_;
v___y_4177_ = v___y_4185_;
goto v___jp_4174_;
}
else
{
v___y_4167_ = v___y_4182_;
v___y_4168_ = v___y_4184_;
v___y_4169_ = v___y_4185_;
goto v___jp_4166_;
}
}
else
{
v___y_4175_ = v___y_4182_;
v___y_4176_ = v___y_4184_;
v___y_4177_ = v___y_4185_;
goto v___jp_4174_;
}
}
}
v___jp_4190_:
{
if (v___y_4195_ == 0)
{
uint8_t v___x_4199_; 
v___x_4199_ = lean_uint64_dec_eq(v_lo_4119_, v___x_4180_);
if (v___x_4199_ == 0)
{
v___y_4182_ = v___y_4191_;
v___y_4183_ = v___y_4198_;
v___y_4184_ = v___y_4197_;
v___y_4185_ = v___y_4196_;
v___y_4186_ = v___y_4193_;
goto v___jp_4181_;
}
else
{
uint64_t v___x_4200_; uint64_t v___x_4201_; uint64_t v___x_4202_; uint64_t v___x_4203_; uint64_t v___x_4204_; uint64_t v___x_4205_; uint8_t v___x_4206_; 
v___x_4200_ = 1ULL;
v___x_4201_ = 65ULL;
v___x_4202_ = lean_uint64_sub(v___y_4192_, v___x_4201_);
v___x_4203_ = lean_uint64_shift_left(v___x_4200_, v___x_4202_);
v___x_4204_ = lean_uint64_sub(v___x_4203_, v___x_4200_);
v___x_4205_ = lean_uint64_land(v_hi_4120_, v___x_4204_);
v___x_4206_ = lean_uint64_dec_eq(v___x_4205_, v___x_4180_);
if (v___x_4206_ == 0)
{
v___y_4182_ = v___y_4191_;
v___y_4183_ = v___y_4198_;
v___y_4184_ = v___y_4197_;
v___y_4185_ = v___y_4196_;
v___y_4186_ = v___x_4199_;
goto v___jp_4181_;
}
else
{
v___y_4182_ = v___y_4191_;
v___y_4183_ = v___y_4198_;
v___y_4184_ = v___y_4197_;
v___y_4185_ = v___y_4196_;
v___y_4186_ = v___y_4194_;
goto v___jp_4181_;
}
}
}
else
{
uint64_t v___x_4207_; uint64_t v___x_4208_; uint64_t v___x_4209_; uint64_t v___x_4210_; uint64_t v___x_4211_; uint8_t v___x_4212_; 
v___x_4207_ = 1ULL;
v___x_4208_ = lean_uint64_sub(v___y_4192_, v___x_4207_);
v___x_4209_ = lean_uint64_shift_left(v___x_4207_, v___x_4208_);
v___x_4210_ = lean_uint64_sub(v___x_4209_, v___x_4207_);
v___x_4211_ = lean_uint64_land(v_lo_4119_, v___x_4210_);
v___x_4212_ = lean_uint64_dec_eq(v___x_4211_, v___x_4180_);
if (v___x_4212_ == 0)
{
v___y_4182_ = v___y_4191_;
v___y_4183_ = v___y_4198_;
v___y_4184_ = v___y_4197_;
v___y_4185_ = v___y_4196_;
v___y_4186_ = v___y_4193_;
goto v___jp_4181_;
}
else
{
v___y_4182_ = v___y_4191_;
v___y_4183_ = v___y_4198_;
v___y_4184_ = v___y_4197_;
v___y_4185_ = v___y_4196_;
v___y_4186_ = v___y_4194_;
goto v___jp_4181_;
}
}
}
v___jp_4213_:
{
uint64_t v___x_4220_; uint8_t v___x_4221_; 
v___x_4220_ = 64ULL;
v___x_4221_ = lean_uint64_dec_le(v___y_4215_, v___x_4220_);
if (v___x_4221_ == 0)
{
uint64_t v___x_4222_; uint64_t v___x_4223_; uint64_t v___x_4224_; uint64_t v___x_4225_; uint64_t v___x_4226_; uint8_t v___x_4227_; 
v___x_4222_ = 65ULL;
v___x_4223_ = lean_uint64_sub(v___y_4215_, v___x_4222_);
v___x_4224_ = lean_uint64_shift_right(v_hi_4120_, v___x_4223_);
v___x_4225_ = 1ULL;
v___x_4226_ = lean_uint64_land(v___x_4224_, v___x_4225_);
v___x_4227_ = lean_uint64_dec_eq(v___x_4226_, v___x_4180_);
if (v___x_4227_ == 0)
{
v___y_4191_ = v___y_4214_;
v___y_4192_ = v___y_4215_;
v___y_4193_ = v___y_4216_;
v___y_4194_ = v___y_4217_;
v___y_4195_ = v___x_4221_;
v___y_4196_ = v___y_4219_;
v___y_4197_ = v___y_4218_;
v___y_4198_ = v___y_4216_;
goto v___jp_4190_;
}
else
{
v___y_4191_ = v___y_4214_;
v___y_4192_ = v___y_4215_;
v___y_4193_ = v___y_4216_;
v___y_4194_ = v___y_4217_;
v___y_4195_ = v___x_4221_;
v___y_4196_ = v___y_4219_;
v___y_4197_ = v___y_4218_;
v___y_4198_ = v___y_4217_;
goto v___jp_4190_;
}
}
else
{
uint64_t v___x_4228_; uint64_t v___x_4229_; uint64_t v___x_4230_; uint64_t v___x_4231_; uint8_t v___x_4232_; 
v___x_4228_ = 1ULL;
v___x_4229_ = lean_uint64_sub(v___y_4215_, v___x_4228_);
v___x_4230_ = lean_uint64_shift_right(v_lo_4119_, v___x_4229_);
v___x_4231_ = lean_uint64_land(v___x_4230_, v___x_4228_);
v___x_4232_ = lean_uint64_dec_eq(v___x_4231_, v___x_4180_);
if (v___x_4232_ == 0)
{
v___y_4191_ = v___y_4214_;
v___y_4192_ = v___y_4215_;
v___y_4193_ = v___y_4216_;
v___y_4194_ = v___y_4217_;
v___y_4195_ = v___x_4221_;
v___y_4196_ = v___y_4219_;
v___y_4197_ = v___y_4218_;
v___y_4198_ = v___y_4216_;
goto v___jp_4190_;
}
else
{
v___y_4191_ = v___y_4214_;
v___y_4192_ = v___y_4215_;
v___y_4193_ = v___y_4216_;
v___y_4194_ = v___y_4217_;
v___y_4195_ = v___x_4221_;
v___y_4196_ = v___y_4219_;
v___y_4197_ = v___y_4218_;
v___y_4198_ = v___y_4217_;
goto v___jp_4190_;
}
}
}
v___jp_4233_:
{
lean_object* v_delta_4235_; lean_object* v___x_4236_; uint8_t v___x_4237_; 
v_delta_4235_ = lean_int_sub(v___y_4234_, v_base_4121_);
v___x_4236_ = lean_obj_once(&lp_competition_Submission_R24ExactDotCost_round128___closed__3, &lp_competition_Submission_R24ExactDotCost_round128___closed__3_once, _init_lp_competition_Submission_R24ExactDotCost_round128___closed__3);
v___x_4237_ = lean_int_dec_le(v_delta_4235_, v___x_4236_);
if (v___x_4237_ == 0)
{
lean_object* v___x_4238_; uint8_t v___x_4239_; 
v___x_4238_ = lean_obj_once(&lp_competition_Submission_R24ExactDotCost_round128___closed__4, &lp_competition_Submission_R24ExactDotCost_round128___closed__4_once, _init_lp_competition_Submission_R24ExactDotCost_round128___closed__4);
v___x_4239_ = lean_int_dec_lt(v___x_4238_, v_delta_4235_);
if (v___x_4239_ == 0)
{
lean_object* v___x_4240_; uint64_t v___x_4241_; uint8_t v___x_4242_; 
v___x_4240_ = l_Int_toNat(v_delta_4235_);
lean_dec(v_delta_4235_);
v___x_4241_ = lean_uint64_of_nat(v___x_4240_);
lean_dec(v___x_4240_);
v___x_4242_ = lean_uint64_dec_eq(v___x_4241_, v___x_4180_);
if (v___x_4242_ == 0)
{
uint64_t v___x_4243_; uint8_t v___x_4244_; 
v___x_4243_ = 128ULL;
v___x_4244_ = lean_uint64_dec_lt(v___x_4243_, v___x_4241_);
if (v___x_4244_ == 0)
{
uint8_t v___x_4245_; 
v___x_4245_ = 1;
if (v___x_4242_ == 0)
{
uint64_t v___x_4246_; uint8_t v___x_4247_; 
v___x_4246_ = 64ULL;
v___x_4247_ = lean_uint64_dec_lt(v___x_4241_, v___x_4246_);
if (v___x_4247_ == 0)
{
uint8_t v___x_4248_; 
v___x_4248_ = lean_uint64_dec_eq(v___x_4241_, v___x_4246_);
if (v___x_4248_ == 0)
{
uint8_t v___x_4249_; 
v___x_4249_ = lean_uint64_dec_lt(v___x_4241_, v___x_4243_);
if (v___x_4249_ == 0)
{
v___y_4214_ = v___x_4236_;
v___y_4215_ = v___x_4241_;
v___y_4216_ = v___x_4245_;
v___y_4217_ = v___x_4242_;
v___y_4218_ = v___y_4234_;
v___y_4219_ = v___x_4180_;
goto v___jp_4213_;
}
else
{
uint64_t v___x_4250_; uint64_t v___x_4251_; 
v___x_4250_ = lean_uint64_sub(v___x_4241_, v___x_4246_);
v___x_4251_ = lean_uint64_shift_right(v_hi_4120_, v___x_4250_);
v___y_4214_ = v___x_4236_;
v___y_4215_ = v___x_4241_;
v___y_4216_ = v___x_4245_;
v___y_4217_ = v___x_4242_;
v___y_4218_ = v___y_4234_;
v___y_4219_ = v___x_4251_;
goto v___jp_4213_;
}
}
else
{
v___y_4214_ = v___x_4236_;
v___y_4215_ = v___x_4241_;
v___y_4216_ = v___x_4245_;
v___y_4217_ = v___x_4242_;
v___y_4218_ = v___y_4234_;
v___y_4219_ = v_hi_4120_;
goto v___jp_4213_;
}
}
else
{
uint64_t v___x_4252_; uint64_t v___x_4253_; uint64_t v___x_4254_; uint64_t v___x_4255_; 
v___x_4252_ = lean_uint64_shift_right(v_lo_4119_, v___x_4241_);
v___x_4253_ = lean_uint64_sub(v___x_4246_, v___x_4241_);
v___x_4254_ = lean_uint64_shift_left(v_hi_4120_, v___x_4253_);
v___x_4255_ = lean_uint64_lor(v___x_4252_, v___x_4254_);
v___y_4214_ = v___x_4236_;
v___y_4215_ = v___x_4241_;
v___y_4216_ = v___x_4245_;
v___y_4217_ = v___x_4242_;
v___y_4218_ = v___y_4234_;
v___y_4219_ = v___x_4255_;
goto v___jp_4213_;
}
}
else
{
v___y_4214_ = v___x_4236_;
v___y_4215_ = v___x_4241_;
v___y_4216_ = v___x_4245_;
v___y_4217_ = v___x_4242_;
v___y_4218_ = v___y_4234_;
v___y_4219_ = v_lo_4119_;
goto v___jp_4213_;
}
}
else
{
v___y_4167_ = v___x_4236_;
v___y_4168_ = v___y_4234_;
v___y_4169_ = v___x_4180_;
goto v___jp_4166_;
}
}
else
{
v___y_4167_ = v___x_4236_;
v___y_4168_ = v___y_4234_;
v___y_4169_ = v_lo_4119_;
goto v___jp_4166_;
}
}
else
{
lean_dec(v_delta_4235_);
v___y_4167_ = v___x_4236_;
v___y_4168_ = v___y_4234_;
v___y_4169_ = v___x_4180_;
goto v___jp_4166_;
}
}
else
{
lean_object* v___x_4256_; lean_object* v___x_4257_; uint64_t v___x_4258_; uint64_t v___x_4259_; 
v___x_4256_ = lean_int_neg(v_delta_4235_);
lean_dec(v_delta_4235_);
v___x_4257_ = l_Int_toNat(v___x_4256_);
lean_dec(v___x_4256_);
v___x_4258_ = lean_uint64_of_nat(v___x_4257_);
lean_dec(v___x_4257_);
v___x_4259_ = lean_uint64_shift_left(v_lo_4119_, v___x_4258_);
v___y_4167_ = v___x_4236_;
v___y_4168_ = v___y_4234_;
v___y_4169_ = v___x_4259_;
goto v___jp_4166_;
}
}
v___jp_4260_:
{
lean_object* v___x_4262_; lean_object* v_total_4263_; lean_object* v___x_4264_; uint8_t v___x_4265_; 
v___x_4262_ = lean_nat_to_int(v___y_4261_);
v_total_4263_ = lean_int_add(v_base_4121_, v___x_4262_);
lean_dec(v___x_4262_);
v___x_4264_ = lean_obj_once(&lp_competition_Submission_R24ExactDotCost_round128___closed__5, &lp_competition_Submission_R24ExactDotCost_round128___closed__5_once, _init_lp_competition_Submission_R24ExactDotCost_round128___closed__5);
v___x_4265_ = lean_int_dec_lt(v___x_4264_, v_total_4263_);
if (v___x_4265_ == 0)
{
lean_object* v___x_4266_; lean_object* v___x_4267_; lean_object* v___x_4268_; uint8_t v___x_4269_; 
v___x_4266_ = lean_obj_once(&lp_competition_Submission_R24ExactDotCost_round128___closed__6, &lp_competition_Submission_R24ExactDotCost_round128___closed__6_once, _init_lp_competition_Submission_R24ExactDotCost_round128___closed__6);
v___x_4267_ = lean_int_sub(v_total_4263_, v___x_4266_);
lean_dec(v_total_4263_);
v___x_4268_ = lean_obj_once(&lp_competition_Submission_R24ExactDotCost_round128___closed__8, &lp_competition_Submission_R24ExactDotCost_round128___closed__8_once, _init_lp_competition_Submission_R24ExactDotCost_round128___closed__8);
v___x_4269_ = lean_int_dec_le(v___x_4267_, v___x_4268_);
if (v___x_4269_ == 0)
{
v___y_4234_ = v___x_4267_;
goto v___jp_4233_;
}
else
{
lean_dec(v___x_4267_);
v___y_4234_ = v___x_4268_;
goto v___jp_4233_;
}
}
else
{
lean_dec(v_total_4263_);
if (v_negative_4118_ == 0)
{
uint32_t v___x_4270_; 
v___x_4270_ = 0;
v___y_4127_ = v___x_4270_;
goto v___jp_4126_;
}
else
{
uint32_t v___x_4271_; 
v___x_4271_ = 2147483648;
v___y_4127_ = v___x_4271_;
goto v___jp_4126_;
}
}
}
v___jp_4272_:
{
lean_object* v___x_4274_; 
v___x_4274_ = lean_uint64_to_nat(v___y_4273_);
v___y_4261_ = v___x_4274_;
goto v___jp_4260_;
}
v___jp_4275_:
{
uint64_t v___x_4278_; uint64_t v___x_4279_; uint8_t v___x_4280_; 
v___x_4278_ = 1ULL;
v___x_4279_ = lean_uint64_shift_right(v___y_4276_, v___x_4278_);
v___x_4280_ = lean_uint64_dec_eq(v___x_4279_, v___x_4180_);
if (v___x_4280_ == 0)
{
uint64_t v___x_4281_; 
v___x_4281_ = lean_uint64_add(v___y_4277_, v___x_4278_);
v___y_4273_ = v___x_4281_;
goto v___jp_4272_;
}
else
{
v___y_4273_ = v___y_4277_;
goto v___jp_4272_;
}
}
v___jp_4282_:
{
uint64_t v___x_4287_; uint8_t v___x_4288_; 
v___x_4287_ = lean_uint64_shift_right(v___y_4284_, v___y_4285_);
v___x_4288_ = lean_uint64_dec_eq(v___x_4287_, v___x_4180_);
if (v___x_4288_ == 0)
{
uint64_t v___x_4289_; 
v___x_4289_ = lean_uint64_add(v___y_4283_, v___y_4285_);
v___y_4276_ = v___y_4286_;
v___y_4277_ = v___x_4289_;
goto v___jp_4275_;
}
else
{
v___y_4276_ = v___y_4286_;
v___y_4277_ = v___y_4283_;
goto v___jp_4275_;
}
}
v___jp_4290_:
{
uint64_t v___x_4293_; uint64_t v___x_4294_; uint8_t v___x_4295_; 
v___x_4293_ = 2ULL;
v___x_4294_ = lean_uint64_shift_right(v___y_4291_, v___x_4293_);
v___x_4295_ = lean_uint64_dec_eq(v___x_4294_, v___x_4180_);
if (v___x_4295_ == 0)
{
v___y_4283_ = v___y_4292_;
v___y_4284_ = v___y_4291_;
v___y_4285_ = v___x_4293_;
v___y_4286_ = v___x_4294_;
goto v___jp_4282_;
}
else
{
v___y_4283_ = v___y_4292_;
v___y_4284_ = v___y_4291_;
v___y_4285_ = v___x_4293_;
v___y_4286_ = v___y_4291_;
goto v___jp_4282_;
}
}
v___jp_4296_:
{
uint64_t v___x_4301_; uint8_t v___x_4302_; 
v___x_4301_ = lean_uint64_shift_right(v___y_4299_, v___y_4297_);
v___x_4302_ = lean_uint64_dec_eq(v___x_4301_, v___x_4180_);
if (v___x_4302_ == 0)
{
uint64_t v___x_4303_; 
v___x_4303_ = lean_uint64_add(v___y_4298_, v___y_4297_);
v___y_4291_ = v___y_4300_;
v___y_4292_ = v___x_4303_;
goto v___jp_4290_;
}
else
{
v___y_4291_ = v___y_4300_;
v___y_4292_ = v___y_4298_;
goto v___jp_4290_;
}
}
v___jp_4304_:
{
uint64_t v___x_4307_; uint64_t v___x_4308_; uint8_t v___x_4309_; 
v___x_4307_ = 4ULL;
v___x_4308_ = lean_uint64_shift_right(v___y_4305_, v___x_4307_);
v___x_4309_ = lean_uint64_dec_eq(v___x_4308_, v___x_4180_);
if (v___x_4309_ == 0)
{
v___y_4297_ = v___x_4307_;
v___y_4298_ = v___y_4306_;
v___y_4299_ = v___y_4305_;
v___y_4300_ = v___x_4308_;
goto v___jp_4296_;
}
else
{
v___y_4297_ = v___x_4307_;
v___y_4298_ = v___y_4306_;
v___y_4299_ = v___y_4305_;
v___y_4300_ = v___y_4305_;
goto v___jp_4296_;
}
}
v___jp_4310_:
{
uint64_t v___x_4315_; uint8_t v___x_4316_; 
v___x_4315_ = lean_uint64_shift_right(v___y_4312_, v___y_4311_);
v___x_4316_ = lean_uint64_dec_eq(v___x_4315_, v___x_4180_);
if (v___x_4316_ == 0)
{
uint64_t v___x_4317_; 
v___x_4317_ = lean_uint64_add(v___y_4313_, v___y_4311_);
v___y_4305_ = v___y_4314_;
v___y_4306_ = v___x_4317_;
goto v___jp_4304_;
}
else
{
v___y_4305_ = v___y_4314_;
v___y_4306_ = v___y_4313_;
goto v___jp_4304_;
}
}
v___jp_4318_:
{
uint64_t v___x_4321_; uint64_t v___x_4322_; uint8_t v___x_4323_; 
v___x_4321_ = 8ULL;
v___x_4322_ = lean_uint64_shift_right(v___y_4319_, v___x_4321_);
v___x_4323_ = lean_uint64_dec_eq(v___x_4322_, v___x_4180_);
if (v___x_4323_ == 0)
{
v___y_4311_ = v___x_4321_;
v___y_4312_ = v___y_4319_;
v___y_4313_ = v___y_4320_;
v___y_4314_ = v___x_4322_;
goto v___jp_4310_;
}
else
{
v___y_4311_ = v___x_4321_;
v___y_4312_ = v___y_4319_;
v___y_4313_ = v___y_4320_;
v___y_4314_ = v___y_4319_;
goto v___jp_4310_;
}
}
v___jp_4324_:
{
uint64_t v___x_4329_; uint8_t v___x_4330_; 
v___x_4329_ = lean_uint64_shift_right(v___y_4326_, v___y_4325_);
v___x_4330_ = lean_uint64_dec_eq(v___x_4329_, v___x_4180_);
if (v___x_4330_ == 0)
{
uint64_t v___x_4331_; 
v___x_4331_ = lean_uint64_add(v___y_4327_, v___y_4325_);
v___y_4319_ = v___y_4328_;
v___y_4320_ = v___x_4331_;
goto v___jp_4318_;
}
else
{
v___y_4319_ = v___y_4328_;
v___y_4320_ = v___y_4327_;
goto v___jp_4318_;
}
}
v___jp_4332_:
{
uint64_t v___x_4335_; uint64_t v___x_4336_; uint8_t v___x_4337_; 
v___x_4335_ = 16ULL;
v___x_4336_ = lean_uint64_shift_right(v___y_4333_, v___x_4335_);
v___x_4337_ = lean_uint64_dec_eq(v___x_4336_, v___x_4180_);
if (v___x_4337_ == 0)
{
v___y_4325_ = v___x_4335_;
v___y_4326_ = v___y_4333_;
v___y_4327_ = v___y_4334_;
v___y_4328_ = v___x_4336_;
goto v___jp_4324_;
}
else
{
v___y_4325_ = v___x_4335_;
v___y_4326_ = v___y_4333_;
v___y_4327_ = v___y_4334_;
v___y_4328_ = v___y_4333_;
goto v___jp_4324_;
}
}
v___jp_4338_:
{
uint64_t v___x_4341_; uint8_t v___x_4342_; 
v___x_4341_ = lean_uint64_shift_right(v_lo_4119_, v___y_4339_);
v___x_4342_ = lean_uint64_dec_eq(v___x_4341_, v___x_4180_);
if (v___x_4342_ == 0)
{
v___y_4333_ = v___y_4340_;
v___y_4334_ = v___y_4339_;
goto v___jp_4332_;
}
else
{
v___y_4333_ = v___y_4340_;
v___y_4334_ = v___x_4180_;
goto v___jp_4332_;
}
}
v___jp_4343_:
{
lean_object* v___x_4346_; lean_object* v___x_4347_; 
v___x_4346_ = lean_uint64_to_nat(v___y_4345_);
v___x_4347_ = lean_nat_add(v___y_4344_, v___x_4346_);
lean_dec(v___x_4346_);
v___y_4261_ = v___x_4347_;
goto v___jp_4260_;
}
v___jp_4348_:
{
uint64_t v___x_4352_; uint64_t v___x_4353_; uint8_t v___x_4354_; 
v___x_4352_ = 1ULL;
v___x_4353_ = lean_uint64_shift_right(v___y_4350_, v___x_4352_);
v___x_4354_ = lean_uint64_dec_eq(v___x_4353_, v___x_4180_);
if (v___x_4354_ == 0)
{
uint64_t v___x_4355_; 
v___x_4355_ = lean_uint64_add(v___y_4351_, v___x_4352_);
v___y_4344_ = v___y_4349_;
v___y_4345_ = v___x_4355_;
goto v___jp_4343_;
}
else
{
v___y_4344_ = v___y_4349_;
v___y_4345_ = v___y_4351_;
goto v___jp_4343_;
}
}
v___jp_4356_:
{
uint64_t v___x_4362_; uint8_t v___x_4363_; 
v___x_4362_ = lean_uint64_shift_right(v___y_4360_, v___y_4358_);
v___x_4363_ = lean_uint64_dec_eq(v___x_4362_, v___x_4180_);
if (v___x_4363_ == 0)
{
uint64_t v___x_4364_; 
v___x_4364_ = lean_uint64_add(v___y_4357_, v___y_4358_);
v___y_4349_ = v___y_4359_;
v___y_4350_ = v___y_4361_;
v___y_4351_ = v___x_4364_;
goto v___jp_4348_;
}
else
{
v___y_4349_ = v___y_4359_;
v___y_4350_ = v___y_4361_;
v___y_4351_ = v___y_4357_;
goto v___jp_4348_;
}
}
v___jp_4365_:
{
uint64_t v___x_4369_; uint64_t v___x_4370_; uint8_t v___x_4371_; 
v___x_4369_ = 2ULL;
v___x_4370_ = lean_uint64_shift_right(v___y_4367_, v___x_4369_);
v___x_4371_ = lean_uint64_dec_eq(v___x_4370_, v___x_4180_);
if (v___x_4371_ == 0)
{
v___y_4357_ = v___y_4368_;
v___y_4358_ = v___x_4369_;
v___y_4359_ = v___y_4366_;
v___y_4360_ = v___y_4367_;
v___y_4361_ = v___x_4370_;
goto v___jp_4356_;
}
else
{
v___y_4357_ = v___y_4368_;
v___y_4358_ = v___x_4369_;
v___y_4359_ = v___y_4366_;
v___y_4360_ = v___y_4367_;
v___y_4361_ = v___y_4367_;
goto v___jp_4356_;
}
}
v___jp_4372_:
{
uint64_t v___x_4378_; uint8_t v___x_4379_; 
v___x_4378_ = lean_uint64_shift_right(v___y_4373_, v___y_4376_);
v___x_4379_ = lean_uint64_dec_eq(v___x_4378_, v___x_4180_);
if (v___x_4379_ == 0)
{
uint64_t v___x_4380_; 
v___x_4380_ = lean_uint64_add(v___y_4374_, v___y_4376_);
v___y_4366_ = v___y_4375_;
v___y_4367_ = v___y_4377_;
v___y_4368_ = v___x_4380_;
goto v___jp_4365_;
}
else
{
v___y_4366_ = v___y_4375_;
v___y_4367_ = v___y_4377_;
v___y_4368_ = v___y_4374_;
goto v___jp_4365_;
}
}
v___jp_4381_:
{
uint64_t v___x_4385_; uint64_t v___x_4386_; uint8_t v___x_4387_; 
v___x_4385_ = 4ULL;
v___x_4386_ = lean_uint64_shift_right(v___y_4382_, v___x_4385_);
v___x_4387_ = lean_uint64_dec_eq(v___x_4386_, v___x_4180_);
if (v___x_4387_ == 0)
{
v___y_4373_ = v___y_4382_;
v___y_4374_ = v___y_4384_;
v___y_4375_ = v___y_4383_;
v___y_4376_ = v___x_4385_;
v___y_4377_ = v___x_4386_;
goto v___jp_4372_;
}
else
{
v___y_4373_ = v___y_4382_;
v___y_4374_ = v___y_4384_;
v___y_4375_ = v___y_4383_;
v___y_4376_ = v___x_4385_;
v___y_4377_ = v___y_4382_;
goto v___jp_4372_;
}
}
v___jp_4388_:
{
uint64_t v___x_4394_; uint8_t v___x_4395_; 
v___x_4394_ = lean_uint64_shift_right(v___y_4390_, v___y_4392_);
v___x_4395_ = lean_uint64_dec_eq(v___x_4394_, v___x_4180_);
if (v___x_4395_ == 0)
{
uint64_t v___x_4396_; 
v___x_4396_ = lean_uint64_add(v___y_4389_, v___y_4392_);
v___y_4382_ = v___y_4393_;
v___y_4383_ = v___y_4391_;
v___y_4384_ = v___x_4396_;
goto v___jp_4381_;
}
else
{
v___y_4382_ = v___y_4393_;
v___y_4383_ = v___y_4391_;
v___y_4384_ = v___y_4389_;
goto v___jp_4381_;
}
}
v___jp_4397_:
{
uint64_t v___x_4401_; uint64_t v___x_4402_; uint8_t v___x_4403_; 
v___x_4401_ = 8ULL;
v___x_4402_ = lean_uint64_shift_right(v___y_4398_, v___x_4401_);
v___x_4403_ = lean_uint64_dec_eq(v___x_4402_, v___x_4180_);
if (v___x_4403_ == 0)
{
v___y_4389_ = v___y_4400_;
v___y_4390_ = v___y_4398_;
v___y_4391_ = v___y_4399_;
v___y_4392_ = v___x_4401_;
v___y_4393_ = v___x_4402_;
goto v___jp_4388_;
}
else
{
v___y_4389_ = v___y_4400_;
v___y_4390_ = v___y_4398_;
v___y_4391_ = v___y_4399_;
v___y_4392_ = v___x_4401_;
v___y_4393_ = v___y_4398_;
goto v___jp_4388_;
}
}
v___jp_4404_:
{
uint64_t v___x_4410_; uint8_t v___x_4411_; 
v___x_4410_ = lean_uint64_shift_right(v___y_4406_, v___y_4407_);
v___x_4411_ = lean_uint64_dec_eq(v___x_4410_, v___x_4180_);
if (v___x_4411_ == 0)
{
uint64_t v___x_4412_; 
v___x_4412_ = lean_uint64_add(v___y_4405_, v___y_4407_);
v___y_4398_ = v___y_4409_;
v___y_4399_ = v___y_4408_;
v___y_4400_ = v___x_4412_;
goto v___jp_4397_;
}
else
{
v___y_4398_ = v___y_4409_;
v___y_4399_ = v___y_4408_;
v___y_4400_ = v___y_4405_;
goto v___jp_4397_;
}
}
v___jp_4413_:
{
uint64_t v___x_4417_; uint64_t v___x_4418_; uint8_t v___x_4419_; 
v___x_4417_ = 16ULL;
v___x_4418_ = lean_uint64_shift_right(v___y_4414_, v___x_4417_);
v___x_4419_ = lean_uint64_dec_eq(v___x_4418_, v___x_4180_);
if (v___x_4419_ == 0)
{
v___y_4405_ = v___y_4416_;
v___y_4406_ = v___y_4414_;
v___y_4407_ = v___x_4417_;
v___y_4408_ = v___y_4415_;
v___y_4409_ = v___x_4418_;
goto v___jp_4404_;
}
else
{
v___y_4405_ = v___y_4416_;
v___y_4406_ = v___y_4414_;
v___y_4407_ = v___x_4417_;
v___y_4408_ = v___y_4415_;
v___y_4409_ = v___y_4414_;
goto v___jp_4404_;
}
}
v___jp_4420_:
{
uint64_t v___x_4424_; uint8_t v___x_4425_; 
v___x_4424_ = lean_uint64_shift_right(v_hi_4120_, v___y_4422_);
v___x_4425_ = lean_uint64_dec_eq(v___x_4424_, v___x_4180_);
if (v___x_4425_ == 0)
{
v___y_4414_ = v___y_4423_;
v___y_4415_ = v___y_4421_;
v___y_4416_ = v___y_4422_;
goto v___jp_4413_;
}
else
{
v___y_4414_ = v___y_4423_;
v___y_4415_ = v___y_4421_;
v___y_4416_ = v___x_4180_;
goto v___jp_4413_;
}
}
v___jp_4426_:
{
if (v___y_4427_ == 0)
{
uint8_t v___x_4428_; 
v___x_4428_ = lean_uint64_dec_eq(v_hi_4120_, v___x_4180_);
if (v___x_4428_ == 0)
{
lean_object* v___x_4429_; uint64_t v___x_4430_; uint64_t v___x_4431_; uint8_t v___x_4432_; 
v___x_4429_ = lean_unsigned_to_nat(64u);
v___x_4430_ = 32ULL;
v___x_4431_ = lean_uint64_shift_right(v_hi_4120_, v___x_4430_);
v___x_4432_ = lean_uint64_dec_eq(v___x_4431_, v___x_4180_);
if (v___x_4432_ == 0)
{
v___y_4421_ = v___x_4429_;
v___y_4422_ = v___x_4430_;
v___y_4423_ = v___x_4431_;
goto v___jp_4420_;
}
else
{
v___y_4421_ = v___x_4429_;
v___y_4422_ = v___x_4430_;
v___y_4423_ = v_hi_4120_;
goto v___jp_4420_;
}
}
else
{
uint64_t v___x_4433_; uint64_t v___x_4434_; uint8_t v___x_4435_; 
v___x_4433_ = 32ULL;
v___x_4434_ = lean_uint64_shift_right(v_lo_4119_, v___x_4433_);
v___x_4435_ = lean_uint64_dec_eq(v___x_4434_, v___x_4180_);
if (v___x_4435_ == 0)
{
v___y_4339_ = v___x_4433_;
v___y_4340_ = v___x_4434_;
goto v___jp_4338_;
}
else
{
v___y_4339_ = v___x_4433_;
v___y_4340_ = v_lo_4119_;
goto v___jp_4338_;
}
}
}
else
{
if (v_negative_4118_ == 0)
{
uint32_t v___x_4436_; 
v___x_4436_ = 0;
return v___x_4436_;
}
else
{
uint32_t v___x_4437_; 
v___x_4437_ = 2147483648;
return v___x_4437_;
}
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_R24ExactDotCost_round128___boxed(lean_object* v_negative_4440_, lean_object* v_lo_4441_, lean_object* v_hi_4442_, lean_object* v_base_4443_){
_start:
{
uint8_t v_negative_boxed_4444_; uint64_t v_lo_boxed_4445_; uint64_t v_hi_boxed_4446_; uint32_t v_res_4447_; lean_object* v_r_4448_; 
v_negative_boxed_4444_ = lean_unbox(v_negative_4440_);
v_lo_boxed_4445_ = lean_unbox_uint64(v_lo_4441_);
lean_dec_ref(v_lo_4441_);
v_hi_boxed_4446_ = lean_unbox_uint64(v_hi_4442_);
lean_dec_ref(v_hi_4442_);
v_res_4447_ = lp_competition_Submission_R24ExactDotCost_round128(v_negative_boxed_4444_, v_lo_boxed_4445_, v_hi_boxed_4446_, v_base_4443_);
lean_dec(v_base_4443_);
v_r_4448_ = lean_box_uint32(v_res_4447_);
return v_r_4448_;
}
}
static lean_object* _init_lp_competition_Submission_R24ExactDotCost_finish___closed__0(void){
_start:
{
lean_object* v___x_4449_; lean_object* v___x_4450_; 
v___x_4449_ = lean_unsigned_to_nat(298u);
v___x_4450_ = lean_nat_to_int(v___x_4449_);
return v___x_4450_;
}
}
LEAN_EXPORT uint32_t lp_competition_Submission_R24ExactDotCost_finish(uint32_t v_base_4451_, uint8_t v_negZero_4452_, uint64_t v_pLo_4453_, uint64_t v_pHi_4454_, uint64_t v_nLo_4455_, uint64_t v_nHi_4456_){
_start:
{
uint64_t v___y_4458_; uint64_t v___y_4459_; uint8_t v___y_4460_; uint64_t v___y_4461_; uint8_t v___y_4469_; uint64_t v___y_4476_; uint8_t v___y_4477_; uint64_t v___y_4478_; uint64_t v___y_4479_; uint8_t v___y_4487_; uint8_t v___y_4488_; uint8_t v___y_4495_; uint8_t v___x_4502_; 
v___x_4502_ = lean_uint64_dec_eq(v_pLo_4453_, v_nLo_4455_);
if (v___x_4502_ == 0)
{
v___y_4495_ = v___x_4502_;
goto v___jp_4494_;
}
else
{
uint8_t v___x_4503_; 
v___x_4503_ = lean_uint64_dec_eq(v_pHi_4454_, v_nHi_4456_);
v___y_4495_ = v___x_4503_;
goto v___jp_4494_;
}
v___jp_4457_:
{
uint64_t v___x_4462_; lean_object* v___x_4463_; lean_object* v___x_4464_; lean_object* v___x_4465_; lean_object* v___x_4466_; uint32_t v___x_4467_; 
v___x_4462_ = lean_uint64_sub(v___y_4459_, v___y_4461_);
v___x_4463_ = lean_uint32_to_nat(v_base_4451_);
v___x_4464_ = lean_nat_to_int(v___x_4463_);
v___x_4465_ = lean_obj_once(&lp_competition_Submission_R24ExactDotCost_finish___closed__0, &lp_competition_Submission_R24ExactDotCost_finish___closed__0_once, _init_lp_competition_Submission_R24ExactDotCost_finish___closed__0);
v___x_4466_ = lean_int_sub(v___x_4464_, v___x_4465_);
lean_dec(v___x_4464_);
v___x_4467_ = lp_competition_Submission_R24ExactDotCost_round128(v___y_4460_, v___y_4458_, v___x_4462_, v___x_4466_);
lean_dec(v___x_4466_);
return v___x_4467_;
}
v___jp_4468_:
{
uint64_t v___x_4470_; uint64_t v___x_4471_; uint8_t v___x_4472_; 
v___x_4470_ = lean_uint64_sub(v_nLo_4455_, v_pLo_4453_);
v___x_4471_ = lean_uint64_sub(v_nHi_4456_, v_pHi_4454_);
v___x_4472_ = lean_uint64_dec_lt(v_nLo_4455_, v_pLo_4453_);
if (v___x_4472_ == 0)
{
uint64_t v___x_4473_; 
v___x_4473_ = 0ULL;
v___y_4458_ = v___x_4470_;
v___y_4459_ = v___x_4471_;
v___y_4460_ = v___y_4469_;
v___y_4461_ = v___x_4473_;
goto v___jp_4457_;
}
else
{
uint64_t v___x_4474_; 
v___x_4474_ = 1ULL;
v___y_4458_ = v___x_4470_;
v___y_4459_ = v___x_4471_;
v___y_4460_ = v___y_4469_;
v___y_4461_ = v___x_4474_;
goto v___jp_4457_;
}
}
v___jp_4475_:
{
uint64_t v___x_4480_; lean_object* v___x_4481_; lean_object* v___x_4482_; lean_object* v___x_4483_; lean_object* v___x_4484_; uint32_t v___x_4485_; 
v___x_4480_ = lean_uint64_sub(v___y_4478_, v___y_4479_);
v___x_4481_ = lean_uint32_to_nat(v_base_4451_);
v___x_4482_ = lean_nat_to_int(v___x_4481_);
v___x_4483_ = lean_obj_once(&lp_competition_Submission_R24ExactDotCost_finish___closed__0, &lp_competition_Submission_R24ExactDotCost_finish___closed__0_once, _init_lp_competition_Submission_R24ExactDotCost_finish___closed__0);
v___x_4484_ = lean_int_sub(v___x_4482_, v___x_4483_);
lean_dec(v___x_4482_);
v___x_4485_ = lp_competition_Submission_R24ExactDotCost_round128(v___y_4477_, v___y_4476_, v___x_4480_, v___x_4484_);
lean_dec(v___x_4484_);
return v___x_4485_;
}
v___jp_4486_:
{
if (v___y_4488_ == 0)
{
uint64_t v___x_4489_; uint64_t v___x_4490_; uint8_t v___x_4491_; 
v___x_4489_ = lean_uint64_sub(v_pLo_4453_, v_nLo_4455_);
v___x_4490_ = lean_uint64_sub(v_pHi_4454_, v_nHi_4456_);
v___x_4491_ = lean_uint64_dec_lt(v_pLo_4453_, v_nLo_4455_);
if (v___x_4491_ == 0)
{
uint64_t v___x_4492_; 
v___x_4492_ = 0ULL;
v___y_4476_ = v___x_4489_;
v___y_4477_ = v___y_4488_;
v___y_4478_ = v___x_4490_;
v___y_4479_ = v___x_4492_;
goto v___jp_4475_;
}
else
{
uint64_t v___x_4493_; 
v___x_4493_ = 1ULL;
v___y_4476_ = v___x_4489_;
v___y_4477_ = v___y_4488_;
v___y_4478_ = v___x_4490_;
v___y_4479_ = v___x_4493_;
goto v___jp_4475_;
}
}
else
{
v___y_4469_ = v___y_4487_;
goto v___jp_4468_;
}
}
v___jp_4494_:
{
if (v___y_4495_ == 0)
{
uint8_t v___x_4496_; uint8_t v___x_4497_; 
v___x_4496_ = 1;
v___x_4497_ = lean_uint64_dec_lt(v_pHi_4454_, v_nHi_4456_);
if (v___x_4497_ == 0)
{
uint8_t v___x_4498_; 
v___x_4498_ = lean_uint64_dec_eq(v_pHi_4454_, v_nHi_4456_);
if (v___x_4498_ == 0)
{
v___y_4487_ = v___x_4496_;
v___y_4488_ = v___x_4498_;
goto v___jp_4486_;
}
else
{
uint8_t v___x_4499_; 
v___x_4499_ = lean_uint64_dec_lt(v_pLo_4453_, v_nLo_4455_);
v___y_4487_ = v___x_4496_;
v___y_4488_ = v___x_4499_;
goto v___jp_4486_;
}
}
else
{
v___y_4469_ = v___x_4496_;
goto v___jp_4468_;
}
}
else
{
if (v_negZero_4452_ == 0)
{
uint32_t v___x_4500_; 
v___x_4500_ = 0;
return v___x_4500_;
}
else
{
uint32_t v___x_4501_; 
v___x_4501_ = 2147483648;
return v___x_4501_;
}
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_R24ExactDotCost_finish___boxed(lean_object* v_base_4504_, lean_object* v_negZero_4505_, lean_object* v_pLo_4506_, lean_object* v_pHi_4507_, lean_object* v_nLo_4508_, lean_object* v_nHi_4509_){
_start:
{
uint32_t v_base_boxed_4510_; uint8_t v_negZero_boxed_4511_; uint64_t v_pLo_boxed_4512_; uint64_t v_pHi_boxed_4513_; uint64_t v_nLo_boxed_4514_; uint64_t v_nHi_boxed_4515_; uint32_t v_res_4516_; lean_object* v_r_4517_; 
v_base_boxed_4510_ = lean_unbox_uint32(v_base_4504_);
lean_dec(v_base_4504_);
v_negZero_boxed_4511_ = lean_unbox(v_negZero_4505_);
v_pLo_boxed_4512_ = lean_unbox_uint64(v_pLo_4506_);
lean_dec_ref(v_pLo_4506_);
v_pHi_boxed_4513_ = lean_unbox_uint64(v_pHi_4507_);
lean_dec_ref(v_pHi_4507_);
v_nLo_boxed_4514_ = lean_unbox_uint64(v_nLo_4508_);
lean_dec_ref(v_nLo_4508_);
v_nHi_boxed_4515_ = lean_unbox_uint64(v_nHi_4509_);
lean_dec_ref(v_nHi_4509_);
v_res_4516_ = lp_competition_Submission_R24ExactDotCost_finish(v_base_boxed_4510_, v_negZero_boxed_4511_, v_pLo_boxed_4512_, v_pHi_boxed_4513_, v_nLo_boxed_4514_, v_nHi_boxed_4515_);
v_r_4517_ = lean_box_uint32(v_res_4516_);
return v_r_4517_;
}
}
LEAN_EXPORT uint32_t lp_competition_Submission_R24ExactDotCost_nativeLoop(lean_object* v_a_4518_, lean_object* v_b_4519_, uint32_t v_base_4520_, lean_object* v_index_4521_, uint8_t v_negZero_4522_, uint64_t v_pLo_4523_, uint64_t v_pHi_4524_, uint64_t v_nLo_4525_, uint64_t v_nHi_4526_, lean_object* v_x_4527_){
_start:
{
uint8_t v___y_4529_; uint64_t v___y_4530_; uint64_t v___y_4531_; uint64_t v___y_4532_; uint8_t v___y_4540_; uint64_t v___y_4541_; uint64_t v___y_4542_; uint64_t v___y_4543_; uint8_t v___y_4551_; uint8_t v___y_4558_; uint8_t v___y_4559_; lean_object* v_zero_4565_; uint8_t v_isZero_4566_; uint8_t v___y_4568_; 
v_zero_4565_ = lean_unsigned_to_nat(0u);
v_isZero_4566_ = lean_nat_dec_eq(v_x_4527_, v_zero_4565_);
if (v_isZero_4566_ == 1)
{
uint8_t v___x_4574_; 
lean_dec(v_x_4527_);
lean_dec(v_index_4521_);
v___x_4574_ = lean_uint64_dec_eq(v_pLo_4523_, v_nLo_4525_);
if (v___x_4574_ == 0)
{
v___y_4568_ = v___x_4574_;
goto v___jp_4567_;
}
else
{
uint8_t v___x_4575_; 
v___x_4575_ = lean_uint64_dec_eq(v_pHi_4524_, v_nHi_4526_);
v___y_4568_ = v___x_4575_;
goto v___jp_4567_;
}
}
else
{
uint32_t v___x_4576_; lean_object* v_one_4577_; lean_object* v_n_4578_; uint64_t v___y_4580_; uint64_t v___y_4581_; uint8_t v___y_4582_; uint64_t v___y_4583_; uint64_t v___y_4588_; uint64_t v___y_4589_; uint8_t v___y_4590_; uint64_t v___y_4591_; uint64_t v___y_4596_; uint8_t v___y_4597_; uint64_t v___y_4598_; uint8_t v___y_4599_; uint64_t v___y_4600_; uint8_t v___y_4610_; uint64_t v___y_4611_; uint64_t v___y_4612_; uint64_t v___y_4613_; uint8_t v___y_4614_; uint8_t v___y_4615_; uint64_t v___y_4616_; uint64_t v___y_4617_; lean_object* v___x_4623_; lean_object* v_wa_4624_; lean_object* v___x_4625_; lean_object* v_wb_4626_; uint64_t v___y_4628_; uint8_t v___y_4629_; uint64_t v___y_4650_; uint64_t v___y_4653_; uint8_t v___y_4654_; uint8_t v___y_4655_; uint64_t v___y_4657_; uint8_t v___y_4658_; uint64_t v___y_4665_; uint64_t v___y_4666_; uint64_t v___y_4674_; uint32_t v___x_4689_; uint32_t v___x_4690_; uint32_t v___x_4691_; uint32_t v___x_4692_; uint32_t v___x_4693_; uint32_t v___x_4694_; uint8_t v___x_4695_; 
v___x_4576_ = 0;
v_one_4577_ = lean_unsigned_to_nat(1u);
v_n_4578_ = lean_nat_sub(v_x_4527_, v_one_4577_);
lean_dec(v_x_4527_);
v___x_4623_ = lp_competition_Submission_R24ExactDotCost_prepareOperand___closed__2___boxed__const__1;
v_wa_4624_ = lean_array_get_borrowed(v___x_4623_, v_a_4518_, v_index_4521_);
v___x_4625_ = lp_competition_Submission_R24ExactDotCost_prepareOperand___closed__2___boxed__const__1;
v_wb_4626_ = lean_array_get_borrowed(v___x_4625_, v_b_4519_, v_index_4521_);
v___x_4689_ = 23;
v___x_4690_ = lean_unbox_uint32(v_wa_4624_);
v___x_4691_ = lean_uint32_shift_right(v___x_4690_, v___x_4689_);
v___x_4692_ = 255;
v___x_4693_ = lean_uint32_land(v___x_4691_, v___x_4692_);
v___x_4694_ = 254;
v___x_4695_ = lean_uint32_dec_eq(v___x_4693_, v___x_4694_);
if (v___x_4695_ == 0)
{
uint32_t v___x_4696_; uint32_t v___x_4697_; uint32_t v___x_4698_; uint32_t v___x_4699_; uint32_t v___x_4700_; uint64_t v___x_4701_; 
v___x_4696_ = 8388607;
v___x_4697_ = lean_unbox_uint32(v_wa_4624_);
v___x_4698_ = lean_uint32_land(v___x_4697_, v___x_4696_);
v___x_4699_ = 8388608;
v___x_4700_ = lean_uint32_lor(v___x_4698_, v___x_4699_);
v___x_4701_ = lean_uint32_to_uint64(v___x_4700_);
v___y_4674_ = v___x_4701_;
goto v___jp_4673_;
}
else
{
uint64_t v___x_4702_; 
v___x_4702_ = 0ULL;
v___y_4674_ = v___x_4702_;
goto v___jp_4673_;
}
v___jp_4579_:
{
uint64_t v_nextHi_4584_; lean_object* v___x_4585_; 
v_nextHi_4584_ = lean_uint64_add(v___y_4580_, v___y_4583_);
v___x_4585_ = lean_nat_add(v_index_4521_, v_one_4577_);
lean_dec(v_index_4521_);
v_index_4521_ = v___x_4585_;
v_negZero_4522_ = v___y_4582_;
v_pLo_4523_ = v___y_4581_;
v_pHi_4524_ = v_nextHi_4584_;
v_x_4527_ = v_n_4578_;
goto _start;
}
v___jp_4587_:
{
uint64_t v_nextHi_4592_; lean_object* v___x_4593_; 
v_nextHi_4592_ = lean_uint64_add(v___y_4588_, v___y_4591_);
v___x_4593_ = lean_nat_add(v_index_4521_, v_one_4577_);
lean_dec(v_index_4521_);
v_index_4521_ = v___x_4593_;
v_negZero_4522_ = v___y_4590_;
v_nLo_4525_ = v___y_4589_;
v_nHi_4526_ = v_nextHi_4592_;
v_x_4527_ = v_n_4578_;
goto _start;
}
v___jp_4595_:
{
if (v___y_4599_ == 0)
{
uint64_t v_nextLo_4601_; uint64_t v___x_4602_; uint8_t v___x_4603_; 
v_nextLo_4601_ = lean_uint64_add(v_pLo_4523_, v___y_4596_);
v___x_4602_ = lean_uint64_add(v_pHi_4524_, v___y_4600_);
v___x_4603_ = lean_uint64_dec_lt(v_nextLo_4601_, v_pLo_4523_);
if (v___x_4603_ == 0)
{
v___y_4580_ = v___x_4602_;
v___y_4581_ = v_nextLo_4601_;
v___y_4582_ = v___y_4599_;
v___y_4583_ = v___y_4598_;
goto v___jp_4579_;
}
else
{
uint64_t v___x_4604_; 
v___x_4604_ = 1ULL;
v___y_4580_ = v___x_4602_;
v___y_4581_ = v_nextLo_4601_;
v___y_4582_ = v___y_4599_;
v___y_4583_ = v___x_4604_;
goto v___jp_4579_;
}
}
else
{
uint64_t v_nextLo_4605_; uint64_t v___x_4606_; uint8_t v___x_4607_; 
v_nextLo_4605_ = lean_uint64_add(v_nLo_4525_, v___y_4596_);
v___x_4606_ = lean_uint64_add(v_nHi_4526_, v___y_4600_);
v___x_4607_ = lean_uint64_dec_lt(v_nextLo_4605_, v_nLo_4525_);
if (v___x_4607_ == 0)
{
v___y_4588_ = v___x_4606_;
v___y_4589_ = v_nextLo_4605_;
v___y_4590_ = v___y_4597_;
v___y_4591_ = v___y_4598_;
goto v___jp_4587_;
}
else
{
uint64_t v___x_4608_; 
v___x_4608_ = 1ULL;
v___y_4588_ = v___x_4606_;
v___y_4589_ = v_nextLo_4605_;
v___y_4590_ = v___y_4597_;
v___y_4591_ = v___x_4608_;
goto v___jp_4587_;
}
}
}
v___jp_4609_:
{
uint8_t v___x_4618_; 
v___x_4618_ = lean_uint64_dec_eq(v___y_4612_, v___y_4613_);
if (v___x_4618_ == 0)
{
if (v___y_4610_ == 0)
{
uint64_t v___x_4619_; uint64_t v___x_4620_; 
v___x_4619_ = lean_uint64_sub(v___y_4612_, v___y_4611_);
v___x_4620_ = lean_uint64_shift_left(v___y_4616_, v___x_4619_);
v___y_4596_ = v___y_4617_;
v___y_4597_ = v___y_4614_;
v___y_4598_ = v___y_4613_;
v___y_4599_ = v___y_4615_;
v___y_4600_ = v___x_4620_;
goto v___jp_4595_;
}
else
{
uint64_t v___x_4621_; uint64_t v___x_4622_; 
v___x_4621_ = lean_uint64_sub(v___y_4611_, v___y_4612_);
v___x_4622_ = lean_uint64_shift_right(v___y_4616_, v___x_4621_);
v___y_4596_ = v___y_4617_;
v___y_4597_ = v___y_4614_;
v___y_4598_ = v___y_4613_;
v___y_4599_ = v___y_4615_;
v___y_4600_ = v___x_4622_;
goto v___jp_4595_;
}
}
else
{
v___y_4596_ = v___y_4617_;
v___y_4597_ = v___y_4614_;
v___y_4598_ = v___y_4613_;
v___y_4599_ = v___y_4615_;
v___y_4600_ = v___y_4613_;
goto v___jp_4595_;
}
}
v___jp_4627_:
{
uint64_t v___x_4630_; uint8_t v___x_4631_; 
v___x_4630_ = 0ULL;
v___x_4631_ = lean_uint64_dec_eq(v___y_4628_, v___x_4630_);
if (v___x_4631_ == 0)
{
uint32_t v___x_4632_; uint32_t v___x_4633_; uint32_t v___x_4634_; uint32_t v___x_4635_; uint32_t v___x_4636_; uint32_t v___x_4637_; uint32_t v___x_4638_; uint32_t v___x_4639_; uint32_t v___x_4640_; uint32_t v___x_4641_; uint64_t v_shift_4642_; uint64_t v___x_4643_; uint8_t v___x_4644_; 
v___x_4632_ = 23;
v___x_4633_ = lean_unbox_uint32(v_wa_4624_);
v___x_4634_ = lean_uint32_shift_right(v___x_4633_, v___x_4632_);
v___x_4635_ = 255;
v___x_4636_ = lean_uint32_land(v___x_4634_, v___x_4635_);
v___x_4637_ = lean_unbox_uint32(v_wb_4626_);
v___x_4638_ = lean_uint32_shift_right(v___x_4637_, v___x_4632_);
v___x_4639_ = lean_uint32_land(v___x_4638_, v___x_4635_);
v___x_4640_ = lean_uint32_add(v___x_4636_, v___x_4639_);
v___x_4641_ = lean_uint32_sub(v___x_4640_, v_base_4520_);
v_shift_4642_ = lean_uint32_to_uint64(v___x_4641_);
v___x_4643_ = 64ULL;
v___x_4644_ = lean_uint64_dec_lt(v_shift_4642_, v___x_4643_);
if (v___x_4644_ == 0)
{
v___y_4610_ = v___x_4644_;
v___y_4611_ = v___x_4643_;
v___y_4612_ = v_shift_4642_;
v___y_4613_ = v___x_4630_;
v___y_4614_ = v___x_4631_;
v___y_4615_ = v___y_4629_;
v___y_4616_ = v___y_4628_;
v___y_4617_ = v___x_4630_;
goto v___jp_4609_;
}
else
{
uint64_t v___x_4645_; 
v___x_4645_ = lean_uint64_shift_left(v___y_4628_, v_shift_4642_);
v___y_4610_ = v___x_4644_;
v___y_4611_ = v___x_4643_;
v___y_4612_ = v_shift_4642_;
v___y_4613_ = v___x_4630_;
v___y_4614_ = v___x_4631_;
v___y_4615_ = v___y_4629_;
v___y_4616_ = v___y_4628_;
v___y_4617_ = v___x_4645_;
goto v___jp_4609_;
}
}
else
{
lean_object* v___x_4646_; 
v___x_4646_ = lean_nat_add(v_index_4521_, v_one_4577_);
lean_dec(v_index_4521_);
if (v_negZero_4522_ == 0)
{
v_index_4521_ = v___x_4646_;
v_x_4527_ = v_n_4578_;
goto _start;
}
else
{
v_index_4521_ = v___x_4646_;
v_negZero_4522_ = v___y_4629_;
v_x_4527_ = v_n_4578_;
goto _start;
}
}
}
v___jp_4649_:
{
uint8_t v___x_4651_; 
v___x_4651_ = 1;
v___y_4628_ = v___y_4650_;
v___y_4629_ = v___x_4651_;
goto v___jp_4627_;
}
v___jp_4652_:
{
if (v___y_4654_ == 0)
{
if (v___y_4655_ == 0)
{
v___y_4628_ = v___y_4653_;
v___y_4629_ = v_isZero_4566_;
goto v___jp_4627_;
}
else
{
v___y_4650_ = v___y_4653_;
goto v___jp_4649_;
}
}
else
{
if (v___y_4655_ == 0)
{
v___y_4650_ = v___y_4653_;
goto v___jp_4649_;
}
else
{
v___y_4628_ = v___y_4653_;
v___y_4629_ = v_isZero_4566_;
goto v___jp_4627_;
}
}
}
v___jp_4656_:
{
uint32_t v___x_4659_; uint32_t v___x_4660_; uint32_t v___x_4661_; uint8_t v___x_4662_; 
v___x_4659_ = 2147483648;
v___x_4660_ = lean_unbox_uint32(v_wb_4626_);
v___x_4661_ = lean_uint32_land(v___x_4660_, v___x_4659_);
v___x_4662_ = lean_uint32_dec_eq(v___x_4661_, v___x_4576_);
if (v___x_4662_ == 0)
{
uint8_t v___x_4663_; 
v___x_4663_ = 1;
v___y_4653_ = v___y_4657_;
v___y_4654_ = v___y_4658_;
v___y_4655_ = v___x_4663_;
goto v___jp_4652_;
}
else
{
v___y_4653_ = v___y_4657_;
v___y_4654_ = v___y_4658_;
v___y_4655_ = v_isZero_4566_;
goto v___jp_4652_;
}
}
v___jp_4664_:
{
uint64_t v_product_4667_; uint32_t v___x_4668_; uint32_t v___x_4669_; uint32_t v___x_4670_; uint8_t v___x_4671_; 
v_product_4667_ = lean_uint64_mul(v___y_4665_, v___y_4666_);
v___x_4668_ = 2147483648;
v___x_4669_ = lean_unbox_uint32(v_wa_4624_);
v___x_4670_ = lean_uint32_land(v___x_4669_, v___x_4668_);
v___x_4671_ = lean_uint32_dec_eq(v___x_4670_, v___x_4576_);
if (v___x_4671_ == 0)
{
uint8_t v___x_4672_; 
v___x_4672_ = 1;
v___y_4657_ = v_product_4667_;
v___y_4658_ = v___x_4672_;
goto v___jp_4656_;
}
else
{
v___y_4657_ = v_product_4667_;
v___y_4658_ = v_isZero_4566_;
goto v___jp_4656_;
}
}
v___jp_4673_:
{
uint32_t v___x_4675_; uint32_t v___x_4676_; uint32_t v___x_4677_; uint32_t v___x_4678_; uint32_t v___x_4679_; uint32_t v___x_4680_; uint8_t v___x_4681_; 
v___x_4675_ = 23;
v___x_4676_ = lean_unbox_uint32(v_wb_4626_);
v___x_4677_ = lean_uint32_shift_right(v___x_4676_, v___x_4675_);
v___x_4678_ = 255;
v___x_4679_ = lean_uint32_land(v___x_4677_, v___x_4678_);
v___x_4680_ = 254;
v___x_4681_ = lean_uint32_dec_eq(v___x_4679_, v___x_4680_);
if (v___x_4681_ == 0)
{
uint32_t v___x_4682_; uint32_t v___x_4683_; uint32_t v___x_4684_; uint32_t v___x_4685_; uint32_t v___x_4686_; uint64_t v___x_4687_; 
v___x_4682_ = 8388607;
v___x_4683_ = lean_unbox_uint32(v_wb_4626_);
v___x_4684_ = lean_uint32_land(v___x_4683_, v___x_4682_);
v___x_4685_ = 8388608;
v___x_4686_ = lean_uint32_lor(v___x_4684_, v___x_4685_);
v___x_4687_ = lean_uint32_to_uint64(v___x_4686_);
v___y_4665_ = v___y_4674_;
v___y_4666_ = v___x_4687_;
goto v___jp_4664_;
}
else
{
uint64_t v___x_4688_; 
v___x_4688_ = 0ULL;
v___y_4665_ = v___y_4674_;
v___y_4666_ = v___x_4688_;
goto v___jp_4664_;
}
}
}
v___jp_4528_:
{
uint64_t v___x_4533_; lean_object* v___x_4534_; lean_object* v___x_4535_; lean_object* v___x_4536_; lean_object* v___x_4537_; uint32_t v___x_4538_; 
v___x_4533_ = lean_uint64_sub(v___y_4531_, v___y_4532_);
v___x_4534_ = lean_uint32_to_nat(v_base_4520_);
v___x_4535_ = lean_nat_to_int(v___x_4534_);
v___x_4536_ = lean_obj_once(&lp_competition_Submission_R24ExactDotCost_finish___closed__0, &lp_competition_Submission_R24ExactDotCost_finish___closed__0_once, _init_lp_competition_Submission_R24ExactDotCost_finish___closed__0);
v___x_4537_ = lean_int_sub(v___x_4535_, v___x_4536_);
lean_dec(v___x_4535_);
v___x_4538_ = lp_competition_Submission_R24ExactDotCost_round128(v___y_4529_, v___y_4530_, v___x_4533_, v___x_4537_);
lean_dec(v___x_4537_);
return v___x_4538_;
}
v___jp_4539_:
{
uint64_t v___x_4544_; lean_object* v___x_4545_; lean_object* v___x_4546_; lean_object* v___x_4547_; lean_object* v___x_4548_; uint32_t v___x_4549_; 
v___x_4544_ = lean_uint64_sub(v___y_4541_, v___y_4543_);
v___x_4545_ = lean_uint32_to_nat(v_base_4520_);
v___x_4546_ = lean_nat_to_int(v___x_4545_);
v___x_4547_ = lean_obj_once(&lp_competition_Submission_R24ExactDotCost_finish___closed__0, &lp_competition_Submission_R24ExactDotCost_finish___closed__0_once, _init_lp_competition_Submission_R24ExactDotCost_finish___closed__0);
v___x_4548_ = lean_int_sub(v___x_4546_, v___x_4547_);
lean_dec(v___x_4546_);
v___x_4549_ = lp_competition_Submission_R24ExactDotCost_round128(v___y_4540_, v___y_4542_, v___x_4544_, v___x_4548_);
lean_dec(v___x_4548_);
return v___x_4549_;
}
v___jp_4550_:
{
uint64_t v___x_4552_; uint64_t v___x_4553_; uint8_t v___x_4554_; 
v___x_4552_ = lean_uint64_sub(v_nLo_4525_, v_pLo_4523_);
v___x_4553_ = lean_uint64_sub(v_nHi_4526_, v_pHi_4524_);
v___x_4554_ = lean_uint64_dec_lt(v_nLo_4525_, v_pLo_4523_);
if (v___x_4554_ == 0)
{
uint64_t v___x_4555_; 
v___x_4555_ = 0ULL;
v___y_4540_ = v___y_4551_;
v___y_4541_ = v___x_4553_;
v___y_4542_ = v___x_4552_;
v___y_4543_ = v___x_4555_;
goto v___jp_4539_;
}
else
{
uint64_t v___x_4556_; 
v___x_4556_ = 1ULL;
v___y_4540_ = v___y_4551_;
v___y_4541_ = v___x_4553_;
v___y_4542_ = v___x_4552_;
v___y_4543_ = v___x_4556_;
goto v___jp_4539_;
}
}
v___jp_4557_:
{
if (v___y_4559_ == 0)
{
uint64_t v___x_4560_; uint64_t v___x_4561_; uint8_t v___x_4562_; 
v___x_4560_ = lean_uint64_sub(v_pLo_4523_, v_nLo_4525_);
v___x_4561_ = lean_uint64_sub(v_pHi_4524_, v_nHi_4526_);
v___x_4562_ = lean_uint64_dec_lt(v_pLo_4523_, v_nLo_4525_);
if (v___x_4562_ == 0)
{
uint64_t v___x_4563_; 
v___x_4563_ = 0ULL;
v___y_4529_ = v___y_4559_;
v___y_4530_ = v___x_4560_;
v___y_4531_ = v___x_4561_;
v___y_4532_ = v___x_4563_;
goto v___jp_4528_;
}
else
{
uint64_t v___x_4564_; 
v___x_4564_ = 1ULL;
v___y_4529_ = v___y_4559_;
v___y_4530_ = v___x_4560_;
v___y_4531_ = v___x_4561_;
v___y_4532_ = v___x_4564_;
goto v___jp_4528_;
}
}
else
{
v___y_4551_ = v___y_4558_;
goto v___jp_4550_;
}
}
v___jp_4567_:
{
if (v___y_4568_ == 0)
{
uint8_t v___x_4569_; 
v___x_4569_ = lean_uint64_dec_lt(v_pHi_4524_, v_nHi_4526_);
if (v___x_4569_ == 0)
{
uint8_t v___x_4570_; 
v___x_4570_ = lean_uint64_dec_eq(v_pHi_4524_, v_nHi_4526_);
if (v___x_4570_ == 0)
{
v___y_4558_ = v_isZero_4566_;
v___y_4559_ = v___x_4570_;
goto v___jp_4557_;
}
else
{
uint8_t v___x_4571_; 
v___x_4571_ = lean_uint64_dec_lt(v_pLo_4523_, v_nLo_4525_);
v___y_4558_ = v_isZero_4566_;
v___y_4559_ = v___x_4571_;
goto v___jp_4557_;
}
}
else
{
v___y_4551_ = v_isZero_4566_;
goto v___jp_4550_;
}
}
else
{
if (v_negZero_4522_ == 0)
{
uint32_t v___x_4572_; 
v___x_4572_ = 0;
return v___x_4572_;
}
else
{
uint32_t v___x_4573_; 
v___x_4573_ = 2147483648;
return v___x_4573_;
}
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_R24ExactDotCost_nativeLoop___boxed(lean_object* v_a_4703_, lean_object* v_b_4704_, lean_object* v_base_4705_, lean_object* v_index_4706_, lean_object* v_negZero_4707_, lean_object* v_pLo_4708_, lean_object* v_pHi_4709_, lean_object* v_nLo_4710_, lean_object* v_nHi_4711_, lean_object* v_x_4712_){
_start:
{
uint32_t v_base_boxed_4713_; uint8_t v_negZero_boxed_4714_; uint64_t v_pLo_boxed_4715_; uint64_t v_pHi_boxed_4716_; uint64_t v_nLo_boxed_4717_; uint64_t v_nHi_boxed_4718_; uint32_t v_res_4719_; lean_object* v_r_4720_; 
v_base_boxed_4713_ = lean_unbox_uint32(v_base_4705_);
lean_dec(v_base_4705_);
v_negZero_boxed_4714_ = lean_unbox(v_negZero_4707_);
v_pLo_boxed_4715_ = lean_unbox_uint64(v_pLo_4708_);
lean_dec_ref(v_pLo_4708_);
v_pHi_boxed_4716_ = lean_unbox_uint64(v_pHi_4709_);
lean_dec_ref(v_pHi_4709_);
v_nLo_boxed_4717_ = lean_unbox_uint64(v_nLo_4710_);
lean_dec_ref(v_nLo_4710_);
v_nHi_boxed_4718_ = lean_unbox_uint64(v_nHi_4711_);
lean_dec_ref(v_nHi_4711_);
v_res_4719_ = lp_competition_Submission_R24ExactDotCost_nativeLoop(v_a_4703_, v_b_4704_, v_base_boxed_4713_, v_index_4706_, v_negZero_boxed_4714_, v_pLo_boxed_4715_, v_pHi_boxed_4716_, v_nLo_boxed_4717_, v_nHi_boxed_4718_, v_x_4712_);
lean_dec_ref(v_b_4704_);
lean_dec_ref(v_a_4703_);
v_r_4720_ = lean_box_uint32(v_res_4719_);
return v_r_4720_;
}
}
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00__private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00Submission_R24ExactDotCost_referencePrepared_spec__0_spec__0___redArg(lean_object* v___x_4721_, lean_object* v_c_4722_, uint8_t v___x_4723_, lean_object* v_range_4724_, lean_object* v_b_4725_, lean_object* v_i_4726_){
_start:
{
lean_object* v_stop_4727_; lean_object* v_step_4728_; lean_object* v_a_4730_; uint8_t v___x_4733_; 
v_stop_4727_ = lean_ctor_get(v_range_4724_, 1);
v_step_4728_ = lean_ctor_get(v_range_4724_, 2);
v___x_4733_ = lean_nat_dec_lt(v_i_4726_, v_stop_4727_);
if (v___x_4733_ == 0)
{
lean_dec(v_i_4726_);
return v_b_4725_;
}
else
{
lean_object* v_fst_4734_; lean_object* v_snd_4735_; lean_object* v___x_4737_; uint8_t v_isShared_4738_; uint8_t v_isSharedCheck_4858_; 
v_fst_4734_ = lean_ctor_get(v_b_4725_, 0);
v_snd_4735_ = lean_ctor_get(v_b_4725_, 1);
v_isSharedCheck_4858_ = !lean_is_exclusive(v_b_4725_);
if (v_isSharedCheck_4858_ == 0)
{
v___x_4737_ = v_b_4725_;
v_isShared_4738_ = v_isSharedCheck_4858_;
goto v_resetjp_4736_;
}
else
{
lean_inc(v_snd_4735_);
lean_inc(v_fst_4734_);
lean_dec(v_b_4725_);
v___x_4737_ = lean_box(0);
v_isShared_4738_ = v_isSharedCheck_4858_;
goto v_resetjp_4736_;
}
v_resetjp_4736_:
{
uint8_t v___y_4740_; uint8_t v___y_4746_; lean_object* v___y_4747_; lean_object* v_right_4751_; uint32_t v_minScale_4752_; uint32_t v___y_4754_; uint8_t v___y_4755_; uint64_t v___y_4756_; uint8_t v___y_4757_; uint32_t v___y_4758_; lean_object* v_raw_4767_; uint8_t v___x_4768_; uint32_t v___x_4769_; lean_object* v___x_4770_; lean_object* v___x_4771_; lean_object* v___x_4772_; lean_object* v___x_4773_; uint8_t v___y_4775_; uint64_t v___y_4776_; uint8_t v___y_4777_; uint32_t v___y_4778_; uint64_t v___y_4788_; uint8_t v___y_4789_; uint64_t v___y_4803_; uint8_t v___y_4804_; uint64_t v___y_4806_; uint8_t v___y_4807_; uint8_t v___y_4808_; uint64_t v___y_4810_; uint8_t v___y_4811_; uint64_t v___y_4817_; uint64_t v___y_4818_; uint64_t v___y_4825_; uint32_t v___x_4842_; uint32_t v___x_4843_; uint32_t v___x_4844_; uint32_t v___x_4845_; uint32_t v___x_4846_; uint8_t v___x_4847_; 
v_right_4751_ = lean_ctor_get(v_c_4722_, 1);
v_minScale_4752_ = lean_ctor_get_uint32(v_c_4722_, sizeof(void*)*2);
v_raw_4767_ = lean_ctor_get(v_right_4751_, 0);
v___x_4768_ = 0;
v___x_4769_ = 0;
v___x_4770_ = lp_competition_Submission_R24ExactDotCost_prepareOperand___closed__2___boxed__const__1;
v___x_4771_ = lean_array_get_borrowed(v___x_4770_, v___x_4721_, v_i_4726_);
v___x_4772_ = lp_competition_Submission_R24ExactDotCost_prepareOperand___closed__2___boxed__const__1;
v___x_4773_ = lean_array_get_borrowed(v___x_4772_, v_raw_4767_, v_i_4726_);
v___x_4842_ = 23;
v___x_4843_ = lean_unbox_uint32(v___x_4771_);
v___x_4844_ = lean_uint32_shift_right(v___x_4843_, v___x_4842_);
v___x_4845_ = 255;
v___x_4846_ = lean_uint32_land(v___x_4844_, v___x_4845_);
v___x_4847_ = lean_uint32_dec_eq(v___x_4846_, v___x_4769_);
if (v___x_4847_ == 0)
{
uint32_t v___x_4848_; uint32_t v___x_4849_; uint32_t v___x_4850_; uint32_t v___x_4851_; uint32_t v___x_4852_; uint64_t v___x_4853_; 
v___x_4848_ = 8388607;
v___x_4849_ = lean_unbox_uint32(v___x_4771_);
v___x_4850_ = lean_uint32_land(v___x_4849_, v___x_4848_);
v___x_4851_ = 8388608;
v___x_4852_ = lean_uint32_lor(v___x_4850_, v___x_4851_);
v___x_4853_ = lean_uint32_to_uint64(v___x_4852_);
v___y_4825_ = v___x_4853_;
goto v___jp_4824_;
}
else
{
uint32_t v___x_4854_; uint32_t v___x_4855_; uint32_t v___x_4856_; uint64_t v___x_4857_; 
v___x_4854_ = 8388607;
v___x_4855_ = lean_unbox_uint32(v___x_4771_);
v___x_4856_ = lean_uint32_land(v___x_4855_, v___x_4854_);
v___x_4857_ = lean_uint32_to_uint64(v___x_4856_);
v___y_4825_ = v___x_4857_;
goto v___jp_4824_;
}
v___jp_4739_:
{
lean_object* v___x_4741_; lean_object* v___x_4743_; 
v___x_4741_ = lean_box(v___y_4740_);
if (v_isShared_4738_ == 0)
{
lean_ctor_set(v___x_4737_, 1, v___x_4741_);
v___x_4743_ = v___x_4737_;
goto v_reusejp_4742_;
}
else
{
lean_object* v_reuseFailAlloc_4744_; 
v_reuseFailAlloc_4744_ = lean_alloc_ctor(0, 2, 0);
lean_ctor_set(v_reuseFailAlloc_4744_, 0, v_fst_4734_);
lean_ctor_set(v_reuseFailAlloc_4744_, 1, v___x_4741_);
v___x_4743_ = v_reuseFailAlloc_4744_;
goto v_reusejp_4742_;
}
v_reusejp_4742_:
{
v_a_4730_ = v___x_4743_;
goto v___jp_4729_;
}
}
v___jp_4745_:
{
lean_object* v___x_4748_; lean_object* v___x_4749_; lean_object* v___x_4750_; 
v___x_4748_ = lean_int_add(v_fst_4734_, v___y_4747_);
lean_dec(v___y_4747_);
lean_dec(v_fst_4734_);
v___x_4749_ = lean_box(v___y_4746_);
v___x_4750_ = lean_alloc_ctor(0, 2, 0);
lean_ctor_set(v___x_4750_, 0, v___x_4748_);
lean_ctor_set(v___x_4750_, 1, v___x_4749_);
v_a_4730_ = v___x_4750_;
goto v___jp_4729_;
}
v___jp_4753_:
{
uint32_t v___x_4759_; uint32_t v___x_4760_; lean_object* v___x_4761_; lean_object* v___x_4762_; lean_object* v___x_4763_; 
v___x_4759_ = lean_uint32_add(v___y_4754_, v___y_4758_);
v___x_4760_ = lean_uint32_sub(v___x_4759_, v_minScale_4752_);
v___x_4761_ = lean_uint32_to_nat(v___x_4760_);
v___x_4762_ = lean_uint64_to_nat(v___y_4756_);
v___x_4763_ = lean_nat_shiftl(v___x_4762_, v___x_4761_);
lean_dec(v___x_4761_);
lean_dec(v___x_4762_);
if (v___y_4757_ == 0)
{
lean_object* v___x_4764_; 
v___x_4764_ = lean_nat_to_int(v___x_4763_);
v___y_4746_ = v___y_4755_;
v___y_4747_ = v___x_4764_;
goto v___jp_4745_;
}
else
{
lean_object* v___x_4765_; lean_object* v___x_4766_; 
v___x_4765_ = lean_nat_to_int(v___x_4763_);
v___x_4766_ = lean_int_neg(v___x_4765_);
lean_dec(v___x_4765_);
v___y_4746_ = v___y_4755_;
v___y_4747_ = v___x_4766_;
goto v___jp_4745_;
}
}
v___jp_4774_:
{
uint32_t v___x_4779_; uint32_t v___x_4780_; uint32_t v___x_4781_; uint32_t v___x_4782_; uint32_t v___x_4783_; uint8_t v___x_4784_; 
v___x_4779_ = 23;
v___x_4780_ = lean_unbox_uint32(v___x_4773_);
v___x_4781_ = lean_uint32_shift_right(v___x_4780_, v___x_4779_);
v___x_4782_ = 255;
v___x_4783_ = lean_uint32_land(v___x_4781_, v___x_4782_);
v___x_4784_ = lean_uint32_dec_eq(v___x_4783_, v___x_4769_);
if (v___x_4784_ == 0)
{
uint32_t v___x_4785_; uint32_t v___x_4786_; 
v___x_4785_ = 1;
v___x_4786_ = lean_uint32_sub(v___x_4783_, v___x_4785_);
v___y_4754_ = v___y_4778_;
v___y_4755_ = v___y_4775_;
v___y_4756_ = v___y_4776_;
v___y_4757_ = v___y_4777_;
v___y_4758_ = v___x_4786_;
goto v___jp_4753_;
}
else
{
v___y_4754_ = v___y_4778_;
v___y_4755_ = v___y_4775_;
v___y_4756_ = v___y_4776_;
v___y_4757_ = v___y_4777_;
v___y_4758_ = v___x_4769_;
goto v___jp_4753_;
}
}
v___jp_4787_:
{
uint64_t v___x_4790_; uint8_t v___x_4791_; 
v___x_4790_ = 0ULL;
v___x_4791_ = lean_uint64_dec_eq(v___y_4788_, v___x_4790_);
if (v___x_4791_ == 0)
{
uint32_t v___x_4792_; uint32_t v___x_4793_; uint32_t v___x_4794_; uint32_t v___x_4795_; uint32_t v___x_4796_; uint8_t v___x_4797_; 
lean_del_object(v___x_4737_);
lean_dec(v_snd_4735_);
v___x_4792_ = 23;
v___x_4793_ = lean_unbox_uint32(v___x_4771_);
v___x_4794_ = lean_uint32_shift_right(v___x_4793_, v___x_4792_);
v___x_4795_ = 255;
v___x_4796_ = lean_uint32_land(v___x_4794_, v___x_4795_);
v___x_4797_ = lean_uint32_dec_eq(v___x_4796_, v___x_4769_);
if (v___x_4797_ == 0)
{
uint32_t v___x_4798_; uint32_t v___x_4799_; 
v___x_4798_ = 1;
v___x_4799_ = lean_uint32_sub(v___x_4796_, v___x_4798_);
v___y_4775_ = v___x_4791_;
v___y_4776_ = v___y_4788_;
v___y_4777_ = v___y_4789_;
v___y_4778_ = v___x_4799_;
goto v___jp_4774_;
}
else
{
v___y_4775_ = v___x_4791_;
v___y_4776_ = v___y_4788_;
v___y_4777_ = v___y_4789_;
v___y_4778_ = v___x_4769_;
goto v___jp_4774_;
}
}
else
{
uint8_t v___x_4800_; 
v___x_4800_ = lean_unbox(v_snd_4735_);
if (v___x_4800_ == 0)
{
uint8_t v___x_4801_; 
v___x_4801_ = lean_unbox(v_snd_4735_);
lean_dec(v_snd_4735_);
v___y_4740_ = v___x_4801_;
goto v___jp_4739_;
}
else
{
lean_dec(v_snd_4735_);
v___y_4740_ = v___y_4789_;
goto v___jp_4739_;
}
}
}
v___jp_4802_:
{
if (v___y_4804_ == 0)
{
v___y_4788_ = v___y_4803_;
v___y_4789_ = v___x_4723_;
goto v___jp_4787_;
}
else
{
v___y_4788_ = v___y_4803_;
v___y_4789_ = v___x_4768_;
goto v___jp_4787_;
}
}
v___jp_4805_:
{
if (v___y_4807_ == 0)
{
if (v___y_4808_ == 0)
{
v___y_4803_ = v___y_4806_;
v___y_4804_ = v___x_4733_;
goto v___jp_4802_;
}
else
{
v___y_4788_ = v___y_4806_;
v___y_4789_ = v___x_4723_;
goto v___jp_4787_;
}
}
else
{
v___y_4803_ = v___y_4806_;
v___y_4804_ = v___y_4808_;
goto v___jp_4802_;
}
}
v___jp_4809_:
{
uint32_t v___x_4812_; uint32_t v___x_4813_; uint32_t v___x_4814_; uint8_t v___x_4815_; 
v___x_4812_ = 2147483648;
v___x_4813_ = lean_unbox_uint32(v___x_4773_);
v___x_4814_ = lean_uint32_land(v___x_4813_, v___x_4812_);
v___x_4815_ = lean_uint32_dec_eq(v___x_4814_, v___x_4769_);
if (v___x_4815_ == 0)
{
v___y_4806_ = v___y_4810_;
v___y_4807_ = v___y_4811_;
v___y_4808_ = v___x_4723_;
goto v___jp_4805_;
}
else
{
v___y_4806_ = v___y_4810_;
v___y_4807_ = v___y_4811_;
v___y_4808_ = v___x_4768_;
goto v___jp_4805_;
}
}
v___jp_4816_:
{
uint64_t v___x_4819_; uint32_t v___x_4820_; uint32_t v___x_4821_; uint32_t v___x_4822_; uint8_t v___x_4823_; 
v___x_4819_ = lean_uint64_mul(v___y_4817_, v___y_4818_);
v___x_4820_ = 2147483648;
v___x_4821_ = lean_unbox_uint32(v___x_4771_);
v___x_4822_ = lean_uint32_land(v___x_4821_, v___x_4820_);
v___x_4823_ = lean_uint32_dec_eq(v___x_4822_, v___x_4769_);
if (v___x_4823_ == 0)
{
v___y_4810_ = v___x_4819_;
v___y_4811_ = v___x_4723_;
goto v___jp_4809_;
}
else
{
v___y_4810_ = v___x_4819_;
v___y_4811_ = v___x_4768_;
goto v___jp_4809_;
}
}
v___jp_4824_:
{
uint32_t v___x_4826_; uint32_t v___x_4827_; uint32_t v___x_4828_; uint32_t v___x_4829_; uint32_t v___x_4830_; uint8_t v___x_4831_; 
v___x_4826_ = 23;
v___x_4827_ = lean_unbox_uint32(v___x_4773_);
v___x_4828_ = lean_uint32_shift_right(v___x_4827_, v___x_4826_);
v___x_4829_ = 255;
v___x_4830_ = lean_uint32_land(v___x_4828_, v___x_4829_);
v___x_4831_ = lean_uint32_dec_eq(v___x_4830_, v___x_4769_);
if (v___x_4831_ == 0)
{
uint32_t v___x_4832_; uint32_t v___x_4833_; uint32_t v___x_4834_; uint32_t v___x_4835_; uint32_t v___x_4836_; uint64_t v___x_4837_; 
v___x_4832_ = 8388607;
v___x_4833_ = lean_unbox_uint32(v___x_4773_);
v___x_4834_ = lean_uint32_land(v___x_4833_, v___x_4832_);
v___x_4835_ = 8388608;
v___x_4836_ = lean_uint32_lor(v___x_4834_, v___x_4835_);
v___x_4837_ = lean_uint32_to_uint64(v___x_4836_);
v___y_4817_ = v___y_4825_;
v___y_4818_ = v___x_4837_;
goto v___jp_4816_;
}
else
{
uint32_t v___x_4838_; uint32_t v___x_4839_; uint32_t v___x_4840_; uint64_t v___x_4841_; 
v___x_4838_ = 8388607;
v___x_4839_ = lean_unbox_uint32(v___x_4773_);
v___x_4840_ = lean_uint32_land(v___x_4839_, v___x_4838_);
v___x_4841_ = lean_uint32_to_uint64(v___x_4840_);
v___y_4817_ = v___y_4825_;
v___y_4818_ = v___x_4841_;
goto v___jp_4816_;
}
}
}
}
v___jp_4729_:
{
lean_object* v___x_4731_; 
v___x_4731_ = lean_nat_add(v_i_4726_, v_step_4728_);
lean_dec(v_i_4726_);
v_b_4725_ = v_a_4730_;
v_i_4726_ = v___x_4731_;
goto _start;
}
}
}
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00__private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00Submission_R24ExactDotCost_referencePrepared_spec__0_spec__0___redArg___boxed(lean_object* v___x_4859_, lean_object* v_c_4860_, lean_object* v___x_4861_, lean_object* v_range_4862_, lean_object* v_b_4863_, lean_object* v_i_4864_){
_start:
{
uint8_t v___x_3872__boxed_4865_; lean_object* v_res_4866_; 
v___x_3872__boxed_4865_ = lean_unbox(v___x_4861_);
v_res_4866_ = lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00__private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00Submission_R24ExactDotCost_referencePrepared_spec__0_spec__0___redArg(v___x_4859_, v_c_4860_, v___x_3872__boxed_4865_, v_range_4862_, v_b_4863_, v_i_4864_);
lean_dec_ref(v_range_4862_);
lean_dec_ref(v_c_4860_);
lean_dec_ref(v___x_4859_);
return v_res_4866_;
}
}
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00Submission_R24ExactDotCost_referencePrepared_spec__0___redArg(lean_object* v___x_4867_, lean_object* v_c_4868_, uint8_t v___x_4869_, lean_object* v_range_4870_, lean_object* v_b_4871_, lean_object* v_i_4872_){
_start:
{
lean_object* v_stop_4873_; lean_object* v_step_4874_; lean_object* v_a_4876_; uint8_t v___x_4879_; 
v_stop_4873_ = lean_ctor_get(v_range_4870_, 1);
v_step_4874_ = lean_ctor_get(v_range_4870_, 2);
v___x_4879_ = lean_nat_dec_lt(v_i_4872_, v_stop_4873_);
if (v___x_4879_ == 0)
{
return v_b_4871_;
}
else
{
lean_object* v_fst_4880_; lean_object* v_snd_4881_; lean_object* v___x_4883_; uint8_t v_isShared_4884_; uint8_t v_isSharedCheck_5004_; 
v_fst_4880_ = lean_ctor_get(v_b_4871_, 0);
v_snd_4881_ = lean_ctor_get(v_b_4871_, 1);
v_isSharedCheck_5004_ = !lean_is_exclusive(v_b_4871_);
if (v_isSharedCheck_5004_ == 0)
{
v___x_4883_ = v_b_4871_;
v_isShared_4884_ = v_isSharedCheck_5004_;
goto v_resetjp_4882_;
}
else
{
lean_inc(v_snd_4881_);
lean_inc(v_fst_4880_);
lean_dec(v_b_4871_);
v___x_4883_ = lean_box(0);
v_isShared_4884_ = v_isSharedCheck_5004_;
goto v_resetjp_4882_;
}
v_resetjp_4882_:
{
uint8_t v___y_4886_; uint8_t v___y_4892_; lean_object* v___y_4893_; lean_object* v_right_4897_; uint32_t v_minScale_4898_; uint8_t v___y_4900_; uint8_t v___y_4901_; uint64_t v___y_4902_; uint32_t v___y_4903_; uint32_t v___y_4904_; lean_object* v_raw_4913_; uint8_t v___x_4914_; uint32_t v___x_4915_; lean_object* v___x_4916_; lean_object* v___x_4917_; lean_object* v___x_4918_; lean_object* v___x_4919_; uint8_t v___y_4921_; uint8_t v___y_4922_; uint64_t v___y_4923_; uint32_t v___y_4924_; uint64_t v___y_4934_; uint8_t v___y_4935_; uint64_t v___y_4949_; uint8_t v___y_4950_; uint8_t v___y_4952_; uint64_t v___y_4953_; uint8_t v___y_4954_; uint64_t v___y_4956_; uint8_t v___y_4957_; uint64_t v___y_4963_; uint64_t v___y_4964_; uint64_t v___y_4971_; uint32_t v___x_4988_; uint32_t v___x_4989_; uint32_t v___x_4990_; uint32_t v___x_4991_; uint32_t v___x_4992_; uint8_t v___x_4993_; 
v_right_4897_ = lean_ctor_get(v_c_4868_, 1);
v_minScale_4898_ = lean_ctor_get_uint32(v_c_4868_, sizeof(void*)*2);
v_raw_4913_ = lean_ctor_get(v_right_4897_, 0);
v___x_4914_ = 0;
v___x_4915_ = 0;
v___x_4916_ = lp_competition_Submission_R24ExactDotCost_prepareOperand___closed__2___boxed__const__1;
v___x_4917_ = lean_array_get_borrowed(v___x_4916_, v___x_4867_, v_i_4872_);
v___x_4918_ = lp_competition_Submission_R24ExactDotCost_prepareOperand___closed__2___boxed__const__1;
v___x_4919_ = lean_array_get_borrowed(v___x_4918_, v_raw_4913_, v_i_4872_);
v___x_4988_ = 23;
v___x_4989_ = lean_unbox_uint32(v___x_4917_);
v___x_4990_ = lean_uint32_shift_right(v___x_4989_, v___x_4988_);
v___x_4991_ = 255;
v___x_4992_ = lean_uint32_land(v___x_4990_, v___x_4991_);
v___x_4993_ = lean_uint32_dec_eq(v___x_4992_, v___x_4915_);
if (v___x_4993_ == 0)
{
uint32_t v___x_4994_; uint32_t v___x_4995_; uint32_t v___x_4996_; uint32_t v___x_4997_; uint32_t v___x_4998_; uint64_t v___x_4999_; 
v___x_4994_ = 8388607;
v___x_4995_ = lean_unbox_uint32(v___x_4917_);
v___x_4996_ = lean_uint32_land(v___x_4995_, v___x_4994_);
v___x_4997_ = 8388608;
v___x_4998_ = lean_uint32_lor(v___x_4996_, v___x_4997_);
v___x_4999_ = lean_uint32_to_uint64(v___x_4998_);
v___y_4971_ = v___x_4999_;
goto v___jp_4970_;
}
else
{
uint32_t v___x_5000_; uint32_t v___x_5001_; uint32_t v___x_5002_; uint64_t v___x_5003_; 
v___x_5000_ = 8388607;
v___x_5001_ = lean_unbox_uint32(v___x_4917_);
v___x_5002_ = lean_uint32_land(v___x_5001_, v___x_5000_);
v___x_5003_ = lean_uint32_to_uint64(v___x_5002_);
v___y_4971_ = v___x_5003_;
goto v___jp_4970_;
}
v___jp_4885_:
{
lean_object* v___x_4887_; lean_object* v___x_4889_; 
v___x_4887_ = lean_box(v___y_4886_);
if (v_isShared_4884_ == 0)
{
lean_ctor_set(v___x_4883_, 1, v___x_4887_);
v___x_4889_ = v___x_4883_;
goto v_reusejp_4888_;
}
else
{
lean_object* v_reuseFailAlloc_4890_; 
v_reuseFailAlloc_4890_ = lean_alloc_ctor(0, 2, 0);
lean_ctor_set(v_reuseFailAlloc_4890_, 0, v_fst_4880_);
lean_ctor_set(v_reuseFailAlloc_4890_, 1, v___x_4887_);
v___x_4889_ = v_reuseFailAlloc_4890_;
goto v_reusejp_4888_;
}
v_reusejp_4888_:
{
v_a_4876_ = v___x_4889_;
goto v___jp_4875_;
}
}
v___jp_4891_:
{
lean_object* v___x_4894_; lean_object* v___x_4895_; lean_object* v___x_4896_; 
v___x_4894_ = lean_int_add(v_fst_4880_, v___y_4893_);
lean_dec(v___y_4893_);
lean_dec(v_fst_4880_);
v___x_4895_ = lean_box(v___y_4892_);
v___x_4896_ = lean_alloc_ctor(0, 2, 0);
lean_ctor_set(v___x_4896_, 0, v___x_4894_);
lean_ctor_set(v___x_4896_, 1, v___x_4895_);
v_a_4876_ = v___x_4896_;
goto v___jp_4875_;
}
v___jp_4899_:
{
uint32_t v___x_4905_; uint32_t v___x_4906_; lean_object* v___x_4907_; lean_object* v___x_4908_; lean_object* v___x_4909_; 
v___x_4905_ = lean_uint32_add(v___y_4903_, v___y_4904_);
v___x_4906_ = lean_uint32_sub(v___x_4905_, v_minScale_4898_);
v___x_4907_ = lean_uint32_to_nat(v___x_4906_);
v___x_4908_ = lean_uint64_to_nat(v___y_4902_);
v___x_4909_ = lean_nat_shiftl(v___x_4908_, v___x_4907_);
lean_dec(v___x_4907_);
lean_dec(v___x_4908_);
if (v___y_4901_ == 0)
{
lean_object* v___x_4910_; 
v___x_4910_ = lean_nat_to_int(v___x_4909_);
v___y_4892_ = v___y_4900_;
v___y_4893_ = v___x_4910_;
goto v___jp_4891_;
}
else
{
lean_object* v___x_4911_; lean_object* v___x_4912_; 
v___x_4911_ = lean_nat_to_int(v___x_4909_);
v___x_4912_ = lean_int_neg(v___x_4911_);
lean_dec(v___x_4911_);
v___y_4892_ = v___y_4900_;
v___y_4893_ = v___x_4912_;
goto v___jp_4891_;
}
}
v___jp_4920_:
{
uint32_t v___x_4925_; uint32_t v___x_4926_; uint32_t v___x_4927_; uint32_t v___x_4928_; uint32_t v___x_4929_; uint8_t v___x_4930_; 
v___x_4925_ = 23;
v___x_4926_ = lean_unbox_uint32(v___x_4919_);
v___x_4927_ = lean_uint32_shift_right(v___x_4926_, v___x_4925_);
v___x_4928_ = 255;
v___x_4929_ = lean_uint32_land(v___x_4927_, v___x_4928_);
v___x_4930_ = lean_uint32_dec_eq(v___x_4929_, v___x_4915_);
if (v___x_4930_ == 0)
{
uint32_t v___x_4931_; uint32_t v___x_4932_; 
v___x_4931_ = 1;
v___x_4932_ = lean_uint32_sub(v___x_4929_, v___x_4931_);
v___y_4900_ = v___y_4921_;
v___y_4901_ = v___y_4922_;
v___y_4902_ = v___y_4923_;
v___y_4903_ = v___y_4924_;
v___y_4904_ = v___x_4932_;
goto v___jp_4899_;
}
else
{
v___y_4900_ = v___y_4921_;
v___y_4901_ = v___y_4922_;
v___y_4902_ = v___y_4923_;
v___y_4903_ = v___y_4924_;
v___y_4904_ = v___x_4915_;
goto v___jp_4899_;
}
}
v___jp_4933_:
{
uint64_t v___x_4936_; uint8_t v___x_4937_; 
v___x_4936_ = 0ULL;
v___x_4937_ = lean_uint64_dec_eq(v___y_4934_, v___x_4936_);
if (v___x_4937_ == 0)
{
uint32_t v___x_4938_; uint32_t v___x_4939_; uint32_t v___x_4940_; uint32_t v___x_4941_; uint32_t v___x_4942_; uint8_t v___x_4943_; 
lean_del_object(v___x_4883_);
lean_dec(v_snd_4881_);
v___x_4938_ = 23;
v___x_4939_ = lean_unbox_uint32(v___x_4917_);
v___x_4940_ = lean_uint32_shift_right(v___x_4939_, v___x_4938_);
v___x_4941_ = 255;
v___x_4942_ = lean_uint32_land(v___x_4940_, v___x_4941_);
v___x_4943_ = lean_uint32_dec_eq(v___x_4942_, v___x_4915_);
if (v___x_4943_ == 0)
{
uint32_t v___x_4944_; uint32_t v___x_4945_; 
v___x_4944_ = 1;
v___x_4945_ = lean_uint32_sub(v___x_4942_, v___x_4944_);
v___y_4921_ = v___x_4937_;
v___y_4922_ = v___y_4935_;
v___y_4923_ = v___y_4934_;
v___y_4924_ = v___x_4945_;
goto v___jp_4920_;
}
else
{
v___y_4921_ = v___x_4937_;
v___y_4922_ = v___y_4935_;
v___y_4923_ = v___y_4934_;
v___y_4924_ = v___x_4915_;
goto v___jp_4920_;
}
}
else
{
uint8_t v___x_4946_; 
v___x_4946_ = lean_unbox(v_snd_4881_);
if (v___x_4946_ == 0)
{
uint8_t v___x_4947_; 
v___x_4947_ = lean_unbox(v_snd_4881_);
lean_dec(v_snd_4881_);
v___y_4886_ = v___x_4947_;
goto v___jp_4885_;
}
else
{
lean_dec(v_snd_4881_);
v___y_4886_ = v___y_4935_;
goto v___jp_4885_;
}
}
}
v___jp_4948_:
{
if (v___y_4950_ == 0)
{
v___y_4934_ = v___y_4949_;
v___y_4935_ = v___x_4869_;
goto v___jp_4933_;
}
else
{
v___y_4934_ = v___y_4949_;
v___y_4935_ = v___x_4914_;
goto v___jp_4933_;
}
}
v___jp_4951_:
{
if (v___y_4952_ == 0)
{
if (v___y_4954_ == 0)
{
v___y_4949_ = v___y_4953_;
v___y_4950_ = v___x_4879_;
goto v___jp_4948_;
}
else
{
v___y_4934_ = v___y_4953_;
v___y_4935_ = v___x_4869_;
goto v___jp_4933_;
}
}
else
{
v___y_4949_ = v___y_4953_;
v___y_4950_ = v___y_4954_;
goto v___jp_4948_;
}
}
v___jp_4955_:
{
uint32_t v___x_4958_; uint32_t v___x_4959_; uint32_t v___x_4960_; uint8_t v___x_4961_; 
v___x_4958_ = 2147483648;
v___x_4959_ = lean_unbox_uint32(v___x_4919_);
v___x_4960_ = lean_uint32_land(v___x_4959_, v___x_4958_);
v___x_4961_ = lean_uint32_dec_eq(v___x_4960_, v___x_4915_);
if (v___x_4961_ == 0)
{
v___y_4952_ = v___y_4957_;
v___y_4953_ = v___y_4956_;
v___y_4954_ = v___x_4869_;
goto v___jp_4951_;
}
else
{
v___y_4952_ = v___y_4957_;
v___y_4953_ = v___y_4956_;
v___y_4954_ = v___x_4914_;
goto v___jp_4951_;
}
}
v___jp_4962_:
{
uint64_t v___x_4965_; uint32_t v___x_4966_; uint32_t v___x_4967_; uint32_t v___x_4968_; uint8_t v___x_4969_; 
v___x_4965_ = lean_uint64_mul(v___y_4963_, v___y_4964_);
v___x_4966_ = 2147483648;
v___x_4967_ = lean_unbox_uint32(v___x_4917_);
v___x_4968_ = lean_uint32_land(v___x_4967_, v___x_4966_);
v___x_4969_ = lean_uint32_dec_eq(v___x_4968_, v___x_4915_);
if (v___x_4969_ == 0)
{
v___y_4956_ = v___x_4965_;
v___y_4957_ = v___x_4869_;
goto v___jp_4955_;
}
else
{
v___y_4956_ = v___x_4965_;
v___y_4957_ = v___x_4914_;
goto v___jp_4955_;
}
}
v___jp_4970_:
{
uint32_t v___x_4972_; uint32_t v___x_4973_; uint32_t v___x_4974_; uint32_t v___x_4975_; uint32_t v___x_4976_; uint8_t v___x_4977_; 
v___x_4972_ = 23;
v___x_4973_ = lean_unbox_uint32(v___x_4919_);
v___x_4974_ = lean_uint32_shift_right(v___x_4973_, v___x_4972_);
v___x_4975_ = 255;
v___x_4976_ = lean_uint32_land(v___x_4974_, v___x_4975_);
v___x_4977_ = lean_uint32_dec_eq(v___x_4976_, v___x_4915_);
if (v___x_4977_ == 0)
{
uint32_t v___x_4978_; uint32_t v___x_4979_; uint32_t v___x_4980_; uint32_t v___x_4981_; uint32_t v___x_4982_; uint64_t v___x_4983_; 
v___x_4978_ = 8388607;
v___x_4979_ = lean_unbox_uint32(v___x_4919_);
v___x_4980_ = lean_uint32_land(v___x_4979_, v___x_4978_);
v___x_4981_ = 8388608;
v___x_4982_ = lean_uint32_lor(v___x_4980_, v___x_4981_);
v___x_4983_ = lean_uint32_to_uint64(v___x_4982_);
v___y_4963_ = v___y_4971_;
v___y_4964_ = v___x_4983_;
goto v___jp_4962_;
}
else
{
uint32_t v___x_4984_; uint32_t v___x_4985_; uint32_t v___x_4986_; uint64_t v___x_4987_; 
v___x_4984_ = 8388607;
v___x_4985_ = lean_unbox_uint32(v___x_4919_);
v___x_4986_ = lean_uint32_land(v___x_4985_, v___x_4984_);
v___x_4987_ = lean_uint32_to_uint64(v___x_4986_);
v___y_4963_ = v___y_4971_;
v___y_4964_ = v___x_4987_;
goto v___jp_4962_;
}
}
}
}
v___jp_4875_:
{
lean_object* v___x_4877_; lean_object* v___x_4878_; 
v___x_4877_ = lean_nat_add(v_i_4872_, v_step_4874_);
v___x_4878_ = lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00__private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00Submission_R24ExactDotCost_referencePrepared_spec__0_spec__0___redArg(v___x_4867_, v_c_4868_, v___x_4869_, v_range_4870_, v_a_4876_, v___x_4877_);
return v___x_4878_;
}
}
}
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00Submission_R24ExactDotCost_referencePrepared_spec__0___redArg___boxed(lean_object* v___x_5005_, lean_object* v_c_5006_, lean_object* v___x_5007_, lean_object* v_range_5008_, lean_object* v_b_5009_, lean_object* v_i_5010_){
_start:
{
uint8_t v___x_4132__boxed_5011_; lean_object* v_res_5012_; 
v___x_4132__boxed_5011_ = lean_unbox(v___x_5007_);
v_res_5012_ = lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00Submission_R24ExactDotCost_referencePrepared_spec__0___redArg(v___x_5005_, v_c_5006_, v___x_4132__boxed_5011_, v_range_5008_, v_b_5009_, v_i_5010_);
lean_dec(v_i_5010_);
lean_dec_ref(v_range_5008_);
lean_dec_ref(v_c_5006_);
lean_dec_ref(v___x_5005_);
return v_res_5012_;
}
}
static lean_object* _init_lp_competition_Submission_R24ExactDotCost_referencePrepared___closed__0(void){
_start:
{
lean_object* v___x_5013_; lean_object* v___x_5014_; 
v___x_5013_ = lean_unsigned_to_nat(126u);
v___x_5014_ = lean_nat_to_int(v___x_5013_);
return v___x_5014_;
}
}
static lean_object* _init_lp_competition_Submission_R24ExactDotCost_referencePrepared___closed__1(void){
_start:
{
lean_object* v___x_5015_; lean_object* v___x_5016_; 
v___x_5015_ = lean_obj_once(&lp_competition_Submission_R24ExactDotCost_referencePrepared___closed__0, &lp_competition_Submission_R24ExactDotCost_referencePrepared___closed__0_once, _init_lp_competition_Submission_R24ExactDotCost_referencePrepared___closed__0);
v___x_5016_ = lean_int_neg(v___x_5015_);
return v___x_5016_;
}
}
LEAN_EXPORT uint32_t lp_competition_Submission_R24ExactDotCost_referencePrepared(lean_object* v_c_5017_){
_start:
{
uint32_t v___y_5019_; lean_object* v___y_5023_; uint32_t v___y_5024_; lean_object* v___y_5030_; lean_object* v___y_5031_; uint32_t v___y_5032_; lean_object* v___y_5044_; uint8_t v___y_5045_; lean_object* v___y_5046_; lean_object* v___y_5047_; uint8_t v___y_5055_; uint8_t v___y_5056_; lean_object* v___y_5057_; lean_object* v___y_5058_; lean_object* v___y_5065_; lean_object* v___y_5066_; uint8_t v___y_5067_; lean_object* v___y_5068_; uint8_t v_matched_5073_; 
v_matched_5073_ = lean_ctor_get_uint8(v_c_5017_, sizeof(void*)*2 + 8);
if (v_matched_5073_ == 0)
{
uint32_t v___x_5074_; 
v___x_5074_ = 2143289344;
return v___x_5074_;
}
else
{
lean_object* v_left_5075_; uint8_t v_finite_5076_; 
v_left_5075_ = lean_ctor_get(v_c_5017_, 0);
v_finite_5076_ = lean_ctor_get_uint8(v_left_5075_, sizeof(void*)*2 + 9);
if (v_finite_5076_ == 0)
{
uint32_t v___x_5077_; 
v___x_5077_ = 2143289344;
return v___x_5077_;
}
else
{
lean_object* v_right_5078_; uint8_t v_finite_5079_; 
v_right_5078_ = lean_ctor_get(v_c_5017_, 1);
v_finite_5079_ = lean_ctor_get_uint8(v_right_5078_, sizeof(void*)*2 + 9);
if (v_finite_5079_ == 0)
{
uint32_t v___x_5080_; 
v___x_5080_ = 2143289344;
return v___x_5080_;
}
else
{
uint32_t v_minScale_5081_; lean_object* v_raw_5082_; lean_object* v___x_5083_; uint8_t v___y_5085_; lean_object* v___y_5086_; lean_object* v___y_5097_; lean_object* v___y_5098_; uint8_t v___y_5099_; lean_object* v_total_5158_; lean_object* v___x_5159_; uint8_t v___y_5161_; uint8_t v___x_5172_; 
v_minScale_5081_ = lean_ctor_get_uint32(v_c_5017_, sizeof(void*)*2);
v_raw_5082_ = lean_ctor_get(v_left_5075_, 0);
v___x_5083_ = lean_unsigned_to_nat(0u);
v_total_5158_ = lean_obj_once(&lp_competition_Submission_R24ExactDotCost_round128___closed__3, &lp_competition_Submission_R24ExactDotCost_round128___closed__3_once, _init_lp_competition_Submission_R24ExactDotCost_round128___closed__3);
v___x_5159_ = lean_array_get_size(v_raw_5082_);
v___x_5172_ = lean_nat_dec_eq(v___x_5159_, v___x_5083_);
if (v___x_5172_ == 0)
{
v___y_5161_ = v_finite_5079_;
goto v___jp_5160_;
}
else
{
uint8_t v___x_5173_; 
v___x_5173_ = 0;
v___y_5161_ = v___x_5173_;
goto v___jp_5160_;
}
v___jp_5084_:
{
uint8_t v___x_5087_; 
v___x_5087_ = lean_nat_dec_eq(v___y_5086_, v___x_5083_);
if (v___x_5087_ == 0)
{
lean_object* v___x_5088_; uint8_t v___x_5089_; 
v___x_5088_ = lean_unsigned_to_nat(8388608u);
v___x_5089_ = lean_nat_dec_eq(v___y_5086_, v___x_5088_);
if (v___x_5089_ == 0)
{
if (v___y_5085_ == 0)
{
uint32_t v___x_5090_; 
v___x_5090_ = 0;
v___y_5023_ = v___y_5086_;
v___y_5024_ = v___x_5090_;
goto v___jp_5022_;
}
else
{
uint32_t v___x_5091_; 
v___x_5091_ = 2147483648;
v___y_5023_ = v___y_5086_;
v___y_5024_ = v___x_5091_;
goto v___jp_5022_;
}
}
else
{
lean_dec(v___y_5086_);
if (v___y_5085_ == 0)
{
uint32_t v___x_5092_; 
v___x_5092_ = 0;
v___y_5019_ = v___x_5092_;
goto v___jp_5018_;
}
else
{
uint32_t v___x_5093_; 
v___x_5093_ = 2147483648;
v___y_5019_ = v___x_5093_;
goto v___jp_5018_;
}
}
}
else
{
lean_dec(v___y_5086_);
if (v___y_5085_ == 0)
{
uint32_t v___x_5094_; 
v___x_5094_ = 0;
return v___x_5094_;
}
else
{
uint32_t v___x_5095_; 
v___x_5095_ = 2147483648;
return v___x_5095_;
}
}
}
v___jp_5096_:
{
lean_object* v___x_5100_; uint8_t v___x_5101_; 
v___x_5100_ = lean_nat_abs(v___y_5098_);
lean_dec(v___y_5098_);
v___x_5101_ = lean_nat_dec_eq(v___x_5100_, v___x_5083_);
if (v___x_5101_ == 0)
{
lean_object* v___x_5102_; lean_object* v___x_5103_; lean_object* v___x_5104_; lean_object* v___x_5105_; lean_object* v_leading_5106_; lean_object* v___x_5107_; lean_object* v_totalExponent_5108_; lean_object* v___x_5109_; uint8_t v___x_5110_; 
v___x_5102_ = lean_uint32_to_nat(v_minScale_5081_);
v___x_5103_ = lean_nat_to_int(v___x_5102_);
v___x_5104_ = lean_obj_once(&lp_competition_Submission_R24ExactDotCost_finish___closed__0, &lp_competition_Submission_R24ExactDotCost_finish___closed__0_once, _init_lp_competition_Submission_R24ExactDotCost_finish___closed__0);
v___x_5105_ = lean_int_sub(v___x_5103_, v___x_5104_);
lean_dec(v___x_5103_);
v_leading_5106_ = lean_nat_log2(v___x_5100_);
lean_inc(v_leading_5106_);
v___x_5107_ = lean_nat_to_int(v_leading_5106_);
v_totalExponent_5108_ = lean_int_add(v___x_5107_, v___x_5105_);
lean_dec(v___x_5107_);
v___x_5109_ = lean_obj_once(&lp_competition_Submission_R24ExactDotCost_referencePrepared___closed__1, &lp_competition_Submission_R24ExactDotCost_referencePrepared___closed__1_once, _init_lp_competition_Submission_R24ExactDotCost_referencePrepared___closed__1);
v___x_5110_ = lean_int_dec_lt(v_totalExponent_5108_, v___x_5109_);
if (v___x_5110_ == 0)
{
lean_object* v___x_5111_; uint8_t v___x_5112_; 
lean_dec(v___x_5105_);
v___x_5111_ = lean_unsigned_to_nat(23u);
v___x_5112_ = lean_nat_dec_le(v___x_5111_, v_leading_5106_);
if (v___x_5112_ == 0)
{
lean_object* v___x_5113_; lean_object* v___x_5114_; 
v___x_5113_ = lean_nat_sub(v___x_5111_, v_leading_5106_);
lean_dec(v_leading_5106_);
v___x_5114_ = lean_nat_shiftl(v___x_5100_, v___x_5113_);
lean_dec(v___x_5113_);
lean_dec(v___x_5100_);
v___y_5065_ = v___y_5097_;
v___y_5066_ = v_totalExponent_5108_;
v___y_5067_ = v___y_5099_;
v___y_5068_ = v___x_5114_;
goto v___jp_5064_;
}
else
{
lean_object* v___x_5115_; uint8_t v___x_5116_; 
v___x_5115_ = lean_nat_sub(v_leading_5106_, v___x_5111_);
v___x_5116_ = lean_nat_dec_eq(v___x_5115_, v___x_5083_);
if (v___x_5116_ == 0)
{
lean_object* v___x_5117_; uint8_t v___x_5118_; 
v___x_5117_ = lean_nat_add(v_leading_5106_, v___y_5097_);
lean_dec(v_leading_5106_);
v___x_5118_ = lean_nat_dec_lt(v___x_5117_, v___x_5115_);
lean_dec(v___x_5117_);
if (v___x_5118_ == 0)
{
lean_object* v_quotient_5119_; lean_object* v___x_5120_; lean_object* v_remainder_5121_; lean_object* v___x_5122_; lean_object* v_half_5123_; uint8_t v___x_5124_; 
v_quotient_5119_ = lean_nat_shiftr(v___x_5100_, v___x_5115_);
v___x_5120_ = lean_nat_shiftl(v_quotient_5119_, v___x_5115_);
v_remainder_5121_ = lean_nat_sub(v___x_5100_, v___x_5120_);
lean_dec(v___x_5120_);
lean_dec(v___x_5100_);
v___x_5122_ = lean_nat_sub(v___x_5115_, v___y_5097_);
lean_dec(v___x_5115_);
v_half_5123_ = lean_nat_shiftl(v___y_5097_, v___x_5122_);
lean_dec(v___x_5122_);
v___x_5124_ = lean_nat_dec_lt(v_remainder_5121_, v_half_5123_);
if (v___x_5124_ == 0)
{
uint8_t v___x_5125_; 
v___x_5125_ = lean_nat_dec_lt(v_half_5123_, v_remainder_5121_);
lean_dec(v_remainder_5121_);
lean_dec(v_half_5123_);
if (v___x_5125_ == 0)
{
lean_object* v___x_5126_; lean_object* v___x_5127_; uint8_t v___x_5128_; 
v___x_5126_ = lean_unsigned_to_nat(2u);
v___x_5127_ = lean_nat_mod(v_quotient_5119_, v___x_5126_);
v___x_5128_ = lean_nat_dec_eq(v___x_5127_, v___x_5083_);
lean_dec(v___x_5127_);
if (v___x_5128_ == 0)
{
lean_object* v___x_5129_; 
v___x_5129_ = lean_nat_add(v_quotient_5119_, v___y_5097_);
lean_dec(v_quotient_5119_);
v___y_5065_ = v___y_5097_;
v___y_5066_ = v_totalExponent_5108_;
v___y_5067_ = v___y_5099_;
v___y_5068_ = v___x_5129_;
goto v___jp_5064_;
}
else
{
v___y_5065_ = v___y_5097_;
v___y_5066_ = v_totalExponent_5108_;
v___y_5067_ = v___y_5099_;
v___y_5068_ = v_quotient_5119_;
goto v___jp_5064_;
}
}
else
{
lean_object* v___x_5130_; 
v___x_5130_ = lean_nat_add(v_quotient_5119_, v___y_5097_);
lean_dec(v_quotient_5119_);
v___y_5065_ = v___y_5097_;
v___y_5066_ = v_totalExponent_5108_;
v___y_5067_ = v___y_5099_;
v___y_5068_ = v___x_5130_;
goto v___jp_5064_;
}
}
else
{
lean_dec(v_half_5123_);
lean_dec(v_remainder_5121_);
v___y_5065_ = v___y_5097_;
v___y_5066_ = v_totalExponent_5108_;
v___y_5067_ = v___y_5099_;
v___y_5068_ = v_quotient_5119_;
goto v___jp_5064_;
}
}
else
{
lean_dec(v___x_5115_);
lean_dec(v___x_5100_);
v___y_5065_ = v___y_5097_;
v___y_5066_ = v_totalExponent_5108_;
v___y_5067_ = v___y_5099_;
v___y_5068_ = v___x_5083_;
goto v___jp_5064_;
}
}
else
{
lean_dec(v___x_5115_);
lean_dec(v_leading_5106_);
v___y_5065_ = v___y_5097_;
v___y_5066_ = v_totalExponent_5108_;
v___y_5067_ = v___y_5099_;
v___y_5068_ = v___x_5100_;
goto v___jp_5064_;
}
}
}
else
{
lean_object* v___x_5131_; lean_object* v___x_5132_; lean_object* v_intZero_5133_; uint8_t v_isNeg_5134_; 
lean_dec(v_totalExponent_5108_);
v___x_5131_ = lean_obj_once(&lp_competition_Submission_R24ExactDotCost_round128___closed__7, &lp_competition_Submission_R24ExactDotCost_round128___closed__7_once, _init_lp_competition_Submission_R24ExactDotCost_round128___closed__7);
v___x_5132_ = lean_int_add(v___x_5105_, v___x_5131_);
lean_dec(v___x_5105_);
v_intZero_5133_ = lean_obj_once(&lp_competition_Submission_R24ExactDotCost_round128___closed__3, &lp_competition_Submission_R24ExactDotCost_round128___closed__3_once, _init_lp_competition_Submission_R24ExactDotCost_round128___closed__3);
v_isNeg_5134_ = lean_int_dec_lt(v___x_5132_, v_intZero_5133_);
if (v_isNeg_5134_ == 0)
{
lean_object* v_a_5135_; lean_object* v___x_5136_; 
lean_dec(v_leading_5106_);
lean_dec(v___y_5097_);
v_a_5135_ = lean_nat_abs(v___x_5132_);
lean_dec(v___x_5132_);
v___x_5136_ = lean_nat_shiftl(v___x_5100_, v_a_5135_);
lean_dec(v_a_5135_);
lean_dec(v___x_5100_);
v___y_5085_ = v___y_5099_;
v___y_5086_ = v___x_5136_;
goto v___jp_5084_;
}
else
{
lean_object* v_abs_5137_; lean_object* v_one_5138_; lean_object* v_a_5139_; lean_object* v___x_5140_; uint8_t v___x_5141_; 
v_abs_5137_ = lean_nat_abs(v___x_5132_);
lean_dec(v___x_5132_);
v_one_5138_ = lean_unsigned_to_nat(1u);
v_a_5139_ = lean_nat_sub(v_abs_5137_, v_one_5138_);
lean_dec(v_abs_5137_);
v___x_5140_ = lean_nat_add(v_a_5139_, v___y_5097_);
lean_dec(v_a_5139_);
v___x_5141_ = lean_nat_dec_eq(v___x_5140_, v___x_5083_);
if (v___x_5141_ == 0)
{
lean_object* v___x_5142_; uint8_t v___x_5143_; 
v___x_5142_ = lean_nat_add(v_leading_5106_, v___y_5097_);
lean_dec(v_leading_5106_);
v___x_5143_ = lean_nat_dec_lt(v___x_5142_, v___x_5140_);
lean_dec(v___x_5142_);
if (v___x_5143_ == 0)
{
lean_object* v_quotient_5144_; lean_object* v___x_5145_; lean_object* v_remainder_5146_; lean_object* v___x_5147_; lean_object* v_half_5148_; uint8_t v___x_5149_; 
v_quotient_5144_ = lean_nat_shiftr(v___x_5100_, v___x_5140_);
v___x_5145_ = lean_nat_shiftl(v_quotient_5144_, v___x_5140_);
v_remainder_5146_ = lean_nat_sub(v___x_5100_, v___x_5145_);
lean_dec(v___x_5145_);
lean_dec(v___x_5100_);
v___x_5147_ = lean_nat_sub(v___x_5140_, v___y_5097_);
lean_dec(v___x_5140_);
v_half_5148_ = lean_nat_shiftl(v___y_5097_, v___x_5147_);
lean_dec(v___x_5147_);
v___x_5149_ = lean_nat_dec_lt(v_remainder_5146_, v_half_5148_);
if (v___x_5149_ == 0)
{
uint8_t v___x_5150_; 
v___x_5150_ = lean_nat_dec_lt(v_half_5148_, v_remainder_5146_);
lean_dec(v_remainder_5146_);
lean_dec(v_half_5148_);
if (v___x_5150_ == 0)
{
lean_object* v___x_5151_; lean_object* v___x_5152_; uint8_t v___x_5153_; 
v___x_5151_ = lean_unsigned_to_nat(2u);
v___x_5152_ = lean_nat_mod(v_quotient_5144_, v___x_5151_);
v___x_5153_ = lean_nat_dec_eq(v___x_5152_, v___x_5083_);
lean_dec(v___x_5152_);
if (v___x_5153_ == 0)
{
lean_object* v___x_5154_; 
v___x_5154_ = lean_nat_add(v_quotient_5144_, v___y_5097_);
lean_dec(v___y_5097_);
lean_dec(v_quotient_5144_);
v___y_5085_ = v___y_5099_;
v___y_5086_ = v___x_5154_;
goto v___jp_5084_;
}
else
{
lean_dec(v___y_5097_);
v___y_5085_ = v___y_5099_;
v___y_5086_ = v_quotient_5144_;
goto v___jp_5084_;
}
}
else
{
lean_object* v___x_5155_; 
v___x_5155_ = lean_nat_add(v_quotient_5144_, v___y_5097_);
lean_dec(v___y_5097_);
lean_dec(v_quotient_5144_);
v___y_5085_ = v___y_5099_;
v___y_5086_ = v___x_5155_;
goto v___jp_5084_;
}
}
else
{
lean_dec(v_half_5148_);
lean_dec(v_remainder_5146_);
lean_dec(v___y_5097_);
v___y_5085_ = v___y_5099_;
v___y_5086_ = v_quotient_5144_;
goto v___jp_5084_;
}
}
else
{
lean_dec(v___x_5140_);
lean_dec(v___x_5100_);
lean_dec(v___y_5097_);
v___y_5085_ = v___y_5099_;
v___y_5086_ = v___x_5083_;
goto v___jp_5084_;
}
}
else
{
lean_dec(v___x_5140_);
lean_dec(v_leading_5106_);
lean_dec(v___y_5097_);
v___y_5085_ = v___y_5099_;
v___y_5086_ = v___x_5100_;
goto v___jp_5084_;
}
}
}
}
else
{
lean_dec(v___x_5100_);
lean_dec(v___y_5097_);
if (v___y_5099_ == 0)
{
uint32_t v___x_5156_; 
v___x_5156_ = 0;
return v___x_5156_;
}
else
{
uint32_t v___x_5157_; 
v___x_5157_ = 2147483648;
return v___x_5157_;
}
}
}
v___jp_5160_:
{
lean_object* v___x_5162_; lean_object* v___x_5163_; lean_object* v___x_5164_; lean_object* v___x_5165_; lean_object* v___x_5166_; lean_object* v_fst_5167_; lean_object* v_snd_5168_; uint8_t v___x_5169_; 
v___x_5162_ = lean_unsigned_to_nat(1u);
v___x_5163_ = lean_alloc_ctor(0, 3, 0);
lean_ctor_set(v___x_5163_, 0, v___x_5083_);
lean_ctor_set(v___x_5163_, 1, v___x_5159_);
lean_ctor_set(v___x_5163_, 2, v___x_5162_);
v___x_5164_ = lean_box(v___y_5161_);
v___x_5165_ = lean_alloc_ctor(0, 2, 0);
lean_ctor_set(v___x_5165_, 0, v_total_5158_);
lean_ctor_set(v___x_5165_, 1, v___x_5164_);
v___x_5166_ = lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00Submission_R24ExactDotCost_referencePrepared_spec__0___redArg(v_raw_5082_, v_c_5017_, v_finite_5079_, v___x_5163_, v___x_5165_, v___x_5083_);
lean_dec_ref_known(v___x_5163_, 3);
v_fst_5167_ = lean_ctor_get(v___x_5166_, 0);
lean_inc(v_fst_5167_);
v_snd_5168_ = lean_ctor_get(v___x_5166_, 1);
lean_inc(v_snd_5168_);
lean_dec_ref(v___x_5166_);
v___x_5169_ = lean_int_dec_eq(v_fst_5167_, v_total_5158_);
if (v___x_5169_ == 0)
{
uint8_t v___x_5170_; 
lean_dec(v_snd_5168_);
v___x_5170_ = lean_int_dec_lt(v_fst_5167_, v_total_5158_);
v___y_5097_ = v___x_5162_;
v___y_5098_ = v_fst_5167_;
v___y_5099_ = v___x_5170_;
goto v___jp_5096_;
}
else
{
uint8_t v___x_5171_; 
v___x_5171_ = lean_unbox(v_snd_5168_);
lean_dec(v_snd_5168_);
v___y_5097_ = v___x_5162_;
v___y_5098_ = v_fst_5167_;
v___y_5099_ = v___x_5171_;
goto v___jp_5096_;
}
}
}
}
}
v___jp_5018_:
{
uint32_t v_exponentBits_5020_; uint32_t v___x_5021_; 
v_exponentBits_5020_ = 8388608;
v___x_5021_ = lean_uint32_lor(v___y_5019_, v_exponentBits_5020_);
return v___x_5021_;
}
v___jp_5022_:
{
uint32_t v___x_5025_; uint32_t v___x_5026_; uint32_t v_fractionBits_5027_; uint32_t v___x_5028_; 
v___x_5025_ = lean_uint32_of_nat(v___y_5023_);
lean_dec(v___y_5023_);
v___x_5026_ = 8388607;
v_fractionBits_5027_ = lean_uint32_land(v___x_5025_, v___x_5026_);
v___x_5028_ = lean_uint32_lor(v___y_5024_, v_fractionBits_5027_);
return v___x_5028_;
}
v___jp_5029_:
{
uint32_t v___x_5033_; uint32_t v___x_5034_; uint32_t v___x_5035_; uint32_t v___x_5036_; uint32_t v_exponentBits_5037_; uint32_t v___x_5038_; uint32_t v___x_5039_; uint32_t v_fractionBits_5040_; uint32_t v___x_5041_; uint32_t v___x_5042_; 
v___x_5033_ = lean_uint32_of_nat(v___y_5030_);
lean_dec(v___y_5030_);
v___x_5034_ = 255;
v___x_5035_ = lean_uint32_land(v___x_5033_, v___x_5034_);
v___x_5036_ = 23;
v_exponentBits_5037_ = lean_uint32_shift_left(v___x_5035_, v___x_5036_);
v___x_5038_ = lean_uint32_of_nat(v___y_5031_);
lean_dec(v___y_5031_);
v___x_5039_ = 8388607;
v_fractionBits_5040_ = lean_uint32_land(v___x_5038_, v___x_5039_);
v___x_5041_ = lean_uint32_lor(v___y_5032_, v_exponentBits_5037_);
v___x_5042_ = lean_uint32_lor(v___x_5041_, v_fractionBits_5040_);
return v___x_5042_;
}
v___jp_5043_:
{
lean_object* v___x_5048_; lean_object* v_encodedExponent_5049_; lean_object* v___x_5050_; lean_object* v_fraction_5051_; 
v___x_5048_ = lean_int_add(v___y_5044_, v___y_5046_);
lean_dec(v___y_5044_);
v_encodedExponent_5049_ = l_Int_toNat(v___x_5048_);
lean_dec(v___x_5048_);
v___x_5050_ = lean_unsigned_to_nat(8388608u);
v_fraction_5051_ = lean_nat_sub(v___y_5047_, v___x_5050_);
lean_dec(v___y_5047_);
if (v___y_5045_ == 0)
{
uint32_t v___x_5052_; 
v___x_5052_ = 0;
v___y_5030_ = v_encodedExponent_5049_;
v___y_5031_ = v_fraction_5051_;
v___y_5032_ = v___x_5052_;
goto v___jp_5029_;
}
else
{
uint32_t v___x_5053_; 
v___x_5053_ = 2147483648;
v___y_5030_ = v_encodedExponent_5049_;
v___y_5031_ = v_fraction_5051_;
v___y_5032_ = v___x_5053_;
goto v___jp_5029_;
}
}
v___jp_5054_:
{
lean_object* v___x_5059_; uint8_t v___x_5060_; 
v___x_5059_ = lean_obj_once(&lp_competition_Submission_R24ExactDotCost_round128___closed__5, &lp_competition_Submission_R24ExactDotCost_round128___closed__5_once, _init_lp_competition_Submission_R24ExactDotCost_round128___closed__5);
v___x_5060_ = lean_int_dec_lt(v___x_5059_, v___y_5058_);
if (v___x_5060_ == 0)
{
if (v___y_5055_ == 0)
{
v___y_5044_ = v___y_5058_;
v___y_5045_ = v___y_5056_;
v___y_5046_ = v___x_5059_;
v___y_5047_ = v___y_5057_;
goto v___jp_5043_;
}
else
{
lean_object* v___x_5061_; 
lean_dec(v___y_5057_);
v___x_5061_ = lean_unsigned_to_nat(8388608u);
v___y_5044_ = v___y_5058_;
v___y_5045_ = v___y_5056_;
v___y_5046_ = v___x_5059_;
v___y_5047_ = v___x_5061_;
goto v___jp_5043_;
}
}
else
{
lean_dec(v___y_5058_);
lean_dec(v___y_5057_);
if (v___y_5056_ == 0)
{
uint32_t v___x_5062_; 
v___x_5062_ = 2139095040;
return v___x_5062_;
}
else
{
uint32_t v___x_5063_; 
v___x_5063_ = 4286578688;
return v___x_5063_;
}
}
}
v___jp_5064_:
{
lean_object* v___x_5069_; uint8_t v_carry_5070_; 
v___x_5069_ = lean_unsigned_to_nat(16777216u);
v_carry_5070_ = lean_nat_dec_eq(v___y_5068_, v___x_5069_);
if (v_carry_5070_ == 0)
{
lean_dec(v___y_5065_);
v___y_5055_ = v_carry_5070_;
v___y_5056_ = v___y_5067_;
v___y_5057_ = v___y_5068_;
v___y_5058_ = v___y_5066_;
goto v___jp_5054_;
}
else
{
lean_object* v___x_5071_; lean_object* v___x_5072_; 
v___x_5071_ = lean_nat_to_int(v___y_5065_);
v___x_5072_ = lean_int_add(v___y_5066_, v___x_5071_);
lean_dec(v___x_5071_);
lean_dec(v___y_5066_);
v___y_5055_ = v_carry_5070_;
v___y_5056_ = v___y_5067_;
v___y_5057_ = v___y_5068_;
v___y_5058_ = v___x_5072_;
goto v___jp_5054_;
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_R24ExactDotCost_referencePrepared___boxed(lean_object* v_c_5174_){
_start:
{
uint32_t v_res_5175_; lean_object* v_r_5176_; 
v_res_5175_ = lp_competition_Submission_R24ExactDotCost_referencePrepared(v_c_5174_);
lean_dec_ref(v_c_5174_);
v_r_5176_ = lean_box_uint32(v_res_5175_);
return v_r_5176_;
}
}
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00Submission_R24ExactDotCost_referencePrepared_spec__0(lean_object* v___x_5177_, lean_object* v_c_5178_, uint8_t v___x_5179_, lean_object* v_range_5180_, lean_object* v_b_5181_, lean_object* v_i_5182_, lean_object* v_hs_5183_, lean_object* v_hl_5184_){
_start:
{
lean_object* v___x_5185_; 
v___x_5185_ = lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00Submission_R24ExactDotCost_referencePrepared_spec__0___redArg(v___x_5177_, v_c_5178_, v___x_5179_, v_range_5180_, v_b_5181_, v_i_5182_);
return v___x_5185_;
}
}
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00Submission_R24ExactDotCost_referencePrepared_spec__0___boxed(lean_object* v___x_5186_, lean_object* v_c_5187_, lean_object* v___x_5188_, lean_object* v_range_5189_, lean_object* v_b_5190_, lean_object* v_i_5191_, lean_object* v_hs_5192_, lean_object* v_hl_5193_){
_start:
{
uint8_t v___x_4666__boxed_5194_; lean_object* v_res_5195_; 
v___x_4666__boxed_5194_ = lean_unbox(v___x_5188_);
v_res_5195_ = lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00Submission_R24ExactDotCost_referencePrepared_spec__0(v___x_5186_, v_c_5187_, v___x_4666__boxed_5194_, v_range_5189_, v_b_5190_, v_i_5191_, v_hs_5192_, v_hl_5193_);
lean_dec(v_i_5191_);
lean_dec_ref(v_range_5189_);
lean_dec_ref(v_c_5187_);
lean_dec_ref(v___x_5186_);
return v_res_5195_;
}
}
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00__private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00Submission_R24ExactDotCost_referencePrepared_spec__0_spec__0(lean_object* v___x_5196_, lean_object* v_c_5197_, uint8_t v___x_5198_, lean_object* v_range_5199_, lean_object* v_b_5200_, lean_object* v_i_5201_, lean_object* v_hs_5202_, lean_object* v_hl_5203_){
_start:
{
lean_object* v___x_5204_; 
v___x_5204_ = lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00__private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00Submission_R24ExactDotCost_referencePrepared_spec__0_spec__0___redArg(v___x_5196_, v_c_5197_, v___x_5198_, v_range_5199_, v_b_5200_, v_i_5201_);
return v___x_5204_;
}
}
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00__private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00Submission_R24ExactDotCost_referencePrepared_spec__0_spec__0___boxed(lean_object* v___x_5205_, lean_object* v_c_5206_, lean_object* v___x_5207_, lean_object* v_range_5208_, lean_object* v_b_5209_, lean_object* v_i_5210_, lean_object* v_hs_5211_, lean_object* v_hl_5212_){
_start:
{
uint8_t v___x_4674__boxed_5213_; lean_object* v_res_5214_; 
v___x_4674__boxed_5213_ = lean_unbox(v___x_5207_);
v_res_5214_ = lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00__private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00Submission_R24ExactDotCost_referencePrepared_spec__0_spec__0(v___x_5205_, v_c_5206_, v___x_4674__boxed_5213_, v_range_5208_, v_b_5209_, v_i_5210_, v_hs_5211_, v_hl_5212_);
lean_dec_ref(v_range_5208_);
lean_dec_ref(v_c_5206_);
lean_dec_ref(v___x_5205_);
return v_res_5214_;
}
}
LEAN_EXPORT uint32_t lp_competition_Submission_R24ExactDotCost_exactPrepared(lean_object* v_c_5215_){
_start:
{
uint8_t v_matched_5216_; 
v_matched_5216_ = lean_ctor_get_uint8(v_c_5215_, sizeof(void*)*2 + 8);
if (v_matched_5216_ == 0)
{
uint32_t v___x_5217_; 
v___x_5217_ = lp_competition_Submission_R24ExactDotCost_referencePrepared(v_c_5215_);
return v___x_5217_;
}
else
{
lean_object* v_left_5218_; uint8_t v_normal_5219_; 
v_left_5218_ = lean_ctor_get(v_c_5215_, 0);
v_normal_5219_ = lean_ctor_get_uint8(v_left_5218_, sizeof(void*)*2 + 8);
if (v_normal_5219_ == 0)
{
uint32_t v___x_5220_; 
v___x_5220_ = lp_competition_Submission_R24ExactDotCost_referencePrepared(v_c_5215_);
return v___x_5220_;
}
else
{
lean_object* v_right_5221_; uint8_t v_normal_5222_; 
v_right_5221_ = lean_ctor_get(v_c_5215_, 1);
v_normal_5222_ = lean_ctor_get_uint8(v_right_5221_, sizeof(void*)*2 + 8);
if (v_normal_5222_ == 0)
{
uint32_t v___x_5223_; 
v___x_5223_ = lp_competition_Submission_R24ExactDotCost_referencePrepared(v_c_5215_);
return v___x_5223_;
}
else
{
uint32_t v_minScale_5224_; uint32_t v_maxScale_5225_; lean_object* v_data_5226_; lean_object* v_data_5227_; lean_object* v___x_5228_; lean_object* v___y_5230_; uint8_t v___y_5231_; lean_object* v___x_5234_; uint8_t v___x_5235_; 
v_minScale_5224_ = lean_ctor_get_uint32(v_c_5215_, sizeof(void*)*2);
v_maxScale_5225_ = lean_ctor_get_uint32(v_c_5215_, sizeof(void*)*2 + 4);
v_data_5226_ = lean_ctor_get(v_left_5218_, 1);
v_data_5227_ = lean_ctor_get(v_right_5221_, 1);
v___x_5228_ = lean_array_get_size(v_data_5226_);
v___x_5234_ = lean_unsigned_to_nat(1048576u);
v___x_5235_ = lean_nat_dec_le(v___x_5228_, v___x_5234_);
if (v___x_5235_ == 0)
{
uint32_t v___x_5236_; 
v___x_5236_ = lp_competition_Submission_R24ExactDotCost_referencePrepared(v_c_5215_);
return v___x_5236_;
}
else
{
lean_object* v___x_5237_; lean_object* v___x_5238_; lean_object* v___x_5239_; lean_object* v___x_5240_; lean_object* v___x_5241_; lean_object* v___y_5243_; lean_object* v___x_5251_; uint64_t v___y_5253_; uint64_t v___y_5257_; uint64_t v___y_5258_; uint64_t v___y_5265_; uint64_t v___y_5266_; uint64_t v___y_5267_; uint64_t v___y_5268_; uint64_t v___y_5274_; uint64_t v___y_5275_; uint64_t v___y_5281_; uint64_t v___y_5282_; uint64_t v___y_5283_; uint64_t v___y_5284_; uint64_t v___y_5290_; uint64_t v___y_5291_; uint64_t v___y_5297_; uint64_t v___y_5298_; uint64_t v___y_5299_; uint64_t v___y_5300_; uint64_t v___y_5306_; uint64_t v___y_5307_; uint64_t v___y_5313_; uint64_t v___y_5314_; uint64_t v___y_5315_; uint64_t v___y_5316_; uint64_t v___y_5322_; uint64_t v___y_5323_; uint8_t v___x_5328_; 
v___x_5237_ = lean_unsigned_to_nat(48u);
v___x_5238_ = lean_uint32_to_nat(v_maxScale_5225_);
v___x_5239_ = lean_uint32_to_nat(v_minScale_5224_);
v___x_5240_ = lean_nat_sub(v___x_5238_, v___x_5239_);
lean_dec(v___x_5239_);
lean_dec(v___x_5238_);
v___x_5241_ = lean_nat_add(v___x_5237_, v___x_5240_);
lean_dec(v___x_5240_);
v___x_5251_ = lean_unsigned_to_nat(1u);
v___x_5328_ = lean_nat_dec_le(v___x_5228_, v___x_5251_);
if (v___x_5328_ == 0)
{
lean_object* v___x_5329_; uint64_t v___x_5330_; uint64_t v___x_5331_; uint64_t v___y_5333_; uint64_t v___x_5337_; uint64_t v___x_5338_; uint8_t v___x_5339_; 
v___x_5329_ = lean_nat_sub(v___x_5228_, v___x_5251_);
v___x_5330_ = lean_uint64_of_nat(v___x_5329_);
lean_dec(v___x_5329_);
v___x_5331_ = 32ULL;
v___x_5337_ = lean_uint64_shift_right(v___x_5330_, v___x_5331_);
v___x_5338_ = 0ULL;
v___x_5339_ = lean_uint64_dec_eq(v___x_5337_, v___x_5338_);
if (v___x_5339_ == 0)
{
v___y_5333_ = v___x_5337_;
goto v___jp_5332_;
}
else
{
v___y_5333_ = v___x_5330_;
goto v___jp_5332_;
}
v___jp_5332_:
{
uint64_t v___x_5334_; uint64_t v___x_5335_; uint8_t v___x_5336_; 
v___x_5334_ = lean_uint64_shift_right(v___x_5330_, v___x_5331_);
v___x_5335_ = 0ULL;
v___x_5336_ = lean_uint64_dec_eq(v___x_5334_, v___x_5335_);
if (v___x_5336_ == 0)
{
v___y_5322_ = v___y_5333_;
v___y_5323_ = v___x_5331_;
goto v___jp_5321_;
}
else
{
v___y_5322_ = v___y_5333_;
v___y_5323_ = v___x_5335_;
goto v___jp_5321_;
}
}
}
else
{
lean_object* v___x_5340_; 
v___x_5340_ = lean_unsigned_to_nat(0u);
v___y_5243_ = v___x_5340_;
goto v___jp_5242_;
}
v___jp_5242_:
{
lean_object* v___x_5244_; lean_object* v___x_5245_; uint8_t v___x_5246_; 
v___x_5244_ = lean_nat_add(v___x_5241_, v___y_5243_);
lean_dec(v___y_5243_);
lean_dec(v___x_5241_);
v___x_5245_ = lean_unsigned_to_nat(128u);
v___x_5246_ = lean_nat_dec_le(v___x_5244_, v___x_5245_);
lean_dec(v___x_5244_);
if (v___x_5246_ == 0)
{
uint32_t v___x_5247_; 
v___x_5247_ = lp_competition_Submission_R24ExactDotCost_referencePrepared(v_c_5215_);
return v___x_5247_;
}
else
{
lean_object* v___x_5248_; uint8_t v___x_5249_; 
v___x_5248_ = lean_unsigned_to_nat(0u);
v___x_5249_ = lean_nat_dec_eq(v___x_5228_, v___x_5248_);
if (v___x_5249_ == 0)
{
v___y_5230_ = v___x_5248_;
v___y_5231_ = v___x_5246_;
goto v___jp_5229_;
}
else
{
uint8_t v___x_5250_; 
v___x_5250_ = 0;
v___y_5230_ = v___x_5248_;
v___y_5231_ = v___x_5250_;
goto v___jp_5229_;
}
}
}
v___jp_5252_:
{
lean_object* v___x_5254_; lean_object* v___x_5255_; 
v___x_5254_ = lean_uint64_to_nat(v___y_5253_);
v___x_5255_ = lean_nat_add(v___x_5254_, v___x_5251_);
lean_dec(v___x_5254_);
v___y_5243_ = v___x_5255_;
goto v___jp_5242_;
}
v___jp_5256_:
{
uint64_t v___x_5259_; uint64_t v___x_5260_; uint64_t v___x_5261_; uint8_t v___x_5262_; 
v___x_5259_ = 1ULL;
v___x_5260_ = lean_uint64_shift_right(v___y_5257_, v___x_5259_);
v___x_5261_ = 0ULL;
v___x_5262_ = lean_uint64_dec_eq(v___x_5260_, v___x_5261_);
if (v___x_5262_ == 0)
{
uint64_t v___x_5263_; 
v___x_5263_ = lean_uint64_add(v___y_5258_, v___x_5259_);
v___y_5253_ = v___x_5263_;
goto v___jp_5252_;
}
else
{
v___y_5253_ = v___y_5258_;
goto v___jp_5252_;
}
}
v___jp_5264_:
{
uint64_t v___x_5269_; uint64_t v___x_5270_; uint8_t v___x_5271_; 
v___x_5269_ = lean_uint64_shift_right(v___y_5267_, v___y_5266_);
v___x_5270_ = 0ULL;
v___x_5271_ = lean_uint64_dec_eq(v___x_5269_, v___x_5270_);
if (v___x_5271_ == 0)
{
uint64_t v___x_5272_; 
v___x_5272_ = lean_uint64_add(v___y_5265_, v___y_5266_);
v___y_5257_ = v___y_5268_;
v___y_5258_ = v___x_5272_;
goto v___jp_5256_;
}
else
{
v___y_5257_ = v___y_5268_;
v___y_5258_ = v___y_5265_;
goto v___jp_5256_;
}
}
v___jp_5273_:
{
uint64_t v___x_5276_; uint64_t v___x_5277_; uint64_t v___x_5278_; uint8_t v___x_5279_; 
v___x_5276_ = 2ULL;
v___x_5277_ = lean_uint64_shift_right(v___y_5274_, v___x_5276_);
v___x_5278_ = 0ULL;
v___x_5279_ = lean_uint64_dec_eq(v___x_5277_, v___x_5278_);
if (v___x_5279_ == 0)
{
v___y_5265_ = v___y_5275_;
v___y_5266_ = v___x_5276_;
v___y_5267_ = v___y_5274_;
v___y_5268_ = v___x_5277_;
goto v___jp_5264_;
}
else
{
v___y_5265_ = v___y_5275_;
v___y_5266_ = v___x_5276_;
v___y_5267_ = v___y_5274_;
v___y_5268_ = v___y_5274_;
goto v___jp_5264_;
}
}
v___jp_5280_:
{
uint64_t v___x_5285_; uint64_t v___x_5286_; uint8_t v___x_5287_; 
v___x_5285_ = lean_uint64_shift_right(v___y_5281_, v___y_5282_);
v___x_5286_ = 0ULL;
v___x_5287_ = lean_uint64_dec_eq(v___x_5285_, v___x_5286_);
if (v___x_5287_ == 0)
{
uint64_t v___x_5288_; 
v___x_5288_ = lean_uint64_add(v___y_5283_, v___y_5282_);
v___y_5274_ = v___y_5284_;
v___y_5275_ = v___x_5288_;
goto v___jp_5273_;
}
else
{
v___y_5274_ = v___y_5284_;
v___y_5275_ = v___y_5283_;
goto v___jp_5273_;
}
}
v___jp_5289_:
{
uint64_t v___x_5292_; uint64_t v___x_5293_; uint64_t v___x_5294_; uint8_t v___x_5295_; 
v___x_5292_ = 4ULL;
v___x_5293_ = lean_uint64_shift_right(v___y_5290_, v___x_5292_);
v___x_5294_ = 0ULL;
v___x_5295_ = lean_uint64_dec_eq(v___x_5293_, v___x_5294_);
if (v___x_5295_ == 0)
{
v___y_5281_ = v___y_5290_;
v___y_5282_ = v___x_5292_;
v___y_5283_ = v___y_5291_;
v___y_5284_ = v___x_5293_;
goto v___jp_5280_;
}
else
{
v___y_5281_ = v___y_5290_;
v___y_5282_ = v___x_5292_;
v___y_5283_ = v___y_5291_;
v___y_5284_ = v___y_5290_;
goto v___jp_5280_;
}
}
v___jp_5296_:
{
uint64_t v___x_5301_; uint64_t v___x_5302_; uint8_t v___x_5303_; 
v___x_5301_ = lean_uint64_shift_right(v___y_5298_, v___y_5297_);
v___x_5302_ = 0ULL;
v___x_5303_ = lean_uint64_dec_eq(v___x_5301_, v___x_5302_);
if (v___x_5303_ == 0)
{
uint64_t v___x_5304_; 
v___x_5304_ = lean_uint64_add(v___y_5299_, v___y_5297_);
v___y_5290_ = v___y_5300_;
v___y_5291_ = v___x_5304_;
goto v___jp_5289_;
}
else
{
v___y_5290_ = v___y_5300_;
v___y_5291_ = v___y_5299_;
goto v___jp_5289_;
}
}
v___jp_5305_:
{
uint64_t v___x_5308_; uint64_t v___x_5309_; uint64_t v___x_5310_; uint8_t v___x_5311_; 
v___x_5308_ = 8ULL;
v___x_5309_ = lean_uint64_shift_right(v___y_5306_, v___x_5308_);
v___x_5310_ = 0ULL;
v___x_5311_ = lean_uint64_dec_eq(v___x_5309_, v___x_5310_);
if (v___x_5311_ == 0)
{
v___y_5297_ = v___x_5308_;
v___y_5298_ = v___y_5306_;
v___y_5299_ = v___y_5307_;
v___y_5300_ = v___x_5309_;
goto v___jp_5296_;
}
else
{
v___y_5297_ = v___x_5308_;
v___y_5298_ = v___y_5306_;
v___y_5299_ = v___y_5307_;
v___y_5300_ = v___y_5306_;
goto v___jp_5296_;
}
}
v___jp_5312_:
{
uint64_t v___x_5317_; uint64_t v___x_5318_; uint8_t v___x_5319_; 
v___x_5317_ = lean_uint64_shift_right(v___y_5313_, v___y_5314_);
v___x_5318_ = 0ULL;
v___x_5319_ = lean_uint64_dec_eq(v___x_5317_, v___x_5318_);
if (v___x_5319_ == 0)
{
uint64_t v___x_5320_; 
v___x_5320_ = lean_uint64_add(v___y_5315_, v___y_5314_);
v___y_5306_ = v___y_5316_;
v___y_5307_ = v___x_5320_;
goto v___jp_5305_;
}
else
{
v___y_5306_ = v___y_5316_;
v___y_5307_ = v___y_5315_;
goto v___jp_5305_;
}
}
v___jp_5321_:
{
uint64_t v___x_5324_; uint64_t v___x_5325_; uint64_t v___x_5326_; uint8_t v___x_5327_; 
v___x_5324_ = 16ULL;
v___x_5325_ = lean_uint64_shift_right(v___y_5322_, v___x_5324_);
v___x_5326_ = 0ULL;
v___x_5327_ = lean_uint64_dec_eq(v___x_5325_, v___x_5326_);
if (v___x_5327_ == 0)
{
v___y_5313_ = v___y_5322_;
v___y_5314_ = v___x_5324_;
v___y_5315_ = v___y_5323_;
v___y_5316_ = v___x_5325_;
goto v___jp_5312_;
}
else
{
v___y_5313_ = v___y_5322_;
v___y_5314_ = v___x_5324_;
v___y_5315_ = v___y_5323_;
v___y_5316_ = v___y_5322_;
goto v___jp_5312_;
}
}
}
v___jp_5229_:
{
uint64_t v___x_5232_; uint32_t v___x_5233_; 
v___x_5232_ = 0ULL;
v___x_5233_ = lp_competition_Submission_R24ExactDotCost_nativeLoop(v_data_5226_, v_data_5227_, v_minScale_5224_, v___y_5230_, v___y_5231_, v___x_5232_, v___x_5232_, v___x_5232_, v___x_5232_, v___x_5228_);
return v___x_5233_;
}
}
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_R24ExactDotCost_exactPrepared___boxed(lean_object* v_c_5341_){
_start:
{
uint32_t v_res_5342_; lean_object* v_r_5343_; 
v_res_5342_ = lp_competition_Submission_R24ExactDotCost_exactPrepared(v_c_5341_);
lean_dec_ref(v_c_5341_);
v_r_5343_ = lean_box_uint32(v_res_5342_);
return v_r_5343_;
}
}
LEAN_EXPORT uint32_t lp_competition_Submission_R24ExactDotCost_full(lean_object* v_rawA_5344_, lean_object* v_rawB_5345_){
_start:
{
uint32_t v___y_5347_; lean_object* v___y_5348_; lean_object* v___y_5349_; lean_object* v___y_5350_; lean_object* v___y_5351_; uint8_t v___y_5352_; uint32_t v___y_5356_; lean_object* v___y_5357_; lean_object* v___y_5358_; lean_object* v___y_5359_; lean_object* v___y_5360_; lean_object* v___y_5361_; lean_object* v___y_5362_; uint32_t v___y_5371_; lean_object* v___y_5372_; lean_object* v___y_5373_; lean_object* v___y_5374_; lean_object* v___y_5375_; lean_object* v___y_5376_; lean_object* v___y_5377_; uint64_t v___y_5378_; uint32_t v___y_5382_; uint64_t v___y_5383_; lean_object* v___y_5384_; lean_object* v___y_5385_; lean_object* v___y_5386_; lean_object* v___y_5387_; lean_object* v___y_5388_; lean_object* v___y_5389_; uint64_t v___y_5390_; uint32_t v___y_5397_; lean_object* v___y_5398_; uint64_t v___y_5399_; lean_object* v___y_5400_; lean_object* v___y_5401_; lean_object* v___y_5402_; uint64_t v___y_5403_; lean_object* v___y_5404_; lean_object* v___y_5405_; uint64_t v___y_5406_; uint64_t v___y_5407_; uint32_t v___y_5413_; lean_object* v___y_5414_; lean_object* v___y_5415_; lean_object* v___y_5416_; lean_object* v___y_5417_; lean_object* v___y_5418_; lean_object* v___y_5419_; uint64_t v___y_5420_; uint64_t v___y_5421_; uint64_t v___y_5427_; uint64_t v___y_5428_; uint32_t v___y_5429_; uint64_t v___y_5430_; lean_object* v___y_5431_; lean_object* v___y_5432_; lean_object* v___y_5433_; lean_object* v___y_5434_; lean_object* v___y_5435_; lean_object* v___y_5436_; uint64_t v___y_5437_; uint32_t v___y_5443_; lean_object* v___y_5444_; uint64_t v___y_5445_; lean_object* v___y_5446_; lean_object* v___y_5447_; lean_object* v___y_5448_; lean_object* v___y_5449_; lean_object* v___y_5450_; uint64_t v___y_5451_; uint32_t v___y_5457_; uint64_t v___y_5458_; lean_object* v___y_5459_; lean_object* v___y_5460_; uint64_t v___y_5461_; lean_object* v___y_5462_; lean_object* v___y_5463_; lean_object* v___y_5464_; uint64_t v___y_5465_; lean_object* v___y_5466_; uint64_t v___y_5467_; uint32_t v___y_5473_; lean_object* v___y_5474_; uint64_t v___y_5475_; lean_object* v___y_5476_; lean_object* v___y_5477_; lean_object* v___y_5478_; lean_object* v___y_5479_; lean_object* v___y_5480_; uint64_t v___y_5481_; uint64_t v___y_5487_; uint32_t v___y_5488_; lean_object* v___y_5489_; lean_object* v___y_5490_; lean_object* v___y_5491_; lean_object* v___y_5492_; lean_object* v___y_5493_; uint64_t v___y_5494_; uint64_t v___y_5495_; lean_object* v___y_5496_; uint64_t v___y_5497_; uint32_t v___y_5503_; lean_object* v___y_5504_; lean_object* v___y_5505_; lean_object* v___y_5506_; lean_object* v___y_5507_; lean_object* v___y_5508_; uint64_t v___y_5509_; lean_object* v___y_5510_; uint64_t v___y_5511_; uint64_t v___y_5517_; uint32_t v___y_5518_; uint64_t v___y_5519_; lean_object* v___y_5520_; lean_object* v___y_5521_; lean_object* v___y_5522_; lean_object* v___y_5523_; lean_object* v___y_5524_; lean_object* v___y_5525_; uint64_t v___y_5526_; lean_object* v___x_5530_; uint8_t v_hasNonzero_5531_; lean_object* v___x_5532_; uint32_t v___y_5534_; uint32_t v___y_5535_; 
v___x_5530_ = lp_competition_Submission_R24ExactDotCost_prepareOperand(v_rawA_5344_);
v_hasNonzero_5531_ = lean_ctor_get_uint8(v___x_5530_, sizeof(void*)*2 + 10);
v___x_5532_ = lp_competition_Submission_R24ExactDotCost_prepareOperand(v_rawB_5345_);
if (v_hasNonzero_5531_ == 0)
{
goto v___jp_5567_;
}
else
{
uint8_t v_hasNonzero_5569_; 
v_hasNonzero_5569_ = lean_ctor_get_uint8(v___x_5532_, sizeof(void*)*2 + 10);
if (v_hasNonzero_5569_ == 0)
{
goto v___jp_5567_;
}
else
{
uint32_t v_minIdx_5570_; uint32_t v_minIdx_5571_; uint32_t v_maxIdx_5572_; uint32_t v_maxIdx_5573_; uint32_t v___x_5574_; uint32_t v___x_5575_; 
v_minIdx_5570_ = lean_ctor_get_uint32(v___x_5530_, sizeof(void*)*2);
v_minIdx_5571_ = lean_ctor_get_uint32(v___x_5532_, sizeof(void*)*2);
v_maxIdx_5572_ = lean_ctor_get_uint32(v___x_5530_, sizeof(void*)*2 + 4);
v_maxIdx_5573_ = lean_ctor_get_uint32(v___x_5532_, sizeof(void*)*2 + 4);
v___x_5574_ = lean_uint32_add(v_minIdx_5570_, v_minIdx_5571_);
v___x_5575_ = lean_uint32_add(v_maxIdx_5572_, v_maxIdx_5573_);
v___y_5534_ = v___x_5574_;
v___y_5535_ = v___x_5575_;
goto v___jp_5533_;
}
}
v___jp_5346_:
{
uint64_t v___x_5353_; uint32_t v___x_5354_; 
v___x_5353_ = 0ULL;
v___x_5354_ = lp_competition_Submission_R24ExactDotCost_nativeLoop(v___y_5350_, v___y_5349_, v___y_5347_, v___y_5348_, v___y_5352_, v___x_5353_, v___x_5353_, v___x_5353_, v___x_5353_, v___y_5351_);
lean_dec_ref(v___y_5349_);
lean_dec_ref(v___y_5350_);
return v___x_5354_;
}
v___jp_5355_:
{
lean_object* v___x_5363_; lean_object* v___x_5364_; uint8_t v___x_5365_; 
v___x_5363_ = lean_nat_add(v___y_5359_, v___y_5362_);
lean_dec(v___y_5362_);
lean_dec(v___y_5359_);
v___x_5364_ = lean_unsigned_to_nat(128u);
v___x_5365_ = lean_nat_dec_le(v___x_5363_, v___x_5364_);
lean_dec(v___x_5363_);
if (v___x_5365_ == 0)
{
uint32_t v___x_5366_; 
lean_dec(v___y_5361_);
lean_dec_ref(v___y_5360_);
lean_dec_ref(v___y_5358_);
v___x_5366_ = lp_competition_Submission_R24ExactDotCost_referencePrepared(v___y_5357_);
lean_dec_ref(v___y_5357_);
return v___x_5366_;
}
else
{
lean_object* v___x_5367_; uint8_t v___x_5368_; 
lean_dec_ref(v___y_5357_);
v___x_5367_ = lean_unsigned_to_nat(0u);
v___x_5368_ = lean_nat_dec_eq(v___y_5361_, v___x_5367_);
if (v___x_5368_ == 0)
{
v___y_5347_ = v___y_5356_;
v___y_5348_ = v___x_5367_;
v___y_5349_ = v___y_5358_;
v___y_5350_ = v___y_5360_;
v___y_5351_ = v___y_5361_;
v___y_5352_ = v___x_5365_;
goto v___jp_5346_;
}
else
{
uint8_t v___x_5369_; 
v___x_5369_ = 0;
v___y_5347_ = v___y_5356_;
v___y_5348_ = v___x_5367_;
v___y_5349_ = v___y_5358_;
v___y_5350_ = v___y_5360_;
v___y_5351_ = v___y_5361_;
v___y_5352_ = v___x_5369_;
goto v___jp_5346_;
}
}
}
v___jp_5370_:
{
lean_object* v___x_5379_; lean_object* v___x_5380_; 
v___x_5379_ = lean_uint64_to_nat(v___y_5378_);
v___x_5380_ = lean_nat_add(v___x_5379_, v___y_5373_);
lean_dec(v___x_5379_);
v___y_5356_ = v___y_5371_;
v___y_5357_ = v___y_5372_;
v___y_5358_ = v___y_5375_;
v___y_5359_ = v___y_5374_;
v___y_5360_ = v___y_5376_;
v___y_5361_ = v___y_5377_;
v___y_5362_ = v___x_5380_;
goto v___jp_5355_;
}
v___jp_5381_:
{
uint64_t v___x_5391_; uint64_t v___x_5392_; uint64_t v___x_5393_; uint8_t v___x_5394_; 
v___x_5391_ = 1ULL;
v___x_5392_ = lean_uint64_shift_right(v___y_5383_, v___x_5391_);
v___x_5393_ = 0ULL;
v___x_5394_ = lean_uint64_dec_eq(v___x_5392_, v___x_5393_);
if (v___x_5394_ == 0)
{
uint64_t v___x_5395_; 
v___x_5395_ = lean_uint64_add(v___y_5390_, v___x_5391_);
v___y_5371_ = v___y_5382_;
v___y_5372_ = v___y_5384_;
v___y_5373_ = v___y_5385_;
v___y_5374_ = v___y_5387_;
v___y_5375_ = v___y_5386_;
v___y_5376_ = v___y_5388_;
v___y_5377_ = v___y_5389_;
v___y_5378_ = v___x_5395_;
goto v___jp_5370_;
}
else
{
v___y_5371_ = v___y_5382_;
v___y_5372_ = v___y_5384_;
v___y_5373_ = v___y_5385_;
v___y_5374_ = v___y_5387_;
v___y_5375_ = v___y_5386_;
v___y_5376_ = v___y_5388_;
v___y_5377_ = v___y_5389_;
v___y_5378_ = v___y_5390_;
goto v___jp_5370_;
}
}
v___jp_5396_:
{
uint64_t v___x_5408_; uint64_t v___x_5409_; uint8_t v___x_5410_; 
v___x_5408_ = lean_uint64_shift_right(v___y_5406_, v___y_5399_);
v___x_5409_ = 0ULL;
v___x_5410_ = lean_uint64_dec_eq(v___x_5408_, v___x_5409_);
if (v___x_5410_ == 0)
{
uint64_t v___x_5411_; 
v___x_5411_ = lean_uint64_add(v___y_5403_, v___y_5399_);
v___y_5382_ = v___y_5397_;
v___y_5383_ = v___y_5407_;
v___y_5384_ = v___y_5398_;
v___y_5385_ = v___y_5400_;
v___y_5386_ = v___y_5402_;
v___y_5387_ = v___y_5401_;
v___y_5388_ = v___y_5404_;
v___y_5389_ = v___y_5405_;
v___y_5390_ = v___x_5411_;
goto v___jp_5381_;
}
else
{
v___y_5382_ = v___y_5397_;
v___y_5383_ = v___y_5407_;
v___y_5384_ = v___y_5398_;
v___y_5385_ = v___y_5400_;
v___y_5386_ = v___y_5402_;
v___y_5387_ = v___y_5401_;
v___y_5388_ = v___y_5404_;
v___y_5389_ = v___y_5405_;
v___y_5390_ = v___y_5403_;
goto v___jp_5381_;
}
}
v___jp_5412_:
{
uint64_t v___x_5422_; uint64_t v___x_5423_; uint64_t v___x_5424_; uint8_t v___x_5425_; 
v___x_5422_ = 2ULL;
v___x_5423_ = lean_uint64_shift_right(v___y_5420_, v___x_5422_);
v___x_5424_ = 0ULL;
v___x_5425_ = lean_uint64_dec_eq(v___x_5423_, v___x_5424_);
if (v___x_5425_ == 0)
{
v___y_5397_ = v___y_5413_;
v___y_5398_ = v___y_5414_;
v___y_5399_ = v___x_5422_;
v___y_5400_ = v___y_5415_;
v___y_5401_ = v___y_5417_;
v___y_5402_ = v___y_5416_;
v___y_5403_ = v___y_5421_;
v___y_5404_ = v___y_5418_;
v___y_5405_ = v___y_5419_;
v___y_5406_ = v___y_5420_;
v___y_5407_ = v___x_5423_;
goto v___jp_5396_;
}
else
{
v___y_5397_ = v___y_5413_;
v___y_5398_ = v___y_5414_;
v___y_5399_ = v___x_5422_;
v___y_5400_ = v___y_5415_;
v___y_5401_ = v___y_5417_;
v___y_5402_ = v___y_5416_;
v___y_5403_ = v___y_5421_;
v___y_5404_ = v___y_5418_;
v___y_5405_ = v___y_5419_;
v___y_5406_ = v___y_5420_;
v___y_5407_ = v___y_5420_;
goto v___jp_5396_;
}
}
v___jp_5426_:
{
uint64_t v___x_5438_; uint64_t v___x_5439_; uint8_t v___x_5440_; 
v___x_5438_ = lean_uint64_shift_right(v___y_5430_, v___y_5428_);
v___x_5439_ = 0ULL;
v___x_5440_ = lean_uint64_dec_eq(v___x_5438_, v___x_5439_);
if (v___x_5440_ == 0)
{
uint64_t v___x_5441_; 
v___x_5441_ = lean_uint64_add(v___y_5427_, v___y_5428_);
v___y_5413_ = v___y_5429_;
v___y_5414_ = v___y_5431_;
v___y_5415_ = v___y_5432_;
v___y_5416_ = v___y_5434_;
v___y_5417_ = v___y_5433_;
v___y_5418_ = v___y_5435_;
v___y_5419_ = v___y_5436_;
v___y_5420_ = v___y_5437_;
v___y_5421_ = v___x_5441_;
goto v___jp_5412_;
}
else
{
v___y_5413_ = v___y_5429_;
v___y_5414_ = v___y_5431_;
v___y_5415_ = v___y_5432_;
v___y_5416_ = v___y_5434_;
v___y_5417_ = v___y_5433_;
v___y_5418_ = v___y_5435_;
v___y_5419_ = v___y_5436_;
v___y_5420_ = v___y_5437_;
v___y_5421_ = v___y_5427_;
goto v___jp_5412_;
}
}
v___jp_5442_:
{
uint64_t v___x_5452_; uint64_t v___x_5453_; uint64_t v___x_5454_; uint8_t v___x_5455_; 
v___x_5452_ = 4ULL;
v___x_5453_ = lean_uint64_shift_right(v___y_5445_, v___x_5452_);
v___x_5454_ = 0ULL;
v___x_5455_ = lean_uint64_dec_eq(v___x_5453_, v___x_5454_);
if (v___x_5455_ == 0)
{
v___y_5427_ = v___y_5451_;
v___y_5428_ = v___x_5452_;
v___y_5429_ = v___y_5443_;
v___y_5430_ = v___y_5445_;
v___y_5431_ = v___y_5444_;
v___y_5432_ = v___y_5446_;
v___y_5433_ = v___y_5448_;
v___y_5434_ = v___y_5447_;
v___y_5435_ = v___y_5449_;
v___y_5436_ = v___y_5450_;
v___y_5437_ = v___x_5453_;
goto v___jp_5426_;
}
else
{
v___y_5427_ = v___y_5451_;
v___y_5428_ = v___x_5452_;
v___y_5429_ = v___y_5443_;
v___y_5430_ = v___y_5445_;
v___y_5431_ = v___y_5444_;
v___y_5432_ = v___y_5446_;
v___y_5433_ = v___y_5448_;
v___y_5434_ = v___y_5447_;
v___y_5435_ = v___y_5449_;
v___y_5436_ = v___y_5450_;
v___y_5437_ = v___y_5445_;
goto v___jp_5426_;
}
}
v___jp_5456_:
{
uint64_t v___x_5468_; uint64_t v___x_5469_; uint8_t v___x_5470_; 
v___x_5468_ = lean_uint64_shift_right(v___y_5458_, v___y_5461_);
v___x_5469_ = 0ULL;
v___x_5470_ = lean_uint64_dec_eq(v___x_5468_, v___x_5469_);
if (v___x_5470_ == 0)
{
uint64_t v___x_5471_; 
v___x_5471_ = lean_uint64_add(v___y_5465_, v___y_5461_);
v___y_5443_ = v___y_5457_;
v___y_5444_ = v___y_5459_;
v___y_5445_ = v___y_5467_;
v___y_5446_ = v___y_5460_;
v___y_5447_ = v___y_5463_;
v___y_5448_ = v___y_5462_;
v___y_5449_ = v___y_5464_;
v___y_5450_ = v___y_5466_;
v___y_5451_ = v___x_5471_;
goto v___jp_5442_;
}
else
{
v___y_5443_ = v___y_5457_;
v___y_5444_ = v___y_5459_;
v___y_5445_ = v___y_5467_;
v___y_5446_ = v___y_5460_;
v___y_5447_ = v___y_5463_;
v___y_5448_ = v___y_5462_;
v___y_5449_ = v___y_5464_;
v___y_5450_ = v___y_5466_;
v___y_5451_ = v___y_5465_;
goto v___jp_5442_;
}
}
v___jp_5472_:
{
uint64_t v___x_5482_; uint64_t v___x_5483_; uint64_t v___x_5484_; uint8_t v___x_5485_; 
v___x_5482_ = 8ULL;
v___x_5483_ = lean_uint64_shift_right(v___y_5475_, v___x_5482_);
v___x_5484_ = 0ULL;
v___x_5485_ = lean_uint64_dec_eq(v___x_5483_, v___x_5484_);
if (v___x_5485_ == 0)
{
v___y_5457_ = v___y_5473_;
v___y_5458_ = v___y_5475_;
v___y_5459_ = v___y_5474_;
v___y_5460_ = v___y_5476_;
v___y_5461_ = v___x_5482_;
v___y_5462_ = v___y_5478_;
v___y_5463_ = v___y_5477_;
v___y_5464_ = v___y_5479_;
v___y_5465_ = v___y_5481_;
v___y_5466_ = v___y_5480_;
v___y_5467_ = v___x_5483_;
goto v___jp_5456_;
}
else
{
v___y_5457_ = v___y_5473_;
v___y_5458_ = v___y_5475_;
v___y_5459_ = v___y_5474_;
v___y_5460_ = v___y_5476_;
v___y_5461_ = v___x_5482_;
v___y_5462_ = v___y_5478_;
v___y_5463_ = v___y_5477_;
v___y_5464_ = v___y_5479_;
v___y_5465_ = v___y_5481_;
v___y_5466_ = v___y_5480_;
v___y_5467_ = v___y_5475_;
goto v___jp_5456_;
}
}
v___jp_5486_:
{
uint64_t v___x_5498_; uint64_t v___x_5499_; uint8_t v___x_5500_; 
v___x_5498_ = lean_uint64_shift_right(v___y_5495_, v___y_5487_);
v___x_5499_ = 0ULL;
v___x_5500_ = lean_uint64_dec_eq(v___x_5498_, v___x_5499_);
if (v___x_5500_ == 0)
{
uint64_t v___x_5501_; 
v___x_5501_ = lean_uint64_add(v___y_5494_, v___y_5487_);
v___y_5473_ = v___y_5488_;
v___y_5474_ = v___y_5489_;
v___y_5475_ = v___y_5497_;
v___y_5476_ = v___y_5490_;
v___y_5477_ = v___y_5492_;
v___y_5478_ = v___y_5491_;
v___y_5479_ = v___y_5493_;
v___y_5480_ = v___y_5496_;
v___y_5481_ = v___x_5501_;
goto v___jp_5472_;
}
else
{
v___y_5473_ = v___y_5488_;
v___y_5474_ = v___y_5489_;
v___y_5475_ = v___y_5497_;
v___y_5476_ = v___y_5490_;
v___y_5477_ = v___y_5492_;
v___y_5478_ = v___y_5491_;
v___y_5479_ = v___y_5493_;
v___y_5480_ = v___y_5496_;
v___y_5481_ = v___y_5494_;
goto v___jp_5472_;
}
}
v___jp_5502_:
{
uint64_t v___x_5512_; uint64_t v___x_5513_; uint64_t v___x_5514_; uint8_t v___x_5515_; 
v___x_5512_ = 16ULL;
v___x_5513_ = lean_uint64_shift_right(v___y_5509_, v___x_5512_);
v___x_5514_ = 0ULL;
v___x_5515_ = lean_uint64_dec_eq(v___x_5513_, v___x_5514_);
if (v___x_5515_ == 0)
{
v___y_5487_ = v___x_5512_;
v___y_5488_ = v___y_5503_;
v___y_5489_ = v___y_5504_;
v___y_5490_ = v___y_5505_;
v___y_5491_ = v___y_5507_;
v___y_5492_ = v___y_5506_;
v___y_5493_ = v___y_5508_;
v___y_5494_ = v___y_5511_;
v___y_5495_ = v___y_5509_;
v___y_5496_ = v___y_5510_;
v___y_5497_ = v___x_5513_;
goto v___jp_5486_;
}
else
{
v___y_5487_ = v___x_5512_;
v___y_5488_ = v___y_5503_;
v___y_5489_ = v___y_5504_;
v___y_5490_ = v___y_5505_;
v___y_5491_ = v___y_5507_;
v___y_5492_ = v___y_5506_;
v___y_5493_ = v___y_5508_;
v___y_5494_ = v___y_5511_;
v___y_5495_ = v___y_5509_;
v___y_5496_ = v___y_5510_;
v___y_5497_ = v___y_5509_;
goto v___jp_5486_;
}
}
v___jp_5516_:
{
uint64_t v___x_5527_; uint64_t v___x_5528_; uint8_t v___x_5529_; 
v___x_5527_ = lean_uint64_shift_right(v___y_5519_, v___y_5517_);
v___x_5528_ = 0ULL;
v___x_5529_ = lean_uint64_dec_eq(v___x_5527_, v___x_5528_);
if (v___x_5529_ == 0)
{
v___y_5503_ = v___y_5518_;
v___y_5504_ = v___y_5520_;
v___y_5505_ = v___y_5521_;
v___y_5506_ = v___y_5523_;
v___y_5507_ = v___y_5522_;
v___y_5508_ = v___y_5524_;
v___y_5509_ = v___y_5526_;
v___y_5510_ = v___y_5525_;
v___y_5511_ = v___y_5517_;
goto v___jp_5502_;
}
else
{
v___y_5503_ = v___y_5518_;
v___y_5504_ = v___y_5520_;
v___y_5505_ = v___y_5521_;
v___y_5506_ = v___y_5523_;
v___y_5507_ = v___y_5522_;
v___y_5508_ = v___y_5524_;
v___y_5509_ = v___y_5526_;
v___y_5510_ = v___y_5525_;
v___y_5511_ = v___x_5528_;
goto v___jp_5502_;
}
}
v___jp_5533_:
{
lean_object* v_raw_5536_; lean_object* v_data_5537_; uint8_t v_normal_5538_; lean_object* v_raw_5539_; lean_object* v_data_5540_; uint8_t v_normal_5541_; lean_object* v___x_5542_; lean_object* v___x_5543_; uint8_t v___x_5544_; lean_object* v___x_5545_; 
v_raw_5536_ = lean_ctor_get(v___x_5530_, 0);
lean_inc_ref(v_raw_5536_);
v_data_5537_ = lean_ctor_get(v___x_5530_, 1);
lean_inc_ref(v_data_5537_);
v_normal_5538_ = lean_ctor_get_uint8(v___x_5530_, sizeof(void*)*2 + 8);
v_raw_5539_ = lean_ctor_get(v___x_5532_, 0);
lean_inc_ref(v_raw_5539_);
v_data_5540_ = lean_ctor_get(v___x_5532_, 1);
lean_inc_ref(v_data_5540_);
v_normal_5541_ = lean_ctor_get_uint8(v___x_5532_, sizeof(void*)*2 + 8);
v___x_5542_ = lean_array_get_size(v_raw_5536_);
lean_dec_ref(v_raw_5536_);
v___x_5543_ = lean_array_get_size(v_raw_5539_);
lean_dec_ref(v_raw_5539_);
v___x_5544_ = lean_nat_dec_eq(v___x_5542_, v___x_5543_);
v___x_5545_ = lean_alloc_ctor(0, 2, 9);
lean_ctor_set(v___x_5545_, 0, v___x_5530_);
lean_ctor_set(v___x_5545_, 1, v___x_5532_);
lean_ctor_set_uint32(v___x_5545_, sizeof(void*)*2, v___y_5534_);
lean_ctor_set_uint32(v___x_5545_, sizeof(void*)*2 + 4, v___y_5535_);
lean_ctor_set_uint8(v___x_5545_, sizeof(void*)*2 + 8, v___x_5544_);
if (v___x_5544_ == 0)
{
uint32_t v___x_5546_; 
lean_dec_ref(v_data_5540_);
lean_dec_ref(v_data_5537_);
v___x_5546_ = lp_competition_Submission_R24ExactDotCost_referencePrepared(v___x_5545_);
lean_dec_ref_known(v___x_5545_, 2);
return v___x_5546_;
}
else
{
if (v_normal_5538_ == 0)
{
uint32_t v___x_5547_; 
lean_dec_ref(v_data_5540_);
lean_dec_ref(v_data_5537_);
v___x_5547_ = lp_competition_Submission_R24ExactDotCost_referencePrepared(v___x_5545_);
lean_dec_ref_known(v___x_5545_, 2);
return v___x_5547_;
}
else
{
if (v_normal_5541_ == 0)
{
uint32_t v___x_5548_; 
lean_dec_ref(v_data_5540_);
lean_dec_ref(v_data_5537_);
v___x_5548_ = lp_competition_Submission_R24ExactDotCost_referencePrepared(v___x_5545_);
lean_dec_ref_known(v___x_5545_, 2);
return v___x_5548_;
}
else
{
lean_object* v___x_5549_; lean_object* v___x_5550_; uint8_t v___x_5551_; 
v___x_5549_ = lean_array_get_size(v_data_5537_);
v___x_5550_ = lean_unsigned_to_nat(1048576u);
v___x_5551_ = lean_nat_dec_le(v___x_5549_, v___x_5550_);
if (v___x_5551_ == 0)
{
uint32_t v___x_5552_; 
lean_dec_ref(v_data_5540_);
lean_dec_ref(v_data_5537_);
v___x_5552_ = lp_competition_Submission_R24ExactDotCost_referencePrepared(v___x_5545_);
lean_dec_ref_known(v___x_5545_, 2);
return v___x_5552_;
}
else
{
lean_object* v___x_5553_; lean_object* v___x_5554_; lean_object* v___x_5555_; lean_object* v___x_5556_; lean_object* v___x_5557_; lean_object* v___x_5558_; uint8_t v___x_5559_; 
v___x_5553_ = lean_unsigned_to_nat(48u);
v___x_5554_ = lean_uint32_to_nat(v___y_5535_);
v___x_5555_ = lean_uint32_to_nat(v___y_5534_);
v___x_5556_ = lean_nat_sub(v___x_5554_, v___x_5555_);
lean_dec(v___x_5555_);
lean_dec(v___x_5554_);
v___x_5557_ = lean_nat_add(v___x_5553_, v___x_5556_);
lean_dec(v___x_5556_);
v___x_5558_ = lean_unsigned_to_nat(1u);
v___x_5559_ = lean_nat_dec_le(v___x_5549_, v___x_5558_);
if (v___x_5559_ == 0)
{
lean_object* v___x_5560_; uint64_t v___x_5561_; uint64_t v___x_5562_; uint64_t v___x_5563_; uint64_t v___x_5564_; uint8_t v___x_5565_; 
v___x_5560_ = lean_nat_sub(v___x_5549_, v___x_5558_);
v___x_5561_ = lean_uint64_of_nat(v___x_5560_);
lean_dec(v___x_5560_);
v___x_5562_ = 32ULL;
v___x_5563_ = lean_uint64_shift_right(v___x_5561_, v___x_5562_);
v___x_5564_ = 0ULL;
v___x_5565_ = lean_uint64_dec_eq(v___x_5563_, v___x_5564_);
if (v___x_5565_ == 0)
{
v___y_5517_ = v___x_5562_;
v___y_5518_ = v___y_5534_;
v___y_5519_ = v___x_5561_;
v___y_5520_ = v___x_5545_;
v___y_5521_ = v___x_5558_;
v___y_5522_ = v___x_5557_;
v___y_5523_ = v_data_5540_;
v___y_5524_ = v_data_5537_;
v___y_5525_ = v___x_5549_;
v___y_5526_ = v___x_5563_;
goto v___jp_5516_;
}
else
{
v___y_5517_ = v___x_5562_;
v___y_5518_ = v___y_5534_;
v___y_5519_ = v___x_5561_;
v___y_5520_ = v___x_5545_;
v___y_5521_ = v___x_5558_;
v___y_5522_ = v___x_5557_;
v___y_5523_ = v_data_5540_;
v___y_5524_ = v_data_5537_;
v___y_5525_ = v___x_5549_;
v___y_5526_ = v___x_5561_;
goto v___jp_5516_;
}
}
else
{
lean_object* v___x_5566_; 
v___x_5566_ = lean_unsigned_to_nat(0u);
v___y_5356_ = v___y_5534_;
v___y_5357_ = v___x_5545_;
v___y_5358_ = v_data_5540_;
v___y_5359_ = v___x_5557_;
v___y_5360_ = v_data_5537_;
v___y_5361_ = v___x_5549_;
v___y_5362_ = v___x_5566_;
goto v___jp_5355_;
}
}
}
}
}
}
v___jp_5567_:
{
uint32_t v___x_5568_; 
v___x_5568_ = 0;
v___y_5534_ = v___x_5568_;
v___y_5535_ = v___x_5568_;
goto v___jp_5533_;
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_R24ExactDotCost_full___boxed(lean_object* v_rawA_5576_, lean_object* v_rawB_5577_){
_start:
{
uint32_t v_res_5578_; lean_object* v_r_5579_; 
v_res_5578_ = lp_competition_Submission_R24ExactDotCost_full(v_rawA_5576_, v_rawB_5577_);
v_r_5579_ = lean_box_uint32(v_res_5578_);
return v_r_5579_;
}
}
LEAN_EXPORT uint32_t lp_competition_Submission_R24ExactDotCost_prepared2(lean_object* v_left_5580_, lean_object* v_right_5581_){
_start:
{
lean_object* v___y_5583_; lean_object* v___y_5584_; lean_object* v___y_5585_; uint32_t v___y_5586_; lean_object* v___y_5587_; uint8_t v___y_5588_; lean_object* v___y_5592_; lean_object* v___y_5593_; lean_object* v___y_5594_; uint32_t v___y_5595_; lean_object* v___y_5596_; lean_object* v___y_5597_; lean_object* v___y_5598_; lean_object* v___y_5607_; lean_object* v___y_5608_; lean_object* v___y_5609_; lean_object* v___y_5610_; uint32_t v___y_5611_; lean_object* v___y_5612_; lean_object* v___y_5613_; uint64_t v___y_5614_; lean_object* v___y_5618_; lean_object* v___y_5619_; lean_object* v___y_5620_; lean_object* v___y_5621_; uint32_t v___y_5622_; lean_object* v___y_5623_; uint64_t v___y_5624_; lean_object* v___y_5625_; uint64_t v___y_5626_; lean_object* v___y_5633_; lean_object* v___y_5634_; uint64_t v___y_5635_; lean_object* v___y_5636_; lean_object* v___y_5637_; uint64_t v___y_5638_; uint32_t v___y_5639_; lean_object* v___y_5640_; lean_object* v___y_5641_; uint64_t v___y_5642_; uint64_t v___y_5643_; lean_object* v___y_5649_; lean_object* v___y_5650_; uint64_t v___y_5651_; lean_object* v___y_5652_; lean_object* v___y_5653_; uint32_t v___y_5654_; lean_object* v___y_5655_; lean_object* v___y_5656_; uint64_t v___y_5657_; lean_object* v___y_5663_; uint64_t v___y_5664_; lean_object* v___y_5665_; lean_object* v___y_5666_; lean_object* v___y_5667_; uint32_t v___y_5668_; uint64_t v___y_5669_; lean_object* v___y_5670_; lean_object* v___y_5671_; uint64_t v___y_5672_; uint64_t v___y_5673_; lean_object* v___y_5679_; lean_object* v___y_5680_; lean_object* v___y_5681_; lean_object* v___y_5682_; uint32_t v___y_5683_; lean_object* v___y_5684_; lean_object* v___y_5685_; uint64_t v___y_5686_; uint64_t v___y_5687_; lean_object* v___y_5693_; uint64_t v___y_5694_; lean_object* v___y_5695_; lean_object* v___y_5696_; uint64_t v___y_5697_; lean_object* v___y_5698_; uint32_t v___y_5699_; lean_object* v___y_5700_; uint64_t v___y_5701_; lean_object* v___y_5702_; uint64_t v___y_5703_; lean_object* v___y_5709_; uint64_t v___y_5710_; lean_object* v___y_5711_; lean_object* v___y_5712_; lean_object* v___y_5713_; uint32_t v___y_5714_; lean_object* v___y_5715_; lean_object* v___y_5716_; uint64_t v___y_5717_; lean_object* v___y_5723_; lean_object* v___y_5724_; lean_object* v___y_5725_; lean_object* v___y_5726_; uint32_t v___y_5727_; lean_object* v___y_5728_; uint64_t v___y_5729_; uint64_t v___y_5730_; uint64_t v___y_5731_; lean_object* v___y_5732_; uint64_t v___y_5733_; lean_object* v___y_5739_; lean_object* v___y_5740_; lean_object* v___y_5741_; lean_object* v___y_5742_; uint32_t v___y_5743_; lean_object* v___y_5744_; uint64_t v___y_5745_; lean_object* v___y_5746_; uint64_t v___y_5747_; lean_object* v___y_5753_; lean_object* v___y_5754_; uint64_t v___y_5755_; lean_object* v___y_5756_; uint64_t v___y_5757_; lean_object* v___y_5758_; uint32_t v___y_5759_; lean_object* v___y_5760_; lean_object* v___y_5761_; uint64_t v___y_5762_; lean_object* v_raw_5766_; lean_object* v_data_5767_; uint32_t v_minIdx_5768_; uint32_t v_maxIdx_5769_; uint8_t v_normal_5770_; uint8_t v_hasNonzero_5771_; uint32_t v___y_5773_; uint32_t v___y_5774_; 
v_raw_5766_ = lean_ctor_get(v_left_5580_, 0);
v_data_5767_ = lean_ctor_get(v_left_5580_, 1);
lean_inc_ref(v_data_5767_);
v_minIdx_5768_ = lean_ctor_get_uint32(v_left_5580_, sizeof(void*)*2);
v_maxIdx_5769_ = lean_ctor_get_uint32(v_left_5580_, sizeof(void*)*2 + 4);
v_normal_5770_ = lean_ctor_get_uint8(v_left_5580_, sizeof(void*)*2 + 8);
v_hasNonzero_5771_ = lean_ctor_get_uint8(v_left_5580_, sizeof(void*)*2 + 10);
if (v_hasNonzero_5771_ == 0)
{
goto v___jp_5803_;
}
else
{
uint8_t v_hasNonzero_5805_; 
v_hasNonzero_5805_ = lean_ctor_get_uint8(v_right_5581_, sizeof(void*)*2 + 10);
if (v_hasNonzero_5805_ == 0)
{
goto v___jp_5803_;
}
else
{
uint32_t v_minIdx_5806_; uint32_t v_maxIdx_5807_; uint32_t v___x_5808_; uint32_t v___x_5809_; 
v_minIdx_5806_ = lean_ctor_get_uint32(v_right_5581_, sizeof(void*)*2);
v_maxIdx_5807_ = lean_ctor_get_uint32(v_right_5581_, sizeof(void*)*2 + 4);
v___x_5808_ = lean_uint32_add(v_minIdx_5768_, v_minIdx_5806_);
v___x_5809_ = lean_uint32_add(v_maxIdx_5769_, v_maxIdx_5807_);
v___y_5773_ = v___x_5808_;
v___y_5774_ = v___x_5809_;
goto v___jp_5772_;
}
}
v___jp_5582_:
{
uint64_t v___x_5589_; uint32_t v___x_5590_; 
v___x_5589_ = 0ULL;
v___x_5590_ = lp_competition_Submission_R24ExactDotCost_nativeLoop(v___y_5585_, v___y_5583_, v___y_5586_, v___y_5587_, v___y_5588_, v___x_5589_, v___x_5589_, v___x_5589_, v___x_5589_, v___y_5584_);
lean_dec_ref(v___y_5583_);
lean_dec_ref(v___y_5585_);
return v___x_5590_;
}
v___jp_5591_:
{
lean_object* v___x_5599_; lean_object* v___x_5600_; uint8_t v___x_5601_; 
v___x_5599_ = lean_nat_add(v___y_5596_, v___y_5598_);
lean_dec(v___y_5598_);
lean_dec(v___y_5596_);
v___x_5600_ = lean_unsigned_to_nat(128u);
v___x_5601_ = lean_nat_dec_le(v___x_5599_, v___x_5600_);
lean_dec(v___x_5599_);
if (v___x_5601_ == 0)
{
uint32_t v___x_5602_; 
lean_dec_ref(v___y_5594_);
lean_dec(v___y_5593_);
lean_dec_ref(v___y_5592_);
v___x_5602_ = lp_competition_Submission_R24ExactDotCost_referencePrepared(v___y_5597_);
lean_dec_ref(v___y_5597_);
return v___x_5602_;
}
else
{
lean_object* v___x_5603_; uint8_t v___x_5604_; 
lean_dec_ref(v___y_5597_);
v___x_5603_ = lean_unsigned_to_nat(0u);
v___x_5604_ = lean_nat_dec_eq(v___y_5593_, v___x_5603_);
if (v___x_5604_ == 0)
{
v___y_5583_ = v___y_5592_;
v___y_5584_ = v___y_5593_;
v___y_5585_ = v___y_5594_;
v___y_5586_ = v___y_5595_;
v___y_5587_ = v___x_5603_;
v___y_5588_ = v___x_5601_;
goto v___jp_5582_;
}
else
{
uint8_t v___x_5605_; 
v___x_5605_ = 0;
v___y_5583_ = v___y_5592_;
v___y_5584_ = v___y_5593_;
v___y_5585_ = v___y_5594_;
v___y_5586_ = v___y_5595_;
v___y_5587_ = v___x_5603_;
v___y_5588_ = v___x_5605_;
goto v___jp_5582_;
}
}
}
v___jp_5606_:
{
lean_object* v___x_5615_; lean_object* v___x_5616_; 
v___x_5615_ = lean_uint64_to_nat(v___y_5614_);
v___x_5616_ = lean_nat_add(v___x_5615_, v___y_5609_);
lean_dec(v___x_5615_);
v___y_5592_ = v___y_5607_;
v___y_5593_ = v___y_5608_;
v___y_5594_ = v___y_5610_;
v___y_5595_ = v___y_5611_;
v___y_5596_ = v___y_5612_;
v___y_5597_ = v___y_5613_;
v___y_5598_ = v___x_5616_;
goto v___jp_5591_;
}
v___jp_5617_:
{
uint64_t v___x_5627_; uint64_t v___x_5628_; uint64_t v___x_5629_; uint8_t v___x_5630_; 
v___x_5627_ = 1ULL;
v___x_5628_ = lean_uint64_shift_right(v___y_5624_, v___x_5627_);
v___x_5629_ = 0ULL;
v___x_5630_ = lean_uint64_dec_eq(v___x_5628_, v___x_5629_);
if (v___x_5630_ == 0)
{
uint64_t v___x_5631_; 
v___x_5631_ = lean_uint64_add(v___y_5626_, v___x_5627_);
v___y_5607_ = v___y_5618_;
v___y_5608_ = v___y_5619_;
v___y_5609_ = v___y_5620_;
v___y_5610_ = v___y_5621_;
v___y_5611_ = v___y_5622_;
v___y_5612_ = v___y_5623_;
v___y_5613_ = v___y_5625_;
v___y_5614_ = v___x_5631_;
goto v___jp_5606_;
}
else
{
v___y_5607_ = v___y_5618_;
v___y_5608_ = v___y_5619_;
v___y_5609_ = v___y_5620_;
v___y_5610_ = v___y_5621_;
v___y_5611_ = v___y_5622_;
v___y_5612_ = v___y_5623_;
v___y_5613_ = v___y_5625_;
v___y_5614_ = v___y_5626_;
goto v___jp_5606_;
}
}
v___jp_5632_:
{
uint64_t v___x_5644_; uint64_t v___x_5645_; uint8_t v___x_5646_; 
v___x_5644_ = lean_uint64_shift_right(v___y_5635_, v___y_5642_);
v___x_5645_ = 0ULL;
v___x_5646_ = lean_uint64_dec_eq(v___x_5644_, v___x_5645_);
if (v___x_5646_ == 0)
{
uint64_t v___x_5647_; 
v___x_5647_ = lean_uint64_add(v___y_5638_, v___y_5642_);
v___y_5618_ = v___y_5633_;
v___y_5619_ = v___y_5634_;
v___y_5620_ = v___y_5636_;
v___y_5621_ = v___y_5637_;
v___y_5622_ = v___y_5639_;
v___y_5623_ = v___y_5640_;
v___y_5624_ = v___y_5643_;
v___y_5625_ = v___y_5641_;
v___y_5626_ = v___x_5647_;
goto v___jp_5617_;
}
else
{
v___y_5618_ = v___y_5633_;
v___y_5619_ = v___y_5634_;
v___y_5620_ = v___y_5636_;
v___y_5621_ = v___y_5637_;
v___y_5622_ = v___y_5639_;
v___y_5623_ = v___y_5640_;
v___y_5624_ = v___y_5643_;
v___y_5625_ = v___y_5641_;
v___y_5626_ = v___y_5638_;
goto v___jp_5617_;
}
}
v___jp_5648_:
{
uint64_t v___x_5658_; uint64_t v___x_5659_; uint64_t v___x_5660_; uint8_t v___x_5661_; 
v___x_5658_ = 2ULL;
v___x_5659_ = lean_uint64_shift_right(v___y_5651_, v___x_5658_);
v___x_5660_ = 0ULL;
v___x_5661_ = lean_uint64_dec_eq(v___x_5659_, v___x_5660_);
if (v___x_5661_ == 0)
{
v___y_5633_ = v___y_5649_;
v___y_5634_ = v___y_5650_;
v___y_5635_ = v___y_5651_;
v___y_5636_ = v___y_5652_;
v___y_5637_ = v___y_5653_;
v___y_5638_ = v___y_5657_;
v___y_5639_ = v___y_5654_;
v___y_5640_ = v___y_5655_;
v___y_5641_ = v___y_5656_;
v___y_5642_ = v___x_5658_;
v___y_5643_ = v___x_5659_;
goto v___jp_5632_;
}
else
{
v___y_5633_ = v___y_5649_;
v___y_5634_ = v___y_5650_;
v___y_5635_ = v___y_5651_;
v___y_5636_ = v___y_5652_;
v___y_5637_ = v___y_5653_;
v___y_5638_ = v___y_5657_;
v___y_5639_ = v___y_5654_;
v___y_5640_ = v___y_5655_;
v___y_5641_ = v___y_5656_;
v___y_5642_ = v___x_5658_;
v___y_5643_ = v___y_5651_;
goto v___jp_5632_;
}
}
v___jp_5662_:
{
uint64_t v___x_5674_; uint64_t v___x_5675_; uint8_t v___x_5676_; 
v___x_5674_ = lean_uint64_shift_right(v___y_5672_, v___y_5664_);
v___x_5675_ = 0ULL;
v___x_5676_ = lean_uint64_dec_eq(v___x_5674_, v___x_5675_);
if (v___x_5676_ == 0)
{
uint64_t v___x_5677_; 
v___x_5677_ = lean_uint64_add(v___y_5669_, v___y_5664_);
v___y_5649_ = v___y_5663_;
v___y_5650_ = v___y_5665_;
v___y_5651_ = v___y_5673_;
v___y_5652_ = v___y_5666_;
v___y_5653_ = v___y_5667_;
v___y_5654_ = v___y_5668_;
v___y_5655_ = v___y_5670_;
v___y_5656_ = v___y_5671_;
v___y_5657_ = v___x_5677_;
goto v___jp_5648_;
}
else
{
v___y_5649_ = v___y_5663_;
v___y_5650_ = v___y_5665_;
v___y_5651_ = v___y_5673_;
v___y_5652_ = v___y_5666_;
v___y_5653_ = v___y_5667_;
v___y_5654_ = v___y_5668_;
v___y_5655_ = v___y_5670_;
v___y_5656_ = v___y_5671_;
v___y_5657_ = v___y_5669_;
goto v___jp_5648_;
}
}
v___jp_5678_:
{
uint64_t v___x_5688_; uint64_t v___x_5689_; uint64_t v___x_5690_; uint8_t v___x_5691_; 
v___x_5688_ = 4ULL;
v___x_5689_ = lean_uint64_shift_right(v___y_5686_, v___x_5688_);
v___x_5690_ = 0ULL;
v___x_5691_ = lean_uint64_dec_eq(v___x_5689_, v___x_5690_);
if (v___x_5691_ == 0)
{
v___y_5663_ = v___y_5679_;
v___y_5664_ = v___x_5688_;
v___y_5665_ = v___y_5680_;
v___y_5666_ = v___y_5681_;
v___y_5667_ = v___y_5682_;
v___y_5668_ = v___y_5683_;
v___y_5669_ = v___y_5687_;
v___y_5670_ = v___y_5684_;
v___y_5671_ = v___y_5685_;
v___y_5672_ = v___y_5686_;
v___y_5673_ = v___x_5689_;
goto v___jp_5662_;
}
else
{
v___y_5663_ = v___y_5679_;
v___y_5664_ = v___x_5688_;
v___y_5665_ = v___y_5680_;
v___y_5666_ = v___y_5681_;
v___y_5667_ = v___y_5682_;
v___y_5668_ = v___y_5683_;
v___y_5669_ = v___y_5687_;
v___y_5670_ = v___y_5684_;
v___y_5671_ = v___y_5685_;
v___y_5672_ = v___y_5686_;
v___y_5673_ = v___y_5686_;
goto v___jp_5662_;
}
}
v___jp_5692_:
{
uint64_t v___x_5704_; uint64_t v___x_5705_; uint8_t v___x_5706_; 
v___x_5704_ = lean_uint64_shift_right(v___y_5694_, v___y_5701_);
v___x_5705_ = 0ULL;
v___x_5706_ = lean_uint64_dec_eq(v___x_5704_, v___x_5705_);
if (v___x_5706_ == 0)
{
uint64_t v___x_5707_; 
v___x_5707_ = lean_uint64_add(v___y_5697_, v___y_5701_);
v___y_5679_ = v___y_5693_;
v___y_5680_ = v___y_5695_;
v___y_5681_ = v___y_5696_;
v___y_5682_ = v___y_5698_;
v___y_5683_ = v___y_5699_;
v___y_5684_ = v___y_5700_;
v___y_5685_ = v___y_5702_;
v___y_5686_ = v___y_5703_;
v___y_5687_ = v___x_5707_;
goto v___jp_5678_;
}
else
{
v___y_5679_ = v___y_5693_;
v___y_5680_ = v___y_5695_;
v___y_5681_ = v___y_5696_;
v___y_5682_ = v___y_5698_;
v___y_5683_ = v___y_5699_;
v___y_5684_ = v___y_5700_;
v___y_5685_ = v___y_5702_;
v___y_5686_ = v___y_5703_;
v___y_5687_ = v___y_5697_;
goto v___jp_5678_;
}
}
v___jp_5708_:
{
uint64_t v___x_5718_; uint64_t v___x_5719_; uint64_t v___x_5720_; uint8_t v___x_5721_; 
v___x_5718_ = 8ULL;
v___x_5719_ = lean_uint64_shift_right(v___y_5710_, v___x_5718_);
v___x_5720_ = 0ULL;
v___x_5721_ = lean_uint64_dec_eq(v___x_5719_, v___x_5720_);
if (v___x_5721_ == 0)
{
v___y_5693_ = v___y_5709_;
v___y_5694_ = v___y_5710_;
v___y_5695_ = v___y_5711_;
v___y_5696_ = v___y_5712_;
v___y_5697_ = v___y_5717_;
v___y_5698_ = v___y_5713_;
v___y_5699_ = v___y_5714_;
v___y_5700_ = v___y_5715_;
v___y_5701_ = v___x_5718_;
v___y_5702_ = v___y_5716_;
v___y_5703_ = v___x_5719_;
goto v___jp_5692_;
}
else
{
v___y_5693_ = v___y_5709_;
v___y_5694_ = v___y_5710_;
v___y_5695_ = v___y_5711_;
v___y_5696_ = v___y_5712_;
v___y_5697_ = v___y_5717_;
v___y_5698_ = v___y_5713_;
v___y_5699_ = v___y_5714_;
v___y_5700_ = v___y_5715_;
v___y_5701_ = v___x_5718_;
v___y_5702_ = v___y_5716_;
v___y_5703_ = v___y_5710_;
goto v___jp_5692_;
}
}
v___jp_5722_:
{
uint64_t v___x_5734_; uint64_t v___x_5735_; uint8_t v___x_5736_; 
v___x_5734_ = lean_uint64_shift_right(v___y_5730_, v___y_5731_);
v___x_5735_ = 0ULL;
v___x_5736_ = lean_uint64_dec_eq(v___x_5734_, v___x_5735_);
if (v___x_5736_ == 0)
{
uint64_t v___x_5737_; 
v___x_5737_ = lean_uint64_add(v___y_5729_, v___y_5731_);
v___y_5709_ = v___y_5723_;
v___y_5710_ = v___y_5733_;
v___y_5711_ = v___y_5724_;
v___y_5712_ = v___y_5725_;
v___y_5713_ = v___y_5726_;
v___y_5714_ = v___y_5727_;
v___y_5715_ = v___y_5728_;
v___y_5716_ = v___y_5732_;
v___y_5717_ = v___x_5737_;
goto v___jp_5708_;
}
else
{
v___y_5709_ = v___y_5723_;
v___y_5710_ = v___y_5733_;
v___y_5711_ = v___y_5724_;
v___y_5712_ = v___y_5725_;
v___y_5713_ = v___y_5726_;
v___y_5714_ = v___y_5727_;
v___y_5715_ = v___y_5728_;
v___y_5716_ = v___y_5732_;
v___y_5717_ = v___y_5729_;
goto v___jp_5708_;
}
}
v___jp_5738_:
{
uint64_t v___x_5748_; uint64_t v___x_5749_; uint64_t v___x_5750_; uint8_t v___x_5751_; 
v___x_5748_ = 16ULL;
v___x_5749_ = lean_uint64_shift_right(v___y_5745_, v___x_5748_);
v___x_5750_ = 0ULL;
v___x_5751_ = lean_uint64_dec_eq(v___x_5749_, v___x_5750_);
if (v___x_5751_ == 0)
{
v___y_5723_ = v___y_5739_;
v___y_5724_ = v___y_5740_;
v___y_5725_ = v___y_5741_;
v___y_5726_ = v___y_5742_;
v___y_5727_ = v___y_5743_;
v___y_5728_ = v___y_5744_;
v___y_5729_ = v___y_5747_;
v___y_5730_ = v___y_5745_;
v___y_5731_ = v___x_5748_;
v___y_5732_ = v___y_5746_;
v___y_5733_ = v___x_5749_;
goto v___jp_5722_;
}
else
{
v___y_5723_ = v___y_5739_;
v___y_5724_ = v___y_5740_;
v___y_5725_ = v___y_5741_;
v___y_5726_ = v___y_5742_;
v___y_5727_ = v___y_5743_;
v___y_5728_ = v___y_5744_;
v___y_5729_ = v___y_5747_;
v___y_5730_ = v___y_5745_;
v___y_5731_ = v___x_5748_;
v___y_5732_ = v___y_5746_;
v___y_5733_ = v___y_5745_;
goto v___jp_5722_;
}
}
v___jp_5752_:
{
uint64_t v___x_5763_; uint64_t v___x_5764_; uint8_t v___x_5765_; 
v___x_5763_ = lean_uint64_shift_right(v___y_5755_, v___y_5757_);
v___x_5764_ = 0ULL;
v___x_5765_ = lean_uint64_dec_eq(v___x_5763_, v___x_5764_);
if (v___x_5765_ == 0)
{
v___y_5739_ = v___y_5753_;
v___y_5740_ = v___y_5754_;
v___y_5741_ = v___y_5756_;
v___y_5742_ = v___y_5758_;
v___y_5743_ = v___y_5759_;
v___y_5744_ = v___y_5760_;
v___y_5745_ = v___y_5762_;
v___y_5746_ = v___y_5761_;
v___y_5747_ = v___y_5757_;
goto v___jp_5738_;
}
else
{
v___y_5739_ = v___y_5753_;
v___y_5740_ = v___y_5754_;
v___y_5741_ = v___y_5756_;
v___y_5742_ = v___y_5758_;
v___y_5743_ = v___y_5759_;
v___y_5744_ = v___y_5760_;
v___y_5745_ = v___y_5762_;
v___y_5746_ = v___y_5761_;
v___y_5747_ = v___x_5764_;
goto v___jp_5738_;
}
}
v___jp_5772_:
{
lean_object* v_raw_5775_; lean_object* v_data_5776_; uint8_t v_normal_5777_; lean_object* v___x_5778_; lean_object* v___x_5779_; uint8_t v___x_5780_; lean_object* v___x_5781_; 
v_raw_5775_ = lean_ctor_get(v_right_5581_, 0);
v_data_5776_ = lean_ctor_get(v_right_5581_, 1);
lean_inc_ref(v_data_5776_);
v_normal_5777_ = lean_ctor_get_uint8(v_right_5581_, sizeof(void*)*2 + 8);
v___x_5778_ = lean_array_get_size(v_raw_5766_);
v___x_5779_ = lean_array_get_size(v_raw_5775_);
v___x_5780_ = lean_nat_dec_eq(v___x_5778_, v___x_5779_);
v___x_5781_ = lean_alloc_ctor(0, 2, 9);
lean_ctor_set(v___x_5781_, 0, v_left_5580_);
lean_ctor_set(v___x_5781_, 1, v_right_5581_);
lean_ctor_set_uint32(v___x_5781_, sizeof(void*)*2, v___y_5773_);
lean_ctor_set_uint32(v___x_5781_, sizeof(void*)*2 + 4, v___y_5774_);
lean_ctor_set_uint8(v___x_5781_, sizeof(void*)*2 + 8, v___x_5780_);
if (v___x_5780_ == 0)
{
uint32_t v___x_5782_; 
lean_dec_ref(v_data_5776_);
lean_dec_ref(v_data_5767_);
v___x_5782_ = lp_competition_Submission_R24ExactDotCost_referencePrepared(v___x_5781_);
lean_dec_ref_known(v___x_5781_, 2);
return v___x_5782_;
}
else
{
if (v_normal_5770_ == 0)
{
uint32_t v___x_5783_; 
lean_dec_ref(v_data_5776_);
lean_dec_ref(v_data_5767_);
v___x_5783_ = lp_competition_Submission_R24ExactDotCost_referencePrepared(v___x_5781_);
lean_dec_ref_known(v___x_5781_, 2);
return v___x_5783_;
}
else
{
if (v_normal_5777_ == 0)
{
uint32_t v___x_5784_; 
lean_dec_ref(v_data_5776_);
lean_dec_ref(v_data_5767_);
v___x_5784_ = lp_competition_Submission_R24ExactDotCost_referencePrepared(v___x_5781_);
lean_dec_ref_known(v___x_5781_, 2);
return v___x_5784_;
}
else
{
lean_object* v___x_5785_; lean_object* v___x_5786_; uint8_t v___x_5787_; 
v___x_5785_ = lean_array_get_size(v_data_5767_);
v___x_5786_ = lean_unsigned_to_nat(1048576u);
v___x_5787_ = lean_nat_dec_le(v___x_5785_, v___x_5786_);
if (v___x_5787_ == 0)
{
uint32_t v___x_5788_; 
lean_dec_ref(v_data_5776_);
lean_dec_ref(v_data_5767_);
v___x_5788_ = lp_competition_Submission_R24ExactDotCost_referencePrepared(v___x_5781_);
lean_dec_ref_known(v___x_5781_, 2);
return v___x_5788_;
}
else
{
lean_object* v___x_5789_; lean_object* v___x_5790_; lean_object* v___x_5791_; lean_object* v___x_5792_; lean_object* v___x_5793_; lean_object* v___x_5794_; uint8_t v___x_5795_; 
v___x_5789_ = lean_unsigned_to_nat(48u);
v___x_5790_ = lean_uint32_to_nat(v___y_5774_);
v___x_5791_ = lean_uint32_to_nat(v___y_5773_);
v___x_5792_ = lean_nat_sub(v___x_5790_, v___x_5791_);
lean_dec(v___x_5791_);
lean_dec(v___x_5790_);
v___x_5793_ = lean_nat_add(v___x_5789_, v___x_5792_);
lean_dec(v___x_5792_);
v___x_5794_ = lean_unsigned_to_nat(1u);
v___x_5795_ = lean_nat_dec_le(v___x_5785_, v___x_5794_);
if (v___x_5795_ == 0)
{
lean_object* v___x_5796_; uint64_t v___x_5797_; uint64_t v___x_5798_; uint64_t v___x_5799_; uint64_t v___x_5800_; uint8_t v___x_5801_; 
v___x_5796_ = lean_nat_sub(v___x_5785_, v___x_5794_);
v___x_5797_ = lean_uint64_of_nat(v___x_5796_);
lean_dec(v___x_5796_);
v___x_5798_ = 32ULL;
v___x_5799_ = lean_uint64_shift_right(v___x_5797_, v___x_5798_);
v___x_5800_ = 0ULL;
v___x_5801_ = lean_uint64_dec_eq(v___x_5799_, v___x_5800_);
if (v___x_5801_ == 0)
{
v___y_5753_ = v_data_5776_;
v___y_5754_ = v___x_5785_;
v___y_5755_ = v___x_5797_;
v___y_5756_ = v___x_5794_;
v___y_5757_ = v___x_5798_;
v___y_5758_ = v_data_5767_;
v___y_5759_ = v___y_5773_;
v___y_5760_ = v___x_5793_;
v___y_5761_ = v___x_5781_;
v___y_5762_ = v___x_5799_;
goto v___jp_5752_;
}
else
{
v___y_5753_ = v_data_5776_;
v___y_5754_ = v___x_5785_;
v___y_5755_ = v___x_5797_;
v___y_5756_ = v___x_5794_;
v___y_5757_ = v___x_5798_;
v___y_5758_ = v_data_5767_;
v___y_5759_ = v___y_5773_;
v___y_5760_ = v___x_5793_;
v___y_5761_ = v___x_5781_;
v___y_5762_ = v___x_5797_;
goto v___jp_5752_;
}
}
else
{
lean_object* v___x_5802_; 
v___x_5802_ = lean_unsigned_to_nat(0u);
v___y_5592_ = v_data_5776_;
v___y_5593_ = v___x_5785_;
v___y_5594_ = v_data_5767_;
v___y_5595_ = v___y_5773_;
v___y_5596_ = v___x_5793_;
v___y_5597_ = v___x_5781_;
v___y_5598_ = v___x_5802_;
goto v___jp_5591_;
}
}
}
}
}
}
v___jp_5803_:
{
uint32_t v___x_5804_; 
v___x_5804_ = 0;
v___y_5773_ = v___x_5804_;
v___y_5774_ = v___x_5804_;
goto v___jp_5772_;
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_R24ExactDotCost_prepared2___boxed(lean_object* v_left_5810_, lean_object* v_right_5811_){
_start:
{
uint32_t v_res_5812_; lean_object* v_r_5813_; 
v_res_5812_ = lp_competition_Submission_R24ExactDotCost_prepared2(v_left_5810_, v_right_5811_);
v_r_5813_ = lean_box_uint32(v_res_5812_);
return v_r_5813_;
}
}
LEAN_EXPORT uint8_t lp_competition_Submission_R24ExactDotTiered_eligible64(lean_object* v_c_5814_){
_start:
{
uint8_t v_matched_5815_; 
v_matched_5815_ = lean_ctor_get_uint8(v_c_5814_, sizeof(void*)*2 + 8);
if (v_matched_5815_ == 0)
{
return v_matched_5815_;
}
else
{
lean_object* v_left_5816_; uint8_t v_normal_5817_; 
v_left_5816_ = lean_ctor_get(v_c_5814_, 0);
v_normal_5817_ = lean_ctor_get_uint8(v_left_5816_, sizeof(void*)*2 + 8);
if (v_normal_5817_ == 0)
{
return v_normal_5817_;
}
else
{
lean_object* v_right_5818_; uint8_t v_normal_5819_; 
v_right_5818_ = lean_ctor_get(v_c_5814_, 1);
v_normal_5819_ = lean_ctor_get_uint8(v_right_5818_, sizeof(void*)*2 + 8);
if (v_normal_5819_ == 0)
{
return v_normal_5819_;
}
else
{
uint32_t v_minScale_5820_; uint32_t v_maxScale_5821_; lean_object* v_data_5822_; lean_object* v___x_5823_; lean_object* v___x_5824_; uint8_t v___x_5825_; 
v_minScale_5820_ = lean_ctor_get_uint32(v_c_5814_, sizeof(void*)*2);
v_maxScale_5821_ = lean_ctor_get_uint32(v_c_5814_, sizeof(void*)*2 + 4);
v_data_5822_ = lean_ctor_get(v_left_5816_, 1);
v___x_5823_ = lean_array_get_size(v_data_5822_);
v___x_5824_ = lean_unsigned_to_nat(1048576u);
v___x_5825_ = lean_nat_dec_le(v___x_5823_, v___x_5824_);
if (v___x_5825_ == 0)
{
return v___x_5825_;
}
else
{
lean_object* v___x_5826_; lean_object* v___x_5827_; lean_object* v___x_5828_; lean_object* v___x_5829_; lean_object* v___x_5830_; lean_object* v___y_5832_; lean_object* v___x_5836_; uint64_t v___y_5838_; uint64_t v___y_5842_; uint64_t v___y_5843_; uint64_t v___y_5850_; uint64_t v___y_5851_; uint64_t v___y_5852_; uint64_t v___y_5853_; uint64_t v___y_5859_; uint64_t v___y_5860_; uint64_t v___y_5866_; uint64_t v___y_5867_; uint64_t v___y_5868_; uint64_t v___y_5869_; uint64_t v___y_5875_; uint64_t v___y_5876_; uint64_t v___y_5882_; uint64_t v___y_5883_; uint64_t v___y_5884_; uint64_t v___y_5885_; uint64_t v___y_5891_; uint64_t v___y_5892_; uint64_t v___y_5898_; uint64_t v___y_5899_; uint64_t v___y_5900_; uint64_t v___y_5901_; uint64_t v___y_5907_; uint64_t v___y_5908_; uint8_t v___x_5913_; 
v___x_5826_ = lean_unsigned_to_nat(48u);
v___x_5827_ = lean_uint32_to_nat(v_maxScale_5821_);
v___x_5828_ = lean_uint32_to_nat(v_minScale_5820_);
v___x_5829_ = lean_nat_sub(v___x_5827_, v___x_5828_);
lean_dec(v___x_5828_);
lean_dec(v___x_5827_);
v___x_5830_ = lean_nat_add(v___x_5826_, v___x_5829_);
lean_dec(v___x_5829_);
v___x_5836_ = lean_unsigned_to_nat(1u);
v___x_5913_ = lean_nat_dec_le(v___x_5823_, v___x_5836_);
if (v___x_5913_ == 0)
{
lean_object* v___x_5914_; uint64_t v___x_5915_; uint64_t v___x_5916_; uint64_t v___y_5918_; uint64_t v___x_5922_; uint64_t v___x_5923_; uint8_t v___x_5924_; 
v___x_5914_ = lean_nat_sub(v___x_5823_, v___x_5836_);
v___x_5915_ = lean_uint64_of_nat(v___x_5914_);
lean_dec(v___x_5914_);
v___x_5916_ = 32ULL;
v___x_5922_ = lean_uint64_shift_right(v___x_5915_, v___x_5916_);
v___x_5923_ = 0ULL;
v___x_5924_ = lean_uint64_dec_eq(v___x_5922_, v___x_5923_);
if (v___x_5924_ == 0)
{
v___y_5918_ = v___x_5922_;
goto v___jp_5917_;
}
else
{
v___y_5918_ = v___x_5915_;
goto v___jp_5917_;
}
v___jp_5917_:
{
uint64_t v___x_5919_; uint64_t v___x_5920_; uint8_t v___x_5921_; 
v___x_5919_ = lean_uint64_shift_right(v___x_5915_, v___x_5916_);
v___x_5920_ = 0ULL;
v___x_5921_ = lean_uint64_dec_eq(v___x_5919_, v___x_5920_);
if (v___x_5921_ == 0)
{
v___y_5907_ = v___y_5918_;
v___y_5908_ = v___x_5916_;
goto v___jp_5906_;
}
else
{
v___y_5907_ = v___y_5918_;
v___y_5908_ = v___x_5920_;
goto v___jp_5906_;
}
}
}
else
{
lean_object* v___x_5925_; 
v___x_5925_ = lean_unsigned_to_nat(0u);
v___y_5832_ = v___x_5925_;
goto v___jp_5831_;
}
v___jp_5831_:
{
lean_object* v___x_5833_; lean_object* v___x_5834_; uint8_t v___x_5835_; 
v___x_5833_ = lean_nat_add(v___x_5830_, v___y_5832_);
lean_dec(v___y_5832_);
lean_dec(v___x_5830_);
v___x_5834_ = lean_unsigned_to_nat(62u);
v___x_5835_ = lean_nat_dec_le(v___x_5833_, v___x_5834_);
lean_dec(v___x_5833_);
return v___x_5835_;
}
v___jp_5837_:
{
lean_object* v___x_5839_; lean_object* v___x_5840_; 
v___x_5839_ = lean_uint64_to_nat(v___y_5838_);
v___x_5840_ = lean_nat_add(v___x_5839_, v___x_5836_);
lean_dec(v___x_5839_);
v___y_5832_ = v___x_5840_;
goto v___jp_5831_;
}
v___jp_5841_:
{
uint64_t v___x_5844_; uint64_t v___x_5845_; uint64_t v___x_5846_; uint8_t v___x_5847_; 
v___x_5844_ = 1ULL;
v___x_5845_ = lean_uint64_shift_right(v___y_5842_, v___x_5844_);
v___x_5846_ = 0ULL;
v___x_5847_ = lean_uint64_dec_eq(v___x_5845_, v___x_5846_);
if (v___x_5847_ == 0)
{
uint64_t v___x_5848_; 
v___x_5848_ = lean_uint64_add(v___y_5843_, v___x_5844_);
v___y_5838_ = v___x_5848_;
goto v___jp_5837_;
}
else
{
v___y_5838_ = v___y_5843_;
goto v___jp_5837_;
}
}
v___jp_5849_:
{
uint64_t v___x_5854_; uint64_t v___x_5855_; uint8_t v___x_5856_; 
v___x_5854_ = lean_uint64_shift_right(v___y_5852_, v___y_5850_);
v___x_5855_ = 0ULL;
v___x_5856_ = lean_uint64_dec_eq(v___x_5854_, v___x_5855_);
if (v___x_5856_ == 0)
{
uint64_t v___x_5857_; 
v___x_5857_ = lean_uint64_add(v___y_5851_, v___y_5850_);
v___y_5842_ = v___y_5853_;
v___y_5843_ = v___x_5857_;
goto v___jp_5841_;
}
else
{
v___y_5842_ = v___y_5853_;
v___y_5843_ = v___y_5851_;
goto v___jp_5841_;
}
}
v___jp_5858_:
{
uint64_t v___x_5861_; uint64_t v___x_5862_; uint64_t v___x_5863_; uint8_t v___x_5864_; 
v___x_5861_ = 2ULL;
v___x_5862_ = lean_uint64_shift_right(v___y_5859_, v___x_5861_);
v___x_5863_ = 0ULL;
v___x_5864_ = lean_uint64_dec_eq(v___x_5862_, v___x_5863_);
if (v___x_5864_ == 0)
{
v___y_5850_ = v___x_5861_;
v___y_5851_ = v___y_5860_;
v___y_5852_ = v___y_5859_;
v___y_5853_ = v___x_5862_;
goto v___jp_5849_;
}
else
{
v___y_5850_ = v___x_5861_;
v___y_5851_ = v___y_5860_;
v___y_5852_ = v___y_5859_;
v___y_5853_ = v___y_5859_;
goto v___jp_5849_;
}
}
v___jp_5865_:
{
uint64_t v___x_5870_; uint64_t v___x_5871_; uint8_t v___x_5872_; 
v___x_5870_ = lean_uint64_shift_right(v___y_5868_, v___y_5867_);
v___x_5871_ = 0ULL;
v___x_5872_ = lean_uint64_dec_eq(v___x_5870_, v___x_5871_);
if (v___x_5872_ == 0)
{
uint64_t v___x_5873_; 
v___x_5873_ = lean_uint64_add(v___y_5866_, v___y_5867_);
v___y_5859_ = v___y_5869_;
v___y_5860_ = v___x_5873_;
goto v___jp_5858_;
}
else
{
v___y_5859_ = v___y_5869_;
v___y_5860_ = v___y_5866_;
goto v___jp_5858_;
}
}
v___jp_5874_:
{
uint64_t v___x_5877_; uint64_t v___x_5878_; uint64_t v___x_5879_; uint8_t v___x_5880_; 
v___x_5877_ = 4ULL;
v___x_5878_ = lean_uint64_shift_right(v___y_5875_, v___x_5877_);
v___x_5879_ = 0ULL;
v___x_5880_ = lean_uint64_dec_eq(v___x_5878_, v___x_5879_);
if (v___x_5880_ == 0)
{
v___y_5866_ = v___y_5876_;
v___y_5867_ = v___x_5877_;
v___y_5868_ = v___y_5875_;
v___y_5869_ = v___x_5878_;
goto v___jp_5865_;
}
else
{
v___y_5866_ = v___y_5876_;
v___y_5867_ = v___x_5877_;
v___y_5868_ = v___y_5875_;
v___y_5869_ = v___y_5875_;
goto v___jp_5865_;
}
}
v___jp_5881_:
{
uint64_t v___x_5886_; uint64_t v___x_5887_; uint8_t v___x_5888_; 
v___x_5886_ = lean_uint64_shift_right(v___y_5882_, v___y_5884_);
v___x_5887_ = 0ULL;
v___x_5888_ = lean_uint64_dec_eq(v___x_5886_, v___x_5887_);
if (v___x_5888_ == 0)
{
uint64_t v___x_5889_; 
v___x_5889_ = lean_uint64_add(v___y_5883_, v___y_5884_);
v___y_5875_ = v___y_5885_;
v___y_5876_ = v___x_5889_;
goto v___jp_5874_;
}
else
{
v___y_5875_ = v___y_5885_;
v___y_5876_ = v___y_5883_;
goto v___jp_5874_;
}
}
v___jp_5890_:
{
uint64_t v___x_5893_; uint64_t v___x_5894_; uint64_t v___x_5895_; uint8_t v___x_5896_; 
v___x_5893_ = 8ULL;
v___x_5894_ = lean_uint64_shift_right(v___y_5891_, v___x_5893_);
v___x_5895_ = 0ULL;
v___x_5896_ = lean_uint64_dec_eq(v___x_5894_, v___x_5895_);
if (v___x_5896_ == 0)
{
v___y_5882_ = v___y_5891_;
v___y_5883_ = v___y_5892_;
v___y_5884_ = v___x_5893_;
v___y_5885_ = v___x_5894_;
goto v___jp_5881_;
}
else
{
v___y_5882_ = v___y_5891_;
v___y_5883_ = v___y_5892_;
v___y_5884_ = v___x_5893_;
v___y_5885_ = v___y_5891_;
goto v___jp_5881_;
}
}
v___jp_5897_:
{
uint64_t v___x_5902_; uint64_t v___x_5903_; uint8_t v___x_5904_; 
v___x_5902_ = lean_uint64_shift_right(v___y_5898_, v___y_5900_);
v___x_5903_ = 0ULL;
v___x_5904_ = lean_uint64_dec_eq(v___x_5902_, v___x_5903_);
if (v___x_5904_ == 0)
{
uint64_t v___x_5905_; 
v___x_5905_ = lean_uint64_add(v___y_5899_, v___y_5900_);
v___y_5891_ = v___y_5901_;
v___y_5892_ = v___x_5905_;
goto v___jp_5890_;
}
else
{
v___y_5891_ = v___y_5901_;
v___y_5892_ = v___y_5899_;
goto v___jp_5890_;
}
}
v___jp_5906_:
{
uint64_t v___x_5909_; uint64_t v___x_5910_; uint64_t v___x_5911_; uint8_t v___x_5912_; 
v___x_5909_ = 16ULL;
v___x_5910_ = lean_uint64_shift_right(v___y_5907_, v___x_5909_);
v___x_5911_ = 0ULL;
v___x_5912_ = lean_uint64_dec_eq(v___x_5910_, v___x_5911_);
if (v___x_5912_ == 0)
{
v___y_5898_ = v___y_5907_;
v___y_5899_ = v___y_5908_;
v___y_5900_ = v___x_5909_;
v___y_5901_ = v___x_5910_;
goto v___jp_5897_;
}
else
{
v___y_5898_ = v___y_5907_;
v___y_5899_ = v___y_5908_;
v___y_5900_ = v___x_5909_;
v___y_5901_ = v___y_5907_;
goto v___jp_5897_;
}
}
}
}
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_R24ExactDotTiered_eligible64___boxed(lean_object* v_c_5926_){
_start:
{
uint8_t v_res_5927_; lean_object* v_r_5928_; 
v_res_5927_ = lp_competition_Submission_R24ExactDotTiered_eligible64(v_c_5926_);
lean_dec_ref(v_c_5926_);
v_r_5928_ = lean_box(v_res_5927_);
return v_r_5928_;
}
}
LEAN_EXPORT uint32_t lp_competition_Submission_R24ExactDotTiered_finish64(uint32_t v_base_5929_, uint8_t v_negZero_5930_, uint64_t v_acc_5931_){
_start:
{
uint64_t v___x_5932_; uint8_t v___y_5934_; uint64_t v___y_5935_; uint8_t v___y_5942_; uint8_t v___x_5944_; 
v___x_5932_ = 0ULL;
v___x_5944_ = lean_uint64_dec_eq(v_acc_5931_, v___x_5932_);
if (v___x_5944_ == 0)
{
uint64_t v___x_5945_; uint64_t v___x_5946_; uint8_t v___x_5947_; 
v___x_5945_ = 9223372036854775808ULL;
v___x_5946_ = lean_uint64_land(v_acc_5931_, v___x_5945_);
v___x_5947_ = lean_uint64_dec_eq(v___x_5946_, v___x_5932_);
if (v___x_5947_ == 0)
{
uint8_t v___x_5948_; 
v___x_5948_ = 1;
v___y_5942_ = v___x_5948_;
goto v___jp_5941_;
}
else
{
if (v___x_5944_ == 0)
{
v___y_5934_ = v___x_5944_;
v___y_5935_ = v_acc_5931_;
goto v___jp_5933_;
}
else
{
v___y_5942_ = v___x_5944_;
goto v___jp_5941_;
}
}
}
else
{
if (v_negZero_5930_ == 0)
{
uint32_t v___x_5949_; 
v___x_5949_ = 0;
return v___x_5949_;
}
else
{
uint32_t v___x_5950_; 
v___x_5950_ = 2147483648;
return v___x_5950_;
}
}
v___jp_5933_:
{
lean_object* v___x_5936_; lean_object* v___x_5937_; lean_object* v___x_5938_; lean_object* v___x_5939_; uint32_t v___x_5940_; 
v___x_5936_ = lean_uint32_to_nat(v_base_5929_);
v___x_5937_ = lean_nat_to_int(v___x_5936_);
v___x_5938_ = lean_obj_once(&lp_competition_Submission_R24ExactDotCost_finish___closed__0, &lp_competition_Submission_R24ExactDotCost_finish___closed__0_once, _init_lp_competition_Submission_R24ExactDotCost_finish___closed__0);
v___x_5939_ = lean_int_sub(v___x_5937_, v___x_5938_);
lean_dec(v___x_5937_);
v___x_5940_ = lp_competition_Submission_R24ExactDotCost_round128(v___y_5934_, v___y_5935_, v___x_5932_, v___x_5939_);
lean_dec(v___x_5939_);
return v___x_5940_;
}
v___jp_5941_:
{
uint64_t v___x_5943_; 
v___x_5943_ = lean_uint64_sub(v___x_5932_, v_acc_5931_);
v___y_5934_ = v___y_5942_;
v___y_5935_ = v___x_5943_;
goto v___jp_5933_;
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_R24ExactDotTiered_finish64___boxed(lean_object* v_base_5951_, lean_object* v_negZero_5952_, lean_object* v_acc_5953_){
_start:
{
uint32_t v_base_boxed_5954_; uint8_t v_negZero_boxed_5955_; uint64_t v_acc_boxed_5956_; uint32_t v_res_5957_; lean_object* v_r_5958_; 
v_base_boxed_5954_ = lean_unbox_uint32(v_base_5951_);
lean_dec(v_base_5951_);
v_negZero_boxed_5955_ = lean_unbox(v_negZero_5952_);
v_acc_boxed_5956_ = lean_unbox_uint64(v_acc_5953_);
lean_dec_ref(v_acc_5953_);
v_res_5957_ = lp_competition_Submission_R24ExactDotTiered_finish64(v_base_boxed_5954_, v_negZero_boxed_5955_, v_acc_boxed_5956_);
v_r_5958_ = lean_box_uint32(v_res_5957_);
return v_r_5958_;
}
}
LEAN_EXPORT uint32_t lp_competition_Submission_R24ExactDotTiered_native64Loop(lean_object* v_a_5959_, lean_object* v_b_5960_, uint32_t v_base_5961_, lean_object* v_index_5962_, uint8_t v_negZero_5963_, uint64_t v_acc_5964_, lean_object* v_x_5965_){
_start:
{
lean_object* v_zero_5966_; uint8_t v_isZero_5967_; 
v_zero_5966_ = lean_unsigned_to_nat(0u);
v_isZero_5967_ = lean_nat_dec_eq(v_x_5965_, v_zero_5966_);
if (v_isZero_5967_ == 1)
{
uint64_t v___x_5968_; uint8_t v___y_5970_; uint64_t v___y_5971_; uint8_t v___y_5978_; uint8_t v___x_5980_; 
lean_dec(v_x_5965_);
lean_dec(v_index_5962_);
v___x_5968_ = 0ULL;
v___x_5980_ = lean_uint64_dec_eq(v_acc_5964_, v___x_5968_);
if (v___x_5980_ == 0)
{
uint64_t v___x_5981_; uint64_t v___x_5982_; uint8_t v___x_5983_; 
v___x_5981_ = 9223372036854775808ULL;
v___x_5982_ = lean_uint64_land(v_acc_5964_, v___x_5981_);
v___x_5983_ = lean_uint64_dec_eq(v___x_5982_, v___x_5968_);
if (v___x_5983_ == 0)
{
v___y_5978_ = v_isZero_5967_;
goto v___jp_5977_;
}
else
{
v___y_5978_ = v___x_5980_;
goto v___jp_5977_;
}
}
else
{
if (v_negZero_5963_ == 0)
{
uint32_t v___x_5984_; 
v___x_5984_ = 0;
return v___x_5984_;
}
else
{
uint32_t v___x_5985_; 
v___x_5985_ = 2147483648;
return v___x_5985_;
}
}
v___jp_5969_:
{
lean_object* v___x_5972_; lean_object* v___x_5973_; lean_object* v___x_5974_; lean_object* v___x_5975_; uint32_t v___x_5976_; 
v___x_5972_ = lean_uint32_to_nat(v_base_5961_);
v___x_5973_ = lean_nat_to_int(v___x_5972_);
v___x_5974_ = lean_obj_once(&lp_competition_Submission_R24ExactDotCost_finish___closed__0, &lp_competition_Submission_R24ExactDotCost_finish___closed__0_once, _init_lp_competition_Submission_R24ExactDotCost_finish___closed__0);
v___x_5975_ = lean_int_sub(v___x_5973_, v___x_5974_);
lean_dec(v___x_5973_);
v___x_5976_ = lp_competition_Submission_R24ExactDotCost_round128(v___y_5970_, v___y_5971_, v___x_5968_, v___x_5975_);
lean_dec(v___x_5975_);
return v___x_5976_;
}
v___jp_5977_:
{
if (v___y_5978_ == 0)
{
v___y_5970_ = v___y_5978_;
v___y_5971_ = v_acc_5964_;
goto v___jp_5969_;
}
else
{
uint64_t v___x_5979_; 
v___x_5979_ = lean_uint64_sub(v___x_5968_, v_acc_5964_);
v___y_5970_ = v___y_5978_;
v___y_5971_ = v___x_5979_;
goto v___jp_5969_;
}
}
}
else
{
uint32_t v___x_5986_; lean_object* v_one_5987_; lean_object* v_n_5988_; uint64_t v___y_5990_; uint8_t v___y_5991_; lean_object* v___x_5995_; lean_object* v_wa_5996_; lean_object* v___x_5997_; lean_object* v_wb_5998_; uint64_t v___y_6000_; uint8_t v___y_6001_; uint64_t v___y_6002_; uint64_t v___y_6021_; uint8_t v___y_6022_; uint64_t v___y_6025_; uint64_t v___y_6028_; uint8_t v___y_6029_; uint64_t v___y_6032_; uint8_t v___y_6033_; uint8_t v___y_6034_; uint64_t v___y_6036_; uint8_t v___y_6037_; uint64_t v___y_6044_; uint64_t v___y_6045_; uint64_t v___y_6053_; uint32_t v___x_6068_; uint32_t v___x_6069_; uint32_t v___x_6070_; uint32_t v___x_6071_; uint32_t v___x_6072_; uint32_t v___x_6073_; uint8_t v___x_6074_; 
v___x_5986_ = 0;
v_one_5987_ = lean_unsigned_to_nat(1u);
v_n_5988_ = lean_nat_sub(v_x_5965_, v_one_5987_);
lean_dec(v_x_5965_);
v___x_5995_ = lp_competition_Submission_R24ExactDotCost_prepareOperand___closed__2___boxed__const__1;
v_wa_5996_ = lean_array_get_borrowed(v___x_5995_, v_a_5959_, v_index_5962_);
v___x_5997_ = lp_competition_Submission_R24ExactDotCost_prepareOperand___closed__2___boxed__const__1;
v_wb_5998_ = lean_array_get_borrowed(v___x_5997_, v_b_5960_, v_index_5962_);
v___x_6068_ = 23;
v___x_6069_ = lean_unbox_uint32(v_wa_5996_);
v___x_6070_ = lean_uint32_shift_right(v___x_6069_, v___x_6068_);
v___x_6071_ = 255;
v___x_6072_ = lean_uint32_land(v___x_6070_, v___x_6071_);
v___x_6073_ = 254;
v___x_6074_ = lean_uint32_dec_eq(v___x_6072_, v___x_6073_);
if (v___x_6074_ == 0)
{
uint32_t v___x_6075_; uint32_t v___x_6076_; uint32_t v___x_6077_; uint32_t v___x_6078_; uint32_t v___x_6079_; uint64_t v___x_6080_; 
v___x_6075_ = 8388607;
v___x_6076_ = lean_unbox_uint32(v_wa_5996_);
v___x_6077_ = lean_uint32_land(v___x_6076_, v___x_6075_);
v___x_6078_ = 8388608;
v___x_6079_ = lean_uint32_lor(v___x_6077_, v___x_6078_);
v___x_6080_ = lean_uint32_to_uint64(v___x_6079_);
v___y_6053_ = v___x_6080_;
goto v___jp_6052_;
}
else
{
uint64_t v___x_6081_; 
v___x_6081_ = 0ULL;
v___y_6053_ = v___x_6081_;
goto v___jp_6052_;
}
v___jp_5989_:
{
lean_object* v___x_5992_; uint64_t v___x_5993_; 
v___x_5992_ = lean_nat_add(v_index_5962_, v_one_5987_);
lean_dec(v_index_5962_);
v___x_5993_ = lean_uint64_add(v_acc_5964_, v___y_5990_);
v_index_5962_ = v___x_5992_;
v_negZero_5963_ = v___y_5991_;
v_acc_5964_ = v___x_5993_;
v_x_5965_ = v_n_5988_;
goto _start;
}
v___jp_5999_:
{
uint64_t v___x_6003_; uint64_t v_signMask_6004_; uint32_t v___x_6005_; uint32_t v___x_6006_; uint32_t v___x_6007_; uint32_t v___x_6008_; uint32_t v___x_6009_; uint32_t v___x_6010_; uint32_t v___x_6011_; uint32_t v___x_6012_; uint32_t v___x_6013_; uint32_t v___x_6014_; uint64_t v_shift_6015_; uint64_t v___x_6016_; uint64_t v___x_6017_; uint64_t v_term_6018_; 
v___x_6003_ = 0ULL;
v_signMask_6004_ = lean_uint64_sub(v___x_6003_, v___y_6002_);
v___x_6005_ = 23;
v___x_6006_ = lean_unbox_uint32(v_wa_5996_);
v___x_6007_ = lean_uint32_shift_right(v___x_6006_, v___x_6005_);
v___x_6008_ = 255;
v___x_6009_ = lean_uint32_land(v___x_6007_, v___x_6008_);
v___x_6010_ = lean_unbox_uint32(v_wb_5998_);
v___x_6011_ = lean_uint32_shift_right(v___x_6010_, v___x_6005_);
v___x_6012_ = lean_uint32_land(v___x_6011_, v___x_6008_);
v___x_6013_ = lean_uint32_add(v___x_6009_, v___x_6012_);
v___x_6014_ = lean_uint32_sub(v___x_6013_, v_base_5961_);
v_shift_6015_ = lean_uint32_to_uint64(v___x_6014_);
v___x_6016_ = lean_uint64_shift_left(v___y_6000_, v_shift_6015_);
v___x_6017_ = lean_uint64_xor(v___x_6016_, v_signMask_6004_);
v_term_6018_ = lean_uint64_add(v___x_6017_, v___y_6002_);
if (v_negZero_5963_ == 0)
{
v___y_5990_ = v_term_6018_;
v___y_5991_ = v_negZero_5963_;
goto v___jp_5989_;
}
else
{
uint8_t v___x_6019_; 
v___x_6019_ = lean_uint64_dec_eq(v___y_6000_, v___x_6003_);
if (v___x_6019_ == 0)
{
v___y_5990_ = v_term_6018_;
v___y_5991_ = v___x_6019_;
goto v___jp_5989_;
}
else
{
v___y_5990_ = v_term_6018_;
v___y_5991_ = v___y_6001_;
goto v___jp_5989_;
}
}
}
v___jp_6020_:
{
uint64_t v___x_6023_; 
v___x_6023_ = 1ULL;
v___y_6000_ = v___y_6021_;
v___y_6001_ = v___y_6022_;
v___y_6002_ = v___x_6023_;
goto v___jp_5999_;
}
v___jp_6024_:
{
uint8_t v___x_6026_; 
v___x_6026_ = 1;
v___y_6021_ = v___y_6025_;
v___y_6022_ = v___x_6026_;
goto v___jp_6020_;
}
v___jp_6027_:
{
if (v___y_6029_ == 0)
{
uint64_t v___x_6030_; 
v___x_6030_ = 0ULL;
v___y_6000_ = v___y_6028_;
v___y_6001_ = v___y_6029_;
v___y_6002_ = v___x_6030_;
goto v___jp_5999_;
}
else
{
v___y_6021_ = v___y_6028_;
v___y_6022_ = v___y_6029_;
goto v___jp_6020_;
}
}
v___jp_6031_:
{
if (v___y_6033_ == 0)
{
if (v___y_6034_ == 0)
{
v___y_6028_ = v___y_6032_;
v___y_6029_ = v_isZero_5967_;
goto v___jp_6027_;
}
else
{
v___y_6025_ = v___y_6032_;
goto v___jp_6024_;
}
}
else
{
if (v___y_6034_ == 0)
{
v___y_6025_ = v___y_6032_;
goto v___jp_6024_;
}
else
{
v___y_6028_ = v___y_6032_;
v___y_6029_ = v_isZero_5967_;
goto v___jp_6027_;
}
}
}
v___jp_6035_:
{
uint32_t v___x_6038_; uint32_t v___x_6039_; uint32_t v___x_6040_; uint8_t v___x_6041_; 
v___x_6038_ = 2147483648;
v___x_6039_ = lean_unbox_uint32(v_wb_5998_);
v___x_6040_ = lean_uint32_land(v___x_6039_, v___x_6038_);
v___x_6041_ = lean_uint32_dec_eq(v___x_6040_, v___x_5986_);
if (v___x_6041_ == 0)
{
uint8_t v___x_6042_; 
v___x_6042_ = 1;
v___y_6032_ = v___y_6036_;
v___y_6033_ = v___y_6037_;
v___y_6034_ = v___x_6042_;
goto v___jp_6031_;
}
else
{
v___y_6032_ = v___y_6036_;
v___y_6033_ = v___y_6037_;
v___y_6034_ = v_isZero_5967_;
goto v___jp_6031_;
}
}
v___jp_6043_:
{
uint64_t v_product_6046_; uint32_t v___x_6047_; uint32_t v___x_6048_; uint32_t v___x_6049_; uint8_t v___x_6050_; 
v_product_6046_ = lean_uint64_mul(v___y_6044_, v___y_6045_);
v___x_6047_ = 2147483648;
v___x_6048_ = lean_unbox_uint32(v_wa_5996_);
v___x_6049_ = lean_uint32_land(v___x_6048_, v___x_6047_);
v___x_6050_ = lean_uint32_dec_eq(v___x_6049_, v___x_5986_);
if (v___x_6050_ == 0)
{
uint8_t v___x_6051_; 
v___x_6051_ = 1;
v___y_6036_ = v_product_6046_;
v___y_6037_ = v___x_6051_;
goto v___jp_6035_;
}
else
{
v___y_6036_ = v_product_6046_;
v___y_6037_ = v_isZero_5967_;
goto v___jp_6035_;
}
}
v___jp_6052_:
{
uint32_t v___x_6054_; uint32_t v___x_6055_; uint32_t v___x_6056_; uint32_t v___x_6057_; uint32_t v___x_6058_; uint32_t v___x_6059_; uint8_t v___x_6060_; 
v___x_6054_ = 23;
v___x_6055_ = lean_unbox_uint32(v_wb_5998_);
v___x_6056_ = lean_uint32_shift_right(v___x_6055_, v___x_6054_);
v___x_6057_ = 255;
v___x_6058_ = lean_uint32_land(v___x_6056_, v___x_6057_);
v___x_6059_ = 254;
v___x_6060_ = lean_uint32_dec_eq(v___x_6058_, v___x_6059_);
if (v___x_6060_ == 0)
{
uint32_t v___x_6061_; uint32_t v___x_6062_; uint32_t v___x_6063_; uint32_t v___x_6064_; uint32_t v___x_6065_; uint64_t v___x_6066_; 
v___x_6061_ = 8388607;
v___x_6062_ = lean_unbox_uint32(v_wb_5998_);
v___x_6063_ = lean_uint32_land(v___x_6062_, v___x_6061_);
v___x_6064_ = 8388608;
v___x_6065_ = lean_uint32_lor(v___x_6063_, v___x_6064_);
v___x_6066_ = lean_uint32_to_uint64(v___x_6065_);
v___y_6044_ = v___y_6053_;
v___y_6045_ = v___x_6066_;
goto v___jp_6043_;
}
else
{
uint64_t v___x_6067_; 
v___x_6067_ = 0ULL;
v___y_6044_ = v___y_6053_;
v___y_6045_ = v___x_6067_;
goto v___jp_6043_;
}
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_R24ExactDotTiered_native64Loop___boxed(lean_object* v_a_6082_, lean_object* v_b_6083_, lean_object* v_base_6084_, lean_object* v_index_6085_, lean_object* v_negZero_6086_, lean_object* v_acc_6087_, lean_object* v_x_6088_){
_start:
{
uint32_t v_base_boxed_6089_; uint8_t v_negZero_boxed_6090_; uint64_t v_acc_boxed_6091_; uint32_t v_res_6092_; lean_object* v_r_6093_; 
v_base_boxed_6089_ = lean_unbox_uint32(v_base_6084_);
lean_dec(v_base_6084_);
v_negZero_boxed_6090_ = lean_unbox(v_negZero_6086_);
v_acc_boxed_6091_ = lean_unbox_uint64(v_acc_6087_);
lean_dec_ref(v_acc_6087_);
v_res_6092_ = lp_competition_Submission_R24ExactDotTiered_native64Loop(v_a_6082_, v_b_6083_, v_base_boxed_6089_, v_index_6085_, v_negZero_boxed_6090_, v_acc_boxed_6091_, v_x_6088_);
lean_dec_ref(v_b_6083_);
lean_dec_ref(v_a_6082_);
v_r_6093_ = lean_box_uint32(v_res_6092_);
return v_r_6093_;
}
}
LEAN_EXPORT uint32_t lp_competition_Submission_R24ExactDotTiered_exactPreparedV2(lean_object* v_c_6094_){
_start:
{
lean_object* v___y_6096_; lean_object* v___y_6097_; lean_object* v___y_6098_; lean_object* v___y_6099_; uint32_t v___y_6100_; uint8_t v___y_6101_; uint8_t v___y_6105_; lean_object* v___y_6106_; lean_object* v___y_6107_; lean_object* v___y_6108_; uint32_t v___y_6109_; lean_object* v___y_6110_; lean_object* v___y_6111_; uint8_t v___y_6119_; lean_object* v___y_6120_; lean_object* v___y_6121_; lean_object* v___y_6122_; lean_object* v___y_6123_; lean_object* v___y_6124_; uint32_t v___y_6125_; uint64_t v___y_6126_; uint8_t v___y_6130_; lean_object* v___y_6131_; lean_object* v___y_6132_; lean_object* v___y_6133_; lean_object* v___y_6134_; uint64_t v___y_6135_; uint32_t v___y_6136_; lean_object* v___y_6137_; uint64_t v___y_6138_; uint64_t v___y_6145_; uint8_t v___y_6146_; lean_object* v___y_6147_; uint64_t v___y_6148_; lean_object* v___y_6149_; lean_object* v___y_6150_; uint64_t v___y_6151_; lean_object* v___y_6152_; lean_object* v___y_6153_; uint32_t v___y_6154_; uint64_t v___y_6155_; uint8_t v___y_6161_; lean_object* v___y_6162_; lean_object* v___y_6163_; lean_object* v___y_6164_; uint64_t v___y_6165_; lean_object* v___y_6166_; uint32_t v___y_6167_; lean_object* v___y_6168_; uint64_t v___y_6169_; uint64_t v___y_6175_; uint64_t v___y_6176_; uint8_t v___y_6177_; lean_object* v___y_6178_; lean_object* v___y_6179_; lean_object* v___y_6180_; lean_object* v___y_6181_; uint64_t v___y_6182_; lean_object* v___y_6183_; uint32_t v___y_6184_; uint64_t v___y_6185_; uint64_t v___y_6191_; uint8_t v___y_6192_; lean_object* v___y_6193_; lean_object* v___y_6194_; lean_object* v___y_6195_; lean_object* v___y_6196_; uint32_t v___y_6197_; lean_object* v___y_6198_; uint64_t v___y_6199_; uint8_t v___y_6205_; lean_object* v___y_6206_; lean_object* v___y_6207_; lean_object* v___y_6208_; lean_object* v___y_6209_; uint64_t v___y_6210_; uint64_t v___y_6211_; uint64_t v___y_6212_; lean_object* v___y_6213_; uint32_t v___y_6214_; uint64_t v___y_6215_; uint8_t v___y_6221_; lean_object* v___y_6222_; lean_object* v___y_6223_; lean_object* v___y_6224_; lean_object* v___y_6225_; uint64_t v___y_6226_; uint32_t v___y_6227_; lean_object* v___y_6228_; uint64_t v___y_6229_; uint8_t v___y_6235_; lean_object* v___y_6236_; lean_object* v___y_6237_; uint64_t v___y_6238_; lean_object* v___y_6239_; lean_object* v___y_6240_; uint64_t v___y_6241_; uint64_t v___y_6242_; lean_object* v___y_6243_; uint32_t v___y_6244_; uint64_t v___y_6245_; uint8_t v___y_6251_; lean_object* v___y_6252_; lean_object* v___y_6253_; lean_object* v___y_6254_; lean_object* v___y_6255_; uint64_t v___y_6256_; uint32_t v___y_6257_; lean_object* v___y_6258_; uint64_t v___y_6259_; uint64_t v___y_6265_; uint8_t v___y_6266_; uint64_t v___y_6267_; lean_object* v___y_6268_; lean_object* v___y_6269_; lean_object* v___y_6270_; lean_object* v___y_6271_; lean_object* v___y_6272_; uint32_t v___y_6273_; uint64_t v___y_6274_; lean_object* v_left_6278_; lean_object* v_right_6279_; uint32_t v_minScale_6280_; uint32_t v_maxScale_6281_; uint8_t v_matched_6282_; uint8_t v___y_6284_; 
v_left_6278_ = lean_ctor_get(v_c_6094_, 0);
v_right_6279_ = lean_ctor_get(v_c_6094_, 1);
v_minScale_6280_ = lean_ctor_get_uint32(v_c_6094_, sizeof(void*)*2);
v_maxScale_6281_ = lean_ctor_get_uint32(v_c_6094_, sizeof(void*)*2 + 4);
v_matched_6282_ = lean_ctor_get_uint8(v_c_6094_, sizeof(void*)*2 + 8);
if (v_matched_6282_ == 0)
{
v___y_6284_ = v_matched_6282_;
goto v___jp_6283_;
}
else
{
uint8_t v_normal_6310_; 
v_normal_6310_ = lean_ctor_get_uint8(v_left_6278_, sizeof(void*)*2 + 8);
if (v_normal_6310_ == 0)
{
v___y_6284_ = v_normal_6310_;
goto v___jp_6283_;
}
else
{
uint8_t v_normal_6311_; 
v_normal_6311_ = lean_ctor_get_uint8(v_right_6279_, sizeof(void*)*2 + 8);
if (v_normal_6311_ == 0)
{
v___y_6284_ = v_normal_6311_;
goto v___jp_6283_;
}
else
{
lean_object* v_data_6312_; lean_object* v_data_6313_; lean_object* v___x_6314_; lean_object* v___y_6316_; uint8_t v___y_6317_; lean_object* v___x_6320_; uint8_t v___x_6321_; 
v_data_6312_ = lean_ctor_get(v_left_6278_, 1);
v_data_6313_ = lean_ctor_get(v_right_6279_, 1);
v___x_6314_ = lean_array_get_size(v_data_6312_);
v___x_6320_ = lean_unsigned_to_nat(1048576u);
v___x_6321_ = lean_nat_dec_le(v___x_6314_, v___x_6320_);
if (v___x_6321_ == 0)
{
v___y_6284_ = v___x_6321_;
goto v___jp_6283_;
}
else
{
lean_object* v___x_6322_; lean_object* v___x_6323_; lean_object* v___x_6324_; lean_object* v___x_6325_; lean_object* v___x_6326_; lean_object* v___y_6328_; lean_object* v___x_6335_; uint64_t v___y_6337_; uint64_t v___y_6341_; uint64_t v___y_6342_; uint64_t v___y_6349_; uint64_t v___y_6350_; uint64_t v___y_6351_; uint64_t v___y_6352_; uint64_t v___y_6358_; uint64_t v___y_6359_; uint64_t v___y_6365_; uint64_t v___y_6366_; uint64_t v___y_6367_; uint64_t v___y_6368_; uint64_t v___y_6374_; uint64_t v___y_6375_; uint64_t v___y_6381_; uint64_t v___y_6382_; uint64_t v___y_6383_; uint64_t v___y_6384_; uint64_t v___y_6390_; uint64_t v___y_6391_; uint64_t v___y_6397_; uint64_t v___y_6398_; uint64_t v___y_6399_; uint64_t v___y_6400_; uint64_t v___y_6406_; uint64_t v___y_6407_; uint8_t v___x_6412_; 
v___x_6322_ = lean_unsigned_to_nat(48u);
v___x_6323_ = lean_uint32_to_nat(v_maxScale_6281_);
v___x_6324_ = lean_uint32_to_nat(v_minScale_6280_);
v___x_6325_ = lean_nat_sub(v___x_6323_, v___x_6324_);
lean_dec(v___x_6324_);
lean_dec(v___x_6323_);
v___x_6326_ = lean_nat_add(v___x_6322_, v___x_6325_);
lean_dec(v___x_6325_);
v___x_6335_ = lean_unsigned_to_nat(1u);
v___x_6412_ = lean_nat_dec_le(v___x_6314_, v___x_6335_);
if (v___x_6412_ == 0)
{
lean_object* v___x_6413_; uint64_t v___x_6414_; uint64_t v___x_6415_; uint64_t v___y_6417_; uint64_t v___x_6421_; uint64_t v___x_6422_; uint8_t v___x_6423_; 
v___x_6413_ = lean_nat_sub(v___x_6314_, v___x_6335_);
v___x_6414_ = lean_uint64_of_nat(v___x_6413_);
lean_dec(v___x_6413_);
v___x_6415_ = 32ULL;
v___x_6421_ = lean_uint64_shift_right(v___x_6414_, v___x_6415_);
v___x_6422_ = 0ULL;
v___x_6423_ = lean_uint64_dec_eq(v___x_6421_, v___x_6422_);
if (v___x_6423_ == 0)
{
v___y_6417_ = v___x_6421_;
goto v___jp_6416_;
}
else
{
v___y_6417_ = v___x_6414_;
goto v___jp_6416_;
}
v___jp_6416_:
{
uint64_t v___x_6418_; uint64_t v___x_6419_; uint8_t v___x_6420_; 
v___x_6418_ = lean_uint64_shift_right(v___x_6414_, v___x_6415_);
v___x_6419_ = 0ULL;
v___x_6420_ = lean_uint64_dec_eq(v___x_6418_, v___x_6419_);
if (v___x_6420_ == 0)
{
v___y_6406_ = v___y_6417_;
v___y_6407_ = v___x_6415_;
goto v___jp_6405_;
}
else
{
v___y_6406_ = v___y_6417_;
v___y_6407_ = v___x_6419_;
goto v___jp_6405_;
}
}
}
else
{
lean_object* v___x_6424_; 
v___x_6424_ = lean_unsigned_to_nat(0u);
v___y_6328_ = v___x_6424_;
goto v___jp_6327_;
}
v___jp_6327_:
{
lean_object* v___x_6329_; lean_object* v___x_6330_; uint8_t v___x_6331_; 
v___x_6329_ = lean_nat_add(v___x_6326_, v___y_6328_);
lean_dec(v___y_6328_);
lean_dec(v___x_6326_);
v___x_6330_ = lean_unsigned_to_nat(62u);
v___x_6331_ = lean_nat_dec_le(v___x_6329_, v___x_6330_);
lean_dec(v___x_6329_);
if (v___x_6331_ == 0)
{
v___y_6284_ = v___x_6331_;
goto v___jp_6283_;
}
else
{
lean_object* v___x_6332_; uint8_t v___x_6333_; 
v___x_6332_ = lean_unsigned_to_nat(0u);
v___x_6333_ = lean_nat_dec_eq(v___x_6314_, v___x_6332_);
if (v___x_6333_ == 0)
{
v___y_6316_ = v___x_6332_;
v___y_6317_ = v___x_6331_;
goto v___jp_6315_;
}
else
{
uint8_t v___x_6334_; 
v___x_6334_ = 0;
v___y_6316_ = v___x_6332_;
v___y_6317_ = v___x_6334_;
goto v___jp_6315_;
}
}
}
v___jp_6336_:
{
lean_object* v___x_6338_; lean_object* v___x_6339_; 
v___x_6338_ = lean_uint64_to_nat(v___y_6337_);
v___x_6339_ = lean_nat_add(v___x_6338_, v___x_6335_);
lean_dec(v___x_6338_);
v___y_6328_ = v___x_6339_;
goto v___jp_6327_;
}
v___jp_6340_:
{
uint64_t v___x_6343_; uint64_t v___x_6344_; uint64_t v___x_6345_; uint8_t v___x_6346_; 
v___x_6343_ = 1ULL;
v___x_6344_ = lean_uint64_shift_right(v___y_6341_, v___x_6343_);
v___x_6345_ = 0ULL;
v___x_6346_ = lean_uint64_dec_eq(v___x_6344_, v___x_6345_);
if (v___x_6346_ == 0)
{
uint64_t v___x_6347_; 
v___x_6347_ = lean_uint64_add(v___y_6342_, v___x_6343_);
v___y_6337_ = v___x_6347_;
goto v___jp_6336_;
}
else
{
v___y_6337_ = v___y_6342_;
goto v___jp_6336_;
}
}
v___jp_6348_:
{
uint64_t v___x_6353_; uint64_t v___x_6354_; uint8_t v___x_6355_; 
v___x_6353_ = lean_uint64_shift_right(v___y_6350_, v___y_6351_);
v___x_6354_ = 0ULL;
v___x_6355_ = lean_uint64_dec_eq(v___x_6353_, v___x_6354_);
if (v___x_6355_ == 0)
{
uint64_t v___x_6356_; 
v___x_6356_ = lean_uint64_add(v___y_6349_, v___y_6351_);
v___y_6341_ = v___y_6352_;
v___y_6342_ = v___x_6356_;
goto v___jp_6340_;
}
else
{
v___y_6341_ = v___y_6352_;
v___y_6342_ = v___y_6349_;
goto v___jp_6340_;
}
}
v___jp_6357_:
{
uint64_t v___x_6360_; uint64_t v___x_6361_; uint64_t v___x_6362_; uint8_t v___x_6363_; 
v___x_6360_ = 2ULL;
v___x_6361_ = lean_uint64_shift_right(v___y_6358_, v___x_6360_);
v___x_6362_ = 0ULL;
v___x_6363_ = lean_uint64_dec_eq(v___x_6361_, v___x_6362_);
if (v___x_6363_ == 0)
{
v___y_6349_ = v___y_6359_;
v___y_6350_ = v___y_6358_;
v___y_6351_ = v___x_6360_;
v___y_6352_ = v___x_6361_;
goto v___jp_6348_;
}
else
{
v___y_6349_ = v___y_6359_;
v___y_6350_ = v___y_6358_;
v___y_6351_ = v___x_6360_;
v___y_6352_ = v___y_6358_;
goto v___jp_6348_;
}
}
v___jp_6364_:
{
uint64_t v___x_6369_; uint64_t v___x_6370_; uint8_t v___x_6371_; 
v___x_6369_ = lean_uint64_shift_right(v___y_6367_, v___y_6365_);
v___x_6370_ = 0ULL;
v___x_6371_ = lean_uint64_dec_eq(v___x_6369_, v___x_6370_);
if (v___x_6371_ == 0)
{
uint64_t v___x_6372_; 
v___x_6372_ = lean_uint64_add(v___y_6366_, v___y_6365_);
v___y_6358_ = v___y_6368_;
v___y_6359_ = v___x_6372_;
goto v___jp_6357_;
}
else
{
v___y_6358_ = v___y_6368_;
v___y_6359_ = v___y_6366_;
goto v___jp_6357_;
}
}
v___jp_6373_:
{
uint64_t v___x_6376_; uint64_t v___x_6377_; uint64_t v___x_6378_; uint8_t v___x_6379_; 
v___x_6376_ = 4ULL;
v___x_6377_ = lean_uint64_shift_right(v___y_6374_, v___x_6376_);
v___x_6378_ = 0ULL;
v___x_6379_ = lean_uint64_dec_eq(v___x_6377_, v___x_6378_);
if (v___x_6379_ == 0)
{
v___y_6365_ = v___x_6376_;
v___y_6366_ = v___y_6375_;
v___y_6367_ = v___y_6374_;
v___y_6368_ = v___x_6377_;
goto v___jp_6364_;
}
else
{
v___y_6365_ = v___x_6376_;
v___y_6366_ = v___y_6375_;
v___y_6367_ = v___y_6374_;
v___y_6368_ = v___y_6374_;
goto v___jp_6364_;
}
}
v___jp_6380_:
{
uint64_t v___x_6385_; uint64_t v___x_6386_; uint8_t v___x_6387_; 
v___x_6385_ = lean_uint64_shift_right(v___y_6382_, v___y_6383_);
v___x_6386_ = 0ULL;
v___x_6387_ = lean_uint64_dec_eq(v___x_6385_, v___x_6386_);
if (v___x_6387_ == 0)
{
uint64_t v___x_6388_; 
v___x_6388_ = lean_uint64_add(v___y_6381_, v___y_6383_);
v___y_6374_ = v___y_6384_;
v___y_6375_ = v___x_6388_;
goto v___jp_6373_;
}
else
{
v___y_6374_ = v___y_6384_;
v___y_6375_ = v___y_6381_;
goto v___jp_6373_;
}
}
v___jp_6389_:
{
uint64_t v___x_6392_; uint64_t v___x_6393_; uint64_t v___x_6394_; uint8_t v___x_6395_; 
v___x_6392_ = 8ULL;
v___x_6393_ = lean_uint64_shift_right(v___y_6390_, v___x_6392_);
v___x_6394_ = 0ULL;
v___x_6395_ = lean_uint64_dec_eq(v___x_6393_, v___x_6394_);
if (v___x_6395_ == 0)
{
v___y_6381_ = v___y_6391_;
v___y_6382_ = v___y_6390_;
v___y_6383_ = v___x_6392_;
v___y_6384_ = v___x_6393_;
goto v___jp_6380_;
}
else
{
v___y_6381_ = v___y_6391_;
v___y_6382_ = v___y_6390_;
v___y_6383_ = v___x_6392_;
v___y_6384_ = v___y_6390_;
goto v___jp_6380_;
}
}
v___jp_6396_:
{
uint64_t v___x_6401_; uint64_t v___x_6402_; uint8_t v___x_6403_; 
v___x_6401_ = lean_uint64_shift_right(v___y_6398_, v___y_6399_);
v___x_6402_ = 0ULL;
v___x_6403_ = lean_uint64_dec_eq(v___x_6401_, v___x_6402_);
if (v___x_6403_ == 0)
{
uint64_t v___x_6404_; 
v___x_6404_ = lean_uint64_add(v___y_6397_, v___y_6399_);
v___y_6390_ = v___y_6400_;
v___y_6391_ = v___x_6404_;
goto v___jp_6389_;
}
else
{
v___y_6390_ = v___y_6400_;
v___y_6391_ = v___y_6397_;
goto v___jp_6389_;
}
}
v___jp_6405_:
{
uint64_t v___x_6408_; uint64_t v___x_6409_; uint64_t v___x_6410_; uint8_t v___x_6411_; 
v___x_6408_ = 16ULL;
v___x_6409_ = lean_uint64_shift_right(v___y_6406_, v___x_6408_);
v___x_6410_ = 0ULL;
v___x_6411_ = lean_uint64_dec_eq(v___x_6409_, v___x_6410_);
if (v___x_6411_ == 0)
{
v___y_6397_ = v___y_6407_;
v___y_6398_ = v___y_6406_;
v___y_6399_ = v___x_6408_;
v___y_6400_ = v___x_6409_;
goto v___jp_6396_;
}
else
{
v___y_6397_ = v___y_6407_;
v___y_6398_ = v___y_6406_;
v___y_6399_ = v___x_6408_;
v___y_6400_ = v___y_6406_;
goto v___jp_6396_;
}
}
}
v___jp_6315_:
{
uint64_t v___x_6318_; uint32_t v___x_6319_; 
v___x_6318_ = 0ULL;
v___x_6319_ = lp_competition_Submission_R24ExactDotTiered_native64Loop(v_data_6312_, v_data_6313_, v_minScale_6280_, v___y_6316_, v___y_6317_, v___x_6318_, v___x_6314_);
return v___x_6319_;
}
}
}
}
v___jp_6095_:
{
uint64_t v___x_6102_; uint32_t v___x_6103_; 
v___x_6102_ = 0ULL;
v___x_6103_ = lp_competition_Submission_R24ExactDotCost_nativeLoop(v___y_6098_, v___y_6097_, v___y_6100_, v___y_6099_, v___y_6101_, v___x_6102_, v___x_6102_, v___x_6102_, v___x_6102_, v___y_6096_);
return v___x_6103_;
}
v___jp_6104_:
{
lean_object* v___x_6112_; lean_object* v___x_6113_; uint8_t v___x_6114_; 
v___x_6112_ = lean_nat_add(v___y_6110_, v___y_6111_);
lean_dec(v___y_6111_);
lean_dec(v___y_6110_);
v___x_6113_ = lean_unsigned_to_nat(128u);
v___x_6114_ = lean_nat_dec_le(v___x_6112_, v___x_6113_);
lean_dec(v___x_6112_);
if (v___x_6114_ == 0)
{
uint32_t v___x_6115_; 
lean_dec(v___y_6106_);
v___x_6115_ = lp_competition_Submission_R24ExactDotCost_referencePrepared(v_c_6094_);
return v___x_6115_;
}
else
{
lean_object* v___x_6116_; uint8_t v___x_6117_; 
v___x_6116_ = lean_unsigned_to_nat(0u);
v___x_6117_ = lean_nat_dec_eq(v___y_6106_, v___x_6116_);
if (v___x_6117_ == 0)
{
v___y_6096_ = v___y_6106_;
v___y_6097_ = v___y_6107_;
v___y_6098_ = v___y_6108_;
v___y_6099_ = v___x_6116_;
v___y_6100_ = v___y_6109_;
v___y_6101_ = v___x_6114_;
goto v___jp_6095_;
}
else
{
v___y_6096_ = v___y_6106_;
v___y_6097_ = v___y_6107_;
v___y_6098_ = v___y_6108_;
v___y_6099_ = v___x_6116_;
v___y_6100_ = v___y_6109_;
v___y_6101_ = v___y_6105_;
goto v___jp_6095_;
}
}
}
v___jp_6118_:
{
lean_object* v___x_6127_; lean_object* v___x_6128_; 
v___x_6127_ = lean_uint64_to_nat(v___y_6126_);
v___x_6128_ = lean_nat_add(v___x_6127_, v___y_6120_);
lean_dec(v___x_6127_);
v___y_6105_ = v___y_6119_;
v___y_6106_ = v___y_6121_;
v___y_6107_ = v___y_6122_;
v___y_6108_ = v___y_6123_;
v___y_6109_ = v___y_6125_;
v___y_6110_ = v___y_6124_;
v___y_6111_ = v___x_6128_;
goto v___jp_6104_;
}
v___jp_6129_:
{
uint64_t v___x_6139_; uint64_t v___x_6140_; uint64_t v___x_6141_; uint8_t v___x_6142_; 
v___x_6139_ = 1ULL;
v___x_6140_ = lean_uint64_shift_right(v___y_6135_, v___x_6139_);
v___x_6141_ = 0ULL;
v___x_6142_ = lean_uint64_dec_eq(v___x_6140_, v___x_6141_);
if (v___x_6142_ == 0)
{
uint64_t v___x_6143_; 
v___x_6143_ = lean_uint64_add(v___y_6138_, v___x_6139_);
v___y_6119_ = v___y_6130_;
v___y_6120_ = v___y_6131_;
v___y_6121_ = v___y_6132_;
v___y_6122_ = v___y_6133_;
v___y_6123_ = v___y_6134_;
v___y_6124_ = v___y_6137_;
v___y_6125_ = v___y_6136_;
v___y_6126_ = v___x_6143_;
goto v___jp_6118_;
}
else
{
v___y_6119_ = v___y_6130_;
v___y_6120_ = v___y_6131_;
v___y_6121_ = v___y_6132_;
v___y_6122_ = v___y_6133_;
v___y_6123_ = v___y_6134_;
v___y_6124_ = v___y_6137_;
v___y_6125_ = v___y_6136_;
v___y_6126_ = v___y_6138_;
goto v___jp_6118_;
}
}
v___jp_6144_:
{
uint64_t v___x_6156_; uint64_t v___x_6157_; uint8_t v___x_6158_; 
v___x_6156_ = lean_uint64_shift_right(v___y_6151_, v___y_6145_);
v___x_6157_ = 0ULL;
v___x_6158_ = lean_uint64_dec_eq(v___x_6156_, v___x_6157_);
if (v___x_6158_ == 0)
{
uint64_t v___x_6159_; 
v___x_6159_ = lean_uint64_add(v___y_6148_, v___y_6145_);
v___y_6130_ = v___y_6146_;
v___y_6131_ = v___y_6147_;
v___y_6132_ = v___y_6149_;
v___y_6133_ = v___y_6150_;
v___y_6134_ = v___y_6152_;
v___y_6135_ = v___y_6155_;
v___y_6136_ = v___y_6154_;
v___y_6137_ = v___y_6153_;
v___y_6138_ = v___x_6159_;
goto v___jp_6129_;
}
else
{
v___y_6130_ = v___y_6146_;
v___y_6131_ = v___y_6147_;
v___y_6132_ = v___y_6149_;
v___y_6133_ = v___y_6150_;
v___y_6134_ = v___y_6152_;
v___y_6135_ = v___y_6155_;
v___y_6136_ = v___y_6154_;
v___y_6137_ = v___y_6153_;
v___y_6138_ = v___y_6148_;
goto v___jp_6129_;
}
}
v___jp_6160_:
{
uint64_t v___x_6170_; uint64_t v___x_6171_; uint64_t v___x_6172_; uint8_t v___x_6173_; 
v___x_6170_ = 2ULL;
v___x_6171_ = lean_uint64_shift_right(v___y_6165_, v___x_6170_);
v___x_6172_ = 0ULL;
v___x_6173_ = lean_uint64_dec_eq(v___x_6171_, v___x_6172_);
if (v___x_6173_ == 0)
{
v___y_6145_ = v___x_6170_;
v___y_6146_ = v___y_6161_;
v___y_6147_ = v___y_6162_;
v___y_6148_ = v___y_6169_;
v___y_6149_ = v___y_6163_;
v___y_6150_ = v___y_6164_;
v___y_6151_ = v___y_6165_;
v___y_6152_ = v___y_6166_;
v___y_6153_ = v___y_6168_;
v___y_6154_ = v___y_6167_;
v___y_6155_ = v___x_6171_;
goto v___jp_6144_;
}
else
{
v___y_6145_ = v___x_6170_;
v___y_6146_ = v___y_6161_;
v___y_6147_ = v___y_6162_;
v___y_6148_ = v___y_6169_;
v___y_6149_ = v___y_6163_;
v___y_6150_ = v___y_6164_;
v___y_6151_ = v___y_6165_;
v___y_6152_ = v___y_6166_;
v___y_6153_ = v___y_6168_;
v___y_6154_ = v___y_6167_;
v___y_6155_ = v___y_6165_;
goto v___jp_6144_;
}
}
v___jp_6174_:
{
uint64_t v___x_6186_; uint64_t v___x_6187_; uint8_t v___x_6188_; 
v___x_6186_ = lean_uint64_shift_right(v___y_6175_, v___y_6182_);
v___x_6187_ = 0ULL;
v___x_6188_ = lean_uint64_dec_eq(v___x_6186_, v___x_6187_);
if (v___x_6188_ == 0)
{
uint64_t v___x_6189_; 
v___x_6189_ = lean_uint64_add(v___y_6176_, v___y_6182_);
v___y_6161_ = v___y_6177_;
v___y_6162_ = v___y_6178_;
v___y_6163_ = v___y_6179_;
v___y_6164_ = v___y_6180_;
v___y_6165_ = v___y_6185_;
v___y_6166_ = v___y_6181_;
v___y_6167_ = v___y_6184_;
v___y_6168_ = v___y_6183_;
v___y_6169_ = v___x_6189_;
goto v___jp_6160_;
}
else
{
v___y_6161_ = v___y_6177_;
v___y_6162_ = v___y_6178_;
v___y_6163_ = v___y_6179_;
v___y_6164_ = v___y_6180_;
v___y_6165_ = v___y_6185_;
v___y_6166_ = v___y_6181_;
v___y_6167_ = v___y_6184_;
v___y_6168_ = v___y_6183_;
v___y_6169_ = v___y_6176_;
goto v___jp_6160_;
}
}
v___jp_6190_:
{
uint64_t v___x_6200_; uint64_t v___x_6201_; uint64_t v___x_6202_; uint8_t v___x_6203_; 
v___x_6200_ = 4ULL;
v___x_6201_ = lean_uint64_shift_right(v___y_6191_, v___x_6200_);
v___x_6202_ = 0ULL;
v___x_6203_ = lean_uint64_dec_eq(v___x_6201_, v___x_6202_);
if (v___x_6203_ == 0)
{
v___y_6175_ = v___y_6191_;
v___y_6176_ = v___y_6199_;
v___y_6177_ = v___y_6192_;
v___y_6178_ = v___y_6193_;
v___y_6179_ = v___y_6194_;
v___y_6180_ = v___y_6195_;
v___y_6181_ = v___y_6196_;
v___y_6182_ = v___x_6200_;
v___y_6183_ = v___y_6198_;
v___y_6184_ = v___y_6197_;
v___y_6185_ = v___x_6201_;
goto v___jp_6174_;
}
else
{
v___y_6175_ = v___y_6191_;
v___y_6176_ = v___y_6199_;
v___y_6177_ = v___y_6192_;
v___y_6178_ = v___y_6193_;
v___y_6179_ = v___y_6194_;
v___y_6180_ = v___y_6195_;
v___y_6181_ = v___y_6196_;
v___y_6182_ = v___x_6200_;
v___y_6183_ = v___y_6198_;
v___y_6184_ = v___y_6197_;
v___y_6185_ = v___y_6191_;
goto v___jp_6174_;
}
}
v___jp_6204_:
{
uint64_t v___x_6216_; uint64_t v___x_6217_; uint8_t v___x_6218_; 
v___x_6216_ = lean_uint64_shift_right(v___y_6212_, v___y_6211_);
v___x_6217_ = 0ULL;
v___x_6218_ = lean_uint64_dec_eq(v___x_6216_, v___x_6217_);
if (v___x_6218_ == 0)
{
uint64_t v___x_6219_; 
v___x_6219_ = lean_uint64_add(v___y_6210_, v___y_6211_);
v___y_6191_ = v___y_6215_;
v___y_6192_ = v___y_6205_;
v___y_6193_ = v___y_6206_;
v___y_6194_ = v___y_6207_;
v___y_6195_ = v___y_6208_;
v___y_6196_ = v___y_6209_;
v___y_6197_ = v___y_6214_;
v___y_6198_ = v___y_6213_;
v___y_6199_ = v___x_6219_;
goto v___jp_6190_;
}
else
{
v___y_6191_ = v___y_6215_;
v___y_6192_ = v___y_6205_;
v___y_6193_ = v___y_6206_;
v___y_6194_ = v___y_6207_;
v___y_6195_ = v___y_6208_;
v___y_6196_ = v___y_6209_;
v___y_6197_ = v___y_6214_;
v___y_6198_ = v___y_6213_;
v___y_6199_ = v___y_6210_;
goto v___jp_6190_;
}
}
v___jp_6220_:
{
uint64_t v___x_6230_; uint64_t v___x_6231_; uint64_t v___x_6232_; uint8_t v___x_6233_; 
v___x_6230_ = 8ULL;
v___x_6231_ = lean_uint64_shift_right(v___y_6226_, v___x_6230_);
v___x_6232_ = 0ULL;
v___x_6233_ = lean_uint64_dec_eq(v___x_6231_, v___x_6232_);
if (v___x_6233_ == 0)
{
v___y_6205_ = v___y_6221_;
v___y_6206_ = v___y_6222_;
v___y_6207_ = v___y_6223_;
v___y_6208_ = v___y_6224_;
v___y_6209_ = v___y_6225_;
v___y_6210_ = v___y_6229_;
v___y_6211_ = v___x_6230_;
v___y_6212_ = v___y_6226_;
v___y_6213_ = v___y_6228_;
v___y_6214_ = v___y_6227_;
v___y_6215_ = v___x_6231_;
goto v___jp_6204_;
}
else
{
v___y_6205_ = v___y_6221_;
v___y_6206_ = v___y_6222_;
v___y_6207_ = v___y_6223_;
v___y_6208_ = v___y_6224_;
v___y_6209_ = v___y_6225_;
v___y_6210_ = v___y_6229_;
v___y_6211_ = v___x_6230_;
v___y_6212_ = v___y_6226_;
v___y_6213_ = v___y_6228_;
v___y_6214_ = v___y_6227_;
v___y_6215_ = v___y_6226_;
goto v___jp_6204_;
}
}
v___jp_6234_:
{
uint64_t v___x_6246_; uint64_t v___x_6247_; uint8_t v___x_6248_; 
v___x_6246_ = lean_uint64_shift_right(v___y_6242_, v___y_6241_);
v___x_6247_ = 0ULL;
v___x_6248_ = lean_uint64_dec_eq(v___x_6246_, v___x_6247_);
if (v___x_6248_ == 0)
{
uint64_t v___x_6249_; 
v___x_6249_ = lean_uint64_add(v___y_6238_, v___y_6241_);
v___y_6221_ = v___y_6235_;
v___y_6222_ = v___y_6236_;
v___y_6223_ = v___y_6237_;
v___y_6224_ = v___y_6239_;
v___y_6225_ = v___y_6240_;
v___y_6226_ = v___y_6245_;
v___y_6227_ = v___y_6244_;
v___y_6228_ = v___y_6243_;
v___y_6229_ = v___x_6249_;
goto v___jp_6220_;
}
else
{
v___y_6221_ = v___y_6235_;
v___y_6222_ = v___y_6236_;
v___y_6223_ = v___y_6237_;
v___y_6224_ = v___y_6239_;
v___y_6225_ = v___y_6240_;
v___y_6226_ = v___y_6245_;
v___y_6227_ = v___y_6244_;
v___y_6228_ = v___y_6243_;
v___y_6229_ = v___y_6238_;
goto v___jp_6220_;
}
}
v___jp_6250_:
{
uint64_t v___x_6260_; uint64_t v___x_6261_; uint64_t v___x_6262_; uint8_t v___x_6263_; 
v___x_6260_ = 16ULL;
v___x_6261_ = lean_uint64_shift_right(v___y_6256_, v___x_6260_);
v___x_6262_ = 0ULL;
v___x_6263_ = lean_uint64_dec_eq(v___x_6261_, v___x_6262_);
if (v___x_6263_ == 0)
{
v___y_6235_ = v___y_6251_;
v___y_6236_ = v___y_6252_;
v___y_6237_ = v___y_6253_;
v___y_6238_ = v___y_6259_;
v___y_6239_ = v___y_6254_;
v___y_6240_ = v___y_6255_;
v___y_6241_ = v___x_6260_;
v___y_6242_ = v___y_6256_;
v___y_6243_ = v___y_6258_;
v___y_6244_ = v___y_6257_;
v___y_6245_ = v___x_6261_;
goto v___jp_6234_;
}
else
{
v___y_6235_ = v___y_6251_;
v___y_6236_ = v___y_6252_;
v___y_6237_ = v___y_6253_;
v___y_6238_ = v___y_6259_;
v___y_6239_ = v___y_6254_;
v___y_6240_ = v___y_6255_;
v___y_6241_ = v___x_6260_;
v___y_6242_ = v___y_6256_;
v___y_6243_ = v___y_6258_;
v___y_6244_ = v___y_6257_;
v___y_6245_ = v___y_6256_;
goto v___jp_6234_;
}
}
v___jp_6264_:
{
uint64_t v___x_6275_; uint64_t v___x_6276_; uint8_t v___x_6277_; 
v___x_6275_ = lean_uint64_shift_right(v___y_6267_, v___y_6265_);
v___x_6276_ = 0ULL;
v___x_6277_ = lean_uint64_dec_eq(v___x_6275_, v___x_6276_);
if (v___x_6277_ == 0)
{
v___y_6251_ = v___y_6266_;
v___y_6252_ = v___y_6268_;
v___y_6253_ = v___y_6269_;
v___y_6254_ = v___y_6270_;
v___y_6255_ = v___y_6271_;
v___y_6256_ = v___y_6274_;
v___y_6257_ = v___y_6273_;
v___y_6258_ = v___y_6272_;
v___y_6259_ = v___y_6265_;
goto v___jp_6250_;
}
else
{
v___y_6251_ = v___y_6266_;
v___y_6252_ = v___y_6268_;
v___y_6253_ = v___y_6269_;
v___y_6254_ = v___y_6270_;
v___y_6255_ = v___y_6271_;
v___y_6256_ = v___y_6274_;
v___y_6257_ = v___y_6273_;
v___y_6258_ = v___y_6272_;
v___y_6259_ = v___x_6276_;
goto v___jp_6250_;
}
}
v___jp_6283_:
{
if (v_matched_6282_ == 0)
{
uint32_t v___x_6285_; 
v___x_6285_ = lp_competition_Submission_R24ExactDotCost_referencePrepared(v_c_6094_);
return v___x_6285_;
}
else
{
uint8_t v_normal_6286_; 
v_normal_6286_ = lean_ctor_get_uint8(v_left_6278_, sizeof(void*)*2 + 8);
if (v_normal_6286_ == 0)
{
uint32_t v___x_6287_; 
v___x_6287_ = lp_competition_Submission_R24ExactDotCost_referencePrepared(v_c_6094_);
return v___x_6287_;
}
else
{
uint8_t v_normal_6288_; 
v_normal_6288_ = lean_ctor_get_uint8(v_right_6279_, sizeof(void*)*2 + 8);
if (v_normal_6288_ == 0)
{
uint32_t v___x_6289_; 
v___x_6289_ = lp_competition_Submission_R24ExactDotCost_referencePrepared(v_c_6094_);
return v___x_6289_;
}
else
{
lean_object* v_data_6290_; lean_object* v_data_6291_; lean_object* v___x_6292_; lean_object* v___x_6293_; uint8_t v___x_6294_; 
v_data_6290_ = lean_ctor_get(v_left_6278_, 1);
v_data_6291_ = lean_ctor_get(v_right_6279_, 1);
v___x_6292_ = lean_array_get_size(v_data_6290_);
v___x_6293_ = lean_unsigned_to_nat(1048576u);
v___x_6294_ = lean_nat_dec_le(v___x_6292_, v___x_6293_);
if (v___x_6294_ == 0)
{
uint32_t v___x_6295_; 
v___x_6295_ = lp_competition_Submission_R24ExactDotCost_referencePrepared(v_c_6094_);
return v___x_6295_;
}
else
{
lean_object* v___x_6296_; lean_object* v___x_6297_; lean_object* v___x_6298_; lean_object* v___x_6299_; lean_object* v___x_6300_; lean_object* v___x_6301_; uint8_t v___x_6302_; 
v___x_6296_ = lean_unsigned_to_nat(48u);
v___x_6297_ = lean_uint32_to_nat(v_maxScale_6281_);
v___x_6298_ = lean_uint32_to_nat(v_minScale_6280_);
v___x_6299_ = lean_nat_sub(v___x_6297_, v___x_6298_);
lean_dec(v___x_6298_);
lean_dec(v___x_6297_);
v___x_6300_ = lean_nat_add(v___x_6296_, v___x_6299_);
lean_dec(v___x_6299_);
v___x_6301_ = lean_unsigned_to_nat(1u);
v___x_6302_ = lean_nat_dec_le(v___x_6292_, v___x_6301_);
if (v___x_6302_ == 0)
{
lean_object* v___x_6303_; uint64_t v___x_6304_; uint64_t v___x_6305_; uint64_t v___x_6306_; uint64_t v___x_6307_; uint8_t v___x_6308_; 
v___x_6303_ = lean_nat_sub(v___x_6292_, v___x_6301_);
v___x_6304_ = lean_uint64_of_nat(v___x_6303_);
lean_dec(v___x_6303_);
v___x_6305_ = 32ULL;
v___x_6306_ = lean_uint64_shift_right(v___x_6304_, v___x_6305_);
v___x_6307_ = 0ULL;
v___x_6308_ = lean_uint64_dec_eq(v___x_6306_, v___x_6307_);
if (v___x_6308_ == 0)
{
v___y_6265_ = v___x_6305_;
v___y_6266_ = v___y_6284_;
v___y_6267_ = v___x_6304_;
v___y_6268_ = v___x_6301_;
v___y_6269_ = v___x_6292_;
v___y_6270_ = v_data_6291_;
v___y_6271_ = v_data_6290_;
v___y_6272_ = v___x_6300_;
v___y_6273_ = v_minScale_6280_;
v___y_6274_ = v___x_6306_;
goto v___jp_6264_;
}
else
{
v___y_6265_ = v___x_6305_;
v___y_6266_ = v___y_6284_;
v___y_6267_ = v___x_6304_;
v___y_6268_ = v___x_6301_;
v___y_6269_ = v___x_6292_;
v___y_6270_ = v_data_6291_;
v___y_6271_ = v_data_6290_;
v___y_6272_ = v___x_6300_;
v___y_6273_ = v_minScale_6280_;
v___y_6274_ = v___x_6304_;
goto v___jp_6264_;
}
}
else
{
lean_object* v___x_6309_; 
v___x_6309_ = lean_unsigned_to_nat(0u);
v___y_6105_ = v___y_6284_;
v___y_6106_ = v___x_6292_;
v___y_6107_ = v_data_6291_;
v___y_6108_ = v_data_6290_;
v___y_6109_ = v_minScale_6280_;
v___y_6110_ = v___x_6300_;
v___y_6111_ = v___x_6309_;
goto v___jp_6104_;
}
}
}
}
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_R24ExactDotTiered_exactPreparedV2___boxed(lean_object* v_c_6425_){
_start:
{
uint32_t v_res_6426_; lean_object* v_r_6427_; 
v_res_6426_ = lp_competition_Submission_R24ExactDotTiered_exactPreparedV2(v_c_6425_);
lean_dec_ref(v_c_6425_);
v_r_6427_ = lean_box_uint32(v_res_6426_);
return v_r_6427_;
}
}
LEAN_EXPORT uint32_t lp_competition_Submission_R24ExactDotTiered_fullv2(lean_object* v_rawA_6428_, lean_object* v_rawB_6429_){
_start:
{
lean_object* v___y_6431_; lean_object* v___y_6432_; lean_object* v___y_6433_; lean_object* v___y_6434_; uint32_t v___y_6435_; uint8_t v___y_6436_; uint8_t v___y_6440_; lean_object* v___y_6441_; lean_object* v___y_6442_; lean_object* v___y_6443_; lean_object* v___y_6444_; lean_object* v___y_6445_; uint32_t v___y_6446_; lean_object* v___y_6447_; uint8_t v___y_6455_; lean_object* v___y_6456_; lean_object* v___y_6457_; lean_object* v___y_6458_; lean_object* v___y_6459_; lean_object* v___y_6460_; lean_object* v___y_6461_; uint32_t v___y_6462_; uint64_t v___y_6463_; uint8_t v___y_6467_; lean_object* v___y_6468_; lean_object* v___y_6469_; uint64_t v___y_6470_; lean_object* v___y_6471_; lean_object* v___y_6472_; lean_object* v___y_6473_; lean_object* v___y_6474_; uint32_t v___y_6475_; uint64_t v___y_6476_; uint64_t v___y_6483_; uint8_t v___y_6484_; lean_object* v___y_6485_; lean_object* v___y_6486_; lean_object* v___y_6487_; lean_object* v___y_6488_; uint64_t v___y_6489_; lean_object* v___y_6490_; lean_object* v___y_6491_; uint64_t v___y_6492_; uint32_t v___y_6493_; uint64_t v___y_6494_; uint8_t v___y_6500_; lean_object* v___y_6501_; lean_object* v___y_6502_; lean_object* v___y_6503_; lean_object* v___y_6504_; lean_object* v___y_6505_; lean_object* v___y_6506_; uint64_t v___y_6507_; uint32_t v___y_6508_; uint64_t v___y_6509_; uint64_t v___y_6515_; uint8_t v___y_6516_; uint64_t v___y_6517_; lean_object* v___y_6518_; lean_object* v___y_6519_; lean_object* v___y_6520_; uint64_t v___y_6521_; lean_object* v___y_6522_; lean_object* v___y_6523_; lean_object* v___y_6524_; uint32_t v___y_6525_; uint64_t v___y_6526_; uint8_t v___y_6532_; lean_object* v___y_6533_; lean_object* v___y_6534_; lean_object* v___y_6535_; lean_object* v___y_6536_; uint64_t v___y_6537_; lean_object* v___y_6538_; lean_object* v___y_6539_; uint32_t v___y_6540_; uint64_t v___y_6541_; uint64_t v___y_6547_; uint8_t v___y_6548_; uint64_t v___y_6549_; lean_object* v___y_6550_; lean_object* v___y_6551_; lean_object* v___y_6552_; lean_object* v___y_6553_; uint64_t v___y_6554_; lean_object* v___y_6555_; lean_object* v___y_6556_; uint32_t v___y_6557_; uint64_t v___y_6558_; uint8_t v___y_6564_; lean_object* v___y_6565_; lean_object* v___y_6566_; lean_object* v___y_6567_; lean_object* v___y_6568_; lean_object* v___y_6569_; lean_object* v___y_6570_; uint64_t v___y_6571_; uint32_t v___y_6572_; uint64_t v___y_6573_; uint64_t v___y_6579_; uint64_t v___y_6580_; uint8_t v___y_6581_; lean_object* v___y_6582_; lean_object* v___y_6583_; lean_object* v___y_6584_; lean_object* v___y_6585_; lean_object* v___y_6586_; lean_object* v___y_6587_; uint64_t v___y_6588_; uint32_t v___y_6589_; uint64_t v___y_6590_; uint8_t v___y_6596_; lean_object* v___y_6597_; lean_object* v___y_6598_; lean_object* v___y_6599_; lean_object* v___y_6600_; lean_object* v___y_6601_; lean_object* v___y_6602_; uint64_t v___y_6603_; uint32_t v___y_6604_; uint64_t v___y_6605_; uint64_t v___y_6611_; uint8_t v___y_6612_; lean_object* v___y_6613_; lean_object* v___y_6614_; lean_object* v___y_6615_; lean_object* v___y_6616_; uint64_t v___y_6617_; lean_object* v___y_6618_; lean_object* v___y_6619_; uint32_t v___y_6620_; uint64_t v___y_6621_; lean_object* v___y_6626_; lean_object* v___y_6627_; lean_object* v___y_6628_; uint8_t v___y_6629_; uint32_t v___y_6630_; uint8_t v___y_6631_; uint8_t v___y_6632_; uint32_t v___y_6633_; uint8_t v___y_6634_; lean_object* v___y_6657_; lean_object* v___y_6658_; lean_object* v___y_6659_; lean_object* v___y_6660_; uint32_t v___y_6661_; uint8_t v___y_6662_; lean_object* v___y_6666_; lean_object* v___y_6667_; lean_object* v___y_6668_; uint8_t v___y_6669_; lean_object* v___y_6670_; uint8_t v___y_6671_; uint8_t v___y_6672_; uint32_t v___y_6673_; uint32_t v___y_6674_; lean_object* v___y_6675_; lean_object* v___y_6676_; lean_object* v___y_6684_; lean_object* v___y_6685_; lean_object* v___y_6686_; lean_object* v___y_6687_; uint8_t v___y_6688_; uint32_t v___y_6689_; uint8_t v___y_6690_; uint8_t v___y_6691_; lean_object* v___y_6692_; lean_object* v___y_6693_; uint32_t v___y_6694_; uint64_t v___y_6695_; lean_object* v___y_6699_; uint64_t v___y_6700_; lean_object* v___y_6701_; lean_object* v___y_6702_; uint8_t v___y_6703_; lean_object* v___y_6704_; uint8_t v___y_6705_; uint8_t v___y_6706_; uint32_t v___y_6707_; lean_object* v___y_6708_; uint32_t v___y_6709_; lean_object* v___y_6710_; uint64_t v___y_6711_; lean_object* v___y_6718_; lean_object* v___y_6719_; lean_object* v___y_6720_; uint64_t v___y_6721_; uint8_t v___y_6722_; uint8_t v___y_6723_; uint32_t v___y_6724_; uint64_t v___y_6725_; uint32_t v___y_6726_; uint64_t v___y_6727_; lean_object* v___y_6728_; uint8_t v___y_6729_; lean_object* v___y_6730_; lean_object* v___y_6731_; uint64_t v___y_6732_; uint64_t v___y_6738_; lean_object* v___y_6739_; lean_object* v___y_6740_; lean_object* v___y_6741_; uint8_t v___y_6742_; lean_object* v___y_6743_; uint32_t v___y_6744_; uint8_t v___y_6745_; uint8_t v___y_6746_; lean_object* v___y_6747_; lean_object* v___y_6748_; uint32_t v___y_6749_; uint64_t v___y_6750_; lean_object* v___y_6756_; uint64_t v___y_6757_; lean_object* v___y_6758_; uint64_t v___y_6759_; lean_object* v___y_6760_; uint32_t v___y_6761_; uint8_t v___y_6762_; uint8_t v___y_6763_; uint64_t v___y_6764_; uint32_t v___y_6765_; lean_object* v___y_6766_; uint8_t v___y_6767_; lean_object* v___y_6768_; lean_object* v___y_6769_; uint64_t v___y_6770_; lean_object* v___y_6776_; lean_object* v___y_6777_; lean_object* v___y_6778_; uint8_t v___y_6779_; lean_object* v___y_6780_; uint8_t v___y_6781_; uint8_t v___y_6782_; uint32_t v___y_6783_; lean_object* v___y_6784_; uint64_t v___y_6785_; lean_object* v___y_6786_; uint32_t v___y_6787_; uint64_t v___y_6788_; lean_object* v___y_6794_; uint64_t v___y_6795_; lean_object* v___y_6796_; uint64_t v___y_6797_; lean_object* v___y_6798_; uint8_t v___y_6799_; uint8_t v___y_6800_; uint32_t v___y_6801_; uint64_t v___y_6802_; uint32_t v___y_6803_; lean_object* v___y_6804_; uint8_t v___y_6805_; lean_object* v___y_6806_; lean_object* v___y_6807_; uint64_t v___y_6808_; lean_object* v___y_6814_; lean_object* v___y_6815_; lean_object* v___y_6816_; uint8_t v___y_6817_; lean_object* v___y_6818_; uint32_t v___y_6819_; uint8_t v___y_6820_; uint8_t v___y_6821_; lean_object* v___y_6822_; uint64_t v___y_6823_; lean_object* v___y_6824_; uint32_t v___y_6825_; uint64_t v___y_6826_; lean_object* v___y_6832_; lean_object* v___y_6833_; lean_object* v___y_6834_; uint32_t v___y_6835_; uint8_t v___y_6836_; uint8_t v___y_6837_; uint32_t v___y_6838_; lean_object* v___y_6839_; uint64_t v___y_6840_; uint8_t v___y_6841_; uint64_t v___y_6842_; uint64_t v___y_6843_; lean_object* v___y_6844_; lean_object* v___y_6845_; uint64_t v___y_6846_; lean_object* v___y_6852_; lean_object* v___y_6853_; lean_object* v___y_6854_; uint64_t v___y_6855_; uint8_t v___y_6856_; lean_object* v___y_6857_; uint8_t v___y_6858_; uint8_t v___y_6859_; uint32_t v___y_6860_; lean_object* v___y_6861_; lean_object* v___y_6862_; uint32_t v___y_6863_; uint64_t v___y_6864_; lean_object* v___y_6870_; uint64_t v___y_6871_; lean_object* v___y_6872_; lean_object* v___y_6873_; uint64_t v___y_6874_; uint8_t v___y_6875_; uint8_t v___y_6876_; uint32_t v___y_6877_; uint32_t v___y_6878_; lean_object* v___y_6879_; uint8_t v___y_6880_; lean_object* v___y_6881_; lean_object* v___y_6882_; uint64_t v___y_6883_; lean_object* v___x_6887_; uint8_t v_hasNonzero_6888_; lean_object* v___x_6889_; uint32_t v___y_6891_; uint32_t v___y_6892_; 
v___x_6887_ = lp_competition_Submission_R24ExactDotCost_prepareOperand(v_rawA_6428_);
v_hasNonzero_6888_ = lean_ctor_get_uint8(v___x_6887_, sizeof(void*)*2 + 10);
v___x_6889_ = lp_competition_Submission_R24ExactDotCost_prepareOperand(v_rawB_6429_);
if (v_hasNonzero_6888_ == 0)
{
goto v___jp_6920_;
}
else
{
uint8_t v_hasNonzero_6922_; 
v_hasNonzero_6922_ = lean_ctor_get_uint8(v___x_6889_, sizeof(void*)*2 + 10);
if (v_hasNonzero_6922_ == 0)
{
goto v___jp_6920_;
}
else
{
uint32_t v_minIdx_6923_; uint32_t v_minIdx_6924_; uint32_t v_maxIdx_6925_; uint32_t v_maxIdx_6926_; uint32_t v___x_6927_; uint32_t v___x_6928_; 
v_minIdx_6923_ = lean_ctor_get_uint32(v___x_6887_, sizeof(void*)*2);
v_minIdx_6924_ = lean_ctor_get_uint32(v___x_6889_, sizeof(void*)*2);
v_maxIdx_6925_ = lean_ctor_get_uint32(v___x_6887_, sizeof(void*)*2 + 4);
v_maxIdx_6926_ = lean_ctor_get_uint32(v___x_6889_, sizeof(void*)*2 + 4);
v___x_6927_ = lean_uint32_add(v_minIdx_6923_, v_minIdx_6924_);
v___x_6928_ = lean_uint32_add(v_maxIdx_6925_, v_maxIdx_6926_);
v___y_6891_ = v___x_6927_;
v___y_6892_ = v___x_6928_;
goto v___jp_6890_;
}
}
v___jp_6430_:
{
uint64_t v___x_6437_; uint32_t v___x_6438_; 
v___x_6437_ = 0ULL;
v___x_6438_ = lp_competition_Submission_R24ExactDotCost_nativeLoop(v___y_6431_, v___y_6433_, v___y_6435_, v___y_6434_, v___y_6436_, v___x_6437_, v___x_6437_, v___x_6437_, v___x_6437_, v___y_6432_);
lean_dec_ref(v___y_6433_);
lean_dec_ref(v___y_6431_);
return v___x_6438_;
}
v___jp_6439_:
{
lean_object* v___x_6448_; lean_object* v___x_6449_; uint8_t v___x_6450_; 
v___x_6448_ = lean_nat_add(v___y_6442_, v___y_6447_);
lean_dec(v___y_6447_);
lean_dec(v___y_6442_);
v___x_6449_ = lean_unsigned_to_nat(128u);
v___x_6450_ = lean_nat_dec_le(v___x_6448_, v___x_6449_);
lean_dec(v___x_6448_);
if (v___x_6450_ == 0)
{
uint32_t v___x_6451_; 
lean_dec(v___y_6445_);
lean_dec_ref(v___y_6444_);
lean_dec_ref(v___y_6441_);
v___x_6451_ = lp_competition_Submission_R24ExactDotCost_referencePrepared(v___y_6443_);
lean_dec_ref(v___y_6443_);
return v___x_6451_;
}
else
{
lean_object* v___x_6452_; uint8_t v___x_6453_; 
lean_dec_ref(v___y_6443_);
v___x_6452_ = lean_unsigned_to_nat(0u);
v___x_6453_ = lean_nat_dec_eq(v___y_6445_, v___x_6452_);
if (v___x_6453_ == 0)
{
v___y_6431_ = v___y_6441_;
v___y_6432_ = v___y_6445_;
v___y_6433_ = v___y_6444_;
v___y_6434_ = v___x_6452_;
v___y_6435_ = v___y_6446_;
v___y_6436_ = v___x_6450_;
goto v___jp_6430_;
}
else
{
v___y_6431_ = v___y_6441_;
v___y_6432_ = v___y_6445_;
v___y_6433_ = v___y_6444_;
v___y_6434_ = v___x_6452_;
v___y_6435_ = v___y_6446_;
v___y_6436_ = v___y_6440_;
goto v___jp_6430_;
}
}
}
v___jp_6454_:
{
lean_object* v___x_6464_; lean_object* v___x_6465_; 
v___x_6464_ = lean_uint64_to_nat(v___y_6463_);
v___x_6465_ = lean_nat_add(v___x_6464_, v___y_6456_);
lean_dec(v___x_6464_);
v___y_6440_ = v___y_6455_;
v___y_6441_ = v___y_6457_;
v___y_6442_ = v___y_6458_;
v___y_6443_ = v___y_6459_;
v___y_6444_ = v___y_6461_;
v___y_6445_ = v___y_6460_;
v___y_6446_ = v___y_6462_;
v___y_6447_ = v___x_6465_;
goto v___jp_6439_;
}
v___jp_6466_:
{
uint64_t v___x_6477_; uint64_t v___x_6478_; uint64_t v___x_6479_; uint8_t v___x_6480_; 
v___x_6477_ = 1ULL;
v___x_6478_ = lean_uint64_shift_right(v___y_6470_, v___x_6477_);
v___x_6479_ = 0ULL;
v___x_6480_ = lean_uint64_dec_eq(v___x_6478_, v___x_6479_);
if (v___x_6480_ == 0)
{
uint64_t v___x_6481_; 
v___x_6481_ = lean_uint64_add(v___y_6476_, v___x_6477_);
v___y_6455_ = v___y_6467_;
v___y_6456_ = v___y_6468_;
v___y_6457_ = v___y_6469_;
v___y_6458_ = v___y_6471_;
v___y_6459_ = v___y_6472_;
v___y_6460_ = v___y_6474_;
v___y_6461_ = v___y_6473_;
v___y_6462_ = v___y_6475_;
v___y_6463_ = v___x_6481_;
goto v___jp_6454_;
}
else
{
v___y_6455_ = v___y_6467_;
v___y_6456_ = v___y_6468_;
v___y_6457_ = v___y_6469_;
v___y_6458_ = v___y_6471_;
v___y_6459_ = v___y_6472_;
v___y_6460_ = v___y_6474_;
v___y_6461_ = v___y_6473_;
v___y_6462_ = v___y_6475_;
v___y_6463_ = v___y_6476_;
goto v___jp_6454_;
}
}
v___jp_6482_:
{
uint64_t v___x_6495_; uint64_t v___x_6496_; uint8_t v___x_6497_; 
v___x_6495_ = lean_uint64_shift_right(v___y_6489_, v___y_6483_);
v___x_6496_ = 0ULL;
v___x_6497_ = lean_uint64_dec_eq(v___x_6495_, v___x_6496_);
if (v___x_6497_ == 0)
{
uint64_t v___x_6498_; 
v___x_6498_ = lean_uint64_add(v___y_6492_, v___y_6483_);
v___y_6467_ = v___y_6484_;
v___y_6468_ = v___y_6485_;
v___y_6469_ = v___y_6486_;
v___y_6470_ = v___y_6494_;
v___y_6471_ = v___y_6487_;
v___y_6472_ = v___y_6488_;
v___y_6473_ = v___y_6491_;
v___y_6474_ = v___y_6490_;
v___y_6475_ = v___y_6493_;
v___y_6476_ = v___x_6498_;
goto v___jp_6466_;
}
else
{
v___y_6467_ = v___y_6484_;
v___y_6468_ = v___y_6485_;
v___y_6469_ = v___y_6486_;
v___y_6470_ = v___y_6494_;
v___y_6471_ = v___y_6487_;
v___y_6472_ = v___y_6488_;
v___y_6473_ = v___y_6491_;
v___y_6474_ = v___y_6490_;
v___y_6475_ = v___y_6493_;
v___y_6476_ = v___y_6492_;
goto v___jp_6466_;
}
}
v___jp_6499_:
{
uint64_t v___x_6510_; uint64_t v___x_6511_; uint64_t v___x_6512_; uint8_t v___x_6513_; 
v___x_6510_ = 2ULL;
v___x_6511_ = lean_uint64_shift_right(v___y_6507_, v___x_6510_);
v___x_6512_ = 0ULL;
v___x_6513_ = lean_uint64_dec_eq(v___x_6511_, v___x_6512_);
if (v___x_6513_ == 0)
{
v___y_6483_ = v___x_6510_;
v___y_6484_ = v___y_6500_;
v___y_6485_ = v___y_6501_;
v___y_6486_ = v___y_6502_;
v___y_6487_ = v___y_6503_;
v___y_6488_ = v___y_6504_;
v___y_6489_ = v___y_6507_;
v___y_6490_ = v___y_6506_;
v___y_6491_ = v___y_6505_;
v___y_6492_ = v___y_6509_;
v___y_6493_ = v___y_6508_;
v___y_6494_ = v___x_6511_;
goto v___jp_6482_;
}
else
{
v___y_6483_ = v___x_6510_;
v___y_6484_ = v___y_6500_;
v___y_6485_ = v___y_6501_;
v___y_6486_ = v___y_6502_;
v___y_6487_ = v___y_6503_;
v___y_6488_ = v___y_6504_;
v___y_6489_ = v___y_6507_;
v___y_6490_ = v___y_6506_;
v___y_6491_ = v___y_6505_;
v___y_6492_ = v___y_6509_;
v___y_6493_ = v___y_6508_;
v___y_6494_ = v___y_6507_;
goto v___jp_6482_;
}
}
v___jp_6514_:
{
uint64_t v___x_6527_; uint64_t v___x_6528_; uint8_t v___x_6529_; 
v___x_6527_ = lean_uint64_shift_right(v___y_6521_, v___y_6517_);
v___x_6528_ = 0ULL;
v___x_6529_ = lean_uint64_dec_eq(v___x_6527_, v___x_6528_);
if (v___x_6529_ == 0)
{
uint64_t v___x_6530_; 
v___x_6530_ = lean_uint64_add(v___y_6515_, v___y_6517_);
v___y_6500_ = v___y_6516_;
v___y_6501_ = v___y_6518_;
v___y_6502_ = v___y_6519_;
v___y_6503_ = v___y_6520_;
v___y_6504_ = v___y_6522_;
v___y_6505_ = v___y_6524_;
v___y_6506_ = v___y_6523_;
v___y_6507_ = v___y_6526_;
v___y_6508_ = v___y_6525_;
v___y_6509_ = v___x_6530_;
goto v___jp_6499_;
}
else
{
v___y_6500_ = v___y_6516_;
v___y_6501_ = v___y_6518_;
v___y_6502_ = v___y_6519_;
v___y_6503_ = v___y_6520_;
v___y_6504_ = v___y_6522_;
v___y_6505_ = v___y_6524_;
v___y_6506_ = v___y_6523_;
v___y_6507_ = v___y_6526_;
v___y_6508_ = v___y_6525_;
v___y_6509_ = v___y_6515_;
goto v___jp_6499_;
}
}
v___jp_6531_:
{
uint64_t v___x_6542_; uint64_t v___x_6543_; uint64_t v___x_6544_; uint8_t v___x_6545_; 
v___x_6542_ = 4ULL;
v___x_6543_ = lean_uint64_shift_right(v___y_6537_, v___x_6542_);
v___x_6544_ = 0ULL;
v___x_6545_ = lean_uint64_dec_eq(v___x_6543_, v___x_6544_);
if (v___x_6545_ == 0)
{
v___y_6515_ = v___y_6541_;
v___y_6516_ = v___y_6532_;
v___y_6517_ = v___x_6542_;
v___y_6518_ = v___y_6533_;
v___y_6519_ = v___y_6534_;
v___y_6520_ = v___y_6535_;
v___y_6521_ = v___y_6537_;
v___y_6522_ = v___y_6536_;
v___y_6523_ = v___y_6539_;
v___y_6524_ = v___y_6538_;
v___y_6525_ = v___y_6540_;
v___y_6526_ = v___x_6543_;
goto v___jp_6514_;
}
else
{
v___y_6515_ = v___y_6541_;
v___y_6516_ = v___y_6532_;
v___y_6517_ = v___x_6542_;
v___y_6518_ = v___y_6533_;
v___y_6519_ = v___y_6534_;
v___y_6520_ = v___y_6535_;
v___y_6521_ = v___y_6537_;
v___y_6522_ = v___y_6536_;
v___y_6523_ = v___y_6539_;
v___y_6524_ = v___y_6538_;
v___y_6525_ = v___y_6540_;
v___y_6526_ = v___y_6537_;
goto v___jp_6514_;
}
}
v___jp_6546_:
{
uint64_t v___x_6559_; uint64_t v___x_6560_; uint8_t v___x_6561_; 
v___x_6559_ = lean_uint64_shift_right(v___y_6554_, v___y_6549_);
v___x_6560_ = 0ULL;
v___x_6561_ = lean_uint64_dec_eq(v___x_6559_, v___x_6560_);
if (v___x_6561_ == 0)
{
uint64_t v___x_6562_; 
v___x_6562_ = lean_uint64_add(v___y_6547_, v___y_6549_);
v___y_6532_ = v___y_6548_;
v___y_6533_ = v___y_6550_;
v___y_6534_ = v___y_6551_;
v___y_6535_ = v___y_6552_;
v___y_6536_ = v___y_6553_;
v___y_6537_ = v___y_6558_;
v___y_6538_ = v___y_6556_;
v___y_6539_ = v___y_6555_;
v___y_6540_ = v___y_6557_;
v___y_6541_ = v___x_6562_;
goto v___jp_6531_;
}
else
{
v___y_6532_ = v___y_6548_;
v___y_6533_ = v___y_6550_;
v___y_6534_ = v___y_6551_;
v___y_6535_ = v___y_6552_;
v___y_6536_ = v___y_6553_;
v___y_6537_ = v___y_6558_;
v___y_6538_ = v___y_6556_;
v___y_6539_ = v___y_6555_;
v___y_6540_ = v___y_6557_;
v___y_6541_ = v___y_6547_;
goto v___jp_6531_;
}
}
v___jp_6563_:
{
uint64_t v___x_6574_; uint64_t v___x_6575_; uint64_t v___x_6576_; uint8_t v___x_6577_; 
v___x_6574_ = 8ULL;
v___x_6575_ = lean_uint64_shift_right(v___y_6571_, v___x_6574_);
v___x_6576_ = 0ULL;
v___x_6577_ = lean_uint64_dec_eq(v___x_6575_, v___x_6576_);
if (v___x_6577_ == 0)
{
v___y_6547_ = v___y_6573_;
v___y_6548_ = v___y_6564_;
v___y_6549_ = v___x_6574_;
v___y_6550_ = v___y_6565_;
v___y_6551_ = v___y_6566_;
v___y_6552_ = v___y_6567_;
v___y_6553_ = v___y_6568_;
v___y_6554_ = v___y_6571_;
v___y_6555_ = v___y_6570_;
v___y_6556_ = v___y_6569_;
v___y_6557_ = v___y_6572_;
v___y_6558_ = v___x_6575_;
goto v___jp_6546_;
}
else
{
v___y_6547_ = v___y_6573_;
v___y_6548_ = v___y_6564_;
v___y_6549_ = v___x_6574_;
v___y_6550_ = v___y_6565_;
v___y_6551_ = v___y_6566_;
v___y_6552_ = v___y_6567_;
v___y_6553_ = v___y_6568_;
v___y_6554_ = v___y_6571_;
v___y_6555_ = v___y_6570_;
v___y_6556_ = v___y_6569_;
v___y_6557_ = v___y_6572_;
v___y_6558_ = v___y_6571_;
goto v___jp_6546_;
}
}
v___jp_6578_:
{
uint64_t v___x_6591_; uint64_t v___x_6592_; uint8_t v___x_6593_; 
v___x_6591_ = lean_uint64_shift_right(v___y_6588_, v___y_6580_);
v___x_6592_ = 0ULL;
v___x_6593_ = lean_uint64_dec_eq(v___x_6591_, v___x_6592_);
if (v___x_6593_ == 0)
{
uint64_t v___x_6594_; 
v___x_6594_ = lean_uint64_add(v___y_6579_, v___y_6580_);
v___y_6564_ = v___y_6581_;
v___y_6565_ = v___y_6582_;
v___y_6566_ = v___y_6583_;
v___y_6567_ = v___y_6584_;
v___y_6568_ = v___y_6585_;
v___y_6569_ = v___y_6587_;
v___y_6570_ = v___y_6586_;
v___y_6571_ = v___y_6590_;
v___y_6572_ = v___y_6589_;
v___y_6573_ = v___x_6594_;
goto v___jp_6563_;
}
else
{
v___y_6564_ = v___y_6581_;
v___y_6565_ = v___y_6582_;
v___y_6566_ = v___y_6583_;
v___y_6567_ = v___y_6584_;
v___y_6568_ = v___y_6585_;
v___y_6569_ = v___y_6587_;
v___y_6570_ = v___y_6586_;
v___y_6571_ = v___y_6590_;
v___y_6572_ = v___y_6589_;
v___y_6573_ = v___y_6579_;
goto v___jp_6563_;
}
}
v___jp_6595_:
{
uint64_t v___x_6606_; uint64_t v___x_6607_; uint64_t v___x_6608_; uint8_t v___x_6609_; 
v___x_6606_ = 16ULL;
v___x_6607_ = lean_uint64_shift_right(v___y_6603_, v___x_6606_);
v___x_6608_ = 0ULL;
v___x_6609_ = lean_uint64_dec_eq(v___x_6607_, v___x_6608_);
if (v___x_6609_ == 0)
{
v___y_6579_ = v___y_6605_;
v___y_6580_ = v___x_6606_;
v___y_6581_ = v___y_6596_;
v___y_6582_ = v___y_6597_;
v___y_6583_ = v___y_6598_;
v___y_6584_ = v___y_6599_;
v___y_6585_ = v___y_6600_;
v___y_6586_ = v___y_6602_;
v___y_6587_ = v___y_6601_;
v___y_6588_ = v___y_6603_;
v___y_6589_ = v___y_6604_;
v___y_6590_ = v___x_6607_;
goto v___jp_6578_;
}
else
{
v___y_6579_ = v___y_6605_;
v___y_6580_ = v___x_6606_;
v___y_6581_ = v___y_6596_;
v___y_6582_ = v___y_6597_;
v___y_6583_ = v___y_6598_;
v___y_6584_ = v___y_6599_;
v___y_6585_ = v___y_6600_;
v___y_6586_ = v___y_6602_;
v___y_6587_ = v___y_6601_;
v___y_6588_ = v___y_6603_;
v___y_6589_ = v___y_6604_;
v___y_6590_ = v___y_6603_;
goto v___jp_6578_;
}
}
v___jp_6610_:
{
uint64_t v___x_6622_; uint64_t v___x_6623_; uint8_t v___x_6624_; 
v___x_6622_ = lean_uint64_shift_right(v___y_6617_, v___y_6611_);
v___x_6623_ = 0ULL;
v___x_6624_ = lean_uint64_dec_eq(v___x_6622_, v___x_6623_);
if (v___x_6624_ == 0)
{
v___y_6596_ = v___y_6612_;
v___y_6597_ = v___y_6613_;
v___y_6598_ = v___y_6614_;
v___y_6599_ = v___y_6615_;
v___y_6600_ = v___y_6616_;
v___y_6601_ = v___y_6619_;
v___y_6602_ = v___y_6618_;
v___y_6603_ = v___y_6621_;
v___y_6604_ = v___y_6620_;
v___y_6605_ = v___y_6611_;
goto v___jp_6595_;
}
else
{
v___y_6596_ = v___y_6612_;
v___y_6597_ = v___y_6613_;
v___y_6598_ = v___y_6614_;
v___y_6599_ = v___y_6615_;
v___y_6600_ = v___y_6616_;
v___y_6601_ = v___y_6619_;
v___y_6602_ = v___y_6618_;
v___y_6603_ = v___y_6621_;
v___y_6604_ = v___y_6620_;
v___y_6605_ = v___x_6623_;
goto v___jp_6595_;
}
}
v___jp_6625_:
{
if (v___y_6632_ == 0)
{
uint32_t v___x_6635_; 
lean_dec_ref(v___y_6628_);
lean_dec_ref(v___y_6626_);
v___x_6635_ = lp_competition_Submission_R24ExactDotCost_referencePrepared(v___y_6627_);
lean_dec_ref(v___y_6627_);
return v___x_6635_;
}
else
{
if (v___y_6631_ == 0)
{
uint32_t v___x_6636_; 
lean_dec_ref(v___y_6628_);
lean_dec_ref(v___y_6626_);
v___x_6636_ = lp_competition_Submission_R24ExactDotCost_referencePrepared(v___y_6627_);
lean_dec_ref(v___y_6627_);
return v___x_6636_;
}
else
{
if (v___y_6629_ == 0)
{
uint32_t v___x_6637_; 
lean_dec_ref(v___y_6628_);
lean_dec_ref(v___y_6626_);
v___x_6637_ = lp_competition_Submission_R24ExactDotCost_referencePrepared(v___y_6627_);
lean_dec_ref(v___y_6627_);
return v___x_6637_;
}
else
{
lean_object* v___x_6638_; lean_object* v___x_6639_; uint8_t v___x_6640_; 
v___x_6638_ = lean_array_get_size(v___y_6626_);
v___x_6639_ = lean_unsigned_to_nat(1048576u);
v___x_6640_ = lean_nat_dec_le(v___x_6638_, v___x_6639_);
if (v___x_6640_ == 0)
{
uint32_t v___x_6641_; 
lean_dec_ref(v___y_6628_);
lean_dec_ref(v___y_6626_);
v___x_6641_ = lp_competition_Submission_R24ExactDotCost_referencePrepared(v___y_6627_);
lean_dec_ref(v___y_6627_);
return v___x_6641_;
}
else
{
lean_object* v___x_6642_; lean_object* v___x_6643_; lean_object* v___x_6644_; lean_object* v___x_6645_; lean_object* v___x_6646_; lean_object* v___x_6647_; uint8_t v___x_6648_; 
v___x_6642_ = lean_unsigned_to_nat(48u);
v___x_6643_ = lean_uint32_to_nat(v___y_6630_);
v___x_6644_ = lean_uint32_to_nat(v___y_6633_);
v___x_6645_ = lean_nat_sub(v___x_6643_, v___x_6644_);
lean_dec(v___x_6644_);
lean_dec(v___x_6643_);
v___x_6646_ = lean_nat_add(v___x_6642_, v___x_6645_);
lean_dec(v___x_6645_);
v___x_6647_ = lean_unsigned_to_nat(1u);
v___x_6648_ = lean_nat_dec_le(v___x_6638_, v___x_6647_);
if (v___x_6648_ == 0)
{
lean_object* v___x_6649_; uint64_t v___x_6650_; uint64_t v___x_6651_; uint64_t v___x_6652_; uint64_t v___x_6653_; uint8_t v___x_6654_; 
v___x_6649_ = lean_nat_sub(v___x_6638_, v___x_6647_);
v___x_6650_ = lean_uint64_of_nat(v___x_6649_);
lean_dec(v___x_6649_);
v___x_6651_ = 32ULL;
v___x_6652_ = lean_uint64_shift_right(v___x_6650_, v___x_6651_);
v___x_6653_ = 0ULL;
v___x_6654_ = lean_uint64_dec_eq(v___x_6652_, v___x_6653_);
if (v___x_6654_ == 0)
{
v___y_6611_ = v___x_6651_;
v___y_6612_ = v___y_6634_;
v___y_6613_ = v___x_6647_;
v___y_6614_ = v___y_6626_;
v___y_6615_ = v___x_6646_;
v___y_6616_ = v___y_6627_;
v___y_6617_ = v___x_6650_;
v___y_6618_ = v___x_6638_;
v___y_6619_ = v___y_6628_;
v___y_6620_ = v___y_6633_;
v___y_6621_ = v___x_6652_;
goto v___jp_6610_;
}
else
{
v___y_6611_ = v___x_6651_;
v___y_6612_ = v___y_6634_;
v___y_6613_ = v___x_6647_;
v___y_6614_ = v___y_6626_;
v___y_6615_ = v___x_6646_;
v___y_6616_ = v___y_6627_;
v___y_6617_ = v___x_6650_;
v___y_6618_ = v___x_6638_;
v___y_6619_ = v___y_6628_;
v___y_6620_ = v___y_6633_;
v___y_6621_ = v___x_6650_;
goto v___jp_6610_;
}
}
else
{
lean_object* v___x_6655_; 
v___x_6655_ = lean_unsigned_to_nat(0u);
v___y_6440_ = v___y_6634_;
v___y_6441_ = v___y_6626_;
v___y_6442_ = v___x_6646_;
v___y_6443_ = v___y_6627_;
v___y_6444_ = v___y_6628_;
v___y_6445_ = v___x_6638_;
v___y_6446_ = v___y_6633_;
v___y_6447_ = v___x_6655_;
goto v___jp_6439_;
}
}
}
}
}
}
v___jp_6656_:
{
uint64_t v___x_6663_; uint32_t v___x_6664_; 
v___x_6663_ = 0ULL;
v___x_6664_ = lp_competition_Submission_R24ExactDotTiered_native64Loop(v___y_6658_, v___y_6659_, v___y_6661_, v___y_6660_, v___y_6662_, v___x_6663_, v___y_6657_);
lean_dec_ref(v___y_6659_);
lean_dec_ref(v___y_6658_);
return v___x_6664_;
}
v___jp_6665_:
{
lean_object* v___x_6677_; lean_object* v___x_6678_; uint8_t v___x_6679_; 
v___x_6677_ = lean_nat_add(v___y_6675_, v___y_6676_);
lean_dec(v___y_6676_);
lean_dec(v___y_6675_);
v___x_6678_ = lean_unsigned_to_nat(62u);
v___x_6679_ = lean_nat_dec_le(v___x_6677_, v___x_6678_);
lean_dec(v___x_6677_);
if (v___x_6679_ == 0)
{
lean_dec(v___y_6666_);
v___y_6626_ = v___y_6667_;
v___y_6627_ = v___y_6668_;
v___y_6628_ = v___y_6670_;
v___y_6629_ = v___y_6669_;
v___y_6630_ = v___y_6673_;
v___y_6631_ = v___y_6672_;
v___y_6632_ = v___y_6671_;
v___y_6633_ = v___y_6674_;
v___y_6634_ = v___x_6679_;
goto v___jp_6625_;
}
else
{
lean_object* v___x_6680_; uint8_t v___x_6681_; 
lean_dec_ref(v___y_6668_);
v___x_6680_ = lean_unsigned_to_nat(0u);
v___x_6681_ = lean_nat_dec_eq(v___y_6666_, v___x_6680_);
if (v___x_6681_ == 0)
{
v___y_6657_ = v___y_6666_;
v___y_6658_ = v___y_6667_;
v___y_6659_ = v___y_6670_;
v___y_6660_ = v___x_6680_;
v___y_6661_ = v___y_6674_;
v___y_6662_ = v___x_6679_;
goto v___jp_6656_;
}
else
{
uint8_t v___x_6682_; 
v___x_6682_ = 0;
v___y_6657_ = v___y_6666_;
v___y_6658_ = v___y_6667_;
v___y_6659_ = v___y_6670_;
v___y_6660_ = v___x_6680_;
v___y_6661_ = v___y_6674_;
v___y_6662_ = v___x_6682_;
goto v___jp_6656_;
}
}
}
v___jp_6683_:
{
lean_object* v___x_6696_; lean_object* v___x_6697_; 
v___x_6696_ = lean_uint64_to_nat(v___y_6695_);
v___x_6697_ = lean_nat_add(v___x_6696_, v___y_6692_);
lean_dec(v___x_6696_);
v___y_6666_ = v___y_6684_;
v___y_6667_ = v___y_6685_;
v___y_6668_ = v___y_6686_;
v___y_6669_ = v___y_6688_;
v___y_6670_ = v___y_6687_;
v___y_6671_ = v___y_6691_;
v___y_6672_ = v___y_6690_;
v___y_6673_ = v___y_6689_;
v___y_6674_ = v___y_6694_;
v___y_6675_ = v___y_6693_;
v___y_6676_ = v___x_6697_;
goto v___jp_6665_;
}
v___jp_6698_:
{
uint64_t v___x_6712_; uint64_t v___x_6713_; uint64_t v___x_6714_; uint8_t v___x_6715_; 
v___x_6712_ = 1ULL;
v___x_6713_ = lean_uint64_shift_right(v___y_6700_, v___x_6712_);
v___x_6714_ = 0ULL;
v___x_6715_ = lean_uint64_dec_eq(v___x_6713_, v___x_6714_);
if (v___x_6715_ == 0)
{
uint64_t v___x_6716_; 
v___x_6716_ = lean_uint64_add(v___y_6711_, v___x_6712_);
v___y_6684_ = v___y_6699_;
v___y_6685_ = v___y_6701_;
v___y_6686_ = v___y_6702_;
v___y_6687_ = v___y_6704_;
v___y_6688_ = v___y_6703_;
v___y_6689_ = v___y_6707_;
v___y_6690_ = v___y_6706_;
v___y_6691_ = v___y_6705_;
v___y_6692_ = v___y_6708_;
v___y_6693_ = v___y_6710_;
v___y_6694_ = v___y_6709_;
v___y_6695_ = v___x_6716_;
goto v___jp_6683_;
}
else
{
v___y_6684_ = v___y_6699_;
v___y_6685_ = v___y_6701_;
v___y_6686_ = v___y_6702_;
v___y_6687_ = v___y_6704_;
v___y_6688_ = v___y_6703_;
v___y_6689_ = v___y_6707_;
v___y_6690_ = v___y_6706_;
v___y_6691_ = v___y_6705_;
v___y_6692_ = v___y_6708_;
v___y_6693_ = v___y_6710_;
v___y_6694_ = v___y_6709_;
v___y_6695_ = v___y_6711_;
goto v___jp_6683_;
}
}
v___jp_6717_:
{
uint64_t v___x_6733_; uint64_t v___x_6734_; uint8_t v___x_6735_; 
v___x_6733_ = lean_uint64_shift_right(v___y_6727_, v___y_6721_);
v___x_6734_ = 0ULL;
v___x_6735_ = lean_uint64_dec_eq(v___x_6733_, v___x_6734_);
if (v___x_6735_ == 0)
{
uint64_t v___x_6736_; 
v___x_6736_ = lean_uint64_add(v___y_6725_, v___y_6721_);
v___y_6699_ = v___y_6718_;
v___y_6700_ = v___y_6732_;
v___y_6701_ = v___y_6719_;
v___y_6702_ = v___y_6728_;
v___y_6703_ = v___y_6729_;
v___y_6704_ = v___y_6720_;
v___y_6705_ = v___y_6722_;
v___y_6706_ = v___y_6723_;
v___y_6707_ = v___y_6724_;
v___y_6708_ = v___y_6730_;
v___y_6709_ = v___y_6726_;
v___y_6710_ = v___y_6731_;
v___y_6711_ = v___x_6736_;
goto v___jp_6698_;
}
else
{
v___y_6699_ = v___y_6718_;
v___y_6700_ = v___y_6732_;
v___y_6701_ = v___y_6719_;
v___y_6702_ = v___y_6728_;
v___y_6703_ = v___y_6729_;
v___y_6704_ = v___y_6720_;
v___y_6705_ = v___y_6722_;
v___y_6706_ = v___y_6723_;
v___y_6707_ = v___y_6724_;
v___y_6708_ = v___y_6730_;
v___y_6709_ = v___y_6726_;
v___y_6710_ = v___y_6731_;
v___y_6711_ = v___y_6725_;
goto v___jp_6698_;
}
}
v___jp_6737_:
{
uint64_t v___x_6751_; uint64_t v___x_6752_; uint64_t v___x_6753_; uint8_t v___x_6754_; 
v___x_6751_ = 2ULL;
v___x_6752_ = lean_uint64_shift_right(v___y_6738_, v___x_6751_);
v___x_6753_ = 0ULL;
v___x_6754_ = lean_uint64_dec_eq(v___x_6752_, v___x_6753_);
if (v___x_6754_ == 0)
{
v___y_6718_ = v___y_6739_;
v___y_6719_ = v___y_6740_;
v___y_6720_ = v___y_6743_;
v___y_6721_ = v___x_6751_;
v___y_6722_ = v___y_6746_;
v___y_6723_ = v___y_6745_;
v___y_6724_ = v___y_6744_;
v___y_6725_ = v___y_6750_;
v___y_6726_ = v___y_6749_;
v___y_6727_ = v___y_6738_;
v___y_6728_ = v___y_6741_;
v___y_6729_ = v___y_6742_;
v___y_6730_ = v___y_6747_;
v___y_6731_ = v___y_6748_;
v___y_6732_ = v___x_6752_;
goto v___jp_6717_;
}
else
{
v___y_6718_ = v___y_6739_;
v___y_6719_ = v___y_6740_;
v___y_6720_ = v___y_6743_;
v___y_6721_ = v___x_6751_;
v___y_6722_ = v___y_6746_;
v___y_6723_ = v___y_6745_;
v___y_6724_ = v___y_6744_;
v___y_6725_ = v___y_6750_;
v___y_6726_ = v___y_6749_;
v___y_6727_ = v___y_6738_;
v___y_6728_ = v___y_6741_;
v___y_6729_ = v___y_6742_;
v___y_6730_ = v___y_6747_;
v___y_6731_ = v___y_6748_;
v___y_6732_ = v___y_6738_;
goto v___jp_6717_;
}
}
v___jp_6755_:
{
uint64_t v___x_6771_; uint64_t v___x_6772_; uint8_t v___x_6773_; 
v___x_6771_ = lean_uint64_shift_right(v___y_6764_, v___y_6759_);
v___x_6772_ = 0ULL;
v___x_6773_ = lean_uint64_dec_eq(v___x_6771_, v___x_6772_);
if (v___x_6773_ == 0)
{
uint64_t v___x_6774_; 
v___x_6774_ = lean_uint64_add(v___y_6757_, v___y_6759_);
v___y_6738_ = v___y_6770_;
v___y_6739_ = v___y_6756_;
v___y_6740_ = v___y_6758_;
v___y_6741_ = v___y_6766_;
v___y_6742_ = v___y_6767_;
v___y_6743_ = v___y_6760_;
v___y_6744_ = v___y_6761_;
v___y_6745_ = v___y_6762_;
v___y_6746_ = v___y_6763_;
v___y_6747_ = v___y_6768_;
v___y_6748_ = v___y_6769_;
v___y_6749_ = v___y_6765_;
v___y_6750_ = v___x_6774_;
goto v___jp_6737_;
}
else
{
v___y_6738_ = v___y_6770_;
v___y_6739_ = v___y_6756_;
v___y_6740_ = v___y_6758_;
v___y_6741_ = v___y_6766_;
v___y_6742_ = v___y_6767_;
v___y_6743_ = v___y_6760_;
v___y_6744_ = v___y_6761_;
v___y_6745_ = v___y_6762_;
v___y_6746_ = v___y_6763_;
v___y_6747_ = v___y_6768_;
v___y_6748_ = v___y_6769_;
v___y_6749_ = v___y_6765_;
v___y_6750_ = v___y_6757_;
goto v___jp_6737_;
}
}
v___jp_6775_:
{
uint64_t v___x_6789_; uint64_t v___x_6790_; uint64_t v___x_6791_; uint8_t v___x_6792_; 
v___x_6789_ = 4ULL;
v___x_6790_ = lean_uint64_shift_right(v___y_6785_, v___x_6789_);
v___x_6791_ = 0ULL;
v___x_6792_ = lean_uint64_dec_eq(v___x_6790_, v___x_6791_);
if (v___x_6792_ == 0)
{
v___y_6756_ = v___y_6776_;
v___y_6757_ = v___y_6788_;
v___y_6758_ = v___y_6777_;
v___y_6759_ = v___x_6789_;
v___y_6760_ = v___y_6780_;
v___y_6761_ = v___y_6783_;
v___y_6762_ = v___y_6782_;
v___y_6763_ = v___y_6781_;
v___y_6764_ = v___y_6785_;
v___y_6765_ = v___y_6787_;
v___y_6766_ = v___y_6778_;
v___y_6767_ = v___y_6779_;
v___y_6768_ = v___y_6784_;
v___y_6769_ = v___y_6786_;
v___y_6770_ = v___x_6790_;
goto v___jp_6755_;
}
else
{
v___y_6756_ = v___y_6776_;
v___y_6757_ = v___y_6788_;
v___y_6758_ = v___y_6777_;
v___y_6759_ = v___x_6789_;
v___y_6760_ = v___y_6780_;
v___y_6761_ = v___y_6783_;
v___y_6762_ = v___y_6782_;
v___y_6763_ = v___y_6781_;
v___y_6764_ = v___y_6785_;
v___y_6765_ = v___y_6787_;
v___y_6766_ = v___y_6778_;
v___y_6767_ = v___y_6779_;
v___y_6768_ = v___y_6784_;
v___y_6769_ = v___y_6786_;
v___y_6770_ = v___y_6785_;
goto v___jp_6755_;
}
}
v___jp_6793_:
{
uint64_t v___x_6809_; uint64_t v___x_6810_; uint8_t v___x_6811_; 
v___x_6809_ = lean_uint64_shift_right(v___y_6802_, v___y_6795_);
v___x_6810_ = 0ULL;
v___x_6811_ = lean_uint64_dec_eq(v___x_6809_, v___x_6810_);
if (v___x_6811_ == 0)
{
uint64_t v___x_6812_; 
v___x_6812_ = lean_uint64_add(v___y_6797_, v___y_6795_);
v___y_6776_ = v___y_6794_;
v___y_6777_ = v___y_6796_;
v___y_6778_ = v___y_6804_;
v___y_6779_ = v___y_6805_;
v___y_6780_ = v___y_6798_;
v___y_6781_ = v___y_6799_;
v___y_6782_ = v___y_6800_;
v___y_6783_ = v___y_6801_;
v___y_6784_ = v___y_6806_;
v___y_6785_ = v___y_6808_;
v___y_6786_ = v___y_6807_;
v___y_6787_ = v___y_6803_;
v___y_6788_ = v___x_6812_;
goto v___jp_6775_;
}
else
{
v___y_6776_ = v___y_6794_;
v___y_6777_ = v___y_6796_;
v___y_6778_ = v___y_6804_;
v___y_6779_ = v___y_6805_;
v___y_6780_ = v___y_6798_;
v___y_6781_ = v___y_6799_;
v___y_6782_ = v___y_6800_;
v___y_6783_ = v___y_6801_;
v___y_6784_ = v___y_6806_;
v___y_6785_ = v___y_6808_;
v___y_6786_ = v___y_6807_;
v___y_6787_ = v___y_6803_;
v___y_6788_ = v___y_6797_;
goto v___jp_6775_;
}
}
v___jp_6813_:
{
uint64_t v___x_6827_; uint64_t v___x_6828_; uint64_t v___x_6829_; uint8_t v___x_6830_; 
v___x_6827_ = 8ULL;
v___x_6828_ = lean_uint64_shift_right(v___y_6823_, v___x_6827_);
v___x_6829_ = 0ULL;
v___x_6830_ = lean_uint64_dec_eq(v___x_6828_, v___x_6829_);
if (v___x_6830_ == 0)
{
v___y_6794_ = v___y_6814_;
v___y_6795_ = v___x_6827_;
v___y_6796_ = v___y_6815_;
v___y_6797_ = v___y_6826_;
v___y_6798_ = v___y_6818_;
v___y_6799_ = v___y_6821_;
v___y_6800_ = v___y_6820_;
v___y_6801_ = v___y_6819_;
v___y_6802_ = v___y_6823_;
v___y_6803_ = v___y_6825_;
v___y_6804_ = v___y_6816_;
v___y_6805_ = v___y_6817_;
v___y_6806_ = v___y_6822_;
v___y_6807_ = v___y_6824_;
v___y_6808_ = v___x_6828_;
goto v___jp_6793_;
}
else
{
v___y_6794_ = v___y_6814_;
v___y_6795_ = v___x_6827_;
v___y_6796_ = v___y_6815_;
v___y_6797_ = v___y_6826_;
v___y_6798_ = v___y_6818_;
v___y_6799_ = v___y_6821_;
v___y_6800_ = v___y_6820_;
v___y_6801_ = v___y_6819_;
v___y_6802_ = v___y_6823_;
v___y_6803_ = v___y_6825_;
v___y_6804_ = v___y_6816_;
v___y_6805_ = v___y_6817_;
v___y_6806_ = v___y_6822_;
v___y_6807_ = v___y_6824_;
v___y_6808_ = v___y_6823_;
goto v___jp_6793_;
}
}
v___jp_6831_:
{
uint64_t v___x_6847_; uint64_t v___x_6848_; uint8_t v___x_6849_; 
v___x_6847_ = lean_uint64_shift_right(v___y_6840_, v___y_6843_);
v___x_6848_ = 0ULL;
v___x_6849_ = lean_uint64_dec_eq(v___x_6847_, v___x_6848_);
if (v___x_6849_ == 0)
{
uint64_t v___x_6850_; 
v___x_6850_ = lean_uint64_add(v___y_6842_, v___y_6843_);
v___y_6814_ = v___y_6832_;
v___y_6815_ = v___y_6833_;
v___y_6816_ = v___y_6839_;
v___y_6817_ = v___y_6841_;
v___y_6818_ = v___y_6834_;
v___y_6819_ = v___y_6835_;
v___y_6820_ = v___y_6836_;
v___y_6821_ = v___y_6837_;
v___y_6822_ = v___y_6844_;
v___y_6823_ = v___y_6846_;
v___y_6824_ = v___y_6845_;
v___y_6825_ = v___y_6838_;
v___y_6826_ = v___x_6850_;
goto v___jp_6813_;
}
else
{
v___y_6814_ = v___y_6832_;
v___y_6815_ = v___y_6833_;
v___y_6816_ = v___y_6839_;
v___y_6817_ = v___y_6841_;
v___y_6818_ = v___y_6834_;
v___y_6819_ = v___y_6835_;
v___y_6820_ = v___y_6836_;
v___y_6821_ = v___y_6837_;
v___y_6822_ = v___y_6844_;
v___y_6823_ = v___y_6846_;
v___y_6824_ = v___y_6845_;
v___y_6825_ = v___y_6838_;
v___y_6826_ = v___y_6842_;
goto v___jp_6813_;
}
}
v___jp_6851_:
{
uint64_t v___x_6865_; uint64_t v___x_6866_; uint64_t v___x_6867_; uint8_t v___x_6868_; 
v___x_6865_ = 16ULL;
v___x_6866_ = lean_uint64_shift_right(v___y_6855_, v___x_6865_);
v___x_6867_ = 0ULL;
v___x_6868_ = lean_uint64_dec_eq(v___x_6866_, v___x_6867_);
if (v___x_6868_ == 0)
{
v___y_6832_ = v___y_6852_;
v___y_6833_ = v___y_6853_;
v___y_6834_ = v___y_6857_;
v___y_6835_ = v___y_6860_;
v___y_6836_ = v___y_6859_;
v___y_6837_ = v___y_6858_;
v___y_6838_ = v___y_6863_;
v___y_6839_ = v___y_6854_;
v___y_6840_ = v___y_6855_;
v___y_6841_ = v___y_6856_;
v___y_6842_ = v___y_6864_;
v___y_6843_ = v___x_6865_;
v___y_6844_ = v___y_6861_;
v___y_6845_ = v___y_6862_;
v___y_6846_ = v___x_6866_;
goto v___jp_6831_;
}
else
{
v___y_6832_ = v___y_6852_;
v___y_6833_ = v___y_6853_;
v___y_6834_ = v___y_6857_;
v___y_6835_ = v___y_6860_;
v___y_6836_ = v___y_6859_;
v___y_6837_ = v___y_6858_;
v___y_6838_ = v___y_6863_;
v___y_6839_ = v___y_6854_;
v___y_6840_ = v___y_6855_;
v___y_6841_ = v___y_6856_;
v___y_6842_ = v___y_6864_;
v___y_6843_ = v___x_6865_;
v___y_6844_ = v___y_6861_;
v___y_6845_ = v___y_6862_;
v___y_6846_ = v___y_6855_;
goto v___jp_6831_;
}
}
v___jp_6869_:
{
uint64_t v___x_6884_; uint64_t v___x_6885_; uint8_t v___x_6886_; 
v___x_6884_ = lean_uint64_shift_right(v___y_6871_, v___y_6874_);
v___x_6885_ = 0ULL;
v___x_6886_ = lean_uint64_dec_eq(v___x_6884_, v___x_6885_);
if (v___x_6886_ == 0)
{
v___y_6852_ = v___y_6870_;
v___y_6853_ = v___y_6872_;
v___y_6854_ = v___y_6879_;
v___y_6855_ = v___y_6883_;
v___y_6856_ = v___y_6880_;
v___y_6857_ = v___y_6873_;
v___y_6858_ = v___y_6875_;
v___y_6859_ = v___y_6876_;
v___y_6860_ = v___y_6877_;
v___y_6861_ = v___y_6881_;
v___y_6862_ = v___y_6882_;
v___y_6863_ = v___y_6878_;
v___y_6864_ = v___y_6874_;
goto v___jp_6851_;
}
else
{
v___y_6852_ = v___y_6870_;
v___y_6853_ = v___y_6872_;
v___y_6854_ = v___y_6879_;
v___y_6855_ = v___y_6883_;
v___y_6856_ = v___y_6880_;
v___y_6857_ = v___y_6873_;
v___y_6858_ = v___y_6875_;
v___y_6859_ = v___y_6876_;
v___y_6860_ = v___y_6877_;
v___y_6861_ = v___y_6881_;
v___y_6862_ = v___y_6882_;
v___y_6863_ = v___y_6878_;
v___y_6864_ = v___x_6885_;
goto v___jp_6851_;
}
}
v___jp_6890_:
{
lean_object* v_raw_6893_; lean_object* v_data_6894_; uint8_t v_normal_6895_; lean_object* v_raw_6896_; lean_object* v_data_6897_; uint8_t v_normal_6898_; lean_object* v___x_6899_; lean_object* v___x_6900_; uint8_t v___x_6901_; lean_object* v___x_6902_; 
v_raw_6893_ = lean_ctor_get(v___x_6887_, 0);
lean_inc_ref(v_raw_6893_);
v_data_6894_ = lean_ctor_get(v___x_6887_, 1);
lean_inc_ref(v_data_6894_);
v_normal_6895_ = lean_ctor_get_uint8(v___x_6887_, sizeof(void*)*2 + 8);
v_raw_6896_ = lean_ctor_get(v___x_6889_, 0);
lean_inc_ref(v_raw_6896_);
v_data_6897_ = lean_ctor_get(v___x_6889_, 1);
lean_inc_ref(v_data_6897_);
v_normal_6898_ = lean_ctor_get_uint8(v___x_6889_, sizeof(void*)*2 + 8);
v___x_6899_ = lean_array_get_size(v_raw_6893_);
lean_dec_ref(v_raw_6893_);
v___x_6900_ = lean_array_get_size(v_raw_6896_);
lean_dec_ref(v_raw_6896_);
v___x_6901_ = lean_nat_dec_eq(v___x_6899_, v___x_6900_);
v___x_6902_ = lean_alloc_ctor(0, 2, 9);
lean_ctor_set(v___x_6902_, 0, v___x_6887_);
lean_ctor_set(v___x_6902_, 1, v___x_6889_);
lean_ctor_set_uint32(v___x_6902_, sizeof(void*)*2, v___y_6891_);
lean_ctor_set_uint32(v___x_6902_, sizeof(void*)*2 + 4, v___y_6892_);
lean_ctor_set_uint8(v___x_6902_, sizeof(void*)*2 + 8, v___x_6901_);
if (v___x_6901_ == 0)
{
v___y_6626_ = v_data_6894_;
v___y_6627_ = v___x_6902_;
v___y_6628_ = v_data_6897_;
v___y_6629_ = v_normal_6898_;
v___y_6630_ = v___y_6892_;
v___y_6631_ = v_normal_6895_;
v___y_6632_ = v___x_6901_;
v___y_6633_ = v___y_6891_;
v___y_6634_ = v___x_6901_;
goto v___jp_6625_;
}
else
{
if (v_normal_6895_ == 0)
{
v___y_6626_ = v_data_6894_;
v___y_6627_ = v___x_6902_;
v___y_6628_ = v_data_6897_;
v___y_6629_ = v_normal_6898_;
v___y_6630_ = v___y_6892_;
v___y_6631_ = v_normal_6895_;
v___y_6632_ = v___x_6901_;
v___y_6633_ = v___y_6891_;
v___y_6634_ = v_normal_6895_;
goto v___jp_6625_;
}
else
{
if (v_normal_6898_ == 0)
{
v___y_6626_ = v_data_6894_;
v___y_6627_ = v___x_6902_;
v___y_6628_ = v_data_6897_;
v___y_6629_ = v_normal_6898_;
v___y_6630_ = v___y_6892_;
v___y_6631_ = v_normal_6895_;
v___y_6632_ = v___x_6901_;
v___y_6633_ = v___y_6891_;
v___y_6634_ = v_normal_6898_;
goto v___jp_6625_;
}
else
{
lean_object* v___x_6903_; lean_object* v___x_6904_; uint8_t v___x_6905_; 
v___x_6903_ = lean_array_get_size(v_data_6894_);
v___x_6904_ = lean_unsigned_to_nat(1048576u);
v___x_6905_ = lean_nat_dec_le(v___x_6903_, v___x_6904_);
if (v___x_6905_ == 0)
{
v___y_6626_ = v_data_6894_;
v___y_6627_ = v___x_6902_;
v___y_6628_ = v_data_6897_;
v___y_6629_ = v_normal_6898_;
v___y_6630_ = v___y_6892_;
v___y_6631_ = v_normal_6895_;
v___y_6632_ = v___x_6901_;
v___y_6633_ = v___y_6891_;
v___y_6634_ = v___x_6905_;
goto v___jp_6625_;
}
else
{
lean_object* v___x_6906_; lean_object* v___x_6907_; lean_object* v___x_6908_; lean_object* v___x_6909_; lean_object* v___x_6910_; lean_object* v___x_6911_; uint8_t v___x_6912_; 
v___x_6906_ = lean_unsigned_to_nat(48u);
v___x_6907_ = lean_uint32_to_nat(v___y_6892_);
v___x_6908_ = lean_uint32_to_nat(v___y_6891_);
v___x_6909_ = lean_nat_sub(v___x_6907_, v___x_6908_);
lean_dec(v___x_6908_);
lean_dec(v___x_6907_);
v___x_6910_ = lean_nat_add(v___x_6906_, v___x_6909_);
lean_dec(v___x_6909_);
v___x_6911_ = lean_unsigned_to_nat(1u);
v___x_6912_ = lean_nat_dec_le(v___x_6903_, v___x_6911_);
if (v___x_6912_ == 0)
{
lean_object* v___x_6913_; uint64_t v___x_6914_; uint64_t v___x_6915_; uint64_t v___x_6916_; uint64_t v___x_6917_; uint8_t v___x_6918_; 
v___x_6913_ = lean_nat_sub(v___x_6903_, v___x_6911_);
v___x_6914_ = lean_uint64_of_nat(v___x_6913_);
lean_dec(v___x_6913_);
v___x_6915_ = 32ULL;
v___x_6916_ = lean_uint64_shift_right(v___x_6914_, v___x_6915_);
v___x_6917_ = 0ULL;
v___x_6918_ = lean_uint64_dec_eq(v___x_6916_, v___x_6917_);
if (v___x_6918_ == 0)
{
v___y_6870_ = v___x_6903_;
v___y_6871_ = v___x_6914_;
v___y_6872_ = v_data_6894_;
v___y_6873_ = v_data_6897_;
v___y_6874_ = v___x_6915_;
v___y_6875_ = v___x_6901_;
v___y_6876_ = v_normal_6895_;
v___y_6877_ = v___y_6892_;
v___y_6878_ = v___y_6891_;
v___y_6879_ = v___x_6902_;
v___y_6880_ = v_normal_6898_;
v___y_6881_ = v___x_6911_;
v___y_6882_ = v___x_6910_;
v___y_6883_ = v___x_6916_;
goto v___jp_6869_;
}
else
{
v___y_6870_ = v___x_6903_;
v___y_6871_ = v___x_6914_;
v___y_6872_ = v_data_6894_;
v___y_6873_ = v_data_6897_;
v___y_6874_ = v___x_6915_;
v___y_6875_ = v___x_6901_;
v___y_6876_ = v_normal_6895_;
v___y_6877_ = v___y_6892_;
v___y_6878_ = v___y_6891_;
v___y_6879_ = v___x_6902_;
v___y_6880_ = v_normal_6898_;
v___y_6881_ = v___x_6911_;
v___y_6882_ = v___x_6910_;
v___y_6883_ = v___x_6914_;
goto v___jp_6869_;
}
}
else
{
lean_object* v___x_6919_; 
v___x_6919_ = lean_unsigned_to_nat(0u);
v___y_6666_ = v___x_6903_;
v___y_6667_ = v_data_6894_;
v___y_6668_ = v___x_6902_;
v___y_6669_ = v_normal_6898_;
v___y_6670_ = v_data_6897_;
v___y_6671_ = v___x_6901_;
v___y_6672_ = v_normal_6895_;
v___y_6673_ = v___y_6892_;
v___y_6674_ = v___y_6891_;
v___y_6675_ = v___x_6910_;
v___y_6676_ = v___x_6919_;
goto v___jp_6665_;
}
}
}
}
}
}
v___jp_6920_:
{
uint32_t v___x_6921_; 
v___x_6921_ = 0;
v___y_6891_ = v___x_6921_;
v___y_6892_ = v___x_6921_;
goto v___jp_6890_;
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_R24ExactDotTiered_fullv2___boxed(lean_object* v_rawA_6929_, lean_object* v_rawB_6930_){
_start:
{
uint32_t v_res_6931_; lean_object* v_r_6932_; 
v_res_6931_ = lp_competition_Submission_R24ExactDotTiered_fullv2(v_rawA_6929_, v_rawB_6930_);
v_r_6932_ = lean_box_uint32(v_res_6931_);
return v_r_6932_;
}
}
LEAN_EXPORT uint32_t lp_competition_Submission_R24ExactDotTiered_prepared2v2(lean_object* v_left_6933_, lean_object* v_right_6934_){
_start:
{
lean_object* v___y_6936_; lean_object* v___y_6937_; lean_object* v___y_6938_; lean_object* v___y_6939_; uint32_t v___y_6940_; uint8_t v___y_6941_; lean_object* v___y_6945_; lean_object* v___y_6946_; lean_object* v___y_6947_; lean_object* v___y_6948_; lean_object* v___y_6949_; uint32_t v___y_6950_; uint8_t v___y_6951_; lean_object* v___y_6952_; lean_object* v___y_6960_; lean_object* v___y_6961_; lean_object* v___y_6962_; lean_object* v___y_6963_; lean_object* v___y_6964_; uint32_t v___y_6965_; uint8_t v___y_6966_; lean_object* v___y_6967_; uint64_t v___y_6968_; lean_object* v___y_6972_; lean_object* v___y_6973_; lean_object* v___y_6974_; uint64_t v___y_6975_; lean_object* v___y_6976_; lean_object* v___y_6977_; uint32_t v___y_6978_; uint8_t v___y_6979_; lean_object* v___y_6980_; uint64_t v___y_6981_; lean_object* v___y_6988_; uint64_t v___y_6989_; uint64_t v___y_6990_; lean_object* v___y_6991_; lean_object* v___y_6992_; lean_object* v___y_6993_; lean_object* v___y_6994_; uint64_t v___y_6995_; uint32_t v___y_6996_; uint8_t v___y_6997_; lean_object* v___y_6998_; uint64_t v___y_6999_; lean_object* v___y_7005_; uint64_t v___y_7006_; lean_object* v___y_7007_; lean_object* v___y_7008_; lean_object* v___y_7009_; lean_object* v___y_7010_; uint32_t v___y_7011_; uint8_t v___y_7012_; lean_object* v___y_7013_; uint64_t v___y_7014_; uint64_t v___y_7020_; uint64_t v___y_7021_; lean_object* v___y_7022_; lean_object* v___y_7023_; lean_object* v___y_7024_; lean_object* v___y_7025_; lean_object* v___y_7026_; uint32_t v___y_7027_; uint64_t v___y_7028_; uint8_t v___y_7029_; lean_object* v___y_7030_; uint64_t v___y_7031_; lean_object* v___y_7037_; lean_object* v___y_7038_; lean_object* v___y_7039_; lean_object* v___y_7040_; lean_object* v___y_7041_; uint32_t v___y_7042_; uint64_t v___y_7043_; uint8_t v___y_7044_; lean_object* v___y_7045_; uint64_t v___y_7046_; uint64_t v___y_7052_; uint64_t v___y_7053_; lean_object* v___y_7054_; lean_object* v___y_7055_; lean_object* v___y_7056_; lean_object* v___y_7057_; lean_object* v___y_7058_; uint32_t v___y_7059_; uint64_t v___y_7060_; uint8_t v___y_7061_; lean_object* v___y_7062_; uint64_t v___y_7063_; uint64_t v___y_7069_; lean_object* v___y_7070_; lean_object* v___y_7071_; lean_object* v___y_7072_; lean_object* v___y_7073_; lean_object* v___y_7074_; uint32_t v___y_7075_; uint8_t v___y_7076_; lean_object* v___y_7077_; uint64_t v___y_7078_; uint64_t v___y_7084_; lean_object* v___y_7085_; uint64_t v___y_7086_; lean_object* v___y_7087_; lean_object* v___y_7088_; lean_object* v___y_7089_; lean_object* v___y_7090_; uint32_t v___y_7091_; uint8_t v___y_7092_; uint64_t v___y_7093_; lean_object* v___y_7094_; uint64_t v___y_7095_; lean_object* v___y_7101_; uint64_t v___y_7102_; lean_object* v___y_7103_; lean_object* v___y_7104_; lean_object* v___y_7105_; lean_object* v___y_7106_; uint32_t v___y_7107_; uint8_t v___y_7108_; lean_object* v___y_7109_; uint64_t v___y_7110_; lean_object* v___y_7116_; uint64_t v___y_7117_; uint64_t v___y_7118_; lean_object* v___y_7119_; lean_object* v___y_7120_; lean_object* v___y_7121_; lean_object* v___y_7122_; uint32_t v___y_7123_; uint8_t v___y_7124_; lean_object* v___y_7125_; uint64_t v___y_7126_; uint8_t v___y_7131_; uint8_t v___y_7132_; lean_object* v___y_7133_; uint8_t v___y_7134_; uint32_t v___y_7135_; lean_object* v___y_7136_; lean_object* v___y_7137_; uint32_t v___y_7138_; uint8_t v___y_7139_; lean_object* v___y_7162_; lean_object* v___y_7163_; lean_object* v___y_7164_; lean_object* v___y_7165_; uint32_t v___y_7166_; uint8_t v___y_7167_; uint8_t v___y_7171_; uint8_t v___y_7172_; lean_object* v___y_7173_; lean_object* v___y_7174_; uint8_t v___y_7175_; lean_object* v___y_7176_; lean_object* v___y_7177_; uint32_t v___y_7178_; lean_object* v___y_7179_; uint32_t v___y_7180_; lean_object* v___y_7181_; uint8_t v___y_7189_; uint8_t v___y_7190_; lean_object* v___y_7191_; lean_object* v___y_7192_; lean_object* v___y_7193_; uint8_t v___y_7194_; uint32_t v___y_7195_; lean_object* v___y_7196_; lean_object* v___y_7197_; uint32_t v___y_7198_; lean_object* v___y_7199_; uint64_t v___y_7200_; uint8_t v___y_7204_; uint8_t v___y_7205_; lean_object* v___y_7206_; lean_object* v___y_7207_; uint8_t v___y_7208_; lean_object* v___y_7209_; lean_object* v___y_7210_; uint32_t v___y_7211_; lean_object* v___y_7212_; uint64_t v___y_7213_; uint32_t v___y_7214_; lean_object* v___y_7215_; uint64_t v___y_7216_; uint8_t v___y_7223_; uint8_t v___y_7224_; lean_object* v___y_7225_; lean_object* v___y_7226_; uint64_t v___y_7227_; uint64_t v___y_7228_; uint8_t v___y_7229_; lean_object* v___y_7230_; lean_object* v___y_7231_; uint32_t v___y_7232_; lean_object* v___y_7233_; uint32_t v___y_7234_; lean_object* v___y_7235_; uint64_t v___y_7236_; uint64_t v___y_7237_; uint8_t v___y_7243_; uint8_t v___y_7244_; lean_object* v___y_7245_; lean_object* v___y_7246_; uint64_t v___y_7247_; lean_object* v___y_7248_; uint8_t v___y_7249_; uint32_t v___y_7250_; lean_object* v___y_7251_; lean_object* v___y_7252_; uint32_t v___y_7253_; lean_object* v___y_7254_; uint64_t v___y_7255_; uint8_t v___y_7261_; uint8_t v___y_7262_; lean_object* v___y_7263_; lean_object* v___y_7264_; lean_object* v___y_7265_; uint8_t v___y_7266_; lean_object* v___y_7267_; uint32_t v___y_7268_; uint64_t v___y_7269_; lean_object* v___y_7270_; uint64_t v___y_7271_; uint32_t v___y_7272_; lean_object* v___y_7273_; uint64_t v___y_7274_; uint64_t v___y_7275_; uint8_t v___y_7281_; uint8_t v___y_7282_; lean_object* v___y_7283_; lean_object* v___y_7284_; uint8_t v___y_7285_; lean_object* v___y_7286_; uint32_t v___y_7287_; lean_object* v___y_7288_; lean_object* v___y_7289_; uint64_t v___y_7290_; uint32_t v___y_7291_; lean_object* v___y_7292_; uint64_t v___y_7293_; uint8_t v___y_7299_; uint8_t v___y_7300_; lean_object* v___y_7301_; lean_object* v___y_7302_; uint64_t v___y_7303_; uint8_t v___y_7304_; lean_object* v___y_7305_; lean_object* v___y_7306_; uint64_t v___y_7307_; uint32_t v___y_7308_; lean_object* v___y_7309_; uint64_t v___y_7310_; uint32_t v___y_7311_; lean_object* v___y_7312_; uint64_t v___y_7313_; uint8_t v___y_7319_; uint8_t v___y_7320_; uint64_t v___y_7321_; lean_object* v___y_7322_; lean_object* v___y_7323_; lean_object* v___y_7324_; uint8_t v___y_7325_; uint32_t v___y_7326_; lean_object* v___y_7327_; lean_object* v___y_7328_; uint32_t v___y_7329_; lean_object* v___y_7330_; uint64_t v___y_7331_; uint8_t v___y_7337_; uint8_t v___y_7338_; lean_object* v___y_7339_; lean_object* v___y_7340_; lean_object* v___y_7341_; uint8_t v___y_7342_; lean_object* v___y_7343_; uint64_t v___y_7344_; uint32_t v___y_7345_; lean_object* v___y_7346_; uint64_t v___y_7347_; uint64_t v___y_7348_; uint32_t v___y_7349_; lean_object* v___y_7350_; uint64_t v___y_7351_; uint8_t v___y_7357_; uint8_t v___y_7358_; uint64_t v___y_7359_; lean_object* v___y_7360_; lean_object* v___y_7361_; uint8_t v___y_7362_; lean_object* v___y_7363_; uint32_t v___y_7364_; lean_object* v___y_7365_; lean_object* v___y_7366_; uint32_t v___y_7367_; lean_object* v___y_7368_; uint64_t v___y_7369_; uint8_t v___y_7375_; uint8_t v___y_7376_; lean_object* v___y_7377_; lean_object* v___y_7378_; uint8_t v___y_7379_; lean_object* v___y_7380_; lean_object* v___y_7381_; uint32_t v___y_7382_; lean_object* v___y_7383_; uint64_t v___y_7384_; uint64_t v___y_7385_; uint32_t v___y_7386_; lean_object* v___y_7387_; uint64_t v___y_7388_; lean_object* v_raw_7392_; lean_object* v_data_7393_; uint32_t v_minIdx_7394_; uint32_t v_maxIdx_7395_; uint8_t v_normal_7396_; uint8_t v_hasNonzero_7397_; uint32_t v___y_7399_; uint32_t v___y_7400_; 
v_raw_7392_ = lean_ctor_get(v_left_6933_, 0);
v_data_7393_ = lean_ctor_get(v_left_6933_, 1);
lean_inc_ref(v_data_7393_);
v_minIdx_7394_ = lean_ctor_get_uint32(v_left_6933_, sizeof(void*)*2);
v_maxIdx_7395_ = lean_ctor_get_uint32(v_left_6933_, sizeof(void*)*2 + 4);
v_normal_7396_ = lean_ctor_get_uint8(v_left_6933_, sizeof(void*)*2 + 8);
v_hasNonzero_7397_ = lean_ctor_get_uint8(v_left_6933_, sizeof(void*)*2 + 10);
if (v_hasNonzero_7397_ == 0)
{
goto v___jp_7425_;
}
else
{
uint8_t v_hasNonzero_7427_; 
v_hasNonzero_7427_ = lean_ctor_get_uint8(v_right_6934_, sizeof(void*)*2 + 10);
if (v_hasNonzero_7427_ == 0)
{
goto v___jp_7425_;
}
else
{
uint32_t v_minIdx_7428_; uint32_t v_maxIdx_7429_; uint32_t v___x_7430_; uint32_t v___x_7431_; 
v_minIdx_7428_ = lean_ctor_get_uint32(v_right_6934_, sizeof(void*)*2);
v_maxIdx_7429_ = lean_ctor_get_uint32(v_right_6934_, sizeof(void*)*2 + 4);
v___x_7430_ = lean_uint32_add(v_minIdx_7394_, v_minIdx_7428_);
v___x_7431_ = lean_uint32_add(v_maxIdx_7395_, v_maxIdx_7429_);
v___y_7399_ = v___x_7430_;
v___y_7400_ = v___x_7431_;
goto v___jp_7398_;
}
}
v___jp_6935_:
{
uint64_t v___x_6942_; uint32_t v___x_6943_; 
v___x_6942_ = 0ULL;
v___x_6943_ = lp_competition_Submission_R24ExactDotCost_nativeLoop(v___y_6936_, v___y_6938_, v___y_6940_, v___y_6937_, v___y_6941_, v___x_6942_, v___x_6942_, v___x_6942_, v___x_6942_, v___y_6939_);
lean_dec_ref(v___y_6938_);
lean_dec_ref(v___y_6936_);
return v___x_6943_;
}
v___jp_6944_:
{
lean_object* v___x_6953_; lean_object* v___x_6954_; uint8_t v___x_6955_; 
v___x_6953_ = lean_nat_add(v___y_6947_, v___y_6952_);
lean_dec(v___y_6952_);
lean_dec(v___y_6947_);
v___x_6954_ = lean_unsigned_to_nat(128u);
v___x_6955_ = lean_nat_dec_le(v___x_6953_, v___x_6954_);
lean_dec(v___x_6953_);
if (v___x_6955_ == 0)
{
uint32_t v___x_6956_; 
lean_dec(v___y_6949_);
lean_dec_ref(v___y_6948_);
lean_dec_ref(v___y_6946_);
v___x_6956_ = lp_competition_Submission_R24ExactDotCost_referencePrepared(v___y_6945_);
lean_dec_ref(v___y_6945_);
return v___x_6956_;
}
else
{
lean_object* v___x_6957_; uint8_t v___x_6958_; 
lean_dec_ref(v___y_6945_);
v___x_6957_ = lean_unsigned_to_nat(0u);
v___x_6958_ = lean_nat_dec_eq(v___y_6949_, v___x_6957_);
if (v___x_6958_ == 0)
{
v___y_6936_ = v___y_6946_;
v___y_6937_ = v___x_6957_;
v___y_6938_ = v___y_6948_;
v___y_6939_ = v___y_6949_;
v___y_6940_ = v___y_6950_;
v___y_6941_ = v___x_6955_;
goto v___jp_6935_;
}
else
{
v___y_6936_ = v___y_6946_;
v___y_6937_ = v___x_6957_;
v___y_6938_ = v___y_6948_;
v___y_6939_ = v___y_6949_;
v___y_6940_ = v___y_6950_;
v___y_6941_ = v___y_6951_;
goto v___jp_6935_;
}
}
}
v___jp_6959_:
{
lean_object* v___x_6969_; lean_object* v___x_6970_; 
v___x_6969_ = lean_uint64_to_nat(v___y_6968_);
v___x_6970_ = lean_nat_add(v___x_6969_, v___y_6967_);
lean_dec(v___x_6969_);
v___y_6945_ = v___y_6960_;
v___y_6946_ = v___y_6962_;
v___y_6947_ = v___y_6961_;
v___y_6948_ = v___y_6963_;
v___y_6949_ = v___y_6964_;
v___y_6950_ = v___y_6965_;
v___y_6951_ = v___y_6966_;
v___y_6952_ = v___x_6970_;
goto v___jp_6944_;
}
v___jp_6971_:
{
uint64_t v___x_6982_; uint64_t v___x_6983_; uint64_t v___x_6984_; uint8_t v___x_6985_; 
v___x_6982_ = 1ULL;
v___x_6983_ = lean_uint64_shift_right(v___y_6975_, v___x_6982_);
v___x_6984_ = 0ULL;
v___x_6985_ = lean_uint64_dec_eq(v___x_6983_, v___x_6984_);
if (v___x_6985_ == 0)
{
uint64_t v___x_6986_; 
v___x_6986_ = lean_uint64_add(v___y_6981_, v___x_6982_);
v___y_6960_ = v___y_6972_;
v___y_6961_ = v___y_6974_;
v___y_6962_ = v___y_6973_;
v___y_6963_ = v___y_6976_;
v___y_6964_ = v___y_6977_;
v___y_6965_ = v___y_6978_;
v___y_6966_ = v___y_6979_;
v___y_6967_ = v___y_6980_;
v___y_6968_ = v___x_6986_;
goto v___jp_6959_;
}
else
{
v___y_6960_ = v___y_6972_;
v___y_6961_ = v___y_6974_;
v___y_6962_ = v___y_6973_;
v___y_6963_ = v___y_6976_;
v___y_6964_ = v___y_6977_;
v___y_6965_ = v___y_6978_;
v___y_6966_ = v___y_6979_;
v___y_6967_ = v___y_6980_;
v___y_6968_ = v___y_6981_;
goto v___jp_6959_;
}
}
v___jp_6987_:
{
uint64_t v___x_7000_; uint64_t v___x_7001_; uint8_t v___x_7002_; 
v___x_7000_ = lean_uint64_shift_right(v___y_6990_, v___y_6995_);
v___x_7001_ = 0ULL;
v___x_7002_ = lean_uint64_dec_eq(v___x_7000_, v___x_7001_);
if (v___x_7002_ == 0)
{
uint64_t v___x_7003_; 
v___x_7003_ = lean_uint64_add(v___y_6989_, v___y_6995_);
v___y_6972_ = v___y_6988_;
v___y_6973_ = v___y_6992_;
v___y_6974_ = v___y_6991_;
v___y_6975_ = v___y_6999_;
v___y_6976_ = v___y_6993_;
v___y_6977_ = v___y_6994_;
v___y_6978_ = v___y_6996_;
v___y_6979_ = v___y_6997_;
v___y_6980_ = v___y_6998_;
v___y_6981_ = v___x_7003_;
goto v___jp_6971_;
}
else
{
v___y_6972_ = v___y_6988_;
v___y_6973_ = v___y_6992_;
v___y_6974_ = v___y_6991_;
v___y_6975_ = v___y_6999_;
v___y_6976_ = v___y_6993_;
v___y_6977_ = v___y_6994_;
v___y_6978_ = v___y_6996_;
v___y_6979_ = v___y_6997_;
v___y_6980_ = v___y_6998_;
v___y_6981_ = v___y_6989_;
goto v___jp_6971_;
}
}
v___jp_7004_:
{
uint64_t v___x_7015_; uint64_t v___x_7016_; uint64_t v___x_7017_; uint8_t v___x_7018_; 
v___x_7015_ = 2ULL;
v___x_7016_ = lean_uint64_shift_right(v___y_7006_, v___x_7015_);
v___x_7017_ = 0ULL;
v___x_7018_ = lean_uint64_dec_eq(v___x_7016_, v___x_7017_);
if (v___x_7018_ == 0)
{
v___y_6988_ = v___y_7005_;
v___y_6989_ = v___y_7014_;
v___y_6990_ = v___y_7006_;
v___y_6991_ = v___y_7008_;
v___y_6992_ = v___y_7007_;
v___y_6993_ = v___y_7009_;
v___y_6994_ = v___y_7010_;
v___y_6995_ = v___x_7015_;
v___y_6996_ = v___y_7011_;
v___y_6997_ = v___y_7012_;
v___y_6998_ = v___y_7013_;
v___y_6999_ = v___x_7016_;
goto v___jp_6987_;
}
else
{
v___y_6988_ = v___y_7005_;
v___y_6989_ = v___y_7014_;
v___y_6990_ = v___y_7006_;
v___y_6991_ = v___y_7008_;
v___y_6992_ = v___y_7007_;
v___y_6993_ = v___y_7009_;
v___y_6994_ = v___y_7010_;
v___y_6995_ = v___x_7015_;
v___y_6996_ = v___y_7011_;
v___y_6997_ = v___y_7012_;
v___y_6998_ = v___y_7013_;
v___y_6999_ = v___y_7006_;
goto v___jp_6987_;
}
}
v___jp_7019_:
{
uint64_t v___x_7032_; uint64_t v___x_7033_; uint8_t v___x_7034_; 
v___x_7032_ = lean_uint64_shift_right(v___y_7028_, v___y_7021_);
v___x_7033_ = 0ULL;
v___x_7034_ = lean_uint64_dec_eq(v___x_7032_, v___x_7033_);
if (v___x_7034_ == 0)
{
uint64_t v___x_7035_; 
v___x_7035_ = lean_uint64_add(v___y_7020_, v___y_7021_);
v___y_7005_ = v___y_7022_;
v___y_7006_ = v___y_7031_;
v___y_7007_ = v___y_7024_;
v___y_7008_ = v___y_7023_;
v___y_7009_ = v___y_7025_;
v___y_7010_ = v___y_7026_;
v___y_7011_ = v___y_7027_;
v___y_7012_ = v___y_7029_;
v___y_7013_ = v___y_7030_;
v___y_7014_ = v___x_7035_;
goto v___jp_7004_;
}
else
{
v___y_7005_ = v___y_7022_;
v___y_7006_ = v___y_7031_;
v___y_7007_ = v___y_7024_;
v___y_7008_ = v___y_7023_;
v___y_7009_ = v___y_7025_;
v___y_7010_ = v___y_7026_;
v___y_7011_ = v___y_7027_;
v___y_7012_ = v___y_7029_;
v___y_7013_ = v___y_7030_;
v___y_7014_ = v___y_7020_;
goto v___jp_7004_;
}
}
v___jp_7036_:
{
uint64_t v___x_7047_; uint64_t v___x_7048_; uint64_t v___x_7049_; uint8_t v___x_7050_; 
v___x_7047_ = 4ULL;
v___x_7048_ = lean_uint64_shift_right(v___y_7043_, v___x_7047_);
v___x_7049_ = 0ULL;
v___x_7050_ = lean_uint64_dec_eq(v___x_7048_, v___x_7049_);
if (v___x_7050_ == 0)
{
v___y_7020_ = v___y_7046_;
v___y_7021_ = v___x_7047_;
v___y_7022_ = v___y_7037_;
v___y_7023_ = v___y_7039_;
v___y_7024_ = v___y_7038_;
v___y_7025_ = v___y_7040_;
v___y_7026_ = v___y_7041_;
v___y_7027_ = v___y_7042_;
v___y_7028_ = v___y_7043_;
v___y_7029_ = v___y_7044_;
v___y_7030_ = v___y_7045_;
v___y_7031_ = v___x_7048_;
goto v___jp_7019_;
}
else
{
v___y_7020_ = v___y_7046_;
v___y_7021_ = v___x_7047_;
v___y_7022_ = v___y_7037_;
v___y_7023_ = v___y_7039_;
v___y_7024_ = v___y_7038_;
v___y_7025_ = v___y_7040_;
v___y_7026_ = v___y_7041_;
v___y_7027_ = v___y_7042_;
v___y_7028_ = v___y_7043_;
v___y_7029_ = v___y_7044_;
v___y_7030_ = v___y_7045_;
v___y_7031_ = v___y_7043_;
goto v___jp_7019_;
}
}
v___jp_7051_:
{
uint64_t v___x_7064_; uint64_t v___x_7065_; uint8_t v___x_7066_; 
v___x_7064_ = lean_uint64_shift_right(v___y_7052_, v___y_7060_);
v___x_7065_ = 0ULL;
v___x_7066_ = lean_uint64_dec_eq(v___x_7064_, v___x_7065_);
if (v___x_7066_ == 0)
{
uint64_t v___x_7067_; 
v___x_7067_ = lean_uint64_add(v___y_7053_, v___y_7060_);
v___y_7037_ = v___y_7054_;
v___y_7038_ = v___y_7056_;
v___y_7039_ = v___y_7055_;
v___y_7040_ = v___y_7057_;
v___y_7041_ = v___y_7058_;
v___y_7042_ = v___y_7059_;
v___y_7043_ = v___y_7063_;
v___y_7044_ = v___y_7061_;
v___y_7045_ = v___y_7062_;
v___y_7046_ = v___x_7067_;
goto v___jp_7036_;
}
else
{
v___y_7037_ = v___y_7054_;
v___y_7038_ = v___y_7056_;
v___y_7039_ = v___y_7055_;
v___y_7040_ = v___y_7057_;
v___y_7041_ = v___y_7058_;
v___y_7042_ = v___y_7059_;
v___y_7043_ = v___y_7063_;
v___y_7044_ = v___y_7061_;
v___y_7045_ = v___y_7062_;
v___y_7046_ = v___y_7053_;
goto v___jp_7036_;
}
}
v___jp_7068_:
{
uint64_t v___x_7079_; uint64_t v___x_7080_; uint64_t v___x_7081_; uint8_t v___x_7082_; 
v___x_7079_ = 8ULL;
v___x_7080_ = lean_uint64_shift_right(v___y_7069_, v___x_7079_);
v___x_7081_ = 0ULL;
v___x_7082_ = lean_uint64_dec_eq(v___x_7080_, v___x_7081_);
if (v___x_7082_ == 0)
{
v___y_7052_ = v___y_7069_;
v___y_7053_ = v___y_7078_;
v___y_7054_ = v___y_7070_;
v___y_7055_ = v___y_7072_;
v___y_7056_ = v___y_7071_;
v___y_7057_ = v___y_7073_;
v___y_7058_ = v___y_7074_;
v___y_7059_ = v___y_7075_;
v___y_7060_ = v___x_7079_;
v___y_7061_ = v___y_7076_;
v___y_7062_ = v___y_7077_;
v___y_7063_ = v___x_7080_;
goto v___jp_7051_;
}
else
{
v___y_7052_ = v___y_7069_;
v___y_7053_ = v___y_7078_;
v___y_7054_ = v___y_7070_;
v___y_7055_ = v___y_7072_;
v___y_7056_ = v___y_7071_;
v___y_7057_ = v___y_7073_;
v___y_7058_ = v___y_7074_;
v___y_7059_ = v___y_7075_;
v___y_7060_ = v___x_7079_;
v___y_7061_ = v___y_7076_;
v___y_7062_ = v___y_7077_;
v___y_7063_ = v___y_7069_;
goto v___jp_7051_;
}
}
v___jp_7083_:
{
uint64_t v___x_7096_; uint64_t v___x_7097_; uint8_t v___x_7098_; 
v___x_7096_ = lean_uint64_shift_right(v___y_7086_, v___y_7084_);
v___x_7097_ = 0ULL;
v___x_7098_ = lean_uint64_dec_eq(v___x_7096_, v___x_7097_);
if (v___x_7098_ == 0)
{
uint64_t v___x_7099_; 
v___x_7099_ = lean_uint64_add(v___y_7093_, v___y_7084_);
v___y_7069_ = v___y_7095_;
v___y_7070_ = v___y_7085_;
v___y_7071_ = v___y_7088_;
v___y_7072_ = v___y_7087_;
v___y_7073_ = v___y_7089_;
v___y_7074_ = v___y_7090_;
v___y_7075_ = v___y_7091_;
v___y_7076_ = v___y_7092_;
v___y_7077_ = v___y_7094_;
v___y_7078_ = v___x_7099_;
goto v___jp_7068_;
}
else
{
v___y_7069_ = v___y_7095_;
v___y_7070_ = v___y_7085_;
v___y_7071_ = v___y_7088_;
v___y_7072_ = v___y_7087_;
v___y_7073_ = v___y_7089_;
v___y_7074_ = v___y_7090_;
v___y_7075_ = v___y_7091_;
v___y_7076_ = v___y_7092_;
v___y_7077_ = v___y_7094_;
v___y_7078_ = v___y_7093_;
goto v___jp_7068_;
}
}
v___jp_7100_:
{
uint64_t v___x_7111_; uint64_t v___x_7112_; uint64_t v___x_7113_; uint8_t v___x_7114_; 
v___x_7111_ = 16ULL;
v___x_7112_ = lean_uint64_shift_right(v___y_7102_, v___x_7111_);
v___x_7113_ = 0ULL;
v___x_7114_ = lean_uint64_dec_eq(v___x_7112_, v___x_7113_);
if (v___x_7114_ == 0)
{
v___y_7084_ = v___x_7111_;
v___y_7085_ = v___y_7101_;
v___y_7086_ = v___y_7102_;
v___y_7087_ = v___y_7104_;
v___y_7088_ = v___y_7103_;
v___y_7089_ = v___y_7105_;
v___y_7090_ = v___y_7106_;
v___y_7091_ = v___y_7107_;
v___y_7092_ = v___y_7108_;
v___y_7093_ = v___y_7110_;
v___y_7094_ = v___y_7109_;
v___y_7095_ = v___x_7112_;
goto v___jp_7083_;
}
else
{
v___y_7084_ = v___x_7111_;
v___y_7085_ = v___y_7101_;
v___y_7086_ = v___y_7102_;
v___y_7087_ = v___y_7104_;
v___y_7088_ = v___y_7103_;
v___y_7089_ = v___y_7105_;
v___y_7090_ = v___y_7106_;
v___y_7091_ = v___y_7107_;
v___y_7092_ = v___y_7108_;
v___y_7093_ = v___y_7110_;
v___y_7094_ = v___y_7109_;
v___y_7095_ = v___y_7102_;
goto v___jp_7083_;
}
}
v___jp_7115_:
{
uint64_t v___x_7127_; uint64_t v___x_7128_; uint8_t v___x_7129_; 
v___x_7127_ = lean_uint64_shift_right(v___y_7118_, v___y_7117_);
v___x_7128_ = 0ULL;
v___x_7129_ = lean_uint64_dec_eq(v___x_7127_, v___x_7128_);
if (v___x_7129_ == 0)
{
v___y_7101_ = v___y_7116_;
v___y_7102_ = v___y_7126_;
v___y_7103_ = v___y_7120_;
v___y_7104_ = v___y_7119_;
v___y_7105_ = v___y_7121_;
v___y_7106_ = v___y_7122_;
v___y_7107_ = v___y_7123_;
v___y_7108_ = v___y_7124_;
v___y_7109_ = v___y_7125_;
v___y_7110_ = v___y_7117_;
goto v___jp_7100_;
}
else
{
v___y_7101_ = v___y_7116_;
v___y_7102_ = v___y_7126_;
v___y_7103_ = v___y_7120_;
v___y_7104_ = v___y_7119_;
v___y_7105_ = v___y_7121_;
v___y_7106_ = v___y_7122_;
v___y_7107_ = v___y_7123_;
v___y_7108_ = v___y_7124_;
v___y_7109_ = v___y_7125_;
v___y_7110_ = v___x_7128_;
goto v___jp_7100_;
}
}
v___jp_7130_:
{
if (v___y_7134_ == 0)
{
uint32_t v___x_7140_; 
lean_dec_ref(v___y_7137_);
lean_dec_ref(v___y_7136_);
v___x_7140_ = lp_competition_Submission_R24ExactDotCost_referencePrepared(v___y_7133_);
lean_dec_ref(v___y_7133_);
return v___x_7140_;
}
else
{
if (v___y_7132_ == 0)
{
uint32_t v___x_7141_; 
lean_dec_ref(v___y_7137_);
lean_dec_ref(v___y_7136_);
v___x_7141_ = lp_competition_Submission_R24ExactDotCost_referencePrepared(v___y_7133_);
lean_dec_ref(v___y_7133_);
return v___x_7141_;
}
else
{
if (v___y_7131_ == 0)
{
uint32_t v___x_7142_; 
lean_dec_ref(v___y_7137_);
lean_dec_ref(v___y_7136_);
v___x_7142_ = lp_competition_Submission_R24ExactDotCost_referencePrepared(v___y_7133_);
lean_dec_ref(v___y_7133_);
return v___x_7142_;
}
else
{
lean_object* v___x_7143_; lean_object* v___x_7144_; uint8_t v___x_7145_; 
v___x_7143_ = lean_array_get_size(v___y_7136_);
v___x_7144_ = lean_unsigned_to_nat(1048576u);
v___x_7145_ = lean_nat_dec_le(v___x_7143_, v___x_7144_);
if (v___x_7145_ == 0)
{
uint32_t v___x_7146_; 
lean_dec_ref(v___y_7137_);
lean_dec_ref(v___y_7136_);
v___x_7146_ = lp_competition_Submission_R24ExactDotCost_referencePrepared(v___y_7133_);
lean_dec_ref(v___y_7133_);
return v___x_7146_;
}
else
{
lean_object* v___x_7147_; lean_object* v___x_7148_; lean_object* v___x_7149_; lean_object* v___x_7150_; lean_object* v___x_7151_; lean_object* v___x_7152_; uint8_t v___x_7153_; 
v___x_7147_ = lean_unsigned_to_nat(48u);
v___x_7148_ = lean_uint32_to_nat(v___y_7135_);
v___x_7149_ = lean_uint32_to_nat(v___y_7138_);
v___x_7150_ = lean_nat_sub(v___x_7148_, v___x_7149_);
lean_dec(v___x_7149_);
lean_dec(v___x_7148_);
v___x_7151_ = lean_nat_add(v___x_7147_, v___x_7150_);
lean_dec(v___x_7150_);
v___x_7152_ = lean_unsigned_to_nat(1u);
v___x_7153_ = lean_nat_dec_le(v___x_7143_, v___x_7152_);
if (v___x_7153_ == 0)
{
lean_object* v___x_7154_; uint64_t v___x_7155_; uint64_t v___x_7156_; uint64_t v___x_7157_; uint64_t v___x_7158_; uint8_t v___x_7159_; 
v___x_7154_ = lean_nat_sub(v___x_7143_, v___x_7152_);
v___x_7155_ = lean_uint64_of_nat(v___x_7154_);
lean_dec(v___x_7154_);
v___x_7156_ = 32ULL;
v___x_7157_ = lean_uint64_shift_right(v___x_7155_, v___x_7156_);
v___x_7158_ = 0ULL;
v___x_7159_ = lean_uint64_dec_eq(v___x_7157_, v___x_7158_);
if (v___x_7159_ == 0)
{
v___y_7116_ = v___y_7133_;
v___y_7117_ = v___x_7156_;
v___y_7118_ = v___x_7155_;
v___y_7119_ = v___x_7151_;
v___y_7120_ = v___y_7136_;
v___y_7121_ = v___y_7137_;
v___y_7122_ = v___x_7143_;
v___y_7123_ = v___y_7138_;
v___y_7124_ = v___y_7139_;
v___y_7125_ = v___x_7152_;
v___y_7126_ = v___x_7157_;
goto v___jp_7115_;
}
else
{
v___y_7116_ = v___y_7133_;
v___y_7117_ = v___x_7156_;
v___y_7118_ = v___x_7155_;
v___y_7119_ = v___x_7151_;
v___y_7120_ = v___y_7136_;
v___y_7121_ = v___y_7137_;
v___y_7122_ = v___x_7143_;
v___y_7123_ = v___y_7138_;
v___y_7124_ = v___y_7139_;
v___y_7125_ = v___x_7152_;
v___y_7126_ = v___x_7155_;
goto v___jp_7115_;
}
}
else
{
lean_object* v___x_7160_; 
v___x_7160_ = lean_unsigned_to_nat(0u);
v___y_6945_ = v___y_7133_;
v___y_6946_ = v___y_7136_;
v___y_6947_ = v___x_7151_;
v___y_6948_ = v___y_7137_;
v___y_6949_ = v___x_7143_;
v___y_6950_ = v___y_7138_;
v___y_6951_ = v___y_7139_;
v___y_6952_ = v___x_7160_;
goto v___jp_6944_;
}
}
}
}
}
}
v___jp_7161_:
{
uint64_t v___x_7168_; uint32_t v___x_7169_; 
v___x_7168_ = 0ULL;
v___x_7169_ = lp_competition_Submission_R24ExactDotTiered_native64Loop(v___y_7163_, v___y_7164_, v___y_7166_, v___y_7165_, v___y_7167_, v___x_7168_, v___y_7162_);
lean_dec_ref(v___y_7164_);
lean_dec_ref(v___y_7163_);
return v___x_7169_;
}
v___jp_7170_:
{
lean_object* v___x_7182_; lean_object* v___x_7183_; uint8_t v___x_7184_; 
v___x_7182_ = lean_nat_add(v___y_7176_, v___y_7181_);
lean_dec(v___y_7181_);
lean_dec(v___y_7176_);
v___x_7183_ = lean_unsigned_to_nat(62u);
v___x_7184_ = lean_nat_dec_le(v___x_7182_, v___x_7183_);
lean_dec(v___x_7182_);
if (v___x_7184_ == 0)
{
lean_dec(v___y_7173_);
v___y_7131_ = v___y_7171_;
v___y_7132_ = v___y_7172_;
v___y_7133_ = v___y_7174_;
v___y_7134_ = v___y_7175_;
v___y_7135_ = v___y_7178_;
v___y_7136_ = v___y_7177_;
v___y_7137_ = v___y_7179_;
v___y_7138_ = v___y_7180_;
v___y_7139_ = v___x_7184_;
goto v___jp_7130_;
}
else
{
lean_object* v___x_7185_; uint8_t v___x_7186_; 
lean_dec_ref(v___y_7174_);
v___x_7185_ = lean_unsigned_to_nat(0u);
v___x_7186_ = lean_nat_dec_eq(v___y_7173_, v___x_7185_);
if (v___x_7186_ == 0)
{
v___y_7162_ = v___y_7173_;
v___y_7163_ = v___y_7177_;
v___y_7164_ = v___y_7179_;
v___y_7165_ = v___x_7185_;
v___y_7166_ = v___y_7180_;
v___y_7167_ = v___x_7184_;
goto v___jp_7161_;
}
else
{
uint8_t v___x_7187_; 
v___x_7187_ = 0;
v___y_7162_ = v___y_7173_;
v___y_7163_ = v___y_7177_;
v___y_7164_ = v___y_7179_;
v___y_7165_ = v___x_7185_;
v___y_7166_ = v___y_7180_;
v___y_7167_ = v___x_7187_;
goto v___jp_7161_;
}
}
}
v___jp_7188_:
{
lean_object* v___x_7201_; lean_object* v___x_7202_; 
v___x_7201_ = lean_uint64_to_nat(v___y_7200_);
v___x_7202_ = lean_nat_add(v___x_7201_, v___y_7199_);
lean_dec(v___x_7201_);
v___y_7171_ = v___y_7189_;
v___y_7172_ = v___y_7190_;
v___y_7173_ = v___y_7192_;
v___y_7174_ = v___y_7191_;
v___y_7175_ = v___y_7194_;
v___y_7176_ = v___y_7193_;
v___y_7177_ = v___y_7196_;
v___y_7178_ = v___y_7195_;
v___y_7179_ = v___y_7197_;
v___y_7180_ = v___y_7198_;
v___y_7181_ = v___x_7202_;
goto v___jp_7170_;
}
v___jp_7203_:
{
uint64_t v___x_7217_; uint64_t v___x_7218_; uint64_t v___x_7219_; uint8_t v___x_7220_; 
v___x_7217_ = 1ULL;
v___x_7218_ = lean_uint64_shift_right(v___y_7213_, v___x_7217_);
v___x_7219_ = 0ULL;
v___x_7220_ = lean_uint64_dec_eq(v___x_7218_, v___x_7219_);
if (v___x_7220_ == 0)
{
uint64_t v___x_7221_; 
v___x_7221_ = lean_uint64_add(v___y_7216_, v___x_7217_);
v___y_7189_ = v___y_7204_;
v___y_7190_ = v___y_7205_;
v___y_7191_ = v___y_7207_;
v___y_7192_ = v___y_7206_;
v___y_7193_ = v___y_7209_;
v___y_7194_ = v___y_7208_;
v___y_7195_ = v___y_7211_;
v___y_7196_ = v___y_7210_;
v___y_7197_ = v___y_7212_;
v___y_7198_ = v___y_7214_;
v___y_7199_ = v___y_7215_;
v___y_7200_ = v___x_7221_;
goto v___jp_7188_;
}
else
{
v___y_7189_ = v___y_7204_;
v___y_7190_ = v___y_7205_;
v___y_7191_ = v___y_7207_;
v___y_7192_ = v___y_7206_;
v___y_7193_ = v___y_7209_;
v___y_7194_ = v___y_7208_;
v___y_7195_ = v___y_7211_;
v___y_7196_ = v___y_7210_;
v___y_7197_ = v___y_7212_;
v___y_7198_ = v___y_7214_;
v___y_7199_ = v___y_7215_;
v___y_7200_ = v___y_7216_;
goto v___jp_7188_;
}
}
v___jp_7222_:
{
uint64_t v___x_7238_; uint64_t v___x_7239_; uint8_t v___x_7240_; 
v___x_7238_ = lean_uint64_shift_right(v___y_7227_, v___y_7236_);
v___x_7239_ = 0ULL;
v___x_7240_ = lean_uint64_dec_eq(v___x_7238_, v___x_7239_);
if (v___x_7240_ == 0)
{
uint64_t v___x_7241_; 
v___x_7241_ = lean_uint64_add(v___y_7228_, v___y_7236_);
v___y_7204_ = v___y_7223_;
v___y_7205_ = v___y_7224_;
v___y_7206_ = v___y_7225_;
v___y_7207_ = v___y_7226_;
v___y_7208_ = v___y_7229_;
v___y_7209_ = v___y_7230_;
v___y_7210_ = v___y_7231_;
v___y_7211_ = v___y_7234_;
v___y_7212_ = v___y_7235_;
v___y_7213_ = v___y_7237_;
v___y_7214_ = v___y_7232_;
v___y_7215_ = v___y_7233_;
v___y_7216_ = v___x_7241_;
goto v___jp_7203_;
}
else
{
v___y_7204_ = v___y_7223_;
v___y_7205_ = v___y_7224_;
v___y_7206_ = v___y_7225_;
v___y_7207_ = v___y_7226_;
v___y_7208_ = v___y_7229_;
v___y_7209_ = v___y_7230_;
v___y_7210_ = v___y_7231_;
v___y_7211_ = v___y_7234_;
v___y_7212_ = v___y_7235_;
v___y_7213_ = v___y_7237_;
v___y_7214_ = v___y_7232_;
v___y_7215_ = v___y_7233_;
v___y_7216_ = v___y_7228_;
goto v___jp_7203_;
}
}
v___jp_7242_:
{
uint64_t v___x_7256_; uint64_t v___x_7257_; uint64_t v___x_7258_; uint8_t v___x_7259_; 
v___x_7256_ = 2ULL;
v___x_7257_ = lean_uint64_shift_right(v___y_7247_, v___x_7256_);
v___x_7258_ = 0ULL;
v___x_7259_ = lean_uint64_dec_eq(v___x_7257_, v___x_7258_);
if (v___x_7259_ == 0)
{
v___y_7223_ = v___y_7243_;
v___y_7224_ = v___y_7244_;
v___y_7225_ = v___y_7246_;
v___y_7226_ = v___y_7245_;
v___y_7227_ = v___y_7247_;
v___y_7228_ = v___y_7255_;
v___y_7229_ = v___y_7249_;
v___y_7230_ = v___y_7248_;
v___y_7231_ = v___y_7251_;
v___y_7232_ = v___y_7253_;
v___y_7233_ = v___y_7254_;
v___y_7234_ = v___y_7250_;
v___y_7235_ = v___y_7252_;
v___y_7236_ = v___x_7256_;
v___y_7237_ = v___x_7257_;
goto v___jp_7222_;
}
else
{
v___y_7223_ = v___y_7243_;
v___y_7224_ = v___y_7244_;
v___y_7225_ = v___y_7246_;
v___y_7226_ = v___y_7245_;
v___y_7227_ = v___y_7247_;
v___y_7228_ = v___y_7255_;
v___y_7229_ = v___y_7249_;
v___y_7230_ = v___y_7248_;
v___y_7231_ = v___y_7251_;
v___y_7232_ = v___y_7253_;
v___y_7233_ = v___y_7254_;
v___y_7234_ = v___y_7250_;
v___y_7235_ = v___y_7252_;
v___y_7236_ = v___x_7256_;
v___y_7237_ = v___y_7247_;
goto v___jp_7222_;
}
}
v___jp_7260_:
{
uint64_t v___x_7276_; uint64_t v___x_7277_; uint8_t v___x_7278_; 
v___x_7276_ = lean_uint64_shift_right(v___y_7274_, v___y_7269_);
v___x_7277_ = 0ULL;
v___x_7278_ = lean_uint64_dec_eq(v___x_7276_, v___x_7277_);
if (v___x_7278_ == 0)
{
uint64_t v___x_7279_; 
v___x_7279_ = lean_uint64_add(v___y_7271_, v___y_7269_);
v___y_7243_ = v___y_7261_;
v___y_7244_ = v___y_7262_;
v___y_7245_ = v___y_7263_;
v___y_7246_ = v___y_7264_;
v___y_7247_ = v___y_7275_;
v___y_7248_ = v___y_7265_;
v___y_7249_ = v___y_7266_;
v___y_7250_ = v___y_7272_;
v___y_7251_ = v___y_7267_;
v___y_7252_ = v___y_7273_;
v___y_7253_ = v___y_7268_;
v___y_7254_ = v___y_7270_;
v___y_7255_ = v___x_7279_;
goto v___jp_7242_;
}
else
{
v___y_7243_ = v___y_7261_;
v___y_7244_ = v___y_7262_;
v___y_7245_ = v___y_7263_;
v___y_7246_ = v___y_7264_;
v___y_7247_ = v___y_7275_;
v___y_7248_ = v___y_7265_;
v___y_7249_ = v___y_7266_;
v___y_7250_ = v___y_7272_;
v___y_7251_ = v___y_7267_;
v___y_7252_ = v___y_7273_;
v___y_7253_ = v___y_7268_;
v___y_7254_ = v___y_7270_;
v___y_7255_ = v___y_7271_;
goto v___jp_7242_;
}
}
v___jp_7280_:
{
uint64_t v___x_7294_; uint64_t v___x_7295_; uint64_t v___x_7296_; uint8_t v___x_7297_; 
v___x_7294_ = 4ULL;
v___x_7295_ = lean_uint64_shift_right(v___y_7290_, v___x_7294_);
v___x_7296_ = 0ULL;
v___x_7297_ = lean_uint64_dec_eq(v___x_7295_, v___x_7296_);
if (v___x_7297_ == 0)
{
v___y_7261_ = v___y_7281_;
v___y_7262_ = v___y_7282_;
v___y_7263_ = v___y_7284_;
v___y_7264_ = v___y_7283_;
v___y_7265_ = v___y_7286_;
v___y_7266_ = v___y_7285_;
v___y_7267_ = v___y_7288_;
v___y_7268_ = v___y_7291_;
v___y_7269_ = v___x_7294_;
v___y_7270_ = v___y_7292_;
v___y_7271_ = v___y_7293_;
v___y_7272_ = v___y_7287_;
v___y_7273_ = v___y_7289_;
v___y_7274_ = v___y_7290_;
v___y_7275_ = v___x_7295_;
goto v___jp_7260_;
}
else
{
v___y_7261_ = v___y_7281_;
v___y_7262_ = v___y_7282_;
v___y_7263_ = v___y_7284_;
v___y_7264_ = v___y_7283_;
v___y_7265_ = v___y_7286_;
v___y_7266_ = v___y_7285_;
v___y_7267_ = v___y_7288_;
v___y_7268_ = v___y_7291_;
v___y_7269_ = v___x_7294_;
v___y_7270_ = v___y_7292_;
v___y_7271_ = v___y_7293_;
v___y_7272_ = v___y_7287_;
v___y_7273_ = v___y_7289_;
v___y_7274_ = v___y_7290_;
v___y_7275_ = v___y_7290_;
goto v___jp_7260_;
}
}
v___jp_7298_:
{
uint64_t v___x_7314_; uint64_t v___x_7315_; uint8_t v___x_7316_; 
v___x_7314_ = lean_uint64_shift_right(v___y_7310_, v___y_7303_);
v___x_7315_ = 0ULL;
v___x_7316_ = lean_uint64_dec_eq(v___x_7314_, v___x_7315_);
if (v___x_7316_ == 0)
{
uint64_t v___x_7317_; 
v___x_7317_ = lean_uint64_add(v___y_7307_, v___y_7303_);
v___y_7281_ = v___y_7299_;
v___y_7282_ = v___y_7300_;
v___y_7283_ = v___y_7301_;
v___y_7284_ = v___y_7302_;
v___y_7285_ = v___y_7304_;
v___y_7286_ = v___y_7305_;
v___y_7287_ = v___y_7311_;
v___y_7288_ = v___y_7306_;
v___y_7289_ = v___y_7312_;
v___y_7290_ = v___y_7313_;
v___y_7291_ = v___y_7308_;
v___y_7292_ = v___y_7309_;
v___y_7293_ = v___x_7317_;
goto v___jp_7280_;
}
else
{
v___y_7281_ = v___y_7299_;
v___y_7282_ = v___y_7300_;
v___y_7283_ = v___y_7301_;
v___y_7284_ = v___y_7302_;
v___y_7285_ = v___y_7304_;
v___y_7286_ = v___y_7305_;
v___y_7287_ = v___y_7311_;
v___y_7288_ = v___y_7306_;
v___y_7289_ = v___y_7312_;
v___y_7290_ = v___y_7313_;
v___y_7291_ = v___y_7308_;
v___y_7292_ = v___y_7309_;
v___y_7293_ = v___y_7307_;
goto v___jp_7280_;
}
}
v___jp_7318_:
{
uint64_t v___x_7332_; uint64_t v___x_7333_; uint64_t v___x_7334_; uint8_t v___x_7335_; 
v___x_7332_ = 8ULL;
v___x_7333_ = lean_uint64_shift_right(v___y_7321_, v___x_7332_);
v___x_7334_ = 0ULL;
v___x_7335_ = lean_uint64_dec_eq(v___x_7333_, v___x_7334_);
if (v___x_7335_ == 0)
{
v___y_7299_ = v___y_7319_;
v___y_7300_ = v___y_7320_;
v___y_7301_ = v___y_7323_;
v___y_7302_ = v___y_7322_;
v___y_7303_ = v___x_7332_;
v___y_7304_ = v___y_7325_;
v___y_7305_ = v___y_7324_;
v___y_7306_ = v___y_7327_;
v___y_7307_ = v___y_7331_;
v___y_7308_ = v___y_7329_;
v___y_7309_ = v___y_7330_;
v___y_7310_ = v___y_7321_;
v___y_7311_ = v___y_7326_;
v___y_7312_ = v___y_7328_;
v___y_7313_ = v___x_7333_;
goto v___jp_7298_;
}
else
{
v___y_7299_ = v___y_7319_;
v___y_7300_ = v___y_7320_;
v___y_7301_ = v___y_7323_;
v___y_7302_ = v___y_7322_;
v___y_7303_ = v___x_7332_;
v___y_7304_ = v___y_7325_;
v___y_7305_ = v___y_7324_;
v___y_7306_ = v___y_7327_;
v___y_7307_ = v___y_7331_;
v___y_7308_ = v___y_7329_;
v___y_7309_ = v___y_7330_;
v___y_7310_ = v___y_7321_;
v___y_7311_ = v___y_7326_;
v___y_7312_ = v___y_7328_;
v___y_7313_ = v___y_7321_;
goto v___jp_7298_;
}
}
v___jp_7336_:
{
uint64_t v___x_7352_; uint64_t v___x_7353_; uint8_t v___x_7354_; 
v___x_7352_ = lean_uint64_shift_right(v___y_7347_, v___y_7344_);
v___x_7353_ = 0ULL;
v___x_7354_ = lean_uint64_dec_eq(v___x_7352_, v___x_7353_);
if (v___x_7354_ == 0)
{
uint64_t v___x_7355_; 
v___x_7355_ = lean_uint64_add(v___y_7348_, v___y_7344_);
v___y_7319_ = v___y_7337_;
v___y_7320_ = v___y_7338_;
v___y_7321_ = v___y_7351_;
v___y_7322_ = v___y_7339_;
v___y_7323_ = v___y_7340_;
v___y_7324_ = v___y_7341_;
v___y_7325_ = v___y_7342_;
v___y_7326_ = v___y_7349_;
v___y_7327_ = v___y_7343_;
v___y_7328_ = v___y_7350_;
v___y_7329_ = v___y_7345_;
v___y_7330_ = v___y_7346_;
v___y_7331_ = v___x_7355_;
goto v___jp_7318_;
}
else
{
v___y_7319_ = v___y_7337_;
v___y_7320_ = v___y_7338_;
v___y_7321_ = v___y_7351_;
v___y_7322_ = v___y_7339_;
v___y_7323_ = v___y_7340_;
v___y_7324_ = v___y_7341_;
v___y_7325_ = v___y_7342_;
v___y_7326_ = v___y_7349_;
v___y_7327_ = v___y_7343_;
v___y_7328_ = v___y_7350_;
v___y_7329_ = v___y_7345_;
v___y_7330_ = v___y_7346_;
v___y_7331_ = v___y_7348_;
goto v___jp_7318_;
}
}
v___jp_7356_:
{
uint64_t v___x_7370_; uint64_t v___x_7371_; uint64_t v___x_7372_; uint8_t v___x_7373_; 
v___x_7370_ = 16ULL;
v___x_7371_ = lean_uint64_shift_right(v___y_7359_, v___x_7370_);
v___x_7372_ = 0ULL;
v___x_7373_ = lean_uint64_dec_eq(v___x_7371_, v___x_7372_);
if (v___x_7373_ == 0)
{
v___y_7337_ = v___y_7357_;
v___y_7338_ = v___y_7358_;
v___y_7339_ = v___y_7361_;
v___y_7340_ = v___y_7360_;
v___y_7341_ = v___y_7363_;
v___y_7342_ = v___y_7362_;
v___y_7343_ = v___y_7365_;
v___y_7344_ = v___x_7370_;
v___y_7345_ = v___y_7367_;
v___y_7346_ = v___y_7368_;
v___y_7347_ = v___y_7359_;
v___y_7348_ = v___y_7369_;
v___y_7349_ = v___y_7364_;
v___y_7350_ = v___y_7366_;
v___y_7351_ = v___x_7371_;
goto v___jp_7336_;
}
else
{
v___y_7337_ = v___y_7357_;
v___y_7338_ = v___y_7358_;
v___y_7339_ = v___y_7361_;
v___y_7340_ = v___y_7360_;
v___y_7341_ = v___y_7363_;
v___y_7342_ = v___y_7362_;
v___y_7343_ = v___y_7365_;
v___y_7344_ = v___x_7370_;
v___y_7345_ = v___y_7367_;
v___y_7346_ = v___y_7368_;
v___y_7347_ = v___y_7359_;
v___y_7348_ = v___y_7369_;
v___y_7349_ = v___y_7364_;
v___y_7350_ = v___y_7366_;
v___y_7351_ = v___y_7359_;
goto v___jp_7336_;
}
}
v___jp_7374_:
{
uint64_t v___x_7389_; uint64_t v___x_7390_; uint8_t v___x_7391_; 
v___x_7389_ = lean_uint64_shift_right(v___y_7385_, v___y_7384_);
v___x_7390_ = 0ULL;
v___x_7391_ = lean_uint64_dec_eq(v___x_7389_, v___x_7390_);
if (v___x_7391_ == 0)
{
v___y_7357_ = v___y_7375_;
v___y_7358_ = v___y_7376_;
v___y_7359_ = v___y_7388_;
v___y_7360_ = v___y_7377_;
v___y_7361_ = v___y_7378_;
v___y_7362_ = v___y_7379_;
v___y_7363_ = v___y_7380_;
v___y_7364_ = v___y_7386_;
v___y_7365_ = v___y_7381_;
v___y_7366_ = v___y_7387_;
v___y_7367_ = v___y_7382_;
v___y_7368_ = v___y_7383_;
v___y_7369_ = v___y_7384_;
goto v___jp_7356_;
}
else
{
v___y_7357_ = v___y_7375_;
v___y_7358_ = v___y_7376_;
v___y_7359_ = v___y_7388_;
v___y_7360_ = v___y_7377_;
v___y_7361_ = v___y_7378_;
v___y_7362_ = v___y_7379_;
v___y_7363_ = v___y_7380_;
v___y_7364_ = v___y_7386_;
v___y_7365_ = v___y_7381_;
v___y_7366_ = v___y_7387_;
v___y_7367_ = v___y_7382_;
v___y_7368_ = v___y_7383_;
v___y_7369_ = v___x_7390_;
goto v___jp_7356_;
}
}
v___jp_7398_:
{
lean_object* v_raw_7401_; lean_object* v_data_7402_; uint8_t v_normal_7403_; lean_object* v___x_7404_; lean_object* v___x_7405_; uint8_t v___x_7406_; lean_object* v___x_7407_; 
v_raw_7401_ = lean_ctor_get(v_right_6934_, 0);
v_data_7402_ = lean_ctor_get(v_right_6934_, 1);
lean_inc_ref(v_data_7402_);
v_normal_7403_ = lean_ctor_get_uint8(v_right_6934_, sizeof(void*)*2 + 8);
v___x_7404_ = lean_array_get_size(v_raw_7392_);
v___x_7405_ = lean_array_get_size(v_raw_7401_);
v___x_7406_ = lean_nat_dec_eq(v___x_7404_, v___x_7405_);
v___x_7407_ = lean_alloc_ctor(0, 2, 9);
lean_ctor_set(v___x_7407_, 0, v_left_6933_);
lean_ctor_set(v___x_7407_, 1, v_right_6934_);
lean_ctor_set_uint32(v___x_7407_, sizeof(void*)*2, v___y_7399_);
lean_ctor_set_uint32(v___x_7407_, sizeof(void*)*2 + 4, v___y_7400_);
lean_ctor_set_uint8(v___x_7407_, sizeof(void*)*2 + 8, v___x_7406_);
if (v___x_7406_ == 0)
{
v___y_7131_ = v_normal_7403_;
v___y_7132_ = v_normal_7396_;
v___y_7133_ = v___x_7407_;
v___y_7134_ = v___x_7406_;
v___y_7135_ = v___y_7400_;
v___y_7136_ = v_data_7393_;
v___y_7137_ = v_data_7402_;
v___y_7138_ = v___y_7399_;
v___y_7139_ = v___x_7406_;
goto v___jp_7130_;
}
else
{
if (v_normal_7396_ == 0)
{
v___y_7131_ = v_normal_7403_;
v___y_7132_ = v_normal_7396_;
v___y_7133_ = v___x_7407_;
v___y_7134_ = v___x_7406_;
v___y_7135_ = v___y_7400_;
v___y_7136_ = v_data_7393_;
v___y_7137_ = v_data_7402_;
v___y_7138_ = v___y_7399_;
v___y_7139_ = v_normal_7396_;
goto v___jp_7130_;
}
else
{
if (v_normal_7403_ == 0)
{
v___y_7131_ = v_normal_7403_;
v___y_7132_ = v_normal_7396_;
v___y_7133_ = v___x_7407_;
v___y_7134_ = v___x_7406_;
v___y_7135_ = v___y_7400_;
v___y_7136_ = v_data_7393_;
v___y_7137_ = v_data_7402_;
v___y_7138_ = v___y_7399_;
v___y_7139_ = v_normal_7403_;
goto v___jp_7130_;
}
else
{
lean_object* v___x_7408_; lean_object* v___x_7409_; uint8_t v___x_7410_; 
v___x_7408_ = lean_array_get_size(v_data_7393_);
v___x_7409_ = lean_unsigned_to_nat(1048576u);
v___x_7410_ = lean_nat_dec_le(v___x_7408_, v___x_7409_);
if (v___x_7410_ == 0)
{
v___y_7131_ = v_normal_7403_;
v___y_7132_ = v_normal_7396_;
v___y_7133_ = v___x_7407_;
v___y_7134_ = v___x_7406_;
v___y_7135_ = v___y_7400_;
v___y_7136_ = v_data_7393_;
v___y_7137_ = v_data_7402_;
v___y_7138_ = v___y_7399_;
v___y_7139_ = v___x_7410_;
goto v___jp_7130_;
}
else
{
lean_object* v___x_7411_; lean_object* v___x_7412_; lean_object* v___x_7413_; lean_object* v___x_7414_; lean_object* v___x_7415_; lean_object* v___x_7416_; uint8_t v___x_7417_; 
v___x_7411_ = lean_unsigned_to_nat(48u);
v___x_7412_ = lean_uint32_to_nat(v___y_7400_);
v___x_7413_ = lean_uint32_to_nat(v___y_7399_);
v___x_7414_ = lean_nat_sub(v___x_7412_, v___x_7413_);
lean_dec(v___x_7413_);
lean_dec(v___x_7412_);
v___x_7415_ = lean_nat_add(v___x_7411_, v___x_7414_);
lean_dec(v___x_7414_);
v___x_7416_ = lean_unsigned_to_nat(1u);
v___x_7417_ = lean_nat_dec_le(v___x_7408_, v___x_7416_);
if (v___x_7417_ == 0)
{
lean_object* v___x_7418_; uint64_t v___x_7419_; uint64_t v___x_7420_; uint64_t v___x_7421_; uint64_t v___x_7422_; uint8_t v___x_7423_; 
v___x_7418_ = lean_nat_sub(v___x_7408_, v___x_7416_);
v___x_7419_ = lean_uint64_of_nat(v___x_7418_);
lean_dec(v___x_7418_);
v___x_7420_ = 32ULL;
v___x_7421_ = lean_uint64_shift_right(v___x_7419_, v___x_7420_);
v___x_7422_ = 0ULL;
v___x_7423_ = lean_uint64_dec_eq(v___x_7421_, v___x_7422_);
if (v___x_7423_ == 0)
{
v___y_7375_ = v_normal_7403_;
v___y_7376_ = v_normal_7396_;
v___y_7377_ = v___x_7408_;
v___y_7378_ = v___x_7407_;
v___y_7379_ = v___x_7406_;
v___y_7380_ = v___x_7415_;
v___y_7381_ = v_data_7393_;
v___y_7382_ = v___y_7399_;
v___y_7383_ = v___x_7416_;
v___y_7384_ = v___x_7420_;
v___y_7385_ = v___x_7419_;
v___y_7386_ = v___y_7400_;
v___y_7387_ = v_data_7402_;
v___y_7388_ = v___x_7421_;
goto v___jp_7374_;
}
else
{
v___y_7375_ = v_normal_7403_;
v___y_7376_ = v_normal_7396_;
v___y_7377_ = v___x_7408_;
v___y_7378_ = v___x_7407_;
v___y_7379_ = v___x_7406_;
v___y_7380_ = v___x_7415_;
v___y_7381_ = v_data_7393_;
v___y_7382_ = v___y_7399_;
v___y_7383_ = v___x_7416_;
v___y_7384_ = v___x_7420_;
v___y_7385_ = v___x_7419_;
v___y_7386_ = v___y_7400_;
v___y_7387_ = v_data_7402_;
v___y_7388_ = v___x_7419_;
goto v___jp_7374_;
}
}
else
{
lean_object* v___x_7424_; 
v___x_7424_ = lean_unsigned_to_nat(0u);
v___y_7171_ = v_normal_7403_;
v___y_7172_ = v_normal_7396_;
v___y_7173_ = v___x_7408_;
v___y_7174_ = v___x_7407_;
v___y_7175_ = v___x_7406_;
v___y_7176_ = v___x_7415_;
v___y_7177_ = v_data_7393_;
v___y_7178_ = v___y_7400_;
v___y_7179_ = v_data_7402_;
v___y_7180_ = v___y_7399_;
v___y_7181_ = v___x_7424_;
goto v___jp_7170_;
}
}
}
}
}
}
v___jp_7425_:
{
uint32_t v___x_7426_; 
v___x_7426_ = 0;
v___y_7399_ = v___x_7426_;
v___y_7400_ = v___x_7426_;
goto v___jp_7398_;
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_R24ExactDotTiered_prepared2v2___boxed(lean_object* v_left_7432_, lean_object* v_right_7433_){
_start:
{
uint32_t v_res_7434_; lean_object* v_r_7435_; 
v_res_7434_ = lp_competition_Submission_R24ExactDotTiered_prepared2v2(v_left_7432_, v_right_7433_);
v_r_7435_ = lean_box_uint32(v_res_7434_);
return v_r_7435_;
}
}
LEAN_EXPORT uint32_t lp_competition_Submission_R24PortableF64_index32(uint32_t v_word_7436_){
_start:
{
uint32_t v___x_7437_; uint32_t v___x_7438_; uint32_t v___x_7439_; uint32_t v_e_7440_; uint32_t v___x_7441_; uint8_t v___x_7442_; 
v___x_7437_ = 23;
v___x_7438_ = lean_uint32_shift_right(v_word_7436_, v___x_7437_);
v___x_7439_ = 255;
v_e_7440_ = lean_uint32_land(v___x_7438_, v___x_7439_);
v___x_7441_ = 0;
v___x_7442_ = lean_uint32_dec_eq(v_e_7440_, v___x_7441_);
if (v___x_7442_ == 0)
{
uint32_t v___x_7443_; uint32_t v___x_7444_; 
v___x_7443_ = 1;
v___x_7444_ = lean_uint32_sub(v_e_7440_, v___x_7443_);
return v___x_7444_;
}
else
{
return v___x_7441_;
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_R24PortableF64_index32___boxed(lean_object* v_word_7445_){
_start:
{
uint32_t v_word_boxed_7446_; uint32_t v_res_7447_; lean_object* v_r_7448_; 
v_word_boxed_7446_ = lean_unbox_uint32(v_word_7445_);
lean_dec(v_word_7445_);
v_res_7447_ = lp_competition_Submission_R24PortableF64_index32(v_word_boxed_7446_);
v_r_7448_ = lean_box_uint32(v_res_7447_);
return v_r_7448_;
}
}
LEAN_EXPORT uint64_t lp_competition_Submission_R24PortableF64_widenBits(uint32_t v_word_7449_){
_start:
{
uint64_t v___x_7450_; uint64_t v___x_7451_; uint64_t v___x_7452_; uint64_t v___x_7453_; uint64_t v_sign_7454_; uint32_t v___x_7455_; uint32_t v___x_7456_; uint32_t v___x_7457_; uint32_t v_e_7458_; uint32_t v___x_7459_; uint32_t v___x_7460_; uint64_t v_f_7461_; uint64_t v___y_7463_; uint32_t v___x_7475_; uint8_t v___x_7476_; 
v___x_7450_ = lean_uint32_to_uint64(v_word_7449_);
v___x_7451_ = 2147483648ULL;
v___x_7452_ = lean_uint64_land(v___x_7450_, v___x_7451_);
v___x_7453_ = 32ULL;
v_sign_7454_ = lean_uint64_shift_left(v___x_7452_, v___x_7453_);
v___x_7455_ = 23;
v___x_7456_ = lean_uint32_shift_right(v_word_7449_, v___x_7455_);
v___x_7457_ = 255;
v_e_7458_ = lean_uint32_land(v___x_7456_, v___x_7457_);
v___x_7459_ = 8388607;
v___x_7460_ = lean_uint32_land(v_word_7449_, v___x_7459_);
v_f_7461_ = lean_uint32_to_uint64(v___x_7460_);
v___x_7475_ = 0;
v___x_7476_ = lean_uint32_dec_eq(v_e_7458_, v___x_7475_);
if (v___x_7476_ == 0)
{
uint64_t v___x_7477_; uint64_t v___x_7478_; uint64_t v___x_7479_; uint64_t v___x_7480_; uint64_t v___x_7481_; uint64_t v___x_7482_; uint64_t v___x_7483_; uint64_t v___x_7484_; uint64_t v___x_7485_; 
v___x_7477_ = lean_uint32_to_uint64(v_e_7458_);
v___x_7478_ = 896ULL;
v___x_7479_ = lean_uint64_add(v___x_7477_, v___x_7478_);
v___x_7480_ = 52ULL;
v___x_7481_ = lean_uint64_shift_left(v___x_7479_, v___x_7480_);
v___x_7482_ = lean_uint64_lor(v_sign_7454_, v___x_7481_);
v___x_7483_ = 29ULL;
v___x_7484_ = lean_uint64_shift_left(v_f_7461_, v___x_7483_);
v___x_7485_ = lean_uint64_lor(v___x_7482_, v___x_7484_);
return v___x_7485_;
}
else
{
uint64_t v___x_7486_; uint64_t v___y_7488_; uint64_t v___y_7489_; uint64_t v___y_7495_; uint64_t v___y_7496_; uint64_t v___y_7497_; uint64_t v___y_7498_; uint64_t v___y_7503_; uint64_t v___y_7504_; uint64_t v___y_7509_; uint64_t v___y_7510_; uint64_t v___y_7511_; uint64_t v___y_7512_; uint64_t v___y_7517_; uint64_t v___y_7518_; uint64_t v___y_7523_; uint64_t v___y_7524_; uint64_t v___y_7525_; uint64_t v___y_7526_; uint64_t v___y_7531_; uint64_t v___y_7532_; uint64_t v___y_7537_; uint64_t v___y_7538_; uint64_t v___y_7539_; uint64_t v___y_7540_; uint64_t v___y_7545_; uint64_t v___y_7546_; uint64_t v___y_7551_; uint8_t v___x_7554_; 
v___x_7486_ = 0ULL;
v___x_7554_ = lean_uint64_dec_eq(v_f_7461_, v___x_7486_);
if (v___x_7554_ == 0)
{
uint64_t v___x_7555_; uint8_t v___x_7556_; 
v___x_7555_ = lean_uint64_shift_right(v_f_7461_, v___x_7453_);
v___x_7556_ = lean_uint64_dec_eq(v___x_7555_, v___x_7486_);
if (v___x_7556_ == 0)
{
v___y_7551_ = v___x_7555_;
goto v___jp_7550_;
}
else
{
v___y_7551_ = v_f_7461_;
goto v___jp_7550_;
}
}
else
{
return v_sign_7454_;
}
v___jp_7487_:
{
uint64_t v___x_7490_; uint64_t v___x_7491_; uint8_t v___x_7492_; 
v___x_7490_ = 1ULL;
v___x_7491_ = lean_uint64_shift_right(v___y_7488_, v___x_7490_);
v___x_7492_ = lean_uint64_dec_eq(v___x_7491_, v___x_7486_);
if (v___x_7492_ == 0)
{
uint64_t v___x_7493_; 
v___x_7493_ = lean_uint64_add(v___y_7489_, v___x_7490_);
v___y_7463_ = v___x_7493_;
goto v___jp_7462_;
}
else
{
v___y_7463_ = v___y_7489_;
goto v___jp_7462_;
}
}
v___jp_7494_:
{
uint64_t v___x_7499_; uint8_t v___x_7500_; 
v___x_7499_ = lean_uint64_shift_right(v___y_7495_, v___y_7496_);
v___x_7500_ = lean_uint64_dec_eq(v___x_7499_, v___x_7486_);
if (v___x_7500_ == 0)
{
uint64_t v___x_7501_; 
v___x_7501_ = lean_uint64_add(v___y_7497_, v___y_7496_);
v___y_7488_ = v___y_7498_;
v___y_7489_ = v___x_7501_;
goto v___jp_7487_;
}
else
{
v___y_7488_ = v___y_7498_;
v___y_7489_ = v___y_7497_;
goto v___jp_7487_;
}
}
v___jp_7502_:
{
uint64_t v___x_7505_; uint64_t v___x_7506_; uint8_t v___x_7507_; 
v___x_7505_ = 2ULL;
v___x_7506_ = lean_uint64_shift_right(v___y_7503_, v___x_7505_);
v___x_7507_ = lean_uint64_dec_eq(v___x_7506_, v___x_7486_);
if (v___x_7507_ == 0)
{
v___y_7495_ = v___y_7503_;
v___y_7496_ = v___x_7505_;
v___y_7497_ = v___y_7504_;
v___y_7498_ = v___x_7506_;
goto v___jp_7494_;
}
else
{
v___y_7495_ = v___y_7503_;
v___y_7496_ = v___x_7505_;
v___y_7497_ = v___y_7504_;
v___y_7498_ = v___y_7503_;
goto v___jp_7494_;
}
}
v___jp_7508_:
{
uint64_t v___x_7513_; uint8_t v___x_7514_; 
v___x_7513_ = lean_uint64_shift_right(v___y_7510_, v___y_7509_);
v___x_7514_ = lean_uint64_dec_eq(v___x_7513_, v___x_7486_);
if (v___x_7514_ == 0)
{
uint64_t v___x_7515_; 
v___x_7515_ = lean_uint64_add(v___y_7511_, v___y_7509_);
v___y_7503_ = v___y_7512_;
v___y_7504_ = v___x_7515_;
goto v___jp_7502_;
}
else
{
v___y_7503_ = v___y_7512_;
v___y_7504_ = v___y_7511_;
goto v___jp_7502_;
}
}
v___jp_7516_:
{
uint64_t v___x_7519_; uint64_t v___x_7520_; uint8_t v___x_7521_; 
v___x_7519_ = 4ULL;
v___x_7520_ = lean_uint64_shift_right(v___y_7517_, v___x_7519_);
v___x_7521_ = lean_uint64_dec_eq(v___x_7520_, v___x_7486_);
if (v___x_7521_ == 0)
{
v___y_7509_ = v___x_7519_;
v___y_7510_ = v___y_7517_;
v___y_7511_ = v___y_7518_;
v___y_7512_ = v___x_7520_;
goto v___jp_7508_;
}
else
{
v___y_7509_ = v___x_7519_;
v___y_7510_ = v___y_7517_;
v___y_7511_ = v___y_7518_;
v___y_7512_ = v___y_7517_;
goto v___jp_7508_;
}
}
v___jp_7522_:
{
uint64_t v___x_7527_; uint8_t v___x_7528_; 
v___x_7527_ = lean_uint64_shift_right(v___y_7523_, v___y_7524_);
v___x_7528_ = lean_uint64_dec_eq(v___x_7527_, v___x_7486_);
if (v___x_7528_ == 0)
{
uint64_t v___x_7529_; 
v___x_7529_ = lean_uint64_add(v___y_7525_, v___y_7524_);
v___y_7517_ = v___y_7526_;
v___y_7518_ = v___x_7529_;
goto v___jp_7516_;
}
else
{
v___y_7517_ = v___y_7526_;
v___y_7518_ = v___y_7525_;
goto v___jp_7516_;
}
}
v___jp_7530_:
{
uint64_t v___x_7533_; uint64_t v___x_7534_; uint8_t v___x_7535_; 
v___x_7533_ = 8ULL;
v___x_7534_ = lean_uint64_shift_right(v___y_7531_, v___x_7533_);
v___x_7535_ = lean_uint64_dec_eq(v___x_7534_, v___x_7486_);
if (v___x_7535_ == 0)
{
v___y_7523_ = v___y_7531_;
v___y_7524_ = v___x_7533_;
v___y_7525_ = v___y_7532_;
v___y_7526_ = v___x_7534_;
goto v___jp_7522_;
}
else
{
v___y_7523_ = v___y_7531_;
v___y_7524_ = v___x_7533_;
v___y_7525_ = v___y_7532_;
v___y_7526_ = v___y_7531_;
goto v___jp_7522_;
}
}
v___jp_7536_:
{
uint64_t v___x_7541_; uint8_t v___x_7542_; 
v___x_7541_ = lean_uint64_shift_right(v___y_7537_, v___y_7539_);
v___x_7542_ = lean_uint64_dec_eq(v___x_7541_, v___x_7486_);
if (v___x_7542_ == 0)
{
uint64_t v___x_7543_; 
v___x_7543_ = lean_uint64_add(v___y_7538_, v___y_7539_);
v___y_7531_ = v___y_7540_;
v___y_7532_ = v___x_7543_;
goto v___jp_7530_;
}
else
{
v___y_7531_ = v___y_7540_;
v___y_7532_ = v___y_7538_;
goto v___jp_7530_;
}
}
v___jp_7544_:
{
uint64_t v___x_7547_; uint64_t v___x_7548_; uint8_t v___x_7549_; 
v___x_7547_ = 16ULL;
v___x_7548_ = lean_uint64_shift_right(v___y_7545_, v___x_7547_);
v___x_7549_ = lean_uint64_dec_eq(v___x_7548_, v___x_7486_);
if (v___x_7549_ == 0)
{
v___y_7537_ = v___y_7545_;
v___y_7538_ = v___y_7546_;
v___y_7539_ = v___x_7547_;
v___y_7540_ = v___x_7548_;
goto v___jp_7536_;
}
else
{
v___y_7537_ = v___y_7545_;
v___y_7538_ = v___y_7546_;
v___y_7539_ = v___x_7547_;
v___y_7540_ = v___y_7545_;
goto v___jp_7536_;
}
}
v___jp_7550_:
{
uint64_t v___x_7552_; uint8_t v___x_7553_; 
v___x_7552_ = lean_uint64_shift_right(v_f_7461_, v___x_7453_);
v___x_7553_ = lean_uint64_dec_eq(v___x_7552_, v___x_7486_);
if (v___x_7553_ == 0)
{
v___y_7545_ = v___y_7551_;
v___y_7546_ = v___x_7453_;
goto v___jp_7544_;
}
else
{
v___y_7545_ = v___y_7551_;
v___y_7546_ = v___x_7486_;
goto v___jp_7544_;
}
}
}
v___jp_7462_:
{
uint64_t v___x_7464_; uint64_t v___x_7465_; uint64_t v___x_7466_; uint64_t v___x_7467_; uint64_t v___x_7468_; uint64_t v___x_7469_; uint64_t v___x_7470_; uint64_t v___x_7471_; uint64_t v___x_7472_; uint64_t v___x_7473_; uint64_t v___x_7474_; 
v___x_7464_ = 874ULL;
v___x_7465_ = lean_uint64_add(v___y_7463_, v___x_7464_);
v___x_7466_ = 52ULL;
v___x_7467_ = lean_uint64_shift_left(v___x_7465_, v___x_7466_);
v___x_7468_ = lean_uint64_lor(v_sign_7454_, v___x_7467_);
v___x_7469_ = 1ULL;
v___x_7470_ = lean_uint64_shift_left(v___x_7469_, v___y_7463_);
v___x_7471_ = lean_uint64_sub(v_f_7461_, v___x_7470_);
v___x_7472_ = lean_uint64_sub(v___x_7466_, v___y_7463_);
v___x_7473_ = lean_uint64_shift_left(v___x_7471_, v___x_7472_);
v___x_7474_ = lean_uint64_lor(v___x_7468_, v___x_7473_);
return v___x_7474_;
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_R24PortableF64_widenBits___boxed(lean_object* v_word_7557_){
_start:
{
uint32_t v_word_boxed_7558_; uint64_t v_res_7559_; lean_object* v_r_7560_; 
v_word_boxed_7558_ = lean_unbox_uint32(v_word_7557_);
lean_dec(v_word_7557_);
v_res_7559_ = lp_competition_Submission_R24PortableF64_widenBits(v_word_boxed_7558_);
v_r_7560_ = lean_box_uint64(v_res_7559_);
return v_r_7560_;
}
}
static double _init_lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00Submission_R24PortableF64_prepare_spec__0___closed__0(void){
_start:
{
uint64_t v___x_7561_; double v___x_7562_; 
v___x_7561_ = 0ULL;
v___x_7562_ = lean_float_of_bits(v___x_7561_);
return v___x_7562_;
}
}
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00Submission_R24PortableF64_prepare_spec__0(lean_object* v_as_7563_, size_t v_sz_7564_, size_t v_i_7565_, lean_object* v_b_7566_){
_start:
{
lean_object* v_a_7568_; uint8_t v___x_7572_; 
v___x_7572_ = lean_usize_dec_lt(v_i_7565_, v_sz_7564_);
if (v___x_7572_ == 0)
{
return v_b_7566_;
}
else
{
lean_object* v_snd_7573_; lean_object* v_fst_7574_; lean_object* v___x_7576_; uint8_t v_isShared_7577_; uint8_t v_isSharedCheck_7768_; 
v_snd_7573_ = lean_ctor_get(v_b_7566_, 1);
v_fst_7574_ = lean_ctor_get(v_b_7566_, 0);
v_isSharedCheck_7768_ = !lean_is_exclusive(v_b_7566_);
if (v_isSharedCheck_7768_ == 0)
{
v___x_7576_ = v_b_7566_;
v_isShared_7577_ = v_isSharedCheck_7768_;
goto v_resetjp_7575_;
}
else
{
lean_inc(v_snd_7573_);
lean_inc(v_fst_7574_);
lean_dec(v_b_7566_);
v___x_7576_ = lean_box(0);
v_isShared_7577_ = v_isSharedCheck_7768_;
goto v_resetjp_7575_;
}
v_resetjp_7575_:
{
lean_object* v_fst_7578_; lean_object* v_snd_7579_; lean_object* v___x_7581_; uint8_t v_isShared_7582_; uint8_t v_isSharedCheck_7767_; 
v_fst_7578_ = lean_ctor_get(v_snd_7573_, 0);
v_snd_7579_ = lean_ctor_get(v_snd_7573_, 1);
v_isSharedCheck_7767_ = !lean_is_exclusive(v_snd_7573_);
if (v_isSharedCheck_7767_ == 0)
{
v___x_7581_ = v_snd_7573_;
v_isShared_7582_ = v_isSharedCheck_7767_;
goto v_resetjp_7580_;
}
else
{
lean_inc(v_snd_7579_);
lean_inc(v_fst_7578_);
lean_dec(v_snd_7573_);
v___x_7581_ = lean_box(0);
v_isShared_7582_ = v_isSharedCheck_7767_;
goto v_resetjp_7580_;
}
v_resetjp_7580_:
{
uint32_t v___y_7584_; uint64_t v___y_7585_; uint32_t v___y_7596_; uint64_t v___y_7597_; uint64_t v___y_7598_; uint64_t v___y_7599_; uint32_t v___y_7612_; uint64_t v___y_7613_; uint64_t v___y_7614_; uint64_t v___y_7615_; uint64_t v___y_7616_; uint64_t v___y_7617_; uint32_t v___y_7623_; uint64_t v___y_7624_; uint64_t v___y_7625_; uint64_t v___y_7626_; uint64_t v___y_7627_; uint64_t v___y_7628_; uint64_t v___y_7629_; uint64_t v___y_7630_; uint32_t v___y_7635_; uint64_t v___y_7636_; uint64_t v___y_7637_; uint64_t v___y_7638_; uint64_t v___y_7639_; uint64_t v___y_7640_; uint64_t v___y_7645_; uint64_t v___y_7646_; uint32_t v___y_7647_; uint64_t v___y_7648_; uint64_t v___y_7649_; uint64_t v___y_7650_; uint64_t v___y_7651_; uint64_t v___y_7652_; uint32_t v___y_7657_; uint64_t v___y_7658_; uint64_t v___y_7659_; uint64_t v___y_7660_; uint64_t v___y_7661_; uint64_t v___y_7662_; uint32_t v___y_7667_; uint64_t v___y_7668_; uint64_t v___y_7669_; uint64_t v___y_7670_; uint64_t v___y_7671_; uint64_t v___y_7672_; uint64_t v___y_7673_; uint64_t v___y_7674_; uint32_t v___y_7679_; uint64_t v___y_7680_; uint64_t v___y_7681_; uint64_t v___y_7682_; uint64_t v___y_7683_; uint64_t v___y_7684_; uint64_t v___y_7689_; uint32_t v___y_7690_; uint64_t v___y_7691_; uint64_t v___y_7692_; uint64_t v___y_7693_; uint64_t v___y_7694_; uint64_t v___y_7695_; uint64_t v___y_7696_; uint32_t v___y_7701_; uint64_t v___y_7702_; uint64_t v___y_7703_; uint64_t v___y_7704_; uint64_t v___y_7705_; uint64_t v___y_7706_; uint32_t v___y_7711_; uint64_t v___y_7712_; uint64_t v___y_7713_; uint64_t v___y_7714_; uint64_t v___y_7715_; uint64_t v___y_7716_; lean_object* v_a_7719_; uint32_t v___x_7720_; uint32_t v___x_7721_; uint32_t v___x_7722_; uint32_t v___x_7723_; uint32_t v___x_7724_; uint8_t v___x_7725_; 
v_a_7719_ = lean_array_uget_borrowed(v_as_7563_, v_i_7565_);
v___x_7720_ = 23;
v___x_7721_ = lean_unbox_uint32(v_a_7719_);
v___x_7722_ = lean_uint32_shift_right(v___x_7721_, v___x_7720_);
v___x_7723_ = 255;
v___x_7724_ = lean_uint32_land(v___x_7722_, v___x_7723_);
v___x_7725_ = lean_uint32_dec_eq(v___x_7724_, v___x_7723_);
if (v___x_7725_ == 0)
{
uint32_t v_peak_7726_; uint32_t v_peak_7728_; uint32_t v___y_7754_; uint8_t v___x_7758_; 
v_peak_7726_ = 0;
v___x_7758_ = lean_uint32_dec_eq(v___x_7724_, v_peak_7726_);
if (v___x_7758_ == 0)
{
uint32_t v___x_7759_; uint32_t v___x_7760_; 
v___x_7759_ = 1;
v___x_7760_ = lean_uint32_sub(v___x_7724_, v___x_7759_);
v___y_7754_ = v___x_7760_;
goto v___jp_7753_;
}
else
{
v___y_7754_ = v_peak_7726_;
goto v___jp_7753_;
}
v___jp_7727_:
{
uint32_t v___x_7729_; uint64_t v___x_7730_; uint64_t v___x_7731_; uint64_t v___x_7732_; uint64_t v___x_7733_; uint64_t v_sign_7734_; uint32_t v___x_7735_; uint32_t v___x_7736_; uint32_t v___x_7737_; uint64_t v_f_7738_; uint8_t v___x_7739_; 
v___x_7729_ = lean_unbox_uint32(v_a_7719_);
v___x_7730_ = lean_uint32_to_uint64(v___x_7729_);
v___x_7731_ = 2147483648ULL;
v___x_7732_ = lean_uint64_land(v___x_7730_, v___x_7731_);
v___x_7733_ = 32ULL;
v_sign_7734_ = lean_uint64_shift_left(v___x_7732_, v___x_7733_);
v___x_7735_ = 8388607;
v___x_7736_ = lean_unbox_uint32(v_a_7719_);
v___x_7737_ = lean_uint32_land(v___x_7736_, v___x_7735_);
v_f_7738_ = lean_uint32_to_uint64(v___x_7737_);
v___x_7739_ = lean_uint32_dec_eq(v___x_7724_, v_peak_7726_);
if (v___x_7739_ == 0)
{
uint64_t v___x_7740_; uint64_t v___x_7741_; uint64_t v___x_7742_; uint64_t v___x_7743_; uint64_t v___x_7744_; uint64_t v___x_7745_; uint64_t v___x_7746_; uint64_t v___x_7747_; uint64_t v___x_7748_; 
v___x_7740_ = lean_uint32_to_uint64(v___x_7724_);
v___x_7741_ = 896ULL;
v___x_7742_ = lean_uint64_add(v___x_7740_, v___x_7741_);
v___x_7743_ = 52ULL;
v___x_7744_ = lean_uint64_shift_left(v___x_7742_, v___x_7743_);
v___x_7745_ = lean_uint64_lor(v_sign_7734_, v___x_7744_);
v___x_7746_ = 29ULL;
v___x_7747_ = lean_uint64_shift_left(v_f_7738_, v___x_7746_);
v___x_7748_ = lean_uint64_lor(v___x_7745_, v___x_7747_);
v___y_7584_ = v_peak_7728_;
v___y_7585_ = v___x_7748_;
goto v___jp_7583_;
}
else
{
uint64_t v___x_7749_; uint8_t v___x_7750_; 
v___x_7749_ = 0ULL;
v___x_7750_ = lean_uint64_dec_eq(v_f_7738_, v___x_7749_);
if (v___x_7750_ == 0)
{
uint64_t v___x_7751_; uint8_t v___x_7752_; 
v___x_7751_ = lean_uint64_shift_right(v_f_7738_, v___x_7733_);
v___x_7752_ = lean_uint64_dec_eq(v___x_7751_, v___x_7749_);
if (v___x_7752_ == 0)
{
v___y_7711_ = v_peak_7728_;
v___y_7712_ = v_sign_7734_;
v___y_7713_ = v___x_7749_;
v___y_7714_ = v_f_7738_;
v___y_7715_ = v___x_7733_;
v___y_7716_ = v___x_7751_;
goto v___jp_7710_;
}
else
{
v___y_7711_ = v_peak_7728_;
v___y_7712_ = v_sign_7734_;
v___y_7713_ = v___x_7749_;
v___y_7714_ = v_f_7738_;
v___y_7715_ = v___x_7733_;
v___y_7716_ = v_f_7738_;
goto v___jp_7710_;
}
}
else
{
v___y_7584_ = v_peak_7728_;
v___y_7585_ = v_sign_7734_;
goto v___jp_7583_;
}
}
}
v___jp_7753_:
{
uint32_t v___x_7755_; uint8_t v___x_7756_; 
v___x_7755_ = lean_unbox_uint32(v_fst_7578_);
v___x_7756_ = lean_uint32_dec_lt(v___x_7755_, v___y_7754_);
if (v___x_7756_ == 0)
{
uint32_t v___x_7757_; 
v___x_7757_ = lean_unbox_uint32(v_fst_7578_);
lean_dec(v_fst_7578_);
v_peak_7728_ = v___x_7757_;
goto v___jp_7727_;
}
else
{
lean_dec(v_fst_7578_);
v_peak_7728_ = v___y_7754_;
goto v___jp_7727_;
}
}
}
else
{
uint8_t v___x_7761_; double v___x_7762_; lean_object* v___x_7763_; lean_object* v___x_7764_; lean_object* v___x_7765_; lean_object* v___x_7766_; 
lean_del_object(v___x_7581_);
lean_dec(v_snd_7579_);
lean_del_object(v___x_7576_);
v___x_7761_ = 0;
v___x_7762_ = lean_float_once(&lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00Submission_R24PortableF64_prepare_spec__0___closed__0, &lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00Submission_R24PortableF64_prepare_spec__0___closed__0_once, _init_lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00Submission_R24PortableF64_prepare_spec__0___closed__0);
v___x_7763_ = lean_float_array_push(v_fst_7574_, v___x_7762_);
v___x_7764_ = lean_box(v___x_7761_);
v___x_7765_ = lean_alloc_ctor(0, 2, 0);
lean_ctor_set(v___x_7765_, 0, v_fst_7578_);
lean_ctor_set(v___x_7765_, 1, v___x_7764_);
v___x_7766_ = lean_alloc_ctor(0, 2, 0);
lean_ctor_set(v___x_7766_, 0, v___x_7763_);
lean_ctor_set(v___x_7766_, 1, v___x_7765_);
v_a_7568_ = v___x_7766_;
goto v___jp_7567_;
}
v___jp_7583_:
{
double v___x_7586_; lean_object* v___x_7587_; lean_object* v___x_7588_; lean_object* v___x_7590_; 
v___x_7586_ = lean_float_of_bits(v___y_7585_);
v___x_7587_ = lean_float_array_push(v_fst_7574_, v___x_7586_);
v___x_7588_ = lean_box_uint32(v___y_7584_);
if (v_isShared_7582_ == 0)
{
lean_ctor_set(v___x_7581_, 0, v___x_7588_);
v___x_7590_ = v___x_7581_;
goto v_reusejp_7589_;
}
else
{
lean_object* v_reuseFailAlloc_7594_; 
v_reuseFailAlloc_7594_ = lean_alloc_ctor(0, 2, 0);
lean_ctor_set(v_reuseFailAlloc_7594_, 0, v___x_7588_);
lean_ctor_set(v_reuseFailAlloc_7594_, 1, v_snd_7579_);
v___x_7590_ = v_reuseFailAlloc_7594_;
goto v_reusejp_7589_;
}
v_reusejp_7589_:
{
lean_object* v___x_7592_; 
if (v_isShared_7577_ == 0)
{
lean_ctor_set(v___x_7576_, 1, v___x_7590_);
lean_ctor_set(v___x_7576_, 0, v___x_7587_);
v___x_7592_ = v___x_7576_;
goto v_reusejp_7591_;
}
else
{
lean_object* v_reuseFailAlloc_7593_; 
v_reuseFailAlloc_7593_ = lean_alloc_ctor(0, 2, 0);
lean_ctor_set(v_reuseFailAlloc_7593_, 0, v___x_7587_);
lean_ctor_set(v_reuseFailAlloc_7593_, 1, v___x_7590_);
v___x_7592_ = v_reuseFailAlloc_7593_;
goto v_reusejp_7591_;
}
v_reusejp_7591_:
{
v_a_7568_ = v___x_7592_;
goto v___jp_7567_;
}
}
}
v___jp_7595_:
{
uint64_t v___x_7600_; uint64_t v___x_7601_; uint64_t v___x_7602_; uint64_t v___x_7603_; uint64_t v___x_7604_; uint64_t v___x_7605_; uint64_t v___x_7606_; uint64_t v___x_7607_; uint64_t v___x_7608_; uint64_t v___x_7609_; uint64_t v___x_7610_; 
v___x_7600_ = 874ULL;
v___x_7601_ = lean_uint64_add(v___y_7599_, v___x_7600_);
v___x_7602_ = 52ULL;
v___x_7603_ = lean_uint64_shift_left(v___x_7601_, v___x_7602_);
v___x_7604_ = lean_uint64_lor(v___y_7597_, v___x_7603_);
v___x_7605_ = 1ULL;
v___x_7606_ = lean_uint64_shift_left(v___x_7605_, v___y_7599_);
v___x_7607_ = lean_uint64_sub(v___y_7598_, v___x_7606_);
v___x_7608_ = lean_uint64_sub(v___x_7602_, v___y_7599_);
v___x_7609_ = lean_uint64_shift_left(v___x_7607_, v___x_7608_);
v___x_7610_ = lean_uint64_lor(v___x_7604_, v___x_7609_);
v___y_7584_ = v___y_7596_;
v___y_7585_ = v___x_7610_;
goto v___jp_7583_;
}
v___jp_7611_:
{
uint64_t v___x_7618_; uint64_t v___x_7619_; uint8_t v___x_7620_; 
v___x_7618_ = 1ULL;
v___x_7619_ = lean_uint64_shift_right(v___y_7614_, v___x_7618_);
v___x_7620_ = lean_uint64_dec_eq(v___x_7619_, v___y_7615_);
if (v___x_7620_ == 0)
{
uint64_t v___x_7621_; 
v___x_7621_ = lean_uint64_add(v___y_7617_, v___x_7618_);
v___y_7596_ = v___y_7612_;
v___y_7597_ = v___y_7613_;
v___y_7598_ = v___y_7616_;
v___y_7599_ = v___x_7621_;
goto v___jp_7595_;
}
else
{
v___y_7596_ = v___y_7612_;
v___y_7597_ = v___y_7613_;
v___y_7598_ = v___y_7616_;
v___y_7599_ = v___y_7617_;
goto v___jp_7595_;
}
}
v___jp_7622_:
{
uint64_t v___x_7631_; uint8_t v___x_7632_; 
v___x_7631_ = lean_uint64_shift_right(v___y_7629_, v___y_7626_);
v___x_7632_ = lean_uint64_dec_eq(v___x_7631_, v___y_7627_);
if (v___x_7632_ == 0)
{
uint64_t v___x_7633_; 
v___x_7633_ = lean_uint64_add(v___y_7624_, v___y_7626_);
v___y_7612_ = v___y_7623_;
v___y_7613_ = v___y_7625_;
v___y_7614_ = v___y_7630_;
v___y_7615_ = v___y_7627_;
v___y_7616_ = v___y_7628_;
v___y_7617_ = v___x_7633_;
goto v___jp_7611_;
}
else
{
v___y_7612_ = v___y_7623_;
v___y_7613_ = v___y_7625_;
v___y_7614_ = v___y_7630_;
v___y_7615_ = v___y_7627_;
v___y_7616_ = v___y_7628_;
v___y_7617_ = v___y_7624_;
goto v___jp_7611_;
}
}
v___jp_7634_:
{
uint64_t v___x_7641_; uint64_t v___x_7642_; uint8_t v___x_7643_; 
v___x_7641_ = 2ULL;
v___x_7642_ = lean_uint64_shift_right(v___y_7639_, v___x_7641_);
v___x_7643_ = lean_uint64_dec_eq(v___x_7642_, v___y_7637_);
if (v___x_7643_ == 0)
{
v___y_7623_ = v___y_7635_;
v___y_7624_ = v___y_7640_;
v___y_7625_ = v___y_7636_;
v___y_7626_ = v___x_7641_;
v___y_7627_ = v___y_7637_;
v___y_7628_ = v___y_7638_;
v___y_7629_ = v___y_7639_;
v___y_7630_ = v___x_7642_;
goto v___jp_7622_;
}
else
{
v___y_7623_ = v___y_7635_;
v___y_7624_ = v___y_7640_;
v___y_7625_ = v___y_7636_;
v___y_7626_ = v___x_7641_;
v___y_7627_ = v___y_7637_;
v___y_7628_ = v___y_7638_;
v___y_7629_ = v___y_7639_;
v___y_7630_ = v___y_7639_;
goto v___jp_7622_;
}
}
v___jp_7644_:
{
uint64_t v___x_7653_; uint8_t v___x_7654_; 
v___x_7653_ = lean_uint64_shift_right(v___y_7649_, v___y_7646_);
v___x_7654_ = lean_uint64_dec_eq(v___x_7653_, v___y_7650_);
if (v___x_7654_ == 0)
{
uint64_t v___x_7655_; 
v___x_7655_ = lean_uint64_add(v___y_7645_, v___y_7646_);
v___y_7635_ = v___y_7647_;
v___y_7636_ = v___y_7648_;
v___y_7637_ = v___y_7650_;
v___y_7638_ = v___y_7651_;
v___y_7639_ = v___y_7652_;
v___y_7640_ = v___x_7655_;
goto v___jp_7634_;
}
else
{
v___y_7635_ = v___y_7647_;
v___y_7636_ = v___y_7648_;
v___y_7637_ = v___y_7650_;
v___y_7638_ = v___y_7651_;
v___y_7639_ = v___y_7652_;
v___y_7640_ = v___y_7645_;
goto v___jp_7634_;
}
}
v___jp_7656_:
{
uint64_t v___x_7663_; uint64_t v___x_7664_; uint8_t v___x_7665_; 
v___x_7663_ = 4ULL;
v___x_7664_ = lean_uint64_shift_right(v___y_7659_, v___x_7663_);
v___x_7665_ = lean_uint64_dec_eq(v___x_7664_, v___y_7660_);
if (v___x_7665_ == 0)
{
v___y_7645_ = v___y_7662_;
v___y_7646_ = v___x_7663_;
v___y_7647_ = v___y_7657_;
v___y_7648_ = v___y_7658_;
v___y_7649_ = v___y_7659_;
v___y_7650_ = v___y_7660_;
v___y_7651_ = v___y_7661_;
v___y_7652_ = v___x_7664_;
goto v___jp_7644_;
}
else
{
v___y_7645_ = v___y_7662_;
v___y_7646_ = v___x_7663_;
v___y_7647_ = v___y_7657_;
v___y_7648_ = v___y_7658_;
v___y_7649_ = v___y_7659_;
v___y_7650_ = v___y_7660_;
v___y_7651_ = v___y_7661_;
v___y_7652_ = v___y_7659_;
goto v___jp_7644_;
}
}
v___jp_7666_:
{
uint64_t v___x_7675_; uint8_t v___x_7676_; 
v___x_7675_ = lean_uint64_shift_right(v___y_7669_, v___y_7673_);
v___x_7676_ = lean_uint64_dec_eq(v___x_7675_, v___y_7670_);
if (v___x_7676_ == 0)
{
uint64_t v___x_7677_; 
v___x_7677_ = lean_uint64_add(v___y_7671_, v___y_7673_);
v___y_7657_ = v___y_7667_;
v___y_7658_ = v___y_7668_;
v___y_7659_ = v___y_7674_;
v___y_7660_ = v___y_7670_;
v___y_7661_ = v___y_7672_;
v___y_7662_ = v___x_7677_;
goto v___jp_7656_;
}
else
{
v___y_7657_ = v___y_7667_;
v___y_7658_ = v___y_7668_;
v___y_7659_ = v___y_7674_;
v___y_7660_ = v___y_7670_;
v___y_7661_ = v___y_7672_;
v___y_7662_ = v___y_7671_;
goto v___jp_7656_;
}
}
v___jp_7678_:
{
uint64_t v___x_7685_; uint64_t v___x_7686_; uint8_t v___x_7687_; 
v___x_7685_ = 8ULL;
v___x_7686_ = lean_uint64_shift_right(v___y_7681_, v___x_7685_);
v___x_7687_ = lean_uint64_dec_eq(v___x_7686_, v___y_7682_);
if (v___x_7687_ == 0)
{
v___y_7667_ = v___y_7679_;
v___y_7668_ = v___y_7680_;
v___y_7669_ = v___y_7681_;
v___y_7670_ = v___y_7682_;
v___y_7671_ = v___y_7684_;
v___y_7672_ = v___y_7683_;
v___y_7673_ = v___x_7685_;
v___y_7674_ = v___x_7686_;
goto v___jp_7666_;
}
else
{
v___y_7667_ = v___y_7679_;
v___y_7668_ = v___y_7680_;
v___y_7669_ = v___y_7681_;
v___y_7670_ = v___y_7682_;
v___y_7671_ = v___y_7684_;
v___y_7672_ = v___y_7683_;
v___y_7673_ = v___x_7685_;
v___y_7674_ = v___y_7681_;
goto v___jp_7666_;
}
}
v___jp_7688_:
{
uint64_t v___x_7697_; uint8_t v___x_7698_; 
v___x_7697_ = lean_uint64_shift_right(v___y_7695_, v___y_7694_);
v___x_7698_ = lean_uint64_dec_eq(v___x_7697_, v___y_7692_);
if (v___x_7698_ == 0)
{
uint64_t v___x_7699_; 
v___x_7699_ = lean_uint64_add(v___y_7689_, v___y_7694_);
v___y_7679_ = v___y_7690_;
v___y_7680_ = v___y_7691_;
v___y_7681_ = v___y_7696_;
v___y_7682_ = v___y_7692_;
v___y_7683_ = v___y_7693_;
v___y_7684_ = v___x_7699_;
goto v___jp_7678_;
}
else
{
v___y_7679_ = v___y_7690_;
v___y_7680_ = v___y_7691_;
v___y_7681_ = v___y_7696_;
v___y_7682_ = v___y_7692_;
v___y_7683_ = v___y_7693_;
v___y_7684_ = v___y_7689_;
goto v___jp_7678_;
}
}
v___jp_7700_:
{
uint64_t v___x_7707_; uint64_t v___x_7708_; uint8_t v___x_7709_; 
v___x_7707_ = 16ULL;
v___x_7708_ = lean_uint64_shift_right(v___y_7705_, v___x_7707_);
v___x_7709_ = lean_uint64_dec_eq(v___x_7708_, v___y_7703_);
if (v___x_7709_ == 0)
{
v___y_7689_ = v___y_7706_;
v___y_7690_ = v___y_7701_;
v___y_7691_ = v___y_7702_;
v___y_7692_ = v___y_7703_;
v___y_7693_ = v___y_7704_;
v___y_7694_ = v___x_7707_;
v___y_7695_ = v___y_7705_;
v___y_7696_ = v___x_7708_;
goto v___jp_7688_;
}
else
{
v___y_7689_ = v___y_7706_;
v___y_7690_ = v___y_7701_;
v___y_7691_ = v___y_7702_;
v___y_7692_ = v___y_7703_;
v___y_7693_ = v___y_7704_;
v___y_7694_ = v___x_7707_;
v___y_7695_ = v___y_7705_;
v___y_7696_ = v___y_7705_;
goto v___jp_7688_;
}
}
v___jp_7710_:
{
uint64_t v___x_7717_; uint8_t v___x_7718_; 
v___x_7717_ = lean_uint64_shift_right(v___y_7714_, v___y_7715_);
v___x_7718_ = lean_uint64_dec_eq(v___x_7717_, v___y_7713_);
if (v___x_7718_ == 0)
{
v___y_7701_ = v___y_7711_;
v___y_7702_ = v___y_7712_;
v___y_7703_ = v___y_7713_;
v___y_7704_ = v___y_7714_;
v___y_7705_ = v___y_7716_;
v___y_7706_ = v___y_7715_;
goto v___jp_7700_;
}
else
{
v___y_7701_ = v___y_7711_;
v___y_7702_ = v___y_7712_;
v___y_7703_ = v___y_7713_;
v___y_7704_ = v___y_7714_;
v___y_7705_ = v___y_7716_;
v___y_7706_ = v___y_7713_;
goto v___jp_7700_;
}
}
}
}
}
v___jp_7567_:
{
size_t v___x_7569_; size_t v___x_7570_; 
v___x_7569_ = ((size_t)1ULL);
v___x_7570_ = lean_usize_add(v_i_7565_, v___x_7569_);
v_i_7565_ = v___x_7570_;
v_b_7566_ = v_a_7568_;
goto _start;
}
}
}
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00Submission_R24PortableF64_prepare_spec__0___boxed(lean_object* v_as_7769_, lean_object* v_sz_7770_, lean_object* v_i_7771_, lean_object* v_b_7772_){
_start:
{
size_t v_sz_boxed_7773_; size_t v_i_boxed_7774_; lean_object* v_res_7775_; 
v_sz_boxed_7773_ = lean_unbox_usize(v_sz_7770_);
lean_dec(v_sz_7770_);
v_i_boxed_7774_ = lean_unbox_usize(v_i_7771_);
lean_dec(v_i_7771_);
v_res_7775_ = lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00Submission_R24PortableF64_prepare_spec__0(v_as_7769_, v_sz_boxed_7773_, v_i_boxed_7774_, v_b_7772_);
lean_dec_ref(v_as_7769_);
return v_res_7775_;
}
}
static lean_object* _init_lp_competition_Submission_R24PortableF64_prepare___closed__0(void){
_start:
{
uint8_t v_valid_7776_; lean_object* v___x_7777_; lean_object* v___x_7778_; lean_object* v___x_7779_; 
v_valid_7776_ = 1;
v___x_7777_ = lp_competition_Submission_R24ExactDotCost_prepareOperand___closed__2___boxed__const__1;
v___x_7778_ = lean_box(v_valid_7776_);
v___x_7779_ = lean_alloc_ctor(0, 2, 0);
lean_ctor_set(v___x_7779_, 0, v___x_7777_);
lean_ctor_set(v___x_7779_, 1, v___x_7778_);
return v___x_7779_;
}
}
static lean_object* _init_lp_competition_Submission_R24PortableF64_prepare___closed__1(void){
_start:
{
lean_object* v___x_7780_; lean_object* v___x_7781_; 
v___x_7780_ = lean_unsigned_to_nat(0u);
v___x_7781_ = lean_mk_empty_float_array(v___x_7780_);
return v___x_7781_;
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_R24PortableF64_prepare(lean_object* v_raw_7782_){
_start:
{
lean_object* v___x_7783_; lean_object* v___x_7784_; uint8_t v___x_7785_; 
v___x_7783_ = lean_unsigned_to_nat(1073741824u);
v___x_7784_ = lean_array_get_size(v_raw_7782_);
v___x_7785_ = lean_nat_dec_lt(v___x_7783_, v___x_7784_);
if (v___x_7785_ == 0)
{
lean_object* v_values_7786_; lean_object* v___x_7787_; lean_object* v___x_7788_; size_t v_sz_7789_; size_t v___x_7790_; lean_object* v___x_7791_; lean_object* v_snd_7792_; lean_object* v_fst_7793_; lean_object* v_fst_7794_; lean_object* v_snd_7795_; lean_object* v___x_7796_; uint32_t v___x_7797_; uint8_t v___x_7798_; 
v_values_7786_ = lean_mk_empty_float_array(v___x_7784_);
v___x_7787_ = lean_obj_once(&lp_competition_Submission_R24PortableF64_prepare___closed__0, &lp_competition_Submission_R24PortableF64_prepare___closed__0_once, _init_lp_competition_Submission_R24PortableF64_prepare___closed__0);
v___x_7788_ = lean_alloc_ctor(0, 2, 0);
lean_ctor_set(v___x_7788_, 0, v_values_7786_);
lean_ctor_set(v___x_7788_, 1, v___x_7787_);
v_sz_7789_ = lean_array_size(v_raw_7782_);
v___x_7790_ = ((size_t)0ULL);
v___x_7791_ = lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00Submission_R24PortableF64_prepare_spec__0(v_raw_7782_, v_sz_7789_, v___x_7790_, v___x_7788_);
v_snd_7792_ = lean_ctor_get(v___x_7791_, 1);
lean_inc(v_snd_7792_);
v_fst_7793_ = lean_ctor_get(v___x_7791_, 0);
lean_inc(v_fst_7793_);
lean_dec_ref(v___x_7791_);
v_fst_7794_ = lean_ctor_get(v_snd_7792_, 0);
lean_inc(v_fst_7794_);
v_snd_7795_ = lean_ctor_get(v_snd_7792_, 1);
lean_inc(v_snd_7795_);
lean_dec(v_snd_7792_);
v___x_7796_ = lean_alloc_ctor(0, 2, 5);
lean_ctor_set(v___x_7796_, 0, v_raw_7782_);
lean_ctor_set(v___x_7796_, 1, v_fst_7793_);
v___x_7797_ = lean_unbox_uint32(v_fst_7794_);
lean_dec(v_fst_7794_);
lean_ctor_set_uint32(v___x_7796_, sizeof(void*)*2, v___x_7797_);
v___x_7798_ = lean_unbox(v_snd_7795_);
lean_dec(v_snd_7795_);
lean_ctor_set_uint8(v___x_7796_, sizeof(void*)*2 + 4, v___x_7798_);
return v___x_7796_;
}
else
{
lean_object* v___x_7799_; uint32_t v___x_7800_; uint8_t v___x_7801_; lean_object* v___x_7802_; 
v___x_7799_ = lean_obj_once(&lp_competition_Submission_R24PortableF64_prepare___closed__1, &lp_competition_Submission_R24PortableF64_prepare___closed__1_once, _init_lp_competition_Submission_R24PortableF64_prepare___closed__1);
v___x_7800_ = 0;
v___x_7801_ = 0;
v___x_7802_ = lean_alloc_ctor(0, 2, 5);
lean_ctor_set(v___x_7802_, 0, v_raw_7782_);
lean_ctor_set(v___x_7802_, 1, v___x_7799_);
lean_ctor_set_uint32(v___x_7802_, sizeof(void*)*2, v___x_7800_);
lean_ctor_set_uint8(v___x_7802_, sizeof(void*)*2 + 4, v___x_7801_);
return v___x_7802_;
}
}
}
LEAN_EXPORT uint64_t lp_competition_Submission_R24PortableF64_ceilLog2(lean_object* v_n_7803_){
_start:
{
lean_object* v___x_7804_; uint8_t v___x_7805_; 
v___x_7804_ = lean_unsigned_to_nat(1u);
v___x_7805_ = lean_nat_dec_le(v_n_7803_, v___x_7804_);
if (v___x_7805_ == 0)
{
uint64_t v___x_7806_; uint64_t v___x_7807_; uint64_t v___y_7809_; uint64_t v___y_7810_; uint64_t v___y_7818_; uint64_t v___y_7819_; uint64_t v___y_7820_; uint64_t v___y_7821_; uint64_t v___y_7827_; uint64_t v___y_7828_; uint64_t v___y_7834_; uint64_t v___y_7835_; uint64_t v___y_7836_; uint64_t v___y_7837_; uint64_t v___y_7843_; uint64_t v___y_7844_; uint64_t v___y_7850_; uint64_t v___y_7851_; uint64_t v___y_7852_; uint64_t v___y_7853_; uint64_t v___y_7859_; uint64_t v___y_7860_; uint64_t v___y_7866_; uint64_t v___y_7867_; uint64_t v___y_7868_; uint64_t v___y_7869_; uint64_t v___y_7875_; uint64_t v___y_7876_; uint64_t v___x_7881_; uint64_t v___x_7882_; uint64_t v___y_7884_; uint64_t v___x_7888_; uint64_t v___x_7889_; uint8_t v___x_7890_; 
v___x_7806_ = lean_uint64_of_nat(v_n_7803_);
v___x_7807_ = 1ULL;
v___x_7881_ = lean_uint64_sub(v___x_7806_, v___x_7807_);
v___x_7882_ = 32ULL;
v___x_7888_ = lean_uint64_shift_right(v___x_7881_, v___x_7882_);
v___x_7889_ = 0ULL;
v___x_7890_ = lean_uint64_dec_eq(v___x_7888_, v___x_7889_);
if (v___x_7890_ == 0)
{
v___y_7884_ = v___x_7888_;
goto v___jp_7883_;
}
else
{
v___y_7884_ = v___x_7881_;
goto v___jp_7883_;
}
v___jp_7808_:
{
uint64_t v___x_7811_; uint64_t v___x_7812_; uint8_t v___x_7813_; 
v___x_7811_ = lean_uint64_shift_right(v___y_7809_, v___x_7807_);
v___x_7812_ = 0ULL;
v___x_7813_ = lean_uint64_dec_eq(v___x_7811_, v___x_7812_);
if (v___x_7813_ == 0)
{
uint64_t v___x_7814_; uint64_t v___x_7815_; 
v___x_7814_ = lean_uint64_add(v___y_7810_, v___x_7807_);
v___x_7815_ = lean_uint64_add(v___x_7814_, v___x_7807_);
return v___x_7815_;
}
else
{
uint64_t v___x_7816_; 
v___x_7816_ = lean_uint64_add(v___y_7810_, v___x_7807_);
return v___x_7816_;
}
}
v___jp_7817_:
{
uint64_t v___x_7822_; uint64_t v___x_7823_; uint8_t v___x_7824_; 
v___x_7822_ = lean_uint64_shift_right(v___y_7818_, v___y_7820_);
v___x_7823_ = 0ULL;
v___x_7824_ = lean_uint64_dec_eq(v___x_7822_, v___x_7823_);
if (v___x_7824_ == 0)
{
uint64_t v___x_7825_; 
v___x_7825_ = lean_uint64_add(v___y_7819_, v___y_7820_);
v___y_7809_ = v___y_7821_;
v___y_7810_ = v___x_7825_;
goto v___jp_7808_;
}
else
{
v___y_7809_ = v___y_7821_;
v___y_7810_ = v___y_7819_;
goto v___jp_7808_;
}
}
v___jp_7826_:
{
uint64_t v___x_7829_; uint64_t v___x_7830_; uint64_t v___x_7831_; uint8_t v___x_7832_; 
v___x_7829_ = 2ULL;
v___x_7830_ = lean_uint64_shift_right(v___y_7827_, v___x_7829_);
v___x_7831_ = 0ULL;
v___x_7832_ = lean_uint64_dec_eq(v___x_7830_, v___x_7831_);
if (v___x_7832_ == 0)
{
v___y_7818_ = v___y_7827_;
v___y_7819_ = v___y_7828_;
v___y_7820_ = v___x_7829_;
v___y_7821_ = v___x_7830_;
goto v___jp_7817_;
}
else
{
v___y_7818_ = v___y_7827_;
v___y_7819_ = v___y_7828_;
v___y_7820_ = v___x_7829_;
v___y_7821_ = v___y_7827_;
goto v___jp_7817_;
}
}
v___jp_7833_:
{
uint64_t v___x_7838_; uint64_t v___x_7839_; uint8_t v___x_7840_; 
v___x_7838_ = lean_uint64_shift_right(v___y_7836_, v___y_7834_);
v___x_7839_ = 0ULL;
v___x_7840_ = lean_uint64_dec_eq(v___x_7838_, v___x_7839_);
if (v___x_7840_ == 0)
{
uint64_t v___x_7841_; 
v___x_7841_ = lean_uint64_add(v___y_7835_, v___y_7834_);
v___y_7827_ = v___y_7837_;
v___y_7828_ = v___x_7841_;
goto v___jp_7826_;
}
else
{
v___y_7827_ = v___y_7837_;
v___y_7828_ = v___y_7835_;
goto v___jp_7826_;
}
}
v___jp_7842_:
{
uint64_t v___x_7845_; uint64_t v___x_7846_; uint64_t v___x_7847_; uint8_t v___x_7848_; 
v___x_7845_ = 4ULL;
v___x_7846_ = lean_uint64_shift_right(v___y_7843_, v___x_7845_);
v___x_7847_ = 0ULL;
v___x_7848_ = lean_uint64_dec_eq(v___x_7846_, v___x_7847_);
if (v___x_7848_ == 0)
{
v___y_7834_ = v___x_7845_;
v___y_7835_ = v___y_7844_;
v___y_7836_ = v___y_7843_;
v___y_7837_ = v___x_7846_;
goto v___jp_7833_;
}
else
{
v___y_7834_ = v___x_7845_;
v___y_7835_ = v___y_7844_;
v___y_7836_ = v___y_7843_;
v___y_7837_ = v___y_7843_;
goto v___jp_7833_;
}
}
v___jp_7849_:
{
uint64_t v___x_7854_; uint64_t v___x_7855_; uint8_t v___x_7856_; 
v___x_7854_ = lean_uint64_shift_right(v___y_7852_, v___y_7850_);
v___x_7855_ = 0ULL;
v___x_7856_ = lean_uint64_dec_eq(v___x_7854_, v___x_7855_);
if (v___x_7856_ == 0)
{
uint64_t v___x_7857_; 
v___x_7857_ = lean_uint64_add(v___y_7851_, v___y_7850_);
v___y_7843_ = v___y_7853_;
v___y_7844_ = v___x_7857_;
goto v___jp_7842_;
}
else
{
v___y_7843_ = v___y_7853_;
v___y_7844_ = v___y_7851_;
goto v___jp_7842_;
}
}
v___jp_7858_:
{
uint64_t v___x_7861_; uint64_t v___x_7862_; uint64_t v___x_7863_; uint8_t v___x_7864_; 
v___x_7861_ = 8ULL;
v___x_7862_ = lean_uint64_shift_right(v___y_7859_, v___x_7861_);
v___x_7863_ = 0ULL;
v___x_7864_ = lean_uint64_dec_eq(v___x_7862_, v___x_7863_);
if (v___x_7864_ == 0)
{
v___y_7850_ = v___x_7861_;
v___y_7851_ = v___y_7860_;
v___y_7852_ = v___y_7859_;
v___y_7853_ = v___x_7862_;
goto v___jp_7849_;
}
else
{
v___y_7850_ = v___x_7861_;
v___y_7851_ = v___y_7860_;
v___y_7852_ = v___y_7859_;
v___y_7853_ = v___y_7859_;
goto v___jp_7849_;
}
}
v___jp_7865_:
{
uint64_t v___x_7870_; uint64_t v___x_7871_; uint8_t v___x_7872_; 
v___x_7870_ = lean_uint64_shift_right(v___y_7866_, v___y_7868_);
v___x_7871_ = 0ULL;
v___x_7872_ = lean_uint64_dec_eq(v___x_7870_, v___x_7871_);
if (v___x_7872_ == 0)
{
uint64_t v___x_7873_; 
v___x_7873_ = lean_uint64_add(v___y_7867_, v___y_7868_);
v___y_7859_ = v___y_7869_;
v___y_7860_ = v___x_7873_;
goto v___jp_7858_;
}
else
{
v___y_7859_ = v___y_7869_;
v___y_7860_ = v___y_7867_;
goto v___jp_7858_;
}
}
v___jp_7874_:
{
uint64_t v___x_7877_; uint64_t v___x_7878_; uint64_t v___x_7879_; uint8_t v___x_7880_; 
v___x_7877_ = 16ULL;
v___x_7878_ = lean_uint64_shift_right(v___y_7875_, v___x_7877_);
v___x_7879_ = 0ULL;
v___x_7880_ = lean_uint64_dec_eq(v___x_7878_, v___x_7879_);
if (v___x_7880_ == 0)
{
v___y_7866_ = v___y_7875_;
v___y_7867_ = v___y_7876_;
v___y_7868_ = v___x_7877_;
v___y_7869_ = v___x_7878_;
goto v___jp_7865_;
}
else
{
v___y_7866_ = v___y_7875_;
v___y_7867_ = v___y_7876_;
v___y_7868_ = v___x_7877_;
v___y_7869_ = v___y_7875_;
goto v___jp_7865_;
}
}
v___jp_7883_:
{
uint64_t v___x_7885_; uint64_t v___x_7886_; uint8_t v___x_7887_; 
v___x_7885_ = lean_uint64_shift_right(v___x_7881_, v___x_7882_);
v___x_7886_ = 0ULL;
v___x_7887_ = lean_uint64_dec_eq(v___x_7885_, v___x_7886_);
if (v___x_7887_ == 0)
{
v___y_7875_ = v___y_7884_;
v___y_7876_ = v___x_7882_;
goto v___jp_7874_;
}
else
{
v___y_7875_ = v___y_7884_;
v___y_7876_ = v___x_7886_;
goto v___jp_7874_;
}
}
}
else
{
uint64_t v___x_7891_; 
v___x_7891_ = 0ULL;
return v___x_7891_;
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_R24PortableF64_ceilLog2___boxed(lean_object* v_n_7892_){
_start:
{
uint64_t v_res_7893_; lean_object* v_r_7894_; 
v_res_7893_ = lp_competition_Submission_R24PortableF64_ceilLog2(v_n_7892_);
lean_dec(v_n_7892_);
v_r_7894_ = lean_box_uint64(v_res_7893_);
return v_r_7894_;
}
}
LEAN_EXPORT uint8_t lp_competition_Submission_R24PortableF64_finite64(uint64_t v_word_7895_){
_start:
{
uint64_t v___x_7896_; uint64_t v___x_7897_; uint8_t v___x_7898_; 
v___x_7896_ = 9218868437227405312ULL;
v___x_7897_ = lean_uint64_land(v_word_7895_, v___x_7896_);
v___x_7898_ = lean_uint64_dec_eq(v___x_7897_, v___x_7896_);
if (v___x_7898_ == 0)
{
uint8_t v___x_7899_; 
v___x_7899_ = 1;
return v___x_7899_;
}
else
{
uint8_t v___x_7900_; 
v___x_7900_ = 0;
return v___x_7900_;
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_R24PortableF64_finite64___boxed(lean_object* v_word_7901_){
_start:
{
uint64_t v_word_boxed_7902_; uint8_t v_res_7903_; lean_object* v_r_7904_; 
v_word_boxed_7902_ = lean_unbox_uint64(v_word_7901_);
lean_dec_ref(v_word_7901_);
v_res_7903_ = lp_competition_Submission_R24PortableF64_finite64(v_word_boxed_7902_);
v_r_7904_ = lean_box(v_res_7903_);
return v_r_7904_;
}
}
LEAN_EXPORT uint32_t lp_competition_Submission_R24PortableF64_proposal(uint64_t v_word_7905_){
_start:
{
uint64_t v___x_7906_; uint64_t v___x_7907_; uint64_t v___x_7908_; uint64_t v___x_7909_; uint64_t v___x_7910_; uint64_t v___x_7911_; uint32_t v___x_7912_; uint32_t v___x_7913_; uint32_t v___x_7914_; uint32_t v___x_7915_; uint32_t v_magnitude_7916_; uint64_t v___x_7917_; uint64_t v___x_7918_; uint32_t v___x_7919_; uint32_t v___x_7920_; uint32_t v___x_7921_; uint32_t v___x_7922_; 
v___x_7906_ = 9223372036854775807ULL;
v___x_7907_ = lean_uint64_land(v_word_7905_, v___x_7906_);
v___x_7908_ = 268435456ULL;
v___x_7909_ = lean_uint64_add(v___x_7907_, v___x_7908_);
v___x_7910_ = 29ULL;
v___x_7911_ = lean_uint64_shift_right(v___x_7909_, v___x_7910_);
v___x_7912_ = lean_uint64_to_uint32(v___x_7911_);
v___x_7913_ = 3221225472;
v___x_7914_ = lean_uint32_sub(v___x_7912_, v___x_7913_);
v___x_7915_ = 2147483647;
v_magnitude_7916_ = lean_uint32_land(v___x_7914_, v___x_7915_);
v___x_7917_ = 32ULL;
v___x_7918_ = lean_uint64_shift_right(v_word_7905_, v___x_7917_);
v___x_7919_ = lean_uint64_to_uint32(v___x_7918_);
v___x_7920_ = 2147483648;
v___x_7921_ = lean_uint32_land(v___x_7919_, v___x_7920_);
v___x_7922_ = lean_uint32_lor(v___x_7921_, v_magnitude_7916_);
return v___x_7922_;
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_R24PortableF64_proposal___boxed(lean_object* v_word_7923_){
_start:
{
uint64_t v_word_boxed_7924_; uint32_t v_res_7925_; lean_object* v_r_7926_; 
v_word_boxed_7924_ = lean_unbox_uint64(v_word_7923_);
lean_dec_ref(v_word_7923_);
v_res_7925_ = lp_competition_Submission_R24PortableF64_proposal(v_word_boxed_7924_);
v_r_7926_ = lean_box_uint32(v_res_7925_);
return v_r_7926_;
}
}
LEAN_EXPORT uint64_t lp_competition_Submission_R24PortableF64_orderKey(uint64_t v_word_7927_){
_start:
{
uint64_t v___x_7928_; uint64_t v___x_7929_; uint64_t v___x_7930_; uint8_t v___x_7931_; 
v___x_7928_ = 9223372036854775808ULL;
v___x_7929_ = lean_uint64_land(v_word_7927_, v___x_7928_);
v___x_7930_ = 0ULL;
v___x_7931_ = lean_uint64_dec_eq(v___x_7929_, v___x_7930_);
if (v___x_7931_ == 0)
{
uint64_t v___x_7932_; uint64_t v___x_7933_; 
v___x_7932_ = 18446744073709551615ULL;
v___x_7933_ = lean_uint64_xor(v_word_7927_, v___x_7932_);
return v___x_7933_;
}
else
{
uint64_t v___x_7934_; 
v___x_7934_ = lean_uint64_xor(v_word_7927_, v___x_7928_);
return v___x_7934_;
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_R24PortableF64_orderKey___boxed(lean_object* v_word_7935_){
_start:
{
uint64_t v_word_boxed_7936_; uint64_t v_res_7937_; lean_object* v_r_7938_; 
v_word_boxed_7936_ = lean_unbox_uint64(v_word_7935_);
lean_dec_ref(v_word_7935_);
v_res_7937_ = lp_competition_Submission_R24PortableF64_orderKey(v_word_boxed_7936_);
v_r_7938_ = lean_box_uint64(v_res_7937_);
return v_r_7938_;
}
}
LEAN_EXPORT uint8_t lp_competition_Submission_R24PortableF64_certify(double v_sum_7939_, double v_radius_7940_, uint64_t v_sumWord_7941_, uint32_t v_guess_7942_){
_start:
{
uint64_t v___y_7944_; uint64_t v___y_7945_; uint64_t v___y_7956_; uint64_t v___y_7957_; uint64_t v___y_7958_; uint64_t v___y_7959_; uint64_t v___y_7969_; uint64_t v___y_7970_; uint64_t v___y_7971_; uint64_t v___y_7972_; uint64_t v___y_7981_; uint64_t v___y_7982_; uint64_t v___y_7983_; uint64_t v___y_7984_; uint64_t v___y_7993_; uint64_t v___y_7994_; uint64_t v___y_7995_; uint64_t v___y_7996_; uint64_t v___y_8001_; uint64_t v___y_8002_; uint64_t v___y_8003_; uint64_t v___y_8004_; uint8_t v___y_8005_; uint32_t v___x_8006_; uint32_t v_magnitude_8007_; uint32_t v___x_8008_; uint32_t v___x_8009_; uint32_t v___x_8010_; uint32_t v_e_8011_; uint32_t v___x_8012_; uint8_t v___y_8014_; uint64_t v___y_8015_; uint8_t v___y_8016_; uint64_t v___y_8017_; uint64_t v___y_8018_; uint64_t v___y_8019_; uint64_t v___y_8027_; uint8_t v___y_8028_; uint64_t v___y_8029_; uint8_t v___y_8030_; uint8_t v___y_8047_; uint8_t v___x_8061_; 
v___x_8006_ = 2147483647;
v_magnitude_8007_ = lean_uint32_land(v_guess_7942_, v___x_8006_);
v___x_8008_ = 23;
v___x_8009_ = lean_uint32_shift_right(v_magnitude_8007_, v___x_8008_);
v___x_8010_ = 255;
v_e_8011_ = lean_uint32_land(v___x_8009_, v___x_8010_);
v___x_8012_ = 0;
v___x_8061_ = lean_uint32_dec_eq(v_e_8011_, v___x_8012_);
if (v___x_8061_ == 0)
{
uint8_t v___x_8062_; 
v___x_8062_ = lean_uint32_dec_eq(v_e_8011_, v___x_8010_);
v___y_8047_ = v___x_8062_;
goto v___jp_8046_;
}
else
{
v___y_8047_ = v___x_8061_;
goto v___jp_8046_;
}
v___jp_7943_:
{
uint64_t v___x_7946_; uint64_t v___x_7947_; uint64_t v___x_7948_; uint8_t v___x_7949_; 
v___x_7946_ = 9223372036854775808ULL;
v___x_7947_ = lean_uint64_land(v___y_7944_, v___x_7946_);
v___x_7948_ = 0ULL;
v___x_7949_ = lean_uint64_dec_eq(v___x_7947_, v___x_7948_);
if (v___x_7949_ == 0)
{
uint64_t v___x_7950_; uint64_t v___x_7951_; uint8_t v___x_7952_; 
v___x_7950_ = 18446744073709551615ULL;
v___x_7951_ = lean_uint64_xor(v___y_7944_, v___x_7950_);
v___x_7952_ = lean_uint64_dec_lt(v___y_7945_, v___x_7951_);
return v___x_7952_;
}
else
{
uint64_t v___x_7953_; uint8_t v___x_7954_; 
v___x_7953_ = lean_uint64_xor(v___y_7944_, v___x_7946_);
v___x_7954_ = lean_uint64_dec_lt(v___y_7945_, v___x_7953_);
return v___x_7954_;
}
}
v___jp_7955_:
{
uint8_t v___x_7960_; 
v___x_7960_ = lean_uint64_dec_lt(v___y_7956_, v___y_7959_);
if (v___x_7960_ == 0)
{
return v___x_7960_;
}
else
{
uint64_t v___x_7961_; uint64_t v___x_7962_; uint64_t v___x_7963_; uint8_t v___x_7964_; 
v___x_7961_ = 9223372036854775808ULL;
v___x_7962_ = lean_uint64_land(v___y_7957_, v___x_7961_);
v___x_7963_ = 0ULL;
v___x_7964_ = lean_uint64_dec_eq(v___x_7962_, v___x_7963_);
if (v___x_7964_ == 0)
{
uint64_t v___x_7965_; uint64_t v___x_7966_; 
v___x_7965_ = 18446744073709551615ULL;
v___x_7966_ = lean_uint64_xor(v___y_7957_, v___x_7965_);
v___y_7944_ = v___y_7958_;
v___y_7945_ = v___x_7966_;
goto v___jp_7943_;
}
else
{
uint64_t v___x_7967_; 
v___x_7967_ = lean_uint64_xor(v___y_7957_, v___x_7961_);
v___y_7944_ = v___y_7958_;
v___y_7945_ = v___x_7967_;
goto v___jp_7943_;
}
}
}
v___jp_7968_:
{
uint64_t v___x_7973_; uint64_t v___x_7974_; uint64_t v___x_7975_; uint8_t v___x_7976_; 
v___x_7973_ = 9223372036854775808ULL;
v___x_7974_ = lean_uint64_land(v___y_7969_, v___x_7973_);
v___x_7975_ = 0ULL;
v___x_7976_ = lean_uint64_dec_eq(v___x_7974_, v___x_7975_);
if (v___x_7976_ == 0)
{
uint64_t v___x_7977_; uint64_t v___x_7978_; 
v___x_7977_ = 18446744073709551615ULL;
v___x_7978_ = lean_uint64_xor(v___y_7969_, v___x_7977_);
v___y_7956_ = v___y_7972_;
v___y_7957_ = v___y_7970_;
v___y_7958_ = v___y_7971_;
v___y_7959_ = v___x_7978_;
goto v___jp_7955_;
}
else
{
uint64_t v___x_7979_; 
v___x_7979_ = lean_uint64_xor(v___y_7969_, v___x_7973_);
v___y_7956_ = v___y_7972_;
v___y_7957_ = v___y_7970_;
v___y_7958_ = v___y_7971_;
v___y_7959_ = v___x_7979_;
goto v___jp_7955_;
}
}
v___jp_7980_:
{
uint64_t v___x_7985_; uint64_t v___x_7986_; uint64_t v___x_7987_; uint8_t v___x_7988_; 
v___x_7985_ = 9223372036854775808ULL;
v___x_7986_ = lean_uint64_land(v___y_7982_, v___x_7985_);
v___x_7987_ = 0ULL;
v___x_7988_ = lean_uint64_dec_eq(v___x_7986_, v___x_7987_);
if (v___x_7988_ == 0)
{
uint64_t v___x_7989_; uint64_t v___x_7990_; 
v___x_7989_ = 18446744073709551615ULL;
v___x_7990_ = lean_uint64_xor(v___y_7982_, v___x_7989_);
v___y_7969_ = v___y_7981_;
v___y_7970_ = v___y_7983_;
v___y_7971_ = v___y_7984_;
v___y_7972_ = v___x_7990_;
goto v___jp_7968_;
}
else
{
uint64_t v___x_7991_; 
v___x_7991_ = lean_uint64_xor(v___y_7982_, v___x_7985_);
v___y_7969_ = v___y_7981_;
v___y_7970_ = v___y_7983_;
v___y_7971_ = v___y_7984_;
v___y_7972_ = v___x_7991_;
goto v___jp_7968_;
}
}
v___jp_7992_:
{
uint64_t v___x_7997_; uint64_t v___x_7998_; uint64_t v___x_7999_; 
v___x_7997_ = 9223372036854775808ULL;
v___x_7998_ = lean_uint64_lor(v___y_7994_, v___x_7997_);
v___x_7999_ = lean_uint64_lor(v___y_7995_, v___x_7997_);
v___y_7981_ = v___y_7993_;
v___y_7982_ = v___x_7998_;
v___y_7983_ = v___y_7996_;
v___y_7984_ = v___x_7999_;
goto v___jp_7980_;
}
v___jp_8000_:
{
if (v___y_8005_ == 0)
{
v___y_7981_ = v___y_8001_;
v___y_7982_ = v___y_8003_;
v___y_7983_ = v___y_8004_;
v___y_7984_ = v___y_8002_;
goto v___jp_7980_;
}
else
{
v___y_7993_ = v___y_8001_;
v___y_7994_ = v___y_8002_;
v___y_7995_ = v___y_8003_;
v___y_7996_ = v___y_8004_;
goto v___jp_7992_;
}
}
v___jp_8013_:
{
uint64_t v_below_8020_; uint64_t v___x_8021_; uint64_t v_above_8022_; uint32_t v___x_8023_; uint32_t v___x_8024_; uint8_t v___x_8025_; 
v_below_8020_ = lean_uint64_sub(v___y_8018_, v___y_8019_);
v___x_8021_ = 268435456ULL;
v_above_8022_ = lean_uint64_add(v___y_8018_, v___x_8021_);
v___x_8023_ = 2147483648;
v___x_8024_ = lean_uint32_land(v_guess_7942_, v___x_8023_);
v___x_8025_ = lean_uint32_dec_eq(v___x_8024_, v___x_8012_);
if (v___x_8025_ == 0)
{
if (v___y_8014_ == 0)
{
v___y_8001_ = v___y_8015_;
v___y_8002_ = v_above_8022_;
v___y_8003_ = v_below_8020_;
v___y_8004_ = v___y_8017_;
v___y_8005_ = v___y_8016_;
goto v___jp_8000_;
}
else
{
v___y_7993_ = v___y_8015_;
v___y_7994_ = v_above_8022_;
v___y_7995_ = v_below_8020_;
v___y_7996_ = v___y_8017_;
goto v___jp_7992_;
}
}
else
{
v___y_8001_ = v___y_8015_;
v___y_8002_ = v_above_8022_;
v___y_8003_ = v_below_8020_;
v___y_8004_ = v___y_8017_;
v___y_8005_ = v___y_8016_;
goto v___jp_8000_;
}
}
v___jp_8026_:
{
uint64_t v___x_8031_; uint64_t v___x_8032_; uint64_t v___x_8033_; uint64_t v___x_8034_; uint64_t v___x_8035_; uint32_t v___x_8036_; uint32_t v___x_8037_; uint64_t v___x_8038_; uint64_t v___x_8039_; uint64_t v___x_8040_; uint64_t v_base_8041_; uint32_t v___x_8042_; uint8_t v___x_8043_; 
v___x_8031_ = lean_uint32_to_uint64(v_e_8011_);
v___x_8032_ = 896ULL;
v___x_8033_ = lean_uint64_add(v___x_8031_, v___x_8032_);
v___x_8034_ = 52ULL;
v___x_8035_ = lean_uint64_shift_left(v___x_8033_, v___x_8034_);
v___x_8036_ = 8388607;
v___x_8037_ = lean_uint32_land(v_magnitude_8007_, v___x_8036_);
v___x_8038_ = lean_uint32_to_uint64(v___x_8037_);
v___x_8039_ = 29ULL;
v___x_8040_ = lean_uint64_shift_left(v___x_8038_, v___x_8039_);
v_base_8041_ = lean_uint64_lor(v___x_8035_, v___x_8040_);
v___x_8042_ = 8388608;
v___x_8043_ = lean_uint32_dec_eq(v_magnitude_8007_, v___x_8042_);
if (v___x_8043_ == 0)
{
uint64_t v___x_8044_; 
v___x_8044_ = 268435456ULL;
v___y_8014_ = v___y_8030_;
v___y_8015_ = v___y_8027_;
v___y_8016_ = v___y_8028_;
v___y_8017_ = v___y_8029_;
v___y_8018_ = v_base_8041_;
v___y_8019_ = v___x_8044_;
goto v___jp_8013_;
}
else
{
uint64_t v___x_8045_; 
v___x_8045_ = 536870912ULL;
v___y_8014_ = v___y_8030_;
v___y_8015_ = v___y_8027_;
v___y_8016_ = v___y_8028_;
v___y_8017_ = v___y_8029_;
v___y_8018_ = v_base_8041_;
v___y_8019_ = v___x_8045_;
goto v___jp_8013_;
}
}
v___jp_8046_:
{
if (v___y_8047_ == 0)
{
uint64_t v___x_8048_; uint64_t v___x_8049_; uint8_t v___x_8050_; 
v___x_8048_ = 9218868437227405312ULL;
v___x_8049_ = lean_uint64_land(v_sumWord_7941_, v___x_8048_);
v___x_8050_ = lean_uint64_dec_eq(v___x_8049_, v___x_8048_);
if (v___x_8050_ == 0)
{
double v___x_8051_; uint64_t v_lowerEndpoint_8052_; uint64_t v___x_8053_; uint8_t v___x_8054_; 
v___x_8051_ = lean_float_sub(v_sum_7939_, v_radius_7940_);
v_lowerEndpoint_8052_ = lean_float_to_bits(v___x_8051_);
v___x_8053_ = lean_uint64_land(v_lowerEndpoint_8052_, v___x_8048_);
v___x_8054_ = lean_uint64_dec_eq(v___x_8053_, v___x_8048_);
if (v___x_8054_ == 0)
{
double v___x_8055_; uint64_t v_upperEndpoint_8056_; uint64_t v___x_8057_; uint8_t v___x_8058_; 
v___x_8055_ = lean_float_add(v_sum_7939_, v_radius_7940_);
v_upperEndpoint_8056_ = lean_float_to_bits(v___x_8055_);
v___x_8057_ = lean_uint64_land(v_upperEndpoint_8056_, v___x_8048_);
v___x_8058_ = lean_uint64_dec_eq(v___x_8057_, v___x_8048_);
if (v___x_8058_ == 0)
{
uint8_t v___x_8059_; 
v___x_8059_ = 1;
v___y_8027_ = v_lowerEndpoint_8052_;
v___y_8028_ = v___y_8047_;
v___y_8029_ = v_upperEndpoint_8056_;
v___y_8030_ = v___x_8059_;
goto v___jp_8026_;
}
else
{
if (v___x_8054_ == 0)
{
return v___y_8047_;
}
else
{
v___y_8027_ = v_lowerEndpoint_8052_;
v___y_8028_ = v___y_8047_;
v___y_8029_ = v_upperEndpoint_8056_;
v___y_8030_ = v___x_8054_;
goto v___jp_8026_;
}
}
}
else
{
return v___y_8047_;
}
}
else
{
return v___y_8047_;
}
}
else
{
uint8_t v___x_8060_; 
v___x_8060_ = 0;
return v___x_8060_;
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_R24PortableF64_certify___boxed(lean_object* v_sum_8063_, lean_object* v_radius_8064_, lean_object* v_sumWord_8065_, lean_object* v_guess_8066_){
_start:
{
double v_sum_boxed_8067_; double v_radius_boxed_8068_; uint64_t v_sumWord_boxed_8069_; uint32_t v_guess_boxed_8070_; uint8_t v_res_8071_; lean_object* v_r_8072_; 
v_sum_boxed_8067_ = lean_unbox_float(v_sum_8063_);
lean_dec_ref(v_sum_8063_);
v_radius_boxed_8068_ = lean_unbox_float(v_radius_8064_);
lean_dec_ref(v_radius_8064_);
v_sumWord_boxed_8069_ = lean_unbox_uint64(v_sumWord_8065_);
lean_dec_ref(v_sumWord_8065_);
v_guess_boxed_8070_ = lean_unbox_uint32(v_guess_8066_);
lean_dec(v_guess_8066_);
v_res_8071_ = lp_competition_Submission_R24PortableF64_certify(v_sum_boxed_8067_, v_radius_boxed_8068_, v_sumWord_boxed_8069_, v_guess_boxed_8070_);
v_r_8072_ = lean_box(v_res_8071_);
return v_r_8072_;
}
}
LEAN_EXPORT double lp_competition_Submission_R24PortableF64_sumRemaining(lean_object* v_a_8073_, lean_object* v_b_8074_, lean_object* v_index_8075_, double v_acc_8076_, lean_object* v_remaining_8077_){
_start:
{
lean_object* v_zero_8078_; uint8_t v_isZero_8079_; 
v_zero_8078_ = lean_unsigned_to_nat(0u);
v_isZero_8079_ = lean_nat_dec_eq(v_remaining_8077_, v_zero_8078_);
if (v_isZero_8079_ == 1)
{
lean_dec(v_remaining_8077_);
lean_dec(v_index_8075_);
return v_acc_8076_;
}
else
{
lean_object* v_one_8080_; lean_object* v_n_8081_; lean_object* v___x_8082_; double v___x_8083_; double v___x_8084_; double v___x_8085_; double v___x_8086_; 
v_one_8080_ = lean_unsigned_to_nat(1u);
v_n_8081_ = lean_nat_sub(v_remaining_8077_, v_one_8080_);
lean_dec(v_remaining_8077_);
v___x_8082_ = lean_nat_add(v_index_8075_, v_one_8080_);
v___x_8083_ = lean_float_array_get(v_a_8073_, v_index_8075_);
v___x_8084_ = lean_float_array_get(v_b_8074_, v_index_8075_);
lean_dec(v_index_8075_);
v___x_8085_ = lean_float_mul(v___x_8083_, v___x_8084_);
v___x_8086_ = lean_float_add(v_acc_8076_, v___x_8085_);
v_index_8075_ = v___x_8082_;
v_acc_8076_ = v___x_8086_;
v_remaining_8077_ = v_n_8081_;
goto _start;
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_R24PortableF64_sumRemaining___boxed(lean_object* v_a_8088_, lean_object* v_b_8089_, lean_object* v_index_8090_, lean_object* v_acc_8091_, lean_object* v_remaining_8092_){
_start:
{
double v_acc_boxed_8093_; double v_res_8094_; lean_object* v_r_8095_; 
v_acc_boxed_8093_ = lean_unbox_float(v_acc_8091_);
lean_dec_ref(v_acc_8091_);
v_res_8094_ = lp_competition_Submission_R24PortableF64_sumRemaining(v_a_8088_, v_b_8089_, v_index_8090_, v_acc_boxed_8093_, v_remaining_8092_);
lean_dec_ref(v_b_8089_);
lean_dec_ref(v_a_8088_);
v_r_8095_ = lean_box_float(v_res_8094_);
return v_r_8095_;
}
}
LEAN_EXPORT uint32_t lp_competition_Submission_R24PortableF64_attemptPrepared(lean_object* v_x_8096_, lean_object* v_y_8097_){
_start:
{
uint32_t v___y_8099_; uint8_t v___y_8100_; uint32_t v___y_8103_; uint64_t v___y_8104_; uint64_t v___y_8105_; uint64_t v___y_8108_; uint64_t v___y_8109_; uint32_t v___y_8110_; uint64_t v___y_8111_; uint64_t v___y_8119_; uint64_t v___y_8120_; uint64_t v___y_8121_; uint64_t v___y_8122_; uint32_t v___y_8123_; uint64_t v___y_8124_; uint64_t v___y_8133_; uint64_t v___y_8134_; uint32_t v___y_8135_; uint64_t v___y_8136_; uint64_t v___y_8137_; uint64_t v___y_8138_; uint64_t v___y_8146_; uint64_t v___y_8147_; uint64_t v___y_8148_; uint32_t v___y_8149_; uint64_t v___y_8150_; uint64_t v___y_8151_; uint64_t v___y_8159_; uint64_t v___y_8160_; uint64_t v___y_8161_; uint64_t v___y_8162_; uint64_t v___y_8163_; uint32_t v___y_8164_; uint64_t v___y_8169_; uint64_t v___y_8170_; uint64_t v___y_8171_; uint64_t v___y_8172_; uint64_t v___y_8173_; uint32_t v___y_8174_; uint8_t v___y_8175_; uint64_t v___y_8177_; uint64_t v___y_8178_; uint64_t v___y_8179_; uint64_t v___y_8180_; uint8_t v___y_8181_; uint8_t v___y_8182_; uint32_t v___y_8183_; uint32_t v___y_8184_; uint64_t v___y_8185_; uint32_t v___y_8186_; uint64_t v___y_8187_; uint32_t v___y_8193_; uint64_t v___y_8194_; uint64_t v___y_8195_; uint64_t v___y_8196_; uint64_t v___y_8197_; uint8_t v___y_8198_; uint64_t v___y_8199_; uint32_t v___y_8200_; uint32_t v___y_8201_; uint64_t v___y_8202_; uint32_t v___y_8203_; uint32_t v___y_8204_; uint8_t v___y_8205_; uint8_t v___y_8219_; uint64_t v___y_8220_; uint64_t v___y_8221_; uint32_t v___y_8222_; uint32_t v___y_8223_; double v___y_8224_; uint32_t v___y_8225_; uint64_t v___y_8226_; double v___y_8227_; uint64_t v___y_8228_; uint32_t v___y_8229_; uint32_t v___y_8230_; uint64_t v___y_8231_; uint8_t v___y_8232_; lean_object* v_raw_8244_; lean_object* v_values_8245_; uint32_t v_maxIndex_8246_; uint8_t v_valid_8247_; uint64_t v___y_8249_; uint8_t v___y_8250_; double v___y_8251_; uint32_t v___y_8252_; uint32_t v___y_8253_; uint64_t v___y_8254_; uint64_t v___y_8255_; uint32_t v___y_8256_; uint32_t v___y_8257_; uint64_t v___y_8258_; uint64_t v___y_8259_; uint8_t v___y_8279_; uint64_t v___y_8280_; double v___y_8281_; uint32_t v___y_8282_; uint32_t v___y_8283_; uint64_t v___y_8284_; uint64_t v___y_8285_; uint64_t v___y_8286_; uint32_t v___y_8287_; uint32_t v___y_8288_; uint64_t v___y_8289_; uint64_t v___y_8290_; uint64_t v___y_8291_; uint8_t v___y_8298_; uint64_t v___y_8299_; uint64_t v___y_8300_; uint64_t v___y_8301_; uint32_t v___y_8302_; uint64_t v___y_8303_; uint64_t v___y_8304_; uint64_t v___y_8305_; double v___y_8306_; uint32_t v___y_8307_; uint32_t v___y_8308_; uint32_t v___y_8309_; uint64_t v___y_8310_; uint64_t v___y_8311_; uint64_t v___y_8312_; uint64_t v___y_8317_; uint8_t v___y_8318_; double v___y_8319_; uint32_t v___y_8320_; uint32_t v___y_8321_; uint64_t v___y_8322_; uint64_t v___y_8323_; uint32_t v___y_8324_; uint32_t v___y_8325_; uint64_t v___y_8326_; uint64_t v___y_8327_; uint64_t v___y_8328_; uint64_t v___y_8329_; uint8_t v___y_8334_; uint64_t v___y_8335_; uint64_t v___y_8336_; uint64_t v___y_8337_; uint32_t v___y_8338_; uint64_t v___y_8339_; uint64_t v___y_8340_; double v___y_8341_; uint32_t v___y_8342_; uint32_t v___y_8343_; uint64_t v___y_8344_; uint32_t v___y_8345_; uint64_t v___y_8346_; uint64_t v___y_8347_; uint64_t v___y_8348_; uint64_t v___y_8353_; uint8_t v___y_8354_; double v___y_8355_; uint32_t v___y_8356_; uint32_t v___y_8357_; uint64_t v___y_8358_; uint64_t v___y_8359_; uint64_t v___y_8360_; uint32_t v___y_8361_; uint32_t v___y_8362_; uint64_t v___y_8363_; uint64_t v___y_8364_; uint64_t v___y_8365_; uint8_t v___y_8370_; uint64_t v___y_8371_; uint64_t v___y_8372_; uint64_t v___y_8373_; uint64_t v___y_8374_; uint32_t v___y_8375_; uint64_t v___y_8376_; double v___y_8377_; uint32_t v___y_8378_; uint32_t v___y_8379_; uint32_t v___y_8380_; uint64_t v___y_8381_; uint64_t v___y_8382_; uint64_t v___y_8383_; uint64_t v___y_8384_; uint64_t v___y_8389_; uint8_t v___y_8390_; double v___y_8391_; uint32_t v___y_8392_; uint32_t v___y_8393_; uint64_t v___y_8394_; uint64_t v___y_8395_; uint64_t v___y_8396_; uint32_t v___y_8397_; uint32_t v___y_8398_; uint64_t v___y_8399_; uint64_t v___y_8400_; uint64_t v___y_8401_; uint8_t v___y_8406_; uint64_t v___y_8407_; uint64_t v___y_8408_; uint64_t v___y_8409_; uint64_t v___y_8410_; uint32_t v___y_8411_; uint64_t v___y_8412_; double v___y_8413_; uint64_t v___y_8414_; uint32_t v___y_8415_; uint32_t v___y_8416_; uint32_t v___y_8417_; uint64_t v___y_8418_; uint64_t v___y_8419_; uint64_t v___y_8420_; uint64_t v___y_8425_; uint8_t v___y_8426_; double v___y_8427_; uint64_t v___y_8428_; uint32_t v___y_8429_; uint32_t v___y_8430_; uint64_t v___y_8431_; uint64_t v___y_8432_; uint32_t v___y_8433_; uint32_t v___y_8434_; uint64_t v___y_8435_; uint64_t v___y_8436_; uint64_t v___y_8437_; uint8_t v___y_8442_; uint64_t v___y_8443_; uint64_t v___y_8444_; uint32_t v___y_8445_; uint64_t v___y_8446_; double v___y_8447_; uint64_t v___y_8448_; uint32_t v___y_8449_; uint32_t v___y_8450_; uint32_t v___y_8451_; uint64_t v___y_8452_; uint64_t v___y_8453_; uint64_t v___y_8454_; uint64_t v___y_8455_; lean_object* v_n_8458_; lean_object* v___x_8459_; uint8_t v___y_8461_; uint8_t v___x_8499_; 
v_raw_8244_ = lean_ctor_get(v_x_8096_, 0);
v_values_8245_ = lean_ctor_get(v_x_8096_, 1);
v_maxIndex_8246_ = lean_ctor_get_uint32(v_x_8096_, sizeof(void*)*2);
v_valid_8247_ = lean_ctor_get_uint8(v_x_8096_, sizeof(void*)*2 + 4);
v_n_8458_ = lean_array_get_size(v_raw_8244_);
v___x_8459_ = lean_unsigned_to_nat(0u);
v___x_8499_ = lean_nat_dec_eq(v_n_8458_, v___x_8459_);
if (v___x_8499_ == 0)
{
lean_object* v_raw_8500_; lean_object* v___x_8501_; uint8_t v___x_8502_; 
v_raw_8500_ = lean_ctor_get(v_y_8097_, 0);
v___x_8501_ = lean_array_get_size(v_raw_8500_);
v___x_8502_ = lean_nat_dec_eq(v_n_8458_, v___x_8501_);
if (v___x_8502_ == 0)
{
uint32_t v___x_8503_; 
v___x_8503_ = 0;
return v___x_8503_;
}
else
{
v___y_8461_ = v___x_8499_;
goto v___jp_8460_;
}
}
else
{
v___y_8461_ = v___x_8499_;
goto v___jp_8460_;
}
v___jp_8098_:
{
if (v___y_8100_ == 0)
{
uint32_t v___x_8101_; 
v___x_8101_ = 0;
return v___x_8101_;
}
else
{
return v___y_8099_;
}
}
v___jp_8102_:
{
uint8_t v___x_8106_; 
v___x_8106_ = lean_uint64_dec_lt(v___y_8104_, v___y_8105_);
v___y_8099_ = v___y_8103_;
v___y_8100_ = v___x_8106_;
goto v___jp_8098_;
}
v___jp_8107_:
{
uint64_t v___x_8112_; uint64_t v___x_8113_; uint8_t v___x_8114_; 
v___x_8112_ = 9223372036854775808ULL;
v___x_8113_ = lean_uint64_land(v___y_8109_, v___x_8112_);
v___x_8114_ = lean_uint64_dec_eq(v___x_8113_, v___y_8108_);
if (v___x_8114_ == 0)
{
uint64_t v___x_8115_; uint64_t v___x_8116_; 
v___x_8115_ = 18446744073709551615ULL;
v___x_8116_ = lean_uint64_xor(v___y_8109_, v___x_8115_);
v___y_8103_ = v___y_8110_;
v___y_8104_ = v___y_8111_;
v___y_8105_ = v___x_8116_;
goto v___jp_8102_;
}
else
{
uint64_t v___x_8117_; 
v___x_8117_ = lean_uint64_xor(v___y_8109_, v___x_8112_);
v___y_8103_ = v___y_8110_;
v___y_8104_ = v___y_8111_;
v___y_8105_ = v___x_8117_;
goto v___jp_8102_;
}
}
v___jp_8118_:
{
uint8_t v___x_8125_; 
v___x_8125_ = lean_uint64_dec_lt(v___y_8120_, v___y_8124_);
if (v___x_8125_ == 0)
{
v___y_8099_ = v___y_8123_;
v___y_8100_ = v___x_8125_;
goto v___jp_8098_;
}
else
{
uint64_t v___x_8126_; uint64_t v___x_8127_; uint8_t v___x_8128_; 
v___x_8126_ = 9223372036854775808ULL;
v___x_8127_ = lean_uint64_land(v___y_8122_, v___x_8126_);
v___x_8128_ = lean_uint64_dec_eq(v___x_8127_, v___y_8119_);
if (v___x_8128_ == 0)
{
uint64_t v___x_8129_; uint64_t v___x_8130_; 
v___x_8129_ = 18446744073709551615ULL;
v___x_8130_ = lean_uint64_xor(v___y_8122_, v___x_8129_);
v___y_8108_ = v___y_8119_;
v___y_8109_ = v___y_8121_;
v___y_8110_ = v___y_8123_;
v___y_8111_ = v___x_8130_;
goto v___jp_8107_;
}
else
{
uint64_t v___x_8131_; 
v___x_8131_ = lean_uint64_xor(v___y_8122_, v___x_8126_);
v___y_8108_ = v___y_8119_;
v___y_8109_ = v___y_8121_;
v___y_8110_ = v___y_8123_;
v___y_8111_ = v___x_8131_;
goto v___jp_8107_;
}
}
}
v___jp_8132_:
{
uint64_t v___x_8139_; uint64_t v___x_8140_; uint8_t v___x_8141_; 
v___x_8139_ = 9223372036854775808ULL;
v___x_8140_ = lean_uint64_land(v___y_8134_, v___x_8139_);
v___x_8141_ = lean_uint64_dec_eq(v___x_8140_, v___y_8133_);
if (v___x_8141_ == 0)
{
uint64_t v___x_8142_; uint64_t v___x_8143_; 
v___x_8142_ = 18446744073709551615ULL;
v___x_8143_ = lean_uint64_xor(v___y_8134_, v___x_8142_);
v___y_8119_ = v___y_8133_;
v___y_8120_ = v___y_8138_;
v___y_8121_ = v___y_8137_;
v___y_8122_ = v___y_8136_;
v___y_8123_ = v___y_8135_;
v___y_8124_ = v___x_8143_;
goto v___jp_8118_;
}
else
{
uint64_t v___x_8144_; 
v___x_8144_ = lean_uint64_xor(v___y_8134_, v___x_8139_);
v___y_8119_ = v___y_8133_;
v___y_8120_ = v___y_8138_;
v___y_8121_ = v___y_8137_;
v___y_8122_ = v___y_8136_;
v___y_8123_ = v___y_8135_;
v___y_8124_ = v___x_8144_;
goto v___jp_8118_;
}
}
v___jp_8145_:
{
uint64_t v___x_8152_; uint64_t v___x_8153_; uint8_t v___x_8154_; 
v___x_8152_ = 9223372036854775808ULL;
v___x_8153_ = lean_uint64_land(v___y_8150_, v___x_8152_);
v___x_8154_ = lean_uint64_dec_eq(v___x_8153_, v___y_8146_);
if (v___x_8154_ == 0)
{
uint64_t v___x_8155_; uint64_t v___x_8156_; 
v___x_8155_ = 18446744073709551615ULL;
v___x_8156_ = lean_uint64_xor(v___y_8150_, v___x_8155_);
v___y_8133_ = v___y_8146_;
v___y_8134_ = v___y_8147_;
v___y_8135_ = v___y_8149_;
v___y_8136_ = v___y_8148_;
v___y_8137_ = v___y_8151_;
v___y_8138_ = v___x_8156_;
goto v___jp_8132_;
}
else
{
uint64_t v___x_8157_; 
v___x_8157_ = lean_uint64_xor(v___y_8150_, v___x_8152_);
v___y_8133_ = v___y_8146_;
v___y_8134_ = v___y_8147_;
v___y_8135_ = v___y_8149_;
v___y_8136_ = v___y_8148_;
v___y_8137_ = v___y_8151_;
v___y_8138_ = v___x_8157_;
goto v___jp_8132_;
}
}
v___jp_8158_:
{
uint64_t v___x_8165_; uint64_t v___x_8166_; uint64_t v___x_8167_; 
v___x_8165_ = 9223372036854775808ULL;
v___x_8166_ = lean_uint64_lor(v___y_8160_, v___x_8165_);
v___x_8167_ = lean_uint64_lor(v___y_8162_, v___x_8165_);
v___y_8146_ = v___y_8159_;
v___y_8147_ = v___y_8161_;
v___y_8148_ = v___y_8163_;
v___y_8149_ = v___y_8164_;
v___y_8150_ = v___x_8166_;
v___y_8151_ = v___x_8167_;
goto v___jp_8145_;
}
v___jp_8168_:
{
if (v___y_8175_ == 0)
{
v___y_8146_ = v___y_8169_;
v___y_8147_ = v___y_8171_;
v___y_8148_ = v___y_8173_;
v___y_8149_ = v___y_8174_;
v___y_8150_ = v___y_8172_;
v___y_8151_ = v___y_8170_;
goto v___jp_8145_;
}
else
{
v___y_8159_ = v___y_8169_;
v___y_8160_ = v___y_8170_;
v___y_8161_ = v___y_8171_;
v___y_8162_ = v___y_8172_;
v___y_8163_ = v___y_8173_;
v___y_8164_ = v___y_8174_;
goto v___jp_8158_;
}
}
v___jp_8176_:
{
uint64_t v_below_8188_; uint64_t v_above_8189_; uint32_t v___x_8190_; uint8_t v___x_8191_; 
v_below_8188_ = lean_uint64_sub(v___y_8178_, v___y_8187_);
v_above_8189_ = lean_uint64_add(v___y_8178_, v___y_8180_);
v___x_8190_ = lean_uint32_land(v___y_8184_, v___y_8183_);
v___x_8191_ = lean_uint32_dec_eq(v___x_8190_, v___y_8186_);
if (v___x_8191_ == 0)
{
if (v___y_8182_ == 0)
{
v___y_8169_ = v___y_8177_;
v___y_8170_ = v_above_8189_;
v___y_8171_ = v___y_8179_;
v___y_8172_ = v_below_8188_;
v___y_8173_ = v___y_8185_;
v___y_8174_ = v___y_8184_;
v___y_8175_ = v___y_8181_;
goto v___jp_8168_;
}
else
{
v___y_8159_ = v___y_8177_;
v___y_8160_ = v_above_8189_;
v___y_8161_ = v___y_8179_;
v___y_8162_ = v_below_8188_;
v___y_8163_ = v___y_8185_;
v___y_8164_ = v___y_8184_;
goto v___jp_8158_;
}
}
else
{
v___y_8169_ = v___y_8177_;
v___y_8170_ = v_above_8189_;
v___y_8171_ = v___y_8179_;
v___y_8172_ = v_below_8188_;
v___y_8173_ = v___y_8185_;
v___y_8174_ = v___y_8184_;
v___y_8175_ = v___y_8181_;
goto v___jp_8168_;
}
}
v___jp_8192_:
{
uint64_t v___x_8206_; uint64_t v___x_8207_; uint64_t v___x_8208_; uint64_t v___x_8209_; uint32_t v___x_8210_; uint32_t v___x_8211_; uint64_t v___x_8212_; uint64_t v___x_8213_; uint64_t v_base_8214_; uint32_t v___x_8215_; uint8_t v___x_8216_; 
v___x_8206_ = lean_uint32_to_uint64(v___y_8201_);
v___x_8207_ = 896ULL;
v___x_8208_ = lean_uint64_add(v___x_8206_, v___x_8207_);
v___x_8209_ = lean_uint64_shift_left(v___x_8208_, v___y_8195_);
v___x_8210_ = 8388607;
v___x_8211_ = lean_uint32_land(v___y_8193_, v___x_8210_);
v___x_8212_ = lean_uint32_to_uint64(v___x_8211_);
v___x_8213_ = lean_uint64_shift_left(v___x_8212_, v___y_8199_);
v_base_8214_ = lean_uint64_lor(v___x_8209_, v___x_8213_);
v___x_8215_ = 8388608;
v___x_8216_ = lean_uint32_dec_eq(v___y_8193_, v___x_8215_);
if (v___x_8216_ == 0)
{
v___y_8177_ = v___y_8194_;
v___y_8178_ = v_base_8214_;
v___y_8179_ = v___y_8197_;
v___y_8180_ = v___y_8196_;
v___y_8181_ = v___y_8198_;
v___y_8182_ = v___y_8205_;
v___y_8183_ = v___y_8200_;
v___y_8184_ = v___y_8203_;
v___y_8185_ = v___y_8202_;
v___y_8186_ = v___y_8204_;
v___y_8187_ = v___y_8196_;
goto v___jp_8176_;
}
else
{
uint64_t v___x_8217_; 
v___x_8217_ = 536870912ULL;
v___y_8177_ = v___y_8194_;
v___y_8178_ = v_base_8214_;
v___y_8179_ = v___y_8197_;
v___y_8180_ = v___y_8196_;
v___y_8181_ = v___y_8198_;
v___y_8182_ = v___y_8205_;
v___y_8183_ = v___y_8200_;
v___y_8184_ = v___y_8203_;
v___y_8185_ = v___y_8202_;
v___y_8186_ = v___y_8204_;
v___y_8187_ = v___x_8217_;
goto v___jp_8176_;
}
}
v___jp_8218_:
{
if (v___y_8232_ == 0)
{
uint64_t v___x_8233_; uint64_t v___x_8234_; uint8_t v___x_8235_; 
v___x_8233_ = 9218868437227405312ULL;
v___x_8234_ = lean_uint64_land(v___y_8231_, v___x_8233_);
v___x_8235_ = lean_uint64_dec_eq(v___x_8234_, v___x_8233_);
if (v___x_8235_ == 0)
{
double v___x_8236_; uint64_t v_lowerEndpoint_8237_; uint64_t v___x_8238_; uint8_t v___x_8239_; 
v___x_8236_ = lean_float_sub(v___y_8227_, v___y_8224_);
v_lowerEndpoint_8237_ = lean_float_to_bits(v___x_8236_);
v___x_8238_ = lean_uint64_land(v_lowerEndpoint_8237_, v___x_8233_);
v___x_8239_ = lean_uint64_dec_eq(v___x_8238_, v___x_8233_);
if (v___x_8239_ == 0)
{
double v___x_8240_; uint64_t v_upperEndpoint_8241_; uint64_t v___x_8242_; uint8_t v___x_8243_; 
v___x_8240_ = lean_float_add(v___y_8227_, v___y_8224_);
v_upperEndpoint_8241_ = lean_float_to_bits(v___x_8240_);
v___x_8242_ = lean_uint64_land(v_upperEndpoint_8241_, v___x_8233_);
v___x_8243_ = lean_uint64_dec_eq(v___x_8242_, v___x_8233_);
if (v___x_8243_ == 0)
{
v___y_8193_ = v___y_8225_;
v___y_8194_ = v___y_8226_;
v___y_8195_ = v___y_8228_;
v___y_8196_ = v___y_8220_;
v___y_8197_ = v_lowerEndpoint_8237_;
v___y_8198_ = v___x_8239_;
v___y_8199_ = v___y_8221_;
v___y_8200_ = v___y_8229_;
v___y_8201_ = v___y_8230_;
v___y_8202_ = v_upperEndpoint_8241_;
v___y_8203_ = v___y_8222_;
v___y_8204_ = v___y_8223_;
v___y_8205_ = v___y_8219_;
goto v___jp_8192_;
}
else
{
if (v___x_8239_ == 0)
{
return v___y_8223_;
}
else
{
v___y_8193_ = v___y_8225_;
v___y_8194_ = v___y_8226_;
v___y_8195_ = v___y_8228_;
v___y_8196_ = v___y_8220_;
v___y_8197_ = v_lowerEndpoint_8237_;
v___y_8198_ = v___x_8239_;
v___y_8199_ = v___y_8221_;
v___y_8200_ = v___y_8229_;
v___y_8201_ = v___y_8230_;
v___y_8202_ = v_upperEndpoint_8241_;
v___y_8203_ = v___y_8222_;
v___y_8204_ = v___y_8223_;
v___y_8205_ = v___x_8239_;
goto v___jp_8192_;
}
}
}
else
{
return v___y_8223_;
}
}
else
{
return v___y_8223_;
}
}
else
{
return v___y_8223_;
}
}
v___jp_8248_:
{
uint64_t v___x_8260_; uint64_t v___x_8261_; uint64_t v_H_8262_; uint64_t v___x_8263_; uint64_t v___x_8264_; uint64_t v___x_8265_; uint64_t v___x_8266_; uint64_t v___x_8267_; uint64_t v___x_8268_; double v_radius_8269_; uint32_t v_magnitude_8270_; uint32_t v___x_8271_; uint32_t v___x_8272_; uint32_t v___x_8273_; uint32_t v_e_8274_; uint32_t v___x_8275_; uint8_t v___x_8276_; 
v___x_8260_ = lean_uint32_to_uint64(v_maxIndex_8246_);
v___x_8261_ = lean_uint32_to_uint64(v___y_8253_);
v_H_8262_ = lean_uint64_add(v___x_8260_, v___x_8261_);
v___x_8263_ = lean_uint64_add(v___y_8259_, v___y_8259_);
v___x_8264_ = lean_uint64_add(v_H_8262_, v___x_8263_);
v___x_8265_ = 720ULL;
v___x_8266_ = lean_uint64_add(v___x_8264_, v___x_8265_);
v___x_8267_ = 52ULL;
v___x_8268_ = lean_uint64_shift_left(v___x_8266_, v___x_8267_);
v_radius_8269_ = lean_float_of_bits(v___x_8268_);
v_magnitude_8270_ = lean_uint32_land(v___y_8257_, v___y_8252_);
v___x_8271_ = 23;
v___x_8272_ = lean_uint32_shift_right(v_magnitude_8270_, v___x_8271_);
v___x_8273_ = 255;
v_e_8274_ = lean_uint32_land(v___x_8272_, v___x_8273_);
v___x_8275_ = 0;
v___x_8276_ = lean_uint32_dec_eq(v_e_8274_, v___x_8275_);
if (v___x_8276_ == 0)
{
uint8_t v___x_8277_; 
v___x_8277_ = lean_uint32_dec_eq(v_e_8274_, v___x_8273_);
v___y_8219_ = v___y_8250_;
v___y_8220_ = v___y_8254_;
v___y_8221_ = v___y_8255_;
v___y_8222_ = v___y_8257_;
v___y_8223_ = v___x_8275_;
v___y_8224_ = v_radius_8269_;
v___y_8225_ = v_magnitude_8270_;
v___y_8226_ = v___y_8249_;
v___y_8227_ = v___y_8251_;
v___y_8228_ = v___x_8267_;
v___y_8229_ = v___y_8256_;
v___y_8230_ = v_e_8274_;
v___y_8231_ = v___y_8258_;
v___y_8232_ = v___x_8277_;
goto v___jp_8218_;
}
else
{
v___y_8219_ = v___y_8250_;
v___y_8220_ = v___y_8254_;
v___y_8221_ = v___y_8255_;
v___y_8222_ = v___y_8257_;
v___y_8223_ = v___x_8275_;
v___y_8224_ = v_radius_8269_;
v___y_8225_ = v_magnitude_8270_;
v___y_8226_ = v___y_8249_;
v___y_8227_ = v___y_8251_;
v___y_8228_ = v___x_8267_;
v___y_8229_ = v___y_8256_;
v___y_8230_ = v_e_8274_;
v___y_8231_ = v___y_8258_;
v___y_8232_ = v___x_8276_;
goto v___jp_8218_;
}
}
v___jp_8278_:
{
uint64_t v___x_8292_; uint8_t v___x_8293_; 
v___x_8292_ = lean_uint64_shift_right(v___y_8284_, v___y_8290_);
v___x_8293_ = lean_uint64_dec_eq(v___x_8292_, v___y_8280_);
if (v___x_8293_ == 0)
{
uint64_t v___x_8294_; uint64_t v___x_8295_; 
v___x_8294_ = lean_uint64_add(v___y_8291_, v___y_8290_);
v___x_8295_ = lean_uint64_add(v___x_8294_, v___y_8290_);
v___y_8249_ = v___y_8280_;
v___y_8250_ = v___y_8279_;
v___y_8251_ = v___y_8281_;
v___y_8252_ = v___y_8283_;
v___y_8253_ = v___y_8282_;
v___y_8254_ = v___y_8285_;
v___y_8255_ = v___y_8286_;
v___y_8256_ = v___y_8287_;
v___y_8257_ = v___y_8288_;
v___y_8258_ = v___y_8289_;
v___y_8259_ = v___x_8295_;
goto v___jp_8248_;
}
else
{
uint64_t v___x_8296_; 
v___x_8296_ = lean_uint64_add(v___y_8291_, v___y_8290_);
v___y_8249_ = v___y_8280_;
v___y_8250_ = v___y_8279_;
v___y_8251_ = v___y_8281_;
v___y_8252_ = v___y_8283_;
v___y_8253_ = v___y_8282_;
v___y_8254_ = v___y_8285_;
v___y_8255_ = v___y_8286_;
v___y_8256_ = v___y_8287_;
v___y_8257_ = v___y_8288_;
v___y_8258_ = v___y_8289_;
v___y_8259_ = v___x_8296_;
goto v___jp_8248_;
}
}
v___jp_8297_:
{
uint64_t v___x_8313_; uint8_t v___x_8314_; 
v___x_8313_ = lean_uint64_shift_right(v___y_8303_, v___y_8299_);
v___x_8314_ = lean_uint64_dec_eq(v___x_8313_, v___y_8305_);
if (v___x_8314_ == 0)
{
uint64_t v___x_8315_; 
v___x_8315_ = lean_uint64_add(v___y_8304_, v___y_8299_);
v___y_8279_ = v___y_8298_;
v___y_8280_ = v___y_8305_;
v___y_8281_ = v___y_8306_;
v___y_8282_ = v___y_8307_;
v___y_8283_ = v___y_8308_;
v___y_8284_ = v___y_8312_;
v___y_8285_ = v___y_8300_;
v___y_8286_ = v___y_8301_;
v___y_8287_ = v___y_8309_;
v___y_8288_ = v___y_8302_;
v___y_8289_ = v___y_8310_;
v___y_8290_ = v___y_8311_;
v___y_8291_ = v___x_8315_;
goto v___jp_8278_;
}
else
{
v___y_8279_ = v___y_8298_;
v___y_8280_ = v___y_8305_;
v___y_8281_ = v___y_8306_;
v___y_8282_ = v___y_8307_;
v___y_8283_ = v___y_8308_;
v___y_8284_ = v___y_8312_;
v___y_8285_ = v___y_8300_;
v___y_8286_ = v___y_8301_;
v___y_8287_ = v___y_8309_;
v___y_8288_ = v___y_8302_;
v___y_8289_ = v___y_8310_;
v___y_8290_ = v___y_8311_;
v___y_8291_ = v___y_8304_;
goto v___jp_8278_;
}
}
v___jp_8316_:
{
uint64_t v___x_8330_; uint64_t v___x_8331_; uint8_t v___x_8332_; 
v___x_8330_ = 2ULL;
v___x_8331_ = lean_uint64_shift_right(v___y_8326_, v___x_8330_);
v___x_8332_ = lean_uint64_dec_eq(v___x_8331_, v___y_8317_);
if (v___x_8332_ == 0)
{
v___y_8298_ = v___y_8318_;
v___y_8299_ = v___x_8330_;
v___y_8300_ = v___y_8322_;
v___y_8301_ = v___y_8323_;
v___y_8302_ = v___y_8325_;
v___y_8303_ = v___y_8326_;
v___y_8304_ = v___y_8329_;
v___y_8305_ = v___y_8317_;
v___y_8306_ = v___y_8319_;
v___y_8307_ = v___y_8321_;
v___y_8308_ = v___y_8320_;
v___y_8309_ = v___y_8324_;
v___y_8310_ = v___y_8327_;
v___y_8311_ = v___y_8328_;
v___y_8312_ = v___x_8331_;
goto v___jp_8297_;
}
else
{
v___y_8298_ = v___y_8318_;
v___y_8299_ = v___x_8330_;
v___y_8300_ = v___y_8322_;
v___y_8301_ = v___y_8323_;
v___y_8302_ = v___y_8325_;
v___y_8303_ = v___y_8326_;
v___y_8304_ = v___y_8329_;
v___y_8305_ = v___y_8317_;
v___y_8306_ = v___y_8319_;
v___y_8307_ = v___y_8321_;
v___y_8308_ = v___y_8320_;
v___y_8309_ = v___y_8324_;
v___y_8310_ = v___y_8327_;
v___y_8311_ = v___y_8328_;
v___y_8312_ = v___y_8326_;
goto v___jp_8297_;
}
}
v___jp_8333_:
{
uint64_t v___x_8349_; uint8_t v___x_8350_; 
v___x_8349_ = lean_uint64_shift_right(v___y_8344_, v___y_8335_);
v___x_8350_ = lean_uint64_dec_eq(v___x_8349_, v___y_8340_);
if (v___x_8350_ == 0)
{
uint64_t v___x_8351_; 
v___x_8351_ = lean_uint64_add(v___y_8339_, v___y_8335_);
v___y_8317_ = v___y_8340_;
v___y_8318_ = v___y_8334_;
v___y_8319_ = v___y_8341_;
v___y_8320_ = v___y_8342_;
v___y_8321_ = v___y_8343_;
v___y_8322_ = v___y_8336_;
v___y_8323_ = v___y_8337_;
v___y_8324_ = v___y_8345_;
v___y_8325_ = v___y_8338_;
v___y_8326_ = v___y_8348_;
v___y_8327_ = v___y_8346_;
v___y_8328_ = v___y_8347_;
v___y_8329_ = v___x_8351_;
goto v___jp_8316_;
}
else
{
v___y_8317_ = v___y_8340_;
v___y_8318_ = v___y_8334_;
v___y_8319_ = v___y_8341_;
v___y_8320_ = v___y_8342_;
v___y_8321_ = v___y_8343_;
v___y_8322_ = v___y_8336_;
v___y_8323_ = v___y_8337_;
v___y_8324_ = v___y_8345_;
v___y_8325_ = v___y_8338_;
v___y_8326_ = v___y_8348_;
v___y_8327_ = v___y_8346_;
v___y_8328_ = v___y_8347_;
v___y_8329_ = v___y_8339_;
goto v___jp_8316_;
}
}
v___jp_8352_:
{
uint64_t v___x_8366_; uint64_t v___x_8367_; uint8_t v___x_8368_; 
v___x_8366_ = 4ULL;
v___x_8367_ = lean_uint64_shift_right(v___y_8358_, v___x_8366_);
v___x_8368_ = lean_uint64_dec_eq(v___x_8367_, v___y_8353_);
if (v___x_8368_ == 0)
{
v___y_8334_ = v___y_8354_;
v___y_8335_ = v___x_8366_;
v___y_8336_ = v___y_8359_;
v___y_8337_ = v___y_8360_;
v___y_8338_ = v___y_8362_;
v___y_8339_ = v___y_8365_;
v___y_8340_ = v___y_8353_;
v___y_8341_ = v___y_8355_;
v___y_8342_ = v___y_8357_;
v___y_8343_ = v___y_8356_;
v___y_8344_ = v___y_8358_;
v___y_8345_ = v___y_8361_;
v___y_8346_ = v___y_8363_;
v___y_8347_ = v___y_8364_;
v___y_8348_ = v___x_8367_;
goto v___jp_8333_;
}
else
{
v___y_8334_ = v___y_8354_;
v___y_8335_ = v___x_8366_;
v___y_8336_ = v___y_8359_;
v___y_8337_ = v___y_8360_;
v___y_8338_ = v___y_8362_;
v___y_8339_ = v___y_8365_;
v___y_8340_ = v___y_8353_;
v___y_8341_ = v___y_8355_;
v___y_8342_ = v___y_8357_;
v___y_8343_ = v___y_8356_;
v___y_8344_ = v___y_8358_;
v___y_8345_ = v___y_8361_;
v___y_8346_ = v___y_8363_;
v___y_8347_ = v___y_8364_;
v___y_8348_ = v___y_8358_;
goto v___jp_8333_;
}
}
v___jp_8369_:
{
uint64_t v___x_8385_; uint8_t v___x_8386_; 
v___x_8385_ = lean_uint64_shift_right(v___y_8372_, v___y_8374_);
v___x_8386_ = lean_uint64_dec_eq(v___x_8385_, v___y_8376_);
if (v___x_8386_ == 0)
{
uint64_t v___x_8387_; 
v___x_8387_ = lean_uint64_add(v___y_8381_, v___y_8374_);
v___y_8353_ = v___y_8376_;
v___y_8354_ = v___y_8370_;
v___y_8355_ = v___y_8377_;
v___y_8356_ = v___y_8378_;
v___y_8357_ = v___y_8379_;
v___y_8358_ = v___y_8384_;
v___y_8359_ = v___y_8371_;
v___y_8360_ = v___y_8373_;
v___y_8361_ = v___y_8380_;
v___y_8362_ = v___y_8375_;
v___y_8363_ = v___y_8382_;
v___y_8364_ = v___y_8383_;
v___y_8365_ = v___x_8387_;
goto v___jp_8352_;
}
else
{
v___y_8353_ = v___y_8376_;
v___y_8354_ = v___y_8370_;
v___y_8355_ = v___y_8377_;
v___y_8356_ = v___y_8378_;
v___y_8357_ = v___y_8379_;
v___y_8358_ = v___y_8384_;
v___y_8359_ = v___y_8371_;
v___y_8360_ = v___y_8373_;
v___y_8361_ = v___y_8380_;
v___y_8362_ = v___y_8375_;
v___y_8363_ = v___y_8382_;
v___y_8364_ = v___y_8383_;
v___y_8365_ = v___y_8381_;
goto v___jp_8352_;
}
}
v___jp_8388_:
{
uint64_t v___x_8402_; uint64_t v___x_8403_; uint8_t v___x_8404_; 
v___x_8402_ = 8ULL;
v___x_8403_ = lean_uint64_shift_right(v___y_8394_, v___x_8402_);
v___x_8404_ = lean_uint64_dec_eq(v___x_8403_, v___y_8389_);
if (v___x_8404_ == 0)
{
v___y_8370_ = v___y_8390_;
v___y_8371_ = v___y_8395_;
v___y_8372_ = v___y_8394_;
v___y_8373_ = v___y_8396_;
v___y_8374_ = v___x_8402_;
v___y_8375_ = v___y_8398_;
v___y_8376_ = v___y_8389_;
v___y_8377_ = v___y_8391_;
v___y_8378_ = v___y_8393_;
v___y_8379_ = v___y_8392_;
v___y_8380_ = v___y_8397_;
v___y_8381_ = v___y_8401_;
v___y_8382_ = v___y_8399_;
v___y_8383_ = v___y_8400_;
v___y_8384_ = v___x_8403_;
goto v___jp_8369_;
}
else
{
v___y_8370_ = v___y_8390_;
v___y_8371_ = v___y_8395_;
v___y_8372_ = v___y_8394_;
v___y_8373_ = v___y_8396_;
v___y_8374_ = v___x_8402_;
v___y_8375_ = v___y_8398_;
v___y_8376_ = v___y_8389_;
v___y_8377_ = v___y_8391_;
v___y_8378_ = v___y_8393_;
v___y_8379_ = v___y_8392_;
v___y_8380_ = v___y_8397_;
v___y_8381_ = v___y_8401_;
v___y_8382_ = v___y_8399_;
v___y_8383_ = v___y_8400_;
v___y_8384_ = v___y_8394_;
goto v___jp_8369_;
}
}
v___jp_8405_:
{
uint64_t v___x_8421_; uint8_t v___x_8422_; 
v___x_8421_ = lean_uint64_shift_right(v___y_8414_, v___y_8408_);
v___x_8422_ = lean_uint64_dec_eq(v___x_8421_, v___y_8412_);
if (v___x_8422_ == 0)
{
uint64_t v___x_8423_; 
v___x_8423_ = lean_uint64_add(v___y_8407_, v___y_8408_);
v___y_8389_ = v___y_8412_;
v___y_8390_ = v___y_8406_;
v___y_8391_ = v___y_8413_;
v___y_8392_ = v___y_8415_;
v___y_8393_ = v___y_8416_;
v___y_8394_ = v___y_8420_;
v___y_8395_ = v___y_8409_;
v___y_8396_ = v___y_8410_;
v___y_8397_ = v___y_8417_;
v___y_8398_ = v___y_8411_;
v___y_8399_ = v___y_8418_;
v___y_8400_ = v___y_8419_;
v___y_8401_ = v___x_8423_;
goto v___jp_8388_;
}
else
{
v___y_8389_ = v___y_8412_;
v___y_8390_ = v___y_8406_;
v___y_8391_ = v___y_8413_;
v___y_8392_ = v___y_8415_;
v___y_8393_ = v___y_8416_;
v___y_8394_ = v___y_8420_;
v___y_8395_ = v___y_8409_;
v___y_8396_ = v___y_8410_;
v___y_8397_ = v___y_8417_;
v___y_8398_ = v___y_8411_;
v___y_8399_ = v___y_8418_;
v___y_8400_ = v___y_8419_;
v___y_8401_ = v___y_8407_;
goto v___jp_8388_;
}
}
v___jp_8424_:
{
uint64_t v___x_8438_; uint64_t v___x_8439_; uint8_t v___x_8440_; 
v___x_8438_ = 16ULL;
v___x_8439_ = lean_uint64_shift_right(v___y_8428_, v___x_8438_);
v___x_8440_ = lean_uint64_dec_eq(v___x_8439_, v___y_8425_);
if (v___x_8440_ == 0)
{
v___y_8406_ = v___y_8426_;
v___y_8407_ = v___y_8437_;
v___y_8408_ = v___x_8438_;
v___y_8409_ = v___y_8431_;
v___y_8410_ = v___y_8432_;
v___y_8411_ = v___y_8434_;
v___y_8412_ = v___y_8425_;
v___y_8413_ = v___y_8427_;
v___y_8414_ = v___y_8428_;
v___y_8415_ = v___y_8430_;
v___y_8416_ = v___y_8429_;
v___y_8417_ = v___y_8433_;
v___y_8418_ = v___y_8435_;
v___y_8419_ = v___y_8436_;
v___y_8420_ = v___x_8439_;
goto v___jp_8405_;
}
else
{
v___y_8406_ = v___y_8426_;
v___y_8407_ = v___y_8437_;
v___y_8408_ = v___x_8438_;
v___y_8409_ = v___y_8431_;
v___y_8410_ = v___y_8432_;
v___y_8411_ = v___y_8434_;
v___y_8412_ = v___y_8425_;
v___y_8413_ = v___y_8427_;
v___y_8414_ = v___y_8428_;
v___y_8415_ = v___y_8430_;
v___y_8416_ = v___y_8429_;
v___y_8417_ = v___y_8433_;
v___y_8418_ = v___y_8435_;
v___y_8419_ = v___y_8436_;
v___y_8420_ = v___y_8428_;
goto v___jp_8405_;
}
}
v___jp_8441_:
{
uint64_t v___x_8456_; uint8_t v___x_8457_; 
v___x_8456_ = lean_uint64_shift_right(v___y_8452_, v___y_8448_);
v___x_8457_ = lean_uint64_dec_eq(v___x_8456_, v___y_8446_);
if (v___x_8457_ == 0)
{
v___y_8425_ = v___y_8446_;
v___y_8426_ = v___y_8442_;
v___y_8427_ = v___y_8447_;
v___y_8428_ = v___y_8455_;
v___y_8429_ = v___y_8449_;
v___y_8430_ = v___y_8450_;
v___y_8431_ = v___y_8443_;
v___y_8432_ = v___y_8444_;
v___y_8433_ = v___y_8451_;
v___y_8434_ = v___y_8445_;
v___y_8435_ = v___y_8453_;
v___y_8436_ = v___y_8454_;
v___y_8437_ = v___y_8448_;
goto v___jp_8424_;
}
else
{
v___y_8425_ = v___y_8446_;
v___y_8426_ = v___y_8442_;
v___y_8427_ = v___y_8447_;
v___y_8428_ = v___y_8455_;
v___y_8429_ = v___y_8449_;
v___y_8430_ = v___y_8450_;
v___y_8431_ = v___y_8443_;
v___y_8432_ = v___y_8444_;
v___y_8433_ = v___y_8451_;
v___y_8434_ = v___y_8445_;
v___y_8435_ = v___y_8453_;
v___y_8436_ = v___y_8454_;
v___y_8437_ = v___y_8446_;
goto v___jp_8424_;
}
}
v___jp_8460_:
{
if (v___y_8461_ == 0)
{
lean_object* v___x_8462_; uint8_t v___x_8463_; 
v___x_8462_ = lean_unsigned_to_nat(1073741824u);
v___x_8463_ = lean_nat_dec_lt(v___x_8462_, v_n_8458_);
if (v___x_8463_ == 0)
{
if (v_valid_8247_ == 0)
{
uint32_t v___x_8464_; 
v___x_8464_ = 0;
return v___x_8464_;
}
else
{
uint8_t v_valid_8465_; 
v_valid_8465_ = lean_ctor_get_uint8(v_y_8097_, sizeof(void*)*2 + 4);
if (v_valid_8465_ == 0)
{
uint32_t v___x_8466_; 
v___x_8466_ = 0;
return v___x_8466_;
}
else
{
lean_object* v_values_8467_; uint32_t v_maxIndex_8468_; uint64_t v___x_8469_; double v___x_8470_; double v_sum_8471_; uint64_t v_sumWord_8472_; uint64_t v___x_8473_; uint64_t v___x_8474_; uint64_t v___x_8475_; uint64_t v___x_8476_; uint64_t v___x_8477_; uint64_t v___x_8478_; uint32_t v___x_8479_; uint32_t v___x_8480_; uint32_t v___x_8481_; uint32_t v___x_8482_; uint32_t v_magnitude_8483_; uint64_t v___x_8484_; uint64_t v___x_8485_; uint32_t v___x_8486_; uint32_t v___x_8487_; uint32_t v___x_8488_; uint32_t v_guess_8489_; lean_object* v___x_8490_; uint8_t v___x_8491_; 
v_values_8467_ = lean_ctor_get(v_y_8097_, 1);
v_maxIndex_8468_ = lean_ctor_get_uint32(v_y_8097_, sizeof(void*)*2);
v___x_8469_ = 0ULL;
v___x_8470_ = lean_float_once(&lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00Submission_R24PortableF64_prepare_spec__0___closed__0, &lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00Submission_R24PortableF64_prepare_spec__0___closed__0_once, _init_lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00Submission_R24PortableF64_prepare_spec__0___closed__0);
v_sum_8471_ = lp_competition_Submission_R24PortableF64_sumRemaining(v_values_8245_, v_values_8467_, v___x_8459_, v___x_8470_, v_n_8458_);
v_sumWord_8472_ = lean_float_to_bits(v_sum_8471_);
v___x_8473_ = 9223372036854775807ULL;
v___x_8474_ = lean_uint64_land(v_sumWord_8472_, v___x_8473_);
v___x_8475_ = 268435456ULL;
v___x_8476_ = lean_uint64_add(v___x_8474_, v___x_8475_);
v___x_8477_ = 29ULL;
v___x_8478_ = lean_uint64_shift_right(v___x_8476_, v___x_8477_);
v___x_8479_ = lean_uint64_to_uint32(v___x_8478_);
v___x_8480_ = 3221225472;
v___x_8481_ = lean_uint32_sub(v___x_8479_, v___x_8480_);
v___x_8482_ = 2147483647;
v_magnitude_8483_ = lean_uint32_land(v___x_8481_, v___x_8482_);
v___x_8484_ = 32ULL;
v___x_8485_ = lean_uint64_shift_right(v_sumWord_8472_, v___x_8484_);
v___x_8486_ = lean_uint64_to_uint32(v___x_8485_);
v___x_8487_ = 2147483648;
v___x_8488_ = lean_uint32_land(v___x_8486_, v___x_8487_);
v_guess_8489_ = lean_uint32_lor(v___x_8488_, v_magnitude_8483_);
v___x_8490_ = lean_unsigned_to_nat(1u);
v___x_8491_ = lean_nat_dec_le(v_n_8458_, v___x_8490_);
if (v___x_8491_ == 0)
{
uint64_t v___x_8492_; uint64_t v___x_8493_; uint64_t v___x_8494_; uint64_t v___x_8495_; uint8_t v___x_8496_; 
v___x_8492_ = lean_uint64_of_nat(v_n_8458_);
v___x_8493_ = 1ULL;
v___x_8494_ = lean_uint64_sub(v___x_8492_, v___x_8493_);
v___x_8495_ = lean_uint64_shift_right(v___x_8494_, v___x_8484_);
v___x_8496_ = lean_uint64_dec_eq(v___x_8495_, v___x_8469_);
if (v___x_8496_ == 0)
{
v___y_8442_ = v_valid_8465_;
v___y_8443_ = v___x_8475_;
v___y_8444_ = v___x_8477_;
v___y_8445_ = v_guess_8489_;
v___y_8446_ = v___x_8469_;
v___y_8447_ = v_sum_8471_;
v___y_8448_ = v___x_8484_;
v___y_8449_ = v_maxIndex_8468_;
v___y_8450_ = v___x_8482_;
v___y_8451_ = v___x_8487_;
v___y_8452_ = v___x_8494_;
v___y_8453_ = v_sumWord_8472_;
v___y_8454_ = v___x_8493_;
v___y_8455_ = v___x_8495_;
goto v___jp_8441_;
}
else
{
v___y_8442_ = v_valid_8465_;
v___y_8443_ = v___x_8475_;
v___y_8444_ = v___x_8477_;
v___y_8445_ = v_guess_8489_;
v___y_8446_ = v___x_8469_;
v___y_8447_ = v_sum_8471_;
v___y_8448_ = v___x_8484_;
v___y_8449_ = v_maxIndex_8468_;
v___y_8450_ = v___x_8482_;
v___y_8451_ = v___x_8487_;
v___y_8452_ = v___x_8494_;
v___y_8453_ = v_sumWord_8472_;
v___y_8454_ = v___x_8493_;
v___y_8455_ = v___x_8494_;
goto v___jp_8441_;
}
}
else
{
v___y_8249_ = v___x_8469_;
v___y_8250_ = v_valid_8465_;
v___y_8251_ = v_sum_8471_;
v___y_8252_ = v___x_8482_;
v___y_8253_ = v_maxIndex_8468_;
v___y_8254_ = v___x_8475_;
v___y_8255_ = v___x_8477_;
v___y_8256_ = v___x_8487_;
v___y_8257_ = v_guess_8489_;
v___y_8258_ = v_sumWord_8472_;
v___y_8259_ = v___x_8469_;
goto v___jp_8248_;
}
}
}
}
else
{
uint32_t v___x_8497_; 
v___x_8497_ = 0;
return v___x_8497_;
}
}
else
{
uint32_t v___x_8498_; 
v___x_8498_ = 0;
return v___x_8498_;
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_R24PortableF64_attemptPrepared___boxed(lean_object* v_x_8504_, lean_object* v_y_8505_){
_start:
{
uint32_t v_res_8506_; lean_object* v_r_8507_; 
v_res_8506_ = lp_competition_Submission_R24PortableF64_attemptPrepared(v_x_8504_, v_y_8505_);
lean_dec_ref(v_y_8505_);
lean_dec_ref(v_x_8504_);
v_r_8507_ = lean_box_uint32(v_res_8506_);
return v_r_8507_;
}
}
LEAN_EXPORT uint32_t lp_competition_Submission_R24PortableF64_attemptCold(lean_object* v_x_8508_, lean_object* v_y_8509_){
_start:
{
lean_object* v___x_8510_; uint8_t v___y_8512_; lean_object* v___x_8520_; uint8_t v___x_8521_; 
v___x_8510_ = lean_array_get_size(v_x_8508_);
v___x_8520_ = lean_unsigned_to_nat(0u);
v___x_8521_ = lean_nat_dec_eq(v___x_8510_, v___x_8520_);
if (v___x_8521_ == 0)
{
lean_object* v___x_8522_; uint8_t v___x_8523_; 
v___x_8522_ = lean_array_get_size(v_y_8509_);
v___x_8523_ = lean_nat_dec_eq(v___x_8510_, v___x_8522_);
if (v___x_8523_ == 0)
{
uint32_t v___x_8524_; 
lean_dec_ref(v_y_8509_);
lean_dec_ref(v_x_8508_);
v___x_8524_ = 0;
return v___x_8524_;
}
else
{
v___y_8512_ = v___x_8521_;
goto v___jp_8511_;
}
}
else
{
v___y_8512_ = v___x_8521_;
goto v___jp_8511_;
}
v___jp_8511_:
{
if (v___y_8512_ == 0)
{
lean_object* v___x_8513_; uint8_t v___x_8514_; 
v___x_8513_ = lean_unsigned_to_nat(1073741824u);
v___x_8514_ = lean_nat_dec_lt(v___x_8513_, v___x_8510_);
if (v___x_8514_ == 0)
{
lean_object* v___x_8515_; lean_object* v___x_8516_; uint32_t v___x_8517_; 
v___x_8515_ = lp_competition_Submission_R24PortableF64_prepare(v_x_8508_);
v___x_8516_ = lp_competition_Submission_R24PortableF64_prepare(v_y_8509_);
v___x_8517_ = lp_competition_Submission_R24PortableF64_attemptPrepared(v___x_8515_, v___x_8516_);
lean_dec_ref(v___x_8516_);
lean_dec_ref(v___x_8515_);
return v___x_8517_;
}
else
{
uint32_t v___x_8518_; 
lean_dec_ref(v_y_8509_);
lean_dec_ref(v_x_8508_);
v___x_8518_ = 0;
return v___x_8518_;
}
}
else
{
uint32_t v___x_8519_; 
lean_dec_ref(v_y_8509_);
lean_dec_ref(v_x_8508_);
v___x_8519_ = 0;
return v___x_8519_;
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_R24PortableF64_attemptCold___boxed(lean_object* v_x_8525_, lean_object* v_y_8526_){
_start:
{
uint32_t v_res_8527_; lean_object* v_r_8528_; 
v_res_8527_ = lp_competition_Submission_R24PortableF64_attemptCold(v_x_8525_, v_y_8526_);
v_r_8528_ = lean_box_uint32(v_res_8527_);
return v_r_8528_;
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_R24DotProbe_prepareEagerOperand(lean_object* v_a_8529_){
_start:
{
lean_object* v___x_8530_; lean_object* v___x_8531_; lean_object* v___x_8532_; 
lean_inc_ref(v_a_8529_);
v___x_8530_ = lp_competition_Submission_R24ExactDotCost_prepareOperand(v_a_8529_);
v___x_8531_ = lp_competition_Submission_R24PortableF64_prepare(v_a_8529_);
v___x_8532_ = lean_alloc_ctor(0, 2, 0);
lean_ctor_set(v___x_8532_, 0, v___x_8530_);
lean_ctor_set(v___x_8532_, 1, v___x_8531_);
return v___x_8532_;
}
}
LEAN_EXPORT uint32_t lp_competition_Submission_R24DotProbe_exactFull(lean_object* v_a_8533_, lean_object* v_b_8534_){
_start:
{
uint32_t v___x_8535_; 
v___x_8535_ = lp_competition_Submission_R24ExactDotTiered_fullv2(v_a_8533_, v_b_8534_);
return v___x_8535_;
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_R24DotProbe_exactFull___boxed(lean_object* v_a_8536_, lean_object* v_b_8537_){
_start:
{
uint32_t v_res_8538_; lean_object* v_r_8539_; 
v_res_8538_ = lp_competition_Submission_R24DotProbe_exactFull(v_a_8536_, v_b_8537_);
v_r_8539_ = lean_box_uint32(v_res_8538_);
return v_r_8539_;
}
}
LEAN_EXPORT uint32_t lp_competition_Submission_R24DotProbe_exactPrepared(lean_object* v_a_8540_, lean_object* v_b_8541_){
_start:
{
uint32_t v___x_8542_; 
v___x_8542_ = lp_competition_Submission_R24ExactDotTiered_prepared2v2(v_a_8540_, v_b_8541_);
return v___x_8542_;
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_R24DotProbe_exactPrepared___boxed(lean_object* v_a_8543_, lean_object* v_b_8544_){
_start:
{
uint32_t v_res_8545_; lean_object* v_r_8546_; 
v_res_8545_ = lp_competition_Submission_R24DotProbe_exactPrepared(v_a_8543_, v_b_8544_);
v_r_8546_ = lean_box_uint32(v_res_8545_);
return v_r_8546_;
}
}
LEAN_EXPORT uint32_t lp_competition_Submission_R24DotProbe_eagerPrepared(lean_object* v_a_8547_, lean_object* v_b_8548_){
_start:
{
lean_object* v_exact_8549_; lean_object* v_fp_8550_; lean_object* v_exact_8551_; lean_object* v_fp_8552_; uint32_t v_q_8553_; uint32_t v___x_8554_; uint8_t v___x_8555_; 
v_exact_8549_ = lean_ctor_get(v_a_8547_, 0);
lean_inc_ref(v_exact_8549_);
v_fp_8550_ = lean_ctor_get(v_a_8547_, 1);
lean_inc_ref(v_fp_8550_);
lean_dec_ref(v_a_8547_);
v_exact_8551_ = lean_ctor_get(v_b_8548_, 0);
lean_inc_ref(v_exact_8551_);
v_fp_8552_ = lean_ctor_get(v_b_8548_, 1);
lean_inc_ref(v_fp_8552_);
lean_dec_ref(v_b_8548_);
v_q_8553_ = lp_competition_Submission_R24PortableF64_attemptPrepared(v_fp_8550_, v_fp_8552_);
lean_dec_ref(v_fp_8552_);
lean_dec_ref(v_fp_8550_);
v___x_8554_ = 0;
v___x_8555_ = lean_uint32_dec_eq(v_q_8553_, v___x_8554_);
if (v___x_8555_ == 0)
{
lean_dec_ref(v_exact_8551_);
lean_dec_ref(v_exact_8549_);
return v_q_8553_;
}
else
{
uint32_t v___x_8556_; 
v___x_8556_ = lp_competition_Submission_R24ExactDotTiered_prepared2v2(v_exact_8549_, v_exact_8551_);
return v___x_8556_;
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_R24DotProbe_eagerPrepared___boxed(lean_object* v_a_8557_, lean_object* v_b_8558_){
_start:
{
uint32_t v_res_8559_; lean_object* v_r_8560_; 
v_res_8559_ = lp_competition_Submission_R24DotProbe_eagerPrepared(v_a_8557_, v_b_8558_);
v_r_8560_ = lean_box_uint32(v_res_8559_);
return v_r_8560_;
}
}
LEAN_EXPORT uint32_t lp_competition_Submission_R24DotProbe_eagerFull(lean_object* v_a_8561_, lean_object* v_b_8562_){
_start:
{
lean_object* v___x_8563_; lean_object* v___x_8564_; uint32_t v___x_8565_; 
v___x_8563_ = lp_competition_Submission_R24DotProbe_prepareEagerOperand(v_a_8561_);
v___x_8564_ = lp_competition_Submission_R24DotProbe_prepareEagerOperand(v_b_8562_);
v___x_8565_ = lp_competition_Submission_R24DotProbe_eagerPrepared(v___x_8563_, v___x_8564_);
return v___x_8565_;
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_R24DotProbe_eagerFull___boxed(lean_object* v_a_8566_, lean_object* v_b_8567_){
_start:
{
uint32_t v_res_8568_; lean_object* v_r_8569_; 
v_res_8568_ = lp_competition_Submission_R24DotProbe_eagerFull(v_a_8566_, v_b_8567_);
v_r_8569_ = lean_box_uint32(v_res_8568_);
return v_r_8569_;
}
}
LEAN_EXPORT uint32_t lp_competition_Submission_R24DotProbe_lazyPrepared(lean_object* v_a_8570_, lean_object* v_b_8571_){
_start:
{
uint32_t v_q_8572_; uint32_t v___x_8573_; uint8_t v___x_8574_; 
v_q_8572_ = lp_competition_Submission_R24PortableF64_attemptPrepared(v_a_8570_, v_b_8571_);
v___x_8573_ = 0;
v___x_8574_ = lean_uint32_dec_eq(v_q_8572_, v___x_8573_);
if (v___x_8574_ == 0)
{
lean_dec_ref(v_b_8571_);
lean_dec_ref(v_a_8570_);
return v_q_8572_;
}
else
{
lean_object* v_raw_8575_; lean_object* v_raw_8576_; uint32_t v___x_8577_; 
v_raw_8575_ = lean_ctor_get(v_a_8570_, 0);
lean_inc_ref(v_raw_8575_);
lean_dec_ref(v_a_8570_);
v_raw_8576_ = lean_ctor_get(v_b_8571_, 0);
lean_inc_ref(v_raw_8576_);
lean_dec_ref(v_b_8571_);
v___x_8577_ = lp_competition_Submission_R24ExactDotTiered_fullv2(v_raw_8575_, v_raw_8576_);
return v___x_8577_;
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_R24DotProbe_lazyPrepared___boxed(lean_object* v_a_8578_, lean_object* v_b_8579_){
_start:
{
uint32_t v_res_8580_; lean_object* v_r_8581_; 
v_res_8580_ = lp_competition_Submission_R24DotProbe_lazyPrepared(v_a_8578_, v_b_8579_);
v_r_8581_ = lean_box_uint32(v_res_8580_);
return v_r_8581_;
}
}
LEAN_EXPORT uint32_t lp_competition_Submission_R24DotProbe_lazyFull(lean_object* v_a_8582_, lean_object* v_b_8583_){
_start:
{
uint32_t v_q_8584_; uint32_t v___x_8585_; uint8_t v___x_8586_; 
lean_inc_ref(v_b_8583_);
lean_inc_ref(v_a_8582_);
v_q_8584_ = lp_competition_Submission_R24PortableF64_attemptCold(v_a_8582_, v_b_8583_);
v___x_8585_ = 0;
v___x_8586_ = lean_uint32_dec_eq(v_q_8584_, v___x_8585_);
if (v___x_8586_ == 0)
{
lean_dec_ref(v_b_8583_);
lean_dec_ref(v_a_8582_);
return v_q_8584_;
}
else
{
uint32_t v___x_8587_; 
v___x_8587_ = lp_competition_Submission_R24ExactDotTiered_fullv2(v_a_8582_, v_b_8583_);
return v___x_8587_;
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_R24DotProbe_lazyFull___boxed(lean_object* v_a_8588_, lean_object* v_b_8589_){
_start:
{
uint32_t v_res_8590_; lean_object* v_r_8591_; 
v_res_8590_ = lp_competition_Submission_R24DotProbe_lazyFull(v_a_8588_, v_b_8589_);
v_r_8591_ = lean_box_uint32(v_res_8590_);
return v_r_8591_;
}
}
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00Submission_R24GenericDotBank_exactBank_spec__1(lean_object* v_a_8592_, lean_object* v_as_8593_, size_t v_sz_8594_, size_t v_i_8595_, lean_object* v_b_8596_){
_start:
{
uint8_t v___x_8597_; 
v___x_8597_ = lean_usize_dec_lt(v_i_8595_, v_sz_8594_);
if (v___x_8597_ == 0)
{
lean_dec_ref(v_a_8592_);
return v_b_8596_;
}
else
{
lean_object* v_a_8598_; uint32_t v___x_8599_; lean_object* v___x_8600_; lean_object* v___x_8601_; size_t v___x_8602_; size_t v___x_8603_; 
v_a_8598_ = lean_array_uget_borrowed(v_as_8593_, v_i_8595_);
lean_inc(v_a_8598_);
lean_inc_ref(v_a_8592_);
v___x_8599_ = lp_competition_Submission_R24DotProbe_exactPrepared(v_a_8592_, v_a_8598_);
v___x_8600_ = lean_box_uint32(v___x_8599_);
v___x_8601_ = lean_array_push(v_b_8596_, v___x_8600_);
v___x_8602_ = ((size_t)1ULL);
v___x_8603_ = lean_usize_add(v_i_8595_, v___x_8602_);
v_i_8595_ = v___x_8603_;
v_b_8596_ = v___x_8601_;
goto _start;
}
}
}
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00Submission_R24GenericDotBank_exactBank_spec__1___boxed(lean_object* v_a_8605_, lean_object* v_as_8606_, lean_object* v_sz_8607_, lean_object* v_i_8608_, lean_object* v_b_8609_){
_start:
{
size_t v_sz_boxed_8610_; size_t v_i_boxed_8611_; lean_object* v_res_8612_; 
v_sz_boxed_8610_ = lean_unbox_usize(v_sz_8607_);
lean_dec(v_sz_8607_);
v_i_boxed_8611_ = lean_unbox_usize(v_i_8608_);
lean_dec(v_i_8608_);
v_res_8612_ = lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00Submission_R24GenericDotBank_exactBank_spec__1(v_a_8605_, v_as_8606_, v_sz_boxed_8610_, v_i_boxed_8611_, v_b_8609_);
lean_dec_ref(v_as_8606_);
return v_res_8612_;
}
}
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00Submission_R24GenericDotBank_exactBank_spec__2(lean_object* v___x_8613_, lean_object* v_as_8614_, size_t v_sz_8615_, size_t v_i_8616_, lean_object* v_b_8617_){
_start:
{
uint8_t v___x_8618_; 
v___x_8618_ = lean_usize_dec_lt(v_i_8616_, v_sz_8615_);
if (v___x_8618_ == 0)
{
return v_b_8617_;
}
else
{
lean_object* v_a_8619_; size_t v_sz_8620_; size_t v___x_8621_; lean_object* v___x_8622_; size_t v___x_8623_; size_t v___x_8624_; 
v_a_8619_ = lean_array_uget_borrowed(v_as_8614_, v_i_8616_);
v_sz_8620_ = lean_array_size(v___x_8613_);
v___x_8621_ = ((size_t)0ULL);
lean_inc(v_a_8619_);
v___x_8622_ = lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00Submission_R24GenericDotBank_exactBank_spec__1(v_a_8619_, v___x_8613_, v_sz_8620_, v___x_8621_, v_b_8617_);
v___x_8623_ = ((size_t)1ULL);
v___x_8624_ = lean_usize_add(v_i_8616_, v___x_8623_);
v_i_8616_ = v___x_8624_;
v_b_8617_ = v___x_8622_;
goto _start;
}
}
}
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00Submission_R24GenericDotBank_exactBank_spec__2___boxed(lean_object* v___x_8626_, lean_object* v_as_8627_, lean_object* v_sz_8628_, lean_object* v_i_8629_, lean_object* v_b_8630_){
_start:
{
size_t v_sz_boxed_8631_; size_t v_i_boxed_8632_; lean_object* v_res_8633_; 
v_sz_boxed_8631_ = lean_unbox_usize(v_sz_8628_);
lean_dec(v_sz_8628_);
v_i_boxed_8632_ = lean_unbox_usize(v_i_8629_);
lean_dec(v_i_8629_);
v_res_8633_ = lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00Submission_R24GenericDotBank_exactBank_spec__2(v___x_8626_, v_as_8627_, v_sz_boxed_8631_, v_i_boxed_8632_, v_b_8630_);
lean_dec_ref(v_as_8627_);
lean_dec_ref(v___x_8626_);
return v_res_8633_;
}
}
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00Submission_R24GenericDotBank_exactBank_spec__0(lean_object* v_as_8634_, size_t v_sz_8635_, size_t v_i_8636_, lean_object* v_b_8637_){
_start:
{
uint8_t v___x_8638_; 
v___x_8638_ = lean_usize_dec_lt(v_i_8636_, v_sz_8635_);
if (v___x_8638_ == 0)
{
return v_b_8637_;
}
else
{
lean_object* v_a_8639_; lean_object* v___x_8640_; lean_object* v___x_8641_; size_t v___x_8642_; size_t v___x_8643_; 
v_a_8639_ = lean_array_uget_borrowed(v_as_8634_, v_i_8636_);
lean_inc(v_a_8639_);
v___x_8640_ = lp_competition_Submission_R24ExactDotCost_prepareOperand(v_a_8639_);
v___x_8641_ = lean_array_push(v_b_8637_, v___x_8640_);
v___x_8642_ = ((size_t)1ULL);
v___x_8643_ = lean_usize_add(v_i_8636_, v___x_8642_);
v_i_8636_ = v___x_8643_;
v_b_8637_ = v___x_8641_;
goto _start;
}
}
}
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00Submission_R24GenericDotBank_exactBank_spec__0___boxed(lean_object* v_as_8645_, lean_object* v_sz_8646_, lean_object* v_i_8647_, lean_object* v_b_8648_){
_start:
{
size_t v_sz_boxed_8649_; size_t v_i_boxed_8650_; lean_object* v_res_8651_; 
v_sz_boxed_8649_ = lean_unbox_usize(v_sz_8646_);
lean_dec(v_sz_8646_);
v_i_boxed_8650_ = lean_unbox_usize(v_i_8647_);
lean_dec(v_i_8647_);
v_res_8651_ = lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00Submission_R24GenericDotBank_exactBank_spec__0(v_as_8645_, v_sz_boxed_8649_, v_i_boxed_8650_, v_b_8648_);
lean_dec_ref(v_as_8645_);
return v_res_8651_;
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_R24GenericDotBank_exactBank(lean_object* v_rowsA_8652_, lean_object* v_rowsB_8653_){
_start:
{
lean_object* v___x_8654_; lean_object* v_a_8655_; size_t v_sz_8656_; size_t v___x_8657_; lean_object* v___x_8658_; lean_object* v___x_8659_; lean_object* v___x_8660_; size_t v_sz_8661_; lean_object* v___x_8662_; lean_object* v___x_8663_; lean_object* v___x_8664_; size_t v_sz_8665_; lean_object* v___x_8666_; 
v___x_8654_ = lean_array_get_size(v_rowsA_8652_);
v_a_8655_ = lean_mk_empty_array_with_capacity(v___x_8654_);
v_sz_8656_ = lean_array_size(v_rowsA_8652_);
v___x_8657_ = ((size_t)0ULL);
v___x_8658_ = lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00Submission_R24GenericDotBank_exactBank_spec__0(v_rowsA_8652_, v_sz_8656_, v___x_8657_, v_a_8655_);
v___x_8659_ = lean_array_get_size(v_rowsB_8653_);
v___x_8660_ = lean_mk_empty_array_with_capacity(v___x_8659_);
v_sz_8661_ = lean_array_size(v_rowsB_8653_);
v___x_8662_ = lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00Submission_R24GenericDotBank_exactBank_spec__0(v_rowsB_8653_, v_sz_8661_, v___x_8657_, v___x_8660_);
v___x_8663_ = lean_nat_mul(v___x_8654_, v___x_8659_);
v___x_8664_ = lean_mk_empty_array_with_capacity(v___x_8663_);
lean_dec(v___x_8663_);
v_sz_8665_ = lean_array_size(v___x_8658_);
v___x_8666_ = lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00Submission_R24GenericDotBank_exactBank_spec__2(v___x_8662_, v___x_8658_, v_sz_8665_, v___x_8657_, v___x_8664_);
lean_dec_ref(v___x_8658_);
lean_dec_ref(v___x_8662_);
return v___x_8666_;
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_R24GenericDotBank_exactBank___boxed(lean_object* v_rowsA_8667_, lean_object* v_rowsB_8668_){
_start:
{
lean_object* v_res_8669_; 
v_res_8669_ = lp_competition_Submission_R24GenericDotBank_exactBank(v_rowsA_8667_, v_rowsB_8668_);
lean_dec_ref(v_rowsB_8668_);
lean_dec_ref(v_rowsA_8667_);
return v_res_8669_;
}
}
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00Submission_R24GenericDotBank_eagerBank_spec__0(lean_object* v_as_8670_, size_t v_sz_8671_, size_t v_i_8672_, lean_object* v_b_8673_){
_start:
{
uint8_t v___x_8674_; 
v___x_8674_ = lean_usize_dec_lt(v_i_8672_, v_sz_8671_);
if (v___x_8674_ == 0)
{
return v_b_8673_;
}
else
{
lean_object* v_a_8675_; lean_object* v___x_8676_; lean_object* v___x_8677_; size_t v___x_8678_; size_t v___x_8679_; 
v_a_8675_ = lean_array_uget_borrowed(v_as_8670_, v_i_8672_);
lean_inc(v_a_8675_);
v___x_8676_ = lp_competition_Submission_R24DotProbe_prepareEagerOperand(v_a_8675_);
v___x_8677_ = lean_array_push(v_b_8673_, v___x_8676_);
v___x_8678_ = ((size_t)1ULL);
v___x_8679_ = lean_usize_add(v_i_8672_, v___x_8678_);
v_i_8672_ = v___x_8679_;
v_b_8673_ = v___x_8677_;
goto _start;
}
}
}
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00Submission_R24GenericDotBank_eagerBank_spec__0___boxed(lean_object* v_as_8681_, lean_object* v_sz_8682_, lean_object* v_i_8683_, lean_object* v_b_8684_){
_start:
{
size_t v_sz_boxed_8685_; size_t v_i_boxed_8686_; lean_object* v_res_8687_; 
v_sz_boxed_8685_ = lean_unbox_usize(v_sz_8682_);
lean_dec(v_sz_8682_);
v_i_boxed_8686_ = lean_unbox_usize(v_i_8683_);
lean_dec(v_i_8683_);
v_res_8687_ = lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00Submission_R24GenericDotBank_eagerBank_spec__0(v_as_8681_, v_sz_boxed_8685_, v_i_boxed_8686_, v_b_8684_);
lean_dec_ref(v_as_8681_);
return v_res_8687_;
}
}
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00Submission_R24GenericDotBank_eagerBank_spec__1(lean_object* v_a_8688_, lean_object* v_as_8689_, size_t v_sz_8690_, size_t v_i_8691_, lean_object* v_b_8692_){
_start:
{
uint8_t v___x_8693_; 
v___x_8693_ = lean_usize_dec_lt(v_i_8691_, v_sz_8690_);
if (v___x_8693_ == 0)
{
lean_dec_ref(v_a_8688_);
return v_b_8692_;
}
else
{
lean_object* v_a_8694_; uint32_t v___x_8695_; lean_object* v___x_8696_; lean_object* v___x_8697_; size_t v___x_8698_; size_t v___x_8699_; 
v_a_8694_ = lean_array_uget_borrowed(v_as_8689_, v_i_8691_);
lean_inc(v_a_8694_);
lean_inc_ref(v_a_8688_);
v___x_8695_ = lp_competition_Submission_R24DotProbe_eagerPrepared(v_a_8688_, v_a_8694_);
v___x_8696_ = lean_box_uint32(v___x_8695_);
v___x_8697_ = lean_array_push(v_b_8692_, v___x_8696_);
v___x_8698_ = ((size_t)1ULL);
v___x_8699_ = lean_usize_add(v_i_8691_, v___x_8698_);
v_i_8691_ = v___x_8699_;
v_b_8692_ = v___x_8697_;
goto _start;
}
}
}
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00Submission_R24GenericDotBank_eagerBank_spec__1___boxed(lean_object* v_a_8701_, lean_object* v_as_8702_, lean_object* v_sz_8703_, lean_object* v_i_8704_, lean_object* v_b_8705_){
_start:
{
size_t v_sz_boxed_8706_; size_t v_i_boxed_8707_; lean_object* v_res_8708_; 
v_sz_boxed_8706_ = lean_unbox_usize(v_sz_8703_);
lean_dec(v_sz_8703_);
v_i_boxed_8707_ = lean_unbox_usize(v_i_8704_);
lean_dec(v_i_8704_);
v_res_8708_ = lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00Submission_R24GenericDotBank_eagerBank_spec__1(v_a_8701_, v_as_8702_, v_sz_boxed_8706_, v_i_boxed_8707_, v_b_8705_);
lean_dec_ref(v_as_8702_);
return v_res_8708_;
}
}
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00Submission_R24GenericDotBank_eagerBank_spec__2(lean_object* v___x_8709_, lean_object* v_as_8710_, size_t v_sz_8711_, size_t v_i_8712_, lean_object* v_b_8713_){
_start:
{
uint8_t v___x_8714_; 
v___x_8714_ = lean_usize_dec_lt(v_i_8712_, v_sz_8711_);
if (v___x_8714_ == 0)
{
return v_b_8713_;
}
else
{
lean_object* v_a_8715_; size_t v_sz_8716_; size_t v___x_8717_; lean_object* v___x_8718_; size_t v___x_8719_; size_t v___x_8720_; 
v_a_8715_ = lean_array_uget_borrowed(v_as_8710_, v_i_8712_);
v_sz_8716_ = lean_array_size(v___x_8709_);
v___x_8717_ = ((size_t)0ULL);
lean_inc(v_a_8715_);
v___x_8718_ = lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00Submission_R24GenericDotBank_eagerBank_spec__1(v_a_8715_, v___x_8709_, v_sz_8716_, v___x_8717_, v_b_8713_);
v___x_8719_ = ((size_t)1ULL);
v___x_8720_ = lean_usize_add(v_i_8712_, v___x_8719_);
v_i_8712_ = v___x_8720_;
v_b_8713_ = v___x_8718_;
goto _start;
}
}
}
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00Submission_R24GenericDotBank_eagerBank_spec__2___boxed(lean_object* v___x_8722_, lean_object* v_as_8723_, lean_object* v_sz_8724_, lean_object* v_i_8725_, lean_object* v_b_8726_){
_start:
{
size_t v_sz_boxed_8727_; size_t v_i_boxed_8728_; lean_object* v_res_8729_; 
v_sz_boxed_8727_ = lean_unbox_usize(v_sz_8724_);
lean_dec(v_sz_8724_);
v_i_boxed_8728_ = lean_unbox_usize(v_i_8725_);
lean_dec(v_i_8725_);
v_res_8729_ = lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00Submission_R24GenericDotBank_eagerBank_spec__2(v___x_8722_, v_as_8723_, v_sz_boxed_8727_, v_i_boxed_8728_, v_b_8726_);
lean_dec_ref(v_as_8723_);
lean_dec_ref(v___x_8722_);
return v_res_8729_;
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_R24GenericDotBank_eagerBank(lean_object* v_rowsA_8730_, lean_object* v_rowsB_8731_){
_start:
{
lean_object* v___x_8732_; lean_object* v_a_8733_; size_t v_sz_8734_; size_t v___x_8735_; lean_object* v___x_8736_; lean_object* v___x_8737_; lean_object* v___x_8738_; size_t v_sz_8739_; lean_object* v___x_8740_; lean_object* v___x_8741_; lean_object* v___x_8742_; size_t v_sz_8743_; lean_object* v___x_8744_; 
v___x_8732_ = lean_array_get_size(v_rowsA_8730_);
v_a_8733_ = lean_mk_empty_array_with_capacity(v___x_8732_);
v_sz_8734_ = lean_array_size(v_rowsA_8730_);
v___x_8735_ = ((size_t)0ULL);
v___x_8736_ = lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00Submission_R24GenericDotBank_eagerBank_spec__0(v_rowsA_8730_, v_sz_8734_, v___x_8735_, v_a_8733_);
v___x_8737_ = lean_array_get_size(v_rowsB_8731_);
v___x_8738_ = lean_mk_empty_array_with_capacity(v___x_8737_);
v_sz_8739_ = lean_array_size(v_rowsB_8731_);
v___x_8740_ = lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00Submission_R24GenericDotBank_eagerBank_spec__0(v_rowsB_8731_, v_sz_8739_, v___x_8735_, v___x_8738_);
v___x_8741_ = lean_nat_mul(v___x_8732_, v___x_8737_);
v___x_8742_ = lean_mk_empty_array_with_capacity(v___x_8741_);
lean_dec(v___x_8741_);
v_sz_8743_ = lean_array_size(v___x_8736_);
v___x_8744_ = lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00Submission_R24GenericDotBank_eagerBank_spec__2(v___x_8740_, v___x_8736_, v_sz_8743_, v___x_8735_, v___x_8742_);
lean_dec_ref(v___x_8736_);
lean_dec_ref(v___x_8740_);
return v___x_8744_;
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_R24GenericDotBank_eagerBank___boxed(lean_object* v_rowsA_8745_, lean_object* v_rowsB_8746_){
_start:
{
lean_object* v_res_8747_; 
v_res_8747_ = lp_competition_Submission_R24GenericDotBank_eagerBank(v_rowsA_8745_, v_rowsB_8746_);
lean_dec_ref(v_rowsB_8746_);
lean_dec_ref(v_rowsA_8745_);
return v_res_8747_;
}
}
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00Submission_R24GenericDotBank_lazyBank_spec__0(lean_object* v_as_8748_, size_t v_sz_8749_, size_t v_i_8750_, lean_object* v_b_8751_){
_start:
{
uint8_t v___x_8752_; 
v___x_8752_ = lean_usize_dec_lt(v_i_8750_, v_sz_8749_);
if (v___x_8752_ == 0)
{
return v_b_8751_;
}
else
{
lean_object* v_a_8753_; lean_object* v___x_8754_; lean_object* v___x_8755_; size_t v___x_8756_; size_t v___x_8757_; 
v_a_8753_ = lean_array_uget_borrowed(v_as_8748_, v_i_8750_);
lean_inc(v_a_8753_);
v___x_8754_ = lp_competition_Submission_R24PortableF64_prepare(v_a_8753_);
v___x_8755_ = lean_array_push(v_b_8751_, v___x_8754_);
v___x_8756_ = ((size_t)1ULL);
v___x_8757_ = lean_usize_add(v_i_8750_, v___x_8756_);
v_i_8750_ = v___x_8757_;
v_b_8751_ = v___x_8755_;
goto _start;
}
}
}
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00Submission_R24GenericDotBank_lazyBank_spec__0___boxed(lean_object* v_as_8759_, lean_object* v_sz_8760_, lean_object* v_i_8761_, lean_object* v_b_8762_){
_start:
{
size_t v_sz_boxed_8763_; size_t v_i_boxed_8764_; lean_object* v_res_8765_; 
v_sz_boxed_8763_ = lean_unbox_usize(v_sz_8760_);
lean_dec(v_sz_8760_);
v_i_boxed_8764_ = lean_unbox_usize(v_i_8761_);
lean_dec(v_i_8761_);
v_res_8765_ = lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00Submission_R24GenericDotBank_lazyBank_spec__0(v_as_8759_, v_sz_boxed_8763_, v_i_boxed_8764_, v_b_8762_);
lean_dec_ref(v_as_8759_);
return v_res_8765_;
}
}
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00Submission_R24GenericDotBank_lazyBank_spec__1(lean_object* v_a_8766_, lean_object* v_as_8767_, size_t v_sz_8768_, size_t v_i_8769_, lean_object* v_b_8770_){
_start:
{
uint8_t v___x_8771_; 
v___x_8771_ = lean_usize_dec_lt(v_i_8769_, v_sz_8768_);
if (v___x_8771_ == 0)
{
lean_dec_ref(v_a_8766_);
return v_b_8770_;
}
else
{
lean_object* v_a_8772_; uint32_t v___x_8773_; lean_object* v___x_8774_; lean_object* v___x_8775_; size_t v___x_8776_; size_t v___x_8777_; 
v_a_8772_ = lean_array_uget_borrowed(v_as_8767_, v_i_8769_);
lean_inc(v_a_8772_);
lean_inc_ref(v_a_8766_);
v___x_8773_ = lp_competition_Submission_R24DotProbe_lazyPrepared(v_a_8766_, v_a_8772_);
v___x_8774_ = lean_box_uint32(v___x_8773_);
v___x_8775_ = lean_array_push(v_b_8770_, v___x_8774_);
v___x_8776_ = ((size_t)1ULL);
v___x_8777_ = lean_usize_add(v_i_8769_, v___x_8776_);
v_i_8769_ = v___x_8777_;
v_b_8770_ = v___x_8775_;
goto _start;
}
}
}
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00Submission_R24GenericDotBank_lazyBank_spec__1___boxed(lean_object* v_a_8779_, lean_object* v_as_8780_, lean_object* v_sz_8781_, lean_object* v_i_8782_, lean_object* v_b_8783_){
_start:
{
size_t v_sz_boxed_8784_; size_t v_i_boxed_8785_; lean_object* v_res_8786_; 
v_sz_boxed_8784_ = lean_unbox_usize(v_sz_8781_);
lean_dec(v_sz_8781_);
v_i_boxed_8785_ = lean_unbox_usize(v_i_8782_);
lean_dec(v_i_8782_);
v_res_8786_ = lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00Submission_R24GenericDotBank_lazyBank_spec__1(v_a_8779_, v_as_8780_, v_sz_boxed_8784_, v_i_boxed_8785_, v_b_8783_);
lean_dec_ref(v_as_8780_);
return v_res_8786_;
}
}
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00Submission_R24GenericDotBank_lazyBank_spec__2(lean_object* v___x_8787_, lean_object* v_as_8788_, size_t v_sz_8789_, size_t v_i_8790_, lean_object* v_b_8791_){
_start:
{
uint8_t v___x_8792_; 
v___x_8792_ = lean_usize_dec_lt(v_i_8790_, v_sz_8789_);
if (v___x_8792_ == 0)
{
return v_b_8791_;
}
else
{
lean_object* v_a_8793_; size_t v_sz_8794_; size_t v___x_8795_; lean_object* v___x_8796_; size_t v___x_8797_; size_t v___x_8798_; 
v_a_8793_ = lean_array_uget_borrowed(v_as_8788_, v_i_8790_);
v_sz_8794_ = lean_array_size(v___x_8787_);
v___x_8795_ = ((size_t)0ULL);
lean_inc(v_a_8793_);
v___x_8796_ = lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00Submission_R24GenericDotBank_lazyBank_spec__1(v_a_8793_, v___x_8787_, v_sz_8794_, v___x_8795_, v_b_8791_);
v___x_8797_ = ((size_t)1ULL);
v___x_8798_ = lean_usize_add(v_i_8790_, v___x_8797_);
v_i_8790_ = v___x_8798_;
v_b_8791_ = v___x_8796_;
goto _start;
}
}
}
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00Submission_R24GenericDotBank_lazyBank_spec__2___boxed(lean_object* v___x_8800_, lean_object* v_as_8801_, lean_object* v_sz_8802_, lean_object* v_i_8803_, lean_object* v_b_8804_){
_start:
{
size_t v_sz_boxed_8805_; size_t v_i_boxed_8806_; lean_object* v_res_8807_; 
v_sz_boxed_8805_ = lean_unbox_usize(v_sz_8802_);
lean_dec(v_sz_8802_);
v_i_boxed_8806_ = lean_unbox_usize(v_i_8803_);
lean_dec(v_i_8803_);
v_res_8807_ = lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00Submission_R24GenericDotBank_lazyBank_spec__2(v___x_8800_, v_as_8801_, v_sz_boxed_8805_, v_i_boxed_8806_, v_b_8804_);
lean_dec_ref(v_as_8801_);
lean_dec_ref(v___x_8800_);
return v_res_8807_;
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_R24GenericDotBank_lazyBank(lean_object* v_rowsA_8808_, lean_object* v_rowsB_8809_){
_start:
{
lean_object* v___x_8810_; lean_object* v_a_8811_; size_t v_sz_8812_; size_t v___x_8813_; lean_object* v___x_8814_; lean_object* v___x_8815_; lean_object* v___x_8816_; size_t v_sz_8817_; lean_object* v___x_8818_; lean_object* v___x_8819_; lean_object* v___x_8820_; size_t v_sz_8821_; lean_object* v___x_8822_; 
v___x_8810_ = lean_array_get_size(v_rowsA_8808_);
v_a_8811_ = lean_mk_empty_array_with_capacity(v___x_8810_);
v_sz_8812_ = lean_array_size(v_rowsA_8808_);
v___x_8813_ = ((size_t)0ULL);
v___x_8814_ = lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00Submission_R24GenericDotBank_lazyBank_spec__0(v_rowsA_8808_, v_sz_8812_, v___x_8813_, v_a_8811_);
v___x_8815_ = lean_array_get_size(v_rowsB_8809_);
v___x_8816_ = lean_mk_empty_array_with_capacity(v___x_8815_);
v_sz_8817_ = lean_array_size(v_rowsB_8809_);
v___x_8818_ = lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00Submission_R24GenericDotBank_lazyBank_spec__0(v_rowsB_8809_, v_sz_8817_, v___x_8813_, v___x_8816_);
v___x_8819_ = lean_nat_mul(v___x_8810_, v___x_8815_);
v___x_8820_ = lean_mk_empty_array_with_capacity(v___x_8819_);
lean_dec(v___x_8819_);
v_sz_8821_ = lean_array_size(v___x_8814_);
v___x_8822_ = lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00Submission_R24GenericDotBank_lazyBank_spec__2(v___x_8818_, v___x_8814_, v_sz_8821_, v___x_8813_, v___x_8820_);
lean_dec_ref(v___x_8814_);
lean_dec_ref(v___x_8818_);
return v___x_8822_;
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_R24GenericDotBank_lazyBank___boxed(lean_object* v_rowsA_8823_, lean_object* v_rowsB_8824_){
_start:
{
lean_object* v_res_8825_; 
v_res_8825_ = lp_competition_Submission_R24GenericDotBank_lazyBank(v_rowsA_8823_, v_rowsB_8824_);
lean_dec_ref(v_rowsB_8824_);
lean_dec_ref(v_rowsA_8823_);
return v_res_8825_;
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
lp_competition_Submission_R24ExactDotCost_prepareOperand___closed__2___boxed__const__1 = _init_lp_competition_Submission_R24ExactDotCost_prepareOperand___closed__2___boxed__const__1();
lean_mark_persistent(lp_competition_Submission_R24ExactDotCost_prepareOperand___closed__2___boxed__const__1);
lp_competition_Submission_R24ExactDotCost_prepareOperand___closed__3___boxed__const__1 = _init_lp_competition_Submission_R24ExactDotCost_prepareOperand___closed__3___boxed__const__1();
lean_mark_persistent(lp_competition_Submission_R24ExactDotCost_prepareOperand___closed__3___boxed__const__1);
return lean_io_result_mk_ok(lean_box(0));
}
#ifdef __cplusplus
}
#endif
