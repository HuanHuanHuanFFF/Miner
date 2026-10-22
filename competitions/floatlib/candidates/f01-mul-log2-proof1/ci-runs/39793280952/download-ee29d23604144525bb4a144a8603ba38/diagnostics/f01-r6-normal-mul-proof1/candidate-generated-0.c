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
uint8_t lean_float32_isfinite(float);
lean_object* l_BitVec_ofNat(lean_object*, lean_object*);
uint32_t lean_uint32_of_nat(lean_object*);
uint32_t lean_float32_to_bits(float);
uint32_t lean_uint32_land(uint32_t, uint32_t);
uint32_t lean_uint32_lor(uint32_t, uint32_t);
float lean_uint32_to_float32(uint32_t);
uint32_t lean_uint32_shift_left(uint32_t, uint32_t);
uint32_t lean_uint32_sub(uint32_t, uint32_t);
uint8_t lean_uint32_dec_le(uint32_t, uint32_t);
uint32_t lean_uint32_shift_right(uint32_t, uint32_t);
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
uint8_t lean_uint32_dec_eq(uint32_t, uint32_t);
uint64_t lean_uint64_lor(uint64_t, uint64_t);
lean_object* lp_floatlib_FloatLib_Floats_Formats_BinaryInterchange_Model_AddBackend_word___at___00FloatLib_Floats_Formats_BinaryInterchange_Configured_Plan_softwareAdd32Certified_spec__1(lean_object*, lean_object*);
uint64_t lean_uint64_mul(uint64_t, uint64_t);
lean_object* lp_floatlib_FloatLib_Floats_Formats_BinaryInterchange_Model_MulBackend_word___at___00FloatLib_Floats_Formats_BinaryInterchange_Configured_Plan_softwareMul32Certified_spec__1(lean_object*, lean_object*);
uint32_t lean_uint32_add(uint32_t, uint32_t);
lean_object* lp_competition_Competition_bmmDecodeC(lean_object*, lean_object*, lean_object*);
lean_object* lean_mk_empty_array_with_capacity(lean_object*);
uint8_t lean_nat_dec_le(lean_object*, lean_object*);
uint8_t lean_usize_dec_eq(size_t, size_t);
lean_object* l_Array_append___redArg(lean_object*, lean_object*);
lean_object* lp_floatlib_FloatLib_Floats_Formats_BinaryInterchange_Model_MulBackend_word(lean_object*, lean_object*, lean_object*);
lean_object* lean_nat_shiftr(lean_object*, lean_object*);
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
LEAN_EXPORT uint64_t lp_competition_Submission_R6NormalMul_leading(uint64_t);
LEAN_EXPORT lean_object* lp_competition_Submission_R6NormalMul_leading___boxed(lean_object*);
LEAN_EXPORT uint32_t lp_competition_Submission_R6NormalMul_roundP(uint8_t, uint64_t, uint64_t);
LEAN_EXPORT lean_object* lp_competition_Submission_R6NormalMul_roundP___boxed(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT uint32_t lp_competition_Submission_R6NormalMul_core(uint32_t, uint32_t);
LEAN_EXPORT lean_object* lp_competition_Submission_R6NormalMul_core___boxed(lean_object*, lean_object*);
LEAN_EXPORT uint32_t lp_competition_Submission_R6NormalMul_mul(uint32_t, uint32_t);
LEAN_EXPORT lean_object* lp_competition_Submission_R6NormalMul_mul___boxed(lean_object*, lean_object*);
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
LEAN_EXPORT uint32_t lp_competition_R2W01b_magnitude(uint32_t v_u_1_){
_start:
{
uint32_t v___x_2_; uint32_t v___x_3_; 
v___x_2_ = 2147483647;
v___x_3_ = lean_uint32_land(v_u_1_, v___x_2_);
return v___x_3_;
}
}
LEAN_EXPORT lean_object* lp_competition_R2W01b_magnitude___boxed(lean_object* v_u_4_){
_start:
{
uint32_t v_u_boxed_5_; uint32_t v_res_6_; lean_object* v_r_7_; 
v_u_boxed_5_ = lean_unbox_uint32(v_u_4_);
lean_dec(v_u_4_);
v_res_6_ = lp_competition_R2W01b_magnitude(v_u_boxed_5_);
v_r_7_ = lean_box_uint32(v_res_6_);
return v_r_7_;
}
}
LEAN_EXPORT uint8_t lp_competition_R2W01b_fastOK(uint32_t v_u_8_){
_start:
{
uint32_t v___x_9_; uint32_t v_a_10_; uint32_t v___x_11_; uint32_t v___x_12_; uint32_t v___x_13_; uint8_t v___x_14_; 
v___x_9_ = 2147483647;
v_a_10_ = lean_uint32_land(v_u_8_, v___x_9_);
v___x_11_ = 201326591;
v___x_12_ = 1;
v___x_13_ = lean_uint32_sub(v_a_10_, v___x_12_);
v___x_14_ = lean_uint32_dec_le(v___x_11_, v___x_13_);
if (v___x_14_ == 0)
{
return v___x_14_;
}
else
{
uint32_t v___x_15_; uint8_t v___x_16_; 
v___x_15_ = 2139095040;
v___x_16_ = lean_uint32_dec_lt(v_a_10_, v___x_15_);
return v___x_16_;
}
}
}
LEAN_EXPORT lean_object* lp_competition_R2W01b_fastOK___boxed(lean_object* v_u_17_){
_start:
{
uint32_t v_u_boxed_18_; uint8_t v_res_19_; lean_object* v_r_20_; 
v_u_boxed_18_ = lean_unbox_uint32(v_u_17_);
lean_dec(v_u_17_);
v_res_19_ = lp_competition_R2W01b_fastOK(v_u_boxed_18_);
v_r_20_ = lean_box(v_res_19_);
return v_r_20_;
}
}
LEAN_EXPORT uint32_t lp_competition_R2W01b_tableIndex(uint32_t v_u_21_){
_start:
{
uint32_t v___x_22_; uint32_t v___x_23_; 
v___x_22_ = 23;
v___x_23_ = lean_uint32_shift_right(v_u_21_, v___x_22_);
return v___x_23_;
}
}
LEAN_EXPORT lean_object* lp_competition_R2W01b_tableIndex___boxed(lean_object* v_u_24_){
_start:
{
uint32_t v_u_boxed_25_; uint32_t v_res_26_; lean_object* v_r_27_; 
v_u_boxed_25_ = lean_unbox_uint32(v_u_24_);
lean_dec(v_u_24_);
v_res_26_ = lp_competition_R2W01b_tableIndex(v_u_boxed_25_);
v_r_27_ = lean_box_uint32(v_res_26_);
return v_r_27_;
}
}
LEAN_EXPORT uint32_t lp_competition_R2W01b_mantissa(uint32_t v_u_28_){
_start:
{
uint32_t v___x_29_; uint32_t v___x_30_; uint32_t v___x_31_; uint32_t v___x_32_; 
v___x_29_ = 8388607;
v___x_30_ = lean_uint32_land(v_u_28_, v___x_29_);
v___x_31_ = 8388608;
v___x_32_ = lean_uint32_lor(v___x_30_, v___x_31_);
return v___x_32_;
}
}
LEAN_EXPORT lean_object* lp_competition_R2W01b_mantissa___boxed(lean_object* v_u_33_){
_start:
{
uint32_t v_u_boxed_34_; uint32_t v_res_35_; lean_object* v_r_36_; 
v_u_boxed_34_ = lean_unbox_uint32(v_u_33_);
lean_dec(v_u_33_);
v_res_35_ = lp_competition_R2W01b_mantissa(v_u_boxed_34_);
v_r_36_ = lean_box_uint32(v_res_35_);
return v_r_36_;
}
}
LEAN_EXPORT uint32_t lp_competition_R2W01b_scaleBits(uint32_t v_j_37_){
_start:
{
uint32_t v___x_38_; uint32_t v_e_39_; uint32_t v___x_40_; uint32_t v___x_41_; uint32_t v___x_42_; uint32_t v_s_43_; uint8_t v___y_45_; uint32_t v___x_49_; uint8_t v___x_50_; 
v___x_38_ = 255;
v_e_39_ = lean_uint32_land(v_j_37_, v___x_38_);
v___x_40_ = 256;
v___x_41_ = lean_uint32_land(v_j_37_, v___x_40_);
v___x_42_ = 23;
v_s_43_ = lean_uint32_shift_left(v___x_41_, v___x_42_);
v___x_49_ = 24;
v___x_50_ = lean_uint32_dec_le(v___x_49_, v_e_39_);
if (v___x_50_ == 0)
{
v___y_45_ = v___x_50_;
goto v___jp_44_;
}
else
{
uint32_t v___x_51_; uint8_t v___x_52_; 
v___x_51_ = 254;
v___x_52_ = lean_uint32_dec_le(v_e_39_, v___x_51_);
v___y_45_ = v___x_52_;
goto v___jp_44_;
}
v___jp_44_:
{
if (v___y_45_ == 0)
{
return v_s_43_;
}
else
{
uint32_t v___x_46_; uint32_t v___x_47_; uint32_t v___x_48_; 
v___x_46_ = lean_uint32_sub(v_e_39_, v___x_42_);
v___x_47_ = lean_uint32_shift_left(v___x_46_, v___x_42_);
v___x_48_ = lean_uint32_lor(v_s_43_, v___x_47_);
return v___x_48_;
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_R2W01b_scaleBits___boxed(lean_object* v_j_53_){
_start:
{
uint32_t v_j_boxed_54_; uint32_t v_res_55_; lean_object* v_r_56_; 
v_j_boxed_54_ = lean_unbox_uint32(v_j_53_);
lean_dec(v_j_53_);
v_res_55_ = lp_competition_R2W01b_scaleBits(v_j_boxed_54_);
v_r_56_ = lean_box_uint32(v_res_55_);
return v_r_56_;
}
}
LEAN_EXPORT float lp_competition_R2W01b_scaleTable___lam__0(lean_object* v_j_57_){
_start:
{
uint32_t v___x_58_; uint32_t v___x_59_; uint32_t v_e_60_; uint32_t v___x_61_; uint32_t v___x_62_; uint32_t v___x_63_; uint32_t v_s_64_; uint8_t v___y_66_; uint32_t v___x_72_; uint8_t v___x_73_; 
v___x_58_ = lean_uint32_of_nat(v_j_57_);
v___x_59_ = 255;
v_e_60_ = lean_uint32_land(v___x_58_, v___x_59_);
v___x_61_ = 256;
v___x_62_ = lean_uint32_land(v___x_58_, v___x_61_);
v___x_63_ = 23;
v_s_64_ = lean_uint32_shift_left(v___x_62_, v___x_63_);
v___x_72_ = 24;
v___x_73_ = lean_uint32_dec_le(v___x_72_, v_e_60_);
if (v___x_73_ == 0)
{
v___y_66_ = v___x_73_;
goto v___jp_65_;
}
else
{
uint32_t v___x_74_; uint8_t v___x_75_; 
v___x_74_ = 254;
v___x_75_ = lean_uint32_dec_le(v_e_60_, v___x_74_);
v___y_66_ = v___x_75_;
goto v___jp_65_;
}
v___jp_65_:
{
if (v___y_66_ == 0)
{
float v___x_67_; 
v___x_67_ = lean_float32_of_bits(v_s_64_);
return v___x_67_;
}
else
{
uint32_t v___x_68_; uint32_t v___x_69_; uint32_t v___x_70_; float v___x_71_; 
v___x_68_ = lean_uint32_sub(v_e_60_, v___x_63_);
v___x_69_ = lean_uint32_shift_left(v___x_68_, v___x_63_);
v___x_70_ = lean_uint32_lor(v_s_64_, v___x_69_);
v___x_71_ = lean_float32_of_bits(v___x_70_);
return v___x_71_;
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_R2W01b_scaleTable___lam__0___boxed(lean_object* v_j_76_){
_start:
{
float v_res_77_; lean_object* v_r_78_; 
v_res_77_ = lp_competition_R2W01b_scaleTable___lam__0(v_j_76_);
lean_dec(v_j_76_);
v_r_78_ = lean_box_float32(v_res_77_);
return v_r_78_;
}
}
static lean_object* _init_lp_competition_R2W01b_scaleTable___closed__1(void){
_start:
{
lean_object* v___f_80_; lean_object* v___x_81_; lean_object* v___x_82_; 
v___f_80_ = ((lean_object*)(lp_competition_R2W01b_scaleTable___closed__0));
v___x_81_ = lean_unsigned_to_nat(512u);
v___x_82_ = l_Array_ofFn___redArg(v___x_81_, v___f_80_);
return v___x_82_;
}
}
static lean_object* _init_lp_competition_R2W01b_scaleTable(void){
_start:
{
lean_object* v___x_83_; 
v___x_83_ = lean_obj_once(&lp_competition_R2W01b_scaleTable___closed__1, &lp_competition_R2W01b_scaleTable___closed__1_once, _init_lp_competition_R2W01b_scaleTable___closed__1);
return v___x_83_;
}
}
LEAN_EXPORT float lp_competition_R2W01b_scaleAt(uint32_t v_u_84_){
_start:
{
lean_object* v___x_85_; uint32_t v___x_86_; uint32_t v___x_87_; lean_object* v___x_88_; lean_object* v___x_89_; float v___x_90_; 
v___x_85_ = lp_competition_R2W01b_scaleTable;
v___x_86_ = 23;
v___x_87_ = lean_uint32_shift_right(v_u_84_, v___x_86_);
v___x_88_ = lean_uint32_to_nat(v___x_87_);
v___x_89_ = lean_array_fget_borrowed(v___x_85_, v___x_88_);
lean_dec(v___x_88_);
v___x_90_ = lean_unbox_float32(v___x_89_);
return v___x_90_;
}
}
LEAN_EXPORT lean_object* lp_competition_R2W01b_scaleAt___boxed(lean_object* v_u_91_){
_start:
{
uint32_t v_u_boxed_92_; float v_res_93_; lean_object* v_r_94_; 
v_u_boxed_92_ = lean_unbox_uint32(v_u_91_);
lean_dec(v_u_91_);
v_res_93_ = lp_competition_R2W01b_scaleAt(v_u_boxed_92_);
v_r_94_ = lean_box_float32(v_res_93_);
return v_r_94_;
}
}
LEAN_EXPORT float lp_competition_R2W01b_tableProduct(uint32_t v_u_95_){
_start:
{
uint32_t v___x_96_; uint32_t v___x_97_; uint32_t v___x_98_; uint32_t v___x_99_; float v___x_100_; lean_object* v___x_101_; uint32_t v___x_102_; uint32_t v___x_103_; lean_object* v___x_104_; lean_object* v___x_105_; float v___x_106_; float v___x_107_; 
v___x_96_ = 8388607;
v___x_97_ = lean_uint32_land(v_u_95_, v___x_96_);
v___x_98_ = 8388608;
v___x_99_ = lean_uint32_lor(v___x_97_, v___x_98_);
v___x_100_ = lean_uint32_to_float32(v___x_99_);
v___x_101_ = lp_competition_R2W01b_scaleTable;
v___x_102_ = 23;
v___x_103_ = lean_uint32_shift_right(v_u_95_, v___x_102_);
v___x_104_ = lean_uint32_to_nat(v___x_103_);
v___x_105_ = lean_array_fget_borrowed(v___x_101_, v___x_104_);
lean_dec(v___x_104_);
v___x_106_ = lean_unbox_float32(v___x_105_);
v___x_107_ = lean_float32_mul(v___x_100_, v___x_106_);
return v___x_107_;
}
}
LEAN_EXPORT lean_object* lp_competition_R2W01b_tableProduct___boxed(lean_object* v_u_108_){
_start:
{
uint32_t v_u_boxed_109_; float v_res_110_; lean_object* v_r_111_; 
v_u_boxed_109_ = lean_unbox_uint32(v_u_108_);
lean_dec(v_u_108_);
v_res_110_ = lp_competition_R2W01b_tableProduct(v_u_boxed_109_);
v_r_111_ = lean_box_float32(v_res_110_);
return v_r_111_;
}
}
LEAN_EXPORT float lp_competition_R2W01b_convert(uint32_t v_u_112_){
_start:
{
uint8_t v___y_114_; uint32_t v___x_128_; uint32_t v_a_129_; uint32_t v___x_130_; uint32_t v___x_131_; uint32_t v___x_132_; uint8_t v___x_133_; 
v___x_128_ = 2147483647;
v_a_129_ = lean_uint32_land(v_u_112_, v___x_128_);
v___x_130_ = 201326591;
v___x_131_ = 1;
v___x_132_ = lean_uint32_sub(v_a_129_, v___x_131_);
v___x_133_ = lean_uint32_dec_le(v___x_130_, v___x_132_);
if (v___x_133_ == 0)
{
v___y_114_ = v___x_133_;
goto v___jp_113_;
}
else
{
uint32_t v___x_134_; uint8_t v___x_135_; 
v___x_134_ = 2139095040;
v___x_135_ = lean_uint32_dec_lt(v_a_129_, v___x_134_);
v___y_114_ = v___x_135_;
goto v___jp_113_;
}
v___jp_113_:
{
if (v___y_114_ == 0)
{
float v___x_115_; 
v___x_115_ = lean_float32_of_bits(v_u_112_);
return v___x_115_;
}
else
{
uint32_t v___x_116_; uint32_t v___x_117_; uint32_t v___x_118_; uint32_t v___x_119_; float v___x_120_; lean_object* v___x_121_; uint32_t v___x_122_; uint32_t v___x_123_; lean_object* v___x_124_; lean_object* v___x_125_; float v___x_126_; float v___x_127_; 
v___x_116_ = 8388607;
v___x_117_ = lean_uint32_land(v_u_112_, v___x_116_);
v___x_118_ = 8388608;
v___x_119_ = lean_uint32_lor(v___x_117_, v___x_118_);
v___x_120_ = lean_uint32_to_float32(v___x_119_);
v___x_121_ = lp_competition_R2W01b_scaleTable;
v___x_122_ = 23;
v___x_123_ = lean_uint32_shift_right(v_u_112_, v___x_122_);
v___x_124_ = lean_uint32_to_nat(v___x_123_);
v___x_125_ = lean_array_fget_borrowed(v___x_121_, v___x_124_);
lean_dec(v___x_124_);
v___x_126_ = lean_unbox_float32(v___x_125_);
v___x_127_ = lean_float32_mul(v___x_120_, v___x_126_);
return v___x_127_;
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_R2W01b_convert___boxed(lean_object* v_u_136_){
_start:
{
uint32_t v_u_boxed_137_; float v_res_138_; lean_object* v_r_139_; 
v_u_boxed_137_ = lean_unbox_uint32(v_u_136_);
lean_dec(v_u_136_);
v_res_138_ = lp_competition_R2W01b_convert(v_u_boxed_137_);
v_r_139_ = lean_box_float32(v_res_138_);
return v_r_139_;
}
}
LEAN_EXPORT lean_object* lp_competition_R2W01c_nativeModel(float v_x_140_){
_start:
{
uint32_t v___x_141_; lean_object* v___x_142_; 
v___x_141_ = lean_float32_to_bits(v_x_140_);
v___x_142_ = lean_uint32_to_nat(v___x_141_);
return v___x_142_;
}
}
LEAN_EXPORT lean_object* lp_competition_R2W01c_nativeModel___boxed(lean_object* v_x_143_){
_start:
{
float v_x_boxed_144_; lean_object* v_res_145_; 
v_x_boxed_144_ = lean_unbox_float32(v_x_143_);
lean_dec_ref(v_x_143_);
v_res_145_ = lp_competition_R2W01c_nativeModel(v_x_boxed_144_);
return v_res_145_;
}
}
LEAN_EXPORT lean_object* lp_competition_R2W01c_rawModel(uint32_t v_u_146_){
_start:
{
lean_object* v___x_147_; 
v___x_147_ = lean_uint32_to_nat(v_u_146_);
return v___x_147_;
}
}
LEAN_EXPORT lean_object* lp_competition_R2W01c_rawModel___boxed(lean_object* v_u_148_){
_start:
{
uint32_t v_u_boxed_149_; lean_object* v_res_150_; 
v_u_boxed_149_ = lean_unbox_uint32(v_u_148_);
lean_dec(v_u_148_);
v_res_150_ = lp_competition_R2W01c_rawModel(v_u_boxed_149_);
return v_res_150_;
}
}
LEAN_EXPORT lean_object* lp_competition_R2W01c_raw32(uint32_t v_u_151_){
_start:
{
lean_object* v___x_152_; lean_object* v___x_153_; lean_object* v___x_154_; 
v___x_152_ = lean_uint32_to_nat(v_u_151_);
v___x_153_ = lean_unsigned_to_nat(32u);
v___x_154_ = l_BitVec_ofNat(v___x_153_, v___x_152_);
lean_dec(v___x_152_);
return v___x_154_;
}
}
LEAN_EXPORT lean_object* lp_competition_R2W01c_raw32___boxed(lean_object* v_u_155_){
_start:
{
uint32_t v_u_boxed_156_; lean_object* v_res_157_; 
v_u_boxed_156_ = lean_unbox_uint32(v_u_155_);
lean_dec(v_u_155_);
v_res_157_ = lp_competition_R2W01c_raw32(v_u_boxed_156_);
return v_res_157_;
}
}
LEAN_EXPORT uint8_t lp_competition_R2W01c_wordSign(uint32_t v_u_158_){
_start:
{
lean_object* v___x_159_; lean_object* v___x_160_; uint8_t v___x_161_; 
v___x_159_ = lean_unsigned_to_nat(2147483648u);
v___x_160_ = lean_uint32_to_nat(v_u_158_);
v___x_161_ = lean_nat_dec_le(v___x_159_, v___x_160_);
lean_dec(v___x_160_);
return v___x_161_;
}
}
LEAN_EXPORT lean_object* lp_competition_R2W01c_wordSign___boxed(lean_object* v_u_162_){
_start:
{
uint32_t v_u_boxed_163_; uint8_t v_res_164_; lean_object* v_r_165_; 
v_u_boxed_163_ = lean_unbox_uint32(v_u_162_);
lean_dec(v_u_162_);
v_res_164_ = lp_competition_R2W01c_wordSign(v_u_boxed_163_);
v_r_165_ = lean_box(v_res_164_);
return v_r_165_;
}
}
LEAN_EXPORT lean_object* lp_competition_R2W01c_wordExp(uint32_t v_u_166_){
_start:
{
lean_object* v___x_167_; lean_object* v___x_168_; lean_object* v___x_169_; lean_object* v___x_170_; lean_object* v___x_171_; 
v___x_167_ = lean_uint32_to_nat(v_u_166_);
v___x_168_ = lean_unsigned_to_nat(23u);
v___x_169_ = lean_nat_shiftr(v___x_167_, v___x_168_);
lean_dec(v___x_167_);
v___x_170_ = lean_unsigned_to_nat(256u);
v___x_171_ = lean_nat_mod(v___x_169_, v___x_170_);
lean_dec(v___x_169_);
return v___x_171_;
}
}
LEAN_EXPORT lean_object* lp_competition_R2W01c_wordExp___boxed(lean_object* v_u_172_){
_start:
{
uint32_t v_u_boxed_173_; lean_object* v_res_174_; 
v_u_boxed_173_ = lean_unbox_uint32(v_u_172_);
lean_dec(v_u_172_);
v_res_174_ = lp_competition_R2W01c_wordExp(v_u_boxed_173_);
return v_res_174_;
}
}
LEAN_EXPORT lean_object* lp_competition_R2W01c_wordFrac(uint32_t v_u_175_){
_start:
{
lean_object* v___x_176_; lean_object* v___x_177_; lean_object* v___x_178_; 
v___x_176_ = lean_uint32_to_nat(v_u_175_);
v___x_177_ = lean_unsigned_to_nat(8388608u);
v___x_178_ = lean_nat_mod(v___x_176_, v___x_177_);
lean_dec(v___x_176_);
return v___x_178_;
}
}
LEAN_EXPORT lean_object* lp_competition_R2W01c_wordFrac___boxed(lean_object* v_u_179_){
_start:
{
uint32_t v_u_boxed_180_; lean_object* v_res_181_; 
v_u_boxed_180_ = lean_unbox_uint32(v_u_179_);
lean_dec(v_u_179_);
v_res_181_ = lp_competition_R2W01c_wordFrac(v_u_boxed_180_);
return v_res_181_;
}
}
LEAN_EXPORT uint64_t lp_competition_Submission_TunedAdd_sx(uint64_t v_k_182_, uint64_t v_x_183_){
_start:
{
uint64_t v___x_184_; uint64_t v___x_185_; uint8_t v___x_186_; 
v___x_184_ = lean_uint64_shift_right(v_x_183_, v_k_182_);
v___x_185_ = 0ULL;
v___x_186_ = lean_uint64_dec_eq(v___x_184_, v___x_185_);
if (v___x_186_ == 0)
{
return v___x_184_;
}
else
{
return v_x_183_;
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_TunedAdd_sx___boxed(lean_object* v_k_187_, lean_object* v_x_188_){
_start:
{
uint64_t v_k_boxed_189_; uint64_t v_x_boxed_190_; uint64_t v_res_191_; lean_object* v_r_192_; 
v_k_boxed_189_ = lean_unbox_uint64(v_k_187_);
lean_dec_ref(v_k_187_);
v_x_boxed_190_ = lean_unbox_uint64(v_x_188_);
lean_dec_ref(v_x_188_);
v_res_191_ = lp_competition_Submission_TunedAdd_sx(v_k_boxed_189_, v_x_boxed_190_);
v_r_192_ = lean_box_uint64(v_res_191_);
return v_r_192_;
}
}
LEAN_EXPORT uint64_t lp_competition_Submission_TunedAdd_sr(uint64_t v_k_193_, uint64_t v_x_194_, uint64_t v_r_195_){
_start:
{
uint64_t v___x_196_; uint64_t v___x_197_; uint8_t v___x_198_; 
v___x_196_ = lean_uint64_shift_right(v_x_194_, v_k_193_);
v___x_197_ = 0ULL;
v___x_198_ = lean_uint64_dec_eq(v___x_196_, v___x_197_);
if (v___x_198_ == 0)
{
uint64_t v___x_199_; 
v___x_199_ = lean_uint64_add(v_r_195_, v_k_193_);
return v___x_199_;
}
else
{
return v_r_195_;
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_TunedAdd_sr___boxed(lean_object* v_k_200_, lean_object* v_x_201_, lean_object* v_r_202_){
_start:
{
uint64_t v_k_boxed_203_; uint64_t v_x_boxed_204_; uint64_t v_r_boxed_205_; uint64_t v_res_206_; lean_object* v_r_207_; 
v_k_boxed_203_ = lean_unbox_uint64(v_k_200_);
lean_dec_ref(v_k_200_);
v_x_boxed_204_ = lean_unbox_uint64(v_x_201_);
lean_dec_ref(v_x_201_);
v_r_boxed_205_ = lean_unbox_uint64(v_r_202_);
lean_dec_ref(v_r_202_);
v_res_206_ = lp_competition_Submission_TunedAdd_sr(v_k_boxed_203_, v_x_boxed_204_, v_r_boxed_205_);
v_r_207_ = lean_box_uint64(v_res_206_);
return v_r_207_;
}
}
LEAN_EXPORT uint64_t lp_competition_Submission_TunedAdd_fastLog2(uint64_t v_x0_208_){
_start:
{
uint64_t v___y_210_; uint64_t v___y_211_; uint64_t v___y_218_; uint64_t v___y_219_; uint64_t v___y_220_; uint64_t v___y_221_; uint64_t v___y_227_; uint64_t v___y_228_; uint64_t v___y_234_; uint64_t v___y_235_; uint64_t v___y_236_; uint64_t v___y_237_; uint64_t v___y_243_; uint64_t v___y_244_; uint64_t v___y_250_; uint64_t v___y_251_; uint64_t v___y_252_; uint64_t v___y_253_; uint64_t v___y_259_; uint64_t v___y_260_; uint64_t v___y_266_; uint64_t v___y_267_; uint64_t v___y_268_; uint64_t v___y_269_; uint64_t v___y_275_; uint64_t v___y_276_; uint64_t v___x_281_; uint64_t v___y_283_; uint64_t v___x_287_; uint64_t v___x_288_; uint8_t v___x_289_; 
v___x_281_ = 32ULL;
v___x_287_ = lean_uint64_shift_right(v_x0_208_, v___x_281_);
v___x_288_ = 0ULL;
v___x_289_ = lean_uint64_dec_eq(v___x_287_, v___x_288_);
if (v___x_289_ == 0)
{
v___y_283_ = v___x_287_;
goto v___jp_282_;
}
else
{
v___y_283_ = v_x0_208_;
goto v___jp_282_;
}
v___jp_209_:
{
uint64_t v___x_212_; uint64_t v___x_213_; uint64_t v___x_214_; uint8_t v___x_215_; 
v___x_212_ = 1ULL;
v___x_213_ = lean_uint64_shift_right(v___y_210_, v___x_212_);
v___x_214_ = 0ULL;
v___x_215_ = lean_uint64_dec_eq(v___x_213_, v___x_214_);
if (v___x_215_ == 0)
{
uint64_t v___x_216_; 
v___x_216_ = lean_uint64_add(v___y_211_, v___x_212_);
return v___x_216_;
}
else
{
return v___y_211_;
}
}
v___jp_217_:
{
uint64_t v___x_222_; uint64_t v___x_223_; uint8_t v___x_224_; 
v___x_222_ = lean_uint64_shift_right(v___y_218_, v___y_220_);
v___x_223_ = 0ULL;
v___x_224_ = lean_uint64_dec_eq(v___x_222_, v___x_223_);
if (v___x_224_ == 0)
{
uint64_t v___x_225_; 
v___x_225_ = lean_uint64_add(v___y_219_, v___y_220_);
v___y_210_ = v___y_221_;
v___y_211_ = v___x_225_;
goto v___jp_209_;
}
else
{
v___y_210_ = v___y_221_;
v___y_211_ = v___y_219_;
goto v___jp_209_;
}
}
v___jp_226_:
{
uint64_t v___x_229_; uint64_t v___x_230_; uint64_t v___x_231_; uint8_t v___x_232_; 
v___x_229_ = 2ULL;
v___x_230_ = lean_uint64_shift_right(v___y_227_, v___x_229_);
v___x_231_ = 0ULL;
v___x_232_ = lean_uint64_dec_eq(v___x_230_, v___x_231_);
if (v___x_232_ == 0)
{
v___y_218_ = v___y_227_;
v___y_219_ = v___y_228_;
v___y_220_ = v___x_229_;
v___y_221_ = v___x_230_;
goto v___jp_217_;
}
else
{
v___y_218_ = v___y_227_;
v___y_219_ = v___y_228_;
v___y_220_ = v___x_229_;
v___y_221_ = v___y_227_;
goto v___jp_217_;
}
}
v___jp_233_:
{
uint64_t v___x_238_; uint64_t v___x_239_; uint8_t v___x_240_; 
v___x_238_ = lean_uint64_shift_right(v___y_235_, v___y_234_);
v___x_239_ = 0ULL;
v___x_240_ = lean_uint64_dec_eq(v___x_238_, v___x_239_);
if (v___x_240_ == 0)
{
uint64_t v___x_241_; 
v___x_241_ = lean_uint64_add(v___y_236_, v___y_234_);
v___y_227_ = v___y_237_;
v___y_228_ = v___x_241_;
goto v___jp_226_;
}
else
{
v___y_227_ = v___y_237_;
v___y_228_ = v___y_236_;
goto v___jp_226_;
}
}
v___jp_242_:
{
uint64_t v___x_245_; uint64_t v___x_246_; uint64_t v___x_247_; uint8_t v___x_248_; 
v___x_245_ = 4ULL;
v___x_246_ = lean_uint64_shift_right(v___y_243_, v___x_245_);
v___x_247_ = 0ULL;
v___x_248_ = lean_uint64_dec_eq(v___x_246_, v___x_247_);
if (v___x_248_ == 0)
{
v___y_234_ = v___x_245_;
v___y_235_ = v___y_243_;
v___y_236_ = v___y_244_;
v___y_237_ = v___x_246_;
goto v___jp_233_;
}
else
{
v___y_234_ = v___x_245_;
v___y_235_ = v___y_243_;
v___y_236_ = v___y_244_;
v___y_237_ = v___y_243_;
goto v___jp_233_;
}
}
v___jp_249_:
{
uint64_t v___x_254_; uint64_t v___x_255_; uint8_t v___x_256_; 
v___x_254_ = lean_uint64_shift_right(v___y_250_, v___y_252_);
v___x_255_ = 0ULL;
v___x_256_ = lean_uint64_dec_eq(v___x_254_, v___x_255_);
if (v___x_256_ == 0)
{
uint64_t v___x_257_; 
v___x_257_ = lean_uint64_add(v___y_251_, v___y_252_);
v___y_243_ = v___y_253_;
v___y_244_ = v___x_257_;
goto v___jp_242_;
}
else
{
v___y_243_ = v___y_253_;
v___y_244_ = v___y_251_;
goto v___jp_242_;
}
}
v___jp_258_:
{
uint64_t v___x_261_; uint64_t v___x_262_; uint64_t v___x_263_; uint8_t v___x_264_; 
v___x_261_ = 8ULL;
v___x_262_ = lean_uint64_shift_right(v___y_259_, v___x_261_);
v___x_263_ = 0ULL;
v___x_264_ = lean_uint64_dec_eq(v___x_262_, v___x_263_);
if (v___x_264_ == 0)
{
v___y_250_ = v___y_259_;
v___y_251_ = v___y_260_;
v___y_252_ = v___x_261_;
v___y_253_ = v___x_262_;
goto v___jp_249_;
}
else
{
v___y_250_ = v___y_259_;
v___y_251_ = v___y_260_;
v___y_252_ = v___x_261_;
v___y_253_ = v___y_259_;
goto v___jp_249_;
}
}
v___jp_265_:
{
uint64_t v___x_270_; uint64_t v___x_271_; uint8_t v___x_272_; 
v___x_270_ = lean_uint64_shift_right(v___y_268_, v___y_266_);
v___x_271_ = 0ULL;
v___x_272_ = lean_uint64_dec_eq(v___x_270_, v___x_271_);
if (v___x_272_ == 0)
{
uint64_t v___x_273_; 
v___x_273_ = lean_uint64_add(v___y_267_, v___y_266_);
v___y_259_ = v___y_269_;
v___y_260_ = v___x_273_;
goto v___jp_258_;
}
else
{
v___y_259_ = v___y_269_;
v___y_260_ = v___y_267_;
goto v___jp_258_;
}
}
v___jp_274_:
{
uint64_t v___x_277_; uint64_t v___x_278_; uint64_t v___x_279_; uint8_t v___x_280_; 
v___x_277_ = 16ULL;
v___x_278_ = lean_uint64_shift_right(v___y_275_, v___x_277_);
v___x_279_ = 0ULL;
v___x_280_ = lean_uint64_dec_eq(v___x_278_, v___x_279_);
if (v___x_280_ == 0)
{
v___y_266_ = v___x_277_;
v___y_267_ = v___y_276_;
v___y_268_ = v___y_275_;
v___y_269_ = v___x_278_;
goto v___jp_265_;
}
else
{
v___y_266_ = v___x_277_;
v___y_267_ = v___y_276_;
v___y_268_ = v___y_275_;
v___y_269_ = v___y_275_;
goto v___jp_265_;
}
}
v___jp_282_:
{
uint64_t v___x_284_; uint64_t v___x_285_; uint8_t v___x_286_; 
v___x_284_ = lean_uint64_shift_right(v_x0_208_, v___x_281_);
v___x_285_ = 0ULL;
v___x_286_ = lean_uint64_dec_eq(v___x_284_, v___x_285_);
if (v___x_286_ == 0)
{
v___y_275_ = v___y_283_;
v___y_276_ = v___x_281_;
goto v___jp_274_;
}
else
{
v___y_275_ = v___y_283_;
v___y_276_ = v___x_285_;
goto v___jp_274_;
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_TunedAdd_fastLog2___boxed(lean_object* v_x0_290_){
_start:
{
uint64_t v_x0_boxed_291_; uint64_t v_res_292_; lean_object* v_r_293_; 
v_x0_boxed_291_ = lean_unbox_uint64(v_x0_290_);
lean_dec_ref(v_x0_290_);
v_res_292_ = lp_competition_Submission_TunedAdd_fastLog2(v_x0_boxed_291_);
v_r_293_ = lean_box_uint64(v_res_292_);
return v_r_293_;
}
}
LEAN_EXPORT uint64_t lp_competition_Submission_TunedAdd_rse(uint64_t v_value_294_, uint64_t v_shift_295_){
_start:
{
uint64_t v_quotient_296_; uint64_t v___x_297_; uint64_t v___x_298_; uint64_t v___x_299_; uint64_t v_remainder_300_; uint64_t v___x_301_; uint64_t v_half_302_; uint8_t v___x_303_; 
v_quotient_296_ = lean_uint64_shift_right(v_value_294_, v_shift_295_);
v___x_297_ = 1ULL;
v___x_298_ = lean_uint64_shift_left(v___x_297_, v_shift_295_);
v___x_299_ = lean_uint64_sub(v___x_298_, v___x_297_);
v_remainder_300_ = lean_uint64_land(v_value_294_, v___x_299_);
v___x_301_ = lean_uint64_sub(v_shift_295_, v___x_297_);
v_half_302_ = lean_uint64_shift_left(v___x_297_, v___x_301_);
v___x_303_ = lean_uint64_dec_lt(v_remainder_300_, v_half_302_);
if (v___x_303_ == 0)
{
uint8_t v___x_304_; 
v___x_304_ = lean_uint64_dec_lt(v_half_302_, v_remainder_300_);
if (v___x_304_ == 0)
{
uint64_t v___x_305_; uint64_t v___x_306_; uint8_t v___x_307_; 
v___x_305_ = lean_uint64_land(v_quotient_296_, v___x_297_);
v___x_306_ = 0ULL;
v___x_307_ = lean_uint64_dec_eq(v___x_305_, v___x_306_);
if (v___x_307_ == 0)
{
uint64_t v___x_308_; 
v___x_308_ = lean_uint64_add(v_quotient_296_, v___x_297_);
return v___x_308_;
}
else
{
return v_quotient_296_;
}
}
else
{
uint64_t v___x_309_; 
v___x_309_ = lean_uint64_add(v_quotient_296_, v___x_297_);
return v___x_309_;
}
}
else
{
return v_quotient_296_;
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_TunedAdd_rse___boxed(lean_object* v_value_310_, lean_object* v_shift_311_){
_start:
{
uint64_t v_value_boxed_312_; uint64_t v_shift_boxed_313_; uint64_t v_res_314_; lean_object* v_r_315_; 
v_value_boxed_312_ = lean_unbox_uint64(v_value_310_);
lean_dec_ref(v_value_310_);
v_shift_boxed_313_ = lean_unbox_uint64(v_shift_311_);
lean_dec_ref(v_shift_311_);
v_res_314_ = lp_competition_Submission_TunedAdd_rse(v_value_boxed_312_, v_shift_boxed_313_);
v_r_315_ = lean_box_uint64(v_res_314_);
return v_r_315_;
}
}
LEAN_EXPORT uint64_t lp_competition_Submission_TunedAdd_rseAny(uint64_t v_value_316_, uint64_t v_shift_317_){
_start:
{
uint64_t v___x_318_; uint8_t v___x_319_; 
v___x_318_ = 0ULL;
v___x_319_ = lean_uint64_dec_eq(v_shift_317_, v___x_318_);
if (v___x_319_ == 0)
{
uint64_t v___x_320_; uint8_t v___x_321_; 
v___x_320_ = 64ULL;
v___x_321_ = lean_uint64_dec_lt(v_shift_317_, v___x_320_);
if (v___x_321_ == 0)
{
uint8_t v___x_322_; 
v___x_322_ = lean_uint64_dec_eq(v_shift_317_, v___x_320_);
if (v___x_322_ == 0)
{
return v___x_318_;
}
else
{
uint64_t v___x_323_; uint8_t v___x_324_; 
v___x_323_ = 9223372036854775808ULL;
v___x_324_ = lean_uint64_dec_lt(v___x_323_, v_value_316_);
if (v___x_324_ == 0)
{
return v___x_318_;
}
else
{
uint64_t v___x_325_; 
v___x_325_ = 1ULL;
return v___x_325_;
}
}
}
else
{
uint64_t v_quotient_326_; uint64_t v___x_327_; uint64_t v___x_328_; uint64_t v___x_329_; uint64_t v_remainder_330_; uint64_t v___x_331_; uint64_t v_half_332_; uint8_t v___x_333_; 
v_quotient_326_ = lean_uint64_shift_right(v_value_316_, v_shift_317_);
v___x_327_ = 1ULL;
v___x_328_ = lean_uint64_shift_left(v___x_327_, v_shift_317_);
v___x_329_ = lean_uint64_sub(v___x_328_, v___x_327_);
v_remainder_330_ = lean_uint64_land(v_value_316_, v___x_329_);
v___x_331_ = lean_uint64_sub(v_shift_317_, v___x_327_);
v_half_332_ = lean_uint64_shift_left(v___x_327_, v___x_331_);
v___x_333_ = lean_uint64_dec_lt(v_remainder_330_, v_half_332_);
if (v___x_333_ == 0)
{
uint8_t v___x_334_; 
v___x_334_ = lean_uint64_dec_lt(v_half_332_, v_remainder_330_);
if (v___x_334_ == 0)
{
uint64_t v___x_335_; uint8_t v___x_336_; 
v___x_335_ = lean_uint64_land(v_quotient_326_, v___x_327_);
v___x_336_ = lean_uint64_dec_eq(v___x_335_, v___x_318_);
if (v___x_336_ == 0)
{
uint64_t v___x_337_; 
v___x_337_ = lean_uint64_add(v_quotient_326_, v___x_327_);
return v___x_337_;
}
else
{
return v_quotient_326_;
}
}
else
{
uint64_t v___x_338_; 
v___x_338_ = lean_uint64_add(v_quotient_326_, v___x_327_);
return v___x_338_;
}
}
else
{
return v_quotient_326_;
}
}
}
else
{
return v_value_316_;
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_TunedAdd_rseAny___boxed(lean_object* v_value_339_, lean_object* v_shift_340_){
_start:
{
uint64_t v_value_boxed_341_; uint64_t v_shift_boxed_342_; uint64_t v_res_343_; lean_object* v_r_344_; 
v_value_boxed_341_ = lean_unbox_uint64(v_value_339_);
lean_dec_ref(v_value_339_);
v_shift_boxed_342_ = lean_unbox_uint64(v_shift_340_);
lean_dec_ref(v_shift_340_);
v_res_343_ = lp_competition_Submission_TunedAdd_rseAny(v_value_boxed_341_, v_shift_boxed_342_);
v_r_344_ = lean_box_uint64(v_res_343_);
return v_r_344_;
}
}
LEAN_EXPORT uint32_t lp_competition_Submission_TunedAdd_mkW(uint8_t v_sign_345_, uint32_t v_e_346_, uint32_t v_f_347_){
_start:
{
uint32_t v___y_349_; 
if (v_sign_345_ == 0)
{
uint32_t v___x_358_; 
v___x_358_ = 0;
v___y_349_ = v___x_358_;
goto v___jp_348_;
}
else
{
uint32_t v___x_359_; 
v___x_359_ = 2147483648;
v___y_349_ = v___x_359_;
goto v___jp_348_;
}
v___jp_348_:
{
uint32_t v___x_350_; uint32_t v___x_351_; uint32_t v___x_352_; uint32_t v___x_353_; uint32_t v___x_354_; uint32_t v___x_355_; uint32_t v___x_356_; uint32_t v___x_357_; 
v___x_350_ = 255;
v___x_351_ = lean_uint32_land(v_e_346_, v___x_350_);
v___x_352_ = 23;
v___x_353_ = lean_uint32_shift_left(v___x_351_, v___x_352_);
v___x_354_ = lean_uint32_lor(v___y_349_, v___x_353_);
v___x_355_ = 8388607;
v___x_356_ = lean_uint32_land(v_f_347_, v___x_355_);
v___x_357_ = lean_uint32_lor(v___x_354_, v___x_356_);
return v___x_357_;
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_TunedAdd_mkW___boxed(lean_object* v_sign_360_, lean_object* v_e_361_, lean_object* v_f_362_){
_start:
{
uint8_t v_sign_boxed_363_; uint32_t v_e_boxed_364_; uint32_t v_f_boxed_365_; uint32_t v_res_366_; lean_object* v_r_367_; 
v_sign_boxed_363_ = lean_unbox(v_sign_360_);
v_e_boxed_364_ = lean_unbox_uint32(v_e_361_);
lean_dec(v_e_361_);
v_f_boxed_365_ = lean_unbox_uint32(v_f_362_);
lean_dec(v_f_362_);
v_res_366_ = lp_competition_Submission_TunedAdd_mkW(v_sign_boxed_363_, v_e_boxed_364_, v_f_boxed_365_);
v_r_367_ = lean_box_uint32(v_res_366_);
return v_r_367_;
}
}
static uint32_t _init_lp_competition_Submission_TunedAdd_fracW___closed__0(void){
_start:
{
uint64_t v___x_368_; uint32_t v___x_369_; 
v___x_368_ = 0ULL;
v___x_369_ = lean_uint64_to_uint32(v___x_368_);
return v___x_369_;
}
}
LEAN_EXPORT uint32_t lp_competition_Submission_TunedAdd_fracW(uint64_t v_n_370_){
_start:
{
uint64_t v___x_371_; uint8_t v___x_372_; 
v___x_371_ = 8388608ULL;
v___x_372_ = lean_uint64_dec_lt(v_n_370_, v___x_371_);
if (v___x_372_ == 0)
{
uint64_t v___x_373_; uint32_t v___x_374_; 
v___x_373_ = lean_uint64_sub(v_n_370_, v___x_371_);
v___x_374_ = lean_uint64_to_uint32(v___x_373_);
return v___x_374_;
}
else
{
uint32_t v___x_375_; 
v___x_375_ = lean_uint32_once(&lp_competition_Submission_TunedAdd_fracW___closed__0, &lp_competition_Submission_TunedAdd_fracW___closed__0_once, _init_lp_competition_Submission_TunedAdd_fracW___closed__0);
return v___x_375_;
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_TunedAdd_fracW___boxed(lean_object* v_n_376_){
_start:
{
uint64_t v_n_boxed_377_; uint32_t v_res_378_; lean_object* v_r_379_; 
v_n_boxed_377_ = lean_unbox_uint64(v_n_376_);
lean_dec_ref(v_n_376_);
v_res_378_ = lp_competition_Submission_TunedAdd_fracW(v_n_boxed_377_);
v_r_379_ = lean_box_uint32(v_res_378_);
return v_r_379_;
}
}
LEAN_EXPORT uint32_t lp_competition_Submission_TunedAdd_roundP(uint8_t v_sign_380_, uint64_t v_product_381_, uint64_t v_scale_382_){
_start:
{
uint32_t v___y_384_; uint32_t v___y_388_; uint32_t v___y_389_; uint32_t v___y_394_; uint32_t v___y_395_; uint32_t v___y_396_; uint32_t v___y_406_; uint32_t v___y_407_; uint64_t v___x_410_; uint64_t v___y_412_; uint64_t v___y_424_; uint64_t v___y_425_; uint64_t v___y_435_; uint8_t v___y_436_; uint64_t v___y_437_; uint64_t v___y_444_; uint64_t v___y_445_; uint64_t v___y_451_; uint64_t v___y_506_; uint64_t v___y_507_; uint64_t v___y_513_; uint64_t v___y_514_; uint64_t v___y_515_; uint64_t v___y_516_; uint64_t v___y_521_; uint64_t v___y_522_; uint64_t v___y_527_; uint64_t v___y_528_; uint64_t v___y_529_; uint64_t v___y_530_; uint64_t v___y_535_; uint64_t v___y_536_; uint64_t v___y_541_; uint64_t v___y_542_; uint64_t v___y_543_; uint64_t v___y_544_; uint64_t v___y_549_; uint64_t v___y_550_; uint64_t v___y_555_; uint64_t v___y_556_; uint64_t v___y_557_; uint64_t v___y_558_; uint64_t v___y_563_; uint64_t v___y_564_; uint8_t v___x_568_; 
v___x_410_ = 0ULL;
v___x_568_ = lean_uint64_dec_eq(v_product_381_, v___x_410_);
if (v___x_568_ == 0)
{
uint64_t v___x_569_; uint64_t v___y_571_; uint64_t v___x_574_; uint8_t v___x_575_; 
v___x_569_ = 32ULL;
v___x_574_ = lean_uint64_shift_right(v_product_381_, v___x_569_);
v___x_575_ = lean_uint64_dec_eq(v___x_574_, v___x_410_);
if (v___x_575_ == 0)
{
v___y_571_ = v___x_574_;
goto v___jp_570_;
}
else
{
v___y_571_ = v_product_381_;
goto v___jp_570_;
}
v___jp_570_:
{
uint64_t v___x_572_; uint8_t v___x_573_; 
v___x_572_ = lean_uint64_shift_right(v_product_381_, v___x_569_);
v___x_573_ = lean_uint64_dec_eq(v___x_572_, v___x_410_);
if (v___x_573_ == 0)
{
v___y_563_ = v___y_571_;
v___y_564_ = v___x_569_;
goto v___jp_562_;
}
else
{
v___y_563_ = v___y_571_;
v___y_564_ = v___x_410_;
goto v___jp_562_;
}
}
}
else
{
if (v_sign_380_ == 0)
{
uint32_t v___x_576_; 
v___x_576_ = 0;
return v___x_576_;
}
else
{
uint32_t v___x_577_; 
v___x_577_ = 2147483648;
return v___x_577_;
}
}
v___jp_383_:
{
uint32_t v___x_385_; uint32_t v___x_386_; 
v___x_385_ = 8388608;
v___x_386_ = lean_uint32_lor(v___y_384_, v___x_385_);
return v___x_386_;
}
v___jp_387_:
{
uint32_t v___x_390_; uint32_t v___x_391_; uint32_t v___x_392_; 
v___x_390_ = 8388607;
v___x_391_ = lean_uint32_land(v___y_388_, v___x_390_);
v___x_392_ = lean_uint32_lor(v___y_389_, v___x_391_);
return v___x_392_;
}
v___jp_393_:
{
uint32_t v___x_397_; uint32_t v___x_398_; uint32_t v___x_399_; uint32_t v___x_400_; uint32_t v___x_401_; uint32_t v___x_402_; uint32_t v___x_403_; uint32_t v___x_404_; 
v___x_397_ = 255;
v___x_398_ = lean_uint32_land(v___y_394_, v___x_397_);
v___x_399_ = 23;
v___x_400_ = lean_uint32_shift_left(v___x_398_, v___x_399_);
v___x_401_ = lean_uint32_lor(v___y_396_, v___x_400_);
v___x_402_ = 8388607;
v___x_403_ = lean_uint32_land(v___y_395_, v___x_402_);
v___x_404_ = lean_uint32_lor(v___x_401_, v___x_403_);
return v___x_404_;
}
v___jp_405_:
{
if (v_sign_380_ == 0)
{
uint32_t v___x_408_; 
v___x_408_ = 0;
v___y_394_ = v___y_406_;
v___y_395_ = v___y_407_;
v___y_396_ = v___x_408_;
goto v___jp_393_;
}
else
{
uint32_t v___x_409_; 
v___x_409_ = 2147483648;
v___y_394_ = v___y_406_;
v___y_395_ = v___y_407_;
v___y_396_ = v___x_409_;
goto v___jp_393_;
}
}
v___jp_411_:
{
uint8_t v___x_413_; 
v___x_413_ = lean_uint64_dec_eq(v___y_412_, v___x_410_);
if (v___x_413_ == 0)
{
uint64_t v___x_414_; uint8_t v___x_415_; 
v___x_414_ = 8388608ULL;
v___x_415_ = lean_uint64_dec_eq(v___y_412_, v___x_414_);
if (v___x_415_ == 0)
{
uint32_t v___x_416_; 
v___x_416_ = lean_uint64_to_uint32(v___y_412_);
if (v_sign_380_ == 0)
{
uint32_t v___x_417_; 
v___x_417_ = 0;
v___y_388_ = v___x_416_;
v___y_389_ = v___x_417_;
goto v___jp_387_;
}
else
{
uint32_t v___x_418_; 
v___x_418_ = 2147483648;
v___y_388_ = v___x_416_;
v___y_389_ = v___x_418_;
goto v___jp_387_;
}
}
else
{
if (v_sign_380_ == 0)
{
uint32_t v___x_419_; 
v___x_419_ = 0;
v___y_384_ = v___x_419_;
goto v___jp_383_;
}
else
{
uint32_t v___x_420_; 
v___x_420_ = 2147483648;
v___y_384_ = v___x_420_;
goto v___jp_383_;
}
}
}
else
{
if (v_sign_380_ == 0)
{
uint32_t v___x_421_; 
v___x_421_ = 0;
return v___x_421_;
}
else
{
uint32_t v___x_422_; 
v___x_422_ = 2147483648;
return v___x_422_;
}
}
}
v___jp_423_:
{
uint64_t v___x_426_; uint64_t v_encodedExponent_427_; uint32_t v___x_428_; uint64_t v___x_429_; uint8_t v___x_430_; 
v___x_426_ = 171ULL;
v_encodedExponent_427_ = lean_uint64_sub(v___y_424_, v___x_426_);
v___x_428_ = lean_uint64_to_uint32(v_encodedExponent_427_);
v___x_429_ = 8388608ULL;
v___x_430_ = lean_uint64_dec_lt(v___y_425_, v___x_429_);
if (v___x_430_ == 0)
{
uint64_t v___x_431_; uint32_t v___x_432_; 
v___x_431_ = lean_uint64_sub(v___y_425_, v___x_429_);
v___x_432_ = lean_uint64_to_uint32(v___x_431_);
v___y_406_ = v___x_428_;
v___y_407_ = v___x_432_;
goto v___jp_405_;
}
else
{
uint32_t v___x_433_; 
v___x_433_ = lean_uint32_once(&lp_competition_Submission_TunedAdd_fracW___closed__0, &lp_competition_Submission_TunedAdd_fracW___closed__0_once, _init_lp_competition_Submission_TunedAdd_fracW___closed__0);
v___y_406_ = v___x_428_;
v___y_407_ = v___x_433_;
goto v___jp_405_;
}
}
v___jp_434_:
{
uint64_t v___x_438_; uint8_t v___x_439_; 
v___x_438_ = 425ULL;
v___x_439_ = lean_uint64_dec_lt(v___x_438_, v___y_437_);
if (v___x_439_ == 0)
{
if (v___y_436_ == 0)
{
v___y_424_ = v___y_437_;
v___y_425_ = v___y_435_;
goto v___jp_423_;
}
else
{
uint64_t v___x_440_; 
v___x_440_ = 8388608ULL;
v___y_424_ = v___y_437_;
v___y_425_ = v___x_440_;
goto v___jp_423_;
}
}
else
{
if (v_sign_380_ == 0)
{
uint32_t v___x_441_; 
v___x_441_ = 2139095040;
return v___x_441_;
}
else
{
uint32_t v___x_442_; 
v___x_442_ = 4286578688;
return v___x_442_;
}
}
}
v___jp_443_:
{
uint64_t v___x_446_; uint8_t v_carry_447_; 
v___x_446_ = 16777216ULL;
v_carry_447_ = lean_uint64_dec_eq(v___y_445_, v___x_446_);
if (v_carry_447_ == 0)
{
v___y_435_ = v___y_445_;
v___y_436_ = v_carry_447_;
v___y_437_ = v___y_444_;
goto v___jp_434_;
}
else
{
uint64_t v___x_448_; uint64_t v___x_449_; 
v___x_448_ = 1ULL;
v___x_449_ = lean_uint64_add(v___y_444_, v___x_448_);
v___y_435_ = v___y_445_;
v___y_436_ = v_carry_447_;
v___y_437_ = v___x_449_;
goto v___jp_434_;
}
}
v___jp_450_:
{
uint64_t v_position_452_; uint64_t v___x_453_; uint8_t v___x_454_; 
v_position_452_ = lean_uint64_add(v___y_451_, v_scale_382_);
v___x_453_ = 172ULL;
v___x_454_ = lean_uint64_dec_lt(v_position_452_, v___x_453_);
if (v___x_454_ == 0)
{
uint64_t v___x_455_; uint8_t v___x_456_; 
v___x_455_ = 23ULL;
v___x_456_ = lean_uint64_dec_lt(v___y_451_, v___x_455_);
if (v___x_456_ == 0)
{
uint64_t v___x_457_; uint8_t v___x_458_; 
v___x_457_ = lean_uint64_sub(v___y_451_, v___x_455_);
v___x_458_ = lean_uint64_dec_eq(v___x_457_, v___x_410_);
if (v___x_458_ == 0)
{
uint64_t v___x_459_; uint8_t v___x_460_; 
v___x_459_ = 64ULL;
v___x_460_ = lean_uint64_dec_lt(v___x_457_, v___x_459_);
if (v___x_460_ == 0)
{
uint8_t v___x_461_; 
v___x_461_ = lean_uint64_dec_eq(v___x_457_, v___x_459_);
if (v___x_461_ == 0)
{
v___y_444_ = v_position_452_;
v___y_445_ = v___x_410_;
goto v___jp_443_;
}
else
{
uint64_t v___x_462_; uint8_t v___x_463_; 
v___x_462_ = 9223372036854775808ULL;
v___x_463_ = lean_uint64_dec_lt(v___x_462_, v_product_381_);
if (v___x_463_ == 0)
{
v___y_444_ = v_position_452_;
v___y_445_ = v___x_410_;
goto v___jp_443_;
}
else
{
uint64_t v___x_464_; 
v___x_464_ = 1ULL;
v___y_444_ = v_position_452_;
v___y_445_ = v___x_464_;
goto v___jp_443_;
}
}
}
else
{
uint64_t v_quotient_465_; uint64_t v___x_466_; uint64_t v___x_467_; uint64_t v___x_468_; uint64_t v_remainder_469_; uint64_t v___x_470_; uint64_t v_half_471_; uint8_t v___x_472_; 
v_quotient_465_ = lean_uint64_shift_right(v_product_381_, v___x_457_);
v___x_466_ = 1ULL;
v___x_467_ = lean_uint64_shift_left(v___x_466_, v___x_457_);
v___x_468_ = lean_uint64_sub(v___x_467_, v___x_466_);
v_remainder_469_ = lean_uint64_land(v_product_381_, v___x_468_);
v___x_470_ = lean_uint64_sub(v___x_457_, v___x_466_);
v_half_471_ = lean_uint64_shift_left(v___x_466_, v___x_470_);
v___x_472_ = lean_uint64_dec_lt(v_remainder_469_, v_half_471_);
if (v___x_472_ == 0)
{
uint8_t v___x_473_; 
v___x_473_ = lean_uint64_dec_lt(v_half_471_, v_remainder_469_);
if (v___x_473_ == 0)
{
uint64_t v___x_474_; uint8_t v___x_475_; 
v___x_474_ = lean_uint64_land(v_quotient_465_, v___x_466_);
v___x_475_ = lean_uint64_dec_eq(v___x_474_, v___x_410_);
if (v___x_475_ == 0)
{
uint64_t v___x_476_; 
v___x_476_ = lean_uint64_add(v_quotient_465_, v___x_466_);
v___y_444_ = v_position_452_;
v___y_445_ = v___x_476_;
goto v___jp_443_;
}
else
{
v___y_444_ = v_position_452_;
v___y_445_ = v_quotient_465_;
goto v___jp_443_;
}
}
else
{
uint64_t v___x_477_; 
v___x_477_ = lean_uint64_add(v_quotient_465_, v___x_466_);
v___y_444_ = v_position_452_;
v___y_445_ = v___x_477_;
goto v___jp_443_;
}
}
else
{
v___y_444_ = v_position_452_;
v___y_445_ = v_quotient_465_;
goto v___jp_443_;
}
}
}
else
{
v___y_444_ = v_position_452_;
v___y_445_ = v_product_381_;
goto v___jp_443_;
}
}
else
{
uint64_t v___x_478_; uint64_t v___x_479_; 
v___x_478_ = lean_uint64_sub(v___x_455_, v___y_451_);
v___x_479_ = lean_uint64_shift_left(v_product_381_, v___x_478_);
v___y_444_ = v_position_452_;
v___y_445_ = v___x_479_;
goto v___jp_443_;
}
}
else
{
uint64_t v___x_480_; uint8_t v___x_481_; 
v___x_480_ = 149ULL;
v___x_481_ = lean_uint64_dec_lt(v_scale_382_, v___x_480_);
if (v___x_481_ == 0)
{
uint64_t v___x_482_; uint64_t v___x_483_; 
v___x_482_ = lean_uint64_sub(v_scale_382_, v___x_480_);
v___x_483_ = lean_uint64_shift_left(v_product_381_, v___x_482_);
v___y_412_ = v___x_483_;
goto v___jp_411_;
}
else
{
uint64_t v___x_484_; uint8_t v___x_485_; 
v___x_484_ = lean_uint64_sub(v___x_480_, v_scale_382_);
v___x_485_ = lean_uint64_dec_eq(v___x_484_, v___x_410_);
if (v___x_485_ == 0)
{
uint64_t v___x_486_; uint8_t v___x_487_; 
v___x_486_ = 64ULL;
v___x_487_ = lean_uint64_dec_lt(v___x_484_, v___x_486_);
if (v___x_487_ == 0)
{
uint8_t v___x_488_; 
v___x_488_ = lean_uint64_dec_eq(v___x_484_, v___x_486_);
if (v___x_488_ == 0)
{
v___y_412_ = v___x_410_;
goto v___jp_411_;
}
else
{
uint64_t v___x_489_; uint8_t v___x_490_; 
v___x_489_ = 9223372036854775808ULL;
v___x_490_ = lean_uint64_dec_lt(v___x_489_, v_product_381_);
if (v___x_490_ == 0)
{
v___y_412_ = v___x_410_;
goto v___jp_411_;
}
else
{
uint64_t v___x_491_; 
v___x_491_ = 1ULL;
v___y_412_ = v___x_491_;
goto v___jp_411_;
}
}
}
else
{
uint64_t v_quotient_492_; uint64_t v___x_493_; uint64_t v___x_494_; uint64_t v___x_495_; uint64_t v_remainder_496_; uint64_t v___x_497_; uint64_t v_half_498_; uint8_t v___x_499_; 
v_quotient_492_ = lean_uint64_shift_right(v_product_381_, v___x_484_);
v___x_493_ = 1ULL;
v___x_494_ = lean_uint64_shift_left(v___x_493_, v___x_484_);
v___x_495_ = lean_uint64_sub(v___x_494_, v___x_493_);
v_remainder_496_ = lean_uint64_land(v_product_381_, v___x_495_);
v___x_497_ = lean_uint64_sub(v___x_484_, v___x_493_);
v_half_498_ = lean_uint64_shift_left(v___x_493_, v___x_497_);
v___x_499_ = lean_uint64_dec_lt(v_remainder_496_, v_half_498_);
if (v___x_499_ == 0)
{
uint8_t v___x_500_; 
v___x_500_ = lean_uint64_dec_lt(v_half_498_, v_remainder_496_);
if (v___x_500_ == 0)
{
uint64_t v___x_501_; uint8_t v___x_502_; 
v___x_501_ = lean_uint64_land(v_quotient_492_, v___x_493_);
v___x_502_ = lean_uint64_dec_eq(v___x_501_, v___x_410_);
if (v___x_502_ == 0)
{
uint64_t v___x_503_; 
v___x_503_ = lean_uint64_add(v_quotient_492_, v___x_493_);
v___y_412_ = v___x_503_;
goto v___jp_411_;
}
else
{
v___y_412_ = v_quotient_492_;
goto v___jp_411_;
}
}
else
{
uint64_t v___x_504_; 
v___x_504_ = lean_uint64_add(v_quotient_492_, v___x_493_);
v___y_412_ = v___x_504_;
goto v___jp_411_;
}
}
else
{
v___y_412_ = v_quotient_492_;
goto v___jp_411_;
}
}
}
else
{
v___y_412_ = v_product_381_;
goto v___jp_411_;
}
}
}
}
v___jp_505_:
{
uint64_t v___x_508_; uint64_t v___x_509_; uint8_t v___x_510_; 
v___x_508_ = 1ULL;
v___x_509_ = lean_uint64_shift_right(v___y_506_, v___x_508_);
v___x_510_ = lean_uint64_dec_eq(v___x_509_, v___x_410_);
if (v___x_510_ == 0)
{
uint64_t v___x_511_; 
v___x_511_ = lean_uint64_add(v___y_507_, v___x_508_);
v___y_451_ = v___x_511_;
goto v___jp_450_;
}
else
{
v___y_451_ = v___y_507_;
goto v___jp_450_;
}
}
v___jp_512_:
{
uint64_t v___x_517_; uint8_t v___x_518_; 
v___x_517_ = lean_uint64_shift_right(v___y_513_, v___y_515_);
v___x_518_ = lean_uint64_dec_eq(v___x_517_, v___x_410_);
if (v___x_518_ == 0)
{
uint64_t v___x_519_; 
v___x_519_ = lean_uint64_add(v___y_514_, v___y_515_);
v___y_506_ = v___y_516_;
v___y_507_ = v___x_519_;
goto v___jp_505_;
}
else
{
v___y_506_ = v___y_516_;
v___y_507_ = v___y_514_;
goto v___jp_505_;
}
}
v___jp_520_:
{
uint64_t v___x_523_; uint64_t v___x_524_; uint8_t v___x_525_; 
v___x_523_ = 2ULL;
v___x_524_ = lean_uint64_shift_right(v___y_521_, v___x_523_);
v___x_525_ = lean_uint64_dec_eq(v___x_524_, v___x_410_);
if (v___x_525_ == 0)
{
v___y_513_ = v___y_521_;
v___y_514_ = v___y_522_;
v___y_515_ = v___x_523_;
v___y_516_ = v___x_524_;
goto v___jp_512_;
}
else
{
v___y_513_ = v___y_521_;
v___y_514_ = v___y_522_;
v___y_515_ = v___x_523_;
v___y_516_ = v___y_521_;
goto v___jp_512_;
}
}
v___jp_526_:
{
uint64_t v___x_531_; uint8_t v___x_532_; 
v___x_531_ = lean_uint64_shift_right(v___y_528_, v___y_529_);
v___x_532_ = lean_uint64_dec_eq(v___x_531_, v___x_410_);
if (v___x_532_ == 0)
{
uint64_t v___x_533_; 
v___x_533_ = lean_uint64_add(v___y_527_, v___y_529_);
v___y_521_ = v___y_530_;
v___y_522_ = v___x_533_;
goto v___jp_520_;
}
else
{
v___y_521_ = v___y_530_;
v___y_522_ = v___y_527_;
goto v___jp_520_;
}
}
v___jp_534_:
{
uint64_t v___x_537_; uint64_t v___x_538_; uint8_t v___x_539_; 
v___x_537_ = 4ULL;
v___x_538_ = lean_uint64_shift_right(v___y_535_, v___x_537_);
v___x_539_ = lean_uint64_dec_eq(v___x_538_, v___x_410_);
if (v___x_539_ == 0)
{
v___y_527_ = v___y_536_;
v___y_528_ = v___y_535_;
v___y_529_ = v___x_537_;
v___y_530_ = v___x_538_;
goto v___jp_526_;
}
else
{
v___y_527_ = v___y_536_;
v___y_528_ = v___y_535_;
v___y_529_ = v___x_537_;
v___y_530_ = v___y_535_;
goto v___jp_526_;
}
}
v___jp_540_:
{
uint64_t v___x_545_; uint8_t v___x_546_; 
v___x_545_ = lean_uint64_shift_right(v___y_541_, v___y_542_);
v___x_546_ = lean_uint64_dec_eq(v___x_545_, v___x_410_);
if (v___x_546_ == 0)
{
uint64_t v___x_547_; 
v___x_547_ = lean_uint64_add(v___y_543_, v___y_542_);
v___y_535_ = v___y_544_;
v___y_536_ = v___x_547_;
goto v___jp_534_;
}
else
{
v___y_535_ = v___y_544_;
v___y_536_ = v___y_543_;
goto v___jp_534_;
}
}
v___jp_548_:
{
uint64_t v___x_551_; uint64_t v___x_552_; uint8_t v___x_553_; 
v___x_551_ = 8ULL;
v___x_552_ = lean_uint64_shift_right(v___y_549_, v___x_551_);
v___x_553_ = lean_uint64_dec_eq(v___x_552_, v___x_410_);
if (v___x_553_ == 0)
{
v___y_541_ = v___y_549_;
v___y_542_ = v___x_551_;
v___y_543_ = v___y_550_;
v___y_544_ = v___x_552_;
goto v___jp_540_;
}
else
{
v___y_541_ = v___y_549_;
v___y_542_ = v___x_551_;
v___y_543_ = v___y_550_;
v___y_544_ = v___y_549_;
goto v___jp_540_;
}
}
v___jp_554_:
{
uint64_t v___x_559_; uint8_t v___x_560_; 
v___x_559_ = lean_uint64_shift_right(v___y_555_, v___y_556_);
v___x_560_ = lean_uint64_dec_eq(v___x_559_, v___x_410_);
if (v___x_560_ == 0)
{
uint64_t v___x_561_; 
v___x_561_ = lean_uint64_add(v___y_557_, v___y_556_);
v___y_549_ = v___y_558_;
v___y_550_ = v___x_561_;
goto v___jp_548_;
}
else
{
v___y_549_ = v___y_558_;
v___y_550_ = v___y_557_;
goto v___jp_548_;
}
}
v___jp_562_:
{
uint64_t v___x_565_; uint64_t v___x_566_; uint8_t v___x_567_; 
v___x_565_ = 16ULL;
v___x_566_ = lean_uint64_shift_right(v___y_563_, v___x_565_);
v___x_567_ = lean_uint64_dec_eq(v___x_566_, v___x_410_);
if (v___x_567_ == 0)
{
v___y_555_ = v___y_563_;
v___y_556_ = v___x_565_;
v___y_557_ = v___y_564_;
v___y_558_ = v___x_566_;
goto v___jp_554_;
}
else
{
v___y_555_ = v___y_563_;
v___y_556_ = v___x_565_;
v___y_557_ = v___y_564_;
v___y_558_ = v___y_563_;
goto v___jp_554_;
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_TunedAdd_roundP___boxed(lean_object* v_sign_578_, lean_object* v_product_579_, lean_object* v_scale_580_){
_start:
{
uint8_t v_sign_boxed_581_; uint64_t v_product_boxed_582_; uint64_t v_scale_boxed_583_; uint32_t v_res_584_; lean_object* v_r_585_; 
v_sign_boxed_581_ = lean_unbox(v_sign_578_);
v_product_boxed_582_ = lean_unbox_uint64(v_product_579_);
lean_dec_ref(v_product_579_);
v_scale_boxed_583_ = lean_unbox_uint64(v_scale_580_);
lean_dec_ref(v_scale_580_);
v_res_584_ = lp_competition_Submission_TunedAdd_roundP(v_sign_boxed_581_, v_product_boxed_582_, v_scale_boxed_583_);
v_r_585_ = lean_box_uint32(v_res_584_);
return v_r_585_;
}
}
LEAN_EXPORT uint32_t lp_competition_Submission_TunedAdd_core(uint32_t v_xBits_588_, uint32_t v_yBits_589_){
_start:
{
uint32_t v___y_591_; uint32_t v___y_595_; uint32_t v___y_599_; uint32_t v___y_600_; lean_object* v___y_605_; uint64_t v___y_606_; uint64_t v___y_607_; uint32_t v___y_622_; uint32_t v___y_623_; uint64_t v___y_628_; lean_object* v___y_629_; uint64_t v___y_630_; uint32_t v___x_644_; uint32_t v___x_645_; uint32_t v___x_646_; uint32_t v___y_648_; uint32_t v___y_649_; uint32_t v___y_650_; lean_object* v___y_658_; uint32_t v___y_659_; uint32_t v___y_660_; lean_object* v___y_665_; uint64_t v___y_666_; uint64_t v___y_667_; uint64_t v___y_668_; lean_object* v___y_678_; uint64_t v___y_679_; uint64_t v___y_680_; uint8_t v___y_681_; uint64_t v___y_682_; lean_object* v___y_690_; uint64_t v___y_691_; uint64_t v___y_692_; uint64_t v___y_693_; lean_object* v___y_699_; uint64_t v___y_700_; uint64_t v___y_701_; uint64_t v___y_702_; lean_object* v___y_703_; uint64_t v___y_704_; lean_object* v___y_768_; uint64_t v___y_769_; uint64_t v___y_770_; uint64_t v___y_771_; uint64_t v___y_772_; lean_object* v___y_773_; uint64_t v___y_774_; lean_object* v___y_780_; uint64_t v___y_781_; uint64_t v___y_782_; uint64_t v___y_783_; uint64_t v___y_784_; uint64_t v___y_785_; lean_object* v___y_786_; uint64_t v___y_787_; uint64_t v___y_788_; lean_object* v___y_793_; uint64_t v___y_794_; uint64_t v___y_795_; uint64_t v___y_796_; lean_object* v___y_797_; uint64_t v___y_798_; uint64_t v___y_799_; uint64_t v___y_804_; lean_object* v___y_805_; uint64_t v___y_806_; uint64_t v___y_807_; uint64_t v___y_808_; uint64_t v___y_809_; lean_object* v___y_810_; uint64_t v___y_811_; uint64_t v___y_812_; lean_object* v___y_817_; uint64_t v___y_818_; uint64_t v___y_819_; uint64_t v___y_820_; lean_object* v___y_821_; uint64_t v___y_822_; uint64_t v___y_823_; uint64_t v___y_828_; lean_object* v___y_829_; uint64_t v___y_830_; uint64_t v___y_831_; uint64_t v___y_832_; uint64_t v___y_833_; uint64_t v___y_834_; lean_object* v___y_835_; uint64_t v___y_836_; lean_object* v___y_841_; uint64_t v___y_842_; uint64_t v___y_843_; uint64_t v___y_844_; uint64_t v___y_845_; lean_object* v___y_846_; uint64_t v___y_847_; lean_object* v___y_852_; uint64_t v___y_853_; uint64_t v___y_854_; uint64_t v___y_855_; uint64_t v___y_856_; uint64_t v___y_857_; lean_object* v___y_858_; uint64_t v___y_859_; uint64_t v___y_860_; lean_object* v___y_865_; uint64_t v___y_866_; uint64_t v___y_867_; uint64_t v___y_868_; uint64_t v___y_869_; lean_object* v___y_870_; uint64_t v___y_871_; lean_object* v___y_876_; uint64_t v___y_877_; uint64_t v___y_878_; uint64_t v___y_879_; uint64_t v___y_880_; lean_object* v___y_881_; uint64_t v___y_882_; uint64_t v___y_887_; lean_object* v_fst_888_; lean_object* v_snd_889_; uint64_t v___y_904_; uint64_t v___y_905_; uint8_t v___y_906_; uint8_t v___y_907_; uint64_t v___y_908_; uint8_t v___y_909_; uint64_t v___y_921_; uint64_t v___y_922_; uint8_t v___y_923_; uint64_t v___y_924_; uint8_t v___y_925_; uint8_t v___y_926_; uint32_t v___y_931_; uint32_t v___y_932_; uint32_t v___y_933_; uint32_t v___y_941_; lean_object* v___y_942_; uint32_t v___y_943_; uint64_t v___y_948_; uint64_t v___y_949_; lean_object* v___y_950_; uint64_t v___y_951_; uint64_t v___y_961_; uint64_t v___y_962_; lean_object* v___y_963_; uint8_t v___y_964_; uint64_t v___y_965_; uint64_t v___y_973_; uint64_t v___y_974_; lean_object* v___y_975_; uint64_t v___y_976_; lean_object* v___y_982_; uint64_t v___y_983_; uint64_t v___y_984_; lean_object* v___y_985_; uint64_t v___y_986_; uint64_t v___y_987_; uint64_t v___y_1051_; lean_object* v___y_1052_; uint64_t v___y_1053_; lean_object* v___y_1054_; uint64_t v___y_1055_; uint64_t v___y_1056_; uint64_t v___y_1057_; uint64_t v___y_1063_; lean_object* v___y_1064_; uint64_t v___y_1065_; uint64_t v___y_1066_; lean_object* v___y_1067_; uint64_t v___y_1068_; uint64_t v___y_1069_; uint64_t v___y_1070_; uint64_t v___y_1071_; uint64_t v___y_1076_; lean_object* v___y_1077_; uint64_t v___y_1078_; uint64_t v___y_1079_; lean_object* v___y_1080_; uint64_t v___y_1081_; uint64_t v___y_1082_; lean_object* v___y_1087_; uint64_t v___y_1088_; uint64_t v___y_1089_; uint64_t v___y_1090_; uint64_t v___y_1091_; lean_object* v___y_1092_; uint64_t v___y_1093_; uint64_t v___y_1094_; uint64_t v___y_1095_; uint64_t v___y_1100_; lean_object* v___y_1101_; uint64_t v___y_1102_; uint64_t v___y_1103_; lean_object* v___y_1104_; uint64_t v___y_1105_; uint64_t v___y_1106_; lean_object* v___y_1111_; uint64_t v___y_1112_; uint64_t v___y_1113_; uint64_t v___y_1114_; uint64_t v___y_1115_; lean_object* v___y_1116_; uint64_t v___y_1117_; uint64_t v___y_1118_; uint64_t v___y_1119_; uint64_t v___y_1124_; lean_object* v___y_1125_; uint64_t v___y_1126_; uint64_t v___y_1127_; lean_object* v___y_1128_; uint64_t v___y_1129_; uint64_t v___y_1130_; lean_object* v___y_1135_; uint64_t v___y_1136_; uint64_t v___y_1137_; uint64_t v___y_1138_; uint64_t v___y_1139_; uint64_t v___y_1140_; lean_object* v___y_1141_; uint64_t v___y_1142_; uint64_t v___y_1143_; uint64_t v___y_1148_; lean_object* v___y_1149_; uint64_t v___y_1150_; uint64_t v___y_1151_; lean_object* v___y_1152_; uint64_t v___y_1153_; uint64_t v___y_1154_; lean_object* v___y_1159_; uint64_t v___y_1160_; uint64_t v___y_1161_; uint64_t v___y_1162_; lean_object* v___y_1163_; uint64_t v___y_1164_; uint64_t v___y_1165_; uint64_t v___y_1170_; lean_object* v_fst_1171_; lean_object* v_snd_1172_; uint64_t v___y_1187_; uint64_t v___y_1188_; uint8_t v___y_1189_; uint8_t v___y_1190_; uint64_t v___y_1191_; uint8_t v___y_1192_; uint64_t v___y_1204_; uint64_t v___y_1205_; uint8_t v___y_1206_; uint8_t v___y_1207_; uint64_t v___y_1208_; uint8_t v___y_1209_; uint64_t v___y_1214_; uint64_t v___y_1215_; uint64_t v___y_1216_; uint8_t v___y_1217_; uint8_t v___y_1218_; uint64_t v___y_1219_; uint32_t v_xExponent_1229_; uint32_t v___x_1230_; uint32_t v_yExponent_1231_; uint64_t v___y_1233_; uint64_t v___y_1234_; uint8_t v___y_1235_; uint8_t v___y_1236_; uint64_t v___y_1237_; uint64_t v___y_1244_; uint8_t v___y_1245_; uint8_t v___y_1246_; uint64_t v___y_1247_; uint8_t v___y_1254_; uint8_t v___y_1255_; uint64_t v___y_1256_; uint8_t v___y_1266_; uint8_t v___y_1267_; uint8_t v___y_1277_; uint32_t v___x_1284_; uint32_t v___x_1285_; uint32_t v___x_1286_; uint8_t v___x_1287_; 
v___x_644_ = 23;
v___x_645_ = lean_uint32_shift_right(v_xBits_588_, v___x_644_);
v___x_646_ = 255;
v_xExponent_1229_ = lean_uint32_land(v___x_645_, v___x_646_);
v___x_1230_ = lean_uint32_shift_right(v_yBits_589_, v___x_644_);
v_yExponent_1231_ = lean_uint32_land(v___x_1230_, v___x_646_);
v___x_1284_ = 2147483648;
v___x_1285_ = lean_uint32_land(v_xBits_588_, v___x_1284_);
v___x_1286_ = 0;
v___x_1287_ = lean_uint32_dec_eq(v___x_1285_, v___x_1286_);
if (v___x_1287_ == 0)
{
uint8_t v___x_1288_; 
v___x_1288_ = 1;
v___y_1277_ = v___x_1288_;
goto v___jp_1276_;
}
else
{
uint8_t v___x_1289_; 
v___x_1289_ = 0;
v___y_1277_ = v___x_1289_;
goto v___jp_1276_;
}
v___jp_590_:
{
uint32_t v___x_592_; uint32_t v___x_593_; 
v___x_592_ = 8388608;
v___x_593_ = lean_uint32_lor(v___y_591_, v___x_592_);
return v___x_593_;
}
v___jp_594_:
{
uint32_t v___x_596_; uint32_t v___x_597_; 
v___x_596_ = 8388608;
v___x_597_ = lean_uint32_lor(v___y_595_, v___x_596_);
return v___x_597_;
}
v___jp_598_:
{
uint32_t v___x_601_; uint32_t v___x_602_; uint32_t v___x_603_; 
v___x_601_ = 8388607;
v___x_602_ = lean_uint32_land(v___y_599_, v___x_601_);
v___x_603_ = lean_uint32_lor(v___y_600_, v___x_602_);
return v___x_603_;
}
v___jp_604_:
{
uint8_t v___x_608_; 
v___x_608_ = lean_uint64_dec_eq(v___y_607_, v___y_606_);
if (v___x_608_ == 0)
{
uint64_t v___x_609_; uint8_t v___x_610_; 
v___x_609_ = 8388608ULL;
v___x_610_ = lean_uint64_dec_eq(v___y_607_, v___x_609_);
if (v___x_610_ == 0)
{
uint32_t v___x_611_; uint8_t v___x_612_; 
v___x_611_ = lean_uint64_to_uint32(v___y_607_);
v___x_612_ = lean_unbox(v___y_605_);
lean_dec(v___y_605_);
if (v___x_612_ == 0)
{
uint32_t v___x_613_; 
v___x_613_ = 0;
v___y_599_ = v___x_611_;
v___y_600_ = v___x_613_;
goto v___jp_598_;
}
else
{
uint32_t v___x_614_; 
v___x_614_ = 2147483648;
v___y_599_ = v___x_611_;
v___y_600_ = v___x_614_;
goto v___jp_598_;
}
}
else
{
uint8_t v___x_615_; 
v___x_615_ = lean_unbox(v___y_605_);
lean_dec(v___y_605_);
if (v___x_615_ == 0)
{
uint32_t v___x_616_; 
v___x_616_ = 0;
v___y_595_ = v___x_616_;
goto v___jp_594_;
}
else
{
uint32_t v___x_617_; 
v___x_617_ = 2147483648;
v___y_595_ = v___x_617_;
goto v___jp_594_;
}
}
}
else
{
uint8_t v___x_618_; 
v___x_618_ = lean_unbox(v___y_605_);
lean_dec(v___y_605_);
if (v___x_618_ == 0)
{
uint32_t v___x_619_; 
v___x_619_ = 0;
return v___x_619_;
}
else
{
uint32_t v___x_620_; 
v___x_620_ = 2147483648;
return v___x_620_;
}
}
}
v___jp_621_:
{
uint32_t v___x_624_; uint32_t v___x_625_; uint32_t v___x_626_; 
v___x_624_ = 8388607;
v___x_625_ = lean_uint32_land(v___y_622_, v___x_624_);
v___x_626_ = lean_uint32_lor(v___y_623_, v___x_625_);
return v___x_626_;
}
v___jp_627_:
{
uint8_t v___x_631_; 
v___x_631_ = lean_uint64_dec_eq(v___y_630_, v___y_628_);
if (v___x_631_ == 0)
{
uint64_t v___x_632_; uint8_t v___x_633_; 
v___x_632_ = 8388608ULL;
v___x_633_ = lean_uint64_dec_eq(v___y_630_, v___x_632_);
if (v___x_633_ == 0)
{
uint32_t v___x_634_; uint8_t v___x_635_; 
v___x_634_ = lean_uint64_to_uint32(v___y_630_);
v___x_635_ = lean_unbox(v___y_629_);
lean_dec(v___y_629_);
if (v___x_635_ == 0)
{
uint32_t v___x_636_; 
v___x_636_ = 0;
v___y_622_ = v___x_634_;
v___y_623_ = v___x_636_;
goto v___jp_621_;
}
else
{
uint32_t v___x_637_; 
v___x_637_ = 2147483648;
v___y_622_ = v___x_634_;
v___y_623_ = v___x_637_;
goto v___jp_621_;
}
}
else
{
uint8_t v___x_638_; 
v___x_638_ = lean_unbox(v___y_629_);
lean_dec(v___y_629_);
if (v___x_638_ == 0)
{
uint32_t v___x_639_; 
v___x_639_ = 0;
v___y_591_ = v___x_639_;
goto v___jp_590_;
}
else
{
uint32_t v___x_640_; 
v___x_640_ = 2147483648;
v___y_591_ = v___x_640_;
goto v___jp_590_;
}
}
}
else
{
uint8_t v___x_641_; 
v___x_641_ = lean_unbox(v___y_629_);
lean_dec(v___y_629_);
if (v___x_641_ == 0)
{
uint32_t v___x_642_; 
v___x_642_ = 0;
return v___x_642_;
}
else
{
uint32_t v___x_643_; 
v___x_643_ = 2147483648;
return v___x_643_;
}
}
}
v___jp_647_:
{
uint32_t v___x_651_; uint32_t v___x_652_; uint32_t v___x_653_; uint32_t v___x_654_; uint32_t v___x_655_; uint32_t v___x_656_; 
v___x_651_ = lean_uint32_land(v___y_649_, v___x_646_);
v___x_652_ = lean_uint32_shift_left(v___x_651_, v___x_644_);
v___x_653_ = lean_uint32_lor(v___y_650_, v___x_652_);
v___x_654_ = 8388607;
v___x_655_ = lean_uint32_land(v___y_648_, v___x_654_);
v___x_656_ = lean_uint32_lor(v___x_653_, v___x_655_);
return v___x_656_;
}
v___jp_657_:
{
uint8_t v___x_661_; 
v___x_661_ = lean_unbox(v___y_658_);
lean_dec(v___y_658_);
if (v___x_661_ == 0)
{
uint32_t v___x_662_; 
v___x_662_ = 0;
v___y_648_ = v___y_660_;
v___y_649_ = v___y_659_;
v___y_650_ = v___x_662_;
goto v___jp_647_;
}
else
{
uint32_t v___x_663_; 
v___x_663_ = 2147483648;
v___y_648_ = v___y_660_;
v___y_649_ = v___y_659_;
v___y_650_ = v___x_663_;
goto v___jp_647_;
}
}
v___jp_664_:
{
uint64_t v___x_669_; uint64_t v_encodedExponent_670_; uint32_t v___x_671_; uint64_t v___x_672_; uint8_t v___x_673_; 
v___x_669_ = 171ULL;
v_encodedExponent_670_ = lean_uint64_sub(v___y_667_, v___x_669_);
v___x_671_ = lean_uint64_to_uint32(v_encodedExponent_670_);
v___x_672_ = 8388608ULL;
v___x_673_ = lean_uint64_dec_lt(v___y_668_, v___x_672_);
if (v___x_673_ == 0)
{
uint64_t v___x_674_; uint32_t v___x_675_; 
v___x_674_ = lean_uint64_sub(v___y_668_, v___x_672_);
v___x_675_ = lean_uint64_to_uint32(v___x_674_);
v___y_658_ = v___y_665_;
v___y_659_ = v___x_671_;
v___y_660_ = v___x_675_;
goto v___jp_657_;
}
else
{
uint32_t v___x_676_; 
v___x_676_ = lean_uint64_to_uint32(v___y_666_);
v___y_658_ = v___y_665_;
v___y_659_ = v___x_671_;
v___y_660_ = v___x_676_;
goto v___jp_657_;
}
}
v___jp_677_:
{
uint64_t v___x_683_; uint8_t v___x_684_; 
v___x_683_ = 425ULL;
v___x_684_ = lean_uint64_dec_lt(v___x_683_, v___y_682_);
if (v___x_684_ == 0)
{
if (v___y_681_ == 0)
{
v___y_665_ = v___y_678_;
v___y_666_ = v___y_680_;
v___y_667_ = v___y_682_;
v___y_668_ = v___y_679_;
goto v___jp_664_;
}
else
{
uint64_t v___x_685_; 
v___x_685_ = 8388608ULL;
v___y_665_ = v___y_678_;
v___y_666_ = v___y_680_;
v___y_667_ = v___y_682_;
v___y_668_ = v___x_685_;
goto v___jp_664_;
}
}
else
{
uint8_t v___x_686_; 
v___x_686_ = lean_unbox(v___y_678_);
lean_dec(v___y_678_);
if (v___x_686_ == 0)
{
uint32_t v___x_687_; 
v___x_687_ = 2139095040;
return v___x_687_;
}
else
{
uint32_t v___x_688_; 
v___x_688_ = 4286578688;
return v___x_688_;
}
}
}
v___jp_689_:
{
uint64_t v___x_694_; uint8_t v_carry_695_; 
v___x_694_ = 16777216ULL;
v_carry_695_ = lean_uint64_dec_eq(v___y_693_, v___x_694_);
if (v_carry_695_ == 0)
{
v___y_678_ = v___y_690_;
v___y_679_ = v___y_693_;
v___y_680_ = v___y_692_;
v___y_681_ = v_carry_695_;
v___y_682_ = v___y_691_;
goto v___jp_677_;
}
else
{
uint64_t v___x_696_; uint64_t v___x_697_; 
v___x_696_ = 1ULL;
v___x_697_ = lean_uint64_add(v___y_691_, v___x_696_);
v___y_678_ = v___y_690_;
v___y_679_ = v___y_693_;
v___y_680_ = v___y_692_;
v___y_681_ = v_carry_695_;
v___y_682_ = v___x_697_;
goto v___jp_677_;
}
}
v___jp_698_:
{
uint64_t v_position_705_; uint64_t v___x_706_; uint8_t v___x_707_; 
v_position_705_ = lean_uint64_add(v___y_704_, v___y_700_);
v___x_706_ = 172ULL;
v___x_707_ = lean_uint64_dec_lt(v_position_705_, v___x_706_);
if (v___x_707_ == 0)
{
uint64_t v___x_708_; uint8_t v___x_709_; 
v___x_708_ = 23ULL;
v___x_709_ = lean_uint64_dec_lt(v___y_704_, v___x_708_);
if (v___x_709_ == 0)
{
uint64_t v___x_710_; uint8_t v___x_711_; 
v___x_710_ = lean_uint64_sub(v___y_704_, v___x_708_);
v___x_711_ = lean_uint64_dec_eq(v___x_710_, v___y_702_);
if (v___x_711_ == 0)
{
uint64_t v___x_712_; uint8_t v___x_713_; 
v___x_712_ = 64ULL;
v___x_713_ = lean_uint64_dec_lt(v___x_710_, v___x_712_);
if (v___x_713_ == 0)
{
uint8_t v___x_714_; 
v___x_714_ = lean_uint64_dec_eq(v___x_710_, v___x_712_);
if (v___x_714_ == 0)
{
lean_dec(v___y_703_);
v___y_690_ = v___y_699_;
v___y_691_ = v_position_705_;
v___y_692_ = v___y_702_;
v___y_693_ = v___y_702_;
goto v___jp_689_;
}
else
{
uint64_t v___x_715_; uint64_t v___x_716_; uint8_t v___x_717_; 
v___x_715_ = 9223372036854775808ULL;
v___x_716_ = lean_unbox_uint64(v___y_703_);
lean_dec(v___y_703_);
v___x_717_ = lean_uint64_dec_lt(v___x_715_, v___x_716_);
if (v___x_717_ == 0)
{
v___y_690_ = v___y_699_;
v___y_691_ = v_position_705_;
v___y_692_ = v___y_702_;
v___y_693_ = v___y_702_;
goto v___jp_689_;
}
else
{
uint64_t v___x_718_; 
v___x_718_ = 1ULL;
v___y_690_ = v___y_699_;
v___y_691_ = v_position_705_;
v___y_692_ = v___y_702_;
v___y_693_ = v___x_718_;
goto v___jp_689_;
}
}
}
else
{
uint64_t v___x_719_; uint64_t v_quotient_720_; uint64_t v___x_721_; uint64_t v___x_722_; uint64_t v___x_723_; uint64_t v___x_724_; uint64_t v_remainder_725_; uint64_t v___x_726_; uint64_t v_half_727_; uint8_t v___x_728_; 
v___x_719_ = lean_unbox_uint64(v___y_703_);
v_quotient_720_ = lean_uint64_shift_right(v___x_719_, v___x_710_);
v___x_721_ = 1ULL;
v___x_722_ = lean_uint64_shift_left(v___x_721_, v___x_710_);
v___x_723_ = lean_uint64_sub(v___x_722_, v___x_721_);
v___x_724_ = lean_unbox_uint64(v___y_703_);
lean_dec(v___y_703_);
v_remainder_725_ = lean_uint64_land(v___x_724_, v___x_723_);
v___x_726_ = lean_uint64_sub(v___x_710_, v___x_721_);
v_half_727_ = lean_uint64_shift_left(v___x_721_, v___x_726_);
v___x_728_ = lean_uint64_dec_lt(v_remainder_725_, v_half_727_);
if (v___x_728_ == 0)
{
uint8_t v___x_729_; 
v___x_729_ = lean_uint64_dec_lt(v_half_727_, v_remainder_725_);
if (v___x_729_ == 0)
{
uint64_t v___x_730_; uint8_t v___x_731_; 
v___x_730_ = lean_uint64_land(v_quotient_720_, v___x_721_);
v___x_731_ = lean_uint64_dec_eq(v___x_730_, v___y_702_);
if (v___x_731_ == 0)
{
uint64_t v___x_732_; 
v___x_732_ = lean_uint64_add(v_quotient_720_, v___x_721_);
v___y_690_ = v___y_699_;
v___y_691_ = v_position_705_;
v___y_692_ = v___y_702_;
v___y_693_ = v___x_732_;
goto v___jp_689_;
}
else
{
v___y_690_ = v___y_699_;
v___y_691_ = v_position_705_;
v___y_692_ = v___y_702_;
v___y_693_ = v_quotient_720_;
goto v___jp_689_;
}
}
else
{
uint64_t v___x_733_; 
v___x_733_ = lean_uint64_add(v_quotient_720_, v___x_721_);
v___y_690_ = v___y_699_;
v___y_691_ = v_position_705_;
v___y_692_ = v___y_702_;
v___y_693_ = v___x_733_;
goto v___jp_689_;
}
}
else
{
v___y_690_ = v___y_699_;
v___y_691_ = v_position_705_;
v___y_692_ = v___y_702_;
v___y_693_ = v_quotient_720_;
goto v___jp_689_;
}
}
}
else
{
uint64_t v___x_734_; 
v___x_734_ = lean_unbox_uint64(v___y_703_);
lean_dec(v___y_703_);
v___y_690_ = v___y_699_;
v___y_691_ = v_position_705_;
v___y_692_ = v___y_702_;
v___y_693_ = v___x_734_;
goto v___jp_689_;
}
}
else
{
uint64_t v___x_735_; uint64_t v___x_736_; uint64_t v___x_737_; 
v___x_735_ = lean_uint64_sub(v___x_708_, v___y_704_);
v___x_736_ = lean_unbox_uint64(v___y_703_);
lean_dec(v___y_703_);
v___x_737_ = lean_uint64_shift_left(v___x_736_, v___x_735_);
v___y_690_ = v___y_699_;
v___y_691_ = v_position_705_;
v___y_692_ = v___y_702_;
v___y_693_ = v___x_737_;
goto v___jp_689_;
}
}
else
{
uint8_t v___x_738_; 
v___x_738_ = lean_uint64_dec_lt(v___y_700_, v___y_701_);
if (v___x_738_ == 0)
{
uint64_t v___x_739_; uint64_t v___x_740_; uint64_t v___x_741_; 
v___x_739_ = lean_uint64_sub(v___y_700_, v___y_701_);
v___x_740_ = lean_unbox_uint64(v___y_703_);
lean_dec(v___y_703_);
v___x_741_ = lean_uint64_shift_left(v___x_740_, v___x_739_);
v___y_605_ = v___y_699_;
v___y_606_ = v___y_702_;
v___y_607_ = v___x_741_;
goto v___jp_604_;
}
else
{
uint64_t v___x_742_; uint8_t v___x_743_; 
v___x_742_ = lean_uint64_sub(v___y_701_, v___y_700_);
v___x_743_ = lean_uint64_dec_eq(v___x_742_, v___y_702_);
if (v___x_743_ == 0)
{
uint64_t v___x_744_; uint8_t v___x_745_; 
v___x_744_ = 64ULL;
v___x_745_ = lean_uint64_dec_lt(v___x_742_, v___x_744_);
if (v___x_745_ == 0)
{
uint8_t v___x_746_; 
v___x_746_ = lean_uint64_dec_eq(v___x_742_, v___x_744_);
if (v___x_746_ == 0)
{
lean_dec(v___y_703_);
v___y_605_ = v___y_699_;
v___y_606_ = v___y_702_;
v___y_607_ = v___y_702_;
goto v___jp_604_;
}
else
{
uint64_t v___x_747_; uint64_t v___x_748_; uint8_t v___x_749_; 
v___x_747_ = 9223372036854775808ULL;
v___x_748_ = lean_unbox_uint64(v___y_703_);
lean_dec(v___y_703_);
v___x_749_ = lean_uint64_dec_lt(v___x_747_, v___x_748_);
if (v___x_749_ == 0)
{
v___y_605_ = v___y_699_;
v___y_606_ = v___y_702_;
v___y_607_ = v___y_702_;
goto v___jp_604_;
}
else
{
uint64_t v___x_750_; 
v___x_750_ = 1ULL;
v___y_605_ = v___y_699_;
v___y_606_ = v___y_702_;
v___y_607_ = v___x_750_;
goto v___jp_604_;
}
}
}
else
{
uint64_t v___x_751_; uint64_t v_quotient_752_; uint64_t v___x_753_; uint64_t v___x_754_; uint64_t v___x_755_; uint64_t v___x_756_; uint64_t v_remainder_757_; uint64_t v___x_758_; uint64_t v_half_759_; uint8_t v___x_760_; 
v___x_751_ = lean_unbox_uint64(v___y_703_);
v_quotient_752_ = lean_uint64_shift_right(v___x_751_, v___x_742_);
v___x_753_ = 1ULL;
v___x_754_ = lean_uint64_shift_left(v___x_753_, v___x_742_);
v___x_755_ = lean_uint64_sub(v___x_754_, v___x_753_);
v___x_756_ = lean_unbox_uint64(v___y_703_);
lean_dec(v___y_703_);
v_remainder_757_ = lean_uint64_land(v___x_756_, v___x_755_);
v___x_758_ = lean_uint64_sub(v___x_742_, v___x_753_);
v_half_759_ = lean_uint64_shift_left(v___x_753_, v___x_758_);
v___x_760_ = lean_uint64_dec_lt(v_remainder_757_, v_half_759_);
if (v___x_760_ == 0)
{
uint8_t v___x_761_; 
v___x_761_ = lean_uint64_dec_lt(v_half_759_, v_remainder_757_);
if (v___x_761_ == 0)
{
uint64_t v___x_762_; uint8_t v___x_763_; 
v___x_762_ = lean_uint64_land(v_quotient_752_, v___x_753_);
v___x_763_ = lean_uint64_dec_eq(v___x_762_, v___y_702_);
if (v___x_763_ == 0)
{
uint64_t v___x_764_; 
v___x_764_ = lean_uint64_add(v_quotient_752_, v___x_753_);
v___y_605_ = v___y_699_;
v___y_606_ = v___y_702_;
v___y_607_ = v___x_764_;
goto v___jp_604_;
}
else
{
v___y_605_ = v___y_699_;
v___y_606_ = v___y_702_;
v___y_607_ = v_quotient_752_;
goto v___jp_604_;
}
}
else
{
uint64_t v___x_765_; 
v___x_765_ = lean_uint64_add(v_quotient_752_, v___x_753_);
v___y_605_ = v___y_699_;
v___y_606_ = v___y_702_;
v___y_607_ = v___x_765_;
goto v___jp_604_;
}
}
else
{
v___y_605_ = v___y_699_;
v___y_606_ = v___y_702_;
v___y_607_ = v_quotient_752_;
goto v___jp_604_;
}
}
}
else
{
uint64_t v___x_766_; 
v___x_766_ = lean_unbox_uint64(v___y_703_);
lean_dec(v___y_703_);
v___y_605_ = v___y_699_;
v___y_606_ = v___y_702_;
v___y_607_ = v___x_766_;
goto v___jp_604_;
}
}
}
}
v___jp_767_:
{
uint64_t v___x_775_; uint64_t v___x_776_; uint8_t v___x_777_; 
v___x_775_ = 1ULL;
v___x_776_ = lean_uint64_shift_right(v___y_769_, v___x_775_);
v___x_777_ = lean_uint64_dec_eq(v___x_776_, v___y_772_);
if (v___x_777_ == 0)
{
uint64_t v___x_778_; 
v___x_778_ = lean_uint64_add(v___y_774_, v___x_775_);
v___y_699_ = v___y_768_;
v___y_700_ = v___y_770_;
v___y_701_ = v___y_771_;
v___y_702_ = v___y_772_;
v___y_703_ = v___y_773_;
v___y_704_ = v___x_778_;
goto v___jp_698_;
}
else
{
v___y_699_ = v___y_768_;
v___y_700_ = v___y_770_;
v___y_701_ = v___y_771_;
v___y_702_ = v___y_772_;
v___y_703_ = v___y_773_;
v___y_704_ = v___y_774_;
goto v___jp_698_;
}
}
v___jp_779_:
{
uint64_t v___x_789_; uint8_t v___x_790_; 
v___x_789_ = lean_uint64_shift_right(v___y_785_, v___y_787_);
v___x_790_ = lean_uint64_dec_eq(v___x_789_, v___y_784_);
if (v___x_790_ == 0)
{
uint64_t v___x_791_; 
v___x_791_ = lean_uint64_add(v___y_781_, v___y_787_);
v___y_768_ = v___y_780_;
v___y_769_ = v___y_788_;
v___y_770_ = v___y_782_;
v___y_771_ = v___y_783_;
v___y_772_ = v___y_784_;
v___y_773_ = v___y_786_;
v___y_774_ = v___x_791_;
goto v___jp_767_;
}
else
{
v___y_768_ = v___y_780_;
v___y_769_ = v___y_788_;
v___y_770_ = v___y_782_;
v___y_771_ = v___y_783_;
v___y_772_ = v___y_784_;
v___y_773_ = v___y_786_;
v___y_774_ = v___y_781_;
goto v___jp_767_;
}
}
v___jp_792_:
{
uint64_t v___x_800_; uint64_t v___x_801_; uint8_t v___x_802_; 
v___x_800_ = 2ULL;
v___x_801_ = lean_uint64_shift_right(v___y_798_, v___x_800_);
v___x_802_ = lean_uint64_dec_eq(v___x_801_, v___y_796_);
if (v___x_802_ == 0)
{
v___y_780_ = v___y_793_;
v___y_781_ = v___y_799_;
v___y_782_ = v___y_794_;
v___y_783_ = v___y_795_;
v___y_784_ = v___y_796_;
v___y_785_ = v___y_798_;
v___y_786_ = v___y_797_;
v___y_787_ = v___x_800_;
v___y_788_ = v___x_801_;
goto v___jp_779_;
}
else
{
v___y_780_ = v___y_793_;
v___y_781_ = v___y_799_;
v___y_782_ = v___y_794_;
v___y_783_ = v___y_795_;
v___y_784_ = v___y_796_;
v___y_785_ = v___y_798_;
v___y_786_ = v___y_797_;
v___y_787_ = v___x_800_;
v___y_788_ = v___y_798_;
goto v___jp_779_;
}
}
v___jp_803_:
{
uint64_t v___x_813_; uint8_t v___x_814_; 
v___x_813_ = lean_uint64_shift_right(v___y_811_, v___y_804_);
v___x_814_ = lean_uint64_dec_eq(v___x_813_, v___y_808_);
if (v___x_814_ == 0)
{
uint64_t v___x_815_; 
v___x_815_ = lean_uint64_add(v___y_809_, v___y_804_);
v___y_793_ = v___y_805_;
v___y_794_ = v___y_806_;
v___y_795_ = v___y_807_;
v___y_796_ = v___y_808_;
v___y_797_ = v___y_810_;
v___y_798_ = v___y_812_;
v___y_799_ = v___x_815_;
goto v___jp_792_;
}
else
{
v___y_793_ = v___y_805_;
v___y_794_ = v___y_806_;
v___y_795_ = v___y_807_;
v___y_796_ = v___y_808_;
v___y_797_ = v___y_810_;
v___y_798_ = v___y_812_;
v___y_799_ = v___y_809_;
goto v___jp_792_;
}
}
v___jp_816_:
{
uint64_t v___x_824_; uint64_t v___x_825_; uint8_t v___x_826_; 
v___x_824_ = 4ULL;
v___x_825_ = lean_uint64_shift_right(v___y_822_, v___x_824_);
v___x_826_ = lean_uint64_dec_eq(v___x_825_, v___y_820_);
if (v___x_826_ == 0)
{
v___y_804_ = v___x_824_;
v___y_805_ = v___y_817_;
v___y_806_ = v___y_818_;
v___y_807_ = v___y_819_;
v___y_808_ = v___y_820_;
v___y_809_ = v___y_823_;
v___y_810_ = v___y_821_;
v___y_811_ = v___y_822_;
v___y_812_ = v___x_825_;
goto v___jp_803_;
}
else
{
v___y_804_ = v___x_824_;
v___y_805_ = v___y_817_;
v___y_806_ = v___y_818_;
v___y_807_ = v___y_819_;
v___y_808_ = v___y_820_;
v___y_809_ = v___y_823_;
v___y_810_ = v___y_821_;
v___y_811_ = v___y_822_;
v___y_812_ = v___y_822_;
goto v___jp_803_;
}
}
v___jp_827_:
{
uint64_t v___x_837_; uint8_t v___x_838_; 
v___x_837_ = lean_uint64_shift_right(v___y_831_, v___y_828_);
v___x_838_ = lean_uint64_dec_eq(v___x_837_, v___y_834_);
if (v___x_838_ == 0)
{
uint64_t v___x_839_; 
v___x_839_ = lean_uint64_add(v___y_832_, v___y_828_);
v___y_817_ = v___y_829_;
v___y_818_ = v___y_830_;
v___y_819_ = v___y_833_;
v___y_820_ = v___y_834_;
v___y_821_ = v___y_835_;
v___y_822_ = v___y_836_;
v___y_823_ = v___x_839_;
goto v___jp_816_;
}
else
{
v___y_817_ = v___y_829_;
v___y_818_ = v___y_830_;
v___y_819_ = v___y_833_;
v___y_820_ = v___y_834_;
v___y_821_ = v___y_835_;
v___y_822_ = v___y_836_;
v___y_823_ = v___y_832_;
goto v___jp_816_;
}
}
v___jp_840_:
{
uint64_t v___x_848_; uint64_t v___x_849_; uint8_t v___x_850_; 
v___x_848_ = 8ULL;
v___x_849_ = lean_uint64_shift_right(v___y_843_, v___x_848_);
v___x_850_ = lean_uint64_dec_eq(v___x_849_, v___y_845_);
if (v___x_850_ == 0)
{
v___y_828_ = v___x_848_;
v___y_829_ = v___y_841_;
v___y_830_ = v___y_842_;
v___y_831_ = v___y_843_;
v___y_832_ = v___y_847_;
v___y_833_ = v___y_844_;
v___y_834_ = v___y_845_;
v___y_835_ = v___y_846_;
v___y_836_ = v___x_849_;
goto v___jp_827_;
}
else
{
v___y_828_ = v___x_848_;
v___y_829_ = v___y_841_;
v___y_830_ = v___y_842_;
v___y_831_ = v___y_843_;
v___y_832_ = v___y_847_;
v___y_833_ = v___y_844_;
v___y_834_ = v___y_845_;
v___y_835_ = v___y_846_;
v___y_836_ = v___y_843_;
goto v___jp_827_;
}
}
v___jp_851_:
{
uint64_t v___x_861_; uint8_t v___x_862_; 
v___x_861_ = lean_uint64_shift_right(v___y_855_, v___y_859_);
v___x_862_ = lean_uint64_dec_eq(v___x_861_, v___y_856_);
if (v___x_862_ == 0)
{
uint64_t v___x_863_; 
v___x_863_ = lean_uint64_add(v___y_857_, v___y_859_);
v___y_841_ = v___y_852_;
v___y_842_ = v___y_853_;
v___y_843_ = v___y_860_;
v___y_844_ = v___y_854_;
v___y_845_ = v___y_856_;
v___y_846_ = v___y_858_;
v___y_847_ = v___x_863_;
goto v___jp_840_;
}
else
{
v___y_841_ = v___y_852_;
v___y_842_ = v___y_853_;
v___y_843_ = v___y_860_;
v___y_844_ = v___y_854_;
v___y_845_ = v___y_856_;
v___y_846_ = v___y_858_;
v___y_847_ = v___y_857_;
goto v___jp_840_;
}
}
v___jp_864_:
{
uint64_t v___x_872_; uint64_t v___x_873_; uint8_t v___x_874_; 
v___x_872_ = 16ULL;
v___x_873_ = lean_uint64_shift_right(v___y_868_, v___x_872_);
v___x_874_ = lean_uint64_dec_eq(v___x_873_, v___y_869_);
if (v___x_874_ == 0)
{
v___y_852_ = v___y_865_;
v___y_853_ = v___y_866_;
v___y_854_ = v___y_867_;
v___y_855_ = v___y_868_;
v___y_856_ = v___y_869_;
v___y_857_ = v___y_871_;
v___y_858_ = v___y_870_;
v___y_859_ = v___x_872_;
v___y_860_ = v___x_873_;
goto v___jp_851_;
}
else
{
v___y_852_ = v___y_865_;
v___y_853_ = v___y_866_;
v___y_854_ = v___y_867_;
v___y_855_ = v___y_868_;
v___y_856_ = v___y_869_;
v___y_857_ = v___y_871_;
v___y_858_ = v___y_870_;
v___y_859_ = v___x_872_;
v___y_860_ = v___y_868_;
goto v___jp_851_;
}
}
v___jp_875_:
{
uint64_t v___x_883_; uint64_t v___x_884_; uint8_t v___x_885_; 
v___x_883_ = lean_unbox_uint64(v___y_881_);
v___x_884_ = lean_uint64_shift_right(v___x_883_, v___y_879_);
v___x_885_ = lean_uint64_dec_eq(v___x_884_, v___y_880_);
if (v___x_885_ == 0)
{
v___y_865_ = v___y_876_;
v___y_866_ = v___y_877_;
v___y_867_ = v___y_878_;
v___y_868_ = v___y_882_;
v___y_869_ = v___y_880_;
v___y_870_ = v___y_881_;
v___y_871_ = v___y_879_;
goto v___jp_864_;
}
else
{
v___y_865_ = v___y_876_;
v___y_866_ = v___y_877_;
v___y_867_ = v___y_878_;
v___y_868_ = v___y_882_;
v___y_869_ = v___y_880_;
v___y_870_ = v___y_881_;
v___y_871_ = v___y_880_;
goto v___jp_864_;
}
}
v___jp_886_:
{
uint64_t v___x_890_; uint64_t v___x_891_; uint8_t v___x_892_; 
v___x_890_ = 0ULL;
v___x_891_ = lean_unbox_uint64(v_snd_889_);
v___x_892_ = lean_uint64_dec_eq(v___x_891_, v___x_890_);
if (v___x_892_ == 0)
{
uint64_t v___x_893_; uint64_t v___x_894_; uint64_t v___x_895_; uint64_t v___x_896_; uint64_t v___x_897_; uint8_t v___x_898_; 
v___x_893_ = 149ULL;
v___x_894_ = lean_uint64_add(v___y_887_, v___x_893_);
v___x_895_ = 32ULL;
v___x_896_ = lean_unbox_uint64(v_snd_889_);
v___x_897_ = lean_uint64_shift_right(v___x_896_, v___x_895_);
v___x_898_ = lean_uint64_dec_eq(v___x_897_, v___x_890_);
if (v___x_898_ == 0)
{
v___y_876_ = v_fst_888_;
v___y_877_ = v___x_894_;
v___y_878_ = v___x_893_;
v___y_879_ = v___x_895_;
v___y_880_ = v___x_890_;
v___y_881_ = v_snd_889_;
v___y_882_ = v___x_897_;
goto v___jp_875_;
}
else
{
uint64_t v___x_899_; 
v___x_899_ = lean_unbox_uint64(v_snd_889_);
v___y_876_ = v_fst_888_;
v___y_877_ = v___x_894_;
v___y_878_ = v___x_893_;
v___y_879_ = v___x_895_;
v___y_880_ = v___x_890_;
v___y_881_ = v_snd_889_;
v___y_882_ = v___x_899_;
goto v___jp_875_;
}
}
else
{
uint8_t v___x_900_; 
lean_dec(v_snd_889_);
v___x_900_ = lean_unbox(v_fst_888_);
lean_dec(v_fst_888_);
if (v___x_900_ == 0)
{
uint32_t v___x_901_; 
v___x_901_ = 0;
return v___x_901_;
}
else
{
uint32_t v___x_902_; 
v___x_902_ = 2147483648;
return v___x_902_;
}
}
}
v___jp_903_:
{
uint8_t v___x_910_; 
v___x_910_ = lean_uint64_dec_eq(v___y_904_, v___y_908_);
if (v___x_910_ == 0)
{
uint8_t v___x_911_; 
v___x_911_ = lean_uint64_dec_lt(v___y_904_, v___y_908_);
if (v___x_911_ == 0)
{
uint64_t v___x_912_; lean_object* v___x_913_; lean_object* v___x_914_; 
v___x_912_ = lean_uint64_sub(v___y_904_, v___y_908_);
v___x_913_ = lean_box(v___y_907_);
v___x_914_ = lean_box_uint64(v___x_912_);
v___y_887_ = v___y_905_;
v_fst_888_ = v___x_913_;
v_snd_889_ = v___x_914_;
goto v___jp_886_;
}
else
{
uint64_t v___x_915_; lean_object* v___x_916_; lean_object* v___x_917_; 
v___x_915_ = lean_uint64_sub(v___y_908_, v___y_904_);
v___x_916_ = lean_box(v___y_906_);
v___x_917_ = lean_box_uint64(v___x_915_);
v___y_887_ = v___y_905_;
v_fst_888_ = v___x_916_;
v_snd_889_ = v___x_917_;
goto v___jp_886_;
}
}
else
{
lean_object* v___x_918_; lean_object* v___x_919_; 
v___x_918_ = lean_box(v___y_909_);
v___x_919_ = ((lean_object*)(lp_competition_Submission_TunedAdd_core___boxed__const__1));
v___y_887_ = v___y_905_;
v_fst_888_ = v___x_918_;
v_snd_889_ = v___x_919_;
goto v___jp_886_;
}
}
v___jp_920_:
{
if (v___y_926_ == 0)
{
v___y_904_ = v___y_921_;
v___y_905_ = v___y_922_;
v___y_906_ = v___y_923_;
v___y_907_ = v___y_925_;
v___y_908_ = v___y_924_;
v___y_909_ = v___y_926_;
goto v___jp_903_;
}
else
{
uint64_t v___x_927_; lean_object* v___x_928_; lean_object* v___x_929_; 
v___x_927_ = lean_uint64_add(v___y_921_, v___y_924_);
v___x_928_ = lean_box(v___y_925_);
v___x_929_ = lean_box_uint64(v___x_927_);
v___y_887_ = v___y_922_;
v_fst_888_ = v___x_928_;
v_snd_889_ = v___x_929_;
goto v___jp_886_;
}
}
v___jp_930_:
{
uint32_t v___x_934_; uint32_t v___x_935_; uint32_t v___x_936_; uint32_t v___x_937_; uint32_t v___x_938_; uint32_t v___x_939_; 
v___x_934_ = lean_uint32_land(v___y_931_, v___x_646_);
v___x_935_ = lean_uint32_shift_left(v___x_934_, v___x_644_);
v___x_936_ = lean_uint32_lor(v___y_933_, v___x_935_);
v___x_937_ = 8388607;
v___x_938_ = lean_uint32_land(v___y_932_, v___x_937_);
v___x_939_ = lean_uint32_lor(v___x_936_, v___x_938_);
return v___x_939_;
}
v___jp_940_:
{
uint8_t v___x_944_; 
v___x_944_ = lean_unbox(v___y_942_);
lean_dec(v___y_942_);
if (v___x_944_ == 0)
{
uint32_t v___x_945_; 
v___x_945_ = 0;
v___y_931_ = v___y_941_;
v___y_932_ = v___y_943_;
v___y_933_ = v___x_945_;
goto v___jp_930_;
}
else
{
uint32_t v___x_946_; 
v___x_946_ = 2147483648;
v___y_931_ = v___y_941_;
v___y_932_ = v___y_943_;
v___y_933_ = v___x_946_;
goto v___jp_930_;
}
}
v___jp_947_:
{
uint64_t v___x_952_; uint64_t v_encodedExponent_953_; uint32_t v___x_954_; uint64_t v___x_955_; uint8_t v___x_956_; 
v___x_952_ = 171ULL;
v_encodedExponent_953_ = lean_uint64_sub(v___y_948_, v___x_952_);
v___x_954_ = lean_uint64_to_uint32(v_encodedExponent_953_);
v___x_955_ = 8388608ULL;
v___x_956_ = lean_uint64_dec_lt(v___y_951_, v___x_955_);
if (v___x_956_ == 0)
{
uint64_t v___x_957_; uint32_t v___x_958_; 
v___x_957_ = lean_uint64_sub(v___y_951_, v___x_955_);
v___x_958_ = lean_uint64_to_uint32(v___x_957_);
v___y_941_ = v___x_954_;
v___y_942_ = v___y_950_;
v___y_943_ = v___x_958_;
goto v___jp_940_;
}
else
{
uint32_t v___x_959_; 
v___x_959_ = lean_uint64_to_uint32(v___y_949_);
v___y_941_ = v___x_954_;
v___y_942_ = v___y_950_;
v___y_943_ = v___x_959_;
goto v___jp_940_;
}
}
v___jp_960_:
{
uint64_t v___x_966_; uint8_t v___x_967_; 
v___x_966_ = 425ULL;
v___x_967_ = lean_uint64_dec_lt(v___x_966_, v___y_965_);
if (v___x_967_ == 0)
{
if (v___y_964_ == 0)
{
v___y_948_ = v___y_965_;
v___y_949_ = v___y_962_;
v___y_950_ = v___y_963_;
v___y_951_ = v___y_961_;
goto v___jp_947_;
}
else
{
uint64_t v___x_968_; 
v___x_968_ = 8388608ULL;
v___y_948_ = v___y_965_;
v___y_949_ = v___y_962_;
v___y_950_ = v___y_963_;
v___y_951_ = v___x_968_;
goto v___jp_947_;
}
}
else
{
uint8_t v___x_969_; 
v___x_969_ = lean_unbox(v___y_963_);
lean_dec(v___y_963_);
if (v___x_969_ == 0)
{
uint32_t v___x_970_; 
v___x_970_ = 2139095040;
return v___x_970_;
}
else
{
uint32_t v___x_971_; 
v___x_971_ = 4286578688;
return v___x_971_;
}
}
}
v___jp_972_:
{
uint64_t v___x_977_; uint8_t v_carry_978_; 
v___x_977_ = 16777216ULL;
v_carry_978_ = lean_uint64_dec_eq(v___y_976_, v___x_977_);
if (v_carry_978_ == 0)
{
v___y_961_ = v___y_976_;
v___y_962_ = v___y_974_;
v___y_963_ = v___y_975_;
v___y_964_ = v_carry_978_;
v___y_965_ = v___y_973_;
goto v___jp_960_;
}
else
{
uint64_t v___x_979_; uint64_t v___x_980_; 
v___x_979_ = 1ULL;
v___x_980_ = lean_uint64_add(v___y_973_, v___x_979_);
v___y_961_ = v___y_976_;
v___y_962_ = v___y_974_;
v___y_963_ = v___y_975_;
v___y_964_ = v_carry_978_;
v___y_965_ = v___x_980_;
goto v___jp_960_;
}
}
v___jp_981_:
{
uint64_t v_position_988_; uint64_t v___x_989_; uint8_t v___x_990_; 
v_position_988_ = lean_uint64_add(v___y_987_, v___y_983_);
v___x_989_ = 172ULL;
v___x_990_ = lean_uint64_dec_lt(v_position_988_, v___x_989_);
if (v___x_990_ == 0)
{
uint64_t v___x_991_; uint8_t v___x_992_; 
v___x_991_ = 23ULL;
v___x_992_ = lean_uint64_dec_lt(v___y_987_, v___x_991_);
if (v___x_992_ == 0)
{
uint64_t v___x_993_; uint8_t v___x_994_; 
v___x_993_ = lean_uint64_sub(v___y_987_, v___x_991_);
v___x_994_ = lean_uint64_dec_eq(v___x_993_, v___y_984_);
if (v___x_994_ == 0)
{
uint64_t v___x_995_; uint8_t v___x_996_; 
v___x_995_ = 64ULL;
v___x_996_ = lean_uint64_dec_lt(v___x_993_, v___x_995_);
if (v___x_996_ == 0)
{
uint8_t v___x_997_; 
v___x_997_ = lean_uint64_dec_eq(v___x_993_, v___x_995_);
if (v___x_997_ == 0)
{
lean_dec(v___y_982_);
v___y_973_ = v_position_988_;
v___y_974_ = v___y_984_;
v___y_975_ = v___y_985_;
v___y_976_ = v___y_984_;
goto v___jp_972_;
}
else
{
uint64_t v___x_998_; uint64_t v___x_999_; uint8_t v___x_1000_; 
v___x_998_ = 9223372036854775808ULL;
v___x_999_ = lean_unbox_uint64(v___y_982_);
lean_dec(v___y_982_);
v___x_1000_ = lean_uint64_dec_lt(v___x_998_, v___x_999_);
if (v___x_1000_ == 0)
{
v___y_973_ = v_position_988_;
v___y_974_ = v___y_984_;
v___y_975_ = v___y_985_;
v___y_976_ = v___y_984_;
goto v___jp_972_;
}
else
{
uint64_t v___x_1001_; 
v___x_1001_ = 1ULL;
v___y_973_ = v_position_988_;
v___y_974_ = v___y_984_;
v___y_975_ = v___y_985_;
v___y_976_ = v___x_1001_;
goto v___jp_972_;
}
}
}
else
{
uint64_t v___x_1002_; uint64_t v_quotient_1003_; uint64_t v___x_1004_; uint64_t v___x_1005_; uint64_t v___x_1006_; uint64_t v___x_1007_; uint64_t v_remainder_1008_; uint64_t v___x_1009_; uint64_t v_half_1010_; uint8_t v___x_1011_; 
v___x_1002_ = lean_unbox_uint64(v___y_982_);
v_quotient_1003_ = lean_uint64_shift_right(v___x_1002_, v___x_993_);
v___x_1004_ = 1ULL;
v___x_1005_ = lean_uint64_shift_left(v___x_1004_, v___x_993_);
v___x_1006_ = lean_uint64_sub(v___x_1005_, v___x_1004_);
v___x_1007_ = lean_unbox_uint64(v___y_982_);
lean_dec(v___y_982_);
v_remainder_1008_ = lean_uint64_land(v___x_1007_, v___x_1006_);
v___x_1009_ = lean_uint64_sub(v___x_993_, v___x_1004_);
v_half_1010_ = lean_uint64_shift_left(v___x_1004_, v___x_1009_);
v___x_1011_ = lean_uint64_dec_lt(v_remainder_1008_, v_half_1010_);
if (v___x_1011_ == 0)
{
uint8_t v___x_1012_; 
v___x_1012_ = lean_uint64_dec_lt(v_half_1010_, v_remainder_1008_);
if (v___x_1012_ == 0)
{
uint64_t v___x_1013_; uint8_t v___x_1014_; 
v___x_1013_ = lean_uint64_land(v_quotient_1003_, v___x_1004_);
v___x_1014_ = lean_uint64_dec_eq(v___x_1013_, v___y_984_);
if (v___x_1014_ == 0)
{
uint64_t v___x_1015_; 
v___x_1015_ = lean_uint64_add(v_quotient_1003_, v___x_1004_);
v___y_973_ = v_position_988_;
v___y_974_ = v___y_984_;
v___y_975_ = v___y_985_;
v___y_976_ = v___x_1015_;
goto v___jp_972_;
}
else
{
v___y_973_ = v_position_988_;
v___y_974_ = v___y_984_;
v___y_975_ = v___y_985_;
v___y_976_ = v_quotient_1003_;
goto v___jp_972_;
}
}
else
{
uint64_t v___x_1016_; 
v___x_1016_ = lean_uint64_add(v_quotient_1003_, v___x_1004_);
v___y_973_ = v_position_988_;
v___y_974_ = v___y_984_;
v___y_975_ = v___y_985_;
v___y_976_ = v___x_1016_;
goto v___jp_972_;
}
}
else
{
v___y_973_ = v_position_988_;
v___y_974_ = v___y_984_;
v___y_975_ = v___y_985_;
v___y_976_ = v_quotient_1003_;
goto v___jp_972_;
}
}
}
else
{
uint64_t v___x_1017_; 
v___x_1017_ = lean_unbox_uint64(v___y_982_);
lean_dec(v___y_982_);
v___y_973_ = v_position_988_;
v___y_974_ = v___y_984_;
v___y_975_ = v___y_985_;
v___y_976_ = v___x_1017_;
goto v___jp_972_;
}
}
else
{
uint64_t v___x_1018_; uint64_t v___x_1019_; uint64_t v___x_1020_; 
v___x_1018_ = lean_uint64_sub(v___x_991_, v___y_987_);
v___x_1019_ = lean_unbox_uint64(v___y_982_);
lean_dec(v___y_982_);
v___x_1020_ = lean_uint64_shift_left(v___x_1019_, v___x_1018_);
v___y_973_ = v_position_988_;
v___y_974_ = v___y_984_;
v___y_975_ = v___y_985_;
v___y_976_ = v___x_1020_;
goto v___jp_972_;
}
}
else
{
uint8_t v___x_1021_; 
v___x_1021_ = lean_uint64_dec_lt(v___y_983_, v___y_986_);
if (v___x_1021_ == 0)
{
uint64_t v___x_1022_; uint64_t v___x_1023_; uint64_t v___x_1024_; 
v___x_1022_ = lean_uint64_sub(v___y_983_, v___y_986_);
v___x_1023_ = lean_unbox_uint64(v___y_982_);
lean_dec(v___y_982_);
v___x_1024_ = lean_uint64_shift_left(v___x_1023_, v___x_1022_);
v___y_628_ = v___y_984_;
v___y_629_ = v___y_985_;
v___y_630_ = v___x_1024_;
goto v___jp_627_;
}
else
{
uint64_t v___x_1025_; uint8_t v___x_1026_; 
v___x_1025_ = lean_uint64_sub(v___y_986_, v___y_983_);
v___x_1026_ = lean_uint64_dec_eq(v___x_1025_, v___y_984_);
if (v___x_1026_ == 0)
{
uint64_t v___x_1027_; uint8_t v___x_1028_; 
v___x_1027_ = 64ULL;
v___x_1028_ = lean_uint64_dec_lt(v___x_1025_, v___x_1027_);
if (v___x_1028_ == 0)
{
uint8_t v___x_1029_; 
v___x_1029_ = lean_uint64_dec_eq(v___x_1025_, v___x_1027_);
if (v___x_1029_ == 0)
{
lean_dec(v___y_982_);
v___y_628_ = v___y_984_;
v___y_629_ = v___y_985_;
v___y_630_ = v___y_984_;
goto v___jp_627_;
}
else
{
uint64_t v___x_1030_; uint64_t v___x_1031_; uint8_t v___x_1032_; 
v___x_1030_ = 9223372036854775808ULL;
v___x_1031_ = lean_unbox_uint64(v___y_982_);
lean_dec(v___y_982_);
v___x_1032_ = lean_uint64_dec_lt(v___x_1030_, v___x_1031_);
if (v___x_1032_ == 0)
{
v___y_628_ = v___y_984_;
v___y_629_ = v___y_985_;
v___y_630_ = v___y_984_;
goto v___jp_627_;
}
else
{
uint64_t v___x_1033_; 
v___x_1033_ = 1ULL;
v___y_628_ = v___y_984_;
v___y_629_ = v___y_985_;
v___y_630_ = v___x_1033_;
goto v___jp_627_;
}
}
}
else
{
uint64_t v___x_1034_; uint64_t v_quotient_1035_; uint64_t v___x_1036_; uint64_t v___x_1037_; uint64_t v___x_1038_; uint64_t v___x_1039_; uint64_t v_remainder_1040_; uint64_t v___x_1041_; uint64_t v_half_1042_; uint8_t v___x_1043_; 
v___x_1034_ = lean_unbox_uint64(v___y_982_);
v_quotient_1035_ = lean_uint64_shift_right(v___x_1034_, v___x_1025_);
v___x_1036_ = 1ULL;
v___x_1037_ = lean_uint64_shift_left(v___x_1036_, v___x_1025_);
v___x_1038_ = lean_uint64_sub(v___x_1037_, v___x_1036_);
v___x_1039_ = lean_unbox_uint64(v___y_982_);
lean_dec(v___y_982_);
v_remainder_1040_ = lean_uint64_land(v___x_1039_, v___x_1038_);
v___x_1041_ = lean_uint64_sub(v___x_1025_, v___x_1036_);
v_half_1042_ = lean_uint64_shift_left(v___x_1036_, v___x_1041_);
v___x_1043_ = lean_uint64_dec_lt(v_remainder_1040_, v_half_1042_);
if (v___x_1043_ == 0)
{
uint8_t v___x_1044_; 
v___x_1044_ = lean_uint64_dec_lt(v_half_1042_, v_remainder_1040_);
if (v___x_1044_ == 0)
{
uint64_t v___x_1045_; uint8_t v___x_1046_; 
v___x_1045_ = lean_uint64_land(v_quotient_1035_, v___x_1036_);
v___x_1046_ = lean_uint64_dec_eq(v___x_1045_, v___y_984_);
if (v___x_1046_ == 0)
{
uint64_t v___x_1047_; 
v___x_1047_ = lean_uint64_add(v_quotient_1035_, v___x_1036_);
v___y_628_ = v___y_984_;
v___y_629_ = v___y_985_;
v___y_630_ = v___x_1047_;
goto v___jp_627_;
}
else
{
v___y_628_ = v___y_984_;
v___y_629_ = v___y_985_;
v___y_630_ = v_quotient_1035_;
goto v___jp_627_;
}
}
else
{
uint64_t v___x_1048_; 
v___x_1048_ = lean_uint64_add(v_quotient_1035_, v___x_1036_);
v___y_628_ = v___y_984_;
v___y_629_ = v___y_985_;
v___y_630_ = v___x_1048_;
goto v___jp_627_;
}
}
else
{
v___y_628_ = v___y_984_;
v___y_629_ = v___y_985_;
v___y_630_ = v_quotient_1035_;
goto v___jp_627_;
}
}
}
else
{
uint64_t v___x_1049_; 
v___x_1049_ = lean_unbox_uint64(v___y_982_);
lean_dec(v___y_982_);
v___y_628_ = v___y_984_;
v___y_629_ = v___y_985_;
v___y_630_ = v___x_1049_;
goto v___jp_627_;
}
}
}
}
v___jp_1050_:
{
uint64_t v___x_1058_; uint64_t v___x_1059_; uint8_t v___x_1060_; 
v___x_1058_ = 1ULL;
v___x_1059_ = lean_uint64_shift_right(v___y_1056_, v___x_1058_);
v___x_1060_ = lean_uint64_dec_eq(v___x_1059_, v___y_1053_);
if (v___x_1060_ == 0)
{
uint64_t v___x_1061_; 
v___x_1061_ = lean_uint64_add(v___y_1057_, v___x_1058_);
v___y_982_ = v___y_1052_;
v___y_983_ = v___y_1051_;
v___y_984_ = v___y_1053_;
v___y_985_ = v___y_1054_;
v___y_986_ = v___y_1055_;
v___y_987_ = v___x_1061_;
goto v___jp_981_;
}
else
{
v___y_982_ = v___y_1052_;
v___y_983_ = v___y_1051_;
v___y_984_ = v___y_1053_;
v___y_985_ = v___y_1054_;
v___y_986_ = v___y_1055_;
v___y_987_ = v___y_1057_;
goto v___jp_981_;
}
}
v___jp_1062_:
{
uint64_t v___x_1072_; uint8_t v___x_1073_; 
v___x_1072_ = lean_uint64_shift_right(v___y_1063_, v___y_1068_);
v___x_1073_ = lean_uint64_dec_eq(v___x_1072_, v___y_1066_);
if (v___x_1073_ == 0)
{
uint64_t v___x_1074_; 
v___x_1074_ = lean_uint64_add(v___y_1070_, v___y_1068_);
v___y_1051_ = v___y_1065_;
v___y_1052_ = v___y_1064_;
v___y_1053_ = v___y_1066_;
v___y_1054_ = v___y_1067_;
v___y_1055_ = v___y_1069_;
v___y_1056_ = v___y_1071_;
v___y_1057_ = v___x_1074_;
goto v___jp_1050_;
}
else
{
v___y_1051_ = v___y_1065_;
v___y_1052_ = v___y_1064_;
v___y_1053_ = v___y_1066_;
v___y_1054_ = v___y_1067_;
v___y_1055_ = v___y_1069_;
v___y_1056_ = v___y_1071_;
v___y_1057_ = v___y_1070_;
goto v___jp_1050_;
}
}
v___jp_1075_:
{
uint64_t v___x_1083_; uint64_t v___x_1084_; uint8_t v___x_1085_; 
v___x_1083_ = 2ULL;
v___x_1084_ = lean_uint64_shift_right(v___y_1078_, v___x_1083_);
v___x_1085_ = lean_uint64_dec_eq(v___x_1084_, v___y_1079_);
if (v___x_1085_ == 0)
{
v___y_1063_ = v___y_1078_;
v___y_1064_ = v___y_1077_;
v___y_1065_ = v___y_1076_;
v___y_1066_ = v___y_1079_;
v___y_1067_ = v___y_1080_;
v___y_1068_ = v___x_1083_;
v___y_1069_ = v___y_1081_;
v___y_1070_ = v___y_1082_;
v___y_1071_ = v___x_1084_;
goto v___jp_1062_;
}
else
{
v___y_1063_ = v___y_1078_;
v___y_1064_ = v___y_1077_;
v___y_1065_ = v___y_1076_;
v___y_1066_ = v___y_1079_;
v___y_1067_ = v___y_1080_;
v___y_1068_ = v___x_1083_;
v___y_1069_ = v___y_1081_;
v___y_1070_ = v___y_1082_;
v___y_1071_ = v___y_1078_;
goto v___jp_1062_;
}
}
v___jp_1086_:
{
uint64_t v___x_1096_; uint8_t v___x_1097_; 
v___x_1096_ = lean_uint64_shift_right(v___y_1091_, v___y_1093_);
v___x_1097_ = lean_uint64_dec_eq(v___x_1096_, v___y_1090_);
if (v___x_1097_ == 0)
{
uint64_t v___x_1098_; 
v___x_1098_ = lean_uint64_add(v___y_1089_, v___y_1093_);
v___y_1076_ = v___y_1088_;
v___y_1077_ = v___y_1087_;
v___y_1078_ = v___y_1095_;
v___y_1079_ = v___y_1090_;
v___y_1080_ = v___y_1092_;
v___y_1081_ = v___y_1094_;
v___y_1082_ = v___x_1098_;
goto v___jp_1075_;
}
else
{
v___y_1076_ = v___y_1088_;
v___y_1077_ = v___y_1087_;
v___y_1078_ = v___y_1095_;
v___y_1079_ = v___y_1090_;
v___y_1080_ = v___y_1092_;
v___y_1081_ = v___y_1094_;
v___y_1082_ = v___y_1089_;
goto v___jp_1075_;
}
}
v___jp_1099_:
{
uint64_t v___x_1107_; uint64_t v___x_1108_; uint8_t v___x_1109_; 
v___x_1107_ = 4ULL;
v___x_1108_ = lean_uint64_shift_right(v___y_1103_, v___x_1107_);
v___x_1109_ = lean_uint64_dec_eq(v___x_1108_, v___y_1102_);
if (v___x_1109_ == 0)
{
v___y_1087_ = v___y_1101_;
v___y_1088_ = v___y_1100_;
v___y_1089_ = v___y_1106_;
v___y_1090_ = v___y_1102_;
v___y_1091_ = v___y_1103_;
v___y_1092_ = v___y_1104_;
v___y_1093_ = v___x_1107_;
v___y_1094_ = v___y_1105_;
v___y_1095_ = v___x_1108_;
goto v___jp_1086_;
}
else
{
v___y_1087_ = v___y_1101_;
v___y_1088_ = v___y_1100_;
v___y_1089_ = v___y_1106_;
v___y_1090_ = v___y_1102_;
v___y_1091_ = v___y_1103_;
v___y_1092_ = v___y_1104_;
v___y_1093_ = v___x_1107_;
v___y_1094_ = v___y_1105_;
v___y_1095_ = v___y_1103_;
goto v___jp_1086_;
}
}
v___jp_1110_:
{
uint64_t v___x_1120_; uint8_t v___x_1121_; 
v___x_1120_ = lean_uint64_shift_right(v___y_1113_, v___y_1118_);
v___x_1121_ = lean_uint64_dec_eq(v___x_1120_, v___y_1115_);
if (v___x_1121_ == 0)
{
uint64_t v___x_1122_; 
v___x_1122_ = lean_uint64_add(v___y_1114_, v___y_1118_);
v___y_1100_ = v___y_1112_;
v___y_1101_ = v___y_1111_;
v___y_1102_ = v___y_1115_;
v___y_1103_ = v___y_1119_;
v___y_1104_ = v___y_1116_;
v___y_1105_ = v___y_1117_;
v___y_1106_ = v___x_1122_;
goto v___jp_1099_;
}
else
{
v___y_1100_ = v___y_1112_;
v___y_1101_ = v___y_1111_;
v___y_1102_ = v___y_1115_;
v___y_1103_ = v___y_1119_;
v___y_1104_ = v___y_1116_;
v___y_1105_ = v___y_1117_;
v___y_1106_ = v___y_1114_;
goto v___jp_1099_;
}
}
v___jp_1123_:
{
uint64_t v___x_1131_; uint64_t v___x_1132_; uint8_t v___x_1133_; 
v___x_1131_ = 8ULL;
v___x_1132_ = lean_uint64_shift_right(v___y_1126_, v___x_1131_);
v___x_1133_ = lean_uint64_dec_eq(v___x_1132_, v___y_1127_);
if (v___x_1133_ == 0)
{
v___y_1111_ = v___y_1125_;
v___y_1112_ = v___y_1124_;
v___y_1113_ = v___y_1126_;
v___y_1114_ = v___y_1130_;
v___y_1115_ = v___y_1127_;
v___y_1116_ = v___y_1128_;
v___y_1117_ = v___y_1129_;
v___y_1118_ = v___x_1131_;
v___y_1119_ = v___x_1132_;
goto v___jp_1110_;
}
else
{
v___y_1111_ = v___y_1125_;
v___y_1112_ = v___y_1124_;
v___y_1113_ = v___y_1126_;
v___y_1114_ = v___y_1130_;
v___y_1115_ = v___y_1127_;
v___y_1116_ = v___y_1128_;
v___y_1117_ = v___y_1129_;
v___y_1118_ = v___x_1131_;
v___y_1119_ = v___y_1126_;
goto v___jp_1110_;
}
}
v___jp_1134_:
{
uint64_t v___x_1144_; uint8_t v___x_1145_; 
v___x_1144_ = lean_uint64_shift_right(v___y_1137_, v___y_1139_);
v___x_1145_ = lean_uint64_dec_eq(v___x_1144_, v___y_1140_);
if (v___x_1145_ == 0)
{
uint64_t v___x_1146_; 
v___x_1146_ = lean_uint64_add(v___y_1138_, v___y_1139_);
v___y_1124_ = v___y_1136_;
v___y_1125_ = v___y_1135_;
v___y_1126_ = v___y_1143_;
v___y_1127_ = v___y_1140_;
v___y_1128_ = v___y_1141_;
v___y_1129_ = v___y_1142_;
v___y_1130_ = v___x_1146_;
goto v___jp_1123_;
}
else
{
v___y_1124_ = v___y_1136_;
v___y_1125_ = v___y_1135_;
v___y_1126_ = v___y_1143_;
v___y_1127_ = v___y_1140_;
v___y_1128_ = v___y_1141_;
v___y_1129_ = v___y_1142_;
v___y_1130_ = v___y_1138_;
goto v___jp_1123_;
}
}
v___jp_1147_:
{
uint64_t v___x_1155_; uint64_t v___x_1156_; uint8_t v___x_1157_; 
v___x_1155_ = 16ULL;
v___x_1156_ = lean_uint64_shift_right(v___y_1150_, v___x_1155_);
v___x_1157_ = lean_uint64_dec_eq(v___x_1156_, v___y_1151_);
if (v___x_1157_ == 0)
{
v___y_1135_ = v___y_1149_;
v___y_1136_ = v___y_1148_;
v___y_1137_ = v___y_1150_;
v___y_1138_ = v___y_1154_;
v___y_1139_ = v___x_1155_;
v___y_1140_ = v___y_1151_;
v___y_1141_ = v___y_1152_;
v___y_1142_ = v___y_1153_;
v___y_1143_ = v___x_1156_;
goto v___jp_1134_;
}
else
{
v___y_1135_ = v___y_1149_;
v___y_1136_ = v___y_1148_;
v___y_1137_ = v___y_1150_;
v___y_1138_ = v___y_1154_;
v___y_1139_ = v___x_1155_;
v___y_1140_ = v___y_1151_;
v___y_1141_ = v___y_1152_;
v___y_1142_ = v___y_1153_;
v___y_1143_ = v___y_1150_;
goto v___jp_1134_;
}
}
v___jp_1158_:
{
uint64_t v___x_1166_; uint64_t v___x_1167_; uint8_t v___x_1168_; 
v___x_1166_ = lean_unbox_uint64(v___y_1159_);
v___x_1167_ = lean_uint64_shift_right(v___x_1166_, v___y_1162_);
v___x_1168_ = lean_uint64_dec_eq(v___x_1167_, v___y_1161_);
if (v___x_1168_ == 0)
{
v___y_1148_ = v___y_1160_;
v___y_1149_ = v___y_1159_;
v___y_1150_ = v___y_1165_;
v___y_1151_ = v___y_1161_;
v___y_1152_ = v___y_1163_;
v___y_1153_ = v___y_1164_;
v___y_1154_ = v___y_1162_;
goto v___jp_1147_;
}
else
{
v___y_1148_ = v___y_1160_;
v___y_1149_ = v___y_1159_;
v___y_1150_ = v___y_1165_;
v___y_1151_ = v___y_1161_;
v___y_1152_ = v___y_1163_;
v___y_1153_ = v___y_1164_;
v___y_1154_ = v___y_1161_;
goto v___jp_1147_;
}
}
v___jp_1169_:
{
uint64_t v___x_1173_; uint64_t v___x_1174_; uint8_t v___x_1175_; 
v___x_1173_ = 0ULL;
v___x_1174_ = lean_unbox_uint64(v_snd_1172_);
v___x_1175_ = lean_uint64_dec_eq(v___x_1174_, v___x_1173_);
if (v___x_1175_ == 0)
{
uint64_t v___x_1176_; uint64_t v___x_1177_; uint64_t v___x_1178_; uint64_t v___x_1179_; uint64_t v___x_1180_; uint8_t v___x_1181_; 
v___x_1176_ = 149ULL;
v___x_1177_ = lean_uint64_add(v___y_1170_, v___x_1176_);
v___x_1178_ = 32ULL;
v___x_1179_ = lean_unbox_uint64(v_snd_1172_);
v___x_1180_ = lean_uint64_shift_right(v___x_1179_, v___x_1178_);
v___x_1181_ = lean_uint64_dec_eq(v___x_1180_, v___x_1173_);
if (v___x_1181_ == 0)
{
v___y_1159_ = v_snd_1172_;
v___y_1160_ = v___x_1177_;
v___y_1161_ = v___x_1173_;
v___y_1162_ = v___x_1178_;
v___y_1163_ = v_fst_1171_;
v___y_1164_ = v___x_1176_;
v___y_1165_ = v___x_1180_;
goto v___jp_1158_;
}
else
{
uint64_t v___x_1182_; 
v___x_1182_ = lean_unbox_uint64(v_snd_1172_);
v___y_1159_ = v_snd_1172_;
v___y_1160_ = v___x_1177_;
v___y_1161_ = v___x_1173_;
v___y_1162_ = v___x_1178_;
v___y_1163_ = v_fst_1171_;
v___y_1164_ = v___x_1176_;
v___y_1165_ = v___x_1182_;
goto v___jp_1158_;
}
}
else
{
uint8_t v___x_1183_; 
lean_dec(v_snd_1172_);
v___x_1183_ = lean_unbox(v_fst_1171_);
lean_dec(v_fst_1171_);
if (v___x_1183_ == 0)
{
uint32_t v___x_1184_; 
v___x_1184_ = 0;
return v___x_1184_;
}
else
{
uint32_t v___x_1185_; 
v___x_1185_ = 2147483648;
return v___x_1185_;
}
}
}
v___jp_1186_:
{
uint8_t v___x_1193_; 
v___x_1193_ = lean_uint64_dec_eq(v___y_1191_, v___y_1188_);
if (v___x_1193_ == 0)
{
uint8_t v___x_1194_; 
v___x_1194_ = lean_uint64_dec_lt(v___y_1191_, v___y_1188_);
if (v___x_1194_ == 0)
{
uint64_t v___x_1195_; lean_object* v___x_1196_; lean_object* v___x_1197_; 
v___x_1195_ = lean_uint64_sub(v___y_1191_, v___y_1188_);
v___x_1196_ = lean_box(v___y_1190_);
v___x_1197_ = lean_box_uint64(v___x_1195_);
v___y_1170_ = v___y_1187_;
v_fst_1171_ = v___x_1196_;
v_snd_1172_ = v___x_1197_;
goto v___jp_1169_;
}
else
{
uint64_t v___x_1198_; lean_object* v___x_1199_; lean_object* v___x_1200_; 
v___x_1198_ = lean_uint64_sub(v___y_1188_, v___y_1191_);
v___x_1199_ = lean_box(v___y_1189_);
v___x_1200_ = lean_box_uint64(v___x_1198_);
v___y_1170_ = v___y_1187_;
v_fst_1171_ = v___x_1199_;
v_snd_1172_ = v___x_1200_;
goto v___jp_1169_;
}
}
else
{
lean_object* v___x_1201_; lean_object* v___x_1202_; 
v___x_1201_ = lean_box(v___y_1192_);
v___x_1202_ = ((lean_object*)(lp_competition_Submission_TunedAdd_core___boxed__const__1));
v___y_1170_ = v___y_1187_;
v_fst_1171_ = v___x_1201_;
v_snd_1172_ = v___x_1202_;
goto v___jp_1169_;
}
}
v___jp_1203_:
{
if (v___y_1209_ == 0)
{
v___y_1187_ = v___y_1204_;
v___y_1188_ = v___y_1205_;
v___y_1189_ = v___y_1206_;
v___y_1190_ = v___y_1207_;
v___y_1191_ = v___y_1208_;
v___y_1192_ = v___y_1209_;
goto v___jp_1186_;
}
else
{
uint64_t v___x_1210_; lean_object* v___x_1211_; lean_object* v___x_1212_; 
v___x_1210_ = lean_uint64_add(v___y_1208_, v___y_1205_);
v___x_1211_ = lean_box(v___y_1207_);
v___x_1212_ = lean_box_uint64(v___x_1210_);
v___y_1170_ = v___y_1204_;
v_fst_1171_ = v___x_1211_;
v_snd_1172_ = v___x_1212_;
goto v___jp_1169_;
}
}
v___jp_1213_:
{
uint8_t v___x_1220_; 
v___x_1220_ = lean_uint64_dec_le(v___y_1216_, v___y_1219_);
if (v___x_1220_ == 0)
{
uint64_t v_shift_1221_; uint64_t v___x_1222_; uint8_t v___x_1223_; 
v_shift_1221_ = lean_uint64_sub(v___y_1216_, v___y_1219_);
v___x_1222_ = 39ULL;
v___x_1223_ = lean_uint64_dec_le(v_shift_1221_, v___x_1222_);
if (v___x_1223_ == 0)
{
return v_xBits_588_;
}
else
{
uint64_t v___x_1224_; 
v___x_1224_ = lean_uint64_shift_left(v___y_1214_, v_shift_1221_);
if (v___y_1218_ == 0)
{
if (v___y_1217_ == 0)
{
v___y_1204_ = v___y_1219_;
v___y_1205_ = v___y_1215_;
v___y_1206_ = v___y_1217_;
v___y_1207_ = v___y_1218_;
v___y_1208_ = v___x_1224_;
v___y_1209_ = v___x_1223_;
goto v___jp_1203_;
}
else
{
v___y_1187_ = v___y_1219_;
v___y_1188_ = v___y_1215_;
v___y_1189_ = v___y_1217_;
v___y_1190_ = v___y_1218_;
v___y_1191_ = v___x_1224_;
v___y_1192_ = v___y_1218_;
goto v___jp_1186_;
}
}
else
{
v___y_1204_ = v___y_1219_;
v___y_1205_ = v___y_1215_;
v___y_1206_ = v___y_1217_;
v___y_1207_ = v___y_1218_;
v___y_1208_ = v___x_1224_;
v___y_1209_ = v___y_1217_;
goto v___jp_1203_;
}
}
}
else
{
uint64_t v_shift_1225_; uint64_t v___x_1226_; uint8_t v___x_1227_; 
v_shift_1225_ = lean_uint64_sub(v___y_1219_, v___y_1216_);
v___x_1226_ = 39ULL;
v___x_1227_ = lean_uint64_dec_le(v_shift_1225_, v___x_1226_);
if (v___x_1227_ == 0)
{
return v_yBits_589_;
}
else
{
uint64_t v___x_1228_; 
v___x_1228_ = lean_uint64_shift_left(v___y_1215_, v_shift_1225_);
if (v___y_1218_ == 0)
{
if (v___y_1217_ == 0)
{
v___y_921_ = v___y_1214_;
v___y_922_ = v___y_1216_;
v___y_923_ = v___y_1217_;
v___y_924_ = v___x_1228_;
v___y_925_ = v___y_1218_;
v___y_926_ = v___x_1227_;
goto v___jp_920_;
}
else
{
v___y_904_ = v___y_1214_;
v___y_905_ = v___y_1216_;
v___y_906_ = v___y_1217_;
v___y_907_ = v___y_1218_;
v___y_908_ = v___x_1228_;
v___y_909_ = v___y_1218_;
goto v___jp_903_;
}
}
else
{
v___y_921_ = v___y_1214_;
v___y_922_ = v___y_1216_;
v___y_923_ = v___y_1217_;
v___y_924_ = v___x_1228_;
v___y_925_ = v___y_1218_;
v___y_926_ = v___y_1217_;
goto v___jp_920_;
}
}
}
}
v___jp_1232_:
{
uint64_t v___x_1238_; uint64_t v___x_1239_; uint8_t v___x_1240_; 
v___x_1238_ = lean_uint32_to_uint64(v_yExponent_1231_);
v___x_1239_ = 0ULL;
v___x_1240_ = lean_uint64_dec_eq(v___x_1238_, v___x_1239_);
if (v___x_1240_ == 0)
{
uint64_t v___x_1241_; uint64_t v___x_1242_; 
v___x_1241_ = 1ULL;
v___x_1242_ = lean_uint64_sub(v___x_1238_, v___x_1241_);
v___y_1214_ = v___y_1233_;
v___y_1215_ = v___y_1234_;
v___y_1216_ = v___y_1237_;
v___y_1217_ = v___y_1235_;
v___y_1218_ = v___y_1236_;
v___y_1219_ = v___x_1242_;
goto v___jp_1213_;
}
else
{
v___y_1214_ = v___y_1233_;
v___y_1215_ = v___y_1234_;
v___y_1216_ = v___y_1237_;
v___y_1217_ = v___y_1235_;
v___y_1218_ = v___y_1236_;
v___y_1219_ = v___x_1239_;
goto v___jp_1213_;
}
}
v___jp_1243_:
{
uint64_t v___x_1248_; uint64_t v___x_1249_; uint8_t v___x_1250_; 
v___x_1248_ = lean_uint32_to_uint64(v_xExponent_1229_);
v___x_1249_ = 0ULL;
v___x_1250_ = lean_uint64_dec_eq(v___x_1248_, v___x_1249_);
if (v___x_1250_ == 0)
{
uint64_t v___x_1251_; uint64_t v___x_1252_; 
v___x_1251_ = 1ULL;
v___x_1252_ = lean_uint64_sub(v___x_1248_, v___x_1251_);
v___y_1233_ = v___y_1244_;
v___y_1234_ = v___y_1247_;
v___y_1235_ = v___y_1245_;
v___y_1236_ = v___y_1246_;
v___y_1237_ = v___x_1252_;
goto v___jp_1232_;
}
else
{
v___y_1233_ = v___y_1244_;
v___y_1234_ = v___y_1247_;
v___y_1235_ = v___y_1245_;
v___y_1236_ = v___y_1246_;
v___y_1237_ = v___x_1249_;
goto v___jp_1232_;
}
}
v___jp_1253_:
{
uint32_t v___x_1257_; uint32_t v___x_1258_; uint32_t v___x_1259_; uint8_t v___x_1260_; 
v___x_1257_ = 8388607;
v___x_1258_ = lean_uint32_land(v_yBits_589_, v___x_1257_);
v___x_1259_ = 0;
v___x_1260_ = lean_uint32_dec_eq(v_yExponent_1231_, v___x_1259_);
if (v___x_1260_ == 0)
{
uint64_t v___x_1261_; uint64_t v___x_1262_; uint64_t v___x_1263_; 
v___x_1261_ = lean_uint32_to_uint64(v___x_1258_);
v___x_1262_ = 8388608ULL;
v___x_1263_ = lean_uint64_lor(v___x_1261_, v___x_1262_);
v___y_1244_ = v___y_1256_;
v___y_1245_ = v___y_1254_;
v___y_1246_ = v___y_1255_;
v___y_1247_ = v___x_1263_;
goto v___jp_1243_;
}
else
{
uint64_t v___x_1264_; 
v___x_1264_ = lean_uint32_to_uint64(v___x_1258_);
v___y_1244_ = v___y_1256_;
v___y_1245_ = v___y_1254_;
v___y_1246_ = v___y_1255_;
v___y_1247_ = v___x_1264_;
goto v___jp_1243_;
}
}
v___jp_1265_:
{
uint32_t v___x_1268_; uint32_t v___x_1269_; uint32_t v___x_1270_; uint8_t v___x_1271_; 
v___x_1268_ = 8388607;
v___x_1269_ = lean_uint32_land(v_xBits_588_, v___x_1268_);
v___x_1270_ = 0;
v___x_1271_ = lean_uint32_dec_eq(v_xExponent_1229_, v___x_1270_);
if (v___x_1271_ == 0)
{
uint64_t v___x_1272_; uint64_t v___x_1273_; uint64_t v___x_1274_; 
v___x_1272_ = lean_uint32_to_uint64(v___x_1269_);
v___x_1273_ = 8388608ULL;
v___x_1274_ = lean_uint64_lor(v___x_1272_, v___x_1273_);
v___y_1254_ = v___y_1267_;
v___y_1255_ = v___y_1266_;
v___y_1256_ = v___x_1274_;
goto v___jp_1253_;
}
else
{
uint64_t v___x_1275_; 
v___x_1275_ = lean_uint32_to_uint64(v___x_1269_);
v___y_1254_ = v___y_1267_;
v___y_1255_ = v___y_1266_;
v___y_1256_ = v___x_1275_;
goto v___jp_1253_;
}
}
v___jp_1276_:
{
uint32_t v___x_1278_; uint32_t v___x_1279_; uint32_t v___x_1280_; uint8_t v___x_1281_; 
v___x_1278_ = 2147483648;
v___x_1279_ = lean_uint32_land(v_yBits_589_, v___x_1278_);
v___x_1280_ = 0;
v___x_1281_ = lean_uint32_dec_eq(v___x_1279_, v___x_1280_);
if (v___x_1281_ == 0)
{
uint8_t v___x_1282_; 
v___x_1282_ = 1;
v___y_1266_ = v___y_1277_;
v___y_1267_ = v___x_1282_;
goto v___jp_1265_;
}
else
{
uint8_t v___x_1283_; 
v___x_1283_ = 0;
v___y_1266_ = v___y_1277_;
v___y_1267_ = v___x_1283_;
goto v___jp_1265_;
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_TunedAdd_core___boxed(lean_object* v_xBits_1290_, lean_object* v_yBits_1291_){
_start:
{
uint32_t v_xBits_boxed_1292_; uint32_t v_yBits_boxed_1293_; uint32_t v_res_1294_; lean_object* v_r_1295_; 
v_xBits_boxed_1292_ = lean_unbox_uint32(v_xBits_1290_);
lean_dec(v_xBits_1290_);
v_yBits_boxed_1293_ = lean_unbox_uint32(v_yBits_1291_);
lean_dec(v_yBits_1291_);
v_res_1294_ = lp_competition_Submission_TunedAdd_core(v_xBits_boxed_1292_, v_yBits_boxed_1293_);
v_r_1295_ = lean_box_uint32(v_res_1294_);
return v_r_1295_;
}
}
LEAN_EXPORT uint8_t lp_competition_Submission_TunedAdd_sp1(uint32_t v_a_1296_){
_start:
{
uint32_t v___x_1297_; uint32_t v___x_1298_; uint32_t v___x_1299_; uint32_t v___x_1300_; uint8_t v___x_1301_; 
v___x_1297_ = 4278190079;
v___x_1298_ = 1;
v___x_1299_ = lean_uint32_shift_left(v_a_1296_, v___x_1298_);
v___x_1300_ = lean_uint32_sub(v___x_1299_, v___x_1298_);
v___x_1301_ = lean_uint32_dec_le(v___x_1297_, v___x_1300_);
return v___x_1301_;
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_TunedAdd_sp1___boxed(lean_object* v_a_1302_){
_start:
{
uint32_t v_a_boxed_1303_; uint8_t v_res_1304_; lean_object* v_r_1305_; 
v_a_boxed_1303_ = lean_unbox_uint32(v_a_1302_);
lean_dec(v_a_1302_);
v_res_1304_ = lp_competition_Submission_TunedAdd_sp1(v_a_boxed_1303_);
v_r_1305_ = lean_box(v_res_1304_);
return v_r_1305_;
}
}
LEAN_EXPORT uint8_t lp_competition_Submission_TunedAdd_special(uint32_t v_a_1306_, uint32_t v_b_1307_){
_start:
{
uint32_t v___x_1308_; uint32_t v___x_1309_; uint32_t v___x_1310_; uint32_t v___x_1311_; uint8_t v___x_1312_; 
v___x_1308_ = 4278190079;
v___x_1309_ = 1;
v___x_1310_ = lean_uint32_shift_left(v_a_1306_, v___x_1309_);
v___x_1311_ = lean_uint32_sub(v___x_1310_, v___x_1309_);
v___x_1312_ = lean_uint32_dec_le(v___x_1308_, v___x_1311_);
if (v___x_1312_ == 0)
{
uint32_t v___x_1313_; uint32_t v___x_1314_; uint8_t v___x_1315_; 
v___x_1313_ = lean_uint32_shift_left(v_b_1307_, v___x_1309_);
v___x_1314_ = lean_uint32_sub(v___x_1313_, v___x_1309_);
v___x_1315_ = lean_uint32_dec_le(v___x_1308_, v___x_1314_);
return v___x_1315_;
}
else
{
return v___x_1312_;
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_TunedAdd_special___boxed(lean_object* v_a_1316_, lean_object* v_b_1317_){
_start:
{
uint32_t v_a_boxed_1318_; uint32_t v_b_boxed_1319_; uint8_t v_res_1320_; lean_object* v_r_1321_; 
v_a_boxed_1318_ = lean_unbox_uint32(v_a_1316_);
lean_dec(v_a_1316_);
v_b_boxed_1319_ = lean_unbox_uint32(v_b_1317_);
lean_dec(v_b_1317_);
v_res_1320_ = lp_competition_Submission_TunedAdd_special(v_a_boxed_1318_, v_b_boxed_1319_);
v_r_1321_ = lean_box(v_res_1320_);
return v_r_1321_;
}
}
LEAN_EXPORT uint32_t lp_competition_Submission_TunedAdd_ofBits(uint32_t v_w_1322_){
_start:
{
return v_w_1322_;
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_TunedAdd_ofBits___boxed(lean_object* v_w_1323_){
_start:
{
uint32_t v_w_boxed_1324_; uint32_t v_res_1325_; lean_object* v_r_1326_; 
v_w_boxed_1324_ = lean_unbox_uint32(v_w_1323_);
lean_dec(v_w_1323_);
v_res_1325_ = lp_competition_Submission_TunedAdd_ofBits(v_w_boxed_1324_);
v_r_1326_ = lean_box_uint32(v_res_1325_);
return v_r_1326_;
}
}
LEAN_EXPORT uint32_t lp_competition_Submission_TunedAdd_add(uint32_t v_x_1327_, uint32_t v_y_1328_){
_start:
{
uint32_t v___y_1330_; uint32_t v___y_1334_; uint32_t v___y_1338_; uint32_t v___y_1339_; uint64_t v___y_1344_; lean_object* v___y_1345_; uint64_t v___y_1346_; uint32_t v___y_1361_; uint32_t v___y_1362_; uint32_t v___y_1363_; uint32_t v___y_1364_; uint32_t v___y_1365_; uint32_t v___y_1373_; uint32_t v___y_1374_; uint32_t v___y_1375_; lean_object* v___y_1376_; uint32_t v___y_1377_; uint64_t v___y_1382_; uint32_t v___y_1383_; uint64_t v___y_1384_; uint32_t v___y_1385_; lean_object* v___y_1386_; uint64_t v___y_1387_; uint8_t v___y_1397_; uint32_t v___y_1398_; uint32_t v___y_1399_; uint64_t v___y_1400_; lean_object* v___y_1401_; uint64_t v___y_1402_; uint64_t v___y_1403_; uint64_t v___y_1411_; uint32_t v___y_1412_; uint64_t v___y_1413_; uint32_t v___y_1414_; lean_object* v___y_1415_; uint64_t v___y_1416_; uint64_t v___y_1422_; lean_object* v___y_1423_; uint32_t v___y_1424_; uint32_t v___y_1425_; uint64_t v___y_1426_; lean_object* v___y_1427_; uint64_t v___y_1428_; uint64_t v___y_1429_; uint64_t v___y_1493_; uint32_t v___y_1494_; lean_object* v___y_1495_; uint32_t v___y_1496_; uint64_t v___y_1497_; uint64_t v___y_1498_; lean_object* v___y_1499_; uint64_t v___y_1500_; uint64_t v___y_1501_; uint64_t v___y_1507_; uint64_t v___y_1508_; uint64_t v___y_1509_; lean_object* v___y_1510_; uint32_t v___y_1511_; uint64_t v___y_1512_; uint64_t v___y_1513_; uint32_t v___y_1514_; lean_object* v___y_1515_; uint64_t v___y_1516_; uint64_t v___y_1517_; uint64_t v___y_1522_; uint64_t v___y_1523_; uint32_t v___y_1524_; lean_object* v___y_1525_; uint32_t v___y_1526_; uint64_t v___y_1527_; uint64_t v___y_1528_; lean_object* v___y_1529_; uint64_t v___y_1530_; uint64_t v___y_1535_; uint64_t v___y_1536_; uint64_t v___y_1537_; uint64_t v___y_1538_; lean_object* v___y_1539_; uint32_t v___y_1540_; uint64_t v___y_1541_; uint32_t v___y_1542_; lean_object* v___y_1543_; uint64_t v___y_1544_; uint64_t v___y_1545_; uint64_t v___y_1550_; uint64_t v___y_1551_; uint32_t v___y_1552_; lean_object* v___y_1553_; uint32_t v___y_1554_; uint64_t v___y_1555_; uint64_t v___y_1556_; lean_object* v___y_1557_; uint64_t v___y_1558_; uint64_t v___y_1563_; uint64_t v___y_1564_; uint64_t v___y_1565_; lean_object* v___y_1566_; uint32_t v___y_1567_; uint64_t v___y_1568_; uint32_t v___y_1569_; uint64_t v___y_1570_; lean_object* v___y_1571_; uint64_t v___y_1572_; uint64_t v___y_1573_; uint64_t v___y_1578_; uint64_t v___y_1579_; uint32_t v___y_1580_; lean_object* v___y_1581_; uint32_t v___y_1582_; uint64_t v___y_1583_; uint64_t v___y_1584_; lean_object* v___y_1585_; uint64_t v___y_1586_; uint64_t v___y_1591_; uint64_t v___y_1592_; lean_object* v___y_1593_; uint32_t v___y_1594_; uint64_t v___y_1595_; uint32_t v___y_1596_; lean_object* v___y_1597_; uint64_t v___y_1598_; uint64_t v___y_1599_; uint64_t v___y_1600_; uint64_t v___y_1601_; uint64_t v___y_1606_; uint32_t v___y_1607_; lean_object* v___y_1608_; uint32_t v___y_1609_; uint64_t v___y_1610_; uint64_t v___y_1611_; lean_object* v___y_1612_; uint64_t v___y_1613_; uint64_t v___y_1614_; uint64_t v___y_1619_; lean_object* v___y_1620_; uint32_t v___y_1621_; uint64_t v___y_1622_; uint32_t v___y_1623_; lean_object* v___y_1624_; uint64_t v___y_1625_; uint64_t v___y_1626_; uint64_t v___y_1627_; uint64_t v___y_1632_; uint32_t v___y_1633_; uint32_t v___y_1634_; lean_object* v_fst_1635_; lean_object* v_snd_1636_; uint32_t v___y_1651_; uint32_t v___y_1652_; uint64_t v___y_1657_; lean_object* v___y_1658_; uint64_t v___y_1659_; uint32_t v___y_1674_; uint32_t v___y_1675_; uint32_t v___y_1676_; uint32_t v___y_1677_; uint32_t v___y_1678_; uint32_t v___y_1686_; uint32_t v___y_1687_; uint32_t v___y_1688_; lean_object* v___y_1689_; uint32_t v___y_1690_; uint64_t v___y_1695_; uint32_t v___y_1696_; uint32_t v___y_1697_; lean_object* v___y_1698_; uint64_t v___y_1699_; uint64_t v___y_1700_; uint8_t v___y_1710_; uint32_t v___y_1711_; uint64_t v___y_1712_; uint64_t v___y_1713_; uint32_t v___y_1714_; lean_object* v___y_1715_; uint64_t v___y_1716_; uint64_t v___y_1724_; uint64_t v___y_1725_; uint32_t v___y_1726_; uint32_t v___y_1727_; lean_object* v___y_1728_; uint64_t v___y_1729_; uint64_t v___y_1735_; uint64_t v___y_1736_; lean_object* v___y_1737_; uint32_t v___y_1738_; uint64_t v___y_1739_; uint32_t v___y_1740_; lean_object* v___y_1741_; uint64_t v___y_1742_; uint64_t v___y_1806_; uint64_t v___y_1807_; uint64_t v___y_1808_; lean_object* v___y_1809_; uint32_t v___y_1810_; uint64_t v___y_1811_; uint32_t v___y_1812_; lean_object* v___y_1813_; uint64_t v___y_1814_; uint64_t v___y_1820_; uint64_t v___y_1821_; uint64_t v___y_1822_; uint64_t v___y_1823_; lean_object* v___y_1824_; uint64_t v___y_1825_; uint64_t v___y_1826_; uint32_t v___y_1827_; uint32_t v___y_1828_; lean_object* v___y_1829_; uint64_t v___y_1830_; uint64_t v___y_1835_; uint64_t v___y_1836_; uint64_t v___y_1837_; lean_object* v___y_1838_; uint32_t v___y_1839_; uint64_t v___y_1840_; uint32_t v___y_1841_; lean_object* v___y_1842_; uint64_t v___y_1843_; uint64_t v___y_1848_; uint64_t v___y_1849_; uint64_t v___y_1850_; uint64_t v___y_1851_; uint64_t v___y_1852_; lean_object* v___y_1853_; uint64_t v___y_1854_; uint32_t v___y_1855_; uint32_t v___y_1856_; lean_object* v___y_1857_; uint64_t v___y_1858_; uint64_t v___y_1863_; uint64_t v___y_1864_; lean_object* v___y_1865_; uint64_t v___y_1866_; uint32_t v___y_1867_; uint64_t v___y_1868_; uint32_t v___y_1869_; lean_object* v___y_1870_; uint64_t v___y_1871_; uint64_t v___y_1876_; uint64_t v___y_1877_; uint64_t v___y_1878_; uint64_t v___y_1879_; uint64_t v___y_1880_; lean_object* v___y_1881_; uint64_t v___y_1882_; uint32_t v___y_1883_; uint32_t v___y_1884_; lean_object* v___y_1885_; uint64_t v___y_1886_; uint64_t v___y_1891_; uint64_t v___y_1892_; uint64_t v___y_1893_; lean_object* v___y_1894_; uint32_t v___y_1895_; uint64_t v___y_1896_; uint32_t v___y_1897_; lean_object* v___y_1898_; uint64_t v___y_1899_; uint64_t v___y_1904_; uint64_t v___y_1905_; uint64_t v___y_1906_; lean_object* v___y_1907_; uint64_t v___y_1908_; uint64_t v___y_1909_; uint32_t v___y_1910_; uint32_t v___y_1911_; lean_object* v___y_1912_; uint64_t v___y_1913_; uint64_t v___y_1914_; uint64_t v___y_1919_; uint64_t v___y_1920_; lean_object* v___y_1921_; uint32_t v___y_1922_; uint64_t v___y_1923_; uint64_t v___y_1924_; uint32_t v___y_1925_; lean_object* v___y_1926_; uint64_t v___y_1927_; uint64_t v___y_1932_; uint64_t v___y_1933_; uint64_t v___y_1934_; lean_object* v___y_1935_; uint64_t v___y_1936_; uint32_t v___y_1937_; uint32_t v___y_1938_; lean_object* v___y_1939_; uint64_t v___y_1940_; uint32_t v___y_1945_; uint32_t v___y_1946_; uint64_t v___y_1947_; lean_object* v_fst_1948_; lean_object* v_snd_1949_; uint64_t v___y_1964_; uint64_t v___y_1965_; uint8_t v___y_1966_; uint8_t v___y_1967_; uint32_t v___y_1968_; uint32_t v___y_1969_; uint64_t v___y_1970_; uint8_t v___y_1971_; uint64_t v___y_1983_; uint64_t v___y_1984_; uint8_t v___y_1985_; uint8_t v___y_1986_; uint32_t v___y_1987_; uint32_t v___y_1988_; uint64_t v___y_1989_; uint8_t v___y_1990_; uint64_t v___y_1995_; uint8_t v___y_1996_; uint8_t v___y_1997_; uint64_t v___y_1998_; uint32_t v___y_1999_; uint32_t v___y_2000_; uint64_t v___y_2001_; uint8_t v___y_2002_; uint64_t v___y_2014_; uint8_t v___y_2015_; uint8_t v___y_2016_; uint64_t v___y_2017_; uint32_t v___y_2018_; uint32_t v___y_2019_; uint64_t v___y_2020_; uint8_t v___y_2021_; uint64_t v___y_2026_; uint8_t v___y_2027_; uint8_t v___y_2028_; uint64_t v___y_2029_; uint32_t v___y_2030_; uint32_t v___y_2031_; uint64_t v___y_2032_; uint64_t v___y_2033_; uint64_t v___y_2044_; uint8_t v___y_2045_; uint8_t v___y_2046_; uint32_t v___y_2047_; uint32_t v___y_2048_; uint64_t v___y_2049_; uint32_t v___y_2050_; uint64_t v___y_2051_; uint8_t v___y_2058_; uint8_t v___y_2059_; uint32_t v___y_2060_; uint32_t v___y_2061_; uint32_t v___y_2062_; uint64_t v___y_2063_; uint32_t v___y_2064_; uint64_t v___y_2065_; uint8_t v___y_2072_; uint8_t v___y_2073_; uint32_t v___y_2074_; uint32_t v___y_2075_; uint32_t v___y_2076_; uint32_t v___y_2077_; uint64_t v___y_2078_; uint8_t v___y_2088_; uint32_t v___y_2089_; uint32_t v___y_2090_; uint32_t v___y_2091_; uint32_t v___y_2092_; uint8_t v___y_2093_; uint8_t v___y_2103_; uint32_t v___y_2104_; uint32_t v___y_2105_; uint32_t v___y_2106_; uint32_t v___y_2107_; uint8_t v___y_2108_; uint8_t v___y_2115_; uint32_t v___x_2131_; uint32_t v___x_2132_; uint32_t v___x_2133_; uint32_t v___x_2134_; uint8_t v___x_2135_; 
v___x_2131_ = 4278190079;
v___x_2132_ = 1;
v___x_2133_ = lean_uint32_shift_left(v_x_1327_, v___x_2132_);
v___x_2134_ = lean_uint32_sub(v___x_2133_, v___x_2132_);
v___x_2135_ = lean_uint32_dec_le(v___x_2131_, v___x_2134_);
if (v___x_2135_ == 0)
{
uint32_t v___x_2136_; uint32_t v___x_2137_; uint8_t v___x_2138_; 
v___x_2136_ = lean_uint32_shift_left(v_y_1328_, v___x_2132_);
v___x_2137_ = lean_uint32_sub(v___x_2136_, v___x_2132_);
v___x_2138_ = lean_uint32_dec_le(v___x_2131_, v___x_2137_);
v___y_2115_ = v___x_2138_;
goto v___jp_2114_;
}
else
{
v___y_2115_ = v___x_2135_;
goto v___jp_2114_;
}
v___jp_1329_:
{
uint32_t v___x_1331_; uint32_t v___x_1332_; 
v___x_1331_ = 8388608;
v___x_1332_ = lean_uint32_lor(v___y_1330_, v___x_1331_);
return v___x_1332_;
}
v___jp_1333_:
{
uint32_t v___x_1335_; uint32_t v___x_1336_; 
v___x_1335_ = 8388608;
v___x_1336_ = lean_uint32_lor(v___y_1334_, v___x_1335_);
return v___x_1336_;
}
v___jp_1337_:
{
uint32_t v___x_1340_; uint32_t v___x_1341_; uint32_t v___x_1342_; 
v___x_1340_ = 8388607;
v___x_1341_ = lean_uint32_land(v___y_1338_, v___x_1340_);
v___x_1342_ = lean_uint32_lor(v___y_1339_, v___x_1341_);
return v___x_1342_;
}
v___jp_1343_:
{
uint8_t v___x_1347_; 
v___x_1347_ = lean_uint64_dec_eq(v___y_1346_, v___y_1344_);
if (v___x_1347_ == 0)
{
uint64_t v___x_1348_; uint8_t v___x_1349_; 
v___x_1348_ = 8388608ULL;
v___x_1349_ = lean_uint64_dec_eq(v___y_1346_, v___x_1348_);
if (v___x_1349_ == 0)
{
uint32_t v___x_1350_; uint8_t v___x_1351_; 
v___x_1350_ = lean_uint64_to_uint32(v___y_1346_);
v___x_1351_ = lean_unbox(v___y_1345_);
lean_dec(v___y_1345_);
if (v___x_1351_ == 0)
{
uint32_t v___x_1352_; 
v___x_1352_ = 0;
v___y_1338_ = v___x_1350_;
v___y_1339_ = v___x_1352_;
goto v___jp_1337_;
}
else
{
uint32_t v___x_1353_; 
v___x_1353_ = 2147483648;
v___y_1338_ = v___x_1350_;
v___y_1339_ = v___x_1353_;
goto v___jp_1337_;
}
}
else
{
uint8_t v___x_1354_; 
v___x_1354_ = lean_unbox(v___y_1345_);
lean_dec(v___y_1345_);
if (v___x_1354_ == 0)
{
uint32_t v___x_1355_; 
v___x_1355_ = 0;
v___y_1334_ = v___x_1355_;
goto v___jp_1333_;
}
else
{
uint32_t v___x_1356_; 
v___x_1356_ = 2147483648;
v___y_1334_ = v___x_1356_;
goto v___jp_1333_;
}
}
}
else
{
uint8_t v___x_1357_; 
v___x_1357_ = lean_unbox(v___y_1345_);
lean_dec(v___y_1345_);
if (v___x_1357_ == 0)
{
uint32_t v___x_1358_; 
v___x_1358_ = 0;
return v___x_1358_;
}
else
{
uint32_t v___x_1359_; 
v___x_1359_ = 2147483648;
return v___x_1359_;
}
}
}
v___jp_1360_:
{
uint32_t v___x_1366_; uint32_t v___x_1367_; uint32_t v___x_1368_; uint32_t v___x_1369_; uint32_t v___x_1370_; uint32_t v___x_1371_; 
v___x_1366_ = lean_uint32_land(v___y_1362_, v___y_1364_);
v___x_1367_ = lean_uint32_shift_left(v___x_1366_, v___y_1363_);
v___x_1368_ = lean_uint32_lor(v___y_1365_, v___x_1367_);
v___x_1369_ = 8388607;
v___x_1370_ = lean_uint32_land(v___y_1361_, v___x_1369_);
v___x_1371_ = lean_uint32_lor(v___x_1368_, v___x_1370_);
return v___x_1371_;
}
v___jp_1372_:
{
uint8_t v___x_1378_; 
v___x_1378_ = lean_unbox(v___y_1376_);
lean_dec(v___y_1376_);
if (v___x_1378_ == 0)
{
uint32_t v___x_1379_; 
v___x_1379_ = 0;
v___y_1361_ = v___y_1377_;
v___y_1362_ = v___y_1373_;
v___y_1363_ = v___y_1374_;
v___y_1364_ = v___y_1375_;
v___y_1365_ = v___x_1379_;
goto v___jp_1360_;
}
else
{
uint32_t v___x_1380_; 
v___x_1380_ = 2147483648;
v___y_1361_ = v___y_1377_;
v___y_1362_ = v___y_1373_;
v___y_1363_ = v___y_1374_;
v___y_1364_ = v___y_1375_;
v___y_1365_ = v___x_1380_;
goto v___jp_1360_;
}
}
v___jp_1381_:
{
uint64_t v___x_1388_; uint64_t v_encodedExponent_1389_; uint32_t v___x_1390_; uint64_t v___x_1391_; uint8_t v___x_1392_; 
v___x_1388_ = 171ULL;
v_encodedExponent_1389_ = lean_uint64_sub(v___y_1382_, v___x_1388_);
v___x_1390_ = lean_uint64_to_uint32(v_encodedExponent_1389_);
v___x_1391_ = 8388608ULL;
v___x_1392_ = lean_uint64_dec_lt(v___y_1387_, v___x_1391_);
if (v___x_1392_ == 0)
{
uint64_t v___x_1393_; uint32_t v___x_1394_; 
v___x_1393_ = lean_uint64_sub(v___y_1387_, v___x_1391_);
v___x_1394_ = lean_uint64_to_uint32(v___x_1393_);
v___y_1373_ = v___x_1390_;
v___y_1374_ = v___y_1383_;
v___y_1375_ = v___y_1385_;
v___y_1376_ = v___y_1386_;
v___y_1377_ = v___x_1394_;
goto v___jp_1372_;
}
else
{
uint32_t v___x_1395_; 
v___x_1395_ = lean_uint64_to_uint32(v___y_1384_);
v___y_1373_ = v___x_1390_;
v___y_1374_ = v___y_1383_;
v___y_1375_ = v___y_1385_;
v___y_1376_ = v___y_1386_;
v___y_1377_ = v___x_1395_;
goto v___jp_1372_;
}
}
v___jp_1396_:
{
uint64_t v___x_1404_; uint8_t v___x_1405_; 
v___x_1404_ = 425ULL;
v___x_1405_ = lean_uint64_dec_lt(v___x_1404_, v___y_1403_);
if (v___x_1405_ == 0)
{
if (v___y_1397_ == 0)
{
v___y_1382_ = v___y_1403_;
v___y_1383_ = v___y_1398_;
v___y_1384_ = v___y_1400_;
v___y_1385_ = v___y_1399_;
v___y_1386_ = v___y_1401_;
v___y_1387_ = v___y_1402_;
goto v___jp_1381_;
}
else
{
uint64_t v___x_1406_; 
v___x_1406_ = 8388608ULL;
v___y_1382_ = v___y_1403_;
v___y_1383_ = v___y_1398_;
v___y_1384_ = v___y_1400_;
v___y_1385_ = v___y_1399_;
v___y_1386_ = v___y_1401_;
v___y_1387_ = v___x_1406_;
goto v___jp_1381_;
}
}
else
{
uint8_t v___x_1407_; 
v___x_1407_ = lean_unbox(v___y_1401_);
lean_dec(v___y_1401_);
if (v___x_1407_ == 0)
{
uint32_t v___x_1408_; 
v___x_1408_ = 2139095040;
return v___x_1408_;
}
else
{
uint32_t v___x_1409_; 
v___x_1409_ = 4286578688;
return v___x_1409_;
}
}
}
v___jp_1410_:
{
uint64_t v___x_1417_; uint8_t v_carry_1418_; 
v___x_1417_ = 16777216ULL;
v_carry_1418_ = lean_uint64_dec_eq(v___y_1416_, v___x_1417_);
if (v_carry_1418_ == 0)
{
v___y_1397_ = v_carry_1418_;
v___y_1398_ = v___y_1412_;
v___y_1399_ = v___y_1414_;
v___y_1400_ = v___y_1413_;
v___y_1401_ = v___y_1415_;
v___y_1402_ = v___y_1416_;
v___y_1403_ = v___y_1411_;
goto v___jp_1396_;
}
else
{
uint64_t v___x_1419_; uint64_t v___x_1420_; 
v___x_1419_ = 1ULL;
v___x_1420_ = lean_uint64_add(v___y_1411_, v___x_1419_);
v___y_1397_ = v_carry_1418_;
v___y_1398_ = v___y_1412_;
v___y_1399_ = v___y_1414_;
v___y_1400_ = v___y_1413_;
v___y_1401_ = v___y_1415_;
v___y_1402_ = v___y_1416_;
v___y_1403_ = v___x_1420_;
goto v___jp_1396_;
}
}
v___jp_1421_:
{
uint64_t v_position_1430_; uint64_t v___x_1431_; uint8_t v___x_1432_; 
v_position_1430_ = lean_uint64_add(v___y_1429_, v___y_1428_);
v___x_1431_ = 172ULL;
v___x_1432_ = lean_uint64_dec_lt(v_position_1430_, v___x_1431_);
if (v___x_1432_ == 0)
{
uint64_t v___x_1433_; uint8_t v___x_1434_; 
v___x_1433_ = 23ULL;
v___x_1434_ = lean_uint64_dec_lt(v___y_1429_, v___x_1433_);
if (v___x_1434_ == 0)
{
uint64_t v___x_1435_; uint8_t v___x_1436_; 
v___x_1435_ = lean_uint64_sub(v___y_1429_, v___x_1433_);
v___x_1436_ = lean_uint64_dec_eq(v___x_1435_, v___y_1426_);
if (v___x_1436_ == 0)
{
uint64_t v___x_1437_; uint8_t v___x_1438_; 
v___x_1437_ = 64ULL;
v___x_1438_ = lean_uint64_dec_lt(v___x_1435_, v___x_1437_);
if (v___x_1438_ == 0)
{
uint8_t v___x_1439_; 
v___x_1439_ = lean_uint64_dec_eq(v___x_1435_, v___x_1437_);
if (v___x_1439_ == 0)
{
lean_dec(v___y_1423_);
v___y_1411_ = v_position_1430_;
v___y_1412_ = v___y_1424_;
v___y_1413_ = v___y_1426_;
v___y_1414_ = v___y_1425_;
v___y_1415_ = v___y_1427_;
v___y_1416_ = v___y_1426_;
goto v___jp_1410_;
}
else
{
uint64_t v___x_1440_; uint64_t v___x_1441_; uint8_t v___x_1442_; 
v___x_1440_ = 9223372036854775808ULL;
v___x_1441_ = lean_unbox_uint64(v___y_1423_);
lean_dec(v___y_1423_);
v___x_1442_ = lean_uint64_dec_lt(v___x_1440_, v___x_1441_);
if (v___x_1442_ == 0)
{
v___y_1411_ = v_position_1430_;
v___y_1412_ = v___y_1424_;
v___y_1413_ = v___y_1426_;
v___y_1414_ = v___y_1425_;
v___y_1415_ = v___y_1427_;
v___y_1416_ = v___y_1426_;
goto v___jp_1410_;
}
else
{
uint64_t v___x_1443_; 
v___x_1443_ = 1ULL;
v___y_1411_ = v_position_1430_;
v___y_1412_ = v___y_1424_;
v___y_1413_ = v___y_1426_;
v___y_1414_ = v___y_1425_;
v___y_1415_ = v___y_1427_;
v___y_1416_ = v___x_1443_;
goto v___jp_1410_;
}
}
}
else
{
uint64_t v___x_1444_; uint64_t v_quotient_1445_; uint64_t v___x_1446_; uint64_t v___x_1447_; uint64_t v___x_1448_; uint64_t v___x_1449_; uint64_t v_remainder_1450_; uint64_t v___x_1451_; uint64_t v_half_1452_; uint8_t v___x_1453_; 
v___x_1444_ = lean_unbox_uint64(v___y_1423_);
v_quotient_1445_ = lean_uint64_shift_right(v___x_1444_, v___x_1435_);
v___x_1446_ = 1ULL;
v___x_1447_ = lean_uint64_shift_left(v___x_1446_, v___x_1435_);
v___x_1448_ = lean_uint64_sub(v___x_1447_, v___x_1446_);
v___x_1449_ = lean_unbox_uint64(v___y_1423_);
lean_dec(v___y_1423_);
v_remainder_1450_ = lean_uint64_land(v___x_1449_, v___x_1448_);
v___x_1451_ = lean_uint64_sub(v___x_1435_, v___x_1446_);
v_half_1452_ = lean_uint64_shift_left(v___x_1446_, v___x_1451_);
v___x_1453_ = lean_uint64_dec_lt(v_remainder_1450_, v_half_1452_);
if (v___x_1453_ == 0)
{
uint8_t v___x_1454_; 
v___x_1454_ = lean_uint64_dec_lt(v_half_1452_, v_remainder_1450_);
if (v___x_1454_ == 0)
{
uint64_t v___x_1455_; uint8_t v___x_1456_; 
v___x_1455_ = lean_uint64_land(v_quotient_1445_, v___x_1446_);
v___x_1456_ = lean_uint64_dec_eq(v___x_1455_, v___y_1426_);
if (v___x_1456_ == 0)
{
uint64_t v___x_1457_; 
v___x_1457_ = lean_uint64_add(v_quotient_1445_, v___x_1446_);
v___y_1411_ = v_position_1430_;
v___y_1412_ = v___y_1424_;
v___y_1413_ = v___y_1426_;
v___y_1414_ = v___y_1425_;
v___y_1415_ = v___y_1427_;
v___y_1416_ = v___x_1457_;
goto v___jp_1410_;
}
else
{
v___y_1411_ = v_position_1430_;
v___y_1412_ = v___y_1424_;
v___y_1413_ = v___y_1426_;
v___y_1414_ = v___y_1425_;
v___y_1415_ = v___y_1427_;
v___y_1416_ = v_quotient_1445_;
goto v___jp_1410_;
}
}
else
{
uint64_t v___x_1458_; 
v___x_1458_ = lean_uint64_add(v_quotient_1445_, v___x_1446_);
v___y_1411_ = v_position_1430_;
v___y_1412_ = v___y_1424_;
v___y_1413_ = v___y_1426_;
v___y_1414_ = v___y_1425_;
v___y_1415_ = v___y_1427_;
v___y_1416_ = v___x_1458_;
goto v___jp_1410_;
}
}
else
{
v___y_1411_ = v_position_1430_;
v___y_1412_ = v___y_1424_;
v___y_1413_ = v___y_1426_;
v___y_1414_ = v___y_1425_;
v___y_1415_ = v___y_1427_;
v___y_1416_ = v_quotient_1445_;
goto v___jp_1410_;
}
}
}
else
{
uint64_t v___x_1459_; 
v___x_1459_ = lean_unbox_uint64(v___y_1423_);
lean_dec(v___y_1423_);
v___y_1411_ = v_position_1430_;
v___y_1412_ = v___y_1424_;
v___y_1413_ = v___y_1426_;
v___y_1414_ = v___y_1425_;
v___y_1415_ = v___y_1427_;
v___y_1416_ = v___x_1459_;
goto v___jp_1410_;
}
}
else
{
uint64_t v___x_1460_; uint64_t v___x_1461_; uint64_t v___x_1462_; 
v___x_1460_ = lean_uint64_sub(v___x_1433_, v___y_1429_);
v___x_1461_ = lean_unbox_uint64(v___y_1423_);
lean_dec(v___y_1423_);
v___x_1462_ = lean_uint64_shift_left(v___x_1461_, v___x_1460_);
v___y_1411_ = v_position_1430_;
v___y_1412_ = v___y_1424_;
v___y_1413_ = v___y_1426_;
v___y_1414_ = v___y_1425_;
v___y_1415_ = v___y_1427_;
v___y_1416_ = v___x_1462_;
goto v___jp_1410_;
}
}
else
{
uint8_t v___x_1463_; 
v___x_1463_ = lean_uint64_dec_lt(v___y_1428_, v___y_1422_);
if (v___x_1463_ == 0)
{
uint64_t v___x_1464_; uint64_t v___x_1465_; uint64_t v___x_1466_; 
v___x_1464_ = lean_uint64_sub(v___y_1428_, v___y_1422_);
v___x_1465_ = lean_unbox_uint64(v___y_1423_);
lean_dec(v___y_1423_);
v___x_1466_ = lean_uint64_shift_left(v___x_1465_, v___x_1464_);
v___y_1344_ = v___y_1426_;
v___y_1345_ = v___y_1427_;
v___y_1346_ = v___x_1466_;
goto v___jp_1343_;
}
else
{
uint64_t v___x_1467_; uint8_t v___x_1468_; 
v___x_1467_ = lean_uint64_sub(v___y_1422_, v___y_1428_);
v___x_1468_ = lean_uint64_dec_eq(v___x_1467_, v___y_1426_);
if (v___x_1468_ == 0)
{
uint64_t v___x_1469_; uint8_t v___x_1470_; 
v___x_1469_ = 64ULL;
v___x_1470_ = lean_uint64_dec_lt(v___x_1467_, v___x_1469_);
if (v___x_1470_ == 0)
{
uint8_t v___x_1471_; 
v___x_1471_ = lean_uint64_dec_eq(v___x_1467_, v___x_1469_);
if (v___x_1471_ == 0)
{
lean_dec(v___y_1423_);
v___y_1344_ = v___y_1426_;
v___y_1345_ = v___y_1427_;
v___y_1346_ = v___y_1426_;
goto v___jp_1343_;
}
else
{
uint64_t v___x_1472_; uint64_t v___x_1473_; uint8_t v___x_1474_; 
v___x_1472_ = 9223372036854775808ULL;
v___x_1473_ = lean_unbox_uint64(v___y_1423_);
lean_dec(v___y_1423_);
v___x_1474_ = lean_uint64_dec_lt(v___x_1472_, v___x_1473_);
if (v___x_1474_ == 0)
{
v___y_1344_ = v___y_1426_;
v___y_1345_ = v___y_1427_;
v___y_1346_ = v___y_1426_;
goto v___jp_1343_;
}
else
{
uint64_t v___x_1475_; 
v___x_1475_ = 1ULL;
v___y_1344_ = v___y_1426_;
v___y_1345_ = v___y_1427_;
v___y_1346_ = v___x_1475_;
goto v___jp_1343_;
}
}
}
else
{
uint64_t v___x_1476_; uint64_t v_quotient_1477_; uint64_t v___x_1478_; uint64_t v___x_1479_; uint64_t v___x_1480_; uint64_t v___x_1481_; uint64_t v_remainder_1482_; uint64_t v___x_1483_; uint64_t v_half_1484_; uint8_t v___x_1485_; 
v___x_1476_ = lean_unbox_uint64(v___y_1423_);
v_quotient_1477_ = lean_uint64_shift_right(v___x_1476_, v___x_1467_);
v___x_1478_ = 1ULL;
v___x_1479_ = lean_uint64_shift_left(v___x_1478_, v___x_1467_);
v___x_1480_ = lean_uint64_sub(v___x_1479_, v___x_1478_);
v___x_1481_ = lean_unbox_uint64(v___y_1423_);
lean_dec(v___y_1423_);
v_remainder_1482_ = lean_uint64_land(v___x_1481_, v___x_1480_);
v___x_1483_ = lean_uint64_sub(v___x_1467_, v___x_1478_);
v_half_1484_ = lean_uint64_shift_left(v___x_1478_, v___x_1483_);
v___x_1485_ = lean_uint64_dec_lt(v_remainder_1482_, v_half_1484_);
if (v___x_1485_ == 0)
{
uint8_t v___x_1486_; 
v___x_1486_ = lean_uint64_dec_lt(v_half_1484_, v_remainder_1482_);
if (v___x_1486_ == 0)
{
uint64_t v___x_1487_; uint8_t v___x_1488_; 
v___x_1487_ = lean_uint64_land(v_quotient_1477_, v___x_1478_);
v___x_1488_ = lean_uint64_dec_eq(v___x_1487_, v___y_1426_);
if (v___x_1488_ == 0)
{
uint64_t v___x_1489_; 
v___x_1489_ = lean_uint64_add(v_quotient_1477_, v___x_1478_);
v___y_1344_ = v___y_1426_;
v___y_1345_ = v___y_1427_;
v___y_1346_ = v___x_1489_;
goto v___jp_1343_;
}
else
{
v___y_1344_ = v___y_1426_;
v___y_1345_ = v___y_1427_;
v___y_1346_ = v_quotient_1477_;
goto v___jp_1343_;
}
}
else
{
uint64_t v___x_1490_; 
v___x_1490_ = lean_uint64_add(v_quotient_1477_, v___x_1478_);
v___y_1344_ = v___y_1426_;
v___y_1345_ = v___y_1427_;
v___y_1346_ = v___x_1490_;
goto v___jp_1343_;
}
}
else
{
v___y_1344_ = v___y_1426_;
v___y_1345_ = v___y_1427_;
v___y_1346_ = v_quotient_1477_;
goto v___jp_1343_;
}
}
}
else
{
uint64_t v___x_1491_; 
v___x_1491_ = lean_unbox_uint64(v___y_1423_);
lean_dec(v___y_1423_);
v___y_1344_ = v___y_1426_;
v___y_1345_ = v___y_1427_;
v___y_1346_ = v___x_1491_;
goto v___jp_1343_;
}
}
}
}
v___jp_1492_:
{
uint64_t v___x_1502_; uint64_t v___x_1503_; uint8_t v___x_1504_; 
v___x_1502_ = 1ULL;
v___x_1503_ = lean_uint64_shift_right(v___y_1500_, v___x_1502_);
v___x_1504_ = lean_uint64_dec_eq(v___x_1503_, v___y_1497_);
if (v___x_1504_ == 0)
{
uint64_t v___x_1505_; 
v___x_1505_ = lean_uint64_add(v___y_1501_, v___x_1502_);
v___y_1422_ = v___y_1493_;
v___y_1423_ = v___y_1495_;
v___y_1424_ = v___y_1494_;
v___y_1425_ = v___y_1496_;
v___y_1426_ = v___y_1497_;
v___y_1427_ = v___y_1499_;
v___y_1428_ = v___y_1498_;
v___y_1429_ = v___x_1505_;
goto v___jp_1421_;
}
else
{
v___y_1422_ = v___y_1493_;
v___y_1423_ = v___y_1495_;
v___y_1424_ = v___y_1494_;
v___y_1425_ = v___y_1496_;
v___y_1426_ = v___y_1497_;
v___y_1427_ = v___y_1499_;
v___y_1428_ = v___y_1498_;
v___y_1429_ = v___y_1501_;
goto v___jp_1421_;
}
}
v___jp_1506_:
{
uint64_t v___x_1518_; uint8_t v___x_1519_; 
v___x_1518_ = lean_uint64_shift_right(v___y_1509_, v___y_1507_);
v___x_1519_ = lean_uint64_dec_eq(v___x_1518_, v___y_1513_);
if (v___x_1519_ == 0)
{
uint64_t v___x_1520_; 
v___x_1520_ = lean_uint64_add(v___y_1512_, v___y_1507_);
v___y_1493_ = v___y_1508_;
v___y_1494_ = v___y_1511_;
v___y_1495_ = v___y_1510_;
v___y_1496_ = v___y_1514_;
v___y_1497_ = v___y_1513_;
v___y_1498_ = v___y_1516_;
v___y_1499_ = v___y_1515_;
v___y_1500_ = v___y_1517_;
v___y_1501_ = v___x_1520_;
goto v___jp_1492_;
}
else
{
v___y_1493_ = v___y_1508_;
v___y_1494_ = v___y_1511_;
v___y_1495_ = v___y_1510_;
v___y_1496_ = v___y_1514_;
v___y_1497_ = v___y_1513_;
v___y_1498_ = v___y_1516_;
v___y_1499_ = v___y_1515_;
v___y_1500_ = v___y_1517_;
v___y_1501_ = v___y_1512_;
goto v___jp_1492_;
}
}
v___jp_1521_:
{
uint64_t v___x_1531_; uint64_t v___x_1532_; uint8_t v___x_1533_; 
v___x_1531_ = 2ULL;
v___x_1532_ = lean_uint64_shift_right(v___y_1523_, v___x_1531_);
v___x_1533_ = lean_uint64_dec_eq(v___x_1532_, v___y_1527_);
if (v___x_1533_ == 0)
{
v___y_1507_ = v___x_1531_;
v___y_1508_ = v___y_1522_;
v___y_1509_ = v___y_1523_;
v___y_1510_ = v___y_1525_;
v___y_1511_ = v___y_1524_;
v___y_1512_ = v___y_1530_;
v___y_1513_ = v___y_1527_;
v___y_1514_ = v___y_1526_;
v___y_1515_ = v___y_1529_;
v___y_1516_ = v___y_1528_;
v___y_1517_ = v___x_1532_;
goto v___jp_1506_;
}
else
{
v___y_1507_ = v___x_1531_;
v___y_1508_ = v___y_1522_;
v___y_1509_ = v___y_1523_;
v___y_1510_ = v___y_1525_;
v___y_1511_ = v___y_1524_;
v___y_1512_ = v___y_1530_;
v___y_1513_ = v___y_1527_;
v___y_1514_ = v___y_1526_;
v___y_1515_ = v___y_1529_;
v___y_1516_ = v___y_1528_;
v___y_1517_ = v___y_1523_;
goto v___jp_1506_;
}
}
v___jp_1534_:
{
uint64_t v___x_1546_; uint8_t v___x_1547_; 
v___x_1546_ = lean_uint64_shift_right(v___y_1537_, v___y_1536_);
v___x_1547_ = lean_uint64_dec_eq(v___x_1546_, v___y_1541_);
if (v___x_1547_ == 0)
{
uint64_t v___x_1548_; 
v___x_1548_ = lean_uint64_add(v___y_1538_, v___y_1536_);
v___y_1522_ = v___y_1535_;
v___y_1523_ = v___y_1545_;
v___y_1524_ = v___y_1540_;
v___y_1525_ = v___y_1539_;
v___y_1526_ = v___y_1542_;
v___y_1527_ = v___y_1541_;
v___y_1528_ = v___y_1544_;
v___y_1529_ = v___y_1543_;
v___y_1530_ = v___x_1548_;
goto v___jp_1521_;
}
else
{
v___y_1522_ = v___y_1535_;
v___y_1523_ = v___y_1545_;
v___y_1524_ = v___y_1540_;
v___y_1525_ = v___y_1539_;
v___y_1526_ = v___y_1542_;
v___y_1527_ = v___y_1541_;
v___y_1528_ = v___y_1544_;
v___y_1529_ = v___y_1543_;
v___y_1530_ = v___y_1538_;
goto v___jp_1521_;
}
}
v___jp_1549_:
{
uint64_t v___x_1559_; uint64_t v___x_1560_; uint8_t v___x_1561_; 
v___x_1559_ = 4ULL;
v___x_1560_ = lean_uint64_shift_right(v___y_1551_, v___x_1559_);
v___x_1561_ = lean_uint64_dec_eq(v___x_1560_, v___y_1555_);
if (v___x_1561_ == 0)
{
v___y_1535_ = v___y_1550_;
v___y_1536_ = v___x_1559_;
v___y_1537_ = v___y_1551_;
v___y_1538_ = v___y_1558_;
v___y_1539_ = v___y_1553_;
v___y_1540_ = v___y_1552_;
v___y_1541_ = v___y_1555_;
v___y_1542_ = v___y_1554_;
v___y_1543_ = v___y_1557_;
v___y_1544_ = v___y_1556_;
v___y_1545_ = v___x_1560_;
goto v___jp_1534_;
}
else
{
v___y_1535_ = v___y_1550_;
v___y_1536_ = v___x_1559_;
v___y_1537_ = v___y_1551_;
v___y_1538_ = v___y_1558_;
v___y_1539_ = v___y_1553_;
v___y_1540_ = v___y_1552_;
v___y_1541_ = v___y_1555_;
v___y_1542_ = v___y_1554_;
v___y_1543_ = v___y_1557_;
v___y_1544_ = v___y_1556_;
v___y_1545_ = v___y_1551_;
goto v___jp_1534_;
}
}
v___jp_1562_:
{
uint64_t v___x_1574_; uint8_t v___x_1575_; 
v___x_1574_ = lean_uint64_shift_right(v___y_1564_, v___y_1565_);
v___x_1575_ = lean_uint64_dec_eq(v___x_1574_, v___y_1568_);
if (v___x_1575_ == 0)
{
uint64_t v___x_1576_; 
v___x_1576_ = lean_uint64_add(v___y_1570_, v___y_1565_);
v___y_1550_ = v___y_1563_;
v___y_1551_ = v___y_1573_;
v___y_1552_ = v___y_1567_;
v___y_1553_ = v___y_1566_;
v___y_1554_ = v___y_1569_;
v___y_1555_ = v___y_1568_;
v___y_1556_ = v___y_1572_;
v___y_1557_ = v___y_1571_;
v___y_1558_ = v___x_1576_;
goto v___jp_1549_;
}
else
{
v___y_1550_ = v___y_1563_;
v___y_1551_ = v___y_1573_;
v___y_1552_ = v___y_1567_;
v___y_1553_ = v___y_1566_;
v___y_1554_ = v___y_1569_;
v___y_1555_ = v___y_1568_;
v___y_1556_ = v___y_1572_;
v___y_1557_ = v___y_1571_;
v___y_1558_ = v___y_1570_;
goto v___jp_1549_;
}
}
v___jp_1577_:
{
uint64_t v___x_1587_; uint64_t v___x_1588_; uint8_t v___x_1589_; 
v___x_1587_ = 8ULL;
v___x_1588_ = lean_uint64_shift_right(v___y_1579_, v___x_1587_);
v___x_1589_ = lean_uint64_dec_eq(v___x_1588_, v___y_1583_);
if (v___x_1589_ == 0)
{
v___y_1563_ = v___y_1578_;
v___y_1564_ = v___y_1579_;
v___y_1565_ = v___x_1587_;
v___y_1566_ = v___y_1581_;
v___y_1567_ = v___y_1580_;
v___y_1568_ = v___y_1583_;
v___y_1569_ = v___y_1582_;
v___y_1570_ = v___y_1586_;
v___y_1571_ = v___y_1585_;
v___y_1572_ = v___y_1584_;
v___y_1573_ = v___x_1588_;
goto v___jp_1562_;
}
else
{
v___y_1563_ = v___y_1578_;
v___y_1564_ = v___y_1579_;
v___y_1565_ = v___x_1587_;
v___y_1566_ = v___y_1581_;
v___y_1567_ = v___y_1580_;
v___y_1568_ = v___y_1583_;
v___y_1569_ = v___y_1582_;
v___y_1570_ = v___y_1586_;
v___y_1571_ = v___y_1585_;
v___y_1572_ = v___y_1584_;
v___y_1573_ = v___y_1579_;
goto v___jp_1562_;
}
}
v___jp_1590_:
{
uint64_t v___x_1602_; uint8_t v___x_1603_; 
v___x_1602_ = lean_uint64_shift_right(v___y_1600_, v___y_1599_);
v___x_1603_ = lean_uint64_dec_eq(v___x_1602_, v___y_1595_);
if (v___x_1603_ == 0)
{
uint64_t v___x_1604_; 
v___x_1604_ = lean_uint64_add(v___y_1592_, v___y_1599_);
v___y_1578_ = v___y_1591_;
v___y_1579_ = v___y_1601_;
v___y_1580_ = v___y_1594_;
v___y_1581_ = v___y_1593_;
v___y_1582_ = v___y_1596_;
v___y_1583_ = v___y_1595_;
v___y_1584_ = v___y_1598_;
v___y_1585_ = v___y_1597_;
v___y_1586_ = v___x_1604_;
goto v___jp_1577_;
}
else
{
v___y_1578_ = v___y_1591_;
v___y_1579_ = v___y_1601_;
v___y_1580_ = v___y_1594_;
v___y_1581_ = v___y_1593_;
v___y_1582_ = v___y_1596_;
v___y_1583_ = v___y_1595_;
v___y_1584_ = v___y_1598_;
v___y_1585_ = v___y_1597_;
v___y_1586_ = v___y_1592_;
goto v___jp_1577_;
}
}
v___jp_1605_:
{
uint64_t v___x_1615_; uint64_t v___x_1616_; uint8_t v___x_1617_; 
v___x_1615_ = 16ULL;
v___x_1616_ = lean_uint64_shift_right(v___y_1613_, v___x_1615_);
v___x_1617_ = lean_uint64_dec_eq(v___x_1616_, v___y_1610_);
if (v___x_1617_ == 0)
{
v___y_1591_ = v___y_1606_;
v___y_1592_ = v___y_1614_;
v___y_1593_ = v___y_1608_;
v___y_1594_ = v___y_1607_;
v___y_1595_ = v___y_1610_;
v___y_1596_ = v___y_1609_;
v___y_1597_ = v___y_1612_;
v___y_1598_ = v___y_1611_;
v___y_1599_ = v___x_1615_;
v___y_1600_ = v___y_1613_;
v___y_1601_ = v___x_1616_;
goto v___jp_1590_;
}
else
{
v___y_1591_ = v___y_1606_;
v___y_1592_ = v___y_1614_;
v___y_1593_ = v___y_1608_;
v___y_1594_ = v___y_1607_;
v___y_1595_ = v___y_1610_;
v___y_1596_ = v___y_1609_;
v___y_1597_ = v___y_1612_;
v___y_1598_ = v___y_1611_;
v___y_1599_ = v___x_1615_;
v___y_1600_ = v___y_1613_;
v___y_1601_ = v___y_1613_;
goto v___jp_1590_;
}
}
v___jp_1618_:
{
uint64_t v___x_1628_; uint64_t v___x_1629_; uint8_t v___x_1630_; 
v___x_1628_ = lean_unbox_uint64(v___y_1620_);
v___x_1629_ = lean_uint64_shift_right(v___x_1628_, v___y_1626_);
v___x_1630_ = lean_uint64_dec_eq(v___x_1629_, v___y_1622_);
if (v___x_1630_ == 0)
{
v___y_1606_ = v___y_1619_;
v___y_1607_ = v___y_1621_;
v___y_1608_ = v___y_1620_;
v___y_1609_ = v___y_1623_;
v___y_1610_ = v___y_1622_;
v___y_1611_ = v___y_1625_;
v___y_1612_ = v___y_1624_;
v___y_1613_ = v___y_1627_;
v___y_1614_ = v___y_1626_;
goto v___jp_1605_;
}
else
{
v___y_1606_ = v___y_1619_;
v___y_1607_ = v___y_1621_;
v___y_1608_ = v___y_1620_;
v___y_1609_ = v___y_1623_;
v___y_1610_ = v___y_1622_;
v___y_1611_ = v___y_1625_;
v___y_1612_ = v___y_1624_;
v___y_1613_ = v___y_1627_;
v___y_1614_ = v___y_1622_;
goto v___jp_1605_;
}
}
v___jp_1631_:
{
uint64_t v___x_1637_; uint64_t v___x_1638_; uint8_t v___x_1639_; 
v___x_1637_ = 0ULL;
v___x_1638_ = lean_unbox_uint64(v_snd_1636_);
v___x_1639_ = lean_uint64_dec_eq(v___x_1638_, v___x_1637_);
if (v___x_1639_ == 0)
{
uint64_t v___x_1640_; uint64_t v___x_1641_; uint64_t v___x_1642_; uint64_t v___x_1643_; uint64_t v___x_1644_; uint8_t v___x_1645_; 
v___x_1640_ = 149ULL;
v___x_1641_ = lean_uint64_add(v___y_1632_, v___x_1640_);
v___x_1642_ = 32ULL;
v___x_1643_ = lean_unbox_uint64(v_snd_1636_);
v___x_1644_ = lean_uint64_shift_right(v___x_1643_, v___x_1642_);
v___x_1645_ = lean_uint64_dec_eq(v___x_1644_, v___x_1637_);
if (v___x_1645_ == 0)
{
v___y_1619_ = v___x_1640_;
v___y_1620_ = v_snd_1636_;
v___y_1621_ = v___y_1633_;
v___y_1622_ = v___x_1637_;
v___y_1623_ = v___y_1634_;
v___y_1624_ = v_fst_1635_;
v___y_1625_ = v___x_1641_;
v___y_1626_ = v___x_1642_;
v___y_1627_ = v___x_1644_;
goto v___jp_1618_;
}
else
{
uint64_t v___x_1646_; 
v___x_1646_ = lean_unbox_uint64(v_snd_1636_);
v___y_1619_ = v___x_1640_;
v___y_1620_ = v_snd_1636_;
v___y_1621_ = v___y_1633_;
v___y_1622_ = v___x_1637_;
v___y_1623_ = v___y_1634_;
v___y_1624_ = v_fst_1635_;
v___y_1625_ = v___x_1641_;
v___y_1626_ = v___x_1642_;
v___y_1627_ = v___x_1646_;
goto v___jp_1618_;
}
}
else
{
uint8_t v___x_1647_; 
lean_dec(v_snd_1636_);
v___x_1647_ = lean_unbox(v_fst_1635_);
lean_dec(v_fst_1635_);
if (v___x_1647_ == 0)
{
uint32_t v___x_1648_; 
v___x_1648_ = 0;
return v___x_1648_;
}
else
{
uint32_t v___x_1649_; 
v___x_1649_ = 2147483648;
return v___x_1649_;
}
}
}
v___jp_1650_:
{
uint32_t v___x_1653_; uint32_t v___x_1654_; uint32_t v___x_1655_; 
v___x_1653_ = 8388607;
v___x_1654_ = lean_uint32_land(v___y_1651_, v___x_1653_);
v___x_1655_ = lean_uint32_lor(v___y_1652_, v___x_1654_);
return v___x_1655_;
}
v___jp_1656_:
{
uint8_t v___x_1660_; 
v___x_1660_ = lean_uint64_dec_eq(v___y_1659_, v___y_1657_);
if (v___x_1660_ == 0)
{
uint64_t v___x_1661_; uint8_t v___x_1662_; 
v___x_1661_ = 8388608ULL;
v___x_1662_ = lean_uint64_dec_eq(v___y_1659_, v___x_1661_);
if (v___x_1662_ == 0)
{
uint32_t v___x_1663_; uint8_t v___x_1664_; 
v___x_1663_ = lean_uint64_to_uint32(v___y_1659_);
v___x_1664_ = lean_unbox(v___y_1658_);
lean_dec(v___y_1658_);
if (v___x_1664_ == 0)
{
uint32_t v___x_1665_; 
v___x_1665_ = 0;
v___y_1651_ = v___x_1663_;
v___y_1652_ = v___x_1665_;
goto v___jp_1650_;
}
else
{
uint32_t v___x_1666_; 
v___x_1666_ = 2147483648;
v___y_1651_ = v___x_1663_;
v___y_1652_ = v___x_1666_;
goto v___jp_1650_;
}
}
else
{
uint8_t v___x_1667_; 
v___x_1667_ = lean_unbox(v___y_1658_);
lean_dec(v___y_1658_);
if (v___x_1667_ == 0)
{
uint32_t v___x_1668_; 
v___x_1668_ = 0;
v___y_1330_ = v___x_1668_;
goto v___jp_1329_;
}
else
{
uint32_t v___x_1669_; 
v___x_1669_ = 2147483648;
v___y_1330_ = v___x_1669_;
goto v___jp_1329_;
}
}
}
else
{
uint8_t v___x_1670_; 
v___x_1670_ = lean_unbox(v___y_1658_);
lean_dec(v___y_1658_);
if (v___x_1670_ == 0)
{
uint32_t v___x_1671_; 
v___x_1671_ = 0;
return v___x_1671_;
}
else
{
uint32_t v___x_1672_; 
v___x_1672_ = 2147483648;
return v___x_1672_;
}
}
}
v___jp_1673_:
{
uint32_t v___x_1679_; uint32_t v___x_1680_; uint32_t v___x_1681_; uint32_t v___x_1682_; uint32_t v___x_1683_; uint32_t v___x_1684_; 
v___x_1679_ = lean_uint32_land(v___y_1674_, v___y_1677_);
v___x_1680_ = lean_uint32_shift_left(v___x_1679_, v___y_1676_);
v___x_1681_ = lean_uint32_lor(v___y_1678_, v___x_1680_);
v___x_1682_ = 8388607;
v___x_1683_ = lean_uint32_land(v___y_1675_, v___x_1682_);
v___x_1684_ = lean_uint32_lor(v___x_1681_, v___x_1683_);
return v___x_1684_;
}
v___jp_1685_:
{
uint8_t v___x_1691_; 
v___x_1691_ = lean_unbox(v___y_1689_);
lean_dec(v___y_1689_);
if (v___x_1691_ == 0)
{
uint32_t v___x_1692_; 
v___x_1692_ = 0;
v___y_1674_ = v___y_1686_;
v___y_1675_ = v___y_1690_;
v___y_1676_ = v___y_1687_;
v___y_1677_ = v___y_1688_;
v___y_1678_ = v___x_1692_;
goto v___jp_1673_;
}
else
{
uint32_t v___x_1693_; 
v___x_1693_ = 2147483648;
v___y_1674_ = v___y_1686_;
v___y_1675_ = v___y_1690_;
v___y_1676_ = v___y_1687_;
v___y_1677_ = v___y_1688_;
v___y_1678_ = v___x_1693_;
goto v___jp_1673_;
}
}
v___jp_1694_:
{
uint64_t v___x_1701_; uint64_t v_encodedExponent_1702_; uint32_t v___x_1703_; uint64_t v___x_1704_; uint8_t v___x_1705_; 
v___x_1701_ = 171ULL;
v_encodedExponent_1702_ = lean_uint64_sub(v___y_1699_, v___x_1701_);
v___x_1703_ = lean_uint64_to_uint32(v_encodedExponent_1702_);
v___x_1704_ = 8388608ULL;
v___x_1705_ = lean_uint64_dec_lt(v___y_1700_, v___x_1704_);
if (v___x_1705_ == 0)
{
uint64_t v___x_1706_; uint32_t v___x_1707_; 
v___x_1706_ = lean_uint64_sub(v___y_1700_, v___x_1704_);
v___x_1707_ = lean_uint64_to_uint32(v___x_1706_);
v___y_1686_ = v___x_1703_;
v___y_1687_ = v___y_1696_;
v___y_1688_ = v___y_1697_;
v___y_1689_ = v___y_1698_;
v___y_1690_ = v___x_1707_;
goto v___jp_1685_;
}
else
{
uint32_t v___x_1708_; 
v___x_1708_ = lean_uint64_to_uint32(v___y_1695_);
v___y_1686_ = v___x_1703_;
v___y_1687_ = v___y_1696_;
v___y_1688_ = v___y_1697_;
v___y_1689_ = v___y_1698_;
v___y_1690_ = v___x_1708_;
goto v___jp_1685_;
}
}
v___jp_1709_:
{
uint64_t v___x_1717_; uint8_t v___x_1718_; 
v___x_1717_ = 425ULL;
v___x_1718_ = lean_uint64_dec_lt(v___x_1717_, v___y_1716_);
if (v___x_1718_ == 0)
{
if (v___y_1710_ == 0)
{
v___y_1695_ = v___y_1712_;
v___y_1696_ = v___y_1711_;
v___y_1697_ = v___y_1714_;
v___y_1698_ = v___y_1715_;
v___y_1699_ = v___y_1716_;
v___y_1700_ = v___y_1713_;
goto v___jp_1694_;
}
else
{
uint64_t v___x_1719_; 
v___x_1719_ = 8388608ULL;
v___y_1695_ = v___y_1712_;
v___y_1696_ = v___y_1711_;
v___y_1697_ = v___y_1714_;
v___y_1698_ = v___y_1715_;
v___y_1699_ = v___y_1716_;
v___y_1700_ = v___x_1719_;
goto v___jp_1694_;
}
}
else
{
uint8_t v___x_1720_; 
v___x_1720_ = lean_unbox(v___y_1715_);
lean_dec(v___y_1715_);
if (v___x_1720_ == 0)
{
uint32_t v___x_1721_; 
v___x_1721_ = 2139095040;
return v___x_1721_;
}
else
{
uint32_t v___x_1722_; 
v___x_1722_ = 4286578688;
return v___x_1722_;
}
}
}
v___jp_1723_:
{
uint64_t v___x_1730_; uint8_t v_carry_1731_; 
v___x_1730_ = 16777216ULL;
v_carry_1731_ = lean_uint64_dec_eq(v___y_1729_, v___x_1730_);
if (v_carry_1731_ == 0)
{
v___y_1710_ = v_carry_1731_;
v___y_1711_ = v___y_1726_;
v___y_1712_ = v___y_1725_;
v___y_1713_ = v___y_1729_;
v___y_1714_ = v___y_1727_;
v___y_1715_ = v___y_1728_;
v___y_1716_ = v___y_1724_;
goto v___jp_1709_;
}
else
{
uint64_t v___x_1732_; uint64_t v___x_1733_; 
v___x_1732_ = 1ULL;
v___x_1733_ = lean_uint64_add(v___y_1724_, v___x_1732_);
v___y_1710_ = v_carry_1731_;
v___y_1711_ = v___y_1726_;
v___y_1712_ = v___y_1725_;
v___y_1713_ = v___y_1729_;
v___y_1714_ = v___y_1727_;
v___y_1715_ = v___y_1728_;
v___y_1716_ = v___x_1733_;
goto v___jp_1709_;
}
}
v___jp_1734_:
{
uint64_t v_position_1743_; uint64_t v___x_1744_; uint8_t v___x_1745_; 
v_position_1743_ = lean_uint64_add(v___y_1742_, v___y_1736_);
v___x_1744_ = 172ULL;
v___x_1745_ = lean_uint64_dec_lt(v_position_1743_, v___x_1744_);
if (v___x_1745_ == 0)
{
uint64_t v___x_1746_; uint8_t v___x_1747_; 
v___x_1746_ = 23ULL;
v___x_1747_ = lean_uint64_dec_lt(v___y_1742_, v___x_1746_);
if (v___x_1747_ == 0)
{
uint64_t v___x_1748_; uint8_t v___x_1749_; 
v___x_1748_ = lean_uint64_sub(v___y_1742_, v___x_1746_);
v___x_1749_ = lean_uint64_dec_eq(v___x_1748_, v___y_1739_);
if (v___x_1749_ == 0)
{
uint64_t v___x_1750_; uint8_t v___x_1751_; 
v___x_1750_ = 64ULL;
v___x_1751_ = lean_uint64_dec_lt(v___x_1748_, v___x_1750_);
if (v___x_1751_ == 0)
{
uint8_t v___x_1752_; 
v___x_1752_ = lean_uint64_dec_eq(v___x_1748_, v___x_1750_);
if (v___x_1752_ == 0)
{
lean_dec(v___y_1737_);
v___y_1724_ = v_position_1743_;
v___y_1725_ = v___y_1739_;
v___y_1726_ = v___y_1738_;
v___y_1727_ = v___y_1740_;
v___y_1728_ = v___y_1741_;
v___y_1729_ = v___y_1739_;
goto v___jp_1723_;
}
else
{
uint64_t v___x_1753_; uint64_t v___x_1754_; uint8_t v___x_1755_; 
v___x_1753_ = 9223372036854775808ULL;
v___x_1754_ = lean_unbox_uint64(v___y_1737_);
lean_dec(v___y_1737_);
v___x_1755_ = lean_uint64_dec_lt(v___x_1753_, v___x_1754_);
if (v___x_1755_ == 0)
{
v___y_1724_ = v_position_1743_;
v___y_1725_ = v___y_1739_;
v___y_1726_ = v___y_1738_;
v___y_1727_ = v___y_1740_;
v___y_1728_ = v___y_1741_;
v___y_1729_ = v___y_1739_;
goto v___jp_1723_;
}
else
{
uint64_t v___x_1756_; 
v___x_1756_ = 1ULL;
v___y_1724_ = v_position_1743_;
v___y_1725_ = v___y_1739_;
v___y_1726_ = v___y_1738_;
v___y_1727_ = v___y_1740_;
v___y_1728_ = v___y_1741_;
v___y_1729_ = v___x_1756_;
goto v___jp_1723_;
}
}
}
else
{
uint64_t v___x_1757_; uint64_t v_quotient_1758_; uint64_t v___x_1759_; uint64_t v___x_1760_; uint64_t v___x_1761_; uint64_t v___x_1762_; uint64_t v_remainder_1763_; uint64_t v___x_1764_; uint64_t v_half_1765_; uint8_t v___x_1766_; 
v___x_1757_ = lean_unbox_uint64(v___y_1737_);
v_quotient_1758_ = lean_uint64_shift_right(v___x_1757_, v___x_1748_);
v___x_1759_ = 1ULL;
v___x_1760_ = lean_uint64_shift_left(v___x_1759_, v___x_1748_);
v___x_1761_ = lean_uint64_sub(v___x_1760_, v___x_1759_);
v___x_1762_ = lean_unbox_uint64(v___y_1737_);
lean_dec(v___y_1737_);
v_remainder_1763_ = lean_uint64_land(v___x_1762_, v___x_1761_);
v___x_1764_ = lean_uint64_sub(v___x_1748_, v___x_1759_);
v_half_1765_ = lean_uint64_shift_left(v___x_1759_, v___x_1764_);
v___x_1766_ = lean_uint64_dec_lt(v_remainder_1763_, v_half_1765_);
if (v___x_1766_ == 0)
{
uint8_t v___x_1767_; 
v___x_1767_ = lean_uint64_dec_lt(v_half_1765_, v_remainder_1763_);
if (v___x_1767_ == 0)
{
uint64_t v___x_1768_; uint8_t v___x_1769_; 
v___x_1768_ = lean_uint64_land(v_quotient_1758_, v___x_1759_);
v___x_1769_ = lean_uint64_dec_eq(v___x_1768_, v___y_1739_);
if (v___x_1769_ == 0)
{
uint64_t v___x_1770_; 
v___x_1770_ = lean_uint64_add(v_quotient_1758_, v___x_1759_);
v___y_1724_ = v_position_1743_;
v___y_1725_ = v___y_1739_;
v___y_1726_ = v___y_1738_;
v___y_1727_ = v___y_1740_;
v___y_1728_ = v___y_1741_;
v___y_1729_ = v___x_1770_;
goto v___jp_1723_;
}
else
{
v___y_1724_ = v_position_1743_;
v___y_1725_ = v___y_1739_;
v___y_1726_ = v___y_1738_;
v___y_1727_ = v___y_1740_;
v___y_1728_ = v___y_1741_;
v___y_1729_ = v_quotient_1758_;
goto v___jp_1723_;
}
}
else
{
uint64_t v___x_1771_; 
v___x_1771_ = lean_uint64_add(v_quotient_1758_, v___x_1759_);
v___y_1724_ = v_position_1743_;
v___y_1725_ = v___y_1739_;
v___y_1726_ = v___y_1738_;
v___y_1727_ = v___y_1740_;
v___y_1728_ = v___y_1741_;
v___y_1729_ = v___x_1771_;
goto v___jp_1723_;
}
}
else
{
v___y_1724_ = v_position_1743_;
v___y_1725_ = v___y_1739_;
v___y_1726_ = v___y_1738_;
v___y_1727_ = v___y_1740_;
v___y_1728_ = v___y_1741_;
v___y_1729_ = v_quotient_1758_;
goto v___jp_1723_;
}
}
}
else
{
uint64_t v___x_1772_; 
v___x_1772_ = lean_unbox_uint64(v___y_1737_);
lean_dec(v___y_1737_);
v___y_1724_ = v_position_1743_;
v___y_1725_ = v___y_1739_;
v___y_1726_ = v___y_1738_;
v___y_1727_ = v___y_1740_;
v___y_1728_ = v___y_1741_;
v___y_1729_ = v___x_1772_;
goto v___jp_1723_;
}
}
else
{
uint64_t v___x_1773_; uint64_t v___x_1774_; uint64_t v___x_1775_; 
v___x_1773_ = lean_uint64_sub(v___x_1746_, v___y_1742_);
v___x_1774_ = lean_unbox_uint64(v___y_1737_);
lean_dec(v___y_1737_);
v___x_1775_ = lean_uint64_shift_left(v___x_1774_, v___x_1773_);
v___y_1724_ = v_position_1743_;
v___y_1725_ = v___y_1739_;
v___y_1726_ = v___y_1738_;
v___y_1727_ = v___y_1740_;
v___y_1728_ = v___y_1741_;
v___y_1729_ = v___x_1775_;
goto v___jp_1723_;
}
}
else
{
uint8_t v___x_1776_; 
v___x_1776_ = lean_uint64_dec_lt(v___y_1736_, v___y_1735_);
if (v___x_1776_ == 0)
{
uint64_t v___x_1777_; uint64_t v___x_1778_; uint64_t v___x_1779_; 
v___x_1777_ = lean_uint64_sub(v___y_1736_, v___y_1735_);
v___x_1778_ = lean_unbox_uint64(v___y_1737_);
lean_dec(v___y_1737_);
v___x_1779_ = lean_uint64_shift_left(v___x_1778_, v___x_1777_);
v___y_1657_ = v___y_1739_;
v___y_1658_ = v___y_1741_;
v___y_1659_ = v___x_1779_;
goto v___jp_1656_;
}
else
{
uint64_t v___x_1780_; uint8_t v___x_1781_; 
v___x_1780_ = lean_uint64_sub(v___y_1735_, v___y_1736_);
v___x_1781_ = lean_uint64_dec_eq(v___x_1780_, v___y_1739_);
if (v___x_1781_ == 0)
{
uint64_t v___x_1782_; uint8_t v___x_1783_; 
v___x_1782_ = 64ULL;
v___x_1783_ = lean_uint64_dec_lt(v___x_1780_, v___x_1782_);
if (v___x_1783_ == 0)
{
uint8_t v___x_1784_; 
v___x_1784_ = lean_uint64_dec_eq(v___x_1780_, v___x_1782_);
if (v___x_1784_ == 0)
{
lean_dec(v___y_1737_);
v___y_1657_ = v___y_1739_;
v___y_1658_ = v___y_1741_;
v___y_1659_ = v___y_1739_;
goto v___jp_1656_;
}
else
{
uint64_t v___x_1785_; uint64_t v___x_1786_; uint8_t v___x_1787_; 
v___x_1785_ = 9223372036854775808ULL;
v___x_1786_ = lean_unbox_uint64(v___y_1737_);
lean_dec(v___y_1737_);
v___x_1787_ = lean_uint64_dec_lt(v___x_1785_, v___x_1786_);
if (v___x_1787_ == 0)
{
v___y_1657_ = v___y_1739_;
v___y_1658_ = v___y_1741_;
v___y_1659_ = v___y_1739_;
goto v___jp_1656_;
}
else
{
uint64_t v___x_1788_; 
v___x_1788_ = 1ULL;
v___y_1657_ = v___y_1739_;
v___y_1658_ = v___y_1741_;
v___y_1659_ = v___x_1788_;
goto v___jp_1656_;
}
}
}
else
{
uint64_t v___x_1789_; uint64_t v_quotient_1790_; uint64_t v___x_1791_; uint64_t v___x_1792_; uint64_t v___x_1793_; uint64_t v___x_1794_; uint64_t v_remainder_1795_; uint64_t v___x_1796_; uint64_t v_half_1797_; uint8_t v___x_1798_; 
v___x_1789_ = lean_unbox_uint64(v___y_1737_);
v_quotient_1790_ = lean_uint64_shift_right(v___x_1789_, v___x_1780_);
v___x_1791_ = 1ULL;
v___x_1792_ = lean_uint64_shift_left(v___x_1791_, v___x_1780_);
v___x_1793_ = lean_uint64_sub(v___x_1792_, v___x_1791_);
v___x_1794_ = lean_unbox_uint64(v___y_1737_);
lean_dec(v___y_1737_);
v_remainder_1795_ = lean_uint64_land(v___x_1794_, v___x_1793_);
v___x_1796_ = lean_uint64_sub(v___x_1780_, v___x_1791_);
v_half_1797_ = lean_uint64_shift_left(v___x_1791_, v___x_1796_);
v___x_1798_ = lean_uint64_dec_lt(v_remainder_1795_, v_half_1797_);
if (v___x_1798_ == 0)
{
uint8_t v___x_1799_; 
v___x_1799_ = lean_uint64_dec_lt(v_half_1797_, v_remainder_1795_);
if (v___x_1799_ == 0)
{
uint64_t v___x_1800_; uint8_t v___x_1801_; 
v___x_1800_ = lean_uint64_land(v_quotient_1790_, v___x_1791_);
v___x_1801_ = lean_uint64_dec_eq(v___x_1800_, v___y_1739_);
if (v___x_1801_ == 0)
{
uint64_t v___x_1802_; 
v___x_1802_ = lean_uint64_add(v_quotient_1790_, v___x_1791_);
v___y_1657_ = v___y_1739_;
v___y_1658_ = v___y_1741_;
v___y_1659_ = v___x_1802_;
goto v___jp_1656_;
}
else
{
v___y_1657_ = v___y_1739_;
v___y_1658_ = v___y_1741_;
v___y_1659_ = v_quotient_1790_;
goto v___jp_1656_;
}
}
else
{
uint64_t v___x_1803_; 
v___x_1803_ = lean_uint64_add(v_quotient_1790_, v___x_1791_);
v___y_1657_ = v___y_1739_;
v___y_1658_ = v___y_1741_;
v___y_1659_ = v___x_1803_;
goto v___jp_1656_;
}
}
else
{
v___y_1657_ = v___y_1739_;
v___y_1658_ = v___y_1741_;
v___y_1659_ = v_quotient_1790_;
goto v___jp_1656_;
}
}
}
else
{
uint64_t v___x_1804_; 
v___x_1804_ = lean_unbox_uint64(v___y_1737_);
lean_dec(v___y_1737_);
v___y_1657_ = v___y_1739_;
v___y_1658_ = v___y_1741_;
v___y_1659_ = v___x_1804_;
goto v___jp_1656_;
}
}
}
}
v___jp_1805_:
{
uint64_t v___x_1815_; uint64_t v___x_1816_; uint8_t v___x_1817_; 
v___x_1815_ = 1ULL;
v___x_1816_ = lean_uint64_shift_right(v___y_1807_, v___x_1815_);
v___x_1817_ = lean_uint64_dec_eq(v___x_1816_, v___y_1811_);
if (v___x_1817_ == 0)
{
uint64_t v___x_1818_; 
v___x_1818_ = lean_uint64_add(v___y_1814_, v___x_1815_);
v___y_1735_ = v___y_1806_;
v___y_1736_ = v___y_1808_;
v___y_1737_ = v___y_1809_;
v___y_1738_ = v___y_1810_;
v___y_1739_ = v___y_1811_;
v___y_1740_ = v___y_1812_;
v___y_1741_ = v___y_1813_;
v___y_1742_ = v___x_1818_;
goto v___jp_1734_;
}
else
{
v___y_1735_ = v___y_1806_;
v___y_1736_ = v___y_1808_;
v___y_1737_ = v___y_1809_;
v___y_1738_ = v___y_1810_;
v___y_1739_ = v___y_1811_;
v___y_1740_ = v___y_1812_;
v___y_1741_ = v___y_1813_;
v___y_1742_ = v___y_1814_;
goto v___jp_1734_;
}
}
v___jp_1819_:
{
uint64_t v___x_1831_; uint8_t v___x_1832_; 
v___x_1831_ = lean_uint64_shift_right(v___y_1821_, v___y_1825_);
v___x_1832_ = lean_uint64_dec_eq(v___x_1831_, v___y_1826_);
if (v___x_1832_ == 0)
{
uint64_t v___x_1833_; 
v___x_1833_ = lean_uint64_add(v___y_1822_, v___y_1825_);
v___y_1806_ = v___y_1820_;
v___y_1807_ = v___y_1830_;
v___y_1808_ = v___y_1823_;
v___y_1809_ = v___y_1824_;
v___y_1810_ = v___y_1827_;
v___y_1811_ = v___y_1826_;
v___y_1812_ = v___y_1828_;
v___y_1813_ = v___y_1829_;
v___y_1814_ = v___x_1833_;
goto v___jp_1805_;
}
else
{
v___y_1806_ = v___y_1820_;
v___y_1807_ = v___y_1830_;
v___y_1808_ = v___y_1823_;
v___y_1809_ = v___y_1824_;
v___y_1810_ = v___y_1827_;
v___y_1811_ = v___y_1826_;
v___y_1812_ = v___y_1828_;
v___y_1813_ = v___y_1829_;
v___y_1814_ = v___y_1822_;
goto v___jp_1805_;
}
}
v___jp_1834_:
{
uint64_t v___x_1844_; uint64_t v___x_1845_; uint8_t v___x_1846_; 
v___x_1844_ = 2ULL;
v___x_1845_ = lean_uint64_shift_right(v___y_1836_, v___x_1844_);
v___x_1846_ = lean_uint64_dec_eq(v___x_1845_, v___y_1840_);
if (v___x_1846_ == 0)
{
v___y_1820_ = v___y_1835_;
v___y_1821_ = v___y_1836_;
v___y_1822_ = v___y_1843_;
v___y_1823_ = v___y_1837_;
v___y_1824_ = v___y_1838_;
v___y_1825_ = v___x_1844_;
v___y_1826_ = v___y_1840_;
v___y_1827_ = v___y_1839_;
v___y_1828_ = v___y_1841_;
v___y_1829_ = v___y_1842_;
v___y_1830_ = v___x_1845_;
goto v___jp_1819_;
}
else
{
v___y_1820_ = v___y_1835_;
v___y_1821_ = v___y_1836_;
v___y_1822_ = v___y_1843_;
v___y_1823_ = v___y_1837_;
v___y_1824_ = v___y_1838_;
v___y_1825_ = v___x_1844_;
v___y_1826_ = v___y_1840_;
v___y_1827_ = v___y_1839_;
v___y_1828_ = v___y_1841_;
v___y_1829_ = v___y_1842_;
v___y_1830_ = v___y_1836_;
goto v___jp_1819_;
}
}
v___jp_1847_:
{
uint64_t v___x_1859_; uint8_t v___x_1860_; 
v___x_1859_ = lean_uint64_shift_right(v___y_1852_, v___y_1850_);
v___x_1860_ = lean_uint64_dec_eq(v___x_1859_, v___y_1854_);
if (v___x_1860_ == 0)
{
uint64_t v___x_1861_; 
v___x_1861_ = lean_uint64_add(v___y_1849_, v___y_1850_);
v___y_1835_ = v___y_1848_;
v___y_1836_ = v___y_1858_;
v___y_1837_ = v___y_1851_;
v___y_1838_ = v___y_1853_;
v___y_1839_ = v___y_1855_;
v___y_1840_ = v___y_1854_;
v___y_1841_ = v___y_1856_;
v___y_1842_ = v___y_1857_;
v___y_1843_ = v___x_1861_;
goto v___jp_1834_;
}
else
{
v___y_1835_ = v___y_1848_;
v___y_1836_ = v___y_1858_;
v___y_1837_ = v___y_1851_;
v___y_1838_ = v___y_1853_;
v___y_1839_ = v___y_1855_;
v___y_1840_ = v___y_1854_;
v___y_1841_ = v___y_1856_;
v___y_1842_ = v___y_1857_;
v___y_1843_ = v___y_1849_;
goto v___jp_1834_;
}
}
v___jp_1862_:
{
uint64_t v___x_1872_; uint64_t v___x_1873_; uint8_t v___x_1874_; 
v___x_1872_ = 4ULL;
v___x_1873_ = lean_uint64_shift_right(v___y_1866_, v___x_1872_);
v___x_1874_ = lean_uint64_dec_eq(v___x_1873_, v___y_1868_);
if (v___x_1874_ == 0)
{
v___y_1848_ = v___y_1863_;
v___y_1849_ = v___y_1871_;
v___y_1850_ = v___x_1872_;
v___y_1851_ = v___y_1864_;
v___y_1852_ = v___y_1866_;
v___y_1853_ = v___y_1865_;
v___y_1854_ = v___y_1868_;
v___y_1855_ = v___y_1867_;
v___y_1856_ = v___y_1869_;
v___y_1857_ = v___y_1870_;
v___y_1858_ = v___x_1873_;
goto v___jp_1847_;
}
else
{
v___y_1848_ = v___y_1863_;
v___y_1849_ = v___y_1871_;
v___y_1850_ = v___x_1872_;
v___y_1851_ = v___y_1864_;
v___y_1852_ = v___y_1866_;
v___y_1853_ = v___y_1865_;
v___y_1854_ = v___y_1868_;
v___y_1855_ = v___y_1867_;
v___y_1856_ = v___y_1869_;
v___y_1857_ = v___y_1870_;
v___y_1858_ = v___y_1866_;
goto v___jp_1847_;
}
}
v___jp_1875_:
{
uint64_t v___x_1887_; uint8_t v___x_1888_; 
v___x_1887_ = lean_uint64_shift_right(v___y_1877_, v___y_1879_);
v___x_1888_ = lean_uint64_dec_eq(v___x_1887_, v___y_1882_);
if (v___x_1888_ == 0)
{
uint64_t v___x_1889_; 
v___x_1889_ = lean_uint64_add(v___y_1876_, v___y_1879_);
v___y_1863_ = v___y_1878_;
v___y_1864_ = v___y_1880_;
v___y_1865_ = v___y_1881_;
v___y_1866_ = v___y_1886_;
v___y_1867_ = v___y_1883_;
v___y_1868_ = v___y_1882_;
v___y_1869_ = v___y_1884_;
v___y_1870_ = v___y_1885_;
v___y_1871_ = v___x_1889_;
goto v___jp_1862_;
}
else
{
v___y_1863_ = v___y_1878_;
v___y_1864_ = v___y_1880_;
v___y_1865_ = v___y_1881_;
v___y_1866_ = v___y_1886_;
v___y_1867_ = v___y_1883_;
v___y_1868_ = v___y_1882_;
v___y_1869_ = v___y_1884_;
v___y_1870_ = v___y_1885_;
v___y_1871_ = v___y_1876_;
goto v___jp_1862_;
}
}
v___jp_1890_:
{
uint64_t v___x_1900_; uint64_t v___x_1901_; uint8_t v___x_1902_; 
v___x_1900_ = 8ULL;
v___x_1901_ = lean_uint64_shift_right(v___y_1891_, v___x_1900_);
v___x_1902_ = lean_uint64_dec_eq(v___x_1901_, v___y_1896_);
if (v___x_1902_ == 0)
{
v___y_1876_ = v___y_1899_;
v___y_1877_ = v___y_1891_;
v___y_1878_ = v___y_1892_;
v___y_1879_ = v___x_1900_;
v___y_1880_ = v___y_1893_;
v___y_1881_ = v___y_1894_;
v___y_1882_ = v___y_1896_;
v___y_1883_ = v___y_1895_;
v___y_1884_ = v___y_1897_;
v___y_1885_ = v___y_1898_;
v___y_1886_ = v___x_1901_;
goto v___jp_1875_;
}
else
{
v___y_1876_ = v___y_1899_;
v___y_1877_ = v___y_1891_;
v___y_1878_ = v___y_1892_;
v___y_1879_ = v___x_1900_;
v___y_1880_ = v___y_1893_;
v___y_1881_ = v___y_1894_;
v___y_1882_ = v___y_1896_;
v___y_1883_ = v___y_1895_;
v___y_1884_ = v___y_1897_;
v___y_1885_ = v___y_1898_;
v___y_1886_ = v___y_1891_;
goto v___jp_1875_;
}
}
v___jp_1903_:
{
uint64_t v___x_1915_; uint8_t v___x_1916_; 
v___x_1915_ = lean_uint64_shift_right(v___y_1908_, v___y_1913_);
v___x_1916_ = lean_uint64_dec_eq(v___x_1915_, v___y_1909_);
if (v___x_1916_ == 0)
{
uint64_t v___x_1917_; 
v___x_1917_ = lean_uint64_add(v___y_1904_, v___y_1913_);
v___y_1891_ = v___y_1914_;
v___y_1892_ = v___y_1905_;
v___y_1893_ = v___y_1906_;
v___y_1894_ = v___y_1907_;
v___y_1895_ = v___y_1910_;
v___y_1896_ = v___y_1909_;
v___y_1897_ = v___y_1911_;
v___y_1898_ = v___y_1912_;
v___y_1899_ = v___x_1917_;
goto v___jp_1890_;
}
else
{
v___y_1891_ = v___y_1914_;
v___y_1892_ = v___y_1905_;
v___y_1893_ = v___y_1906_;
v___y_1894_ = v___y_1907_;
v___y_1895_ = v___y_1910_;
v___y_1896_ = v___y_1909_;
v___y_1897_ = v___y_1911_;
v___y_1898_ = v___y_1912_;
v___y_1899_ = v___y_1904_;
goto v___jp_1890_;
}
}
v___jp_1918_:
{
uint64_t v___x_1928_; uint64_t v___x_1929_; uint8_t v___x_1930_; 
v___x_1928_ = 16ULL;
v___x_1929_ = lean_uint64_shift_right(v___y_1924_, v___x_1928_);
v___x_1930_ = lean_uint64_dec_eq(v___x_1929_, v___y_1923_);
if (v___x_1930_ == 0)
{
v___y_1904_ = v___y_1927_;
v___y_1905_ = v___y_1919_;
v___y_1906_ = v___y_1920_;
v___y_1907_ = v___y_1921_;
v___y_1908_ = v___y_1924_;
v___y_1909_ = v___y_1923_;
v___y_1910_ = v___y_1922_;
v___y_1911_ = v___y_1925_;
v___y_1912_ = v___y_1926_;
v___y_1913_ = v___x_1928_;
v___y_1914_ = v___x_1929_;
goto v___jp_1903_;
}
else
{
v___y_1904_ = v___y_1927_;
v___y_1905_ = v___y_1919_;
v___y_1906_ = v___y_1920_;
v___y_1907_ = v___y_1921_;
v___y_1908_ = v___y_1924_;
v___y_1909_ = v___y_1923_;
v___y_1910_ = v___y_1922_;
v___y_1911_ = v___y_1925_;
v___y_1912_ = v___y_1926_;
v___y_1913_ = v___x_1928_;
v___y_1914_ = v___y_1924_;
goto v___jp_1903_;
}
}
v___jp_1931_:
{
uint64_t v___x_1941_; uint64_t v___x_1942_; uint8_t v___x_1943_; 
v___x_1941_ = lean_unbox_uint64(v___y_1935_);
v___x_1942_ = lean_uint64_shift_right(v___x_1941_, v___y_1934_);
v___x_1943_ = lean_uint64_dec_eq(v___x_1942_, v___y_1936_);
if (v___x_1943_ == 0)
{
v___y_1919_ = v___y_1932_;
v___y_1920_ = v___y_1933_;
v___y_1921_ = v___y_1935_;
v___y_1922_ = v___y_1937_;
v___y_1923_ = v___y_1936_;
v___y_1924_ = v___y_1940_;
v___y_1925_ = v___y_1938_;
v___y_1926_ = v___y_1939_;
v___y_1927_ = v___y_1934_;
goto v___jp_1918_;
}
else
{
v___y_1919_ = v___y_1932_;
v___y_1920_ = v___y_1933_;
v___y_1921_ = v___y_1935_;
v___y_1922_ = v___y_1937_;
v___y_1923_ = v___y_1936_;
v___y_1924_ = v___y_1940_;
v___y_1925_ = v___y_1938_;
v___y_1926_ = v___y_1939_;
v___y_1927_ = v___y_1936_;
goto v___jp_1918_;
}
}
v___jp_1944_:
{
uint64_t v___x_1950_; uint64_t v___x_1951_; uint8_t v___x_1952_; 
v___x_1950_ = 0ULL;
v___x_1951_ = lean_unbox_uint64(v_snd_1949_);
v___x_1952_ = lean_uint64_dec_eq(v___x_1951_, v___x_1950_);
if (v___x_1952_ == 0)
{
uint64_t v___x_1953_; uint64_t v___x_1954_; uint64_t v___x_1955_; uint64_t v___x_1956_; uint64_t v___x_1957_; uint8_t v___x_1958_; 
v___x_1953_ = 149ULL;
v___x_1954_ = lean_uint64_add(v___y_1947_, v___x_1953_);
v___x_1955_ = 32ULL;
v___x_1956_ = lean_unbox_uint64(v_snd_1949_);
v___x_1957_ = lean_uint64_shift_right(v___x_1956_, v___x_1955_);
v___x_1958_ = lean_uint64_dec_eq(v___x_1957_, v___x_1950_);
if (v___x_1958_ == 0)
{
v___y_1932_ = v___x_1953_;
v___y_1933_ = v___x_1954_;
v___y_1934_ = v___x_1955_;
v___y_1935_ = v_snd_1949_;
v___y_1936_ = v___x_1950_;
v___y_1937_ = v___y_1945_;
v___y_1938_ = v___y_1946_;
v___y_1939_ = v_fst_1948_;
v___y_1940_ = v___x_1957_;
goto v___jp_1931_;
}
else
{
uint64_t v___x_1959_; 
v___x_1959_ = lean_unbox_uint64(v_snd_1949_);
v___y_1932_ = v___x_1953_;
v___y_1933_ = v___x_1954_;
v___y_1934_ = v___x_1955_;
v___y_1935_ = v_snd_1949_;
v___y_1936_ = v___x_1950_;
v___y_1937_ = v___y_1945_;
v___y_1938_ = v___y_1946_;
v___y_1939_ = v_fst_1948_;
v___y_1940_ = v___x_1959_;
goto v___jp_1931_;
}
}
else
{
uint8_t v___x_1960_; 
lean_dec(v_snd_1949_);
v___x_1960_ = lean_unbox(v_fst_1948_);
lean_dec(v_fst_1948_);
if (v___x_1960_ == 0)
{
uint32_t v___x_1961_; 
v___x_1961_ = 0;
return v___x_1961_;
}
else
{
uint32_t v___x_1962_; 
v___x_1962_ = 2147483648;
return v___x_1962_;
}
}
}
v___jp_1963_:
{
uint8_t v___x_1972_; 
v___x_1972_ = lean_uint64_dec_eq(v___y_1965_, v___y_1964_);
if (v___x_1972_ == 0)
{
uint8_t v___x_1973_; 
v___x_1973_ = lean_uint64_dec_lt(v___y_1965_, v___y_1964_);
if (v___x_1973_ == 0)
{
uint64_t v___x_1974_; lean_object* v___x_1975_; lean_object* v___x_1976_; 
v___x_1974_ = lean_uint64_sub(v___y_1965_, v___y_1964_);
v___x_1975_ = lean_box(v___y_1967_);
v___x_1976_ = lean_box_uint64(v___x_1974_);
v___y_1945_ = v___y_1968_;
v___y_1946_ = v___y_1969_;
v___y_1947_ = v___y_1970_;
v_fst_1948_ = v___x_1975_;
v_snd_1949_ = v___x_1976_;
goto v___jp_1944_;
}
else
{
uint64_t v___x_1977_; lean_object* v___x_1978_; lean_object* v___x_1979_; 
v___x_1977_ = lean_uint64_sub(v___y_1964_, v___y_1965_);
v___x_1978_ = lean_box(v___y_1966_);
v___x_1979_ = lean_box_uint64(v___x_1977_);
v___y_1945_ = v___y_1968_;
v___y_1946_ = v___y_1969_;
v___y_1947_ = v___y_1970_;
v_fst_1948_ = v___x_1978_;
v_snd_1949_ = v___x_1979_;
goto v___jp_1944_;
}
}
else
{
lean_object* v___x_1980_; lean_object* v___x_1981_; 
v___x_1980_ = lean_box(v___y_1971_);
v___x_1981_ = ((lean_object*)(lp_competition_Submission_TunedAdd_core___boxed__const__1));
v___y_1945_ = v___y_1968_;
v___y_1946_ = v___y_1969_;
v___y_1947_ = v___y_1970_;
v_fst_1948_ = v___x_1980_;
v_snd_1949_ = v___x_1981_;
goto v___jp_1944_;
}
}
v___jp_1982_:
{
if (v___y_1990_ == 0)
{
v___y_1964_ = v___y_1983_;
v___y_1965_ = v___y_1984_;
v___y_1966_ = v___y_1986_;
v___y_1967_ = v___y_1985_;
v___y_1968_ = v___y_1987_;
v___y_1969_ = v___y_1988_;
v___y_1970_ = v___y_1989_;
v___y_1971_ = v___y_1990_;
goto v___jp_1963_;
}
else
{
uint64_t v___x_1991_; lean_object* v___x_1992_; lean_object* v___x_1993_; 
v___x_1991_ = lean_uint64_add(v___y_1984_, v___y_1983_);
v___x_1992_ = lean_box(v___y_1985_);
v___x_1993_ = lean_box_uint64(v___x_1991_);
v___y_1945_ = v___y_1987_;
v___y_1946_ = v___y_1988_;
v___y_1947_ = v___y_1989_;
v_fst_1948_ = v___x_1992_;
v_snd_1949_ = v___x_1993_;
goto v___jp_1944_;
}
}
v___jp_1994_:
{
uint8_t v___x_2003_; 
v___x_2003_ = lean_uint64_dec_eq(v___y_2001_, v___y_1995_);
if (v___x_2003_ == 0)
{
uint8_t v___x_2004_; 
v___x_2004_ = lean_uint64_dec_lt(v___y_2001_, v___y_1995_);
if (v___x_2004_ == 0)
{
uint64_t v___x_2005_; lean_object* v___x_2006_; lean_object* v___x_2007_; 
v___x_2005_ = lean_uint64_sub(v___y_2001_, v___y_1995_);
v___x_2006_ = lean_box(v___y_1997_);
v___x_2007_ = lean_box_uint64(v___x_2005_);
v___y_1632_ = v___y_1998_;
v___y_1633_ = v___y_1999_;
v___y_1634_ = v___y_2000_;
v_fst_1635_ = v___x_2006_;
v_snd_1636_ = v___x_2007_;
goto v___jp_1631_;
}
else
{
uint64_t v___x_2008_; lean_object* v___x_2009_; lean_object* v___x_2010_; 
v___x_2008_ = lean_uint64_sub(v___y_1995_, v___y_2001_);
v___x_2009_ = lean_box(v___y_1996_);
v___x_2010_ = lean_box_uint64(v___x_2008_);
v___y_1632_ = v___y_1998_;
v___y_1633_ = v___y_1999_;
v___y_1634_ = v___y_2000_;
v_fst_1635_ = v___x_2009_;
v_snd_1636_ = v___x_2010_;
goto v___jp_1631_;
}
}
else
{
lean_object* v___x_2011_; lean_object* v___x_2012_; 
v___x_2011_ = lean_box(v___y_2002_);
v___x_2012_ = ((lean_object*)(lp_competition_Submission_TunedAdd_core___boxed__const__1));
v___y_1632_ = v___y_1998_;
v___y_1633_ = v___y_1999_;
v___y_1634_ = v___y_2000_;
v_fst_1635_ = v___x_2011_;
v_snd_1636_ = v___x_2012_;
goto v___jp_1631_;
}
}
v___jp_2013_:
{
if (v___y_2021_ == 0)
{
v___y_1995_ = v___y_2014_;
v___y_1996_ = v___y_2016_;
v___y_1997_ = v___y_2015_;
v___y_1998_ = v___y_2017_;
v___y_1999_ = v___y_2018_;
v___y_2000_ = v___y_2019_;
v___y_2001_ = v___y_2020_;
v___y_2002_ = v___y_2021_;
goto v___jp_1994_;
}
else
{
uint64_t v___x_2022_; lean_object* v___x_2023_; lean_object* v___x_2024_; 
v___x_2022_ = lean_uint64_add(v___y_2020_, v___y_2014_);
v___x_2023_ = lean_box(v___y_2015_);
v___x_2024_ = lean_box_uint64(v___x_2022_);
v___y_1632_ = v___y_2017_;
v___y_1633_ = v___y_2018_;
v___y_1634_ = v___y_2019_;
v_fst_1635_ = v___x_2023_;
v_snd_1636_ = v___x_2024_;
goto v___jp_1631_;
}
}
v___jp_2025_:
{
uint8_t v___x_2034_; 
v___x_2034_ = lean_uint64_dec_le(v___y_2029_, v___y_2033_);
if (v___x_2034_ == 0)
{
uint64_t v_shift_2035_; uint64_t v___x_2036_; uint8_t v___x_2037_; 
v_shift_2035_ = lean_uint64_sub(v___y_2029_, v___y_2033_);
v___x_2036_ = 39ULL;
v___x_2037_ = lean_uint64_dec_le(v_shift_2035_, v___x_2036_);
if (v___x_2037_ == 0)
{
return v_x_1327_;
}
else
{
uint64_t v___x_2038_; 
v___x_2038_ = lean_uint64_shift_left(v___y_2032_, v_shift_2035_);
if (v___y_2027_ == 0)
{
if (v___y_2028_ == 0)
{
v___y_1983_ = v___y_2026_;
v___y_1984_ = v___x_2038_;
v___y_1985_ = v___y_2027_;
v___y_1986_ = v___y_2028_;
v___y_1987_ = v___y_2030_;
v___y_1988_ = v___y_2031_;
v___y_1989_ = v___y_2033_;
v___y_1990_ = v___x_2037_;
goto v___jp_1982_;
}
else
{
v___y_1964_ = v___y_2026_;
v___y_1965_ = v___x_2038_;
v___y_1966_ = v___y_2028_;
v___y_1967_ = v___y_2027_;
v___y_1968_ = v___y_2030_;
v___y_1969_ = v___y_2031_;
v___y_1970_ = v___y_2033_;
v___y_1971_ = v___y_2027_;
goto v___jp_1963_;
}
}
else
{
v___y_1983_ = v___y_2026_;
v___y_1984_ = v___x_2038_;
v___y_1985_ = v___y_2027_;
v___y_1986_ = v___y_2028_;
v___y_1987_ = v___y_2030_;
v___y_1988_ = v___y_2031_;
v___y_1989_ = v___y_2033_;
v___y_1990_ = v___y_2028_;
goto v___jp_1982_;
}
}
}
else
{
uint64_t v_shift_2039_; uint64_t v___x_2040_; uint8_t v___x_2041_; 
v_shift_2039_ = lean_uint64_sub(v___y_2033_, v___y_2029_);
v___x_2040_ = 39ULL;
v___x_2041_ = lean_uint64_dec_le(v_shift_2039_, v___x_2040_);
if (v___x_2041_ == 0)
{
return v_y_1328_;
}
else
{
uint64_t v___x_2042_; 
v___x_2042_ = lean_uint64_shift_left(v___y_2026_, v_shift_2039_);
if (v___y_2027_ == 0)
{
if (v___y_2028_ == 0)
{
v___y_2014_ = v___x_2042_;
v___y_2015_ = v___y_2027_;
v___y_2016_ = v___y_2028_;
v___y_2017_ = v___y_2029_;
v___y_2018_ = v___y_2030_;
v___y_2019_ = v___y_2031_;
v___y_2020_ = v___y_2032_;
v___y_2021_ = v___x_2041_;
goto v___jp_2013_;
}
else
{
v___y_1995_ = v___x_2042_;
v___y_1996_ = v___y_2028_;
v___y_1997_ = v___y_2027_;
v___y_1998_ = v___y_2029_;
v___y_1999_ = v___y_2030_;
v___y_2000_ = v___y_2031_;
v___y_2001_ = v___y_2032_;
v___y_2002_ = v___y_2027_;
goto v___jp_1994_;
}
}
else
{
v___y_2014_ = v___x_2042_;
v___y_2015_ = v___y_2027_;
v___y_2016_ = v___y_2028_;
v___y_2017_ = v___y_2029_;
v___y_2018_ = v___y_2030_;
v___y_2019_ = v___y_2031_;
v___y_2020_ = v___y_2032_;
v___y_2021_ = v___y_2028_;
goto v___jp_2013_;
}
}
}
}
v___jp_2043_:
{
uint64_t v___x_2052_; uint64_t v___x_2053_; uint8_t v___x_2054_; 
v___x_2052_ = lean_uint32_to_uint64(v___y_2050_);
v___x_2053_ = 0ULL;
v___x_2054_ = lean_uint64_dec_eq(v___x_2052_, v___x_2053_);
if (v___x_2054_ == 0)
{
uint64_t v___x_2055_; uint64_t v___x_2056_; 
v___x_2055_ = 1ULL;
v___x_2056_ = lean_uint64_sub(v___x_2052_, v___x_2055_);
v___y_2026_ = v___y_2044_;
v___y_2027_ = v___y_2046_;
v___y_2028_ = v___y_2045_;
v___y_2029_ = v___y_2051_;
v___y_2030_ = v___y_2047_;
v___y_2031_ = v___y_2048_;
v___y_2032_ = v___y_2049_;
v___y_2033_ = v___x_2056_;
goto v___jp_2025_;
}
else
{
v___y_2026_ = v___y_2044_;
v___y_2027_ = v___y_2046_;
v___y_2028_ = v___y_2045_;
v___y_2029_ = v___y_2051_;
v___y_2030_ = v___y_2047_;
v___y_2031_ = v___y_2048_;
v___y_2032_ = v___y_2049_;
v___y_2033_ = v___x_2053_;
goto v___jp_2025_;
}
}
v___jp_2057_:
{
uint64_t v___x_2066_; uint64_t v___x_2067_; uint8_t v___x_2068_; 
v___x_2066_ = lean_uint32_to_uint64(v___y_2060_);
v___x_2067_ = 0ULL;
v___x_2068_ = lean_uint64_dec_eq(v___x_2066_, v___x_2067_);
if (v___x_2068_ == 0)
{
uint64_t v___x_2069_; uint64_t v___x_2070_; 
v___x_2069_ = 1ULL;
v___x_2070_ = lean_uint64_sub(v___x_2066_, v___x_2069_);
v___y_2044_ = v___y_2065_;
v___y_2045_ = v___y_2059_;
v___y_2046_ = v___y_2058_;
v___y_2047_ = v___y_2061_;
v___y_2048_ = v___y_2062_;
v___y_2049_ = v___y_2063_;
v___y_2050_ = v___y_2064_;
v___y_2051_ = v___x_2070_;
goto v___jp_2043_;
}
else
{
v___y_2044_ = v___y_2065_;
v___y_2045_ = v___y_2059_;
v___y_2046_ = v___y_2058_;
v___y_2047_ = v___y_2061_;
v___y_2048_ = v___y_2062_;
v___y_2049_ = v___y_2063_;
v___y_2050_ = v___y_2064_;
v___y_2051_ = v___x_2067_;
goto v___jp_2043_;
}
}
v___jp_2071_:
{
uint32_t v___x_2079_; uint32_t v___x_2080_; uint32_t v___x_2081_; uint8_t v___x_2082_; 
v___x_2079_ = 8388607;
v___x_2080_ = lean_uint32_land(v_y_1328_, v___x_2079_);
v___x_2081_ = 0;
v___x_2082_ = lean_uint32_dec_eq(v___y_2077_, v___x_2081_);
if (v___x_2082_ == 0)
{
uint64_t v___x_2083_; uint64_t v___x_2084_; uint64_t v___x_2085_; 
v___x_2083_ = lean_uint32_to_uint64(v___x_2080_);
v___x_2084_ = 8388608ULL;
v___x_2085_ = lean_uint64_lor(v___x_2083_, v___x_2084_);
v___y_2058_ = v___y_2073_;
v___y_2059_ = v___y_2072_;
v___y_2060_ = v___y_2075_;
v___y_2061_ = v___y_2074_;
v___y_2062_ = v___y_2076_;
v___y_2063_ = v___y_2078_;
v___y_2064_ = v___y_2077_;
v___y_2065_ = v___x_2085_;
goto v___jp_2057_;
}
else
{
uint64_t v___x_2086_; 
v___x_2086_ = lean_uint32_to_uint64(v___x_2080_);
v___y_2058_ = v___y_2073_;
v___y_2059_ = v___y_2072_;
v___y_2060_ = v___y_2075_;
v___y_2061_ = v___y_2074_;
v___y_2062_ = v___y_2076_;
v___y_2063_ = v___y_2078_;
v___y_2064_ = v___y_2077_;
v___y_2065_ = v___x_2086_;
goto v___jp_2057_;
}
}
v___jp_2087_:
{
uint32_t v___x_2094_; uint32_t v___x_2095_; uint32_t v___x_2096_; uint8_t v___x_2097_; 
v___x_2094_ = 8388607;
v___x_2095_ = lean_uint32_land(v_x_1327_, v___x_2094_);
v___x_2096_ = 0;
v___x_2097_ = lean_uint32_dec_eq(v___y_2089_, v___x_2096_);
if (v___x_2097_ == 0)
{
uint64_t v___x_2098_; uint64_t v___x_2099_; uint64_t v___x_2100_; 
v___x_2098_ = lean_uint32_to_uint64(v___x_2095_);
v___x_2099_ = 8388608ULL;
v___x_2100_ = lean_uint64_lor(v___x_2098_, v___x_2099_);
v___y_2072_ = v___y_2093_;
v___y_2073_ = v___y_2088_;
v___y_2074_ = v___y_2090_;
v___y_2075_ = v___y_2089_;
v___y_2076_ = v___y_2091_;
v___y_2077_ = v___y_2092_;
v___y_2078_ = v___x_2100_;
goto v___jp_2071_;
}
else
{
uint64_t v___x_2101_; 
v___x_2101_ = lean_uint32_to_uint64(v___x_2095_);
v___y_2072_ = v___y_2093_;
v___y_2073_ = v___y_2088_;
v___y_2074_ = v___y_2090_;
v___y_2075_ = v___y_2089_;
v___y_2076_ = v___y_2091_;
v___y_2077_ = v___y_2092_;
v___y_2078_ = v___x_2101_;
goto v___jp_2071_;
}
}
v___jp_2102_:
{
uint32_t v___x_2109_; uint32_t v___x_2110_; uint32_t v___x_2111_; uint8_t v___x_2112_; 
v___x_2109_ = 2147483648;
v___x_2110_ = lean_uint32_land(v_y_1328_, v___x_2109_);
v___x_2111_ = 0;
v___x_2112_ = lean_uint32_dec_eq(v___x_2110_, v___x_2111_);
if (v___x_2112_ == 0)
{
uint8_t v___x_2113_; 
v___x_2113_ = 1;
v___y_2088_ = v___y_2108_;
v___y_2089_ = v___y_2105_;
v___y_2090_ = v___y_2104_;
v___y_2091_ = v___y_2106_;
v___y_2092_ = v___y_2107_;
v___y_2093_ = v___x_2113_;
goto v___jp_2087_;
}
else
{
v___y_2088_ = v___y_2108_;
v___y_2089_ = v___y_2105_;
v___y_2090_ = v___y_2104_;
v___y_2091_ = v___y_2106_;
v___y_2092_ = v___y_2107_;
v___y_2093_ = v___y_2103_;
goto v___jp_2087_;
}
}
v___jp_2114_:
{
if (v___y_2115_ == 0)
{
uint32_t v___x_2116_; uint32_t v___x_2117_; uint32_t v___x_2118_; uint32_t v_xExponent_2119_; uint32_t v___x_2120_; uint32_t v_yExponent_2121_; uint32_t v___x_2122_; uint32_t v___x_2123_; uint32_t v___x_2124_; uint8_t v___x_2125_; 
v___x_2116_ = 23;
v___x_2117_ = lean_uint32_shift_right(v_x_1327_, v___x_2116_);
v___x_2118_ = 255;
v_xExponent_2119_ = lean_uint32_land(v___x_2117_, v___x_2118_);
v___x_2120_ = lean_uint32_shift_right(v_y_1328_, v___x_2116_);
v_yExponent_2121_ = lean_uint32_land(v___x_2120_, v___x_2118_);
v___x_2122_ = 2147483648;
v___x_2123_ = lean_uint32_land(v_x_1327_, v___x_2122_);
v___x_2124_ = 0;
v___x_2125_ = lean_uint32_dec_eq(v___x_2123_, v___x_2124_);
if (v___x_2125_ == 0)
{
uint8_t v___x_2126_; 
v___x_2126_ = 1;
v___y_2103_ = v___y_2115_;
v___y_2104_ = v___x_2116_;
v___y_2105_ = v_xExponent_2119_;
v___y_2106_ = v___x_2118_;
v___y_2107_ = v_yExponent_2121_;
v___y_2108_ = v___x_2126_;
goto v___jp_2102_;
}
else
{
v___y_2103_ = v___y_2115_;
v___y_2104_ = v___x_2116_;
v___y_2105_ = v_xExponent_2119_;
v___y_2106_ = v___x_2118_;
v___y_2107_ = v_yExponent_2121_;
v___y_2108_ = v___y_2115_;
goto v___jp_2102_;
}
}
else
{
lean_object* v___x_2127_; lean_object* v___x_2128_; lean_object* v___x_2129_; uint32_t v___x_2130_; 
v___x_2127_ = lean_uint32_to_nat(v_x_1327_);
v___x_2128_ = lean_uint32_to_nat(v_y_1328_);
v___x_2129_ = lp_floatlib_FloatLib_Floats_Formats_BinaryInterchange_Model_AddBackend_word___at___00FloatLib_Floats_Formats_BinaryInterchange_Configured_Plan_softwareAdd32Certified_spec__1(v___x_2127_, v___x_2128_);
v___x_2130_ = lean_uint32_of_nat(v___x_2129_);
lean_dec(v___x_2129_);
return v___x_2130_;
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_TunedAdd_add___boxed(lean_object* v_x_2139_, lean_object* v_y_2140_){
_start:
{
uint32_t v_x_boxed_2141_; uint32_t v_y_boxed_2142_; uint32_t v_res_2143_; lean_object* v_r_2144_; 
v_x_boxed_2141_ = lean_unbox_uint32(v_x_2139_);
lean_dec(v_x_2139_);
v_y_boxed_2142_ = lean_unbox_uint32(v_y_2140_);
lean_dec(v_y_2140_);
v_res_2143_ = lp_competition_Submission_TunedAdd_add(v_x_boxed_2141_, v_y_boxed_2142_);
v_r_2144_ = lean_box_uint32(v_res_2143_);
return v_r_2144_;
}
}
static uint8_t _init_lp_competition_Submission_TunedAdd_Plan(void){
_start:
{
uint8_t v___x_2151_; 
v___x_2151_ = 2;
return v___x_2151_;
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_TunedAdd_dec(uint32_t v_z_2152_){
_start:
{
lean_object* v___x_2153_; 
v___x_2153_ = lean_uint32_to_nat(v_z_2152_);
return v___x_2153_;
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_TunedAdd_dec___boxed(lean_object* v_z_2154_){
_start:
{
uint32_t v_z_boxed_2155_; lean_object* v_res_2156_; 
v_z_boxed_2155_ = lean_unbox_uint32(v_z_2154_);
lean_dec(v_z_2154_);
v_res_2156_ = lp_competition_Submission_TunedAdd_dec(v_z_boxed_2155_);
return v_res_2156_;
}
}
LEAN_EXPORT uint64_t lp_competition_Submission_FastMul_sx(uint64_t v_k_2157_, uint64_t v_x_2158_){
_start:
{
uint64_t v___x_2159_; uint64_t v___x_2160_; uint8_t v___x_2161_; 
v___x_2159_ = lean_uint64_shift_right(v_x_2158_, v_k_2157_);
v___x_2160_ = 0ULL;
v___x_2161_ = lean_uint64_dec_eq(v___x_2159_, v___x_2160_);
if (v___x_2161_ == 0)
{
return v___x_2159_;
}
else
{
return v_x_2158_;
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_FastMul_sx___boxed(lean_object* v_k_2162_, lean_object* v_x_2163_){
_start:
{
uint64_t v_k_boxed_2164_; uint64_t v_x_boxed_2165_; uint64_t v_res_2166_; lean_object* v_r_2167_; 
v_k_boxed_2164_ = lean_unbox_uint64(v_k_2162_);
lean_dec_ref(v_k_2162_);
v_x_boxed_2165_ = lean_unbox_uint64(v_x_2163_);
lean_dec_ref(v_x_2163_);
v_res_2166_ = lp_competition_Submission_FastMul_sx(v_k_boxed_2164_, v_x_boxed_2165_);
v_r_2167_ = lean_box_uint64(v_res_2166_);
return v_r_2167_;
}
}
LEAN_EXPORT uint64_t lp_competition_Submission_FastMul_sr(uint64_t v_k_2168_, uint64_t v_x_2169_, uint64_t v_r_2170_){
_start:
{
uint64_t v___x_2171_; uint64_t v___x_2172_; uint8_t v___x_2173_; 
v___x_2171_ = lean_uint64_shift_right(v_x_2169_, v_k_2168_);
v___x_2172_ = 0ULL;
v___x_2173_ = lean_uint64_dec_eq(v___x_2171_, v___x_2172_);
if (v___x_2173_ == 0)
{
uint64_t v___x_2174_; 
v___x_2174_ = lean_uint64_add(v_r_2170_, v_k_2168_);
return v___x_2174_;
}
else
{
return v_r_2170_;
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_FastMul_sr___boxed(lean_object* v_k_2175_, lean_object* v_x_2176_, lean_object* v_r_2177_){
_start:
{
uint64_t v_k_boxed_2178_; uint64_t v_x_boxed_2179_; uint64_t v_r_boxed_2180_; uint64_t v_res_2181_; lean_object* v_r_2182_; 
v_k_boxed_2178_ = lean_unbox_uint64(v_k_2175_);
lean_dec_ref(v_k_2175_);
v_x_boxed_2179_ = lean_unbox_uint64(v_x_2176_);
lean_dec_ref(v_x_2176_);
v_r_boxed_2180_ = lean_unbox_uint64(v_r_2177_);
lean_dec_ref(v_r_2177_);
v_res_2181_ = lp_competition_Submission_FastMul_sr(v_k_boxed_2178_, v_x_boxed_2179_, v_r_boxed_2180_);
v_r_2182_ = lean_box_uint64(v_res_2181_);
return v_r_2182_;
}
}
LEAN_EXPORT uint64_t lp_competition_Submission_FastMul_fastLog2(uint64_t v_x0_2183_){
_start:
{
uint64_t v___y_2185_; uint64_t v___y_2186_; uint64_t v___y_2193_; uint64_t v___y_2194_; uint64_t v___y_2195_; uint64_t v___y_2196_; uint64_t v___y_2202_; uint64_t v___y_2203_; uint64_t v___y_2209_; uint64_t v___y_2210_; uint64_t v___y_2211_; uint64_t v___y_2212_; uint64_t v___y_2218_; uint64_t v___y_2219_; uint64_t v___y_2225_; uint64_t v___y_2226_; uint64_t v___y_2227_; uint64_t v___y_2228_; uint64_t v___y_2234_; uint64_t v___y_2235_; uint64_t v___y_2241_; uint64_t v___y_2242_; uint64_t v___y_2243_; uint64_t v___y_2244_; uint64_t v___y_2250_; uint64_t v___y_2251_; uint64_t v___x_2256_; uint64_t v___y_2258_; uint64_t v___x_2262_; uint64_t v___x_2263_; uint8_t v___x_2264_; 
v___x_2256_ = 32ULL;
v___x_2262_ = lean_uint64_shift_right(v_x0_2183_, v___x_2256_);
v___x_2263_ = 0ULL;
v___x_2264_ = lean_uint64_dec_eq(v___x_2262_, v___x_2263_);
if (v___x_2264_ == 0)
{
v___y_2258_ = v___x_2262_;
goto v___jp_2257_;
}
else
{
v___y_2258_ = v_x0_2183_;
goto v___jp_2257_;
}
v___jp_2184_:
{
uint64_t v___x_2187_; uint64_t v___x_2188_; uint64_t v___x_2189_; uint8_t v___x_2190_; 
v___x_2187_ = 1ULL;
v___x_2188_ = lean_uint64_shift_right(v___y_2185_, v___x_2187_);
v___x_2189_ = 0ULL;
v___x_2190_ = lean_uint64_dec_eq(v___x_2188_, v___x_2189_);
if (v___x_2190_ == 0)
{
uint64_t v___x_2191_; 
v___x_2191_ = lean_uint64_add(v___y_2186_, v___x_2187_);
return v___x_2191_;
}
else
{
return v___y_2186_;
}
}
v___jp_2192_:
{
uint64_t v___x_2197_; uint64_t v___x_2198_; uint8_t v___x_2199_; 
v___x_2197_ = lean_uint64_shift_right(v___y_2195_, v___y_2194_);
v___x_2198_ = 0ULL;
v___x_2199_ = lean_uint64_dec_eq(v___x_2197_, v___x_2198_);
if (v___x_2199_ == 0)
{
uint64_t v___x_2200_; 
v___x_2200_ = lean_uint64_add(v___y_2193_, v___y_2194_);
v___y_2185_ = v___y_2196_;
v___y_2186_ = v___x_2200_;
goto v___jp_2184_;
}
else
{
v___y_2185_ = v___y_2196_;
v___y_2186_ = v___y_2193_;
goto v___jp_2184_;
}
}
v___jp_2201_:
{
uint64_t v___x_2204_; uint64_t v___x_2205_; uint64_t v___x_2206_; uint8_t v___x_2207_; 
v___x_2204_ = 2ULL;
v___x_2205_ = lean_uint64_shift_right(v___y_2202_, v___x_2204_);
v___x_2206_ = 0ULL;
v___x_2207_ = lean_uint64_dec_eq(v___x_2205_, v___x_2206_);
if (v___x_2207_ == 0)
{
v___y_2193_ = v___y_2203_;
v___y_2194_ = v___x_2204_;
v___y_2195_ = v___y_2202_;
v___y_2196_ = v___x_2205_;
goto v___jp_2192_;
}
else
{
v___y_2193_ = v___y_2203_;
v___y_2194_ = v___x_2204_;
v___y_2195_ = v___y_2202_;
v___y_2196_ = v___y_2202_;
goto v___jp_2192_;
}
}
v___jp_2208_:
{
uint64_t v___x_2213_; uint64_t v___x_2214_; uint8_t v___x_2215_; 
v___x_2213_ = lean_uint64_shift_right(v___y_2211_, v___y_2209_);
v___x_2214_ = 0ULL;
v___x_2215_ = lean_uint64_dec_eq(v___x_2213_, v___x_2214_);
if (v___x_2215_ == 0)
{
uint64_t v___x_2216_; 
v___x_2216_ = lean_uint64_add(v___y_2210_, v___y_2209_);
v___y_2202_ = v___y_2212_;
v___y_2203_ = v___x_2216_;
goto v___jp_2201_;
}
else
{
v___y_2202_ = v___y_2212_;
v___y_2203_ = v___y_2210_;
goto v___jp_2201_;
}
}
v___jp_2217_:
{
uint64_t v___x_2220_; uint64_t v___x_2221_; uint64_t v___x_2222_; uint8_t v___x_2223_; 
v___x_2220_ = 4ULL;
v___x_2221_ = lean_uint64_shift_right(v___y_2218_, v___x_2220_);
v___x_2222_ = 0ULL;
v___x_2223_ = lean_uint64_dec_eq(v___x_2221_, v___x_2222_);
if (v___x_2223_ == 0)
{
v___y_2209_ = v___x_2220_;
v___y_2210_ = v___y_2219_;
v___y_2211_ = v___y_2218_;
v___y_2212_ = v___x_2221_;
goto v___jp_2208_;
}
else
{
v___y_2209_ = v___x_2220_;
v___y_2210_ = v___y_2219_;
v___y_2211_ = v___y_2218_;
v___y_2212_ = v___y_2218_;
goto v___jp_2208_;
}
}
v___jp_2224_:
{
uint64_t v___x_2229_; uint64_t v___x_2230_; uint8_t v___x_2231_; 
v___x_2229_ = lean_uint64_shift_right(v___y_2227_, v___y_2226_);
v___x_2230_ = 0ULL;
v___x_2231_ = lean_uint64_dec_eq(v___x_2229_, v___x_2230_);
if (v___x_2231_ == 0)
{
uint64_t v___x_2232_; 
v___x_2232_ = lean_uint64_add(v___y_2225_, v___y_2226_);
v___y_2218_ = v___y_2228_;
v___y_2219_ = v___x_2232_;
goto v___jp_2217_;
}
else
{
v___y_2218_ = v___y_2228_;
v___y_2219_ = v___y_2225_;
goto v___jp_2217_;
}
}
v___jp_2233_:
{
uint64_t v___x_2236_; uint64_t v___x_2237_; uint64_t v___x_2238_; uint8_t v___x_2239_; 
v___x_2236_ = 8ULL;
v___x_2237_ = lean_uint64_shift_right(v___y_2234_, v___x_2236_);
v___x_2238_ = 0ULL;
v___x_2239_ = lean_uint64_dec_eq(v___x_2237_, v___x_2238_);
if (v___x_2239_ == 0)
{
v___y_2225_ = v___y_2235_;
v___y_2226_ = v___x_2236_;
v___y_2227_ = v___y_2234_;
v___y_2228_ = v___x_2237_;
goto v___jp_2224_;
}
else
{
v___y_2225_ = v___y_2235_;
v___y_2226_ = v___x_2236_;
v___y_2227_ = v___y_2234_;
v___y_2228_ = v___y_2234_;
goto v___jp_2224_;
}
}
v___jp_2240_:
{
uint64_t v___x_2245_; uint64_t v___x_2246_; uint8_t v___x_2247_; 
v___x_2245_ = lean_uint64_shift_right(v___y_2243_, v___y_2241_);
v___x_2246_ = 0ULL;
v___x_2247_ = lean_uint64_dec_eq(v___x_2245_, v___x_2246_);
if (v___x_2247_ == 0)
{
uint64_t v___x_2248_; 
v___x_2248_ = lean_uint64_add(v___y_2242_, v___y_2241_);
v___y_2234_ = v___y_2244_;
v___y_2235_ = v___x_2248_;
goto v___jp_2233_;
}
else
{
v___y_2234_ = v___y_2244_;
v___y_2235_ = v___y_2242_;
goto v___jp_2233_;
}
}
v___jp_2249_:
{
uint64_t v___x_2252_; uint64_t v___x_2253_; uint64_t v___x_2254_; uint8_t v___x_2255_; 
v___x_2252_ = 16ULL;
v___x_2253_ = lean_uint64_shift_right(v___y_2250_, v___x_2252_);
v___x_2254_ = 0ULL;
v___x_2255_ = lean_uint64_dec_eq(v___x_2253_, v___x_2254_);
if (v___x_2255_ == 0)
{
v___y_2241_ = v___x_2252_;
v___y_2242_ = v___y_2251_;
v___y_2243_ = v___y_2250_;
v___y_2244_ = v___x_2253_;
goto v___jp_2240_;
}
else
{
v___y_2241_ = v___x_2252_;
v___y_2242_ = v___y_2251_;
v___y_2243_ = v___y_2250_;
v___y_2244_ = v___y_2250_;
goto v___jp_2240_;
}
}
v___jp_2257_:
{
uint64_t v___x_2259_; uint64_t v___x_2260_; uint8_t v___x_2261_; 
v___x_2259_ = lean_uint64_shift_right(v_x0_2183_, v___x_2256_);
v___x_2260_ = 0ULL;
v___x_2261_ = lean_uint64_dec_eq(v___x_2259_, v___x_2260_);
if (v___x_2261_ == 0)
{
v___y_2250_ = v___y_2258_;
v___y_2251_ = v___x_2256_;
goto v___jp_2249_;
}
else
{
v___y_2250_ = v___y_2258_;
v___y_2251_ = v___x_2260_;
goto v___jp_2249_;
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_FastMul_fastLog2___boxed(lean_object* v_x0_2265_){
_start:
{
uint64_t v_x0_boxed_2266_; uint64_t v_res_2267_; lean_object* v_r_2268_; 
v_x0_boxed_2266_ = lean_unbox_uint64(v_x0_2265_);
lean_dec_ref(v_x0_2265_);
v_res_2267_ = lp_competition_Submission_FastMul_fastLog2(v_x0_boxed_2266_);
v_r_2268_ = lean_box_uint64(v_res_2267_);
return v_r_2268_;
}
}
LEAN_EXPORT uint64_t lp_competition_Submission_FastMul_rse(uint64_t v_value_2269_, uint64_t v_shift_2270_){
_start:
{
uint64_t v_quotient_2271_; uint64_t v___x_2272_; uint64_t v___x_2273_; uint64_t v___x_2274_; uint64_t v_remainder_2275_; uint64_t v___x_2276_; uint64_t v_half_2277_; uint8_t v___x_2278_; 
v_quotient_2271_ = lean_uint64_shift_right(v_value_2269_, v_shift_2270_);
v___x_2272_ = 1ULL;
v___x_2273_ = lean_uint64_shift_left(v___x_2272_, v_shift_2270_);
v___x_2274_ = lean_uint64_sub(v___x_2273_, v___x_2272_);
v_remainder_2275_ = lean_uint64_land(v_value_2269_, v___x_2274_);
v___x_2276_ = lean_uint64_sub(v_shift_2270_, v___x_2272_);
v_half_2277_ = lean_uint64_shift_left(v___x_2272_, v___x_2276_);
v___x_2278_ = lean_uint64_dec_lt(v_remainder_2275_, v_half_2277_);
if (v___x_2278_ == 0)
{
uint8_t v___x_2279_; 
v___x_2279_ = lean_uint64_dec_lt(v_half_2277_, v_remainder_2275_);
if (v___x_2279_ == 0)
{
uint64_t v___x_2280_; uint64_t v___x_2281_; uint8_t v___x_2282_; 
v___x_2280_ = lean_uint64_land(v_quotient_2271_, v___x_2272_);
v___x_2281_ = 0ULL;
v___x_2282_ = lean_uint64_dec_eq(v___x_2280_, v___x_2281_);
if (v___x_2282_ == 0)
{
uint64_t v___x_2283_; 
v___x_2283_ = lean_uint64_add(v_quotient_2271_, v___x_2272_);
return v___x_2283_;
}
else
{
return v_quotient_2271_;
}
}
else
{
uint64_t v___x_2284_; 
v___x_2284_ = lean_uint64_add(v_quotient_2271_, v___x_2272_);
return v___x_2284_;
}
}
else
{
return v_quotient_2271_;
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_FastMul_rse___boxed(lean_object* v_value_2285_, lean_object* v_shift_2286_){
_start:
{
uint64_t v_value_boxed_2287_; uint64_t v_shift_boxed_2288_; uint64_t v_res_2289_; lean_object* v_r_2290_; 
v_value_boxed_2287_ = lean_unbox_uint64(v_value_2285_);
lean_dec_ref(v_value_2285_);
v_shift_boxed_2288_ = lean_unbox_uint64(v_shift_2286_);
lean_dec_ref(v_shift_2286_);
v_res_2289_ = lp_competition_Submission_FastMul_rse(v_value_boxed_2287_, v_shift_boxed_2288_);
v_r_2290_ = lean_box_uint64(v_res_2289_);
return v_r_2290_;
}
}
LEAN_EXPORT uint64_t lp_competition_Submission_FastMul_rseAny(uint64_t v_value_2291_, uint64_t v_shift_2292_){
_start:
{
uint64_t v___x_2293_; uint8_t v___x_2294_; 
v___x_2293_ = 0ULL;
v___x_2294_ = lean_uint64_dec_eq(v_shift_2292_, v___x_2293_);
if (v___x_2294_ == 0)
{
uint64_t v___x_2295_; uint8_t v___x_2296_; 
v___x_2295_ = 64ULL;
v___x_2296_ = lean_uint64_dec_lt(v_shift_2292_, v___x_2295_);
if (v___x_2296_ == 0)
{
uint8_t v___x_2297_; 
v___x_2297_ = lean_uint64_dec_eq(v_shift_2292_, v___x_2295_);
if (v___x_2297_ == 0)
{
return v___x_2293_;
}
else
{
uint64_t v___x_2298_; uint8_t v___x_2299_; 
v___x_2298_ = 9223372036854775808ULL;
v___x_2299_ = lean_uint64_dec_lt(v___x_2298_, v_value_2291_);
if (v___x_2299_ == 0)
{
return v___x_2293_;
}
else
{
uint64_t v___x_2300_; 
v___x_2300_ = 1ULL;
return v___x_2300_;
}
}
}
else
{
uint64_t v_quotient_2301_; uint64_t v___x_2302_; uint64_t v___x_2303_; uint64_t v___x_2304_; uint64_t v_remainder_2305_; uint64_t v___x_2306_; uint64_t v_half_2307_; uint8_t v___x_2308_; 
v_quotient_2301_ = lean_uint64_shift_right(v_value_2291_, v_shift_2292_);
v___x_2302_ = 1ULL;
v___x_2303_ = lean_uint64_shift_left(v___x_2302_, v_shift_2292_);
v___x_2304_ = lean_uint64_sub(v___x_2303_, v___x_2302_);
v_remainder_2305_ = lean_uint64_land(v_value_2291_, v___x_2304_);
v___x_2306_ = lean_uint64_sub(v_shift_2292_, v___x_2302_);
v_half_2307_ = lean_uint64_shift_left(v___x_2302_, v___x_2306_);
v___x_2308_ = lean_uint64_dec_lt(v_remainder_2305_, v_half_2307_);
if (v___x_2308_ == 0)
{
uint8_t v___x_2309_; 
v___x_2309_ = lean_uint64_dec_lt(v_half_2307_, v_remainder_2305_);
if (v___x_2309_ == 0)
{
uint64_t v___x_2310_; uint8_t v___x_2311_; 
v___x_2310_ = lean_uint64_land(v_quotient_2301_, v___x_2302_);
v___x_2311_ = lean_uint64_dec_eq(v___x_2310_, v___x_2293_);
if (v___x_2311_ == 0)
{
uint64_t v___x_2312_; 
v___x_2312_ = lean_uint64_add(v_quotient_2301_, v___x_2302_);
return v___x_2312_;
}
else
{
return v_quotient_2301_;
}
}
else
{
uint64_t v___x_2313_; 
v___x_2313_ = lean_uint64_add(v_quotient_2301_, v___x_2302_);
return v___x_2313_;
}
}
else
{
return v_quotient_2301_;
}
}
}
else
{
return v_value_2291_;
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_FastMul_rseAny___boxed(lean_object* v_value_2314_, lean_object* v_shift_2315_){
_start:
{
uint64_t v_value_boxed_2316_; uint64_t v_shift_boxed_2317_; uint64_t v_res_2318_; lean_object* v_r_2319_; 
v_value_boxed_2316_ = lean_unbox_uint64(v_value_2314_);
lean_dec_ref(v_value_2314_);
v_shift_boxed_2317_ = lean_unbox_uint64(v_shift_2315_);
lean_dec_ref(v_shift_2315_);
v_res_2318_ = lp_competition_Submission_FastMul_rseAny(v_value_boxed_2316_, v_shift_boxed_2317_);
v_r_2319_ = lean_box_uint64(v_res_2318_);
return v_r_2319_;
}
}
LEAN_EXPORT uint32_t lp_competition_Submission_FastMul_mkW(uint8_t v_sign_2320_, uint32_t v_e_2321_, uint32_t v_f_2322_){
_start:
{
uint32_t v___y_2324_; 
if (v_sign_2320_ == 0)
{
uint32_t v___x_2333_; 
v___x_2333_ = 0;
v___y_2324_ = v___x_2333_;
goto v___jp_2323_;
}
else
{
uint32_t v___x_2334_; 
v___x_2334_ = 2147483648;
v___y_2324_ = v___x_2334_;
goto v___jp_2323_;
}
v___jp_2323_:
{
uint32_t v___x_2325_; uint32_t v___x_2326_; uint32_t v___x_2327_; uint32_t v___x_2328_; uint32_t v___x_2329_; uint32_t v___x_2330_; uint32_t v___x_2331_; uint32_t v___x_2332_; 
v___x_2325_ = 255;
v___x_2326_ = lean_uint32_land(v_e_2321_, v___x_2325_);
v___x_2327_ = 23;
v___x_2328_ = lean_uint32_shift_left(v___x_2326_, v___x_2327_);
v___x_2329_ = lean_uint32_lor(v___y_2324_, v___x_2328_);
v___x_2330_ = 8388607;
v___x_2331_ = lean_uint32_land(v_f_2322_, v___x_2330_);
v___x_2332_ = lean_uint32_lor(v___x_2329_, v___x_2331_);
return v___x_2332_;
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_FastMul_mkW___boxed(lean_object* v_sign_2335_, lean_object* v_e_2336_, lean_object* v_f_2337_){
_start:
{
uint8_t v_sign_boxed_2338_; uint32_t v_e_boxed_2339_; uint32_t v_f_boxed_2340_; uint32_t v_res_2341_; lean_object* v_r_2342_; 
v_sign_boxed_2338_ = lean_unbox(v_sign_2335_);
v_e_boxed_2339_ = lean_unbox_uint32(v_e_2336_);
lean_dec(v_e_2336_);
v_f_boxed_2340_ = lean_unbox_uint32(v_f_2337_);
lean_dec(v_f_2337_);
v_res_2341_ = lp_competition_Submission_FastMul_mkW(v_sign_boxed_2338_, v_e_boxed_2339_, v_f_boxed_2340_);
v_r_2342_ = lean_box_uint32(v_res_2341_);
return v_r_2342_;
}
}
LEAN_EXPORT uint32_t lp_competition_Submission_FastMul_fracW(uint64_t v_n_2343_){
_start:
{
uint64_t v___x_2344_; uint8_t v___x_2345_; 
v___x_2344_ = 8388608ULL;
v___x_2345_ = lean_uint64_dec_lt(v_n_2343_, v___x_2344_);
if (v___x_2345_ == 0)
{
uint64_t v___x_2346_; uint32_t v___x_2347_; 
v___x_2346_ = lean_uint64_sub(v_n_2343_, v___x_2344_);
v___x_2347_ = lean_uint64_to_uint32(v___x_2346_);
return v___x_2347_;
}
else
{
uint32_t v___x_2348_; 
v___x_2348_ = lean_uint32_once(&lp_competition_Submission_TunedAdd_fracW___closed__0, &lp_competition_Submission_TunedAdd_fracW___closed__0_once, _init_lp_competition_Submission_TunedAdd_fracW___closed__0);
return v___x_2348_;
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_FastMul_fracW___boxed(lean_object* v_n_2349_){
_start:
{
uint64_t v_n_boxed_2350_; uint32_t v_res_2351_; lean_object* v_r_2352_; 
v_n_boxed_2350_ = lean_unbox_uint64(v_n_2349_);
lean_dec_ref(v_n_2349_);
v_res_2351_ = lp_competition_Submission_FastMul_fracW(v_n_boxed_2350_);
v_r_2352_ = lean_box_uint32(v_res_2351_);
return v_r_2352_;
}
}
LEAN_EXPORT uint32_t lp_competition_Submission_FastMul_roundP(uint8_t v_sign_2353_, uint64_t v_product_2354_, uint64_t v_scale_2355_){
_start:
{
uint32_t v___y_2357_; uint32_t v___y_2361_; uint32_t v___y_2362_; uint32_t v___y_2367_; uint32_t v___y_2368_; uint32_t v___y_2369_; uint32_t v___y_2379_; uint32_t v___y_2380_; uint64_t v___x_2383_; uint64_t v___y_2385_; uint64_t v___y_2397_; uint64_t v___y_2398_; uint8_t v___y_2408_; uint64_t v___y_2409_; uint64_t v___y_2410_; uint64_t v___y_2417_; uint64_t v___y_2418_; uint64_t v___y_2424_; uint64_t v___y_2479_; uint64_t v___y_2480_; uint64_t v___y_2486_; uint64_t v___y_2487_; uint64_t v___y_2488_; uint64_t v___y_2489_; uint64_t v___y_2494_; uint64_t v___y_2495_; uint64_t v___y_2500_; uint64_t v___y_2501_; uint64_t v___y_2502_; uint64_t v___y_2503_; uint64_t v___y_2508_; uint64_t v___y_2509_; uint64_t v___y_2514_; uint64_t v___y_2515_; uint64_t v___y_2516_; uint64_t v___y_2517_; uint64_t v___y_2522_; uint64_t v___y_2523_; uint64_t v___y_2528_; uint64_t v___y_2529_; uint64_t v___y_2530_; uint64_t v___y_2531_; uint64_t v___y_2536_; uint64_t v___y_2537_; uint8_t v___x_2541_; 
v___x_2383_ = 0ULL;
v___x_2541_ = lean_uint64_dec_eq(v_product_2354_, v___x_2383_);
if (v___x_2541_ == 0)
{
uint64_t v___x_2542_; uint64_t v___y_2544_; uint64_t v___x_2547_; uint8_t v___x_2548_; 
v___x_2542_ = 32ULL;
v___x_2547_ = lean_uint64_shift_right(v_product_2354_, v___x_2542_);
v___x_2548_ = lean_uint64_dec_eq(v___x_2547_, v___x_2383_);
if (v___x_2548_ == 0)
{
v___y_2544_ = v___x_2547_;
goto v___jp_2543_;
}
else
{
v___y_2544_ = v_product_2354_;
goto v___jp_2543_;
}
v___jp_2543_:
{
uint64_t v___x_2545_; uint8_t v___x_2546_; 
v___x_2545_ = lean_uint64_shift_right(v_product_2354_, v___x_2542_);
v___x_2546_ = lean_uint64_dec_eq(v___x_2545_, v___x_2383_);
if (v___x_2546_ == 0)
{
v___y_2536_ = v___y_2544_;
v___y_2537_ = v___x_2542_;
goto v___jp_2535_;
}
else
{
v___y_2536_ = v___y_2544_;
v___y_2537_ = v___x_2383_;
goto v___jp_2535_;
}
}
}
else
{
if (v_sign_2353_ == 0)
{
uint32_t v___x_2549_; 
v___x_2549_ = 0;
return v___x_2549_;
}
else
{
uint32_t v___x_2550_; 
v___x_2550_ = 2147483648;
return v___x_2550_;
}
}
v___jp_2356_:
{
uint32_t v___x_2358_; uint32_t v___x_2359_; 
v___x_2358_ = 8388608;
v___x_2359_ = lean_uint32_lor(v___y_2357_, v___x_2358_);
return v___x_2359_;
}
v___jp_2360_:
{
uint32_t v___x_2363_; uint32_t v___x_2364_; uint32_t v___x_2365_; 
v___x_2363_ = 8388607;
v___x_2364_ = lean_uint32_land(v___y_2361_, v___x_2363_);
v___x_2365_ = lean_uint32_lor(v___y_2362_, v___x_2364_);
return v___x_2365_;
}
v___jp_2366_:
{
uint32_t v___x_2370_; uint32_t v___x_2371_; uint32_t v___x_2372_; uint32_t v___x_2373_; uint32_t v___x_2374_; uint32_t v___x_2375_; uint32_t v___x_2376_; uint32_t v___x_2377_; 
v___x_2370_ = 255;
v___x_2371_ = lean_uint32_land(v___y_2367_, v___x_2370_);
v___x_2372_ = 23;
v___x_2373_ = lean_uint32_shift_left(v___x_2371_, v___x_2372_);
v___x_2374_ = lean_uint32_lor(v___y_2369_, v___x_2373_);
v___x_2375_ = 8388607;
v___x_2376_ = lean_uint32_land(v___y_2368_, v___x_2375_);
v___x_2377_ = lean_uint32_lor(v___x_2374_, v___x_2376_);
return v___x_2377_;
}
v___jp_2378_:
{
if (v_sign_2353_ == 0)
{
uint32_t v___x_2381_; 
v___x_2381_ = 0;
v___y_2367_ = v___y_2379_;
v___y_2368_ = v___y_2380_;
v___y_2369_ = v___x_2381_;
goto v___jp_2366_;
}
else
{
uint32_t v___x_2382_; 
v___x_2382_ = 2147483648;
v___y_2367_ = v___y_2379_;
v___y_2368_ = v___y_2380_;
v___y_2369_ = v___x_2382_;
goto v___jp_2366_;
}
}
v___jp_2384_:
{
uint8_t v___x_2386_; 
v___x_2386_ = lean_uint64_dec_eq(v___y_2385_, v___x_2383_);
if (v___x_2386_ == 0)
{
uint64_t v___x_2387_; uint8_t v___x_2388_; 
v___x_2387_ = 8388608ULL;
v___x_2388_ = lean_uint64_dec_eq(v___y_2385_, v___x_2387_);
if (v___x_2388_ == 0)
{
uint32_t v___x_2389_; 
v___x_2389_ = lean_uint64_to_uint32(v___y_2385_);
if (v_sign_2353_ == 0)
{
uint32_t v___x_2390_; 
v___x_2390_ = 0;
v___y_2361_ = v___x_2389_;
v___y_2362_ = v___x_2390_;
goto v___jp_2360_;
}
else
{
uint32_t v___x_2391_; 
v___x_2391_ = 2147483648;
v___y_2361_ = v___x_2389_;
v___y_2362_ = v___x_2391_;
goto v___jp_2360_;
}
}
else
{
if (v_sign_2353_ == 0)
{
uint32_t v___x_2392_; 
v___x_2392_ = 0;
v___y_2357_ = v___x_2392_;
goto v___jp_2356_;
}
else
{
uint32_t v___x_2393_; 
v___x_2393_ = 2147483648;
v___y_2357_ = v___x_2393_;
goto v___jp_2356_;
}
}
}
else
{
if (v_sign_2353_ == 0)
{
uint32_t v___x_2394_; 
v___x_2394_ = 0;
return v___x_2394_;
}
else
{
uint32_t v___x_2395_; 
v___x_2395_ = 2147483648;
return v___x_2395_;
}
}
}
v___jp_2396_:
{
uint64_t v___x_2399_; uint64_t v_encodedExponent_2400_; uint32_t v___x_2401_; uint64_t v___x_2402_; uint8_t v___x_2403_; 
v___x_2399_ = 171ULL;
v_encodedExponent_2400_ = lean_uint64_sub(v___y_2397_, v___x_2399_);
v___x_2401_ = lean_uint64_to_uint32(v_encodedExponent_2400_);
v___x_2402_ = 8388608ULL;
v___x_2403_ = lean_uint64_dec_lt(v___y_2398_, v___x_2402_);
if (v___x_2403_ == 0)
{
uint64_t v___x_2404_; uint32_t v___x_2405_; 
v___x_2404_ = lean_uint64_sub(v___y_2398_, v___x_2402_);
v___x_2405_ = lean_uint64_to_uint32(v___x_2404_);
v___y_2379_ = v___x_2401_;
v___y_2380_ = v___x_2405_;
goto v___jp_2378_;
}
else
{
uint32_t v___x_2406_; 
v___x_2406_ = lean_uint32_once(&lp_competition_Submission_TunedAdd_fracW___closed__0, &lp_competition_Submission_TunedAdd_fracW___closed__0_once, _init_lp_competition_Submission_TunedAdd_fracW___closed__0);
v___y_2379_ = v___x_2401_;
v___y_2380_ = v___x_2406_;
goto v___jp_2378_;
}
}
v___jp_2407_:
{
uint64_t v___x_2411_; uint8_t v___x_2412_; 
v___x_2411_ = 425ULL;
v___x_2412_ = lean_uint64_dec_lt(v___x_2411_, v___y_2410_);
if (v___x_2412_ == 0)
{
if (v___y_2408_ == 0)
{
v___y_2397_ = v___y_2410_;
v___y_2398_ = v___y_2409_;
goto v___jp_2396_;
}
else
{
uint64_t v___x_2413_; 
v___x_2413_ = 8388608ULL;
v___y_2397_ = v___y_2410_;
v___y_2398_ = v___x_2413_;
goto v___jp_2396_;
}
}
else
{
if (v_sign_2353_ == 0)
{
uint32_t v___x_2414_; 
v___x_2414_ = 2139095040;
return v___x_2414_;
}
else
{
uint32_t v___x_2415_; 
v___x_2415_ = 4286578688;
return v___x_2415_;
}
}
}
v___jp_2416_:
{
uint64_t v___x_2419_; uint8_t v_carry_2420_; 
v___x_2419_ = 16777216ULL;
v_carry_2420_ = lean_uint64_dec_eq(v___y_2418_, v___x_2419_);
if (v_carry_2420_ == 0)
{
v___y_2408_ = v_carry_2420_;
v___y_2409_ = v___y_2418_;
v___y_2410_ = v___y_2417_;
goto v___jp_2407_;
}
else
{
uint64_t v___x_2421_; uint64_t v___x_2422_; 
v___x_2421_ = 1ULL;
v___x_2422_ = lean_uint64_add(v___y_2417_, v___x_2421_);
v___y_2408_ = v_carry_2420_;
v___y_2409_ = v___y_2418_;
v___y_2410_ = v___x_2422_;
goto v___jp_2407_;
}
}
v___jp_2423_:
{
uint64_t v_position_2425_; uint64_t v___x_2426_; uint8_t v___x_2427_; 
v_position_2425_ = lean_uint64_add(v___y_2424_, v_scale_2355_);
v___x_2426_ = 172ULL;
v___x_2427_ = lean_uint64_dec_lt(v_position_2425_, v___x_2426_);
if (v___x_2427_ == 0)
{
uint64_t v___x_2428_; uint8_t v___x_2429_; 
v___x_2428_ = 23ULL;
v___x_2429_ = lean_uint64_dec_lt(v___y_2424_, v___x_2428_);
if (v___x_2429_ == 0)
{
uint64_t v___x_2430_; uint8_t v___x_2431_; 
v___x_2430_ = lean_uint64_sub(v___y_2424_, v___x_2428_);
v___x_2431_ = lean_uint64_dec_eq(v___x_2430_, v___x_2383_);
if (v___x_2431_ == 0)
{
uint64_t v___x_2432_; uint8_t v___x_2433_; 
v___x_2432_ = 64ULL;
v___x_2433_ = lean_uint64_dec_lt(v___x_2430_, v___x_2432_);
if (v___x_2433_ == 0)
{
uint8_t v___x_2434_; 
v___x_2434_ = lean_uint64_dec_eq(v___x_2430_, v___x_2432_);
if (v___x_2434_ == 0)
{
v___y_2417_ = v_position_2425_;
v___y_2418_ = v___x_2383_;
goto v___jp_2416_;
}
else
{
uint64_t v___x_2435_; uint8_t v___x_2436_; 
v___x_2435_ = 9223372036854775808ULL;
v___x_2436_ = lean_uint64_dec_lt(v___x_2435_, v_product_2354_);
if (v___x_2436_ == 0)
{
v___y_2417_ = v_position_2425_;
v___y_2418_ = v___x_2383_;
goto v___jp_2416_;
}
else
{
uint64_t v___x_2437_; 
v___x_2437_ = 1ULL;
v___y_2417_ = v_position_2425_;
v___y_2418_ = v___x_2437_;
goto v___jp_2416_;
}
}
}
else
{
uint64_t v_quotient_2438_; uint64_t v___x_2439_; uint64_t v___x_2440_; uint64_t v___x_2441_; uint64_t v_remainder_2442_; uint64_t v___x_2443_; uint64_t v_half_2444_; uint8_t v___x_2445_; 
v_quotient_2438_ = lean_uint64_shift_right(v_product_2354_, v___x_2430_);
v___x_2439_ = 1ULL;
v___x_2440_ = lean_uint64_shift_left(v___x_2439_, v___x_2430_);
v___x_2441_ = lean_uint64_sub(v___x_2440_, v___x_2439_);
v_remainder_2442_ = lean_uint64_land(v_product_2354_, v___x_2441_);
v___x_2443_ = lean_uint64_sub(v___x_2430_, v___x_2439_);
v_half_2444_ = lean_uint64_shift_left(v___x_2439_, v___x_2443_);
v___x_2445_ = lean_uint64_dec_lt(v_remainder_2442_, v_half_2444_);
if (v___x_2445_ == 0)
{
uint8_t v___x_2446_; 
v___x_2446_ = lean_uint64_dec_lt(v_half_2444_, v_remainder_2442_);
if (v___x_2446_ == 0)
{
uint64_t v___x_2447_; uint8_t v___x_2448_; 
v___x_2447_ = lean_uint64_land(v_quotient_2438_, v___x_2439_);
v___x_2448_ = lean_uint64_dec_eq(v___x_2447_, v___x_2383_);
if (v___x_2448_ == 0)
{
uint64_t v___x_2449_; 
v___x_2449_ = lean_uint64_add(v_quotient_2438_, v___x_2439_);
v___y_2417_ = v_position_2425_;
v___y_2418_ = v___x_2449_;
goto v___jp_2416_;
}
else
{
v___y_2417_ = v_position_2425_;
v___y_2418_ = v_quotient_2438_;
goto v___jp_2416_;
}
}
else
{
uint64_t v___x_2450_; 
v___x_2450_ = lean_uint64_add(v_quotient_2438_, v___x_2439_);
v___y_2417_ = v_position_2425_;
v___y_2418_ = v___x_2450_;
goto v___jp_2416_;
}
}
else
{
v___y_2417_ = v_position_2425_;
v___y_2418_ = v_quotient_2438_;
goto v___jp_2416_;
}
}
}
else
{
v___y_2417_ = v_position_2425_;
v___y_2418_ = v_product_2354_;
goto v___jp_2416_;
}
}
else
{
uint64_t v___x_2451_; uint64_t v___x_2452_; 
v___x_2451_ = lean_uint64_sub(v___x_2428_, v___y_2424_);
v___x_2452_ = lean_uint64_shift_left(v_product_2354_, v___x_2451_);
v___y_2417_ = v_position_2425_;
v___y_2418_ = v___x_2452_;
goto v___jp_2416_;
}
}
else
{
uint64_t v___x_2453_; uint8_t v___x_2454_; 
v___x_2453_ = 149ULL;
v___x_2454_ = lean_uint64_dec_lt(v_scale_2355_, v___x_2453_);
if (v___x_2454_ == 0)
{
uint64_t v___x_2455_; uint64_t v___x_2456_; 
v___x_2455_ = lean_uint64_sub(v_scale_2355_, v___x_2453_);
v___x_2456_ = lean_uint64_shift_left(v_product_2354_, v___x_2455_);
v___y_2385_ = v___x_2456_;
goto v___jp_2384_;
}
else
{
uint64_t v___x_2457_; uint8_t v___x_2458_; 
v___x_2457_ = lean_uint64_sub(v___x_2453_, v_scale_2355_);
v___x_2458_ = lean_uint64_dec_eq(v___x_2457_, v___x_2383_);
if (v___x_2458_ == 0)
{
uint64_t v___x_2459_; uint8_t v___x_2460_; 
v___x_2459_ = 64ULL;
v___x_2460_ = lean_uint64_dec_lt(v___x_2457_, v___x_2459_);
if (v___x_2460_ == 0)
{
uint8_t v___x_2461_; 
v___x_2461_ = lean_uint64_dec_eq(v___x_2457_, v___x_2459_);
if (v___x_2461_ == 0)
{
v___y_2385_ = v___x_2383_;
goto v___jp_2384_;
}
else
{
uint64_t v___x_2462_; uint8_t v___x_2463_; 
v___x_2462_ = 9223372036854775808ULL;
v___x_2463_ = lean_uint64_dec_lt(v___x_2462_, v_product_2354_);
if (v___x_2463_ == 0)
{
v___y_2385_ = v___x_2383_;
goto v___jp_2384_;
}
else
{
uint64_t v___x_2464_; 
v___x_2464_ = 1ULL;
v___y_2385_ = v___x_2464_;
goto v___jp_2384_;
}
}
}
else
{
uint64_t v_quotient_2465_; uint64_t v___x_2466_; uint64_t v___x_2467_; uint64_t v___x_2468_; uint64_t v_remainder_2469_; uint64_t v___x_2470_; uint64_t v_half_2471_; uint8_t v___x_2472_; 
v_quotient_2465_ = lean_uint64_shift_right(v_product_2354_, v___x_2457_);
v___x_2466_ = 1ULL;
v___x_2467_ = lean_uint64_shift_left(v___x_2466_, v___x_2457_);
v___x_2468_ = lean_uint64_sub(v___x_2467_, v___x_2466_);
v_remainder_2469_ = lean_uint64_land(v_product_2354_, v___x_2468_);
v___x_2470_ = lean_uint64_sub(v___x_2457_, v___x_2466_);
v_half_2471_ = lean_uint64_shift_left(v___x_2466_, v___x_2470_);
v___x_2472_ = lean_uint64_dec_lt(v_remainder_2469_, v_half_2471_);
if (v___x_2472_ == 0)
{
uint8_t v___x_2473_; 
v___x_2473_ = lean_uint64_dec_lt(v_half_2471_, v_remainder_2469_);
if (v___x_2473_ == 0)
{
uint64_t v___x_2474_; uint8_t v___x_2475_; 
v___x_2474_ = lean_uint64_land(v_quotient_2465_, v___x_2466_);
v___x_2475_ = lean_uint64_dec_eq(v___x_2474_, v___x_2383_);
if (v___x_2475_ == 0)
{
uint64_t v___x_2476_; 
v___x_2476_ = lean_uint64_add(v_quotient_2465_, v___x_2466_);
v___y_2385_ = v___x_2476_;
goto v___jp_2384_;
}
else
{
v___y_2385_ = v_quotient_2465_;
goto v___jp_2384_;
}
}
else
{
uint64_t v___x_2477_; 
v___x_2477_ = lean_uint64_add(v_quotient_2465_, v___x_2466_);
v___y_2385_ = v___x_2477_;
goto v___jp_2384_;
}
}
else
{
v___y_2385_ = v_quotient_2465_;
goto v___jp_2384_;
}
}
}
else
{
v___y_2385_ = v_product_2354_;
goto v___jp_2384_;
}
}
}
}
v___jp_2478_:
{
uint64_t v___x_2481_; uint64_t v___x_2482_; uint8_t v___x_2483_; 
v___x_2481_ = 1ULL;
v___x_2482_ = lean_uint64_shift_right(v___y_2479_, v___x_2481_);
v___x_2483_ = lean_uint64_dec_eq(v___x_2482_, v___x_2383_);
if (v___x_2483_ == 0)
{
uint64_t v___x_2484_; 
v___x_2484_ = lean_uint64_add(v___y_2480_, v___x_2481_);
v___y_2424_ = v___x_2484_;
goto v___jp_2423_;
}
else
{
v___y_2424_ = v___y_2480_;
goto v___jp_2423_;
}
}
v___jp_2485_:
{
uint64_t v___x_2490_; uint8_t v___x_2491_; 
v___x_2490_ = lean_uint64_shift_right(v___y_2486_, v___y_2488_);
v___x_2491_ = lean_uint64_dec_eq(v___x_2490_, v___x_2383_);
if (v___x_2491_ == 0)
{
uint64_t v___x_2492_; 
v___x_2492_ = lean_uint64_add(v___y_2487_, v___y_2488_);
v___y_2479_ = v___y_2489_;
v___y_2480_ = v___x_2492_;
goto v___jp_2478_;
}
else
{
v___y_2479_ = v___y_2489_;
v___y_2480_ = v___y_2487_;
goto v___jp_2478_;
}
}
v___jp_2493_:
{
uint64_t v___x_2496_; uint64_t v___x_2497_; uint8_t v___x_2498_; 
v___x_2496_ = 2ULL;
v___x_2497_ = lean_uint64_shift_right(v___y_2494_, v___x_2496_);
v___x_2498_ = lean_uint64_dec_eq(v___x_2497_, v___x_2383_);
if (v___x_2498_ == 0)
{
v___y_2486_ = v___y_2494_;
v___y_2487_ = v___y_2495_;
v___y_2488_ = v___x_2496_;
v___y_2489_ = v___x_2497_;
goto v___jp_2485_;
}
else
{
v___y_2486_ = v___y_2494_;
v___y_2487_ = v___y_2495_;
v___y_2488_ = v___x_2496_;
v___y_2489_ = v___y_2494_;
goto v___jp_2485_;
}
}
v___jp_2499_:
{
uint64_t v___x_2504_; uint8_t v___x_2505_; 
v___x_2504_ = lean_uint64_shift_right(v___y_2501_, v___y_2502_);
v___x_2505_ = lean_uint64_dec_eq(v___x_2504_, v___x_2383_);
if (v___x_2505_ == 0)
{
uint64_t v___x_2506_; 
v___x_2506_ = lean_uint64_add(v___y_2500_, v___y_2502_);
v___y_2494_ = v___y_2503_;
v___y_2495_ = v___x_2506_;
goto v___jp_2493_;
}
else
{
v___y_2494_ = v___y_2503_;
v___y_2495_ = v___y_2500_;
goto v___jp_2493_;
}
}
v___jp_2507_:
{
uint64_t v___x_2510_; uint64_t v___x_2511_; uint8_t v___x_2512_; 
v___x_2510_ = 4ULL;
v___x_2511_ = lean_uint64_shift_right(v___y_2508_, v___x_2510_);
v___x_2512_ = lean_uint64_dec_eq(v___x_2511_, v___x_2383_);
if (v___x_2512_ == 0)
{
v___y_2500_ = v___y_2509_;
v___y_2501_ = v___y_2508_;
v___y_2502_ = v___x_2510_;
v___y_2503_ = v___x_2511_;
goto v___jp_2499_;
}
else
{
v___y_2500_ = v___y_2509_;
v___y_2501_ = v___y_2508_;
v___y_2502_ = v___x_2510_;
v___y_2503_ = v___y_2508_;
goto v___jp_2499_;
}
}
v___jp_2513_:
{
uint64_t v___x_2518_; uint8_t v___x_2519_; 
v___x_2518_ = lean_uint64_shift_right(v___y_2515_, v___y_2514_);
v___x_2519_ = lean_uint64_dec_eq(v___x_2518_, v___x_2383_);
if (v___x_2519_ == 0)
{
uint64_t v___x_2520_; 
v___x_2520_ = lean_uint64_add(v___y_2516_, v___y_2514_);
v___y_2508_ = v___y_2517_;
v___y_2509_ = v___x_2520_;
goto v___jp_2507_;
}
else
{
v___y_2508_ = v___y_2517_;
v___y_2509_ = v___y_2516_;
goto v___jp_2507_;
}
}
v___jp_2521_:
{
uint64_t v___x_2524_; uint64_t v___x_2525_; uint8_t v___x_2526_; 
v___x_2524_ = 8ULL;
v___x_2525_ = lean_uint64_shift_right(v___y_2522_, v___x_2524_);
v___x_2526_ = lean_uint64_dec_eq(v___x_2525_, v___x_2383_);
if (v___x_2526_ == 0)
{
v___y_2514_ = v___x_2524_;
v___y_2515_ = v___y_2522_;
v___y_2516_ = v___y_2523_;
v___y_2517_ = v___x_2525_;
goto v___jp_2513_;
}
else
{
v___y_2514_ = v___x_2524_;
v___y_2515_ = v___y_2522_;
v___y_2516_ = v___y_2523_;
v___y_2517_ = v___y_2522_;
goto v___jp_2513_;
}
}
v___jp_2527_:
{
uint64_t v___x_2532_; uint8_t v___x_2533_; 
v___x_2532_ = lean_uint64_shift_right(v___y_2530_, v___y_2528_);
v___x_2533_ = lean_uint64_dec_eq(v___x_2532_, v___x_2383_);
if (v___x_2533_ == 0)
{
uint64_t v___x_2534_; 
v___x_2534_ = lean_uint64_add(v___y_2529_, v___y_2528_);
v___y_2522_ = v___y_2531_;
v___y_2523_ = v___x_2534_;
goto v___jp_2521_;
}
else
{
v___y_2522_ = v___y_2531_;
v___y_2523_ = v___y_2529_;
goto v___jp_2521_;
}
}
v___jp_2535_:
{
uint64_t v___x_2538_; uint64_t v___x_2539_; uint8_t v___x_2540_; 
v___x_2538_ = 16ULL;
v___x_2539_ = lean_uint64_shift_right(v___y_2536_, v___x_2538_);
v___x_2540_ = lean_uint64_dec_eq(v___x_2539_, v___x_2383_);
if (v___x_2540_ == 0)
{
v___y_2528_ = v___x_2538_;
v___y_2529_ = v___y_2537_;
v___y_2530_ = v___y_2536_;
v___y_2531_ = v___x_2539_;
goto v___jp_2527_;
}
else
{
v___y_2528_ = v___x_2538_;
v___y_2529_ = v___y_2537_;
v___y_2530_ = v___y_2536_;
v___y_2531_ = v___y_2536_;
goto v___jp_2527_;
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_FastMul_roundP___boxed(lean_object* v_sign_2551_, lean_object* v_product_2552_, lean_object* v_scale_2553_){
_start:
{
uint8_t v_sign_boxed_2554_; uint64_t v_product_boxed_2555_; uint64_t v_scale_boxed_2556_; uint32_t v_res_2557_; lean_object* v_r_2558_; 
v_sign_boxed_2554_ = lean_unbox(v_sign_2551_);
v_product_boxed_2555_ = lean_unbox_uint64(v_product_2552_);
lean_dec_ref(v_product_2552_);
v_scale_boxed_2556_ = lean_unbox_uint64(v_scale_2553_);
lean_dec_ref(v_scale_2553_);
v_res_2557_ = lp_competition_Submission_FastMul_roundP(v_sign_boxed_2554_, v_product_boxed_2555_, v_scale_boxed_2556_);
v_r_2558_ = lean_box_uint32(v_res_2557_);
return v_r_2558_;
}
}
LEAN_EXPORT uint32_t lp_competition_Submission_FastMul_core(uint32_t v_xBits_2559_, uint32_t v_yBits_2560_){
_start:
{
uint32_t v___y_2562_; uint32_t v___y_2566_; uint32_t v___y_2567_; uint32_t v___y_2568_; uint8_t v___y_2572_; uint32_t v___y_2573_; uint64_t v___y_2574_; uint64_t v___y_2575_; uint32_t v___x_2586_; uint32_t v___x_2587_; uint32_t v___x_2588_; uint32_t v___y_2590_; uint32_t v___y_2591_; uint32_t v___y_2592_; uint32_t v___y_2593_; uint32_t v___y_2600_; uint8_t v___y_2601_; uint32_t v___y_2602_; uint32_t v___y_2603_; uint64_t v___y_2607_; uint8_t v___y_2608_; uint32_t v___y_2609_; uint64_t v___y_2610_; uint64_t v___y_2611_; uint64_t v___y_2621_; uint8_t v___y_2622_; uint8_t v___y_2623_; uint32_t v___y_2624_; uint64_t v___y_2625_; uint64_t v___y_2626_; uint8_t v___y_2633_; uint32_t v___y_2634_; uint64_t v___y_2635_; uint64_t v___y_2636_; uint64_t v___y_2637_; uint64_t v___y_2643_; uint64_t v___y_2644_; uint8_t v___y_2645_; uint32_t v___y_2646_; uint64_t v___y_2647_; uint64_t v___y_2648_; uint64_t v___y_2703_; uint64_t v___y_2704_; uint8_t v___y_2705_; uint32_t v___y_2706_; uint64_t v___y_2707_; uint64_t v___y_2708_; uint64_t v___y_2709_; uint64_t v___y_2715_; uint64_t v___y_2716_; uint64_t v___y_2717_; uint8_t v___y_2718_; uint32_t v___y_2719_; uint64_t v___y_2720_; uint64_t v___y_2721_; uint64_t v___y_2722_; uint64_t v___y_2723_; uint64_t v___y_2728_; uint64_t v___y_2729_; uint8_t v___y_2730_; uint32_t v___y_2731_; uint64_t v___y_2732_; uint64_t v___y_2733_; uint64_t v___y_2734_; uint64_t v___y_2739_; uint64_t v___y_2740_; uint64_t v___y_2741_; uint64_t v___y_2742_; uint8_t v___y_2743_; uint32_t v___y_2744_; uint64_t v___y_2745_; uint64_t v___y_2746_; uint64_t v___y_2747_; uint64_t v___y_2752_; uint64_t v___y_2753_; uint8_t v___y_2754_; uint32_t v___y_2755_; uint64_t v___y_2756_; uint64_t v___y_2757_; uint64_t v___y_2758_; uint64_t v___y_2763_; uint64_t v___y_2764_; uint64_t v___y_2765_; uint64_t v___y_2766_; uint64_t v___y_2767_; uint8_t v___y_2768_; uint32_t v___y_2769_; uint64_t v___y_2770_; uint64_t v___y_2771_; uint64_t v___y_2776_; uint64_t v___y_2777_; uint64_t v___y_2778_; uint8_t v___y_2779_; uint32_t v___y_2780_; uint64_t v___y_2781_; uint64_t v___y_2782_; uint64_t v___y_2787_; uint64_t v___y_2788_; uint64_t v___y_2789_; uint8_t v___y_2790_; uint32_t v___y_2791_; uint64_t v___y_2792_; uint64_t v___y_2793_; uint64_t v___y_2794_; uint64_t v___y_2795_; uint64_t v___y_2800_; uint64_t v___y_2801_; uint64_t v___y_2802_; uint8_t v___y_2803_; uint32_t v___y_2804_; uint64_t v___y_2805_; uint64_t v___y_2806_; uint64_t v___y_2811_; uint64_t v___y_2812_; uint64_t v___y_2813_; uint8_t v___y_2814_; uint32_t v___y_2815_; uint64_t v___y_2816_; uint64_t v___y_2817_; uint64_t v___y_2821_; uint64_t v___y_2822_; uint8_t v___y_2823_; uint32_t v___y_2824_; uint64_t v___y_2825_; uint64_t v___y_2826_; uint32_t v_xExponent_2836_; uint32_t v___x_2837_; uint32_t v_yExponent_2838_; uint64_t v___y_2840_; uint8_t v___y_2841_; uint32_t v___y_2842_; uint64_t v___y_2843_; uint64_t v___y_2844_; uint8_t v___y_2851_; uint32_t v___y_2852_; uint64_t v___y_2853_; uint64_t v___y_2854_; uint32_t v___y_2861_; uint8_t v___y_2862_; uint32_t v___y_2863_; uint64_t v___y_2864_; uint8_t v___y_2872_; uint8_t v___y_2887_; uint8_t v___y_2888_; uint8_t v___y_2890_; uint32_t v___x_2897_; uint32_t v___x_2898_; uint32_t v___x_2899_; uint8_t v___x_2900_; 
v___x_2586_ = 23;
v___x_2587_ = lean_uint32_shift_right(v_xBits_2559_, v___x_2586_);
v___x_2588_ = 255;
v_xExponent_2836_ = lean_uint32_land(v___x_2587_, v___x_2588_);
v___x_2837_ = lean_uint32_shift_right(v_yBits_2560_, v___x_2586_);
v_yExponent_2838_ = lean_uint32_land(v___x_2837_, v___x_2588_);
v___x_2897_ = 2147483648;
v___x_2898_ = lean_uint32_land(v_xBits_2559_, v___x_2897_);
v___x_2899_ = 0;
v___x_2900_ = lean_uint32_dec_eq(v___x_2898_, v___x_2899_);
if (v___x_2900_ == 0)
{
uint8_t v___x_2901_; 
v___x_2901_ = 1;
v___y_2890_ = v___x_2901_;
goto v___jp_2889_;
}
else
{
uint8_t v___x_2902_; 
v___x_2902_ = 0;
v___y_2890_ = v___x_2902_;
goto v___jp_2889_;
}
v___jp_2561_:
{
uint32_t v___x_2563_; uint32_t v___x_2564_; 
v___x_2563_ = 8388608;
v___x_2564_ = lean_uint32_lor(v___y_2562_, v___x_2563_);
return v___x_2564_;
}
v___jp_2565_:
{
uint32_t v___x_2569_; uint32_t v___x_2570_; 
v___x_2569_ = lean_uint32_land(v___y_2567_, v___y_2566_);
v___x_2570_ = lean_uint32_lor(v___y_2568_, v___x_2569_);
return v___x_2570_;
}
v___jp_2571_:
{
uint8_t v___x_2576_; 
v___x_2576_ = lean_uint64_dec_eq(v___y_2575_, v___y_2574_);
if (v___x_2576_ == 0)
{
uint64_t v___x_2577_; uint8_t v___x_2578_; 
v___x_2577_ = 8388608ULL;
v___x_2578_ = lean_uint64_dec_eq(v___y_2575_, v___x_2577_);
if (v___x_2578_ == 0)
{
uint32_t v___x_2579_; 
v___x_2579_ = lean_uint64_to_uint32(v___y_2575_);
if (v___y_2572_ == 0)
{
uint32_t v___x_2580_; 
v___x_2580_ = 0;
v___y_2566_ = v___y_2573_;
v___y_2567_ = v___x_2579_;
v___y_2568_ = v___x_2580_;
goto v___jp_2565_;
}
else
{
uint32_t v___x_2581_; 
v___x_2581_ = 2147483648;
v___y_2566_ = v___y_2573_;
v___y_2567_ = v___x_2579_;
v___y_2568_ = v___x_2581_;
goto v___jp_2565_;
}
}
else
{
if (v___y_2572_ == 0)
{
uint32_t v___x_2582_; 
v___x_2582_ = 0;
v___y_2562_ = v___x_2582_;
goto v___jp_2561_;
}
else
{
uint32_t v___x_2583_; 
v___x_2583_ = 2147483648;
v___y_2562_ = v___x_2583_;
goto v___jp_2561_;
}
}
}
else
{
if (v___y_2572_ == 0)
{
uint32_t v___x_2584_; 
v___x_2584_ = 0;
return v___x_2584_;
}
else
{
uint32_t v___x_2585_; 
v___x_2585_ = 2147483648;
return v___x_2585_;
}
}
}
v___jp_2589_:
{
uint32_t v___x_2594_; uint32_t v___x_2595_; uint32_t v___x_2596_; uint32_t v___x_2597_; uint32_t v___x_2598_; 
v___x_2594_ = lean_uint32_land(v___y_2590_, v___x_2588_);
v___x_2595_ = lean_uint32_shift_left(v___x_2594_, v___x_2586_);
v___x_2596_ = lean_uint32_lor(v___y_2593_, v___x_2595_);
v___x_2597_ = lean_uint32_land(v___y_2592_, v___y_2591_);
v___x_2598_ = lean_uint32_lor(v___x_2596_, v___x_2597_);
return v___x_2598_;
}
v___jp_2599_:
{
if (v___y_2601_ == 0)
{
uint32_t v___x_2604_; 
v___x_2604_ = 0;
v___y_2590_ = v___y_2600_;
v___y_2591_ = v___y_2602_;
v___y_2592_ = v___y_2603_;
v___y_2593_ = v___x_2604_;
goto v___jp_2589_;
}
else
{
uint32_t v___x_2605_; 
v___x_2605_ = 2147483648;
v___y_2590_ = v___y_2600_;
v___y_2591_ = v___y_2602_;
v___y_2592_ = v___y_2603_;
v___y_2593_ = v___x_2605_;
goto v___jp_2589_;
}
}
v___jp_2606_:
{
uint64_t v___x_2612_; uint64_t v_encodedExponent_2613_; uint32_t v___x_2614_; uint64_t v___x_2615_; uint8_t v___x_2616_; 
v___x_2612_ = 171ULL;
v_encodedExponent_2613_ = lean_uint64_sub(v___y_2607_, v___x_2612_);
v___x_2614_ = lean_uint64_to_uint32(v_encodedExponent_2613_);
v___x_2615_ = 8388608ULL;
v___x_2616_ = lean_uint64_dec_lt(v___y_2611_, v___x_2615_);
if (v___x_2616_ == 0)
{
uint64_t v___x_2617_; uint32_t v___x_2618_; 
v___x_2617_ = lean_uint64_sub(v___y_2611_, v___x_2615_);
v___x_2618_ = lean_uint64_to_uint32(v___x_2617_);
v___y_2600_ = v___x_2614_;
v___y_2601_ = v___y_2608_;
v___y_2602_ = v___y_2609_;
v___y_2603_ = v___x_2618_;
goto v___jp_2599_;
}
else
{
uint32_t v___x_2619_; 
v___x_2619_ = lean_uint64_to_uint32(v___y_2610_);
v___y_2600_ = v___x_2614_;
v___y_2601_ = v___y_2608_;
v___y_2602_ = v___y_2609_;
v___y_2603_ = v___x_2619_;
goto v___jp_2599_;
}
}
v___jp_2620_:
{
uint64_t v___x_2627_; uint8_t v___x_2628_; 
v___x_2627_ = 425ULL;
v___x_2628_ = lean_uint64_dec_lt(v___x_2627_, v___y_2626_);
if (v___x_2628_ == 0)
{
if (v___y_2622_ == 0)
{
v___y_2607_ = v___y_2626_;
v___y_2608_ = v___y_2623_;
v___y_2609_ = v___y_2624_;
v___y_2610_ = v___y_2625_;
v___y_2611_ = v___y_2621_;
goto v___jp_2606_;
}
else
{
uint64_t v___x_2629_; 
v___x_2629_ = 8388608ULL;
v___y_2607_ = v___y_2626_;
v___y_2608_ = v___y_2623_;
v___y_2609_ = v___y_2624_;
v___y_2610_ = v___y_2625_;
v___y_2611_ = v___x_2629_;
goto v___jp_2606_;
}
}
else
{
if (v___y_2623_ == 0)
{
uint32_t v___x_2630_; 
v___x_2630_ = 2139095040;
return v___x_2630_;
}
else
{
uint32_t v___x_2631_; 
v___x_2631_ = 4286578688;
return v___x_2631_;
}
}
}
v___jp_2632_:
{
uint64_t v___x_2638_; uint8_t v_carry_2639_; 
v___x_2638_ = 16777216ULL;
v_carry_2639_ = lean_uint64_dec_eq(v___y_2637_, v___x_2638_);
if (v_carry_2639_ == 0)
{
v___y_2621_ = v___y_2637_;
v___y_2622_ = v_carry_2639_;
v___y_2623_ = v___y_2633_;
v___y_2624_ = v___y_2634_;
v___y_2625_ = v___y_2636_;
v___y_2626_ = v___y_2635_;
goto v___jp_2620_;
}
else
{
uint64_t v___x_2640_; uint64_t v___x_2641_; 
v___x_2640_ = 1ULL;
v___x_2641_ = lean_uint64_add(v___y_2635_, v___x_2640_);
v___y_2621_ = v___y_2637_;
v___y_2622_ = v_carry_2639_;
v___y_2623_ = v___y_2633_;
v___y_2624_ = v___y_2634_;
v___y_2625_ = v___y_2636_;
v___y_2626_ = v___x_2641_;
goto v___jp_2620_;
}
}
v___jp_2642_:
{
uint64_t v_position_2649_; uint64_t v___x_2650_; uint8_t v___x_2651_; 
v_position_2649_ = lean_uint64_add(v___y_2648_, v___y_2643_);
v___x_2650_ = 172ULL;
v___x_2651_ = lean_uint64_dec_lt(v_position_2649_, v___x_2650_);
if (v___x_2651_ == 0)
{
uint64_t v___x_2652_; uint8_t v___x_2653_; 
v___x_2652_ = 23ULL;
v___x_2653_ = lean_uint64_dec_lt(v___y_2648_, v___x_2652_);
if (v___x_2653_ == 0)
{
uint64_t v___x_2654_; uint8_t v___x_2655_; 
v___x_2654_ = lean_uint64_sub(v___y_2648_, v___x_2652_);
v___x_2655_ = lean_uint64_dec_eq(v___x_2654_, v___y_2647_);
if (v___x_2655_ == 0)
{
uint64_t v___x_2656_; uint8_t v___x_2657_; 
v___x_2656_ = 64ULL;
v___x_2657_ = lean_uint64_dec_lt(v___x_2654_, v___x_2656_);
if (v___x_2657_ == 0)
{
uint8_t v___x_2658_; 
v___x_2658_ = lean_uint64_dec_eq(v___x_2654_, v___x_2656_);
if (v___x_2658_ == 0)
{
v___y_2633_ = v___y_2645_;
v___y_2634_ = v___y_2646_;
v___y_2635_ = v_position_2649_;
v___y_2636_ = v___y_2647_;
v___y_2637_ = v___y_2647_;
goto v___jp_2632_;
}
else
{
uint64_t v___x_2659_; uint8_t v___x_2660_; 
v___x_2659_ = 9223372036854775808ULL;
v___x_2660_ = lean_uint64_dec_lt(v___x_2659_, v___y_2644_);
if (v___x_2660_ == 0)
{
v___y_2633_ = v___y_2645_;
v___y_2634_ = v___y_2646_;
v___y_2635_ = v_position_2649_;
v___y_2636_ = v___y_2647_;
v___y_2637_ = v___y_2647_;
goto v___jp_2632_;
}
else
{
uint64_t v___x_2661_; 
v___x_2661_ = 1ULL;
v___y_2633_ = v___y_2645_;
v___y_2634_ = v___y_2646_;
v___y_2635_ = v_position_2649_;
v___y_2636_ = v___y_2647_;
v___y_2637_ = v___x_2661_;
goto v___jp_2632_;
}
}
}
else
{
uint64_t v_quotient_2662_; uint64_t v___x_2663_; uint64_t v___x_2664_; uint64_t v___x_2665_; uint64_t v_remainder_2666_; uint64_t v___x_2667_; uint64_t v_half_2668_; uint8_t v___x_2669_; 
v_quotient_2662_ = lean_uint64_shift_right(v___y_2644_, v___x_2654_);
v___x_2663_ = 1ULL;
v___x_2664_ = lean_uint64_shift_left(v___x_2663_, v___x_2654_);
v___x_2665_ = lean_uint64_sub(v___x_2664_, v___x_2663_);
v_remainder_2666_ = lean_uint64_land(v___y_2644_, v___x_2665_);
v___x_2667_ = lean_uint64_sub(v___x_2654_, v___x_2663_);
v_half_2668_ = lean_uint64_shift_left(v___x_2663_, v___x_2667_);
v___x_2669_ = lean_uint64_dec_lt(v_remainder_2666_, v_half_2668_);
if (v___x_2669_ == 0)
{
uint8_t v___x_2670_; 
v___x_2670_ = lean_uint64_dec_lt(v_half_2668_, v_remainder_2666_);
if (v___x_2670_ == 0)
{
uint64_t v___x_2671_; uint8_t v___x_2672_; 
v___x_2671_ = lean_uint64_land(v_quotient_2662_, v___x_2663_);
v___x_2672_ = lean_uint64_dec_eq(v___x_2671_, v___y_2647_);
if (v___x_2672_ == 0)
{
uint64_t v___x_2673_; 
v___x_2673_ = lean_uint64_add(v_quotient_2662_, v___x_2663_);
v___y_2633_ = v___y_2645_;
v___y_2634_ = v___y_2646_;
v___y_2635_ = v_position_2649_;
v___y_2636_ = v___y_2647_;
v___y_2637_ = v___x_2673_;
goto v___jp_2632_;
}
else
{
v___y_2633_ = v___y_2645_;
v___y_2634_ = v___y_2646_;
v___y_2635_ = v_position_2649_;
v___y_2636_ = v___y_2647_;
v___y_2637_ = v_quotient_2662_;
goto v___jp_2632_;
}
}
else
{
uint64_t v___x_2674_; 
v___x_2674_ = lean_uint64_add(v_quotient_2662_, v___x_2663_);
v___y_2633_ = v___y_2645_;
v___y_2634_ = v___y_2646_;
v___y_2635_ = v_position_2649_;
v___y_2636_ = v___y_2647_;
v___y_2637_ = v___x_2674_;
goto v___jp_2632_;
}
}
else
{
v___y_2633_ = v___y_2645_;
v___y_2634_ = v___y_2646_;
v___y_2635_ = v_position_2649_;
v___y_2636_ = v___y_2647_;
v___y_2637_ = v_quotient_2662_;
goto v___jp_2632_;
}
}
}
else
{
v___y_2633_ = v___y_2645_;
v___y_2634_ = v___y_2646_;
v___y_2635_ = v_position_2649_;
v___y_2636_ = v___y_2647_;
v___y_2637_ = v___y_2644_;
goto v___jp_2632_;
}
}
else
{
uint64_t v___x_2675_; uint64_t v___x_2676_; 
v___x_2675_ = lean_uint64_sub(v___x_2652_, v___y_2648_);
v___x_2676_ = lean_uint64_shift_left(v___y_2644_, v___x_2675_);
v___y_2633_ = v___y_2645_;
v___y_2634_ = v___y_2646_;
v___y_2635_ = v_position_2649_;
v___y_2636_ = v___y_2647_;
v___y_2637_ = v___x_2676_;
goto v___jp_2632_;
}
}
else
{
uint64_t v___x_2677_; uint8_t v___x_2678_; 
v___x_2677_ = 149ULL;
v___x_2678_ = lean_uint64_dec_lt(v___y_2643_, v___x_2677_);
if (v___x_2678_ == 0)
{
uint64_t v___x_2679_; uint64_t v___x_2680_; 
v___x_2679_ = lean_uint64_sub(v___y_2643_, v___x_2677_);
v___x_2680_ = lean_uint64_shift_left(v___y_2644_, v___x_2679_);
v___y_2572_ = v___y_2645_;
v___y_2573_ = v___y_2646_;
v___y_2574_ = v___y_2647_;
v___y_2575_ = v___x_2680_;
goto v___jp_2571_;
}
else
{
uint64_t v___x_2681_; uint8_t v___x_2682_; 
v___x_2681_ = lean_uint64_sub(v___x_2677_, v___y_2643_);
v___x_2682_ = lean_uint64_dec_eq(v___x_2681_, v___y_2647_);
if (v___x_2682_ == 0)
{
uint64_t v___x_2683_; uint8_t v___x_2684_; 
v___x_2683_ = 64ULL;
v___x_2684_ = lean_uint64_dec_lt(v___x_2681_, v___x_2683_);
if (v___x_2684_ == 0)
{
uint8_t v___x_2685_; 
v___x_2685_ = lean_uint64_dec_eq(v___x_2681_, v___x_2683_);
if (v___x_2685_ == 0)
{
v___y_2572_ = v___y_2645_;
v___y_2573_ = v___y_2646_;
v___y_2574_ = v___y_2647_;
v___y_2575_ = v___y_2647_;
goto v___jp_2571_;
}
else
{
uint64_t v___x_2686_; uint8_t v___x_2687_; 
v___x_2686_ = 9223372036854775808ULL;
v___x_2687_ = lean_uint64_dec_lt(v___x_2686_, v___y_2644_);
if (v___x_2687_ == 0)
{
v___y_2572_ = v___y_2645_;
v___y_2573_ = v___y_2646_;
v___y_2574_ = v___y_2647_;
v___y_2575_ = v___y_2647_;
goto v___jp_2571_;
}
else
{
uint64_t v___x_2688_; 
v___x_2688_ = 1ULL;
v___y_2572_ = v___y_2645_;
v___y_2573_ = v___y_2646_;
v___y_2574_ = v___y_2647_;
v___y_2575_ = v___x_2688_;
goto v___jp_2571_;
}
}
}
else
{
uint64_t v_quotient_2689_; uint64_t v___x_2690_; uint64_t v___x_2691_; uint64_t v___x_2692_; uint64_t v_remainder_2693_; uint64_t v___x_2694_; uint64_t v_half_2695_; uint8_t v___x_2696_; 
v_quotient_2689_ = lean_uint64_shift_right(v___y_2644_, v___x_2681_);
v___x_2690_ = 1ULL;
v___x_2691_ = lean_uint64_shift_left(v___x_2690_, v___x_2681_);
v___x_2692_ = lean_uint64_sub(v___x_2691_, v___x_2690_);
v_remainder_2693_ = lean_uint64_land(v___y_2644_, v___x_2692_);
v___x_2694_ = lean_uint64_sub(v___x_2681_, v___x_2690_);
v_half_2695_ = lean_uint64_shift_left(v___x_2690_, v___x_2694_);
v___x_2696_ = lean_uint64_dec_lt(v_remainder_2693_, v_half_2695_);
if (v___x_2696_ == 0)
{
uint8_t v___x_2697_; 
v___x_2697_ = lean_uint64_dec_lt(v_half_2695_, v_remainder_2693_);
if (v___x_2697_ == 0)
{
uint64_t v___x_2698_; uint8_t v___x_2699_; 
v___x_2698_ = lean_uint64_land(v_quotient_2689_, v___x_2690_);
v___x_2699_ = lean_uint64_dec_eq(v___x_2698_, v___y_2647_);
if (v___x_2699_ == 0)
{
uint64_t v___x_2700_; 
v___x_2700_ = lean_uint64_add(v_quotient_2689_, v___x_2690_);
v___y_2572_ = v___y_2645_;
v___y_2573_ = v___y_2646_;
v___y_2574_ = v___y_2647_;
v___y_2575_ = v___x_2700_;
goto v___jp_2571_;
}
else
{
v___y_2572_ = v___y_2645_;
v___y_2573_ = v___y_2646_;
v___y_2574_ = v___y_2647_;
v___y_2575_ = v_quotient_2689_;
goto v___jp_2571_;
}
}
else
{
uint64_t v___x_2701_; 
v___x_2701_ = lean_uint64_add(v_quotient_2689_, v___x_2690_);
v___y_2572_ = v___y_2645_;
v___y_2573_ = v___y_2646_;
v___y_2574_ = v___y_2647_;
v___y_2575_ = v___x_2701_;
goto v___jp_2571_;
}
}
else
{
v___y_2572_ = v___y_2645_;
v___y_2573_ = v___y_2646_;
v___y_2574_ = v___y_2647_;
v___y_2575_ = v_quotient_2689_;
goto v___jp_2571_;
}
}
}
else
{
v___y_2572_ = v___y_2645_;
v___y_2573_ = v___y_2646_;
v___y_2574_ = v___y_2647_;
v___y_2575_ = v___y_2644_;
goto v___jp_2571_;
}
}
}
}
v___jp_2702_:
{
uint64_t v___x_2710_; uint64_t v___x_2711_; uint8_t v___x_2712_; 
v___x_2710_ = 1ULL;
v___x_2711_ = lean_uint64_shift_right(v___y_2707_, v___x_2710_);
v___x_2712_ = lean_uint64_dec_eq(v___x_2711_, v___y_2708_);
if (v___x_2712_ == 0)
{
uint64_t v___x_2713_; 
v___x_2713_ = lean_uint64_add(v___y_2709_, v___x_2710_);
v___y_2643_ = v___y_2703_;
v___y_2644_ = v___y_2704_;
v___y_2645_ = v___y_2705_;
v___y_2646_ = v___y_2706_;
v___y_2647_ = v___y_2708_;
v___y_2648_ = v___x_2713_;
goto v___jp_2642_;
}
else
{
v___y_2643_ = v___y_2703_;
v___y_2644_ = v___y_2704_;
v___y_2645_ = v___y_2705_;
v___y_2646_ = v___y_2706_;
v___y_2647_ = v___y_2708_;
v___y_2648_ = v___y_2709_;
goto v___jp_2642_;
}
}
v___jp_2714_:
{
uint64_t v___x_2724_; uint8_t v___x_2725_; 
v___x_2724_ = lean_uint64_shift_right(v___y_2721_, v___y_2720_);
v___x_2725_ = lean_uint64_dec_eq(v___x_2724_, v___y_2722_);
if (v___x_2725_ == 0)
{
uint64_t v___x_2726_; 
v___x_2726_ = lean_uint64_add(v___y_2715_, v___y_2720_);
v___y_2703_ = v___y_2716_;
v___y_2704_ = v___y_2717_;
v___y_2705_ = v___y_2718_;
v___y_2706_ = v___y_2719_;
v___y_2707_ = v___y_2723_;
v___y_2708_ = v___y_2722_;
v___y_2709_ = v___x_2726_;
goto v___jp_2702_;
}
else
{
v___y_2703_ = v___y_2716_;
v___y_2704_ = v___y_2717_;
v___y_2705_ = v___y_2718_;
v___y_2706_ = v___y_2719_;
v___y_2707_ = v___y_2723_;
v___y_2708_ = v___y_2722_;
v___y_2709_ = v___y_2715_;
goto v___jp_2702_;
}
}
v___jp_2727_:
{
uint64_t v___x_2735_; uint64_t v___x_2736_; uint8_t v___x_2737_; 
v___x_2735_ = 2ULL;
v___x_2736_ = lean_uint64_shift_right(v___y_2732_, v___x_2735_);
v___x_2737_ = lean_uint64_dec_eq(v___x_2736_, v___y_2733_);
if (v___x_2737_ == 0)
{
v___y_2715_ = v___y_2734_;
v___y_2716_ = v___y_2728_;
v___y_2717_ = v___y_2729_;
v___y_2718_ = v___y_2730_;
v___y_2719_ = v___y_2731_;
v___y_2720_ = v___x_2735_;
v___y_2721_ = v___y_2732_;
v___y_2722_ = v___y_2733_;
v___y_2723_ = v___x_2736_;
goto v___jp_2714_;
}
else
{
v___y_2715_ = v___y_2734_;
v___y_2716_ = v___y_2728_;
v___y_2717_ = v___y_2729_;
v___y_2718_ = v___y_2730_;
v___y_2719_ = v___y_2731_;
v___y_2720_ = v___x_2735_;
v___y_2721_ = v___y_2732_;
v___y_2722_ = v___y_2733_;
v___y_2723_ = v___y_2732_;
goto v___jp_2714_;
}
}
v___jp_2738_:
{
uint64_t v___x_2748_; uint8_t v___x_2749_; 
v___x_2748_ = lean_uint64_shift_right(v___y_2745_, v___y_2742_);
v___x_2749_ = lean_uint64_dec_eq(v___x_2748_, v___y_2746_);
if (v___x_2749_ == 0)
{
uint64_t v___x_2750_; 
v___x_2750_ = lean_uint64_add(v___y_2741_, v___y_2742_);
v___y_2728_ = v___y_2739_;
v___y_2729_ = v___y_2740_;
v___y_2730_ = v___y_2743_;
v___y_2731_ = v___y_2744_;
v___y_2732_ = v___y_2747_;
v___y_2733_ = v___y_2746_;
v___y_2734_ = v___x_2750_;
goto v___jp_2727_;
}
else
{
v___y_2728_ = v___y_2739_;
v___y_2729_ = v___y_2740_;
v___y_2730_ = v___y_2743_;
v___y_2731_ = v___y_2744_;
v___y_2732_ = v___y_2747_;
v___y_2733_ = v___y_2746_;
v___y_2734_ = v___y_2741_;
goto v___jp_2727_;
}
}
v___jp_2751_:
{
uint64_t v___x_2759_; uint64_t v___x_2760_; uint8_t v___x_2761_; 
v___x_2759_ = 4ULL;
v___x_2760_ = lean_uint64_shift_right(v___y_2756_, v___x_2759_);
v___x_2761_ = lean_uint64_dec_eq(v___x_2760_, v___y_2757_);
if (v___x_2761_ == 0)
{
v___y_2739_ = v___y_2752_;
v___y_2740_ = v___y_2753_;
v___y_2741_ = v___y_2758_;
v___y_2742_ = v___x_2759_;
v___y_2743_ = v___y_2754_;
v___y_2744_ = v___y_2755_;
v___y_2745_ = v___y_2756_;
v___y_2746_ = v___y_2757_;
v___y_2747_ = v___x_2760_;
goto v___jp_2738_;
}
else
{
v___y_2739_ = v___y_2752_;
v___y_2740_ = v___y_2753_;
v___y_2741_ = v___y_2758_;
v___y_2742_ = v___x_2759_;
v___y_2743_ = v___y_2754_;
v___y_2744_ = v___y_2755_;
v___y_2745_ = v___y_2756_;
v___y_2746_ = v___y_2757_;
v___y_2747_ = v___y_2756_;
goto v___jp_2738_;
}
}
v___jp_2762_:
{
uint64_t v___x_2772_; uint8_t v___x_2773_; 
v___x_2772_ = lean_uint64_shift_right(v___y_2766_, v___y_2763_);
v___x_2773_ = lean_uint64_dec_eq(v___x_2772_, v___y_2770_);
if (v___x_2773_ == 0)
{
uint64_t v___x_2774_; 
v___x_2774_ = lean_uint64_add(v___y_2767_, v___y_2763_);
v___y_2752_ = v___y_2764_;
v___y_2753_ = v___y_2765_;
v___y_2754_ = v___y_2768_;
v___y_2755_ = v___y_2769_;
v___y_2756_ = v___y_2771_;
v___y_2757_ = v___y_2770_;
v___y_2758_ = v___x_2774_;
goto v___jp_2751_;
}
else
{
v___y_2752_ = v___y_2764_;
v___y_2753_ = v___y_2765_;
v___y_2754_ = v___y_2768_;
v___y_2755_ = v___y_2769_;
v___y_2756_ = v___y_2771_;
v___y_2757_ = v___y_2770_;
v___y_2758_ = v___y_2767_;
goto v___jp_2751_;
}
}
v___jp_2775_:
{
uint64_t v___x_2783_; uint64_t v___x_2784_; uint8_t v___x_2785_; 
v___x_2783_ = 8ULL;
v___x_2784_ = lean_uint64_shift_right(v___y_2778_, v___x_2783_);
v___x_2785_ = lean_uint64_dec_eq(v___x_2784_, v___y_2781_);
if (v___x_2785_ == 0)
{
v___y_2763_ = v___x_2783_;
v___y_2764_ = v___y_2776_;
v___y_2765_ = v___y_2777_;
v___y_2766_ = v___y_2778_;
v___y_2767_ = v___y_2782_;
v___y_2768_ = v___y_2779_;
v___y_2769_ = v___y_2780_;
v___y_2770_ = v___y_2781_;
v___y_2771_ = v___x_2784_;
goto v___jp_2762_;
}
else
{
v___y_2763_ = v___x_2783_;
v___y_2764_ = v___y_2776_;
v___y_2765_ = v___y_2777_;
v___y_2766_ = v___y_2778_;
v___y_2767_ = v___y_2782_;
v___y_2768_ = v___y_2779_;
v___y_2769_ = v___y_2780_;
v___y_2770_ = v___y_2781_;
v___y_2771_ = v___y_2778_;
goto v___jp_2762_;
}
}
v___jp_2786_:
{
uint64_t v___x_2796_; uint8_t v___x_2797_; 
v___x_2796_ = lean_uint64_shift_right(v___y_2787_, v___y_2792_);
v___x_2797_ = lean_uint64_dec_eq(v___x_2796_, v___y_2794_);
if (v___x_2797_ == 0)
{
uint64_t v___x_2798_; 
v___x_2798_ = lean_uint64_add(v___y_2793_, v___y_2792_);
v___y_2776_ = v___y_2788_;
v___y_2777_ = v___y_2789_;
v___y_2778_ = v___y_2795_;
v___y_2779_ = v___y_2790_;
v___y_2780_ = v___y_2791_;
v___y_2781_ = v___y_2794_;
v___y_2782_ = v___x_2798_;
goto v___jp_2775_;
}
else
{
v___y_2776_ = v___y_2788_;
v___y_2777_ = v___y_2789_;
v___y_2778_ = v___y_2795_;
v___y_2779_ = v___y_2790_;
v___y_2780_ = v___y_2791_;
v___y_2781_ = v___y_2794_;
v___y_2782_ = v___y_2793_;
goto v___jp_2775_;
}
}
v___jp_2799_:
{
uint64_t v___x_2807_; uint64_t v___x_2808_; uint8_t v___x_2809_; 
v___x_2807_ = 16ULL;
v___x_2808_ = lean_uint64_shift_right(v___y_2800_, v___x_2807_);
v___x_2809_ = lean_uint64_dec_eq(v___x_2808_, v___y_2805_);
if (v___x_2809_ == 0)
{
v___y_2787_ = v___y_2800_;
v___y_2788_ = v___y_2801_;
v___y_2789_ = v___y_2802_;
v___y_2790_ = v___y_2803_;
v___y_2791_ = v___y_2804_;
v___y_2792_ = v___x_2807_;
v___y_2793_ = v___y_2806_;
v___y_2794_ = v___y_2805_;
v___y_2795_ = v___x_2808_;
goto v___jp_2786_;
}
else
{
v___y_2787_ = v___y_2800_;
v___y_2788_ = v___y_2801_;
v___y_2789_ = v___y_2802_;
v___y_2790_ = v___y_2803_;
v___y_2791_ = v___y_2804_;
v___y_2792_ = v___x_2807_;
v___y_2793_ = v___y_2806_;
v___y_2794_ = v___y_2805_;
v___y_2795_ = v___y_2800_;
goto v___jp_2786_;
}
}
v___jp_2810_:
{
uint64_t v___x_2818_; uint8_t v___x_2819_; 
v___x_2818_ = lean_uint64_shift_right(v___y_2812_, v___y_2813_);
v___x_2819_ = lean_uint64_dec_eq(v___x_2818_, v___y_2816_);
if (v___x_2819_ == 0)
{
v___y_2800_ = v___y_2817_;
v___y_2801_ = v___y_2811_;
v___y_2802_ = v___y_2812_;
v___y_2803_ = v___y_2814_;
v___y_2804_ = v___y_2815_;
v___y_2805_ = v___y_2816_;
v___y_2806_ = v___y_2813_;
goto v___jp_2799_;
}
else
{
v___y_2800_ = v___y_2817_;
v___y_2801_ = v___y_2811_;
v___y_2802_ = v___y_2812_;
v___y_2803_ = v___y_2814_;
v___y_2804_ = v___y_2815_;
v___y_2805_ = v___y_2816_;
v___y_2806_ = v___y_2816_;
goto v___jp_2799_;
}
}
v___jp_2820_:
{
uint64_t v___x_2827_; uint64_t v___x_2828_; uint8_t v___x_2829_; 
v___x_2827_ = lean_uint64_mul(v___y_2825_, v___y_2821_);
v___x_2828_ = 0ULL;
v___x_2829_ = lean_uint64_dec_eq(v___x_2827_, v___x_2828_);
if (v___x_2829_ == 0)
{
uint64_t v___x_2830_; uint64_t v___x_2831_; uint64_t v___x_2832_; uint8_t v___x_2833_; 
v___x_2830_ = lean_uint64_add(v___y_2822_, v___y_2826_);
v___x_2831_ = 32ULL;
v___x_2832_ = lean_uint64_shift_right(v___x_2827_, v___x_2831_);
v___x_2833_ = lean_uint64_dec_eq(v___x_2832_, v___x_2828_);
if (v___x_2833_ == 0)
{
v___y_2811_ = v___x_2830_;
v___y_2812_ = v___x_2827_;
v___y_2813_ = v___x_2831_;
v___y_2814_ = v___y_2823_;
v___y_2815_ = v___y_2824_;
v___y_2816_ = v___x_2828_;
v___y_2817_ = v___x_2832_;
goto v___jp_2810_;
}
else
{
v___y_2811_ = v___x_2830_;
v___y_2812_ = v___x_2827_;
v___y_2813_ = v___x_2831_;
v___y_2814_ = v___y_2823_;
v___y_2815_ = v___y_2824_;
v___y_2816_ = v___x_2828_;
v___y_2817_ = v___x_2827_;
goto v___jp_2810_;
}
}
else
{
if (v___y_2823_ == 0)
{
uint32_t v___x_2834_; 
v___x_2834_ = 0;
return v___x_2834_;
}
else
{
uint32_t v___x_2835_; 
v___x_2835_ = 2147483648;
return v___x_2835_;
}
}
}
v___jp_2839_:
{
uint64_t v___x_2845_; uint64_t v___x_2846_; uint8_t v___x_2847_; 
v___x_2845_ = lean_uint32_to_uint64(v_yExponent_2838_);
v___x_2846_ = 0ULL;
v___x_2847_ = lean_uint64_dec_eq(v___x_2845_, v___x_2846_);
if (v___x_2847_ == 0)
{
uint64_t v___x_2848_; uint64_t v___x_2849_; 
v___x_2848_ = 1ULL;
v___x_2849_ = lean_uint64_sub(v___x_2845_, v___x_2848_);
v___y_2821_ = v___y_2840_;
v___y_2822_ = v___y_2844_;
v___y_2823_ = v___y_2841_;
v___y_2824_ = v___y_2842_;
v___y_2825_ = v___y_2843_;
v___y_2826_ = v___x_2849_;
goto v___jp_2820_;
}
else
{
v___y_2821_ = v___y_2840_;
v___y_2822_ = v___y_2844_;
v___y_2823_ = v___y_2841_;
v___y_2824_ = v___y_2842_;
v___y_2825_ = v___y_2843_;
v___y_2826_ = v___x_2846_;
goto v___jp_2820_;
}
}
v___jp_2850_:
{
uint64_t v___x_2855_; uint64_t v___x_2856_; uint8_t v___x_2857_; 
v___x_2855_ = lean_uint32_to_uint64(v_xExponent_2836_);
v___x_2856_ = 0ULL;
v___x_2857_ = lean_uint64_dec_eq(v___x_2855_, v___x_2856_);
if (v___x_2857_ == 0)
{
uint64_t v___x_2858_; uint64_t v___x_2859_; 
v___x_2858_ = 1ULL;
v___x_2859_ = lean_uint64_sub(v___x_2855_, v___x_2858_);
v___y_2840_ = v___y_2854_;
v___y_2841_ = v___y_2851_;
v___y_2842_ = v___y_2852_;
v___y_2843_ = v___y_2853_;
v___y_2844_ = v___x_2859_;
goto v___jp_2839_;
}
else
{
v___y_2840_ = v___y_2854_;
v___y_2841_ = v___y_2851_;
v___y_2842_ = v___y_2852_;
v___y_2843_ = v___y_2853_;
v___y_2844_ = v___x_2856_;
goto v___jp_2839_;
}
}
v___jp_2860_:
{
uint32_t v___x_2865_; uint8_t v___x_2866_; 
v___x_2865_ = 0;
v___x_2866_ = lean_uint32_dec_eq(v_yExponent_2838_, v___x_2865_);
if (v___x_2866_ == 0)
{
uint64_t v___x_2867_; uint64_t v___x_2868_; uint64_t v___x_2869_; 
v___x_2867_ = lean_uint32_to_uint64(v___y_2861_);
v___x_2868_ = 8388608ULL;
v___x_2869_ = lean_uint64_lor(v___x_2867_, v___x_2868_);
v___y_2851_ = v___y_2862_;
v___y_2852_ = v___y_2863_;
v___y_2853_ = v___y_2864_;
v___y_2854_ = v___x_2869_;
goto v___jp_2850_;
}
else
{
uint64_t v___x_2870_; 
v___x_2870_ = lean_uint32_to_uint64(v___y_2861_);
v___y_2851_ = v___y_2862_;
v___y_2852_ = v___y_2863_;
v___y_2853_ = v___y_2864_;
v___y_2854_ = v___x_2870_;
goto v___jp_2850_;
}
}
v___jp_2871_:
{
uint32_t v___x_2873_; uint32_t v_xFraction_2874_; uint32_t v_yFraction_2875_; uint32_t v___x_2876_; uint8_t v___x_2877_; 
v___x_2873_ = 8388607;
v_xFraction_2874_ = lean_uint32_land(v_xBits_2559_, v___x_2873_);
v_yFraction_2875_ = lean_uint32_land(v_yBits_2560_, v___x_2873_);
v___x_2876_ = 0;
v___x_2877_ = lean_uint32_dec_eq(v_xExponent_2836_, v___x_2876_);
if (v___x_2877_ == 0)
{
uint64_t v___x_2878_; uint64_t v___x_2879_; uint64_t v___x_2880_; 
v___x_2878_ = lean_uint32_to_uint64(v_xFraction_2874_);
v___x_2879_ = 8388608ULL;
v___x_2880_ = lean_uint64_lor(v___x_2878_, v___x_2879_);
v___y_2861_ = v_yFraction_2875_;
v___y_2862_ = v___y_2872_;
v___y_2863_ = v___x_2873_;
v___y_2864_ = v___x_2880_;
goto v___jp_2860_;
}
else
{
uint64_t v___x_2881_; 
v___x_2881_ = lean_uint32_to_uint64(v_xFraction_2874_);
v___y_2861_ = v_yFraction_2875_;
v___y_2862_ = v___y_2872_;
v___y_2863_ = v___x_2873_;
v___y_2864_ = v___x_2881_;
goto v___jp_2860_;
}
}
v___jp_2882_:
{
uint8_t v___x_2883_; 
v___x_2883_ = 1;
v___y_2872_ = v___x_2883_;
goto v___jp_2871_;
}
v___jp_2884_:
{
uint8_t v___x_2885_; 
v___x_2885_ = 0;
v___y_2872_ = v___x_2885_;
goto v___jp_2871_;
}
v___jp_2886_:
{
if (v___y_2887_ == 0)
{
if (v___y_2888_ == 0)
{
goto v___jp_2884_;
}
else
{
goto v___jp_2882_;
}
}
else
{
if (v___y_2888_ == 0)
{
goto v___jp_2882_;
}
else
{
goto v___jp_2884_;
}
}
}
v___jp_2889_:
{
uint32_t v___x_2891_; uint32_t v___x_2892_; uint32_t v___x_2893_; uint8_t v___x_2894_; 
v___x_2891_ = 2147483648;
v___x_2892_ = lean_uint32_land(v_yBits_2560_, v___x_2891_);
v___x_2893_ = 0;
v___x_2894_ = lean_uint32_dec_eq(v___x_2892_, v___x_2893_);
if (v___x_2894_ == 0)
{
uint8_t v___x_2895_; 
v___x_2895_ = 1;
v___y_2887_ = v___y_2890_;
v___y_2888_ = v___x_2895_;
goto v___jp_2886_;
}
else
{
uint8_t v___x_2896_; 
v___x_2896_ = 0;
v___y_2887_ = v___y_2890_;
v___y_2888_ = v___x_2896_;
goto v___jp_2886_;
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_FastMul_core___boxed(lean_object* v_xBits_2903_, lean_object* v_yBits_2904_){
_start:
{
uint32_t v_xBits_boxed_2905_; uint32_t v_yBits_boxed_2906_; uint32_t v_res_2907_; lean_object* v_r_2908_; 
v_xBits_boxed_2905_ = lean_unbox_uint32(v_xBits_2903_);
lean_dec(v_xBits_2903_);
v_yBits_boxed_2906_ = lean_unbox_uint32(v_yBits_2904_);
lean_dec(v_yBits_2904_);
v_res_2907_ = lp_competition_Submission_FastMul_core(v_xBits_boxed_2905_, v_yBits_boxed_2906_);
v_r_2908_ = lean_box_uint32(v_res_2907_);
return v_r_2908_;
}
}
LEAN_EXPORT uint8_t lp_competition_Submission_FastMul_sm1(uint32_t v_a_2909_){
_start:
{
uint32_t v___x_2910_; uint32_t v___x_2911_; uint32_t v___x_2912_; uint8_t v___x_2913_; 
v___x_2910_ = 4278190080;
v___x_2911_ = 1;
v___x_2912_ = lean_uint32_shift_left(v_a_2909_, v___x_2911_);
v___x_2913_ = lean_uint32_dec_le(v___x_2910_, v___x_2912_);
return v___x_2913_;
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_FastMul_sm1___boxed(lean_object* v_a_2914_){
_start:
{
uint32_t v_a_boxed_2915_; uint8_t v_res_2916_; lean_object* v_r_2917_; 
v_a_boxed_2915_ = lean_unbox_uint32(v_a_2914_);
lean_dec(v_a_2914_);
v_res_2916_ = lp_competition_Submission_FastMul_sm1(v_a_boxed_2915_);
v_r_2917_ = lean_box(v_res_2916_);
return v_r_2917_;
}
}
LEAN_EXPORT uint8_t lp_competition_Submission_FastMul_special(uint32_t v_a_2918_, uint32_t v_b_2919_){
_start:
{
uint32_t v___x_2920_; uint32_t v___x_2921_; uint32_t v___x_2922_; uint8_t v___x_2923_; 
v___x_2920_ = 4278190080;
v___x_2921_ = 1;
v___x_2922_ = lean_uint32_shift_left(v_a_2918_, v___x_2921_);
v___x_2923_ = lean_uint32_dec_le(v___x_2920_, v___x_2922_);
if (v___x_2923_ == 0)
{
uint32_t v___x_2924_; uint8_t v___x_2925_; 
v___x_2924_ = lean_uint32_shift_left(v_b_2919_, v___x_2921_);
v___x_2925_ = lean_uint32_dec_le(v___x_2920_, v___x_2924_);
return v___x_2925_;
}
else
{
return v___x_2923_;
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_FastMul_special___boxed(lean_object* v_a_2926_, lean_object* v_b_2927_){
_start:
{
uint32_t v_a_boxed_2928_; uint32_t v_b_boxed_2929_; uint8_t v_res_2930_; lean_object* v_r_2931_; 
v_a_boxed_2928_ = lean_unbox_uint32(v_a_2926_);
lean_dec(v_a_2926_);
v_b_boxed_2929_ = lean_unbox_uint32(v_b_2927_);
lean_dec(v_b_2927_);
v_res_2930_ = lp_competition_Submission_FastMul_special(v_a_boxed_2928_, v_b_boxed_2929_);
v_r_2931_ = lean_box(v_res_2930_);
return v_r_2931_;
}
}
LEAN_EXPORT uint32_t lp_competition_Submission_FastMul_ofBits(uint32_t v_w_2932_){
_start:
{
return v_w_2932_;
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_FastMul_ofBits___boxed(lean_object* v_w_2933_){
_start:
{
uint32_t v_w_boxed_2934_; uint32_t v_res_2935_; lean_object* v_r_2936_; 
v_w_boxed_2934_ = lean_unbox_uint32(v_w_2933_);
lean_dec(v_w_2933_);
v_res_2935_ = lp_competition_Submission_FastMul_ofBits(v_w_boxed_2934_);
v_r_2936_ = lean_box_uint32(v_res_2935_);
return v_r_2936_;
}
}
LEAN_EXPORT uint32_t lp_competition_Submission_FastMul_mul(uint32_t v_x_2937_, uint32_t v_y_2938_){
_start:
{
uint32_t v___y_2940_; uint32_t v___y_2944_; uint32_t v___y_2945_; uint32_t v___y_2946_; uint32_t v___y_2950_; uint64_t v___y_2951_; uint8_t v___y_2952_; uint64_t v___y_2953_; uint32_t v___y_2965_; uint32_t v___y_2966_; uint32_t v___y_2967_; uint32_t v___y_2968_; uint32_t v___y_2969_; uint32_t v___y_2970_; uint32_t v___y_2977_; uint32_t v___y_2978_; uint32_t v___y_2979_; uint8_t v___y_2980_; uint32_t v___y_2981_; uint32_t v___y_2982_; uint32_t v___y_2986_; uint32_t v___y_2987_; uint64_t v___y_2988_; uint64_t v___y_2989_; uint32_t v___y_2990_; uint8_t v___y_2991_; uint64_t v___y_2992_; uint32_t v___y_3002_; uint64_t v___y_3003_; uint8_t v___y_3004_; uint32_t v___y_3005_; uint64_t v___y_3006_; uint8_t v___y_3007_; uint32_t v___y_3008_; uint64_t v___y_3009_; uint64_t v___y_3016_; uint32_t v___y_3017_; uint32_t v___y_3018_; uint64_t v___y_3019_; uint32_t v___y_3020_; uint8_t v___y_3021_; uint64_t v___y_3022_; uint64_t v___y_3028_; uint32_t v___y_3029_; uint64_t v___y_3030_; uint32_t v___y_3031_; uint64_t v___y_3032_; uint8_t v___y_3033_; uint32_t v___y_3034_; uint64_t v___y_3035_; uint32_t v___y_3090_; uint64_t v___y_3091_; uint64_t v___y_3092_; uint32_t v___y_3093_; uint64_t v___y_3094_; uint32_t v___y_3095_; uint8_t v___y_3096_; uint64_t v___y_3097_; uint64_t v___y_3098_; uint64_t v___y_3104_; uint64_t v___y_3105_; uint64_t v___y_3106_; uint32_t v___y_3107_; uint64_t v___y_3108_; uint32_t v___y_3109_; uint64_t v___y_3110_; uint64_t v___y_3111_; uint8_t v___y_3112_; uint32_t v___y_3113_; uint64_t v___y_3114_; uint64_t v___y_3119_; uint32_t v___y_3120_; uint64_t v___y_3121_; uint64_t v___y_3122_; uint32_t v___y_3123_; uint64_t v___y_3124_; uint32_t v___y_3125_; uint8_t v___y_3126_; uint64_t v___y_3127_; uint64_t v___y_3132_; uint64_t v___y_3133_; uint64_t v___y_3134_; uint32_t v___y_3135_; uint64_t v___y_3136_; uint32_t v___y_3137_; uint64_t v___y_3138_; uint8_t v___y_3139_; uint32_t v___y_3140_; uint64_t v___y_3141_; uint64_t v___y_3142_; uint64_t v___y_3147_; uint32_t v___y_3148_; uint64_t v___y_3149_; uint64_t v___y_3150_; uint32_t v___y_3151_; uint64_t v___y_3152_; uint32_t v___y_3153_; uint8_t v___y_3154_; uint64_t v___y_3155_; uint64_t v___y_3160_; uint64_t v___y_3161_; uint64_t v___y_3162_; uint32_t v___y_3163_; uint64_t v___y_3164_; uint32_t v___y_3165_; uint64_t v___y_3166_; uint64_t v___y_3167_; uint8_t v___y_3168_; uint32_t v___y_3169_; uint64_t v___y_3170_; uint32_t v___y_3175_; uint64_t v___y_3176_; uint64_t v___y_3177_; uint32_t v___y_3178_; uint64_t v___y_3179_; uint64_t v___y_3180_; uint32_t v___y_3181_; uint8_t v___y_3182_; uint64_t v___y_3183_; uint64_t v___y_3188_; uint64_t v___y_3189_; uint64_t v___y_3190_; uint32_t v___y_3191_; uint64_t v___y_3192_; uint32_t v___y_3193_; uint64_t v___y_3194_; uint64_t v___y_3195_; uint8_t v___y_3196_; uint32_t v___y_3197_; uint64_t v___y_3198_; uint64_t v___y_3203_; uint32_t v___y_3204_; uint64_t v___y_3205_; uint64_t v___y_3206_; uint32_t v___y_3207_; uint64_t v___y_3208_; uint32_t v___y_3209_; uint8_t v___y_3210_; uint64_t v___y_3211_; uint64_t v___y_3216_; uint32_t v___y_3217_; uint64_t v___y_3218_; uint32_t v___y_3219_; uint64_t v___y_3220_; uint64_t v___y_3221_; uint8_t v___y_3222_; uint32_t v___y_3223_; uint64_t v___y_3224_; uint64_t v___y_3228_; uint32_t v___y_3229_; uint64_t v___y_3230_; uint32_t v___y_3231_; uint64_t v___y_3232_; uint32_t v___y_3233_; uint8_t v___y_3234_; uint64_t v___y_3235_; uint32_t v___y_3246_; uint64_t v___y_3247_; uint32_t v___y_3248_; uint64_t v___y_3249_; uint32_t v___y_3250_; uint8_t v___y_3251_; uint32_t v___y_3252_; uint64_t v___y_3253_; uint32_t v___y_3260_; uint32_t v___y_3261_; uint32_t v___y_3262_; uint64_t v___y_3263_; uint32_t v___y_3264_; uint8_t v___y_3265_; uint32_t v___y_3266_; uint64_t v___y_3267_; uint32_t v___y_3274_; uint32_t v___y_3275_; uint32_t v___y_3276_; uint32_t v___y_3277_; uint8_t v___y_3278_; uint32_t v___y_3279_; uint32_t v___y_3280_; uint64_t v___y_3281_; uint32_t v___y_3289_; uint32_t v___y_3290_; uint32_t v___y_3291_; uint32_t v___y_3292_; uint8_t v___y_3293_; uint32_t v___y_3304_; uint32_t v___y_3305_; uint32_t v___y_3306_; uint32_t v___y_3307_; uint32_t v___y_3310_; uint8_t v___y_3311_; uint8_t v___y_3312_; uint32_t v___y_3313_; uint32_t v___y_3314_; uint32_t v___y_3315_; uint8_t v___y_3316_; uint32_t v___y_3318_; uint8_t v___y_3319_; uint32_t v___y_3320_; uint32_t v___y_3321_; uint32_t v___y_3322_; uint8_t v___y_3323_; uint8_t v___y_3330_; uint32_t v___x_3346_; uint32_t v___x_3347_; uint32_t v___x_3348_; uint8_t v___x_3349_; 
v___x_3346_ = 4278190080;
v___x_3347_ = 1;
v___x_3348_ = lean_uint32_shift_left(v_x_2937_, v___x_3347_);
v___x_3349_ = lean_uint32_dec_le(v___x_3346_, v___x_3348_);
if (v___x_3349_ == 0)
{
uint32_t v___x_3350_; uint8_t v___x_3351_; 
v___x_3350_ = lean_uint32_shift_left(v_y_2938_, v___x_3347_);
v___x_3351_ = lean_uint32_dec_le(v___x_3346_, v___x_3350_);
v___y_3330_ = v___x_3351_;
goto v___jp_3329_;
}
else
{
v___y_3330_ = v___x_3349_;
goto v___jp_3329_;
}
v___jp_2939_:
{
uint32_t v___x_2941_; uint32_t v___x_2942_; 
v___x_2941_ = 8388608;
v___x_2942_ = lean_uint32_lor(v___y_2940_, v___x_2941_);
return v___x_2942_;
}
v___jp_2943_:
{
uint32_t v___x_2947_; uint32_t v___x_2948_; 
v___x_2947_ = lean_uint32_land(v___y_2945_, v___y_2944_);
v___x_2948_ = lean_uint32_lor(v___y_2946_, v___x_2947_);
return v___x_2948_;
}
v___jp_2949_:
{
uint8_t v___x_2954_; 
v___x_2954_ = lean_uint64_dec_eq(v___y_2953_, v___y_2951_);
if (v___x_2954_ == 0)
{
uint64_t v___x_2955_; uint8_t v___x_2956_; 
v___x_2955_ = 8388608ULL;
v___x_2956_ = lean_uint64_dec_eq(v___y_2953_, v___x_2955_);
if (v___x_2956_ == 0)
{
uint32_t v___x_2957_; 
v___x_2957_ = lean_uint64_to_uint32(v___y_2953_);
if (v___y_2952_ == 0)
{
uint32_t v___x_2958_; 
v___x_2958_ = 0;
v___y_2944_ = v___y_2950_;
v___y_2945_ = v___x_2957_;
v___y_2946_ = v___x_2958_;
goto v___jp_2943_;
}
else
{
uint32_t v___x_2959_; 
v___x_2959_ = 2147483648;
v___y_2944_ = v___y_2950_;
v___y_2945_ = v___x_2957_;
v___y_2946_ = v___x_2959_;
goto v___jp_2943_;
}
}
else
{
if (v___y_2952_ == 0)
{
uint32_t v___x_2960_; 
v___x_2960_ = 0;
v___y_2940_ = v___x_2960_;
goto v___jp_2939_;
}
else
{
uint32_t v___x_2961_; 
v___x_2961_ = 2147483648;
v___y_2940_ = v___x_2961_;
goto v___jp_2939_;
}
}
}
else
{
if (v___y_2952_ == 0)
{
uint32_t v___x_2962_; 
v___x_2962_ = 0;
return v___x_2962_;
}
else
{
uint32_t v___x_2963_; 
v___x_2963_ = 2147483648;
return v___x_2963_;
}
}
}
v___jp_2964_:
{
uint32_t v___x_2971_; uint32_t v___x_2972_; uint32_t v___x_2973_; uint32_t v___x_2974_; uint32_t v___x_2975_; 
v___x_2971_ = lean_uint32_land(v___y_2966_, v___y_2969_);
v___x_2972_ = lean_uint32_shift_left(v___x_2971_, v___y_2968_);
v___x_2973_ = lean_uint32_lor(v___y_2970_, v___x_2972_);
v___x_2974_ = lean_uint32_land(v___y_2965_, v___y_2967_);
v___x_2975_ = lean_uint32_lor(v___x_2973_, v___x_2974_);
return v___x_2975_;
}
v___jp_2976_:
{
if (v___y_2980_ == 0)
{
uint32_t v___x_2983_; 
v___x_2983_ = 0;
v___y_2965_ = v___y_2982_;
v___y_2966_ = v___y_2977_;
v___y_2967_ = v___y_2978_;
v___y_2968_ = v___y_2979_;
v___y_2969_ = v___y_2981_;
v___y_2970_ = v___x_2983_;
goto v___jp_2964_;
}
else
{
uint32_t v___x_2984_; 
v___x_2984_ = 2147483648;
v___y_2965_ = v___y_2982_;
v___y_2966_ = v___y_2977_;
v___y_2967_ = v___y_2978_;
v___y_2968_ = v___y_2979_;
v___y_2969_ = v___y_2981_;
v___y_2970_ = v___x_2984_;
goto v___jp_2964_;
}
}
v___jp_2985_:
{
uint64_t v___x_2993_; uint64_t v_encodedExponent_2994_; uint32_t v___x_2995_; uint64_t v___x_2996_; uint8_t v___x_2997_; 
v___x_2993_ = 171ULL;
v_encodedExponent_2994_ = lean_uint64_sub(v___y_2988_, v___x_2993_);
v___x_2995_ = lean_uint64_to_uint32(v_encodedExponent_2994_);
v___x_2996_ = 8388608ULL;
v___x_2997_ = lean_uint64_dec_lt(v___y_2992_, v___x_2996_);
if (v___x_2997_ == 0)
{
uint64_t v___x_2998_; uint32_t v___x_2999_; 
v___x_2998_ = lean_uint64_sub(v___y_2992_, v___x_2996_);
v___x_2999_ = lean_uint64_to_uint32(v___x_2998_);
v___y_2977_ = v___x_2995_;
v___y_2978_ = v___y_2986_;
v___y_2979_ = v___y_2987_;
v___y_2980_ = v___y_2991_;
v___y_2981_ = v___y_2990_;
v___y_2982_ = v___x_2999_;
goto v___jp_2976_;
}
else
{
uint32_t v___x_3000_; 
v___x_3000_ = lean_uint64_to_uint32(v___y_2989_);
v___y_2977_ = v___x_2995_;
v___y_2978_ = v___y_2986_;
v___y_2979_ = v___y_2987_;
v___y_2980_ = v___y_2991_;
v___y_2981_ = v___y_2990_;
v___y_2982_ = v___x_3000_;
goto v___jp_2976_;
}
}
v___jp_3001_:
{
uint64_t v___x_3010_; uint8_t v___x_3011_; 
v___x_3010_ = 425ULL;
v___x_3011_ = lean_uint64_dec_lt(v___x_3010_, v___y_3009_);
if (v___x_3011_ == 0)
{
if (v___y_3004_ == 0)
{
v___y_2986_ = v___y_3002_;
v___y_2987_ = v___y_3005_;
v___y_2988_ = v___y_3009_;
v___y_2989_ = v___y_3006_;
v___y_2990_ = v___y_3008_;
v___y_2991_ = v___y_3007_;
v___y_2992_ = v___y_3003_;
goto v___jp_2985_;
}
else
{
uint64_t v___x_3012_; 
v___x_3012_ = 8388608ULL;
v___y_2986_ = v___y_3002_;
v___y_2987_ = v___y_3005_;
v___y_2988_ = v___y_3009_;
v___y_2989_ = v___y_3006_;
v___y_2990_ = v___y_3008_;
v___y_2991_ = v___y_3007_;
v___y_2992_ = v___x_3012_;
goto v___jp_2985_;
}
}
else
{
if (v___y_3007_ == 0)
{
uint32_t v___x_3013_; 
v___x_3013_ = 2139095040;
return v___x_3013_;
}
else
{
uint32_t v___x_3014_; 
v___x_3014_ = 4286578688;
return v___x_3014_;
}
}
}
v___jp_3015_:
{
uint64_t v___x_3023_; uint8_t v_carry_3024_; 
v___x_3023_ = 16777216ULL;
v_carry_3024_ = lean_uint64_dec_eq(v___y_3022_, v___x_3023_);
if (v_carry_3024_ == 0)
{
v___y_3002_ = v___y_3017_;
v___y_3003_ = v___y_3022_;
v___y_3004_ = v_carry_3024_;
v___y_3005_ = v___y_3018_;
v___y_3006_ = v___y_3019_;
v___y_3007_ = v___y_3021_;
v___y_3008_ = v___y_3020_;
v___y_3009_ = v___y_3016_;
goto v___jp_3001_;
}
else
{
uint64_t v___x_3025_; uint64_t v___x_3026_; 
v___x_3025_ = 1ULL;
v___x_3026_ = lean_uint64_add(v___y_3016_, v___x_3025_);
v___y_3002_ = v___y_3017_;
v___y_3003_ = v___y_3022_;
v___y_3004_ = v_carry_3024_;
v___y_3005_ = v___y_3018_;
v___y_3006_ = v___y_3019_;
v___y_3007_ = v___y_3021_;
v___y_3008_ = v___y_3020_;
v___y_3009_ = v___x_3026_;
goto v___jp_3001_;
}
}
v___jp_3027_:
{
uint64_t v_position_3036_; uint64_t v___x_3037_; uint8_t v___x_3038_; 
v_position_3036_ = lean_uint64_add(v___y_3035_, v___y_3030_);
v___x_3037_ = 172ULL;
v___x_3038_ = lean_uint64_dec_lt(v_position_3036_, v___x_3037_);
if (v___x_3038_ == 0)
{
uint64_t v___x_3039_; uint8_t v___x_3040_; 
v___x_3039_ = 23ULL;
v___x_3040_ = lean_uint64_dec_lt(v___y_3035_, v___x_3039_);
if (v___x_3040_ == 0)
{
uint64_t v___x_3041_; uint8_t v___x_3042_; 
v___x_3041_ = lean_uint64_sub(v___y_3035_, v___x_3039_);
v___x_3042_ = lean_uint64_dec_eq(v___x_3041_, v___y_3032_);
if (v___x_3042_ == 0)
{
uint64_t v___x_3043_; uint8_t v___x_3044_; 
v___x_3043_ = 64ULL;
v___x_3044_ = lean_uint64_dec_lt(v___x_3041_, v___x_3043_);
if (v___x_3044_ == 0)
{
uint8_t v___x_3045_; 
v___x_3045_ = lean_uint64_dec_eq(v___x_3041_, v___x_3043_);
if (v___x_3045_ == 0)
{
v___y_3016_ = v_position_3036_;
v___y_3017_ = v___y_3029_;
v___y_3018_ = v___y_3031_;
v___y_3019_ = v___y_3032_;
v___y_3020_ = v___y_3034_;
v___y_3021_ = v___y_3033_;
v___y_3022_ = v___y_3032_;
goto v___jp_3015_;
}
else
{
uint64_t v___x_3046_; uint8_t v___x_3047_; 
v___x_3046_ = 9223372036854775808ULL;
v___x_3047_ = lean_uint64_dec_lt(v___x_3046_, v___y_3028_);
if (v___x_3047_ == 0)
{
v___y_3016_ = v_position_3036_;
v___y_3017_ = v___y_3029_;
v___y_3018_ = v___y_3031_;
v___y_3019_ = v___y_3032_;
v___y_3020_ = v___y_3034_;
v___y_3021_ = v___y_3033_;
v___y_3022_ = v___y_3032_;
goto v___jp_3015_;
}
else
{
uint64_t v___x_3048_; 
v___x_3048_ = 1ULL;
v___y_3016_ = v_position_3036_;
v___y_3017_ = v___y_3029_;
v___y_3018_ = v___y_3031_;
v___y_3019_ = v___y_3032_;
v___y_3020_ = v___y_3034_;
v___y_3021_ = v___y_3033_;
v___y_3022_ = v___x_3048_;
goto v___jp_3015_;
}
}
}
else
{
uint64_t v_quotient_3049_; uint64_t v___x_3050_; uint64_t v___x_3051_; uint64_t v___x_3052_; uint64_t v_remainder_3053_; uint64_t v___x_3054_; uint64_t v_half_3055_; uint8_t v___x_3056_; 
v_quotient_3049_ = lean_uint64_shift_right(v___y_3028_, v___x_3041_);
v___x_3050_ = 1ULL;
v___x_3051_ = lean_uint64_shift_left(v___x_3050_, v___x_3041_);
v___x_3052_ = lean_uint64_sub(v___x_3051_, v___x_3050_);
v_remainder_3053_ = lean_uint64_land(v___y_3028_, v___x_3052_);
v___x_3054_ = lean_uint64_sub(v___x_3041_, v___x_3050_);
v_half_3055_ = lean_uint64_shift_left(v___x_3050_, v___x_3054_);
v___x_3056_ = lean_uint64_dec_lt(v_remainder_3053_, v_half_3055_);
if (v___x_3056_ == 0)
{
uint8_t v___x_3057_; 
v___x_3057_ = lean_uint64_dec_lt(v_half_3055_, v_remainder_3053_);
if (v___x_3057_ == 0)
{
uint64_t v___x_3058_; uint8_t v___x_3059_; 
v___x_3058_ = lean_uint64_land(v_quotient_3049_, v___x_3050_);
v___x_3059_ = lean_uint64_dec_eq(v___x_3058_, v___y_3032_);
if (v___x_3059_ == 0)
{
uint64_t v___x_3060_; 
v___x_3060_ = lean_uint64_add(v_quotient_3049_, v___x_3050_);
v___y_3016_ = v_position_3036_;
v___y_3017_ = v___y_3029_;
v___y_3018_ = v___y_3031_;
v___y_3019_ = v___y_3032_;
v___y_3020_ = v___y_3034_;
v___y_3021_ = v___y_3033_;
v___y_3022_ = v___x_3060_;
goto v___jp_3015_;
}
else
{
v___y_3016_ = v_position_3036_;
v___y_3017_ = v___y_3029_;
v___y_3018_ = v___y_3031_;
v___y_3019_ = v___y_3032_;
v___y_3020_ = v___y_3034_;
v___y_3021_ = v___y_3033_;
v___y_3022_ = v_quotient_3049_;
goto v___jp_3015_;
}
}
else
{
uint64_t v___x_3061_; 
v___x_3061_ = lean_uint64_add(v_quotient_3049_, v___x_3050_);
v___y_3016_ = v_position_3036_;
v___y_3017_ = v___y_3029_;
v___y_3018_ = v___y_3031_;
v___y_3019_ = v___y_3032_;
v___y_3020_ = v___y_3034_;
v___y_3021_ = v___y_3033_;
v___y_3022_ = v___x_3061_;
goto v___jp_3015_;
}
}
else
{
v___y_3016_ = v_position_3036_;
v___y_3017_ = v___y_3029_;
v___y_3018_ = v___y_3031_;
v___y_3019_ = v___y_3032_;
v___y_3020_ = v___y_3034_;
v___y_3021_ = v___y_3033_;
v___y_3022_ = v_quotient_3049_;
goto v___jp_3015_;
}
}
}
else
{
v___y_3016_ = v_position_3036_;
v___y_3017_ = v___y_3029_;
v___y_3018_ = v___y_3031_;
v___y_3019_ = v___y_3032_;
v___y_3020_ = v___y_3034_;
v___y_3021_ = v___y_3033_;
v___y_3022_ = v___y_3028_;
goto v___jp_3015_;
}
}
else
{
uint64_t v___x_3062_; uint64_t v___x_3063_; 
v___x_3062_ = lean_uint64_sub(v___x_3039_, v___y_3035_);
v___x_3063_ = lean_uint64_shift_left(v___y_3028_, v___x_3062_);
v___y_3016_ = v_position_3036_;
v___y_3017_ = v___y_3029_;
v___y_3018_ = v___y_3031_;
v___y_3019_ = v___y_3032_;
v___y_3020_ = v___y_3034_;
v___y_3021_ = v___y_3033_;
v___y_3022_ = v___x_3063_;
goto v___jp_3015_;
}
}
else
{
uint64_t v___x_3064_; uint8_t v___x_3065_; 
v___x_3064_ = 149ULL;
v___x_3065_ = lean_uint64_dec_lt(v___y_3030_, v___x_3064_);
if (v___x_3065_ == 0)
{
uint64_t v___x_3066_; uint64_t v___x_3067_; 
v___x_3066_ = lean_uint64_sub(v___y_3030_, v___x_3064_);
v___x_3067_ = lean_uint64_shift_left(v___y_3028_, v___x_3066_);
v___y_2950_ = v___y_3029_;
v___y_2951_ = v___y_3032_;
v___y_2952_ = v___y_3033_;
v___y_2953_ = v___x_3067_;
goto v___jp_2949_;
}
else
{
uint64_t v___x_3068_; uint8_t v___x_3069_; 
v___x_3068_ = lean_uint64_sub(v___x_3064_, v___y_3030_);
v___x_3069_ = lean_uint64_dec_eq(v___x_3068_, v___y_3032_);
if (v___x_3069_ == 0)
{
uint64_t v___x_3070_; uint8_t v___x_3071_; 
v___x_3070_ = 64ULL;
v___x_3071_ = lean_uint64_dec_lt(v___x_3068_, v___x_3070_);
if (v___x_3071_ == 0)
{
uint8_t v___x_3072_; 
v___x_3072_ = lean_uint64_dec_eq(v___x_3068_, v___x_3070_);
if (v___x_3072_ == 0)
{
v___y_2950_ = v___y_3029_;
v___y_2951_ = v___y_3032_;
v___y_2952_ = v___y_3033_;
v___y_2953_ = v___y_3032_;
goto v___jp_2949_;
}
else
{
uint64_t v___x_3073_; uint8_t v___x_3074_; 
v___x_3073_ = 9223372036854775808ULL;
v___x_3074_ = lean_uint64_dec_lt(v___x_3073_, v___y_3028_);
if (v___x_3074_ == 0)
{
v___y_2950_ = v___y_3029_;
v___y_2951_ = v___y_3032_;
v___y_2952_ = v___y_3033_;
v___y_2953_ = v___y_3032_;
goto v___jp_2949_;
}
else
{
uint64_t v___x_3075_; 
v___x_3075_ = 1ULL;
v___y_2950_ = v___y_3029_;
v___y_2951_ = v___y_3032_;
v___y_2952_ = v___y_3033_;
v___y_2953_ = v___x_3075_;
goto v___jp_2949_;
}
}
}
else
{
uint64_t v_quotient_3076_; uint64_t v___x_3077_; uint64_t v___x_3078_; uint64_t v___x_3079_; uint64_t v_remainder_3080_; uint64_t v___x_3081_; uint64_t v_half_3082_; uint8_t v___x_3083_; 
v_quotient_3076_ = lean_uint64_shift_right(v___y_3028_, v___x_3068_);
v___x_3077_ = 1ULL;
v___x_3078_ = lean_uint64_shift_left(v___x_3077_, v___x_3068_);
v___x_3079_ = lean_uint64_sub(v___x_3078_, v___x_3077_);
v_remainder_3080_ = lean_uint64_land(v___y_3028_, v___x_3079_);
v___x_3081_ = lean_uint64_sub(v___x_3068_, v___x_3077_);
v_half_3082_ = lean_uint64_shift_left(v___x_3077_, v___x_3081_);
v___x_3083_ = lean_uint64_dec_lt(v_remainder_3080_, v_half_3082_);
if (v___x_3083_ == 0)
{
uint8_t v___x_3084_; 
v___x_3084_ = lean_uint64_dec_lt(v_half_3082_, v_remainder_3080_);
if (v___x_3084_ == 0)
{
uint64_t v___x_3085_; uint8_t v___x_3086_; 
v___x_3085_ = lean_uint64_land(v_quotient_3076_, v___x_3077_);
v___x_3086_ = lean_uint64_dec_eq(v___x_3085_, v___y_3032_);
if (v___x_3086_ == 0)
{
uint64_t v___x_3087_; 
v___x_3087_ = lean_uint64_add(v_quotient_3076_, v___x_3077_);
v___y_2950_ = v___y_3029_;
v___y_2951_ = v___y_3032_;
v___y_2952_ = v___y_3033_;
v___y_2953_ = v___x_3087_;
goto v___jp_2949_;
}
else
{
v___y_2950_ = v___y_3029_;
v___y_2951_ = v___y_3032_;
v___y_2952_ = v___y_3033_;
v___y_2953_ = v_quotient_3076_;
goto v___jp_2949_;
}
}
else
{
uint64_t v___x_3088_; 
v___x_3088_ = lean_uint64_add(v_quotient_3076_, v___x_3077_);
v___y_2950_ = v___y_3029_;
v___y_2951_ = v___y_3032_;
v___y_2952_ = v___y_3033_;
v___y_2953_ = v___x_3088_;
goto v___jp_2949_;
}
}
else
{
v___y_2950_ = v___y_3029_;
v___y_2951_ = v___y_3032_;
v___y_2952_ = v___y_3033_;
v___y_2953_ = v_quotient_3076_;
goto v___jp_2949_;
}
}
}
else
{
v___y_2950_ = v___y_3029_;
v___y_2951_ = v___y_3032_;
v___y_2952_ = v___y_3033_;
v___y_2953_ = v___y_3028_;
goto v___jp_2949_;
}
}
}
}
v___jp_3089_:
{
uint64_t v___x_3099_; uint64_t v___x_3100_; uint8_t v___x_3101_; 
v___x_3099_ = 1ULL;
v___x_3100_ = lean_uint64_shift_right(v___y_3097_, v___x_3099_);
v___x_3101_ = lean_uint64_dec_eq(v___x_3100_, v___y_3094_);
if (v___x_3101_ == 0)
{
uint64_t v___x_3102_; 
v___x_3102_ = lean_uint64_add(v___y_3098_, v___x_3099_);
v___y_3028_ = v___y_3091_;
v___y_3029_ = v___y_3090_;
v___y_3030_ = v___y_3092_;
v___y_3031_ = v___y_3093_;
v___y_3032_ = v___y_3094_;
v___y_3033_ = v___y_3096_;
v___y_3034_ = v___y_3095_;
v___y_3035_ = v___x_3102_;
goto v___jp_3027_;
}
else
{
v___y_3028_ = v___y_3091_;
v___y_3029_ = v___y_3090_;
v___y_3030_ = v___y_3092_;
v___y_3031_ = v___y_3093_;
v___y_3032_ = v___y_3094_;
v___y_3033_ = v___y_3096_;
v___y_3034_ = v___y_3095_;
v___y_3035_ = v___y_3098_;
goto v___jp_3027_;
}
}
v___jp_3103_:
{
uint64_t v___x_3115_; uint8_t v___x_3116_; 
v___x_3115_ = lean_uint64_shift_right(v___y_3104_, v___y_3111_);
v___x_3116_ = lean_uint64_dec_eq(v___x_3115_, v___y_3110_);
if (v___x_3116_ == 0)
{
uint64_t v___x_3117_; 
v___x_3117_ = lean_uint64_add(v___y_3105_, v___y_3111_);
v___y_3090_ = v___y_3107_;
v___y_3091_ = v___y_3106_;
v___y_3092_ = v___y_3108_;
v___y_3093_ = v___y_3109_;
v___y_3094_ = v___y_3110_;
v___y_3095_ = v___y_3113_;
v___y_3096_ = v___y_3112_;
v___y_3097_ = v___y_3114_;
v___y_3098_ = v___x_3117_;
goto v___jp_3089_;
}
else
{
v___y_3090_ = v___y_3107_;
v___y_3091_ = v___y_3106_;
v___y_3092_ = v___y_3108_;
v___y_3093_ = v___y_3109_;
v___y_3094_ = v___y_3110_;
v___y_3095_ = v___y_3113_;
v___y_3096_ = v___y_3112_;
v___y_3097_ = v___y_3114_;
v___y_3098_ = v___y_3105_;
goto v___jp_3089_;
}
}
v___jp_3118_:
{
uint64_t v___x_3128_; uint64_t v___x_3129_; uint8_t v___x_3130_; 
v___x_3128_ = 2ULL;
v___x_3129_ = lean_uint64_shift_right(v___y_3119_, v___x_3128_);
v___x_3130_ = lean_uint64_dec_eq(v___x_3129_, v___y_3124_);
if (v___x_3130_ == 0)
{
v___y_3104_ = v___y_3119_;
v___y_3105_ = v___y_3127_;
v___y_3106_ = v___y_3121_;
v___y_3107_ = v___y_3120_;
v___y_3108_ = v___y_3122_;
v___y_3109_ = v___y_3123_;
v___y_3110_ = v___y_3124_;
v___y_3111_ = v___x_3128_;
v___y_3112_ = v___y_3126_;
v___y_3113_ = v___y_3125_;
v___y_3114_ = v___x_3129_;
goto v___jp_3103_;
}
else
{
v___y_3104_ = v___y_3119_;
v___y_3105_ = v___y_3127_;
v___y_3106_ = v___y_3121_;
v___y_3107_ = v___y_3120_;
v___y_3108_ = v___y_3122_;
v___y_3109_ = v___y_3123_;
v___y_3110_ = v___y_3124_;
v___y_3111_ = v___x_3128_;
v___y_3112_ = v___y_3126_;
v___y_3113_ = v___y_3125_;
v___y_3114_ = v___y_3119_;
goto v___jp_3103_;
}
}
v___jp_3131_:
{
uint64_t v___x_3143_; uint8_t v___x_3144_; 
v___x_3143_ = lean_uint64_shift_right(v___y_3132_, v___y_3133_);
v___x_3144_ = lean_uint64_dec_eq(v___x_3143_, v___y_3138_);
if (v___x_3144_ == 0)
{
uint64_t v___x_3145_; 
v___x_3145_ = lean_uint64_add(v___y_3141_, v___y_3133_);
v___y_3119_ = v___y_3142_;
v___y_3120_ = v___y_3135_;
v___y_3121_ = v___y_3134_;
v___y_3122_ = v___y_3136_;
v___y_3123_ = v___y_3137_;
v___y_3124_ = v___y_3138_;
v___y_3125_ = v___y_3140_;
v___y_3126_ = v___y_3139_;
v___y_3127_ = v___x_3145_;
goto v___jp_3118_;
}
else
{
v___y_3119_ = v___y_3142_;
v___y_3120_ = v___y_3135_;
v___y_3121_ = v___y_3134_;
v___y_3122_ = v___y_3136_;
v___y_3123_ = v___y_3137_;
v___y_3124_ = v___y_3138_;
v___y_3125_ = v___y_3140_;
v___y_3126_ = v___y_3139_;
v___y_3127_ = v___y_3141_;
goto v___jp_3118_;
}
}
v___jp_3146_:
{
uint64_t v___x_3156_; uint64_t v___x_3157_; uint8_t v___x_3158_; 
v___x_3156_ = 4ULL;
v___x_3157_ = lean_uint64_shift_right(v___y_3147_, v___x_3156_);
v___x_3158_ = lean_uint64_dec_eq(v___x_3157_, v___y_3152_);
if (v___x_3158_ == 0)
{
v___y_3132_ = v___y_3147_;
v___y_3133_ = v___x_3156_;
v___y_3134_ = v___y_3149_;
v___y_3135_ = v___y_3148_;
v___y_3136_ = v___y_3150_;
v___y_3137_ = v___y_3151_;
v___y_3138_ = v___y_3152_;
v___y_3139_ = v___y_3154_;
v___y_3140_ = v___y_3153_;
v___y_3141_ = v___y_3155_;
v___y_3142_ = v___x_3157_;
goto v___jp_3131_;
}
else
{
v___y_3132_ = v___y_3147_;
v___y_3133_ = v___x_3156_;
v___y_3134_ = v___y_3149_;
v___y_3135_ = v___y_3148_;
v___y_3136_ = v___y_3150_;
v___y_3137_ = v___y_3151_;
v___y_3138_ = v___y_3152_;
v___y_3139_ = v___y_3154_;
v___y_3140_ = v___y_3153_;
v___y_3141_ = v___y_3155_;
v___y_3142_ = v___y_3147_;
goto v___jp_3131_;
}
}
v___jp_3159_:
{
uint64_t v___x_3171_; uint8_t v___x_3172_; 
v___x_3171_ = lean_uint64_shift_right(v___y_3166_, v___y_3160_);
v___x_3172_ = lean_uint64_dec_eq(v___x_3171_, v___y_3167_);
if (v___x_3172_ == 0)
{
uint64_t v___x_3173_; 
v___x_3173_ = lean_uint64_add(v___y_3161_, v___y_3160_);
v___y_3147_ = v___y_3170_;
v___y_3148_ = v___y_3163_;
v___y_3149_ = v___y_3162_;
v___y_3150_ = v___y_3164_;
v___y_3151_ = v___y_3165_;
v___y_3152_ = v___y_3167_;
v___y_3153_ = v___y_3169_;
v___y_3154_ = v___y_3168_;
v___y_3155_ = v___x_3173_;
goto v___jp_3146_;
}
else
{
v___y_3147_ = v___y_3170_;
v___y_3148_ = v___y_3163_;
v___y_3149_ = v___y_3162_;
v___y_3150_ = v___y_3164_;
v___y_3151_ = v___y_3165_;
v___y_3152_ = v___y_3167_;
v___y_3153_ = v___y_3169_;
v___y_3154_ = v___y_3168_;
v___y_3155_ = v___y_3161_;
goto v___jp_3146_;
}
}
v___jp_3174_:
{
uint64_t v___x_3184_; uint64_t v___x_3185_; uint8_t v___x_3186_; 
v___x_3184_ = 8ULL;
v___x_3185_ = lean_uint64_shift_right(v___y_3180_, v___x_3184_);
v___x_3186_ = lean_uint64_dec_eq(v___x_3185_, v___y_3179_);
if (v___x_3186_ == 0)
{
v___y_3160_ = v___x_3184_;
v___y_3161_ = v___y_3183_;
v___y_3162_ = v___y_3176_;
v___y_3163_ = v___y_3175_;
v___y_3164_ = v___y_3177_;
v___y_3165_ = v___y_3178_;
v___y_3166_ = v___y_3180_;
v___y_3167_ = v___y_3179_;
v___y_3168_ = v___y_3182_;
v___y_3169_ = v___y_3181_;
v___y_3170_ = v___x_3185_;
goto v___jp_3159_;
}
else
{
v___y_3160_ = v___x_3184_;
v___y_3161_ = v___y_3183_;
v___y_3162_ = v___y_3176_;
v___y_3163_ = v___y_3175_;
v___y_3164_ = v___y_3177_;
v___y_3165_ = v___y_3178_;
v___y_3166_ = v___y_3180_;
v___y_3167_ = v___y_3179_;
v___y_3168_ = v___y_3182_;
v___y_3169_ = v___y_3181_;
v___y_3170_ = v___y_3180_;
goto v___jp_3159_;
}
}
v___jp_3187_:
{
uint64_t v___x_3199_; uint8_t v___x_3200_; 
v___x_3199_ = lean_uint64_shift_right(v___y_3189_, v___y_3188_);
v___x_3200_ = lean_uint64_dec_eq(v___x_3199_, v___y_3194_);
if (v___x_3200_ == 0)
{
uint64_t v___x_3201_; 
v___x_3201_ = lean_uint64_add(v___y_3195_, v___y_3188_);
v___y_3175_ = v___y_3191_;
v___y_3176_ = v___y_3190_;
v___y_3177_ = v___y_3192_;
v___y_3178_ = v___y_3193_;
v___y_3179_ = v___y_3194_;
v___y_3180_ = v___y_3198_;
v___y_3181_ = v___y_3197_;
v___y_3182_ = v___y_3196_;
v___y_3183_ = v___x_3201_;
goto v___jp_3174_;
}
else
{
v___y_3175_ = v___y_3191_;
v___y_3176_ = v___y_3190_;
v___y_3177_ = v___y_3192_;
v___y_3178_ = v___y_3193_;
v___y_3179_ = v___y_3194_;
v___y_3180_ = v___y_3198_;
v___y_3181_ = v___y_3197_;
v___y_3182_ = v___y_3196_;
v___y_3183_ = v___y_3195_;
goto v___jp_3174_;
}
}
v___jp_3202_:
{
uint64_t v___x_3212_; uint64_t v___x_3213_; uint8_t v___x_3214_; 
v___x_3212_ = 16ULL;
v___x_3213_ = lean_uint64_shift_right(v___y_3203_, v___x_3212_);
v___x_3214_ = lean_uint64_dec_eq(v___x_3213_, v___y_3208_);
if (v___x_3214_ == 0)
{
v___y_3188_ = v___x_3212_;
v___y_3189_ = v___y_3203_;
v___y_3190_ = v___y_3205_;
v___y_3191_ = v___y_3204_;
v___y_3192_ = v___y_3206_;
v___y_3193_ = v___y_3207_;
v___y_3194_ = v___y_3208_;
v___y_3195_ = v___y_3211_;
v___y_3196_ = v___y_3210_;
v___y_3197_ = v___y_3209_;
v___y_3198_ = v___x_3213_;
goto v___jp_3187_;
}
else
{
v___y_3188_ = v___x_3212_;
v___y_3189_ = v___y_3203_;
v___y_3190_ = v___y_3205_;
v___y_3191_ = v___y_3204_;
v___y_3192_ = v___y_3206_;
v___y_3193_ = v___y_3207_;
v___y_3194_ = v___y_3208_;
v___y_3195_ = v___y_3211_;
v___y_3196_ = v___y_3210_;
v___y_3197_ = v___y_3209_;
v___y_3198_ = v___y_3203_;
goto v___jp_3187_;
}
}
v___jp_3215_:
{
uint64_t v___x_3225_; uint8_t v___x_3226_; 
v___x_3225_ = lean_uint64_shift_right(v___y_3216_, v___y_3221_);
v___x_3226_ = lean_uint64_dec_eq(v___x_3225_, v___y_3220_);
if (v___x_3226_ == 0)
{
v___y_3203_ = v___y_3224_;
v___y_3204_ = v___y_3217_;
v___y_3205_ = v___y_3216_;
v___y_3206_ = v___y_3218_;
v___y_3207_ = v___y_3219_;
v___y_3208_ = v___y_3220_;
v___y_3209_ = v___y_3223_;
v___y_3210_ = v___y_3222_;
v___y_3211_ = v___y_3221_;
goto v___jp_3202_;
}
else
{
v___y_3203_ = v___y_3224_;
v___y_3204_ = v___y_3217_;
v___y_3205_ = v___y_3216_;
v___y_3206_ = v___y_3218_;
v___y_3207_ = v___y_3219_;
v___y_3208_ = v___y_3220_;
v___y_3209_ = v___y_3223_;
v___y_3210_ = v___y_3222_;
v___y_3211_ = v___y_3220_;
goto v___jp_3202_;
}
}
v___jp_3227_:
{
uint64_t v___x_3236_; uint64_t v___x_3237_; uint8_t v___x_3238_; 
v___x_3236_ = lean_uint64_mul(v___y_3232_, v___y_3228_);
v___x_3237_ = 0ULL;
v___x_3238_ = lean_uint64_dec_eq(v___x_3236_, v___x_3237_);
if (v___x_3238_ == 0)
{
uint64_t v___x_3239_; uint64_t v___x_3240_; uint64_t v___x_3241_; uint8_t v___x_3242_; 
v___x_3239_ = lean_uint64_add(v___y_3230_, v___y_3235_);
v___x_3240_ = 32ULL;
v___x_3241_ = lean_uint64_shift_right(v___x_3236_, v___x_3240_);
v___x_3242_ = lean_uint64_dec_eq(v___x_3241_, v___x_3237_);
if (v___x_3242_ == 0)
{
v___y_3216_ = v___x_3236_;
v___y_3217_ = v___y_3229_;
v___y_3218_ = v___x_3239_;
v___y_3219_ = v___y_3231_;
v___y_3220_ = v___x_3237_;
v___y_3221_ = v___x_3240_;
v___y_3222_ = v___y_3234_;
v___y_3223_ = v___y_3233_;
v___y_3224_ = v___x_3241_;
goto v___jp_3215_;
}
else
{
v___y_3216_ = v___x_3236_;
v___y_3217_ = v___y_3229_;
v___y_3218_ = v___x_3239_;
v___y_3219_ = v___y_3231_;
v___y_3220_ = v___x_3237_;
v___y_3221_ = v___x_3240_;
v___y_3222_ = v___y_3234_;
v___y_3223_ = v___y_3233_;
v___y_3224_ = v___x_3236_;
goto v___jp_3215_;
}
}
else
{
if (v___y_3234_ == 0)
{
uint32_t v___x_3243_; 
v___x_3243_ = 0;
return v___x_3243_;
}
else
{
uint32_t v___x_3244_; 
v___x_3244_ = 2147483648;
return v___x_3244_;
}
}
}
v___jp_3245_:
{
uint64_t v___x_3254_; uint64_t v___x_3255_; uint8_t v___x_3256_; 
v___x_3254_ = lean_uint32_to_uint64(v___y_3246_);
v___x_3255_ = 0ULL;
v___x_3256_ = lean_uint64_dec_eq(v___x_3254_, v___x_3255_);
if (v___x_3256_ == 0)
{
uint64_t v___x_3257_; uint64_t v___x_3258_; 
v___x_3257_ = 1ULL;
v___x_3258_ = lean_uint64_sub(v___x_3254_, v___x_3257_);
v___y_3228_ = v___y_3247_;
v___y_3229_ = v___y_3248_;
v___y_3230_ = v___y_3253_;
v___y_3231_ = v___y_3250_;
v___y_3232_ = v___y_3249_;
v___y_3233_ = v___y_3252_;
v___y_3234_ = v___y_3251_;
v___y_3235_ = v___x_3258_;
goto v___jp_3227_;
}
else
{
v___y_3228_ = v___y_3247_;
v___y_3229_ = v___y_3248_;
v___y_3230_ = v___y_3253_;
v___y_3231_ = v___y_3250_;
v___y_3232_ = v___y_3249_;
v___y_3233_ = v___y_3252_;
v___y_3234_ = v___y_3251_;
v___y_3235_ = v___x_3255_;
goto v___jp_3227_;
}
}
v___jp_3259_:
{
uint64_t v___x_3268_; uint64_t v___x_3269_; uint8_t v___x_3270_; 
v___x_3268_ = lean_uint32_to_uint64(v___y_3266_);
v___x_3269_ = 0ULL;
v___x_3270_ = lean_uint64_dec_eq(v___x_3268_, v___x_3269_);
if (v___x_3270_ == 0)
{
uint64_t v___x_3271_; uint64_t v___x_3272_; 
v___x_3271_ = 1ULL;
v___x_3272_ = lean_uint64_sub(v___x_3268_, v___x_3271_);
v___y_3246_ = v___y_3260_;
v___y_3247_ = v___y_3267_;
v___y_3248_ = v___y_3261_;
v___y_3249_ = v___y_3263_;
v___y_3250_ = v___y_3262_;
v___y_3251_ = v___y_3265_;
v___y_3252_ = v___y_3264_;
v___y_3253_ = v___x_3272_;
goto v___jp_3245_;
}
else
{
v___y_3246_ = v___y_3260_;
v___y_3247_ = v___y_3267_;
v___y_3248_ = v___y_3261_;
v___y_3249_ = v___y_3263_;
v___y_3250_ = v___y_3262_;
v___y_3251_ = v___y_3265_;
v___y_3252_ = v___y_3264_;
v___y_3253_ = v___x_3269_;
goto v___jp_3245_;
}
}
v___jp_3273_:
{
uint32_t v___x_3282_; uint8_t v___x_3283_; 
v___x_3282_ = 0;
v___x_3283_ = lean_uint32_dec_eq(v___y_3274_, v___x_3282_);
if (v___x_3283_ == 0)
{
uint64_t v___x_3284_; uint64_t v___x_3285_; uint64_t v___x_3286_; 
v___x_3284_ = lean_uint32_to_uint64(v___y_3275_);
v___x_3285_ = 8388608ULL;
v___x_3286_ = lean_uint64_lor(v___x_3284_, v___x_3285_);
v___y_3260_ = v___y_3274_;
v___y_3261_ = v___y_3276_;
v___y_3262_ = v___y_3277_;
v___y_3263_ = v___y_3281_;
v___y_3264_ = v___y_3279_;
v___y_3265_ = v___y_3278_;
v___y_3266_ = v___y_3280_;
v___y_3267_ = v___x_3286_;
goto v___jp_3259_;
}
else
{
uint64_t v___x_3287_; 
v___x_3287_ = lean_uint32_to_uint64(v___y_3275_);
v___y_3260_ = v___y_3274_;
v___y_3261_ = v___y_3276_;
v___y_3262_ = v___y_3277_;
v___y_3263_ = v___y_3281_;
v___y_3264_ = v___y_3279_;
v___y_3265_ = v___y_3278_;
v___y_3266_ = v___y_3280_;
v___y_3267_ = v___x_3287_;
goto v___jp_3259_;
}
}
v___jp_3288_:
{
uint32_t v___x_3294_; uint32_t v_xFraction_3295_; uint32_t v_yFraction_3296_; uint32_t v___x_3297_; uint8_t v___x_3298_; 
v___x_3294_ = 8388607;
v_xFraction_3295_ = lean_uint32_land(v_x_2937_, v___x_3294_);
v_yFraction_3296_ = lean_uint32_land(v_y_2938_, v___x_3294_);
v___x_3297_ = 0;
v___x_3298_ = lean_uint32_dec_eq(v___y_3292_, v___x_3297_);
if (v___x_3298_ == 0)
{
uint64_t v___x_3299_; uint64_t v___x_3300_; uint64_t v___x_3301_; 
v___x_3299_ = lean_uint32_to_uint64(v_xFraction_3295_);
v___x_3300_ = 8388608ULL;
v___x_3301_ = lean_uint64_lor(v___x_3299_, v___x_3300_);
v___y_3274_ = v___y_3289_;
v___y_3275_ = v_yFraction_3296_;
v___y_3276_ = v___x_3294_;
v___y_3277_ = v___y_3290_;
v___y_3278_ = v___y_3293_;
v___y_3279_ = v___y_3291_;
v___y_3280_ = v___y_3292_;
v___y_3281_ = v___x_3301_;
goto v___jp_3273_;
}
else
{
uint64_t v___x_3302_; 
v___x_3302_ = lean_uint32_to_uint64(v_xFraction_3295_);
v___y_3274_ = v___y_3289_;
v___y_3275_ = v_yFraction_3296_;
v___y_3276_ = v___x_3294_;
v___y_3277_ = v___y_3290_;
v___y_3278_ = v___y_3293_;
v___y_3279_ = v___y_3291_;
v___y_3280_ = v___y_3292_;
v___y_3281_ = v___x_3302_;
goto v___jp_3273_;
}
}
v___jp_3303_:
{
uint8_t v___x_3308_; 
v___x_3308_ = 1;
v___y_3289_ = v___y_3304_;
v___y_3290_ = v___y_3305_;
v___y_3291_ = v___y_3306_;
v___y_3292_ = v___y_3307_;
v___y_3293_ = v___x_3308_;
goto v___jp_3288_;
}
v___jp_3309_:
{
if (v___y_3312_ == 0)
{
if (v___y_3316_ == 0)
{
v___y_3289_ = v___y_3310_;
v___y_3290_ = v___y_3313_;
v___y_3291_ = v___y_3314_;
v___y_3292_ = v___y_3315_;
v___y_3293_ = v___y_3311_;
goto v___jp_3288_;
}
else
{
v___y_3304_ = v___y_3310_;
v___y_3305_ = v___y_3313_;
v___y_3306_ = v___y_3314_;
v___y_3307_ = v___y_3315_;
goto v___jp_3303_;
}
}
else
{
if (v___y_3316_ == 0)
{
v___y_3304_ = v___y_3310_;
v___y_3305_ = v___y_3313_;
v___y_3306_ = v___y_3314_;
v___y_3307_ = v___y_3315_;
goto v___jp_3303_;
}
else
{
v___y_3289_ = v___y_3310_;
v___y_3290_ = v___y_3313_;
v___y_3291_ = v___y_3314_;
v___y_3292_ = v___y_3315_;
v___y_3293_ = v___y_3311_;
goto v___jp_3288_;
}
}
}
v___jp_3317_:
{
uint32_t v___x_3324_; uint32_t v___x_3325_; uint32_t v___x_3326_; uint8_t v___x_3327_; 
v___x_3324_ = 2147483648;
v___x_3325_ = lean_uint32_land(v_y_2938_, v___x_3324_);
v___x_3326_ = 0;
v___x_3327_ = lean_uint32_dec_eq(v___x_3325_, v___x_3326_);
if (v___x_3327_ == 0)
{
uint8_t v___x_3328_; 
v___x_3328_ = 1;
v___y_3310_ = v___y_3318_;
v___y_3311_ = v___y_3319_;
v___y_3312_ = v___y_3323_;
v___y_3313_ = v___y_3320_;
v___y_3314_ = v___y_3321_;
v___y_3315_ = v___y_3322_;
v___y_3316_ = v___x_3328_;
goto v___jp_3309_;
}
else
{
v___y_3310_ = v___y_3318_;
v___y_3311_ = v___y_3319_;
v___y_3312_ = v___y_3323_;
v___y_3313_ = v___y_3320_;
v___y_3314_ = v___y_3321_;
v___y_3315_ = v___y_3322_;
v___y_3316_ = v___y_3319_;
goto v___jp_3309_;
}
}
v___jp_3329_:
{
if (v___y_3330_ == 0)
{
uint32_t v___x_3331_; uint32_t v___x_3332_; uint32_t v___x_3333_; uint32_t v_xExponent_3334_; uint32_t v___x_3335_; uint32_t v_yExponent_3336_; uint32_t v___x_3337_; uint32_t v___x_3338_; uint32_t v___x_3339_; uint8_t v___x_3340_; 
v___x_3331_ = 23;
v___x_3332_ = lean_uint32_shift_right(v_x_2937_, v___x_3331_);
v___x_3333_ = 255;
v_xExponent_3334_ = lean_uint32_land(v___x_3332_, v___x_3333_);
v___x_3335_ = lean_uint32_shift_right(v_y_2938_, v___x_3331_);
v_yExponent_3336_ = lean_uint32_land(v___x_3335_, v___x_3333_);
v___x_3337_ = 2147483648;
v___x_3338_ = lean_uint32_land(v_x_2937_, v___x_3337_);
v___x_3339_ = 0;
v___x_3340_ = lean_uint32_dec_eq(v___x_3338_, v___x_3339_);
if (v___x_3340_ == 0)
{
uint8_t v___x_3341_; 
v___x_3341_ = 1;
v___y_3318_ = v_yExponent_3336_;
v___y_3319_ = v___y_3330_;
v___y_3320_ = v___x_3331_;
v___y_3321_ = v___x_3333_;
v___y_3322_ = v_xExponent_3334_;
v___y_3323_ = v___x_3341_;
goto v___jp_3317_;
}
else
{
v___y_3318_ = v_yExponent_3336_;
v___y_3319_ = v___y_3330_;
v___y_3320_ = v___x_3331_;
v___y_3321_ = v___x_3333_;
v___y_3322_ = v_xExponent_3334_;
v___y_3323_ = v___y_3330_;
goto v___jp_3317_;
}
}
else
{
lean_object* v___x_3342_; lean_object* v___x_3343_; lean_object* v___x_3344_; uint32_t v___x_3345_; 
v___x_3342_ = lean_uint32_to_nat(v_x_2937_);
v___x_3343_ = lean_uint32_to_nat(v_y_2938_);
v___x_3344_ = lp_floatlib_FloatLib_Floats_Formats_BinaryInterchange_Model_MulBackend_word___at___00FloatLib_Floats_Formats_BinaryInterchange_Configured_Plan_softwareMul32Certified_spec__1(v___x_3342_, v___x_3343_);
v___x_3345_ = lean_uint32_of_nat(v___x_3344_);
lean_dec(v___x_3344_);
return v___x_3345_;
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_FastMul_mul___boxed(lean_object* v_x_3352_, lean_object* v_y_3353_){
_start:
{
uint32_t v_x_boxed_3354_; uint32_t v_y_boxed_3355_; uint32_t v_res_3356_; lean_object* v_r_3357_; 
v_x_boxed_3354_ = lean_unbox_uint32(v_x_3352_);
lean_dec(v_x_3352_);
v_y_boxed_3355_ = lean_unbox_uint32(v_y_3353_);
lean_dec(v_y_3353_);
v_res_3356_ = lp_competition_Submission_FastMul_mul(v_x_boxed_3354_, v_y_boxed_3355_);
v_r_3357_ = lean_box_uint32(v_res_3356_);
return v_r_3357_;
}
}
static uint8_t _init_lp_competition_Submission_FastMul_Plan(void){
_start:
{
uint8_t v___x_3359_; 
v___x_3359_ = 2;
return v___x_3359_;
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_FastMul_dec(uint32_t v_z_3360_){
_start:
{
lean_object* v___x_3361_; 
v___x_3361_ = lean_uint32_to_nat(v_z_3360_);
return v___x_3361_;
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_FastMul_dec___boxed(lean_object* v_z_3362_){
_start:
{
uint32_t v_z_boxed_3363_; lean_object* v_res_3364_; 
v_z_boxed_3363_ = lean_unbox_uint32(v_z_3362_);
lean_dec(v_z_3362_);
v_res_3364_ = lp_competition_Submission_FastMul_dec(v_z_boxed_3363_);
return v_res_3364_;
}
}
LEAN_EXPORT uint64_t lp_competition_Submission_R6NormalMul_leading(uint64_t v_x_3365_){
_start:
{
uint64_t v___y_3367_; uint64_t v___y_3368_; uint64_t v___y_3375_; uint64_t v___y_3376_; uint64_t v___y_3377_; uint64_t v___y_3378_; uint64_t v___y_3384_; uint64_t v___y_3385_; uint64_t v___y_3391_; uint64_t v___y_3392_; uint64_t v___y_3393_; uint64_t v___y_3394_; uint64_t v___y_3400_; uint64_t v___y_3401_; uint64_t v___y_3407_; uint64_t v___y_3408_; uint64_t v___y_3409_; uint64_t v___y_3410_; uint64_t v___y_3416_; uint64_t v___y_3417_; uint64_t v___y_3423_; uint64_t v___y_3424_; uint64_t v___y_3425_; uint64_t v___y_3426_; uint64_t v___y_3432_; uint64_t v___y_3433_; uint64_t v___y_3439_; uint64_t v___y_3440_; uint64_t v___x_3449_; uint8_t v___x_3450_; 
v___x_3449_ = 70368744177664ULL;
v___x_3450_ = lean_uint64_dec_le(v___x_3449_, v_x_3365_);
if (v___x_3450_ == 0)
{
goto v___jp_3444_;
}
else
{
uint64_t v___x_3451_; uint8_t v___x_3452_; 
v___x_3451_ = 281474976710656ULL;
v___x_3452_ = lean_uint64_dec_lt(v_x_3365_, v___x_3451_);
if (v___x_3452_ == 0)
{
goto v___jp_3444_;
}
else
{
uint64_t v___x_3453_; uint8_t v___x_3454_; 
v___x_3453_ = 140737488355328ULL;
v___x_3454_ = lean_uint64_dec_lt(v_x_3365_, v___x_3453_);
if (v___x_3454_ == 0)
{
uint64_t v___x_3455_; 
v___x_3455_ = 47ULL;
return v___x_3455_;
}
else
{
uint64_t v___x_3456_; 
v___x_3456_ = 46ULL;
return v___x_3456_;
}
}
}
v___jp_3366_:
{
uint64_t v___x_3369_; uint64_t v___x_3370_; uint64_t v___x_3371_; uint8_t v___x_3372_; 
v___x_3369_ = 1ULL;
v___x_3370_ = lean_uint64_shift_right(v___y_3367_, v___x_3369_);
v___x_3371_ = 0ULL;
v___x_3372_ = lean_uint64_dec_eq(v___x_3370_, v___x_3371_);
if (v___x_3372_ == 0)
{
uint64_t v___x_3373_; 
v___x_3373_ = lean_uint64_add(v___y_3368_, v___x_3369_);
return v___x_3373_;
}
else
{
return v___y_3368_;
}
}
v___jp_3374_:
{
uint64_t v___x_3379_; uint64_t v___x_3380_; uint8_t v___x_3381_; 
v___x_3379_ = lean_uint64_shift_right(v___y_3377_, v___y_3376_);
v___x_3380_ = 0ULL;
v___x_3381_ = lean_uint64_dec_eq(v___x_3379_, v___x_3380_);
if (v___x_3381_ == 0)
{
uint64_t v___x_3382_; 
v___x_3382_ = lean_uint64_add(v___y_3375_, v___y_3376_);
v___y_3367_ = v___y_3378_;
v___y_3368_ = v___x_3382_;
goto v___jp_3366_;
}
else
{
v___y_3367_ = v___y_3378_;
v___y_3368_ = v___y_3375_;
goto v___jp_3366_;
}
}
v___jp_3383_:
{
uint64_t v___x_3386_; uint64_t v___x_3387_; uint64_t v___x_3388_; uint8_t v___x_3389_; 
v___x_3386_ = 2ULL;
v___x_3387_ = lean_uint64_shift_right(v___y_3384_, v___x_3386_);
v___x_3388_ = 0ULL;
v___x_3389_ = lean_uint64_dec_eq(v___x_3387_, v___x_3388_);
if (v___x_3389_ == 0)
{
v___y_3375_ = v___y_3385_;
v___y_3376_ = v___x_3386_;
v___y_3377_ = v___y_3384_;
v___y_3378_ = v___x_3387_;
goto v___jp_3374_;
}
else
{
v___y_3375_ = v___y_3385_;
v___y_3376_ = v___x_3386_;
v___y_3377_ = v___y_3384_;
v___y_3378_ = v___y_3384_;
goto v___jp_3374_;
}
}
v___jp_3390_:
{
uint64_t v___x_3395_; uint64_t v___x_3396_; uint8_t v___x_3397_; 
v___x_3395_ = lean_uint64_shift_right(v___y_3393_, v___y_3391_);
v___x_3396_ = 0ULL;
v___x_3397_ = lean_uint64_dec_eq(v___x_3395_, v___x_3396_);
if (v___x_3397_ == 0)
{
uint64_t v___x_3398_; 
v___x_3398_ = lean_uint64_add(v___y_3392_, v___y_3391_);
v___y_3384_ = v___y_3394_;
v___y_3385_ = v___x_3398_;
goto v___jp_3383_;
}
else
{
v___y_3384_ = v___y_3394_;
v___y_3385_ = v___y_3392_;
goto v___jp_3383_;
}
}
v___jp_3399_:
{
uint64_t v___x_3402_; uint64_t v___x_3403_; uint64_t v___x_3404_; uint8_t v___x_3405_; 
v___x_3402_ = 4ULL;
v___x_3403_ = lean_uint64_shift_right(v___y_3400_, v___x_3402_);
v___x_3404_ = 0ULL;
v___x_3405_ = lean_uint64_dec_eq(v___x_3403_, v___x_3404_);
if (v___x_3405_ == 0)
{
v___y_3391_ = v___x_3402_;
v___y_3392_ = v___y_3401_;
v___y_3393_ = v___y_3400_;
v___y_3394_ = v___x_3403_;
goto v___jp_3390_;
}
else
{
v___y_3391_ = v___x_3402_;
v___y_3392_ = v___y_3401_;
v___y_3393_ = v___y_3400_;
v___y_3394_ = v___y_3400_;
goto v___jp_3390_;
}
}
v___jp_3406_:
{
uint64_t v___x_3411_; uint64_t v___x_3412_; uint8_t v___x_3413_; 
v___x_3411_ = lean_uint64_shift_right(v___y_3409_, v___y_3408_);
v___x_3412_ = 0ULL;
v___x_3413_ = lean_uint64_dec_eq(v___x_3411_, v___x_3412_);
if (v___x_3413_ == 0)
{
uint64_t v___x_3414_; 
v___x_3414_ = lean_uint64_add(v___y_3407_, v___y_3408_);
v___y_3400_ = v___y_3410_;
v___y_3401_ = v___x_3414_;
goto v___jp_3399_;
}
else
{
v___y_3400_ = v___y_3410_;
v___y_3401_ = v___y_3407_;
goto v___jp_3399_;
}
}
v___jp_3415_:
{
uint64_t v___x_3418_; uint64_t v___x_3419_; uint64_t v___x_3420_; uint8_t v___x_3421_; 
v___x_3418_ = 8ULL;
v___x_3419_ = lean_uint64_shift_right(v___y_3416_, v___x_3418_);
v___x_3420_ = 0ULL;
v___x_3421_ = lean_uint64_dec_eq(v___x_3419_, v___x_3420_);
if (v___x_3421_ == 0)
{
v___y_3407_ = v___y_3417_;
v___y_3408_ = v___x_3418_;
v___y_3409_ = v___y_3416_;
v___y_3410_ = v___x_3419_;
goto v___jp_3406_;
}
else
{
v___y_3407_ = v___y_3417_;
v___y_3408_ = v___x_3418_;
v___y_3409_ = v___y_3416_;
v___y_3410_ = v___y_3416_;
goto v___jp_3406_;
}
}
v___jp_3422_:
{
uint64_t v___x_3427_; uint64_t v___x_3428_; uint8_t v___x_3429_; 
v___x_3427_ = lean_uint64_shift_right(v___y_3424_, v___y_3425_);
v___x_3428_ = 0ULL;
v___x_3429_ = lean_uint64_dec_eq(v___x_3427_, v___x_3428_);
if (v___x_3429_ == 0)
{
uint64_t v___x_3430_; 
v___x_3430_ = lean_uint64_add(v___y_3423_, v___y_3425_);
v___y_3416_ = v___y_3426_;
v___y_3417_ = v___x_3430_;
goto v___jp_3415_;
}
else
{
v___y_3416_ = v___y_3426_;
v___y_3417_ = v___y_3423_;
goto v___jp_3415_;
}
}
v___jp_3431_:
{
uint64_t v___x_3434_; uint64_t v___x_3435_; uint64_t v___x_3436_; uint8_t v___x_3437_; 
v___x_3434_ = 16ULL;
v___x_3435_ = lean_uint64_shift_right(v___y_3432_, v___x_3434_);
v___x_3436_ = 0ULL;
v___x_3437_ = lean_uint64_dec_eq(v___x_3435_, v___x_3436_);
if (v___x_3437_ == 0)
{
v___y_3423_ = v___y_3433_;
v___y_3424_ = v___y_3432_;
v___y_3425_ = v___x_3434_;
v___y_3426_ = v___x_3435_;
goto v___jp_3422_;
}
else
{
v___y_3423_ = v___y_3433_;
v___y_3424_ = v___y_3432_;
v___y_3425_ = v___x_3434_;
v___y_3426_ = v___y_3432_;
goto v___jp_3422_;
}
}
v___jp_3438_:
{
uint64_t v___x_3441_; uint64_t v___x_3442_; uint8_t v___x_3443_; 
v___x_3441_ = lean_uint64_shift_right(v_x_3365_, v___y_3439_);
v___x_3442_ = 0ULL;
v___x_3443_ = lean_uint64_dec_eq(v___x_3441_, v___x_3442_);
if (v___x_3443_ == 0)
{
v___y_3432_ = v___y_3440_;
v___y_3433_ = v___y_3439_;
goto v___jp_3431_;
}
else
{
v___y_3432_ = v___y_3440_;
v___y_3433_ = v___x_3442_;
goto v___jp_3431_;
}
}
v___jp_3444_:
{
uint64_t v___x_3445_; uint64_t v___x_3446_; uint64_t v___x_3447_; uint8_t v___x_3448_; 
v___x_3445_ = 32ULL;
v___x_3446_ = lean_uint64_shift_right(v_x_3365_, v___x_3445_);
v___x_3447_ = 0ULL;
v___x_3448_ = lean_uint64_dec_eq(v___x_3446_, v___x_3447_);
if (v___x_3448_ == 0)
{
v___y_3439_ = v___x_3445_;
v___y_3440_ = v___x_3446_;
goto v___jp_3438_;
}
else
{
v___y_3439_ = v___x_3445_;
v___y_3440_ = v_x_3365_;
goto v___jp_3438_;
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_R6NormalMul_leading___boxed(lean_object* v_x_3457_){
_start:
{
uint64_t v_x_boxed_3458_; uint64_t v_res_3459_; lean_object* v_r_3460_; 
v_x_boxed_3458_ = lean_unbox_uint64(v_x_3457_);
lean_dec_ref(v_x_3457_);
v_res_3459_ = lp_competition_Submission_R6NormalMul_leading(v_x_boxed_3458_);
v_r_3460_ = lean_box_uint64(v_res_3459_);
return v_r_3460_;
}
}
LEAN_EXPORT uint32_t lp_competition_Submission_R6NormalMul_roundP(uint8_t v_sign_3461_, uint64_t v_product_3462_, uint64_t v_scale_3463_){
_start:
{
uint32_t v___y_3465_; uint32_t v___y_3469_; uint32_t v___y_3470_; uint32_t v___y_3475_; uint32_t v___y_3476_; uint32_t v___y_3477_; uint32_t v___y_3487_; uint32_t v___y_3488_; uint64_t v___x_3491_; uint64_t v___y_3493_; uint64_t v___y_3505_; uint64_t v___y_3506_; uint8_t v___y_3516_; uint64_t v___y_3517_; uint64_t v___y_3518_; uint64_t v___y_3525_; uint64_t v___y_3526_; uint64_t v___y_3532_; uint64_t v___y_3587_; uint64_t v___y_3588_; uint64_t v___y_3594_; uint64_t v___y_3595_; uint64_t v___y_3596_; uint64_t v___y_3597_; uint64_t v___y_3602_; uint64_t v___y_3603_; uint64_t v___y_3608_; uint64_t v___y_3609_; uint64_t v___y_3610_; uint64_t v___y_3611_; uint64_t v___y_3616_; uint64_t v___y_3617_; uint64_t v___y_3622_; uint64_t v___y_3623_; uint64_t v___y_3624_; uint64_t v___y_3625_; uint64_t v___y_3630_; uint64_t v___y_3631_; uint64_t v___y_3636_; uint64_t v___y_3637_; uint64_t v___y_3638_; uint64_t v___y_3639_; uint64_t v___y_3644_; uint64_t v___y_3645_; uint64_t v___y_3650_; uint64_t v___y_3651_; uint8_t v___x_3658_; 
v___x_3491_ = 0ULL;
v___x_3658_ = lean_uint64_dec_eq(v_product_3462_, v___x_3491_);
if (v___x_3658_ == 0)
{
uint64_t v___x_3659_; uint8_t v___x_3660_; 
v___x_3659_ = 70368744177664ULL;
v___x_3660_ = lean_uint64_dec_le(v___x_3659_, v_product_3462_);
if (v___x_3660_ == 0)
{
goto v___jp_3654_;
}
else
{
uint64_t v___x_3661_; uint8_t v___x_3662_; 
v___x_3661_ = 281474976710656ULL;
v___x_3662_ = lean_uint64_dec_lt(v_product_3462_, v___x_3661_);
if (v___x_3662_ == 0)
{
goto v___jp_3654_;
}
else
{
uint64_t v___x_3663_; uint8_t v___x_3664_; 
v___x_3663_ = 140737488355328ULL;
v___x_3664_ = lean_uint64_dec_lt(v_product_3462_, v___x_3663_);
if (v___x_3664_ == 0)
{
uint64_t v___x_3665_; 
v___x_3665_ = 47ULL;
v___y_3532_ = v___x_3665_;
goto v___jp_3531_;
}
else
{
uint64_t v___x_3666_; 
v___x_3666_ = 46ULL;
v___y_3532_ = v___x_3666_;
goto v___jp_3531_;
}
}
}
}
else
{
if (v_sign_3461_ == 0)
{
uint32_t v___x_3667_; 
v___x_3667_ = 0;
return v___x_3667_;
}
else
{
uint32_t v___x_3668_; 
v___x_3668_ = 2147483648;
return v___x_3668_;
}
}
v___jp_3464_:
{
uint32_t v___x_3466_; uint32_t v___x_3467_; 
v___x_3466_ = 8388608;
v___x_3467_ = lean_uint32_lor(v___y_3465_, v___x_3466_);
return v___x_3467_;
}
v___jp_3468_:
{
uint32_t v___x_3471_; uint32_t v___x_3472_; uint32_t v___x_3473_; 
v___x_3471_ = 8388607;
v___x_3472_ = lean_uint32_land(v___y_3469_, v___x_3471_);
v___x_3473_ = lean_uint32_lor(v___y_3470_, v___x_3472_);
return v___x_3473_;
}
v___jp_3474_:
{
uint32_t v___x_3478_; uint32_t v___x_3479_; uint32_t v___x_3480_; uint32_t v___x_3481_; uint32_t v___x_3482_; uint32_t v___x_3483_; uint32_t v___x_3484_; uint32_t v___x_3485_; 
v___x_3478_ = 255;
v___x_3479_ = lean_uint32_land(v___y_3475_, v___x_3478_);
v___x_3480_ = 23;
v___x_3481_ = lean_uint32_shift_left(v___x_3479_, v___x_3480_);
v___x_3482_ = lean_uint32_lor(v___y_3477_, v___x_3481_);
v___x_3483_ = 8388607;
v___x_3484_ = lean_uint32_land(v___y_3476_, v___x_3483_);
v___x_3485_ = lean_uint32_lor(v___x_3482_, v___x_3484_);
return v___x_3485_;
}
v___jp_3486_:
{
if (v_sign_3461_ == 0)
{
uint32_t v___x_3489_; 
v___x_3489_ = 0;
v___y_3475_ = v___y_3487_;
v___y_3476_ = v___y_3488_;
v___y_3477_ = v___x_3489_;
goto v___jp_3474_;
}
else
{
uint32_t v___x_3490_; 
v___x_3490_ = 2147483648;
v___y_3475_ = v___y_3487_;
v___y_3476_ = v___y_3488_;
v___y_3477_ = v___x_3490_;
goto v___jp_3474_;
}
}
v___jp_3492_:
{
uint8_t v___x_3494_; 
v___x_3494_ = lean_uint64_dec_eq(v___y_3493_, v___x_3491_);
if (v___x_3494_ == 0)
{
uint64_t v___x_3495_; uint8_t v___x_3496_; 
v___x_3495_ = 8388608ULL;
v___x_3496_ = lean_uint64_dec_eq(v___y_3493_, v___x_3495_);
if (v___x_3496_ == 0)
{
uint32_t v___x_3497_; 
v___x_3497_ = lean_uint64_to_uint32(v___y_3493_);
if (v_sign_3461_ == 0)
{
uint32_t v___x_3498_; 
v___x_3498_ = 0;
v___y_3469_ = v___x_3497_;
v___y_3470_ = v___x_3498_;
goto v___jp_3468_;
}
else
{
uint32_t v___x_3499_; 
v___x_3499_ = 2147483648;
v___y_3469_ = v___x_3497_;
v___y_3470_ = v___x_3499_;
goto v___jp_3468_;
}
}
else
{
if (v_sign_3461_ == 0)
{
uint32_t v___x_3500_; 
v___x_3500_ = 0;
v___y_3465_ = v___x_3500_;
goto v___jp_3464_;
}
else
{
uint32_t v___x_3501_; 
v___x_3501_ = 2147483648;
v___y_3465_ = v___x_3501_;
goto v___jp_3464_;
}
}
}
else
{
if (v_sign_3461_ == 0)
{
uint32_t v___x_3502_; 
v___x_3502_ = 0;
return v___x_3502_;
}
else
{
uint32_t v___x_3503_; 
v___x_3503_ = 2147483648;
return v___x_3503_;
}
}
}
v___jp_3504_:
{
uint64_t v___x_3507_; uint64_t v_encodedExponent_3508_; uint32_t v___x_3509_; uint64_t v___x_3510_; uint8_t v___x_3511_; 
v___x_3507_ = 171ULL;
v_encodedExponent_3508_ = lean_uint64_sub(v___y_3505_, v___x_3507_);
v___x_3509_ = lean_uint64_to_uint32(v_encodedExponent_3508_);
v___x_3510_ = 8388608ULL;
v___x_3511_ = lean_uint64_dec_lt(v___y_3506_, v___x_3510_);
if (v___x_3511_ == 0)
{
uint64_t v___x_3512_; uint32_t v___x_3513_; 
v___x_3512_ = lean_uint64_sub(v___y_3506_, v___x_3510_);
v___x_3513_ = lean_uint64_to_uint32(v___x_3512_);
v___y_3487_ = v___x_3509_;
v___y_3488_ = v___x_3513_;
goto v___jp_3486_;
}
else
{
uint32_t v___x_3514_; 
v___x_3514_ = lean_uint32_once(&lp_competition_Submission_TunedAdd_fracW___closed__0, &lp_competition_Submission_TunedAdd_fracW___closed__0_once, _init_lp_competition_Submission_TunedAdd_fracW___closed__0);
v___y_3487_ = v___x_3509_;
v___y_3488_ = v___x_3514_;
goto v___jp_3486_;
}
}
v___jp_3515_:
{
uint64_t v___x_3519_; uint8_t v___x_3520_; 
v___x_3519_ = 425ULL;
v___x_3520_ = lean_uint64_dec_lt(v___x_3519_, v___y_3518_);
if (v___x_3520_ == 0)
{
if (v___y_3516_ == 0)
{
v___y_3505_ = v___y_3518_;
v___y_3506_ = v___y_3517_;
goto v___jp_3504_;
}
else
{
uint64_t v___x_3521_; 
v___x_3521_ = 8388608ULL;
v___y_3505_ = v___y_3518_;
v___y_3506_ = v___x_3521_;
goto v___jp_3504_;
}
}
else
{
if (v_sign_3461_ == 0)
{
uint32_t v___x_3522_; 
v___x_3522_ = 2139095040;
return v___x_3522_;
}
else
{
uint32_t v___x_3523_; 
v___x_3523_ = 4286578688;
return v___x_3523_;
}
}
}
v___jp_3524_:
{
uint64_t v___x_3527_; uint8_t v_carry_3528_; 
v___x_3527_ = 16777216ULL;
v_carry_3528_ = lean_uint64_dec_eq(v___y_3526_, v___x_3527_);
if (v_carry_3528_ == 0)
{
v___y_3516_ = v_carry_3528_;
v___y_3517_ = v___y_3526_;
v___y_3518_ = v___y_3525_;
goto v___jp_3515_;
}
else
{
uint64_t v___x_3529_; uint64_t v___x_3530_; 
v___x_3529_ = 1ULL;
v___x_3530_ = lean_uint64_add(v___y_3525_, v___x_3529_);
v___y_3516_ = v_carry_3528_;
v___y_3517_ = v___y_3526_;
v___y_3518_ = v___x_3530_;
goto v___jp_3515_;
}
}
v___jp_3531_:
{
uint64_t v_position_3533_; uint64_t v___x_3534_; uint8_t v___x_3535_; 
v_position_3533_ = lean_uint64_add(v___y_3532_, v_scale_3463_);
v___x_3534_ = 172ULL;
v___x_3535_ = lean_uint64_dec_lt(v_position_3533_, v___x_3534_);
if (v___x_3535_ == 0)
{
uint64_t v___x_3536_; uint8_t v___x_3537_; 
v___x_3536_ = 23ULL;
v___x_3537_ = lean_uint64_dec_lt(v___y_3532_, v___x_3536_);
if (v___x_3537_ == 0)
{
uint64_t v___x_3538_; uint8_t v___x_3539_; 
v___x_3538_ = lean_uint64_sub(v___y_3532_, v___x_3536_);
v___x_3539_ = lean_uint64_dec_eq(v___x_3538_, v___x_3491_);
if (v___x_3539_ == 0)
{
uint64_t v___x_3540_; uint8_t v___x_3541_; 
v___x_3540_ = 64ULL;
v___x_3541_ = lean_uint64_dec_lt(v___x_3538_, v___x_3540_);
if (v___x_3541_ == 0)
{
uint8_t v___x_3542_; 
v___x_3542_ = lean_uint64_dec_eq(v___x_3538_, v___x_3540_);
if (v___x_3542_ == 0)
{
v___y_3525_ = v_position_3533_;
v___y_3526_ = v___x_3491_;
goto v___jp_3524_;
}
else
{
uint64_t v___x_3543_; uint8_t v___x_3544_; 
v___x_3543_ = 9223372036854775808ULL;
v___x_3544_ = lean_uint64_dec_lt(v___x_3543_, v_product_3462_);
if (v___x_3544_ == 0)
{
v___y_3525_ = v_position_3533_;
v___y_3526_ = v___x_3491_;
goto v___jp_3524_;
}
else
{
uint64_t v___x_3545_; 
v___x_3545_ = 1ULL;
v___y_3525_ = v_position_3533_;
v___y_3526_ = v___x_3545_;
goto v___jp_3524_;
}
}
}
else
{
uint64_t v_quotient_3546_; uint64_t v___x_3547_; uint64_t v___x_3548_; uint64_t v___x_3549_; uint64_t v_remainder_3550_; uint64_t v___x_3551_; uint64_t v_half_3552_; uint8_t v___x_3553_; 
v_quotient_3546_ = lean_uint64_shift_right(v_product_3462_, v___x_3538_);
v___x_3547_ = 1ULL;
v___x_3548_ = lean_uint64_shift_left(v___x_3547_, v___x_3538_);
v___x_3549_ = lean_uint64_sub(v___x_3548_, v___x_3547_);
v_remainder_3550_ = lean_uint64_land(v_product_3462_, v___x_3549_);
v___x_3551_ = lean_uint64_sub(v___x_3538_, v___x_3547_);
v_half_3552_ = lean_uint64_shift_left(v___x_3547_, v___x_3551_);
v___x_3553_ = lean_uint64_dec_lt(v_remainder_3550_, v_half_3552_);
if (v___x_3553_ == 0)
{
uint8_t v___x_3554_; 
v___x_3554_ = lean_uint64_dec_lt(v_half_3552_, v_remainder_3550_);
if (v___x_3554_ == 0)
{
uint64_t v___x_3555_; uint8_t v___x_3556_; 
v___x_3555_ = lean_uint64_land(v_quotient_3546_, v___x_3547_);
v___x_3556_ = lean_uint64_dec_eq(v___x_3555_, v___x_3491_);
if (v___x_3556_ == 0)
{
uint64_t v___x_3557_; 
v___x_3557_ = lean_uint64_add(v_quotient_3546_, v___x_3547_);
v___y_3525_ = v_position_3533_;
v___y_3526_ = v___x_3557_;
goto v___jp_3524_;
}
else
{
v___y_3525_ = v_position_3533_;
v___y_3526_ = v_quotient_3546_;
goto v___jp_3524_;
}
}
else
{
uint64_t v___x_3558_; 
v___x_3558_ = lean_uint64_add(v_quotient_3546_, v___x_3547_);
v___y_3525_ = v_position_3533_;
v___y_3526_ = v___x_3558_;
goto v___jp_3524_;
}
}
else
{
v___y_3525_ = v_position_3533_;
v___y_3526_ = v_quotient_3546_;
goto v___jp_3524_;
}
}
}
else
{
v___y_3525_ = v_position_3533_;
v___y_3526_ = v_product_3462_;
goto v___jp_3524_;
}
}
else
{
uint64_t v___x_3559_; uint64_t v___x_3560_; 
v___x_3559_ = lean_uint64_sub(v___x_3536_, v___y_3532_);
v___x_3560_ = lean_uint64_shift_left(v_product_3462_, v___x_3559_);
v___y_3525_ = v_position_3533_;
v___y_3526_ = v___x_3560_;
goto v___jp_3524_;
}
}
else
{
uint64_t v___x_3561_; uint8_t v___x_3562_; 
v___x_3561_ = 149ULL;
v___x_3562_ = lean_uint64_dec_lt(v_scale_3463_, v___x_3561_);
if (v___x_3562_ == 0)
{
uint64_t v___x_3563_; uint64_t v___x_3564_; 
v___x_3563_ = lean_uint64_sub(v_scale_3463_, v___x_3561_);
v___x_3564_ = lean_uint64_shift_left(v_product_3462_, v___x_3563_);
v___y_3493_ = v___x_3564_;
goto v___jp_3492_;
}
else
{
uint64_t v___x_3565_; uint8_t v___x_3566_; 
v___x_3565_ = lean_uint64_sub(v___x_3561_, v_scale_3463_);
v___x_3566_ = lean_uint64_dec_eq(v___x_3565_, v___x_3491_);
if (v___x_3566_ == 0)
{
uint64_t v___x_3567_; uint8_t v___x_3568_; 
v___x_3567_ = 64ULL;
v___x_3568_ = lean_uint64_dec_lt(v___x_3565_, v___x_3567_);
if (v___x_3568_ == 0)
{
uint8_t v___x_3569_; 
v___x_3569_ = lean_uint64_dec_eq(v___x_3565_, v___x_3567_);
if (v___x_3569_ == 0)
{
v___y_3493_ = v___x_3491_;
goto v___jp_3492_;
}
else
{
uint64_t v___x_3570_; uint8_t v___x_3571_; 
v___x_3570_ = 9223372036854775808ULL;
v___x_3571_ = lean_uint64_dec_lt(v___x_3570_, v_product_3462_);
if (v___x_3571_ == 0)
{
v___y_3493_ = v___x_3491_;
goto v___jp_3492_;
}
else
{
uint64_t v___x_3572_; 
v___x_3572_ = 1ULL;
v___y_3493_ = v___x_3572_;
goto v___jp_3492_;
}
}
}
else
{
uint64_t v_quotient_3573_; uint64_t v___x_3574_; uint64_t v___x_3575_; uint64_t v___x_3576_; uint64_t v_remainder_3577_; uint64_t v___x_3578_; uint64_t v_half_3579_; uint8_t v___x_3580_; 
v_quotient_3573_ = lean_uint64_shift_right(v_product_3462_, v___x_3565_);
v___x_3574_ = 1ULL;
v___x_3575_ = lean_uint64_shift_left(v___x_3574_, v___x_3565_);
v___x_3576_ = lean_uint64_sub(v___x_3575_, v___x_3574_);
v_remainder_3577_ = lean_uint64_land(v_product_3462_, v___x_3576_);
v___x_3578_ = lean_uint64_sub(v___x_3565_, v___x_3574_);
v_half_3579_ = lean_uint64_shift_left(v___x_3574_, v___x_3578_);
v___x_3580_ = lean_uint64_dec_lt(v_remainder_3577_, v_half_3579_);
if (v___x_3580_ == 0)
{
uint8_t v___x_3581_; 
v___x_3581_ = lean_uint64_dec_lt(v_half_3579_, v_remainder_3577_);
if (v___x_3581_ == 0)
{
uint64_t v___x_3582_; uint8_t v___x_3583_; 
v___x_3582_ = lean_uint64_land(v_quotient_3573_, v___x_3574_);
v___x_3583_ = lean_uint64_dec_eq(v___x_3582_, v___x_3491_);
if (v___x_3583_ == 0)
{
uint64_t v___x_3584_; 
v___x_3584_ = lean_uint64_add(v_quotient_3573_, v___x_3574_);
v___y_3493_ = v___x_3584_;
goto v___jp_3492_;
}
else
{
v___y_3493_ = v_quotient_3573_;
goto v___jp_3492_;
}
}
else
{
uint64_t v___x_3585_; 
v___x_3585_ = lean_uint64_add(v_quotient_3573_, v___x_3574_);
v___y_3493_ = v___x_3585_;
goto v___jp_3492_;
}
}
else
{
v___y_3493_ = v_quotient_3573_;
goto v___jp_3492_;
}
}
}
else
{
v___y_3493_ = v_product_3462_;
goto v___jp_3492_;
}
}
}
}
v___jp_3586_:
{
uint64_t v___x_3589_; uint64_t v___x_3590_; uint8_t v___x_3591_; 
v___x_3589_ = 1ULL;
v___x_3590_ = lean_uint64_shift_right(v___y_3587_, v___x_3589_);
v___x_3591_ = lean_uint64_dec_eq(v___x_3590_, v___x_3491_);
if (v___x_3591_ == 0)
{
uint64_t v___x_3592_; 
v___x_3592_ = lean_uint64_add(v___y_3588_, v___x_3589_);
v___y_3532_ = v___x_3592_;
goto v___jp_3531_;
}
else
{
v___y_3532_ = v___y_3588_;
goto v___jp_3531_;
}
}
v___jp_3593_:
{
uint64_t v___x_3598_; uint8_t v___x_3599_; 
v___x_3598_ = lean_uint64_shift_right(v___y_3596_, v___y_3594_);
v___x_3599_ = lean_uint64_dec_eq(v___x_3598_, v___x_3491_);
if (v___x_3599_ == 0)
{
uint64_t v___x_3600_; 
v___x_3600_ = lean_uint64_add(v___y_3595_, v___y_3594_);
v___y_3587_ = v___y_3597_;
v___y_3588_ = v___x_3600_;
goto v___jp_3586_;
}
else
{
v___y_3587_ = v___y_3597_;
v___y_3588_ = v___y_3595_;
goto v___jp_3586_;
}
}
v___jp_3601_:
{
uint64_t v___x_3604_; uint64_t v___x_3605_; uint8_t v___x_3606_; 
v___x_3604_ = 2ULL;
v___x_3605_ = lean_uint64_shift_right(v___y_3602_, v___x_3604_);
v___x_3606_ = lean_uint64_dec_eq(v___x_3605_, v___x_3491_);
if (v___x_3606_ == 0)
{
v___y_3594_ = v___x_3604_;
v___y_3595_ = v___y_3603_;
v___y_3596_ = v___y_3602_;
v___y_3597_ = v___x_3605_;
goto v___jp_3593_;
}
else
{
v___y_3594_ = v___x_3604_;
v___y_3595_ = v___y_3603_;
v___y_3596_ = v___y_3602_;
v___y_3597_ = v___y_3602_;
goto v___jp_3593_;
}
}
v___jp_3607_:
{
uint64_t v___x_3612_; uint8_t v___x_3613_; 
v___x_3612_ = lean_uint64_shift_right(v___y_3608_, v___y_3610_);
v___x_3613_ = lean_uint64_dec_eq(v___x_3612_, v___x_3491_);
if (v___x_3613_ == 0)
{
uint64_t v___x_3614_; 
v___x_3614_ = lean_uint64_add(v___y_3609_, v___y_3610_);
v___y_3602_ = v___y_3611_;
v___y_3603_ = v___x_3614_;
goto v___jp_3601_;
}
else
{
v___y_3602_ = v___y_3611_;
v___y_3603_ = v___y_3609_;
goto v___jp_3601_;
}
}
v___jp_3615_:
{
uint64_t v___x_3618_; uint64_t v___x_3619_; uint8_t v___x_3620_; 
v___x_3618_ = 4ULL;
v___x_3619_ = lean_uint64_shift_right(v___y_3616_, v___x_3618_);
v___x_3620_ = lean_uint64_dec_eq(v___x_3619_, v___x_3491_);
if (v___x_3620_ == 0)
{
v___y_3608_ = v___y_3616_;
v___y_3609_ = v___y_3617_;
v___y_3610_ = v___x_3618_;
v___y_3611_ = v___x_3619_;
goto v___jp_3607_;
}
else
{
v___y_3608_ = v___y_3616_;
v___y_3609_ = v___y_3617_;
v___y_3610_ = v___x_3618_;
v___y_3611_ = v___y_3616_;
goto v___jp_3607_;
}
}
v___jp_3621_:
{
uint64_t v___x_3626_; uint8_t v___x_3627_; 
v___x_3626_ = lean_uint64_shift_right(v___y_3623_, v___y_3622_);
v___x_3627_ = lean_uint64_dec_eq(v___x_3626_, v___x_3491_);
if (v___x_3627_ == 0)
{
uint64_t v___x_3628_; 
v___x_3628_ = lean_uint64_add(v___y_3624_, v___y_3622_);
v___y_3616_ = v___y_3625_;
v___y_3617_ = v___x_3628_;
goto v___jp_3615_;
}
else
{
v___y_3616_ = v___y_3625_;
v___y_3617_ = v___y_3624_;
goto v___jp_3615_;
}
}
v___jp_3629_:
{
uint64_t v___x_3632_; uint64_t v___x_3633_; uint8_t v___x_3634_; 
v___x_3632_ = 8ULL;
v___x_3633_ = lean_uint64_shift_right(v___y_3630_, v___x_3632_);
v___x_3634_ = lean_uint64_dec_eq(v___x_3633_, v___x_3491_);
if (v___x_3634_ == 0)
{
v___y_3622_ = v___x_3632_;
v___y_3623_ = v___y_3630_;
v___y_3624_ = v___y_3631_;
v___y_3625_ = v___x_3633_;
goto v___jp_3621_;
}
else
{
v___y_3622_ = v___x_3632_;
v___y_3623_ = v___y_3630_;
v___y_3624_ = v___y_3631_;
v___y_3625_ = v___y_3630_;
goto v___jp_3621_;
}
}
v___jp_3635_:
{
uint64_t v___x_3640_; uint8_t v___x_3641_; 
v___x_3640_ = lean_uint64_shift_right(v___y_3638_, v___y_3637_);
v___x_3641_ = lean_uint64_dec_eq(v___x_3640_, v___x_3491_);
if (v___x_3641_ == 0)
{
uint64_t v___x_3642_; 
v___x_3642_ = lean_uint64_add(v___y_3636_, v___y_3637_);
v___y_3630_ = v___y_3639_;
v___y_3631_ = v___x_3642_;
goto v___jp_3629_;
}
else
{
v___y_3630_ = v___y_3639_;
v___y_3631_ = v___y_3636_;
goto v___jp_3629_;
}
}
v___jp_3643_:
{
uint64_t v___x_3646_; uint64_t v___x_3647_; uint8_t v___x_3648_; 
v___x_3646_ = 16ULL;
v___x_3647_ = lean_uint64_shift_right(v___y_3644_, v___x_3646_);
v___x_3648_ = lean_uint64_dec_eq(v___x_3647_, v___x_3491_);
if (v___x_3648_ == 0)
{
v___y_3636_ = v___y_3645_;
v___y_3637_ = v___x_3646_;
v___y_3638_ = v___y_3644_;
v___y_3639_ = v___x_3647_;
goto v___jp_3635_;
}
else
{
v___y_3636_ = v___y_3645_;
v___y_3637_ = v___x_3646_;
v___y_3638_ = v___y_3644_;
v___y_3639_ = v___y_3644_;
goto v___jp_3635_;
}
}
v___jp_3649_:
{
uint64_t v___x_3652_; uint8_t v___x_3653_; 
v___x_3652_ = lean_uint64_shift_right(v_product_3462_, v___y_3650_);
v___x_3653_ = lean_uint64_dec_eq(v___x_3652_, v___x_3491_);
if (v___x_3653_ == 0)
{
v___y_3644_ = v___y_3651_;
v___y_3645_ = v___y_3650_;
goto v___jp_3643_;
}
else
{
v___y_3644_ = v___y_3651_;
v___y_3645_ = v___x_3491_;
goto v___jp_3643_;
}
}
v___jp_3654_:
{
uint64_t v___x_3655_; uint64_t v___x_3656_; uint8_t v___x_3657_; 
v___x_3655_ = 32ULL;
v___x_3656_ = lean_uint64_shift_right(v_product_3462_, v___x_3655_);
v___x_3657_ = lean_uint64_dec_eq(v___x_3656_, v___x_3491_);
if (v___x_3657_ == 0)
{
v___y_3650_ = v___x_3655_;
v___y_3651_ = v___x_3656_;
goto v___jp_3649_;
}
else
{
v___y_3650_ = v___x_3655_;
v___y_3651_ = v_product_3462_;
goto v___jp_3649_;
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_R6NormalMul_roundP___boxed(lean_object* v_sign_3669_, lean_object* v_product_3670_, lean_object* v_scale_3671_){
_start:
{
uint8_t v_sign_boxed_3672_; uint64_t v_product_boxed_3673_; uint64_t v_scale_boxed_3674_; uint32_t v_res_3675_; lean_object* v_r_3676_; 
v_sign_boxed_3672_ = lean_unbox(v_sign_3669_);
v_product_boxed_3673_ = lean_unbox_uint64(v_product_3670_);
lean_dec_ref(v_product_3670_);
v_scale_boxed_3674_ = lean_unbox_uint64(v_scale_3671_);
lean_dec_ref(v_scale_3671_);
v_res_3675_ = lp_competition_Submission_R6NormalMul_roundP(v_sign_boxed_3672_, v_product_boxed_3673_, v_scale_boxed_3674_);
v_r_3676_ = lean_box_uint32(v_res_3675_);
return v_r_3676_;
}
}
LEAN_EXPORT uint32_t lp_competition_Submission_R6NormalMul_core(uint32_t v_xBits_3677_, uint32_t v_yBits_3678_){
_start:
{
uint32_t v___y_3680_; uint32_t v___y_3684_; uint32_t v___y_3685_; uint32_t v___y_3686_; uint32_t v___y_3690_; uint64_t v___y_3691_; uint8_t v___y_3692_; uint64_t v___y_3693_; uint32_t v___x_3704_; uint32_t v___x_3705_; uint32_t v___x_3706_; uint32_t v___y_3708_; uint32_t v___y_3709_; uint32_t v___y_3710_; uint32_t v___y_3711_; uint32_t v___y_3718_; uint8_t v___y_3719_; uint32_t v___y_3720_; uint32_t v___y_3721_; uint64_t v___y_3725_; uint32_t v___y_3726_; uint8_t v___y_3727_; uint64_t v___y_3728_; uint64_t v___y_3729_; uint8_t v___y_3739_; uint64_t v___y_3740_; uint32_t v___y_3741_; uint64_t v___y_3742_; uint8_t v___y_3743_; uint64_t v___y_3744_; uint64_t v___y_3751_; uint64_t v___y_3752_; uint32_t v___y_3753_; uint8_t v___y_3754_; uint64_t v___y_3755_; uint32_t v___y_3761_; uint64_t v___y_3762_; uint8_t v___y_3763_; uint64_t v___y_3764_; uint64_t v___y_3765_; uint64_t v___y_3766_; uint64_t v___y_3821_; uint32_t v___y_3822_; uint64_t v___y_3823_; uint8_t v___y_3824_; uint64_t v___y_3825_; uint64_t v___y_3826_; uint64_t v___y_3827_; uint64_t v___y_3833_; uint64_t v___y_3834_; uint64_t v___y_3835_; uint64_t v___y_3836_; uint32_t v___y_3837_; uint8_t v___y_3838_; uint64_t v___y_3839_; uint64_t v___y_3840_; uint64_t v___y_3841_; uint64_t v___y_3846_; uint32_t v___y_3847_; uint64_t v___y_3848_; uint8_t v___y_3849_; uint64_t v___y_3850_; uint64_t v___y_3851_; uint64_t v___y_3852_; uint64_t v___y_3857_; uint64_t v___y_3858_; uint32_t v___y_3859_; uint8_t v___y_3860_; uint64_t v___y_3861_; uint64_t v___y_3862_; uint64_t v___y_3863_; uint64_t v___y_3864_; uint64_t v___y_3865_; uint32_t v___y_3870_; uint64_t v___y_3871_; uint8_t v___y_3872_; uint64_t v___y_3873_; uint64_t v___y_3874_; uint64_t v___y_3875_; uint64_t v___y_3876_; uint64_t v___y_3881_; uint64_t v___y_3882_; uint64_t v___y_3883_; uint64_t v___y_3884_; uint32_t v___y_3885_; uint8_t v___y_3886_; uint64_t v___y_3887_; uint64_t v___y_3888_; uint64_t v___y_3889_; uint64_t v___y_3894_; uint32_t v___y_3895_; uint64_t v___y_3896_; uint8_t v___y_3897_; uint64_t v___y_3898_; uint64_t v___y_3899_; uint64_t v___y_3900_; uint64_t v___y_3905_; uint64_t v___y_3906_; uint64_t v___y_3907_; uint64_t v___y_3908_; uint32_t v___y_3909_; uint8_t v___y_3910_; uint64_t v___y_3911_; uint64_t v___y_3912_; uint64_t v___y_3913_; uint32_t v___y_3918_; uint64_t v___y_3919_; uint64_t v___y_3920_; uint8_t v___y_3921_; uint64_t v___y_3922_; uint64_t v___y_3923_; uint64_t v___y_3924_; uint64_t v___y_3929_; uint64_t v___y_3930_; uint32_t v___y_3931_; uint8_t v___y_3932_; uint64_t v___y_3933_; uint64_t v___y_3934_; uint64_t v___y_3935_; uint32_t v___y_3939_; uint64_t v___y_3940_; uint8_t v___y_3941_; uint64_t v___y_3942_; uint64_t v___y_3943_; uint64_t v___y_3948_; uint32_t v___y_3949_; uint8_t v___y_3950_; uint64_t v___y_3951_; uint64_t v___y_3952_; uint64_t v___y_3953_; uint32_t v_xExponent_3968_; uint32_t v___x_3969_; uint32_t v_yExponent_3970_; uint32_t v___y_3972_; uint8_t v___y_3973_; uint64_t v___y_3974_; uint64_t v___y_3975_; uint64_t v___y_3976_; uint32_t v___y_3983_; uint8_t v___y_3984_; uint64_t v___y_3985_; uint64_t v___y_3986_; uint32_t v___y_3993_; uint32_t v___y_3994_; uint8_t v___y_3995_; uint64_t v___y_3996_; uint8_t v___y_4004_; uint8_t v___y_4019_; uint8_t v___y_4020_; uint8_t v___y_4022_; uint32_t v___x_4029_; uint32_t v___x_4030_; uint32_t v___x_4031_; uint8_t v___x_4032_; 
v___x_3704_ = 23;
v___x_3705_ = lean_uint32_shift_right(v_xBits_3677_, v___x_3704_);
v___x_3706_ = 255;
v_xExponent_3968_ = lean_uint32_land(v___x_3705_, v___x_3706_);
v___x_3969_ = lean_uint32_shift_right(v_yBits_3678_, v___x_3704_);
v_yExponent_3970_ = lean_uint32_land(v___x_3969_, v___x_3706_);
v___x_4029_ = 2147483648;
v___x_4030_ = lean_uint32_land(v_xBits_3677_, v___x_4029_);
v___x_4031_ = 0;
v___x_4032_ = lean_uint32_dec_eq(v___x_4030_, v___x_4031_);
if (v___x_4032_ == 0)
{
uint8_t v___x_4033_; 
v___x_4033_ = 1;
v___y_4022_ = v___x_4033_;
goto v___jp_4021_;
}
else
{
uint8_t v___x_4034_; 
v___x_4034_ = 0;
v___y_4022_ = v___x_4034_;
goto v___jp_4021_;
}
v___jp_3679_:
{
uint32_t v___x_3681_; uint32_t v___x_3682_; 
v___x_3681_ = 8388608;
v___x_3682_ = lean_uint32_lor(v___y_3680_, v___x_3681_);
return v___x_3682_;
}
v___jp_3683_:
{
uint32_t v___x_3687_; uint32_t v___x_3688_; 
v___x_3687_ = lean_uint32_land(v___y_3684_, v___y_3685_);
v___x_3688_ = lean_uint32_lor(v___y_3686_, v___x_3687_);
return v___x_3688_;
}
v___jp_3689_:
{
uint8_t v___x_3694_; 
v___x_3694_ = lean_uint64_dec_eq(v___y_3693_, v___y_3691_);
if (v___x_3694_ == 0)
{
uint64_t v___x_3695_; uint8_t v___x_3696_; 
v___x_3695_ = 8388608ULL;
v___x_3696_ = lean_uint64_dec_eq(v___y_3693_, v___x_3695_);
if (v___x_3696_ == 0)
{
uint32_t v___x_3697_; 
v___x_3697_ = lean_uint64_to_uint32(v___y_3693_);
if (v___y_3692_ == 0)
{
uint32_t v___x_3698_; 
v___x_3698_ = 0;
v___y_3684_ = v___x_3697_;
v___y_3685_ = v___y_3690_;
v___y_3686_ = v___x_3698_;
goto v___jp_3683_;
}
else
{
uint32_t v___x_3699_; 
v___x_3699_ = 2147483648;
v___y_3684_ = v___x_3697_;
v___y_3685_ = v___y_3690_;
v___y_3686_ = v___x_3699_;
goto v___jp_3683_;
}
}
else
{
if (v___y_3692_ == 0)
{
uint32_t v___x_3700_; 
v___x_3700_ = 0;
v___y_3680_ = v___x_3700_;
goto v___jp_3679_;
}
else
{
uint32_t v___x_3701_; 
v___x_3701_ = 2147483648;
v___y_3680_ = v___x_3701_;
goto v___jp_3679_;
}
}
}
else
{
if (v___y_3692_ == 0)
{
uint32_t v___x_3702_; 
v___x_3702_ = 0;
return v___x_3702_;
}
else
{
uint32_t v___x_3703_; 
v___x_3703_ = 2147483648;
return v___x_3703_;
}
}
}
v___jp_3707_:
{
uint32_t v___x_3712_; uint32_t v___x_3713_; uint32_t v___x_3714_; uint32_t v___x_3715_; uint32_t v___x_3716_; 
v___x_3712_ = lean_uint32_land(v___y_3709_, v___x_3706_);
v___x_3713_ = lean_uint32_shift_left(v___x_3712_, v___x_3704_);
v___x_3714_ = lean_uint32_lor(v___y_3711_, v___x_3713_);
v___x_3715_ = lean_uint32_land(v___y_3710_, v___y_3708_);
v___x_3716_ = lean_uint32_lor(v___x_3714_, v___x_3715_);
return v___x_3716_;
}
v___jp_3717_:
{
if (v___y_3719_ == 0)
{
uint32_t v___x_3722_; 
v___x_3722_ = 0;
v___y_3708_ = v___y_3718_;
v___y_3709_ = v___y_3720_;
v___y_3710_ = v___y_3721_;
v___y_3711_ = v___x_3722_;
goto v___jp_3707_;
}
else
{
uint32_t v___x_3723_; 
v___x_3723_ = 2147483648;
v___y_3708_ = v___y_3718_;
v___y_3709_ = v___y_3720_;
v___y_3710_ = v___y_3721_;
v___y_3711_ = v___x_3723_;
goto v___jp_3707_;
}
}
v___jp_3724_:
{
uint64_t v___x_3730_; uint64_t v_encodedExponent_3731_; uint32_t v___x_3732_; uint64_t v___x_3733_; uint8_t v___x_3734_; 
v___x_3730_ = 171ULL;
v_encodedExponent_3731_ = lean_uint64_sub(v___y_3728_, v___x_3730_);
v___x_3732_ = lean_uint64_to_uint32(v_encodedExponent_3731_);
v___x_3733_ = 8388608ULL;
v___x_3734_ = lean_uint64_dec_lt(v___y_3729_, v___x_3733_);
if (v___x_3734_ == 0)
{
uint64_t v___x_3735_; uint32_t v___x_3736_; 
v___x_3735_ = lean_uint64_sub(v___y_3729_, v___x_3733_);
v___x_3736_ = lean_uint64_to_uint32(v___x_3735_);
v___y_3718_ = v___y_3726_;
v___y_3719_ = v___y_3727_;
v___y_3720_ = v___x_3732_;
v___y_3721_ = v___x_3736_;
goto v___jp_3717_;
}
else
{
uint32_t v___x_3737_; 
v___x_3737_ = lean_uint64_to_uint32(v___y_3725_);
v___y_3718_ = v___y_3726_;
v___y_3719_ = v___y_3727_;
v___y_3720_ = v___x_3732_;
v___y_3721_ = v___x_3737_;
goto v___jp_3717_;
}
}
v___jp_3738_:
{
uint64_t v___x_3745_; uint8_t v___x_3746_; 
v___x_3745_ = 425ULL;
v___x_3746_ = lean_uint64_dec_lt(v___x_3745_, v___y_3744_);
if (v___x_3746_ == 0)
{
if (v___y_3739_ == 0)
{
v___y_3725_ = v___y_3742_;
v___y_3726_ = v___y_3741_;
v___y_3727_ = v___y_3743_;
v___y_3728_ = v___y_3744_;
v___y_3729_ = v___y_3740_;
goto v___jp_3724_;
}
else
{
uint64_t v___x_3747_; 
v___x_3747_ = 8388608ULL;
v___y_3725_ = v___y_3742_;
v___y_3726_ = v___y_3741_;
v___y_3727_ = v___y_3743_;
v___y_3728_ = v___y_3744_;
v___y_3729_ = v___x_3747_;
goto v___jp_3724_;
}
}
else
{
if (v___y_3743_ == 0)
{
uint32_t v___x_3748_; 
v___x_3748_ = 2139095040;
return v___x_3748_;
}
else
{
uint32_t v___x_3749_; 
v___x_3749_ = 4286578688;
return v___x_3749_;
}
}
}
v___jp_3750_:
{
uint64_t v___x_3756_; uint8_t v_carry_3757_; 
v___x_3756_ = 16777216ULL;
v_carry_3757_ = lean_uint64_dec_eq(v___y_3755_, v___x_3756_);
if (v_carry_3757_ == 0)
{
v___y_3739_ = v_carry_3757_;
v___y_3740_ = v___y_3755_;
v___y_3741_ = v___y_3753_;
v___y_3742_ = v___y_3752_;
v___y_3743_ = v___y_3754_;
v___y_3744_ = v___y_3751_;
goto v___jp_3738_;
}
else
{
uint64_t v___x_3758_; uint64_t v___x_3759_; 
v___x_3758_ = 1ULL;
v___x_3759_ = lean_uint64_add(v___y_3751_, v___x_3758_);
v___y_3739_ = v_carry_3757_;
v___y_3740_ = v___y_3755_;
v___y_3741_ = v___y_3753_;
v___y_3742_ = v___y_3752_;
v___y_3743_ = v___y_3754_;
v___y_3744_ = v___x_3759_;
goto v___jp_3738_;
}
}
v___jp_3760_:
{
uint64_t v_position_3767_; uint64_t v___x_3768_; uint8_t v___x_3769_; 
v_position_3767_ = lean_uint64_add(v___y_3766_, v___y_3765_);
v___x_3768_ = 172ULL;
v___x_3769_ = lean_uint64_dec_lt(v_position_3767_, v___x_3768_);
if (v___x_3769_ == 0)
{
uint64_t v___x_3770_; uint8_t v___x_3771_; 
v___x_3770_ = 23ULL;
v___x_3771_ = lean_uint64_dec_lt(v___y_3766_, v___x_3770_);
if (v___x_3771_ == 0)
{
uint64_t v___x_3772_; uint8_t v___x_3773_; 
v___x_3772_ = lean_uint64_sub(v___y_3766_, v___x_3770_);
v___x_3773_ = lean_uint64_dec_eq(v___x_3772_, v___y_3762_);
if (v___x_3773_ == 0)
{
uint64_t v___x_3774_; uint8_t v___x_3775_; 
v___x_3774_ = 64ULL;
v___x_3775_ = lean_uint64_dec_lt(v___x_3772_, v___x_3774_);
if (v___x_3775_ == 0)
{
uint8_t v___x_3776_; 
v___x_3776_ = lean_uint64_dec_eq(v___x_3772_, v___x_3774_);
if (v___x_3776_ == 0)
{
v___y_3751_ = v_position_3767_;
v___y_3752_ = v___y_3762_;
v___y_3753_ = v___y_3761_;
v___y_3754_ = v___y_3763_;
v___y_3755_ = v___y_3762_;
goto v___jp_3750_;
}
else
{
uint64_t v___x_3777_; uint8_t v___x_3778_; 
v___x_3777_ = 9223372036854775808ULL;
v___x_3778_ = lean_uint64_dec_lt(v___x_3777_, v___y_3764_);
if (v___x_3778_ == 0)
{
v___y_3751_ = v_position_3767_;
v___y_3752_ = v___y_3762_;
v___y_3753_ = v___y_3761_;
v___y_3754_ = v___y_3763_;
v___y_3755_ = v___y_3762_;
goto v___jp_3750_;
}
else
{
uint64_t v___x_3779_; 
v___x_3779_ = 1ULL;
v___y_3751_ = v_position_3767_;
v___y_3752_ = v___y_3762_;
v___y_3753_ = v___y_3761_;
v___y_3754_ = v___y_3763_;
v___y_3755_ = v___x_3779_;
goto v___jp_3750_;
}
}
}
else
{
uint64_t v_quotient_3780_; uint64_t v___x_3781_; uint64_t v___x_3782_; uint64_t v___x_3783_; uint64_t v_remainder_3784_; uint64_t v___x_3785_; uint64_t v_half_3786_; uint8_t v___x_3787_; 
v_quotient_3780_ = lean_uint64_shift_right(v___y_3764_, v___x_3772_);
v___x_3781_ = 1ULL;
v___x_3782_ = lean_uint64_shift_left(v___x_3781_, v___x_3772_);
v___x_3783_ = lean_uint64_sub(v___x_3782_, v___x_3781_);
v_remainder_3784_ = lean_uint64_land(v___y_3764_, v___x_3783_);
v___x_3785_ = lean_uint64_sub(v___x_3772_, v___x_3781_);
v_half_3786_ = lean_uint64_shift_left(v___x_3781_, v___x_3785_);
v___x_3787_ = lean_uint64_dec_lt(v_remainder_3784_, v_half_3786_);
if (v___x_3787_ == 0)
{
uint8_t v___x_3788_; 
v___x_3788_ = lean_uint64_dec_lt(v_half_3786_, v_remainder_3784_);
if (v___x_3788_ == 0)
{
uint64_t v___x_3789_; uint8_t v___x_3790_; 
v___x_3789_ = lean_uint64_land(v_quotient_3780_, v___x_3781_);
v___x_3790_ = lean_uint64_dec_eq(v___x_3789_, v___y_3762_);
if (v___x_3790_ == 0)
{
uint64_t v___x_3791_; 
v___x_3791_ = lean_uint64_add(v_quotient_3780_, v___x_3781_);
v___y_3751_ = v_position_3767_;
v___y_3752_ = v___y_3762_;
v___y_3753_ = v___y_3761_;
v___y_3754_ = v___y_3763_;
v___y_3755_ = v___x_3791_;
goto v___jp_3750_;
}
else
{
v___y_3751_ = v_position_3767_;
v___y_3752_ = v___y_3762_;
v___y_3753_ = v___y_3761_;
v___y_3754_ = v___y_3763_;
v___y_3755_ = v_quotient_3780_;
goto v___jp_3750_;
}
}
else
{
uint64_t v___x_3792_; 
v___x_3792_ = lean_uint64_add(v_quotient_3780_, v___x_3781_);
v___y_3751_ = v_position_3767_;
v___y_3752_ = v___y_3762_;
v___y_3753_ = v___y_3761_;
v___y_3754_ = v___y_3763_;
v___y_3755_ = v___x_3792_;
goto v___jp_3750_;
}
}
else
{
v___y_3751_ = v_position_3767_;
v___y_3752_ = v___y_3762_;
v___y_3753_ = v___y_3761_;
v___y_3754_ = v___y_3763_;
v___y_3755_ = v_quotient_3780_;
goto v___jp_3750_;
}
}
}
else
{
v___y_3751_ = v_position_3767_;
v___y_3752_ = v___y_3762_;
v___y_3753_ = v___y_3761_;
v___y_3754_ = v___y_3763_;
v___y_3755_ = v___y_3764_;
goto v___jp_3750_;
}
}
else
{
uint64_t v___x_3793_; uint64_t v___x_3794_; 
v___x_3793_ = lean_uint64_sub(v___x_3770_, v___y_3766_);
v___x_3794_ = lean_uint64_shift_left(v___y_3764_, v___x_3793_);
v___y_3751_ = v_position_3767_;
v___y_3752_ = v___y_3762_;
v___y_3753_ = v___y_3761_;
v___y_3754_ = v___y_3763_;
v___y_3755_ = v___x_3794_;
goto v___jp_3750_;
}
}
else
{
uint64_t v___x_3795_; uint8_t v___x_3796_; 
v___x_3795_ = 149ULL;
v___x_3796_ = lean_uint64_dec_lt(v___y_3765_, v___x_3795_);
if (v___x_3796_ == 0)
{
uint64_t v___x_3797_; uint64_t v___x_3798_; 
v___x_3797_ = lean_uint64_sub(v___y_3765_, v___x_3795_);
v___x_3798_ = lean_uint64_shift_left(v___y_3764_, v___x_3797_);
v___y_3690_ = v___y_3761_;
v___y_3691_ = v___y_3762_;
v___y_3692_ = v___y_3763_;
v___y_3693_ = v___x_3798_;
goto v___jp_3689_;
}
else
{
uint64_t v___x_3799_; uint8_t v___x_3800_; 
v___x_3799_ = lean_uint64_sub(v___x_3795_, v___y_3765_);
v___x_3800_ = lean_uint64_dec_eq(v___x_3799_, v___y_3762_);
if (v___x_3800_ == 0)
{
uint64_t v___x_3801_; uint8_t v___x_3802_; 
v___x_3801_ = 64ULL;
v___x_3802_ = lean_uint64_dec_lt(v___x_3799_, v___x_3801_);
if (v___x_3802_ == 0)
{
uint8_t v___x_3803_; 
v___x_3803_ = lean_uint64_dec_eq(v___x_3799_, v___x_3801_);
if (v___x_3803_ == 0)
{
v___y_3690_ = v___y_3761_;
v___y_3691_ = v___y_3762_;
v___y_3692_ = v___y_3763_;
v___y_3693_ = v___y_3762_;
goto v___jp_3689_;
}
else
{
uint64_t v___x_3804_; uint8_t v___x_3805_; 
v___x_3804_ = 9223372036854775808ULL;
v___x_3805_ = lean_uint64_dec_lt(v___x_3804_, v___y_3764_);
if (v___x_3805_ == 0)
{
v___y_3690_ = v___y_3761_;
v___y_3691_ = v___y_3762_;
v___y_3692_ = v___y_3763_;
v___y_3693_ = v___y_3762_;
goto v___jp_3689_;
}
else
{
uint64_t v___x_3806_; 
v___x_3806_ = 1ULL;
v___y_3690_ = v___y_3761_;
v___y_3691_ = v___y_3762_;
v___y_3692_ = v___y_3763_;
v___y_3693_ = v___x_3806_;
goto v___jp_3689_;
}
}
}
else
{
uint64_t v_quotient_3807_; uint64_t v___x_3808_; uint64_t v___x_3809_; uint64_t v___x_3810_; uint64_t v_remainder_3811_; uint64_t v___x_3812_; uint64_t v_half_3813_; uint8_t v___x_3814_; 
v_quotient_3807_ = lean_uint64_shift_right(v___y_3764_, v___x_3799_);
v___x_3808_ = 1ULL;
v___x_3809_ = lean_uint64_shift_left(v___x_3808_, v___x_3799_);
v___x_3810_ = lean_uint64_sub(v___x_3809_, v___x_3808_);
v_remainder_3811_ = lean_uint64_land(v___y_3764_, v___x_3810_);
v___x_3812_ = lean_uint64_sub(v___x_3799_, v___x_3808_);
v_half_3813_ = lean_uint64_shift_left(v___x_3808_, v___x_3812_);
v___x_3814_ = lean_uint64_dec_lt(v_remainder_3811_, v_half_3813_);
if (v___x_3814_ == 0)
{
uint8_t v___x_3815_; 
v___x_3815_ = lean_uint64_dec_lt(v_half_3813_, v_remainder_3811_);
if (v___x_3815_ == 0)
{
uint64_t v___x_3816_; uint8_t v___x_3817_; 
v___x_3816_ = lean_uint64_land(v_quotient_3807_, v___x_3808_);
v___x_3817_ = lean_uint64_dec_eq(v___x_3816_, v___y_3762_);
if (v___x_3817_ == 0)
{
uint64_t v___x_3818_; 
v___x_3818_ = lean_uint64_add(v_quotient_3807_, v___x_3808_);
v___y_3690_ = v___y_3761_;
v___y_3691_ = v___y_3762_;
v___y_3692_ = v___y_3763_;
v___y_3693_ = v___x_3818_;
goto v___jp_3689_;
}
else
{
v___y_3690_ = v___y_3761_;
v___y_3691_ = v___y_3762_;
v___y_3692_ = v___y_3763_;
v___y_3693_ = v_quotient_3807_;
goto v___jp_3689_;
}
}
else
{
uint64_t v___x_3819_; 
v___x_3819_ = lean_uint64_add(v_quotient_3807_, v___x_3808_);
v___y_3690_ = v___y_3761_;
v___y_3691_ = v___y_3762_;
v___y_3692_ = v___y_3763_;
v___y_3693_ = v___x_3819_;
goto v___jp_3689_;
}
}
else
{
v___y_3690_ = v___y_3761_;
v___y_3691_ = v___y_3762_;
v___y_3692_ = v___y_3763_;
v___y_3693_ = v_quotient_3807_;
goto v___jp_3689_;
}
}
}
else
{
v___y_3690_ = v___y_3761_;
v___y_3691_ = v___y_3762_;
v___y_3692_ = v___y_3763_;
v___y_3693_ = v___y_3764_;
goto v___jp_3689_;
}
}
}
}
v___jp_3820_:
{
uint64_t v___x_3828_; uint64_t v___x_3829_; uint8_t v___x_3830_; 
v___x_3828_ = 1ULL;
v___x_3829_ = lean_uint64_shift_right(v___y_3821_, v___x_3828_);
v___x_3830_ = lean_uint64_dec_eq(v___x_3829_, v___y_3823_);
if (v___x_3830_ == 0)
{
uint64_t v___x_3831_; 
v___x_3831_ = lean_uint64_add(v___y_3827_, v___x_3828_);
v___y_3761_ = v___y_3822_;
v___y_3762_ = v___y_3823_;
v___y_3763_ = v___y_3824_;
v___y_3764_ = v___y_3825_;
v___y_3765_ = v___y_3826_;
v___y_3766_ = v___x_3831_;
goto v___jp_3760_;
}
else
{
v___y_3761_ = v___y_3822_;
v___y_3762_ = v___y_3823_;
v___y_3763_ = v___y_3824_;
v___y_3764_ = v___y_3825_;
v___y_3765_ = v___y_3826_;
v___y_3766_ = v___y_3827_;
goto v___jp_3760_;
}
}
v___jp_3832_:
{
uint64_t v___x_3842_; uint8_t v___x_3843_; 
v___x_3842_ = lean_uint64_shift_right(v___y_3835_, v___y_3834_);
v___x_3843_ = lean_uint64_dec_eq(v___x_3842_, v___y_3836_);
if (v___x_3843_ == 0)
{
uint64_t v___x_3844_; 
v___x_3844_ = lean_uint64_add(v___y_3833_, v___y_3834_);
v___y_3821_ = v___y_3841_;
v___y_3822_ = v___y_3837_;
v___y_3823_ = v___y_3836_;
v___y_3824_ = v___y_3838_;
v___y_3825_ = v___y_3839_;
v___y_3826_ = v___y_3840_;
v___y_3827_ = v___x_3844_;
goto v___jp_3820_;
}
else
{
v___y_3821_ = v___y_3841_;
v___y_3822_ = v___y_3837_;
v___y_3823_ = v___y_3836_;
v___y_3824_ = v___y_3838_;
v___y_3825_ = v___y_3839_;
v___y_3826_ = v___y_3840_;
v___y_3827_ = v___y_3833_;
goto v___jp_3820_;
}
}
v___jp_3845_:
{
uint64_t v___x_3853_; uint64_t v___x_3854_; uint8_t v___x_3855_; 
v___x_3853_ = 2ULL;
v___x_3854_ = lean_uint64_shift_right(v___y_3846_, v___x_3853_);
v___x_3855_ = lean_uint64_dec_eq(v___x_3854_, v___y_3848_);
if (v___x_3855_ == 0)
{
v___y_3833_ = v___y_3852_;
v___y_3834_ = v___x_3853_;
v___y_3835_ = v___y_3846_;
v___y_3836_ = v___y_3848_;
v___y_3837_ = v___y_3847_;
v___y_3838_ = v___y_3849_;
v___y_3839_ = v___y_3850_;
v___y_3840_ = v___y_3851_;
v___y_3841_ = v___x_3854_;
goto v___jp_3832_;
}
else
{
v___y_3833_ = v___y_3852_;
v___y_3834_ = v___x_3853_;
v___y_3835_ = v___y_3846_;
v___y_3836_ = v___y_3848_;
v___y_3837_ = v___y_3847_;
v___y_3838_ = v___y_3849_;
v___y_3839_ = v___y_3850_;
v___y_3840_ = v___y_3851_;
v___y_3841_ = v___y_3846_;
goto v___jp_3832_;
}
}
v___jp_3856_:
{
uint64_t v___x_3866_; uint8_t v___x_3867_; 
v___x_3866_ = lean_uint64_shift_right(v___y_3864_, v___y_3862_);
v___x_3867_ = lean_uint64_dec_eq(v___x_3866_, v___y_3858_);
if (v___x_3867_ == 0)
{
uint64_t v___x_3868_; 
v___x_3868_ = lean_uint64_add(v___y_3857_, v___y_3862_);
v___y_3846_ = v___y_3865_;
v___y_3847_ = v___y_3859_;
v___y_3848_ = v___y_3858_;
v___y_3849_ = v___y_3860_;
v___y_3850_ = v___y_3861_;
v___y_3851_ = v___y_3863_;
v___y_3852_ = v___x_3868_;
goto v___jp_3845_;
}
else
{
v___y_3846_ = v___y_3865_;
v___y_3847_ = v___y_3859_;
v___y_3848_ = v___y_3858_;
v___y_3849_ = v___y_3860_;
v___y_3850_ = v___y_3861_;
v___y_3851_ = v___y_3863_;
v___y_3852_ = v___y_3857_;
goto v___jp_3845_;
}
}
v___jp_3869_:
{
uint64_t v___x_3877_; uint64_t v___x_3878_; uint8_t v___x_3879_; 
v___x_3877_ = 4ULL;
v___x_3878_ = lean_uint64_shift_right(v___y_3875_, v___x_3877_);
v___x_3879_ = lean_uint64_dec_eq(v___x_3878_, v___y_3871_);
if (v___x_3879_ == 0)
{
v___y_3857_ = v___y_3876_;
v___y_3858_ = v___y_3871_;
v___y_3859_ = v___y_3870_;
v___y_3860_ = v___y_3872_;
v___y_3861_ = v___y_3873_;
v___y_3862_ = v___x_3877_;
v___y_3863_ = v___y_3874_;
v___y_3864_ = v___y_3875_;
v___y_3865_ = v___x_3878_;
goto v___jp_3856_;
}
else
{
v___y_3857_ = v___y_3876_;
v___y_3858_ = v___y_3871_;
v___y_3859_ = v___y_3870_;
v___y_3860_ = v___y_3872_;
v___y_3861_ = v___y_3873_;
v___y_3862_ = v___x_3877_;
v___y_3863_ = v___y_3874_;
v___y_3864_ = v___y_3875_;
v___y_3865_ = v___y_3875_;
goto v___jp_3856_;
}
}
v___jp_3880_:
{
uint64_t v___x_3890_; uint8_t v___x_3891_; 
v___x_3890_ = lean_uint64_shift_right(v___y_3883_, v___y_3882_);
v___x_3891_ = lean_uint64_dec_eq(v___x_3890_, v___y_3884_);
if (v___x_3891_ == 0)
{
uint64_t v___x_3892_; 
v___x_3892_ = lean_uint64_add(v___y_3881_, v___y_3882_);
v___y_3870_ = v___y_3885_;
v___y_3871_ = v___y_3884_;
v___y_3872_ = v___y_3886_;
v___y_3873_ = v___y_3887_;
v___y_3874_ = v___y_3888_;
v___y_3875_ = v___y_3889_;
v___y_3876_ = v___x_3892_;
goto v___jp_3869_;
}
else
{
v___y_3870_ = v___y_3885_;
v___y_3871_ = v___y_3884_;
v___y_3872_ = v___y_3886_;
v___y_3873_ = v___y_3887_;
v___y_3874_ = v___y_3888_;
v___y_3875_ = v___y_3889_;
v___y_3876_ = v___y_3881_;
goto v___jp_3869_;
}
}
v___jp_3893_:
{
uint64_t v___x_3901_; uint64_t v___x_3902_; uint8_t v___x_3903_; 
v___x_3901_ = 8ULL;
v___x_3902_ = lean_uint64_shift_right(v___y_3894_, v___x_3901_);
v___x_3903_ = lean_uint64_dec_eq(v___x_3902_, v___y_3896_);
if (v___x_3903_ == 0)
{
v___y_3881_ = v___y_3900_;
v___y_3882_ = v___x_3901_;
v___y_3883_ = v___y_3894_;
v___y_3884_ = v___y_3896_;
v___y_3885_ = v___y_3895_;
v___y_3886_ = v___y_3897_;
v___y_3887_ = v___y_3898_;
v___y_3888_ = v___y_3899_;
v___y_3889_ = v___x_3902_;
goto v___jp_3880_;
}
else
{
v___y_3881_ = v___y_3900_;
v___y_3882_ = v___x_3901_;
v___y_3883_ = v___y_3894_;
v___y_3884_ = v___y_3896_;
v___y_3885_ = v___y_3895_;
v___y_3886_ = v___y_3897_;
v___y_3887_ = v___y_3898_;
v___y_3888_ = v___y_3899_;
v___y_3889_ = v___y_3894_;
goto v___jp_3880_;
}
}
v___jp_3904_:
{
uint64_t v___x_3914_; uint8_t v___x_3915_; 
v___x_3914_ = lean_uint64_shift_right(v___y_3907_, v___y_3905_);
v___x_3915_ = lean_uint64_dec_eq(v___x_3914_, v___y_3908_);
if (v___x_3915_ == 0)
{
uint64_t v___x_3916_; 
v___x_3916_ = lean_uint64_add(v___y_3906_, v___y_3905_);
v___y_3894_ = v___y_3913_;
v___y_3895_ = v___y_3909_;
v___y_3896_ = v___y_3908_;
v___y_3897_ = v___y_3910_;
v___y_3898_ = v___y_3911_;
v___y_3899_ = v___y_3912_;
v___y_3900_ = v___x_3916_;
goto v___jp_3893_;
}
else
{
v___y_3894_ = v___y_3913_;
v___y_3895_ = v___y_3909_;
v___y_3896_ = v___y_3908_;
v___y_3897_ = v___y_3910_;
v___y_3898_ = v___y_3911_;
v___y_3899_ = v___y_3912_;
v___y_3900_ = v___y_3906_;
goto v___jp_3893_;
}
}
v___jp_3917_:
{
uint64_t v___x_3925_; uint64_t v___x_3926_; uint8_t v___x_3927_; 
v___x_3925_ = 16ULL;
v___x_3926_ = lean_uint64_shift_right(v___y_3920_, v___x_3925_);
v___x_3927_ = lean_uint64_dec_eq(v___x_3926_, v___y_3919_);
if (v___x_3927_ == 0)
{
v___y_3905_ = v___x_3925_;
v___y_3906_ = v___y_3924_;
v___y_3907_ = v___y_3920_;
v___y_3908_ = v___y_3919_;
v___y_3909_ = v___y_3918_;
v___y_3910_ = v___y_3921_;
v___y_3911_ = v___y_3922_;
v___y_3912_ = v___y_3923_;
v___y_3913_ = v___x_3926_;
goto v___jp_3904_;
}
else
{
v___y_3905_ = v___x_3925_;
v___y_3906_ = v___y_3924_;
v___y_3907_ = v___y_3920_;
v___y_3908_ = v___y_3919_;
v___y_3909_ = v___y_3918_;
v___y_3910_ = v___y_3921_;
v___y_3911_ = v___y_3922_;
v___y_3912_ = v___y_3923_;
v___y_3913_ = v___y_3920_;
goto v___jp_3904_;
}
}
v___jp_3928_:
{
uint64_t v___x_3936_; uint8_t v___x_3937_; 
v___x_3936_ = lean_uint64_shift_right(v___y_3933_, v___y_3929_);
v___x_3937_ = lean_uint64_dec_eq(v___x_3936_, v___y_3930_);
if (v___x_3937_ == 0)
{
v___y_3918_ = v___y_3931_;
v___y_3919_ = v___y_3930_;
v___y_3920_ = v___y_3935_;
v___y_3921_ = v___y_3932_;
v___y_3922_ = v___y_3933_;
v___y_3923_ = v___y_3934_;
v___y_3924_ = v___y_3929_;
goto v___jp_3917_;
}
else
{
v___y_3918_ = v___y_3931_;
v___y_3919_ = v___y_3930_;
v___y_3920_ = v___y_3935_;
v___y_3921_ = v___y_3932_;
v___y_3922_ = v___y_3933_;
v___y_3923_ = v___y_3934_;
v___y_3924_ = v___y_3930_;
goto v___jp_3917_;
}
}
v___jp_3938_:
{
uint64_t v___x_3944_; uint64_t v___x_3945_; uint8_t v___x_3946_; 
v___x_3944_ = 32ULL;
v___x_3945_ = lean_uint64_shift_right(v___y_3942_, v___x_3944_);
v___x_3946_ = lean_uint64_dec_eq(v___x_3945_, v___y_3940_);
if (v___x_3946_ == 0)
{
v___y_3929_ = v___x_3944_;
v___y_3930_ = v___y_3940_;
v___y_3931_ = v___y_3939_;
v___y_3932_ = v___y_3941_;
v___y_3933_ = v___y_3942_;
v___y_3934_ = v___y_3943_;
v___y_3935_ = v___x_3945_;
goto v___jp_3928_;
}
else
{
v___y_3929_ = v___x_3944_;
v___y_3930_ = v___y_3940_;
v___y_3931_ = v___y_3939_;
v___y_3932_ = v___y_3941_;
v___y_3933_ = v___y_3942_;
v___y_3934_ = v___y_3943_;
v___y_3935_ = v___y_3942_;
goto v___jp_3928_;
}
}
v___jp_3947_:
{
uint64_t v___x_3954_; uint64_t v___x_3955_; uint8_t v___x_3956_; 
v___x_3954_ = lean_uint64_mul(v___y_3952_, v___y_3951_);
v___x_3955_ = 0ULL;
v___x_3956_ = lean_uint64_dec_eq(v___x_3954_, v___x_3955_);
if (v___x_3956_ == 0)
{
uint64_t v___x_3957_; uint64_t v___x_3958_; uint8_t v___x_3959_; 
v___x_3957_ = lean_uint64_add(v___y_3948_, v___y_3953_);
v___x_3958_ = 70368744177664ULL;
v___x_3959_ = lean_uint64_dec_le(v___x_3958_, v___x_3954_);
if (v___x_3959_ == 0)
{
v___y_3939_ = v___y_3949_;
v___y_3940_ = v___x_3955_;
v___y_3941_ = v___y_3950_;
v___y_3942_ = v___x_3954_;
v___y_3943_ = v___x_3957_;
goto v___jp_3938_;
}
else
{
uint64_t v___x_3960_; uint8_t v___x_3961_; 
v___x_3960_ = 281474976710656ULL;
v___x_3961_ = lean_uint64_dec_lt(v___x_3954_, v___x_3960_);
if (v___x_3961_ == 0)
{
v___y_3939_ = v___y_3949_;
v___y_3940_ = v___x_3955_;
v___y_3941_ = v___y_3950_;
v___y_3942_ = v___x_3954_;
v___y_3943_ = v___x_3957_;
goto v___jp_3938_;
}
else
{
uint64_t v___x_3962_; uint8_t v___x_3963_; 
v___x_3962_ = 140737488355328ULL;
v___x_3963_ = lean_uint64_dec_lt(v___x_3954_, v___x_3962_);
if (v___x_3963_ == 0)
{
uint64_t v___x_3964_; 
v___x_3964_ = 47ULL;
v___y_3761_ = v___y_3949_;
v___y_3762_ = v___x_3955_;
v___y_3763_ = v___y_3950_;
v___y_3764_ = v___x_3954_;
v___y_3765_ = v___x_3957_;
v___y_3766_ = v___x_3964_;
goto v___jp_3760_;
}
else
{
uint64_t v___x_3965_; 
v___x_3965_ = 46ULL;
v___y_3761_ = v___y_3949_;
v___y_3762_ = v___x_3955_;
v___y_3763_ = v___y_3950_;
v___y_3764_ = v___x_3954_;
v___y_3765_ = v___x_3957_;
v___y_3766_ = v___x_3965_;
goto v___jp_3760_;
}
}
}
}
else
{
if (v___y_3950_ == 0)
{
uint32_t v___x_3966_; 
v___x_3966_ = 0;
return v___x_3966_;
}
else
{
uint32_t v___x_3967_; 
v___x_3967_ = 2147483648;
return v___x_3967_;
}
}
}
v___jp_3971_:
{
uint64_t v___x_3977_; uint64_t v___x_3978_; uint8_t v___x_3979_; 
v___x_3977_ = lean_uint32_to_uint64(v_yExponent_3970_);
v___x_3978_ = 0ULL;
v___x_3979_ = lean_uint64_dec_eq(v___x_3977_, v___x_3978_);
if (v___x_3979_ == 0)
{
uint64_t v___x_3980_; uint64_t v___x_3981_; 
v___x_3980_ = 1ULL;
v___x_3981_ = lean_uint64_sub(v___x_3977_, v___x_3980_);
v___y_3948_ = v___y_3976_;
v___y_3949_ = v___y_3972_;
v___y_3950_ = v___y_3973_;
v___y_3951_ = v___y_3974_;
v___y_3952_ = v___y_3975_;
v___y_3953_ = v___x_3981_;
goto v___jp_3947_;
}
else
{
v___y_3948_ = v___y_3976_;
v___y_3949_ = v___y_3972_;
v___y_3950_ = v___y_3973_;
v___y_3951_ = v___y_3974_;
v___y_3952_ = v___y_3975_;
v___y_3953_ = v___x_3978_;
goto v___jp_3947_;
}
}
v___jp_3982_:
{
uint64_t v___x_3987_; uint64_t v___x_3988_; uint8_t v___x_3989_; 
v___x_3987_ = lean_uint32_to_uint64(v_xExponent_3968_);
v___x_3988_ = 0ULL;
v___x_3989_ = lean_uint64_dec_eq(v___x_3987_, v___x_3988_);
if (v___x_3989_ == 0)
{
uint64_t v___x_3990_; uint64_t v___x_3991_; 
v___x_3990_ = 1ULL;
v___x_3991_ = lean_uint64_sub(v___x_3987_, v___x_3990_);
v___y_3972_ = v___y_3983_;
v___y_3973_ = v___y_3984_;
v___y_3974_ = v___y_3986_;
v___y_3975_ = v___y_3985_;
v___y_3976_ = v___x_3991_;
goto v___jp_3971_;
}
else
{
v___y_3972_ = v___y_3983_;
v___y_3973_ = v___y_3984_;
v___y_3974_ = v___y_3986_;
v___y_3975_ = v___y_3985_;
v___y_3976_ = v___x_3988_;
goto v___jp_3971_;
}
}
v___jp_3992_:
{
uint32_t v___x_3997_; uint8_t v___x_3998_; 
v___x_3997_ = 0;
v___x_3998_ = lean_uint32_dec_eq(v_yExponent_3970_, v___x_3997_);
if (v___x_3998_ == 0)
{
uint64_t v___x_3999_; uint64_t v___x_4000_; uint64_t v___x_4001_; 
v___x_3999_ = lean_uint32_to_uint64(v___y_3993_);
v___x_4000_ = 8388608ULL;
v___x_4001_ = lean_uint64_lor(v___x_3999_, v___x_4000_);
v___y_3983_ = v___y_3994_;
v___y_3984_ = v___y_3995_;
v___y_3985_ = v___y_3996_;
v___y_3986_ = v___x_4001_;
goto v___jp_3982_;
}
else
{
uint64_t v___x_4002_; 
v___x_4002_ = lean_uint32_to_uint64(v___y_3993_);
v___y_3983_ = v___y_3994_;
v___y_3984_ = v___y_3995_;
v___y_3985_ = v___y_3996_;
v___y_3986_ = v___x_4002_;
goto v___jp_3982_;
}
}
v___jp_4003_:
{
uint32_t v___x_4005_; uint32_t v_xFraction_4006_; uint32_t v_yFraction_4007_; uint32_t v___x_4008_; uint8_t v___x_4009_; 
v___x_4005_ = 8388607;
v_xFraction_4006_ = lean_uint32_land(v_xBits_3677_, v___x_4005_);
v_yFraction_4007_ = lean_uint32_land(v_yBits_3678_, v___x_4005_);
v___x_4008_ = 0;
v___x_4009_ = lean_uint32_dec_eq(v_xExponent_3968_, v___x_4008_);
if (v___x_4009_ == 0)
{
uint64_t v___x_4010_; uint64_t v___x_4011_; uint64_t v___x_4012_; 
v___x_4010_ = lean_uint32_to_uint64(v_xFraction_4006_);
v___x_4011_ = 8388608ULL;
v___x_4012_ = lean_uint64_lor(v___x_4010_, v___x_4011_);
v___y_3993_ = v_yFraction_4007_;
v___y_3994_ = v___x_4005_;
v___y_3995_ = v___y_4004_;
v___y_3996_ = v___x_4012_;
goto v___jp_3992_;
}
else
{
uint64_t v___x_4013_; 
v___x_4013_ = lean_uint32_to_uint64(v_xFraction_4006_);
v___y_3993_ = v_yFraction_4007_;
v___y_3994_ = v___x_4005_;
v___y_3995_ = v___y_4004_;
v___y_3996_ = v___x_4013_;
goto v___jp_3992_;
}
}
v___jp_4014_:
{
uint8_t v___x_4015_; 
v___x_4015_ = 1;
v___y_4004_ = v___x_4015_;
goto v___jp_4003_;
}
v___jp_4016_:
{
uint8_t v___x_4017_; 
v___x_4017_ = 0;
v___y_4004_ = v___x_4017_;
goto v___jp_4003_;
}
v___jp_4018_:
{
if (v___y_4019_ == 0)
{
if (v___y_4020_ == 0)
{
goto v___jp_4016_;
}
else
{
goto v___jp_4014_;
}
}
else
{
if (v___y_4020_ == 0)
{
goto v___jp_4014_;
}
else
{
goto v___jp_4016_;
}
}
}
v___jp_4021_:
{
uint32_t v___x_4023_; uint32_t v___x_4024_; uint32_t v___x_4025_; uint8_t v___x_4026_; 
v___x_4023_ = 2147483648;
v___x_4024_ = lean_uint32_land(v_yBits_3678_, v___x_4023_);
v___x_4025_ = 0;
v___x_4026_ = lean_uint32_dec_eq(v___x_4024_, v___x_4025_);
if (v___x_4026_ == 0)
{
uint8_t v___x_4027_; 
v___x_4027_ = 1;
v___y_4019_ = v___y_4022_;
v___y_4020_ = v___x_4027_;
goto v___jp_4018_;
}
else
{
uint8_t v___x_4028_; 
v___x_4028_ = 0;
v___y_4019_ = v___y_4022_;
v___y_4020_ = v___x_4028_;
goto v___jp_4018_;
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_R6NormalMul_core___boxed(lean_object* v_xBits_4035_, lean_object* v_yBits_4036_){
_start:
{
uint32_t v_xBits_boxed_4037_; uint32_t v_yBits_boxed_4038_; uint32_t v_res_4039_; lean_object* v_r_4040_; 
v_xBits_boxed_4037_ = lean_unbox_uint32(v_xBits_4035_);
lean_dec(v_xBits_4035_);
v_yBits_boxed_4038_ = lean_unbox_uint32(v_yBits_4036_);
lean_dec(v_yBits_4036_);
v_res_4039_ = lp_competition_Submission_R6NormalMul_core(v_xBits_boxed_4037_, v_yBits_boxed_4038_);
v_r_4040_ = lean_box_uint32(v_res_4039_);
return v_r_4040_;
}
}
LEAN_EXPORT uint32_t lp_competition_Submission_R6NormalMul_mul(uint32_t v_x_4041_, uint32_t v_y_4042_){
_start:
{
uint32_t v___y_4044_; uint32_t v___y_4048_; uint32_t v___y_4049_; uint32_t v___y_4050_; uint8_t v___y_4054_; uint64_t v___y_4055_; uint32_t v___y_4056_; uint64_t v___y_4057_; uint32_t v___y_4069_; uint32_t v___y_4070_; uint32_t v___y_4071_; uint32_t v___y_4072_; uint32_t v___y_4073_; uint32_t v___y_4074_; uint32_t v___y_4081_; uint8_t v___y_4082_; uint32_t v___y_4083_; uint32_t v___y_4084_; uint32_t v___y_4085_; uint32_t v___y_4086_; uint8_t v___y_4090_; uint64_t v___y_4091_; uint32_t v___y_4092_; uint32_t v___y_4093_; uint64_t v___y_4094_; uint32_t v___y_4095_; uint64_t v___y_4096_; uint8_t v___y_4106_; uint8_t v___y_4107_; uint64_t v___y_4108_; uint64_t v___y_4109_; uint32_t v___y_4110_; uint32_t v___y_4111_; uint32_t v___y_4112_; uint64_t v___y_4113_; uint64_t v___y_4120_; uint8_t v___y_4121_; uint64_t v___y_4122_; uint32_t v___y_4123_; uint32_t v___y_4124_; uint32_t v___y_4125_; uint64_t v___y_4126_; uint64_t v___y_4132_; uint8_t v___y_4133_; uint64_t v___y_4134_; uint32_t v___y_4135_; uint32_t v___y_4136_; uint64_t v___y_4137_; uint32_t v___y_4138_; uint64_t v___y_4139_; uint64_t v___y_4194_; uint8_t v___y_4195_; uint64_t v___y_4196_; uint32_t v___y_4197_; uint32_t v___y_4198_; uint32_t v___y_4199_; uint64_t v___y_4200_; uint64_t v___y_4201_; uint64_t v___y_4202_; uint64_t v___y_4208_; uint64_t v___y_4209_; uint64_t v___y_4210_; uint64_t v___y_4211_; uint8_t v___y_4212_; uint64_t v___y_4213_; uint32_t v___y_4214_; uint32_t v___y_4215_; uint64_t v___y_4216_; uint32_t v___y_4217_; uint64_t v___y_4218_; uint64_t v___y_4223_; uint64_t v___y_4224_; uint8_t v___y_4225_; uint64_t v___y_4226_; uint32_t v___y_4227_; uint32_t v___y_4228_; uint32_t v___y_4229_; uint64_t v___y_4230_; uint64_t v___y_4231_; uint64_t v___y_4236_; uint64_t v___y_4237_; uint8_t v___y_4238_; uint64_t v___y_4239_; uint64_t v___y_4240_; uint64_t v___y_4241_; uint32_t v___y_4242_; uint32_t v___y_4243_; uint64_t v___y_4244_; uint32_t v___y_4245_; uint64_t v___y_4246_; uint64_t v___y_4251_; uint8_t v___y_4252_; uint64_t v___y_4253_; uint64_t v___y_4254_; uint32_t v___y_4255_; uint32_t v___y_4256_; uint32_t v___y_4257_; uint64_t v___y_4258_; uint64_t v___y_4259_; uint64_t v___y_4264_; uint64_t v___y_4265_; uint64_t v___y_4266_; uint8_t v___y_4267_; uint64_t v___y_4268_; uint32_t v___y_4269_; uint32_t v___y_4270_; uint64_t v___y_4271_; uint64_t v___y_4272_; uint32_t v___y_4273_; uint64_t v___y_4274_; uint64_t v___y_4279_; uint8_t v___y_4280_; uint64_t v___y_4281_; uint32_t v___y_4282_; uint32_t v___y_4283_; uint32_t v___y_4284_; uint64_t v___y_4285_; uint64_t v___y_4286_; uint64_t v___y_4287_; uint64_t v___y_4292_; uint64_t v___y_4293_; uint64_t v___y_4294_; uint8_t v___y_4295_; uint64_t v___y_4296_; uint64_t v___y_4297_; uint32_t v___y_4298_; uint32_t v___y_4299_; uint64_t v___y_4300_; uint32_t v___y_4301_; uint64_t v___y_4302_; uint64_t v___y_4307_; uint8_t v___y_4308_; uint64_t v___y_4309_; uint64_t v___y_4310_; uint32_t v___y_4311_; uint32_t v___y_4312_; uint32_t v___y_4313_; uint64_t v___y_4314_; uint64_t v___y_4315_; uint64_t v___y_4320_; uint8_t v___y_4321_; uint64_t v___y_4322_; uint64_t v___y_4323_; uint32_t v___y_4324_; uint32_t v___y_4325_; uint64_t v___y_4326_; uint32_t v___y_4327_; uint64_t v___y_4328_; uint64_t v___y_4332_; uint8_t v___y_4333_; uint64_t v___y_4334_; uint32_t v___y_4335_; uint32_t v___y_4336_; uint32_t v___y_4337_; uint64_t v___y_4338_; uint64_t v___y_4343_; uint8_t v___y_4344_; uint64_t v___y_4345_; uint32_t v___y_4346_; uint32_t v___y_4347_; uint32_t v___y_4348_; uint64_t v___y_4349_; uint64_t v___y_4350_; uint64_t v___y_4366_; uint32_t v___y_4367_; uint8_t v___y_4368_; uint64_t v___y_4369_; uint32_t v___y_4370_; uint32_t v___y_4371_; uint32_t v___y_4372_; uint64_t v___y_4373_; uint32_t v___y_4380_; uint32_t v___y_4381_; uint8_t v___y_4382_; uint64_t v___y_4383_; uint32_t v___y_4384_; uint32_t v___y_4385_; uint32_t v___y_4386_; uint64_t v___y_4387_; uint32_t v___y_4394_; uint32_t v___y_4395_; uint32_t v___y_4396_; uint8_t v___y_4397_; uint32_t v___y_4398_; uint32_t v___y_4399_; uint32_t v___y_4400_; uint64_t v___y_4401_; uint32_t v___y_4409_; uint32_t v___y_4410_; uint32_t v___y_4411_; uint32_t v___y_4412_; uint8_t v___y_4413_; uint32_t v___y_4424_; uint32_t v___y_4425_; uint32_t v___y_4426_; uint32_t v___y_4427_; uint32_t v___y_4430_; uint32_t v___y_4431_; uint8_t v___y_4432_; uint8_t v___y_4433_; uint32_t v___y_4434_; uint32_t v___y_4435_; uint8_t v___y_4436_; uint32_t v___y_4438_; uint8_t v___y_4439_; uint32_t v___y_4440_; uint32_t v___y_4441_; uint32_t v___y_4442_; uint8_t v___y_4443_; uint8_t v___y_4450_; uint32_t v___x_4467_; uint32_t v___x_4468_; uint32_t v___x_4469_; uint8_t v___x_4470_; 
v___x_4467_ = 4278190080;
v___x_4468_ = 1;
v___x_4469_ = lean_uint32_shift_left(v_x_4041_, v___x_4468_);
v___x_4470_ = lean_uint32_dec_le(v___x_4467_, v___x_4469_);
if (v___x_4470_ == 0)
{
uint32_t v___x_4471_; uint8_t v___x_4472_; 
v___x_4471_ = lean_uint32_shift_left(v_y_4042_, v___x_4468_);
v___x_4472_ = lean_uint32_dec_le(v___x_4467_, v___x_4471_);
v___y_4450_ = v___x_4472_;
goto v___jp_4449_;
}
else
{
v___y_4450_ = v___x_4470_;
goto v___jp_4449_;
}
v___jp_4043_:
{
uint32_t v___x_4045_; uint32_t v___x_4046_; 
v___x_4045_ = 8388608;
v___x_4046_ = lean_uint32_lor(v___y_4044_, v___x_4045_);
return v___x_4046_;
}
v___jp_4047_:
{
uint32_t v___x_4051_; uint32_t v___x_4052_; 
v___x_4051_ = lean_uint32_land(v___y_4048_, v___y_4049_);
v___x_4052_ = lean_uint32_lor(v___y_4050_, v___x_4051_);
return v___x_4052_;
}
v___jp_4053_:
{
uint8_t v___x_4058_; 
v___x_4058_ = lean_uint64_dec_eq(v___y_4057_, v___y_4055_);
if (v___x_4058_ == 0)
{
uint64_t v___x_4059_; uint8_t v___x_4060_; 
v___x_4059_ = 8388608ULL;
v___x_4060_ = lean_uint64_dec_eq(v___y_4057_, v___x_4059_);
if (v___x_4060_ == 0)
{
uint32_t v___x_4061_; 
v___x_4061_ = lean_uint64_to_uint32(v___y_4057_);
if (v___y_4054_ == 0)
{
uint32_t v___x_4062_; 
v___x_4062_ = 0;
v___y_4048_ = v___x_4061_;
v___y_4049_ = v___y_4056_;
v___y_4050_ = v___x_4062_;
goto v___jp_4047_;
}
else
{
uint32_t v___x_4063_; 
v___x_4063_ = 2147483648;
v___y_4048_ = v___x_4061_;
v___y_4049_ = v___y_4056_;
v___y_4050_ = v___x_4063_;
goto v___jp_4047_;
}
}
else
{
if (v___y_4054_ == 0)
{
uint32_t v___x_4064_; 
v___x_4064_ = 0;
v___y_4044_ = v___x_4064_;
goto v___jp_4043_;
}
else
{
uint32_t v___x_4065_; 
v___x_4065_ = 2147483648;
v___y_4044_ = v___x_4065_;
goto v___jp_4043_;
}
}
}
else
{
if (v___y_4054_ == 0)
{
uint32_t v___x_4066_; 
v___x_4066_ = 0;
return v___x_4066_;
}
else
{
uint32_t v___x_4067_; 
v___x_4067_ = 2147483648;
return v___x_4067_;
}
}
}
v___jp_4068_:
{
uint32_t v___x_4075_; uint32_t v___x_4076_; uint32_t v___x_4077_; uint32_t v___x_4078_; uint32_t v___x_4079_; 
v___x_4075_ = lean_uint32_land(v___y_4069_, v___y_4071_);
v___x_4076_ = lean_uint32_shift_left(v___x_4075_, v___y_4073_);
v___x_4077_ = lean_uint32_lor(v___y_4074_, v___x_4076_);
v___x_4078_ = lean_uint32_land(v___y_4070_, v___y_4072_);
v___x_4079_ = lean_uint32_lor(v___x_4077_, v___x_4078_);
return v___x_4079_;
}
v___jp_4080_:
{
if (v___y_4082_ == 0)
{
uint32_t v___x_4087_; 
v___x_4087_ = 0;
v___y_4069_ = v___y_4081_;
v___y_4070_ = v___y_4086_;
v___y_4071_ = v___y_4083_;
v___y_4072_ = v___y_4084_;
v___y_4073_ = v___y_4085_;
v___y_4074_ = v___x_4087_;
goto v___jp_4068_;
}
else
{
uint32_t v___x_4088_; 
v___x_4088_ = 2147483648;
v___y_4069_ = v___y_4081_;
v___y_4070_ = v___y_4086_;
v___y_4071_ = v___y_4083_;
v___y_4072_ = v___y_4084_;
v___y_4073_ = v___y_4085_;
v___y_4074_ = v___x_4088_;
goto v___jp_4068_;
}
}
v___jp_4089_:
{
uint64_t v___x_4097_; uint64_t v_encodedExponent_4098_; uint32_t v___x_4099_; uint64_t v___x_4100_; uint8_t v___x_4101_; 
v___x_4097_ = 171ULL;
v_encodedExponent_4098_ = lean_uint64_sub(v___y_4094_, v___x_4097_);
v___x_4099_ = lean_uint64_to_uint32(v_encodedExponent_4098_);
v___x_4100_ = 8388608ULL;
v___x_4101_ = lean_uint64_dec_lt(v___y_4096_, v___x_4100_);
if (v___x_4101_ == 0)
{
uint64_t v___x_4102_; uint32_t v___x_4103_; 
v___x_4102_ = lean_uint64_sub(v___y_4096_, v___x_4100_);
v___x_4103_ = lean_uint64_to_uint32(v___x_4102_);
v___y_4081_ = v___x_4099_;
v___y_4082_ = v___y_4090_;
v___y_4083_ = v___y_4092_;
v___y_4084_ = v___y_4093_;
v___y_4085_ = v___y_4095_;
v___y_4086_ = v___x_4103_;
goto v___jp_4080_;
}
else
{
uint32_t v___x_4104_; 
v___x_4104_ = lean_uint64_to_uint32(v___y_4091_);
v___y_4081_ = v___x_4099_;
v___y_4082_ = v___y_4090_;
v___y_4083_ = v___y_4092_;
v___y_4084_ = v___y_4093_;
v___y_4085_ = v___y_4095_;
v___y_4086_ = v___x_4104_;
goto v___jp_4080_;
}
}
v___jp_4105_:
{
uint64_t v___x_4114_; uint8_t v___x_4115_; 
v___x_4114_ = 425ULL;
v___x_4115_ = lean_uint64_dec_lt(v___x_4114_, v___y_4113_);
if (v___x_4115_ == 0)
{
if (v___y_4106_ == 0)
{
v___y_4090_ = v___y_4107_;
v___y_4091_ = v___y_4109_;
v___y_4092_ = v___y_4110_;
v___y_4093_ = v___y_4111_;
v___y_4094_ = v___y_4113_;
v___y_4095_ = v___y_4112_;
v___y_4096_ = v___y_4108_;
goto v___jp_4089_;
}
else
{
uint64_t v___x_4116_; 
v___x_4116_ = 8388608ULL;
v___y_4090_ = v___y_4107_;
v___y_4091_ = v___y_4109_;
v___y_4092_ = v___y_4110_;
v___y_4093_ = v___y_4111_;
v___y_4094_ = v___y_4113_;
v___y_4095_ = v___y_4112_;
v___y_4096_ = v___x_4116_;
goto v___jp_4089_;
}
}
else
{
if (v___y_4107_ == 0)
{
uint32_t v___x_4117_; 
v___x_4117_ = 2139095040;
return v___x_4117_;
}
else
{
uint32_t v___x_4118_; 
v___x_4118_ = 4286578688;
return v___x_4118_;
}
}
}
v___jp_4119_:
{
uint64_t v___x_4127_; uint8_t v_carry_4128_; 
v___x_4127_ = 16777216ULL;
v_carry_4128_ = lean_uint64_dec_eq(v___y_4126_, v___x_4127_);
if (v_carry_4128_ == 0)
{
v___y_4106_ = v_carry_4128_;
v___y_4107_ = v___y_4121_;
v___y_4108_ = v___y_4126_;
v___y_4109_ = v___y_4122_;
v___y_4110_ = v___y_4123_;
v___y_4111_ = v___y_4124_;
v___y_4112_ = v___y_4125_;
v___y_4113_ = v___y_4120_;
goto v___jp_4105_;
}
else
{
uint64_t v___x_4129_; uint64_t v___x_4130_; 
v___x_4129_ = 1ULL;
v___x_4130_ = lean_uint64_add(v___y_4120_, v___x_4129_);
v___y_4106_ = v_carry_4128_;
v___y_4107_ = v___y_4121_;
v___y_4108_ = v___y_4126_;
v___y_4109_ = v___y_4122_;
v___y_4110_ = v___y_4123_;
v___y_4111_ = v___y_4124_;
v___y_4112_ = v___y_4125_;
v___y_4113_ = v___x_4130_;
goto v___jp_4105_;
}
}
v___jp_4131_:
{
uint64_t v_position_4140_; uint64_t v___x_4141_; uint8_t v___x_4142_; 
v_position_4140_ = lean_uint64_add(v___y_4139_, v___y_4132_);
v___x_4141_ = 172ULL;
v___x_4142_ = lean_uint64_dec_lt(v_position_4140_, v___x_4141_);
if (v___x_4142_ == 0)
{
uint64_t v___x_4143_; uint8_t v___x_4144_; 
v___x_4143_ = 23ULL;
v___x_4144_ = lean_uint64_dec_lt(v___y_4139_, v___x_4143_);
if (v___x_4144_ == 0)
{
uint64_t v___x_4145_; uint8_t v___x_4146_; 
v___x_4145_ = lean_uint64_sub(v___y_4139_, v___x_4143_);
v___x_4146_ = lean_uint64_dec_eq(v___x_4145_, v___y_4134_);
if (v___x_4146_ == 0)
{
uint64_t v___x_4147_; uint8_t v___x_4148_; 
v___x_4147_ = 64ULL;
v___x_4148_ = lean_uint64_dec_lt(v___x_4145_, v___x_4147_);
if (v___x_4148_ == 0)
{
uint8_t v___x_4149_; 
v___x_4149_ = lean_uint64_dec_eq(v___x_4145_, v___x_4147_);
if (v___x_4149_ == 0)
{
v___y_4120_ = v_position_4140_;
v___y_4121_ = v___y_4133_;
v___y_4122_ = v___y_4134_;
v___y_4123_ = v___y_4135_;
v___y_4124_ = v___y_4136_;
v___y_4125_ = v___y_4138_;
v___y_4126_ = v___y_4134_;
goto v___jp_4119_;
}
else
{
uint64_t v___x_4150_; uint8_t v___x_4151_; 
v___x_4150_ = 9223372036854775808ULL;
v___x_4151_ = lean_uint64_dec_lt(v___x_4150_, v___y_4137_);
if (v___x_4151_ == 0)
{
v___y_4120_ = v_position_4140_;
v___y_4121_ = v___y_4133_;
v___y_4122_ = v___y_4134_;
v___y_4123_ = v___y_4135_;
v___y_4124_ = v___y_4136_;
v___y_4125_ = v___y_4138_;
v___y_4126_ = v___y_4134_;
goto v___jp_4119_;
}
else
{
uint64_t v___x_4152_; 
v___x_4152_ = 1ULL;
v___y_4120_ = v_position_4140_;
v___y_4121_ = v___y_4133_;
v___y_4122_ = v___y_4134_;
v___y_4123_ = v___y_4135_;
v___y_4124_ = v___y_4136_;
v___y_4125_ = v___y_4138_;
v___y_4126_ = v___x_4152_;
goto v___jp_4119_;
}
}
}
else
{
uint64_t v_quotient_4153_; uint64_t v___x_4154_; uint64_t v___x_4155_; uint64_t v___x_4156_; uint64_t v_remainder_4157_; uint64_t v___x_4158_; uint64_t v_half_4159_; uint8_t v___x_4160_; 
v_quotient_4153_ = lean_uint64_shift_right(v___y_4137_, v___x_4145_);
v___x_4154_ = 1ULL;
v___x_4155_ = lean_uint64_shift_left(v___x_4154_, v___x_4145_);
v___x_4156_ = lean_uint64_sub(v___x_4155_, v___x_4154_);
v_remainder_4157_ = lean_uint64_land(v___y_4137_, v___x_4156_);
v___x_4158_ = lean_uint64_sub(v___x_4145_, v___x_4154_);
v_half_4159_ = lean_uint64_shift_left(v___x_4154_, v___x_4158_);
v___x_4160_ = lean_uint64_dec_lt(v_remainder_4157_, v_half_4159_);
if (v___x_4160_ == 0)
{
uint8_t v___x_4161_; 
v___x_4161_ = lean_uint64_dec_lt(v_half_4159_, v_remainder_4157_);
if (v___x_4161_ == 0)
{
uint64_t v___x_4162_; uint8_t v___x_4163_; 
v___x_4162_ = lean_uint64_land(v_quotient_4153_, v___x_4154_);
v___x_4163_ = lean_uint64_dec_eq(v___x_4162_, v___y_4134_);
if (v___x_4163_ == 0)
{
uint64_t v___x_4164_; 
v___x_4164_ = lean_uint64_add(v_quotient_4153_, v___x_4154_);
v___y_4120_ = v_position_4140_;
v___y_4121_ = v___y_4133_;
v___y_4122_ = v___y_4134_;
v___y_4123_ = v___y_4135_;
v___y_4124_ = v___y_4136_;
v___y_4125_ = v___y_4138_;
v___y_4126_ = v___x_4164_;
goto v___jp_4119_;
}
else
{
v___y_4120_ = v_position_4140_;
v___y_4121_ = v___y_4133_;
v___y_4122_ = v___y_4134_;
v___y_4123_ = v___y_4135_;
v___y_4124_ = v___y_4136_;
v___y_4125_ = v___y_4138_;
v___y_4126_ = v_quotient_4153_;
goto v___jp_4119_;
}
}
else
{
uint64_t v___x_4165_; 
v___x_4165_ = lean_uint64_add(v_quotient_4153_, v___x_4154_);
v___y_4120_ = v_position_4140_;
v___y_4121_ = v___y_4133_;
v___y_4122_ = v___y_4134_;
v___y_4123_ = v___y_4135_;
v___y_4124_ = v___y_4136_;
v___y_4125_ = v___y_4138_;
v___y_4126_ = v___x_4165_;
goto v___jp_4119_;
}
}
else
{
v___y_4120_ = v_position_4140_;
v___y_4121_ = v___y_4133_;
v___y_4122_ = v___y_4134_;
v___y_4123_ = v___y_4135_;
v___y_4124_ = v___y_4136_;
v___y_4125_ = v___y_4138_;
v___y_4126_ = v_quotient_4153_;
goto v___jp_4119_;
}
}
}
else
{
v___y_4120_ = v_position_4140_;
v___y_4121_ = v___y_4133_;
v___y_4122_ = v___y_4134_;
v___y_4123_ = v___y_4135_;
v___y_4124_ = v___y_4136_;
v___y_4125_ = v___y_4138_;
v___y_4126_ = v___y_4137_;
goto v___jp_4119_;
}
}
else
{
uint64_t v___x_4166_; uint64_t v___x_4167_; 
v___x_4166_ = lean_uint64_sub(v___x_4143_, v___y_4139_);
v___x_4167_ = lean_uint64_shift_left(v___y_4137_, v___x_4166_);
v___y_4120_ = v_position_4140_;
v___y_4121_ = v___y_4133_;
v___y_4122_ = v___y_4134_;
v___y_4123_ = v___y_4135_;
v___y_4124_ = v___y_4136_;
v___y_4125_ = v___y_4138_;
v___y_4126_ = v___x_4167_;
goto v___jp_4119_;
}
}
else
{
uint64_t v___x_4168_; uint8_t v___x_4169_; 
v___x_4168_ = 149ULL;
v___x_4169_ = lean_uint64_dec_lt(v___y_4132_, v___x_4168_);
if (v___x_4169_ == 0)
{
uint64_t v___x_4170_; uint64_t v___x_4171_; 
v___x_4170_ = lean_uint64_sub(v___y_4132_, v___x_4168_);
v___x_4171_ = lean_uint64_shift_left(v___y_4137_, v___x_4170_);
v___y_4054_ = v___y_4133_;
v___y_4055_ = v___y_4134_;
v___y_4056_ = v___y_4136_;
v___y_4057_ = v___x_4171_;
goto v___jp_4053_;
}
else
{
uint64_t v___x_4172_; uint8_t v___x_4173_; 
v___x_4172_ = lean_uint64_sub(v___x_4168_, v___y_4132_);
v___x_4173_ = lean_uint64_dec_eq(v___x_4172_, v___y_4134_);
if (v___x_4173_ == 0)
{
uint64_t v___x_4174_; uint8_t v___x_4175_; 
v___x_4174_ = 64ULL;
v___x_4175_ = lean_uint64_dec_lt(v___x_4172_, v___x_4174_);
if (v___x_4175_ == 0)
{
uint8_t v___x_4176_; 
v___x_4176_ = lean_uint64_dec_eq(v___x_4172_, v___x_4174_);
if (v___x_4176_ == 0)
{
v___y_4054_ = v___y_4133_;
v___y_4055_ = v___y_4134_;
v___y_4056_ = v___y_4136_;
v___y_4057_ = v___y_4134_;
goto v___jp_4053_;
}
else
{
uint64_t v___x_4177_; uint8_t v___x_4178_; 
v___x_4177_ = 9223372036854775808ULL;
v___x_4178_ = lean_uint64_dec_lt(v___x_4177_, v___y_4137_);
if (v___x_4178_ == 0)
{
v___y_4054_ = v___y_4133_;
v___y_4055_ = v___y_4134_;
v___y_4056_ = v___y_4136_;
v___y_4057_ = v___y_4134_;
goto v___jp_4053_;
}
else
{
uint64_t v___x_4179_; 
v___x_4179_ = 1ULL;
v___y_4054_ = v___y_4133_;
v___y_4055_ = v___y_4134_;
v___y_4056_ = v___y_4136_;
v___y_4057_ = v___x_4179_;
goto v___jp_4053_;
}
}
}
else
{
uint64_t v_quotient_4180_; uint64_t v___x_4181_; uint64_t v___x_4182_; uint64_t v___x_4183_; uint64_t v_remainder_4184_; uint64_t v___x_4185_; uint64_t v_half_4186_; uint8_t v___x_4187_; 
v_quotient_4180_ = lean_uint64_shift_right(v___y_4137_, v___x_4172_);
v___x_4181_ = 1ULL;
v___x_4182_ = lean_uint64_shift_left(v___x_4181_, v___x_4172_);
v___x_4183_ = lean_uint64_sub(v___x_4182_, v___x_4181_);
v_remainder_4184_ = lean_uint64_land(v___y_4137_, v___x_4183_);
v___x_4185_ = lean_uint64_sub(v___x_4172_, v___x_4181_);
v_half_4186_ = lean_uint64_shift_left(v___x_4181_, v___x_4185_);
v___x_4187_ = lean_uint64_dec_lt(v_remainder_4184_, v_half_4186_);
if (v___x_4187_ == 0)
{
uint8_t v___x_4188_; 
v___x_4188_ = lean_uint64_dec_lt(v_half_4186_, v_remainder_4184_);
if (v___x_4188_ == 0)
{
uint64_t v___x_4189_; uint8_t v___x_4190_; 
v___x_4189_ = lean_uint64_land(v_quotient_4180_, v___x_4181_);
v___x_4190_ = lean_uint64_dec_eq(v___x_4189_, v___y_4134_);
if (v___x_4190_ == 0)
{
uint64_t v___x_4191_; 
v___x_4191_ = lean_uint64_add(v_quotient_4180_, v___x_4181_);
v___y_4054_ = v___y_4133_;
v___y_4055_ = v___y_4134_;
v___y_4056_ = v___y_4136_;
v___y_4057_ = v___x_4191_;
goto v___jp_4053_;
}
else
{
v___y_4054_ = v___y_4133_;
v___y_4055_ = v___y_4134_;
v___y_4056_ = v___y_4136_;
v___y_4057_ = v_quotient_4180_;
goto v___jp_4053_;
}
}
else
{
uint64_t v___x_4192_; 
v___x_4192_ = lean_uint64_add(v_quotient_4180_, v___x_4181_);
v___y_4054_ = v___y_4133_;
v___y_4055_ = v___y_4134_;
v___y_4056_ = v___y_4136_;
v___y_4057_ = v___x_4192_;
goto v___jp_4053_;
}
}
else
{
v___y_4054_ = v___y_4133_;
v___y_4055_ = v___y_4134_;
v___y_4056_ = v___y_4136_;
v___y_4057_ = v_quotient_4180_;
goto v___jp_4053_;
}
}
}
else
{
v___y_4054_ = v___y_4133_;
v___y_4055_ = v___y_4134_;
v___y_4056_ = v___y_4136_;
v___y_4057_ = v___y_4137_;
goto v___jp_4053_;
}
}
}
}
v___jp_4193_:
{
uint64_t v___x_4203_; uint64_t v___x_4204_; uint8_t v___x_4205_; 
v___x_4203_ = 1ULL;
v___x_4204_ = lean_uint64_shift_right(v___y_4201_, v___x_4203_);
v___x_4205_ = lean_uint64_dec_eq(v___x_4204_, v___y_4196_);
if (v___x_4205_ == 0)
{
uint64_t v___x_4206_; 
v___x_4206_ = lean_uint64_add(v___y_4202_, v___x_4203_);
v___y_4132_ = v___y_4194_;
v___y_4133_ = v___y_4195_;
v___y_4134_ = v___y_4196_;
v___y_4135_ = v___y_4197_;
v___y_4136_ = v___y_4198_;
v___y_4137_ = v___y_4200_;
v___y_4138_ = v___y_4199_;
v___y_4139_ = v___x_4206_;
goto v___jp_4131_;
}
else
{
v___y_4132_ = v___y_4194_;
v___y_4133_ = v___y_4195_;
v___y_4134_ = v___y_4196_;
v___y_4135_ = v___y_4197_;
v___y_4136_ = v___y_4198_;
v___y_4137_ = v___y_4200_;
v___y_4138_ = v___y_4199_;
v___y_4139_ = v___y_4202_;
goto v___jp_4131_;
}
}
v___jp_4207_:
{
uint64_t v___x_4219_; uint8_t v___x_4220_; 
v___x_4219_ = lean_uint64_shift_right(v___y_4211_, v___y_4210_);
v___x_4220_ = lean_uint64_dec_eq(v___x_4219_, v___y_4213_);
if (v___x_4220_ == 0)
{
uint64_t v___x_4221_; 
v___x_4221_ = lean_uint64_add(v___y_4208_, v___y_4210_);
v___y_4194_ = v___y_4209_;
v___y_4195_ = v___y_4212_;
v___y_4196_ = v___y_4213_;
v___y_4197_ = v___y_4214_;
v___y_4198_ = v___y_4215_;
v___y_4199_ = v___y_4217_;
v___y_4200_ = v___y_4216_;
v___y_4201_ = v___y_4218_;
v___y_4202_ = v___x_4221_;
goto v___jp_4193_;
}
else
{
v___y_4194_ = v___y_4209_;
v___y_4195_ = v___y_4212_;
v___y_4196_ = v___y_4213_;
v___y_4197_ = v___y_4214_;
v___y_4198_ = v___y_4215_;
v___y_4199_ = v___y_4217_;
v___y_4200_ = v___y_4216_;
v___y_4201_ = v___y_4218_;
v___y_4202_ = v___y_4208_;
goto v___jp_4193_;
}
}
v___jp_4222_:
{
uint64_t v___x_4232_; uint64_t v___x_4233_; uint8_t v___x_4234_; 
v___x_4232_ = 2ULL;
v___x_4233_ = lean_uint64_shift_right(v___y_4224_, v___x_4232_);
v___x_4234_ = lean_uint64_dec_eq(v___x_4233_, v___y_4226_);
if (v___x_4234_ == 0)
{
v___y_4208_ = v___y_4231_;
v___y_4209_ = v___y_4223_;
v___y_4210_ = v___x_4232_;
v___y_4211_ = v___y_4224_;
v___y_4212_ = v___y_4225_;
v___y_4213_ = v___y_4226_;
v___y_4214_ = v___y_4227_;
v___y_4215_ = v___y_4228_;
v___y_4216_ = v___y_4230_;
v___y_4217_ = v___y_4229_;
v___y_4218_ = v___x_4233_;
goto v___jp_4207_;
}
else
{
v___y_4208_ = v___y_4231_;
v___y_4209_ = v___y_4223_;
v___y_4210_ = v___x_4232_;
v___y_4211_ = v___y_4224_;
v___y_4212_ = v___y_4225_;
v___y_4213_ = v___y_4226_;
v___y_4214_ = v___y_4227_;
v___y_4215_ = v___y_4228_;
v___y_4216_ = v___y_4230_;
v___y_4217_ = v___y_4229_;
v___y_4218_ = v___y_4224_;
goto v___jp_4207_;
}
}
v___jp_4235_:
{
uint64_t v___x_4247_; uint8_t v___x_4248_; 
v___x_4247_ = lean_uint64_shift_right(v___y_4239_, v___y_4240_);
v___x_4248_ = lean_uint64_dec_eq(v___x_4247_, v___y_4241_);
if (v___x_4248_ == 0)
{
uint64_t v___x_4249_; 
v___x_4249_ = lean_uint64_add(v___y_4236_, v___y_4240_);
v___y_4223_ = v___y_4237_;
v___y_4224_ = v___y_4246_;
v___y_4225_ = v___y_4238_;
v___y_4226_ = v___y_4241_;
v___y_4227_ = v___y_4242_;
v___y_4228_ = v___y_4243_;
v___y_4229_ = v___y_4245_;
v___y_4230_ = v___y_4244_;
v___y_4231_ = v___x_4249_;
goto v___jp_4222_;
}
else
{
v___y_4223_ = v___y_4237_;
v___y_4224_ = v___y_4246_;
v___y_4225_ = v___y_4238_;
v___y_4226_ = v___y_4241_;
v___y_4227_ = v___y_4242_;
v___y_4228_ = v___y_4243_;
v___y_4229_ = v___y_4245_;
v___y_4230_ = v___y_4244_;
v___y_4231_ = v___y_4236_;
goto v___jp_4222_;
}
}
v___jp_4250_:
{
uint64_t v___x_4260_; uint64_t v___x_4261_; uint8_t v___x_4262_; 
v___x_4260_ = 4ULL;
v___x_4261_ = lean_uint64_shift_right(v___y_4253_, v___x_4260_);
v___x_4262_ = lean_uint64_dec_eq(v___x_4261_, v___y_4254_);
if (v___x_4262_ == 0)
{
v___y_4236_ = v___y_4259_;
v___y_4237_ = v___y_4251_;
v___y_4238_ = v___y_4252_;
v___y_4239_ = v___y_4253_;
v___y_4240_ = v___x_4260_;
v___y_4241_ = v___y_4254_;
v___y_4242_ = v___y_4255_;
v___y_4243_ = v___y_4256_;
v___y_4244_ = v___y_4258_;
v___y_4245_ = v___y_4257_;
v___y_4246_ = v___x_4261_;
goto v___jp_4235_;
}
else
{
v___y_4236_ = v___y_4259_;
v___y_4237_ = v___y_4251_;
v___y_4238_ = v___y_4252_;
v___y_4239_ = v___y_4253_;
v___y_4240_ = v___x_4260_;
v___y_4241_ = v___y_4254_;
v___y_4242_ = v___y_4255_;
v___y_4243_ = v___y_4256_;
v___y_4244_ = v___y_4258_;
v___y_4245_ = v___y_4257_;
v___y_4246_ = v___y_4253_;
goto v___jp_4235_;
}
}
v___jp_4263_:
{
uint64_t v___x_4275_; uint8_t v___x_4276_; 
v___x_4275_ = lean_uint64_shift_right(v___y_4271_, v___y_4264_);
v___x_4276_ = lean_uint64_dec_eq(v___x_4275_, v___y_4268_);
if (v___x_4276_ == 0)
{
uint64_t v___x_4277_; 
v___x_4277_ = lean_uint64_add(v___y_4266_, v___y_4264_);
v___y_4251_ = v___y_4265_;
v___y_4252_ = v___y_4267_;
v___y_4253_ = v___y_4274_;
v___y_4254_ = v___y_4268_;
v___y_4255_ = v___y_4269_;
v___y_4256_ = v___y_4270_;
v___y_4257_ = v___y_4273_;
v___y_4258_ = v___y_4272_;
v___y_4259_ = v___x_4277_;
goto v___jp_4250_;
}
else
{
v___y_4251_ = v___y_4265_;
v___y_4252_ = v___y_4267_;
v___y_4253_ = v___y_4274_;
v___y_4254_ = v___y_4268_;
v___y_4255_ = v___y_4269_;
v___y_4256_ = v___y_4270_;
v___y_4257_ = v___y_4273_;
v___y_4258_ = v___y_4272_;
v___y_4259_ = v___y_4266_;
goto v___jp_4250_;
}
}
v___jp_4278_:
{
uint64_t v___x_4288_; uint64_t v___x_4289_; uint8_t v___x_4290_; 
v___x_4288_ = 8ULL;
v___x_4289_ = lean_uint64_shift_right(v___y_4286_, v___x_4288_);
v___x_4290_ = lean_uint64_dec_eq(v___x_4289_, v___y_4281_);
if (v___x_4290_ == 0)
{
v___y_4264_ = v___x_4288_;
v___y_4265_ = v___y_4279_;
v___y_4266_ = v___y_4287_;
v___y_4267_ = v___y_4280_;
v___y_4268_ = v___y_4281_;
v___y_4269_ = v___y_4282_;
v___y_4270_ = v___y_4283_;
v___y_4271_ = v___y_4286_;
v___y_4272_ = v___y_4285_;
v___y_4273_ = v___y_4284_;
v___y_4274_ = v___x_4289_;
goto v___jp_4263_;
}
else
{
v___y_4264_ = v___x_4288_;
v___y_4265_ = v___y_4279_;
v___y_4266_ = v___y_4287_;
v___y_4267_ = v___y_4280_;
v___y_4268_ = v___y_4281_;
v___y_4269_ = v___y_4282_;
v___y_4270_ = v___y_4283_;
v___y_4271_ = v___y_4286_;
v___y_4272_ = v___y_4285_;
v___y_4273_ = v___y_4284_;
v___y_4274_ = v___y_4286_;
goto v___jp_4263_;
}
}
v___jp_4291_:
{
uint64_t v___x_4303_; uint8_t v___x_4304_; 
v___x_4303_ = lean_uint64_shift_right(v___y_4296_, v___y_4294_);
v___x_4304_ = lean_uint64_dec_eq(v___x_4303_, v___y_4297_);
if (v___x_4304_ == 0)
{
uint64_t v___x_4305_; 
v___x_4305_ = lean_uint64_add(v___y_4292_, v___y_4294_);
v___y_4279_ = v___y_4293_;
v___y_4280_ = v___y_4295_;
v___y_4281_ = v___y_4297_;
v___y_4282_ = v___y_4298_;
v___y_4283_ = v___y_4299_;
v___y_4284_ = v___y_4301_;
v___y_4285_ = v___y_4300_;
v___y_4286_ = v___y_4302_;
v___y_4287_ = v___x_4305_;
goto v___jp_4278_;
}
else
{
v___y_4279_ = v___y_4293_;
v___y_4280_ = v___y_4295_;
v___y_4281_ = v___y_4297_;
v___y_4282_ = v___y_4298_;
v___y_4283_ = v___y_4299_;
v___y_4284_ = v___y_4301_;
v___y_4285_ = v___y_4300_;
v___y_4286_ = v___y_4302_;
v___y_4287_ = v___y_4292_;
goto v___jp_4278_;
}
}
v___jp_4306_:
{
uint64_t v___x_4316_; uint64_t v___x_4317_; uint8_t v___x_4318_; 
v___x_4316_ = 16ULL;
v___x_4317_ = lean_uint64_shift_right(v___y_4309_, v___x_4316_);
v___x_4318_ = lean_uint64_dec_eq(v___x_4317_, v___y_4310_);
if (v___x_4318_ == 0)
{
v___y_4292_ = v___y_4315_;
v___y_4293_ = v___y_4307_;
v___y_4294_ = v___x_4316_;
v___y_4295_ = v___y_4308_;
v___y_4296_ = v___y_4309_;
v___y_4297_ = v___y_4310_;
v___y_4298_ = v___y_4311_;
v___y_4299_ = v___y_4312_;
v___y_4300_ = v___y_4314_;
v___y_4301_ = v___y_4313_;
v___y_4302_ = v___x_4317_;
goto v___jp_4291_;
}
else
{
v___y_4292_ = v___y_4315_;
v___y_4293_ = v___y_4307_;
v___y_4294_ = v___x_4316_;
v___y_4295_ = v___y_4308_;
v___y_4296_ = v___y_4309_;
v___y_4297_ = v___y_4310_;
v___y_4298_ = v___y_4311_;
v___y_4299_ = v___y_4312_;
v___y_4300_ = v___y_4314_;
v___y_4301_ = v___y_4313_;
v___y_4302_ = v___y_4309_;
goto v___jp_4291_;
}
}
v___jp_4319_:
{
uint64_t v___x_4329_; uint8_t v___x_4330_; 
v___x_4329_ = lean_uint64_shift_right(v___y_4326_, v___y_4322_);
v___x_4330_ = lean_uint64_dec_eq(v___x_4329_, v___y_4323_);
if (v___x_4330_ == 0)
{
v___y_4307_ = v___y_4320_;
v___y_4308_ = v___y_4321_;
v___y_4309_ = v___y_4328_;
v___y_4310_ = v___y_4323_;
v___y_4311_ = v___y_4324_;
v___y_4312_ = v___y_4325_;
v___y_4313_ = v___y_4327_;
v___y_4314_ = v___y_4326_;
v___y_4315_ = v___y_4322_;
goto v___jp_4306_;
}
else
{
v___y_4307_ = v___y_4320_;
v___y_4308_ = v___y_4321_;
v___y_4309_ = v___y_4328_;
v___y_4310_ = v___y_4323_;
v___y_4311_ = v___y_4324_;
v___y_4312_ = v___y_4325_;
v___y_4313_ = v___y_4327_;
v___y_4314_ = v___y_4326_;
v___y_4315_ = v___y_4323_;
goto v___jp_4306_;
}
}
v___jp_4331_:
{
uint64_t v___x_4339_; uint64_t v___x_4340_; uint8_t v___x_4341_; 
v___x_4339_ = 32ULL;
v___x_4340_ = lean_uint64_shift_right(v___y_4338_, v___x_4339_);
v___x_4341_ = lean_uint64_dec_eq(v___x_4340_, v___y_4334_);
if (v___x_4341_ == 0)
{
v___y_4320_ = v___y_4332_;
v___y_4321_ = v___y_4333_;
v___y_4322_ = v___x_4339_;
v___y_4323_ = v___y_4334_;
v___y_4324_ = v___y_4335_;
v___y_4325_ = v___y_4336_;
v___y_4326_ = v___y_4338_;
v___y_4327_ = v___y_4337_;
v___y_4328_ = v___x_4340_;
goto v___jp_4319_;
}
else
{
v___y_4320_ = v___y_4332_;
v___y_4321_ = v___y_4333_;
v___y_4322_ = v___x_4339_;
v___y_4323_ = v___y_4334_;
v___y_4324_ = v___y_4335_;
v___y_4325_ = v___y_4336_;
v___y_4326_ = v___y_4338_;
v___y_4327_ = v___y_4337_;
v___y_4328_ = v___y_4338_;
goto v___jp_4319_;
}
}
v___jp_4342_:
{
uint64_t v___x_4351_; uint64_t v___x_4352_; uint8_t v___x_4353_; 
v___x_4351_ = lean_uint64_mul(v___y_4345_, v___y_4343_);
v___x_4352_ = 0ULL;
v___x_4353_ = lean_uint64_dec_eq(v___x_4351_, v___x_4352_);
if (v___x_4353_ == 0)
{
uint64_t v___x_4354_; uint64_t v___x_4355_; uint8_t v___x_4356_; 
v___x_4354_ = lean_uint64_add(v___y_4349_, v___y_4350_);
v___x_4355_ = 70368744177664ULL;
v___x_4356_ = lean_uint64_dec_le(v___x_4355_, v___x_4351_);
if (v___x_4356_ == 0)
{
v___y_4332_ = v___x_4354_;
v___y_4333_ = v___y_4344_;
v___y_4334_ = v___x_4352_;
v___y_4335_ = v___y_4346_;
v___y_4336_ = v___y_4347_;
v___y_4337_ = v___y_4348_;
v___y_4338_ = v___x_4351_;
goto v___jp_4331_;
}
else
{
uint64_t v___x_4357_; uint8_t v___x_4358_; 
v___x_4357_ = 281474976710656ULL;
v___x_4358_ = lean_uint64_dec_lt(v___x_4351_, v___x_4357_);
if (v___x_4358_ == 0)
{
v___y_4332_ = v___x_4354_;
v___y_4333_ = v___y_4344_;
v___y_4334_ = v___x_4352_;
v___y_4335_ = v___y_4346_;
v___y_4336_ = v___y_4347_;
v___y_4337_ = v___y_4348_;
v___y_4338_ = v___x_4351_;
goto v___jp_4331_;
}
else
{
uint64_t v___x_4359_; uint8_t v___x_4360_; 
v___x_4359_ = 140737488355328ULL;
v___x_4360_ = lean_uint64_dec_lt(v___x_4351_, v___x_4359_);
if (v___x_4360_ == 0)
{
uint64_t v___x_4361_; 
v___x_4361_ = 47ULL;
v___y_4132_ = v___x_4354_;
v___y_4133_ = v___y_4344_;
v___y_4134_ = v___x_4352_;
v___y_4135_ = v___y_4346_;
v___y_4136_ = v___y_4347_;
v___y_4137_ = v___x_4351_;
v___y_4138_ = v___y_4348_;
v___y_4139_ = v___x_4361_;
goto v___jp_4131_;
}
else
{
uint64_t v___x_4362_; 
v___x_4362_ = 46ULL;
v___y_4132_ = v___x_4354_;
v___y_4133_ = v___y_4344_;
v___y_4134_ = v___x_4352_;
v___y_4135_ = v___y_4346_;
v___y_4136_ = v___y_4347_;
v___y_4137_ = v___x_4351_;
v___y_4138_ = v___y_4348_;
v___y_4139_ = v___x_4362_;
goto v___jp_4131_;
}
}
}
}
else
{
if (v___y_4344_ == 0)
{
uint32_t v___x_4363_; 
v___x_4363_ = 0;
return v___x_4363_;
}
else
{
uint32_t v___x_4364_; 
v___x_4364_ = 2147483648;
return v___x_4364_;
}
}
}
v___jp_4365_:
{
uint64_t v___x_4374_; uint64_t v___x_4375_; uint8_t v___x_4376_; 
v___x_4374_ = lean_uint32_to_uint64(v___y_4367_);
v___x_4375_ = 0ULL;
v___x_4376_ = lean_uint64_dec_eq(v___x_4374_, v___x_4375_);
if (v___x_4376_ == 0)
{
uint64_t v___x_4377_; uint64_t v___x_4378_; 
v___x_4377_ = 1ULL;
v___x_4378_ = lean_uint64_sub(v___x_4374_, v___x_4377_);
v___y_4343_ = v___y_4366_;
v___y_4344_ = v___y_4368_;
v___y_4345_ = v___y_4369_;
v___y_4346_ = v___y_4370_;
v___y_4347_ = v___y_4371_;
v___y_4348_ = v___y_4372_;
v___y_4349_ = v___y_4373_;
v___y_4350_ = v___x_4378_;
goto v___jp_4342_;
}
else
{
v___y_4343_ = v___y_4366_;
v___y_4344_ = v___y_4368_;
v___y_4345_ = v___y_4369_;
v___y_4346_ = v___y_4370_;
v___y_4347_ = v___y_4371_;
v___y_4348_ = v___y_4372_;
v___y_4349_ = v___y_4373_;
v___y_4350_ = v___x_4375_;
goto v___jp_4342_;
}
}
v___jp_4379_:
{
uint64_t v___x_4388_; uint64_t v___x_4389_; uint8_t v___x_4390_; 
v___x_4388_ = lean_uint32_to_uint64(v___y_4380_);
v___x_4389_ = 0ULL;
v___x_4390_ = lean_uint64_dec_eq(v___x_4388_, v___x_4389_);
if (v___x_4390_ == 0)
{
uint64_t v___x_4391_; uint64_t v___x_4392_; 
v___x_4391_ = 1ULL;
v___x_4392_ = lean_uint64_sub(v___x_4388_, v___x_4391_);
v___y_4366_ = v___y_4387_;
v___y_4367_ = v___y_4381_;
v___y_4368_ = v___y_4382_;
v___y_4369_ = v___y_4383_;
v___y_4370_ = v___y_4384_;
v___y_4371_ = v___y_4385_;
v___y_4372_ = v___y_4386_;
v___y_4373_ = v___x_4392_;
goto v___jp_4365_;
}
else
{
v___y_4366_ = v___y_4387_;
v___y_4367_ = v___y_4381_;
v___y_4368_ = v___y_4382_;
v___y_4369_ = v___y_4383_;
v___y_4370_ = v___y_4384_;
v___y_4371_ = v___y_4385_;
v___y_4372_ = v___y_4386_;
v___y_4373_ = v___x_4389_;
goto v___jp_4365_;
}
}
v___jp_4393_:
{
uint32_t v___x_4402_; uint8_t v___x_4403_; 
v___x_4402_ = 0;
v___x_4403_ = lean_uint32_dec_eq(v___y_4396_, v___x_4402_);
if (v___x_4403_ == 0)
{
uint64_t v___x_4404_; uint64_t v___x_4405_; uint64_t v___x_4406_; 
v___x_4404_ = lean_uint32_to_uint64(v___y_4394_);
v___x_4405_ = 8388608ULL;
v___x_4406_ = lean_uint64_lor(v___x_4404_, v___x_4405_);
v___y_4380_ = v___y_4395_;
v___y_4381_ = v___y_4396_;
v___y_4382_ = v___y_4397_;
v___y_4383_ = v___y_4401_;
v___y_4384_ = v___y_4398_;
v___y_4385_ = v___y_4399_;
v___y_4386_ = v___y_4400_;
v___y_4387_ = v___x_4406_;
goto v___jp_4379_;
}
else
{
uint64_t v___x_4407_; 
v___x_4407_ = lean_uint32_to_uint64(v___y_4394_);
v___y_4380_ = v___y_4395_;
v___y_4381_ = v___y_4396_;
v___y_4382_ = v___y_4397_;
v___y_4383_ = v___y_4401_;
v___y_4384_ = v___y_4398_;
v___y_4385_ = v___y_4399_;
v___y_4386_ = v___y_4400_;
v___y_4387_ = v___x_4407_;
goto v___jp_4379_;
}
}
v___jp_4408_:
{
uint32_t v___x_4414_; uint32_t v_xFraction_4415_; uint32_t v_yFraction_4416_; uint32_t v___x_4417_; uint8_t v___x_4418_; 
v___x_4414_ = 8388607;
v_xFraction_4415_ = lean_uint32_land(v_x_4041_, v___x_4414_);
v_yFraction_4416_ = lean_uint32_land(v_y_4042_, v___x_4414_);
v___x_4417_ = 0;
v___x_4418_ = lean_uint32_dec_eq(v___y_4409_, v___x_4417_);
if (v___x_4418_ == 0)
{
uint64_t v___x_4419_; uint64_t v___x_4420_; uint64_t v___x_4421_; 
v___x_4419_ = lean_uint32_to_uint64(v_xFraction_4415_);
v___x_4420_ = 8388608ULL;
v___x_4421_ = lean_uint64_lor(v___x_4419_, v___x_4420_);
v___y_4394_ = v_yFraction_4416_;
v___y_4395_ = v___y_4409_;
v___y_4396_ = v___y_4410_;
v___y_4397_ = v___y_4413_;
v___y_4398_ = v___y_4411_;
v___y_4399_ = v___x_4414_;
v___y_4400_ = v___y_4412_;
v___y_4401_ = v___x_4421_;
goto v___jp_4393_;
}
else
{
uint64_t v___x_4422_; 
v___x_4422_ = lean_uint32_to_uint64(v_xFraction_4415_);
v___y_4394_ = v_yFraction_4416_;
v___y_4395_ = v___y_4409_;
v___y_4396_ = v___y_4410_;
v___y_4397_ = v___y_4413_;
v___y_4398_ = v___y_4411_;
v___y_4399_ = v___x_4414_;
v___y_4400_ = v___y_4412_;
v___y_4401_ = v___x_4422_;
goto v___jp_4393_;
}
}
v___jp_4423_:
{
uint8_t v___x_4428_; 
v___x_4428_ = 1;
v___y_4409_ = v___y_4424_;
v___y_4410_ = v___y_4425_;
v___y_4411_ = v___y_4426_;
v___y_4412_ = v___y_4427_;
v___y_4413_ = v___x_4428_;
goto v___jp_4408_;
}
v___jp_4429_:
{
if (v___y_4433_ == 0)
{
if (v___y_4436_ == 0)
{
v___y_4409_ = v___y_4430_;
v___y_4410_ = v___y_4431_;
v___y_4411_ = v___y_4434_;
v___y_4412_ = v___y_4435_;
v___y_4413_ = v___y_4432_;
goto v___jp_4408_;
}
else
{
v___y_4424_ = v___y_4430_;
v___y_4425_ = v___y_4431_;
v___y_4426_ = v___y_4434_;
v___y_4427_ = v___y_4435_;
goto v___jp_4423_;
}
}
else
{
if (v___y_4436_ == 0)
{
v___y_4424_ = v___y_4430_;
v___y_4425_ = v___y_4431_;
v___y_4426_ = v___y_4434_;
v___y_4427_ = v___y_4435_;
goto v___jp_4423_;
}
else
{
v___y_4409_ = v___y_4430_;
v___y_4410_ = v___y_4431_;
v___y_4411_ = v___y_4434_;
v___y_4412_ = v___y_4435_;
v___y_4413_ = v___y_4432_;
goto v___jp_4408_;
}
}
}
v___jp_4437_:
{
uint32_t v___x_4444_; uint32_t v___x_4445_; uint32_t v___x_4446_; uint8_t v___x_4447_; 
v___x_4444_ = 2147483648;
v___x_4445_ = lean_uint32_land(v_y_4042_, v___x_4444_);
v___x_4446_ = 0;
v___x_4447_ = lean_uint32_dec_eq(v___x_4445_, v___x_4446_);
if (v___x_4447_ == 0)
{
uint8_t v___x_4448_; 
v___x_4448_ = 1;
v___y_4430_ = v___y_4438_;
v___y_4431_ = v___y_4440_;
v___y_4432_ = v___y_4439_;
v___y_4433_ = v___y_4443_;
v___y_4434_ = v___y_4441_;
v___y_4435_ = v___y_4442_;
v___y_4436_ = v___x_4448_;
goto v___jp_4429_;
}
else
{
v___y_4430_ = v___y_4438_;
v___y_4431_ = v___y_4440_;
v___y_4432_ = v___y_4439_;
v___y_4433_ = v___y_4443_;
v___y_4434_ = v___y_4441_;
v___y_4435_ = v___y_4442_;
v___y_4436_ = v___y_4439_;
goto v___jp_4429_;
}
}
v___jp_4449_:
{
if (v___y_4450_ == 0)
{
uint32_t v___x_4451_; uint32_t v___x_4452_; uint32_t v___x_4453_; uint32_t v_xExponent_4454_; uint32_t v___x_4455_; uint32_t v_yExponent_4456_; uint32_t v___x_4457_; uint32_t v___x_4458_; uint32_t v___x_4459_; uint8_t v___x_4460_; 
v___x_4451_ = 23;
v___x_4452_ = lean_uint32_shift_right(v_x_4041_, v___x_4451_);
v___x_4453_ = 255;
v_xExponent_4454_ = lean_uint32_land(v___x_4452_, v___x_4453_);
v___x_4455_ = lean_uint32_shift_right(v_y_4042_, v___x_4451_);
v_yExponent_4456_ = lean_uint32_land(v___x_4455_, v___x_4453_);
v___x_4457_ = 2147483648;
v___x_4458_ = lean_uint32_land(v_x_4041_, v___x_4457_);
v___x_4459_ = 0;
v___x_4460_ = lean_uint32_dec_eq(v___x_4458_, v___x_4459_);
if (v___x_4460_ == 0)
{
uint8_t v___x_4461_; 
v___x_4461_ = 1;
v___y_4438_ = v_xExponent_4454_;
v___y_4439_ = v___y_4450_;
v___y_4440_ = v_yExponent_4456_;
v___y_4441_ = v___x_4453_;
v___y_4442_ = v___x_4451_;
v___y_4443_ = v___x_4461_;
goto v___jp_4437_;
}
else
{
v___y_4438_ = v_xExponent_4454_;
v___y_4439_ = v___y_4450_;
v___y_4440_ = v_yExponent_4456_;
v___y_4441_ = v___x_4453_;
v___y_4442_ = v___x_4451_;
v___y_4443_ = v___y_4450_;
goto v___jp_4437_;
}
}
else
{
lean_object* v___x_4462_; lean_object* v___x_4463_; lean_object* v___x_4464_; lean_object* v___x_4465_; uint32_t v___x_4466_; 
v___x_4462_ = ((lean_object*)(lp_competition_Submission_TunedAdd_Fmt___closed__0));
v___x_4463_ = lean_uint32_to_nat(v_x_4041_);
v___x_4464_ = lean_uint32_to_nat(v_y_4042_);
v___x_4465_ = lp_floatlib_FloatLib_Floats_Formats_BinaryInterchange_Model_MulBackend_word(v___x_4462_, v___x_4463_, v___x_4464_);
v___x_4466_ = lean_uint32_of_nat(v___x_4465_);
lean_dec(v___x_4465_);
return v___x_4466_;
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_R6NormalMul_mul___boxed(lean_object* v_x_4473_, lean_object* v_y_4474_){
_start:
{
uint32_t v_x_boxed_4475_; uint32_t v_y_boxed_4476_; uint32_t v_res_4477_; lean_object* v_r_4478_; 
v_x_boxed_4475_ = lean_unbox_uint32(v_x_4473_);
lean_dec(v_x_4473_);
v_y_boxed_4476_ = lean_unbox_uint32(v_y_4474_);
lean_dec(v_y_4474_);
v_res_4477_ = lp_competition_Submission_R6NormalMul_mul(v_x_boxed_4475_, v_y_boxed_4476_);
v_r_4478_ = lean_box_uint32(v_res_4477_);
return v_r_4478_;
}
}
LEAN_EXPORT uint32_t lp_competition_Submission_LowScale_roundLow(uint8_t v_sign_4479_, uint64_t v_product_4480_, uint64_t v_scale_4481_){
_start:
{
uint32_t v___y_4483_; uint32_t v___y_4487_; uint32_t v___y_4488_; uint64_t v___x_4492_; uint64_t v___y_4494_; uint8_t v___x_4505_; 
v___x_4492_ = 0ULL;
v___x_4505_ = lean_uint64_dec_eq(v_product_4480_, v___x_4492_);
if (v___x_4505_ == 0)
{
uint64_t v___x_4506_; uint64_t v___x_4507_; uint8_t v___x_4508_; 
v___x_4506_ = 149ULL;
v___x_4507_ = lean_uint64_sub(v___x_4506_, v_scale_4481_);
v___x_4508_ = lean_uint64_dec_eq(v___x_4507_, v___x_4492_);
if (v___x_4508_ == 0)
{
uint64_t v___x_4509_; uint8_t v___x_4510_; 
v___x_4509_ = 64ULL;
v___x_4510_ = lean_uint64_dec_lt(v___x_4507_, v___x_4509_);
if (v___x_4510_ == 0)
{
uint8_t v___x_4511_; 
v___x_4511_ = lean_uint64_dec_eq(v___x_4507_, v___x_4509_);
if (v___x_4511_ == 0)
{
v___y_4494_ = v___x_4492_;
goto v___jp_4493_;
}
else
{
uint64_t v___x_4512_; uint8_t v___x_4513_; 
v___x_4512_ = 9223372036854775808ULL;
v___x_4513_ = lean_uint64_dec_lt(v___x_4512_, v_product_4480_);
if (v___x_4513_ == 0)
{
v___y_4494_ = v___x_4492_;
goto v___jp_4493_;
}
else
{
uint64_t v___x_4514_; 
v___x_4514_ = 1ULL;
v___y_4494_ = v___x_4514_;
goto v___jp_4493_;
}
}
}
else
{
uint64_t v_quotient_4515_; uint64_t v___x_4516_; uint64_t v___x_4517_; uint64_t v___x_4518_; uint64_t v_remainder_4519_; uint64_t v___x_4520_; uint64_t v_half_4521_; uint8_t v___x_4522_; 
v_quotient_4515_ = lean_uint64_shift_right(v_product_4480_, v___x_4507_);
v___x_4516_ = 1ULL;
v___x_4517_ = lean_uint64_shift_left(v___x_4516_, v___x_4507_);
v___x_4518_ = lean_uint64_sub(v___x_4517_, v___x_4516_);
v_remainder_4519_ = lean_uint64_land(v_product_4480_, v___x_4518_);
v___x_4520_ = lean_uint64_sub(v___x_4507_, v___x_4516_);
v_half_4521_ = lean_uint64_shift_left(v___x_4516_, v___x_4520_);
v___x_4522_ = lean_uint64_dec_lt(v_remainder_4519_, v_half_4521_);
if (v___x_4522_ == 0)
{
uint8_t v___x_4523_; 
v___x_4523_ = lean_uint64_dec_lt(v_half_4521_, v_remainder_4519_);
if (v___x_4523_ == 0)
{
uint64_t v___x_4524_; uint8_t v___x_4525_; 
v___x_4524_ = lean_uint64_land(v_quotient_4515_, v___x_4516_);
v___x_4525_ = lean_uint64_dec_eq(v___x_4524_, v___x_4492_);
if (v___x_4525_ == 0)
{
uint64_t v___x_4526_; 
v___x_4526_ = lean_uint64_add(v_quotient_4515_, v___x_4516_);
v___y_4494_ = v___x_4526_;
goto v___jp_4493_;
}
else
{
v___y_4494_ = v_quotient_4515_;
goto v___jp_4493_;
}
}
else
{
uint64_t v___x_4527_; 
v___x_4527_ = lean_uint64_add(v_quotient_4515_, v___x_4516_);
v___y_4494_ = v___x_4527_;
goto v___jp_4493_;
}
}
else
{
v___y_4494_ = v_quotient_4515_;
goto v___jp_4493_;
}
}
}
else
{
v___y_4494_ = v_product_4480_;
goto v___jp_4493_;
}
}
else
{
if (v_sign_4479_ == 0)
{
uint32_t v___x_4528_; 
v___x_4528_ = 0;
return v___x_4528_;
}
else
{
uint32_t v___x_4529_; 
v___x_4529_ = 2147483648;
return v___x_4529_;
}
}
v___jp_4482_:
{
uint32_t v___x_4484_; uint32_t v___x_4485_; 
v___x_4484_ = 8388608;
v___x_4485_ = lean_uint32_lor(v___y_4483_, v___x_4484_);
return v___x_4485_;
}
v___jp_4486_:
{
uint32_t v___x_4489_; uint32_t v___x_4490_; uint32_t v___x_4491_; 
v___x_4489_ = 8388607;
v___x_4490_ = lean_uint32_land(v___y_4487_, v___x_4489_);
v___x_4491_ = lean_uint32_lor(v___y_4488_, v___x_4490_);
return v___x_4491_;
}
v___jp_4493_:
{
uint8_t v___x_4495_; 
v___x_4495_ = lean_uint64_dec_eq(v___y_4494_, v___x_4492_);
if (v___x_4495_ == 0)
{
uint64_t v___x_4496_; uint8_t v___x_4497_; 
v___x_4496_ = 8388608ULL;
v___x_4497_ = lean_uint64_dec_eq(v___y_4494_, v___x_4496_);
if (v___x_4497_ == 0)
{
uint32_t v___x_4498_; 
v___x_4498_ = lean_uint64_to_uint32(v___y_4494_);
if (v_sign_4479_ == 0)
{
uint32_t v___x_4499_; 
v___x_4499_ = 0;
v___y_4487_ = v___x_4498_;
v___y_4488_ = v___x_4499_;
goto v___jp_4486_;
}
else
{
uint32_t v___x_4500_; 
v___x_4500_ = 2147483648;
v___y_4487_ = v___x_4498_;
v___y_4488_ = v___x_4500_;
goto v___jp_4486_;
}
}
else
{
if (v_sign_4479_ == 0)
{
uint32_t v___x_4501_; 
v___x_4501_ = 0;
v___y_4483_ = v___x_4501_;
goto v___jp_4482_;
}
else
{
uint32_t v___x_4502_; 
v___x_4502_ = 2147483648;
v___y_4483_ = v___x_4502_;
goto v___jp_4482_;
}
}
}
else
{
if (v_sign_4479_ == 0)
{
uint32_t v___x_4503_; 
v___x_4503_ = 0;
return v___x_4503_;
}
else
{
uint32_t v___x_4504_; 
v___x_4504_ = 2147483648;
return v___x_4504_;
}
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_LowScale_roundLow___boxed(lean_object* v_sign_4530_, lean_object* v_product_4531_, lean_object* v_scale_4532_){
_start:
{
uint8_t v_sign_boxed_4533_; uint64_t v_product_boxed_4534_; uint64_t v_scale_boxed_4535_; uint32_t v_res_4536_; lean_object* v_r_4537_; 
v_sign_boxed_4533_ = lean_unbox(v_sign_4530_);
v_product_boxed_4534_ = lean_unbox_uint64(v_product_4531_);
lean_dec_ref(v_product_4531_);
v_scale_boxed_4535_ = lean_unbox_uint64(v_scale_4532_);
lean_dec_ref(v_scale_4532_);
v_res_4536_ = lp_competition_Submission_LowScale_roundLow(v_sign_boxed_4533_, v_product_boxed_4534_, v_scale_boxed_4535_);
v_r_4537_ = lean_box_uint32(v_res_4536_);
return v_r_4537_;
}
}
LEAN_EXPORT uint32_t lp_competition_Submission_LowScale_roundSelect(uint8_t v_sign_4538_, uint64_t v_product_4539_, uint64_t v_scale_4540_){
_start:
{
uint32_t v___y_4542_; uint32_t v___y_4546_; uint32_t v___y_4547_; uint32_t v___y_4552_; uint32_t v___y_4556_; uint32_t v___y_4557_; uint64_t v___y_4562_; uint64_t v___y_4563_; uint32_t v___y_4575_; uint32_t v___y_4576_; uint32_t v___y_4577_; uint32_t v___y_4587_; uint32_t v___y_4588_; uint64_t v___y_4592_; uint64_t v___y_4593_; uint64_t v___y_4594_; uint64_t v___y_4604_; uint64_t v___y_4605_; uint8_t v___y_4606_; uint64_t v___y_4607_; uint64_t v___y_4614_; uint64_t v___y_4615_; uint64_t v___y_4616_; uint64_t v___y_4622_; uint64_t v___y_4623_; uint64_t v___y_4678_; uint64_t v___y_4679_; uint64_t v___y_4680_; uint64_t v___y_4686_; uint64_t v___y_4687_; uint64_t v___y_4688_; uint64_t v___y_4689_; uint64_t v___y_4690_; uint64_t v___y_4695_; uint64_t v___y_4696_; uint64_t v___y_4697_; uint64_t v___y_4702_; uint64_t v___y_4703_; uint64_t v___y_4704_; uint64_t v___y_4705_; uint64_t v___y_4706_; uint64_t v___y_4711_; uint64_t v___y_4712_; uint64_t v___y_4713_; uint64_t v___y_4718_; uint64_t v___y_4719_; uint64_t v___y_4720_; uint64_t v___y_4721_; uint64_t v___y_4722_; uint64_t v___y_4727_; uint64_t v___y_4728_; uint64_t v___y_4729_; uint64_t v___y_4734_; uint64_t v___y_4735_; uint64_t v___y_4736_; uint64_t v___y_4737_; uint64_t v___y_4738_; uint64_t v___y_4743_; uint64_t v___y_4744_; uint64_t v___y_4745_; uint64_t v___y_4750_; uint64_t v___y_4751_; uint64_t v___y_4752_; uint64_t v___x_4763_; uint8_t v___x_4764_; 
v___x_4763_ = 281474976710656ULL;
v___x_4764_ = lean_uint64_dec_lt(v_product_4539_, v___x_4763_);
if (v___x_4764_ == 0)
{
goto v___jp_4755_;
}
else
{
uint64_t v___x_4765_; uint8_t v___x_4766_; 
v___x_4765_ = 123ULL;
v___x_4766_ = lean_uint64_dec_le(v_scale_4540_, v___x_4765_);
if (v___x_4766_ == 0)
{
goto v___jp_4755_;
}
else
{
uint64_t v___x_4767_; uint64_t v___y_4769_; uint8_t v___x_4780_; 
v___x_4767_ = 0ULL;
v___x_4780_ = lean_uint64_dec_eq(v_product_4539_, v___x_4767_);
if (v___x_4780_ == 0)
{
uint64_t v___x_4781_; uint64_t v___x_4782_; uint8_t v___x_4783_; 
v___x_4781_ = 149ULL;
v___x_4782_ = lean_uint64_sub(v___x_4781_, v_scale_4540_);
v___x_4783_ = lean_uint64_dec_eq(v___x_4782_, v___x_4767_);
if (v___x_4783_ == 0)
{
uint64_t v___x_4784_; uint8_t v___x_4785_; 
v___x_4784_ = 64ULL;
v___x_4785_ = lean_uint64_dec_lt(v___x_4782_, v___x_4784_);
if (v___x_4785_ == 0)
{
uint8_t v___x_4786_; 
v___x_4786_ = lean_uint64_dec_eq(v___x_4782_, v___x_4784_);
if (v___x_4786_ == 0)
{
v___y_4769_ = v___x_4767_;
goto v___jp_4768_;
}
else
{
uint64_t v___x_4787_; uint8_t v___x_4788_; 
v___x_4787_ = 9223372036854775808ULL;
v___x_4788_ = lean_uint64_dec_lt(v___x_4787_, v_product_4539_);
if (v___x_4788_ == 0)
{
v___y_4769_ = v___x_4767_;
goto v___jp_4768_;
}
else
{
uint64_t v___x_4789_; 
v___x_4789_ = 1ULL;
v___y_4769_ = v___x_4789_;
goto v___jp_4768_;
}
}
}
else
{
uint64_t v_quotient_4790_; uint64_t v___x_4791_; uint64_t v___x_4792_; uint64_t v___x_4793_; uint64_t v_remainder_4794_; uint64_t v___x_4795_; uint64_t v_half_4796_; uint8_t v___x_4797_; 
v_quotient_4790_ = lean_uint64_shift_right(v_product_4539_, v___x_4782_);
v___x_4791_ = 1ULL;
v___x_4792_ = lean_uint64_shift_left(v___x_4791_, v___x_4782_);
v___x_4793_ = lean_uint64_sub(v___x_4792_, v___x_4791_);
v_remainder_4794_ = lean_uint64_land(v_product_4539_, v___x_4793_);
v___x_4795_ = lean_uint64_sub(v___x_4782_, v___x_4791_);
v_half_4796_ = lean_uint64_shift_left(v___x_4791_, v___x_4795_);
v___x_4797_ = lean_uint64_dec_lt(v_remainder_4794_, v_half_4796_);
if (v___x_4797_ == 0)
{
uint8_t v___x_4798_; 
v___x_4798_ = lean_uint64_dec_lt(v_half_4796_, v_remainder_4794_);
if (v___x_4798_ == 0)
{
uint64_t v___x_4799_; uint8_t v___x_4800_; 
v___x_4799_ = lean_uint64_land(v_quotient_4790_, v___x_4791_);
v___x_4800_ = lean_uint64_dec_eq(v___x_4799_, v___x_4767_);
if (v___x_4800_ == 0)
{
uint64_t v___x_4801_; 
v___x_4801_ = lean_uint64_add(v_quotient_4790_, v___x_4791_);
v___y_4769_ = v___x_4801_;
goto v___jp_4768_;
}
else
{
v___y_4769_ = v_quotient_4790_;
goto v___jp_4768_;
}
}
else
{
uint64_t v___x_4802_; 
v___x_4802_ = lean_uint64_add(v_quotient_4790_, v___x_4791_);
v___y_4769_ = v___x_4802_;
goto v___jp_4768_;
}
}
else
{
v___y_4769_ = v_quotient_4790_;
goto v___jp_4768_;
}
}
}
else
{
v___y_4769_ = v_product_4539_;
goto v___jp_4768_;
}
}
else
{
if (v_sign_4538_ == 0)
{
uint32_t v___x_4803_; 
v___x_4803_ = 0;
return v___x_4803_;
}
else
{
uint32_t v___x_4804_; 
v___x_4804_ = 2147483648;
return v___x_4804_;
}
}
v___jp_4768_:
{
uint8_t v___x_4770_; 
v___x_4770_ = lean_uint64_dec_eq(v___y_4769_, v___x_4767_);
if (v___x_4770_ == 0)
{
uint64_t v___x_4771_; uint8_t v___x_4772_; 
v___x_4771_ = 8388608ULL;
v___x_4772_ = lean_uint64_dec_eq(v___y_4769_, v___x_4771_);
if (v___x_4772_ == 0)
{
uint32_t v___x_4773_; 
v___x_4773_ = lean_uint64_to_uint32(v___y_4769_);
if (v_sign_4538_ == 0)
{
uint32_t v___x_4774_; 
v___x_4774_ = 0;
v___y_4546_ = v___x_4773_;
v___y_4547_ = v___x_4774_;
goto v___jp_4545_;
}
else
{
uint32_t v___x_4775_; 
v___x_4775_ = 2147483648;
v___y_4546_ = v___x_4773_;
v___y_4547_ = v___x_4775_;
goto v___jp_4545_;
}
}
else
{
if (v_sign_4538_ == 0)
{
uint32_t v___x_4776_; 
v___x_4776_ = 0;
v___y_4542_ = v___x_4776_;
goto v___jp_4541_;
}
else
{
uint32_t v___x_4777_; 
v___x_4777_ = 2147483648;
v___y_4542_ = v___x_4777_;
goto v___jp_4541_;
}
}
}
else
{
if (v_sign_4538_ == 0)
{
uint32_t v___x_4778_; 
v___x_4778_ = 0;
return v___x_4778_;
}
else
{
uint32_t v___x_4779_; 
v___x_4779_ = 2147483648;
return v___x_4779_;
}
}
}
}
}
v___jp_4541_:
{
uint32_t v___x_4543_; uint32_t v___x_4544_; 
v___x_4543_ = 8388608;
v___x_4544_ = lean_uint32_lor(v___y_4542_, v___x_4543_);
return v___x_4544_;
}
v___jp_4545_:
{
uint32_t v___x_4548_; uint32_t v___x_4549_; uint32_t v___x_4550_; 
v___x_4548_ = 8388607;
v___x_4549_ = lean_uint32_land(v___y_4546_, v___x_4548_);
v___x_4550_ = lean_uint32_lor(v___y_4547_, v___x_4549_);
return v___x_4550_;
}
v___jp_4551_:
{
uint32_t v___x_4553_; uint32_t v___x_4554_; 
v___x_4553_ = 8388608;
v___x_4554_ = lean_uint32_lor(v___y_4552_, v___x_4553_);
return v___x_4554_;
}
v___jp_4555_:
{
uint32_t v___x_4558_; uint32_t v___x_4559_; uint32_t v___x_4560_; 
v___x_4558_ = 8388607;
v___x_4559_ = lean_uint32_land(v___y_4556_, v___x_4558_);
v___x_4560_ = lean_uint32_lor(v___y_4557_, v___x_4559_);
return v___x_4560_;
}
v___jp_4561_:
{
uint8_t v___x_4564_; 
v___x_4564_ = lean_uint64_dec_eq(v___y_4563_, v___y_4562_);
if (v___x_4564_ == 0)
{
uint64_t v___x_4565_; uint8_t v___x_4566_; 
v___x_4565_ = 8388608ULL;
v___x_4566_ = lean_uint64_dec_eq(v___y_4563_, v___x_4565_);
if (v___x_4566_ == 0)
{
uint32_t v___x_4567_; 
v___x_4567_ = lean_uint64_to_uint32(v___y_4563_);
if (v_sign_4538_ == 0)
{
uint32_t v___x_4568_; 
v___x_4568_ = 0;
v___y_4556_ = v___x_4567_;
v___y_4557_ = v___x_4568_;
goto v___jp_4555_;
}
else
{
uint32_t v___x_4569_; 
v___x_4569_ = 2147483648;
v___y_4556_ = v___x_4567_;
v___y_4557_ = v___x_4569_;
goto v___jp_4555_;
}
}
else
{
if (v_sign_4538_ == 0)
{
uint32_t v___x_4570_; 
v___x_4570_ = 0;
v___y_4552_ = v___x_4570_;
goto v___jp_4551_;
}
else
{
uint32_t v___x_4571_; 
v___x_4571_ = 2147483648;
v___y_4552_ = v___x_4571_;
goto v___jp_4551_;
}
}
}
else
{
if (v_sign_4538_ == 0)
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
v___jp_4574_:
{
uint32_t v___x_4578_; uint32_t v___x_4579_; uint32_t v___x_4580_; uint32_t v___x_4581_; uint32_t v___x_4582_; uint32_t v___x_4583_; uint32_t v___x_4584_; uint32_t v___x_4585_; 
v___x_4578_ = 255;
v___x_4579_ = lean_uint32_land(v___y_4576_, v___x_4578_);
v___x_4580_ = 23;
v___x_4581_ = lean_uint32_shift_left(v___x_4579_, v___x_4580_);
v___x_4582_ = lean_uint32_lor(v___y_4577_, v___x_4581_);
v___x_4583_ = 8388607;
v___x_4584_ = lean_uint32_land(v___y_4575_, v___x_4583_);
v___x_4585_ = lean_uint32_lor(v___x_4582_, v___x_4584_);
return v___x_4585_;
}
v___jp_4586_:
{
if (v_sign_4538_ == 0)
{
uint32_t v___x_4589_; 
v___x_4589_ = 0;
v___y_4575_ = v___y_4588_;
v___y_4576_ = v___y_4587_;
v___y_4577_ = v___x_4589_;
goto v___jp_4574_;
}
else
{
uint32_t v___x_4590_; 
v___x_4590_ = 2147483648;
v___y_4575_ = v___y_4588_;
v___y_4576_ = v___y_4587_;
v___y_4577_ = v___x_4590_;
goto v___jp_4574_;
}
}
v___jp_4591_:
{
uint64_t v___x_4595_; uint64_t v_encodedExponent_4596_; uint32_t v___x_4597_; uint64_t v___x_4598_; uint8_t v___x_4599_; 
v___x_4595_ = 171ULL;
v_encodedExponent_4596_ = lean_uint64_sub(v___y_4593_, v___x_4595_);
v___x_4597_ = lean_uint64_to_uint32(v_encodedExponent_4596_);
v___x_4598_ = 8388608ULL;
v___x_4599_ = lean_uint64_dec_lt(v___y_4594_, v___x_4598_);
if (v___x_4599_ == 0)
{
uint64_t v___x_4600_; uint32_t v___x_4601_; 
v___x_4600_ = lean_uint64_sub(v___y_4594_, v___x_4598_);
v___x_4601_ = lean_uint64_to_uint32(v___x_4600_);
v___y_4587_ = v___x_4597_;
v___y_4588_ = v___x_4601_;
goto v___jp_4586_;
}
else
{
uint32_t v___x_4602_; 
v___x_4602_ = lean_uint64_to_uint32(v___y_4592_);
v___y_4587_ = v___x_4597_;
v___y_4588_ = v___x_4602_;
goto v___jp_4586_;
}
}
v___jp_4603_:
{
uint64_t v___x_4608_; uint8_t v___x_4609_; 
v___x_4608_ = 425ULL;
v___x_4609_ = lean_uint64_dec_lt(v___x_4608_, v___y_4607_);
if (v___x_4609_ == 0)
{
if (v___y_4606_ == 0)
{
v___y_4592_ = v___y_4604_;
v___y_4593_ = v___y_4607_;
v___y_4594_ = v___y_4605_;
goto v___jp_4591_;
}
else
{
uint64_t v___x_4610_; 
v___x_4610_ = 8388608ULL;
v___y_4592_ = v___y_4604_;
v___y_4593_ = v___y_4607_;
v___y_4594_ = v___x_4610_;
goto v___jp_4591_;
}
}
else
{
if (v_sign_4538_ == 0)
{
uint32_t v___x_4611_; 
v___x_4611_ = 2139095040;
return v___x_4611_;
}
else
{
uint32_t v___x_4612_; 
v___x_4612_ = 4286578688;
return v___x_4612_;
}
}
}
v___jp_4613_:
{
uint64_t v___x_4617_; uint8_t v_carry_4618_; 
v___x_4617_ = 16777216ULL;
v_carry_4618_ = lean_uint64_dec_eq(v___y_4616_, v___x_4617_);
if (v_carry_4618_ == 0)
{
v___y_4604_ = v___y_4614_;
v___y_4605_ = v___y_4616_;
v___y_4606_ = v_carry_4618_;
v___y_4607_ = v___y_4615_;
goto v___jp_4603_;
}
else
{
uint64_t v___x_4619_; uint64_t v___x_4620_; 
v___x_4619_ = 1ULL;
v___x_4620_ = lean_uint64_add(v___y_4615_, v___x_4619_);
v___y_4604_ = v___y_4614_;
v___y_4605_ = v___y_4616_;
v___y_4606_ = v_carry_4618_;
v___y_4607_ = v___x_4620_;
goto v___jp_4603_;
}
}
v___jp_4621_:
{
uint64_t v_position_4624_; uint64_t v___x_4625_; uint8_t v___x_4626_; 
v_position_4624_ = lean_uint64_add(v___y_4623_, v_scale_4540_);
v___x_4625_ = 172ULL;
v___x_4626_ = lean_uint64_dec_lt(v_position_4624_, v___x_4625_);
if (v___x_4626_ == 0)
{
uint64_t v___x_4627_; uint8_t v___x_4628_; 
v___x_4627_ = 23ULL;
v___x_4628_ = lean_uint64_dec_lt(v___y_4623_, v___x_4627_);
if (v___x_4628_ == 0)
{
uint64_t v___x_4629_; uint8_t v___x_4630_; 
v___x_4629_ = lean_uint64_sub(v___y_4623_, v___x_4627_);
v___x_4630_ = lean_uint64_dec_eq(v___x_4629_, v___y_4622_);
if (v___x_4630_ == 0)
{
uint64_t v___x_4631_; uint8_t v___x_4632_; 
v___x_4631_ = 64ULL;
v___x_4632_ = lean_uint64_dec_lt(v___x_4629_, v___x_4631_);
if (v___x_4632_ == 0)
{
uint8_t v___x_4633_; 
v___x_4633_ = lean_uint64_dec_eq(v___x_4629_, v___x_4631_);
if (v___x_4633_ == 0)
{
v___y_4614_ = v___y_4622_;
v___y_4615_ = v_position_4624_;
v___y_4616_ = v___y_4622_;
goto v___jp_4613_;
}
else
{
uint64_t v___x_4634_; uint8_t v___x_4635_; 
v___x_4634_ = 9223372036854775808ULL;
v___x_4635_ = lean_uint64_dec_lt(v___x_4634_, v_product_4539_);
if (v___x_4635_ == 0)
{
v___y_4614_ = v___y_4622_;
v___y_4615_ = v_position_4624_;
v___y_4616_ = v___y_4622_;
goto v___jp_4613_;
}
else
{
uint64_t v___x_4636_; 
v___x_4636_ = 1ULL;
v___y_4614_ = v___y_4622_;
v___y_4615_ = v_position_4624_;
v___y_4616_ = v___x_4636_;
goto v___jp_4613_;
}
}
}
else
{
uint64_t v_quotient_4637_; uint64_t v___x_4638_; uint64_t v___x_4639_; uint64_t v___x_4640_; uint64_t v_remainder_4641_; uint64_t v___x_4642_; uint64_t v_half_4643_; uint8_t v___x_4644_; 
v_quotient_4637_ = lean_uint64_shift_right(v_product_4539_, v___x_4629_);
v___x_4638_ = 1ULL;
v___x_4639_ = lean_uint64_shift_left(v___x_4638_, v___x_4629_);
v___x_4640_ = lean_uint64_sub(v___x_4639_, v___x_4638_);
v_remainder_4641_ = lean_uint64_land(v_product_4539_, v___x_4640_);
v___x_4642_ = lean_uint64_sub(v___x_4629_, v___x_4638_);
v_half_4643_ = lean_uint64_shift_left(v___x_4638_, v___x_4642_);
v___x_4644_ = lean_uint64_dec_lt(v_remainder_4641_, v_half_4643_);
if (v___x_4644_ == 0)
{
uint8_t v___x_4645_; 
v___x_4645_ = lean_uint64_dec_lt(v_half_4643_, v_remainder_4641_);
if (v___x_4645_ == 0)
{
uint64_t v___x_4646_; uint8_t v___x_4647_; 
v___x_4646_ = lean_uint64_land(v_quotient_4637_, v___x_4638_);
v___x_4647_ = lean_uint64_dec_eq(v___x_4646_, v___y_4622_);
if (v___x_4647_ == 0)
{
uint64_t v___x_4648_; 
v___x_4648_ = lean_uint64_add(v_quotient_4637_, v___x_4638_);
v___y_4614_ = v___y_4622_;
v___y_4615_ = v_position_4624_;
v___y_4616_ = v___x_4648_;
goto v___jp_4613_;
}
else
{
v___y_4614_ = v___y_4622_;
v___y_4615_ = v_position_4624_;
v___y_4616_ = v_quotient_4637_;
goto v___jp_4613_;
}
}
else
{
uint64_t v___x_4649_; 
v___x_4649_ = lean_uint64_add(v_quotient_4637_, v___x_4638_);
v___y_4614_ = v___y_4622_;
v___y_4615_ = v_position_4624_;
v___y_4616_ = v___x_4649_;
goto v___jp_4613_;
}
}
else
{
v___y_4614_ = v___y_4622_;
v___y_4615_ = v_position_4624_;
v___y_4616_ = v_quotient_4637_;
goto v___jp_4613_;
}
}
}
else
{
v___y_4614_ = v___y_4622_;
v___y_4615_ = v_position_4624_;
v___y_4616_ = v_product_4539_;
goto v___jp_4613_;
}
}
else
{
uint64_t v___x_4650_; uint64_t v___x_4651_; 
v___x_4650_ = lean_uint64_sub(v___x_4627_, v___y_4623_);
v___x_4651_ = lean_uint64_shift_left(v_product_4539_, v___x_4650_);
v___y_4614_ = v___y_4622_;
v___y_4615_ = v_position_4624_;
v___y_4616_ = v___x_4651_;
goto v___jp_4613_;
}
}
else
{
uint64_t v___x_4652_; uint8_t v___x_4653_; 
v___x_4652_ = 149ULL;
v___x_4653_ = lean_uint64_dec_lt(v_scale_4540_, v___x_4652_);
if (v___x_4653_ == 0)
{
uint64_t v___x_4654_; uint64_t v___x_4655_; 
v___x_4654_ = lean_uint64_sub(v_scale_4540_, v___x_4652_);
v___x_4655_ = lean_uint64_shift_left(v_product_4539_, v___x_4654_);
v___y_4562_ = v___y_4622_;
v___y_4563_ = v___x_4655_;
goto v___jp_4561_;
}
else
{
uint64_t v___x_4656_; uint8_t v___x_4657_; 
v___x_4656_ = lean_uint64_sub(v___x_4652_, v_scale_4540_);
v___x_4657_ = lean_uint64_dec_eq(v___x_4656_, v___y_4622_);
if (v___x_4657_ == 0)
{
uint64_t v___x_4658_; uint8_t v___x_4659_; 
v___x_4658_ = 64ULL;
v___x_4659_ = lean_uint64_dec_lt(v___x_4656_, v___x_4658_);
if (v___x_4659_ == 0)
{
uint8_t v___x_4660_; 
v___x_4660_ = lean_uint64_dec_eq(v___x_4656_, v___x_4658_);
if (v___x_4660_ == 0)
{
v___y_4562_ = v___y_4622_;
v___y_4563_ = v___y_4622_;
goto v___jp_4561_;
}
else
{
uint64_t v___x_4661_; uint8_t v___x_4662_; 
v___x_4661_ = 9223372036854775808ULL;
v___x_4662_ = lean_uint64_dec_lt(v___x_4661_, v_product_4539_);
if (v___x_4662_ == 0)
{
v___y_4562_ = v___y_4622_;
v___y_4563_ = v___y_4622_;
goto v___jp_4561_;
}
else
{
uint64_t v___x_4663_; 
v___x_4663_ = 1ULL;
v___y_4562_ = v___y_4622_;
v___y_4563_ = v___x_4663_;
goto v___jp_4561_;
}
}
}
else
{
uint64_t v_quotient_4664_; uint64_t v___x_4665_; uint64_t v___x_4666_; uint64_t v___x_4667_; uint64_t v_remainder_4668_; uint64_t v___x_4669_; uint64_t v_half_4670_; uint8_t v___x_4671_; 
v_quotient_4664_ = lean_uint64_shift_right(v_product_4539_, v___x_4656_);
v___x_4665_ = 1ULL;
v___x_4666_ = lean_uint64_shift_left(v___x_4665_, v___x_4656_);
v___x_4667_ = lean_uint64_sub(v___x_4666_, v___x_4665_);
v_remainder_4668_ = lean_uint64_land(v_product_4539_, v___x_4667_);
v___x_4669_ = lean_uint64_sub(v___x_4656_, v___x_4665_);
v_half_4670_ = lean_uint64_shift_left(v___x_4665_, v___x_4669_);
v___x_4671_ = lean_uint64_dec_lt(v_remainder_4668_, v_half_4670_);
if (v___x_4671_ == 0)
{
uint8_t v___x_4672_; 
v___x_4672_ = lean_uint64_dec_lt(v_half_4670_, v_remainder_4668_);
if (v___x_4672_ == 0)
{
uint64_t v___x_4673_; uint8_t v___x_4674_; 
v___x_4673_ = lean_uint64_land(v_quotient_4664_, v___x_4665_);
v___x_4674_ = lean_uint64_dec_eq(v___x_4673_, v___y_4622_);
if (v___x_4674_ == 0)
{
uint64_t v___x_4675_; 
v___x_4675_ = lean_uint64_add(v_quotient_4664_, v___x_4665_);
v___y_4562_ = v___y_4622_;
v___y_4563_ = v___x_4675_;
goto v___jp_4561_;
}
else
{
v___y_4562_ = v___y_4622_;
v___y_4563_ = v_quotient_4664_;
goto v___jp_4561_;
}
}
else
{
uint64_t v___x_4676_; 
v___x_4676_ = lean_uint64_add(v_quotient_4664_, v___x_4665_);
v___y_4562_ = v___y_4622_;
v___y_4563_ = v___x_4676_;
goto v___jp_4561_;
}
}
else
{
v___y_4562_ = v___y_4622_;
v___y_4563_ = v_quotient_4664_;
goto v___jp_4561_;
}
}
}
else
{
v___y_4562_ = v___y_4622_;
v___y_4563_ = v_product_4539_;
goto v___jp_4561_;
}
}
}
}
v___jp_4677_:
{
uint64_t v___x_4681_; uint64_t v___x_4682_; uint8_t v___x_4683_; 
v___x_4681_ = 1ULL;
v___x_4682_ = lean_uint64_shift_right(v___y_4679_, v___x_4681_);
v___x_4683_ = lean_uint64_dec_eq(v___x_4682_, v___y_4678_);
if (v___x_4683_ == 0)
{
uint64_t v___x_4684_; 
v___x_4684_ = lean_uint64_add(v___y_4680_, v___x_4681_);
v___y_4622_ = v___y_4678_;
v___y_4623_ = v___x_4684_;
goto v___jp_4621_;
}
else
{
v___y_4622_ = v___y_4678_;
v___y_4623_ = v___y_4680_;
goto v___jp_4621_;
}
}
v___jp_4685_:
{
uint64_t v___x_4691_; uint8_t v___x_4692_; 
v___x_4691_ = lean_uint64_shift_right(v___y_4686_, v___y_4687_);
v___x_4692_ = lean_uint64_dec_eq(v___x_4691_, v___y_4689_);
if (v___x_4692_ == 0)
{
uint64_t v___x_4693_; 
v___x_4693_ = lean_uint64_add(v___y_4688_, v___y_4687_);
v___y_4678_ = v___y_4689_;
v___y_4679_ = v___y_4690_;
v___y_4680_ = v___x_4693_;
goto v___jp_4677_;
}
else
{
v___y_4678_ = v___y_4689_;
v___y_4679_ = v___y_4690_;
v___y_4680_ = v___y_4688_;
goto v___jp_4677_;
}
}
v___jp_4694_:
{
uint64_t v___x_4698_; uint64_t v___x_4699_; uint8_t v___x_4700_; 
v___x_4698_ = 2ULL;
v___x_4699_ = lean_uint64_shift_right(v___y_4695_, v___x_4698_);
v___x_4700_ = lean_uint64_dec_eq(v___x_4699_, v___y_4696_);
if (v___x_4700_ == 0)
{
v___y_4686_ = v___y_4695_;
v___y_4687_ = v___x_4698_;
v___y_4688_ = v___y_4697_;
v___y_4689_ = v___y_4696_;
v___y_4690_ = v___x_4699_;
goto v___jp_4685_;
}
else
{
v___y_4686_ = v___y_4695_;
v___y_4687_ = v___x_4698_;
v___y_4688_ = v___y_4697_;
v___y_4689_ = v___y_4696_;
v___y_4690_ = v___y_4695_;
goto v___jp_4685_;
}
}
v___jp_4701_:
{
uint64_t v___x_4707_; uint8_t v___x_4708_; 
v___x_4707_ = lean_uint64_shift_right(v___y_4703_, v___y_4705_);
v___x_4708_ = lean_uint64_dec_eq(v___x_4707_, v___y_4702_);
if (v___x_4708_ == 0)
{
uint64_t v___x_4709_; 
v___x_4709_ = lean_uint64_add(v___y_4704_, v___y_4705_);
v___y_4695_ = v___y_4706_;
v___y_4696_ = v___y_4702_;
v___y_4697_ = v___x_4709_;
goto v___jp_4694_;
}
else
{
v___y_4695_ = v___y_4706_;
v___y_4696_ = v___y_4702_;
v___y_4697_ = v___y_4704_;
goto v___jp_4694_;
}
}
v___jp_4710_:
{
uint64_t v___x_4714_; uint64_t v___x_4715_; uint8_t v___x_4716_; 
v___x_4714_ = 4ULL;
v___x_4715_ = lean_uint64_shift_right(v___y_4712_, v___x_4714_);
v___x_4716_ = lean_uint64_dec_eq(v___x_4715_, v___y_4711_);
if (v___x_4716_ == 0)
{
v___y_4702_ = v___y_4711_;
v___y_4703_ = v___y_4712_;
v___y_4704_ = v___y_4713_;
v___y_4705_ = v___x_4714_;
v___y_4706_ = v___x_4715_;
goto v___jp_4701_;
}
else
{
v___y_4702_ = v___y_4711_;
v___y_4703_ = v___y_4712_;
v___y_4704_ = v___y_4713_;
v___y_4705_ = v___x_4714_;
v___y_4706_ = v___y_4712_;
goto v___jp_4701_;
}
}
v___jp_4717_:
{
uint64_t v___x_4723_; uint8_t v___x_4724_; 
v___x_4723_ = lean_uint64_shift_right(v___y_4720_, v___y_4721_);
v___x_4724_ = lean_uint64_dec_eq(v___x_4723_, v___y_4719_);
if (v___x_4724_ == 0)
{
uint64_t v___x_4725_; 
v___x_4725_ = lean_uint64_add(v___y_4718_, v___y_4721_);
v___y_4711_ = v___y_4719_;
v___y_4712_ = v___y_4722_;
v___y_4713_ = v___x_4725_;
goto v___jp_4710_;
}
else
{
v___y_4711_ = v___y_4719_;
v___y_4712_ = v___y_4722_;
v___y_4713_ = v___y_4718_;
goto v___jp_4710_;
}
}
v___jp_4726_:
{
uint64_t v___x_4730_; uint64_t v___x_4731_; uint8_t v___x_4732_; 
v___x_4730_ = 8ULL;
v___x_4731_ = lean_uint64_shift_right(v___y_4728_, v___x_4730_);
v___x_4732_ = lean_uint64_dec_eq(v___x_4731_, v___y_4727_);
if (v___x_4732_ == 0)
{
v___y_4718_ = v___y_4729_;
v___y_4719_ = v___y_4727_;
v___y_4720_ = v___y_4728_;
v___y_4721_ = v___x_4730_;
v___y_4722_ = v___x_4731_;
goto v___jp_4717_;
}
else
{
v___y_4718_ = v___y_4729_;
v___y_4719_ = v___y_4727_;
v___y_4720_ = v___y_4728_;
v___y_4721_ = v___x_4730_;
v___y_4722_ = v___y_4728_;
goto v___jp_4717_;
}
}
v___jp_4733_:
{
uint64_t v___x_4739_; uint8_t v___x_4740_; 
v___x_4739_ = lean_uint64_shift_right(v___y_4736_, v___y_4734_);
v___x_4740_ = lean_uint64_dec_eq(v___x_4739_, v___y_4735_);
if (v___x_4740_ == 0)
{
uint64_t v___x_4741_; 
v___x_4741_ = lean_uint64_add(v___y_4737_, v___y_4734_);
v___y_4727_ = v___y_4735_;
v___y_4728_ = v___y_4738_;
v___y_4729_ = v___x_4741_;
goto v___jp_4726_;
}
else
{
v___y_4727_ = v___y_4735_;
v___y_4728_ = v___y_4738_;
v___y_4729_ = v___y_4737_;
goto v___jp_4726_;
}
}
v___jp_4742_:
{
uint64_t v___x_4746_; uint64_t v___x_4747_; uint8_t v___x_4748_; 
v___x_4746_ = 16ULL;
v___x_4747_ = lean_uint64_shift_right(v___y_4744_, v___x_4746_);
v___x_4748_ = lean_uint64_dec_eq(v___x_4747_, v___y_4743_);
if (v___x_4748_ == 0)
{
v___y_4734_ = v___x_4746_;
v___y_4735_ = v___y_4743_;
v___y_4736_ = v___y_4744_;
v___y_4737_ = v___y_4745_;
v___y_4738_ = v___x_4747_;
goto v___jp_4733_;
}
else
{
v___y_4734_ = v___x_4746_;
v___y_4735_ = v___y_4743_;
v___y_4736_ = v___y_4744_;
v___y_4737_ = v___y_4745_;
v___y_4738_ = v___y_4744_;
goto v___jp_4733_;
}
}
v___jp_4749_:
{
uint64_t v___x_4753_; uint8_t v___x_4754_; 
v___x_4753_ = lean_uint64_shift_right(v_product_4539_, v___y_4750_);
v___x_4754_ = lean_uint64_dec_eq(v___x_4753_, v___y_4751_);
if (v___x_4754_ == 0)
{
v___y_4743_ = v___y_4751_;
v___y_4744_ = v___y_4752_;
v___y_4745_ = v___y_4750_;
goto v___jp_4742_;
}
else
{
v___y_4743_ = v___y_4751_;
v___y_4744_ = v___y_4752_;
v___y_4745_ = v___y_4751_;
goto v___jp_4742_;
}
}
v___jp_4755_:
{
uint64_t v___x_4756_; uint8_t v___x_4757_; 
v___x_4756_ = 0ULL;
v___x_4757_ = lean_uint64_dec_eq(v_product_4539_, v___x_4756_);
if (v___x_4757_ == 0)
{
uint64_t v___x_4758_; uint64_t v___x_4759_; uint8_t v___x_4760_; 
v___x_4758_ = 32ULL;
v___x_4759_ = lean_uint64_shift_right(v_product_4539_, v___x_4758_);
v___x_4760_ = lean_uint64_dec_eq(v___x_4759_, v___x_4756_);
if (v___x_4760_ == 0)
{
v___y_4750_ = v___x_4758_;
v___y_4751_ = v___x_4756_;
v___y_4752_ = v___x_4759_;
goto v___jp_4749_;
}
else
{
v___y_4750_ = v___x_4758_;
v___y_4751_ = v___x_4756_;
v___y_4752_ = v_product_4539_;
goto v___jp_4749_;
}
}
else
{
if (v_sign_4538_ == 0)
{
uint32_t v___x_4761_; 
v___x_4761_ = 0;
return v___x_4761_;
}
else
{
uint32_t v___x_4762_; 
v___x_4762_ = 2147483648;
return v___x_4762_;
}
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_LowScale_roundSelect___boxed(lean_object* v_sign_4805_, lean_object* v_product_4806_, lean_object* v_scale_4807_){
_start:
{
uint8_t v_sign_boxed_4808_; uint64_t v_product_boxed_4809_; uint64_t v_scale_boxed_4810_; uint32_t v_res_4811_; lean_object* v_r_4812_; 
v_sign_boxed_4808_ = lean_unbox(v_sign_4805_);
v_product_boxed_4809_ = lean_unbox_uint64(v_product_4806_);
lean_dec_ref(v_product_4806_);
v_scale_boxed_4810_ = lean_unbox_uint64(v_scale_4807_);
lean_dec_ref(v_scale_4807_);
v_res_4811_ = lp_competition_Submission_LowScale_roundSelect(v_sign_boxed_4808_, v_product_boxed_4809_, v_scale_boxed_4810_);
v_r_4812_ = lean_box_uint32(v_res_4811_);
return v_r_4812_;
}
}
LEAN_EXPORT uint32_t lp_competition_Submission_LowScale_core(uint32_t v_xBits_4813_, uint32_t v_yBits_4814_){
_start:
{
uint32_t v___y_4816_; uint32_t v___y_4820_; uint32_t v___y_4824_; uint32_t v___y_4825_; uint32_t v___y_4826_; uint32_t v___y_4830_; uint8_t v___y_4831_; uint64_t v___y_4832_; uint64_t v___y_4833_; uint32_t v___y_4845_; uint32_t v___y_4846_; uint32_t v___y_4847_; uint32_t v___y_4851_; uint8_t v___y_4852_; uint64_t v___y_4853_; uint64_t v___y_4854_; uint32_t v___x_4865_; uint32_t v___x_4866_; uint32_t v___x_4867_; uint32_t v___y_4869_; uint32_t v___y_4870_; uint32_t v___y_4871_; uint32_t v___y_4872_; uint32_t v___y_4879_; uint8_t v___y_4880_; uint32_t v___y_4881_; uint32_t v___y_4882_; uint32_t v___y_4886_; uint8_t v___y_4887_; uint64_t v___y_4888_; uint64_t v___y_4889_; uint64_t v___y_4890_; uint32_t v___y_4900_; uint8_t v___y_4901_; uint64_t v___y_4902_; uint8_t v___y_4903_; uint64_t v___y_4904_; uint64_t v___y_4905_; uint32_t v___y_4912_; uint8_t v___y_4913_; uint64_t v___y_4914_; uint64_t v___y_4915_; uint64_t v___y_4916_; uint32_t v___y_4922_; uint8_t v___y_4923_; uint64_t v___y_4924_; uint64_t v___y_4925_; uint64_t v___y_4926_; uint64_t v___y_4927_; uint32_t v___y_4982_; uint64_t v___y_4983_; uint8_t v___y_4984_; uint64_t v___y_4985_; uint64_t v___y_4986_; uint64_t v___y_4987_; uint64_t v___y_4988_; uint64_t v___y_4994_; uint32_t v___y_4995_; uint8_t v___y_4996_; uint64_t v___y_4997_; uint64_t v___y_4998_; uint64_t v___y_4999_; uint64_t v___y_5000_; uint64_t v___y_5001_; uint64_t v___y_5002_; uint64_t v___y_5007_; uint32_t v___y_5008_; uint8_t v___y_5009_; uint64_t v___y_5010_; uint64_t v___y_5011_; uint64_t v___y_5012_; uint64_t v___y_5013_; uint64_t v___y_5018_; uint32_t v___y_5019_; uint8_t v___y_5020_; uint64_t v___y_5021_; uint64_t v___y_5022_; uint64_t v___y_5023_; uint64_t v___y_5024_; uint64_t v___y_5025_; uint64_t v___y_5026_; uint32_t v___y_5031_; uint8_t v___y_5032_; uint64_t v___y_5033_; uint64_t v___y_5034_; uint64_t v___y_5035_; uint64_t v___y_5036_; uint64_t v___y_5037_; uint32_t v___y_5042_; uint64_t v___y_5043_; uint8_t v___y_5044_; uint64_t v___y_5045_; uint64_t v___y_5046_; uint64_t v___y_5047_; uint64_t v___y_5048_; uint64_t v___y_5049_; uint64_t v___y_5050_; uint32_t v___y_5055_; uint8_t v___y_5056_; uint64_t v___y_5057_; uint64_t v___y_5058_; uint64_t v___y_5059_; uint64_t v___y_5060_; uint64_t v___y_5061_; uint32_t v___y_5066_; uint8_t v___y_5067_; uint64_t v___y_5068_; uint64_t v___y_5069_; uint64_t v___y_5070_; uint64_t v___y_5071_; uint64_t v___y_5072_; uint64_t v___y_5073_; uint64_t v___y_5074_; uint32_t v___y_5079_; uint8_t v___y_5080_; uint64_t v___y_5081_; uint64_t v___y_5082_; uint64_t v___y_5083_; uint64_t v___y_5084_; uint64_t v___y_5085_; uint64_t v___y_5090_; uint32_t v___y_5091_; uint8_t v___y_5092_; uint64_t v___y_5093_; uint64_t v___y_5094_; uint64_t v___y_5095_; uint64_t v___y_5096_; uint32_t v___y_5100_; uint8_t v___y_5101_; uint64_t v___y_5102_; uint64_t v___y_5103_; uint64_t v___y_5112_; uint32_t v___y_5113_; uint8_t v___y_5114_; uint64_t v___y_5115_; uint64_t v___y_5116_; uint64_t v___y_5117_; uint32_t v_xExponent_5150_; uint32_t v___x_5151_; uint32_t v_yExponent_5152_; uint64_t v___y_5154_; uint32_t v___y_5155_; uint64_t v___y_5156_; uint8_t v___y_5157_; uint64_t v___y_5158_; uint64_t v___y_5165_; uint32_t v___y_5166_; uint8_t v___y_5167_; uint64_t v___y_5168_; uint32_t v___y_5175_; uint32_t v___y_5176_; uint8_t v___y_5177_; uint64_t v___y_5178_; uint8_t v___y_5186_; uint8_t v___y_5201_; uint8_t v___y_5202_; uint8_t v___y_5204_; uint32_t v___x_5211_; uint32_t v___x_5212_; uint32_t v___x_5213_; uint8_t v___x_5214_; 
v___x_4865_ = 23;
v___x_4866_ = lean_uint32_shift_right(v_xBits_4813_, v___x_4865_);
v___x_4867_ = 255;
v_xExponent_5150_ = lean_uint32_land(v___x_4866_, v___x_4867_);
v___x_5151_ = lean_uint32_shift_right(v_yBits_4814_, v___x_4865_);
v_yExponent_5152_ = lean_uint32_land(v___x_5151_, v___x_4867_);
v___x_5211_ = 2147483648;
v___x_5212_ = lean_uint32_land(v_xBits_4813_, v___x_5211_);
v___x_5213_ = 0;
v___x_5214_ = lean_uint32_dec_eq(v___x_5212_, v___x_5213_);
if (v___x_5214_ == 0)
{
uint8_t v___x_5215_; 
v___x_5215_ = 1;
v___y_5204_ = v___x_5215_;
goto v___jp_5203_;
}
else
{
uint8_t v___x_5216_; 
v___x_5216_ = 0;
v___y_5204_ = v___x_5216_;
goto v___jp_5203_;
}
v___jp_4815_:
{
uint32_t v___x_4817_; uint32_t v___x_4818_; 
v___x_4817_ = 8388608;
v___x_4818_ = lean_uint32_lor(v___y_4816_, v___x_4817_);
return v___x_4818_;
}
v___jp_4819_:
{
uint32_t v___x_4821_; uint32_t v___x_4822_; 
v___x_4821_ = 8388608;
v___x_4822_ = lean_uint32_lor(v___y_4820_, v___x_4821_);
return v___x_4822_;
}
v___jp_4823_:
{
uint32_t v___x_4827_; uint32_t v___x_4828_; 
v___x_4827_ = lean_uint32_land(v___y_4825_, v___y_4824_);
v___x_4828_ = lean_uint32_lor(v___y_4826_, v___x_4827_);
return v___x_4828_;
}
v___jp_4829_:
{
uint8_t v___x_4834_; 
v___x_4834_ = lean_uint64_dec_eq(v___y_4833_, v___y_4832_);
if (v___x_4834_ == 0)
{
uint64_t v___x_4835_; uint8_t v___x_4836_; 
v___x_4835_ = 8388608ULL;
v___x_4836_ = lean_uint64_dec_eq(v___y_4833_, v___x_4835_);
if (v___x_4836_ == 0)
{
uint32_t v___x_4837_; 
v___x_4837_ = lean_uint64_to_uint32(v___y_4833_);
if (v___y_4831_ == 0)
{
uint32_t v___x_4838_; 
v___x_4838_ = 0;
v___y_4824_ = v___y_4830_;
v___y_4825_ = v___x_4837_;
v___y_4826_ = v___x_4838_;
goto v___jp_4823_;
}
else
{
uint32_t v___x_4839_; 
v___x_4839_ = 2147483648;
v___y_4824_ = v___y_4830_;
v___y_4825_ = v___x_4837_;
v___y_4826_ = v___x_4839_;
goto v___jp_4823_;
}
}
else
{
if (v___y_4831_ == 0)
{
uint32_t v___x_4840_; 
v___x_4840_ = 0;
v___y_4816_ = v___x_4840_;
goto v___jp_4815_;
}
else
{
uint32_t v___x_4841_; 
v___x_4841_ = 2147483648;
v___y_4816_ = v___x_4841_;
goto v___jp_4815_;
}
}
}
else
{
if (v___y_4831_ == 0)
{
uint32_t v___x_4842_; 
v___x_4842_ = 0;
return v___x_4842_;
}
else
{
uint32_t v___x_4843_; 
v___x_4843_ = 2147483648;
return v___x_4843_;
}
}
}
v___jp_4844_:
{
uint32_t v___x_4848_; uint32_t v___x_4849_; 
v___x_4848_ = lean_uint32_land(v___y_4846_, v___y_4845_);
v___x_4849_ = lean_uint32_lor(v___y_4847_, v___x_4848_);
return v___x_4849_;
}
v___jp_4850_:
{
uint8_t v___x_4855_; 
v___x_4855_ = lean_uint64_dec_eq(v___y_4854_, v___y_4853_);
if (v___x_4855_ == 0)
{
uint64_t v___x_4856_; uint8_t v___x_4857_; 
v___x_4856_ = 8388608ULL;
v___x_4857_ = lean_uint64_dec_eq(v___y_4854_, v___x_4856_);
if (v___x_4857_ == 0)
{
uint32_t v___x_4858_; 
v___x_4858_ = lean_uint64_to_uint32(v___y_4854_);
if (v___y_4852_ == 0)
{
uint32_t v___x_4859_; 
v___x_4859_ = 0;
v___y_4845_ = v___y_4851_;
v___y_4846_ = v___x_4858_;
v___y_4847_ = v___x_4859_;
goto v___jp_4844_;
}
else
{
uint32_t v___x_4860_; 
v___x_4860_ = 2147483648;
v___y_4845_ = v___y_4851_;
v___y_4846_ = v___x_4858_;
v___y_4847_ = v___x_4860_;
goto v___jp_4844_;
}
}
else
{
if (v___y_4852_ == 0)
{
uint32_t v___x_4861_; 
v___x_4861_ = 0;
v___y_4820_ = v___x_4861_;
goto v___jp_4819_;
}
else
{
uint32_t v___x_4862_; 
v___x_4862_ = 2147483648;
v___y_4820_ = v___x_4862_;
goto v___jp_4819_;
}
}
}
else
{
if (v___y_4852_ == 0)
{
uint32_t v___x_4863_; 
v___x_4863_ = 0;
return v___x_4863_;
}
else
{
uint32_t v___x_4864_; 
v___x_4864_ = 2147483648;
return v___x_4864_;
}
}
}
v___jp_4868_:
{
uint32_t v___x_4873_; uint32_t v___x_4874_; uint32_t v___x_4875_; uint32_t v___x_4876_; uint32_t v___x_4877_; 
v___x_4873_ = lean_uint32_land(v___y_4871_, v___x_4867_);
v___x_4874_ = lean_uint32_shift_left(v___x_4873_, v___x_4865_);
v___x_4875_ = lean_uint32_lor(v___y_4872_, v___x_4874_);
v___x_4876_ = lean_uint32_land(v___y_4870_, v___y_4869_);
v___x_4877_ = lean_uint32_lor(v___x_4875_, v___x_4876_);
return v___x_4877_;
}
v___jp_4878_:
{
if (v___y_4880_ == 0)
{
uint32_t v___x_4883_; 
v___x_4883_ = 0;
v___y_4869_ = v___y_4879_;
v___y_4870_ = v___y_4882_;
v___y_4871_ = v___y_4881_;
v___y_4872_ = v___x_4883_;
goto v___jp_4868_;
}
else
{
uint32_t v___x_4884_; 
v___x_4884_ = 2147483648;
v___y_4869_ = v___y_4879_;
v___y_4870_ = v___y_4882_;
v___y_4871_ = v___y_4881_;
v___y_4872_ = v___x_4884_;
goto v___jp_4868_;
}
}
v___jp_4885_:
{
uint64_t v___x_4891_; uint64_t v_encodedExponent_4892_; uint32_t v___x_4893_; uint64_t v___x_4894_; uint8_t v___x_4895_; 
v___x_4891_ = 171ULL;
v_encodedExponent_4892_ = lean_uint64_sub(v___y_4888_, v___x_4891_);
v___x_4893_ = lean_uint64_to_uint32(v_encodedExponent_4892_);
v___x_4894_ = 8388608ULL;
v___x_4895_ = lean_uint64_dec_lt(v___y_4890_, v___x_4894_);
if (v___x_4895_ == 0)
{
uint64_t v___x_4896_; uint32_t v___x_4897_; 
v___x_4896_ = lean_uint64_sub(v___y_4890_, v___x_4894_);
v___x_4897_ = lean_uint64_to_uint32(v___x_4896_);
v___y_4879_ = v___y_4886_;
v___y_4880_ = v___y_4887_;
v___y_4881_ = v___x_4893_;
v___y_4882_ = v___x_4897_;
goto v___jp_4878_;
}
else
{
uint32_t v___x_4898_; 
v___x_4898_ = lean_uint64_to_uint32(v___y_4889_);
v___y_4879_ = v___y_4886_;
v___y_4880_ = v___y_4887_;
v___y_4881_ = v___x_4893_;
v___y_4882_ = v___x_4898_;
goto v___jp_4878_;
}
}
v___jp_4899_:
{
uint64_t v___x_4906_; uint8_t v___x_4907_; 
v___x_4906_ = 425ULL;
v___x_4907_ = lean_uint64_dec_lt(v___x_4906_, v___y_4905_);
if (v___x_4907_ == 0)
{
if (v___y_4903_ == 0)
{
v___y_4886_ = v___y_4900_;
v___y_4887_ = v___y_4901_;
v___y_4888_ = v___y_4905_;
v___y_4889_ = v___y_4904_;
v___y_4890_ = v___y_4902_;
goto v___jp_4885_;
}
else
{
uint64_t v___x_4908_; 
v___x_4908_ = 8388608ULL;
v___y_4886_ = v___y_4900_;
v___y_4887_ = v___y_4901_;
v___y_4888_ = v___y_4905_;
v___y_4889_ = v___y_4904_;
v___y_4890_ = v___x_4908_;
goto v___jp_4885_;
}
}
else
{
if (v___y_4901_ == 0)
{
uint32_t v___x_4909_; 
v___x_4909_ = 2139095040;
return v___x_4909_;
}
else
{
uint32_t v___x_4910_; 
v___x_4910_ = 4286578688;
return v___x_4910_;
}
}
}
v___jp_4911_:
{
uint64_t v___x_4917_; uint8_t v_carry_4918_; 
v___x_4917_ = 16777216ULL;
v_carry_4918_ = lean_uint64_dec_eq(v___y_4916_, v___x_4917_);
if (v_carry_4918_ == 0)
{
v___y_4900_ = v___y_4912_;
v___y_4901_ = v___y_4913_;
v___y_4902_ = v___y_4916_;
v___y_4903_ = v_carry_4918_;
v___y_4904_ = v___y_4915_;
v___y_4905_ = v___y_4914_;
goto v___jp_4899_;
}
else
{
uint64_t v___x_4919_; uint64_t v___x_4920_; 
v___x_4919_ = 1ULL;
v___x_4920_ = lean_uint64_add(v___y_4914_, v___x_4919_);
v___y_4900_ = v___y_4912_;
v___y_4901_ = v___y_4913_;
v___y_4902_ = v___y_4916_;
v___y_4903_ = v_carry_4918_;
v___y_4904_ = v___y_4915_;
v___y_4905_ = v___x_4920_;
goto v___jp_4899_;
}
}
v___jp_4921_:
{
uint64_t v_position_4928_; uint64_t v___x_4929_; uint8_t v___x_4930_; 
v_position_4928_ = lean_uint64_add(v___y_4927_, v___y_4925_);
v___x_4929_ = 172ULL;
v___x_4930_ = lean_uint64_dec_lt(v_position_4928_, v___x_4929_);
if (v___x_4930_ == 0)
{
uint64_t v___x_4931_; uint8_t v___x_4932_; 
v___x_4931_ = 23ULL;
v___x_4932_ = lean_uint64_dec_lt(v___y_4927_, v___x_4931_);
if (v___x_4932_ == 0)
{
uint64_t v___x_4933_; uint8_t v___x_4934_; 
v___x_4933_ = lean_uint64_sub(v___y_4927_, v___x_4931_);
v___x_4934_ = lean_uint64_dec_eq(v___x_4933_, v___y_4926_);
if (v___x_4934_ == 0)
{
uint64_t v___x_4935_; uint8_t v___x_4936_; 
v___x_4935_ = 64ULL;
v___x_4936_ = lean_uint64_dec_lt(v___x_4933_, v___x_4935_);
if (v___x_4936_ == 0)
{
uint8_t v___x_4937_; 
v___x_4937_ = lean_uint64_dec_eq(v___x_4933_, v___x_4935_);
if (v___x_4937_ == 0)
{
v___y_4912_ = v___y_4922_;
v___y_4913_ = v___y_4923_;
v___y_4914_ = v_position_4928_;
v___y_4915_ = v___y_4926_;
v___y_4916_ = v___y_4926_;
goto v___jp_4911_;
}
else
{
uint64_t v___x_4938_; uint8_t v___x_4939_; 
v___x_4938_ = 9223372036854775808ULL;
v___x_4939_ = lean_uint64_dec_lt(v___x_4938_, v___y_4924_);
if (v___x_4939_ == 0)
{
v___y_4912_ = v___y_4922_;
v___y_4913_ = v___y_4923_;
v___y_4914_ = v_position_4928_;
v___y_4915_ = v___y_4926_;
v___y_4916_ = v___y_4926_;
goto v___jp_4911_;
}
else
{
uint64_t v___x_4940_; 
v___x_4940_ = 1ULL;
v___y_4912_ = v___y_4922_;
v___y_4913_ = v___y_4923_;
v___y_4914_ = v_position_4928_;
v___y_4915_ = v___y_4926_;
v___y_4916_ = v___x_4940_;
goto v___jp_4911_;
}
}
}
else
{
uint64_t v_quotient_4941_; uint64_t v___x_4942_; uint64_t v___x_4943_; uint64_t v___x_4944_; uint64_t v_remainder_4945_; uint64_t v___x_4946_; uint64_t v_half_4947_; uint8_t v___x_4948_; 
v_quotient_4941_ = lean_uint64_shift_right(v___y_4924_, v___x_4933_);
v___x_4942_ = 1ULL;
v___x_4943_ = lean_uint64_shift_left(v___x_4942_, v___x_4933_);
v___x_4944_ = lean_uint64_sub(v___x_4943_, v___x_4942_);
v_remainder_4945_ = lean_uint64_land(v___y_4924_, v___x_4944_);
v___x_4946_ = lean_uint64_sub(v___x_4933_, v___x_4942_);
v_half_4947_ = lean_uint64_shift_left(v___x_4942_, v___x_4946_);
v___x_4948_ = lean_uint64_dec_lt(v_remainder_4945_, v_half_4947_);
if (v___x_4948_ == 0)
{
uint8_t v___x_4949_; 
v___x_4949_ = lean_uint64_dec_lt(v_half_4947_, v_remainder_4945_);
if (v___x_4949_ == 0)
{
uint64_t v___x_4950_; uint8_t v___x_4951_; 
v___x_4950_ = lean_uint64_land(v_quotient_4941_, v___x_4942_);
v___x_4951_ = lean_uint64_dec_eq(v___x_4950_, v___y_4926_);
if (v___x_4951_ == 0)
{
uint64_t v___x_4952_; 
v___x_4952_ = lean_uint64_add(v_quotient_4941_, v___x_4942_);
v___y_4912_ = v___y_4922_;
v___y_4913_ = v___y_4923_;
v___y_4914_ = v_position_4928_;
v___y_4915_ = v___y_4926_;
v___y_4916_ = v___x_4952_;
goto v___jp_4911_;
}
else
{
v___y_4912_ = v___y_4922_;
v___y_4913_ = v___y_4923_;
v___y_4914_ = v_position_4928_;
v___y_4915_ = v___y_4926_;
v___y_4916_ = v_quotient_4941_;
goto v___jp_4911_;
}
}
else
{
uint64_t v___x_4953_; 
v___x_4953_ = lean_uint64_add(v_quotient_4941_, v___x_4942_);
v___y_4912_ = v___y_4922_;
v___y_4913_ = v___y_4923_;
v___y_4914_ = v_position_4928_;
v___y_4915_ = v___y_4926_;
v___y_4916_ = v___x_4953_;
goto v___jp_4911_;
}
}
else
{
v___y_4912_ = v___y_4922_;
v___y_4913_ = v___y_4923_;
v___y_4914_ = v_position_4928_;
v___y_4915_ = v___y_4926_;
v___y_4916_ = v_quotient_4941_;
goto v___jp_4911_;
}
}
}
else
{
v___y_4912_ = v___y_4922_;
v___y_4913_ = v___y_4923_;
v___y_4914_ = v_position_4928_;
v___y_4915_ = v___y_4926_;
v___y_4916_ = v___y_4924_;
goto v___jp_4911_;
}
}
else
{
uint64_t v___x_4954_; uint64_t v___x_4955_; 
v___x_4954_ = lean_uint64_sub(v___x_4931_, v___y_4927_);
v___x_4955_ = lean_uint64_shift_left(v___y_4924_, v___x_4954_);
v___y_4912_ = v___y_4922_;
v___y_4913_ = v___y_4923_;
v___y_4914_ = v_position_4928_;
v___y_4915_ = v___y_4926_;
v___y_4916_ = v___x_4955_;
goto v___jp_4911_;
}
}
else
{
uint64_t v___x_4956_; uint8_t v___x_4957_; 
v___x_4956_ = 149ULL;
v___x_4957_ = lean_uint64_dec_lt(v___y_4925_, v___x_4956_);
if (v___x_4957_ == 0)
{
uint64_t v___x_4958_; uint64_t v___x_4959_; 
v___x_4958_ = lean_uint64_sub(v___y_4925_, v___x_4956_);
v___x_4959_ = lean_uint64_shift_left(v___y_4924_, v___x_4958_);
v___y_4830_ = v___y_4922_;
v___y_4831_ = v___y_4923_;
v___y_4832_ = v___y_4926_;
v___y_4833_ = v___x_4959_;
goto v___jp_4829_;
}
else
{
uint64_t v___x_4960_; uint8_t v___x_4961_; 
v___x_4960_ = lean_uint64_sub(v___x_4956_, v___y_4925_);
v___x_4961_ = lean_uint64_dec_eq(v___x_4960_, v___y_4926_);
if (v___x_4961_ == 0)
{
uint64_t v___x_4962_; uint8_t v___x_4963_; 
v___x_4962_ = 64ULL;
v___x_4963_ = lean_uint64_dec_lt(v___x_4960_, v___x_4962_);
if (v___x_4963_ == 0)
{
uint8_t v___x_4964_; 
v___x_4964_ = lean_uint64_dec_eq(v___x_4960_, v___x_4962_);
if (v___x_4964_ == 0)
{
v___y_4830_ = v___y_4922_;
v___y_4831_ = v___y_4923_;
v___y_4832_ = v___y_4926_;
v___y_4833_ = v___y_4926_;
goto v___jp_4829_;
}
else
{
uint64_t v___x_4965_; uint8_t v___x_4966_; 
v___x_4965_ = 9223372036854775808ULL;
v___x_4966_ = lean_uint64_dec_lt(v___x_4965_, v___y_4924_);
if (v___x_4966_ == 0)
{
v___y_4830_ = v___y_4922_;
v___y_4831_ = v___y_4923_;
v___y_4832_ = v___y_4926_;
v___y_4833_ = v___y_4926_;
goto v___jp_4829_;
}
else
{
uint64_t v___x_4967_; 
v___x_4967_ = 1ULL;
v___y_4830_ = v___y_4922_;
v___y_4831_ = v___y_4923_;
v___y_4832_ = v___y_4926_;
v___y_4833_ = v___x_4967_;
goto v___jp_4829_;
}
}
}
else
{
uint64_t v_quotient_4968_; uint64_t v___x_4969_; uint64_t v___x_4970_; uint64_t v___x_4971_; uint64_t v_remainder_4972_; uint64_t v___x_4973_; uint64_t v_half_4974_; uint8_t v___x_4975_; 
v_quotient_4968_ = lean_uint64_shift_right(v___y_4924_, v___x_4960_);
v___x_4969_ = 1ULL;
v___x_4970_ = lean_uint64_shift_left(v___x_4969_, v___x_4960_);
v___x_4971_ = lean_uint64_sub(v___x_4970_, v___x_4969_);
v_remainder_4972_ = lean_uint64_land(v___y_4924_, v___x_4971_);
v___x_4973_ = lean_uint64_sub(v___x_4960_, v___x_4969_);
v_half_4974_ = lean_uint64_shift_left(v___x_4969_, v___x_4973_);
v___x_4975_ = lean_uint64_dec_lt(v_remainder_4972_, v_half_4974_);
if (v___x_4975_ == 0)
{
uint8_t v___x_4976_; 
v___x_4976_ = lean_uint64_dec_lt(v_half_4974_, v_remainder_4972_);
if (v___x_4976_ == 0)
{
uint64_t v___x_4977_; uint8_t v___x_4978_; 
v___x_4977_ = lean_uint64_land(v_quotient_4968_, v___x_4969_);
v___x_4978_ = lean_uint64_dec_eq(v___x_4977_, v___y_4926_);
if (v___x_4978_ == 0)
{
uint64_t v___x_4979_; 
v___x_4979_ = lean_uint64_add(v_quotient_4968_, v___x_4969_);
v___y_4830_ = v___y_4922_;
v___y_4831_ = v___y_4923_;
v___y_4832_ = v___y_4926_;
v___y_4833_ = v___x_4979_;
goto v___jp_4829_;
}
else
{
v___y_4830_ = v___y_4922_;
v___y_4831_ = v___y_4923_;
v___y_4832_ = v___y_4926_;
v___y_4833_ = v_quotient_4968_;
goto v___jp_4829_;
}
}
else
{
uint64_t v___x_4980_; 
v___x_4980_ = lean_uint64_add(v_quotient_4968_, v___x_4969_);
v___y_4830_ = v___y_4922_;
v___y_4831_ = v___y_4923_;
v___y_4832_ = v___y_4926_;
v___y_4833_ = v___x_4980_;
goto v___jp_4829_;
}
}
else
{
v___y_4830_ = v___y_4922_;
v___y_4831_ = v___y_4923_;
v___y_4832_ = v___y_4926_;
v___y_4833_ = v_quotient_4968_;
goto v___jp_4829_;
}
}
}
else
{
v___y_4830_ = v___y_4922_;
v___y_4831_ = v___y_4923_;
v___y_4832_ = v___y_4926_;
v___y_4833_ = v___y_4924_;
goto v___jp_4829_;
}
}
}
}
v___jp_4981_:
{
uint64_t v___x_4989_; uint64_t v___x_4990_; uint8_t v___x_4991_; 
v___x_4989_ = 1ULL;
v___x_4990_ = lean_uint64_shift_right(v___y_4983_, v___x_4989_);
v___x_4991_ = lean_uint64_dec_eq(v___x_4990_, v___y_4987_);
if (v___x_4991_ == 0)
{
uint64_t v___x_4992_; 
v___x_4992_ = lean_uint64_add(v___y_4988_, v___x_4989_);
v___y_4922_ = v___y_4982_;
v___y_4923_ = v___y_4984_;
v___y_4924_ = v___y_4986_;
v___y_4925_ = v___y_4985_;
v___y_4926_ = v___y_4987_;
v___y_4927_ = v___x_4992_;
goto v___jp_4921_;
}
else
{
v___y_4922_ = v___y_4982_;
v___y_4923_ = v___y_4984_;
v___y_4924_ = v___y_4986_;
v___y_4925_ = v___y_4985_;
v___y_4926_ = v___y_4987_;
v___y_4927_ = v___y_4988_;
goto v___jp_4921_;
}
}
v___jp_4993_:
{
uint64_t v___x_5003_; uint8_t v___x_5004_; 
v___x_5003_ = lean_uint64_shift_right(v___y_4994_, v___y_4997_);
v___x_5004_ = lean_uint64_dec_eq(v___x_5003_, v___y_5001_);
if (v___x_5004_ == 0)
{
uint64_t v___x_5005_; 
v___x_5005_ = lean_uint64_add(v___y_4998_, v___y_4997_);
v___y_4982_ = v___y_4995_;
v___y_4983_ = v___y_5002_;
v___y_4984_ = v___y_4996_;
v___y_4985_ = v___y_5000_;
v___y_4986_ = v___y_4999_;
v___y_4987_ = v___y_5001_;
v___y_4988_ = v___x_5005_;
goto v___jp_4981_;
}
else
{
v___y_4982_ = v___y_4995_;
v___y_4983_ = v___y_5002_;
v___y_4984_ = v___y_4996_;
v___y_4985_ = v___y_5000_;
v___y_4986_ = v___y_4999_;
v___y_4987_ = v___y_5001_;
v___y_4988_ = v___y_4998_;
goto v___jp_4981_;
}
}
v___jp_5006_:
{
uint64_t v___x_5014_; uint64_t v___x_5015_; uint8_t v___x_5016_; 
v___x_5014_ = 2ULL;
v___x_5015_ = lean_uint64_shift_right(v___y_5007_, v___x_5014_);
v___x_5016_ = lean_uint64_dec_eq(v___x_5015_, v___y_5012_);
if (v___x_5016_ == 0)
{
v___y_4994_ = v___y_5007_;
v___y_4995_ = v___y_5008_;
v___y_4996_ = v___y_5009_;
v___y_4997_ = v___x_5014_;
v___y_4998_ = v___y_5013_;
v___y_4999_ = v___y_5011_;
v___y_5000_ = v___y_5010_;
v___y_5001_ = v___y_5012_;
v___y_5002_ = v___x_5015_;
goto v___jp_4993_;
}
else
{
v___y_4994_ = v___y_5007_;
v___y_4995_ = v___y_5008_;
v___y_4996_ = v___y_5009_;
v___y_4997_ = v___x_5014_;
v___y_4998_ = v___y_5013_;
v___y_4999_ = v___y_5011_;
v___y_5000_ = v___y_5010_;
v___y_5001_ = v___y_5012_;
v___y_5002_ = v___y_5007_;
goto v___jp_4993_;
}
}
v___jp_5017_:
{
uint64_t v___x_5027_; uint8_t v___x_5028_; 
v___x_5027_ = lean_uint64_shift_right(v___y_5022_, v___y_5021_);
v___x_5028_ = lean_uint64_dec_eq(v___x_5027_, v___y_5025_);
if (v___x_5028_ == 0)
{
uint64_t v___x_5029_; 
v___x_5029_ = lean_uint64_add(v___y_5018_, v___y_5021_);
v___y_5007_ = v___y_5026_;
v___y_5008_ = v___y_5019_;
v___y_5009_ = v___y_5020_;
v___y_5010_ = v___y_5024_;
v___y_5011_ = v___y_5023_;
v___y_5012_ = v___y_5025_;
v___y_5013_ = v___x_5029_;
goto v___jp_5006_;
}
else
{
v___y_5007_ = v___y_5026_;
v___y_5008_ = v___y_5019_;
v___y_5009_ = v___y_5020_;
v___y_5010_ = v___y_5024_;
v___y_5011_ = v___y_5023_;
v___y_5012_ = v___y_5025_;
v___y_5013_ = v___y_5018_;
goto v___jp_5006_;
}
}
v___jp_5030_:
{
uint64_t v___x_5038_; uint64_t v___x_5039_; uint8_t v___x_5040_; 
v___x_5038_ = 4ULL;
v___x_5039_ = lean_uint64_shift_right(v___y_5033_, v___x_5038_);
v___x_5040_ = lean_uint64_dec_eq(v___x_5039_, v___y_5036_);
if (v___x_5040_ == 0)
{
v___y_5018_ = v___y_5037_;
v___y_5019_ = v___y_5031_;
v___y_5020_ = v___y_5032_;
v___y_5021_ = v___x_5038_;
v___y_5022_ = v___y_5033_;
v___y_5023_ = v___y_5035_;
v___y_5024_ = v___y_5034_;
v___y_5025_ = v___y_5036_;
v___y_5026_ = v___x_5039_;
goto v___jp_5017_;
}
else
{
v___y_5018_ = v___y_5037_;
v___y_5019_ = v___y_5031_;
v___y_5020_ = v___y_5032_;
v___y_5021_ = v___x_5038_;
v___y_5022_ = v___y_5033_;
v___y_5023_ = v___y_5035_;
v___y_5024_ = v___y_5034_;
v___y_5025_ = v___y_5036_;
v___y_5026_ = v___y_5033_;
goto v___jp_5017_;
}
}
v___jp_5041_:
{
uint64_t v___x_5051_; uint8_t v___x_5052_; 
v___x_5051_ = lean_uint64_shift_right(v___y_5046_, v___y_5045_);
v___x_5052_ = lean_uint64_dec_eq(v___x_5051_, v___y_5049_);
if (v___x_5052_ == 0)
{
uint64_t v___x_5053_; 
v___x_5053_ = lean_uint64_add(v___y_5043_, v___y_5045_);
v___y_5031_ = v___y_5042_;
v___y_5032_ = v___y_5044_;
v___y_5033_ = v___y_5050_;
v___y_5034_ = v___y_5048_;
v___y_5035_ = v___y_5047_;
v___y_5036_ = v___y_5049_;
v___y_5037_ = v___x_5053_;
goto v___jp_5030_;
}
else
{
v___y_5031_ = v___y_5042_;
v___y_5032_ = v___y_5044_;
v___y_5033_ = v___y_5050_;
v___y_5034_ = v___y_5048_;
v___y_5035_ = v___y_5047_;
v___y_5036_ = v___y_5049_;
v___y_5037_ = v___y_5043_;
goto v___jp_5030_;
}
}
v___jp_5054_:
{
uint64_t v___x_5062_; uint64_t v___x_5063_; uint8_t v___x_5064_; 
v___x_5062_ = 8ULL;
v___x_5063_ = lean_uint64_shift_right(v___y_5057_, v___x_5062_);
v___x_5064_ = lean_uint64_dec_eq(v___x_5063_, v___y_5060_);
if (v___x_5064_ == 0)
{
v___y_5042_ = v___y_5055_;
v___y_5043_ = v___y_5061_;
v___y_5044_ = v___y_5056_;
v___y_5045_ = v___x_5062_;
v___y_5046_ = v___y_5057_;
v___y_5047_ = v___y_5059_;
v___y_5048_ = v___y_5058_;
v___y_5049_ = v___y_5060_;
v___y_5050_ = v___x_5063_;
goto v___jp_5041_;
}
else
{
v___y_5042_ = v___y_5055_;
v___y_5043_ = v___y_5061_;
v___y_5044_ = v___y_5056_;
v___y_5045_ = v___x_5062_;
v___y_5046_ = v___y_5057_;
v___y_5047_ = v___y_5059_;
v___y_5048_ = v___y_5058_;
v___y_5049_ = v___y_5060_;
v___y_5050_ = v___y_5057_;
goto v___jp_5041_;
}
}
v___jp_5065_:
{
uint64_t v___x_5075_; uint8_t v___x_5076_; 
v___x_5075_ = lean_uint64_shift_right(v___y_5072_, v___y_5068_);
v___x_5076_ = lean_uint64_dec_eq(v___x_5075_, v___y_5073_);
if (v___x_5076_ == 0)
{
uint64_t v___x_5077_; 
v___x_5077_ = lean_uint64_add(v___y_5071_, v___y_5068_);
v___y_5055_ = v___y_5066_;
v___y_5056_ = v___y_5067_;
v___y_5057_ = v___y_5074_;
v___y_5058_ = v___y_5070_;
v___y_5059_ = v___y_5069_;
v___y_5060_ = v___y_5073_;
v___y_5061_ = v___x_5077_;
goto v___jp_5054_;
}
else
{
v___y_5055_ = v___y_5066_;
v___y_5056_ = v___y_5067_;
v___y_5057_ = v___y_5074_;
v___y_5058_ = v___y_5070_;
v___y_5059_ = v___y_5069_;
v___y_5060_ = v___y_5073_;
v___y_5061_ = v___y_5071_;
goto v___jp_5054_;
}
}
v___jp_5078_:
{
uint64_t v___x_5086_; uint64_t v___x_5087_; uint8_t v___x_5088_; 
v___x_5086_ = 16ULL;
v___x_5087_ = lean_uint64_shift_right(v___y_5084_, v___x_5086_);
v___x_5088_ = lean_uint64_dec_eq(v___x_5087_, v___y_5083_);
if (v___x_5088_ == 0)
{
v___y_5066_ = v___y_5079_;
v___y_5067_ = v___y_5080_;
v___y_5068_ = v___x_5086_;
v___y_5069_ = v___y_5082_;
v___y_5070_ = v___y_5081_;
v___y_5071_ = v___y_5085_;
v___y_5072_ = v___y_5084_;
v___y_5073_ = v___y_5083_;
v___y_5074_ = v___x_5087_;
goto v___jp_5065_;
}
else
{
v___y_5066_ = v___y_5079_;
v___y_5067_ = v___y_5080_;
v___y_5068_ = v___x_5086_;
v___y_5069_ = v___y_5082_;
v___y_5070_ = v___y_5081_;
v___y_5071_ = v___y_5085_;
v___y_5072_ = v___y_5084_;
v___y_5073_ = v___y_5083_;
v___y_5074_ = v___y_5084_;
goto v___jp_5065_;
}
}
v___jp_5089_:
{
uint64_t v___x_5097_; uint8_t v___x_5098_; 
v___x_5097_ = lean_uint64_shift_right(v___y_5093_, v___y_5090_);
v___x_5098_ = lean_uint64_dec_eq(v___x_5097_, v___y_5095_);
if (v___x_5098_ == 0)
{
v___y_5079_ = v___y_5091_;
v___y_5080_ = v___y_5092_;
v___y_5081_ = v___y_5094_;
v___y_5082_ = v___y_5093_;
v___y_5083_ = v___y_5095_;
v___y_5084_ = v___y_5096_;
v___y_5085_ = v___y_5090_;
goto v___jp_5078_;
}
else
{
v___y_5079_ = v___y_5091_;
v___y_5080_ = v___y_5092_;
v___y_5081_ = v___y_5094_;
v___y_5082_ = v___y_5093_;
v___y_5083_ = v___y_5095_;
v___y_5084_ = v___y_5096_;
v___y_5085_ = v___y_5095_;
goto v___jp_5078_;
}
}
v___jp_5099_:
{
uint64_t v___x_5104_; uint8_t v___x_5105_; 
v___x_5104_ = 0ULL;
v___x_5105_ = lean_uint64_dec_eq(v___y_5103_, v___x_5104_);
if (v___x_5105_ == 0)
{
uint64_t v___x_5106_; uint64_t v___x_5107_; uint8_t v___x_5108_; 
v___x_5106_ = 32ULL;
v___x_5107_ = lean_uint64_shift_right(v___y_5103_, v___x_5106_);
v___x_5108_ = lean_uint64_dec_eq(v___x_5107_, v___x_5104_);
if (v___x_5108_ == 0)
{
v___y_5090_ = v___x_5106_;
v___y_5091_ = v___y_5100_;
v___y_5092_ = v___y_5101_;
v___y_5093_ = v___y_5103_;
v___y_5094_ = v___y_5102_;
v___y_5095_ = v___x_5104_;
v___y_5096_ = v___x_5107_;
goto v___jp_5089_;
}
else
{
v___y_5090_ = v___x_5106_;
v___y_5091_ = v___y_5100_;
v___y_5092_ = v___y_5101_;
v___y_5093_ = v___y_5103_;
v___y_5094_ = v___y_5102_;
v___y_5095_ = v___x_5104_;
v___y_5096_ = v___y_5103_;
goto v___jp_5089_;
}
}
else
{
if (v___y_5101_ == 0)
{
uint32_t v___x_5109_; 
v___x_5109_ = 0;
return v___x_5109_;
}
else
{
uint32_t v___x_5110_; 
v___x_5110_ = 2147483648;
return v___x_5110_;
}
}
}
v___jp_5111_:
{
uint64_t v___x_5118_; uint64_t v___x_5119_; uint64_t v___x_5120_; uint8_t v___x_5121_; 
v___x_5118_ = lean_uint64_mul(v___y_5112_, v___y_5115_);
v___x_5119_ = lean_uint64_add(v___y_5116_, v___y_5117_);
v___x_5120_ = 281474976710656ULL;
v___x_5121_ = lean_uint64_dec_lt(v___x_5118_, v___x_5120_);
if (v___x_5121_ == 0)
{
v___y_5100_ = v___y_5113_;
v___y_5101_ = v___y_5114_;
v___y_5102_ = v___x_5119_;
v___y_5103_ = v___x_5118_;
goto v___jp_5099_;
}
else
{
uint64_t v___x_5122_; uint8_t v___x_5123_; 
v___x_5122_ = 123ULL;
v___x_5123_ = lean_uint64_dec_le(v___x_5119_, v___x_5122_);
if (v___x_5123_ == 0)
{
v___y_5100_ = v___y_5113_;
v___y_5101_ = v___y_5114_;
v___y_5102_ = v___x_5119_;
v___y_5103_ = v___x_5118_;
goto v___jp_5099_;
}
else
{
uint64_t v___x_5124_; uint8_t v___x_5125_; 
v___x_5124_ = 0ULL;
v___x_5125_ = lean_uint64_dec_eq(v___x_5118_, v___x_5124_);
if (v___x_5125_ == 0)
{
uint64_t v___x_5126_; uint64_t v___x_5127_; uint8_t v___x_5128_; 
v___x_5126_ = 149ULL;
v___x_5127_ = lean_uint64_sub(v___x_5126_, v___x_5119_);
v___x_5128_ = lean_uint64_dec_eq(v___x_5127_, v___x_5124_);
if (v___x_5128_ == 0)
{
uint64_t v___x_5129_; uint8_t v___x_5130_; 
v___x_5129_ = 64ULL;
v___x_5130_ = lean_uint64_dec_lt(v___x_5127_, v___x_5129_);
if (v___x_5130_ == 0)
{
uint8_t v___x_5131_; 
v___x_5131_ = lean_uint64_dec_eq(v___x_5127_, v___x_5129_);
if (v___x_5131_ == 0)
{
v___y_4851_ = v___y_5113_;
v___y_4852_ = v___y_5114_;
v___y_4853_ = v___x_5124_;
v___y_4854_ = v___x_5124_;
goto v___jp_4850_;
}
else
{
uint64_t v___x_5132_; uint8_t v___x_5133_; 
v___x_5132_ = 9223372036854775808ULL;
v___x_5133_ = lean_uint64_dec_lt(v___x_5132_, v___x_5118_);
if (v___x_5133_ == 0)
{
v___y_4851_ = v___y_5113_;
v___y_4852_ = v___y_5114_;
v___y_4853_ = v___x_5124_;
v___y_4854_ = v___x_5124_;
goto v___jp_4850_;
}
else
{
uint64_t v___x_5134_; 
v___x_5134_ = 1ULL;
v___y_4851_ = v___y_5113_;
v___y_4852_ = v___y_5114_;
v___y_4853_ = v___x_5124_;
v___y_4854_ = v___x_5134_;
goto v___jp_4850_;
}
}
}
else
{
uint64_t v_quotient_5135_; uint64_t v___x_5136_; uint64_t v___x_5137_; uint64_t v___x_5138_; uint64_t v_remainder_5139_; uint64_t v___x_5140_; uint64_t v_half_5141_; uint8_t v___x_5142_; 
v_quotient_5135_ = lean_uint64_shift_right(v___x_5118_, v___x_5127_);
v___x_5136_ = 1ULL;
v___x_5137_ = lean_uint64_shift_left(v___x_5136_, v___x_5127_);
v___x_5138_ = lean_uint64_sub(v___x_5137_, v___x_5136_);
v_remainder_5139_ = lean_uint64_land(v___x_5118_, v___x_5138_);
v___x_5140_ = lean_uint64_sub(v___x_5127_, v___x_5136_);
v_half_5141_ = lean_uint64_shift_left(v___x_5136_, v___x_5140_);
v___x_5142_ = lean_uint64_dec_lt(v_remainder_5139_, v_half_5141_);
if (v___x_5142_ == 0)
{
uint8_t v___x_5143_; 
v___x_5143_ = lean_uint64_dec_lt(v_half_5141_, v_remainder_5139_);
if (v___x_5143_ == 0)
{
uint64_t v___x_5144_; uint8_t v___x_5145_; 
v___x_5144_ = lean_uint64_land(v_quotient_5135_, v___x_5136_);
v___x_5145_ = lean_uint64_dec_eq(v___x_5144_, v___x_5124_);
if (v___x_5145_ == 0)
{
uint64_t v___x_5146_; 
v___x_5146_ = lean_uint64_add(v_quotient_5135_, v___x_5136_);
v___y_4851_ = v___y_5113_;
v___y_4852_ = v___y_5114_;
v___y_4853_ = v___x_5124_;
v___y_4854_ = v___x_5146_;
goto v___jp_4850_;
}
else
{
v___y_4851_ = v___y_5113_;
v___y_4852_ = v___y_5114_;
v___y_4853_ = v___x_5124_;
v___y_4854_ = v_quotient_5135_;
goto v___jp_4850_;
}
}
else
{
uint64_t v___x_5147_; 
v___x_5147_ = lean_uint64_add(v_quotient_5135_, v___x_5136_);
v___y_4851_ = v___y_5113_;
v___y_4852_ = v___y_5114_;
v___y_4853_ = v___x_5124_;
v___y_4854_ = v___x_5147_;
goto v___jp_4850_;
}
}
else
{
v___y_4851_ = v___y_5113_;
v___y_4852_ = v___y_5114_;
v___y_4853_ = v___x_5124_;
v___y_4854_ = v_quotient_5135_;
goto v___jp_4850_;
}
}
}
else
{
v___y_4851_ = v___y_5113_;
v___y_4852_ = v___y_5114_;
v___y_4853_ = v___x_5124_;
v___y_4854_ = v___x_5118_;
goto v___jp_4850_;
}
}
else
{
if (v___y_5114_ == 0)
{
uint32_t v___x_5148_; 
v___x_5148_ = 0;
return v___x_5148_;
}
else
{
uint32_t v___x_5149_; 
v___x_5149_ = 2147483648;
return v___x_5149_;
}
}
}
}
}
v___jp_5153_:
{
uint64_t v___x_5159_; uint64_t v___x_5160_; uint8_t v___x_5161_; 
v___x_5159_ = lean_uint32_to_uint64(v_yExponent_5152_);
v___x_5160_ = 0ULL;
v___x_5161_ = lean_uint64_dec_eq(v___x_5159_, v___x_5160_);
if (v___x_5161_ == 0)
{
uint64_t v___x_5162_; uint64_t v___x_5163_; 
v___x_5162_ = 1ULL;
v___x_5163_ = lean_uint64_sub(v___x_5159_, v___x_5162_);
v___y_5112_ = v___y_5154_;
v___y_5113_ = v___y_5155_;
v___y_5114_ = v___y_5157_;
v___y_5115_ = v___y_5156_;
v___y_5116_ = v___y_5158_;
v___y_5117_ = v___x_5163_;
goto v___jp_5111_;
}
else
{
v___y_5112_ = v___y_5154_;
v___y_5113_ = v___y_5155_;
v___y_5114_ = v___y_5157_;
v___y_5115_ = v___y_5156_;
v___y_5116_ = v___y_5158_;
v___y_5117_ = v___x_5160_;
goto v___jp_5111_;
}
}
v___jp_5164_:
{
uint64_t v___x_5169_; uint64_t v___x_5170_; uint8_t v___x_5171_; 
v___x_5169_ = lean_uint32_to_uint64(v_xExponent_5150_);
v___x_5170_ = 0ULL;
v___x_5171_ = lean_uint64_dec_eq(v___x_5169_, v___x_5170_);
if (v___x_5171_ == 0)
{
uint64_t v___x_5172_; uint64_t v___x_5173_; 
v___x_5172_ = 1ULL;
v___x_5173_ = lean_uint64_sub(v___x_5169_, v___x_5172_);
v___y_5154_ = v___y_5165_;
v___y_5155_ = v___y_5166_;
v___y_5156_ = v___y_5168_;
v___y_5157_ = v___y_5167_;
v___y_5158_ = v___x_5173_;
goto v___jp_5153_;
}
else
{
v___y_5154_ = v___y_5165_;
v___y_5155_ = v___y_5166_;
v___y_5156_ = v___y_5168_;
v___y_5157_ = v___y_5167_;
v___y_5158_ = v___x_5170_;
goto v___jp_5153_;
}
}
v___jp_5174_:
{
uint32_t v___x_5179_; uint8_t v___x_5180_; 
v___x_5179_ = 0;
v___x_5180_ = lean_uint32_dec_eq(v_yExponent_5152_, v___x_5179_);
if (v___x_5180_ == 0)
{
uint64_t v___x_5181_; uint64_t v___x_5182_; uint64_t v___x_5183_; 
v___x_5181_ = lean_uint32_to_uint64(v___y_5175_);
v___x_5182_ = 8388608ULL;
v___x_5183_ = lean_uint64_lor(v___x_5181_, v___x_5182_);
v___y_5165_ = v___y_5178_;
v___y_5166_ = v___y_5176_;
v___y_5167_ = v___y_5177_;
v___y_5168_ = v___x_5183_;
goto v___jp_5164_;
}
else
{
uint64_t v___x_5184_; 
v___x_5184_ = lean_uint32_to_uint64(v___y_5175_);
v___y_5165_ = v___y_5178_;
v___y_5166_ = v___y_5176_;
v___y_5167_ = v___y_5177_;
v___y_5168_ = v___x_5184_;
goto v___jp_5164_;
}
}
v___jp_5185_:
{
uint32_t v___x_5187_; uint32_t v_xFraction_5188_; uint32_t v_yFraction_5189_; uint32_t v___x_5190_; uint8_t v___x_5191_; 
v___x_5187_ = 8388607;
v_xFraction_5188_ = lean_uint32_land(v_xBits_4813_, v___x_5187_);
v_yFraction_5189_ = lean_uint32_land(v_yBits_4814_, v___x_5187_);
v___x_5190_ = 0;
v___x_5191_ = lean_uint32_dec_eq(v_xExponent_5150_, v___x_5190_);
if (v___x_5191_ == 0)
{
uint64_t v___x_5192_; uint64_t v___x_5193_; uint64_t v___x_5194_; 
v___x_5192_ = lean_uint32_to_uint64(v_xFraction_5188_);
v___x_5193_ = 8388608ULL;
v___x_5194_ = lean_uint64_lor(v___x_5192_, v___x_5193_);
v___y_5175_ = v_yFraction_5189_;
v___y_5176_ = v___x_5187_;
v___y_5177_ = v___y_5186_;
v___y_5178_ = v___x_5194_;
goto v___jp_5174_;
}
else
{
uint64_t v___x_5195_; 
v___x_5195_ = lean_uint32_to_uint64(v_xFraction_5188_);
v___y_5175_ = v_yFraction_5189_;
v___y_5176_ = v___x_5187_;
v___y_5177_ = v___y_5186_;
v___y_5178_ = v___x_5195_;
goto v___jp_5174_;
}
}
v___jp_5196_:
{
uint8_t v___x_5197_; 
v___x_5197_ = 1;
v___y_5186_ = v___x_5197_;
goto v___jp_5185_;
}
v___jp_5198_:
{
uint8_t v___x_5199_; 
v___x_5199_ = 0;
v___y_5186_ = v___x_5199_;
goto v___jp_5185_;
}
v___jp_5200_:
{
if (v___y_5201_ == 0)
{
if (v___y_5202_ == 0)
{
goto v___jp_5198_;
}
else
{
goto v___jp_5196_;
}
}
else
{
if (v___y_5202_ == 0)
{
goto v___jp_5196_;
}
else
{
goto v___jp_5198_;
}
}
}
v___jp_5203_:
{
uint32_t v___x_5205_; uint32_t v___x_5206_; uint32_t v___x_5207_; uint8_t v___x_5208_; 
v___x_5205_ = 2147483648;
v___x_5206_ = lean_uint32_land(v_yBits_4814_, v___x_5205_);
v___x_5207_ = 0;
v___x_5208_ = lean_uint32_dec_eq(v___x_5206_, v___x_5207_);
if (v___x_5208_ == 0)
{
uint8_t v___x_5209_; 
v___x_5209_ = 1;
v___y_5201_ = v___y_5204_;
v___y_5202_ = v___x_5209_;
goto v___jp_5200_;
}
else
{
uint8_t v___x_5210_; 
v___x_5210_ = 0;
v___y_5201_ = v___y_5204_;
v___y_5202_ = v___x_5210_;
goto v___jp_5200_;
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_LowScale_core___boxed(lean_object* v_xBits_5217_, lean_object* v_yBits_5218_){
_start:
{
uint32_t v_xBits_boxed_5219_; uint32_t v_yBits_boxed_5220_; uint32_t v_res_5221_; lean_object* v_r_5222_; 
v_xBits_boxed_5219_ = lean_unbox_uint32(v_xBits_5217_);
lean_dec(v_xBits_5217_);
v_yBits_boxed_5220_ = lean_unbox_uint32(v_yBits_5218_);
lean_dec(v_yBits_5218_);
v_res_5221_ = lp_competition_Submission_LowScale_core(v_xBits_boxed_5219_, v_yBits_boxed_5220_);
v_r_5222_ = lean_box_uint32(v_res_5221_);
return v_r_5222_;
}
}
LEAN_EXPORT uint32_t lp_competition_Submission_LowScale_mul(uint32_t v_x_5223_, uint32_t v_y_5224_){
_start:
{
uint32_t v___y_5226_; uint32_t v___y_5230_; uint32_t v___y_5234_; uint32_t v___y_5235_; uint32_t v___y_5236_; uint64_t v___y_5240_; uint8_t v___y_5241_; uint32_t v___y_5242_; uint64_t v___y_5243_; uint32_t v___y_5255_; uint32_t v___y_5256_; uint32_t v___y_5257_; uint32_t v___y_5258_; uint32_t v___y_5259_; uint32_t v___y_5260_; uint32_t v___y_5267_; uint32_t v___y_5268_; uint8_t v___y_5269_; uint32_t v___y_5270_; uint32_t v___y_5271_; uint32_t v___y_5272_; uint64_t v___y_5276_; uint32_t v___y_5277_; uint64_t v___y_5278_; uint32_t v___y_5279_; uint8_t v___y_5280_; uint32_t v___y_5281_; uint64_t v___y_5282_; uint64_t v___y_5292_; uint32_t v___y_5293_; uint8_t v___y_5294_; uint64_t v___y_5295_; uint8_t v___y_5296_; uint32_t v___y_5297_; uint32_t v___y_5298_; uint64_t v___y_5299_; uint64_t v___y_5306_; uint64_t v___y_5307_; uint32_t v___y_5308_; uint32_t v___y_5309_; uint8_t v___y_5310_; uint32_t v___y_5311_; uint64_t v___y_5312_; uint64_t v___y_5318_; uint32_t v___y_5319_; uint64_t v___y_5320_; uint8_t v___y_5321_; uint32_t v___y_5322_; uint64_t v___y_5323_; uint32_t v___y_5324_; uint64_t v___y_5325_; uint64_t v___y_5380_; uint32_t v___y_5381_; uint64_t v___y_5382_; uint64_t v___y_5383_; uint32_t v___y_5384_; uint8_t v___y_5385_; uint64_t v___y_5386_; uint32_t v___y_5387_; uint64_t v___y_5388_; uint64_t v___y_5394_; uint64_t v___y_5395_; uint32_t v___y_5396_; uint64_t v___y_5397_; uint64_t v___y_5398_; uint64_t v___y_5399_; uint8_t v___y_5400_; uint32_t v___y_5401_; uint64_t v___y_5402_; uint32_t v___y_5403_; uint64_t v___y_5404_; uint64_t v___y_5409_; uint64_t v___y_5410_; uint32_t v___y_5411_; uint64_t v___y_5412_; uint32_t v___y_5413_; uint8_t v___y_5414_; uint64_t v___y_5415_; uint32_t v___y_5416_; uint64_t v___y_5417_; uint64_t v___y_5422_; uint32_t v___y_5423_; uint64_t v___y_5424_; uint64_t v___y_5425_; uint64_t v___y_5426_; uint8_t v___y_5427_; uint32_t v___y_5428_; uint64_t v___y_5429_; uint64_t v___y_5430_; uint32_t v___y_5431_; uint64_t v___y_5432_; uint64_t v___y_5437_; uint32_t v___y_5438_; uint64_t v___y_5439_; uint64_t v___y_5440_; uint32_t v___y_5441_; uint8_t v___y_5442_; uint64_t v___y_5443_; uint32_t v___y_5444_; uint64_t v___y_5445_; uint64_t v___y_5450_; uint64_t v___y_5451_; uint64_t v___y_5452_; uint32_t v___y_5453_; uint64_t v___y_5454_; uint64_t v___y_5455_; uint8_t v___y_5456_; uint32_t v___y_5457_; uint64_t v___y_5458_; uint32_t v___y_5459_; uint64_t v___y_5460_; uint64_t v___y_5465_; uint32_t v___y_5466_; uint64_t v___y_5467_; uint64_t v___y_5468_; uint32_t v___y_5469_; uint8_t v___y_5470_; uint64_t v___y_5471_; uint32_t v___y_5472_; uint64_t v___y_5473_; uint64_t v___y_5478_; uint64_t v___y_5479_; uint32_t v___y_5480_; uint64_t v___y_5481_; uint64_t v___y_5482_; uint64_t v___y_5483_; uint8_t v___y_5484_; uint32_t v___y_5485_; uint64_t v___y_5486_; uint32_t v___y_5487_; uint64_t v___y_5488_; uint64_t v___y_5493_; uint64_t v___y_5494_; uint32_t v___y_5495_; uint64_t v___y_5496_; uint32_t v___y_5497_; uint8_t v___y_5498_; uint64_t v___y_5499_; uint32_t v___y_5500_; uint64_t v___y_5501_; uint64_t v___y_5506_; uint32_t v___y_5507_; uint64_t v___y_5508_; uint64_t v___y_5509_; uint8_t v___y_5510_; uint32_t v___y_5511_; uint64_t v___y_5512_; uint32_t v___y_5513_; uint64_t v___y_5514_; uint32_t v___y_5518_; uint64_t v___y_5519_; uint32_t v___y_5520_; uint8_t v___y_5521_; uint64_t v___y_5522_; uint32_t v___y_5523_; uint32_t v___y_5532_; uint32_t v___y_5533_; uint32_t v___y_5534_; uint64_t v___y_5538_; uint8_t v___y_5539_; uint32_t v___y_5540_; uint64_t v___y_5541_; uint64_t v___y_5553_; uint32_t v___y_5554_; uint64_t v___y_5555_; uint64_t v___y_5556_; uint8_t v___y_5557_; uint32_t v___y_5558_; uint32_t v___y_5559_; uint64_t v___y_5560_; uint64_t v___y_5594_; uint32_t v___y_5595_; uint32_t v___y_5596_; uint64_t v___y_5597_; uint32_t v___y_5598_; uint8_t v___y_5599_; uint32_t v___y_5600_; uint64_t v___y_5601_; uint64_t v___y_5608_; uint32_t v___y_5609_; uint32_t v___y_5610_; uint32_t v___y_5611_; uint8_t v___y_5612_; uint32_t v___y_5613_; uint32_t v___y_5614_; uint64_t v___y_5615_; uint32_t v___y_5622_; uint32_t v___y_5623_; uint32_t v___y_5624_; uint32_t v___y_5625_; uint8_t v___y_5626_; uint32_t v___y_5627_; uint32_t v___y_5628_; uint64_t v___y_5629_; uint32_t v___y_5637_; uint32_t v___y_5638_; uint32_t v___y_5639_; uint32_t v___y_5640_; uint8_t v___y_5641_; uint32_t v___y_5652_; uint32_t v___y_5653_; uint32_t v___y_5654_; uint32_t v___y_5655_; uint32_t v___y_5658_; uint32_t v___y_5659_; uint8_t v___y_5660_; uint8_t v___y_5661_; uint32_t v___y_5662_; uint32_t v___y_5663_; uint8_t v___y_5664_; uint32_t v___y_5666_; uint32_t v___y_5667_; uint8_t v___y_5668_; uint32_t v___y_5669_; uint32_t v___y_5670_; uint8_t v___y_5671_; uint8_t v___y_5678_; uint32_t v___x_5695_; uint32_t v___x_5696_; uint32_t v___x_5697_; uint8_t v___x_5698_; 
v___x_5695_ = 4278190080;
v___x_5696_ = 1;
v___x_5697_ = lean_uint32_shift_left(v_x_5223_, v___x_5696_);
v___x_5698_ = lean_uint32_dec_le(v___x_5695_, v___x_5697_);
if (v___x_5698_ == 0)
{
uint32_t v___x_5699_; uint8_t v___x_5700_; 
v___x_5699_ = lean_uint32_shift_left(v_y_5224_, v___x_5696_);
v___x_5700_ = lean_uint32_dec_le(v___x_5695_, v___x_5699_);
v___y_5678_ = v___x_5700_;
goto v___jp_5677_;
}
else
{
v___y_5678_ = v___x_5698_;
goto v___jp_5677_;
}
v___jp_5225_:
{
uint32_t v___x_5227_; uint32_t v___x_5228_; 
v___x_5227_ = 8388608;
v___x_5228_ = lean_uint32_lor(v___y_5226_, v___x_5227_);
return v___x_5228_;
}
v___jp_5229_:
{
uint32_t v___x_5231_; uint32_t v___x_5232_; 
v___x_5231_ = 8388608;
v___x_5232_ = lean_uint32_lor(v___y_5230_, v___x_5231_);
return v___x_5232_;
}
v___jp_5233_:
{
uint32_t v___x_5237_; uint32_t v___x_5238_; 
v___x_5237_ = lean_uint32_land(v___y_5234_, v___y_5235_);
v___x_5238_ = lean_uint32_lor(v___y_5236_, v___x_5237_);
return v___x_5238_;
}
v___jp_5239_:
{
uint8_t v___x_5244_; 
v___x_5244_ = lean_uint64_dec_eq(v___y_5243_, v___y_5240_);
if (v___x_5244_ == 0)
{
uint64_t v___x_5245_; uint8_t v___x_5246_; 
v___x_5245_ = 8388608ULL;
v___x_5246_ = lean_uint64_dec_eq(v___y_5243_, v___x_5245_);
if (v___x_5246_ == 0)
{
uint32_t v___x_5247_; 
v___x_5247_ = lean_uint64_to_uint32(v___y_5243_);
if (v___y_5241_ == 0)
{
uint32_t v___x_5248_; 
v___x_5248_ = 0;
v___y_5234_ = v___x_5247_;
v___y_5235_ = v___y_5242_;
v___y_5236_ = v___x_5248_;
goto v___jp_5233_;
}
else
{
uint32_t v___x_5249_; 
v___x_5249_ = 2147483648;
v___y_5234_ = v___x_5247_;
v___y_5235_ = v___y_5242_;
v___y_5236_ = v___x_5249_;
goto v___jp_5233_;
}
}
else
{
if (v___y_5241_ == 0)
{
uint32_t v___x_5250_; 
v___x_5250_ = 0;
v___y_5226_ = v___x_5250_;
goto v___jp_5225_;
}
else
{
uint32_t v___x_5251_; 
v___x_5251_ = 2147483648;
v___y_5226_ = v___x_5251_;
goto v___jp_5225_;
}
}
}
else
{
if (v___y_5241_ == 0)
{
uint32_t v___x_5252_; 
v___x_5252_ = 0;
return v___x_5252_;
}
else
{
uint32_t v___x_5253_; 
v___x_5253_ = 2147483648;
return v___x_5253_;
}
}
}
v___jp_5254_:
{
uint32_t v___x_5261_; uint32_t v___x_5262_; uint32_t v___x_5263_; uint32_t v___x_5264_; uint32_t v___x_5265_; 
v___x_5261_ = lean_uint32_land(v___y_5256_, v___y_5257_);
v___x_5262_ = lean_uint32_shift_left(v___x_5261_, v___y_5255_);
v___x_5263_ = lean_uint32_lor(v___y_5260_, v___x_5262_);
v___x_5264_ = lean_uint32_land(v___y_5259_, v___y_5258_);
v___x_5265_ = lean_uint32_lor(v___x_5263_, v___x_5264_);
return v___x_5265_;
}
v___jp_5266_:
{
if (v___y_5269_ == 0)
{
uint32_t v___x_5273_; 
v___x_5273_ = 0;
v___y_5255_ = v___y_5268_;
v___y_5256_ = v___y_5267_;
v___y_5257_ = v___y_5270_;
v___y_5258_ = v___y_5271_;
v___y_5259_ = v___y_5272_;
v___y_5260_ = v___x_5273_;
goto v___jp_5254_;
}
else
{
uint32_t v___x_5274_; 
v___x_5274_ = 2147483648;
v___y_5255_ = v___y_5268_;
v___y_5256_ = v___y_5267_;
v___y_5257_ = v___y_5270_;
v___y_5258_ = v___y_5271_;
v___y_5259_ = v___y_5272_;
v___y_5260_ = v___x_5274_;
goto v___jp_5254_;
}
}
v___jp_5275_:
{
uint64_t v___x_5283_; uint64_t v_encodedExponent_5284_; uint32_t v___x_5285_; uint64_t v___x_5286_; uint8_t v___x_5287_; 
v___x_5283_ = 171ULL;
v_encodedExponent_5284_ = lean_uint64_sub(v___y_5278_, v___x_5283_);
v___x_5285_ = lean_uint64_to_uint32(v_encodedExponent_5284_);
v___x_5286_ = 8388608ULL;
v___x_5287_ = lean_uint64_dec_lt(v___y_5282_, v___x_5286_);
if (v___x_5287_ == 0)
{
uint64_t v___x_5288_; uint32_t v___x_5289_; 
v___x_5288_ = lean_uint64_sub(v___y_5282_, v___x_5286_);
v___x_5289_ = lean_uint64_to_uint32(v___x_5288_);
v___y_5267_ = v___x_5285_;
v___y_5268_ = v___y_5277_;
v___y_5269_ = v___y_5280_;
v___y_5270_ = v___y_5279_;
v___y_5271_ = v___y_5281_;
v___y_5272_ = v___x_5289_;
goto v___jp_5266_;
}
else
{
uint32_t v___x_5290_; 
v___x_5290_ = lean_uint64_to_uint32(v___y_5276_);
v___y_5267_ = v___x_5285_;
v___y_5268_ = v___y_5277_;
v___y_5269_ = v___y_5280_;
v___y_5270_ = v___y_5279_;
v___y_5271_ = v___y_5281_;
v___y_5272_ = v___x_5290_;
goto v___jp_5266_;
}
}
v___jp_5291_:
{
uint64_t v___x_5300_; uint8_t v___x_5301_; 
v___x_5300_ = 425ULL;
v___x_5301_ = lean_uint64_dec_lt(v___x_5300_, v___y_5299_);
if (v___x_5301_ == 0)
{
if (v___y_5294_ == 0)
{
v___y_5276_ = v___y_5292_;
v___y_5277_ = v___y_5293_;
v___y_5278_ = v___y_5299_;
v___y_5279_ = v___y_5297_;
v___y_5280_ = v___y_5296_;
v___y_5281_ = v___y_5298_;
v___y_5282_ = v___y_5295_;
goto v___jp_5275_;
}
else
{
uint64_t v___x_5302_; 
v___x_5302_ = 8388608ULL;
v___y_5276_ = v___y_5292_;
v___y_5277_ = v___y_5293_;
v___y_5278_ = v___y_5299_;
v___y_5279_ = v___y_5297_;
v___y_5280_ = v___y_5296_;
v___y_5281_ = v___y_5298_;
v___y_5282_ = v___x_5302_;
goto v___jp_5275_;
}
}
else
{
if (v___y_5296_ == 0)
{
uint32_t v___x_5303_; 
v___x_5303_ = 2139095040;
return v___x_5303_;
}
else
{
uint32_t v___x_5304_; 
v___x_5304_ = 4286578688;
return v___x_5304_;
}
}
}
v___jp_5305_:
{
uint64_t v___x_5313_; uint8_t v_carry_5314_; 
v___x_5313_ = 16777216ULL;
v_carry_5314_ = lean_uint64_dec_eq(v___y_5312_, v___x_5313_);
if (v_carry_5314_ == 0)
{
v___y_5292_ = v___y_5306_;
v___y_5293_ = v___y_5308_;
v___y_5294_ = v_carry_5314_;
v___y_5295_ = v___y_5312_;
v___y_5296_ = v___y_5310_;
v___y_5297_ = v___y_5309_;
v___y_5298_ = v___y_5311_;
v___y_5299_ = v___y_5307_;
goto v___jp_5291_;
}
else
{
uint64_t v___x_5315_; uint64_t v___x_5316_; 
v___x_5315_ = 1ULL;
v___x_5316_ = lean_uint64_add(v___y_5307_, v___x_5315_);
v___y_5292_ = v___y_5306_;
v___y_5293_ = v___y_5308_;
v___y_5294_ = v_carry_5314_;
v___y_5295_ = v___y_5312_;
v___y_5296_ = v___y_5310_;
v___y_5297_ = v___y_5309_;
v___y_5298_ = v___y_5311_;
v___y_5299_ = v___x_5316_;
goto v___jp_5291_;
}
}
v___jp_5317_:
{
uint64_t v_position_5326_; uint64_t v___x_5327_; uint8_t v___x_5328_; 
v_position_5326_ = lean_uint64_add(v___y_5325_, v___y_5320_);
v___x_5327_ = 172ULL;
v___x_5328_ = lean_uint64_dec_lt(v_position_5326_, v___x_5327_);
if (v___x_5328_ == 0)
{
uint64_t v___x_5329_; uint8_t v___x_5330_; 
v___x_5329_ = 23ULL;
v___x_5330_ = lean_uint64_dec_lt(v___y_5325_, v___x_5329_);
if (v___x_5330_ == 0)
{
uint64_t v___x_5331_; uint8_t v___x_5332_; 
v___x_5331_ = lean_uint64_sub(v___y_5325_, v___x_5329_);
v___x_5332_ = lean_uint64_dec_eq(v___x_5331_, v___y_5318_);
if (v___x_5332_ == 0)
{
uint64_t v___x_5333_; uint8_t v___x_5334_; 
v___x_5333_ = 64ULL;
v___x_5334_ = lean_uint64_dec_lt(v___x_5331_, v___x_5333_);
if (v___x_5334_ == 0)
{
uint8_t v___x_5335_; 
v___x_5335_ = lean_uint64_dec_eq(v___x_5331_, v___x_5333_);
if (v___x_5335_ == 0)
{
v___y_5306_ = v___y_5318_;
v___y_5307_ = v_position_5326_;
v___y_5308_ = v___y_5319_;
v___y_5309_ = v___y_5322_;
v___y_5310_ = v___y_5321_;
v___y_5311_ = v___y_5324_;
v___y_5312_ = v___y_5318_;
goto v___jp_5305_;
}
else
{
uint64_t v___x_5336_; uint8_t v___x_5337_; 
v___x_5336_ = 9223372036854775808ULL;
v___x_5337_ = lean_uint64_dec_lt(v___x_5336_, v___y_5323_);
if (v___x_5337_ == 0)
{
v___y_5306_ = v___y_5318_;
v___y_5307_ = v_position_5326_;
v___y_5308_ = v___y_5319_;
v___y_5309_ = v___y_5322_;
v___y_5310_ = v___y_5321_;
v___y_5311_ = v___y_5324_;
v___y_5312_ = v___y_5318_;
goto v___jp_5305_;
}
else
{
uint64_t v___x_5338_; 
v___x_5338_ = 1ULL;
v___y_5306_ = v___y_5318_;
v___y_5307_ = v_position_5326_;
v___y_5308_ = v___y_5319_;
v___y_5309_ = v___y_5322_;
v___y_5310_ = v___y_5321_;
v___y_5311_ = v___y_5324_;
v___y_5312_ = v___x_5338_;
goto v___jp_5305_;
}
}
}
else
{
uint64_t v_quotient_5339_; uint64_t v___x_5340_; uint64_t v___x_5341_; uint64_t v___x_5342_; uint64_t v_remainder_5343_; uint64_t v___x_5344_; uint64_t v_half_5345_; uint8_t v___x_5346_; 
v_quotient_5339_ = lean_uint64_shift_right(v___y_5323_, v___x_5331_);
v___x_5340_ = 1ULL;
v___x_5341_ = lean_uint64_shift_left(v___x_5340_, v___x_5331_);
v___x_5342_ = lean_uint64_sub(v___x_5341_, v___x_5340_);
v_remainder_5343_ = lean_uint64_land(v___y_5323_, v___x_5342_);
v___x_5344_ = lean_uint64_sub(v___x_5331_, v___x_5340_);
v_half_5345_ = lean_uint64_shift_left(v___x_5340_, v___x_5344_);
v___x_5346_ = lean_uint64_dec_lt(v_remainder_5343_, v_half_5345_);
if (v___x_5346_ == 0)
{
uint8_t v___x_5347_; 
v___x_5347_ = lean_uint64_dec_lt(v_half_5345_, v_remainder_5343_);
if (v___x_5347_ == 0)
{
uint64_t v___x_5348_; uint8_t v___x_5349_; 
v___x_5348_ = lean_uint64_land(v_quotient_5339_, v___x_5340_);
v___x_5349_ = lean_uint64_dec_eq(v___x_5348_, v___y_5318_);
if (v___x_5349_ == 0)
{
uint64_t v___x_5350_; 
v___x_5350_ = lean_uint64_add(v_quotient_5339_, v___x_5340_);
v___y_5306_ = v___y_5318_;
v___y_5307_ = v_position_5326_;
v___y_5308_ = v___y_5319_;
v___y_5309_ = v___y_5322_;
v___y_5310_ = v___y_5321_;
v___y_5311_ = v___y_5324_;
v___y_5312_ = v___x_5350_;
goto v___jp_5305_;
}
else
{
v___y_5306_ = v___y_5318_;
v___y_5307_ = v_position_5326_;
v___y_5308_ = v___y_5319_;
v___y_5309_ = v___y_5322_;
v___y_5310_ = v___y_5321_;
v___y_5311_ = v___y_5324_;
v___y_5312_ = v_quotient_5339_;
goto v___jp_5305_;
}
}
else
{
uint64_t v___x_5351_; 
v___x_5351_ = lean_uint64_add(v_quotient_5339_, v___x_5340_);
v___y_5306_ = v___y_5318_;
v___y_5307_ = v_position_5326_;
v___y_5308_ = v___y_5319_;
v___y_5309_ = v___y_5322_;
v___y_5310_ = v___y_5321_;
v___y_5311_ = v___y_5324_;
v___y_5312_ = v___x_5351_;
goto v___jp_5305_;
}
}
else
{
v___y_5306_ = v___y_5318_;
v___y_5307_ = v_position_5326_;
v___y_5308_ = v___y_5319_;
v___y_5309_ = v___y_5322_;
v___y_5310_ = v___y_5321_;
v___y_5311_ = v___y_5324_;
v___y_5312_ = v_quotient_5339_;
goto v___jp_5305_;
}
}
}
else
{
v___y_5306_ = v___y_5318_;
v___y_5307_ = v_position_5326_;
v___y_5308_ = v___y_5319_;
v___y_5309_ = v___y_5322_;
v___y_5310_ = v___y_5321_;
v___y_5311_ = v___y_5324_;
v___y_5312_ = v___y_5323_;
goto v___jp_5305_;
}
}
else
{
uint64_t v___x_5352_; uint64_t v___x_5353_; 
v___x_5352_ = lean_uint64_sub(v___x_5329_, v___y_5325_);
v___x_5353_ = lean_uint64_shift_left(v___y_5323_, v___x_5352_);
v___y_5306_ = v___y_5318_;
v___y_5307_ = v_position_5326_;
v___y_5308_ = v___y_5319_;
v___y_5309_ = v___y_5322_;
v___y_5310_ = v___y_5321_;
v___y_5311_ = v___y_5324_;
v___y_5312_ = v___x_5353_;
goto v___jp_5305_;
}
}
else
{
uint64_t v___x_5354_; uint8_t v___x_5355_; 
v___x_5354_ = 149ULL;
v___x_5355_ = lean_uint64_dec_lt(v___y_5320_, v___x_5354_);
if (v___x_5355_ == 0)
{
uint64_t v___x_5356_; uint64_t v___x_5357_; 
v___x_5356_ = lean_uint64_sub(v___y_5320_, v___x_5354_);
v___x_5357_ = lean_uint64_shift_left(v___y_5323_, v___x_5356_);
v___y_5240_ = v___y_5318_;
v___y_5241_ = v___y_5321_;
v___y_5242_ = v___y_5324_;
v___y_5243_ = v___x_5357_;
goto v___jp_5239_;
}
else
{
uint64_t v___x_5358_; uint8_t v___x_5359_; 
v___x_5358_ = lean_uint64_sub(v___x_5354_, v___y_5320_);
v___x_5359_ = lean_uint64_dec_eq(v___x_5358_, v___y_5318_);
if (v___x_5359_ == 0)
{
uint64_t v___x_5360_; uint8_t v___x_5361_; 
v___x_5360_ = 64ULL;
v___x_5361_ = lean_uint64_dec_lt(v___x_5358_, v___x_5360_);
if (v___x_5361_ == 0)
{
uint8_t v___x_5362_; 
v___x_5362_ = lean_uint64_dec_eq(v___x_5358_, v___x_5360_);
if (v___x_5362_ == 0)
{
v___y_5240_ = v___y_5318_;
v___y_5241_ = v___y_5321_;
v___y_5242_ = v___y_5324_;
v___y_5243_ = v___y_5318_;
goto v___jp_5239_;
}
else
{
uint64_t v___x_5363_; uint8_t v___x_5364_; 
v___x_5363_ = 9223372036854775808ULL;
v___x_5364_ = lean_uint64_dec_lt(v___x_5363_, v___y_5323_);
if (v___x_5364_ == 0)
{
v___y_5240_ = v___y_5318_;
v___y_5241_ = v___y_5321_;
v___y_5242_ = v___y_5324_;
v___y_5243_ = v___y_5318_;
goto v___jp_5239_;
}
else
{
uint64_t v___x_5365_; 
v___x_5365_ = 1ULL;
v___y_5240_ = v___y_5318_;
v___y_5241_ = v___y_5321_;
v___y_5242_ = v___y_5324_;
v___y_5243_ = v___x_5365_;
goto v___jp_5239_;
}
}
}
else
{
uint64_t v_quotient_5366_; uint64_t v___x_5367_; uint64_t v___x_5368_; uint64_t v___x_5369_; uint64_t v_remainder_5370_; uint64_t v___x_5371_; uint64_t v_half_5372_; uint8_t v___x_5373_; 
v_quotient_5366_ = lean_uint64_shift_right(v___y_5323_, v___x_5358_);
v___x_5367_ = 1ULL;
v___x_5368_ = lean_uint64_shift_left(v___x_5367_, v___x_5358_);
v___x_5369_ = lean_uint64_sub(v___x_5368_, v___x_5367_);
v_remainder_5370_ = lean_uint64_land(v___y_5323_, v___x_5369_);
v___x_5371_ = lean_uint64_sub(v___x_5358_, v___x_5367_);
v_half_5372_ = lean_uint64_shift_left(v___x_5367_, v___x_5371_);
v___x_5373_ = lean_uint64_dec_lt(v_remainder_5370_, v_half_5372_);
if (v___x_5373_ == 0)
{
uint8_t v___x_5374_; 
v___x_5374_ = lean_uint64_dec_lt(v_half_5372_, v_remainder_5370_);
if (v___x_5374_ == 0)
{
uint64_t v___x_5375_; uint8_t v___x_5376_; 
v___x_5375_ = lean_uint64_land(v_quotient_5366_, v___x_5367_);
v___x_5376_ = lean_uint64_dec_eq(v___x_5375_, v___y_5318_);
if (v___x_5376_ == 0)
{
uint64_t v___x_5377_; 
v___x_5377_ = lean_uint64_add(v_quotient_5366_, v___x_5367_);
v___y_5240_ = v___y_5318_;
v___y_5241_ = v___y_5321_;
v___y_5242_ = v___y_5324_;
v___y_5243_ = v___x_5377_;
goto v___jp_5239_;
}
else
{
v___y_5240_ = v___y_5318_;
v___y_5241_ = v___y_5321_;
v___y_5242_ = v___y_5324_;
v___y_5243_ = v_quotient_5366_;
goto v___jp_5239_;
}
}
else
{
uint64_t v___x_5378_; 
v___x_5378_ = lean_uint64_add(v_quotient_5366_, v___x_5367_);
v___y_5240_ = v___y_5318_;
v___y_5241_ = v___y_5321_;
v___y_5242_ = v___y_5324_;
v___y_5243_ = v___x_5378_;
goto v___jp_5239_;
}
}
else
{
v___y_5240_ = v___y_5318_;
v___y_5241_ = v___y_5321_;
v___y_5242_ = v___y_5324_;
v___y_5243_ = v_quotient_5366_;
goto v___jp_5239_;
}
}
}
else
{
v___y_5240_ = v___y_5318_;
v___y_5241_ = v___y_5321_;
v___y_5242_ = v___y_5324_;
v___y_5243_ = v___y_5323_;
goto v___jp_5239_;
}
}
}
}
v___jp_5379_:
{
uint64_t v___x_5389_; uint64_t v___x_5390_; uint8_t v___x_5391_; 
v___x_5389_ = 1ULL;
v___x_5390_ = lean_uint64_shift_right(v___y_5383_, v___x_5389_);
v___x_5391_ = lean_uint64_dec_eq(v___x_5390_, v___y_5380_);
if (v___x_5391_ == 0)
{
uint64_t v___x_5392_; 
v___x_5392_ = lean_uint64_add(v___y_5388_, v___x_5389_);
v___y_5318_ = v___y_5380_;
v___y_5319_ = v___y_5381_;
v___y_5320_ = v___y_5382_;
v___y_5321_ = v___y_5385_;
v___y_5322_ = v___y_5384_;
v___y_5323_ = v___y_5386_;
v___y_5324_ = v___y_5387_;
v___y_5325_ = v___x_5392_;
goto v___jp_5317_;
}
else
{
v___y_5318_ = v___y_5380_;
v___y_5319_ = v___y_5381_;
v___y_5320_ = v___y_5382_;
v___y_5321_ = v___y_5385_;
v___y_5322_ = v___y_5384_;
v___y_5323_ = v___y_5386_;
v___y_5324_ = v___y_5387_;
v___y_5325_ = v___y_5388_;
goto v___jp_5317_;
}
}
v___jp_5393_:
{
uint64_t v___x_5405_; uint8_t v___x_5406_; 
v___x_5405_ = lean_uint64_shift_right(v___y_5394_, v___y_5398_);
v___x_5406_ = lean_uint64_dec_eq(v___x_5405_, v___y_5395_);
if (v___x_5406_ == 0)
{
uint64_t v___x_5407_; 
v___x_5407_ = lean_uint64_add(v___y_5399_, v___y_5398_);
v___y_5380_ = v___y_5395_;
v___y_5381_ = v___y_5396_;
v___y_5382_ = v___y_5397_;
v___y_5383_ = v___y_5404_;
v___y_5384_ = v___y_5401_;
v___y_5385_ = v___y_5400_;
v___y_5386_ = v___y_5402_;
v___y_5387_ = v___y_5403_;
v___y_5388_ = v___x_5407_;
goto v___jp_5379_;
}
else
{
v___y_5380_ = v___y_5395_;
v___y_5381_ = v___y_5396_;
v___y_5382_ = v___y_5397_;
v___y_5383_ = v___y_5404_;
v___y_5384_ = v___y_5401_;
v___y_5385_ = v___y_5400_;
v___y_5386_ = v___y_5402_;
v___y_5387_ = v___y_5403_;
v___y_5388_ = v___y_5399_;
goto v___jp_5379_;
}
}
v___jp_5408_:
{
uint64_t v___x_5418_; uint64_t v___x_5419_; uint8_t v___x_5420_; 
v___x_5418_ = 2ULL;
v___x_5419_ = lean_uint64_shift_right(v___y_5410_, v___x_5418_);
v___x_5420_ = lean_uint64_dec_eq(v___x_5419_, v___y_5409_);
if (v___x_5420_ == 0)
{
v___y_5394_ = v___y_5410_;
v___y_5395_ = v___y_5409_;
v___y_5396_ = v___y_5411_;
v___y_5397_ = v___y_5412_;
v___y_5398_ = v___x_5418_;
v___y_5399_ = v___y_5417_;
v___y_5400_ = v___y_5414_;
v___y_5401_ = v___y_5413_;
v___y_5402_ = v___y_5415_;
v___y_5403_ = v___y_5416_;
v___y_5404_ = v___x_5419_;
goto v___jp_5393_;
}
else
{
v___y_5394_ = v___y_5410_;
v___y_5395_ = v___y_5409_;
v___y_5396_ = v___y_5411_;
v___y_5397_ = v___y_5412_;
v___y_5398_ = v___x_5418_;
v___y_5399_ = v___y_5417_;
v___y_5400_ = v___y_5414_;
v___y_5401_ = v___y_5413_;
v___y_5402_ = v___y_5415_;
v___y_5403_ = v___y_5416_;
v___y_5404_ = v___y_5410_;
goto v___jp_5393_;
}
}
v___jp_5421_:
{
uint64_t v___x_5433_; uint8_t v___x_5434_; 
v___x_5433_ = lean_uint64_shift_right(v___y_5426_, v___y_5425_);
v___x_5434_ = lean_uint64_dec_eq(v___x_5433_, v___y_5422_);
if (v___x_5434_ == 0)
{
uint64_t v___x_5435_; 
v___x_5435_ = lean_uint64_add(v___y_5430_, v___y_5425_);
v___y_5409_ = v___y_5422_;
v___y_5410_ = v___y_5432_;
v___y_5411_ = v___y_5423_;
v___y_5412_ = v___y_5424_;
v___y_5413_ = v___y_5428_;
v___y_5414_ = v___y_5427_;
v___y_5415_ = v___y_5429_;
v___y_5416_ = v___y_5431_;
v___y_5417_ = v___x_5435_;
goto v___jp_5408_;
}
else
{
v___y_5409_ = v___y_5422_;
v___y_5410_ = v___y_5432_;
v___y_5411_ = v___y_5423_;
v___y_5412_ = v___y_5424_;
v___y_5413_ = v___y_5428_;
v___y_5414_ = v___y_5427_;
v___y_5415_ = v___y_5429_;
v___y_5416_ = v___y_5431_;
v___y_5417_ = v___y_5430_;
goto v___jp_5408_;
}
}
v___jp_5436_:
{
uint64_t v___x_5446_; uint64_t v___x_5447_; uint8_t v___x_5448_; 
v___x_5446_ = 4ULL;
v___x_5447_ = lean_uint64_shift_right(v___y_5440_, v___x_5446_);
v___x_5448_ = lean_uint64_dec_eq(v___x_5447_, v___y_5437_);
if (v___x_5448_ == 0)
{
v___y_5422_ = v___y_5437_;
v___y_5423_ = v___y_5438_;
v___y_5424_ = v___y_5439_;
v___y_5425_ = v___x_5446_;
v___y_5426_ = v___y_5440_;
v___y_5427_ = v___y_5442_;
v___y_5428_ = v___y_5441_;
v___y_5429_ = v___y_5443_;
v___y_5430_ = v___y_5445_;
v___y_5431_ = v___y_5444_;
v___y_5432_ = v___x_5447_;
goto v___jp_5421_;
}
else
{
v___y_5422_ = v___y_5437_;
v___y_5423_ = v___y_5438_;
v___y_5424_ = v___y_5439_;
v___y_5425_ = v___x_5446_;
v___y_5426_ = v___y_5440_;
v___y_5427_ = v___y_5442_;
v___y_5428_ = v___y_5441_;
v___y_5429_ = v___y_5443_;
v___y_5430_ = v___y_5445_;
v___y_5431_ = v___y_5444_;
v___y_5432_ = v___y_5440_;
goto v___jp_5421_;
}
}
v___jp_5449_:
{
uint64_t v___x_5461_; uint8_t v___x_5462_; 
v___x_5461_ = lean_uint64_shift_right(v___y_5452_, v___y_5455_);
v___x_5462_ = lean_uint64_dec_eq(v___x_5461_, v___y_5451_);
if (v___x_5462_ == 0)
{
uint64_t v___x_5463_; 
v___x_5463_ = lean_uint64_add(v___y_5450_, v___y_5455_);
v___y_5437_ = v___y_5451_;
v___y_5438_ = v___y_5453_;
v___y_5439_ = v___y_5454_;
v___y_5440_ = v___y_5460_;
v___y_5441_ = v___y_5457_;
v___y_5442_ = v___y_5456_;
v___y_5443_ = v___y_5458_;
v___y_5444_ = v___y_5459_;
v___y_5445_ = v___x_5463_;
goto v___jp_5436_;
}
else
{
v___y_5437_ = v___y_5451_;
v___y_5438_ = v___y_5453_;
v___y_5439_ = v___y_5454_;
v___y_5440_ = v___y_5460_;
v___y_5441_ = v___y_5457_;
v___y_5442_ = v___y_5456_;
v___y_5443_ = v___y_5458_;
v___y_5444_ = v___y_5459_;
v___y_5445_ = v___y_5450_;
goto v___jp_5436_;
}
}
v___jp_5464_:
{
uint64_t v___x_5474_; uint64_t v___x_5475_; uint8_t v___x_5476_; 
v___x_5474_ = 8ULL;
v___x_5475_ = lean_uint64_shift_right(v___y_5467_, v___x_5474_);
v___x_5476_ = lean_uint64_dec_eq(v___x_5475_, v___y_5465_);
if (v___x_5476_ == 0)
{
v___y_5450_ = v___y_5473_;
v___y_5451_ = v___y_5465_;
v___y_5452_ = v___y_5467_;
v___y_5453_ = v___y_5466_;
v___y_5454_ = v___y_5468_;
v___y_5455_ = v___x_5474_;
v___y_5456_ = v___y_5470_;
v___y_5457_ = v___y_5469_;
v___y_5458_ = v___y_5471_;
v___y_5459_ = v___y_5472_;
v___y_5460_ = v___x_5475_;
goto v___jp_5449_;
}
else
{
v___y_5450_ = v___y_5473_;
v___y_5451_ = v___y_5465_;
v___y_5452_ = v___y_5467_;
v___y_5453_ = v___y_5466_;
v___y_5454_ = v___y_5468_;
v___y_5455_ = v___x_5474_;
v___y_5456_ = v___y_5470_;
v___y_5457_ = v___y_5469_;
v___y_5458_ = v___y_5471_;
v___y_5459_ = v___y_5472_;
v___y_5460_ = v___y_5467_;
goto v___jp_5449_;
}
}
v___jp_5477_:
{
uint64_t v___x_5489_; uint8_t v___x_5490_; 
v___x_5489_ = lean_uint64_shift_right(v___y_5479_, v___y_5483_);
v___x_5490_ = lean_uint64_dec_eq(v___x_5489_, v___y_5478_);
if (v___x_5490_ == 0)
{
uint64_t v___x_5491_; 
v___x_5491_ = lean_uint64_add(v___y_5482_, v___y_5483_);
v___y_5465_ = v___y_5478_;
v___y_5466_ = v___y_5480_;
v___y_5467_ = v___y_5488_;
v___y_5468_ = v___y_5481_;
v___y_5469_ = v___y_5485_;
v___y_5470_ = v___y_5484_;
v___y_5471_ = v___y_5486_;
v___y_5472_ = v___y_5487_;
v___y_5473_ = v___x_5491_;
goto v___jp_5464_;
}
else
{
v___y_5465_ = v___y_5478_;
v___y_5466_ = v___y_5480_;
v___y_5467_ = v___y_5488_;
v___y_5468_ = v___y_5481_;
v___y_5469_ = v___y_5485_;
v___y_5470_ = v___y_5484_;
v___y_5471_ = v___y_5486_;
v___y_5472_ = v___y_5487_;
v___y_5473_ = v___y_5482_;
goto v___jp_5464_;
}
}
v___jp_5492_:
{
uint64_t v___x_5502_; uint64_t v___x_5503_; uint8_t v___x_5504_; 
v___x_5502_ = 16ULL;
v___x_5503_ = lean_uint64_shift_right(v___y_5494_, v___x_5502_);
v___x_5504_ = lean_uint64_dec_eq(v___x_5503_, v___y_5493_);
if (v___x_5504_ == 0)
{
v___y_5478_ = v___y_5493_;
v___y_5479_ = v___y_5494_;
v___y_5480_ = v___y_5495_;
v___y_5481_ = v___y_5496_;
v___y_5482_ = v___y_5501_;
v___y_5483_ = v___x_5502_;
v___y_5484_ = v___y_5498_;
v___y_5485_ = v___y_5497_;
v___y_5486_ = v___y_5499_;
v___y_5487_ = v___y_5500_;
v___y_5488_ = v___x_5503_;
goto v___jp_5477_;
}
else
{
v___y_5478_ = v___y_5493_;
v___y_5479_ = v___y_5494_;
v___y_5480_ = v___y_5495_;
v___y_5481_ = v___y_5496_;
v___y_5482_ = v___y_5501_;
v___y_5483_ = v___x_5502_;
v___y_5484_ = v___y_5498_;
v___y_5485_ = v___y_5497_;
v___y_5486_ = v___y_5499_;
v___y_5487_ = v___y_5500_;
v___y_5488_ = v___y_5494_;
goto v___jp_5477_;
}
}
v___jp_5505_:
{
uint64_t v___x_5515_; uint8_t v___x_5516_; 
v___x_5515_ = lean_uint64_shift_right(v___y_5512_, v___y_5509_);
v___x_5516_ = lean_uint64_dec_eq(v___x_5515_, v___y_5506_);
if (v___x_5516_ == 0)
{
v___y_5493_ = v___y_5506_;
v___y_5494_ = v___y_5514_;
v___y_5495_ = v___y_5507_;
v___y_5496_ = v___y_5508_;
v___y_5497_ = v___y_5511_;
v___y_5498_ = v___y_5510_;
v___y_5499_ = v___y_5512_;
v___y_5500_ = v___y_5513_;
v___y_5501_ = v___y_5509_;
goto v___jp_5492_;
}
else
{
v___y_5493_ = v___y_5506_;
v___y_5494_ = v___y_5514_;
v___y_5495_ = v___y_5507_;
v___y_5496_ = v___y_5508_;
v___y_5497_ = v___y_5511_;
v___y_5498_ = v___y_5510_;
v___y_5499_ = v___y_5512_;
v___y_5500_ = v___y_5513_;
v___y_5501_ = v___y_5506_;
goto v___jp_5492_;
}
}
v___jp_5517_:
{
uint64_t v___x_5524_; uint8_t v___x_5525_; 
v___x_5524_ = 0ULL;
v___x_5525_ = lean_uint64_dec_eq(v___y_5522_, v___x_5524_);
if (v___x_5525_ == 0)
{
uint64_t v___x_5526_; uint64_t v___x_5527_; uint8_t v___x_5528_; 
v___x_5526_ = 32ULL;
v___x_5527_ = lean_uint64_shift_right(v___y_5522_, v___x_5526_);
v___x_5528_ = lean_uint64_dec_eq(v___x_5527_, v___x_5524_);
if (v___x_5528_ == 0)
{
v___y_5506_ = v___x_5524_;
v___y_5507_ = v___y_5518_;
v___y_5508_ = v___y_5519_;
v___y_5509_ = v___x_5526_;
v___y_5510_ = v___y_5521_;
v___y_5511_ = v___y_5520_;
v___y_5512_ = v___y_5522_;
v___y_5513_ = v___y_5523_;
v___y_5514_ = v___x_5527_;
goto v___jp_5505_;
}
else
{
v___y_5506_ = v___x_5524_;
v___y_5507_ = v___y_5518_;
v___y_5508_ = v___y_5519_;
v___y_5509_ = v___x_5526_;
v___y_5510_ = v___y_5521_;
v___y_5511_ = v___y_5520_;
v___y_5512_ = v___y_5522_;
v___y_5513_ = v___y_5523_;
v___y_5514_ = v___y_5522_;
goto v___jp_5505_;
}
}
else
{
if (v___y_5521_ == 0)
{
uint32_t v___x_5529_; 
v___x_5529_ = 0;
return v___x_5529_;
}
else
{
uint32_t v___x_5530_; 
v___x_5530_ = 2147483648;
return v___x_5530_;
}
}
}
v___jp_5531_:
{
uint32_t v___x_5535_; uint32_t v___x_5536_; 
v___x_5535_ = lean_uint32_land(v___y_5532_, v___y_5533_);
v___x_5536_ = lean_uint32_lor(v___y_5534_, v___x_5535_);
return v___x_5536_;
}
v___jp_5537_:
{
uint8_t v___x_5542_; 
v___x_5542_ = lean_uint64_dec_eq(v___y_5541_, v___y_5538_);
if (v___x_5542_ == 0)
{
uint64_t v___x_5543_; uint8_t v___x_5544_; 
v___x_5543_ = 8388608ULL;
v___x_5544_ = lean_uint64_dec_eq(v___y_5541_, v___x_5543_);
if (v___x_5544_ == 0)
{
uint32_t v___x_5545_; 
v___x_5545_ = lean_uint64_to_uint32(v___y_5541_);
if (v___y_5539_ == 0)
{
uint32_t v___x_5546_; 
v___x_5546_ = 0;
v___y_5532_ = v___x_5545_;
v___y_5533_ = v___y_5540_;
v___y_5534_ = v___x_5546_;
goto v___jp_5531_;
}
else
{
uint32_t v___x_5547_; 
v___x_5547_ = 2147483648;
v___y_5532_ = v___x_5545_;
v___y_5533_ = v___y_5540_;
v___y_5534_ = v___x_5547_;
goto v___jp_5531_;
}
}
else
{
if (v___y_5539_ == 0)
{
uint32_t v___x_5548_; 
v___x_5548_ = 0;
v___y_5230_ = v___x_5548_;
goto v___jp_5229_;
}
else
{
uint32_t v___x_5549_; 
v___x_5549_ = 2147483648;
v___y_5230_ = v___x_5549_;
goto v___jp_5229_;
}
}
}
else
{
if (v___y_5539_ == 0)
{
uint32_t v___x_5550_; 
v___x_5550_ = 0;
return v___x_5550_;
}
else
{
uint32_t v___x_5551_; 
v___x_5551_ = 2147483648;
return v___x_5551_;
}
}
}
v___jp_5552_:
{
uint64_t v___x_5561_; uint64_t v___x_5562_; uint64_t v___x_5563_; uint8_t v___x_5564_; 
v___x_5561_ = lean_uint64_mul(v___y_5553_, v___y_5556_);
v___x_5562_ = lean_uint64_add(v___y_5555_, v___y_5560_);
v___x_5563_ = 281474976710656ULL;
v___x_5564_ = lean_uint64_dec_lt(v___x_5561_, v___x_5563_);
if (v___x_5564_ == 0)
{
v___y_5518_ = v___y_5554_;
v___y_5519_ = v___x_5562_;
v___y_5520_ = v___y_5558_;
v___y_5521_ = v___y_5557_;
v___y_5522_ = v___x_5561_;
v___y_5523_ = v___y_5559_;
goto v___jp_5517_;
}
else
{
uint64_t v___x_5565_; uint8_t v___x_5566_; 
v___x_5565_ = 123ULL;
v___x_5566_ = lean_uint64_dec_le(v___x_5562_, v___x_5565_);
if (v___x_5566_ == 0)
{
v___y_5518_ = v___y_5554_;
v___y_5519_ = v___x_5562_;
v___y_5520_ = v___y_5558_;
v___y_5521_ = v___y_5557_;
v___y_5522_ = v___x_5561_;
v___y_5523_ = v___y_5559_;
goto v___jp_5517_;
}
else
{
uint64_t v___x_5567_; uint8_t v___x_5568_; 
v___x_5567_ = 0ULL;
v___x_5568_ = lean_uint64_dec_eq(v___x_5561_, v___x_5567_);
if (v___x_5568_ == 0)
{
uint64_t v___x_5569_; uint64_t v___x_5570_; uint8_t v___x_5571_; 
v___x_5569_ = 149ULL;
v___x_5570_ = lean_uint64_sub(v___x_5569_, v___x_5562_);
v___x_5571_ = lean_uint64_dec_eq(v___x_5570_, v___x_5567_);
if (v___x_5571_ == 0)
{
uint64_t v___x_5572_; uint8_t v___x_5573_; 
v___x_5572_ = 64ULL;
v___x_5573_ = lean_uint64_dec_lt(v___x_5570_, v___x_5572_);
if (v___x_5573_ == 0)
{
uint8_t v___x_5574_; 
v___x_5574_ = lean_uint64_dec_eq(v___x_5570_, v___x_5572_);
if (v___x_5574_ == 0)
{
v___y_5538_ = v___x_5567_;
v___y_5539_ = v___y_5557_;
v___y_5540_ = v___y_5559_;
v___y_5541_ = v___x_5567_;
goto v___jp_5537_;
}
else
{
uint64_t v___x_5575_; uint8_t v___x_5576_; 
v___x_5575_ = 9223372036854775808ULL;
v___x_5576_ = lean_uint64_dec_lt(v___x_5575_, v___x_5561_);
if (v___x_5576_ == 0)
{
v___y_5538_ = v___x_5567_;
v___y_5539_ = v___y_5557_;
v___y_5540_ = v___y_5559_;
v___y_5541_ = v___x_5567_;
goto v___jp_5537_;
}
else
{
uint64_t v___x_5577_; 
v___x_5577_ = 1ULL;
v___y_5538_ = v___x_5567_;
v___y_5539_ = v___y_5557_;
v___y_5540_ = v___y_5559_;
v___y_5541_ = v___x_5577_;
goto v___jp_5537_;
}
}
}
else
{
uint64_t v_quotient_5578_; uint64_t v___x_5579_; uint64_t v___x_5580_; uint64_t v___x_5581_; uint64_t v_remainder_5582_; uint64_t v___x_5583_; uint64_t v_half_5584_; uint8_t v___x_5585_; 
v_quotient_5578_ = lean_uint64_shift_right(v___x_5561_, v___x_5570_);
v___x_5579_ = 1ULL;
v___x_5580_ = lean_uint64_shift_left(v___x_5579_, v___x_5570_);
v___x_5581_ = lean_uint64_sub(v___x_5580_, v___x_5579_);
v_remainder_5582_ = lean_uint64_land(v___x_5561_, v___x_5581_);
v___x_5583_ = lean_uint64_sub(v___x_5570_, v___x_5579_);
v_half_5584_ = lean_uint64_shift_left(v___x_5579_, v___x_5583_);
v___x_5585_ = lean_uint64_dec_lt(v_remainder_5582_, v_half_5584_);
if (v___x_5585_ == 0)
{
uint8_t v___x_5586_; 
v___x_5586_ = lean_uint64_dec_lt(v_half_5584_, v_remainder_5582_);
if (v___x_5586_ == 0)
{
uint64_t v___x_5587_; uint8_t v___x_5588_; 
v___x_5587_ = lean_uint64_land(v_quotient_5578_, v___x_5579_);
v___x_5588_ = lean_uint64_dec_eq(v___x_5587_, v___x_5567_);
if (v___x_5588_ == 0)
{
uint64_t v___x_5589_; 
v___x_5589_ = lean_uint64_add(v_quotient_5578_, v___x_5579_);
v___y_5538_ = v___x_5567_;
v___y_5539_ = v___y_5557_;
v___y_5540_ = v___y_5559_;
v___y_5541_ = v___x_5589_;
goto v___jp_5537_;
}
else
{
v___y_5538_ = v___x_5567_;
v___y_5539_ = v___y_5557_;
v___y_5540_ = v___y_5559_;
v___y_5541_ = v_quotient_5578_;
goto v___jp_5537_;
}
}
else
{
uint64_t v___x_5590_; 
v___x_5590_ = lean_uint64_add(v_quotient_5578_, v___x_5579_);
v___y_5538_ = v___x_5567_;
v___y_5539_ = v___y_5557_;
v___y_5540_ = v___y_5559_;
v___y_5541_ = v___x_5590_;
goto v___jp_5537_;
}
}
else
{
v___y_5538_ = v___x_5567_;
v___y_5539_ = v___y_5557_;
v___y_5540_ = v___y_5559_;
v___y_5541_ = v_quotient_5578_;
goto v___jp_5537_;
}
}
}
else
{
v___y_5538_ = v___x_5567_;
v___y_5539_ = v___y_5557_;
v___y_5540_ = v___y_5559_;
v___y_5541_ = v___x_5561_;
goto v___jp_5537_;
}
}
else
{
if (v___y_5557_ == 0)
{
uint32_t v___x_5591_; 
v___x_5591_ = 0;
return v___x_5591_;
}
else
{
uint32_t v___x_5592_; 
v___x_5592_ = 2147483648;
return v___x_5592_;
}
}
}
}
}
v___jp_5593_:
{
uint64_t v___x_5602_; uint64_t v___x_5603_; uint8_t v___x_5604_; 
v___x_5602_ = lean_uint32_to_uint64(v___y_5595_);
v___x_5603_ = 0ULL;
v___x_5604_ = lean_uint64_dec_eq(v___x_5602_, v___x_5603_);
if (v___x_5604_ == 0)
{
uint64_t v___x_5605_; uint64_t v___x_5606_; 
v___x_5605_ = 1ULL;
v___x_5606_ = lean_uint64_sub(v___x_5602_, v___x_5605_);
v___y_5553_ = v___y_5594_;
v___y_5554_ = v___y_5596_;
v___y_5555_ = v___y_5601_;
v___y_5556_ = v___y_5597_;
v___y_5557_ = v___y_5599_;
v___y_5558_ = v___y_5598_;
v___y_5559_ = v___y_5600_;
v___y_5560_ = v___x_5606_;
goto v___jp_5552_;
}
else
{
v___y_5553_ = v___y_5594_;
v___y_5554_ = v___y_5596_;
v___y_5555_ = v___y_5601_;
v___y_5556_ = v___y_5597_;
v___y_5557_ = v___y_5599_;
v___y_5558_ = v___y_5598_;
v___y_5559_ = v___y_5600_;
v___y_5560_ = v___x_5603_;
goto v___jp_5552_;
}
}
v___jp_5607_:
{
uint64_t v___x_5616_; uint64_t v___x_5617_; uint8_t v___x_5618_; 
v___x_5616_ = lean_uint32_to_uint64(v___y_5611_);
v___x_5617_ = 0ULL;
v___x_5618_ = lean_uint64_dec_eq(v___x_5616_, v___x_5617_);
if (v___x_5618_ == 0)
{
uint64_t v___x_5619_; uint64_t v___x_5620_; 
v___x_5619_ = 1ULL;
v___x_5620_ = lean_uint64_sub(v___x_5616_, v___x_5619_);
v___y_5594_ = v___y_5608_;
v___y_5595_ = v___y_5610_;
v___y_5596_ = v___y_5609_;
v___y_5597_ = v___y_5615_;
v___y_5598_ = v___y_5613_;
v___y_5599_ = v___y_5612_;
v___y_5600_ = v___y_5614_;
v___y_5601_ = v___x_5620_;
goto v___jp_5593_;
}
else
{
v___y_5594_ = v___y_5608_;
v___y_5595_ = v___y_5610_;
v___y_5596_ = v___y_5609_;
v___y_5597_ = v___y_5615_;
v___y_5598_ = v___y_5613_;
v___y_5599_ = v___y_5612_;
v___y_5600_ = v___y_5614_;
v___y_5601_ = v___x_5617_;
goto v___jp_5593_;
}
}
v___jp_5621_:
{
uint32_t v___x_5630_; uint8_t v___x_5631_; 
v___x_5630_ = 0;
v___x_5631_ = lean_uint32_dec_eq(v___y_5622_, v___x_5630_);
if (v___x_5631_ == 0)
{
uint64_t v___x_5632_; uint64_t v___x_5633_; uint64_t v___x_5634_; 
v___x_5632_ = lean_uint32_to_uint64(v___y_5624_);
v___x_5633_ = 8388608ULL;
v___x_5634_ = lean_uint64_lor(v___x_5632_, v___x_5633_);
v___y_5608_ = v___y_5629_;
v___y_5609_ = v___y_5623_;
v___y_5610_ = v___y_5622_;
v___y_5611_ = v___y_5627_;
v___y_5612_ = v___y_5626_;
v___y_5613_ = v___y_5625_;
v___y_5614_ = v___y_5628_;
v___y_5615_ = v___x_5634_;
goto v___jp_5607_;
}
else
{
uint64_t v___x_5635_; 
v___x_5635_ = lean_uint32_to_uint64(v___y_5624_);
v___y_5608_ = v___y_5629_;
v___y_5609_ = v___y_5623_;
v___y_5610_ = v___y_5622_;
v___y_5611_ = v___y_5627_;
v___y_5612_ = v___y_5626_;
v___y_5613_ = v___y_5625_;
v___y_5614_ = v___y_5628_;
v___y_5615_ = v___x_5635_;
goto v___jp_5607_;
}
}
v___jp_5636_:
{
uint32_t v___x_5642_; uint32_t v_xFraction_5643_; uint32_t v_yFraction_5644_; uint32_t v___x_5645_; uint8_t v___x_5646_; 
v___x_5642_ = 8388607;
v_xFraction_5643_ = lean_uint32_land(v_x_5223_, v___x_5642_);
v_yFraction_5644_ = lean_uint32_land(v_y_5224_, v___x_5642_);
v___x_5645_ = 0;
v___x_5646_ = lean_uint32_dec_eq(v___y_5639_, v___x_5645_);
if (v___x_5646_ == 0)
{
uint64_t v___x_5647_; uint64_t v___x_5648_; uint64_t v___x_5649_; 
v___x_5647_ = lean_uint32_to_uint64(v_xFraction_5643_);
v___x_5648_ = 8388608ULL;
v___x_5649_ = lean_uint64_lor(v___x_5647_, v___x_5648_);
v___y_5622_ = v___y_5638_;
v___y_5623_ = v___y_5637_;
v___y_5624_ = v_yFraction_5644_;
v___y_5625_ = v___y_5640_;
v___y_5626_ = v___y_5641_;
v___y_5627_ = v___y_5639_;
v___y_5628_ = v___x_5642_;
v___y_5629_ = v___x_5649_;
goto v___jp_5621_;
}
else
{
uint64_t v___x_5650_; 
v___x_5650_ = lean_uint32_to_uint64(v_xFraction_5643_);
v___y_5622_ = v___y_5638_;
v___y_5623_ = v___y_5637_;
v___y_5624_ = v_yFraction_5644_;
v___y_5625_ = v___y_5640_;
v___y_5626_ = v___y_5641_;
v___y_5627_ = v___y_5639_;
v___y_5628_ = v___x_5642_;
v___y_5629_ = v___x_5650_;
goto v___jp_5621_;
}
}
v___jp_5651_:
{
uint8_t v___x_5656_; 
v___x_5656_ = 1;
v___y_5637_ = v___y_5653_;
v___y_5638_ = v___y_5652_;
v___y_5639_ = v___y_5655_;
v___y_5640_ = v___y_5654_;
v___y_5641_ = v___x_5656_;
goto v___jp_5636_;
}
v___jp_5657_:
{
if (v___y_5660_ == 0)
{
if (v___y_5664_ == 0)
{
v___y_5637_ = v___y_5659_;
v___y_5638_ = v___y_5658_;
v___y_5639_ = v___y_5663_;
v___y_5640_ = v___y_5662_;
v___y_5641_ = v___y_5661_;
goto v___jp_5636_;
}
else
{
v___y_5652_ = v___y_5658_;
v___y_5653_ = v___y_5659_;
v___y_5654_ = v___y_5662_;
v___y_5655_ = v___y_5663_;
goto v___jp_5651_;
}
}
else
{
if (v___y_5664_ == 0)
{
v___y_5652_ = v___y_5658_;
v___y_5653_ = v___y_5659_;
v___y_5654_ = v___y_5662_;
v___y_5655_ = v___y_5663_;
goto v___jp_5651_;
}
else
{
v___y_5637_ = v___y_5659_;
v___y_5638_ = v___y_5658_;
v___y_5639_ = v___y_5663_;
v___y_5640_ = v___y_5662_;
v___y_5641_ = v___y_5661_;
goto v___jp_5636_;
}
}
}
v___jp_5665_:
{
uint32_t v___x_5672_; uint32_t v___x_5673_; uint32_t v___x_5674_; uint8_t v___x_5675_; 
v___x_5672_ = 2147483648;
v___x_5673_ = lean_uint32_land(v_y_5224_, v___x_5672_);
v___x_5674_ = 0;
v___x_5675_ = lean_uint32_dec_eq(v___x_5673_, v___x_5674_);
if (v___x_5675_ == 0)
{
uint8_t v___x_5676_; 
v___x_5676_ = 1;
v___y_5658_ = v___y_5667_;
v___y_5659_ = v___y_5666_;
v___y_5660_ = v___y_5671_;
v___y_5661_ = v___y_5668_;
v___y_5662_ = v___y_5670_;
v___y_5663_ = v___y_5669_;
v___y_5664_ = v___x_5676_;
goto v___jp_5657_;
}
else
{
v___y_5658_ = v___y_5667_;
v___y_5659_ = v___y_5666_;
v___y_5660_ = v___y_5671_;
v___y_5661_ = v___y_5668_;
v___y_5662_ = v___y_5670_;
v___y_5663_ = v___y_5669_;
v___y_5664_ = v___y_5668_;
goto v___jp_5657_;
}
}
v___jp_5677_:
{
if (v___y_5678_ == 0)
{
uint32_t v___x_5679_; uint32_t v___x_5680_; uint32_t v___x_5681_; uint32_t v_xExponent_5682_; uint32_t v___x_5683_; uint32_t v_yExponent_5684_; uint32_t v___x_5685_; uint32_t v___x_5686_; uint32_t v___x_5687_; uint8_t v___x_5688_; 
v___x_5679_ = 23;
v___x_5680_ = lean_uint32_shift_right(v_x_5223_, v___x_5679_);
v___x_5681_ = 255;
v_xExponent_5682_ = lean_uint32_land(v___x_5680_, v___x_5681_);
v___x_5683_ = lean_uint32_shift_right(v_y_5224_, v___x_5679_);
v_yExponent_5684_ = lean_uint32_land(v___x_5683_, v___x_5681_);
v___x_5685_ = 2147483648;
v___x_5686_ = lean_uint32_land(v_x_5223_, v___x_5685_);
v___x_5687_ = 0;
v___x_5688_ = lean_uint32_dec_eq(v___x_5686_, v___x_5687_);
if (v___x_5688_ == 0)
{
uint8_t v___x_5689_; 
v___x_5689_ = 1;
v___y_5666_ = v___x_5679_;
v___y_5667_ = v_yExponent_5684_;
v___y_5668_ = v___y_5678_;
v___y_5669_ = v_xExponent_5682_;
v___y_5670_ = v___x_5681_;
v___y_5671_ = v___x_5689_;
goto v___jp_5665_;
}
else
{
v___y_5666_ = v___x_5679_;
v___y_5667_ = v_yExponent_5684_;
v___y_5668_ = v___y_5678_;
v___y_5669_ = v_xExponent_5682_;
v___y_5670_ = v___x_5681_;
v___y_5671_ = v___y_5678_;
goto v___jp_5665_;
}
}
else
{
lean_object* v___x_5690_; lean_object* v___x_5691_; lean_object* v___x_5692_; lean_object* v___x_5693_; uint32_t v___x_5694_; 
v___x_5690_ = ((lean_object*)(lp_competition_Submission_TunedAdd_Fmt___closed__0));
v___x_5691_ = lean_uint32_to_nat(v_x_5223_);
v___x_5692_ = lean_uint32_to_nat(v_y_5224_);
v___x_5693_ = lp_floatlib_FloatLib_Floats_Formats_BinaryInterchange_Model_MulBackend_word(v___x_5690_, v___x_5691_, v___x_5692_);
v___x_5694_ = lean_uint32_of_nat(v___x_5693_);
lean_dec(v___x_5693_);
return v___x_5694_;
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_LowScale_mul___boxed(lean_object* v_x_5701_, lean_object* v_y_5702_){
_start:
{
uint32_t v_x_boxed_5703_; uint32_t v_y_boxed_5704_; uint32_t v_res_5705_; lean_object* v_r_5706_; 
v_x_boxed_5703_ = lean_unbox_uint32(v_x_5701_);
lean_dec(v_x_5701_);
v_y_boxed_5704_ = lean_unbox_uint32(v_y_5702_);
lean_dec(v_y_5702_);
v_res_5705_ = lp_competition_Submission_LowScale_mul(v_x_boxed_5703_, v_y_boxed_5704_);
v_r_5706_ = lean_box_uint32(v_res_5705_);
return v_r_5706_;
}
}
LEAN_EXPORT uint32_t lp_competition_Submission_add(uint32_t v_x_5707_, uint32_t v_y_5708_){
_start:
{
float v___y_5710_; float v___y_5711_; float v___y_5715_; uint8_t v___y_5716_; float v___y_5731_; uint8_t v___y_5741_; uint32_t v___x_5755_; uint32_t v___x_5756_; uint32_t v___x_5757_; uint32_t v___x_5758_; uint8_t v___x_5759_; 
v___x_5755_ = 23;
v___x_5756_ = lean_uint32_shift_right(v_x_5707_, v___x_5755_);
v___x_5757_ = 255;
v___x_5758_ = lean_uint32_land(v___x_5756_, v___x_5757_);
v___x_5759_ = lean_uint32_dec_eq(v___x_5758_, v___x_5757_);
if (v___x_5759_ == 0)
{
uint32_t v___x_5760_; uint32_t v___x_5761_; uint8_t v___x_5762_; 
v___x_5760_ = lean_uint32_shift_right(v_y_5708_, v___x_5755_);
v___x_5761_ = lean_uint32_land(v___x_5760_, v___x_5757_);
v___x_5762_ = lean_uint32_dec_eq(v___x_5761_, v___x_5757_);
if (v___x_5762_ == 0)
{
uint32_t v___x_5763_; uint32_t v_a_5764_; uint32_t v___x_5765_; uint32_t v___x_5766_; uint32_t v___x_5767_; uint8_t v___x_5768_; 
v___x_5763_ = 2147483647;
v_a_5764_ = lean_uint32_land(v_x_5707_, v___x_5763_);
v___x_5765_ = 201326591;
v___x_5766_ = 1;
v___x_5767_ = lean_uint32_sub(v_a_5764_, v___x_5766_);
v___x_5768_ = lean_uint32_dec_le(v___x_5765_, v___x_5767_);
if (v___x_5768_ == 0)
{
v___y_5741_ = v___x_5768_;
goto v___jp_5740_;
}
else
{
uint32_t v___x_5769_; uint8_t v___x_5770_; 
v___x_5769_ = 2139095040;
v___x_5770_ = lean_uint32_dec_lt(v_a_5764_, v___x_5769_);
v___y_5741_ = v___x_5770_;
goto v___jp_5740_;
}
}
else
{
uint32_t v___x_5771_; 
v___x_5771_ = lp_competition_Submission_TunedAdd_add(v_x_5707_, v_y_5708_);
return v___x_5771_;
}
}
else
{
uint32_t v___x_5772_; 
v___x_5772_ = lp_competition_Submission_TunedAdd_add(v_x_5707_, v_y_5708_);
return v___x_5772_;
}
v___jp_5709_:
{
float v___x_5712_; uint32_t v___x_5713_; 
v___x_5712_ = lean_float32_add(v___y_5710_, v___y_5711_);
v___x_5713_ = lean_float32_to_bits(v___x_5712_);
return v___x_5713_;
}
v___jp_5714_:
{
if (v___y_5716_ == 0)
{
float v___x_5717_; 
v___x_5717_ = lean_float32_of_bits(v_y_5708_);
v___y_5710_ = v___y_5715_;
v___y_5711_ = v___x_5717_;
goto v___jp_5709_;
}
else
{
uint32_t v___x_5718_; uint32_t v___x_5719_; uint32_t v___x_5720_; uint32_t v___x_5721_; float v___x_5722_; lean_object* v___x_5723_; uint32_t v___x_5724_; uint32_t v___x_5725_; lean_object* v___x_5726_; lean_object* v___x_5727_; float v___x_5728_; float v___x_5729_; 
v___x_5718_ = 8388607;
v___x_5719_ = lean_uint32_land(v_y_5708_, v___x_5718_);
v___x_5720_ = 8388608;
v___x_5721_ = lean_uint32_lor(v___x_5719_, v___x_5720_);
v___x_5722_ = lean_uint32_to_float32(v___x_5721_);
v___x_5723_ = lp_competition_R2W01b_scaleTable;
v___x_5724_ = 23;
v___x_5725_ = lean_uint32_shift_right(v_y_5708_, v___x_5724_);
v___x_5726_ = lean_uint32_to_nat(v___x_5725_);
v___x_5727_ = lean_array_fget_borrowed(v___x_5723_, v___x_5726_);
lean_dec(v___x_5726_);
v___x_5728_ = lean_unbox_float32(v___x_5727_);
v___x_5729_ = lean_float32_mul(v___x_5722_, v___x_5728_);
v___y_5710_ = v___y_5715_;
v___y_5711_ = v___x_5729_;
goto v___jp_5709_;
}
}
v___jp_5730_:
{
uint32_t v___x_5732_; uint32_t v_a_5733_; uint32_t v___x_5734_; uint32_t v___x_5735_; uint32_t v___x_5736_; uint8_t v___x_5737_; 
v___x_5732_ = 2147483647;
v_a_5733_ = lean_uint32_land(v_y_5708_, v___x_5732_);
v___x_5734_ = 201326591;
v___x_5735_ = 1;
v___x_5736_ = lean_uint32_sub(v_a_5733_, v___x_5735_);
v___x_5737_ = lean_uint32_dec_le(v___x_5734_, v___x_5736_);
if (v___x_5737_ == 0)
{
v___y_5715_ = v___y_5731_;
v___y_5716_ = v___x_5737_;
goto v___jp_5714_;
}
else
{
uint32_t v___x_5738_; uint8_t v___x_5739_; 
v___x_5738_ = 2139095040;
v___x_5739_ = lean_uint32_dec_lt(v_a_5733_, v___x_5738_);
v___y_5715_ = v___y_5731_;
v___y_5716_ = v___x_5739_;
goto v___jp_5714_;
}
}
v___jp_5740_:
{
if (v___y_5741_ == 0)
{
float v___x_5742_; 
v___x_5742_ = lean_float32_of_bits(v_x_5707_);
v___y_5731_ = v___x_5742_;
goto v___jp_5730_;
}
else
{
uint32_t v___x_5743_; uint32_t v___x_5744_; uint32_t v___x_5745_; uint32_t v___x_5746_; float v___x_5747_; lean_object* v___x_5748_; uint32_t v___x_5749_; uint32_t v___x_5750_; lean_object* v___x_5751_; lean_object* v___x_5752_; float v___x_5753_; float v___x_5754_; 
v___x_5743_ = 8388607;
v___x_5744_ = lean_uint32_land(v_x_5707_, v___x_5743_);
v___x_5745_ = 8388608;
v___x_5746_ = lean_uint32_lor(v___x_5744_, v___x_5745_);
v___x_5747_ = lean_uint32_to_float32(v___x_5746_);
v___x_5748_ = lp_competition_R2W01b_scaleTable;
v___x_5749_ = 23;
v___x_5750_ = lean_uint32_shift_right(v_x_5707_, v___x_5749_);
v___x_5751_ = lean_uint32_to_nat(v___x_5750_);
v___x_5752_ = lean_array_fget_borrowed(v___x_5748_, v___x_5751_);
lean_dec(v___x_5751_);
v___x_5753_ = lean_unbox_float32(v___x_5752_);
v___x_5754_ = lean_float32_mul(v___x_5747_, v___x_5753_);
v___y_5731_ = v___x_5754_;
goto v___jp_5730_;
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_add___boxed(lean_object* v_x_5773_, lean_object* v_y_5774_){
_start:
{
uint32_t v_x_boxed_5775_; uint32_t v_y_boxed_5776_; uint32_t v_res_5777_; lean_object* v_r_5778_; 
v_x_boxed_5775_ = lean_unbox_uint32(v_x_5773_);
lean_dec(v_x_5773_);
v_y_boxed_5776_ = lean_unbox_uint32(v_y_5774_);
lean_dec(v_y_5774_);
v_res_5777_ = lp_competition_Submission_add(v_x_boxed_5775_, v_y_boxed_5776_);
v_r_5778_ = lean_box_uint32(v_res_5777_);
return v_r_5778_;
}
}
LEAN_EXPORT uint32_t lp_competition_Submission_nativeMul(uint32_t v_x_5779_, uint32_t v_y_5780_){
_start:
{
uint32_t v___x_5781_; uint32_t v___x_5782_; uint32_t v___x_5783_; uint32_t v___x_5784_; uint8_t v___x_5785_; 
v___x_5781_ = 23;
v___x_5782_ = lean_uint32_shift_right(v_x_5779_, v___x_5781_);
v___x_5783_ = 255;
v___x_5784_ = lean_uint32_land(v___x_5782_, v___x_5783_);
v___x_5785_ = lean_uint32_dec_eq(v___x_5784_, v___x_5783_);
if (v___x_5785_ == 0)
{
uint32_t v___x_5786_; uint32_t v___x_5787_; uint8_t v___x_5788_; 
v___x_5786_ = lean_uint32_shift_right(v_y_5780_, v___x_5781_);
v___x_5787_ = lean_uint32_land(v___x_5786_, v___x_5783_);
v___x_5788_ = lean_uint32_dec_eq(v___x_5787_, v___x_5783_);
if (v___x_5788_ == 0)
{
float v___x_5789_; float v___x_5790_; float v___x_5791_; uint32_t v___x_5792_; 
v___x_5789_ = lean_float32_of_bits(v_x_5779_);
v___x_5790_ = lean_float32_of_bits(v_y_5780_);
v___x_5791_ = lean_float32_mul(v___x_5789_, v___x_5790_);
v___x_5792_ = lean_float32_to_bits(v___x_5791_);
return v___x_5792_;
}
else
{
uint32_t v___x_5793_; 
v___x_5793_ = lp_competition_Submission_FastMul_mul(v_x_5779_, v_y_5780_);
return v___x_5793_;
}
}
else
{
uint32_t v___x_5794_; 
v___x_5794_ = lp_competition_Submission_FastMul_mul(v_x_5779_, v_y_5780_);
return v___x_5794_;
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_nativeMul___boxed(lean_object* v_x_5795_, lean_object* v_y_5796_){
_start:
{
uint32_t v_x_boxed_5797_; uint32_t v_y_boxed_5798_; uint32_t v_res_5799_; lean_object* v_r_5800_; 
v_x_boxed_5797_ = lean_unbox_uint32(v_x_5795_);
lean_dec(v_x_5795_);
v_y_boxed_5798_ = lean_unbox_uint32(v_y_5796_);
lean_dec(v_y_5796_);
v_res_5799_ = lp_competition_Submission_nativeMul(v_x_boxed_5797_, v_y_boxed_5798_);
v_r_5800_ = lean_box_uint32(v_res_5799_);
return v_r_5800_;
}
}
LEAN_EXPORT uint32_t lp_competition_Submission_mul(uint32_t v_x_5801_, uint32_t v_y_5802_){
_start:
{
uint32_t v___y_5804_; uint32_t v___y_5808_; uint32_t v___y_5812_; uint32_t v___y_5813_; uint32_t v___y_5814_; uint32_t v___y_5818_; uint64_t v___y_5819_; uint8_t v___y_5820_; uint64_t v___y_5821_; uint32_t v___y_5833_; uint32_t v___y_5834_; uint32_t v___y_5835_; uint32_t v___y_5839_; uint64_t v___y_5840_; uint8_t v___y_5841_; uint64_t v___y_5842_; uint32_t v___y_5854_; uint32_t v___y_5858_; uint32_t v___y_5859_; uint32_t v___y_5860_; uint64_t v___y_5864_; uint8_t v___y_5865_; uint32_t v___y_5866_; uint64_t v___y_5867_; uint32_t v___x_5878_; uint32_t v___x_5879_; uint32_t v___x_5880_; uint32_t v___y_5882_; uint32_t v___y_5883_; uint32_t v___y_5884_; uint32_t v___y_5885_; uint32_t v___y_5892_; uint8_t v___y_5893_; uint32_t v___y_5894_; uint32_t v___y_5895_; uint64_t v___y_5899_; uint64_t v___y_5900_; uint8_t v___y_5901_; uint32_t v___y_5902_; uint64_t v___y_5903_; uint64_t v___y_5913_; uint64_t v___y_5914_; uint8_t v___y_5915_; uint32_t v___y_5916_; uint8_t v___y_5917_; uint64_t v___y_5918_; uint64_t v___y_5925_; uint64_t v___y_5926_; uint8_t v___y_5927_; uint32_t v___y_5928_; uint64_t v___y_5929_; uint64_t v___y_5935_; uint64_t v___y_5936_; uint64_t v___y_5937_; uint8_t v___y_5938_; uint32_t v___y_5939_; uint64_t v___y_5940_; uint64_t v___y_5995_; uint64_t v___y_5996_; uint64_t v___y_5997_; uint64_t v___y_5998_; uint8_t v___y_5999_; uint32_t v___y_6000_; uint64_t v___y_6001_; uint64_t v___y_6007_; uint64_t v___y_6008_; uint64_t v___y_6009_; uint64_t v___y_6010_; uint64_t v___y_6011_; uint8_t v___y_6012_; uint32_t v___y_6013_; uint64_t v___y_6014_; uint64_t v___y_6015_; uint64_t v___y_6020_; uint64_t v___y_6021_; uint64_t v___y_6022_; uint64_t v___y_6023_; uint8_t v___y_6024_; uint32_t v___y_6025_; uint64_t v___y_6026_; uint64_t v___y_6031_; uint64_t v___y_6032_; uint64_t v___y_6033_; uint8_t v___y_6034_; uint64_t v___y_6035_; uint64_t v___y_6036_; uint64_t v___y_6037_; uint32_t v___y_6038_; uint64_t v___y_6039_; uint64_t v___y_6044_; uint64_t v___y_6045_; uint64_t v___y_6046_; uint8_t v___y_6047_; uint32_t v___y_6048_; uint64_t v___y_6049_; uint64_t v___y_6050_; uint64_t v___y_6055_; uint64_t v___y_6056_; uint64_t v___y_6057_; uint64_t v___y_6058_; uint64_t v___y_6059_; uint64_t v___y_6060_; uint8_t v___y_6061_; uint32_t v___y_6062_; uint64_t v___y_6063_; uint64_t v___y_6068_; uint64_t v___y_6069_; uint64_t v___y_6070_; uint64_t v___y_6071_; uint8_t v___y_6072_; uint32_t v___y_6073_; uint64_t v___y_6074_; uint64_t v___y_6079_; uint64_t v___y_6080_; uint64_t v___y_6081_; uint64_t v___y_6082_; uint64_t v___y_6083_; uint8_t v___y_6084_; uint32_t v___y_6085_; uint64_t v___y_6086_; uint64_t v___y_6087_; uint64_t v___y_6092_; uint64_t v___y_6093_; uint64_t v___y_6094_; uint64_t v___y_6095_; uint8_t v___y_6096_; uint32_t v___y_6097_; uint64_t v___y_6098_; uint64_t v___y_6103_; uint64_t v___y_6104_; uint64_t v___y_6105_; uint64_t v___y_6106_; uint8_t v___y_6107_; uint32_t v___y_6108_; uint64_t v___y_6109_; uint64_t v___y_6113_; uint64_t v___y_6114_; uint64_t v___y_6115_; uint8_t v___y_6116_; uint32_t v___y_6117_; uint64_t v___y_6122_; uint8_t v___y_6123_; uint64_t v___y_6124_; uint32_t v___y_6125_; uint64_t v___y_6126_; uint64_t v___y_6127_; uint32_t v___y_6143_; uint32_t v___y_6144_; uint32_t v___y_6145_; uint32_t v___y_6146_; uint32_t v___y_6153_; uint32_t v___y_6154_; uint8_t v___y_6155_; uint32_t v___y_6156_; uint32_t v___y_6160_; uint64_t v___y_6161_; uint8_t v___y_6162_; uint64_t v___y_6163_; uint64_t v___y_6164_; uint32_t v___y_6174_; uint64_t v___y_6175_; uint64_t v___y_6176_; uint8_t v___y_6177_; uint8_t v___y_6178_; uint64_t v___y_6179_; uint32_t v___y_6186_; uint64_t v___y_6187_; uint64_t v___y_6188_; uint8_t v___y_6189_; uint64_t v___y_6190_; uint32_t v___y_6196_; uint64_t v___y_6197_; uint64_t v___y_6198_; uint64_t v___y_6199_; uint8_t v___y_6200_; uint64_t v___y_6201_; uint32_t v___y_6256_; uint64_t v___y_6257_; uint64_t v___y_6258_; uint64_t v___y_6259_; uint64_t v___y_6260_; uint8_t v___y_6261_; uint64_t v___y_6262_; uint32_t v___y_6268_; uint64_t v___y_6269_; uint64_t v___y_6270_; uint64_t v___y_6271_; uint64_t v___y_6272_; uint64_t v___y_6273_; uint64_t v___y_6274_; uint8_t v___y_6275_; uint64_t v___y_6276_; uint32_t v___y_6281_; uint64_t v___y_6282_; uint64_t v___y_6283_; uint64_t v___y_6284_; uint64_t v___y_6285_; uint8_t v___y_6286_; uint64_t v___y_6287_; uint32_t v___y_6292_; uint64_t v___y_6293_; uint64_t v___y_6294_; uint64_t v___y_6295_; uint64_t v___y_6296_; uint64_t v___y_6297_; uint64_t v___y_6298_; uint8_t v___y_6299_; uint64_t v___y_6300_; uint32_t v___y_6305_; uint64_t v___y_6306_; uint64_t v___y_6307_; uint64_t v___y_6308_; uint64_t v___y_6309_; uint8_t v___y_6310_; uint64_t v___y_6311_; uint64_t v___y_6316_; uint32_t v___y_6317_; uint64_t v___y_6318_; uint64_t v___y_6319_; uint64_t v___y_6320_; uint64_t v___y_6321_; uint64_t v___y_6322_; uint8_t v___y_6323_; uint64_t v___y_6324_; uint32_t v___y_6329_; uint64_t v___y_6330_; uint64_t v___y_6331_; uint64_t v___y_6332_; uint64_t v___y_6333_; uint8_t v___y_6334_; uint64_t v___y_6335_; uint32_t v___y_6340_; uint64_t v___y_6341_; uint64_t v___y_6342_; uint64_t v___y_6343_; uint64_t v___y_6344_; uint64_t v___y_6345_; uint64_t v___y_6346_; uint8_t v___y_6347_; uint64_t v___y_6348_; uint32_t v___y_6353_; uint64_t v___y_6354_; uint64_t v___y_6355_; uint64_t v___y_6356_; uint64_t v___y_6357_; uint8_t v___y_6358_; uint64_t v___y_6359_; uint32_t v___y_6364_; uint64_t v___y_6365_; uint64_t v___y_6366_; uint64_t v___y_6367_; uint64_t v___y_6368_; uint8_t v___y_6369_; uint64_t v___y_6370_; uint32_t v___y_6374_; uint64_t v___y_6375_; uint64_t v___y_6376_; uint8_t v___y_6377_; uint32_t v___y_6386_; uint64_t v___y_6387_; uint64_t v___y_6388_; uint64_t v___y_6389_; uint8_t v___y_6390_; uint64_t v___y_6391_; uint32_t v_ex_6424_; uint32_t v___x_6425_; uint32_t v_ey_6426_; uint8_t v___y_6428_; uint64_t v___y_6429_; uint64_t v___y_6430_; uint32_t v___y_6431_; uint64_t v___y_6432_; uint8_t v___y_6439_; uint32_t v___y_6440_; uint64_t v___y_6441_; uint64_t v___y_6442_; uint32_t v___y_6449_; uint8_t v___y_6450_; uint32_t v___y_6451_; uint64_t v___y_6452_; uint8_t v___y_6460_; uint8_t v___y_6473_; uint8_t v___y_6474_; uint8_t v___y_6475_; uint8_t v___y_6477_; uint8_t v___y_6478_; uint8_t v___y_6485_; uint32_t v___y_6497_; uint64_t v___y_6498_; uint64_t v___y_6499_; uint8_t v___y_6500_; uint64_t v___y_6501_; uint32_t v___y_6508_; uint64_t v___y_6509_; uint8_t v___y_6510_; uint64_t v___y_6511_; uint32_t v___y_6518_; uint32_t v___y_6519_; uint8_t v___y_6520_; uint64_t v___y_6521_; uint8_t v___y_6529_; uint32_t v___x_6539_; uint32_t v___x_6540_; uint8_t v___x_6541_; uint8_t v___y_6543_; uint8_t v___y_6544_; uint8_t v___y_6546_; uint8_t v___y_6547_; uint8_t v___y_6548_; uint8_t v___y_6550_; uint8_t v___y_6551_; uint8_t v___y_6557_; 
v___x_5878_ = 23;
v___x_5879_ = lean_uint32_shift_right(v_x_5801_, v___x_5878_);
v___x_5880_ = 255;
v_ex_6424_ = lean_uint32_land(v___x_5879_, v___x_5880_);
v___x_6425_ = lean_uint32_shift_right(v_y_5802_, v___x_5878_);
v_ey_6426_ = lean_uint32_land(v___x_6425_, v___x_5880_);
v___x_6539_ = lean_uint32_add(v_ex_6424_, v_ey_6426_);
v___x_6540_ = 128;
v___x_6541_ = lean_uint32_dec_lt(v___x_6539_, v___x_6540_);
if (v___x_6541_ == 0)
{
uint32_t v___x_6567_; uint32_t v___x_6568_; uint32_t v___x_6569_; uint8_t v___x_6570_; 
v___x_6567_ = 4278190080;
v___x_6568_ = 1;
v___x_6569_ = lean_uint32_shift_left(v_x_5801_, v___x_6568_);
v___x_6570_ = lean_uint32_dec_le(v___x_6567_, v___x_6569_);
if (v___x_6570_ == 0)
{
uint32_t v___x_6571_; uint8_t v___x_6572_; 
v___x_6571_ = lean_uint32_shift_left(v_y_5802_, v___x_6568_);
v___x_6572_ = lean_uint32_dec_le(v___x_6567_, v___x_6571_);
v___y_6485_ = v___x_6572_;
goto v___jp_6484_;
}
else
{
v___y_6485_ = v___x_6570_;
goto v___jp_6484_;
}
}
else
{
uint32_t v___x_6573_; uint32_t v___x_6574_; uint32_t v___x_6575_; uint8_t v___x_6576_; 
v___x_6573_ = 4278190080;
v___x_6574_ = 1;
v___x_6575_ = lean_uint32_shift_left(v_x_5801_, v___x_6574_);
v___x_6576_ = lean_uint32_dec_le(v___x_6573_, v___x_6575_);
if (v___x_6576_ == 0)
{
uint32_t v___x_6577_; uint8_t v___x_6578_; 
v___x_6577_ = lean_uint32_shift_left(v_y_5802_, v___x_6574_);
v___x_6578_ = lean_uint32_dec_le(v___x_6573_, v___x_6577_);
v___y_6557_ = v___x_6578_;
goto v___jp_6556_;
}
else
{
v___y_6557_ = v___x_6576_;
goto v___jp_6556_;
}
}
v___jp_5803_:
{
uint32_t v___x_5805_; uint32_t v___x_5806_; 
v___x_5805_ = 8388608;
v___x_5806_ = lean_uint32_lor(v___y_5804_, v___x_5805_);
return v___x_5806_;
}
v___jp_5807_:
{
uint32_t v___x_5809_; uint32_t v___x_5810_; 
v___x_5809_ = 8388608;
v___x_5810_ = lean_uint32_lor(v___y_5808_, v___x_5809_);
return v___x_5810_;
}
v___jp_5811_:
{
uint32_t v___x_5815_; uint32_t v___x_5816_; 
v___x_5815_ = lean_uint32_land(v___y_5813_, v___y_5812_);
v___x_5816_ = lean_uint32_lor(v___y_5814_, v___x_5815_);
return v___x_5816_;
}
v___jp_5817_:
{
uint8_t v___x_5822_; 
v___x_5822_ = lean_uint64_dec_eq(v___y_5821_, v___y_5819_);
if (v___x_5822_ == 0)
{
uint64_t v___x_5823_; uint8_t v___x_5824_; 
v___x_5823_ = 8388608ULL;
v___x_5824_ = lean_uint64_dec_eq(v___y_5821_, v___x_5823_);
if (v___x_5824_ == 0)
{
uint32_t v___x_5825_; 
v___x_5825_ = lean_uint64_to_uint32(v___y_5821_);
if (v___y_5820_ == 0)
{
uint32_t v___x_5826_; 
v___x_5826_ = 0;
v___y_5812_ = v___y_5818_;
v___y_5813_ = v___x_5825_;
v___y_5814_ = v___x_5826_;
goto v___jp_5811_;
}
else
{
uint32_t v___x_5827_; 
v___x_5827_ = 2147483648;
v___y_5812_ = v___y_5818_;
v___y_5813_ = v___x_5825_;
v___y_5814_ = v___x_5827_;
goto v___jp_5811_;
}
}
else
{
if (v___y_5820_ == 0)
{
uint32_t v___x_5828_; 
v___x_5828_ = 0;
v___y_5808_ = v___x_5828_;
goto v___jp_5807_;
}
else
{
uint32_t v___x_5829_; 
v___x_5829_ = 2147483648;
v___y_5808_ = v___x_5829_;
goto v___jp_5807_;
}
}
}
else
{
if (v___y_5820_ == 0)
{
uint32_t v___x_5830_; 
v___x_5830_ = 0;
return v___x_5830_;
}
else
{
uint32_t v___x_5831_; 
v___x_5831_ = 2147483648;
return v___x_5831_;
}
}
}
v___jp_5832_:
{
uint32_t v___x_5836_; uint32_t v___x_5837_; 
v___x_5836_ = lean_uint32_land(v___y_5834_, v___y_5833_);
v___x_5837_ = lean_uint32_lor(v___y_5835_, v___x_5836_);
return v___x_5837_;
}
v___jp_5838_:
{
uint8_t v___x_5843_; 
v___x_5843_ = lean_uint64_dec_eq(v___y_5842_, v___y_5840_);
if (v___x_5843_ == 0)
{
uint64_t v___x_5844_; uint8_t v___x_5845_; 
v___x_5844_ = 8388608ULL;
v___x_5845_ = lean_uint64_dec_eq(v___y_5842_, v___x_5844_);
if (v___x_5845_ == 0)
{
uint32_t v___x_5846_; 
v___x_5846_ = lean_uint64_to_uint32(v___y_5842_);
if (v___y_5841_ == 0)
{
uint32_t v___x_5847_; 
v___x_5847_ = 0;
v___y_5833_ = v___y_5839_;
v___y_5834_ = v___x_5846_;
v___y_5835_ = v___x_5847_;
goto v___jp_5832_;
}
else
{
uint32_t v___x_5848_; 
v___x_5848_ = 2147483648;
v___y_5833_ = v___y_5839_;
v___y_5834_ = v___x_5846_;
v___y_5835_ = v___x_5848_;
goto v___jp_5832_;
}
}
else
{
if (v___y_5841_ == 0)
{
uint32_t v___x_5849_; 
v___x_5849_ = 0;
v___y_5804_ = v___x_5849_;
goto v___jp_5803_;
}
else
{
uint32_t v___x_5850_; 
v___x_5850_ = 2147483648;
v___y_5804_ = v___x_5850_;
goto v___jp_5803_;
}
}
}
else
{
if (v___y_5841_ == 0)
{
uint32_t v___x_5851_; 
v___x_5851_ = 0;
return v___x_5851_;
}
else
{
uint32_t v___x_5852_; 
v___x_5852_ = 2147483648;
return v___x_5852_;
}
}
}
v___jp_5853_:
{
uint32_t v___x_5855_; uint32_t v___x_5856_; 
v___x_5855_ = 8388608;
v___x_5856_ = lean_uint32_lor(v___y_5854_, v___x_5855_);
return v___x_5856_;
}
v___jp_5857_:
{
uint32_t v___x_5861_; uint32_t v___x_5862_; 
v___x_5861_ = lean_uint32_land(v___y_5859_, v___y_5858_);
v___x_5862_ = lean_uint32_lor(v___y_5860_, v___x_5861_);
return v___x_5862_;
}
v___jp_5863_:
{
uint8_t v___x_5868_; 
v___x_5868_ = lean_uint64_dec_eq(v___y_5867_, v___y_5864_);
if (v___x_5868_ == 0)
{
uint64_t v___x_5869_; uint8_t v___x_5870_; 
v___x_5869_ = 8388608ULL;
v___x_5870_ = lean_uint64_dec_eq(v___y_5867_, v___x_5869_);
if (v___x_5870_ == 0)
{
uint32_t v___x_5871_; 
v___x_5871_ = lean_uint64_to_uint32(v___y_5867_);
if (v___y_5865_ == 0)
{
uint32_t v___x_5872_; 
v___x_5872_ = 0;
v___y_5858_ = v___y_5866_;
v___y_5859_ = v___x_5871_;
v___y_5860_ = v___x_5872_;
goto v___jp_5857_;
}
else
{
uint32_t v___x_5873_; 
v___x_5873_ = 2147483648;
v___y_5858_ = v___y_5866_;
v___y_5859_ = v___x_5871_;
v___y_5860_ = v___x_5873_;
goto v___jp_5857_;
}
}
else
{
if (v___y_5865_ == 0)
{
uint32_t v___x_5874_; 
v___x_5874_ = 0;
v___y_5854_ = v___x_5874_;
goto v___jp_5853_;
}
else
{
uint32_t v___x_5875_; 
v___x_5875_ = 2147483648;
v___y_5854_ = v___x_5875_;
goto v___jp_5853_;
}
}
}
else
{
if (v___y_5865_ == 0)
{
uint32_t v___x_5876_; 
v___x_5876_ = 0;
return v___x_5876_;
}
else
{
uint32_t v___x_5877_; 
v___x_5877_ = 2147483648;
return v___x_5877_;
}
}
}
v___jp_5881_:
{
uint32_t v___x_5886_; uint32_t v___x_5887_; uint32_t v___x_5888_; uint32_t v___x_5889_; uint32_t v___x_5890_; 
v___x_5886_ = lean_uint32_land(v___y_5882_, v___x_5880_);
v___x_5887_ = lean_uint32_shift_left(v___x_5886_, v___x_5878_);
v___x_5888_ = lean_uint32_lor(v___y_5885_, v___x_5887_);
v___x_5889_ = lean_uint32_land(v___y_5883_, v___y_5884_);
v___x_5890_ = lean_uint32_lor(v___x_5888_, v___x_5889_);
return v___x_5890_;
}
v___jp_5891_:
{
if (v___y_5893_ == 0)
{
uint32_t v___x_5896_; 
v___x_5896_ = 0;
v___y_5882_ = v___y_5892_;
v___y_5883_ = v___y_5895_;
v___y_5884_ = v___y_5894_;
v___y_5885_ = v___x_5896_;
goto v___jp_5881_;
}
else
{
uint32_t v___x_5897_; 
v___x_5897_ = 2147483648;
v___y_5882_ = v___y_5892_;
v___y_5883_ = v___y_5895_;
v___y_5884_ = v___y_5894_;
v___y_5885_ = v___x_5897_;
goto v___jp_5881_;
}
}
v___jp_5898_:
{
uint64_t v___x_5904_; uint64_t v_encodedExponent_5905_; uint32_t v___x_5906_; uint64_t v___x_5907_; uint8_t v___x_5908_; 
v___x_5904_ = 171ULL;
v_encodedExponent_5905_ = lean_uint64_sub(v___y_5900_, v___x_5904_);
v___x_5906_ = lean_uint64_to_uint32(v_encodedExponent_5905_);
v___x_5907_ = 8388608ULL;
v___x_5908_ = lean_uint64_dec_lt(v___y_5903_, v___x_5907_);
if (v___x_5908_ == 0)
{
uint64_t v___x_5909_; uint32_t v___x_5910_; 
v___x_5909_ = lean_uint64_sub(v___y_5903_, v___x_5907_);
v___x_5910_ = lean_uint64_to_uint32(v___x_5909_);
v___y_5892_ = v___x_5906_;
v___y_5893_ = v___y_5901_;
v___y_5894_ = v___y_5902_;
v___y_5895_ = v___x_5910_;
goto v___jp_5891_;
}
else
{
uint32_t v___x_5911_; 
v___x_5911_ = lean_uint64_to_uint32(v___y_5899_);
v___y_5892_ = v___x_5906_;
v___y_5893_ = v___y_5901_;
v___y_5894_ = v___y_5902_;
v___y_5895_ = v___x_5911_;
goto v___jp_5891_;
}
}
v___jp_5912_:
{
uint64_t v___x_5919_; uint8_t v___x_5920_; 
v___x_5919_ = 425ULL;
v___x_5920_ = lean_uint64_dec_lt(v___x_5919_, v___y_5918_);
if (v___x_5920_ == 0)
{
if (v___y_5917_ == 0)
{
v___y_5899_ = v___y_5914_;
v___y_5900_ = v___y_5918_;
v___y_5901_ = v___y_5915_;
v___y_5902_ = v___y_5916_;
v___y_5903_ = v___y_5913_;
goto v___jp_5898_;
}
else
{
uint64_t v___x_5921_; 
v___x_5921_ = 8388608ULL;
v___y_5899_ = v___y_5914_;
v___y_5900_ = v___y_5918_;
v___y_5901_ = v___y_5915_;
v___y_5902_ = v___y_5916_;
v___y_5903_ = v___x_5921_;
goto v___jp_5898_;
}
}
else
{
if (v___y_5915_ == 0)
{
uint32_t v___x_5922_; 
v___x_5922_ = 2139095040;
return v___x_5922_;
}
else
{
uint32_t v___x_5923_; 
v___x_5923_ = 4286578688;
return v___x_5923_;
}
}
}
v___jp_5924_:
{
uint64_t v___x_5930_; uint8_t v_carry_5931_; 
v___x_5930_ = 16777216ULL;
v_carry_5931_ = lean_uint64_dec_eq(v___y_5929_, v___x_5930_);
if (v_carry_5931_ == 0)
{
v___y_5913_ = v___y_5929_;
v___y_5914_ = v___y_5925_;
v___y_5915_ = v___y_5927_;
v___y_5916_ = v___y_5928_;
v___y_5917_ = v_carry_5931_;
v___y_5918_ = v___y_5926_;
goto v___jp_5912_;
}
else
{
uint64_t v___x_5932_; uint64_t v___x_5933_; 
v___x_5932_ = 1ULL;
v___x_5933_ = lean_uint64_add(v___y_5926_, v___x_5932_);
v___y_5913_ = v___y_5929_;
v___y_5914_ = v___y_5925_;
v___y_5915_ = v___y_5927_;
v___y_5916_ = v___y_5928_;
v___y_5917_ = v_carry_5931_;
v___y_5918_ = v___x_5933_;
goto v___jp_5912_;
}
}
v___jp_5934_:
{
uint64_t v_position_5941_; uint64_t v___x_5942_; uint8_t v___x_5943_; 
v_position_5941_ = lean_uint64_add(v___y_5940_, v___y_5935_);
v___x_5942_ = 172ULL;
v___x_5943_ = lean_uint64_dec_lt(v_position_5941_, v___x_5942_);
if (v___x_5943_ == 0)
{
uint64_t v___x_5944_; uint8_t v___x_5945_; 
v___x_5944_ = 23ULL;
v___x_5945_ = lean_uint64_dec_lt(v___y_5940_, v___x_5944_);
if (v___x_5945_ == 0)
{
uint64_t v___x_5946_; uint8_t v___x_5947_; 
v___x_5946_ = lean_uint64_sub(v___y_5940_, v___x_5944_);
v___x_5947_ = lean_uint64_dec_eq(v___x_5946_, v___y_5937_);
if (v___x_5947_ == 0)
{
uint64_t v___x_5948_; uint8_t v___x_5949_; 
v___x_5948_ = 64ULL;
v___x_5949_ = lean_uint64_dec_lt(v___x_5946_, v___x_5948_);
if (v___x_5949_ == 0)
{
uint8_t v___x_5950_; 
v___x_5950_ = lean_uint64_dec_eq(v___x_5946_, v___x_5948_);
if (v___x_5950_ == 0)
{
v___y_5925_ = v___y_5937_;
v___y_5926_ = v_position_5941_;
v___y_5927_ = v___y_5938_;
v___y_5928_ = v___y_5939_;
v___y_5929_ = v___y_5937_;
goto v___jp_5924_;
}
else
{
uint64_t v___x_5951_; uint8_t v___x_5952_; 
v___x_5951_ = 9223372036854775808ULL;
v___x_5952_ = lean_uint64_dec_lt(v___x_5951_, v___y_5936_);
if (v___x_5952_ == 0)
{
v___y_5925_ = v___y_5937_;
v___y_5926_ = v_position_5941_;
v___y_5927_ = v___y_5938_;
v___y_5928_ = v___y_5939_;
v___y_5929_ = v___y_5937_;
goto v___jp_5924_;
}
else
{
uint64_t v___x_5953_; 
v___x_5953_ = 1ULL;
v___y_5925_ = v___y_5937_;
v___y_5926_ = v_position_5941_;
v___y_5927_ = v___y_5938_;
v___y_5928_ = v___y_5939_;
v___y_5929_ = v___x_5953_;
goto v___jp_5924_;
}
}
}
else
{
uint64_t v_quotient_5954_; uint64_t v___x_5955_; uint64_t v___x_5956_; uint64_t v___x_5957_; uint64_t v_remainder_5958_; uint64_t v___x_5959_; uint64_t v_half_5960_; uint8_t v___x_5961_; 
v_quotient_5954_ = lean_uint64_shift_right(v___y_5936_, v___x_5946_);
v___x_5955_ = 1ULL;
v___x_5956_ = lean_uint64_shift_left(v___x_5955_, v___x_5946_);
v___x_5957_ = lean_uint64_sub(v___x_5956_, v___x_5955_);
v_remainder_5958_ = lean_uint64_land(v___y_5936_, v___x_5957_);
v___x_5959_ = lean_uint64_sub(v___x_5946_, v___x_5955_);
v_half_5960_ = lean_uint64_shift_left(v___x_5955_, v___x_5959_);
v___x_5961_ = lean_uint64_dec_lt(v_remainder_5958_, v_half_5960_);
if (v___x_5961_ == 0)
{
uint8_t v___x_5962_; 
v___x_5962_ = lean_uint64_dec_lt(v_half_5960_, v_remainder_5958_);
if (v___x_5962_ == 0)
{
uint64_t v___x_5963_; uint8_t v___x_5964_; 
v___x_5963_ = lean_uint64_land(v_quotient_5954_, v___x_5955_);
v___x_5964_ = lean_uint64_dec_eq(v___x_5963_, v___y_5937_);
if (v___x_5964_ == 0)
{
uint64_t v___x_5965_; 
v___x_5965_ = lean_uint64_add(v_quotient_5954_, v___x_5955_);
v___y_5925_ = v___y_5937_;
v___y_5926_ = v_position_5941_;
v___y_5927_ = v___y_5938_;
v___y_5928_ = v___y_5939_;
v___y_5929_ = v___x_5965_;
goto v___jp_5924_;
}
else
{
v___y_5925_ = v___y_5937_;
v___y_5926_ = v_position_5941_;
v___y_5927_ = v___y_5938_;
v___y_5928_ = v___y_5939_;
v___y_5929_ = v_quotient_5954_;
goto v___jp_5924_;
}
}
else
{
uint64_t v___x_5966_; 
v___x_5966_ = lean_uint64_add(v_quotient_5954_, v___x_5955_);
v___y_5925_ = v___y_5937_;
v___y_5926_ = v_position_5941_;
v___y_5927_ = v___y_5938_;
v___y_5928_ = v___y_5939_;
v___y_5929_ = v___x_5966_;
goto v___jp_5924_;
}
}
else
{
v___y_5925_ = v___y_5937_;
v___y_5926_ = v_position_5941_;
v___y_5927_ = v___y_5938_;
v___y_5928_ = v___y_5939_;
v___y_5929_ = v_quotient_5954_;
goto v___jp_5924_;
}
}
}
else
{
v___y_5925_ = v___y_5937_;
v___y_5926_ = v_position_5941_;
v___y_5927_ = v___y_5938_;
v___y_5928_ = v___y_5939_;
v___y_5929_ = v___y_5936_;
goto v___jp_5924_;
}
}
else
{
uint64_t v___x_5967_; uint64_t v___x_5968_; 
v___x_5967_ = lean_uint64_sub(v___x_5944_, v___y_5940_);
v___x_5968_ = lean_uint64_shift_left(v___y_5936_, v___x_5967_);
v___y_5925_ = v___y_5937_;
v___y_5926_ = v_position_5941_;
v___y_5927_ = v___y_5938_;
v___y_5928_ = v___y_5939_;
v___y_5929_ = v___x_5968_;
goto v___jp_5924_;
}
}
else
{
uint64_t v___x_5969_; uint8_t v___x_5970_; 
v___x_5969_ = 149ULL;
v___x_5970_ = lean_uint64_dec_lt(v___y_5935_, v___x_5969_);
if (v___x_5970_ == 0)
{
uint64_t v___x_5971_; uint64_t v___x_5972_; 
v___x_5971_ = lean_uint64_sub(v___y_5935_, v___x_5969_);
v___x_5972_ = lean_uint64_shift_left(v___y_5936_, v___x_5971_);
v___y_5864_ = v___y_5937_;
v___y_5865_ = v___y_5938_;
v___y_5866_ = v___y_5939_;
v___y_5867_ = v___x_5972_;
goto v___jp_5863_;
}
else
{
uint64_t v___x_5973_; uint8_t v___x_5974_; 
v___x_5973_ = lean_uint64_sub(v___x_5969_, v___y_5935_);
v___x_5974_ = lean_uint64_dec_eq(v___x_5973_, v___y_5937_);
if (v___x_5974_ == 0)
{
uint64_t v___x_5975_; uint8_t v___x_5976_; 
v___x_5975_ = 64ULL;
v___x_5976_ = lean_uint64_dec_lt(v___x_5973_, v___x_5975_);
if (v___x_5976_ == 0)
{
uint8_t v___x_5977_; 
v___x_5977_ = lean_uint64_dec_eq(v___x_5973_, v___x_5975_);
if (v___x_5977_ == 0)
{
v___y_5864_ = v___y_5937_;
v___y_5865_ = v___y_5938_;
v___y_5866_ = v___y_5939_;
v___y_5867_ = v___y_5937_;
goto v___jp_5863_;
}
else
{
uint64_t v___x_5978_; uint8_t v___x_5979_; 
v___x_5978_ = 9223372036854775808ULL;
v___x_5979_ = lean_uint64_dec_lt(v___x_5978_, v___y_5936_);
if (v___x_5979_ == 0)
{
v___y_5864_ = v___y_5937_;
v___y_5865_ = v___y_5938_;
v___y_5866_ = v___y_5939_;
v___y_5867_ = v___y_5937_;
goto v___jp_5863_;
}
else
{
uint64_t v___x_5980_; 
v___x_5980_ = 1ULL;
v___y_5864_ = v___y_5937_;
v___y_5865_ = v___y_5938_;
v___y_5866_ = v___y_5939_;
v___y_5867_ = v___x_5980_;
goto v___jp_5863_;
}
}
}
else
{
uint64_t v_quotient_5981_; uint64_t v___x_5982_; uint64_t v___x_5983_; uint64_t v___x_5984_; uint64_t v_remainder_5985_; uint64_t v___x_5986_; uint64_t v_half_5987_; uint8_t v___x_5988_; 
v_quotient_5981_ = lean_uint64_shift_right(v___y_5936_, v___x_5973_);
v___x_5982_ = 1ULL;
v___x_5983_ = lean_uint64_shift_left(v___x_5982_, v___x_5973_);
v___x_5984_ = lean_uint64_sub(v___x_5983_, v___x_5982_);
v_remainder_5985_ = lean_uint64_land(v___y_5936_, v___x_5984_);
v___x_5986_ = lean_uint64_sub(v___x_5973_, v___x_5982_);
v_half_5987_ = lean_uint64_shift_left(v___x_5982_, v___x_5986_);
v___x_5988_ = lean_uint64_dec_lt(v_remainder_5985_, v_half_5987_);
if (v___x_5988_ == 0)
{
uint8_t v___x_5989_; 
v___x_5989_ = lean_uint64_dec_lt(v_half_5987_, v_remainder_5985_);
if (v___x_5989_ == 0)
{
uint64_t v___x_5990_; uint8_t v___x_5991_; 
v___x_5990_ = lean_uint64_land(v_quotient_5981_, v___x_5982_);
v___x_5991_ = lean_uint64_dec_eq(v___x_5990_, v___y_5937_);
if (v___x_5991_ == 0)
{
uint64_t v___x_5992_; 
v___x_5992_ = lean_uint64_add(v_quotient_5981_, v___x_5982_);
v___y_5864_ = v___y_5937_;
v___y_5865_ = v___y_5938_;
v___y_5866_ = v___y_5939_;
v___y_5867_ = v___x_5992_;
goto v___jp_5863_;
}
else
{
v___y_5864_ = v___y_5937_;
v___y_5865_ = v___y_5938_;
v___y_5866_ = v___y_5939_;
v___y_5867_ = v_quotient_5981_;
goto v___jp_5863_;
}
}
else
{
uint64_t v___x_5993_; 
v___x_5993_ = lean_uint64_add(v_quotient_5981_, v___x_5982_);
v___y_5864_ = v___y_5937_;
v___y_5865_ = v___y_5938_;
v___y_5866_ = v___y_5939_;
v___y_5867_ = v___x_5993_;
goto v___jp_5863_;
}
}
else
{
v___y_5864_ = v___y_5937_;
v___y_5865_ = v___y_5938_;
v___y_5866_ = v___y_5939_;
v___y_5867_ = v_quotient_5981_;
goto v___jp_5863_;
}
}
}
else
{
v___y_5864_ = v___y_5937_;
v___y_5865_ = v___y_5938_;
v___y_5866_ = v___y_5939_;
v___y_5867_ = v___y_5936_;
goto v___jp_5863_;
}
}
}
}
v___jp_5994_:
{
uint64_t v___x_6002_; uint64_t v___x_6003_; uint8_t v___x_6004_; 
v___x_6002_ = 1ULL;
v___x_6003_ = lean_uint64_shift_right(v___y_5998_, v___x_6002_);
v___x_6004_ = lean_uint64_dec_eq(v___x_6003_, v___y_5997_);
if (v___x_6004_ == 0)
{
uint64_t v___x_6005_; 
v___x_6005_ = lean_uint64_add(v___y_6001_, v___x_6002_);
v___y_5935_ = v___y_5995_;
v___y_5936_ = v___y_5996_;
v___y_5937_ = v___y_5997_;
v___y_5938_ = v___y_5999_;
v___y_5939_ = v___y_6000_;
v___y_5940_ = v___x_6005_;
goto v___jp_5934_;
}
else
{
v___y_5935_ = v___y_5995_;
v___y_5936_ = v___y_5996_;
v___y_5937_ = v___y_5997_;
v___y_5938_ = v___y_5999_;
v___y_5939_ = v___y_6000_;
v___y_5940_ = v___y_6001_;
goto v___jp_5934_;
}
}
v___jp_6006_:
{
uint64_t v___x_6016_; uint8_t v___x_6017_; 
v___x_6016_ = lean_uint64_shift_right(v___y_6009_, v___y_6008_);
v___x_6017_ = lean_uint64_dec_eq(v___x_6016_, v___y_6011_);
if (v___x_6017_ == 0)
{
uint64_t v___x_6018_; 
v___x_6018_ = lean_uint64_add(v___y_6014_, v___y_6008_);
v___y_5995_ = v___y_6007_;
v___y_5996_ = v___y_6010_;
v___y_5997_ = v___y_6011_;
v___y_5998_ = v___y_6015_;
v___y_5999_ = v___y_6012_;
v___y_6000_ = v___y_6013_;
v___y_6001_ = v___x_6018_;
goto v___jp_5994_;
}
else
{
v___y_5995_ = v___y_6007_;
v___y_5996_ = v___y_6010_;
v___y_5997_ = v___y_6011_;
v___y_5998_ = v___y_6015_;
v___y_5999_ = v___y_6012_;
v___y_6000_ = v___y_6013_;
v___y_6001_ = v___y_6014_;
goto v___jp_5994_;
}
}
v___jp_6019_:
{
uint64_t v___x_6027_; uint64_t v___x_6028_; uint8_t v___x_6029_; 
v___x_6027_ = 2ULL;
v___x_6028_ = lean_uint64_shift_right(v___y_6022_, v___x_6027_);
v___x_6029_ = lean_uint64_dec_eq(v___x_6028_, v___y_6023_);
if (v___x_6029_ == 0)
{
v___y_6007_ = v___y_6020_;
v___y_6008_ = v___x_6027_;
v___y_6009_ = v___y_6022_;
v___y_6010_ = v___y_6021_;
v___y_6011_ = v___y_6023_;
v___y_6012_ = v___y_6024_;
v___y_6013_ = v___y_6025_;
v___y_6014_ = v___y_6026_;
v___y_6015_ = v___x_6028_;
goto v___jp_6006_;
}
else
{
v___y_6007_ = v___y_6020_;
v___y_6008_ = v___x_6027_;
v___y_6009_ = v___y_6022_;
v___y_6010_ = v___y_6021_;
v___y_6011_ = v___y_6023_;
v___y_6012_ = v___y_6024_;
v___y_6013_ = v___y_6025_;
v___y_6014_ = v___y_6026_;
v___y_6015_ = v___y_6022_;
goto v___jp_6006_;
}
}
v___jp_6030_:
{
uint64_t v___x_6040_; uint8_t v___x_6041_; 
v___x_6040_ = lean_uint64_shift_right(v___y_6037_, v___y_6036_);
v___x_6041_ = lean_uint64_dec_eq(v___x_6040_, v___y_6033_);
if (v___x_6041_ == 0)
{
uint64_t v___x_6042_; 
v___x_6042_ = lean_uint64_add(v___y_6035_, v___y_6036_);
v___y_6020_ = v___y_6031_;
v___y_6021_ = v___y_6032_;
v___y_6022_ = v___y_6039_;
v___y_6023_ = v___y_6033_;
v___y_6024_ = v___y_6034_;
v___y_6025_ = v___y_6038_;
v___y_6026_ = v___x_6042_;
goto v___jp_6019_;
}
else
{
v___y_6020_ = v___y_6031_;
v___y_6021_ = v___y_6032_;
v___y_6022_ = v___y_6039_;
v___y_6023_ = v___y_6033_;
v___y_6024_ = v___y_6034_;
v___y_6025_ = v___y_6038_;
v___y_6026_ = v___y_6035_;
goto v___jp_6019_;
}
}
v___jp_6043_:
{
uint64_t v___x_6051_; uint64_t v___x_6052_; uint8_t v___x_6053_; 
v___x_6051_ = 4ULL;
v___x_6052_ = lean_uint64_shift_right(v___y_6049_, v___x_6051_);
v___x_6053_ = lean_uint64_dec_eq(v___x_6052_, v___y_6046_);
if (v___x_6053_ == 0)
{
v___y_6031_ = v___y_6044_;
v___y_6032_ = v___y_6045_;
v___y_6033_ = v___y_6046_;
v___y_6034_ = v___y_6047_;
v___y_6035_ = v___y_6050_;
v___y_6036_ = v___x_6051_;
v___y_6037_ = v___y_6049_;
v___y_6038_ = v___y_6048_;
v___y_6039_ = v___x_6052_;
goto v___jp_6030_;
}
else
{
v___y_6031_ = v___y_6044_;
v___y_6032_ = v___y_6045_;
v___y_6033_ = v___y_6046_;
v___y_6034_ = v___y_6047_;
v___y_6035_ = v___y_6050_;
v___y_6036_ = v___x_6051_;
v___y_6037_ = v___y_6049_;
v___y_6038_ = v___y_6048_;
v___y_6039_ = v___y_6049_;
goto v___jp_6030_;
}
}
v___jp_6054_:
{
uint64_t v___x_6064_; uint8_t v___x_6065_; 
v___x_6064_ = lean_uint64_shift_right(v___y_6057_, v___y_6058_);
v___x_6065_ = lean_uint64_dec_eq(v___x_6064_, v___y_6060_);
if (v___x_6065_ == 0)
{
uint64_t v___x_6066_; 
v___x_6066_ = lean_uint64_add(v___y_6055_, v___y_6058_);
v___y_6044_ = v___y_6056_;
v___y_6045_ = v___y_6059_;
v___y_6046_ = v___y_6060_;
v___y_6047_ = v___y_6061_;
v___y_6048_ = v___y_6062_;
v___y_6049_ = v___y_6063_;
v___y_6050_ = v___x_6066_;
goto v___jp_6043_;
}
else
{
v___y_6044_ = v___y_6056_;
v___y_6045_ = v___y_6059_;
v___y_6046_ = v___y_6060_;
v___y_6047_ = v___y_6061_;
v___y_6048_ = v___y_6062_;
v___y_6049_ = v___y_6063_;
v___y_6050_ = v___y_6055_;
goto v___jp_6043_;
}
}
v___jp_6067_:
{
uint64_t v___x_6075_; uint64_t v___x_6076_; uint8_t v___x_6077_; 
v___x_6075_ = 8ULL;
v___x_6076_ = lean_uint64_shift_right(v___y_6069_, v___x_6075_);
v___x_6077_ = lean_uint64_dec_eq(v___x_6076_, v___y_6071_);
if (v___x_6077_ == 0)
{
v___y_6055_ = v___y_6074_;
v___y_6056_ = v___y_6068_;
v___y_6057_ = v___y_6069_;
v___y_6058_ = v___x_6075_;
v___y_6059_ = v___y_6070_;
v___y_6060_ = v___y_6071_;
v___y_6061_ = v___y_6072_;
v___y_6062_ = v___y_6073_;
v___y_6063_ = v___x_6076_;
goto v___jp_6054_;
}
else
{
v___y_6055_ = v___y_6074_;
v___y_6056_ = v___y_6068_;
v___y_6057_ = v___y_6069_;
v___y_6058_ = v___x_6075_;
v___y_6059_ = v___y_6070_;
v___y_6060_ = v___y_6071_;
v___y_6061_ = v___y_6072_;
v___y_6062_ = v___y_6073_;
v___y_6063_ = v___y_6069_;
goto v___jp_6054_;
}
}
v___jp_6078_:
{
uint64_t v___x_6088_; uint8_t v___x_6089_; 
v___x_6088_ = lean_uint64_shift_right(v___y_6082_, v___y_6081_);
v___x_6089_ = lean_uint64_dec_eq(v___x_6088_, v___y_6083_);
if (v___x_6089_ == 0)
{
uint64_t v___x_6090_; 
v___x_6090_ = lean_uint64_add(v___y_6086_, v___y_6081_);
v___y_6068_ = v___y_6079_;
v___y_6069_ = v___y_6087_;
v___y_6070_ = v___y_6080_;
v___y_6071_ = v___y_6083_;
v___y_6072_ = v___y_6084_;
v___y_6073_ = v___y_6085_;
v___y_6074_ = v___x_6090_;
goto v___jp_6067_;
}
else
{
v___y_6068_ = v___y_6079_;
v___y_6069_ = v___y_6087_;
v___y_6070_ = v___y_6080_;
v___y_6071_ = v___y_6083_;
v___y_6072_ = v___y_6084_;
v___y_6073_ = v___y_6085_;
v___y_6074_ = v___y_6086_;
goto v___jp_6067_;
}
}
v___jp_6091_:
{
uint64_t v___x_6099_; uint64_t v___x_6100_; uint8_t v___x_6101_; 
v___x_6099_ = 16ULL;
v___x_6100_ = lean_uint64_shift_right(v___y_6094_, v___x_6099_);
v___x_6101_ = lean_uint64_dec_eq(v___x_6100_, v___y_6095_);
if (v___x_6101_ == 0)
{
v___y_6079_ = v___y_6092_;
v___y_6080_ = v___y_6093_;
v___y_6081_ = v___x_6099_;
v___y_6082_ = v___y_6094_;
v___y_6083_ = v___y_6095_;
v___y_6084_ = v___y_6096_;
v___y_6085_ = v___y_6097_;
v___y_6086_ = v___y_6098_;
v___y_6087_ = v___x_6100_;
goto v___jp_6078_;
}
else
{
v___y_6079_ = v___y_6092_;
v___y_6080_ = v___y_6093_;
v___y_6081_ = v___x_6099_;
v___y_6082_ = v___y_6094_;
v___y_6083_ = v___y_6095_;
v___y_6084_ = v___y_6096_;
v___y_6085_ = v___y_6097_;
v___y_6086_ = v___y_6098_;
v___y_6087_ = v___y_6094_;
goto v___jp_6078_;
}
}
v___jp_6102_:
{
uint64_t v___x_6110_; uint8_t v___x_6111_; 
v___x_6110_ = lean_uint64_shift_right(v___y_6104_, v___y_6106_);
v___x_6111_ = lean_uint64_dec_eq(v___x_6110_, v___y_6105_);
if (v___x_6111_ == 0)
{
v___y_6092_ = v___y_6103_;
v___y_6093_ = v___y_6104_;
v___y_6094_ = v___y_6109_;
v___y_6095_ = v___y_6105_;
v___y_6096_ = v___y_6107_;
v___y_6097_ = v___y_6108_;
v___y_6098_ = v___y_6106_;
goto v___jp_6091_;
}
else
{
v___y_6092_ = v___y_6103_;
v___y_6093_ = v___y_6104_;
v___y_6094_ = v___y_6109_;
v___y_6095_ = v___y_6105_;
v___y_6096_ = v___y_6107_;
v___y_6097_ = v___y_6108_;
v___y_6098_ = v___y_6105_;
goto v___jp_6091_;
}
}
v___jp_6112_:
{
uint64_t v___x_6118_; uint64_t v___x_6119_; uint8_t v___x_6120_; 
v___x_6118_ = 32ULL;
v___x_6119_ = lean_uint64_shift_right(v___y_6114_, v___x_6118_);
v___x_6120_ = lean_uint64_dec_eq(v___x_6119_, v___y_6115_);
if (v___x_6120_ == 0)
{
v___y_6103_ = v___y_6113_;
v___y_6104_ = v___y_6114_;
v___y_6105_ = v___y_6115_;
v___y_6106_ = v___x_6118_;
v___y_6107_ = v___y_6116_;
v___y_6108_ = v___y_6117_;
v___y_6109_ = v___x_6119_;
goto v___jp_6102_;
}
else
{
v___y_6103_ = v___y_6113_;
v___y_6104_ = v___y_6114_;
v___y_6105_ = v___y_6115_;
v___y_6106_ = v___x_6118_;
v___y_6107_ = v___y_6116_;
v___y_6108_ = v___y_6117_;
v___y_6109_ = v___y_6114_;
goto v___jp_6102_;
}
}
v___jp_6121_:
{
uint64_t v___x_6128_; uint64_t v___x_6129_; uint8_t v___x_6130_; 
v___x_6128_ = lean_uint64_mul(v___y_6126_, v___y_6124_);
v___x_6129_ = 0ULL;
v___x_6130_ = lean_uint64_dec_eq(v___x_6128_, v___x_6129_);
if (v___x_6130_ == 0)
{
uint64_t v___x_6131_; uint64_t v___x_6132_; uint8_t v___x_6133_; 
v___x_6131_ = lean_uint64_add(v___y_6122_, v___y_6127_);
v___x_6132_ = 70368744177664ULL;
v___x_6133_ = lean_uint64_dec_le(v___x_6132_, v___x_6128_);
if (v___x_6133_ == 0)
{
v___y_6113_ = v___x_6131_;
v___y_6114_ = v___x_6128_;
v___y_6115_ = v___x_6129_;
v___y_6116_ = v___y_6123_;
v___y_6117_ = v___y_6125_;
goto v___jp_6112_;
}
else
{
uint64_t v___x_6134_; uint8_t v___x_6135_; 
v___x_6134_ = 281474976710656ULL;
v___x_6135_ = lean_uint64_dec_lt(v___x_6128_, v___x_6134_);
if (v___x_6135_ == 0)
{
v___y_6113_ = v___x_6131_;
v___y_6114_ = v___x_6128_;
v___y_6115_ = v___x_6129_;
v___y_6116_ = v___y_6123_;
v___y_6117_ = v___y_6125_;
goto v___jp_6112_;
}
else
{
uint64_t v___x_6136_; uint8_t v___x_6137_; 
v___x_6136_ = 140737488355328ULL;
v___x_6137_ = lean_uint64_dec_lt(v___x_6128_, v___x_6136_);
if (v___x_6137_ == 0)
{
uint64_t v___x_6138_; 
v___x_6138_ = 47ULL;
v___y_5935_ = v___x_6131_;
v___y_5936_ = v___x_6128_;
v___y_5937_ = v___x_6129_;
v___y_5938_ = v___y_6123_;
v___y_5939_ = v___y_6125_;
v___y_5940_ = v___x_6138_;
goto v___jp_5934_;
}
else
{
uint64_t v___x_6139_; 
v___x_6139_ = 46ULL;
v___y_5935_ = v___x_6131_;
v___y_5936_ = v___x_6128_;
v___y_5937_ = v___x_6129_;
v___y_5938_ = v___y_6123_;
v___y_5939_ = v___y_6125_;
v___y_5940_ = v___x_6139_;
goto v___jp_5934_;
}
}
}
}
else
{
if (v___y_6123_ == 0)
{
uint32_t v___x_6140_; 
v___x_6140_ = 0;
return v___x_6140_;
}
else
{
uint32_t v___x_6141_; 
v___x_6141_ = 2147483648;
return v___x_6141_;
}
}
}
v___jp_6142_:
{
uint32_t v___x_6147_; uint32_t v___x_6148_; uint32_t v___x_6149_; uint32_t v___x_6150_; uint32_t v___x_6151_; 
v___x_6147_ = lean_uint32_land(v___y_6145_, v___x_5880_);
v___x_6148_ = lean_uint32_shift_left(v___x_6147_, v___x_5878_);
v___x_6149_ = lean_uint32_lor(v___y_6146_, v___x_6148_);
v___x_6150_ = lean_uint32_land(v___y_6144_, v___y_6143_);
v___x_6151_ = lean_uint32_lor(v___x_6149_, v___x_6150_);
return v___x_6151_;
}
v___jp_6152_:
{
if (v___y_6155_ == 0)
{
uint32_t v___x_6157_; 
v___x_6157_ = 0;
v___y_6143_ = v___y_6153_;
v___y_6144_ = v___y_6156_;
v___y_6145_ = v___y_6154_;
v___y_6146_ = v___x_6157_;
goto v___jp_6142_;
}
else
{
uint32_t v___x_6158_; 
v___x_6158_ = 2147483648;
v___y_6143_ = v___y_6153_;
v___y_6144_ = v___y_6156_;
v___y_6145_ = v___y_6154_;
v___y_6146_ = v___x_6158_;
goto v___jp_6142_;
}
}
v___jp_6159_:
{
uint64_t v___x_6165_; uint64_t v_encodedExponent_6166_; uint32_t v___x_6167_; uint64_t v___x_6168_; uint8_t v___x_6169_; 
v___x_6165_ = 171ULL;
v_encodedExponent_6166_ = lean_uint64_sub(v___y_6163_, v___x_6165_);
v___x_6167_ = lean_uint64_to_uint32(v_encodedExponent_6166_);
v___x_6168_ = 8388608ULL;
v___x_6169_ = lean_uint64_dec_lt(v___y_6164_, v___x_6168_);
if (v___x_6169_ == 0)
{
uint64_t v___x_6170_; uint32_t v___x_6171_; 
v___x_6170_ = lean_uint64_sub(v___y_6164_, v___x_6168_);
v___x_6171_ = lean_uint64_to_uint32(v___x_6170_);
v___y_6153_ = v___y_6160_;
v___y_6154_ = v___x_6167_;
v___y_6155_ = v___y_6162_;
v___y_6156_ = v___x_6171_;
goto v___jp_6152_;
}
else
{
uint32_t v___x_6172_; 
v___x_6172_ = lean_uint64_to_uint32(v___y_6161_);
v___y_6153_ = v___y_6160_;
v___y_6154_ = v___x_6167_;
v___y_6155_ = v___y_6162_;
v___y_6156_ = v___x_6172_;
goto v___jp_6152_;
}
}
v___jp_6173_:
{
uint64_t v___x_6180_; uint8_t v___x_6181_; 
v___x_6180_ = 425ULL;
v___x_6181_ = lean_uint64_dec_lt(v___x_6180_, v___y_6179_);
if (v___x_6181_ == 0)
{
if (v___y_6177_ == 0)
{
v___y_6160_ = v___y_6174_;
v___y_6161_ = v___y_6176_;
v___y_6162_ = v___y_6178_;
v___y_6163_ = v___y_6179_;
v___y_6164_ = v___y_6175_;
goto v___jp_6159_;
}
else
{
uint64_t v___x_6182_; 
v___x_6182_ = 8388608ULL;
v___y_6160_ = v___y_6174_;
v___y_6161_ = v___y_6176_;
v___y_6162_ = v___y_6178_;
v___y_6163_ = v___y_6179_;
v___y_6164_ = v___x_6182_;
goto v___jp_6159_;
}
}
else
{
if (v___y_6178_ == 0)
{
uint32_t v___x_6183_; 
v___x_6183_ = 2139095040;
return v___x_6183_;
}
else
{
uint32_t v___x_6184_; 
v___x_6184_ = 4286578688;
return v___x_6184_;
}
}
}
v___jp_6185_:
{
uint64_t v___x_6191_; uint8_t v_carry_6192_; 
v___x_6191_ = 16777216ULL;
v_carry_6192_ = lean_uint64_dec_eq(v___y_6190_, v___x_6191_);
if (v_carry_6192_ == 0)
{
v___y_6174_ = v___y_6186_;
v___y_6175_ = v___y_6190_;
v___y_6176_ = v___y_6187_;
v___y_6177_ = v_carry_6192_;
v___y_6178_ = v___y_6189_;
v___y_6179_ = v___y_6188_;
goto v___jp_6173_;
}
else
{
uint64_t v___x_6193_; uint64_t v___x_6194_; 
v___x_6193_ = 1ULL;
v___x_6194_ = lean_uint64_add(v___y_6188_, v___x_6193_);
v___y_6174_ = v___y_6186_;
v___y_6175_ = v___y_6190_;
v___y_6176_ = v___y_6187_;
v___y_6177_ = v_carry_6192_;
v___y_6178_ = v___y_6189_;
v___y_6179_ = v___x_6194_;
goto v___jp_6173_;
}
}
v___jp_6195_:
{
uint64_t v_position_6202_; uint64_t v___x_6203_; uint8_t v___x_6204_; 
v_position_6202_ = lean_uint64_add(v___y_6201_, v___y_6198_);
v___x_6203_ = 172ULL;
v___x_6204_ = lean_uint64_dec_lt(v_position_6202_, v___x_6203_);
if (v___x_6204_ == 0)
{
uint64_t v___x_6205_; uint8_t v___x_6206_; 
v___x_6205_ = 23ULL;
v___x_6206_ = lean_uint64_dec_lt(v___y_6201_, v___x_6205_);
if (v___x_6206_ == 0)
{
uint64_t v___x_6207_; uint8_t v___x_6208_; 
v___x_6207_ = lean_uint64_sub(v___y_6201_, v___x_6205_);
v___x_6208_ = lean_uint64_dec_eq(v___x_6207_, v___y_6197_);
if (v___x_6208_ == 0)
{
uint64_t v___x_6209_; uint8_t v___x_6210_; 
v___x_6209_ = 64ULL;
v___x_6210_ = lean_uint64_dec_lt(v___x_6207_, v___x_6209_);
if (v___x_6210_ == 0)
{
uint8_t v___x_6211_; 
v___x_6211_ = lean_uint64_dec_eq(v___x_6207_, v___x_6209_);
if (v___x_6211_ == 0)
{
v___y_6186_ = v___y_6196_;
v___y_6187_ = v___y_6197_;
v___y_6188_ = v_position_6202_;
v___y_6189_ = v___y_6200_;
v___y_6190_ = v___y_6197_;
goto v___jp_6185_;
}
else
{
uint64_t v___x_6212_; uint8_t v___x_6213_; 
v___x_6212_ = 9223372036854775808ULL;
v___x_6213_ = lean_uint64_dec_lt(v___x_6212_, v___y_6199_);
if (v___x_6213_ == 0)
{
v___y_6186_ = v___y_6196_;
v___y_6187_ = v___y_6197_;
v___y_6188_ = v_position_6202_;
v___y_6189_ = v___y_6200_;
v___y_6190_ = v___y_6197_;
goto v___jp_6185_;
}
else
{
uint64_t v___x_6214_; 
v___x_6214_ = 1ULL;
v___y_6186_ = v___y_6196_;
v___y_6187_ = v___y_6197_;
v___y_6188_ = v_position_6202_;
v___y_6189_ = v___y_6200_;
v___y_6190_ = v___x_6214_;
goto v___jp_6185_;
}
}
}
else
{
uint64_t v_quotient_6215_; uint64_t v___x_6216_; uint64_t v___x_6217_; uint64_t v___x_6218_; uint64_t v_remainder_6219_; uint64_t v___x_6220_; uint64_t v_half_6221_; uint8_t v___x_6222_; 
v_quotient_6215_ = lean_uint64_shift_right(v___y_6199_, v___x_6207_);
v___x_6216_ = 1ULL;
v___x_6217_ = lean_uint64_shift_left(v___x_6216_, v___x_6207_);
v___x_6218_ = lean_uint64_sub(v___x_6217_, v___x_6216_);
v_remainder_6219_ = lean_uint64_land(v___y_6199_, v___x_6218_);
v___x_6220_ = lean_uint64_sub(v___x_6207_, v___x_6216_);
v_half_6221_ = lean_uint64_shift_left(v___x_6216_, v___x_6220_);
v___x_6222_ = lean_uint64_dec_lt(v_remainder_6219_, v_half_6221_);
if (v___x_6222_ == 0)
{
uint8_t v___x_6223_; 
v___x_6223_ = lean_uint64_dec_lt(v_half_6221_, v_remainder_6219_);
if (v___x_6223_ == 0)
{
uint64_t v___x_6224_; uint8_t v___x_6225_; 
v___x_6224_ = lean_uint64_land(v_quotient_6215_, v___x_6216_);
v___x_6225_ = lean_uint64_dec_eq(v___x_6224_, v___y_6197_);
if (v___x_6225_ == 0)
{
uint64_t v___x_6226_; 
v___x_6226_ = lean_uint64_add(v_quotient_6215_, v___x_6216_);
v___y_6186_ = v___y_6196_;
v___y_6187_ = v___y_6197_;
v___y_6188_ = v_position_6202_;
v___y_6189_ = v___y_6200_;
v___y_6190_ = v___x_6226_;
goto v___jp_6185_;
}
else
{
v___y_6186_ = v___y_6196_;
v___y_6187_ = v___y_6197_;
v___y_6188_ = v_position_6202_;
v___y_6189_ = v___y_6200_;
v___y_6190_ = v_quotient_6215_;
goto v___jp_6185_;
}
}
else
{
uint64_t v___x_6227_; 
v___x_6227_ = lean_uint64_add(v_quotient_6215_, v___x_6216_);
v___y_6186_ = v___y_6196_;
v___y_6187_ = v___y_6197_;
v___y_6188_ = v_position_6202_;
v___y_6189_ = v___y_6200_;
v___y_6190_ = v___x_6227_;
goto v___jp_6185_;
}
}
else
{
v___y_6186_ = v___y_6196_;
v___y_6187_ = v___y_6197_;
v___y_6188_ = v_position_6202_;
v___y_6189_ = v___y_6200_;
v___y_6190_ = v_quotient_6215_;
goto v___jp_6185_;
}
}
}
else
{
v___y_6186_ = v___y_6196_;
v___y_6187_ = v___y_6197_;
v___y_6188_ = v_position_6202_;
v___y_6189_ = v___y_6200_;
v___y_6190_ = v___y_6199_;
goto v___jp_6185_;
}
}
else
{
uint64_t v___x_6228_; uint64_t v___x_6229_; 
v___x_6228_ = lean_uint64_sub(v___x_6205_, v___y_6201_);
v___x_6229_ = lean_uint64_shift_left(v___y_6199_, v___x_6228_);
v___y_6186_ = v___y_6196_;
v___y_6187_ = v___y_6197_;
v___y_6188_ = v_position_6202_;
v___y_6189_ = v___y_6200_;
v___y_6190_ = v___x_6229_;
goto v___jp_6185_;
}
}
else
{
uint64_t v___x_6230_; uint8_t v___x_6231_; 
v___x_6230_ = 149ULL;
v___x_6231_ = lean_uint64_dec_lt(v___y_6198_, v___x_6230_);
if (v___x_6231_ == 0)
{
uint64_t v___x_6232_; uint64_t v___x_6233_; 
v___x_6232_ = lean_uint64_sub(v___y_6198_, v___x_6230_);
v___x_6233_ = lean_uint64_shift_left(v___y_6199_, v___x_6232_);
v___y_5818_ = v___y_6196_;
v___y_5819_ = v___y_6197_;
v___y_5820_ = v___y_6200_;
v___y_5821_ = v___x_6233_;
goto v___jp_5817_;
}
else
{
uint64_t v___x_6234_; uint8_t v___x_6235_; 
v___x_6234_ = lean_uint64_sub(v___x_6230_, v___y_6198_);
v___x_6235_ = lean_uint64_dec_eq(v___x_6234_, v___y_6197_);
if (v___x_6235_ == 0)
{
uint64_t v___x_6236_; uint8_t v___x_6237_; 
v___x_6236_ = 64ULL;
v___x_6237_ = lean_uint64_dec_lt(v___x_6234_, v___x_6236_);
if (v___x_6237_ == 0)
{
uint8_t v___x_6238_; 
v___x_6238_ = lean_uint64_dec_eq(v___x_6234_, v___x_6236_);
if (v___x_6238_ == 0)
{
v___y_5818_ = v___y_6196_;
v___y_5819_ = v___y_6197_;
v___y_5820_ = v___y_6200_;
v___y_5821_ = v___y_6197_;
goto v___jp_5817_;
}
else
{
uint64_t v___x_6239_; uint8_t v___x_6240_; 
v___x_6239_ = 9223372036854775808ULL;
v___x_6240_ = lean_uint64_dec_lt(v___x_6239_, v___y_6199_);
if (v___x_6240_ == 0)
{
v___y_5818_ = v___y_6196_;
v___y_5819_ = v___y_6197_;
v___y_5820_ = v___y_6200_;
v___y_5821_ = v___y_6197_;
goto v___jp_5817_;
}
else
{
uint64_t v___x_6241_; 
v___x_6241_ = 1ULL;
v___y_5818_ = v___y_6196_;
v___y_5819_ = v___y_6197_;
v___y_5820_ = v___y_6200_;
v___y_5821_ = v___x_6241_;
goto v___jp_5817_;
}
}
}
else
{
uint64_t v_quotient_6242_; uint64_t v___x_6243_; uint64_t v___x_6244_; uint64_t v___x_6245_; uint64_t v_remainder_6246_; uint64_t v___x_6247_; uint64_t v_half_6248_; uint8_t v___x_6249_; 
v_quotient_6242_ = lean_uint64_shift_right(v___y_6199_, v___x_6234_);
v___x_6243_ = 1ULL;
v___x_6244_ = lean_uint64_shift_left(v___x_6243_, v___x_6234_);
v___x_6245_ = lean_uint64_sub(v___x_6244_, v___x_6243_);
v_remainder_6246_ = lean_uint64_land(v___y_6199_, v___x_6245_);
v___x_6247_ = lean_uint64_sub(v___x_6234_, v___x_6243_);
v_half_6248_ = lean_uint64_shift_left(v___x_6243_, v___x_6247_);
v___x_6249_ = lean_uint64_dec_lt(v_remainder_6246_, v_half_6248_);
if (v___x_6249_ == 0)
{
uint8_t v___x_6250_; 
v___x_6250_ = lean_uint64_dec_lt(v_half_6248_, v_remainder_6246_);
if (v___x_6250_ == 0)
{
uint64_t v___x_6251_; uint8_t v___x_6252_; 
v___x_6251_ = lean_uint64_land(v_quotient_6242_, v___x_6243_);
v___x_6252_ = lean_uint64_dec_eq(v___x_6251_, v___y_6197_);
if (v___x_6252_ == 0)
{
uint64_t v___x_6253_; 
v___x_6253_ = lean_uint64_add(v_quotient_6242_, v___x_6243_);
v___y_5818_ = v___y_6196_;
v___y_5819_ = v___y_6197_;
v___y_5820_ = v___y_6200_;
v___y_5821_ = v___x_6253_;
goto v___jp_5817_;
}
else
{
v___y_5818_ = v___y_6196_;
v___y_5819_ = v___y_6197_;
v___y_5820_ = v___y_6200_;
v___y_5821_ = v_quotient_6242_;
goto v___jp_5817_;
}
}
else
{
uint64_t v___x_6254_; 
v___x_6254_ = lean_uint64_add(v_quotient_6242_, v___x_6243_);
v___y_5818_ = v___y_6196_;
v___y_5819_ = v___y_6197_;
v___y_5820_ = v___y_6200_;
v___y_5821_ = v___x_6254_;
goto v___jp_5817_;
}
}
else
{
v___y_5818_ = v___y_6196_;
v___y_5819_ = v___y_6197_;
v___y_5820_ = v___y_6200_;
v___y_5821_ = v_quotient_6242_;
goto v___jp_5817_;
}
}
}
else
{
v___y_5818_ = v___y_6196_;
v___y_5819_ = v___y_6197_;
v___y_5820_ = v___y_6200_;
v___y_5821_ = v___y_6199_;
goto v___jp_5817_;
}
}
}
}
v___jp_6255_:
{
uint64_t v___x_6263_; uint64_t v___x_6264_; uint8_t v___x_6265_; 
v___x_6263_ = 1ULL;
v___x_6264_ = lean_uint64_shift_right(v___y_6259_, v___x_6263_);
v___x_6265_ = lean_uint64_dec_eq(v___x_6264_, v___y_6257_);
if (v___x_6265_ == 0)
{
uint64_t v___x_6266_; 
v___x_6266_ = lean_uint64_add(v___y_6262_, v___x_6263_);
v___y_6196_ = v___y_6256_;
v___y_6197_ = v___y_6257_;
v___y_6198_ = v___y_6258_;
v___y_6199_ = v___y_6260_;
v___y_6200_ = v___y_6261_;
v___y_6201_ = v___x_6266_;
goto v___jp_6195_;
}
else
{
v___y_6196_ = v___y_6256_;
v___y_6197_ = v___y_6257_;
v___y_6198_ = v___y_6258_;
v___y_6199_ = v___y_6260_;
v___y_6200_ = v___y_6261_;
v___y_6201_ = v___y_6262_;
goto v___jp_6195_;
}
}
v___jp_6267_:
{
uint64_t v___x_6277_; uint8_t v___x_6278_; 
v___x_6277_ = lean_uint64_shift_right(v___y_6271_, v___y_6272_);
v___x_6278_ = lean_uint64_dec_eq(v___x_6277_, v___y_6269_);
if (v___x_6278_ == 0)
{
uint64_t v___x_6279_; 
v___x_6279_ = lean_uint64_add(v___y_6273_, v___y_6272_);
v___y_6256_ = v___y_6268_;
v___y_6257_ = v___y_6269_;
v___y_6258_ = v___y_6270_;
v___y_6259_ = v___y_6276_;
v___y_6260_ = v___y_6274_;
v___y_6261_ = v___y_6275_;
v___y_6262_ = v___x_6279_;
goto v___jp_6255_;
}
else
{
v___y_6256_ = v___y_6268_;
v___y_6257_ = v___y_6269_;
v___y_6258_ = v___y_6270_;
v___y_6259_ = v___y_6276_;
v___y_6260_ = v___y_6274_;
v___y_6261_ = v___y_6275_;
v___y_6262_ = v___y_6273_;
goto v___jp_6255_;
}
}
v___jp_6280_:
{
uint64_t v___x_6288_; uint64_t v___x_6289_; uint8_t v___x_6290_; 
v___x_6288_ = 2ULL;
v___x_6289_ = lean_uint64_shift_right(v___y_6284_, v___x_6288_);
v___x_6290_ = lean_uint64_dec_eq(v___x_6289_, v___y_6282_);
if (v___x_6290_ == 0)
{
v___y_6268_ = v___y_6281_;
v___y_6269_ = v___y_6282_;
v___y_6270_ = v___y_6283_;
v___y_6271_ = v___y_6284_;
v___y_6272_ = v___x_6288_;
v___y_6273_ = v___y_6287_;
v___y_6274_ = v___y_6285_;
v___y_6275_ = v___y_6286_;
v___y_6276_ = v___x_6289_;
goto v___jp_6267_;
}
else
{
v___y_6268_ = v___y_6281_;
v___y_6269_ = v___y_6282_;
v___y_6270_ = v___y_6283_;
v___y_6271_ = v___y_6284_;
v___y_6272_ = v___x_6288_;
v___y_6273_ = v___y_6287_;
v___y_6274_ = v___y_6285_;
v___y_6275_ = v___y_6286_;
v___y_6276_ = v___y_6284_;
goto v___jp_6267_;
}
}
v___jp_6291_:
{
uint64_t v___x_6301_; uint8_t v___x_6302_; 
v___x_6301_ = lean_uint64_shift_right(v___y_6296_, v___y_6294_);
v___x_6302_ = lean_uint64_dec_eq(v___x_6301_, v___y_6293_);
if (v___x_6302_ == 0)
{
uint64_t v___x_6303_; 
v___x_6303_ = lean_uint64_add(v___y_6298_, v___y_6294_);
v___y_6281_ = v___y_6292_;
v___y_6282_ = v___y_6293_;
v___y_6283_ = v___y_6295_;
v___y_6284_ = v___y_6300_;
v___y_6285_ = v___y_6297_;
v___y_6286_ = v___y_6299_;
v___y_6287_ = v___x_6303_;
goto v___jp_6280_;
}
else
{
v___y_6281_ = v___y_6292_;
v___y_6282_ = v___y_6293_;
v___y_6283_ = v___y_6295_;
v___y_6284_ = v___y_6300_;
v___y_6285_ = v___y_6297_;
v___y_6286_ = v___y_6299_;
v___y_6287_ = v___y_6298_;
goto v___jp_6280_;
}
}
v___jp_6304_:
{
uint64_t v___x_6312_; uint64_t v___x_6313_; uint8_t v___x_6314_; 
v___x_6312_ = 4ULL;
v___x_6313_ = lean_uint64_shift_right(v___y_6308_, v___x_6312_);
v___x_6314_ = lean_uint64_dec_eq(v___x_6313_, v___y_6306_);
if (v___x_6314_ == 0)
{
v___y_6292_ = v___y_6305_;
v___y_6293_ = v___y_6306_;
v___y_6294_ = v___x_6312_;
v___y_6295_ = v___y_6307_;
v___y_6296_ = v___y_6308_;
v___y_6297_ = v___y_6309_;
v___y_6298_ = v___y_6311_;
v___y_6299_ = v___y_6310_;
v___y_6300_ = v___x_6313_;
goto v___jp_6291_;
}
else
{
v___y_6292_ = v___y_6305_;
v___y_6293_ = v___y_6306_;
v___y_6294_ = v___x_6312_;
v___y_6295_ = v___y_6307_;
v___y_6296_ = v___y_6308_;
v___y_6297_ = v___y_6309_;
v___y_6298_ = v___y_6311_;
v___y_6299_ = v___y_6310_;
v___y_6300_ = v___y_6308_;
goto v___jp_6291_;
}
}
v___jp_6315_:
{
uint64_t v___x_6325_; uint8_t v___x_6326_; 
v___x_6325_ = lean_uint64_shift_right(v___y_6318_, v___y_6316_);
v___x_6326_ = lean_uint64_dec_eq(v___x_6325_, v___y_6319_);
if (v___x_6326_ == 0)
{
uint64_t v___x_6327_; 
v___x_6327_ = lean_uint64_add(v___y_6321_, v___y_6316_);
v___y_6305_ = v___y_6317_;
v___y_6306_ = v___y_6319_;
v___y_6307_ = v___y_6320_;
v___y_6308_ = v___y_6324_;
v___y_6309_ = v___y_6322_;
v___y_6310_ = v___y_6323_;
v___y_6311_ = v___x_6327_;
goto v___jp_6304_;
}
else
{
v___y_6305_ = v___y_6317_;
v___y_6306_ = v___y_6319_;
v___y_6307_ = v___y_6320_;
v___y_6308_ = v___y_6324_;
v___y_6309_ = v___y_6322_;
v___y_6310_ = v___y_6323_;
v___y_6311_ = v___y_6321_;
goto v___jp_6304_;
}
}
v___jp_6328_:
{
uint64_t v___x_6336_; uint64_t v___x_6337_; uint8_t v___x_6338_; 
v___x_6336_ = 8ULL;
v___x_6337_ = lean_uint64_shift_right(v___y_6330_, v___x_6336_);
v___x_6338_ = lean_uint64_dec_eq(v___x_6337_, v___y_6331_);
if (v___x_6338_ == 0)
{
v___y_6316_ = v___x_6336_;
v___y_6317_ = v___y_6329_;
v___y_6318_ = v___y_6330_;
v___y_6319_ = v___y_6331_;
v___y_6320_ = v___y_6332_;
v___y_6321_ = v___y_6335_;
v___y_6322_ = v___y_6333_;
v___y_6323_ = v___y_6334_;
v___y_6324_ = v___x_6337_;
goto v___jp_6315_;
}
else
{
v___y_6316_ = v___x_6336_;
v___y_6317_ = v___y_6329_;
v___y_6318_ = v___y_6330_;
v___y_6319_ = v___y_6331_;
v___y_6320_ = v___y_6332_;
v___y_6321_ = v___y_6335_;
v___y_6322_ = v___y_6333_;
v___y_6323_ = v___y_6334_;
v___y_6324_ = v___y_6330_;
goto v___jp_6315_;
}
}
v___jp_6339_:
{
uint64_t v___x_6349_; uint8_t v___x_6350_; 
v___x_6349_ = lean_uint64_shift_right(v___y_6342_, v___y_6345_);
v___x_6350_ = lean_uint64_dec_eq(v___x_6349_, v___y_6341_);
if (v___x_6350_ == 0)
{
uint64_t v___x_6351_; 
v___x_6351_ = lean_uint64_add(v___y_6344_, v___y_6345_);
v___y_6329_ = v___y_6340_;
v___y_6330_ = v___y_6348_;
v___y_6331_ = v___y_6341_;
v___y_6332_ = v___y_6343_;
v___y_6333_ = v___y_6346_;
v___y_6334_ = v___y_6347_;
v___y_6335_ = v___x_6351_;
goto v___jp_6328_;
}
else
{
v___y_6329_ = v___y_6340_;
v___y_6330_ = v___y_6348_;
v___y_6331_ = v___y_6341_;
v___y_6332_ = v___y_6343_;
v___y_6333_ = v___y_6346_;
v___y_6334_ = v___y_6347_;
v___y_6335_ = v___y_6344_;
goto v___jp_6328_;
}
}
v___jp_6352_:
{
uint64_t v___x_6360_; uint64_t v___x_6361_; uint8_t v___x_6362_; 
v___x_6360_ = 16ULL;
v___x_6361_ = lean_uint64_shift_right(v___y_6355_, v___x_6360_);
v___x_6362_ = lean_uint64_dec_eq(v___x_6361_, v___y_6354_);
if (v___x_6362_ == 0)
{
v___y_6340_ = v___y_6353_;
v___y_6341_ = v___y_6354_;
v___y_6342_ = v___y_6355_;
v___y_6343_ = v___y_6356_;
v___y_6344_ = v___y_6359_;
v___y_6345_ = v___x_6360_;
v___y_6346_ = v___y_6357_;
v___y_6347_ = v___y_6358_;
v___y_6348_ = v___x_6361_;
goto v___jp_6339_;
}
else
{
v___y_6340_ = v___y_6353_;
v___y_6341_ = v___y_6354_;
v___y_6342_ = v___y_6355_;
v___y_6343_ = v___y_6356_;
v___y_6344_ = v___y_6359_;
v___y_6345_ = v___x_6360_;
v___y_6346_ = v___y_6357_;
v___y_6347_ = v___y_6358_;
v___y_6348_ = v___y_6355_;
goto v___jp_6339_;
}
}
v___jp_6363_:
{
uint64_t v___x_6371_; uint8_t v___x_6372_; 
v___x_6371_ = lean_uint64_shift_right(v___y_6368_, v___y_6367_);
v___x_6372_ = lean_uint64_dec_eq(v___x_6371_, v___y_6365_);
if (v___x_6372_ == 0)
{
v___y_6353_ = v___y_6364_;
v___y_6354_ = v___y_6365_;
v___y_6355_ = v___y_6370_;
v___y_6356_ = v___y_6366_;
v___y_6357_ = v___y_6368_;
v___y_6358_ = v___y_6369_;
v___y_6359_ = v___y_6367_;
goto v___jp_6352_;
}
else
{
v___y_6353_ = v___y_6364_;
v___y_6354_ = v___y_6365_;
v___y_6355_ = v___y_6370_;
v___y_6356_ = v___y_6366_;
v___y_6357_ = v___y_6368_;
v___y_6358_ = v___y_6369_;
v___y_6359_ = v___y_6365_;
goto v___jp_6352_;
}
}
v___jp_6373_:
{
uint64_t v___x_6378_; uint8_t v___x_6379_; 
v___x_6378_ = 0ULL;
v___x_6379_ = lean_uint64_dec_eq(v___y_6376_, v___x_6378_);
if (v___x_6379_ == 0)
{
uint64_t v___x_6380_; uint64_t v___x_6381_; uint8_t v___x_6382_; 
v___x_6380_ = 32ULL;
v___x_6381_ = lean_uint64_shift_right(v___y_6376_, v___x_6380_);
v___x_6382_ = lean_uint64_dec_eq(v___x_6381_, v___x_6378_);
if (v___x_6382_ == 0)
{
v___y_6364_ = v___y_6374_;
v___y_6365_ = v___x_6378_;
v___y_6366_ = v___y_6375_;
v___y_6367_ = v___x_6380_;
v___y_6368_ = v___y_6376_;
v___y_6369_ = v___y_6377_;
v___y_6370_ = v___x_6381_;
goto v___jp_6363_;
}
else
{
v___y_6364_ = v___y_6374_;
v___y_6365_ = v___x_6378_;
v___y_6366_ = v___y_6375_;
v___y_6367_ = v___x_6380_;
v___y_6368_ = v___y_6376_;
v___y_6369_ = v___y_6377_;
v___y_6370_ = v___y_6376_;
goto v___jp_6363_;
}
}
else
{
if (v___y_6377_ == 0)
{
uint32_t v___x_6383_; 
v___x_6383_ = 0;
return v___x_6383_;
}
else
{
uint32_t v___x_6384_; 
v___x_6384_ = 2147483648;
return v___x_6384_;
}
}
}
v___jp_6385_:
{
uint64_t v___x_6392_; uint64_t v___x_6393_; uint64_t v___x_6394_; uint8_t v___x_6395_; 
v___x_6392_ = lean_uint64_mul(v___y_6388_, v___y_6387_);
v___x_6393_ = lean_uint64_add(v___y_6389_, v___y_6391_);
v___x_6394_ = 281474976710656ULL;
v___x_6395_ = lean_uint64_dec_lt(v___x_6392_, v___x_6394_);
if (v___x_6395_ == 0)
{
v___y_6374_ = v___y_6386_;
v___y_6375_ = v___x_6393_;
v___y_6376_ = v___x_6392_;
v___y_6377_ = v___y_6390_;
goto v___jp_6373_;
}
else
{
uint64_t v___x_6396_; uint8_t v___x_6397_; 
v___x_6396_ = 123ULL;
v___x_6397_ = lean_uint64_dec_le(v___x_6393_, v___x_6396_);
if (v___x_6397_ == 0)
{
v___y_6374_ = v___y_6386_;
v___y_6375_ = v___x_6393_;
v___y_6376_ = v___x_6392_;
v___y_6377_ = v___y_6390_;
goto v___jp_6373_;
}
else
{
uint64_t v___x_6398_; uint8_t v___x_6399_; 
v___x_6398_ = 0ULL;
v___x_6399_ = lean_uint64_dec_eq(v___x_6392_, v___x_6398_);
if (v___x_6399_ == 0)
{
uint64_t v___x_6400_; uint64_t v___x_6401_; uint8_t v___x_6402_; 
v___x_6400_ = 149ULL;
v___x_6401_ = lean_uint64_sub(v___x_6400_, v___x_6393_);
v___x_6402_ = lean_uint64_dec_eq(v___x_6401_, v___x_6398_);
if (v___x_6402_ == 0)
{
uint64_t v___x_6403_; uint8_t v___x_6404_; 
v___x_6403_ = 64ULL;
v___x_6404_ = lean_uint64_dec_lt(v___x_6401_, v___x_6403_);
if (v___x_6404_ == 0)
{
uint8_t v___x_6405_; 
v___x_6405_ = lean_uint64_dec_eq(v___x_6401_, v___x_6403_);
if (v___x_6405_ == 0)
{
v___y_5839_ = v___y_6386_;
v___y_5840_ = v___x_6398_;
v___y_5841_ = v___y_6390_;
v___y_5842_ = v___x_6398_;
goto v___jp_5838_;
}
else
{
uint64_t v___x_6406_; uint8_t v___x_6407_; 
v___x_6406_ = 9223372036854775808ULL;
v___x_6407_ = lean_uint64_dec_lt(v___x_6406_, v___x_6392_);
if (v___x_6407_ == 0)
{
v___y_5839_ = v___y_6386_;
v___y_5840_ = v___x_6398_;
v___y_5841_ = v___y_6390_;
v___y_5842_ = v___x_6398_;
goto v___jp_5838_;
}
else
{
uint64_t v___x_6408_; 
v___x_6408_ = 1ULL;
v___y_5839_ = v___y_6386_;
v___y_5840_ = v___x_6398_;
v___y_5841_ = v___y_6390_;
v___y_5842_ = v___x_6408_;
goto v___jp_5838_;
}
}
}
else
{
uint64_t v_quotient_6409_; uint64_t v___x_6410_; uint64_t v___x_6411_; uint64_t v___x_6412_; uint64_t v_remainder_6413_; uint64_t v___x_6414_; uint64_t v_half_6415_; uint8_t v___x_6416_; 
v_quotient_6409_ = lean_uint64_shift_right(v___x_6392_, v___x_6401_);
v___x_6410_ = 1ULL;
v___x_6411_ = lean_uint64_shift_left(v___x_6410_, v___x_6401_);
v___x_6412_ = lean_uint64_sub(v___x_6411_, v___x_6410_);
v_remainder_6413_ = lean_uint64_land(v___x_6392_, v___x_6412_);
v___x_6414_ = lean_uint64_sub(v___x_6401_, v___x_6410_);
v_half_6415_ = lean_uint64_shift_left(v___x_6410_, v___x_6414_);
v___x_6416_ = lean_uint64_dec_lt(v_remainder_6413_, v_half_6415_);
if (v___x_6416_ == 0)
{
uint8_t v___x_6417_; 
v___x_6417_ = lean_uint64_dec_lt(v_half_6415_, v_remainder_6413_);
if (v___x_6417_ == 0)
{
uint64_t v___x_6418_; uint8_t v___x_6419_; 
v___x_6418_ = lean_uint64_land(v_quotient_6409_, v___x_6410_);
v___x_6419_ = lean_uint64_dec_eq(v___x_6418_, v___x_6398_);
if (v___x_6419_ == 0)
{
uint64_t v___x_6420_; 
v___x_6420_ = lean_uint64_add(v_quotient_6409_, v___x_6410_);
v___y_5839_ = v___y_6386_;
v___y_5840_ = v___x_6398_;
v___y_5841_ = v___y_6390_;
v___y_5842_ = v___x_6420_;
goto v___jp_5838_;
}
else
{
v___y_5839_ = v___y_6386_;
v___y_5840_ = v___x_6398_;
v___y_5841_ = v___y_6390_;
v___y_5842_ = v_quotient_6409_;
goto v___jp_5838_;
}
}
else
{
uint64_t v___x_6421_; 
v___x_6421_ = lean_uint64_add(v_quotient_6409_, v___x_6410_);
v___y_5839_ = v___y_6386_;
v___y_5840_ = v___x_6398_;
v___y_5841_ = v___y_6390_;
v___y_5842_ = v___x_6421_;
goto v___jp_5838_;
}
}
else
{
v___y_5839_ = v___y_6386_;
v___y_5840_ = v___x_6398_;
v___y_5841_ = v___y_6390_;
v___y_5842_ = v_quotient_6409_;
goto v___jp_5838_;
}
}
}
else
{
v___y_5839_ = v___y_6386_;
v___y_5840_ = v___x_6398_;
v___y_5841_ = v___y_6390_;
v___y_5842_ = v___x_6392_;
goto v___jp_5838_;
}
}
else
{
if (v___y_6390_ == 0)
{
uint32_t v___x_6422_; 
v___x_6422_ = 0;
return v___x_6422_;
}
else
{
uint32_t v___x_6423_; 
v___x_6423_ = 2147483648;
return v___x_6423_;
}
}
}
}
}
v___jp_6427_:
{
uint64_t v___x_6433_; uint64_t v___x_6434_; uint8_t v___x_6435_; 
v___x_6433_ = lean_uint32_to_uint64(v_ey_6426_);
v___x_6434_ = 0ULL;
v___x_6435_ = lean_uint64_dec_eq(v___x_6433_, v___x_6434_);
if (v___x_6435_ == 0)
{
uint64_t v___x_6436_; uint64_t v___x_6437_; 
v___x_6436_ = 1ULL;
v___x_6437_ = lean_uint64_sub(v___x_6433_, v___x_6436_);
v___y_6122_ = v___y_6432_;
v___y_6123_ = v___y_6428_;
v___y_6124_ = v___y_6429_;
v___y_6125_ = v___y_6431_;
v___y_6126_ = v___y_6430_;
v___y_6127_ = v___x_6437_;
goto v___jp_6121_;
}
else
{
v___y_6122_ = v___y_6432_;
v___y_6123_ = v___y_6428_;
v___y_6124_ = v___y_6429_;
v___y_6125_ = v___y_6431_;
v___y_6126_ = v___y_6430_;
v___y_6127_ = v___x_6434_;
goto v___jp_6121_;
}
}
v___jp_6438_:
{
uint64_t v___x_6443_; uint64_t v___x_6444_; uint8_t v___x_6445_; 
v___x_6443_ = lean_uint32_to_uint64(v_ex_6424_);
v___x_6444_ = 0ULL;
v___x_6445_ = lean_uint64_dec_eq(v___x_6443_, v___x_6444_);
if (v___x_6445_ == 0)
{
uint64_t v___x_6446_; uint64_t v___x_6447_; 
v___x_6446_ = 1ULL;
v___x_6447_ = lean_uint64_sub(v___x_6443_, v___x_6446_);
v___y_6428_ = v___y_6439_;
v___y_6429_ = v___y_6442_;
v___y_6430_ = v___y_6441_;
v___y_6431_ = v___y_6440_;
v___y_6432_ = v___x_6447_;
goto v___jp_6427_;
}
else
{
v___y_6428_ = v___y_6439_;
v___y_6429_ = v___y_6442_;
v___y_6430_ = v___y_6441_;
v___y_6431_ = v___y_6440_;
v___y_6432_ = v___x_6444_;
goto v___jp_6427_;
}
}
v___jp_6448_:
{
uint32_t v___x_6453_; uint8_t v___x_6454_; 
v___x_6453_ = 0;
v___x_6454_ = lean_uint32_dec_eq(v_ey_6426_, v___x_6453_);
if (v___x_6454_ == 0)
{
uint64_t v___x_6455_; uint64_t v___x_6456_; uint64_t v___x_6457_; 
v___x_6455_ = lean_uint32_to_uint64(v___y_6449_);
v___x_6456_ = 8388608ULL;
v___x_6457_ = lean_uint64_lor(v___x_6455_, v___x_6456_);
v___y_6439_ = v___y_6450_;
v___y_6440_ = v___y_6451_;
v___y_6441_ = v___y_6452_;
v___y_6442_ = v___x_6457_;
goto v___jp_6438_;
}
else
{
uint64_t v___x_6458_; 
v___x_6458_ = lean_uint32_to_uint64(v___y_6449_);
v___y_6439_ = v___y_6450_;
v___y_6440_ = v___y_6451_;
v___y_6441_ = v___y_6452_;
v___y_6442_ = v___x_6458_;
goto v___jp_6438_;
}
}
v___jp_6459_:
{
uint32_t v___x_6461_; uint32_t v_xFraction_6462_; uint32_t v_yFraction_6463_; uint32_t v___x_6464_; uint8_t v___x_6465_; 
v___x_6461_ = 8388607;
v_xFraction_6462_ = lean_uint32_land(v_x_5801_, v___x_6461_);
v_yFraction_6463_ = lean_uint32_land(v_y_5802_, v___x_6461_);
v___x_6464_ = 0;
v___x_6465_ = lean_uint32_dec_eq(v_ex_6424_, v___x_6464_);
if (v___x_6465_ == 0)
{
uint64_t v___x_6466_; uint64_t v___x_6467_; uint64_t v___x_6468_; 
v___x_6466_ = lean_uint32_to_uint64(v_xFraction_6462_);
v___x_6467_ = 8388608ULL;
v___x_6468_ = lean_uint64_lor(v___x_6466_, v___x_6467_);
v___y_6449_ = v_yFraction_6463_;
v___y_6450_ = v___y_6460_;
v___y_6451_ = v___x_6461_;
v___y_6452_ = v___x_6468_;
goto v___jp_6448_;
}
else
{
uint64_t v___x_6469_; 
v___x_6469_ = lean_uint32_to_uint64(v_xFraction_6462_);
v___y_6449_ = v_yFraction_6463_;
v___y_6450_ = v___y_6460_;
v___y_6451_ = v___x_6461_;
v___y_6452_ = v___x_6469_;
goto v___jp_6448_;
}
}
v___jp_6470_:
{
uint8_t v___x_6471_; 
v___x_6471_ = 1;
v___y_6460_ = v___x_6471_;
goto v___jp_6459_;
}
v___jp_6472_:
{
if (v___y_6473_ == 0)
{
if (v___y_6475_ == 0)
{
v___y_6460_ = v___y_6474_;
goto v___jp_6459_;
}
else
{
goto v___jp_6470_;
}
}
else
{
if (v___y_6475_ == 0)
{
goto v___jp_6470_;
}
else
{
v___y_6460_ = v___y_6474_;
goto v___jp_6459_;
}
}
}
v___jp_6476_:
{
uint32_t v___x_6479_; uint32_t v___x_6480_; uint32_t v___x_6481_; uint8_t v___x_6482_; 
v___x_6479_ = 2147483648;
v___x_6480_ = lean_uint32_land(v_y_5802_, v___x_6479_);
v___x_6481_ = 0;
v___x_6482_ = lean_uint32_dec_eq(v___x_6480_, v___x_6481_);
if (v___x_6482_ == 0)
{
uint8_t v___x_6483_; 
v___x_6483_ = 1;
v___y_6473_ = v___y_6478_;
v___y_6474_ = v___y_6477_;
v___y_6475_ = v___x_6483_;
goto v___jp_6472_;
}
else
{
v___y_6473_ = v___y_6478_;
v___y_6474_ = v___y_6477_;
v___y_6475_ = v___y_6477_;
goto v___jp_6472_;
}
}
v___jp_6484_:
{
if (v___y_6485_ == 0)
{
uint32_t v___x_6486_; uint32_t v___x_6487_; uint32_t v___x_6488_; uint8_t v___x_6489_; 
v___x_6486_ = 2147483648;
v___x_6487_ = lean_uint32_land(v_x_5801_, v___x_6486_);
v___x_6488_ = 0;
v___x_6489_ = lean_uint32_dec_eq(v___x_6487_, v___x_6488_);
if (v___x_6489_ == 0)
{
uint8_t v___x_6490_; 
v___x_6490_ = 1;
v___y_6477_ = v___y_6485_;
v___y_6478_ = v___x_6490_;
goto v___jp_6476_;
}
else
{
v___y_6477_ = v___y_6485_;
v___y_6478_ = v___y_6485_;
goto v___jp_6476_;
}
}
else
{
lean_object* v___x_6491_; lean_object* v___x_6492_; lean_object* v___x_6493_; lean_object* v___x_6494_; uint32_t v___x_6495_; 
v___x_6491_ = ((lean_object*)(lp_competition_Submission_TunedAdd_Fmt___closed__0));
v___x_6492_ = lean_uint32_to_nat(v_x_5801_);
v___x_6493_ = lean_uint32_to_nat(v_y_5802_);
v___x_6494_ = lp_floatlib_FloatLib_Floats_Formats_BinaryInterchange_Model_MulBackend_word(v___x_6491_, v___x_6492_, v___x_6493_);
v___x_6495_ = lean_uint32_of_nat(v___x_6494_);
lean_dec(v___x_6494_);
return v___x_6495_;
}
}
v___jp_6496_:
{
uint64_t v___x_6502_; uint64_t v___x_6503_; uint8_t v___x_6504_; 
v___x_6502_ = lean_uint32_to_uint64(v_ey_6426_);
v___x_6503_ = 0ULL;
v___x_6504_ = lean_uint64_dec_eq(v___x_6502_, v___x_6503_);
if (v___x_6504_ == 0)
{
uint64_t v___x_6505_; uint64_t v___x_6506_; 
v___x_6505_ = 1ULL;
v___x_6506_ = lean_uint64_sub(v___x_6502_, v___x_6505_);
v___y_6386_ = v___y_6497_;
v___y_6387_ = v___y_6499_;
v___y_6388_ = v___y_6498_;
v___y_6389_ = v___y_6501_;
v___y_6390_ = v___y_6500_;
v___y_6391_ = v___x_6506_;
goto v___jp_6385_;
}
else
{
v___y_6386_ = v___y_6497_;
v___y_6387_ = v___y_6499_;
v___y_6388_ = v___y_6498_;
v___y_6389_ = v___y_6501_;
v___y_6390_ = v___y_6500_;
v___y_6391_ = v___x_6503_;
goto v___jp_6385_;
}
}
v___jp_6507_:
{
uint64_t v___x_6512_; uint64_t v___x_6513_; uint8_t v___x_6514_; 
v___x_6512_ = lean_uint32_to_uint64(v_ex_6424_);
v___x_6513_ = 0ULL;
v___x_6514_ = lean_uint64_dec_eq(v___x_6512_, v___x_6513_);
if (v___x_6514_ == 0)
{
uint64_t v___x_6515_; uint64_t v___x_6516_; 
v___x_6515_ = 1ULL;
v___x_6516_ = lean_uint64_sub(v___x_6512_, v___x_6515_);
v___y_6497_ = v___y_6508_;
v___y_6498_ = v___y_6509_;
v___y_6499_ = v___y_6511_;
v___y_6500_ = v___y_6510_;
v___y_6501_ = v___x_6516_;
goto v___jp_6496_;
}
else
{
v___y_6497_ = v___y_6508_;
v___y_6498_ = v___y_6509_;
v___y_6499_ = v___y_6511_;
v___y_6500_ = v___y_6510_;
v___y_6501_ = v___x_6513_;
goto v___jp_6496_;
}
}
v___jp_6517_:
{
uint32_t v___x_6522_; uint8_t v___x_6523_; 
v___x_6522_ = 0;
v___x_6523_ = lean_uint32_dec_eq(v_ey_6426_, v___x_6522_);
if (v___x_6523_ == 0)
{
uint64_t v___x_6524_; uint64_t v___x_6525_; uint64_t v___x_6526_; 
v___x_6524_ = lean_uint32_to_uint64(v___y_6519_);
v___x_6525_ = 8388608ULL;
v___x_6526_ = lean_uint64_lor(v___x_6524_, v___x_6525_);
v___y_6508_ = v___y_6518_;
v___y_6509_ = v___y_6521_;
v___y_6510_ = v___y_6520_;
v___y_6511_ = v___x_6526_;
goto v___jp_6507_;
}
else
{
uint64_t v___x_6527_; 
v___x_6527_ = lean_uint32_to_uint64(v___y_6519_);
v___y_6508_ = v___y_6518_;
v___y_6509_ = v___y_6521_;
v___y_6510_ = v___y_6520_;
v___y_6511_ = v___x_6527_;
goto v___jp_6507_;
}
}
v___jp_6528_:
{
uint32_t v___x_6530_; uint32_t v_xFraction_6531_; uint32_t v_yFraction_6532_; uint32_t v___x_6533_; uint8_t v___x_6534_; 
v___x_6530_ = 8388607;
v_xFraction_6531_ = lean_uint32_land(v_x_5801_, v___x_6530_);
v_yFraction_6532_ = lean_uint32_land(v_y_5802_, v___x_6530_);
v___x_6533_ = 0;
v___x_6534_ = lean_uint32_dec_eq(v_ex_6424_, v___x_6533_);
if (v___x_6534_ == 0)
{
uint64_t v___x_6535_; uint64_t v___x_6536_; uint64_t v___x_6537_; 
v___x_6535_ = lean_uint32_to_uint64(v_xFraction_6531_);
v___x_6536_ = 8388608ULL;
v___x_6537_ = lean_uint64_lor(v___x_6535_, v___x_6536_);
v___y_6518_ = v___x_6530_;
v___y_6519_ = v_yFraction_6532_;
v___y_6520_ = v___y_6529_;
v___y_6521_ = v___x_6537_;
goto v___jp_6517_;
}
else
{
uint64_t v___x_6538_; 
v___x_6538_ = lean_uint32_to_uint64(v_xFraction_6531_);
v___y_6518_ = v___x_6530_;
v___y_6519_ = v_yFraction_6532_;
v___y_6520_ = v___y_6529_;
v___y_6521_ = v___x_6538_;
goto v___jp_6517_;
}
}
v___jp_6542_:
{
if (v___y_6544_ == 0)
{
v___y_6529_ = v___x_6541_;
goto v___jp_6528_;
}
else
{
v___y_6529_ = v___y_6543_;
goto v___jp_6528_;
}
}
v___jp_6545_:
{
if (v___y_6547_ == 0)
{
if (v___y_6548_ == 0)
{
v___y_6543_ = v___y_6546_;
v___y_6544_ = v___x_6541_;
goto v___jp_6542_;
}
else
{
v___y_6529_ = v___x_6541_;
goto v___jp_6528_;
}
}
else
{
v___y_6543_ = v___y_6546_;
v___y_6544_ = v___y_6548_;
goto v___jp_6542_;
}
}
v___jp_6549_:
{
uint32_t v___x_6552_; uint32_t v___x_6553_; uint32_t v___x_6554_; uint8_t v___x_6555_; 
v___x_6552_ = 2147483648;
v___x_6553_ = lean_uint32_land(v_y_5802_, v___x_6552_);
v___x_6554_ = 0;
v___x_6555_ = lean_uint32_dec_eq(v___x_6553_, v___x_6554_);
if (v___x_6555_ == 0)
{
v___y_6546_ = v___y_6550_;
v___y_6547_ = v___y_6551_;
v___y_6548_ = v___x_6541_;
goto v___jp_6545_;
}
else
{
v___y_6546_ = v___y_6550_;
v___y_6547_ = v___y_6551_;
v___y_6548_ = v___y_6550_;
goto v___jp_6545_;
}
}
v___jp_6556_:
{
if (v___y_6557_ == 0)
{
uint32_t v___x_6558_; uint32_t v___x_6559_; uint32_t v___x_6560_; uint8_t v___x_6561_; 
v___x_6558_ = 2147483648;
v___x_6559_ = lean_uint32_land(v_x_5801_, v___x_6558_);
v___x_6560_ = 0;
v___x_6561_ = lean_uint32_dec_eq(v___x_6559_, v___x_6560_);
if (v___x_6561_ == 0)
{
v___y_6550_ = v___y_6557_;
v___y_6551_ = v___x_6541_;
goto v___jp_6549_;
}
else
{
v___y_6550_ = v___y_6557_;
v___y_6551_ = v___y_6557_;
goto v___jp_6549_;
}
}
else
{
lean_object* v___x_6562_; lean_object* v___x_6563_; lean_object* v___x_6564_; lean_object* v___x_6565_; uint32_t v___x_6566_; 
v___x_6562_ = ((lean_object*)(lp_competition_Submission_TunedAdd_Fmt___closed__0));
v___x_6563_ = lean_uint32_to_nat(v_x_5801_);
v___x_6564_ = lean_uint32_to_nat(v_y_5802_);
v___x_6565_ = lp_floatlib_FloatLib_Floats_Formats_BinaryInterchange_Model_MulBackend_word(v___x_6562_, v___x_6563_, v___x_6564_);
v___x_6566_ = lean_uint32_of_nat(v___x_6565_);
lean_dec(v___x_6565_);
return v___x_6566_;
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_mul___boxed(lean_object* v_x_6579_, lean_object* v_y_6580_){
_start:
{
uint32_t v_x_boxed_6581_; uint32_t v_y_boxed_6582_; uint32_t v_res_6583_; lean_object* v_r_6584_; 
v_x_boxed_6581_ = lean_unbox_uint32(v_x_6579_);
lean_dec(v_x_6579_);
v_y_boxed_6582_ = lean_unbox_uint32(v_y_6580_);
lean_dec(v_y_6580_);
v_res_6583_ = lp_competition_Submission_mul(v_x_boxed_6581_, v_y_boxed_6582_);
v_r_6584_ = lean_box_uint32(v_res_6583_);
return v_r_6584_;
}
}
LEAN_EXPORT uint32_t lp_competition___private_Init_Data_Array_Basic_0__Array_foldlMUnsafe_fold___at___00Submission_referenceSum_spec__0(lean_object* v_as_6585_, size_t v_i_6586_, size_t v_stop_6587_, uint32_t v_b_6588_){
_start:
{
uint32_t v___y_6590_; float v___y_6595_; float v___y_6596_; uint8_t v___x_6599_; 
v___x_6599_ = lean_usize_dec_eq(v_i_6586_, v_stop_6587_);
if (v___x_6599_ == 0)
{
lean_object* v___x_6600_; float v___y_6602_; uint8_t v___y_6603_; float v___y_6621_; uint8_t v___y_6632_; uint32_t v___x_6655_; uint32_t v___x_6656_; uint32_t v___x_6657_; uint32_t v___x_6665_; uint8_t v___x_6666_; 
v___x_6600_ = lean_array_uget_borrowed(v_as_6585_, v_i_6586_);
v___x_6655_ = 23;
v___x_6656_ = lean_uint32_shift_right(v_b_6588_, v___x_6655_);
v___x_6657_ = 255;
v___x_6665_ = lean_uint32_land(v___x_6656_, v___x_6657_);
v___x_6666_ = lean_uint32_dec_eq(v___x_6665_, v___x_6657_);
if (v___x_6666_ == 0)
{
goto v___jp_6658_;
}
else
{
if (v___x_6599_ == 0)
{
uint32_t v___x_6667_; uint32_t v___x_6668_; 
v___x_6667_ = lean_unbox_uint32(v___x_6600_);
v___x_6668_ = lp_competition_Submission_TunedAdd_add(v_b_6588_, v___x_6667_);
v___y_6590_ = v___x_6668_;
goto v___jp_6589_;
}
else
{
goto v___jp_6658_;
}
}
v___jp_6601_:
{
if (v___y_6603_ == 0)
{
uint32_t v___x_6604_; float v___x_6605_; 
v___x_6604_ = lean_unbox_uint32(v___x_6600_);
v___x_6605_ = lean_float32_of_bits(v___x_6604_);
v___y_6595_ = v___y_6602_;
v___y_6596_ = v___x_6605_;
goto v___jp_6594_;
}
else
{
uint32_t v___x_6606_; uint32_t v___x_6607_; uint32_t v___x_6608_; uint32_t v___x_6609_; uint32_t v___x_6610_; float v___x_6611_; lean_object* v___x_6612_; uint32_t v___x_6613_; uint32_t v___x_6614_; uint32_t v___x_6615_; lean_object* v___x_6616_; lean_object* v___x_6617_; float v___x_6618_; float v___x_6619_; 
v___x_6606_ = 8388607;
v___x_6607_ = lean_unbox_uint32(v___x_6600_);
v___x_6608_ = lean_uint32_land(v___x_6607_, v___x_6606_);
v___x_6609_ = 8388608;
v___x_6610_ = lean_uint32_lor(v___x_6608_, v___x_6609_);
v___x_6611_ = lean_uint32_to_float32(v___x_6610_);
v___x_6612_ = lp_competition_R2W01b_scaleTable;
v___x_6613_ = 23;
v___x_6614_ = lean_unbox_uint32(v___x_6600_);
v___x_6615_ = lean_uint32_shift_right(v___x_6614_, v___x_6613_);
v___x_6616_ = lean_uint32_to_nat(v___x_6615_);
v___x_6617_ = lean_array_fget_borrowed(v___x_6612_, v___x_6616_);
lean_dec(v___x_6616_);
v___x_6618_ = lean_unbox_float32(v___x_6617_);
v___x_6619_ = lean_float32_mul(v___x_6611_, v___x_6618_);
v___y_6595_ = v___y_6602_;
v___y_6596_ = v___x_6619_;
goto v___jp_6594_;
}
}
v___jp_6620_:
{
uint32_t v___x_6622_; uint32_t v___x_6623_; uint32_t v_a_6624_; uint32_t v___x_6625_; uint32_t v___x_6626_; uint32_t v___x_6627_; uint8_t v___x_6628_; 
v___x_6622_ = 2147483647;
v___x_6623_ = lean_unbox_uint32(v___x_6600_);
v_a_6624_ = lean_uint32_land(v___x_6623_, v___x_6622_);
v___x_6625_ = 201326591;
v___x_6626_ = 1;
v___x_6627_ = lean_uint32_sub(v_a_6624_, v___x_6626_);
v___x_6628_ = lean_uint32_dec_le(v___x_6625_, v___x_6627_);
if (v___x_6628_ == 0)
{
v___y_6602_ = v___y_6621_;
v___y_6603_ = v___x_6628_;
goto v___jp_6601_;
}
else
{
uint32_t v___x_6629_; uint8_t v___x_6630_; 
v___x_6629_ = 2139095040;
v___x_6630_ = lean_uint32_dec_lt(v_a_6624_, v___x_6629_);
v___y_6602_ = v___y_6621_;
v___y_6603_ = v___x_6630_;
goto v___jp_6601_;
}
}
v___jp_6631_:
{
if (v___y_6632_ == 0)
{
float v___x_6633_; 
v___x_6633_ = lean_float32_of_bits(v_b_6588_);
v___y_6621_ = v___x_6633_;
goto v___jp_6620_;
}
else
{
uint32_t v___x_6634_; uint32_t v___x_6635_; uint32_t v___x_6636_; uint32_t v___x_6637_; float v___x_6638_; lean_object* v___x_6639_; uint32_t v___x_6640_; uint32_t v___x_6641_; lean_object* v___x_6642_; lean_object* v___x_6643_; float v___x_6644_; float v___x_6645_; 
v___x_6634_ = 8388607;
v___x_6635_ = lean_uint32_land(v_b_6588_, v___x_6634_);
v___x_6636_ = 8388608;
v___x_6637_ = lean_uint32_lor(v___x_6635_, v___x_6636_);
v___x_6638_ = lean_uint32_to_float32(v___x_6637_);
v___x_6639_ = lp_competition_R2W01b_scaleTable;
v___x_6640_ = 23;
v___x_6641_ = lean_uint32_shift_right(v_b_6588_, v___x_6640_);
v___x_6642_ = lean_uint32_to_nat(v___x_6641_);
v___x_6643_ = lean_array_fget_borrowed(v___x_6639_, v___x_6642_);
lean_dec(v___x_6642_);
v___x_6644_ = lean_unbox_float32(v___x_6643_);
v___x_6645_ = lean_float32_mul(v___x_6638_, v___x_6644_);
v___y_6621_ = v___x_6645_;
goto v___jp_6620_;
}
}
v___jp_6646_:
{
uint32_t v___x_6647_; uint32_t v_a_6648_; uint32_t v___x_6649_; uint32_t v___x_6650_; uint32_t v___x_6651_; uint8_t v___x_6652_; 
v___x_6647_ = 2147483647;
v_a_6648_ = lean_uint32_land(v_b_6588_, v___x_6647_);
v___x_6649_ = 201326591;
v___x_6650_ = 1;
v___x_6651_ = lean_uint32_sub(v_a_6648_, v___x_6650_);
v___x_6652_ = lean_uint32_dec_le(v___x_6649_, v___x_6651_);
if (v___x_6652_ == 0)
{
v___y_6632_ = v___x_6652_;
goto v___jp_6631_;
}
else
{
uint32_t v___x_6653_; uint8_t v___x_6654_; 
v___x_6653_ = 2139095040;
v___x_6654_ = lean_uint32_dec_lt(v_a_6648_, v___x_6653_);
v___y_6632_ = v___x_6654_;
goto v___jp_6631_;
}
}
v___jp_6658_:
{
uint32_t v___x_6659_; uint32_t v___x_6660_; uint32_t v___x_6661_; uint8_t v___x_6662_; 
v___x_6659_ = lean_unbox_uint32(v___x_6600_);
v___x_6660_ = lean_uint32_shift_right(v___x_6659_, v___x_6655_);
v___x_6661_ = lean_uint32_land(v___x_6660_, v___x_6657_);
v___x_6662_ = lean_uint32_dec_eq(v___x_6661_, v___x_6657_);
if (v___x_6662_ == 0)
{
goto v___jp_6646_;
}
else
{
if (v___x_6599_ == 0)
{
uint32_t v___x_6663_; uint32_t v___x_6664_; 
v___x_6663_ = lean_unbox_uint32(v___x_6600_);
v___x_6664_ = lp_competition_Submission_TunedAdd_add(v_b_6588_, v___x_6663_);
v___y_6590_ = v___x_6664_;
goto v___jp_6589_;
}
else
{
goto v___jp_6646_;
}
}
}
}
else
{
return v_b_6588_;
}
v___jp_6589_:
{
size_t v___x_6591_; size_t v___x_6592_; 
v___x_6591_ = ((size_t)1ULL);
v___x_6592_ = lean_usize_add(v_i_6586_, v___x_6591_);
v_i_6586_ = v___x_6592_;
v_b_6588_ = v___y_6590_;
goto _start;
}
v___jp_6594_:
{
float v___x_6597_; uint32_t v___x_6598_; 
v___x_6597_ = lean_float32_add(v___y_6595_, v___y_6596_);
v___x_6598_ = lean_float32_to_bits(v___x_6597_);
v___y_6590_ = v___x_6598_;
goto v___jp_6589_;
}
}
}
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_foldlMUnsafe_fold___at___00Submission_referenceSum_spec__0___boxed(lean_object* v_as_6669_, lean_object* v_i_6670_, lean_object* v_stop_6671_, lean_object* v_b_6672_){
_start:
{
size_t v_i_boxed_6673_; size_t v_stop_boxed_6674_; uint32_t v_b_boxed_6675_; uint32_t v_res_6676_; lean_object* v_r_6677_; 
v_i_boxed_6673_ = lean_unbox_usize(v_i_6670_);
lean_dec(v_i_6670_);
v_stop_boxed_6674_ = lean_unbox_usize(v_stop_6671_);
lean_dec(v_stop_6671_);
v_b_boxed_6675_ = lean_unbox_uint32(v_b_6672_);
lean_dec(v_b_6672_);
v_res_6676_ = lp_competition___private_Init_Data_Array_Basic_0__Array_foldlMUnsafe_fold___at___00Submission_referenceSum_spec__0(v_as_6669_, v_i_boxed_6673_, v_stop_boxed_6674_, v_b_boxed_6675_);
lean_dec_ref(v_as_6669_);
v_r_6677_ = lean_box_uint32(v_res_6676_);
return v_r_6677_;
}
}
static lean_object* _init_lp_competition_Submission_referenceSum___redArg___closed__0(void){
_start:
{
lean_object* v___x_6678_; lean_object* v___x_6679_; lean_object* v___x_6680_; 
v___x_6678_ = lean_unsigned_to_nat(0u);
v___x_6679_ = lean_unsigned_to_nat(32u);
v___x_6680_ = l_BitVec_ofNat(v___x_6679_, v___x_6678_);
return v___x_6680_;
}
}
static uint32_t _init_lp_competition_Submission_referenceSum___redArg___closed__1(void){
_start:
{
lean_object* v___x_6681_; uint32_t v___x_6682_; 
v___x_6681_ = lean_obj_once(&lp_competition_Submission_referenceSum___redArg___closed__0, &lp_competition_Submission_referenceSum___redArg___closed__0_once, _init_lp_competition_Submission_referenceSum___redArg___closed__0);
v___x_6682_ = lean_uint32_of_nat(v___x_6681_);
return v___x_6682_;
}
}
LEAN_EXPORT uint32_t lp_competition_Submission_referenceSum___redArg(lean_object* v_x_6683_){
_start:
{
lean_object* v___x_6684_; uint32_t v___x_6685_; lean_object* v___x_6686_; uint8_t v___x_6687_; 
v___x_6684_ = lean_unsigned_to_nat(0u);
v___x_6685_ = lean_uint32_once(&lp_competition_Submission_referenceSum___redArg___closed__1, &lp_competition_Submission_referenceSum___redArg___closed__1_once, _init_lp_competition_Submission_referenceSum___redArg___closed__1);
v___x_6686_ = lean_array_get_size(v_x_6683_);
v___x_6687_ = lean_nat_dec_lt(v___x_6684_, v___x_6686_);
if (v___x_6687_ == 0)
{
return v___x_6685_;
}
else
{
uint8_t v___x_6688_; 
v___x_6688_ = lean_nat_dec_le(v___x_6686_, v___x_6686_);
if (v___x_6688_ == 0)
{
if (v___x_6687_ == 0)
{
return v___x_6685_;
}
else
{
size_t v___x_6689_; size_t v___x_6690_; uint32_t v___x_6691_; 
v___x_6689_ = ((size_t)0ULL);
v___x_6690_ = lean_usize_of_nat(v___x_6686_);
v___x_6691_ = lp_competition___private_Init_Data_Array_Basic_0__Array_foldlMUnsafe_fold___at___00Submission_referenceSum_spec__0(v_x_6683_, v___x_6689_, v___x_6690_, v___x_6685_);
return v___x_6691_;
}
}
else
{
size_t v___x_6692_; size_t v___x_6693_; uint32_t v___x_6694_; 
v___x_6692_ = ((size_t)0ULL);
v___x_6693_ = lean_usize_of_nat(v___x_6686_);
v___x_6694_ = lp_competition___private_Init_Data_Array_Basic_0__Array_foldlMUnsafe_fold___at___00Submission_referenceSum_spec__0(v_x_6683_, v___x_6692_, v___x_6693_, v___x_6685_);
return v___x_6694_;
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_referenceSum___redArg___boxed(lean_object* v_x_6695_){
_start:
{
uint32_t v_res_6696_; lean_object* v_r_6697_; 
v_res_6696_ = lp_competition_Submission_referenceSum___redArg(v_x_6695_);
lean_dec_ref(v_x_6695_);
v_r_6697_ = lean_box_uint32(v_res_6696_);
return v_r_6697_;
}
}
LEAN_EXPORT uint32_t lp_competition_Submission_referenceSum(lean_object* v_n_6698_, lean_object* v_x_6699_){
_start:
{
uint32_t v___x_6700_; 
v___x_6700_ = lp_competition_Submission_referenceSum___redArg(v_x_6699_);
return v___x_6700_;
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_referenceSum___boxed(lean_object* v_n_6701_, lean_object* v_x_6702_){
_start:
{
uint32_t v_res_6703_; lean_object* v_r_6704_; 
v_res_6703_ = lp_competition_Submission_referenceSum(v_n_6701_, v_x_6702_);
lean_dec_ref(v_x_6702_);
lean_dec(v_n_6701_);
v_r_6704_ = lean_box_uint32(v_res_6703_);
return v_r_6704_;
}
}
LEAN_EXPORT uint32_t lp_competition_Fin_foldl_loop___at___00Submission_referenceBmm_spec__0(lean_object* v_A_6705_, lean_object* v_fst_6706_, lean_object* v_m_6707_, lean_object* v_fst_6708_, lean_object* v_n_6709_, lean_object* v_B_6710_, lean_object* v_p_6711_, lean_object* v_snd_6712_, lean_object* v_n_6713_, uint32_t v_x_6714_, lean_object* v_i_6715_){
_start:
{
uint32_t v___y_6717_; float v___y_6722_; float v___y_6723_; uint32_t v___y_6727_; float v___y_6728_; uint8_t v___y_6729_; uint32_t v___y_6744_; float v___y_6745_; uint32_t v___y_6755_; uint8_t v___y_6756_; uint32_t v___y_6771_; uint8_t v___x_6773_; uint32_t v___y_6775_; uint32_t v___y_6794_; uint32_t v___y_6798_; uint32_t v___y_6802_; uint32_t v___y_6806_; uint32_t v___y_6807_; uint32_t v___y_6808_; uint32_t v___y_6812_; uint8_t v___y_6813_; uint64_t v___y_6814_; uint64_t v___y_6815_; uint32_t v___y_6827_; uint32_t v___y_6828_; uint32_t v___y_6829_; uint32_t v___y_6830_; uint32_t v___y_6831_; uint32_t v___y_6832_; uint32_t v___y_6839_; uint32_t v___y_6840_; uint8_t v___y_6841_; uint32_t v___y_6842_; uint32_t v___y_6843_; uint32_t v___y_6844_; uint32_t v___y_6848_; uint8_t v___y_6849_; uint32_t v___y_6850_; uint64_t v___y_6851_; uint32_t v___y_6852_; uint64_t v___y_6853_; uint64_t v___y_6854_; uint32_t v___y_6864_; uint8_t v___y_6865_; uint32_t v___y_6866_; uint64_t v___y_6867_; uint8_t v___y_6868_; uint32_t v___y_6869_; uint64_t v___y_6870_; uint64_t v___y_6871_; uint32_t v___y_6878_; uint8_t v___y_6879_; uint32_t v___y_6880_; uint64_t v___y_6881_; uint32_t v___y_6882_; uint64_t v___y_6883_; uint64_t v___y_6884_; uint32_t v___y_6890_; uint64_t v___y_6891_; uint8_t v___y_6892_; uint32_t v___y_6893_; uint64_t v___y_6894_; uint32_t v___y_6895_; uint64_t v___y_6896_; uint64_t v___y_6897_; uint32_t v___y_6952_; uint64_t v___y_6953_; uint64_t v___y_6954_; uint8_t v___y_6955_; uint32_t v___y_6956_; uint64_t v___y_6957_; uint32_t v___y_6958_; uint64_t v___y_6959_; uint64_t v___y_6960_; uint32_t v___y_6966_; uint64_t v___y_6967_; uint64_t v___y_6968_; uint64_t v___y_6969_; uint8_t v___y_6970_; uint32_t v___y_6971_; uint64_t v___y_6972_; uint64_t v___y_6973_; uint32_t v___y_6974_; uint64_t v___y_6975_; uint64_t v___y_6976_; uint32_t v___y_6981_; uint64_t v___y_6982_; uint64_t v___y_6983_; uint8_t v___y_6984_; uint32_t v___y_6985_; uint64_t v___y_6986_; uint32_t v___y_6987_; uint64_t v___y_6988_; uint64_t v___y_6989_; uint32_t v___y_6994_; uint64_t v___y_6995_; uint64_t v___y_6996_; uint64_t v___y_6997_; uint8_t v___y_6998_; uint32_t v___y_6999_; uint64_t v___y_7000_; uint32_t v___y_7001_; uint64_t v___y_7002_; uint64_t v___y_7003_; uint64_t v___y_7004_; uint32_t v___y_7009_; uint64_t v___y_7010_; uint8_t v___y_7011_; uint32_t v___y_7012_; uint64_t v___y_7013_; uint32_t v___y_7014_; uint64_t v___y_7015_; uint64_t v___y_7016_; uint64_t v___y_7017_; uint32_t v___y_7022_; uint64_t v___y_7023_; uint64_t v___y_7024_; uint8_t v___y_7025_; uint32_t v___y_7026_; uint64_t v___y_7027_; uint64_t v___y_7028_; uint32_t v___y_7029_; uint64_t v___y_7030_; uint64_t v___y_7031_; uint64_t v___y_7032_; uint32_t v___y_7037_; uint64_t v___y_7038_; uint8_t v___y_7039_; uint32_t v___y_7040_; uint64_t v___y_7041_; uint64_t v___y_7042_; uint32_t v___y_7043_; uint64_t v___y_7044_; uint64_t v___y_7045_; uint32_t v___y_7050_; uint64_t v___y_7051_; uint64_t v___y_7052_; uint64_t v___y_7053_; uint8_t v___y_7054_; uint32_t v___y_7055_; uint64_t v___y_7056_; uint32_t v___y_7057_; uint64_t v___y_7058_; uint64_t v___y_7059_; uint64_t v___y_7060_; uint32_t v___y_7065_; uint64_t v___y_7066_; uint64_t v___y_7067_; uint8_t v___y_7068_; uint32_t v___y_7069_; uint64_t v___y_7070_; uint32_t v___y_7071_; uint64_t v___y_7072_; uint64_t v___y_7073_; uint32_t v___y_7078_; uint64_t v___y_7079_; uint8_t v___y_7080_; uint32_t v___y_7081_; uint64_t v___y_7082_; uint32_t v___y_7083_; uint64_t v___y_7084_; uint64_t v___y_7085_; uint64_t v___y_7086_; uint32_t v___y_7090_; uint64_t v___y_7091_; uint8_t v___y_7092_; uint32_t v___y_7093_; uint64_t v___y_7094_; uint32_t v___y_7095_; uint32_t v___y_7104_; uint32_t v___y_7105_; uint32_t v___y_7106_; uint32_t v___y_7110_; uint64_t v___y_7111_; uint8_t v___y_7112_; uint64_t v___y_7113_; uint32_t v___y_7125_; uint64_t v___y_7126_; uint64_t v___y_7127_; uint8_t v___y_7128_; uint32_t v___y_7129_; uint64_t v___y_7130_; uint32_t v___y_7131_; uint64_t v___y_7132_; uint32_t v___y_7166_; uint64_t v___y_7167_; uint8_t v___y_7168_; uint32_t v___y_7169_; uint32_t v___y_7170_; uint64_t v___y_7171_; uint32_t v___y_7172_; uint64_t v___y_7173_; uint32_t v___y_7180_; uint64_t v___y_7181_; uint8_t v___y_7182_; uint32_t v___y_7183_; uint32_t v___y_7184_; uint32_t v___y_7185_; uint32_t v___y_7186_; uint64_t v___y_7187_; uint32_t v___y_7194_; uint8_t v___y_7195_; uint32_t v___y_7196_; uint32_t v___y_7197_; uint32_t v___y_7198_; uint32_t v___y_7199_; uint32_t v___y_7200_; uint64_t v___y_7201_; uint32_t v___y_7209_; uint32_t v___y_7210_; uint32_t v___y_7211_; uint32_t v___y_7212_; uint32_t v___y_7213_; uint32_t v___y_7214_; uint8_t v___y_7215_; uint32_t v___y_7226_; uint32_t v___y_7227_; uint32_t v___y_7228_; uint32_t v___y_7232_; uint8_t v___y_7233_; uint64_t v___y_7234_; uint64_t v___y_7235_; uint32_t v___y_7247_; uint32_t v___y_7248_; uint32_t v___y_7249_; uint32_t v___y_7250_; uint32_t v___y_7251_; uint32_t v___y_7252_; uint32_t v___y_7259_; uint32_t v___y_7260_; uint8_t v___y_7261_; uint32_t v___y_7262_; uint32_t v___y_7263_; uint32_t v___y_7264_; uint32_t v___y_7268_; uint32_t v___y_7269_; uint8_t v___y_7270_; uint64_t v___y_7271_; uint32_t v___y_7272_; uint64_t v___y_7273_; uint64_t v___y_7274_; uint32_t v___y_7284_; uint32_t v___y_7285_; uint64_t v___y_7286_; uint8_t v___y_7287_; uint8_t v___y_7288_; uint32_t v___y_7289_; uint64_t v___y_7290_; uint64_t v___y_7291_; uint32_t v___y_7298_; uint32_t v___y_7299_; uint8_t v___y_7300_; uint64_t v___y_7301_; uint32_t v___y_7302_; uint64_t v___y_7303_; uint64_t v___y_7304_; uint64_t v___y_7310_; uint32_t v___y_7311_; uint32_t v___y_7312_; uint8_t v___y_7313_; uint32_t v___y_7314_; uint64_t v___y_7315_; uint64_t v___y_7316_; uint64_t v___y_7317_; uint64_t v___y_7372_; uint64_t v___y_7373_; uint32_t v___y_7374_; uint32_t v___y_7375_; uint8_t v___y_7376_; uint32_t v___y_7377_; uint64_t v___y_7378_; uint64_t v___y_7379_; uint64_t v___y_7380_; uint64_t v___y_7386_; uint64_t v___y_7387_; uint64_t v___y_7388_; uint32_t v___y_7389_; uint32_t v___y_7390_; uint8_t v___y_7391_; uint64_t v___y_7392_; uint32_t v___y_7393_; uint64_t v___y_7394_; uint64_t v___y_7395_; uint64_t v___y_7396_; uint64_t v___y_7401_; uint64_t v___y_7402_; uint32_t v___y_7403_; uint32_t v___y_7404_; uint8_t v___y_7405_; uint32_t v___y_7406_; uint64_t v___y_7407_; uint64_t v___y_7408_; uint64_t v___y_7409_; uint64_t v___y_7414_; uint64_t v___y_7415_; uint32_t v___y_7416_; uint32_t v___y_7417_; uint8_t v___y_7418_; uint64_t v___y_7419_; uint64_t v___y_7420_; uint32_t v___y_7421_; uint64_t v___y_7422_; uint64_t v___y_7423_; uint64_t v___y_7424_; uint64_t v___y_7429_; uint32_t v___y_7430_; uint32_t v___y_7431_; uint8_t v___y_7432_; uint32_t v___y_7433_; uint64_t v___y_7434_; uint64_t v___y_7435_; uint64_t v___y_7436_; uint64_t v___y_7437_; uint64_t v___y_7442_; uint32_t v___y_7443_; uint64_t v___y_7444_; uint64_t v___y_7445_; uint32_t v___y_7446_; uint8_t v___y_7447_; uint32_t v___y_7448_; uint64_t v___y_7449_; uint64_t v___y_7450_; uint64_t v___y_7451_; uint64_t v___y_7452_; uint64_t v___y_7457_; uint32_t v___y_7458_; uint64_t v___y_7459_; uint32_t v___y_7460_; uint8_t v___y_7461_; uint32_t v___y_7462_; uint64_t v___y_7463_; uint64_t v___y_7464_; uint64_t v___y_7465_; uint64_t v___y_7470_; uint64_t v___y_7471_; uint32_t v___y_7472_; uint32_t v___y_7473_; uint8_t v___y_7474_; uint32_t v___y_7475_; uint64_t v___y_7476_; uint64_t v___y_7477_; uint64_t v___y_7478_; uint64_t v___y_7479_; uint64_t v___y_7480_; uint64_t v___y_7485_; uint32_t v___y_7486_; uint32_t v___y_7487_; uint8_t v___y_7488_; uint32_t v___y_7489_; uint64_t v___y_7490_; uint64_t v___y_7491_; uint64_t v___y_7492_; uint64_t v___y_7493_; uint64_t v___y_7498_; uint64_t v___y_7499_; uint32_t v___y_7500_; uint32_t v___y_7501_; uint8_t v___y_7502_; uint32_t v___y_7503_; uint64_t v___y_7504_; uint64_t v___y_7505_; uint64_t v___y_7506_; uint64_t v___y_7510_; uint32_t v___y_7511_; uint32_t v___y_7512_; uint8_t v___y_7513_; uint32_t v___y_7514_; uint64_t v___y_7515_; uint64_t v___y_7516_; uint32_t v___y_7521_; uint32_t v___y_7522_; uint8_t v___y_7523_; uint64_t v___y_7524_; uint32_t v___y_7525_; uint64_t v___y_7526_; uint64_t v___y_7527_; uint64_t v___y_7528_; uint32_t v___y_7544_; uint32_t v___y_7545_; uint32_t v___y_7546_; uint8_t v___y_7547_; uint32_t v___y_7548_; uint64_t v___y_7549_; uint64_t v___y_7550_; uint64_t v___y_7551_; uint32_t v___y_7558_; uint32_t v___y_7559_; uint32_t v___y_7560_; uint8_t v___y_7561_; uint32_t v___y_7562_; uint32_t v___y_7563_; uint64_t v___y_7564_; uint64_t v___y_7565_; uint32_t v___y_7572_; uint32_t v___y_7573_; uint32_t v___y_7574_; uint8_t v___y_7575_; uint32_t v___y_7576_; uint32_t v___y_7577_; uint32_t v___y_7578_; uint64_t v___y_7579_; uint32_t v___y_7587_; uint32_t v___y_7588_; uint32_t v___y_7589_; uint32_t v___y_7590_; uint32_t v___y_7591_; uint32_t v___y_7592_; uint8_t v___y_7593_; uint32_t v___y_7604_; uint32_t v___y_7605_; uint32_t v___y_7606_; uint32_t v___y_7607_; uint8_t v___y_7608_; uint32_t v___y_7609_; uint32_t v___y_7610_; uint8_t v___y_7611_; uint32_t v___y_7613_; uint32_t v___y_7614_; uint32_t v___y_7615_; uint32_t v___y_7616_; uint8_t v___y_7617_; uint8_t v___y_7618_; uint32_t v___y_7619_; uint32_t v___y_7620_; uint8_t v___y_7621_; uint32_t v___y_7623_; uint32_t v___y_7624_; uint32_t v___y_7625_; uint32_t v___y_7626_; uint8_t v___y_7627_; uint32_t v___y_7628_; uint32_t v___y_7629_; uint8_t v___y_7630_; uint32_t v___y_7636_; uint32_t v___y_7637_; uint32_t v___y_7638_; uint32_t v___y_7639_; uint32_t v___y_7640_; uint32_t v___y_7641_; uint8_t v___y_7642_; uint32_t v___y_7652_; uint32_t v___y_7653_; uint32_t v___y_7654_; uint32_t v___y_7655_; uint32_t v___y_7656_; uint32_t v___y_7657_; uint8_t v___y_7658_; uint8_t v___y_7659_; uint32_t v___y_7661_; uint32_t v___y_7662_; uint8_t v___y_7663_; uint32_t v___y_7664_; uint32_t v___y_7665_; uint32_t v___y_7666_; uint32_t v___y_7667_; uint8_t v___y_7668_; uint8_t v___y_7669_; uint32_t v___y_7671_; uint32_t v___y_7672_; uint32_t v___y_7673_; uint32_t v___y_7674_; uint32_t v___y_7675_; uint32_t v___y_7676_; uint8_t v___y_7677_; uint8_t v___y_7678_; uint32_t v___y_7684_; uint32_t v___y_7685_; uint32_t v___y_7686_; uint32_t v___y_7687_; uint32_t v___y_7688_; uint32_t v___y_7689_; uint8_t v___y_7690_; uint32_t v___y_7700_; uint32_t v___y_7701_; 
v___x_6773_ = lean_nat_dec_lt(v_i_6715_, v_n_6713_);
if (v___x_6773_ == 0)
{
lean_dec(v_i_6715_);
return v_x_6714_;
}
else
{
lean_object* v___x_7723_; lean_object* v___x_7724_; lean_object* v___x_7725_; lean_object* v___x_7726_; uint32_t v___x_7727_; uint32_t v___y_7729_; lean_object* v___x_7738_; uint8_t v___x_7739_; 
v___x_7723_ = lean_nat_mul(v_fst_6706_, v_m_6707_);
v___x_7724_ = lean_nat_add(v___x_7723_, v_fst_6708_);
lean_dec(v___x_7723_);
v___x_7725_ = lean_nat_mul(v___x_7724_, v_n_6709_);
lean_dec(v___x_7724_);
v___x_7726_ = lean_nat_add(v___x_7725_, v_i_6715_);
lean_dec(v___x_7725_);
v___x_7727_ = lean_uint32_once(&lp_competition_Submission_referenceSum___redArg___closed__1, &lp_competition_Submission_referenceSum___redArg___closed__1_once, _init_lp_competition_Submission_referenceSum___redArg___closed__1);
v___x_7738_ = lean_array_get_size(v_A_6705_);
v___x_7739_ = lean_nat_dec_lt(v___x_7726_, v___x_7738_);
if (v___x_7739_ == 0)
{
lean_dec(v___x_7726_);
v___y_7729_ = v___x_7727_;
goto v___jp_7728_;
}
else
{
lean_object* v___x_7740_; uint32_t v___x_7741_; 
v___x_7740_ = lean_array_fget_borrowed(v_A_6705_, v___x_7726_);
lean_dec(v___x_7726_);
v___x_7741_ = lean_unbox_uint32(v___x_7740_);
v___y_7729_ = v___x_7741_;
goto v___jp_7728_;
}
v___jp_7728_:
{
lean_object* v___x_7730_; lean_object* v___x_7731_; lean_object* v___x_7732_; lean_object* v___x_7733_; lean_object* v___x_7734_; uint8_t v___x_7735_; 
v___x_7730_ = lean_nat_mul(v_fst_6706_, v_n_6709_);
v___x_7731_ = lean_nat_add(v___x_7730_, v_i_6715_);
lean_dec(v___x_7730_);
v___x_7732_ = lean_nat_mul(v___x_7731_, v_p_6711_);
lean_dec(v___x_7731_);
v___x_7733_ = lean_nat_add(v___x_7732_, v_snd_6712_);
lean_dec(v___x_7732_);
v___x_7734_ = lean_array_get_size(v_B_6710_);
v___x_7735_ = lean_nat_dec_lt(v___x_7733_, v___x_7734_);
if (v___x_7735_ == 0)
{
lean_dec(v___x_7733_);
v___y_7700_ = v___y_7729_;
v___y_7701_ = v___x_7727_;
goto v___jp_7699_;
}
else
{
lean_object* v___x_7736_; uint32_t v___x_7737_; 
v___x_7736_ = lean_array_fget_borrowed(v_B_6710_, v___x_7733_);
lean_dec(v___x_7733_);
v___x_7737_ = lean_unbox_uint32(v___x_7736_);
v___y_7700_ = v___y_7729_;
v___y_7701_ = v___x_7737_;
goto v___jp_7699_;
}
}
}
v___jp_6716_:
{
lean_object* v___x_6718_; lean_object* v___x_6719_; 
v___x_6718_ = lean_unsigned_to_nat(1u);
v___x_6719_ = lean_nat_add(v_i_6715_, v___x_6718_);
lean_dec(v_i_6715_);
v_x_6714_ = v___y_6717_;
v_i_6715_ = v___x_6719_;
goto _start;
}
v___jp_6721_:
{
float v___x_6724_; uint32_t v___x_6725_; 
v___x_6724_ = lean_float32_add(v___y_6722_, v___y_6723_);
v___x_6725_ = lean_float32_to_bits(v___x_6724_);
v___y_6717_ = v___x_6725_;
goto v___jp_6716_;
}
v___jp_6726_:
{
if (v___y_6729_ == 0)
{
float v___x_6730_; 
v___x_6730_ = lean_float32_of_bits(v___y_6727_);
v___y_6722_ = v___y_6728_;
v___y_6723_ = v___x_6730_;
goto v___jp_6721_;
}
else
{
uint32_t v___x_6731_; uint32_t v___x_6732_; uint32_t v___x_6733_; uint32_t v___x_6734_; float v___x_6735_; lean_object* v___x_6736_; uint32_t v___x_6737_; uint32_t v___x_6738_; lean_object* v___x_6739_; lean_object* v___x_6740_; float v___x_6741_; float v___x_6742_; 
v___x_6731_ = 8388607;
v___x_6732_ = lean_uint32_land(v___y_6727_, v___x_6731_);
v___x_6733_ = 8388608;
v___x_6734_ = lean_uint32_lor(v___x_6732_, v___x_6733_);
v___x_6735_ = lean_uint32_to_float32(v___x_6734_);
v___x_6736_ = lp_competition_R2W01b_scaleTable;
v___x_6737_ = 23;
v___x_6738_ = lean_uint32_shift_right(v___y_6727_, v___x_6737_);
v___x_6739_ = lean_uint32_to_nat(v___x_6738_);
v___x_6740_ = lean_array_fget_borrowed(v___x_6736_, v___x_6739_);
lean_dec(v___x_6739_);
v___x_6741_ = lean_unbox_float32(v___x_6740_);
v___x_6742_ = lean_float32_mul(v___x_6735_, v___x_6741_);
v___y_6722_ = v___y_6728_;
v___y_6723_ = v___x_6742_;
goto v___jp_6721_;
}
}
v___jp_6743_:
{
uint32_t v___x_6746_; uint32_t v_a_6747_; uint32_t v___x_6748_; uint32_t v___x_6749_; uint32_t v___x_6750_; uint8_t v___x_6751_; 
v___x_6746_ = 2147483647;
v_a_6747_ = lean_uint32_land(v___y_6744_, v___x_6746_);
v___x_6748_ = 201326591;
v___x_6749_ = 1;
v___x_6750_ = lean_uint32_sub(v_a_6747_, v___x_6749_);
v___x_6751_ = lean_uint32_dec_le(v___x_6748_, v___x_6750_);
if (v___x_6751_ == 0)
{
v___y_6727_ = v___y_6744_;
v___y_6728_ = v___y_6745_;
v___y_6729_ = v___x_6751_;
goto v___jp_6726_;
}
else
{
uint32_t v___x_6752_; uint8_t v___x_6753_; 
v___x_6752_ = 2139095040;
v___x_6753_ = lean_uint32_dec_lt(v_a_6747_, v___x_6752_);
v___y_6727_ = v___y_6744_;
v___y_6728_ = v___y_6745_;
v___y_6729_ = v___x_6753_;
goto v___jp_6726_;
}
}
v___jp_6754_:
{
if (v___y_6756_ == 0)
{
float v___x_6757_; 
v___x_6757_ = lean_float32_of_bits(v_x_6714_);
v___y_6744_ = v___y_6755_;
v___y_6745_ = v___x_6757_;
goto v___jp_6743_;
}
else
{
uint32_t v___x_6758_; uint32_t v___x_6759_; uint32_t v___x_6760_; uint32_t v___x_6761_; float v___x_6762_; lean_object* v___x_6763_; uint32_t v___x_6764_; uint32_t v___x_6765_; lean_object* v___x_6766_; lean_object* v___x_6767_; float v___x_6768_; float v___x_6769_; 
v___x_6758_ = 8388607;
v___x_6759_ = lean_uint32_land(v_x_6714_, v___x_6758_);
v___x_6760_ = 8388608;
v___x_6761_ = lean_uint32_lor(v___x_6759_, v___x_6760_);
v___x_6762_ = lean_uint32_to_float32(v___x_6761_);
v___x_6763_ = lp_competition_R2W01b_scaleTable;
v___x_6764_ = 23;
v___x_6765_ = lean_uint32_shift_right(v_x_6714_, v___x_6764_);
v___x_6766_ = lean_uint32_to_nat(v___x_6765_);
v___x_6767_ = lean_array_fget_borrowed(v___x_6763_, v___x_6766_);
lean_dec(v___x_6766_);
v___x_6768_ = lean_unbox_float32(v___x_6767_);
v___x_6769_ = lean_float32_mul(v___x_6762_, v___x_6768_);
v___y_6744_ = v___y_6755_;
v___y_6745_ = v___x_6769_;
goto v___jp_6743_;
}
}
v___jp_6770_:
{
uint32_t v___x_6772_; 
v___x_6772_ = lp_competition_Submission_TunedAdd_add(v_x_6714_, v___y_6771_);
v___y_6717_ = v___x_6772_;
goto v___jp_6716_;
}
v___jp_6774_:
{
uint32_t v___x_6776_; uint32_t v___x_6777_; uint32_t v___x_6778_; uint32_t v___x_6779_; uint8_t v___x_6780_; 
v___x_6776_ = 23;
v___x_6777_ = lean_uint32_shift_right(v_x_6714_, v___x_6776_);
v___x_6778_ = 255;
v___x_6779_ = lean_uint32_land(v___x_6777_, v___x_6778_);
v___x_6780_ = lean_uint32_dec_eq(v___x_6779_, v___x_6778_);
if (v___x_6780_ == 0)
{
if (v___x_6773_ == 0)
{
v___y_6771_ = v___y_6775_;
goto v___jp_6770_;
}
else
{
uint32_t v___x_6781_; uint32_t v___x_6782_; uint8_t v___x_6783_; 
v___x_6781_ = lean_uint32_shift_right(v___y_6775_, v___x_6776_);
v___x_6782_ = lean_uint32_land(v___x_6781_, v___x_6778_);
v___x_6783_ = lean_uint32_dec_eq(v___x_6782_, v___x_6778_);
if (v___x_6783_ == 0)
{
uint32_t v___x_6784_; uint32_t v_a_6785_; uint32_t v___x_6786_; uint32_t v___x_6787_; uint32_t v___x_6788_; uint8_t v___x_6789_; 
v___x_6784_ = 2147483647;
v_a_6785_ = lean_uint32_land(v_x_6714_, v___x_6784_);
v___x_6786_ = 201326591;
v___x_6787_ = 1;
v___x_6788_ = lean_uint32_sub(v_a_6785_, v___x_6787_);
v___x_6789_ = lean_uint32_dec_le(v___x_6786_, v___x_6788_);
if (v___x_6789_ == 0)
{
v___y_6755_ = v___y_6775_;
v___y_6756_ = v___x_6789_;
goto v___jp_6754_;
}
else
{
uint32_t v___x_6790_; uint8_t v___x_6791_; 
v___x_6790_ = 2139095040;
v___x_6791_ = lean_uint32_dec_lt(v_a_6785_, v___x_6790_);
v___y_6755_ = v___y_6775_;
v___y_6756_ = v___x_6791_;
goto v___jp_6754_;
}
}
else
{
uint32_t v___x_6792_; 
v___x_6792_ = lp_competition_Submission_TunedAdd_add(v_x_6714_, v___y_6775_);
v___y_6717_ = v___x_6792_;
goto v___jp_6716_;
}
}
}
else
{
v___y_6771_ = v___y_6775_;
goto v___jp_6770_;
}
}
v___jp_6793_:
{
uint32_t v___x_6795_; uint32_t v___x_6796_; 
v___x_6795_ = 8388608;
v___x_6796_ = lean_uint32_lor(v___y_6794_, v___x_6795_);
v___y_6775_ = v___x_6796_;
goto v___jp_6774_;
}
v___jp_6797_:
{
uint32_t v___x_6799_; uint32_t v___x_6800_; 
v___x_6799_ = 8388608;
v___x_6800_ = lean_uint32_lor(v___y_6798_, v___x_6799_);
v___y_6775_ = v___x_6800_;
goto v___jp_6774_;
}
v___jp_6801_:
{
uint32_t v___x_6803_; uint32_t v___x_6804_; 
v___x_6803_ = 8388608;
v___x_6804_ = lean_uint32_lor(v___y_6802_, v___x_6803_);
v___y_6775_ = v___x_6804_;
goto v___jp_6774_;
}
v___jp_6805_:
{
uint32_t v___x_6809_; uint32_t v___x_6810_; 
v___x_6809_ = lean_uint32_land(v___y_6807_, v___y_6806_);
v___x_6810_ = lean_uint32_lor(v___y_6808_, v___x_6809_);
v___y_6775_ = v___x_6810_;
goto v___jp_6774_;
}
v___jp_6811_:
{
uint8_t v___x_6816_; 
v___x_6816_ = lean_uint64_dec_eq(v___y_6815_, v___y_6814_);
if (v___x_6816_ == 0)
{
uint64_t v___x_6817_; uint8_t v___x_6818_; 
v___x_6817_ = 8388608ULL;
v___x_6818_ = lean_uint64_dec_eq(v___y_6815_, v___x_6817_);
if (v___x_6818_ == 0)
{
uint32_t v___x_6819_; 
v___x_6819_ = lean_uint64_to_uint32(v___y_6815_);
if (v___y_6813_ == 0)
{
uint32_t v___x_6820_; 
v___x_6820_ = 0;
v___y_6806_ = v___y_6812_;
v___y_6807_ = v___x_6819_;
v___y_6808_ = v___x_6820_;
goto v___jp_6805_;
}
else
{
uint32_t v___x_6821_; 
v___x_6821_ = 2147483648;
v___y_6806_ = v___y_6812_;
v___y_6807_ = v___x_6819_;
v___y_6808_ = v___x_6821_;
goto v___jp_6805_;
}
}
else
{
if (v___y_6813_ == 0)
{
uint32_t v___x_6822_; 
v___x_6822_ = 0;
v___y_6794_ = v___x_6822_;
goto v___jp_6793_;
}
else
{
uint32_t v___x_6823_; 
v___x_6823_ = 2147483648;
v___y_6794_ = v___x_6823_;
goto v___jp_6793_;
}
}
}
else
{
if (v___y_6813_ == 0)
{
uint32_t v___x_6824_; 
v___x_6824_ = 0;
v___y_6775_ = v___x_6824_;
goto v___jp_6774_;
}
else
{
uint32_t v___x_6825_; 
v___x_6825_ = 2147483648;
v___y_6775_ = v___x_6825_;
goto v___jp_6774_;
}
}
}
v___jp_6826_:
{
uint32_t v___x_6833_; uint32_t v___x_6834_; uint32_t v___x_6835_; uint32_t v___x_6836_; uint32_t v___x_6837_; 
v___x_6833_ = lean_uint32_land(v___y_6829_, v___y_6831_);
v___x_6834_ = lean_uint32_shift_left(v___x_6833_, v___y_6830_);
v___x_6835_ = lean_uint32_lor(v___y_6832_, v___x_6834_);
v___x_6836_ = lean_uint32_land(v___y_6828_, v___y_6827_);
v___x_6837_ = lean_uint32_lor(v___x_6835_, v___x_6836_);
v___y_6775_ = v___x_6837_;
goto v___jp_6774_;
}
v___jp_6838_:
{
if (v___y_6841_ == 0)
{
uint32_t v___x_6845_; 
v___x_6845_ = 0;
v___y_6827_ = v___y_6839_;
v___y_6828_ = v___y_6844_;
v___y_6829_ = v___y_6840_;
v___y_6830_ = v___y_6842_;
v___y_6831_ = v___y_6843_;
v___y_6832_ = v___x_6845_;
goto v___jp_6826_;
}
else
{
uint32_t v___x_6846_; 
v___x_6846_ = 2147483648;
v___y_6827_ = v___y_6839_;
v___y_6828_ = v___y_6844_;
v___y_6829_ = v___y_6840_;
v___y_6830_ = v___y_6842_;
v___y_6831_ = v___y_6843_;
v___y_6832_ = v___x_6846_;
goto v___jp_6826_;
}
}
v___jp_6847_:
{
uint64_t v___x_6855_; uint64_t v_encodedExponent_6856_; uint32_t v___x_6857_; uint64_t v___x_6858_; uint8_t v___x_6859_; 
v___x_6855_ = 171ULL;
v_encodedExponent_6856_ = lean_uint64_sub(v___y_6851_, v___x_6855_);
v___x_6857_ = lean_uint64_to_uint32(v_encodedExponent_6856_);
v___x_6858_ = 8388608ULL;
v___x_6859_ = lean_uint64_dec_lt(v___y_6854_, v___x_6858_);
if (v___x_6859_ == 0)
{
uint64_t v___x_6860_; uint32_t v___x_6861_; 
v___x_6860_ = lean_uint64_sub(v___y_6854_, v___x_6858_);
v___x_6861_ = lean_uint64_to_uint32(v___x_6860_);
v___y_6839_ = v___y_6848_;
v___y_6840_ = v___x_6857_;
v___y_6841_ = v___y_6849_;
v___y_6842_ = v___y_6850_;
v___y_6843_ = v___y_6852_;
v___y_6844_ = v___x_6861_;
goto v___jp_6838_;
}
else
{
uint32_t v___x_6862_; 
v___x_6862_ = lean_uint64_to_uint32(v___y_6853_);
v___y_6839_ = v___y_6848_;
v___y_6840_ = v___x_6857_;
v___y_6841_ = v___y_6849_;
v___y_6842_ = v___y_6850_;
v___y_6843_ = v___y_6852_;
v___y_6844_ = v___x_6862_;
goto v___jp_6838_;
}
}
v___jp_6863_:
{
uint64_t v___x_6872_; uint8_t v___x_6873_; 
v___x_6872_ = 425ULL;
v___x_6873_ = lean_uint64_dec_lt(v___x_6872_, v___y_6871_);
if (v___x_6873_ == 0)
{
if (v___y_6868_ == 0)
{
v___y_6848_ = v___y_6864_;
v___y_6849_ = v___y_6865_;
v___y_6850_ = v___y_6866_;
v___y_6851_ = v___y_6871_;
v___y_6852_ = v___y_6869_;
v___y_6853_ = v___y_6870_;
v___y_6854_ = v___y_6867_;
goto v___jp_6847_;
}
else
{
uint64_t v___x_6874_; 
v___x_6874_ = 8388608ULL;
v___y_6848_ = v___y_6864_;
v___y_6849_ = v___y_6865_;
v___y_6850_ = v___y_6866_;
v___y_6851_ = v___y_6871_;
v___y_6852_ = v___y_6869_;
v___y_6853_ = v___y_6870_;
v___y_6854_ = v___x_6874_;
goto v___jp_6847_;
}
}
else
{
if (v___y_6865_ == 0)
{
uint32_t v___x_6875_; 
v___x_6875_ = 2139095040;
v___y_6775_ = v___x_6875_;
goto v___jp_6774_;
}
else
{
uint32_t v___x_6876_; 
v___x_6876_ = 4286578688;
v___y_6775_ = v___x_6876_;
goto v___jp_6774_;
}
}
}
v___jp_6877_:
{
uint64_t v___x_6885_; uint8_t v_carry_6886_; 
v___x_6885_ = 16777216ULL;
v_carry_6886_ = lean_uint64_dec_eq(v___y_6884_, v___x_6885_);
if (v_carry_6886_ == 0)
{
v___y_6864_ = v___y_6878_;
v___y_6865_ = v___y_6879_;
v___y_6866_ = v___y_6880_;
v___y_6867_ = v___y_6884_;
v___y_6868_ = v_carry_6886_;
v___y_6869_ = v___y_6882_;
v___y_6870_ = v___y_6883_;
v___y_6871_ = v___y_6881_;
goto v___jp_6863_;
}
else
{
uint64_t v___x_6887_; uint64_t v___x_6888_; 
v___x_6887_ = 1ULL;
v___x_6888_ = lean_uint64_add(v___y_6881_, v___x_6887_);
v___y_6864_ = v___y_6878_;
v___y_6865_ = v___y_6879_;
v___y_6866_ = v___y_6880_;
v___y_6867_ = v___y_6884_;
v___y_6868_ = v_carry_6886_;
v___y_6869_ = v___y_6882_;
v___y_6870_ = v___y_6883_;
v___y_6871_ = v___x_6888_;
goto v___jp_6863_;
}
}
v___jp_6889_:
{
uint64_t v_position_6898_; uint64_t v___x_6899_; uint8_t v___x_6900_; 
v_position_6898_ = lean_uint64_add(v___y_6897_, v___y_6894_);
v___x_6899_ = 172ULL;
v___x_6900_ = lean_uint64_dec_lt(v_position_6898_, v___x_6899_);
if (v___x_6900_ == 0)
{
uint64_t v___x_6901_; uint8_t v___x_6902_; 
v___x_6901_ = 23ULL;
v___x_6902_ = lean_uint64_dec_lt(v___y_6897_, v___x_6901_);
if (v___x_6902_ == 0)
{
uint64_t v___x_6903_; uint8_t v___x_6904_; 
v___x_6903_ = lean_uint64_sub(v___y_6897_, v___x_6901_);
v___x_6904_ = lean_uint64_dec_eq(v___x_6903_, v___y_6896_);
if (v___x_6904_ == 0)
{
uint64_t v___x_6905_; uint8_t v___x_6906_; 
v___x_6905_ = 64ULL;
v___x_6906_ = lean_uint64_dec_lt(v___x_6903_, v___x_6905_);
if (v___x_6906_ == 0)
{
uint8_t v___x_6907_; 
v___x_6907_ = lean_uint64_dec_eq(v___x_6903_, v___x_6905_);
if (v___x_6907_ == 0)
{
v___y_6878_ = v___y_6890_;
v___y_6879_ = v___y_6892_;
v___y_6880_ = v___y_6893_;
v___y_6881_ = v_position_6898_;
v___y_6882_ = v___y_6895_;
v___y_6883_ = v___y_6896_;
v___y_6884_ = v___y_6896_;
goto v___jp_6877_;
}
else
{
uint64_t v___x_6908_; uint8_t v___x_6909_; 
v___x_6908_ = 9223372036854775808ULL;
v___x_6909_ = lean_uint64_dec_lt(v___x_6908_, v___y_6891_);
if (v___x_6909_ == 0)
{
v___y_6878_ = v___y_6890_;
v___y_6879_ = v___y_6892_;
v___y_6880_ = v___y_6893_;
v___y_6881_ = v_position_6898_;
v___y_6882_ = v___y_6895_;
v___y_6883_ = v___y_6896_;
v___y_6884_ = v___y_6896_;
goto v___jp_6877_;
}
else
{
uint64_t v___x_6910_; 
v___x_6910_ = 1ULL;
v___y_6878_ = v___y_6890_;
v___y_6879_ = v___y_6892_;
v___y_6880_ = v___y_6893_;
v___y_6881_ = v_position_6898_;
v___y_6882_ = v___y_6895_;
v___y_6883_ = v___y_6896_;
v___y_6884_ = v___x_6910_;
goto v___jp_6877_;
}
}
}
else
{
uint64_t v_quotient_6911_; uint64_t v___x_6912_; uint64_t v___x_6913_; uint64_t v___x_6914_; uint64_t v_remainder_6915_; uint64_t v___x_6916_; uint64_t v_half_6917_; uint8_t v___x_6918_; 
v_quotient_6911_ = lean_uint64_shift_right(v___y_6891_, v___x_6903_);
v___x_6912_ = 1ULL;
v___x_6913_ = lean_uint64_shift_left(v___x_6912_, v___x_6903_);
v___x_6914_ = lean_uint64_sub(v___x_6913_, v___x_6912_);
v_remainder_6915_ = lean_uint64_land(v___y_6891_, v___x_6914_);
v___x_6916_ = lean_uint64_sub(v___x_6903_, v___x_6912_);
v_half_6917_ = lean_uint64_shift_left(v___x_6912_, v___x_6916_);
v___x_6918_ = lean_uint64_dec_lt(v_remainder_6915_, v_half_6917_);
if (v___x_6918_ == 0)
{
uint8_t v___x_6919_; 
v___x_6919_ = lean_uint64_dec_lt(v_half_6917_, v_remainder_6915_);
if (v___x_6919_ == 0)
{
uint64_t v___x_6920_; uint8_t v___x_6921_; 
v___x_6920_ = lean_uint64_land(v_quotient_6911_, v___x_6912_);
v___x_6921_ = lean_uint64_dec_eq(v___x_6920_, v___y_6896_);
if (v___x_6921_ == 0)
{
uint64_t v___x_6922_; 
v___x_6922_ = lean_uint64_add(v_quotient_6911_, v___x_6912_);
v___y_6878_ = v___y_6890_;
v___y_6879_ = v___y_6892_;
v___y_6880_ = v___y_6893_;
v___y_6881_ = v_position_6898_;
v___y_6882_ = v___y_6895_;
v___y_6883_ = v___y_6896_;
v___y_6884_ = v___x_6922_;
goto v___jp_6877_;
}
else
{
v___y_6878_ = v___y_6890_;
v___y_6879_ = v___y_6892_;
v___y_6880_ = v___y_6893_;
v___y_6881_ = v_position_6898_;
v___y_6882_ = v___y_6895_;
v___y_6883_ = v___y_6896_;
v___y_6884_ = v_quotient_6911_;
goto v___jp_6877_;
}
}
else
{
uint64_t v___x_6923_; 
v___x_6923_ = lean_uint64_add(v_quotient_6911_, v___x_6912_);
v___y_6878_ = v___y_6890_;
v___y_6879_ = v___y_6892_;
v___y_6880_ = v___y_6893_;
v___y_6881_ = v_position_6898_;
v___y_6882_ = v___y_6895_;
v___y_6883_ = v___y_6896_;
v___y_6884_ = v___x_6923_;
goto v___jp_6877_;
}
}
else
{
v___y_6878_ = v___y_6890_;
v___y_6879_ = v___y_6892_;
v___y_6880_ = v___y_6893_;
v___y_6881_ = v_position_6898_;
v___y_6882_ = v___y_6895_;
v___y_6883_ = v___y_6896_;
v___y_6884_ = v_quotient_6911_;
goto v___jp_6877_;
}
}
}
else
{
v___y_6878_ = v___y_6890_;
v___y_6879_ = v___y_6892_;
v___y_6880_ = v___y_6893_;
v___y_6881_ = v_position_6898_;
v___y_6882_ = v___y_6895_;
v___y_6883_ = v___y_6896_;
v___y_6884_ = v___y_6891_;
goto v___jp_6877_;
}
}
else
{
uint64_t v___x_6924_; uint64_t v___x_6925_; 
v___x_6924_ = lean_uint64_sub(v___x_6901_, v___y_6897_);
v___x_6925_ = lean_uint64_shift_left(v___y_6891_, v___x_6924_);
v___y_6878_ = v___y_6890_;
v___y_6879_ = v___y_6892_;
v___y_6880_ = v___y_6893_;
v___y_6881_ = v_position_6898_;
v___y_6882_ = v___y_6895_;
v___y_6883_ = v___y_6896_;
v___y_6884_ = v___x_6925_;
goto v___jp_6877_;
}
}
else
{
uint64_t v___x_6926_; uint8_t v___x_6927_; 
v___x_6926_ = 149ULL;
v___x_6927_ = lean_uint64_dec_lt(v___y_6894_, v___x_6926_);
if (v___x_6927_ == 0)
{
uint64_t v___x_6928_; uint64_t v___x_6929_; 
v___x_6928_ = lean_uint64_sub(v___y_6894_, v___x_6926_);
v___x_6929_ = lean_uint64_shift_left(v___y_6891_, v___x_6928_);
v___y_6812_ = v___y_6890_;
v___y_6813_ = v___y_6892_;
v___y_6814_ = v___y_6896_;
v___y_6815_ = v___x_6929_;
goto v___jp_6811_;
}
else
{
uint64_t v___x_6930_; uint8_t v___x_6931_; 
v___x_6930_ = lean_uint64_sub(v___x_6926_, v___y_6894_);
v___x_6931_ = lean_uint64_dec_eq(v___x_6930_, v___y_6896_);
if (v___x_6931_ == 0)
{
uint64_t v___x_6932_; uint8_t v___x_6933_; 
v___x_6932_ = 64ULL;
v___x_6933_ = lean_uint64_dec_lt(v___x_6930_, v___x_6932_);
if (v___x_6933_ == 0)
{
uint8_t v___x_6934_; 
v___x_6934_ = lean_uint64_dec_eq(v___x_6930_, v___x_6932_);
if (v___x_6934_ == 0)
{
v___y_6812_ = v___y_6890_;
v___y_6813_ = v___y_6892_;
v___y_6814_ = v___y_6896_;
v___y_6815_ = v___y_6896_;
goto v___jp_6811_;
}
else
{
uint64_t v___x_6935_; uint8_t v___x_6936_; 
v___x_6935_ = 9223372036854775808ULL;
v___x_6936_ = lean_uint64_dec_lt(v___x_6935_, v___y_6891_);
if (v___x_6936_ == 0)
{
v___y_6812_ = v___y_6890_;
v___y_6813_ = v___y_6892_;
v___y_6814_ = v___y_6896_;
v___y_6815_ = v___y_6896_;
goto v___jp_6811_;
}
else
{
uint64_t v___x_6937_; 
v___x_6937_ = 1ULL;
v___y_6812_ = v___y_6890_;
v___y_6813_ = v___y_6892_;
v___y_6814_ = v___y_6896_;
v___y_6815_ = v___x_6937_;
goto v___jp_6811_;
}
}
}
else
{
uint64_t v_quotient_6938_; uint64_t v___x_6939_; uint64_t v___x_6940_; uint64_t v___x_6941_; uint64_t v_remainder_6942_; uint64_t v___x_6943_; uint64_t v_half_6944_; uint8_t v___x_6945_; 
v_quotient_6938_ = lean_uint64_shift_right(v___y_6891_, v___x_6930_);
v___x_6939_ = 1ULL;
v___x_6940_ = lean_uint64_shift_left(v___x_6939_, v___x_6930_);
v___x_6941_ = lean_uint64_sub(v___x_6940_, v___x_6939_);
v_remainder_6942_ = lean_uint64_land(v___y_6891_, v___x_6941_);
v___x_6943_ = lean_uint64_sub(v___x_6930_, v___x_6939_);
v_half_6944_ = lean_uint64_shift_left(v___x_6939_, v___x_6943_);
v___x_6945_ = lean_uint64_dec_lt(v_remainder_6942_, v_half_6944_);
if (v___x_6945_ == 0)
{
uint8_t v___x_6946_; 
v___x_6946_ = lean_uint64_dec_lt(v_half_6944_, v_remainder_6942_);
if (v___x_6946_ == 0)
{
uint64_t v___x_6947_; uint8_t v___x_6948_; 
v___x_6947_ = lean_uint64_land(v_quotient_6938_, v___x_6939_);
v___x_6948_ = lean_uint64_dec_eq(v___x_6947_, v___y_6896_);
if (v___x_6948_ == 0)
{
uint64_t v___x_6949_; 
v___x_6949_ = lean_uint64_add(v_quotient_6938_, v___x_6939_);
v___y_6812_ = v___y_6890_;
v___y_6813_ = v___y_6892_;
v___y_6814_ = v___y_6896_;
v___y_6815_ = v___x_6949_;
goto v___jp_6811_;
}
else
{
v___y_6812_ = v___y_6890_;
v___y_6813_ = v___y_6892_;
v___y_6814_ = v___y_6896_;
v___y_6815_ = v_quotient_6938_;
goto v___jp_6811_;
}
}
else
{
uint64_t v___x_6950_; 
v___x_6950_ = lean_uint64_add(v_quotient_6938_, v___x_6939_);
v___y_6812_ = v___y_6890_;
v___y_6813_ = v___y_6892_;
v___y_6814_ = v___y_6896_;
v___y_6815_ = v___x_6950_;
goto v___jp_6811_;
}
}
else
{
v___y_6812_ = v___y_6890_;
v___y_6813_ = v___y_6892_;
v___y_6814_ = v___y_6896_;
v___y_6815_ = v_quotient_6938_;
goto v___jp_6811_;
}
}
}
else
{
v___y_6812_ = v___y_6890_;
v___y_6813_ = v___y_6892_;
v___y_6814_ = v___y_6896_;
v___y_6815_ = v___y_6891_;
goto v___jp_6811_;
}
}
}
}
v___jp_6951_:
{
uint64_t v___x_6961_; uint64_t v___x_6962_; uint8_t v___x_6963_; 
v___x_6961_ = 1ULL;
v___x_6962_ = lean_uint64_shift_right(v___y_6953_, v___x_6961_);
v___x_6963_ = lean_uint64_dec_eq(v___x_6962_, v___y_6959_);
if (v___x_6963_ == 0)
{
uint64_t v___x_6964_; 
v___x_6964_ = lean_uint64_add(v___y_6960_, v___x_6961_);
v___y_6890_ = v___y_6952_;
v___y_6891_ = v___y_6954_;
v___y_6892_ = v___y_6955_;
v___y_6893_ = v___y_6956_;
v___y_6894_ = v___y_6957_;
v___y_6895_ = v___y_6958_;
v___y_6896_ = v___y_6959_;
v___y_6897_ = v___x_6964_;
goto v___jp_6889_;
}
else
{
v___y_6890_ = v___y_6952_;
v___y_6891_ = v___y_6954_;
v___y_6892_ = v___y_6955_;
v___y_6893_ = v___y_6956_;
v___y_6894_ = v___y_6957_;
v___y_6895_ = v___y_6958_;
v___y_6896_ = v___y_6959_;
v___y_6897_ = v___y_6960_;
goto v___jp_6889_;
}
}
v___jp_6965_:
{
uint64_t v___x_6977_; uint8_t v___x_6978_; 
v___x_6977_ = lean_uint64_shift_right(v___y_6967_, v___y_6969_);
v___x_6978_ = lean_uint64_dec_eq(v___x_6977_, v___y_6975_);
if (v___x_6978_ == 0)
{
uint64_t v___x_6979_; 
v___x_6979_ = lean_uint64_add(v___y_6972_, v___y_6969_);
v___y_6952_ = v___y_6966_;
v___y_6953_ = v___y_6976_;
v___y_6954_ = v___y_6968_;
v___y_6955_ = v___y_6970_;
v___y_6956_ = v___y_6971_;
v___y_6957_ = v___y_6973_;
v___y_6958_ = v___y_6974_;
v___y_6959_ = v___y_6975_;
v___y_6960_ = v___x_6979_;
goto v___jp_6951_;
}
else
{
v___y_6952_ = v___y_6966_;
v___y_6953_ = v___y_6976_;
v___y_6954_ = v___y_6968_;
v___y_6955_ = v___y_6970_;
v___y_6956_ = v___y_6971_;
v___y_6957_ = v___y_6973_;
v___y_6958_ = v___y_6974_;
v___y_6959_ = v___y_6975_;
v___y_6960_ = v___y_6972_;
goto v___jp_6951_;
}
}
v___jp_6980_:
{
uint64_t v___x_6990_; uint64_t v___x_6991_; uint8_t v___x_6992_; 
v___x_6990_ = 2ULL;
v___x_6991_ = lean_uint64_shift_right(v___y_6982_, v___x_6990_);
v___x_6992_ = lean_uint64_dec_eq(v___x_6991_, v___y_6988_);
if (v___x_6992_ == 0)
{
v___y_6966_ = v___y_6981_;
v___y_6967_ = v___y_6982_;
v___y_6968_ = v___y_6983_;
v___y_6969_ = v___x_6990_;
v___y_6970_ = v___y_6984_;
v___y_6971_ = v___y_6985_;
v___y_6972_ = v___y_6989_;
v___y_6973_ = v___y_6986_;
v___y_6974_ = v___y_6987_;
v___y_6975_ = v___y_6988_;
v___y_6976_ = v___x_6991_;
goto v___jp_6965_;
}
else
{
v___y_6966_ = v___y_6981_;
v___y_6967_ = v___y_6982_;
v___y_6968_ = v___y_6983_;
v___y_6969_ = v___x_6990_;
v___y_6970_ = v___y_6984_;
v___y_6971_ = v___y_6985_;
v___y_6972_ = v___y_6989_;
v___y_6973_ = v___y_6986_;
v___y_6974_ = v___y_6987_;
v___y_6975_ = v___y_6988_;
v___y_6976_ = v___y_6982_;
goto v___jp_6965_;
}
}
v___jp_6993_:
{
uint64_t v___x_7005_; uint8_t v___x_7006_; 
v___x_7005_ = lean_uint64_shift_right(v___y_7002_, v___y_6996_);
v___x_7006_ = lean_uint64_dec_eq(v___x_7005_, v___y_7003_);
if (v___x_7006_ == 0)
{
uint64_t v___x_7007_; 
v___x_7007_ = lean_uint64_add(v___y_6995_, v___y_6996_);
v___y_6981_ = v___y_6994_;
v___y_6982_ = v___y_7004_;
v___y_6983_ = v___y_6997_;
v___y_6984_ = v___y_6998_;
v___y_6985_ = v___y_6999_;
v___y_6986_ = v___y_7000_;
v___y_6987_ = v___y_7001_;
v___y_6988_ = v___y_7003_;
v___y_6989_ = v___x_7007_;
goto v___jp_6980_;
}
else
{
v___y_6981_ = v___y_6994_;
v___y_6982_ = v___y_7004_;
v___y_6983_ = v___y_6997_;
v___y_6984_ = v___y_6998_;
v___y_6985_ = v___y_6999_;
v___y_6986_ = v___y_7000_;
v___y_6987_ = v___y_7001_;
v___y_6988_ = v___y_7003_;
v___y_6989_ = v___y_6995_;
goto v___jp_6980_;
}
}
v___jp_7008_:
{
uint64_t v___x_7018_; uint64_t v___x_7019_; uint8_t v___x_7020_; 
v___x_7018_ = 4ULL;
v___x_7019_ = lean_uint64_shift_right(v___y_7015_, v___x_7018_);
v___x_7020_ = lean_uint64_dec_eq(v___x_7019_, v___y_7016_);
if (v___x_7020_ == 0)
{
v___y_6994_ = v___y_7009_;
v___y_6995_ = v___y_7017_;
v___y_6996_ = v___x_7018_;
v___y_6997_ = v___y_7010_;
v___y_6998_ = v___y_7011_;
v___y_6999_ = v___y_7012_;
v___y_7000_ = v___y_7013_;
v___y_7001_ = v___y_7014_;
v___y_7002_ = v___y_7015_;
v___y_7003_ = v___y_7016_;
v___y_7004_ = v___x_7019_;
goto v___jp_6993_;
}
else
{
v___y_6994_ = v___y_7009_;
v___y_6995_ = v___y_7017_;
v___y_6996_ = v___x_7018_;
v___y_6997_ = v___y_7010_;
v___y_6998_ = v___y_7011_;
v___y_6999_ = v___y_7012_;
v___y_7000_ = v___y_7013_;
v___y_7001_ = v___y_7014_;
v___y_7002_ = v___y_7015_;
v___y_7003_ = v___y_7016_;
v___y_7004_ = v___y_7015_;
goto v___jp_6993_;
}
}
v___jp_7021_:
{
uint64_t v___x_7033_; uint8_t v___x_7034_; 
v___x_7033_ = lean_uint64_shift_right(v___y_7027_, v___y_7023_);
v___x_7034_ = lean_uint64_dec_eq(v___x_7033_, v___y_7031_);
if (v___x_7034_ == 0)
{
uint64_t v___x_7035_; 
v___x_7035_ = lean_uint64_add(v___y_7030_, v___y_7023_);
v___y_7009_ = v___y_7022_;
v___y_7010_ = v___y_7024_;
v___y_7011_ = v___y_7025_;
v___y_7012_ = v___y_7026_;
v___y_7013_ = v___y_7028_;
v___y_7014_ = v___y_7029_;
v___y_7015_ = v___y_7032_;
v___y_7016_ = v___y_7031_;
v___y_7017_ = v___x_7035_;
goto v___jp_7008_;
}
else
{
v___y_7009_ = v___y_7022_;
v___y_7010_ = v___y_7024_;
v___y_7011_ = v___y_7025_;
v___y_7012_ = v___y_7026_;
v___y_7013_ = v___y_7028_;
v___y_7014_ = v___y_7029_;
v___y_7015_ = v___y_7032_;
v___y_7016_ = v___y_7031_;
v___y_7017_ = v___y_7030_;
goto v___jp_7008_;
}
}
v___jp_7036_:
{
uint64_t v___x_7046_; uint64_t v___x_7047_; uint8_t v___x_7048_; 
v___x_7046_ = 8ULL;
v___x_7047_ = lean_uint64_shift_right(v___y_7041_, v___x_7046_);
v___x_7048_ = lean_uint64_dec_eq(v___x_7047_, v___y_7044_);
if (v___x_7048_ == 0)
{
v___y_7022_ = v___y_7037_;
v___y_7023_ = v___x_7046_;
v___y_7024_ = v___y_7038_;
v___y_7025_ = v___y_7039_;
v___y_7026_ = v___y_7040_;
v___y_7027_ = v___y_7041_;
v___y_7028_ = v___y_7042_;
v___y_7029_ = v___y_7043_;
v___y_7030_ = v___y_7045_;
v___y_7031_ = v___y_7044_;
v___y_7032_ = v___x_7047_;
goto v___jp_7021_;
}
else
{
v___y_7022_ = v___y_7037_;
v___y_7023_ = v___x_7046_;
v___y_7024_ = v___y_7038_;
v___y_7025_ = v___y_7039_;
v___y_7026_ = v___y_7040_;
v___y_7027_ = v___y_7041_;
v___y_7028_ = v___y_7042_;
v___y_7029_ = v___y_7043_;
v___y_7030_ = v___y_7045_;
v___y_7031_ = v___y_7044_;
v___y_7032_ = v___y_7041_;
goto v___jp_7021_;
}
}
v___jp_7049_:
{
uint64_t v___x_7061_; uint8_t v___x_7062_; 
v___x_7061_ = lean_uint64_shift_right(v___y_7051_, v___y_7058_);
v___x_7062_ = lean_uint64_dec_eq(v___x_7061_, v___y_7059_);
if (v___x_7062_ == 0)
{
uint64_t v___x_7063_; 
v___x_7063_ = lean_uint64_add(v___y_7052_, v___y_7058_);
v___y_7037_ = v___y_7050_;
v___y_7038_ = v___y_7053_;
v___y_7039_ = v___y_7054_;
v___y_7040_ = v___y_7055_;
v___y_7041_ = v___y_7060_;
v___y_7042_ = v___y_7056_;
v___y_7043_ = v___y_7057_;
v___y_7044_ = v___y_7059_;
v___y_7045_ = v___x_7063_;
goto v___jp_7036_;
}
else
{
v___y_7037_ = v___y_7050_;
v___y_7038_ = v___y_7053_;
v___y_7039_ = v___y_7054_;
v___y_7040_ = v___y_7055_;
v___y_7041_ = v___y_7060_;
v___y_7042_ = v___y_7056_;
v___y_7043_ = v___y_7057_;
v___y_7044_ = v___y_7059_;
v___y_7045_ = v___y_7052_;
goto v___jp_7036_;
}
}
v___jp_7064_:
{
uint64_t v___x_7074_; uint64_t v___x_7075_; uint8_t v___x_7076_; 
v___x_7074_ = 16ULL;
v___x_7075_ = lean_uint64_shift_right(v___y_7066_, v___x_7074_);
v___x_7076_ = lean_uint64_dec_eq(v___x_7075_, v___y_7072_);
if (v___x_7076_ == 0)
{
v___y_7050_ = v___y_7065_;
v___y_7051_ = v___y_7066_;
v___y_7052_ = v___y_7073_;
v___y_7053_ = v___y_7067_;
v___y_7054_ = v___y_7068_;
v___y_7055_ = v___y_7069_;
v___y_7056_ = v___y_7070_;
v___y_7057_ = v___y_7071_;
v___y_7058_ = v___x_7074_;
v___y_7059_ = v___y_7072_;
v___y_7060_ = v___x_7075_;
goto v___jp_7049_;
}
else
{
v___y_7050_ = v___y_7065_;
v___y_7051_ = v___y_7066_;
v___y_7052_ = v___y_7073_;
v___y_7053_ = v___y_7067_;
v___y_7054_ = v___y_7068_;
v___y_7055_ = v___y_7069_;
v___y_7056_ = v___y_7070_;
v___y_7057_ = v___y_7071_;
v___y_7058_ = v___x_7074_;
v___y_7059_ = v___y_7072_;
v___y_7060_ = v___y_7066_;
goto v___jp_7049_;
}
}
v___jp_7077_:
{
uint64_t v___x_7087_; uint8_t v___x_7088_; 
v___x_7087_ = lean_uint64_shift_right(v___y_7079_, v___y_7084_);
v___x_7088_ = lean_uint64_dec_eq(v___x_7087_, v___y_7085_);
if (v___x_7088_ == 0)
{
v___y_7065_ = v___y_7078_;
v___y_7066_ = v___y_7086_;
v___y_7067_ = v___y_7079_;
v___y_7068_ = v___y_7080_;
v___y_7069_ = v___y_7081_;
v___y_7070_ = v___y_7082_;
v___y_7071_ = v___y_7083_;
v___y_7072_ = v___y_7085_;
v___y_7073_ = v___y_7084_;
goto v___jp_7064_;
}
else
{
v___y_7065_ = v___y_7078_;
v___y_7066_ = v___y_7086_;
v___y_7067_ = v___y_7079_;
v___y_7068_ = v___y_7080_;
v___y_7069_ = v___y_7081_;
v___y_7070_ = v___y_7082_;
v___y_7071_ = v___y_7083_;
v___y_7072_ = v___y_7085_;
v___y_7073_ = v___y_7085_;
goto v___jp_7064_;
}
}
v___jp_7089_:
{
uint64_t v___x_7096_; uint8_t v___x_7097_; 
v___x_7096_ = 0ULL;
v___x_7097_ = lean_uint64_dec_eq(v___y_7091_, v___x_7096_);
if (v___x_7097_ == 0)
{
uint64_t v___x_7098_; uint64_t v___x_7099_; uint8_t v___x_7100_; 
v___x_7098_ = 32ULL;
v___x_7099_ = lean_uint64_shift_right(v___y_7091_, v___x_7098_);
v___x_7100_ = lean_uint64_dec_eq(v___x_7099_, v___x_7096_);
if (v___x_7100_ == 0)
{
v___y_7078_ = v___y_7090_;
v___y_7079_ = v___y_7091_;
v___y_7080_ = v___y_7092_;
v___y_7081_ = v___y_7093_;
v___y_7082_ = v___y_7094_;
v___y_7083_ = v___y_7095_;
v___y_7084_ = v___x_7098_;
v___y_7085_ = v___x_7096_;
v___y_7086_ = v___x_7099_;
goto v___jp_7077_;
}
else
{
v___y_7078_ = v___y_7090_;
v___y_7079_ = v___y_7091_;
v___y_7080_ = v___y_7092_;
v___y_7081_ = v___y_7093_;
v___y_7082_ = v___y_7094_;
v___y_7083_ = v___y_7095_;
v___y_7084_ = v___x_7098_;
v___y_7085_ = v___x_7096_;
v___y_7086_ = v___y_7091_;
goto v___jp_7077_;
}
}
else
{
if (v___y_7092_ == 0)
{
uint32_t v___x_7101_; 
v___x_7101_ = 0;
v___y_6775_ = v___x_7101_;
goto v___jp_6774_;
}
else
{
uint32_t v___x_7102_; 
v___x_7102_ = 2147483648;
v___y_6775_ = v___x_7102_;
goto v___jp_6774_;
}
}
}
v___jp_7103_:
{
uint32_t v___x_7107_; uint32_t v___x_7108_; 
v___x_7107_ = lean_uint32_land(v___y_7105_, v___y_7104_);
v___x_7108_ = lean_uint32_lor(v___y_7106_, v___x_7107_);
v___y_6775_ = v___x_7108_;
goto v___jp_6774_;
}
v___jp_7109_:
{
uint8_t v___x_7114_; 
v___x_7114_ = lean_uint64_dec_eq(v___y_7113_, v___y_7111_);
if (v___x_7114_ == 0)
{
uint64_t v___x_7115_; uint8_t v___x_7116_; 
v___x_7115_ = 8388608ULL;
v___x_7116_ = lean_uint64_dec_eq(v___y_7113_, v___x_7115_);
if (v___x_7116_ == 0)
{
uint32_t v___x_7117_; 
v___x_7117_ = lean_uint64_to_uint32(v___y_7113_);
if (v___y_7112_ == 0)
{
uint32_t v___x_7118_; 
v___x_7118_ = 0;
v___y_7104_ = v___y_7110_;
v___y_7105_ = v___x_7117_;
v___y_7106_ = v___x_7118_;
goto v___jp_7103_;
}
else
{
uint32_t v___x_7119_; 
v___x_7119_ = 2147483648;
v___y_7104_ = v___y_7110_;
v___y_7105_ = v___x_7117_;
v___y_7106_ = v___x_7119_;
goto v___jp_7103_;
}
}
else
{
if (v___y_7112_ == 0)
{
uint32_t v___x_7120_; 
v___x_7120_ = 0;
v___y_6798_ = v___x_7120_;
goto v___jp_6797_;
}
else
{
uint32_t v___x_7121_; 
v___x_7121_ = 2147483648;
v___y_6798_ = v___x_7121_;
goto v___jp_6797_;
}
}
}
else
{
if (v___y_7112_ == 0)
{
uint32_t v___x_7122_; 
v___x_7122_ = 0;
v___y_6775_ = v___x_7122_;
goto v___jp_6774_;
}
else
{
uint32_t v___x_7123_; 
v___x_7123_ = 2147483648;
v___y_6775_ = v___x_7123_;
goto v___jp_6774_;
}
}
}
v___jp_7124_:
{
uint64_t v___x_7133_; uint64_t v___x_7134_; uint64_t v___x_7135_; uint8_t v___x_7136_; 
v___x_7133_ = lean_uint64_mul(v___y_7127_, v___y_7130_);
v___x_7134_ = lean_uint64_add(v___y_7126_, v___y_7132_);
v___x_7135_ = 281474976710656ULL;
v___x_7136_ = lean_uint64_dec_lt(v___x_7133_, v___x_7135_);
if (v___x_7136_ == 0)
{
v___y_7090_ = v___y_7125_;
v___y_7091_ = v___x_7133_;
v___y_7092_ = v___y_7128_;
v___y_7093_ = v___y_7129_;
v___y_7094_ = v___x_7134_;
v___y_7095_ = v___y_7131_;
goto v___jp_7089_;
}
else
{
uint64_t v___x_7137_; uint8_t v___x_7138_; 
v___x_7137_ = 123ULL;
v___x_7138_ = lean_uint64_dec_le(v___x_7134_, v___x_7137_);
if (v___x_7138_ == 0)
{
v___y_7090_ = v___y_7125_;
v___y_7091_ = v___x_7133_;
v___y_7092_ = v___y_7128_;
v___y_7093_ = v___y_7129_;
v___y_7094_ = v___x_7134_;
v___y_7095_ = v___y_7131_;
goto v___jp_7089_;
}
else
{
uint64_t v___x_7139_; uint8_t v___x_7140_; 
v___x_7139_ = 0ULL;
v___x_7140_ = lean_uint64_dec_eq(v___x_7133_, v___x_7139_);
if (v___x_7140_ == 0)
{
uint64_t v___x_7141_; uint64_t v___x_7142_; uint8_t v___x_7143_; 
v___x_7141_ = 149ULL;
v___x_7142_ = lean_uint64_sub(v___x_7141_, v___x_7134_);
v___x_7143_ = lean_uint64_dec_eq(v___x_7142_, v___x_7139_);
if (v___x_7143_ == 0)
{
uint64_t v___x_7144_; uint8_t v___x_7145_; 
v___x_7144_ = 64ULL;
v___x_7145_ = lean_uint64_dec_lt(v___x_7142_, v___x_7144_);
if (v___x_7145_ == 0)
{
uint8_t v___x_7146_; 
v___x_7146_ = lean_uint64_dec_eq(v___x_7142_, v___x_7144_);
if (v___x_7146_ == 0)
{
v___y_7110_ = v___y_7125_;
v___y_7111_ = v___x_7139_;
v___y_7112_ = v___y_7128_;
v___y_7113_ = v___x_7139_;
goto v___jp_7109_;
}
else
{
uint64_t v___x_7147_; uint8_t v___x_7148_; 
v___x_7147_ = 9223372036854775808ULL;
v___x_7148_ = lean_uint64_dec_lt(v___x_7147_, v___x_7133_);
if (v___x_7148_ == 0)
{
v___y_7110_ = v___y_7125_;
v___y_7111_ = v___x_7139_;
v___y_7112_ = v___y_7128_;
v___y_7113_ = v___x_7139_;
goto v___jp_7109_;
}
else
{
uint64_t v___x_7149_; 
v___x_7149_ = 1ULL;
v___y_7110_ = v___y_7125_;
v___y_7111_ = v___x_7139_;
v___y_7112_ = v___y_7128_;
v___y_7113_ = v___x_7149_;
goto v___jp_7109_;
}
}
}
else
{
uint64_t v_quotient_7150_; uint64_t v___x_7151_; uint64_t v___x_7152_; uint64_t v___x_7153_; uint64_t v_remainder_7154_; uint64_t v___x_7155_; uint64_t v_half_7156_; uint8_t v___x_7157_; 
v_quotient_7150_ = lean_uint64_shift_right(v___x_7133_, v___x_7142_);
v___x_7151_ = 1ULL;
v___x_7152_ = lean_uint64_shift_left(v___x_7151_, v___x_7142_);
v___x_7153_ = lean_uint64_sub(v___x_7152_, v___x_7151_);
v_remainder_7154_ = lean_uint64_land(v___x_7133_, v___x_7153_);
v___x_7155_ = lean_uint64_sub(v___x_7142_, v___x_7151_);
v_half_7156_ = lean_uint64_shift_left(v___x_7151_, v___x_7155_);
v___x_7157_ = lean_uint64_dec_lt(v_remainder_7154_, v_half_7156_);
if (v___x_7157_ == 0)
{
uint8_t v___x_7158_; 
v___x_7158_ = lean_uint64_dec_lt(v_half_7156_, v_remainder_7154_);
if (v___x_7158_ == 0)
{
uint64_t v___x_7159_; uint8_t v___x_7160_; 
v___x_7159_ = lean_uint64_land(v_quotient_7150_, v___x_7151_);
v___x_7160_ = lean_uint64_dec_eq(v___x_7159_, v___x_7139_);
if (v___x_7160_ == 0)
{
uint64_t v___x_7161_; 
v___x_7161_ = lean_uint64_add(v_quotient_7150_, v___x_7151_);
v___y_7110_ = v___y_7125_;
v___y_7111_ = v___x_7139_;
v___y_7112_ = v___y_7128_;
v___y_7113_ = v___x_7161_;
goto v___jp_7109_;
}
else
{
v___y_7110_ = v___y_7125_;
v___y_7111_ = v___x_7139_;
v___y_7112_ = v___y_7128_;
v___y_7113_ = v_quotient_7150_;
goto v___jp_7109_;
}
}
else
{
uint64_t v___x_7162_; 
v___x_7162_ = lean_uint64_add(v_quotient_7150_, v___x_7151_);
v___y_7110_ = v___y_7125_;
v___y_7111_ = v___x_7139_;
v___y_7112_ = v___y_7128_;
v___y_7113_ = v___x_7162_;
goto v___jp_7109_;
}
}
else
{
v___y_7110_ = v___y_7125_;
v___y_7111_ = v___x_7139_;
v___y_7112_ = v___y_7128_;
v___y_7113_ = v_quotient_7150_;
goto v___jp_7109_;
}
}
}
else
{
v___y_7110_ = v___y_7125_;
v___y_7111_ = v___x_7139_;
v___y_7112_ = v___y_7128_;
v___y_7113_ = v___x_7133_;
goto v___jp_7109_;
}
}
else
{
if (v___y_7128_ == 0)
{
uint32_t v___x_7163_; 
v___x_7163_ = 0;
v___y_6775_ = v___x_7163_;
goto v___jp_6774_;
}
else
{
uint32_t v___x_7164_; 
v___x_7164_ = 2147483648;
v___y_6775_ = v___x_7164_;
goto v___jp_6774_;
}
}
}
}
}
v___jp_7165_:
{
uint64_t v___x_7174_; uint64_t v___x_7175_; uint8_t v___x_7176_; 
v___x_7174_ = lean_uint32_to_uint64(v___y_7169_);
v___x_7175_ = 0ULL;
v___x_7176_ = lean_uint64_dec_eq(v___x_7174_, v___x_7175_);
if (v___x_7176_ == 0)
{
uint64_t v___x_7177_; uint64_t v___x_7178_; 
v___x_7177_ = 1ULL;
v___x_7178_ = lean_uint64_sub(v___x_7174_, v___x_7177_);
v___y_7125_ = v___y_7166_;
v___y_7126_ = v___y_7173_;
v___y_7127_ = v___y_7167_;
v___y_7128_ = v___y_7168_;
v___y_7129_ = v___y_7170_;
v___y_7130_ = v___y_7171_;
v___y_7131_ = v___y_7172_;
v___y_7132_ = v___x_7178_;
goto v___jp_7124_;
}
else
{
v___y_7125_ = v___y_7166_;
v___y_7126_ = v___y_7173_;
v___y_7127_ = v___y_7167_;
v___y_7128_ = v___y_7168_;
v___y_7129_ = v___y_7170_;
v___y_7130_ = v___y_7171_;
v___y_7131_ = v___y_7172_;
v___y_7132_ = v___x_7175_;
goto v___jp_7124_;
}
}
v___jp_7179_:
{
uint64_t v___x_7188_; uint64_t v___x_7189_; uint8_t v___x_7190_; 
v___x_7188_ = lean_uint32_to_uint64(v___y_7185_);
v___x_7189_ = 0ULL;
v___x_7190_ = lean_uint64_dec_eq(v___x_7188_, v___x_7189_);
if (v___x_7190_ == 0)
{
uint64_t v___x_7191_; uint64_t v___x_7192_; 
v___x_7191_ = 1ULL;
v___x_7192_ = lean_uint64_sub(v___x_7188_, v___x_7191_);
v___y_7166_ = v___y_7180_;
v___y_7167_ = v___y_7181_;
v___y_7168_ = v___y_7182_;
v___y_7169_ = v___y_7184_;
v___y_7170_ = v___y_7183_;
v___y_7171_ = v___y_7187_;
v___y_7172_ = v___y_7186_;
v___y_7173_ = v___x_7192_;
goto v___jp_7165_;
}
else
{
v___y_7166_ = v___y_7180_;
v___y_7167_ = v___y_7181_;
v___y_7168_ = v___y_7182_;
v___y_7169_ = v___y_7184_;
v___y_7170_ = v___y_7183_;
v___y_7171_ = v___y_7187_;
v___y_7172_ = v___y_7186_;
v___y_7173_ = v___x_7189_;
goto v___jp_7165_;
}
}
v___jp_7193_:
{
uint32_t v___x_7202_; uint8_t v___x_7203_; 
v___x_7202_ = 0;
v___x_7203_ = lean_uint32_dec_eq(v___y_7196_, v___x_7202_);
if (v___x_7203_ == 0)
{
uint64_t v___x_7204_; uint64_t v___x_7205_; uint64_t v___x_7206_; 
v___x_7204_ = lean_uint32_to_uint64(v___y_7199_);
v___x_7205_ = 8388608ULL;
v___x_7206_ = lean_uint64_lor(v___x_7204_, v___x_7205_);
v___y_7180_ = v___y_7194_;
v___y_7181_ = v___y_7201_;
v___y_7182_ = v___y_7195_;
v___y_7183_ = v___y_7197_;
v___y_7184_ = v___y_7196_;
v___y_7185_ = v___y_7198_;
v___y_7186_ = v___y_7200_;
v___y_7187_ = v___x_7206_;
goto v___jp_7179_;
}
else
{
uint64_t v___x_7207_; 
v___x_7207_ = lean_uint32_to_uint64(v___y_7199_);
v___y_7180_ = v___y_7194_;
v___y_7181_ = v___y_7201_;
v___y_7182_ = v___y_7195_;
v___y_7183_ = v___y_7197_;
v___y_7184_ = v___y_7196_;
v___y_7185_ = v___y_7198_;
v___y_7186_ = v___y_7200_;
v___y_7187_ = v___x_7207_;
goto v___jp_7179_;
}
}
v___jp_7208_:
{
uint32_t v___x_7216_; uint32_t v_xFraction_7217_; uint32_t v_yFraction_7218_; uint32_t v___x_7219_; uint8_t v___x_7220_; 
v___x_7216_ = 8388607;
v_xFraction_7217_ = lean_uint32_land(v___y_7209_, v___x_7216_);
v_yFraction_7218_ = lean_uint32_land(v___y_7210_, v___x_7216_);
v___x_7219_ = 0;
v___x_7220_ = lean_uint32_dec_eq(v___y_7213_, v___x_7219_);
if (v___x_7220_ == 0)
{
uint64_t v___x_7221_; uint64_t v___x_7222_; uint64_t v___x_7223_; 
v___x_7221_ = lean_uint32_to_uint64(v_xFraction_7217_);
v___x_7222_ = 8388608ULL;
v___x_7223_ = lean_uint64_lor(v___x_7221_, v___x_7222_);
v___y_7194_ = v___x_7216_;
v___y_7195_ = v___y_7215_;
v___y_7196_ = v___y_7212_;
v___y_7197_ = v___y_7211_;
v___y_7198_ = v___y_7213_;
v___y_7199_ = v_yFraction_7218_;
v___y_7200_ = v___y_7214_;
v___y_7201_ = v___x_7223_;
goto v___jp_7193_;
}
else
{
uint64_t v___x_7224_; 
v___x_7224_ = lean_uint32_to_uint64(v_xFraction_7217_);
v___y_7194_ = v___x_7216_;
v___y_7195_ = v___y_7215_;
v___y_7196_ = v___y_7212_;
v___y_7197_ = v___y_7211_;
v___y_7198_ = v___y_7213_;
v___y_7199_ = v_yFraction_7218_;
v___y_7200_ = v___y_7214_;
v___y_7201_ = v___x_7224_;
goto v___jp_7193_;
}
}
v___jp_7225_:
{
uint32_t v___x_7229_; uint32_t v___x_7230_; 
v___x_7229_ = lean_uint32_land(v___y_7227_, v___y_7226_);
v___x_7230_ = lean_uint32_lor(v___y_7228_, v___x_7229_);
v___y_6775_ = v___x_7230_;
goto v___jp_6774_;
}
v___jp_7231_:
{
uint8_t v___x_7236_; 
v___x_7236_ = lean_uint64_dec_eq(v___y_7235_, v___y_7234_);
if (v___x_7236_ == 0)
{
uint64_t v___x_7237_; uint8_t v___x_7238_; 
v___x_7237_ = 8388608ULL;
v___x_7238_ = lean_uint64_dec_eq(v___y_7235_, v___x_7237_);
if (v___x_7238_ == 0)
{
uint32_t v___x_7239_; 
v___x_7239_ = lean_uint64_to_uint32(v___y_7235_);
if (v___y_7233_ == 0)
{
uint32_t v___x_7240_; 
v___x_7240_ = 0;
v___y_7226_ = v___y_7232_;
v___y_7227_ = v___x_7239_;
v___y_7228_ = v___x_7240_;
goto v___jp_7225_;
}
else
{
uint32_t v___x_7241_; 
v___x_7241_ = 2147483648;
v___y_7226_ = v___y_7232_;
v___y_7227_ = v___x_7239_;
v___y_7228_ = v___x_7241_;
goto v___jp_7225_;
}
}
else
{
if (v___y_7233_ == 0)
{
uint32_t v___x_7242_; 
v___x_7242_ = 0;
v___y_6802_ = v___x_7242_;
goto v___jp_6801_;
}
else
{
uint32_t v___x_7243_; 
v___x_7243_ = 2147483648;
v___y_6802_ = v___x_7243_;
goto v___jp_6801_;
}
}
}
else
{
if (v___y_7233_ == 0)
{
uint32_t v___x_7244_; 
v___x_7244_ = 0;
v___y_6775_ = v___x_7244_;
goto v___jp_6774_;
}
else
{
uint32_t v___x_7245_; 
v___x_7245_ = 2147483648;
v___y_6775_ = v___x_7245_;
goto v___jp_6774_;
}
}
}
v___jp_7246_:
{
uint32_t v___x_7253_; uint32_t v___x_7254_; uint32_t v___x_7255_; uint32_t v___x_7256_; uint32_t v___x_7257_; 
v___x_7253_ = lean_uint32_land(v___y_7250_, v___y_7251_);
v___x_7254_ = lean_uint32_shift_left(v___x_7253_, v___y_7249_);
v___x_7255_ = lean_uint32_lor(v___y_7252_, v___x_7254_);
v___x_7256_ = lean_uint32_land(v___y_7247_, v___y_7248_);
v___x_7257_ = lean_uint32_lor(v___x_7255_, v___x_7256_);
v___y_6775_ = v___x_7257_;
goto v___jp_6774_;
}
v___jp_7258_:
{
if (v___y_7261_ == 0)
{
uint32_t v___x_7265_; 
v___x_7265_ = 0;
v___y_7247_ = v___y_7264_;
v___y_7248_ = v___y_7259_;
v___y_7249_ = v___y_7260_;
v___y_7250_ = v___y_7262_;
v___y_7251_ = v___y_7263_;
v___y_7252_ = v___x_7265_;
goto v___jp_7246_;
}
else
{
uint32_t v___x_7266_; 
v___x_7266_ = 2147483648;
v___y_7247_ = v___y_7264_;
v___y_7248_ = v___y_7259_;
v___y_7249_ = v___y_7260_;
v___y_7250_ = v___y_7262_;
v___y_7251_ = v___y_7263_;
v___y_7252_ = v___x_7266_;
goto v___jp_7246_;
}
}
v___jp_7267_:
{
uint64_t v___x_7275_; uint64_t v_encodedExponent_7276_; uint32_t v___x_7277_; uint64_t v___x_7278_; uint8_t v___x_7279_; 
v___x_7275_ = 171ULL;
v_encodedExponent_7276_ = lean_uint64_sub(v___y_7271_, v___x_7275_);
v___x_7277_ = lean_uint64_to_uint32(v_encodedExponent_7276_);
v___x_7278_ = 8388608ULL;
v___x_7279_ = lean_uint64_dec_lt(v___y_7274_, v___x_7278_);
if (v___x_7279_ == 0)
{
uint64_t v___x_7280_; uint32_t v___x_7281_; 
v___x_7280_ = lean_uint64_sub(v___y_7274_, v___x_7278_);
v___x_7281_ = lean_uint64_to_uint32(v___x_7280_);
v___y_7259_ = v___y_7268_;
v___y_7260_ = v___y_7269_;
v___y_7261_ = v___y_7270_;
v___y_7262_ = v___x_7277_;
v___y_7263_ = v___y_7272_;
v___y_7264_ = v___x_7281_;
goto v___jp_7258_;
}
else
{
uint32_t v___x_7282_; 
v___x_7282_ = lean_uint64_to_uint32(v___y_7273_);
v___y_7259_ = v___y_7268_;
v___y_7260_ = v___y_7269_;
v___y_7261_ = v___y_7270_;
v___y_7262_ = v___x_7277_;
v___y_7263_ = v___y_7272_;
v___y_7264_ = v___x_7282_;
goto v___jp_7258_;
}
}
v___jp_7283_:
{
uint64_t v___x_7292_; uint8_t v___x_7293_; 
v___x_7292_ = 425ULL;
v___x_7293_ = lean_uint64_dec_lt(v___x_7292_, v___y_7291_);
if (v___x_7293_ == 0)
{
if (v___y_7288_ == 0)
{
v___y_7268_ = v___y_7284_;
v___y_7269_ = v___y_7285_;
v___y_7270_ = v___y_7287_;
v___y_7271_ = v___y_7291_;
v___y_7272_ = v___y_7289_;
v___y_7273_ = v___y_7290_;
v___y_7274_ = v___y_7286_;
goto v___jp_7267_;
}
else
{
uint64_t v___x_7294_; 
v___x_7294_ = 8388608ULL;
v___y_7268_ = v___y_7284_;
v___y_7269_ = v___y_7285_;
v___y_7270_ = v___y_7287_;
v___y_7271_ = v___y_7291_;
v___y_7272_ = v___y_7289_;
v___y_7273_ = v___y_7290_;
v___y_7274_ = v___x_7294_;
goto v___jp_7267_;
}
}
else
{
if (v___y_7287_ == 0)
{
uint32_t v___x_7295_; 
v___x_7295_ = 2139095040;
v___y_6775_ = v___x_7295_;
goto v___jp_6774_;
}
else
{
uint32_t v___x_7296_; 
v___x_7296_ = 4286578688;
v___y_6775_ = v___x_7296_;
goto v___jp_6774_;
}
}
}
v___jp_7297_:
{
uint64_t v___x_7305_; uint8_t v_carry_7306_; 
v___x_7305_ = 16777216ULL;
v_carry_7306_ = lean_uint64_dec_eq(v___y_7304_, v___x_7305_);
if (v_carry_7306_ == 0)
{
v___y_7284_ = v___y_7298_;
v___y_7285_ = v___y_7299_;
v___y_7286_ = v___y_7304_;
v___y_7287_ = v___y_7300_;
v___y_7288_ = v_carry_7306_;
v___y_7289_ = v___y_7302_;
v___y_7290_ = v___y_7303_;
v___y_7291_ = v___y_7301_;
goto v___jp_7283_;
}
else
{
uint64_t v___x_7307_; uint64_t v___x_7308_; 
v___x_7307_ = 1ULL;
v___x_7308_ = lean_uint64_add(v___y_7301_, v___x_7307_);
v___y_7284_ = v___y_7298_;
v___y_7285_ = v___y_7299_;
v___y_7286_ = v___y_7304_;
v___y_7287_ = v___y_7300_;
v___y_7288_ = v_carry_7306_;
v___y_7289_ = v___y_7302_;
v___y_7290_ = v___y_7303_;
v___y_7291_ = v___x_7308_;
goto v___jp_7283_;
}
}
v___jp_7309_:
{
uint64_t v_position_7318_; uint64_t v___x_7319_; uint8_t v___x_7320_; 
v_position_7318_ = lean_uint64_add(v___y_7317_, v___y_7310_);
v___x_7319_ = 172ULL;
v___x_7320_ = lean_uint64_dec_lt(v_position_7318_, v___x_7319_);
if (v___x_7320_ == 0)
{
uint64_t v___x_7321_; uint8_t v___x_7322_; 
v___x_7321_ = 23ULL;
v___x_7322_ = lean_uint64_dec_lt(v___y_7317_, v___x_7321_);
if (v___x_7322_ == 0)
{
uint64_t v___x_7323_; uint8_t v___x_7324_; 
v___x_7323_ = lean_uint64_sub(v___y_7317_, v___x_7321_);
v___x_7324_ = lean_uint64_dec_eq(v___x_7323_, v___y_7315_);
if (v___x_7324_ == 0)
{
uint64_t v___x_7325_; uint8_t v___x_7326_; 
v___x_7325_ = 64ULL;
v___x_7326_ = lean_uint64_dec_lt(v___x_7323_, v___x_7325_);
if (v___x_7326_ == 0)
{
uint8_t v___x_7327_; 
v___x_7327_ = lean_uint64_dec_eq(v___x_7323_, v___x_7325_);
if (v___x_7327_ == 0)
{
v___y_7298_ = v___y_7311_;
v___y_7299_ = v___y_7312_;
v___y_7300_ = v___y_7313_;
v___y_7301_ = v_position_7318_;
v___y_7302_ = v___y_7314_;
v___y_7303_ = v___y_7315_;
v___y_7304_ = v___y_7315_;
goto v___jp_7297_;
}
else
{
uint64_t v___x_7328_; uint8_t v___x_7329_; 
v___x_7328_ = 9223372036854775808ULL;
v___x_7329_ = lean_uint64_dec_lt(v___x_7328_, v___y_7316_);
if (v___x_7329_ == 0)
{
v___y_7298_ = v___y_7311_;
v___y_7299_ = v___y_7312_;
v___y_7300_ = v___y_7313_;
v___y_7301_ = v_position_7318_;
v___y_7302_ = v___y_7314_;
v___y_7303_ = v___y_7315_;
v___y_7304_ = v___y_7315_;
goto v___jp_7297_;
}
else
{
uint64_t v___x_7330_; 
v___x_7330_ = 1ULL;
v___y_7298_ = v___y_7311_;
v___y_7299_ = v___y_7312_;
v___y_7300_ = v___y_7313_;
v___y_7301_ = v_position_7318_;
v___y_7302_ = v___y_7314_;
v___y_7303_ = v___y_7315_;
v___y_7304_ = v___x_7330_;
goto v___jp_7297_;
}
}
}
else
{
uint64_t v_quotient_7331_; uint64_t v___x_7332_; uint64_t v___x_7333_; uint64_t v___x_7334_; uint64_t v_remainder_7335_; uint64_t v___x_7336_; uint64_t v_half_7337_; uint8_t v___x_7338_; 
v_quotient_7331_ = lean_uint64_shift_right(v___y_7316_, v___x_7323_);
v___x_7332_ = 1ULL;
v___x_7333_ = lean_uint64_shift_left(v___x_7332_, v___x_7323_);
v___x_7334_ = lean_uint64_sub(v___x_7333_, v___x_7332_);
v_remainder_7335_ = lean_uint64_land(v___y_7316_, v___x_7334_);
v___x_7336_ = lean_uint64_sub(v___x_7323_, v___x_7332_);
v_half_7337_ = lean_uint64_shift_left(v___x_7332_, v___x_7336_);
v___x_7338_ = lean_uint64_dec_lt(v_remainder_7335_, v_half_7337_);
if (v___x_7338_ == 0)
{
uint8_t v___x_7339_; 
v___x_7339_ = lean_uint64_dec_lt(v_half_7337_, v_remainder_7335_);
if (v___x_7339_ == 0)
{
uint64_t v___x_7340_; uint8_t v___x_7341_; 
v___x_7340_ = lean_uint64_land(v_quotient_7331_, v___x_7332_);
v___x_7341_ = lean_uint64_dec_eq(v___x_7340_, v___y_7315_);
if (v___x_7341_ == 0)
{
uint64_t v___x_7342_; 
v___x_7342_ = lean_uint64_add(v_quotient_7331_, v___x_7332_);
v___y_7298_ = v___y_7311_;
v___y_7299_ = v___y_7312_;
v___y_7300_ = v___y_7313_;
v___y_7301_ = v_position_7318_;
v___y_7302_ = v___y_7314_;
v___y_7303_ = v___y_7315_;
v___y_7304_ = v___x_7342_;
goto v___jp_7297_;
}
else
{
v___y_7298_ = v___y_7311_;
v___y_7299_ = v___y_7312_;
v___y_7300_ = v___y_7313_;
v___y_7301_ = v_position_7318_;
v___y_7302_ = v___y_7314_;
v___y_7303_ = v___y_7315_;
v___y_7304_ = v_quotient_7331_;
goto v___jp_7297_;
}
}
else
{
uint64_t v___x_7343_; 
v___x_7343_ = lean_uint64_add(v_quotient_7331_, v___x_7332_);
v___y_7298_ = v___y_7311_;
v___y_7299_ = v___y_7312_;
v___y_7300_ = v___y_7313_;
v___y_7301_ = v_position_7318_;
v___y_7302_ = v___y_7314_;
v___y_7303_ = v___y_7315_;
v___y_7304_ = v___x_7343_;
goto v___jp_7297_;
}
}
else
{
v___y_7298_ = v___y_7311_;
v___y_7299_ = v___y_7312_;
v___y_7300_ = v___y_7313_;
v___y_7301_ = v_position_7318_;
v___y_7302_ = v___y_7314_;
v___y_7303_ = v___y_7315_;
v___y_7304_ = v_quotient_7331_;
goto v___jp_7297_;
}
}
}
else
{
v___y_7298_ = v___y_7311_;
v___y_7299_ = v___y_7312_;
v___y_7300_ = v___y_7313_;
v___y_7301_ = v_position_7318_;
v___y_7302_ = v___y_7314_;
v___y_7303_ = v___y_7315_;
v___y_7304_ = v___y_7316_;
goto v___jp_7297_;
}
}
else
{
uint64_t v___x_7344_; uint64_t v___x_7345_; 
v___x_7344_ = lean_uint64_sub(v___x_7321_, v___y_7317_);
v___x_7345_ = lean_uint64_shift_left(v___y_7316_, v___x_7344_);
v___y_7298_ = v___y_7311_;
v___y_7299_ = v___y_7312_;
v___y_7300_ = v___y_7313_;
v___y_7301_ = v_position_7318_;
v___y_7302_ = v___y_7314_;
v___y_7303_ = v___y_7315_;
v___y_7304_ = v___x_7345_;
goto v___jp_7297_;
}
}
else
{
uint64_t v___x_7346_; uint8_t v___x_7347_; 
v___x_7346_ = 149ULL;
v___x_7347_ = lean_uint64_dec_lt(v___y_7310_, v___x_7346_);
if (v___x_7347_ == 0)
{
uint64_t v___x_7348_; uint64_t v___x_7349_; 
v___x_7348_ = lean_uint64_sub(v___y_7310_, v___x_7346_);
v___x_7349_ = lean_uint64_shift_left(v___y_7316_, v___x_7348_);
v___y_7232_ = v___y_7311_;
v___y_7233_ = v___y_7313_;
v___y_7234_ = v___y_7315_;
v___y_7235_ = v___x_7349_;
goto v___jp_7231_;
}
else
{
uint64_t v___x_7350_; uint8_t v___x_7351_; 
v___x_7350_ = lean_uint64_sub(v___x_7346_, v___y_7310_);
v___x_7351_ = lean_uint64_dec_eq(v___x_7350_, v___y_7315_);
if (v___x_7351_ == 0)
{
uint64_t v___x_7352_; uint8_t v___x_7353_; 
v___x_7352_ = 64ULL;
v___x_7353_ = lean_uint64_dec_lt(v___x_7350_, v___x_7352_);
if (v___x_7353_ == 0)
{
uint8_t v___x_7354_; 
v___x_7354_ = lean_uint64_dec_eq(v___x_7350_, v___x_7352_);
if (v___x_7354_ == 0)
{
v___y_7232_ = v___y_7311_;
v___y_7233_ = v___y_7313_;
v___y_7234_ = v___y_7315_;
v___y_7235_ = v___y_7315_;
goto v___jp_7231_;
}
else
{
uint64_t v___x_7355_; uint8_t v___x_7356_; 
v___x_7355_ = 9223372036854775808ULL;
v___x_7356_ = lean_uint64_dec_lt(v___x_7355_, v___y_7316_);
if (v___x_7356_ == 0)
{
v___y_7232_ = v___y_7311_;
v___y_7233_ = v___y_7313_;
v___y_7234_ = v___y_7315_;
v___y_7235_ = v___y_7315_;
goto v___jp_7231_;
}
else
{
uint64_t v___x_7357_; 
v___x_7357_ = 1ULL;
v___y_7232_ = v___y_7311_;
v___y_7233_ = v___y_7313_;
v___y_7234_ = v___y_7315_;
v___y_7235_ = v___x_7357_;
goto v___jp_7231_;
}
}
}
else
{
uint64_t v_quotient_7358_; uint64_t v___x_7359_; uint64_t v___x_7360_; uint64_t v___x_7361_; uint64_t v_remainder_7362_; uint64_t v___x_7363_; uint64_t v_half_7364_; uint8_t v___x_7365_; 
v_quotient_7358_ = lean_uint64_shift_right(v___y_7316_, v___x_7350_);
v___x_7359_ = 1ULL;
v___x_7360_ = lean_uint64_shift_left(v___x_7359_, v___x_7350_);
v___x_7361_ = lean_uint64_sub(v___x_7360_, v___x_7359_);
v_remainder_7362_ = lean_uint64_land(v___y_7316_, v___x_7361_);
v___x_7363_ = lean_uint64_sub(v___x_7350_, v___x_7359_);
v_half_7364_ = lean_uint64_shift_left(v___x_7359_, v___x_7363_);
v___x_7365_ = lean_uint64_dec_lt(v_remainder_7362_, v_half_7364_);
if (v___x_7365_ == 0)
{
uint8_t v___x_7366_; 
v___x_7366_ = lean_uint64_dec_lt(v_half_7364_, v_remainder_7362_);
if (v___x_7366_ == 0)
{
uint64_t v___x_7367_; uint8_t v___x_7368_; 
v___x_7367_ = lean_uint64_land(v_quotient_7358_, v___x_7359_);
v___x_7368_ = lean_uint64_dec_eq(v___x_7367_, v___y_7315_);
if (v___x_7368_ == 0)
{
uint64_t v___x_7369_; 
v___x_7369_ = lean_uint64_add(v_quotient_7358_, v___x_7359_);
v___y_7232_ = v___y_7311_;
v___y_7233_ = v___y_7313_;
v___y_7234_ = v___y_7315_;
v___y_7235_ = v___x_7369_;
goto v___jp_7231_;
}
else
{
v___y_7232_ = v___y_7311_;
v___y_7233_ = v___y_7313_;
v___y_7234_ = v___y_7315_;
v___y_7235_ = v_quotient_7358_;
goto v___jp_7231_;
}
}
else
{
uint64_t v___x_7370_; 
v___x_7370_ = lean_uint64_add(v_quotient_7358_, v___x_7359_);
v___y_7232_ = v___y_7311_;
v___y_7233_ = v___y_7313_;
v___y_7234_ = v___y_7315_;
v___y_7235_ = v___x_7370_;
goto v___jp_7231_;
}
}
else
{
v___y_7232_ = v___y_7311_;
v___y_7233_ = v___y_7313_;
v___y_7234_ = v___y_7315_;
v___y_7235_ = v_quotient_7358_;
goto v___jp_7231_;
}
}
}
else
{
v___y_7232_ = v___y_7311_;
v___y_7233_ = v___y_7313_;
v___y_7234_ = v___y_7315_;
v___y_7235_ = v___y_7316_;
goto v___jp_7231_;
}
}
}
}
v___jp_7371_:
{
uint64_t v___x_7381_; uint64_t v___x_7382_; uint8_t v___x_7383_; 
v___x_7381_ = 1ULL;
v___x_7382_ = lean_uint64_shift_right(v___y_7373_, v___x_7381_);
v___x_7383_ = lean_uint64_dec_eq(v___x_7382_, v___y_7378_);
if (v___x_7383_ == 0)
{
uint64_t v___x_7384_; 
v___x_7384_ = lean_uint64_add(v___y_7380_, v___x_7381_);
v___y_7310_ = v___y_7372_;
v___y_7311_ = v___y_7374_;
v___y_7312_ = v___y_7375_;
v___y_7313_ = v___y_7376_;
v___y_7314_ = v___y_7377_;
v___y_7315_ = v___y_7378_;
v___y_7316_ = v___y_7379_;
v___y_7317_ = v___x_7384_;
goto v___jp_7309_;
}
else
{
v___y_7310_ = v___y_7372_;
v___y_7311_ = v___y_7374_;
v___y_7312_ = v___y_7375_;
v___y_7313_ = v___y_7376_;
v___y_7314_ = v___y_7377_;
v___y_7315_ = v___y_7378_;
v___y_7316_ = v___y_7379_;
v___y_7317_ = v___y_7380_;
goto v___jp_7309_;
}
}
v___jp_7385_:
{
uint64_t v___x_7397_; uint8_t v___x_7398_; 
v___x_7397_ = lean_uint64_shift_right(v___y_7388_, v___y_7392_);
v___x_7398_ = lean_uint64_dec_eq(v___x_7397_, v___y_7394_);
if (v___x_7398_ == 0)
{
uint64_t v___x_7399_; 
v___x_7399_ = lean_uint64_add(v___y_7386_, v___y_7392_);
v___y_7372_ = v___y_7387_;
v___y_7373_ = v___y_7396_;
v___y_7374_ = v___y_7389_;
v___y_7375_ = v___y_7390_;
v___y_7376_ = v___y_7391_;
v___y_7377_ = v___y_7393_;
v___y_7378_ = v___y_7394_;
v___y_7379_ = v___y_7395_;
v___y_7380_ = v___x_7399_;
goto v___jp_7371_;
}
else
{
v___y_7372_ = v___y_7387_;
v___y_7373_ = v___y_7396_;
v___y_7374_ = v___y_7389_;
v___y_7375_ = v___y_7390_;
v___y_7376_ = v___y_7391_;
v___y_7377_ = v___y_7393_;
v___y_7378_ = v___y_7394_;
v___y_7379_ = v___y_7395_;
v___y_7380_ = v___y_7386_;
goto v___jp_7371_;
}
}
v___jp_7400_:
{
uint64_t v___x_7410_; uint64_t v___x_7411_; uint8_t v___x_7412_; 
v___x_7410_ = 2ULL;
v___x_7411_ = lean_uint64_shift_right(v___y_7402_, v___x_7410_);
v___x_7412_ = lean_uint64_dec_eq(v___x_7411_, v___y_7407_);
if (v___x_7412_ == 0)
{
v___y_7386_ = v___y_7409_;
v___y_7387_ = v___y_7401_;
v___y_7388_ = v___y_7402_;
v___y_7389_ = v___y_7403_;
v___y_7390_ = v___y_7404_;
v___y_7391_ = v___y_7405_;
v___y_7392_ = v___x_7410_;
v___y_7393_ = v___y_7406_;
v___y_7394_ = v___y_7407_;
v___y_7395_ = v___y_7408_;
v___y_7396_ = v___x_7411_;
goto v___jp_7385_;
}
else
{
v___y_7386_ = v___y_7409_;
v___y_7387_ = v___y_7401_;
v___y_7388_ = v___y_7402_;
v___y_7389_ = v___y_7403_;
v___y_7390_ = v___y_7404_;
v___y_7391_ = v___y_7405_;
v___y_7392_ = v___x_7410_;
v___y_7393_ = v___y_7406_;
v___y_7394_ = v___y_7407_;
v___y_7395_ = v___y_7408_;
v___y_7396_ = v___y_7402_;
goto v___jp_7385_;
}
}
v___jp_7413_:
{
uint64_t v___x_7425_; uint8_t v___x_7426_; 
v___x_7425_ = lean_uint64_shift_right(v___y_7420_, v___y_7415_);
v___x_7426_ = lean_uint64_dec_eq(v___x_7425_, v___y_7422_);
if (v___x_7426_ == 0)
{
uint64_t v___x_7427_; 
v___x_7427_ = lean_uint64_add(v___y_7419_, v___y_7415_);
v___y_7401_ = v___y_7414_;
v___y_7402_ = v___y_7424_;
v___y_7403_ = v___y_7416_;
v___y_7404_ = v___y_7417_;
v___y_7405_ = v___y_7418_;
v___y_7406_ = v___y_7421_;
v___y_7407_ = v___y_7422_;
v___y_7408_ = v___y_7423_;
v___y_7409_ = v___x_7427_;
goto v___jp_7400_;
}
else
{
v___y_7401_ = v___y_7414_;
v___y_7402_ = v___y_7424_;
v___y_7403_ = v___y_7416_;
v___y_7404_ = v___y_7417_;
v___y_7405_ = v___y_7418_;
v___y_7406_ = v___y_7421_;
v___y_7407_ = v___y_7422_;
v___y_7408_ = v___y_7423_;
v___y_7409_ = v___y_7419_;
goto v___jp_7400_;
}
}
v___jp_7428_:
{
uint64_t v___x_7438_; uint64_t v___x_7439_; uint8_t v___x_7440_; 
v___x_7438_ = 4ULL;
v___x_7439_ = lean_uint64_shift_right(v___y_7434_, v___x_7438_);
v___x_7440_ = lean_uint64_dec_eq(v___x_7439_, v___y_7435_);
if (v___x_7440_ == 0)
{
v___y_7414_ = v___y_7429_;
v___y_7415_ = v___x_7438_;
v___y_7416_ = v___y_7430_;
v___y_7417_ = v___y_7431_;
v___y_7418_ = v___y_7432_;
v___y_7419_ = v___y_7437_;
v___y_7420_ = v___y_7434_;
v___y_7421_ = v___y_7433_;
v___y_7422_ = v___y_7435_;
v___y_7423_ = v___y_7436_;
v___y_7424_ = v___x_7439_;
goto v___jp_7413_;
}
else
{
v___y_7414_ = v___y_7429_;
v___y_7415_ = v___x_7438_;
v___y_7416_ = v___y_7430_;
v___y_7417_ = v___y_7431_;
v___y_7418_ = v___y_7432_;
v___y_7419_ = v___y_7437_;
v___y_7420_ = v___y_7434_;
v___y_7421_ = v___y_7433_;
v___y_7422_ = v___y_7435_;
v___y_7423_ = v___y_7436_;
v___y_7424_ = v___y_7434_;
goto v___jp_7413_;
}
}
v___jp_7441_:
{
uint64_t v___x_7453_; uint8_t v___x_7454_; 
v___x_7453_ = lean_uint64_shift_right(v___y_7445_, v___y_7444_);
v___x_7454_ = lean_uint64_dec_eq(v___x_7453_, v___y_7450_);
if (v___x_7454_ == 0)
{
uint64_t v___x_7455_; 
v___x_7455_ = lean_uint64_add(v___y_7449_, v___y_7444_);
v___y_7429_ = v___y_7442_;
v___y_7430_ = v___y_7443_;
v___y_7431_ = v___y_7446_;
v___y_7432_ = v___y_7447_;
v___y_7433_ = v___y_7448_;
v___y_7434_ = v___y_7452_;
v___y_7435_ = v___y_7450_;
v___y_7436_ = v___y_7451_;
v___y_7437_ = v___x_7455_;
goto v___jp_7428_;
}
else
{
v___y_7429_ = v___y_7442_;
v___y_7430_ = v___y_7443_;
v___y_7431_ = v___y_7446_;
v___y_7432_ = v___y_7447_;
v___y_7433_ = v___y_7448_;
v___y_7434_ = v___y_7452_;
v___y_7435_ = v___y_7450_;
v___y_7436_ = v___y_7451_;
v___y_7437_ = v___y_7449_;
goto v___jp_7428_;
}
}
v___jp_7456_:
{
uint64_t v___x_7466_; uint64_t v___x_7467_; uint8_t v___x_7468_; 
v___x_7466_ = 8ULL;
v___x_7467_ = lean_uint64_shift_right(v___y_7459_, v___x_7466_);
v___x_7468_ = lean_uint64_dec_eq(v___x_7467_, v___y_7463_);
if (v___x_7468_ == 0)
{
v___y_7442_ = v___y_7457_;
v___y_7443_ = v___y_7458_;
v___y_7444_ = v___x_7466_;
v___y_7445_ = v___y_7459_;
v___y_7446_ = v___y_7460_;
v___y_7447_ = v___y_7461_;
v___y_7448_ = v___y_7462_;
v___y_7449_ = v___y_7465_;
v___y_7450_ = v___y_7463_;
v___y_7451_ = v___y_7464_;
v___y_7452_ = v___x_7467_;
goto v___jp_7441_;
}
else
{
v___y_7442_ = v___y_7457_;
v___y_7443_ = v___y_7458_;
v___y_7444_ = v___x_7466_;
v___y_7445_ = v___y_7459_;
v___y_7446_ = v___y_7460_;
v___y_7447_ = v___y_7461_;
v___y_7448_ = v___y_7462_;
v___y_7449_ = v___y_7465_;
v___y_7450_ = v___y_7463_;
v___y_7451_ = v___y_7464_;
v___y_7452_ = v___y_7459_;
goto v___jp_7441_;
}
}
v___jp_7469_:
{
uint64_t v___x_7481_; uint8_t v___x_7482_; 
v___x_7481_ = lean_uint64_shift_right(v___y_7477_, v___y_7476_);
v___x_7482_ = lean_uint64_dec_eq(v___x_7481_, v___y_7478_);
if (v___x_7482_ == 0)
{
uint64_t v___x_7483_; 
v___x_7483_ = lean_uint64_add(v___y_7470_, v___y_7476_);
v___y_7457_ = v___y_7471_;
v___y_7458_ = v___y_7472_;
v___y_7459_ = v___y_7480_;
v___y_7460_ = v___y_7473_;
v___y_7461_ = v___y_7474_;
v___y_7462_ = v___y_7475_;
v___y_7463_ = v___y_7478_;
v___y_7464_ = v___y_7479_;
v___y_7465_ = v___x_7483_;
goto v___jp_7456_;
}
else
{
v___y_7457_ = v___y_7471_;
v___y_7458_ = v___y_7472_;
v___y_7459_ = v___y_7480_;
v___y_7460_ = v___y_7473_;
v___y_7461_ = v___y_7474_;
v___y_7462_ = v___y_7475_;
v___y_7463_ = v___y_7478_;
v___y_7464_ = v___y_7479_;
v___y_7465_ = v___y_7470_;
goto v___jp_7456_;
}
}
v___jp_7484_:
{
uint64_t v___x_7494_; uint64_t v___x_7495_; uint8_t v___x_7496_; 
v___x_7494_ = 16ULL;
v___x_7495_ = lean_uint64_shift_right(v___y_7491_, v___x_7494_);
v___x_7496_ = lean_uint64_dec_eq(v___x_7495_, v___y_7490_);
if (v___x_7496_ == 0)
{
v___y_7470_ = v___y_7493_;
v___y_7471_ = v___y_7485_;
v___y_7472_ = v___y_7486_;
v___y_7473_ = v___y_7487_;
v___y_7474_ = v___y_7488_;
v___y_7475_ = v___y_7489_;
v___y_7476_ = v___x_7494_;
v___y_7477_ = v___y_7491_;
v___y_7478_ = v___y_7490_;
v___y_7479_ = v___y_7492_;
v___y_7480_ = v___x_7495_;
goto v___jp_7469_;
}
else
{
v___y_7470_ = v___y_7493_;
v___y_7471_ = v___y_7485_;
v___y_7472_ = v___y_7486_;
v___y_7473_ = v___y_7487_;
v___y_7474_ = v___y_7488_;
v___y_7475_ = v___y_7489_;
v___y_7476_ = v___x_7494_;
v___y_7477_ = v___y_7491_;
v___y_7478_ = v___y_7490_;
v___y_7479_ = v___y_7492_;
v___y_7480_ = v___y_7491_;
goto v___jp_7469_;
}
}
v___jp_7497_:
{
uint64_t v___x_7507_; uint8_t v___x_7508_; 
v___x_7507_ = lean_uint64_shift_right(v___y_7505_, v___y_7498_);
v___x_7508_ = lean_uint64_dec_eq(v___x_7507_, v___y_7504_);
if (v___x_7508_ == 0)
{
v___y_7485_ = v___y_7499_;
v___y_7486_ = v___y_7500_;
v___y_7487_ = v___y_7501_;
v___y_7488_ = v___y_7502_;
v___y_7489_ = v___y_7503_;
v___y_7490_ = v___y_7504_;
v___y_7491_ = v___y_7506_;
v___y_7492_ = v___y_7505_;
v___y_7493_ = v___y_7498_;
goto v___jp_7484_;
}
else
{
v___y_7485_ = v___y_7499_;
v___y_7486_ = v___y_7500_;
v___y_7487_ = v___y_7501_;
v___y_7488_ = v___y_7502_;
v___y_7489_ = v___y_7503_;
v___y_7490_ = v___y_7504_;
v___y_7491_ = v___y_7506_;
v___y_7492_ = v___y_7505_;
v___y_7493_ = v___y_7504_;
goto v___jp_7484_;
}
}
v___jp_7509_:
{
uint64_t v___x_7517_; uint64_t v___x_7518_; uint8_t v___x_7519_; 
v___x_7517_ = 32ULL;
v___x_7518_ = lean_uint64_shift_right(v___y_7516_, v___x_7517_);
v___x_7519_ = lean_uint64_dec_eq(v___x_7518_, v___y_7515_);
if (v___x_7519_ == 0)
{
v___y_7498_ = v___x_7517_;
v___y_7499_ = v___y_7510_;
v___y_7500_ = v___y_7511_;
v___y_7501_ = v___y_7512_;
v___y_7502_ = v___y_7513_;
v___y_7503_ = v___y_7514_;
v___y_7504_ = v___y_7515_;
v___y_7505_ = v___y_7516_;
v___y_7506_ = v___x_7518_;
goto v___jp_7497_;
}
else
{
v___y_7498_ = v___x_7517_;
v___y_7499_ = v___y_7510_;
v___y_7500_ = v___y_7511_;
v___y_7501_ = v___y_7512_;
v___y_7502_ = v___y_7513_;
v___y_7503_ = v___y_7514_;
v___y_7504_ = v___y_7515_;
v___y_7505_ = v___y_7516_;
v___y_7506_ = v___y_7516_;
goto v___jp_7497_;
}
}
v___jp_7520_:
{
uint64_t v___x_7529_; uint64_t v___x_7530_; uint8_t v___x_7531_; 
v___x_7529_ = lean_uint64_mul(v___y_7526_, v___y_7527_);
v___x_7530_ = 0ULL;
v___x_7531_ = lean_uint64_dec_eq(v___x_7529_, v___x_7530_);
if (v___x_7531_ == 0)
{
uint64_t v___x_7532_; uint64_t v___x_7533_; uint8_t v___x_7534_; 
v___x_7532_ = lean_uint64_add(v___y_7524_, v___y_7528_);
v___x_7533_ = 70368744177664ULL;
v___x_7534_ = lean_uint64_dec_le(v___x_7533_, v___x_7529_);
if (v___x_7534_ == 0)
{
v___y_7510_ = v___x_7532_;
v___y_7511_ = v___y_7521_;
v___y_7512_ = v___y_7522_;
v___y_7513_ = v___y_7523_;
v___y_7514_ = v___y_7525_;
v___y_7515_ = v___x_7530_;
v___y_7516_ = v___x_7529_;
goto v___jp_7509_;
}
else
{
uint64_t v___x_7535_; uint8_t v___x_7536_; 
v___x_7535_ = 281474976710656ULL;
v___x_7536_ = lean_uint64_dec_lt(v___x_7529_, v___x_7535_);
if (v___x_7536_ == 0)
{
v___y_7510_ = v___x_7532_;
v___y_7511_ = v___y_7521_;
v___y_7512_ = v___y_7522_;
v___y_7513_ = v___y_7523_;
v___y_7514_ = v___y_7525_;
v___y_7515_ = v___x_7530_;
v___y_7516_ = v___x_7529_;
goto v___jp_7509_;
}
else
{
uint64_t v___x_7537_; uint8_t v___x_7538_; 
v___x_7537_ = 140737488355328ULL;
v___x_7538_ = lean_uint64_dec_lt(v___x_7529_, v___x_7537_);
if (v___x_7538_ == 0)
{
uint64_t v___x_7539_; 
v___x_7539_ = 47ULL;
v___y_7310_ = v___x_7532_;
v___y_7311_ = v___y_7521_;
v___y_7312_ = v___y_7522_;
v___y_7313_ = v___y_7523_;
v___y_7314_ = v___y_7525_;
v___y_7315_ = v___x_7530_;
v___y_7316_ = v___x_7529_;
v___y_7317_ = v___x_7539_;
goto v___jp_7309_;
}
else
{
uint64_t v___x_7540_; 
v___x_7540_ = 46ULL;
v___y_7310_ = v___x_7532_;
v___y_7311_ = v___y_7521_;
v___y_7312_ = v___y_7522_;
v___y_7313_ = v___y_7523_;
v___y_7314_ = v___y_7525_;
v___y_7315_ = v___x_7530_;
v___y_7316_ = v___x_7529_;
v___y_7317_ = v___x_7540_;
goto v___jp_7309_;
}
}
}
}
else
{
if (v___y_7523_ == 0)
{
uint32_t v___x_7541_; 
v___x_7541_ = 0;
v___y_6775_ = v___x_7541_;
goto v___jp_6774_;
}
else
{
uint32_t v___x_7542_; 
v___x_7542_ = 2147483648;
v___y_6775_ = v___x_7542_;
goto v___jp_6774_;
}
}
}
v___jp_7543_:
{
uint64_t v___x_7552_; uint64_t v___x_7553_; uint8_t v___x_7554_; 
v___x_7552_ = lean_uint32_to_uint64(v___y_7545_);
v___x_7553_ = 0ULL;
v___x_7554_ = lean_uint64_dec_eq(v___x_7552_, v___x_7553_);
if (v___x_7554_ == 0)
{
uint64_t v___x_7555_; uint64_t v___x_7556_; 
v___x_7555_ = 1ULL;
v___x_7556_ = lean_uint64_sub(v___x_7552_, v___x_7555_);
v___y_7521_ = v___y_7544_;
v___y_7522_ = v___y_7546_;
v___y_7523_ = v___y_7547_;
v___y_7524_ = v___y_7551_;
v___y_7525_ = v___y_7548_;
v___y_7526_ = v___y_7549_;
v___y_7527_ = v___y_7550_;
v___y_7528_ = v___x_7556_;
goto v___jp_7520_;
}
else
{
v___y_7521_ = v___y_7544_;
v___y_7522_ = v___y_7546_;
v___y_7523_ = v___y_7547_;
v___y_7524_ = v___y_7551_;
v___y_7525_ = v___y_7548_;
v___y_7526_ = v___y_7549_;
v___y_7527_ = v___y_7550_;
v___y_7528_ = v___x_7553_;
goto v___jp_7520_;
}
}
v___jp_7557_:
{
uint64_t v___x_7566_; uint64_t v___x_7567_; uint8_t v___x_7568_; 
v___x_7566_ = lean_uint32_to_uint64(v___y_7562_);
v___x_7567_ = 0ULL;
v___x_7568_ = lean_uint64_dec_eq(v___x_7566_, v___x_7567_);
if (v___x_7568_ == 0)
{
uint64_t v___x_7569_; uint64_t v___x_7570_; 
v___x_7569_ = 1ULL;
v___x_7570_ = lean_uint64_sub(v___x_7566_, v___x_7569_);
v___y_7544_ = v___y_7558_;
v___y_7545_ = v___y_7560_;
v___y_7546_ = v___y_7559_;
v___y_7547_ = v___y_7561_;
v___y_7548_ = v___y_7563_;
v___y_7549_ = v___y_7564_;
v___y_7550_ = v___y_7565_;
v___y_7551_ = v___x_7570_;
goto v___jp_7543_;
}
else
{
v___y_7544_ = v___y_7558_;
v___y_7545_ = v___y_7560_;
v___y_7546_ = v___y_7559_;
v___y_7547_ = v___y_7561_;
v___y_7548_ = v___y_7563_;
v___y_7549_ = v___y_7564_;
v___y_7550_ = v___y_7565_;
v___y_7551_ = v___x_7567_;
goto v___jp_7543_;
}
}
v___jp_7571_:
{
uint32_t v___x_7580_; uint8_t v___x_7581_; 
v___x_7580_ = 0;
v___x_7581_ = lean_uint32_dec_eq(v___y_7573_, v___x_7580_);
if (v___x_7581_ == 0)
{
uint64_t v___x_7582_; uint64_t v___x_7583_; uint64_t v___x_7584_; 
v___x_7582_ = lean_uint32_to_uint64(v___y_7576_);
v___x_7583_ = 8388608ULL;
v___x_7584_ = lean_uint64_lor(v___x_7582_, v___x_7583_);
v___y_7558_ = v___y_7572_;
v___y_7559_ = v___y_7574_;
v___y_7560_ = v___y_7573_;
v___y_7561_ = v___y_7575_;
v___y_7562_ = v___y_7577_;
v___y_7563_ = v___y_7578_;
v___y_7564_ = v___y_7579_;
v___y_7565_ = v___x_7584_;
goto v___jp_7557_;
}
else
{
uint64_t v___x_7585_; 
v___x_7585_ = lean_uint32_to_uint64(v___y_7576_);
v___y_7558_ = v___y_7572_;
v___y_7559_ = v___y_7574_;
v___y_7560_ = v___y_7573_;
v___y_7561_ = v___y_7575_;
v___y_7562_ = v___y_7577_;
v___y_7563_ = v___y_7578_;
v___y_7564_ = v___y_7579_;
v___y_7565_ = v___x_7585_;
goto v___jp_7557_;
}
}
v___jp_7586_:
{
uint32_t v___x_7594_; uint32_t v_xFraction_7595_; uint32_t v_yFraction_7596_; uint32_t v___x_7597_; uint8_t v___x_7598_; 
v___x_7594_ = 8388607;
v_xFraction_7595_ = lean_uint32_land(v___y_7587_, v___x_7594_);
v_yFraction_7596_ = lean_uint32_land(v___y_7588_, v___x_7594_);
v___x_7597_ = 0;
v___x_7598_ = lean_uint32_dec_eq(v___y_7591_, v___x_7597_);
if (v___x_7598_ == 0)
{
uint64_t v___x_7599_; uint64_t v___x_7600_; uint64_t v___x_7601_; 
v___x_7599_ = lean_uint32_to_uint64(v_xFraction_7595_);
v___x_7600_ = 8388608ULL;
v___x_7601_ = lean_uint64_lor(v___x_7599_, v___x_7600_);
v___y_7572_ = v___x_7594_;
v___y_7573_ = v___y_7590_;
v___y_7574_ = v___y_7589_;
v___y_7575_ = v___y_7593_;
v___y_7576_ = v_yFraction_7596_;
v___y_7577_ = v___y_7591_;
v___y_7578_ = v___y_7592_;
v___y_7579_ = v___x_7601_;
goto v___jp_7571_;
}
else
{
uint64_t v___x_7602_; 
v___x_7602_ = lean_uint32_to_uint64(v_xFraction_7595_);
v___y_7572_ = v___x_7594_;
v___y_7573_ = v___y_7590_;
v___y_7574_ = v___y_7589_;
v___y_7575_ = v___y_7593_;
v___y_7576_ = v_yFraction_7596_;
v___y_7577_ = v___y_7591_;
v___y_7578_ = v___y_7592_;
v___y_7579_ = v___x_7602_;
goto v___jp_7571_;
}
}
v___jp_7603_:
{
if (v___y_7611_ == 0)
{
v___y_7209_ = v___y_7604_;
v___y_7210_ = v___y_7605_;
v___y_7211_ = v___y_7607_;
v___y_7212_ = v___y_7606_;
v___y_7213_ = v___y_7609_;
v___y_7214_ = v___y_7610_;
v___y_7215_ = v___x_6773_;
goto v___jp_7208_;
}
else
{
v___y_7209_ = v___y_7604_;
v___y_7210_ = v___y_7605_;
v___y_7211_ = v___y_7607_;
v___y_7212_ = v___y_7606_;
v___y_7213_ = v___y_7609_;
v___y_7214_ = v___y_7610_;
v___y_7215_ = v___y_7608_;
goto v___jp_7208_;
}
}
v___jp_7612_:
{
if (v___y_7617_ == 0)
{
if (v___y_7621_ == 0)
{
v___y_7604_ = v___y_7613_;
v___y_7605_ = v___y_7614_;
v___y_7606_ = v___y_7616_;
v___y_7607_ = v___y_7615_;
v___y_7608_ = v___y_7618_;
v___y_7609_ = v___y_7619_;
v___y_7610_ = v___y_7620_;
v___y_7611_ = v___x_6773_;
goto v___jp_7603_;
}
else
{
v___y_7209_ = v___y_7613_;
v___y_7210_ = v___y_7614_;
v___y_7211_ = v___y_7615_;
v___y_7212_ = v___y_7616_;
v___y_7213_ = v___y_7619_;
v___y_7214_ = v___y_7620_;
v___y_7215_ = v___x_6773_;
goto v___jp_7208_;
}
}
else
{
v___y_7604_ = v___y_7613_;
v___y_7605_ = v___y_7614_;
v___y_7606_ = v___y_7616_;
v___y_7607_ = v___y_7615_;
v___y_7608_ = v___y_7618_;
v___y_7609_ = v___y_7619_;
v___y_7610_ = v___y_7620_;
v___y_7611_ = v___y_7621_;
goto v___jp_7603_;
}
}
v___jp_7622_:
{
uint32_t v___x_7631_; uint32_t v___x_7632_; uint32_t v___x_7633_; uint8_t v___x_7634_; 
v___x_7631_ = 2147483648;
v___x_7632_ = lean_uint32_land(v___y_7624_, v___x_7631_);
v___x_7633_ = 0;
v___x_7634_ = lean_uint32_dec_eq(v___x_7632_, v___x_7633_);
if (v___x_7634_ == 0)
{
v___y_7613_ = v___y_7623_;
v___y_7614_ = v___y_7624_;
v___y_7615_ = v___y_7626_;
v___y_7616_ = v___y_7625_;
v___y_7617_ = v___y_7630_;
v___y_7618_ = v___y_7627_;
v___y_7619_ = v___y_7628_;
v___y_7620_ = v___y_7629_;
v___y_7621_ = v___x_6773_;
goto v___jp_7612_;
}
else
{
v___y_7613_ = v___y_7623_;
v___y_7614_ = v___y_7624_;
v___y_7615_ = v___y_7626_;
v___y_7616_ = v___y_7625_;
v___y_7617_ = v___y_7630_;
v___y_7618_ = v___y_7627_;
v___y_7619_ = v___y_7628_;
v___y_7620_ = v___y_7629_;
v___y_7621_ = v___y_7627_;
goto v___jp_7612_;
}
}
v___jp_7635_:
{
if (v___y_7642_ == 0)
{
uint32_t v___x_7643_; uint32_t v___x_7644_; uint32_t v___x_7645_; uint8_t v___x_7646_; 
v___x_7643_ = 2147483648;
v___x_7644_ = lean_uint32_land(v___y_7636_, v___x_7643_);
v___x_7645_ = 0;
v___x_7646_ = lean_uint32_dec_eq(v___x_7644_, v___x_7645_);
if (v___x_7646_ == 0)
{
v___y_7623_ = v___y_7636_;
v___y_7624_ = v___y_7637_;
v___y_7625_ = v___y_7639_;
v___y_7626_ = v___y_7638_;
v___y_7627_ = v___y_7642_;
v___y_7628_ = v___y_7640_;
v___y_7629_ = v___y_7641_;
v___y_7630_ = v___x_6773_;
goto v___jp_7622_;
}
else
{
v___y_7623_ = v___y_7636_;
v___y_7624_ = v___y_7637_;
v___y_7625_ = v___y_7639_;
v___y_7626_ = v___y_7638_;
v___y_7627_ = v___y_7642_;
v___y_7628_ = v___y_7640_;
v___y_7629_ = v___y_7641_;
v___y_7630_ = v___y_7642_;
goto v___jp_7622_;
}
}
else
{
lean_object* v___x_7647_; lean_object* v___x_7648_; lean_object* v___x_7649_; uint32_t v___x_7650_; 
v___x_7647_ = lean_uint32_to_nat(v___y_7636_);
v___x_7648_ = lean_uint32_to_nat(v___y_7637_);
v___x_7649_ = lp_floatlib_FloatLib_Floats_Formats_BinaryInterchange_Model_MulBackend_word___at___00FloatLib_Floats_Formats_BinaryInterchange_Configured_Plan_softwareMul32Certified_spec__1(v___x_7647_, v___x_7648_);
v___x_7650_ = lean_uint32_of_nat(v___x_7649_);
lean_dec(v___x_7649_);
v___y_6775_ = v___x_7650_;
goto v___jp_6774_;
}
}
v___jp_7651_:
{
if (v___y_7659_ == 0)
{
v___y_7587_ = v___y_7652_;
v___y_7588_ = v___y_7653_;
v___y_7589_ = v___y_7655_;
v___y_7590_ = v___y_7654_;
v___y_7591_ = v___y_7656_;
v___y_7592_ = v___y_7657_;
v___y_7593_ = v___x_6773_;
goto v___jp_7586_;
}
else
{
v___y_7587_ = v___y_7652_;
v___y_7588_ = v___y_7653_;
v___y_7589_ = v___y_7655_;
v___y_7590_ = v___y_7654_;
v___y_7591_ = v___y_7656_;
v___y_7592_ = v___y_7657_;
v___y_7593_ = v___y_7658_;
goto v___jp_7586_;
}
}
v___jp_7660_:
{
if (v___y_7663_ == 0)
{
if (v___y_7669_ == 0)
{
v___y_7652_ = v___y_7661_;
v___y_7653_ = v___y_7662_;
v___y_7654_ = v___y_7665_;
v___y_7655_ = v___y_7664_;
v___y_7656_ = v___y_7666_;
v___y_7657_ = v___y_7667_;
v___y_7658_ = v___y_7668_;
v___y_7659_ = v___x_6773_;
goto v___jp_7651_;
}
else
{
v___y_7587_ = v___y_7661_;
v___y_7588_ = v___y_7662_;
v___y_7589_ = v___y_7664_;
v___y_7590_ = v___y_7665_;
v___y_7591_ = v___y_7666_;
v___y_7592_ = v___y_7667_;
v___y_7593_ = v___x_6773_;
goto v___jp_7586_;
}
}
else
{
v___y_7652_ = v___y_7661_;
v___y_7653_ = v___y_7662_;
v___y_7654_ = v___y_7665_;
v___y_7655_ = v___y_7664_;
v___y_7656_ = v___y_7666_;
v___y_7657_ = v___y_7667_;
v___y_7658_ = v___y_7668_;
v___y_7659_ = v___y_7669_;
goto v___jp_7651_;
}
}
v___jp_7670_:
{
uint32_t v___x_7679_; uint32_t v___x_7680_; uint32_t v___x_7681_; uint8_t v___x_7682_; 
v___x_7679_ = 2147483648;
v___x_7680_ = lean_uint32_land(v___y_7672_, v___x_7679_);
v___x_7681_ = 0;
v___x_7682_ = lean_uint32_dec_eq(v___x_7680_, v___x_7681_);
if (v___x_7682_ == 0)
{
v___y_7661_ = v___y_7671_;
v___y_7662_ = v___y_7672_;
v___y_7663_ = v___y_7678_;
v___y_7664_ = v___y_7674_;
v___y_7665_ = v___y_7673_;
v___y_7666_ = v___y_7675_;
v___y_7667_ = v___y_7676_;
v___y_7668_ = v___y_7677_;
v___y_7669_ = v___x_6773_;
goto v___jp_7660_;
}
else
{
v___y_7661_ = v___y_7671_;
v___y_7662_ = v___y_7672_;
v___y_7663_ = v___y_7678_;
v___y_7664_ = v___y_7674_;
v___y_7665_ = v___y_7673_;
v___y_7666_ = v___y_7675_;
v___y_7667_ = v___y_7676_;
v___y_7668_ = v___y_7677_;
v___y_7669_ = v___y_7677_;
goto v___jp_7660_;
}
}
v___jp_7683_:
{
if (v___y_7690_ == 0)
{
uint32_t v___x_7691_; uint32_t v___x_7692_; uint32_t v___x_7693_; uint8_t v___x_7694_; 
v___x_7691_ = 2147483648;
v___x_7692_ = lean_uint32_land(v___y_7684_, v___x_7691_);
v___x_7693_ = 0;
v___x_7694_ = lean_uint32_dec_eq(v___x_7692_, v___x_7693_);
if (v___x_7694_ == 0)
{
v___y_7671_ = v___y_7684_;
v___y_7672_ = v___y_7685_;
v___y_7673_ = v___y_7687_;
v___y_7674_ = v___y_7686_;
v___y_7675_ = v___y_7688_;
v___y_7676_ = v___y_7689_;
v___y_7677_ = v___y_7690_;
v___y_7678_ = v___x_6773_;
goto v___jp_7670_;
}
else
{
v___y_7671_ = v___y_7684_;
v___y_7672_ = v___y_7685_;
v___y_7673_ = v___y_7687_;
v___y_7674_ = v___y_7686_;
v___y_7675_ = v___y_7688_;
v___y_7676_ = v___y_7689_;
v___y_7677_ = v___y_7690_;
v___y_7678_ = v___y_7690_;
goto v___jp_7670_;
}
}
else
{
lean_object* v___x_7695_; lean_object* v___x_7696_; lean_object* v___x_7697_; uint32_t v___x_7698_; 
v___x_7695_ = lean_uint32_to_nat(v___y_7684_);
v___x_7696_ = lean_uint32_to_nat(v___y_7685_);
v___x_7697_ = lp_floatlib_FloatLib_Floats_Formats_BinaryInterchange_Model_MulBackend_word___at___00FloatLib_Floats_Formats_BinaryInterchange_Configured_Plan_softwareMul32Certified_spec__1(v___x_7695_, v___x_7696_);
v___x_7698_ = lean_uint32_of_nat(v___x_7697_);
lean_dec(v___x_7697_);
v___y_6775_ = v___x_7698_;
goto v___jp_6774_;
}
}
v___jp_7699_:
{
uint32_t v___x_7702_; uint32_t v___x_7703_; uint32_t v___x_7704_; uint32_t v_ex_7705_; uint32_t v___x_7706_; uint32_t v_ey_7707_; uint32_t v___x_7708_; uint32_t v___x_7709_; uint8_t v___x_7710_; 
v___x_7702_ = 23;
v___x_7703_ = lean_uint32_shift_right(v___y_7700_, v___x_7702_);
v___x_7704_ = 255;
v_ex_7705_ = lean_uint32_land(v___x_7703_, v___x_7704_);
v___x_7706_ = lean_uint32_shift_right(v___y_7701_, v___x_7702_);
v_ey_7707_ = lean_uint32_land(v___x_7706_, v___x_7704_);
v___x_7708_ = lean_uint32_add(v_ex_7705_, v_ey_7707_);
v___x_7709_ = 128;
v___x_7710_ = lean_uint32_dec_lt(v___x_7708_, v___x_7709_);
if (v___x_7710_ == 0)
{
uint32_t v___x_7711_; uint32_t v___x_7712_; uint32_t v___x_7713_; uint8_t v___x_7714_; 
v___x_7711_ = 4278190080;
v___x_7712_ = 1;
v___x_7713_ = lean_uint32_shift_left(v___y_7700_, v___x_7712_);
v___x_7714_ = lean_uint32_dec_le(v___x_7711_, v___x_7713_);
if (v___x_7714_ == 0)
{
uint32_t v___x_7715_; uint8_t v___x_7716_; 
v___x_7715_ = lean_uint32_shift_left(v___y_7701_, v___x_7712_);
v___x_7716_ = lean_uint32_dec_le(v___x_7711_, v___x_7715_);
v___y_7684_ = v___y_7700_;
v___y_7685_ = v___y_7701_;
v___y_7686_ = v___x_7702_;
v___y_7687_ = v_ey_7707_;
v___y_7688_ = v_ex_7705_;
v___y_7689_ = v___x_7704_;
v___y_7690_ = v___x_7716_;
goto v___jp_7683_;
}
else
{
v___y_7684_ = v___y_7700_;
v___y_7685_ = v___y_7701_;
v___y_7686_ = v___x_7702_;
v___y_7687_ = v_ey_7707_;
v___y_7688_ = v_ex_7705_;
v___y_7689_ = v___x_7704_;
v___y_7690_ = v___x_7714_;
goto v___jp_7683_;
}
}
else
{
uint32_t v___x_7717_; uint32_t v___x_7718_; uint32_t v___x_7719_; uint8_t v___x_7720_; 
v___x_7717_ = 4278190080;
v___x_7718_ = 1;
v___x_7719_ = lean_uint32_shift_left(v___y_7700_, v___x_7718_);
v___x_7720_ = lean_uint32_dec_le(v___x_7717_, v___x_7719_);
if (v___x_7720_ == 0)
{
uint32_t v___x_7721_; uint8_t v___x_7722_; 
v___x_7721_ = lean_uint32_shift_left(v___y_7701_, v___x_7718_);
v___x_7722_ = lean_uint32_dec_le(v___x_7717_, v___x_7721_);
v___y_7636_ = v___y_7700_;
v___y_7637_ = v___y_7701_;
v___y_7638_ = v___x_7702_;
v___y_7639_ = v_ey_7707_;
v___y_7640_ = v_ex_7705_;
v___y_7641_ = v___x_7704_;
v___y_7642_ = v___x_7722_;
goto v___jp_7635_;
}
else
{
v___y_7636_ = v___y_7700_;
v___y_7637_ = v___y_7701_;
v___y_7638_ = v___x_7702_;
v___y_7639_ = v_ey_7707_;
v___y_7640_ = v_ex_7705_;
v___y_7641_ = v___x_7704_;
v___y_7642_ = v___x_7720_;
goto v___jp_7635_;
}
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_Fin_foldl_loop___at___00Submission_referenceBmm_spec__0___boxed(lean_object* v_A_7742_, lean_object* v_fst_7743_, lean_object* v_m_7744_, lean_object* v_fst_7745_, lean_object* v_n_7746_, lean_object* v_B_7747_, lean_object* v_p_7748_, lean_object* v_snd_7749_, lean_object* v_n_7750_, lean_object* v_x_7751_, lean_object* v_i_7752_){
_start:
{
uint32_t v_x_boxed_7753_; uint32_t v_res_7754_; lean_object* v_r_7755_; 
v_x_boxed_7753_ = lean_unbox_uint32(v_x_7751_);
lean_dec(v_x_7751_);
v_res_7754_ = lp_competition_Fin_foldl_loop___at___00Submission_referenceBmm_spec__0(v_A_7742_, v_fst_7743_, v_m_7744_, v_fst_7745_, v_n_7746_, v_B_7747_, v_p_7748_, v_snd_7749_, v_n_7750_, v_x_boxed_7753_, v_i_7752_);
lean_dec(v_n_7750_);
lean_dec(v_snd_7749_);
lean_dec(v_p_7748_);
lean_dec_ref(v_B_7747_);
lean_dec(v_n_7746_);
lean_dec(v_fst_7745_);
lean_dec(v_m_7744_);
lean_dec(v_fst_7743_);
lean_dec_ref(v_A_7742_);
v_r_7755_ = lean_box_uint32(v_res_7754_);
return v_r_7755_;
}
}
LEAN_EXPORT uint32_t lp_competition_Submission_referenceBmm___lam__0(lean_object* v_m_7756_, lean_object* v_p_7757_, lean_object* v_A_7758_, lean_object* v_n_7759_, lean_object* v_B_7760_, lean_object* v_q_7761_){
_start:
{
lean_object* v___x_7762_; lean_object* v_snd_7763_; lean_object* v_fst_7764_; lean_object* v_fst_7765_; lean_object* v_snd_7766_; lean_object* v___x_7767_; uint32_t v___x_7768_; uint32_t v___x_7769_; 
v___x_7762_ = lp_competition_Competition_bmmDecodeC(v_m_7756_, v_p_7757_, v_q_7761_);
v_snd_7763_ = lean_ctor_get(v___x_7762_, 1);
lean_inc(v_snd_7763_);
v_fst_7764_ = lean_ctor_get(v___x_7762_, 0);
lean_inc(v_fst_7764_);
lean_dec_ref(v___x_7762_);
v_fst_7765_ = lean_ctor_get(v_snd_7763_, 0);
lean_inc(v_fst_7765_);
v_snd_7766_ = lean_ctor_get(v_snd_7763_, 1);
lean_inc(v_snd_7766_);
lean_dec(v_snd_7763_);
v___x_7767_ = lean_unsigned_to_nat(0u);
v___x_7768_ = lean_uint32_once(&lp_competition_Submission_referenceSum___redArg___closed__1, &lp_competition_Submission_referenceSum___redArg___closed__1_once, _init_lp_competition_Submission_referenceSum___redArg___closed__1);
v___x_7769_ = lp_competition_Fin_foldl_loop___at___00Submission_referenceBmm_spec__0(v_A_7758_, v_fst_7764_, v_m_7756_, v_fst_7765_, v_n_7759_, v_B_7760_, v_p_7757_, v_snd_7766_, v_n_7759_, v___x_7768_, v___x_7767_);
lean_dec(v_snd_7766_);
lean_dec(v_fst_7765_);
lean_dec(v_fst_7764_);
return v___x_7769_;
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_referenceBmm___lam__0___boxed(lean_object* v_m_7770_, lean_object* v_p_7771_, lean_object* v_A_7772_, lean_object* v_n_7773_, lean_object* v_B_7774_, lean_object* v_q_7775_){
_start:
{
uint32_t v_res_7776_; lean_object* v_r_7777_; 
v_res_7776_ = lp_competition_Submission_referenceBmm___lam__0(v_m_7770_, v_p_7771_, v_A_7772_, v_n_7773_, v_B_7774_, v_q_7775_);
lean_dec(v_q_7775_);
lean_dec_ref(v_B_7774_);
lean_dec(v_n_7773_);
lean_dec_ref(v_A_7772_);
lean_dec(v_p_7771_);
lean_dec(v_m_7770_);
v_r_7777_ = lean_box_uint32(v_res_7776_);
return v_r_7777_;
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_referenceBmm(lean_object* v_batch_7778_, lean_object* v_m_7779_, lean_object* v_n_7780_, lean_object* v_p_7781_, lean_object* v_A_7782_, lean_object* v_B_7783_){
_start:
{
lean_object* v___f_7784_; lean_object* v___x_7785_; lean_object* v___x_7786_; lean_object* v___x_7787_; 
lean_inc(v_p_7781_);
lean_inc(v_m_7779_);
v___f_7784_ = lean_alloc_closure((void*)(lp_competition_Submission_referenceBmm___lam__0___boxed), 6, 5);
lean_closure_set(v___f_7784_, 0, v_m_7779_);
lean_closure_set(v___f_7784_, 1, v_p_7781_);
lean_closure_set(v___f_7784_, 2, v_A_7782_);
lean_closure_set(v___f_7784_, 3, v_n_7780_);
lean_closure_set(v___f_7784_, 4, v_B_7783_);
v___x_7785_ = lean_nat_mul(v_batch_7778_, v_m_7779_);
lean_dec(v_m_7779_);
v___x_7786_ = lean_nat_mul(v___x_7785_, v_p_7781_);
lean_dec(v_p_7781_);
lean_dec(v___x_7785_);
v___x_7787_ = l_Array_ofFn___redArg(v___x_7786_, v___f_7784_);
return v___x_7787_;
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_referenceBmm___boxed(lean_object* v_batch_7788_, lean_object* v_m_7789_, lean_object* v_n_7790_, lean_object* v_p_7791_, lean_object* v_A_7792_, lean_object* v_B_7793_){
_start:
{
lean_object* v_res_7794_; 
v_res_7794_ = lp_competition_Submission_referenceBmm(v_batch_7788_, v_m_7789_, v_n_7790_, v_p_7791_, v_A_7792_, v_B_7793_);
lean_dec(v_batch_7788_);
return v_res_7794_;
}
}
LEAN_EXPORT float lp_competition_Submission_NativeFinal_sumLoop(lean_object* v_n_7795_, lean_object* v_x_7796_, lean_object* v_k_7797_, float v_acc_7798_){
_start:
{
uint8_t v___x_7799_; 
v___x_7799_ = lean_nat_dec_lt(v_k_7797_, v_n_7795_);
if (v___x_7799_ == 0)
{
lean_dec(v_k_7797_);
return v_acc_7798_;
}
else
{
lean_object* v___x_7800_; lean_object* v___x_7801_; lean_object* v___x_7802_; uint32_t v___x_7803_; float v___x_7804_; float v___x_7805_; 
v___x_7800_ = lean_unsigned_to_nat(1u);
v___x_7801_ = lean_nat_add(v_k_7797_, v___x_7800_);
v___x_7802_ = lean_array_fget_borrowed(v_x_7796_, v_k_7797_);
lean_dec(v_k_7797_);
v___x_7803_ = lean_unbox_uint32(v___x_7802_);
v___x_7804_ = lean_float32_of_bits(v___x_7803_);
v___x_7805_ = lean_float32_add(v_acc_7798_, v___x_7804_);
v_k_7797_ = v___x_7801_;
v_acc_7798_ = v___x_7805_;
goto _start;
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_NativeFinal_sumLoop___boxed(lean_object* v_n_7807_, lean_object* v_x_7808_, lean_object* v_k_7809_, lean_object* v_acc_7810_){
_start:
{
float v_acc_boxed_7811_; float v_res_7812_; lean_object* v_r_7813_; 
v_acc_boxed_7811_ = lean_unbox_float32(v_acc_7810_);
lean_dec_ref(v_acc_7810_);
v_res_7812_ = lp_competition_Submission_NativeFinal_sumLoop(v_n_7807_, v_x_7808_, v_k_7809_, v_acc_boxed_7811_);
lean_dec_ref(v_x_7808_);
lean_dec(v_n_7807_);
v_r_7813_ = lean_box_float32(v_res_7812_);
return v_r_7813_;
}
}
LEAN_EXPORT float lp_competition_Submission_NativeFinal_dotLoop(lean_object* v_n_7814_, lean_object* v_baseA_7815_, lean_object* v_baseB_7816_, lean_object* v_p_7817_, lean_object* v_A_7818_, lean_object* v_B_7819_, lean_object* v_k_7820_, float v_acc_7821_){
_start:
{
float v___y_7823_; uint32_t v___y_7824_; uint8_t v___x_7831_; 
v___x_7831_ = lean_nat_dec_lt(v_k_7820_, v_n_7814_);
if (v___x_7831_ == 0)
{
lean_dec(v_k_7820_);
return v_acc_7821_;
}
else
{
lean_object* v___x_7832_; uint32_t v___x_7833_; uint32_t v___y_7835_; lean_object* v___x_7843_; uint8_t v___x_7844_; 
v___x_7832_ = lean_nat_add(v_baseA_7815_, v_k_7820_);
v___x_7833_ = lean_uint32_once(&lp_competition_Submission_referenceSum___redArg___closed__1, &lp_competition_Submission_referenceSum___redArg___closed__1_once, _init_lp_competition_Submission_referenceSum___redArg___closed__1);
v___x_7843_ = lean_array_get_size(v_A_7818_);
v___x_7844_ = lean_nat_dec_lt(v___x_7832_, v___x_7843_);
if (v___x_7844_ == 0)
{
lean_dec(v___x_7832_);
v___y_7835_ = v___x_7833_;
goto v___jp_7834_;
}
else
{
lean_object* v___x_7845_; uint32_t v___x_7846_; 
v___x_7845_ = lean_array_fget_borrowed(v_A_7818_, v___x_7832_);
lean_dec(v___x_7832_);
v___x_7846_ = lean_unbox_uint32(v___x_7845_);
v___y_7835_ = v___x_7846_;
goto v___jp_7834_;
}
v___jp_7834_:
{
float v_fa_7836_; lean_object* v___x_7837_; lean_object* v___x_7838_; lean_object* v___x_7839_; uint8_t v___x_7840_; 
v_fa_7836_ = lean_float32_of_bits(v___y_7835_);
v___x_7837_ = lean_nat_mul(v_k_7820_, v_p_7817_);
v___x_7838_ = lean_nat_add(v_baseB_7816_, v___x_7837_);
lean_dec(v___x_7837_);
v___x_7839_ = lean_array_get_size(v_B_7819_);
v___x_7840_ = lean_nat_dec_lt(v___x_7838_, v___x_7839_);
if (v___x_7840_ == 0)
{
lean_dec(v___x_7838_);
v___y_7823_ = v_fa_7836_;
v___y_7824_ = v___x_7833_;
goto v___jp_7822_;
}
else
{
lean_object* v___x_7841_; uint32_t v___x_7842_; 
v___x_7841_ = lean_array_fget_borrowed(v_B_7819_, v___x_7838_);
lean_dec(v___x_7838_);
v___x_7842_ = lean_unbox_uint32(v___x_7841_);
v___y_7823_ = v_fa_7836_;
v___y_7824_ = v___x_7842_;
goto v___jp_7822_;
}
}
}
v___jp_7822_:
{
float v_fb_7825_; lean_object* v___x_7826_; lean_object* v___x_7827_; float v___x_7828_; float v___x_7829_; 
v_fb_7825_ = lean_float32_of_bits(v___y_7824_);
v___x_7826_ = lean_unsigned_to_nat(1u);
v___x_7827_ = lean_nat_add(v_k_7820_, v___x_7826_);
lean_dec(v_k_7820_);
v___x_7828_ = lean_float32_mul(v___y_7823_, v_fb_7825_);
v___x_7829_ = lean_float32_add(v_acc_7821_, v___x_7828_);
v_k_7820_ = v___x_7827_;
v_acc_7821_ = v___x_7829_;
goto _start;
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_NativeFinal_dotLoop___boxed(lean_object* v_n_7847_, lean_object* v_baseA_7848_, lean_object* v_baseB_7849_, lean_object* v_p_7850_, lean_object* v_A_7851_, lean_object* v_B_7852_, lean_object* v_k_7853_, lean_object* v_acc_7854_){
_start:
{
float v_acc_boxed_7855_; float v_res_7856_; lean_object* v_r_7857_; 
v_acc_boxed_7855_ = lean_unbox_float32(v_acc_7854_);
lean_dec_ref(v_acc_7854_);
v_res_7856_ = lp_competition_Submission_NativeFinal_dotLoop(v_n_7847_, v_baseA_7848_, v_baseB_7849_, v_p_7850_, v_A_7851_, v_B_7852_, v_k_7853_, v_acc_boxed_7855_);
lean_dec_ref(v_B_7852_);
lean_dec_ref(v_A_7851_);
lean_dec(v_p_7850_);
lean_dec(v_baseB_7849_);
lean_dec(v_baseA_7848_);
lean_dec(v_n_7847_);
v_r_7857_ = lean_box_float32(v_res_7856_);
return v_r_7857_;
}
}
LEAN_EXPORT uint32_t lp_competition_Fin_foldl_loop___at___00Submission_NativeFinal_dot_spec__0(lean_object* v_baseA_7858_, lean_object* v_p_7859_, lean_object* v_baseB_7860_, lean_object* v_B_7861_, lean_object* v_A_7862_, lean_object* v_n_7863_, uint32_t v_x_7864_, lean_object* v_i_7865_){
_start:
{
uint32_t v___y_7867_; float v___y_7872_; float v___y_7873_; float v___y_7877_; uint32_t v___y_7878_; uint8_t v___y_7879_; uint32_t v___y_7894_; float v___y_7895_; uint32_t v___y_7905_; uint8_t v___y_7906_; uint32_t v___y_7921_; uint8_t v___x_7923_; uint32_t v___y_7925_; uint32_t v___y_7944_; uint32_t v___y_7948_; uint32_t v___y_7952_; uint32_t v___y_7956_; uint32_t v___y_7957_; uint32_t v___y_7958_; uint32_t v___y_7962_; uint64_t v___y_7963_; uint8_t v___y_7964_; uint64_t v___y_7965_; uint32_t v___y_7977_; uint32_t v___y_7978_; uint32_t v___y_7979_; uint32_t v___y_7980_; uint32_t v___y_7981_; uint32_t v___y_7982_; uint32_t v___y_7989_; uint32_t v___y_7990_; uint32_t v___y_7991_; uint8_t v___y_7992_; uint32_t v___y_7993_; uint32_t v___y_7994_; uint32_t v___y_7998_; uint64_t v___y_7999_; uint32_t v___y_8000_; uint64_t v___y_8001_; uint32_t v___y_8002_; uint8_t v___y_8003_; uint64_t v___y_8004_; uint32_t v___y_8014_; uint64_t v___y_8015_; uint32_t v___y_8016_; uint8_t v___y_8017_; uint64_t v___y_8018_; uint32_t v___y_8019_; uint8_t v___y_8020_; uint64_t v___y_8021_; uint64_t v___y_8028_; uint32_t v___y_8029_; uint64_t v___y_8030_; uint32_t v___y_8031_; uint32_t v___y_8032_; uint8_t v___y_8033_; uint64_t v___y_8034_; uint32_t v___y_8040_; uint64_t v___y_8041_; uint32_t v___y_8042_; uint32_t v___y_8043_; uint8_t v___y_8044_; uint64_t v___y_8045_; uint64_t v___y_8046_; uint64_t v___y_8047_; uint32_t v___y_8102_; uint64_t v___y_8103_; uint32_t v___y_8104_; uint32_t v___y_8105_; uint8_t v___y_8106_; uint64_t v___y_8107_; uint64_t v___y_8108_; uint64_t v___y_8109_; uint64_t v___y_8110_; uint64_t v___y_8116_; uint64_t v___y_8117_; uint32_t v___y_8118_; uint64_t v___y_8119_; uint32_t v___y_8120_; uint64_t v___y_8121_; uint32_t v___y_8122_; uint8_t v___y_8123_; uint64_t v___y_8124_; uint64_t v___y_8125_; uint64_t v___y_8126_; uint32_t v___y_8131_; uint64_t v___y_8132_; uint64_t v___y_8133_; uint32_t v___y_8134_; uint32_t v___y_8135_; uint8_t v___y_8136_; uint64_t v___y_8137_; uint64_t v___y_8138_; uint64_t v___y_8139_; uint32_t v___y_8144_; uint64_t v___y_8145_; uint32_t v___y_8146_; uint64_t v___y_8147_; uint32_t v___y_8148_; uint8_t v___y_8149_; uint64_t v___y_8150_; uint64_t v___y_8151_; uint64_t v___y_8152_; uint64_t v___y_8153_; uint64_t v___y_8154_; uint32_t v___y_8159_; uint64_t v___y_8160_; uint32_t v___y_8161_; uint64_t v___y_8162_; uint32_t v___y_8163_; uint8_t v___y_8164_; uint64_t v___y_8165_; uint64_t v___y_8166_; uint64_t v___y_8167_; uint64_t v___y_8172_; uint32_t v___y_8173_; uint64_t v___y_8174_; uint32_t v___y_8175_; uint64_t v___y_8176_; uint64_t v___y_8177_; uint32_t v___y_8178_; uint8_t v___y_8179_; uint64_t v___y_8180_; uint64_t v___y_8181_; uint64_t v___y_8182_; uint32_t v___y_8187_; uint64_t v___y_8188_; uint64_t v___y_8189_; uint32_t v___y_8190_; uint32_t v___y_8191_; uint8_t v___y_8192_; uint64_t v___y_8193_; uint64_t v___y_8194_; uint64_t v___y_8195_; uint32_t v___y_8200_; uint64_t v___y_8201_; uint32_t v___y_8202_; uint32_t v___y_8203_; uint64_t v___y_8204_; uint8_t v___y_8205_; uint64_t v___y_8206_; uint64_t v___y_8207_; uint64_t v___y_8208_; uint64_t v___y_8209_; uint64_t v___y_8210_; uint32_t v___y_8215_; uint64_t v___y_8216_; uint32_t v___y_8217_; uint32_t v___y_8218_; uint8_t v___y_8219_; uint64_t v___y_8220_; uint64_t v___y_8221_; uint64_t v___y_8222_; uint64_t v___y_8223_; uint32_t v___y_8228_; uint64_t v___y_8229_; uint32_t v___y_8230_; uint64_t v___y_8231_; uint32_t v___y_8232_; uint8_t v___y_8233_; uint64_t v___y_8234_; uint64_t v___y_8235_; uint64_t v___y_8236_; uint32_t v___y_8240_; uint32_t v___y_8241_; uint32_t v___y_8242_; uint8_t v___y_8243_; uint64_t v___y_8244_; uint64_t v___y_8245_; uint32_t v___y_8254_; uint32_t v___y_8255_; uint32_t v___y_8256_; uint32_t v___y_8260_; uint64_t v___y_8261_; uint8_t v___y_8262_; uint64_t v___y_8263_; uint64_t v___y_8275_; uint64_t v___y_8276_; uint32_t v___y_8277_; uint32_t v___y_8278_; uint32_t v___y_8279_; uint64_t v___y_8280_; uint8_t v___y_8281_; uint64_t v___y_8282_; uint64_t v___y_8316_; uint32_t v___y_8317_; uint32_t v___y_8318_; uint32_t v___y_8319_; uint32_t v___y_8320_; uint64_t v___y_8321_; uint8_t v___y_8322_; uint64_t v___y_8323_; uint64_t v___y_8330_; uint32_t v___y_8331_; uint32_t v___y_8332_; uint32_t v___y_8333_; uint32_t v___y_8334_; uint32_t v___y_8335_; uint8_t v___y_8336_; uint64_t v___y_8337_; uint32_t v___y_8344_; uint32_t v___y_8345_; uint32_t v___y_8346_; uint32_t v___y_8347_; uint32_t v___y_8348_; uint32_t v___y_8349_; uint8_t v___y_8350_; uint64_t v___y_8351_; uint32_t v___y_8359_; uint32_t v___y_8360_; uint32_t v___y_8361_; uint32_t v___y_8362_; uint32_t v___y_8363_; uint32_t v___y_8364_; uint8_t v___y_8365_; uint32_t v___y_8376_; uint32_t v___y_8377_; uint32_t v___y_8378_; uint64_t v___y_8382_; uint8_t v___y_8383_; uint32_t v___y_8384_; uint64_t v___y_8385_; uint32_t v___y_8397_; uint32_t v___y_8398_; uint32_t v___y_8399_; uint32_t v___y_8400_; uint32_t v___y_8401_; uint32_t v___y_8402_; uint32_t v___y_8409_; uint32_t v___y_8410_; uint32_t v___y_8411_; uint8_t v___y_8412_; uint32_t v___y_8413_; uint32_t v___y_8414_; uint32_t v___y_8418_; uint64_t v___y_8419_; uint64_t v___y_8420_; uint32_t v___y_8421_; uint8_t v___y_8422_; uint32_t v___y_8423_; uint64_t v___y_8424_; uint32_t v___y_8434_; uint64_t v___y_8435_; uint8_t v___y_8436_; uint32_t v___y_8437_; uint64_t v___y_8438_; uint8_t v___y_8439_; uint32_t v___y_8440_; uint64_t v___y_8441_; uint64_t v___y_8448_; uint32_t v___y_8449_; uint64_t v___y_8450_; uint32_t v___y_8451_; uint8_t v___y_8452_; uint32_t v___y_8453_; uint64_t v___y_8454_; uint64_t v___y_8460_; uint32_t v___y_8461_; uint64_t v___y_8462_; uint32_t v___y_8463_; uint64_t v___y_8464_; uint8_t v___y_8465_; uint32_t v___y_8466_; uint64_t v___y_8467_; uint64_t v___y_8522_; uint64_t v___y_8523_; uint32_t v___y_8524_; uint32_t v___y_8525_; uint64_t v___y_8526_; uint64_t v___y_8527_; uint8_t v___y_8528_; uint32_t v___y_8529_; uint64_t v___y_8530_; uint64_t v___y_8536_; uint32_t v___y_8537_; uint64_t v___y_8538_; uint64_t v___y_8539_; uint64_t v___y_8540_; uint32_t v___y_8541_; uint64_t v___y_8542_; uint64_t v___y_8543_; uint8_t v___y_8544_; uint32_t v___y_8545_; uint64_t v___y_8546_; uint64_t v___y_8551_; uint32_t v___y_8552_; uint32_t v___y_8553_; uint64_t v___y_8554_; uint64_t v___y_8555_; uint64_t v___y_8556_; uint8_t v___y_8557_; uint32_t v___y_8558_; uint64_t v___y_8559_; uint64_t v___y_8564_; uint64_t v___y_8565_; uint64_t v___y_8566_; uint32_t v___y_8567_; uint64_t v___y_8568_; uint64_t v___y_8569_; uint64_t v___y_8570_; uint32_t v___y_8571_; uint8_t v___y_8572_; uint32_t v___y_8573_; uint64_t v___y_8574_; uint64_t v___y_8579_; uint32_t v___y_8580_; uint64_t v___y_8581_; uint32_t v___y_8582_; uint64_t v___y_8583_; uint64_t v___y_8584_; uint8_t v___y_8585_; uint32_t v___y_8586_; uint64_t v___y_8587_; uint64_t v___y_8592_; uint64_t v___y_8593_; uint64_t v___y_8594_; uint32_t v___y_8595_; uint64_t v___y_8596_; uint64_t v___y_8597_; uint32_t v___y_8598_; uint64_t v___y_8599_; uint8_t v___y_8600_; uint32_t v___y_8601_; uint64_t v___y_8602_; uint64_t v___y_8607_; uint32_t v___y_8608_; uint32_t v___y_8609_; uint64_t v___y_8610_; uint64_t v___y_8611_; uint8_t v___y_8612_; uint64_t v___y_8613_; uint32_t v___y_8614_; uint64_t v___y_8615_; uint64_t v___y_8620_; uint32_t v___y_8621_; uint64_t v___y_8622_; uint64_t v___y_8623_; uint64_t v___y_8624_; uint32_t v___y_8625_; uint64_t v___y_8626_; uint8_t v___y_8627_; uint64_t v___y_8628_; uint32_t v___y_8629_; uint64_t v___y_8630_; uint64_t v___y_8635_; uint32_t v___y_8636_; uint32_t v___y_8637_; uint64_t v___y_8638_; uint64_t v___y_8639_; uint8_t v___y_8640_; uint32_t v___y_8641_; uint64_t v___y_8642_; uint64_t v___y_8643_; uint64_t v___y_8648_; uint32_t v___y_8649_; uint64_t v___y_8650_; uint64_t v___y_8651_; uint32_t v___y_8652_; uint64_t v___y_8653_; uint8_t v___y_8654_; uint32_t v___y_8655_; uint64_t v___y_8656_; uint64_t v___y_8660_; uint32_t v___y_8661_; uint32_t v___y_8662_; uint64_t v___y_8663_; uint64_t v___y_8664_; uint8_t v___y_8665_; uint32_t v___y_8666_; uint32_t v___y_8671_; uint64_t v___y_8672_; uint64_t v___y_8673_; uint32_t v___y_8674_; uint8_t v___y_8675_; uint64_t v___y_8676_; uint32_t v___y_8677_; uint64_t v___y_8678_; uint32_t v___y_8694_; uint32_t v___y_8695_; uint64_t v___y_8696_; uint32_t v___y_8697_; uint64_t v___y_8698_; uint8_t v___y_8699_; uint32_t v___y_8700_; uint64_t v___y_8701_; uint32_t v___y_8708_; uint32_t v___y_8709_; uint64_t v___y_8710_; uint32_t v___y_8711_; uint32_t v___y_8712_; uint8_t v___y_8713_; uint32_t v___y_8714_; uint64_t v___y_8715_; uint32_t v___y_8722_; uint32_t v___y_8723_; uint32_t v___y_8724_; uint32_t v___y_8725_; uint8_t v___y_8726_; uint32_t v___y_8727_; uint32_t v___y_8728_; uint64_t v___y_8729_; uint32_t v___y_8737_; uint32_t v___y_8738_; uint32_t v___y_8739_; uint32_t v___y_8740_; uint32_t v___y_8741_; uint32_t v___y_8742_; uint8_t v___y_8743_; uint32_t v___y_8754_; uint32_t v___y_8755_; uint32_t v___y_8756_; uint32_t v___y_8757_; uint32_t v___y_8758_; uint32_t v___y_8759_; uint8_t v___y_8760_; uint8_t v___y_8761_; uint32_t v___y_8763_; uint8_t v___y_8764_; uint32_t v___y_8765_; uint32_t v___y_8766_; uint32_t v___y_8767_; uint32_t v___y_8768_; uint32_t v___y_8769_; uint8_t v___y_8770_; uint8_t v___y_8771_; uint32_t v___y_8773_; uint32_t v___y_8774_; uint32_t v___y_8775_; uint32_t v___y_8776_; uint32_t v___y_8777_; uint32_t v___y_8778_; uint8_t v___y_8779_; uint8_t v___y_8780_; uint32_t v___y_8786_; uint32_t v___y_8787_; uint32_t v___y_8788_; uint32_t v___y_8789_; uint32_t v___y_8790_; uint32_t v___y_8791_; uint8_t v___y_8792_; uint32_t v___y_8802_; uint32_t v___y_8803_; uint32_t v___y_8804_; uint32_t v___y_8805_; uint32_t v___y_8806_; uint8_t v___y_8807_; uint32_t v___y_8808_; uint8_t v___y_8809_; uint32_t v___y_8811_; uint32_t v___y_8812_; uint32_t v___y_8813_; uint32_t v___y_8814_; uint32_t v___y_8815_; uint32_t v___y_8816_; uint8_t v___y_8817_; uint8_t v___y_8818_; uint8_t v___y_8819_; uint32_t v___y_8821_; uint32_t v___y_8822_; uint32_t v___y_8823_; uint32_t v___y_8824_; uint32_t v___y_8825_; uint8_t v___y_8826_; uint32_t v___y_8827_; uint8_t v___y_8828_; uint32_t v___y_8834_; uint32_t v___y_8835_; uint32_t v___y_8836_; uint32_t v___y_8837_; uint32_t v___y_8838_; uint32_t v___y_8839_; uint8_t v___y_8840_; uint32_t v___y_8850_; uint32_t v___y_8851_; 
v___x_7923_ = lean_nat_dec_lt(v_i_7865_, v_n_7863_);
if (v___x_7923_ == 0)
{
lean_dec(v_i_7865_);
return v_x_7864_;
}
else
{
lean_object* v___x_8873_; uint32_t v___x_8874_; uint32_t v___y_8876_; lean_object* v___x_8883_; uint8_t v___x_8884_; 
v___x_8873_ = lean_nat_add(v_baseA_7858_, v_i_7865_);
v___x_8874_ = lean_uint32_once(&lp_competition_Submission_referenceSum___redArg___closed__1, &lp_competition_Submission_referenceSum___redArg___closed__1_once, _init_lp_competition_Submission_referenceSum___redArg___closed__1);
v___x_8883_ = lean_array_get_size(v_A_7862_);
v___x_8884_ = lean_nat_dec_lt(v___x_8873_, v___x_8883_);
if (v___x_8884_ == 0)
{
lean_dec(v___x_8873_);
v___y_8876_ = v___x_8874_;
goto v___jp_8875_;
}
else
{
lean_object* v___x_8885_; uint32_t v___x_8886_; 
v___x_8885_ = lean_array_fget_borrowed(v_A_7862_, v___x_8873_);
lean_dec(v___x_8873_);
v___x_8886_ = lean_unbox_uint32(v___x_8885_);
v___y_8876_ = v___x_8886_;
goto v___jp_8875_;
}
v___jp_8875_:
{
lean_object* v___x_8877_; lean_object* v___x_8878_; lean_object* v___x_8879_; uint8_t v___x_8880_; 
v___x_8877_ = lean_nat_mul(v_i_7865_, v_p_7859_);
v___x_8878_ = lean_nat_add(v_baseB_7860_, v___x_8877_);
lean_dec(v___x_8877_);
v___x_8879_ = lean_array_get_size(v_B_7861_);
v___x_8880_ = lean_nat_dec_lt(v___x_8878_, v___x_8879_);
if (v___x_8880_ == 0)
{
lean_dec(v___x_8878_);
v___y_8850_ = v___y_8876_;
v___y_8851_ = v___x_8874_;
goto v___jp_8849_;
}
else
{
lean_object* v___x_8881_; uint32_t v___x_8882_; 
v___x_8881_ = lean_array_fget_borrowed(v_B_7861_, v___x_8878_);
lean_dec(v___x_8878_);
v___x_8882_ = lean_unbox_uint32(v___x_8881_);
v___y_8850_ = v___y_8876_;
v___y_8851_ = v___x_8882_;
goto v___jp_8849_;
}
}
}
v___jp_7866_:
{
lean_object* v___x_7868_; lean_object* v___x_7869_; 
v___x_7868_ = lean_unsigned_to_nat(1u);
v___x_7869_ = lean_nat_add(v_i_7865_, v___x_7868_);
lean_dec(v_i_7865_);
v_x_7864_ = v___y_7867_;
v_i_7865_ = v___x_7869_;
goto _start;
}
v___jp_7871_:
{
float v___x_7874_; uint32_t v___x_7875_; 
v___x_7874_ = lean_float32_add(v___y_7872_, v___y_7873_);
v___x_7875_ = lean_float32_to_bits(v___x_7874_);
v___y_7867_ = v___x_7875_;
goto v___jp_7866_;
}
v___jp_7876_:
{
if (v___y_7879_ == 0)
{
float v___x_7880_; 
v___x_7880_ = lean_float32_of_bits(v___y_7878_);
v___y_7872_ = v___y_7877_;
v___y_7873_ = v___x_7880_;
goto v___jp_7871_;
}
else
{
uint32_t v___x_7881_; uint32_t v___x_7882_; uint32_t v___x_7883_; uint32_t v___x_7884_; float v___x_7885_; lean_object* v___x_7886_; uint32_t v___x_7887_; uint32_t v___x_7888_; lean_object* v___x_7889_; lean_object* v___x_7890_; float v___x_7891_; float v___x_7892_; 
v___x_7881_ = 8388607;
v___x_7882_ = lean_uint32_land(v___y_7878_, v___x_7881_);
v___x_7883_ = 8388608;
v___x_7884_ = lean_uint32_lor(v___x_7882_, v___x_7883_);
v___x_7885_ = lean_uint32_to_float32(v___x_7884_);
v___x_7886_ = lp_competition_R2W01b_scaleTable;
v___x_7887_ = 23;
v___x_7888_ = lean_uint32_shift_right(v___y_7878_, v___x_7887_);
v___x_7889_ = lean_uint32_to_nat(v___x_7888_);
v___x_7890_ = lean_array_fget_borrowed(v___x_7886_, v___x_7889_);
lean_dec(v___x_7889_);
v___x_7891_ = lean_unbox_float32(v___x_7890_);
v___x_7892_ = lean_float32_mul(v___x_7885_, v___x_7891_);
v___y_7872_ = v___y_7877_;
v___y_7873_ = v___x_7892_;
goto v___jp_7871_;
}
}
v___jp_7893_:
{
uint32_t v___x_7896_; uint32_t v_a_7897_; uint32_t v___x_7898_; uint32_t v___x_7899_; uint32_t v___x_7900_; uint8_t v___x_7901_; 
v___x_7896_ = 2147483647;
v_a_7897_ = lean_uint32_land(v___y_7894_, v___x_7896_);
v___x_7898_ = 201326591;
v___x_7899_ = 1;
v___x_7900_ = lean_uint32_sub(v_a_7897_, v___x_7899_);
v___x_7901_ = lean_uint32_dec_le(v___x_7898_, v___x_7900_);
if (v___x_7901_ == 0)
{
v___y_7877_ = v___y_7895_;
v___y_7878_ = v___y_7894_;
v___y_7879_ = v___x_7901_;
goto v___jp_7876_;
}
else
{
uint32_t v___x_7902_; uint8_t v___x_7903_; 
v___x_7902_ = 2139095040;
v___x_7903_ = lean_uint32_dec_lt(v_a_7897_, v___x_7902_);
v___y_7877_ = v___y_7895_;
v___y_7878_ = v___y_7894_;
v___y_7879_ = v___x_7903_;
goto v___jp_7876_;
}
}
v___jp_7904_:
{
if (v___y_7906_ == 0)
{
float v___x_7907_; 
v___x_7907_ = lean_float32_of_bits(v_x_7864_);
v___y_7894_ = v___y_7905_;
v___y_7895_ = v___x_7907_;
goto v___jp_7893_;
}
else
{
uint32_t v___x_7908_; uint32_t v___x_7909_; uint32_t v___x_7910_; uint32_t v___x_7911_; float v___x_7912_; lean_object* v___x_7913_; uint32_t v___x_7914_; uint32_t v___x_7915_; lean_object* v___x_7916_; lean_object* v___x_7917_; float v___x_7918_; float v___x_7919_; 
v___x_7908_ = 8388607;
v___x_7909_ = lean_uint32_land(v_x_7864_, v___x_7908_);
v___x_7910_ = 8388608;
v___x_7911_ = lean_uint32_lor(v___x_7909_, v___x_7910_);
v___x_7912_ = lean_uint32_to_float32(v___x_7911_);
v___x_7913_ = lp_competition_R2W01b_scaleTable;
v___x_7914_ = 23;
v___x_7915_ = lean_uint32_shift_right(v_x_7864_, v___x_7914_);
v___x_7916_ = lean_uint32_to_nat(v___x_7915_);
v___x_7917_ = lean_array_fget_borrowed(v___x_7913_, v___x_7916_);
lean_dec(v___x_7916_);
v___x_7918_ = lean_unbox_float32(v___x_7917_);
v___x_7919_ = lean_float32_mul(v___x_7912_, v___x_7918_);
v___y_7894_ = v___y_7905_;
v___y_7895_ = v___x_7919_;
goto v___jp_7893_;
}
}
v___jp_7920_:
{
uint32_t v___x_7922_; 
v___x_7922_ = lp_competition_Submission_TunedAdd_add(v_x_7864_, v___y_7921_);
v___y_7867_ = v___x_7922_;
goto v___jp_7866_;
}
v___jp_7924_:
{
uint32_t v___x_7926_; uint32_t v___x_7927_; uint32_t v___x_7928_; uint32_t v___x_7929_; uint8_t v___x_7930_; 
v___x_7926_ = 23;
v___x_7927_ = lean_uint32_shift_right(v_x_7864_, v___x_7926_);
v___x_7928_ = 255;
v___x_7929_ = lean_uint32_land(v___x_7927_, v___x_7928_);
v___x_7930_ = lean_uint32_dec_eq(v___x_7929_, v___x_7928_);
if (v___x_7930_ == 0)
{
if (v___x_7923_ == 0)
{
v___y_7921_ = v___y_7925_;
goto v___jp_7920_;
}
else
{
uint32_t v___x_7931_; uint32_t v___x_7932_; uint8_t v___x_7933_; 
v___x_7931_ = lean_uint32_shift_right(v___y_7925_, v___x_7926_);
v___x_7932_ = lean_uint32_land(v___x_7931_, v___x_7928_);
v___x_7933_ = lean_uint32_dec_eq(v___x_7932_, v___x_7928_);
if (v___x_7933_ == 0)
{
uint32_t v___x_7934_; uint32_t v_a_7935_; uint32_t v___x_7936_; uint32_t v___x_7937_; uint32_t v___x_7938_; uint8_t v___x_7939_; 
v___x_7934_ = 2147483647;
v_a_7935_ = lean_uint32_land(v_x_7864_, v___x_7934_);
v___x_7936_ = 201326591;
v___x_7937_ = 1;
v___x_7938_ = lean_uint32_sub(v_a_7935_, v___x_7937_);
v___x_7939_ = lean_uint32_dec_le(v___x_7936_, v___x_7938_);
if (v___x_7939_ == 0)
{
v___y_7905_ = v___y_7925_;
v___y_7906_ = v___x_7939_;
goto v___jp_7904_;
}
else
{
uint32_t v___x_7940_; uint8_t v___x_7941_; 
v___x_7940_ = 2139095040;
v___x_7941_ = lean_uint32_dec_lt(v_a_7935_, v___x_7940_);
v___y_7905_ = v___y_7925_;
v___y_7906_ = v___x_7941_;
goto v___jp_7904_;
}
}
else
{
uint32_t v___x_7942_; 
v___x_7942_ = lp_competition_Submission_TunedAdd_add(v_x_7864_, v___y_7925_);
v___y_7867_ = v___x_7942_;
goto v___jp_7866_;
}
}
}
else
{
v___y_7921_ = v___y_7925_;
goto v___jp_7920_;
}
}
v___jp_7943_:
{
uint32_t v___x_7945_; uint32_t v___x_7946_; 
v___x_7945_ = 8388608;
v___x_7946_ = lean_uint32_lor(v___y_7944_, v___x_7945_);
v___y_7925_ = v___x_7946_;
goto v___jp_7924_;
}
v___jp_7947_:
{
uint32_t v___x_7949_; uint32_t v___x_7950_; 
v___x_7949_ = 8388608;
v___x_7950_ = lean_uint32_lor(v___y_7948_, v___x_7949_);
v___y_7925_ = v___x_7950_;
goto v___jp_7924_;
}
v___jp_7951_:
{
uint32_t v___x_7953_; uint32_t v___x_7954_; 
v___x_7953_ = 8388608;
v___x_7954_ = lean_uint32_lor(v___y_7952_, v___x_7953_);
v___y_7925_ = v___x_7954_;
goto v___jp_7924_;
}
v___jp_7955_:
{
uint32_t v___x_7959_; uint32_t v___x_7960_; 
v___x_7959_ = lean_uint32_land(v___y_7957_, v___y_7956_);
v___x_7960_ = lean_uint32_lor(v___y_7958_, v___x_7959_);
v___y_7925_ = v___x_7960_;
goto v___jp_7924_;
}
v___jp_7961_:
{
uint8_t v___x_7966_; 
v___x_7966_ = lean_uint64_dec_eq(v___y_7965_, v___y_7963_);
if (v___x_7966_ == 0)
{
uint64_t v___x_7967_; uint8_t v___x_7968_; 
v___x_7967_ = 8388608ULL;
v___x_7968_ = lean_uint64_dec_eq(v___y_7965_, v___x_7967_);
if (v___x_7968_ == 0)
{
uint32_t v___x_7969_; 
v___x_7969_ = lean_uint64_to_uint32(v___y_7965_);
if (v___y_7964_ == 0)
{
uint32_t v___x_7970_; 
v___x_7970_ = 0;
v___y_7956_ = v___y_7962_;
v___y_7957_ = v___x_7969_;
v___y_7958_ = v___x_7970_;
goto v___jp_7955_;
}
else
{
uint32_t v___x_7971_; 
v___x_7971_ = 2147483648;
v___y_7956_ = v___y_7962_;
v___y_7957_ = v___x_7969_;
v___y_7958_ = v___x_7971_;
goto v___jp_7955_;
}
}
else
{
if (v___y_7964_ == 0)
{
uint32_t v___x_7972_; 
v___x_7972_ = 0;
v___y_7944_ = v___x_7972_;
goto v___jp_7943_;
}
else
{
uint32_t v___x_7973_; 
v___x_7973_ = 2147483648;
v___y_7944_ = v___x_7973_;
goto v___jp_7943_;
}
}
}
else
{
if (v___y_7964_ == 0)
{
uint32_t v___x_7974_; 
v___x_7974_ = 0;
v___y_7925_ = v___x_7974_;
goto v___jp_7924_;
}
else
{
uint32_t v___x_7975_; 
v___x_7975_ = 2147483648;
v___y_7925_ = v___x_7975_;
goto v___jp_7924_;
}
}
}
v___jp_7976_:
{
uint32_t v___x_7983_; uint32_t v___x_7984_; uint32_t v___x_7985_; uint32_t v___x_7986_; uint32_t v___x_7987_; 
v___x_7983_ = lean_uint32_land(v___y_7981_, v___y_7980_);
v___x_7984_ = lean_uint32_shift_left(v___x_7983_, v___y_7979_);
v___x_7985_ = lean_uint32_lor(v___y_7982_, v___x_7984_);
v___x_7986_ = lean_uint32_land(v___y_7977_, v___y_7978_);
v___x_7987_ = lean_uint32_lor(v___x_7985_, v___x_7986_);
v___y_7925_ = v___x_7987_;
goto v___jp_7924_;
}
v___jp_7988_:
{
if (v___y_7992_ == 0)
{
uint32_t v___x_7995_; 
v___x_7995_ = 0;
v___y_7977_ = v___y_7994_;
v___y_7978_ = v___y_7989_;
v___y_7979_ = v___y_7990_;
v___y_7980_ = v___y_7991_;
v___y_7981_ = v___y_7993_;
v___y_7982_ = v___x_7995_;
goto v___jp_7976_;
}
else
{
uint32_t v___x_7996_; 
v___x_7996_ = 2147483648;
v___y_7977_ = v___y_7994_;
v___y_7978_ = v___y_7989_;
v___y_7979_ = v___y_7990_;
v___y_7980_ = v___y_7991_;
v___y_7981_ = v___y_7993_;
v___y_7982_ = v___x_7996_;
goto v___jp_7976_;
}
}
v___jp_7997_:
{
uint64_t v___x_8005_; uint64_t v_encodedExponent_8006_; uint32_t v___x_8007_; uint64_t v___x_8008_; uint8_t v___x_8009_; 
v___x_8005_ = 171ULL;
v_encodedExponent_8006_ = lean_uint64_sub(v___y_8001_, v___x_8005_);
v___x_8007_ = lean_uint64_to_uint32(v_encodedExponent_8006_);
v___x_8008_ = 8388608ULL;
v___x_8009_ = lean_uint64_dec_lt(v___y_8004_, v___x_8008_);
if (v___x_8009_ == 0)
{
uint64_t v___x_8010_; uint32_t v___x_8011_; 
v___x_8010_ = lean_uint64_sub(v___y_8004_, v___x_8008_);
v___x_8011_ = lean_uint64_to_uint32(v___x_8010_);
v___y_7989_ = v___y_7998_;
v___y_7990_ = v___y_8000_;
v___y_7991_ = v___y_8002_;
v___y_7992_ = v___y_8003_;
v___y_7993_ = v___x_8007_;
v___y_7994_ = v___x_8011_;
goto v___jp_7988_;
}
else
{
uint32_t v___x_8012_; 
v___x_8012_ = lean_uint64_to_uint32(v___y_7999_);
v___y_7989_ = v___y_7998_;
v___y_7990_ = v___y_8000_;
v___y_7991_ = v___y_8002_;
v___y_7992_ = v___y_8003_;
v___y_7993_ = v___x_8007_;
v___y_7994_ = v___x_8012_;
goto v___jp_7988_;
}
}
v___jp_8013_:
{
uint64_t v___x_8022_; uint8_t v___x_8023_; 
v___x_8022_ = 425ULL;
v___x_8023_ = lean_uint64_dec_lt(v___x_8022_, v___y_8021_);
if (v___x_8023_ == 0)
{
if (v___y_8017_ == 0)
{
v___y_7998_ = v___y_8014_;
v___y_7999_ = v___y_8015_;
v___y_8000_ = v___y_8016_;
v___y_8001_ = v___y_8021_;
v___y_8002_ = v___y_8019_;
v___y_8003_ = v___y_8020_;
v___y_8004_ = v___y_8018_;
goto v___jp_7997_;
}
else
{
uint64_t v___x_8024_; 
v___x_8024_ = 8388608ULL;
v___y_7998_ = v___y_8014_;
v___y_7999_ = v___y_8015_;
v___y_8000_ = v___y_8016_;
v___y_8001_ = v___y_8021_;
v___y_8002_ = v___y_8019_;
v___y_8003_ = v___y_8020_;
v___y_8004_ = v___x_8024_;
goto v___jp_7997_;
}
}
else
{
if (v___y_8020_ == 0)
{
uint32_t v___x_8025_; 
v___x_8025_ = 2139095040;
v___y_7925_ = v___x_8025_;
goto v___jp_7924_;
}
else
{
uint32_t v___x_8026_; 
v___x_8026_ = 4286578688;
v___y_7925_ = v___x_8026_;
goto v___jp_7924_;
}
}
}
v___jp_8027_:
{
uint64_t v___x_8035_; uint8_t v_carry_8036_; 
v___x_8035_ = 16777216ULL;
v_carry_8036_ = lean_uint64_dec_eq(v___y_8034_, v___x_8035_);
if (v_carry_8036_ == 0)
{
v___y_8014_ = v___y_8029_;
v___y_8015_ = v___y_8030_;
v___y_8016_ = v___y_8031_;
v___y_8017_ = v_carry_8036_;
v___y_8018_ = v___y_8034_;
v___y_8019_ = v___y_8032_;
v___y_8020_ = v___y_8033_;
v___y_8021_ = v___y_8028_;
goto v___jp_8013_;
}
else
{
uint64_t v___x_8037_; uint64_t v___x_8038_; 
v___x_8037_ = 1ULL;
v___x_8038_ = lean_uint64_add(v___y_8028_, v___x_8037_);
v___y_8014_ = v___y_8029_;
v___y_8015_ = v___y_8030_;
v___y_8016_ = v___y_8031_;
v___y_8017_ = v_carry_8036_;
v___y_8018_ = v___y_8034_;
v___y_8019_ = v___y_8032_;
v___y_8020_ = v___y_8033_;
v___y_8021_ = v___x_8038_;
goto v___jp_8013_;
}
}
v___jp_8039_:
{
uint64_t v_position_8048_; uint64_t v___x_8049_; uint8_t v___x_8050_; 
v_position_8048_ = lean_uint64_add(v___y_8047_, v___y_8046_);
v___x_8049_ = 172ULL;
v___x_8050_ = lean_uint64_dec_lt(v_position_8048_, v___x_8049_);
if (v___x_8050_ == 0)
{
uint64_t v___x_8051_; uint8_t v___x_8052_; 
v___x_8051_ = 23ULL;
v___x_8052_ = lean_uint64_dec_lt(v___y_8047_, v___x_8051_);
if (v___x_8052_ == 0)
{
uint64_t v___x_8053_; uint8_t v___x_8054_; 
v___x_8053_ = lean_uint64_sub(v___y_8047_, v___x_8051_);
v___x_8054_ = lean_uint64_dec_eq(v___x_8053_, v___y_8041_);
if (v___x_8054_ == 0)
{
uint64_t v___x_8055_; uint8_t v___x_8056_; 
v___x_8055_ = 64ULL;
v___x_8056_ = lean_uint64_dec_lt(v___x_8053_, v___x_8055_);
if (v___x_8056_ == 0)
{
uint8_t v___x_8057_; 
v___x_8057_ = lean_uint64_dec_eq(v___x_8053_, v___x_8055_);
if (v___x_8057_ == 0)
{
v___y_8028_ = v_position_8048_;
v___y_8029_ = v___y_8040_;
v___y_8030_ = v___y_8041_;
v___y_8031_ = v___y_8042_;
v___y_8032_ = v___y_8043_;
v___y_8033_ = v___y_8044_;
v___y_8034_ = v___y_8041_;
goto v___jp_8027_;
}
else
{
uint64_t v___x_8058_; uint8_t v___x_8059_; 
v___x_8058_ = 9223372036854775808ULL;
v___x_8059_ = lean_uint64_dec_lt(v___x_8058_, v___y_8045_);
if (v___x_8059_ == 0)
{
v___y_8028_ = v_position_8048_;
v___y_8029_ = v___y_8040_;
v___y_8030_ = v___y_8041_;
v___y_8031_ = v___y_8042_;
v___y_8032_ = v___y_8043_;
v___y_8033_ = v___y_8044_;
v___y_8034_ = v___y_8041_;
goto v___jp_8027_;
}
else
{
uint64_t v___x_8060_; 
v___x_8060_ = 1ULL;
v___y_8028_ = v_position_8048_;
v___y_8029_ = v___y_8040_;
v___y_8030_ = v___y_8041_;
v___y_8031_ = v___y_8042_;
v___y_8032_ = v___y_8043_;
v___y_8033_ = v___y_8044_;
v___y_8034_ = v___x_8060_;
goto v___jp_8027_;
}
}
}
else
{
uint64_t v_quotient_8061_; uint64_t v___x_8062_; uint64_t v___x_8063_; uint64_t v___x_8064_; uint64_t v_remainder_8065_; uint64_t v___x_8066_; uint64_t v_half_8067_; uint8_t v___x_8068_; 
v_quotient_8061_ = lean_uint64_shift_right(v___y_8045_, v___x_8053_);
v___x_8062_ = 1ULL;
v___x_8063_ = lean_uint64_shift_left(v___x_8062_, v___x_8053_);
v___x_8064_ = lean_uint64_sub(v___x_8063_, v___x_8062_);
v_remainder_8065_ = lean_uint64_land(v___y_8045_, v___x_8064_);
v___x_8066_ = lean_uint64_sub(v___x_8053_, v___x_8062_);
v_half_8067_ = lean_uint64_shift_left(v___x_8062_, v___x_8066_);
v___x_8068_ = lean_uint64_dec_lt(v_remainder_8065_, v_half_8067_);
if (v___x_8068_ == 0)
{
uint8_t v___x_8069_; 
v___x_8069_ = lean_uint64_dec_lt(v_half_8067_, v_remainder_8065_);
if (v___x_8069_ == 0)
{
uint64_t v___x_8070_; uint8_t v___x_8071_; 
v___x_8070_ = lean_uint64_land(v_quotient_8061_, v___x_8062_);
v___x_8071_ = lean_uint64_dec_eq(v___x_8070_, v___y_8041_);
if (v___x_8071_ == 0)
{
uint64_t v___x_8072_; 
v___x_8072_ = lean_uint64_add(v_quotient_8061_, v___x_8062_);
v___y_8028_ = v_position_8048_;
v___y_8029_ = v___y_8040_;
v___y_8030_ = v___y_8041_;
v___y_8031_ = v___y_8042_;
v___y_8032_ = v___y_8043_;
v___y_8033_ = v___y_8044_;
v___y_8034_ = v___x_8072_;
goto v___jp_8027_;
}
else
{
v___y_8028_ = v_position_8048_;
v___y_8029_ = v___y_8040_;
v___y_8030_ = v___y_8041_;
v___y_8031_ = v___y_8042_;
v___y_8032_ = v___y_8043_;
v___y_8033_ = v___y_8044_;
v___y_8034_ = v_quotient_8061_;
goto v___jp_8027_;
}
}
else
{
uint64_t v___x_8073_; 
v___x_8073_ = lean_uint64_add(v_quotient_8061_, v___x_8062_);
v___y_8028_ = v_position_8048_;
v___y_8029_ = v___y_8040_;
v___y_8030_ = v___y_8041_;
v___y_8031_ = v___y_8042_;
v___y_8032_ = v___y_8043_;
v___y_8033_ = v___y_8044_;
v___y_8034_ = v___x_8073_;
goto v___jp_8027_;
}
}
else
{
v___y_8028_ = v_position_8048_;
v___y_8029_ = v___y_8040_;
v___y_8030_ = v___y_8041_;
v___y_8031_ = v___y_8042_;
v___y_8032_ = v___y_8043_;
v___y_8033_ = v___y_8044_;
v___y_8034_ = v_quotient_8061_;
goto v___jp_8027_;
}
}
}
else
{
v___y_8028_ = v_position_8048_;
v___y_8029_ = v___y_8040_;
v___y_8030_ = v___y_8041_;
v___y_8031_ = v___y_8042_;
v___y_8032_ = v___y_8043_;
v___y_8033_ = v___y_8044_;
v___y_8034_ = v___y_8045_;
goto v___jp_8027_;
}
}
else
{
uint64_t v___x_8074_; uint64_t v___x_8075_; 
v___x_8074_ = lean_uint64_sub(v___x_8051_, v___y_8047_);
v___x_8075_ = lean_uint64_shift_left(v___y_8045_, v___x_8074_);
v___y_8028_ = v_position_8048_;
v___y_8029_ = v___y_8040_;
v___y_8030_ = v___y_8041_;
v___y_8031_ = v___y_8042_;
v___y_8032_ = v___y_8043_;
v___y_8033_ = v___y_8044_;
v___y_8034_ = v___x_8075_;
goto v___jp_8027_;
}
}
else
{
uint64_t v___x_8076_; uint8_t v___x_8077_; 
v___x_8076_ = 149ULL;
v___x_8077_ = lean_uint64_dec_lt(v___y_8046_, v___x_8076_);
if (v___x_8077_ == 0)
{
uint64_t v___x_8078_; uint64_t v___x_8079_; 
v___x_8078_ = lean_uint64_sub(v___y_8046_, v___x_8076_);
v___x_8079_ = lean_uint64_shift_left(v___y_8045_, v___x_8078_);
v___y_7962_ = v___y_8040_;
v___y_7963_ = v___y_8041_;
v___y_7964_ = v___y_8044_;
v___y_7965_ = v___x_8079_;
goto v___jp_7961_;
}
else
{
uint64_t v___x_8080_; uint8_t v___x_8081_; 
v___x_8080_ = lean_uint64_sub(v___x_8076_, v___y_8046_);
v___x_8081_ = lean_uint64_dec_eq(v___x_8080_, v___y_8041_);
if (v___x_8081_ == 0)
{
uint64_t v___x_8082_; uint8_t v___x_8083_; 
v___x_8082_ = 64ULL;
v___x_8083_ = lean_uint64_dec_lt(v___x_8080_, v___x_8082_);
if (v___x_8083_ == 0)
{
uint8_t v___x_8084_; 
v___x_8084_ = lean_uint64_dec_eq(v___x_8080_, v___x_8082_);
if (v___x_8084_ == 0)
{
v___y_7962_ = v___y_8040_;
v___y_7963_ = v___y_8041_;
v___y_7964_ = v___y_8044_;
v___y_7965_ = v___y_8041_;
goto v___jp_7961_;
}
else
{
uint64_t v___x_8085_; uint8_t v___x_8086_; 
v___x_8085_ = 9223372036854775808ULL;
v___x_8086_ = lean_uint64_dec_lt(v___x_8085_, v___y_8045_);
if (v___x_8086_ == 0)
{
v___y_7962_ = v___y_8040_;
v___y_7963_ = v___y_8041_;
v___y_7964_ = v___y_8044_;
v___y_7965_ = v___y_8041_;
goto v___jp_7961_;
}
else
{
uint64_t v___x_8087_; 
v___x_8087_ = 1ULL;
v___y_7962_ = v___y_8040_;
v___y_7963_ = v___y_8041_;
v___y_7964_ = v___y_8044_;
v___y_7965_ = v___x_8087_;
goto v___jp_7961_;
}
}
}
else
{
uint64_t v_quotient_8088_; uint64_t v___x_8089_; uint64_t v___x_8090_; uint64_t v___x_8091_; uint64_t v_remainder_8092_; uint64_t v___x_8093_; uint64_t v_half_8094_; uint8_t v___x_8095_; 
v_quotient_8088_ = lean_uint64_shift_right(v___y_8045_, v___x_8080_);
v___x_8089_ = 1ULL;
v___x_8090_ = lean_uint64_shift_left(v___x_8089_, v___x_8080_);
v___x_8091_ = lean_uint64_sub(v___x_8090_, v___x_8089_);
v_remainder_8092_ = lean_uint64_land(v___y_8045_, v___x_8091_);
v___x_8093_ = lean_uint64_sub(v___x_8080_, v___x_8089_);
v_half_8094_ = lean_uint64_shift_left(v___x_8089_, v___x_8093_);
v___x_8095_ = lean_uint64_dec_lt(v_remainder_8092_, v_half_8094_);
if (v___x_8095_ == 0)
{
uint8_t v___x_8096_; 
v___x_8096_ = lean_uint64_dec_lt(v_half_8094_, v_remainder_8092_);
if (v___x_8096_ == 0)
{
uint64_t v___x_8097_; uint8_t v___x_8098_; 
v___x_8097_ = lean_uint64_land(v_quotient_8088_, v___x_8089_);
v___x_8098_ = lean_uint64_dec_eq(v___x_8097_, v___y_8041_);
if (v___x_8098_ == 0)
{
uint64_t v___x_8099_; 
v___x_8099_ = lean_uint64_add(v_quotient_8088_, v___x_8089_);
v___y_7962_ = v___y_8040_;
v___y_7963_ = v___y_8041_;
v___y_7964_ = v___y_8044_;
v___y_7965_ = v___x_8099_;
goto v___jp_7961_;
}
else
{
v___y_7962_ = v___y_8040_;
v___y_7963_ = v___y_8041_;
v___y_7964_ = v___y_8044_;
v___y_7965_ = v_quotient_8088_;
goto v___jp_7961_;
}
}
else
{
uint64_t v___x_8100_; 
v___x_8100_ = lean_uint64_add(v_quotient_8088_, v___x_8089_);
v___y_7962_ = v___y_8040_;
v___y_7963_ = v___y_8041_;
v___y_7964_ = v___y_8044_;
v___y_7965_ = v___x_8100_;
goto v___jp_7961_;
}
}
else
{
v___y_7962_ = v___y_8040_;
v___y_7963_ = v___y_8041_;
v___y_7964_ = v___y_8044_;
v___y_7965_ = v_quotient_8088_;
goto v___jp_7961_;
}
}
}
else
{
v___y_7962_ = v___y_8040_;
v___y_7963_ = v___y_8041_;
v___y_7964_ = v___y_8044_;
v___y_7965_ = v___y_8045_;
goto v___jp_7961_;
}
}
}
}
v___jp_8101_:
{
uint64_t v___x_8111_; uint64_t v___x_8112_; uint8_t v___x_8113_; 
v___x_8111_ = 1ULL;
v___x_8112_ = lean_uint64_shift_right(v___y_8107_, v___x_8111_);
v___x_8113_ = lean_uint64_dec_eq(v___x_8112_, v___y_8103_);
if (v___x_8113_ == 0)
{
uint64_t v___x_8114_; 
v___x_8114_ = lean_uint64_add(v___y_8110_, v___x_8111_);
v___y_8040_ = v___y_8102_;
v___y_8041_ = v___y_8103_;
v___y_8042_ = v___y_8104_;
v___y_8043_ = v___y_8105_;
v___y_8044_ = v___y_8106_;
v___y_8045_ = v___y_8108_;
v___y_8046_ = v___y_8109_;
v___y_8047_ = v___x_8114_;
goto v___jp_8039_;
}
else
{
v___y_8040_ = v___y_8102_;
v___y_8041_ = v___y_8103_;
v___y_8042_ = v___y_8104_;
v___y_8043_ = v___y_8105_;
v___y_8044_ = v___y_8106_;
v___y_8045_ = v___y_8108_;
v___y_8046_ = v___y_8109_;
v___y_8047_ = v___y_8110_;
goto v___jp_8039_;
}
}
v___jp_8115_:
{
uint64_t v___x_8127_; uint8_t v___x_8128_; 
v___x_8127_ = lean_uint64_shift_right(v___y_8117_, v___y_8116_);
v___x_8128_ = lean_uint64_dec_eq(v___x_8127_, v___y_8119_);
if (v___x_8128_ == 0)
{
uint64_t v___x_8129_; 
v___x_8129_ = lean_uint64_add(v___y_8121_, v___y_8116_);
v___y_8102_ = v___y_8118_;
v___y_8103_ = v___y_8119_;
v___y_8104_ = v___y_8120_;
v___y_8105_ = v___y_8122_;
v___y_8106_ = v___y_8123_;
v___y_8107_ = v___y_8126_;
v___y_8108_ = v___y_8124_;
v___y_8109_ = v___y_8125_;
v___y_8110_ = v___x_8129_;
goto v___jp_8101_;
}
else
{
v___y_8102_ = v___y_8118_;
v___y_8103_ = v___y_8119_;
v___y_8104_ = v___y_8120_;
v___y_8105_ = v___y_8122_;
v___y_8106_ = v___y_8123_;
v___y_8107_ = v___y_8126_;
v___y_8108_ = v___y_8124_;
v___y_8109_ = v___y_8125_;
v___y_8110_ = v___y_8121_;
goto v___jp_8101_;
}
}
v___jp_8130_:
{
uint64_t v___x_8140_; uint64_t v___x_8141_; uint8_t v___x_8142_; 
v___x_8140_ = 2ULL;
v___x_8141_ = lean_uint64_shift_right(v___y_8132_, v___x_8140_);
v___x_8142_ = lean_uint64_dec_eq(v___x_8141_, v___y_8133_);
if (v___x_8142_ == 0)
{
v___y_8116_ = v___x_8140_;
v___y_8117_ = v___y_8132_;
v___y_8118_ = v___y_8131_;
v___y_8119_ = v___y_8133_;
v___y_8120_ = v___y_8134_;
v___y_8121_ = v___y_8139_;
v___y_8122_ = v___y_8135_;
v___y_8123_ = v___y_8136_;
v___y_8124_ = v___y_8137_;
v___y_8125_ = v___y_8138_;
v___y_8126_ = v___x_8141_;
goto v___jp_8115_;
}
else
{
v___y_8116_ = v___x_8140_;
v___y_8117_ = v___y_8132_;
v___y_8118_ = v___y_8131_;
v___y_8119_ = v___y_8133_;
v___y_8120_ = v___y_8134_;
v___y_8121_ = v___y_8139_;
v___y_8122_ = v___y_8135_;
v___y_8123_ = v___y_8136_;
v___y_8124_ = v___y_8137_;
v___y_8125_ = v___y_8138_;
v___y_8126_ = v___y_8132_;
goto v___jp_8115_;
}
}
v___jp_8143_:
{
uint64_t v___x_8155_; uint8_t v___x_8156_; 
v___x_8155_ = lean_uint64_shift_right(v___y_8147_, v___y_8152_);
v___x_8156_ = lean_uint64_dec_eq(v___x_8155_, v___y_8145_);
if (v___x_8156_ == 0)
{
uint64_t v___x_8157_; 
v___x_8157_ = lean_uint64_add(v___y_8151_, v___y_8152_);
v___y_8131_ = v___y_8144_;
v___y_8132_ = v___y_8154_;
v___y_8133_ = v___y_8145_;
v___y_8134_ = v___y_8146_;
v___y_8135_ = v___y_8148_;
v___y_8136_ = v___y_8149_;
v___y_8137_ = v___y_8150_;
v___y_8138_ = v___y_8153_;
v___y_8139_ = v___x_8157_;
goto v___jp_8130_;
}
else
{
v___y_8131_ = v___y_8144_;
v___y_8132_ = v___y_8154_;
v___y_8133_ = v___y_8145_;
v___y_8134_ = v___y_8146_;
v___y_8135_ = v___y_8148_;
v___y_8136_ = v___y_8149_;
v___y_8137_ = v___y_8150_;
v___y_8138_ = v___y_8153_;
v___y_8139_ = v___y_8151_;
goto v___jp_8130_;
}
}
v___jp_8158_:
{
uint64_t v___x_8168_; uint64_t v___x_8169_; uint8_t v___x_8170_; 
v___x_8168_ = 4ULL;
v___x_8169_ = lean_uint64_shift_right(v___y_8162_, v___x_8168_);
v___x_8170_ = lean_uint64_dec_eq(v___x_8169_, v___y_8160_);
if (v___x_8170_ == 0)
{
v___y_8144_ = v___y_8159_;
v___y_8145_ = v___y_8160_;
v___y_8146_ = v___y_8161_;
v___y_8147_ = v___y_8162_;
v___y_8148_ = v___y_8163_;
v___y_8149_ = v___y_8164_;
v___y_8150_ = v___y_8165_;
v___y_8151_ = v___y_8167_;
v___y_8152_ = v___x_8168_;
v___y_8153_ = v___y_8166_;
v___y_8154_ = v___x_8169_;
goto v___jp_8143_;
}
else
{
v___y_8144_ = v___y_8159_;
v___y_8145_ = v___y_8160_;
v___y_8146_ = v___y_8161_;
v___y_8147_ = v___y_8162_;
v___y_8148_ = v___y_8163_;
v___y_8149_ = v___y_8164_;
v___y_8150_ = v___y_8165_;
v___y_8151_ = v___y_8167_;
v___y_8152_ = v___x_8168_;
v___y_8153_ = v___y_8166_;
v___y_8154_ = v___y_8162_;
goto v___jp_8143_;
}
}
v___jp_8171_:
{
uint64_t v___x_8183_; uint8_t v___x_8184_; 
v___x_8183_ = lean_uint64_shift_right(v___y_8172_, v___y_8176_);
v___x_8184_ = lean_uint64_dec_eq(v___x_8183_, v___y_8174_);
if (v___x_8184_ == 0)
{
uint64_t v___x_8185_; 
v___x_8185_ = lean_uint64_add(v___y_8177_, v___y_8176_);
v___y_8159_ = v___y_8173_;
v___y_8160_ = v___y_8174_;
v___y_8161_ = v___y_8175_;
v___y_8162_ = v___y_8182_;
v___y_8163_ = v___y_8178_;
v___y_8164_ = v___y_8179_;
v___y_8165_ = v___y_8180_;
v___y_8166_ = v___y_8181_;
v___y_8167_ = v___x_8185_;
goto v___jp_8158_;
}
else
{
v___y_8159_ = v___y_8173_;
v___y_8160_ = v___y_8174_;
v___y_8161_ = v___y_8175_;
v___y_8162_ = v___y_8182_;
v___y_8163_ = v___y_8178_;
v___y_8164_ = v___y_8179_;
v___y_8165_ = v___y_8180_;
v___y_8166_ = v___y_8181_;
v___y_8167_ = v___y_8177_;
goto v___jp_8158_;
}
}
v___jp_8186_:
{
uint64_t v___x_8196_; uint64_t v___x_8197_; uint8_t v___x_8198_; 
v___x_8196_ = 8ULL;
v___x_8197_ = lean_uint64_shift_right(v___y_8188_, v___x_8196_);
v___x_8198_ = lean_uint64_dec_eq(v___x_8197_, v___y_8189_);
if (v___x_8198_ == 0)
{
v___y_8172_ = v___y_8188_;
v___y_8173_ = v___y_8187_;
v___y_8174_ = v___y_8189_;
v___y_8175_ = v___y_8190_;
v___y_8176_ = v___x_8196_;
v___y_8177_ = v___y_8195_;
v___y_8178_ = v___y_8191_;
v___y_8179_ = v___y_8192_;
v___y_8180_ = v___y_8193_;
v___y_8181_ = v___y_8194_;
v___y_8182_ = v___x_8197_;
goto v___jp_8171_;
}
else
{
v___y_8172_ = v___y_8188_;
v___y_8173_ = v___y_8187_;
v___y_8174_ = v___y_8189_;
v___y_8175_ = v___y_8190_;
v___y_8176_ = v___x_8196_;
v___y_8177_ = v___y_8195_;
v___y_8178_ = v___y_8191_;
v___y_8179_ = v___y_8192_;
v___y_8180_ = v___y_8193_;
v___y_8181_ = v___y_8194_;
v___y_8182_ = v___y_8188_;
goto v___jp_8171_;
}
}
v___jp_8199_:
{
uint64_t v___x_8211_; uint8_t v___x_8212_; 
v___x_8211_ = lean_uint64_shift_right(v___y_8206_, v___y_8208_);
v___x_8212_ = lean_uint64_dec_eq(v___x_8211_, v___y_8201_);
if (v___x_8212_ == 0)
{
uint64_t v___x_8213_; 
v___x_8213_ = lean_uint64_add(v___y_8204_, v___y_8208_);
v___y_8187_ = v___y_8200_;
v___y_8188_ = v___y_8210_;
v___y_8189_ = v___y_8201_;
v___y_8190_ = v___y_8202_;
v___y_8191_ = v___y_8203_;
v___y_8192_ = v___y_8205_;
v___y_8193_ = v___y_8207_;
v___y_8194_ = v___y_8209_;
v___y_8195_ = v___x_8213_;
goto v___jp_8186_;
}
else
{
v___y_8187_ = v___y_8200_;
v___y_8188_ = v___y_8210_;
v___y_8189_ = v___y_8201_;
v___y_8190_ = v___y_8202_;
v___y_8191_ = v___y_8203_;
v___y_8192_ = v___y_8205_;
v___y_8193_ = v___y_8207_;
v___y_8194_ = v___y_8209_;
v___y_8195_ = v___y_8204_;
goto v___jp_8186_;
}
}
v___jp_8214_:
{
uint64_t v___x_8224_; uint64_t v___x_8225_; uint8_t v___x_8226_; 
v___x_8224_ = 16ULL;
v___x_8225_ = lean_uint64_shift_right(v___y_8221_, v___x_8224_);
v___x_8226_ = lean_uint64_dec_eq(v___x_8225_, v___y_8216_);
if (v___x_8226_ == 0)
{
v___y_8200_ = v___y_8215_;
v___y_8201_ = v___y_8216_;
v___y_8202_ = v___y_8217_;
v___y_8203_ = v___y_8218_;
v___y_8204_ = v___y_8223_;
v___y_8205_ = v___y_8219_;
v___y_8206_ = v___y_8221_;
v___y_8207_ = v___y_8220_;
v___y_8208_ = v___x_8224_;
v___y_8209_ = v___y_8222_;
v___y_8210_ = v___x_8225_;
goto v___jp_8199_;
}
else
{
v___y_8200_ = v___y_8215_;
v___y_8201_ = v___y_8216_;
v___y_8202_ = v___y_8217_;
v___y_8203_ = v___y_8218_;
v___y_8204_ = v___y_8223_;
v___y_8205_ = v___y_8219_;
v___y_8206_ = v___y_8221_;
v___y_8207_ = v___y_8220_;
v___y_8208_ = v___x_8224_;
v___y_8209_ = v___y_8222_;
v___y_8210_ = v___y_8221_;
goto v___jp_8199_;
}
}
v___jp_8227_:
{
uint64_t v___x_8237_; uint8_t v___x_8238_; 
v___x_8237_ = lean_uint64_shift_right(v___y_8234_, v___y_8231_);
v___x_8238_ = lean_uint64_dec_eq(v___x_8237_, v___y_8229_);
if (v___x_8238_ == 0)
{
v___y_8215_ = v___y_8228_;
v___y_8216_ = v___y_8229_;
v___y_8217_ = v___y_8230_;
v___y_8218_ = v___y_8232_;
v___y_8219_ = v___y_8233_;
v___y_8220_ = v___y_8234_;
v___y_8221_ = v___y_8236_;
v___y_8222_ = v___y_8235_;
v___y_8223_ = v___y_8231_;
goto v___jp_8214_;
}
else
{
v___y_8215_ = v___y_8228_;
v___y_8216_ = v___y_8229_;
v___y_8217_ = v___y_8230_;
v___y_8218_ = v___y_8232_;
v___y_8219_ = v___y_8233_;
v___y_8220_ = v___y_8234_;
v___y_8221_ = v___y_8236_;
v___y_8222_ = v___y_8235_;
v___y_8223_ = v___y_8229_;
goto v___jp_8214_;
}
}
v___jp_8239_:
{
uint64_t v___x_8246_; uint8_t v___x_8247_; 
v___x_8246_ = 0ULL;
v___x_8247_ = lean_uint64_dec_eq(v___y_8244_, v___x_8246_);
if (v___x_8247_ == 0)
{
uint64_t v___x_8248_; uint64_t v___x_8249_; uint8_t v___x_8250_; 
v___x_8248_ = 32ULL;
v___x_8249_ = lean_uint64_shift_right(v___y_8244_, v___x_8248_);
v___x_8250_ = lean_uint64_dec_eq(v___x_8249_, v___x_8246_);
if (v___x_8250_ == 0)
{
v___y_8228_ = v___y_8240_;
v___y_8229_ = v___x_8246_;
v___y_8230_ = v___y_8241_;
v___y_8231_ = v___x_8248_;
v___y_8232_ = v___y_8242_;
v___y_8233_ = v___y_8243_;
v___y_8234_ = v___y_8244_;
v___y_8235_ = v___y_8245_;
v___y_8236_ = v___x_8249_;
goto v___jp_8227_;
}
else
{
v___y_8228_ = v___y_8240_;
v___y_8229_ = v___x_8246_;
v___y_8230_ = v___y_8241_;
v___y_8231_ = v___x_8248_;
v___y_8232_ = v___y_8242_;
v___y_8233_ = v___y_8243_;
v___y_8234_ = v___y_8244_;
v___y_8235_ = v___y_8245_;
v___y_8236_ = v___y_8244_;
goto v___jp_8227_;
}
}
else
{
if (v___y_8243_ == 0)
{
uint32_t v___x_8251_; 
v___x_8251_ = 0;
v___y_7925_ = v___x_8251_;
goto v___jp_7924_;
}
else
{
uint32_t v___x_8252_; 
v___x_8252_ = 2147483648;
v___y_7925_ = v___x_8252_;
goto v___jp_7924_;
}
}
}
v___jp_8253_:
{
uint32_t v___x_8257_; uint32_t v___x_8258_; 
v___x_8257_ = lean_uint32_land(v___y_8254_, v___y_8255_);
v___x_8258_ = lean_uint32_lor(v___y_8256_, v___x_8257_);
v___y_7925_ = v___x_8258_;
goto v___jp_7924_;
}
v___jp_8259_:
{
uint8_t v___x_8264_; 
v___x_8264_ = lean_uint64_dec_eq(v___y_8263_, v___y_8261_);
if (v___x_8264_ == 0)
{
uint64_t v___x_8265_; uint8_t v___x_8266_; 
v___x_8265_ = 8388608ULL;
v___x_8266_ = lean_uint64_dec_eq(v___y_8263_, v___x_8265_);
if (v___x_8266_ == 0)
{
uint32_t v___x_8267_; 
v___x_8267_ = lean_uint64_to_uint32(v___y_8263_);
if (v___y_8262_ == 0)
{
uint32_t v___x_8268_; 
v___x_8268_ = 0;
v___y_8254_ = v___x_8267_;
v___y_8255_ = v___y_8260_;
v___y_8256_ = v___x_8268_;
goto v___jp_8253_;
}
else
{
uint32_t v___x_8269_; 
v___x_8269_ = 2147483648;
v___y_8254_ = v___x_8267_;
v___y_8255_ = v___y_8260_;
v___y_8256_ = v___x_8269_;
goto v___jp_8253_;
}
}
else
{
if (v___y_8262_ == 0)
{
uint32_t v___x_8270_; 
v___x_8270_ = 0;
v___y_7948_ = v___x_8270_;
goto v___jp_7947_;
}
else
{
uint32_t v___x_8271_; 
v___x_8271_ = 2147483648;
v___y_7948_ = v___x_8271_;
goto v___jp_7947_;
}
}
}
else
{
if (v___y_8262_ == 0)
{
uint32_t v___x_8272_; 
v___x_8272_ = 0;
v___y_7925_ = v___x_8272_;
goto v___jp_7924_;
}
else
{
uint32_t v___x_8273_; 
v___x_8273_ = 2147483648;
v___y_7925_ = v___x_8273_;
goto v___jp_7924_;
}
}
}
v___jp_8274_:
{
uint64_t v___x_8283_; uint64_t v___x_8284_; uint64_t v___x_8285_; uint8_t v___x_8286_; 
v___x_8283_ = lean_uint64_mul(v___y_8275_, v___y_8280_);
v___x_8284_ = lean_uint64_add(v___y_8276_, v___y_8282_);
v___x_8285_ = 281474976710656ULL;
v___x_8286_ = lean_uint64_dec_lt(v___x_8283_, v___x_8285_);
if (v___x_8286_ == 0)
{
v___y_8240_ = v___y_8277_;
v___y_8241_ = v___y_8278_;
v___y_8242_ = v___y_8279_;
v___y_8243_ = v___y_8281_;
v___y_8244_ = v___x_8283_;
v___y_8245_ = v___x_8284_;
goto v___jp_8239_;
}
else
{
uint64_t v___x_8287_; uint8_t v___x_8288_; 
v___x_8287_ = 123ULL;
v___x_8288_ = lean_uint64_dec_le(v___x_8284_, v___x_8287_);
if (v___x_8288_ == 0)
{
v___y_8240_ = v___y_8277_;
v___y_8241_ = v___y_8278_;
v___y_8242_ = v___y_8279_;
v___y_8243_ = v___y_8281_;
v___y_8244_ = v___x_8283_;
v___y_8245_ = v___x_8284_;
goto v___jp_8239_;
}
else
{
uint64_t v___x_8289_; uint8_t v___x_8290_; 
v___x_8289_ = 0ULL;
v___x_8290_ = lean_uint64_dec_eq(v___x_8283_, v___x_8289_);
if (v___x_8290_ == 0)
{
uint64_t v___x_8291_; uint64_t v___x_8292_; uint8_t v___x_8293_; 
v___x_8291_ = 149ULL;
v___x_8292_ = lean_uint64_sub(v___x_8291_, v___x_8284_);
v___x_8293_ = lean_uint64_dec_eq(v___x_8292_, v___x_8289_);
if (v___x_8293_ == 0)
{
uint64_t v___x_8294_; uint8_t v___x_8295_; 
v___x_8294_ = 64ULL;
v___x_8295_ = lean_uint64_dec_lt(v___x_8292_, v___x_8294_);
if (v___x_8295_ == 0)
{
uint8_t v___x_8296_; 
v___x_8296_ = lean_uint64_dec_eq(v___x_8292_, v___x_8294_);
if (v___x_8296_ == 0)
{
v___y_8260_ = v___y_8277_;
v___y_8261_ = v___x_8289_;
v___y_8262_ = v___y_8281_;
v___y_8263_ = v___x_8289_;
goto v___jp_8259_;
}
else
{
uint64_t v___x_8297_; uint8_t v___x_8298_; 
v___x_8297_ = 9223372036854775808ULL;
v___x_8298_ = lean_uint64_dec_lt(v___x_8297_, v___x_8283_);
if (v___x_8298_ == 0)
{
v___y_8260_ = v___y_8277_;
v___y_8261_ = v___x_8289_;
v___y_8262_ = v___y_8281_;
v___y_8263_ = v___x_8289_;
goto v___jp_8259_;
}
else
{
uint64_t v___x_8299_; 
v___x_8299_ = 1ULL;
v___y_8260_ = v___y_8277_;
v___y_8261_ = v___x_8289_;
v___y_8262_ = v___y_8281_;
v___y_8263_ = v___x_8299_;
goto v___jp_8259_;
}
}
}
else
{
uint64_t v_quotient_8300_; uint64_t v___x_8301_; uint64_t v___x_8302_; uint64_t v___x_8303_; uint64_t v_remainder_8304_; uint64_t v___x_8305_; uint64_t v_half_8306_; uint8_t v___x_8307_; 
v_quotient_8300_ = lean_uint64_shift_right(v___x_8283_, v___x_8292_);
v___x_8301_ = 1ULL;
v___x_8302_ = lean_uint64_shift_left(v___x_8301_, v___x_8292_);
v___x_8303_ = lean_uint64_sub(v___x_8302_, v___x_8301_);
v_remainder_8304_ = lean_uint64_land(v___x_8283_, v___x_8303_);
v___x_8305_ = lean_uint64_sub(v___x_8292_, v___x_8301_);
v_half_8306_ = lean_uint64_shift_left(v___x_8301_, v___x_8305_);
v___x_8307_ = lean_uint64_dec_lt(v_remainder_8304_, v_half_8306_);
if (v___x_8307_ == 0)
{
uint8_t v___x_8308_; 
v___x_8308_ = lean_uint64_dec_lt(v_half_8306_, v_remainder_8304_);
if (v___x_8308_ == 0)
{
uint64_t v___x_8309_; uint8_t v___x_8310_; 
v___x_8309_ = lean_uint64_land(v_quotient_8300_, v___x_8301_);
v___x_8310_ = lean_uint64_dec_eq(v___x_8309_, v___x_8289_);
if (v___x_8310_ == 0)
{
uint64_t v___x_8311_; 
v___x_8311_ = lean_uint64_add(v_quotient_8300_, v___x_8301_);
v___y_8260_ = v___y_8277_;
v___y_8261_ = v___x_8289_;
v___y_8262_ = v___y_8281_;
v___y_8263_ = v___x_8311_;
goto v___jp_8259_;
}
else
{
v___y_8260_ = v___y_8277_;
v___y_8261_ = v___x_8289_;
v___y_8262_ = v___y_8281_;
v___y_8263_ = v_quotient_8300_;
goto v___jp_8259_;
}
}
else
{
uint64_t v___x_8312_; 
v___x_8312_ = lean_uint64_add(v_quotient_8300_, v___x_8301_);
v___y_8260_ = v___y_8277_;
v___y_8261_ = v___x_8289_;
v___y_8262_ = v___y_8281_;
v___y_8263_ = v___x_8312_;
goto v___jp_8259_;
}
}
else
{
v___y_8260_ = v___y_8277_;
v___y_8261_ = v___x_8289_;
v___y_8262_ = v___y_8281_;
v___y_8263_ = v_quotient_8300_;
goto v___jp_8259_;
}
}
}
else
{
v___y_8260_ = v___y_8277_;
v___y_8261_ = v___x_8289_;
v___y_8262_ = v___y_8281_;
v___y_8263_ = v___x_8283_;
goto v___jp_8259_;
}
}
else
{
if (v___y_8281_ == 0)
{
uint32_t v___x_8313_; 
v___x_8313_ = 0;
v___y_7925_ = v___x_8313_;
goto v___jp_7924_;
}
else
{
uint32_t v___x_8314_; 
v___x_8314_ = 2147483648;
v___y_7925_ = v___x_8314_;
goto v___jp_7924_;
}
}
}
}
}
v___jp_8315_:
{
uint64_t v___x_8324_; uint64_t v___x_8325_; uint8_t v___x_8326_; 
v___x_8324_ = lean_uint32_to_uint64(v___y_8319_);
v___x_8325_ = 0ULL;
v___x_8326_ = lean_uint64_dec_eq(v___x_8324_, v___x_8325_);
if (v___x_8326_ == 0)
{
uint64_t v___x_8327_; uint64_t v___x_8328_; 
v___x_8327_ = 1ULL;
v___x_8328_ = lean_uint64_sub(v___x_8324_, v___x_8327_);
v___y_8275_ = v___y_8316_;
v___y_8276_ = v___y_8323_;
v___y_8277_ = v___y_8317_;
v___y_8278_ = v___y_8318_;
v___y_8279_ = v___y_8320_;
v___y_8280_ = v___y_8321_;
v___y_8281_ = v___y_8322_;
v___y_8282_ = v___x_8328_;
goto v___jp_8274_;
}
else
{
v___y_8275_ = v___y_8316_;
v___y_8276_ = v___y_8323_;
v___y_8277_ = v___y_8317_;
v___y_8278_ = v___y_8318_;
v___y_8279_ = v___y_8320_;
v___y_8280_ = v___y_8321_;
v___y_8281_ = v___y_8322_;
v___y_8282_ = v___x_8325_;
goto v___jp_8274_;
}
}
v___jp_8329_:
{
uint64_t v___x_8338_; uint64_t v___x_8339_; uint8_t v___x_8340_; 
v___x_8338_ = lean_uint32_to_uint64(v___y_8332_);
v___x_8339_ = 0ULL;
v___x_8340_ = lean_uint64_dec_eq(v___x_8338_, v___x_8339_);
if (v___x_8340_ == 0)
{
uint64_t v___x_8341_; uint64_t v___x_8342_; 
v___x_8341_ = 1ULL;
v___x_8342_ = lean_uint64_sub(v___x_8338_, v___x_8341_);
v___y_8316_ = v___y_8330_;
v___y_8317_ = v___y_8331_;
v___y_8318_ = v___y_8333_;
v___y_8319_ = v___y_8334_;
v___y_8320_ = v___y_8335_;
v___y_8321_ = v___y_8337_;
v___y_8322_ = v___y_8336_;
v___y_8323_ = v___x_8342_;
goto v___jp_8315_;
}
else
{
v___y_8316_ = v___y_8330_;
v___y_8317_ = v___y_8331_;
v___y_8318_ = v___y_8333_;
v___y_8319_ = v___y_8334_;
v___y_8320_ = v___y_8335_;
v___y_8321_ = v___y_8337_;
v___y_8322_ = v___y_8336_;
v___y_8323_ = v___x_8339_;
goto v___jp_8315_;
}
}
v___jp_8343_:
{
uint32_t v___x_8352_; uint8_t v___x_8353_; 
v___x_8352_ = 0;
v___x_8353_ = lean_uint32_dec_eq(v___y_8348_, v___x_8352_);
if (v___x_8353_ == 0)
{
uint64_t v___x_8354_; uint64_t v___x_8355_; uint64_t v___x_8356_; 
v___x_8354_ = lean_uint32_to_uint64(v___y_8344_);
v___x_8355_ = 8388608ULL;
v___x_8356_ = lean_uint64_lor(v___x_8354_, v___x_8355_);
v___y_8330_ = v___y_8351_;
v___y_8331_ = v___y_8345_;
v___y_8332_ = v___y_8346_;
v___y_8333_ = v___y_8347_;
v___y_8334_ = v___y_8348_;
v___y_8335_ = v___y_8349_;
v___y_8336_ = v___y_8350_;
v___y_8337_ = v___x_8356_;
goto v___jp_8329_;
}
else
{
uint64_t v___x_8357_; 
v___x_8357_ = lean_uint32_to_uint64(v___y_8344_);
v___y_8330_ = v___y_8351_;
v___y_8331_ = v___y_8345_;
v___y_8332_ = v___y_8346_;
v___y_8333_ = v___y_8347_;
v___y_8334_ = v___y_8348_;
v___y_8335_ = v___y_8349_;
v___y_8336_ = v___y_8350_;
v___y_8337_ = v___x_8357_;
goto v___jp_8329_;
}
}
v___jp_8358_:
{
uint32_t v___x_8366_; uint32_t v_xFraction_8367_; uint32_t v_yFraction_8368_; uint32_t v___x_8369_; uint8_t v___x_8370_; 
v___x_8366_ = 8388607;
v_xFraction_8367_ = lean_uint32_land(v___y_8361_, v___x_8366_);
v_yFraction_8368_ = lean_uint32_land(v___y_8359_, v___x_8366_);
v___x_8369_ = 0;
v___x_8370_ = lean_uint32_dec_eq(v___y_8360_, v___x_8369_);
if (v___x_8370_ == 0)
{
uint64_t v___x_8371_; uint64_t v___x_8372_; uint64_t v___x_8373_; 
v___x_8371_ = lean_uint32_to_uint64(v_xFraction_8367_);
v___x_8372_ = 8388608ULL;
v___x_8373_ = lean_uint64_lor(v___x_8371_, v___x_8372_);
v___y_8344_ = v_yFraction_8368_;
v___y_8345_ = v___x_8366_;
v___y_8346_ = v___y_8360_;
v___y_8347_ = v___y_8362_;
v___y_8348_ = v___y_8363_;
v___y_8349_ = v___y_8364_;
v___y_8350_ = v___y_8365_;
v___y_8351_ = v___x_8373_;
goto v___jp_8343_;
}
else
{
uint64_t v___x_8374_; 
v___x_8374_ = lean_uint32_to_uint64(v_xFraction_8367_);
v___y_8344_ = v_yFraction_8368_;
v___y_8345_ = v___x_8366_;
v___y_8346_ = v___y_8360_;
v___y_8347_ = v___y_8362_;
v___y_8348_ = v___y_8363_;
v___y_8349_ = v___y_8364_;
v___y_8350_ = v___y_8365_;
v___y_8351_ = v___x_8374_;
goto v___jp_8343_;
}
}
v___jp_8375_:
{
uint32_t v___x_8379_; uint32_t v___x_8380_; 
v___x_8379_ = lean_uint32_land(v___y_8376_, v___y_8377_);
v___x_8380_ = lean_uint32_lor(v___y_8378_, v___x_8379_);
v___y_7925_ = v___x_8380_;
goto v___jp_7924_;
}
v___jp_8381_:
{
uint8_t v___x_8386_; 
v___x_8386_ = lean_uint64_dec_eq(v___y_8385_, v___y_8382_);
if (v___x_8386_ == 0)
{
uint64_t v___x_8387_; uint8_t v___x_8388_; 
v___x_8387_ = 8388608ULL;
v___x_8388_ = lean_uint64_dec_eq(v___y_8385_, v___x_8387_);
if (v___x_8388_ == 0)
{
uint32_t v___x_8389_; 
v___x_8389_ = lean_uint64_to_uint32(v___y_8385_);
if (v___y_8383_ == 0)
{
uint32_t v___x_8390_; 
v___x_8390_ = 0;
v___y_8376_ = v___x_8389_;
v___y_8377_ = v___y_8384_;
v___y_8378_ = v___x_8390_;
goto v___jp_8375_;
}
else
{
uint32_t v___x_8391_; 
v___x_8391_ = 2147483648;
v___y_8376_ = v___x_8389_;
v___y_8377_ = v___y_8384_;
v___y_8378_ = v___x_8391_;
goto v___jp_8375_;
}
}
else
{
if (v___y_8383_ == 0)
{
uint32_t v___x_8392_; 
v___x_8392_ = 0;
v___y_7952_ = v___x_8392_;
goto v___jp_7951_;
}
else
{
uint32_t v___x_8393_; 
v___x_8393_ = 2147483648;
v___y_7952_ = v___x_8393_;
goto v___jp_7951_;
}
}
}
else
{
if (v___y_8383_ == 0)
{
uint32_t v___x_8394_; 
v___x_8394_ = 0;
v___y_7925_ = v___x_8394_;
goto v___jp_7924_;
}
else
{
uint32_t v___x_8395_; 
v___x_8395_ = 2147483648;
v___y_7925_ = v___x_8395_;
goto v___jp_7924_;
}
}
}
v___jp_8396_:
{
uint32_t v___x_8403_; uint32_t v___x_8404_; uint32_t v___x_8405_; uint32_t v___x_8406_; uint32_t v___x_8407_; 
v___x_8403_ = lean_uint32_land(v___y_8399_, v___y_8400_);
v___x_8404_ = lean_uint32_shift_left(v___x_8403_, v___y_8398_);
v___x_8405_ = lean_uint32_lor(v___y_8402_, v___x_8404_);
v___x_8406_ = lean_uint32_land(v___y_8397_, v___y_8401_);
v___x_8407_ = lean_uint32_lor(v___x_8405_, v___x_8406_);
v___y_7925_ = v___x_8407_;
goto v___jp_7924_;
}
v___jp_8408_:
{
if (v___y_8412_ == 0)
{
uint32_t v___x_8415_; 
v___x_8415_ = 0;
v___y_8397_ = v___y_8414_;
v___y_8398_ = v___y_8409_;
v___y_8399_ = v___y_8410_;
v___y_8400_ = v___y_8411_;
v___y_8401_ = v___y_8413_;
v___y_8402_ = v___x_8415_;
goto v___jp_8396_;
}
else
{
uint32_t v___x_8416_; 
v___x_8416_ = 2147483648;
v___y_8397_ = v___y_8414_;
v___y_8398_ = v___y_8409_;
v___y_8399_ = v___y_8410_;
v___y_8400_ = v___y_8411_;
v___y_8401_ = v___y_8413_;
v___y_8402_ = v___x_8416_;
goto v___jp_8396_;
}
}
v___jp_8417_:
{
uint64_t v___x_8425_; uint64_t v_encodedExponent_8426_; uint32_t v___x_8427_; uint64_t v___x_8428_; uint8_t v___x_8429_; 
v___x_8425_ = 171ULL;
v_encodedExponent_8426_ = lean_uint64_sub(v___y_8419_, v___x_8425_);
v___x_8427_ = lean_uint64_to_uint32(v_encodedExponent_8426_);
v___x_8428_ = 8388608ULL;
v___x_8429_ = lean_uint64_dec_lt(v___y_8424_, v___x_8428_);
if (v___x_8429_ == 0)
{
uint64_t v___x_8430_; uint32_t v___x_8431_; 
v___x_8430_ = lean_uint64_sub(v___y_8424_, v___x_8428_);
v___x_8431_ = lean_uint64_to_uint32(v___x_8430_);
v___y_8409_ = v___y_8418_;
v___y_8410_ = v___x_8427_;
v___y_8411_ = v___y_8421_;
v___y_8412_ = v___y_8422_;
v___y_8413_ = v___y_8423_;
v___y_8414_ = v___x_8431_;
goto v___jp_8408_;
}
else
{
uint32_t v___x_8432_; 
v___x_8432_ = lean_uint64_to_uint32(v___y_8420_);
v___y_8409_ = v___y_8418_;
v___y_8410_ = v___x_8427_;
v___y_8411_ = v___y_8421_;
v___y_8412_ = v___y_8422_;
v___y_8413_ = v___y_8423_;
v___y_8414_ = v___x_8432_;
goto v___jp_8408_;
}
}
v___jp_8433_:
{
uint64_t v___x_8442_; uint8_t v___x_8443_; 
v___x_8442_ = 425ULL;
v___x_8443_ = lean_uint64_dec_lt(v___x_8442_, v___y_8441_);
if (v___x_8443_ == 0)
{
if (v___y_8436_ == 0)
{
v___y_8418_ = v___y_8434_;
v___y_8419_ = v___y_8441_;
v___y_8420_ = v___y_8438_;
v___y_8421_ = v___y_8437_;
v___y_8422_ = v___y_8439_;
v___y_8423_ = v___y_8440_;
v___y_8424_ = v___y_8435_;
goto v___jp_8417_;
}
else
{
uint64_t v___x_8444_; 
v___x_8444_ = 8388608ULL;
v___y_8418_ = v___y_8434_;
v___y_8419_ = v___y_8441_;
v___y_8420_ = v___y_8438_;
v___y_8421_ = v___y_8437_;
v___y_8422_ = v___y_8439_;
v___y_8423_ = v___y_8440_;
v___y_8424_ = v___x_8444_;
goto v___jp_8417_;
}
}
else
{
if (v___y_8439_ == 0)
{
uint32_t v___x_8445_; 
v___x_8445_ = 2139095040;
v___y_7925_ = v___x_8445_;
goto v___jp_7924_;
}
else
{
uint32_t v___x_8446_; 
v___x_8446_ = 4286578688;
v___y_7925_ = v___x_8446_;
goto v___jp_7924_;
}
}
}
v___jp_8447_:
{
uint64_t v___x_8455_; uint8_t v_carry_8456_; 
v___x_8455_ = 16777216ULL;
v_carry_8456_ = lean_uint64_dec_eq(v___y_8454_, v___x_8455_);
if (v_carry_8456_ == 0)
{
v___y_8434_ = v___y_8449_;
v___y_8435_ = v___y_8454_;
v___y_8436_ = v_carry_8456_;
v___y_8437_ = v___y_8451_;
v___y_8438_ = v___y_8450_;
v___y_8439_ = v___y_8452_;
v___y_8440_ = v___y_8453_;
v___y_8441_ = v___y_8448_;
goto v___jp_8433_;
}
else
{
uint64_t v___x_8457_; uint64_t v___x_8458_; 
v___x_8457_ = 1ULL;
v___x_8458_ = lean_uint64_add(v___y_8448_, v___x_8457_);
v___y_8434_ = v___y_8449_;
v___y_8435_ = v___y_8454_;
v___y_8436_ = v_carry_8456_;
v___y_8437_ = v___y_8451_;
v___y_8438_ = v___y_8450_;
v___y_8439_ = v___y_8452_;
v___y_8440_ = v___y_8453_;
v___y_8441_ = v___x_8458_;
goto v___jp_8433_;
}
}
v___jp_8459_:
{
uint64_t v_position_8468_; uint64_t v___x_8469_; uint8_t v___x_8470_; 
v_position_8468_ = lean_uint64_add(v___y_8467_, v___y_8460_);
v___x_8469_ = 172ULL;
v___x_8470_ = lean_uint64_dec_lt(v_position_8468_, v___x_8469_);
if (v___x_8470_ == 0)
{
uint64_t v___x_8471_; uint8_t v___x_8472_; 
v___x_8471_ = 23ULL;
v___x_8472_ = lean_uint64_dec_lt(v___y_8467_, v___x_8471_);
if (v___x_8472_ == 0)
{
uint64_t v___x_8473_; uint8_t v___x_8474_; 
v___x_8473_ = lean_uint64_sub(v___y_8467_, v___x_8471_);
v___x_8474_ = lean_uint64_dec_eq(v___x_8473_, v___y_8464_);
if (v___x_8474_ == 0)
{
uint64_t v___x_8475_; uint8_t v___x_8476_; 
v___x_8475_ = 64ULL;
v___x_8476_ = lean_uint64_dec_lt(v___x_8473_, v___x_8475_);
if (v___x_8476_ == 0)
{
uint8_t v___x_8477_; 
v___x_8477_ = lean_uint64_dec_eq(v___x_8473_, v___x_8475_);
if (v___x_8477_ == 0)
{
v___y_8448_ = v_position_8468_;
v___y_8449_ = v___y_8461_;
v___y_8450_ = v___y_8464_;
v___y_8451_ = v___y_8463_;
v___y_8452_ = v___y_8465_;
v___y_8453_ = v___y_8466_;
v___y_8454_ = v___y_8464_;
goto v___jp_8447_;
}
else
{
uint64_t v___x_8478_; uint8_t v___x_8479_; 
v___x_8478_ = 9223372036854775808ULL;
v___x_8479_ = lean_uint64_dec_lt(v___x_8478_, v___y_8462_);
if (v___x_8479_ == 0)
{
v___y_8448_ = v_position_8468_;
v___y_8449_ = v___y_8461_;
v___y_8450_ = v___y_8464_;
v___y_8451_ = v___y_8463_;
v___y_8452_ = v___y_8465_;
v___y_8453_ = v___y_8466_;
v___y_8454_ = v___y_8464_;
goto v___jp_8447_;
}
else
{
uint64_t v___x_8480_; 
v___x_8480_ = 1ULL;
v___y_8448_ = v_position_8468_;
v___y_8449_ = v___y_8461_;
v___y_8450_ = v___y_8464_;
v___y_8451_ = v___y_8463_;
v___y_8452_ = v___y_8465_;
v___y_8453_ = v___y_8466_;
v___y_8454_ = v___x_8480_;
goto v___jp_8447_;
}
}
}
else
{
uint64_t v_quotient_8481_; uint64_t v___x_8482_; uint64_t v___x_8483_; uint64_t v___x_8484_; uint64_t v_remainder_8485_; uint64_t v___x_8486_; uint64_t v_half_8487_; uint8_t v___x_8488_; 
v_quotient_8481_ = lean_uint64_shift_right(v___y_8462_, v___x_8473_);
v___x_8482_ = 1ULL;
v___x_8483_ = lean_uint64_shift_left(v___x_8482_, v___x_8473_);
v___x_8484_ = lean_uint64_sub(v___x_8483_, v___x_8482_);
v_remainder_8485_ = lean_uint64_land(v___y_8462_, v___x_8484_);
v___x_8486_ = lean_uint64_sub(v___x_8473_, v___x_8482_);
v_half_8487_ = lean_uint64_shift_left(v___x_8482_, v___x_8486_);
v___x_8488_ = lean_uint64_dec_lt(v_remainder_8485_, v_half_8487_);
if (v___x_8488_ == 0)
{
uint8_t v___x_8489_; 
v___x_8489_ = lean_uint64_dec_lt(v_half_8487_, v_remainder_8485_);
if (v___x_8489_ == 0)
{
uint64_t v___x_8490_; uint8_t v___x_8491_; 
v___x_8490_ = lean_uint64_land(v_quotient_8481_, v___x_8482_);
v___x_8491_ = lean_uint64_dec_eq(v___x_8490_, v___y_8464_);
if (v___x_8491_ == 0)
{
uint64_t v___x_8492_; 
v___x_8492_ = lean_uint64_add(v_quotient_8481_, v___x_8482_);
v___y_8448_ = v_position_8468_;
v___y_8449_ = v___y_8461_;
v___y_8450_ = v___y_8464_;
v___y_8451_ = v___y_8463_;
v___y_8452_ = v___y_8465_;
v___y_8453_ = v___y_8466_;
v___y_8454_ = v___x_8492_;
goto v___jp_8447_;
}
else
{
v___y_8448_ = v_position_8468_;
v___y_8449_ = v___y_8461_;
v___y_8450_ = v___y_8464_;
v___y_8451_ = v___y_8463_;
v___y_8452_ = v___y_8465_;
v___y_8453_ = v___y_8466_;
v___y_8454_ = v_quotient_8481_;
goto v___jp_8447_;
}
}
else
{
uint64_t v___x_8493_; 
v___x_8493_ = lean_uint64_add(v_quotient_8481_, v___x_8482_);
v___y_8448_ = v_position_8468_;
v___y_8449_ = v___y_8461_;
v___y_8450_ = v___y_8464_;
v___y_8451_ = v___y_8463_;
v___y_8452_ = v___y_8465_;
v___y_8453_ = v___y_8466_;
v___y_8454_ = v___x_8493_;
goto v___jp_8447_;
}
}
else
{
v___y_8448_ = v_position_8468_;
v___y_8449_ = v___y_8461_;
v___y_8450_ = v___y_8464_;
v___y_8451_ = v___y_8463_;
v___y_8452_ = v___y_8465_;
v___y_8453_ = v___y_8466_;
v___y_8454_ = v_quotient_8481_;
goto v___jp_8447_;
}
}
}
else
{
v___y_8448_ = v_position_8468_;
v___y_8449_ = v___y_8461_;
v___y_8450_ = v___y_8464_;
v___y_8451_ = v___y_8463_;
v___y_8452_ = v___y_8465_;
v___y_8453_ = v___y_8466_;
v___y_8454_ = v___y_8462_;
goto v___jp_8447_;
}
}
else
{
uint64_t v___x_8494_; uint64_t v___x_8495_; 
v___x_8494_ = lean_uint64_sub(v___x_8471_, v___y_8467_);
v___x_8495_ = lean_uint64_shift_left(v___y_8462_, v___x_8494_);
v___y_8448_ = v_position_8468_;
v___y_8449_ = v___y_8461_;
v___y_8450_ = v___y_8464_;
v___y_8451_ = v___y_8463_;
v___y_8452_ = v___y_8465_;
v___y_8453_ = v___y_8466_;
v___y_8454_ = v___x_8495_;
goto v___jp_8447_;
}
}
else
{
uint64_t v___x_8496_; uint8_t v___x_8497_; 
v___x_8496_ = 149ULL;
v___x_8497_ = lean_uint64_dec_lt(v___y_8460_, v___x_8496_);
if (v___x_8497_ == 0)
{
uint64_t v___x_8498_; uint64_t v___x_8499_; 
v___x_8498_ = lean_uint64_sub(v___y_8460_, v___x_8496_);
v___x_8499_ = lean_uint64_shift_left(v___y_8462_, v___x_8498_);
v___y_8382_ = v___y_8464_;
v___y_8383_ = v___y_8465_;
v___y_8384_ = v___y_8466_;
v___y_8385_ = v___x_8499_;
goto v___jp_8381_;
}
else
{
uint64_t v___x_8500_; uint8_t v___x_8501_; 
v___x_8500_ = lean_uint64_sub(v___x_8496_, v___y_8460_);
v___x_8501_ = lean_uint64_dec_eq(v___x_8500_, v___y_8464_);
if (v___x_8501_ == 0)
{
uint64_t v___x_8502_; uint8_t v___x_8503_; 
v___x_8502_ = 64ULL;
v___x_8503_ = lean_uint64_dec_lt(v___x_8500_, v___x_8502_);
if (v___x_8503_ == 0)
{
uint8_t v___x_8504_; 
v___x_8504_ = lean_uint64_dec_eq(v___x_8500_, v___x_8502_);
if (v___x_8504_ == 0)
{
v___y_8382_ = v___y_8464_;
v___y_8383_ = v___y_8465_;
v___y_8384_ = v___y_8466_;
v___y_8385_ = v___y_8464_;
goto v___jp_8381_;
}
else
{
uint64_t v___x_8505_; uint8_t v___x_8506_; 
v___x_8505_ = 9223372036854775808ULL;
v___x_8506_ = lean_uint64_dec_lt(v___x_8505_, v___y_8462_);
if (v___x_8506_ == 0)
{
v___y_8382_ = v___y_8464_;
v___y_8383_ = v___y_8465_;
v___y_8384_ = v___y_8466_;
v___y_8385_ = v___y_8464_;
goto v___jp_8381_;
}
else
{
uint64_t v___x_8507_; 
v___x_8507_ = 1ULL;
v___y_8382_ = v___y_8464_;
v___y_8383_ = v___y_8465_;
v___y_8384_ = v___y_8466_;
v___y_8385_ = v___x_8507_;
goto v___jp_8381_;
}
}
}
else
{
uint64_t v_quotient_8508_; uint64_t v___x_8509_; uint64_t v___x_8510_; uint64_t v___x_8511_; uint64_t v_remainder_8512_; uint64_t v___x_8513_; uint64_t v_half_8514_; uint8_t v___x_8515_; 
v_quotient_8508_ = lean_uint64_shift_right(v___y_8462_, v___x_8500_);
v___x_8509_ = 1ULL;
v___x_8510_ = lean_uint64_shift_left(v___x_8509_, v___x_8500_);
v___x_8511_ = lean_uint64_sub(v___x_8510_, v___x_8509_);
v_remainder_8512_ = lean_uint64_land(v___y_8462_, v___x_8511_);
v___x_8513_ = lean_uint64_sub(v___x_8500_, v___x_8509_);
v_half_8514_ = lean_uint64_shift_left(v___x_8509_, v___x_8513_);
v___x_8515_ = lean_uint64_dec_lt(v_remainder_8512_, v_half_8514_);
if (v___x_8515_ == 0)
{
uint8_t v___x_8516_; 
v___x_8516_ = lean_uint64_dec_lt(v_half_8514_, v_remainder_8512_);
if (v___x_8516_ == 0)
{
uint64_t v___x_8517_; uint8_t v___x_8518_; 
v___x_8517_ = lean_uint64_land(v_quotient_8508_, v___x_8509_);
v___x_8518_ = lean_uint64_dec_eq(v___x_8517_, v___y_8464_);
if (v___x_8518_ == 0)
{
uint64_t v___x_8519_; 
v___x_8519_ = lean_uint64_add(v_quotient_8508_, v___x_8509_);
v___y_8382_ = v___y_8464_;
v___y_8383_ = v___y_8465_;
v___y_8384_ = v___y_8466_;
v___y_8385_ = v___x_8519_;
goto v___jp_8381_;
}
else
{
v___y_8382_ = v___y_8464_;
v___y_8383_ = v___y_8465_;
v___y_8384_ = v___y_8466_;
v___y_8385_ = v_quotient_8508_;
goto v___jp_8381_;
}
}
else
{
uint64_t v___x_8520_; 
v___x_8520_ = lean_uint64_add(v_quotient_8508_, v___x_8509_);
v___y_8382_ = v___y_8464_;
v___y_8383_ = v___y_8465_;
v___y_8384_ = v___y_8466_;
v___y_8385_ = v___x_8520_;
goto v___jp_8381_;
}
}
else
{
v___y_8382_ = v___y_8464_;
v___y_8383_ = v___y_8465_;
v___y_8384_ = v___y_8466_;
v___y_8385_ = v_quotient_8508_;
goto v___jp_8381_;
}
}
}
else
{
v___y_8382_ = v___y_8464_;
v___y_8383_ = v___y_8465_;
v___y_8384_ = v___y_8466_;
v___y_8385_ = v___y_8462_;
goto v___jp_8381_;
}
}
}
}
v___jp_8521_:
{
uint64_t v___x_8531_; uint64_t v___x_8532_; uint8_t v___x_8533_; 
v___x_8531_ = 1ULL;
v___x_8532_ = lean_uint64_shift_right(v___y_8523_, v___x_8531_);
v___x_8533_ = lean_uint64_dec_eq(v___x_8532_, v___y_8527_);
if (v___x_8533_ == 0)
{
uint64_t v___x_8534_; 
v___x_8534_ = lean_uint64_add(v___y_8530_, v___x_8531_);
v___y_8460_ = v___y_8522_;
v___y_8461_ = v___y_8524_;
v___y_8462_ = v___y_8526_;
v___y_8463_ = v___y_8525_;
v___y_8464_ = v___y_8527_;
v___y_8465_ = v___y_8528_;
v___y_8466_ = v___y_8529_;
v___y_8467_ = v___x_8534_;
goto v___jp_8459_;
}
else
{
v___y_8460_ = v___y_8522_;
v___y_8461_ = v___y_8524_;
v___y_8462_ = v___y_8526_;
v___y_8463_ = v___y_8525_;
v___y_8464_ = v___y_8527_;
v___y_8465_ = v___y_8528_;
v___y_8466_ = v___y_8529_;
v___y_8467_ = v___y_8530_;
goto v___jp_8459_;
}
}
v___jp_8535_:
{
uint64_t v___x_8547_; uint8_t v___x_8548_; 
v___x_8547_ = lean_uint64_shift_right(v___y_8542_, v___y_8538_);
v___x_8548_ = lean_uint64_dec_eq(v___x_8547_, v___y_8539_);
if (v___x_8548_ == 0)
{
uint64_t v___x_8549_; 
v___x_8549_ = lean_uint64_add(v___y_8543_, v___y_8538_);
v___y_8522_ = v___y_8536_;
v___y_8523_ = v___y_8546_;
v___y_8524_ = v___y_8537_;
v___y_8525_ = v___y_8541_;
v___y_8526_ = v___y_8540_;
v___y_8527_ = v___y_8539_;
v___y_8528_ = v___y_8544_;
v___y_8529_ = v___y_8545_;
v___y_8530_ = v___x_8549_;
goto v___jp_8521_;
}
else
{
v___y_8522_ = v___y_8536_;
v___y_8523_ = v___y_8546_;
v___y_8524_ = v___y_8537_;
v___y_8525_ = v___y_8541_;
v___y_8526_ = v___y_8540_;
v___y_8527_ = v___y_8539_;
v___y_8528_ = v___y_8544_;
v___y_8529_ = v___y_8545_;
v___y_8530_ = v___y_8543_;
goto v___jp_8521_;
}
}
v___jp_8550_:
{
uint64_t v___x_8560_; uint64_t v___x_8561_; uint8_t v___x_8562_; 
v___x_8560_ = 2ULL;
v___x_8561_ = lean_uint64_shift_right(v___y_8556_, v___x_8560_);
v___x_8562_ = lean_uint64_dec_eq(v___x_8561_, v___y_8555_);
if (v___x_8562_ == 0)
{
v___y_8536_ = v___y_8551_;
v___y_8537_ = v___y_8552_;
v___y_8538_ = v___x_8560_;
v___y_8539_ = v___y_8555_;
v___y_8540_ = v___y_8554_;
v___y_8541_ = v___y_8553_;
v___y_8542_ = v___y_8556_;
v___y_8543_ = v___y_8559_;
v___y_8544_ = v___y_8557_;
v___y_8545_ = v___y_8558_;
v___y_8546_ = v___x_8561_;
goto v___jp_8535_;
}
else
{
v___y_8536_ = v___y_8551_;
v___y_8537_ = v___y_8552_;
v___y_8538_ = v___x_8560_;
v___y_8539_ = v___y_8555_;
v___y_8540_ = v___y_8554_;
v___y_8541_ = v___y_8553_;
v___y_8542_ = v___y_8556_;
v___y_8543_ = v___y_8559_;
v___y_8544_ = v___y_8557_;
v___y_8545_ = v___y_8558_;
v___y_8546_ = v___y_8556_;
goto v___jp_8535_;
}
}
v___jp_8563_:
{
uint64_t v___x_8575_; uint8_t v___x_8576_; 
v___x_8575_ = lean_uint64_shift_right(v___y_8566_, v___y_8565_);
v___x_8576_ = lean_uint64_dec_eq(v___x_8575_, v___y_8569_);
if (v___x_8576_ == 0)
{
uint64_t v___x_8577_; 
v___x_8577_ = lean_uint64_add(v___y_8568_, v___y_8565_);
v___y_8551_ = v___y_8564_;
v___y_8552_ = v___y_8567_;
v___y_8553_ = v___y_8571_;
v___y_8554_ = v___y_8570_;
v___y_8555_ = v___y_8569_;
v___y_8556_ = v___y_8574_;
v___y_8557_ = v___y_8572_;
v___y_8558_ = v___y_8573_;
v___y_8559_ = v___x_8577_;
goto v___jp_8550_;
}
else
{
v___y_8551_ = v___y_8564_;
v___y_8552_ = v___y_8567_;
v___y_8553_ = v___y_8571_;
v___y_8554_ = v___y_8570_;
v___y_8555_ = v___y_8569_;
v___y_8556_ = v___y_8574_;
v___y_8557_ = v___y_8572_;
v___y_8558_ = v___y_8573_;
v___y_8559_ = v___y_8568_;
goto v___jp_8550_;
}
}
v___jp_8578_:
{
uint64_t v___x_8588_; uint64_t v___x_8589_; uint8_t v___x_8590_; 
v___x_8588_ = 4ULL;
v___x_8589_ = lean_uint64_shift_right(v___y_8581_, v___x_8588_);
v___x_8590_ = lean_uint64_dec_eq(v___x_8589_, v___y_8584_);
if (v___x_8590_ == 0)
{
v___y_8564_ = v___y_8579_;
v___y_8565_ = v___x_8588_;
v___y_8566_ = v___y_8581_;
v___y_8567_ = v___y_8580_;
v___y_8568_ = v___y_8587_;
v___y_8569_ = v___y_8584_;
v___y_8570_ = v___y_8583_;
v___y_8571_ = v___y_8582_;
v___y_8572_ = v___y_8585_;
v___y_8573_ = v___y_8586_;
v___y_8574_ = v___x_8589_;
goto v___jp_8563_;
}
else
{
v___y_8564_ = v___y_8579_;
v___y_8565_ = v___x_8588_;
v___y_8566_ = v___y_8581_;
v___y_8567_ = v___y_8580_;
v___y_8568_ = v___y_8587_;
v___y_8569_ = v___y_8584_;
v___y_8570_ = v___y_8583_;
v___y_8571_ = v___y_8582_;
v___y_8572_ = v___y_8585_;
v___y_8573_ = v___y_8586_;
v___y_8574_ = v___y_8581_;
goto v___jp_8563_;
}
}
v___jp_8591_:
{
uint64_t v___x_8603_; uint8_t v___x_8604_; 
v___x_8603_ = lean_uint64_shift_right(v___y_8599_, v___y_8594_);
v___x_8604_ = lean_uint64_dec_eq(v___x_8603_, v___y_8596_);
if (v___x_8604_ == 0)
{
uint64_t v___x_8605_; 
v___x_8605_ = lean_uint64_add(v___y_8592_, v___y_8594_);
v___y_8579_ = v___y_8593_;
v___y_8580_ = v___y_8595_;
v___y_8581_ = v___y_8602_;
v___y_8582_ = v___y_8598_;
v___y_8583_ = v___y_8597_;
v___y_8584_ = v___y_8596_;
v___y_8585_ = v___y_8600_;
v___y_8586_ = v___y_8601_;
v___y_8587_ = v___x_8605_;
goto v___jp_8578_;
}
else
{
v___y_8579_ = v___y_8593_;
v___y_8580_ = v___y_8595_;
v___y_8581_ = v___y_8602_;
v___y_8582_ = v___y_8598_;
v___y_8583_ = v___y_8597_;
v___y_8584_ = v___y_8596_;
v___y_8585_ = v___y_8600_;
v___y_8586_ = v___y_8601_;
v___y_8587_ = v___y_8592_;
goto v___jp_8578_;
}
}
v___jp_8606_:
{
uint64_t v___x_8616_; uint64_t v___x_8617_; uint8_t v___x_8618_; 
v___x_8616_ = 8ULL;
v___x_8617_ = lean_uint64_shift_right(v___y_8613_, v___x_8616_);
v___x_8618_ = lean_uint64_dec_eq(v___x_8617_, v___y_8611_);
if (v___x_8618_ == 0)
{
v___y_8592_ = v___y_8615_;
v___y_8593_ = v___y_8607_;
v___y_8594_ = v___x_8616_;
v___y_8595_ = v___y_8608_;
v___y_8596_ = v___y_8611_;
v___y_8597_ = v___y_8610_;
v___y_8598_ = v___y_8609_;
v___y_8599_ = v___y_8613_;
v___y_8600_ = v___y_8612_;
v___y_8601_ = v___y_8614_;
v___y_8602_ = v___x_8617_;
goto v___jp_8591_;
}
else
{
v___y_8592_ = v___y_8615_;
v___y_8593_ = v___y_8607_;
v___y_8594_ = v___x_8616_;
v___y_8595_ = v___y_8608_;
v___y_8596_ = v___y_8611_;
v___y_8597_ = v___y_8610_;
v___y_8598_ = v___y_8609_;
v___y_8599_ = v___y_8613_;
v___y_8600_ = v___y_8612_;
v___y_8601_ = v___y_8614_;
v___y_8602_ = v___y_8613_;
goto v___jp_8591_;
}
}
v___jp_8619_:
{
uint64_t v___x_8631_; uint8_t v___x_8632_; 
v___x_8631_ = lean_uint64_shift_right(v___y_8628_, v___y_8622_);
v___x_8632_ = lean_uint64_dec_eq(v___x_8631_, v___y_8623_);
if (v___x_8632_ == 0)
{
uint64_t v___x_8633_; 
v___x_8633_ = lean_uint64_add(v___y_8626_, v___y_8622_);
v___y_8607_ = v___y_8620_;
v___y_8608_ = v___y_8621_;
v___y_8609_ = v___y_8625_;
v___y_8610_ = v___y_8624_;
v___y_8611_ = v___y_8623_;
v___y_8612_ = v___y_8627_;
v___y_8613_ = v___y_8630_;
v___y_8614_ = v___y_8629_;
v___y_8615_ = v___x_8633_;
goto v___jp_8606_;
}
else
{
v___y_8607_ = v___y_8620_;
v___y_8608_ = v___y_8621_;
v___y_8609_ = v___y_8625_;
v___y_8610_ = v___y_8624_;
v___y_8611_ = v___y_8623_;
v___y_8612_ = v___y_8627_;
v___y_8613_ = v___y_8630_;
v___y_8614_ = v___y_8629_;
v___y_8615_ = v___y_8626_;
goto v___jp_8606_;
}
}
v___jp_8634_:
{
uint64_t v___x_8644_; uint64_t v___x_8645_; uint8_t v___x_8646_; 
v___x_8644_ = 16ULL;
v___x_8645_ = lean_uint64_shift_right(v___y_8642_, v___x_8644_);
v___x_8646_ = lean_uint64_dec_eq(v___x_8645_, v___y_8639_);
if (v___x_8646_ == 0)
{
v___y_8620_ = v___y_8635_;
v___y_8621_ = v___y_8636_;
v___y_8622_ = v___x_8644_;
v___y_8623_ = v___y_8639_;
v___y_8624_ = v___y_8638_;
v___y_8625_ = v___y_8637_;
v___y_8626_ = v___y_8643_;
v___y_8627_ = v___y_8640_;
v___y_8628_ = v___y_8642_;
v___y_8629_ = v___y_8641_;
v___y_8630_ = v___x_8645_;
goto v___jp_8619_;
}
else
{
v___y_8620_ = v___y_8635_;
v___y_8621_ = v___y_8636_;
v___y_8622_ = v___x_8644_;
v___y_8623_ = v___y_8639_;
v___y_8624_ = v___y_8638_;
v___y_8625_ = v___y_8637_;
v___y_8626_ = v___y_8643_;
v___y_8627_ = v___y_8640_;
v___y_8628_ = v___y_8642_;
v___y_8629_ = v___y_8641_;
v___y_8630_ = v___y_8642_;
goto v___jp_8619_;
}
}
v___jp_8647_:
{
uint64_t v___x_8657_; uint8_t v___x_8658_; 
v___x_8657_ = lean_uint64_shift_right(v___y_8651_, v___y_8653_);
v___x_8658_ = lean_uint64_dec_eq(v___x_8657_, v___y_8650_);
if (v___x_8658_ == 0)
{
v___y_8635_ = v___y_8648_;
v___y_8636_ = v___y_8649_;
v___y_8637_ = v___y_8652_;
v___y_8638_ = v___y_8651_;
v___y_8639_ = v___y_8650_;
v___y_8640_ = v___y_8654_;
v___y_8641_ = v___y_8655_;
v___y_8642_ = v___y_8656_;
v___y_8643_ = v___y_8653_;
goto v___jp_8634_;
}
else
{
v___y_8635_ = v___y_8648_;
v___y_8636_ = v___y_8649_;
v___y_8637_ = v___y_8652_;
v___y_8638_ = v___y_8651_;
v___y_8639_ = v___y_8650_;
v___y_8640_ = v___y_8654_;
v___y_8641_ = v___y_8655_;
v___y_8642_ = v___y_8656_;
v___y_8643_ = v___y_8650_;
goto v___jp_8634_;
}
}
v___jp_8659_:
{
uint64_t v___x_8667_; uint64_t v___x_8668_; uint8_t v___x_8669_; 
v___x_8667_ = 32ULL;
v___x_8668_ = lean_uint64_shift_right(v___y_8663_, v___x_8667_);
v___x_8669_ = lean_uint64_dec_eq(v___x_8668_, v___y_8664_);
if (v___x_8669_ == 0)
{
v___y_8648_ = v___y_8660_;
v___y_8649_ = v___y_8661_;
v___y_8650_ = v___y_8664_;
v___y_8651_ = v___y_8663_;
v___y_8652_ = v___y_8662_;
v___y_8653_ = v___x_8667_;
v___y_8654_ = v___y_8665_;
v___y_8655_ = v___y_8666_;
v___y_8656_ = v___x_8668_;
goto v___jp_8647_;
}
else
{
v___y_8648_ = v___y_8660_;
v___y_8649_ = v___y_8661_;
v___y_8650_ = v___y_8664_;
v___y_8651_ = v___y_8663_;
v___y_8652_ = v___y_8662_;
v___y_8653_ = v___x_8667_;
v___y_8654_ = v___y_8665_;
v___y_8655_ = v___y_8666_;
v___y_8656_ = v___y_8663_;
goto v___jp_8647_;
}
}
v___jp_8670_:
{
uint64_t v___x_8679_; uint64_t v___x_8680_; uint8_t v___x_8681_; 
v___x_8679_ = lean_uint64_mul(v___y_8673_, v___y_8676_);
v___x_8680_ = 0ULL;
v___x_8681_ = lean_uint64_dec_eq(v___x_8679_, v___x_8680_);
if (v___x_8681_ == 0)
{
uint64_t v___x_8682_; uint64_t v___x_8683_; uint8_t v___x_8684_; 
v___x_8682_ = lean_uint64_add(v___y_8672_, v___y_8678_);
v___x_8683_ = 70368744177664ULL;
v___x_8684_ = lean_uint64_dec_le(v___x_8683_, v___x_8679_);
if (v___x_8684_ == 0)
{
v___y_8660_ = v___x_8682_;
v___y_8661_ = v___y_8671_;
v___y_8662_ = v___y_8674_;
v___y_8663_ = v___x_8679_;
v___y_8664_ = v___x_8680_;
v___y_8665_ = v___y_8675_;
v___y_8666_ = v___y_8677_;
goto v___jp_8659_;
}
else
{
uint64_t v___x_8685_; uint8_t v___x_8686_; 
v___x_8685_ = 281474976710656ULL;
v___x_8686_ = lean_uint64_dec_lt(v___x_8679_, v___x_8685_);
if (v___x_8686_ == 0)
{
v___y_8660_ = v___x_8682_;
v___y_8661_ = v___y_8671_;
v___y_8662_ = v___y_8674_;
v___y_8663_ = v___x_8679_;
v___y_8664_ = v___x_8680_;
v___y_8665_ = v___y_8675_;
v___y_8666_ = v___y_8677_;
goto v___jp_8659_;
}
else
{
uint64_t v___x_8687_; uint8_t v___x_8688_; 
v___x_8687_ = 140737488355328ULL;
v___x_8688_ = lean_uint64_dec_lt(v___x_8679_, v___x_8687_);
if (v___x_8688_ == 0)
{
uint64_t v___x_8689_; 
v___x_8689_ = 47ULL;
v___y_8460_ = v___x_8682_;
v___y_8461_ = v___y_8671_;
v___y_8462_ = v___x_8679_;
v___y_8463_ = v___y_8674_;
v___y_8464_ = v___x_8680_;
v___y_8465_ = v___y_8675_;
v___y_8466_ = v___y_8677_;
v___y_8467_ = v___x_8689_;
goto v___jp_8459_;
}
else
{
uint64_t v___x_8690_; 
v___x_8690_ = 46ULL;
v___y_8460_ = v___x_8682_;
v___y_8461_ = v___y_8671_;
v___y_8462_ = v___x_8679_;
v___y_8463_ = v___y_8674_;
v___y_8464_ = v___x_8680_;
v___y_8465_ = v___y_8675_;
v___y_8466_ = v___y_8677_;
v___y_8467_ = v___x_8690_;
goto v___jp_8459_;
}
}
}
}
else
{
if (v___y_8675_ == 0)
{
uint32_t v___x_8691_; 
v___x_8691_ = 0;
v___y_7925_ = v___x_8691_;
goto v___jp_7924_;
}
else
{
uint32_t v___x_8692_; 
v___x_8692_ = 2147483648;
v___y_7925_ = v___x_8692_;
goto v___jp_7924_;
}
}
}
v___jp_8693_:
{
uint64_t v___x_8702_; uint64_t v___x_8703_; uint8_t v___x_8704_; 
v___x_8702_ = lean_uint32_to_uint64(v___y_8695_);
v___x_8703_ = 0ULL;
v___x_8704_ = lean_uint64_dec_eq(v___x_8702_, v___x_8703_);
if (v___x_8704_ == 0)
{
uint64_t v___x_8705_; uint64_t v___x_8706_; 
v___x_8705_ = 1ULL;
v___x_8706_ = lean_uint64_sub(v___x_8702_, v___x_8705_);
v___y_8671_ = v___y_8694_;
v___y_8672_ = v___y_8701_;
v___y_8673_ = v___y_8696_;
v___y_8674_ = v___y_8697_;
v___y_8675_ = v___y_8699_;
v___y_8676_ = v___y_8698_;
v___y_8677_ = v___y_8700_;
v___y_8678_ = v___x_8706_;
goto v___jp_8670_;
}
else
{
v___y_8671_ = v___y_8694_;
v___y_8672_ = v___y_8701_;
v___y_8673_ = v___y_8696_;
v___y_8674_ = v___y_8697_;
v___y_8675_ = v___y_8699_;
v___y_8676_ = v___y_8698_;
v___y_8677_ = v___y_8700_;
v___y_8678_ = v___x_8703_;
goto v___jp_8670_;
}
}
v___jp_8707_:
{
uint64_t v___x_8716_; uint64_t v___x_8717_; uint8_t v___x_8718_; 
v___x_8716_ = lean_uint32_to_uint64(v___y_8708_);
v___x_8717_ = 0ULL;
v___x_8718_ = lean_uint64_dec_eq(v___x_8716_, v___x_8717_);
if (v___x_8718_ == 0)
{
uint64_t v___x_8719_; uint64_t v___x_8720_; 
v___x_8719_ = 1ULL;
v___x_8720_ = lean_uint64_sub(v___x_8716_, v___x_8719_);
v___y_8694_ = v___y_8709_;
v___y_8695_ = v___y_8711_;
v___y_8696_ = v___y_8710_;
v___y_8697_ = v___y_8712_;
v___y_8698_ = v___y_8715_;
v___y_8699_ = v___y_8713_;
v___y_8700_ = v___y_8714_;
v___y_8701_ = v___x_8720_;
goto v___jp_8693_;
}
else
{
v___y_8694_ = v___y_8709_;
v___y_8695_ = v___y_8711_;
v___y_8696_ = v___y_8710_;
v___y_8697_ = v___y_8712_;
v___y_8698_ = v___y_8715_;
v___y_8699_ = v___y_8713_;
v___y_8700_ = v___y_8714_;
v___y_8701_ = v___x_8717_;
goto v___jp_8693_;
}
}
v___jp_8721_:
{
uint32_t v___x_8730_; uint8_t v___x_8731_; 
v___x_8730_ = 0;
v___x_8731_ = lean_uint32_dec_eq(v___y_8724_, v___x_8730_);
if (v___x_8731_ == 0)
{
uint64_t v___x_8732_; uint64_t v___x_8733_; uint64_t v___x_8734_; 
v___x_8732_ = lean_uint32_to_uint64(v___y_8727_);
v___x_8733_ = 8388608ULL;
v___x_8734_ = lean_uint64_lor(v___x_8732_, v___x_8733_);
v___y_8708_ = v___y_8722_;
v___y_8709_ = v___y_8723_;
v___y_8710_ = v___y_8729_;
v___y_8711_ = v___y_8724_;
v___y_8712_ = v___y_8725_;
v___y_8713_ = v___y_8726_;
v___y_8714_ = v___y_8728_;
v___y_8715_ = v___x_8734_;
goto v___jp_8707_;
}
else
{
uint64_t v___x_8735_; 
v___x_8735_ = lean_uint32_to_uint64(v___y_8727_);
v___y_8708_ = v___y_8722_;
v___y_8709_ = v___y_8723_;
v___y_8710_ = v___y_8729_;
v___y_8711_ = v___y_8724_;
v___y_8712_ = v___y_8725_;
v___y_8713_ = v___y_8726_;
v___y_8714_ = v___y_8728_;
v___y_8715_ = v___x_8735_;
goto v___jp_8707_;
}
}
v___jp_8736_:
{
uint32_t v___x_8744_; uint32_t v_xFraction_8745_; uint32_t v_yFraction_8746_; uint32_t v___x_8747_; uint8_t v___x_8748_; 
v___x_8744_ = 8388607;
v_xFraction_8745_ = lean_uint32_land(v___y_8739_, v___x_8744_);
v_yFraction_8746_ = lean_uint32_land(v___y_8737_, v___x_8744_);
v___x_8747_ = 0;
v___x_8748_ = lean_uint32_dec_eq(v___y_8738_, v___x_8747_);
if (v___x_8748_ == 0)
{
uint64_t v___x_8749_; uint64_t v___x_8750_; uint64_t v___x_8751_; 
v___x_8749_ = lean_uint32_to_uint64(v_xFraction_8745_);
v___x_8750_ = 8388608ULL;
v___x_8751_ = lean_uint64_lor(v___x_8749_, v___x_8750_);
v___y_8722_ = v___y_8738_;
v___y_8723_ = v___y_8740_;
v___y_8724_ = v___y_8741_;
v___y_8725_ = v___y_8742_;
v___y_8726_ = v___y_8743_;
v___y_8727_ = v_yFraction_8746_;
v___y_8728_ = v___x_8744_;
v___y_8729_ = v___x_8751_;
goto v___jp_8721_;
}
else
{
uint64_t v___x_8752_; 
v___x_8752_ = lean_uint32_to_uint64(v_xFraction_8745_);
v___y_8722_ = v___y_8738_;
v___y_8723_ = v___y_8740_;
v___y_8724_ = v___y_8741_;
v___y_8725_ = v___y_8742_;
v___y_8726_ = v___y_8743_;
v___y_8727_ = v_yFraction_8746_;
v___y_8728_ = v___x_8744_;
v___y_8729_ = v___x_8752_;
goto v___jp_8721_;
}
}
v___jp_8753_:
{
if (v___y_8761_ == 0)
{
v___y_8359_ = v___y_8754_;
v___y_8360_ = v___y_8756_;
v___y_8361_ = v___y_8755_;
v___y_8362_ = v___y_8757_;
v___y_8363_ = v___y_8758_;
v___y_8364_ = v___y_8759_;
v___y_8365_ = v___x_7923_;
goto v___jp_8358_;
}
else
{
v___y_8359_ = v___y_8754_;
v___y_8360_ = v___y_8756_;
v___y_8361_ = v___y_8755_;
v___y_8362_ = v___y_8757_;
v___y_8363_ = v___y_8758_;
v___y_8364_ = v___y_8759_;
v___y_8365_ = v___y_8760_;
goto v___jp_8358_;
}
}
v___jp_8762_:
{
if (v___y_8764_ == 0)
{
if (v___y_8771_ == 0)
{
v___y_8754_ = v___y_8763_;
v___y_8755_ = v___y_8766_;
v___y_8756_ = v___y_8765_;
v___y_8757_ = v___y_8767_;
v___y_8758_ = v___y_8768_;
v___y_8759_ = v___y_8769_;
v___y_8760_ = v___y_8770_;
v___y_8761_ = v___x_7923_;
goto v___jp_8753_;
}
else
{
v___y_8359_ = v___y_8763_;
v___y_8360_ = v___y_8765_;
v___y_8361_ = v___y_8766_;
v___y_8362_ = v___y_8767_;
v___y_8363_ = v___y_8768_;
v___y_8364_ = v___y_8769_;
v___y_8365_ = v___x_7923_;
goto v___jp_8358_;
}
}
else
{
v___y_8754_ = v___y_8763_;
v___y_8755_ = v___y_8766_;
v___y_8756_ = v___y_8765_;
v___y_8757_ = v___y_8767_;
v___y_8758_ = v___y_8768_;
v___y_8759_ = v___y_8769_;
v___y_8760_ = v___y_8770_;
v___y_8761_ = v___y_8771_;
goto v___jp_8753_;
}
}
v___jp_8772_:
{
uint32_t v___x_8781_; uint32_t v___x_8782_; uint32_t v___x_8783_; uint8_t v___x_8784_; 
v___x_8781_ = 2147483648;
v___x_8782_ = lean_uint32_land(v___y_8773_, v___x_8781_);
v___x_8783_ = 0;
v___x_8784_ = lean_uint32_dec_eq(v___x_8782_, v___x_8783_);
if (v___x_8784_ == 0)
{
v___y_8763_ = v___y_8773_;
v___y_8764_ = v___y_8780_;
v___y_8765_ = v___y_8775_;
v___y_8766_ = v___y_8774_;
v___y_8767_ = v___y_8776_;
v___y_8768_ = v___y_8777_;
v___y_8769_ = v___y_8778_;
v___y_8770_ = v___y_8779_;
v___y_8771_ = v___x_7923_;
goto v___jp_8762_;
}
else
{
v___y_8763_ = v___y_8773_;
v___y_8764_ = v___y_8780_;
v___y_8765_ = v___y_8775_;
v___y_8766_ = v___y_8774_;
v___y_8767_ = v___y_8776_;
v___y_8768_ = v___y_8777_;
v___y_8769_ = v___y_8778_;
v___y_8770_ = v___y_8779_;
v___y_8771_ = v___y_8779_;
goto v___jp_8762_;
}
}
v___jp_8785_:
{
if (v___y_8792_ == 0)
{
uint32_t v___x_8793_; uint32_t v___x_8794_; uint32_t v___x_8795_; uint8_t v___x_8796_; 
v___x_8793_ = 2147483648;
v___x_8794_ = lean_uint32_land(v___y_8788_, v___x_8793_);
v___x_8795_ = 0;
v___x_8796_ = lean_uint32_dec_eq(v___x_8794_, v___x_8795_);
if (v___x_8796_ == 0)
{
v___y_8773_ = v___y_8786_;
v___y_8774_ = v___y_8788_;
v___y_8775_ = v___y_8787_;
v___y_8776_ = v___y_8789_;
v___y_8777_ = v___y_8790_;
v___y_8778_ = v___y_8791_;
v___y_8779_ = v___y_8792_;
v___y_8780_ = v___x_7923_;
goto v___jp_8772_;
}
else
{
v___y_8773_ = v___y_8786_;
v___y_8774_ = v___y_8788_;
v___y_8775_ = v___y_8787_;
v___y_8776_ = v___y_8789_;
v___y_8777_ = v___y_8790_;
v___y_8778_ = v___y_8791_;
v___y_8779_ = v___y_8792_;
v___y_8780_ = v___y_8792_;
goto v___jp_8772_;
}
}
else
{
lean_object* v___x_8797_; lean_object* v___x_8798_; lean_object* v___x_8799_; uint32_t v___x_8800_; 
v___x_8797_ = lean_uint32_to_nat(v___y_8788_);
v___x_8798_ = lean_uint32_to_nat(v___y_8786_);
v___x_8799_ = lp_floatlib_FloatLib_Floats_Formats_BinaryInterchange_Model_MulBackend_word___at___00FloatLib_Floats_Formats_BinaryInterchange_Configured_Plan_softwareMul32Certified_spec__1(v___x_8797_, v___x_8798_);
v___x_8800_ = lean_uint32_of_nat(v___x_8799_);
lean_dec(v___x_8799_);
v___y_7925_ = v___x_8800_;
goto v___jp_7924_;
}
}
v___jp_8801_:
{
if (v___y_8809_ == 0)
{
v___y_8737_ = v___y_8802_;
v___y_8738_ = v___y_8804_;
v___y_8739_ = v___y_8803_;
v___y_8740_ = v___y_8805_;
v___y_8741_ = v___y_8806_;
v___y_8742_ = v___y_8808_;
v___y_8743_ = v___x_7923_;
goto v___jp_8736_;
}
else
{
v___y_8737_ = v___y_8802_;
v___y_8738_ = v___y_8804_;
v___y_8739_ = v___y_8803_;
v___y_8740_ = v___y_8805_;
v___y_8741_ = v___y_8806_;
v___y_8742_ = v___y_8808_;
v___y_8743_ = v___y_8807_;
goto v___jp_8736_;
}
}
v___jp_8810_:
{
if (v___y_8818_ == 0)
{
if (v___y_8819_ == 0)
{
v___y_8802_ = v___y_8811_;
v___y_8803_ = v___y_8813_;
v___y_8804_ = v___y_8812_;
v___y_8805_ = v___y_8814_;
v___y_8806_ = v___y_8815_;
v___y_8807_ = v___y_8817_;
v___y_8808_ = v___y_8816_;
v___y_8809_ = v___x_7923_;
goto v___jp_8801_;
}
else
{
v___y_8737_ = v___y_8811_;
v___y_8738_ = v___y_8812_;
v___y_8739_ = v___y_8813_;
v___y_8740_ = v___y_8814_;
v___y_8741_ = v___y_8815_;
v___y_8742_ = v___y_8816_;
v___y_8743_ = v___x_7923_;
goto v___jp_8736_;
}
}
else
{
v___y_8802_ = v___y_8811_;
v___y_8803_ = v___y_8813_;
v___y_8804_ = v___y_8812_;
v___y_8805_ = v___y_8814_;
v___y_8806_ = v___y_8815_;
v___y_8807_ = v___y_8817_;
v___y_8808_ = v___y_8816_;
v___y_8809_ = v___y_8819_;
goto v___jp_8801_;
}
}
v___jp_8820_:
{
uint32_t v___x_8829_; uint32_t v___x_8830_; uint32_t v___x_8831_; uint8_t v___x_8832_; 
v___x_8829_ = 2147483648;
v___x_8830_ = lean_uint32_land(v___y_8821_, v___x_8829_);
v___x_8831_ = 0;
v___x_8832_ = lean_uint32_dec_eq(v___x_8830_, v___x_8831_);
if (v___x_8832_ == 0)
{
v___y_8811_ = v___y_8821_;
v___y_8812_ = v___y_8823_;
v___y_8813_ = v___y_8822_;
v___y_8814_ = v___y_8824_;
v___y_8815_ = v___y_8825_;
v___y_8816_ = v___y_8827_;
v___y_8817_ = v___y_8826_;
v___y_8818_ = v___y_8828_;
v___y_8819_ = v___x_7923_;
goto v___jp_8810_;
}
else
{
v___y_8811_ = v___y_8821_;
v___y_8812_ = v___y_8823_;
v___y_8813_ = v___y_8822_;
v___y_8814_ = v___y_8824_;
v___y_8815_ = v___y_8825_;
v___y_8816_ = v___y_8827_;
v___y_8817_ = v___y_8826_;
v___y_8818_ = v___y_8828_;
v___y_8819_ = v___y_8826_;
goto v___jp_8810_;
}
}
v___jp_8833_:
{
if (v___y_8840_ == 0)
{
uint32_t v___x_8841_; uint32_t v___x_8842_; uint32_t v___x_8843_; uint8_t v___x_8844_; 
v___x_8841_ = 2147483648;
v___x_8842_ = lean_uint32_land(v___y_8836_, v___x_8841_);
v___x_8843_ = 0;
v___x_8844_ = lean_uint32_dec_eq(v___x_8842_, v___x_8843_);
if (v___x_8844_ == 0)
{
v___y_8821_ = v___y_8834_;
v___y_8822_ = v___y_8836_;
v___y_8823_ = v___y_8835_;
v___y_8824_ = v___y_8837_;
v___y_8825_ = v___y_8838_;
v___y_8826_ = v___y_8840_;
v___y_8827_ = v___y_8839_;
v___y_8828_ = v___x_7923_;
goto v___jp_8820_;
}
else
{
v___y_8821_ = v___y_8834_;
v___y_8822_ = v___y_8836_;
v___y_8823_ = v___y_8835_;
v___y_8824_ = v___y_8837_;
v___y_8825_ = v___y_8838_;
v___y_8826_ = v___y_8840_;
v___y_8827_ = v___y_8839_;
v___y_8828_ = v___y_8840_;
goto v___jp_8820_;
}
}
else
{
lean_object* v___x_8845_; lean_object* v___x_8846_; lean_object* v___x_8847_; uint32_t v___x_8848_; 
v___x_8845_ = lean_uint32_to_nat(v___y_8836_);
v___x_8846_ = lean_uint32_to_nat(v___y_8834_);
v___x_8847_ = lp_floatlib_FloatLib_Floats_Formats_BinaryInterchange_Model_MulBackend_word___at___00FloatLib_Floats_Formats_BinaryInterchange_Configured_Plan_softwareMul32Certified_spec__1(v___x_8845_, v___x_8846_);
v___x_8848_ = lean_uint32_of_nat(v___x_8847_);
lean_dec(v___x_8847_);
v___y_7925_ = v___x_8848_;
goto v___jp_7924_;
}
}
v___jp_8849_:
{
uint32_t v___x_8852_; uint32_t v___x_8853_; uint32_t v___x_8854_; uint32_t v_ex_8855_; uint32_t v___x_8856_; uint32_t v_ey_8857_; uint32_t v___x_8858_; uint32_t v___x_8859_; uint8_t v___x_8860_; 
v___x_8852_ = 23;
v___x_8853_ = lean_uint32_shift_right(v___y_8850_, v___x_8852_);
v___x_8854_ = 255;
v_ex_8855_ = lean_uint32_land(v___x_8853_, v___x_8854_);
v___x_8856_ = lean_uint32_shift_right(v___y_8851_, v___x_8852_);
v_ey_8857_ = lean_uint32_land(v___x_8856_, v___x_8854_);
v___x_8858_ = lean_uint32_add(v_ex_8855_, v_ey_8857_);
v___x_8859_ = 128;
v___x_8860_ = lean_uint32_dec_lt(v___x_8858_, v___x_8859_);
if (v___x_8860_ == 0)
{
uint32_t v___x_8861_; uint32_t v___x_8862_; uint32_t v___x_8863_; uint8_t v___x_8864_; 
v___x_8861_ = 4278190080;
v___x_8862_ = 1;
v___x_8863_ = lean_uint32_shift_left(v___y_8850_, v___x_8862_);
v___x_8864_ = lean_uint32_dec_le(v___x_8861_, v___x_8863_);
if (v___x_8864_ == 0)
{
uint32_t v___x_8865_; uint8_t v___x_8866_; 
v___x_8865_ = lean_uint32_shift_left(v___y_8851_, v___x_8862_);
v___x_8866_ = lean_uint32_dec_le(v___x_8861_, v___x_8865_);
v___y_8834_ = v___y_8851_;
v___y_8835_ = v_ex_8855_;
v___y_8836_ = v___y_8850_;
v___y_8837_ = v___x_8852_;
v___y_8838_ = v_ey_8857_;
v___y_8839_ = v___x_8854_;
v___y_8840_ = v___x_8866_;
goto v___jp_8833_;
}
else
{
v___y_8834_ = v___y_8851_;
v___y_8835_ = v_ex_8855_;
v___y_8836_ = v___y_8850_;
v___y_8837_ = v___x_8852_;
v___y_8838_ = v_ey_8857_;
v___y_8839_ = v___x_8854_;
v___y_8840_ = v___x_8864_;
goto v___jp_8833_;
}
}
else
{
uint32_t v___x_8867_; uint32_t v___x_8868_; uint32_t v___x_8869_; uint8_t v___x_8870_; 
v___x_8867_ = 4278190080;
v___x_8868_ = 1;
v___x_8869_ = lean_uint32_shift_left(v___y_8850_, v___x_8868_);
v___x_8870_ = lean_uint32_dec_le(v___x_8867_, v___x_8869_);
if (v___x_8870_ == 0)
{
uint32_t v___x_8871_; uint8_t v___x_8872_; 
v___x_8871_ = lean_uint32_shift_left(v___y_8851_, v___x_8868_);
v___x_8872_ = lean_uint32_dec_le(v___x_8867_, v___x_8871_);
v___y_8786_ = v___y_8851_;
v___y_8787_ = v_ex_8855_;
v___y_8788_ = v___y_8850_;
v___y_8789_ = v___x_8852_;
v___y_8790_ = v_ey_8857_;
v___y_8791_ = v___x_8854_;
v___y_8792_ = v___x_8872_;
goto v___jp_8785_;
}
else
{
v___y_8786_ = v___y_8851_;
v___y_8787_ = v_ex_8855_;
v___y_8788_ = v___y_8850_;
v___y_8789_ = v___x_8852_;
v___y_8790_ = v_ey_8857_;
v___y_8791_ = v___x_8854_;
v___y_8792_ = v___x_8870_;
goto v___jp_8785_;
}
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_Fin_foldl_loop___at___00Submission_NativeFinal_dot_spec__0___boxed(lean_object* v_baseA_8887_, lean_object* v_p_8888_, lean_object* v_baseB_8889_, lean_object* v_B_8890_, lean_object* v_A_8891_, lean_object* v_n_8892_, lean_object* v_x_8893_, lean_object* v_i_8894_){
_start:
{
uint32_t v_x_boxed_8895_; uint32_t v_res_8896_; lean_object* v_r_8897_; 
v_x_boxed_8895_ = lean_unbox_uint32(v_x_8893_);
lean_dec(v_x_8893_);
v_res_8896_ = lp_competition_Fin_foldl_loop___at___00Submission_NativeFinal_dot_spec__0(v_baseA_8887_, v_p_8888_, v_baseB_8889_, v_B_8890_, v_A_8891_, v_n_8892_, v_x_boxed_8895_, v_i_8894_);
lean_dec(v_n_8892_);
lean_dec_ref(v_A_8891_);
lean_dec_ref(v_B_8890_);
lean_dec(v_baseB_8889_);
lean_dec(v_p_8888_);
lean_dec(v_baseA_8887_);
v_r_8897_ = lean_box_uint32(v_res_8896_);
return v_r_8897_;
}
}
static float _init_lp_competition_Submission_NativeFinal_dot___closed__0(void){
_start:
{
uint32_t v___x_8898_; float v___x_8899_; 
v___x_8898_ = 0;
v___x_8899_ = lean_float32_of_bits(v___x_8898_);
return v___x_8899_;
}
}
LEAN_EXPORT uint32_t lp_competition_Submission_NativeFinal_dot(lean_object* v_n_8900_, lean_object* v_baseA_8901_, lean_object* v_baseB_8902_, lean_object* v_p_8903_, lean_object* v_A_8904_, lean_object* v_B_8905_){
_start:
{
lean_object* v___x_8906_; float v___x_8907_; float v_result_8908_; uint8_t v___x_8909_; 
v___x_8906_ = lean_unsigned_to_nat(0u);
v___x_8907_ = lean_float32_once(&lp_competition_Submission_NativeFinal_dot___closed__0, &lp_competition_Submission_NativeFinal_dot___closed__0_once, _init_lp_competition_Submission_NativeFinal_dot___closed__0);
v_result_8908_ = lp_competition_Submission_NativeFinal_dotLoop(v_n_8900_, v_baseA_8901_, v_baseB_8902_, v_p_8903_, v_A_8904_, v_B_8905_, v___x_8906_, v___x_8907_);
v___x_8909_ = lean_float32_isfinite(v_result_8908_);
if (v___x_8909_ == 0)
{
uint32_t v___x_8910_; uint32_t v___x_8911_; 
v___x_8910_ = lean_uint32_once(&lp_competition_Submission_referenceSum___redArg___closed__1, &lp_competition_Submission_referenceSum___redArg___closed__1_once, _init_lp_competition_Submission_referenceSum___redArg___closed__1);
v___x_8911_ = lp_competition_Fin_foldl_loop___at___00Submission_NativeFinal_dot_spec__0(v_baseA_8901_, v_p_8903_, v_baseB_8902_, v_B_8905_, v_A_8904_, v_n_8900_, v___x_8910_, v___x_8906_);
return v___x_8911_;
}
else
{
uint32_t v___x_8912_; 
v___x_8912_ = lean_float32_to_bits(v_result_8908_);
return v___x_8912_;
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_NativeFinal_dot___boxed(lean_object* v_n_8913_, lean_object* v_baseA_8914_, lean_object* v_baseB_8915_, lean_object* v_p_8916_, lean_object* v_A_8917_, lean_object* v_B_8918_){
_start:
{
uint32_t v_res_8919_; lean_object* v_r_8920_; 
v_res_8919_ = lp_competition_Submission_NativeFinal_dot(v_n_8913_, v_baseA_8914_, v_baseB_8915_, v_p_8916_, v_A_8917_, v_B_8918_);
lean_dec_ref(v_B_8918_);
lean_dec_ref(v_A_8917_);
lean_dec(v_p_8916_);
lean_dec(v_baseB_8915_);
lean_dec(v_baseA_8914_);
lean_dec(v_n_8913_);
v_r_8920_ = lean_box_uint32(v_res_8919_);
return v_r_8920_;
}
}
LEAN_EXPORT uint32_t lp_competition_Submission_originalSum(lean_object* v_n_8921_, lean_object* v_x_8922_){
_start:
{
lean_object* v___x_8923_; float v___x_8924_; float v_result_8925_; uint8_t v___x_8926_; 
v___x_8923_ = lean_unsigned_to_nat(0u);
v___x_8924_ = lean_float32_once(&lp_competition_Submission_NativeFinal_dot___closed__0, &lp_competition_Submission_NativeFinal_dot___closed__0_once, _init_lp_competition_Submission_NativeFinal_dot___closed__0);
v_result_8925_ = lp_competition_Submission_NativeFinal_sumLoop(v_n_8921_, v_x_8922_, v___x_8923_, v___x_8924_);
v___x_8926_ = lean_float32_isfinite(v_result_8925_);
if (v___x_8926_ == 0)
{
uint32_t v___x_8927_; 
v___x_8927_ = lp_competition_Submission_referenceSum___redArg(v_x_8922_);
return v___x_8927_;
}
else
{
uint32_t v___x_8928_; 
v___x_8928_ = lean_float32_to_bits(v_result_8925_);
return v___x_8928_;
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_originalSum___boxed(lean_object* v_n_8929_, lean_object* v_x_8930_){
_start:
{
uint32_t v_res_8931_; lean_object* v_r_8932_; 
v_res_8931_ = lp_competition_Submission_originalSum(v_n_8929_, v_x_8930_);
lean_dec_ref(v_x_8930_);
lean_dec(v_n_8929_);
v_r_8932_ = lean_box_uint32(v_res_8931_);
return v_r_8932_;
}
}
static float _init_lp_competition_Submission_Packed10_zero32(void){
_start:
{
float v___x_8933_; 
v___x_8933_ = lean_float32_once(&lp_competition_Submission_NativeFinal_dot___closed__0, &lp_competition_Submission_NativeFinal_dot___closed__0_once, _init_lp_competition_Submission_NativeFinal_dot___closed__0);
return v___x_8933_;
}
}
static lean_object* _init_lp_competition_Submission_Packed10_zero10___closed__0(void){
_start:
{
float v___x_8934_; lean_object* v___x_8935_; 
v___x_8934_ = lean_float32_once(&lp_competition_Submission_NativeFinal_dot___closed__0, &lp_competition_Submission_NativeFinal_dot___closed__0_once, _init_lp_competition_Submission_NativeFinal_dot___closed__0);
v___x_8935_ = lean_alloc_ctor(0, 0, 40);
lean_ctor_set_float32(v___x_8935_, 0, v___x_8934_);
lean_ctor_set_float32(v___x_8935_, 4, v___x_8934_);
lean_ctor_set_float32(v___x_8935_, 8, v___x_8934_);
lean_ctor_set_float32(v___x_8935_, 12, v___x_8934_);
lean_ctor_set_float32(v___x_8935_, 16, v___x_8934_);
lean_ctor_set_float32(v___x_8935_, 20, v___x_8934_);
lean_ctor_set_float32(v___x_8935_, 24, v___x_8934_);
lean_ctor_set_float32(v___x_8935_, 28, v___x_8934_);
lean_ctor_set_float32(v___x_8935_, 32, v___x_8934_);
lean_ctor_set_float32(v___x_8935_, 36, v___x_8934_);
return v___x_8935_;
}
}
static lean_object* _init_lp_competition_Submission_Packed10_zero10(void){
_start:
{
lean_object* v___x_8936_; 
v___x_8936_ = lean_obj_once(&lp_competition_Submission_Packed10_zero10___closed__0, &lp_competition_Submission_Packed10_zero10___closed__0_once, _init_lp_competition_Submission_Packed10_zero10___closed__0);
return v___x_8936_;
}
}
LEAN_EXPORT float lp_competition_Submission_Packed10_lane(lean_object* v_v_8937_, lean_object* v_l_8938_){
_start:
{
lean_object* v___x_8939_; uint8_t v___x_8940_; 
v___x_8939_ = lean_unsigned_to_nat(0u);
v___x_8940_ = lean_nat_dec_eq(v_l_8938_, v___x_8939_);
if (v___x_8940_ == 0)
{
lean_object* v___x_8941_; uint8_t v___x_8942_; 
v___x_8941_ = lean_unsigned_to_nat(1u);
v___x_8942_ = lean_nat_dec_eq(v_l_8938_, v___x_8941_);
if (v___x_8942_ == 0)
{
lean_object* v___x_8943_; uint8_t v___x_8944_; 
v___x_8943_ = lean_unsigned_to_nat(2u);
v___x_8944_ = lean_nat_dec_eq(v_l_8938_, v___x_8943_);
if (v___x_8944_ == 0)
{
lean_object* v___x_8945_; uint8_t v___x_8946_; 
v___x_8945_ = lean_unsigned_to_nat(3u);
v___x_8946_ = lean_nat_dec_eq(v_l_8938_, v___x_8945_);
if (v___x_8946_ == 0)
{
lean_object* v___x_8947_; uint8_t v___x_8948_; 
v___x_8947_ = lean_unsigned_to_nat(4u);
v___x_8948_ = lean_nat_dec_eq(v_l_8938_, v___x_8947_);
if (v___x_8948_ == 0)
{
lean_object* v___x_8949_; uint8_t v___x_8950_; 
v___x_8949_ = lean_unsigned_to_nat(5u);
v___x_8950_ = lean_nat_dec_eq(v_l_8938_, v___x_8949_);
if (v___x_8950_ == 0)
{
lean_object* v___x_8951_; uint8_t v___x_8952_; 
v___x_8951_ = lean_unsigned_to_nat(6u);
v___x_8952_ = lean_nat_dec_eq(v_l_8938_, v___x_8951_);
if (v___x_8952_ == 0)
{
lean_object* v___x_8953_; uint8_t v___x_8954_; 
v___x_8953_ = lean_unsigned_to_nat(7u);
v___x_8954_ = lean_nat_dec_eq(v_l_8938_, v___x_8953_);
if (v___x_8954_ == 0)
{
lean_object* v___x_8955_; uint8_t v___x_8956_; 
v___x_8955_ = lean_unsigned_to_nat(8u);
v___x_8956_ = lean_nat_dec_eq(v_l_8938_, v___x_8955_);
if (v___x_8956_ == 0)
{
float v_s9_8957_; 
v_s9_8957_ = lean_ctor_get_float32(v_v_8937_, 36);
return v_s9_8957_;
}
else
{
float v_s8_8958_; 
v_s8_8958_ = lean_ctor_get_float32(v_v_8937_, 32);
return v_s8_8958_;
}
}
else
{
float v_s7_8959_; 
v_s7_8959_ = lean_ctor_get_float32(v_v_8937_, 28);
return v_s7_8959_;
}
}
else
{
float v_s6_8960_; 
v_s6_8960_ = lean_ctor_get_float32(v_v_8937_, 24);
return v_s6_8960_;
}
}
else
{
float v_s5_8961_; 
v_s5_8961_ = lean_ctor_get_float32(v_v_8937_, 20);
return v_s5_8961_;
}
}
else
{
float v_s4_8962_; 
v_s4_8962_ = lean_ctor_get_float32(v_v_8937_, 16);
return v_s4_8962_;
}
}
else
{
float v_s3_8963_; 
v_s3_8963_ = lean_ctor_get_float32(v_v_8937_, 12);
return v_s3_8963_;
}
}
else
{
float v_s2_8964_; 
v_s2_8964_ = lean_ctor_get_float32(v_v_8937_, 8);
return v_s2_8964_;
}
}
else
{
float v_s1_8965_; 
v_s1_8965_ = lean_ctor_get_float32(v_v_8937_, 4);
return v_s1_8965_;
}
}
else
{
float v_s0_8966_; 
v_s0_8966_ = lean_ctor_get_float32(v_v_8937_, 0);
return v_s0_8966_;
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_Packed10_lane___boxed(lean_object* v_v_8967_, lean_object* v_l_8968_){
_start:
{
float v_res_8969_; lean_object* v_r_8970_; 
v_res_8969_ = lp_competition_Submission_Packed10_lane(v_v_8967_, v_l_8968_);
lean_dec(v_l_8968_);
lean_dec_ref(v_v_8967_);
v_r_8970_ = lean_box_float32(v_res_8969_);
return v_r_8970_;
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_Packed10_packet(lean_object* v_read_8971_, lean_object* v_col_8972_){
_start:
{
lean_object* v___x_8973_; lean_object* v___x_8974_; lean_object* v___x_8975_; lean_object* v___x_8976_; lean_object* v___x_8977_; lean_object* v___x_8978_; lean_object* v___x_8979_; lean_object* v___x_8980_; lean_object* v___x_8981_; lean_object* v___x_8982_; lean_object* v___x_8983_; lean_object* v___x_8984_; lean_object* v___x_8985_; lean_object* v___x_8986_; lean_object* v___x_8987_; lean_object* v___x_8988_; lean_object* v___x_8989_; lean_object* v___x_8990_; lean_object* v___x_8991_; lean_object* v___x_8992_; lean_object* v___x_8993_; lean_object* v___x_8994_; lean_object* v___x_8995_; lean_object* v___x_8996_; lean_object* v___x_8997_; lean_object* v___x_8998_; lean_object* v___x_8999_; lean_object* v___x_9000_; lean_object* v___x_9001_; float v___x_9002_; float v___x_9003_; float v___x_9004_; float v___x_9005_; float v___x_9006_; float v___x_9007_; float v___x_9008_; float v___x_9009_; float v___x_9010_; float v___x_9011_; 
lean_inc_ref_n(v_read_8971_, 9);
lean_inc(v_col_8972_);
v___x_8973_ = lean_apply_1(v_read_8971_, v_col_8972_);
v___x_8974_ = lean_unsigned_to_nat(1u);
v___x_8975_ = lean_nat_add(v_col_8972_, v___x_8974_);
v___x_8976_ = lean_apply_1(v_read_8971_, v___x_8975_);
v___x_8977_ = lean_unsigned_to_nat(2u);
v___x_8978_ = lean_nat_add(v_col_8972_, v___x_8977_);
v___x_8979_ = lean_apply_1(v_read_8971_, v___x_8978_);
v___x_8980_ = lean_unsigned_to_nat(3u);
v___x_8981_ = lean_nat_add(v_col_8972_, v___x_8980_);
v___x_8982_ = lean_apply_1(v_read_8971_, v___x_8981_);
v___x_8983_ = lean_unsigned_to_nat(4u);
v___x_8984_ = lean_nat_add(v_col_8972_, v___x_8983_);
v___x_8985_ = lean_apply_1(v_read_8971_, v___x_8984_);
v___x_8986_ = lean_unsigned_to_nat(5u);
v___x_8987_ = lean_nat_add(v_col_8972_, v___x_8986_);
v___x_8988_ = lean_apply_1(v_read_8971_, v___x_8987_);
v___x_8989_ = lean_unsigned_to_nat(6u);
v___x_8990_ = lean_nat_add(v_col_8972_, v___x_8989_);
v___x_8991_ = lean_apply_1(v_read_8971_, v___x_8990_);
v___x_8992_ = lean_unsigned_to_nat(7u);
v___x_8993_ = lean_nat_add(v_col_8972_, v___x_8992_);
v___x_8994_ = lean_apply_1(v_read_8971_, v___x_8993_);
v___x_8995_ = lean_unsigned_to_nat(8u);
v___x_8996_ = lean_nat_add(v_col_8972_, v___x_8995_);
v___x_8997_ = lean_apply_1(v_read_8971_, v___x_8996_);
v___x_8998_ = lean_unsigned_to_nat(9u);
v___x_8999_ = lean_nat_add(v_col_8972_, v___x_8998_);
lean_dec(v_col_8972_);
v___x_9000_ = lean_apply_1(v_read_8971_, v___x_8999_);
v___x_9001_ = lean_alloc_ctor(0, 0, 40);
v___x_9002_ = lean_unbox_float32(v___x_8973_);
lean_dec_ref(v___x_8973_);
lean_ctor_set_float32(v___x_9001_, 0, v___x_9002_);
v___x_9003_ = lean_unbox_float32(v___x_8976_);
lean_dec_ref(v___x_8976_);
lean_ctor_set_float32(v___x_9001_, 4, v___x_9003_);
v___x_9004_ = lean_unbox_float32(v___x_8979_);
lean_dec_ref(v___x_8979_);
lean_ctor_set_float32(v___x_9001_, 8, v___x_9004_);
v___x_9005_ = lean_unbox_float32(v___x_8982_);
lean_dec_ref(v___x_8982_);
lean_ctor_set_float32(v___x_9001_, 12, v___x_9005_);
v___x_9006_ = lean_unbox_float32(v___x_8985_);
lean_dec_ref(v___x_8985_);
lean_ctor_set_float32(v___x_9001_, 16, v___x_9006_);
v___x_9007_ = lean_unbox_float32(v___x_8988_);
lean_dec_ref(v___x_8988_);
lean_ctor_set_float32(v___x_9001_, 20, v___x_9007_);
v___x_9008_ = lean_unbox_float32(v___x_8991_);
lean_dec_ref(v___x_8991_);
lean_ctor_set_float32(v___x_9001_, 24, v___x_9008_);
v___x_9009_ = lean_unbox_float32(v___x_8994_);
lean_dec_ref(v___x_8994_);
lean_ctor_set_float32(v___x_9001_, 28, v___x_9009_);
v___x_9010_ = lean_unbox_float32(v___x_8997_);
lean_dec_ref(v___x_8997_);
lean_ctor_set_float32(v___x_9001_, 32, v___x_9010_);
v___x_9011_ = lean_unbox_float32(v___x_9000_);
lean_dec_ref(v___x_9000_);
lean_ctor_set_float32(v___x_9001_, 36, v___x_9011_);
return v___x_9001_;
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_Packed10_update(lean_object* v_acc_9012_, float v_a_9013_, lean_object* v_v_9014_){
_start:
{
float v_s0_9015_; float v_s1_9016_; float v_s2_9017_; float v_s3_9018_; float v_s4_9019_; float v_s5_9020_; float v_s6_9021_; float v_s7_9022_; float v_s8_9023_; float v_s9_9024_; float v_s0_9025_; float v_s1_9026_; float v_s2_9027_; float v_s3_9028_; float v_s4_9029_; float v_s5_9030_; float v_s6_9031_; float v_s7_9032_; float v_s8_9033_; float v_s9_9034_; lean_object* v___x_9036_; uint8_t v_isShared_9037_; uint8_t v_isSharedCheck_9061_; 
v_s0_9015_ = lean_ctor_get_float32(v_acc_9012_, 0);
v_s1_9016_ = lean_ctor_get_float32(v_acc_9012_, 4);
v_s2_9017_ = lean_ctor_get_float32(v_acc_9012_, 8);
v_s3_9018_ = lean_ctor_get_float32(v_acc_9012_, 12);
v_s4_9019_ = lean_ctor_get_float32(v_acc_9012_, 16);
v_s5_9020_ = lean_ctor_get_float32(v_acc_9012_, 20);
v_s6_9021_ = lean_ctor_get_float32(v_acc_9012_, 24);
v_s7_9022_ = lean_ctor_get_float32(v_acc_9012_, 28);
v_s8_9023_ = lean_ctor_get_float32(v_acc_9012_, 32);
v_s9_9024_ = lean_ctor_get_float32(v_acc_9012_, 36);
v_s0_9025_ = lean_ctor_get_float32(v_v_9014_, 0);
v_s1_9026_ = lean_ctor_get_float32(v_v_9014_, 4);
v_s2_9027_ = lean_ctor_get_float32(v_v_9014_, 8);
v_s3_9028_ = lean_ctor_get_float32(v_v_9014_, 12);
v_s4_9029_ = lean_ctor_get_float32(v_v_9014_, 16);
v_s5_9030_ = lean_ctor_get_float32(v_v_9014_, 20);
v_s6_9031_ = lean_ctor_get_float32(v_v_9014_, 24);
v_s7_9032_ = lean_ctor_get_float32(v_v_9014_, 28);
v_s8_9033_ = lean_ctor_get_float32(v_v_9014_, 32);
v_s9_9034_ = lean_ctor_get_float32(v_v_9014_, 36);
v_isSharedCheck_9061_ = !lean_is_exclusive(v_v_9014_);
if (v_isSharedCheck_9061_ == 0)
{
v___x_9036_ = v_v_9014_;
v_isShared_9037_ = v_isSharedCheck_9061_;
goto v_resetjp_9035_;
}
else
{
lean_dec(v_v_9014_);
v___x_9036_ = lean_box(0);
v_isShared_9037_ = v_isSharedCheck_9061_;
goto v_resetjp_9035_;
}
v_resetjp_9035_:
{
float v___x_9038_; float v___x_9039_; float v___x_9040_; float v___x_9041_; float v___x_9042_; float v___x_9043_; float v___x_9044_; float v___x_9045_; float v___x_9046_; float v___x_9047_; float v___x_9048_; float v___x_9049_; float v___x_9050_; float v___x_9051_; float v___x_9052_; float v___x_9053_; float v___x_9054_; float v___x_9055_; float v___x_9056_; float v___x_9057_; lean_object* v___x_9059_; 
v___x_9038_ = lean_float32_mul(v_a_9013_, v_s0_9025_);
v___x_9039_ = lean_float32_add(v_s0_9015_, v___x_9038_);
v___x_9040_ = lean_float32_mul(v_a_9013_, v_s1_9026_);
v___x_9041_ = lean_float32_add(v_s1_9016_, v___x_9040_);
v___x_9042_ = lean_float32_mul(v_a_9013_, v_s2_9027_);
v___x_9043_ = lean_float32_add(v_s2_9017_, v___x_9042_);
v___x_9044_ = lean_float32_mul(v_a_9013_, v_s3_9028_);
v___x_9045_ = lean_float32_add(v_s3_9018_, v___x_9044_);
v___x_9046_ = lean_float32_mul(v_a_9013_, v_s4_9029_);
v___x_9047_ = lean_float32_add(v_s4_9019_, v___x_9046_);
v___x_9048_ = lean_float32_mul(v_a_9013_, v_s5_9030_);
v___x_9049_ = lean_float32_add(v_s5_9020_, v___x_9048_);
v___x_9050_ = lean_float32_mul(v_a_9013_, v_s6_9031_);
v___x_9051_ = lean_float32_add(v_s6_9021_, v___x_9050_);
v___x_9052_ = lean_float32_mul(v_a_9013_, v_s7_9032_);
v___x_9053_ = lean_float32_add(v_s7_9022_, v___x_9052_);
v___x_9054_ = lean_float32_mul(v_a_9013_, v_s8_9033_);
v___x_9055_ = lean_float32_add(v_s8_9023_, v___x_9054_);
v___x_9056_ = lean_float32_mul(v_a_9013_, v_s9_9034_);
v___x_9057_ = lean_float32_add(v_s9_9024_, v___x_9056_);
if (v_isShared_9037_ == 0)
{
v___x_9059_ = v___x_9036_;
goto v_reusejp_9058_;
}
else
{
lean_object* v_reuseFailAlloc_9060_; 
v_reuseFailAlloc_9060_ = lean_alloc_ctor(0, 0, 40);
v___x_9059_ = v_reuseFailAlloc_9060_;
goto v_reusejp_9058_;
}
v_reusejp_9058_:
{
lean_ctor_set_float32(v___x_9059_, 0, v___x_9039_);
lean_ctor_set_float32(v___x_9059_, 4, v___x_9041_);
lean_ctor_set_float32(v___x_9059_, 8, v___x_9043_);
lean_ctor_set_float32(v___x_9059_, 12, v___x_9045_);
lean_ctor_set_float32(v___x_9059_, 16, v___x_9047_);
lean_ctor_set_float32(v___x_9059_, 20, v___x_9049_);
lean_ctor_set_float32(v___x_9059_, 24, v___x_9051_);
lean_ctor_set_float32(v___x_9059_, 28, v___x_9053_);
lean_ctor_set_float32(v___x_9059_, 32, v___x_9055_);
lean_ctor_set_float32(v___x_9059_, 36, v___x_9057_);
return v___x_9059_;
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_Packed10_update___boxed(lean_object* v_acc_9062_, lean_object* v_a_9063_, lean_object* v_v_9064_){
_start:
{
float v_a_boxed_9065_; lean_object* v_res_9066_; 
v_a_boxed_9065_ = lean_unbox_float32(v_a_9063_);
lean_dec_ref(v_a_9063_);
v_res_9066_ = lp_competition_Submission_Packed10_update(v_acc_9062_, v_a_boxed_9065_, v_v_9064_);
lean_dec_ref(v_acc_9062_);
return v_res_9066_;
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_Packed10_groups(lean_object* v_p_9067_){
_start:
{
lean_object* v___x_9068_; lean_object* v___x_9069_; lean_object* v___x_9070_; lean_object* v___x_9071_; 
v___x_9068_ = lean_unsigned_to_nat(9u);
v___x_9069_ = lean_nat_add(v_p_9067_, v___x_9068_);
v___x_9070_ = lean_unsigned_to_nat(10u);
v___x_9071_ = lean_nat_div(v___x_9069_, v___x_9070_);
lean_dec(v___x_9069_);
return v___x_9071_;
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_Packed10_groups___boxed(lean_object* v_p_9072_){
_start:
{
lean_object* v_res_9073_; 
v_res_9073_ = lp_competition_Submission_Packed10_groups(v_p_9072_);
lean_dec(v_p_9072_);
return v_res_9073_;
}
}
LEAN_EXPORT float lp_competition_Submission_Packed10_packB___lam__0(lean_object* v_p_9074_, lean_object* v_base_9075_, lean_object* v_B_9076_, lean_object* v_j_9077_){
_start:
{
uint8_t v___x_9078_; 
v___x_9078_ = lean_nat_dec_lt(v_j_9077_, v_p_9074_);
if (v___x_9078_ == 0)
{
float v___x_9079_; 
v___x_9079_ = lean_float32_once(&lp_competition_Submission_NativeFinal_dot___closed__0, &lp_competition_Submission_NativeFinal_dot___closed__0_once, _init_lp_competition_Submission_NativeFinal_dot___closed__0);
return v___x_9079_;
}
else
{
lean_object* v___x_9080_; lean_object* v___x_9081_; uint32_t v___x_9082_; float v___x_9083_; 
v___x_9080_ = lean_nat_add(v_base_9075_, v_j_9077_);
v___x_9081_ = lean_array_fget_borrowed(v_B_9076_, v___x_9080_);
lean_dec(v___x_9080_);
v___x_9082_ = lean_unbox_uint32(v___x_9081_);
v___x_9083_ = lean_float32_of_bits(v___x_9082_);
return v___x_9083_;
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_Packed10_packB___lam__0___boxed(lean_object* v_p_9084_, lean_object* v_base_9085_, lean_object* v_B_9086_, lean_object* v_j_9087_){
_start:
{
float v_res_9088_; lean_object* v_r_9089_; 
v_res_9088_ = lp_competition_Submission_Packed10_packB___lam__0(v_p_9084_, v_base_9085_, v_B_9086_, v_j_9087_);
lean_dec(v_j_9087_);
lean_dec_ref(v_B_9086_);
lean_dec(v_base_9085_);
lean_dec(v_p_9084_);
v_r_9089_ = lean_box_float32(v_res_9088_);
return v_r_9089_;
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_Packed10_packB___lam__1(lean_object* v_b_9090_, lean_object* v_n_9091_, lean_object* v_p_9092_, lean_object* v_B_9093_, lean_object* v_g_9094_, lean_object* v_k_9095_){
_start:
{
lean_object* v___x_9096_; lean_object* v___x_9097_; lean_object* v_base_9098_; lean_object* v___x_9099_; lean_object* v___x_9100_; float v___x_9101_; lean_object* v___x_9102_; lean_object* v___x_9103_; float v___x_9104_; lean_object* v___x_9105_; lean_object* v___x_9106_; float v___x_9107_; lean_object* v___x_9108_; lean_object* v___x_9109_; float v___x_9110_; lean_object* v___x_9111_; lean_object* v___x_9112_; float v___x_9113_; lean_object* v___x_9114_; lean_object* v___x_9115_; float v___x_9116_; lean_object* v___x_9117_; lean_object* v___x_9118_; float v___x_9119_; lean_object* v___x_9120_; lean_object* v___x_9121_; float v___x_9122_; lean_object* v___x_9123_; lean_object* v___x_9124_; float v___x_9125_; lean_object* v___x_9126_; lean_object* v___x_9127_; float v___x_9128_; lean_object* v___x_9129_; 
v___x_9096_ = lean_nat_mul(v_b_9090_, v_n_9091_);
v___x_9097_ = lean_nat_add(v___x_9096_, v_k_9095_);
lean_dec(v___x_9096_);
v_base_9098_ = lean_nat_mul(v___x_9097_, v_p_9092_);
lean_dec(v___x_9097_);
v___x_9099_ = lean_unsigned_to_nat(10u);
v___x_9100_ = lean_nat_mul(v___x_9099_, v_g_9094_);
v___x_9101_ = lp_competition_Submission_Packed10_packB___lam__0(v_p_9092_, v_base_9098_, v_B_9093_, v___x_9100_);
v___x_9102_ = lean_unsigned_to_nat(1u);
v___x_9103_ = lean_nat_add(v___x_9100_, v___x_9102_);
v___x_9104_ = lp_competition_Submission_Packed10_packB___lam__0(v_p_9092_, v_base_9098_, v_B_9093_, v___x_9103_);
lean_dec(v___x_9103_);
v___x_9105_ = lean_unsigned_to_nat(2u);
v___x_9106_ = lean_nat_add(v___x_9100_, v___x_9105_);
v___x_9107_ = lp_competition_Submission_Packed10_packB___lam__0(v_p_9092_, v_base_9098_, v_B_9093_, v___x_9106_);
lean_dec(v___x_9106_);
v___x_9108_ = lean_unsigned_to_nat(3u);
v___x_9109_ = lean_nat_add(v___x_9100_, v___x_9108_);
v___x_9110_ = lp_competition_Submission_Packed10_packB___lam__0(v_p_9092_, v_base_9098_, v_B_9093_, v___x_9109_);
lean_dec(v___x_9109_);
v___x_9111_ = lean_unsigned_to_nat(4u);
v___x_9112_ = lean_nat_add(v___x_9100_, v___x_9111_);
v___x_9113_ = lp_competition_Submission_Packed10_packB___lam__0(v_p_9092_, v_base_9098_, v_B_9093_, v___x_9112_);
lean_dec(v___x_9112_);
v___x_9114_ = lean_unsigned_to_nat(5u);
v___x_9115_ = lean_nat_add(v___x_9100_, v___x_9114_);
v___x_9116_ = lp_competition_Submission_Packed10_packB___lam__0(v_p_9092_, v_base_9098_, v_B_9093_, v___x_9115_);
lean_dec(v___x_9115_);
v___x_9117_ = lean_unsigned_to_nat(6u);
v___x_9118_ = lean_nat_add(v___x_9100_, v___x_9117_);
v___x_9119_ = lp_competition_Submission_Packed10_packB___lam__0(v_p_9092_, v_base_9098_, v_B_9093_, v___x_9118_);
lean_dec(v___x_9118_);
v___x_9120_ = lean_unsigned_to_nat(7u);
v___x_9121_ = lean_nat_add(v___x_9100_, v___x_9120_);
v___x_9122_ = lp_competition_Submission_Packed10_packB___lam__0(v_p_9092_, v_base_9098_, v_B_9093_, v___x_9121_);
lean_dec(v___x_9121_);
v___x_9123_ = lean_unsigned_to_nat(8u);
v___x_9124_ = lean_nat_add(v___x_9100_, v___x_9123_);
v___x_9125_ = lp_competition_Submission_Packed10_packB___lam__0(v_p_9092_, v_base_9098_, v_B_9093_, v___x_9124_);
lean_dec(v___x_9124_);
v___x_9126_ = lean_unsigned_to_nat(9u);
v___x_9127_ = lean_nat_add(v___x_9100_, v___x_9126_);
lean_dec(v___x_9100_);
v___x_9128_ = lp_competition_Submission_Packed10_packB___lam__0(v_p_9092_, v_base_9098_, v_B_9093_, v___x_9127_);
lean_dec(v___x_9127_);
lean_dec(v_base_9098_);
v___x_9129_ = lean_alloc_ctor(0, 0, 40);
lean_ctor_set_float32(v___x_9129_, 0, v___x_9101_);
lean_ctor_set_float32(v___x_9129_, 4, v___x_9104_);
lean_ctor_set_float32(v___x_9129_, 8, v___x_9107_);
lean_ctor_set_float32(v___x_9129_, 12, v___x_9110_);
lean_ctor_set_float32(v___x_9129_, 16, v___x_9113_);
lean_ctor_set_float32(v___x_9129_, 20, v___x_9116_);
lean_ctor_set_float32(v___x_9129_, 24, v___x_9119_);
lean_ctor_set_float32(v___x_9129_, 28, v___x_9122_);
lean_ctor_set_float32(v___x_9129_, 32, v___x_9125_);
lean_ctor_set_float32(v___x_9129_, 36, v___x_9128_);
return v___x_9129_;
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_Packed10_packB___lam__1___boxed(lean_object* v_b_9130_, lean_object* v_n_9131_, lean_object* v_p_9132_, lean_object* v_B_9133_, lean_object* v_g_9134_, lean_object* v_k_9135_){
_start:
{
lean_object* v_res_9136_; 
v_res_9136_ = lp_competition_Submission_Packed10_packB___lam__1(v_b_9130_, v_n_9131_, v_p_9132_, v_B_9133_, v_g_9134_, v_k_9135_);
lean_dec(v_k_9135_);
lean_dec(v_g_9134_);
lean_dec_ref(v_B_9133_);
lean_dec(v_p_9132_);
lean_dec(v_n_9131_);
lean_dec(v_b_9130_);
return v_res_9136_;
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_Packed10_packB___lam__2(lean_object* v_b_9137_, lean_object* v_n_9138_, lean_object* v_p_9139_, lean_object* v_B_9140_, lean_object* v_g_9141_){
_start:
{
lean_object* v___f_9142_; lean_object* v___x_9143_; 
lean_inc(v_n_9138_);
v___f_9142_ = lean_alloc_closure((void*)(lp_competition_Submission_Packed10_packB___lam__1___boxed), 6, 5);
lean_closure_set(v___f_9142_, 0, v_b_9137_);
lean_closure_set(v___f_9142_, 1, v_n_9138_);
lean_closure_set(v___f_9142_, 2, v_p_9139_);
lean_closure_set(v___f_9142_, 3, v_B_9140_);
lean_closure_set(v___f_9142_, 4, v_g_9141_);
v___x_9143_ = l_Array_ofFn___redArg(v_n_9138_, v___f_9142_);
return v___x_9143_;
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_Packed10_packB___lam__3(lean_object* v_n_9144_, lean_object* v_p_9145_, lean_object* v_B_9146_, lean_object* v_b_9147_){
_start:
{
lean_object* v___f_9148_; lean_object* v___x_9149_; lean_object* v___x_9150_; lean_object* v___x_9151_; lean_object* v___x_9152_; lean_object* v___x_9153_; 
lean_inc(v_p_9145_);
v___f_9148_ = lean_alloc_closure((void*)(lp_competition_Submission_Packed10_packB___lam__2), 5, 4);
lean_closure_set(v___f_9148_, 0, v_b_9147_);
lean_closure_set(v___f_9148_, 1, v_n_9144_);
lean_closure_set(v___f_9148_, 2, v_p_9145_);
lean_closure_set(v___f_9148_, 3, v_B_9146_);
v___x_9149_ = lean_unsigned_to_nat(9u);
v___x_9150_ = lean_nat_add(v_p_9145_, v___x_9149_);
lean_dec(v_p_9145_);
v___x_9151_ = lean_unsigned_to_nat(10u);
v___x_9152_ = lean_nat_div(v___x_9150_, v___x_9151_);
lean_dec(v___x_9150_);
v___x_9153_ = l_Array_ofFn___redArg(v___x_9152_, v___f_9148_);
return v___x_9153_;
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_Packed10_packB(lean_object* v_batch_9154_, lean_object* v_n_9155_, lean_object* v_p_9156_, lean_object* v_B_9157_){
_start:
{
lean_object* v___f_9158_; lean_object* v___x_9159_; 
v___f_9158_ = lean_alloc_closure((void*)(lp_competition_Submission_Packed10_packB___lam__3), 4, 3);
lean_closure_set(v___f_9158_, 0, v_n_9155_);
lean_closure_set(v___f_9158_, 1, v_p_9156_);
lean_closure_set(v___f_9158_, 2, v_B_9157_);
v___x_9159_ = l_Array_ofFn___redArg(v_batch_9154_, v___f_9158_);
return v___x_9159_;
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_Packed10_dot10(lean_object* v_n_9160_, lean_object* v_baseA_9161_, lean_object* v_A_9162_, lean_object* v_B_9163_, lean_object* v_k_9164_, float v_s0_9165_, float v_s1_9166_, float v_s2_9167_, float v_s3_9168_, float v_s4_9169_, float v_s5_9170_, float v_s6_9171_, float v_s7_9172_, float v_s8_9173_, float v_s9_9174_){
_start:
{
float v___y_9176_; uint8_t v___x_9211_; 
v___x_9211_ = lean_nat_dec_lt(v_k_9164_, v_n_9160_);
if (v___x_9211_ == 0)
{
lean_object* v___x_9212_; 
lean_dec(v_k_9164_);
v___x_9212_ = lean_alloc_ctor(0, 0, 40);
lean_ctor_set_float32(v___x_9212_, 0, v_s0_9165_);
lean_ctor_set_float32(v___x_9212_, 4, v_s1_9166_);
lean_ctor_set_float32(v___x_9212_, 8, v_s2_9167_);
lean_ctor_set_float32(v___x_9212_, 12, v_s3_9168_);
lean_ctor_set_float32(v___x_9212_, 16, v_s4_9169_);
lean_ctor_set_float32(v___x_9212_, 20, v_s5_9170_);
lean_ctor_set_float32(v___x_9212_, 24, v_s6_9171_);
lean_ctor_set_float32(v___x_9212_, 28, v_s7_9172_);
lean_ctor_set_float32(v___x_9212_, 32, v_s8_9173_);
lean_ctor_set_float32(v___x_9212_, 36, v_s9_9174_);
return v___x_9212_;
}
else
{
lean_object* v___x_9213_; lean_object* v___x_9214_; uint8_t v___x_9215_; 
v___x_9213_ = lean_nat_add(v_baseA_9161_, v_k_9164_);
v___x_9214_ = lean_array_get_size(v_A_9162_);
v___x_9215_ = lean_nat_dec_lt(v___x_9213_, v___x_9214_);
if (v___x_9215_ == 0)
{
float v___x_9216_; 
lean_dec(v___x_9213_);
v___x_9216_ = lean_float32_once(&lp_competition_Submission_NativeFinal_dot___closed__0, &lp_competition_Submission_NativeFinal_dot___closed__0_once, _init_lp_competition_Submission_NativeFinal_dot___closed__0);
v___y_9176_ = v___x_9216_;
goto v___jp_9175_;
}
else
{
lean_object* v___x_9217_; float v___x_9218_; 
v___x_9217_ = lean_array_fget_borrowed(v_A_9162_, v___x_9213_);
lean_dec(v___x_9213_);
v___x_9218_ = lean_unbox_float32(v___x_9217_);
v___y_9176_ = v___x_9218_;
goto v___jp_9175_;
}
}
v___jp_9175_:
{
lean_object* v_v_9177_; float v_s0_9178_; float v_s1_9179_; float v_s2_9180_; float v_s3_9181_; float v_s4_9182_; float v_s5_9183_; float v_s6_9184_; float v_s7_9185_; float v_s8_9186_; float v_s9_9187_; lean_object* v___x_9188_; lean_object* v___x_9189_; float v___x_9190_; float v___x_9191_; float v___x_9192_; float v___x_9193_; float v___x_9194_; float v___x_9195_; float v___x_9196_; float v___x_9197_; float v___x_9198_; float v___x_9199_; float v___x_9200_; float v___x_9201_; float v___x_9202_; float v___x_9203_; float v___x_9204_; float v___x_9205_; float v___x_9206_; float v___x_9207_; float v___x_9208_; float v___x_9209_; 
v_v_9177_ = lean_array_fget_borrowed(v_B_9163_, v_k_9164_);
v_s0_9178_ = lean_ctor_get_float32(v_v_9177_, 0);
v_s1_9179_ = lean_ctor_get_float32(v_v_9177_, 4);
v_s2_9180_ = lean_ctor_get_float32(v_v_9177_, 8);
v_s3_9181_ = lean_ctor_get_float32(v_v_9177_, 12);
v_s4_9182_ = lean_ctor_get_float32(v_v_9177_, 16);
v_s5_9183_ = lean_ctor_get_float32(v_v_9177_, 20);
v_s6_9184_ = lean_ctor_get_float32(v_v_9177_, 24);
v_s7_9185_ = lean_ctor_get_float32(v_v_9177_, 28);
v_s8_9186_ = lean_ctor_get_float32(v_v_9177_, 32);
v_s9_9187_ = lean_ctor_get_float32(v_v_9177_, 36);
v___x_9188_ = lean_unsigned_to_nat(1u);
v___x_9189_ = lean_nat_add(v_k_9164_, v___x_9188_);
lean_dec(v_k_9164_);
v___x_9190_ = lean_float32_mul(v___y_9176_, v_s0_9178_);
v___x_9191_ = lean_float32_add(v_s0_9165_, v___x_9190_);
v___x_9192_ = lean_float32_mul(v___y_9176_, v_s1_9179_);
v___x_9193_ = lean_float32_add(v_s1_9166_, v___x_9192_);
v___x_9194_ = lean_float32_mul(v___y_9176_, v_s2_9180_);
v___x_9195_ = lean_float32_add(v_s2_9167_, v___x_9194_);
v___x_9196_ = lean_float32_mul(v___y_9176_, v_s3_9181_);
v___x_9197_ = lean_float32_add(v_s3_9168_, v___x_9196_);
v___x_9198_ = lean_float32_mul(v___y_9176_, v_s4_9182_);
v___x_9199_ = lean_float32_add(v_s4_9169_, v___x_9198_);
v___x_9200_ = lean_float32_mul(v___y_9176_, v_s5_9183_);
v___x_9201_ = lean_float32_add(v_s5_9170_, v___x_9200_);
v___x_9202_ = lean_float32_mul(v___y_9176_, v_s6_9184_);
v___x_9203_ = lean_float32_add(v_s6_9171_, v___x_9202_);
v___x_9204_ = lean_float32_mul(v___y_9176_, v_s7_9185_);
v___x_9205_ = lean_float32_add(v_s7_9172_, v___x_9204_);
v___x_9206_ = lean_float32_mul(v___y_9176_, v_s8_9186_);
v___x_9207_ = lean_float32_add(v_s8_9173_, v___x_9206_);
v___x_9208_ = lean_float32_mul(v___y_9176_, v_s9_9187_);
v___x_9209_ = lean_float32_add(v_s9_9174_, v___x_9208_);
v_k_9164_ = v___x_9189_;
v_s0_9165_ = v___x_9191_;
v_s1_9166_ = v___x_9193_;
v_s2_9167_ = v___x_9195_;
v_s3_9168_ = v___x_9197_;
v_s4_9169_ = v___x_9199_;
v_s5_9170_ = v___x_9201_;
v_s6_9171_ = v___x_9203_;
v_s7_9172_ = v___x_9205_;
v_s8_9173_ = v___x_9207_;
v_s9_9174_ = v___x_9209_;
goto _start;
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_Packed10_dot10___boxed(lean_object* v_n_9219_, lean_object* v_baseA_9220_, lean_object* v_A_9221_, lean_object* v_B_9222_, lean_object* v_k_9223_, lean_object* v_s0_9224_, lean_object* v_s1_9225_, lean_object* v_s2_9226_, lean_object* v_s3_9227_, lean_object* v_s4_9228_, lean_object* v_s5_9229_, lean_object* v_s6_9230_, lean_object* v_s7_9231_, lean_object* v_s8_9232_, lean_object* v_s9_9233_){
_start:
{
float v_s0_boxed_9234_; float v_s1_boxed_9235_; float v_s2_boxed_9236_; float v_s3_boxed_9237_; float v_s4_boxed_9238_; float v_s5_boxed_9239_; float v_s6_boxed_9240_; float v_s7_boxed_9241_; float v_s8_boxed_9242_; float v_s9_boxed_9243_; lean_object* v_res_9244_; 
v_s0_boxed_9234_ = lean_unbox_float32(v_s0_9224_);
lean_dec_ref(v_s0_9224_);
v_s1_boxed_9235_ = lean_unbox_float32(v_s1_9225_);
lean_dec_ref(v_s1_9225_);
v_s2_boxed_9236_ = lean_unbox_float32(v_s2_9226_);
lean_dec_ref(v_s2_9226_);
v_s3_boxed_9237_ = lean_unbox_float32(v_s3_9227_);
lean_dec_ref(v_s3_9227_);
v_s4_boxed_9238_ = lean_unbox_float32(v_s4_9228_);
lean_dec_ref(v_s4_9228_);
v_s5_boxed_9239_ = lean_unbox_float32(v_s5_9229_);
lean_dec_ref(v_s5_9229_);
v_s6_boxed_9240_ = lean_unbox_float32(v_s6_9230_);
lean_dec_ref(v_s6_9230_);
v_s7_boxed_9241_ = lean_unbox_float32(v_s7_9231_);
lean_dec_ref(v_s7_9231_);
v_s8_boxed_9242_ = lean_unbox_float32(v_s8_9232_);
lean_dec_ref(v_s8_9232_);
v_s9_boxed_9243_ = lean_unbox_float32(v_s9_9233_);
lean_dec_ref(v_s9_9233_);
v_res_9244_ = lp_competition_Submission_Packed10_dot10(v_n_9219_, v_baseA_9220_, v_A_9221_, v_B_9222_, v_k_9223_, v_s0_boxed_9234_, v_s1_boxed_9235_, v_s2_boxed_9236_, v_s3_boxed_9237_, v_s4_boxed_9238_, v_s5_boxed_9239_, v_s6_boxed_9240_, v_s7_boxed_9241_, v_s8_boxed_9242_, v_s9_boxed_9243_);
lean_dec_ref(v_B_9222_);
lean_dec_ref(v_A_9221_);
lean_dec(v_baseA_9220_);
lean_dec(v_n_9219_);
return v_res_9244_;
}
}
LEAN_EXPORT uint32_t lp_competition_Submission_Packed10_finish(lean_object* v_n_9245_, lean_object* v_baseA_9246_, lean_object* v_baseB_9247_, lean_object* v_p_9248_, lean_object* v_Araw_9249_, lean_object* v_Braw_9250_, float v_result_9251_){
_start:
{
uint8_t v___x_9252_; 
v___x_9252_ = lean_float32_isfinite(v_result_9251_);
if (v___x_9252_ == 0)
{
lean_object* v___x_9253_; uint32_t v___x_9254_; uint32_t v___x_9255_; 
v___x_9253_ = lean_unsigned_to_nat(0u);
v___x_9254_ = lean_uint32_once(&lp_competition_Submission_referenceSum___redArg___closed__1, &lp_competition_Submission_referenceSum___redArg___closed__1_once, _init_lp_competition_Submission_referenceSum___redArg___closed__1);
v___x_9255_ = lp_competition_Fin_foldl_loop___at___00Submission_NativeFinal_dot_spec__0(v_baseA_9246_, v_p_9248_, v_baseB_9247_, v_Braw_9250_, v_Araw_9249_, v_n_9245_, v___x_9254_, v___x_9253_);
return v___x_9255_;
}
else
{
uint32_t v___x_9256_; 
v___x_9256_ = lean_float32_to_bits(v_result_9251_);
return v___x_9256_;
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_Packed10_finish___boxed(lean_object* v_n_9257_, lean_object* v_baseA_9258_, lean_object* v_baseB_9259_, lean_object* v_p_9260_, lean_object* v_Araw_9261_, lean_object* v_Braw_9262_, lean_object* v_result_9263_){
_start:
{
float v_result_boxed_9264_; uint32_t v_res_9265_; lean_object* v_r_9266_; 
v_result_boxed_9264_ = lean_unbox_float32(v_result_9263_);
lean_dec_ref(v_result_9263_);
v_res_9265_ = lp_competition_Submission_Packed10_finish(v_n_9257_, v_baseA_9258_, v_baseB_9259_, v_p_9260_, v_Araw_9261_, v_Braw_9262_, v_result_boxed_9264_);
lean_dec_ref(v_Braw_9262_);
lean_dec_ref(v_Araw_9261_);
lean_dec(v_p_9260_);
lean_dec(v_baseB_9259_);
lean_dec(v_baseA_9258_);
lean_dec(v_n_9257_);
v_r_9266_ = lean_box_uint32(v_res_9265_);
return v_r_9266_;
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_Packed10Index_loop___redArg(size_t v_count_9267_, size_t v_baseA_9268_, lean_object* v_A_9269_, lean_object* v_B_9270_, size_t v_k_9271_, float v_s0_9272_, float v_s1_9273_, float v_s2_9274_, float v_s3_9275_, float v_s4_9276_, float v_s5_9277_, float v_s6_9278_, float v_s7_9279_, float v_s8_9280_, float v_s9_9281_){
_start:
{
uint8_t v___x_9282_; 
v___x_9282_ = lean_usize_dec_lt(v_k_9271_, v_count_9267_);
if (v___x_9282_ == 0)
{
lean_object* v___x_9283_; 
v___x_9283_ = lean_alloc_ctor(0, 0, 40);
lean_ctor_set_float32(v___x_9283_, 0, v_s0_9272_);
lean_ctor_set_float32(v___x_9283_, 4, v_s1_9273_);
lean_ctor_set_float32(v___x_9283_, 8, v_s2_9274_);
lean_ctor_set_float32(v___x_9283_, 12, v_s3_9275_);
lean_ctor_set_float32(v___x_9283_, 16, v_s4_9276_);
lean_ctor_set_float32(v___x_9283_, 20, v_s5_9277_);
lean_ctor_set_float32(v___x_9283_, 24, v_s6_9278_);
lean_ctor_set_float32(v___x_9283_, 28, v_s7_9279_);
lean_ctor_set_float32(v___x_9283_, 32, v_s8_9280_);
lean_ctor_set_float32(v___x_9283_, 36, v_s9_9281_);
return v___x_9283_;
}
else
{
size_t v___x_9284_; lean_object* v_v_9285_; float v_s0_9286_; float v_s1_9287_; float v_s2_9288_; float v_s3_9289_; float v_s4_9290_; float v_s5_9291_; float v_s6_9292_; float v_s7_9293_; float v_s8_9294_; float v_s9_9295_; lean_object* v_a_9296_; size_t v___x_9297_; size_t v___x_9298_; float v___x_9299_; float v___x_9300_; float v___x_9301_; float v___x_9302_; float v___x_9303_; float v___x_9304_; float v___x_9305_; float v___x_9306_; float v___x_9307_; float v___x_9308_; float v___x_9309_; float v___x_9310_; float v___x_9311_; float v___x_9312_; float v___x_9313_; float v___x_9314_; float v___x_9315_; float v___x_9316_; float v___x_9317_; float v___x_9318_; float v___x_9319_; float v___x_9320_; float v___x_9321_; float v___x_9322_; float v___x_9323_; float v___x_9324_; float v___x_9325_; float v___x_9326_; float v___x_9327_; float v___x_9328_; 
v___x_9284_ = lean_usize_add(v_baseA_9268_, v_k_9271_);
v_v_9285_ = lean_array_uget_borrowed(v_B_9270_, v_k_9271_);
v_s0_9286_ = lean_ctor_get_float32(v_v_9285_, 0);
v_s1_9287_ = lean_ctor_get_float32(v_v_9285_, 4);
v_s2_9288_ = lean_ctor_get_float32(v_v_9285_, 8);
v_s3_9289_ = lean_ctor_get_float32(v_v_9285_, 12);
v_s4_9290_ = lean_ctor_get_float32(v_v_9285_, 16);
v_s5_9291_ = lean_ctor_get_float32(v_v_9285_, 20);
v_s6_9292_ = lean_ctor_get_float32(v_v_9285_, 24);
v_s7_9293_ = lean_ctor_get_float32(v_v_9285_, 28);
v_s8_9294_ = lean_ctor_get_float32(v_v_9285_, 32);
v_s9_9295_ = lean_ctor_get_float32(v_v_9285_, 36);
v_a_9296_ = lean_array_uget_borrowed(v_A_9269_, v___x_9284_);
v___x_9297_ = ((size_t)1ULL);
v___x_9298_ = lean_usize_add(v_k_9271_, v___x_9297_);
v___x_9299_ = lean_unbox_float32(v_a_9296_);
v___x_9300_ = lean_float32_mul(v___x_9299_, v_s0_9286_);
v___x_9301_ = lean_float32_add(v_s0_9272_, v___x_9300_);
v___x_9302_ = lean_unbox_float32(v_a_9296_);
v___x_9303_ = lean_float32_mul(v___x_9302_, v_s1_9287_);
v___x_9304_ = lean_float32_add(v_s1_9273_, v___x_9303_);
v___x_9305_ = lean_unbox_float32(v_a_9296_);
v___x_9306_ = lean_float32_mul(v___x_9305_, v_s2_9288_);
v___x_9307_ = lean_float32_add(v_s2_9274_, v___x_9306_);
v___x_9308_ = lean_unbox_float32(v_a_9296_);
v___x_9309_ = lean_float32_mul(v___x_9308_, v_s3_9289_);
v___x_9310_ = lean_float32_add(v_s3_9275_, v___x_9309_);
v___x_9311_ = lean_unbox_float32(v_a_9296_);
v___x_9312_ = lean_float32_mul(v___x_9311_, v_s4_9290_);
v___x_9313_ = lean_float32_add(v_s4_9276_, v___x_9312_);
v___x_9314_ = lean_unbox_float32(v_a_9296_);
v___x_9315_ = lean_float32_mul(v___x_9314_, v_s5_9291_);
v___x_9316_ = lean_float32_add(v_s5_9277_, v___x_9315_);
v___x_9317_ = lean_unbox_float32(v_a_9296_);
v___x_9318_ = lean_float32_mul(v___x_9317_, v_s6_9292_);
v___x_9319_ = lean_float32_add(v_s6_9278_, v___x_9318_);
v___x_9320_ = lean_unbox_float32(v_a_9296_);
v___x_9321_ = lean_float32_mul(v___x_9320_, v_s7_9293_);
v___x_9322_ = lean_float32_add(v_s7_9279_, v___x_9321_);
v___x_9323_ = lean_unbox_float32(v_a_9296_);
v___x_9324_ = lean_float32_mul(v___x_9323_, v_s8_9294_);
v___x_9325_ = lean_float32_add(v_s8_9280_, v___x_9324_);
v___x_9326_ = lean_unbox_float32(v_a_9296_);
v___x_9327_ = lean_float32_mul(v___x_9326_, v_s9_9295_);
v___x_9328_ = lean_float32_add(v_s9_9281_, v___x_9327_);
v_k_9271_ = v___x_9298_;
v_s0_9272_ = v___x_9301_;
v_s1_9273_ = v___x_9304_;
v_s2_9274_ = v___x_9307_;
v_s3_9275_ = v___x_9310_;
v_s4_9276_ = v___x_9313_;
v_s5_9277_ = v___x_9316_;
v_s6_9278_ = v___x_9319_;
v_s7_9279_ = v___x_9322_;
v_s8_9280_ = v___x_9325_;
v_s9_9281_ = v___x_9328_;
goto _start;
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_Packed10Index_loop___redArg___boxed(lean_object* v_count_9330_, lean_object* v_baseA_9331_, lean_object* v_A_9332_, lean_object* v_B_9333_, lean_object* v_k_9334_, lean_object* v_s0_9335_, lean_object* v_s1_9336_, lean_object* v_s2_9337_, lean_object* v_s3_9338_, lean_object* v_s4_9339_, lean_object* v_s5_9340_, lean_object* v_s6_9341_, lean_object* v_s7_9342_, lean_object* v_s8_9343_, lean_object* v_s9_9344_){
_start:
{
size_t v_count_boxed_9345_; size_t v_baseA_boxed_9346_; size_t v_k_boxed_9347_; float v_s0_boxed_9348_; float v_s1_boxed_9349_; float v_s2_boxed_9350_; float v_s3_boxed_9351_; float v_s4_boxed_9352_; float v_s5_boxed_9353_; float v_s6_boxed_9354_; float v_s7_boxed_9355_; float v_s8_boxed_9356_; float v_s9_boxed_9357_; lean_object* v_res_9358_; 
v_count_boxed_9345_ = lean_unbox_usize(v_count_9330_);
lean_dec(v_count_9330_);
v_baseA_boxed_9346_ = lean_unbox_usize(v_baseA_9331_);
lean_dec(v_baseA_9331_);
v_k_boxed_9347_ = lean_unbox_usize(v_k_9334_);
lean_dec(v_k_9334_);
v_s0_boxed_9348_ = lean_unbox_float32(v_s0_9335_);
lean_dec_ref(v_s0_9335_);
v_s1_boxed_9349_ = lean_unbox_float32(v_s1_9336_);
lean_dec_ref(v_s1_9336_);
v_s2_boxed_9350_ = lean_unbox_float32(v_s2_9337_);
lean_dec_ref(v_s2_9337_);
v_s3_boxed_9351_ = lean_unbox_float32(v_s3_9338_);
lean_dec_ref(v_s3_9338_);
v_s4_boxed_9352_ = lean_unbox_float32(v_s4_9339_);
lean_dec_ref(v_s4_9339_);
v_s5_boxed_9353_ = lean_unbox_float32(v_s5_9340_);
lean_dec_ref(v_s5_9340_);
v_s6_boxed_9354_ = lean_unbox_float32(v_s6_9341_);
lean_dec_ref(v_s6_9341_);
v_s7_boxed_9355_ = lean_unbox_float32(v_s7_9342_);
lean_dec_ref(v_s7_9342_);
v_s8_boxed_9356_ = lean_unbox_float32(v_s8_9343_);
lean_dec_ref(v_s8_9343_);
v_s9_boxed_9357_ = lean_unbox_float32(v_s9_9344_);
lean_dec_ref(v_s9_9344_);
v_res_9358_ = lp_competition_Submission_Packed10Index_loop___redArg(v_count_boxed_9345_, v_baseA_boxed_9346_, v_A_9332_, v_B_9333_, v_k_boxed_9347_, v_s0_boxed_9348_, v_s1_boxed_9349_, v_s2_boxed_9350_, v_s3_boxed_9351_, v_s4_boxed_9352_, v_s5_boxed_9353_, v_s6_boxed_9354_, v_s7_boxed_9355_, v_s8_boxed_9356_, v_s9_boxed_9357_);
lean_dec_ref(v_B_9333_);
lean_dec_ref(v_A_9332_);
return v_res_9358_;
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_Packed10Index_loop(lean_object* v_n_9359_, size_t v_count_9360_, size_t v_baseA_9361_, lean_object* v_A_9362_, lean_object* v_B_9363_, lean_object* v_hn_9364_, lean_object* v_hA_9365_, lean_object* v_hAS_9366_, size_t v_k_9367_, float v_s0_9368_, float v_s1_9369_, float v_s2_9370_, float v_s3_9371_, float v_s4_9372_, float v_s5_9373_, float v_s6_9374_, float v_s7_9375_, float v_s8_9376_, float v_s9_9377_){
_start:
{
lean_object* v___x_9378_; 
v___x_9378_ = lp_competition_Submission_Packed10Index_loop___redArg(v_count_9360_, v_baseA_9361_, v_A_9362_, v_B_9363_, v_k_9367_, v_s0_9368_, v_s1_9369_, v_s2_9370_, v_s3_9371_, v_s4_9372_, v_s5_9373_, v_s6_9374_, v_s7_9375_, v_s8_9376_, v_s9_9377_);
return v___x_9378_;
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_Packed10Index_loop___boxed(lean_object** _args){
lean_object* v_n_9379_ = _args[0];
lean_object* v_count_9380_ = _args[1];
lean_object* v_baseA_9381_ = _args[2];
lean_object* v_A_9382_ = _args[3];
lean_object* v_B_9383_ = _args[4];
lean_object* v_hn_9384_ = _args[5];
lean_object* v_hA_9385_ = _args[6];
lean_object* v_hAS_9386_ = _args[7];
lean_object* v_k_9387_ = _args[8];
lean_object* v_s0_9388_ = _args[9];
lean_object* v_s1_9389_ = _args[10];
lean_object* v_s2_9390_ = _args[11];
lean_object* v_s3_9391_ = _args[12];
lean_object* v_s4_9392_ = _args[13];
lean_object* v_s5_9393_ = _args[14];
lean_object* v_s6_9394_ = _args[15];
lean_object* v_s7_9395_ = _args[16];
lean_object* v_s8_9396_ = _args[17];
lean_object* v_s9_9397_ = _args[18];
_start:
{
size_t v_count_boxed_9398_; size_t v_baseA_boxed_9399_; size_t v_k_boxed_9400_; float v_s0_boxed_9401_; float v_s1_boxed_9402_; float v_s2_boxed_9403_; float v_s3_boxed_9404_; float v_s4_boxed_9405_; float v_s5_boxed_9406_; float v_s6_boxed_9407_; float v_s7_boxed_9408_; float v_s8_boxed_9409_; float v_s9_boxed_9410_; lean_object* v_res_9411_; 
v_count_boxed_9398_ = lean_unbox_usize(v_count_9380_);
lean_dec(v_count_9380_);
v_baseA_boxed_9399_ = lean_unbox_usize(v_baseA_9381_);
lean_dec(v_baseA_9381_);
v_k_boxed_9400_ = lean_unbox_usize(v_k_9387_);
lean_dec(v_k_9387_);
v_s0_boxed_9401_ = lean_unbox_float32(v_s0_9388_);
lean_dec_ref(v_s0_9388_);
v_s1_boxed_9402_ = lean_unbox_float32(v_s1_9389_);
lean_dec_ref(v_s1_9389_);
v_s2_boxed_9403_ = lean_unbox_float32(v_s2_9390_);
lean_dec_ref(v_s2_9390_);
v_s3_boxed_9404_ = lean_unbox_float32(v_s3_9391_);
lean_dec_ref(v_s3_9391_);
v_s4_boxed_9405_ = lean_unbox_float32(v_s4_9392_);
lean_dec_ref(v_s4_9392_);
v_s5_boxed_9406_ = lean_unbox_float32(v_s5_9393_);
lean_dec_ref(v_s5_9393_);
v_s6_boxed_9407_ = lean_unbox_float32(v_s6_9394_);
lean_dec_ref(v_s6_9394_);
v_s7_boxed_9408_ = lean_unbox_float32(v_s7_9395_);
lean_dec_ref(v_s7_9395_);
v_s8_boxed_9409_ = lean_unbox_float32(v_s8_9396_);
lean_dec_ref(v_s8_9396_);
v_s9_boxed_9410_ = lean_unbox_float32(v_s9_9397_);
lean_dec_ref(v_s9_9397_);
v_res_9411_ = lp_competition_Submission_Packed10Index_loop(v_n_9379_, v_count_boxed_9398_, v_baseA_boxed_9399_, v_A_9382_, v_B_9383_, v_hn_9384_, v_hA_9385_, v_hAS_9386_, v_k_boxed_9400_, v_s0_boxed_9401_, v_s1_boxed_9402_, v_s2_boxed_9403_, v_s3_boxed_9404_, v_s4_boxed_9405_, v_s5_boxed_9406_, v_s6_boxed_9407_, v_s7_boxed_9408_, v_s8_boxed_9409_, v_s9_boxed_9410_);
lean_dec_ref(v_B_9383_);
lean_dec_ref(v_A_9382_);
lean_dec(v_n_9379_);
return v_res_9411_;
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_Packed10Index_within___redArg(lean_object* v_n_9412_, lean_object* v_baseA_9413_, lean_object* v_A_9414_, lean_object* v_B_9415_){
_start:
{
size_t v___x_9416_; size_t v___x_9417_; size_t v___x_9418_; float v___x_9419_; lean_object* v___x_9420_; 
v___x_9416_ = lean_usize_of_nat(v_n_9412_);
v___x_9417_ = lean_usize_of_nat(v_baseA_9413_);
v___x_9418_ = ((size_t)0ULL);
v___x_9419_ = lean_float32_once(&lp_competition_Submission_NativeFinal_dot___closed__0, &lp_competition_Submission_NativeFinal_dot___closed__0_once, _init_lp_competition_Submission_NativeFinal_dot___closed__0);
v___x_9420_ = lp_competition_Submission_Packed10Index_loop___redArg(v___x_9416_, v___x_9417_, v_A_9414_, v_B_9415_, v___x_9418_, v___x_9419_, v___x_9419_, v___x_9419_, v___x_9419_, v___x_9419_, v___x_9419_, v___x_9419_, v___x_9419_, v___x_9419_, v___x_9419_);
return v___x_9420_;
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_Packed10Index_within___redArg___boxed(lean_object* v_n_9421_, lean_object* v_baseA_9422_, lean_object* v_A_9423_, lean_object* v_B_9424_){
_start:
{
lean_object* v_res_9425_; 
v_res_9425_ = lp_competition_Submission_Packed10Index_within___redArg(v_n_9421_, v_baseA_9422_, v_A_9423_, v_B_9424_);
lean_dec_ref(v_B_9424_);
lean_dec_ref(v_A_9423_);
lean_dec(v_baseA_9422_);
lean_dec(v_n_9421_);
return v_res_9425_;
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_Packed10Index_within(lean_object* v_n_9426_, lean_object* v_baseA_9427_, lean_object* v_A_9428_, lean_object* v_B_9429_, lean_object* v_hn_9430_, lean_object* v_ha_9431_, lean_object* v_hA_9432_, lean_object* v_hAS_9433_){
_start:
{
size_t v___x_9434_; size_t v___x_9435_; size_t v___x_9436_; float v___x_9437_; lean_object* v___x_9438_; 
v___x_9434_ = lean_usize_of_nat(v_n_9426_);
v___x_9435_ = lean_usize_of_nat(v_baseA_9427_);
v___x_9436_ = ((size_t)0ULL);
v___x_9437_ = lean_float32_once(&lp_competition_Submission_NativeFinal_dot___closed__0, &lp_competition_Submission_NativeFinal_dot___closed__0_once, _init_lp_competition_Submission_NativeFinal_dot___closed__0);
v___x_9438_ = lp_competition_Submission_Packed10Index_loop___redArg(v___x_9434_, v___x_9435_, v_A_9428_, v_B_9429_, v___x_9436_, v___x_9437_, v___x_9437_, v___x_9437_, v___x_9437_, v___x_9437_, v___x_9437_, v___x_9437_, v___x_9437_, v___x_9437_, v___x_9437_);
return v___x_9438_;
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_Packed10Index_within___boxed(lean_object* v_n_9439_, lean_object* v_baseA_9440_, lean_object* v_A_9441_, lean_object* v_B_9442_, lean_object* v_hn_9443_, lean_object* v_ha_9444_, lean_object* v_hA_9445_, lean_object* v_hAS_9446_){
_start:
{
lean_object* v_res_9447_; 
v_res_9447_ = lp_competition_Submission_Packed10Index_within(v_n_9439_, v_baseA_9440_, v_A_9441_, v_B_9442_, v_hn_9443_, v_ha_9444_, v_hA_9445_, v_hAS_9446_);
lean_dec_ref(v_B_9442_);
lean_dec_ref(v_A_9441_);
lean_dec(v_baseA_9440_);
lean_dec(v_n_9439_);
return v_res_9447_;
}
}
static lean_object* _init_lp_competition_Submission_Packed10Index_runDot___closed__0(void){
_start:
{
lean_object* v___x_9448_; lean_object* v___x_9449_; lean_object* v___x_9450_; 
v___x_9448_ = l_System_Platform_numBits;
v___x_9449_ = lean_unsigned_to_nat(2u);
v___x_9450_ = lean_nat_pow(v___x_9449_, v___x_9448_);
return v___x_9450_;
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_Packed10Index_runDot(lean_object* v_n_9451_, lean_object* v_baseA_9452_, lean_object* v_A_9453_, lean_object* v_B_9454_){
_start:
{
lean_object* v___x_9459_; uint8_t v___x_9460_; 
v___x_9459_ = lean_obj_once(&lp_competition_Submission_Packed10Index_runDot___closed__0, &lp_competition_Submission_Packed10Index_runDot___closed__0_once, _init_lp_competition_Submission_Packed10Index_runDot___closed__0);
v___x_9460_ = lean_nat_dec_lt(v_n_9451_, v___x_9459_);
if (v___x_9460_ == 0)
{
goto v___jp_9455_;
}
else
{
uint8_t v___x_9461_; 
v___x_9461_ = lean_nat_dec_lt(v_baseA_9452_, v___x_9459_);
if (v___x_9461_ == 0)
{
goto v___jp_9455_;
}
else
{
lean_object* v___x_9462_; lean_object* v___x_9463_; lean_object* v___x_9464_; lean_object* v___x_9465_; uint8_t v___x_9466_; 
v___x_9462_ = lean_unsigned_to_nat(1u);
v___x_9463_ = lean_nat_sub(v_n_9451_, v___x_9462_);
v___x_9464_ = lean_nat_add(v_baseA_9452_, v___x_9463_);
lean_dec(v___x_9463_);
v___x_9465_ = lean_array_get_size(v_A_9453_);
v___x_9466_ = lean_nat_dec_lt(v___x_9464_, v___x_9465_);
lean_dec(v___x_9464_);
if (v___x_9466_ == 0)
{
goto v___jp_9455_;
}
else
{
uint8_t v___x_9467_; 
v___x_9467_ = lean_nat_dec_lt(v___x_9465_, v___x_9459_);
if (v___x_9467_ == 0)
{
goto v___jp_9455_;
}
else
{
size_t v___x_9468_; size_t v___x_9469_; size_t v___x_9470_; float v___x_9471_; lean_object* v___x_9472_; 
v___x_9468_ = lean_usize_of_nat(v_n_9451_);
v___x_9469_ = lean_usize_of_nat(v_baseA_9452_);
v___x_9470_ = ((size_t)0ULL);
v___x_9471_ = lean_float32_once(&lp_competition_Submission_NativeFinal_dot___closed__0, &lp_competition_Submission_NativeFinal_dot___closed__0_once, _init_lp_competition_Submission_NativeFinal_dot___closed__0);
v___x_9472_ = lp_competition_Submission_Packed10Index_loop___redArg(v___x_9468_, v___x_9469_, v_A_9453_, v_B_9454_, v___x_9470_, v___x_9471_, v___x_9471_, v___x_9471_, v___x_9471_, v___x_9471_, v___x_9471_, v___x_9471_, v___x_9471_, v___x_9471_, v___x_9471_);
return v___x_9472_;
}
}
}
}
v___jp_9455_:
{
lean_object* v___x_9456_; float v___x_9457_; lean_object* v___x_9458_; 
v___x_9456_ = lean_unsigned_to_nat(0u);
v___x_9457_ = lean_float32_once(&lp_competition_Submission_NativeFinal_dot___closed__0, &lp_competition_Submission_NativeFinal_dot___closed__0_once, _init_lp_competition_Submission_NativeFinal_dot___closed__0);
v___x_9458_ = lp_competition_Submission_Packed10_dot10(v_n_9451_, v_baseA_9452_, v_A_9453_, v_B_9454_, v___x_9456_, v___x_9457_, v___x_9457_, v___x_9457_, v___x_9457_, v___x_9457_, v___x_9457_, v___x_9457_, v___x_9457_, v___x_9457_, v___x_9457_);
return v___x_9458_;
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_Packed10Index_runDot___boxed(lean_object* v_n_9473_, lean_object* v_baseA_9474_, lean_object* v_A_9475_, lean_object* v_B_9476_){
_start:
{
lean_object* v_res_9477_; 
v_res_9477_ = lp_competition_Submission_Packed10Index_runDot(v_n_9473_, v_baseA_9474_, v_A_9475_, v_B_9476_);
lean_dec_ref(v_B_9476_);
lean_dec_ref(v_A_9475_);
lean_dec(v_baseA_9474_);
lean_dec(v_n_9473_);
return v_res_9477_;
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_Packed10_tileResults___lam__0(lean_object* v_b_9478_, lean_object* v_m_9479_, lean_object* v_i_9480_, lean_object* v_n_9481_, lean_object* v_B_9482_, lean_object* v_A_9483_, lean_object* v_g_9484_){
_start:
{
lean_object* v___x_9485_; lean_object* v___x_9486_; lean_object* v___x_9487_; lean_object* v___x_9488_; lean_object* v___x_9489_; lean_object* v___x_9494_; uint8_t v___x_9495_; 
v___x_9485_ = lean_nat_mul(v_b_9478_, v_m_9479_);
v___x_9486_ = lean_nat_add(v___x_9485_, v_i_9480_);
lean_dec(v___x_9485_);
v___x_9487_ = lean_nat_mul(v___x_9486_, v_n_9481_);
lean_dec(v___x_9486_);
v___x_9488_ = lean_array_fget_borrowed(v_B_9482_, v_b_9478_);
v___x_9489_ = lean_array_fget_borrowed(v___x_9488_, v_g_9484_);
v___x_9494_ = lean_obj_once(&lp_competition_Submission_Packed10Index_runDot___closed__0, &lp_competition_Submission_Packed10Index_runDot___closed__0_once, _init_lp_competition_Submission_Packed10Index_runDot___closed__0);
v___x_9495_ = lean_nat_dec_lt(v_n_9481_, v___x_9494_);
if (v___x_9495_ == 0)
{
goto v___jp_9490_;
}
else
{
uint8_t v___x_9496_; 
v___x_9496_ = lean_nat_dec_lt(v___x_9487_, v___x_9494_);
if (v___x_9496_ == 0)
{
goto v___jp_9490_;
}
else
{
lean_object* v___x_9497_; lean_object* v___x_9498_; lean_object* v___x_9499_; lean_object* v___x_9500_; uint8_t v___x_9501_; 
v___x_9497_ = lean_unsigned_to_nat(1u);
v___x_9498_ = lean_nat_sub(v_n_9481_, v___x_9497_);
v___x_9499_ = lean_nat_add(v___x_9487_, v___x_9498_);
lean_dec(v___x_9498_);
v___x_9500_ = lean_array_get_size(v_A_9483_);
v___x_9501_ = lean_nat_dec_lt(v___x_9499_, v___x_9500_);
lean_dec(v___x_9499_);
if (v___x_9501_ == 0)
{
goto v___jp_9490_;
}
else
{
uint8_t v___x_9502_; 
v___x_9502_ = lean_nat_dec_lt(v___x_9500_, v___x_9494_);
if (v___x_9502_ == 0)
{
goto v___jp_9490_;
}
else
{
size_t v___x_9503_; size_t v___x_9504_; size_t v___x_9505_; float v___x_9506_; lean_object* v___x_9507_; 
v___x_9503_ = lean_usize_of_nat(v_n_9481_);
v___x_9504_ = lean_usize_of_nat(v___x_9487_);
lean_dec(v___x_9487_);
v___x_9505_ = ((size_t)0ULL);
v___x_9506_ = lean_float32_once(&lp_competition_Submission_NativeFinal_dot___closed__0, &lp_competition_Submission_NativeFinal_dot___closed__0_once, _init_lp_competition_Submission_NativeFinal_dot___closed__0);
v___x_9507_ = lp_competition_Submission_Packed10Index_loop___redArg(v___x_9503_, v___x_9504_, v_A_9483_, v___x_9489_, v___x_9505_, v___x_9506_, v___x_9506_, v___x_9506_, v___x_9506_, v___x_9506_, v___x_9506_, v___x_9506_, v___x_9506_, v___x_9506_, v___x_9506_);
return v___x_9507_;
}
}
}
}
v___jp_9490_:
{
lean_object* v___x_9491_; float v___x_9492_; lean_object* v___x_9493_; 
v___x_9491_ = lean_unsigned_to_nat(0u);
v___x_9492_ = lean_float32_once(&lp_competition_Submission_NativeFinal_dot___closed__0, &lp_competition_Submission_NativeFinal_dot___closed__0_once, _init_lp_competition_Submission_NativeFinal_dot___closed__0);
v___x_9493_ = lp_competition_Submission_Packed10_dot10(v_n_9481_, v___x_9487_, v_A_9483_, v___x_9489_, v___x_9491_, v___x_9492_, v___x_9492_, v___x_9492_, v___x_9492_, v___x_9492_, v___x_9492_, v___x_9492_, v___x_9492_, v___x_9492_, v___x_9492_);
lean_dec(v___x_9487_);
return v___x_9493_;
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_Packed10_tileResults___lam__0___boxed(lean_object* v_b_9508_, lean_object* v_m_9509_, lean_object* v_i_9510_, lean_object* v_n_9511_, lean_object* v_B_9512_, lean_object* v_A_9513_, lean_object* v_g_9514_){
_start:
{
lean_object* v_res_9515_; 
v_res_9515_ = lp_competition_Submission_Packed10_tileResults___lam__0(v_b_9508_, v_m_9509_, v_i_9510_, v_n_9511_, v_B_9512_, v_A_9513_, v_g_9514_);
lean_dec(v_g_9514_);
lean_dec_ref(v_A_9513_);
lean_dec_ref(v_B_9512_);
lean_dec(v_n_9511_);
lean_dec(v_i_9510_);
lean_dec(v_m_9509_);
lean_dec(v_b_9508_);
return v_res_9515_;
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_Packed10_tileResults___lam__1(lean_object* v_b_9516_, lean_object* v_m_9517_, lean_object* v_n_9518_, lean_object* v_B_9519_, lean_object* v_A_9520_, lean_object* v_p_9521_, lean_object* v_i_9522_){
_start:
{
lean_object* v___f_9523_; lean_object* v___x_9524_; lean_object* v___x_9525_; lean_object* v___x_9526_; lean_object* v___x_9527_; lean_object* v___x_9528_; 
v___f_9523_ = lean_alloc_closure((void*)(lp_competition_Submission_Packed10_tileResults___lam__0___boxed), 7, 6);
lean_closure_set(v___f_9523_, 0, v_b_9516_);
lean_closure_set(v___f_9523_, 1, v_m_9517_);
lean_closure_set(v___f_9523_, 2, v_i_9522_);
lean_closure_set(v___f_9523_, 3, v_n_9518_);
lean_closure_set(v___f_9523_, 4, v_B_9519_);
lean_closure_set(v___f_9523_, 5, v_A_9520_);
v___x_9524_ = lean_unsigned_to_nat(9u);
v___x_9525_ = lean_nat_add(v_p_9521_, v___x_9524_);
v___x_9526_ = lean_unsigned_to_nat(10u);
v___x_9527_ = lean_nat_div(v___x_9525_, v___x_9526_);
lean_dec(v___x_9525_);
v___x_9528_ = l_Array_ofFn___redArg(v___x_9527_, v___f_9523_);
return v___x_9528_;
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_Packed10_tileResults___lam__1___boxed(lean_object* v_b_9529_, lean_object* v_m_9530_, lean_object* v_n_9531_, lean_object* v_B_9532_, lean_object* v_A_9533_, lean_object* v_p_9534_, lean_object* v_i_9535_){
_start:
{
lean_object* v_res_9536_; 
v_res_9536_ = lp_competition_Submission_Packed10_tileResults___lam__1(v_b_9529_, v_m_9530_, v_n_9531_, v_B_9532_, v_A_9533_, v_p_9534_, v_i_9535_);
lean_dec(v_p_9534_);
return v_res_9536_;
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_Packed10_tileResults___lam__2(lean_object* v_m_9537_, lean_object* v_n_9538_, lean_object* v_B_9539_, lean_object* v_A_9540_, lean_object* v_p_9541_, lean_object* v_b_9542_){
_start:
{
lean_object* v___f_9543_; lean_object* v___x_9544_; 
lean_inc(v_m_9537_);
v___f_9543_ = lean_alloc_closure((void*)(lp_competition_Submission_Packed10_tileResults___lam__1___boxed), 7, 6);
lean_closure_set(v___f_9543_, 0, v_b_9542_);
lean_closure_set(v___f_9543_, 1, v_m_9537_);
lean_closure_set(v___f_9543_, 2, v_n_9538_);
lean_closure_set(v___f_9543_, 3, v_B_9539_);
lean_closure_set(v___f_9543_, 4, v_A_9540_);
lean_closure_set(v___f_9543_, 5, v_p_9541_);
v___x_9544_ = l_Array_ofFn___redArg(v_m_9537_, v___f_9543_);
return v___x_9544_;
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_Packed10_tileResults(lean_object* v_batch_9545_, lean_object* v_m_9546_, lean_object* v_n_9547_, lean_object* v_p_9548_, lean_object* v_A_9549_, lean_object* v_B_9550_){
_start:
{
lean_object* v___f_9551_; lean_object* v___x_9552_; 
v___f_9551_ = lean_alloc_closure((void*)(lp_competition_Submission_Packed10_tileResults___lam__2), 6, 5);
lean_closure_set(v___f_9551_, 0, v_m_9546_);
lean_closure_set(v___f_9551_, 1, v_n_9547_);
lean_closure_set(v___f_9551_, 2, v_B_9550_);
lean_closure_set(v___f_9551_, 3, v_A_9549_);
lean_closure_set(v___f_9551_, 4, v_p_9548_);
v___x_9552_ = l_Array_ofFn___redArg(v_batch_9545_, v___f_9551_);
return v___x_9552_;
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_Packed10_inlineDecodeC(lean_object* v_m_9553_, lean_object* v_p_9554_, lean_object* v_q_9555_){
_start:
{
lean_object* v___y_9557_; lean_object* v___y_9558_; lean_object* v___y_9559_; lean_object* v_rowSize_9562_; lean_object* v___x_9563_; uint8_t v___x_9564_; uint8_t v___x_9565_; lean_object* v___y_9567_; lean_object* v___y_9568_; lean_object* v___y_9569_; lean_object* v___y_9572_; lean_object* v___y_9573_; lean_object* v___y_9576_; 
v_rowSize_9562_ = lean_nat_mul(v_m_9553_, v_p_9554_);
v___x_9563_ = lean_unsigned_to_nat(0u);
v___x_9564_ = lean_nat_dec_eq(v_rowSize_9562_, v___x_9563_);
v___x_9565_ = lean_nat_dec_eq(v_p_9554_, v___x_9563_);
if (v___x_9564_ == 0)
{
lean_object* v___x_9578_; 
v___x_9578_ = lean_nat_div(v_q_9555_, v_rowSize_9562_);
v___y_9576_ = v___x_9578_;
goto v___jp_9575_;
}
else
{
v___y_9576_ = v___x_9563_;
goto v___jp_9575_;
}
v___jp_9556_:
{
lean_object* v___x_9560_; lean_object* v___x_9561_; 
v___x_9560_ = lean_alloc_ctor(0, 2, 0);
lean_ctor_set(v___x_9560_, 0, v___y_9558_);
lean_ctor_set(v___x_9560_, 1, v___y_9559_);
v___x_9561_ = lean_alloc_ctor(0, 2, 0);
lean_ctor_set(v___x_9561_, 0, v___y_9557_);
lean_ctor_set(v___x_9561_, 1, v___x_9560_);
return v___x_9561_;
}
v___jp_9566_:
{
if (v___x_9565_ == 0)
{
lean_object* v___x_9570_; 
v___x_9570_ = lean_nat_mod(v___y_9568_, v_p_9554_);
lean_dec(v___y_9568_);
v___y_9557_ = v___y_9567_;
v___y_9558_ = v___y_9569_;
v___y_9559_ = v___x_9570_;
goto v___jp_9556_;
}
else
{
lean_dec(v___y_9568_);
v___y_9557_ = v___y_9567_;
v___y_9558_ = v___y_9569_;
v___y_9559_ = v___x_9563_;
goto v___jp_9556_;
}
}
v___jp_9571_:
{
if (v___x_9565_ == 0)
{
lean_object* v___x_9574_; 
v___x_9574_ = lean_nat_div(v___y_9573_, v_p_9554_);
v___y_9567_ = v___y_9572_;
v___y_9568_ = v___y_9573_;
v___y_9569_ = v___x_9574_;
goto v___jp_9566_;
}
else
{
v___y_9567_ = v___y_9572_;
v___y_9568_ = v___y_9573_;
v___y_9569_ = v___x_9563_;
goto v___jp_9566_;
}
}
v___jp_9575_:
{
if (v___x_9564_ == 0)
{
lean_object* v___x_9577_; 
v___x_9577_ = lean_nat_mod(v_q_9555_, v_rowSize_9562_);
lean_dec(v_rowSize_9562_);
v___y_9572_ = v___y_9576_;
v___y_9573_ = v___x_9577_;
goto v___jp_9571_;
}
else
{
lean_dec(v_rowSize_9562_);
v___y_9572_ = v___y_9576_;
v___y_9573_ = v___x_9563_;
goto v___jp_9571_;
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_Packed10_inlineDecodeC___boxed(lean_object* v_m_9579_, lean_object* v_p_9580_, lean_object* v_q_9581_){
_start:
{
lean_object* v_res_9582_; 
v_res_9582_ = lp_competition_Submission_Packed10_inlineDecodeC(v_m_9579_, v_p_9580_, v_q_9581_);
lean_dec(v_q_9581_);
lean_dec(v_p_9580_);
lean_dec(v_m_9579_);
return v_res_9582_;
}
}
LEAN_EXPORT uint32_t lp_competition_Submission_Packed10_outputFromTiles___redArg(lean_object* v_m_9583_, lean_object* v_n_9584_, lean_object* v_p_9585_, lean_object* v_A_9586_, lean_object* v_B_9587_, lean_object* v_tiles_9588_, lean_object* v_q_9589_){
_start:
{
lean_object* v_rowSize_9590_; lean_object* v___x_9591_; lean_object* v___y_9593_; lean_object* v___y_9594_; lean_object* v___y_9595_; uint8_t v___x_9645_; uint8_t v___x_9646_; lean_object* v___y_9648_; lean_object* v___y_9649_; lean_object* v___y_9650_; lean_object* v___y_9653_; lean_object* v___y_9654_; lean_object* v___y_9657_; 
v_rowSize_9590_ = lean_nat_mul(v_m_9583_, v_p_9585_);
v___x_9591_ = lean_unsigned_to_nat(0u);
v___x_9645_ = lean_nat_dec_eq(v_rowSize_9590_, v___x_9591_);
v___x_9646_ = lean_nat_dec_eq(v_p_9585_, v___x_9591_);
if (v___x_9645_ == 0)
{
lean_object* v___x_9659_; 
v___x_9659_ = lean_nat_div(v_q_9589_, v_rowSize_9590_);
v___y_9657_ = v___x_9659_;
goto v___jp_9656_;
}
else
{
v___y_9657_ = v___x_9591_;
goto v___jp_9656_;
}
v___jp_9592_:
{
lean_object* v___x_9596_; lean_object* v___x_9597_; lean_object* v___x_9598_; lean_object* v___x_9599_; lean_object* v___x_9600_; lean_object* v___x_9601_; lean_object* v___x_9602_; lean_object* v___x_9603_; lean_object* v___x_9604_; lean_object* v___x_9605_; lean_object* v___x_9606_; lean_object* v___x_9607_; uint8_t v___x_9608_; 
v___x_9596_ = lean_unsigned_to_nat(10u);
v___x_9597_ = lean_nat_div(v___y_9595_, v___x_9596_);
v___x_9598_ = lean_nat_mod(v___y_9595_, v___x_9596_);
v___x_9599_ = lean_nat_mul(v___y_9594_, v_m_9583_);
v___x_9600_ = lean_nat_add(v___x_9599_, v___y_9593_);
lean_dec(v___x_9599_);
v___x_9601_ = lean_nat_mul(v___x_9600_, v_n_9584_);
lean_dec(v___x_9600_);
v___x_9602_ = lean_nat_mul(v___y_9594_, v_n_9584_);
v___x_9603_ = lean_nat_mul(v___x_9602_, v_p_9585_);
lean_dec(v___x_9602_);
v___x_9604_ = lean_nat_add(v___x_9603_, v___y_9595_);
lean_dec(v___y_9595_);
lean_dec(v___x_9603_);
v___x_9605_ = lean_array_fget_borrowed(v_tiles_9588_, v___y_9594_);
lean_dec(v___y_9594_);
v___x_9606_ = lean_array_fget_borrowed(v___x_9605_, v___y_9593_);
lean_dec(v___y_9593_);
v___x_9607_ = lean_array_fget_borrowed(v___x_9606_, v___x_9597_);
lean_dec(v___x_9597_);
v___x_9608_ = lean_nat_dec_eq(v___x_9598_, v___x_9591_);
if (v___x_9608_ == 0)
{
lean_object* v___x_9609_; uint8_t v___x_9610_; 
v___x_9609_ = lean_unsigned_to_nat(1u);
v___x_9610_ = lean_nat_dec_eq(v___x_9598_, v___x_9609_);
if (v___x_9610_ == 0)
{
lean_object* v___x_9611_; uint8_t v___x_9612_; 
v___x_9611_ = lean_unsigned_to_nat(2u);
v___x_9612_ = lean_nat_dec_eq(v___x_9598_, v___x_9611_);
if (v___x_9612_ == 0)
{
lean_object* v___x_9613_; uint8_t v___x_9614_; 
v___x_9613_ = lean_unsigned_to_nat(3u);
v___x_9614_ = lean_nat_dec_eq(v___x_9598_, v___x_9613_);
if (v___x_9614_ == 0)
{
lean_object* v___x_9615_; uint8_t v___x_9616_; 
v___x_9615_ = lean_unsigned_to_nat(4u);
v___x_9616_ = lean_nat_dec_eq(v___x_9598_, v___x_9615_);
if (v___x_9616_ == 0)
{
lean_object* v___x_9617_; uint8_t v___x_9618_; 
v___x_9617_ = lean_unsigned_to_nat(5u);
v___x_9618_ = lean_nat_dec_eq(v___x_9598_, v___x_9617_);
if (v___x_9618_ == 0)
{
lean_object* v___x_9619_; uint8_t v___x_9620_; 
v___x_9619_ = lean_unsigned_to_nat(6u);
v___x_9620_ = lean_nat_dec_eq(v___x_9598_, v___x_9619_);
if (v___x_9620_ == 0)
{
lean_object* v___x_9621_; uint8_t v___x_9622_; 
v___x_9621_ = lean_unsigned_to_nat(7u);
v___x_9622_ = lean_nat_dec_eq(v___x_9598_, v___x_9621_);
if (v___x_9622_ == 0)
{
lean_object* v___x_9623_; uint8_t v___x_9624_; 
v___x_9623_ = lean_unsigned_to_nat(8u);
v___x_9624_ = lean_nat_dec_eq(v___x_9598_, v___x_9623_);
lean_dec(v___x_9598_);
if (v___x_9624_ == 0)
{
float v_s9_9625_; uint32_t v___x_9626_; 
v_s9_9625_ = lean_ctor_get_float32(v___x_9607_, 36);
v___x_9626_ = lp_competition_Submission_Packed10_finish(v_n_9584_, v___x_9601_, v___x_9604_, v_p_9585_, v_A_9586_, v_B_9587_, v_s9_9625_);
lean_dec(v___x_9604_);
lean_dec(v___x_9601_);
return v___x_9626_;
}
else
{
float v_s8_9627_; uint32_t v___x_9628_; 
v_s8_9627_ = lean_ctor_get_float32(v___x_9607_, 32);
v___x_9628_ = lp_competition_Submission_Packed10_finish(v_n_9584_, v___x_9601_, v___x_9604_, v_p_9585_, v_A_9586_, v_B_9587_, v_s8_9627_);
lean_dec(v___x_9604_);
lean_dec(v___x_9601_);
return v___x_9628_;
}
}
else
{
float v_s7_9629_; uint32_t v___x_9630_; 
lean_dec(v___x_9598_);
v_s7_9629_ = lean_ctor_get_float32(v___x_9607_, 28);
v___x_9630_ = lp_competition_Submission_Packed10_finish(v_n_9584_, v___x_9601_, v___x_9604_, v_p_9585_, v_A_9586_, v_B_9587_, v_s7_9629_);
lean_dec(v___x_9604_);
lean_dec(v___x_9601_);
return v___x_9630_;
}
}
else
{
float v_s6_9631_; uint32_t v___x_9632_; 
lean_dec(v___x_9598_);
v_s6_9631_ = lean_ctor_get_float32(v___x_9607_, 24);
v___x_9632_ = lp_competition_Submission_Packed10_finish(v_n_9584_, v___x_9601_, v___x_9604_, v_p_9585_, v_A_9586_, v_B_9587_, v_s6_9631_);
lean_dec(v___x_9604_);
lean_dec(v___x_9601_);
return v___x_9632_;
}
}
else
{
float v_s5_9633_; uint32_t v___x_9634_; 
lean_dec(v___x_9598_);
v_s5_9633_ = lean_ctor_get_float32(v___x_9607_, 20);
v___x_9634_ = lp_competition_Submission_Packed10_finish(v_n_9584_, v___x_9601_, v___x_9604_, v_p_9585_, v_A_9586_, v_B_9587_, v_s5_9633_);
lean_dec(v___x_9604_);
lean_dec(v___x_9601_);
return v___x_9634_;
}
}
else
{
float v_s4_9635_; uint32_t v___x_9636_; 
lean_dec(v___x_9598_);
v_s4_9635_ = lean_ctor_get_float32(v___x_9607_, 16);
v___x_9636_ = lp_competition_Submission_Packed10_finish(v_n_9584_, v___x_9601_, v___x_9604_, v_p_9585_, v_A_9586_, v_B_9587_, v_s4_9635_);
lean_dec(v___x_9604_);
lean_dec(v___x_9601_);
return v___x_9636_;
}
}
else
{
float v_s3_9637_; uint32_t v___x_9638_; 
lean_dec(v___x_9598_);
v_s3_9637_ = lean_ctor_get_float32(v___x_9607_, 12);
v___x_9638_ = lp_competition_Submission_Packed10_finish(v_n_9584_, v___x_9601_, v___x_9604_, v_p_9585_, v_A_9586_, v_B_9587_, v_s3_9637_);
lean_dec(v___x_9604_);
lean_dec(v___x_9601_);
return v___x_9638_;
}
}
else
{
float v_s2_9639_; uint32_t v___x_9640_; 
lean_dec(v___x_9598_);
v_s2_9639_ = lean_ctor_get_float32(v___x_9607_, 8);
v___x_9640_ = lp_competition_Submission_Packed10_finish(v_n_9584_, v___x_9601_, v___x_9604_, v_p_9585_, v_A_9586_, v_B_9587_, v_s2_9639_);
lean_dec(v___x_9604_);
lean_dec(v___x_9601_);
return v___x_9640_;
}
}
else
{
float v_s1_9641_; uint32_t v___x_9642_; 
lean_dec(v___x_9598_);
v_s1_9641_ = lean_ctor_get_float32(v___x_9607_, 4);
v___x_9642_ = lp_competition_Submission_Packed10_finish(v_n_9584_, v___x_9601_, v___x_9604_, v_p_9585_, v_A_9586_, v_B_9587_, v_s1_9641_);
lean_dec(v___x_9604_);
lean_dec(v___x_9601_);
return v___x_9642_;
}
}
else
{
float v_s0_9643_; uint32_t v___x_9644_; 
lean_dec(v___x_9598_);
v_s0_9643_ = lean_ctor_get_float32(v___x_9607_, 0);
v___x_9644_ = lp_competition_Submission_Packed10_finish(v_n_9584_, v___x_9601_, v___x_9604_, v_p_9585_, v_A_9586_, v_B_9587_, v_s0_9643_);
lean_dec(v___x_9604_);
lean_dec(v___x_9601_);
return v___x_9644_;
}
}
v___jp_9647_:
{
if (v___x_9646_ == 0)
{
lean_object* v___x_9651_; 
v___x_9651_ = lean_nat_mod(v___y_9649_, v_p_9585_);
lean_dec(v___y_9649_);
v___y_9593_ = v___y_9650_;
v___y_9594_ = v___y_9648_;
v___y_9595_ = v___x_9651_;
goto v___jp_9592_;
}
else
{
lean_dec(v___y_9649_);
v___y_9593_ = v___y_9650_;
v___y_9594_ = v___y_9648_;
v___y_9595_ = v___x_9591_;
goto v___jp_9592_;
}
}
v___jp_9652_:
{
if (v___x_9646_ == 0)
{
lean_object* v___x_9655_; 
v___x_9655_ = lean_nat_div(v___y_9654_, v_p_9585_);
v___y_9648_ = v___y_9653_;
v___y_9649_ = v___y_9654_;
v___y_9650_ = v___x_9655_;
goto v___jp_9647_;
}
else
{
v___y_9648_ = v___y_9653_;
v___y_9649_ = v___y_9654_;
v___y_9650_ = v___x_9591_;
goto v___jp_9647_;
}
}
v___jp_9656_:
{
if (v___x_9645_ == 0)
{
lean_object* v___x_9658_; 
v___x_9658_ = lean_nat_mod(v_q_9589_, v_rowSize_9590_);
lean_dec(v_rowSize_9590_);
v___y_9653_ = v___y_9657_;
v___y_9654_ = v___x_9658_;
goto v___jp_9652_;
}
else
{
lean_dec(v_rowSize_9590_);
v___y_9653_ = v___y_9657_;
v___y_9654_ = v___x_9591_;
goto v___jp_9652_;
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_Packed10_outputFromTiles___redArg___boxed(lean_object* v_m_9660_, lean_object* v_n_9661_, lean_object* v_p_9662_, lean_object* v_A_9663_, lean_object* v_B_9664_, lean_object* v_tiles_9665_, lean_object* v_q_9666_){
_start:
{
uint32_t v_res_9667_; lean_object* v_r_9668_; 
v_res_9667_ = lp_competition_Submission_Packed10_outputFromTiles___redArg(v_m_9660_, v_n_9661_, v_p_9662_, v_A_9663_, v_B_9664_, v_tiles_9665_, v_q_9666_);
lean_dec(v_q_9666_);
lean_dec_ref(v_tiles_9665_);
lean_dec_ref(v_B_9664_);
lean_dec_ref(v_A_9663_);
lean_dec(v_p_9662_);
lean_dec(v_n_9661_);
lean_dec(v_m_9660_);
v_r_9668_ = lean_box_uint32(v_res_9667_);
return v_r_9668_;
}
}
LEAN_EXPORT uint32_t lp_competition_Submission_Packed10_outputFromTiles(lean_object* v_batch_9669_, lean_object* v_m_9670_, lean_object* v_n_9671_, lean_object* v_p_9672_, lean_object* v_A_9673_, lean_object* v_B_9674_, lean_object* v_tiles_9675_, lean_object* v_q_9676_){
_start:
{
uint32_t v___x_9677_; 
v___x_9677_ = lp_competition_Submission_Packed10_outputFromTiles___redArg(v_m_9670_, v_n_9671_, v_p_9672_, v_A_9673_, v_B_9674_, v_tiles_9675_, v_q_9676_);
return v___x_9677_;
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_Packed10_outputFromTiles___boxed(lean_object* v_batch_9678_, lean_object* v_m_9679_, lean_object* v_n_9680_, lean_object* v_p_9681_, lean_object* v_A_9682_, lean_object* v_B_9683_, lean_object* v_tiles_9684_, lean_object* v_q_9685_){
_start:
{
uint32_t v_res_9686_; lean_object* v_r_9687_; 
v_res_9686_ = lp_competition_Submission_Packed10_outputFromTiles(v_batch_9678_, v_m_9679_, v_n_9680_, v_p_9681_, v_A_9682_, v_B_9683_, v_tiles_9684_, v_q_9685_);
lean_dec(v_q_9685_);
lean_dec_ref(v_tiles_9684_);
lean_dec_ref(v_B_9683_);
lean_dec_ref(v_A_9682_);
lean_dec(v_p_9681_);
lean_dec(v_n_9680_);
lean_dec(v_m_9679_);
lean_dec(v_batch_9678_);
v_r_9687_ = lean_box_uint32(v_res_9686_);
return v_r_9687_;
}
}
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_mapMUnsafe_map___at___00Submission_Packed10_core_spec__0(size_t v_sz_9688_, size_t v_i_9689_, lean_object* v_bs_9690_){
_start:
{
uint8_t v___x_9691_; 
v___x_9691_ = lean_usize_dec_lt(v_i_9689_, v_sz_9688_);
if (v___x_9691_ == 0)
{
return v_bs_9690_;
}
else
{
lean_object* v_v_9692_; lean_object* v___x_9693_; lean_object* v_bs_x27_9694_; uint32_t v___x_9695_; float v___x_9696_; size_t v___x_9697_; size_t v___x_9698_; lean_object* v___x_9699_; lean_object* v___x_9700_; 
v_v_9692_ = lean_array_uget(v_bs_9690_, v_i_9689_);
v___x_9693_ = lean_unsigned_to_nat(0u);
v_bs_x27_9694_ = lean_array_uset(v_bs_9690_, v_i_9689_, v___x_9693_);
v___x_9695_ = lean_unbox_uint32(v_v_9692_);
lean_dec(v_v_9692_);
v___x_9696_ = lean_float32_of_bits(v___x_9695_);
v___x_9697_ = ((size_t)1ULL);
v___x_9698_ = lean_usize_add(v_i_9689_, v___x_9697_);
v___x_9699_ = lean_box_float32(v___x_9696_);
v___x_9700_ = lean_array_uset(v_bs_x27_9694_, v_i_9689_, v___x_9699_);
v_i_9689_ = v___x_9698_;
v_bs_9690_ = v___x_9700_;
goto _start;
}
}
}
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_mapMUnsafe_map___at___00Submission_Packed10_core_spec__0___boxed(lean_object* v_sz_9702_, lean_object* v_i_9703_, lean_object* v_bs_9704_){
_start:
{
size_t v_sz_boxed_9705_; size_t v_i_boxed_9706_; lean_object* v_res_9707_; 
v_sz_boxed_9705_ = lean_unbox_usize(v_sz_9702_);
lean_dec(v_sz_9702_);
v_i_boxed_9706_ = lean_unbox_usize(v_i_9703_);
lean_dec(v_i_9703_);
v_res_9707_ = lp_competition___private_Init_Data_Array_Basic_0__Array_mapMUnsafe_map___at___00Submission_Packed10_core_spec__0(v_sz_boxed_9705_, v_i_boxed_9706_, v_bs_9704_);
return v_res_9707_;
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_Packed10_core(lean_object* v_batch_9708_, lean_object* v_m_9709_, lean_object* v_n_9710_, lean_object* v_p_9711_, lean_object* v_A_9712_, lean_object* v_B_9713_){
_start:
{
size_t v_sz_9714_; size_t v___x_9715_; lean_object* v_nativeA_9716_; lean_object* v_packedB_9717_; lean_object* v_tiles_9718_; lean_object* v___x_9719_; lean_object* v___x_9720_; lean_object* v___x_9721_; lean_object* v___x_9722_; 
v_sz_9714_ = lean_array_size(v_A_9712_);
v___x_9715_ = ((size_t)0ULL);
lean_inc_ref(v_A_9712_);
v_nativeA_9716_ = lp_competition___private_Init_Data_Array_Basic_0__Array_mapMUnsafe_map___at___00Submission_Packed10_core_spec__0(v_sz_9714_, v___x_9715_, v_A_9712_);
lean_inc_ref(v_B_9713_);
lean_inc_n(v_p_9711_, 2);
lean_inc_n(v_n_9710_, 2);
lean_inc_n(v_batch_9708_, 2);
v_packedB_9717_ = lp_competition_Submission_Packed10_packB(v_batch_9708_, v_n_9710_, v_p_9711_, v_B_9713_);
lean_inc(v_m_9709_);
v_tiles_9718_ = lp_competition_Submission_Packed10_tileResults(v_batch_9708_, v_m_9709_, v_n_9710_, v_p_9711_, v_nativeA_9716_, v_packedB_9717_);
v___x_9719_ = lean_nat_mul(v_batch_9708_, v_m_9709_);
v___x_9720_ = lean_nat_mul(v___x_9719_, v_p_9711_);
lean_dec(v___x_9719_);
v___x_9721_ = lean_alloc_closure((void*)(lp_competition_Submission_Packed10_outputFromTiles___boxed), 8, 7);
lean_closure_set(v___x_9721_, 0, v_batch_9708_);
lean_closure_set(v___x_9721_, 1, v_m_9709_);
lean_closure_set(v___x_9721_, 2, v_n_9710_);
lean_closure_set(v___x_9721_, 3, v_p_9711_);
lean_closure_set(v___x_9721_, 4, v_A_9712_);
lean_closure_set(v___x_9721_, 5, v_B_9713_);
lean_closure_set(v___x_9721_, 6, v_tiles_9718_);
v___x_9722_ = l_Array_ofFn___redArg(v___x_9720_, v___x_9721_);
return v___x_9722_;
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_bmmR4(lean_object* v_batch_9723_, lean_object* v_m_9724_, lean_object* v_n_9725_, lean_object* v_p_9726_, lean_object* v_A_9727_, lean_object* v_B_9728_){
_start:
{
lean_object* v___x_9729_; lean_object* v___x_9730_; lean_object* v___x_9731_; uint8_t v___x_9732_; 
v___x_9729_ = lean_nat_mul(v_batch_9723_, v_m_9724_);
v___x_9730_ = lean_nat_mul(v___x_9729_, v_p_9726_);
lean_dec(v___x_9729_);
v___x_9731_ = lean_unsigned_to_nat(0u);
v___x_9732_ = lean_nat_dec_eq(v___x_9730_, v___x_9731_);
lean_dec(v___x_9730_);
if (v___x_9732_ == 0)
{
uint8_t v___x_9733_; 
v___x_9733_ = lean_nat_dec_eq(v_n_9725_, v___x_9731_);
if (v___x_9733_ == 0)
{
lean_object* v___x_9734_; 
v___x_9734_ = lp_competition_Submission_Packed10_core(v_batch_9723_, v_m_9724_, v_n_9725_, v_p_9726_, v_A_9727_, v_B_9728_);
return v___x_9734_;
}
else
{
lean_object* v___x_9735_; 
v___x_9735_ = lp_competition_Submission_referenceBmm(v_batch_9723_, v_m_9724_, v_n_9725_, v_p_9726_, v_A_9727_, v_B_9728_);
lean_dec(v_batch_9723_);
return v___x_9735_;
}
}
else
{
lean_object* v___x_9736_; 
v___x_9736_ = lp_competition_Submission_referenceBmm(v_batch_9723_, v_m_9724_, v_n_9725_, v_p_9726_, v_A_9727_, v_B_9728_);
lean_dec(v_batch_9723_);
return v___x_9736_;
}
}
}
LEAN_EXPORT float lp_competition_Submission_NativeDecodeSum_decode(uint32_t v_x_9737_){
_start:
{
uint8_t v___y_9739_; uint32_t v___x_9753_; uint32_t v_a_9754_; uint32_t v___x_9755_; uint32_t v___x_9756_; uint32_t v___x_9757_; uint8_t v___x_9758_; 
v___x_9753_ = 2147483647;
v_a_9754_ = lean_uint32_land(v_x_9737_, v___x_9753_);
v___x_9755_ = 201326591;
v___x_9756_ = 1;
v___x_9757_ = lean_uint32_sub(v_a_9754_, v___x_9756_);
v___x_9758_ = lean_uint32_dec_le(v___x_9755_, v___x_9757_);
if (v___x_9758_ == 0)
{
v___y_9739_ = v___x_9758_;
goto v___jp_9738_;
}
else
{
uint32_t v___x_9759_; uint8_t v___x_9760_; 
v___x_9759_ = 2139095040;
v___x_9760_ = lean_uint32_dec_lt(v_a_9754_, v___x_9759_);
v___y_9739_ = v___x_9760_;
goto v___jp_9738_;
}
v___jp_9738_:
{
if (v___y_9739_ == 0)
{
float v___x_9740_; 
v___x_9740_ = lean_float32_of_bits(v_x_9737_);
return v___x_9740_;
}
else
{
uint32_t v___x_9741_; uint32_t v___x_9742_; uint32_t v___x_9743_; uint32_t v___x_9744_; float v___x_9745_; lean_object* v___x_9746_; uint32_t v___x_9747_; uint32_t v___x_9748_; lean_object* v___x_9749_; lean_object* v___x_9750_; float v___x_9751_; float v___x_9752_; 
v___x_9741_ = 8388607;
v___x_9742_ = lean_uint32_land(v_x_9737_, v___x_9741_);
v___x_9743_ = 8388608;
v___x_9744_ = lean_uint32_lor(v___x_9742_, v___x_9743_);
v___x_9745_ = lean_uint32_to_float32(v___x_9744_);
v___x_9746_ = lp_competition_R2W01b_scaleTable;
v___x_9747_ = 23;
v___x_9748_ = lean_uint32_shift_right(v_x_9737_, v___x_9747_);
v___x_9749_ = lean_uint32_to_nat(v___x_9748_);
v___x_9750_ = lean_array_fget_borrowed(v___x_9746_, v___x_9749_);
lean_dec(v___x_9749_);
v___x_9751_ = lean_unbox_float32(v___x_9750_);
v___x_9752_ = lean_float32_mul(v___x_9745_, v___x_9751_);
return v___x_9752_;
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_NativeDecodeSum_decode___boxed(lean_object* v_x_9761_){
_start:
{
uint32_t v_x_boxed_9762_; float v_res_9763_; lean_object* v_r_9764_; 
v_x_boxed_9762_ = lean_unbox_uint32(v_x_9761_);
lean_dec(v_x_9761_);
v_res_9763_ = lp_competition_Submission_NativeDecodeSum_decode(v_x_boxed_9762_);
v_r_9764_ = lean_box_float32(v_res_9763_);
return v_r_9764_;
}
}
LEAN_EXPORT float lp_competition_Submission_NativeDecodeSum_loop(lean_object* v_n_9765_, lean_object* v_x_9766_, lean_object* v_k_9767_, float v_acc_9768_){
_start:
{
uint8_t v___x_9769_; 
v___x_9769_ = lean_nat_dec_lt(v_k_9767_, v_n_9765_);
if (v___x_9769_ == 0)
{
lean_dec(v_k_9767_);
return v_acc_9768_;
}
else
{
lean_object* v___x_9770_; lean_object* v___x_9771_; float v___y_9773_; lean_object* v___x_9776_; uint8_t v___y_9778_; uint32_t v___x_9795_; uint32_t v___x_9796_; uint32_t v_a_9797_; uint32_t v___x_9798_; uint32_t v___x_9799_; uint32_t v___x_9800_; uint8_t v___x_9801_; 
v___x_9770_ = lean_unsigned_to_nat(1u);
v___x_9771_ = lean_nat_add(v_k_9767_, v___x_9770_);
v___x_9776_ = lean_array_fget_borrowed(v_x_9766_, v_k_9767_);
lean_dec(v_k_9767_);
v___x_9795_ = 2147483647;
v___x_9796_ = lean_unbox_uint32(v___x_9776_);
v_a_9797_ = lean_uint32_land(v___x_9796_, v___x_9795_);
v___x_9798_ = 201326591;
v___x_9799_ = 1;
v___x_9800_ = lean_uint32_sub(v_a_9797_, v___x_9799_);
v___x_9801_ = lean_uint32_dec_le(v___x_9798_, v___x_9800_);
if (v___x_9801_ == 0)
{
v___y_9778_ = v___x_9801_;
goto v___jp_9777_;
}
else
{
uint32_t v___x_9802_; uint8_t v___x_9803_; 
v___x_9802_ = 2139095040;
v___x_9803_ = lean_uint32_dec_lt(v_a_9797_, v___x_9802_);
v___y_9778_ = v___x_9803_;
goto v___jp_9777_;
}
v___jp_9772_:
{
float v___x_9774_; 
v___x_9774_ = lean_float32_add(v_acc_9768_, v___y_9773_);
v_k_9767_ = v___x_9771_;
v_acc_9768_ = v___x_9774_;
goto _start;
}
v___jp_9777_:
{
if (v___y_9778_ == 0)
{
uint32_t v___x_9779_; float v___x_9780_; 
v___x_9779_ = lean_unbox_uint32(v___x_9776_);
v___x_9780_ = lean_float32_of_bits(v___x_9779_);
v___y_9773_ = v___x_9780_;
goto v___jp_9772_;
}
else
{
uint32_t v___x_9781_; uint32_t v___x_9782_; uint32_t v___x_9783_; uint32_t v___x_9784_; uint32_t v___x_9785_; float v___x_9786_; lean_object* v___x_9787_; uint32_t v___x_9788_; uint32_t v___x_9789_; uint32_t v___x_9790_; lean_object* v___x_9791_; lean_object* v___x_9792_; float v___x_9793_; float v___x_9794_; 
v___x_9781_ = 8388607;
v___x_9782_ = lean_unbox_uint32(v___x_9776_);
v___x_9783_ = lean_uint32_land(v___x_9782_, v___x_9781_);
v___x_9784_ = 8388608;
v___x_9785_ = lean_uint32_lor(v___x_9783_, v___x_9784_);
v___x_9786_ = lean_uint32_to_float32(v___x_9785_);
v___x_9787_ = lp_competition_R2W01b_scaleTable;
v___x_9788_ = 23;
v___x_9789_ = lean_unbox_uint32(v___x_9776_);
v___x_9790_ = lean_uint32_shift_right(v___x_9789_, v___x_9788_);
v___x_9791_ = lean_uint32_to_nat(v___x_9790_);
v___x_9792_ = lean_array_fget_borrowed(v___x_9787_, v___x_9791_);
lean_dec(v___x_9791_);
v___x_9793_ = lean_unbox_float32(v___x_9792_);
v___x_9794_ = lean_float32_mul(v___x_9786_, v___x_9793_);
v___y_9773_ = v___x_9794_;
goto v___jp_9772_;
}
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_NativeDecodeSum_loop___boxed(lean_object* v_n_9804_, lean_object* v_x_9805_, lean_object* v_k_9806_, lean_object* v_acc_9807_){
_start:
{
float v_acc_boxed_9808_; float v_res_9809_; lean_object* v_r_9810_; 
v_acc_boxed_9808_ = lean_unbox_float32(v_acc_9807_);
lean_dec_ref(v_acc_9807_);
v_res_9809_ = lp_competition_Submission_NativeDecodeSum_loop(v_n_9804_, v_x_9805_, v_k_9806_, v_acc_boxed_9808_);
lean_dec_ref(v_x_9805_);
lean_dec(v_n_9804_);
v_r_9810_ = lean_box_float32(v_res_9809_);
return v_r_9810_;
}
}
LEAN_EXPORT float lp_competition_Submission_NativeDecodeSumWord_loop___redArg(lean_object* v_x_9811_, size_t v_count_9812_, size_t v_k_9813_, float v_acc_9814_){
_start:
{
uint8_t v___x_9815_; 
v___x_9815_ = lean_usize_dec_lt(v_k_9813_, v_count_9812_);
if (v___x_9815_ == 0)
{
return v_acc_9814_;
}
else
{
lean_object* v_value_9816_; size_t v___x_9817_; size_t v___x_9818_; float v___y_9820_; uint8_t v___y_9824_; uint32_t v___x_9841_; uint32_t v___x_9842_; uint32_t v_a_9843_; uint32_t v___x_9844_; uint32_t v___x_9845_; uint32_t v___x_9846_; uint8_t v___x_9847_; 
v_value_9816_ = lean_array_uget_borrowed(v_x_9811_, v_k_9813_);
v___x_9817_ = ((size_t)1ULL);
v___x_9818_ = lean_usize_add(v_k_9813_, v___x_9817_);
v___x_9841_ = 2147483647;
v___x_9842_ = lean_unbox_uint32(v_value_9816_);
v_a_9843_ = lean_uint32_land(v___x_9842_, v___x_9841_);
v___x_9844_ = 201326591;
v___x_9845_ = 1;
v___x_9846_ = lean_uint32_sub(v_a_9843_, v___x_9845_);
v___x_9847_ = lean_uint32_dec_le(v___x_9844_, v___x_9846_);
if (v___x_9847_ == 0)
{
v___y_9824_ = v___x_9847_;
goto v___jp_9823_;
}
else
{
uint32_t v___x_9848_; uint8_t v___x_9849_; 
v___x_9848_ = 2139095040;
v___x_9849_ = lean_uint32_dec_lt(v_a_9843_, v___x_9848_);
v___y_9824_ = v___x_9849_;
goto v___jp_9823_;
}
v___jp_9819_:
{
float v___x_9821_; 
v___x_9821_ = lean_float32_add(v_acc_9814_, v___y_9820_);
v_k_9813_ = v___x_9818_;
v_acc_9814_ = v___x_9821_;
goto _start;
}
v___jp_9823_:
{
if (v___y_9824_ == 0)
{
uint32_t v___x_9825_; float v___x_9826_; 
v___x_9825_ = lean_unbox_uint32(v_value_9816_);
v___x_9826_ = lean_float32_of_bits(v___x_9825_);
v___y_9820_ = v___x_9826_;
goto v___jp_9819_;
}
else
{
uint32_t v___x_9827_; uint32_t v___x_9828_; uint32_t v___x_9829_; uint32_t v___x_9830_; uint32_t v___x_9831_; float v___x_9832_; lean_object* v___x_9833_; uint32_t v___x_9834_; uint32_t v___x_9835_; uint32_t v___x_9836_; lean_object* v___x_9837_; lean_object* v___x_9838_; float v___x_9839_; float v___x_9840_; 
v___x_9827_ = 8388607;
v___x_9828_ = lean_unbox_uint32(v_value_9816_);
v___x_9829_ = lean_uint32_land(v___x_9828_, v___x_9827_);
v___x_9830_ = 8388608;
v___x_9831_ = lean_uint32_lor(v___x_9829_, v___x_9830_);
v___x_9832_ = lean_uint32_to_float32(v___x_9831_);
v___x_9833_ = lp_competition_R2W01b_scaleTable;
v___x_9834_ = 23;
v___x_9835_ = lean_unbox_uint32(v_value_9816_);
v___x_9836_ = lean_uint32_shift_right(v___x_9835_, v___x_9834_);
v___x_9837_ = lean_uint32_to_nat(v___x_9836_);
v___x_9838_ = lean_array_fget_borrowed(v___x_9833_, v___x_9837_);
lean_dec(v___x_9837_);
v___x_9839_ = lean_unbox_float32(v___x_9838_);
v___x_9840_ = lean_float32_mul(v___x_9832_, v___x_9839_);
v___y_9820_ = v___x_9840_;
goto v___jp_9819_;
}
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_NativeDecodeSumWord_loop___redArg___boxed(lean_object* v_x_9850_, lean_object* v_count_9851_, lean_object* v_k_9852_, lean_object* v_acc_9853_){
_start:
{
size_t v_count_boxed_9854_; size_t v_k_boxed_9855_; float v_acc_boxed_9856_; float v_res_9857_; lean_object* v_r_9858_; 
v_count_boxed_9854_ = lean_unbox_usize(v_count_9851_);
lean_dec(v_count_9851_);
v_k_boxed_9855_ = lean_unbox_usize(v_k_9852_);
lean_dec(v_k_9852_);
v_acc_boxed_9856_ = lean_unbox_float32(v_acc_9853_);
lean_dec_ref(v_acc_9853_);
v_res_9857_ = lp_competition_Submission_NativeDecodeSumWord_loop___redArg(v_x_9850_, v_count_boxed_9854_, v_k_boxed_9855_, v_acc_boxed_9856_);
lean_dec_ref(v_x_9850_);
v_r_9858_ = lean_box_float32(v_res_9857_);
return v_r_9858_;
}
}
LEAN_EXPORT float lp_competition_Submission_NativeDecodeSumWord_loop(lean_object* v_n_9859_, lean_object* v_x_9860_, size_t v_count_9861_, lean_object* v_hn_9862_, size_t v_k_9863_, float v_acc_9864_){
_start:
{
float v___x_9865_; 
v___x_9865_ = lp_competition_Submission_NativeDecodeSumWord_loop___redArg(v_x_9860_, v_count_9861_, v_k_9863_, v_acc_9864_);
return v___x_9865_;
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_NativeDecodeSumWord_loop___boxed(lean_object* v_n_9866_, lean_object* v_x_9867_, lean_object* v_count_9868_, lean_object* v_hn_9869_, lean_object* v_k_9870_, lean_object* v_acc_9871_){
_start:
{
size_t v_count_boxed_9872_; size_t v_k_boxed_9873_; float v_acc_boxed_9874_; float v_res_9875_; lean_object* v_r_9876_; 
v_count_boxed_9872_ = lean_unbox_usize(v_count_9868_);
lean_dec(v_count_9868_);
v_k_boxed_9873_ = lean_unbox_usize(v_k_9870_);
lean_dec(v_k_9870_);
v_acc_boxed_9874_ = lean_unbox_float32(v_acc_9871_);
lean_dec_ref(v_acc_9871_);
v_res_9875_ = lp_competition_Submission_NativeDecodeSumWord_loop(v_n_9866_, v_x_9867_, v_count_boxed_9872_, v_hn_9869_, v_k_boxed_9873_, v_acc_boxed_9874_);
lean_dec_ref(v_x_9867_);
lean_dec(v_n_9866_);
v_r_9876_ = lean_box_float32(v_res_9875_);
return v_r_9876_;
}
}
LEAN_EXPORT float lp_competition_Submission_NativeDecodeSumWord_run(lean_object* v_n_9877_, lean_object* v_x_9878_){
_start:
{
lean_object* v___x_9879_; uint8_t v___x_9880_; 
v___x_9879_ = lean_obj_once(&lp_competition_Submission_Packed10Index_runDot___closed__0, &lp_competition_Submission_Packed10Index_runDot___closed__0_once, _init_lp_competition_Submission_Packed10Index_runDot___closed__0);
v___x_9880_ = lean_nat_dec_lt(v_n_9877_, v___x_9879_);
if (v___x_9880_ == 0)
{
lean_object* v___x_9881_; float v___x_9882_; float v___x_9883_; 
v___x_9881_ = lean_unsigned_to_nat(0u);
v___x_9882_ = lean_float32_once(&lp_competition_Submission_NativeFinal_dot___closed__0, &lp_competition_Submission_NativeFinal_dot___closed__0_once, _init_lp_competition_Submission_NativeFinal_dot___closed__0);
v___x_9883_ = lp_competition_Submission_NativeDecodeSum_loop(v_n_9877_, v_x_9878_, v___x_9881_, v___x_9882_);
return v___x_9883_;
}
else
{
size_t v___x_9884_; size_t v___x_9885_; float v___x_9886_; float v___x_9887_; 
v___x_9884_ = lean_usize_of_nat(v_n_9877_);
v___x_9885_ = ((size_t)0ULL);
v___x_9886_ = lean_float32_once(&lp_competition_Submission_NativeFinal_dot___closed__0, &lp_competition_Submission_NativeFinal_dot___closed__0_once, _init_lp_competition_Submission_NativeFinal_dot___closed__0);
v___x_9887_ = lp_competition_Submission_NativeDecodeSumWord_loop___redArg(v_x_9878_, v___x_9884_, v___x_9885_, v___x_9886_);
return v___x_9887_;
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_NativeDecodeSumWord_run___boxed(lean_object* v_n_9888_, lean_object* v_x_9889_){
_start:
{
float v_res_9890_; lean_object* v_r_9891_; 
v_res_9890_ = lp_competition_Submission_NativeDecodeSumWord_run(v_n_9888_, v_x_9889_);
lean_dec_ref(v_x_9889_);
lean_dec(v_n_9888_);
v_r_9891_ = lean_box_float32(v_res_9890_);
return v_r_9891_;
}
}
LEAN_EXPORT uint32_t lp_competition_Submission_sum(lean_object* v_n_9892_, lean_object* v_x_9893_){
_start:
{
float v___y_9895_; lean_object* v___x_9899_; uint8_t v___x_9900_; 
v___x_9899_ = lean_obj_once(&lp_competition_Submission_Packed10Index_runDot___closed__0, &lp_competition_Submission_Packed10Index_runDot___closed__0_once, _init_lp_competition_Submission_Packed10Index_runDot___closed__0);
v___x_9900_ = lean_nat_dec_lt(v_n_9892_, v___x_9899_);
if (v___x_9900_ == 0)
{
lean_object* v___x_9901_; float v___x_9902_; float v___x_9903_; 
v___x_9901_ = lean_unsigned_to_nat(0u);
v___x_9902_ = lean_float32_once(&lp_competition_Submission_NativeFinal_dot___closed__0, &lp_competition_Submission_NativeFinal_dot___closed__0_once, _init_lp_competition_Submission_NativeFinal_dot___closed__0);
v___x_9903_ = lp_competition_Submission_NativeDecodeSum_loop(v_n_9892_, v_x_9893_, v___x_9901_, v___x_9902_);
v___y_9895_ = v___x_9903_;
goto v___jp_9894_;
}
else
{
size_t v___x_9904_; size_t v___x_9905_; float v___x_9906_; float v___x_9907_; 
v___x_9904_ = lean_usize_of_nat(v_n_9892_);
v___x_9905_ = ((size_t)0ULL);
v___x_9906_ = lean_float32_once(&lp_competition_Submission_NativeFinal_dot___closed__0, &lp_competition_Submission_NativeFinal_dot___closed__0_once, _init_lp_competition_Submission_NativeFinal_dot___closed__0);
v___x_9907_ = lp_competition_Submission_NativeDecodeSumWord_loop___redArg(v_x_9893_, v___x_9904_, v___x_9905_, v___x_9906_);
v___y_9895_ = v___x_9907_;
goto v___jp_9894_;
}
v___jp_9894_:
{
uint8_t v___x_9896_; 
v___x_9896_ = lean_float32_isfinite(v___y_9895_);
if (v___x_9896_ == 0)
{
uint32_t v___x_9897_; 
v___x_9897_ = lp_competition_Submission_referenceSum___redArg(v_x_9893_);
return v___x_9897_;
}
else
{
uint32_t v___x_9898_; 
v___x_9898_ = lean_float32_to_bits(v___y_9895_);
return v___x_9898_;
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_sum___boxed(lean_object* v_n_9908_, lean_object* v_x_9909_){
_start:
{
uint32_t v_res_9910_; lean_object* v_r_9911_; 
v_res_9910_ = lp_competition_Submission_sum(v_n_9908_, v_x_9909_);
lean_dec_ref(v_x_9909_);
lean_dec(v_n_9908_);
v_r_9911_ = lean_box_uint32(v_res_9910_);
return v_r_9911_;
}
}
LEAN_EXPORT uint32_t lp_competition_Submission_RowOutput_row___redArg___lam__0(lean_object* v_baseB_9912_, lean_object* v_tiles_9913_, lean_object* v_n_9914_, lean_object* v_baseA_9915_, lean_object* v_p_9916_, lean_object* v_A_9917_, lean_object* v_B_9918_, lean_object* v_j_9919_){
_start:
{
lean_object* v___x_9920_; lean_object* v___x_9921_; lean_object* v___x_9922_; lean_object* v___x_9923_; lean_object* v___x_9924_; lean_object* v___x_9925_; uint8_t v___x_9926_; 
v___x_9920_ = lean_unsigned_to_nat(10u);
v___x_9921_ = lean_nat_div(v_j_9919_, v___x_9920_);
v___x_9922_ = lean_nat_mod(v_j_9919_, v___x_9920_);
v___x_9923_ = lean_nat_add(v_baseB_9912_, v_j_9919_);
v___x_9924_ = lean_array_fget_borrowed(v_tiles_9913_, v___x_9921_);
lean_dec(v___x_9921_);
v___x_9925_ = lean_unsigned_to_nat(0u);
v___x_9926_ = lean_nat_dec_eq(v___x_9922_, v___x_9925_);
if (v___x_9926_ == 0)
{
lean_object* v___x_9927_; uint8_t v___x_9928_; 
v___x_9927_ = lean_unsigned_to_nat(1u);
v___x_9928_ = lean_nat_dec_eq(v___x_9922_, v___x_9927_);
if (v___x_9928_ == 0)
{
lean_object* v___x_9929_; uint8_t v___x_9930_; 
v___x_9929_ = lean_unsigned_to_nat(2u);
v___x_9930_ = lean_nat_dec_eq(v___x_9922_, v___x_9929_);
if (v___x_9930_ == 0)
{
lean_object* v___x_9931_; uint8_t v___x_9932_; 
v___x_9931_ = lean_unsigned_to_nat(3u);
v___x_9932_ = lean_nat_dec_eq(v___x_9922_, v___x_9931_);
if (v___x_9932_ == 0)
{
lean_object* v___x_9933_; uint8_t v___x_9934_; 
v___x_9933_ = lean_unsigned_to_nat(4u);
v___x_9934_ = lean_nat_dec_eq(v___x_9922_, v___x_9933_);
if (v___x_9934_ == 0)
{
lean_object* v___x_9935_; uint8_t v___x_9936_; 
v___x_9935_ = lean_unsigned_to_nat(5u);
v___x_9936_ = lean_nat_dec_eq(v___x_9922_, v___x_9935_);
if (v___x_9936_ == 0)
{
lean_object* v___x_9937_; uint8_t v___x_9938_; 
v___x_9937_ = lean_unsigned_to_nat(6u);
v___x_9938_ = lean_nat_dec_eq(v___x_9922_, v___x_9937_);
if (v___x_9938_ == 0)
{
lean_object* v___x_9939_; uint8_t v___x_9940_; 
v___x_9939_ = lean_unsigned_to_nat(7u);
v___x_9940_ = lean_nat_dec_eq(v___x_9922_, v___x_9939_);
if (v___x_9940_ == 0)
{
lean_object* v___x_9941_; uint8_t v___x_9942_; 
v___x_9941_ = lean_unsigned_to_nat(8u);
v___x_9942_ = lean_nat_dec_eq(v___x_9922_, v___x_9941_);
lean_dec(v___x_9922_);
if (v___x_9942_ == 0)
{
float v_s9_9943_; uint32_t v___x_9944_; 
v_s9_9943_ = lean_ctor_get_float32(v___x_9924_, 36);
v___x_9944_ = lp_competition_Submission_Packed10_finish(v_n_9914_, v_baseA_9915_, v___x_9923_, v_p_9916_, v_A_9917_, v_B_9918_, v_s9_9943_);
lean_dec(v___x_9923_);
return v___x_9944_;
}
else
{
float v_s8_9945_; uint32_t v___x_9946_; 
v_s8_9945_ = lean_ctor_get_float32(v___x_9924_, 32);
v___x_9946_ = lp_competition_Submission_Packed10_finish(v_n_9914_, v_baseA_9915_, v___x_9923_, v_p_9916_, v_A_9917_, v_B_9918_, v_s8_9945_);
lean_dec(v___x_9923_);
return v___x_9946_;
}
}
else
{
float v_s7_9947_; uint32_t v___x_9948_; 
lean_dec(v___x_9922_);
v_s7_9947_ = lean_ctor_get_float32(v___x_9924_, 28);
v___x_9948_ = lp_competition_Submission_Packed10_finish(v_n_9914_, v_baseA_9915_, v___x_9923_, v_p_9916_, v_A_9917_, v_B_9918_, v_s7_9947_);
lean_dec(v___x_9923_);
return v___x_9948_;
}
}
else
{
float v_s6_9949_; uint32_t v___x_9950_; 
lean_dec(v___x_9922_);
v_s6_9949_ = lean_ctor_get_float32(v___x_9924_, 24);
v___x_9950_ = lp_competition_Submission_Packed10_finish(v_n_9914_, v_baseA_9915_, v___x_9923_, v_p_9916_, v_A_9917_, v_B_9918_, v_s6_9949_);
lean_dec(v___x_9923_);
return v___x_9950_;
}
}
else
{
float v_s5_9951_; uint32_t v___x_9952_; 
lean_dec(v___x_9922_);
v_s5_9951_ = lean_ctor_get_float32(v___x_9924_, 20);
v___x_9952_ = lp_competition_Submission_Packed10_finish(v_n_9914_, v_baseA_9915_, v___x_9923_, v_p_9916_, v_A_9917_, v_B_9918_, v_s5_9951_);
lean_dec(v___x_9923_);
return v___x_9952_;
}
}
else
{
float v_s4_9953_; uint32_t v___x_9954_; 
lean_dec(v___x_9922_);
v_s4_9953_ = lean_ctor_get_float32(v___x_9924_, 16);
v___x_9954_ = lp_competition_Submission_Packed10_finish(v_n_9914_, v_baseA_9915_, v___x_9923_, v_p_9916_, v_A_9917_, v_B_9918_, v_s4_9953_);
lean_dec(v___x_9923_);
return v___x_9954_;
}
}
else
{
float v_s3_9955_; uint32_t v___x_9956_; 
lean_dec(v___x_9922_);
v_s3_9955_ = lean_ctor_get_float32(v___x_9924_, 12);
v___x_9956_ = lp_competition_Submission_Packed10_finish(v_n_9914_, v_baseA_9915_, v___x_9923_, v_p_9916_, v_A_9917_, v_B_9918_, v_s3_9955_);
lean_dec(v___x_9923_);
return v___x_9956_;
}
}
else
{
float v_s2_9957_; uint32_t v___x_9958_; 
lean_dec(v___x_9922_);
v_s2_9957_ = lean_ctor_get_float32(v___x_9924_, 8);
v___x_9958_ = lp_competition_Submission_Packed10_finish(v_n_9914_, v_baseA_9915_, v___x_9923_, v_p_9916_, v_A_9917_, v_B_9918_, v_s2_9957_);
lean_dec(v___x_9923_);
return v___x_9958_;
}
}
else
{
float v_s1_9959_; uint32_t v___x_9960_; 
lean_dec(v___x_9922_);
v_s1_9959_ = lean_ctor_get_float32(v___x_9924_, 4);
v___x_9960_ = lp_competition_Submission_Packed10_finish(v_n_9914_, v_baseA_9915_, v___x_9923_, v_p_9916_, v_A_9917_, v_B_9918_, v_s1_9959_);
lean_dec(v___x_9923_);
return v___x_9960_;
}
}
else
{
float v_s0_9961_; uint32_t v___x_9962_; 
lean_dec(v___x_9922_);
v_s0_9961_ = lean_ctor_get_float32(v___x_9924_, 0);
v___x_9962_ = lp_competition_Submission_Packed10_finish(v_n_9914_, v_baseA_9915_, v___x_9923_, v_p_9916_, v_A_9917_, v_B_9918_, v_s0_9961_);
lean_dec(v___x_9923_);
return v___x_9962_;
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_RowOutput_row___redArg___lam__0___boxed(lean_object* v_baseB_9963_, lean_object* v_tiles_9964_, lean_object* v_n_9965_, lean_object* v_baseA_9966_, lean_object* v_p_9967_, lean_object* v_A_9968_, lean_object* v_B_9969_, lean_object* v_j_9970_){
_start:
{
uint32_t v_res_9971_; lean_object* v_r_9972_; 
v_res_9971_ = lp_competition_Submission_RowOutput_row___redArg___lam__0(v_baseB_9963_, v_tiles_9964_, v_n_9965_, v_baseA_9966_, v_p_9967_, v_A_9968_, v_B_9969_, v_j_9970_);
lean_dec(v_j_9970_);
lean_dec_ref(v_B_9969_);
lean_dec_ref(v_A_9968_);
lean_dec(v_p_9967_);
lean_dec(v_baseA_9966_);
lean_dec(v_n_9965_);
lean_dec_ref(v_tiles_9964_);
lean_dec(v_baseB_9963_);
v_r_9972_ = lean_box_uint32(v_res_9971_);
return v_r_9972_;
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_RowOutput_row___redArg(lean_object* v_m_9973_, lean_object* v_n_9974_, lean_object* v_p_9975_, lean_object* v_A_9976_, lean_object* v_B_9977_, lean_object* v_b_9978_, lean_object* v_i_9979_, lean_object* v_tiles_9980_){
_start:
{
lean_object* v___x_9981_; lean_object* v___x_9982_; lean_object* v_baseA_9983_; lean_object* v___x_9984_; lean_object* v_baseB_9985_; lean_object* v___f_9986_; lean_object* v___x_9987_; 
v___x_9981_ = lean_nat_mul(v_b_9978_, v_m_9973_);
v___x_9982_ = lean_nat_add(v___x_9981_, v_i_9979_);
lean_dec(v___x_9981_);
v_baseA_9983_ = lean_nat_mul(v___x_9982_, v_n_9974_);
lean_dec(v___x_9982_);
v___x_9984_ = lean_nat_mul(v_b_9978_, v_n_9974_);
v_baseB_9985_ = lean_nat_mul(v___x_9984_, v_p_9975_);
lean_dec(v___x_9984_);
lean_inc(v_p_9975_);
v___f_9986_ = lean_alloc_closure((void*)(lp_competition_Submission_RowOutput_row___redArg___lam__0___boxed), 8, 7);
lean_closure_set(v___f_9986_, 0, v_baseB_9985_);
lean_closure_set(v___f_9986_, 1, v_tiles_9980_);
lean_closure_set(v___f_9986_, 2, v_n_9974_);
lean_closure_set(v___f_9986_, 3, v_baseA_9983_);
lean_closure_set(v___f_9986_, 4, v_p_9975_);
lean_closure_set(v___f_9986_, 5, v_A_9976_);
lean_closure_set(v___f_9986_, 6, v_B_9977_);
v___x_9987_ = l_Array_ofFn___redArg(v_p_9975_, v___f_9986_);
return v___x_9987_;
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_RowOutput_row___redArg___boxed(lean_object* v_m_9988_, lean_object* v_n_9989_, lean_object* v_p_9990_, lean_object* v_A_9991_, lean_object* v_B_9992_, lean_object* v_b_9993_, lean_object* v_i_9994_, lean_object* v_tiles_9995_){
_start:
{
lean_object* v_res_9996_; 
v_res_9996_ = lp_competition_Submission_RowOutput_row___redArg(v_m_9988_, v_n_9989_, v_p_9990_, v_A_9991_, v_B_9992_, v_b_9993_, v_i_9994_, v_tiles_9995_);
lean_dec(v_i_9994_);
lean_dec(v_b_9993_);
lean_dec(v_m_9988_);
return v_res_9996_;
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_RowOutput_row(lean_object* v_batch_9997_, lean_object* v_m_9998_, lean_object* v_n_9999_, lean_object* v_p_10000_, lean_object* v_A_10001_, lean_object* v_B_10002_, lean_object* v_b_10003_, lean_object* v_i_10004_, lean_object* v_tiles_10005_){
_start:
{
lean_object* v___x_10006_; 
v___x_10006_ = lp_competition_Submission_RowOutput_row___redArg(v_m_9998_, v_n_9999_, v_p_10000_, v_A_10001_, v_B_10002_, v_b_10003_, v_i_10004_, v_tiles_10005_);
return v___x_10006_;
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_RowOutput_row___boxed(lean_object* v_batch_10007_, lean_object* v_m_10008_, lean_object* v_n_10009_, lean_object* v_p_10010_, lean_object* v_A_10011_, lean_object* v_B_10012_, lean_object* v_b_10013_, lean_object* v_i_10014_, lean_object* v_tiles_10015_){
_start:
{
lean_object* v_res_10016_; 
v_res_10016_ = lp_competition_Submission_RowOutput_row(v_batch_10007_, v_m_10008_, v_n_10009_, v_p_10010_, v_A_10011_, v_B_10012_, v_b_10013_, v_i_10014_, v_tiles_10015_);
lean_dec(v_i_10014_);
lean_dec(v_b_10013_);
lean_dec(v_m_10008_);
lean_dec(v_batch_10007_);
return v_res_10016_;
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_RowOutput_output___lam__0(lean_object* v_batchTiles_10017_, lean_object* v_m_10018_, lean_object* v_n_10019_, lean_object* v_p_10020_, lean_object* v_A_10021_, lean_object* v_B_10022_, lean_object* v_b_10023_, lean_object* v_i_10024_){
_start:
{
lean_object* v___x_10025_; lean_object* v___x_10026_; 
v___x_10025_ = lean_array_fget_borrowed(v_batchTiles_10017_, v_i_10024_);
lean_inc(v___x_10025_);
v___x_10026_ = lp_competition_Submission_RowOutput_row___redArg(v_m_10018_, v_n_10019_, v_p_10020_, v_A_10021_, v_B_10022_, v_b_10023_, v_i_10024_, v___x_10025_);
return v___x_10026_;
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_RowOutput_output___lam__0___boxed(lean_object* v_batchTiles_10027_, lean_object* v_m_10028_, lean_object* v_n_10029_, lean_object* v_p_10030_, lean_object* v_A_10031_, lean_object* v_B_10032_, lean_object* v_b_10033_, lean_object* v_i_10034_){
_start:
{
lean_object* v_res_10035_; 
v_res_10035_ = lp_competition_Submission_RowOutput_output___lam__0(v_batchTiles_10027_, v_m_10028_, v_n_10029_, v_p_10030_, v_A_10031_, v_B_10032_, v_b_10033_, v_i_10034_);
lean_dec(v_i_10034_);
lean_dec(v_b_10033_);
lean_dec(v_m_10028_);
lean_dec_ref(v_batchTiles_10027_);
return v_res_10035_;
}
}
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_mapMUnsafe_map___at___00Submission_RowOutput_output_spec__0(size_t v_sz_10036_, size_t v_i_10037_, lean_object* v_bs_10038_){
_start:
{
uint8_t v___x_10039_; 
v___x_10039_ = lean_usize_dec_lt(v_i_10037_, v_sz_10036_);
if (v___x_10039_ == 0)
{
return v_bs_10038_;
}
else
{
lean_object* v_v_10040_; lean_object* v___x_10041_; lean_object* v_bs_x27_10042_; size_t v___x_10043_; size_t v___x_10044_; lean_object* v___x_10045_; 
v_v_10040_ = lean_array_uget(v_bs_10038_, v_i_10037_);
v___x_10041_ = lean_unsigned_to_nat(0u);
v_bs_x27_10042_ = lean_array_uset(v_bs_10038_, v_i_10037_, v___x_10041_);
v___x_10043_ = ((size_t)1ULL);
v___x_10044_ = lean_usize_add(v_i_10037_, v___x_10043_);
v___x_10045_ = lean_array_uset(v_bs_x27_10042_, v_i_10037_, v_v_10040_);
v_i_10037_ = v___x_10044_;
v_bs_10038_ = v___x_10045_;
goto _start;
}
}
}
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_mapMUnsafe_map___at___00Submission_RowOutput_output_spec__0___boxed(lean_object* v_sz_10047_, lean_object* v_i_10048_, lean_object* v_bs_10049_){
_start:
{
size_t v_sz_boxed_10050_; size_t v_i_boxed_10051_; lean_object* v_res_10052_; 
v_sz_boxed_10050_ = lean_unbox_usize(v_sz_10047_);
lean_dec(v_sz_10047_);
v_i_boxed_10051_ = lean_unbox_usize(v_i_10048_);
lean_dec(v_i_10048_);
v_res_10052_ = lp_competition___private_Init_Data_Array_Basic_0__Array_mapMUnsafe_map___at___00Submission_RowOutput_output_spec__0(v_sz_boxed_10050_, v_i_boxed_10051_, v_bs_10049_);
return v_res_10052_;
}
}
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_foldlMUnsafe_fold___at___00Submission_RowOutput_output_spec__1(lean_object* v_as_10053_, size_t v_i_10054_, size_t v_stop_10055_, lean_object* v_b_10056_){
_start:
{
uint8_t v___x_10057_; 
v___x_10057_ = lean_usize_dec_eq(v_i_10054_, v_stop_10055_);
if (v___x_10057_ == 0)
{
lean_object* v___x_10058_; lean_object* v___x_10059_; size_t v___x_10060_; size_t v___x_10061_; 
v___x_10058_ = lean_array_uget_borrowed(v_as_10053_, v_i_10054_);
v___x_10059_ = l_Array_append___redArg(v_b_10056_, v___x_10058_);
v___x_10060_ = ((size_t)1ULL);
v___x_10061_ = lean_usize_add(v_i_10054_, v___x_10060_);
v_i_10054_ = v___x_10061_;
v_b_10056_ = v___x_10059_;
goto _start;
}
else
{
return v_b_10056_;
}
}
}
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_foldlMUnsafe_fold___at___00Submission_RowOutput_output_spec__1___boxed(lean_object* v_as_10063_, lean_object* v_i_10064_, lean_object* v_stop_10065_, lean_object* v_b_10066_){
_start:
{
size_t v_i_boxed_10067_; size_t v_stop_boxed_10068_; lean_object* v_res_10069_; 
v_i_boxed_10067_ = lean_unbox_usize(v_i_10064_);
lean_dec(v_i_10064_);
v_stop_boxed_10068_ = lean_unbox_usize(v_stop_10065_);
lean_dec(v_stop_10065_);
v_res_10069_ = lp_competition___private_Init_Data_Array_Basic_0__Array_foldlMUnsafe_fold___at___00Submission_RowOutput_output_spec__1(v_as_10063_, v_i_boxed_10067_, v_stop_boxed_10068_, v_b_10066_);
lean_dec_ref(v_as_10063_);
return v_res_10069_;
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_RowOutput_output___lam__1(lean_object* v_tiles_10072_, lean_object* v_m_10073_, lean_object* v_n_10074_, lean_object* v_p_10075_, lean_object* v_A_10076_, lean_object* v_B_10077_, lean_object* v_b_10078_){
_start:
{
lean_object* v_batchTiles_10079_; lean_object* v___f_10080_; lean_object* v___x_10081_; size_t v_sz_10082_; size_t v___x_10083_; lean_object* v___x_10084_; lean_object* v___x_10085_; lean_object* v___x_10086_; lean_object* v___x_10087_; uint8_t v___x_10088_; 
v_batchTiles_10079_ = lean_array_fget_borrowed(v_tiles_10072_, v_b_10078_);
lean_inc(v_m_10073_);
lean_inc(v_batchTiles_10079_);
v___f_10080_ = lean_alloc_closure((void*)(lp_competition_Submission_RowOutput_output___lam__0___boxed), 8, 7);
lean_closure_set(v___f_10080_, 0, v_batchTiles_10079_);
lean_closure_set(v___f_10080_, 1, v_m_10073_);
lean_closure_set(v___f_10080_, 2, v_n_10074_);
lean_closure_set(v___f_10080_, 3, v_p_10075_);
lean_closure_set(v___f_10080_, 4, v_A_10076_);
lean_closure_set(v___f_10080_, 5, v_B_10077_);
lean_closure_set(v___f_10080_, 6, v_b_10078_);
v___x_10081_ = l_Array_ofFn___redArg(v_m_10073_, v___f_10080_);
v_sz_10082_ = lean_array_size(v___x_10081_);
v___x_10083_ = ((size_t)0ULL);
v___x_10084_ = lp_competition___private_Init_Data_Array_Basic_0__Array_mapMUnsafe_map___at___00Submission_RowOutput_output_spec__0(v_sz_10082_, v___x_10083_, v___x_10081_);
v___x_10085_ = lean_unsigned_to_nat(0u);
v___x_10086_ = ((lean_object*)(lp_competition_Submission_RowOutput_output___lam__1___closed__0));
v___x_10087_ = lean_array_get_size(v___x_10084_);
v___x_10088_ = lean_nat_dec_lt(v___x_10085_, v___x_10087_);
if (v___x_10088_ == 0)
{
lean_dec_ref(v___x_10084_);
return v___x_10086_;
}
else
{
uint8_t v___x_10089_; 
v___x_10089_ = lean_nat_dec_le(v___x_10087_, v___x_10087_);
if (v___x_10089_ == 0)
{
if (v___x_10088_ == 0)
{
lean_dec_ref(v___x_10084_);
return v___x_10086_;
}
else
{
size_t v___x_10090_; lean_object* v___x_10091_; 
v___x_10090_ = lean_usize_of_nat(v___x_10087_);
v___x_10091_ = lp_competition___private_Init_Data_Array_Basic_0__Array_foldlMUnsafe_fold___at___00Submission_RowOutput_output_spec__1(v___x_10084_, v___x_10083_, v___x_10090_, v___x_10086_);
lean_dec_ref(v___x_10084_);
return v___x_10091_;
}
}
else
{
size_t v___x_10092_; lean_object* v___x_10093_; 
v___x_10092_ = lean_usize_of_nat(v___x_10087_);
v___x_10093_ = lp_competition___private_Init_Data_Array_Basic_0__Array_foldlMUnsafe_fold___at___00Submission_RowOutput_output_spec__1(v___x_10084_, v___x_10083_, v___x_10092_, v___x_10086_);
lean_dec_ref(v___x_10084_);
return v___x_10093_;
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_RowOutput_output___lam__1___boxed(lean_object* v_tiles_10094_, lean_object* v_m_10095_, lean_object* v_n_10096_, lean_object* v_p_10097_, lean_object* v_A_10098_, lean_object* v_B_10099_, lean_object* v_b_10100_){
_start:
{
lean_object* v_res_10101_; 
v_res_10101_ = lp_competition_Submission_RowOutput_output___lam__1(v_tiles_10094_, v_m_10095_, v_n_10096_, v_p_10097_, v_A_10098_, v_B_10099_, v_b_10100_);
lean_dec_ref(v_tiles_10094_);
return v_res_10101_;
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_RowOutput_output(lean_object* v_batch_10102_, lean_object* v_m_10103_, lean_object* v_n_10104_, lean_object* v_p_10105_, lean_object* v_A_10106_, lean_object* v_B_10107_, lean_object* v_tiles_10108_){
_start:
{
lean_object* v___f_10109_; lean_object* v___x_10110_; size_t v_sz_10111_; size_t v___x_10112_; lean_object* v___x_10113_; lean_object* v___x_10114_; lean_object* v___x_10115_; lean_object* v___x_10116_; uint8_t v___x_10117_; 
v___f_10109_ = lean_alloc_closure((void*)(lp_competition_Submission_RowOutput_output___lam__1___boxed), 7, 6);
lean_closure_set(v___f_10109_, 0, v_tiles_10108_);
lean_closure_set(v___f_10109_, 1, v_m_10103_);
lean_closure_set(v___f_10109_, 2, v_n_10104_);
lean_closure_set(v___f_10109_, 3, v_p_10105_);
lean_closure_set(v___f_10109_, 4, v_A_10106_);
lean_closure_set(v___f_10109_, 5, v_B_10107_);
v___x_10110_ = l_Array_ofFn___redArg(v_batch_10102_, v___f_10109_);
v_sz_10111_ = lean_array_size(v___x_10110_);
v___x_10112_ = ((size_t)0ULL);
v___x_10113_ = lp_competition___private_Init_Data_Array_Basic_0__Array_mapMUnsafe_map___at___00Submission_RowOutput_output_spec__0(v_sz_10111_, v___x_10112_, v___x_10110_);
v___x_10114_ = lean_unsigned_to_nat(0u);
v___x_10115_ = ((lean_object*)(lp_competition_Submission_RowOutput_output___lam__1___closed__0));
v___x_10116_ = lean_array_get_size(v___x_10113_);
v___x_10117_ = lean_nat_dec_lt(v___x_10114_, v___x_10116_);
if (v___x_10117_ == 0)
{
lean_dec_ref(v___x_10113_);
return v___x_10115_;
}
else
{
uint8_t v___x_10118_; 
v___x_10118_ = lean_nat_dec_le(v___x_10116_, v___x_10116_);
if (v___x_10118_ == 0)
{
if (v___x_10117_ == 0)
{
lean_dec_ref(v___x_10113_);
return v___x_10115_;
}
else
{
size_t v___x_10119_; lean_object* v___x_10120_; 
v___x_10119_ = lean_usize_of_nat(v___x_10116_);
v___x_10120_ = lp_competition___private_Init_Data_Array_Basic_0__Array_foldlMUnsafe_fold___at___00Submission_RowOutput_output_spec__1(v___x_10113_, v___x_10112_, v___x_10119_, v___x_10115_);
lean_dec_ref(v___x_10113_);
return v___x_10120_;
}
}
else
{
size_t v___x_10121_; lean_object* v___x_10122_; 
v___x_10121_ = lean_usize_of_nat(v___x_10116_);
v___x_10122_ = lp_competition___private_Init_Data_Array_Basic_0__Array_foldlMUnsafe_fold___at___00Submission_RowOutput_output_spec__1(v___x_10113_, v___x_10112_, v___x_10121_, v___x_10115_);
lean_dec_ref(v___x_10113_);
return v___x_10122_;
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_RowOutput_core(lean_object* v_batch_10123_, lean_object* v_m_10124_, lean_object* v_n_10125_, lean_object* v_p_10126_, lean_object* v_A_10127_, lean_object* v_B_10128_){
_start:
{
size_t v_sz_10129_; size_t v___x_10130_; lean_object* v_nativeA_10131_; lean_object* v_packedB_10132_; lean_object* v_tiles_10133_; lean_object* v___x_10134_; 
v_sz_10129_ = lean_array_size(v_A_10127_);
v___x_10130_ = ((size_t)0ULL);
lean_inc_ref(v_A_10127_);
v_nativeA_10131_ = lp_competition___private_Init_Data_Array_Basic_0__Array_mapMUnsafe_map___at___00Submission_Packed10_core_spec__0(v_sz_10129_, v___x_10130_, v_A_10127_);
lean_inc_ref(v_B_10128_);
lean_inc_n(v_p_10126_, 2);
lean_inc_n(v_n_10125_, 2);
lean_inc_n(v_batch_10123_, 2);
v_packedB_10132_ = lp_competition_Submission_Packed10_packB(v_batch_10123_, v_n_10125_, v_p_10126_, v_B_10128_);
lean_inc(v_m_10124_);
v_tiles_10133_ = lp_competition_Submission_Packed10_tileResults(v_batch_10123_, v_m_10124_, v_n_10125_, v_p_10126_, v_nativeA_10131_, v_packedB_10132_);
v___x_10134_ = lp_competition_Submission_RowOutput_output(v_batch_10123_, v_m_10124_, v_n_10125_, v_p_10126_, v_A_10127_, v_B_10128_, v_tiles_10133_);
return v___x_10134_;
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_bmmRows(lean_object* v_batch_10135_, lean_object* v_m_10136_, lean_object* v_n_10137_, lean_object* v_p_10138_, lean_object* v_A_10139_, lean_object* v_B_10140_){
_start:
{
lean_object* v___x_10141_; lean_object* v___x_10142_; lean_object* v___x_10143_; uint8_t v___x_10144_; 
v___x_10141_ = lean_nat_mul(v_batch_10135_, v_m_10136_);
v___x_10142_ = lean_nat_mul(v___x_10141_, v_p_10138_);
lean_dec(v___x_10141_);
v___x_10143_ = lean_unsigned_to_nat(0u);
v___x_10144_ = lean_nat_dec_eq(v___x_10142_, v___x_10143_);
lean_dec(v___x_10142_);
if (v___x_10144_ == 0)
{
uint8_t v___x_10145_; 
v___x_10145_ = lean_nat_dec_eq(v_n_10137_, v___x_10143_);
if (v___x_10145_ == 0)
{
lean_object* v___x_10146_; 
v___x_10146_ = lp_competition_Submission_RowOutput_core(v_batch_10135_, v_m_10136_, v_n_10137_, v_p_10138_, v_A_10139_, v_B_10140_);
return v___x_10146_;
}
else
{
lean_object* v___x_10147_; 
v___x_10147_ = lp_competition_Submission_referenceBmm(v_batch_10135_, v_m_10136_, v_n_10137_, v_p_10138_, v_A_10139_, v_B_10140_);
lean_dec(v_batch_10135_);
return v___x_10147_;
}
}
else
{
lean_object* v___x_10148_; 
v___x_10148_ = lp_competition_Submission_referenceBmm(v_batch_10135_, v_m_10136_, v_n_10137_, v_p_10138_, v_A_10139_, v_B_10140_);
lean_dec(v_batch_10135_);
return v___x_10148_;
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_RowStream_core___lam__0(lean_object* v_r_10149_){
_start:
{
lean_inc(v_r_10149_);
return v_r_10149_;
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_RowStream_core___lam__0___boxed(lean_object* v_r_10150_){
_start:
{
lean_object* v_res_10151_; 
v_res_10151_ = lp_competition_Submission_RowStream_core___lam__0(v_r_10150_);
lean_dec(v_r_10150_);
return v_res_10151_;
}
}
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_foldlMUnsafe_fold___at___00Submission_RowStream_core_spec__0___redArg___lam__0(lean_object* v_b_10152_, lean_object* v_m_10153_, lean_object* v_i_10154_, lean_object* v_n_10155_, lean_object* v_packedB_10156_, lean_object* v_nativeA_10157_, lean_object* v_g_10158_){
_start:
{
lean_object* v___x_10159_; lean_object* v___x_10160_; lean_object* v___x_10161_; lean_object* v___x_10162_; lean_object* v___x_10163_; lean_object* v___x_10168_; uint8_t v___x_10169_; 
v___x_10159_ = lean_nat_mul(v_b_10152_, v_m_10153_);
v___x_10160_ = lean_nat_add(v___x_10159_, v_i_10154_);
lean_dec(v___x_10159_);
v___x_10161_ = lean_nat_mul(v___x_10160_, v_n_10155_);
lean_dec(v___x_10160_);
v___x_10162_ = lean_array_fget_borrowed(v_packedB_10156_, v_b_10152_);
v___x_10163_ = lean_array_fget_borrowed(v___x_10162_, v_g_10158_);
v___x_10168_ = lean_obj_once(&lp_competition_Submission_Packed10Index_runDot___closed__0, &lp_competition_Submission_Packed10Index_runDot___closed__0_once, _init_lp_competition_Submission_Packed10Index_runDot___closed__0);
v___x_10169_ = lean_nat_dec_lt(v_n_10155_, v___x_10168_);
if (v___x_10169_ == 0)
{
goto v___jp_10164_;
}
else
{
uint8_t v___x_10170_; 
v___x_10170_ = lean_nat_dec_lt(v___x_10161_, v___x_10168_);
if (v___x_10170_ == 0)
{
goto v___jp_10164_;
}
else
{
lean_object* v___x_10171_; lean_object* v___x_10172_; lean_object* v___x_10173_; lean_object* v___x_10174_; uint8_t v___x_10175_; 
v___x_10171_ = lean_unsigned_to_nat(1u);
v___x_10172_ = lean_nat_sub(v_n_10155_, v___x_10171_);
v___x_10173_ = lean_nat_add(v___x_10161_, v___x_10172_);
lean_dec(v___x_10172_);
v___x_10174_ = lean_array_get_size(v_nativeA_10157_);
v___x_10175_ = lean_nat_dec_lt(v___x_10173_, v___x_10174_);
lean_dec(v___x_10173_);
if (v___x_10175_ == 0)
{
goto v___jp_10164_;
}
else
{
uint8_t v___x_10176_; 
v___x_10176_ = lean_nat_dec_lt(v___x_10174_, v___x_10168_);
if (v___x_10176_ == 0)
{
goto v___jp_10164_;
}
else
{
size_t v___x_10177_; size_t v___x_10178_; size_t v___x_10179_; float v___x_10180_; lean_object* v___x_10181_; 
v___x_10177_ = lean_usize_of_nat(v_n_10155_);
v___x_10178_ = lean_usize_of_nat(v___x_10161_);
lean_dec(v___x_10161_);
v___x_10179_ = ((size_t)0ULL);
v___x_10180_ = lean_float32_once(&lp_competition_Submission_NativeFinal_dot___closed__0, &lp_competition_Submission_NativeFinal_dot___closed__0_once, _init_lp_competition_Submission_NativeFinal_dot___closed__0);
v___x_10181_ = lp_competition_Submission_Packed10Index_loop___redArg(v___x_10177_, v___x_10178_, v_nativeA_10157_, v___x_10163_, v___x_10179_, v___x_10180_, v___x_10180_, v___x_10180_, v___x_10180_, v___x_10180_, v___x_10180_, v___x_10180_, v___x_10180_, v___x_10180_, v___x_10180_);
return v___x_10181_;
}
}
}
}
v___jp_10164_:
{
lean_object* v___x_10165_; float v___x_10166_; lean_object* v___x_10167_; 
v___x_10165_ = lean_unsigned_to_nat(0u);
v___x_10166_ = lean_float32_once(&lp_competition_Submission_NativeFinal_dot___closed__0, &lp_competition_Submission_NativeFinal_dot___closed__0_once, _init_lp_competition_Submission_NativeFinal_dot___closed__0);
v___x_10167_ = lp_competition_Submission_Packed10_dot10(v_n_10155_, v___x_10161_, v_nativeA_10157_, v___x_10163_, v___x_10165_, v___x_10166_, v___x_10166_, v___x_10166_, v___x_10166_, v___x_10166_, v___x_10166_, v___x_10166_, v___x_10166_, v___x_10166_, v___x_10166_);
lean_dec(v___x_10161_);
return v___x_10167_;
}
}
}
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_foldlMUnsafe_fold___at___00Submission_RowStream_core_spec__0___redArg___lam__0___boxed(lean_object* v_b_10182_, lean_object* v_m_10183_, lean_object* v_i_10184_, lean_object* v_n_10185_, lean_object* v_packedB_10186_, lean_object* v_nativeA_10187_, lean_object* v_g_10188_){
_start:
{
lean_object* v_res_10189_; 
v_res_10189_ = lp_competition___private_Init_Data_Array_Basic_0__Array_foldlMUnsafe_fold___at___00Submission_RowStream_core_spec__0___redArg___lam__0(v_b_10182_, v_m_10183_, v_i_10184_, v_n_10185_, v_packedB_10186_, v_nativeA_10187_, v_g_10188_);
lean_dec(v_g_10188_);
lean_dec_ref(v_nativeA_10187_);
lean_dec_ref(v_packedB_10186_);
lean_dec(v_n_10185_);
lean_dec(v_i_10184_);
lean_dec(v_m_10183_);
lean_dec(v_b_10182_);
return v_res_10189_;
}
}
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_foldlMUnsafe_fold___at___00Submission_RowStream_core_spec__0___redArg(lean_object* v_m_10190_, lean_object* v_n_10191_, lean_object* v_packedB_10192_, lean_object* v_nativeA_10193_, lean_object* v_p_10194_, lean_object* v_A_10195_, lean_object* v_B_10196_, lean_object* v_as_10197_, size_t v_i_10198_, size_t v_stop_10199_, lean_object* v_b_10200_){
_start:
{
uint8_t v___x_10201_; 
v___x_10201_ = lean_usize_dec_eq(v_i_10198_, v_stop_10199_);
if (v___x_10201_ == 0)
{
lean_object* v___x_10202_; lean_object* v_b_10203_; lean_object* v_i_10204_; lean_object* v___f_10205_; lean_object* v___x_10206_; lean_object* v___x_10207_; lean_object* v___x_10208_; lean_object* v___x_10209_; lean_object* v_rowTiles_10210_; lean_object* v___x_10211_; lean_object* v___x_10212_; size_t v___x_10213_; size_t v___x_10214_; 
v___x_10202_ = lean_array_uget_borrowed(v_as_10197_, v_i_10198_);
v_b_10203_ = lean_nat_div(v___x_10202_, v_m_10190_);
v_i_10204_ = lean_nat_mod(v___x_10202_, v_m_10190_);
lean_inc_ref(v_nativeA_10193_);
lean_inc_ref(v_packedB_10192_);
lean_inc_n(v_n_10191_, 2);
lean_inc(v_i_10204_);
lean_inc(v_m_10190_);
lean_inc(v_b_10203_);
v___f_10205_ = lean_alloc_closure((void*)(lp_competition___private_Init_Data_Array_Basic_0__Array_foldlMUnsafe_fold___at___00Submission_RowStream_core_spec__0___redArg___lam__0___boxed), 7, 6);
lean_closure_set(v___f_10205_, 0, v_b_10203_);
lean_closure_set(v___f_10205_, 1, v_m_10190_);
lean_closure_set(v___f_10205_, 2, v_i_10204_);
lean_closure_set(v___f_10205_, 3, v_n_10191_);
lean_closure_set(v___f_10205_, 4, v_packedB_10192_);
lean_closure_set(v___f_10205_, 5, v_nativeA_10193_);
v___x_10206_ = lean_unsigned_to_nat(9u);
v___x_10207_ = lean_nat_add(v_p_10194_, v___x_10206_);
v___x_10208_ = lean_unsigned_to_nat(10u);
v___x_10209_ = lean_nat_div(v___x_10207_, v___x_10208_);
lean_dec(v___x_10207_);
v_rowTiles_10210_ = l_Array_ofFn___redArg(v___x_10209_, v___f_10205_);
lean_inc_ref(v_B_10196_);
lean_inc_ref(v_A_10195_);
lean_inc(v_p_10194_);
v___x_10211_ = lp_competition_Submission_RowOutput_row___redArg(v_m_10190_, v_n_10191_, v_p_10194_, v_A_10195_, v_B_10196_, v_b_10203_, v_i_10204_, v_rowTiles_10210_);
lean_dec(v_i_10204_);
lean_dec(v_b_10203_);
v___x_10212_ = l_Array_append___redArg(v_b_10200_, v___x_10211_);
lean_dec_ref(v___x_10211_);
v___x_10213_ = ((size_t)1ULL);
v___x_10214_ = lean_usize_add(v_i_10198_, v___x_10213_);
v_i_10198_ = v___x_10214_;
v_b_10200_ = v___x_10212_;
goto _start;
}
else
{
lean_dec_ref(v_B_10196_);
lean_dec_ref(v_A_10195_);
lean_dec(v_p_10194_);
lean_dec_ref(v_nativeA_10193_);
lean_dec_ref(v_packedB_10192_);
lean_dec(v_n_10191_);
lean_dec(v_m_10190_);
return v_b_10200_;
}
}
}
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_foldlMUnsafe_fold___at___00Submission_RowStream_core_spec__0___redArg___boxed(lean_object* v_m_10216_, lean_object* v_n_10217_, lean_object* v_packedB_10218_, lean_object* v_nativeA_10219_, lean_object* v_p_10220_, lean_object* v_A_10221_, lean_object* v_B_10222_, lean_object* v_as_10223_, lean_object* v_i_10224_, lean_object* v_stop_10225_, lean_object* v_b_10226_){
_start:
{
size_t v_i_boxed_10227_; size_t v_stop_boxed_10228_; lean_object* v_res_10229_; 
v_i_boxed_10227_ = lean_unbox_usize(v_i_10224_);
lean_dec(v_i_10224_);
v_stop_boxed_10228_ = lean_unbox_usize(v_stop_10225_);
lean_dec(v_stop_10225_);
v_res_10229_ = lp_competition___private_Init_Data_Array_Basic_0__Array_foldlMUnsafe_fold___at___00Submission_RowStream_core_spec__0___redArg(v_m_10216_, v_n_10217_, v_packedB_10218_, v_nativeA_10219_, v_p_10220_, v_A_10221_, v_B_10222_, v_as_10223_, v_i_boxed_10227_, v_stop_boxed_10228_, v_b_10226_);
lean_dec_ref(v_as_10223_);
return v_res_10229_;
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_RowStream_core(lean_object* v_batch_10231_, lean_object* v_m_10232_, lean_object* v_n_10233_, lean_object* v_p_10234_, lean_object* v_A_10235_, lean_object* v_B_10236_){
_start:
{
lean_object* v___f_10237_; lean_object* v___x_10238_; lean_object* v___x_10239_; lean_object* v___x_10240_; lean_object* v___x_10241_; lean_object* v___x_10242_; uint8_t v___x_10243_; 
v___f_10237_ = ((lean_object*)(lp_competition_Submission_RowStream_core___closed__0));
v___x_10238_ = lean_nat_mul(v_batch_10231_, v_m_10232_);
v___x_10239_ = l_Array_ofFn___redArg(v___x_10238_, v___f_10237_);
v___x_10240_ = lean_unsigned_to_nat(0u);
v___x_10241_ = ((lean_object*)(lp_competition_Submission_RowOutput_output___lam__1___closed__0));
v___x_10242_ = lean_array_get_size(v___x_10239_);
v___x_10243_ = lean_nat_dec_lt(v___x_10240_, v___x_10242_);
if (v___x_10243_ == 0)
{
lean_dec_ref(v___x_10239_);
lean_dec_ref(v_B_10236_);
lean_dec_ref(v_A_10235_);
lean_dec(v_p_10234_);
lean_dec(v_n_10233_);
lean_dec(v_m_10232_);
lean_dec(v_batch_10231_);
return v___x_10241_;
}
else
{
size_t v_sz_10244_; size_t v___x_10245_; lean_object* v_nativeA_10246_; lean_object* v_packedB_10247_; uint8_t v___x_10248_; 
v_sz_10244_ = lean_array_size(v_A_10235_);
v___x_10245_ = ((size_t)0ULL);
lean_inc_ref(v_A_10235_);
v_nativeA_10246_ = lp_competition___private_Init_Data_Array_Basic_0__Array_mapMUnsafe_map___at___00Submission_Packed10_core_spec__0(v_sz_10244_, v___x_10245_, v_A_10235_);
lean_inc_ref(v_B_10236_);
lean_inc(v_p_10234_);
lean_inc(v_n_10233_);
v_packedB_10247_ = lp_competition_Submission_Packed10_packB(v_batch_10231_, v_n_10233_, v_p_10234_, v_B_10236_);
v___x_10248_ = lean_nat_dec_le(v___x_10242_, v___x_10242_);
if (v___x_10248_ == 0)
{
if (v___x_10243_ == 0)
{
lean_dec_ref(v_packedB_10247_);
lean_dec_ref(v_nativeA_10246_);
lean_dec_ref(v___x_10239_);
lean_dec_ref(v_B_10236_);
lean_dec_ref(v_A_10235_);
lean_dec(v_p_10234_);
lean_dec(v_n_10233_);
lean_dec(v_m_10232_);
return v___x_10241_;
}
else
{
size_t v___x_10249_; lean_object* v___x_10250_; 
v___x_10249_ = lean_usize_of_nat(v___x_10242_);
v___x_10250_ = lp_competition___private_Init_Data_Array_Basic_0__Array_foldlMUnsafe_fold___at___00Submission_RowStream_core_spec__0___redArg(v_m_10232_, v_n_10233_, v_packedB_10247_, v_nativeA_10246_, v_p_10234_, v_A_10235_, v_B_10236_, v___x_10239_, v___x_10245_, v___x_10249_, v___x_10241_);
lean_dec_ref(v___x_10239_);
return v___x_10250_;
}
}
else
{
size_t v___x_10251_; lean_object* v___x_10252_; 
v___x_10251_ = lean_usize_of_nat(v___x_10242_);
v___x_10252_ = lp_competition___private_Init_Data_Array_Basic_0__Array_foldlMUnsafe_fold___at___00Submission_RowStream_core_spec__0___redArg(v_m_10232_, v_n_10233_, v_packedB_10247_, v_nativeA_10246_, v_p_10234_, v_A_10235_, v_B_10236_, v___x_10239_, v___x_10245_, v___x_10251_, v___x_10241_);
lean_dec_ref(v___x_10239_);
return v___x_10252_;
}
}
}
}
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_foldlMUnsafe_fold___at___00Submission_RowStream_core_spec__0(lean_object* v_m_10253_, lean_object* v_batch_10254_, lean_object* v_n_10255_, lean_object* v_packedB_10256_, lean_object* v_nativeA_10257_, lean_object* v_p_10258_, lean_object* v_A_10259_, lean_object* v_B_10260_, lean_object* v_as_10261_, size_t v_i_10262_, size_t v_stop_10263_, lean_object* v_b_10264_){
_start:
{
lean_object* v___x_10265_; 
v___x_10265_ = lp_competition___private_Init_Data_Array_Basic_0__Array_foldlMUnsafe_fold___at___00Submission_RowStream_core_spec__0___redArg(v_m_10253_, v_n_10255_, v_packedB_10256_, v_nativeA_10257_, v_p_10258_, v_A_10259_, v_B_10260_, v_as_10261_, v_i_10262_, v_stop_10263_, v_b_10264_);
return v___x_10265_;
}
}
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_foldlMUnsafe_fold___at___00Submission_RowStream_core_spec__0___boxed(lean_object* v_m_10266_, lean_object* v_batch_10267_, lean_object* v_n_10268_, lean_object* v_packedB_10269_, lean_object* v_nativeA_10270_, lean_object* v_p_10271_, lean_object* v_A_10272_, lean_object* v_B_10273_, lean_object* v_as_10274_, lean_object* v_i_10275_, lean_object* v_stop_10276_, lean_object* v_b_10277_){
_start:
{
size_t v_i_boxed_10278_; size_t v_stop_boxed_10279_; lean_object* v_res_10280_; 
v_i_boxed_10278_ = lean_unbox_usize(v_i_10275_);
lean_dec(v_i_10275_);
v_stop_boxed_10279_ = lean_unbox_usize(v_stop_10276_);
lean_dec(v_stop_10276_);
v_res_10280_ = lp_competition___private_Init_Data_Array_Basic_0__Array_foldlMUnsafe_fold___at___00Submission_RowStream_core_spec__0(v_m_10266_, v_batch_10267_, v_n_10268_, v_packedB_10269_, v_nativeA_10270_, v_p_10271_, v_A_10272_, v_B_10273_, v_as_10274_, v_i_boxed_10278_, v_stop_boxed_10279_, v_b_10277_);
lean_dec_ref(v_as_10274_);
lean_dec(v_batch_10267_);
return v_res_10280_;
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_bmm(lean_object* v_batch_10281_, lean_object* v_m_10282_, lean_object* v_n_10283_, lean_object* v_p_10284_, lean_object* v_A_10285_, lean_object* v_B_10286_){
_start:
{
lean_object* v___x_10287_; lean_object* v___x_10288_; lean_object* v___x_10289_; uint8_t v___x_10290_; 
v___x_10287_ = lean_nat_mul(v_batch_10281_, v_m_10282_);
v___x_10288_ = lean_nat_mul(v___x_10287_, v_p_10284_);
lean_dec(v___x_10287_);
v___x_10289_ = lean_unsigned_to_nat(0u);
v___x_10290_ = lean_nat_dec_eq(v___x_10288_, v___x_10289_);
lean_dec(v___x_10288_);
if (v___x_10290_ == 0)
{
uint8_t v___x_10291_; 
v___x_10291_ = lean_nat_dec_eq(v_n_10283_, v___x_10289_);
if (v___x_10291_ == 0)
{
lean_object* v___x_10292_; 
v___x_10292_ = lp_competition_Submission_RowStream_core(v_batch_10281_, v_m_10282_, v_n_10283_, v_p_10284_, v_A_10285_, v_B_10286_);
return v___x_10292_;
}
else
{
lean_object* v___x_10293_; 
v___x_10293_ = lp_competition_Submission_referenceBmm(v_batch_10281_, v_m_10282_, v_n_10283_, v_p_10284_, v_A_10285_, v_B_10286_);
lean_dec(v_batch_10281_);
return v___x_10293_;
}
}
else
{
lean_object* v___x_10294_; 
v___x_10294_ = lp_competition_Submission_referenceBmm(v_batch_10281_, v_m_10282_, v_n_10283_, v_p_10284_, v_A_10285_, v_B_10286_);
lean_dec(v_batch_10281_);
return v___x_10294_;
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
