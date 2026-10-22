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
uint32_t lean_float32_to_bits(float);
lean_object* lean_uint32_to_nat(uint32_t);
lean_object* lean_nat_mul(lean_object*, lean_object*);
uint8_t lean_nat_dec_eq(lean_object*, lean_object*);
size_t lean_array_size(lean_object*);
uint8_t lean_usize_dec_lt(size_t, size_t);
lean_object* lean_array_uget(lean_object*, size_t);
lean_object* lean_array_uset(lean_object*, size_t, lean_object*);
float lean_float32_of_bits(uint32_t);
size_t lean_usize_add(size_t, size_t);
lean_object* lean_nat_add(lean_object*, lean_object*);
uint8_t lean_nat_dec_lt(lean_object*, lean_object*);
lean_object* lean_array_fget_borrowed(lean_object*, lean_object*);
lean_object* l_Array_ofFn___redArg(lean_object*, lean_object*);
lean_object* lean_nat_div(lean_object*, lean_object*);
float lean_float32_mul(float, float);
float lean_float32_add(float, float);
lean_object* lean_array_get_size(lean_object*);
extern lean_object* l_System_Platform_numBits;
lean_object* lean_nat_pow(lean_object*, lean_object*);
lean_object* lean_nat_sub(lean_object*, lean_object*);
size_t lean_usize_of_nat(lean_object*);
lean_object* lean_array_uget_borrowed(lean_object*, size_t);
lean_object* lean_nat_mod(lean_object*, lean_object*);
uint32_t lean_float32_to_bits(float);
uint32_t lean_uint32_shift_right(uint32_t, uint32_t);
uint32_t lean_uint32_land(uint32_t, uint32_t);
uint8_t lean_uint32_dec_eq(uint32_t, uint32_t);
lean_object* l_BitVec_ofNat(lean_object*, lean_object*);
uint32_t lean_uint32_of_nat(lean_object*);
uint32_t lean_uint32_lor(uint32_t, uint32_t);
float lean_uint32_to_float32(uint32_t);
uint32_t lean_uint32_shift_left(uint32_t, uint32_t);
uint32_t lean_uint32_sub(uint32_t, uint32_t);
uint8_t lean_uint32_dec_le(uint32_t, uint32_t);
lean_object* lean_uint32_to_nat(uint32_t);
uint8_t lean_uint32_dec_lt(uint32_t, uint32_t);
uint8_t lean_uint64_dec_eq(uint64_t, uint64_t);
uint32_t lean_uint64_to_uint32(uint64_t);
uint64_t lean_uint64_sub(uint64_t, uint64_t);
uint8_t lean_uint64_dec_lt(uint64_t, uint64_t);
uint64_t lean_uint64_add(uint64_t, uint64_t);
uint64_t lean_uint64_shift_right(uint64_t, uint64_t);
uint64_t lean_uint64_shift_left(uint64_t, uint64_t);
uint64_t lean_uint64_land(uint64_t, uint64_t);
uint8_t lean_uint64_dec_le(uint64_t, uint64_t);
uint64_t lean_uint32_to_uint64(uint32_t);
uint64_t lean_uint64_lor(uint64_t, uint64_t);
lean_object* lp_floatlib_FloatLib_Floats_Formats_BinaryInterchange_Model_AddBackend_word___at___00FloatLib_Floats_Formats_BinaryInterchange_Configured_Plan_softwareAdd32Certified_spec__1(lean_object*, lean_object*);
uint64_t lean_uint64_mul(uint64_t, uint64_t);
lean_object* lp_floatlib_FloatLib_Floats_Formats_BinaryInterchange_Model_MulBackend_word___at___00FloatLib_Floats_Formats_BinaryInterchange_Configured_Plan_softwareMul32Certified_spec__1(lean_object*, lean_object*);
uint32_t lean_uint32_add(uint32_t, uint32_t);
lean_object* lp_competition_Competition_bmmDecodeC(lean_object*, lean_object*, lean_object*);
uint8_t lean_float32_isfinite(float);
lean_object* lean_mk_empty_array_with_capacity(lean_object*);
uint8_t lean_nat_dec_le(lean_object*, lean_object*);
uint8_t lean_usize_dec_eq(size_t, size_t);
lean_object* l_Array_append___redArg(lean_object*, lean_object*);
lean_object* lp_floatlib_FloatLib_Floats_Formats_BinaryInterchange_Model_MulBackend_word(lean_object*, lean_object*, lean_object*);
lean_object* lean_nat_shiftr(lean_object*, lean_object*);
LEAN_EXPORT uint8_t lp_competition_R5W02_finiteBits(uint32_t);
LEAN_EXPORT lean_object* lp_competition_R5W02_finiteBits___boxed(lean_object*);
LEAN_EXPORT uint32_t lp_competition_R2W01b_magnitude(uint32_t);
LEAN_EXPORT lean_object* lp_competition_R2W01b_magnitude___boxed(lean_object*);
LEAN_EXPORT uint8_t lp_competition_R2W01b_fastOK(uint32_t);
LEAN_EXPORT lean_object* lp_competition_R2W01b_fastOK___boxed(lean_object*);
LEAN_EXPORT uint32_t lp_competition_R2W01b_tableIndex(uint32_t);
LEAN_EXPORT lean_object* lp_competition_R2W01b_tableIndex___boxed(lean_object*);
LEAN_EXPORT uint32_t lp_competition_R2W01b_mantissa(uint32_t);
LEAN_EXPORT lean_object* lp_competition_R2W01b_mantissa___boxed(lean_object*);
LEAN_EXPORT uint32_t lp_competition_R2W01b_scaleBits(uint32_t);
LEAN_EXPORT lean_object* lp_competition_R2W01b_scaleBits___boxed(lean_object*);
LEAN_EXPORT float lp_competition_R2W01b_scaleTable___lam__0(lean_object*);
LEAN_EXPORT lean_object* lp_competition_R2W01b_scaleTable___lam__0___boxed(lean_object*);
static const lean_closure_object lp_competition_R2W01b_scaleTable___closed__0_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_closure_object) + sizeof(void*)*0, .m_other = 0, .m_tag = 245}, .m_fun = (void*)lp_competition_R2W01b_scaleTable___lam__0___boxed, .m_arity = 1, .m_num_fixed = 0, .m_objs = {} };
static const lean_object* lp_competition_R2W01b_scaleTable___closed__0 = (const lean_object*)&lp_competition_R2W01b_scaleTable___closed__0_value;
static lean_once_cell_t lp_competition_R2W01b_scaleTable___closed__1_once = LEAN_ONCE_CELL_INITIALIZER;
static lean_object* lp_competition_R2W01b_scaleTable___closed__1;
LEAN_EXPORT lean_object* lp_competition_R2W01b_scaleTable;
LEAN_EXPORT float lp_competition_R2W01b_scaleAt(uint32_t);
LEAN_EXPORT lean_object* lp_competition_R2W01b_scaleAt___boxed(lean_object*);
LEAN_EXPORT float lp_competition_R2W01b_tableProduct(uint32_t);
LEAN_EXPORT lean_object* lp_competition_R2W01b_tableProduct___boxed(lean_object*);
LEAN_EXPORT float lp_competition_R2W01b_convert(uint32_t);
LEAN_EXPORT lean_object* lp_competition_R2W01b_convert___boxed(lean_object*);
LEAN_EXPORT lean_object* lp_competition_R2W01c_nativeModel(float);
LEAN_EXPORT lean_object* lp_competition_R2W01c_nativeModel___boxed(lean_object*);
LEAN_EXPORT lean_object* lp_competition_R2W01c_rawModel(uint32_t);
LEAN_EXPORT lean_object* lp_competition_R2W01c_rawModel___boxed(lean_object*);
LEAN_EXPORT lean_object* lp_competition_R2W01c_raw32(uint32_t);
LEAN_EXPORT lean_object* lp_competition_R2W01c_raw32___boxed(lean_object*);
LEAN_EXPORT uint8_t lp_competition_R2W01c_wordSign(uint32_t);
LEAN_EXPORT lean_object* lp_competition_R2W01c_wordSign___boxed(lean_object*);
LEAN_EXPORT lean_object* lp_competition_R2W01c_wordExp(uint32_t);
LEAN_EXPORT lean_object* lp_competition_R2W01c_wordExp___boxed(lean_object*);
LEAN_EXPORT lean_object* lp_competition_R2W01c_wordFrac(uint32_t);
LEAN_EXPORT lean_object* lp_competition_R2W01c_wordFrac___boxed(lean_object*);
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
LEAN_EXPORT uint32_t lp_competition_Submission_LowScale_roundLow(uint8_t, uint64_t, uint64_t);
LEAN_EXPORT lean_object* lp_competition_Submission_LowScale_roundLow___boxed(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT uint32_t lp_competition_Submission_LowScale_roundSelect(uint8_t, uint64_t, uint64_t);
LEAN_EXPORT lean_object* lp_competition_Submission_LowScale_roundSelect___boxed(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT uint32_t lp_competition_Submission_LowScale_core(uint32_t, uint32_t);
LEAN_EXPORT lean_object* lp_competition_Submission_LowScale_core___boxed(lean_object*, lean_object*);
LEAN_EXPORT uint32_t lp_competition_Submission_LowScale_mul(uint32_t, uint32_t);
LEAN_EXPORT lean_object* lp_competition_Submission_LowScale_mul___boxed(lean_object*, lean_object*);
LEAN_EXPORT uint32_t lp_competition_Submission_add(uint32_t, uint32_t);
LEAN_EXPORT lean_object* lp_competition_Submission_add___boxed(lean_object*, lean_object*);
LEAN_EXPORT uint32_t lp_competition_Submission_nativeMul(uint32_t, uint32_t);
LEAN_EXPORT lean_object* lp_competition_Submission_nativeMul___boxed(lean_object*, lean_object*);
LEAN_EXPORT uint32_t lp_competition_Submission_mul(uint32_t, uint32_t);
LEAN_EXPORT lean_object* lp_competition_Submission_mul___boxed(lean_object*, lean_object*);
LEAN_EXPORT uint32_t lp_competition___private_Init_Data_Array_Basic_0__Array_foldlMUnsafe_fold___at___00Submission_referenceSum_spec__0(lean_object*, size_t, size_t, uint32_t);
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_foldlMUnsafe_fold___at___00Submission_referenceSum_spec__0___boxed(lean_object*, lean_object*, lean_object*, lean_object*);
static lean_once_cell_t lp_competition_Submission_referenceSum___redArg___closed__0_once = LEAN_ONCE_CELL_INITIALIZER;
static lean_object* lp_competition_Submission_referenceSum___redArg___closed__0;
static lean_once_cell_t lp_competition_Submission_referenceSum___redArg___closed__1_once = LEAN_ONCE_CELL_INITIALIZER;
static uint32_t lp_competition_Submission_referenceSum___redArg___closed__1;
LEAN_EXPORT uint32_t lp_competition_Submission_referenceSum___redArg(lean_object*);
LEAN_EXPORT lean_object* lp_competition_Submission_referenceSum___redArg___boxed(lean_object*);
LEAN_EXPORT uint32_t lp_competition_Submission_referenceSum(lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_Submission_referenceSum___boxed(lean_object*, lean_object*);
LEAN_EXPORT uint32_t lp_competition_Fin_foldl_loop___at___00Submission_referenceBmm_spec__0(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, uint32_t, lean_object*);
LEAN_EXPORT lean_object* lp_competition_Fin_foldl_loop___at___00Submission_referenceBmm_spec__0___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT uint32_t lp_competition_Submission_referenceBmm___lam__0(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_Submission_referenceBmm___lam__0___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_Submission_referenceBmm(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_Submission_referenceBmm___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT float lp_competition_Submission_NativeFinal_sumLoop(lean_object*, lean_object*, lean_object*, float);
LEAN_EXPORT lean_object* lp_competition_Submission_NativeFinal_sumLoop___boxed(lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT float lp_competition_Submission_NativeFinal_dotLoop(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, float);
LEAN_EXPORT lean_object* lp_competition_Submission_NativeFinal_dotLoop___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT uint32_t lp_competition_Fin_foldl_loop___at___00Submission_NativeFinal_dot_spec__0(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, uint32_t, lean_object*);
LEAN_EXPORT lean_object* lp_competition_Fin_foldl_loop___at___00Submission_NativeFinal_dot_spec__0___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
static lean_once_cell_t lp_competition_Submission_NativeFinal_dot___closed__0_once = LEAN_ONCE_CELL_INITIALIZER;
static float lp_competition_Submission_NativeFinal_dot___closed__0;
LEAN_EXPORT uint32_t lp_competition_Submission_NativeFinal_dot(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_Submission_NativeFinal_dot___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT uint32_t lp_competition_Submission_originalSum(lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_Submission_originalSum___boxed(lean_object*, lean_object*);
LEAN_EXPORT float lp_competition_Submission_Packed10_zero32;
static lean_once_cell_t lp_competition_Submission_Packed10_zero10___closed__0_once = LEAN_ONCE_CELL_INITIALIZER;
static lean_object* lp_competition_Submission_Packed10_zero10___closed__0;
LEAN_EXPORT lean_object* lp_competition_Submission_Packed10_zero10;
LEAN_EXPORT float lp_competition_Submission_Packed10_lane(lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_Submission_Packed10_lane___boxed(lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_Submission_Packed10_packet(lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_Submission_Packed10_update(lean_object*, float, lean_object*);
LEAN_EXPORT lean_object* lp_competition_Submission_Packed10_update___boxed(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_Submission_Packed10_groups(lean_object*);
LEAN_EXPORT lean_object* lp_competition_Submission_Packed10_groups___boxed(lean_object*);
LEAN_EXPORT float lp_competition_Submission_Packed10_packB___lam__0(lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_Submission_Packed10_packB___lam__0___boxed(lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_Submission_Packed10_packB___lam__1(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_Submission_Packed10_packB___lam__1___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_Submission_Packed10_packB___lam__2(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_Submission_Packed10_packB___lam__3(lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_Submission_Packed10_packB(lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_Submission_Packed10_dot10(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, float, float, float, float, float, float, float, float, float, float);
LEAN_EXPORT lean_object* lp_competition_Submission_Packed10_dot10___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT uint32_t lp_competition_Submission_Packed10_finish(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, float);
LEAN_EXPORT lean_object* lp_competition_Submission_Packed10_finish___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_Submission_Packed10Index_loop___redArg(size_t, size_t, lean_object*, lean_object*, size_t, float, float, float, float, float, float, float, float, float, float);
LEAN_EXPORT lean_object* lp_competition_Submission_Packed10Index_loop___redArg___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_Submission_Packed10Index_loop(lean_object*, size_t, size_t, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, size_t, float, float, float, float, float, float, float, float, float, float);
LEAN_EXPORT lean_object* lp_competition_Submission_Packed10Index_loop___boxed(lean_object**);
LEAN_EXPORT lean_object* lp_competition_Submission_Packed10Index_within___redArg(lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_Submission_Packed10Index_within___redArg___boxed(lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_Submission_Packed10Index_within(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_Submission_Packed10Index_within___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
static lean_once_cell_t lp_competition_Submission_Packed10Index_runDot___closed__0_once = LEAN_ONCE_CELL_INITIALIZER;
static lean_object* lp_competition_Submission_Packed10Index_runDot___closed__0;
LEAN_EXPORT lean_object* lp_competition_Submission_Packed10Index_runDot(lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_Submission_Packed10Index_runDot___boxed(lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_Submission_Packed10_tileResults___lam__0(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_Submission_Packed10_tileResults___lam__0___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_Submission_Packed10_tileResults___lam__1(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_Submission_Packed10_tileResults___lam__1___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_Submission_Packed10_tileResults___lam__2(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_Submission_Packed10_tileResults(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_Submission_Packed10_inlineDecodeC(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_Submission_Packed10_inlineDecodeC___boxed(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT uint32_t lp_competition_Submission_Packed10_outputFromTiles___redArg(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_Submission_Packed10_outputFromTiles___redArg___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT uint32_t lp_competition_Submission_Packed10_outputFromTiles(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_Submission_Packed10_outputFromTiles___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_mapMUnsafe_map___at___00Submission_Packed10_core_spec__0(size_t, size_t, lean_object*);
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_mapMUnsafe_map___at___00Submission_Packed10_core_spec__0___boxed(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_Submission_Packed10_core(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_Submission_bmmR4(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT float lp_competition_Submission_NativeDecodeSum_decode(uint32_t);
LEAN_EXPORT lean_object* lp_competition_Submission_NativeDecodeSum_decode___boxed(lean_object*);
LEAN_EXPORT float lp_competition_Submission_NativeDecodeSum_loop(lean_object*, lean_object*, lean_object*, float);
LEAN_EXPORT lean_object* lp_competition_Submission_NativeDecodeSum_loop___boxed(lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT float lp_competition_Submission_NativeDecodeSumWord_loop___redArg(lean_object*, size_t, size_t, float);
LEAN_EXPORT lean_object* lp_competition_Submission_NativeDecodeSumWord_loop___redArg___boxed(lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT float lp_competition_Submission_NativeDecodeSumWord_loop(lean_object*, lean_object*, size_t, lean_object*, size_t, float);
LEAN_EXPORT lean_object* lp_competition_Submission_NativeDecodeSumWord_loop___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT float lp_competition_Submission_NativeDecodeSumWord_run(lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_Submission_NativeDecodeSumWord_run___boxed(lean_object*, lean_object*);
LEAN_EXPORT uint32_t lp_competition_Submission_sum(lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_Submission_sum___boxed(lean_object*, lean_object*);
LEAN_EXPORT uint32_t lp_competition_Submission_RowOutput_row___redArg___lam__0(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_Submission_RowOutput_row___redArg___lam__0___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_Submission_RowOutput_row___redArg(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_Submission_RowOutput_row___redArg___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_Submission_RowOutput_row(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_Submission_RowOutput_row___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_Submission_RowOutput_output___lam__0(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_Submission_RowOutput_output___lam__0___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_mapMUnsafe_map___at___00Submission_RowOutput_output_spec__0(size_t, size_t, lean_object*);
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_mapMUnsafe_map___at___00Submission_RowOutput_output_spec__0___boxed(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_foldlMUnsafe_fold___at___00Submission_RowOutput_output_spec__1(lean_object*, size_t, size_t, lean_object*);
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_foldlMUnsafe_fold___at___00Submission_RowOutput_output_spec__1___boxed(lean_object*, lean_object*, lean_object*, lean_object*);
static const lean_array_object lp_competition_Submission_RowOutput_output___lam__1___closed__0_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_array_object) + sizeof(void*)*0, .m_other = 0, .m_tag = 246}, .m_size = 0, .m_capacity = 0, .m_data = {}};
static const lean_object* lp_competition_Submission_RowOutput_output___lam__1___closed__0 = (const lean_object*)&lp_competition_Submission_RowOutput_output___lam__1___closed__0_value;
LEAN_EXPORT lean_object* lp_competition_Submission_RowOutput_output___lam__1(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_Submission_RowOutput_output___lam__1___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_Submission_RowOutput_output(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_Submission_RowOutput_core(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_Submission_bmmRows(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_Submission_RowStream_core___lam__0(lean_object*);
LEAN_EXPORT lean_object* lp_competition_Submission_RowStream_core___lam__0___boxed(lean_object*);
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_foldlMUnsafe_fold___at___00Submission_RowStream_core_spec__0___redArg___lam__0(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_foldlMUnsafe_fold___at___00Submission_RowStream_core_spec__0___redArg___lam__0___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_foldlMUnsafe_fold___at___00Submission_RowStream_core_spec__0___redArg(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, size_t, size_t, lean_object*);
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_foldlMUnsafe_fold___at___00Submission_RowStream_core_spec__0___redArg___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
static const lean_closure_object lp_competition_Submission_RowStream_core___closed__0_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_closure_object) + sizeof(void*)*0, .m_other = 0, .m_tag = 245}, .m_fun = (void*)lp_competition_Submission_RowStream_core___lam__0___boxed, .m_arity = 1, .m_num_fixed = 0, .m_objs = {} };
static const lean_object* lp_competition_Submission_RowStream_core___closed__0 = (const lean_object*)&lp_competition_Submission_RowStream_core___closed__0_value;
LEAN_EXPORT lean_object* lp_competition_Submission_RowStream_core(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_foldlMUnsafe_fold___at___00Submission_RowStream_core_spec__0(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, size_t, size_t, lean_object*);
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_foldlMUnsafe_fold___at___00Submission_RowStream_core_spec__0___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_Submission_bmm(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT uint8_t lp_competition_R5W02_finiteBits(uint32_t v_u_1_){
_start:
{
uint32_t v___x_2_; uint32_t v___x_3_; uint32_t v___x_4_; uint32_t v___x_5_; uint8_t v___x_6_; 
v___x_2_ = 23;
v___x_3_ = lean_uint32_shift_right(v_u_1_, v___x_2_);
v___x_4_ = 255;
v___x_5_ = lean_uint32_land(v___x_3_, v___x_4_);
v___x_6_ = lean_uint32_dec_eq(v___x_5_, v___x_4_);
if (v___x_6_ == 0)
{
uint8_t v___x_7_; 
v___x_7_ = 1;
return v___x_7_;
}
else
{
uint8_t v___x_8_; 
v___x_8_ = 0;
return v___x_8_;
}
}
}
LEAN_EXPORT lean_object* lp_competition_R5W02_finiteBits___boxed(lean_object* v_u_9_){
_start:
{
uint32_t v_u_boxed_10_; uint8_t v_res_11_; lean_object* v_r_12_; 
v_u_boxed_10_ = lean_unbox_uint32(v_u_9_);
lean_dec(v_u_9_);
v_res_11_ = lp_competition_R5W02_finiteBits(v_u_boxed_10_);
v_r_12_ = lean_box(v_res_11_);
return v_r_12_;
}
}
LEAN_EXPORT uint32_t lp_competition_R2W01b_magnitude(uint32_t v_u_13_){
_start:
{
uint32_t v___x_14_; uint32_t v___x_15_; 
v___x_14_ = 2147483647;
v___x_15_ = lean_uint32_land(v_u_13_, v___x_14_);
return v___x_15_;
}
}
LEAN_EXPORT lean_object* lp_competition_R2W01b_magnitude___boxed(lean_object* v_u_16_){
_start:
{
uint32_t v_u_boxed_17_; uint32_t v_res_18_; lean_object* v_r_19_; 
v_u_boxed_17_ = lean_unbox_uint32(v_u_16_);
lean_dec(v_u_16_);
v_res_18_ = lp_competition_R2W01b_magnitude(v_u_boxed_17_);
v_r_19_ = lean_box_uint32(v_res_18_);
return v_r_19_;
}
}
LEAN_EXPORT uint8_t lp_competition_R2W01b_fastOK(uint32_t v_u_20_){
_start:
{
uint32_t v___x_21_; uint32_t v_a_22_; uint32_t v___x_23_; uint32_t v___x_24_; uint32_t v___x_25_; uint8_t v___x_26_; 
v___x_21_ = 2147483647;
v_a_22_ = lean_uint32_land(v_u_20_, v___x_21_);
v___x_23_ = 201326591;
v___x_24_ = 1;
v___x_25_ = lean_uint32_sub(v_a_22_, v___x_24_);
v___x_26_ = lean_uint32_dec_le(v___x_23_, v___x_25_);
if (v___x_26_ == 0)
{
return v___x_26_;
}
else
{
uint32_t v___x_27_; uint8_t v___x_28_; 
v___x_27_ = 2139095040;
v___x_28_ = lean_uint32_dec_lt(v_a_22_, v___x_27_);
return v___x_28_;
}
}
}
LEAN_EXPORT lean_object* lp_competition_R2W01b_fastOK___boxed(lean_object* v_u_29_){
_start:
{
uint32_t v_u_boxed_30_; uint8_t v_res_31_; lean_object* v_r_32_; 
v_u_boxed_30_ = lean_unbox_uint32(v_u_29_);
lean_dec(v_u_29_);
v_res_31_ = lp_competition_R2W01b_fastOK(v_u_boxed_30_);
v_r_32_ = lean_box(v_res_31_);
return v_r_32_;
}
}
LEAN_EXPORT uint32_t lp_competition_R2W01b_tableIndex(uint32_t v_u_33_){
_start:
{
uint32_t v___x_34_; uint32_t v___x_35_; 
v___x_34_ = 23;
v___x_35_ = lean_uint32_shift_right(v_u_33_, v___x_34_);
return v___x_35_;
}
}
LEAN_EXPORT lean_object* lp_competition_R2W01b_tableIndex___boxed(lean_object* v_u_36_){
_start:
{
uint32_t v_u_boxed_37_; uint32_t v_res_38_; lean_object* v_r_39_; 
v_u_boxed_37_ = lean_unbox_uint32(v_u_36_);
lean_dec(v_u_36_);
v_res_38_ = lp_competition_R2W01b_tableIndex(v_u_boxed_37_);
v_r_39_ = lean_box_uint32(v_res_38_);
return v_r_39_;
}
}
LEAN_EXPORT uint32_t lp_competition_R2W01b_mantissa(uint32_t v_u_40_){
_start:
{
uint32_t v___x_41_; uint32_t v___x_42_; uint32_t v___x_43_; uint32_t v___x_44_; 
v___x_41_ = 8388607;
v___x_42_ = lean_uint32_land(v_u_40_, v___x_41_);
v___x_43_ = 8388608;
v___x_44_ = lean_uint32_lor(v___x_42_, v___x_43_);
return v___x_44_;
}
}
LEAN_EXPORT lean_object* lp_competition_R2W01b_mantissa___boxed(lean_object* v_u_45_){
_start:
{
uint32_t v_u_boxed_46_; uint32_t v_res_47_; lean_object* v_r_48_; 
v_u_boxed_46_ = lean_unbox_uint32(v_u_45_);
lean_dec(v_u_45_);
v_res_47_ = lp_competition_R2W01b_mantissa(v_u_boxed_46_);
v_r_48_ = lean_box_uint32(v_res_47_);
return v_r_48_;
}
}
LEAN_EXPORT uint32_t lp_competition_R2W01b_scaleBits(uint32_t v_j_49_){
_start:
{
uint32_t v___x_50_; uint32_t v_e_51_; uint32_t v___x_52_; uint32_t v___x_53_; uint32_t v___x_54_; uint32_t v_s_55_; uint8_t v___y_57_; uint32_t v___x_61_; uint8_t v___x_62_; 
v___x_50_ = 255;
v_e_51_ = lean_uint32_land(v_j_49_, v___x_50_);
v___x_52_ = 256;
v___x_53_ = lean_uint32_land(v_j_49_, v___x_52_);
v___x_54_ = 23;
v_s_55_ = lean_uint32_shift_left(v___x_53_, v___x_54_);
v___x_61_ = 24;
v___x_62_ = lean_uint32_dec_le(v___x_61_, v_e_51_);
if (v___x_62_ == 0)
{
v___y_57_ = v___x_62_;
goto v___jp_56_;
}
else
{
uint32_t v___x_63_; uint8_t v___x_64_; 
v___x_63_ = 254;
v___x_64_ = lean_uint32_dec_le(v_e_51_, v___x_63_);
v___y_57_ = v___x_64_;
goto v___jp_56_;
}
v___jp_56_:
{
if (v___y_57_ == 0)
{
return v_s_55_;
}
else
{
uint32_t v___x_58_; uint32_t v___x_59_; uint32_t v___x_60_; 
v___x_58_ = lean_uint32_sub(v_e_51_, v___x_54_);
v___x_59_ = lean_uint32_shift_left(v___x_58_, v___x_54_);
v___x_60_ = lean_uint32_lor(v_s_55_, v___x_59_);
return v___x_60_;
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_R2W01b_scaleBits___boxed(lean_object* v_j_65_){
_start:
{
uint32_t v_j_boxed_66_; uint32_t v_res_67_; lean_object* v_r_68_; 
v_j_boxed_66_ = lean_unbox_uint32(v_j_65_);
lean_dec(v_j_65_);
v_res_67_ = lp_competition_R2W01b_scaleBits(v_j_boxed_66_);
v_r_68_ = lean_box_uint32(v_res_67_);
return v_r_68_;
}
}
LEAN_EXPORT float lp_competition_R2W01b_scaleTable___lam__0(lean_object* v_j_69_){
_start:
{
uint32_t v___x_70_; uint32_t v___x_71_; uint32_t v_e_72_; uint32_t v___x_73_; uint32_t v___x_74_; uint32_t v___x_75_; uint32_t v_s_76_; uint8_t v___y_78_; uint32_t v___x_84_; uint8_t v___x_85_; 
v___x_70_ = lean_uint32_of_nat(v_j_69_);
v___x_71_ = 255;
v_e_72_ = lean_uint32_land(v___x_70_, v___x_71_);
v___x_73_ = 256;
v___x_74_ = lean_uint32_land(v___x_70_, v___x_73_);
v___x_75_ = 23;
v_s_76_ = lean_uint32_shift_left(v___x_74_, v___x_75_);
v___x_84_ = 24;
v___x_85_ = lean_uint32_dec_le(v___x_84_, v_e_72_);
if (v___x_85_ == 0)
{
v___y_78_ = v___x_85_;
goto v___jp_77_;
}
else
{
uint32_t v___x_86_; uint8_t v___x_87_; 
v___x_86_ = 254;
v___x_87_ = lean_uint32_dec_le(v_e_72_, v___x_86_);
v___y_78_ = v___x_87_;
goto v___jp_77_;
}
v___jp_77_:
{
if (v___y_78_ == 0)
{
float v___x_79_; 
v___x_79_ = lean_float32_of_bits(v_s_76_);
return v___x_79_;
}
else
{
uint32_t v___x_80_; uint32_t v___x_81_; uint32_t v___x_82_; float v___x_83_; 
v___x_80_ = lean_uint32_sub(v_e_72_, v___x_75_);
v___x_81_ = lean_uint32_shift_left(v___x_80_, v___x_75_);
v___x_82_ = lean_uint32_lor(v_s_76_, v___x_81_);
v___x_83_ = lean_float32_of_bits(v___x_82_);
return v___x_83_;
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_R2W01b_scaleTable___lam__0___boxed(lean_object* v_j_88_){
_start:
{
float v_res_89_; lean_object* v_r_90_; 
v_res_89_ = lp_competition_R2W01b_scaleTable___lam__0(v_j_88_);
lean_dec(v_j_88_);
v_r_90_ = lean_box_float32(v_res_89_);
return v_r_90_;
}
}
static lean_object* _init_lp_competition_R2W01b_scaleTable___closed__1(void){
_start:
{
lean_object* v___f_92_; lean_object* v___x_93_; lean_object* v___x_94_; 
v___f_92_ = ((lean_object*)(lp_competition_R2W01b_scaleTable___closed__0));
v___x_93_ = lean_unsigned_to_nat(512u);
v___x_94_ = l_Array_ofFn___redArg(v___x_93_, v___f_92_);
return v___x_94_;
}
}
static lean_object* _init_lp_competition_R2W01b_scaleTable(void){
_start:
{
lean_object* v___x_95_; 
v___x_95_ = lean_obj_once(&lp_competition_R2W01b_scaleTable___closed__1, &lp_competition_R2W01b_scaleTable___closed__1_once, _init_lp_competition_R2W01b_scaleTable___closed__1);
return v___x_95_;
}
}
LEAN_EXPORT float lp_competition_R2W01b_scaleAt(uint32_t v_u_96_){
_start:
{
lean_object* v___x_97_; uint32_t v___x_98_; uint32_t v___x_99_; lean_object* v___x_100_; lean_object* v___x_101_; float v___x_102_; 
v___x_97_ = lp_competition_R2W01b_scaleTable;
v___x_98_ = 23;
v___x_99_ = lean_uint32_shift_right(v_u_96_, v___x_98_);
v___x_100_ = lean_uint32_to_nat(v___x_99_);
v___x_101_ = lean_array_fget_borrowed(v___x_97_, v___x_100_);
lean_dec(v___x_100_);
v___x_102_ = lean_unbox_float32(v___x_101_);
return v___x_102_;
}
}
LEAN_EXPORT lean_object* lp_competition_R2W01b_scaleAt___boxed(lean_object* v_u_103_){
_start:
{
uint32_t v_u_boxed_104_; float v_res_105_; lean_object* v_r_106_; 
v_u_boxed_104_ = lean_unbox_uint32(v_u_103_);
lean_dec(v_u_103_);
v_res_105_ = lp_competition_R2W01b_scaleAt(v_u_boxed_104_);
v_r_106_ = lean_box_float32(v_res_105_);
return v_r_106_;
}
}
LEAN_EXPORT float lp_competition_R2W01b_tableProduct(uint32_t v_u_107_){
_start:
{
uint32_t v___x_108_; uint32_t v___x_109_; uint32_t v___x_110_; uint32_t v___x_111_; float v___x_112_; lean_object* v___x_113_; uint32_t v___x_114_; uint32_t v___x_115_; lean_object* v___x_116_; lean_object* v___x_117_; float v___x_118_; float v___x_119_; 
v___x_108_ = 8388607;
v___x_109_ = lean_uint32_land(v_u_107_, v___x_108_);
v___x_110_ = 8388608;
v___x_111_ = lean_uint32_lor(v___x_109_, v___x_110_);
v___x_112_ = lean_uint32_to_float32(v___x_111_);
v___x_113_ = lp_competition_R2W01b_scaleTable;
v___x_114_ = 23;
v___x_115_ = lean_uint32_shift_right(v_u_107_, v___x_114_);
v___x_116_ = lean_uint32_to_nat(v___x_115_);
v___x_117_ = lean_array_fget_borrowed(v___x_113_, v___x_116_);
lean_dec(v___x_116_);
v___x_118_ = lean_unbox_float32(v___x_117_);
v___x_119_ = lean_float32_mul(v___x_112_, v___x_118_);
return v___x_119_;
}
}
LEAN_EXPORT lean_object* lp_competition_R2W01b_tableProduct___boxed(lean_object* v_u_120_){
_start:
{
uint32_t v_u_boxed_121_; float v_res_122_; lean_object* v_r_123_; 
v_u_boxed_121_ = lean_unbox_uint32(v_u_120_);
lean_dec(v_u_120_);
v_res_122_ = lp_competition_R2W01b_tableProduct(v_u_boxed_121_);
v_r_123_ = lean_box_float32(v_res_122_);
return v_r_123_;
}
}
LEAN_EXPORT float lp_competition_R2W01b_convert(uint32_t v_u_124_){
_start:
{
uint8_t v___y_126_; uint32_t v___x_140_; uint32_t v_a_141_; uint32_t v___x_142_; uint32_t v___x_143_; uint32_t v___x_144_; uint8_t v___x_145_; 
v___x_140_ = 2147483647;
v_a_141_ = lean_uint32_land(v_u_124_, v___x_140_);
v___x_142_ = 201326591;
v___x_143_ = 1;
v___x_144_ = lean_uint32_sub(v_a_141_, v___x_143_);
v___x_145_ = lean_uint32_dec_le(v___x_142_, v___x_144_);
if (v___x_145_ == 0)
{
v___y_126_ = v___x_145_;
goto v___jp_125_;
}
else
{
uint32_t v___x_146_; uint8_t v___x_147_; 
v___x_146_ = 2139095040;
v___x_147_ = lean_uint32_dec_lt(v_a_141_, v___x_146_);
v___y_126_ = v___x_147_;
goto v___jp_125_;
}
v___jp_125_:
{
if (v___y_126_ == 0)
{
float v___x_127_; 
v___x_127_ = lean_float32_of_bits(v_u_124_);
return v___x_127_;
}
else
{
uint32_t v___x_128_; uint32_t v___x_129_; uint32_t v___x_130_; uint32_t v___x_131_; float v___x_132_; lean_object* v___x_133_; uint32_t v___x_134_; uint32_t v___x_135_; lean_object* v___x_136_; lean_object* v___x_137_; float v___x_138_; float v___x_139_; 
v___x_128_ = 8388607;
v___x_129_ = lean_uint32_land(v_u_124_, v___x_128_);
v___x_130_ = 8388608;
v___x_131_ = lean_uint32_lor(v___x_129_, v___x_130_);
v___x_132_ = lean_uint32_to_float32(v___x_131_);
v___x_133_ = lp_competition_R2W01b_scaleTable;
v___x_134_ = 23;
v___x_135_ = lean_uint32_shift_right(v_u_124_, v___x_134_);
v___x_136_ = lean_uint32_to_nat(v___x_135_);
v___x_137_ = lean_array_fget_borrowed(v___x_133_, v___x_136_);
lean_dec(v___x_136_);
v___x_138_ = lean_unbox_float32(v___x_137_);
v___x_139_ = lean_float32_mul(v___x_132_, v___x_138_);
return v___x_139_;
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_R2W01b_convert___boxed(lean_object* v_u_148_){
_start:
{
uint32_t v_u_boxed_149_; float v_res_150_; lean_object* v_r_151_; 
v_u_boxed_149_ = lean_unbox_uint32(v_u_148_);
lean_dec(v_u_148_);
v_res_150_ = lp_competition_R2W01b_convert(v_u_boxed_149_);
v_r_151_ = lean_box_float32(v_res_150_);
return v_r_151_;
}
}
LEAN_EXPORT lean_object* lp_competition_R2W01c_nativeModel(float v_x_152_){
_start:
{
uint32_t v___x_153_; lean_object* v___x_154_; 
v___x_153_ = lean_float32_to_bits(v_x_152_);
v___x_154_ = lean_uint32_to_nat(v___x_153_);
return v___x_154_;
}
}
LEAN_EXPORT lean_object* lp_competition_R2W01c_nativeModel___boxed(lean_object* v_x_155_){
_start:
{
float v_x_boxed_156_; lean_object* v_res_157_; 
v_x_boxed_156_ = lean_unbox_float32(v_x_155_);
lean_dec_ref(v_x_155_);
v_res_157_ = lp_competition_R2W01c_nativeModel(v_x_boxed_156_);
return v_res_157_;
}
}
LEAN_EXPORT lean_object* lp_competition_R2W01c_rawModel(uint32_t v_u_158_){
_start:
{
lean_object* v___x_159_; 
v___x_159_ = lean_uint32_to_nat(v_u_158_);
return v___x_159_;
}
}
LEAN_EXPORT lean_object* lp_competition_R2W01c_rawModel___boxed(lean_object* v_u_160_){
_start:
{
uint32_t v_u_boxed_161_; lean_object* v_res_162_; 
v_u_boxed_161_ = lean_unbox_uint32(v_u_160_);
lean_dec(v_u_160_);
v_res_162_ = lp_competition_R2W01c_rawModel(v_u_boxed_161_);
return v_res_162_;
}
}
LEAN_EXPORT lean_object* lp_competition_R2W01c_raw32(uint32_t v_u_163_){
_start:
{
lean_object* v___x_164_; lean_object* v___x_165_; lean_object* v___x_166_; 
v___x_164_ = lean_uint32_to_nat(v_u_163_);
v___x_165_ = lean_unsigned_to_nat(32u);
v___x_166_ = l_BitVec_ofNat(v___x_165_, v___x_164_);
lean_dec(v___x_164_);
return v___x_166_;
}
}
LEAN_EXPORT lean_object* lp_competition_R2W01c_raw32___boxed(lean_object* v_u_167_){
_start:
{
uint32_t v_u_boxed_168_; lean_object* v_res_169_; 
v_u_boxed_168_ = lean_unbox_uint32(v_u_167_);
lean_dec(v_u_167_);
v_res_169_ = lp_competition_R2W01c_raw32(v_u_boxed_168_);
return v_res_169_;
}
}
LEAN_EXPORT uint8_t lp_competition_R2W01c_wordSign(uint32_t v_u_170_){
_start:
{
lean_object* v___x_171_; lean_object* v___x_172_; uint8_t v___x_173_; 
v___x_171_ = lean_unsigned_to_nat(2147483648u);
v___x_172_ = lean_uint32_to_nat(v_u_170_);
v___x_173_ = lean_nat_dec_le(v___x_171_, v___x_172_);
lean_dec(v___x_172_);
return v___x_173_;
}
}
LEAN_EXPORT lean_object* lp_competition_R2W01c_wordSign___boxed(lean_object* v_u_174_){
_start:
{
uint32_t v_u_boxed_175_; uint8_t v_res_176_; lean_object* v_r_177_; 
v_u_boxed_175_ = lean_unbox_uint32(v_u_174_);
lean_dec(v_u_174_);
v_res_176_ = lp_competition_R2W01c_wordSign(v_u_boxed_175_);
v_r_177_ = lean_box(v_res_176_);
return v_r_177_;
}
}
LEAN_EXPORT lean_object* lp_competition_R2W01c_wordExp(uint32_t v_u_178_){
_start:
{
lean_object* v___x_179_; lean_object* v___x_180_; lean_object* v___x_181_; lean_object* v___x_182_; lean_object* v___x_183_; 
v___x_179_ = lean_uint32_to_nat(v_u_178_);
v___x_180_ = lean_unsigned_to_nat(23u);
v___x_181_ = lean_nat_shiftr(v___x_179_, v___x_180_);
lean_dec(v___x_179_);
v___x_182_ = lean_unsigned_to_nat(256u);
v___x_183_ = lean_nat_mod(v___x_181_, v___x_182_);
lean_dec(v___x_181_);
return v___x_183_;
}
}
LEAN_EXPORT lean_object* lp_competition_R2W01c_wordExp___boxed(lean_object* v_u_184_){
_start:
{
uint32_t v_u_boxed_185_; lean_object* v_res_186_; 
v_u_boxed_185_ = lean_unbox_uint32(v_u_184_);
lean_dec(v_u_184_);
v_res_186_ = lp_competition_R2W01c_wordExp(v_u_boxed_185_);
return v_res_186_;
}
}
LEAN_EXPORT lean_object* lp_competition_R2W01c_wordFrac(uint32_t v_u_187_){
_start:
{
lean_object* v___x_188_; lean_object* v___x_189_; lean_object* v___x_190_; 
v___x_188_ = lean_uint32_to_nat(v_u_187_);
v___x_189_ = lean_unsigned_to_nat(8388608u);
v___x_190_ = lean_nat_mod(v___x_188_, v___x_189_);
lean_dec(v___x_188_);
return v___x_190_;
}
}
LEAN_EXPORT lean_object* lp_competition_R2W01c_wordFrac___boxed(lean_object* v_u_191_){
_start:
{
uint32_t v_u_boxed_192_; lean_object* v_res_193_; 
v_u_boxed_192_ = lean_unbox_uint32(v_u_191_);
lean_dec(v_u_191_);
v_res_193_ = lp_competition_R2W01c_wordFrac(v_u_boxed_192_);
return v_res_193_;
}
}
LEAN_EXPORT uint64_t lp_competition_Submission_TunedAdd_sx(uint64_t v_k_194_, uint64_t v_x_195_){
_start:
{
uint64_t v___x_196_; uint64_t v___x_197_; uint8_t v___x_198_; 
v___x_196_ = lean_uint64_shift_right(v_x_195_, v_k_194_);
v___x_197_ = 0ULL;
v___x_198_ = lean_uint64_dec_eq(v___x_196_, v___x_197_);
if (v___x_198_ == 0)
{
return v___x_196_;
}
else
{
return v_x_195_;
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_TunedAdd_sx___boxed(lean_object* v_k_199_, lean_object* v_x_200_){
_start:
{
uint64_t v_k_boxed_201_; uint64_t v_x_boxed_202_; uint64_t v_res_203_; lean_object* v_r_204_; 
v_k_boxed_201_ = lean_unbox_uint64(v_k_199_);
lean_dec_ref(v_k_199_);
v_x_boxed_202_ = lean_unbox_uint64(v_x_200_);
lean_dec_ref(v_x_200_);
v_res_203_ = lp_competition_Submission_TunedAdd_sx(v_k_boxed_201_, v_x_boxed_202_);
v_r_204_ = lean_box_uint64(v_res_203_);
return v_r_204_;
}
}
LEAN_EXPORT uint64_t lp_competition_Submission_TunedAdd_sr(uint64_t v_k_205_, uint64_t v_x_206_, uint64_t v_r_207_){
_start:
{
uint64_t v___x_208_; uint64_t v___x_209_; uint8_t v___x_210_; 
v___x_208_ = lean_uint64_shift_right(v_x_206_, v_k_205_);
v___x_209_ = 0ULL;
v___x_210_ = lean_uint64_dec_eq(v___x_208_, v___x_209_);
if (v___x_210_ == 0)
{
uint64_t v___x_211_; 
v___x_211_ = lean_uint64_add(v_r_207_, v_k_205_);
return v___x_211_;
}
else
{
return v_r_207_;
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_TunedAdd_sr___boxed(lean_object* v_k_212_, lean_object* v_x_213_, lean_object* v_r_214_){
_start:
{
uint64_t v_k_boxed_215_; uint64_t v_x_boxed_216_; uint64_t v_r_boxed_217_; uint64_t v_res_218_; lean_object* v_r_219_; 
v_k_boxed_215_ = lean_unbox_uint64(v_k_212_);
lean_dec_ref(v_k_212_);
v_x_boxed_216_ = lean_unbox_uint64(v_x_213_);
lean_dec_ref(v_x_213_);
v_r_boxed_217_ = lean_unbox_uint64(v_r_214_);
lean_dec_ref(v_r_214_);
v_res_218_ = lp_competition_Submission_TunedAdd_sr(v_k_boxed_215_, v_x_boxed_216_, v_r_boxed_217_);
v_r_219_ = lean_box_uint64(v_res_218_);
return v_r_219_;
}
}
LEAN_EXPORT uint64_t lp_competition_Submission_TunedAdd_fastLog2(uint64_t v_x0_220_){
_start:
{
uint64_t v___y_222_; uint64_t v___y_223_; uint64_t v___y_230_; uint64_t v___y_231_; uint64_t v___y_232_; uint64_t v___y_233_; uint64_t v___y_239_; uint64_t v___y_240_; uint64_t v___y_246_; uint64_t v___y_247_; uint64_t v___y_248_; uint64_t v___y_249_; uint64_t v___y_255_; uint64_t v___y_256_; uint64_t v___y_262_; uint64_t v___y_263_; uint64_t v___y_264_; uint64_t v___y_265_; uint64_t v___y_271_; uint64_t v___y_272_; uint64_t v___y_278_; uint64_t v___y_279_; uint64_t v___y_280_; uint64_t v___y_281_; uint64_t v___y_287_; uint64_t v___y_288_; uint64_t v___x_293_; uint64_t v___y_295_; uint64_t v___x_299_; uint64_t v___x_300_; uint8_t v___x_301_; 
v___x_293_ = 32ULL;
v___x_299_ = lean_uint64_shift_right(v_x0_220_, v___x_293_);
v___x_300_ = 0ULL;
v___x_301_ = lean_uint64_dec_eq(v___x_299_, v___x_300_);
if (v___x_301_ == 0)
{
v___y_295_ = v___x_299_;
goto v___jp_294_;
}
else
{
v___y_295_ = v_x0_220_;
goto v___jp_294_;
}
v___jp_221_:
{
uint64_t v___x_224_; uint64_t v___x_225_; uint64_t v___x_226_; uint8_t v___x_227_; 
v___x_224_ = 1ULL;
v___x_225_ = lean_uint64_shift_right(v___y_222_, v___x_224_);
v___x_226_ = 0ULL;
v___x_227_ = lean_uint64_dec_eq(v___x_225_, v___x_226_);
if (v___x_227_ == 0)
{
uint64_t v___x_228_; 
v___x_228_ = lean_uint64_add(v___y_223_, v___x_224_);
return v___x_228_;
}
else
{
return v___y_223_;
}
}
v___jp_229_:
{
uint64_t v___x_234_; uint64_t v___x_235_; uint8_t v___x_236_; 
v___x_234_ = lean_uint64_shift_right(v___y_231_, v___y_232_);
v___x_235_ = 0ULL;
v___x_236_ = lean_uint64_dec_eq(v___x_234_, v___x_235_);
if (v___x_236_ == 0)
{
uint64_t v___x_237_; 
v___x_237_ = lean_uint64_add(v___y_230_, v___y_232_);
v___y_222_ = v___y_233_;
v___y_223_ = v___x_237_;
goto v___jp_221_;
}
else
{
v___y_222_ = v___y_233_;
v___y_223_ = v___y_230_;
goto v___jp_221_;
}
}
v___jp_238_:
{
uint64_t v___x_241_; uint64_t v___x_242_; uint64_t v___x_243_; uint8_t v___x_244_; 
v___x_241_ = 2ULL;
v___x_242_ = lean_uint64_shift_right(v___y_239_, v___x_241_);
v___x_243_ = 0ULL;
v___x_244_ = lean_uint64_dec_eq(v___x_242_, v___x_243_);
if (v___x_244_ == 0)
{
v___y_230_ = v___y_240_;
v___y_231_ = v___y_239_;
v___y_232_ = v___x_241_;
v___y_233_ = v___x_242_;
goto v___jp_229_;
}
else
{
v___y_230_ = v___y_240_;
v___y_231_ = v___y_239_;
v___y_232_ = v___x_241_;
v___y_233_ = v___y_239_;
goto v___jp_229_;
}
}
v___jp_245_:
{
uint64_t v___x_250_; uint64_t v___x_251_; uint8_t v___x_252_; 
v___x_250_ = lean_uint64_shift_right(v___y_246_, v___y_248_);
v___x_251_ = 0ULL;
v___x_252_ = lean_uint64_dec_eq(v___x_250_, v___x_251_);
if (v___x_252_ == 0)
{
uint64_t v___x_253_; 
v___x_253_ = lean_uint64_add(v___y_247_, v___y_248_);
v___y_239_ = v___y_249_;
v___y_240_ = v___x_253_;
goto v___jp_238_;
}
else
{
v___y_239_ = v___y_249_;
v___y_240_ = v___y_247_;
goto v___jp_238_;
}
}
v___jp_254_:
{
uint64_t v___x_257_; uint64_t v___x_258_; uint64_t v___x_259_; uint8_t v___x_260_; 
v___x_257_ = 4ULL;
v___x_258_ = lean_uint64_shift_right(v___y_255_, v___x_257_);
v___x_259_ = 0ULL;
v___x_260_ = lean_uint64_dec_eq(v___x_258_, v___x_259_);
if (v___x_260_ == 0)
{
v___y_246_ = v___y_255_;
v___y_247_ = v___y_256_;
v___y_248_ = v___x_257_;
v___y_249_ = v___x_258_;
goto v___jp_245_;
}
else
{
v___y_246_ = v___y_255_;
v___y_247_ = v___y_256_;
v___y_248_ = v___x_257_;
v___y_249_ = v___y_255_;
goto v___jp_245_;
}
}
v___jp_261_:
{
uint64_t v___x_266_; uint64_t v___x_267_; uint8_t v___x_268_; 
v___x_266_ = lean_uint64_shift_right(v___y_263_, v___y_262_);
v___x_267_ = 0ULL;
v___x_268_ = lean_uint64_dec_eq(v___x_266_, v___x_267_);
if (v___x_268_ == 0)
{
uint64_t v___x_269_; 
v___x_269_ = lean_uint64_add(v___y_264_, v___y_262_);
v___y_255_ = v___y_265_;
v___y_256_ = v___x_269_;
goto v___jp_254_;
}
else
{
v___y_255_ = v___y_265_;
v___y_256_ = v___y_264_;
goto v___jp_254_;
}
}
v___jp_270_:
{
uint64_t v___x_273_; uint64_t v___x_274_; uint64_t v___x_275_; uint8_t v___x_276_; 
v___x_273_ = 8ULL;
v___x_274_ = lean_uint64_shift_right(v___y_271_, v___x_273_);
v___x_275_ = 0ULL;
v___x_276_ = lean_uint64_dec_eq(v___x_274_, v___x_275_);
if (v___x_276_ == 0)
{
v___y_262_ = v___x_273_;
v___y_263_ = v___y_271_;
v___y_264_ = v___y_272_;
v___y_265_ = v___x_274_;
goto v___jp_261_;
}
else
{
v___y_262_ = v___x_273_;
v___y_263_ = v___y_271_;
v___y_264_ = v___y_272_;
v___y_265_ = v___y_271_;
goto v___jp_261_;
}
}
v___jp_277_:
{
uint64_t v___x_282_; uint64_t v___x_283_; uint8_t v___x_284_; 
v___x_282_ = lean_uint64_shift_right(v___y_279_, v___y_280_);
v___x_283_ = 0ULL;
v___x_284_ = lean_uint64_dec_eq(v___x_282_, v___x_283_);
if (v___x_284_ == 0)
{
uint64_t v___x_285_; 
v___x_285_ = lean_uint64_add(v___y_278_, v___y_280_);
v___y_271_ = v___y_281_;
v___y_272_ = v___x_285_;
goto v___jp_270_;
}
else
{
v___y_271_ = v___y_281_;
v___y_272_ = v___y_278_;
goto v___jp_270_;
}
}
v___jp_286_:
{
uint64_t v___x_289_; uint64_t v___x_290_; uint64_t v___x_291_; uint8_t v___x_292_; 
v___x_289_ = 16ULL;
v___x_290_ = lean_uint64_shift_right(v___y_287_, v___x_289_);
v___x_291_ = 0ULL;
v___x_292_ = lean_uint64_dec_eq(v___x_290_, v___x_291_);
if (v___x_292_ == 0)
{
v___y_278_ = v___y_288_;
v___y_279_ = v___y_287_;
v___y_280_ = v___x_289_;
v___y_281_ = v___x_290_;
goto v___jp_277_;
}
else
{
v___y_278_ = v___y_288_;
v___y_279_ = v___y_287_;
v___y_280_ = v___x_289_;
v___y_281_ = v___y_287_;
goto v___jp_277_;
}
}
v___jp_294_:
{
uint64_t v___x_296_; uint64_t v___x_297_; uint8_t v___x_298_; 
v___x_296_ = lean_uint64_shift_right(v_x0_220_, v___x_293_);
v___x_297_ = 0ULL;
v___x_298_ = lean_uint64_dec_eq(v___x_296_, v___x_297_);
if (v___x_298_ == 0)
{
v___y_287_ = v___y_295_;
v___y_288_ = v___x_293_;
goto v___jp_286_;
}
else
{
v___y_287_ = v___y_295_;
v___y_288_ = v___x_297_;
goto v___jp_286_;
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_TunedAdd_fastLog2___boxed(lean_object* v_x0_302_){
_start:
{
uint64_t v_x0_boxed_303_; uint64_t v_res_304_; lean_object* v_r_305_; 
v_x0_boxed_303_ = lean_unbox_uint64(v_x0_302_);
lean_dec_ref(v_x0_302_);
v_res_304_ = lp_competition_Submission_TunedAdd_fastLog2(v_x0_boxed_303_);
v_r_305_ = lean_box_uint64(v_res_304_);
return v_r_305_;
}
}
LEAN_EXPORT uint64_t lp_competition_Submission_TunedAdd_rse(uint64_t v_value_306_, uint64_t v_shift_307_){
_start:
{
uint64_t v_quotient_308_; uint64_t v___x_309_; uint64_t v___x_310_; uint64_t v___x_311_; uint64_t v_remainder_312_; uint64_t v___x_313_; uint64_t v_half_314_; uint8_t v___x_315_; 
v_quotient_308_ = lean_uint64_shift_right(v_value_306_, v_shift_307_);
v___x_309_ = 1ULL;
v___x_310_ = lean_uint64_shift_left(v___x_309_, v_shift_307_);
v___x_311_ = lean_uint64_sub(v___x_310_, v___x_309_);
v_remainder_312_ = lean_uint64_land(v_value_306_, v___x_311_);
v___x_313_ = lean_uint64_sub(v_shift_307_, v___x_309_);
v_half_314_ = lean_uint64_shift_left(v___x_309_, v___x_313_);
v___x_315_ = lean_uint64_dec_lt(v_remainder_312_, v_half_314_);
if (v___x_315_ == 0)
{
uint8_t v___x_316_; 
v___x_316_ = lean_uint64_dec_lt(v_half_314_, v_remainder_312_);
if (v___x_316_ == 0)
{
uint64_t v___x_317_; uint64_t v___x_318_; uint8_t v___x_319_; 
v___x_317_ = lean_uint64_land(v_quotient_308_, v___x_309_);
v___x_318_ = 0ULL;
v___x_319_ = lean_uint64_dec_eq(v___x_317_, v___x_318_);
if (v___x_319_ == 0)
{
uint64_t v___x_320_; 
v___x_320_ = lean_uint64_add(v_quotient_308_, v___x_309_);
return v___x_320_;
}
else
{
return v_quotient_308_;
}
}
else
{
uint64_t v___x_321_; 
v___x_321_ = lean_uint64_add(v_quotient_308_, v___x_309_);
return v___x_321_;
}
}
else
{
return v_quotient_308_;
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_TunedAdd_rse___boxed(lean_object* v_value_322_, lean_object* v_shift_323_){
_start:
{
uint64_t v_value_boxed_324_; uint64_t v_shift_boxed_325_; uint64_t v_res_326_; lean_object* v_r_327_; 
v_value_boxed_324_ = lean_unbox_uint64(v_value_322_);
lean_dec_ref(v_value_322_);
v_shift_boxed_325_ = lean_unbox_uint64(v_shift_323_);
lean_dec_ref(v_shift_323_);
v_res_326_ = lp_competition_Submission_TunedAdd_rse(v_value_boxed_324_, v_shift_boxed_325_);
v_r_327_ = lean_box_uint64(v_res_326_);
return v_r_327_;
}
}
LEAN_EXPORT uint64_t lp_competition_Submission_TunedAdd_rseAny(uint64_t v_value_328_, uint64_t v_shift_329_){
_start:
{
uint64_t v___x_330_; uint8_t v___x_331_; 
v___x_330_ = 0ULL;
v___x_331_ = lean_uint64_dec_eq(v_shift_329_, v___x_330_);
if (v___x_331_ == 0)
{
uint64_t v___x_332_; uint8_t v___x_333_; 
v___x_332_ = 64ULL;
v___x_333_ = lean_uint64_dec_lt(v_shift_329_, v___x_332_);
if (v___x_333_ == 0)
{
uint8_t v___x_334_; 
v___x_334_ = lean_uint64_dec_eq(v_shift_329_, v___x_332_);
if (v___x_334_ == 0)
{
return v___x_330_;
}
else
{
uint64_t v___x_335_; uint8_t v___x_336_; 
v___x_335_ = 9223372036854775808ULL;
v___x_336_ = lean_uint64_dec_lt(v___x_335_, v_value_328_);
if (v___x_336_ == 0)
{
return v___x_330_;
}
else
{
uint64_t v___x_337_; 
v___x_337_ = 1ULL;
return v___x_337_;
}
}
}
else
{
uint64_t v_quotient_338_; uint64_t v___x_339_; uint64_t v___x_340_; uint64_t v___x_341_; uint64_t v_remainder_342_; uint64_t v___x_343_; uint64_t v_half_344_; uint8_t v___x_345_; 
v_quotient_338_ = lean_uint64_shift_right(v_value_328_, v_shift_329_);
v___x_339_ = 1ULL;
v___x_340_ = lean_uint64_shift_left(v___x_339_, v_shift_329_);
v___x_341_ = lean_uint64_sub(v___x_340_, v___x_339_);
v_remainder_342_ = lean_uint64_land(v_value_328_, v___x_341_);
v___x_343_ = lean_uint64_sub(v_shift_329_, v___x_339_);
v_half_344_ = lean_uint64_shift_left(v___x_339_, v___x_343_);
v___x_345_ = lean_uint64_dec_lt(v_remainder_342_, v_half_344_);
if (v___x_345_ == 0)
{
uint8_t v___x_346_; 
v___x_346_ = lean_uint64_dec_lt(v_half_344_, v_remainder_342_);
if (v___x_346_ == 0)
{
uint64_t v___x_347_; uint8_t v___x_348_; 
v___x_347_ = lean_uint64_land(v_quotient_338_, v___x_339_);
v___x_348_ = lean_uint64_dec_eq(v___x_347_, v___x_330_);
if (v___x_348_ == 0)
{
uint64_t v___x_349_; 
v___x_349_ = lean_uint64_add(v_quotient_338_, v___x_339_);
return v___x_349_;
}
else
{
return v_quotient_338_;
}
}
else
{
uint64_t v___x_350_; 
v___x_350_ = lean_uint64_add(v_quotient_338_, v___x_339_);
return v___x_350_;
}
}
else
{
return v_quotient_338_;
}
}
}
else
{
return v_value_328_;
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_TunedAdd_rseAny___boxed(lean_object* v_value_351_, lean_object* v_shift_352_){
_start:
{
uint64_t v_value_boxed_353_; uint64_t v_shift_boxed_354_; uint64_t v_res_355_; lean_object* v_r_356_; 
v_value_boxed_353_ = lean_unbox_uint64(v_value_351_);
lean_dec_ref(v_value_351_);
v_shift_boxed_354_ = lean_unbox_uint64(v_shift_352_);
lean_dec_ref(v_shift_352_);
v_res_355_ = lp_competition_Submission_TunedAdd_rseAny(v_value_boxed_353_, v_shift_boxed_354_);
v_r_356_ = lean_box_uint64(v_res_355_);
return v_r_356_;
}
}
LEAN_EXPORT uint32_t lp_competition_Submission_TunedAdd_mkW(uint8_t v_sign_357_, uint32_t v_e_358_, uint32_t v_f_359_){
_start:
{
uint32_t v___y_361_; 
if (v_sign_357_ == 0)
{
uint32_t v___x_370_; 
v___x_370_ = 0;
v___y_361_ = v___x_370_;
goto v___jp_360_;
}
else
{
uint32_t v___x_371_; 
v___x_371_ = 2147483648;
v___y_361_ = v___x_371_;
goto v___jp_360_;
}
v___jp_360_:
{
uint32_t v___x_362_; uint32_t v___x_363_; uint32_t v___x_364_; uint32_t v___x_365_; uint32_t v___x_366_; uint32_t v___x_367_; uint32_t v___x_368_; uint32_t v___x_369_; 
v___x_362_ = 255;
v___x_363_ = lean_uint32_land(v_e_358_, v___x_362_);
v___x_364_ = 23;
v___x_365_ = lean_uint32_shift_left(v___x_363_, v___x_364_);
v___x_366_ = lean_uint32_lor(v___y_361_, v___x_365_);
v___x_367_ = 8388607;
v___x_368_ = lean_uint32_land(v_f_359_, v___x_367_);
v___x_369_ = lean_uint32_lor(v___x_366_, v___x_368_);
return v___x_369_;
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_TunedAdd_mkW___boxed(lean_object* v_sign_372_, lean_object* v_e_373_, lean_object* v_f_374_){
_start:
{
uint8_t v_sign_boxed_375_; uint32_t v_e_boxed_376_; uint32_t v_f_boxed_377_; uint32_t v_res_378_; lean_object* v_r_379_; 
v_sign_boxed_375_ = lean_unbox(v_sign_372_);
v_e_boxed_376_ = lean_unbox_uint32(v_e_373_);
lean_dec(v_e_373_);
v_f_boxed_377_ = lean_unbox_uint32(v_f_374_);
lean_dec(v_f_374_);
v_res_378_ = lp_competition_Submission_TunedAdd_mkW(v_sign_boxed_375_, v_e_boxed_376_, v_f_boxed_377_);
v_r_379_ = lean_box_uint32(v_res_378_);
return v_r_379_;
}
}
static uint32_t _init_lp_competition_Submission_TunedAdd_fracW___closed__0(void){
_start:
{
uint64_t v___x_380_; uint32_t v___x_381_; 
v___x_380_ = 0ULL;
v___x_381_ = lean_uint64_to_uint32(v___x_380_);
return v___x_381_;
}
}
LEAN_EXPORT uint32_t lp_competition_Submission_TunedAdd_fracW(uint64_t v_n_382_){
_start:
{
uint64_t v___x_383_; uint8_t v___x_384_; 
v___x_383_ = 8388608ULL;
v___x_384_ = lean_uint64_dec_lt(v_n_382_, v___x_383_);
if (v___x_384_ == 0)
{
uint64_t v___x_385_; uint32_t v___x_386_; 
v___x_385_ = lean_uint64_sub(v_n_382_, v___x_383_);
v___x_386_ = lean_uint64_to_uint32(v___x_385_);
return v___x_386_;
}
else
{
uint32_t v___x_387_; 
v___x_387_ = lean_uint32_once(&lp_competition_Submission_TunedAdd_fracW___closed__0, &lp_competition_Submission_TunedAdd_fracW___closed__0_once, _init_lp_competition_Submission_TunedAdd_fracW___closed__0);
return v___x_387_;
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_TunedAdd_fracW___boxed(lean_object* v_n_388_){
_start:
{
uint64_t v_n_boxed_389_; uint32_t v_res_390_; lean_object* v_r_391_; 
v_n_boxed_389_ = lean_unbox_uint64(v_n_388_);
lean_dec_ref(v_n_388_);
v_res_390_ = lp_competition_Submission_TunedAdd_fracW(v_n_boxed_389_);
v_r_391_ = lean_box_uint32(v_res_390_);
return v_r_391_;
}
}
LEAN_EXPORT uint32_t lp_competition_Submission_TunedAdd_roundP(uint8_t v_sign_392_, uint64_t v_product_393_, uint64_t v_scale_394_){
_start:
{
uint32_t v___y_396_; uint32_t v___y_400_; uint32_t v___y_401_; uint32_t v___y_406_; uint32_t v___y_407_; uint32_t v___y_408_; uint32_t v___y_418_; uint32_t v___y_419_; uint64_t v___x_422_; uint64_t v___y_424_; uint64_t v___y_436_; uint64_t v___y_437_; uint64_t v___y_447_; uint8_t v___y_448_; uint64_t v___y_449_; uint64_t v___y_456_; uint64_t v___y_457_; uint64_t v___y_463_; uint64_t v___y_518_; uint64_t v___y_519_; uint64_t v___y_525_; uint64_t v___y_526_; uint64_t v___y_527_; uint64_t v___y_528_; uint64_t v___y_533_; uint64_t v___y_534_; uint64_t v___y_539_; uint64_t v___y_540_; uint64_t v___y_541_; uint64_t v___y_542_; uint64_t v___y_547_; uint64_t v___y_548_; uint64_t v___y_553_; uint64_t v___y_554_; uint64_t v___y_555_; uint64_t v___y_556_; uint64_t v___y_561_; uint64_t v___y_562_; uint64_t v___y_567_; uint64_t v___y_568_; uint64_t v___y_569_; uint64_t v___y_570_; uint64_t v___y_575_; uint64_t v___y_576_; uint8_t v___x_580_; 
v___x_422_ = 0ULL;
v___x_580_ = lean_uint64_dec_eq(v_product_393_, v___x_422_);
if (v___x_580_ == 0)
{
uint64_t v___x_581_; uint64_t v___y_583_; uint64_t v___x_586_; uint8_t v___x_587_; 
v___x_581_ = 32ULL;
v___x_586_ = lean_uint64_shift_right(v_product_393_, v___x_581_);
v___x_587_ = lean_uint64_dec_eq(v___x_586_, v___x_422_);
if (v___x_587_ == 0)
{
v___y_583_ = v___x_586_;
goto v___jp_582_;
}
else
{
v___y_583_ = v_product_393_;
goto v___jp_582_;
}
v___jp_582_:
{
uint64_t v___x_584_; uint8_t v___x_585_; 
v___x_584_ = lean_uint64_shift_right(v_product_393_, v___x_581_);
v___x_585_ = lean_uint64_dec_eq(v___x_584_, v___x_422_);
if (v___x_585_ == 0)
{
v___y_575_ = v___y_583_;
v___y_576_ = v___x_581_;
goto v___jp_574_;
}
else
{
v___y_575_ = v___y_583_;
v___y_576_ = v___x_422_;
goto v___jp_574_;
}
}
}
else
{
if (v_sign_392_ == 0)
{
uint32_t v___x_588_; 
v___x_588_ = 0;
return v___x_588_;
}
else
{
uint32_t v___x_589_; 
v___x_589_ = 2147483648;
return v___x_589_;
}
}
v___jp_395_:
{
uint32_t v___x_397_; uint32_t v___x_398_; 
v___x_397_ = 8388608;
v___x_398_ = lean_uint32_lor(v___y_396_, v___x_397_);
return v___x_398_;
}
v___jp_399_:
{
uint32_t v___x_402_; uint32_t v___x_403_; uint32_t v___x_404_; 
v___x_402_ = 8388607;
v___x_403_ = lean_uint32_land(v___y_400_, v___x_402_);
v___x_404_ = lean_uint32_lor(v___y_401_, v___x_403_);
return v___x_404_;
}
v___jp_405_:
{
uint32_t v___x_409_; uint32_t v___x_410_; uint32_t v___x_411_; uint32_t v___x_412_; uint32_t v___x_413_; uint32_t v___x_414_; uint32_t v___x_415_; uint32_t v___x_416_; 
v___x_409_ = 255;
v___x_410_ = lean_uint32_land(v___y_406_, v___x_409_);
v___x_411_ = 23;
v___x_412_ = lean_uint32_shift_left(v___x_410_, v___x_411_);
v___x_413_ = lean_uint32_lor(v___y_408_, v___x_412_);
v___x_414_ = 8388607;
v___x_415_ = lean_uint32_land(v___y_407_, v___x_414_);
v___x_416_ = lean_uint32_lor(v___x_413_, v___x_415_);
return v___x_416_;
}
v___jp_417_:
{
if (v_sign_392_ == 0)
{
uint32_t v___x_420_; 
v___x_420_ = 0;
v___y_406_ = v___y_418_;
v___y_407_ = v___y_419_;
v___y_408_ = v___x_420_;
goto v___jp_405_;
}
else
{
uint32_t v___x_421_; 
v___x_421_ = 2147483648;
v___y_406_ = v___y_418_;
v___y_407_ = v___y_419_;
v___y_408_ = v___x_421_;
goto v___jp_405_;
}
}
v___jp_423_:
{
uint8_t v___x_425_; 
v___x_425_ = lean_uint64_dec_eq(v___y_424_, v___x_422_);
if (v___x_425_ == 0)
{
uint64_t v___x_426_; uint8_t v___x_427_; 
v___x_426_ = 8388608ULL;
v___x_427_ = lean_uint64_dec_eq(v___y_424_, v___x_426_);
if (v___x_427_ == 0)
{
uint32_t v___x_428_; 
v___x_428_ = lean_uint64_to_uint32(v___y_424_);
if (v_sign_392_ == 0)
{
uint32_t v___x_429_; 
v___x_429_ = 0;
v___y_400_ = v___x_428_;
v___y_401_ = v___x_429_;
goto v___jp_399_;
}
else
{
uint32_t v___x_430_; 
v___x_430_ = 2147483648;
v___y_400_ = v___x_428_;
v___y_401_ = v___x_430_;
goto v___jp_399_;
}
}
else
{
if (v_sign_392_ == 0)
{
uint32_t v___x_431_; 
v___x_431_ = 0;
v___y_396_ = v___x_431_;
goto v___jp_395_;
}
else
{
uint32_t v___x_432_; 
v___x_432_ = 2147483648;
v___y_396_ = v___x_432_;
goto v___jp_395_;
}
}
}
else
{
if (v_sign_392_ == 0)
{
uint32_t v___x_433_; 
v___x_433_ = 0;
return v___x_433_;
}
else
{
uint32_t v___x_434_; 
v___x_434_ = 2147483648;
return v___x_434_;
}
}
}
v___jp_435_:
{
uint64_t v___x_438_; uint64_t v_encodedExponent_439_; uint32_t v___x_440_; uint64_t v___x_441_; uint8_t v___x_442_; 
v___x_438_ = 171ULL;
v_encodedExponent_439_ = lean_uint64_sub(v___y_436_, v___x_438_);
v___x_440_ = lean_uint64_to_uint32(v_encodedExponent_439_);
v___x_441_ = 8388608ULL;
v___x_442_ = lean_uint64_dec_lt(v___y_437_, v___x_441_);
if (v___x_442_ == 0)
{
uint64_t v___x_443_; uint32_t v___x_444_; 
v___x_443_ = lean_uint64_sub(v___y_437_, v___x_441_);
v___x_444_ = lean_uint64_to_uint32(v___x_443_);
v___y_418_ = v___x_440_;
v___y_419_ = v___x_444_;
goto v___jp_417_;
}
else
{
uint32_t v___x_445_; 
v___x_445_ = lean_uint32_once(&lp_competition_Submission_TunedAdd_fracW___closed__0, &lp_competition_Submission_TunedAdd_fracW___closed__0_once, _init_lp_competition_Submission_TunedAdd_fracW___closed__0);
v___y_418_ = v___x_440_;
v___y_419_ = v___x_445_;
goto v___jp_417_;
}
}
v___jp_446_:
{
uint64_t v___x_450_; uint8_t v___x_451_; 
v___x_450_ = 425ULL;
v___x_451_ = lean_uint64_dec_lt(v___x_450_, v___y_449_);
if (v___x_451_ == 0)
{
if (v___y_448_ == 0)
{
v___y_436_ = v___y_449_;
v___y_437_ = v___y_447_;
goto v___jp_435_;
}
else
{
uint64_t v___x_452_; 
v___x_452_ = 8388608ULL;
v___y_436_ = v___y_449_;
v___y_437_ = v___x_452_;
goto v___jp_435_;
}
}
else
{
if (v_sign_392_ == 0)
{
uint32_t v___x_453_; 
v___x_453_ = 2139095040;
return v___x_453_;
}
else
{
uint32_t v___x_454_; 
v___x_454_ = 4286578688;
return v___x_454_;
}
}
}
v___jp_455_:
{
uint64_t v___x_458_; uint8_t v_carry_459_; 
v___x_458_ = 16777216ULL;
v_carry_459_ = lean_uint64_dec_eq(v___y_457_, v___x_458_);
if (v_carry_459_ == 0)
{
v___y_447_ = v___y_457_;
v___y_448_ = v_carry_459_;
v___y_449_ = v___y_456_;
goto v___jp_446_;
}
else
{
uint64_t v___x_460_; uint64_t v___x_461_; 
v___x_460_ = 1ULL;
v___x_461_ = lean_uint64_add(v___y_456_, v___x_460_);
v___y_447_ = v___y_457_;
v___y_448_ = v_carry_459_;
v___y_449_ = v___x_461_;
goto v___jp_446_;
}
}
v___jp_462_:
{
uint64_t v_position_464_; uint64_t v___x_465_; uint8_t v___x_466_; 
v_position_464_ = lean_uint64_add(v___y_463_, v_scale_394_);
v___x_465_ = 172ULL;
v___x_466_ = lean_uint64_dec_lt(v_position_464_, v___x_465_);
if (v___x_466_ == 0)
{
uint64_t v___x_467_; uint8_t v___x_468_; 
v___x_467_ = 23ULL;
v___x_468_ = lean_uint64_dec_lt(v___y_463_, v___x_467_);
if (v___x_468_ == 0)
{
uint64_t v___x_469_; uint8_t v___x_470_; 
v___x_469_ = lean_uint64_sub(v___y_463_, v___x_467_);
v___x_470_ = lean_uint64_dec_eq(v___x_469_, v___x_422_);
if (v___x_470_ == 0)
{
uint64_t v___x_471_; uint8_t v___x_472_; 
v___x_471_ = 64ULL;
v___x_472_ = lean_uint64_dec_lt(v___x_469_, v___x_471_);
if (v___x_472_ == 0)
{
uint8_t v___x_473_; 
v___x_473_ = lean_uint64_dec_eq(v___x_469_, v___x_471_);
if (v___x_473_ == 0)
{
v___y_456_ = v_position_464_;
v___y_457_ = v___x_422_;
goto v___jp_455_;
}
else
{
uint64_t v___x_474_; uint8_t v___x_475_; 
v___x_474_ = 9223372036854775808ULL;
v___x_475_ = lean_uint64_dec_lt(v___x_474_, v_product_393_);
if (v___x_475_ == 0)
{
v___y_456_ = v_position_464_;
v___y_457_ = v___x_422_;
goto v___jp_455_;
}
else
{
uint64_t v___x_476_; 
v___x_476_ = 1ULL;
v___y_456_ = v_position_464_;
v___y_457_ = v___x_476_;
goto v___jp_455_;
}
}
}
else
{
uint64_t v_quotient_477_; uint64_t v___x_478_; uint64_t v___x_479_; uint64_t v___x_480_; uint64_t v_remainder_481_; uint64_t v___x_482_; uint64_t v_half_483_; uint8_t v___x_484_; 
v_quotient_477_ = lean_uint64_shift_right(v_product_393_, v___x_469_);
v___x_478_ = 1ULL;
v___x_479_ = lean_uint64_shift_left(v___x_478_, v___x_469_);
v___x_480_ = lean_uint64_sub(v___x_479_, v___x_478_);
v_remainder_481_ = lean_uint64_land(v_product_393_, v___x_480_);
v___x_482_ = lean_uint64_sub(v___x_469_, v___x_478_);
v_half_483_ = lean_uint64_shift_left(v___x_478_, v___x_482_);
v___x_484_ = lean_uint64_dec_lt(v_remainder_481_, v_half_483_);
if (v___x_484_ == 0)
{
uint8_t v___x_485_; 
v___x_485_ = lean_uint64_dec_lt(v_half_483_, v_remainder_481_);
if (v___x_485_ == 0)
{
uint64_t v___x_486_; uint8_t v___x_487_; 
v___x_486_ = lean_uint64_land(v_quotient_477_, v___x_478_);
v___x_487_ = lean_uint64_dec_eq(v___x_486_, v___x_422_);
if (v___x_487_ == 0)
{
uint64_t v___x_488_; 
v___x_488_ = lean_uint64_add(v_quotient_477_, v___x_478_);
v___y_456_ = v_position_464_;
v___y_457_ = v___x_488_;
goto v___jp_455_;
}
else
{
v___y_456_ = v_position_464_;
v___y_457_ = v_quotient_477_;
goto v___jp_455_;
}
}
else
{
uint64_t v___x_489_; 
v___x_489_ = lean_uint64_add(v_quotient_477_, v___x_478_);
v___y_456_ = v_position_464_;
v___y_457_ = v___x_489_;
goto v___jp_455_;
}
}
else
{
v___y_456_ = v_position_464_;
v___y_457_ = v_quotient_477_;
goto v___jp_455_;
}
}
}
else
{
v___y_456_ = v_position_464_;
v___y_457_ = v_product_393_;
goto v___jp_455_;
}
}
else
{
uint64_t v___x_490_; uint64_t v___x_491_; 
v___x_490_ = lean_uint64_sub(v___x_467_, v___y_463_);
v___x_491_ = lean_uint64_shift_left(v_product_393_, v___x_490_);
v___y_456_ = v_position_464_;
v___y_457_ = v___x_491_;
goto v___jp_455_;
}
}
else
{
uint64_t v___x_492_; uint8_t v___x_493_; 
v___x_492_ = 149ULL;
v___x_493_ = lean_uint64_dec_lt(v_scale_394_, v___x_492_);
if (v___x_493_ == 0)
{
uint64_t v___x_494_; uint64_t v___x_495_; 
v___x_494_ = lean_uint64_sub(v_scale_394_, v___x_492_);
v___x_495_ = lean_uint64_shift_left(v_product_393_, v___x_494_);
v___y_424_ = v___x_495_;
goto v___jp_423_;
}
else
{
uint64_t v___x_496_; uint8_t v___x_497_; 
v___x_496_ = lean_uint64_sub(v___x_492_, v_scale_394_);
v___x_497_ = lean_uint64_dec_eq(v___x_496_, v___x_422_);
if (v___x_497_ == 0)
{
uint64_t v___x_498_; uint8_t v___x_499_; 
v___x_498_ = 64ULL;
v___x_499_ = lean_uint64_dec_lt(v___x_496_, v___x_498_);
if (v___x_499_ == 0)
{
uint8_t v___x_500_; 
v___x_500_ = lean_uint64_dec_eq(v___x_496_, v___x_498_);
if (v___x_500_ == 0)
{
v___y_424_ = v___x_422_;
goto v___jp_423_;
}
else
{
uint64_t v___x_501_; uint8_t v___x_502_; 
v___x_501_ = 9223372036854775808ULL;
v___x_502_ = lean_uint64_dec_lt(v___x_501_, v_product_393_);
if (v___x_502_ == 0)
{
v___y_424_ = v___x_422_;
goto v___jp_423_;
}
else
{
uint64_t v___x_503_; 
v___x_503_ = 1ULL;
v___y_424_ = v___x_503_;
goto v___jp_423_;
}
}
}
else
{
uint64_t v_quotient_504_; uint64_t v___x_505_; uint64_t v___x_506_; uint64_t v___x_507_; uint64_t v_remainder_508_; uint64_t v___x_509_; uint64_t v_half_510_; uint8_t v___x_511_; 
v_quotient_504_ = lean_uint64_shift_right(v_product_393_, v___x_496_);
v___x_505_ = 1ULL;
v___x_506_ = lean_uint64_shift_left(v___x_505_, v___x_496_);
v___x_507_ = lean_uint64_sub(v___x_506_, v___x_505_);
v_remainder_508_ = lean_uint64_land(v_product_393_, v___x_507_);
v___x_509_ = lean_uint64_sub(v___x_496_, v___x_505_);
v_half_510_ = lean_uint64_shift_left(v___x_505_, v___x_509_);
v___x_511_ = lean_uint64_dec_lt(v_remainder_508_, v_half_510_);
if (v___x_511_ == 0)
{
uint8_t v___x_512_; 
v___x_512_ = lean_uint64_dec_lt(v_half_510_, v_remainder_508_);
if (v___x_512_ == 0)
{
uint64_t v___x_513_; uint8_t v___x_514_; 
v___x_513_ = lean_uint64_land(v_quotient_504_, v___x_505_);
v___x_514_ = lean_uint64_dec_eq(v___x_513_, v___x_422_);
if (v___x_514_ == 0)
{
uint64_t v___x_515_; 
v___x_515_ = lean_uint64_add(v_quotient_504_, v___x_505_);
v___y_424_ = v___x_515_;
goto v___jp_423_;
}
else
{
v___y_424_ = v_quotient_504_;
goto v___jp_423_;
}
}
else
{
uint64_t v___x_516_; 
v___x_516_ = lean_uint64_add(v_quotient_504_, v___x_505_);
v___y_424_ = v___x_516_;
goto v___jp_423_;
}
}
else
{
v___y_424_ = v_quotient_504_;
goto v___jp_423_;
}
}
}
else
{
v___y_424_ = v_product_393_;
goto v___jp_423_;
}
}
}
}
v___jp_517_:
{
uint64_t v___x_520_; uint64_t v___x_521_; uint8_t v___x_522_; 
v___x_520_ = 1ULL;
v___x_521_ = lean_uint64_shift_right(v___y_518_, v___x_520_);
v___x_522_ = lean_uint64_dec_eq(v___x_521_, v___x_422_);
if (v___x_522_ == 0)
{
uint64_t v___x_523_; 
v___x_523_ = lean_uint64_add(v___y_519_, v___x_520_);
v___y_463_ = v___x_523_;
goto v___jp_462_;
}
else
{
v___y_463_ = v___y_519_;
goto v___jp_462_;
}
}
v___jp_524_:
{
uint64_t v___x_529_; uint8_t v___x_530_; 
v___x_529_ = lean_uint64_shift_right(v___y_527_, v___y_526_);
v___x_530_ = lean_uint64_dec_eq(v___x_529_, v___x_422_);
if (v___x_530_ == 0)
{
uint64_t v___x_531_; 
v___x_531_ = lean_uint64_add(v___y_525_, v___y_526_);
v___y_518_ = v___y_528_;
v___y_519_ = v___x_531_;
goto v___jp_517_;
}
else
{
v___y_518_ = v___y_528_;
v___y_519_ = v___y_525_;
goto v___jp_517_;
}
}
v___jp_532_:
{
uint64_t v___x_535_; uint64_t v___x_536_; uint8_t v___x_537_; 
v___x_535_ = 2ULL;
v___x_536_ = lean_uint64_shift_right(v___y_533_, v___x_535_);
v___x_537_ = lean_uint64_dec_eq(v___x_536_, v___x_422_);
if (v___x_537_ == 0)
{
v___y_525_ = v___y_534_;
v___y_526_ = v___x_535_;
v___y_527_ = v___y_533_;
v___y_528_ = v___x_536_;
goto v___jp_524_;
}
else
{
v___y_525_ = v___y_534_;
v___y_526_ = v___x_535_;
v___y_527_ = v___y_533_;
v___y_528_ = v___y_533_;
goto v___jp_524_;
}
}
v___jp_538_:
{
uint64_t v___x_543_; uint8_t v___x_544_; 
v___x_543_ = lean_uint64_shift_right(v___y_541_, v___y_539_);
v___x_544_ = lean_uint64_dec_eq(v___x_543_, v___x_422_);
if (v___x_544_ == 0)
{
uint64_t v___x_545_; 
v___x_545_ = lean_uint64_add(v___y_540_, v___y_539_);
v___y_533_ = v___y_542_;
v___y_534_ = v___x_545_;
goto v___jp_532_;
}
else
{
v___y_533_ = v___y_542_;
v___y_534_ = v___y_540_;
goto v___jp_532_;
}
}
v___jp_546_:
{
uint64_t v___x_549_; uint64_t v___x_550_; uint8_t v___x_551_; 
v___x_549_ = 4ULL;
v___x_550_ = lean_uint64_shift_right(v___y_547_, v___x_549_);
v___x_551_ = lean_uint64_dec_eq(v___x_550_, v___x_422_);
if (v___x_551_ == 0)
{
v___y_539_ = v___x_549_;
v___y_540_ = v___y_548_;
v___y_541_ = v___y_547_;
v___y_542_ = v___x_550_;
goto v___jp_538_;
}
else
{
v___y_539_ = v___x_549_;
v___y_540_ = v___y_548_;
v___y_541_ = v___y_547_;
v___y_542_ = v___y_547_;
goto v___jp_538_;
}
}
v___jp_552_:
{
uint64_t v___x_557_; uint8_t v___x_558_; 
v___x_557_ = lean_uint64_shift_right(v___y_554_, v___y_553_);
v___x_558_ = lean_uint64_dec_eq(v___x_557_, v___x_422_);
if (v___x_558_ == 0)
{
uint64_t v___x_559_; 
v___x_559_ = lean_uint64_add(v___y_555_, v___y_553_);
v___y_547_ = v___y_556_;
v___y_548_ = v___x_559_;
goto v___jp_546_;
}
else
{
v___y_547_ = v___y_556_;
v___y_548_ = v___y_555_;
goto v___jp_546_;
}
}
v___jp_560_:
{
uint64_t v___x_563_; uint64_t v___x_564_; uint8_t v___x_565_; 
v___x_563_ = 8ULL;
v___x_564_ = lean_uint64_shift_right(v___y_561_, v___x_563_);
v___x_565_ = lean_uint64_dec_eq(v___x_564_, v___x_422_);
if (v___x_565_ == 0)
{
v___y_553_ = v___x_563_;
v___y_554_ = v___y_561_;
v___y_555_ = v___y_562_;
v___y_556_ = v___x_564_;
goto v___jp_552_;
}
else
{
v___y_553_ = v___x_563_;
v___y_554_ = v___y_561_;
v___y_555_ = v___y_562_;
v___y_556_ = v___y_561_;
goto v___jp_552_;
}
}
v___jp_566_:
{
uint64_t v___x_571_; uint8_t v___x_572_; 
v___x_571_ = lean_uint64_shift_right(v___y_568_, v___y_569_);
v___x_572_ = lean_uint64_dec_eq(v___x_571_, v___x_422_);
if (v___x_572_ == 0)
{
uint64_t v___x_573_; 
v___x_573_ = lean_uint64_add(v___y_567_, v___y_569_);
v___y_561_ = v___y_570_;
v___y_562_ = v___x_573_;
goto v___jp_560_;
}
else
{
v___y_561_ = v___y_570_;
v___y_562_ = v___y_567_;
goto v___jp_560_;
}
}
v___jp_574_:
{
uint64_t v___x_577_; uint64_t v___x_578_; uint8_t v___x_579_; 
v___x_577_ = 16ULL;
v___x_578_ = lean_uint64_shift_right(v___y_575_, v___x_577_);
v___x_579_ = lean_uint64_dec_eq(v___x_578_, v___x_422_);
if (v___x_579_ == 0)
{
v___y_567_ = v___y_576_;
v___y_568_ = v___y_575_;
v___y_569_ = v___x_577_;
v___y_570_ = v___x_578_;
goto v___jp_566_;
}
else
{
v___y_567_ = v___y_576_;
v___y_568_ = v___y_575_;
v___y_569_ = v___x_577_;
v___y_570_ = v___y_575_;
goto v___jp_566_;
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_TunedAdd_roundP___boxed(lean_object* v_sign_590_, lean_object* v_product_591_, lean_object* v_scale_592_){
_start:
{
uint8_t v_sign_boxed_593_; uint64_t v_product_boxed_594_; uint64_t v_scale_boxed_595_; uint32_t v_res_596_; lean_object* v_r_597_; 
v_sign_boxed_593_ = lean_unbox(v_sign_590_);
v_product_boxed_594_ = lean_unbox_uint64(v_product_591_);
lean_dec_ref(v_product_591_);
v_scale_boxed_595_ = lean_unbox_uint64(v_scale_592_);
lean_dec_ref(v_scale_592_);
v_res_596_ = lp_competition_Submission_TunedAdd_roundP(v_sign_boxed_593_, v_product_boxed_594_, v_scale_boxed_595_);
v_r_597_ = lean_box_uint32(v_res_596_);
return v_r_597_;
}
}
LEAN_EXPORT uint32_t lp_competition_Submission_TunedAdd_core(uint32_t v_xBits_600_, uint32_t v_yBits_601_){
_start:
{
uint32_t v___y_603_; uint32_t v___y_607_; uint32_t v___y_611_; uint32_t v___y_612_; uint64_t v___y_617_; lean_object* v___y_618_; uint64_t v___y_619_; uint32_t v___y_634_; uint32_t v___y_635_; uint64_t v___y_640_; lean_object* v___y_641_; uint64_t v___y_642_; uint32_t v___x_656_; uint32_t v___x_657_; uint32_t v___x_658_; uint32_t v___y_660_; uint32_t v___y_661_; uint32_t v___y_662_; lean_object* v___y_670_; uint32_t v___y_671_; uint32_t v___y_672_; uint64_t v___y_677_; uint64_t v___y_678_; lean_object* v___y_679_; uint64_t v___y_680_; uint64_t v___y_690_; uint64_t v___y_691_; lean_object* v___y_692_; uint8_t v___y_693_; uint64_t v___y_694_; uint64_t v___y_702_; uint64_t v___y_703_; lean_object* v___y_704_; uint64_t v___y_705_; uint64_t v___y_711_; uint64_t v___y_712_; uint64_t v___y_713_; lean_object* v___y_714_; lean_object* v___y_715_; uint64_t v___y_716_; uint64_t v___y_780_; uint64_t v___y_781_; uint64_t v___y_782_; uint64_t v___y_783_; lean_object* v___y_784_; lean_object* v___y_785_; uint64_t v___y_786_; uint64_t v___y_792_; uint64_t v___y_793_; uint64_t v___y_794_; uint64_t v___y_795_; uint64_t v___y_796_; uint64_t v___y_797_; lean_object* v___y_798_; lean_object* v___y_799_; uint64_t v___y_800_; uint64_t v___y_805_; uint64_t v___y_806_; uint64_t v___y_807_; uint64_t v___y_808_; lean_object* v___y_809_; lean_object* v___y_810_; uint64_t v___y_811_; uint64_t v___y_816_; uint64_t v___y_817_; uint64_t v___y_818_; uint64_t v___y_819_; lean_object* v___y_820_; uint64_t v___y_821_; uint64_t v___y_822_; lean_object* v___y_823_; uint64_t v___y_824_; uint64_t v___y_829_; uint64_t v___y_830_; uint64_t v___y_831_; lean_object* v___y_832_; lean_object* v___y_833_; uint64_t v___y_834_; uint64_t v___y_835_; uint64_t v___y_840_; uint64_t v___y_841_; uint64_t v___y_842_; uint64_t v___y_843_; uint64_t v___y_844_; lean_object* v___y_845_; uint64_t v___y_846_; lean_object* v___y_847_; uint64_t v___y_848_; uint64_t v___y_853_; uint64_t v___y_854_; uint64_t v___y_855_; uint64_t v___y_856_; lean_object* v___y_857_; lean_object* v___y_858_; uint64_t v___y_859_; uint64_t v___y_864_; uint64_t v___y_865_; uint64_t v___y_866_; uint64_t v___y_867_; uint64_t v___y_868_; lean_object* v___y_869_; uint64_t v___y_870_; lean_object* v___y_871_; uint64_t v___y_872_; uint64_t v___y_877_; uint64_t v___y_878_; uint64_t v___y_879_; uint64_t v___y_880_; lean_object* v___y_881_; lean_object* v___y_882_; uint64_t v___y_883_; uint64_t v___y_888_; uint64_t v___y_889_; uint64_t v___y_890_; uint64_t v___y_891_; lean_object* v___y_892_; lean_object* v___y_893_; uint64_t v___y_894_; uint64_t v___y_899_; lean_object* v_fst_900_; lean_object* v_snd_901_; uint64_t v___y_916_; uint64_t v___y_917_; uint8_t v___y_918_; uint64_t v___y_919_; uint8_t v___y_920_; uint8_t v___y_921_; uint64_t v___y_933_; uint64_t v___y_934_; uint8_t v___y_935_; uint64_t v___y_936_; uint8_t v___y_937_; uint8_t v___y_938_; uint32_t v___y_943_; uint32_t v___y_944_; uint32_t v___y_945_; uint32_t v___y_953_; lean_object* v___y_954_; uint32_t v___y_955_; uint64_t v___y_960_; uint64_t v___y_961_; lean_object* v___y_962_; uint64_t v___y_963_; uint64_t v___y_973_; uint8_t v___y_974_; uint64_t v___y_975_; lean_object* v___y_976_; uint64_t v___y_977_; uint64_t v___y_985_; uint64_t v___y_986_; lean_object* v___y_987_; uint64_t v___y_988_; uint64_t v___y_994_; uint64_t v___y_995_; uint64_t v___y_996_; lean_object* v___y_997_; lean_object* v___y_998_; uint64_t v___y_999_; uint64_t v___y_1063_; uint64_t v___y_1064_; uint64_t v___y_1065_; uint64_t v___y_1066_; lean_object* v___y_1067_; lean_object* v___y_1068_; uint64_t v___y_1069_; uint64_t v___y_1075_; uint64_t v___y_1076_; uint64_t v___y_1077_; uint64_t v___y_1078_; uint64_t v___y_1079_; lean_object* v___y_1080_; uint64_t v___y_1081_; lean_object* v___y_1082_; uint64_t v___y_1083_; uint64_t v___y_1088_; uint64_t v___y_1089_; uint64_t v___y_1090_; lean_object* v___y_1091_; lean_object* v___y_1092_; uint64_t v___y_1093_; uint64_t v___y_1094_; uint64_t v___y_1099_; uint64_t v___y_1100_; uint64_t v___y_1101_; uint64_t v___y_1102_; uint64_t v___y_1103_; uint64_t v___y_1104_; lean_object* v___y_1105_; lean_object* v___y_1106_; uint64_t v___y_1107_; uint64_t v___y_1112_; uint64_t v___y_1113_; uint64_t v___y_1114_; uint64_t v___y_1115_; lean_object* v___y_1116_; lean_object* v___y_1117_; uint64_t v___y_1118_; uint64_t v___y_1123_; uint64_t v___y_1124_; uint64_t v___y_1125_; uint64_t v___y_1126_; uint64_t v___y_1127_; lean_object* v___y_1128_; uint64_t v___y_1129_; lean_object* v___y_1130_; uint64_t v___y_1131_; uint64_t v___y_1136_; uint64_t v___y_1137_; uint64_t v___y_1138_; uint64_t v___y_1139_; lean_object* v___y_1140_; lean_object* v___y_1141_; uint64_t v___y_1142_; uint64_t v___y_1147_; uint64_t v___y_1148_; uint64_t v___y_1149_; uint64_t v___y_1150_; uint64_t v___y_1151_; lean_object* v___y_1152_; uint64_t v___y_1153_; lean_object* v___y_1154_; uint64_t v___y_1155_; uint64_t v___y_1160_; uint64_t v___y_1161_; uint64_t v___y_1162_; uint64_t v___y_1163_; lean_object* v___y_1164_; lean_object* v___y_1165_; uint64_t v___y_1166_; uint64_t v___y_1171_; uint64_t v___y_1172_; uint64_t v___y_1173_; uint64_t v___y_1174_; lean_object* v___y_1175_; lean_object* v___y_1176_; uint64_t v___y_1177_; uint64_t v___y_1182_; lean_object* v_fst_1183_; lean_object* v_snd_1184_; uint64_t v___y_1199_; uint64_t v___y_1200_; uint8_t v___y_1201_; uint64_t v___y_1202_; uint8_t v___y_1203_; uint8_t v___y_1204_; uint64_t v___y_1216_; uint64_t v___y_1217_; uint8_t v___y_1218_; uint64_t v___y_1219_; uint8_t v___y_1220_; uint8_t v___y_1221_; uint64_t v___y_1226_; uint64_t v___y_1227_; uint64_t v___y_1228_; uint8_t v___y_1229_; uint8_t v___y_1230_; uint64_t v___y_1231_; uint32_t v_xExponent_1241_; uint32_t v___x_1242_; uint32_t v_yExponent_1243_; uint64_t v___y_1245_; uint64_t v___y_1246_; uint8_t v___y_1247_; uint8_t v___y_1248_; uint64_t v___y_1249_; uint64_t v___y_1256_; uint8_t v___y_1257_; uint8_t v___y_1258_; uint64_t v___y_1259_; uint8_t v___y_1266_; uint8_t v___y_1267_; uint64_t v___y_1268_; uint8_t v___y_1278_; uint8_t v___y_1279_; uint8_t v___y_1289_; uint32_t v___x_1296_; uint32_t v___x_1297_; uint32_t v___x_1298_; uint8_t v___x_1299_; 
v___x_656_ = 23;
v___x_657_ = lean_uint32_shift_right(v_xBits_600_, v___x_656_);
v___x_658_ = 255;
v_xExponent_1241_ = lean_uint32_land(v___x_657_, v___x_658_);
v___x_1242_ = lean_uint32_shift_right(v_yBits_601_, v___x_656_);
v_yExponent_1243_ = lean_uint32_land(v___x_1242_, v___x_658_);
v___x_1296_ = 2147483648;
v___x_1297_ = lean_uint32_land(v_xBits_600_, v___x_1296_);
v___x_1298_ = 0;
v___x_1299_ = lean_uint32_dec_eq(v___x_1297_, v___x_1298_);
if (v___x_1299_ == 0)
{
uint8_t v___x_1300_; 
v___x_1300_ = 1;
v___y_1289_ = v___x_1300_;
goto v___jp_1288_;
}
else
{
uint8_t v___x_1301_; 
v___x_1301_ = 0;
v___y_1289_ = v___x_1301_;
goto v___jp_1288_;
}
v___jp_602_:
{
uint32_t v___x_604_; uint32_t v___x_605_; 
v___x_604_ = 8388608;
v___x_605_ = lean_uint32_lor(v___y_603_, v___x_604_);
return v___x_605_;
}
v___jp_606_:
{
uint32_t v___x_608_; uint32_t v___x_609_; 
v___x_608_ = 8388608;
v___x_609_ = lean_uint32_lor(v___y_607_, v___x_608_);
return v___x_609_;
}
v___jp_610_:
{
uint32_t v___x_613_; uint32_t v___x_614_; uint32_t v___x_615_; 
v___x_613_ = 8388607;
v___x_614_ = lean_uint32_land(v___y_611_, v___x_613_);
v___x_615_ = lean_uint32_lor(v___y_612_, v___x_614_);
return v___x_615_;
}
v___jp_616_:
{
uint8_t v___x_620_; 
v___x_620_ = lean_uint64_dec_eq(v___y_619_, v___y_617_);
if (v___x_620_ == 0)
{
uint64_t v___x_621_; uint8_t v___x_622_; 
v___x_621_ = 8388608ULL;
v___x_622_ = lean_uint64_dec_eq(v___y_619_, v___x_621_);
if (v___x_622_ == 0)
{
uint32_t v___x_623_; uint8_t v___x_624_; 
v___x_623_ = lean_uint64_to_uint32(v___y_619_);
v___x_624_ = lean_unbox(v___y_618_);
lean_dec(v___y_618_);
if (v___x_624_ == 0)
{
uint32_t v___x_625_; 
v___x_625_ = 0;
v___y_611_ = v___x_623_;
v___y_612_ = v___x_625_;
goto v___jp_610_;
}
else
{
uint32_t v___x_626_; 
v___x_626_ = 2147483648;
v___y_611_ = v___x_623_;
v___y_612_ = v___x_626_;
goto v___jp_610_;
}
}
else
{
uint8_t v___x_627_; 
v___x_627_ = lean_unbox(v___y_618_);
lean_dec(v___y_618_);
if (v___x_627_ == 0)
{
uint32_t v___x_628_; 
v___x_628_ = 0;
v___y_607_ = v___x_628_;
goto v___jp_606_;
}
else
{
uint32_t v___x_629_; 
v___x_629_ = 2147483648;
v___y_607_ = v___x_629_;
goto v___jp_606_;
}
}
}
else
{
uint8_t v___x_630_; 
v___x_630_ = lean_unbox(v___y_618_);
lean_dec(v___y_618_);
if (v___x_630_ == 0)
{
uint32_t v___x_631_; 
v___x_631_ = 0;
return v___x_631_;
}
else
{
uint32_t v___x_632_; 
v___x_632_ = 2147483648;
return v___x_632_;
}
}
}
v___jp_633_:
{
uint32_t v___x_636_; uint32_t v___x_637_; uint32_t v___x_638_; 
v___x_636_ = 8388607;
v___x_637_ = lean_uint32_land(v___y_634_, v___x_636_);
v___x_638_ = lean_uint32_lor(v___y_635_, v___x_637_);
return v___x_638_;
}
v___jp_639_:
{
uint8_t v___x_643_; 
v___x_643_ = lean_uint64_dec_eq(v___y_642_, v___y_640_);
if (v___x_643_ == 0)
{
uint64_t v___x_644_; uint8_t v___x_645_; 
v___x_644_ = 8388608ULL;
v___x_645_ = lean_uint64_dec_eq(v___y_642_, v___x_644_);
if (v___x_645_ == 0)
{
uint32_t v___x_646_; uint8_t v___x_647_; 
v___x_646_ = lean_uint64_to_uint32(v___y_642_);
v___x_647_ = lean_unbox(v___y_641_);
lean_dec(v___y_641_);
if (v___x_647_ == 0)
{
uint32_t v___x_648_; 
v___x_648_ = 0;
v___y_634_ = v___x_646_;
v___y_635_ = v___x_648_;
goto v___jp_633_;
}
else
{
uint32_t v___x_649_; 
v___x_649_ = 2147483648;
v___y_634_ = v___x_646_;
v___y_635_ = v___x_649_;
goto v___jp_633_;
}
}
else
{
uint8_t v___x_650_; 
v___x_650_ = lean_unbox(v___y_641_);
lean_dec(v___y_641_);
if (v___x_650_ == 0)
{
uint32_t v___x_651_; 
v___x_651_ = 0;
v___y_603_ = v___x_651_;
goto v___jp_602_;
}
else
{
uint32_t v___x_652_; 
v___x_652_ = 2147483648;
v___y_603_ = v___x_652_;
goto v___jp_602_;
}
}
}
else
{
uint8_t v___x_653_; 
v___x_653_ = lean_unbox(v___y_641_);
lean_dec(v___y_641_);
if (v___x_653_ == 0)
{
uint32_t v___x_654_; 
v___x_654_ = 0;
return v___x_654_;
}
else
{
uint32_t v___x_655_; 
v___x_655_ = 2147483648;
return v___x_655_;
}
}
}
v___jp_659_:
{
uint32_t v___x_663_; uint32_t v___x_664_; uint32_t v___x_665_; uint32_t v___x_666_; uint32_t v___x_667_; uint32_t v___x_668_; 
v___x_663_ = lean_uint32_land(v___y_660_, v___x_658_);
v___x_664_ = lean_uint32_shift_left(v___x_663_, v___x_656_);
v___x_665_ = lean_uint32_lor(v___y_662_, v___x_664_);
v___x_666_ = 8388607;
v___x_667_ = lean_uint32_land(v___y_661_, v___x_666_);
v___x_668_ = lean_uint32_lor(v___x_665_, v___x_667_);
return v___x_668_;
}
v___jp_669_:
{
uint8_t v___x_673_; 
v___x_673_ = lean_unbox(v___y_670_);
lean_dec(v___y_670_);
if (v___x_673_ == 0)
{
uint32_t v___x_674_; 
v___x_674_ = 0;
v___y_660_ = v___y_671_;
v___y_661_ = v___y_672_;
v___y_662_ = v___x_674_;
goto v___jp_659_;
}
else
{
uint32_t v___x_675_; 
v___x_675_ = 2147483648;
v___y_660_ = v___y_671_;
v___y_661_ = v___y_672_;
v___y_662_ = v___x_675_;
goto v___jp_659_;
}
}
v___jp_676_:
{
uint64_t v___x_681_; uint64_t v_encodedExponent_682_; uint32_t v___x_683_; uint64_t v___x_684_; uint8_t v___x_685_; 
v___x_681_ = 171ULL;
v_encodedExponent_682_ = lean_uint64_sub(v___y_677_, v___x_681_);
v___x_683_ = lean_uint64_to_uint32(v_encodedExponent_682_);
v___x_684_ = 8388608ULL;
v___x_685_ = lean_uint64_dec_lt(v___y_680_, v___x_684_);
if (v___x_685_ == 0)
{
uint64_t v___x_686_; uint32_t v___x_687_; 
v___x_686_ = lean_uint64_sub(v___y_680_, v___x_684_);
v___x_687_ = lean_uint64_to_uint32(v___x_686_);
v___y_670_ = v___y_679_;
v___y_671_ = v___x_683_;
v___y_672_ = v___x_687_;
goto v___jp_669_;
}
else
{
uint32_t v___x_688_; 
v___x_688_ = lean_uint64_to_uint32(v___y_678_);
v___y_670_ = v___y_679_;
v___y_671_ = v___x_683_;
v___y_672_ = v___x_688_;
goto v___jp_669_;
}
}
v___jp_689_:
{
uint64_t v___x_695_; uint8_t v___x_696_; 
v___x_695_ = 425ULL;
v___x_696_ = lean_uint64_dec_lt(v___x_695_, v___y_694_);
if (v___x_696_ == 0)
{
if (v___y_693_ == 0)
{
v___y_677_ = v___y_694_;
v___y_678_ = v___y_691_;
v___y_679_ = v___y_692_;
v___y_680_ = v___y_690_;
goto v___jp_676_;
}
else
{
uint64_t v___x_697_; 
v___x_697_ = 8388608ULL;
v___y_677_ = v___y_694_;
v___y_678_ = v___y_691_;
v___y_679_ = v___y_692_;
v___y_680_ = v___x_697_;
goto v___jp_676_;
}
}
else
{
uint8_t v___x_698_; 
v___x_698_ = lean_unbox(v___y_692_);
lean_dec(v___y_692_);
if (v___x_698_ == 0)
{
uint32_t v___x_699_; 
v___x_699_ = 2139095040;
return v___x_699_;
}
else
{
uint32_t v___x_700_; 
v___x_700_ = 4286578688;
return v___x_700_;
}
}
}
v___jp_701_:
{
uint64_t v___x_706_; uint8_t v_carry_707_; 
v___x_706_ = 16777216ULL;
v_carry_707_ = lean_uint64_dec_eq(v___y_705_, v___x_706_);
if (v_carry_707_ == 0)
{
v___y_690_ = v___y_705_;
v___y_691_ = v___y_703_;
v___y_692_ = v___y_704_;
v___y_693_ = v_carry_707_;
v___y_694_ = v___y_702_;
goto v___jp_689_;
}
else
{
uint64_t v___x_708_; uint64_t v___x_709_; 
v___x_708_ = 1ULL;
v___x_709_ = lean_uint64_add(v___y_702_, v___x_708_);
v___y_690_ = v___y_705_;
v___y_691_ = v___y_703_;
v___y_692_ = v___y_704_;
v___y_693_ = v_carry_707_;
v___y_694_ = v___x_709_;
goto v___jp_689_;
}
}
v___jp_710_:
{
uint64_t v_position_717_; uint64_t v___x_718_; uint8_t v___x_719_; 
v_position_717_ = lean_uint64_add(v___y_716_, v___y_712_);
v___x_718_ = 172ULL;
v___x_719_ = lean_uint64_dec_lt(v_position_717_, v___x_718_);
if (v___x_719_ == 0)
{
uint64_t v___x_720_; uint8_t v___x_721_; 
v___x_720_ = 23ULL;
v___x_721_ = lean_uint64_dec_lt(v___y_716_, v___x_720_);
if (v___x_721_ == 0)
{
uint64_t v___x_722_; uint8_t v___x_723_; 
v___x_722_ = lean_uint64_sub(v___y_716_, v___x_720_);
v___x_723_ = lean_uint64_dec_eq(v___x_722_, v___y_713_);
if (v___x_723_ == 0)
{
uint64_t v___x_724_; uint8_t v___x_725_; 
v___x_724_ = 64ULL;
v___x_725_ = lean_uint64_dec_lt(v___x_722_, v___x_724_);
if (v___x_725_ == 0)
{
uint8_t v___x_726_; 
v___x_726_ = lean_uint64_dec_eq(v___x_722_, v___x_724_);
if (v___x_726_ == 0)
{
lean_dec(v___y_715_);
v___y_702_ = v_position_717_;
v___y_703_ = v___y_713_;
v___y_704_ = v___y_714_;
v___y_705_ = v___y_713_;
goto v___jp_701_;
}
else
{
uint64_t v___x_727_; uint64_t v___x_728_; uint8_t v___x_729_; 
v___x_727_ = 9223372036854775808ULL;
v___x_728_ = lean_unbox_uint64(v___y_715_);
lean_dec(v___y_715_);
v___x_729_ = lean_uint64_dec_lt(v___x_727_, v___x_728_);
if (v___x_729_ == 0)
{
v___y_702_ = v_position_717_;
v___y_703_ = v___y_713_;
v___y_704_ = v___y_714_;
v___y_705_ = v___y_713_;
goto v___jp_701_;
}
else
{
uint64_t v___x_730_; 
v___x_730_ = 1ULL;
v___y_702_ = v_position_717_;
v___y_703_ = v___y_713_;
v___y_704_ = v___y_714_;
v___y_705_ = v___x_730_;
goto v___jp_701_;
}
}
}
else
{
uint64_t v___x_731_; uint64_t v_quotient_732_; uint64_t v___x_733_; uint64_t v___x_734_; uint64_t v___x_735_; uint64_t v___x_736_; uint64_t v_remainder_737_; uint64_t v___x_738_; uint64_t v_half_739_; uint8_t v___x_740_; 
v___x_731_ = lean_unbox_uint64(v___y_715_);
v_quotient_732_ = lean_uint64_shift_right(v___x_731_, v___x_722_);
v___x_733_ = 1ULL;
v___x_734_ = lean_uint64_shift_left(v___x_733_, v___x_722_);
v___x_735_ = lean_uint64_sub(v___x_734_, v___x_733_);
v___x_736_ = lean_unbox_uint64(v___y_715_);
lean_dec(v___y_715_);
v_remainder_737_ = lean_uint64_land(v___x_736_, v___x_735_);
v___x_738_ = lean_uint64_sub(v___x_722_, v___x_733_);
v_half_739_ = lean_uint64_shift_left(v___x_733_, v___x_738_);
v___x_740_ = lean_uint64_dec_lt(v_remainder_737_, v_half_739_);
if (v___x_740_ == 0)
{
uint8_t v___x_741_; 
v___x_741_ = lean_uint64_dec_lt(v_half_739_, v_remainder_737_);
if (v___x_741_ == 0)
{
uint64_t v___x_742_; uint8_t v___x_743_; 
v___x_742_ = lean_uint64_land(v_quotient_732_, v___x_733_);
v___x_743_ = lean_uint64_dec_eq(v___x_742_, v___y_713_);
if (v___x_743_ == 0)
{
uint64_t v___x_744_; 
v___x_744_ = lean_uint64_add(v_quotient_732_, v___x_733_);
v___y_702_ = v_position_717_;
v___y_703_ = v___y_713_;
v___y_704_ = v___y_714_;
v___y_705_ = v___x_744_;
goto v___jp_701_;
}
else
{
v___y_702_ = v_position_717_;
v___y_703_ = v___y_713_;
v___y_704_ = v___y_714_;
v___y_705_ = v_quotient_732_;
goto v___jp_701_;
}
}
else
{
uint64_t v___x_745_; 
v___x_745_ = lean_uint64_add(v_quotient_732_, v___x_733_);
v___y_702_ = v_position_717_;
v___y_703_ = v___y_713_;
v___y_704_ = v___y_714_;
v___y_705_ = v___x_745_;
goto v___jp_701_;
}
}
else
{
v___y_702_ = v_position_717_;
v___y_703_ = v___y_713_;
v___y_704_ = v___y_714_;
v___y_705_ = v_quotient_732_;
goto v___jp_701_;
}
}
}
else
{
uint64_t v___x_746_; 
v___x_746_ = lean_unbox_uint64(v___y_715_);
lean_dec(v___y_715_);
v___y_702_ = v_position_717_;
v___y_703_ = v___y_713_;
v___y_704_ = v___y_714_;
v___y_705_ = v___x_746_;
goto v___jp_701_;
}
}
else
{
uint64_t v___x_747_; uint64_t v___x_748_; uint64_t v___x_749_; 
v___x_747_ = lean_uint64_sub(v___x_720_, v___y_716_);
v___x_748_ = lean_unbox_uint64(v___y_715_);
lean_dec(v___y_715_);
v___x_749_ = lean_uint64_shift_left(v___x_748_, v___x_747_);
v___y_702_ = v_position_717_;
v___y_703_ = v___y_713_;
v___y_704_ = v___y_714_;
v___y_705_ = v___x_749_;
goto v___jp_701_;
}
}
else
{
uint8_t v___x_750_; 
v___x_750_ = lean_uint64_dec_lt(v___y_712_, v___y_711_);
if (v___x_750_ == 0)
{
uint64_t v___x_751_; uint64_t v___x_752_; uint64_t v___x_753_; 
v___x_751_ = lean_uint64_sub(v___y_712_, v___y_711_);
v___x_752_ = lean_unbox_uint64(v___y_715_);
lean_dec(v___y_715_);
v___x_753_ = lean_uint64_shift_left(v___x_752_, v___x_751_);
v___y_617_ = v___y_713_;
v___y_618_ = v___y_714_;
v___y_619_ = v___x_753_;
goto v___jp_616_;
}
else
{
uint64_t v___x_754_; uint8_t v___x_755_; 
v___x_754_ = lean_uint64_sub(v___y_711_, v___y_712_);
v___x_755_ = lean_uint64_dec_eq(v___x_754_, v___y_713_);
if (v___x_755_ == 0)
{
uint64_t v___x_756_; uint8_t v___x_757_; 
v___x_756_ = 64ULL;
v___x_757_ = lean_uint64_dec_lt(v___x_754_, v___x_756_);
if (v___x_757_ == 0)
{
uint8_t v___x_758_; 
v___x_758_ = lean_uint64_dec_eq(v___x_754_, v___x_756_);
if (v___x_758_ == 0)
{
lean_dec(v___y_715_);
v___y_617_ = v___y_713_;
v___y_618_ = v___y_714_;
v___y_619_ = v___y_713_;
goto v___jp_616_;
}
else
{
uint64_t v___x_759_; uint64_t v___x_760_; uint8_t v___x_761_; 
v___x_759_ = 9223372036854775808ULL;
v___x_760_ = lean_unbox_uint64(v___y_715_);
lean_dec(v___y_715_);
v___x_761_ = lean_uint64_dec_lt(v___x_759_, v___x_760_);
if (v___x_761_ == 0)
{
v___y_617_ = v___y_713_;
v___y_618_ = v___y_714_;
v___y_619_ = v___y_713_;
goto v___jp_616_;
}
else
{
uint64_t v___x_762_; 
v___x_762_ = 1ULL;
v___y_617_ = v___y_713_;
v___y_618_ = v___y_714_;
v___y_619_ = v___x_762_;
goto v___jp_616_;
}
}
}
else
{
uint64_t v___x_763_; uint64_t v_quotient_764_; uint64_t v___x_765_; uint64_t v___x_766_; uint64_t v___x_767_; uint64_t v___x_768_; uint64_t v_remainder_769_; uint64_t v___x_770_; uint64_t v_half_771_; uint8_t v___x_772_; 
v___x_763_ = lean_unbox_uint64(v___y_715_);
v_quotient_764_ = lean_uint64_shift_right(v___x_763_, v___x_754_);
v___x_765_ = 1ULL;
v___x_766_ = lean_uint64_shift_left(v___x_765_, v___x_754_);
v___x_767_ = lean_uint64_sub(v___x_766_, v___x_765_);
v___x_768_ = lean_unbox_uint64(v___y_715_);
lean_dec(v___y_715_);
v_remainder_769_ = lean_uint64_land(v___x_768_, v___x_767_);
v___x_770_ = lean_uint64_sub(v___x_754_, v___x_765_);
v_half_771_ = lean_uint64_shift_left(v___x_765_, v___x_770_);
v___x_772_ = lean_uint64_dec_lt(v_remainder_769_, v_half_771_);
if (v___x_772_ == 0)
{
uint8_t v___x_773_; 
v___x_773_ = lean_uint64_dec_lt(v_half_771_, v_remainder_769_);
if (v___x_773_ == 0)
{
uint64_t v___x_774_; uint8_t v___x_775_; 
v___x_774_ = lean_uint64_land(v_quotient_764_, v___x_765_);
v___x_775_ = lean_uint64_dec_eq(v___x_774_, v___y_713_);
if (v___x_775_ == 0)
{
uint64_t v___x_776_; 
v___x_776_ = lean_uint64_add(v_quotient_764_, v___x_765_);
v___y_617_ = v___y_713_;
v___y_618_ = v___y_714_;
v___y_619_ = v___x_776_;
goto v___jp_616_;
}
else
{
v___y_617_ = v___y_713_;
v___y_618_ = v___y_714_;
v___y_619_ = v_quotient_764_;
goto v___jp_616_;
}
}
else
{
uint64_t v___x_777_; 
v___x_777_ = lean_uint64_add(v_quotient_764_, v___x_765_);
v___y_617_ = v___y_713_;
v___y_618_ = v___y_714_;
v___y_619_ = v___x_777_;
goto v___jp_616_;
}
}
else
{
v___y_617_ = v___y_713_;
v___y_618_ = v___y_714_;
v___y_619_ = v_quotient_764_;
goto v___jp_616_;
}
}
}
else
{
uint64_t v___x_778_; 
v___x_778_ = lean_unbox_uint64(v___y_715_);
lean_dec(v___y_715_);
v___y_617_ = v___y_713_;
v___y_618_ = v___y_714_;
v___y_619_ = v___x_778_;
goto v___jp_616_;
}
}
}
}
v___jp_779_:
{
uint64_t v___x_787_; uint64_t v___x_788_; uint8_t v___x_789_; 
v___x_787_ = 1ULL;
v___x_788_ = lean_uint64_shift_right(v___y_782_, v___x_787_);
v___x_789_ = lean_uint64_dec_eq(v___x_788_, v___y_783_);
if (v___x_789_ == 0)
{
uint64_t v___x_790_; 
v___x_790_ = lean_uint64_add(v___y_786_, v___x_787_);
v___y_711_ = v___y_781_;
v___y_712_ = v___y_780_;
v___y_713_ = v___y_783_;
v___y_714_ = v___y_784_;
v___y_715_ = v___y_785_;
v___y_716_ = v___x_790_;
goto v___jp_710_;
}
else
{
v___y_711_ = v___y_781_;
v___y_712_ = v___y_780_;
v___y_713_ = v___y_783_;
v___y_714_ = v___y_784_;
v___y_715_ = v___y_785_;
v___y_716_ = v___y_786_;
goto v___jp_710_;
}
}
v___jp_791_:
{
uint64_t v___x_801_; uint8_t v___x_802_; 
v___x_801_ = lean_uint64_shift_right(v___y_797_, v___y_794_);
v___x_802_ = lean_uint64_dec_eq(v___x_801_, v___y_795_);
if (v___x_802_ == 0)
{
uint64_t v___x_803_; 
v___x_803_ = lean_uint64_add(v___y_796_, v___y_794_);
v___y_780_ = v___y_793_;
v___y_781_ = v___y_792_;
v___y_782_ = v___y_800_;
v___y_783_ = v___y_795_;
v___y_784_ = v___y_798_;
v___y_785_ = v___y_799_;
v___y_786_ = v___x_803_;
goto v___jp_779_;
}
else
{
v___y_780_ = v___y_793_;
v___y_781_ = v___y_792_;
v___y_782_ = v___y_800_;
v___y_783_ = v___y_795_;
v___y_784_ = v___y_798_;
v___y_785_ = v___y_799_;
v___y_786_ = v___y_796_;
goto v___jp_779_;
}
}
v___jp_804_:
{
uint64_t v___x_812_; uint64_t v___x_813_; uint8_t v___x_814_; 
v___x_812_ = 2ULL;
v___x_813_ = lean_uint64_shift_right(v___y_808_, v___x_812_);
v___x_814_ = lean_uint64_dec_eq(v___x_813_, v___y_807_);
if (v___x_814_ == 0)
{
v___y_792_ = v___y_806_;
v___y_793_ = v___y_805_;
v___y_794_ = v___x_812_;
v___y_795_ = v___y_807_;
v___y_796_ = v___y_811_;
v___y_797_ = v___y_808_;
v___y_798_ = v___y_809_;
v___y_799_ = v___y_810_;
v___y_800_ = v___x_813_;
goto v___jp_791_;
}
else
{
v___y_792_ = v___y_806_;
v___y_793_ = v___y_805_;
v___y_794_ = v___x_812_;
v___y_795_ = v___y_807_;
v___y_796_ = v___y_811_;
v___y_797_ = v___y_808_;
v___y_798_ = v___y_809_;
v___y_799_ = v___y_810_;
v___y_800_ = v___y_808_;
goto v___jp_791_;
}
}
v___jp_815_:
{
uint64_t v___x_825_; uint8_t v___x_826_; 
v___x_825_ = lean_uint64_shift_right(v___y_822_, v___y_821_);
v___x_826_ = lean_uint64_dec_eq(v___x_825_, v___y_819_);
if (v___x_826_ == 0)
{
uint64_t v___x_827_; 
v___x_827_ = lean_uint64_add(v___y_818_, v___y_821_);
v___y_805_ = v___y_817_;
v___y_806_ = v___y_816_;
v___y_807_ = v___y_819_;
v___y_808_ = v___y_824_;
v___y_809_ = v___y_820_;
v___y_810_ = v___y_823_;
v___y_811_ = v___x_827_;
goto v___jp_804_;
}
else
{
v___y_805_ = v___y_817_;
v___y_806_ = v___y_816_;
v___y_807_ = v___y_819_;
v___y_808_ = v___y_824_;
v___y_809_ = v___y_820_;
v___y_810_ = v___y_823_;
v___y_811_ = v___y_818_;
goto v___jp_804_;
}
}
v___jp_828_:
{
uint64_t v___x_836_; uint64_t v___x_837_; uint8_t v___x_838_; 
v___x_836_ = 4ULL;
v___x_837_ = lean_uint64_shift_right(v___y_834_, v___x_836_);
v___x_838_ = lean_uint64_dec_eq(v___x_837_, v___y_831_);
if (v___x_838_ == 0)
{
v___y_816_ = v___y_830_;
v___y_817_ = v___y_829_;
v___y_818_ = v___y_835_;
v___y_819_ = v___y_831_;
v___y_820_ = v___y_832_;
v___y_821_ = v___x_836_;
v___y_822_ = v___y_834_;
v___y_823_ = v___y_833_;
v___y_824_ = v___x_837_;
goto v___jp_815_;
}
else
{
v___y_816_ = v___y_830_;
v___y_817_ = v___y_829_;
v___y_818_ = v___y_835_;
v___y_819_ = v___y_831_;
v___y_820_ = v___y_832_;
v___y_821_ = v___x_836_;
v___y_822_ = v___y_834_;
v___y_823_ = v___y_833_;
v___y_824_ = v___y_834_;
goto v___jp_815_;
}
}
v___jp_839_:
{
uint64_t v___x_849_; uint8_t v___x_850_; 
v___x_849_ = lean_uint64_shift_right(v___y_844_, v___y_842_);
v___x_850_ = lean_uint64_dec_eq(v___x_849_, v___y_843_);
if (v___x_850_ == 0)
{
uint64_t v___x_851_; 
v___x_851_ = lean_uint64_add(v___y_846_, v___y_842_);
v___y_829_ = v___y_841_;
v___y_830_ = v___y_840_;
v___y_831_ = v___y_843_;
v___y_832_ = v___y_845_;
v___y_833_ = v___y_847_;
v___y_834_ = v___y_848_;
v___y_835_ = v___x_851_;
goto v___jp_828_;
}
else
{
v___y_829_ = v___y_841_;
v___y_830_ = v___y_840_;
v___y_831_ = v___y_843_;
v___y_832_ = v___y_845_;
v___y_833_ = v___y_847_;
v___y_834_ = v___y_848_;
v___y_835_ = v___y_846_;
goto v___jp_828_;
}
}
v___jp_852_:
{
uint64_t v___x_860_; uint64_t v___x_861_; uint8_t v___x_862_; 
v___x_860_ = 8ULL;
v___x_861_ = lean_uint64_shift_right(v___y_856_, v___x_860_);
v___x_862_ = lean_uint64_dec_eq(v___x_861_, v___y_855_);
if (v___x_862_ == 0)
{
v___y_840_ = v___y_854_;
v___y_841_ = v___y_853_;
v___y_842_ = v___x_860_;
v___y_843_ = v___y_855_;
v___y_844_ = v___y_856_;
v___y_845_ = v___y_857_;
v___y_846_ = v___y_859_;
v___y_847_ = v___y_858_;
v___y_848_ = v___x_861_;
goto v___jp_839_;
}
else
{
v___y_840_ = v___y_854_;
v___y_841_ = v___y_853_;
v___y_842_ = v___x_860_;
v___y_843_ = v___y_855_;
v___y_844_ = v___y_856_;
v___y_845_ = v___y_857_;
v___y_846_ = v___y_859_;
v___y_847_ = v___y_858_;
v___y_848_ = v___y_856_;
goto v___jp_839_;
}
}
v___jp_863_:
{
uint64_t v___x_873_; uint8_t v___x_874_; 
v___x_873_ = lean_uint64_shift_right(v___y_866_, v___y_870_);
v___x_874_ = lean_uint64_dec_eq(v___x_873_, v___y_868_);
if (v___x_874_ == 0)
{
uint64_t v___x_875_; 
v___x_875_ = lean_uint64_add(v___y_867_, v___y_870_);
v___y_853_ = v___y_865_;
v___y_854_ = v___y_864_;
v___y_855_ = v___y_868_;
v___y_856_ = v___y_872_;
v___y_857_ = v___y_869_;
v___y_858_ = v___y_871_;
v___y_859_ = v___x_875_;
goto v___jp_852_;
}
else
{
v___y_853_ = v___y_865_;
v___y_854_ = v___y_864_;
v___y_855_ = v___y_868_;
v___y_856_ = v___y_872_;
v___y_857_ = v___y_869_;
v___y_858_ = v___y_871_;
v___y_859_ = v___y_867_;
goto v___jp_852_;
}
}
v___jp_876_:
{
uint64_t v___x_884_; uint64_t v___x_885_; uint8_t v___x_886_; 
v___x_884_ = 16ULL;
v___x_885_ = lean_uint64_shift_right(v___y_879_, v___x_884_);
v___x_886_ = lean_uint64_dec_eq(v___x_885_, v___y_880_);
if (v___x_886_ == 0)
{
v___y_864_ = v___y_878_;
v___y_865_ = v___y_877_;
v___y_866_ = v___y_879_;
v___y_867_ = v___y_883_;
v___y_868_ = v___y_880_;
v___y_869_ = v___y_881_;
v___y_870_ = v___x_884_;
v___y_871_ = v___y_882_;
v___y_872_ = v___x_885_;
goto v___jp_863_;
}
else
{
v___y_864_ = v___y_878_;
v___y_865_ = v___y_877_;
v___y_866_ = v___y_879_;
v___y_867_ = v___y_883_;
v___y_868_ = v___y_880_;
v___y_869_ = v___y_881_;
v___y_870_ = v___x_884_;
v___y_871_ = v___y_882_;
v___y_872_ = v___y_879_;
goto v___jp_863_;
}
}
v___jp_887_:
{
uint64_t v___x_895_; uint64_t v___x_896_; uint8_t v___x_897_; 
v___x_895_ = lean_unbox_uint64(v___y_893_);
v___x_896_ = lean_uint64_shift_right(v___x_895_, v___y_891_);
v___x_897_ = lean_uint64_dec_eq(v___x_896_, v___y_890_);
if (v___x_897_ == 0)
{
v___y_877_ = v___y_889_;
v___y_878_ = v___y_888_;
v___y_879_ = v___y_894_;
v___y_880_ = v___y_890_;
v___y_881_ = v___y_892_;
v___y_882_ = v___y_893_;
v___y_883_ = v___y_891_;
goto v___jp_876_;
}
else
{
v___y_877_ = v___y_889_;
v___y_878_ = v___y_888_;
v___y_879_ = v___y_894_;
v___y_880_ = v___y_890_;
v___y_881_ = v___y_892_;
v___y_882_ = v___y_893_;
v___y_883_ = v___y_890_;
goto v___jp_876_;
}
}
v___jp_898_:
{
uint64_t v___x_902_; uint64_t v___x_903_; uint8_t v___x_904_; 
v___x_902_ = 0ULL;
v___x_903_ = lean_unbox_uint64(v_snd_901_);
v___x_904_ = lean_uint64_dec_eq(v___x_903_, v___x_902_);
if (v___x_904_ == 0)
{
uint64_t v___x_905_; uint64_t v___x_906_; uint64_t v___x_907_; uint64_t v___x_908_; uint64_t v___x_909_; uint8_t v___x_910_; 
v___x_905_ = 149ULL;
v___x_906_ = lean_uint64_add(v___y_899_, v___x_905_);
v___x_907_ = 32ULL;
v___x_908_ = lean_unbox_uint64(v_snd_901_);
v___x_909_ = lean_uint64_shift_right(v___x_908_, v___x_907_);
v___x_910_ = lean_uint64_dec_eq(v___x_909_, v___x_902_);
if (v___x_910_ == 0)
{
v___y_888_ = v___x_905_;
v___y_889_ = v___x_906_;
v___y_890_ = v___x_902_;
v___y_891_ = v___x_907_;
v___y_892_ = v_fst_900_;
v___y_893_ = v_snd_901_;
v___y_894_ = v___x_909_;
goto v___jp_887_;
}
else
{
uint64_t v___x_911_; 
v___x_911_ = lean_unbox_uint64(v_snd_901_);
v___y_888_ = v___x_905_;
v___y_889_ = v___x_906_;
v___y_890_ = v___x_902_;
v___y_891_ = v___x_907_;
v___y_892_ = v_fst_900_;
v___y_893_ = v_snd_901_;
v___y_894_ = v___x_911_;
goto v___jp_887_;
}
}
else
{
uint8_t v___x_912_; 
lean_dec(v_snd_901_);
v___x_912_ = lean_unbox(v_fst_900_);
lean_dec(v_fst_900_);
if (v___x_912_ == 0)
{
uint32_t v___x_913_; 
v___x_913_ = 0;
return v___x_913_;
}
else
{
uint32_t v___x_914_; 
v___x_914_ = 2147483648;
return v___x_914_;
}
}
}
v___jp_915_:
{
uint8_t v___x_922_; 
v___x_922_ = lean_uint64_dec_eq(v___y_916_, v___y_919_);
if (v___x_922_ == 0)
{
uint8_t v___x_923_; 
v___x_923_ = lean_uint64_dec_lt(v___y_916_, v___y_919_);
if (v___x_923_ == 0)
{
uint64_t v___x_924_; lean_object* v___x_925_; lean_object* v___x_926_; 
v___x_924_ = lean_uint64_sub(v___y_916_, v___y_919_);
v___x_925_ = lean_box(v___y_918_);
v___x_926_ = lean_box_uint64(v___x_924_);
v___y_899_ = v___y_917_;
v_fst_900_ = v___x_925_;
v_snd_901_ = v___x_926_;
goto v___jp_898_;
}
else
{
uint64_t v___x_927_; lean_object* v___x_928_; lean_object* v___x_929_; 
v___x_927_ = lean_uint64_sub(v___y_919_, v___y_916_);
v___x_928_ = lean_box(v___y_920_);
v___x_929_ = lean_box_uint64(v___x_927_);
v___y_899_ = v___y_917_;
v_fst_900_ = v___x_928_;
v_snd_901_ = v___x_929_;
goto v___jp_898_;
}
}
else
{
lean_object* v___x_930_; lean_object* v___x_931_; 
v___x_930_ = lean_box(v___y_921_);
v___x_931_ = ((lean_object*)(lp_competition_Submission_TunedAdd_core___boxed__const__1));
v___y_899_ = v___y_917_;
v_fst_900_ = v___x_930_;
v_snd_901_ = v___x_931_;
goto v___jp_898_;
}
}
v___jp_932_:
{
if (v___y_938_ == 0)
{
v___y_916_ = v___y_933_;
v___y_917_ = v___y_934_;
v___y_918_ = v___y_935_;
v___y_919_ = v___y_936_;
v___y_920_ = v___y_937_;
v___y_921_ = v___y_938_;
goto v___jp_915_;
}
else
{
uint64_t v___x_939_; lean_object* v___x_940_; lean_object* v___x_941_; 
v___x_939_ = lean_uint64_add(v___y_933_, v___y_936_);
v___x_940_ = lean_box(v___y_935_);
v___x_941_ = lean_box_uint64(v___x_939_);
v___y_899_ = v___y_934_;
v_fst_900_ = v___x_940_;
v_snd_901_ = v___x_941_;
goto v___jp_898_;
}
}
v___jp_942_:
{
uint32_t v___x_946_; uint32_t v___x_947_; uint32_t v___x_948_; uint32_t v___x_949_; uint32_t v___x_950_; uint32_t v___x_951_; 
v___x_946_ = lean_uint32_land(v___y_944_, v___x_658_);
v___x_947_ = lean_uint32_shift_left(v___x_946_, v___x_656_);
v___x_948_ = lean_uint32_lor(v___y_945_, v___x_947_);
v___x_949_ = 8388607;
v___x_950_ = lean_uint32_land(v___y_943_, v___x_949_);
v___x_951_ = lean_uint32_lor(v___x_948_, v___x_950_);
return v___x_951_;
}
v___jp_952_:
{
uint8_t v___x_956_; 
v___x_956_ = lean_unbox(v___y_954_);
lean_dec(v___y_954_);
if (v___x_956_ == 0)
{
uint32_t v___x_957_; 
v___x_957_ = 0;
v___y_943_ = v___y_955_;
v___y_944_ = v___y_953_;
v___y_945_ = v___x_957_;
goto v___jp_942_;
}
else
{
uint32_t v___x_958_; 
v___x_958_ = 2147483648;
v___y_943_ = v___y_955_;
v___y_944_ = v___y_953_;
v___y_945_ = v___x_958_;
goto v___jp_942_;
}
}
v___jp_959_:
{
uint64_t v___x_964_; uint64_t v_encodedExponent_965_; uint32_t v___x_966_; uint64_t v___x_967_; uint8_t v___x_968_; 
v___x_964_ = 171ULL;
v_encodedExponent_965_ = lean_uint64_sub(v___y_961_, v___x_964_);
v___x_966_ = lean_uint64_to_uint32(v_encodedExponent_965_);
v___x_967_ = 8388608ULL;
v___x_968_ = lean_uint64_dec_lt(v___y_963_, v___x_967_);
if (v___x_968_ == 0)
{
uint64_t v___x_969_; uint32_t v___x_970_; 
v___x_969_ = lean_uint64_sub(v___y_963_, v___x_967_);
v___x_970_ = lean_uint64_to_uint32(v___x_969_);
v___y_953_ = v___x_966_;
v___y_954_ = v___y_962_;
v___y_955_ = v___x_970_;
goto v___jp_952_;
}
else
{
uint32_t v___x_971_; 
v___x_971_ = lean_uint64_to_uint32(v___y_960_);
v___y_953_ = v___x_966_;
v___y_954_ = v___y_962_;
v___y_955_ = v___x_971_;
goto v___jp_952_;
}
}
v___jp_972_:
{
uint64_t v___x_978_; uint8_t v___x_979_; 
v___x_978_ = 425ULL;
v___x_979_ = lean_uint64_dec_lt(v___x_978_, v___y_977_);
if (v___x_979_ == 0)
{
if (v___y_974_ == 0)
{
v___y_960_ = v___y_973_;
v___y_961_ = v___y_977_;
v___y_962_ = v___y_976_;
v___y_963_ = v___y_975_;
goto v___jp_959_;
}
else
{
uint64_t v___x_980_; 
v___x_980_ = 8388608ULL;
v___y_960_ = v___y_973_;
v___y_961_ = v___y_977_;
v___y_962_ = v___y_976_;
v___y_963_ = v___x_980_;
goto v___jp_959_;
}
}
else
{
uint8_t v___x_981_; 
v___x_981_ = lean_unbox(v___y_976_);
lean_dec(v___y_976_);
if (v___x_981_ == 0)
{
uint32_t v___x_982_; 
v___x_982_ = 2139095040;
return v___x_982_;
}
else
{
uint32_t v___x_983_; 
v___x_983_ = 4286578688;
return v___x_983_;
}
}
}
v___jp_984_:
{
uint64_t v___x_989_; uint8_t v_carry_990_; 
v___x_989_ = 16777216ULL;
v_carry_990_ = lean_uint64_dec_eq(v___y_988_, v___x_989_);
if (v_carry_990_ == 0)
{
v___y_973_ = v___y_985_;
v___y_974_ = v_carry_990_;
v___y_975_ = v___y_988_;
v___y_976_ = v___y_987_;
v___y_977_ = v___y_986_;
goto v___jp_972_;
}
else
{
uint64_t v___x_991_; uint64_t v___x_992_; 
v___x_991_ = 1ULL;
v___x_992_ = lean_uint64_add(v___y_986_, v___x_991_);
v___y_973_ = v___y_985_;
v___y_974_ = v_carry_990_;
v___y_975_ = v___y_988_;
v___y_976_ = v___y_987_;
v___y_977_ = v___x_992_;
goto v___jp_972_;
}
}
v___jp_993_:
{
uint64_t v_position_1000_; uint64_t v___x_1001_; uint8_t v___x_1002_; 
v_position_1000_ = lean_uint64_add(v___y_999_, v___y_994_);
v___x_1001_ = 172ULL;
v___x_1002_ = lean_uint64_dec_lt(v_position_1000_, v___x_1001_);
if (v___x_1002_ == 0)
{
uint64_t v___x_1003_; uint8_t v___x_1004_; 
v___x_1003_ = 23ULL;
v___x_1004_ = lean_uint64_dec_lt(v___y_999_, v___x_1003_);
if (v___x_1004_ == 0)
{
uint64_t v___x_1005_; uint8_t v___x_1006_; 
v___x_1005_ = lean_uint64_sub(v___y_999_, v___x_1003_);
v___x_1006_ = lean_uint64_dec_eq(v___x_1005_, v___y_995_);
if (v___x_1006_ == 0)
{
uint64_t v___x_1007_; uint8_t v___x_1008_; 
v___x_1007_ = 64ULL;
v___x_1008_ = lean_uint64_dec_lt(v___x_1005_, v___x_1007_);
if (v___x_1008_ == 0)
{
uint8_t v___x_1009_; 
v___x_1009_ = lean_uint64_dec_eq(v___x_1005_, v___x_1007_);
if (v___x_1009_ == 0)
{
lean_dec(v___y_997_);
v___y_985_ = v___y_995_;
v___y_986_ = v_position_1000_;
v___y_987_ = v___y_998_;
v___y_988_ = v___y_995_;
goto v___jp_984_;
}
else
{
uint64_t v___x_1010_; uint64_t v___x_1011_; uint8_t v___x_1012_; 
v___x_1010_ = 9223372036854775808ULL;
v___x_1011_ = lean_unbox_uint64(v___y_997_);
lean_dec(v___y_997_);
v___x_1012_ = lean_uint64_dec_lt(v___x_1010_, v___x_1011_);
if (v___x_1012_ == 0)
{
v___y_985_ = v___y_995_;
v___y_986_ = v_position_1000_;
v___y_987_ = v___y_998_;
v___y_988_ = v___y_995_;
goto v___jp_984_;
}
else
{
uint64_t v___x_1013_; 
v___x_1013_ = 1ULL;
v___y_985_ = v___y_995_;
v___y_986_ = v_position_1000_;
v___y_987_ = v___y_998_;
v___y_988_ = v___x_1013_;
goto v___jp_984_;
}
}
}
else
{
uint64_t v___x_1014_; uint64_t v_quotient_1015_; uint64_t v___x_1016_; uint64_t v___x_1017_; uint64_t v___x_1018_; uint64_t v___x_1019_; uint64_t v_remainder_1020_; uint64_t v___x_1021_; uint64_t v_half_1022_; uint8_t v___x_1023_; 
v___x_1014_ = lean_unbox_uint64(v___y_997_);
v_quotient_1015_ = lean_uint64_shift_right(v___x_1014_, v___x_1005_);
v___x_1016_ = 1ULL;
v___x_1017_ = lean_uint64_shift_left(v___x_1016_, v___x_1005_);
v___x_1018_ = lean_uint64_sub(v___x_1017_, v___x_1016_);
v___x_1019_ = lean_unbox_uint64(v___y_997_);
lean_dec(v___y_997_);
v_remainder_1020_ = lean_uint64_land(v___x_1019_, v___x_1018_);
v___x_1021_ = lean_uint64_sub(v___x_1005_, v___x_1016_);
v_half_1022_ = lean_uint64_shift_left(v___x_1016_, v___x_1021_);
v___x_1023_ = lean_uint64_dec_lt(v_remainder_1020_, v_half_1022_);
if (v___x_1023_ == 0)
{
uint8_t v___x_1024_; 
v___x_1024_ = lean_uint64_dec_lt(v_half_1022_, v_remainder_1020_);
if (v___x_1024_ == 0)
{
uint64_t v___x_1025_; uint8_t v___x_1026_; 
v___x_1025_ = lean_uint64_land(v_quotient_1015_, v___x_1016_);
v___x_1026_ = lean_uint64_dec_eq(v___x_1025_, v___y_995_);
if (v___x_1026_ == 0)
{
uint64_t v___x_1027_; 
v___x_1027_ = lean_uint64_add(v_quotient_1015_, v___x_1016_);
v___y_985_ = v___y_995_;
v___y_986_ = v_position_1000_;
v___y_987_ = v___y_998_;
v___y_988_ = v___x_1027_;
goto v___jp_984_;
}
else
{
v___y_985_ = v___y_995_;
v___y_986_ = v_position_1000_;
v___y_987_ = v___y_998_;
v___y_988_ = v_quotient_1015_;
goto v___jp_984_;
}
}
else
{
uint64_t v___x_1028_; 
v___x_1028_ = lean_uint64_add(v_quotient_1015_, v___x_1016_);
v___y_985_ = v___y_995_;
v___y_986_ = v_position_1000_;
v___y_987_ = v___y_998_;
v___y_988_ = v___x_1028_;
goto v___jp_984_;
}
}
else
{
v___y_985_ = v___y_995_;
v___y_986_ = v_position_1000_;
v___y_987_ = v___y_998_;
v___y_988_ = v_quotient_1015_;
goto v___jp_984_;
}
}
}
else
{
uint64_t v___x_1029_; 
v___x_1029_ = lean_unbox_uint64(v___y_997_);
lean_dec(v___y_997_);
v___y_985_ = v___y_995_;
v___y_986_ = v_position_1000_;
v___y_987_ = v___y_998_;
v___y_988_ = v___x_1029_;
goto v___jp_984_;
}
}
else
{
uint64_t v___x_1030_; uint64_t v___x_1031_; uint64_t v___x_1032_; 
v___x_1030_ = lean_uint64_sub(v___x_1003_, v___y_999_);
v___x_1031_ = lean_unbox_uint64(v___y_997_);
lean_dec(v___y_997_);
v___x_1032_ = lean_uint64_shift_left(v___x_1031_, v___x_1030_);
v___y_985_ = v___y_995_;
v___y_986_ = v_position_1000_;
v___y_987_ = v___y_998_;
v___y_988_ = v___x_1032_;
goto v___jp_984_;
}
}
else
{
uint8_t v___x_1033_; 
v___x_1033_ = lean_uint64_dec_lt(v___y_994_, v___y_996_);
if (v___x_1033_ == 0)
{
uint64_t v___x_1034_; uint64_t v___x_1035_; uint64_t v___x_1036_; 
v___x_1034_ = lean_uint64_sub(v___y_994_, v___y_996_);
v___x_1035_ = lean_unbox_uint64(v___y_997_);
lean_dec(v___y_997_);
v___x_1036_ = lean_uint64_shift_left(v___x_1035_, v___x_1034_);
v___y_640_ = v___y_995_;
v___y_641_ = v___y_998_;
v___y_642_ = v___x_1036_;
goto v___jp_639_;
}
else
{
uint64_t v___x_1037_; uint8_t v___x_1038_; 
v___x_1037_ = lean_uint64_sub(v___y_996_, v___y_994_);
v___x_1038_ = lean_uint64_dec_eq(v___x_1037_, v___y_995_);
if (v___x_1038_ == 0)
{
uint64_t v___x_1039_; uint8_t v___x_1040_; 
v___x_1039_ = 64ULL;
v___x_1040_ = lean_uint64_dec_lt(v___x_1037_, v___x_1039_);
if (v___x_1040_ == 0)
{
uint8_t v___x_1041_; 
v___x_1041_ = lean_uint64_dec_eq(v___x_1037_, v___x_1039_);
if (v___x_1041_ == 0)
{
lean_dec(v___y_997_);
v___y_640_ = v___y_995_;
v___y_641_ = v___y_998_;
v___y_642_ = v___y_995_;
goto v___jp_639_;
}
else
{
uint64_t v___x_1042_; uint64_t v___x_1043_; uint8_t v___x_1044_; 
v___x_1042_ = 9223372036854775808ULL;
v___x_1043_ = lean_unbox_uint64(v___y_997_);
lean_dec(v___y_997_);
v___x_1044_ = lean_uint64_dec_lt(v___x_1042_, v___x_1043_);
if (v___x_1044_ == 0)
{
v___y_640_ = v___y_995_;
v___y_641_ = v___y_998_;
v___y_642_ = v___y_995_;
goto v___jp_639_;
}
else
{
uint64_t v___x_1045_; 
v___x_1045_ = 1ULL;
v___y_640_ = v___y_995_;
v___y_641_ = v___y_998_;
v___y_642_ = v___x_1045_;
goto v___jp_639_;
}
}
}
else
{
uint64_t v___x_1046_; uint64_t v_quotient_1047_; uint64_t v___x_1048_; uint64_t v___x_1049_; uint64_t v___x_1050_; uint64_t v___x_1051_; uint64_t v_remainder_1052_; uint64_t v___x_1053_; uint64_t v_half_1054_; uint8_t v___x_1055_; 
v___x_1046_ = lean_unbox_uint64(v___y_997_);
v_quotient_1047_ = lean_uint64_shift_right(v___x_1046_, v___x_1037_);
v___x_1048_ = 1ULL;
v___x_1049_ = lean_uint64_shift_left(v___x_1048_, v___x_1037_);
v___x_1050_ = lean_uint64_sub(v___x_1049_, v___x_1048_);
v___x_1051_ = lean_unbox_uint64(v___y_997_);
lean_dec(v___y_997_);
v_remainder_1052_ = lean_uint64_land(v___x_1051_, v___x_1050_);
v___x_1053_ = lean_uint64_sub(v___x_1037_, v___x_1048_);
v_half_1054_ = lean_uint64_shift_left(v___x_1048_, v___x_1053_);
v___x_1055_ = lean_uint64_dec_lt(v_remainder_1052_, v_half_1054_);
if (v___x_1055_ == 0)
{
uint8_t v___x_1056_; 
v___x_1056_ = lean_uint64_dec_lt(v_half_1054_, v_remainder_1052_);
if (v___x_1056_ == 0)
{
uint64_t v___x_1057_; uint8_t v___x_1058_; 
v___x_1057_ = lean_uint64_land(v_quotient_1047_, v___x_1048_);
v___x_1058_ = lean_uint64_dec_eq(v___x_1057_, v___y_995_);
if (v___x_1058_ == 0)
{
uint64_t v___x_1059_; 
v___x_1059_ = lean_uint64_add(v_quotient_1047_, v___x_1048_);
v___y_640_ = v___y_995_;
v___y_641_ = v___y_998_;
v___y_642_ = v___x_1059_;
goto v___jp_639_;
}
else
{
v___y_640_ = v___y_995_;
v___y_641_ = v___y_998_;
v___y_642_ = v_quotient_1047_;
goto v___jp_639_;
}
}
else
{
uint64_t v___x_1060_; 
v___x_1060_ = lean_uint64_add(v_quotient_1047_, v___x_1048_);
v___y_640_ = v___y_995_;
v___y_641_ = v___y_998_;
v___y_642_ = v___x_1060_;
goto v___jp_639_;
}
}
else
{
v___y_640_ = v___y_995_;
v___y_641_ = v___y_998_;
v___y_642_ = v_quotient_1047_;
goto v___jp_639_;
}
}
}
else
{
uint64_t v___x_1061_; 
v___x_1061_ = lean_unbox_uint64(v___y_997_);
lean_dec(v___y_997_);
v___y_640_ = v___y_995_;
v___y_641_ = v___y_998_;
v___y_642_ = v___x_1061_;
goto v___jp_639_;
}
}
}
}
v___jp_1062_:
{
uint64_t v___x_1070_; uint64_t v___x_1071_; uint8_t v___x_1072_; 
v___x_1070_ = 1ULL;
v___x_1071_ = lean_uint64_shift_right(v___y_1066_, v___x_1070_);
v___x_1072_ = lean_uint64_dec_eq(v___x_1071_, v___y_1064_);
if (v___x_1072_ == 0)
{
uint64_t v___x_1073_; 
v___x_1073_ = lean_uint64_add(v___y_1069_, v___x_1070_);
v___y_994_ = v___y_1063_;
v___y_995_ = v___y_1064_;
v___y_996_ = v___y_1065_;
v___y_997_ = v___y_1067_;
v___y_998_ = v___y_1068_;
v___y_999_ = v___x_1073_;
goto v___jp_993_;
}
else
{
v___y_994_ = v___y_1063_;
v___y_995_ = v___y_1064_;
v___y_996_ = v___y_1065_;
v___y_997_ = v___y_1067_;
v___y_998_ = v___y_1068_;
v___y_999_ = v___y_1069_;
goto v___jp_993_;
}
}
v___jp_1074_:
{
uint64_t v___x_1084_; uint8_t v___x_1085_; 
v___x_1084_ = lean_uint64_shift_right(v___y_1081_, v___y_1079_);
v___x_1085_ = lean_uint64_dec_eq(v___x_1084_, v___y_1076_);
if (v___x_1085_ == 0)
{
uint64_t v___x_1086_; 
v___x_1086_ = lean_uint64_add(v___y_1077_, v___y_1079_);
v___y_1063_ = v___y_1075_;
v___y_1064_ = v___y_1076_;
v___y_1065_ = v___y_1078_;
v___y_1066_ = v___y_1083_;
v___y_1067_ = v___y_1080_;
v___y_1068_ = v___y_1082_;
v___y_1069_ = v___x_1086_;
goto v___jp_1062_;
}
else
{
v___y_1063_ = v___y_1075_;
v___y_1064_ = v___y_1076_;
v___y_1065_ = v___y_1078_;
v___y_1066_ = v___y_1083_;
v___y_1067_ = v___y_1080_;
v___y_1068_ = v___y_1082_;
v___y_1069_ = v___y_1077_;
goto v___jp_1062_;
}
}
v___jp_1087_:
{
uint64_t v___x_1095_; uint64_t v___x_1096_; uint8_t v___x_1097_; 
v___x_1095_ = 2ULL;
v___x_1096_ = lean_uint64_shift_right(v___y_1093_, v___x_1095_);
v___x_1097_ = lean_uint64_dec_eq(v___x_1096_, v___y_1089_);
if (v___x_1097_ == 0)
{
v___y_1075_ = v___y_1088_;
v___y_1076_ = v___y_1089_;
v___y_1077_ = v___y_1094_;
v___y_1078_ = v___y_1090_;
v___y_1079_ = v___x_1095_;
v___y_1080_ = v___y_1091_;
v___y_1081_ = v___y_1093_;
v___y_1082_ = v___y_1092_;
v___y_1083_ = v___x_1096_;
goto v___jp_1074_;
}
else
{
v___y_1075_ = v___y_1088_;
v___y_1076_ = v___y_1089_;
v___y_1077_ = v___y_1094_;
v___y_1078_ = v___y_1090_;
v___y_1079_ = v___x_1095_;
v___y_1080_ = v___y_1091_;
v___y_1081_ = v___y_1093_;
v___y_1082_ = v___y_1092_;
v___y_1083_ = v___y_1093_;
goto v___jp_1074_;
}
}
v___jp_1098_:
{
uint64_t v___x_1108_; uint8_t v___x_1109_; 
v___x_1108_ = lean_uint64_shift_right(v___y_1099_, v___y_1100_);
v___x_1109_ = lean_uint64_dec_eq(v___x_1108_, v___y_1102_);
if (v___x_1109_ == 0)
{
uint64_t v___x_1110_; 
v___x_1110_ = lean_uint64_add(v___y_1103_, v___y_1100_);
v___y_1088_ = v___y_1101_;
v___y_1089_ = v___y_1102_;
v___y_1090_ = v___y_1104_;
v___y_1091_ = v___y_1105_;
v___y_1092_ = v___y_1106_;
v___y_1093_ = v___y_1107_;
v___y_1094_ = v___x_1110_;
goto v___jp_1087_;
}
else
{
v___y_1088_ = v___y_1101_;
v___y_1089_ = v___y_1102_;
v___y_1090_ = v___y_1104_;
v___y_1091_ = v___y_1105_;
v___y_1092_ = v___y_1106_;
v___y_1093_ = v___y_1107_;
v___y_1094_ = v___y_1103_;
goto v___jp_1087_;
}
}
v___jp_1111_:
{
uint64_t v___x_1119_; uint64_t v___x_1120_; uint8_t v___x_1121_; 
v___x_1119_ = 4ULL;
v___x_1120_ = lean_uint64_shift_right(v___y_1112_, v___x_1119_);
v___x_1121_ = lean_uint64_dec_eq(v___x_1120_, v___y_1114_);
if (v___x_1121_ == 0)
{
v___y_1099_ = v___y_1112_;
v___y_1100_ = v___x_1119_;
v___y_1101_ = v___y_1113_;
v___y_1102_ = v___y_1114_;
v___y_1103_ = v___y_1118_;
v___y_1104_ = v___y_1115_;
v___y_1105_ = v___y_1116_;
v___y_1106_ = v___y_1117_;
v___y_1107_ = v___x_1120_;
goto v___jp_1098_;
}
else
{
v___y_1099_ = v___y_1112_;
v___y_1100_ = v___x_1119_;
v___y_1101_ = v___y_1113_;
v___y_1102_ = v___y_1114_;
v___y_1103_ = v___y_1118_;
v___y_1104_ = v___y_1115_;
v___y_1105_ = v___y_1116_;
v___y_1106_ = v___y_1117_;
v___y_1107_ = v___y_1112_;
goto v___jp_1098_;
}
}
v___jp_1122_:
{
uint64_t v___x_1132_; uint8_t v___x_1133_; 
v___x_1132_ = lean_uint64_shift_right(v___y_1126_, v___y_1125_);
v___x_1133_ = lean_uint64_dec_eq(v___x_1132_, v___y_1124_);
if (v___x_1133_ == 0)
{
uint64_t v___x_1134_; 
v___x_1134_ = lean_uint64_add(v___y_1129_, v___y_1125_);
v___y_1112_ = v___y_1131_;
v___y_1113_ = v___y_1123_;
v___y_1114_ = v___y_1124_;
v___y_1115_ = v___y_1127_;
v___y_1116_ = v___y_1128_;
v___y_1117_ = v___y_1130_;
v___y_1118_ = v___x_1134_;
goto v___jp_1111_;
}
else
{
v___y_1112_ = v___y_1131_;
v___y_1113_ = v___y_1123_;
v___y_1114_ = v___y_1124_;
v___y_1115_ = v___y_1127_;
v___y_1116_ = v___y_1128_;
v___y_1117_ = v___y_1130_;
v___y_1118_ = v___y_1129_;
goto v___jp_1111_;
}
}
v___jp_1135_:
{
uint64_t v___x_1143_; uint64_t v___x_1144_; uint8_t v___x_1145_; 
v___x_1143_ = 8ULL;
v___x_1144_ = lean_uint64_shift_right(v___y_1138_, v___x_1143_);
v___x_1145_ = lean_uint64_dec_eq(v___x_1144_, v___y_1137_);
if (v___x_1145_ == 0)
{
v___y_1123_ = v___y_1136_;
v___y_1124_ = v___y_1137_;
v___y_1125_ = v___x_1143_;
v___y_1126_ = v___y_1138_;
v___y_1127_ = v___y_1139_;
v___y_1128_ = v___y_1140_;
v___y_1129_ = v___y_1142_;
v___y_1130_ = v___y_1141_;
v___y_1131_ = v___x_1144_;
goto v___jp_1122_;
}
else
{
v___y_1123_ = v___y_1136_;
v___y_1124_ = v___y_1137_;
v___y_1125_ = v___x_1143_;
v___y_1126_ = v___y_1138_;
v___y_1127_ = v___y_1139_;
v___y_1128_ = v___y_1140_;
v___y_1129_ = v___y_1142_;
v___y_1130_ = v___y_1141_;
v___y_1131_ = v___y_1138_;
goto v___jp_1122_;
}
}
v___jp_1146_:
{
uint64_t v___x_1156_; uint8_t v___x_1157_; 
v___x_1156_ = lean_uint64_shift_right(v___y_1147_, v___y_1149_);
v___x_1157_ = lean_uint64_dec_eq(v___x_1156_, v___y_1150_);
if (v___x_1157_ == 0)
{
uint64_t v___x_1158_; 
v___x_1158_ = lean_uint64_add(v___y_1153_, v___y_1149_);
v___y_1136_ = v___y_1148_;
v___y_1137_ = v___y_1150_;
v___y_1138_ = v___y_1155_;
v___y_1139_ = v___y_1151_;
v___y_1140_ = v___y_1152_;
v___y_1141_ = v___y_1154_;
v___y_1142_ = v___x_1158_;
goto v___jp_1135_;
}
else
{
v___y_1136_ = v___y_1148_;
v___y_1137_ = v___y_1150_;
v___y_1138_ = v___y_1155_;
v___y_1139_ = v___y_1151_;
v___y_1140_ = v___y_1152_;
v___y_1141_ = v___y_1154_;
v___y_1142_ = v___y_1153_;
goto v___jp_1135_;
}
}
v___jp_1159_:
{
uint64_t v___x_1167_; uint64_t v___x_1168_; uint8_t v___x_1169_; 
v___x_1167_ = 16ULL;
v___x_1168_ = lean_uint64_shift_right(v___y_1160_, v___x_1167_);
v___x_1169_ = lean_uint64_dec_eq(v___x_1168_, v___y_1162_);
if (v___x_1169_ == 0)
{
v___y_1147_ = v___y_1160_;
v___y_1148_ = v___y_1161_;
v___y_1149_ = v___x_1167_;
v___y_1150_ = v___y_1162_;
v___y_1151_ = v___y_1163_;
v___y_1152_ = v___y_1164_;
v___y_1153_ = v___y_1166_;
v___y_1154_ = v___y_1165_;
v___y_1155_ = v___x_1168_;
goto v___jp_1146_;
}
else
{
v___y_1147_ = v___y_1160_;
v___y_1148_ = v___y_1161_;
v___y_1149_ = v___x_1167_;
v___y_1150_ = v___y_1162_;
v___y_1151_ = v___y_1163_;
v___y_1152_ = v___y_1164_;
v___y_1153_ = v___y_1166_;
v___y_1154_ = v___y_1165_;
v___y_1155_ = v___y_1160_;
goto v___jp_1146_;
}
}
v___jp_1170_:
{
uint64_t v___x_1178_; uint64_t v___x_1179_; uint8_t v___x_1180_; 
v___x_1178_ = lean_unbox_uint64(v___y_1175_);
v___x_1179_ = lean_uint64_shift_right(v___x_1178_, v___y_1172_);
v___x_1180_ = lean_uint64_dec_eq(v___x_1179_, v___y_1173_);
if (v___x_1180_ == 0)
{
v___y_1160_ = v___y_1177_;
v___y_1161_ = v___y_1171_;
v___y_1162_ = v___y_1173_;
v___y_1163_ = v___y_1174_;
v___y_1164_ = v___y_1175_;
v___y_1165_ = v___y_1176_;
v___y_1166_ = v___y_1172_;
goto v___jp_1159_;
}
else
{
v___y_1160_ = v___y_1177_;
v___y_1161_ = v___y_1171_;
v___y_1162_ = v___y_1173_;
v___y_1163_ = v___y_1174_;
v___y_1164_ = v___y_1175_;
v___y_1165_ = v___y_1176_;
v___y_1166_ = v___y_1173_;
goto v___jp_1159_;
}
}
v___jp_1181_:
{
uint64_t v___x_1185_; uint64_t v___x_1186_; uint8_t v___x_1187_; 
v___x_1185_ = 0ULL;
v___x_1186_ = lean_unbox_uint64(v_snd_1184_);
v___x_1187_ = lean_uint64_dec_eq(v___x_1186_, v___x_1185_);
if (v___x_1187_ == 0)
{
uint64_t v___x_1188_; uint64_t v___x_1189_; uint64_t v___x_1190_; uint64_t v___x_1191_; uint64_t v___x_1192_; uint8_t v___x_1193_; 
v___x_1188_ = 149ULL;
v___x_1189_ = lean_uint64_add(v___y_1182_, v___x_1188_);
v___x_1190_ = 32ULL;
v___x_1191_ = lean_unbox_uint64(v_snd_1184_);
v___x_1192_ = lean_uint64_shift_right(v___x_1191_, v___x_1190_);
v___x_1193_ = lean_uint64_dec_eq(v___x_1192_, v___x_1185_);
if (v___x_1193_ == 0)
{
v___y_1171_ = v___x_1189_;
v___y_1172_ = v___x_1190_;
v___y_1173_ = v___x_1185_;
v___y_1174_ = v___x_1188_;
v___y_1175_ = v_snd_1184_;
v___y_1176_ = v_fst_1183_;
v___y_1177_ = v___x_1192_;
goto v___jp_1170_;
}
else
{
uint64_t v___x_1194_; 
v___x_1194_ = lean_unbox_uint64(v_snd_1184_);
v___y_1171_ = v___x_1189_;
v___y_1172_ = v___x_1190_;
v___y_1173_ = v___x_1185_;
v___y_1174_ = v___x_1188_;
v___y_1175_ = v_snd_1184_;
v___y_1176_ = v_fst_1183_;
v___y_1177_ = v___x_1194_;
goto v___jp_1170_;
}
}
else
{
uint8_t v___x_1195_; 
lean_dec(v_snd_1184_);
v___x_1195_ = lean_unbox(v_fst_1183_);
lean_dec(v_fst_1183_);
if (v___x_1195_ == 0)
{
uint32_t v___x_1196_; 
v___x_1196_ = 0;
return v___x_1196_;
}
else
{
uint32_t v___x_1197_; 
v___x_1197_ = 2147483648;
return v___x_1197_;
}
}
}
v___jp_1198_:
{
uint8_t v___x_1205_; 
v___x_1205_ = lean_uint64_dec_eq(v___y_1202_, v___y_1200_);
if (v___x_1205_ == 0)
{
uint8_t v___x_1206_; 
v___x_1206_ = lean_uint64_dec_lt(v___y_1202_, v___y_1200_);
if (v___x_1206_ == 0)
{
uint64_t v___x_1207_; lean_object* v___x_1208_; lean_object* v___x_1209_; 
v___x_1207_ = lean_uint64_sub(v___y_1202_, v___y_1200_);
v___x_1208_ = lean_box(v___y_1201_);
v___x_1209_ = lean_box_uint64(v___x_1207_);
v___y_1182_ = v___y_1199_;
v_fst_1183_ = v___x_1208_;
v_snd_1184_ = v___x_1209_;
goto v___jp_1181_;
}
else
{
uint64_t v___x_1210_; lean_object* v___x_1211_; lean_object* v___x_1212_; 
v___x_1210_ = lean_uint64_sub(v___y_1200_, v___y_1202_);
v___x_1211_ = lean_box(v___y_1203_);
v___x_1212_ = lean_box_uint64(v___x_1210_);
v___y_1182_ = v___y_1199_;
v_fst_1183_ = v___x_1211_;
v_snd_1184_ = v___x_1212_;
goto v___jp_1181_;
}
}
else
{
lean_object* v___x_1213_; lean_object* v___x_1214_; 
v___x_1213_ = lean_box(v___y_1204_);
v___x_1214_ = ((lean_object*)(lp_competition_Submission_TunedAdd_core___boxed__const__1));
v___y_1182_ = v___y_1199_;
v_fst_1183_ = v___x_1213_;
v_snd_1184_ = v___x_1214_;
goto v___jp_1181_;
}
}
v___jp_1215_:
{
if (v___y_1221_ == 0)
{
v___y_1199_ = v___y_1216_;
v___y_1200_ = v___y_1217_;
v___y_1201_ = v___y_1218_;
v___y_1202_ = v___y_1219_;
v___y_1203_ = v___y_1220_;
v___y_1204_ = v___y_1221_;
goto v___jp_1198_;
}
else
{
uint64_t v___x_1222_; lean_object* v___x_1223_; lean_object* v___x_1224_; 
v___x_1222_ = lean_uint64_add(v___y_1219_, v___y_1217_);
v___x_1223_ = lean_box(v___y_1218_);
v___x_1224_ = lean_box_uint64(v___x_1222_);
v___y_1182_ = v___y_1216_;
v_fst_1183_ = v___x_1223_;
v_snd_1184_ = v___x_1224_;
goto v___jp_1181_;
}
}
v___jp_1225_:
{
uint8_t v___x_1232_; 
v___x_1232_ = lean_uint64_dec_le(v___y_1228_, v___y_1231_);
if (v___x_1232_ == 0)
{
uint64_t v_shift_1233_; uint64_t v___x_1234_; uint8_t v___x_1235_; 
v_shift_1233_ = lean_uint64_sub(v___y_1228_, v___y_1231_);
v___x_1234_ = 39ULL;
v___x_1235_ = lean_uint64_dec_le(v_shift_1233_, v___x_1234_);
if (v___x_1235_ == 0)
{
return v_xBits_600_;
}
else
{
uint64_t v___x_1236_; 
v___x_1236_ = lean_uint64_shift_left(v___y_1226_, v_shift_1233_);
if (v___y_1229_ == 0)
{
if (v___y_1230_ == 0)
{
v___y_1216_ = v___y_1231_;
v___y_1217_ = v___y_1227_;
v___y_1218_ = v___y_1229_;
v___y_1219_ = v___x_1236_;
v___y_1220_ = v___y_1230_;
v___y_1221_ = v___x_1235_;
goto v___jp_1215_;
}
else
{
v___y_1199_ = v___y_1231_;
v___y_1200_ = v___y_1227_;
v___y_1201_ = v___y_1229_;
v___y_1202_ = v___x_1236_;
v___y_1203_ = v___y_1230_;
v___y_1204_ = v___y_1229_;
goto v___jp_1198_;
}
}
else
{
v___y_1216_ = v___y_1231_;
v___y_1217_ = v___y_1227_;
v___y_1218_ = v___y_1229_;
v___y_1219_ = v___x_1236_;
v___y_1220_ = v___y_1230_;
v___y_1221_ = v___y_1230_;
goto v___jp_1215_;
}
}
}
else
{
uint64_t v_shift_1237_; uint64_t v___x_1238_; uint8_t v___x_1239_; 
v_shift_1237_ = lean_uint64_sub(v___y_1231_, v___y_1228_);
v___x_1238_ = 39ULL;
v___x_1239_ = lean_uint64_dec_le(v_shift_1237_, v___x_1238_);
if (v___x_1239_ == 0)
{
return v_yBits_601_;
}
else
{
uint64_t v___x_1240_; 
v___x_1240_ = lean_uint64_shift_left(v___y_1227_, v_shift_1237_);
if (v___y_1229_ == 0)
{
if (v___y_1230_ == 0)
{
v___y_933_ = v___y_1226_;
v___y_934_ = v___y_1228_;
v___y_935_ = v___y_1229_;
v___y_936_ = v___x_1240_;
v___y_937_ = v___y_1230_;
v___y_938_ = v___x_1239_;
goto v___jp_932_;
}
else
{
v___y_916_ = v___y_1226_;
v___y_917_ = v___y_1228_;
v___y_918_ = v___y_1229_;
v___y_919_ = v___x_1240_;
v___y_920_ = v___y_1230_;
v___y_921_ = v___y_1229_;
goto v___jp_915_;
}
}
else
{
v___y_933_ = v___y_1226_;
v___y_934_ = v___y_1228_;
v___y_935_ = v___y_1229_;
v___y_936_ = v___x_1240_;
v___y_937_ = v___y_1230_;
v___y_938_ = v___y_1230_;
goto v___jp_932_;
}
}
}
}
v___jp_1244_:
{
uint64_t v___x_1250_; uint64_t v___x_1251_; uint8_t v___x_1252_; 
v___x_1250_ = lean_uint32_to_uint64(v_yExponent_1243_);
v___x_1251_ = 0ULL;
v___x_1252_ = lean_uint64_dec_eq(v___x_1250_, v___x_1251_);
if (v___x_1252_ == 0)
{
uint64_t v___x_1253_; uint64_t v___x_1254_; 
v___x_1253_ = 1ULL;
v___x_1254_ = lean_uint64_sub(v___x_1250_, v___x_1253_);
v___y_1226_ = v___y_1245_;
v___y_1227_ = v___y_1246_;
v___y_1228_ = v___y_1249_;
v___y_1229_ = v___y_1247_;
v___y_1230_ = v___y_1248_;
v___y_1231_ = v___x_1254_;
goto v___jp_1225_;
}
else
{
v___y_1226_ = v___y_1245_;
v___y_1227_ = v___y_1246_;
v___y_1228_ = v___y_1249_;
v___y_1229_ = v___y_1247_;
v___y_1230_ = v___y_1248_;
v___y_1231_ = v___x_1251_;
goto v___jp_1225_;
}
}
v___jp_1255_:
{
uint64_t v___x_1260_; uint64_t v___x_1261_; uint8_t v___x_1262_; 
v___x_1260_ = lean_uint32_to_uint64(v_xExponent_1241_);
v___x_1261_ = 0ULL;
v___x_1262_ = lean_uint64_dec_eq(v___x_1260_, v___x_1261_);
if (v___x_1262_ == 0)
{
uint64_t v___x_1263_; uint64_t v___x_1264_; 
v___x_1263_ = 1ULL;
v___x_1264_ = lean_uint64_sub(v___x_1260_, v___x_1263_);
v___y_1245_ = v___y_1256_;
v___y_1246_ = v___y_1259_;
v___y_1247_ = v___y_1257_;
v___y_1248_ = v___y_1258_;
v___y_1249_ = v___x_1264_;
goto v___jp_1244_;
}
else
{
v___y_1245_ = v___y_1256_;
v___y_1246_ = v___y_1259_;
v___y_1247_ = v___y_1257_;
v___y_1248_ = v___y_1258_;
v___y_1249_ = v___x_1261_;
goto v___jp_1244_;
}
}
v___jp_1265_:
{
uint32_t v___x_1269_; uint32_t v___x_1270_; uint32_t v___x_1271_; uint8_t v___x_1272_; 
v___x_1269_ = 8388607;
v___x_1270_ = lean_uint32_land(v_yBits_601_, v___x_1269_);
v___x_1271_ = 0;
v___x_1272_ = lean_uint32_dec_eq(v_yExponent_1243_, v___x_1271_);
if (v___x_1272_ == 0)
{
uint64_t v___x_1273_; uint64_t v___x_1274_; uint64_t v___x_1275_; 
v___x_1273_ = lean_uint32_to_uint64(v___x_1270_);
v___x_1274_ = 8388608ULL;
v___x_1275_ = lean_uint64_lor(v___x_1273_, v___x_1274_);
v___y_1256_ = v___y_1268_;
v___y_1257_ = v___y_1266_;
v___y_1258_ = v___y_1267_;
v___y_1259_ = v___x_1275_;
goto v___jp_1255_;
}
else
{
uint64_t v___x_1276_; 
v___x_1276_ = lean_uint32_to_uint64(v___x_1270_);
v___y_1256_ = v___y_1268_;
v___y_1257_ = v___y_1266_;
v___y_1258_ = v___y_1267_;
v___y_1259_ = v___x_1276_;
goto v___jp_1255_;
}
}
v___jp_1277_:
{
uint32_t v___x_1280_; uint32_t v___x_1281_; uint32_t v___x_1282_; uint8_t v___x_1283_; 
v___x_1280_ = 8388607;
v___x_1281_ = lean_uint32_land(v_xBits_600_, v___x_1280_);
v___x_1282_ = 0;
v___x_1283_ = lean_uint32_dec_eq(v_xExponent_1241_, v___x_1282_);
if (v___x_1283_ == 0)
{
uint64_t v___x_1284_; uint64_t v___x_1285_; uint64_t v___x_1286_; 
v___x_1284_ = lean_uint32_to_uint64(v___x_1281_);
v___x_1285_ = 8388608ULL;
v___x_1286_ = lean_uint64_lor(v___x_1284_, v___x_1285_);
v___y_1266_ = v___y_1278_;
v___y_1267_ = v___y_1279_;
v___y_1268_ = v___x_1286_;
goto v___jp_1265_;
}
else
{
uint64_t v___x_1287_; 
v___x_1287_ = lean_uint32_to_uint64(v___x_1281_);
v___y_1266_ = v___y_1278_;
v___y_1267_ = v___y_1279_;
v___y_1268_ = v___x_1287_;
goto v___jp_1265_;
}
}
v___jp_1288_:
{
uint32_t v___x_1290_; uint32_t v___x_1291_; uint32_t v___x_1292_; uint8_t v___x_1293_; 
v___x_1290_ = 2147483648;
v___x_1291_ = lean_uint32_land(v_yBits_601_, v___x_1290_);
v___x_1292_ = 0;
v___x_1293_ = lean_uint32_dec_eq(v___x_1291_, v___x_1292_);
if (v___x_1293_ == 0)
{
uint8_t v___x_1294_; 
v___x_1294_ = 1;
v___y_1278_ = v___y_1289_;
v___y_1279_ = v___x_1294_;
goto v___jp_1277_;
}
else
{
uint8_t v___x_1295_; 
v___x_1295_ = 0;
v___y_1278_ = v___y_1289_;
v___y_1279_ = v___x_1295_;
goto v___jp_1277_;
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_TunedAdd_core___boxed(lean_object* v_xBits_1302_, lean_object* v_yBits_1303_){
_start:
{
uint32_t v_xBits_boxed_1304_; uint32_t v_yBits_boxed_1305_; uint32_t v_res_1306_; lean_object* v_r_1307_; 
v_xBits_boxed_1304_ = lean_unbox_uint32(v_xBits_1302_);
lean_dec(v_xBits_1302_);
v_yBits_boxed_1305_ = lean_unbox_uint32(v_yBits_1303_);
lean_dec(v_yBits_1303_);
v_res_1306_ = lp_competition_Submission_TunedAdd_core(v_xBits_boxed_1304_, v_yBits_boxed_1305_);
v_r_1307_ = lean_box_uint32(v_res_1306_);
return v_r_1307_;
}
}
LEAN_EXPORT uint8_t lp_competition_Submission_TunedAdd_sp1(uint32_t v_a_1308_){
_start:
{
uint32_t v___x_1309_; uint32_t v___x_1310_; uint32_t v___x_1311_; uint32_t v___x_1312_; uint8_t v___x_1313_; 
v___x_1309_ = 4278190079;
v___x_1310_ = 1;
v___x_1311_ = lean_uint32_shift_left(v_a_1308_, v___x_1310_);
v___x_1312_ = lean_uint32_sub(v___x_1311_, v___x_1310_);
v___x_1313_ = lean_uint32_dec_le(v___x_1309_, v___x_1312_);
return v___x_1313_;
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_TunedAdd_sp1___boxed(lean_object* v_a_1314_){
_start:
{
uint32_t v_a_boxed_1315_; uint8_t v_res_1316_; lean_object* v_r_1317_; 
v_a_boxed_1315_ = lean_unbox_uint32(v_a_1314_);
lean_dec(v_a_1314_);
v_res_1316_ = lp_competition_Submission_TunedAdd_sp1(v_a_boxed_1315_);
v_r_1317_ = lean_box(v_res_1316_);
return v_r_1317_;
}
}
LEAN_EXPORT uint8_t lp_competition_Submission_TunedAdd_special(uint32_t v_a_1318_, uint32_t v_b_1319_){
_start:
{
uint32_t v___x_1320_; uint32_t v___x_1321_; uint32_t v___x_1322_; uint32_t v___x_1323_; uint8_t v___x_1324_; 
v___x_1320_ = 4278190079;
v___x_1321_ = 1;
v___x_1322_ = lean_uint32_shift_left(v_a_1318_, v___x_1321_);
v___x_1323_ = lean_uint32_sub(v___x_1322_, v___x_1321_);
v___x_1324_ = lean_uint32_dec_le(v___x_1320_, v___x_1323_);
if (v___x_1324_ == 0)
{
uint32_t v___x_1325_; uint32_t v___x_1326_; uint8_t v___x_1327_; 
v___x_1325_ = lean_uint32_shift_left(v_b_1319_, v___x_1321_);
v___x_1326_ = lean_uint32_sub(v___x_1325_, v___x_1321_);
v___x_1327_ = lean_uint32_dec_le(v___x_1320_, v___x_1326_);
return v___x_1327_;
}
else
{
return v___x_1324_;
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_TunedAdd_special___boxed(lean_object* v_a_1328_, lean_object* v_b_1329_){
_start:
{
uint32_t v_a_boxed_1330_; uint32_t v_b_boxed_1331_; uint8_t v_res_1332_; lean_object* v_r_1333_; 
v_a_boxed_1330_ = lean_unbox_uint32(v_a_1328_);
lean_dec(v_a_1328_);
v_b_boxed_1331_ = lean_unbox_uint32(v_b_1329_);
lean_dec(v_b_1329_);
v_res_1332_ = lp_competition_Submission_TunedAdd_special(v_a_boxed_1330_, v_b_boxed_1331_);
v_r_1333_ = lean_box(v_res_1332_);
return v_r_1333_;
}
}
LEAN_EXPORT uint32_t lp_competition_Submission_TunedAdd_ofBits(uint32_t v_w_1334_){
_start:
{
return v_w_1334_;
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_TunedAdd_ofBits___boxed(lean_object* v_w_1335_){
_start:
{
uint32_t v_w_boxed_1336_; uint32_t v_res_1337_; lean_object* v_r_1338_; 
v_w_boxed_1336_ = lean_unbox_uint32(v_w_1335_);
lean_dec(v_w_1335_);
v_res_1337_ = lp_competition_Submission_TunedAdd_ofBits(v_w_boxed_1336_);
v_r_1338_ = lean_box_uint32(v_res_1337_);
return v_r_1338_;
}
}
LEAN_EXPORT uint32_t lp_competition_Submission_TunedAdd_add(uint32_t v_x_1339_, uint32_t v_y_1340_){
_start:
{
uint32_t v___y_1342_; uint32_t v___y_1346_; uint32_t v___y_1350_; uint32_t v___y_1351_; uint64_t v___y_1356_; lean_object* v___y_1357_; uint64_t v___y_1358_; uint32_t v___y_1373_; uint32_t v___y_1374_; uint32_t v___y_1375_; uint32_t v___y_1376_; uint32_t v___y_1377_; lean_object* v___y_1385_; uint32_t v___y_1386_; uint32_t v___y_1387_; uint32_t v___y_1388_; uint32_t v___y_1389_; uint64_t v___y_1394_; uint64_t v___y_1395_; lean_object* v___y_1396_; uint32_t v___y_1397_; uint32_t v___y_1398_; uint64_t v___y_1399_; uint64_t v___y_1409_; lean_object* v___y_1410_; uint32_t v___y_1411_; uint8_t v___y_1412_; uint64_t v___y_1413_; uint32_t v___y_1414_; uint64_t v___y_1415_; uint64_t v___y_1423_; uint64_t v___y_1424_; lean_object* v___y_1425_; uint32_t v___y_1426_; uint32_t v___y_1427_; uint64_t v___y_1428_; uint64_t v___y_1434_; uint64_t v___y_1435_; lean_object* v___y_1436_; uint32_t v___y_1437_; uint32_t v___y_1438_; uint64_t v___y_1439_; lean_object* v___y_1440_; uint64_t v___y_1441_; uint64_t v___y_1505_; uint64_t v___y_1506_; lean_object* v___y_1507_; uint32_t v___y_1508_; uint64_t v___y_1509_; uint32_t v___y_1510_; uint64_t v___y_1511_; lean_object* v___y_1512_; uint64_t v___y_1513_; uint64_t v___y_1519_; uint64_t v___y_1520_; lean_object* v___y_1521_; uint32_t v___y_1522_; uint64_t v___y_1523_; uint32_t v___y_1524_; uint64_t v___y_1525_; uint64_t v___y_1526_; uint64_t v___y_1527_; lean_object* v___y_1528_; uint64_t v___y_1529_; uint64_t v___y_1534_; uint64_t v___y_1535_; lean_object* v___y_1536_; uint32_t v___y_1537_; uint32_t v___y_1538_; uint64_t v___y_1539_; lean_object* v___y_1540_; uint64_t v___y_1541_; uint64_t v___y_1542_; uint64_t v___y_1547_; uint64_t v___y_1548_; lean_object* v___y_1549_; uint32_t v___y_1550_; uint64_t v___y_1551_; uint32_t v___y_1552_; uint64_t v___y_1553_; uint64_t v___y_1554_; uint64_t v___y_1555_; lean_object* v___y_1556_; uint64_t v___y_1557_; uint64_t v___y_1562_; uint64_t v___y_1563_; lean_object* v___y_1564_; uint32_t v___y_1565_; uint32_t v___y_1566_; uint64_t v___y_1567_; lean_object* v___y_1568_; uint64_t v___y_1569_; uint64_t v___y_1570_; uint64_t v___y_1575_; uint64_t v___y_1576_; uint64_t v___y_1577_; lean_object* v___y_1578_; uint32_t v___y_1579_; uint64_t v___y_1580_; uint64_t v___y_1581_; uint32_t v___y_1582_; uint64_t v___y_1583_; lean_object* v___y_1584_; uint64_t v___y_1585_; uint64_t v___y_1590_; uint64_t v___y_1591_; uint64_t v___y_1592_; lean_object* v___y_1593_; uint32_t v___y_1594_; uint32_t v___y_1595_; uint64_t v___y_1596_; lean_object* v___y_1597_; uint64_t v___y_1598_; uint64_t v___y_1603_; uint64_t v___y_1604_; uint64_t v___y_1605_; uint64_t v___y_1606_; lean_object* v___y_1607_; uint32_t v___y_1608_; uint64_t v___y_1609_; uint32_t v___y_1610_; uint64_t v___y_1611_; lean_object* v___y_1612_; uint64_t v___y_1613_; uint64_t v___y_1618_; uint64_t v___y_1619_; lean_object* v___y_1620_; uint32_t v___y_1621_; uint64_t v___y_1622_; uint32_t v___y_1623_; uint64_t v___y_1624_; lean_object* v___y_1625_; uint64_t v___y_1626_; uint64_t v___y_1631_; uint64_t v___y_1632_; lean_object* v___y_1633_; uint32_t v___y_1634_; uint64_t v___y_1635_; uint32_t v___y_1636_; uint64_t v___y_1637_; lean_object* v___y_1638_; uint64_t v___y_1639_; uint32_t v___y_1644_; uint64_t v___y_1645_; uint32_t v___y_1646_; lean_object* v_fst_1647_; lean_object* v_snd_1648_; uint32_t v___y_1663_; uint32_t v___y_1664_; lean_object* v___y_1669_; uint64_t v___y_1670_; uint64_t v___y_1671_; uint32_t v___y_1686_; uint32_t v___y_1687_; uint32_t v___y_1688_; uint32_t v___y_1689_; uint32_t v___y_1690_; lean_object* v___y_1698_; uint32_t v___y_1699_; uint32_t v___y_1700_; uint32_t v___y_1701_; uint32_t v___y_1702_; lean_object* v___y_1707_; uint32_t v___y_1708_; uint64_t v___y_1709_; uint32_t v___y_1710_; uint64_t v___y_1711_; uint64_t v___y_1712_; lean_object* v___y_1722_; uint32_t v___y_1723_; uint32_t v___y_1724_; uint64_t v___y_1725_; uint8_t v___y_1726_; uint64_t v___y_1727_; uint64_t v___y_1728_; lean_object* v___y_1736_; uint64_t v___y_1737_; uint32_t v___y_1738_; uint32_t v___y_1739_; uint64_t v___y_1740_; uint64_t v___y_1741_; lean_object* v___y_1747_; lean_object* v___y_1748_; uint32_t v___y_1749_; uint64_t v___y_1750_; uint32_t v___y_1751_; uint64_t v___y_1752_; uint64_t v___y_1753_; uint64_t v___y_1754_; lean_object* v___y_1818_; uint64_t v___y_1819_; lean_object* v___y_1820_; uint32_t v___y_1821_; uint64_t v___y_1822_; uint64_t v___y_1823_; uint32_t v___y_1824_; uint64_t v___y_1825_; uint64_t v___y_1826_; lean_object* v___y_1832_; lean_object* v___y_1833_; uint32_t v___y_1834_; uint64_t v___y_1835_; uint64_t v___y_1836_; uint32_t v___y_1837_; uint64_t v___y_1838_; uint64_t v___y_1839_; uint64_t v___y_1840_; uint64_t v___y_1841_; uint64_t v___y_1842_; lean_object* v___y_1847_; lean_object* v___y_1848_; uint32_t v___y_1849_; uint64_t v___y_1850_; uint64_t v___y_1851_; uint64_t v___y_1852_; uint32_t v___y_1853_; uint64_t v___y_1854_; uint64_t v___y_1855_; lean_object* v___y_1860_; uint64_t v___y_1861_; lean_object* v___y_1862_; uint64_t v___y_1863_; uint32_t v___y_1864_; uint64_t v___y_1865_; uint64_t v___y_1866_; uint32_t v___y_1867_; uint64_t v___y_1868_; uint64_t v___y_1869_; uint64_t v___y_1870_; lean_object* v___y_1875_; lean_object* v___y_1876_; uint32_t v___y_1877_; uint64_t v___y_1878_; uint64_t v___y_1879_; uint64_t v___y_1880_; uint32_t v___y_1881_; uint64_t v___y_1882_; uint64_t v___y_1883_; lean_object* v___y_1888_; lean_object* v___y_1889_; uint32_t v___y_1890_; uint64_t v___y_1891_; uint32_t v___y_1892_; uint64_t v___y_1893_; uint64_t v___y_1894_; uint64_t v___y_1895_; uint64_t v___y_1896_; uint64_t v___y_1897_; uint64_t v___y_1898_; lean_object* v___y_1903_; lean_object* v___y_1904_; uint32_t v___y_1905_; uint64_t v___y_1906_; uint64_t v___y_1907_; uint32_t v___y_1908_; uint64_t v___y_1909_; uint64_t v___y_1910_; uint64_t v___y_1911_; lean_object* v___y_1916_; uint64_t v___y_1917_; uint64_t v___y_1918_; lean_object* v___y_1919_; uint64_t v___y_1920_; uint32_t v___y_1921_; uint64_t v___y_1922_; uint32_t v___y_1923_; uint64_t v___y_1924_; uint64_t v___y_1925_; uint64_t v___y_1926_; lean_object* v___y_1931_; uint64_t v___y_1932_; lean_object* v___y_1933_; uint32_t v___y_1934_; uint64_t v___y_1935_; uint64_t v___y_1936_; uint32_t v___y_1937_; uint64_t v___y_1938_; uint64_t v___y_1939_; lean_object* v___y_1944_; lean_object* v___y_1945_; uint32_t v___y_1946_; uint64_t v___y_1947_; uint32_t v___y_1948_; uint64_t v___y_1949_; uint64_t v___y_1950_; uint64_t v___y_1951_; uint64_t v___y_1952_; uint64_t v___y_1957_; uint32_t v___y_1958_; uint32_t v___y_1959_; lean_object* v_fst_1960_; lean_object* v_snd_1961_; uint64_t v___y_1976_; uint64_t v___y_1977_; uint32_t v___y_1978_; uint64_t v___y_1979_; uint32_t v___y_1980_; uint8_t v___y_1981_; uint8_t v___y_1982_; uint8_t v___y_1983_; uint64_t v___y_1995_; uint64_t v___y_1996_; uint64_t v___y_1997_; uint32_t v___y_1998_; uint32_t v___y_1999_; uint8_t v___y_2000_; uint8_t v___y_2001_; uint8_t v___y_2002_; uint64_t v___y_2007_; uint32_t v___y_2008_; uint64_t v___y_2009_; uint32_t v___y_2010_; uint8_t v___y_2011_; uint8_t v___y_2012_; uint64_t v___y_2013_; uint8_t v___y_2014_; uint32_t v___y_2026_; uint64_t v___y_2027_; uint64_t v___y_2028_; uint32_t v___y_2029_; uint8_t v___y_2030_; uint8_t v___y_2031_; uint64_t v___y_2032_; uint8_t v___y_2033_; uint64_t v___y_2038_; uint64_t v___y_2039_; uint32_t v___y_2040_; uint32_t v___y_2041_; uint8_t v___y_2042_; uint8_t v___y_2043_; uint64_t v___y_2044_; uint64_t v___y_2045_; uint64_t v___y_2056_; uint32_t v___y_2057_; uint32_t v___y_2058_; uint32_t v___y_2059_; uint8_t v___y_2060_; uint8_t v___y_2061_; uint64_t v___y_2062_; uint64_t v___y_2063_; uint32_t v___y_2070_; uint32_t v___y_2071_; uint32_t v___y_2072_; uint8_t v___y_2073_; uint8_t v___y_2074_; uint32_t v___y_2075_; uint64_t v___y_2076_; uint64_t v___y_2077_; uint32_t v___y_2084_; uint32_t v___y_2085_; uint32_t v___y_2086_; uint8_t v___y_2087_; uint8_t v___y_2088_; uint32_t v___y_2089_; uint64_t v___y_2090_; uint32_t v___y_2100_; uint32_t v___y_2101_; uint32_t v___y_2102_; uint8_t v___y_2103_; uint32_t v___y_2104_; uint8_t v___y_2105_; uint8_t v___y_2115_; uint32_t v___y_2116_; uint32_t v___y_2117_; uint32_t v___y_2118_; uint32_t v___y_2119_; uint8_t v___y_2120_; uint8_t v___y_2127_; uint32_t v___x_2143_; uint32_t v___x_2144_; uint32_t v___x_2145_; uint32_t v___x_2146_; uint8_t v___x_2147_; 
v___x_2143_ = 4278190079;
v___x_2144_ = 1;
v___x_2145_ = lean_uint32_shift_left(v_x_1339_, v___x_2144_);
v___x_2146_ = lean_uint32_sub(v___x_2145_, v___x_2144_);
v___x_2147_ = lean_uint32_dec_le(v___x_2143_, v___x_2146_);
if (v___x_2147_ == 0)
{
uint32_t v___x_2148_; uint32_t v___x_2149_; uint8_t v___x_2150_; 
v___x_2148_ = lean_uint32_shift_left(v_y_1340_, v___x_2144_);
v___x_2149_ = lean_uint32_sub(v___x_2148_, v___x_2144_);
v___x_2150_ = lean_uint32_dec_le(v___x_2143_, v___x_2149_);
v___y_2127_ = v___x_2150_;
goto v___jp_2126_;
}
else
{
v___y_2127_ = v___x_2147_;
goto v___jp_2126_;
}
v___jp_1341_:
{
uint32_t v___x_1343_; uint32_t v___x_1344_; 
v___x_1343_ = 8388608;
v___x_1344_ = lean_uint32_lor(v___y_1342_, v___x_1343_);
return v___x_1344_;
}
v___jp_1345_:
{
uint32_t v___x_1347_; uint32_t v___x_1348_; 
v___x_1347_ = 8388608;
v___x_1348_ = lean_uint32_lor(v___y_1346_, v___x_1347_);
return v___x_1348_;
}
v___jp_1349_:
{
uint32_t v___x_1352_; uint32_t v___x_1353_; uint32_t v___x_1354_; 
v___x_1352_ = 8388607;
v___x_1353_ = lean_uint32_land(v___y_1350_, v___x_1352_);
v___x_1354_ = lean_uint32_lor(v___y_1351_, v___x_1353_);
return v___x_1354_;
}
v___jp_1355_:
{
uint8_t v___x_1359_; 
v___x_1359_ = lean_uint64_dec_eq(v___y_1358_, v___y_1356_);
if (v___x_1359_ == 0)
{
uint64_t v___x_1360_; uint8_t v___x_1361_; 
v___x_1360_ = 8388608ULL;
v___x_1361_ = lean_uint64_dec_eq(v___y_1358_, v___x_1360_);
if (v___x_1361_ == 0)
{
uint32_t v___x_1362_; uint8_t v___x_1363_; 
v___x_1362_ = lean_uint64_to_uint32(v___y_1358_);
v___x_1363_ = lean_unbox(v___y_1357_);
lean_dec(v___y_1357_);
if (v___x_1363_ == 0)
{
uint32_t v___x_1364_; 
v___x_1364_ = 0;
v___y_1350_ = v___x_1362_;
v___y_1351_ = v___x_1364_;
goto v___jp_1349_;
}
else
{
uint32_t v___x_1365_; 
v___x_1365_ = 2147483648;
v___y_1350_ = v___x_1362_;
v___y_1351_ = v___x_1365_;
goto v___jp_1349_;
}
}
else
{
uint8_t v___x_1366_; 
v___x_1366_ = lean_unbox(v___y_1357_);
lean_dec(v___y_1357_);
if (v___x_1366_ == 0)
{
uint32_t v___x_1367_; 
v___x_1367_ = 0;
v___y_1346_ = v___x_1367_;
goto v___jp_1345_;
}
else
{
uint32_t v___x_1368_; 
v___x_1368_ = 2147483648;
v___y_1346_ = v___x_1368_;
goto v___jp_1345_;
}
}
}
else
{
uint8_t v___x_1369_; 
v___x_1369_ = lean_unbox(v___y_1357_);
lean_dec(v___y_1357_);
if (v___x_1369_ == 0)
{
uint32_t v___x_1370_; 
v___x_1370_ = 0;
return v___x_1370_;
}
else
{
uint32_t v___x_1371_; 
v___x_1371_ = 2147483648;
return v___x_1371_;
}
}
}
v___jp_1372_:
{
uint32_t v___x_1378_; uint32_t v___x_1379_; uint32_t v___x_1380_; uint32_t v___x_1381_; uint32_t v___x_1382_; uint32_t v___x_1383_; 
v___x_1378_ = lean_uint32_land(v___y_1375_, v___y_1376_);
v___x_1379_ = lean_uint32_shift_left(v___x_1378_, v___y_1374_);
v___x_1380_ = lean_uint32_lor(v___y_1377_, v___x_1379_);
v___x_1381_ = 8388607;
v___x_1382_ = lean_uint32_land(v___y_1373_, v___x_1381_);
v___x_1383_ = lean_uint32_lor(v___x_1380_, v___x_1382_);
return v___x_1383_;
}
v___jp_1384_:
{
uint8_t v___x_1390_; 
v___x_1390_ = lean_unbox(v___y_1385_);
lean_dec(v___y_1385_);
if (v___x_1390_ == 0)
{
uint32_t v___x_1391_; 
v___x_1391_ = 0;
v___y_1373_ = v___y_1389_;
v___y_1374_ = v___y_1386_;
v___y_1375_ = v___y_1387_;
v___y_1376_ = v___y_1388_;
v___y_1377_ = v___x_1391_;
goto v___jp_1372_;
}
else
{
uint32_t v___x_1392_; 
v___x_1392_ = 2147483648;
v___y_1373_ = v___y_1389_;
v___y_1374_ = v___y_1386_;
v___y_1375_ = v___y_1387_;
v___y_1376_ = v___y_1388_;
v___y_1377_ = v___x_1392_;
goto v___jp_1372_;
}
}
v___jp_1393_:
{
uint64_t v___x_1400_; uint64_t v_encodedExponent_1401_; uint32_t v___x_1402_; uint64_t v___x_1403_; uint8_t v___x_1404_; 
v___x_1400_ = 171ULL;
v_encodedExponent_1401_ = lean_uint64_sub(v___y_1395_, v___x_1400_);
v___x_1402_ = lean_uint64_to_uint32(v_encodedExponent_1401_);
v___x_1403_ = 8388608ULL;
v___x_1404_ = lean_uint64_dec_lt(v___y_1399_, v___x_1403_);
if (v___x_1404_ == 0)
{
uint64_t v___x_1405_; uint32_t v___x_1406_; 
v___x_1405_ = lean_uint64_sub(v___y_1399_, v___x_1403_);
v___x_1406_ = lean_uint64_to_uint32(v___x_1405_);
v___y_1385_ = v___y_1396_;
v___y_1386_ = v___y_1397_;
v___y_1387_ = v___x_1402_;
v___y_1388_ = v___y_1398_;
v___y_1389_ = v___x_1406_;
goto v___jp_1384_;
}
else
{
uint32_t v___x_1407_; 
v___x_1407_ = lean_uint64_to_uint32(v___y_1394_);
v___y_1385_ = v___y_1396_;
v___y_1386_ = v___y_1397_;
v___y_1387_ = v___x_1402_;
v___y_1388_ = v___y_1398_;
v___y_1389_ = v___x_1407_;
goto v___jp_1384_;
}
}
v___jp_1408_:
{
uint64_t v___x_1416_; uint8_t v___x_1417_; 
v___x_1416_ = 425ULL;
v___x_1417_ = lean_uint64_dec_lt(v___x_1416_, v___y_1415_);
if (v___x_1417_ == 0)
{
if (v___y_1412_ == 0)
{
v___y_1394_ = v___y_1409_;
v___y_1395_ = v___y_1415_;
v___y_1396_ = v___y_1410_;
v___y_1397_ = v___y_1411_;
v___y_1398_ = v___y_1414_;
v___y_1399_ = v___y_1413_;
goto v___jp_1393_;
}
else
{
uint64_t v___x_1418_; 
v___x_1418_ = 8388608ULL;
v___y_1394_ = v___y_1409_;
v___y_1395_ = v___y_1415_;
v___y_1396_ = v___y_1410_;
v___y_1397_ = v___y_1411_;
v___y_1398_ = v___y_1414_;
v___y_1399_ = v___x_1418_;
goto v___jp_1393_;
}
}
else
{
uint8_t v___x_1419_; 
v___x_1419_ = lean_unbox(v___y_1410_);
lean_dec(v___y_1410_);
if (v___x_1419_ == 0)
{
uint32_t v___x_1420_; 
v___x_1420_ = 2139095040;
return v___x_1420_;
}
else
{
uint32_t v___x_1421_; 
v___x_1421_ = 4286578688;
return v___x_1421_;
}
}
}
v___jp_1422_:
{
uint64_t v___x_1429_; uint8_t v_carry_1430_; 
v___x_1429_ = 16777216ULL;
v_carry_1430_ = lean_uint64_dec_eq(v___y_1428_, v___x_1429_);
if (v_carry_1430_ == 0)
{
v___y_1409_ = v___y_1424_;
v___y_1410_ = v___y_1425_;
v___y_1411_ = v___y_1426_;
v___y_1412_ = v_carry_1430_;
v___y_1413_ = v___y_1428_;
v___y_1414_ = v___y_1427_;
v___y_1415_ = v___y_1423_;
goto v___jp_1408_;
}
else
{
uint64_t v___x_1431_; uint64_t v___x_1432_; 
v___x_1431_ = 1ULL;
v___x_1432_ = lean_uint64_add(v___y_1423_, v___x_1431_);
v___y_1409_ = v___y_1424_;
v___y_1410_ = v___y_1425_;
v___y_1411_ = v___y_1426_;
v___y_1412_ = v_carry_1430_;
v___y_1413_ = v___y_1428_;
v___y_1414_ = v___y_1427_;
v___y_1415_ = v___x_1432_;
goto v___jp_1408_;
}
}
v___jp_1433_:
{
uint64_t v_position_1442_; uint64_t v___x_1443_; uint8_t v___x_1444_; 
v_position_1442_ = lean_uint64_add(v___y_1441_, v___y_1435_);
v___x_1443_ = 172ULL;
v___x_1444_ = lean_uint64_dec_lt(v_position_1442_, v___x_1443_);
if (v___x_1444_ == 0)
{
uint64_t v___x_1445_; uint8_t v___x_1446_; 
v___x_1445_ = 23ULL;
v___x_1446_ = lean_uint64_dec_lt(v___y_1441_, v___x_1445_);
if (v___x_1446_ == 0)
{
uint64_t v___x_1447_; uint8_t v___x_1448_; 
v___x_1447_ = lean_uint64_sub(v___y_1441_, v___x_1445_);
v___x_1448_ = lean_uint64_dec_eq(v___x_1447_, v___y_1434_);
if (v___x_1448_ == 0)
{
uint64_t v___x_1449_; uint8_t v___x_1450_; 
v___x_1449_ = 64ULL;
v___x_1450_ = lean_uint64_dec_lt(v___x_1447_, v___x_1449_);
if (v___x_1450_ == 0)
{
uint8_t v___x_1451_; 
v___x_1451_ = lean_uint64_dec_eq(v___x_1447_, v___x_1449_);
if (v___x_1451_ == 0)
{
lean_dec(v___y_1440_);
v___y_1423_ = v_position_1442_;
v___y_1424_ = v___y_1434_;
v___y_1425_ = v___y_1436_;
v___y_1426_ = v___y_1437_;
v___y_1427_ = v___y_1438_;
v___y_1428_ = v___y_1434_;
goto v___jp_1422_;
}
else
{
uint64_t v___x_1452_; uint64_t v___x_1453_; uint8_t v___x_1454_; 
v___x_1452_ = 9223372036854775808ULL;
v___x_1453_ = lean_unbox_uint64(v___y_1440_);
lean_dec(v___y_1440_);
v___x_1454_ = lean_uint64_dec_lt(v___x_1452_, v___x_1453_);
if (v___x_1454_ == 0)
{
v___y_1423_ = v_position_1442_;
v___y_1424_ = v___y_1434_;
v___y_1425_ = v___y_1436_;
v___y_1426_ = v___y_1437_;
v___y_1427_ = v___y_1438_;
v___y_1428_ = v___y_1434_;
goto v___jp_1422_;
}
else
{
uint64_t v___x_1455_; 
v___x_1455_ = 1ULL;
v___y_1423_ = v_position_1442_;
v___y_1424_ = v___y_1434_;
v___y_1425_ = v___y_1436_;
v___y_1426_ = v___y_1437_;
v___y_1427_ = v___y_1438_;
v___y_1428_ = v___x_1455_;
goto v___jp_1422_;
}
}
}
else
{
uint64_t v___x_1456_; uint64_t v_quotient_1457_; uint64_t v___x_1458_; uint64_t v___x_1459_; uint64_t v___x_1460_; uint64_t v___x_1461_; uint64_t v_remainder_1462_; uint64_t v___x_1463_; uint64_t v_half_1464_; uint8_t v___x_1465_; 
v___x_1456_ = lean_unbox_uint64(v___y_1440_);
v_quotient_1457_ = lean_uint64_shift_right(v___x_1456_, v___x_1447_);
v___x_1458_ = 1ULL;
v___x_1459_ = lean_uint64_shift_left(v___x_1458_, v___x_1447_);
v___x_1460_ = lean_uint64_sub(v___x_1459_, v___x_1458_);
v___x_1461_ = lean_unbox_uint64(v___y_1440_);
lean_dec(v___y_1440_);
v_remainder_1462_ = lean_uint64_land(v___x_1461_, v___x_1460_);
v___x_1463_ = lean_uint64_sub(v___x_1447_, v___x_1458_);
v_half_1464_ = lean_uint64_shift_left(v___x_1458_, v___x_1463_);
v___x_1465_ = lean_uint64_dec_lt(v_remainder_1462_, v_half_1464_);
if (v___x_1465_ == 0)
{
uint8_t v___x_1466_; 
v___x_1466_ = lean_uint64_dec_lt(v_half_1464_, v_remainder_1462_);
if (v___x_1466_ == 0)
{
uint64_t v___x_1467_; uint8_t v___x_1468_; 
v___x_1467_ = lean_uint64_land(v_quotient_1457_, v___x_1458_);
v___x_1468_ = lean_uint64_dec_eq(v___x_1467_, v___y_1434_);
if (v___x_1468_ == 0)
{
uint64_t v___x_1469_; 
v___x_1469_ = lean_uint64_add(v_quotient_1457_, v___x_1458_);
v___y_1423_ = v_position_1442_;
v___y_1424_ = v___y_1434_;
v___y_1425_ = v___y_1436_;
v___y_1426_ = v___y_1437_;
v___y_1427_ = v___y_1438_;
v___y_1428_ = v___x_1469_;
goto v___jp_1422_;
}
else
{
v___y_1423_ = v_position_1442_;
v___y_1424_ = v___y_1434_;
v___y_1425_ = v___y_1436_;
v___y_1426_ = v___y_1437_;
v___y_1427_ = v___y_1438_;
v___y_1428_ = v_quotient_1457_;
goto v___jp_1422_;
}
}
else
{
uint64_t v___x_1470_; 
v___x_1470_ = lean_uint64_add(v_quotient_1457_, v___x_1458_);
v___y_1423_ = v_position_1442_;
v___y_1424_ = v___y_1434_;
v___y_1425_ = v___y_1436_;
v___y_1426_ = v___y_1437_;
v___y_1427_ = v___y_1438_;
v___y_1428_ = v___x_1470_;
goto v___jp_1422_;
}
}
else
{
v___y_1423_ = v_position_1442_;
v___y_1424_ = v___y_1434_;
v___y_1425_ = v___y_1436_;
v___y_1426_ = v___y_1437_;
v___y_1427_ = v___y_1438_;
v___y_1428_ = v_quotient_1457_;
goto v___jp_1422_;
}
}
}
else
{
uint64_t v___x_1471_; 
v___x_1471_ = lean_unbox_uint64(v___y_1440_);
lean_dec(v___y_1440_);
v___y_1423_ = v_position_1442_;
v___y_1424_ = v___y_1434_;
v___y_1425_ = v___y_1436_;
v___y_1426_ = v___y_1437_;
v___y_1427_ = v___y_1438_;
v___y_1428_ = v___x_1471_;
goto v___jp_1422_;
}
}
else
{
uint64_t v___x_1472_; uint64_t v___x_1473_; uint64_t v___x_1474_; 
v___x_1472_ = lean_uint64_sub(v___x_1445_, v___y_1441_);
v___x_1473_ = lean_unbox_uint64(v___y_1440_);
lean_dec(v___y_1440_);
v___x_1474_ = lean_uint64_shift_left(v___x_1473_, v___x_1472_);
v___y_1423_ = v_position_1442_;
v___y_1424_ = v___y_1434_;
v___y_1425_ = v___y_1436_;
v___y_1426_ = v___y_1437_;
v___y_1427_ = v___y_1438_;
v___y_1428_ = v___x_1474_;
goto v___jp_1422_;
}
}
else
{
uint8_t v___x_1475_; 
v___x_1475_ = lean_uint64_dec_lt(v___y_1435_, v___y_1439_);
if (v___x_1475_ == 0)
{
uint64_t v___x_1476_; uint64_t v___x_1477_; uint64_t v___x_1478_; 
v___x_1476_ = lean_uint64_sub(v___y_1435_, v___y_1439_);
v___x_1477_ = lean_unbox_uint64(v___y_1440_);
lean_dec(v___y_1440_);
v___x_1478_ = lean_uint64_shift_left(v___x_1477_, v___x_1476_);
v___y_1356_ = v___y_1434_;
v___y_1357_ = v___y_1436_;
v___y_1358_ = v___x_1478_;
goto v___jp_1355_;
}
else
{
uint64_t v___x_1479_; uint8_t v___x_1480_; 
v___x_1479_ = lean_uint64_sub(v___y_1439_, v___y_1435_);
v___x_1480_ = lean_uint64_dec_eq(v___x_1479_, v___y_1434_);
if (v___x_1480_ == 0)
{
uint64_t v___x_1481_; uint8_t v___x_1482_; 
v___x_1481_ = 64ULL;
v___x_1482_ = lean_uint64_dec_lt(v___x_1479_, v___x_1481_);
if (v___x_1482_ == 0)
{
uint8_t v___x_1483_; 
v___x_1483_ = lean_uint64_dec_eq(v___x_1479_, v___x_1481_);
if (v___x_1483_ == 0)
{
lean_dec(v___y_1440_);
v___y_1356_ = v___y_1434_;
v___y_1357_ = v___y_1436_;
v___y_1358_ = v___y_1434_;
goto v___jp_1355_;
}
else
{
uint64_t v___x_1484_; uint64_t v___x_1485_; uint8_t v___x_1486_; 
v___x_1484_ = 9223372036854775808ULL;
v___x_1485_ = lean_unbox_uint64(v___y_1440_);
lean_dec(v___y_1440_);
v___x_1486_ = lean_uint64_dec_lt(v___x_1484_, v___x_1485_);
if (v___x_1486_ == 0)
{
v___y_1356_ = v___y_1434_;
v___y_1357_ = v___y_1436_;
v___y_1358_ = v___y_1434_;
goto v___jp_1355_;
}
else
{
uint64_t v___x_1487_; 
v___x_1487_ = 1ULL;
v___y_1356_ = v___y_1434_;
v___y_1357_ = v___y_1436_;
v___y_1358_ = v___x_1487_;
goto v___jp_1355_;
}
}
}
else
{
uint64_t v___x_1488_; uint64_t v_quotient_1489_; uint64_t v___x_1490_; uint64_t v___x_1491_; uint64_t v___x_1492_; uint64_t v___x_1493_; uint64_t v_remainder_1494_; uint64_t v___x_1495_; uint64_t v_half_1496_; uint8_t v___x_1497_; 
v___x_1488_ = lean_unbox_uint64(v___y_1440_);
v_quotient_1489_ = lean_uint64_shift_right(v___x_1488_, v___x_1479_);
v___x_1490_ = 1ULL;
v___x_1491_ = lean_uint64_shift_left(v___x_1490_, v___x_1479_);
v___x_1492_ = lean_uint64_sub(v___x_1491_, v___x_1490_);
v___x_1493_ = lean_unbox_uint64(v___y_1440_);
lean_dec(v___y_1440_);
v_remainder_1494_ = lean_uint64_land(v___x_1493_, v___x_1492_);
v___x_1495_ = lean_uint64_sub(v___x_1479_, v___x_1490_);
v_half_1496_ = lean_uint64_shift_left(v___x_1490_, v___x_1495_);
v___x_1497_ = lean_uint64_dec_lt(v_remainder_1494_, v_half_1496_);
if (v___x_1497_ == 0)
{
uint8_t v___x_1498_; 
v___x_1498_ = lean_uint64_dec_lt(v_half_1496_, v_remainder_1494_);
if (v___x_1498_ == 0)
{
uint64_t v___x_1499_; uint8_t v___x_1500_; 
v___x_1499_ = lean_uint64_land(v_quotient_1489_, v___x_1490_);
v___x_1500_ = lean_uint64_dec_eq(v___x_1499_, v___y_1434_);
if (v___x_1500_ == 0)
{
uint64_t v___x_1501_; 
v___x_1501_ = lean_uint64_add(v_quotient_1489_, v___x_1490_);
v___y_1356_ = v___y_1434_;
v___y_1357_ = v___y_1436_;
v___y_1358_ = v___x_1501_;
goto v___jp_1355_;
}
else
{
v___y_1356_ = v___y_1434_;
v___y_1357_ = v___y_1436_;
v___y_1358_ = v_quotient_1489_;
goto v___jp_1355_;
}
}
else
{
uint64_t v___x_1502_; 
v___x_1502_ = lean_uint64_add(v_quotient_1489_, v___x_1490_);
v___y_1356_ = v___y_1434_;
v___y_1357_ = v___y_1436_;
v___y_1358_ = v___x_1502_;
goto v___jp_1355_;
}
}
else
{
v___y_1356_ = v___y_1434_;
v___y_1357_ = v___y_1436_;
v___y_1358_ = v_quotient_1489_;
goto v___jp_1355_;
}
}
}
else
{
uint64_t v___x_1503_; 
v___x_1503_ = lean_unbox_uint64(v___y_1440_);
lean_dec(v___y_1440_);
v___y_1356_ = v___y_1434_;
v___y_1357_ = v___y_1436_;
v___y_1358_ = v___x_1503_;
goto v___jp_1355_;
}
}
}
}
v___jp_1504_:
{
uint64_t v___x_1514_; uint64_t v___x_1515_; uint8_t v___x_1516_; 
v___x_1514_ = 1ULL;
v___x_1515_ = lean_uint64_shift_right(v___y_1509_, v___x_1514_);
v___x_1516_ = lean_uint64_dec_eq(v___x_1515_, v___y_1505_);
if (v___x_1516_ == 0)
{
uint64_t v___x_1517_; 
v___x_1517_ = lean_uint64_add(v___y_1513_, v___x_1514_);
v___y_1434_ = v___y_1505_;
v___y_1435_ = v___y_1506_;
v___y_1436_ = v___y_1507_;
v___y_1437_ = v___y_1508_;
v___y_1438_ = v___y_1510_;
v___y_1439_ = v___y_1511_;
v___y_1440_ = v___y_1512_;
v___y_1441_ = v___x_1517_;
goto v___jp_1433_;
}
else
{
v___y_1434_ = v___y_1505_;
v___y_1435_ = v___y_1506_;
v___y_1436_ = v___y_1507_;
v___y_1437_ = v___y_1508_;
v___y_1438_ = v___y_1510_;
v___y_1439_ = v___y_1511_;
v___y_1440_ = v___y_1512_;
v___y_1441_ = v___y_1513_;
goto v___jp_1433_;
}
}
v___jp_1518_:
{
uint64_t v___x_1530_; uint8_t v___x_1531_; 
v___x_1530_ = lean_uint64_shift_right(v___y_1527_, v___y_1526_);
v___x_1531_ = lean_uint64_dec_eq(v___x_1530_, v___y_1519_);
if (v___x_1531_ == 0)
{
uint64_t v___x_1532_; 
v___x_1532_ = lean_uint64_add(v___y_1523_, v___y_1526_);
v___y_1505_ = v___y_1519_;
v___y_1506_ = v___y_1520_;
v___y_1507_ = v___y_1521_;
v___y_1508_ = v___y_1522_;
v___y_1509_ = v___y_1529_;
v___y_1510_ = v___y_1524_;
v___y_1511_ = v___y_1525_;
v___y_1512_ = v___y_1528_;
v___y_1513_ = v___x_1532_;
goto v___jp_1504_;
}
else
{
v___y_1505_ = v___y_1519_;
v___y_1506_ = v___y_1520_;
v___y_1507_ = v___y_1521_;
v___y_1508_ = v___y_1522_;
v___y_1509_ = v___y_1529_;
v___y_1510_ = v___y_1524_;
v___y_1511_ = v___y_1525_;
v___y_1512_ = v___y_1528_;
v___y_1513_ = v___y_1523_;
goto v___jp_1504_;
}
}
v___jp_1533_:
{
uint64_t v___x_1543_; uint64_t v___x_1544_; uint8_t v___x_1545_; 
v___x_1543_ = 2ULL;
v___x_1544_ = lean_uint64_shift_right(v___y_1541_, v___x_1543_);
v___x_1545_ = lean_uint64_dec_eq(v___x_1544_, v___y_1534_);
if (v___x_1545_ == 0)
{
v___y_1519_ = v___y_1534_;
v___y_1520_ = v___y_1535_;
v___y_1521_ = v___y_1536_;
v___y_1522_ = v___y_1537_;
v___y_1523_ = v___y_1542_;
v___y_1524_ = v___y_1538_;
v___y_1525_ = v___y_1539_;
v___y_1526_ = v___x_1543_;
v___y_1527_ = v___y_1541_;
v___y_1528_ = v___y_1540_;
v___y_1529_ = v___x_1544_;
goto v___jp_1518_;
}
else
{
v___y_1519_ = v___y_1534_;
v___y_1520_ = v___y_1535_;
v___y_1521_ = v___y_1536_;
v___y_1522_ = v___y_1537_;
v___y_1523_ = v___y_1542_;
v___y_1524_ = v___y_1538_;
v___y_1525_ = v___y_1539_;
v___y_1526_ = v___x_1543_;
v___y_1527_ = v___y_1541_;
v___y_1528_ = v___y_1540_;
v___y_1529_ = v___y_1541_;
goto v___jp_1518_;
}
}
v___jp_1546_:
{
uint64_t v___x_1558_; uint8_t v___x_1559_; 
v___x_1558_ = lean_uint64_shift_right(v___y_1555_, v___y_1554_);
v___x_1559_ = lean_uint64_dec_eq(v___x_1558_, v___y_1547_);
if (v___x_1559_ == 0)
{
uint64_t v___x_1560_; 
v___x_1560_ = lean_uint64_add(v___y_1551_, v___y_1554_);
v___y_1534_ = v___y_1547_;
v___y_1535_ = v___y_1548_;
v___y_1536_ = v___y_1549_;
v___y_1537_ = v___y_1550_;
v___y_1538_ = v___y_1552_;
v___y_1539_ = v___y_1553_;
v___y_1540_ = v___y_1556_;
v___y_1541_ = v___y_1557_;
v___y_1542_ = v___x_1560_;
goto v___jp_1533_;
}
else
{
v___y_1534_ = v___y_1547_;
v___y_1535_ = v___y_1548_;
v___y_1536_ = v___y_1549_;
v___y_1537_ = v___y_1550_;
v___y_1538_ = v___y_1552_;
v___y_1539_ = v___y_1553_;
v___y_1540_ = v___y_1556_;
v___y_1541_ = v___y_1557_;
v___y_1542_ = v___y_1551_;
goto v___jp_1533_;
}
}
v___jp_1561_:
{
uint64_t v___x_1571_; uint64_t v___x_1572_; uint8_t v___x_1573_; 
v___x_1571_ = 4ULL;
v___x_1572_ = lean_uint64_shift_right(v___y_1569_, v___x_1571_);
v___x_1573_ = lean_uint64_dec_eq(v___x_1572_, v___y_1562_);
if (v___x_1573_ == 0)
{
v___y_1547_ = v___y_1562_;
v___y_1548_ = v___y_1563_;
v___y_1549_ = v___y_1564_;
v___y_1550_ = v___y_1565_;
v___y_1551_ = v___y_1570_;
v___y_1552_ = v___y_1566_;
v___y_1553_ = v___y_1567_;
v___y_1554_ = v___x_1571_;
v___y_1555_ = v___y_1569_;
v___y_1556_ = v___y_1568_;
v___y_1557_ = v___x_1572_;
goto v___jp_1546_;
}
else
{
v___y_1547_ = v___y_1562_;
v___y_1548_ = v___y_1563_;
v___y_1549_ = v___y_1564_;
v___y_1550_ = v___y_1565_;
v___y_1551_ = v___y_1570_;
v___y_1552_ = v___y_1566_;
v___y_1553_ = v___y_1567_;
v___y_1554_ = v___x_1571_;
v___y_1555_ = v___y_1569_;
v___y_1556_ = v___y_1568_;
v___y_1557_ = v___y_1569_;
goto v___jp_1546_;
}
}
v___jp_1574_:
{
uint64_t v___x_1586_; uint8_t v___x_1587_; 
v___x_1586_ = lean_uint64_shift_right(v___y_1576_, v___y_1581_);
v___x_1587_ = lean_uint64_dec_eq(v___x_1586_, v___y_1575_);
if (v___x_1587_ == 0)
{
uint64_t v___x_1588_; 
v___x_1588_ = lean_uint64_add(v___y_1580_, v___y_1581_);
v___y_1562_ = v___y_1575_;
v___y_1563_ = v___y_1577_;
v___y_1564_ = v___y_1578_;
v___y_1565_ = v___y_1579_;
v___y_1566_ = v___y_1582_;
v___y_1567_ = v___y_1583_;
v___y_1568_ = v___y_1584_;
v___y_1569_ = v___y_1585_;
v___y_1570_ = v___x_1588_;
goto v___jp_1561_;
}
else
{
v___y_1562_ = v___y_1575_;
v___y_1563_ = v___y_1577_;
v___y_1564_ = v___y_1578_;
v___y_1565_ = v___y_1579_;
v___y_1566_ = v___y_1582_;
v___y_1567_ = v___y_1583_;
v___y_1568_ = v___y_1584_;
v___y_1569_ = v___y_1585_;
v___y_1570_ = v___y_1580_;
goto v___jp_1561_;
}
}
v___jp_1589_:
{
uint64_t v___x_1599_; uint64_t v___x_1600_; uint8_t v___x_1601_; 
v___x_1599_ = 8ULL;
v___x_1600_ = lean_uint64_shift_right(v___y_1592_, v___x_1599_);
v___x_1601_ = lean_uint64_dec_eq(v___x_1600_, v___y_1590_);
if (v___x_1601_ == 0)
{
v___y_1575_ = v___y_1590_;
v___y_1576_ = v___y_1592_;
v___y_1577_ = v___y_1591_;
v___y_1578_ = v___y_1593_;
v___y_1579_ = v___y_1594_;
v___y_1580_ = v___y_1598_;
v___y_1581_ = v___x_1599_;
v___y_1582_ = v___y_1595_;
v___y_1583_ = v___y_1596_;
v___y_1584_ = v___y_1597_;
v___y_1585_ = v___x_1600_;
goto v___jp_1574_;
}
else
{
v___y_1575_ = v___y_1590_;
v___y_1576_ = v___y_1592_;
v___y_1577_ = v___y_1591_;
v___y_1578_ = v___y_1593_;
v___y_1579_ = v___y_1594_;
v___y_1580_ = v___y_1598_;
v___y_1581_ = v___x_1599_;
v___y_1582_ = v___y_1595_;
v___y_1583_ = v___y_1596_;
v___y_1584_ = v___y_1597_;
v___y_1585_ = v___y_1592_;
goto v___jp_1574_;
}
}
v___jp_1602_:
{
uint64_t v___x_1614_; uint8_t v___x_1615_; 
v___x_1614_ = lean_uint64_shift_right(v___y_1609_, v___y_1605_);
v___x_1615_ = lean_uint64_dec_eq(v___x_1614_, v___y_1603_);
if (v___x_1615_ == 0)
{
uint64_t v___x_1616_; 
v___x_1616_ = lean_uint64_add(v___y_1604_, v___y_1605_);
v___y_1590_ = v___y_1603_;
v___y_1591_ = v___y_1606_;
v___y_1592_ = v___y_1613_;
v___y_1593_ = v___y_1607_;
v___y_1594_ = v___y_1608_;
v___y_1595_ = v___y_1610_;
v___y_1596_ = v___y_1611_;
v___y_1597_ = v___y_1612_;
v___y_1598_ = v___x_1616_;
goto v___jp_1589_;
}
else
{
v___y_1590_ = v___y_1603_;
v___y_1591_ = v___y_1606_;
v___y_1592_ = v___y_1613_;
v___y_1593_ = v___y_1607_;
v___y_1594_ = v___y_1608_;
v___y_1595_ = v___y_1610_;
v___y_1596_ = v___y_1611_;
v___y_1597_ = v___y_1612_;
v___y_1598_ = v___y_1604_;
goto v___jp_1589_;
}
}
v___jp_1617_:
{
uint64_t v___x_1627_; uint64_t v___x_1628_; uint8_t v___x_1629_; 
v___x_1627_ = 16ULL;
v___x_1628_ = lean_uint64_shift_right(v___y_1622_, v___x_1627_);
v___x_1629_ = lean_uint64_dec_eq(v___x_1628_, v___y_1618_);
if (v___x_1629_ == 0)
{
v___y_1603_ = v___y_1618_;
v___y_1604_ = v___y_1626_;
v___y_1605_ = v___x_1627_;
v___y_1606_ = v___y_1619_;
v___y_1607_ = v___y_1620_;
v___y_1608_ = v___y_1621_;
v___y_1609_ = v___y_1622_;
v___y_1610_ = v___y_1623_;
v___y_1611_ = v___y_1624_;
v___y_1612_ = v___y_1625_;
v___y_1613_ = v___x_1628_;
goto v___jp_1602_;
}
else
{
v___y_1603_ = v___y_1618_;
v___y_1604_ = v___y_1626_;
v___y_1605_ = v___x_1627_;
v___y_1606_ = v___y_1619_;
v___y_1607_ = v___y_1620_;
v___y_1608_ = v___y_1621_;
v___y_1609_ = v___y_1622_;
v___y_1610_ = v___y_1623_;
v___y_1611_ = v___y_1624_;
v___y_1612_ = v___y_1625_;
v___y_1613_ = v___y_1622_;
goto v___jp_1602_;
}
}
v___jp_1630_:
{
uint64_t v___x_1640_; uint64_t v___x_1641_; uint8_t v___x_1642_; 
v___x_1640_ = lean_unbox_uint64(v___y_1638_);
v___x_1641_ = lean_uint64_shift_right(v___x_1640_, v___y_1635_);
v___x_1642_ = lean_uint64_dec_eq(v___x_1641_, v___y_1631_);
if (v___x_1642_ == 0)
{
v___y_1618_ = v___y_1631_;
v___y_1619_ = v___y_1632_;
v___y_1620_ = v___y_1633_;
v___y_1621_ = v___y_1634_;
v___y_1622_ = v___y_1639_;
v___y_1623_ = v___y_1636_;
v___y_1624_ = v___y_1637_;
v___y_1625_ = v___y_1638_;
v___y_1626_ = v___y_1635_;
goto v___jp_1617_;
}
else
{
v___y_1618_ = v___y_1631_;
v___y_1619_ = v___y_1632_;
v___y_1620_ = v___y_1633_;
v___y_1621_ = v___y_1634_;
v___y_1622_ = v___y_1639_;
v___y_1623_ = v___y_1636_;
v___y_1624_ = v___y_1637_;
v___y_1625_ = v___y_1638_;
v___y_1626_ = v___y_1631_;
goto v___jp_1617_;
}
}
v___jp_1643_:
{
uint64_t v___x_1649_; uint64_t v___x_1650_; uint8_t v___x_1651_; 
v___x_1649_ = 0ULL;
v___x_1650_ = lean_unbox_uint64(v_snd_1648_);
v___x_1651_ = lean_uint64_dec_eq(v___x_1650_, v___x_1649_);
if (v___x_1651_ == 0)
{
uint64_t v___x_1652_; uint64_t v___x_1653_; uint64_t v___x_1654_; uint64_t v___x_1655_; uint64_t v___x_1656_; uint8_t v___x_1657_; 
v___x_1652_ = 149ULL;
v___x_1653_ = lean_uint64_add(v___y_1645_, v___x_1652_);
v___x_1654_ = 32ULL;
v___x_1655_ = lean_unbox_uint64(v_snd_1648_);
v___x_1656_ = lean_uint64_shift_right(v___x_1655_, v___x_1654_);
v___x_1657_ = lean_uint64_dec_eq(v___x_1656_, v___x_1649_);
if (v___x_1657_ == 0)
{
v___y_1631_ = v___x_1649_;
v___y_1632_ = v___x_1653_;
v___y_1633_ = v_fst_1647_;
v___y_1634_ = v___y_1644_;
v___y_1635_ = v___x_1654_;
v___y_1636_ = v___y_1646_;
v___y_1637_ = v___x_1652_;
v___y_1638_ = v_snd_1648_;
v___y_1639_ = v___x_1656_;
goto v___jp_1630_;
}
else
{
uint64_t v___x_1658_; 
v___x_1658_ = lean_unbox_uint64(v_snd_1648_);
v___y_1631_ = v___x_1649_;
v___y_1632_ = v___x_1653_;
v___y_1633_ = v_fst_1647_;
v___y_1634_ = v___y_1644_;
v___y_1635_ = v___x_1654_;
v___y_1636_ = v___y_1646_;
v___y_1637_ = v___x_1652_;
v___y_1638_ = v_snd_1648_;
v___y_1639_ = v___x_1658_;
goto v___jp_1630_;
}
}
else
{
uint8_t v___x_1659_; 
lean_dec(v_snd_1648_);
v___x_1659_ = lean_unbox(v_fst_1647_);
lean_dec(v_fst_1647_);
if (v___x_1659_ == 0)
{
uint32_t v___x_1660_; 
v___x_1660_ = 0;
return v___x_1660_;
}
else
{
uint32_t v___x_1661_; 
v___x_1661_ = 2147483648;
return v___x_1661_;
}
}
}
v___jp_1662_:
{
uint32_t v___x_1665_; uint32_t v___x_1666_; uint32_t v___x_1667_; 
v___x_1665_ = 8388607;
v___x_1666_ = lean_uint32_land(v___y_1663_, v___x_1665_);
v___x_1667_ = lean_uint32_lor(v___y_1664_, v___x_1666_);
return v___x_1667_;
}
v___jp_1668_:
{
uint8_t v___x_1672_; 
v___x_1672_ = lean_uint64_dec_eq(v___y_1671_, v___y_1670_);
if (v___x_1672_ == 0)
{
uint64_t v___x_1673_; uint8_t v___x_1674_; 
v___x_1673_ = 8388608ULL;
v___x_1674_ = lean_uint64_dec_eq(v___y_1671_, v___x_1673_);
if (v___x_1674_ == 0)
{
uint32_t v___x_1675_; uint8_t v___x_1676_; 
v___x_1675_ = lean_uint64_to_uint32(v___y_1671_);
v___x_1676_ = lean_unbox(v___y_1669_);
lean_dec(v___y_1669_);
if (v___x_1676_ == 0)
{
uint32_t v___x_1677_; 
v___x_1677_ = 0;
v___y_1663_ = v___x_1675_;
v___y_1664_ = v___x_1677_;
goto v___jp_1662_;
}
else
{
uint32_t v___x_1678_; 
v___x_1678_ = 2147483648;
v___y_1663_ = v___x_1675_;
v___y_1664_ = v___x_1678_;
goto v___jp_1662_;
}
}
else
{
uint8_t v___x_1679_; 
v___x_1679_ = lean_unbox(v___y_1669_);
lean_dec(v___y_1669_);
if (v___x_1679_ == 0)
{
uint32_t v___x_1680_; 
v___x_1680_ = 0;
v___y_1342_ = v___x_1680_;
goto v___jp_1341_;
}
else
{
uint32_t v___x_1681_; 
v___x_1681_ = 2147483648;
v___y_1342_ = v___x_1681_;
goto v___jp_1341_;
}
}
}
else
{
uint8_t v___x_1682_; 
v___x_1682_ = lean_unbox(v___y_1669_);
lean_dec(v___y_1669_);
if (v___x_1682_ == 0)
{
uint32_t v___x_1683_; 
v___x_1683_ = 0;
return v___x_1683_;
}
else
{
uint32_t v___x_1684_; 
v___x_1684_ = 2147483648;
return v___x_1684_;
}
}
}
v___jp_1685_:
{
uint32_t v___x_1691_; uint32_t v___x_1692_; uint32_t v___x_1693_; uint32_t v___x_1694_; uint32_t v___x_1695_; uint32_t v___x_1696_; 
v___x_1691_ = lean_uint32_land(v___y_1689_, v___y_1688_);
v___x_1692_ = lean_uint32_shift_left(v___x_1691_, v___y_1686_);
v___x_1693_ = lean_uint32_lor(v___y_1690_, v___x_1692_);
v___x_1694_ = 8388607;
v___x_1695_ = lean_uint32_land(v___y_1687_, v___x_1694_);
v___x_1696_ = lean_uint32_lor(v___x_1693_, v___x_1695_);
return v___x_1696_;
}
v___jp_1697_:
{
uint8_t v___x_1703_; 
v___x_1703_ = lean_unbox(v___y_1698_);
lean_dec(v___y_1698_);
if (v___x_1703_ == 0)
{
uint32_t v___x_1704_; 
v___x_1704_ = 0;
v___y_1686_ = v___y_1699_;
v___y_1687_ = v___y_1702_;
v___y_1688_ = v___y_1700_;
v___y_1689_ = v___y_1701_;
v___y_1690_ = v___x_1704_;
goto v___jp_1685_;
}
else
{
uint32_t v___x_1705_; 
v___x_1705_ = 2147483648;
v___y_1686_ = v___y_1699_;
v___y_1687_ = v___y_1702_;
v___y_1688_ = v___y_1700_;
v___y_1689_ = v___y_1701_;
v___y_1690_ = v___x_1705_;
goto v___jp_1685_;
}
}
v___jp_1706_:
{
uint64_t v___x_1713_; uint64_t v_encodedExponent_1714_; uint32_t v___x_1715_; uint64_t v___x_1716_; uint8_t v___x_1717_; 
v___x_1713_ = 171ULL;
v_encodedExponent_1714_ = lean_uint64_sub(v___y_1709_, v___x_1713_);
v___x_1715_ = lean_uint64_to_uint32(v_encodedExponent_1714_);
v___x_1716_ = 8388608ULL;
v___x_1717_ = lean_uint64_dec_lt(v___y_1712_, v___x_1716_);
if (v___x_1717_ == 0)
{
uint64_t v___x_1718_; uint32_t v___x_1719_; 
v___x_1718_ = lean_uint64_sub(v___y_1712_, v___x_1716_);
v___x_1719_ = lean_uint64_to_uint32(v___x_1718_);
v___y_1698_ = v___y_1707_;
v___y_1699_ = v___y_1708_;
v___y_1700_ = v___y_1710_;
v___y_1701_ = v___x_1715_;
v___y_1702_ = v___x_1719_;
goto v___jp_1697_;
}
else
{
uint32_t v___x_1720_; 
v___x_1720_ = lean_uint64_to_uint32(v___y_1711_);
v___y_1698_ = v___y_1707_;
v___y_1699_ = v___y_1708_;
v___y_1700_ = v___y_1710_;
v___y_1701_ = v___x_1715_;
v___y_1702_ = v___x_1720_;
goto v___jp_1697_;
}
}
v___jp_1721_:
{
uint64_t v___x_1729_; uint8_t v___x_1730_; 
v___x_1729_ = 425ULL;
v___x_1730_ = lean_uint64_dec_lt(v___x_1729_, v___y_1728_);
if (v___x_1730_ == 0)
{
if (v___y_1726_ == 0)
{
v___y_1707_ = v___y_1722_;
v___y_1708_ = v___y_1723_;
v___y_1709_ = v___y_1728_;
v___y_1710_ = v___y_1724_;
v___y_1711_ = v___y_1727_;
v___y_1712_ = v___y_1725_;
goto v___jp_1706_;
}
else
{
uint64_t v___x_1731_; 
v___x_1731_ = 8388608ULL;
v___y_1707_ = v___y_1722_;
v___y_1708_ = v___y_1723_;
v___y_1709_ = v___y_1728_;
v___y_1710_ = v___y_1724_;
v___y_1711_ = v___y_1727_;
v___y_1712_ = v___x_1731_;
goto v___jp_1706_;
}
}
else
{
uint8_t v___x_1732_; 
v___x_1732_ = lean_unbox(v___y_1722_);
lean_dec(v___y_1722_);
if (v___x_1732_ == 0)
{
uint32_t v___x_1733_; 
v___x_1733_ = 2139095040;
return v___x_1733_;
}
else
{
uint32_t v___x_1734_; 
v___x_1734_ = 4286578688;
return v___x_1734_;
}
}
}
v___jp_1735_:
{
uint64_t v___x_1742_; uint8_t v_carry_1743_; 
v___x_1742_ = 16777216ULL;
v_carry_1743_ = lean_uint64_dec_eq(v___y_1741_, v___x_1742_);
if (v_carry_1743_ == 0)
{
v___y_1722_ = v___y_1736_;
v___y_1723_ = v___y_1738_;
v___y_1724_ = v___y_1739_;
v___y_1725_ = v___y_1741_;
v___y_1726_ = v_carry_1743_;
v___y_1727_ = v___y_1740_;
v___y_1728_ = v___y_1737_;
goto v___jp_1721_;
}
else
{
uint64_t v___x_1744_; uint64_t v___x_1745_; 
v___x_1744_ = 1ULL;
v___x_1745_ = lean_uint64_add(v___y_1737_, v___x_1744_);
v___y_1722_ = v___y_1736_;
v___y_1723_ = v___y_1738_;
v___y_1724_ = v___y_1739_;
v___y_1725_ = v___y_1741_;
v___y_1726_ = v_carry_1743_;
v___y_1727_ = v___y_1740_;
v___y_1728_ = v___x_1745_;
goto v___jp_1721_;
}
}
v___jp_1746_:
{
uint64_t v_position_1755_; uint64_t v___x_1756_; uint8_t v___x_1757_; 
v_position_1755_ = lean_uint64_add(v___y_1754_, v___y_1752_);
v___x_1756_ = 172ULL;
v___x_1757_ = lean_uint64_dec_lt(v_position_1755_, v___x_1756_);
if (v___x_1757_ == 0)
{
uint64_t v___x_1758_; uint8_t v___x_1759_; 
v___x_1758_ = 23ULL;
v___x_1759_ = lean_uint64_dec_lt(v___y_1754_, v___x_1758_);
if (v___x_1759_ == 0)
{
uint64_t v___x_1760_; uint8_t v___x_1761_; 
v___x_1760_ = lean_uint64_sub(v___y_1754_, v___x_1758_);
v___x_1761_ = lean_uint64_dec_eq(v___x_1760_, v___y_1753_);
if (v___x_1761_ == 0)
{
uint64_t v___x_1762_; uint8_t v___x_1763_; 
v___x_1762_ = 64ULL;
v___x_1763_ = lean_uint64_dec_lt(v___x_1760_, v___x_1762_);
if (v___x_1763_ == 0)
{
uint8_t v___x_1764_; 
v___x_1764_ = lean_uint64_dec_eq(v___x_1760_, v___x_1762_);
if (v___x_1764_ == 0)
{
lean_dec(v___y_1747_);
v___y_1736_ = v___y_1748_;
v___y_1737_ = v_position_1755_;
v___y_1738_ = v___y_1749_;
v___y_1739_ = v___y_1751_;
v___y_1740_ = v___y_1753_;
v___y_1741_ = v___y_1753_;
goto v___jp_1735_;
}
else
{
uint64_t v___x_1765_; uint64_t v___x_1766_; uint8_t v___x_1767_; 
v___x_1765_ = 9223372036854775808ULL;
v___x_1766_ = lean_unbox_uint64(v___y_1747_);
lean_dec(v___y_1747_);
v___x_1767_ = lean_uint64_dec_lt(v___x_1765_, v___x_1766_);
if (v___x_1767_ == 0)
{
v___y_1736_ = v___y_1748_;
v___y_1737_ = v_position_1755_;
v___y_1738_ = v___y_1749_;
v___y_1739_ = v___y_1751_;
v___y_1740_ = v___y_1753_;
v___y_1741_ = v___y_1753_;
goto v___jp_1735_;
}
else
{
uint64_t v___x_1768_; 
v___x_1768_ = 1ULL;
v___y_1736_ = v___y_1748_;
v___y_1737_ = v_position_1755_;
v___y_1738_ = v___y_1749_;
v___y_1739_ = v___y_1751_;
v___y_1740_ = v___y_1753_;
v___y_1741_ = v___x_1768_;
goto v___jp_1735_;
}
}
}
else
{
uint64_t v___x_1769_; uint64_t v_quotient_1770_; uint64_t v___x_1771_; uint64_t v___x_1772_; uint64_t v___x_1773_; uint64_t v___x_1774_; uint64_t v_remainder_1775_; uint64_t v___x_1776_; uint64_t v_half_1777_; uint8_t v___x_1778_; 
v___x_1769_ = lean_unbox_uint64(v___y_1747_);
v_quotient_1770_ = lean_uint64_shift_right(v___x_1769_, v___x_1760_);
v___x_1771_ = 1ULL;
v___x_1772_ = lean_uint64_shift_left(v___x_1771_, v___x_1760_);
v___x_1773_ = lean_uint64_sub(v___x_1772_, v___x_1771_);
v___x_1774_ = lean_unbox_uint64(v___y_1747_);
lean_dec(v___y_1747_);
v_remainder_1775_ = lean_uint64_land(v___x_1774_, v___x_1773_);
v___x_1776_ = lean_uint64_sub(v___x_1760_, v___x_1771_);
v_half_1777_ = lean_uint64_shift_left(v___x_1771_, v___x_1776_);
v___x_1778_ = lean_uint64_dec_lt(v_remainder_1775_, v_half_1777_);
if (v___x_1778_ == 0)
{
uint8_t v___x_1779_; 
v___x_1779_ = lean_uint64_dec_lt(v_half_1777_, v_remainder_1775_);
if (v___x_1779_ == 0)
{
uint64_t v___x_1780_; uint8_t v___x_1781_; 
v___x_1780_ = lean_uint64_land(v_quotient_1770_, v___x_1771_);
v___x_1781_ = lean_uint64_dec_eq(v___x_1780_, v___y_1753_);
if (v___x_1781_ == 0)
{
uint64_t v___x_1782_; 
v___x_1782_ = lean_uint64_add(v_quotient_1770_, v___x_1771_);
v___y_1736_ = v___y_1748_;
v___y_1737_ = v_position_1755_;
v___y_1738_ = v___y_1749_;
v___y_1739_ = v___y_1751_;
v___y_1740_ = v___y_1753_;
v___y_1741_ = v___x_1782_;
goto v___jp_1735_;
}
else
{
v___y_1736_ = v___y_1748_;
v___y_1737_ = v_position_1755_;
v___y_1738_ = v___y_1749_;
v___y_1739_ = v___y_1751_;
v___y_1740_ = v___y_1753_;
v___y_1741_ = v_quotient_1770_;
goto v___jp_1735_;
}
}
else
{
uint64_t v___x_1783_; 
v___x_1783_ = lean_uint64_add(v_quotient_1770_, v___x_1771_);
v___y_1736_ = v___y_1748_;
v___y_1737_ = v_position_1755_;
v___y_1738_ = v___y_1749_;
v___y_1739_ = v___y_1751_;
v___y_1740_ = v___y_1753_;
v___y_1741_ = v___x_1783_;
goto v___jp_1735_;
}
}
else
{
v___y_1736_ = v___y_1748_;
v___y_1737_ = v_position_1755_;
v___y_1738_ = v___y_1749_;
v___y_1739_ = v___y_1751_;
v___y_1740_ = v___y_1753_;
v___y_1741_ = v_quotient_1770_;
goto v___jp_1735_;
}
}
}
else
{
uint64_t v___x_1784_; 
v___x_1784_ = lean_unbox_uint64(v___y_1747_);
lean_dec(v___y_1747_);
v___y_1736_ = v___y_1748_;
v___y_1737_ = v_position_1755_;
v___y_1738_ = v___y_1749_;
v___y_1739_ = v___y_1751_;
v___y_1740_ = v___y_1753_;
v___y_1741_ = v___x_1784_;
goto v___jp_1735_;
}
}
else
{
uint64_t v___x_1785_; uint64_t v___x_1786_; uint64_t v___x_1787_; 
v___x_1785_ = lean_uint64_sub(v___x_1758_, v___y_1754_);
v___x_1786_ = lean_unbox_uint64(v___y_1747_);
lean_dec(v___y_1747_);
v___x_1787_ = lean_uint64_shift_left(v___x_1786_, v___x_1785_);
v___y_1736_ = v___y_1748_;
v___y_1737_ = v_position_1755_;
v___y_1738_ = v___y_1749_;
v___y_1739_ = v___y_1751_;
v___y_1740_ = v___y_1753_;
v___y_1741_ = v___x_1787_;
goto v___jp_1735_;
}
}
else
{
uint8_t v___x_1788_; 
v___x_1788_ = lean_uint64_dec_lt(v___y_1752_, v___y_1750_);
if (v___x_1788_ == 0)
{
uint64_t v___x_1789_; uint64_t v___x_1790_; uint64_t v___x_1791_; 
v___x_1789_ = lean_uint64_sub(v___y_1752_, v___y_1750_);
v___x_1790_ = lean_unbox_uint64(v___y_1747_);
lean_dec(v___y_1747_);
v___x_1791_ = lean_uint64_shift_left(v___x_1790_, v___x_1789_);
v___y_1669_ = v___y_1748_;
v___y_1670_ = v___y_1753_;
v___y_1671_ = v___x_1791_;
goto v___jp_1668_;
}
else
{
uint64_t v___x_1792_; uint8_t v___x_1793_; 
v___x_1792_ = lean_uint64_sub(v___y_1750_, v___y_1752_);
v___x_1793_ = lean_uint64_dec_eq(v___x_1792_, v___y_1753_);
if (v___x_1793_ == 0)
{
uint64_t v___x_1794_; uint8_t v___x_1795_; 
v___x_1794_ = 64ULL;
v___x_1795_ = lean_uint64_dec_lt(v___x_1792_, v___x_1794_);
if (v___x_1795_ == 0)
{
uint8_t v___x_1796_; 
v___x_1796_ = lean_uint64_dec_eq(v___x_1792_, v___x_1794_);
if (v___x_1796_ == 0)
{
lean_dec(v___y_1747_);
v___y_1669_ = v___y_1748_;
v___y_1670_ = v___y_1753_;
v___y_1671_ = v___y_1753_;
goto v___jp_1668_;
}
else
{
uint64_t v___x_1797_; uint64_t v___x_1798_; uint8_t v___x_1799_; 
v___x_1797_ = 9223372036854775808ULL;
v___x_1798_ = lean_unbox_uint64(v___y_1747_);
lean_dec(v___y_1747_);
v___x_1799_ = lean_uint64_dec_lt(v___x_1797_, v___x_1798_);
if (v___x_1799_ == 0)
{
v___y_1669_ = v___y_1748_;
v___y_1670_ = v___y_1753_;
v___y_1671_ = v___y_1753_;
goto v___jp_1668_;
}
else
{
uint64_t v___x_1800_; 
v___x_1800_ = 1ULL;
v___y_1669_ = v___y_1748_;
v___y_1670_ = v___y_1753_;
v___y_1671_ = v___x_1800_;
goto v___jp_1668_;
}
}
}
else
{
uint64_t v___x_1801_; uint64_t v_quotient_1802_; uint64_t v___x_1803_; uint64_t v___x_1804_; uint64_t v___x_1805_; uint64_t v___x_1806_; uint64_t v_remainder_1807_; uint64_t v___x_1808_; uint64_t v_half_1809_; uint8_t v___x_1810_; 
v___x_1801_ = lean_unbox_uint64(v___y_1747_);
v_quotient_1802_ = lean_uint64_shift_right(v___x_1801_, v___x_1792_);
v___x_1803_ = 1ULL;
v___x_1804_ = lean_uint64_shift_left(v___x_1803_, v___x_1792_);
v___x_1805_ = lean_uint64_sub(v___x_1804_, v___x_1803_);
v___x_1806_ = lean_unbox_uint64(v___y_1747_);
lean_dec(v___y_1747_);
v_remainder_1807_ = lean_uint64_land(v___x_1806_, v___x_1805_);
v___x_1808_ = lean_uint64_sub(v___x_1792_, v___x_1803_);
v_half_1809_ = lean_uint64_shift_left(v___x_1803_, v___x_1808_);
v___x_1810_ = lean_uint64_dec_lt(v_remainder_1807_, v_half_1809_);
if (v___x_1810_ == 0)
{
uint8_t v___x_1811_; 
v___x_1811_ = lean_uint64_dec_lt(v_half_1809_, v_remainder_1807_);
if (v___x_1811_ == 0)
{
uint64_t v___x_1812_; uint8_t v___x_1813_; 
v___x_1812_ = lean_uint64_land(v_quotient_1802_, v___x_1803_);
v___x_1813_ = lean_uint64_dec_eq(v___x_1812_, v___y_1753_);
if (v___x_1813_ == 0)
{
uint64_t v___x_1814_; 
v___x_1814_ = lean_uint64_add(v_quotient_1802_, v___x_1803_);
v___y_1669_ = v___y_1748_;
v___y_1670_ = v___y_1753_;
v___y_1671_ = v___x_1814_;
goto v___jp_1668_;
}
else
{
v___y_1669_ = v___y_1748_;
v___y_1670_ = v___y_1753_;
v___y_1671_ = v_quotient_1802_;
goto v___jp_1668_;
}
}
else
{
uint64_t v___x_1815_; 
v___x_1815_ = lean_uint64_add(v_quotient_1802_, v___x_1803_);
v___y_1669_ = v___y_1748_;
v___y_1670_ = v___y_1753_;
v___y_1671_ = v___x_1815_;
goto v___jp_1668_;
}
}
else
{
v___y_1669_ = v___y_1748_;
v___y_1670_ = v___y_1753_;
v___y_1671_ = v_quotient_1802_;
goto v___jp_1668_;
}
}
}
else
{
uint64_t v___x_1816_; 
v___x_1816_ = lean_unbox_uint64(v___y_1747_);
lean_dec(v___y_1747_);
v___y_1669_ = v___y_1748_;
v___y_1670_ = v___y_1753_;
v___y_1671_ = v___x_1816_;
goto v___jp_1668_;
}
}
}
}
v___jp_1817_:
{
uint64_t v___x_1827_; uint64_t v___x_1828_; uint8_t v___x_1829_; 
v___x_1827_ = 1ULL;
v___x_1828_ = lean_uint64_shift_right(v___y_1819_, v___x_1827_);
v___x_1829_ = lean_uint64_dec_eq(v___x_1828_, v___y_1825_);
if (v___x_1829_ == 0)
{
uint64_t v___x_1830_; 
v___x_1830_ = lean_uint64_add(v___y_1826_, v___x_1827_);
v___y_1747_ = v___y_1818_;
v___y_1748_ = v___y_1820_;
v___y_1749_ = v___y_1821_;
v___y_1750_ = v___y_1822_;
v___y_1751_ = v___y_1824_;
v___y_1752_ = v___y_1823_;
v___y_1753_ = v___y_1825_;
v___y_1754_ = v___x_1830_;
goto v___jp_1746_;
}
else
{
v___y_1747_ = v___y_1818_;
v___y_1748_ = v___y_1820_;
v___y_1749_ = v___y_1821_;
v___y_1750_ = v___y_1822_;
v___y_1751_ = v___y_1824_;
v___y_1752_ = v___y_1823_;
v___y_1753_ = v___y_1825_;
v___y_1754_ = v___y_1826_;
goto v___jp_1746_;
}
}
v___jp_1831_:
{
uint64_t v___x_1843_; uint8_t v___x_1844_; 
v___x_1843_ = lean_uint64_shift_right(v___y_1835_, v___y_1839_);
v___x_1844_ = lean_uint64_dec_eq(v___x_1843_, v___y_1841_);
if (v___x_1844_ == 0)
{
uint64_t v___x_1845_; 
v___x_1845_ = lean_uint64_add(v___y_1840_, v___y_1839_);
v___y_1818_ = v___y_1832_;
v___y_1819_ = v___y_1842_;
v___y_1820_ = v___y_1833_;
v___y_1821_ = v___y_1834_;
v___y_1822_ = v___y_1836_;
v___y_1823_ = v___y_1838_;
v___y_1824_ = v___y_1837_;
v___y_1825_ = v___y_1841_;
v___y_1826_ = v___x_1845_;
goto v___jp_1817_;
}
else
{
v___y_1818_ = v___y_1832_;
v___y_1819_ = v___y_1842_;
v___y_1820_ = v___y_1833_;
v___y_1821_ = v___y_1834_;
v___y_1822_ = v___y_1836_;
v___y_1823_ = v___y_1838_;
v___y_1824_ = v___y_1837_;
v___y_1825_ = v___y_1841_;
v___y_1826_ = v___y_1840_;
goto v___jp_1817_;
}
}
v___jp_1846_:
{
uint64_t v___x_1856_; uint64_t v___x_1857_; uint8_t v___x_1858_; 
v___x_1856_ = 2ULL;
v___x_1857_ = lean_uint64_shift_right(v___y_1850_, v___x_1856_);
v___x_1858_ = lean_uint64_dec_eq(v___x_1857_, v___y_1854_);
if (v___x_1858_ == 0)
{
v___y_1832_ = v___y_1847_;
v___y_1833_ = v___y_1848_;
v___y_1834_ = v___y_1849_;
v___y_1835_ = v___y_1850_;
v___y_1836_ = v___y_1851_;
v___y_1837_ = v___y_1853_;
v___y_1838_ = v___y_1852_;
v___y_1839_ = v___x_1856_;
v___y_1840_ = v___y_1855_;
v___y_1841_ = v___y_1854_;
v___y_1842_ = v___x_1857_;
goto v___jp_1831_;
}
else
{
v___y_1832_ = v___y_1847_;
v___y_1833_ = v___y_1848_;
v___y_1834_ = v___y_1849_;
v___y_1835_ = v___y_1850_;
v___y_1836_ = v___y_1851_;
v___y_1837_ = v___y_1853_;
v___y_1838_ = v___y_1852_;
v___y_1839_ = v___x_1856_;
v___y_1840_ = v___y_1855_;
v___y_1841_ = v___y_1854_;
v___y_1842_ = v___y_1850_;
goto v___jp_1831_;
}
}
v___jp_1859_:
{
uint64_t v___x_1871_; uint8_t v___x_1872_; 
v___x_1871_ = lean_uint64_shift_right(v___y_1866_, v___y_1861_);
v___x_1872_ = lean_uint64_dec_eq(v___x_1871_, v___y_1869_);
if (v___x_1872_ == 0)
{
uint64_t v___x_1873_; 
v___x_1873_ = lean_uint64_add(v___y_1863_, v___y_1861_);
v___y_1847_ = v___y_1860_;
v___y_1848_ = v___y_1862_;
v___y_1849_ = v___y_1864_;
v___y_1850_ = v___y_1870_;
v___y_1851_ = v___y_1865_;
v___y_1852_ = v___y_1868_;
v___y_1853_ = v___y_1867_;
v___y_1854_ = v___y_1869_;
v___y_1855_ = v___x_1873_;
goto v___jp_1846_;
}
else
{
v___y_1847_ = v___y_1860_;
v___y_1848_ = v___y_1862_;
v___y_1849_ = v___y_1864_;
v___y_1850_ = v___y_1870_;
v___y_1851_ = v___y_1865_;
v___y_1852_ = v___y_1868_;
v___y_1853_ = v___y_1867_;
v___y_1854_ = v___y_1869_;
v___y_1855_ = v___y_1863_;
goto v___jp_1846_;
}
}
v___jp_1874_:
{
uint64_t v___x_1884_; uint64_t v___x_1885_; uint8_t v___x_1886_; 
v___x_1884_ = 4ULL;
v___x_1885_ = lean_uint64_shift_right(v___y_1879_, v___x_1884_);
v___x_1886_ = lean_uint64_dec_eq(v___x_1885_, v___y_1882_);
if (v___x_1886_ == 0)
{
v___y_1860_ = v___y_1875_;
v___y_1861_ = v___x_1884_;
v___y_1862_ = v___y_1876_;
v___y_1863_ = v___y_1883_;
v___y_1864_ = v___y_1877_;
v___y_1865_ = v___y_1878_;
v___y_1866_ = v___y_1879_;
v___y_1867_ = v___y_1881_;
v___y_1868_ = v___y_1880_;
v___y_1869_ = v___y_1882_;
v___y_1870_ = v___x_1885_;
goto v___jp_1859_;
}
else
{
v___y_1860_ = v___y_1875_;
v___y_1861_ = v___x_1884_;
v___y_1862_ = v___y_1876_;
v___y_1863_ = v___y_1883_;
v___y_1864_ = v___y_1877_;
v___y_1865_ = v___y_1878_;
v___y_1866_ = v___y_1879_;
v___y_1867_ = v___y_1881_;
v___y_1868_ = v___y_1880_;
v___y_1869_ = v___y_1882_;
v___y_1870_ = v___y_1879_;
goto v___jp_1859_;
}
}
v___jp_1887_:
{
uint64_t v___x_1899_; uint8_t v___x_1900_; 
v___x_1899_ = lean_uint64_shift_right(v___y_1896_, v___y_1895_);
v___x_1900_ = lean_uint64_dec_eq(v___x_1899_, v___y_1897_);
if (v___x_1900_ == 0)
{
uint64_t v___x_1901_; 
v___x_1901_ = lean_uint64_add(v___y_1894_, v___y_1895_);
v___y_1875_ = v___y_1888_;
v___y_1876_ = v___y_1889_;
v___y_1877_ = v___y_1890_;
v___y_1878_ = v___y_1891_;
v___y_1879_ = v___y_1898_;
v___y_1880_ = v___y_1893_;
v___y_1881_ = v___y_1892_;
v___y_1882_ = v___y_1897_;
v___y_1883_ = v___x_1901_;
goto v___jp_1874_;
}
else
{
v___y_1875_ = v___y_1888_;
v___y_1876_ = v___y_1889_;
v___y_1877_ = v___y_1890_;
v___y_1878_ = v___y_1891_;
v___y_1879_ = v___y_1898_;
v___y_1880_ = v___y_1893_;
v___y_1881_ = v___y_1892_;
v___y_1882_ = v___y_1897_;
v___y_1883_ = v___y_1894_;
goto v___jp_1874_;
}
}
v___jp_1902_:
{
uint64_t v___x_1912_; uint64_t v___x_1913_; uint8_t v___x_1914_; 
v___x_1912_ = 8ULL;
v___x_1913_ = lean_uint64_shift_right(v___y_1910_, v___x_1912_);
v___x_1914_ = lean_uint64_dec_eq(v___x_1913_, v___y_1909_);
if (v___x_1914_ == 0)
{
v___y_1888_ = v___y_1903_;
v___y_1889_ = v___y_1904_;
v___y_1890_ = v___y_1905_;
v___y_1891_ = v___y_1906_;
v___y_1892_ = v___y_1908_;
v___y_1893_ = v___y_1907_;
v___y_1894_ = v___y_1911_;
v___y_1895_ = v___x_1912_;
v___y_1896_ = v___y_1910_;
v___y_1897_ = v___y_1909_;
v___y_1898_ = v___x_1913_;
goto v___jp_1887_;
}
else
{
v___y_1888_ = v___y_1903_;
v___y_1889_ = v___y_1904_;
v___y_1890_ = v___y_1905_;
v___y_1891_ = v___y_1906_;
v___y_1892_ = v___y_1908_;
v___y_1893_ = v___y_1907_;
v___y_1894_ = v___y_1911_;
v___y_1895_ = v___x_1912_;
v___y_1896_ = v___y_1910_;
v___y_1897_ = v___y_1909_;
v___y_1898_ = v___y_1910_;
goto v___jp_1887_;
}
}
v___jp_1915_:
{
uint64_t v___x_1927_; uint8_t v___x_1928_; 
v___x_1927_ = lean_uint64_shift_right(v___y_1918_, v___y_1920_);
v___x_1928_ = lean_uint64_dec_eq(v___x_1927_, v___y_1925_);
if (v___x_1928_ == 0)
{
uint64_t v___x_1929_; 
v___x_1929_ = lean_uint64_add(v___y_1917_, v___y_1920_);
v___y_1903_ = v___y_1916_;
v___y_1904_ = v___y_1919_;
v___y_1905_ = v___y_1921_;
v___y_1906_ = v___y_1922_;
v___y_1907_ = v___y_1924_;
v___y_1908_ = v___y_1923_;
v___y_1909_ = v___y_1925_;
v___y_1910_ = v___y_1926_;
v___y_1911_ = v___x_1929_;
goto v___jp_1902_;
}
else
{
v___y_1903_ = v___y_1916_;
v___y_1904_ = v___y_1919_;
v___y_1905_ = v___y_1921_;
v___y_1906_ = v___y_1922_;
v___y_1907_ = v___y_1924_;
v___y_1908_ = v___y_1923_;
v___y_1909_ = v___y_1925_;
v___y_1910_ = v___y_1926_;
v___y_1911_ = v___y_1917_;
goto v___jp_1902_;
}
}
v___jp_1930_:
{
uint64_t v___x_1940_; uint64_t v___x_1941_; uint8_t v___x_1942_; 
v___x_1940_ = 16ULL;
v___x_1941_ = lean_uint64_shift_right(v___y_1932_, v___x_1940_);
v___x_1942_ = lean_uint64_dec_eq(v___x_1941_, v___y_1938_);
if (v___x_1942_ == 0)
{
v___y_1916_ = v___y_1931_;
v___y_1917_ = v___y_1939_;
v___y_1918_ = v___y_1932_;
v___y_1919_ = v___y_1933_;
v___y_1920_ = v___x_1940_;
v___y_1921_ = v___y_1934_;
v___y_1922_ = v___y_1935_;
v___y_1923_ = v___y_1937_;
v___y_1924_ = v___y_1936_;
v___y_1925_ = v___y_1938_;
v___y_1926_ = v___x_1941_;
goto v___jp_1915_;
}
else
{
v___y_1916_ = v___y_1931_;
v___y_1917_ = v___y_1939_;
v___y_1918_ = v___y_1932_;
v___y_1919_ = v___y_1933_;
v___y_1920_ = v___x_1940_;
v___y_1921_ = v___y_1934_;
v___y_1922_ = v___y_1935_;
v___y_1923_ = v___y_1937_;
v___y_1924_ = v___y_1936_;
v___y_1925_ = v___y_1938_;
v___y_1926_ = v___y_1932_;
goto v___jp_1915_;
}
}
v___jp_1943_:
{
uint64_t v___x_1953_; uint64_t v___x_1954_; uint8_t v___x_1955_; 
v___x_1953_ = lean_unbox_uint64(v___y_1944_);
v___x_1954_ = lean_uint64_shift_right(v___x_1953_, v___y_1950_);
v___x_1955_ = lean_uint64_dec_eq(v___x_1954_, v___y_1951_);
if (v___x_1955_ == 0)
{
v___y_1931_ = v___y_1944_;
v___y_1932_ = v___y_1952_;
v___y_1933_ = v___y_1945_;
v___y_1934_ = v___y_1946_;
v___y_1935_ = v___y_1947_;
v___y_1936_ = v___y_1949_;
v___y_1937_ = v___y_1948_;
v___y_1938_ = v___y_1951_;
v___y_1939_ = v___y_1950_;
goto v___jp_1930_;
}
else
{
v___y_1931_ = v___y_1944_;
v___y_1932_ = v___y_1952_;
v___y_1933_ = v___y_1945_;
v___y_1934_ = v___y_1946_;
v___y_1935_ = v___y_1947_;
v___y_1936_ = v___y_1949_;
v___y_1937_ = v___y_1948_;
v___y_1938_ = v___y_1951_;
v___y_1939_ = v___y_1951_;
goto v___jp_1930_;
}
}
v___jp_1956_:
{
uint64_t v___x_1962_; uint64_t v___x_1963_; uint8_t v___x_1964_; 
v___x_1962_ = 0ULL;
v___x_1963_ = lean_unbox_uint64(v_snd_1961_);
v___x_1964_ = lean_uint64_dec_eq(v___x_1963_, v___x_1962_);
if (v___x_1964_ == 0)
{
uint64_t v___x_1965_; uint64_t v___x_1966_; uint64_t v___x_1967_; uint64_t v___x_1968_; uint64_t v___x_1969_; uint8_t v___x_1970_; 
v___x_1965_ = 149ULL;
v___x_1966_ = lean_uint64_add(v___y_1957_, v___x_1965_);
v___x_1967_ = 32ULL;
v___x_1968_ = lean_unbox_uint64(v_snd_1961_);
v___x_1969_ = lean_uint64_shift_right(v___x_1968_, v___x_1967_);
v___x_1970_ = lean_uint64_dec_eq(v___x_1969_, v___x_1962_);
if (v___x_1970_ == 0)
{
v___y_1944_ = v_snd_1961_;
v___y_1945_ = v_fst_1960_;
v___y_1946_ = v___y_1958_;
v___y_1947_ = v___x_1965_;
v___y_1948_ = v___y_1959_;
v___y_1949_ = v___x_1966_;
v___y_1950_ = v___x_1967_;
v___y_1951_ = v___x_1962_;
v___y_1952_ = v___x_1969_;
goto v___jp_1943_;
}
else
{
uint64_t v___x_1971_; 
v___x_1971_ = lean_unbox_uint64(v_snd_1961_);
v___y_1944_ = v_snd_1961_;
v___y_1945_ = v_fst_1960_;
v___y_1946_ = v___y_1958_;
v___y_1947_ = v___x_1965_;
v___y_1948_ = v___y_1959_;
v___y_1949_ = v___x_1966_;
v___y_1950_ = v___x_1967_;
v___y_1951_ = v___x_1962_;
v___y_1952_ = v___x_1971_;
goto v___jp_1943_;
}
}
else
{
uint8_t v___x_1972_; 
lean_dec(v_snd_1961_);
v___x_1972_ = lean_unbox(v_fst_1960_);
lean_dec(v_fst_1960_);
if (v___x_1972_ == 0)
{
uint32_t v___x_1973_; 
v___x_1973_ = 0;
return v___x_1973_;
}
else
{
uint32_t v___x_1974_; 
v___x_1974_ = 2147483648;
return v___x_1974_;
}
}
}
v___jp_1975_:
{
uint8_t v___x_1984_; 
v___x_1984_ = lean_uint64_dec_eq(v___y_1977_, v___y_1979_);
if (v___x_1984_ == 0)
{
uint8_t v___x_1985_; 
v___x_1985_ = lean_uint64_dec_lt(v___y_1977_, v___y_1979_);
if (v___x_1985_ == 0)
{
uint64_t v___x_1986_; lean_object* v___x_1987_; lean_object* v___x_1988_; 
v___x_1986_ = lean_uint64_sub(v___y_1977_, v___y_1979_);
v___x_1987_ = lean_box(v___y_1982_);
v___x_1988_ = lean_box_uint64(v___x_1986_);
v___y_1957_ = v___y_1976_;
v___y_1958_ = v___y_1978_;
v___y_1959_ = v___y_1980_;
v_fst_1960_ = v___x_1987_;
v_snd_1961_ = v___x_1988_;
goto v___jp_1956_;
}
else
{
uint64_t v___x_1989_; lean_object* v___x_1990_; lean_object* v___x_1991_; 
v___x_1989_ = lean_uint64_sub(v___y_1979_, v___y_1977_);
v___x_1990_ = lean_box(v___y_1981_);
v___x_1991_ = lean_box_uint64(v___x_1989_);
v___y_1957_ = v___y_1976_;
v___y_1958_ = v___y_1978_;
v___y_1959_ = v___y_1980_;
v_fst_1960_ = v___x_1990_;
v_snd_1961_ = v___x_1991_;
goto v___jp_1956_;
}
}
else
{
lean_object* v___x_1992_; lean_object* v___x_1993_; 
v___x_1992_ = lean_box(v___y_1983_);
v___x_1993_ = ((lean_object*)(lp_competition_Submission_TunedAdd_core___boxed__const__1));
v___y_1957_ = v___y_1976_;
v___y_1958_ = v___y_1978_;
v___y_1959_ = v___y_1980_;
v_fst_1960_ = v___x_1992_;
v_snd_1961_ = v___x_1993_;
goto v___jp_1956_;
}
}
v___jp_1994_:
{
if (v___y_2002_ == 0)
{
v___y_1976_ = v___y_1995_;
v___y_1977_ = v___y_1996_;
v___y_1978_ = v___y_1998_;
v___y_1979_ = v___y_1997_;
v___y_1980_ = v___y_1999_;
v___y_1981_ = v___y_2000_;
v___y_1982_ = v___y_2001_;
v___y_1983_ = v___y_2002_;
goto v___jp_1975_;
}
else
{
uint64_t v___x_2003_; lean_object* v___x_2004_; lean_object* v___x_2005_; 
v___x_2003_ = lean_uint64_add(v___y_1996_, v___y_1997_);
v___x_2004_ = lean_box(v___y_2001_);
v___x_2005_ = lean_box_uint64(v___x_2003_);
v___y_1957_ = v___y_1995_;
v___y_1958_ = v___y_1998_;
v___y_1959_ = v___y_1999_;
v_fst_1960_ = v___x_2004_;
v_snd_1961_ = v___x_2005_;
goto v___jp_1956_;
}
}
v___jp_2006_:
{
uint8_t v___x_2015_; 
v___x_2015_ = lean_uint64_dec_eq(v___y_2013_, v___y_2009_);
if (v___x_2015_ == 0)
{
uint8_t v___x_2016_; 
v___x_2016_ = lean_uint64_dec_lt(v___y_2013_, v___y_2009_);
if (v___x_2016_ == 0)
{
uint64_t v___x_2017_; lean_object* v___x_2018_; lean_object* v___x_2019_; 
v___x_2017_ = lean_uint64_sub(v___y_2013_, v___y_2009_);
v___x_2018_ = lean_box(v___y_2012_);
v___x_2019_ = lean_box_uint64(v___x_2017_);
v___y_1644_ = v___y_2008_;
v___y_1645_ = v___y_2007_;
v___y_1646_ = v___y_2010_;
v_fst_1647_ = v___x_2018_;
v_snd_1648_ = v___x_2019_;
goto v___jp_1643_;
}
else
{
uint64_t v___x_2020_; lean_object* v___x_2021_; lean_object* v___x_2022_; 
v___x_2020_ = lean_uint64_sub(v___y_2009_, v___y_2013_);
v___x_2021_ = lean_box(v___y_2011_);
v___x_2022_ = lean_box_uint64(v___x_2020_);
v___y_1644_ = v___y_2008_;
v___y_1645_ = v___y_2007_;
v___y_1646_ = v___y_2010_;
v_fst_1647_ = v___x_2021_;
v_snd_1648_ = v___x_2022_;
goto v___jp_1643_;
}
}
else
{
lean_object* v___x_2023_; lean_object* v___x_2024_; 
v___x_2023_ = lean_box(v___y_2014_);
v___x_2024_ = ((lean_object*)(lp_competition_Submission_TunedAdd_core___boxed__const__1));
v___y_1644_ = v___y_2008_;
v___y_1645_ = v___y_2007_;
v___y_1646_ = v___y_2010_;
v_fst_1647_ = v___x_2023_;
v_snd_1648_ = v___x_2024_;
goto v___jp_1643_;
}
}
v___jp_2025_:
{
if (v___y_2033_ == 0)
{
v___y_2007_ = v___y_2027_;
v___y_2008_ = v___y_2026_;
v___y_2009_ = v___y_2028_;
v___y_2010_ = v___y_2029_;
v___y_2011_ = v___y_2030_;
v___y_2012_ = v___y_2031_;
v___y_2013_ = v___y_2032_;
v___y_2014_ = v___y_2033_;
goto v___jp_2006_;
}
else
{
uint64_t v___x_2034_; lean_object* v___x_2035_; lean_object* v___x_2036_; 
v___x_2034_ = lean_uint64_add(v___y_2032_, v___y_2028_);
v___x_2035_ = lean_box(v___y_2031_);
v___x_2036_ = lean_box_uint64(v___x_2034_);
v___y_1644_ = v___y_2026_;
v___y_1645_ = v___y_2027_;
v___y_1646_ = v___y_2029_;
v_fst_1647_ = v___x_2035_;
v_snd_1648_ = v___x_2036_;
goto v___jp_1643_;
}
}
v___jp_2037_:
{
uint8_t v___x_2046_; 
v___x_2046_ = lean_uint64_dec_le(v___y_2039_, v___y_2045_);
if (v___x_2046_ == 0)
{
uint64_t v_shift_2047_; uint64_t v___x_2048_; uint8_t v___x_2049_; 
v_shift_2047_ = lean_uint64_sub(v___y_2039_, v___y_2045_);
v___x_2048_ = 39ULL;
v___x_2049_ = lean_uint64_dec_le(v_shift_2047_, v___x_2048_);
if (v___x_2049_ == 0)
{
return v_x_1339_;
}
else
{
uint64_t v___x_2050_; 
v___x_2050_ = lean_uint64_shift_left(v___y_2044_, v_shift_2047_);
if (v___y_2043_ == 0)
{
if (v___y_2042_ == 0)
{
v___y_1995_ = v___y_2045_;
v___y_1996_ = v___x_2050_;
v___y_1997_ = v___y_2038_;
v___y_1998_ = v___y_2040_;
v___y_1999_ = v___y_2041_;
v___y_2000_ = v___y_2042_;
v___y_2001_ = v___y_2043_;
v___y_2002_ = v___x_2049_;
goto v___jp_1994_;
}
else
{
v___y_1976_ = v___y_2045_;
v___y_1977_ = v___x_2050_;
v___y_1978_ = v___y_2040_;
v___y_1979_ = v___y_2038_;
v___y_1980_ = v___y_2041_;
v___y_1981_ = v___y_2042_;
v___y_1982_ = v___y_2043_;
v___y_1983_ = v___y_2043_;
goto v___jp_1975_;
}
}
else
{
v___y_1995_ = v___y_2045_;
v___y_1996_ = v___x_2050_;
v___y_1997_ = v___y_2038_;
v___y_1998_ = v___y_2040_;
v___y_1999_ = v___y_2041_;
v___y_2000_ = v___y_2042_;
v___y_2001_ = v___y_2043_;
v___y_2002_ = v___y_2042_;
goto v___jp_1994_;
}
}
}
else
{
uint64_t v_shift_2051_; uint64_t v___x_2052_; uint8_t v___x_2053_; 
v_shift_2051_ = lean_uint64_sub(v___y_2045_, v___y_2039_);
v___x_2052_ = 39ULL;
v___x_2053_ = lean_uint64_dec_le(v_shift_2051_, v___x_2052_);
if (v___x_2053_ == 0)
{
return v_y_1340_;
}
else
{
uint64_t v___x_2054_; 
v___x_2054_ = lean_uint64_shift_left(v___y_2038_, v_shift_2051_);
if (v___y_2043_ == 0)
{
if (v___y_2042_ == 0)
{
v___y_2026_ = v___y_2040_;
v___y_2027_ = v___y_2039_;
v___y_2028_ = v___x_2054_;
v___y_2029_ = v___y_2041_;
v___y_2030_ = v___y_2042_;
v___y_2031_ = v___y_2043_;
v___y_2032_ = v___y_2044_;
v___y_2033_ = v___x_2053_;
goto v___jp_2025_;
}
else
{
v___y_2007_ = v___y_2039_;
v___y_2008_ = v___y_2040_;
v___y_2009_ = v___x_2054_;
v___y_2010_ = v___y_2041_;
v___y_2011_ = v___y_2042_;
v___y_2012_ = v___y_2043_;
v___y_2013_ = v___y_2044_;
v___y_2014_ = v___y_2043_;
goto v___jp_2006_;
}
}
else
{
v___y_2026_ = v___y_2040_;
v___y_2027_ = v___y_2039_;
v___y_2028_ = v___x_2054_;
v___y_2029_ = v___y_2041_;
v___y_2030_ = v___y_2042_;
v___y_2031_ = v___y_2043_;
v___y_2032_ = v___y_2044_;
v___y_2033_ = v___y_2042_;
goto v___jp_2025_;
}
}
}
}
v___jp_2055_:
{
uint64_t v___x_2064_; uint64_t v___x_2065_; uint8_t v___x_2066_; 
v___x_2064_ = lean_uint32_to_uint64(v___y_2058_);
v___x_2065_ = 0ULL;
v___x_2066_ = lean_uint64_dec_eq(v___x_2064_, v___x_2065_);
if (v___x_2066_ == 0)
{
uint64_t v___x_2067_; uint64_t v___x_2068_; 
v___x_2067_ = 1ULL;
v___x_2068_ = lean_uint64_sub(v___x_2064_, v___x_2067_);
v___y_2038_ = v___y_2056_;
v___y_2039_ = v___y_2063_;
v___y_2040_ = v___y_2057_;
v___y_2041_ = v___y_2059_;
v___y_2042_ = v___y_2060_;
v___y_2043_ = v___y_2061_;
v___y_2044_ = v___y_2062_;
v___y_2045_ = v___x_2068_;
goto v___jp_2037_;
}
else
{
v___y_2038_ = v___y_2056_;
v___y_2039_ = v___y_2063_;
v___y_2040_ = v___y_2057_;
v___y_2041_ = v___y_2059_;
v___y_2042_ = v___y_2060_;
v___y_2043_ = v___y_2061_;
v___y_2044_ = v___y_2062_;
v___y_2045_ = v___x_2065_;
goto v___jp_2037_;
}
}
v___jp_2069_:
{
uint64_t v___x_2078_; uint64_t v___x_2079_; uint8_t v___x_2080_; 
v___x_2078_ = lean_uint32_to_uint64(v___y_2075_);
v___x_2079_ = 0ULL;
v___x_2080_ = lean_uint64_dec_eq(v___x_2078_, v___x_2079_);
if (v___x_2080_ == 0)
{
uint64_t v___x_2081_; uint64_t v___x_2082_; 
v___x_2081_ = 1ULL;
v___x_2082_ = lean_uint64_sub(v___x_2078_, v___x_2081_);
v___y_2056_ = v___y_2077_;
v___y_2057_ = v___y_2070_;
v___y_2058_ = v___y_2071_;
v___y_2059_ = v___y_2072_;
v___y_2060_ = v___y_2073_;
v___y_2061_ = v___y_2074_;
v___y_2062_ = v___y_2076_;
v___y_2063_ = v___x_2082_;
goto v___jp_2055_;
}
else
{
v___y_2056_ = v___y_2077_;
v___y_2057_ = v___y_2070_;
v___y_2058_ = v___y_2071_;
v___y_2059_ = v___y_2072_;
v___y_2060_ = v___y_2073_;
v___y_2061_ = v___y_2074_;
v___y_2062_ = v___y_2076_;
v___y_2063_ = v___x_2079_;
goto v___jp_2055_;
}
}
v___jp_2083_:
{
uint32_t v___x_2091_; uint32_t v___x_2092_; uint32_t v___x_2093_; uint8_t v___x_2094_; 
v___x_2091_ = 8388607;
v___x_2092_ = lean_uint32_land(v_y_1340_, v___x_2091_);
v___x_2093_ = 0;
v___x_2094_ = lean_uint32_dec_eq(v___y_2085_, v___x_2093_);
if (v___x_2094_ == 0)
{
uint64_t v___x_2095_; uint64_t v___x_2096_; uint64_t v___x_2097_; 
v___x_2095_ = lean_uint32_to_uint64(v___x_2092_);
v___x_2096_ = 8388608ULL;
v___x_2097_ = lean_uint64_lor(v___x_2095_, v___x_2096_);
v___y_2070_ = v___y_2084_;
v___y_2071_ = v___y_2085_;
v___y_2072_ = v___y_2086_;
v___y_2073_ = v___y_2087_;
v___y_2074_ = v___y_2088_;
v___y_2075_ = v___y_2089_;
v___y_2076_ = v___y_2090_;
v___y_2077_ = v___x_2097_;
goto v___jp_2069_;
}
else
{
uint64_t v___x_2098_; 
v___x_2098_ = lean_uint32_to_uint64(v___x_2092_);
v___y_2070_ = v___y_2084_;
v___y_2071_ = v___y_2085_;
v___y_2072_ = v___y_2086_;
v___y_2073_ = v___y_2087_;
v___y_2074_ = v___y_2088_;
v___y_2075_ = v___y_2089_;
v___y_2076_ = v___y_2090_;
v___y_2077_ = v___x_2098_;
goto v___jp_2069_;
}
}
v___jp_2099_:
{
uint32_t v___x_2106_; uint32_t v___x_2107_; uint32_t v___x_2108_; uint8_t v___x_2109_; 
v___x_2106_ = 8388607;
v___x_2107_ = lean_uint32_land(v_x_1339_, v___x_2106_);
v___x_2108_ = 0;
v___x_2109_ = lean_uint32_dec_eq(v___y_2104_, v___x_2108_);
if (v___x_2109_ == 0)
{
uint64_t v___x_2110_; uint64_t v___x_2111_; uint64_t v___x_2112_; 
v___x_2110_ = lean_uint32_to_uint64(v___x_2107_);
v___x_2111_ = 8388608ULL;
v___x_2112_ = lean_uint64_lor(v___x_2110_, v___x_2111_);
v___y_2084_ = v___y_2100_;
v___y_2085_ = v___y_2101_;
v___y_2086_ = v___y_2102_;
v___y_2087_ = v___y_2105_;
v___y_2088_ = v___y_2103_;
v___y_2089_ = v___y_2104_;
v___y_2090_ = v___x_2112_;
goto v___jp_2083_;
}
else
{
uint64_t v___x_2113_; 
v___x_2113_ = lean_uint32_to_uint64(v___x_2107_);
v___y_2084_ = v___y_2100_;
v___y_2085_ = v___y_2101_;
v___y_2086_ = v___y_2102_;
v___y_2087_ = v___y_2105_;
v___y_2088_ = v___y_2103_;
v___y_2089_ = v___y_2104_;
v___y_2090_ = v___x_2113_;
goto v___jp_2083_;
}
}
v___jp_2114_:
{
uint32_t v___x_2121_; uint32_t v___x_2122_; uint32_t v___x_2123_; uint8_t v___x_2124_; 
v___x_2121_ = 2147483648;
v___x_2122_ = lean_uint32_land(v_y_1340_, v___x_2121_);
v___x_2123_ = 0;
v___x_2124_ = lean_uint32_dec_eq(v___x_2122_, v___x_2123_);
if (v___x_2124_ == 0)
{
uint8_t v___x_2125_; 
v___x_2125_ = 1;
v___y_2100_ = v___y_2116_;
v___y_2101_ = v___y_2117_;
v___y_2102_ = v___y_2118_;
v___y_2103_ = v___y_2120_;
v___y_2104_ = v___y_2119_;
v___y_2105_ = v___x_2125_;
goto v___jp_2099_;
}
else
{
v___y_2100_ = v___y_2116_;
v___y_2101_ = v___y_2117_;
v___y_2102_ = v___y_2118_;
v___y_2103_ = v___y_2120_;
v___y_2104_ = v___y_2119_;
v___y_2105_ = v___y_2115_;
goto v___jp_2099_;
}
}
v___jp_2126_:
{
if (v___y_2127_ == 0)
{
uint32_t v___x_2128_; uint32_t v___x_2129_; uint32_t v___x_2130_; uint32_t v_xExponent_2131_; uint32_t v___x_2132_; uint32_t v_yExponent_2133_; uint32_t v___x_2134_; uint32_t v___x_2135_; uint32_t v___x_2136_; uint8_t v___x_2137_; 
v___x_2128_ = 23;
v___x_2129_ = lean_uint32_shift_right(v_x_1339_, v___x_2128_);
v___x_2130_ = 255;
v_xExponent_2131_ = lean_uint32_land(v___x_2129_, v___x_2130_);
v___x_2132_ = lean_uint32_shift_right(v_y_1340_, v___x_2128_);
v_yExponent_2133_ = lean_uint32_land(v___x_2132_, v___x_2130_);
v___x_2134_ = 2147483648;
v___x_2135_ = lean_uint32_land(v_x_1339_, v___x_2134_);
v___x_2136_ = 0;
v___x_2137_ = lean_uint32_dec_eq(v___x_2135_, v___x_2136_);
if (v___x_2137_ == 0)
{
uint8_t v___x_2138_; 
v___x_2138_ = 1;
v___y_2115_ = v___y_2127_;
v___y_2116_ = v___x_2128_;
v___y_2117_ = v_yExponent_2133_;
v___y_2118_ = v___x_2130_;
v___y_2119_ = v_xExponent_2131_;
v___y_2120_ = v___x_2138_;
goto v___jp_2114_;
}
else
{
v___y_2115_ = v___y_2127_;
v___y_2116_ = v___x_2128_;
v___y_2117_ = v_yExponent_2133_;
v___y_2118_ = v___x_2130_;
v___y_2119_ = v_xExponent_2131_;
v___y_2120_ = v___y_2127_;
goto v___jp_2114_;
}
}
else
{
lean_object* v___x_2139_; lean_object* v___x_2140_; lean_object* v___x_2141_; uint32_t v___x_2142_; 
v___x_2139_ = lean_uint32_to_nat(v_x_1339_);
v___x_2140_ = lean_uint32_to_nat(v_y_1340_);
v___x_2141_ = lp_floatlib_FloatLib_Floats_Formats_BinaryInterchange_Model_AddBackend_word___at___00FloatLib_Floats_Formats_BinaryInterchange_Configured_Plan_softwareAdd32Certified_spec__1(v___x_2139_, v___x_2140_);
v___x_2142_ = lean_uint32_of_nat(v___x_2141_);
lean_dec(v___x_2141_);
return v___x_2142_;
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_TunedAdd_add___boxed(lean_object* v_x_2151_, lean_object* v_y_2152_){
_start:
{
uint32_t v_x_boxed_2153_; uint32_t v_y_boxed_2154_; uint32_t v_res_2155_; lean_object* v_r_2156_; 
v_x_boxed_2153_ = lean_unbox_uint32(v_x_2151_);
lean_dec(v_x_2151_);
v_y_boxed_2154_ = lean_unbox_uint32(v_y_2152_);
lean_dec(v_y_2152_);
v_res_2155_ = lp_competition_Submission_TunedAdd_add(v_x_boxed_2153_, v_y_boxed_2154_);
v_r_2156_ = lean_box_uint32(v_res_2155_);
return v_r_2156_;
}
}
static uint8_t _init_lp_competition_Submission_TunedAdd_Plan(void){
_start:
{
uint8_t v___x_2163_; 
v___x_2163_ = 2;
return v___x_2163_;
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_TunedAdd_dec(uint32_t v_z_2164_){
_start:
{
lean_object* v___x_2165_; 
v___x_2165_ = lean_uint32_to_nat(v_z_2164_);
return v___x_2165_;
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_TunedAdd_dec___boxed(lean_object* v_z_2166_){
_start:
{
uint32_t v_z_boxed_2167_; lean_object* v_res_2168_; 
v_z_boxed_2167_ = lean_unbox_uint32(v_z_2166_);
lean_dec(v_z_2166_);
v_res_2168_ = lp_competition_Submission_TunedAdd_dec(v_z_boxed_2167_);
return v_res_2168_;
}
}
LEAN_EXPORT uint64_t lp_competition_Submission_FastMul_sx(uint64_t v_k_2169_, uint64_t v_x_2170_){
_start:
{
uint64_t v___x_2171_; uint64_t v___x_2172_; uint8_t v___x_2173_; 
v___x_2171_ = lean_uint64_shift_right(v_x_2170_, v_k_2169_);
v___x_2172_ = 0ULL;
v___x_2173_ = lean_uint64_dec_eq(v___x_2171_, v___x_2172_);
if (v___x_2173_ == 0)
{
return v___x_2171_;
}
else
{
return v_x_2170_;
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_FastMul_sx___boxed(lean_object* v_k_2174_, lean_object* v_x_2175_){
_start:
{
uint64_t v_k_boxed_2176_; uint64_t v_x_boxed_2177_; uint64_t v_res_2178_; lean_object* v_r_2179_; 
v_k_boxed_2176_ = lean_unbox_uint64(v_k_2174_);
lean_dec_ref(v_k_2174_);
v_x_boxed_2177_ = lean_unbox_uint64(v_x_2175_);
lean_dec_ref(v_x_2175_);
v_res_2178_ = lp_competition_Submission_FastMul_sx(v_k_boxed_2176_, v_x_boxed_2177_);
v_r_2179_ = lean_box_uint64(v_res_2178_);
return v_r_2179_;
}
}
LEAN_EXPORT uint64_t lp_competition_Submission_FastMul_sr(uint64_t v_k_2180_, uint64_t v_x_2181_, uint64_t v_r_2182_){
_start:
{
uint64_t v___x_2183_; uint64_t v___x_2184_; uint8_t v___x_2185_; 
v___x_2183_ = lean_uint64_shift_right(v_x_2181_, v_k_2180_);
v___x_2184_ = 0ULL;
v___x_2185_ = lean_uint64_dec_eq(v___x_2183_, v___x_2184_);
if (v___x_2185_ == 0)
{
uint64_t v___x_2186_; 
v___x_2186_ = lean_uint64_add(v_r_2182_, v_k_2180_);
return v___x_2186_;
}
else
{
return v_r_2182_;
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_FastMul_sr___boxed(lean_object* v_k_2187_, lean_object* v_x_2188_, lean_object* v_r_2189_){
_start:
{
uint64_t v_k_boxed_2190_; uint64_t v_x_boxed_2191_; uint64_t v_r_boxed_2192_; uint64_t v_res_2193_; lean_object* v_r_2194_; 
v_k_boxed_2190_ = lean_unbox_uint64(v_k_2187_);
lean_dec_ref(v_k_2187_);
v_x_boxed_2191_ = lean_unbox_uint64(v_x_2188_);
lean_dec_ref(v_x_2188_);
v_r_boxed_2192_ = lean_unbox_uint64(v_r_2189_);
lean_dec_ref(v_r_2189_);
v_res_2193_ = lp_competition_Submission_FastMul_sr(v_k_boxed_2190_, v_x_boxed_2191_, v_r_boxed_2192_);
v_r_2194_ = lean_box_uint64(v_res_2193_);
return v_r_2194_;
}
}
LEAN_EXPORT uint64_t lp_competition_Submission_FastMul_fastLog2(uint64_t v_x0_2195_){
_start:
{
uint64_t v___y_2197_; uint64_t v___y_2198_; uint64_t v___y_2205_; uint64_t v___y_2206_; uint64_t v___y_2207_; uint64_t v___y_2208_; uint64_t v___y_2214_; uint64_t v___y_2215_; uint64_t v___y_2221_; uint64_t v___y_2222_; uint64_t v___y_2223_; uint64_t v___y_2224_; uint64_t v___y_2230_; uint64_t v___y_2231_; uint64_t v___y_2237_; uint64_t v___y_2238_; uint64_t v___y_2239_; uint64_t v___y_2240_; uint64_t v___y_2246_; uint64_t v___y_2247_; uint64_t v___y_2253_; uint64_t v___y_2254_; uint64_t v___y_2255_; uint64_t v___y_2256_; uint64_t v___y_2262_; uint64_t v___y_2263_; uint64_t v___x_2268_; uint64_t v___y_2270_; uint64_t v___x_2274_; uint64_t v___x_2275_; uint8_t v___x_2276_; 
v___x_2268_ = 32ULL;
v___x_2274_ = lean_uint64_shift_right(v_x0_2195_, v___x_2268_);
v___x_2275_ = 0ULL;
v___x_2276_ = lean_uint64_dec_eq(v___x_2274_, v___x_2275_);
if (v___x_2276_ == 0)
{
v___y_2270_ = v___x_2274_;
goto v___jp_2269_;
}
else
{
v___y_2270_ = v_x0_2195_;
goto v___jp_2269_;
}
v___jp_2196_:
{
uint64_t v___x_2199_; uint64_t v___x_2200_; uint64_t v___x_2201_; uint8_t v___x_2202_; 
v___x_2199_ = 1ULL;
v___x_2200_ = lean_uint64_shift_right(v___y_2197_, v___x_2199_);
v___x_2201_ = 0ULL;
v___x_2202_ = lean_uint64_dec_eq(v___x_2200_, v___x_2201_);
if (v___x_2202_ == 0)
{
uint64_t v___x_2203_; 
v___x_2203_ = lean_uint64_add(v___y_2198_, v___x_2199_);
return v___x_2203_;
}
else
{
return v___y_2198_;
}
}
v___jp_2204_:
{
uint64_t v___x_2209_; uint64_t v___x_2210_; uint8_t v___x_2211_; 
v___x_2209_ = lean_uint64_shift_right(v___y_2206_, v___y_2207_);
v___x_2210_ = 0ULL;
v___x_2211_ = lean_uint64_dec_eq(v___x_2209_, v___x_2210_);
if (v___x_2211_ == 0)
{
uint64_t v___x_2212_; 
v___x_2212_ = lean_uint64_add(v___y_2205_, v___y_2207_);
v___y_2197_ = v___y_2208_;
v___y_2198_ = v___x_2212_;
goto v___jp_2196_;
}
else
{
v___y_2197_ = v___y_2208_;
v___y_2198_ = v___y_2205_;
goto v___jp_2196_;
}
}
v___jp_2213_:
{
uint64_t v___x_2216_; uint64_t v___x_2217_; uint64_t v___x_2218_; uint8_t v___x_2219_; 
v___x_2216_ = 2ULL;
v___x_2217_ = lean_uint64_shift_right(v___y_2214_, v___x_2216_);
v___x_2218_ = 0ULL;
v___x_2219_ = lean_uint64_dec_eq(v___x_2217_, v___x_2218_);
if (v___x_2219_ == 0)
{
v___y_2205_ = v___y_2215_;
v___y_2206_ = v___y_2214_;
v___y_2207_ = v___x_2216_;
v___y_2208_ = v___x_2217_;
goto v___jp_2204_;
}
else
{
v___y_2205_ = v___y_2215_;
v___y_2206_ = v___y_2214_;
v___y_2207_ = v___x_2216_;
v___y_2208_ = v___y_2214_;
goto v___jp_2204_;
}
}
v___jp_2220_:
{
uint64_t v___x_2225_; uint64_t v___x_2226_; uint8_t v___x_2227_; 
v___x_2225_ = lean_uint64_shift_right(v___y_2222_, v___y_2223_);
v___x_2226_ = 0ULL;
v___x_2227_ = lean_uint64_dec_eq(v___x_2225_, v___x_2226_);
if (v___x_2227_ == 0)
{
uint64_t v___x_2228_; 
v___x_2228_ = lean_uint64_add(v___y_2221_, v___y_2223_);
v___y_2214_ = v___y_2224_;
v___y_2215_ = v___x_2228_;
goto v___jp_2213_;
}
else
{
v___y_2214_ = v___y_2224_;
v___y_2215_ = v___y_2221_;
goto v___jp_2213_;
}
}
v___jp_2229_:
{
uint64_t v___x_2232_; uint64_t v___x_2233_; uint64_t v___x_2234_; uint8_t v___x_2235_; 
v___x_2232_ = 4ULL;
v___x_2233_ = lean_uint64_shift_right(v___y_2230_, v___x_2232_);
v___x_2234_ = 0ULL;
v___x_2235_ = lean_uint64_dec_eq(v___x_2233_, v___x_2234_);
if (v___x_2235_ == 0)
{
v___y_2221_ = v___y_2231_;
v___y_2222_ = v___y_2230_;
v___y_2223_ = v___x_2232_;
v___y_2224_ = v___x_2233_;
goto v___jp_2220_;
}
else
{
v___y_2221_ = v___y_2231_;
v___y_2222_ = v___y_2230_;
v___y_2223_ = v___x_2232_;
v___y_2224_ = v___y_2230_;
goto v___jp_2220_;
}
}
v___jp_2236_:
{
uint64_t v___x_2241_; uint64_t v___x_2242_; uint8_t v___x_2243_; 
v___x_2241_ = lean_uint64_shift_right(v___y_2237_, v___y_2239_);
v___x_2242_ = 0ULL;
v___x_2243_ = lean_uint64_dec_eq(v___x_2241_, v___x_2242_);
if (v___x_2243_ == 0)
{
uint64_t v___x_2244_; 
v___x_2244_ = lean_uint64_add(v___y_2238_, v___y_2239_);
v___y_2230_ = v___y_2240_;
v___y_2231_ = v___x_2244_;
goto v___jp_2229_;
}
else
{
v___y_2230_ = v___y_2240_;
v___y_2231_ = v___y_2238_;
goto v___jp_2229_;
}
}
v___jp_2245_:
{
uint64_t v___x_2248_; uint64_t v___x_2249_; uint64_t v___x_2250_; uint8_t v___x_2251_; 
v___x_2248_ = 8ULL;
v___x_2249_ = lean_uint64_shift_right(v___y_2246_, v___x_2248_);
v___x_2250_ = 0ULL;
v___x_2251_ = lean_uint64_dec_eq(v___x_2249_, v___x_2250_);
if (v___x_2251_ == 0)
{
v___y_2237_ = v___y_2246_;
v___y_2238_ = v___y_2247_;
v___y_2239_ = v___x_2248_;
v___y_2240_ = v___x_2249_;
goto v___jp_2236_;
}
else
{
v___y_2237_ = v___y_2246_;
v___y_2238_ = v___y_2247_;
v___y_2239_ = v___x_2248_;
v___y_2240_ = v___y_2246_;
goto v___jp_2236_;
}
}
v___jp_2252_:
{
uint64_t v___x_2257_; uint64_t v___x_2258_; uint8_t v___x_2259_; 
v___x_2257_ = lean_uint64_shift_right(v___y_2253_, v___y_2254_);
v___x_2258_ = 0ULL;
v___x_2259_ = lean_uint64_dec_eq(v___x_2257_, v___x_2258_);
if (v___x_2259_ == 0)
{
uint64_t v___x_2260_; 
v___x_2260_ = lean_uint64_add(v___y_2255_, v___y_2254_);
v___y_2246_ = v___y_2256_;
v___y_2247_ = v___x_2260_;
goto v___jp_2245_;
}
else
{
v___y_2246_ = v___y_2256_;
v___y_2247_ = v___y_2255_;
goto v___jp_2245_;
}
}
v___jp_2261_:
{
uint64_t v___x_2264_; uint64_t v___x_2265_; uint64_t v___x_2266_; uint8_t v___x_2267_; 
v___x_2264_ = 16ULL;
v___x_2265_ = lean_uint64_shift_right(v___y_2262_, v___x_2264_);
v___x_2266_ = 0ULL;
v___x_2267_ = lean_uint64_dec_eq(v___x_2265_, v___x_2266_);
if (v___x_2267_ == 0)
{
v___y_2253_ = v___y_2262_;
v___y_2254_ = v___x_2264_;
v___y_2255_ = v___y_2263_;
v___y_2256_ = v___x_2265_;
goto v___jp_2252_;
}
else
{
v___y_2253_ = v___y_2262_;
v___y_2254_ = v___x_2264_;
v___y_2255_ = v___y_2263_;
v___y_2256_ = v___y_2262_;
goto v___jp_2252_;
}
}
v___jp_2269_:
{
uint64_t v___x_2271_; uint64_t v___x_2272_; uint8_t v___x_2273_; 
v___x_2271_ = lean_uint64_shift_right(v_x0_2195_, v___x_2268_);
v___x_2272_ = 0ULL;
v___x_2273_ = lean_uint64_dec_eq(v___x_2271_, v___x_2272_);
if (v___x_2273_ == 0)
{
v___y_2262_ = v___y_2270_;
v___y_2263_ = v___x_2268_;
goto v___jp_2261_;
}
else
{
v___y_2262_ = v___y_2270_;
v___y_2263_ = v___x_2272_;
goto v___jp_2261_;
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_FastMul_fastLog2___boxed(lean_object* v_x0_2277_){
_start:
{
uint64_t v_x0_boxed_2278_; uint64_t v_res_2279_; lean_object* v_r_2280_; 
v_x0_boxed_2278_ = lean_unbox_uint64(v_x0_2277_);
lean_dec_ref(v_x0_2277_);
v_res_2279_ = lp_competition_Submission_FastMul_fastLog2(v_x0_boxed_2278_);
v_r_2280_ = lean_box_uint64(v_res_2279_);
return v_r_2280_;
}
}
LEAN_EXPORT uint64_t lp_competition_Submission_FastMul_rse(uint64_t v_value_2281_, uint64_t v_shift_2282_){
_start:
{
uint64_t v_quotient_2283_; uint64_t v___x_2284_; uint64_t v___x_2285_; uint64_t v___x_2286_; uint64_t v_remainder_2287_; uint64_t v___x_2288_; uint64_t v_half_2289_; uint8_t v___x_2290_; 
v_quotient_2283_ = lean_uint64_shift_right(v_value_2281_, v_shift_2282_);
v___x_2284_ = 1ULL;
v___x_2285_ = lean_uint64_shift_left(v___x_2284_, v_shift_2282_);
v___x_2286_ = lean_uint64_sub(v___x_2285_, v___x_2284_);
v_remainder_2287_ = lean_uint64_land(v_value_2281_, v___x_2286_);
v___x_2288_ = lean_uint64_sub(v_shift_2282_, v___x_2284_);
v_half_2289_ = lean_uint64_shift_left(v___x_2284_, v___x_2288_);
v___x_2290_ = lean_uint64_dec_lt(v_remainder_2287_, v_half_2289_);
if (v___x_2290_ == 0)
{
uint8_t v___x_2291_; 
v___x_2291_ = lean_uint64_dec_lt(v_half_2289_, v_remainder_2287_);
if (v___x_2291_ == 0)
{
uint64_t v___x_2292_; uint64_t v___x_2293_; uint8_t v___x_2294_; 
v___x_2292_ = lean_uint64_land(v_quotient_2283_, v___x_2284_);
v___x_2293_ = 0ULL;
v___x_2294_ = lean_uint64_dec_eq(v___x_2292_, v___x_2293_);
if (v___x_2294_ == 0)
{
uint64_t v___x_2295_; 
v___x_2295_ = lean_uint64_add(v_quotient_2283_, v___x_2284_);
return v___x_2295_;
}
else
{
return v_quotient_2283_;
}
}
else
{
uint64_t v___x_2296_; 
v___x_2296_ = lean_uint64_add(v_quotient_2283_, v___x_2284_);
return v___x_2296_;
}
}
else
{
return v_quotient_2283_;
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_FastMul_rse___boxed(lean_object* v_value_2297_, lean_object* v_shift_2298_){
_start:
{
uint64_t v_value_boxed_2299_; uint64_t v_shift_boxed_2300_; uint64_t v_res_2301_; lean_object* v_r_2302_; 
v_value_boxed_2299_ = lean_unbox_uint64(v_value_2297_);
lean_dec_ref(v_value_2297_);
v_shift_boxed_2300_ = lean_unbox_uint64(v_shift_2298_);
lean_dec_ref(v_shift_2298_);
v_res_2301_ = lp_competition_Submission_FastMul_rse(v_value_boxed_2299_, v_shift_boxed_2300_);
v_r_2302_ = lean_box_uint64(v_res_2301_);
return v_r_2302_;
}
}
LEAN_EXPORT uint64_t lp_competition_Submission_FastMul_rseAny(uint64_t v_value_2303_, uint64_t v_shift_2304_){
_start:
{
uint64_t v___x_2305_; uint8_t v___x_2306_; 
v___x_2305_ = 0ULL;
v___x_2306_ = lean_uint64_dec_eq(v_shift_2304_, v___x_2305_);
if (v___x_2306_ == 0)
{
uint64_t v___x_2307_; uint8_t v___x_2308_; 
v___x_2307_ = 64ULL;
v___x_2308_ = lean_uint64_dec_lt(v_shift_2304_, v___x_2307_);
if (v___x_2308_ == 0)
{
uint8_t v___x_2309_; 
v___x_2309_ = lean_uint64_dec_eq(v_shift_2304_, v___x_2307_);
if (v___x_2309_ == 0)
{
return v___x_2305_;
}
else
{
uint64_t v___x_2310_; uint8_t v___x_2311_; 
v___x_2310_ = 9223372036854775808ULL;
v___x_2311_ = lean_uint64_dec_lt(v___x_2310_, v_value_2303_);
if (v___x_2311_ == 0)
{
return v___x_2305_;
}
else
{
uint64_t v___x_2312_; 
v___x_2312_ = 1ULL;
return v___x_2312_;
}
}
}
else
{
uint64_t v_quotient_2313_; uint64_t v___x_2314_; uint64_t v___x_2315_; uint64_t v___x_2316_; uint64_t v_remainder_2317_; uint64_t v___x_2318_; uint64_t v_half_2319_; uint8_t v___x_2320_; 
v_quotient_2313_ = lean_uint64_shift_right(v_value_2303_, v_shift_2304_);
v___x_2314_ = 1ULL;
v___x_2315_ = lean_uint64_shift_left(v___x_2314_, v_shift_2304_);
v___x_2316_ = lean_uint64_sub(v___x_2315_, v___x_2314_);
v_remainder_2317_ = lean_uint64_land(v_value_2303_, v___x_2316_);
v___x_2318_ = lean_uint64_sub(v_shift_2304_, v___x_2314_);
v_half_2319_ = lean_uint64_shift_left(v___x_2314_, v___x_2318_);
v___x_2320_ = lean_uint64_dec_lt(v_remainder_2317_, v_half_2319_);
if (v___x_2320_ == 0)
{
uint8_t v___x_2321_; 
v___x_2321_ = lean_uint64_dec_lt(v_half_2319_, v_remainder_2317_);
if (v___x_2321_ == 0)
{
uint64_t v___x_2322_; uint8_t v___x_2323_; 
v___x_2322_ = lean_uint64_land(v_quotient_2313_, v___x_2314_);
v___x_2323_ = lean_uint64_dec_eq(v___x_2322_, v___x_2305_);
if (v___x_2323_ == 0)
{
uint64_t v___x_2324_; 
v___x_2324_ = lean_uint64_add(v_quotient_2313_, v___x_2314_);
return v___x_2324_;
}
else
{
return v_quotient_2313_;
}
}
else
{
uint64_t v___x_2325_; 
v___x_2325_ = lean_uint64_add(v_quotient_2313_, v___x_2314_);
return v___x_2325_;
}
}
else
{
return v_quotient_2313_;
}
}
}
else
{
return v_value_2303_;
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_FastMul_rseAny___boxed(lean_object* v_value_2326_, lean_object* v_shift_2327_){
_start:
{
uint64_t v_value_boxed_2328_; uint64_t v_shift_boxed_2329_; uint64_t v_res_2330_; lean_object* v_r_2331_; 
v_value_boxed_2328_ = lean_unbox_uint64(v_value_2326_);
lean_dec_ref(v_value_2326_);
v_shift_boxed_2329_ = lean_unbox_uint64(v_shift_2327_);
lean_dec_ref(v_shift_2327_);
v_res_2330_ = lp_competition_Submission_FastMul_rseAny(v_value_boxed_2328_, v_shift_boxed_2329_);
v_r_2331_ = lean_box_uint64(v_res_2330_);
return v_r_2331_;
}
}
LEAN_EXPORT uint32_t lp_competition_Submission_FastMul_mkW(uint8_t v_sign_2332_, uint32_t v_e_2333_, uint32_t v_f_2334_){
_start:
{
uint32_t v___y_2336_; 
if (v_sign_2332_ == 0)
{
uint32_t v___x_2345_; 
v___x_2345_ = 0;
v___y_2336_ = v___x_2345_;
goto v___jp_2335_;
}
else
{
uint32_t v___x_2346_; 
v___x_2346_ = 2147483648;
v___y_2336_ = v___x_2346_;
goto v___jp_2335_;
}
v___jp_2335_:
{
uint32_t v___x_2337_; uint32_t v___x_2338_; uint32_t v___x_2339_; uint32_t v___x_2340_; uint32_t v___x_2341_; uint32_t v___x_2342_; uint32_t v___x_2343_; uint32_t v___x_2344_; 
v___x_2337_ = 255;
v___x_2338_ = lean_uint32_land(v_e_2333_, v___x_2337_);
v___x_2339_ = 23;
v___x_2340_ = lean_uint32_shift_left(v___x_2338_, v___x_2339_);
v___x_2341_ = lean_uint32_lor(v___y_2336_, v___x_2340_);
v___x_2342_ = 8388607;
v___x_2343_ = lean_uint32_land(v_f_2334_, v___x_2342_);
v___x_2344_ = lean_uint32_lor(v___x_2341_, v___x_2343_);
return v___x_2344_;
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_FastMul_mkW___boxed(lean_object* v_sign_2347_, lean_object* v_e_2348_, lean_object* v_f_2349_){
_start:
{
uint8_t v_sign_boxed_2350_; uint32_t v_e_boxed_2351_; uint32_t v_f_boxed_2352_; uint32_t v_res_2353_; lean_object* v_r_2354_; 
v_sign_boxed_2350_ = lean_unbox(v_sign_2347_);
v_e_boxed_2351_ = lean_unbox_uint32(v_e_2348_);
lean_dec(v_e_2348_);
v_f_boxed_2352_ = lean_unbox_uint32(v_f_2349_);
lean_dec(v_f_2349_);
v_res_2353_ = lp_competition_Submission_FastMul_mkW(v_sign_boxed_2350_, v_e_boxed_2351_, v_f_boxed_2352_);
v_r_2354_ = lean_box_uint32(v_res_2353_);
return v_r_2354_;
}
}
LEAN_EXPORT uint32_t lp_competition_Submission_FastMul_fracW(uint64_t v_n_2355_){
_start:
{
uint64_t v___x_2356_; uint8_t v___x_2357_; 
v___x_2356_ = 8388608ULL;
v___x_2357_ = lean_uint64_dec_lt(v_n_2355_, v___x_2356_);
if (v___x_2357_ == 0)
{
uint64_t v___x_2358_; uint32_t v___x_2359_; 
v___x_2358_ = lean_uint64_sub(v_n_2355_, v___x_2356_);
v___x_2359_ = lean_uint64_to_uint32(v___x_2358_);
return v___x_2359_;
}
else
{
uint32_t v___x_2360_; 
v___x_2360_ = lean_uint32_once(&lp_competition_Submission_TunedAdd_fracW___closed__0, &lp_competition_Submission_TunedAdd_fracW___closed__0_once, _init_lp_competition_Submission_TunedAdd_fracW___closed__0);
return v___x_2360_;
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_FastMul_fracW___boxed(lean_object* v_n_2361_){
_start:
{
uint64_t v_n_boxed_2362_; uint32_t v_res_2363_; lean_object* v_r_2364_; 
v_n_boxed_2362_ = lean_unbox_uint64(v_n_2361_);
lean_dec_ref(v_n_2361_);
v_res_2363_ = lp_competition_Submission_FastMul_fracW(v_n_boxed_2362_);
v_r_2364_ = lean_box_uint32(v_res_2363_);
return v_r_2364_;
}
}
LEAN_EXPORT uint32_t lp_competition_Submission_FastMul_roundP(uint8_t v_sign_2365_, uint64_t v_product_2366_, uint64_t v_scale_2367_){
_start:
{
uint32_t v___y_2369_; uint32_t v___y_2373_; uint32_t v___y_2374_; uint32_t v___y_2379_; uint32_t v___y_2380_; uint32_t v___y_2381_; uint32_t v___y_2391_; uint32_t v___y_2392_; uint64_t v___x_2395_; uint64_t v___y_2397_; uint64_t v___y_2409_; uint64_t v___y_2410_; uint8_t v___y_2420_; uint64_t v___y_2421_; uint64_t v___y_2422_; uint64_t v___y_2429_; uint64_t v___y_2430_; uint64_t v___y_2436_; uint64_t v___y_2491_; uint64_t v___y_2492_; uint64_t v___y_2498_; uint64_t v___y_2499_; uint64_t v___y_2500_; uint64_t v___y_2501_; uint64_t v___y_2506_; uint64_t v___y_2507_; uint64_t v___y_2512_; uint64_t v___y_2513_; uint64_t v___y_2514_; uint64_t v___y_2515_; uint64_t v___y_2520_; uint64_t v___y_2521_; uint64_t v___y_2526_; uint64_t v___y_2527_; uint64_t v___y_2528_; uint64_t v___y_2529_; uint64_t v___y_2534_; uint64_t v___y_2535_; uint64_t v___y_2540_; uint64_t v___y_2541_; uint64_t v___y_2542_; uint64_t v___y_2543_; uint64_t v___y_2548_; uint64_t v___y_2549_; uint8_t v___x_2553_; 
v___x_2395_ = 0ULL;
v___x_2553_ = lean_uint64_dec_eq(v_product_2366_, v___x_2395_);
if (v___x_2553_ == 0)
{
uint64_t v___x_2554_; uint64_t v___y_2556_; uint64_t v___x_2559_; uint8_t v___x_2560_; 
v___x_2554_ = 32ULL;
v___x_2559_ = lean_uint64_shift_right(v_product_2366_, v___x_2554_);
v___x_2560_ = lean_uint64_dec_eq(v___x_2559_, v___x_2395_);
if (v___x_2560_ == 0)
{
v___y_2556_ = v___x_2559_;
goto v___jp_2555_;
}
else
{
v___y_2556_ = v_product_2366_;
goto v___jp_2555_;
}
v___jp_2555_:
{
uint64_t v___x_2557_; uint8_t v___x_2558_; 
v___x_2557_ = lean_uint64_shift_right(v_product_2366_, v___x_2554_);
v___x_2558_ = lean_uint64_dec_eq(v___x_2557_, v___x_2395_);
if (v___x_2558_ == 0)
{
v___y_2548_ = v___y_2556_;
v___y_2549_ = v___x_2554_;
goto v___jp_2547_;
}
else
{
v___y_2548_ = v___y_2556_;
v___y_2549_ = v___x_2395_;
goto v___jp_2547_;
}
}
}
else
{
if (v_sign_2365_ == 0)
{
uint32_t v___x_2561_; 
v___x_2561_ = 0;
return v___x_2561_;
}
else
{
uint32_t v___x_2562_; 
v___x_2562_ = 2147483648;
return v___x_2562_;
}
}
v___jp_2368_:
{
uint32_t v___x_2370_; uint32_t v___x_2371_; 
v___x_2370_ = 8388608;
v___x_2371_ = lean_uint32_lor(v___y_2369_, v___x_2370_);
return v___x_2371_;
}
v___jp_2372_:
{
uint32_t v___x_2375_; uint32_t v___x_2376_; uint32_t v___x_2377_; 
v___x_2375_ = 8388607;
v___x_2376_ = lean_uint32_land(v___y_2373_, v___x_2375_);
v___x_2377_ = lean_uint32_lor(v___y_2374_, v___x_2376_);
return v___x_2377_;
}
v___jp_2378_:
{
uint32_t v___x_2382_; uint32_t v___x_2383_; uint32_t v___x_2384_; uint32_t v___x_2385_; uint32_t v___x_2386_; uint32_t v___x_2387_; uint32_t v___x_2388_; uint32_t v___x_2389_; 
v___x_2382_ = 255;
v___x_2383_ = lean_uint32_land(v___y_2379_, v___x_2382_);
v___x_2384_ = 23;
v___x_2385_ = lean_uint32_shift_left(v___x_2383_, v___x_2384_);
v___x_2386_ = lean_uint32_lor(v___y_2381_, v___x_2385_);
v___x_2387_ = 8388607;
v___x_2388_ = lean_uint32_land(v___y_2380_, v___x_2387_);
v___x_2389_ = lean_uint32_lor(v___x_2386_, v___x_2388_);
return v___x_2389_;
}
v___jp_2390_:
{
if (v_sign_2365_ == 0)
{
uint32_t v___x_2393_; 
v___x_2393_ = 0;
v___y_2379_ = v___y_2391_;
v___y_2380_ = v___y_2392_;
v___y_2381_ = v___x_2393_;
goto v___jp_2378_;
}
else
{
uint32_t v___x_2394_; 
v___x_2394_ = 2147483648;
v___y_2379_ = v___y_2391_;
v___y_2380_ = v___y_2392_;
v___y_2381_ = v___x_2394_;
goto v___jp_2378_;
}
}
v___jp_2396_:
{
uint8_t v___x_2398_; 
v___x_2398_ = lean_uint64_dec_eq(v___y_2397_, v___x_2395_);
if (v___x_2398_ == 0)
{
uint64_t v___x_2399_; uint8_t v___x_2400_; 
v___x_2399_ = 8388608ULL;
v___x_2400_ = lean_uint64_dec_eq(v___y_2397_, v___x_2399_);
if (v___x_2400_ == 0)
{
uint32_t v___x_2401_; 
v___x_2401_ = lean_uint64_to_uint32(v___y_2397_);
if (v_sign_2365_ == 0)
{
uint32_t v___x_2402_; 
v___x_2402_ = 0;
v___y_2373_ = v___x_2401_;
v___y_2374_ = v___x_2402_;
goto v___jp_2372_;
}
else
{
uint32_t v___x_2403_; 
v___x_2403_ = 2147483648;
v___y_2373_ = v___x_2401_;
v___y_2374_ = v___x_2403_;
goto v___jp_2372_;
}
}
else
{
if (v_sign_2365_ == 0)
{
uint32_t v___x_2404_; 
v___x_2404_ = 0;
v___y_2369_ = v___x_2404_;
goto v___jp_2368_;
}
else
{
uint32_t v___x_2405_; 
v___x_2405_ = 2147483648;
v___y_2369_ = v___x_2405_;
goto v___jp_2368_;
}
}
}
else
{
if (v_sign_2365_ == 0)
{
uint32_t v___x_2406_; 
v___x_2406_ = 0;
return v___x_2406_;
}
else
{
uint32_t v___x_2407_; 
v___x_2407_ = 2147483648;
return v___x_2407_;
}
}
}
v___jp_2408_:
{
uint64_t v___x_2411_; uint64_t v_encodedExponent_2412_; uint32_t v___x_2413_; uint64_t v___x_2414_; uint8_t v___x_2415_; 
v___x_2411_ = 171ULL;
v_encodedExponent_2412_ = lean_uint64_sub(v___y_2409_, v___x_2411_);
v___x_2413_ = lean_uint64_to_uint32(v_encodedExponent_2412_);
v___x_2414_ = 8388608ULL;
v___x_2415_ = lean_uint64_dec_lt(v___y_2410_, v___x_2414_);
if (v___x_2415_ == 0)
{
uint64_t v___x_2416_; uint32_t v___x_2417_; 
v___x_2416_ = lean_uint64_sub(v___y_2410_, v___x_2414_);
v___x_2417_ = lean_uint64_to_uint32(v___x_2416_);
v___y_2391_ = v___x_2413_;
v___y_2392_ = v___x_2417_;
goto v___jp_2390_;
}
else
{
uint32_t v___x_2418_; 
v___x_2418_ = lean_uint32_once(&lp_competition_Submission_TunedAdd_fracW___closed__0, &lp_competition_Submission_TunedAdd_fracW___closed__0_once, _init_lp_competition_Submission_TunedAdd_fracW___closed__0);
v___y_2391_ = v___x_2413_;
v___y_2392_ = v___x_2418_;
goto v___jp_2390_;
}
}
v___jp_2419_:
{
uint64_t v___x_2423_; uint8_t v___x_2424_; 
v___x_2423_ = 425ULL;
v___x_2424_ = lean_uint64_dec_lt(v___x_2423_, v___y_2422_);
if (v___x_2424_ == 0)
{
if (v___y_2420_ == 0)
{
v___y_2409_ = v___y_2422_;
v___y_2410_ = v___y_2421_;
goto v___jp_2408_;
}
else
{
uint64_t v___x_2425_; 
v___x_2425_ = 8388608ULL;
v___y_2409_ = v___y_2422_;
v___y_2410_ = v___x_2425_;
goto v___jp_2408_;
}
}
else
{
if (v_sign_2365_ == 0)
{
uint32_t v___x_2426_; 
v___x_2426_ = 2139095040;
return v___x_2426_;
}
else
{
uint32_t v___x_2427_; 
v___x_2427_ = 4286578688;
return v___x_2427_;
}
}
}
v___jp_2428_:
{
uint64_t v___x_2431_; uint8_t v_carry_2432_; 
v___x_2431_ = 16777216ULL;
v_carry_2432_ = lean_uint64_dec_eq(v___y_2430_, v___x_2431_);
if (v_carry_2432_ == 0)
{
v___y_2420_ = v_carry_2432_;
v___y_2421_ = v___y_2430_;
v___y_2422_ = v___y_2429_;
goto v___jp_2419_;
}
else
{
uint64_t v___x_2433_; uint64_t v___x_2434_; 
v___x_2433_ = 1ULL;
v___x_2434_ = lean_uint64_add(v___y_2429_, v___x_2433_);
v___y_2420_ = v_carry_2432_;
v___y_2421_ = v___y_2430_;
v___y_2422_ = v___x_2434_;
goto v___jp_2419_;
}
}
v___jp_2435_:
{
uint64_t v_position_2437_; uint64_t v___x_2438_; uint8_t v___x_2439_; 
v_position_2437_ = lean_uint64_add(v___y_2436_, v_scale_2367_);
v___x_2438_ = 172ULL;
v___x_2439_ = lean_uint64_dec_lt(v_position_2437_, v___x_2438_);
if (v___x_2439_ == 0)
{
uint64_t v___x_2440_; uint8_t v___x_2441_; 
v___x_2440_ = 23ULL;
v___x_2441_ = lean_uint64_dec_lt(v___y_2436_, v___x_2440_);
if (v___x_2441_ == 0)
{
uint64_t v___x_2442_; uint8_t v___x_2443_; 
v___x_2442_ = lean_uint64_sub(v___y_2436_, v___x_2440_);
v___x_2443_ = lean_uint64_dec_eq(v___x_2442_, v___x_2395_);
if (v___x_2443_ == 0)
{
uint64_t v___x_2444_; uint8_t v___x_2445_; 
v___x_2444_ = 64ULL;
v___x_2445_ = lean_uint64_dec_lt(v___x_2442_, v___x_2444_);
if (v___x_2445_ == 0)
{
uint8_t v___x_2446_; 
v___x_2446_ = lean_uint64_dec_eq(v___x_2442_, v___x_2444_);
if (v___x_2446_ == 0)
{
v___y_2429_ = v_position_2437_;
v___y_2430_ = v___x_2395_;
goto v___jp_2428_;
}
else
{
uint64_t v___x_2447_; uint8_t v___x_2448_; 
v___x_2447_ = 9223372036854775808ULL;
v___x_2448_ = lean_uint64_dec_lt(v___x_2447_, v_product_2366_);
if (v___x_2448_ == 0)
{
v___y_2429_ = v_position_2437_;
v___y_2430_ = v___x_2395_;
goto v___jp_2428_;
}
else
{
uint64_t v___x_2449_; 
v___x_2449_ = 1ULL;
v___y_2429_ = v_position_2437_;
v___y_2430_ = v___x_2449_;
goto v___jp_2428_;
}
}
}
else
{
uint64_t v_quotient_2450_; uint64_t v___x_2451_; uint64_t v___x_2452_; uint64_t v___x_2453_; uint64_t v_remainder_2454_; uint64_t v___x_2455_; uint64_t v_half_2456_; uint8_t v___x_2457_; 
v_quotient_2450_ = lean_uint64_shift_right(v_product_2366_, v___x_2442_);
v___x_2451_ = 1ULL;
v___x_2452_ = lean_uint64_shift_left(v___x_2451_, v___x_2442_);
v___x_2453_ = lean_uint64_sub(v___x_2452_, v___x_2451_);
v_remainder_2454_ = lean_uint64_land(v_product_2366_, v___x_2453_);
v___x_2455_ = lean_uint64_sub(v___x_2442_, v___x_2451_);
v_half_2456_ = lean_uint64_shift_left(v___x_2451_, v___x_2455_);
v___x_2457_ = lean_uint64_dec_lt(v_remainder_2454_, v_half_2456_);
if (v___x_2457_ == 0)
{
uint8_t v___x_2458_; 
v___x_2458_ = lean_uint64_dec_lt(v_half_2456_, v_remainder_2454_);
if (v___x_2458_ == 0)
{
uint64_t v___x_2459_; uint8_t v___x_2460_; 
v___x_2459_ = lean_uint64_land(v_quotient_2450_, v___x_2451_);
v___x_2460_ = lean_uint64_dec_eq(v___x_2459_, v___x_2395_);
if (v___x_2460_ == 0)
{
uint64_t v___x_2461_; 
v___x_2461_ = lean_uint64_add(v_quotient_2450_, v___x_2451_);
v___y_2429_ = v_position_2437_;
v___y_2430_ = v___x_2461_;
goto v___jp_2428_;
}
else
{
v___y_2429_ = v_position_2437_;
v___y_2430_ = v_quotient_2450_;
goto v___jp_2428_;
}
}
else
{
uint64_t v___x_2462_; 
v___x_2462_ = lean_uint64_add(v_quotient_2450_, v___x_2451_);
v___y_2429_ = v_position_2437_;
v___y_2430_ = v___x_2462_;
goto v___jp_2428_;
}
}
else
{
v___y_2429_ = v_position_2437_;
v___y_2430_ = v_quotient_2450_;
goto v___jp_2428_;
}
}
}
else
{
v___y_2429_ = v_position_2437_;
v___y_2430_ = v_product_2366_;
goto v___jp_2428_;
}
}
else
{
uint64_t v___x_2463_; uint64_t v___x_2464_; 
v___x_2463_ = lean_uint64_sub(v___x_2440_, v___y_2436_);
v___x_2464_ = lean_uint64_shift_left(v_product_2366_, v___x_2463_);
v___y_2429_ = v_position_2437_;
v___y_2430_ = v___x_2464_;
goto v___jp_2428_;
}
}
else
{
uint64_t v___x_2465_; uint8_t v___x_2466_; 
v___x_2465_ = 149ULL;
v___x_2466_ = lean_uint64_dec_lt(v_scale_2367_, v___x_2465_);
if (v___x_2466_ == 0)
{
uint64_t v___x_2467_; uint64_t v___x_2468_; 
v___x_2467_ = lean_uint64_sub(v_scale_2367_, v___x_2465_);
v___x_2468_ = lean_uint64_shift_left(v_product_2366_, v___x_2467_);
v___y_2397_ = v___x_2468_;
goto v___jp_2396_;
}
else
{
uint64_t v___x_2469_; uint8_t v___x_2470_; 
v___x_2469_ = lean_uint64_sub(v___x_2465_, v_scale_2367_);
v___x_2470_ = lean_uint64_dec_eq(v___x_2469_, v___x_2395_);
if (v___x_2470_ == 0)
{
uint64_t v___x_2471_; uint8_t v___x_2472_; 
v___x_2471_ = 64ULL;
v___x_2472_ = lean_uint64_dec_lt(v___x_2469_, v___x_2471_);
if (v___x_2472_ == 0)
{
uint8_t v___x_2473_; 
v___x_2473_ = lean_uint64_dec_eq(v___x_2469_, v___x_2471_);
if (v___x_2473_ == 0)
{
v___y_2397_ = v___x_2395_;
goto v___jp_2396_;
}
else
{
uint64_t v___x_2474_; uint8_t v___x_2475_; 
v___x_2474_ = 9223372036854775808ULL;
v___x_2475_ = lean_uint64_dec_lt(v___x_2474_, v_product_2366_);
if (v___x_2475_ == 0)
{
v___y_2397_ = v___x_2395_;
goto v___jp_2396_;
}
else
{
uint64_t v___x_2476_; 
v___x_2476_ = 1ULL;
v___y_2397_ = v___x_2476_;
goto v___jp_2396_;
}
}
}
else
{
uint64_t v_quotient_2477_; uint64_t v___x_2478_; uint64_t v___x_2479_; uint64_t v___x_2480_; uint64_t v_remainder_2481_; uint64_t v___x_2482_; uint64_t v_half_2483_; uint8_t v___x_2484_; 
v_quotient_2477_ = lean_uint64_shift_right(v_product_2366_, v___x_2469_);
v___x_2478_ = 1ULL;
v___x_2479_ = lean_uint64_shift_left(v___x_2478_, v___x_2469_);
v___x_2480_ = lean_uint64_sub(v___x_2479_, v___x_2478_);
v_remainder_2481_ = lean_uint64_land(v_product_2366_, v___x_2480_);
v___x_2482_ = lean_uint64_sub(v___x_2469_, v___x_2478_);
v_half_2483_ = lean_uint64_shift_left(v___x_2478_, v___x_2482_);
v___x_2484_ = lean_uint64_dec_lt(v_remainder_2481_, v_half_2483_);
if (v___x_2484_ == 0)
{
uint8_t v___x_2485_; 
v___x_2485_ = lean_uint64_dec_lt(v_half_2483_, v_remainder_2481_);
if (v___x_2485_ == 0)
{
uint64_t v___x_2486_; uint8_t v___x_2487_; 
v___x_2486_ = lean_uint64_land(v_quotient_2477_, v___x_2478_);
v___x_2487_ = lean_uint64_dec_eq(v___x_2486_, v___x_2395_);
if (v___x_2487_ == 0)
{
uint64_t v___x_2488_; 
v___x_2488_ = lean_uint64_add(v_quotient_2477_, v___x_2478_);
v___y_2397_ = v___x_2488_;
goto v___jp_2396_;
}
else
{
v___y_2397_ = v_quotient_2477_;
goto v___jp_2396_;
}
}
else
{
uint64_t v___x_2489_; 
v___x_2489_ = lean_uint64_add(v_quotient_2477_, v___x_2478_);
v___y_2397_ = v___x_2489_;
goto v___jp_2396_;
}
}
else
{
v___y_2397_ = v_quotient_2477_;
goto v___jp_2396_;
}
}
}
else
{
v___y_2397_ = v_product_2366_;
goto v___jp_2396_;
}
}
}
}
v___jp_2490_:
{
uint64_t v___x_2493_; uint64_t v___x_2494_; uint8_t v___x_2495_; 
v___x_2493_ = 1ULL;
v___x_2494_ = lean_uint64_shift_right(v___y_2491_, v___x_2493_);
v___x_2495_ = lean_uint64_dec_eq(v___x_2494_, v___x_2395_);
if (v___x_2495_ == 0)
{
uint64_t v___x_2496_; 
v___x_2496_ = lean_uint64_add(v___y_2492_, v___x_2493_);
v___y_2436_ = v___x_2496_;
goto v___jp_2435_;
}
else
{
v___y_2436_ = v___y_2492_;
goto v___jp_2435_;
}
}
v___jp_2497_:
{
uint64_t v___x_2502_; uint8_t v___x_2503_; 
v___x_2502_ = lean_uint64_shift_right(v___y_2500_, v___y_2498_);
v___x_2503_ = lean_uint64_dec_eq(v___x_2502_, v___x_2395_);
if (v___x_2503_ == 0)
{
uint64_t v___x_2504_; 
v___x_2504_ = lean_uint64_add(v___y_2499_, v___y_2498_);
v___y_2491_ = v___y_2501_;
v___y_2492_ = v___x_2504_;
goto v___jp_2490_;
}
else
{
v___y_2491_ = v___y_2501_;
v___y_2492_ = v___y_2499_;
goto v___jp_2490_;
}
}
v___jp_2505_:
{
uint64_t v___x_2508_; uint64_t v___x_2509_; uint8_t v___x_2510_; 
v___x_2508_ = 2ULL;
v___x_2509_ = lean_uint64_shift_right(v___y_2506_, v___x_2508_);
v___x_2510_ = lean_uint64_dec_eq(v___x_2509_, v___x_2395_);
if (v___x_2510_ == 0)
{
v___y_2498_ = v___x_2508_;
v___y_2499_ = v___y_2507_;
v___y_2500_ = v___y_2506_;
v___y_2501_ = v___x_2509_;
goto v___jp_2497_;
}
else
{
v___y_2498_ = v___x_2508_;
v___y_2499_ = v___y_2507_;
v___y_2500_ = v___y_2506_;
v___y_2501_ = v___y_2506_;
goto v___jp_2497_;
}
}
v___jp_2511_:
{
uint64_t v___x_2516_; uint8_t v___x_2517_; 
v___x_2516_ = lean_uint64_shift_right(v___y_2514_, v___y_2512_);
v___x_2517_ = lean_uint64_dec_eq(v___x_2516_, v___x_2395_);
if (v___x_2517_ == 0)
{
uint64_t v___x_2518_; 
v___x_2518_ = lean_uint64_add(v___y_2513_, v___y_2512_);
v___y_2506_ = v___y_2515_;
v___y_2507_ = v___x_2518_;
goto v___jp_2505_;
}
else
{
v___y_2506_ = v___y_2515_;
v___y_2507_ = v___y_2513_;
goto v___jp_2505_;
}
}
v___jp_2519_:
{
uint64_t v___x_2522_; uint64_t v___x_2523_; uint8_t v___x_2524_; 
v___x_2522_ = 4ULL;
v___x_2523_ = lean_uint64_shift_right(v___y_2520_, v___x_2522_);
v___x_2524_ = lean_uint64_dec_eq(v___x_2523_, v___x_2395_);
if (v___x_2524_ == 0)
{
v___y_2512_ = v___x_2522_;
v___y_2513_ = v___y_2521_;
v___y_2514_ = v___y_2520_;
v___y_2515_ = v___x_2523_;
goto v___jp_2511_;
}
else
{
v___y_2512_ = v___x_2522_;
v___y_2513_ = v___y_2521_;
v___y_2514_ = v___y_2520_;
v___y_2515_ = v___y_2520_;
goto v___jp_2511_;
}
}
v___jp_2525_:
{
uint64_t v___x_2530_; uint8_t v___x_2531_; 
v___x_2530_ = lean_uint64_shift_right(v___y_2526_, v___y_2527_);
v___x_2531_ = lean_uint64_dec_eq(v___x_2530_, v___x_2395_);
if (v___x_2531_ == 0)
{
uint64_t v___x_2532_; 
v___x_2532_ = lean_uint64_add(v___y_2528_, v___y_2527_);
v___y_2520_ = v___y_2529_;
v___y_2521_ = v___x_2532_;
goto v___jp_2519_;
}
else
{
v___y_2520_ = v___y_2529_;
v___y_2521_ = v___y_2528_;
goto v___jp_2519_;
}
}
v___jp_2533_:
{
uint64_t v___x_2536_; uint64_t v___x_2537_; uint8_t v___x_2538_; 
v___x_2536_ = 8ULL;
v___x_2537_ = lean_uint64_shift_right(v___y_2534_, v___x_2536_);
v___x_2538_ = lean_uint64_dec_eq(v___x_2537_, v___x_2395_);
if (v___x_2538_ == 0)
{
v___y_2526_ = v___y_2534_;
v___y_2527_ = v___x_2536_;
v___y_2528_ = v___y_2535_;
v___y_2529_ = v___x_2537_;
goto v___jp_2525_;
}
else
{
v___y_2526_ = v___y_2534_;
v___y_2527_ = v___x_2536_;
v___y_2528_ = v___y_2535_;
v___y_2529_ = v___y_2534_;
goto v___jp_2525_;
}
}
v___jp_2539_:
{
uint64_t v___x_2544_; uint8_t v___x_2545_; 
v___x_2544_ = lean_uint64_shift_right(v___y_2542_, v___y_2541_);
v___x_2545_ = lean_uint64_dec_eq(v___x_2544_, v___x_2395_);
if (v___x_2545_ == 0)
{
uint64_t v___x_2546_; 
v___x_2546_ = lean_uint64_add(v___y_2540_, v___y_2541_);
v___y_2534_ = v___y_2543_;
v___y_2535_ = v___x_2546_;
goto v___jp_2533_;
}
else
{
v___y_2534_ = v___y_2543_;
v___y_2535_ = v___y_2540_;
goto v___jp_2533_;
}
}
v___jp_2547_:
{
uint64_t v___x_2550_; uint64_t v___x_2551_; uint8_t v___x_2552_; 
v___x_2550_ = 16ULL;
v___x_2551_ = lean_uint64_shift_right(v___y_2548_, v___x_2550_);
v___x_2552_ = lean_uint64_dec_eq(v___x_2551_, v___x_2395_);
if (v___x_2552_ == 0)
{
v___y_2540_ = v___y_2549_;
v___y_2541_ = v___x_2550_;
v___y_2542_ = v___y_2548_;
v___y_2543_ = v___x_2551_;
goto v___jp_2539_;
}
else
{
v___y_2540_ = v___y_2549_;
v___y_2541_ = v___x_2550_;
v___y_2542_ = v___y_2548_;
v___y_2543_ = v___y_2548_;
goto v___jp_2539_;
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_FastMul_roundP___boxed(lean_object* v_sign_2563_, lean_object* v_product_2564_, lean_object* v_scale_2565_){
_start:
{
uint8_t v_sign_boxed_2566_; uint64_t v_product_boxed_2567_; uint64_t v_scale_boxed_2568_; uint32_t v_res_2569_; lean_object* v_r_2570_; 
v_sign_boxed_2566_ = lean_unbox(v_sign_2563_);
v_product_boxed_2567_ = lean_unbox_uint64(v_product_2564_);
lean_dec_ref(v_product_2564_);
v_scale_boxed_2568_ = lean_unbox_uint64(v_scale_2565_);
lean_dec_ref(v_scale_2565_);
v_res_2569_ = lp_competition_Submission_FastMul_roundP(v_sign_boxed_2566_, v_product_boxed_2567_, v_scale_boxed_2568_);
v_r_2570_ = lean_box_uint32(v_res_2569_);
return v_r_2570_;
}
}
LEAN_EXPORT uint32_t lp_competition_Submission_FastMul_core(uint32_t v_xBits_2571_, uint32_t v_yBits_2572_){
_start:
{
uint32_t v___y_2574_; uint32_t v___y_2578_; uint32_t v___y_2579_; uint32_t v___y_2580_; uint32_t v___y_2584_; uint64_t v___y_2585_; uint8_t v___y_2586_; uint64_t v___y_2587_; uint32_t v___x_2598_; uint32_t v___x_2599_; uint32_t v___x_2600_; uint32_t v___y_2602_; uint32_t v___y_2603_; uint32_t v___y_2604_; uint32_t v___y_2605_; uint32_t v___y_2612_; uint8_t v___y_2613_; uint32_t v___y_2614_; uint32_t v___y_2615_; uint32_t v___y_2619_; uint64_t v___y_2620_; uint8_t v___y_2621_; uint64_t v___y_2622_; uint64_t v___y_2623_; uint32_t v___y_2633_; uint64_t v___y_2634_; uint8_t v___y_2635_; uint64_t v___y_2636_; uint8_t v___y_2637_; uint64_t v___y_2638_; uint32_t v___y_2645_; uint64_t v___y_2646_; uint64_t v___y_2647_; uint8_t v___y_2648_; uint64_t v___y_2649_; uint64_t v___y_2655_; uint32_t v___y_2656_; uint64_t v___y_2657_; uint64_t v___y_2658_; uint8_t v___y_2659_; uint64_t v___y_2660_; uint64_t v___y_2715_; uint32_t v___y_2716_; uint64_t v___y_2717_; uint64_t v___y_2718_; uint64_t v___y_2719_; uint8_t v___y_2720_; uint64_t v___y_2721_; uint64_t v___y_2727_; uint32_t v___y_2728_; uint64_t v___y_2729_; uint64_t v___y_2730_; uint8_t v___y_2731_; uint64_t v___y_2732_; uint64_t v___y_2733_; uint64_t v___y_2734_; uint64_t v___y_2735_; uint32_t v___y_2740_; uint64_t v___y_2741_; uint64_t v___y_2742_; uint64_t v___y_2743_; uint8_t v___y_2744_; uint64_t v___y_2745_; uint64_t v___y_2746_; uint64_t v___y_2751_; uint64_t v___y_2752_; uint32_t v___y_2753_; uint64_t v___y_2754_; uint64_t v___y_2755_; uint64_t v___y_2756_; uint64_t v___y_2757_; uint8_t v___y_2758_; uint64_t v___y_2759_; uint32_t v___y_2764_; uint64_t v___y_2765_; uint64_t v___y_2766_; uint64_t v___y_2767_; uint64_t v___y_2768_; uint8_t v___y_2769_; uint64_t v___y_2770_; uint64_t v___y_2775_; uint32_t v___y_2776_; uint64_t v___y_2777_; uint64_t v___y_2778_; uint64_t v___y_2779_; uint64_t v___y_2780_; uint64_t v___y_2781_; uint8_t v___y_2782_; uint64_t v___y_2783_; uint32_t v___y_2788_; uint64_t v___y_2789_; uint64_t v___y_2790_; uint64_t v___y_2791_; uint64_t v___y_2792_; uint8_t v___y_2793_; uint64_t v___y_2794_; uint64_t v___y_2799_; uint32_t v___y_2800_; uint64_t v___y_2801_; uint64_t v___y_2802_; uint64_t v___y_2803_; uint64_t v___y_2804_; uint8_t v___y_2805_; uint64_t v___y_2806_; uint64_t v___y_2807_; uint32_t v___y_2812_; uint64_t v___y_2813_; uint64_t v___y_2814_; uint64_t v___y_2815_; uint8_t v___y_2816_; uint64_t v___y_2817_; uint64_t v___y_2818_; uint64_t v___y_2823_; uint32_t v___y_2824_; uint64_t v___y_2825_; uint64_t v___y_2826_; uint64_t v___y_2827_; uint8_t v___y_2828_; uint64_t v___y_2829_; uint32_t v___y_2833_; uint64_t v___y_2834_; uint64_t v___y_2835_; uint64_t v___y_2836_; uint8_t v___y_2837_; uint64_t v___y_2838_; uint32_t v_xExponent_2848_; uint32_t v___x_2849_; uint32_t v_yExponent_2850_; uint32_t v___y_2852_; uint64_t v___y_2853_; uint64_t v___y_2854_; uint8_t v___y_2855_; uint64_t v___y_2856_; uint32_t v___y_2863_; uint64_t v___y_2864_; uint8_t v___y_2865_; uint64_t v___y_2866_; uint32_t v___y_2873_; uint32_t v___y_2874_; uint8_t v___y_2875_; uint64_t v___y_2876_; uint8_t v___y_2884_; uint8_t v___y_2899_; uint8_t v___y_2900_; uint8_t v___y_2902_; uint32_t v___x_2909_; uint32_t v___x_2910_; uint32_t v___x_2911_; uint8_t v___x_2912_; 
v___x_2598_ = 23;
v___x_2599_ = lean_uint32_shift_right(v_xBits_2571_, v___x_2598_);
v___x_2600_ = 255;
v_xExponent_2848_ = lean_uint32_land(v___x_2599_, v___x_2600_);
v___x_2849_ = lean_uint32_shift_right(v_yBits_2572_, v___x_2598_);
v_yExponent_2850_ = lean_uint32_land(v___x_2849_, v___x_2600_);
v___x_2909_ = 2147483648;
v___x_2910_ = lean_uint32_land(v_xBits_2571_, v___x_2909_);
v___x_2911_ = 0;
v___x_2912_ = lean_uint32_dec_eq(v___x_2910_, v___x_2911_);
if (v___x_2912_ == 0)
{
uint8_t v___x_2913_; 
v___x_2913_ = 1;
v___y_2902_ = v___x_2913_;
goto v___jp_2901_;
}
else
{
uint8_t v___x_2914_; 
v___x_2914_ = 0;
v___y_2902_ = v___x_2914_;
goto v___jp_2901_;
}
v___jp_2573_:
{
uint32_t v___x_2575_; uint32_t v___x_2576_; 
v___x_2575_ = 8388608;
v___x_2576_ = lean_uint32_lor(v___y_2574_, v___x_2575_);
return v___x_2576_;
}
v___jp_2577_:
{
uint32_t v___x_2581_; uint32_t v___x_2582_; 
v___x_2581_ = lean_uint32_land(v___y_2579_, v___y_2578_);
v___x_2582_ = lean_uint32_lor(v___y_2580_, v___x_2581_);
return v___x_2582_;
}
v___jp_2583_:
{
uint8_t v___x_2588_; 
v___x_2588_ = lean_uint64_dec_eq(v___y_2587_, v___y_2585_);
if (v___x_2588_ == 0)
{
uint64_t v___x_2589_; uint8_t v___x_2590_; 
v___x_2589_ = 8388608ULL;
v___x_2590_ = lean_uint64_dec_eq(v___y_2587_, v___x_2589_);
if (v___x_2590_ == 0)
{
uint32_t v___x_2591_; 
v___x_2591_ = lean_uint64_to_uint32(v___y_2587_);
if (v___y_2586_ == 0)
{
uint32_t v___x_2592_; 
v___x_2592_ = 0;
v___y_2578_ = v___y_2584_;
v___y_2579_ = v___x_2591_;
v___y_2580_ = v___x_2592_;
goto v___jp_2577_;
}
else
{
uint32_t v___x_2593_; 
v___x_2593_ = 2147483648;
v___y_2578_ = v___y_2584_;
v___y_2579_ = v___x_2591_;
v___y_2580_ = v___x_2593_;
goto v___jp_2577_;
}
}
else
{
if (v___y_2586_ == 0)
{
uint32_t v___x_2594_; 
v___x_2594_ = 0;
v___y_2574_ = v___x_2594_;
goto v___jp_2573_;
}
else
{
uint32_t v___x_2595_; 
v___x_2595_ = 2147483648;
v___y_2574_ = v___x_2595_;
goto v___jp_2573_;
}
}
}
else
{
if (v___y_2586_ == 0)
{
uint32_t v___x_2596_; 
v___x_2596_ = 0;
return v___x_2596_;
}
else
{
uint32_t v___x_2597_; 
v___x_2597_ = 2147483648;
return v___x_2597_;
}
}
}
v___jp_2601_:
{
uint32_t v___x_2606_; uint32_t v___x_2607_; uint32_t v___x_2608_; uint32_t v___x_2609_; uint32_t v___x_2610_; 
v___x_2606_ = lean_uint32_land(v___y_2604_, v___x_2600_);
v___x_2607_ = lean_uint32_shift_left(v___x_2606_, v___x_2598_);
v___x_2608_ = lean_uint32_lor(v___y_2605_, v___x_2607_);
v___x_2609_ = lean_uint32_land(v___y_2603_, v___y_2602_);
v___x_2610_ = lean_uint32_lor(v___x_2608_, v___x_2609_);
return v___x_2610_;
}
v___jp_2611_:
{
if (v___y_2613_ == 0)
{
uint32_t v___x_2616_; 
v___x_2616_ = 0;
v___y_2602_ = v___y_2612_;
v___y_2603_ = v___y_2615_;
v___y_2604_ = v___y_2614_;
v___y_2605_ = v___x_2616_;
goto v___jp_2601_;
}
else
{
uint32_t v___x_2617_; 
v___x_2617_ = 2147483648;
v___y_2602_ = v___y_2612_;
v___y_2603_ = v___y_2615_;
v___y_2604_ = v___y_2614_;
v___y_2605_ = v___x_2617_;
goto v___jp_2601_;
}
}
v___jp_2618_:
{
uint64_t v___x_2624_; uint64_t v_encodedExponent_2625_; uint32_t v___x_2626_; uint64_t v___x_2627_; uint8_t v___x_2628_; 
v___x_2624_ = 171ULL;
v_encodedExponent_2625_ = lean_uint64_sub(v___y_2622_, v___x_2624_);
v___x_2626_ = lean_uint64_to_uint32(v_encodedExponent_2625_);
v___x_2627_ = 8388608ULL;
v___x_2628_ = lean_uint64_dec_lt(v___y_2623_, v___x_2627_);
if (v___x_2628_ == 0)
{
uint64_t v___x_2629_; uint32_t v___x_2630_; 
v___x_2629_ = lean_uint64_sub(v___y_2623_, v___x_2627_);
v___x_2630_ = lean_uint64_to_uint32(v___x_2629_);
v___y_2612_ = v___y_2619_;
v___y_2613_ = v___y_2621_;
v___y_2614_ = v___x_2626_;
v___y_2615_ = v___x_2630_;
goto v___jp_2611_;
}
else
{
uint32_t v___x_2631_; 
v___x_2631_ = lean_uint64_to_uint32(v___y_2620_);
v___y_2612_ = v___y_2619_;
v___y_2613_ = v___y_2621_;
v___y_2614_ = v___x_2626_;
v___y_2615_ = v___x_2631_;
goto v___jp_2611_;
}
}
v___jp_2632_:
{
uint64_t v___x_2639_; uint8_t v___x_2640_; 
v___x_2639_ = 425ULL;
v___x_2640_ = lean_uint64_dec_lt(v___x_2639_, v___y_2638_);
if (v___x_2640_ == 0)
{
if (v___y_2635_ == 0)
{
v___y_2619_ = v___y_2633_;
v___y_2620_ = v___y_2634_;
v___y_2621_ = v___y_2637_;
v___y_2622_ = v___y_2638_;
v___y_2623_ = v___y_2636_;
goto v___jp_2618_;
}
else
{
uint64_t v___x_2641_; 
v___x_2641_ = 8388608ULL;
v___y_2619_ = v___y_2633_;
v___y_2620_ = v___y_2634_;
v___y_2621_ = v___y_2637_;
v___y_2622_ = v___y_2638_;
v___y_2623_ = v___x_2641_;
goto v___jp_2618_;
}
}
else
{
if (v___y_2637_ == 0)
{
uint32_t v___x_2642_; 
v___x_2642_ = 2139095040;
return v___x_2642_;
}
else
{
uint32_t v___x_2643_; 
v___x_2643_ = 4286578688;
return v___x_2643_;
}
}
}
v___jp_2644_:
{
uint64_t v___x_2650_; uint8_t v_carry_2651_; 
v___x_2650_ = 16777216ULL;
v_carry_2651_ = lean_uint64_dec_eq(v___y_2649_, v___x_2650_);
if (v_carry_2651_ == 0)
{
v___y_2633_ = v___y_2645_;
v___y_2634_ = v___y_2646_;
v___y_2635_ = v_carry_2651_;
v___y_2636_ = v___y_2649_;
v___y_2637_ = v___y_2648_;
v___y_2638_ = v___y_2647_;
goto v___jp_2632_;
}
else
{
uint64_t v___x_2652_; uint64_t v___x_2653_; 
v___x_2652_ = 1ULL;
v___x_2653_ = lean_uint64_add(v___y_2647_, v___x_2652_);
v___y_2633_ = v___y_2645_;
v___y_2634_ = v___y_2646_;
v___y_2635_ = v_carry_2651_;
v___y_2636_ = v___y_2649_;
v___y_2637_ = v___y_2648_;
v___y_2638_ = v___x_2653_;
goto v___jp_2632_;
}
}
v___jp_2654_:
{
uint64_t v_position_2661_; uint64_t v___x_2662_; uint8_t v___x_2663_; 
v_position_2661_ = lean_uint64_add(v___y_2660_, v___y_2658_);
v___x_2662_ = 172ULL;
v___x_2663_ = lean_uint64_dec_lt(v_position_2661_, v___x_2662_);
if (v___x_2663_ == 0)
{
uint64_t v___x_2664_; uint8_t v___x_2665_; 
v___x_2664_ = 23ULL;
v___x_2665_ = lean_uint64_dec_lt(v___y_2660_, v___x_2664_);
if (v___x_2665_ == 0)
{
uint64_t v___x_2666_; uint8_t v___x_2667_; 
v___x_2666_ = lean_uint64_sub(v___y_2660_, v___x_2664_);
v___x_2667_ = lean_uint64_dec_eq(v___x_2666_, v___y_2657_);
if (v___x_2667_ == 0)
{
uint64_t v___x_2668_; uint8_t v___x_2669_; 
v___x_2668_ = 64ULL;
v___x_2669_ = lean_uint64_dec_lt(v___x_2666_, v___x_2668_);
if (v___x_2669_ == 0)
{
uint8_t v___x_2670_; 
v___x_2670_ = lean_uint64_dec_eq(v___x_2666_, v___x_2668_);
if (v___x_2670_ == 0)
{
v___y_2645_ = v___y_2656_;
v___y_2646_ = v___y_2657_;
v___y_2647_ = v_position_2661_;
v___y_2648_ = v___y_2659_;
v___y_2649_ = v___y_2657_;
goto v___jp_2644_;
}
else
{
uint64_t v___x_2671_; uint8_t v___x_2672_; 
v___x_2671_ = 9223372036854775808ULL;
v___x_2672_ = lean_uint64_dec_lt(v___x_2671_, v___y_2655_);
if (v___x_2672_ == 0)
{
v___y_2645_ = v___y_2656_;
v___y_2646_ = v___y_2657_;
v___y_2647_ = v_position_2661_;
v___y_2648_ = v___y_2659_;
v___y_2649_ = v___y_2657_;
goto v___jp_2644_;
}
else
{
uint64_t v___x_2673_; 
v___x_2673_ = 1ULL;
v___y_2645_ = v___y_2656_;
v___y_2646_ = v___y_2657_;
v___y_2647_ = v_position_2661_;
v___y_2648_ = v___y_2659_;
v___y_2649_ = v___x_2673_;
goto v___jp_2644_;
}
}
}
else
{
uint64_t v_quotient_2674_; uint64_t v___x_2675_; uint64_t v___x_2676_; uint64_t v___x_2677_; uint64_t v_remainder_2678_; uint64_t v___x_2679_; uint64_t v_half_2680_; uint8_t v___x_2681_; 
v_quotient_2674_ = lean_uint64_shift_right(v___y_2655_, v___x_2666_);
v___x_2675_ = 1ULL;
v___x_2676_ = lean_uint64_shift_left(v___x_2675_, v___x_2666_);
v___x_2677_ = lean_uint64_sub(v___x_2676_, v___x_2675_);
v_remainder_2678_ = lean_uint64_land(v___y_2655_, v___x_2677_);
v___x_2679_ = lean_uint64_sub(v___x_2666_, v___x_2675_);
v_half_2680_ = lean_uint64_shift_left(v___x_2675_, v___x_2679_);
v___x_2681_ = lean_uint64_dec_lt(v_remainder_2678_, v_half_2680_);
if (v___x_2681_ == 0)
{
uint8_t v___x_2682_; 
v___x_2682_ = lean_uint64_dec_lt(v_half_2680_, v_remainder_2678_);
if (v___x_2682_ == 0)
{
uint64_t v___x_2683_; uint8_t v___x_2684_; 
v___x_2683_ = lean_uint64_land(v_quotient_2674_, v___x_2675_);
v___x_2684_ = lean_uint64_dec_eq(v___x_2683_, v___y_2657_);
if (v___x_2684_ == 0)
{
uint64_t v___x_2685_; 
v___x_2685_ = lean_uint64_add(v_quotient_2674_, v___x_2675_);
v___y_2645_ = v___y_2656_;
v___y_2646_ = v___y_2657_;
v___y_2647_ = v_position_2661_;
v___y_2648_ = v___y_2659_;
v___y_2649_ = v___x_2685_;
goto v___jp_2644_;
}
else
{
v___y_2645_ = v___y_2656_;
v___y_2646_ = v___y_2657_;
v___y_2647_ = v_position_2661_;
v___y_2648_ = v___y_2659_;
v___y_2649_ = v_quotient_2674_;
goto v___jp_2644_;
}
}
else
{
uint64_t v___x_2686_; 
v___x_2686_ = lean_uint64_add(v_quotient_2674_, v___x_2675_);
v___y_2645_ = v___y_2656_;
v___y_2646_ = v___y_2657_;
v___y_2647_ = v_position_2661_;
v___y_2648_ = v___y_2659_;
v___y_2649_ = v___x_2686_;
goto v___jp_2644_;
}
}
else
{
v___y_2645_ = v___y_2656_;
v___y_2646_ = v___y_2657_;
v___y_2647_ = v_position_2661_;
v___y_2648_ = v___y_2659_;
v___y_2649_ = v_quotient_2674_;
goto v___jp_2644_;
}
}
}
else
{
v___y_2645_ = v___y_2656_;
v___y_2646_ = v___y_2657_;
v___y_2647_ = v_position_2661_;
v___y_2648_ = v___y_2659_;
v___y_2649_ = v___y_2655_;
goto v___jp_2644_;
}
}
else
{
uint64_t v___x_2687_; uint64_t v___x_2688_; 
v___x_2687_ = lean_uint64_sub(v___x_2664_, v___y_2660_);
v___x_2688_ = lean_uint64_shift_left(v___y_2655_, v___x_2687_);
v___y_2645_ = v___y_2656_;
v___y_2646_ = v___y_2657_;
v___y_2647_ = v_position_2661_;
v___y_2648_ = v___y_2659_;
v___y_2649_ = v___x_2688_;
goto v___jp_2644_;
}
}
else
{
uint64_t v___x_2689_; uint8_t v___x_2690_; 
v___x_2689_ = 149ULL;
v___x_2690_ = lean_uint64_dec_lt(v___y_2658_, v___x_2689_);
if (v___x_2690_ == 0)
{
uint64_t v___x_2691_; uint64_t v___x_2692_; 
v___x_2691_ = lean_uint64_sub(v___y_2658_, v___x_2689_);
v___x_2692_ = lean_uint64_shift_left(v___y_2655_, v___x_2691_);
v___y_2584_ = v___y_2656_;
v___y_2585_ = v___y_2657_;
v___y_2586_ = v___y_2659_;
v___y_2587_ = v___x_2692_;
goto v___jp_2583_;
}
else
{
uint64_t v___x_2693_; uint8_t v___x_2694_; 
v___x_2693_ = lean_uint64_sub(v___x_2689_, v___y_2658_);
v___x_2694_ = lean_uint64_dec_eq(v___x_2693_, v___y_2657_);
if (v___x_2694_ == 0)
{
uint64_t v___x_2695_; uint8_t v___x_2696_; 
v___x_2695_ = 64ULL;
v___x_2696_ = lean_uint64_dec_lt(v___x_2693_, v___x_2695_);
if (v___x_2696_ == 0)
{
uint8_t v___x_2697_; 
v___x_2697_ = lean_uint64_dec_eq(v___x_2693_, v___x_2695_);
if (v___x_2697_ == 0)
{
v___y_2584_ = v___y_2656_;
v___y_2585_ = v___y_2657_;
v___y_2586_ = v___y_2659_;
v___y_2587_ = v___y_2657_;
goto v___jp_2583_;
}
else
{
uint64_t v___x_2698_; uint8_t v___x_2699_; 
v___x_2698_ = 9223372036854775808ULL;
v___x_2699_ = lean_uint64_dec_lt(v___x_2698_, v___y_2655_);
if (v___x_2699_ == 0)
{
v___y_2584_ = v___y_2656_;
v___y_2585_ = v___y_2657_;
v___y_2586_ = v___y_2659_;
v___y_2587_ = v___y_2657_;
goto v___jp_2583_;
}
else
{
uint64_t v___x_2700_; 
v___x_2700_ = 1ULL;
v___y_2584_ = v___y_2656_;
v___y_2585_ = v___y_2657_;
v___y_2586_ = v___y_2659_;
v___y_2587_ = v___x_2700_;
goto v___jp_2583_;
}
}
}
else
{
uint64_t v_quotient_2701_; uint64_t v___x_2702_; uint64_t v___x_2703_; uint64_t v___x_2704_; uint64_t v_remainder_2705_; uint64_t v___x_2706_; uint64_t v_half_2707_; uint8_t v___x_2708_; 
v_quotient_2701_ = lean_uint64_shift_right(v___y_2655_, v___x_2693_);
v___x_2702_ = 1ULL;
v___x_2703_ = lean_uint64_shift_left(v___x_2702_, v___x_2693_);
v___x_2704_ = lean_uint64_sub(v___x_2703_, v___x_2702_);
v_remainder_2705_ = lean_uint64_land(v___y_2655_, v___x_2704_);
v___x_2706_ = lean_uint64_sub(v___x_2693_, v___x_2702_);
v_half_2707_ = lean_uint64_shift_left(v___x_2702_, v___x_2706_);
v___x_2708_ = lean_uint64_dec_lt(v_remainder_2705_, v_half_2707_);
if (v___x_2708_ == 0)
{
uint8_t v___x_2709_; 
v___x_2709_ = lean_uint64_dec_lt(v_half_2707_, v_remainder_2705_);
if (v___x_2709_ == 0)
{
uint64_t v___x_2710_; uint8_t v___x_2711_; 
v___x_2710_ = lean_uint64_land(v_quotient_2701_, v___x_2702_);
v___x_2711_ = lean_uint64_dec_eq(v___x_2710_, v___y_2657_);
if (v___x_2711_ == 0)
{
uint64_t v___x_2712_; 
v___x_2712_ = lean_uint64_add(v_quotient_2701_, v___x_2702_);
v___y_2584_ = v___y_2656_;
v___y_2585_ = v___y_2657_;
v___y_2586_ = v___y_2659_;
v___y_2587_ = v___x_2712_;
goto v___jp_2583_;
}
else
{
v___y_2584_ = v___y_2656_;
v___y_2585_ = v___y_2657_;
v___y_2586_ = v___y_2659_;
v___y_2587_ = v_quotient_2701_;
goto v___jp_2583_;
}
}
else
{
uint64_t v___x_2713_; 
v___x_2713_ = lean_uint64_add(v_quotient_2701_, v___x_2702_);
v___y_2584_ = v___y_2656_;
v___y_2585_ = v___y_2657_;
v___y_2586_ = v___y_2659_;
v___y_2587_ = v___x_2713_;
goto v___jp_2583_;
}
}
else
{
v___y_2584_ = v___y_2656_;
v___y_2585_ = v___y_2657_;
v___y_2586_ = v___y_2659_;
v___y_2587_ = v_quotient_2701_;
goto v___jp_2583_;
}
}
}
else
{
v___y_2584_ = v___y_2656_;
v___y_2585_ = v___y_2657_;
v___y_2586_ = v___y_2659_;
v___y_2587_ = v___y_2655_;
goto v___jp_2583_;
}
}
}
}
v___jp_2714_:
{
uint64_t v___x_2722_; uint64_t v___x_2723_; uint8_t v___x_2724_; 
v___x_2722_ = 1ULL;
v___x_2723_ = lean_uint64_shift_right(v___y_2715_, v___x_2722_);
v___x_2724_ = lean_uint64_dec_eq(v___x_2723_, v___y_2719_);
if (v___x_2724_ == 0)
{
uint64_t v___x_2725_; 
v___x_2725_ = lean_uint64_add(v___y_2721_, v___x_2722_);
v___y_2655_ = v___y_2717_;
v___y_2656_ = v___y_2716_;
v___y_2657_ = v___y_2719_;
v___y_2658_ = v___y_2718_;
v___y_2659_ = v___y_2720_;
v___y_2660_ = v___x_2725_;
goto v___jp_2654_;
}
else
{
v___y_2655_ = v___y_2717_;
v___y_2656_ = v___y_2716_;
v___y_2657_ = v___y_2719_;
v___y_2658_ = v___y_2718_;
v___y_2659_ = v___y_2720_;
v___y_2660_ = v___y_2721_;
goto v___jp_2654_;
}
}
v___jp_2726_:
{
uint64_t v___x_2736_; uint8_t v___x_2737_; 
v___x_2736_ = lean_uint64_shift_right(v___y_2734_, v___y_2733_);
v___x_2737_ = lean_uint64_dec_eq(v___x_2736_, v___y_2729_);
if (v___x_2737_ == 0)
{
uint64_t v___x_2738_; 
v___x_2738_ = lean_uint64_add(v___y_2732_, v___y_2733_);
v___y_2715_ = v___y_2735_;
v___y_2716_ = v___y_2728_;
v___y_2717_ = v___y_2727_;
v___y_2718_ = v___y_2730_;
v___y_2719_ = v___y_2729_;
v___y_2720_ = v___y_2731_;
v___y_2721_ = v___x_2738_;
goto v___jp_2714_;
}
else
{
v___y_2715_ = v___y_2735_;
v___y_2716_ = v___y_2728_;
v___y_2717_ = v___y_2727_;
v___y_2718_ = v___y_2730_;
v___y_2719_ = v___y_2729_;
v___y_2720_ = v___y_2731_;
v___y_2721_ = v___y_2732_;
goto v___jp_2714_;
}
}
v___jp_2739_:
{
uint64_t v___x_2747_; uint64_t v___x_2748_; uint8_t v___x_2749_; 
v___x_2747_ = 2ULL;
v___x_2748_ = lean_uint64_shift_right(v___y_2745_, v___x_2747_);
v___x_2749_ = lean_uint64_dec_eq(v___x_2748_, v___y_2743_);
if (v___x_2749_ == 0)
{
v___y_2727_ = v___y_2741_;
v___y_2728_ = v___y_2740_;
v___y_2729_ = v___y_2743_;
v___y_2730_ = v___y_2742_;
v___y_2731_ = v___y_2744_;
v___y_2732_ = v___y_2746_;
v___y_2733_ = v___x_2747_;
v___y_2734_ = v___y_2745_;
v___y_2735_ = v___x_2748_;
goto v___jp_2726_;
}
else
{
v___y_2727_ = v___y_2741_;
v___y_2728_ = v___y_2740_;
v___y_2729_ = v___y_2743_;
v___y_2730_ = v___y_2742_;
v___y_2731_ = v___y_2744_;
v___y_2732_ = v___y_2746_;
v___y_2733_ = v___x_2747_;
v___y_2734_ = v___y_2745_;
v___y_2735_ = v___y_2745_;
goto v___jp_2726_;
}
}
v___jp_2750_:
{
uint64_t v___x_2760_; uint8_t v___x_2761_; 
v___x_2760_ = lean_uint64_shift_right(v___y_2751_, v___y_2757_);
v___x_2761_ = lean_uint64_dec_eq(v___x_2760_, v___y_2754_);
if (v___x_2761_ == 0)
{
uint64_t v___x_2762_; 
v___x_2762_ = lean_uint64_add(v___y_2756_, v___y_2757_);
v___y_2740_ = v___y_2753_;
v___y_2741_ = v___y_2752_;
v___y_2742_ = v___y_2755_;
v___y_2743_ = v___y_2754_;
v___y_2744_ = v___y_2758_;
v___y_2745_ = v___y_2759_;
v___y_2746_ = v___x_2762_;
goto v___jp_2739_;
}
else
{
v___y_2740_ = v___y_2753_;
v___y_2741_ = v___y_2752_;
v___y_2742_ = v___y_2755_;
v___y_2743_ = v___y_2754_;
v___y_2744_ = v___y_2758_;
v___y_2745_ = v___y_2759_;
v___y_2746_ = v___y_2756_;
goto v___jp_2739_;
}
}
v___jp_2763_:
{
uint64_t v___x_2771_; uint64_t v___x_2772_; uint8_t v___x_2773_; 
v___x_2771_ = 4ULL;
v___x_2772_ = lean_uint64_shift_right(v___y_2766_, v___x_2771_);
v___x_2773_ = lean_uint64_dec_eq(v___x_2772_, v___y_2768_);
if (v___x_2773_ == 0)
{
v___y_2751_ = v___y_2766_;
v___y_2752_ = v___y_2765_;
v___y_2753_ = v___y_2764_;
v___y_2754_ = v___y_2768_;
v___y_2755_ = v___y_2767_;
v___y_2756_ = v___y_2770_;
v___y_2757_ = v___x_2771_;
v___y_2758_ = v___y_2769_;
v___y_2759_ = v___x_2772_;
goto v___jp_2750_;
}
else
{
v___y_2751_ = v___y_2766_;
v___y_2752_ = v___y_2765_;
v___y_2753_ = v___y_2764_;
v___y_2754_ = v___y_2768_;
v___y_2755_ = v___y_2767_;
v___y_2756_ = v___y_2770_;
v___y_2757_ = v___x_2771_;
v___y_2758_ = v___y_2769_;
v___y_2759_ = v___y_2766_;
goto v___jp_2750_;
}
}
v___jp_2774_:
{
uint64_t v___x_2784_; uint8_t v___x_2785_; 
v___x_2784_ = lean_uint64_shift_right(v___y_2781_, v___y_2780_);
v___x_2785_ = lean_uint64_dec_eq(v___x_2784_, v___y_2778_);
if (v___x_2785_ == 0)
{
uint64_t v___x_2786_; 
v___x_2786_ = lean_uint64_add(v___y_2777_, v___y_2780_);
v___y_2764_ = v___y_2776_;
v___y_2765_ = v___y_2775_;
v___y_2766_ = v___y_2783_;
v___y_2767_ = v___y_2779_;
v___y_2768_ = v___y_2778_;
v___y_2769_ = v___y_2782_;
v___y_2770_ = v___x_2786_;
goto v___jp_2763_;
}
else
{
v___y_2764_ = v___y_2776_;
v___y_2765_ = v___y_2775_;
v___y_2766_ = v___y_2783_;
v___y_2767_ = v___y_2779_;
v___y_2768_ = v___y_2778_;
v___y_2769_ = v___y_2782_;
v___y_2770_ = v___y_2777_;
goto v___jp_2763_;
}
}
v___jp_2787_:
{
uint64_t v___x_2795_; uint64_t v___x_2796_; uint8_t v___x_2797_; 
v___x_2795_ = 8ULL;
v___x_2796_ = lean_uint64_shift_right(v___y_2792_, v___x_2795_);
v___x_2797_ = lean_uint64_dec_eq(v___x_2796_, v___y_2791_);
if (v___x_2797_ == 0)
{
v___y_2775_ = v___y_2789_;
v___y_2776_ = v___y_2788_;
v___y_2777_ = v___y_2794_;
v___y_2778_ = v___y_2791_;
v___y_2779_ = v___y_2790_;
v___y_2780_ = v___x_2795_;
v___y_2781_ = v___y_2792_;
v___y_2782_ = v___y_2793_;
v___y_2783_ = v___x_2796_;
goto v___jp_2774_;
}
else
{
v___y_2775_ = v___y_2789_;
v___y_2776_ = v___y_2788_;
v___y_2777_ = v___y_2794_;
v___y_2778_ = v___y_2791_;
v___y_2779_ = v___y_2790_;
v___y_2780_ = v___x_2795_;
v___y_2781_ = v___y_2792_;
v___y_2782_ = v___y_2793_;
v___y_2783_ = v___y_2792_;
goto v___jp_2774_;
}
}
v___jp_2798_:
{
uint64_t v___x_2808_; uint8_t v___x_2809_; 
v___x_2808_ = lean_uint64_shift_right(v___y_2806_, v___y_2803_);
v___x_2809_ = lean_uint64_dec_eq(v___x_2808_, v___y_2801_);
if (v___x_2809_ == 0)
{
uint64_t v___x_2810_; 
v___x_2810_ = lean_uint64_add(v___y_2804_, v___y_2803_);
v___y_2788_ = v___y_2800_;
v___y_2789_ = v___y_2799_;
v___y_2790_ = v___y_2802_;
v___y_2791_ = v___y_2801_;
v___y_2792_ = v___y_2807_;
v___y_2793_ = v___y_2805_;
v___y_2794_ = v___x_2810_;
goto v___jp_2787_;
}
else
{
v___y_2788_ = v___y_2800_;
v___y_2789_ = v___y_2799_;
v___y_2790_ = v___y_2802_;
v___y_2791_ = v___y_2801_;
v___y_2792_ = v___y_2807_;
v___y_2793_ = v___y_2805_;
v___y_2794_ = v___y_2804_;
goto v___jp_2787_;
}
}
v___jp_2811_:
{
uint64_t v___x_2819_; uint64_t v___x_2820_; uint8_t v___x_2821_; 
v___x_2819_ = 16ULL;
v___x_2820_ = lean_uint64_shift_right(v___y_2817_, v___x_2819_);
v___x_2821_ = lean_uint64_dec_eq(v___x_2820_, v___y_2815_);
if (v___x_2821_ == 0)
{
v___y_2799_ = v___y_2813_;
v___y_2800_ = v___y_2812_;
v___y_2801_ = v___y_2815_;
v___y_2802_ = v___y_2814_;
v___y_2803_ = v___x_2819_;
v___y_2804_ = v___y_2818_;
v___y_2805_ = v___y_2816_;
v___y_2806_ = v___y_2817_;
v___y_2807_ = v___x_2820_;
goto v___jp_2798_;
}
else
{
v___y_2799_ = v___y_2813_;
v___y_2800_ = v___y_2812_;
v___y_2801_ = v___y_2815_;
v___y_2802_ = v___y_2814_;
v___y_2803_ = v___x_2819_;
v___y_2804_ = v___y_2818_;
v___y_2805_ = v___y_2816_;
v___y_2806_ = v___y_2817_;
v___y_2807_ = v___y_2817_;
goto v___jp_2798_;
}
}
v___jp_2822_:
{
uint64_t v___x_2830_; uint8_t v___x_2831_; 
v___x_2830_ = lean_uint64_shift_right(v___y_2823_, v___y_2827_);
v___x_2831_ = lean_uint64_dec_eq(v___x_2830_, v___y_2825_);
if (v___x_2831_ == 0)
{
v___y_2812_ = v___y_2824_;
v___y_2813_ = v___y_2823_;
v___y_2814_ = v___y_2826_;
v___y_2815_ = v___y_2825_;
v___y_2816_ = v___y_2828_;
v___y_2817_ = v___y_2829_;
v___y_2818_ = v___y_2827_;
goto v___jp_2811_;
}
else
{
v___y_2812_ = v___y_2824_;
v___y_2813_ = v___y_2823_;
v___y_2814_ = v___y_2826_;
v___y_2815_ = v___y_2825_;
v___y_2816_ = v___y_2828_;
v___y_2817_ = v___y_2829_;
v___y_2818_ = v___y_2825_;
goto v___jp_2811_;
}
}
v___jp_2832_:
{
uint64_t v___x_2839_; uint64_t v___x_2840_; uint8_t v___x_2841_; 
v___x_2839_ = lean_uint64_mul(v___y_2835_, v___y_2834_);
v___x_2840_ = 0ULL;
v___x_2841_ = lean_uint64_dec_eq(v___x_2839_, v___x_2840_);
if (v___x_2841_ == 0)
{
uint64_t v___x_2842_; uint64_t v___x_2843_; uint64_t v___x_2844_; uint8_t v___x_2845_; 
v___x_2842_ = lean_uint64_add(v___y_2836_, v___y_2838_);
v___x_2843_ = 32ULL;
v___x_2844_ = lean_uint64_shift_right(v___x_2839_, v___x_2843_);
v___x_2845_ = lean_uint64_dec_eq(v___x_2844_, v___x_2840_);
if (v___x_2845_ == 0)
{
v___y_2823_ = v___x_2839_;
v___y_2824_ = v___y_2833_;
v___y_2825_ = v___x_2840_;
v___y_2826_ = v___x_2842_;
v___y_2827_ = v___x_2843_;
v___y_2828_ = v___y_2837_;
v___y_2829_ = v___x_2844_;
goto v___jp_2822_;
}
else
{
v___y_2823_ = v___x_2839_;
v___y_2824_ = v___y_2833_;
v___y_2825_ = v___x_2840_;
v___y_2826_ = v___x_2842_;
v___y_2827_ = v___x_2843_;
v___y_2828_ = v___y_2837_;
v___y_2829_ = v___x_2839_;
goto v___jp_2822_;
}
}
else
{
if (v___y_2837_ == 0)
{
uint32_t v___x_2846_; 
v___x_2846_ = 0;
return v___x_2846_;
}
else
{
uint32_t v___x_2847_; 
v___x_2847_ = 2147483648;
return v___x_2847_;
}
}
}
v___jp_2851_:
{
uint64_t v___x_2857_; uint64_t v___x_2858_; uint8_t v___x_2859_; 
v___x_2857_ = lean_uint32_to_uint64(v_yExponent_2850_);
v___x_2858_ = 0ULL;
v___x_2859_ = lean_uint64_dec_eq(v___x_2857_, v___x_2858_);
if (v___x_2859_ == 0)
{
uint64_t v___x_2860_; uint64_t v___x_2861_; 
v___x_2860_ = 1ULL;
v___x_2861_ = lean_uint64_sub(v___x_2857_, v___x_2860_);
v___y_2833_ = v___y_2852_;
v___y_2834_ = v___y_2853_;
v___y_2835_ = v___y_2854_;
v___y_2836_ = v___y_2856_;
v___y_2837_ = v___y_2855_;
v___y_2838_ = v___x_2861_;
goto v___jp_2832_;
}
else
{
v___y_2833_ = v___y_2852_;
v___y_2834_ = v___y_2853_;
v___y_2835_ = v___y_2854_;
v___y_2836_ = v___y_2856_;
v___y_2837_ = v___y_2855_;
v___y_2838_ = v___x_2858_;
goto v___jp_2832_;
}
}
v___jp_2862_:
{
uint64_t v___x_2867_; uint64_t v___x_2868_; uint8_t v___x_2869_; 
v___x_2867_ = lean_uint32_to_uint64(v_xExponent_2848_);
v___x_2868_ = 0ULL;
v___x_2869_ = lean_uint64_dec_eq(v___x_2867_, v___x_2868_);
if (v___x_2869_ == 0)
{
uint64_t v___x_2870_; uint64_t v___x_2871_; 
v___x_2870_ = 1ULL;
v___x_2871_ = lean_uint64_sub(v___x_2867_, v___x_2870_);
v___y_2852_ = v___y_2863_;
v___y_2853_ = v___y_2866_;
v___y_2854_ = v___y_2864_;
v___y_2855_ = v___y_2865_;
v___y_2856_ = v___x_2871_;
goto v___jp_2851_;
}
else
{
v___y_2852_ = v___y_2863_;
v___y_2853_ = v___y_2866_;
v___y_2854_ = v___y_2864_;
v___y_2855_ = v___y_2865_;
v___y_2856_ = v___x_2868_;
goto v___jp_2851_;
}
}
v___jp_2872_:
{
uint32_t v___x_2877_; uint8_t v___x_2878_; 
v___x_2877_ = 0;
v___x_2878_ = lean_uint32_dec_eq(v_yExponent_2850_, v___x_2877_);
if (v___x_2878_ == 0)
{
uint64_t v___x_2879_; uint64_t v___x_2880_; uint64_t v___x_2881_; 
v___x_2879_ = lean_uint32_to_uint64(v___y_2874_);
v___x_2880_ = 8388608ULL;
v___x_2881_ = lean_uint64_lor(v___x_2879_, v___x_2880_);
v___y_2863_ = v___y_2873_;
v___y_2864_ = v___y_2876_;
v___y_2865_ = v___y_2875_;
v___y_2866_ = v___x_2881_;
goto v___jp_2862_;
}
else
{
uint64_t v___x_2882_; 
v___x_2882_ = lean_uint32_to_uint64(v___y_2874_);
v___y_2863_ = v___y_2873_;
v___y_2864_ = v___y_2876_;
v___y_2865_ = v___y_2875_;
v___y_2866_ = v___x_2882_;
goto v___jp_2862_;
}
}
v___jp_2883_:
{
uint32_t v___x_2885_; uint32_t v_xFraction_2886_; uint32_t v_yFraction_2887_; uint32_t v___x_2888_; uint8_t v___x_2889_; 
v___x_2885_ = 8388607;
v_xFraction_2886_ = lean_uint32_land(v_xBits_2571_, v___x_2885_);
v_yFraction_2887_ = lean_uint32_land(v_yBits_2572_, v___x_2885_);
v___x_2888_ = 0;
v___x_2889_ = lean_uint32_dec_eq(v_xExponent_2848_, v___x_2888_);
if (v___x_2889_ == 0)
{
uint64_t v___x_2890_; uint64_t v___x_2891_; uint64_t v___x_2892_; 
v___x_2890_ = lean_uint32_to_uint64(v_xFraction_2886_);
v___x_2891_ = 8388608ULL;
v___x_2892_ = lean_uint64_lor(v___x_2890_, v___x_2891_);
v___y_2873_ = v___x_2885_;
v___y_2874_ = v_yFraction_2887_;
v___y_2875_ = v___y_2884_;
v___y_2876_ = v___x_2892_;
goto v___jp_2872_;
}
else
{
uint64_t v___x_2893_; 
v___x_2893_ = lean_uint32_to_uint64(v_xFraction_2886_);
v___y_2873_ = v___x_2885_;
v___y_2874_ = v_yFraction_2887_;
v___y_2875_ = v___y_2884_;
v___y_2876_ = v___x_2893_;
goto v___jp_2872_;
}
}
v___jp_2894_:
{
uint8_t v___x_2895_; 
v___x_2895_ = 1;
v___y_2884_ = v___x_2895_;
goto v___jp_2883_;
}
v___jp_2896_:
{
uint8_t v___x_2897_; 
v___x_2897_ = 0;
v___y_2884_ = v___x_2897_;
goto v___jp_2883_;
}
v___jp_2898_:
{
if (v___y_2899_ == 0)
{
if (v___y_2900_ == 0)
{
goto v___jp_2896_;
}
else
{
goto v___jp_2894_;
}
}
else
{
if (v___y_2900_ == 0)
{
goto v___jp_2894_;
}
else
{
goto v___jp_2896_;
}
}
}
v___jp_2901_:
{
uint32_t v___x_2903_; uint32_t v___x_2904_; uint32_t v___x_2905_; uint8_t v___x_2906_; 
v___x_2903_ = 2147483648;
v___x_2904_ = lean_uint32_land(v_yBits_2572_, v___x_2903_);
v___x_2905_ = 0;
v___x_2906_ = lean_uint32_dec_eq(v___x_2904_, v___x_2905_);
if (v___x_2906_ == 0)
{
uint8_t v___x_2907_; 
v___x_2907_ = 1;
v___y_2899_ = v___y_2902_;
v___y_2900_ = v___x_2907_;
goto v___jp_2898_;
}
else
{
uint8_t v___x_2908_; 
v___x_2908_ = 0;
v___y_2899_ = v___y_2902_;
v___y_2900_ = v___x_2908_;
goto v___jp_2898_;
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_FastMul_core___boxed(lean_object* v_xBits_2915_, lean_object* v_yBits_2916_){
_start:
{
uint32_t v_xBits_boxed_2917_; uint32_t v_yBits_boxed_2918_; uint32_t v_res_2919_; lean_object* v_r_2920_; 
v_xBits_boxed_2917_ = lean_unbox_uint32(v_xBits_2915_);
lean_dec(v_xBits_2915_);
v_yBits_boxed_2918_ = lean_unbox_uint32(v_yBits_2916_);
lean_dec(v_yBits_2916_);
v_res_2919_ = lp_competition_Submission_FastMul_core(v_xBits_boxed_2917_, v_yBits_boxed_2918_);
v_r_2920_ = lean_box_uint32(v_res_2919_);
return v_r_2920_;
}
}
LEAN_EXPORT uint8_t lp_competition_Submission_FastMul_sm1(uint32_t v_a_2921_){
_start:
{
uint32_t v___x_2922_; uint32_t v___x_2923_; uint32_t v___x_2924_; uint8_t v___x_2925_; 
v___x_2922_ = 4278190080;
v___x_2923_ = 1;
v___x_2924_ = lean_uint32_shift_left(v_a_2921_, v___x_2923_);
v___x_2925_ = lean_uint32_dec_le(v___x_2922_, v___x_2924_);
return v___x_2925_;
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_FastMul_sm1___boxed(lean_object* v_a_2926_){
_start:
{
uint32_t v_a_boxed_2927_; uint8_t v_res_2928_; lean_object* v_r_2929_; 
v_a_boxed_2927_ = lean_unbox_uint32(v_a_2926_);
lean_dec(v_a_2926_);
v_res_2928_ = lp_competition_Submission_FastMul_sm1(v_a_boxed_2927_);
v_r_2929_ = lean_box(v_res_2928_);
return v_r_2929_;
}
}
LEAN_EXPORT uint8_t lp_competition_Submission_FastMul_special(uint32_t v_a_2930_, uint32_t v_b_2931_){
_start:
{
uint32_t v___x_2932_; uint32_t v___x_2933_; uint32_t v___x_2934_; uint8_t v___x_2935_; 
v___x_2932_ = 4278190080;
v___x_2933_ = 1;
v___x_2934_ = lean_uint32_shift_left(v_a_2930_, v___x_2933_);
v___x_2935_ = lean_uint32_dec_le(v___x_2932_, v___x_2934_);
if (v___x_2935_ == 0)
{
uint32_t v___x_2936_; uint8_t v___x_2937_; 
v___x_2936_ = lean_uint32_shift_left(v_b_2931_, v___x_2933_);
v___x_2937_ = lean_uint32_dec_le(v___x_2932_, v___x_2936_);
return v___x_2937_;
}
else
{
return v___x_2935_;
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_FastMul_special___boxed(lean_object* v_a_2938_, lean_object* v_b_2939_){
_start:
{
uint32_t v_a_boxed_2940_; uint32_t v_b_boxed_2941_; uint8_t v_res_2942_; lean_object* v_r_2943_; 
v_a_boxed_2940_ = lean_unbox_uint32(v_a_2938_);
lean_dec(v_a_2938_);
v_b_boxed_2941_ = lean_unbox_uint32(v_b_2939_);
lean_dec(v_b_2939_);
v_res_2942_ = lp_competition_Submission_FastMul_special(v_a_boxed_2940_, v_b_boxed_2941_);
v_r_2943_ = lean_box(v_res_2942_);
return v_r_2943_;
}
}
LEAN_EXPORT uint32_t lp_competition_Submission_FastMul_ofBits(uint32_t v_w_2944_){
_start:
{
return v_w_2944_;
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_FastMul_ofBits___boxed(lean_object* v_w_2945_){
_start:
{
uint32_t v_w_boxed_2946_; uint32_t v_res_2947_; lean_object* v_r_2948_; 
v_w_boxed_2946_ = lean_unbox_uint32(v_w_2945_);
lean_dec(v_w_2945_);
v_res_2947_ = lp_competition_Submission_FastMul_ofBits(v_w_boxed_2946_);
v_r_2948_ = lean_box_uint32(v_res_2947_);
return v_r_2948_;
}
}
LEAN_EXPORT uint32_t lp_competition_Submission_FastMul_mul(uint32_t v_x_2949_, uint32_t v_y_2950_){
_start:
{
uint32_t v___y_2952_; uint32_t v___y_2956_; uint32_t v___y_2957_; uint32_t v___y_2958_; uint32_t v___y_2962_; uint8_t v___y_2963_; uint64_t v___y_2964_; uint64_t v___y_2965_; uint32_t v___y_2977_; uint32_t v___y_2978_; uint32_t v___y_2979_; uint32_t v___y_2980_; uint32_t v___y_2981_; uint32_t v___y_2982_; uint32_t v___y_2989_; uint32_t v___y_2990_; uint32_t v___y_2991_; uint32_t v___y_2992_; uint8_t v___y_2993_; uint32_t v___y_2994_; uint64_t v___y_2998_; uint32_t v___y_2999_; uint32_t v___y_3000_; uint32_t v___y_3001_; uint8_t v___y_3002_; uint64_t v___y_3003_; uint64_t v___y_3004_; uint64_t v___y_3014_; uint32_t v___y_3015_; uint32_t v___y_3016_; uint32_t v___y_3017_; uint8_t v___y_3018_; uint8_t v___y_3019_; uint64_t v___y_3020_; uint64_t v___y_3021_; uint64_t v___y_3028_; uint32_t v___y_3029_; uint32_t v___y_3030_; uint32_t v___y_3031_; uint8_t v___y_3032_; uint64_t v___y_3033_; uint64_t v___y_3034_; uint32_t v___y_3040_; uint32_t v___y_3041_; uint32_t v___y_3042_; uint64_t v___y_3043_; uint8_t v___y_3044_; uint64_t v___y_3045_; uint64_t v___y_3046_; uint64_t v___y_3047_; uint32_t v___y_3102_; uint32_t v___y_3103_; uint64_t v___y_3104_; uint32_t v___y_3105_; uint64_t v___y_3106_; uint8_t v___y_3107_; uint64_t v___y_3108_; uint64_t v___y_3109_; uint64_t v___y_3110_; uint32_t v___y_3116_; uint64_t v___y_3117_; uint32_t v___y_3118_; uint64_t v___y_3119_; uint32_t v___y_3120_; uint64_t v___y_3121_; uint64_t v___y_3122_; uint8_t v___y_3123_; uint64_t v___y_3124_; uint64_t v___y_3125_; uint64_t v___y_3126_; uint32_t v___y_3131_; uint32_t v___y_3132_; uint32_t v___y_3133_; uint64_t v___y_3134_; uint64_t v___y_3135_; uint8_t v___y_3136_; uint64_t v___y_3137_; uint64_t v___y_3138_; uint64_t v___y_3139_; uint64_t v___y_3144_; uint32_t v___y_3145_; uint32_t v___y_3146_; uint64_t v___y_3147_; uint32_t v___y_3148_; uint64_t v___y_3149_; uint8_t v___y_3150_; uint64_t v___y_3151_; uint64_t v___y_3152_; uint64_t v___y_3153_; uint64_t v___y_3154_; uint64_t v___y_3159_; uint32_t v___y_3160_; uint32_t v___y_3161_; uint32_t v___y_3162_; uint64_t v___y_3163_; uint8_t v___y_3164_; uint64_t v___y_3165_; uint64_t v___y_3166_; uint64_t v___y_3167_; uint64_t v___y_3172_; uint32_t v___y_3173_; uint32_t v___y_3174_; uint32_t v___y_3175_; uint64_t v___y_3176_; uint64_t v___y_3177_; uint8_t v___y_3178_; uint64_t v___y_3179_; uint64_t v___y_3180_; uint64_t v___y_3181_; uint64_t v___y_3182_; uint32_t v___y_3187_; uint32_t v___y_3188_; uint32_t v___y_3189_; uint64_t v___y_3190_; uint8_t v___y_3191_; uint64_t v___y_3192_; uint64_t v___y_3193_; uint64_t v___y_3194_; uint64_t v___y_3195_; uint64_t v___y_3200_; uint32_t v___y_3201_; uint32_t v___y_3202_; uint64_t v___y_3203_; uint32_t v___y_3204_; uint64_t v___y_3205_; uint8_t v___y_3206_; uint64_t v___y_3207_; uint64_t v___y_3208_; uint64_t v___y_3209_; uint64_t v___y_3210_; uint32_t v___y_3215_; uint32_t v___y_3216_; uint32_t v___y_3217_; uint64_t v___y_3218_; uint64_t v___y_3219_; uint8_t v___y_3220_; uint64_t v___y_3221_; uint64_t v___y_3222_; uint64_t v___y_3223_; uint32_t v___y_3228_; uint32_t v___y_3229_; uint32_t v___y_3230_; uint64_t v___y_3231_; uint8_t v___y_3232_; uint64_t v___y_3233_; uint64_t v___y_3234_; uint64_t v___y_3235_; uint64_t v___y_3236_; uint32_t v___y_3240_; uint32_t v___y_3241_; uint32_t v___y_3242_; uint8_t v___y_3243_; uint64_t v___y_3244_; uint64_t v___y_3245_; uint64_t v___y_3246_; uint64_t v___y_3247_; uint32_t v___y_3258_; uint32_t v___y_3259_; uint32_t v___y_3260_; uint32_t v___y_3261_; uint8_t v___y_3262_; uint64_t v___y_3263_; uint64_t v___y_3264_; uint64_t v___y_3265_; uint32_t v___y_3272_; uint32_t v___y_3273_; uint32_t v___y_3274_; uint32_t v___y_3275_; uint32_t v___y_3276_; uint8_t v___y_3277_; uint64_t v___y_3278_; uint64_t v___y_3279_; uint32_t v___y_3286_; uint32_t v___y_3287_; uint32_t v___y_3288_; uint32_t v___y_3289_; uint32_t v___y_3290_; uint32_t v___y_3291_; uint8_t v___y_3292_; uint64_t v___y_3293_; uint32_t v___y_3301_; uint32_t v___y_3302_; uint32_t v___y_3303_; uint32_t v___y_3304_; uint8_t v___y_3305_; uint32_t v___y_3316_; uint32_t v___y_3317_; uint32_t v___y_3318_; uint32_t v___y_3319_; uint8_t v___y_3322_; uint32_t v___y_3323_; uint8_t v___y_3324_; uint32_t v___y_3325_; uint32_t v___y_3326_; uint32_t v___y_3327_; uint8_t v___y_3328_; uint32_t v___y_3330_; uint8_t v___y_3331_; uint32_t v___y_3332_; uint32_t v___y_3333_; uint32_t v___y_3334_; uint8_t v___y_3335_; uint8_t v___y_3342_; uint32_t v___x_3358_; uint32_t v___x_3359_; uint32_t v___x_3360_; uint8_t v___x_3361_; 
v___x_3358_ = 4278190080;
v___x_3359_ = 1;
v___x_3360_ = lean_uint32_shift_left(v_x_2949_, v___x_3359_);
v___x_3361_ = lean_uint32_dec_le(v___x_3358_, v___x_3360_);
if (v___x_3361_ == 0)
{
uint32_t v___x_3362_; uint8_t v___x_3363_; 
v___x_3362_ = lean_uint32_shift_left(v_y_2950_, v___x_3359_);
v___x_3363_ = lean_uint32_dec_le(v___x_3358_, v___x_3362_);
v___y_3342_ = v___x_3363_;
goto v___jp_3341_;
}
else
{
v___y_3342_ = v___x_3361_;
goto v___jp_3341_;
}
v___jp_2951_:
{
uint32_t v___x_2953_; uint32_t v___x_2954_; 
v___x_2953_ = 8388608;
v___x_2954_ = lean_uint32_lor(v___y_2952_, v___x_2953_);
return v___x_2954_;
}
v___jp_2955_:
{
uint32_t v___x_2959_; uint32_t v___x_2960_; 
v___x_2959_ = lean_uint32_land(v___y_2957_, v___y_2956_);
v___x_2960_ = lean_uint32_lor(v___y_2958_, v___x_2959_);
return v___x_2960_;
}
v___jp_2961_:
{
uint8_t v___x_2966_; 
v___x_2966_ = lean_uint64_dec_eq(v___y_2965_, v___y_2964_);
if (v___x_2966_ == 0)
{
uint64_t v___x_2967_; uint8_t v___x_2968_; 
v___x_2967_ = 8388608ULL;
v___x_2968_ = lean_uint64_dec_eq(v___y_2965_, v___x_2967_);
if (v___x_2968_ == 0)
{
uint32_t v___x_2969_; 
v___x_2969_ = lean_uint64_to_uint32(v___y_2965_);
if (v___y_2963_ == 0)
{
uint32_t v___x_2970_; 
v___x_2970_ = 0;
v___y_2956_ = v___y_2962_;
v___y_2957_ = v___x_2969_;
v___y_2958_ = v___x_2970_;
goto v___jp_2955_;
}
else
{
uint32_t v___x_2971_; 
v___x_2971_ = 2147483648;
v___y_2956_ = v___y_2962_;
v___y_2957_ = v___x_2969_;
v___y_2958_ = v___x_2971_;
goto v___jp_2955_;
}
}
else
{
if (v___y_2963_ == 0)
{
uint32_t v___x_2972_; 
v___x_2972_ = 0;
v___y_2952_ = v___x_2972_;
goto v___jp_2951_;
}
else
{
uint32_t v___x_2973_; 
v___x_2973_ = 2147483648;
v___y_2952_ = v___x_2973_;
goto v___jp_2951_;
}
}
}
else
{
if (v___y_2963_ == 0)
{
uint32_t v___x_2974_; 
v___x_2974_ = 0;
return v___x_2974_;
}
else
{
uint32_t v___x_2975_; 
v___x_2975_ = 2147483648;
return v___x_2975_;
}
}
}
v___jp_2976_:
{
uint32_t v___x_2983_; uint32_t v___x_2984_; uint32_t v___x_2985_; uint32_t v___x_2986_; uint32_t v___x_2987_; 
v___x_2983_ = lean_uint32_land(v___y_2977_, v___y_2980_);
v___x_2984_ = lean_uint32_shift_left(v___x_2983_, v___y_2978_);
v___x_2985_ = lean_uint32_lor(v___y_2982_, v___x_2984_);
v___x_2986_ = lean_uint32_land(v___y_2981_, v___y_2979_);
v___x_2987_ = lean_uint32_lor(v___x_2985_, v___x_2986_);
return v___x_2987_;
}
v___jp_2988_:
{
if (v___y_2993_ == 0)
{
uint32_t v___x_2995_; 
v___x_2995_ = 0;
v___y_2977_ = v___y_2989_;
v___y_2978_ = v___y_2990_;
v___y_2979_ = v___y_2991_;
v___y_2980_ = v___y_2992_;
v___y_2981_ = v___y_2994_;
v___y_2982_ = v___x_2995_;
goto v___jp_2976_;
}
else
{
uint32_t v___x_2996_; 
v___x_2996_ = 2147483648;
v___y_2977_ = v___y_2989_;
v___y_2978_ = v___y_2990_;
v___y_2979_ = v___y_2991_;
v___y_2980_ = v___y_2992_;
v___y_2981_ = v___y_2994_;
v___y_2982_ = v___x_2996_;
goto v___jp_2976_;
}
}
v___jp_2997_:
{
uint64_t v___x_3005_; uint64_t v_encodedExponent_3006_; uint32_t v___x_3007_; uint64_t v___x_3008_; uint8_t v___x_3009_; 
v___x_3005_ = 171ULL;
v_encodedExponent_3006_ = lean_uint64_sub(v___y_2998_, v___x_3005_);
v___x_3007_ = lean_uint64_to_uint32(v_encodedExponent_3006_);
v___x_3008_ = 8388608ULL;
v___x_3009_ = lean_uint64_dec_lt(v___y_3004_, v___x_3008_);
if (v___x_3009_ == 0)
{
uint64_t v___x_3010_; uint32_t v___x_3011_; 
v___x_3010_ = lean_uint64_sub(v___y_3004_, v___x_3008_);
v___x_3011_ = lean_uint64_to_uint32(v___x_3010_);
v___y_2989_ = v___x_3007_;
v___y_2990_ = v___y_2999_;
v___y_2991_ = v___y_3000_;
v___y_2992_ = v___y_3001_;
v___y_2993_ = v___y_3002_;
v___y_2994_ = v___x_3011_;
goto v___jp_2988_;
}
else
{
uint32_t v___x_3012_; 
v___x_3012_ = lean_uint64_to_uint32(v___y_3003_);
v___y_2989_ = v___x_3007_;
v___y_2990_ = v___y_2999_;
v___y_2991_ = v___y_3000_;
v___y_2992_ = v___y_3001_;
v___y_2993_ = v___y_3002_;
v___y_2994_ = v___x_3012_;
goto v___jp_2988_;
}
}
v___jp_3013_:
{
uint64_t v___x_3022_; uint8_t v___x_3023_; 
v___x_3022_ = 425ULL;
v___x_3023_ = lean_uint64_dec_lt(v___x_3022_, v___y_3021_);
if (v___x_3023_ == 0)
{
if (v___y_3019_ == 0)
{
v___y_2998_ = v___y_3021_;
v___y_2999_ = v___y_3015_;
v___y_3000_ = v___y_3016_;
v___y_3001_ = v___y_3017_;
v___y_3002_ = v___y_3018_;
v___y_3003_ = v___y_3020_;
v___y_3004_ = v___y_3014_;
goto v___jp_2997_;
}
else
{
uint64_t v___x_3024_; 
v___x_3024_ = 8388608ULL;
v___y_2998_ = v___y_3021_;
v___y_2999_ = v___y_3015_;
v___y_3000_ = v___y_3016_;
v___y_3001_ = v___y_3017_;
v___y_3002_ = v___y_3018_;
v___y_3003_ = v___y_3020_;
v___y_3004_ = v___x_3024_;
goto v___jp_2997_;
}
}
else
{
if (v___y_3018_ == 0)
{
uint32_t v___x_3025_; 
v___x_3025_ = 2139095040;
return v___x_3025_;
}
else
{
uint32_t v___x_3026_; 
v___x_3026_ = 4286578688;
return v___x_3026_;
}
}
}
v___jp_3027_:
{
uint64_t v___x_3035_; uint8_t v_carry_3036_; 
v___x_3035_ = 16777216ULL;
v_carry_3036_ = lean_uint64_dec_eq(v___y_3034_, v___x_3035_);
if (v_carry_3036_ == 0)
{
v___y_3014_ = v___y_3034_;
v___y_3015_ = v___y_3029_;
v___y_3016_ = v___y_3030_;
v___y_3017_ = v___y_3031_;
v___y_3018_ = v___y_3032_;
v___y_3019_ = v_carry_3036_;
v___y_3020_ = v___y_3033_;
v___y_3021_ = v___y_3028_;
goto v___jp_3013_;
}
else
{
uint64_t v___x_3037_; uint64_t v___x_3038_; 
v___x_3037_ = 1ULL;
v___x_3038_ = lean_uint64_add(v___y_3028_, v___x_3037_);
v___y_3014_ = v___y_3034_;
v___y_3015_ = v___y_3029_;
v___y_3016_ = v___y_3030_;
v___y_3017_ = v___y_3031_;
v___y_3018_ = v___y_3032_;
v___y_3019_ = v_carry_3036_;
v___y_3020_ = v___y_3033_;
v___y_3021_ = v___x_3038_;
goto v___jp_3013_;
}
}
v___jp_3039_:
{
uint64_t v_position_3048_; uint64_t v___x_3049_; uint8_t v___x_3050_; 
v_position_3048_ = lean_uint64_add(v___y_3047_, v___y_3045_);
v___x_3049_ = 172ULL;
v___x_3050_ = lean_uint64_dec_lt(v_position_3048_, v___x_3049_);
if (v___x_3050_ == 0)
{
uint64_t v___x_3051_; uint8_t v___x_3052_; 
v___x_3051_ = 23ULL;
v___x_3052_ = lean_uint64_dec_lt(v___y_3047_, v___x_3051_);
if (v___x_3052_ == 0)
{
uint64_t v___x_3053_; uint8_t v___x_3054_; 
v___x_3053_ = lean_uint64_sub(v___y_3047_, v___x_3051_);
v___x_3054_ = lean_uint64_dec_eq(v___x_3053_, v___y_3046_);
if (v___x_3054_ == 0)
{
uint64_t v___x_3055_; uint8_t v___x_3056_; 
v___x_3055_ = 64ULL;
v___x_3056_ = lean_uint64_dec_lt(v___x_3053_, v___x_3055_);
if (v___x_3056_ == 0)
{
uint8_t v___x_3057_; 
v___x_3057_ = lean_uint64_dec_eq(v___x_3053_, v___x_3055_);
if (v___x_3057_ == 0)
{
v___y_3028_ = v_position_3048_;
v___y_3029_ = v___y_3040_;
v___y_3030_ = v___y_3041_;
v___y_3031_ = v___y_3042_;
v___y_3032_ = v___y_3044_;
v___y_3033_ = v___y_3046_;
v___y_3034_ = v___y_3046_;
goto v___jp_3027_;
}
else
{
uint64_t v___x_3058_; uint8_t v___x_3059_; 
v___x_3058_ = 9223372036854775808ULL;
v___x_3059_ = lean_uint64_dec_lt(v___x_3058_, v___y_3043_);
if (v___x_3059_ == 0)
{
v___y_3028_ = v_position_3048_;
v___y_3029_ = v___y_3040_;
v___y_3030_ = v___y_3041_;
v___y_3031_ = v___y_3042_;
v___y_3032_ = v___y_3044_;
v___y_3033_ = v___y_3046_;
v___y_3034_ = v___y_3046_;
goto v___jp_3027_;
}
else
{
uint64_t v___x_3060_; 
v___x_3060_ = 1ULL;
v___y_3028_ = v_position_3048_;
v___y_3029_ = v___y_3040_;
v___y_3030_ = v___y_3041_;
v___y_3031_ = v___y_3042_;
v___y_3032_ = v___y_3044_;
v___y_3033_ = v___y_3046_;
v___y_3034_ = v___x_3060_;
goto v___jp_3027_;
}
}
}
else
{
uint64_t v_quotient_3061_; uint64_t v___x_3062_; uint64_t v___x_3063_; uint64_t v___x_3064_; uint64_t v_remainder_3065_; uint64_t v___x_3066_; uint64_t v_half_3067_; uint8_t v___x_3068_; 
v_quotient_3061_ = lean_uint64_shift_right(v___y_3043_, v___x_3053_);
v___x_3062_ = 1ULL;
v___x_3063_ = lean_uint64_shift_left(v___x_3062_, v___x_3053_);
v___x_3064_ = lean_uint64_sub(v___x_3063_, v___x_3062_);
v_remainder_3065_ = lean_uint64_land(v___y_3043_, v___x_3064_);
v___x_3066_ = lean_uint64_sub(v___x_3053_, v___x_3062_);
v_half_3067_ = lean_uint64_shift_left(v___x_3062_, v___x_3066_);
v___x_3068_ = lean_uint64_dec_lt(v_remainder_3065_, v_half_3067_);
if (v___x_3068_ == 0)
{
uint8_t v___x_3069_; 
v___x_3069_ = lean_uint64_dec_lt(v_half_3067_, v_remainder_3065_);
if (v___x_3069_ == 0)
{
uint64_t v___x_3070_; uint8_t v___x_3071_; 
v___x_3070_ = lean_uint64_land(v_quotient_3061_, v___x_3062_);
v___x_3071_ = lean_uint64_dec_eq(v___x_3070_, v___y_3046_);
if (v___x_3071_ == 0)
{
uint64_t v___x_3072_; 
v___x_3072_ = lean_uint64_add(v_quotient_3061_, v___x_3062_);
v___y_3028_ = v_position_3048_;
v___y_3029_ = v___y_3040_;
v___y_3030_ = v___y_3041_;
v___y_3031_ = v___y_3042_;
v___y_3032_ = v___y_3044_;
v___y_3033_ = v___y_3046_;
v___y_3034_ = v___x_3072_;
goto v___jp_3027_;
}
else
{
v___y_3028_ = v_position_3048_;
v___y_3029_ = v___y_3040_;
v___y_3030_ = v___y_3041_;
v___y_3031_ = v___y_3042_;
v___y_3032_ = v___y_3044_;
v___y_3033_ = v___y_3046_;
v___y_3034_ = v_quotient_3061_;
goto v___jp_3027_;
}
}
else
{
uint64_t v___x_3073_; 
v___x_3073_ = lean_uint64_add(v_quotient_3061_, v___x_3062_);
v___y_3028_ = v_position_3048_;
v___y_3029_ = v___y_3040_;
v___y_3030_ = v___y_3041_;
v___y_3031_ = v___y_3042_;
v___y_3032_ = v___y_3044_;
v___y_3033_ = v___y_3046_;
v___y_3034_ = v___x_3073_;
goto v___jp_3027_;
}
}
else
{
v___y_3028_ = v_position_3048_;
v___y_3029_ = v___y_3040_;
v___y_3030_ = v___y_3041_;
v___y_3031_ = v___y_3042_;
v___y_3032_ = v___y_3044_;
v___y_3033_ = v___y_3046_;
v___y_3034_ = v_quotient_3061_;
goto v___jp_3027_;
}
}
}
else
{
v___y_3028_ = v_position_3048_;
v___y_3029_ = v___y_3040_;
v___y_3030_ = v___y_3041_;
v___y_3031_ = v___y_3042_;
v___y_3032_ = v___y_3044_;
v___y_3033_ = v___y_3046_;
v___y_3034_ = v___y_3043_;
goto v___jp_3027_;
}
}
else
{
uint64_t v___x_3074_; uint64_t v___x_3075_; 
v___x_3074_ = lean_uint64_sub(v___x_3051_, v___y_3047_);
v___x_3075_ = lean_uint64_shift_left(v___y_3043_, v___x_3074_);
v___y_3028_ = v_position_3048_;
v___y_3029_ = v___y_3040_;
v___y_3030_ = v___y_3041_;
v___y_3031_ = v___y_3042_;
v___y_3032_ = v___y_3044_;
v___y_3033_ = v___y_3046_;
v___y_3034_ = v___x_3075_;
goto v___jp_3027_;
}
}
else
{
uint64_t v___x_3076_; uint8_t v___x_3077_; 
v___x_3076_ = 149ULL;
v___x_3077_ = lean_uint64_dec_lt(v___y_3045_, v___x_3076_);
if (v___x_3077_ == 0)
{
uint64_t v___x_3078_; uint64_t v___x_3079_; 
v___x_3078_ = lean_uint64_sub(v___y_3045_, v___x_3076_);
v___x_3079_ = lean_uint64_shift_left(v___y_3043_, v___x_3078_);
v___y_2962_ = v___y_3041_;
v___y_2963_ = v___y_3044_;
v___y_2964_ = v___y_3046_;
v___y_2965_ = v___x_3079_;
goto v___jp_2961_;
}
else
{
uint64_t v___x_3080_; uint8_t v___x_3081_; 
v___x_3080_ = lean_uint64_sub(v___x_3076_, v___y_3045_);
v___x_3081_ = lean_uint64_dec_eq(v___x_3080_, v___y_3046_);
if (v___x_3081_ == 0)
{
uint64_t v___x_3082_; uint8_t v___x_3083_; 
v___x_3082_ = 64ULL;
v___x_3083_ = lean_uint64_dec_lt(v___x_3080_, v___x_3082_);
if (v___x_3083_ == 0)
{
uint8_t v___x_3084_; 
v___x_3084_ = lean_uint64_dec_eq(v___x_3080_, v___x_3082_);
if (v___x_3084_ == 0)
{
v___y_2962_ = v___y_3041_;
v___y_2963_ = v___y_3044_;
v___y_2964_ = v___y_3046_;
v___y_2965_ = v___y_3046_;
goto v___jp_2961_;
}
else
{
uint64_t v___x_3085_; uint8_t v___x_3086_; 
v___x_3085_ = 9223372036854775808ULL;
v___x_3086_ = lean_uint64_dec_lt(v___x_3085_, v___y_3043_);
if (v___x_3086_ == 0)
{
v___y_2962_ = v___y_3041_;
v___y_2963_ = v___y_3044_;
v___y_2964_ = v___y_3046_;
v___y_2965_ = v___y_3046_;
goto v___jp_2961_;
}
else
{
uint64_t v___x_3087_; 
v___x_3087_ = 1ULL;
v___y_2962_ = v___y_3041_;
v___y_2963_ = v___y_3044_;
v___y_2964_ = v___y_3046_;
v___y_2965_ = v___x_3087_;
goto v___jp_2961_;
}
}
}
else
{
uint64_t v_quotient_3088_; uint64_t v___x_3089_; uint64_t v___x_3090_; uint64_t v___x_3091_; uint64_t v_remainder_3092_; uint64_t v___x_3093_; uint64_t v_half_3094_; uint8_t v___x_3095_; 
v_quotient_3088_ = lean_uint64_shift_right(v___y_3043_, v___x_3080_);
v___x_3089_ = 1ULL;
v___x_3090_ = lean_uint64_shift_left(v___x_3089_, v___x_3080_);
v___x_3091_ = lean_uint64_sub(v___x_3090_, v___x_3089_);
v_remainder_3092_ = lean_uint64_land(v___y_3043_, v___x_3091_);
v___x_3093_ = lean_uint64_sub(v___x_3080_, v___x_3089_);
v_half_3094_ = lean_uint64_shift_left(v___x_3089_, v___x_3093_);
v___x_3095_ = lean_uint64_dec_lt(v_remainder_3092_, v_half_3094_);
if (v___x_3095_ == 0)
{
uint8_t v___x_3096_; 
v___x_3096_ = lean_uint64_dec_lt(v_half_3094_, v_remainder_3092_);
if (v___x_3096_ == 0)
{
uint64_t v___x_3097_; uint8_t v___x_3098_; 
v___x_3097_ = lean_uint64_land(v_quotient_3088_, v___x_3089_);
v___x_3098_ = lean_uint64_dec_eq(v___x_3097_, v___y_3046_);
if (v___x_3098_ == 0)
{
uint64_t v___x_3099_; 
v___x_3099_ = lean_uint64_add(v_quotient_3088_, v___x_3089_);
v___y_2962_ = v___y_3041_;
v___y_2963_ = v___y_3044_;
v___y_2964_ = v___y_3046_;
v___y_2965_ = v___x_3099_;
goto v___jp_2961_;
}
else
{
v___y_2962_ = v___y_3041_;
v___y_2963_ = v___y_3044_;
v___y_2964_ = v___y_3046_;
v___y_2965_ = v_quotient_3088_;
goto v___jp_2961_;
}
}
else
{
uint64_t v___x_3100_; 
v___x_3100_ = lean_uint64_add(v_quotient_3088_, v___x_3089_);
v___y_2962_ = v___y_3041_;
v___y_2963_ = v___y_3044_;
v___y_2964_ = v___y_3046_;
v___y_2965_ = v___x_3100_;
goto v___jp_2961_;
}
}
else
{
v___y_2962_ = v___y_3041_;
v___y_2963_ = v___y_3044_;
v___y_2964_ = v___y_3046_;
v___y_2965_ = v_quotient_3088_;
goto v___jp_2961_;
}
}
}
else
{
v___y_2962_ = v___y_3041_;
v___y_2963_ = v___y_3044_;
v___y_2964_ = v___y_3046_;
v___y_2965_ = v___y_3043_;
goto v___jp_2961_;
}
}
}
}
v___jp_3101_:
{
uint64_t v___x_3111_; uint64_t v___x_3112_; uint8_t v___x_3113_; 
v___x_3111_ = 1ULL;
v___x_3112_ = lean_uint64_shift_right(v___y_3104_, v___x_3111_);
v___x_3113_ = lean_uint64_dec_eq(v___x_3112_, v___y_3109_);
if (v___x_3113_ == 0)
{
uint64_t v___x_3114_; 
v___x_3114_ = lean_uint64_add(v___y_3110_, v___x_3111_);
v___y_3040_ = v___y_3102_;
v___y_3041_ = v___y_3103_;
v___y_3042_ = v___y_3105_;
v___y_3043_ = v___y_3108_;
v___y_3044_ = v___y_3107_;
v___y_3045_ = v___y_3106_;
v___y_3046_ = v___y_3109_;
v___y_3047_ = v___x_3114_;
goto v___jp_3039_;
}
else
{
v___y_3040_ = v___y_3102_;
v___y_3041_ = v___y_3103_;
v___y_3042_ = v___y_3105_;
v___y_3043_ = v___y_3108_;
v___y_3044_ = v___y_3107_;
v___y_3045_ = v___y_3106_;
v___y_3046_ = v___y_3109_;
v___y_3047_ = v___y_3110_;
goto v___jp_3039_;
}
}
v___jp_3115_:
{
uint64_t v___x_3127_; uint8_t v___x_3128_; 
v___x_3127_ = lean_uint64_shift_right(v___y_3119_, v___y_3117_);
v___x_3128_ = lean_uint64_dec_eq(v___x_3127_, v___y_3125_);
if (v___x_3128_ == 0)
{
uint64_t v___x_3129_; 
v___x_3129_ = lean_uint64_add(v___y_3121_, v___y_3117_);
v___y_3102_ = v___y_3116_;
v___y_3103_ = v___y_3118_;
v___y_3104_ = v___y_3126_;
v___y_3105_ = v___y_3120_;
v___y_3106_ = v___y_3124_;
v___y_3107_ = v___y_3123_;
v___y_3108_ = v___y_3122_;
v___y_3109_ = v___y_3125_;
v___y_3110_ = v___x_3129_;
goto v___jp_3101_;
}
else
{
v___y_3102_ = v___y_3116_;
v___y_3103_ = v___y_3118_;
v___y_3104_ = v___y_3126_;
v___y_3105_ = v___y_3120_;
v___y_3106_ = v___y_3124_;
v___y_3107_ = v___y_3123_;
v___y_3108_ = v___y_3122_;
v___y_3109_ = v___y_3125_;
v___y_3110_ = v___y_3121_;
goto v___jp_3101_;
}
}
v___jp_3130_:
{
uint64_t v___x_3140_; uint64_t v___x_3141_; uint8_t v___x_3142_; 
v___x_3140_ = 2ULL;
v___x_3141_ = lean_uint64_shift_right(v___y_3134_, v___x_3140_);
v___x_3142_ = lean_uint64_dec_eq(v___x_3141_, v___y_3138_);
if (v___x_3142_ == 0)
{
v___y_3116_ = v___y_3131_;
v___y_3117_ = v___x_3140_;
v___y_3118_ = v___y_3132_;
v___y_3119_ = v___y_3134_;
v___y_3120_ = v___y_3133_;
v___y_3121_ = v___y_3139_;
v___y_3122_ = v___y_3137_;
v___y_3123_ = v___y_3136_;
v___y_3124_ = v___y_3135_;
v___y_3125_ = v___y_3138_;
v___y_3126_ = v___x_3141_;
goto v___jp_3115_;
}
else
{
v___y_3116_ = v___y_3131_;
v___y_3117_ = v___x_3140_;
v___y_3118_ = v___y_3132_;
v___y_3119_ = v___y_3134_;
v___y_3120_ = v___y_3133_;
v___y_3121_ = v___y_3139_;
v___y_3122_ = v___y_3137_;
v___y_3123_ = v___y_3136_;
v___y_3124_ = v___y_3135_;
v___y_3125_ = v___y_3138_;
v___y_3126_ = v___y_3134_;
goto v___jp_3115_;
}
}
v___jp_3143_:
{
uint64_t v___x_3155_; uint8_t v___x_3156_; 
v___x_3155_ = lean_uint64_shift_right(v___y_3144_, v___y_3153_);
v___x_3156_ = lean_uint64_dec_eq(v___x_3155_, v___y_3152_);
if (v___x_3156_ == 0)
{
uint64_t v___x_3157_; 
v___x_3157_ = lean_uint64_add(v___y_3147_, v___y_3153_);
v___y_3131_ = v___y_3145_;
v___y_3132_ = v___y_3146_;
v___y_3133_ = v___y_3148_;
v___y_3134_ = v___y_3154_;
v___y_3135_ = v___y_3151_;
v___y_3136_ = v___y_3150_;
v___y_3137_ = v___y_3149_;
v___y_3138_ = v___y_3152_;
v___y_3139_ = v___x_3157_;
goto v___jp_3130_;
}
else
{
v___y_3131_ = v___y_3145_;
v___y_3132_ = v___y_3146_;
v___y_3133_ = v___y_3148_;
v___y_3134_ = v___y_3154_;
v___y_3135_ = v___y_3151_;
v___y_3136_ = v___y_3150_;
v___y_3137_ = v___y_3149_;
v___y_3138_ = v___y_3152_;
v___y_3139_ = v___y_3147_;
goto v___jp_3130_;
}
}
v___jp_3158_:
{
uint64_t v___x_3168_; uint64_t v___x_3169_; uint8_t v___x_3170_; 
v___x_3168_ = 4ULL;
v___x_3169_ = lean_uint64_shift_right(v___y_3159_, v___x_3168_);
v___x_3170_ = lean_uint64_dec_eq(v___x_3169_, v___y_3166_);
if (v___x_3170_ == 0)
{
v___y_3144_ = v___y_3159_;
v___y_3145_ = v___y_3160_;
v___y_3146_ = v___y_3161_;
v___y_3147_ = v___y_3167_;
v___y_3148_ = v___y_3162_;
v___y_3149_ = v___y_3165_;
v___y_3150_ = v___y_3164_;
v___y_3151_ = v___y_3163_;
v___y_3152_ = v___y_3166_;
v___y_3153_ = v___x_3168_;
v___y_3154_ = v___x_3169_;
goto v___jp_3143_;
}
else
{
v___y_3144_ = v___y_3159_;
v___y_3145_ = v___y_3160_;
v___y_3146_ = v___y_3161_;
v___y_3147_ = v___y_3167_;
v___y_3148_ = v___y_3162_;
v___y_3149_ = v___y_3165_;
v___y_3150_ = v___y_3164_;
v___y_3151_ = v___y_3163_;
v___y_3152_ = v___y_3166_;
v___y_3153_ = v___x_3168_;
v___y_3154_ = v___y_3159_;
goto v___jp_3143_;
}
}
v___jp_3171_:
{
uint64_t v___x_3183_; uint8_t v___x_3184_; 
v___x_3183_ = lean_uint64_shift_right(v___y_3181_, v___y_3172_);
v___x_3184_ = lean_uint64_dec_eq(v___x_3183_, v___y_3180_);
if (v___x_3184_ == 0)
{
uint64_t v___x_3185_; 
v___x_3185_ = lean_uint64_add(v___y_3176_, v___y_3172_);
v___y_3159_ = v___y_3182_;
v___y_3160_ = v___y_3173_;
v___y_3161_ = v___y_3174_;
v___y_3162_ = v___y_3175_;
v___y_3163_ = v___y_3179_;
v___y_3164_ = v___y_3178_;
v___y_3165_ = v___y_3177_;
v___y_3166_ = v___y_3180_;
v___y_3167_ = v___x_3185_;
goto v___jp_3158_;
}
else
{
v___y_3159_ = v___y_3182_;
v___y_3160_ = v___y_3173_;
v___y_3161_ = v___y_3174_;
v___y_3162_ = v___y_3175_;
v___y_3163_ = v___y_3179_;
v___y_3164_ = v___y_3178_;
v___y_3165_ = v___y_3177_;
v___y_3166_ = v___y_3180_;
v___y_3167_ = v___y_3176_;
goto v___jp_3158_;
}
}
v___jp_3186_:
{
uint64_t v___x_3196_; uint64_t v___x_3197_; uint8_t v___x_3198_; 
v___x_3196_ = 8ULL;
v___x_3197_ = lean_uint64_shift_right(v___y_3194_, v___x_3196_);
v___x_3198_ = lean_uint64_dec_eq(v___x_3197_, v___y_3193_);
if (v___x_3198_ == 0)
{
v___y_3172_ = v___x_3196_;
v___y_3173_ = v___y_3187_;
v___y_3174_ = v___y_3188_;
v___y_3175_ = v___y_3189_;
v___y_3176_ = v___y_3195_;
v___y_3177_ = v___y_3192_;
v___y_3178_ = v___y_3191_;
v___y_3179_ = v___y_3190_;
v___y_3180_ = v___y_3193_;
v___y_3181_ = v___y_3194_;
v___y_3182_ = v___x_3197_;
goto v___jp_3171_;
}
else
{
v___y_3172_ = v___x_3196_;
v___y_3173_ = v___y_3187_;
v___y_3174_ = v___y_3188_;
v___y_3175_ = v___y_3189_;
v___y_3176_ = v___y_3195_;
v___y_3177_ = v___y_3192_;
v___y_3178_ = v___y_3191_;
v___y_3179_ = v___y_3190_;
v___y_3180_ = v___y_3193_;
v___y_3181_ = v___y_3194_;
v___y_3182_ = v___y_3194_;
goto v___jp_3171_;
}
}
v___jp_3199_:
{
uint64_t v___x_3211_; uint8_t v___x_3212_; 
v___x_3211_ = lean_uint64_shift_right(v___y_3203_, v___y_3209_);
v___x_3212_ = lean_uint64_dec_eq(v___x_3211_, v___y_3208_);
if (v___x_3212_ == 0)
{
uint64_t v___x_3213_; 
v___x_3213_ = lean_uint64_add(v___y_3200_, v___y_3209_);
v___y_3187_ = v___y_3201_;
v___y_3188_ = v___y_3202_;
v___y_3189_ = v___y_3204_;
v___y_3190_ = v___y_3207_;
v___y_3191_ = v___y_3206_;
v___y_3192_ = v___y_3205_;
v___y_3193_ = v___y_3208_;
v___y_3194_ = v___y_3210_;
v___y_3195_ = v___x_3213_;
goto v___jp_3186_;
}
else
{
v___y_3187_ = v___y_3201_;
v___y_3188_ = v___y_3202_;
v___y_3189_ = v___y_3204_;
v___y_3190_ = v___y_3207_;
v___y_3191_ = v___y_3206_;
v___y_3192_ = v___y_3205_;
v___y_3193_ = v___y_3208_;
v___y_3194_ = v___y_3210_;
v___y_3195_ = v___y_3200_;
goto v___jp_3186_;
}
}
v___jp_3214_:
{
uint64_t v___x_3224_; uint64_t v___x_3225_; uint8_t v___x_3226_; 
v___x_3224_ = 16ULL;
v___x_3225_ = lean_uint64_shift_right(v___y_3218_, v___x_3224_);
v___x_3226_ = lean_uint64_dec_eq(v___x_3225_, v___y_3222_);
if (v___x_3226_ == 0)
{
v___y_3200_ = v___y_3223_;
v___y_3201_ = v___y_3215_;
v___y_3202_ = v___y_3216_;
v___y_3203_ = v___y_3218_;
v___y_3204_ = v___y_3217_;
v___y_3205_ = v___y_3221_;
v___y_3206_ = v___y_3220_;
v___y_3207_ = v___y_3219_;
v___y_3208_ = v___y_3222_;
v___y_3209_ = v___x_3224_;
v___y_3210_ = v___x_3225_;
goto v___jp_3199_;
}
else
{
v___y_3200_ = v___y_3223_;
v___y_3201_ = v___y_3215_;
v___y_3202_ = v___y_3216_;
v___y_3203_ = v___y_3218_;
v___y_3204_ = v___y_3217_;
v___y_3205_ = v___y_3221_;
v___y_3206_ = v___y_3220_;
v___y_3207_ = v___y_3219_;
v___y_3208_ = v___y_3222_;
v___y_3209_ = v___x_3224_;
v___y_3210_ = v___y_3218_;
goto v___jp_3199_;
}
}
v___jp_3227_:
{
uint64_t v___x_3237_; uint8_t v___x_3238_; 
v___x_3237_ = lean_uint64_shift_right(v___y_3231_, v___y_3235_);
v___x_3238_ = lean_uint64_dec_eq(v___x_3237_, v___y_3234_);
if (v___x_3238_ == 0)
{
v___y_3215_ = v___y_3228_;
v___y_3216_ = v___y_3229_;
v___y_3217_ = v___y_3230_;
v___y_3218_ = v___y_3236_;
v___y_3219_ = v___y_3233_;
v___y_3220_ = v___y_3232_;
v___y_3221_ = v___y_3231_;
v___y_3222_ = v___y_3234_;
v___y_3223_ = v___y_3235_;
goto v___jp_3214_;
}
else
{
v___y_3215_ = v___y_3228_;
v___y_3216_ = v___y_3229_;
v___y_3217_ = v___y_3230_;
v___y_3218_ = v___y_3236_;
v___y_3219_ = v___y_3233_;
v___y_3220_ = v___y_3232_;
v___y_3221_ = v___y_3231_;
v___y_3222_ = v___y_3234_;
v___y_3223_ = v___y_3234_;
goto v___jp_3214_;
}
}
v___jp_3239_:
{
uint64_t v___x_3248_; uint64_t v___x_3249_; uint8_t v___x_3250_; 
v___x_3248_ = lean_uint64_mul(v___y_3246_, v___y_3244_);
v___x_3249_ = 0ULL;
v___x_3250_ = lean_uint64_dec_eq(v___x_3248_, v___x_3249_);
if (v___x_3250_ == 0)
{
uint64_t v___x_3251_; uint64_t v___x_3252_; uint64_t v___x_3253_; uint8_t v___x_3254_; 
v___x_3251_ = lean_uint64_add(v___y_3245_, v___y_3247_);
v___x_3252_ = 32ULL;
v___x_3253_ = lean_uint64_shift_right(v___x_3248_, v___x_3252_);
v___x_3254_ = lean_uint64_dec_eq(v___x_3253_, v___x_3249_);
if (v___x_3254_ == 0)
{
v___y_3228_ = v___y_3240_;
v___y_3229_ = v___y_3241_;
v___y_3230_ = v___y_3242_;
v___y_3231_ = v___x_3248_;
v___y_3232_ = v___y_3243_;
v___y_3233_ = v___x_3251_;
v___y_3234_ = v___x_3249_;
v___y_3235_ = v___x_3252_;
v___y_3236_ = v___x_3253_;
goto v___jp_3227_;
}
else
{
v___y_3228_ = v___y_3240_;
v___y_3229_ = v___y_3241_;
v___y_3230_ = v___y_3242_;
v___y_3231_ = v___x_3248_;
v___y_3232_ = v___y_3243_;
v___y_3233_ = v___x_3251_;
v___y_3234_ = v___x_3249_;
v___y_3235_ = v___x_3252_;
v___y_3236_ = v___x_3248_;
goto v___jp_3227_;
}
}
else
{
if (v___y_3243_ == 0)
{
uint32_t v___x_3255_; 
v___x_3255_ = 0;
return v___x_3255_;
}
else
{
uint32_t v___x_3256_; 
v___x_3256_ = 2147483648;
return v___x_3256_;
}
}
}
v___jp_3257_:
{
uint64_t v___x_3266_; uint64_t v___x_3267_; uint8_t v___x_3268_; 
v___x_3266_ = lean_uint32_to_uint64(v___y_3260_);
v___x_3267_ = 0ULL;
v___x_3268_ = lean_uint64_dec_eq(v___x_3266_, v___x_3267_);
if (v___x_3268_ == 0)
{
uint64_t v___x_3269_; uint64_t v___x_3270_; 
v___x_3269_ = 1ULL;
v___x_3270_ = lean_uint64_sub(v___x_3266_, v___x_3269_);
v___y_3240_ = v___y_3258_;
v___y_3241_ = v___y_3259_;
v___y_3242_ = v___y_3261_;
v___y_3243_ = v___y_3262_;
v___y_3244_ = v___y_3263_;
v___y_3245_ = v___y_3265_;
v___y_3246_ = v___y_3264_;
v___y_3247_ = v___x_3270_;
goto v___jp_3239_;
}
else
{
v___y_3240_ = v___y_3258_;
v___y_3241_ = v___y_3259_;
v___y_3242_ = v___y_3261_;
v___y_3243_ = v___y_3262_;
v___y_3244_ = v___y_3263_;
v___y_3245_ = v___y_3265_;
v___y_3246_ = v___y_3264_;
v___y_3247_ = v___x_3267_;
goto v___jp_3239_;
}
}
v___jp_3271_:
{
uint64_t v___x_3280_; uint64_t v___x_3281_; uint8_t v___x_3282_; 
v___x_3280_ = lean_uint32_to_uint64(v___y_3272_);
v___x_3281_ = 0ULL;
v___x_3282_ = lean_uint64_dec_eq(v___x_3280_, v___x_3281_);
if (v___x_3282_ == 0)
{
uint64_t v___x_3283_; uint64_t v___x_3284_; 
v___x_3283_ = 1ULL;
v___x_3284_ = lean_uint64_sub(v___x_3280_, v___x_3283_);
v___y_3258_ = v___y_3273_;
v___y_3259_ = v___y_3274_;
v___y_3260_ = v___y_3276_;
v___y_3261_ = v___y_3275_;
v___y_3262_ = v___y_3277_;
v___y_3263_ = v___y_3279_;
v___y_3264_ = v___y_3278_;
v___y_3265_ = v___x_3284_;
goto v___jp_3257_;
}
else
{
v___y_3258_ = v___y_3273_;
v___y_3259_ = v___y_3274_;
v___y_3260_ = v___y_3276_;
v___y_3261_ = v___y_3275_;
v___y_3262_ = v___y_3277_;
v___y_3263_ = v___y_3279_;
v___y_3264_ = v___y_3278_;
v___y_3265_ = v___x_3281_;
goto v___jp_3257_;
}
}
v___jp_3285_:
{
uint32_t v___x_3294_; uint8_t v___x_3295_; 
v___x_3294_ = 0;
v___x_3295_ = lean_uint32_dec_eq(v___y_3290_, v___x_3294_);
if (v___x_3295_ == 0)
{
uint64_t v___x_3296_; uint64_t v___x_3297_; uint64_t v___x_3298_; 
v___x_3296_ = lean_uint32_to_uint64(v___y_3287_);
v___x_3297_ = 8388608ULL;
v___x_3298_ = lean_uint64_lor(v___x_3296_, v___x_3297_);
v___y_3272_ = v___y_3286_;
v___y_3273_ = v___y_3288_;
v___y_3274_ = v___y_3289_;
v___y_3275_ = v___y_3291_;
v___y_3276_ = v___y_3290_;
v___y_3277_ = v___y_3292_;
v___y_3278_ = v___y_3293_;
v___y_3279_ = v___x_3298_;
goto v___jp_3271_;
}
else
{
uint64_t v___x_3299_; 
v___x_3299_ = lean_uint32_to_uint64(v___y_3287_);
v___y_3272_ = v___y_3286_;
v___y_3273_ = v___y_3288_;
v___y_3274_ = v___y_3289_;
v___y_3275_ = v___y_3291_;
v___y_3276_ = v___y_3290_;
v___y_3277_ = v___y_3292_;
v___y_3278_ = v___y_3293_;
v___y_3279_ = v___x_3299_;
goto v___jp_3271_;
}
}
v___jp_3300_:
{
uint32_t v___x_3306_; uint32_t v_xFraction_3307_; uint32_t v_yFraction_3308_; uint32_t v___x_3309_; uint8_t v___x_3310_; 
v___x_3306_ = 8388607;
v_xFraction_3307_ = lean_uint32_land(v_x_2949_, v___x_3306_);
v_yFraction_3308_ = lean_uint32_land(v_y_2950_, v___x_3306_);
v___x_3309_ = 0;
v___x_3310_ = lean_uint32_dec_eq(v___y_3301_, v___x_3309_);
if (v___x_3310_ == 0)
{
uint64_t v___x_3311_; uint64_t v___x_3312_; uint64_t v___x_3313_; 
v___x_3311_ = lean_uint32_to_uint64(v_xFraction_3307_);
v___x_3312_ = 8388608ULL;
v___x_3313_ = lean_uint64_lor(v___x_3311_, v___x_3312_);
v___y_3286_ = v___y_3301_;
v___y_3287_ = v_yFraction_3308_;
v___y_3288_ = v___y_3302_;
v___y_3289_ = v___x_3306_;
v___y_3290_ = v___y_3304_;
v___y_3291_ = v___y_3303_;
v___y_3292_ = v___y_3305_;
v___y_3293_ = v___x_3313_;
goto v___jp_3285_;
}
else
{
uint64_t v___x_3314_; 
v___x_3314_ = lean_uint32_to_uint64(v_xFraction_3307_);
v___y_3286_ = v___y_3301_;
v___y_3287_ = v_yFraction_3308_;
v___y_3288_ = v___y_3302_;
v___y_3289_ = v___x_3306_;
v___y_3290_ = v___y_3304_;
v___y_3291_ = v___y_3303_;
v___y_3292_ = v___y_3305_;
v___y_3293_ = v___x_3314_;
goto v___jp_3285_;
}
}
v___jp_3315_:
{
uint8_t v___x_3320_; 
v___x_3320_ = 1;
v___y_3301_ = v___y_3316_;
v___y_3302_ = v___y_3317_;
v___y_3303_ = v___y_3319_;
v___y_3304_ = v___y_3318_;
v___y_3305_ = v___x_3320_;
goto v___jp_3300_;
}
v___jp_3321_:
{
if (v___y_3322_ == 0)
{
if (v___y_3328_ == 0)
{
v___y_3301_ = v___y_3323_;
v___y_3302_ = v___y_3325_;
v___y_3303_ = v___y_3327_;
v___y_3304_ = v___y_3326_;
v___y_3305_ = v___y_3324_;
goto v___jp_3300_;
}
else
{
v___y_3316_ = v___y_3323_;
v___y_3317_ = v___y_3325_;
v___y_3318_ = v___y_3326_;
v___y_3319_ = v___y_3327_;
goto v___jp_3315_;
}
}
else
{
if (v___y_3328_ == 0)
{
v___y_3316_ = v___y_3323_;
v___y_3317_ = v___y_3325_;
v___y_3318_ = v___y_3326_;
v___y_3319_ = v___y_3327_;
goto v___jp_3315_;
}
else
{
v___y_3301_ = v___y_3323_;
v___y_3302_ = v___y_3325_;
v___y_3303_ = v___y_3327_;
v___y_3304_ = v___y_3326_;
v___y_3305_ = v___y_3324_;
goto v___jp_3300_;
}
}
}
v___jp_3329_:
{
uint32_t v___x_3336_; uint32_t v___x_3337_; uint32_t v___x_3338_; uint8_t v___x_3339_; 
v___x_3336_ = 2147483648;
v___x_3337_ = lean_uint32_land(v_y_2950_, v___x_3336_);
v___x_3338_ = 0;
v___x_3339_ = lean_uint32_dec_eq(v___x_3337_, v___x_3338_);
if (v___x_3339_ == 0)
{
uint8_t v___x_3340_; 
v___x_3340_ = 1;
v___y_3322_ = v___y_3335_;
v___y_3323_ = v___y_3330_;
v___y_3324_ = v___y_3331_;
v___y_3325_ = v___y_3332_;
v___y_3326_ = v___y_3334_;
v___y_3327_ = v___y_3333_;
v___y_3328_ = v___x_3340_;
goto v___jp_3321_;
}
else
{
v___y_3322_ = v___y_3335_;
v___y_3323_ = v___y_3330_;
v___y_3324_ = v___y_3331_;
v___y_3325_ = v___y_3332_;
v___y_3326_ = v___y_3334_;
v___y_3327_ = v___y_3333_;
v___y_3328_ = v___y_3331_;
goto v___jp_3321_;
}
}
v___jp_3341_:
{
if (v___y_3342_ == 0)
{
uint32_t v___x_3343_; uint32_t v___x_3344_; uint32_t v___x_3345_; uint32_t v_xExponent_3346_; uint32_t v___x_3347_; uint32_t v_yExponent_3348_; uint32_t v___x_3349_; uint32_t v___x_3350_; uint32_t v___x_3351_; uint8_t v___x_3352_; 
v___x_3343_ = 23;
v___x_3344_ = lean_uint32_shift_right(v_x_2949_, v___x_3343_);
v___x_3345_ = 255;
v_xExponent_3346_ = lean_uint32_land(v___x_3344_, v___x_3345_);
v___x_3347_ = lean_uint32_shift_right(v_y_2950_, v___x_3343_);
v_yExponent_3348_ = lean_uint32_land(v___x_3347_, v___x_3345_);
v___x_3349_ = 2147483648;
v___x_3350_ = lean_uint32_land(v_x_2949_, v___x_3349_);
v___x_3351_ = 0;
v___x_3352_ = lean_uint32_dec_eq(v___x_3350_, v___x_3351_);
if (v___x_3352_ == 0)
{
uint8_t v___x_3353_; 
v___x_3353_ = 1;
v___y_3330_ = v_xExponent_3346_;
v___y_3331_ = v___y_3342_;
v___y_3332_ = v___x_3343_;
v___y_3333_ = v___x_3345_;
v___y_3334_ = v_yExponent_3348_;
v___y_3335_ = v___x_3353_;
goto v___jp_3329_;
}
else
{
v___y_3330_ = v_xExponent_3346_;
v___y_3331_ = v___y_3342_;
v___y_3332_ = v___x_3343_;
v___y_3333_ = v___x_3345_;
v___y_3334_ = v_yExponent_3348_;
v___y_3335_ = v___y_3342_;
goto v___jp_3329_;
}
}
else
{
lean_object* v___x_3354_; lean_object* v___x_3355_; lean_object* v___x_3356_; uint32_t v___x_3357_; 
v___x_3354_ = lean_uint32_to_nat(v_x_2949_);
v___x_3355_ = lean_uint32_to_nat(v_y_2950_);
v___x_3356_ = lp_floatlib_FloatLib_Floats_Formats_BinaryInterchange_Model_MulBackend_word___at___00FloatLib_Floats_Formats_BinaryInterchange_Configured_Plan_softwareMul32Certified_spec__1(v___x_3354_, v___x_3355_);
v___x_3357_ = lean_uint32_of_nat(v___x_3356_);
lean_dec(v___x_3356_);
return v___x_3357_;
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_FastMul_mul___boxed(lean_object* v_x_3364_, lean_object* v_y_3365_){
_start:
{
uint32_t v_x_boxed_3366_; uint32_t v_y_boxed_3367_; uint32_t v_res_3368_; lean_object* v_r_3369_; 
v_x_boxed_3366_ = lean_unbox_uint32(v_x_3364_);
lean_dec(v_x_3364_);
v_y_boxed_3367_ = lean_unbox_uint32(v_y_3365_);
lean_dec(v_y_3365_);
v_res_3368_ = lp_competition_Submission_FastMul_mul(v_x_boxed_3366_, v_y_boxed_3367_);
v_r_3369_ = lean_box_uint32(v_res_3368_);
return v_r_3369_;
}
}
static uint8_t _init_lp_competition_Submission_FastMul_Plan(void){
_start:
{
uint8_t v___x_3371_; 
v___x_3371_ = 2;
return v___x_3371_;
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_FastMul_dec(uint32_t v_z_3372_){
_start:
{
lean_object* v___x_3373_; 
v___x_3373_ = lean_uint32_to_nat(v_z_3372_);
return v___x_3373_;
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_FastMul_dec___boxed(lean_object* v_z_3374_){
_start:
{
uint32_t v_z_boxed_3375_; lean_object* v_res_3376_; 
v_z_boxed_3375_ = lean_unbox_uint32(v_z_3374_);
lean_dec(v_z_3374_);
v_res_3376_ = lp_competition_Submission_FastMul_dec(v_z_boxed_3375_);
return v_res_3376_;
}
}
LEAN_EXPORT uint32_t lp_competition_Submission_LowScale_roundLow(uint8_t v_sign_3377_, uint64_t v_product_3378_, uint64_t v_scale_3379_){
_start:
{
uint32_t v___y_3381_; uint32_t v___y_3385_; uint32_t v___y_3386_; uint64_t v___x_3390_; uint64_t v___y_3392_; uint8_t v___x_3403_; 
v___x_3390_ = 0ULL;
v___x_3403_ = lean_uint64_dec_eq(v_product_3378_, v___x_3390_);
if (v___x_3403_ == 0)
{
uint64_t v___x_3404_; uint64_t v___x_3405_; uint8_t v___x_3406_; 
v___x_3404_ = 149ULL;
v___x_3405_ = lean_uint64_sub(v___x_3404_, v_scale_3379_);
v___x_3406_ = lean_uint64_dec_eq(v___x_3405_, v___x_3390_);
if (v___x_3406_ == 0)
{
uint64_t v___x_3407_; uint8_t v___x_3408_; 
v___x_3407_ = 64ULL;
v___x_3408_ = lean_uint64_dec_lt(v___x_3405_, v___x_3407_);
if (v___x_3408_ == 0)
{
uint8_t v___x_3409_; 
v___x_3409_ = lean_uint64_dec_eq(v___x_3405_, v___x_3407_);
if (v___x_3409_ == 0)
{
v___y_3392_ = v___x_3390_;
goto v___jp_3391_;
}
else
{
uint64_t v___x_3410_; uint8_t v___x_3411_; 
v___x_3410_ = 9223372036854775808ULL;
v___x_3411_ = lean_uint64_dec_lt(v___x_3410_, v_product_3378_);
if (v___x_3411_ == 0)
{
v___y_3392_ = v___x_3390_;
goto v___jp_3391_;
}
else
{
uint64_t v___x_3412_; 
v___x_3412_ = 1ULL;
v___y_3392_ = v___x_3412_;
goto v___jp_3391_;
}
}
}
else
{
uint64_t v_quotient_3413_; uint64_t v___x_3414_; uint64_t v___x_3415_; uint64_t v___x_3416_; uint64_t v_remainder_3417_; uint64_t v___x_3418_; uint64_t v_half_3419_; uint8_t v___x_3420_; 
v_quotient_3413_ = lean_uint64_shift_right(v_product_3378_, v___x_3405_);
v___x_3414_ = 1ULL;
v___x_3415_ = lean_uint64_shift_left(v___x_3414_, v___x_3405_);
v___x_3416_ = lean_uint64_sub(v___x_3415_, v___x_3414_);
v_remainder_3417_ = lean_uint64_land(v_product_3378_, v___x_3416_);
v___x_3418_ = lean_uint64_sub(v___x_3405_, v___x_3414_);
v_half_3419_ = lean_uint64_shift_left(v___x_3414_, v___x_3418_);
v___x_3420_ = lean_uint64_dec_lt(v_remainder_3417_, v_half_3419_);
if (v___x_3420_ == 0)
{
uint8_t v___x_3421_; 
v___x_3421_ = lean_uint64_dec_lt(v_half_3419_, v_remainder_3417_);
if (v___x_3421_ == 0)
{
uint64_t v___x_3422_; uint8_t v___x_3423_; 
v___x_3422_ = lean_uint64_land(v_quotient_3413_, v___x_3414_);
v___x_3423_ = lean_uint64_dec_eq(v___x_3422_, v___x_3390_);
if (v___x_3423_ == 0)
{
uint64_t v___x_3424_; 
v___x_3424_ = lean_uint64_add(v_quotient_3413_, v___x_3414_);
v___y_3392_ = v___x_3424_;
goto v___jp_3391_;
}
else
{
v___y_3392_ = v_quotient_3413_;
goto v___jp_3391_;
}
}
else
{
uint64_t v___x_3425_; 
v___x_3425_ = lean_uint64_add(v_quotient_3413_, v___x_3414_);
v___y_3392_ = v___x_3425_;
goto v___jp_3391_;
}
}
else
{
v___y_3392_ = v_quotient_3413_;
goto v___jp_3391_;
}
}
}
else
{
v___y_3392_ = v_product_3378_;
goto v___jp_3391_;
}
}
else
{
if (v_sign_3377_ == 0)
{
uint32_t v___x_3426_; 
v___x_3426_ = 0;
return v___x_3426_;
}
else
{
uint32_t v___x_3427_; 
v___x_3427_ = 2147483648;
return v___x_3427_;
}
}
v___jp_3380_:
{
uint32_t v___x_3382_; uint32_t v___x_3383_; 
v___x_3382_ = 8388608;
v___x_3383_ = lean_uint32_lor(v___y_3381_, v___x_3382_);
return v___x_3383_;
}
v___jp_3384_:
{
uint32_t v___x_3387_; uint32_t v___x_3388_; uint32_t v___x_3389_; 
v___x_3387_ = 8388607;
v___x_3388_ = lean_uint32_land(v___y_3385_, v___x_3387_);
v___x_3389_ = lean_uint32_lor(v___y_3386_, v___x_3388_);
return v___x_3389_;
}
v___jp_3391_:
{
uint8_t v___x_3393_; 
v___x_3393_ = lean_uint64_dec_eq(v___y_3392_, v___x_3390_);
if (v___x_3393_ == 0)
{
uint64_t v___x_3394_; uint8_t v___x_3395_; 
v___x_3394_ = 8388608ULL;
v___x_3395_ = lean_uint64_dec_eq(v___y_3392_, v___x_3394_);
if (v___x_3395_ == 0)
{
uint32_t v___x_3396_; 
v___x_3396_ = lean_uint64_to_uint32(v___y_3392_);
if (v_sign_3377_ == 0)
{
uint32_t v___x_3397_; 
v___x_3397_ = 0;
v___y_3385_ = v___x_3396_;
v___y_3386_ = v___x_3397_;
goto v___jp_3384_;
}
else
{
uint32_t v___x_3398_; 
v___x_3398_ = 2147483648;
v___y_3385_ = v___x_3396_;
v___y_3386_ = v___x_3398_;
goto v___jp_3384_;
}
}
else
{
if (v_sign_3377_ == 0)
{
uint32_t v___x_3399_; 
v___x_3399_ = 0;
v___y_3381_ = v___x_3399_;
goto v___jp_3380_;
}
else
{
uint32_t v___x_3400_; 
v___x_3400_ = 2147483648;
v___y_3381_ = v___x_3400_;
goto v___jp_3380_;
}
}
}
else
{
if (v_sign_3377_ == 0)
{
uint32_t v___x_3401_; 
v___x_3401_ = 0;
return v___x_3401_;
}
else
{
uint32_t v___x_3402_; 
v___x_3402_ = 2147483648;
return v___x_3402_;
}
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_LowScale_roundLow___boxed(lean_object* v_sign_3428_, lean_object* v_product_3429_, lean_object* v_scale_3430_){
_start:
{
uint8_t v_sign_boxed_3431_; uint64_t v_product_boxed_3432_; uint64_t v_scale_boxed_3433_; uint32_t v_res_3434_; lean_object* v_r_3435_; 
v_sign_boxed_3431_ = lean_unbox(v_sign_3428_);
v_product_boxed_3432_ = lean_unbox_uint64(v_product_3429_);
lean_dec_ref(v_product_3429_);
v_scale_boxed_3433_ = lean_unbox_uint64(v_scale_3430_);
lean_dec_ref(v_scale_3430_);
v_res_3434_ = lp_competition_Submission_LowScale_roundLow(v_sign_boxed_3431_, v_product_boxed_3432_, v_scale_boxed_3433_);
v_r_3435_ = lean_box_uint32(v_res_3434_);
return v_r_3435_;
}
}
LEAN_EXPORT uint32_t lp_competition_Submission_LowScale_roundSelect(uint8_t v_sign_3436_, uint64_t v_product_3437_, uint64_t v_scale_3438_){
_start:
{
uint32_t v___y_3440_; uint32_t v___y_3444_; uint32_t v___y_3445_; uint32_t v___y_3450_; uint32_t v___y_3454_; uint32_t v___y_3455_; uint64_t v___y_3460_; uint64_t v___y_3461_; uint32_t v___y_3473_; uint32_t v___y_3474_; uint32_t v___y_3475_; uint32_t v___y_3485_; uint32_t v___y_3486_; uint64_t v___y_3490_; uint64_t v___y_3491_; uint64_t v___y_3492_; uint64_t v___y_3502_; uint8_t v___y_3503_; uint64_t v___y_3504_; uint64_t v___y_3505_; uint64_t v___y_3512_; uint64_t v___y_3513_; uint64_t v___y_3514_; uint64_t v___y_3520_; uint64_t v___y_3521_; uint64_t v___y_3576_; uint64_t v___y_3577_; uint64_t v___y_3578_; uint64_t v___y_3584_; uint64_t v___y_3585_; uint64_t v___y_3586_; uint64_t v___y_3587_; uint64_t v___y_3588_; uint64_t v___y_3593_; uint64_t v___y_3594_; uint64_t v___y_3595_; uint64_t v___y_3600_; uint64_t v___y_3601_; uint64_t v___y_3602_; uint64_t v___y_3603_; uint64_t v___y_3604_; uint64_t v___y_3609_; uint64_t v___y_3610_; uint64_t v___y_3611_; uint64_t v___y_3616_; uint64_t v___y_3617_; uint64_t v___y_3618_; uint64_t v___y_3619_; uint64_t v___y_3620_; uint64_t v___y_3625_; uint64_t v___y_3626_; uint64_t v___y_3627_; uint64_t v___y_3632_; uint64_t v___y_3633_; uint64_t v___y_3634_; uint64_t v___y_3635_; uint64_t v___y_3636_; uint64_t v___y_3641_; uint64_t v___y_3642_; uint64_t v___y_3643_; uint64_t v___y_3648_; uint64_t v___y_3649_; uint64_t v___y_3650_; uint64_t v___x_3661_; uint8_t v___x_3662_; 
v___x_3661_ = 281474976710656ULL;
v___x_3662_ = lean_uint64_dec_lt(v_product_3437_, v___x_3661_);
if (v___x_3662_ == 0)
{
goto v___jp_3653_;
}
else
{
uint64_t v___x_3663_; uint8_t v___x_3664_; 
v___x_3663_ = 123ULL;
v___x_3664_ = lean_uint64_dec_le(v_scale_3438_, v___x_3663_);
if (v___x_3664_ == 0)
{
goto v___jp_3653_;
}
else
{
uint64_t v___x_3665_; uint64_t v___y_3667_; uint8_t v___x_3678_; 
v___x_3665_ = 0ULL;
v___x_3678_ = lean_uint64_dec_eq(v_product_3437_, v___x_3665_);
if (v___x_3678_ == 0)
{
uint64_t v___x_3679_; uint64_t v___x_3680_; uint8_t v___x_3681_; 
v___x_3679_ = 149ULL;
v___x_3680_ = lean_uint64_sub(v___x_3679_, v_scale_3438_);
v___x_3681_ = lean_uint64_dec_eq(v___x_3680_, v___x_3665_);
if (v___x_3681_ == 0)
{
uint64_t v___x_3682_; uint8_t v___x_3683_; 
v___x_3682_ = 64ULL;
v___x_3683_ = lean_uint64_dec_lt(v___x_3680_, v___x_3682_);
if (v___x_3683_ == 0)
{
uint8_t v___x_3684_; 
v___x_3684_ = lean_uint64_dec_eq(v___x_3680_, v___x_3682_);
if (v___x_3684_ == 0)
{
v___y_3667_ = v___x_3665_;
goto v___jp_3666_;
}
else
{
uint64_t v___x_3685_; uint8_t v___x_3686_; 
v___x_3685_ = 9223372036854775808ULL;
v___x_3686_ = lean_uint64_dec_lt(v___x_3685_, v_product_3437_);
if (v___x_3686_ == 0)
{
v___y_3667_ = v___x_3665_;
goto v___jp_3666_;
}
else
{
uint64_t v___x_3687_; 
v___x_3687_ = 1ULL;
v___y_3667_ = v___x_3687_;
goto v___jp_3666_;
}
}
}
else
{
uint64_t v_quotient_3688_; uint64_t v___x_3689_; uint64_t v___x_3690_; uint64_t v___x_3691_; uint64_t v_remainder_3692_; uint64_t v___x_3693_; uint64_t v_half_3694_; uint8_t v___x_3695_; 
v_quotient_3688_ = lean_uint64_shift_right(v_product_3437_, v___x_3680_);
v___x_3689_ = 1ULL;
v___x_3690_ = lean_uint64_shift_left(v___x_3689_, v___x_3680_);
v___x_3691_ = lean_uint64_sub(v___x_3690_, v___x_3689_);
v_remainder_3692_ = lean_uint64_land(v_product_3437_, v___x_3691_);
v___x_3693_ = lean_uint64_sub(v___x_3680_, v___x_3689_);
v_half_3694_ = lean_uint64_shift_left(v___x_3689_, v___x_3693_);
v___x_3695_ = lean_uint64_dec_lt(v_remainder_3692_, v_half_3694_);
if (v___x_3695_ == 0)
{
uint8_t v___x_3696_; 
v___x_3696_ = lean_uint64_dec_lt(v_half_3694_, v_remainder_3692_);
if (v___x_3696_ == 0)
{
uint64_t v___x_3697_; uint8_t v___x_3698_; 
v___x_3697_ = lean_uint64_land(v_quotient_3688_, v___x_3689_);
v___x_3698_ = lean_uint64_dec_eq(v___x_3697_, v___x_3665_);
if (v___x_3698_ == 0)
{
uint64_t v___x_3699_; 
v___x_3699_ = lean_uint64_add(v_quotient_3688_, v___x_3689_);
v___y_3667_ = v___x_3699_;
goto v___jp_3666_;
}
else
{
v___y_3667_ = v_quotient_3688_;
goto v___jp_3666_;
}
}
else
{
uint64_t v___x_3700_; 
v___x_3700_ = lean_uint64_add(v_quotient_3688_, v___x_3689_);
v___y_3667_ = v___x_3700_;
goto v___jp_3666_;
}
}
else
{
v___y_3667_ = v_quotient_3688_;
goto v___jp_3666_;
}
}
}
else
{
v___y_3667_ = v_product_3437_;
goto v___jp_3666_;
}
}
else
{
if (v_sign_3436_ == 0)
{
uint32_t v___x_3701_; 
v___x_3701_ = 0;
return v___x_3701_;
}
else
{
uint32_t v___x_3702_; 
v___x_3702_ = 2147483648;
return v___x_3702_;
}
}
v___jp_3666_:
{
uint8_t v___x_3668_; 
v___x_3668_ = lean_uint64_dec_eq(v___y_3667_, v___x_3665_);
if (v___x_3668_ == 0)
{
uint64_t v___x_3669_; uint8_t v___x_3670_; 
v___x_3669_ = 8388608ULL;
v___x_3670_ = lean_uint64_dec_eq(v___y_3667_, v___x_3669_);
if (v___x_3670_ == 0)
{
uint32_t v___x_3671_; 
v___x_3671_ = lean_uint64_to_uint32(v___y_3667_);
if (v_sign_3436_ == 0)
{
uint32_t v___x_3672_; 
v___x_3672_ = 0;
v___y_3444_ = v___x_3671_;
v___y_3445_ = v___x_3672_;
goto v___jp_3443_;
}
else
{
uint32_t v___x_3673_; 
v___x_3673_ = 2147483648;
v___y_3444_ = v___x_3671_;
v___y_3445_ = v___x_3673_;
goto v___jp_3443_;
}
}
else
{
if (v_sign_3436_ == 0)
{
uint32_t v___x_3674_; 
v___x_3674_ = 0;
v___y_3440_ = v___x_3674_;
goto v___jp_3439_;
}
else
{
uint32_t v___x_3675_; 
v___x_3675_ = 2147483648;
v___y_3440_ = v___x_3675_;
goto v___jp_3439_;
}
}
}
else
{
if (v_sign_3436_ == 0)
{
uint32_t v___x_3676_; 
v___x_3676_ = 0;
return v___x_3676_;
}
else
{
uint32_t v___x_3677_; 
v___x_3677_ = 2147483648;
return v___x_3677_;
}
}
}
}
}
v___jp_3439_:
{
uint32_t v___x_3441_; uint32_t v___x_3442_; 
v___x_3441_ = 8388608;
v___x_3442_ = lean_uint32_lor(v___y_3440_, v___x_3441_);
return v___x_3442_;
}
v___jp_3443_:
{
uint32_t v___x_3446_; uint32_t v___x_3447_; uint32_t v___x_3448_; 
v___x_3446_ = 8388607;
v___x_3447_ = lean_uint32_land(v___y_3444_, v___x_3446_);
v___x_3448_ = lean_uint32_lor(v___y_3445_, v___x_3447_);
return v___x_3448_;
}
v___jp_3449_:
{
uint32_t v___x_3451_; uint32_t v___x_3452_; 
v___x_3451_ = 8388608;
v___x_3452_ = lean_uint32_lor(v___y_3450_, v___x_3451_);
return v___x_3452_;
}
v___jp_3453_:
{
uint32_t v___x_3456_; uint32_t v___x_3457_; uint32_t v___x_3458_; 
v___x_3456_ = 8388607;
v___x_3457_ = lean_uint32_land(v___y_3454_, v___x_3456_);
v___x_3458_ = lean_uint32_lor(v___y_3455_, v___x_3457_);
return v___x_3458_;
}
v___jp_3459_:
{
uint8_t v___x_3462_; 
v___x_3462_ = lean_uint64_dec_eq(v___y_3461_, v___y_3460_);
if (v___x_3462_ == 0)
{
uint64_t v___x_3463_; uint8_t v___x_3464_; 
v___x_3463_ = 8388608ULL;
v___x_3464_ = lean_uint64_dec_eq(v___y_3461_, v___x_3463_);
if (v___x_3464_ == 0)
{
uint32_t v___x_3465_; 
v___x_3465_ = lean_uint64_to_uint32(v___y_3461_);
if (v_sign_3436_ == 0)
{
uint32_t v___x_3466_; 
v___x_3466_ = 0;
v___y_3454_ = v___x_3465_;
v___y_3455_ = v___x_3466_;
goto v___jp_3453_;
}
else
{
uint32_t v___x_3467_; 
v___x_3467_ = 2147483648;
v___y_3454_ = v___x_3465_;
v___y_3455_ = v___x_3467_;
goto v___jp_3453_;
}
}
else
{
if (v_sign_3436_ == 0)
{
uint32_t v___x_3468_; 
v___x_3468_ = 0;
v___y_3450_ = v___x_3468_;
goto v___jp_3449_;
}
else
{
uint32_t v___x_3469_; 
v___x_3469_ = 2147483648;
v___y_3450_ = v___x_3469_;
goto v___jp_3449_;
}
}
}
else
{
if (v_sign_3436_ == 0)
{
uint32_t v___x_3470_; 
v___x_3470_ = 0;
return v___x_3470_;
}
else
{
uint32_t v___x_3471_; 
v___x_3471_ = 2147483648;
return v___x_3471_;
}
}
}
v___jp_3472_:
{
uint32_t v___x_3476_; uint32_t v___x_3477_; uint32_t v___x_3478_; uint32_t v___x_3479_; uint32_t v___x_3480_; uint32_t v___x_3481_; uint32_t v___x_3482_; uint32_t v___x_3483_; 
v___x_3476_ = 255;
v___x_3477_ = lean_uint32_land(v___y_3473_, v___x_3476_);
v___x_3478_ = 23;
v___x_3479_ = lean_uint32_shift_left(v___x_3477_, v___x_3478_);
v___x_3480_ = lean_uint32_lor(v___y_3475_, v___x_3479_);
v___x_3481_ = 8388607;
v___x_3482_ = lean_uint32_land(v___y_3474_, v___x_3481_);
v___x_3483_ = lean_uint32_lor(v___x_3480_, v___x_3482_);
return v___x_3483_;
}
v___jp_3484_:
{
if (v_sign_3436_ == 0)
{
uint32_t v___x_3487_; 
v___x_3487_ = 0;
v___y_3473_ = v___y_3485_;
v___y_3474_ = v___y_3486_;
v___y_3475_ = v___x_3487_;
goto v___jp_3472_;
}
else
{
uint32_t v___x_3488_; 
v___x_3488_ = 2147483648;
v___y_3473_ = v___y_3485_;
v___y_3474_ = v___y_3486_;
v___y_3475_ = v___x_3488_;
goto v___jp_3472_;
}
}
v___jp_3489_:
{
uint64_t v___x_3493_; uint64_t v_encodedExponent_3494_; uint32_t v___x_3495_; uint64_t v___x_3496_; uint8_t v___x_3497_; 
v___x_3493_ = 171ULL;
v_encodedExponent_3494_ = lean_uint64_sub(v___y_3490_, v___x_3493_);
v___x_3495_ = lean_uint64_to_uint32(v_encodedExponent_3494_);
v___x_3496_ = 8388608ULL;
v___x_3497_ = lean_uint64_dec_lt(v___y_3492_, v___x_3496_);
if (v___x_3497_ == 0)
{
uint64_t v___x_3498_; uint32_t v___x_3499_; 
v___x_3498_ = lean_uint64_sub(v___y_3492_, v___x_3496_);
v___x_3499_ = lean_uint64_to_uint32(v___x_3498_);
v___y_3485_ = v___x_3495_;
v___y_3486_ = v___x_3499_;
goto v___jp_3484_;
}
else
{
uint32_t v___x_3500_; 
v___x_3500_ = lean_uint64_to_uint32(v___y_3491_);
v___y_3485_ = v___x_3495_;
v___y_3486_ = v___x_3500_;
goto v___jp_3484_;
}
}
v___jp_3501_:
{
uint64_t v___x_3506_; uint8_t v___x_3507_; 
v___x_3506_ = 425ULL;
v___x_3507_ = lean_uint64_dec_lt(v___x_3506_, v___y_3505_);
if (v___x_3507_ == 0)
{
if (v___y_3503_ == 0)
{
v___y_3490_ = v___y_3505_;
v___y_3491_ = v___y_3502_;
v___y_3492_ = v___y_3504_;
goto v___jp_3489_;
}
else
{
uint64_t v___x_3508_; 
v___x_3508_ = 8388608ULL;
v___y_3490_ = v___y_3505_;
v___y_3491_ = v___y_3502_;
v___y_3492_ = v___x_3508_;
goto v___jp_3489_;
}
}
else
{
if (v_sign_3436_ == 0)
{
uint32_t v___x_3509_; 
v___x_3509_ = 2139095040;
return v___x_3509_;
}
else
{
uint32_t v___x_3510_; 
v___x_3510_ = 4286578688;
return v___x_3510_;
}
}
}
v___jp_3511_:
{
uint64_t v___x_3515_; uint8_t v_carry_3516_; 
v___x_3515_ = 16777216ULL;
v_carry_3516_ = lean_uint64_dec_eq(v___y_3514_, v___x_3515_);
if (v_carry_3516_ == 0)
{
v___y_3502_ = v___y_3512_;
v___y_3503_ = v_carry_3516_;
v___y_3504_ = v___y_3514_;
v___y_3505_ = v___y_3513_;
goto v___jp_3501_;
}
else
{
uint64_t v___x_3517_; uint64_t v___x_3518_; 
v___x_3517_ = 1ULL;
v___x_3518_ = lean_uint64_add(v___y_3513_, v___x_3517_);
v___y_3502_ = v___y_3512_;
v___y_3503_ = v_carry_3516_;
v___y_3504_ = v___y_3514_;
v___y_3505_ = v___x_3518_;
goto v___jp_3501_;
}
}
v___jp_3519_:
{
uint64_t v_position_3522_; uint64_t v___x_3523_; uint8_t v___x_3524_; 
v_position_3522_ = lean_uint64_add(v___y_3521_, v_scale_3438_);
v___x_3523_ = 172ULL;
v___x_3524_ = lean_uint64_dec_lt(v_position_3522_, v___x_3523_);
if (v___x_3524_ == 0)
{
uint64_t v___x_3525_; uint8_t v___x_3526_; 
v___x_3525_ = 23ULL;
v___x_3526_ = lean_uint64_dec_lt(v___y_3521_, v___x_3525_);
if (v___x_3526_ == 0)
{
uint64_t v___x_3527_; uint8_t v___x_3528_; 
v___x_3527_ = lean_uint64_sub(v___y_3521_, v___x_3525_);
v___x_3528_ = lean_uint64_dec_eq(v___x_3527_, v___y_3520_);
if (v___x_3528_ == 0)
{
uint64_t v___x_3529_; uint8_t v___x_3530_; 
v___x_3529_ = 64ULL;
v___x_3530_ = lean_uint64_dec_lt(v___x_3527_, v___x_3529_);
if (v___x_3530_ == 0)
{
uint8_t v___x_3531_; 
v___x_3531_ = lean_uint64_dec_eq(v___x_3527_, v___x_3529_);
if (v___x_3531_ == 0)
{
v___y_3512_ = v___y_3520_;
v___y_3513_ = v_position_3522_;
v___y_3514_ = v___y_3520_;
goto v___jp_3511_;
}
else
{
uint64_t v___x_3532_; uint8_t v___x_3533_; 
v___x_3532_ = 9223372036854775808ULL;
v___x_3533_ = lean_uint64_dec_lt(v___x_3532_, v_product_3437_);
if (v___x_3533_ == 0)
{
v___y_3512_ = v___y_3520_;
v___y_3513_ = v_position_3522_;
v___y_3514_ = v___y_3520_;
goto v___jp_3511_;
}
else
{
uint64_t v___x_3534_; 
v___x_3534_ = 1ULL;
v___y_3512_ = v___y_3520_;
v___y_3513_ = v_position_3522_;
v___y_3514_ = v___x_3534_;
goto v___jp_3511_;
}
}
}
else
{
uint64_t v_quotient_3535_; uint64_t v___x_3536_; uint64_t v___x_3537_; uint64_t v___x_3538_; uint64_t v_remainder_3539_; uint64_t v___x_3540_; uint64_t v_half_3541_; uint8_t v___x_3542_; 
v_quotient_3535_ = lean_uint64_shift_right(v_product_3437_, v___x_3527_);
v___x_3536_ = 1ULL;
v___x_3537_ = lean_uint64_shift_left(v___x_3536_, v___x_3527_);
v___x_3538_ = lean_uint64_sub(v___x_3537_, v___x_3536_);
v_remainder_3539_ = lean_uint64_land(v_product_3437_, v___x_3538_);
v___x_3540_ = lean_uint64_sub(v___x_3527_, v___x_3536_);
v_half_3541_ = lean_uint64_shift_left(v___x_3536_, v___x_3540_);
v___x_3542_ = lean_uint64_dec_lt(v_remainder_3539_, v_half_3541_);
if (v___x_3542_ == 0)
{
uint8_t v___x_3543_; 
v___x_3543_ = lean_uint64_dec_lt(v_half_3541_, v_remainder_3539_);
if (v___x_3543_ == 0)
{
uint64_t v___x_3544_; uint8_t v___x_3545_; 
v___x_3544_ = lean_uint64_land(v_quotient_3535_, v___x_3536_);
v___x_3545_ = lean_uint64_dec_eq(v___x_3544_, v___y_3520_);
if (v___x_3545_ == 0)
{
uint64_t v___x_3546_; 
v___x_3546_ = lean_uint64_add(v_quotient_3535_, v___x_3536_);
v___y_3512_ = v___y_3520_;
v___y_3513_ = v_position_3522_;
v___y_3514_ = v___x_3546_;
goto v___jp_3511_;
}
else
{
v___y_3512_ = v___y_3520_;
v___y_3513_ = v_position_3522_;
v___y_3514_ = v_quotient_3535_;
goto v___jp_3511_;
}
}
else
{
uint64_t v___x_3547_; 
v___x_3547_ = lean_uint64_add(v_quotient_3535_, v___x_3536_);
v___y_3512_ = v___y_3520_;
v___y_3513_ = v_position_3522_;
v___y_3514_ = v___x_3547_;
goto v___jp_3511_;
}
}
else
{
v___y_3512_ = v___y_3520_;
v___y_3513_ = v_position_3522_;
v___y_3514_ = v_quotient_3535_;
goto v___jp_3511_;
}
}
}
else
{
v___y_3512_ = v___y_3520_;
v___y_3513_ = v_position_3522_;
v___y_3514_ = v_product_3437_;
goto v___jp_3511_;
}
}
else
{
uint64_t v___x_3548_; uint64_t v___x_3549_; 
v___x_3548_ = lean_uint64_sub(v___x_3525_, v___y_3521_);
v___x_3549_ = lean_uint64_shift_left(v_product_3437_, v___x_3548_);
v___y_3512_ = v___y_3520_;
v___y_3513_ = v_position_3522_;
v___y_3514_ = v___x_3549_;
goto v___jp_3511_;
}
}
else
{
uint64_t v___x_3550_; uint8_t v___x_3551_; 
v___x_3550_ = 149ULL;
v___x_3551_ = lean_uint64_dec_lt(v_scale_3438_, v___x_3550_);
if (v___x_3551_ == 0)
{
uint64_t v___x_3552_; uint64_t v___x_3553_; 
v___x_3552_ = lean_uint64_sub(v_scale_3438_, v___x_3550_);
v___x_3553_ = lean_uint64_shift_left(v_product_3437_, v___x_3552_);
v___y_3460_ = v___y_3520_;
v___y_3461_ = v___x_3553_;
goto v___jp_3459_;
}
else
{
uint64_t v___x_3554_; uint8_t v___x_3555_; 
v___x_3554_ = lean_uint64_sub(v___x_3550_, v_scale_3438_);
v___x_3555_ = lean_uint64_dec_eq(v___x_3554_, v___y_3520_);
if (v___x_3555_ == 0)
{
uint64_t v___x_3556_; uint8_t v___x_3557_; 
v___x_3556_ = 64ULL;
v___x_3557_ = lean_uint64_dec_lt(v___x_3554_, v___x_3556_);
if (v___x_3557_ == 0)
{
uint8_t v___x_3558_; 
v___x_3558_ = lean_uint64_dec_eq(v___x_3554_, v___x_3556_);
if (v___x_3558_ == 0)
{
v___y_3460_ = v___y_3520_;
v___y_3461_ = v___y_3520_;
goto v___jp_3459_;
}
else
{
uint64_t v___x_3559_; uint8_t v___x_3560_; 
v___x_3559_ = 9223372036854775808ULL;
v___x_3560_ = lean_uint64_dec_lt(v___x_3559_, v_product_3437_);
if (v___x_3560_ == 0)
{
v___y_3460_ = v___y_3520_;
v___y_3461_ = v___y_3520_;
goto v___jp_3459_;
}
else
{
uint64_t v___x_3561_; 
v___x_3561_ = 1ULL;
v___y_3460_ = v___y_3520_;
v___y_3461_ = v___x_3561_;
goto v___jp_3459_;
}
}
}
else
{
uint64_t v_quotient_3562_; uint64_t v___x_3563_; uint64_t v___x_3564_; uint64_t v___x_3565_; uint64_t v_remainder_3566_; uint64_t v___x_3567_; uint64_t v_half_3568_; uint8_t v___x_3569_; 
v_quotient_3562_ = lean_uint64_shift_right(v_product_3437_, v___x_3554_);
v___x_3563_ = 1ULL;
v___x_3564_ = lean_uint64_shift_left(v___x_3563_, v___x_3554_);
v___x_3565_ = lean_uint64_sub(v___x_3564_, v___x_3563_);
v_remainder_3566_ = lean_uint64_land(v_product_3437_, v___x_3565_);
v___x_3567_ = lean_uint64_sub(v___x_3554_, v___x_3563_);
v_half_3568_ = lean_uint64_shift_left(v___x_3563_, v___x_3567_);
v___x_3569_ = lean_uint64_dec_lt(v_remainder_3566_, v_half_3568_);
if (v___x_3569_ == 0)
{
uint8_t v___x_3570_; 
v___x_3570_ = lean_uint64_dec_lt(v_half_3568_, v_remainder_3566_);
if (v___x_3570_ == 0)
{
uint64_t v___x_3571_; uint8_t v___x_3572_; 
v___x_3571_ = lean_uint64_land(v_quotient_3562_, v___x_3563_);
v___x_3572_ = lean_uint64_dec_eq(v___x_3571_, v___y_3520_);
if (v___x_3572_ == 0)
{
uint64_t v___x_3573_; 
v___x_3573_ = lean_uint64_add(v_quotient_3562_, v___x_3563_);
v___y_3460_ = v___y_3520_;
v___y_3461_ = v___x_3573_;
goto v___jp_3459_;
}
else
{
v___y_3460_ = v___y_3520_;
v___y_3461_ = v_quotient_3562_;
goto v___jp_3459_;
}
}
else
{
uint64_t v___x_3574_; 
v___x_3574_ = lean_uint64_add(v_quotient_3562_, v___x_3563_);
v___y_3460_ = v___y_3520_;
v___y_3461_ = v___x_3574_;
goto v___jp_3459_;
}
}
else
{
v___y_3460_ = v___y_3520_;
v___y_3461_ = v_quotient_3562_;
goto v___jp_3459_;
}
}
}
else
{
v___y_3460_ = v___y_3520_;
v___y_3461_ = v_product_3437_;
goto v___jp_3459_;
}
}
}
}
v___jp_3575_:
{
uint64_t v___x_3579_; uint64_t v___x_3580_; uint8_t v___x_3581_; 
v___x_3579_ = 1ULL;
v___x_3580_ = lean_uint64_shift_right(v___y_3577_, v___x_3579_);
v___x_3581_ = lean_uint64_dec_eq(v___x_3580_, v___y_3576_);
if (v___x_3581_ == 0)
{
uint64_t v___x_3582_; 
v___x_3582_ = lean_uint64_add(v___y_3578_, v___x_3579_);
v___y_3520_ = v___y_3576_;
v___y_3521_ = v___x_3582_;
goto v___jp_3519_;
}
else
{
v___y_3520_ = v___y_3576_;
v___y_3521_ = v___y_3578_;
goto v___jp_3519_;
}
}
v___jp_3583_:
{
uint64_t v___x_3589_; uint8_t v___x_3590_; 
v___x_3589_ = lean_uint64_shift_right(v___y_3587_, v___y_3585_);
v___x_3590_ = lean_uint64_dec_eq(v___x_3589_, v___y_3584_);
if (v___x_3590_ == 0)
{
uint64_t v___x_3591_; 
v___x_3591_ = lean_uint64_add(v___y_3586_, v___y_3585_);
v___y_3576_ = v___y_3584_;
v___y_3577_ = v___y_3588_;
v___y_3578_ = v___x_3591_;
goto v___jp_3575_;
}
else
{
v___y_3576_ = v___y_3584_;
v___y_3577_ = v___y_3588_;
v___y_3578_ = v___y_3586_;
goto v___jp_3575_;
}
}
v___jp_3592_:
{
uint64_t v___x_3596_; uint64_t v___x_3597_; uint8_t v___x_3598_; 
v___x_3596_ = 2ULL;
v___x_3597_ = lean_uint64_shift_right(v___y_3594_, v___x_3596_);
v___x_3598_ = lean_uint64_dec_eq(v___x_3597_, v___y_3593_);
if (v___x_3598_ == 0)
{
v___y_3584_ = v___y_3593_;
v___y_3585_ = v___x_3596_;
v___y_3586_ = v___y_3595_;
v___y_3587_ = v___y_3594_;
v___y_3588_ = v___x_3597_;
goto v___jp_3583_;
}
else
{
v___y_3584_ = v___y_3593_;
v___y_3585_ = v___x_3596_;
v___y_3586_ = v___y_3595_;
v___y_3587_ = v___y_3594_;
v___y_3588_ = v___y_3594_;
goto v___jp_3583_;
}
}
v___jp_3599_:
{
uint64_t v___x_3605_; uint8_t v___x_3606_; 
v___x_3605_ = lean_uint64_shift_right(v___y_3603_, v___y_3602_);
v___x_3606_ = lean_uint64_dec_eq(v___x_3605_, v___y_3600_);
if (v___x_3606_ == 0)
{
uint64_t v___x_3607_; 
v___x_3607_ = lean_uint64_add(v___y_3601_, v___y_3602_);
v___y_3593_ = v___y_3600_;
v___y_3594_ = v___y_3604_;
v___y_3595_ = v___x_3607_;
goto v___jp_3592_;
}
else
{
v___y_3593_ = v___y_3600_;
v___y_3594_ = v___y_3604_;
v___y_3595_ = v___y_3601_;
goto v___jp_3592_;
}
}
v___jp_3608_:
{
uint64_t v___x_3612_; uint64_t v___x_3613_; uint8_t v___x_3614_; 
v___x_3612_ = 4ULL;
v___x_3613_ = lean_uint64_shift_right(v___y_3610_, v___x_3612_);
v___x_3614_ = lean_uint64_dec_eq(v___x_3613_, v___y_3609_);
if (v___x_3614_ == 0)
{
v___y_3600_ = v___y_3609_;
v___y_3601_ = v___y_3611_;
v___y_3602_ = v___x_3612_;
v___y_3603_ = v___y_3610_;
v___y_3604_ = v___x_3613_;
goto v___jp_3599_;
}
else
{
v___y_3600_ = v___y_3609_;
v___y_3601_ = v___y_3611_;
v___y_3602_ = v___x_3612_;
v___y_3603_ = v___y_3610_;
v___y_3604_ = v___y_3610_;
goto v___jp_3599_;
}
}
v___jp_3615_:
{
uint64_t v___x_3621_; uint8_t v___x_3622_; 
v___x_3621_ = lean_uint64_shift_right(v___y_3617_, v___y_3619_);
v___x_3622_ = lean_uint64_dec_eq(v___x_3621_, v___y_3616_);
if (v___x_3622_ == 0)
{
uint64_t v___x_3623_; 
v___x_3623_ = lean_uint64_add(v___y_3618_, v___y_3619_);
v___y_3609_ = v___y_3616_;
v___y_3610_ = v___y_3620_;
v___y_3611_ = v___x_3623_;
goto v___jp_3608_;
}
else
{
v___y_3609_ = v___y_3616_;
v___y_3610_ = v___y_3620_;
v___y_3611_ = v___y_3618_;
goto v___jp_3608_;
}
}
v___jp_3624_:
{
uint64_t v___x_3628_; uint64_t v___x_3629_; uint8_t v___x_3630_; 
v___x_3628_ = 8ULL;
v___x_3629_ = lean_uint64_shift_right(v___y_3626_, v___x_3628_);
v___x_3630_ = lean_uint64_dec_eq(v___x_3629_, v___y_3625_);
if (v___x_3630_ == 0)
{
v___y_3616_ = v___y_3625_;
v___y_3617_ = v___y_3626_;
v___y_3618_ = v___y_3627_;
v___y_3619_ = v___x_3628_;
v___y_3620_ = v___x_3629_;
goto v___jp_3615_;
}
else
{
v___y_3616_ = v___y_3625_;
v___y_3617_ = v___y_3626_;
v___y_3618_ = v___y_3627_;
v___y_3619_ = v___x_3628_;
v___y_3620_ = v___y_3626_;
goto v___jp_3615_;
}
}
v___jp_3631_:
{
uint64_t v___x_3637_; uint8_t v___x_3638_; 
v___x_3637_ = lean_uint64_shift_right(v___y_3635_, v___y_3633_);
v___x_3638_ = lean_uint64_dec_eq(v___x_3637_, v___y_3634_);
if (v___x_3638_ == 0)
{
uint64_t v___x_3639_; 
v___x_3639_ = lean_uint64_add(v___y_3632_, v___y_3633_);
v___y_3625_ = v___y_3634_;
v___y_3626_ = v___y_3636_;
v___y_3627_ = v___x_3639_;
goto v___jp_3624_;
}
else
{
v___y_3625_ = v___y_3634_;
v___y_3626_ = v___y_3636_;
v___y_3627_ = v___y_3632_;
goto v___jp_3624_;
}
}
v___jp_3640_:
{
uint64_t v___x_3644_; uint64_t v___x_3645_; uint8_t v___x_3646_; 
v___x_3644_ = 16ULL;
v___x_3645_ = lean_uint64_shift_right(v___y_3642_, v___x_3644_);
v___x_3646_ = lean_uint64_dec_eq(v___x_3645_, v___y_3641_);
if (v___x_3646_ == 0)
{
v___y_3632_ = v___y_3643_;
v___y_3633_ = v___x_3644_;
v___y_3634_ = v___y_3641_;
v___y_3635_ = v___y_3642_;
v___y_3636_ = v___x_3645_;
goto v___jp_3631_;
}
else
{
v___y_3632_ = v___y_3643_;
v___y_3633_ = v___x_3644_;
v___y_3634_ = v___y_3641_;
v___y_3635_ = v___y_3642_;
v___y_3636_ = v___y_3642_;
goto v___jp_3631_;
}
}
v___jp_3647_:
{
uint64_t v___x_3651_; uint8_t v___x_3652_; 
v___x_3651_ = lean_uint64_shift_right(v_product_3437_, v___y_3649_);
v___x_3652_ = lean_uint64_dec_eq(v___x_3651_, v___y_3648_);
if (v___x_3652_ == 0)
{
v___y_3641_ = v___y_3648_;
v___y_3642_ = v___y_3650_;
v___y_3643_ = v___y_3649_;
goto v___jp_3640_;
}
else
{
v___y_3641_ = v___y_3648_;
v___y_3642_ = v___y_3650_;
v___y_3643_ = v___y_3648_;
goto v___jp_3640_;
}
}
v___jp_3653_:
{
uint64_t v___x_3654_; uint8_t v___x_3655_; 
v___x_3654_ = 0ULL;
v___x_3655_ = lean_uint64_dec_eq(v_product_3437_, v___x_3654_);
if (v___x_3655_ == 0)
{
uint64_t v___x_3656_; uint64_t v___x_3657_; uint8_t v___x_3658_; 
v___x_3656_ = 32ULL;
v___x_3657_ = lean_uint64_shift_right(v_product_3437_, v___x_3656_);
v___x_3658_ = lean_uint64_dec_eq(v___x_3657_, v___x_3654_);
if (v___x_3658_ == 0)
{
v___y_3648_ = v___x_3654_;
v___y_3649_ = v___x_3656_;
v___y_3650_ = v___x_3657_;
goto v___jp_3647_;
}
else
{
v___y_3648_ = v___x_3654_;
v___y_3649_ = v___x_3656_;
v___y_3650_ = v_product_3437_;
goto v___jp_3647_;
}
}
else
{
if (v_sign_3436_ == 0)
{
uint32_t v___x_3659_; 
v___x_3659_ = 0;
return v___x_3659_;
}
else
{
uint32_t v___x_3660_; 
v___x_3660_ = 2147483648;
return v___x_3660_;
}
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_LowScale_roundSelect___boxed(lean_object* v_sign_3703_, lean_object* v_product_3704_, lean_object* v_scale_3705_){
_start:
{
uint8_t v_sign_boxed_3706_; uint64_t v_product_boxed_3707_; uint64_t v_scale_boxed_3708_; uint32_t v_res_3709_; lean_object* v_r_3710_; 
v_sign_boxed_3706_ = lean_unbox(v_sign_3703_);
v_product_boxed_3707_ = lean_unbox_uint64(v_product_3704_);
lean_dec_ref(v_product_3704_);
v_scale_boxed_3708_ = lean_unbox_uint64(v_scale_3705_);
lean_dec_ref(v_scale_3705_);
v_res_3709_ = lp_competition_Submission_LowScale_roundSelect(v_sign_boxed_3706_, v_product_boxed_3707_, v_scale_boxed_3708_);
v_r_3710_ = lean_box_uint32(v_res_3709_);
return v_r_3710_;
}
}
LEAN_EXPORT uint32_t lp_competition_Submission_LowScale_core(uint32_t v_xBits_3711_, uint32_t v_yBits_3712_){
_start:
{
uint32_t v___y_3714_; uint32_t v___y_3718_; uint32_t v___y_3722_; uint32_t v___y_3723_; uint32_t v___y_3724_; uint32_t v___y_3728_; uint64_t v___y_3729_; uint8_t v___y_3730_; uint64_t v___y_3731_; uint32_t v___y_3743_; uint32_t v___y_3744_; uint32_t v___y_3745_; uint32_t v___y_3749_; uint64_t v___y_3750_; uint8_t v___y_3751_; uint64_t v___y_3752_; uint32_t v___x_3763_; uint32_t v___x_3764_; uint32_t v___x_3765_; uint32_t v___y_3767_; uint32_t v___y_3768_; uint32_t v___y_3769_; uint32_t v___y_3770_; uint32_t v___y_3777_; uint32_t v___y_3778_; uint8_t v___y_3779_; uint32_t v___y_3780_; uint64_t v___y_3784_; uint32_t v___y_3785_; uint64_t v___y_3786_; uint8_t v___y_3787_; uint64_t v___y_3788_; uint8_t v___y_3798_; uint32_t v___y_3799_; uint64_t v___y_3800_; uint64_t v___y_3801_; uint8_t v___y_3802_; uint64_t v___y_3803_; uint32_t v___y_3810_; uint64_t v___y_3811_; uint64_t v___y_3812_; uint8_t v___y_3813_; uint64_t v___y_3814_; uint64_t v___y_3820_; uint32_t v___y_3821_; uint64_t v___y_3822_; uint64_t v___y_3823_; uint8_t v___y_3824_; uint64_t v___y_3825_; uint64_t v___y_3880_; uint32_t v___y_3881_; uint64_t v___y_3882_; uint64_t v___y_3883_; uint64_t v___y_3884_; uint8_t v___y_3885_; uint64_t v___y_3886_; uint64_t v___y_3892_; uint32_t v___y_3893_; uint64_t v___y_3894_; uint64_t v___y_3895_; uint64_t v___y_3896_; uint64_t v___y_3897_; uint64_t v___y_3898_; uint8_t v___y_3899_; uint64_t v___y_3900_; uint64_t v___y_3905_; uint32_t v___y_3906_; uint64_t v___y_3907_; uint64_t v___y_3908_; uint64_t v___y_3909_; uint8_t v___y_3910_; uint64_t v___y_3911_; uint64_t v___y_3916_; uint64_t v___y_3917_; uint64_t v___y_3918_; uint32_t v___y_3919_; uint64_t v___y_3920_; uint64_t v___y_3921_; uint64_t v___y_3922_; uint8_t v___y_3923_; uint64_t v___y_3924_; uint64_t v___y_3929_; uint64_t v___y_3930_; uint32_t v___y_3931_; uint64_t v___y_3932_; uint64_t v___y_3933_; uint8_t v___y_3934_; uint64_t v___y_3935_; uint64_t v___y_3940_; uint32_t v___y_3941_; uint64_t v___y_3942_; uint64_t v___y_3943_; uint64_t v___y_3944_; uint64_t v___y_3945_; uint64_t v___y_3946_; uint8_t v___y_3947_; uint64_t v___y_3948_; uint64_t v___y_3953_; uint32_t v___y_3954_; uint64_t v___y_3955_; uint64_t v___y_3956_; uint64_t v___y_3957_; uint8_t v___y_3958_; uint64_t v___y_3959_; uint64_t v___y_3964_; uint32_t v___y_3965_; uint64_t v___y_3966_; uint64_t v___y_3967_; uint64_t v___y_3968_; uint64_t v___y_3969_; uint64_t v___y_3970_; uint8_t v___y_3971_; uint64_t v___y_3972_; uint64_t v___y_3977_; uint32_t v___y_3978_; uint64_t v___y_3979_; uint64_t v___y_3980_; uint8_t v___y_3981_; uint64_t v___y_3982_; uint64_t v___y_3983_; uint64_t v___y_3988_; uint32_t v___y_3989_; uint64_t v___y_3990_; uint64_t v___y_3991_; uint64_t v___y_3992_; uint8_t v___y_3993_; uint64_t v___y_3994_; uint64_t v___y_3998_; uint32_t v___y_3999_; uint64_t v___y_4000_; uint8_t v___y_4001_; uint32_t v___y_4010_; uint64_t v___y_4011_; uint64_t v___y_4012_; uint64_t v___y_4013_; uint8_t v___y_4014_; uint64_t v___y_4015_; uint32_t v_xExponent_4048_; uint32_t v___x_4049_; uint32_t v_yExponent_4050_; uint32_t v___y_4052_; uint64_t v___y_4053_; uint64_t v___y_4054_; uint8_t v___y_4055_; uint64_t v___y_4056_; uint32_t v___y_4063_; uint64_t v___y_4064_; uint8_t v___y_4065_; uint64_t v___y_4066_; uint32_t v___y_4073_; uint32_t v___y_4074_; uint8_t v___y_4075_; uint64_t v___y_4076_; uint8_t v___y_4084_; uint8_t v___y_4099_; uint8_t v___y_4100_; uint8_t v___y_4102_; uint32_t v___x_4109_; uint32_t v___x_4110_; uint32_t v___x_4111_; uint8_t v___x_4112_; 
v___x_3763_ = 23;
v___x_3764_ = lean_uint32_shift_right(v_xBits_3711_, v___x_3763_);
v___x_3765_ = 255;
v_xExponent_4048_ = lean_uint32_land(v___x_3764_, v___x_3765_);
v___x_4049_ = lean_uint32_shift_right(v_yBits_3712_, v___x_3763_);
v_yExponent_4050_ = lean_uint32_land(v___x_4049_, v___x_3765_);
v___x_4109_ = 2147483648;
v___x_4110_ = lean_uint32_land(v_xBits_3711_, v___x_4109_);
v___x_4111_ = 0;
v___x_4112_ = lean_uint32_dec_eq(v___x_4110_, v___x_4111_);
if (v___x_4112_ == 0)
{
uint8_t v___x_4113_; 
v___x_4113_ = 1;
v___y_4102_ = v___x_4113_;
goto v___jp_4101_;
}
else
{
uint8_t v___x_4114_; 
v___x_4114_ = 0;
v___y_4102_ = v___x_4114_;
goto v___jp_4101_;
}
v___jp_3713_:
{
uint32_t v___x_3715_; uint32_t v___x_3716_; 
v___x_3715_ = 8388608;
v___x_3716_ = lean_uint32_lor(v___y_3714_, v___x_3715_);
return v___x_3716_;
}
v___jp_3717_:
{
uint32_t v___x_3719_; uint32_t v___x_3720_; 
v___x_3719_ = 8388608;
v___x_3720_ = lean_uint32_lor(v___y_3718_, v___x_3719_);
return v___x_3720_;
}
v___jp_3721_:
{
uint32_t v___x_3725_; uint32_t v___x_3726_; 
v___x_3725_ = lean_uint32_land(v___y_3723_, v___y_3722_);
v___x_3726_ = lean_uint32_lor(v___y_3724_, v___x_3725_);
return v___x_3726_;
}
v___jp_3727_:
{
uint8_t v___x_3732_; 
v___x_3732_ = lean_uint64_dec_eq(v___y_3731_, v___y_3729_);
if (v___x_3732_ == 0)
{
uint64_t v___x_3733_; uint8_t v___x_3734_; 
v___x_3733_ = 8388608ULL;
v___x_3734_ = lean_uint64_dec_eq(v___y_3731_, v___x_3733_);
if (v___x_3734_ == 0)
{
uint32_t v___x_3735_; 
v___x_3735_ = lean_uint64_to_uint32(v___y_3731_);
if (v___y_3730_ == 0)
{
uint32_t v___x_3736_; 
v___x_3736_ = 0;
v___y_3722_ = v___y_3728_;
v___y_3723_ = v___x_3735_;
v___y_3724_ = v___x_3736_;
goto v___jp_3721_;
}
else
{
uint32_t v___x_3737_; 
v___x_3737_ = 2147483648;
v___y_3722_ = v___y_3728_;
v___y_3723_ = v___x_3735_;
v___y_3724_ = v___x_3737_;
goto v___jp_3721_;
}
}
else
{
if (v___y_3730_ == 0)
{
uint32_t v___x_3738_; 
v___x_3738_ = 0;
v___y_3714_ = v___x_3738_;
goto v___jp_3713_;
}
else
{
uint32_t v___x_3739_; 
v___x_3739_ = 2147483648;
v___y_3714_ = v___x_3739_;
goto v___jp_3713_;
}
}
}
else
{
if (v___y_3730_ == 0)
{
uint32_t v___x_3740_; 
v___x_3740_ = 0;
return v___x_3740_;
}
else
{
uint32_t v___x_3741_; 
v___x_3741_ = 2147483648;
return v___x_3741_;
}
}
}
v___jp_3742_:
{
uint32_t v___x_3746_; uint32_t v___x_3747_; 
v___x_3746_ = lean_uint32_land(v___y_3744_, v___y_3743_);
v___x_3747_ = lean_uint32_lor(v___y_3745_, v___x_3746_);
return v___x_3747_;
}
v___jp_3748_:
{
uint8_t v___x_3753_; 
v___x_3753_ = lean_uint64_dec_eq(v___y_3752_, v___y_3750_);
if (v___x_3753_ == 0)
{
uint64_t v___x_3754_; uint8_t v___x_3755_; 
v___x_3754_ = 8388608ULL;
v___x_3755_ = lean_uint64_dec_eq(v___y_3752_, v___x_3754_);
if (v___x_3755_ == 0)
{
uint32_t v___x_3756_; 
v___x_3756_ = lean_uint64_to_uint32(v___y_3752_);
if (v___y_3751_ == 0)
{
uint32_t v___x_3757_; 
v___x_3757_ = 0;
v___y_3743_ = v___y_3749_;
v___y_3744_ = v___x_3756_;
v___y_3745_ = v___x_3757_;
goto v___jp_3742_;
}
else
{
uint32_t v___x_3758_; 
v___x_3758_ = 2147483648;
v___y_3743_ = v___y_3749_;
v___y_3744_ = v___x_3756_;
v___y_3745_ = v___x_3758_;
goto v___jp_3742_;
}
}
else
{
if (v___y_3751_ == 0)
{
uint32_t v___x_3759_; 
v___x_3759_ = 0;
v___y_3718_ = v___x_3759_;
goto v___jp_3717_;
}
else
{
uint32_t v___x_3760_; 
v___x_3760_ = 2147483648;
v___y_3718_ = v___x_3760_;
goto v___jp_3717_;
}
}
}
else
{
if (v___y_3751_ == 0)
{
uint32_t v___x_3761_; 
v___x_3761_ = 0;
return v___x_3761_;
}
else
{
uint32_t v___x_3762_; 
v___x_3762_ = 2147483648;
return v___x_3762_;
}
}
}
v___jp_3766_:
{
uint32_t v___x_3771_; uint32_t v___x_3772_; uint32_t v___x_3773_; uint32_t v___x_3774_; uint32_t v___x_3775_; 
v___x_3771_ = lean_uint32_land(v___y_3768_, v___x_3765_);
v___x_3772_ = lean_uint32_shift_left(v___x_3771_, v___x_3763_);
v___x_3773_ = lean_uint32_lor(v___y_3770_, v___x_3772_);
v___x_3774_ = lean_uint32_land(v___y_3769_, v___y_3767_);
v___x_3775_ = lean_uint32_lor(v___x_3773_, v___x_3774_);
return v___x_3775_;
}
v___jp_3776_:
{
if (v___y_3779_ == 0)
{
uint32_t v___x_3781_; 
v___x_3781_ = 0;
v___y_3767_ = v___y_3777_;
v___y_3768_ = v___y_3778_;
v___y_3769_ = v___y_3780_;
v___y_3770_ = v___x_3781_;
goto v___jp_3766_;
}
else
{
uint32_t v___x_3782_; 
v___x_3782_ = 2147483648;
v___y_3767_ = v___y_3777_;
v___y_3768_ = v___y_3778_;
v___y_3769_ = v___y_3780_;
v___y_3770_ = v___x_3782_;
goto v___jp_3766_;
}
}
v___jp_3783_:
{
uint64_t v___x_3789_; uint64_t v_encodedExponent_3790_; uint32_t v___x_3791_; uint64_t v___x_3792_; uint8_t v___x_3793_; 
v___x_3789_ = 171ULL;
v_encodedExponent_3790_ = lean_uint64_sub(v___y_3784_, v___x_3789_);
v___x_3791_ = lean_uint64_to_uint32(v_encodedExponent_3790_);
v___x_3792_ = 8388608ULL;
v___x_3793_ = lean_uint64_dec_lt(v___y_3788_, v___x_3792_);
if (v___x_3793_ == 0)
{
uint64_t v___x_3794_; uint32_t v___x_3795_; 
v___x_3794_ = lean_uint64_sub(v___y_3788_, v___x_3792_);
v___x_3795_ = lean_uint64_to_uint32(v___x_3794_);
v___y_3777_ = v___y_3785_;
v___y_3778_ = v___x_3791_;
v___y_3779_ = v___y_3787_;
v___y_3780_ = v___x_3795_;
goto v___jp_3776_;
}
else
{
uint32_t v___x_3796_; 
v___x_3796_ = lean_uint64_to_uint32(v___y_3786_);
v___y_3777_ = v___y_3785_;
v___y_3778_ = v___x_3791_;
v___y_3779_ = v___y_3787_;
v___y_3780_ = v___x_3796_;
goto v___jp_3776_;
}
}
v___jp_3797_:
{
uint64_t v___x_3804_; uint8_t v___x_3805_; 
v___x_3804_ = 425ULL;
v___x_3805_ = lean_uint64_dec_lt(v___x_3804_, v___y_3803_);
if (v___x_3805_ == 0)
{
if (v___y_3798_ == 0)
{
v___y_3784_ = v___y_3803_;
v___y_3785_ = v___y_3799_;
v___y_3786_ = v___y_3801_;
v___y_3787_ = v___y_3802_;
v___y_3788_ = v___y_3800_;
goto v___jp_3783_;
}
else
{
uint64_t v___x_3806_; 
v___x_3806_ = 8388608ULL;
v___y_3784_ = v___y_3803_;
v___y_3785_ = v___y_3799_;
v___y_3786_ = v___y_3801_;
v___y_3787_ = v___y_3802_;
v___y_3788_ = v___x_3806_;
goto v___jp_3783_;
}
}
else
{
if (v___y_3802_ == 0)
{
uint32_t v___x_3807_; 
v___x_3807_ = 2139095040;
return v___x_3807_;
}
else
{
uint32_t v___x_3808_; 
v___x_3808_ = 4286578688;
return v___x_3808_;
}
}
}
v___jp_3809_:
{
uint64_t v___x_3815_; uint8_t v_carry_3816_; 
v___x_3815_ = 16777216ULL;
v_carry_3816_ = lean_uint64_dec_eq(v___y_3814_, v___x_3815_);
if (v_carry_3816_ == 0)
{
v___y_3798_ = v_carry_3816_;
v___y_3799_ = v___y_3810_;
v___y_3800_ = v___y_3814_;
v___y_3801_ = v___y_3811_;
v___y_3802_ = v___y_3813_;
v___y_3803_ = v___y_3812_;
goto v___jp_3797_;
}
else
{
uint64_t v___x_3817_; uint64_t v___x_3818_; 
v___x_3817_ = 1ULL;
v___x_3818_ = lean_uint64_add(v___y_3812_, v___x_3817_);
v___y_3798_ = v_carry_3816_;
v___y_3799_ = v___y_3810_;
v___y_3800_ = v___y_3814_;
v___y_3801_ = v___y_3811_;
v___y_3802_ = v___y_3813_;
v___y_3803_ = v___x_3818_;
goto v___jp_3797_;
}
}
v___jp_3819_:
{
uint64_t v_position_3826_; uint64_t v___x_3827_; uint8_t v___x_3828_; 
v_position_3826_ = lean_uint64_add(v___y_3825_, v___y_3820_);
v___x_3827_ = 172ULL;
v___x_3828_ = lean_uint64_dec_lt(v_position_3826_, v___x_3827_);
if (v___x_3828_ == 0)
{
uint64_t v___x_3829_; uint8_t v___x_3830_; 
v___x_3829_ = 23ULL;
v___x_3830_ = lean_uint64_dec_lt(v___y_3825_, v___x_3829_);
if (v___x_3830_ == 0)
{
uint64_t v___x_3831_; uint8_t v___x_3832_; 
v___x_3831_ = lean_uint64_sub(v___y_3825_, v___x_3829_);
v___x_3832_ = lean_uint64_dec_eq(v___x_3831_, v___y_3822_);
if (v___x_3832_ == 0)
{
uint64_t v___x_3833_; uint8_t v___x_3834_; 
v___x_3833_ = 64ULL;
v___x_3834_ = lean_uint64_dec_lt(v___x_3831_, v___x_3833_);
if (v___x_3834_ == 0)
{
uint8_t v___x_3835_; 
v___x_3835_ = lean_uint64_dec_eq(v___x_3831_, v___x_3833_);
if (v___x_3835_ == 0)
{
v___y_3810_ = v___y_3821_;
v___y_3811_ = v___y_3822_;
v___y_3812_ = v_position_3826_;
v___y_3813_ = v___y_3824_;
v___y_3814_ = v___y_3822_;
goto v___jp_3809_;
}
else
{
uint64_t v___x_3836_; uint8_t v___x_3837_; 
v___x_3836_ = 9223372036854775808ULL;
v___x_3837_ = lean_uint64_dec_lt(v___x_3836_, v___y_3823_);
if (v___x_3837_ == 0)
{
v___y_3810_ = v___y_3821_;
v___y_3811_ = v___y_3822_;
v___y_3812_ = v_position_3826_;
v___y_3813_ = v___y_3824_;
v___y_3814_ = v___y_3822_;
goto v___jp_3809_;
}
else
{
uint64_t v___x_3838_; 
v___x_3838_ = 1ULL;
v___y_3810_ = v___y_3821_;
v___y_3811_ = v___y_3822_;
v___y_3812_ = v_position_3826_;
v___y_3813_ = v___y_3824_;
v___y_3814_ = v___x_3838_;
goto v___jp_3809_;
}
}
}
else
{
uint64_t v_quotient_3839_; uint64_t v___x_3840_; uint64_t v___x_3841_; uint64_t v___x_3842_; uint64_t v_remainder_3843_; uint64_t v___x_3844_; uint64_t v_half_3845_; uint8_t v___x_3846_; 
v_quotient_3839_ = lean_uint64_shift_right(v___y_3823_, v___x_3831_);
v___x_3840_ = 1ULL;
v___x_3841_ = lean_uint64_shift_left(v___x_3840_, v___x_3831_);
v___x_3842_ = lean_uint64_sub(v___x_3841_, v___x_3840_);
v_remainder_3843_ = lean_uint64_land(v___y_3823_, v___x_3842_);
v___x_3844_ = lean_uint64_sub(v___x_3831_, v___x_3840_);
v_half_3845_ = lean_uint64_shift_left(v___x_3840_, v___x_3844_);
v___x_3846_ = lean_uint64_dec_lt(v_remainder_3843_, v_half_3845_);
if (v___x_3846_ == 0)
{
uint8_t v___x_3847_; 
v___x_3847_ = lean_uint64_dec_lt(v_half_3845_, v_remainder_3843_);
if (v___x_3847_ == 0)
{
uint64_t v___x_3848_; uint8_t v___x_3849_; 
v___x_3848_ = lean_uint64_land(v_quotient_3839_, v___x_3840_);
v___x_3849_ = lean_uint64_dec_eq(v___x_3848_, v___y_3822_);
if (v___x_3849_ == 0)
{
uint64_t v___x_3850_; 
v___x_3850_ = lean_uint64_add(v_quotient_3839_, v___x_3840_);
v___y_3810_ = v___y_3821_;
v___y_3811_ = v___y_3822_;
v___y_3812_ = v_position_3826_;
v___y_3813_ = v___y_3824_;
v___y_3814_ = v___x_3850_;
goto v___jp_3809_;
}
else
{
v___y_3810_ = v___y_3821_;
v___y_3811_ = v___y_3822_;
v___y_3812_ = v_position_3826_;
v___y_3813_ = v___y_3824_;
v___y_3814_ = v_quotient_3839_;
goto v___jp_3809_;
}
}
else
{
uint64_t v___x_3851_; 
v___x_3851_ = lean_uint64_add(v_quotient_3839_, v___x_3840_);
v___y_3810_ = v___y_3821_;
v___y_3811_ = v___y_3822_;
v___y_3812_ = v_position_3826_;
v___y_3813_ = v___y_3824_;
v___y_3814_ = v___x_3851_;
goto v___jp_3809_;
}
}
else
{
v___y_3810_ = v___y_3821_;
v___y_3811_ = v___y_3822_;
v___y_3812_ = v_position_3826_;
v___y_3813_ = v___y_3824_;
v___y_3814_ = v_quotient_3839_;
goto v___jp_3809_;
}
}
}
else
{
v___y_3810_ = v___y_3821_;
v___y_3811_ = v___y_3822_;
v___y_3812_ = v_position_3826_;
v___y_3813_ = v___y_3824_;
v___y_3814_ = v___y_3823_;
goto v___jp_3809_;
}
}
else
{
uint64_t v___x_3852_; uint64_t v___x_3853_; 
v___x_3852_ = lean_uint64_sub(v___x_3829_, v___y_3825_);
v___x_3853_ = lean_uint64_shift_left(v___y_3823_, v___x_3852_);
v___y_3810_ = v___y_3821_;
v___y_3811_ = v___y_3822_;
v___y_3812_ = v_position_3826_;
v___y_3813_ = v___y_3824_;
v___y_3814_ = v___x_3853_;
goto v___jp_3809_;
}
}
else
{
uint64_t v___x_3854_; uint8_t v___x_3855_; 
v___x_3854_ = 149ULL;
v___x_3855_ = lean_uint64_dec_lt(v___y_3820_, v___x_3854_);
if (v___x_3855_ == 0)
{
uint64_t v___x_3856_; uint64_t v___x_3857_; 
v___x_3856_ = lean_uint64_sub(v___y_3820_, v___x_3854_);
v___x_3857_ = lean_uint64_shift_left(v___y_3823_, v___x_3856_);
v___y_3728_ = v___y_3821_;
v___y_3729_ = v___y_3822_;
v___y_3730_ = v___y_3824_;
v___y_3731_ = v___x_3857_;
goto v___jp_3727_;
}
else
{
uint64_t v___x_3858_; uint8_t v___x_3859_; 
v___x_3858_ = lean_uint64_sub(v___x_3854_, v___y_3820_);
v___x_3859_ = lean_uint64_dec_eq(v___x_3858_, v___y_3822_);
if (v___x_3859_ == 0)
{
uint64_t v___x_3860_; uint8_t v___x_3861_; 
v___x_3860_ = 64ULL;
v___x_3861_ = lean_uint64_dec_lt(v___x_3858_, v___x_3860_);
if (v___x_3861_ == 0)
{
uint8_t v___x_3862_; 
v___x_3862_ = lean_uint64_dec_eq(v___x_3858_, v___x_3860_);
if (v___x_3862_ == 0)
{
v___y_3728_ = v___y_3821_;
v___y_3729_ = v___y_3822_;
v___y_3730_ = v___y_3824_;
v___y_3731_ = v___y_3822_;
goto v___jp_3727_;
}
else
{
uint64_t v___x_3863_; uint8_t v___x_3864_; 
v___x_3863_ = 9223372036854775808ULL;
v___x_3864_ = lean_uint64_dec_lt(v___x_3863_, v___y_3823_);
if (v___x_3864_ == 0)
{
v___y_3728_ = v___y_3821_;
v___y_3729_ = v___y_3822_;
v___y_3730_ = v___y_3824_;
v___y_3731_ = v___y_3822_;
goto v___jp_3727_;
}
else
{
uint64_t v___x_3865_; 
v___x_3865_ = 1ULL;
v___y_3728_ = v___y_3821_;
v___y_3729_ = v___y_3822_;
v___y_3730_ = v___y_3824_;
v___y_3731_ = v___x_3865_;
goto v___jp_3727_;
}
}
}
else
{
uint64_t v_quotient_3866_; uint64_t v___x_3867_; uint64_t v___x_3868_; uint64_t v___x_3869_; uint64_t v_remainder_3870_; uint64_t v___x_3871_; uint64_t v_half_3872_; uint8_t v___x_3873_; 
v_quotient_3866_ = lean_uint64_shift_right(v___y_3823_, v___x_3858_);
v___x_3867_ = 1ULL;
v___x_3868_ = lean_uint64_shift_left(v___x_3867_, v___x_3858_);
v___x_3869_ = lean_uint64_sub(v___x_3868_, v___x_3867_);
v_remainder_3870_ = lean_uint64_land(v___y_3823_, v___x_3869_);
v___x_3871_ = lean_uint64_sub(v___x_3858_, v___x_3867_);
v_half_3872_ = lean_uint64_shift_left(v___x_3867_, v___x_3871_);
v___x_3873_ = lean_uint64_dec_lt(v_remainder_3870_, v_half_3872_);
if (v___x_3873_ == 0)
{
uint8_t v___x_3874_; 
v___x_3874_ = lean_uint64_dec_lt(v_half_3872_, v_remainder_3870_);
if (v___x_3874_ == 0)
{
uint64_t v___x_3875_; uint8_t v___x_3876_; 
v___x_3875_ = lean_uint64_land(v_quotient_3866_, v___x_3867_);
v___x_3876_ = lean_uint64_dec_eq(v___x_3875_, v___y_3822_);
if (v___x_3876_ == 0)
{
uint64_t v___x_3877_; 
v___x_3877_ = lean_uint64_add(v_quotient_3866_, v___x_3867_);
v___y_3728_ = v___y_3821_;
v___y_3729_ = v___y_3822_;
v___y_3730_ = v___y_3824_;
v___y_3731_ = v___x_3877_;
goto v___jp_3727_;
}
else
{
v___y_3728_ = v___y_3821_;
v___y_3729_ = v___y_3822_;
v___y_3730_ = v___y_3824_;
v___y_3731_ = v_quotient_3866_;
goto v___jp_3727_;
}
}
else
{
uint64_t v___x_3878_; 
v___x_3878_ = lean_uint64_add(v_quotient_3866_, v___x_3867_);
v___y_3728_ = v___y_3821_;
v___y_3729_ = v___y_3822_;
v___y_3730_ = v___y_3824_;
v___y_3731_ = v___x_3878_;
goto v___jp_3727_;
}
}
else
{
v___y_3728_ = v___y_3821_;
v___y_3729_ = v___y_3822_;
v___y_3730_ = v___y_3824_;
v___y_3731_ = v_quotient_3866_;
goto v___jp_3727_;
}
}
}
else
{
v___y_3728_ = v___y_3821_;
v___y_3729_ = v___y_3822_;
v___y_3730_ = v___y_3824_;
v___y_3731_ = v___y_3823_;
goto v___jp_3727_;
}
}
}
}
v___jp_3879_:
{
uint64_t v___x_3887_; uint64_t v___x_3888_; uint8_t v___x_3889_; 
v___x_3887_ = 1ULL;
v___x_3888_ = lean_uint64_shift_right(v___y_3883_, v___x_3887_);
v___x_3889_ = lean_uint64_dec_eq(v___x_3888_, v___y_3882_);
if (v___x_3889_ == 0)
{
uint64_t v___x_3890_; 
v___x_3890_ = lean_uint64_add(v___y_3886_, v___x_3887_);
v___y_3820_ = v___y_3880_;
v___y_3821_ = v___y_3881_;
v___y_3822_ = v___y_3882_;
v___y_3823_ = v___y_3884_;
v___y_3824_ = v___y_3885_;
v___y_3825_ = v___x_3890_;
goto v___jp_3819_;
}
else
{
v___y_3820_ = v___y_3880_;
v___y_3821_ = v___y_3881_;
v___y_3822_ = v___y_3882_;
v___y_3823_ = v___y_3884_;
v___y_3824_ = v___y_3885_;
v___y_3825_ = v___y_3886_;
goto v___jp_3819_;
}
}
v___jp_3891_:
{
uint64_t v___x_3901_; uint8_t v___x_3902_; 
v___x_3901_ = lean_uint64_shift_right(v___y_3895_, v___y_3894_);
v___x_3902_ = lean_uint64_dec_eq(v___x_3901_, v___y_3896_);
if (v___x_3902_ == 0)
{
uint64_t v___x_3903_; 
v___x_3903_ = lean_uint64_add(v___y_3897_, v___y_3894_);
v___y_3880_ = v___y_3892_;
v___y_3881_ = v___y_3893_;
v___y_3882_ = v___y_3896_;
v___y_3883_ = v___y_3900_;
v___y_3884_ = v___y_3898_;
v___y_3885_ = v___y_3899_;
v___y_3886_ = v___x_3903_;
goto v___jp_3879_;
}
else
{
v___y_3880_ = v___y_3892_;
v___y_3881_ = v___y_3893_;
v___y_3882_ = v___y_3896_;
v___y_3883_ = v___y_3900_;
v___y_3884_ = v___y_3898_;
v___y_3885_ = v___y_3899_;
v___y_3886_ = v___y_3897_;
goto v___jp_3879_;
}
}
v___jp_3904_:
{
uint64_t v___x_3912_; uint64_t v___x_3913_; uint8_t v___x_3914_; 
v___x_3912_ = 2ULL;
v___x_3913_ = lean_uint64_shift_right(v___y_3907_, v___x_3912_);
v___x_3914_ = lean_uint64_dec_eq(v___x_3913_, v___y_3908_);
if (v___x_3914_ == 0)
{
v___y_3892_ = v___y_3905_;
v___y_3893_ = v___y_3906_;
v___y_3894_ = v___x_3912_;
v___y_3895_ = v___y_3907_;
v___y_3896_ = v___y_3908_;
v___y_3897_ = v___y_3911_;
v___y_3898_ = v___y_3909_;
v___y_3899_ = v___y_3910_;
v___y_3900_ = v___x_3913_;
goto v___jp_3891_;
}
else
{
v___y_3892_ = v___y_3905_;
v___y_3893_ = v___y_3906_;
v___y_3894_ = v___x_3912_;
v___y_3895_ = v___y_3907_;
v___y_3896_ = v___y_3908_;
v___y_3897_ = v___y_3911_;
v___y_3898_ = v___y_3909_;
v___y_3899_ = v___y_3910_;
v___y_3900_ = v___y_3907_;
goto v___jp_3891_;
}
}
v___jp_3915_:
{
uint64_t v___x_3925_; uint8_t v___x_3926_; 
v___x_3925_ = lean_uint64_shift_right(v___y_3917_, v___y_3916_);
v___x_3926_ = lean_uint64_dec_eq(v___x_3925_, v___y_3920_);
if (v___x_3926_ == 0)
{
uint64_t v___x_3927_; 
v___x_3927_ = lean_uint64_add(v___y_3921_, v___y_3916_);
v___y_3905_ = v___y_3918_;
v___y_3906_ = v___y_3919_;
v___y_3907_ = v___y_3924_;
v___y_3908_ = v___y_3920_;
v___y_3909_ = v___y_3922_;
v___y_3910_ = v___y_3923_;
v___y_3911_ = v___x_3927_;
goto v___jp_3904_;
}
else
{
v___y_3905_ = v___y_3918_;
v___y_3906_ = v___y_3919_;
v___y_3907_ = v___y_3924_;
v___y_3908_ = v___y_3920_;
v___y_3909_ = v___y_3922_;
v___y_3910_ = v___y_3923_;
v___y_3911_ = v___y_3921_;
goto v___jp_3904_;
}
}
v___jp_3928_:
{
uint64_t v___x_3936_; uint64_t v___x_3937_; uint8_t v___x_3938_; 
v___x_3936_ = 4ULL;
v___x_3937_ = lean_uint64_shift_right(v___y_3930_, v___x_3936_);
v___x_3938_ = lean_uint64_dec_eq(v___x_3937_, v___y_3932_);
if (v___x_3938_ == 0)
{
v___y_3916_ = v___x_3936_;
v___y_3917_ = v___y_3930_;
v___y_3918_ = v___y_3929_;
v___y_3919_ = v___y_3931_;
v___y_3920_ = v___y_3932_;
v___y_3921_ = v___y_3935_;
v___y_3922_ = v___y_3933_;
v___y_3923_ = v___y_3934_;
v___y_3924_ = v___x_3937_;
goto v___jp_3915_;
}
else
{
v___y_3916_ = v___x_3936_;
v___y_3917_ = v___y_3930_;
v___y_3918_ = v___y_3929_;
v___y_3919_ = v___y_3931_;
v___y_3920_ = v___y_3932_;
v___y_3921_ = v___y_3935_;
v___y_3922_ = v___y_3933_;
v___y_3923_ = v___y_3934_;
v___y_3924_ = v___y_3930_;
goto v___jp_3915_;
}
}
v___jp_3939_:
{
uint64_t v___x_3949_; uint8_t v___x_3950_; 
v___x_3949_ = lean_uint64_shift_right(v___y_3943_, v___y_3942_);
v___x_3950_ = lean_uint64_dec_eq(v___x_3949_, v___y_3944_);
if (v___x_3950_ == 0)
{
uint64_t v___x_3951_; 
v___x_3951_ = lean_uint64_add(v___y_3946_, v___y_3942_);
v___y_3929_ = v___y_3940_;
v___y_3930_ = v___y_3948_;
v___y_3931_ = v___y_3941_;
v___y_3932_ = v___y_3944_;
v___y_3933_ = v___y_3945_;
v___y_3934_ = v___y_3947_;
v___y_3935_ = v___x_3951_;
goto v___jp_3928_;
}
else
{
v___y_3929_ = v___y_3940_;
v___y_3930_ = v___y_3948_;
v___y_3931_ = v___y_3941_;
v___y_3932_ = v___y_3944_;
v___y_3933_ = v___y_3945_;
v___y_3934_ = v___y_3947_;
v___y_3935_ = v___y_3946_;
goto v___jp_3928_;
}
}
v___jp_3952_:
{
uint64_t v___x_3960_; uint64_t v___x_3961_; uint8_t v___x_3962_; 
v___x_3960_ = 8ULL;
v___x_3961_ = lean_uint64_shift_right(v___y_3955_, v___x_3960_);
v___x_3962_ = lean_uint64_dec_eq(v___x_3961_, v___y_3956_);
if (v___x_3962_ == 0)
{
v___y_3940_ = v___y_3953_;
v___y_3941_ = v___y_3954_;
v___y_3942_ = v___x_3960_;
v___y_3943_ = v___y_3955_;
v___y_3944_ = v___y_3956_;
v___y_3945_ = v___y_3957_;
v___y_3946_ = v___y_3959_;
v___y_3947_ = v___y_3958_;
v___y_3948_ = v___x_3961_;
goto v___jp_3939_;
}
else
{
v___y_3940_ = v___y_3953_;
v___y_3941_ = v___y_3954_;
v___y_3942_ = v___x_3960_;
v___y_3943_ = v___y_3955_;
v___y_3944_ = v___y_3956_;
v___y_3945_ = v___y_3957_;
v___y_3946_ = v___y_3959_;
v___y_3947_ = v___y_3958_;
v___y_3948_ = v___y_3955_;
goto v___jp_3939_;
}
}
v___jp_3963_:
{
uint64_t v___x_3973_; uint8_t v___x_3974_; 
v___x_3973_ = lean_uint64_shift_right(v___y_3970_, v___y_3969_);
v___x_3974_ = lean_uint64_dec_eq(v___x_3973_, v___y_3967_);
if (v___x_3974_ == 0)
{
uint64_t v___x_3975_; 
v___x_3975_ = lean_uint64_add(v___y_3966_, v___y_3969_);
v___y_3953_ = v___y_3964_;
v___y_3954_ = v___y_3965_;
v___y_3955_ = v___y_3972_;
v___y_3956_ = v___y_3967_;
v___y_3957_ = v___y_3968_;
v___y_3958_ = v___y_3971_;
v___y_3959_ = v___x_3975_;
goto v___jp_3952_;
}
else
{
v___y_3953_ = v___y_3964_;
v___y_3954_ = v___y_3965_;
v___y_3955_ = v___y_3972_;
v___y_3956_ = v___y_3967_;
v___y_3957_ = v___y_3968_;
v___y_3958_ = v___y_3971_;
v___y_3959_ = v___y_3966_;
goto v___jp_3952_;
}
}
v___jp_3976_:
{
uint64_t v___x_3984_; uint64_t v___x_3985_; uint8_t v___x_3986_; 
v___x_3984_ = 16ULL;
v___x_3985_ = lean_uint64_shift_right(v___y_3982_, v___x_3984_);
v___x_3986_ = lean_uint64_dec_eq(v___x_3985_, v___y_3979_);
if (v___x_3986_ == 0)
{
v___y_3964_ = v___y_3977_;
v___y_3965_ = v___y_3978_;
v___y_3966_ = v___y_3983_;
v___y_3967_ = v___y_3979_;
v___y_3968_ = v___y_3980_;
v___y_3969_ = v___x_3984_;
v___y_3970_ = v___y_3982_;
v___y_3971_ = v___y_3981_;
v___y_3972_ = v___x_3985_;
goto v___jp_3963_;
}
else
{
v___y_3964_ = v___y_3977_;
v___y_3965_ = v___y_3978_;
v___y_3966_ = v___y_3983_;
v___y_3967_ = v___y_3979_;
v___y_3968_ = v___y_3980_;
v___y_3969_ = v___x_3984_;
v___y_3970_ = v___y_3982_;
v___y_3971_ = v___y_3981_;
v___y_3972_ = v___y_3982_;
goto v___jp_3963_;
}
}
v___jp_3987_:
{
uint64_t v___x_3995_; uint8_t v___x_3996_; 
v___x_3995_ = lean_uint64_shift_right(v___y_3992_, v___y_3990_);
v___x_3996_ = lean_uint64_dec_eq(v___x_3995_, v___y_3991_);
if (v___x_3996_ == 0)
{
v___y_3977_ = v___y_3988_;
v___y_3978_ = v___y_3989_;
v___y_3979_ = v___y_3991_;
v___y_3980_ = v___y_3992_;
v___y_3981_ = v___y_3993_;
v___y_3982_ = v___y_3994_;
v___y_3983_ = v___y_3990_;
goto v___jp_3976_;
}
else
{
v___y_3977_ = v___y_3988_;
v___y_3978_ = v___y_3989_;
v___y_3979_ = v___y_3991_;
v___y_3980_ = v___y_3992_;
v___y_3981_ = v___y_3993_;
v___y_3982_ = v___y_3994_;
v___y_3983_ = v___y_3991_;
goto v___jp_3976_;
}
}
v___jp_3997_:
{
uint64_t v___x_4002_; uint8_t v___x_4003_; 
v___x_4002_ = 0ULL;
v___x_4003_ = lean_uint64_dec_eq(v___y_4000_, v___x_4002_);
if (v___x_4003_ == 0)
{
uint64_t v___x_4004_; uint64_t v___x_4005_; uint8_t v___x_4006_; 
v___x_4004_ = 32ULL;
v___x_4005_ = lean_uint64_shift_right(v___y_4000_, v___x_4004_);
v___x_4006_ = lean_uint64_dec_eq(v___x_4005_, v___x_4002_);
if (v___x_4006_ == 0)
{
v___y_3988_ = v___y_3998_;
v___y_3989_ = v___y_3999_;
v___y_3990_ = v___x_4004_;
v___y_3991_ = v___x_4002_;
v___y_3992_ = v___y_4000_;
v___y_3993_ = v___y_4001_;
v___y_3994_ = v___x_4005_;
goto v___jp_3987_;
}
else
{
v___y_3988_ = v___y_3998_;
v___y_3989_ = v___y_3999_;
v___y_3990_ = v___x_4004_;
v___y_3991_ = v___x_4002_;
v___y_3992_ = v___y_4000_;
v___y_3993_ = v___y_4001_;
v___y_3994_ = v___y_4000_;
goto v___jp_3987_;
}
}
else
{
if (v___y_4001_ == 0)
{
uint32_t v___x_4007_; 
v___x_4007_ = 0;
return v___x_4007_;
}
else
{
uint32_t v___x_4008_; 
v___x_4008_ = 2147483648;
return v___x_4008_;
}
}
}
v___jp_4009_:
{
uint64_t v___x_4016_; uint64_t v___x_4017_; uint64_t v___x_4018_; uint8_t v___x_4019_; 
v___x_4016_ = lean_uint64_mul(v___y_4012_, v___y_4013_);
v___x_4017_ = lean_uint64_add(v___y_4011_, v___y_4015_);
v___x_4018_ = 281474976710656ULL;
v___x_4019_ = lean_uint64_dec_lt(v___x_4016_, v___x_4018_);
if (v___x_4019_ == 0)
{
v___y_3998_ = v___x_4017_;
v___y_3999_ = v___y_4010_;
v___y_4000_ = v___x_4016_;
v___y_4001_ = v___y_4014_;
goto v___jp_3997_;
}
else
{
uint64_t v___x_4020_; uint8_t v___x_4021_; 
v___x_4020_ = 123ULL;
v___x_4021_ = lean_uint64_dec_le(v___x_4017_, v___x_4020_);
if (v___x_4021_ == 0)
{
v___y_3998_ = v___x_4017_;
v___y_3999_ = v___y_4010_;
v___y_4000_ = v___x_4016_;
v___y_4001_ = v___y_4014_;
goto v___jp_3997_;
}
else
{
uint64_t v___x_4022_; uint8_t v___x_4023_; 
v___x_4022_ = 0ULL;
v___x_4023_ = lean_uint64_dec_eq(v___x_4016_, v___x_4022_);
if (v___x_4023_ == 0)
{
uint64_t v___x_4024_; uint64_t v___x_4025_; uint8_t v___x_4026_; 
v___x_4024_ = 149ULL;
v___x_4025_ = lean_uint64_sub(v___x_4024_, v___x_4017_);
v___x_4026_ = lean_uint64_dec_eq(v___x_4025_, v___x_4022_);
if (v___x_4026_ == 0)
{
uint64_t v___x_4027_; uint8_t v___x_4028_; 
v___x_4027_ = 64ULL;
v___x_4028_ = lean_uint64_dec_lt(v___x_4025_, v___x_4027_);
if (v___x_4028_ == 0)
{
uint8_t v___x_4029_; 
v___x_4029_ = lean_uint64_dec_eq(v___x_4025_, v___x_4027_);
if (v___x_4029_ == 0)
{
v___y_3749_ = v___y_4010_;
v___y_3750_ = v___x_4022_;
v___y_3751_ = v___y_4014_;
v___y_3752_ = v___x_4022_;
goto v___jp_3748_;
}
else
{
uint64_t v___x_4030_; uint8_t v___x_4031_; 
v___x_4030_ = 9223372036854775808ULL;
v___x_4031_ = lean_uint64_dec_lt(v___x_4030_, v___x_4016_);
if (v___x_4031_ == 0)
{
v___y_3749_ = v___y_4010_;
v___y_3750_ = v___x_4022_;
v___y_3751_ = v___y_4014_;
v___y_3752_ = v___x_4022_;
goto v___jp_3748_;
}
else
{
uint64_t v___x_4032_; 
v___x_4032_ = 1ULL;
v___y_3749_ = v___y_4010_;
v___y_3750_ = v___x_4022_;
v___y_3751_ = v___y_4014_;
v___y_3752_ = v___x_4032_;
goto v___jp_3748_;
}
}
}
else
{
uint64_t v_quotient_4033_; uint64_t v___x_4034_; uint64_t v___x_4035_; uint64_t v___x_4036_; uint64_t v_remainder_4037_; uint64_t v___x_4038_; uint64_t v_half_4039_; uint8_t v___x_4040_; 
v_quotient_4033_ = lean_uint64_shift_right(v___x_4016_, v___x_4025_);
v___x_4034_ = 1ULL;
v___x_4035_ = lean_uint64_shift_left(v___x_4034_, v___x_4025_);
v___x_4036_ = lean_uint64_sub(v___x_4035_, v___x_4034_);
v_remainder_4037_ = lean_uint64_land(v___x_4016_, v___x_4036_);
v___x_4038_ = lean_uint64_sub(v___x_4025_, v___x_4034_);
v_half_4039_ = lean_uint64_shift_left(v___x_4034_, v___x_4038_);
v___x_4040_ = lean_uint64_dec_lt(v_remainder_4037_, v_half_4039_);
if (v___x_4040_ == 0)
{
uint8_t v___x_4041_; 
v___x_4041_ = lean_uint64_dec_lt(v_half_4039_, v_remainder_4037_);
if (v___x_4041_ == 0)
{
uint64_t v___x_4042_; uint8_t v___x_4043_; 
v___x_4042_ = lean_uint64_land(v_quotient_4033_, v___x_4034_);
v___x_4043_ = lean_uint64_dec_eq(v___x_4042_, v___x_4022_);
if (v___x_4043_ == 0)
{
uint64_t v___x_4044_; 
v___x_4044_ = lean_uint64_add(v_quotient_4033_, v___x_4034_);
v___y_3749_ = v___y_4010_;
v___y_3750_ = v___x_4022_;
v___y_3751_ = v___y_4014_;
v___y_3752_ = v___x_4044_;
goto v___jp_3748_;
}
else
{
v___y_3749_ = v___y_4010_;
v___y_3750_ = v___x_4022_;
v___y_3751_ = v___y_4014_;
v___y_3752_ = v_quotient_4033_;
goto v___jp_3748_;
}
}
else
{
uint64_t v___x_4045_; 
v___x_4045_ = lean_uint64_add(v_quotient_4033_, v___x_4034_);
v___y_3749_ = v___y_4010_;
v___y_3750_ = v___x_4022_;
v___y_3751_ = v___y_4014_;
v___y_3752_ = v___x_4045_;
goto v___jp_3748_;
}
}
else
{
v___y_3749_ = v___y_4010_;
v___y_3750_ = v___x_4022_;
v___y_3751_ = v___y_4014_;
v___y_3752_ = v_quotient_4033_;
goto v___jp_3748_;
}
}
}
else
{
v___y_3749_ = v___y_4010_;
v___y_3750_ = v___x_4022_;
v___y_3751_ = v___y_4014_;
v___y_3752_ = v___x_4016_;
goto v___jp_3748_;
}
}
else
{
if (v___y_4014_ == 0)
{
uint32_t v___x_4046_; 
v___x_4046_ = 0;
return v___x_4046_;
}
else
{
uint32_t v___x_4047_; 
v___x_4047_ = 2147483648;
return v___x_4047_;
}
}
}
}
}
v___jp_4051_:
{
uint64_t v___x_4057_; uint64_t v___x_4058_; uint8_t v___x_4059_; 
v___x_4057_ = lean_uint32_to_uint64(v_yExponent_4050_);
v___x_4058_ = 0ULL;
v___x_4059_ = lean_uint64_dec_eq(v___x_4057_, v___x_4058_);
if (v___x_4059_ == 0)
{
uint64_t v___x_4060_; uint64_t v___x_4061_; 
v___x_4060_ = 1ULL;
v___x_4061_ = lean_uint64_sub(v___x_4057_, v___x_4060_);
v___y_4010_ = v___y_4052_;
v___y_4011_ = v___y_4056_;
v___y_4012_ = v___y_4053_;
v___y_4013_ = v___y_4054_;
v___y_4014_ = v___y_4055_;
v___y_4015_ = v___x_4061_;
goto v___jp_4009_;
}
else
{
v___y_4010_ = v___y_4052_;
v___y_4011_ = v___y_4056_;
v___y_4012_ = v___y_4053_;
v___y_4013_ = v___y_4054_;
v___y_4014_ = v___y_4055_;
v___y_4015_ = v___x_4058_;
goto v___jp_4009_;
}
}
v___jp_4062_:
{
uint64_t v___x_4067_; uint64_t v___x_4068_; uint8_t v___x_4069_; 
v___x_4067_ = lean_uint32_to_uint64(v_xExponent_4048_);
v___x_4068_ = 0ULL;
v___x_4069_ = lean_uint64_dec_eq(v___x_4067_, v___x_4068_);
if (v___x_4069_ == 0)
{
uint64_t v___x_4070_; uint64_t v___x_4071_; 
v___x_4070_ = 1ULL;
v___x_4071_ = lean_uint64_sub(v___x_4067_, v___x_4070_);
v___y_4052_ = v___y_4063_;
v___y_4053_ = v___y_4064_;
v___y_4054_ = v___y_4066_;
v___y_4055_ = v___y_4065_;
v___y_4056_ = v___x_4071_;
goto v___jp_4051_;
}
else
{
v___y_4052_ = v___y_4063_;
v___y_4053_ = v___y_4064_;
v___y_4054_ = v___y_4066_;
v___y_4055_ = v___y_4065_;
v___y_4056_ = v___x_4068_;
goto v___jp_4051_;
}
}
v___jp_4072_:
{
uint32_t v___x_4077_; uint8_t v___x_4078_; 
v___x_4077_ = 0;
v___x_4078_ = lean_uint32_dec_eq(v_yExponent_4050_, v___x_4077_);
if (v___x_4078_ == 0)
{
uint64_t v___x_4079_; uint64_t v___x_4080_; uint64_t v___x_4081_; 
v___x_4079_ = lean_uint32_to_uint64(v___y_4074_);
v___x_4080_ = 8388608ULL;
v___x_4081_ = lean_uint64_lor(v___x_4079_, v___x_4080_);
v___y_4063_ = v___y_4073_;
v___y_4064_ = v___y_4076_;
v___y_4065_ = v___y_4075_;
v___y_4066_ = v___x_4081_;
goto v___jp_4062_;
}
else
{
uint64_t v___x_4082_; 
v___x_4082_ = lean_uint32_to_uint64(v___y_4074_);
v___y_4063_ = v___y_4073_;
v___y_4064_ = v___y_4076_;
v___y_4065_ = v___y_4075_;
v___y_4066_ = v___x_4082_;
goto v___jp_4062_;
}
}
v___jp_4083_:
{
uint32_t v___x_4085_; uint32_t v_xFraction_4086_; uint32_t v_yFraction_4087_; uint32_t v___x_4088_; uint8_t v___x_4089_; 
v___x_4085_ = 8388607;
v_xFraction_4086_ = lean_uint32_land(v_xBits_3711_, v___x_4085_);
v_yFraction_4087_ = lean_uint32_land(v_yBits_3712_, v___x_4085_);
v___x_4088_ = 0;
v___x_4089_ = lean_uint32_dec_eq(v_xExponent_4048_, v___x_4088_);
if (v___x_4089_ == 0)
{
uint64_t v___x_4090_; uint64_t v___x_4091_; uint64_t v___x_4092_; 
v___x_4090_ = lean_uint32_to_uint64(v_xFraction_4086_);
v___x_4091_ = 8388608ULL;
v___x_4092_ = lean_uint64_lor(v___x_4090_, v___x_4091_);
v___y_4073_ = v___x_4085_;
v___y_4074_ = v_yFraction_4087_;
v___y_4075_ = v___y_4084_;
v___y_4076_ = v___x_4092_;
goto v___jp_4072_;
}
else
{
uint64_t v___x_4093_; 
v___x_4093_ = lean_uint32_to_uint64(v_xFraction_4086_);
v___y_4073_ = v___x_4085_;
v___y_4074_ = v_yFraction_4087_;
v___y_4075_ = v___y_4084_;
v___y_4076_ = v___x_4093_;
goto v___jp_4072_;
}
}
v___jp_4094_:
{
uint8_t v___x_4095_; 
v___x_4095_ = 1;
v___y_4084_ = v___x_4095_;
goto v___jp_4083_;
}
v___jp_4096_:
{
uint8_t v___x_4097_; 
v___x_4097_ = 0;
v___y_4084_ = v___x_4097_;
goto v___jp_4083_;
}
v___jp_4098_:
{
if (v___y_4099_ == 0)
{
if (v___y_4100_ == 0)
{
goto v___jp_4096_;
}
else
{
goto v___jp_4094_;
}
}
else
{
if (v___y_4100_ == 0)
{
goto v___jp_4094_;
}
else
{
goto v___jp_4096_;
}
}
}
v___jp_4101_:
{
uint32_t v___x_4103_; uint32_t v___x_4104_; uint32_t v___x_4105_; uint8_t v___x_4106_; 
v___x_4103_ = 2147483648;
v___x_4104_ = lean_uint32_land(v_yBits_3712_, v___x_4103_);
v___x_4105_ = 0;
v___x_4106_ = lean_uint32_dec_eq(v___x_4104_, v___x_4105_);
if (v___x_4106_ == 0)
{
uint8_t v___x_4107_; 
v___x_4107_ = 1;
v___y_4099_ = v___y_4102_;
v___y_4100_ = v___x_4107_;
goto v___jp_4098_;
}
else
{
uint8_t v___x_4108_; 
v___x_4108_ = 0;
v___y_4099_ = v___y_4102_;
v___y_4100_ = v___x_4108_;
goto v___jp_4098_;
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_LowScale_core___boxed(lean_object* v_xBits_4115_, lean_object* v_yBits_4116_){
_start:
{
uint32_t v_xBits_boxed_4117_; uint32_t v_yBits_boxed_4118_; uint32_t v_res_4119_; lean_object* v_r_4120_; 
v_xBits_boxed_4117_ = lean_unbox_uint32(v_xBits_4115_);
lean_dec(v_xBits_4115_);
v_yBits_boxed_4118_ = lean_unbox_uint32(v_yBits_4116_);
lean_dec(v_yBits_4116_);
v_res_4119_ = lp_competition_Submission_LowScale_core(v_xBits_boxed_4117_, v_yBits_boxed_4118_);
v_r_4120_ = lean_box_uint32(v_res_4119_);
return v_r_4120_;
}
}
LEAN_EXPORT uint32_t lp_competition_Submission_LowScale_mul(uint32_t v_x_4121_, uint32_t v_y_4122_){
_start:
{
uint32_t v___y_4124_; uint32_t v___y_4128_; uint32_t v___y_4132_; uint32_t v___y_4133_; uint32_t v___y_4134_; uint64_t v___y_4138_; uint32_t v___y_4139_; uint8_t v___y_4140_; uint64_t v___y_4141_; uint32_t v___y_4153_; uint32_t v___y_4154_; uint32_t v___y_4155_; uint32_t v___y_4156_; uint32_t v___y_4157_; uint32_t v___y_4158_; uint32_t v___y_4165_; uint32_t v___y_4166_; uint32_t v___y_4167_; uint32_t v___y_4168_; uint8_t v___y_4169_; uint32_t v___y_4170_; uint32_t v___y_4174_; uint64_t v___y_4175_; uint64_t v___y_4176_; uint32_t v___y_4177_; uint32_t v___y_4178_; uint8_t v___y_4179_; uint64_t v___y_4180_; uint32_t v___y_4190_; uint8_t v___y_4191_; uint64_t v___y_4192_; uint32_t v___y_4193_; uint32_t v___y_4194_; uint64_t v___y_4195_; uint8_t v___y_4196_; uint64_t v___y_4197_; uint32_t v___y_4204_; uint64_t v___y_4205_; uint64_t v___y_4206_; uint32_t v___y_4207_; uint32_t v___y_4208_; uint8_t v___y_4209_; uint64_t v___y_4210_; uint32_t v___y_4216_; uint64_t v___y_4217_; uint64_t v___y_4218_; uint32_t v___y_4219_; uint32_t v___y_4220_; uint8_t v___y_4221_; uint64_t v___y_4222_; uint64_t v___y_4223_; uint32_t v___y_4278_; uint64_t v___y_4279_; uint64_t v___y_4280_; uint64_t v___y_4281_; uint32_t v___y_4282_; uint32_t v___y_4283_; uint64_t v___y_4284_; uint8_t v___y_4285_; uint64_t v___y_4286_; uint64_t v___y_4292_; uint32_t v___y_4293_; uint64_t v___y_4294_; uint64_t v___y_4295_; uint64_t v___y_4296_; uint32_t v___y_4297_; uint32_t v___y_4298_; uint8_t v___y_4299_; uint64_t v___y_4300_; uint64_t v___y_4301_; uint64_t v___y_4302_; uint64_t v___y_4307_; uint32_t v___y_4308_; uint64_t v___y_4309_; uint64_t v___y_4310_; uint32_t v___y_4311_; uint32_t v___y_4312_; uint64_t v___y_4313_; uint8_t v___y_4314_; uint64_t v___y_4315_; uint64_t v___y_4320_; uint32_t v___y_4321_; uint64_t v___y_4322_; uint64_t v___y_4323_; uint64_t v___y_4324_; uint32_t v___y_4325_; uint32_t v___y_4326_; uint8_t v___y_4327_; uint64_t v___y_4328_; uint64_t v___y_4329_; uint64_t v___y_4330_; uint32_t v___y_4335_; uint64_t v___y_4336_; uint64_t v___y_4337_; uint32_t v___y_4338_; uint32_t v___y_4339_; uint64_t v___y_4340_; uint8_t v___y_4341_; uint64_t v___y_4342_; uint64_t v___y_4343_; uint64_t v___y_4348_; uint32_t v___y_4349_; uint64_t v___y_4350_; uint64_t v___y_4351_; uint64_t v___y_4352_; uint32_t v___y_4353_; uint32_t v___y_4354_; uint64_t v___y_4355_; uint8_t v___y_4356_; uint64_t v___y_4357_; uint64_t v___y_4358_; uint32_t v___y_4363_; uint64_t v___y_4364_; uint64_t v___y_4365_; uint64_t v___y_4366_; uint32_t v___y_4367_; uint32_t v___y_4368_; uint64_t v___y_4369_; uint8_t v___y_4370_; uint64_t v___y_4371_; uint32_t v___y_4376_; uint64_t v___y_4377_; uint64_t v___y_4378_; uint64_t v___y_4379_; uint32_t v___y_4380_; uint32_t v___y_4381_; uint8_t v___y_4382_; uint64_t v___y_4383_; uint64_t v___y_4384_; uint64_t v___y_4385_; uint64_t v___y_4386_; uint32_t v___y_4391_; uint64_t v___y_4392_; uint64_t v___y_4393_; uint64_t v___y_4394_; uint32_t v___y_4395_; uint32_t v___y_4396_; uint64_t v___y_4397_; uint8_t v___y_4398_; uint64_t v___y_4399_; uint32_t v___y_4404_; uint64_t v___y_4405_; uint64_t v___y_4406_; uint64_t v___y_4407_; uint32_t v___y_4408_; uint32_t v___y_4409_; uint8_t v___y_4410_; uint64_t v___y_4411_; uint64_t v___y_4412_; uint32_t v___y_4416_; uint64_t v___y_4417_; uint32_t v___y_4418_; uint32_t v___y_4419_; uint64_t v___y_4420_; uint8_t v___y_4421_; uint32_t v___y_4430_; uint32_t v___y_4431_; uint32_t v___y_4432_; uint64_t v___y_4436_; uint32_t v___y_4437_; uint8_t v___y_4438_; uint64_t v___y_4439_; uint64_t v___y_4451_; uint64_t v___y_4452_; uint32_t v___y_4453_; uint32_t v___y_4454_; uint32_t v___y_4455_; uint8_t v___y_4456_; uint64_t v___y_4457_; uint64_t v___y_4458_; uint64_t v___y_4492_; uint32_t v___y_4493_; uint32_t v___y_4494_; uint32_t v___y_4495_; uint32_t v___y_4496_; uint64_t v___y_4497_; uint8_t v___y_4498_; uint64_t v___y_4499_; uint32_t v___y_4506_; uint32_t v___y_4507_; uint32_t v___y_4508_; uint32_t v___y_4509_; uint32_t v___y_4510_; uint8_t v___y_4511_; uint64_t v___y_4512_; uint64_t v___y_4513_; uint32_t v___y_4520_; uint32_t v___y_4521_; uint32_t v___y_4522_; uint32_t v___y_4523_; uint32_t v___y_4524_; uint8_t v___y_4525_; uint32_t v___y_4526_; uint64_t v___y_4527_; uint32_t v___y_4535_; uint32_t v___y_4536_; uint32_t v___y_4537_; uint32_t v___y_4538_; uint8_t v___y_4539_; uint32_t v___y_4550_; uint32_t v___y_4551_; uint32_t v___y_4552_; uint32_t v___y_4553_; uint8_t v___y_4556_; uint32_t v___y_4557_; uint32_t v___y_4558_; uint32_t v___y_4559_; uint32_t v___y_4560_; uint8_t v___y_4561_; uint8_t v___y_4562_; uint32_t v___y_4564_; uint32_t v___y_4565_; uint32_t v___y_4566_; uint32_t v___y_4567_; uint8_t v___y_4568_; uint8_t v___y_4569_; uint8_t v___y_4576_; uint32_t v___x_4593_; uint32_t v___x_4594_; uint32_t v___x_4595_; uint8_t v___x_4596_; 
v___x_4593_ = 4278190080;
v___x_4594_ = 1;
v___x_4595_ = lean_uint32_shift_left(v_x_4121_, v___x_4594_);
v___x_4596_ = lean_uint32_dec_le(v___x_4593_, v___x_4595_);
if (v___x_4596_ == 0)
{
uint32_t v___x_4597_; uint8_t v___x_4598_; 
v___x_4597_ = lean_uint32_shift_left(v_y_4122_, v___x_4594_);
v___x_4598_ = lean_uint32_dec_le(v___x_4593_, v___x_4597_);
v___y_4576_ = v___x_4598_;
goto v___jp_4575_;
}
else
{
v___y_4576_ = v___x_4596_;
goto v___jp_4575_;
}
v___jp_4123_:
{
uint32_t v___x_4125_; uint32_t v___x_4126_; 
v___x_4125_ = 8388608;
v___x_4126_ = lean_uint32_lor(v___y_4124_, v___x_4125_);
return v___x_4126_;
}
v___jp_4127_:
{
uint32_t v___x_4129_; uint32_t v___x_4130_; 
v___x_4129_ = 8388608;
v___x_4130_ = lean_uint32_lor(v___y_4128_, v___x_4129_);
return v___x_4130_;
}
v___jp_4131_:
{
uint32_t v___x_4135_; uint32_t v___x_4136_; 
v___x_4135_ = lean_uint32_land(v___y_4132_, v___y_4133_);
v___x_4136_ = lean_uint32_lor(v___y_4134_, v___x_4135_);
return v___x_4136_;
}
v___jp_4137_:
{
uint8_t v___x_4142_; 
v___x_4142_ = lean_uint64_dec_eq(v___y_4141_, v___y_4138_);
if (v___x_4142_ == 0)
{
uint64_t v___x_4143_; uint8_t v___x_4144_; 
v___x_4143_ = 8388608ULL;
v___x_4144_ = lean_uint64_dec_eq(v___y_4141_, v___x_4143_);
if (v___x_4144_ == 0)
{
uint32_t v___x_4145_; 
v___x_4145_ = lean_uint64_to_uint32(v___y_4141_);
if (v___y_4140_ == 0)
{
uint32_t v___x_4146_; 
v___x_4146_ = 0;
v___y_4132_ = v___x_4145_;
v___y_4133_ = v___y_4139_;
v___y_4134_ = v___x_4146_;
goto v___jp_4131_;
}
else
{
uint32_t v___x_4147_; 
v___x_4147_ = 2147483648;
v___y_4132_ = v___x_4145_;
v___y_4133_ = v___y_4139_;
v___y_4134_ = v___x_4147_;
goto v___jp_4131_;
}
}
else
{
if (v___y_4140_ == 0)
{
uint32_t v___x_4148_; 
v___x_4148_ = 0;
v___y_4124_ = v___x_4148_;
goto v___jp_4123_;
}
else
{
uint32_t v___x_4149_; 
v___x_4149_ = 2147483648;
v___y_4124_ = v___x_4149_;
goto v___jp_4123_;
}
}
}
else
{
if (v___y_4140_ == 0)
{
uint32_t v___x_4150_; 
v___x_4150_ = 0;
return v___x_4150_;
}
else
{
uint32_t v___x_4151_; 
v___x_4151_ = 2147483648;
return v___x_4151_;
}
}
}
v___jp_4152_:
{
uint32_t v___x_4159_; uint32_t v___x_4160_; uint32_t v___x_4161_; uint32_t v___x_4162_; uint32_t v___x_4163_; 
v___x_4159_ = lean_uint32_land(v___y_4155_, v___y_4154_);
v___x_4160_ = lean_uint32_shift_left(v___x_4159_, v___y_4156_);
v___x_4161_ = lean_uint32_lor(v___y_4158_, v___x_4160_);
v___x_4162_ = lean_uint32_land(v___y_4153_, v___y_4157_);
v___x_4163_ = lean_uint32_lor(v___x_4161_, v___x_4162_);
return v___x_4163_;
}
v___jp_4164_:
{
if (v___y_4169_ == 0)
{
uint32_t v___x_4171_; 
v___x_4171_ = 0;
v___y_4153_ = v___y_4170_;
v___y_4154_ = v___y_4165_;
v___y_4155_ = v___y_4166_;
v___y_4156_ = v___y_4167_;
v___y_4157_ = v___y_4168_;
v___y_4158_ = v___x_4171_;
goto v___jp_4152_;
}
else
{
uint32_t v___x_4172_; 
v___x_4172_ = 2147483648;
v___y_4153_ = v___y_4170_;
v___y_4154_ = v___y_4165_;
v___y_4155_ = v___y_4166_;
v___y_4156_ = v___y_4167_;
v___y_4157_ = v___y_4168_;
v___y_4158_ = v___x_4172_;
goto v___jp_4152_;
}
}
v___jp_4173_:
{
uint64_t v___x_4181_; uint64_t v_encodedExponent_4182_; uint32_t v___x_4183_; uint64_t v___x_4184_; uint8_t v___x_4185_; 
v___x_4181_ = 171ULL;
v_encodedExponent_4182_ = lean_uint64_sub(v___y_4176_, v___x_4181_);
v___x_4183_ = lean_uint64_to_uint32(v_encodedExponent_4182_);
v___x_4184_ = 8388608ULL;
v___x_4185_ = lean_uint64_dec_lt(v___y_4180_, v___x_4184_);
if (v___x_4185_ == 0)
{
uint64_t v___x_4186_; uint32_t v___x_4187_; 
v___x_4186_ = lean_uint64_sub(v___y_4180_, v___x_4184_);
v___x_4187_ = lean_uint64_to_uint32(v___x_4186_);
v___y_4165_ = v___y_4174_;
v___y_4166_ = v___x_4183_;
v___y_4167_ = v___y_4177_;
v___y_4168_ = v___y_4178_;
v___y_4169_ = v___y_4179_;
v___y_4170_ = v___x_4187_;
goto v___jp_4164_;
}
else
{
uint32_t v___x_4188_; 
v___x_4188_ = lean_uint64_to_uint32(v___y_4175_);
v___y_4165_ = v___y_4174_;
v___y_4166_ = v___x_4183_;
v___y_4167_ = v___y_4177_;
v___y_4168_ = v___y_4178_;
v___y_4169_ = v___y_4179_;
v___y_4170_ = v___x_4188_;
goto v___jp_4164_;
}
}
v___jp_4189_:
{
uint64_t v___x_4198_; uint8_t v___x_4199_; 
v___x_4198_ = 425ULL;
v___x_4199_ = lean_uint64_dec_lt(v___x_4198_, v___y_4197_);
if (v___x_4199_ == 0)
{
if (v___y_4191_ == 0)
{
v___y_4174_ = v___y_4190_;
v___y_4175_ = v___y_4192_;
v___y_4176_ = v___y_4197_;
v___y_4177_ = v___y_4193_;
v___y_4178_ = v___y_4194_;
v___y_4179_ = v___y_4196_;
v___y_4180_ = v___y_4195_;
goto v___jp_4173_;
}
else
{
uint64_t v___x_4200_; 
v___x_4200_ = 8388608ULL;
v___y_4174_ = v___y_4190_;
v___y_4175_ = v___y_4192_;
v___y_4176_ = v___y_4197_;
v___y_4177_ = v___y_4193_;
v___y_4178_ = v___y_4194_;
v___y_4179_ = v___y_4196_;
v___y_4180_ = v___x_4200_;
goto v___jp_4173_;
}
}
else
{
if (v___y_4196_ == 0)
{
uint32_t v___x_4201_; 
v___x_4201_ = 2139095040;
return v___x_4201_;
}
else
{
uint32_t v___x_4202_; 
v___x_4202_ = 4286578688;
return v___x_4202_;
}
}
}
v___jp_4203_:
{
uint64_t v___x_4211_; uint8_t v_carry_4212_; 
v___x_4211_ = 16777216ULL;
v_carry_4212_ = lean_uint64_dec_eq(v___y_4210_, v___x_4211_);
if (v_carry_4212_ == 0)
{
v___y_4190_ = v___y_4204_;
v___y_4191_ = v_carry_4212_;
v___y_4192_ = v___y_4206_;
v___y_4193_ = v___y_4207_;
v___y_4194_ = v___y_4208_;
v___y_4195_ = v___y_4210_;
v___y_4196_ = v___y_4209_;
v___y_4197_ = v___y_4205_;
goto v___jp_4189_;
}
else
{
uint64_t v___x_4213_; uint64_t v___x_4214_; 
v___x_4213_ = 1ULL;
v___x_4214_ = lean_uint64_add(v___y_4205_, v___x_4213_);
v___y_4190_ = v___y_4204_;
v___y_4191_ = v_carry_4212_;
v___y_4192_ = v___y_4206_;
v___y_4193_ = v___y_4207_;
v___y_4194_ = v___y_4208_;
v___y_4195_ = v___y_4210_;
v___y_4196_ = v___y_4209_;
v___y_4197_ = v___x_4214_;
goto v___jp_4189_;
}
}
v___jp_4215_:
{
uint64_t v_position_4224_; uint64_t v___x_4225_; uint8_t v___x_4226_; 
v_position_4224_ = lean_uint64_add(v___y_4223_, v___y_4222_);
v___x_4225_ = 172ULL;
v___x_4226_ = lean_uint64_dec_lt(v_position_4224_, v___x_4225_);
if (v___x_4226_ == 0)
{
uint64_t v___x_4227_; uint8_t v___x_4228_; 
v___x_4227_ = 23ULL;
v___x_4228_ = lean_uint64_dec_lt(v___y_4223_, v___x_4227_);
if (v___x_4228_ == 0)
{
uint64_t v___x_4229_; uint8_t v___x_4230_; 
v___x_4229_ = lean_uint64_sub(v___y_4223_, v___x_4227_);
v___x_4230_ = lean_uint64_dec_eq(v___x_4229_, v___y_4218_);
if (v___x_4230_ == 0)
{
uint64_t v___x_4231_; uint8_t v___x_4232_; 
v___x_4231_ = 64ULL;
v___x_4232_ = lean_uint64_dec_lt(v___x_4229_, v___x_4231_);
if (v___x_4232_ == 0)
{
uint8_t v___x_4233_; 
v___x_4233_ = lean_uint64_dec_eq(v___x_4229_, v___x_4231_);
if (v___x_4233_ == 0)
{
v___y_4204_ = v___y_4216_;
v___y_4205_ = v_position_4224_;
v___y_4206_ = v___y_4218_;
v___y_4207_ = v___y_4219_;
v___y_4208_ = v___y_4220_;
v___y_4209_ = v___y_4221_;
v___y_4210_ = v___y_4218_;
goto v___jp_4203_;
}
else
{
uint64_t v___x_4234_; uint8_t v___x_4235_; 
v___x_4234_ = 9223372036854775808ULL;
v___x_4235_ = lean_uint64_dec_lt(v___x_4234_, v___y_4217_);
if (v___x_4235_ == 0)
{
v___y_4204_ = v___y_4216_;
v___y_4205_ = v_position_4224_;
v___y_4206_ = v___y_4218_;
v___y_4207_ = v___y_4219_;
v___y_4208_ = v___y_4220_;
v___y_4209_ = v___y_4221_;
v___y_4210_ = v___y_4218_;
goto v___jp_4203_;
}
else
{
uint64_t v___x_4236_; 
v___x_4236_ = 1ULL;
v___y_4204_ = v___y_4216_;
v___y_4205_ = v_position_4224_;
v___y_4206_ = v___y_4218_;
v___y_4207_ = v___y_4219_;
v___y_4208_ = v___y_4220_;
v___y_4209_ = v___y_4221_;
v___y_4210_ = v___x_4236_;
goto v___jp_4203_;
}
}
}
else
{
uint64_t v_quotient_4237_; uint64_t v___x_4238_; uint64_t v___x_4239_; uint64_t v___x_4240_; uint64_t v_remainder_4241_; uint64_t v___x_4242_; uint64_t v_half_4243_; uint8_t v___x_4244_; 
v_quotient_4237_ = lean_uint64_shift_right(v___y_4217_, v___x_4229_);
v___x_4238_ = 1ULL;
v___x_4239_ = lean_uint64_shift_left(v___x_4238_, v___x_4229_);
v___x_4240_ = lean_uint64_sub(v___x_4239_, v___x_4238_);
v_remainder_4241_ = lean_uint64_land(v___y_4217_, v___x_4240_);
v___x_4242_ = lean_uint64_sub(v___x_4229_, v___x_4238_);
v_half_4243_ = lean_uint64_shift_left(v___x_4238_, v___x_4242_);
v___x_4244_ = lean_uint64_dec_lt(v_remainder_4241_, v_half_4243_);
if (v___x_4244_ == 0)
{
uint8_t v___x_4245_; 
v___x_4245_ = lean_uint64_dec_lt(v_half_4243_, v_remainder_4241_);
if (v___x_4245_ == 0)
{
uint64_t v___x_4246_; uint8_t v___x_4247_; 
v___x_4246_ = lean_uint64_land(v_quotient_4237_, v___x_4238_);
v___x_4247_ = lean_uint64_dec_eq(v___x_4246_, v___y_4218_);
if (v___x_4247_ == 0)
{
uint64_t v___x_4248_; 
v___x_4248_ = lean_uint64_add(v_quotient_4237_, v___x_4238_);
v___y_4204_ = v___y_4216_;
v___y_4205_ = v_position_4224_;
v___y_4206_ = v___y_4218_;
v___y_4207_ = v___y_4219_;
v___y_4208_ = v___y_4220_;
v___y_4209_ = v___y_4221_;
v___y_4210_ = v___x_4248_;
goto v___jp_4203_;
}
else
{
v___y_4204_ = v___y_4216_;
v___y_4205_ = v_position_4224_;
v___y_4206_ = v___y_4218_;
v___y_4207_ = v___y_4219_;
v___y_4208_ = v___y_4220_;
v___y_4209_ = v___y_4221_;
v___y_4210_ = v_quotient_4237_;
goto v___jp_4203_;
}
}
else
{
uint64_t v___x_4249_; 
v___x_4249_ = lean_uint64_add(v_quotient_4237_, v___x_4238_);
v___y_4204_ = v___y_4216_;
v___y_4205_ = v_position_4224_;
v___y_4206_ = v___y_4218_;
v___y_4207_ = v___y_4219_;
v___y_4208_ = v___y_4220_;
v___y_4209_ = v___y_4221_;
v___y_4210_ = v___x_4249_;
goto v___jp_4203_;
}
}
else
{
v___y_4204_ = v___y_4216_;
v___y_4205_ = v_position_4224_;
v___y_4206_ = v___y_4218_;
v___y_4207_ = v___y_4219_;
v___y_4208_ = v___y_4220_;
v___y_4209_ = v___y_4221_;
v___y_4210_ = v_quotient_4237_;
goto v___jp_4203_;
}
}
}
else
{
v___y_4204_ = v___y_4216_;
v___y_4205_ = v_position_4224_;
v___y_4206_ = v___y_4218_;
v___y_4207_ = v___y_4219_;
v___y_4208_ = v___y_4220_;
v___y_4209_ = v___y_4221_;
v___y_4210_ = v___y_4217_;
goto v___jp_4203_;
}
}
else
{
uint64_t v___x_4250_; uint64_t v___x_4251_; 
v___x_4250_ = lean_uint64_sub(v___x_4227_, v___y_4223_);
v___x_4251_ = lean_uint64_shift_left(v___y_4217_, v___x_4250_);
v___y_4204_ = v___y_4216_;
v___y_4205_ = v_position_4224_;
v___y_4206_ = v___y_4218_;
v___y_4207_ = v___y_4219_;
v___y_4208_ = v___y_4220_;
v___y_4209_ = v___y_4221_;
v___y_4210_ = v___x_4251_;
goto v___jp_4203_;
}
}
else
{
uint64_t v___x_4252_; uint8_t v___x_4253_; 
v___x_4252_ = 149ULL;
v___x_4253_ = lean_uint64_dec_lt(v___y_4222_, v___x_4252_);
if (v___x_4253_ == 0)
{
uint64_t v___x_4254_; uint64_t v___x_4255_; 
v___x_4254_ = lean_uint64_sub(v___y_4222_, v___x_4252_);
v___x_4255_ = lean_uint64_shift_left(v___y_4217_, v___x_4254_);
v___y_4138_ = v___y_4218_;
v___y_4139_ = v___y_4220_;
v___y_4140_ = v___y_4221_;
v___y_4141_ = v___x_4255_;
goto v___jp_4137_;
}
else
{
uint64_t v___x_4256_; uint8_t v___x_4257_; 
v___x_4256_ = lean_uint64_sub(v___x_4252_, v___y_4222_);
v___x_4257_ = lean_uint64_dec_eq(v___x_4256_, v___y_4218_);
if (v___x_4257_ == 0)
{
uint64_t v___x_4258_; uint8_t v___x_4259_; 
v___x_4258_ = 64ULL;
v___x_4259_ = lean_uint64_dec_lt(v___x_4256_, v___x_4258_);
if (v___x_4259_ == 0)
{
uint8_t v___x_4260_; 
v___x_4260_ = lean_uint64_dec_eq(v___x_4256_, v___x_4258_);
if (v___x_4260_ == 0)
{
v___y_4138_ = v___y_4218_;
v___y_4139_ = v___y_4220_;
v___y_4140_ = v___y_4221_;
v___y_4141_ = v___y_4218_;
goto v___jp_4137_;
}
else
{
uint64_t v___x_4261_; uint8_t v___x_4262_; 
v___x_4261_ = 9223372036854775808ULL;
v___x_4262_ = lean_uint64_dec_lt(v___x_4261_, v___y_4217_);
if (v___x_4262_ == 0)
{
v___y_4138_ = v___y_4218_;
v___y_4139_ = v___y_4220_;
v___y_4140_ = v___y_4221_;
v___y_4141_ = v___y_4218_;
goto v___jp_4137_;
}
else
{
uint64_t v___x_4263_; 
v___x_4263_ = 1ULL;
v___y_4138_ = v___y_4218_;
v___y_4139_ = v___y_4220_;
v___y_4140_ = v___y_4221_;
v___y_4141_ = v___x_4263_;
goto v___jp_4137_;
}
}
}
else
{
uint64_t v_quotient_4264_; uint64_t v___x_4265_; uint64_t v___x_4266_; uint64_t v___x_4267_; uint64_t v_remainder_4268_; uint64_t v___x_4269_; uint64_t v_half_4270_; uint8_t v___x_4271_; 
v_quotient_4264_ = lean_uint64_shift_right(v___y_4217_, v___x_4256_);
v___x_4265_ = 1ULL;
v___x_4266_ = lean_uint64_shift_left(v___x_4265_, v___x_4256_);
v___x_4267_ = lean_uint64_sub(v___x_4266_, v___x_4265_);
v_remainder_4268_ = lean_uint64_land(v___y_4217_, v___x_4267_);
v___x_4269_ = lean_uint64_sub(v___x_4256_, v___x_4265_);
v_half_4270_ = lean_uint64_shift_left(v___x_4265_, v___x_4269_);
v___x_4271_ = lean_uint64_dec_lt(v_remainder_4268_, v_half_4270_);
if (v___x_4271_ == 0)
{
uint8_t v___x_4272_; 
v___x_4272_ = lean_uint64_dec_lt(v_half_4270_, v_remainder_4268_);
if (v___x_4272_ == 0)
{
uint64_t v___x_4273_; uint8_t v___x_4274_; 
v___x_4273_ = lean_uint64_land(v_quotient_4264_, v___x_4265_);
v___x_4274_ = lean_uint64_dec_eq(v___x_4273_, v___y_4218_);
if (v___x_4274_ == 0)
{
uint64_t v___x_4275_; 
v___x_4275_ = lean_uint64_add(v_quotient_4264_, v___x_4265_);
v___y_4138_ = v___y_4218_;
v___y_4139_ = v___y_4220_;
v___y_4140_ = v___y_4221_;
v___y_4141_ = v___x_4275_;
goto v___jp_4137_;
}
else
{
v___y_4138_ = v___y_4218_;
v___y_4139_ = v___y_4220_;
v___y_4140_ = v___y_4221_;
v___y_4141_ = v_quotient_4264_;
goto v___jp_4137_;
}
}
else
{
uint64_t v___x_4276_; 
v___x_4276_ = lean_uint64_add(v_quotient_4264_, v___x_4265_);
v___y_4138_ = v___y_4218_;
v___y_4139_ = v___y_4220_;
v___y_4140_ = v___y_4221_;
v___y_4141_ = v___x_4276_;
goto v___jp_4137_;
}
}
else
{
v___y_4138_ = v___y_4218_;
v___y_4139_ = v___y_4220_;
v___y_4140_ = v___y_4221_;
v___y_4141_ = v_quotient_4264_;
goto v___jp_4137_;
}
}
}
else
{
v___y_4138_ = v___y_4218_;
v___y_4139_ = v___y_4220_;
v___y_4140_ = v___y_4221_;
v___y_4141_ = v___y_4217_;
goto v___jp_4137_;
}
}
}
}
v___jp_4277_:
{
uint64_t v___x_4287_; uint64_t v___x_4288_; uint8_t v___x_4289_; 
v___x_4287_ = 1ULL;
v___x_4288_ = lean_uint64_shift_right(v___y_4281_, v___x_4287_);
v___x_4289_ = lean_uint64_dec_eq(v___x_4288_, v___y_4280_);
if (v___x_4289_ == 0)
{
uint64_t v___x_4290_; 
v___x_4290_ = lean_uint64_add(v___y_4286_, v___x_4287_);
v___y_4216_ = v___y_4278_;
v___y_4217_ = v___y_4279_;
v___y_4218_ = v___y_4280_;
v___y_4219_ = v___y_4282_;
v___y_4220_ = v___y_4283_;
v___y_4221_ = v___y_4285_;
v___y_4222_ = v___y_4284_;
v___y_4223_ = v___x_4290_;
goto v___jp_4215_;
}
else
{
v___y_4216_ = v___y_4278_;
v___y_4217_ = v___y_4279_;
v___y_4218_ = v___y_4280_;
v___y_4219_ = v___y_4282_;
v___y_4220_ = v___y_4283_;
v___y_4221_ = v___y_4285_;
v___y_4222_ = v___y_4284_;
v___y_4223_ = v___y_4286_;
goto v___jp_4215_;
}
}
v___jp_4291_:
{
uint64_t v___x_4303_; uint8_t v___x_4304_; 
v___x_4303_ = lean_uint64_shift_right(v___y_4292_, v___y_4301_);
v___x_4304_ = lean_uint64_dec_eq(v___x_4303_, v___y_4296_);
if (v___x_4304_ == 0)
{
uint64_t v___x_4305_; 
v___x_4305_ = lean_uint64_add(v___y_4294_, v___y_4301_);
v___y_4278_ = v___y_4293_;
v___y_4279_ = v___y_4295_;
v___y_4280_ = v___y_4296_;
v___y_4281_ = v___y_4302_;
v___y_4282_ = v___y_4297_;
v___y_4283_ = v___y_4298_;
v___y_4284_ = v___y_4300_;
v___y_4285_ = v___y_4299_;
v___y_4286_ = v___x_4305_;
goto v___jp_4277_;
}
else
{
v___y_4278_ = v___y_4293_;
v___y_4279_ = v___y_4295_;
v___y_4280_ = v___y_4296_;
v___y_4281_ = v___y_4302_;
v___y_4282_ = v___y_4297_;
v___y_4283_ = v___y_4298_;
v___y_4284_ = v___y_4300_;
v___y_4285_ = v___y_4299_;
v___y_4286_ = v___y_4294_;
goto v___jp_4277_;
}
}
v___jp_4306_:
{
uint64_t v___x_4316_; uint64_t v___x_4317_; uint8_t v___x_4318_; 
v___x_4316_ = 2ULL;
v___x_4317_ = lean_uint64_shift_right(v___y_4307_, v___x_4316_);
v___x_4318_ = lean_uint64_dec_eq(v___x_4317_, v___y_4310_);
if (v___x_4318_ == 0)
{
v___y_4292_ = v___y_4307_;
v___y_4293_ = v___y_4308_;
v___y_4294_ = v___y_4315_;
v___y_4295_ = v___y_4309_;
v___y_4296_ = v___y_4310_;
v___y_4297_ = v___y_4311_;
v___y_4298_ = v___y_4312_;
v___y_4299_ = v___y_4314_;
v___y_4300_ = v___y_4313_;
v___y_4301_ = v___x_4316_;
v___y_4302_ = v___x_4317_;
goto v___jp_4291_;
}
else
{
v___y_4292_ = v___y_4307_;
v___y_4293_ = v___y_4308_;
v___y_4294_ = v___y_4315_;
v___y_4295_ = v___y_4309_;
v___y_4296_ = v___y_4310_;
v___y_4297_ = v___y_4311_;
v___y_4298_ = v___y_4312_;
v___y_4299_ = v___y_4314_;
v___y_4300_ = v___y_4313_;
v___y_4301_ = v___x_4316_;
v___y_4302_ = v___y_4307_;
goto v___jp_4291_;
}
}
v___jp_4319_:
{
uint64_t v___x_4331_; uint8_t v___x_4332_; 
v___x_4331_ = lean_uint64_shift_right(v___y_4329_, v___y_4324_);
v___x_4332_ = lean_uint64_dec_eq(v___x_4331_, v___y_4323_);
if (v___x_4332_ == 0)
{
uint64_t v___x_4333_; 
v___x_4333_ = lean_uint64_add(v___y_4320_, v___y_4324_);
v___y_4307_ = v___y_4330_;
v___y_4308_ = v___y_4321_;
v___y_4309_ = v___y_4322_;
v___y_4310_ = v___y_4323_;
v___y_4311_ = v___y_4325_;
v___y_4312_ = v___y_4326_;
v___y_4313_ = v___y_4328_;
v___y_4314_ = v___y_4327_;
v___y_4315_ = v___x_4333_;
goto v___jp_4306_;
}
else
{
v___y_4307_ = v___y_4330_;
v___y_4308_ = v___y_4321_;
v___y_4309_ = v___y_4322_;
v___y_4310_ = v___y_4323_;
v___y_4311_ = v___y_4325_;
v___y_4312_ = v___y_4326_;
v___y_4313_ = v___y_4328_;
v___y_4314_ = v___y_4327_;
v___y_4315_ = v___y_4320_;
goto v___jp_4306_;
}
}
v___jp_4334_:
{
uint64_t v___x_4344_; uint64_t v___x_4345_; uint8_t v___x_4346_; 
v___x_4344_ = 4ULL;
v___x_4345_ = lean_uint64_shift_right(v___y_4342_, v___x_4344_);
v___x_4346_ = lean_uint64_dec_eq(v___x_4345_, v___y_4337_);
if (v___x_4346_ == 0)
{
v___y_4320_ = v___y_4343_;
v___y_4321_ = v___y_4335_;
v___y_4322_ = v___y_4336_;
v___y_4323_ = v___y_4337_;
v___y_4324_ = v___x_4344_;
v___y_4325_ = v___y_4338_;
v___y_4326_ = v___y_4339_;
v___y_4327_ = v___y_4341_;
v___y_4328_ = v___y_4340_;
v___y_4329_ = v___y_4342_;
v___y_4330_ = v___x_4345_;
goto v___jp_4319_;
}
else
{
v___y_4320_ = v___y_4343_;
v___y_4321_ = v___y_4335_;
v___y_4322_ = v___y_4336_;
v___y_4323_ = v___y_4337_;
v___y_4324_ = v___x_4344_;
v___y_4325_ = v___y_4338_;
v___y_4326_ = v___y_4339_;
v___y_4327_ = v___y_4341_;
v___y_4328_ = v___y_4340_;
v___y_4329_ = v___y_4342_;
v___y_4330_ = v___y_4342_;
goto v___jp_4319_;
}
}
v___jp_4347_:
{
uint64_t v___x_4359_; uint8_t v___x_4360_; 
v___x_4359_ = lean_uint64_shift_right(v___y_4351_, v___y_4348_);
v___x_4360_ = lean_uint64_dec_eq(v___x_4359_, v___y_4352_);
if (v___x_4360_ == 0)
{
uint64_t v___x_4361_; 
v___x_4361_ = lean_uint64_add(v___y_4355_, v___y_4348_);
v___y_4335_ = v___y_4349_;
v___y_4336_ = v___y_4350_;
v___y_4337_ = v___y_4352_;
v___y_4338_ = v___y_4353_;
v___y_4339_ = v___y_4354_;
v___y_4340_ = v___y_4357_;
v___y_4341_ = v___y_4356_;
v___y_4342_ = v___y_4358_;
v___y_4343_ = v___x_4361_;
goto v___jp_4334_;
}
else
{
v___y_4335_ = v___y_4349_;
v___y_4336_ = v___y_4350_;
v___y_4337_ = v___y_4352_;
v___y_4338_ = v___y_4353_;
v___y_4339_ = v___y_4354_;
v___y_4340_ = v___y_4357_;
v___y_4341_ = v___y_4356_;
v___y_4342_ = v___y_4358_;
v___y_4343_ = v___y_4355_;
goto v___jp_4334_;
}
}
v___jp_4362_:
{
uint64_t v___x_4372_; uint64_t v___x_4373_; uint8_t v___x_4374_; 
v___x_4372_ = 8ULL;
v___x_4373_ = lean_uint64_shift_right(v___y_4365_, v___x_4372_);
v___x_4374_ = lean_uint64_dec_eq(v___x_4373_, v___y_4366_);
if (v___x_4374_ == 0)
{
v___y_4348_ = v___x_4372_;
v___y_4349_ = v___y_4363_;
v___y_4350_ = v___y_4364_;
v___y_4351_ = v___y_4365_;
v___y_4352_ = v___y_4366_;
v___y_4353_ = v___y_4367_;
v___y_4354_ = v___y_4368_;
v___y_4355_ = v___y_4371_;
v___y_4356_ = v___y_4370_;
v___y_4357_ = v___y_4369_;
v___y_4358_ = v___x_4373_;
goto v___jp_4347_;
}
else
{
v___y_4348_ = v___x_4372_;
v___y_4349_ = v___y_4363_;
v___y_4350_ = v___y_4364_;
v___y_4351_ = v___y_4365_;
v___y_4352_ = v___y_4366_;
v___y_4353_ = v___y_4367_;
v___y_4354_ = v___y_4368_;
v___y_4355_ = v___y_4371_;
v___y_4356_ = v___y_4370_;
v___y_4357_ = v___y_4369_;
v___y_4358_ = v___y_4365_;
goto v___jp_4347_;
}
}
v___jp_4375_:
{
uint64_t v___x_4387_; uint8_t v___x_4388_; 
v___x_4387_ = lean_uint64_shift_right(v___y_4377_, v___y_4385_);
v___x_4388_ = lean_uint64_dec_eq(v___x_4387_, v___y_4379_);
if (v___x_4388_ == 0)
{
uint64_t v___x_4389_; 
v___x_4389_ = lean_uint64_add(v___y_4384_, v___y_4385_);
v___y_4363_ = v___y_4376_;
v___y_4364_ = v___y_4378_;
v___y_4365_ = v___y_4386_;
v___y_4366_ = v___y_4379_;
v___y_4367_ = v___y_4380_;
v___y_4368_ = v___y_4381_;
v___y_4369_ = v___y_4383_;
v___y_4370_ = v___y_4382_;
v___y_4371_ = v___x_4389_;
goto v___jp_4362_;
}
else
{
v___y_4363_ = v___y_4376_;
v___y_4364_ = v___y_4378_;
v___y_4365_ = v___y_4386_;
v___y_4366_ = v___y_4379_;
v___y_4367_ = v___y_4380_;
v___y_4368_ = v___y_4381_;
v___y_4369_ = v___y_4383_;
v___y_4370_ = v___y_4382_;
v___y_4371_ = v___y_4384_;
goto v___jp_4362_;
}
}
v___jp_4390_:
{
uint64_t v___x_4400_; uint64_t v___x_4401_; uint8_t v___x_4402_; 
v___x_4400_ = 16ULL;
v___x_4401_ = lean_uint64_shift_right(v___y_4393_, v___x_4400_);
v___x_4402_ = lean_uint64_dec_eq(v___x_4401_, v___y_4394_);
if (v___x_4402_ == 0)
{
v___y_4376_ = v___y_4391_;
v___y_4377_ = v___y_4393_;
v___y_4378_ = v___y_4392_;
v___y_4379_ = v___y_4394_;
v___y_4380_ = v___y_4395_;
v___y_4381_ = v___y_4396_;
v___y_4382_ = v___y_4398_;
v___y_4383_ = v___y_4397_;
v___y_4384_ = v___y_4399_;
v___y_4385_ = v___x_4400_;
v___y_4386_ = v___x_4401_;
goto v___jp_4375_;
}
else
{
v___y_4376_ = v___y_4391_;
v___y_4377_ = v___y_4393_;
v___y_4378_ = v___y_4392_;
v___y_4379_ = v___y_4394_;
v___y_4380_ = v___y_4395_;
v___y_4381_ = v___y_4396_;
v___y_4382_ = v___y_4398_;
v___y_4383_ = v___y_4397_;
v___y_4384_ = v___y_4399_;
v___y_4385_ = v___x_4400_;
v___y_4386_ = v___y_4393_;
goto v___jp_4375_;
}
}
v___jp_4403_:
{
uint64_t v___x_4413_; uint8_t v___x_4414_; 
v___x_4413_ = lean_uint64_shift_right(v___y_4405_, v___y_4406_);
v___x_4414_ = lean_uint64_dec_eq(v___x_4413_, v___y_4407_);
if (v___x_4414_ == 0)
{
v___y_4391_ = v___y_4404_;
v___y_4392_ = v___y_4405_;
v___y_4393_ = v___y_4412_;
v___y_4394_ = v___y_4407_;
v___y_4395_ = v___y_4408_;
v___y_4396_ = v___y_4409_;
v___y_4397_ = v___y_4411_;
v___y_4398_ = v___y_4410_;
v___y_4399_ = v___y_4406_;
goto v___jp_4390_;
}
else
{
v___y_4391_ = v___y_4404_;
v___y_4392_ = v___y_4405_;
v___y_4393_ = v___y_4412_;
v___y_4394_ = v___y_4407_;
v___y_4395_ = v___y_4408_;
v___y_4396_ = v___y_4409_;
v___y_4397_ = v___y_4411_;
v___y_4398_ = v___y_4410_;
v___y_4399_ = v___y_4407_;
goto v___jp_4390_;
}
}
v___jp_4415_:
{
uint64_t v___x_4422_; uint8_t v___x_4423_; 
v___x_4422_ = 0ULL;
v___x_4423_ = lean_uint64_dec_eq(v___y_4417_, v___x_4422_);
if (v___x_4423_ == 0)
{
uint64_t v___x_4424_; uint64_t v___x_4425_; uint8_t v___x_4426_; 
v___x_4424_ = 32ULL;
v___x_4425_ = lean_uint64_shift_right(v___y_4417_, v___x_4424_);
v___x_4426_ = lean_uint64_dec_eq(v___x_4425_, v___x_4422_);
if (v___x_4426_ == 0)
{
v___y_4404_ = v___y_4416_;
v___y_4405_ = v___y_4417_;
v___y_4406_ = v___x_4424_;
v___y_4407_ = v___x_4422_;
v___y_4408_ = v___y_4418_;
v___y_4409_ = v___y_4419_;
v___y_4410_ = v___y_4421_;
v___y_4411_ = v___y_4420_;
v___y_4412_ = v___x_4425_;
goto v___jp_4403_;
}
else
{
v___y_4404_ = v___y_4416_;
v___y_4405_ = v___y_4417_;
v___y_4406_ = v___x_4424_;
v___y_4407_ = v___x_4422_;
v___y_4408_ = v___y_4418_;
v___y_4409_ = v___y_4419_;
v___y_4410_ = v___y_4421_;
v___y_4411_ = v___y_4420_;
v___y_4412_ = v___y_4417_;
goto v___jp_4403_;
}
}
else
{
if (v___y_4421_ == 0)
{
uint32_t v___x_4427_; 
v___x_4427_ = 0;
return v___x_4427_;
}
else
{
uint32_t v___x_4428_; 
v___x_4428_ = 2147483648;
return v___x_4428_;
}
}
}
v___jp_4429_:
{
uint32_t v___x_4433_; uint32_t v___x_4434_; 
v___x_4433_ = lean_uint32_land(v___y_4431_, v___y_4430_);
v___x_4434_ = lean_uint32_lor(v___y_4432_, v___x_4433_);
return v___x_4434_;
}
v___jp_4435_:
{
uint8_t v___x_4440_; 
v___x_4440_ = lean_uint64_dec_eq(v___y_4439_, v___y_4436_);
if (v___x_4440_ == 0)
{
uint64_t v___x_4441_; uint8_t v___x_4442_; 
v___x_4441_ = 8388608ULL;
v___x_4442_ = lean_uint64_dec_eq(v___y_4439_, v___x_4441_);
if (v___x_4442_ == 0)
{
uint32_t v___x_4443_; 
v___x_4443_ = lean_uint64_to_uint32(v___y_4439_);
if (v___y_4438_ == 0)
{
uint32_t v___x_4444_; 
v___x_4444_ = 0;
v___y_4430_ = v___y_4437_;
v___y_4431_ = v___x_4443_;
v___y_4432_ = v___x_4444_;
goto v___jp_4429_;
}
else
{
uint32_t v___x_4445_; 
v___x_4445_ = 2147483648;
v___y_4430_ = v___y_4437_;
v___y_4431_ = v___x_4443_;
v___y_4432_ = v___x_4445_;
goto v___jp_4429_;
}
}
else
{
if (v___y_4438_ == 0)
{
uint32_t v___x_4446_; 
v___x_4446_ = 0;
v___y_4128_ = v___x_4446_;
goto v___jp_4127_;
}
else
{
uint32_t v___x_4447_; 
v___x_4447_ = 2147483648;
v___y_4128_ = v___x_4447_;
goto v___jp_4127_;
}
}
}
else
{
if (v___y_4438_ == 0)
{
uint32_t v___x_4448_; 
v___x_4448_ = 0;
return v___x_4448_;
}
else
{
uint32_t v___x_4449_; 
v___x_4449_ = 2147483648;
return v___x_4449_;
}
}
}
v___jp_4450_:
{
uint64_t v___x_4459_; uint64_t v___x_4460_; uint64_t v___x_4461_; uint8_t v___x_4462_; 
v___x_4459_ = lean_uint64_mul(v___y_4457_, v___y_4452_);
v___x_4460_ = lean_uint64_add(v___y_4451_, v___y_4458_);
v___x_4461_ = 281474976710656ULL;
v___x_4462_ = lean_uint64_dec_lt(v___x_4459_, v___x_4461_);
if (v___x_4462_ == 0)
{
v___y_4416_ = v___y_4453_;
v___y_4417_ = v___x_4459_;
v___y_4418_ = v___y_4454_;
v___y_4419_ = v___y_4455_;
v___y_4420_ = v___x_4460_;
v___y_4421_ = v___y_4456_;
goto v___jp_4415_;
}
else
{
uint64_t v___x_4463_; uint8_t v___x_4464_; 
v___x_4463_ = 123ULL;
v___x_4464_ = lean_uint64_dec_le(v___x_4460_, v___x_4463_);
if (v___x_4464_ == 0)
{
v___y_4416_ = v___y_4453_;
v___y_4417_ = v___x_4459_;
v___y_4418_ = v___y_4454_;
v___y_4419_ = v___y_4455_;
v___y_4420_ = v___x_4460_;
v___y_4421_ = v___y_4456_;
goto v___jp_4415_;
}
else
{
uint64_t v___x_4465_; uint8_t v___x_4466_; 
v___x_4465_ = 0ULL;
v___x_4466_ = lean_uint64_dec_eq(v___x_4459_, v___x_4465_);
if (v___x_4466_ == 0)
{
uint64_t v___x_4467_; uint64_t v___x_4468_; uint8_t v___x_4469_; 
v___x_4467_ = 149ULL;
v___x_4468_ = lean_uint64_sub(v___x_4467_, v___x_4460_);
v___x_4469_ = lean_uint64_dec_eq(v___x_4468_, v___x_4465_);
if (v___x_4469_ == 0)
{
uint64_t v___x_4470_; uint8_t v___x_4471_; 
v___x_4470_ = 64ULL;
v___x_4471_ = lean_uint64_dec_lt(v___x_4468_, v___x_4470_);
if (v___x_4471_ == 0)
{
uint8_t v___x_4472_; 
v___x_4472_ = lean_uint64_dec_eq(v___x_4468_, v___x_4470_);
if (v___x_4472_ == 0)
{
v___y_4436_ = v___x_4465_;
v___y_4437_ = v___y_4455_;
v___y_4438_ = v___y_4456_;
v___y_4439_ = v___x_4465_;
goto v___jp_4435_;
}
else
{
uint64_t v___x_4473_; uint8_t v___x_4474_; 
v___x_4473_ = 9223372036854775808ULL;
v___x_4474_ = lean_uint64_dec_lt(v___x_4473_, v___x_4459_);
if (v___x_4474_ == 0)
{
v___y_4436_ = v___x_4465_;
v___y_4437_ = v___y_4455_;
v___y_4438_ = v___y_4456_;
v___y_4439_ = v___x_4465_;
goto v___jp_4435_;
}
else
{
uint64_t v___x_4475_; 
v___x_4475_ = 1ULL;
v___y_4436_ = v___x_4465_;
v___y_4437_ = v___y_4455_;
v___y_4438_ = v___y_4456_;
v___y_4439_ = v___x_4475_;
goto v___jp_4435_;
}
}
}
else
{
uint64_t v_quotient_4476_; uint64_t v___x_4477_; uint64_t v___x_4478_; uint64_t v___x_4479_; uint64_t v_remainder_4480_; uint64_t v___x_4481_; uint64_t v_half_4482_; uint8_t v___x_4483_; 
v_quotient_4476_ = lean_uint64_shift_right(v___x_4459_, v___x_4468_);
v___x_4477_ = 1ULL;
v___x_4478_ = lean_uint64_shift_left(v___x_4477_, v___x_4468_);
v___x_4479_ = lean_uint64_sub(v___x_4478_, v___x_4477_);
v_remainder_4480_ = lean_uint64_land(v___x_4459_, v___x_4479_);
v___x_4481_ = lean_uint64_sub(v___x_4468_, v___x_4477_);
v_half_4482_ = lean_uint64_shift_left(v___x_4477_, v___x_4481_);
v___x_4483_ = lean_uint64_dec_lt(v_remainder_4480_, v_half_4482_);
if (v___x_4483_ == 0)
{
uint8_t v___x_4484_; 
v___x_4484_ = lean_uint64_dec_lt(v_half_4482_, v_remainder_4480_);
if (v___x_4484_ == 0)
{
uint64_t v___x_4485_; uint8_t v___x_4486_; 
v___x_4485_ = lean_uint64_land(v_quotient_4476_, v___x_4477_);
v___x_4486_ = lean_uint64_dec_eq(v___x_4485_, v___x_4465_);
if (v___x_4486_ == 0)
{
uint64_t v___x_4487_; 
v___x_4487_ = lean_uint64_add(v_quotient_4476_, v___x_4477_);
v___y_4436_ = v___x_4465_;
v___y_4437_ = v___y_4455_;
v___y_4438_ = v___y_4456_;
v___y_4439_ = v___x_4487_;
goto v___jp_4435_;
}
else
{
v___y_4436_ = v___x_4465_;
v___y_4437_ = v___y_4455_;
v___y_4438_ = v___y_4456_;
v___y_4439_ = v_quotient_4476_;
goto v___jp_4435_;
}
}
else
{
uint64_t v___x_4488_; 
v___x_4488_ = lean_uint64_add(v_quotient_4476_, v___x_4477_);
v___y_4436_ = v___x_4465_;
v___y_4437_ = v___y_4455_;
v___y_4438_ = v___y_4456_;
v___y_4439_ = v___x_4488_;
goto v___jp_4435_;
}
}
else
{
v___y_4436_ = v___x_4465_;
v___y_4437_ = v___y_4455_;
v___y_4438_ = v___y_4456_;
v___y_4439_ = v_quotient_4476_;
goto v___jp_4435_;
}
}
}
else
{
v___y_4436_ = v___x_4465_;
v___y_4437_ = v___y_4455_;
v___y_4438_ = v___y_4456_;
v___y_4439_ = v___x_4459_;
goto v___jp_4435_;
}
}
else
{
if (v___y_4456_ == 0)
{
uint32_t v___x_4489_; 
v___x_4489_ = 0;
return v___x_4489_;
}
else
{
uint32_t v___x_4490_; 
v___x_4490_ = 2147483648;
return v___x_4490_;
}
}
}
}
}
v___jp_4491_:
{
uint64_t v___x_4500_; uint64_t v___x_4501_; uint8_t v___x_4502_; 
v___x_4500_ = lean_uint32_to_uint64(v___y_4494_);
v___x_4501_ = 0ULL;
v___x_4502_ = lean_uint64_dec_eq(v___x_4500_, v___x_4501_);
if (v___x_4502_ == 0)
{
uint64_t v___x_4503_; uint64_t v___x_4504_; 
v___x_4503_ = 1ULL;
v___x_4504_ = lean_uint64_sub(v___x_4500_, v___x_4503_);
v___y_4451_ = v___y_4499_;
v___y_4452_ = v___y_4492_;
v___y_4453_ = v___y_4493_;
v___y_4454_ = v___y_4495_;
v___y_4455_ = v___y_4496_;
v___y_4456_ = v___y_4498_;
v___y_4457_ = v___y_4497_;
v___y_4458_ = v___x_4504_;
goto v___jp_4450_;
}
else
{
v___y_4451_ = v___y_4499_;
v___y_4452_ = v___y_4492_;
v___y_4453_ = v___y_4493_;
v___y_4454_ = v___y_4495_;
v___y_4455_ = v___y_4496_;
v___y_4456_ = v___y_4498_;
v___y_4457_ = v___y_4497_;
v___y_4458_ = v___x_4501_;
goto v___jp_4450_;
}
}
v___jp_4505_:
{
uint64_t v___x_4514_; uint64_t v___x_4515_; uint8_t v___x_4516_; 
v___x_4514_ = lean_uint32_to_uint64(v___y_4506_);
v___x_4515_ = 0ULL;
v___x_4516_ = lean_uint64_dec_eq(v___x_4514_, v___x_4515_);
if (v___x_4516_ == 0)
{
uint64_t v___x_4517_; uint64_t v___x_4518_; 
v___x_4517_ = 1ULL;
v___x_4518_ = lean_uint64_sub(v___x_4514_, v___x_4517_);
v___y_4492_ = v___y_4513_;
v___y_4493_ = v___y_4507_;
v___y_4494_ = v___y_4508_;
v___y_4495_ = v___y_4509_;
v___y_4496_ = v___y_4510_;
v___y_4497_ = v___y_4512_;
v___y_4498_ = v___y_4511_;
v___y_4499_ = v___x_4518_;
goto v___jp_4491_;
}
else
{
v___y_4492_ = v___y_4513_;
v___y_4493_ = v___y_4507_;
v___y_4494_ = v___y_4508_;
v___y_4495_ = v___y_4509_;
v___y_4496_ = v___y_4510_;
v___y_4497_ = v___y_4512_;
v___y_4498_ = v___y_4511_;
v___y_4499_ = v___x_4515_;
goto v___jp_4491_;
}
}
v___jp_4519_:
{
uint32_t v___x_4528_; uint8_t v___x_4529_; 
v___x_4528_ = 0;
v___x_4529_ = lean_uint32_dec_eq(v___y_4522_, v___x_4528_);
if (v___x_4529_ == 0)
{
uint64_t v___x_4530_; uint64_t v___x_4531_; uint64_t v___x_4532_; 
v___x_4530_ = lean_uint32_to_uint64(v___y_4526_);
v___x_4531_ = 8388608ULL;
v___x_4532_ = lean_uint64_lor(v___x_4530_, v___x_4531_);
v___y_4506_ = v___y_4520_;
v___y_4507_ = v___y_4521_;
v___y_4508_ = v___y_4522_;
v___y_4509_ = v___y_4523_;
v___y_4510_ = v___y_4524_;
v___y_4511_ = v___y_4525_;
v___y_4512_ = v___y_4527_;
v___y_4513_ = v___x_4532_;
goto v___jp_4505_;
}
else
{
uint64_t v___x_4533_; 
v___x_4533_ = lean_uint32_to_uint64(v___y_4526_);
v___y_4506_ = v___y_4520_;
v___y_4507_ = v___y_4521_;
v___y_4508_ = v___y_4522_;
v___y_4509_ = v___y_4523_;
v___y_4510_ = v___y_4524_;
v___y_4511_ = v___y_4525_;
v___y_4512_ = v___y_4527_;
v___y_4513_ = v___x_4533_;
goto v___jp_4505_;
}
}
v___jp_4534_:
{
uint32_t v___x_4540_; uint32_t v_xFraction_4541_; uint32_t v_yFraction_4542_; uint32_t v___x_4543_; uint8_t v___x_4544_; 
v___x_4540_ = 8388607;
v_xFraction_4541_ = lean_uint32_land(v_x_4121_, v___x_4540_);
v_yFraction_4542_ = lean_uint32_land(v_y_4122_, v___x_4540_);
v___x_4543_ = 0;
v___x_4544_ = lean_uint32_dec_eq(v___y_4535_, v___x_4543_);
if (v___x_4544_ == 0)
{
uint64_t v___x_4545_; uint64_t v___x_4546_; uint64_t v___x_4547_; 
v___x_4545_ = lean_uint32_to_uint64(v_xFraction_4541_);
v___x_4546_ = 8388608ULL;
v___x_4547_ = lean_uint64_lor(v___x_4545_, v___x_4546_);
v___y_4520_ = v___y_4535_;
v___y_4521_ = v___y_4536_;
v___y_4522_ = v___y_4537_;
v___y_4523_ = v___y_4538_;
v___y_4524_ = v___x_4540_;
v___y_4525_ = v___y_4539_;
v___y_4526_ = v_yFraction_4542_;
v___y_4527_ = v___x_4547_;
goto v___jp_4519_;
}
else
{
uint64_t v___x_4548_; 
v___x_4548_ = lean_uint32_to_uint64(v_xFraction_4541_);
v___y_4520_ = v___y_4535_;
v___y_4521_ = v___y_4536_;
v___y_4522_ = v___y_4537_;
v___y_4523_ = v___y_4538_;
v___y_4524_ = v___x_4540_;
v___y_4525_ = v___y_4539_;
v___y_4526_ = v_yFraction_4542_;
v___y_4527_ = v___x_4548_;
goto v___jp_4519_;
}
}
v___jp_4549_:
{
uint8_t v___x_4554_; 
v___x_4554_ = 1;
v___y_4535_ = v___y_4550_;
v___y_4536_ = v___y_4551_;
v___y_4537_ = v___y_4552_;
v___y_4538_ = v___y_4553_;
v___y_4539_ = v___x_4554_;
goto v___jp_4534_;
}
v___jp_4555_:
{
if (v___y_4556_ == 0)
{
if (v___y_4562_ == 0)
{
v___y_4535_ = v___y_4557_;
v___y_4536_ = v___y_4558_;
v___y_4537_ = v___y_4559_;
v___y_4538_ = v___y_4560_;
v___y_4539_ = v___y_4561_;
goto v___jp_4534_;
}
else
{
v___y_4550_ = v___y_4557_;
v___y_4551_ = v___y_4558_;
v___y_4552_ = v___y_4559_;
v___y_4553_ = v___y_4560_;
goto v___jp_4549_;
}
}
else
{
if (v___y_4562_ == 0)
{
v___y_4550_ = v___y_4557_;
v___y_4551_ = v___y_4558_;
v___y_4552_ = v___y_4559_;
v___y_4553_ = v___y_4560_;
goto v___jp_4549_;
}
else
{
v___y_4535_ = v___y_4557_;
v___y_4536_ = v___y_4558_;
v___y_4537_ = v___y_4559_;
v___y_4538_ = v___y_4560_;
v___y_4539_ = v___y_4561_;
goto v___jp_4534_;
}
}
}
v___jp_4563_:
{
uint32_t v___x_4570_; uint32_t v___x_4571_; uint32_t v___x_4572_; uint8_t v___x_4573_; 
v___x_4570_ = 2147483648;
v___x_4571_ = lean_uint32_land(v_y_4122_, v___x_4570_);
v___x_4572_ = 0;
v___x_4573_ = lean_uint32_dec_eq(v___x_4571_, v___x_4572_);
if (v___x_4573_ == 0)
{
uint8_t v___x_4574_; 
v___x_4574_ = 1;
v___y_4556_ = v___y_4569_;
v___y_4557_ = v___y_4564_;
v___y_4558_ = v___y_4565_;
v___y_4559_ = v___y_4566_;
v___y_4560_ = v___y_4567_;
v___y_4561_ = v___y_4568_;
v___y_4562_ = v___x_4574_;
goto v___jp_4555_;
}
else
{
v___y_4556_ = v___y_4569_;
v___y_4557_ = v___y_4564_;
v___y_4558_ = v___y_4565_;
v___y_4559_ = v___y_4566_;
v___y_4560_ = v___y_4567_;
v___y_4561_ = v___y_4568_;
v___y_4562_ = v___y_4568_;
goto v___jp_4555_;
}
}
v___jp_4575_:
{
if (v___y_4576_ == 0)
{
uint32_t v___x_4577_; uint32_t v___x_4578_; uint32_t v___x_4579_; uint32_t v_xExponent_4580_; uint32_t v___x_4581_; uint32_t v_yExponent_4582_; uint32_t v___x_4583_; uint32_t v___x_4584_; uint32_t v___x_4585_; uint8_t v___x_4586_; 
v___x_4577_ = 23;
v___x_4578_ = lean_uint32_shift_right(v_x_4121_, v___x_4577_);
v___x_4579_ = 255;
v_xExponent_4580_ = lean_uint32_land(v___x_4578_, v___x_4579_);
v___x_4581_ = lean_uint32_shift_right(v_y_4122_, v___x_4577_);
v_yExponent_4582_ = lean_uint32_land(v___x_4581_, v___x_4579_);
v___x_4583_ = 2147483648;
v___x_4584_ = lean_uint32_land(v_x_4121_, v___x_4583_);
v___x_4585_ = 0;
v___x_4586_ = lean_uint32_dec_eq(v___x_4584_, v___x_4585_);
if (v___x_4586_ == 0)
{
uint8_t v___x_4587_; 
v___x_4587_ = 1;
v___y_4564_ = v_xExponent_4580_;
v___y_4565_ = v___x_4579_;
v___y_4566_ = v_yExponent_4582_;
v___y_4567_ = v___x_4577_;
v___y_4568_ = v___y_4576_;
v___y_4569_ = v___x_4587_;
goto v___jp_4563_;
}
else
{
v___y_4564_ = v_xExponent_4580_;
v___y_4565_ = v___x_4579_;
v___y_4566_ = v_yExponent_4582_;
v___y_4567_ = v___x_4577_;
v___y_4568_ = v___y_4576_;
v___y_4569_ = v___y_4576_;
goto v___jp_4563_;
}
}
else
{
lean_object* v___x_4588_; lean_object* v___x_4589_; lean_object* v___x_4590_; lean_object* v___x_4591_; uint32_t v___x_4592_; 
v___x_4588_ = ((lean_object*)(lp_competition_Submission_TunedAdd_Fmt___closed__0));
v___x_4589_ = lean_uint32_to_nat(v_x_4121_);
v___x_4590_ = lean_uint32_to_nat(v_y_4122_);
v___x_4591_ = lp_floatlib_FloatLib_Floats_Formats_BinaryInterchange_Model_MulBackend_word(v___x_4588_, v___x_4589_, v___x_4590_);
v___x_4592_ = lean_uint32_of_nat(v___x_4591_);
lean_dec(v___x_4591_);
return v___x_4592_;
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_LowScale_mul___boxed(lean_object* v_x_4599_, lean_object* v_y_4600_){
_start:
{
uint32_t v_x_boxed_4601_; uint32_t v_y_boxed_4602_; uint32_t v_res_4603_; lean_object* v_r_4604_; 
v_x_boxed_4601_ = lean_unbox_uint32(v_x_4599_);
lean_dec(v_x_4599_);
v_y_boxed_4602_ = lean_unbox_uint32(v_y_4600_);
lean_dec(v_y_4600_);
v_res_4603_ = lp_competition_Submission_LowScale_mul(v_x_boxed_4601_, v_y_boxed_4602_);
v_r_4604_ = lean_box_uint32(v_res_4603_);
return v_r_4604_;
}
}
LEAN_EXPORT uint32_t lp_competition_Submission_add(uint32_t v_x_4605_, uint32_t v_y_4606_){
_start:
{
float v___y_4608_; float v___y_4609_; float v___y_4613_; uint8_t v___y_4614_; float v___y_4629_; uint8_t v___y_4639_; uint32_t v___x_4653_; uint32_t v___x_4654_; uint32_t v___x_4655_; uint32_t v___x_4656_; uint8_t v___x_4657_; 
v___x_4653_ = 23;
v___x_4654_ = lean_uint32_shift_right(v_x_4605_, v___x_4653_);
v___x_4655_ = 255;
v___x_4656_ = lean_uint32_land(v___x_4654_, v___x_4655_);
v___x_4657_ = lean_uint32_dec_eq(v___x_4656_, v___x_4655_);
if (v___x_4657_ == 0)
{
uint32_t v___x_4658_; uint32_t v___x_4659_; uint8_t v___x_4660_; 
v___x_4658_ = lean_uint32_shift_right(v_y_4606_, v___x_4653_);
v___x_4659_ = lean_uint32_land(v___x_4658_, v___x_4655_);
v___x_4660_ = lean_uint32_dec_eq(v___x_4659_, v___x_4655_);
if (v___x_4660_ == 0)
{
uint32_t v___x_4661_; uint32_t v_a_4662_; uint32_t v___x_4663_; uint32_t v___x_4664_; uint32_t v___x_4665_; uint8_t v___x_4666_; 
v___x_4661_ = 2147483647;
v_a_4662_ = lean_uint32_land(v_x_4605_, v___x_4661_);
v___x_4663_ = 201326591;
v___x_4664_ = 1;
v___x_4665_ = lean_uint32_sub(v_a_4662_, v___x_4664_);
v___x_4666_ = lean_uint32_dec_le(v___x_4663_, v___x_4665_);
if (v___x_4666_ == 0)
{
v___y_4639_ = v___x_4666_;
goto v___jp_4638_;
}
else
{
uint32_t v___x_4667_; uint8_t v___x_4668_; 
v___x_4667_ = 2139095040;
v___x_4668_ = lean_uint32_dec_lt(v_a_4662_, v___x_4667_);
v___y_4639_ = v___x_4668_;
goto v___jp_4638_;
}
}
else
{
uint32_t v___x_4669_; 
v___x_4669_ = lp_competition_Submission_TunedAdd_add(v_x_4605_, v_y_4606_);
return v___x_4669_;
}
}
else
{
uint32_t v___x_4670_; 
v___x_4670_ = lp_competition_Submission_TunedAdd_add(v_x_4605_, v_y_4606_);
return v___x_4670_;
}
v___jp_4607_:
{
float v___x_4610_; uint32_t v___x_4611_; 
v___x_4610_ = lean_float32_add(v___y_4608_, v___y_4609_);
v___x_4611_ = lean_float32_to_bits(v___x_4610_);
return v___x_4611_;
}
v___jp_4612_:
{
if (v___y_4614_ == 0)
{
float v___x_4615_; 
v___x_4615_ = lean_float32_of_bits(v_y_4606_);
v___y_4608_ = v___y_4613_;
v___y_4609_ = v___x_4615_;
goto v___jp_4607_;
}
else
{
uint32_t v___x_4616_; uint32_t v___x_4617_; uint32_t v___x_4618_; uint32_t v___x_4619_; float v___x_4620_; lean_object* v___x_4621_; uint32_t v___x_4622_; uint32_t v___x_4623_; lean_object* v___x_4624_; lean_object* v___x_4625_; float v___x_4626_; float v___x_4627_; 
v___x_4616_ = 8388607;
v___x_4617_ = lean_uint32_land(v_y_4606_, v___x_4616_);
v___x_4618_ = 8388608;
v___x_4619_ = lean_uint32_lor(v___x_4617_, v___x_4618_);
v___x_4620_ = lean_uint32_to_float32(v___x_4619_);
v___x_4621_ = lp_competition_R2W01b_scaleTable;
v___x_4622_ = 23;
v___x_4623_ = lean_uint32_shift_right(v_y_4606_, v___x_4622_);
v___x_4624_ = lean_uint32_to_nat(v___x_4623_);
v___x_4625_ = lean_array_fget_borrowed(v___x_4621_, v___x_4624_);
lean_dec(v___x_4624_);
v___x_4626_ = lean_unbox_float32(v___x_4625_);
v___x_4627_ = lean_float32_mul(v___x_4620_, v___x_4626_);
v___y_4608_ = v___y_4613_;
v___y_4609_ = v___x_4627_;
goto v___jp_4607_;
}
}
v___jp_4628_:
{
uint32_t v___x_4630_; uint32_t v_a_4631_; uint32_t v___x_4632_; uint32_t v___x_4633_; uint32_t v___x_4634_; uint8_t v___x_4635_; 
v___x_4630_ = 2147483647;
v_a_4631_ = lean_uint32_land(v_y_4606_, v___x_4630_);
v___x_4632_ = 201326591;
v___x_4633_ = 1;
v___x_4634_ = lean_uint32_sub(v_a_4631_, v___x_4633_);
v___x_4635_ = lean_uint32_dec_le(v___x_4632_, v___x_4634_);
if (v___x_4635_ == 0)
{
v___y_4613_ = v___y_4629_;
v___y_4614_ = v___x_4635_;
goto v___jp_4612_;
}
else
{
uint32_t v___x_4636_; uint8_t v___x_4637_; 
v___x_4636_ = 2139095040;
v___x_4637_ = lean_uint32_dec_lt(v_a_4631_, v___x_4636_);
v___y_4613_ = v___y_4629_;
v___y_4614_ = v___x_4637_;
goto v___jp_4612_;
}
}
v___jp_4638_:
{
if (v___y_4639_ == 0)
{
float v___x_4640_; 
v___x_4640_ = lean_float32_of_bits(v_x_4605_);
v___y_4629_ = v___x_4640_;
goto v___jp_4628_;
}
else
{
uint32_t v___x_4641_; uint32_t v___x_4642_; uint32_t v___x_4643_; uint32_t v___x_4644_; float v___x_4645_; lean_object* v___x_4646_; uint32_t v___x_4647_; uint32_t v___x_4648_; lean_object* v___x_4649_; lean_object* v___x_4650_; float v___x_4651_; float v___x_4652_; 
v___x_4641_ = 8388607;
v___x_4642_ = lean_uint32_land(v_x_4605_, v___x_4641_);
v___x_4643_ = 8388608;
v___x_4644_ = lean_uint32_lor(v___x_4642_, v___x_4643_);
v___x_4645_ = lean_uint32_to_float32(v___x_4644_);
v___x_4646_ = lp_competition_R2W01b_scaleTable;
v___x_4647_ = 23;
v___x_4648_ = lean_uint32_shift_right(v_x_4605_, v___x_4647_);
v___x_4649_ = lean_uint32_to_nat(v___x_4648_);
v___x_4650_ = lean_array_fget_borrowed(v___x_4646_, v___x_4649_);
lean_dec(v___x_4649_);
v___x_4651_ = lean_unbox_float32(v___x_4650_);
v___x_4652_ = lean_float32_mul(v___x_4645_, v___x_4651_);
v___y_4629_ = v___x_4652_;
goto v___jp_4628_;
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_add___boxed(lean_object* v_x_4671_, lean_object* v_y_4672_){
_start:
{
uint32_t v_x_boxed_4673_; uint32_t v_y_boxed_4674_; uint32_t v_res_4675_; lean_object* v_r_4676_; 
v_x_boxed_4673_ = lean_unbox_uint32(v_x_4671_);
lean_dec(v_x_4671_);
v_y_boxed_4674_ = lean_unbox_uint32(v_y_4672_);
lean_dec(v_y_4672_);
v_res_4675_ = lp_competition_Submission_add(v_x_boxed_4673_, v_y_boxed_4674_);
v_r_4676_ = lean_box_uint32(v_res_4675_);
return v_r_4676_;
}
}
LEAN_EXPORT uint32_t lp_competition_Submission_nativeMul(uint32_t v_x_4677_, uint32_t v_y_4678_){
_start:
{
uint32_t v___x_4679_; uint32_t v___x_4680_; uint32_t v___x_4681_; uint32_t v___x_4682_; uint8_t v___x_4683_; 
v___x_4679_ = 23;
v___x_4680_ = lean_uint32_shift_right(v_x_4677_, v___x_4679_);
v___x_4681_ = 255;
v___x_4682_ = lean_uint32_land(v___x_4680_, v___x_4681_);
v___x_4683_ = lean_uint32_dec_eq(v___x_4682_, v___x_4681_);
if (v___x_4683_ == 0)
{
uint32_t v___x_4684_; uint32_t v___x_4685_; uint8_t v___x_4686_; 
v___x_4684_ = lean_uint32_shift_right(v_y_4678_, v___x_4679_);
v___x_4685_ = lean_uint32_land(v___x_4684_, v___x_4681_);
v___x_4686_ = lean_uint32_dec_eq(v___x_4685_, v___x_4681_);
if (v___x_4686_ == 0)
{
float v___x_4687_; float v___x_4688_; float v___x_4689_; uint32_t v___x_4690_; 
v___x_4687_ = lean_float32_of_bits(v_x_4677_);
v___x_4688_ = lean_float32_of_bits(v_y_4678_);
v___x_4689_ = lean_float32_mul(v___x_4687_, v___x_4688_);
v___x_4690_ = lean_float32_to_bits(v___x_4689_);
return v___x_4690_;
}
else
{
uint32_t v___x_4691_; 
v___x_4691_ = lp_competition_Submission_FastMul_mul(v_x_4677_, v_y_4678_);
return v___x_4691_;
}
}
else
{
uint32_t v___x_4692_; 
v___x_4692_ = lp_competition_Submission_FastMul_mul(v_x_4677_, v_y_4678_);
return v___x_4692_;
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_nativeMul___boxed(lean_object* v_x_4693_, lean_object* v_y_4694_){
_start:
{
uint32_t v_x_boxed_4695_; uint32_t v_y_boxed_4696_; uint32_t v_res_4697_; lean_object* v_r_4698_; 
v_x_boxed_4695_ = lean_unbox_uint32(v_x_4693_);
lean_dec(v_x_4693_);
v_y_boxed_4696_ = lean_unbox_uint32(v_y_4694_);
lean_dec(v_y_4694_);
v_res_4697_ = lp_competition_Submission_nativeMul(v_x_boxed_4695_, v_y_boxed_4696_);
v_r_4698_ = lean_box_uint32(v_res_4697_);
return v_r_4698_;
}
}
LEAN_EXPORT uint32_t lp_competition_Submission_mul(uint32_t v_x_4699_, uint32_t v_y_4700_){
_start:
{
uint32_t v___y_4707_; uint32_t v___y_4711_; uint32_t v___y_4715_; uint32_t v___y_4716_; uint32_t v___y_4717_; uint64_t v___y_4721_; uint8_t v___y_4722_; uint32_t v___y_4723_; uint64_t v___y_4724_; uint32_t v___y_4736_; uint32_t v___y_4737_; uint32_t v___y_4738_; uint8_t v___y_4742_; uint64_t v___y_4743_; uint32_t v___y_4744_; uint64_t v___y_4745_; uint32_t v___x_4756_; uint32_t v___x_4757_; uint32_t v___x_4758_; uint32_t v___y_4760_; uint32_t v___y_4761_; uint32_t v___y_4762_; uint32_t v___y_4763_; uint32_t v___y_4770_; uint8_t v___y_4771_; uint32_t v___y_4772_; uint32_t v___y_4773_; uint64_t v___y_4777_; uint8_t v___y_4778_; uint64_t v___y_4779_; uint32_t v___y_4780_; uint64_t v___y_4781_; uint8_t v___y_4791_; uint64_t v___y_4792_; uint64_t v___y_4793_; uint8_t v___y_4794_; uint32_t v___y_4795_; uint64_t v___y_4796_; uint64_t v___y_4803_; uint8_t v___y_4804_; uint64_t v___y_4805_; uint32_t v___y_4806_; uint64_t v___y_4807_; uint64_t v___y_4813_; uint64_t v___y_4814_; uint8_t v___y_4815_; uint64_t v___y_4816_; uint32_t v___y_4817_; uint64_t v___y_4818_; uint64_t v___y_4873_; uint64_t v___y_4874_; uint64_t v___y_4875_; uint8_t v___y_4876_; uint64_t v___y_4877_; uint32_t v___y_4878_; uint64_t v___y_4879_; uint64_t v___y_4885_; uint64_t v___y_4886_; uint64_t v___y_4887_; uint8_t v___y_4888_; uint64_t v___y_4889_; uint64_t v___y_4890_; uint64_t v___y_4891_; uint32_t v___y_4892_; uint64_t v___y_4893_; uint64_t v___y_4898_; uint64_t v___y_4899_; uint8_t v___y_4900_; uint64_t v___y_4901_; uint64_t v___y_4902_; uint32_t v___y_4903_; uint64_t v___y_4904_; uint64_t v___y_4909_; uint64_t v___y_4910_; uint64_t v___y_4911_; uint64_t v___y_4912_; uint8_t v___y_4913_; uint64_t v___y_4914_; uint64_t v___y_4915_; uint32_t v___y_4916_; uint64_t v___y_4917_; uint64_t v___y_4922_; uint64_t v___y_4923_; uint8_t v___y_4924_; uint64_t v___y_4925_; uint32_t v___y_4926_; uint64_t v___y_4927_; uint64_t v___y_4928_; uint64_t v___y_4933_; uint64_t v___y_4934_; uint64_t v___y_4935_; uint64_t v___y_4936_; uint64_t v___y_4937_; uint8_t v___y_4938_; uint64_t v___y_4939_; uint32_t v___y_4940_; uint64_t v___y_4941_; uint64_t v___y_4946_; uint64_t v___y_4947_; uint64_t v___y_4948_; uint8_t v___y_4949_; uint64_t v___y_4950_; uint32_t v___y_4951_; uint64_t v___y_4952_; uint64_t v___y_4957_; uint64_t v___y_4958_; uint64_t v___y_4959_; uint64_t v___y_4960_; uint64_t v___y_4961_; uint8_t v___y_4962_; uint64_t v___y_4963_; uint32_t v___y_4964_; uint64_t v___y_4965_; uint64_t v___y_4970_; uint64_t v___y_4971_; uint64_t v___y_4972_; uint8_t v___y_4973_; uint64_t v___y_4974_; uint32_t v___y_4975_; uint64_t v___y_4976_; uint64_t v___y_4981_; uint64_t v___y_4982_; uint64_t v___y_4983_; uint8_t v___y_4984_; uint64_t v___y_4985_; uint32_t v___y_4986_; uint64_t v___y_4987_; uint64_t v___y_4991_; uint8_t v___y_4992_; uint64_t v___y_4993_; uint32_t v___y_4994_; uint64_t v___y_5003_; uint8_t v___y_5004_; uint64_t v___y_5005_; uint32_t v___y_5006_; uint64_t v___y_5007_; uint64_t v___y_5008_; uint32_t v_ex_5041_; uint32_t v___x_5042_; uint32_t v_ey_5043_; uint64_t v___y_5045_; uint8_t v___y_5046_; uint64_t v___y_5047_; uint32_t v___y_5048_; uint64_t v___y_5049_; uint8_t v___y_5056_; uint32_t v___y_5057_; uint64_t v___y_5058_; uint64_t v___y_5059_; uint32_t v___y_5066_; uint8_t v___y_5067_; uint32_t v___y_5068_; uint64_t v___y_5069_; uint8_t v___y_5077_; uint32_t v___x_5087_; uint32_t v___x_5088_; uint8_t v___x_5089_; uint8_t v___y_5091_; uint8_t v___y_5092_; uint8_t v___y_5094_; uint8_t v___y_5095_; uint8_t v___y_5096_; uint8_t v___y_5098_; uint8_t v___y_5099_; uint8_t v___y_5105_; 
v___x_4756_ = 23;
v___x_4757_ = lean_uint32_shift_right(v_x_4699_, v___x_4756_);
v___x_4758_ = 255;
v_ex_5041_ = lean_uint32_land(v___x_4757_, v___x_4758_);
v___x_5042_ = lean_uint32_shift_right(v_y_4700_, v___x_4756_);
v_ey_5043_ = lean_uint32_land(v___x_5042_, v___x_4758_);
v___x_5087_ = lean_uint32_add(v_ex_5041_, v_ey_5043_);
v___x_5088_ = 128;
v___x_5089_ = lean_uint32_dec_lt(v___x_5087_, v___x_5088_);
if (v___x_5089_ == 0)
{
uint8_t v___x_5118_; 
v___x_5118_ = lean_uint32_dec_eq(v_ex_5041_, v___x_4758_);
if (v___x_5118_ == 0)
{
goto v___jp_5115_;
}
else
{
if (v___x_5089_ == 0)
{
uint32_t v___x_5119_; 
v___x_5119_ = lp_competition_Submission_FastMul_mul(v_x_4699_, v_y_4700_);
return v___x_5119_;
}
else
{
goto v___jp_5115_;
}
}
}
else
{
uint32_t v___x_5120_; uint32_t v___x_5121_; uint32_t v___x_5122_; uint8_t v___x_5123_; 
v___x_5120_ = 4278190080;
v___x_5121_ = 1;
v___x_5122_ = lean_uint32_shift_left(v_x_4699_, v___x_5121_);
v___x_5123_ = lean_uint32_dec_le(v___x_5120_, v___x_5122_);
if (v___x_5123_ == 0)
{
uint32_t v___x_5124_; uint8_t v___x_5125_; 
v___x_5124_ = lean_uint32_shift_left(v_y_4700_, v___x_5121_);
v___x_5125_ = lean_uint32_dec_le(v___x_5120_, v___x_5124_);
v___y_5105_ = v___x_5125_;
goto v___jp_5104_;
}
else
{
v___y_5105_ = v___x_5123_;
goto v___jp_5104_;
}
}
v___jp_4701_:
{
float v___x_4702_; float v___x_4703_; float v___x_4704_; uint32_t v___x_4705_; 
v___x_4702_ = lean_float32_of_bits(v_x_4699_);
v___x_4703_ = lean_float32_of_bits(v_y_4700_);
v___x_4704_ = lean_float32_mul(v___x_4702_, v___x_4703_);
v___x_4705_ = lean_float32_to_bits(v___x_4704_);
return v___x_4705_;
}
v___jp_4706_:
{
uint32_t v___x_4708_; uint32_t v___x_4709_; 
v___x_4708_ = 8388608;
v___x_4709_ = lean_uint32_lor(v___y_4707_, v___x_4708_);
return v___x_4709_;
}
v___jp_4710_:
{
uint32_t v___x_4712_; uint32_t v___x_4713_; 
v___x_4712_ = 8388608;
v___x_4713_ = lean_uint32_lor(v___y_4711_, v___x_4712_);
return v___x_4713_;
}
v___jp_4714_:
{
uint32_t v___x_4718_; uint32_t v___x_4719_; 
v___x_4718_ = lean_uint32_land(v___y_4715_, v___y_4716_);
v___x_4719_ = lean_uint32_lor(v___y_4717_, v___x_4718_);
return v___x_4719_;
}
v___jp_4720_:
{
uint8_t v___x_4725_; 
v___x_4725_ = lean_uint64_dec_eq(v___y_4724_, v___y_4721_);
if (v___x_4725_ == 0)
{
uint64_t v___x_4726_; uint8_t v___x_4727_; 
v___x_4726_ = 8388608ULL;
v___x_4727_ = lean_uint64_dec_eq(v___y_4724_, v___x_4726_);
if (v___x_4727_ == 0)
{
uint32_t v___x_4728_; 
v___x_4728_ = lean_uint64_to_uint32(v___y_4724_);
if (v___y_4722_ == 0)
{
uint32_t v___x_4729_; 
v___x_4729_ = 0;
v___y_4715_ = v___x_4728_;
v___y_4716_ = v___y_4723_;
v___y_4717_ = v___x_4729_;
goto v___jp_4714_;
}
else
{
uint32_t v___x_4730_; 
v___x_4730_ = 2147483648;
v___y_4715_ = v___x_4728_;
v___y_4716_ = v___y_4723_;
v___y_4717_ = v___x_4730_;
goto v___jp_4714_;
}
}
else
{
if (v___y_4722_ == 0)
{
uint32_t v___x_4731_; 
v___x_4731_ = 0;
v___y_4711_ = v___x_4731_;
goto v___jp_4710_;
}
else
{
uint32_t v___x_4732_; 
v___x_4732_ = 2147483648;
v___y_4711_ = v___x_4732_;
goto v___jp_4710_;
}
}
}
else
{
if (v___y_4722_ == 0)
{
uint32_t v___x_4733_; 
v___x_4733_ = 0;
return v___x_4733_;
}
else
{
uint32_t v___x_4734_; 
v___x_4734_ = 2147483648;
return v___x_4734_;
}
}
}
v___jp_4735_:
{
uint32_t v___x_4739_; uint32_t v___x_4740_; 
v___x_4739_ = lean_uint32_land(v___y_4736_, v___y_4737_);
v___x_4740_ = lean_uint32_lor(v___y_4738_, v___x_4739_);
return v___x_4740_;
}
v___jp_4741_:
{
uint8_t v___x_4746_; 
v___x_4746_ = lean_uint64_dec_eq(v___y_4745_, v___y_4743_);
if (v___x_4746_ == 0)
{
uint64_t v___x_4747_; uint8_t v___x_4748_; 
v___x_4747_ = 8388608ULL;
v___x_4748_ = lean_uint64_dec_eq(v___y_4745_, v___x_4747_);
if (v___x_4748_ == 0)
{
uint32_t v___x_4749_; 
v___x_4749_ = lean_uint64_to_uint32(v___y_4745_);
if (v___y_4742_ == 0)
{
uint32_t v___x_4750_; 
v___x_4750_ = 0;
v___y_4736_ = v___x_4749_;
v___y_4737_ = v___y_4744_;
v___y_4738_ = v___x_4750_;
goto v___jp_4735_;
}
else
{
uint32_t v___x_4751_; 
v___x_4751_ = 2147483648;
v___y_4736_ = v___x_4749_;
v___y_4737_ = v___y_4744_;
v___y_4738_ = v___x_4751_;
goto v___jp_4735_;
}
}
else
{
if (v___y_4742_ == 0)
{
uint32_t v___x_4752_; 
v___x_4752_ = 0;
v___y_4707_ = v___x_4752_;
goto v___jp_4706_;
}
else
{
uint32_t v___x_4753_; 
v___x_4753_ = 2147483648;
v___y_4707_ = v___x_4753_;
goto v___jp_4706_;
}
}
}
else
{
if (v___y_4742_ == 0)
{
uint32_t v___x_4754_; 
v___x_4754_ = 0;
return v___x_4754_;
}
else
{
uint32_t v___x_4755_; 
v___x_4755_ = 2147483648;
return v___x_4755_;
}
}
}
v___jp_4759_:
{
uint32_t v___x_4764_; uint32_t v___x_4765_; uint32_t v___x_4766_; uint32_t v___x_4767_; uint32_t v___x_4768_; 
v___x_4764_ = lean_uint32_land(v___y_4761_, v___x_4758_);
v___x_4765_ = lean_uint32_shift_left(v___x_4764_, v___x_4756_);
v___x_4766_ = lean_uint32_lor(v___y_4763_, v___x_4765_);
v___x_4767_ = lean_uint32_land(v___y_4760_, v___y_4762_);
v___x_4768_ = lean_uint32_lor(v___x_4766_, v___x_4767_);
return v___x_4768_;
}
v___jp_4769_:
{
if (v___y_4771_ == 0)
{
uint32_t v___x_4774_; 
v___x_4774_ = 0;
v___y_4760_ = v___y_4773_;
v___y_4761_ = v___y_4770_;
v___y_4762_ = v___y_4772_;
v___y_4763_ = v___x_4774_;
goto v___jp_4759_;
}
else
{
uint32_t v___x_4775_; 
v___x_4775_ = 2147483648;
v___y_4760_ = v___y_4773_;
v___y_4761_ = v___y_4770_;
v___y_4762_ = v___y_4772_;
v___y_4763_ = v___x_4775_;
goto v___jp_4759_;
}
}
v___jp_4776_:
{
uint64_t v___x_4782_; uint64_t v_encodedExponent_4783_; uint32_t v___x_4784_; uint64_t v___x_4785_; uint8_t v___x_4786_; 
v___x_4782_ = 171ULL;
v_encodedExponent_4783_ = lean_uint64_sub(v___y_4779_, v___x_4782_);
v___x_4784_ = lean_uint64_to_uint32(v_encodedExponent_4783_);
v___x_4785_ = 8388608ULL;
v___x_4786_ = lean_uint64_dec_lt(v___y_4781_, v___x_4785_);
if (v___x_4786_ == 0)
{
uint64_t v___x_4787_; uint32_t v___x_4788_; 
v___x_4787_ = lean_uint64_sub(v___y_4781_, v___x_4785_);
v___x_4788_ = lean_uint64_to_uint32(v___x_4787_);
v___y_4770_ = v___x_4784_;
v___y_4771_ = v___y_4778_;
v___y_4772_ = v___y_4780_;
v___y_4773_ = v___x_4788_;
goto v___jp_4769_;
}
else
{
uint32_t v___x_4789_; 
v___x_4789_ = lean_uint64_to_uint32(v___y_4777_);
v___y_4770_ = v___x_4784_;
v___y_4771_ = v___y_4778_;
v___y_4772_ = v___y_4780_;
v___y_4773_ = v___x_4789_;
goto v___jp_4769_;
}
}
v___jp_4790_:
{
uint64_t v___x_4797_; uint8_t v___x_4798_; 
v___x_4797_ = 425ULL;
v___x_4798_ = lean_uint64_dec_lt(v___x_4797_, v___y_4796_);
if (v___x_4798_ == 0)
{
if (v___y_4791_ == 0)
{
v___y_4777_ = v___y_4792_;
v___y_4778_ = v___y_4794_;
v___y_4779_ = v___y_4796_;
v___y_4780_ = v___y_4795_;
v___y_4781_ = v___y_4793_;
goto v___jp_4776_;
}
else
{
uint64_t v___x_4799_; 
v___x_4799_ = 8388608ULL;
v___y_4777_ = v___y_4792_;
v___y_4778_ = v___y_4794_;
v___y_4779_ = v___y_4796_;
v___y_4780_ = v___y_4795_;
v___y_4781_ = v___x_4799_;
goto v___jp_4776_;
}
}
else
{
if (v___y_4794_ == 0)
{
uint32_t v___x_4800_; 
v___x_4800_ = 2139095040;
return v___x_4800_;
}
else
{
uint32_t v___x_4801_; 
v___x_4801_ = 4286578688;
return v___x_4801_;
}
}
}
v___jp_4802_:
{
uint64_t v___x_4808_; uint8_t v_carry_4809_; 
v___x_4808_ = 16777216ULL;
v_carry_4809_ = lean_uint64_dec_eq(v___y_4807_, v___x_4808_);
if (v_carry_4809_ == 0)
{
v___y_4791_ = v_carry_4809_;
v___y_4792_ = v___y_4803_;
v___y_4793_ = v___y_4807_;
v___y_4794_ = v___y_4804_;
v___y_4795_ = v___y_4806_;
v___y_4796_ = v___y_4805_;
goto v___jp_4790_;
}
else
{
uint64_t v___x_4810_; uint64_t v___x_4811_; 
v___x_4810_ = 1ULL;
v___x_4811_ = lean_uint64_add(v___y_4805_, v___x_4810_);
v___y_4791_ = v_carry_4809_;
v___y_4792_ = v___y_4803_;
v___y_4793_ = v___y_4807_;
v___y_4794_ = v___y_4804_;
v___y_4795_ = v___y_4806_;
v___y_4796_ = v___x_4811_;
goto v___jp_4790_;
}
}
v___jp_4812_:
{
uint64_t v_position_4819_; uint64_t v___x_4820_; uint8_t v___x_4821_; 
v_position_4819_ = lean_uint64_add(v___y_4818_, v___y_4816_);
v___x_4820_ = 172ULL;
v___x_4821_ = lean_uint64_dec_lt(v_position_4819_, v___x_4820_);
if (v___x_4821_ == 0)
{
uint64_t v___x_4822_; uint8_t v___x_4823_; 
v___x_4822_ = 23ULL;
v___x_4823_ = lean_uint64_dec_lt(v___y_4818_, v___x_4822_);
if (v___x_4823_ == 0)
{
uint64_t v___x_4824_; uint8_t v___x_4825_; 
v___x_4824_ = lean_uint64_sub(v___y_4818_, v___x_4822_);
v___x_4825_ = lean_uint64_dec_eq(v___x_4824_, v___y_4814_);
if (v___x_4825_ == 0)
{
uint64_t v___x_4826_; uint8_t v___x_4827_; 
v___x_4826_ = 64ULL;
v___x_4827_ = lean_uint64_dec_lt(v___x_4824_, v___x_4826_);
if (v___x_4827_ == 0)
{
uint8_t v___x_4828_; 
v___x_4828_ = lean_uint64_dec_eq(v___x_4824_, v___x_4826_);
if (v___x_4828_ == 0)
{
v___y_4803_ = v___y_4814_;
v___y_4804_ = v___y_4815_;
v___y_4805_ = v_position_4819_;
v___y_4806_ = v___y_4817_;
v___y_4807_ = v___y_4814_;
goto v___jp_4802_;
}
else
{
uint64_t v___x_4829_; uint8_t v___x_4830_; 
v___x_4829_ = 9223372036854775808ULL;
v___x_4830_ = lean_uint64_dec_lt(v___x_4829_, v___y_4813_);
if (v___x_4830_ == 0)
{
v___y_4803_ = v___y_4814_;
v___y_4804_ = v___y_4815_;
v___y_4805_ = v_position_4819_;
v___y_4806_ = v___y_4817_;
v___y_4807_ = v___y_4814_;
goto v___jp_4802_;
}
else
{
uint64_t v___x_4831_; 
v___x_4831_ = 1ULL;
v___y_4803_ = v___y_4814_;
v___y_4804_ = v___y_4815_;
v___y_4805_ = v_position_4819_;
v___y_4806_ = v___y_4817_;
v___y_4807_ = v___x_4831_;
goto v___jp_4802_;
}
}
}
else
{
uint64_t v_quotient_4832_; uint64_t v___x_4833_; uint64_t v___x_4834_; uint64_t v___x_4835_; uint64_t v_remainder_4836_; uint64_t v___x_4837_; uint64_t v_half_4838_; uint8_t v___x_4839_; 
v_quotient_4832_ = lean_uint64_shift_right(v___y_4813_, v___x_4824_);
v___x_4833_ = 1ULL;
v___x_4834_ = lean_uint64_shift_left(v___x_4833_, v___x_4824_);
v___x_4835_ = lean_uint64_sub(v___x_4834_, v___x_4833_);
v_remainder_4836_ = lean_uint64_land(v___y_4813_, v___x_4835_);
v___x_4837_ = lean_uint64_sub(v___x_4824_, v___x_4833_);
v_half_4838_ = lean_uint64_shift_left(v___x_4833_, v___x_4837_);
v___x_4839_ = lean_uint64_dec_lt(v_remainder_4836_, v_half_4838_);
if (v___x_4839_ == 0)
{
uint8_t v___x_4840_; 
v___x_4840_ = lean_uint64_dec_lt(v_half_4838_, v_remainder_4836_);
if (v___x_4840_ == 0)
{
uint64_t v___x_4841_; uint8_t v___x_4842_; 
v___x_4841_ = lean_uint64_land(v_quotient_4832_, v___x_4833_);
v___x_4842_ = lean_uint64_dec_eq(v___x_4841_, v___y_4814_);
if (v___x_4842_ == 0)
{
uint64_t v___x_4843_; 
v___x_4843_ = lean_uint64_add(v_quotient_4832_, v___x_4833_);
v___y_4803_ = v___y_4814_;
v___y_4804_ = v___y_4815_;
v___y_4805_ = v_position_4819_;
v___y_4806_ = v___y_4817_;
v___y_4807_ = v___x_4843_;
goto v___jp_4802_;
}
else
{
v___y_4803_ = v___y_4814_;
v___y_4804_ = v___y_4815_;
v___y_4805_ = v_position_4819_;
v___y_4806_ = v___y_4817_;
v___y_4807_ = v_quotient_4832_;
goto v___jp_4802_;
}
}
else
{
uint64_t v___x_4844_; 
v___x_4844_ = lean_uint64_add(v_quotient_4832_, v___x_4833_);
v___y_4803_ = v___y_4814_;
v___y_4804_ = v___y_4815_;
v___y_4805_ = v_position_4819_;
v___y_4806_ = v___y_4817_;
v___y_4807_ = v___x_4844_;
goto v___jp_4802_;
}
}
else
{
v___y_4803_ = v___y_4814_;
v___y_4804_ = v___y_4815_;
v___y_4805_ = v_position_4819_;
v___y_4806_ = v___y_4817_;
v___y_4807_ = v_quotient_4832_;
goto v___jp_4802_;
}
}
}
else
{
v___y_4803_ = v___y_4814_;
v___y_4804_ = v___y_4815_;
v___y_4805_ = v_position_4819_;
v___y_4806_ = v___y_4817_;
v___y_4807_ = v___y_4813_;
goto v___jp_4802_;
}
}
else
{
uint64_t v___x_4845_; uint64_t v___x_4846_; 
v___x_4845_ = lean_uint64_sub(v___x_4822_, v___y_4818_);
v___x_4846_ = lean_uint64_shift_left(v___y_4813_, v___x_4845_);
v___y_4803_ = v___y_4814_;
v___y_4804_ = v___y_4815_;
v___y_4805_ = v_position_4819_;
v___y_4806_ = v___y_4817_;
v___y_4807_ = v___x_4846_;
goto v___jp_4802_;
}
}
else
{
uint64_t v___x_4847_; uint8_t v___x_4848_; 
v___x_4847_ = 149ULL;
v___x_4848_ = lean_uint64_dec_lt(v___y_4816_, v___x_4847_);
if (v___x_4848_ == 0)
{
uint64_t v___x_4849_; uint64_t v___x_4850_; 
v___x_4849_ = lean_uint64_sub(v___y_4816_, v___x_4847_);
v___x_4850_ = lean_uint64_shift_left(v___y_4813_, v___x_4849_);
v___y_4721_ = v___y_4814_;
v___y_4722_ = v___y_4815_;
v___y_4723_ = v___y_4817_;
v___y_4724_ = v___x_4850_;
goto v___jp_4720_;
}
else
{
uint64_t v___x_4851_; uint8_t v___x_4852_; 
v___x_4851_ = lean_uint64_sub(v___x_4847_, v___y_4816_);
v___x_4852_ = lean_uint64_dec_eq(v___x_4851_, v___y_4814_);
if (v___x_4852_ == 0)
{
uint64_t v___x_4853_; uint8_t v___x_4854_; 
v___x_4853_ = 64ULL;
v___x_4854_ = lean_uint64_dec_lt(v___x_4851_, v___x_4853_);
if (v___x_4854_ == 0)
{
uint8_t v___x_4855_; 
v___x_4855_ = lean_uint64_dec_eq(v___x_4851_, v___x_4853_);
if (v___x_4855_ == 0)
{
v___y_4721_ = v___y_4814_;
v___y_4722_ = v___y_4815_;
v___y_4723_ = v___y_4817_;
v___y_4724_ = v___y_4814_;
goto v___jp_4720_;
}
else
{
uint64_t v___x_4856_; uint8_t v___x_4857_; 
v___x_4856_ = 9223372036854775808ULL;
v___x_4857_ = lean_uint64_dec_lt(v___x_4856_, v___y_4813_);
if (v___x_4857_ == 0)
{
v___y_4721_ = v___y_4814_;
v___y_4722_ = v___y_4815_;
v___y_4723_ = v___y_4817_;
v___y_4724_ = v___y_4814_;
goto v___jp_4720_;
}
else
{
uint64_t v___x_4858_; 
v___x_4858_ = 1ULL;
v___y_4721_ = v___y_4814_;
v___y_4722_ = v___y_4815_;
v___y_4723_ = v___y_4817_;
v___y_4724_ = v___x_4858_;
goto v___jp_4720_;
}
}
}
else
{
uint64_t v_quotient_4859_; uint64_t v___x_4860_; uint64_t v___x_4861_; uint64_t v___x_4862_; uint64_t v_remainder_4863_; uint64_t v___x_4864_; uint64_t v_half_4865_; uint8_t v___x_4866_; 
v_quotient_4859_ = lean_uint64_shift_right(v___y_4813_, v___x_4851_);
v___x_4860_ = 1ULL;
v___x_4861_ = lean_uint64_shift_left(v___x_4860_, v___x_4851_);
v___x_4862_ = lean_uint64_sub(v___x_4861_, v___x_4860_);
v_remainder_4863_ = lean_uint64_land(v___y_4813_, v___x_4862_);
v___x_4864_ = lean_uint64_sub(v___x_4851_, v___x_4860_);
v_half_4865_ = lean_uint64_shift_left(v___x_4860_, v___x_4864_);
v___x_4866_ = lean_uint64_dec_lt(v_remainder_4863_, v_half_4865_);
if (v___x_4866_ == 0)
{
uint8_t v___x_4867_; 
v___x_4867_ = lean_uint64_dec_lt(v_half_4865_, v_remainder_4863_);
if (v___x_4867_ == 0)
{
uint64_t v___x_4868_; uint8_t v___x_4869_; 
v___x_4868_ = lean_uint64_land(v_quotient_4859_, v___x_4860_);
v___x_4869_ = lean_uint64_dec_eq(v___x_4868_, v___y_4814_);
if (v___x_4869_ == 0)
{
uint64_t v___x_4870_; 
v___x_4870_ = lean_uint64_add(v_quotient_4859_, v___x_4860_);
v___y_4721_ = v___y_4814_;
v___y_4722_ = v___y_4815_;
v___y_4723_ = v___y_4817_;
v___y_4724_ = v___x_4870_;
goto v___jp_4720_;
}
else
{
v___y_4721_ = v___y_4814_;
v___y_4722_ = v___y_4815_;
v___y_4723_ = v___y_4817_;
v___y_4724_ = v_quotient_4859_;
goto v___jp_4720_;
}
}
else
{
uint64_t v___x_4871_; 
v___x_4871_ = lean_uint64_add(v_quotient_4859_, v___x_4860_);
v___y_4721_ = v___y_4814_;
v___y_4722_ = v___y_4815_;
v___y_4723_ = v___y_4817_;
v___y_4724_ = v___x_4871_;
goto v___jp_4720_;
}
}
else
{
v___y_4721_ = v___y_4814_;
v___y_4722_ = v___y_4815_;
v___y_4723_ = v___y_4817_;
v___y_4724_ = v_quotient_4859_;
goto v___jp_4720_;
}
}
}
else
{
v___y_4721_ = v___y_4814_;
v___y_4722_ = v___y_4815_;
v___y_4723_ = v___y_4817_;
v___y_4724_ = v___y_4813_;
goto v___jp_4720_;
}
}
}
}
v___jp_4872_:
{
uint64_t v___x_4880_; uint64_t v___x_4881_; uint8_t v___x_4882_; 
v___x_4880_ = 1ULL;
v___x_4881_ = lean_uint64_shift_right(v___y_4875_, v___x_4880_);
v___x_4882_ = lean_uint64_dec_eq(v___x_4881_, v___y_4874_);
if (v___x_4882_ == 0)
{
uint64_t v___x_4883_; 
v___x_4883_ = lean_uint64_add(v___y_4879_, v___x_4880_);
v___y_4813_ = v___y_4873_;
v___y_4814_ = v___y_4874_;
v___y_4815_ = v___y_4876_;
v___y_4816_ = v___y_4877_;
v___y_4817_ = v___y_4878_;
v___y_4818_ = v___x_4883_;
goto v___jp_4812_;
}
else
{
v___y_4813_ = v___y_4873_;
v___y_4814_ = v___y_4874_;
v___y_4815_ = v___y_4876_;
v___y_4816_ = v___y_4877_;
v___y_4817_ = v___y_4878_;
v___y_4818_ = v___y_4879_;
goto v___jp_4812_;
}
}
v___jp_4884_:
{
uint64_t v___x_4894_; uint8_t v___x_4895_; 
v___x_4894_ = lean_uint64_shift_right(v___y_4891_, v___y_4889_);
v___x_4895_ = lean_uint64_dec_eq(v___x_4894_, v___y_4886_);
if (v___x_4895_ == 0)
{
uint64_t v___x_4896_; 
v___x_4896_ = lean_uint64_add(v___y_4885_, v___y_4889_);
v___y_4873_ = v___y_4887_;
v___y_4874_ = v___y_4886_;
v___y_4875_ = v___y_4893_;
v___y_4876_ = v___y_4888_;
v___y_4877_ = v___y_4890_;
v___y_4878_ = v___y_4892_;
v___y_4879_ = v___x_4896_;
goto v___jp_4872_;
}
else
{
v___y_4873_ = v___y_4887_;
v___y_4874_ = v___y_4886_;
v___y_4875_ = v___y_4893_;
v___y_4876_ = v___y_4888_;
v___y_4877_ = v___y_4890_;
v___y_4878_ = v___y_4892_;
v___y_4879_ = v___y_4885_;
goto v___jp_4872_;
}
}
v___jp_4897_:
{
uint64_t v___x_4905_; uint64_t v___x_4906_; uint8_t v___x_4907_; 
v___x_4905_ = 2ULL;
v___x_4906_ = lean_uint64_shift_right(v___y_4902_, v___x_4905_);
v___x_4907_ = lean_uint64_dec_eq(v___x_4906_, v___y_4899_);
if (v___x_4907_ == 0)
{
v___y_4885_ = v___y_4904_;
v___y_4886_ = v___y_4899_;
v___y_4887_ = v___y_4898_;
v___y_4888_ = v___y_4900_;
v___y_4889_ = v___x_4905_;
v___y_4890_ = v___y_4901_;
v___y_4891_ = v___y_4902_;
v___y_4892_ = v___y_4903_;
v___y_4893_ = v___x_4906_;
goto v___jp_4884_;
}
else
{
v___y_4885_ = v___y_4904_;
v___y_4886_ = v___y_4899_;
v___y_4887_ = v___y_4898_;
v___y_4888_ = v___y_4900_;
v___y_4889_ = v___x_4905_;
v___y_4890_ = v___y_4901_;
v___y_4891_ = v___y_4902_;
v___y_4892_ = v___y_4903_;
v___y_4893_ = v___y_4902_;
goto v___jp_4884_;
}
}
v___jp_4908_:
{
uint64_t v___x_4918_; uint8_t v___x_4919_; 
v___x_4918_ = lean_uint64_shift_right(v___y_4915_, v___y_4911_);
v___x_4919_ = lean_uint64_dec_eq(v___x_4918_, v___y_4909_);
if (v___x_4919_ == 0)
{
uint64_t v___x_4920_; 
v___x_4920_ = lean_uint64_add(v___y_4912_, v___y_4911_);
v___y_4898_ = v___y_4910_;
v___y_4899_ = v___y_4909_;
v___y_4900_ = v___y_4913_;
v___y_4901_ = v___y_4914_;
v___y_4902_ = v___y_4917_;
v___y_4903_ = v___y_4916_;
v___y_4904_ = v___x_4920_;
goto v___jp_4897_;
}
else
{
v___y_4898_ = v___y_4910_;
v___y_4899_ = v___y_4909_;
v___y_4900_ = v___y_4913_;
v___y_4901_ = v___y_4914_;
v___y_4902_ = v___y_4917_;
v___y_4903_ = v___y_4916_;
v___y_4904_ = v___y_4912_;
goto v___jp_4897_;
}
}
v___jp_4921_:
{
uint64_t v___x_4929_; uint64_t v___x_4930_; uint8_t v___x_4931_; 
v___x_4929_ = 4ULL;
v___x_4930_ = lean_uint64_shift_right(v___y_4927_, v___x_4929_);
v___x_4931_ = lean_uint64_dec_eq(v___x_4930_, v___y_4923_);
if (v___x_4931_ == 0)
{
v___y_4909_ = v___y_4923_;
v___y_4910_ = v___y_4922_;
v___y_4911_ = v___x_4929_;
v___y_4912_ = v___y_4928_;
v___y_4913_ = v___y_4924_;
v___y_4914_ = v___y_4925_;
v___y_4915_ = v___y_4927_;
v___y_4916_ = v___y_4926_;
v___y_4917_ = v___x_4930_;
goto v___jp_4908_;
}
else
{
v___y_4909_ = v___y_4923_;
v___y_4910_ = v___y_4922_;
v___y_4911_ = v___x_4929_;
v___y_4912_ = v___y_4928_;
v___y_4913_ = v___y_4924_;
v___y_4914_ = v___y_4925_;
v___y_4915_ = v___y_4927_;
v___y_4916_ = v___y_4926_;
v___y_4917_ = v___y_4927_;
goto v___jp_4908_;
}
}
v___jp_4932_:
{
uint64_t v___x_4942_; uint8_t v___x_4943_; 
v___x_4942_ = lean_uint64_shift_right(v___y_4936_, v___y_4935_);
v___x_4943_ = lean_uint64_dec_eq(v___x_4942_, v___y_4933_);
if (v___x_4943_ == 0)
{
uint64_t v___x_4944_; 
v___x_4944_ = lean_uint64_add(v___y_4937_, v___y_4935_);
v___y_4922_ = v___y_4934_;
v___y_4923_ = v___y_4933_;
v___y_4924_ = v___y_4938_;
v___y_4925_ = v___y_4939_;
v___y_4926_ = v___y_4940_;
v___y_4927_ = v___y_4941_;
v___y_4928_ = v___x_4944_;
goto v___jp_4921_;
}
else
{
v___y_4922_ = v___y_4934_;
v___y_4923_ = v___y_4933_;
v___y_4924_ = v___y_4938_;
v___y_4925_ = v___y_4939_;
v___y_4926_ = v___y_4940_;
v___y_4927_ = v___y_4941_;
v___y_4928_ = v___y_4937_;
goto v___jp_4921_;
}
}
v___jp_4945_:
{
uint64_t v___x_4953_; uint64_t v___x_4954_; uint8_t v___x_4955_; 
v___x_4953_ = 8ULL;
v___x_4954_ = lean_uint64_shift_right(v___y_4948_, v___x_4953_);
v___x_4955_ = lean_uint64_dec_eq(v___x_4954_, v___y_4947_);
if (v___x_4955_ == 0)
{
v___y_4933_ = v___y_4947_;
v___y_4934_ = v___y_4946_;
v___y_4935_ = v___x_4953_;
v___y_4936_ = v___y_4948_;
v___y_4937_ = v___y_4952_;
v___y_4938_ = v___y_4949_;
v___y_4939_ = v___y_4950_;
v___y_4940_ = v___y_4951_;
v___y_4941_ = v___x_4954_;
goto v___jp_4932_;
}
else
{
v___y_4933_ = v___y_4947_;
v___y_4934_ = v___y_4946_;
v___y_4935_ = v___x_4953_;
v___y_4936_ = v___y_4948_;
v___y_4937_ = v___y_4952_;
v___y_4938_ = v___y_4949_;
v___y_4939_ = v___y_4950_;
v___y_4940_ = v___y_4951_;
v___y_4941_ = v___y_4948_;
goto v___jp_4932_;
}
}
v___jp_4956_:
{
uint64_t v___x_4966_; uint8_t v___x_4967_; 
v___x_4966_ = lean_uint64_shift_right(v___y_4959_, v___y_4957_);
v___x_4967_ = lean_uint64_dec_eq(v___x_4966_, v___y_4960_);
if (v___x_4967_ == 0)
{
uint64_t v___x_4968_; 
v___x_4968_ = lean_uint64_add(v___y_4958_, v___y_4957_);
v___y_4946_ = v___y_4961_;
v___y_4947_ = v___y_4960_;
v___y_4948_ = v___y_4965_;
v___y_4949_ = v___y_4962_;
v___y_4950_ = v___y_4963_;
v___y_4951_ = v___y_4964_;
v___y_4952_ = v___x_4968_;
goto v___jp_4945_;
}
else
{
v___y_4946_ = v___y_4961_;
v___y_4947_ = v___y_4960_;
v___y_4948_ = v___y_4965_;
v___y_4949_ = v___y_4962_;
v___y_4950_ = v___y_4963_;
v___y_4951_ = v___y_4964_;
v___y_4952_ = v___y_4958_;
goto v___jp_4945_;
}
}
v___jp_4969_:
{
uint64_t v___x_4977_; uint64_t v___x_4978_; uint8_t v___x_4979_; 
v___x_4977_ = 16ULL;
v___x_4978_ = lean_uint64_shift_right(v___y_4970_, v___x_4977_);
v___x_4979_ = lean_uint64_dec_eq(v___x_4978_, v___y_4972_);
if (v___x_4979_ == 0)
{
v___y_4957_ = v___x_4977_;
v___y_4958_ = v___y_4976_;
v___y_4959_ = v___y_4970_;
v___y_4960_ = v___y_4972_;
v___y_4961_ = v___y_4971_;
v___y_4962_ = v___y_4973_;
v___y_4963_ = v___y_4974_;
v___y_4964_ = v___y_4975_;
v___y_4965_ = v___x_4978_;
goto v___jp_4956_;
}
else
{
v___y_4957_ = v___x_4977_;
v___y_4958_ = v___y_4976_;
v___y_4959_ = v___y_4970_;
v___y_4960_ = v___y_4972_;
v___y_4961_ = v___y_4971_;
v___y_4962_ = v___y_4973_;
v___y_4963_ = v___y_4974_;
v___y_4964_ = v___y_4975_;
v___y_4965_ = v___y_4970_;
goto v___jp_4956_;
}
}
v___jp_4980_:
{
uint64_t v___x_4988_; uint8_t v___x_4989_; 
v___x_4988_ = lean_uint64_shift_right(v___y_4983_, v___y_4981_);
v___x_4989_ = lean_uint64_dec_eq(v___x_4988_, v___y_4982_);
if (v___x_4989_ == 0)
{
v___y_4970_ = v___y_4987_;
v___y_4971_ = v___y_4983_;
v___y_4972_ = v___y_4982_;
v___y_4973_ = v___y_4984_;
v___y_4974_ = v___y_4985_;
v___y_4975_ = v___y_4986_;
v___y_4976_ = v___y_4981_;
goto v___jp_4969_;
}
else
{
v___y_4970_ = v___y_4987_;
v___y_4971_ = v___y_4983_;
v___y_4972_ = v___y_4982_;
v___y_4973_ = v___y_4984_;
v___y_4974_ = v___y_4985_;
v___y_4975_ = v___y_4986_;
v___y_4976_ = v___y_4982_;
goto v___jp_4969_;
}
}
v___jp_4990_:
{
uint64_t v___x_4995_; uint8_t v___x_4996_; 
v___x_4995_ = 0ULL;
v___x_4996_ = lean_uint64_dec_eq(v___y_4991_, v___x_4995_);
if (v___x_4996_ == 0)
{
uint64_t v___x_4997_; uint64_t v___x_4998_; uint8_t v___x_4999_; 
v___x_4997_ = 32ULL;
v___x_4998_ = lean_uint64_shift_right(v___y_4991_, v___x_4997_);
v___x_4999_ = lean_uint64_dec_eq(v___x_4998_, v___x_4995_);
if (v___x_4999_ == 0)
{
v___y_4981_ = v___x_4997_;
v___y_4982_ = v___x_4995_;
v___y_4983_ = v___y_4991_;
v___y_4984_ = v___y_4992_;
v___y_4985_ = v___y_4993_;
v___y_4986_ = v___y_4994_;
v___y_4987_ = v___x_4998_;
goto v___jp_4980_;
}
else
{
v___y_4981_ = v___x_4997_;
v___y_4982_ = v___x_4995_;
v___y_4983_ = v___y_4991_;
v___y_4984_ = v___y_4992_;
v___y_4985_ = v___y_4993_;
v___y_4986_ = v___y_4994_;
v___y_4987_ = v___y_4991_;
goto v___jp_4980_;
}
}
else
{
if (v___y_4992_ == 0)
{
uint32_t v___x_5000_; 
v___x_5000_ = 0;
return v___x_5000_;
}
else
{
uint32_t v___x_5001_; 
v___x_5001_ = 2147483648;
return v___x_5001_;
}
}
}
v___jp_5002_:
{
uint64_t v___x_5009_; uint64_t v___x_5010_; uint64_t v___x_5011_; uint8_t v___x_5012_; 
v___x_5009_ = lean_uint64_mul(v___y_5007_, v___y_5003_);
v___x_5010_ = lean_uint64_add(v___y_5005_, v___y_5008_);
v___x_5011_ = 281474976710656ULL;
v___x_5012_ = lean_uint64_dec_lt(v___x_5009_, v___x_5011_);
if (v___x_5012_ == 0)
{
v___y_4991_ = v___x_5009_;
v___y_4992_ = v___y_5004_;
v___y_4993_ = v___x_5010_;
v___y_4994_ = v___y_5006_;
goto v___jp_4990_;
}
else
{
uint64_t v___x_5013_; uint8_t v___x_5014_; 
v___x_5013_ = 123ULL;
v___x_5014_ = lean_uint64_dec_le(v___x_5010_, v___x_5013_);
if (v___x_5014_ == 0)
{
v___y_4991_ = v___x_5009_;
v___y_4992_ = v___y_5004_;
v___y_4993_ = v___x_5010_;
v___y_4994_ = v___y_5006_;
goto v___jp_4990_;
}
else
{
uint64_t v___x_5015_; uint8_t v___x_5016_; 
v___x_5015_ = 0ULL;
v___x_5016_ = lean_uint64_dec_eq(v___x_5009_, v___x_5015_);
if (v___x_5016_ == 0)
{
uint64_t v___x_5017_; uint64_t v___x_5018_; uint8_t v___x_5019_; 
v___x_5017_ = 149ULL;
v___x_5018_ = lean_uint64_sub(v___x_5017_, v___x_5010_);
v___x_5019_ = lean_uint64_dec_eq(v___x_5018_, v___x_5015_);
if (v___x_5019_ == 0)
{
uint64_t v___x_5020_; uint8_t v___x_5021_; 
v___x_5020_ = 64ULL;
v___x_5021_ = lean_uint64_dec_lt(v___x_5018_, v___x_5020_);
if (v___x_5021_ == 0)
{
uint8_t v___x_5022_; 
v___x_5022_ = lean_uint64_dec_eq(v___x_5018_, v___x_5020_);
if (v___x_5022_ == 0)
{
v___y_4742_ = v___y_5004_;
v___y_4743_ = v___x_5015_;
v___y_4744_ = v___y_5006_;
v___y_4745_ = v___x_5015_;
goto v___jp_4741_;
}
else
{
uint64_t v___x_5023_; uint8_t v___x_5024_; 
v___x_5023_ = 9223372036854775808ULL;
v___x_5024_ = lean_uint64_dec_lt(v___x_5023_, v___x_5009_);
if (v___x_5024_ == 0)
{
v___y_4742_ = v___y_5004_;
v___y_4743_ = v___x_5015_;
v___y_4744_ = v___y_5006_;
v___y_4745_ = v___x_5015_;
goto v___jp_4741_;
}
else
{
uint64_t v___x_5025_; 
v___x_5025_ = 1ULL;
v___y_4742_ = v___y_5004_;
v___y_4743_ = v___x_5015_;
v___y_4744_ = v___y_5006_;
v___y_4745_ = v___x_5025_;
goto v___jp_4741_;
}
}
}
else
{
uint64_t v_quotient_5026_; uint64_t v___x_5027_; uint64_t v___x_5028_; uint64_t v___x_5029_; uint64_t v_remainder_5030_; uint64_t v___x_5031_; uint64_t v_half_5032_; uint8_t v___x_5033_; 
v_quotient_5026_ = lean_uint64_shift_right(v___x_5009_, v___x_5018_);
v___x_5027_ = 1ULL;
v___x_5028_ = lean_uint64_shift_left(v___x_5027_, v___x_5018_);
v___x_5029_ = lean_uint64_sub(v___x_5028_, v___x_5027_);
v_remainder_5030_ = lean_uint64_land(v___x_5009_, v___x_5029_);
v___x_5031_ = lean_uint64_sub(v___x_5018_, v___x_5027_);
v_half_5032_ = lean_uint64_shift_left(v___x_5027_, v___x_5031_);
v___x_5033_ = lean_uint64_dec_lt(v_remainder_5030_, v_half_5032_);
if (v___x_5033_ == 0)
{
uint8_t v___x_5034_; 
v___x_5034_ = lean_uint64_dec_lt(v_half_5032_, v_remainder_5030_);
if (v___x_5034_ == 0)
{
uint64_t v___x_5035_; uint8_t v___x_5036_; 
v___x_5035_ = lean_uint64_land(v_quotient_5026_, v___x_5027_);
v___x_5036_ = lean_uint64_dec_eq(v___x_5035_, v___x_5015_);
if (v___x_5036_ == 0)
{
uint64_t v___x_5037_; 
v___x_5037_ = lean_uint64_add(v_quotient_5026_, v___x_5027_);
v___y_4742_ = v___y_5004_;
v___y_4743_ = v___x_5015_;
v___y_4744_ = v___y_5006_;
v___y_4745_ = v___x_5037_;
goto v___jp_4741_;
}
else
{
v___y_4742_ = v___y_5004_;
v___y_4743_ = v___x_5015_;
v___y_4744_ = v___y_5006_;
v___y_4745_ = v_quotient_5026_;
goto v___jp_4741_;
}
}
else
{
uint64_t v___x_5038_; 
v___x_5038_ = lean_uint64_add(v_quotient_5026_, v___x_5027_);
v___y_4742_ = v___y_5004_;
v___y_4743_ = v___x_5015_;
v___y_4744_ = v___y_5006_;
v___y_4745_ = v___x_5038_;
goto v___jp_4741_;
}
}
else
{
v___y_4742_ = v___y_5004_;
v___y_4743_ = v___x_5015_;
v___y_4744_ = v___y_5006_;
v___y_4745_ = v_quotient_5026_;
goto v___jp_4741_;
}
}
}
else
{
v___y_4742_ = v___y_5004_;
v___y_4743_ = v___x_5015_;
v___y_4744_ = v___y_5006_;
v___y_4745_ = v___x_5009_;
goto v___jp_4741_;
}
}
else
{
if (v___y_5004_ == 0)
{
uint32_t v___x_5039_; 
v___x_5039_ = 0;
return v___x_5039_;
}
else
{
uint32_t v___x_5040_; 
v___x_5040_ = 2147483648;
return v___x_5040_;
}
}
}
}
}
v___jp_5044_:
{
uint64_t v___x_5050_; uint64_t v___x_5051_; uint8_t v___x_5052_; 
v___x_5050_ = lean_uint32_to_uint64(v_ey_5043_);
v___x_5051_ = 0ULL;
v___x_5052_ = lean_uint64_dec_eq(v___x_5050_, v___x_5051_);
if (v___x_5052_ == 0)
{
uint64_t v___x_5053_; uint64_t v___x_5054_; 
v___x_5053_ = 1ULL;
v___x_5054_ = lean_uint64_sub(v___x_5050_, v___x_5053_);
v___y_5003_ = v___y_5045_;
v___y_5004_ = v___y_5046_;
v___y_5005_ = v___y_5049_;
v___y_5006_ = v___y_5048_;
v___y_5007_ = v___y_5047_;
v___y_5008_ = v___x_5054_;
goto v___jp_5002_;
}
else
{
v___y_5003_ = v___y_5045_;
v___y_5004_ = v___y_5046_;
v___y_5005_ = v___y_5049_;
v___y_5006_ = v___y_5048_;
v___y_5007_ = v___y_5047_;
v___y_5008_ = v___x_5051_;
goto v___jp_5002_;
}
}
v___jp_5055_:
{
uint64_t v___x_5060_; uint64_t v___x_5061_; uint8_t v___x_5062_; 
v___x_5060_ = lean_uint32_to_uint64(v_ex_5041_);
v___x_5061_ = 0ULL;
v___x_5062_ = lean_uint64_dec_eq(v___x_5060_, v___x_5061_);
if (v___x_5062_ == 0)
{
uint64_t v___x_5063_; uint64_t v___x_5064_; 
v___x_5063_ = 1ULL;
v___x_5064_ = lean_uint64_sub(v___x_5060_, v___x_5063_);
v___y_5045_ = v___y_5059_;
v___y_5046_ = v___y_5056_;
v___y_5047_ = v___y_5058_;
v___y_5048_ = v___y_5057_;
v___y_5049_ = v___x_5064_;
goto v___jp_5044_;
}
else
{
v___y_5045_ = v___y_5059_;
v___y_5046_ = v___y_5056_;
v___y_5047_ = v___y_5058_;
v___y_5048_ = v___y_5057_;
v___y_5049_ = v___x_5061_;
goto v___jp_5044_;
}
}
v___jp_5065_:
{
uint32_t v___x_5070_; uint8_t v___x_5071_; 
v___x_5070_ = 0;
v___x_5071_ = lean_uint32_dec_eq(v_ey_5043_, v___x_5070_);
if (v___x_5071_ == 0)
{
uint64_t v___x_5072_; uint64_t v___x_5073_; uint64_t v___x_5074_; 
v___x_5072_ = lean_uint32_to_uint64(v___y_5066_);
v___x_5073_ = 8388608ULL;
v___x_5074_ = lean_uint64_lor(v___x_5072_, v___x_5073_);
v___y_5056_ = v___y_5067_;
v___y_5057_ = v___y_5068_;
v___y_5058_ = v___y_5069_;
v___y_5059_ = v___x_5074_;
goto v___jp_5055_;
}
else
{
uint64_t v___x_5075_; 
v___x_5075_ = lean_uint32_to_uint64(v___y_5066_);
v___y_5056_ = v___y_5067_;
v___y_5057_ = v___y_5068_;
v___y_5058_ = v___y_5069_;
v___y_5059_ = v___x_5075_;
goto v___jp_5055_;
}
}
v___jp_5076_:
{
uint32_t v___x_5078_; uint32_t v_xFraction_5079_; uint32_t v_yFraction_5080_; uint32_t v___x_5081_; uint8_t v___x_5082_; 
v___x_5078_ = 8388607;
v_xFraction_5079_ = lean_uint32_land(v_x_4699_, v___x_5078_);
v_yFraction_5080_ = lean_uint32_land(v_y_4700_, v___x_5078_);
v___x_5081_ = 0;
v___x_5082_ = lean_uint32_dec_eq(v_ex_5041_, v___x_5081_);
if (v___x_5082_ == 0)
{
uint64_t v___x_5083_; uint64_t v___x_5084_; uint64_t v___x_5085_; 
v___x_5083_ = lean_uint32_to_uint64(v_xFraction_5079_);
v___x_5084_ = 8388608ULL;
v___x_5085_ = lean_uint64_lor(v___x_5083_, v___x_5084_);
v___y_5066_ = v_yFraction_5080_;
v___y_5067_ = v___y_5077_;
v___y_5068_ = v___x_5078_;
v___y_5069_ = v___x_5085_;
goto v___jp_5065_;
}
else
{
uint64_t v___x_5086_; 
v___x_5086_ = lean_uint32_to_uint64(v_xFraction_5079_);
v___y_5066_ = v_yFraction_5080_;
v___y_5067_ = v___y_5077_;
v___y_5068_ = v___x_5078_;
v___y_5069_ = v___x_5086_;
goto v___jp_5065_;
}
}
v___jp_5090_:
{
if (v___y_5092_ == 0)
{
v___y_5077_ = v___x_5089_;
goto v___jp_5076_;
}
else
{
v___y_5077_ = v___y_5091_;
goto v___jp_5076_;
}
}
v___jp_5093_:
{
if (v___y_5094_ == 0)
{
if (v___y_5096_ == 0)
{
v___y_5091_ = v___y_5095_;
v___y_5092_ = v___x_5089_;
goto v___jp_5090_;
}
else
{
v___y_5077_ = v___x_5089_;
goto v___jp_5076_;
}
}
else
{
v___y_5091_ = v___y_5095_;
v___y_5092_ = v___y_5096_;
goto v___jp_5090_;
}
}
v___jp_5097_:
{
uint32_t v___x_5100_; uint32_t v___x_5101_; uint32_t v___x_5102_; uint8_t v___x_5103_; 
v___x_5100_ = 2147483648;
v___x_5101_ = lean_uint32_land(v_y_4700_, v___x_5100_);
v___x_5102_ = 0;
v___x_5103_ = lean_uint32_dec_eq(v___x_5101_, v___x_5102_);
if (v___x_5103_ == 0)
{
v___y_5094_ = v___y_5099_;
v___y_5095_ = v___y_5098_;
v___y_5096_ = v___x_5089_;
goto v___jp_5093_;
}
else
{
v___y_5094_ = v___y_5099_;
v___y_5095_ = v___y_5098_;
v___y_5096_ = v___y_5098_;
goto v___jp_5093_;
}
}
v___jp_5104_:
{
if (v___y_5105_ == 0)
{
uint32_t v___x_5106_; uint32_t v___x_5107_; uint32_t v___x_5108_; uint8_t v___x_5109_; 
v___x_5106_ = 2147483648;
v___x_5107_ = lean_uint32_land(v_x_4699_, v___x_5106_);
v___x_5108_ = 0;
v___x_5109_ = lean_uint32_dec_eq(v___x_5107_, v___x_5108_);
if (v___x_5109_ == 0)
{
v___y_5098_ = v___y_5105_;
v___y_5099_ = v___x_5089_;
goto v___jp_5097_;
}
else
{
v___y_5098_ = v___y_5105_;
v___y_5099_ = v___y_5105_;
goto v___jp_5097_;
}
}
else
{
lean_object* v___x_5110_; lean_object* v___x_5111_; lean_object* v___x_5112_; lean_object* v___x_5113_; uint32_t v___x_5114_; 
v___x_5110_ = ((lean_object*)(lp_competition_Submission_TunedAdd_Fmt___closed__0));
v___x_5111_ = lean_uint32_to_nat(v_x_4699_);
v___x_5112_ = lean_uint32_to_nat(v_y_4700_);
v___x_5113_ = lp_floatlib_FloatLib_Floats_Formats_BinaryInterchange_Model_MulBackend_word(v___x_5110_, v___x_5111_, v___x_5112_);
v___x_5114_ = lean_uint32_of_nat(v___x_5113_);
lean_dec(v___x_5113_);
return v___x_5114_;
}
}
v___jp_5115_:
{
uint8_t v___x_5116_; 
v___x_5116_ = lean_uint32_dec_eq(v_ey_5043_, v___x_4758_);
if (v___x_5116_ == 0)
{
goto v___jp_4701_;
}
else
{
if (v___x_5089_ == 0)
{
uint32_t v___x_5117_; 
v___x_5117_ = lp_competition_Submission_FastMul_mul(v_x_4699_, v_y_4700_);
return v___x_5117_;
}
else
{
goto v___jp_4701_;
}
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_mul___boxed(lean_object* v_x_5126_, lean_object* v_y_5127_){
_start:
{
uint32_t v_x_boxed_5128_; uint32_t v_y_boxed_5129_; uint32_t v_res_5130_; lean_object* v_r_5131_; 
v_x_boxed_5128_ = lean_unbox_uint32(v_x_5126_);
lean_dec(v_x_5126_);
v_y_boxed_5129_ = lean_unbox_uint32(v_y_5127_);
lean_dec(v_y_5127_);
v_res_5130_ = lp_competition_Submission_mul(v_x_boxed_5128_, v_y_boxed_5129_);
v_r_5131_ = lean_box_uint32(v_res_5130_);
return v_r_5131_;
}
}
LEAN_EXPORT uint32_t lp_competition___private_Init_Data_Array_Basic_0__Array_foldlMUnsafe_fold___at___00Submission_referenceSum_spec__0(lean_object* v_as_5132_, size_t v_i_5133_, size_t v_stop_5134_, uint32_t v_b_5135_){
_start:
{
uint32_t v___y_5137_; float v___y_5142_; float v___y_5143_; uint8_t v___x_5146_; 
v___x_5146_ = lean_usize_dec_eq(v_i_5133_, v_stop_5134_);
if (v___x_5146_ == 0)
{
lean_object* v___x_5147_; float v___y_5149_; uint8_t v___y_5150_; float v___y_5168_; uint8_t v___y_5179_; uint32_t v___x_5202_; uint32_t v___x_5203_; uint32_t v___x_5204_; uint32_t v___x_5212_; uint8_t v___x_5213_; 
v___x_5147_ = lean_array_uget_borrowed(v_as_5132_, v_i_5133_);
v___x_5202_ = 23;
v___x_5203_ = lean_uint32_shift_right(v_b_5135_, v___x_5202_);
v___x_5204_ = 255;
v___x_5212_ = lean_uint32_land(v___x_5203_, v___x_5204_);
v___x_5213_ = lean_uint32_dec_eq(v___x_5212_, v___x_5204_);
if (v___x_5213_ == 0)
{
goto v___jp_5205_;
}
else
{
if (v___x_5146_ == 0)
{
uint32_t v___x_5214_; uint32_t v___x_5215_; 
v___x_5214_ = lean_unbox_uint32(v___x_5147_);
v___x_5215_ = lp_competition_Submission_TunedAdd_add(v_b_5135_, v___x_5214_);
v___y_5137_ = v___x_5215_;
goto v___jp_5136_;
}
else
{
goto v___jp_5205_;
}
}
v___jp_5148_:
{
if (v___y_5150_ == 0)
{
uint32_t v___x_5151_; float v___x_5152_; 
v___x_5151_ = lean_unbox_uint32(v___x_5147_);
v___x_5152_ = lean_float32_of_bits(v___x_5151_);
v___y_5142_ = v___y_5149_;
v___y_5143_ = v___x_5152_;
goto v___jp_5141_;
}
else
{
uint32_t v___x_5153_; uint32_t v___x_5154_; uint32_t v___x_5155_; uint32_t v___x_5156_; uint32_t v___x_5157_; float v___x_5158_; lean_object* v___x_5159_; uint32_t v___x_5160_; uint32_t v___x_5161_; uint32_t v___x_5162_; lean_object* v___x_5163_; lean_object* v___x_5164_; float v___x_5165_; float v___x_5166_; 
v___x_5153_ = 8388607;
v___x_5154_ = lean_unbox_uint32(v___x_5147_);
v___x_5155_ = lean_uint32_land(v___x_5154_, v___x_5153_);
v___x_5156_ = 8388608;
v___x_5157_ = lean_uint32_lor(v___x_5155_, v___x_5156_);
v___x_5158_ = lean_uint32_to_float32(v___x_5157_);
v___x_5159_ = lp_competition_R2W01b_scaleTable;
v___x_5160_ = 23;
v___x_5161_ = lean_unbox_uint32(v___x_5147_);
v___x_5162_ = lean_uint32_shift_right(v___x_5161_, v___x_5160_);
v___x_5163_ = lean_uint32_to_nat(v___x_5162_);
v___x_5164_ = lean_array_fget_borrowed(v___x_5159_, v___x_5163_);
lean_dec(v___x_5163_);
v___x_5165_ = lean_unbox_float32(v___x_5164_);
v___x_5166_ = lean_float32_mul(v___x_5158_, v___x_5165_);
v___y_5142_ = v___y_5149_;
v___y_5143_ = v___x_5166_;
goto v___jp_5141_;
}
}
v___jp_5167_:
{
uint32_t v___x_5169_; uint32_t v___x_5170_; uint32_t v_a_5171_; uint32_t v___x_5172_; uint32_t v___x_5173_; uint32_t v___x_5174_; uint8_t v___x_5175_; 
v___x_5169_ = 2147483647;
v___x_5170_ = lean_unbox_uint32(v___x_5147_);
v_a_5171_ = lean_uint32_land(v___x_5170_, v___x_5169_);
v___x_5172_ = 201326591;
v___x_5173_ = 1;
v___x_5174_ = lean_uint32_sub(v_a_5171_, v___x_5173_);
v___x_5175_ = lean_uint32_dec_le(v___x_5172_, v___x_5174_);
if (v___x_5175_ == 0)
{
v___y_5149_ = v___y_5168_;
v___y_5150_ = v___x_5175_;
goto v___jp_5148_;
}
else
{
uint32_t v___x_5176_; uint8_t v___x_5177_; 
v___x_5176_ = 2139095040;
v___x_5177_ = lean_uint32_dec_lt(v_a_5171_, v___x_5176_);
v___y_5149_ = v___y_5168_;
v___y_5150_ = v___x_5177_;
goto v___jp_5148_;
}
}
v___jp_5178_:
{
if (v___y_5179_ == 0)
{
float v___x_5180_; 
v___x_5180_ = lean_float32_of_bits(v_b_5135_);
v___y_5168_ = v___x_5180_;
goto v___jp_5167_;
}
else
{
uint32_t v___x_5181_; uint32_t v___x_5182_; uint32_t v___x_5183_; uint32_t v___x_5184_; float v___x_5185_; lean_object* v___x_5186_; uint32_t v___x_5187_; uint32_t v___x_5188_; lean_object* v___x_5189_; lean_object* v___x_5190_; float v___x_5191_; float v___x_5192_; 
v___x_5181_ = 8388607;
v___x_5182_ = lean_uint32_land(v_b_5135_, v___x_5181_);
v___x_5183_ = 8388608;
v___x_5184_ = lean_uint32_lor(v___x_5182_, v___x_5183_);
v___x_5185_ = lean_uint32_to_float32(v___x_5184_);
v___x_5186_ = lp_competition_R2W01b_scaleTable;
v___x_5187_ = 23;
v___x_5188_ = lean_uint32_shift_right(v_b_5135_, v___x_5187_);
v___x_5189_ = lean_uint32_to_nat(v___x_5188_);
v___x_5190_ = lean_array_fget_borrowed(v___x_5186_, v___x_5189_);
lean_dec(v___x_5189_);
v___x_5191_ = lean_unbox_float32(v___x_5190_);
v___x_5192_ = lean_float32_mul(v___x_5185_, v___x_5191_);
v___y_5168_ = v___x_5192_;
goto v___jp_5167_;
}
}
v___jp_5193_:
{
uint32_t v___x_5194_; uint32_t v_a_5195_; uint32_t v___x_5196_; uint32_t v___x_5197_; uint32_t v___x_5198_; uint8_t v___x_5199_; 
v___x_5194_ = 2147483647;
v_a_5195_ = lean_uint32_land(v_b_5135_, v___x_5194_);
v___x_5196_ = 201326591;
v___x_5197_ = 1;
v___x_5198_ = lean_uint32_sub(v_a_5195_, v___x_5197_);
v___x_5199_ = lean_uint32_dec_le(v___x_5196_, v___x_5198_);
if (v___x_5199_ == 0)
{
v___y_5179_ = v___x_5199_;
goto v___jp_5178_;
}
else
{
uint32_t v___x_5200_; uint8_t v___x_5201_; 
v___x_5200_ = 2139095040;
v___x_5201_ = lean_uint32_dec_lt(v_a_5195_, v___x_5200_);
v___y_5179_ = v___x_5201_;
goto v___jp_5178_;
}
}
v___jp_5205_:
{
uint32_t v___x_5206_; uint32_t v___x_5207_; uint32_t v___x_5208_; uint8_t v___x_5209_; 
v___x_5206_ = lean_unbox_uint32(v___x_5147_);
v___x_5207_ = lean_uint32_shift_right(v___x_5206_, v___x_5202_);
v___x_5208_ = lean_uint32_land(v___x_5207_, v___x_5204_);
v___x_5209_ = lean_uint32_dec_eq(v___x_5208_, v___x_5204_);
if (v___x_5209_ == 0)
{
goto v___jp_5193_;
}
else
{
if (v___x_5146_ == 0)
{
uint32_t v___x_5210_; uint32_t v___x_5211_; 
v___x_5210_ = lean_unbox_uint32(v___x_5147_);
v___x_5211_ = lp_competition_Submission_TunedAdd_add(v_b_5135_, v___x_5210_);
v___y_5137_ = v___x_5211_;
goto v___jp_5136_;
}
else
{
goto v___jp_5193_;
}
}
}
}
else
{
return v_b_5135_;
}
v___jp_5136_:
{
size_t v___x_5138_; size_t v___x_5139_; 
v___x_5138_ = ((size_t)1ULL);
v___x_5139_ = lean_usize_add(v_i_5133_, v___x_5138_);
v_i_5133_ = v___x_5139_;
v_b_5135_ = v___y_5137_;
goto _start;
}
v___jp_5141_:
{
float v___x_5144_; uint32_t v___x_5145_; 
v___x_5144_ = lean_float32_add(v___y_5142_, v___y_5143_);
v___x_5145_ = lean_float32_to_bits(v___x_5144_);
v___y_5137_ = v___x_5145_;
goto v___jp_5136_;
}
}
}
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_foldlMUnsafe_fold___at___00Submission_referenceSum_spec__0___boxed(lean_object* v_as_5216_, lean_object* v_i_5217_, lean_object* v_stop_5218_, lean_object* v_b_5219_){
_start:
{
size_t v_i_boxed_5220_; size_t v_stop_boxed_5221_; uint32_t v_b_boxed_5222_; uint32_t v_res_5223_; lean_object* v_r_5224_; 
v_i_boxed_5220_ = lean_unbox_usize(v_i_5217_);
lean_dec(v_i_5217_);
v_stop_boxed_5221_ = lean_unbox_usize(v_stop_5218_);
lean_dec(v_stop_5218_);
v_b_boxed_5222_ = lean_unbox_uint32(v_b_5219_);
lean_dec(v_b_5219_);
v_res_5223_ = lp_competition___private_Init_Data_Array_Basic_0__Array_foldlMUnsafe_fold___at___00Submission_referenceSum_spec__0(v_as_5216_, v_i_boxed_5220_, v_stop_boxed_5221_, v_b_boxed_5222_);
lean_dec_ref(v_as_5216_);
v_r_5224_ = lean_box_uint32(v_res_5223_);
return v_r_5224_;
}
}
static lean_object* _init_lp_competition_Submission_referenceSum___redArg___closed__0(void){
_start:
{
lean_object* v___x_5225_; lean_object* v___x_5226_; lean_object* v___x_5227_; 
v___x_5225_ = lean_unsigned_to_nat(0u);
v___x_5226_ = lean_unsigned_to_nat(32u);
v___x_5227_ = l_BitVec_ofNat(v___x_5226_, v___x_5225_);
return v___x_5227_;
}
}
static uint32_t _init_lp_competition_Submission_referenceSum___redArg___closed__1(void){
_start:
{
lean_object* v___x_5228_; uint32_t v___x_5229_; 
v___x_5228_ = lean_obj_once(&lp_competition_Submission_referenceSum___redArg___closed__0, &lp_competition_Submission_referenceSum___redArg___closed__0_once, _init_lp_competition_Submission_referenceSum___redArg___closed__0);
v___x_5229_ = lean_uint32_of_nat(v___x_5228_);
return v___x_5229_;
}
}
LEAN_EXPORT uint32_t lp_competition_Submission_referenceSum___redArg(lean_object* v_x_5230_){
_start:
{
lean_object* v___x_5231_; uint32_t v___x_5232_; lean_object* v___x_5233_; uint8_t v___x_5234_; 
v___x_5231_ = lean_unsigned_to_nat(0u);
v___x_5232_ = lean_uint32_once(&lp_competition_Submission_referenceSum___redArg___closed__1, &lp_competition_Submission_referenceSum___redArg___closed__1_once, _init_lp_competition_Submission_referenceSum___redArg___closed__1);
v___x_5233_ = lean_array_get_size(v_x_5230_);
v___x_5234_ = lean_nat_dec_lt(v___x_5231_, v___x_5233_);
if (v___x_5234_ == 0)
{
return v___x_5232_;
}
else
{
uint8_t v___x_5235_; 
v___x_5235_ = lean_nat_dec_le(v___x_5233_, v___x_5233_);
if (v___x_5235_ == 0)
{
if (v___x_5234_ == 0)
{
return v___x_5232_;
}
else
{
size_t v___x_5236_; size_t v___x_5237_; uint32_t v___x_5238_; 
v___x_5236_ = ((size_t)0ULL);
v___x_5237_ = lean_usize_of_nat(v___x_5233_);
v___x_5238_ = lp_competition___private_Init_Data_Array_Basic_0__Array_foldlMUnsafe_fold___at___00Submission_referenceSum_spec__0(v_x_5230_, v___x_5236_, v___x_5237_, v___x_5232_);
return v___x_5238_;
}
}
else
{
size_t v___x_5239_; size_t v___x_5240_; uint32_t v___x_5241_; 
v___x_5239_ = ((size_t)0ULL);
v___x_5240_ = lean_usize_of_nat(v___x_5233_);
v___x_5241_ = lp_competition___private_Init_Data_Array_Basic_0__Array_foldlMUnsafe_fold___at___00Submission_referenceSum_spec__0(v_x_5230_, v___x_5239_, v___x_5240_, v___x_5232_);
return v___x_5241_;
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_referenceSum___redArg___boxed(lean_object* v_x_5242_){
_start:
{
uint32_t v_res_5243_; lean_object* v_r_5244_; 
v_res_5243_ = lp_competition_Submission_referenceSum___redArg(v_x_5242_);
lean_dec_ref(v_x_5242_);
v_r_5244_ = lean_box_uint32(v_res_5243_);
return v_r_5244_;
}
}
LEAN_EXPORT uint32_t lp_competition_Submission_referenceSum(lean_object* v_n_5245_, lean_object* v_x_5246_){
_start:
{
uint32_t v___x_5247_; 
v___x_5247_ = lp_competition_Submission_referenceSum___redArg(v_x_5246_);
return v___x_5247_;
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_referenceSum___boxed(lean_object* v_n_5248_, lean_object* v_x_5249_){
_start:
{
uint32_t v_res_5250_; lean_object* v_r_5251_; 
v_res_5250_ = lp_competition_Submission_referenceSum(v_n_5248_, v_x_5249_);
lean_dec_ref(v_x_5249_);
lean_dec(v_n_5248_);
v_r_5251_ = lean_box_uint32(v_res_5250_);
return v_r_5251_;
}
}
LEAN_EXPORT uint32_t lp_competition_Fin_foldl_loop___at___00Submission_referenceBmm_spec__0(lean_object* v_A_5252_, lean_object* v_fst_5253_, lean_object* v_m_5254_, lean_object* v_fst_5255_, lean_object* v_n_5256_, lean_object* v_B_5257_, lean_object* v_p_5258_, lean_object* v_snd_5259_, lean_object* v_n_5260_, uint32_t v_x_5261_, lean_object* v_i_5262_){
_start:
{
uint32_t v___y_5264_; float v___y_5269_; float v___y_5270_; float v___y_5274_; uint32_t v___y_5275_; uint8_t v___y_5276_; uint32_t v___y_5291_; float v___y_5292_; uint32_t v___y_5302_; uint8_t v___y_5303_; uint32_t v___y_5318_; uint8_t v___x_5320_; uint32_t v___y_5322_; uint32_t v___y_5341_; uint32_t v___y_5345_; uint32_t v___y_5349_; uint32_t v___y_5350_; uint32_t v___y_5351_; uint32_t v___y_5355_; uint8_t v___y_5356_; uint64_t v___y_5357_; uint64_t v___y_5358_; uint32_t v___y_5370_; uint32_t v___y_5371_; uint32_t v___y_5372_; uint32_t v___y_5373_; uint32_t v___y_5374_; uint32_t v___y_5375_; uint32_t v___y_5382_; uint32_t v___y_5383_; uint32_t v___y_5384_; uint32_t v___y_5385_; uint8_t v___y_5386_; uint32_t v___y_5387_; uint32_t v___y_5391_; uint32_t v___y_5392_; uint32_t v___y_5393_; uint8_t v___y_5394_; uint64_t v___y_5395_; uint64_t v___y_5396_; uint64_t v___y_5397_; uint8_t v___y_5407_; uint32_t v___y_5408_; uint32_t v___y_5409_; uint32_t v___y_5410_; uint64_t v___y_5411_; uint8_t v___y_5412_; uint64_t v___y_5413_; uint64_t v___y_5414_; uint32_t v___y_5421_; uint32_t v___y_5422_; uint64_t v___y_5423_; uint32_t v___y_5424_; uint8_t v___y_5425_; uint64_t v___y_5426_; uint64_t v___y_5427_; uint64_t v___y_5433_; uint32_t v___y_5434_; uint32_t v___y_5435_; uint64_t v___y_5436_; uint32_t v___y_5437_; uint8_t v___y_5438_; uint64_t v___y_5439_; uint64_t v___y_5440_; uint32_t v___y_5495_; uint32_t v___y_5496_; uint64_t v___y_5497_; uint64_t v___y_5498_; uint64_t v___y_5499_; uint32_t v___y_5500_; uint8_t v___y_5501_; uint64_t v___y_5502_; uint64_t v___y_5503_; uint64_t v___y_5509_; uint32_t v___y_5510_; uint32_t v___y_5511_; uint64_t v___y_5512_; uint32_t v___y_5513_; uint64_t v___y_5514_; uint64_t v___y_5515_; uint64_t v___y_5516_; uint8_t v___y_5517_; uint64_t v___y_5518_; uint64_t v___y_5519_; uint32_t v___y_5524_; uint32_t v___y_5525_; uint64_t v___y_5526_; uint64_t v___y_5527_; uint32_t v___y_5528_; uint64_t v___y_5529_; uint8_t v___y_5530_; uint64_t v___y_5531_; uint64_t v___y_5532_; uint64_t v___y_5537_; uint64_t v___y_5538_; uint32_t v___y_5539_; uint32_t v___y_5540_; uint64_t v___y_5541_; uint32_t v___y_5542_; uint64_t v___y_5543_; uint8_t v___y_5544_; uint64_t v___y_5545_; uint64_t v___y_5546_; uint64_t v___y_5547_; uint64_t v___y_5552_; uint32_t v___y_5553_; uint32_t v___y_5554_; uint64_t v___y_5555_; uint64_t v___y_5556_; uint32_t v___y_5557_; uint8_t v___y_5558_; uint64_t v___y_5559_; uint64_t v___y_5560_; uint64_t v___y_5565_; uint32_t v___y_5566_; uint32_t v___y_5567_; uint64_t v___y_5568_; uint64_t v___y_5569_; uint32_t v___y_5570_; uint64_t v___y_5571_; uint8_t v___y_5572_; uint64_t v___y_5573_; uint64_t v___y_5574_; uint64_t v___y_5575_; uint32_t v___y_5580_; uint32_t v___y_5581_; uint64_t v___y_5582_; uint64_t v___y_5583_; uint32_t v___y_5584_; uint8_t v___y_5585_; uint64_t v___y_5586_; uint64_t v___y_5587_; uint64_t v___y_5588_; uint64_t v___y_5593_; uint32_t v___y_5594_; uint32_t v___y_5595_; uint64_t v___y_5596_; uint64_t v___y_5597_; uint32_t v___y_5598_; uint64_t v___y_5599_; uint64_t v___y_5600_; uint8_t v___y_5601_; uint64_t v___y_5602_; uint64_t v___y_5603_; uint32_t v___y_5608_; uint32_t v___y_5609_; uint64_t v___y_5610_; uint64_t v___y_5611_; uint32_t v___y_5612_; uint64_t v___y_5613_; uint8_t v___y_5614_; uint64_t v___y_5615_; uint64_t v___y_5616_; uint64_t v___y_5621_; uint32_t v___y_5622_; uint32_t v___y_5623_; uint64_t v___y_5624_; uint32_t v___y_5625_; uint64_t v___y_5626_; uint8_t v___y_5627_; uint64_t v___y_5628_; uint64_t v___y_5629_; uint32_t v___y_5633_; uint64_t v___y_5634_; uint32_t v___y_5635_; uint64_t v___y_5636_; uint32_t v___y_5637_; uint8_t v___y_5638_; uint32_t v___y_5647_; uint32_t v___y_5648_; uint32_t v___y_5649_; uint32_t v___y_5653_; uint64_t v___y_5654_; uint8_t v___y_5655_; uint64_t v___y_5656_; uint32_t v___y_5668_; uint32_t v___y_5669_; uint32_t v___y_5670_; uint64_t v___y_5671_; uint64_t v___y_5672_; uint64_t v___y_5673_; uint8_t v___y_5674_; uint64_t v___y_5675_; uint32_t v___y_5709_; uint32_t v___y_5710_; uint32_t v___y_5711_; uint64_t v___y_5712_; uint32_t v___y_5713_; uint64_t v___y_5714_; uint8_t v___y_5715_; uint64_t v___y_5716_; uint32_t v___y_5723_; uint32_t v___y_5724_; uint32_t v___y_5725_; uint32_t v___y_5726_; uint64_t v___y_5727_; uint32_t v___y_5728_; uint8_t v___y_5729_; uint64_t v___y_5730_; uint32_t v___y_5737_; uint32_t v___y_5738_; uint32_t v___y_5739_; uint32_t v___y_5740_; uint32_t v___y_5741_; uint32_t v___y_5742_; uint8_t v___y_5743_; uint64_t v___y_5744_; uint32_t v___y_5752_; uint32_t v___y_5753_; uint32_t v___y_5754_; uint32_t v___y_5755_; uint32_t v___y_5756_; uint32_t v___y_5757_; uint8_t v___y_5758_; uint32_t v___y_5769_; uint32_t v___y_5770_; uint32_t v___y_5776_; uint32_t v___y_5777_; uint32_t v___y_5778_; uint32_t v___y_5779_; uint8_t v___y_5780_; uint8_t v___y_5781_; uint32_t v___y_5786_; uint32_t v___y_5787_; uint32_t v___y_5788_; uint32_t v___y_5789_; uint32_t v___y_5790_; uint32_t v___y_5791_; uint8_t v___y_5792_; uint8_t v___y_5793_; uint32_t v___y_5795_; uint32_t v___y_5796_; uint8_t v___y_5797_; uint32_t v___y_5798_; uint32_t v___y_5799_; uint32_t v___y_5800_; uint32_t v___y_5801_; uint8_t v___y_5802_; uint8_t v___y_5803_; uint32_t v___y_5805_; uint32_t v___y_5806_; uint32_t v___y_5807_; uint32_t v___y_5808_; uint32_t v___y_5809_; uint32_t v___y_5810_; uint8_t v___y_5811_; uint8_t v___y_5812_; uint32_t v___y_5818_; uint32_t v___y_5819_; uint32_t v___y_5820_; uint32_t v___y_5821_; uint32_t v___y_5822_; uint32_t v___y_5823_; uint8_t v___y_5824_; uint32_t v___y_5834_; uint32_t v___y_5835_; 
v___x_5320_ = lean_nat_dec_lt(v_i_5262_, v_n_5260_);
if (v___x_5320_ == 0)
{
lean_dec(v_i_5262_);
return v_x_5261_;
}
else
{
lean_object* v___x_5852_; lean_object* v___x_5853_; lean_object* v___x_5854_; lean_object* v___x_5855_; uint32_t v___x_5856_; uint32_t v___y_5858_; lean_object* v___x_5867_; uint8_t v___x_5868_; 
v___x_5852_ = lean_nat_mul(v_fst_5253_, v_m_5254_);
v___x_5853_ = lean_nat_add(v___x_5852_, v_fst_5255_);
lean_dec(v___x_5852_);
v___x_5854_ = lean_nat_mul(v___x_5853_, v_n_5256_);
lean_dec(v___x_5853_);
v___x_5855_ = lean_nat_add(v___x_5854_, v_i_5262_);
lean_dec(v___x_5854_);
v___x_5856_ = lean_uint32_once(&lp_competition_Submission_referenceSum___redArg___closed__1, &lp_competition_Submission_referenceSum___redArg___closed__1_once, _init_lp_competition_Submission_referenceSum___redArg___closed__1);
v___x_5867_ = lean_array_get_size(v_A_5252_);
v___x_5868_ = lean_nat_dec_lt(v___x_5855_, v___x_5867_);
if (v___x_5868_ == 0)
{
lean_dec(v___x_5855_);
v___y_5858_ = v___x_5856_;
goto v___jp_5857_;
}
else
{
lean_object* v___x_5869_; uint32_t v___x_5870_; 
v___x_5869_ = lean_array_fget_borrowed(v_A_5252_, v___x_5855_);
lean_dec(v___x_5855_);
v___x_5870_ = lean_unbox_uint32(v___x_5869_);
v___y_5858_ = v___x_5870_;
goto v___jp_5857_;
}
v___jp_5857_:
{
lean_object* v___x_5859_; lean_object* v___x_5860_; lean_object* v___x_5861_; lean_object* v___x_5862_; lean_object* v___x_5863_; uint8_t v___x_5864_; 
v___x_5859_ = lean_nat_mul(v_fst_5253_, v_n_5256_);
v___x_5860_ = lean_nat_add(v___x_5859_, v_i_5262_);
lean_dec(v___x_5859_);
v___x_5861_ = lean_nat_mul(v___x_5860_, v_p_5258_);
lean_dec(v___x_5860_);
v___x_5862_ = lean_nat_add(v___x_5861_, v_snd_5259_);
lean_dec(v___x_5861_);
v___x_5863_ = lean_array_get_size(v_B_5257_);
v___x_5864_ = lean_nat_dec_lt(v___x_5862_, v___x_5863_);
if (v___x_5864_ == 0)
{
lean_dec(v___x_5862_);
v___y_5834_ = v___y_5858_;
v___y_5835_ = v___x_5856_;
goto v___jp_5833_;
}
else
{
lean_object* v___x_5865_; uint32_t v___x_5866_; 
v___x_5865_ = lean_array_fget_borrowed(v_B_5257_, v___x_5862_);
lean_dec(v___x_5862_);
v___x_5866_ = lean_unbox_uint32(v___x_5865_);
v___y_5834_ = v___y_5858_;
v___y_5835_ = v___x_5866_;
goto v___jp_5833_;
}
}
}
v___jp_5263_:
{
lean_object* v___x_5265_; lean_object* v___x_5266_; 
v___x_5265_ = lean_unsigned_to_nat(1u);
v___x_5266_ = lean_nat_add(v_i_5262_, v___x_5265_);
lean_dec(v_i_5262_);
v_x_5261_ = v___y_5264_;
v_i_5262_ = v___x_5266_;
goto _start;
}
v___jp_5268_:
{
float v___x_5271_; uint32_t v___x_5272_; 
v___x_5271_ = lean_float32_add(v___y_5269_, v___y_5270_);
v___x_5272_ = lean_float32_to_bits(v___x_5271_);
v___y_5264_ = v___x_5272_;
goto v___jp_5263_;
}
v___jp_5273_:
{
if (v___y_5276_ == 0)
{
float v___x_5277_; 
v___x_5277_ = lean_float32_of_bits(v___y_5275_);
v___y_5269_ = v___y_5274_;
v___y_5270_ = v___x_5277_;
goto v___jp_5268_;
}
else
{
uint32_t v___x_5278_; uint32_t v___x_5279_; uint32_t v___x_5280_; uint32_t v___x_5281_; float v___x_5282_; lean_object* v___x_5283_; uint32_t v___x_5284_; uint32_t v___x_5285_; lean_object* v___x_5286_; lean_object* v___x_5287_; float v___x_5288_; float v___x_5289_; 
v___x_5278_ = 8388607;
v___x_5279_ = lean_uint32_land(v___y_5275_, v___x_5278_);
v___x_5280_ = 8388608;
v___x_5281_ = lean_uint32_lor(v___x_5279_, v___x_5280_);
v___x_5282_ = lean_uint32_to_float32(v___x_5281_);
v___x_5283_ = lp_competition_R2W01b_scaleTable;
v___x_5284_ = 23;
v___x_5285_ = lean_uint32_shift_right(v___y_5275_, v___x_5284_);
v___x_5286_ = lean_uint32_to_nat(v___x_5285_);
v___x_5287_ = lean_array_fget_borrowed(v___x_5283_, v___x_5286_);
lean_dec(v___x_5286_);
v___x_5288_ = lean_unbox_float32(v___x_5287_);
v___x_5289_ = lean_float32_mul(v___x_5282_, v___x_5288_);
v___y_5269_ = v___y_5274_;
v___y_5270_ = v___x_5289_;
goto v___jp_5268_;
}
}
v___jp_5290_:
{
uint32_t v___x_5293_; uint32_t v_a_5294_; uint32_t v___x_5295_; uint32_t v___x_5296_; uint32_t v___x_5297_; uint8_t v___x_5298_; 
v___x_5293_ = 2147483647;
v_a_5294_ = lean_uint32_land(v___y_5291_, v___x_5293_);
v___x_5295_ = 201326591;
v___x_5296_ = 1;
v___x_5297_ = lean_uint32_sub(v_a_5294_, v___x_5296_);
v___x_5298_ = lean_uint32_dec_le(v___x_5295_, v___x_5297_);
if (v___x_5298_ == 0)
{
v___y_5274_ = v___y_5292_;
v___y_5275_ = v___y_5291_;
v___y_5276_ = v___x_5298_;
goto v___jp_5273_;
}
else
{
uint32_t v___x_5299_; uint8_t v___x_5300_; 
v___x_5299_ = 2139095040;
v___x_5300_ = lean_uint32_dec_lt(v_a_5294_, v___x_5299_);
v___y_5274_ = v___y_5292_;
v___y_5275_ = v___y_5291_;
v___y_5276_ = v___x_5300_;
goto v___jp_5273_;
}
}
v___jp_5301_:
{
if (v___y_5303_ == 0)
{
float v___x_5304_; 
v___x_5304_ = lean_float32_of_bits(v_x_5261_);
v___y_5291_ = v___y_5302_;
v___y_5292_ = v___x_5304_;
goto v___jp_5290_;
}
else
{
uint32_t v___x_5305_; uint32_t v___x_5306_; uint32_t v___x_5307_; uint32_t v___x_5308_; float v___x_5309_; lean_object* v___x_5310_; uint32_t v___x_5311_; uint32_t v___x_5312_; lean_object* v___x_5313_; lean_object* v___x_5314_; float v___x_5315_; float v___x_5316_; 
v___x_5305_ = 8388607;
v___x_5306_ = lean_uint32_land(v_x_5261_, v___x_5305_);
v___x_5307_ = 8388608;
v___x_5308_ = lean_uint32_lor(v___x_5306_, v___x_5307_);
v___x_5309_ = lean_uint32_to_float32(v___x_5308_);
v___x_5310_ = lp_competition_R2W01b_scaleTable;
v___x_5311_ = 23;
v___x_5312_ = lean_uint32_shift_right(v_x_5261_, v___x_5311_);
v___x_5313_ = lean_uint32_to_nat(v___x_5312_);
v___x_5314_ = lean_array_fget_borrowed(v___x_5310_, v___x_5313_);
lean_dec(v___x_5313_);
v___x_5315_ = lean_unbox_float32(v___x_5314_);
v___x_5316_ = lean_float32_mul(v___x_5309_, v___x_5315_);
v___y_5291_ = v___y_5302_;
v___y_5292_ = v___x_5316_;
goto v___jp_5290_;
}
}
v___jp_5317_:
{
uint32_t v___x_5319_; 
v___x_5319_ = lp_competition_Submission_TunedAdd_add(v_x_5261_, v___y_5318_);
v___y_5264_ = v___x_5319_;
goto v___jp_5263_;
}
v___jp_5321_:
{
uint32_t v___x_5323_; uint32_t v___x_5324_; uint32_t v___x_5325_; uint32_t v___x_5326_; uint8_t v___x_5327_; 
v___x_5323_ = 23;
v___x_5324_ = lean_uint32_shift_right(v_x_5261_, v___x_5323_);
v___x_5325_ = 255;
v___x_5326_ = lean_uint32_land(v___x_5324_, v___x_5325_);
v___x_5327_ = lean_uint32_dec_eq(v___x_5326_, v___x_5325_);
if (v___x_5327_ == 0)
{
if (v___x_5320_ == 0)
{
v___y_5318_ = v___y_5322_;
goto v___jp_5317_;
}
else
{
uint32_t v___x_5328_; uint32_t v___x_5329_; uint8_t v___x_5330_; 
v___x_5328_ = lean_uint32_shift_right(v___y_5322_, v___x_5323_);
v___x_5329_ = lean_uint32_land(v___x_5328_, v___x_5325_);
v___x_5330_ = lean_uint32_dec_eq(v___x_5329_, v___x_5325_);
if (v___x_5330_ == 0)
{
uint32_t v___x_5331_; uint32_t v_a_5332_; uint32_t v___x_5333_; uint32_t v___x_5334_; uint32_t v___x_5335_; uint8_t v___x_5336_; 
v___x_5331_ = 2147483647;
v_a_5332_ = lean_uint32_land(v_x_5261_, v___x_5331_);
v___x_5333_ = 201326591;
v___x_5334_ = 1;
v___x_5335_ = lean_uint32_sub(v_a_5332_, v___x_5334_);
v___x_5336_ = lean_uint32_dec_le(v___x_5333_, v___x_5335_);
if (v___x_5336_ == 0)
{
v___y_5302_ = v___y_5322_;
v___y_5303_ = v___x_5336_;
goto v___jp_5301_;
}
else
{
uint32_t v___x_5337_; uint8_t v___x_5338_; 
v___x_5337_ = 2139095040;
v___x_5338_ = lean_uint32_dec_lt(v_a_5332_, v___x_5337_);
v___y_5302_ = v___y_5322_;
v___y_5303_ = v___x_5338_;
goto v___jp_5301_;
}
}
else
{
uint32_t v___x_5339_; 
v___x_5339_ = lp_competition_Submission_TunedAdd_add(v_x_5261_, v___y_5322_);
v___y_5264_ = v___x_5339_;
goto v___jp_5263_;
}
}
}
else
{
v___y_5318_ = v___y_5322_;
goto v___jp_5317_;
}
}
v___jp_5340_:
{
uint32_t v___x_5342_; uint32_t v___x_5343_; 
v___x_5342_ = 8388608;
v___x_5343_ = lean_uint32_lor(v___y_5341_, v___x_5342_);
v___y_5322_ = v___x_5343_;
goto v___jp_5321_;
}
v___jp_5344_:
{
uint32_t v___x_5346_; uint32_t v___x_5347_; 
v___x_5346_ = 8388608;
v___x_5347_ = lean_uint32_lor(v___y_5345_, v___x_5346_);
v___y_5322_ = v___x_5347_;
goto v___jp_5321_;
}
v___jp_5348_:
{
uint32_t v___x_5352_; uint32_t v___x_5353_; 
v___x_5352_ = lean_uint32_land(v___y_5350_, v___y_5349_);
v___x_5353_ = lean_uint32_lor(v___y_5351_, v___x_5352_);
v___y_5322_ = v___x_5353_;
goto v___jp_5321_;
}
v___jp_5354_:
{
uint8_t v___x_5359_; 
v___x_5359_ = lean_uint64_dec_eq(v___y_5358_, v___y_5357_);
if (v___x_5359_ == 0)
{
uint64_t v___x_5360_; uint8_t v___x_5361_; 
v___x_5360_ = 8388608ULL;
v___x_5361_ = lean_uint64_dec_eq(v___y_5358_, v___x_5360_);
if (v___x_5361_ == 0)
{
uint32_t v___x_5362_; 
v___x_5362_ = lean_uint64_to_uint32(v___y_5358_);
if (v___y_5356_ == 0)
{
uint32_t v___x_5363_; 
v___x_5363_ = 0;
v___y_5349_ = v___y_5355_;
v___y_5350_ = v___x_5362_;
v___y_5351_ = v___x_5363_;
goto v___jp_5348_;
}
else
{
uint32_t v___x_5364_; 
v___x_5364_ = 2147483648;
v___y_5349_ = v___y_5355_;
v___y_5350_ = v___x_5362_;
v___y_5351_ = v___x_5364_;
goto v___jp_5348_;
}
}
else
{
if (v___y_5356_ == 0)
{
uint32_t v___x_5365_; 
v___x_5365_ = 0;
v___y_5341_ = v___x_5365_;
goto v___jp_5340_;
}
else
{
uint32_t v___x_5366_; 
v___x_5366_ = 2147483648;
v___y_5341_ = v___x_5366_;
goto v___jp_5340_;
}
}
}
else
{
if (v___y_5356_ == 0)
{
uint32_t v___x_5367_; 
v___x_5367_ = 0;
v___y_5322_ = v___x_5367_;
goto v___jp_5321_;
}
else
{
uint32_t v___x_5368_; 
v___x_5368_ = 2147483648;
v___y_5322_ = v___x_5368_;
goto v___jp_5321_;
}
}
}
v___jp_5369_:
{
uint32_t v___x_5376_; uint32_t v___x_5377_; uint32_t v___x_5378_; uint32_t v___x_5379_; uint32_t v___x_5380_; 
v___x_5376_ = lean_uint32_land(v___y_5372_, v___y_5371_);
v___x_5377_ = lean_uint32_shift_left(v___x_5376_, v___y_5373_);
v___x_5378_ = lean_uint32_lor(v___y_5375_, v___x_5377_);
v___x_5379_ = lean_uint32_land(v___y_5374_, v___y_5370_);
v___x_5380_ = lean_uint32_lor(v___x_5378_, v___x_5379_);
v___y_5322_ = v___x_5380_;
goto v___jp_5321_;
}
v___jp_5381_:
{
if (v___y_5386_ == 0)
{
uint32_t v___x_5388_; 
v___x_5388_ = 0;
v___y_5370_ = v___y_5383_;
v___y_5371_ = v___y_5382_;
v___y_5372_ = v___y_5384_;
v___y_5373_ = v___y_5385_;
v___y_5374_ = v___y_5387_;
v___y_5375_ = v___x_5388_;
goto v___jp_5369_;
}
else
{
uint32_t v___x_5389_; 
v___x_5389_ = 2147483648;
v___y_5370_ = v___y_5383_;
v___y_5371_ = v___y_5382_;
v___y_5372_ = v___y_5384_;
v___y_5373_ = v___y_5385_;
v___y_5374_ = v___y_5387_;
v___y_5375_ = v___x_5389_;
goto v___jp_5369_;
}
}
v___jp_5390_:
{
uint64_t v___x_5398_; uint64_t v_encodedExponent_5399_; uint32_t v___x_5400_; uint64_t v___x_5401_; uint8_t v___x_5402_; 
v___x_5398_ = 171ULL;
v_encodedExponent_5399_ = lean_uint64_sub(v___y_5396_, v___x_5398_);
v___x_5400_ = lean_uint64_to_uint32(v_encodedExponent_5399_);
v___x_5401_ = 8388608ULL;
v___x_5402_ = lean_uint64_dec_lt(v___y_5397_, v___x_5401_);
if (v___x_5402_ == 0)
{
uint64_t v___x_5403_; uint32_t v___x_5404_; 
v___x_5403_ = lean_uint64_sub(v___y_5397_, v___x_5401_);
v___x_5404_ = lean_uint64_to_uint32(v___x_5403_);
v___y_5382_ = v___y_5392_;
v___y_5383_ = v___y_5391_;
v___y_5384_ = v___x_5400_;
v___y_5385_ = v___y_5393_;
v___y_5386_ = v___y_5394_;
v___y_5387_ = v___x_5404_;
goto v___jp_5381_;
}
else
{
uint32_t v___x_5405_; 
v___x_5405_ = lean_uint64_to_uint32(v___y_5395_);
v___y_5382_ = v___y_5392_;
v___y_5383_ = v___y_5391_;
v___y_5384_ = v___x_5400_;
v___y_5385_ = v___y_5393_;
v___y_5386_ = v___y_5394_;
v___y_5387_ = v___x_5405_;
goto v___jp_5381_;
}
}
v___jp_5406_:
{
uint64_t v___x_5415_; uint8_t v___x_5416_; 
v___x_5415_ = 425ULL;
v___x_5416_ = lean_uint64_dec_lt(v___x_5415_, v___y_5414_);
if (v___x_5416_ == 0)
{
if (v___y_5407_ == 0)
{
v___y_5391_ = v___y_5409_;
v___y_5392_ = v___y_5408_;
v___y_5393_ = v___y_5410_;
v___y_5394_ = v___y_5412_;
v___y_5395_ = v___y_5413_;
v___y_5396_ = v___y_5414_;
v___y_5397_ = v___y_5411_;
goto v___jp_5390_;
}
else
{
uint64_t v___x_5417_; 
v___x_5417_ = 8388608ULL;
v___y_5391_ = v___y_5409_;
v___y_5392_ = v___y_5408_;
v___y_5393_ = v___y_5410_;
v___y_5394_ = v___y_5412_;
v___y_5395_ = v___y_5413_;
v___y_5396_ = v___y_5414_;
v___y_5397_ = v___x_5417_;
goto v___jp_5390_;
}
}
else
{
if (v___y_5412_ == 0)
{
uint32_t v___x_5418_; 
v___x_5418_ = 2139095040;
v___y_5322_ = v___x_5418_;
goto v___jp_5321_;
}
else
{
uint32_t v___x_5419_; 
v___x_5419_ = 4286578688;
v___y_5322_ = v___x_5419_;
goto v___jp_5321_;
}
}
}
v___jp_5420_:
{
uint64_t v___x_5428_; uint8_t v_carry_5429_; 
v___x_5428_ = 16777216ULL;
v_carry_5429_ = lean_uint64_dec_eq(v___y_5427_, v___x_5428_);
if (v_carry_5429_ == 0)
{
v___y_5407_ = v_carry_5429_;
v___y_5408_ = v___y_5422_;
v___y_5409_ = v___y_5421_;
v___y_5410_ = v___y_5424_;
v___y_5411_ = v___y_5427_;
v___y_5412_ = v___y_5425_;
v___y_5413_ = v___y_5426_;
v___y_5414_ = v___y_5423_;
goto v___jp_5406_;
}
else
{
uint64_t v___x_5430_; uint64_t v___x_5431_; 
v___x_5430_ = 1ULL;
v___x_5431_ = lean_uint64_add(v___y_5423_, v___x_5430_);
v___y_5407_ = v_carry_5429_;
v___y_5408_ = v___y_5422_;
v___y_5409_ = v___y_5421_;
v___y_5410_ = v___y_5424_;
v___y_5411_ = v___y_5427_;
v___y_5412_ = v___y_5425_;
v___y_5413_ = v___y_5426_;
v___y_5414_ = v___x_5431_;
goto v___jp_5406_;
}
}
v___jp_5432_:
{
uint64_t v_position_5441_; uint64_t v___x_5442_; uint8_t v___x_5443_; 
v_position_5441_ = lean_uint64_add(v___y_5440_, v___y_5436_);
v___x_5442_ = 172ULL;
v___x_5443_ = lean_uint64_dec_lt(v_position_5441_, v___x_5442_);
if (v___x_5443_ == 0)
{
uint64_t v___x_5444_; uint8_t v___x_5445_; 
v___x_5444_ = 23ULL;
v___x_5445_ = lean_uint64_dec_lt(v___y_5440_, v___x_5444_);
if (v___x_5445_ == 0)
{
uint64_t v___x_5446_; uint8_t v___x_5447_; 
v___x_5446_ = lean_uint64_sub(v___y_5440_, v___x_5444_);
v___x_5447_ = lean_uint64_dec_eq(v___x_5446_, v___y_5439_);
if (v___x_5447_ == 0)
{
uint64_t v___x_5448_; uint8_t v___x_5449_; 
v___x_5448_ = 64ULL;
v___x_5449_ = lean_uint64_dec_lt(v___x_5446_, v___x_5448_);
if (v___x_5449_ == 0)
{
uint8_t v___x_5450_; 
v___x_5450_ = lean_uint64_dec_eq(v___x_5446_, v___x_5448_);
if (v___x_5450_ == 0)
{
v___y_5421_ = v___y_5435_;
v___y_5422_ = v___y_5434_;
v___y_5423_ = v_position_5441_;
v___y_5424_ = v___y_5437_;
v___y_5425_ = v___y_5438_;
v___y_5426_ = v___y_5439_;
v___y_5427_ = v___y_5439_;
goto v___jp_5420_;
}
else
{
uint64_t v___x_5451_; uint8_t v___x_5452_; 
v___x_5451_ = 9223372036854775808ULL;
v___x_5452_ = lean_uint64_dec_lt(v___x_5451_, v___y_5433_);
if (v___x_5452_ == 0)
{
v___y_5421_ = v___y_5435_;
v___y_5422_ = v___y_5434_;
v___y_5423_ = v_position_5441_;
v___y_5424_ = v___y_5437_;
v___y_5425_ = v___y_5438_;
v___y_5426_ = v___y_5439_;
v___y_5427_ = v___y_5439_;
goto v___jp_5420_;
}
else
{
uint64_t v___x_5453_; 
v___x_5453_ = 1ULL;
v___y_5421_ = v___y_5435_;
v___y_5422_ = v___y_5434_;
v___y_5423_ = v_position_5441_;
v___y_5424_ = v___y_5437_;
v___y_5425_ = v___y_5438_;
v___y_5426_ = v___y_5439_;
v___y_5427_ = v___x_5453_;
goto v___jp_5420_;
}
}
}
else
{
uint64_t v_quotient_5454_; uint64_t v___x_5455_; uint64_t v___x_5456_; uint64_t v___x_5457_; uint64_t v_remainder_5458_; uint64_t v___x_5459_; uint64_t v_half_5460_; uint8_t v___x_5461_; 
v_quotient_5454_ = lean_uint64_shift_right(v___y_5433_, v___x_5446_);
v___x_5455_ = 1ULL;
v___x_5456_ = lean_uint64_shift_left(v___x_5455_, v___x_5446_);
v___x_5457_ = lean_uint64_sub(v___x_5456_, v___x_5455_);
v_remainder_5458_ = lean_uint64_land(v___y_5433_, v___x_5457_);
v___x_5459_ = lean_uint64_sub(v___x_5446_, v___x_5455_);
v_half_5460_ = lean_uint64_shift_left(v___x_5455_, v___x_5459_);
v___x_5461_ = lean_uint64_dec_lt(v_remainder_5458_, v_half_5460_);
if (v___x_5461_ == 0)
{
uint8_t v___x_5462_; 
v___x_5462_ = lean_uint64_dec_lt(v_half_5460_, v_remainder_5458_);
if (v___x_5462_ == 0)
{
uint64_t v___x_5463_; uint8_t v___x_5464_; 
v___x_5463_ = lean_uint64_land(v_quotient_5454_, v___x_5455_);
v___x_5464_ = lean_uint64_dec_eq(v___x_5463_, v___y_5439_);
if (v___x_5464_ == 0)
{
uint64_t v___x_5465_; 
v___x_5465_ = lean_uint64_add(v_quotient_5454_, v___x_5455_);
v___y_5421_ = v___y_5435_;
v___y_5422_ = v___y_5434_;
v___y_5423_ = v_position_5441_;
v___y_5424_ = v___y_5437_;
v___y_5425_ = v___y_5438_;
v___y_5426_ = v___y_5439_;
v___y_5427_ = v___x_5465_;
goto v___jp_5420_;
}
else
{
v___y_5421_ = v___y_5435_;
v___y_5422_ = v___y_5434_;
v___y_5423_ = v_position_5441_;
v___y_5424_ = v___y_5437_;
v___y_5425_ = v___y_5438_;
v___y_5426_ = v___y_5439_;
v___y_5427_ = v_quotient_5454_;
goto v___jp_5420_;
}
}
else
{
uint64_t v___x_5466_; 
v___x_5466_ = lean_uint64_add(v_quotient_5454_, v___x_5455_);
v___y_5421_ = v___y_5435_;
v___y_5422_ = v___y_5434_;
v___y_5423_ = v_position_5441_;
v___y_5424_ = v___y_5437_;
v___y_5425_ = v___y_5438_;
v___y_5426_ = v___y_5439_;
v___y_5427_ = v___x_5466_;
goto v___jp_5420_;
}
}
else
{
v___y_5421_ = v___y_5435_;
v___y_5422_ = v___y_5434_;
v___y_5423_ = v_position_5441_;
v___y_5424_ = v___y_5437_;
v___y_5425_ = v___y_5438_;
v___y_5426_ = v___y_5439_;
v___y_5427_ = v_quotient_5454_;
goto v___jp_5420_;
}
}
}
else
{
v___y_5421_ = v___y_5435_;
v___y_5422_ = v___y_5434_;
v___y_5423_ = v_position_5441_;
v___y_5424_ = v___y_5437_;
v___y_5425_ = v___y_5438_;
v___y_5426_ = v___y_5439_;
v___y_5427_ = v___y_5433_;
goto v___jp_5420_;
}
}
else
{
uint64_t v___x_5467_; uint64_t v___x_5468_; 
v___x_5467_ = lean_uint64_sub(v___x_5444_, v___y_5440_);
v___x_5468_ = lean_uint64_shift_left(v___y_5433_, v___x_5467_);
v___y_5421_ = v___y_5435_;
v___y_5422_ = v___y_5434_;
v___y_5423_ = v_position_5441_;
v___y_5424_ = v___y_5437_;
v___y_5425_ = v___y_5438_;
v___y_5426_ = v___y_5439_;
v___y_5427_ = v___x_5468_;
goto v___jp_5420_;
}
}
else
{
uint64_t v___x_5469_; uint8_t v___x_5470_; 
v___x_5469_ = 149ULL;
v___x_5470_ = lean_uint64_dec_lt(v___y_5436_, v___x_5469_);
if (v___x_5470_ == 0)
{
uint64_t v___x_5471_; uint64_t v___x_5472_; 
v___x_5471_ = lean_uint64_sub(v___y_5436_, v___x_5469_);
v___x_5472_ = lean_uint64_shift_left(v___y_5433_, v___x_5471_);
v___y_5355_ = v___y_5435_;
v___y_5356_ = v___y_5438_;
v___y_5357_ = v___y_5439_;
v___y_5358_ = v___x_5472_;
goto v___jp_5354_;
}
else
{
uint64_t v___x_5473_; uint8_t v___x_5474_; 
v___x_5473_ = lean_uint64_sub(v___x_5469_, v___y_5436_);
v___x_5474_ = lean_uint64_dec_eq(v___x_5473_, v___y_5439_);
if (v___x_5474_ == 0)
{
uint64_t v___x_5475_; uint8_t v___x_5476_; 
v___x_5475_ = 64ULL;
v___x_5476_ = lean_uint64_dec_lt(v___x_5473_, v___x_5475_);
if (v___x_5476_ == 0)
{
uint8_t v___x_5477_; 
v___x_5477_ = lean_uint64_dec_eq(v___x_5473_, v___x_5475_);
if (v___x_5477_ == 0)
{
v___y_5355_ = v___y_5435_;
v___y_5356_ = v___y_5438_;
v___y_5357_ = v___y_5439_;
v___y_5358_ = v___y_5439_;
goto v___jp_5354_;
}
else
{
uint64_t v___x_5478_; uint8_t v___x_5479_; 
v___x_5478_ = 9223372036854775808ULL;
v___x_5479_ = lean_uint64_dec_lt(v___x_5478_, v___y_5433_);
if (v___x_5479_ == 0)
{
v___y_5355_ = v___y_5435_;
v___y_5356_ = v___y_5438_;
v___y_5357_ = v___y_5439_;
v___y_5358_ = v___y_5439_;
goto v___jp_5354_;
}
else
{
uint64_t v___x_5480_; 
v___x_5480_ = 1ULL;
v___y_5355_ = v___y_5435_;
v___y_5356_ = v___y_5438_;
v___y_5357_ = v___y_5439_;
v___y_5358_ = v___x_5480_;
goto v___jp_5354_;
}
}
}
else
{
uint64_t v_quotient_5481_; uint64_t v___x_5482_; uint64_t v___x_5483_; uint64_t v___x_5484_; uint64_t v_remainder_5485_; uint64_t v___x_5486_; uint64_t v_half_5487_; uint8_t v___x_5488_; 
v_quotient_5481_ = lean_uint64_shift_right(v___y_5433_, v___x_5473_);
v___x_5482_ = 1ULL;
v___x_5483_ = lean_uint64_shift_left(v___x_5482_, v___x_5473_);
v___x_5484_ = lean_uint64_sub(v___x_5483_, v___x_5482_);
v_remainder_5485_ = lean_uint64_land(v___y_5433_, v___x_5484_);
v___x_5486_ = lean_uint64_sub(v___x_5473_, v___x_5482_);
v_half_5487_ = lean_uint64_shift_left(v___x_5482_, v___x_5486_);
v___x_5488_ = lean_uint64_dec_lt(v_remainder_5485_, v_half_5487_);
if (v___x_5488_ == 0)
{
uint8_t v___x_5489_; 
v___x_5489_ = lean_uint64_dec_lt(v_half_5487_, v_remainder_5485_);
if (v___x_5489_ == 0)
{
uint64_t v___x_5490_; uint8_t v___x_5491_; 
v___x_5490_ = lean_uint64_land(v_quotient_5481_, v___x_5482_);
v___x_5491_ = lean_uint64_dec_eq(v___x_5490_, v___y_5439_);
if (v___x_5491_ == 0)
{
uint64_t v___x_5492_; 
v___x_5492_ = lean_uint64_add(v_quotient_5481_, v___x_5482_);
v___y_5355_ = v___y_5435_;
v___y_5356_ = v___y_5438_;
v___y_5357_ = v___y_5439_;
v___y_5358_ = v___x_5492_;
goto v___jp_5354_;
}
else
{
v___y_5355_ = v___y_5435_;
v___y_5356_ = v___y_5438_;
v___y_5357_ = v___y_5439_;
v___y_5358_ = v_quotient_5481_;
goto v___jp_5354_;
}
}
else
{
uint64_t v___x_5493_; 
v___x_5493_ = lean_uint64_add(v_quotient_5481_, v___x_5482_);
v___y_5355_ = v___y_5435_;
v___y_5356_ = v___y_5438_;
v___y_5357_ = v___y_5439_;
v___y_5358_ = v___x_5493_;
goto v___jp_5354_;
}
}
else
{
v___y_5355_ = v___y_5435_;
v___y_5356_ = v___y_5438_;
v___y_5357_ = v___y_5439_;
v___y_5358_ = v_quotient_5481_;
goto v___jp_5354_;
}
}
}
else
{
v___y_5355_ = v___y_5435_;
v___y_5356_ = v___y_5438_;
v___y_5357_ = v___y_5439_;
v___y_5358_ = v___y_5433_;
goto v___jp_5354_;
}
}
}
}
v___jp_5494_:
{
uint64_t v___x_5504_; uint64_t v___x_5505_; uint8_t v___x_5506_; 
v___x_5504_ = 1ULL;
v___x_5505_ = lean_uint64_shift_right(v___y_5498_, v___x_5504_);
v___x_5506_ = lean_uint64_dec_eq(v___x_5505_, v___y_5502_);
if (v___x_5506_ == 0)
{
uint64_t v___x_5507_; 
v___x_5507_ = lean_uint64_add(v___y_5503_, v___x_5504_);
v___y_5433_ = v___y_5497_;
v___y_5434_ = v___y_5496_;
v___y_5435_ = v___y_5495_;
v___y_5436_ = v___y_5499_;
v___y_5437_ = v___y_5500_;
v___y_5438_ = v___y_5501_;
v___y_5439_ = v___y_5502_;
v___y_5440_ = v___x_5507_;
goto v___jp_5432_;
}
else
{
v___y_5433_ = v___y_5497_;
v___y_5434_ = v___y_5496_;
v___y_5435_ = v___y_5495_;
v___y_5436_ = v___y_5499_;
v___y_5437_ = v___y_5500_;
v___y_5438_ = v___y_5501_;
v___y_5439_ = v___y_5502_;
v___y_5440_ = v___y_5503_;
goto v___jp_5432_;
}
}
v___jp_5508_:
{
uint64_t v___x_5520_; uint8_t v___x_5521_; 
v___x_5520_ = lean_uint64_shift_right(v___y_5515_, v___y_5514_);
v___x_5521_ = lean_uint64_dec_eq(v___x_5520_, v___y_5518_);
if (v___x_5521_ == 0)
{
uint64_t v___x_5522_; 
v___x_5522_ = lean_uint64_add(v___y_5516_, v___y_5514_);
v___y_5495_ = v___y_5511_;
v___y_5496_ = v___y_5510_;
v___y_5497_ = v___y_5509_;
v___y_5498_ = v___y_5519_;
v___y_5499_ = v___y_5512_;
v___y_5500_ = v___y_5513_;
v___y_5501_ = v___y_5517_;
v___y_5502_ = v___y_5518_;
v___y_5503_ = v___x_5522_;
goto v___jp_5494_;
}
else
{
v___y_5495_ = v___y_5511_;
v___y_5496_ = v___y_5510_;
v___y_5497_ = v___y_5509_;
v___y_5498_ = v___y_5519_;
v___y_5499_ = v___y_5512_;
v___y_5500_ = v___y_5513_;
v___y_5501_ = v___y_5517_;
v___y_5502_ = v___y_5518_;
v___y_5503_ = v___y_5516_;
goto v___jp_5494_;
}
}
v___jp_5523_:
{
uint64_t v___x_5533_; uint64_t v___x_5534_; uint8_t v___x_5535_; 
v___x_5533_ = 2ULL;
v___x_5534_ = lean_uint64_shift_right(v___y_5529_, v___x_5533_);
v___x_5535_ = lean_uint64_dec_eq(v___x_5534_, v___y_5531_);
if (v___x_5535_ == 0)
{
v___y_5509_ = v___y_5526_;
v___y_5510_ = v___y_5525_;
v___y_5511_ = v___y_5524_;
v___y_5512_ = v___y_5527_;
v___y_5513_ = v___y_5528_;
v___y_5514_ = v___x_5533_;
v___y_5515_ = v___y_5529_;
v___y_5516_ = v___y_5532_;
v___y_5517_ = v___y_5530_;
v___y_5518_ = v___y_5531_;
v___y_5519_ = v___x_5534_;
goto v___jp_5508_;
}
else
{
v___y_5509_ = v___y_5526_;
v___y_5510_ = v___y_5525_;
v___y_5511_ = v___y_5524_;
v___y_5512_ = v___y_5527_;
v___y_5513_ = v___y_5528_;
v___y_5514_ = v___x_5533_;
v___y_5515_ = v___y_5529_;
v___y_5516_ = v___y_5532_;
v___y_5517_ = v___y_5530_;
v___y_5518_ = v___y_5531_;
v___y_5519_ = v___y_5529_;
goto v___jp_5508_;
}
}
v___jp_5536_:
{
uint64_t v___x_5548_; uint8_t v___x_5549_; 
v___x_5548_ = lean_uint64_shift_right(v___y_5537_, v___y_5543_);
v___x_5549_ = lean_uint64_dec_eq(v___x_5548_, v___y_5546_);
if (v___x_5549_ == 0)
{
uint64_t v___x_5550_; 
v___x_5550_ = lean_uint64_add(v___y_5545_, v___y_5543_);
v___y_5524_ = v___y_5540_;
v___y_5525_ = v___y_5539_;
v___y_5526_ = v___y_5538_;
v___y_5527_ = v___y_5541_;
v___y_5528_ = v___y_5542_;
v___y_5529_ = v___y_5547_;
v___y_5530_ = v___y_5544_;
v___y_5531_ = v___y_5546_;
v___y_5532_ = v___x_5550_;
goto v___jp_5523_;
}
else
{
v___y_5524_ = v___y_5540_;
v___y_5525_ = v___y_5539_;
v___y_5526_ = v___y_5538_;
v___y_5527_ = v___y_5541_;
v___y_5528_ = v___y_5542_;
v___y_5529_ = v___y_5547_;
v___y_5530_ = v___y_5544_;
v___y_5531_ = v___y_5546_;
v___y_5532_ = v___y_5545_;
goto v___jp_5523_;
}
}
v___jp_5551_:
{
uint64_t v___x_5561_; uint64_t v___x_5562_; uint8_t v___x_5563_; 
v___x_5561_ = 4ULL;
v___x_5562_ = lean_uint64_shift_right(v___y_5552_, v___x_5561_);
v___x_5563_ = lean_uint64_dec_eq(v___x_5562_, v___y_5559_);
if (v___x_5563_ == 0)
{
v___y_5537_ = v___y_5552_;
v___y_5538_ = v___y_5555_;
v___y_5539_ = v___y_5554_;
v___y_5540_ = v___y_5553_;
v___y_5541_ = v___y_5556_;
v___y_5542_ = v___y_5557_;
v___y_5543_ = v___x_5561_;
v___y_5544_ = v___y_5558_;
v___y_5545_ = v___y_5560_;
v___y_5546_ = v___y_5559_;
v___y_5547_ = v___x_5562_;
goto v___jp_5536_;
}
else
{
v___y_5537_ = v___y_5552_;
v___y_5538_ = v___y_5555_;
v___y_5539_ = v___y_5554_;
v___y_5540_ = v___y_5553_;
v___y_5541_ = v___y_5556_;
v___y_5542_ = v___y_5557_;
v___y_5543_ = v___x_5561_;
v___y_5544_ = v___y_5558_;
v___y_5545_ = v___y_5560_;
v___y_5546_ = v___y_5559_;
v___y_5547_ = v___y_5552_;
goto v___jp_5536_;
}
}
v___jp_5564_:
{
uint64_t v___x_5576_; uint8_t v___x_5577_; 
v___x_5576_ = lean_uint64_shift_right(v___y_5573_, v___y_5568_);
v___x_5577_ = lean_uint64_dec_eq(v___x_5576_, v___y_5574_);
if (v___x_5577_ == 0)
{
uint64_t v___x_5578_; 
v___x_5578_ = lean_uint64_add(v___y_5571_, v___y_5568_);
v___y_5552_ = v___y_5575_;
v___y_5553_ = v___y_5567_;
v___y_5554_ = v___y_5566_;
v___y_5555_ = v___y_5565_;
v___y_5556_ = v___y_5569_;
v___y_5557_ = v___y_5570_;
v___y_5558_ = v___y_5572_;
v___y_5559_ = v___y_5574_;
v___y_5560_ = v___x_5578_;
goto v___jp_5551_;
}
else
{
v___y_5552_ = v___y_5575_;
v___y_5553_ = v___y_5567_;
v___y_5554_ = v___y_5566_;
v___y_5555_ = v___y_5565_;
v___y_5556_ = v___y_5569_;
v___y_5557_ = v___y_5570_;
v___y_5558_ = v___y_5572_;
v___y_5559_ = v___y_5574_;
v___y_5560_ = v___y_5571_;
goto v___jp_5551_;
}
}
v___jp_5579_:
{
uint64_t v___x_5589_; uint64_t v___x_5590_; uint8_t v___x_5591_; 
v___x_5589_ = 8ULL;
v___x_5590_ = lean_uint64_shift_right(v___y_5587_, v___x_5589_);
v___x_5591_ = lean_uint64_dec_eq(v___x_5590_, v___y_5586_);
if (v___x_5591_ == 0)
{
v___y_5565_ = v___y_5582_;
v___y_5566_ = v___y_5581_;
v___y_5567_ = v___y_5580_;
v___y_5568_ = v___x_5589_;
v___y_5569_ = v___y_5583_;
v___y_5570_ = v___y_5584_;
v___y_5571_ = v___y_5588_;
v___y_5572_ = v___y_5585_;
v___y_5573_ = v___y_5587_;
v___y_5574_ = v___y_5586_;
v___y_5575_ = v___x_5590_;
goto v___jp_5564_;
}
else
{
v___y_5565_ = v___y_5582_;
v___y_5566_ = v___y_5581_;
v___y_5567_ = v___y_5580_;
v___y_5568_ = v___x_5589_;
v___y_5569_ = v___y_5583_;
v___y_5570_ = v___y_5584_;
v___y_5571_ = v___y_5588_;
v___y_5572_ = v___y_5585_;
v___y_5573_ = v___y_5587_;
v___y_5574_ = v___y_5586_;
v___y_5575_ = v___y_5587_;
goto v___jp_5564_;
}
}
v___jp_5592_:
{
uint64_t v___x_5604_; uint8_t v___x_5605_; 
v___x_5604_ = lean_uint64_shift_right(v___y_5599_, v___y_5596_);
v___x_5605_ = lean_uint64_dec_eq(v___x_5604_, v___y_5602_);
if (v___x_5605_ == 0)
{
uint64_t v___x_5606_; 
v___x_5606_ = lean_uint64_add(v___y_5600_, v___y_5596_);
v___y_5580_ = v___y_5595_;
v___y_5581_ = v___y_5594_;
v___y_5582_ = v___y_5593_;
v___y_5583_ = v___y_5597_;
v___y_5584_ = v___y_5598_;
v___y_5585_ = v___y_5601_;
v___y_5586_ = v___y_5602_;
v___y_5587_ = v___y_5603_;
v___y_5588_ = v___x_5606_;
goto v___jp_5579_;
}
else
{
v___y_5580_ = v___y_5595_;
v___y_5581_ = v___y_5594_;
v___y_5582_ = v___y_5593_;
v___y_5583_ = v___y_5597_;
v___y_5584_ = v___y_5598_;
v___y_5585_ = v___y_5601_;
v___y_5586_ = v___y_5602_;
v___y_5587_ = v___y_5603_;
v___y_5588_ = v___y_5600_;
goto v___jp_5579_;
}
}
v___jp_5607_:
{
uint64_t v___x_5617_; uint64_t v___x_5618_; uint8_t v___x_5619_; 
v___x_5617_ = 16ULL;
v___x_5618_ = lean_uint64_shift_right(v___y_5613_, v___x_5617_);
v___x_5619_ = lean_uint64_dec_eq(v___x_5618_, v___y_5615_);
if (v___x_5619_ == 0)
{
v___y_5593_ = v___y_5610_;
v___y_5594_ = v___y_5609_;
v___y_5595_ = v___y_5608_;
v___y_5596_ = v___x_5617_;
v___y_5597_ = v___y_5611_;
v___y_5598_ = v___y_5612_;
v___y_5599_ = v___y_5613_;
v___y_5600_ = v___y_5616_;
v___y_5601_ = v___y_5614_;
v___y_5602_ = v___y_5615_;
v___y_5603_ = v___x_5618_;
goto v___jp_5592_;
}
else
{
v___y_5593_ = v___y_5610_;
v___y_5594_ = v___y_5609_;
v___y_5595_ = v___y_5608_;
v___y_5596_ = v___x_5617_;
v___y_5597_ = v___y_5611_;
v___y_5598_ = v___y_5612_;
v___y_5599_ = v___y_5613_;
v___y_5600_ = v___y_5616_;
v___y_5601_ = v___y_5614_;
v___y_5602_ = v___y_5615_;
v___y_5603_ = v___y_5613_;
goto v___jp_5592_;
}
}
v___jp_5620_:
{
uint64_t v___x_5630_; uint8_t v___x_5631_; 
v___x_5630_ = lean_uint64_shift_right(v___y_5621_, v___y_5626_);
v___x_5631_ = lean_uint64_dec_eq(v___x_5630_, v___y_5628_);
if (v___x_5631_ == 0)
{
v___y_5608_ = v___y_5623_;
v___y_5609_ = v___y_5622_;
v___y_5610_ = v___y_5621_;
v___y_5611_ = v___y_5624_;
v___y_5612_ = v___y_5625_;
v___y_5613_ = v___y_5629_;
v___y_5614_ = v___y_5627_;
v___y_5615_ = v___y_5628_;
v___y_5616_ = v___y_5626_;
goto v___jp_5607_;
}
else
{
v___y_5608_ = v___y_5623_;
v___y_5609_ = v___y_5622_;
v___y_5610_ = v___y_5621_;
v___y_5611_ = v___y_5624_;
v___y_5612_ = v___y_5625_;
v___y_5613_ = v___y_5629_;
v___y_5614_ = v___y_5627_;
v___y_5615_ = v___y_5628_;
v___y_5616_ = v___y_5628_;
goto v___jp_5607_;
}
}
v___jp_5632_:
{
uint64_t v___x_5639_; uint8_t v___x_5640_; 
v___x_5639_ = 0ULL;
v___x_5640_ = lean_uint64_dec_eq(v___y_5634_, v___x_5639_);
if (v___x_5640_ == 0)
{
uint64_t v___x_5641_; uint64_t v___x_5642_; uint8_t v___x_5643_; 
v___x_5641_ = 32ULL;
v___x_5642_ = lean_uint64_shift_right(v___y_5634_, v___x_5641_);
v___x_5643_ = lean_uint64_dec_eq(v___x_5642_, v___x_5639_);
if (v___x_5643_ == 0)
{
v___y_5621_ = v___y_5634_;
v___y_5622_ = v___y_5633_;
v___y_5623_ = v___y_5635_;
v___y_5624_ = v___y_5636_;
v___y_5625_ = v___y_5637_;
v___y_5626_ = v___x_5641_;
v___y_5627_ = v___y_5638_;
v___y_5628_ = v___x_5639_;
v___y_5629_ = v___x_5642_;
goto v___jp_5620_;
}
else
{
v___y_5621_ = v___y_5634_;
v___y_5622_ = v___y_5633_;
v___y_5623_ = v___y_5635_;
v___y_5624_ = v___y_5636_;
v___y_5625_ = v___y_5637_;
v___y_5626_ = v___x_5641_;
v___y_5627_ = v___y_5638_;
v___y_5628_ = v___x_5639_;
v___y_5629_ = v___y_5634_;
goto v___jp_5620_;
}
}
else
{
if (v___y_5638_ == 0)
{
uint32_t v___x_5644_; 
v___x_5644_ = 0;
v___y_5322_ = v___x_5644_;
goto v___jp_5321_;
}
else
{
uint32_t v___x_5645_; 
v___x_5645_ = 2147483648;
v___y_5322_ = v___x_5645_;
goto v___jp_5321_;
}
}
}
v___jp_5646_:
{
uint32_t v___x_5650_; uint32_t v___x_5651_; 
v___x_5650_ = lean_uint32_land(v___y_5648_, v___y_5647_);
v___x_5651_ = lean_uint32_lor(v___y_5649_, v___x_5650_);
v___y_5322_ = v___x_5651_;
goto v___jp_5321_;
}
v___jp_5652_:
{
uint8_t v___x_5657_; 
v___x_5657_ = lean_uint64_dec_eq(v___y_5656_, v___y_5654_);
if (v___x_5657_ == 0)
{
uint64_t v___x_5658_; uint8_t v___x_5659_; 
v___x_5658_ = 8388608ULL;
v___x_5659_ = lean_uint64_dec_eq(v___y_5656_, v___x_5658_);
if (v___x_5659_ == 0)
{
uint32_t v___x_5660_; 
v___x_5660_ = lean_uint64_to_uint32(v___y_5656_);
if (v___y_5655_ == 0)
{
uint32_t v___x_5661_; 
v___x_5661_ = 0;
v___y_5647_ = v___y_5653_;
v___y_5648_ = v___x_5660_;
v___y_5649_ = v___x_5661_;
goto v___jp_5646_;
}
else
{
uint32_t v___x_5662_; 
v___x_5662_ = 2147483648;
v___y_5647_ = v___y_5653_;
v___y_5648_ = v___x_5660_;
v___y_5649_ = v___x_5662_;
goto v___jp_5646_;
}
}
else
{
if (v___y_5655_ == 0)
{
uint32_t v___x_5663_; 
v___x_5663_ = 0;
v___y_5345_ = v___x_5663_;
goto v___jp_5344_;
}
else
{
uint32_t v___x_5664_; 
v___x_5664_ = 2147483648;
v___y_5345_ = v___x_5664_;
goto v___jp_5344_;
}
}
}
else
{
if (v___y_5655_ == 0)
{
uint32_t v___x_5665_; 
v___x_5665_ = 0;
v___y_5322_ = v___x_5665_;
goto v___jp_5321_;
}
else
{
uint32_t v___x_5666_; 
v___x_5666_ = 2147483648;
v___y_5322_ = v___x_5666_;
goto v___jp_5321_;
}
}
}
v___jp_5667_:
{
uint64_t v___x_5676_; uint64_t v___x_5677_; uint64_t v___x_5678_; uint8_t v___x_5679_; 
v___x_5676_ = lean_uint64_mul(v___y_5672_, v___y_5671_);
v___x_5677_ = lean_uint64_add(v___y_5673_, v___y_5675_);
v___x_5678_ = 281474976710656ULL;
v___x_5679_ = lean_uint64_dec_lt(v___x_5676_, v___x_5678_);
if (v___x_5679_ == 0)
{
v___y_5633_ = v___y_5669_;
v___y_5634_ = v___x_5676_;
v___y_5635_ = v___y_5668_;
v___y_5636_ = v___x_5677_;
v___y_5637_ = v___y_5670_;
v___y_5638_ = v___y_5674_;
goto v___jp_5632_;
}
else
{
uint64_t v___x_5680_; uint8_t v___x_5681_; 
v___x_5680_ = 123ULL;
v___x_5681_ = lean_uint64_dec_le(v___x_5677_, v___x_5680_);
if (v___x_5681_ == 0)
{
v___y_5633_ = v___y_5669_;
v___y_5634_ = v___x_5676_;
v___y_5635_ = v___y_5668_;
v___y_5636_ = v___x_5677_;
v___y_5637_ = v___y_5670_;
v___y_5638_ = v___y_5674_;
goto v___jp_5632_;
}
else
{
uint64_t v___x_5682_; uint8_t v___x_5683_; 
v___x_5682_ = 0ULL;
v___x_5683_ = lean_uint64_dec_eq(v___x_5676_, v___x_5682_);
if (v___x_5683_ == 0)
{
uint64_t v___x_5684_; uint64_t v___x_5685_; uint8_t v___x_5686_; 
v___x_5684_ = 149ULL;
v___x_5685_ = lean_uint64_sub(v___x_5684_, v___x_5677_);
v___x_5686_ = lean_uint64_dec_eq(v___x_5685_, v___x_5682_);
if (v___x_5686_ == 0)
{
uint64_t v___x_5687_; uint8_t v___x_5688_; 
v___x_5687_ = 64ULL;
v___x_5688_ = lean_uint64_dec_lt(v___x_5685_, v___x_5687_);
if (v___x_5688_ == 0)
{
uint8_t v___x_5689_; 
v___x_5689_ = lean_uint64_dec_eq(v___x_5685_, v___x_5687_);
if (v___x_5689_ == 0)
{
v___y_5653_ = v___y_5668_;
v___y_5654_ = v___x_5682_;
v___y_5655_ = v___y_5674_;
v___y_5656_ = v___x_5682_;
goto v___jp_5652_;
}
else
{
uint64_t v___x_5690_; uint8_t v___x_5691_; 
v___x_5690_ = 9223372036854775808ULL;
v___x_5691_ = lean_uint64_dec_lt(v___x_5690_, v___x_5676_);
if (v___x_5691_ == 0)
{
v___y_5653_ = v___y_5668_;
v___y_5654_ = v___x_5682_;
v___y_5655_ = v___y_5674_;
v___y_5656_ = v___x_5682_;
goto v___jp_5652_;
}
else
{
uint64_t v___x_5692_; 
v___x_5692_ = 1ULL;
v___y_5653_ = v___y_5668_;
v___y_5654_ = v___x_5682_;
v___y_5655_ = v___y_5674_;
v___y_5656_ = v___x_5692_;
goto v___jp_5652_;
}
}
}
else
{
uint64_t v_quotient_5693_; uint64_t v___x_5694_; uint64_t v___x_5695_; uint64_t v___x_5696_; uint64_t v_remainder_5697_; uint64_t v___x_5698_; uint64_t v_half_5699_; uint8_t v___x_5700_; 
v_quotient_5693_ = lean_uint64_shift_right(v___x_5676_, v___x_5685_);
v___x_5694_ = 1ULL;
v___x_5695_ = lean_uint64_shift_left(v___x_5694_, v___x_5685_);
v___x_5696_ = lean_uint64_sub(v___x_5695_, v___x_5694_);
v_remainder_5697_ = lean_uint64_land(v___x_5676_, v___x_5696_);
v___x_5698_ = lean_uint64_sub(v___x_5685_, v___x_5694_);
v_half_5699_ = lean_uint64_shift_left(v___x_5694_, v___x_5698_);
v___x_5700_ = lean_uint64_dec_lt(v_remainder_5697_, v_half_5699_);
if (v___x_5700_ == 0)
{
uint8_t v___x_5701_; 
v___x_5701_ = lean_uint64_dec_lt(v_half_5699_, v_remainder_5697_);
if (v___x_5701_ == 0)
{
uint64_t v___x_5702_; uint8_t v___x_5703_; 
v___x_5702_ = lean_uint64_land(v_quotient_5693_, v___x_5694_);
v___x_5703_ = lean_uint64_dec_eq(v___x_5702_, v___x_5682_);
if (v___x_5703_ == 0)
{
uint64_t v___x_5704_; 
v___x_5704_ = lean_uint64_add(v_quotient_5693_, v___x_5694_);
v___y_5653_ = v___y_5668_;
v___y_5654_ = v___x_5682_;
v___y_5655_ = v___y_5674_;
v___y_5656_ = v___x_5704_;
goto v___jp_5652_;
}
else
{
v___y_5653_ = v___y_5668_;
v___y_5654_ = v___x_5682_;
v___y_5655_ = v___y_5674_;
v___y_5656_ = v_quotient_5693_;
goto v___jp_5652_;
}
}
else
{
uint64_t v___x_5705_; 
v___x_5705_ = lean_uint64_add(v_quotient_5693_, v___x_5694_);
v___y_5653_ = v___y_5668_;
v___y_5654_ = v___x_5682_;
v___y_5655_ = v___y_5674_;
v___y_5656_ = v___x_5705_;
goto v___jp_5652_;
}
}
else
{
v___y_5653_ = v___y_5668_;
v___y_5654_ = v___x_5682_;
v___y_5655_ = v___y_5674_;
v___y_5656_ = v_quotient_5693_;
goto v___jp_5652_;
}
}
}
else
{
v___y_5653_ = v___y_5668_;
v___y_5654_ = v___x_5682_;
v___y_5655_ = v___y_5674_;
v___y_5656_ = v___x_5676_;
goto v___jp_5652_;
}
}
else
{
if (v___y_5674_ == 0)
{
uint32_t v___x_5706_; 
v___x_5706_ = 0;
v___y_5322_ = v___x_5706_;
goto v___jp_5321_;
}
else
{
uint32_t v___x_5707_; 
v___x_5707_ = 2147483648;
v___y_5322_ = v___x_5707_;
goto v___jp_5321_;
}
}
}
}
}
v___jp_5708_:
{
uint64_t v___x_5717_; uint64_t v___x_5718_; uint8_t v___x_5719_; 
v___x_5717_ = lean_uint32_to_uint64(v___y_5713_);
v___x_5718_ = 0ULL;
v___x_5719_ = lean_uint64_dec_eq(v___x_5717_, v___x_5718_);
if (v___x_5719_ == 0)
{
uint64_t v___x_5720_; uint64_t v___x_5721_; 
v___x_5720_ = 1ULL;
v___x_5721_ = lean_uint64_sub(v___x_5717_, v___x_5720_);
v___y_5668_ = v___y_5710_;
v___y_5669_ = v___y_5709_;
v___y_5670_ = v___y_5711_;
v___y_5671_ = v___y_5712_;
v___y_5672_ = v___y_5714_;
v___y_5673_ = v___y_5716_;
v___y_5674_ = v___y_5715_;
v___y_5675_ = v___x_5721_;
goto v___jp_5667_;
}
else
{
v___y_5668_ = v___y_5710_;
v___y_5669_ = v___y_5709_;
v___y_5670_ = v___y_5711_;
v___y_5671_ = v___y_5712_;
v___y_5672_ = v___y_5714_;
v___y_5673_ = v___y_5716_;
v___y_5674_ = v___y_5715_;
v___y_5675_ = v___x_5718_;
goto v___jp_5667_;
}
}
v___jp_5722_:
{
uint64_t v___x_5731_; uint64_t v___x_5732_; uint8_t v___x_5733_; 
v___x_5731_ = lean_uint32_to_uint64(v___y_5726_);
v___x_5732_ = 0ULL;
v___x_5733_ = lean_uint64_dec_eq(v___x_5731_, v___x_5732_);
if (v___x_5733_ == 0)
{
uint64_t v___x_5734_; uint64_t v___x_5735_; 
v___x_5734_ = 1ULL;
v___x_5735_ = lean_uint64_sub(v___x_5731_, v___x_5734_);
v___y_5709_ = v___y_5724_;
v___y_5710_ = v___y_5723_;
v___y_5711_ = v___y_5725_;
v___y_5712_ = v___y_5730_;
v___y_5713_ = v___y_5728_;
v___y_5714_ = v___y_5727_;
v___y_5715_ = v___y_5729_;
v___y_5716_ = v___x_5735_;
goto v___jp_5708_;
}
else
{
v___y_5709_ = v___y_5724_;
v___y_5710_ = v___y_5723_;
v___y_5711_ = v___y_5725_;
v___y_5712_ = v___y_5730_;
v___y_5713_ = v___y_5728_;
v___y_5714_ = v___y_5727_;
v___y_5715_ = v___y_5729_;
v___y_5716_ = v___x_5732_;
goto v___jp_5708_;
}
}
v___jp_5736_:
{
uint32_t v___x_5745_; uint8_t v___x_5746_; 
v___x_5745_ = 0;
v___x_5746_ = lean_uint32_dec_eq(v___y_5742_, v___x_5745_);
if (v___x_5746_ == 0)
{
uint64_t v___x_5747_; uint64_t v___x_5748_; uint64_t v___x_5749_; 
v___x_5747_ = lean_uint32_to_uint64(v___y_5737_);
v___x_5748_ = 8388608ULL;
v___x_5749_ = lean_uint64_lor(v___x_5747_, v___x_5748_);
v___y_5723_ = v___y_5739_;
v___y_5724_ = v___y_5738_;
v___y_5725_ = v___y_5740_;
v___y_5726_ = v___y_5741_;
v___y_5727_ = v___y_5744_;
v___y_5728_ = v___y_5742_;
v___y_5729_ = v___y_5743_;
v___y_5730_ = v___x_5749_;
goto v___jp_5722_;
}
else
{
uint64_t v___x_5750_; 
v___x_5750_ = lean_uint32_to_uint64(v___y_5737_);
v___y_5723_ = v___y_5739_;
v___y_5724_ = v___y_5738_;
v___y_5725_ = v___y_5740_;
v___y_5726_ = v___y_5741_;
v___y_5727_ = v___y_5744_;
v___y_5728_ = v___y_5742_;
v___y_5729_ = v___y_5743_;
v___y_5730_ = v___x_5750_;
goto v___jp_5722_;
}
}
v___jp_5751_:
{
uint32_t v___x_5759_; uint32_t v_xFraction_5760_; uint32_t v_yFraction_5761_; uint32_t v___x_5762_; uint8_t v___x_5763_; 
v___x_5759_ = 8388607;
v_xFraction_5760_ = lean_uint32_land(v___y_5753_, v___x_5759_);
v_yFraction_5761_ = lean_uint32_land(v___y_5757_, v___x_5759_);
v___x_5762_ = 0;
v___x_5763_ = lean_uint32_dec_eq(v___y_5755_, v___x_5762_);
if (v___x_5763_ == 0)
{
uint64_t v___x_5764_; uint64_t v___x_5765_; uint64_t v___x_5766_; 
v___x_5764_ = lean_uint32_to_uint64(v_xFraction_5760_);
v___x_5765_ = 8388608ULL;
v___x_5766_ = lean_uint64_lor(v___x_5764_, v___x_5765_);
v___y_5737_ = v_yFraction_5761_;
v___y_5738_ = v___y_5752_;
v___y_5739_ = v___x_5759_;
v___y_5740_ = v___y_5754_;
v___y_5741_ = v___y_5755_;
v___y_5742_ = v___y_5756_;
v___y_5743_ = v___y_5758_;
v___y_5744_ = v___x_5766_;
goto v___jp_5736_;
}
else
{
uint64_t v___x_5767_; 
v___x_5767_ = lean_uint32_to_uint64(v_xFraction_5760_);
v___y_5737_ = v_yFraction_5761_;
v___y_5738_ = v___y_5752_;
v___y_5739_ = v___x_5759_;
v___y_5740_ = v___y_5754_;
v___y_5741_ = v___y_5755_;
v___y_5742_ = v___y_5756_;
v___y_5743_ = v___y_5758_;
v___y_5744_ = v___x_5767_;
goto v___jp_5736_;
}
}
v___jp_5768_:
{
float v___x_5771_; float v___x_5772_; float v___x_5773_; uint32_t v___x_5774_; 
v___x_5771_ = lean_float32_of_bits(v___y_5769_);
v___x_5772_ = lean_float32_of_bits(v___y_5770_);
v___x_5773_ = lean_float32_mul(v___x_5771_, v___x_5772_);
v___x_5774_ = lean_float32_to_bits(v___x_5773_);
v___y_5322_ = v___x_5774_;
goto v___jp_5321_;
}
v___jp_5775_:
{
if (v___y_5781_ == 0)
{
uint32_t v___x_5782_; 
v___x_5782_ = lp_competition_Submission_FastMul_mul(v___y_5777_, v___y_5779_);
v___y_5322_ = v___x_5782_;
goto v___jp_5321_;
}
else
{
uint8_t v___x_5783_; 
v___x_5783_ = lean_uint32_dec_eq(v___y_5778_, v___y_5776_);
if (v___x_5783_ == 0)
{
v___y_5769_ = v___y_5777_;
v___y_5770_ = v___y_5779_;
goto v___jp_5768_;
}
else
{
if (v___y_5780_ == 0)
{
uint32_t v___x_5784_; 
v___x_5784_ = lp_competition_Submission_FastMul_mul(v___y_5777_, v___y_5779_);
v___y_5322_ = v___x_5784_;
goto v___jp_5321_;
}
else
{
v___y_5769_ = v___y_5777_;
v___y_5770_ = v___y_5779_;
goto v___jp_5768_;
}
}
}
}
v___jp_5785_:
{
if (v___y_5793_ == 0)
{
v___y_5752_ = v___y_5786_;
v___y_5753_ = v___y_5787_;
v___y_5754_ = v___y_5788_;
v___y_5755_ = v___y_5789_;
v___y_5756_ = v___y_5791_;
v___y_5757_ = v___y_5790_;
v___y_5758_ = v___x_5320_;
goto v___jp_5751_;
}
else
{
v___y_5752_ = v___y_5786_;
v___y_5753_ = v___y_5787_;
v___y_5754_ = v___y_5788_;
v___y_5755_ = v___y_5789_;
v___y_5756_ = v___y_5791_;
v___y_5757_ = v___y_5790_;
v___y_5758_ = v___y_5792_;
goto v___jp_5751_;
}
}
v___jp_5794_:
{
if (v___y_5797_ == 0)
{
if (v___y_5803_ == 0)
{
v___y_5786_ = v___y_5795_;
v___y_5787_ = v___y_5796_;
v___y_5788_ = v___y_5798_;
v___y_5789_ = v___y_5799_;
v___y_5790_ = v___y_5801_;
v___y_5791_ = v___y_5800_;
v___y_5792_ = v___y_5802_;
v___y_5793_ = v___x_5320_;
goto v___jp_5785_;
}
else
{
v___y_5752_ = v___y_5795_;
v___y_5753_ = v___y_5796_;
v___y_5754_ = v___y_5798_;
v___y_5755_ = v___y_5799_;
v___y_5756_ = v___y_5800_;
v___y_5757_ = v___y_5801_;
v___y_5758_ = v___x_5320_;
goto v___jp_5751_;
}
}
else
{
v___y_5786_ = v___y_5795_;
v___y_5787_ = v___y_5796_;
v___y_5788_ = v___y_5798_;
v___y_5789_ = v___y_5799_;
v___y_5790_ = v___y_5801_;
v___y_5791_ = v___y_5800_;
v___y_5792_ = v___y_5802_;
v___y_5793_ = v___y_5803_;
goto v___jp_5785_;
}
}
v___jp_5804_:
{
uint32_t v___x_5813_; uint32_t v___x_5814_; uint32_t v___x_5815_; uint8_t v___x_5816_; 
v___x_5813_ = 2147483648;
v___x_5814_ = lean_uint32_land(v___y_5809_, v___x_5813_);
v___x_5815_ = 0;
v___x_5816_ = lean_uint32_dec_eq(v___x_5814_, v___x_5815_);
if (v___x_5816_ == 0)
{
v___y_5795_ = v___y_5805_;
v___y_5796_ = v___y_5806_;
v___y_5797_ = v___y_5812_;
v___y_5798_ = v___y_5807_;
v___y_5799_ = v___y_5808_;
v___y_5800_ = v___y_5810_;
v___y_5801_ = v___y_5809_;
v___y_5802_ = v___y_5811_;
v___y_5803_ = v___x_5320_;
goto v___jp_5794_;
}
else
{
v___y_5795_ = v___y_5805_;
v___y_5796_ = v___y_5806_;
v___y_5797_ = v___y_5812_;
v___y_5798_ = v___y_5807_;
v___y_5799_ = v___y_5808_;
v___y_5800_ = v___y_5810_;
v___y_5801_ = v___y_5809_;
v___y_5802_ = v___y_5811_;
v___y_5803_ = v___y_5811_;
goto v___jp_5794_;
}
}
v___jp_5817_:
{
if (v___y_5824_ == 0)
{
uint32_t v___x_5825_; uint32_t v___x_5826_; uint32_t v___x_5827_; uint8_t v___x_5828_; 
v___x_5825_ = 2147483648;
v___x_5826_ = lean_uint32_land(v___y_5819_, v___x_5825_);
v___x_5827_ = 0;
v___x_5828_ = lean_uint32_dec_eq(v___x_5826_, v___x_5827_);
if (v___x_5828_ == 0)
{
v___y_5805_ = v___y_5818_;
v___y_5806_ = v___y_5819_;
v___y_5807_ = v___y_5820_;
v___y_5808_ = v___y_5821_;
v___y_5809_ = v___y_5823_;
v___y_5810_ = v___y_5822_;
v___y_5811_ = v___y_5824_;
v___y_5812_ = v___x_5320_;
goto v___jp_5804_;
}
else
{
v___y_5805_ = v___y_5818_;
v___y_5806_ = v___y_5819_;
v___y_5807_ = v___y_5820_;
v___y_5808_ = v___y_5821_;
v___y_5809_ = v___y_5823_;
v___y_5810_ = v___y_5822_;
v___y_5811_ = v___y_5824_;
v___y_5812_ = v___y_5824_;
goto v___jp_5804_;
}
}
else
{
lean_object* v___x_5829_; lean_object* v___x_5830_; lean_object* v___x_5831_; uint32_t v___x_5832_; 
v___x_5829_ = lean_uint32_to_nat(v___y_5819_);
v___x_5830_ = lean_uint32_to_nat(v___y_5823_);
v___x_5831_ = lp_floatlib_FloatLib_Floats_Formats_BinaryInterchange_Model_MulBackend_word___at___00FloatLib_Floats_Formats_BinaryInterchange_Configured_Plan_softwareMul32Certified_spec__1(v___x_5829_, v___x_5830_);
v___x_5832_ = lean_uint32_of_nat(v___x_5831_);
lean_dec(v___x_5831_);
v___y_5322_ = v___x_5832_;
goto v___jp_5321_;
}
}
v___jp_5833_:
{
uint32_t v___x_5836_; uint32_t v___x_5837_; uint32_t v___x_5838_; uint32_t v_ex_5839_; uint32_t v___x_5840_; uint32_t v_ey_5841_; uint32_t v___x_5842_; uint32_t v___x_5843_; uint8_t v___x_5844_; 
v___x_5836_ = 23;
v___x_5837_ = lean_uint32_shift_right(v___y_5834_, v___x_5836_);
v___x_5838_ = 255;
v_ex_5839_ = lean_uint32_land(v___x_5837_, v___x_5838_);
v___x_5840_ = lean_uint32_shift_right(v___y_5835_, v___x_5836_);
v_ey_5841_ = lean_uint32_land(v___x_5840_, v___x_5838_);
v___x_5842_ = lean_uint32_add(v_ex_5839_, v_ey_5841_);
v___x_5843_ = 128;
v___x_5844_ = lean_uint32_dec_lt(v___x_5842_, v___x_5843_);
if (v___x_5844_ == 0)
{
uint8_t v___x_5845_; 
v___x_5845_ = lean_uint32_dec_eq(v_ex_5839_, v___x_5838_);
if (v___x_5845_ == 0)
{
v___y_5776_ = v___x_5838_;
v___y_5777_ = v___y_5834_;
v___y_5778_ = v_ey_5841_;
v___y_5779_ = v___y_5835_;
v___y_5780_ = v___x_5844_;
v___y_5781_ = v___x_5320_;
goto v___jp_5775_;
}
else
{
v___y_5776_ = v___x_5838_;
v___y_5777_ = v___y_5834_;
v___y_5778_ = v_ey_5841_;
v___y_5779_ = v___y_5835_;
v___y_5780_ = v___x_5844_;
v___y_5781_ = v___x_5844_;
goto v___jp_5775_;
}
}
else
{
uint32_t v___x_5846_; uint32_t v___x_5847_; uint32_t v___x_5848_; uint8_t v___x_5849_; 
v___x_5846_ = 4278190080;
v___x_5847_ = 1;
v___x_5848_ = lean_uint32_shift_left(v___y_5834_, v___x_5847_);
v___x_5849_ = lean_uint32_dec_le(v___x_5846_, v___x_5848_);
if (v___x_5849_ == 0)
{
uint32_t v___x_5850_; uint8_t v___x_5851_; 
v___x_5850_ = lean_uint32_shift_left(v___y_5835_, v___x_5847_);
v___x_5851_ = lean_uint32_dec_le(v___x_5846_, v___x_5850_);
v___y_5818_ = v___x_5838_;
v___y_5819_ = v___y_5834_;
v___y_5820_ = v___x_5836_;
v___y_5821_ = v_ex_5839_;
v___y_5822_ = v_ey_5841_;
v___y_5823_ = v___y_5835_;
v___y_5824_ = v___x_5851_;
goto v___jp_5817_;
}
else
{
v___y_5818_ = v___x_5838_;
v___y_5819_ = v___y_5834_;
v___y_5820_ = v___x_5836_;
v___y_5821_ = v_ex_5839_;
v___y_5822_ = v_ey_5841_;
v___y_5823_ = v___y_5835_;
v___y_5824_ = v___x_5849_;
goto v___jp_5817_;
}
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_Fin_foldl_loop___at___00Submission_referenceBmm_spec__0___boxed(lean_object* v_A_5871_, lean_object* v_fst_5872_, lean_object* v_m_5873_, lean_object* v_fst_5874_, lean_object* v_n_5875_, lean_object* v_B_5876_, lean_object* v_p_5877_, lean_object* v_snd_5878_, lean_object* v_n_5879_, lean_object* v_x_5880_, lean_object* v_i_5881_){
_start:
{
uint32_t v_x_boxed_5882_; uint32_t v_res_5883_; lean_object* v_r_5884_; 
v_x_boxed_5882_ = lean_unbox_uint32(v_x_5880_);
lean_dec(v_x_5880_);
v_res_5883_ = lp_competition_Fin_foldl_loop___at___00Submission_referenceBmm_spec__0(v_A_5871_, v_fst_5872_, v_m_5873_, v_fst_5874_, v_n_5875_, v_B_5876_, v_p_5877_, v_snd_5878_, v_n_5879_, v_x_boxed_5882_, v_i_5881_);
lean_dec(v_n_5879_);
lean_dec(v_snd_5878_);
lean_dec(v_p_5877_);
lean_dec_ref(v_B_5876_);
lean_dec(v_n_5875_);
lean_dec(v_fst_5874_);
lean_dec(v_m_5873_);
lean_dec(v_fst_5872_);
lean_dec_ref(v_A_5871_);
v_r_5884_ = lean_box_uint32(v_res_5883_);
return v_r_5884_;
}
}
LEAN_EXPORT uint32_t lp_competition_Submission_referenceBmm___lam__0(lean_object* v_m_5885_, lean_object* v_p_5886_, lean_object* v_A_5887_, lean_object* v_n_5888_, lean_object* v_B_5889_, lean_object* v_q_5890_){
_start:
{
lean_object* v___x_5891_; lean_object* v_snd_5892_; lean_object* v_fst_5893_; lean_object* v_fst_5894_; lean_object* v_snd_5895_; lean_object* v___x_5896_; uint32_t v___x_5897_; uint32_t v___x_5898_; 
v___x_5891_ = lp_competition_Competition_bmmDecodeC(v_m_5885_, v_p_5886_, v_q_5890_);
v_snd_5892_ = lean_ctor_get(v___x_5891_, 1);
lean_inc(v_snd_5892_);
v_fst_5893_ = lean_ctor_get(v___x_5891_, 0);
lean_inc(v_fst_5893_);
lean_dec_ref(v___x_5891_);
v_fst_5894_ = lean_ctor_get(v_snd_5892_, 0);
lean_inc(v_fst_5894_);
v_snd_5895_ = lean_ctor_get(v_snd_5892_, 1);
lean_inc(v_snd_5895_);
lean_dec(v_snd_5892_);
v___x_5896_ = lean_unsigned_to_nat(0u);
v___x_5897_ = lean_uint32_once(&lp_competition_Submission_referenceSum___redArg___closed__1, &lp_competition_Submission_referenceSum___redArg___closed__1_once, _init_lp_competition_Submission_referenceSum___redArg___closed__1);
v___x_5898_ = lp_competition_Fin_foldl_loop___at___00Submission_referenceBmm_spec__0(v_A_5887_, v_fst_5893_, v_m_5885_, v_fst_5894_, v_n_5888_, v_B_5889_, v_p_5886_, v_snd_5895_, v_n_5888_, v___x_5897_, v___x_5896_);
lean_dec(v_snd_5895_);
lean_dec(v_fst_5894_);
lean_dec(v_fst_5893_);
return v___x_5898_;
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_referenceBmm___lam__0___boxed(lean_object* v_m_5899_, lean_object* v_p_5900_, lean_object* v_A_5901_, lean_object* v_n_5902_, lean_object* v_B_5903_, lean_object* v_q_5904_){
_start:
{
uint32_t v_res_5905_; lean_object* v_r_5906_; 
v_res_5905_ = lp_competition_Submission_referenceBmm___lam__0(v_m_5899_, v_p_5900_, v_A_5901_, v_n_5902_, v_B_5903_, v_q_5904_);
lean_dec(v_q_5904_);
lean_dec_ref(v_B_5903_);
lean_dec(v_n_5902_);
lean_dec_ref(v_A_5901_);
lean_dec(v_p_5900_);
lean_dec(v_m_5899_);
v_r_5906_ = lean_box_uint32(v_res_5905_);
return v_r_5906_;
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_referenceBmm(lean_object* v_batch_5907_, lean_object* v_m_5908_, lean_object* v_n_5909_, lean_object* v_p_5910_, lean_object* v_A_5911_, lean_object* v_B_5912_){
_start:
{
lean_object* v___f_5913_; lean_object* v___x_5914_; lean_object* v___x_5915_; lean_object* v___x_5916_; 
lean_inc(v_p_5910_);
lean_inc(v_m_5908_);
v___f_5913_ = lean_alloc_closure((void*)(lp_competition_Submission_referenceBmm___lam__0___boxed), 6, 5);
lean_closure_set(v___f_5913_, 0, v_m_5908_);
lean_closure_set(v___f_5913_, 1, v_p_5910_);
lean_closure_set(v___f_5913_, 2, v_A_5911_);
lean_closure_set(v___f_5913_, 3, v_n_5909_);
lean_closure_set(v___f_5913_, 4, v_B_5912_);
v___x_5914_ = lean_nat_mul(v_batch_5907_, v_m_5908_);
lean_dec(v_m_5908_);
v___x_5915_ = lean_nat_mul(v___x_5914_, v_p_5910_);
lean_dec(v_p_5910_);
lean_dec(v___x_5914_);
v___x_5916_ = l_Array_ofFn___redArg(v___x_5915_, v___f_5913_);
return v___x_5916_;
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_referenceBmm___boxed(lean_object* v_batch_5917_, lean_object* v_m_5918_, lean_object* v_n_5919_, lean_object* v_p_5920_, lean_object* v_A_5921_, lean_object* v_B_5922_){
_start:
{
lean_object* v_res_5923_; 
v_res_5923_ = lp_competition_Submission_referenceBmm(v_batch_5917_, v_m_5918_, v_n_5919_, v_p_5920_, v_A_5921_, v_B_5922_);
lean_dec(v_batch_5917_);
return v_res_5923_;
}
}
LEAN_EXPORT float lp_competition_Submission_NativeFinal_sumLoop(lean_object* v_n_5924_, lean_object* v_x_5925_, lean_object* v_k_5926_, float v_acc_5927_){
_start:
{
uint8_t v___x_5928_; 
v___x_5928_ = lean_nat_dec_lt(v_k_5926_, v_n_5924_);
if (v___x_5928_ == 0)
{
lean_dec(v_k_5926_);
return v_acc_5927_;
}
else
{
lean_object* v___x_5929_; lean_object* v___x_5930_; lean_object* v___x_5931_; uint32_t v___x_5932_; float v___x_5933_; float v___x_5934_; 
v___x_5929_ = lean_unsigned_to_nat(1u);
v___x_5930_ = lean_nat_add(v_k_5926_, v___x_5929_);
v___x_5931_ = lean_array_fget_borrowed(v_x_5925_, v_k_5926_);
lean_dec(v_k_5926_);
v___x_5932_ = lean_unbox_uint32(v___x_5931_);
v___x_5933_ = lean_float32_of_bits(v___x_5932_);
v___x_5934_ = lean_float32_add(v_acc_5927_, v___x_5933_);
v_k_5926_ = v___x_5930_;
v_acc_5927_ = v___x_5934_;
goto _start;
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_NativeFinal_sumLoop___boxed(lean_object* v_n_5936_, lean_object* v_x_5937_, lean_object* v_k_5938_, lean_object* v_acc_5939_){
_start:
{
float v_acc_boxed_5940_; float v_res_5941_; lean_object* v_r_5942_; 
v_acc_boxed_5940_ = lean_unbox_float32(v_acc_5939_);
lean_dec_ref(v_acc_5939_);
v_res_5941_ = lp_competition_Submission_NativeFinal_sumLoop(v_n_5936_, v_x_5937_, v_k_5938_, v_acc_boxed_5940_);
lean_dec_ref(v_x_5937_);
lean_dec(v_n_5936_);
v_r_5942_ = lean_box_float32(v_res_5941_);
return v_r_5942_;
}
}
LEAN_EXPORT float lp_competition_Submission_NativeFinal_dotLoop(lean_object* v_n_5943_, lean_object* v_baseA_5944_, lean_object* v_baseB_5945_, lean_object* v_p_5946_, lean_object* v_A_5947_, lean_object* v_B_5948_, lean_object* v_k_5949_, float v_acc_5950_){
_start:
{
float v___y_5952_; uint32_t v___y_5953_; uint8_t v___x_5960_; 
v___x_5960_ = lean_nat_dec_lt(v_k_5949_, v_n_5943_);
if (v___x_5960_ == 0)
{
lean_dec(v_k_5949_);
return v_acc_5950_;
}
else
{
lean_object* v___x_5961_; uint32_t v___x_5962_; uint32_t v___y_5964_; lean_object* v___x_5972_; uint8_t v___x_5973_; 
v___x_5961_ = lean_nat_add(v_baseA_5944_, v_k_5949_);
v___x_5962_ = lean_uint32_once(&lp_competition_Submission_referenceSum___redArg___closed__1, &lp_competition_Submission_referenceSum___redArg___closed__1_once, _init_lp_competition_Submission_referenceSum___redArg___closed__1);
v___x_5972_ = lean_array_get_size(v_A_5947_);
v___x_5973_ = lean_nat_dec_lt(v___x_5961_, v___x_5972_);
if (v___x_5973_ == 0)
{
lean_dec(v___x_5961_);
v___y_5964_ = v___x_5962_;
goto v___jp_5963_;
}
else
{
lean_object* v___x_5974_; uint32_t v___x_5975_; 
v___x_5974_ = lean_array_fget_borrowed(v_A_5947_, v___x_5961_);
lean_dec(v___x_5961_);
v___x_5975_ = lean_unbox_uint32(v___x_5974_);
v___y_5964_ = v___x_5975_;
goto v___jp_5963_;
}
v___jp_5963_:
{
float v_fa_5965_; lean_object* v___x_5966_; lean_object* v___x_5967_; lean_object* v___x_5968_; uint8_t v___x_5969_; 
v_fa_5965_ = lean_float32_of_bits(v___y_5964_);
v___x_5966_ = lean_nat_mul(v_k_5949_, v_p_5946_);
v___x_5967_ = lean_nat_add(v_baseB_5945_, v___x_5966_);
lean_dec(v___x_5966_);
v___x_5968_ = lean_array_get_size(v_B_5948_);
v___x_5969_ = lean_nat_dec_lt(v___x_5967_, v___x_5968_);
if (v___x_5969_ == 0)
{
lean_dec(v___x_5967_);
v___y_5952_ = v_fa_5965_;
v___y_5953_ = v___x_5962_;
goto v___jp_5951_;
}
else
{
lean_object* v___x_5970_; uint32_t v___x_5971_; 
v___x_5970_ = lean_array_fget_borrowed(v_B_5948_, v___x_5967_);
lean_dec(v___x_5967_);
v___x_5971_ = lean_unbox_uint32(v___x_5970_);
v___y_5952_ = v_fa_5965_;
v___y_5953_ = v___x_5971_;
goto v___jp_5951_;
}
}
}
v___jp_5951_:
{
float v_fb_5954_; lean_object* v___x_5955_; lean_object* v___x_5956_; float v___x_5957_; float v___x_5958_; 
v_fb_5954_ = lean_float32_of_bits(v___y_5953_);
v___x_5955_ = lean_unsigned_to_nat(1u);
v___x_5956_ = lean_nat_add(v_k_5949_, v___x_5955_);
lean_dec(v_k_5949_);
v___x_5957_ = lean_float32_mul(v___y_5952_, v_fb_5954_);
v___x_5958_ = lean_float32_add(v_acc_5950_, v___x_5957_);
v_k_5949_ = v___x_5956_;
v_acc_5950_ = v___x_5958_;
goto _start;
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_NativeFinal_dotLoop___boxed(lean_object* v_n_5976_, lean_object* v_baseA_5977_, lean_object* v_baseB_5978_, lean_object* v_p_5979_, lean_object* v_A_5980_, lean_object* v_B_5981_, lean_object* v_k_5982_, lean_object* v_acc_5983_){
_start:
{
float v_acc_boxed_5984_; float v_res_5985_; lean_object* v_r_5986_; 
v_acc_boxed_5984_ = lean_unbox_float32(v_acc_5983_);
lean_dec_ref(v_acc_5983_);
v_res_5985_ = lp_competition_Submission_NativeFinal_dotLoop(v_n_5976_, v_baseA_5977_, v_baseB_5978_, v_p_5979_, v_A_5980_, v_B_5981_, v_k_5982_, v_acc_boxed_5984_);
lean_dec_ref(v_B_5981_);
lean_dec_ref(v_A_5980_);
lean_dec(v_p_5979_);
lean_dec(v_baseB_5978_);
lean_dec(v_baseA_5977_);
lean_dec(v_n_5976_);
v_r_5986_ = lean_box_float32(v_res_5985_);
return v_r_5986_;
}
}
LEAN_EXPORT uint32_t lp_competition_Fin_foldl_loop___at___00Submission_NativeFinal_dot_spec__0(lean_object* v_baseA_5987_, lean_object* v_p_5988_, lean_object* v_baseB_5989_, lean_object* v_B_5990_, lean_object* v_A_5991_, lean_object* v_n_5992_, uint32_t v_x_5993_, lean_object* v_i_5994_){
_start:
{
uint32_t v___y_5996_; float v___y_6001_; float v___y_6002_; uint32_t v___y_6006_; float v___y_6007_; uint8_t v___y_6008_; uint32_t v___y_6023_; float v___y_6024_; uint32_t v___y_6034_; uint8_t v___y_6035_; uint32_t v___y_6050_; uint8_t v___x_6052_; uint32_t v___y_6054_; uint32_t v___y_6073_; uint32_t v___y_6077_; uint32_t v___y_6081_; uint32_t v___y_6082_; uint32_t v___y_6083_; uint32_t v___y_6087_; uint64_t v___y_6088_; uint8_t v___y_6089_; uint64_t v___y_6090_; uint32_t v___y_6102_; uint32_t v___y_6103_; uint32_t v___y_6104_; uint32_t v___y_6105_; uint32_t v___y_6106_; uint32_t v___y_6107_; uint32_t v___y_6114_; uint32_t v___y_6115_; uint8_t v___y_6116_; uint32_t v___y_6117_; uint32_t v___y_6118_; uint32_t v___y_6119_; uint32_t v___y_6123_; uint64_t v___y_6124_; uint32_t v___y_6125_; uint64_t v___y_6126_; uint8_t v___y_6127_; uint32_t v___y_6128_; uint64_t v___y_6129_; uint32_t v___y_6139_; uint64_t v___y_6140_; uint32_t v___y_6141_; uint64_t v___y_6142_; uint8_t v___y_6143_; uint32_t v___y_6144_; uint8_t v___y_6145_; uint64_t v___y_6146_; uint32_t v___y_6153_; uint64_t v___y_6154_; uint32_t v___y_6155_; uint8_t v___y_6156_; uint32_t v___y_6157_; uint64_t v___y_6158_; uint64_t v___y_6159_; uint32_t v___y_6165_; uint64_t v___y_6166_; uint32_t v___y_6167_; uint64_t v___y_6168_; uint8_t v___y_6169_; uint32_t v___y_6170_; uint64_t v___y_6171_; uint64_t v___y_6172_; uint64_t v___y_6227_; uint32_t v___y_6228_; uint32_t v___y_6229_; uint64_t v___y_6230_; uint64_t v___y_6231_; uint8_t v___y_6232_; uint32_t v___y_6233_; uint64_t v___y_6234_; uint64_t v___y_6235_; uint32_t v___y_6241_; uint64_t v___y_6242_; uint64_t v___y_6243_; uint32_t v___y_6244_; uint64_t v___y_6245_; uint8_t v___y_6246_; uint32_t v___y_6247_; uint64_t v___y_6248_; uint64_t v___y_6249_; uint64_t v___y_6250_; uint64_t v___y_6251_; uint32_t v___y_6256_; uint32_t v___y_6257_; uint64_t v___y_6258_; uint64_t v___y_6259_; uint8_t v___y_6260_; uint32_t v___y_6261_; uint64_t v___y_6262_; uint64_t v___y_6263_; uint64_t v___y_6264_; uint64_t v___y_6269_; uint32_t v___y_6270_; uint64_t v___y_6271_; uint64_t v___y_6272_; uint32_t v___y_6273_; uint8_t v___y_6274_; uint32_t v___y_6275_; uint64_t v___y_6276_; uint64_t v___y_6277_; uint64_t v___y_6278_; uint64_t v___y_6279_; uint32_t v___y_6284_; uint32_t v___y_6285_; uint64_t v___y_6286_; uint64_t v___y_6287_; uint8_t v___y_6288_; uint32_t v___y_6289_; uint64_t v___y_6290_; uint64_t v___y_6291_; uint64_t v___y_6292_; uint32_t v___y_6297_; uint64_t v___y_6298_; uint64_t v___y_6299_; uint64_t v___y_6300_; uint32_t v___y_6301_; uint64_t v___y_6302_; uint8_t v___y_6303_; uint32_t v___y_6304_; uint64_t v___y_6305_; uint64_t v___y_6306_; uint64_t v___y_6307_; uint32_t v___y_6312_; uint32_t v___y_6313_; uint64_t v___y_6314_; uint64_t v___y_6315_; uint8_t v___y_6316_; uint32_t v___y_6317_; uint64_t v___y_6318_; uint64_t v___y_6319_; uint64_t v___y_6320_; uint32_t v___y_6325_; uint64_t v___y_6326_; uint64_t v___y_6327_; uint64_t v___y_6328_; uint32_t v___y_6329_; uint8_t v___y_6330_; uint32_t v___y_6331_; uint64_t v___y_6332_; uint64_t v___y_6333_; uint64_t v___y_6334_; uint64_t v___y_6335_; uint32_t v___y_6340_; uint32_t v___y_6341_; uint64_t v___y_6342_; uint64_t v___y_6343_; uint8_t v___y_6344_; uint32_t v___y_6345_; uint64_t v___y_6346_; uint64_t v___y_6347_; uint64_t v___y_6348_; uint32_t v___y_6353_; uint64_t v___y_6354_; uint64_t v___y_6355_; uint32_t v___y_6356_; uint8_t v___y_6357_; uint32_t v___y_6358_; uint64_t v___y_6359_; uint64_t v___y_6360_; uint64_t v___y_6361_; uint32_t v___y_6365_; uint32_t v___y_6366_; uint64_t v___y_6367_; uint8_t v___y_6368_; uint32_t v___y_6369_; uint64_t v___y_6370_; uint32_t v___y_6379_; uint32_t v___y_6380_; uint32_t v___y_6381_; uint32_t v___y_6385_; uint8_t v___y_6386_; uint64_t v___y_6387_; uint64_t v___y_6388_; uint32_t v___y_6400_; uint32_t v___y_6401_; uint64_t v___y_6402_; uint64_t v___y_6403_; uint8_t v___y_6404_; uint32_t v___y_6405_; uint64_t v___y_6406_; uint64_t v___y_6407_; uint32_t v___y_6441_; uint32_t v___y_6442_; uint64_t v___y_6443_; uint32_t v___y_6444_; uint64_t v___y_6445_; uint8_t v___y_6446_; uint32_t v___y_6447_; uint64_t v___y_6448_; uint32_t v___y_6455_; uint32_t v___y_6456_; uint32_t v___y_6457_; uint32_t v___y_6458_; uint64_t v___y_6459_; uint8_t v___y_6460_; uint32_t v___y_6461_; uint64_t v___y_6462_; uint32_t v___y_6469_; uint32_t v___y_6470_; uint32_t v___y_6471_; uint32_t v___y_6472_; uint8_t v___y_6473_; uint32_t v___y_6474_; uint32_t v___y_6475_; uint64_t v___y_6476_; uint32_t v___y_6484_; uint32_t v___y_6485_; uint32_t v___y_6486_; uint32_t v___y_6487_; uint32_t v___y_6488_; uint32_t v___y_6489_; uint8_t v___y_6490_; uint32_t v___y_6501_; uint32_t v___y_6502_; uint32_t v___y_6508_; uint32_t v___y_6509_; uint32_t v___y_6510_; uint8_t v___y_6511_; uint32_t v___y_6512_; uint8_t v___y_6513_; uint32_t v___y_6518_; uint32_t v___y_6519_; uint32_t v___y_6520_; uint8_t v___y_6521_; uint32_t v___y_6522_; uint32_t v___y_6523_; uint32_t v___y_6524_; uint8_t v___y_6525_; uint32_t v___y_6527_; uint32_t v___y_6528_; uint32_t v___y_6529_; uint8_t v___y_6530_; uint32_t v___y_6531_; uint8_t v___y_6532_; uint32_t v___y_6533_; uint32_t v___y_6534_; uint8_t v___y_6535_; uint32_t v___y_6537_; uint32_t v___y_6538_; uint32_t v___y_6539_; uint8_t v___y_6540_; uint32_t v___y_6541_; uint32_t v___y_6542_; uint32_t v___y_6543_; uint8_t v___y_6544_; uint32_t v___y_6550_; uint32_t v___y_6551_; uint32_t v___y_6552_; uint32_t v___y_6553_; uint32_t v___y_6554_; uint32_t v___y_6555_; uint8_t v___y_6556_; uint32_t v___y_6566_; uint32_t v___y_6567_; 
v___x_6052_ = lean_nat_dec_lt(v_i_5994_, v_n_5992_);
if (v___x_6052_ == 0)
{
lean_dec(v_i_5994_);
return v_x_5993_;
}
else
{
lean_object* v___x_6584_; uint32_t v___x_6585_; uint32_t v___y_6587_; lean_object* v___x_6594_; uint8_t v___x_6595_; 
v___x_6584_ = lean_nat_add(v_baseA_5987_, v_i_5994_);
v___x_6585_ = lean_uint32_once(&lp_competition_Submission_referenceSum___redArg___closed__1, &lp_competition_Submission_referenceSum___redArg___closed__1_once, _init_lp_competition_Submission_referenceSum___redArg___closed__1);
v___x_6594_ = lean_array_get_size(v_A_5991_);
v___x_6595_ = lean_nat_dec_lt(v___x_6584_, v___x_6594_);
if (v___x_6595_ == 0)
{
lean_dec(v___x_6584_);
v___y_6587_ = v___x_6585_;
goto v___jp_6586_;
}
else
{
lean_object* v___x_6596_; uint32_t v___x_6597_; 
v___x_6596_ = lean_array_fget_borrowed(v_A_5991_, v___x_6584_);
lean_dec(v___x_6584_);
v___x_6597_ = lean_unbox_uint32(v___x_6596_);
v___y_6587_ = v___x_6597_;
goto v___jp_6586_;
}
v___jp_6586_:
{
lean_object* v___x_6588_; lean_object* v___x_6589_; lean_object* v___x_6590_; uint8_t v___x_6591_; 
v___x_6588_ = lean_nat_mul(v_i_5994_, v_p_5988_);
v___x_6589_ = lean_nat_add(v_baseB_5989_, v___x_6588_);
lean_dec(v___x_6588_);
v___x_6590_ = lean_array_get_size(v_B_5990_);
v___x_6591_ = lean_nat_dec_lt(v___x_6589_, v___x_6590_);
if (v___x_6591_ == 0)
{
lean_dec(v___x_6589_);
v___y_6566_ = v___y_6587_;
v___y_6567_ = v___x_6585_;
goto v___jp_6565_;
}
else
{
lean_object* v___x_6592_; uint32_t v___x_6593_; 
v___x_6592_ = lean_array_fget_borrowed(v_B_5990_, v___x_6589_);
lean_dec(v___x_6589_);
v___x_6593_ = lean_unbox_uint32(v___x_6592_);
v___y_6566_ = v___y_6587_;
v___y_6567_ = v___x_6593_;
goto v___jp_6565_;
}
}
}
v___jp_5995_:
{
lean_object* v___x_5997_; lean_object* v___x_5998_; 
v___x_5997_ = lean_unsigned_to_nat(1u);
v___x_5998_ = lean_nat_add(v_i_5994_, v___x_5997_);
lean_dec(v_i_5994_);
v_x_5993_ = v___y_5996_;
v_i_5994_ = v___x_5998_;
goto _start;
}
v___jp_6000_:
{
float v___x_6003_; uint32_t v___x_6004_; 
v___x_6003_ = lean_float32_add(v___y_6001_, v___y_6002_);
v___x_6004_ = lean_float32_to_bits(v___x_6003_);
v___y_5996_ = v___x_6004_;
goto v___jp_5995_;
}
v___jp_6005_:
{
if (v___y_6008_ == 0)
{
float v___x_6009_; 
v___x_6009_ = lean_float32_of_bits(v___y_6006_);
v___y_6001_ = v___y_6007_;
v___y_6002_ = v___x_6009_;
goto v___jp_6000_;
}
else
{
uint32_t v___x_6010_; uint32_t v___x_6011_; uint32_t v___x_6012_; uint32_t v___x_6013_; float v___x_6014_; lean_object* v___x_6015_; uint32_t v___x_6016_; uint32_t v___x_6017_; lean_object* v___x_6018_; lean_object* v___x_6019_; float v___x_6020_; float v___x_6021_; 
v___x_6010_ = 8388607;
v___x_6011_ = lean_uint32_land(v___y_6006_, v___x_6010_);
v___x_6012_ = 8388608;
v___x_6013_ = lean_uint32_lor(v___x_6011_, v___x_6012_);
v___x_6014_ = lean_uint32_to_float32(v___x_6013_);
v___x_6015_ = lp_competition_R2W01b_scaleTable;
v___x_6016_ = 23;
v___x_6017_ = lean_uint32_shift_right(v___y_6006_, v___x_6016_);
v___x_6018_ = lean_uint32_to_nat(v___x_6017_);
v___x_6019_ = lean_array_fget_borrowed(v___x_6015_, v___x_6018_);
lean_dec(v___x_6018_);
v___x_6020_ = lean_unbox_float32(v___x_6019_);
v___x_6021_ = lean_float32_mul(v___x_6014_, v___x_6020_);
v___y_6001_ = v___y_6007_;
v___y_6002_ = v___x_6021_;
goto v___jp_6000_;
}
}
v___jp_6022_:
{
uint32_t v___x_6025_; uint32_t v_a_6026_; uint32_t v___x_6027_; uint32_t v___x_6028_; uint32_t v___x_6029_; uint8_t v___x_6030_; 
v___x_6025_ = 2147483647;
v_a_6026_ = lean_uint32_land(v___y_6023_, v___x_6025_);
v___x_6027_ = 201326591;
v___x_6028_ = 1;
v___x_6029_ = lean_uint32_sub(v_a_6026_, v___x_6028_);
v___x_6030_ = lean_uint32_dec_le(v___x_6027_, v___x_6029_);
if (v___x_6030_ == 0)
{
v___y_6006_ = v___y_6023_;
v___y_6007_ = v___y_6024_;
v___y_6008_ = v___x_6030_;
goto v___jp_6005_;
}
else
{
uint32_t v___x_6031_; uint8_t v___x_6032_; 
v___x_6031_ = 2139095040;
v___x_6032_ = lean_uint32_dec_lt(v_a_6026_, v___x_6031_);
v___y_6006_ = v___y_6023_;
v___y_6007_ = v___y_6024_;
v___y_6008_ = v___x_6032_;
goto v___jp_6005_;
}
}
v___jp_6033_:
{
if (v___y_6035_ == 0)
{
float v___x_6036_; 
v___x_6036_ = lean_float32_of_bits(v_x_5993_);
v___y_6023_ = v___y_6034_;
v___y_6024_ = v___x_6036_;
goto v___jp_6022_;
}
else
{
uint32_t v___x_6037_; uint32_t v___x_6038_; uint32_t v___x_6039_; uint32_t v___x_6040_; float v___x_6041_; lean_object* v___x_6042_; uint32_t v___x_6043_; uint32_t v___x_6044_; lean_object* v___x_6045_; lean_object* v___x_6046_; float v___x_6047_; float v___x_6048_; 
v___x_6037_ = 8388607;
v___x_6038_ = lean_uint32_land(v_x_5993_, v___x_6037_);
v___x_6039_ = 8388608;
v___x_6040_ = lean_uint32_lor(v___x_6038_, v___x_6039_);
v___x_6041_ = lean_uint32_to_float32(v___x_6040_);
v___x_6042_ = lp_competition_R2W01b_scaleTable;
v___x_6043_ = 23;
v___x_6044_ = lean_uint32_shift_right(v_x_5993_, v___x_6043_);
v___x_6045_ = lean_uint32_to_nat(v___x_6044_);
v___x_6046_ = lean_array_fget_borrowed(v___x_6042_, v___x_6045_);
lean_dec(v___x_6045_);
v___x_6047_ = lean_unbox_float32(v___x_6046_);
v___x_6048_ = lean_float32_mul(v___x_6041_, v___x_6047_);
v___y_6023_ = v___y_6034_;
v___y_6024_ = v___x_6048_;
goto v___jp_6022_;
}
}
v___jp_6049_:
{
uint32_t v___x_6051_; 
v___x_6051_ = lp_competition_Submission_TunedAdd_add(v_x_5993_, v___y_6050_);
v___y_5996_ = v___x_6051_;
goto v___jp_5995_;
}
v___jp_6053_:
{
uint32_t v___x_6055_; uint32_t v___x_6056_; uint32_t v___x_6057_; uint32_t v___x_6058_; uint8_t v___x_6059_; 
v___x_6055_ = 23;
v___x_6056_ = lean_uint32_shift_right(v_x_5993_, v___x_6055_);
v___x_6057_ = 255;
v___x_6058_ = lean_uint32_land(v___x_6056_, v___x_6057_);
v___x_6059_ = lean_uint32_dec_eq(v___x_6058_, v___x_6057_);
if (v___x_6059_ == 0)
{
if (v___x_6052_ == 0)
{
v___y_6050_ = v___y_6054_;
goto v___jp_6049_;
}
else
{
uint32_t v___x_6060_; uint32_t v___x_6061_; uint8_t v___x_6062_; 
v___x_6060_ = lean_uint32_shift_right(v___y_6054_, v___x_6055_);
v___x_6061_ = lean_uint32_land(v___x_6060_, v___x_6057_);
v___x_6062_ = lean_uint32_dec_eq(v___x_6061_, v___x_6057_);
if (v___x_6062_ == 0)
{
uint32_t v___x_6063_; uint32_t v_a_6064_; uint32_t v___x_6065_; uint32_t v___x_6066_; uint32_t v___x_6067_; uint8_t v___x_6068_; 
v___x_6063_ = 2147483647;
v_a_6064_ = lean_uint32_land(v_x_5993_, v___x_6063_);
v___x_6065_ = 201326591;
v___x_6066_ = 1;
v___x_6067_ = lean_uint32_sub(v_a_6064_, v___x_6066_);
v___x_6068_ = lean_uint32_dec_le(v___x_6065_, v___x_6067_);
if (v___x_6068_ == 0)
{
v___y_6034_ = v___y_6054_;
v___y_6035_ = v___x_6068_;
goto v___jp_6033_;
}
else
{
uint32_t v___x_6069_; uint8_t v___x_6070_; 
v___x_6069_ = 2139095040;
v___x_6070_ = lean_uint32_dec_lt(v_a_6064_, v___x_6069_);
v___y_6034_ = v___y_6054_;
v___y_6035_ = v___x_6070_;
goto v___jp_6033_;
}
}
else
{
uint32_t v___x_6071_; 
v___x_6071_ = lp_competition_Submission_TunedAdd_add(v_x_5993_, v___y_6054_);
v___y_5996_ = v___x_6071_;
goto v___jp_5995_;
}
}
}
else
{
v___y_6050_ = v___y_6054_;
goto v___jp_6049_;
}
}
v___jp_6072_:
{
uint32_t v___x_6074_; uint32_t v___x_6075_; 
v___x_6074_ = 8388608;
v___x_6075_ = lean_uint32_lor(v___y_6073_, v___x_6074_);
v___y_6054_ = v___x_6075_;
goto v___jp_6053_;
}
v___jp_6076_:
{
uint32_t v___x_6078_; uint32_t v___x_6079_; 
v___x_6078_ = 8388608;
v___x_6079_ = lean_uint32_lor(v___y_6077_, v___x_6078_);
v___y_6054_ = v___x_6079_;
goto v___jp_6053_;
}
v___jp_6080_:
{
uint32_t v___x_6084_; uint32_t v___x_6085_; 
v___x_6084_ = lean_uint32_land(v___y_6082_, v___y_6081_);
v___x_6085_ = lean_uint32_lor(v___y_6083_, v___x_6084_);
v___y_6054_ = v___x_6085_;
goto v___jp_6053_;
}
v___jp_6086_:
{
uint8_t v___x_6091_; 
v___x_6091_ = lean_uint64_dec_eq(v___y_6090_, v___y_6088_);
if (v___x_6091_ == 0)
{
uint64_t v___x_6092_; uint8_t v___x_6093_; 
v___x_6092_ = 8388608ULL;
v___x_6093_ = lean_uint64_dec_eq(v___y_6090_, v___x_6092_);
if (v___x_6093_ == 0)
{
uint32_t v___x_6094_; 
v___x_6094_ = lean_uint64_to_uint32(v___y_6090_);
if (v___y_6089_ == 0)
{
uint32_t v___x_6095_; 
v___x_6095_ = 0;
v___y_6081_ = v___y_6087_;
v___y_6082_ = v___x_6094_;
v___y_6083_ = v___x_6095_;
goto v___jp_6080_;
}
else
{
uint32_t v___x_6096_; 
v___x_6096_ = 2147483648;
v___y_6081_ = v___y_6087_;
v___y_6082_ = v___x_6094_;
v___y_6083_ = v___x_6096_;
goto v___jp_6080_;
}
}
else
{
if (v___y_6089_ == 0)
{
uint32_t v___x_6097_; 
v___x_6097_ = 0;
v___y_6073_ = v___x_6097_;
goto v___jp_6072_;
}
else
{
uint32_t v___x_6098_; 
v___x_6098_ = 2147483648;
v___y_6073_ = v___x_6098_;
goto v___jp_6072_;
}
}
}
else
{
if (v___y_6089_ == 0)
{
uint32_t v___x_6099_; 
v___x_6099_ = 0;
v___y_6054_ = v___x_6099_;
goto v___jp_6053_;
}
else
{
uint32_t v___x_6100_; 
v___x_6100_ = 2147483648;
v___y_6054_ = v___x_6100_;
goto v___jp_6053_;
}
}
}
v___jp_6101_:
{
uint32_t v___x_6108_; uint32_t v___x_6109_; uint32_t v___x_6110_; uint32_t v___x_6111_; uint32_t v___x_6112_; 
v___x_6108_ = lean_uint32_land(v___y_6105_, v___y_6103_);
v___x_6109_ = lean_uint32_shift_left(v___x_6108_, v___y_6104_);
v___x_6110_ = lean_uint32_lor(v___y_6107_, v___x_6109_);
v___x_6111_ = lean_uint32_land(v___y_6106_, v___y_6102_);
v___x_6112_ = lean_uint32_lor(v___x_6110_, v___x_6111_);
v___y_6054_ = v___x_6112_;
goto v___jp_6053_;
}
v___jp_6113_:
{
if (v___y_6116_ == 0)
{
uint32_t v___x_6120_; 
v___x_6120_ = 0;
v___y_6102_ = v___y_6114_;
v___y_6103_ = v___y_6115_;
v___y_6104_ = v___y_6117_;
v___y_6105_ = v___y_6118_;
v___y_6106_ = v___y_6119_;
v___y_6107_ = v___x_6120_;
goto v___jp_6101_;
}
else
{
uint32_t v___x_6121_; 
v___x_6121_ = 2147483648;
v___y_6102_ = v___y_6114_;
v___y_6103_ = v___y_6115_;
v___y_6104_ = v___y_6117_;
v___y_6105_ = v___y_6118_;
v___y_6106_ = v___y_6119_;
v___y_6107_ = v___x_6121_;
goto v___jp_6101_;
}
}
v___jp_6122_:
{
uint64_t v___x_6130_; uint64_t v_encodedExponent_6131_; uint32_t v___x_6132_; uint64_t v___x_6133_; uint8_t v___x_6134_; 
v___x_6130_ = 171ULL;
v_encodedExponent_6131_ = lean_uint64_sub(v___y_6126_, v___x_6130_);
v___x_6132_ = lean_uint64_to_uint32(v_encodedExponent_6131_);
v___x_6133_ = 8388608ULL;
v___x_6134_ = lean_uint64_dec_lt(v___y_6129_, v___x_6133_);
if (v___x_6134_ == 0)
{
uint64_t v___x_6135_; uint32_t v___x_6136_; 
v___x_6135_ = lean_uint64_sub(v___y_6129_, v___x_6133_);
v___x_6136_ = lean_uint64_to_uint32(v___x_6135_);
v___y_6114_ = v___y_6123_;
v___y_6115_ = v___y_6125_;
v___y_6116_ = v___y_6127_;
v___y_6117_ = v___y_6128_;
v___y_6118_ = v___x_6132_;
v___y_6119_ = v___x_6136_;
goto v___jp_6113_;
}
else
{
uint32_t v___x_6137_; 
v___x_6137_ = lean_uint64_to_uint32(v___y_6124_);
v___y_6114_ = v___y_6123_;
v___y_6115_ = v___y_6125_;
v___y_6116_ = v___y_6127_;
v___y_6117_ = v___y_6128_;
v___y_6118_ = v___x_6132_;
v___y_6119_ = v___x_6137_;
goto v___jp_6113_;
}
}
v___jp_6138_:
{
uint64_t v___x_6147_; uint8_t v___x_6148_; 
v___x_6147_ = 425ULL;
v___x_6148_ = lean_uint64_dec_lt(v___x_6147_, v___y_6146_);
if (v___x_6148_ == 0)
{
if (v___y_6145_ == 0)
{
v___y_6123_ = v___y_6139_;
v___y_6124_ = v___y_6142_;
v___y_6125_ = v___y_6141_;
v___y_6126_ = v___y_6146_;
v___y_6127_ = v___y_6143_;
v___y_6128_ = v___y_6144_;
v___y_6129_ = v___y_6140_;
goto v___jp_6122_;
}
else
{
uint64_t v___x_6149_; 
v___x_6149_ = 8388608ULL;
v___y_6123_ = v___y_6139_;
v___y_6124_ = v___y_6142_;
v___y_6125_ = v___y_6141_;
v___y_6126_ = v___y_6146_;
v___y_6127_ = v___y_6143_;
v___y_6128_ = v___y_6144_;
v___y_6129_ = v___x_6149_;
goto v___jp_6122_;
}
}
else
{
if (v___y_6143_ == 0)
{
uint32_t v___x_6150_; 
v___x_6150_ = 2139095040;
v___y_6054_ = v___x_6150_;
goto v___jp_6053_;
}
else
{
uint32_t v___x_6151_; 
v___x_6151_ = 4286578688;
v___y_6054_ = v___x_6151_;
goto v___jp_6053_;
}
}
}
v___jp_6152_:
{
uint64_t v___x_6160_; uint8_t v_carry_6161_; 
v___x_6160_ = 16777216ULL;
v_carry_6161_ = lean_uint64_dec_eq(v___y_6159_, v___x_6160_);
if (v_carry_6161_ == 0)
{
v___y_6139_ = v___y_6153_;
v___y_6140_ = v___y_6159_;
v___y_6141_ = v___y_6155_;
v___y_6142_ = v___y_6154_;
v___y_6143_ = v___y_6156_;
v___y_6144_ = v___y_6157_;
v___y_6145_ = v_carry_6161_;
v___y_6146_ = v___y_6158_;
goto v___jp_6138_;
}
else
{
uint64_t v___x_6162_; uint64_t v___x_6163_; 
v___x_6162_ = 1ULL;
v___x_6163_ = lean_uint64_add(v___y_6158_, v___x_6162_);
v___y_6139_ = v___y_6153_;
v___y_6140_ = v___y_6159_;
v___y_6141_ = v___y_6155_;
v___y_6142_ = v___y_6154_;
v___y_6143_ = v___y_6156_;
v___y_6144_ = v___y_6157_;
v___y_6145_ = v_carry_6161_;
v___y_6146_ = v___x_6163_;
goto v___jp_6138_;
}
}
v___jp_6164_:
{
uint64_t v_position_6173_; uint64_t v___x_6174_; uint8_t v___x_6175_; 
v_position_6173_ = lean_uint64_add(v___y_6172_, v___y_6171_);
v___x_6174_ = 172ULL;
v___x_6175_ = lean_uint64_dec_lt(v_position_6173_, v___x_6174_);
if (v___x_6175_ == 0)
{
uint64_t v___x_6176_; uint8_t v___x_6177_; 
v___x_6176_ = 23ULL;
v___x_6177_ = lean_uint64_dec_lt(v___y_6172_, v___x_6176_);
if (v___x_6177_ == 0)
{
uint64_t v___x_6178_; uint8_t v___x_6179_; 
v___x_6178_ = lean_uint64_sub(v___y_6172_, v___x_6176_);
v___x_6179_ = lean_uint64_dec_eq(v___x_6178_, v___y_6168_);
if (v___x_6179_ == 0)
{
uint64_t v___x_6180_; uint8_t v___x_6181_; 
v___x_6180_ = 64ULL;
v___x_6181_ = lean_uint64_dec_lt(v___x_6178_, v___x_6180_);
if (v___x_6181_ == 0)
{
uint8_t v___x_6182_; 
v___x_6182_ = lean_uint64_dec_eq(v___x_6178_, v___x_6180_);
if (v___x_6182_ == 0)
{
v___y_6153_ = v___y_6165_;
v___y_6154_ = v___y_6168_;
v___y_6155_ = v___y_6167_;
v___y_6156_ = v___y_6169_;
v___y_6157_ = v___y_6170_;
v___y_6158_ = v_position_6173_;
v___y_6159_ = v___y_6168_;
goto v___jp_6152_;
}
else
{
uint64_t v___x_6183_; uint8_t v___x_6184_; 
v___x_6183_ = 9223372036854775808ULL;
v___x_6184_ = lean_uint64_dec_lt(v___x_6183_, v___y_6166_);
if (v___x_6184_ == 0)
{
v___y_6153_ = v___y_6165_;
v___y_6154_ = v___y_6168_;
v___y_6155_ = v___y_6167_;
v___y_6156_ = v___y_6169_;
v___y_6157_ = v___y_6170_;
v___y_6158_ = v_position_6173_;
v___y_6159_ = v___y_6168_;
goto v___jp_6152_;
}
else
{
uint64_t v___x_6185_; 
v___x_6185_ = 1ULL;
v___y_6153_ = v___y_6165_;
v___y_6154_ = v___y_6168_;
v___y_6155_ = v___y_6167_;
v___y_6156_ = v___y_6169_;
v___y_6157_ = v___y_6170_;
v___y_6158_ = v_position_6173_;
v___y_6159_ = v___x_6185_;
goto v___jp_6152_;
}
}
}
else
{
uint64_t v_quotient_6186_; uint64_t v___x_6187_; uint64_t v___x_6188_; uint64_t v___x_6189_; uint64_t v_remainder_6190_; uint64_t v___x_6191_; uint64_t v_half_6192_; uint8_t v___x_6193_; 
v_quotient_6186_ = lean_uint64_shift_right(v___y_6166_, v___x_6178_);
v___x_6187_ = 1ULL;
v___x_6188_ = lean_uint64_shift_left(v___x_6187_, v___x_6178_);
v___x_6189_ = lean_uint64_sub(v___x_6188_, v___x_6187_);
v_remainder_6190_ = lean_uint64_land(v___y_6166_, v___x_6189_);
v___x_6191_ = lean_uint64_sub(v___x_6178_, v___x_6187_);
v_half_6192_ = lean_uint64_shift_left(v___x_6187_, v___x_6191_);
v___x_6193_ = lean_uint64_dec_lt(v_remainder_6190_, v_half_6192_);
if (v___x_6193_ == 0)
{
uint8_t v___x_6194_; 
v___x_6194_ = lean_uint64_dec_lt(v_half_6192_, v_remainder_6190_);
if (v___x_6194_ == 0)
{
uint64_t v___x_6195_; uint8_t v___x_6196_; 
v___x_6195_ = lean_uint64_land(v_quotient_6186_, v___x_6187_);
v___x_6196_ = lean_uint64_dec_eq(v___x_6195_, v___y_6168_);
if (v___x_6196_ == 0)
{
uint64_t v___x_6197_; 
v___x_6197_ = lean_uint64_add(v_quotient_6186_, v___x_6187_);
v___y_6153_ = v___y_6165_;
v___y_6154_ = v___y_6168_;
v___y_6155_ = v___y_6167_;
v___y_6156_ = v___y_6169_;
v___y_6157_ = v___y_6170_;
v___y_6158_ = v_position_6173_;
v___y_6159_ = v___x_6197_;
goto v___jp_6152_;
}
else
{
v___y_6153_ = v___y_6165_;
v___y_6154_ = v___y_6168_;
v___y_6155_ = v___y_6167_;
v___y_6156_ = v___y_6169_;
v___y_6157_ = v___y_6170_;
v___y_6158_ = v_position_6173_;
v___y_6159_ = v_quotient_6186_;
goto v___jp_6152_;
}
}
else
{
uint64_t v___x_6198_; 
v___x_6198_ = lean_uint64_add(v_quotient_6186_, v___x_6187_);
v___y_6153_ = v___y_6165_;
v___y_6154_ = v___y_6168_;
v___y_6155_ = v___y_6167_;
v___y_6156_ = v___y_6169_;
v___y_6157_ = v___y_6170_;
v___y_6158_ = v_position_6173_;
v___y_6159_ = v___x_6198_;
goto v___jp_6152_;
}
}
else
{
v___y_6153_ = v___y_6165_;
v___y_6154_ = v___y_6168_;
v___y_6155_ = v___y_6167_;
v___y_6156_ = v___y_6169_;
v___y_6157_ = v___y_6170_;
v___y_6158_ = v_position_6173_;
v___y_6159_ = v_quotient_6186_;
goto v___jp_6152_;
}
}
}
else
{
v___y_6153_ = v___y_6165_;
v___y_6154_ = v___y_6168_;
v___y_6155_ = v___y_6167_;
v___y_6156_ = v___y_6169_;
v___y_6157_ = v___y_6170_;
v___y_6158_ = v_position_6173_;
v___y_6159_ = v___y_6166_;
goto v___jp_6152_;
}
}
else
{
uint64_t v___x_6199_; uint64_t v___x_6200_; 
v___x_6199_ = lean_uint64_sub(v___x_6176_, v___y_6172_);
v___x_6200_ = lean_uint64_shift_left(v___y_6166_, v___x_6199_);
v___y_6153_ = v___y_6165_;
v___y_6154_ = v___y_6168_;
v___y_6155_ = v___y_6167_;
v___y_6156_ = v___y_6169_;
v___y_6157_ = v___y_6170_;
v___y_6158_ = v_position_6173_;
v___y_6159_ = v___x_6200_;
goto v___jp_6152_;
}
}
else
{
uint64_t v___x_6201_; uint8_t v___x_6202_; 
v___x_6201_ = 149ULL;
v___x_6202_ = lean_uint64_dec_lt(v___y_6171_, v___x_6201_);
if (v___x_6202_ == 0)
{
uint64_t v___x_6203_; uint64_t v___x_6204_; 
v___x_6203_ = lean_uint64_sub(v___y_6171_, v___x_6201_);
v___x_6204_ = lean_uint64_shift_left(v___y_6166_, v___x_6203_);
v___y_6087_ = v___y_6165_;
v___y_6088_ = v___y_6168_;
v___y_6089_ = v___y_6169_;
v___y_6090_ = v___x_6204_;
goto v___jp_6086_;
}
else
{
uint64_t v___x_6205_; uint8_t v___x_6206_; 
v___x_6205_ = lean_uint64_sub(v___x_6201_, v___y_6171_);
v___x_6206_ = lean_uint64_dec_eq(v___x_6205_, v___y_6168_);
if (v___x_6206_ == 0)
{
uint64_t v___x_6207_; uint8_t v___x_6208_; 
v___x_6207_ = 64ULL;
v___x_6208_ = lean_uint64_dec_lt(v___x_6205_, v___x_6207_);
if (v___x_6208_ == 0)
{
uint8_t v___x_6209_; 
v___x_6209_ = lean_uint64_dec_eq(v___x_6205_, v___x_6207_);
if (v___x_6209_ == 0)
{
v___y_6087_ = v___y_6165_;
v___y_6088_ = v___y_6168_;
v___y_6089_ = v___y_6169_;
v___y_6090_ = v___y_6168_;
goto v___jp_6086_;
}
else
{
uint64_t v___x_6210_; uint8_t v___x_6211_; 
v___x_6210_ = 9223372036854775808ULL;
v___x_6211_ = lean_uint64_dec_lt(v___x_6210_, v___y_6166_);
if (v___x_6211_ == 0)
{
v___y_6087_ = v___y_6165_;
v___y_6088_ = v___y_6168_;
v___y_6089_ = v___y_6169_;
v___y_6090_ = v___y_6168_;
goto v___jp_6086_;
}
else
{
uint64_t v___x_6212_; 
v___x_6212_ = 1ULL;
v___y_6087_ = v___y_6165_;
v___y_6088_ = v___y_6168_;
v___y_6089_ = v___y_6169_;
v___y_6090_ = v___x_6212_;
goto v___jp_6086_;
}
}
}
else
{
uint64_t v_quotient_6213_; uint64_t v___x_6214_; uint64_t v___x_6215_; uint64_t v___x_6216_; uint64_t v_remainder_6217_; uint64_t v___x_6218_; uint64_t v_half_6219_; uint8_t v___x_6220_; 
v_quotient_6213_ = lean_uint64_shift_right(v___y_6166_, v___x_6205_);
v___x_6214_ = 1ULL;
v___x_6215_ = lean_uint64_shift_left(v___x_6214_, v___x_6205_);
v___x_6216_ = lean_uint64_sub(v___x_6215_, v___x_6214_);
v_remainder_6217_ = lean_uint64_land(v___y_6166_, v___x_6216_);
v___x_6218_ = lean_uint64_sub(v___x_6205_, v___x_6214_);
v_half_6219_ = lean_uint64_shift_left(v___x_6214_, v___x_6218_);
v___x_6220_ = lean_uint64_dec_lt(v_remainder_6217_, v_half_6219_);
if (v___x_6220_ == 0)
{
uint8_t v___x_6221_; 
v___x_6221_ = lean_uint64_dec_lt(v_half_6219_, v_remainder_6217_);
if (v___x_6221_ == 0)
{
uint64_t v___x_6222_; uint8_t v___x_6223_; 
v___x_6222_ = lean_uint64_land(v_quotient_6213_, v___x_6214_);
v___x_6223_ = lean_uint64_dec_eq(v___x_6222_, v___y_6168_);
if (v___x_6223_ == 0)
{
uint64_t v___x_6224_; 
v___x_6224_ = lean_uint64_add(v_quotient_6213_, v___x_6214_);
v___y_6087_ = v___y_6165_;
v___y_6088_ = v___y_6168_;
v___y_6089_ = v___y_6169_;
v___y_6090_ = v___x_6224_;
goto v___jp_6086_;
}
else
{
v___y_6087_ = v___y_6165_;
v___y_6088_ = v___y_6168_;
v___y_6089_ = v___y_6169_;
v___y_6090_ = v_quotient_6213_;
goto v___jp_6086_;
}
}
else
{
uint64_t v___x_6225_; 
v___x_6225_ = lean_uint64_add(v_quotient_6213_, v___x_6214_);
v___y_6087_ = v___y_6165_;
v___y_6088_ = v___y_6168_;
v___y_6089_ = v___y_6169_;
v___y_6090_ = v___x_6225_;
goto v___jp_6086_;
}
}
else
{
v___y_6087_ = v___y_6165_;
v___y_6088_ = v___y_6168_;
v___y_6089_ = v___y_6169_;
v___y_6090_ = v_quotient_6213_;
goto v___jp_6086_;
}
}
}
else
{
v___y_6087_ = v___y_6165_;
v___y_6088_ = v___y_6168_;
v___y_6089_ = v___y_6169_;
v___y_6090_ = v___y_6166_;
goto v___jp_6086_;
}
}
}
}
v___jp_6226_:
{
uint64_t v___x_6236_; uint64_t v___x_6237_; uint8_t v___x_6238_; 
v___x_6236_ = 1ULL;
v___x_6237_ = lean_uint64_shift_right(v___y_6227_, v___x_6236_);
v___x_6238_ = lean_uint64_dec_eq(v___x_6237_, v___y_6231_);
if (v___x_6238_ == 0)
{
uint64_t v___x_6239_; 
v___x_6239_ = lean_uint64_add(v___y_6235_, v___x_6236_);
v___y_6165_ = v___y_6228_;
v___y_6166_ = v___y_6230_;
v___y_6167_ = v___y_6229_;
v___y_6168_ = v___y_6231_;
v___y_6169_ = v___y_6232_;
v___y_6170_ = v___y_6233_;
v___y_6171_ = v___y_6234_;
v___y_6172_ = v___x_6239_;
goto v___jp_6164_;
}
else
{
v___y_6165_ = v___y_6228_;
v___y_6166_ = v___y_6230_;
v___y_6167_ = v___y_6229_;
v___y_6168_ = v___y_6231_;
v___y_6169_ = v___y_6232_;
v___y_6170_ = v___y_6233_;
v___y_6171_ = v___y_6234_;
v___y_6172_ = v___y_6235_;
goto v___jp_6164_;
}
}
v___jp_6240_:
{
uint64_t v___x_6252_; uint8_t v___x_6253_; 
v___x_6252_ = lean_uint64_shift_right(v___y_6249_, v___y_6245_);
v___x_6253_ = lean_uint64_dec_eq(v___x_6252_, v___y_6242_);
if (v___x_6253_ == 0)
{
uint64_t v___x_6254_; 
v___x_6254_ = lean_uint64_add(v___y_6250_, v___y_6245_);
v___y_6227_ = v___y_6251_;
v___y_6228_ = v___y_6241_;
v___y_6229_ = v___y_6244_;
v___y_6230_ = v___y_6243_;
v___y_6231_ = v___y_6242_;
v___y_6232_ = v___y_6246_;
v___y_6233_ = v___y_6247_;
v___y_6234_ = v___y_6248_;
v___y_6235_ = v___x_6254_;
goto v___jp_6226_;
}
else
{
v___y_6227_ = v___y_6251_;
v___y_6228_ = v___y_6241_;
v___y_6229_ = v___y_6244_;
v___y_6230_ = v___y_6243_;
v___y_6231_ = v___y_6242_;
v___y_6232_ = v___y_6246_;
v___y_6233_ = v___y_6247_;
v___y_6234_ = v___y_6248_;
v___y_6235_ = v___y_6250_;
goto v___jp_6226_;
}
}
v___jp_6255_:
{
uint64_t v___x_6265_; uint64_t v___x_6266_; uint8_t v___x_6267_; 
v___x_6265_ = 2ULL;
v___x_6266_ = lean_uint64_shift_right(v___y_6263_, v___x_6265_);
v___x_6267_ = lean_uint64_dec_eq(v___x_6266_, v___y_6259_);
if (v___x_6267_ == 0)
{
v___y_6241_ = v___y_6256_;
v___y_6242_ = v___y_6259_;
v___y_6243_ = v___y_6258_;
v___y_6244_ = v___y_6257_;
v___y_6245_ = v___x_6265_;
v___y_6246_ = v___y_6260_;
v___y_6247_ = v___y_6261_;
v___y_6248_ = v___y_6262_;
v___y_6249_ = v___y_6263_;
v___y_6250_ = v___y_6264_;
v___y_6251_ = v___x_6266_;
goto v___jp_6240_;
}
else
{
v___y_6241_ = v___y_6256_;
v___y_6242_ = v___y_6259_;
v___y_6243_ = v___y_6258_;
v___y_6244_ = v___y_6257_;
v___y_6245_ = v___x_6265_;
v___y_6246_ = v___y_6260_;
v___y_6247_ = v___y_6261_;
v___y_6248_ = v___y_6262_;
v___y_6249_ = v___y_6263_;
v___y_6250_ = v___y_6264_;
v___y_6251_ = v___y_6263_;
goto v___jp_6240_;
}
}
v___jp_6268_:
{
uint64_t v___x_6280_; uint8_t v___x_6281_; 
v___x_6280_ = lean_uint64_shift_right(v___y_6278_, v___y_6269_);
v___x_6281_ = lean_uint64_dec_eq(v___x_6280_, v___y_6271_);
if (v___x_6281_ == 0)
{
uint64_t v___x_6282_; 
v___x_6282_ = lean_uint64_add(v___y_6277_, v___y_6269_);
v___y_6256_ = v___y_6270_;
v___y_6257_ = v___y_6273_;
v___y_6258_ = v___y_6272_;
v___y_6259_ = v___y_6271_;
v___y_6260_ = v___y_6274_;
v___y_6261_ = v___y_6275_;
v___y_6262_ = v___y_6276_;
v___y_6263_ = v___y_6279_;
v___y_6264_ = v___x_6282_;
goto v___jp_6255_;
}
else
{
v___y_6256_ = v___y_6270_;
v___y_6257_ = v___y_6273_;
v___y_6258_ = v___y_6272_;
v___y_6259_ = v___y_6271_;
v___y_6260_ = v___y_6274_;
v___y_6261_ = v___y_6275_;
v___y_6262_ = v___y_6276_;
v___y_6263_ = v___y_6279_;
v___y_6264_ = v___y_6277_;
goto v___jp_6255_;
}
}
v___jp_6283_:
{
uint64_t v___x_6293_; uint64_t v___x_6294_; uint8_t v___x_6295_; 
v___x_6293_ = 4ULL;
v___x_6294_ = lean_uint64_shift_right(v___y_6291_, v___x_6293_);
v___x_6295_ = lean_uint64_dec_eq(v___x_6294_, v___y_6287_);
if (v___x_6295_ == 0)
{
v___y_6269_ = v___x_6293_;
v___y_6270_ = v___y_6284_;
v___y_6271_ = v___y_6287_;
v___y_6272_ = v___y_6286_;
v___y_6273_ = v___y_6285_;
v___y_6274_ = v___y_6288_;
v___y_6275_ = v___y_6289_;
v___y_6276_ = v___y_6290_;
v___y_6277_ = v___y_6292_;
v___y_6278_ = v___y_6291_;
v___y_6279_ = v___x_6294_;
goto v___jp_6268_;
}
else
{
v___y_6269_ = v___x_6293_;
v___y_6270_ = v___y_6284_;
v___y_6271_ = v___y_6287_;
v___y_6272_ = v___y_6286_;
v___y_6273_ = v___y_6285_;
v___y_6274_ = v___y_6288_;
v___y_6275_ = v___y_6289_;
v___y_6276_ = v___y_6290_;
v___y_6277_ = v___y_6292_;
v___y_6278_ = v___y_6291_;
v___y_6279_ = v___y_6291_;
goto v___jp_6268_;
}
}
v___jp_6296_:
{
uint64_t v___x_6308_; uint8_t v___x_6309_; 
v___x_6308_ = lean_uint64_shift_right(v___y_6306_, v___y_6298_);
v___x_6309_ = lean_uint64_dec_eq(v___x_6308_, v___y_6299_);
if (v___x_6309_ == 0)
{
uint64_t v___x_6310_; 
v___x_6310_ = lean_uint64_add(v___y_6302_, v___y_6298_);
v___y_6284_ = v___y_6297_;
v___y_6285_ = v___y_6301_;
v___y_6286_ = v___y_6300_;
v___y_6287_ = v___y_6299_;
v___y_6288_ = v___y_6303_;
v___y_6289_ = v___y_6304_;
v___y_6290_ = v___y_6305_;
v___y_6291_ = v___y_6307_;
v___y_6292_ = v___x_6310_;
goto v___jp_6283_;
}
else
{
v___y_6284_ = v___y_6297_;
v___y_6285_ = v___y_6301_;
v___y_6286_ = v___y_6300_;
v___y_6287_ = v___y_6299_;
v___y_6288_ = v___y_6303_;
v___y_6289_ = v___y_6304_;
v___y_6290_ = v___y_6305_;
v___y_6291_ = v___y_6307_;
v___y_6292_ = v___y_6302_;
goto v___jp_6283_;
}
}
v___jp_6311_:
{
uint64_t v___x_6321_; uint64_t v___x_6322_; uint8_t v___x_6323_; 
v___x_6321_ = 8ULL;
v___x_6322_ = lean_uint64_shift_right(v___y_6319_, v___x_6321_);
v___x_6323_ = lean_uint64_dec_eq(v___x_6322_, v___y_6315_);
if (v___x_6323_ == 0)
{
v___y_6297_ = v___y_6312_;
v___y_6298_ = v___x_6321_;
v___y_6299_ = v___y_6315_;
v___y_6300_ = v___y_6314_;
v___y_6301_ = v___y_6313_;
v___y_6302_ = v___y_6320_;
v___y_6303_ = v___y_6316_;
v___y_6304_ = v___y_6317_;
v___y_6305_ = v___y_6318_;
v___y_6306_ = v___y_6319_;
v___y_6307_ = v___x_6322_;
goto v___jp_6296_;
}
else
{
v___y_6297_ = v___y_6312_;
v___y_6298_ = v___x_6321_;
v___y_6299_ = v___y_6315_;
v___y_6300_ = v___y_6314_;
v___y_6301_ = v___y_6313_;
v___y_6302_ = v___y_6320_;
v___y_6303_ = v___y_6316_;
v___y_6304_ = v___y_6317_;
v___y_6305_ = v___y_6318_;
v___y_6306_ = v___y_6319_;
v___y_6307_ = v___y_6319_;
goto v___jp_6296_;
}
}
v___jp_6324_:
{
uint64_t v___x_6336_; uint8_t v___x_6337_; 
v___x_6336_ = lean_uint64_shift_right(v___y_6334_, v___y_6326_);
v___x_6337_ = lean_uint64_dec_eq(v___x_6336_, v___y_6327_);
if (v___x_6337_ == 0)
{
uint64_t v___x_6338_; 
v___x_6338_ = lean_uint64_add(v___y_6332_, v___y_6326_);
v___y_6312_ = v___y_6325_;
v___y_6313_ = v___y_6329_;
v___y_6314_ = v___y_6328_;
v___y_6315_ = v___y_6327_;
v___y_6316_ = v___y_6330_;
v___y_6317_ = v___y_6331_;
v___y_6318_ = v___y_6333_;
v___y_6319_ = v___y_6335_;
v___y_6320_ = v___x_6338_;
goto v___jp_6311_;
}
else
{
v___y_6312_ = v___y_6325_;
v___y_6313_ = v___y_6329_;
v___y_6314_ = v___y_6328_;
v___y_6315_ = v___y_6327_;
v___y_6316_ = v___y_6330_;
v___y_6317_ = v___y_6331_;
v___y_6318_ = v___y_6333_;
v___y_6319_ = v___y_6335_;
v___y_6320_ = v___y_6332_;
goto v___jp_6311_;
}
}
v___jp_6339_:
{
uint64_t v___x_6349_; uint64_t v___x_6350_; uint8_t v___x_6351_; 
v___x_6349_ = 16ULL;
v___x_6350_ = lean_uint64_shift_right(v___y_6347_, v___x_6349_);
v___x_6351_ = lean_uint64_dec_eq(v___x_6350_, v___y_6343_);
if (v___x_6351_ == 0)
{
v___y_6325_ = v___y_6340_;
v___y_6326_ = v___x_6349_;
v___y_6327_ = v___y_6343_;
v___y_6328_ = v___y_6342_;
v___y_6329_ = v___y_6341_;
v___y_6330_ = v___y_6344_;
v___y_6331_ = v___y_6345_;
v___y_6332_ = v___y_6348_;
v___y_6333_ = v___y_6346_;
v___y_6334_ = v___y_6347_;
v___y_6335_ = v___x_6350_;
goto v___jp_6324_;
}
else
{
v___y_6325_ = v___y_6340_;
v___y_6326_ = v___x_6349_;
v___y_6327_ = v___y_6343_;
v___y_6328_ = v___y_6342_;
v___y_6329_ = v___y_6341_;
v___y_6330_ = v___y_6344_;
v___y_6331_ = v___y_6345_;
v___y_6332_ = v___y_6348_;
v___y_6333_ = v___y_6346_;
v___y_6334_ = v___y_6347_;
v___y_6335_ = v___y_6347_;
goto v___jp_6324_;
}
}
v___jp_6352_:
{
uint64_t v___x_6362_; uint8_t v___x_6363_; 
v___x_6362_ = lean_uint64_shift_right(v___y_6355_, v___y_6359_);
v___x_6363_ = lean_uint64_dec_eq(v___x_6362_, v___y_6354_);
if (v___x_6363_ == 0)
{
v___y_6340_ = v___y_6353_;
v___y_6341_ = v___y_6356_;
v___y_6342_ = v___y_6355_;
v___y_6343_ = v___y_6354_;
v___y_6344_ = v___y_6357_;
v___y_6345_ = v___y_6358_;
v___y_6346_ = v___y_6360_;
v___y_6347_ = v___y_6361_;
v___y_6348_ = v___y_6359_;
goto v___jp_6339_;
}
else
{
v___y_6340_ = v___y_6353_;
v___y_6341_ = v___y_6356_;
v___y_6342_ = v___y_6355_;
v___y_6343_ = v___y_6354_;
v___y_6344_ = v___y_6357_;
v___y_6345_ = v___y_6358_;
v___y_6346_ = v___y_6360_;
v___y_6347_ = v___y_6361_;
v___y_6348_ = v___y_6354_;
goto v___jp_6339_;
}
}
v___jp_6364_:
{
uint64_t v___x_6371_; uint8_t v___x_6372_; 
v___x_6371_ = 0ULL;
v___x_6372_ = lean_uint64_dec_eq(v___y_6367_, v___x_6371_);
if (v___x_6372_ == 0)
{
uint64_t v___x_6373_; uint64_t v___x_6374_; uint8_t v___x_6375_; 
v___x_6373_ = 32ULL;
v___x_6374_ = lean_uint64_shift_right(v___y_6367_, v___x_6373_);
v___x_6375_ = lean_uint64_dec_eq(v___x_6374_, v___x_6371_);
if (v___x_6375_ == 0)
{
v___y_6353_ = v___y_6365_;
v___y_6354_ = v___x_6371_;
v___y_6355_ = v___y_6367_;
v___y_6356_ = v___y_6366_;
v___y_6357_ = v___y_6368_;
v___y_6358_ = v___y_6369_;
v___y_6359_ = v___x_6373_;
v___y_6360_ = v___y_6370_;
v___y_6361_ = v___x_6374_;
goto v___jp_6352_;
}
else
{
v___y_6353_ = v___y_6365_;
v___y_6354_ = v___x_6371_;
v___y_6355_ = v___y_6367_;
v___y_6356_ = v___y_6366_;
v___y_6357_ = v___y_6368_;
v___y_6358_ = v___y_6369_;
v___y_6359_ = v___x_6373_;
v___y_6360_ = v___y_6370_;
v___y_6361_ = v___y_6367_;
goto v___jp_6352_;
}
}
else
{
if (v___y_6368_ == 0)
{
uint32_t v___x_6376_; 
v___x_6376_ = 0;
v___y_6054_ = v___x_6376_;
goto v___jp_6053_;
}
else
{
uint32_t v___x_6377_; 
v___x_6377_ = 2147483648;
v___y_6054_ = v___x_6377_;
goto v___jp_6053_;
}
}
}
v___jp_6378_:
{
uint32_t v___x_6382_; uint32_t v___x_6383_; 
v___x_6382_ = lean_uint32_land(v___y_6380_, v___y_6379_);
v___x_6383_ = lean_uint32_lor(v___y_6381_, v___x_6382_);
v___y_6054_ = v___x_6383_;
goto v___jp_6053_;
}
v___jp_6384_:
{
uint8_t v___x_6389_; 
v___x_6389_ = lean_uint64_dec_eq(v___y_6388_, v___y_6387_);
if (v___x_6389_ == 0)
{
uint64_t v___x_6390_; uint8_t v___x_6391_; 
v___x_6390_ = 8388608ULL;
v___x_6391_ = lean_uint64_dec_eq(v___y_6388_, v___x_6390_);
if (v___x_6391_ == 0)
{
uint32_t v___x_6392_; 
v___x_6392_ = lean_uint64_to_uint32(v___y_6388_);
if (v___y_6386_ == 0)
{
uint32_t v___x_6393_; 
v___x_6393_ = 0;
v___y_6379_ = v___y_6385_;
v___y_6380_ = v___x_6392_;
v___y_6381_ = v___x_6393_;
goto v___jp_6378_;
}
else
{
uint32_t v___x_6394_; 
v___x_6394_ = 2147483648;
v___y_6379_ = v___y_6385_;
v___y_6380_ = v___x_6392_;
v___y_6381_ = v___x_6394_;
goto v___jp_6378_;
}
}
else
{
if (v___y_6386_ == 0)
{
uint32_t v___x_6395_; 
v___x_6395_ = 0;
v___y_6077_ = v___x_6395_;
goto v___jp_6076_;
}
else
{
uint32_t v___x_6396_; 
v___x_6396_ = 2147483648;
v___y_6077_ = v___x_6396_;
goto v___jp_6076_;
}
}
}
else
{
if (v___y_6386_ == 0)
{
uint32_t v___x_6397_; 
v___x_6397_ = 0;
v___y_6054_ = v___x_6397_;
goto v___jp_6053_;
}
else
{
uint32_t v___x_6398_; 
v___x_6398_ = 2147483648;
v___y_6054_ = v___x_6398_;
goto v___jp_6053_;
}
}
}
v___jp_6399_:
{
uint64_t v___x_6408_; uint64_t v___x_6409_; uint64_t v___x_6410_; uint8_t v___x_6411_; 
v___x_6408_ = lean_uint64_mul(v___y_6402_, v___y_6403_);
v___x_6409_ = lean_uint64_add(v___y_6406_, v___y_6407_);
v___x_6410_ = 281474976710656ULL;
v___x_6411_ = lean_uint64_dec_lt(v___x_6408_, v___x_6410_);
if (v___x_6411_ == 0)
{
v___y_6365_ = v___y_6400_;
v___y_6366_ = v___y_6401_;
v___y_6367_ = v___x_6408_;
v___y_6368_ = v___y_6404_;
v___y_6369_ = v___y_6405_;
v___y_6370_ = v___x_6409_;
goto v___jp_6364_;
}
else
{
uint64_t v___x_6412_; uint8_t v___x_6413_; 
v___x_6412_ = 123ULL;
v___x_6413_ = lean_uint64_dec_le(v___x_6409_, v___x_6412_);
if (v___x_6413_ == 0)
{
v___y_6365_ = v___y_6400_;
v___y_6366_ = v___y_6401_;
v___y_6367_ = v___x_6408_;
v___y_6368_ = v___y_6404_;
v___y_6369_ = v___y_6405_;
v___y_6370_ = v___x_6409_;
goto v___jp_6364_;
}
else
{
uint64_t v___x_6414_; uint8_t v___x_6415_; 
v___x_6414_ = 0ULL;
v___x_6415_ = lean_uint64_dec_eq(v___x_6408_, v___x_6414_);
if (v___x_6415_ == 0)
{
uint64_t v___x_6416_; uint64_t v___x_6417_; uint8_t v___x_6418_; 
v___x_6416_ = 149ULL;
v___x_6417_ = lean_uint64_sub(v___x_6416_, v___x_6409_);
v___x_6418_ = lean_uint64_dec_eq(v___x_6417_, v___x_6414_);
if (v___x_6418_ == 0)
{
uint64_t v___x_6419_; uint8_t v___x_6420_; 
v___x_6419_ = 64ULL;
v___x_6420_ = lean_uint64_dec_lt(v___x_6417_, v___x_6419_);
if (v___x_6420_ == 0)
{
uint8_t v___x_6421_; 
v___x_6421_ = lean_uint64_dec_eq(v___x_6417_, v___x_6419_);
if (v___x_6421_ == 0)
{
v___y_6385_ = v___y_6400_;
v___y_6386_ = v___y_6404_;
v___y_6387_ = v___x_6414_;
v___y_6388_ = v___x_6414_;
goto v___jp_6384_;
}
else
{
uint64_t v___x_6422_; uint8_t v___x_6423_; 
v___x_6422_ = 9223372036854775808ULL;
v___x_6423_ = lean_uint64_dec_lt(v___x_6422_, v___x_6408_);
if (v___x_6423_ == 0)
{
v___y_6385_ = v___y_6400_;
v___y_6386_ = v___y_6404_;
v___y_6387_ = v___x_6414_;
v___y_6388_ = v___x_6414_;
goto v___jp_6384_;
}
else
{
uint64_t v___x_6424_; 
v___x_6424_ = 1ULL;
v___y_6385_ = v___y_6400_;
v___y_6386_ = v___y_6404_;
v___y_6387_ = v___x_6414_;
v___y_6388_ = v___x_6424_;
goto v___jp_6384_;
}
}
}
else
{
uint64_t v_quotient_6425_; uint64_t v___x_6426_; uint64_t v___x_6427_; uint64_t v___x_6428_; uint64_t v_remainder_6429_; uint64_t v___x_6430_; uint64_t v_half_6431_; uint8_t v___x_6432_; 
v_quotient_6425_ = lean_uint64_shift_right(v___x_6408_, v___x_6417_);
v___x_6426_ = 1ULL;
v___x_6427_ = lean_uint64_shift_left(v___x_6426_, v___x_6417_);
v___x_6428_ = lean_uint64_sub(v___x_6427_, v___x_6426_);
v_remainder_6429_ = lean_uint64_land(v___x_6408_, v___x_6428_);
v___x_6430_ = lean_uint64_sub(v___x_6417_, v___x_6426_);
v_half_6431_ = lean_uint64_shift_left(v___x_6426_, v___x_6430_);
v___x_6432_ = lean_uint64_dec_lt(v_remainder_6429_, v_half_6431_);
if (v___x_6432_ == 0)
{
uint8_t v___x_6433_; 
v___x_6433_ = lean_uint64_dec_lt(v_half_6431_, v_remainder_6429_);
if (v___x_6433_ == 0)
{
uint64_t v___x_6434_; uint8_t v___x_6435_; 
v___x_6434_ = lean_uint64_land(v_quotient_6425_, v___x_6426_);
v___x_6435_ = lean_uint64_dec_eq(v___x_6434_, v___x_6414_);
if (v___x_6435_ == 0)
{
uint64_t v___x_6436_; 
v___x_6436_ = lean_uint64_add(v_quotient_6425_, v___x_6426_);
v___y_6385_ = v___y_6400_;
v___y_6386_ = v___y_6404_;
v___y_6387_ = v___x_6414_;
v___y_6388_ = v___x_6436_;
goto v___jp_6384_;
}
else
{
v___y_6385_ = v___y_6400_;
v___y_6386_ = v___y_6404_;
v___y_6387_ = v___x_6414_;
v___y_6388_ = v_quotient_6425_;
goto v___jp_6384_;
}
}
else
{
uint64_t v___x_6437_; 
v___x_6437_ = lean_uint64_add(v_quotient_6425_, v___x_6426_);
v___y_6385_ = v___y_6400_;
v___y_6386_ = v___y_6404_;
v___y_6387_ = v___x_6414_;
v___y_6388_ = v___x_6437_;
goto v___jp_6384_;
}
}
else
{
v___y_6385_ = v___y_6400_;
v___y_6386_ = v___y_6404_;
v___y_6387_ = v___x_6414_;
v___y_6388_ = v_quotient_6425_;
goto v___jp_6384_;
}
}
}
else
{
v___y_6385_ = v___y_6400_;
v___y_6386_ = v___y_6404_;
v___y_6387_ = v___x_6414_;
v___y_6388_ = v___x_6408_;
goto v___jp_6384_;
}
}
else
{
if (v___y_6404_ == 0)
{
uint32_t v___x_6438_; 
v___x_6438_ = 0;
v___y_6054_ = v___x_6438_;
goto v___jp_6053_;
}
else
{
uint32_t v___x_6439_; 
v___x_6439_ = 2147483648;
v___y_6054_ = v___x_6439_;
goto v___jp_6053_;
}
}
}
}
}
v___jp_6440_:
{
uint64_t v___x_6449_; uint64_t v___x_6450_; uint8_t v___x_6451_; 
v___x_6449_ = lean_uint32_to_uint64(v___y_6442_);
v___x_6450_ = 0ULL;
v___x_6451_ = lean_uint64_dec_eq(v___x_6449_, v___x_6450_);
if (v___x_6451_ == 0)
{
uint64_t v___x_6452_; uint64_t v___x_6453_; 
v___x_6452_ = 1ULL;
v___x_6453_ = lean_uint64_sub(v___x_6449_, v___x_6452_);
v___y_6400_ = v___y_6441_;
v___y_6401_ = v___y_6444_;
v___y_6402_ = v___y_6443_;
v___y_6403_ = v___y_6445_;
v___y_6404_ = v___y_6446_;
v___y_6405_ = v___y_6447_;
v___y_6406_ = v___y_6448_;
v___y_6407_ = v___x_6453_;
goto v___jp_6399_;
}
else
{
v___y_6400_ = v___y_6441_;
v___y_6401_ = v___y_6444_;
v___y_6402_ = v___y_6443_;
v___y_6403_ = v___y_6445_;
v___y_6404_ = v___y_6446_;
v___y_6405_ = v___y_6447_;
v___y_6406_ = v___y_6448_;
v___y_6407_ = v___x_6450_;
goto v___jp_6399_;
}
}
v___jp_6454_:
{
uint64_t v___x_6463_; uint64_t v___x_6464_; uint8_t v___x_6465_; 
v___x_6463_ = lean_uint32_to_uint64(v___y_6455_);
v___x_6464_ = 0ULL;
v___x_6465_ = lean_uint64_dec_eq(v___x_6463_, v___x_6464_);
if (v___x_6465_ == 0)
{
uint64_t v___x_6466_; uint64_t v___x_6467_; 
v___x_6466_ = 1ULL;
v___x_6467_ = lean_uint64_sub(v___x_6463_, v___x_6466_);
v___y_6441_ = v___y_6456_;
v___y_6442_ = v___y_6457_;
v___y_6443_ = v___y_6459_;
v___y_6444_ = v___y_6458_;
v___y_6445_ = v___y_6462_;
v___y_6446_ = v___y_6460_;
v___y_6447_ = v___y_6461_;
v___y_6448_ = v___x_6467_;
goto v___jp_6440_;
}
else
{
v___y_6441_ = v___y_6456_;
v___y_6442_ = v___y_6457_;
v___y_6443_ = v___y_6459_;
v___y_6444_ = v___y_6458_;
v___y_6445_ = v___y_6462_;
v___y_6446_ = v___y_6460_;
v___y_6447_ = v___y_6461_;
v___y_6448_ = v___x_6464_;
goto v___jp_6440_;
}
}
v___jp_6468_:
{
uint32_t v___x_6477_; uint8_t v___x_6478_; 
v___x_6477_ = 0;
v___x_6478_ = lean_uint32_dec_eq(v___y_6471_, v___x_6477_);
if (v___x_6478_ == 0)
{
uint64_t v___x_6479_; uint64_t v___x_6480_; uint64_t v___x_6481_; 
v___x_6479_ = lean_uint32_to_uint64(v___y_6474_);
v___x_6480_ = 8388608ULL;
v___x_6481_ = lean_uint64_lor(v___x_6479_, v___x_6480_);
v___y_6455_ = v___y_6469_;
v___y_6456_ = v___y_6470_;
v___y_6457_ = v___y_6471_;
v___y_6458_ = v___y_6472_;
v___y_6459_ = v___y_6476_;
v___y_6460_ = v___y_6473_;
v___y_6461_ = v___y_6475_;
v___y_6462_ = v___x_6481_;
goto v___jp_6454_;
}
else
{
uint64_t v___x_6482_; 
v___x_6482_ = lean_uint32_to_uint64(v___y_6474_);
v___y_6455_ = v___y_6469_;
v___y_6456_ = v___y_6470_;
v___y_6457_ = v___y_6471_;
v___y_6458_ = v___y_6472_;
v___y_6459_ = v___y_6476_;
v___y_6460_ = v___y_6473_;
v___y_6461_ = v___y_6475_;
v___y_6462_ = v___x_6482_;
goto v___jp_6454_;
}
}
v___jp_6483_:
{
uint32_t v___x_6491_; uint32_t v_xFraction_6492_; uint32_t v_yFraction_6493_; uint32_t v___x_6494_; uint8_t v___x_6495_; 
v___x_6491_ = 8388607;
v_xFraction_6492_ = lean_uint32_land(v___y_6487_, v___x_6491_);
v_yFraction_6493_ = lean_uint32_land(v___y_6489_, v___x_6491_);
v___x_6494_ = 0;
v___x_6495_ = lean_uint32_dec_eq(v___y_6484_, v___x_6494_);
if (v___x_6495_ == 0)
{
uint64_t v___x_6496_; uint64_t v___x_6497_; uint64_t v___x_6498_; 
v___x_6496_ = lean_uint32_to_uint64(v_xFraction_6492_);
v___x_6497_ = 8388608ULL;
v___x_6498_ = lean_uint64_lor(v___x_6496_, v___x_6497_);
v___y_6469_ = v___y_6484_;
v___y_6470_ = v___x_6491_;
v___y_6471_ = v___y_6485_;
v___y_6472_ = v___y_6486_;
v___y_6473_ = v___y_6490_;
v___y_6474_ = v_yFraction_6493_;
v___y_6475_ = v___y_6488_;
v___y_6476_ = v___x_6498_;
goto v___jp_6468_;
}
else
{
uint64_t v___x_6499_; 
v___x_6499_ = lean_uint32_to_uint64(v_xFraction_6492_);
v___y_6469_ = v___y_6484_;
v___y_6470_ = v___x_6491_;
v___y_6471_ = v___y_6485_;
v___y_6472_ = v___y_6486_;
v___y_6473_ = v___y_6490_;
v___y_6474_ = v_yFraction_6493_;
v___y_6475_ = v___y_6488_;
v___y_6476_ = v___x_6499_;
goto v___jp_6468_;
}
}
v___jp_6500_:
{
float v___x_6503_; float v___x_6504_; float v___x_6505_; uint32_t v___x_6506_; 
v___x_6503_ = lean_float32_of_bits(v___y_6501_);
v___x_6504_ = lean_float32_of_bits(v___y_6502_);
v___x_6505_ = lean_float32_mul(v___x_6503_, v___x_6504_);
v___x_6506_ = lean_float32_to_bits(v___x_6505_);
v___y_6054_ = v___x_6506_;
goto v___jp_6053_;
}
v___jp_6507_:
{
if (v___y_6513_ == 0)
{
uint32_t v___x_6514_; 
v___x_6514_ = lp_competition_Submission_FastMul_mul(v___y_6510_, v___y_6512_);
v___y_6054_ = v___x_6514_;
goto v___jp_6053_;
}
else
{
uint8_t v___x_6515_; 
v___x_6515_ = lean_uint32_dec_eq(v___y_6508_, v___y_6509_);
if (v___x_6515_ == 0)
{
v___y_6501_ = v___y_6510_;
v___y_6502_ = v___y_6512_;
goto v___jp_6500_;
}
else
{
if (v___y_6511_ == 0)
{
uint32_t v___x_6516_; 
v___x_6516_ = lp_competition_Submission_FastMul_mul(v___y_6510_, v___y_6512_);
v___y_6054_ = v___x_6516_;
goto v___jp_6053_;
}
else
{
v___y_6501_ = v___y_6510_;
v___y_6502_ = v___y_6512_;
goto v___jp_6500_;
}
}
}
}
v___jp_6517_:
{
if (v___y_6525_ == 0)
{
v___y_6484_ = v___y_6518_;
v___y_6485_ = v___y_6519_;
v___y_6486_ = v___y_6520_;
v___y_6487_ = v___y_6522_;
v___y_6488_ = v___y_6523_;
v___y_6489_ = v___y_6524_;
v___y_6490_ = v___x_6052_;
goto v___jp_6483_;
}
else
{
v___y_6484_ = v___y_6518_;
v___y_6485_ = v___y_6519_;
v___y_6486_ = v___y_6520_;
v___y_6487_ = v___y_6522_;
v___y_6488_ = v___y_6523_;
v___y_6489_ = v___y_6524_;
v___y_6490_ = v___y_6521_;
goto v___jp_6483_;
}
}
v___jp_6526_:
{
if (v___y_6532_ == 0)
{
if (v___y_6535_ == 0)
{
v___y_6518_ = v___y_6527_;
v___y_6519_ = v___y_6528_;
v___y_6520_ = v___y_6529_;
v___y_6521_ = v___y_6530_;
v___y_6522_ = v___y_6531_;
v___y_6523_ = v___y_6533_;
v___y_6524_ = v___y_6534_;
v___y_6525_ = v___x_6052_;
goto v___jp_6517_;
}
else
{
v___y_6484_ = v___y_6527_;
v___y_6485_ = v___y_6528_;
v___y_6486_ = v___y_6529_;
v___y_6487_ = v___y_6531_;
v___y_6488_ = v___y_6533_;
v___y_6489_ = v___y_6534_;
v___y_6490_ = v___x_6052_;
goto v___jp_6483_;
}
}
else
{
v___y_6518_ = v___y_6527_;
v___y_6519_ = v___y_6528_;
v___y_6520_ = v___y_6529_;
v___y_6521_ = v___y_6530_;
v___y_6522_ = v___y_6531_;
v___y_6523_ = v___y_6533_;
v___y_6524_ = v___y_6534_;
v___y_6525_ = v___y_6535_;
goto v___jp_6517_;
}
}
v___jp_6536_:
{
uint32_t v___x_6545_; uint32_t v___x_6546_; uint32_t v___x_6547_; uint8_t v___x_6548_; 
v___x_6545_ = 2147483648;
v___x_6546_ = lean_uint32_land(v___y_6543_, v___x_6545_);
v___x_6547_ = 0;
v___x_6548_ = lean_uint32_dec_eq(v___x_6546_, v___x_6547_);
if (v___x_6548_ == 0)
{
v___y_6527_ = v___y_6537_;
v___y_6528_ = v___y_6538_;
v___y_6529_ = v___y_6539_;
v___y_6530_ = v___y_6540_;
v___y_6531_ = v___y_6541_;
v___y_6532_ = v___y_6544_;
v___y_6533_ = v___y_6542_;
v___y_6534_ = v___y_6543_;
v___y_6535_ = v___x_6052_;
goto v___jp_6526_;
}
else
{
v___y_6527_ = v___y_6537_;
v___y_6528_ = v___y_6538_;
v___y_6529_ = v___y_6539_;
v___y_6530_ = v___y_6540_;
v___y_6531_ = v___y_6541_;
v___y_6532_ = v___y_6544_;
v___y_6533_ = v___y_6542_;
v___y_6534_ = v___y_6543_;
v___y_6535_ = v___y_6540_;
goto v___jp_6526_;
}
}
v___jp_6549_:
{
if (v___y_6556_ == 0)
{
uint32_t v___x_6557_; uint32_t v___x_6558_; uint32_t v___x_6559_; uint8_t v___x_6560_; 
v___x_6557_ = 2147483648;
v___x_6558_ = lean_uint32_land(v___y_6553_, v___x_6557_);
v___x_6559_ = 0;
v___x_6560_ = lean_uint32_dec_eq(v___x_6558_, v___x_6559_);
if (v___x_6560_ == 0)
{
v___y_6537_ = v___y_6550_;
v___y_6538_ = v___y_6551_;
v___y_6539_ = v___y_6552_;
v___y_6540_ = v___y_6556_;
v___y_6541_ = v___y_6553_;
v___y_6542_ = v___y_6554_;
v___y_6543_ = v___y_6555_;
v___y_6544_ = v___x_6052_;
goto v___jp_6536_;
}
else
{
v___y_6537_ = v___y_6550_;
v___y_6538_ = v___y_6551_;
v___y_6539_ = v___y_6552_;
v___y_6540_ = v___y_6556_;
v___y_6541_ = v___y_6553_;
v___y_6542_ = v___y_6554_;
v___y_6543_ = v___y_6555_;
v___y_6544_ = v___y_6556_;
goto v___jp_6536_;
}
}
else
{
lean_object* v___x_6561_; lean_object* v___x_6562_; lean_object* v___x_6563_; uint32_t v___x_6564_; 
v___x_6561_ = lean_uint32_to_nat(v___y_6553_);
v___x_6562_ = lean_uint32_to_nat(v___y_6555_);
v___x_6563_ = lp_floatlib_FloatLib_Floats_Formats_BinaryInterchange_Model_MulBackend_word___at___00FloatLib_Floats_Formats_BinaryInterchange_Configured_Plan_softwareMul32Certified_spec__1(v___x_6561_, v___x_6562_);
v___x_6564_ = lean_uint32_of_nat(v___x_6563_);
lean_dec(v___x_6563_);
v___y_6054_ = v___x_6564_;
goto v___jp_6053_;
}
}
v___jp_6565_:
{
uint32_t v___x_6568_; uint32_t v___x_6569_; uint32_t v___x_6570_; uint32_t v_ex_6571_; uint32_t v___x_6572_; uint32_t v_ey_6573_; uint32_t v___x_6574_; uint32_t v___x_6575_; uint8_t v___x_6576_; 
v___x_6568_ = 23;
v___x_6569_ = lean_uint32_shift_right(v___y_6566_, v___x_6568_);
v___x_6570_ = 255;
v_ex_6571_ = lean_uint32_land(v___x_6569_, v___x_6570_);
v___x_6572_ = lean_uint32_shift_right(v___y_6567_, v___x_6568_);
v_ey_6573_ = lean_uint32_land(v___x_6572_, v___x_6570_);
v___x_6574_ = lean_uint32_add(v_ex_6571_, v_ey_6573_);
v___x_6575_ = 128;
v___x_6576_ = lean_uint32_dec_lt(v___x_6574_, v___x_6575_);
if (v___x_6576_ == 0)
{
uint8_t v___x_6577_; 
v___x_6577_ = lean_uint32_dec_eq(v_ex_6571_, v___x_6570_);
if (v___x_6577_ == 0)
{
v___y_6508_ = v_ey_6573_;
v___y_6509_ = v___x_6570_;
v___y_6510_ = v___y_6566_;
v___y_6511_ = v___x_6576_;
v___y_6512_ = v___y_6567_;
v___y_6513_ = v___x_6052_;
goto v___jp_6507_;
}
else
{
v___y_6508_ = v_ey_6573_;
v___y_6509_ = v___x_6570_;
v___y_6510_ = v___y_6566_;
v___y_6511_ = v___x_6576_;
v___y_6512_ = v___y_6567_;
v___y_6513_ = v___x_6576_;
goto v___jp_6507_;
}
}
else
{
uint32_t v___x_6578_; uint32_t v___x_6579_; uint32_t v___x_6580_; uint8_t v___x_6581_; 
v___x_6578_ = 4278190080;
v___x_6579_ = 1;
v___x_6580_ = lean_uint32_shift_left(v___y_6566_, v___x_6579_);
v___x_6581_ = lean_uint32_dec_le(v___x_6578_, v___x_6580_);
if (v___x_6581_ == 0)
{
uint32_t v___x_6582_; uint8_t v___x_6583_; 
v___x_6582_ = lean_uint32_shift_left(v___y_6567_, v___x_6579_);
v___x_6583_ = lean_uint32_dec_le(v___x_6578_, v___x_6582_);
v___y_6550_ = v_ex_6571_;
v___y_6551_ = v_ey_6573_;
v___y_6552_ = v___x_6570_;
v___y_6553_ = v___y_6566_;
v___y_6554_ = v___x_6568_;
v___y_6555_ = v___y_6567_;
v___y_6556_ = v___x_6583_;
goto v___jp_6549_;
}
else
{
v___y_6550_ = v_ex_6571_;
v___y_6551_ = v_ey_6573_;
v___y_6552_ = v___x_6570_;
v___y_6553_ = v___y_6566_;
v___y_6554_ = v___x_6568_;
v___y_6555_ = v___y_6567_;
v___y_6556_ = v___x_6581_;
goto v___jp_6549_;
}
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_Fin_foldl_loop___at___00Submission_NativeFinal_dot_spec__0___boxed(lean_object* v_baseA_6598_, lean_object* v_p_6599_, lean_object* v_baseB_6600_, lean_object* v_B_6601_, lean_object* v_A_6602_, lean_object* v_n_6603_, lean_object* v_x_6604_, lean_object* v_i_6605_){
_start:
{
uint32_t v_x_boxed_6606_; uint32_t v_res_6607_; lean_object* v_r_6608_; 
v_x_boxed_6606_ = lean_unbox_uint32(v_x_6604_);
lean_dec(v_x_6604_);
v_res_6607_ = lp_competition_Fin_foldl_loop___at___00Submission_NativeFinal_dot_spec__0(v_baseA_6598_, v_p_6599_, v_baseB_6600_, v_B_6601_, v_A_6602_, v_n_6603_, v_x_boxed_6606_, v_i_6605_);
lean_dec(v_n_6603_);
lean_dec_ref(v_A_6602_);
lean_dec_ref(v_B_6601_);
lean_dec(v_baseB_6600_);
lean_dec(v_p_6599_);
lean_dec(v_baseA_6598_);
v_r_6608_ = lean_box_uint32(v_res_6607_);
return v_r_6608_;
}
}
static float _init_lp_competition_Submission_NativeFinal_dot___closed__0(void){
_start:
{
uint32_t v___x_6609_; float v___x_6610_; 
v___x_6609_ = 0;
v___x_6610_ = lean_float32_of_bits(v___x_6609_);
return v___x_6610_;
}
}
LEAN_EXPORT uint32_t lp_competition_Submission_NativeFinal_dot(lean_object* v_n_6611_, lean_object* v_baseA_6612_, lean_object* v_baseB_6613_, lean_object* v_p_6614_, lean_object* v_A_6615_, lean_object* v_B_6616_){
_start:
{
lean_object* v___x_6617_; float v___x_6618_; float v_result_6619_; uint8_t v___x_6620_; 
v___x_6617_ = lean_unsigned_to_nat(0u);
v___x_6618_ = lean_float32_once(&lp_competition_Submission_NativeFinal_dot___closed__0, &lp_competition_Submission_NativeFinal_dot___closed__0_once, _init_lp_competition_Submission_NativeFinal_dot___closed__0);
v_result_6619_ = lp_competition_Submission_NativeFinal_dotLoop(v_n_6611_, v_baseA_6612_, v_baseB_6613_, v_p_6614_, v_A_6615_, v_B_6616_, v___x_6617_, v___x_6618_);
v___x_6620_ = lean_float32_isfinite(v_result_6619_);
if (v___x_6620_ == 0)
{
uint32_t v___x_6621_; uint32_t v___x_6622_; 
v___x_6621_ = lean_uint32_once(&lp_competition_Submission_referenceSum___redArg___closed__1, &lp_competition_Submission_referenceSum___redArg___closed__1_once, _init_lp_competition_Submission_referenceSum___redArg___closed__1);
v___x_6622_ = lp_competition_Fin_foldl_loop___at___00Submission_NativeFinal_dot_spec__0(v_baseA_6612_, v_p_6614_, v_baseB_6613_, v_B_6616_, v_A_6615_, v_n_6611_, v___x_6621_, v___x_6617_);
return v___x_6622_;
}
else
{
uint32_t v___x_6623_; 
v___x_6623_ = lean_float32_to_bits(v_result_6619_);
return v___x_6623_;
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_NativeFinal_dot___boxed(lean_object* v_n_6624_, lean_object* v_baseA_6625_, lean_object* v_baseB_6626_, lean_object* v_p_6627_, lean_object* v_A_6628_, lean_object* v_B_6629_){
_start:
{
uint32_t v_res_6630_; lean_object* v_r_6631_; 
v_res_6630_ = lp_competition_Submission_NativeFinal_dot(v_n_6624_, v_baseA_6625_, v_baseB_6626_, v_p_6627_, v_A_6628_, v_B_6629_);
lean_dec_ref(v_B_6629_);
lean_dec_ref(v_A_6628_);
lean_dec(v_p_6627_);
lean_dec(v_baseB_6626_);
lean_dec(v_baseA_6625_);
lean_dec(v_n_6624_);
v_r_6631_ = lean_box_uint32(v_res_6630_);
return v_r_6631_;
}
}
LEAN_EXPORT uint32_t lp_competition_Submission_originalSum(lean_object* v_n_6632_, lean_object* v_x_6633_){
_start:
{
lean_object* v___x_6634_; float v___x_6635_; float v_result_6636_; uint8_t v___x_6637_; 
v___x_6634_ = lean_unsigned_to_nat(0u);
v___x_6635_ = lean_float32_once(&lp_competition_Submission_NativeFinal_dot___closed__0, &lp_competition_Submission_NativeFinal_dot___closed__0_once, _init_lp_competition_Submission_NativeFinal_dot___closed__0);
v_result_6636_ = lp_competition_Submission_NativeFinal_sumLoop(v_n_6632_, v_x_6633_, v___x_6634_, v___x_6635_);
v___x_6637_ = lean_float32_isfinite(v_result_6636_);
if (v___x_6637_ == 0)
{
uint32_t v___x_6638_; 
v___x_6638_ = lp_competition_Submission_referenceSum___redArg(v_x_6633_);
return v___x_6638_;
}
else
{
uint32_t v___x_6639_; 
v___x_6639_ = lean_float32_to_bits(v_result_6636_);
return v___x_6639_;
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_originalSum___boxed(lean_object* v_n_6640_, lean_object* v_x_6641_){
_start:
{
uint32_t v_res_6642_; lean_object* v_r_6643_; 
v_res_6642_ = lp_competition_Submission_originalSum(v_n_6640_, v_x_6641_);
lean_dec_ref(v_x_6641_);
lean_dec(v_n_6640_);
v_r_6643_ = lean_box_uint32(v_res_6642_);
return v_r_6643_;
}
}
static float _init_lp_competition_Submission_Packed10_zero32(void){
_start:
{
float v___x_6644_; 
v___x_6644_ = lean_float32_once(&lp_competition_Submission_NativeFinal_dot___closed__0, &lp_competition_Submission_NativeFinal_dot___closed__0_once, _init_lp_competition_Submission_NativeFinal_dot___closed__0);
return v___x_6644_;
}
}
static lean_object* _init_lp_competition_Submission_Packed10_zero10___closed__0(void){
_start:
{
float v___x_6645_; lean_object* v___x_6646_; 
v___x_6645_ = lean_float32_once(&lp_competition_Submission_NativeFinal_dot___closed__0, &lp_competition_Submission_NativeFinal_dot___closed__0_once, _init_lp_competition_Submission_NativeFinal_dot___closed__0);
v___x_6646_ = lean_alloc_ctor(0, 0, 40);
lean_ctor_set_float32(v___x_6646_, 0, v___x_6645_);
lean_ctor_set_float32(v___x_6646_, 4, v___x_6645_);
lean_ctor_set_float32(v___x_6646_, 8, v___x_6645_);
lean_ctor_set_float32(v___x_6646_, 12, v___x_6645_);
lean_ctor_set_float32(v___x_6646_, 16, v___x_6645_);
lean_ctor_set_float32(v___x_6646_, 20, v___x_6645_);
lean_ctor_set_float32(v___x_6646_, 24, v___x_6645_);
lean_ctor_set_float32(v___x_6646_, 28, v___x_6645_);
lean_ctor_set_float32(v___x_6646_, 32, v___x_6645_);
lean_ctor_set_float32(v___x_6646_, 36, v___x_6645_);
return v___x_6646_;
}
}
static lean_object* _init_lp_competition_Submission_Packed10_zero10(void){
_start:
{
lean_object* v___x_6647_; 
v___x_6647_ = lean_obj_once(&lp_competition_Submission_Packed10_zero10___closed__0, &lp_competition_Submission_Packed10_zero10___closed__0_once, _init_lp_competition_Submission_Packed10_zero10___closed__0);
return v___x_6647_;
}
}
LEAN_EXPORT float lp_competition_Submission_Packed10_lane(lean_object* v_v_6648_, lean_object* v_l_6649_){
_start:
{
lean_object* v___x_6650_; uint8_t v___x_6651_; 
v___x_6650_ = lean_unsigned_to_nat(0u);
v___x_6651_ = lean_nat_dec_eq(v_l_6649_, v___x_6650_);
if (v___x_6651_ == 0)
{
lean_object* v___x_6652_; uint8_t v___x_6653_; 
v___x_6652_ = lean_unsigned_to_nat(1u);
v___x_6653_ = lean_nat_dec_eq(v_l_6649_, v___x_6652_);
if (v___x_6653_ == 0)
{
lean_object* v___x_6654_; uint8_t v___x_6655_; 
v___x_6654_ = lean_unsigned_to_nat(2u);
v___x_6655_ = lean_nat_dec_eq(v_l_6649_, v___x_6654_);
if (v___x_6655_ == 0)
{
lean_object* v___x_6656_; uint8_t v___x_6657_; 
v___x_6656_ = lean_unsigned_to_nat(3u);
v___x_6657_ = lean_nat_dec_eq(v_l_6649_, v___x_6656_);
if (v___x_6657_ == 0)
{
lean_object* v___x_6658_; uint8_t v___x_6659_; 
v___x_6658_ = lean_unsigned_to_nat(4u);
v___x_6659_ = lean_nat_dec_eq(v_l_6649_, v___x_6658_);
if (v___x_6659_ == 0)
{
lean_object* v___x_6660_; uint8_t v___x_6661_; 
v___x_6660_ = lean_unsigned_to_nat(5u);
v___x_6661_ = lean_nat_dec_eq(v_l_6649_, v___x_6660_);
if (v___x_6661_ == 0)
{
lean_object* v___x_6662_; uint8_t v___x_6663_; 
v___x_6662_ = lean_unsigned_to_nat(6u);
v___x_6663_ = lean_nat_dec_eq(v_l_6649_, v___x_6662_);
if (v___x_6663_ == 0)
{
lean_object* v___x_6664_; uint8_t v___x_6665_; 
v___x_6664_ = lean_unsigned_to_nat(7u);
v___x_6665_ = lean_nat_dec_eq(v_l_6649_, v___x_6664_);
if (v___x_6665_ == 0)
{
lean_object* v___x_6666_; uint8_t v___x_6667_; 
v___x_6666_ = lean_unsigned_to_nat(8u);
v___x_6667_ = lean_nat_dec_eq(v_l_6649_, v___x_6666_);
if (v___x_6667_ == 0)
{
float v_s9_6668_; 
v_s9_6668_ = lean_ctor_get_float32(v_v_6648_, 36);
return v_s9_6668_;
}
else
{
float v_s8_6669_; 
v_s8_6669_ = lean_ctor_get_float32(v_v_6648_, 32);
return v_s8_6669_;
}
}
else
{
float v_s7_6670_; 
v_s7_6670_ = lean_ctor_get_float32(v_v_6648_, 28);
return v_s7_6670_;
}
}
else
{
float v_s6_6671_; 
v_s6_6671_ = lean_ctor_get_float32(v_v_6648_, 24);
return v_s6_6671_;
}
}
else
{
float v_s5_6672_; 
v_s5_6672_ = lean_ctor_get_float32(v_v_6648_, 20);
return v_s5_6672_;
}
}
else
{
float v_s4_6673_; 
v_s4_6673_ = lean_ctor_get_float32(v_v_6648_, 16);
return v_s4_6673_;
}
}
else
{
float v_s3_6674_; 
v_s3_6674_ = lean_ctor_get_float32(v_v_6648_, 12);
return v_s3_6674_;
}
}
else
{
float v_s2_6675_; 
v_s2_6675_ = lean_ctor_get_float32(v_v_6648_, 8);
return v_s2_6675_;
}
}
else
{
float v_s1_6676_; 
v_s1_6676_ = lean_ctor_get_float32(v_v_6648_, 4);
return v_s1_6676_;
}
}
else
{
float v_s0_6677_; 
v_s0_6677_ = lean_ctor_get_float32(v_v_6648_, 0);
return v_s0_6677_;
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_Packed10_lane___boxed(lean_object* v_v_6678_, lean_object* v_l_6679_){
_start:
{
float v_res_6680_; lean_object* v_r_6681_; 
v_res_6680_ = lp_competition_Submission_Packed10_lane(v_v_6678_, v_l_6679_);
lean_dec(v_l_6679_);
lean_dec_ref(v_v_6678_);
v_r_6681_ = lean_box_float32(v_res_6680_);
return v_r_6681_;
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_Packed10_packet(lean_object* v_read_6682_, lean_object* v_col_6683_){
_start:
{
lean_object* v___x_6684_; lean_object* v___x_6685_; lean_object* v___x_6686_; lean_object* v___x_6687_; lean_object* v___x_6688_; lean_object* v___x_6689_; lean_object* v___x_6690_; lean_object* v___x_6691_; lean_object* v___x_6692_; lean_object* v___x_6693_; lean_object* v___x_6694_; lean_object* v___x_6695_; lean_object* v___x_6696_; lean_object* v___x_6697_; lean_object* v___x_6698_; lean_object* v___x_6699_; lean_object* v___x_6700_; lean_object* v___x_6701_; lean_object* v___x_6702_; lean_object* v___x_6703_; lean_object* v___x_6704_; lean_object* v___x_6705_; lean_object* v___x_6706_; lean_object* v___x_6707_; lean_object* v___x_6708_; lean_object* v___x_6709_; lean_object* v___x_6710_; lean_object* v___x_6711_; lean_object* v___x_6712_; float v___x_6713_; float v___x_6714_; float v___x_6715_; float v___x_6716_; float v___x_6717_; float v___x_6718_; float v___x_6719_; float v___x_6720_; float v___x_6721_; float v___x_6722_; 
lean_inc_ref_n(v_read_6682_, 9);
lean_inc(v_col_6683_);
v___x_6684_ = lean_apply_1(v_read_6682_, v_col_6683_);
v___x_6685_ = lean_unsigned_to_nat(1u);
v___x_6686_ = lean_nat_add(v_col_6683_, v___x_6685_);
v___x_6687_ = lean_apply_1(v_read_6682_, v___x_6686_);
v___x_6688_ = lean_unsigned_to_nat(2u);
v___x_6689_ = lean_nat_add(v_col_6683_, v___x_6688_);
v___x_6690_ = lean_apply_1(v_read_6682_, v___x_6689_);
v___x_6691_ = lean_unsigned_to_nat(3u);
v___x_6692_ = lean_nat_add(v_col_6683_, v___x_6691_);
v___x_6693_ = lean_apply_1(v_read_6682_, v___x_6692_);
v___x_6694_ = lean_unsigned_to_nat(4u);
v___x_6695_ = lean_nat_add(v_col_6683_, v___x_6694_);
v___x_6696_ = lean_apply_1(v_read_6682_, v___x_6695_);
v___x_6697_ = lean_unsigned_to_nat(5u);
v___x_6698_ = lean_nat_add(v_col_6683_, v___x_6697_);
v___x_6699_ = lean_apply_1(v_read_6682_, v___x_6698_);
v___x_6700_ = lean_unsigned_to_nat(6u);
v___x_6701_ = lean_nat_add(v_col_6683_, v___x_6700_);
v___x_6702_ = lean_apply_1(v_read_6682_, v___x_6701_);
v___x_6703_ = lean_unsigned_to_nat(7u);
v___x_6704_ = lean_nat_add(v_col_6683_, v___x_6703_);
v___x_6705_ = lean_apply_1(v_read_6682_, v___x_6704_);
v___x_6706_ = lean_unsigned_to_nat(8u);
v___x_6707_ = lean_nat_add(v_col_6683_, v___x_6706_);
v___x_6708_ = lean_apply_1(v_read_6682_, v___x_6707_);
v___x_6709_ = lean_unsigned_to_nat(9u);
v___x_6710_ = lean_nat_add(v_col_6683_, v___x_6709_);
lean_dec(v_col_6683_);
v___x_6711_ = lean_apply_1(v_read_6682_, v___x_6710_);
v___x_6712_ = lean_alloc_ctor(0, 0, 40);
v___x_6713_ = lean_unbox_float32(v___x_6684_);
lean_dec_ref(v___x_6684_);
lean_ctor_set_float32(v___x_6712_, 0, v___x_6713_);
v___x_6714_ = lean_unbox_float32(v___x_6687_);
lean_dec_ref(v___x_6687_);
lean_ctor_set_float32(v___x_6712_, 4, v___x_6714_);
v___x_6715_ = lean_unbox_float32(v___x_6690_);
lean_dec_ref(v___x_6690_);
lean_ctor_set_float32(v___x_6712_, 8, v___x_6715_);
v___x_6716_ = lean_unbox_float32(v___x_6693_);
lean_dec_ref(v___x_6693_);
lean_ctor_set_float32(v___x_6712_, 12, v___x_6716_);
v___x_6717_ = lean_unbox_float32(v___x_6696_);
lean_dec_ref(v___x_6696_);
lean_ctor_set_float32(v___x_6712_, 16, v___x_6717_);
v___x_6718_ = lean_unbox_float32(v___x_6699_);
lean_dec_ref(v___x_6699_);
lean_ctor_set_float32(v___x_6712_, 20, v___x_6718_);
v___x_6719_ = lean_unbox_float32(v___x_6702_);
lean_dec_ref(v___x_6702_);
lean_ctor_set_float32(v___x_6712_, 24, v___x_6719_);
v___x_6720_ = lean_unbox_float32(v___x_6705_);
lean_dec_ref(v___x_6705_);
lean_ctor_set_float32(v___x_6712_, 28, v___x_6720_);
v___x_6721_ = lean_unbox_float32(v___x_6708_);
lean_dec_ref(v___x_6708_);
lean_ctor_set_float32(v___x_6712_, 32, v___x_6721_);
v___x_6722_ = lean_unbox_float32(v___x_6711_);
lean_dec_ref(v___x_6711_);
lean_ctor_set_float32(v___x_6712_, 36, v___x_6722_);
return v___x_6712_;
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_Packed10_update(lean_object* v_acc_6723_, float v_a_6724_, lean_object* v_v_6725_){
_start:
{
float v_s0_6726_; float v_s1_6727_; float v_s2_6728_; float v_s3_6729_; float v_s4_6730_; float v_s5_6731_; float v_s6_6732_; float v_s7_6733_; float v_s8_6734_; float v_s9_6735_; float v_s0_6736_; float v_s1_6737_; float v_s2_6738_; float v_s3_6739_; float v_s4_6740_; float v_s5_6741_; float v_s6_6742_; float v_s7_6743_; float v_s8_6744_; float v_s9_6745_; lean_object* v___x_6747_; uint8_t v_isShared_6748_; uint8_t v_isSharedCheck_6772_; 
v_s0_6726_ = lean_ctor_get_float32(v_acc_6723_, 0);
v_s1_6727_ = lean_ctor_get_float32(v_acc_6723_, 4);
v_s2_6728_ = lean_ctor_get_float32(v_acc_6723_, 8);
v_s3_6729_ = lean_ctor_get_float32(v_acc_6723_, 12);
v_s4_6730_ = lean_ctor_get_float32(v_acc_6723_, 16);
v_s5_6731_ = lean_ctor_get_float32(v_acc_6723_, 20);
v_s6_6732_ = lean_ctor_get_float32(v_acc_6723_, 24);
v_s7_6733_ = lean_ctor_get_float32(v_acc_6723_, 28);
v_s8_6734_ = lean_ctor_get_float32(v_acc_6723_, 32);
v_s9_6735_ = lean_ctor_get_float32(v_acc_6723_, 36);
v_s0_6736_ = lean_ctor_get_float32(v_v_6725_, 0);
v_s1_6737_ = lean_ctor_get_float32(v_v_6725_, 4);
v_s2_6738_ = lean_ctor_get_float32(v_v_6725_, 8);
v_s3_6739_ = lean_ctor_get_float32(v_v_6725_, 12);
v_s4_6740_ = lean_ctor_get_float32(v_v_6725_, 16);
v_s5_6741_ = lean_ctor_get_float32(v_v_6725_, 20);
v_s6_6742_ = lean_ctor_get_float32(v_v_6725_, 24);
v_s7_6743_ = lean_ctor_get_float32(v_v_6725_, 28);
v_s8_6744_ = lean_ctor_get_float32(v_v_6725_, 32);
v_s9_6745_ = lean_ctor_get_float32(v_v_6725_, 36);
v_isSharedCheck_6772_ = !lean_is_exclusive(v_v_6725_);
if (v_isSharedCheck_6772_ == 0)
{
v___x_6747_ = v_v_6725_;
v_isShared_6748_ = v_isSharedCheck_6772_;
goto v_resetjp_6746_;
}
else
{
lean_dec(v_v_6725_);
v___x_6747_ = lean_box(0);
v_isShared_6748_ = v_isSharedCheck_6772_;
goto v_resetjp_6746_;
}
v_resetjp_6746_:
{
float v___x_6749_; float v___x_6750_; float v___x_6751_; float v___x_6752_; float v___x_6753_; float v___x_6754_; float v___x_6755_; float v___x_6756_; float v___x_6757_; float v___x_6758_; float v___x_6759_; float v___x_6760_; float v___x_6761_; float v___x_6762_; float v___x_6763_; float v___x_6764_; float v___x_6765_; float v___x_6766_; float v___x_6767_; float v___x_6768_; lean_object* v___x_6770_; 
v___x_6749_ = lean_float32_mul(v_a_6724_, v_s0_6736_);
v___x_6750_ = lean_float32_add(v_s0_6726_, v___x_6749_);
v___x_6751_ = lean_float32_mul(v_a_6724_, v_s1_6737_);
v___x_6752_ = lean_float32_add(v_s1_6727_, v___x_6751_);
v___x_6753_ = lean_float32_mul(v_a_6724_, v_s2_6738_);
v___x_6754_ = lean_float32_add(v_s2_6728_, v___x_6753_);
v___x_6755_ = lean_float32_mul(v_a_6724_, v_s3_6739_);
v___x_6756_ = lean_float32_add(v_s3_6729_, v___x_6755_);
v___x_6757_ = lean_float32_mul(v_a_6724_, v_s4_6740_);
v___x_6758_ = lean_float32_add(v_s4_6730_, v___x_6757_);
v___x_6759_ = lean_float32_mul(v_a_6724_, v_s5_6741_);
v___x_6760_ = lean_float32_add(v_s5_6731_, v___x_6759_);
v___x_6761_ = lean_float32_mul(v_a_6724_, v_s6_6742_);
v___x_6762_ = lean_float32_add(v_s6_6732_, v___x_6761_);
v___x_6763_ = lean_float32_mul(v_a_6724_, v_s7_6743_);
v___x_6764_ = lean_float32_add(v_s7_6733_, v___x_6763_);
v___x_6765_ = lean_float32_mul(v_a_6724_, v_s8_6744_);
v___x_6766_ = lean_float32_add(v_s8_6734_, v___x_6765_);
v___x_6767_ = lean_float32_mul(v_a_6724_, v_s9_6745_);
v___x_6768_ = lean_float32_add(v_s9_6735_, v___x_6767_);
if (v_isShared_6748_ == 0)
{
v___x_6770_ = v___x_6747_;
goto v_reusejp_6769_;
}
else
{
lean_object* v_reuseFailAlloc_6771_; 
v_reuseFailAlloc_6771_ = lean_alloc_ctor(0, 0, 40);
v___x_6770_ = v_reuseFailAlloc_6771_;
goto v_reusejp_6769_;
}
v_reusejp_6769_:
{
lean_ctor_set_float32(v___x_6770_, 0, v___x_6750_);
lean_ctor_set_float32(v___x_6770_, 4, v___x_6752_);
lean_ctor_set_float32(v___x_6770_, 8, v___x_6754_);
lean_ctor_set_float32(v___x_6770_, 12, v___x_6756_);
lean_ctor_set_float32(v___x_6770_, 16, v___x_6758_);
lean_ctor_set_float32(v___x_6770_, 20, v___x_6760_);
lean_ctor_set_float32(v___x_6770_, 24, v___x_6762_);
lean_ctor_set_float32(v___x_6770_, 28, v___x_6764_);
lean_ctor_set_float32(v___x_6770_, 32, v___x_6766_);
lean_ctor_set_float32(v___x_6770_, 36, v___x_6768_);
return v___x_6770_;
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_Packed10_update___boxed(lean_object* v_acc_6773_, lean_object* v_a_6774_, lean_object* v_v_6775_){
_start:
{
float v_a_boxed_6776_; lean_object* v_res_6777_; 
v_a_boxed_6776_ = lean_unbox_float32(v_a_6774_);
lean_dec_ref(v_a_6774_);
v_res_6777_ = lp_competition_Submission_Packed10_update(v_acc_6773_, v_a_boxed_6776_, v_v_6775_);
lean_dec_ref(v_acc_6773_);
return v_res_6777_;
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_Packed10_groups(lean_object* v_p_6778_){
_start:
{
lean_object* v___x_6779_; lean_object* v___x_6780_; lean_object* v___x_6781_; lean_object* v___x_6782_; 
v___x_6779_ = lean_unsigned_to_nat(9u);
v___x_6780_ = lean_nat_add(v_p_6778_, v___x_6779_);
v___x_6781_ = lean_unsigned_to_nat(10u);
v___x_6782_ = lean_nat_div(v___x_6780_, v___x_6781_);
lean_dec(v___x_6780_);
return v___x_6782_;
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_Packed10_groups___boxed(lean_object* v_p_6783_){
_start:
{
lean_object* v_res_6784_; 
v_res_6784_ = lp_competition_Submission_Packed10_groups(v_p_6783_);
lean_dec(v_p_6783_);
return v_res_6784_;
}
}
LEAN_EXPORT float lp_competition_Submission_Packed10_packB___lam__0(lean_object* v_p_6785_, lean_object* v_base_6786_, lean_object* v_B_6787_, lean_object* v_j_6788_){
_start:
{
uint8_t v___x_6789_; 
v___x_6789_ = lean_nat_dec_lt(v_j_6788_, v_p_6785_);
if (v___x_6789_ == 0)
{
float v___x_6790_; 
v___x_6790_ = lean_float32_once(&lp_competition_Submission_NativeFinal_dot___closed__0, &lp_competition_Submission_NativeFinal_dot___closed__0_once, _init_lp_competition_Submission_NativeFinal_dot___closed__0);
return v___x_6790_;
}
else
{
lean_object* v___x_6791_; lean_object* v___x_6792_; uint32_t v___x_6793_; float v___x_6794_; 
v___x_6791_ = lean_nat_add(v_base_6786_, v_j_6788_);
v___x_6792_ = lean_array_fget_borrowed(v_B_6787_, v___x_6791_);
lean_dec(v___x_6791_);
v___x_6793_ = lean_unbox_uint32(v___x_6792_);
v___x_6794_ = lean_float32_of_bits(v___x_6793_);
return v___x_6794_;
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_Packed10_packB___lam__0___boxed(lean_object* v_p_6795_, lean_object* v_base_6796_, lean_object* v_B_6797_, lean_object* v_j_6798_){
_start:
{
float v_res_6799_; lean_object* v_r_6800_; 
v_res_6799_ = lp_competition_Submission_Packed10_packB___lam__0(v_p_6795_, v_base_6796_, v_B_6797_, v_j_6798_);
lean_dec(v_j_6798_);
lean_dec_ref(v_B_6797_);
lean_dec(v_base_6796_);
lean_dec(v_p_6795_);
v_r_6800_ = lean_box_float32(v_res_6799_);
return v_r_6800_;
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_Packed10_packB___lam__1(lean_object* v_b_6801_, lean_object* v_n_6802_, lean_object* v_p_6803_, lean_object* v_B_6804_, lean_object* v_g_6805_, lean_object* v_k_6806_){
_start:
{
lean_object* v___x_6807_; lean_object* v___x_6808_; lean_object* v_base_6809_; lean_object* v___x_6810_; lean_object* v___x_6811_; float v___x_6812_; lean_object* v___x_6813_; lean_object* v___x_6814_; float v___x_6815_; lean_object* v___x_6816_; lean_object* v___x_6817_; float v___x_6818_; lean_object* v___x_6819_; lean_object* v___x_6820_; float v___x_6821_; lean_object* v___x_6822_; lean_object* v___x_6823_; float v___x_6824_; lean_object* v___x_6825_; lean_object* v___x_6826_; float v___x_6827_; lean_object* v___x_6828_; lean_object* v___x_6829_; float v___x_6830_; lean_object* v___x_6831_; lean_object* v___x_6832_; float v___x_6833_; lean_object* v___x_6834_; lean_object* v___x_6835_; float v___x_6836_; lean_object* v___x_6837_; lean_object* v___x_6838_; float v___x_6839_; lean_object* v___x_6840_; 
v___x_6807_ = lean_nat_mul(v_b_6801_, v_n_6802_);
v___x_6808_ = lean_nat_add(v___x_6807_, v_k_6806_);
lean_dec(v___x_6807_);
v_base_6809_ = lean_nat_mul(v___x_6808_, v_p_6803_);
lean_dec(v___x_6808_);
v___x_6810_ = lean_unsigned_to_nat(10u);
v___x_6811_ = lean_nat_mul(v___x_6810_, v_g_6805_);
v___x_6812_ = lp_competition_Submission_Packed10_packB___lam__0(v_p_6803_, v_base_6809_, v_B_6804_, v___x_6811_);
v___x_6813_ = lean_unsigned_to_nat(1u);
v___x_6814_ = lean_nat_add(v___x_6811_, v___x_6813_);
v___x_6815_ = lp_competition_Submission_Packed10_packB___lam__0(v_p_6803_, v_base_6809_, v_B_6804_, v___x_6814_);
lean_dec(v___x_6814_);
v___x_6816_ = lean_unsigned_to_nat(2u);
v___x_6817_ = lean_nat_add(v___x_6811_, v___x_6816_);
v___x_6818_ = lp_competition_Submission_Packed10_packB___lam__0(v_p_6803_, v_base_6809_, v_B_6804_, v___x_6817_);
lean_dec(v___x_6817_);
v___x_6819_ = lean_unsigned_to_nat(3u);
v___x_6820_ = lean_nat_add(v___x_6811_, v___x_6819_);
v___x_6821_ = lp_competition_Submission_Packed10_packB___lam__0(v_p_6803_, v_base_6809_, v_B_6804_, v___x_6820_);
lean_dec(v___x_6820_);
v___x_6822_ = lean_unsigned_to_nat(4u);
v___x_6823_ = lean_nat_add(v___x_6811_, v___x_6822_);
v___x_6824_ = lp_competition_Submission_Packed10_packB___lam__0(v_p_6803_, v_base_6809_, v_B_6804_, v___x_6823_);
lean_dec(v___x_6823_);
v___x_6825_ = lean_unsigned_to_nat(5u);
v___x_6826_ = lean_nat_add(v___x_6811_, v___x_6825_);
v___x_6827_ = lp_competition_Submission_Packed10_packB___lam__0(v_p_6803_, v_base_6809_, v_B_6804_, v___x_6826_);
lean_dec(v___x_6826_);
v___x_6828_ = lean_unsigned_to_nat(6u);
v___x_6829_ = lean_nat_add(v___x_6811_, v___x_6828_);
v___x_6830_ = lp_competition_Submission_Packed10_packB___lam__0(v_p_6803_, v_base_6809_, v_B_6804_, v___x_6829_);
lean_dec(v___x_6829_);
v___x_6831_ = lean_unsigned_to_nat(7u);
v___x_6832_ = lean_nat_add(v___x_6811_, v___x_6831_);
v___x_6833_ = lp_competition_Submission_Packed10_packB___lam__0(v_p_6803_, v_base_6809_, v_B_6804_, v___x_6832_);
lean_dec(v___x_6832_);
v___x_6834_ = lean_unsigned_to_nat(8u);
v___x_6835_ = lean_nat_add(v___x_6811_, v___x_6834_);
v___x_6836_ = lp_competition_Submission_Packed10_packB___lam__0(v_p_6803_, v_base_6809_, v_B_6804_, v___x_6835_);
lean_dec(v___x_6835_);
v___x_6837_ = lean_unsigned_to_nat(9u);
v___x_6838_ = lean_nat_add(v___x_6811_, v___x_6837_);
lean_dec(v___x_6811_);
v___x_6839_ = lp_competition_Submission_Packed10_packB___lam__0(v_p_6803_, v_base_6809_, v_B_6804_, v___x_6838_);
lean_dec(v___x_6838_);
lean_dec(v_base_6809_);
v___x_6840_ = lean_alloc_ctor(0, 0, 40);
lean_ctor_set_float32(v___x_6840_, 0, v___x_6812_);
lean_ctor_set_float32(v___x_6840_, 4, v___x_6815_);
lean_ctor_set_float32(v___x_6840_, 8, v___x_6818_);
lean_ctor_set_float32(v___x_6840_, 12, v___x_6821_);
lean_ctor_set_float32(v___x_6840_, 16, v___x_6824_);
lean_ctor_set_float32(v___x_6840_, 20, v___x_6827_);
lean_ctor_set_float32(v___x_6840_, 24, v___x_6830_);
lean_ctor_set_float32(v___x_6840_, 28, v___x_6833_);
lean_ctor_set_float32(v___x_6840_, 32, v___x_6836_);
lean_ctor_set_float32(v___x_6840_, 36, v___x_6839_);
return v___x_6840_;
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_Packed10_packB___lam__1___boxed(lean_object* v_b_6841_, lean_object* v_n_6842_, lean_object* v_p_6843_, lean_object* v_B_6844_, lean_object* v_g_6845_, lean_object* v_k_6846_){
_start:
{
lean_object* v_res_6847_; 
v_res_6847_ = lp_competition_Submission_Packed10_packB___lam__1(v_b_6841_, v_n_6842_, v_p_6843_, v_B_6844_, v_g_6845_, v_k_6846_);
lean_dec(v_k_6846_);
lean_dec(v_g_6845_);
lean_dec_ref(v_B_6844_);
lean_dec(v_p_6843_);
lean_dec(v_n_6842_);
lean_dec(v_b_6841_);
return v_res_6847_;
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_Packed10_packB___lam__2(lean_object* v_b_6848_, lean_object* v_n_6849_, lean_object* v_p_6850_, lean_object* v_B_6851_, lean_object* v_g_6852_){
_start:
{
lean_object* v___f_6853_; lean_object* v___x_6854_; 
lean_inc(v_n_6849_);
v___f_6853_ = lean_alloc_closure((void*)(lp_competition_Submission_Packed10_packB___lam__1___boxed), 6, 5);
lean_closure_set(v___f_6853_, 0, v_b_6848_);
lean_closure_set(v___f_6853_, 1, v_n_6849_);
lean_closure_set(v___f_6853_, 2, v_p_6850_);
lean_closure_set(v___f_6853_, 3, v_B_6851_);
lean_closure_set(v___f_6853_, 4, v_g_6852_);
v___x_6854_ = l_Array_ofFn___redArg(v_n_6849_, v___f_6853_);
return v___x_6854_;
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_Packed10_packB___lam__3(lean_object* v_n_6855_, lean_object* v_p_6856_, lean_object* v_B_6857_, lean_object* v_b_6858_){
_start:
{
lean_object* v___f_6859_; lean_object* v___x_6860_; lean_object* v___x_6861_; lean_object* v___x_6862_; lean_object* v___x_6863_; lean_object* v___x_6864_; 
lean_inc(v_p_6856_);
v___f_6859_ = lean_alloc_closure((void*)(lp_competition_Submission_Packed10_packB___lam__2), 5, 4);
lean_closure_set(v___f_6859_, 0, v_b_6858_);
lean_closure_set(v___f_6859_, 1, v_n_6855_);
lean_closure_set(v___f_6859_, 2, v_p_6856_);
lean_closure_set(v___f_6859_, 3, v_B_6857_);
v___x_6860_ = lean_unsigned_to_nat(9u);
v___x_6861_ = lean_nat_add(v_p_6856_, v___x_6860_);
lean_dec(v_p_6856_);
v___x_6862_ = lean_unsigned_to_nat(10u);
v___x_6863_ = lean_nat_div(v___x_6861_, v___x_6862_);
lean_dec(v___x_6861_);
v___x_6864_ = l_Array_ofFn___redArg(v___x_6863_, v___f_6859_);
return v___x_6864_;
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_Packed10_packB(lean_object* v_batch_6865_, lean_object* v_n_6866_, lean_object* v_p_6867_, lean_object* v_B_6868_){
_start:
{
lean_object* v___f_6869_; lean_object* v___x_6870_; 
v___f_6869_ = lean_alloc_closure((void*)(lp_competition_Submission_Packed10_packB___lam__3), 4, 3);
lean_closure_set(v___f_6869_, 0, v_n_6866_);
lean_closure_set(v___f_6869_, 1, v_p_6867_);
lean_closure_set(v___f_6869_, 2, v_B_6868_);
v___x_6870_ = l_Array_ofFn___redArg(v_batch_6865_, v___f_6869_);
return v___x_6870_;
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_Packed10_dot10(lean_object* v_n_6871_, lean_object* v_baseA_6872_, lean_object* v_A_6873_, lean_object* v_B_6874_, lean_object* v_k_6875_, float v_s0_6876_, float v_s1_6877_, float v_s2_6878_, float v_s3_6879_, float v_s4_6880_, float v_s5_6881_, float v_s6_6882_, float v_s7_6883_, float v_s8_6884_, float v_s9_6885_){
_start:
{
float v___y_6887_; uint8_t v___x_6922_; 
v___x_6922_ = lean_nat_dec_lt(v_k_6875_, v_n_6871_);
if (v___x_6922_ == 0)
{
lean_object* v___x_6923_; 
lean_dec(v_k_6875_);
v___x_6923_ = lean_alloc_ctor(0, 0, 40);
lean_ctor_set_float32(v___x_6923_, 0, v_s0_6876_);
lean_ctor_set_float32(v___x_6923_, 4, v_s1_6877_);
lean_ctor_set_float32(v___x_6923_, 8, v_s2_6878_);
lean_ctor_set_float32(v___x_6923_, 12, v_s3_6879_);
lean_ctor_set_float32(v___x_6923_, 16, v_s4_6880_);
lean_ctor_set_float32(v___x_6923_, 20, v_s5_6881_);
lean_ctor_set_float32(v___x_6923_, 24, v_s6_6882_);
lean_ctor_set_float32(v___x_6923_, 28, v_s7_6883_);
lean_ctor_set_float32(v___x_6923_, 32, v_s8_6884_);
lean_ctor_set_float32(v___x_6923_, 36, v_s9_6885_);
return v___x_6923_;
}
else
{
lean_object* v___x_6924_; lean_object* v___x_6925_; uint8_t v___x_6926_; 
v___x_6924_ = lean_nat_add(v_baseA_6872_, v_k_6875_);
v___x_6925_ = lean_array_get_size(v_A_6873_);
v___x_6926_ = lean_nat_dec_lt(v___x_6924_, v___x_6925_);
if (v___x_6926_ == 0)
{
float v___x_6927_; 
lean_dec(v___x_6924_);
v___x_6927_ = lean_float32_once(&lp_competition_Submission_NativeFinal_dot___closed__0, &lp_competition_Submission_NativeFinal_dot___closed__0_once, _init_lp_competition_Submission_NativeFinal_dot___closed__0);
v___y_6887_ = v___x_6927_;
goto v___jp_6886_;
}
else
{
lean_object* v___x_6928_; float v___x_6929_; 
v___x_6928_ = lean_array_fget_borrowed(v_A_6873_, v___x_6924_);
lean_dec(v___x_6924_);
v___x_6929_ = lean_unbox_float32(v___x_6928_);
v___y_6887_ = v___x_6929_;
goto v___jp_6886_;
}
}
v___jp_6886_:
{
lean_object* v_v_6888_; float v_s0_6889_; float v_s1_6890_; float v_s2_6891_; float v_s3_6892_; float v_s4_6893_; float v_s5_6894_; float v_s6_6895_; float v_s7_6896_; float v_s8_6897_; float v_s9_6898_; lean_object* v___x_6899_; lean_object* v___x_6900_; float v___x_6901_; float v___x_6902_; float v___x_6903_; float v___x_6904_; float v___x_6905_; float v___x_6906_; float v___x_6907_; float v___x_6908_; float v___x_6909_; float v___x_6910_; float v___x_6911_; float v___x_6912_; float v___x_6913_; float v___x_6914_; float v___x_6915_; float v___x_6916_; float v___x_6917_; float v___x_6918_; float v___x_6919_; float v___x_6920_; 
v_v_6888_ = lean_array_fget_borrowed(v_B_6874_, v_k_6875_);
v_s0_6889_ = lean_ctor_get_float32(v_v_6888_, 0);
v_s1_6890_ = lean_ctor_get_float32(v_v_6888_, 4);
v_s2_6891_ = lean_ctor_get_float32(v_v_6888_, 8);
v_s3_6892_ = lean_ctor_get_float32(v_v_6888_, 12);
v_s4_6893_ = lean_ctor_get_float32(v_v_6888_, 16);
v_s5_6894_ = lean_ctor_get_float32(v_v_6888_, 20);
v_s6_6895_ = lean_ctor_get_float32(v_v_6888_, 24);
v_s7_6896_ = lean_ctor_get_float32(v_v_6888_, 28);
v_s8_6897_ = lean_ctor_get_float32(v_v_6888_, 32);
v_s9_6898_ = lean_ctor_get_float32(v_v_6888_, 36);
v___x_6899_ = lean_unsigned_to_nat(1u);
v___x_6900_ = lean_nat_add(v_k_6875_, v___x_6899_);
lean_dec(v_k_6875_);
v___x_6901_ = lean_float32_mul(v___y_6887_, v_s0_6889_);
v___x_6902_ = lean_float32_add(v_s0_6876_, v___x_6901_);
v___x_6903_ = lean_float32_mul(v___y_6887_, v_s1_6890_);
v___x_6904_ = lean_float32_add(v_s1_6877_, v___x_6903_);
v___x_6905_ = lean_float32_mul(v___y_6887_, v_s2_6891_);
v___x_6906_ = lean_float32_add(v_s2_6878_, v___x_6905_);
v___x_6907_ = lean_float32_mul(v___y_6887_, v_s3_6892_);
v___x_6908_ = lean_float32_add(v_s3_6879_, v___x_6907_);
v___x_6909_ = lean_float32_mul(v___y_6887_, v_s4_6893_);
v___x_6910_ = lean_float32_add(v_s4_6880_, v___x_6909_);
v___x_6911_ = lean_float32_mul(v___y_6887_, v_s5_6894_);
v___x_6912_ = lean_float32_add(v_s5_6881_, v___x_6911_);
v___x_6913_ = lean_float32_mul(v___y_6887_, v_s6_6895_);
v___x_6914_ = lean_float32_add(v_s6_6882_, v___x_6913_);
v___x_6915_ = lean_float32_mul(v___y_6887_, v_s7_6896_);
v___x_6916_ = lean_float32_add(v_s7_6883_, v___x_6915_);
v___x_6917_ = lean_float32_mul(v___y_6887_, v_s8_6897_);
v___x_6918_ = lean_float32_add(v_s8_6884_, v___x_6917_);
v___x_6919_ = lean_float32_mul(v___y_6887_, v_s9_6898_);
v___x_6920_ = lean_float32_add(v_s9_6885_, v___x_6919_);
v_k_6875_ = v___x_6900_;
v_s0_6876_ = v___x_6902_;
v_s1_6877_ = v___x_6904_;
v_s2_6878_ = v___x_6906_;
v_s3_6879_ = v___x_6908_;
v_s4_6880_ = v___x_6910_;
v_s5_6881_ = v___x_6912_;
v_s6_6882_ = v___x_6914_;
v_s7_6883_ = v___x_6916_;
v_s8_6884_ = v___x_6918_;
v_s9_6885_ = v___x_6920_;
goto _start;
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_Packed10_dot10___boxed(lean_object* v_n_6930_, lean_object* v_baseA_6931_, lean_object* v_A_6932_, lean_object* v_B_6933_, lean_object* v_k_6934_, lean_object* v_s0_6935_, lean_object* v_s1_6936_, lean_object* v_s2_6937_, lean_object* v_s3_6938_, lean_object* v_s4_6939_, lean_object* v_s5_6940_, lean_object* v_s6_6941_, lean_object* v_s7_6942_, lean_object* v_s8_6943_, lean_object* v_s9_6944_){
_start:
{
float v_s0_boxed_6945_; float v_s1_boxed_6946_; float v_s2_boxed_6947_; float v_s3_boxed_6948_; float v_s4_boxed_6949_; float v_s5_boxed_6950_; float v_s6_boxed_6951_; float v_s7_boxed_6952_; float v_s8_boxed_6953_; float v_s9_boxed_6954_; lean_object* v_res_6955_; 
v_s0_boxed_6945_ = lean_unbox_float32(v_s0_6935_);
lean_dec_ref(v_s0_6935_);
v_s1_boxed_6946_ = lean_unbox_float32(v_s1_6936_);
lean_dec_ref(v_s1_6936_);
v_s2_boxed_6947_ = lean_unbox_float32(v_s2_6937_);
lean_dec_ref(v_s2_6937_);
v_s3_boxed_6948_ = lean_unbox_float32(v_s3_6938_);
lean_dec_ref(v_s3_6938_);
v_s4_boxed_6949_ = lean_unbox_float32(v_s4_6939_);
lean_dec_ref(v_s4_6939_);
v_s5_boxed_6950_ = lean_unbox_float32(v_s5_6940_);
lean_dec_ref(v_s5_6940_);
v_s6_boxed_6951_ = lean_unbox_float32(v_s6_6941_);
lean_dec_ref(v_s6_6941_);
v_s7_boxed_6952_ = lean_unbox_float32(v_s7_6942_);
lean_dec_ref(v_s7_6942_);
v_s8_boxed_6953_ = lean_unbox_float32(v_s8_6943_);
lean_dec_ref(v_s8_6943_);
v_s9_boxed_6954_ = lean_unbox_float32(v_s9_6944_);
lean_dec_ref(v_s9_6944_);
v_res_6955_ = lp_competition_Submission_Packed10_dot10(v_n_6930_, v_baseA_6931_, v_A_6932_, v_B_6933_, v_k_6934_, v_s0_boxed_6945_, v_s1_boxed_6946_, v_s2_boxed_6947_, v_s3_boxed_6948_, v_s4_boxed_6949_, v_s5_boxed_6950_, v_s6_boxed_6951_, v_s7_boxed_6952_, v_s8_boxed_6953_, v_s9_boxed_6954_);
lean_dec_ref(v_B_6933_);
lean_dec_ref(v_A_6932_);
lean_dec(v_baseA_6931_);
lean_dec(v_n_6930_);
return v_res_6955_;
}
}
LEAN_EXPORT uint32_t lp_competition_Submission_Packed10_finish(lean_object* v_n_6956_, lean_object* v_baseA_6957_, lean_object* v_baseB_6958_, lean_object* v_p_6959_, lean_object* v_Araw_6960_, lean_object* v_Braw_6961_, float v_result_6962_){
_start:
{
uint32_t v_u_6963_; uint32_t v___x_6964_; uint32_t v___x_6965_; uint32_t v___x_6966_; uint32_t v___x_6967_; uint8_t v___x_6968_; 
v_u_6963_ = lean_float32_to_bits(v_result_6962_);
v___x_6964_ = 23;
v___x_6965_ = lean_uint32_shift_right(v_u_6963_, v___x_6964_);
v___x_6966_ = 255;
v___x_6967_ = lean_uint32_land(v___x_6965_, v___x_6966_);
v___x_6968_ = lean_uint32_dec_eq(v___x_6967_, v___x_6966_);
if (v___x_6968_ == 0)
{
return v_u_6963_;
}
else
{
lean_object* v___x_6969_; uint32_t v___x_6970_; uint32_t v___x_6971_; 
v___x_6969_ = lean_unsigned_to_nat(0u);
v___x_6970_ = lean_uint32_once(&lp_competition_Submission_referenceSum___redArg___closed__1, &lp_competition_Submission_referenceSum___redArg___closed__1_once, _init_lp_competition_Submission_referenceSum___redArg___closed__1);
v___x_6971_ = lp_competition_Fin_foldl_loop___at___00Submission_NativeFinal_dot_spec__0(v_baseA_6957_, v_p_6959_, v_baseB_6958_, v_Braw_6961_, v_Araw_6960_, v_n_6956_, v___x_6970_, v___x_6969_);
return v___x_6971_;
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_Packed10_finish___boxed(lean_object* v_n_6972_, lean_object* v_baseA_6973_, lean_object* v_baseB_6974_, lean_object* v_p_6975_, lean_object* v_Araw_6976_, lean_object* v_Braw_6977_, lean_object* v_result_6978_){
_start:
{
float v_result_boxed_6979_; uint32_t v_res_6980_; lean_object* v_r_6981_; 
v_result_boxed_6979_ = lean_unbox_float32(v_result_6978_);
lean_dec_ref(v_result_6978_);
v_res_6980_ = lp_competition_Submission_Packed10_finish(v_n_6972_, v_baseA_6973_, v_baseB_6974_, v_p_6975_, v_Araw_6976_, v_Braw_6977_, v_result_boxed_6979_);
lean_dec_ref(v_Braw_6977_);
lean_dec_ref(v_Araw_6976_);
lean_dec(v_p_6975_);
lean_dec(v_baseB_6974_);
lean_dec(v_baseA_6973_);
lean_dec(v_n_6972_);
v_r_6981_ = lean_box_uint32(v_res_6980_);
return v_r_6981_;
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_Packed10Index_loop___redArg(size_t v_count_6982_, size_t v_baseA_6983_, lean_object* v_A_6984_, lean_object* v_B_6985_, size_t v_k_6986_, float v_s0_6987_, float v_s1_6988_, float v_s2_6989_, float v_s3_6990_, float v_s4_6991_, float v_s5_6992_, float v_s6_6993_, float v_s7_6994_, float v_s8_6995_, float v_s9_6996_){
_start:
{
uint8_t v___x_6997_; 
v___x_6997_ = lean_usize_dec_lt(v_k_6986_, v_count_6982_);
if (v___x_6997_ == 0)
{
lean_object* v___x_6998_; 
v___x_6998_ = lean_alloc_ctor(0, 0, 40);
lean_ctor_set_float32(v___x_6998_, 0, v_s0_6987_);
lean_ctor_set_float32(v___x_6998_, 4, v_s1_6988_);
lean_ctor_set_float32(v___x_6998_, 8, v_s2_6989_);
lean_ctor_set_float32(v___x_6998_, 12, v_s3_6990_);
lean_ctor_set_float32(v___x_6998_, 16, v_s4_6991_);
lean_ctor_set_float32(v___x_6998_, 20, v_s5_6992_);
lean_ctor_set_float32(v___x_6998_, 24, v_s6_6993_);
lean_ctor_set_float32(v___x_6998_, 28, v_s7_6994_);
lean_ctor_set_float32(v___x_6998_, 32, v_s8_6995_);
lean_ctor_set_float32(v___x_6998_, 36, v_s9_6996_);
return v___x_6998_;
}
else
{
size_t v___x_6999_; lean_object* v_v_7000_; float v_s0_7001_; float v_s1_7002_; float v_s2_7003_; float v_s3_7004_; float v_s4_7005_; float v_s5_7006_; float v_s6_7007_; float v_s7_7008_; float v_s8_7009_; float v_s9_7010_; lean_object* v_a_7011_; size_t v___x_7012_; size_t v___x_7013_; float v___x_7014_; float v___x_7015_; float v___x_7016_; float v___x_7017_; float v___x_7018_; float v___x_7019_; float v___x_7020_; float v___x_7021_; float v___x_7022_; float v___x_7023_; float v___x_7024_; float v___x_7025_; float v___x_7026_; float v___x_7027_; float v___x_7028_; float v___x_7029_; float v___x_7030_; float v___x_7031_; float v___x_7032_; float v___x_7033_; float v___x_7034_; float v___x_7035_; float v___x_7036_; float v___x_7037_; float v___x_7038_; float v___x_7039_; float v___x_7040_; float v___x_7041_; float v___x_7042_; float v___x_7043_; 
v___x_6999_ = lean_usize_add(v_baseA_6983_, v_k_6986_);
v_v_7000_ = lean_array_uget_borrowed(v_B_6985_, v_k_6986_);
v_s0_7001_ = lean_ctor_get_float32(v_v_7000_, 0);
v_s1_7002_ = lean_ctor_get_float32(v_v_7000_, 4);
v_s2_7003_ = lean_ctor_get_float32(v_v_7000_, 8);
v_s3_7004_ = lean_ctor_get_float32(v_v_7000_, 12);
v_s4_7005_ = lean_ctor_get_float32(v_v_7000_, 16);
v_s5_7006_ = lean_ctor_get_float32(v_v_7000_, 20);
v_s6_7007_ = lean_ctor_get_float32(v_v_7000_, 24);
v_s7_7008_ = lean_ctor_get_float32(v_v_7000_, 28);
v_s8_7009_ = lean_ctor_get_float32(v_v_7000_, 32);
v_s9_7010_ = lean_ctor_get_float32(v_v_7000_, 36);
v_a_7011_ = lean_array_uget_borrowed(v_A_6984_, v___x_6999_);
v___x_7012_ = ((size_t)1ULL);
v___x_7013_ = lean_usize_add(v_k_6986_, v___x_7012_);
v___x_7014_ = lean_unbox_float32(v_a_7011_);
v___x_7015_ = lean_float32_mul(v___x_7014_, v_s0_7001_);
v___x_7016_ = lean_float32_add(v_s0_6987_, v___x_7015_);
v___x_7017_ = lean_unbox_float32(v_a_7011_);
v___x_7018_ = lean_float32_mul(v___x_7017_, v_s1_7002_);
v___x_7019_ = lean_float32_add(v_s1_6988_, v___x_7018_);
v___x_7020_ = lean_unbox_float32(v_a_7011_);
v___x_7021_ = lean_float32_mul(v___x_7020_, v_s2_7003_);
v___x_7022_ = lean_float32_add(v_s2_6989_, v___x_7021_);
v___x_7023_ = lean_unbox_float32(v_a_7011_);
v___x_7024_ = lean_float32_mul(v___x_7023_, v_s3_7004_);
v___x_7025_ = lean_float32_add(v_s3_6990_, v___x_7024_);
v___x_7026_ = lean_unbox_float32(v_a_7011_);
v___x_7027_ = lean_float32_mul(v___x_7026_, v_s4_7005_);
v___x_7028_ = lean_float32_add(v_s4_6991_, v___x_7027_);
v___x_7029_ = lean_unbox_float32(v_a_7011_);
v___x_7030_ = lean_float32_mul(v___x_7029_, v_s5_7006_);
v___x_7031_ = lean_float32_add(v_s5_6992_, v___x_7030_);
v___x_7032_ = lean_unbox_float32(v_a_7011_);
v___x_7033_ = lean_float32_mul(v___x_7032_, v_s6_7007_);
v___x_7034_ = lean_float32_add(v_s6_6993_, v___x_7033_);
v___x_7035_ = lean_unbox_float32(v_a_7011_);
v___x_7036_ = lean_float32_mul(v___x_7035_, v_s7_7008_);
v___x_7037_ = lean_float32_add(v_s7_6994_, v___x_7036_);
v___x_7038_ = lean_unbox_float32(v_a_7011_);
v___x_7039_ = lean_float32_mul(v___x_7038_, v_s8_7009_);
v___x_7040_ = lean_float32_add(v_s8_6995_, v___x_7039_);
v___x_7041_ = lean_unbox_float32(v_a_7011_);
v___x_7042_ = lean_float32_mul(v___x_7041_, v_s9_7010_);
v___x_7043_ = lean_float32_add(v_s9_6996_, v___x_7042_);
v_k_6986_ = v___x_7013_;
v_s0_6987_ = v___x_7016_;
v_s1_6988_ = v___x_7019_;
v_s2_6989_ = v___x_7022_;
v_s3_6990_ = v___x_7025_;
v_s4_6991_ = v___x_7028_;
v_s5_6992_ = v___x_7031_;
v_s6_6993_ = v___x_7034_;
v_s7_6994_ = v___x_7037_;
v_s8_6995_ = v___x_7040_;
v_s9_6996_ = v___x_7043_;
goto _start;
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_Packed10Index_loop___redArg___boxed(lean_object* v_count_7045_, lean_object* v_baseA_7046_, lean_object* v_A_7047_, lean_object* v_B_7048_, lean_object* v_k_7049_, lean_object* v_s0_7050_, lean_object* v_s1_7051_, lean_object* v_s2_7052_, lean_object* v_s3_7053_, lean_object* v_s4_7054_, lean_object* v_s5_7055_, lean_object* v_s6_7056_, lean_object* v_s7_7057_, lean_object* v_s8_7058_, lean_object* v_s9_7059_){
_start:
{
size_t v_count_boxed_7060_; size_t v_baseA_boxed_7061_; size_t v_k_boxed_7062_; float v_s0_boxed_7063_; float v_s1_boxed_7064_; float v_s2_boxed_7065_; float v_s3_boxed_7066_; float v_s4_boxed_7067_; float v_s5_boxed_7068_; float v_s6_boxed_7069_; float v_s7_boxed_7070_; float v_s8_boxed_7071_; float v_s9_boxed_7072_; lean_object* v_res_7073_; 
v_count_boxed_7060_ = lean_unbox_usize(v_count_7045_);
lean_dec(v_count_7045_);
v_baseA_boxed_7061_ = lean_unbox_usize(v_baseA_7046_);
lean_dec(v_baseA_7046_);
v_k_boxed_7062_ = lean_unbox_usize(v_k_7049_);
lean_dec(v_k_7049_);
v_s0_boxed_7063_ = lean_unbox_float32(v_s0_7050_);
lean_dec_ref(v_s0_7050_);
v_s1_boxed_7064_ = lean_unbox_float32(v_s1_7051_);
lean_dec_ref(v_s1_7051_);
v_s2_boxed_7065_ = lean_unbox_float32(v_s2_7052_);
lean_dec_ref(v_s2_7052_);
v_s3_boxed_7066_ = lean_unbox_float32(v_s3_7053_);
lean_dec_ref(v_s3_7053_);
v_s4_boxed_7067_ = lean_unbox_float32(v_s4_7054_);
lean_dec_ref(v_s4_7054_);
v_s5_boxed_7068_ = lean_unbox_float32(v_s5_7055_);
lean_dec_ref(v_s5_7055_);
v_s6_boxed_7069_ = lean_unbox_float32(v_s6_7056_);
lean_dec_ref(v_s6_7056_);
v_s7_boxed_7070_ = lean_unbox_float32(v_s7_7057_);
lean_dec_ref(v_s7_7057_);
v_s8_boxed_7071_ = lean_unbox_float32(v_s8_7058_);
lean_dec_ref(v_s8_7058_);
v_s9_boxed_7072_ = lean_unbox_float32(v_s9_7059_);
lean_dec_ref(v_s9_7059_);
v_res_7073_ = lp_competition_Submission_Packed10Index_loop___redArg(v_count_boxed_7060_, v_baseA_boxed_7061_, v_A_7047_, v_B_7048_, v_k_boxed_7062_, v_s0_boxed_7063_, v_s1_boxed_7064_, v_s2_boxed_7065_, v_s3_boxed_7066_, v_s4_boxed_7067_, v_s5_boxed_7068_, v_s6_boxed_7069_, v_s7_boxed_7070_, v_s8_boxed_7071_, v_s9_boxed_7072_);
lean_dec_ref(v_B_7048_);
lean_dec_ref(v_A_7047_);
return v_res_7073_;
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_Packed10Index_loop(lean_object* v_n_7074_, size_t v_count_7075_, size_t v_baseA_7076_, lean_object* v_A_7077_, lean_object* v_B_7078_, lean_object* v_hn_7079_, lean_object* v_hA_7080_, lean_object* v_hAS_7081_, size_t v_k_7082_, float v_s0_7083_, float v_s1_7084_, float v_s2_7085_, float v_s3_7086_, float v_s4_7087_, float v_s5_7088_, float v_s6_7089_, float v_s7_7090_, float v_s8_7091_, float v_s9_7092_){
_start:
{
lean_object* v___x_7093_; 
v___x_7093_ = lp_competition_Submission_Packed10Index_loop___redArg(v_count_7075_, v_baseA_7076_, v_A_7077_, v_B_7078_, v_k_7082_, v_s0_7083_, v_s1_7084_, v_s2_7085_, v_s3_7086_, v_s4_7087_, v_s5_7088_, v_s6_7089_, v_s7_7090_, v_s8_7091_, v_s9_7092_);
return v___x_7093_;
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_Packed10Index_loop___boxed(lean_object** _args){
lean_object* v_n_7094_ = _args[0];
lean_object* v_count_7095_ = _args[1];
lean_object* v_baseA_7096_ = _args[2];
lean_object* v_A_7097_ = _args[3];
lean_object* v_B_7098_ = _args[4];
lean_object* v_hn_7099_ = _args[5];
lean_object* v_hA_7100_ = _args[6];
lean_object* v_hAS_7101_ = _args[7];
lean_object* v_k_7102_ = _args[8];
lean_object* v_s0_7103_ = _args[9];
lean_object* v_s1_7104_ = _args[10];
lean_object* v_s2_7105_ = _args[11];
lean_object* v_s3_7106_ = _args[12];
lean_object* v_s4_7107_ = _args[13];
lean_object* v_s5_7108_ = _args[14];
lean_object* v_s6_7109_ = _args[15];
lean_object* v_s7_7110_ = _args[16];
lean_object* v_s8_7111_ = _args[17];
lean_object* v_s9_7112_ = _args[18];
_start:
{
size_t v_count_boxed_7113_; size_t v_baseA_boxed_7114_; size_t v_k_boxed_7115_; float v_s0_boxed_7116_; float v_s1_boxed_7117_; float v_s2_boxed_7118_; float v_s3_boxed_7119_; float v_s4_boxed_7120_; float v_s5_boxed_7121_; float v_s6_boxed_7122_; float v_s7_boxed_7123_; float v_s8_boxed_7124_; float v_s9_boxed_7125_; lean_object* v_res_7126_; 
v_count_boxed_7113_ = lean_unbox_usize(v_count_7095_);
lean_dec(v_count_7095_);
v_baseA_boxed_7114_ = lean_unbox_usize(v_baseA_7096_);
lean_dec(v_baseA_7096_);
v_k_boxed_7115_ = lean_unbox_usize(v_k_7102_);
lean_dec(v_k_7102_);
v_s0_boxed_7116_ = lean_unbox_float32(v_s0_7103_);
lean_dec_ref(v_s0_7103_);
v_s1_boxed_7117_ = lean_unbox_float32(v_s1_7104_);
lean_dec_ref(v_s1_7104_);
v_s2_boxed_7118_ = lean_unbox_float32(v_s2_7105_);
lean_dec_ref(v_s2_7105_);
v_s3_boxed_7119_ = lean_unbox_float32(v_s3_7106_);
lean_dec_ref(v_s3_7106_);
v_s4_boxed_7120_ = lean_unbox_float32(v_s4_7107_);
lean_dec_ref(v_s4_7107_);
v_s5_boxed_7121_ = lean_unbox_float32(v_s5_7108_);
lean_dec_ref(v_s5_7108_);
v_s6_boxed_7122_ = lean_unbox_float32(v_s6_7109_);
lean_dec_ref(v_s6_7109_);
v_s7_boxed_7123_ = lean_unbox_float32(v_s7_7110_);
lean_dec_ref(v_s7_7110_);
v_s8_boxed_7124_ = lean_unbox_float32(v_s8_7111_);
lean_dec_ref(v_s8_7111_);
v_s9_boxed_7125_ = lean_unbox_float32(v_s9_7112_);
lean_dec_ref(v_s9_7112_);
v_res_7126_ = lp_competition_Submission_Packed10Index_loop(v_n_7094_, v_count_boxed_7113_, v_baseA_boxed_7114_, v_A_7097_, v_B_7098_, v_hn_7099_, v_hA_7100_, v_hAS_7101_, v_k_boxed_7115_, v_s0_boxed_7116_, v_s1_boxed_7117_, v_s2_boxed_7118_, v_s3_boxed_7119_, v_s4_boxed_7120_, v_s5_boxed_7121_, v_s6_boxed_7122_, v_s7_boxed_7123_, v_s8_boxed_7124_, v_s9_boxed_7125_);
lean_dec_ref(v_B_7098_);
lean_dec_ref(v_A_7097_);
lean_dec(v_n_7094_);
return v_res_7126_;
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_Packed10Index_within___redArg(lean_object* v_n_7127_, lean_object* v_baseA_7128_, lean_object* v_A_7129_, lean_object* v_B_7130_){
_start:
{
size_t v___x_7131_; size_t v___x_7132_; size_t v___x_7133_; float v___x_7134_; lean_object* v___x_7135_; 
v___x_7131_ = lean_usize_of_nat(v_n_7127_);
v___x_7132_ = lean_usize_of_nat(v_baseA_7128_);
v___x_7133_ = ((size_t)0ULL);
v___x_7134_ = lean_float32_once(&lp_competition_Submission_NativeFinal_dot___closed__0, &lp_competition_Submission_NativeFinal_dot___closed__0_once, _init_lp_competition_Submission_NativeFinal_dot___closed__0);
v___x_7135_ = lp_competition_Submission_Packed10Index_loop___redArg(v___x_7131_, v___x_7132_, v_A_7129_, v_B_7130_, v___x_7133_, v___x_7134_, v___x_7134_, v___x_7134_, v___x_7134_, v___x_7134_, v___x_7134_, v___x_7134_, v___x_7134_, v___x_7134_, v___x_7134_);
return v___x_7135_;
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_Packed10Index_within___redArg___boxed(lean_object* v_n_7136_, lean_object* v_baseA_7137_, lean_object* v_A_7138_, lean_object* v_B_7139_){
_start:
{
lean_object* v_res_7140_; 
v_res_7140_ = lp_competition_Submission_Packed10Index_within___redArg(v_n_7136_, v_baseA_7137_, v_A_7138_, v_B_7139_);
lean_dec_ref(v_B_7139_);
lean_dec_ref(v_A_7138_);
lean_dec(v_baseA_7137_);
lean_dec(v_n_7136_);
return v_res_7140_;
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_Packed10Index_within(lean_object* v_n_7141_, lean_object* v_baseA_7142_, lean_object* v_A_7143_, lean_object* v_B_7144_, lean_object* v_hn_7145_, lean_object* v_ha_7146_, lean_object* v_hA_7147_, lean_object* v_hAS_7148_){
_start:
{
size_t v___x_7149_; size_t v___x_7150_; size_t v___x_7151_; float v___x_7152_; lean_object* v___x_7153_; 
v___x_7149_ = lean_usize_of_nat(v_n_7141_);
v___x_7150_ = lean_usize_of_nat(v_baseA_7142_);
v___x_7151_ = ((size_t)0ULL);
v___x_7152_ = lean_float32_once(&lp_competition_Submission_NativeFinal_dot___closed__0, &lp_competition_Submission_NativeFinal_dot___closed__0_once, _init_lp_competition_Submission_NativeFinal_dot___closed__0);
v___x_7153_ = lp_competition_Submission_Packed10Index_loop___redArg(v___x_7149_, v___x_7150_, v_A_7143_, v_B_7144_, v___x_7151_, v___x_7152_, v___x_7152_, v___x_7152_, v___x_7152_, v___x_7152_, v___x_7152_, v___x_7152_, v___x_7152_, v___x_7152_, v___x_7152_);
return v___x_7153_;
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_Packed10Index_within___boxed(lean_object* v_n_7154_, lean_object* v_baseA_7155_, lean_object* v_A_7156_, lean_object* v_B_7157_, lean_object* v_hn_7158_, lean_object* v_ha_7159_, lean_object* v_hA_7160_, lean_object* v_hAS_7161_){
_start:
{
lean_object* v_res_7162_; 
v_res_7162_ = lp_competition_Submission_Packed10Index_within(v_n_7154_, v_baseA_7155_, v_A_7156_, v_B_7157_, v_hn_7158_, v_ha_7159_, v_hA_7160_, v_hAS_7161_);
lean_dec_ref(v_B_7157_);
lean_dec_ref(v_A_7156_);
lean_dec(v_baseA_7155_);
lean_dec(v_n_7154_);
return v_res_7162_;
}
}
static lean_object* _init_lp_competition_Submission_Packed10Index_runDot___closed__0(void){
_start:
{
lean_object* v___x_7163_; lean_object* v___x_7164_; lean_object* v___x_7165_; 
v___x_7163_ = l_System_Platform_numBits;
v___x_7164_ = lean_unsigned_to_nat(2u);
v___x_7165_ = lean_nat_pow(v___x_7164_, v___x_7163_);
return v___x_7165_;
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_Packed10Index_runDot(lean_object* v_n_7166_, lean_object* v_baseA_7167_, lean_object* v_A_7168_, lean_object* v_B_7169_){
_start:
{
lean_object* v___x_7174_; uint8_t v___x_7175_; 
v___x_7174_ = lean_obj_once(&lp_competition_Submission_Packed10Index_runDot___closed__0, &lp_competition_Submission_Packed10Index_runDot___closed__0_once, _init_lp_competition_Submission_Packed10Index_runDot___closed__0);
v___x_7175_ = lean_nat_dec_lt(v_n_7166_, v___x_7174_);
if (v___x_7175_ == 0)
{
goto v___jp_7170_;
}
else
{
uint8_t v___x_7176_; 
v___x_7176_ = lean_nat_dec_lt(v_baseA_7167_, v___x_7174_);
if (v___x_7176_ == 0)
{
goto v___jp_7170_;
}
else
{
lean_object* v___x_7177_; lean_object* v___x_7178_; lean_object* v___x_7179_; lean_object* v___x_7180_; uint8_t v___x_7181_; 
v___x_7177_ = lean_unsigned_to_nat(1u);
v___x_7178_ = lean_nat_sub(v_n_7166_, v___x_7177_);
v___x_7179_ = lean_nat_add(v_baseA_7167_, v___x_7178_);
lean_dec(v___x_7178_);
v___x_7180_ = lean_array_get_size(v_A_7168_);
v___x_7181_ = lean_nat_dec_lt(v___x_7179_, v___x_7180_);
lean_dec(v___x_7179_);
if (v___x_7181_ == 0)
{
goto v___jp_7170_;
}
else
{
uint8_t v___x_7182_; 
v___x_7182_ = lean_nat_dec_lt(v___x_7180_, v___x_7174_);
if (v___x_7182_ == 0)
{
goto v___jp_7170_;
}
else
{
size_t v___x_7183_; size_t v___x_7184_; size_t v___x_7185_; float v___x_7186_; lean_object* v___x_7187_; 
v___x_7183_ = lean_usize_of_nat(v_n_7166_);
v___x_7184_ = lean_usize_of_nat(v_baseA_7167_);
v___x_7185_ = ((size_t)0ULL);
v___x_7186_ = lean_float32_once(&lp_competition_Submission_NativeFinal_dot___closed__0, &lp_competition_Submission_NativeFinal_dot___closed__0_once, _init_lp_competition_Submission_NativeFinal_dot___closed__0);
v___x_7187_ = lp_competition_Submission_Packed10Index_loop___redArg(v___x_7183_, v___x_7184_, v_A_7168_, v_B_7169_, v___x_7185_, v___x_7186_, v___x_7186_, v___x_7186_, v___x_7186_, v___x_7186_, v___x_7186_, v___x_7186_, v___x_7186_, v___x_7186_, v___x_7186_);
return v___x_7187_;
}
}
}
}
v___jp_7170_:
{
lean_object* v___x_7171_; float v___x_7172_; lean_object* v___x_7173_; 
v___x_7171_ = lean_unsigned_to_nat(0u);
v___x_7172_ = lean_float32_once(&lp_competition_Submission_NativeFinal_dot___closed__0, &lp_competition_Submission_NativeFinal_dot___closed__0_once, _init_lp_competition_Submission_NativeFinal_dot___closed__0);
v___x_7173_ = lp_competition_Submission_Packed10_dot10(v_n_7166_, v_baseA_7167_, v_A_7168_, v_B_7169_, v___x_7171_, v___x_7172_, v___x_7172_, v___x_7172_, v___x_7172_, v___x_7172_, v___x_7172_, v___x_7172_, v___x_7172_, v___x_7172_, v___x_7172_);
return v___x_7173_;
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_Packed10Index_runDot___boxed(lean_object* v_n_7188_, lean_object* v_baseA_7189_, lean_object* v_A_7190_, lean_object* v_B_7191_){
_start:
{
lean_object* v_res_7192_; 
v_res_7192_ = lp_competition_Submission_Packed10Index_runDot(v_n_7188_, v_baseA_7189_, v_A_7190_, v_B_7191_);
lean_dec_ref(v_B_7191_);
lean_dec_ref(v_A_7190_);
lean_dec(v_baseA_7189_);
lean_dec(v_n_7188_);
return v_res_7192_;
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_Packed10_tileResults___lam__0(lean_object* v_b_7193_, lean_object* v_m_7194_, lean_object* v_i_7195_, lean_object* v_n_7196_, lean_object* v_B_7197_, lean_object* v_A_7198_, lean_object* v_g_7199_){
_start:
{
lean_object* v___x_7200_; lean_object* v___x_7201_; lean_object* v___x_7202_; lean_object* v___x_7203_; lean_object* v___x_7204_; lean_object* v___x_7209_; uint8_t v___x_7210_; 
v___x_7200_ = lean_nat_mul(v_b_7193_, v_m_7194_);
v___x_7201_ = lean_nat_add(v___x_7200_, v_i_7195_);
lean_dec(v___x_7200_);
v___x_7202_ = lean_nat_mul(v___x_7201_, v_n_7196_);
lean_dec(v___x_7201_);
v___x_7203_ = lean_array_fget_borrowed(v_B_7197_, v_b_7193_);
v___x_7204_ = lean_array_fget_borrowed(v___x_7203_, v_g_7199_);
v___x_7209_ = lean_obj_once(&lp_competition_Submission_Packed10Index_runDot___closed__0, &lp_competition_Submission_Packed10Index_runDot___closed__0_once, _init_lp_competition_Submission_Packed10Index_runDot___closed__0);
v___x_7210_ = lean_nat_dec_lt(v_n_7196_, v___x_7209_);
if (v___x_7210_ == 0)
{
goto v___jp_7205_;
}
else
{
uint8_t v___x_7211_; 
v___x_7211_ = lean_nat_dec_lt(v___x_7202_, v___x_7209_);
if (v___x_7211_ == 0)
{
goto v___jp_7205_;
}
else
{
lean_object* v___x_7212_; lean_object* v___x_7213_; lean_object* v___x_7214_; lean_object* v___x_7215_; uint8_t v___x_7216_; 
v___x_7212_ = lean_unsigned_to_nat(1u);
v___x_7213_ = lean_nat_sub(v_n_7196_, v___x_7212_);
v___x_7214_ = lean_nat_add(v___x_7202_, v___x_7213_);
lean_dec(v___x_7213_);
v___x_7215_ = lean_array_get_size(v_A_7198_);
v___x_7216_ = lean_nat_dec_lt(v___x_7214_, v___x_7215_);
lean_dec(v___x_7214_);
if (v___x_7216_ == 0)
{
goto v___jp_7205_;
}
else
{
uint8_t v___x_7217_; 
v___x_7217_ = lean_nat_dec_lt(v___x_7215_, v___x_7209_);
if (v___x_7217_ == 0)
{
goto v___jp_7205_;
}
else
{
size_t v___x_7218_; size_t v___x_7219_; size_t v___x_7220_; float v___x_7221_; lean_object* v___x_7222_; 
v___x_7218_ = lean_usize_of_nat(v_n_7196_);
v___x_7219_ = lean_usize_of_nat(v___x_7202_);
lean_dec(v___x_7202_);
v___x_7220_ = ((size_t)0ULL);
v___x_7221_ = lean_float32_once(&lp_competition_Submission_NativeFinal_dot___closed__0, &lp_competition_Submission_NativeFinal_dot___closed__0_once, _init_lp_competition_Submission_NativeFinal_dot___closed__0);
v___x_7222_ = lp_competition_Submission_Packed10Index_loop___redArg(v___x_7218_, v___x_7219_, v_A_7198_, v___x_7204_, v___x_7220_, v___x_7221_, v___x_7221_, v___x_7221_, v___x_7221_, v___x_7221_, v___x_7221_, v___x_7221_, v___x_7221_, v___x_7221_, v___x_7221_);
return v___x_7222_;
}
}
}
}
v___jp_7205_:
{
lean_object* v___x_7206_; float v___x_7207_; lean_object* v___x_7208_; 
v___x_7206_ = lean_unsigned_to_nat(0u);
v___x_7207_ = lean_float32_once(&lp_competition_Submission_NativeFinal_dot___closed__0, &lp_competition_Submission_NativeFinal_dot___closed__0_once, _init_lp_competition_Submission_NativeFinal_dot___closed__0);
v___x_7208_ = lp_competition_Submission_Packed10_dot10(v_n_7196_, v___x_7202_, v_A_7198_, v___x_7204_, v___x_7206_, v___x_7207_, v___x_7207_, v___x_7207_, v___x_7207_, v___x_7207_, v___x_7207_, v___x_7207_, v___x_7207_, v___x_7207_, v___x_7207_);
lean_dec(v___x_7202_);
return v___x_7208_;
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_Packed10_tileResults___lam__0___boxed(lean_object* v_b_7223_, lean_object* v_m_7224_, lean_object* v_i_7225_, lean_object* v_n_7226_, lean_object* v_B_7227_, lean_object* v_A_7228_, lean_object* v_g_7229_){
_start:
{
lean_object* v_res_7230_; 
v_res_7230_ = lp_competition_Submission_Packed10_tileResults___lam__0(v_b_7223_, v_m_7224_, v_i_7225_, v_n_7226_, v_B_7227_, v_A_7228_, v_g_7229_);
lean_dec(v_g_7229_);
lean_dec_ref(v_A_7228_);
lean_dec_ref(v_B_7227_);
lean_dec(v_n_7226_);
lean_dec(v_i_7225_);
lean_dec(v_m_7224_);
lean_dec(v_b_7223_);
return v_res_7230_;
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_Packed10_tileResults___lam__1(lean_object* v_b_7231_, lean_object* v_m_7232_, lean_object* v_n_7233_, lean_object* v_B_7234_, lean_object* v_A_7235_, lean_object* v_p_7236_, lean_object* v_i_7237_){
_start:
{
lean_object* v___f_7238_; lean_object* v___x_7239_; lean_object* v___x_7240_; lean_object* v___x_7241_; lean_object* v___x_7242_; lean_object* v___x_7243_; 
v___f_7238_ = lean_alloc_closure((void*)(lp_competition_Submission_Packed10_tileResults___lam__0___boxed), 7, 6);
lean_closure_set(v___f_7238_, 0, v_b_7231_);
lean_closure_set(v___f_7238_, 1, v_m_7232_);
lean_closure_set(v___f_7238_, 2, v_i_7237_);
lean_closure_set(v___f_7238_, 3, v_n_7233_);
lean_closure_set(v___f_7238_, 4, v_B_7234_);
lean_closure_set(v___f_7238_, 5, v_A_7235_);
v___x_7239_ = lean_unsigned_to_nat(9u);
v___x_7240_ = lean_nat_add(v_p_7236_, v___x_7239_);
v___x_7241_ = lean_unsigned_to_nat(10u);
v___x_7242_ = lean_nat_div(v___x_7240_, v___x_7241_);
lean_dec(v___x_7240_);
v___x_7243_ = l_Array_ofFn___redArg(v___x_7242_, v___f_7238_);
return v___x_7243_;
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_Packed10_tileResults___lam__1___boxed(lean_object* v_b_7244_, lean_object* v_m_7245_, lean_object* v_n_7246_, lean_object* v_B_7247_, lean_object* v_A_7248_, lean_object* v_p_7249_, lean_object* v_i_7250_){
_start:
{
lean_object* v_res_7251_; 
v_res_7251_ = lp_competition_Submission_Packed10_tileResults___lam__1(v_b_7244_, v_m_7245_, v_n_7246_, v_B_7247_, v_A_7248_, v_p_7249_, v_i_7250_);
lean_dec(v_p_7249_);
return v_res_7251_;
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_Packed10_tileResults___lam__2(lean_object* v_m_7252_, lean_object* v_n_7253_, lean_object* v_B_7254_, lean_object* v_A_7255_, lean_object* v_p_7256_, lean_object* v_b_7257_){
_start:
{
lean_object* v___f_7258_; lean_object* v___x_7259_; 
lean_inc(v_m_7252_);
v___f_7258_ = lean_alloc_closure((void*)(lp_competition_Submission_Packed10_tileResults___lam__1___boxed), 7, 6);
lean_closure_set(v___f_7258_, 0, v_b_7257_);
lean_closure_set(v___f_7258_, 1, v_m_7252_);
lean_closure_set(v___f_7258_, 2, v_n_7253_);
lean_closure_set(v___f_7258_, 3, v_B_7254_);
lean_closure_set(v___f_7258_, 4, v_A_7255_);
lean_closure_set(v___f_7258_, 5, v_p_7256_);
v___x_7259_ = l_Array_ofFn___redArg(v_m_7252_, v___f_7258_);
return v___x_7259_;
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_Packed10_tileResults(lean_object* v_batch_7260_, lean_object* v_m_7261_, lean_object* v_n_7262_, lean_object* v_p_7263_, lean_object* v_A_7264_, lean_object* v_B_7265_){
_start:
{
lean_object* v___f_7266_; lean_object* v___x_7267_; 
v___f_7266_ = lean_alloc_closure((void*)(lp_competition_Submission_Packed10_tileResults___lam__2), 6, 5);
lean_closure_set(v___f_7266_, 0, v_m_7261_);
lean_closure_set(v___f_7266_, 1, v_n_7262_);
lean_closure_set(v___f_7266_, 2, v_B_7265_);
lean_closure_set(v___f_7266_, 3, v_A_7264_);
lean_closure_set(v___f_7266_, 4, v_p_7263_);
v___x_7267_ = l_Array_ofFn___redArg(v_batch_7260_, v___f_7266_);
return v___x_7267_;
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_Packed10_inlineDecodeC(lean_object* v_m_7268_, lean_object* v_p_7269_, lean_object* v_q_7270_){
_start:
{
lean_object* v___y_7272_; lean_object* v___y_7273_; lean_object* v___y_7274_; lean_object* v_rowSize_7277_; lean_object* v___x_7278_; uint8_t v___x_7279_; uint8_t v___x_7280_; lean_object* v___y_7282_; lean_object* v___y_7283_; lean_object* v___y_7284_; lean_object* v___y_7287_; lean_object* v___y_7288_; lean_object* v___y_7291_; 
v_rowSize_7277_ = lean_nat_mul(v_m_7268_, v_p_7269_);
v___x_7278_ = lean_unsigned_to_nat(0u);
v___x_7279_ = lean_nat_dec_eq(v_rowSize_7277_, v___x_7278_);
v___x_7280_ = lean_nat_dec_eq(v_p_7269_, v___x_7278_);
if (v___x_7279_ == 0)
{
lean_object* v___x_7293_; 
v___x_7293_ = lean_nat_div(v_q_7270_, v_rowSize_7277_);
v___y_7291_ = v___x_7293_;
goto v___jp_7290_;
}
else
{
v___y_7291_ = v___x_7278_;
goto v___jp_7290_;
}
v___jp_7271_:
{
lean_object* v___x_7275_; lean_object* v___x_7276_; 
v___x_7275_ = lean_alloc_ctor(0, 2, 0);
lean_ctor_set(v___x_7275_, 0, v___y_7272_);
lean_ctor_set(v___x_7275_, 1, v___y_7274_);
v___x_7276_ = lean_alloc_ctor(0, 2, 0);
lean_ctor_set(v___x_7276_, 0, v___y_7273_);
lean_ctor_set(v___x_7276_, 1, v___x_7275_);
return v___x_7276_;
}
v___jp_7281_:
{
if (v___x_7280_ == 0)
{
lean_object* v___x_7285_; 
v___x_7285_ = lean_nat_mod(v___y_7282_, v_p_7269_);
lean_dec(v___y_7282_);
v___y_7272_ = v___y_7284_;
v___y_7273_ = v___y_7283_;
v___y_7274_ = v___x_7285_;
goto v___jp_7271_;
}
else
{
lean_dec(v___y_7282_);
v___y_7272_ = v___y_7284_;
v___y_7273_ = v___y_7283_;
v___y_7274_ = v___x_7278_;
goto v___jp_7271_;
}
}
v___jp_7286_:
{
if (v___x_7280_ == 0)
{
lean_object* v___x_7289_; 
v___x_7289_ = lean_nat_div(v___y_7288_, v_p_7269_);
v___y_7282_ = v___y_7288_;
v___y_7283_ = v___y_7287_;
v___y_7284_ = v___x_7289_;
goto v___jp_7281_;
}
else
{
v___y_7282_ = v___y_7288_;
v___y_7283_ = v___y_7287_;
v___y_7284_ = v___x_7278_;
goto v___jp_7281_;
}
}
v___jp_7290_:
{
if (v___x_7279_ == 0)
{
lean_object* v___x_7292_; 
v___x_7292_ = lean_nat_mod(v_q_7270_, v_rowSize_7277_);
lean_dec(v_rowSize_7277_);
v___y_7287_ = v___y_7291_;
v___y_7288_ = v___x_7292_;
goto v___jp_7286_;
}
else
{
lean_dec(v_rowSize_7277_);
v___y_7287_ = v___y_7291_;
v___y_7288_ = v___x_7278_;
goto v___jp_7286_;
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_Packed10_inlineDecodeC___boxed(lean_object* v_m_7294_, lean_object* v_p_7295_, lean_object* v_q_7296_){
_start:
{
lean_object* v_res_7297_; 
v_res_7297_ = lp_competition_Submission_Packed10_inlineDecodeC(v_m_7294_, v_p_7295_, v_q_7296_);
lean_dec(v_q_7296_);
lean_dec(v_p_7295_);
lean_dec(v_m_7294_);
return v_res_7297_;
}
}
LEAN_EXPORT uint32_t lp_competition_Submission_Packed10_outputFromTiles___redArg(lean_object* v_m_7298_, lean_object* v_n_7299_, lean_object* v_p_7300_, lean_object* v_A_7301_, lean_object* v_B_7302_, lean_object* v_tiles_7303_, lean_object* v_q_7304_){
_start:
{
lean_object* v_rowSize_7305_; lean_object* v___x_7306_; lean_object* v___y_7308_; lean_object* v___y_7309_; lean_object* v___y_7310_; uint8_t v___x_7360_; uint8_t v___x_7361_; lean_object* v___y_7363_; lean_object* v___y_7364_; lean_object* v___y_7365_; lean_object* v___y_7368_; lean_object* v___y_7369_; lean_object* v___y_7372_; 
v_rowSize_7305_ = lean_nat_mul(v_m_7298_, v_p_7300_);
v___x_7306_ = lean_unsigned_to_nat(0u);
v___x_7360_ = lean_nat_dec_eq(v_rowSize_7305_, v___x_7306_);
v___x_7361_ = lean_nat_dec_eq(v_p_7300_, v___x_7306_);
if (v___x_7360_ == 0)
{
lean_object* v___x_7374_; 
v___x_7374_ = lean_nat_div(v_q_7304_, v_rowSize_7305_);
v___y_7372_ = v___x_7374_;
goto v___jp_7371_;
}
else
{
v___y_7372_ = v___x_7306_;
goto v___jp_7371_;
}
v___jp_7307_:
{
lean_object* v___x_7311_; lean_object* v___x_7312_; lean_object* v___x_7313_; lean_object* v___x_7314_; lean_object* v___x_7315_; lean_object* v___x_7316_; lean_object* v___x_7317_; lean_object* v___x_7318_; lean_object* v___x_7319_; lean_object* v___x_7320_; lean_object* v___x_7321_; lean_object* v___x_7322_; uint8_t v___x_7323_; 
v___x_7311_ = lean_unsigned_to_nat(10u);
v___x_7312_ = lean_nat_div(v___y_7310_, v___x_7311_);
v___x_7313_ = lean_nat_mod(v___y_7310_, v___x_7311_);
v___x_7314_ = lean_nat_mul(v___y_7309_, v_m_7298_);
v___x_7315_ = lean_nat_add(v___x_7314_, v___y_7308_);
lean_dec(v___x_7314_);
v___x_7316_ = lean_nat_mul(v___x_7315_, v_n_7299_);
lean_dec(v___x_7315_);
v___x_7317_ = lean_nat_mul(v___y_7309_, v_n_7299_);
v___x_7318_ = lean_nat_mul(v___x_7317_, v_p_7300_);
lean_dec(v___x_7317_);
v___x_7319_ = lean_nat_add(v___x_7318_, v___y_7310_);
lean_dec(v___y_7310_);
lean_dec(v___x_7318_);
v___x_7320_ = lean_array_fget_borrowed(v_tiles_7303_, v___y_7309_);
lean_dec(v___y_7309_);
v___x_7321_ = lean_array_fget_borrowed(v___x_7320_, v___y_7308_);
lean_dec(v___y_7308_);
v___x_7322_ = lean_array_fget_borrowed(v___x_7321_, v___x_7312_);
lean_dec(v___x_7312_);
v___x_7323_ = lean_nat_dec_eq(v___x_7313_, v___x_7306_);
if (v___x_7323_ == 0)
{
lean_object* v___x_7324_; uint8_t v___x_7325_; 
v___x_7324_ = lean_unsigned_to_nat(1u);
v___x_7325_ = lean_nat_dec_eq(v___x_7313_, v___x_7324_);
if (v___x_7325_ == 0)
{
lean_object* v___x_7326_; uint8_t v___x_7327_; 
v___x_7326_ = lean_unsigned_to_nat(2u);
v___x_7327_ = lean_nat_dec_eq(v___x_7313_, v___x_7326_);
if (v___x_7327_ == 0)
{
lean_object* v___x_7328_; uint8_t v___x_7329_; 
v___x_7328_ = lean_unsigned_to_nat(3u);
v___x_7329_ = lean_nat_dec_eq(v___x_7313_, v___x_7328_);
if (v___x_7329_ == 0)
{
lean_object* v___x_7330_; uint8_t v___x_7331_; 
v___x_7330_ = lean_unsigned_to_nat(4u);
v___x_7331_ = lean_nat_dec_eq(v___x_7313_, v___x_7330_);
if (v___x_7331_ == 0)
{
lean_object* v___x_7332_; uint8_t v___x_7333_; 
v___x_7332_ = lean_unsigned_to_nat(5u);
v___x_7333_ = lean_nat_dec_eq(v___x_7313_, v___x_7332_);
if (v___x_7333_ == 0)
{
lean_object* v___x_7334_; uint8_t v___x_7335_; 
v___x_7334_ = lean_unsigned_to_nat(6u);
v___x_7335_ = lean_nat_dec_eq(v___x_7313_, v___x_7334_);
if (v___x_7335_ == 0)
{
lean_object* v___x_7336_; uint8_t v___x_7337_; 
v___x_7336_ = lean_unsigned_to_nat(7u);
v___x_7337_ = lean_nat_dec_eq(v___x_7313_, v___x_7336_);
if (v___x_7337_ == 0)
{
lean_object* v___x_7338_; uint8_t v___x_7339_; 
v___x_7338_ = lean_unsigned_to_nat(8u);
v___x_7339_ = lean_nat_dec_eq(v___x_7313_, v___x_7338_);
lean_dec(v___x_7313_);
if (v___x_7339_ == 0)
{
float v_s9_7340_; uint32_t v___x_7341_; 
v_s9_7340_ = lean_ctor_get_float32(v___x_7322_, 36);
v___x_7341_ = lp_competition_Submission_Packed10_finish(v_n_7299_, v___x_7316_, v___x_7319_, v_p_7300_, v_A_7301_, v_B_7302_, v_s9_7340_);
lean_dec(v___x_7319_);
lean_dec(v___x_7316_);
return v___x_7341_;
}
else
{
float v_s8_7342_; uint32_t v___x_7343_; 
v_s8_7342_ = lean_ctor_get_float32(v___x_7322_, 32);
v___x_7343_ = lp_competition_Submission_Packed10_finish(v_n_7299_, v___x_7316_, v___x_7319_, v_p_7300_, v_A_7301_, v_B_7302_, v_s8_7342_);
lean_dec(v___x_7319_);
lean_dec(v___x_7316_);
return v___x_7343_;
}
}
else
{
float v_s7_7344_; uint32_t v___x_7345_; 
lean_dec(v___x_7313_);
v_s7_7344_ = lean_ctor_get_float32(v___x_7322_, 28);
v___x_7345_ = lp_competition_Submission_Packed10_finish(v_n_7299_, v___x_7316_, v___x_7319_, v_p_7300_, v_A_7301_, v_B_7302_, v_s7_7344_);
lean_dec(v___x_7319_);
lean_dec(v___x_7316_);
return v___x_7345_;
}
}
else
{
float v_s6_7346_; uint32_t v___x_7347_; 
lean_dec(v___x_7313_);
v_s6_7346_ = lean_ctor_get_float32(v___x_7322_, 24);
v___x_7347_ = lp_competition_Submission_Packed10_finish(v_n_7299_, v___x_7316_, v___x_7319_, v_p_7300_, v_A_7301_, v_B_7302_, v_s6_7346_);
lean_dec(v___x_7319_);
lean_dec(v___x_7316_);
return v___x_7347_;
}
}
else
{
float v_s5_7348_; uint32_t v___x_7349_; 
lean_dec(v___x_7313_);
v_s5_7348_ = lean_ctor_get_float32(v___x_7322_, 20);
v___x_7349_ = lp_competition_Submission_Packed10_finish(v_n_7299_, v___x_7316_, v___x_7319_, v_p_7300_, v_A_7301_, v_B_7302_, v_s5_7348_);
lean_dec(v___x_7319_);
lean_dec(v___x_7316_);
return v___x_7349_;
}
}
else
{
float v_s4_7350_; uint32_t v___x_7351_; 
lean_dec(v___x_7313_);
v_s4_7350_ = lean_ctor_get_float32(v___x_7322_, 16);
v___x_7351_ = lp_competition_Submission_Packed10_finish(v_n_7299_, v___x_7316_, v___x_7319_, v_p_7300_, v_A_7301_, v_B_7302_, v_s4_7350_);
lean_dec(v___x_7319_);
lean_dec(v___x_7316_);
return v___x_7351_;
}
}
else
{
float v_s3_7352_; uint32_t v___x_7353_; 
lean_dec(v___x_7313_);
v_s3_7352_ = lean_ctor_get_float32(v___x_7322_, 12);
v___x_7353_ = lp_competition_Submission_Packed10_finish(v_n_7299_, v___x_7316_, v___x_7319_, v_p_7300_, v_A_7301_, v_B_7302_, v_s3_7352_);
lean_dec(v___x_7319_);
lean_dec(v___x_7316_);
return v___x_7353_;
}
}
else
{
float v_s2_7354_; uint32_t v___x_7355_; 
lean_dec(v___x_7313_);
v_s2_7354_ = lean_ctor_get_float32(v___x_7322_, 8);
v___x_7355_ = lp_competition_Submission_Packed10_finish(v_n_7299_, v___x_7316_, v___x_7319_, v_p_7300_, v_A_7301_, v_B_7302_, v_s2_7354_);
lean_dec(v___x_7319_);
lean_dec(v___x_7316_);
return v___x_7355_;
}
}
else
{
float v_s1_7356_; uint32_t v___x_7357_; 
lean_dec(v___x_7313_);
v_s1_7356_ = lean_ctor_get_float32(v___x_7322_, 4);
v___x_7357_ = lp_competition_Submission_Packed10_finish(v_n_7299_, v___x_7316_, v___x_7319_, v_p_7300_, v_A_7301_, v_B_7302_, v_s1_7356_);
lean_dec(v___x_7319_);
lean_dec(v___x_7316_);
return v___x_7357_;
}
}
else
{
float v_s0_7358_; uint32_t v___x_7359_; 
lean_dec(v___x_7313_);
v_s0_7358_ = lean_ctor_get_float32(v___x_7322_, 0);
v___x_7359_ = lp_competition_Submission_Packed10_finish(v_n_7299_, v___x_7316_, v___x_7319_, v_p_7300_, v_A_7301_, v_B_7302_, v_s0_7358_);
lean_dec(v___x_7319_);
lean_dec(v___x_7316_);
return v___x_7359_;
}
}
v___jp_7362_:
{
if (v___x_7361_ == 0)
{
lean_object* v___x_7366_; 
v___x_7366_ = lean_nat_mod(v___y_7363_, v_p_7300_);
lean_dec(v___y_7363_);
v___y_7308_ = v___y_7365_;
v___y_7309_ = v___y_7364_;
v___y_7310_ = v___x_7366_;
goto v___jp_7307_;
}
else
{
lean_dec(v___y_7363_);
v___y_7308_ = v___y_7365_;
v___y_7309_ = v___y_7364_;
v___y_7310_ = v___x_7306_;
goto v___jp_7307_;
}
}
v___jp_7367_:
{
if (v___x_7361_ == 0)
{
lean_object* v___x_7370_; 
v___x_7370_ = lean_nat_div(v___y_7369_, v_p_7300_);
v___y_7363_ = v___y_7369_;
v___y_7364_ = v___y_7368_;
v___y_7365_ = v___x_7370_;
goto v___jp_7362_;
}
else
{
v___y_7363_ = v___y_7369_;
v___y_7364_ = v___y_7368_;
v___y_7365_ = v___x_7306_;
goto v___jp_7362_;
}
}
v___jp_7371_:
{
if (v___x_7360_ == 0)
{
lean_object* v___x_7373_; 
v___x_7373_ = lean_nat_mod(v_q_7304_, v_rowSize_7305_);
lean_dec(v_rowSize_7305_);
v___y_7368_ = v___y_7372_;
v___y_7369_ = v___x_7373_;
goto v___jp_7367_;
}
else
{
lean_dec(v_rowSize_7305_);
v___y_7368_ = v___y_7372_;
v___y_7369_ = v___x_7306_;
goto v___jp_7367_;
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_Packed10_outputFromTiles___redArg___boxed(lean_object* v_m_7375_, lean_object* v_n_7376_, lean_object* v_p_7377_, lean_object* v_A_7378_, lean_object* v_B_7379_, lean_object* v_tiles_7380_, lean_object* v_q_7381_){
_start:
{
uint32_t v_res_7382_; lean_object* v_r_7383_; 
v_res_7382_ = lp_competition_Submission_Packed10_outputFromTiles___redArg(v_m_7375_, v_n_7376_, v_p_7377_, v_A_7378_, v_B_7379_, v_tiles_7380_, v_q_7381_);
lean_dec(v_q_7381_);
lean_dec_ref(v_tiles_7380_);
lean_dec_ref(v_B_7379_);
lean_dec_ref(v_A_7378_);
lean_dec(v_p_7377_);
lean_dec(v_n_7376_);
lean_dec(v_m_7375_);
v_r_7383_ = lean_box_uint32(v_res_7382_);
return v_r_7383_;
}
}
LEAN_EXPORT uint32_t lp_competition_Submission_Packed10_outputFromTiles(lean_object* v_batch_7384_, lean_object* v_m_7385_, lean_object* v_n_7386_, lean_object* v_p_7387_, lean_object* v_A_7388_, lean_object* v_B_7389_, lean_object* v_tiles_7390_, lean_object* v_q_7391_){
_start:
{
uint32_t v___x_7392_; 
v___x_7392_ = lp_competition_Submission_Packed10_outputFromTiles___redArg(v_m_7385_, v_n_7386_, v_p_7387_, v_A_7388_, v_B_7389_, v_tiles_7390_, v_q_7391_);
return v___x_7392_;
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_Packed10_outputFromTiles___boxed(lean_object* v_batch_7393_, lean_object* v_m_7394_, lean_object* v_n_7395_, lean_object* v_p_7396_, lean_object* v_A_7397_, lean_object* v_B_7398_, lean_object* v_tiles_7399_, lean_object* v_q_7400_){
_start:
{
uint32_t v_res_7401_; lean_object* v_r_7402_; 
v_res_7401_ = lp_competition_Submission_Packed10_outputFromTiles(v_batch_7393_, v_m_7394_, v_n_7395_, v_p_7396_, v_A_7397_, v_B_7398_, v_tiles_7399_, v_q_7400_);
lean_dec(v_q_7400_);
lean_dec_ref(v_tiles_7399_);
lean_dec_ref(v_B_7398_);
lean_dec_ref(v_A_7397_);
lean_dec(v_p_7396_);
lean_dec(v_n_7395_);
lean_dec(v_m_7394_);
lean_dec(v_batch_7393_);
v_r_7402_ = lean_box_uint32(v_res_7401_);
return v_r_7402_;
}
}
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_mapMUnsafe_map___at___00Submission_Packed10_core_spec__0(size_t v_sz_7403_, size_t v_i_7404_, lean_object* v_bs_7405_){
_start:
{
uint8_t v___x_7406_; 
v___x_7406_ = lean_usize_dec_lt(v_i_7404_, v_sz_7403_);
if (v___x_7406_ == 0)
{
return v_bs_7405_;
}
else
{
lean_object* v_v_7407_; lean_object* v___x_7408_; lean_object* v_bs_x27_7409_; uint32_t v___x_7410_; float v___x_7411_; size_t v___x_7412_; size_t v___x_7413_; lean_object* v___x_7414_; lean_object* v___x_7415_; 
v_v_7407_ = lean_array_uget(v_bs_7405_, v_i_7404_);
v___x_7408_ = lean_unsigned_to_nat(0u);
v_bs_x27_7409_ = lean_array_uset(v_bs_7405_, v_i_7404_, v___x_7408_);
v___x_7410_ = lean_unbox_uint32(v_v_7407_);
lean_dec(v_v_7407_);
v___x_7411_ = lean_float32_of_bits(v___x_7410_);
v___x_7412_ = ((size_t)1ULL);
v___x_7413_ = lean_usize_add(v_i_7404_, v___x_7412_);
v___x_7414_ = lean_box_float32(v___x_7411_);
v___x_7415_ = lean_array_uset(v_bs_x27_7409_, v_i_7404_, v___x_7414_);
v_i_7404_ = v___x_7413_;
v_bs_7405_ = v___x_7415_;
goto _start;
}
}
}
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_mapMUnsafe_map___at___00Submission_Packed10_core_spec__0___boxed(lean_object* v_sz_7417_, lean_object* v_i_7418_, lean_object* v_bs_7419_){
_start:
{
size_t v_sz_boxed_7420_; size_t v_i_boxed_7421_; lean_object* v_res_7422_; 
v_sz_boxed_7420_ = lean_unbox_usize(v_sz_7417_);
lean_dec(v_sz_7417_);
v_i_boxed_7421_ = lean_unbox_usize(v_i_7418_);
lean_dec(v_i_7418_);
v_res_7422_ = lp_competition___private_Init_Data_Array_Basic_0__Array_mapMUnsafe_map___at___00Submission_Packed10_core_spec__0(v_sz_boxed_7420_, v_i_boxed_7421_, v_bs_7419_);
return v_res_7422_;
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_Packed10_core(lean_object* v_batch_7423_, lean_object* v_m_7424_, lean_object* v_n_7425_, lean_object* v_p_7426_, lean_object* v_A_7427_, lean_object* v_B_7428_){
_start:
{
size_t v_sz_7429_; size_t v___x_7430_; lean_object* v_nativeA_7431_; lean_object* v_packedB_7432_; lean_object* v_tiles_7433_; lean_object* v___x_7434_; lean_object* v___x_7435_; lean_object* v___x_7436_; lean_object* v___x_7437_; 
v_sz_7429_ = lean_array_size(v_A_7427_);
v___x_7430_ = ((size_t)0ULL);
lean_inc_ref(v_A_7427_);
v_nativeA_7431_ = lp_competition___private_Init_Data_Array_Basic_0__Array_mapMUnsafe_map___at___00Submission_Packed10_core_spec__0(v_sz_7429_, v___x_7430_, v_A_7427_);
lean_inc_ref(v_B_7428_);
lean_inc_n(v_p_7426_, 2);
lean_inc_n(v_n_7425_, 2);
lean_inc_n(v_batch_7423_, 2);
v_packedB_7432_ = lp_competition_Submission_Packed10_packB(v_batch_7423_, v_n_7425_, v_p_7426_, v_B_7428_);
lean_inc(v_m_7424_);
v_tiles_7433_ = lp_competition_Submission_Packed10_tileResults(v_batch_7423_, v_m_7424_, v_n_7425_, v_p_7426_, v_nativeA_7431_, v_packedB_7432_);
v___x_7434_ = lean_nat_mul(v_batch_7423_, v_m_7424_);
v___x_7435_ = lean_nat_mul(v___x_7434_, v_p_7426_);
lean_dec(v___x_7434_);
v___x_7436_ = lean_alloc_closure((void*)(lp_competition_Submission_Packed10_outputFromTiles___boxed), 8, 7);
lean_closure_set(v___x_7436_, 0, v_batch_7423_);
lean_closure_set(v___x_7436_, 1, v_m_7424_);
lean_closure_set(v___x_7436_, 2, v_n_7425_);
lean_closure_set(v___x_7436_, 3, v_p_7426_);
lean_closure_set(v___x_7436_, 4, v_A_7427_);
lean_closure_set(v___x_7436_, 5, v_B_7428_);
lean_closure_set(v___x_7436_, 6, v_tiles_7433_);
v___x_7437_ = l_Array_ofFn___redArg(v___x_7435_, v___x_7436_);
return v___x_7437_;
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_bmmR4(lean_object* v_batch_7438_, lean_object* v_m_7439_, lean_object* v_n_7440_, lean_object* v_p_7441_, lean_object* v_A_7442_, lean_object* v_B_7443_){
_start:
{
lean_object* v___x_7444_; lean_object* v___x_7445_; lean_object* v___x_7446_; uint8_t v___x_7447_; 
v___x_7444_ = lean_nat_mul(v_batch_7438_, v_m_7439_);
v___x_7445_ = lean_nat_mul(v___x_7444_, v_p_7441_);
lean_dec(v___x_7444_);
v___x_7446_ = lean_unsigned_to_nat(0u);
v___x_7447_ = lean_nat_dec_eq(v___x_7445_, v___x_7446_);
lean_dec(v___x_7445_);
if (v___x_7447_ == 0)
{
uint8_t v___x_7448_; 
v___x_7448_ = lean_nat_dec_eq(v_n_7440_, v___x_7446_);
if (v___x_7448_ == 0)
{
lean_object* v___x_7449_; 
v___x_7449_ = lp_competition_Submission_Packed10_core(v_batch_7438_, v_m_7439_, v_n_7440_, v_p_7441_, v_A_7442_, v_B_7443_);
return v___x_7449_;
}
else
{
lean_object* v___x_7450_; 
v___x_7450_ = lp_competition_Submission_referenceBmm(v_batch_7438_, v_m_7439_, v_n_7440_, v_p_7441_, v_A_7442_, v_B_7443_);
lean_dec(v_batch_7438_);
return v___x_7450_;
}
}
else
{
lean_object* v___x_7451_; 
v___x_7451_ = lp_competition_Submission_referenceBmm(v_batch_7438_, v_m_7439_, v_n_7440_, v_p_7441_, v_A_7442_, v_B_7443_);
lean_dec(v_batch_7438_);
return v___x_7451_;
}
}
}
LEAN_EXPORT float lp_competition_Submission_NativeDecodeSum_decode(uint32_t v_x_7452_){
_start:
{
uint8_t v___y_7454_; uint32_t v___x_7468_; uint32_t v_a_7469_; uint32_t v___x_7470_; uint32_t v___x_7471_; uint32_t v___x_7472_; uint8_t v___x_7473_; 
v___x_7468_ = 2147483647;
v_a_7469_ = lean_uint32_land(v_x_7452_, v___x_7468_);
v___x_7470_ = 201326591;
v___x_7471_ = 1;
v___x_7472_ = lean_uint32_sub(v_a_7469_, v___x_7471_);
v___x_7473_ = lean_uint32_dec_le(v___x_7470_, v___x_7472_);
if (v___x_7473_ == 0)
{
v___y_7454_ = v___x_7473_;
goto v___jp_7453_;
}
else
{
uint32_t v___x_7474_; uint8_t v___x_7475_; 
v___x_7474_ = 2139095040;
v___x_7475_ = lean_uint32_dec_lt(v_a_7469_, v___x_7474_);
v___y_7454_ = v___x_7475_;
goto v___jp_7453_;
}
v___jp_7453_:
{
if (v___y_7454_ == 0)
{
float v___x_7455_; 
v___x_7455_ = lean_float32_of_bits(v_x_7452_);
return v___x_7455_;
}
else
{
uint32_t v___x_7456_; uint32_t v___x_7457_; uint32_t v___x_7458_; uint32_t v___x_7459_; float v___x_7460_; lean_object* v___x_7461_; uint32_t v___x_7462_; uint32_t v___x_7463_; lean_object* v___x_7464_; lean_object* v___x_7465_; float v___x_7466_; float v___x_7467_; 
v___x_7456_ = 8388607;
v___x_7457_ = lean_uint32_land(v_x_7452_, v___x_7456_);
v___x_7458_ = 8388608;
v___x_7459_ = lean_uint32_lor(v___x_7457_, v___x_7458_);
v___x_7460_ = lean_uint32_to_float32(v___x_7459_);
v___x_7461_ = lp_competition_R2W01b_scaleTable;
v___x_7462_ = 23;
v___x_7463_ = lean_uint32_shift_right(v_x_7452_, v___x_7462_);
v___x_7464_ = lean_uint32_to_nat(v___x_7463_);
v___x_7465_ = lean_array_fget_borrowed(v___x_7461_, v___x_7464_);
lean_dec(v___x_7464_);
v___x_7466_ = lean_unbox_float32(v___x_7465_);
v___x_7467_ = lean_float32_mul(v___x_7460_, v___x_7466_);
return v___x_7467_;
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_NativeDecodeSum_decode___boxed(lean_object* v_x_7476_){
_start:
{
uint32_t v_x_boxed_7477_; float v_res_7478_; lean_object* v_r_7479_; 
v_x_boxed_7477_ = lean_unbox_uint32(v_x_7476_);
lean_dec(v_x_7476_);
v_res_7478_ = lp_competition_Submission_NativeDecodeSum_decode(v_x_boxed_7477_);
v_r_7479_ = lean_box_float32(v_res_7478_);
return v_r_7479_;
}
}
LEAN_EXPORT float lp_competition_Submission_NativeDecodeSum_loop(lean_object* v_n_7480_, lean_object* v_x_7481_, lean_object* v_k_7482_, float v_acc_7483_){
_start:
{
uint8_t v___x_7484_; 
v___x_7484_ = lean_nat_dec_lt(v_k_7482_, v_n_7480_);
if (v___x_7484_ == 0)
{
lean_dec(v_k_7482_);
return v_acc_7483_;
}
else
{
lean_object* v___x_7485_; lean_object* v___x_7486_; float v___y_7488_; lean_object* v___x_7491_; uint8_t v___y_7493_; uint32_t v___x_7510_; uint32_t v___x_7511_; uint32_t v_a_7512_; uint32_t v___x_7513_; uint32_t v___x_7514_; uint32_t v___x_7515_; uint8_t v___x_7516_; 
v___x_7485_ = lean_unsigned_to_nat(1u);
v___x_7486_ = lean_nat_add(v_k_7482_, v___x_7485_);
v___x_7491_ = lean_array_fget_borrowed(v_x_7481_, v_k_7482_);
lean_dec(v_k_7482_);
v___x_7510_ = 2147483647;
v___x_7511_ = lean_unbox_uint32(v___x_7491_);
v_a_7512_ = lean_uint32_land(v___x_7511_, v___x_7510_);
v___x_7513_ = 201326591;
v___x_7514_ = 1;
v___x_7515_ = lean_uint32_sub(v_a_7512_, v___x_7514_);
v___x_7516_ = lean_uint32_dec_le(v___x_7513_, v___x_7515_);
if (v___x_7516_ == 0)
{
v___y_7493_ = v___x_7516_;
goto v___jp_7492_;
}
else
{
uint32_t v___x_7517_; uint8_t v___x_7518_; 
v___x_7517_ = 2139095040;
v___x_7518_ = lean_uint32_dec_lt(v_a_7512_, v___x_7517_);
v___y_7493_ = v___x_7518_;
goto v___jp_7492_;
}
v___jp_7487_:
{
float v___x_7489_; 
v___x_7489_ = lean_float32_add(v_acc_7483_, v___y_7488_);
v_k_7482_ = v___x_7486_;
v_acc_7483_ = v___x_7489_;
goto _start;
}
v___jp_7492_:
{
if (v___y_7493_ == 0)
{
uint32_t v___x_7494_; float v___x_7495_; 
v___x_7494_ = lean_unbox_uint32(v___x_7491_);
v___x_7495_ = lean_float32_of_bits(v___x_7494_);
v___y_7488_ = v___x_7495_;
goto v___jp_7487_;
}
else
{
uint32_t v___x_7496_; uint32_t v___x_7497_; uint32_t v___x_7498_; uint32_t v___x_7499_; uint32_t v___x_7500_; float v___x_7501_; lean_object* v___x_7502_; uint32_t v___x_7503_; uint32_t v___x_7504_; uint32_t v___x_7505_; lean_object* v___x_7506_; lean_object* v___x_7507_; float v___x_7508_; float v___x_7509_; 
v___x_7496_ = 8388607;
v___x_7497_ = lean_unbox_uint32(v___x_7491_);
v___x_7498_ = lean_uint32_land(v___x_7497_, v___x_7496_);
v___x_7499_ = 8388608;
v___x_7500_ = lean_uint32_lor(v___x_7498_, v___x_7499_);
v___x_7501_ = lean_uint32_to_float32(v___x_7500_);
v___x_7502_ = lp_competition_R2W01b_scaleTable;
v___x_7503_ = 23;
v___x_7504_ = lean_unbox_uint32(v___x_7491_);
v___x_7505_ = lean_uint32_shift_right(v___x_7504_, v___x_7503_);
v___x_7506_ = lean_uint32_to_nat(v___x_7505_);
v___x_7507_ = lean_array_fget_borrowed(v___x_7502_, v___x_7506_);
lean_dec(v___x_7506_);
v___x_7508_ = lean_unbox_float32(v___x_7507_);
v___x_7509_ = lean_float32_mul(v___x_7501_, v___x_7508_);
v___y_7488_ = v___x_7509_;
goto v___jp_7487_;
}
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_NativeDecodeSum_loop___boxed(lean_object* v_n_7519_, lean_object* v_x_7520_, lean_object* v_k_7521_, lean_object* v_acc_7522_){
_start:
{
float v_acc_boxed_7523_; float v_res_7524_; lean_object* v_r_7525_; 
v_acc_boxed_7523_ = lean_unbox_float32(v_acc_7522_);
lean_dec_ref(v_acc_7522_);
v_res_7524_ = lp_competition_Submission_NativeDecodeSum_loop(v_n_7519_, v_x_7520_, v_k_7521_, v_acc_boxed_7523_);
lean_dec_ref(v_x_7520_);
lean_dec(v_n_7519_);
v_r_7525_ = lean_box_float32(v_res_7524_);
return v_r_7525_;
}
}
LEAN_EXPORT float lp_competition_Submission_NativeDecodeSumWord_loop___redArg(lean_object* v_x_7526_, size_t v_count_7527_, size_t v_k_7528_, float v_acc_7529_){
_start:
{
uint8_t v___x_7530_; 
v___x_7530_ = lean_usize_dec_lt(v_k_7528_, v_count_7527_);
if (v___x_7530_ == 0)
{
return v_acc_7529_;
}
else
{
lean_object* v_value_7531_; size_t v___x_7532_; size_t v___x_7533_; float v___y_7535_; uint8_t v___y_7539_; uint32_t v___x_7556_; uint32_t v___x_7557_; uint32_t v_a_7558_; uint32_t v___x_7559_; uint32_t v___x_7560_; uint32_t v___x_7561_; uint8_t v___x_7562_; 
v_value_7531_ = lean_array_uget_borrowed(v_x_7526_, v_k_7528_);
v___x_7532_ = ((size_t)1ULL);
v___x_7533_ = lean_usize_add(v_k_7528_, v___x_7532_);
v___x_7556_ = 2147483647;
v___x_7557_ = lean_unbox_uint32(v_value_7531_);
v_a_7558_ = lean_uint32_land(v___x_7557_, v___x_7556_);
v___x_7559_ = 201326591;
v___x_7560_ = 1;
v___x_7561_ = lean_uint32_sub(v_a_7558_, v___x_7560_);
v___x_7562_ = lean_uint32_dec_le(v___x_7559_, v___x_7561_);
if (v___x_7562_ == 0)
{
v___y_7539_ = v___x_7562_;
goto v___jp_7538_;
}
else
{
uint32_t v___x_7563_; uint8_t v___x_7564_; 
v___x_7563_ = 2139095040;
v___x_7564_ = lean_uint32_dec_lt(v_a_7558_, v___x_7563_);
v___y_7539_ = v___x_7564_;
goto v___jp_7538_;
}
v___jp_7534_:
{
float v___x_7536_; 
v___x_7536_ = lean_float32_add(v_acc_7529_, v___y_7535_);
v_k_7528_ = v___x_7533_;
v_acc_7529_ = v___x_7536_;
goto _start;
}
v___jp_7538_:
{
if (v___y_7539_ == 0)
{
uint32_t v___x_7540_; float v___x_7541_; 
v___x_7540_ = lean_unbox_uint32(v_value_7531_);
v___x_7541_ = lean_float32_of_bits(v___x_7540_);
v___y_7535_ = v___x_7541_;
goto v___jp_7534_;
}
else
{
uint32_t v___x_7542_; uint32_t v___x_7543_; uint32_t v___x_7544_; uint32_t v___x_7545_; uint32_t v___x_7546_; float v___x_7547_; lean_object* v___x_7548_; uint32_t v___x_7549_; uint32_t v___x_7550_; uint32_t v___x_7551_; lean_object* v___x_7552_; lean_object* v___x_7553_; float v___x_7554_; float v___x_7555_; 
v___x_7542_ = 8388607;
v___x_7543_ = lean_unbox_uint32(v_value_7531_);
v___x_7544_ = lean_uint32_land(v___x_7543_, v___x_7542_);
v___x_7545_ = 8388608;
v___x_7546_ = lean_uint32_lor(v___x_7544_, v___x_7545_);
v___x_7547_ = lean_uint32_to_float32(v___x_7546_);
v___x_7548_ = lp_competition_R2W01b_scaleTable;
v___x_7549_ = 23;
v___x_7550_ = lean_unbox_uint32(v_value_7531_);
v___x_7551_ = lean_uint32_shift_right(v___x_7550_, v___x_7549_);
v___x_7552_ = lean_uint32_to_nat(v___x_7551_);
v___x_7553_ = lean_array_fget_borrowed(v___x_7548_, v___x_7552_);
lean_dec(v___x_7552_);
v___x_7554_ = lean_unbox_float32(v___x_7553_);
v___x_7555_ = lean_float32_mul(v___x_7547_, v___x_7554_);
v___y_7535_ = v___x_7555_;
goto v___jp_7534_;
}
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_NativeDecodeSumWord_loop___redArg___boxed(lean_object* v_x_7565_, lean_object* v_count_7566_, lean_object* v_k_7567_, lean_object* v_acc_7568_){
_start:
{
size_t v_count_boxed_7569_; size_t v_k_boxed_7570_; float v_acc_boxed_7571_; float v_res_7572_; lean_object* v_r_7573_; 
v_count_boxed_7569_ = lean_unbox_usize(v_count_7566_);
lean_dec(v_count_7566_);
v_k_boxed_7570_ = lean_unbox_usize(v_k_7567_);
lean_dec(v_k_7567_);
v_acc_boxed_7571_ = lean_unbox_float32(v_acc_7568_);
lean_dec_ref(v_acc_7568_);
v_res_7572_ = lp_competition_Submission_NativeDecodeSumWord_loop___redArg(v_x_7565_, v_count_boxed_7569_, v_k_boxed_7570_, v_acc_boxed_7571_);
lean_dec_ref(v_x_7565_);
v_r_7573_ = lean_box_float32(v_res_7572_);
return v_r_7573_;
}
}
LEAN_EXPORT float lp_competition_Submission_NativeDecodeSumWord_loop(lean_object* v_n_7574_, lean_object* v_x_7575_, size_t v_count_7576_, lean_object* v_hn_7577_, size_t v_k_7578_, float v_acc_7579_){
_start:
{
float v___x_7580_; 
v___x_7580_ = lp_competition_Submission_NativeDecodeSumWord_loop___redArg(v_x_7575_, v_count_7576_, v_k_7578_, v_acc_7579_);
return v___x_7580_;
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_NativeDecodeSumWord_loop___boxed(lean_object* v_n_7581_, lean_object* v_x_7582_, lean_object* v_count_7583_, lean_object* v_hn_7584_, lean_object* v_k_7585_, lean_object* v_acc_7586_){
_start:
{
size_t v_count_boxed_7587_; size_t v_k_boxed_7588_; float v_acc_boxed_7589_; float v_res_7590_; lean_object* v_r_7591_; 
v_count_boxed_7587_ = lean_unbox_usize(v_count_7583_);
lean_dec(v_count_7583_);
v_k_boxed_7588_ = lean_unbox_usize(v_k_7585_);
lean_dec(v_k_7585_);
v_acc_boxed_7589_ = lean_unbox_float32(v_acc_7586_);
lean_dec_ref(v_acc_7586_);
v_res_7590_ = lp_competition_Submission_NativeDecodeSumWord_loop(v_n_7581_, v_x_7582_, v_count_boxed_7587_, v_hn_7584_, v_k_boxed_7588_, v_acc_boxed_7589_);
lean_dec_ref(v_x_7582_);
lean_dec(v_n_7581_);
v_r_7591_ = lean_box_float32(v_res_7590_);
return v_r_7591_;
}
}
LEAN_EXPORT float lp_competition_Submission_NativeDecodeSumWord_run(lean_object* v_n_7592_, lean_object* v_x_7593_){
_start:
{
lean_object* v___x_7594_; uint8_t v___x_7595_; 
v___x_7594_ = lean_obj_once(&lp_competition_Submission_Packed10Index_runDot___closed__0, &lp_competition_Submission_Packed10Index_runDot___closed__0_once, _init_lp_competition_Submission_Packed10Index_runDot___closed__0);
v___x_7595_ = lean_nat_dec_lt(v_n_7592_, v___x_7594_);
if (v___x_7595_ == 0)
{
lean_object* v___x_7596_; float v___x_7597_; float v___x_7598_; 
v___x_7596_ = lean_unsigned_to_nat(0u);
v___x_7597_ = lean_float32_once(&lp_competition_Submission_NativeFinal_dot___closed__0, &lp_competition_Submission_NativeFinal_dot___closed__0_once, _init_lp_competition_Submission_NativeFinal_dot___closed__0);
v___x_7598_ = lp_competition_Submission_NativeDecodeSum_loop(v_n_7592_, v_x_7593_, v___x_7596_, v___x_7597_);
return v___x_7598_;
}
else
{
size_t v___x_7599_; size_t v___x_7600_; float v___x_7601_; float v___x_7602_; 
v___x_7599_ = lean_usize_of_nat(v_n_7592_);
v___x_7600_ = ((size_t)0ULL);
v___x_7601_ = lean_float32_once(&lp_competition_Submission_NativeFinal_dot___closed__0, &lp_competition_Submission_NativeFinal_dot___closed__0_once, _init_lp_competition_Submission_NativeFinal_dot___closed__0);
v___x_7602_ = lp_competition_Submission_NativeDecodeSumWord_loop___redArg(v_x_7593_, v___x_7599_, v___x_7600_, v___x_7601_);
return v___x_7602_;
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_NativeDecodeSumWord_run___boxed(lean_object* v_n_7603_, lean_object* v_x_7604_){
_start:
{
float v_res_7605_; lean_object* v_r_7606_; 
v_res_7605_ = lp_competition_Submission_NativeDecodeSumWord_run(v_n_7603_, v_x_7604_);
lean_dec_ref(v_x_7604_);
lean_dec(v_n_7603_);
v_r_7606_ = lean_box_float32(v_res_7605_);
return v_r_7606_;
}
}
LEAN_EXPORT uint32_t lp_competition_Submission_sum(lean_object* v_n_7607_, lean_object* v_x_7608_){
_start:
{
float v___y_7610_; lean_object* v___x_7614_; uint8_t v___x_7615_; 
v___x_7614_ = lean_obj_once(&lp_competition_Submission_Packed10Index_runDot___closed__0, &lp_competition_Submission_Packed10Index_runDot___closed__0_once, _init_lp_competition_Submission_Packed10Index_runDot___closed__0);
v___x_7615_ = lean_nat_dec_lt(v_n_7607_, v___x_7614_);
if (v___x_7615_ == 0)
{
lean_object* v___x_7616_; float v___x_7617_; float v___x_7618_; 
v___x_7616_ = lean_unsigned_to_nat(0u);
v___x_7617_ = lean_float32_once(&lp_competition_Submission_NativeFinal_dot___closed__0, &lp_competition_Submission_NativeFinal_dot___closed__0_once, _init_lp_competition_Submission_NativeFinal_dot___closed__0);
v___x_7618_ = lp_competition_Submission_NativeDecodeSum_loop(v_n_7607_, v_x_7608_, v___x_7616_, v___x_7617_);
v___y_7610_ = v___x_7618_;
goto v___jp_7609_;
}
else
{
size_t v___x_7619_; size_t v___x_7620_; float v___x_7621_; float v___x_7622_; 
v___x_7619_ = lean_usize_of_nat(v_n_7607_);
v___x_7620_ = ((size_t)0ULL);
v___x_7621_ = lean_float32_once(&lp_competition_Submission_NativeFinal_dot___closed__0, &lp_competition_Submission_NativeFinal_dot___closed__0_once, _init_lp_competition_Submission_NativeFinal_dot___closed__0);
v___x_7622_ = lp_competition_Submission_NativeDecodeSumWord_loop___redArg(v_x_7608_, v___x_7619_, v___x_7620_, v___x_7621_);
v___y_7610_ = v___x_7622_;
goto v___jp_7609_;
}
v___jp_7609_:
{
uint8_t v___x_7611_; 
v___x_7611_ = lean_float32_isfinite(v___y_7610_);
if (v___x_7611_ == 0)
{
uint32_t v___x_7612_; 
v___x_7612_ = lp_competition_Submission_referenceSum___redArg(v_x_7608_);
return v___x_7612_;
}
else
{
uint32_t v___x_7613_; 
v___x_7613_ = lean_float32_to_bits(v___y_7610_);
return v___x_7613_;
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_sum___boxed(lean_object* v_n_7623_, lean_object* v_x_7624_){
_start:
{
uint32_t v_res_7625_; lean_object* v_r_7626_; 
v_res_7625_ = lp_competition_Submission_sum(v_n_7623_, v_x_7624_);
lean_dec_ref(v_x_7624_);
lean_dec(v_n_7623_);
v_r_7626_ = lean_box_uint32(v_res_7625_);
return v_r_7626_;
}
}
LEAN_EXPORT uint32_t lp_competition_Submission_RowOutput_row___redArg___lam__0(lean_object* v_baseB_7627_, lean_object* v_tiles_7628_, lean_object* v_n_7629_, lean_object* v_baseA_7630_, lean_object* v_p_7631_, lean_object* v_A_7632_, lean_object* v_B_7633_, lean_object* v_j_7634_){
_start:
{
lean_object* v___x_7635_; lean_object* v___x_7636_; lean_object* v___x_7637_; lean_object* v___x_7638_; lean_object* v___x_7639_; lean_object* v___x_7640_; uint8_t v___x_7641_; 
v___x_7635_ = lean_unsigned_to_nat(10u);
v___x_7636_ = lean_nat_div(v_j_7634_, v___x_7635_);
v___x_7637_ = lean_nat_mod(v_j_7634_, v___x_7635_);
v___x_7638_ = lean_nat_add(v_baseB_7627_, v_j_7634_);
v___x_7639_ = lean_array_fget_borrowed(v_tiles_7628_, v___x_7636_);
lean_dec(v___x_7636_);
v___x_7640_ = lean_unsigned_to_nat(0u);
v___x_7641_ = lean_nat_dec_eq(v___x_7637_, v___x_7640_);
if (v___x_7641_ == 0)
{
lean_object* v___x_7642_; uint8_t v___x_7643_; 
v___x_7642_ = lean_unsigned_to_nat(1u);
v___x_7643_ = lean_nat_dec_eq(v___x_7637_, v___x_7642_);
if (v___x_7643_ == 0)
{
lean_object* v___x_7644_; uint8_t v___x_7645_; 
v___x_7644_ = lean_unsigned_to_nat(2u);
v___x_7645_ = lean_nat_dec_eq(v___x_7637_, v___x_7644_);
if (v___x_7645_ == 0)
{
lean_object* v___x_7646_; uint8_t v___x_7647_; 
v___x_7646_ = lean_unsigned_to_nat(3u);
v___x_7647_ = lean_nat_dec_eq(v___x_7637_, v___x_7646_);
if (v___x_7647_ == 0)
{
lean_object* v___x_7648_; uint8_t v___x_7649_; 
v___x_7648_ = lean_unsigned_to_nat(4u);
v___x_7649_ = lean_nat_dec_eq(v___x_7637_, v___x_7648_);
if (v___x_7649_ == 0)
{
lean_object* v___x_7650_; uint8_t v___x_7651_; 
v___x_7650_ = lean_unsigned_to_nat(5u);
v___x_7651_ = lean_nat_dec_eq(v___x_7637_, v___x_7650_);
if (v___x_7651_ == 0)
{
lean_object* v___x_7652_; uint8_t v___x_7653_; 
v___x_7652_ = lean_unsigned_to_nat(6u);
v___x_7653_ = lean_nat_dec_eq(v___x_7637_, v___x_7652_);
if (v___x_7653_ == 0)
{
lean_object* v___x_7654_; uint8_t v___x_7655_; 
v___x_7654_ = lean_unsigned_to_nat(7u);
v___x_7655_ = lean_nat_dec_eq(v___x_7637_, v___x_7654_);
if (v___x_7655_ == 0)
{
lean_object* v___x_7656_; uint8_t v___x_7657_; 
v___x_7656_ = lean_unsigned_to_nat(8u);
v___x_7657_ = lean_nat_dec_eq(v___x_7637_, v___x_7656_);
lean_dec(v___x_7637_);
if (v___x_7657_ == 0)
{
float v_s9_7658_; uint32_t v___x_7659_; 
v_s9_7658_ = lean_ctor_get_float32(v___x_7639_, 36);
v___x_7659_ = lp_competition_Submission_Packed10_finish(v_n_7629_, v_baseA_7630_, v___x_7638_, v_p_7631_, v_A_7632_, v_B_7633_, v_s9_7658_);
lean_dec(v___x_7638_);
return v___x_7659_;
}
else
{
float v_s8_7660_; uint32_t v___x_7661_; 
v_s8_7660_ = lean_ctor_get_float32(v___x_7639_, 32);
v___x_7661_ = lp_competition_Submission_Packed10_finish(v_n_7629_, v_baseA_7630_, v___x_7638_, v_p_7631_, v_A_7632_, v_B_7633_, v_s8_7660_);
lean_dec(v___x_7638_);
return v___x_7661_;
}
}
else
{
float v_s7_7662_; uint32_t v___x_7663_; 
lean_dec(v___x_7637_);
v_s7_7662_ = lean_ctor_get_float32(v___x_7639_, 28);
v___x_7663_ = lp_competition_Submission_Packed10_finish(v_n_7629_, v_baseA_7630_, v___x_7638_, v_p_7631_, v_A_7632_, v_B_7633_, v_s7_7662_);
lean_dec(v___x_7638_);
return v___x_7663_;
}
}
else
{
float v_s6_7664_; uint32_t v___x_7665_; 
lean_dec(v___x_7637_);
v_s6_7664_ = lean_ctor_get_float32(v___x_7639_, 24);
v___x_7665_ = lp_competition_Submission_Packed10_finish(v_n_7629_, v_baseA_7630_, v___x_7638_, v_p_7631_, v_A_7632_, v_B_7633_, v_s6_7664_);
lean_dec(v___x_7638_);
return v___x_7665_;
}
}
else
{
float v_s5_7666_; uint32_t v___x_7667_; 
lean_dec(v___x_7637_);
v_s5_7666_ = lean_ctor_get_float32(v___x_7639_, 20);
v___x_7667_ = lp_competition_Submission_Packed10_finish(v_n_7629_, v_baseA_7630_, v___x_7638_, v_p_7631_, v_A_7632_, v_B_7633_, v_s5_7666_);
lean_dec(v___x_7638_);
return v___x_7667_;
}
}
else
{
float v_s4_7668_; uint32_t v___x_7669_; 
lean_dec(v___x_7637_);
v_s4_7668_ = lean_ctor_get_float32(v___x_7639_, 16);
v___x_7669_ = lp_competition_Submission_Packed10_finish(v_n_7629_, v_baseA_7630_, v___x_7638_, v_p_7631_, v_A_7632_, v_B_7633_, v_s4_7668_);
lean_dec(v___x_7638_);
return v___x_7669_;
}
}
else
{
float v_s3_7670_; uint32_t v___x_7671_; 
lean_dec(v___x_7637_);
v_s3_7670_ = lean_ctor_get_float32(v___x_7639_, 12);
v___x_7671_ = lp_competition_Submission_Packed10_finish(v_n_7629_, v_baseA_7630_, v___x_7638_, v_p_7631_, v_A_7632_, v_B_7633_, v_s3_7670_);
lean_dec(v___x_7638_);
return v___x_7671_;
}
}
else
{
float v_s2_7672_; uint32_t v___x_7673_; 
lean_dec(v___x_7637_);
v_s2_7672_ = lean_ctor_get_float32(v___x_7639_, 8);
v___x_7673_ = lp_competition_Submission_Packed10_finish(v_n_7629_, v_baseA_7630_, v___x_7638_, v_p_7631_, v_A_7632_, v_B_7633_, v_s2_7672_);
lean_dec(v___x_7638_);
return v___x_7673_;
}
}
else
{
float v_s1_7674_; uint32_t v___x_7675_; 
lean_dec(v___x_7637_);
v_s1_7674_ = lean_ctor_get_float32(v___x_7639_, 4);
v___x_7675_ = lp_competition_Submission_Packed10_finish(v_n_7629_, v_baseA_7630_, v___x_7638_, v_p_7631_, v_A_7632_, v_B_7633_, v_s1_7674_);
lean_dec(v___x_7638_);
return v___x_7675_;
}
}
else
{
float v_s0_7676_; uint32_t v___x_7677_; 
lean_dec(v___x_7637_);
v_s0_7676_ = lean_ctor_get_float32(v___x_7639_, 0);
v___x_7677_ = lp_competition_Submission_Packed10_finish(v_n_7629_, v_baseA_7630_, v___x_7638_, v_p_7631_, v_A_7632_, v_B_7633_, v_s0_7676_);
lean_dec(v___x_7638_);
return v___x_7677_;
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_RowOutput_row___redArg___lam__0___boxed(lean_object* v_baseB_7678_, lean_object* v_tiles_7679_, lean_object* v_n_7680_, lean_object* v_baseA_7681_, lean_object* v_p_7682_, lean_object* v_A_7683_, lean_object* v_B_7684_, lean_object* v_j_7685_){
_start:
{
uint32_t v_res_7686_; lean_object* v_r_7687_; 
v_res_7686_ = lp_competition_Submission_RowOutput_row___redArg___lam__0(v_baseB_7678_, v_tiles_7679_, v_n_7680_, v_baseA_7681_, v_p_7682_, v_A_7683_, v_B_7684_, v_j_7685_);
lean_dec(v_j_7685_);
lean_dec_ref(v_B_7684_);
lean_dec_ref(v_A_7683_);
lean_dec(v_p_7682_);
lean_dec(v_baseA_7681_);
lean_dec(v_n_7680_);
lean_dec_ref(v_tiles_7679_);
lean_dec(v_baseB_7678_);
v_r_7687_ = lean_box_uint32(v_res_7686_);
return v_r_7687_;
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_RowOutput_row___redArg(lean_object* v_m_7688_, lean_object* v_n_7689_, lean_object* v_p_7690_, lean_object* v_A_7691_, lean_object* v_B_7692_, lean_object* v_b_7693_, lean_object* v_i_7694_, lean_object* v_tiles_7695_){
_start:
{
lean_object* v___x_7696_; lean_object* v___x_7697_; lean_object* v_baseA_7698_; lean_object* v___x_7699_; lean_object* v_baseB_7700_; lean_object* v___f_7701_; lean_object* v___x_7702_; 
v___x_7696_ = lean_nat_mul(v_b_7693_, v_m_7688_);
v___x_7697_ = lean_nat_add(v___x_7696_, v_i_7694_);
lean_dec(v___x_7696_);
v_baseA_7698_ = lean_nat_mul(v___x_7697_, v_n_7689_);
lean_dec(v___x_7697_);
v___x_7699_ = lean_nat_mul(v_b_7693_, v_n_7689_);
v_baseB_7700_ = lean_nat_mul(v___x_7699_, v_p_7690_);
lean_dec(v___x_7699_);
lean_inc(v_p_7690_);
v___f_7701_ = lean_alloc_closure((void*)(lp_competition_Submission_RowOutput_row___redArg___lam__0___boxed), 8, 7);
lean_closure_set(v___f_7701_, 0, v_baseB_7700_);
lean_closure_set(v___f_7701_, 1, v_tiles_7695_);
lean_closure_set(v___f_7701_, 2, v_n_7689_);
lean_closure_set(v___f_7701_, 3, v_baseA_7698_);
lean_closure_set(v___f_7701_, 4, v_p_7690_);
lean_closure_set(v___f_7701_, 5, v_A_7691_);
lean_closure_set(v___f_7701_, 6, v_B_7692_);
v___x_7702_ = l_Array_ofFn___redArg(v_p_7690_, v___f_7701_);
return v___x_7702_;
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_RowOutput_row___redArg___boxed(lean_object* v_m_7703_, lean_object* v_n_7704_, lean_object* v_p_7705_, lean_object* v_A_7706_, lean_object* v_B_7707_, lean_object* v_b_7708_, lean_object* v_i_7709_, lean_object* v_tiles_7710_){
_start:
{
lean_object* v_res_7711_; 
v_res_7711_ = lp_competition_Submission_RowOutput_row___redArg(v_m_7703_, v_n_7704_, v_p_7705_, v_A_7706_, v_B_7707_, v_b_7708_, v_i_7709_, v_tiles_7710_);
lean_dec(v_i_7709_);
lean_dec(v_b_7708_);
lean_dec(v_m_7703_);
return v_res_7711_;
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_RowOutput_row(lean_object* v_batch_7712_, lean_object* v_m_7713_, lean_object* v_n_7714_, lean_object* v_p_7715_, lean_object* v_A_7716_, lean_object* v_B_7717_, lean_object* v_b_7718_, lean_object* v_i_7719_, lean_object* v_tiles_7720_){
_start:
{
lean_object* v___x_7721_; 
v___x_7721_ = lp_competition_Submission_RowOutput_row___redArg(v_m_7713_, v_n_7714_, v_p_7715_, v_A_7716_, v_B_7717_, v_b_7718_, v_i_7719_, v_tiles_7720_);
return v___x_7721_;
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_RowOutput_row___boxed(lean_object* v_batch_7722_, lean_object* v_m_7723_, lean_object* v_n_7724_, lean_object* v_p_7725_, lean_object* v_A_7726_, lean_object* v_B_7727_, lean_object* v_b_7728_, lean_object* v_i_7729_, lean_object* v_tiles_7730_){
_start:
{
lean_object* v_res_7731_; 
v_res_7731_ = lp_competition_Submission_RowOutput_row(v_batch_7722_, v_m_7723_, v_n_7724_, v_p_7725_, v_A_7726_, v_B_7727_, v_b_7728_, v_i_7729_, v_tiles_7730_);
lean_dec(v_i_7729_);
lean_dec(v_b_7728_);
lean_dec(v_m_7723_);
lean_dec(v_batch_7722_);
return v_res_7731_;
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_RowOutput_output___lam__0(lean_object* v_batchTiles_7732_, lean_object* v_m_7733_, lean_object* v_n_7734_, lean_object* v_p_7735_, lean_object* v_A_7736_, lean_object* v_B_7737_, lean_object* v_b_7738_, lean_object* v_i_7739_){
_start:
{
lean_object* v___x_7740_; lean_object* v___x_7741_; 
v___x_7740_ = lean_array_fget_borrowed(v_batchTiles_7732_, v_i_7739_);
lean_inc(v___x_7740_);
v___x_7741_ = lp_competition_Submission_RowOutput_row___redArg(v_m_7733_, v_n_7734_, v_p_7735_, v_A_7736_, v_B_7737_, v_b_7738_, v_i_7739_, v___x_7740_);
return v___x_7741_;
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_RowOutput_output___lam__0___boxed(lean_object* v_batchTiles_7742_, lean_object* v_m_7743_, lean_object* v_n_7744_, lean_object* v_p_7745_, lean_object* v_A_7746_, lean_object* v_B_7747_, lean_object* v_b_7748_, lean_object* v_i_7749_){
_start:
{
lean_object* v_res_7750_; 
v_res_7750_ = lp_competition_Submission_RowOutput_output___lam__0(v_batchTiles_7742_, v_m_7743_, v_n_7744_, v_p_7745_, v_A_7746_, v_B_7747_, v_b_7748_, v_i_7749_);
lean_dec(v_i_7749_);
lean_dec(v_b_7748_);
lean_dec(v_m_7743_);
lean_dec_ref(v_batchTiles_7742_);
return v_res_7750_;
}
}
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_mapMUnsafe_map___at___00Submission_RowOutput_output_spec__0(size_t v_sz_7751_, size_t v_i_7752_, lean_object* v_bs_7753_){
_start:
{
uint8_t v___x_7754_; 
v___x_7754_ = lean_usize_dec_lt(v_i_7752_, v_sz_7751_);
if (v___x_7754_ == 0)
{
return v_bs_7753_;
}
else
{
lean_object* v_v_7755_; lean_object* v___x_7756_; lean_object* v_bs_x27_7757_; size_t v___x_7758_; size_t v___x_7759_; lean_object* v___x_7760_; 
v_v_7755_ = lean_array_uget(v_bs_7753_, v_i_7752_);
v___x_7756_ = lean_unsigned_to_nat(0u);
v_bs_x27_7757_ = lean_array_uset(v_bs_7753_, v_i_7752_, v___x_7756_);
v___x_7758_ = ((size_t)1ULL);
v___x_7759_ = lean_usize_add(v_i_7752_, v___x_7758_);
v___x_7760_ = lean_array_uset(v_bs_x27_7757_, v_i_7752_, v_v_7755_);
v_i_7752_ = v___x_7759_;
v_bs_7753_ = v___x_7760_;
goto _start;
}
}
}
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_mapMUnsafe_map___at___00Submission_RowOutput_output_spec__0___boxed(lean_object* v_sz_7762_, lean_object* v_i_7763_, lean_object* v_bs_7764_){
_start:
{
size_t v_sz_boxed_7765_; size_t v_i_boxed_7766_; lean_object* v_res_7767_; 
v_sz_boxed_7765_ = lean_unbox_usize(v_sz_7762_);
lean_dec(v_sz_7762_);
v_i_boxed_7766_ = lean_unbox_usize(v_i_7763_);
lean_dec(v_i_7763_);
v_res_7767_ = lp_competition___private_Init_Data_Array_Basic_0__Array_mapMUnsafe_map___at___00Submission_RowOutput_output_spec__0(v_sz_boxed_7765_, v_i_boxed_7766_, v_bs_7764_);
return v_res_7767_;
}
}
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_foldlMUnsafe_fold___at___00Submission_RowOutput_output_spec__1(lean_object* v_as_7768_, size_t v_i_7769_, size_t v_stop_7770_, lean_object* v_b_7771_){
_start:
{
uint8_t v___x_7772_; 
v___x_7772_ = lean_usize_dec_eq(v_i_7769_, v_stop_7770_);
if (v___x_7772_ == 0)
{
lean_object* v___x_7773_; lean_object* v___x_7774_; size_t v___x_7775_; size_t v___x_7776_; 
v___x_7773_ = lean_array_uget_borrowed(v_as_7768_, v_i_7769_);
v___x_7774_ = l_Array_append___redArg(v_b_7771_, v___x_7773_);
v___x_7775_ = ((size_t)1ULL);
v___x_7776_ = lean_usize_add(v_i_7769_, v___x_7775_);
v_i_7769_ = v___x_7776_;
v_b_7771_ = v___x_7774_;
goto _start;
}
else
{
return v_b_7771_;
}
}
}
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_foldlMUnsafe_fold___at___00Submission_RowOutput_output_spec__1___boxed(lean_object* v_as_7778_, lean_object* v_i_7779_, lean_object* v_stop_7780_, lean_object* v_b_7781_){
_start:
{
size_t v_i_boxed_7782_; size_t v_stop_boxed_7783_; lean_object* v_res_7784_; 
v_i_boxed_7782_ = lean_unbox_usize(v_i_7779_);
lean_dec(v_i_7779_);
v_stop_boxed_7783_ = lean_unbox_usize(v_stop_7780_);
lean_dec(v_stop_7780_);
v_res_7784_ = lp_competition___private_Init_Data_Array_Basic_0__Array_foldlMUnsafe_fold___at___00Submission_RowOutput_output_spec__1(v_as_7778_, v_i_boxed_7782_, v_stop_boxed_7783_, v_b_7781_);
lean_dec_ref(v_as_7778_);
return v_res_7784_;
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_RowOutput_output___lam__1(lean_object* v_tiles_7787_, lean_object* v_m_7788_, lean_object* v_n_7789_, lean_object* v_p_7790_, lean_object* v_A_7791_, lean_object* v_B_7792_, lean_object* v_b_7793_){
_start:
{
lean_object* v_batchTiles_7794_; lean_object* v___f_7795_; lean_object* v___x_7796_; size_t v_sz_7797_; size_t v___x_7798_; lean_object* v___x_7799_; lean_object* v___x_7800_; lean_object* v___x_7801_; lean_object* v___x_7802_; uint8_t v___x_7803_; 
v_batchTiles_7794_ = lean_array_fget_borrowed(v_tiles_7787_, v_b_7793_);
lean_inc(v_m_7788_);
lean_inc(v_batchTiles_7794_);
v___f_7795_ = lean_alloc_closure((void*)(lp_competition_Submission_RowOutput_output___lam__0___boxed), 8, 7);
lean_closure_set(v___f_7795_, 0, v_batchTiles_7794_);
lean_closure_set(v___f_7795_, 1, v_m_7788_);
lean_closure_set(v___f_7795_, 2, v_n_7789_);
lean_closure_set(v___f_7795_, 3, v_p_7790_);
lean_closure_set(v___f_7795_, 4, v_A_7791_);
lean_closure_set(v___f_7795_, 5, v_B_7792_);
lean_closure_set(v___f_7795_, 6, v_b_7793_);
v___x_7796_ = l_Array_ofFn___redArg(v_m_7788_, v___f_7795_);
v_sz_7797_ = lean_array_size(v___x_7796_);
v___x_7798_ = ((size_t)0ULL);
v___x_7799_ = lp_competition___private_Init_Data_Array_Basic_0__Array_mapMUnsafe_map___at___00Submission_RowOutput_output_spec__0(v_sz_7797_, v___x_7798_, v___x_7796_);
v___x_7800_ = lean_unsigned_to_nat(0u);
v___x_7801_ = ((lean_object*)(lp_competition_Submission_RowOutput_output___lam__1___closed__0));
v___x_7802_ = lean_array_get_size(v___x_7799_);
v___x_7803_ = lean_nat_dec_lt(v___x_7800_, v___x_7802_);
if (v___x_7803_ == 0)
{
lean_dec_ref(v___x_7799_);
return v___x_7801_;
}
else
{
uint8_t v___x_7804_; 
v___x_7804_ = lean_nat_dec_le(v___x_7802_, v___x_7802_);
if (v___x_7804_ == 0)
{
if (v___x_7803_ == 0)
{
lean_dec_ref(v___x_7799_);
return v___x_7801_;
}
else
{
size_t v___x_7805_; lean_object* v___x_7806_; 
v___x_7805_ = lean_usize_of_nat(v___x_7802_);
v___x_7806_ = lp_competition___private_Init_Data_Array_Basic_0__Array_foldlMUnsafe_fold___at___00Submission_RowOutput_output_spec__1(v___x_7799_, v___x_7798_, v___x_7805_, v___x_7801_);
lean_dec_ref(v___x_7799_);
return v___x_7806_;
}
}
else
{
size_t v___x_7807_; lean_object* v___x_7808_; 
v___x_7807_ = lean_usize_of_nat(v___x_7802_);
v___x_7808_ = lp_competition___private_Init_Data_Array_Basic_0__Array_foldlMUnsafe_fold___at___00Submission_RowOutput_output_spec__1(v___x_7799_, v___x_7798_, v___x_7807_, v___x_7801_);
lean_dec_ref(v___x_7799_);
return v___x_7808_;
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_RowOutput_output___lam__1___boxed(lean_object* v_tiles_7809_, lean_object* v_m_7810_, lean_object* v_n_7811_, lean_object* v_p_7812_, lean_object* v_A_7813_, lean_object* v_B_7814_, lean_object* v_b_7815_){
_start:
{
lean_object* v_res_7816_; 
v_res_7816_ = lp_competition_Submission_RowOutput_output___lam__1(v_tiles_7809_, v_m_7810_, v_n_7811_, v_p_7812_, v_A_7813_, v_B_7814_, v_b_7815_);
lean_dec_ref(v_tiles_7809_);
return v_res_7816_;
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_RowOutput_output(lean_object* v_batch_7817_, lean_object* v_m_7818_, lean_object* v_n_7819_, lean_object* v_p_7820_, lean_object* v_A_7821_, lean_object* v_B_7822_, lean_object* v_tiles_7823_){
_start:
{
lean_object* v___f_7824_; lean_object* v___x_7825_; size_t v_sz_7826_; size_t v___x_7827_; lean_object* v___x_7828_; lean_object* v___x_7829_; lean_object* v___x_7830_; lean_object* v___x_7831_; uint8_t v___x_7832_; 
v___f_7824_ = lean_alloc_closure((void*)(lp_competition_Submission_RowOutput_output___lam__1___boxed), 7, 6);
lean_closure_set(v___f_7824_, 0, v_tiles_7823_);
lean_closure_set(v___f_7824_, 1, v_m_7818_);
lean_closure_set(v___f_7824_, 2, v_n_7819_);
lean_closure_set(v___f_7824_, 3, v_p_7820_);
lean_closure_set(v___f_7824_, 4, v_A_7821_);
lean_closure_set(v___f_7824_, 5, v_B_7822_);
v___x_7825_ = l_Array_ofFn___redArg(v_batch_7817_, v___f_7824_);
v_sz_7826_ = lean_array_size(v___x_7825_);
v___x_7827_ = ((size_t)0ULL);
v___x_7828_ = lp_competition___private_Init_Data_Array_Basic_0__Array_mapMUnsafe_map___at___00Submission_RowOutput_output_spec__0(v_sz_7826_, v___x_7827_, v___x_7825_);
v___x_7829_ = lean_unsigned_to_nat(0u);
v___x_7830_ = ((lean_object*)(lp_competition_Submission_RowOutput_output___lam__1___closed__0));
v___x_7831_ = lean_array_get_size(v___x_7828_);
v___x_7832_ = lean_nat_dec_lt(v___x_7829_, v___x_7831_);
if (v___x_7832_ == 0)
{
lean_dec_ref(v___x_7828_);
return v___x_7830_;
}
else
{
uint8_t v___x_7833_; 
v___x_7833_ = lean_nat_dec_le(v___x_7831_, v___x_7831_);
if (v___x_7833_ == 0)
{
if (v___x_7832_ == 0)
{
lean_dec_ref(v___x_7828_);
return v___x_7830_;
}
else
{
size_t v___x_7834_; lean_object* v___x_7835_; 
v___x_7834_ = lean_usize_of_nat(v___x_7831_);
v___x_7835_ = lp_competition___private_Init_Data_Array_Basic_0__Array_foldlMUnsafe_fold___at___00Submission_RowOutput_output_spec__1(v___x_7828_, v___x_7827_, v___x_7834_, v___x_7830_);
lean_dec_ref(v___x_7828_);
return v___x_7835_;
}
}
else
{
size_t v___x_7836_; lean_object* v___x_7837_; 
v___x_7836_ = lean_usize_of_nat(v___x_7831_);
v___x_7837_ = lp_competition___private_Init_Data_Array_Basic_0__Array_foldlMUnsafe_fold___at___00Submission_RowOutput_output_spec__1(v___x_7828_, v___x_7827_, v___x_7836_, v___x_7830_);
lean_dec_ref(v___x_7828_);
return v___x_7837_;
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_RowOutput_core(lean_object* v_batch_7838_, lean_object* v_m_7839_, lean_object* v_n_7840_, lean_object* v_p_7841_, lean_object* v_A_7842_, lean_object* v_B_7843_){
_start:
{
size_t v_sz_7844_; size_t v___x_7845_; lean_object* v_nativeA_7846_; lean_object* v_packedB_7847_; lean_object* v_tiles_7848_; lean_object* v___x_7849_; 
v_sz_7844_ = lean_array_size(v_A_7842_);
v___x_7845_ = ((size_t)0ULL);
lean_inc_ref(v_A_7842_);
v_nativeA_7846_ = lp_competition___private_Init_Data_Array_Basic_0__Array_mapMUnsafe_map___at___00Submission_Packed10_core_spec__0(v_sz_7844_, v___x_7845_, v_A_7842_);
lean_inc_ref(v_B_7843_);
lean_inc_n(v_p_7841_, 2);
lean_inc_n(v_n_7840_, 2);
lean_inc_n(v_batch_7838_, 2);
v_packedB_7847_ = lp_competition_Submission_Packed10_packB(v_batch_7838_, v_n_7840_, v_p_7841_, v_B_7843_);
lean_inc(v_m_7839_);
v_tiles_7848_ = lp_competition_Submission_Packed10_tileResults(v_batch_7838_, v_m_7839_, v_n_7840_, v_p_7841_, v_nativeA_7846_, v_packedB_7847_);
v___x_7849_ = lp_competition_Submission_RowOutput_output(v_batch_7838_, v_m_7839_, v_n_7840_, v_p_7841_, v_A_7842_, v_B_7843_, v_tiles_7848_);
return v___x_7849_;
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_bmmRows(lean_object* v_batch_7850_, lean_object* v_m_7851_, lean_object* v_n_7852_, lean_object* v_p_7853_, lean_object* v_A_7854_, lean_object* v_B_7855_){
_start:
{
lean_object* v___x_7856_; lean_object* v___x_7857_; lean_object* v___x_7858_; uint8_t v___x_7859_; 
v___x_7856_ = lean_nat_mul(v_batch_7850_, v_m_7851_);
v___x_7857_ = lean_nat_mul(v___x_7856_, v_p_7853_);
lean_dec(v___x_7856_);
v___x_7858_ = lean_unsigned_to_nat(0u);
v___x_7859_ = lean_nat_dec_eq(v___x_7857_, v___x_7858_);
lean_dec(v___x_7857_);
if (v___x_7859_ == 0)
{
uint8_t v___x_7860_; 
v___x_7860_ = lean_nat_dec_eq(v_n_7852_, v___x_7858_);
if (v___x_7860_ == 0)
{
lean_object* v___x_7861_; 
v___x_7861_ = lp_competition_Submission_RowOutput_core(v_batch_7850_, v_m_7851_, v_n_7852_, v_p_7853_, v_A_7854_, v_B_7855_);
return v___x_7861_;
}
else
{
lean_object* v___x_7862_; 
v___x_7862_ = lp_competition_Submission_referenceBmm(v_batch_7850_, v_m_7851_, v_n_7852_, v_p_7853_, v_A_7854_, v_B_7855_);
lean_dec(v_batch_7850_);
return v___x_7862_;
}
}
else
{
lean_object* v___x_7863_; 
v___x_7863_ = lp_competition_Submission_referenceBmm(v_batch_7850_, v_m_7851_, v_n_7852_, v_p_7853_, v_A_7854_, v_B_7855_);
lean_dec(v_batch_7850_);
return v___x_7863_;
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_RowStream_core___lam__0(lean_object* v_r_7864_){
_start:
{
lean_inc(v_r_7864_);
return v_r_7864_;
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_RowStream_core___lam__0___boxed(lean_object* v_r_7865_){
_start:
{
lean_object* v_res_7866_; 
v_res_7866_ = lp_competition_Submission_RowStream_core___lam__0(v_r_7865_);
lean_dec(v_r_7865_);
return v_res_7866_;
}
}
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_foldlMUnsafe_fold___at___00Submission_RowStream_core_spec__0___redArg___lam__0(lean_object* v_b_7867_, lean_object* v_m_7868_, lean_object* v_i_7869_, lean_object* v_n_7870_, lean_object* v_packedB_7871_, lean_object* v_nativeA_7872_, lean_object* v_g_7873_){
_start:
{
lean_object* v___x_7874_; lean_object* v___x_7875_; lean_object* v___x_7876_; lean_object* v___x_7877_; lean_object* v___x_7878_; lean_object* v___x_7883_; uint8_t v___x_7884_; 
v___x_7874_ = lean_nat_mul(v_b_7867_, v_m_7868_);
v___x_7875_ = lean_nat_add(v___x_7874_, v_i_7869_);
lean_dec(v___x_7874_);
v___x_7876_ = lean_nat_mul(v___x_7875_, v_n_7870_);
lean_dec(v___x_7875_);
v___x_7877_ = lean_array_fget_borrowed(v_packedB_7871_, v_b_7867_);
v___x_7878_ = lean_array_fget_borrowed(v___x_7877_, v_g_7873_);
v___x_7883_ = lean_obj_once(&lp_competition_Submission_Packed10Index_runDot___closed__0, &lp_competition_Submission_Packed10Index_runDot___closed__0_once, _init_lp_competition_Submission_Packed10Index_runDot___closed__0);
v___x_7884_ = lean_nat_dec_lt(v_n_7870_, v___x_7883_);
if (v___x_7884_ == 0)
{
goto v___jp_7879_;
}
else
{
uint8_t v___x_7885_; 
v___x_7885_ = lean_nat_dec_lt(v___x_7876_, v___x_7883_);
if (v___x_7885_ == 0)
{
goto v___jp_7879_;
}
else
{
lean_object* v___x_7886_; lean_object* v___x_7887_; lean_object* v___x_7888_; lean_object* v___x_7889_; uint8_t v___x_7890_; 
v___x_7886_ = lean_unsigned_to_nat(1u);
v___x_7887_ = lean_nat_sub(v_n_7870_, v___x_7886_);
v___x_7888_ = lean_nat_add(v___x_7876_, v___x_7887_);
lean_dec(v___x_7887_);
v___x_7889_ = lean_array_get_size(v_nativeA_7872_);
v___x_7890_ = lean_nat_dec_lt(v___x_7888_, v___x_7889_);
lean_dec(v___x_7888_);
if (v___x_7890_ == 0)
{
goto v___jp_7879_;
}
else
{
uint8_t v___x_7891_; 
v___x_7891_ = lean_nat_dec_lt(v___x_7889_, v___x_7883_);
if (v___x_7891_ == 0)
{
goto v___jp_7879_;
}
else
{
size_t v___x_7892_; size_t v___x_7893_; size_t v___x_7894_; float v___x_7895_; lean_object* v___x_7896_; 
v___x_7892_ = lean_usize_of_nat(v_n_7870_);
v___x_7893_ = lean_usize_of_nat(v___x_7876_);
lean_dec(v___x_7876_);
v___x_7894_ = ((size_t)0ULL);
v___x_7895_ = lean_float32_once(&lp_competition_Submission_NativeFinal_dot___closed__0, &lp_competition_Submission_NativeFinal_dot___closed__0_once, _init_lp_competition_Submission_NativeFinal_dot___closed__0);
v___x_7896_ = lp_competition_Submission_Packed10Index_loop___redArg(v___x_7892_, v___x_7893_, v_nativeA_7872_, v___x_7878_, v___x_7894_, v___x_7895_, v___x_7895_, v___x_7895_, v___x_7895_, v___x_7895_, v___x_7895_, v___x_7895_, v___x_7895_, v___x_7895_, v___x_7895_);
return v___x_7896_;
}
}
}
}
v___jp_7879_:
{
lean_object* v___x_7880_; float v___x_7881_; lean_object* v___x_7882_; 
v___x_7880_ = lean_unsigned_to_nat(0u);
v___x_7881_ = lean_float32_once(&lp_competition_Submission_NativeFinal_dot___closed__0, &lp_competition_Submission_NativeFinal_dot___closed__0_once, _init_lp_competition_Submission_NativeFinal_dot___closed__0);
v___x_7882_ = lp_competition_Submission_Packed10_dot10(v_n_7870_, v___x_7876_, v_nativeA_7872_, v___x_7878_, v___x_7880_, v___x_7881_, v___x_7881_, v___x_7881_, v___x_7881_, v___x_7881_, v___x_7881_, v___x_7881_, v___x_7881_, v___x_7881_, v___x_7881_);
lean_dec(v___x_7876_);
return v___x_7882_;
}
}
}
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_foldlMUnsafe_fold___at___00Submission_RowStream_core_spec__0___redArg___lam__0___boxed(lean_object* v_b_7897_, lean_object* v_m_7898_, lean_object* v_i_7899_, lean_object* v_n_7900_, lean_object* v_packedB_7901_, lean_object* v_nativeA_7902_, lean_object* v_g_7903_){
_start:
{
lean_object* v_res_7904_; 
v_res_7904_ = lp_competition___private_Init_Data_Array_Basic_0__Array_foldlMUnsafe_fold___at___00Submission_RowStream_core_spec__0___redArg___lam__0(v_b_7897_, v_m_7898_, v_i_7899_, v_n_7900_, v_packedB_7901_, v_nativeA_7902_, v_g_7903_);
lean_dec(v_g_7903_);
lean_dec_ref(v_nativeA_7902_);
lean_dec_ref(v_packedB_7901_);
lean_dec(v_n_7900_);
lean_dec(v_i_7899_);
lean_dec(v_m_7898_);
lean_dec(v_b_7897_);
return v_res_7904_;
}
}
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_foldlMUnsafe_fold___at___00Submission_RowStream_core_spec__0___redArg(lean_object* v_m_7905_, lean_object* v_n_7906_, lean_object* v_packedB_7907_, lean_object* v_nativeA_7908_, lean_object* v_p_7909_, lean_object* v_A_7910_, lean_object* v_B_7911_, lean_object* v_as_7912_, size_t v_i_7913_, size_t v_stop_7914_, lean_object* v_b_7915_){
_start:
{
uint8_t v___x_7916_; 
v___x_7916_ = lean_usize_dec_eq(v_i_7913_, v_stop_7914_);
if (v___x_7916_ == 0)
{
lean_object* v___x_7917_; lean_object* v_b_7918_; lean_object* v_i_7919_; lean_object* v___f_7920_; lean_object* v___x_7921_; lean_object* v___x_7922_; lean_object* v___x_7923_; lean_object* v___x_7924_; lean_object* v_rowTiles_7925_; lean_object* v___x_7926_; lean_object* v___x_7927_; size_t v___x_7928_; size_t v___x_7929_; 
v___x_7917_ = lean_array_uget_borrowed(v_as_7912_, v_i_7913_);
v_b_7918_ = lean_nat_div(v___x_7917_, v_m_7905_);
v_i_7919_ = lean_nat_mod(v___x_7917_, v_m_7905_);
lean_inc_ref(v_nativeA_7908_);
lean_inc_ref(v_packedB_7907_);
lean_inc_n(v_n_7906_, 2);
lean_inc(v_i_7919_);
lean_inc(v_m_7905_);
lean_inc(v_b_7918_);
v___f_7920_ = lean_alloc_closure((void*)(lp_competition___private_Init_Data_Array_Basic_0__Array_foldlMUnsafe_fold___at___00Submission_RowStream_core_spec__0___redArg___lam__0___boxed), 7, 6);
lean_closure_set(v___f_7920_, 0, v_b_7918_);
lean_closure_set(v___f_7920_, 1, v_m_7905_);
lean_closure_set(v___f_7920_, 2, v_i_7919_);
lean_closure_set(v___f_7920_, 3, v_n_7906_);
lean_closure_set(v___f_7920_, 4, v_packedB_7907_);
lean_closure_set(v___f_7920_, 5, v_nativeA_7908_);
v___x_7921_ = lean_unsigned_to_nat(9u);
v___x_7922_ = lean_nat_add(v_p_7909_, v___x_7921_);
v___x_7923_ = lean_unsigned_to_nat(10u);
v___x_7924_ = lean_nat_div(v___x_7922_, v___x_7923_);
lean_dec(v___x_7922_);
v_rowTiles_7925_ = l_Array_ofFn___redArg(v___x_7924_, v___f_7920_);
lean_inc_ref(v_B_7911_);
lean_inc_ref(v_A_7910_);
lean_inc(v_p_7909_);
v___x_7926_ = lp_competition_Submission_RowOutput_row___redArg(v_m_7905_, v_n_7906_, v_p_7909_, v_A_7910_, v_B_7911_, v_b_7918_, v_i_7919_, v_rowTiles_7925_);
lean_dec(v_i_7919_);
lean_dec(v_b_7918_);
v___x_7927_ = l_Array_append___redArg(v_b_7915_, v___x_7926_);
lean_dec_ref(v___x_7926_);
v___x_7928_ = ((size_t)1ULL);
v___x_7929_ = lean_usize_add(v_i_7913_, v___x_7928_);
v_i_7913_ = v___x_7929_;
v_b_7915_ = v___x_7927_;
goto _start;
}
else
{
lean_dec_ref(v_B_7911_);
lean_dec_ref(v_A_7910_);
lean_dec(v_p_7909_);
lean_dec_ref(v_nativeA_7908_);
lean_dec_ref(v_packedB_7907_);
lean_dec(v_n_7906_);
lean_dec(v_m_7905_);
return v_b_7915_;
}
}
}
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_foldlMUnsafe_fold___at___00Submission_RowStream_core_spec__0___redArg___boxed(lean_object* v_m_7931_, lean_object* v_n_7932_, lean_object* v_packedB_7933_, lean_object* v_nativeA_7934_, lean_object* v_p_7935_, lean_object* v_A_7936_, lean_object* v_B_7937_, lean_object* v_as_7938_, lean_object* v_i_7939_, lean_object* v_stop_7940_, lean_object* v_b_7941_){
_start:
{
size_t v_i_boxed_7942_; size_t v_stop_boxed_7943_; lean_object* v_res_7944_; 
v_i_boxed_7942_ = lean_unbox_usize(v_i_7939_);
lean_dec(v_i_7939_);
v_stop_boxed_7943_ = lean_unbox_usize(v_stop_7940_);
lean_dec(v_stop_7940_);
v_res_7944_ = lp_competition___private_Init_Data_Array_Basic_0__Array_foldlMUnsafe_fold___at___00Submission_RowStream_core_spec__0___redArg(v_m_7931_, v_n_7932_, v_packedB_7933_, v_nativeA_7934_, v_p_7935_, v_A_7936_, v_B_7937_, v_as_7938_, v_i_boxed_7942_, v_stop_boxed_7943_, v_b_7941_);
lean_dec_ref(v_as_7938_);
return v_res_7944_;
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_RowStream_core(lean_object* v_batch_7946_, lean_object* v_m_7947_, lean_object* v_n_7948_, lean_object* v_p_7949_, lean_object* v_A_7950_, lean_object* v_B_7951_){
_start:
{
lean_object* v___f_7952_; lean_object* v___x_7953_; lean_object* v___x_7954_; lean_object* v___x_7955_; lean_object* v___x_7956_; lean_object* v___x_7957_; uint8_t v___x_7958_; 
v___f_7952_ = ((lean_object*)(lp_competition_Submission_RowStream_core___closed__0));
v___x_7953_ = lean_nat_mul(v_batch_7946_, v_m_7947_);
v___x_7954_ = l_Array_ofFn___redArg(v___x_7953_, v___f_7952_);
v___x_7955_ = lean_unsigned_to_nat(0u);
v___x_7956_ = ((lean_object*)(lp_competition_Submission_RowOutput_output___lam__1___closed__0));
v___x_7957_ = lean_array_get_size(v___x_7954_);
v___x_7958_ = lean_nat_dec_lt(v___x_7955_, v___x_7957_);
if (v___x_7958_ == 0)
{
lean_dec_ref(v___x_7954_);
lean_dec_ref(v_B_7951_);
lean_dec_ref(v_A_7950_);
lean_dec(v_p_7949_);
lean_dec(v_n_7948_);
lean_dec(v_m_7947_);
lean_dec(v_batch_7946_);
return v___x_7956_;
}
else
{
size_t v_sz_7959_; size_t v___x_7960_; lean_object* v_nativeA_7961_; lean_object* v_packedB_7962_; uint8_t v___x_7963_; 
v_sz_7959_ = lean_array_size(v_A_7950_);
v___x_7960_ = ((size_t)0ULL);
lean_inc_ref(v_A_7950_);
v_nativeA_7961_ = lp_competition___private_Init_Data_Array_Basic_0__Array_mapMUnsafe_map___at___00Submission_Packed10_core_spec__0(v_sz_7959_, v___x_7960_, v_A_7950_);
lean_inc_ref(v_B_7951_);
lean_inc(v_p_7949_);
lean_inc(v_n_7948_);
v_packedB_7962_ = lp_competition_Submission_Packed10_packB(v_batch_7946_, v_n_7948_, v_p_7949_, v_B_7951_);
v___x_7963_ = lean_nat_dec_le(v___x_7957_, v___x_7957_);
if (v___x_7963_ == 0)
{
if (v___x_7958_ == 0)
{
lean_dec_ref(v_packedB_7962_);
lean_dec_ref(v_nativeA_7961_);
lean_dec_ref(v___x_7954_);
lean_dec_ref(v_B_7951_);
lean_dec_ref(v_A_7950_);
lean_dec(v_p_7949_);
lean_dec(v_n_7948_);
lean_dec(v_m_7947_);
return v___x_7956_;
}
else
{
size_t v___x_7964_; lean_object* v___x_7965_; 
v___x_7964_ = lean_usize_of_nat(v___x_7957_);
v___x_7965_ = lp_competition___private_Init_Data_Array_Basic_0__Array_foldlMUnsafe_fold___at___00Submission_RowStream_core_spec__0___redArg(v_m_7947_, v_n_7948_, v_packedB_7962_, v_nativeA_7961_, v_p_7949_, v_A_7950_, v_B_7951_, v___x_7954_, v___x_7960_, v___x_7964_, v___x_7956_);
lean_dec_ref(v___x_7954_);
return v___x_7965_;
}
}
else
{
size_t v___x_7966_; lean_object* v___x_7967_; 
v___x_7966_ = lean_usize_of_nat(v___x_7957_);
v___x_7967_ = lp_competition___private_Init_Data_Array_Basic_0__Array_foldlMUnsafe_fold___at___00Submission_RowStream_core_spec__0___redArg(v_m_7947_, v_n_7948_, v_packedB_7962_, v_nativeA_7961_, v_p_7949_, v_A_7950_, v_B_7951_, v___x_7954_, v___x_7960_, v___x_7966_, v___x_7956_);
lean_dec_ref(v___x_7954_);
return v___x_7967_;
}
}
}
}
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_foldlMUnsafe_fold___at___00Submission_RowStream_core_spec__0(lean_object* v_m_7968_, lean_object* v_batch_7969_, lean_object* v_n_7970_, lean_object* v_packedB_7971_, lean_object* v_nativeA_7972_, lean_object* v_p_7973_, lean_object* v_A_7974_, lean_object* v_B_7975_, lean_object* v_as_7976_, size_t v_i_7977_, size_t v_stop_7978_, lean_object* v_b_7979_){
_start:
{
lean_object* v___x_7980_; 
v___x_7980_ = lp_competition___private_Init_Data_Array_Basic_0__Array_foldlMUnsafe_fold___at___00Submission_RowStream_core_spec__0___redArg(v_m_7968_, v_n_7970_, v_packedB_7971_, v_nativeA_7972_, v_p_7973_, v_A_7974_, v_B_7975_, v_as_7976_, v_i_7977_, v_stop_7978_, v_b_7979_);
return v___x_7980_;
}
}
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_foldlMUnsafe_fold___at___00Submission_RowStream_core_spec__0___boxed(lean_object* v_m_7981_, lean_object* v_batch_7982_, lean_object* v_n_7983_, lean_object* v_packedB_7984_, lean_object* v_nativeA_7985_, lean_object* v_p_7986_, lean_object* v_A_7987_, lean_object* v_B_7988_, lean_object* v_as_7989_, lean_object* v_i_7990_, lean_object* v_stop_7991_, lean_object* v_b_7992_){
_start:
{
size_t v_i_boxed_7993_; size_t v_stop_boxed_7994_; lean_object* v_res_7995_; 
v_i_boxed_7993_ = lean_unbox_usize(v_i_7990_);
lean_dec(v_i_7990_);
v_stop_boxed_7994_ = lean_unbox_usize(v_stop_7991_);
lean_dec(v_stop_7991_);
v_res_7995_ = lp_competition___private_Init_Data_Array_Basic_0__Array_foldlMUnsafe_fold___at___00Submission_RowStream_core_spec__0(v_m_7981_, v_batch_7982_, v_n_7983_, v_packedB_7984_, v_nativeA_7985_, v_p_7986_, v_A_7987_, v_B_7988_, v_as_7989_, v_i_boxed_7993_, v_stop_boxed_7994_, v_b_7992_);
lean_dec_ref(v_as_7989_);
lean_dec(v_batch_7982_);
return v_res_7995_;
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_bmm(lean_object* v_batch_7996_, lean_object* v_m_7997_, lean_object* v_n_7998_, lean_object* v_p_7999_, lean_object* v_A_8000_, lean_object* v_B_8001_){
_start:
{
lean_object* v___x_8002_; lean_object* v___x_8003_; lean_object* v___x_8004_; uint8_t v___x_8005_; 
v___x_8002_ = lean_nat_mul(v_batch_7996_, v_m_7997_);
v___x_8003_ = lean_nat_mul(v___x_8002_, v_p_7999_);
lean_dec(v___x_8002_);
v___x_8004_ = lean_unsigned_to_nat(0u);
v___x_8005_ = lean_nat_dec_eq(v___x_8003_, v___x_8004_);
lean_dec(v___x_8003_);
if (v___x_8005_ == 0)
{
uint8_t v___x_8006_; 
v___x_8006_ = lean_nat_dec_eq(v_n_7998_, v___x_8004_);
if (v___x_8006_ == 0)
{
lean_object* v___x_8007_; 
v___x_8007_ = lp_competition_Submission_RowStream_core(v_batch_7996_, v_m_7997_, v_n_7998_, v_p_7999_, v_A_8000_, v_B_8001_);
return v___x_8007_;
}
else
{
lean_object* v___x_8008_; 
v___x_8008_ = lp_competition_Submission_referenceBmm(v_batch_7996_, v_m_7997_, v_n_7998_, v_p_7999_, v_A_8000_, v_B_8001_);
lean_dec(v_batch_7996_);
return v___x_8008_;
}
}
else
{
lean_object* v___x_8009_; 
v___x_8009_ = lp_competition_Submission_referenceBmm(v_batch_7996_, v_m_7997_, v_n_7998_, v_p_7999_, v_A_8000_, v_B_8001_);
lean_dec(v_batch_7996_);
return v___x_8009_;
}
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
lp_competition_R2W01b_scaleTable = _init_lp_competition_R2W01b_scaleTable();
lean_mark_persistent(lp_competition_R2W01b_scaleTable);
lp_competition_Submission_TunedAdd_Plan = _init_lp_competition_Submission_TunedAdd_Plan();
lp_competition_Submission_FastMul_Plan = _init_lp_competition_Submission_FastMul_Plan();
lp_competition_Submission_Packed10_zero32 = _init_lp_competition_Submission_Packed10_zero32();
lp_competition_Submission_Packed10_zero10 = _init_lp_competition_Submission_Packed10_zero10();
lean_mark_persistent(lp_competition_Submission_Packed10_zero10);
return lean_io_result_mk_ok(lean_box(0));
}
#ifdef __cplusplus
}
#endif
