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
LEAN_EXPORT uint32_t lp_competition_Submission_LowScale_roundLow(uint8_t, uint64_t, uint64_t);
LEAN_EXPORT lean_object* lp_competition_Submission_LowScale_roundLow___boxed(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT uint32_t lp_competition_Submission_LowScale_roundSelect(uint8_t, uint64_t, uint64_t);
LEAN_EXPORT lean_object* lp_competition_Submission_LowScale_roundSelect___boxed(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT uint32_t lp_competition_Submission_LowScale_core(uint32_t, uint32_t);
LEAN_EXPORT lean_object* lp_competition_Submission_LowScale_core___boxed(lean_object*, lean_object*);
LEAN_EXPORT uint32_t lp_competition_Submission_LowScale_mul(uint32_t, uint32_t);
LEAN_EXPORT lean_object* lp_competition_Submission_LowScale_mul___boxed(lean_object*, lean_object*);
LEAN_EXPORT uint32_t lp_competition_Submission_addR6Parent(uint32_t, uint32_t);
LEAN_EXPORT lean_object* lp_competition_Submission_addR6Parent___boxed(lean_object*, lean_object*);
LEAN_EXPORT uint8_t lp_competition_Submission_R6NormalAdd_normalOK(uint32_t);
LEAN_EXPORT lean_object* lp_competition_Submission_R6NormalAdd_normalOK___boxed(lean_object*);
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
LEAN_EXPORT uint32_t lp_competition_Submission_LowScale_roundLow(uint8_t v_sign_3365_, uint64_t v_product_3366_, uint64_t v_scale_3367_){
_start:
{
uint32_t v___y_3369_; uint32_t v___y_3373_; uint32_t v___y_3374_; uint64_t v___x_3378_; uint64_t v___y_3380_; uint8_t v___x_3391_; 
v___x_3378_ = 0ULL;
v___x_3391_ = lean_uint64_dec_eq(v_product_3366_, v___x_3378_);
if (v___x_3391_ == 0)
{
uint64_t v___x_3392_; uint64_t v___x_3393_; uint8_t v___x_3394_; 
v___x_3392_ = 149ULL;
v___x_3393_ = lean_uint64_sub(v___x_3392_, v_scale_3367_);
v___x_3394_ = lean_uint64_dec_eq(v___x_3393_, v___x_3378_);
if (v___x_3394_ == 0)
{
uint64_t v___x_3395_; uint8_t v___x_3396_; 
v___x_3395_ = 64ULL;
v___x_3396_ = lean_uint64_dec_lt(v___x_3393_, v___x_3395_);
if (v___x_3396_ == 0)
{
uint8_t v___x_3397_; 
v___x_3397_ = lean_uint64_dec_eq(v___x_3393_, v___x_3395_);
if (v___x_3397_ == 0)
{
v___y_3380_ = v___x_3378_;
goto v___jp_3379_;
}
else
{
uint64_t v___x_3398_; uint8_t v___x_3399_; 
v___x_3398_ = 9223372036854775808ULL;
v___x_3399_ = lean_uint64_dec_lt(v___x_3398_, v_product_3366_);
if (v___x_3399_ == 0)
{
v___y_3380_ = v___x_3378_;
goto v___jp_3379_;
}
else
{
uint64_t v___x_3400_; 
v___x_3400_ = 1ULL;
v___y_3380_ = v___x_3400_;
goto v___jp_3379_;
}
}
}
else
{
uint64_t v_quotient_3401_; uint64_t v___x_3402_; uint64_t v___x_3403_; uint64_t v___x_3404_; uint64_t v_remainder_3405_; uint64_t v___x_3406_; uint64_t v_half_3407_; uint8_t v___x_3408_; 
v_quotient_3401_ = lean_uint64_shift_right(v_product_3366_, v___x_3393_);
v___x_3402_ = 1ULL;
v___x_3403_ = lean_uint64_shift_left(v___x_3402_, v___x_3393_);
v___x_3404_ = lean_uint64_sub(v___x_3403_, v___x_3402_);
v_remainder_3405_ = lean_uint64_land(v_product_3366_, v___x_3404_);
v___x_3406_ = lean_uint64_sub(v___x_3393_, v___x_3402_);
v_half_3407_ = lean_uint64_shift_left(v___x_3402_, v___x_3406_);
v___x_3408_ = lean_uint64_dec_lt(v_remainder_3405_, v_half_3407_);
if (v___x_3408_ == 0)
{
uint8_t v___x_3409_; 
v___x_3409_ = lean_uint64_dec_lt(v_half_3407_, v_remainder_3405_);
if (v___x_3409_ == 0)
{
uint64_t v___x_3410_; uint8_t v___x_3411_; 
v___x_3410_ = lean_uint64_land(v_quotient_3401_, v___x_3402_);
v___x_3411_ = lean_uint64_dec_eq(v___x_3410_, v___x_3378_);
if (v___x_3411_ == 0)
{
uint64_t v___x_3412_; 
v___x_3412_ = lean_uint64_add(v_quotient_3401_, v___x_3402_);
v___y_3380_ = v___x_3412_;
goto v___jp_3379_;
}
else
{
v___y_3380_ = v_quotient_3401_;
goto v___jp_3379_;
}
}
else
{
uint64_t v___x_3413_; 
v___x_3413_ = lean_uint64_add(v_quotient_3401_, v___x_3402_);
v___y_3380_ = v___x_3413_;
goto v___jp_3379_;
}
}
else
{
v___y_3380_ = v_quotient_3401_;
goto v___jp_3379_;
}
}
}
else
{
v___y_3380_ = v_product_3366_;
goto v___jp_3379_;
}
}
else
{
if (v_sign_3365_ == 0)
{
uint32_t v___x_3414_; 
v___x_3414_ = 0;
return v___x_3414_;
}
else
{
uint32_t v___x_3415_; 
v___x_3415_ = 2147483648;
return v___x_3415_;
}
}
v___jp_3368_:
{
uint32_t v___x_3370_; uint32_t v___x_3371_; 
v___x_3370_ = 8388608;
v___x_3371_ = lean_uint32_lor(v___y_3369_, v___x_3370_);
return v___x_3371_;
}
v___jp_3372_:
{
uint32_t v___x_3375_; uint32_t v___x_3376_; uint32_t v___x_3377_; 
v___x_3375_ = 8388607;
v___x_3376_ = lean_uint32_land(v___y_3373_, v___x_3375_);
v___x_3377_ = lean_uint32_lor(v___y_3374_, v___x_3376_);
return v___x_3377_;
}
v___jp_3379_:
{
uint8_t v___x_3381_; 
v___x_3381_ = lean_uint64_dec_eq(v___y_3380_, v___x_3378_);
if (v___x_3381_ == 0)
{
uint64_t v___x_3382_; uint8_t v___x_3383_; 
v___x_3382_ = 8388608ULL;
v___x_3383_ = lean_uint64_dec_eq(v___y_3380_, v___x_3382_);
if (v___x_3383_ == 0)
{
uint32_t v___x_3384_; 
v___x_3384_ = lean_uint64_to_uint32(v___y_3380_);
if (v_sign_3365_ == 0)
{
uint32_t v___x_3385_; 
v___x_3385_ = 0;
v___y_3373_ = v___x_3384_;
v___y_3374_ = v___x_3385_;
goto v___jp_3372_;
}
else
{
uint32_t v___x_3386_; 
v___x_3386_ = 2147483648;
v___y_3373_ = v___x_3384_;
v___y_3374_ = v___x_3386_;
goto v___jp_3372_;
}
}
else
{
if (v_sign_3365_ == 0)
{
uint32_t v___x_3387_; 
v___x_3387_ = 0;
v___y_3369_ = v___x_3387_;
goto v___jp_3368_;
}
else
{
uint32_t v___x_3388_; 
v___x_3388_ = 2147483648;
v___y_3369_ = v___x_3388_;
goto v___jp_3368_;
}
}
}
else
{
if (v_sign_3365_ == 0)
{
uint32_t v___x_3389_; 
v___x_3389_ = 0;
return v___x_3389_;
}
else
{
uint32_t v___x_3390_; 
v___x_3390_ = 2147483648;
return v___x_3390_;
}
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_LowScale_roundLow___boxed(lean_object* v_sign_3416_, lean_object* v_product_3417_, lean_object* v_scale_3418_){
_start:
{
uint8_t v_sign_boxed_3419_; uint64_t v_product_boxed_3420_; uint64_t v_scale_boxed_3421_; uint32_t v_res_3422_; lean_object* v_r_3423_; 
v_sign_boxed_3419_ = lean_unbox(v_sign_3416_);
v_product_boxed_3420_ = lean_unbox_uint64(v_product_3417_);
lean_dec_ref(v_product_3417_);
v_scale_boxed_3421_ = lean_unbox_uint64(v_scale_3418_);
lean_dec_ref(v_scale_3418_);
v_res_3422_ = lp_competition_Submission_LowScale_roundLow(v_sign_boxed_3419_, v_product_boxed_3420_, v_scale_boxed_3421_);
v_r_3423_ = lean_box_uint32(v_res_3422_);
return v_r_3423_;
}
}
LEAN_EXPORT uint32_t lp_competition_Submission_LowScale_roundSelect(uint8_t v_sign_3424_, uint64_t v_product_3425_, uint64_t v_scale_3426_){
_start:
{
uint32_t v___y_3428_; uint32_t v___y_3432_; uint32_t v___y_3433_; uint32_t v___y_3438_; uint32_t v___y_3442_; uint32_t v___y_3443_; uint64_t v___y_3448_; uint64_t v___y_3449_; uint32_t v___y_3461_; uint32_t v___y_3462_; uint32_t v___y_3463_; uint32_t v___y_3473_; uint32_t v___y_3474_; uint64_t v___y_3478_; uint64_t v___y_3479_; uint64_t v___y_3480_; uint64_t v___y_3490_; uint8_t v___y_3491_; uint64_t v___y_3492_; uint64_t v___y_3493_; uint64_t v___y_3500_; uint64_t v___y_3501_; uint64_t v___y_3502_; uint64_t v___y_3508_; uint64_t v___y_3509_; uint64_t v___y_3564_; uint64_t v___y_3565_; uint64_t v___y_3566_; uint64_t v___y_3572_; uint64_t v___y_3573_; uint64_t v___y_3574_; uint64_t v___y_3575_; uint64_t v___y_3576_; uint64_t v___y_3581_; uint64_t v___y_3582_; uint64_t v___y_3583_; uint64_t v___y_3588_; uint64_t v___y_3589_; uint64_t v___y_3590_; uint64_t v___y_3591_; uint64_t v___y_3592_; uint64_t v___y_3597_; uint64_t v___y_3598_; uint64_t v___y_3599_; uint64_t v___y_3604_; uint64_t v___y_3605_; uint64_t v___y_3606_; uint64_t v___y_3607_; uint64_t v___y_3608_; uint64_t v___y_3613_; uint64_t v___y_3614_; uint64_t v___y_3615_; uint64_t v___y_3620_; uint64_t v___y_3621_; uint64_t v___y_3622_; uint64_t v___y_3623_; uint64_t v___y_3624_; uint64_t v___y_3629_; uint64_t v___y_3630_; uint64_t v___y_3631_; uint64_t v___y_3636_; uint64_t v___y_3637_; uint64_t v___y_3638_; uint64_t v___x_3649_; uint8_t v___x_3650_; 
v___x_3649_ = 281474976710656ULL;
v___x_3650_ = lean_uint64_dec_lt(v_product_3425_, v___x_3649_);
if (v___x_3650_ == 0)
{
goto v___jp_3641_;
}
else
{
uint64_t v___x_3651_; uint8_t v___x_3652_; 
v___x_3651_ = 123ULL;
v___x_3652_ = lean_uint64_dec_le(v_scale_3426_, v___x_3651_);
if (v___x_3652_ == 0)
{
goto v___jp_3641_;
}
else
{
uint64_t v___x_3653_; uint64_t v___y_3655_; uint8_t v___x_3666_; 
v___x_3653_ = 0ULL;
v___x_3666_ = lean_uint64_dec_eq(v_product_3425_, v___x_3653_);
if (v___x_3666_ == 0)
{
uint64_t v___x_3667_; uint64_t v___x_3668_; uint8_t v___x_3669_; 
v___x_3667_ = 149ULL;
v___x_3668_ = lean_uint64_sub(v___x_3667_, v_scale_3426_);
v___x_3669_ = lean_uint64_dec_eq(v___x_3668_, v___x_3653_);
if (v___x_3669_ == 0)
{
uint64_t v___x_3670_; uint8_t v___x_3671_; 
v___x_3670_ = 64ULL;
v___x_3671_ = lean_uint64_dec_lt(v___x_3668_, v___x_3670_);
if (v___x_3671_ == 0)
{
uint8_t v___x_3672_; 
v___x_3672_ = lean_uint64_dec_eq(v___x_3668_, v___x_3670_);
if (v___x_3672_ == 0)
{
v___y_3655_ = v___x_3653_;
goto v___jp_3654_;
}
else
{
uint64_t v___x_3673_; uint8_t v___x_3674_; 
v___x_3673_ = 9223372036854775808ULL;
v___x_3674_ = lean_uint64_dec_lt(v___x_3673_, v_product_3425_);
if (v___x_3674_ == 0)
{
v___y_3655_ = v___x_3653_;
goto v___jp_3654_;
}
else
{
uint64_t v___x_3675_; 
v___x_3675_ = 1ULL;
v___y_3655_ = v___x_3675_;
goto v___jp_3654_;
}
}
}
else
{
uint64_t v_quotient_3676_; uint64_t v___x_3677_; uint64_t v___x_3678_; uint64_t v___x_3679_; uint64_t v_remainder_3680_; uint64_t v___x_3681_; uint64_t v_half_3682_; uint8_t v___x_3683_; 
v_quotient_3676_ = lean_uint64_shift_right(v_product_3425_, v___x_3668_);
v___x_3677_ = 1ULL;
v___x_3678_ = lean_uint64_shift_left(v___x_3677_, v___x_3668_);
v___x_3679_ = lean_uint64_sub(v___x_3678_, v___x_3677_);
v_remainder_3680_ = lean_uint64_land(v_product_3425_, v___x_3679_);
v___x_3681_ = lean_uint64_sub(v___x_3668_, v___x_3677_);
v_half_3682_ = lean_uint64_shift_left(v___x_3677_, v___x_3681_);
v___x_3683_ = lean_uint64_dec_lt(v_remainder_3680_, v_half_3682_);
if (v___x_3683_ == 0)
{
uint8_t v___x_3684_; 
v___x_3684_ = lean_uint64_dec_lt(v_half_3682_, v_remainder_3680_);
if (v___x_3684_ == 0)
{
uint64_t v___x_3685_; uint8_t v___x_3686_; 
v___x_3685_ = lean_uint64_land(v_quotient_3676_, v___x_3677_);
v___x_3686_ = lean_uint64_dec_eq(v___x_3685_, v___x_3653_);
if (v___x_3686_ == 0)
{
uint64_t v___x_3687_; 
v___x_3687_ = lean_uint64_add(v_quotient_3676_, v___x_3677_);
v___y_3655_ = v___x_3687_;
goto v___jp_3654_;
}
else
{
v___y_3655_ = v_quotient_3676_;
goto v___jp_3654_;
}
}
else
{
uint64_t v___x_3688_; 
v___x_3688_ = lean_uint64_add(v_quotient_3676_, v___x_3677_);
v___y_3655_ = v___x_3688_;
goto v___jp_3654_;
}
}
else
{
v___y_3655_ = v_quotient_3676_;
goto v___jp_3654_;
}
}
}
else
{
v___y_3655_ = v_product_3425_;
goto v___jp_3654_;
}
}
else
{
if (v_sign_3424_ == 0)
{
uint32_t v___x_3689_; 
v___x_3689_ = 0;
return v___x_3689_;
}
else
{
uint32_t v___x_3690_; 
v___x_3690_ = 2147483648;
return v___x_3690_;
}
}
v___jp_3654_:
{
uint8_t v___x_3656_; 
v___x_3656_ = lean_uint64_dec_eq(v___y_3655_, v___x_3653_);
if (v___x_3656_ == 0)
{
uint64_t v___x_3657_; uint8_t v___x_3658_; 
v___x_3657_ = 8388608ULL;
v___x_3658_ = lean_uint64_dec_eq(v___y_3655_, v___x_3657_);
if (v___x_3658_ == 0)
{
uint32_t v___x_3659_; 
v___x_3659_ = lean_uint64_to_uint32(v___y_3655_);
if (v_sign_3424_ == 0)
{
uint32_t v___x_3660_; 
v___x_3660_ = 0;
v___y_3432_ = v___x_3659_;
v___y_3433_ = v___x_3660_;
goto v___jp_3431_;
}
else
{
uint32_t v___x_3661_; 
v___x_3661_ = 2147483648;
v___y_3432_ = v___x_3659_;
v___y_3433_ = v___x_3661_;
goto v___jp_3431_;
}
}
else
{
if (v_sign_3424_ == 0)
{
uint32_t v___x_3662_; 
v___x_3662_ = 0;
v___y_3428_ = v___x_3662_;
goto v___jp_3427_;
}
else
{
uint32_t v___x_3663_; 
v___x_3663_ = 2147483648;
v___y_3428_ = v___x_3663_;
goto v___jp_3427_;
}
}
}
else
{
if (v_sign_3424_ == 0)
{
uint32_t v___x_3664_; 
v___x_3664_ = 0;
return v___x_3664_;
}
else
{
uint32_t v___x_3665_; 
v___x_3665_ = 2147483648;
return v___x_3665_;
}
}
}
}
}
v___jp_3427_:
{
uint32_t v___x_3429_; uint32_t v___x_3430_; 
v___x_3429_ = 8388608;
v___x_3430_ = lean_uint32_lor(v___y_3428_, v___x_3429_);
return v___x_3430_;
}
v___jp_3431_:
{
uint32_t v___x_3434_; uint32_t v___x_3435_; uint32_t v___x_3436_; 
v___x_3434_ = 8388607;
v___x_3435_ = lean_uint32_land(v___y_3432_, v___x_3434_);
v___x_3436_ = lean_uint32_lor(v___y_3433_, v___x_3435_);
return v___x_3436_;
}
v___jp_3437_:
{
uint32_t v___x_3439_; uint32_t v___x_3440_; 
v___x_3439_ = 8388608;
v___x_3440_ = lean_uint32_lor(v___y_3438_, v___x_3439_);
return v___x_3440_;
}
v___jp_3441_:
{
uint32_t v___x_3444_; uint32_t v___x_3445_; uint32_t v___x_3446_; 
v___x_3444_ = 8388607;
v___x_3445_ = lean_uint32_land(v___y_3442_, v___x_3444_);
v___x_3446_ = lean_uint32_lor(v___y_3443_, v___x_3445_);
return v___x_3446_;
}
v___jp_3447_:
{
uint8_t v___x_3450_; 
v___x_3450_ = lean_uint64_dec_eq(v___y_3449_, v___y_3448_);
if (v___x_3450_ == 0)
{
uint64_t v___x_3451_; uint8_t v___x_3452_; 
v___x_3451_ = 8388608ULL;
v___x_3452_ = lean_uint64_dec_eq(v___y_3449_, v___x_3451_);
if (v___x_3452_ == 0)
{
uint32_t v___x_3453_; 
v___x_3453_ = lean_uint64_to_uint32(v___y_3449_);
if (v_sign_3424_ == 0)
{
uint32_t v___x_3454_; 
v___x_3454_ = 0;
v___y_3442_ = v___x_3453_;
v___y_3443_ = v___x_3454_;
goto v___jp_3441_;
}
else
{
uint32_t v___x_3455_; 
v___x_3455_ = 2147483648;
v___y_3442_ = v___x_3453_;
v___y_3443_ = v___x_3455_;
goto v___jp_3441_;
}
}
else
{
if (v_sign_3424_ == 0)
{
uint32_t v___x_3456_; 
v___x_3456_ = 0;
v___y_3438_ = v___x_3456_;
goto v___jp_3437_;
}
else
{
uint32_t v___x_3457_; 
v___x_3457_ = 2147483648;
v___y_3438_ = v___x_3457_;
goto v___jp_3437_;
}
}
}
else
{
if (v_sign_3424_ == 0)
{
uint32_t v___x_3458_; 
v___x_3458_ = 0;
return v___x_3458_;
}
else
{
uint32_t v___x_3459_; 
v___x_3459_ = 2147483648;
return v___x_3459_;
}
}
}
v___jp_3460_:
{
uint32_t v___x_3464_; uint32_t v___x_3465_; uint32_t v___x_3466_; uint32_t v___x_3467_; uint32_t v___x_3468_; uint32_t v___x_3469_; uint32_t v___x_3470_; uint32_t v___x_3471_; 
v___x_3464_ = 255;
v___x_3465_ = lean_uint32_land(v___y_3462_, v___x_3464_);
v___x_3466_ = 23;
v___x_3467_ = lean_uint32_shift_left(v___x_3465_, v___x_3466_);
v___x_3468_ = lean_uint32_lor(v___y_3463_, v___x_3467_);
v___x_3469_ = 8388607;
v___x_3470_ = lean_uint32_land(v___y_3461_, v___x_3469_);
v___x_3471_ = lean_uint32_lor(v___x_3468_, v___x_3470_);
return v___x_3471_;
}
v___jp_3472_:
{
if (v_sign_3424_ == 0)
{
uint32_t v___x_3475_; 
v___x_3475_ = 0;
v___y_3461_ = v___y_3474_;
v___y_3462_ = v___y_3473_;
v___y_3463_ = v___x_3475_;
goto v___jp_3460_;
}
else
{
uint32_t v___x_3476_; 
v___x_3476_ = 2147483648;
v___y_3461_ = v___y_3474_;
v___y_3462_ = v___y_3473_;
v___y_3463_ = v___x_3476_;
goto v___jp_3460_;
}
}
v___jp_3477_:
{
uint64_t v___x_3481_; uint64_t v_encodedExponent_3482_; uint32_t v___x_3483_; uint64_t v___x_3484_; uint8_t v___x_3485_; 
v___x_3481_ = 171ULL;
v_encodedExponent_3482_ = lean_uint64_sub(v___y_3478_, v___x_3481_);
v___x_3483_ = lean_uint64_to_uint32(v_encodedExponent_3482_);
v___x_3484_ = 8388608ULL;
v___x_3485_ = lean_uint64_dec_lt(v___y_3480_, v___x_3484_);
if (v___x_3485_ == 0)
{
uint64_t v___x_3486_; uint32_t v___x_3487_; 
v___x_3486_ = lean_uint64_sub(v___y_3480_, v___x_3484_);
v___x_3487_ = lean_uint64_to_uint32(v___x_3486_);
v___y_3473_ = v___x_3483_;
v___y_3474_ = v___x_3487_;
goto v___jp_3472_;
}
else
{
uint32_t v___x_3488_; 
v___x_3488_ = lean_uint64_to_uint32(v___y_3479_);
v___y_3473_ = v___x_3483_;
v___y_3474_ = v___x_3488_;
goto v___jp_3472_;
}
}
v___jp_3489_:
{
uint64_t v___x_3494_; uint8_t v___x_3495_; 
v___x_3494_ = 425ULL;
v___x_3495_ = lean_uint64_dec_lt(v___x_3494_, v___y_3493_);
if (v___x_3495_ == 0)
{
if (v___y_3491_ == 0)
{
v___y_3478_ = v___y_3493_;
v___y_3479_ = v___y_3492_;
v___y_3480_ = v___y_3490_;
goto v___jp_3477_;
}
else
{
uint64_t v___x_3496_; 
v___x_3496_ = 8388608ULL;
v___y_3478_ = v___y_3493_;
v___y_3479_ = v___y_3492_;
v___y_3480_ = v___x_3496_;
goto v___jp_3477_;
}
}
else
{
if (v_sign_3424_ == 0)
{
uint32_t v___x_3497_; 
v___x_3497_ = 2139095040;
return v___x_3497_;
}
else
{
uint32_t v___x_3498_; 
v___x_3498_ = 4286578688;
return v___x_3498_;
}
}
}
v___jp_3499_:
{
uint64_t v___x_3503_; uint8_t v_carry_3504_; 
v___x_3503_ = 16777216ULL;
v_carry_3504_ = lean_uint64_dec_eq(v___y_3502_, v___x_3503_);
if (v_carry_3504_ == 0)
{
v___y_3490_ = v___y_3502_;
v___y_3491_ = v_carry_3504_;
v___y_3492_ = v___y_3501_;
v___y_3493_ = v___y_3500_;
goto v___jp_3489_;
}
else
{
uint64_t v___x_3505_; uint64_t v___x_3506_; 
v___x_3505_ = 1ULL;
v___x_3506_ = lean_uint64_add(v___y_3500_, v___x_3505_);
v___y_3490_ = v___y_3502_;
v___y_3491_ = v_carry_3504_;
v___y_3492_ = v___y_3501_;
v___y_3493_ = v___x_3506_;
goto v___jp_3489_;
}
}
v___jp_3507_:
{
uint64_t v_position_3510_; uint64_t v___x_3511_; uint8_t v___x_3512_; 
v_position_3510_ = lean_uint64_add(v___y_3509_, v_scale_3426_);
v___x_3511_ = 172ULL;
v___x_3512_ = lean_uint64_dec_lt(v_position_3510_, v___x_3511_);
if (v___x_3512_ == 0)
{
uint64_t v___x_3513_; uint8_t v___x_3514_; 
v___x_3513_ = 23ULL;
v___x_3514_ = lean_uint64_dec_lt(v___y_3509_, v___x_3513_);
if (v___x_3514_ == 0)
{
uint64_t v___x_3515_; uint8_t v___x_3516_; 
v___x_3515_ = lean_uint64_sub(v___y_3509_, v___x_3513_);
v___x_3516_ = lean_uint64_dec_eq(v___x_3515_, v___y_3508_);
if (v___x_3516_ == 0)
{
uint64_t v___x_3517_; uint8_t v___x_3518_; 
v___x_3517_ = 64ULL;
v___x_3518_ = lean_uint64_dec_lt(v___x_3515_, v___x_3517_);
if (v___x_3518_ == 0)
{
uint8_t v___x_3519_; 
v___x_3519_ = lean_uint64_dec_eq(v___x_3515_, v___x_3517_);
if (v___x_3519_ == 0)
{
v___y_3500_ = v_position_3510_;
v___y_3501_ = v___y_3508_;
v___y_3502_ = v___y_3508_;
goto v___jp_3499_;
}
else
{
uint64_t v___x_3520_; uint8_t v___x_3521_; 
v___x_3520_ = 9223372036854775808ULL;
v___x_3521_ = lean_uint64_dec_lt(v___x_3520_, v_product_3425_);
if (v___x_3521_ == 0)
{
v___y_3500_ = v_position_3510_;
v___y_3501_ = v___y_3508_;
v___y_3502_ = v___y_3508_;
goto v___jp_3499_;
}
else
{
uint64_t v___x_3522_; 
v___x_3522_ = 1ULL;
v___y_3500_ = v_position_3510_;
v___y_3501_ = v___y_3508_;
v___y_3502_ = v___x_3522_;
goto v___jp_3499_;
}
}
}
else
{
uint64_t v_quotient_3523_; uint64_t v___x_3524_; uint64_t v___x_3525_; uint64_t v___x_3526_; uint64_t v_remainder_3527_; uint64_t v___x_3528_; uint64_t v_half_3529_; uint8_t v___x_3530_; 
v_quotient_3523_ = lean_uint64_shift_right(v_product_3425_, v___x_3515_);
v___x_3524_ = 1ULL;
v___x_3525_ = lean_uint64_shift_left(v___x_3524_, v___x_3515_);
v___x_3526_ = lean_uint64_sub(v___x_3525_, v___x_3524_);
v_remainder_3527_ = lean_uint64_land(v_product_3425_, v___x_3526_);
v___x_3528_ = lean_uint64_sub(v___x_3515_, v___x_3524_);
v_half_3529_ = lean_uint64_shift_left(v___x_3524_, v___x_3528_);
v___x_3530_ = lean_uint64_dec_lt(v_remainder_3527_, v_half_3529_);
if (v___x_3530_ == 0)
{
uint8_t v___x_3531_; 
v___x_3531_ = lean_uint64_dec_lt(v_half_3529_, v_remainder_3527_);
if (v___x_3531_ == 0)
{
uint64_t v___x_3532_; uint8_t v___x_3533_; 
v___x_3532_ = lean_uint64_land(v_quotient_3523_, v___x_3524_);
v___x_3533_ = lean_uint64_dec_eq(v___x_3532_, v___y_3508_);
if (v___x_3533_ == 0)
{
uint64_t v___x_3534_; 
v___x_3534_ = lean_uint64_add(v_quotient_3523_, v___x_3524_);
v___y_3500_ = v_position_3510_;
v___y_3501_ = v___y_3508_;
v___y_3502_ = v___x_3534_;
goto v___jp_3499_;
}
else
{
v___y_3500_ = v_position_3510_;
v___y_3501_ = v___y_3508_;
v___y_3502_ = v_quotient_3523_;
goto v___jp_3499_;
}
}
else
{
uint64_t v___x_3535_; 
v___x_3535_ = lean_uint64_add(v_quotient_3523_, v___x_3524_);
v___y_3500_ = v_position_3510_;
v___y_3501_ = v___y_3508_;
v___y_3502_ = v___x_3535_;
goto v___jp_3499_;
}
}
else
{
v___y_3500_ = v_position_3510_;
v___y_3501_ = v___y_3508_;
v___y_3502_ = v_quotient_3523_;
goto v___jp_3499_;
}
}
}
else
{
v___y_3500_ = v_position_3510_;
v___y_3501_ = v___y_3508_;
v___y_3502_ = v_product_3425_;
goto v___jp_3499_;
}
}
else
{
uint64_t v___x_3536_; uint64_t v___x_3537_; 
v___x_3536_ = lean_uint64_sub(v___x_3513_, v___y_3509_);
v___x_3537_ = lean_uint64_shift_left(v_product_3425_, v___x_3536_);
v___y_3500_ = v_position_3510_;
v___y_3501_ = v___y_3508_;
v___y_3502_ = v___x_3537_;
goto v___jp_3499_;
}
}
else
{
uint64_t v___x_3538_; uint8_t v___x_3539_; 
v___x_3538_ = 149ULL;
v___x_3539_ = lean_uint64_dec_lt(v_scale_3426_, v___x_3538_);
if (v___x_3539_ == 0)
{
uint64_t v___x_3540_; uint64_t v___x_3541_; 
v___x_3540_ = lean_uint64_sub(v_scale_3426_, v___x_3538_);
v___x_3541_ = lean_uint64_shift_left(v_product_3425_, v___x_3540_);
v___y_3448_ = v___y_3508_;
v___y_3449_ = v___x_3541_;
goto v___jp_3447_;
}
else
{
uint64_t v___x_3542_; uint8_t v___x_3543_; 
v___x_3542_ = lean_uint64_sub(v___x_3538_, v_scale_3426_);
v___x_3543_ = lean_uint64_dec_eq(v___x_3542_, v___y_3508_);
if (v___x_3543_ == 0)
{
uint64_t v___x_3544_; uint8_t v___x_3545_; 
v___x_3544_ = 64ULL;
v___x_3545_ = lean_uint64_dec_lt(v___x_3542_, v___x_3544_);
if (v___x_3545_ == 0)
{
uint8_t v___x_3546_; 
v___x_3546_ = lean_uint64_dec_eq(v___x_3542_, v___x_3544_);
if (v___x_3546_ == 0)
{
v___y_3448_ = v___y_3508_;
v___y_3449_ = v___y_3508_;
goto v___jp_3447_;
}
else
{
uint64_t v___x_3547_; uint8_t v___x_3548_; 
v___x_3547_ = 9223372036854775808ULL;
v___x_3548_ = lean_uint64_dec_lt(v___x_3547_, v_product_3425_);
if (v___x_3548_ == 0)
{
v___y_3448_ = v___y_3508_;
v___y_3449_ = v___y_3508_;
goto v___jp_3447_;
}
else
{
uint64_t v___x_3549_; 
v___x_3549_ = 1ULL;
v___y_3448_ = v___y_3508_;
v___y_3449_ = v___x_3549_;
goto v___jp_3447_;
}
}
}
else
{
uint64_t v_quotient_3550_; uint64_t v___x_3551_; uint64_t v___x_3552_; uint64_t v___x_3553_; uint64_t v_remainder_3554_; uint64_t v___x_3555_; uint64_t v_half_3556_; uint8_t v___x_3557_; 
v_quotient_3550_ = lean_uint64_shift_right(v_product_3425_, v___x_3542_);
v___x_3551_ = 1ULL;
v___x_3552_ = lean_uint64_shift_left(v___x_3551_, v___x_3542_);
v___x_3553_ = lean_uint64_sub(v___x_3552_, v___x_3551_);
v_remainder_3554_ = lean_uint64_land(v_product_3425_, v___x_3553_);
v___x_3555_ = lean_uint64_sub(v___x_3542_, v___x_3551_);
v_half_3556_ = lean_uint64_shift_left(v___x_3551_, v___x_3555_);
v___x_3557_ = lean_uint64_dec_lt(v_remainder_3554_, v_half_3556_);
if (v___x_3557_ == 0)
{
uint8_t v___x_3558_; 
v___x_3558_ = lean_uint64_dec_lt(v_half_3556_, v_remainder_3554_);
if (v___x_3558_ == 0)
{
uint64_t v___x_3559_; uint8_t v___x_3560_; 
v___x_3559_ = lean_uint64_land(v_quotient_3550_, v___x_3551_);
v___x_3560_ = lean_uint64_dec_eq(v___x_3559_, v___y_3508_);
if (v___x_3560_ == 0)
{
uint64_t v___x_3561_; 
v___x_3561_ = lean_uint64_add(v_quotient_3550_, v___x_3551_);
v___y_3448_ = v___y_3508_;
v___y_3449_ = v___x_3561_;
goto v___jp_3447_;
}
else
{
v___y_3448_ = v___y_3508_;
v___y_3449_ = v_quotient_3550_;
goto v___jp_3447_;
}
}
else
{
uint64_t v___x_3562_; 
v___x_3562_ = lean_uint64_add(v_quotient_3550_, v___x_3551_);
v___y_3448_ = v___y_3508_;
v___y_3449_ = v___x_3562_;
goto v___jp_3447_;
}
}
else
{
v___y_3448_ = v___y_3508_;
v___y_3449_ = v_quotient_3550_;
goto v___jp_3447_;
}
}
}
else
{
v___y_3448_ = v___y_3508_;
v___y_3449_ = v_product_3425_;
goto v___jp_3447_;
}
}
}
}
v___jp_3563_:
{
uint64_t v___x_3567_; uint64_t v___x_3568_; uint8_t v___x_3569_; 
v___x_3567_ = 1ULL;
v___x_3568_ = lean_uint64_shift_right(v___y_3564_, v___x_3567_);
v___x_3569_ = lean_uint64_dec_eq(v___x_3568_, v___y_3565_);
if (v___x_3569_ == 0)
{
uint64_t v___x_3570_; 
v___x_3570_ = lean_uint64_add(v___y_3566_, v___x_3567_);
v___y_3508_ = v___y_3565_;
v___y_3509_ = v___x_3570_;
goto v___jp_3507_;
}
else
{
v___y_3508_ = v___y_3565_;
v___y_3509_ = v___y_3566_;
goto v___jp_3507_;
}
}
v___jp_3571_:
{
uint64_t v___x_3577_; uint8_t v___x_3578_; 
v___x_3577_ = lean_uint64_shift_right(v___y_3575_, v___y_3572_);
v___x_3578_ = lean_uint64_dec_eq(v___x_3577_, v___y_3574_);
if (v___x_3578_ == 0)
{
uint64_t v___x_3579_; 
v___x_3579_ = lean_uint64_add(v___y_3573_, v___y_3572_);
v___y_3564_ = v___y_3576_;
v___y_3565_ = v___y_3574_;
v___y_3566_ = v___x_3579_;
goto v___jp_3563_;
}
else
{
v___y_3564_ = v___y_3576_;
v___y_3565_ = v___y_3574_;
v___y_3566_ = v___y_3573_;
goto v___jp_3563_;
}
}
v___jp_3580_:
{
uint64_t v___x_3584_; uint64_t v___x_3585_; uint8_t v___x_3586_; 
v___x_3584_ = 2ULL;
v___x_3585_ = lean_uint64_shift_right(v___y_3582_, v___x_3584_);
v___x_3586_ = lean_uint64_dec_eq(v___x_3585_, v___y_3581_);
if (v___x_3586_ == 0)
{
v___y_3572_ = v___x_3584_;
v___y_3573_ = v___y_3583_;
v___y_3574_ = v___y_3581_;
v___y_3575_ = v___y_3582_;
v___y_3576_ = v___x_3585_;
goto v___jp_3571_;
}
else
{
v___y_3572_ = v___x_3584_;
v___y_3573_ = v___y_3583_;
v___y_3574_ = v___y_3581_;
v___y_3575_ = v___y_3582_;
v___y_3576_ = v___y_3582_;
goto v___jp_3571_;
}
}
v___jp_3587_:
{
uint64_t v___x_3593_; uint8_t v___x_3594_; 
v___x_3593_ = lean_uint64_shift_right(v___y_3590_, v___y_3589_);
v___x_3594_ = lean_uint64_dec_eq(v___x_3593_, v___y_3591_);
if (v___x_3594_ == 0)
{
uint64_t v___x_3595_; 
v___x_3595_ = lean_uint64_add(v___y_3588_, v___y_3589_);
v___y_3581_ = v___y_3591_;
v___y_3582_ = v___y_3592_;
v___y_3583_ = v___x_3595_;
goto v___jp_3580_;
}
else
{
v___y_3581_ = v___y_3591_;
v___y_3582_ = v___y_3592_;
v___y_3583_ = v___y_3588_;
goto v___jp_3580_;
}
}
v___jp_3596_:
{
uint64_t v___x_3600_; uint64_t v___x_3601_; uint8_t v___x_3602_; 
v___x_3600_ = 4ULL;
v___x_3601_ = lean_uint64_shift_right(v___y_3597_, v___x_3600_);
v___x_3602_ = lean_uint64_dec_eq(v___x_3601_, v___y_3598_);
if (v___x_3602_ == 0)
{
v___y_3588_ = v___y_3599_;
v___y_3589_ = v___x_3600_;
v___y_3590_ = v___y_3597_;
v___y_3591_ = v___y_3598_;
v___y_3592_ = v___x_3601_;
goto v___jp_3587_;
}
else
{
v___y_3588_ = v___y_3599_;
v___y_3589_ = v___x_3600_;
v___y_3590_ = v___y_3597_;
v___y_3591_ = v___y_3598_;
v___y_3592_ = v___y_3597_;
goto v___jp_3587_;
}
}
v___jp_3603_:
{
uint64_t v___x_3609_; uint8_t v___x_3610_; 
v___x_3609_ = lean_uint64_shift_right(v___y_3607_, v___y_3604_);
v___x_3610_ = lean_uint64_dec_eq(v___x_3609_, v___y_3605_);
if (v___x_3610_ == 0)
{
uint64_t v___x_3611_; 
v___x_3611_ = lean_uint64_add(v___y_3606_, v___y_3604_);
v___y_3597_ = v___y_3608_;
v___y_3598_ = v___y_3605_;
v___y_3599_ = v___x_3611_;
goto v___jp_3596_;
}
else
{
v___y_3597_ = v___y_3608_;
v___y_3598_ = v___y_3605_;
v___y_3599_ = v___y_3606_;
goto v___jp_3596_;
}
}
v___jp_3612_:
{
uint64_t v___x_3616_; uint64_t v___x_3617_; uint8_t v___x_3618_; 
v___x_3616_ = 8ULL;
v___x_3617_ = lean_uint64_shift_right(v___y_3614_, v___x_3616_);
v___x_3618_ = lean_uint64_dec_eq(v___x_3617_, v___y_3613_);
if (v___x_3618_ == 0)
{
v___y_3604_ = v___x_3616_;
v___y_3605_ = v___y_3613_;
v___y_3606_ = v___y_3615_;
v___y_3607_ = v___y_3614_;
v___y_3608_ = v___x_3617_;
goto v___jp_3603_;
}
else
{
v___y_3604_ = v___x_3616_;
v___y_3605_ = v___y_3613_;
v___y_3606_ = v___y_3615_;
v___y_3607_ = v___y_3614_;
v___y_3608_ = v___y_3614_;
goto v___jp_3603_;
}
}
v___jp_3619_:
{
uint64_t v___x_3625_; uint8_t v___x_3626_; 
v___x_3625_ = lean_uint64_shift_right(v___y_3620_, v___y_3622_);
v___x_3626_ = lean_uint64_dec_eq(v___x_3625_, v___y_3623_);
if (v___x_3626_ == 0)
{
uint64_t v___x_3627_; 
v___x_3627_ = lean_uint64_add(v___y_3621_, v___y_3622_);
v___y_3613_ = v___y_3623_;
v___y_3614_ = v___y_3624_;
v___y_3615_ = v___x_3627_;
goto v___jp_3612_;
}
else
{
v___y_3613_ = v___y_3623_;
v___y_3614_ = v___y_3624_;
v___y_3615_ = v___y_3621_;
goto v___jp_3612_;
}
}
v___jp_3628_:
{
uint64_t v___x_3632_; uint64_t v___x_3633_; uint8_t v___x_3634_; 
v___x_3632_ = 16ULL;
v___x_3633_ = lean_uint64_shift_right(v___y_3629_, v___x_3632_);
v___x_3634_ = lean_uint64_dec_eq(v___x_3633_, v___y_3630_);
if (v___x_3634_ == 0)
{
v___y_3620_ = v___y_3629_;
v___y_3621_ = v___y_3631_;
v___y_3622_ = v___x_3632_;
v___y_3623_ = v___y_3630_;
v___y_3624_ = v___x_3633_;
goto v___jp_3619_;
}
else
{
v___y_3620_ = v___y_3629_;
v___y_3621_ = v___y_3631_;
v___y_3622_ = v___x_3632_;
v___y_3623_ = v___y_3630_;
v___y_3624_ = v___y_3629_;
goto v___jp_3619_;
}
}
v___jp_3635_:
{
uint64_t v___x_3639_; uint8_t v___x_3640_; 
v___x_3639_ = lean_uint64_shift_right(v_product_3425_, v___y_3637_);
v___x_3640_ = lean_uint64_dec_eq(v___x_3639_, v___y_3636_);
if (v___x_3640_ == 0)
{
v___y_3629_ = v___y_3638_;
v___y_3630_ = v___y_3636_;
v___y_3631_ = v___y_3637_;
goto v___jp_3628_;
}
else
{
v___y_3629_ = v___y_3638_;
v___y_3630_ = v___y_3636_;
v___y_3631_ = v___y_3636_;
goto v___jp_3628_;
}
}
v___jp_3641_:
{
uint64_t v___x_3642_; uint8_t v___x_3643_; 
v___x_3642_ = 0ULL;
v___x_3643_ = lean_uint64_dec_eq(v_product_3425_, v___x_3642_);
if (v___x_3643_ == 0)
{
uint64_t v___x_3644_; uint64_t v___x_3645_; uint8_t v___x_3646_; 
v___x_3644_ = 32ULL;
v___x_3645_ = lean_uint64_shift_right(v_product_3425_, v___x_3644_);
v___x_3646_ = lean_uint64_dec_eq(v___x_3645_, v___x_3642_);
if (v___x_3646_ == 0)
{
v___y_3636_ = v___x_3642_;
v___y_3637_ = v___x_3644_;
v___y_3638_ = v___x_3645_;
goto v___jp_3635_;
}
else
{
v___y_3636_ = v___x_3642_;
v___y_3637_ = v___x_3644_;
v___y_3638_ = v_product_3425_;
goto v___jp_3635_;
}
}
else
{
if (v_sign_3424_ == 0)
{
uint32_t v___x_3647_; 
v___x_3647_ = 0;
return v___x_3647_;
}
else
{
uint32_t v___x_3648_; 
v___x_3648_ = 2147483648;
return v___x_3648_;
}
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_LowScale_roundSelect___boxed(lean_object* v_sign_3691_, lean_object* v_product_3692_, lean_object* v_scale_3693_){
_start:
{
uint8_t v_sign_boxed_3694_; uint64_t v_product_boxed_3695_; uint64_t v_scale_boxed_3696_; uint32_t v_res_3697_; lean_object* v_r_3698_; 
v_sign_boxed_3694_ = lean_unbox(v_sign_3691_);
v_product_boxed_3695_ = lean_unbox_uint64(v_product_3692_);
lean_dec_ref(v_product_3692_);
v_scale_boxed_3696_ = lean_unbox_uint64(v_scale_3693_);
lean_dec_ref(v_scale_3693_);
v_res_3697_ = lp_competition_Submission_LowScale_roundSelect(v_sign_boxed_3694_, v_product_boxed_3695_, v_scale_boxed_3696_);
v_r_3698_ = lean_box_uint32(v_res_3697_);
return v_r_3698_;
}
}
LEAN_EXPORT uint32_t lp_competition_Submission_LowScale_core(uint32_t v_xBits_3699_, uint32_t v_yBits_3700_){
_start:
{
uint32_t v___y_3702_; uint32_t v___y_3706_; uint32_t v___y_3710_; uint32_t v___y_3711_; uint32_t v___y_3712_; uint8_t v___y_3716_; uint32_t v___y_3717_; uint64_t v___y_3718_; uint64_t v___y_3719_; uint32_t v___y_3731_; uint32_t v___y_3732_; uint32_t v___y_3733_; uint8_t v___y_3737_; uint32_t v___y_3738_; uint64_t v___y_3739_; uint64_t v___y_3740_; uint32_t v___x_3751_; uint32_t v___x_3752_; uint32_t v___x_3753_; uint32_t v___y_3755_; uint32_t v___y_3756_; uint32_t v___y_3757_; uint32_t v___y_3758_; uint8_t v___y_3765_; uint32_t v___y_3766_; uint32_t v___y_3767_; uint32_t v___y_3768_; uint32_t v___y_3772_; uint8_t v___y_3773_; uint64_t v___y_3774_; uint64_t v___y_3775_; uint64_t v___y_3776_; uint8_t v___y_3786_; uint32_t v___y_3787_; uint64_t v___y_3788_; uint8_t v___y_3789_; uint64_t v___y_3790_; uint64_t v___y_3791_; uint32_t v___y_3798_; uint8_t v___y_3799_; uint64_t v___y_3800_; uint64_t v___y_3801_; uint64_t v___y_3802_; uint64_t v___y_3808_; uint8_t v___y_3809_; uint32_t v___y_3810_; uint64_t v___y_3811_; uint64_t v___y_3812_; uint64_t v___y_3813_; uint64_t v___y_3868_; uint32_t v___y_3869_; uint8_t v___y_3870_; uint64_t v___y_3871_; uint64_t v___y_3872_; uint64_t v___y_3873_; uint64_t v___y_3874_; uint64_t v___y_3880_; uint8_t v___y_3881_; uint32_t v___y_3882_; uint64_t v___y_3883_; uint64_t v___y_3884_; uint64_t v___y_3885_; uint64_t v___y_3886_; uint64_t v___y_3887_; uint64_t v___y_3888_; uint64_t v___y_3893_; uint32_t v___y_3894_; uint8_t v___y_3895_; uint64_t v___y_3896_; uint64_t v___y_3897_; uint64_t v___y_3898_; uint64_t v___y_3899_; uint64_t v___y_3904_; uint8_t v___y_3905_; uint32_t v___y_3906_; uint64_t v___y_3907_; uint64_t v___y_3908_; uint64_t v___y_3909_; uint64_t v___y_3910_; uint64_t v___y_3911_; uint64_t v___y_3912_; uint64_t v___y_3917_; uint32_t v___y_3918_; uint8_t v___y_3919_; uint64_t v___y_3920_; uint64_t v___y_3921_; uint64_t v___y_3922_; uint64_t v___y_3923_; uint64_t v___y_3928_; uint8_t v___y_3929_; uint32_t v___y_3930_; uint64_t v___y_3931_; uint64_t v___y_3932_; uint64_t v___y_3933_; uint64_t v___y_3934_; uint64_t v___y_3935_; uint64_t v___y_3936_; uint64_t v___y_3941_; uint32_t v___y_3942_; uint8_t v___y_3943_; uint64_t v___y_3944_; uint64_t v___y_3945_; uint64_t v___y_3946_; uint64_t v___y_3947_; uint64_t v___y_3952_; uint8_t v___y_3953_; uint32_t v___y_3954_; uint64_t v___y_3955_; uint64_t v___y_3956_; uint64_t v___y_3957_; uint64_t v___y_3958_; uint64_t v___y_3959_; uint64_t v___y_3960_; uint64_t v___y_3965_; uint32_t v___y_3966_; uint8_t v___y_3967_; uint64_t v___y_3968_; uint64_t v___y_3969_; uint64_t v___y_3970_; uint64_t v___y_3971_; uint64_t v___y_3976_; uint8_t v___y_3977_; uint32_t v___y_3978_; uint64_t v___y_3979_; uint64_t v___y_3980_; uint64_t v___y_3981_; uint64_t v___y_3982_; uint64_t v___y_3986_; uint32_t v___y_3987_; uint8_t v___y_3988_; uint64_t v___y_3989_; uint64_t v___y_3998_; uint8_t v___y_3999_; uint32_t v___y_4000_; uint64_t v___y_4001_; uint64_t v___y_4002_; uint64_t v___y_4003_; uint32_t v_xExponent_4036_; uint32_t v___x_4037_; uint32_t v_yExponent_4038_; uint64_t v___y_4040_; uint32_t v___y_4041_; uint8_t v___y_4042_; uint64_t v___y_4043_; uint64_t v___y_4044_; uint8_t v___y_4051_; uint32_t v___y_4052_; uint64_t v___y_4053_; uint64_t v___y_4054_; uint32_t v___y_4061_; uint8_t v___y_4062_; uint32_t v___y_4063_; uint64_t v___y_4064_; uint8_t v___y_4072_; uint8_t v___y_4087_; uint8_t v___y_4088_; uint8_t v___y_4090_; uint32_t v___x_4097_; uint32_t v___x_4098_; uint32_t v___x_4099_; uint8_t v___x_4100_; 
v___x_3751_ = 23;
v___x_3752_ = lean_uint32_shift_right(v_xBits_3699_, v___x_3751_);
v___x_3753_ = 255;
v_xExponent_4036_ = lean_uint32_land(v___x_3752_, v___x_3753_);
v___x_4037_ = lean_uint32_shift_right(v_yBits_3700_, v___x_3751_);
v_yExponent_4038_ = lean_uint32_land(v___x_4037_, v___x_3753_);
v___x_4097_ = 2147483648;
v___x_4098_ = lean_uint32_land(v_xBits_3699_, v___x_4097_);
v___x_4099_ = 0;
v___x_4100_ = lean_uint32_dec_eq(v___x_4098_, v___x_4099_);
if (v___x_4100_ == 0)
{
uint8_t v___x_4101_; 
v___x_4101_ = 1;
v___y_4090_ = v___x_4101_;
goto v___jp_4089_;
}
else
{
uint8_t v___x_4102_; 
v___x_4102_ = 0;
v___y_4090_ = v___x_4102_;
goto v___jp_4089_;
}
v___jp_3701_:
{
uint32_t v___x_3703_; uint32_t v___x_3704_; 
v___x_3703_ = 8388608;
v___x_3704_ = lean_uint32_lor(v___y_3702_, v___x_3703_);
return v___x_3704_;
}
v___jp_3705_:
{
uint32_t v___x_3707_; uint32_t v___x_3708_; 
v___x_3707_ = 8388608;
v___x_3708_ = lean_uint32_lor(v___y_3706_, v___x_3707_);
return v___x_3708_;
}
v___jp_3709_:
{
uint32_t v___x_3713_; uint32_t v___x_3714_; 
v___x_3713_ = lean_uint32_land(v___y_3711_, v___y_3710_);
v___x_3714_ = lean_uint32_lor(v___y_3712_, v___x_3713_);
return v___x_3714_;
}
v___jp_3715_:
{
uint8_t v___x_3720_; 
v___x_3720_ = lean_uint64_dec_eq(v___y_3719_, v___y_3718_);
if (v___x_3720_ == 0)
{
uint64_t v___x_3721_; uint8_t v___x_3722_; 
v___x_3721_ = 8388608ULL;
v___x_3722_ = lean_uint64_dec_eq(v___y_3719_, v___x_3721_);
if (v___x_3722_ == 0)
{
uint32_t v___x_3723_; 
v___x_3723_ = lean_uint64_to_uint32(v___y_3719_);
if (v___y_3716_ == 0)
{
uint32_t v___x_3724_; 
v___x_3724_ = 0;
v___y_3710_ = v___y_3717_;
v___y_3711_ = v___x_3723_;
v___y_3712_ = v___x_3724_;
goto v___jp_3709_;
}
else
{
uint32_t v___x_3725_; 
v___x_3725_ = 2147483648;
v___y_3710_ = v___y_3717_;
v___y_3711_ = v___x_3723_;
v___y_3712_ = v___x_3725_;
goto v___jp_3709_;
}
}
else
{
if (v___y_3716_ == 0)
{
uint32_t v___x_3726_; 
v___x_3726_ = 0;
v___y_3702_ = v___x_3726_;
goto v___jp_3701_;
}
else
{
uint32_t v___x_3727_; 
v___x_3727_ = 2147483648;
v___y_3702_ = v___x_3727_;
goto v___jp_3701_;
}
}
}
else
{
if (v___y_3716_ == 0)
{
uint32_t v___x_3728_; 
v___x_3728_ = 0;
return v___x_3728_;
}
else
{
uint32_t v___x_3729_; 
v___x_3729_ = 2147483648;
return v___x_3729_;
}
}
}
v___jp_3730_:
{
uint32_t v___x_3734_; uint32_t v___x_3735_; 
v___x_3734_ = lean_uint32_land(v___y_3731_, v___y_3732_);
v___x_3735_ = lean_uint32_lor(v___y_3733_, v___x_3734_);
return v___x_3735_;
}
v___jp_3736_:
{
uint8_t v___x_3741_; 
v___x_3741_ = lean_uint64_dec_eq(v___y_3740_, v___y_3739_);
if (v___x_3741_ == 0)
{
uint64_t v___x_3742_; uint8_t v___x_3743_; 
v___x_3742_ = 8388608ULL;
v___x_3743_ = lean_uint64_dec_eq(v___y_3740_, v___x_3742_);
if (v___x_3743_ == 0)
{
uint32_t v___x_3744_; 
v___x_3744_ = lean_uint64_to_uint32(v___y_3740_);
if (v___y_3737_ == 0)
{
uint32_t v___x_3745_; 
v___x_3745_ = 0;
v___y_3731_ = v___x_3744_;
v___y_3732_ = v___y_3738_;
v___y_3733_ = v___x_3745_;
goto v___jp_3730_;
}
else
{
uint32_t v___x_3746_; 
v___x_3746_ = 2147483648;
v___y_3731_ = v___x_3744_;
v___y_3732_ = v___y_3738_;
v___y_3733_ = v___x_3746_;
goto v___jp_3730_;
}
}
else
{
if (v___y_3737_ == 0)
{
uint32_t v___x_3747_; 
v___x_3747_ = 0;
v___y_3706_ = v___x_3747_;
goto v___jp_3705_;
}
else
{
uint32_t v___x_3748_; 
v___x_3748_ = 2147483648;
v___y_3706_ = v___x_3748_;
goto v___jp_3705_;
}
}
}
else
{
if (v___y_3737_ == 0)
{
uint32_t v___x_3749_; 
v___x_3749_ = 0;
return v___x_3749_;
}
else
{
uint32_t v___x_3750_; 
v___x_3750_ = 2147483648;
return v___x_3750_;
}
}
}
v___jp_3754_:
{
uint32_t v___x_3759_; uint32_t v___x_3760_; uint32_t v___x_3761_; uint32_t v___x_3762_; uint32_t v___x_3763_; 
v___x_3759_ = lean_uint32_land(v___y_3757_, v___x_3753_);
v___x_3760_ = lean_uint32_shift_left(v___x_3759_, v___x_3751_);
v___x_3761_ = lean_uint32_lor(v___y_3758_, v___x_3760_);
v___x_3762_ = lean_uint32_land(v___y_3756_, v___y_3755_);
v___x_3763_ = lean_uint32_lor(v___x_3761_, v___x_3762_);
return v___x_3763_;
}
v___jp_3764_:
{
if (v___y_3765_ == 0)
{
uint32_t v___x_3769_; 
v___x_3769_ = 0;
v___y_3755_ = v___y_3766_;
v___y_3756_ = v___y_3768_;
v___y_3757_ = v___y_3767_;
v___y_3758_ = v___x_3769_;
goto v___jp_3754_;
}
else
{
uint32_t v___x_3770_; 
v___x_3770_ = 2147483648;
v___y_3755_ = v___y_3766_;
v___y_3756_ = v___y_3768_;
v___y_3757_ = v___y_3767_;
v___y_3758_ = v___x_3770_;
goto v___jp_3754_;
}
}
v___jp_3771_:
{
uint64_t v___x_3777_; uint64_t v_encodedExponent_3778_; uint32_t v___x_3779_; uint64_t v___x_3780_; uint8_t v___x_3781_; 
v___x_3777_ = 171ULL;
v_encodedExponent_3778_ = lean_uint64_sub(v___y_3775_, v___x_3777_);
v___x_3779_ = lean_uint64_to_uint32(v_encodedExponent_3778_);
v___x_3780_ = 8388608ULL;
v___x_3781_ = lean_uint64_dec_lt(v___y_3776_, v___x_3780_);
if (v___x_3781_ == 0)
{
uint64_t v___x_3782_; uint32_t v___x_3783_; 
v___x_3782_ = lean_uint64_sub(v___y_3776_, v___x_3780_);
v___x_3783_ = lean_uint64_to_uint32(v___x_3782_);
v___y_3765_ = v___y_3773_;
v___y_3766_ = v___y_3772_;
v___y_3767_ = v___x_3779_;
v___y_3768_ = v___x_3783_;
goto v___jp_3764_;
}
else
{
uint32_t v___x_3784_; 
v___x_3784_ = lean_uint64_to_uint32(v___y_3774_);
v___y_3765_ = v___y_3773_;
v___y_3766_ = v___y_3772_;
v___y_3767_ = v___x_3779_;
v___y_3768_ = v___x_3784_;
goto v___jp_3764_;
}
}
v___jp_3785_:
{
uint64_t v___x_3792_; uint8_t v___x_3793_; 
v___x_3792_ = 425ULL;
v___x_3793_ = lean_uint64_dec_lt(v___x_3792_, v___y_3791_);
if (v___x_3793_ == 0)
{
if (v___y_3789_ == 0)
{
v___y_3772_ = v___y_3787_;
v___y_3773_ = v___y_3786_;
v___y_3774_ = v___y_3790_;
v___y_3775_ = v___y_3791_;
v___y_3776_ = v___y_3788_;
goto v___jp_3771_;
}
else
{
uint64_t v___x_3794_; 
v___x_3794_ = 8388608ULL;
v___y_3772_ = v___y_3787_;
v___y_3773_ = v___y_3786_;
v___y_3774_ = v___y_3790_;
v___y_3775_ = v___y_3791_;
v___y_3776_ = v___x_3794_;
goto v___jp_3771_;
}
}
else
{
if (v___y_3786_ == 0)
{
uint32_t v___x_3795_; 
v___x_3795_ = 2139095040;
return v___x_3795_;
}
else
{
uint32_t v___x_3796_; 
v___x_3796_ = 4286578688;
return v___x_3796_;
}
}
}
v___jp_3797_:
{
uint64_t v___x_3803_; uint8_t v_carry_3804_; 
v___x_3803_ = 16777216ULL;
v_carry_3804_ = lean_uint64_dec_eq(v___y_3802_, v___x_3803_);
if (v_carry_3804_ == 0)
{
v___y_3786_ = v___y_3799_;
v___y_3787_ = v___y_3798_;
v___y_3788_ = v___y_3802_;
v___y_3789_ = v_carry_3804_;
v___y_3790_ = v___y_3800_;
v___y_3791_ = v___y_3801_;
goto v___jp_3785_;
}
else
{
uint64_t v___x_3805_; uint64_t v___x_3806_; 
v___x_3805_ = 1ULL;
v___x_3806_ = lean_uint64_add(v___y_3801_, v___x_3805_);
v___y_3786_ = v___y_3799_;
v___y_3787_ = v___y_3798_;
v___y_3788_ = v___y_3802_;
v___y_3789_ = v_carry_3804_;
v___y_3790_ = v___y_3800_;
v___y_3791_ = v___x_3806_;
goto v___jp_3785_;
}
}
v___jp_3807_:
{
uint64_t v_position_3814_; uint64_t v___x_3815_; uint8_t v___x_3816_; 
v_position_3814_ = lean_uint64_add(v___y_3813_, v___y_3808_);
v___x_3815_ = 172ULL;
v___x_3816_ = lean_uint64_dec_lt(v_position_3814_, v___x_3815_);
if (v___x_3816_ == 0)
{
uint64_t v___x_3817_; uint8_t v___x_3818_; 
v___x_3817_ = 23ULL;
v___x_3818_ = lean_uint64_dec_lt(v___y_3813_, v___x_3817_);
if (v___x_3818_ == 0)
{
uint64_t v___x_3819_; uint8_t v___x_3820_; 
v___x_3819_ = lean_uint64_sub(v___y_3813_, v___x_3817_);
v___x_3820_ = lean_uint64_dec_eq(v___x_3819_, v___y_3812_);
if (v___x_3820_ == 0)
{
uint64_t v___x_3821_; uint8_t v___x_3822_; 
v___x_3821_ = 64ULL;
v___x_3822_ = lean_uint64_dec_lt(v___x_3819_, v___x_3821_);
if (v___x_3822_ == 0)
{
uint8_t v___x_3823_; 
v___x_3823_ = lean_uint64_dec_eq(v___x_3819_, v___x_3821_);
if (v___x_3823_ == 0)
{
v___y_3798_ = v___y_3810_;
v___y_3799_ = v___y_3809_;
v___y_3800_ = v___y_3812_;
v___y_3801_ = v_position_3814_;
v___y_3802_ = v___y_3812_;
goto v___jp_3797_;
}
else
{
uint64_t v___x_3824_; uint8_t v___x_3825_; 
v___x_3824_ = 9223372036854775808ULL;
v___x_3825_ = lean_uint64_dec_lt(v___x_3824_, v___y_3811_);
if (v___x_3825_ == 0)
{
v___y_3798_ = v___y_3810_;
v___y_3799_ = v___y_3809_;
v___y_3800_ = v___y_3812_;
v___y_3801_ = v_position_3814_;
v___y_3802_ = v___y_3812_;
goto v___jp_3797_;
}
else
{
uint64_t v___x_3826_; 
v___x_3826_ = 1ULL;
v___y_3798_ = v___y_3810_;
v___y_3799_ = v___y_3809_;
v___y_3800_ = v___y_3812_;
v___y_3801_ = v_position_3814_;
v___y_3802_ = v___x_3826_;
goto v___jp_3797_;
}
}
}
else
{
uint64_t v_quotient_3827_; uint64_t v___x_3828_; uint64_t v___x_3829_; uint64_t v___x_3830_; uint64_t v_remainder_3831_; uint64_t v___x_3832_; uint64_t v_half_3833_; uint8_t v___x_3834_; 
v_quotient_3827_ = lean_uint64_shift_right(v___y_3811_, v___x_3819_);
v___x_3828_ = 1ULL;
v___x_3829_ = lean_uint64_shift_left(v___x_3828_, v___x_3819_);
v___x_3830_ = lean_uint64_sub(v___x_3829_, v___x_3828_);
v_remainder_3831_ = lean_uint64_land(v___y_3811_, v___x_3830_);
v___x_3832_ = lean_uint64_sub(v___x_3819_, v___x_3828_);
v_half_3833_ = lean_uint64_shift_left(v___x_3828_, v___x_3832_);
v___x_3834_ = lean_uint64_dec_lt(v_remainder_3831_, v_half_3833_);
if (v___x_3834_ == 0)
{
uint8_t v___x_3835_; 
v___x_3835_ = lean_uint64_dec_lt(v_half_3833_, v_remainder_3831_);
if (v___x_3835_ == 0)
{
uint64_t v___x_3836_; uint8_t v___x_3837_; 
v___x_3836_ = lean_uint64_land(v_quotient_3827_, v___x_3828_);
v___x_3837_ = lean_uint64_dec_eq(v___x_3836_, v___y_3812_);
if (v___x_3837_ == 0)
{
uint64_t v___x_3838_; 
v___x_3838_ = lean_uint64_add(v_quotient_3827_, v___x_3828_);
v___y_3798_ = v___y_3810_;
v___y_3799_ = v___y_3809_;
v___y_3800_ = v___y_3812_;
v___y_3801_ = v_position_3814_;
v___y_3802_ = v___x_3838_;
goto v___jp_3797_;
}
else
{
v___y_3798_ = v___y_3810_;
v___y_3799_ = v___y_3809_;
v___y_3800_ = v___y_3812_;
v___y_3801_ = v_position_3814_;
v___y_3802_ = v_quotient_3827_;
goto v___jp_3797_;
}
}
else
{
uint64_t v___x_3839_; 
v___x_3839_ = lean_uint64_add(v_quotient_3827_, v___x_3828_);
v___y_3798_ = v___y_3810_;
v___y_3799_ = v___y_3809_;
v___y_3800_ = v___y_3812_;
v___y_3801_ = v_position_3814_;
v___y_3802_ = v___x_3839_;
goto v___jp_3797_;
}
}
else
{
v___y_3798_ = v___y_3810_;
v___y_3799_ = v___y_3809_;
v___y_3800_ = v___y_3812_;
v___y_3801_ = v_position_3814_;
v___y_3802_ = v_quotient_3827_;
goto v___jp_3797_;
}
}
}
else
{
v___y_3798_ = v___y_3810_;
v___y_3799_ = v___y_3809_;
v___y_3800_ = v___y_3812_;
v___y_3801_ = v_position_3814_;
v___y_3802_ = v___y_3811_;
goto v___jp_3797_;
}
}
else
{
uint64_t v___x_3840_; uint64_t v___x_3841_; 
v___x_3840_ = lean_uint64_sub(v___x_3817_, v___y_3813_);
v___x_3841_ = lean_uint64_shift_left(v___y_3811_, v___x_3840_);
v___y_3798_ = v___y_3810_;
v___y_3799_ = v___y_3809_;
v___y_3800_ = v___y_3812_;
v___y_3801_ = v_position_3814_;
v___y_3802_ = v___x_3841_;
goto v___jp_3797_;
}
}
else
{
uint64_t v___x_3842_; uint8_t v___x_3843_; 
v___x_3842_ = 149ULL;
v___x_3843_ = lean_uint64_dec_lt(v___y_3808_, v___x_3842_);
if (v___x_3843_ == 0)
{
uint64_t v___x_3844_; uint64_t v___x_3845_; 
v___x_3844_ = lean_uint64_sub(v___y_3808_, v___x_3842_);
v___x_3845_ = lean_uint64_shift_left(v___y_3811_, v___x_3844_);
v___y_3716_ = v___y_3809_;
v___y_3717_ = v___y_3810_;
v___y_3718_ = v___y_3812_;
v___y_3719_ = v___x_3845_;
goto v___jp_3715_;
}
else
{
uint64_t v___x_3846_; uint8_t v___x_3847_; 
v___x_3846_ = lean_uint64_sub(v___x_3842_, v___y_3808_);
v___x_3847_ = lean_uint64_dec_eq(v___x_3846_, v___y_3812_);
if (v___x_3847_ == 0)
{
uint64_t v___x_3848_; uint8_t v___x_3849_; 
v___x_3848_ = 64ULL;
v___x_3849_ = lean_uint64_dec_lt(v___x_3846_, v___x_3848_);
if (v___x_3849_ == 0)
{
uint8_t v___x_3850_; 
v___x_3850_ = lean_uint64_dec_eq(v___x_3846_, v___x_3848_);
if (v___x_3850_ == 0)
{
v___y_3716_ = v___y_3809_;
v___y_3717_ = v___y_3810_;
v___y_3718_ = v___y_3812_;
v___y_3719_ = v___y_3812_;
goto v___jp_3715_;
}
else
{
uint64_t v___x_3851_; uint8_t v___x_3852_; 
v___x_3851_ = 9223372036854775808ULL;
v___x_3852_ = lean_uint64_dec_lt(v___x_3851_, v___y_3811_);
if (v___x_3852_ == 0)
{
v___y_3716_ = v___y_3809_;
v___y_3717_ = v___y_3810_;
v___y_3718_ = v___y_3812_;
v___y_3719_ = v___y_3812_;
goto v___jp_3715_;
}
else
{
uint64_t v___x_3853_; 
v___x_3853_ = 1ULL;
v___y_3716_ = v___y_3809_;
v___y_3717_ = v___y_3810_;
v___y_3718_ = v___y_3812_;
v___y_3719_ = v___x_3853_;
goto v___jp_3715_;
}
}
}
else
{
uint64_t v_quotient_3854_; uint64_t v___x_3855_; uint64_t v___x_3856_; uint64_t v___x_3857_; uint64_t v_remainder_3858_; uint64_t v___x_3859_; uint64_t v_half_3860_; uint8_t v___x_3861_; 
v_quotient_3854_ = lean_uint64_shift_right(v___y_3811_, v___x_3846_);
v___x_3855_ = 1ULL;
v___x_3856_ = lean_uint64_shift_left(v___x_3855_, v___x_3846_);
v___x_3857_ = lean_uint64_sub(v___x_3856_, v___x_3855_);
v_remainder_3858_ = lean_uint64_land(v___y_3811_, v___x_3857_);
v___x_3859_ = lean_uint64_sub(v___x_3846_, v___x_3855_);
v_half_3860_ = lean_uint64_shift_left(v___x_3855_, v___x_3859_);
v___x_3861_ = lean_uint64_dec_lt(v_remainder_3858_, v_half_3860_);
if (v___x_3861_ == 0)
{
uint8_t v___x_3862_; 
v___x_3862_ = lean_uint64_dec_lt(v_half_3860_, v_remainder_3858_);
if (v___x_3862_ == 0)
{
uint64_t v___x_3863_; uint8_t v___x_3864_; 
v___x_3863_ = lean_uint64_land(v_quotient_3854_, v___x_3855_);
v___x_3864_ = lean_uint64_dec_eq(v___x_3863_, v___y_3812_);
if (v___x_3864_ == 0)
{
uint64_t v___x_3865_; 
v___x_3865_ = lean_uint64_add(v_quotient_3854_, v___x_3855_);
v___y_3716_ = v___y_3809_;
v___y_3717_ = v___y_3810_;
v___y_3718_ = v___y_3812_;
v___y_3719_ = v___x_3865_;
goto v___jp_3715_;
}
else
{
v___y_3716_ = v___y_3809_;
v___y_3717_ = v___y_3810_;
v___y_3718_ = v___y_3812_;
v___y_3719_ = v_quotient_3854_;
goto v___jp_3715_;
}
}
else
{
uint64_t v___x_3866_; 
v___x_3866_ = lean_uint64_add(v_quotient_3854_, v___x_3855_);
v___y_3716_ = v___y_3809_;
v___y_3717_ = v___y_3810_;
v___y_3718_ = v___y_3812_;
v___y_3719_ = v___x_3866_;
goto v___jp_3715_;
}
}
else
{
v___y_3716_ = v___y_3809_;
v___y_3717_ = v___y_3810_;
v___y_3718_ = v___y_3812_;
v___y_3719_ = v_quotient_3854_;
goto v___jp_3715_;
}
}
}
else
{
v___y_3716_ = v___y_3809_;
v___y_3717_ = v___y_3810_;
v___y_3718_ = v___y_3812_;
v___y_3719_ = v___y_3811_;
goto v___jp_3715_;
}
}
}
}
v___jp_3867_:
{
uint64_t v___x_3875_; uint64_t v___x_3876_; uint8_t v___x_3877_; 
v___x_3875_ = 1ULL;
v___x_3876_ = lean_uint64_shift_right(v___y_3873_, v___x_3875_);
v___x_3877_ = lean_uint64_dec_eq(v___x_3876_, v___y_3872_);
if (v___x_3877_ == 0)
{
uint64_t v___x_3878_; 
v___x_3878_ = lean_uint64_add(v___y_3874_, v___x_3875_);
v___y_3808_ = v___y_3868_;
v___y_3809_ = v___y_3870_;
v___y_3810_ = v___y_3869_;
v___y_3811_ = v___y_3871_;
v___y_3812_ = v___y_3872_;
v___y_3813_ = v___x_3878_;
goto v___jp_3807_;
}
else
{
v___y_3808_ = v___y_3868_;
v___y_3809_ = v___y_3870_;
v___y_3810_ = v___y_3869_;
v___y_3811_ = v___y_3871_;
v___y_3812_ = v___y_3872_;
v___y_3813_ = v___y_3874_;
goto v___jp_3807_;
}
}
v___jp_3879_:
{
uint64_t v___x_3889_; uint8_t v___x_3890_; 
v___x_3889_ = lean_uint64_shift_right(v___y_3884_, v___y_3886_);
v___x_3890_ = lean_uint64_dec_eq(v___x_3889_, v___y_3885_);
if (v___x_3890_ == 0)
{
uint64_t v___x_3891_; 
v___x_3891_ = lean_uint64_add(v___y_3887_, v___y_3886_);
v___y_3868_ = v___y_3880_;
v___y_3869_ = v___y_3882_;
v___y_3870_ = v___y_3881_;
v___y_3871_ = v___y_3883_;
v___y_3872_ = v___y_3885_;
v___y_3873_ = v___y_3888_;
v___y_3874_ = v___x_3891_;
goto v___jp_3867_;
}
else
{
v___y_3868_ = v___y_3880_;
v___y_3869_ = v___y_3882_;
v___y_3870_ = v___y_3881_;
v___y_3871_ = v___y_3883_;
v___y_3872_ = v___y_3885_;
v___y_3873_ = v___y_3888_;
v___y_3874_ = v___y_3887_;
goto v___jp_3867_;
}
}
v___jp_3892_:
{
uint64_t v___x_3900_; uint64_t v___x_3901_; uint8_t v___x_3902_; 
v___x_3900_ = 2ULL;
v___x_3901_ = lean_uint64_shift_right(v___y_3897_, v___x_3900_);
v___x_3902_ = lean_uint64_dec_eq(v___x_3901_, v___y_3898_);
if (v___x_3902_ == 0)
{
v___y_3880_ = v___y_3893_;
v___y_3881_ = v___y_3895_;
v___y_3882_ = v___y_3894_;
v___y_3883_ = v___y_3896_;
v___y_3884_ = v___y_3897_;
v___y_3885_ = v___y_3898_;
v___y_3886_ = v___x_3900_;
v___y_3887_ = v___y_3899_;
v___y_3888_ = v___x_3901_;
goto v___jp_3879_;
}
else
{
v___y_3880_ = v___y_3893_;
v___y_3881_ = v___y_3895_;
v___y_3882_ = v___y_3894_;
v___y_3883_ = v___y_3896_;
v___y_3884_ = v___y_3897_;
v___y_3885_ = v___y_3898_;
v___y_3886_ = v___x_3900_;
v___y_3887_ = v___y_3899_;
v___y_3888_ = v___y_3897_;
goto v___jp_3879_;
}
}
v___jp_3903_:
{
uint64_t v___x_3913_; uint8_t v___x_3914_; 
v___x_3913_ = lean_uint64_shift_right(v___y_3911_, v___y_3908_);
v___x_3914_ = lean_uint64_dec_eq(v___x_3913_, v___y_3909_);
if (v___x_3914_ == 0)
{
uint64_t v___x_3915_; 
v___x_3915_ = lean_uint64_add(v___y_3910_, v___y_3908_);
v___y_3893_ = v___y_3904_;
v___y_3894_ = v___y_3906_;
v___y_3895_ = v___y_3905_;
v___y_3896_ = v___y_3907_;
v___y_3897_ = v___y_3912_;
v___y_3898_ = v___y_3909_;
v___y_3899_ = v___x_3915_;
goto v___jp_3892_;
}
else
{
v___y_3893_ = v___y_3904_;
v___y_3894_ = v___y_3906_;
v___y_3895_ = v___y_3905_;
v___y_3896_ = v___y_3907_;
v___y_3897_ = v___y_3912_;
v___y_3898_ = v___y_3909_;
v___y_3899_ = v___y_3910_;
goto v___jp_3892_;
}
}
v___jp_3916_:
{
uint64_t v___x_3924_; uint64_t v___x_3925_; uint8_t v___x_3926_; 
v___x_3924_ = 4ULL;
v___x_3925_ = lean_uint64_shift_right(v___y_3922_, v___x_3924_);
v___x_3926_ = lean_uint64_dec_eq(v___x_3925_, v___y_3921_);
if (v___x_3926_ == 0)
{
v___y_3904_ = v___y_3917_;
v___y_3905_ = v___y_3919_;
v___y_3906_ = v___y_3918_;
v___y_3907_ = v___y_3920_;
v___y_3908_ = v___x_3924_;
v___y_3909_ = v___y_3921_;
v___y_3910_ = v___y_3923_;
v___y_3911_ = v___y_3922_;
v___y_3912_ = v___x_3925_;
goto v___jp_3903_;
}
else
{
v___y_3904_ = v___y_3917_;
v___y_3905_ = v___y_3919_;
v___y_3906_ = v___y_3918_;
v___y_3907_ = v___y_3920_;
v___y_3908_ = v___x_3924_;
v___y_3909_ = v___y_3921_;
v___y_3910_ = v___y_3923_;
v___y_3911_ = v___y_3922_;
v___y_3912_ = v___y_3922_;
goto v___jp_3903_;
}
}
v___jp_3927_:
{
uint64_t v___x_3937_; uint8_t v___x_3938_; 
v___x_3937_ = lean_uint64_shift_right(v___y_3935_, v___y_3931_);
v___x_3938_ = lean_uint64_dec_eq(v___x_3937_, v___y_3934_);
if (v___x_3938_ == 0)
{
uint64_t v___x_3939_; 
v___x_3939_ = lean_uint64_add(v___y_3933_, v___y_3931_);
v___y_3917_ = v___y_3928_;
v___y_3918_ = v___y_3930_;
v___y_3919_ = v___y_3929_;
v___y_3920_ = v___y_3932_;
v___y_3921_ = v___y_3934_;
v___y_3922_ = v___y_3936_;
v___y_3923_ = v___x_3939_;
goto v___jp_3916_;
}
else
{
v___y_3917_ = v___y_3928_;
v___y_3918_ = v___y_3930_;
v___y_3919_ = v___y_3929_;
v___y_3920_ = v___y_3932_;
v___y_3921_ = v___y_3934_;
v___y_3922_ = v___y_3936_;
v___y_3923_ = v___y_3933_;
goto v___jp_3916_;
}
}
v___jp_3940_:
{
uint64_t v___x_3948_; uint64_t v___x_3949_; uint8_t v___x_3950_; 
v___x_3948_ = 8ULL;
v___x_3949_ = lean_uint64_shift_right(v___y_3946_, v___x_3948_);
v___x_3950_ = lean_uint64_dec_eq(v___x_3949_, v___y_3945_);
if (v___x_3950_ == 0)
{
v___y_3928_ = v___y_3941_;
v___y_3929_ = v___y_3943_;
v___y_3930_ = v___y_3942_;
v___y_3931_ = v___x_3948_;
v___y_3932_ = v___y_3944_;
v___y_3933_ = v___y_3947_;
v___y_3934_ = v___y_3945_;
v___y_3935_ = v___y_3946_;
v___y_3936_ = v___x_3949_;
goto v___jp_3927_;
}
else
{
v___y_3928_ = v___y_3941_;
v___y_3929_ = v___y_3943_;
v___y_3930_ = v___y_3942_;
v___y_3931_ = v___x_3948_;
v___y_3932_ = v___y_3944_;
v___y_3933_ = v___y_3947_;
v___y_3934_ = v___y_3945_;
v___y_3935_ = v___y_3946_;
v___y_3936_ = v___y_3946_;
goto v___jp_3927_;
}
}
v___jp_3951_:
{
uint64_t v___x_3961_; uint8_t v___x_3962_; 
v___x_3961_ = lean_uint64_shift_right(v___y_3957_, v___y_3956_);
v___x_3962_ = lean_uint64_dec_eq(v___x_3961_, v___y_3958_);
if (v___x_3962_ == 0)
{
uint64_t v___x_3963_; 
v___x_3963_ = lean_uint64_add(v___y_3959_, v___y_3956_);
v___y_3941_ = v___y_3952_;
v___y_3942_ = v___y_3954_;
v___y_3943_ = v___y_3953_;
v___y_3944_ = v___y_3955_;
v___y_3945_ = v___y_3958_;
v___y_3946_ = v___y_3960_;
v___y_3947_ = v___x_3963_;
goto v___jp_3940_;
}
else
{
v___y_3941_ = v___y_3952_;
v___y_3942_ = v___y_3954_;
v___y_3943_ = v___y_3953_;
v___y_3944_ = v___y_3955_;
v___y_3945_ = v___y_3958_;
v___y_3946_ = v___y_3960_;
v___y_3947_ = v___y_3959_;
goto v___jp_3940_;
}
}
v___jp_3964_:
{
uint64_t v___x_3972_; uint64_t v___x_3973_; uint8_t v___x_3974_; 
v___x_3972_ = 16ULL;
v___x_3973_ = lean_uint64_shift_right(v___y_3969_, v___x_3972_);
v___x_3974_ = lean_uint64_dec_eq(v___x_3973_, v___y_3970_);
if (v___x_3974_ == 0)
{
v___y_3952_ = v___y_3965_;
v___y_3953_ = v___y_3967_;
v___y_3954_ = v___y_3966_;
v___y_3955_ = v___y_3968_;
v___y_3956_ = v___x_3972_;
v___y_3957_ = v___y_3969_;
v___y_3958_ = v___y_3970_;
v___y_3959_ = v___y_3971_;
v___y_3960_ = v___x_3973_;
goto v___jp_3951_;
}
else
{
v___y_3952_ = v___y_3965_;
v___y_3953_ = v___y_3967_;
v___y_3954_ = v___y_3966_;
v___y_3955_ = v___y_3968_;
v___y_3956_ = v___x_3972_;
v___y_3957_ = v___y_3969_;
v___y_3958_ = v___y_3970_;
v___y_3959_ = v___y_3971_;
v___y_3960_ = v___y_3969_;
goto v___jp_3951_;
}
}
v___jp_3975_:
{
uint64_t v___x_3983_; uint8_t v___x_3984_; 
v___x_3983_ = lean_uint64_shift_right(v___y_3979_, v___y_3980_);
v___x_3984_ = lean_uint64_dec_eq(v___x_3983_, v___y_3981_);
if (v___x_3984_ == 0)
{
v___y_3965_ = v___y_3976_;
v___y_3966_ = v___y_3978_;
v___y_3967_ = v___y_3977_;
v___y_3968_ = v___y_3979_;
v___y_3969_ = v___y_3982_;
v___y_3970_ = v___y_3981_;
v___y_3971_ = v___y_3980_;
goto v___jp_3964_;
}
else
{
v___y_3965_ = v___y_3976_;
v___y_3966_ = v___y_3978_;
v___y_3967_ = v___y_3977_;
v___y_3968_ = v___y_3979_;
v___y_3969_ = v___y_3982_;
v___y_3970_ = v___y_3981_;
v___y_3971_ = v___y_3981_;
goto v___jp_3964_;
}
}
v___jp_3985_:
{
uint64_t v___x_3990_; uint8_t v___x_3991_; 
v___x_3990_ = 0ULL;
v___x_3991_ = lean_uint64_dec_eq(v___y_3989_, v___x_3990_);
if (v___x_3991_ == 0)
{
uint64_t v___x_3992_; uint64_t v___x_3993_; uint8_t v___x_3994_; 
v___x_3992_ = 32ULL;
v___x_3993_ = lean_uint64_shift_right(v___y_3989_, v___x_3992_);
v___x_3994_ = lean_uint64_dec_eq(v___x_3993_, v___x_3990_);
if (v___x_3994_ == 0)
{
v___y_3976_ = v___y_3986_;
v___y_3977_ = v___y_3988_;
v___y_3978_ = v___y_3987_;
v___y_3979_ = v___y_3989_;
v___y_3980_ = v___x_3992_;
v___y_3981_ = v___x_3990_;
v___y_3982_ = v___x_3993_;
goto v___jp_3975_;
}
else
{
v___y_3976_ = v___y_3986_;
v___y_3977_ = v___y_3988_;
v___y_3978_ = v___y_3987_;
v___y_3979_ = v___y_3989_;
v___y_3980_ = v___x_3992_;
v___y_3981_ = v___x_3990_;
v___y_3982_ = v___y_3989_;
goto v___jp_3975_;
}
}
else
{
if (v___y_3988_ == 0)
{
uint32_t v___x_3995_; 
v___x_3995_ = 0;
return v___x_3995_;
}
else
{
uint32_t v___x_3996_; 
v___x_3996_ = 2147483648;
return v___x_3996_;
}
}
}
v___jp_3997_:
{
uint64_t v___x_4004_; uint64_t v___x_4005_; uint64_t v___x_4006_; uint8_t v___x_4007_; 
v___x_4004_ = lean_uint64_mul(v___y_4002_, v___y_4001_);
v___x_4005_ = lean_uint64_add(v___y_3998_, v___y_4003_);
v___x_4006_ = 281474976710656ULL;
v___x_4007_ = lean_uint64_dec_lt(v___x_4004_, v___x_4006_);
if (v___x_4007_ == 0)
{
v___y_3986_ = v___x_4005_;
v___y_3987_ = v___y_4000_;
v___y_3988_ = v___y_3999_;
v___y_3989_ = v___x_4004_;
goto v___jp_3985_;
}
else
{
uint64_t v___x_4008_; uint8_t v___x_4009_; 
v___x_4008_ = 123ULL;
v___x_4009_ = lean_uint64_dec_le(v___x_4005_, v___x_4008_);
if (v___x_4009_ == 0)
{
v___y_3986_ = v___x_4005_;
v___y_3987_ = v___y_4000_;
v___y_3988_ = v___y_3999_;
v___y_3989_ = v___x_4004_;
goto v___jp_3985_;
}
else
{
uint64_t v___x_4010_; uint8_t v___x_4011_; 
v___x_4010_ = 0ULL;
v___x_4011_ = lean_uint64_dec_eq(v___x_4004_, v___x_4010_);
if (v___x_4011_ == 0)
{
uint64_t v___x_4012_; uint64_t v___x_4013_; uint8_t v___x_4014_; 
v___x_4012_ = 149ULL;
v___x_4013_ = lean_uint64_sub(v___x_4012_, v___x_4005_);
v___x_4014_ = lean_uint64_dec_eq(v___x_4013_, v___x_4010_);
if (v___x_4014_ == 0)
{
uint64_t v___x_4015_; uint8_t v___x_4016_; 
v___x_4015_ = 64ULL;
v___x_4016_ = lean_uint64_dec_lt(v___x_4013_, v___x_4015_);
if (v___x_4016_ == 0)
{
uint8_t v___x_4017_; 
v___x_4017_ = lean_uint64_dec_eq(v___x_4013_, v___x_4015_);
if (v___x_4017_ == 0)
{
v___y_3737_ = v___y_3999_;
v___y_3738_ = v___y_4000_;
v___y_3739_ = v___x_4010_;
v___y_3740_ = v___x_4010_;
goto v___jp_3736_;
}
else
{
uint64_t v___x_4018_; uint8_t v___x_4019_; 
v___x_4018_ = 9223372036854775808ULL;
v___x_4019_ = lean_uint64_dec_lt(v___x_4018_, v___x_4004_);
if (v___x_4019_ == 0)
{
v___y_3737_ = v___y_3999_;
v___y_3738_ = v___y_4000_;
v___y_3739_ = v___x_4010_;
v___y_3740_ = v___x_4010_;
goto v___jp_3736_;
}
else
{
uint64_t v___x_4020_; 
v___x_4020_ = 1ULL;
v___y_3737_ = v___y_3999_;
v___y_3738_ = v___y_4000_;
v___y_3739_ = v___x_4010_;
v___y_3740_ = v___x_4020_;
goto v___jp_3736_;
}
}
}
else
{
uint64_t v_quotient_4021_; uint64_t v___x_4022_; uint64_t v___x_4023_; uint64_t v___x_4024_; uint64_t v_remainder_4025_; uint64_t v___x_4026_; uint64_t v_half_4027_; uint8_t v___x_4028_; 
v_quotient_4021_ = lean_uint64_shift_right(v___x_4004_, v___x_4013_);
v___x_4022_ = 1ULL;
v___x_4023_ = lean_uint64_shift_left(v___x_4022_, v___x_4013_);
v___x_4024_ = lean_uint64_sub(v___x_4023_, v___x_4022_);
v_remainder_4025_ = lean_uint64_land(v___x_4004_, v___x_4024_);
v___x_4026_ = lean_uint64_sub(v___x_4013_, v___x_4022_);
v_half_4027_ = lean_uint64_shift_left(v___x_4022_, v___x_4026_);
v___x_4028_ = lean_uint64_dec_lt(v_remainder_4025_, v_half_4027_);
if (v___x_4028_ == 0)
{
uint8_t v___x_4029_; 
v___x_4029_ = lean_uint64_dec_lt(v_half_4027_, v_remainder_4025_);
if (v___x_4029_ == 0)
{
uint64_t v___x_4030_; uint8_t v___x_4031_; 
v___x_4030_ = lean_uint64_land(v_quotient_4021_, v___x_4022_);
v___x_4031_ = lean_uint64_dec_eq(v___x_4030_, v___x_4010_);
if (v___x_4031_ == 0)
{
uint64_t v___x_4032_; 
v___x_4032_ = lean_uint64_add(v_quotient_4021_, v___x_4022_);
v___y_3737_ = v___y_3999_;
v___y_3738_ = v___y_4000_;
v___y_3739_ = v___x_4010_;
v___y_3740_ = v___x_4032_;
goto v___jp_3736_;
}
else
{
v___y_3737_ = v___y_3999_;
v___y_3738_ = v___y_4000_;
v___y_3739_ = v___x_4010_;
v___y_3740_ = v_quotient_4021_;
goto v___jp_3736_;
}
}
else
{
uint64_t v___x_4033_; 
v___x_4033_ = lean_uint64_add(v_quotient_4021_, v___x_4022_);
v___y_3737_ = v___y_3999_;
v___y_3738_ = v___y_4000_;
v___y_3739_ = v___x_4010_;
v___y_3740_ = v___x_4033_;
goto v___jp_3736_;
}
}
else
{
v___y_3737_ = v___y_3999_;
v___y_3738_ = v___y_4000_;
v___y_3739_ = v___x_4010_;
v___y_3740_ = v_quotient_4021_;
goto v___jp_3736_;
}
}
}
else
{
v___y_3737_ = v___y_3999_;
v___y_3738_ = v___y_4000_;
v___y_3739_ = v___x_4010_;
v___y_3740_ = v___x_4004_;
goto v___jp_3736_;
}
}
else
{
if (v___y_3999_ == 0)
{
uint32_t v___x_4034_; 
v___x_4034_ = 0;
return v___x_4034_;
}
else
{
uint32_t v___x_4035_; 
v___x_4035_ = 2147483648;
return v___x_4035_;
}
}
}
}
}
v___jp_4039_:
{
uint64_t v___x_4045_; uint64_t v___x_4046_; uint8_t v___x_4047_; 
v___x_4045_ = lean_uint32_to_uint64(v_yExponent_4038_);
v___x_4046_ = 0ULL;
v___x_4047_ = lean_uint64_dec_eq(v___x_4045_, v___x_4046_);
if (v___x_4047_ == 0)
{
uint64_t v___x_4048_; uint64_t v___x_4049_; 
v___x_4048_ = 1ULL;
v___x_4049_ = lean_uint64_sub(v___x_4045_, v___x_4048_);
v___y_3998_ = v___y_4044_;
v___y_3999_ = v___y_4042_;
v___y_4000_ = v___y_4041_;
v___y_4001_ = v___y_4040_;
v___y_4002_ = v___y_4043_;
v___y_4003_ = v___x_4049_;
goto v___jp_3997_;
}
else
{
v___y_3998_ = v___y_4044_;
v___y_3999_ = v___y_4042_;
v___y_4000_ = v___y_4041_;
v___y_4001_ = v___y_4040_;
v___y_4002_ = v___y_4043_;
v___y_4003_ = v___x_4046_;
goto v___jp_3997_;
}
}
v___jp_4050_:
{
uint64_t v___x_4055_; uint64_t v___x_4056_; uint8_t v___x_4057_; 
v___x_4055_ = lean_uint32_to_uint64(v_xExponent_4036_);
v___x_4056_ = 0ULL;
v___x_4057_ = lean_uint64_dec_eq(v___x_4055_, v___x_4056_);
if (v___x_4057_ == 0)
{
uint64_t v___x_4058_; uint64_t v___x_4059_; 
v___x_4058_ = 1ULL;
v___x_4059_ = lean_uint64_sub(v___x_4055_, v___x_4058_);
v___y_4040_ = v___y_4054_;
v___y_4041_ = v___y_4052_;
v___y_4042_ = v___y_4051_;
v___y_4043_ = v___y_4053_;
v___y_4044_ = v___x_4059_;
goto v___jp_4039_;
}
else
{
v___y_4040_ = v___y_4054_;
v___y_4041_ = v___y_4052_;
v___y_4042_ = v___y_4051_;
v___y_4043_ = v___y_4053_;
v___y_4044_ = v___x_4056_;
goto v___jp_4039_;
}
}
v___jp_4060_:
{
uint32_t v___x_4065_; uint8_t v___x_4066_; 
v___x_4065_ = 0;
v___x_4066_ = lean_uint32_dec_eq(v_yExponent_4038_, v___x_4065_);
if (v___x_4066_ == 0)
{
uint64_t v___x_4067_; uint64_t v___x_4068_; uint64_t v___x_4069_; 
v___x_4067_ = lean_uint32_to_uint64(v___y_4063_);
v___x_4068_ = 8388608ULL;
v___x_4069_ = lean_uint64_lor(v___x_4067_, v___x_4068_);
v___y_4051_ = v___y_4062_;
v___y_4052_ = v___y_4061_;
v___y_4053_ = v___y_4064_;
v___y_4054_ = v___x_4069_;
goto v___jp_4050_;
}
else
{
uint64_t v___x_4070_; 
v___x_4070_ = lean_uint32_to_uint64(v___y_4063_);
v___y_4051_ = v___y_4062_;
v___y_4052_ = v___y_4061_;
v___y_4053_ = v___y_4064_;
v___y_4054_ = v___x_4070_;
goto v___jp_4050_;
}
}
v___jp_4071_:
{
uint32_t v___x_4073_; uint32_t v_xFraction_4074_; uint32_t v_yFraction_4075_; uint32_t v___x_4076_; uint8_t v___x_4077_; 
v___x_4073_ = 8388607;
v_xFraction_4074_ = lean_uint32_land(v_xBits_3699_, v___x_4073_);
v_yFraction_4075_ = lean_uint32_land(v_yBits_3700_, v___x_4073_);
v___x_4076_ = 0;
v___x_4077_ = lean_uint32_dec_eq(v_xExponent_4036_, v___x_4076_);
if (v___x_4077_ == 0)
{
uint64_t v___x_4078_; uint64_t v___x_4079_; uint64_t v___x_4080_; 
v___x_4078_ = lean_uint32_to_uint64(v_xFraction_4074_);
v___x_4079_ = 8388608ULL;
v___x_4080_ = lean_uint64_lor(v___x_4078_, v___x_4079_);
v___y_4061_ = v___x_4073_;
v___y_4062_ = v___y_4072_;
v___y_4063_ = v_yFraction_4075_;
v___y_4064_ = v___x_4080_;
goto v___jp_4060_;
}
else
{
uint64_t v___x_4081_; 
v___x_4081_ = lean_uint32_to_uint64(v_xFraction_4074_);
v___y_4061_ = v___x_4073_;
v___y_4062_ = v___y_4072_;
v___y_4063_ = v_yFraction_4075_;
v___y_4064_ = v___x_4081_;
goto v___jp_4060_;
}
}
v___jp_4082_:
{
uint8_t v___x_4083_; 
v___x_4083_ = 1;
v___y_4072_ = v___x_4083_;
goto v___jp_4071_;
}
v___jp_4084_:
{
uint8_t v___x_4085_; 
v___x_4085_ = 0;
v___y_4072_ = v___x_4085_;
goto v___jp_4071_;
}
v___jp_4086_:
{
if (v___y_4087_ == 0)
{
if (v___y_4088_ == 0)
{
goto v___jp_4084_;
}
else
{
goto v___jp_4082_;
}
}
else
{
if (v___y_4088_ == 0)
{
goto v___jp_4082_;
}
else
{
goto v___jp_4084_;
}
}
}
v___jp_4089_:
{
uint32_t v___x_4091_; uint32_t v___x_4092_; uint32_t v___x_4093_; uint8_t v___x_4094_; 
v___x_4091_ = 2147483648;
v___x_4092_ = lean_uint32_land(v_yBits_3700_, v___x_4091_);
v___x_4093_ = 0;
v___x_4094_ = lean_uint32_dec_eq(v___x_4092_, v___x_4093_);
if (v___x_4094_ == 0)
{
uint8_t v___x_4095_; 
v___x_4095_ = 1;
v___y_4087_ = v___y_4090_;
v___y_4088_ = v___x_4095_;
goto v___jp_4086_;
}
else
{
uint8_t v___x_4096_; 
v___x_4096_ = 0;
v___y_4087_ = v___y_4090_;
v___y_4088_ = v___x_4096_;
goto v___jp_4086_;
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_LowScale_core___boxed(lean_object* v_xBits_4103_, lean_object* v_yBits_4104_){
_start:
{
uint32_t v_xBits_boxed_4105_; uint32_t v_yBits_boxed_4106_; uint32_t v_res_4107_; lean_object* v_r_4108_; 
v_xBits_boxed_4105_ = lean_unbox_uint32(v_xBits_4103_);
lean_dec(v_xBits_4103_);
v_yBits_boxed_4106_ = lean_unbox_uint32(v_yBits_4104_);
lean_dec(v_yBits_4104_);
v_res_4107_ = lp_competition_Submission_LowScale_core(v_xBits_boxed_4105_, v_yBits_boxed_4106_);
v_r_4108_ = lean_box_uint32(v_res_4107_);
return v_r_4108_;
}
}
LEAN_EXPORT uint32_t lp_competition_Submission_LowScale_mul(uint32_t v_x_4109_, uint32_t v_y_4110_){
_start:
{
uint32_t v___y_4112_; uint32_t v___y_4116_; uint32_t v___y_4120_; uint32_t v___y_4121_; uint32_t v___y_4122_; uint8_t v___y_4126_; uint64_t v___y_4127_; uint32_t v___y_4128_; uint64_t v___y_4129_; uint32_t v___y_4141_; uint32_t v___y_4142_; uint32_t v___y_4143_; uint32_t v___y_4144_; uint32_t v___y_4145_; uint32_t v___y_4146_; uint8_t v___y_4153_; uint32_t v___y_4154_; uint32_t v___y_4155_; uint32_t v___y_4156_; uint32_t v___y_4157_; uint32_t v___y_4158_; uint64_t v___y_4162_; uint8_t v___y_4163_; uint32_t v___y_4164_; uint32_t v___y_4165_; uint32_t v___y_4166_; uint64_t v___y_4167_; uint64_t v___y_4168_; uint8_t v___y_4178_; uint64_t v___y_4179_; uint8_t v___y_4180_; uint32_t v___y_4181_; uint32_t v___y_4182_; uint32_t v___y_4183_; uint64_t v___y_4184_; uint64_t v___y_4185_; uint64_t v___y_4192_; uint8_t v___y_4193_; uint32_t v___y_4194_; uint32_t v___y_4195_; uint64_t v___y_4196_; uint32_t v___y_4197_; uint64_t v___y_4198_; uint8_t v___y_4204_; uint64_t v___y_4205_; uint32_t v___y_4206_; uint64_t v___y_4207_; uint32_t v___y_4208_; uint64_t v___y_4209_; uint32_t v___y_4210_; uint64_t v___y_4211_; uint8_t v___y_4266_; uint64_t v___y_4267_; uint32_t v___y_4268_; uint64_t v___y_4269_; uint32_t v___y_4270_; uint64_t v___y_4271_; uint32_t v___y_4272_; uint64_t v___y_4273_; uint64_t v___y_4274_; uint64_t v___y_4280_; uint8_t v___y_4281_; uint32_t v___y_4282_; uint64_t v___y_4283_; uint64_t v___y_4284_; uint32_t v___y_4285_; uint64_t v___y_4286_; uint64_t v___y_4287_; uint32_t v___y_4288_; uint64_t v___y_4289_; uint64_t v___y_4290_; uint8_t v___y_4295_; uint64_t v___y_4296_; uint32_t v___y_4297_; uint64_t v___y_4298_; uint64_t v___y_4299_; uint32_t v___y_4300_; uint64_t v___y_4301_; uint32_t v___y_4302_; uint64_t v___y_4303_; uint64_t v___y_4308_; uint8_t v___y_4309_; uint64_t v___y_4310_; uint32_t v___y_4311_; uint64_t v___y_4312_; uint64_t v___y_4313_; uint32_t v___y_4314_; uint64_t v___y_4315_; uint64_t v___y_4316_; uint32_t v___y_4317_; uint64_t v___y_4318_; uint8_t v___y_4323_; uint64_t v___y_4324_; uint32_t v___y_4325_; uint64_t v___y_4326_; uint32_t v___y_4327_; uint64_t v___y_4328_; uint64_t v___y_4329_; uint32_t v___y_4330_; uint64_t v___y_4331_; uint64_t v___y_4336_; uint8_t v___y_4337_; uint32_t v___y_4338_; uint64_t v___y_4339_; uint64_t v___y_4340_; uint64_t v___y_4341_; uint32_t v___y_4342_; uint64_t v___y_4343_; uint64_t v___y_4344_; uint32_t v___y_4345_; uint64_t v___y_4346_; uint8_t v___y_4351_; uint64_t v___y_4352_; uint32_t v___y_4353_; uint64_t v___y_4354_; uint64_t v___y_4355_; uint32_t v___y_4356_; uint64_t v___y_4357_; uint32_t v___y_4358_; uint64_t v___y_4359_; uint64_t v___y_4364_; uint8_t v___y_4365_; uint32_t v___y_4366_; uint64_t v___y_4367_; uint64_t v___y_4368_; uint32_t v___y_4369_; uint64_t v___y_4370_; uint64_t v___y_4371_; uint32_t v___y_4372_; uint64_t v___y_4373_; uint64_t v___y_4374_; uint8_t v___y_4379_; uint64_t v___y_4380_; uint32_t v___y_4381_; uint64_t v___y_4382_; uint32_t v___y_4383_; uint64_t v___y_4384_; uint32_t v___y_4385_; uint64_t v___y_4386_; uint64_t v___y_4387_; uint64_t v___y_4392_; uint8_t v___y_4393_; uint32_t v___y_4394_; uint64_t v___y_4395_; uint32_t v___y_4396_; uint64_t v___y_4397_; uint64_t v___y_4398_; uint32_t v___y_4399_; uint64_t v___y_4400_; uint8_t v___y_4404_; uint32_t v___y_4405_; uint64_t v___y_4406_; uint32_t v___y_4407_; uint64_t v___y_4408_; uint32_t v___y_4409_; uint32_t v___y_4418_; uint32_t v___y_4419_; uint32_t v___y_4420_; uint8_t v___y_4424_; uint64_t v___y_4425_; uint32_t v___y_4426_; uint64_t v___y_4427_; uint8_t v___y_4439_; uint32_t v___y_4440_; uint64_t v___y_4441_; uint32_t v___y_4442_; uint64_t v___y_4443_; uint64_t v___y_4444_; uint32_t v___y_4445_; uint64_t v___y_4446_; uint8_t v___y_4480_; uint32_t v___y_4481_; uint64_t v___y_4482_; uint32_t v___y_4483_; uint64_t v___y_4484_; uint32_t v___y_4485_; uint32_t v___y_4486_; uint64_t v___y_4487_; uint8_t v___y_4494_; uint32_t v___y_4495_; uint64_t v___y_4496_; uint32_t v___y_4497_; uint32_t v___y_4498_; uint32_t v___y_4499_; uint32_t v___y_4500_; uint64_t v___y_4501_; uint8_t v___y_4508_; uint32_t v___y_4509_; uint32_t v___y_4510_; uint32_t v___y_4511_; uint32_t v___y_4512_; uint32_t v___y_4513_; uint32_t v___y_4514_; uint64_t v___y_4515_; uint32_t v___y_4523_; uint32_t v___y_4524_; uint32_t v___y_4525_; uint32_t v___y_4526_; uint8_t v___y_4527_; uint32_t v___y_4538_; uint32_t v___y_4539_; uint32_t v___y_4540_; uint32_t v___y_4541_; uint32_t v___y_4544_; uint32_t v___y_4545_; uint8_t v___y_4546_; uint8_t v___y_4547_; uint32_t v___y_4548_; uint32_t v___y_4549_; uint8_t v___y_4550_; uint32_t v___y_4552_; uint32_t v___y_4553_; uint8_t v___y_4554_; uint32_t v___y_4555_; uint32_t v___y_4556_; uint8_t v___y_4557_; uint8_t v___y_4564_; uint32_t v___x_4581_; uint32_t v___x_4582_; uint32_t v___x_4583_; uint8_t v___x_4584_; 
v___x_4581_ = 4278190080;
v___x_4582_ = 1;
v___x_4583_ = lean_uint32_shift_left(v_x_4109_, v___x_4582_);
v___x_4584_ = lean_uint32_dec_le(v___x_4581_, v___x_4583_);
if (v___x_4584_ == 0)
{
uint32_t v___x_4585_; uint8_t v___x_4586_; 
v___x_4585_ = lean_uint32_shift_left(v_y_4110_, v___x_4582_);
v___x_4586_ = lean_uint32_dec_le(v___x_4581_, v___x_4585_);
v___y_4564_ = v___x_4586_;
goto v___jp_4563_;
}
else
{
v___y_4564_ = v___x_4584_;
goto v___jp_4563_;
}
v___jp_4111_:
{
uint32_t v___x_4113_; uint32_t v___x_4114_; 
v___x_4113_ = 8388608;
v___x_4114_ = lean_uint32_lor(v___y_4112_, v___x_4113_);
return v___x_4114_;
}
v___jp_4115_:
{
uint32_t v___x_4117_; uint32_t v___x_4118_; 
v___x_4117_ = 8388608;
v___x_4118_ = lean_uint32_lor(v___y_4116_, v___x_4117_);
return v___x_4118_;
}
v___jp_4119_:
{
uint32_t v___x_4123_; uint32_t v___x_4124_; 
v___x_4123_ = lean_uint32_land(v___y_4120_, v___y_4121_);
v___x_4124_ = lean_uint32_lor(v___y_4122_, v___x_4123_);
return v___x_4124_;
}
v___jp_4125_:
{
uint8_t v___x_4130_; 
v___x_4130_ = lean_uint64_dec_eq(v___y_4129_, v___y_4127_);
if (v___x_4130_ == 0)
{
uint64_t v___x_4131_; uint8_t v___x_4132_; 
v___x_4131_ = 8388608ULL;
v___x_4132_ = lean_uint64_dec_eq(v___y_4129_, v___x_4131_);
if (v___x_4132_ == 0)
{
uint32_t v___x_4133_; 
v___x_4133_ = lean_uint64_to_uint32(v___y_4129_);
if (v___y_4126_ == 0)
{
uint32_t v___x_4134_; 
v___x_4134_ = 0;
v___y_4120_ = v___x_4133_;
v___y_4121_ = v___y_4128_;
v___y_4122_ = v___x_4134_;
goto v___jp_4119_;
}
else
{
uint32_t v___x_4135_; 
v___x_4135_ = 2147483648;
v___y_4120_ = v___x_4133_;
v___y_4121_ = v___y_4128_;
v___y_4122_ = v___x_4135_;
goto v___jp_4119_;
}
}
else
{
if (v___y_4126_ == 0)
{
uint32_t v___x_4136_; 
v___x_4136_ = 0;
v___y_4112_ = v___x_4136_;
goto v___jp_4111_;
}
else
{
uint32_t v___x_4137_; 
v___x_4137_ = 2147483648;
v___y_4112_ = v___x_4137_;
goto v___jp_4111_;
}
}
}
else
{
if (v___y_4126_ == 0)
{
uint32_t v___x_4138_; 
v___x_4138_ = 0;
return v___x_4138_;
}
else
{
uint32_t v___x_4139_; 
v___x_4139_ = 2147483648;
return v___x_4139_;
}
}
}
v___jp_4140_:
{
uint32_t v___x_4147_; uint32_t v___x_4148_; uint32_t v___x_4149_; uint32_t v___x_4150_; uint32_t v___x_4151_; 
v___x_4147_ = lean_uint32_land(v___y_4144_, v___y_4143_);
v___x_4148_ = lean_uint32_shift_left(v___x_4147_, v___y_4141_);
v___x_4149_ = lean_uint32_lor(v___y_4146_, v___x_4148_);
v___x_4150_ = lean_uint32_land(v___y_4142_, v___y_4145_);
v___x_4151_ = lean_uint32_lor(v___x_4149_, v___x_4150_);
return v___x_4151_;
}
v___jp_4152_:
{
if (v___y_4153_ == 0)
{
uint32_t v___x_4159_; 
v___x_4159_ = 0;
v___y_4141_ = v___y_4154_;
v___y_4142_ = v___y_4158_;
v___y_4143_ = v___y_4155_;
v___y_4144_ = v___y_4156_;
v___y_4145_ = v___y_4157_;
v___y_4146_ = v___x_4159_;
goto v___jp_4140_;
}
else
{
uint32_t v___x_4160_; 
v___x_4160_ = 2147483648;
v___y_4141_ = v___y_4154_;
v___y_4142_ = v___y_4158_;
v___y_4143_ = v___y_4155_;
v___y_4144_ = v___y_4156_;
v___y_4145_ = v___y_4157_;
v___y_4146_ = v___x_4160_;
goto v___jp_4140_;
}
}
v___jp_4161_:
{
uint64_t v___x_4169_; uint64_t v_encodedExponent_4170_; uint32_t v___x_4171_; uint64_t v___x_4172_; uint8_t v___x_4173_; 
v___x_4169_ = 171ULL;
v_encodedExponent_4170_ = lean_uint64_sub(v___y_4167_, v___x_4169_);
v___x_4171_ = lean_uint64_to_uint32(v_encodedExponent_4170_);
v___x_4172_ = 8388608ULL;
v___x_4173_ = lean_uint64_dec_lt(v___y_4168_, v___x_4172_);
if (v___x_4173_ == 0)
{
uint64_t v___x_4174_; uint32_t v___x_4175_; 
v___x_4174_ = lean_uint64_sub(v___y_4168_, v___x_4172_);
v___x_4175_ = lean_uint64_to_uint32(v___x_4174_);
v___y_4153_ = v___y_4163_;
v___y_4154_ = v___y_4164_;
v___y_4155_ = v___y_4165_;
v___y_4156_ = v___x_4171_;
v___y_4157_ = v___y_4166_;
v___y_4158_ = v___x_4175_;
goto v___jp_4152_;
}
else
{
uint32_t v___x_4176_; 
v___x_4176_ = lean_uint64_to_uint32(v___y_4162_);
v___y_4153_ = v___y_4163_;
v___y_4154_ = v___y_4164_;
v___y_4155_ = v___y_4165_;
v___y_4156_ = v___x_4171_;
v___y_4157_ = v___y_4166_;
v___y_4158_ = v___x_4176_;
goto v___jp_4152_;
}
}
v___jp_4177_:
{
uint64_t v___x_4186_; uint8_t v___x_4187_; 
v___x_4186_ = 425ULL;
v___x_4187_ = lean_uint64_dec_lt(v___x_4186_, v___y_4185_);
if (v___x_4187_ == 0)
{
if (v___y_4180_ == 0)
{
v___y_4162_ = v___y_4179_;
v___y_4163_ = v___y_4178_;
v___y_4164_ = v___y_4181_;
v___y_4165_ = v___y_4182_;
v___y_4166_ = v___y_4183_;
v___y_4167_ = v___y_4185_;
v___y_4168_ = v___y_4184_;
goto v___jp_4161_;
}
else
{
uint64_t v___x_4188_; 
v___x_4188_ = 8388608ULL;
v___y_4162_ = v___y_4179_;
v___y_4163_ = v___y_4178_;
v___y_4164_ = v___y_4181_;
v___y_4165_ = v___y_4182_;
v___y_4166_ = v___y_4183_;
v___y_4167_ = v___y_4185_;
v___y_4168_ = v___x_4188_;
goto v___jp_4161_;
}
}
else
{
if (v___y_4178_ == 0)
{
uint32_t v___x_4189_; 
v___x_4189_ = 2139095040;
return v___x_4189_;
}
else
{
uint32_t v___x_4190_; 
v___x_4190_ = 4286578688;
return v___x_4190_;
}
}
}
v___jp_4191_:
{
uint64_t v___x_4199_; uint8_t v_carry_4200_; 
v___x_4199_ = 16777216ULL;
v_carry_4200_ = lean_uint64_dec_eq(v___y_4198_, v___x_4199_);
if (v_carry_4200_ == 0)
{
v___y_4178_ = v___y_4193_;
v___y_4179_ = v___y_4192_;
v___y_4180_ = v_carry_4200_;
v___y_4181_ = v___y_4194_;
v___y_4182_ = v___y_4195_;
v___y_4183_ = v___y_4197_;
v___y_4184_ = v___y_4198_;
v___y_4185_ = v___y_4196_;
goto v___jp_4177_;
}
else
{
uint64_t v___x_4201_; uint64_t v___x_4202_; 
v___x_4201_ = 1ULL;
v___x_4202_ = lean_uint64_add(v___y_4196_, v___x_4201_);
v___y_4178_ = v___y_4193_;
v___y_4179_ = v___y_4192_;
v___y_4180_ = v_carry_4200_;
v___y_4181_ = v___y_4194_;
v___y_4182_ = v___y_4195_;
v___y_4183_ = v___y_4197_;
v___y_4184_ = v___y_4198_;
v___y_4185_ = v___x_4202_;
goto v___jp_4177_;
}
}
v___jp_4203_:
{
uint64_t v_position_4212_; uint64_t v___x_4213_; uint8_t v___x_4214_; 
v_position_4212_ = lean_uint64_add(v___y_4211_, v___y_4207_);
v___x_4213_ = 172ULL;
v___x_4214_ = lean_uint64_dec_lt(v_position_4212_, v___x_4213_);
if (v___x_4214_ == 0)
{
uint64_t v___x_4215_; uint8_t v___x_4216_; 
v___x_4215_ = 23ULL;
v___x_4216_ = lean_uint64_dec_lt(v___y_4211_, v___x_4215_);
if (v___x_4216_ == 0)
{
uint64_t v___x_4217_; uint8_t v___x_4218_; 
v___x_4217_ = lean_uint64_sub(v___y_4211_, v___x_4215_);
v___x_4218_ = lean_uint64_dec_eq(v___x_4217_, v___y_4205_);
if (v___x_4218_ == 0)
{
uint64_t v___x_4219_; uint8_t v___x_4220_; 
v___x_4219_ = 64ULL;
v___x_4220_ = lean_uint64_dec_lt(v___x_4217_, v___x_4219_);
if (v___x_4220_ == 0)
{
uint8_t v___x_4221_; 
v___x_4221_ = lean_uint64_dec_eq(v___x_4217_, v___x_4219_);
if (v___x_4221_ == 0)
{
v___y_4192_ = v___y_4205_;
v___y_4193_ = v___y_4204_;
v___y_4194_ = v___y_4206_;
v___y_4195_ = v___y_4208_;
v___y_4196_ = v_position_4212_;
v___y_4197_ = v___y_4210_;
v___y_4198_ = v___y_4205_;
goto v___jp_4191_;
}
else
{
uint64_t v___x_4222_; uint8_t v___x_4223_; 
v___x_4222_ = 9223372036854775808ULL;
v___x_4223_ = lean_uint64_dec_lt(v___x_4222_, v___y_4209_);
if (v___x_4223_ == 0)
{
v___y_4192_ = v___y_4205_;
v___y_4193_ = v___y_4204_;
v___y_4194_ = v___y_4206_;
v___y_4195_ = v___y_4208_;
v___y_4196_ = v_position_4212_;
v___y_4197_ = v___y_4210_;
v___y_4198_ = v___y_4205_;
goto v___jp_4191_;
}
else
{
uint64_t v___x_4224_; 
v___x_4224_ = 1ULL;
v___y_4192_ = v___y_4205_;
v___y_4193_ = v___y_4204_;
v___y_4194_ = v___y_4206_;
v___y_4195_ = v___y_4208_;
v___y_4196_ = v_position_4212_;
v___y_4197_ = v___y_4210_;
v___y_4198_ = v___x_4224_;
goto v___jp_4191_;
}
}
}
else
{
uint64_t v_quotient_4225_; uint64_t v___x_4226_; uint64_t v___x_4227_; uint64_t v___x_4228_; uint64_t v_remainder_4229_; uint64_t v___x_4230_; uint64_t v_half_4231_; uint8_t v___x_4232_; 
v_quotient_4225_ = lean_uint64_shift_right(v___y_4209_, v___x_4217_);
v___x_4226_ = 1ULL;
v___x_4227_ = lean_uint64_shift_left(v___x_4226_, v___x_4217_);
v___x_4228_ = lean_uint64_sub(v___x_4227_, v___x_4226_);
v_remainder_4229_ = lean_uint64_land(v___y_4209_, v___x_4228_);
v___x_4230_ = lean_uint64_sub(v___x_4217_, v___x_4226_);
v_half_4231_ = lean_uint64_shift_left(v___x_4226_, v___x_4230_);
v___x_4232_ = lean_uint64_dec_lt(v_remainder_4229_, v_half_4231_);
if (v___x_4232_ == 0)
{
uint8_t v___x_4233_; 
v___x_4233_ = lean_uint64_dec_lt(v_half_4231_, v_remainder_4229_);
if (v___x_4233_ == 0)
{
uint64_t v___x_4234_; uint8_t v___x_4235_; 
v___x_4234_ = lean_uint64_land(v_quotient_4225_, v___x_4226_);
v___x_4235_ = lean_uint64_dec_eq(v___x_4234_, v___y_4205_);
if (v___x_4235_ == 0)
{
uint64_t v___x_4236_; 
v___x_4236_ = lean_uint64_add(v_quotient_4225_, v___x_4226_);
v___y_4192_ = v___y_4205_;
v___y_4193_ = v___y_4204_;
v___y_4194_ = v___y_4206_;
v___y_4195_ = v___y_4208_;
v___y_4196_ = v_position_4212_;
v___y_4197_ = v___y_4210_;
v___y_4198_ = v___x_4236_;
goto v___jp_4191_;
}
else
{
v___y_4192_ = v___y_4205_;
v___y_4193_ = v___y_4204_;
v___y_4194_ = v___y_4206_;
v___y_4195_ = v___y_4208_;
v___y_4196_ = v_position_4212_;
v___y_4197_ = v___y_4210_;
v___y_4198_ = v_quotient_4225_;
goto v___jp_4191_;
}
}
else
{
uint64_t v___x_4237_; 
v___x_4237_ = lean_uint64_add(v_quotient_4225_, v___x_4226_);
v___y_4192_ = v___y_4205_;
v___y_4193_ = v___y_4204_;
v___y_4194_ = v___y_4206_;
v___y_4195_ = v___y_4208_;
v___y_4196_ = v_position_4212_;
v___y_4197_ = v___y_4210_;
v___y_4198_ = v___x_4237_;
goto v___jp_4191_;
}
}
else
{
v___y_4192_ = v___y_4205_;
v___y_4193_ = v___y_4204_;
v___y_4194_ = v___y_4206_;
v___y_4195_ = v___y_4208_;
v___y_4196_ = v_position_4212_;
v___y_4197_ = v___y_4210_;
v___y_4198_ = v_quotient_4225_;
goto v___jp_4191_;
}
}
}
else
{
v___y_4192_ = v___y_4205_;
v___y_4193_ = v___y_4204_;
v___y_4194_ = v___y_4206_;
v___y_4195_ = v___y_4208_;
v___y_4196_ = v_position_4212_;
v___y_4197_ = v___y_4210_;
v___y_4198_ = v___y_4209_;
goto v___jp_4191_;
}
}
else
{
uint64_t v___x_4238_; uint64_t v___x_4239_; 
v___x_4238_ = lean_uint64_sub(v___x_4215_, v___y_4211_);
v___x_4239_ = lean_uint64_shift_left(v___y_4209_, v___x_4238_);
v___y_4192_ = v___y_4205_;
v___y_4193_ = v___y_4204_;
v___y_4194_ = v___y_4206_;
v___y_4195_ = v___y_4208_;
v___y_4196_ = v_position_4212_;
v___y_4197_ = v___y_4210_;
v___y_4198_ = v___x_4239_;
goto v___jp_4191_;
}
}
else
{
uint64_t v___x_4240_; uint8_t v___x_4241_; 
v___x_4240_ = 149ULL;
v___x_4241_ = lean_uint64_dec_lt(v___y_4207_, v___x_4240_);
if (v___x_4241_ == 0)
{
uint64_t v___x_4242_; uint64_t v___x_4243_; 
v___x_4242_ = lean_uint64_sub(v___y_4207_, v___x_4240_);
v___x_4243_ = lean_uint64_shift_left(v___y_4209_, v___x_4242_);
v___y_4126_ = v___y_4204_;
v___y_4127_ = v___y_4205_;
v___y_4128_ = v___y_4210_;
v___y_4129_ = v___x_4243_;
goto v___jp_4125_;
}
else
{
uint64_t v___x_4244_; uint8_t v___x_4245_; 
v___x_4244_ = lean_uint64_sub(v___x_4240_, v___y_4207_);
v___x_4245_ = lean_uint64_dec_eq(v___x_4244_, v___y_4205_);
if (v___x_4245_ == 0)
{
uint64_t v___x_4246_; uint8_t v___x_4247_; 
v___x_4246_ = 64ULL;
v___x_4247_ = lean_uint64_dec_lt(v___x_4244_, v___x_4246_);
if (v___x_4247_ == 0)
{
uint8_t v___x_4248_; 
v___x_4248_ = lean_uint64_dec_eq(v___x_4244_, v___x_4246_);
if (v___x_4248_ == 0)
{
v___y_4126_ = v___y_4204_;
v___y_4127_ = v___y_4205_;
v___y_4128_ = v___y_4210_;
v___y_4129_ = v___y_4205_;
goto v___jp_4125_;
}
else
{
uint64_t v___x_4249_; uint8_t v___x_4250_; 
v___x_4249_ = 9223372036854775808ULL;
v___x_4250_ = lean_uint64_dec_lt(v___x_4249_, v___y_4209_);
if (v___x_4250_ == 0)
{
v___y_4126_ = v___y_4204_;
v___y_4127_ = v___y_4205_;
v___y_4128_ = v___y_4210_;
v___y_4129_ = v___y_4205_;
goto v___jp_4125_;
}
else
{
uint64_t v___x_4251_; 
v___x_4251_ = 1ULL;
v___y_4126_ = v___y_4204_;
v___y_4127_ = v___y_4205_;
v___y_4128_ = v___y_4210_;
v___y_4129_ = v___x_4251_;
goto v___jp_4125_;
}
}
}
else
{
uint64_t v_quotient_4252_; uint64_t v___x_4253_; uint64_t v___x_4254_; uint64_t v___x_4255_; uint64_t v_remainder_4256_; uint64_t v___x_4257_; uint64_t v_half_4258_; uint8_t v___x_4259_; 
v_quotient_4252_ = lean_uint64_shift_right(v___y_4209_, v___x_4244_);
v___x_4253_ = 1ULL;
v___x_4254_ = lean_uint64_shift_left(v___x_4253_, v___x_4244_);
v___x_4255_ = lean_uint64_sub(v___x_4254_, v___x_4253_);
v_remainder_4256_ = lean_uint64_land(v___y_4209_, v___x_4255_);
v___x_4257_ = lean_uint64_sub(v___x_4244_, v___x_4253_);
v_half_4258_ = lean_uint64_shift_left(v___x_4253_, v___x_4257_);
v___x_4259_ = lean_uint64_dec_lt(v_remainder_4256_, v_half_4258_);
if (v___x_4259_ == 0)
{
uint8_t v___x_4260_; 
v___x_4260_ = lean_uint64_dec_lt(v_half_4258_, v_remainder_4256_);
if (v___x_4260_ == 0)
{
uint64_t v___x_4261_; uint8_t v___x_4262_; 
v___x_4261_ = lean_uint64_land(v_quotient_4252_, v___x_4253_);
v___x_4262_ = lean_uint64_dec_eq(v___x_4261_, v___y_4205_);
if (v___x_4262_ == 0)
{
uint64_t v___x_4263_; 
v___x_4263_ = lean_uint64_add(v_quotient_4252_, v___x_4253_);
v___y_4126_ = v___y_4204_;
v___y_4127_ = v___y_4205_;
v___y_4128_ = v___y_4210_;
v___y_4129_ = v___x_4263_;
goto v___jp_4125_;
}
else
{
v___y_4126_ = v___y_4204_;
v___y_4127_ = v___y_4205_;
v___y_4128_ = v___y_4210_;
v___y_4129_ = v_quotient_4252_;
goto v___jp_4125_;
}
}
else
{
uint64_t v___x_4264_; 
v___x_4264_ = lean_uint64_add(v_quotient_4252_, v___x_4253_);
v___y_4126_ = v___y_4204_;
v___y_4127_ = v___y_4205_;
v___y_4128_ = v___y_4210_;
v___y_4129_ = v___x_4264_;
goto v___jp_4125_;
}
}
else
{
v___y_4126_ = v___y_4204_;
v___y_4127_ = v___y_4205_;
v___y_4128_ = v___y_4210_;
v___y_4129_ = v_quotient_4252_;
goto v___jp_4125_;
}
}
}
else
{
v___y_4126_ = v___y_4204_;
v___y_4127_ = v___y_4205_;
v___y_4128_ = v___y_4210_;
v___y_4129_ = v___y_4209_;
goto v___jp_4125_;
}
}
}
}
v___jp_4265_:
{
uint64_t v___x_4275_; uint64_t v___x_4276_; uint8_t v___x_4277_; 
v___x_4275_ = 1ULL;
v___x_4276_ = lean_uint64_shift_right(v___y_4273_, v___x_4275_);
v___x_4277_ = lean_uint64_dec_eq(v___x_4276_, v___y_4267_);
if (v___x_4277_ == 0)
{
uint64_t v___x_4278_; 
v___x_4278_ = lean_uint64_add(v___y_4274_, v___x_4275_);
v___y_4204_ = v___y_4266_;
v___y_4205_ = v___y_4267_;
v___y_4206_ = v___y_4268_;
v___y_4207_ = v___y_4269_;
v___y_4208_ = v___y_4270_;
v___y_4209_ = v___y_4271_;
v___y_4210_ = v___y_4272_;
v___y_4211_ = v___x_4278_;
goto v___jp_4203_;
}
else
{
v___y_4204_ = v___y_4266_;
v___y_4205_ = v___y_4267_;
v___y_4206_ = v___y_4268_;
v___y_4207_ = v___y_4269_;
v___y_4208_ = v___y_4270_;
v___y_4209_ = v___y_4271_;
v___y_4210_ = v___y_4272_;
v___y_4211_ = v___y_4274_;
goto v___jp_4203_;
}
}
v___jp_4279_:
{
uint64_t v___x_4291_; uint8_t v___x_4292_; 
v___x_4291_ = lean_uint64_shift_right(v___y_4283_, v___y_4286_);
v___x_4292_ = lean_uint64_dec_eq(v___x_4291_, v___y_4280_);
if (v___x_4292_ == 0)
{
uint64_t v___x_4293_; 
v___x_4293_ = lean_uint64_add(v___y_4289_, v___y_4286_);
v___y_4266_ = v___y_4281_;
v___y_4267_ = v___y_4280_;
v___y_4268_ = v___y_4282_;
v___y_4269_ = v___y_4284_;
v___y_4270_ = v___y_4285_;
v___y_4271_ = v___y_4287_;
v___y_4272_ = v___y_4288_;
v___y_4273_ = v___y_4290_;
v___y_4274_ = v___x_4293_;
goto v___jp_4265_;
}
else
{
v___y_4266_ = v___y_4281_;
v___y_4267_ = v___y_4280_;
v___y_4268_ = v___y_4282_;
v___y_4269_ = v___y_4284_;
v___y_4270_ = v___y_4285_;
v___y_4271_ = v___y_4287_;
v___y_4272_ = v___y_4288_;
v___y_4273_ = v___y_4290_;
v___y_4274_ = v___y_4289_;
goto v___jp_4265_;
}
}
v___jp_4294_:
{
uint64_t v___x_4304_; uint64_t v___x_4305_; uint8_t v___x_4306_; 
v___x_4304_ = 2ULL;
v___x_4305_ = lean_uint64_shift_right(v___y_4299_, v___x_4304_);
v___x_4306_ = lean_uint64_dec_eq(v___x_4305_, v___y_4296_);
if (v___x_4306_ == 0)
{
v___y_4280_ = v___y_4296_;
v___y_4281_ = v___y_4295_;
v___y_4282_ = v___y_4297_;
v___y_4283_ = v___y_4299_;
v___y_4284_ = v___y_4298_;
v___y_4285_ = v___y_4300_;
v___y_4286_ = v___x_4304_;
v___y_4287_ = v___y_4301_;
v___y_4288_ = v___y_4302_;
v___y_4289_ = v___y_4303_;
v___y_4290_ = v___x_4305_;
goto v___jp_4279_;
}
else
{
v___y_4280_ = v___y_4296_;
v___y_4281_ = v___y_4295_;
v___y_4282_ = v___y_4297_;
v___y_4283_ = v___y_4299_;
v___y_4284_ = v___y_4298_;
v___y_4285_ = v___y_4300_;
v___y_4286_ = v___x_4304_;
v___y_4287_ = v___y_4301_;
v___y_4288_ = v___y_4302_;
v___y_4289_ = v___y_4303_;
v___y_4290_ = v___y_4299_;
goto v___jp_4279_;
}
}
v___jp_4307_:
{
uint64_t v___x_4319_; uint8_t v___x_4320_; 
v___x_4319_ = lean_uint64_shift_right(v___y_4313_, v___y_4316_);
v___x_4320_ = lean_uint64_dec_eq(v___x_4319_, v___y_4308_);
if (v___x_4320_ == 0)
{
uint64_t v___x_4321_; 
v___x_4321_ = lean_uint64_add(v___y_4310_, v___y_4316_);
v___y_4295_ = v___y_4309_;
v___y_4296_ = v___y_4308_;
v___y_4297_ = v___y_4311_;
v___y_4298_ = v___y_4312_;
v___y_4299_ = v___y_4318_;
v___y_4300_ = v___y_4314_;
v___y_4301_ = v___y_4315_;
v___y_4302_ = v___y_4317_;
v___y_4303_ = v___x_4321_;
goto v___jp_4294_;
}
else
{
v___y_4295_ = v___y_4309_;
v___y_4296_ = v___y_4308_;
v___y_4297_ = v___y_4311_;
v___y_4298_ = v___y_4312_;
v___y_4299_ = v___y_4318_;
v___y_4300_ = v___y_4314_;
v___y_4301_ = v___y_4315_;
v___y_4302_ = v___y_4317_;
v___y_4303_ = v___y_4310_;
goto v___jp_4294_;
}
}
v___jp_4322_:
{
uint64_t v___x_4332_; uint64_t v___x_4333_; uint8_t v___x_4334_; 
v___x_4332_ = 4ULL;
v___x_4333_ = lean_uint64_shift_right(v___y_4328_, v___x_4332_);
v___x_4334_ = lean_uint64_dec_eq(v___x_4333_, v___y_4324_);
if (v___x_4334_ == 0)
{
v___y_4308_ = v___y_4324_;
v___y_4309_ = v___y_4323_;
v___y_4310_ = v___y_4331_;
v___y_4311_ = v___y_4325_;
v___y_4312_ = v___y_4326_;
v___y_4313_ = v___y_4328_;
v___y_4314_ = v___y_4327_;
v___y_4315_ = v___y_4329_;
v___y_4316_ = v___x_4332_;
v___y_4317_ = v___y_4330_;
v___y_4318_ = v___x_4333_;
goto v___jp_4307_;
}
else
{
v___y_4308_ = v___y_4324_;
v___y_4309_ = v___y_4323_;
v___y_4310_ = v___y_4331_;
v___y_4311_ = v___y_4325_;
v___y_4312_ = v___y_4326_;
v___y_4313_ = v___y_4328_;
v___y_4314_ = v___y_4327_;
v___y_4315_ = v___y_4329_;
v___y_4316_ = v___x_4332_;
v___y_4317_ = v___y_4330_;
v___y_4318_ = v___y_4328_;
goto v___jp_4307_;
}
}
v___jp_4335_:
{
uint64_t v___x_4347_; uint8_t v___x_4348_; 
v___x_4347_ = lean_uint64_shift_right(v___y_4340_, v___y_4339_);
v___x_4348_ = lean_uint64_dec_eq(v___x_4347_, v___y_4336_);
if (v___x_4348_ == 0)
{
uint64_t v___x_4349_; 
v___x_4349_ = lean_uint64_add(v___y_4344_, v___y_4339_);
v___y_4323_ = v___y_4337_;
v___y_4324_ = v___y_4336_;
v___y_4325_ = v___y_4338_;
v___y_4326_ = v___y_4341_;
v___y_4327_ = v___y_4342_;
v___y_4328_ = v___y_4346_;
v___y_4329_ = v___y_4343_;
v___y_4330_ = v___y_4345_;
v___y_4331_ = v___x_4349_;
goto v___jp_4322_;
}
else
{
v___y_4323_ = v___y_4337_;
v___y_4324_ = v___y_4336_;
v___y_4325_ = v___y_4338_;
v___y_4326_ = v___y_4341_;
v___y_4327_ = v___y_4342_;
v___y_4328_ = v___y_4346_;
v___y_4329_ = v___y_4343_;
v___y_4330_ = v___y_4345_;
v___y_4331_ = v___y_4344_;
goto v___jp_4322_;
}
}
v___jp_4350_:
{
uint64_t v___x_4360_; uint64_t v___x_4361_; uint8_t v___x_4362_; 
v___x_4360_ = 8ULL;
v___x_4361_ = lean_uint64_shift_right(v___y_4355_, v___x_4360_);
v___x_4362_ = lean_uint64_dec_eq(v___x_4361_, v___y_4352_);
if (v___x_4362_ == 0)
{
v___y_4336_ = v___y_4352_;
v___y_4337_ = v___y_4351_;
v___y_4338_ = v___y_4353_;
v___y_4339_ = v___x_4360_;
v___y_4340_ = v___y_4355_;
v___y_4341_ = v___y_4354_;
v___y_4342_ = v___y_4356_;
v___y_4343_ = v___y_4357_;
v___y_4344_ = v___y_4359_;
v___y_4345_ = v___y_4358_;
v___y_4346_ = v___x_4361_;
goto v___jp_4335_;
}
else
{
v___y_4336_ = v___y_4352_;
v___y_4337_ = v___y_4351_;
v___y_4338_ = v___y_4353_;
v___y_4339_ = v___x_4360_;
v___y_4340_ = v___y_4355_;
v___y_4341_ = v___y_4354_;
v___y_4342_ = v___y_4356_;
v___y_4343_ = v___y_4357_;
v___y_4344_ = v___y_4359_;
v___y_4345_ = v___y_4358_;
v___y_4346_ = v___y_4355_;
goto v___jp_4335_;
}
}
v___jp_4363_:
{
uint64_t v___x_4375_; uint8_t v___x_4376_; 
v___x_4375_ = lean_uint64_shift_right(v___y_4373_, v___y_4367_);
v___x_4376_ = lean_uint64_dec_eq(v___x_4375_, v___y_4364_);
if (v___x_4376_ == 0)
{
uint64_t v___x_4377_; 
v___x_4377_ = lean_uint64_add(v___y_4371_, v___y_4367_);
v___y_4351_ = v___y_4365_;
v___y_4352_ = v___y_4364_;
v___y_4353_ = v___y_4366_;
v___y_4354_ = v___y_4368_;
v___y_4355_ = v___y_4374_;
v___y_4356_ = v___y_4369_;
v___y_4357_ = v___y_4370_;
v___y_4358_ = v___y_4372_;
v___y_4359_ = v___x_4377_;
goto v___jp_4350_;
}
else
{
v___y_4351_ = v___y_4365_;
v___y_4352_ = v___y_4364_;
v___y_4353_ = v___y_4366_;
v___y_4354_ = v___y_4368_;
v___y_4355_ = v___y_4374_;
v___y_4356_ = v___y_4369_;
v___y_4357_ = v___y_4370_;
v___y_4358_ = v___y_4372_;
v___y_4359_ = v___y_4371_;
goto v___jp_4350_;
}
}
v___jp_4378_:
{
uint64_t v___x_4388_; uint64_t v___x_4389_; uint8_t v___x_4390_; 
v___x_4388_ = 16ULL;
v___x_4389_ = lean_uint64_shift_right(v___y_4386_, v___x_4388_);
v___x_4390_ = lean_uint64_dec_eq(v___x_4389_, v___y_4380_);
if (v___x_4390_ == 0)
{
v___y_4364_ = v___y_4380_;
v___y_4365_ = v___y_4379_;
v___y_4366_ = v___y_4381_;
v___y_4367_ = v___x_4388_;
v___y_4368_ = v___y_4382_;
v___y_4369_ = v___y_4383_;
v___y_4370_ = v___y_4384_;
v___y_4371_ = v___y_4387_;
v___y_4372_ = v___y_4385_;
v___y_4373_ = v___y_4386_;
v___y_4374_ = v___x_4389_;
goto v___jp_4363_;
}
else
{
v___y_4364_ = v___y_4380_;
v___y_4365_ = v___y_4379_;
v___y_4366_ = v___y_4381_;
v___y_4367_ = v___x_4388_;
v___y_4368_ = v___y_4382_;
v___y_4369_ = v___y_4383_;
v___y_4370_ = v___y_4384_;
v___y_4371_ = v___y_4387_;
v___y_4372_ = v___y_4385_;
v___y_4373_ = v___y_4386_;
v___y_4374_ = v___y_4386_;
goto v___jp_4363_;
}
}
v___jp_4391_:
{
uint64_t v___x_4401_; uint8_t v___x_4402_; 
v___x_4401_ = lean_uint64_shift_right(v___y_4398_, v___y_4397_);
v___x_4402_ = lean_uint64_dec_eq(v___x_4401_, v___y_4392_);
if (v___x_4402_ == 0)
{
v___y_4379_ = v___y_4393_;
v___y_4380_ = v___y_4392_;
v___y_4381_ = v___y_4394_;
v___y_4382_ = v___y_4395_;
v___y_4383_ = v___y_4396_;
v___y_4384_ = v___y_4398_;
v___y_4385_ = v___y_4399_;
v___y_4386_ = v___y_4400_;
v___y_4387_ = v___y_4397_;
goto v___jp_4378_;
}
else
{
v___y_4379_ = v___y_4393_;
v___y_4380_ = v___y_4392_;
v___y_4381_ = v___y_4394_;
v___y_4382_ = v___y_4395_;
v___y_4383_ = v___y_4396_;
v___y_4384_ = v___y_4398_;
v___y_4385_ = v___y_4399_;
v___y_4386_ = v___y_4400_;
v___y_4387_ = v___y_4392_;
goto v___jp_4378_;
}
}
v___jp_4403_:
{
uint64_t v___x_4410_; uint8_t v___x_4411_; 
v___x_4410_ = 0ULL;
v___x_4411_ = lean_uint64_dec_eq(v___y_4408_, v___x_4410_);
if (v___x_4411_ == 0)
{
uint64_t v___x_4412_; uint64_t v___x_4413_; uint8_t v___x_4414_; 
v___x_4412_ = 32ULL;
v___x_4413_ = lean_uint64_shift_right(v___y_4408_, v___x_4412_);
v___x_4414_ = lean_uint64_dec_eq(v___x_4413_, v___x_4410_);
if (v___x_4414_ == 0)
{
v___y_4392_ = v___x_4410_;
v___y_4393_ = v___y_4404_;
v___y_4394_ = v___y_4405_;
v___y_4395_ = v___y_4406_;
v___y_4396_ = v___y_4407_;
v___y_4397_ = v___x_4412_;
v___y_4398_ = v___y_4408_;
v___y_4399_ = v___y_4409_;
v___y_4400_ = v___x_4413_;
goto v___jp_4391_;
}
else
{
v___y_4392_ = v___x_4410_;
v___y_4393_ = v___y_4404_;
v___y_4394_ = v___y_4405_;
v___y_4395_ = v___y_4406_;
v___y_4396_ = v___y_4407_;
v___y_4397_ = v___x_4412_;
v___y_4398_ = v___y_4408_;
v___y_4399_ = v___y_4409_;
v___y_4400_ = v___y_4408_;
goto v___jp_4391_;
}
}
else
{
if (v___y_4404_ == 0)
{
uint32_t v___x_4415_; 
v___x_4415_ = 0;
return v___x_4415_;
}
else
{
uint32_t v___x_4416_; 
v___x_4416_ = 2147483648;
return v___x_4416_;
}
}
}
v___jp_4417_:
{
uint32_t v___x_4421_; uint32_t v___x_4422_; 
v___x_4421_ = lean_uint32_land(v___y_4418_, v___y_4419_);
v___x_4422_ = lean_uint32_lor(v___y_4420_, v___x_4421_);
return v___x_4422_;
}
v___jp_4423_:
{
uint8_t v___x_4428_; 
v___x_4428_ = lean_uint64_dec_eq(v___y_4427_, v___y_4425_);
if (v___x_4428_ == 0)
{
uint64_t v___x_4429_; uint8_t v___x_4430_; 
v___x_4429_ = 8388608ULL;
v___x_4430_ = lean_uint64_dec_eq(v___y_4427_, v___x_4429_);
if (v___x_4430_ == 0)
{
uint32_t v___x_4431_; 
v___x_4431_ = lean_uint64_to_uint32(v___y_4427_);
if (v___y_4424_ == 0)
{
uint32_t v___x_4432_; 
v___x_4432_ = 0;
v___y_4418_ = v___x_4431_;
v___y_4419_ = v___y_4426_;
v___y_4420_ = v___x_4432_;
goto v___jp_4417_;
}
else
{
uint32_t v___x_4433_; 
v___x_4433_ = 2147483648;
v___y_4418_ = v___x_4431_;
v___y_4419_ = v___y_4426_;
v___y_4420_ = v___x_4433_;
goto v___jp_4417_;
}
}
else
{
if (v___y_4424_ == 0)
{
uint32_t v___x_4434_; 
v___x_4434_ = 0;
v___y_4116_ = v___x_4434_;
goto v___jp_4115_;
}
else
{
uint32_t v___x_4435_; 
v___x_4435_ = 2147483648;
v___y_4116_ = v___x_4435_;
goto v___jp_4115_;
}
}
}
else
{
if (v___y_4424_ == 0)
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
v___jp_4438_:
{
uint64_t v___x_4447_; uint64_t v___x_4448_; uint64_t v___x_4449_; uint8_t v___x_4450_; 
v___x_4447_ = lean_uint64_mul(v___y_4441_, v___y_4443_);
v___x_4448_ = lean_uint64_add(v___y_4444_, v___y_4446_);
v___x_4449_ = 281474976710656ULL;
v___x_4450_ = lean_uint64_dec_lt(v___x_4447_, v___x_4449_);
if (v___x_4450_ == 0)
{
v___y_4404_ = v___y_4439_;
v___y_4405_ = v___y_4440_;
v___y_4406_ = v___x_4448_;
v___y_4407_ = v___y_4442_;
v___y_4408_ = v___x_4447_;
v___y_4409_ = v___y_4445_;
goto v___jp_4403_;
}
else
{
uint64_t v___x_4451_; uint8_t v___x_4452_; 
v___x_4451_ = 123ULL;
v___x_4452_ = lean_uint64_dec_le(v___x_4448_, v___x_4451_);
if (v___x_4452_ == 0)
{
v___y_4404_ = v___y_4439_;
v___y_4405_ = v___y_4440_;
v___y_4406_ = v___x_4448_;
v___y_4407_ = v___y_4442_;
v___y_4408_ = v___x_4447_;
v___y_4409_ = v___y_4445_;
goto v___jp_4403_;
}
else
{
uint64_t v___x_4453_; uint8_t v___x_4454_; 
v___x_4453_ = 0ULL;
v___x_4454_ = lean_uint64_dec_eq(v___x_4447_, v___x_4453_);
if (v___x_4454_ == 0)
{
uint64_t v___x_4455_; uint64_t v___x_4456_; uint8_t v___x_4457_; 
v___x_4455_ = 149ULL;
v___x_4456_ = lean_uint64_sub(v___x_4455_, v___x_4448_);
v___x_4457_ = lean_uint64_dec_eq(v___x_4456_, v___x_4453_);
if (v___x_4457_ == 0)
{
uint64_t v___x_4458_; uint8_t v___x_4459_; 
v___x_4458_ = 64ULL;
v___x_4459_ = lean_uint64_dec_lt(v___x_4456_, v___x_4458_);
if (v___x_4459_ == 0)
{
uint8_t v___x_4460_; 
v___x_4460_ = lean_uint64_dec_eq(v___x_4456_, v___x_4458_);
if (v___x_4460_ == 0)
{
v___y_4424_ = v___y_4439_;
v___y_4425_ = v___x_4453_;
v___y_4426_ = v___y_4445_;
v___y_4427_ = v___x_4453_;
goto v___jp_4423_;
}
else
{
uint64_t v___x_4461_; uint8_t v___x_4462_; 
v___x_4461_ = 9223372036854775808ULL;
v___x_4462_ = lean_uint64_dec_lt(v___x_4461_, v___x_4447_);
if (v___x_4462_ == 0)
{
v___y_4424_ = v___y_4439_;
v___y_4425_ = v___x_4453_;
v___y_4426_ = v___y_4445_;
v___y_4427_ = v___x_4453_;
goto v___jp_4423_;
}
else
{
uint64_t v___x_4463_; 
v___x_4463_ = 1ULL;
v___y_4424_ = v___y_4439_;
v___y_4425_ = v___x_4453_;
v___y_4426_ = v___y_4445_;
v___y_4427_ = v___x_4463_;
goto v___jp_4423_;
}
}
}
else
{
uint64_t v_quotient_4464_; uint64_t v___x_4465_; uint64_t v___x_4466_; uint64_t v___x_4467_; uint64_t v_remainder_4468_; uint64_t v___x_4469_; uint64_t v_half_4470_; uint8_t v___x_4471_; 
v_quotient_4464_ = lean_uint64_shift_right(v___x_4447_, v___x_4456_);
v___x_4465_ = 1ULL;
v___x_4466_ = lean_uint64_shift_left(v___x_4465_, v___x_4456_);
v___x_4467_ = lean_uint64_sub(v___x_4466_, v___x_4465_);
v_remainder_4468_ = lean_uint64_land(v___x_4447_, v___x_4467_);
v___x_4469_ = lean_uint64_sub(v___x_4456_, v___x_4465_);
v_half_4470_ = lean_uint64_shift_left(v___x_4465_, v___x_4469_);
v___x_4471_ = lean_uint64_dec_lt(v_remainder_4468_, v_half_4470_);
if (v___x_4471_ == 0)
{
uint8_t v___x_4472_; 
v___x_4472_ = lean_uint64_dec_lt(v_half_4470_, v_remainder_4468_);
if (v___x_4472_ == 0)
{
uint64_t v___x_4473_; uint8_t v___x_4474_; 
v___x_4473_ = lean_uint64_land(v_quotient_4464_, v___x_4465_);
v___x_4474_ = lean_uint64_dec_eq(v___x_4473_, v___x_4453_);
if (v___x_4474_ == 0)
{
uint64_t v___x_4475_; 
v___x_4475_ = lean_uint64_add(v_quotient_4464_, v___x_4465_);
v___y_4424_ = v___y_4439_;
v___y_4425_ = v___x_4453_;
v___y_4426_ = v___y_4445_;
v___y_4427_ = v___x_4475_;
goto v___jp_4423_;
}
else
{
v___y_4424_ = v___y_4439_;
v___y_4425_ = v___x_4453_;
v___y_4426_ = v___y_4445_;
v___y_4427_ = v_quotient_4464_;
goto v___jp_4423_;
}
}
else
{
uint64_t v___x_4476_; 
v___x_4476_ = lean_uint64_add(v_quotient_4464_, v___x_4465_);
v___y_4424_ = v___y_4439_;
v___y_4425_ = v___x_4453_;
v___y_4426_ = v___y_4445_;
v___y_4427_ = v___x_4476_;
goto v___jp_4423_;
}
}
else
{
v___y_4424_ = v___y_4439_;
v___y_4425_ = v___x_4453_;
v___y_4426_ = v___y_4445_;
v___y_4427_ = v_quotient_4464_;
goto v___jp_4423_;
}
}
}
else
{
v___y_4424_ = v___y_4439_;
v___y_4425_ = v___x_4453_;
v___y_4426_ = v___y_4445_;
v___y_4427_ = v___x_4447_;
goto v___jp_4423_;
}
}
else
{
if (v___y_4439_ == 0)
{
uint32_t v___x_4477_; 
v___x_4477_ = 0;
return v___x_4477_;
}
else
{
uint32_t v___x_4478_; 
v___x_4478_ = 2147483648;
return v___x_4478_;
}
}
}
}
}
v___jp_4479_:
{
uint64_t v___x_4488_; uint64_t v___x_4489_; uint8_t v___x_4490_; 
v___x_4488_ = lean_uint32_to_uint64(v___y_4486_);
v___x_4489_ = 0ULL;
v___x_4490_ = lean_uint64_dec_eq(v___x_4488_, v___x_4489_);
if (v___x_4490_ == 0)
{
uint64_t v___x_4491_; uint64_t v___x_4492_; 
v___x_4491_ = 1ULL;
v___x_4492_ = lean_uint64_sub(v___x_4488_, v___x_4491_);
v___y_4439_ = v___y_4480_;
v___y_4440_ = v___y_4481_;
v___y_4441_ = v___y_4482_;
v___y_4442_ = v___y_4483_;
v___y_4443_ = v___y_4484_;
v___y_4444_ = v___y_4487_;
v___y_4445_ = v___y_4485_;
v___y_4446_ = v___x_4492_;
goto v___jp_4438_;
}
else
{
v___y_4439_ = v___y_4480_;
v___y_4440_ = v___y_4481_;
v___y_4441_ = v___y_4482_;
v___y_4442_ = v___y_4483_;
v___y_4443_ = v___y_4484_;
v___y_4444_ = v___y_4487_;
v___y_4445_ = v___y_4485_;
v___y_4446_ = v___x_4489_;
goto v___jp_4438_;
}
}
v___jp_4493_:
{
uint64_t v___x_4502_; uint64_t v___x_4503_; uint8_t v___x_4504_; 
v___x_4502_ = lean_uint32_to_uint64(v___y_4498_);
v___x_4503_ = 0ULL;
v___x_4504_ = lean_uint64_dec_eq(v___x_4502_, v___x_4503_);
if (v___x_4504_ == 0)
{
uint64_t v___x_4505_; uint64_t v___x_4506_; 
v___x_4505_ = 1ULL;
v___x_4506_ = lean_uint64_sub(v___x_4502_, v___x_4505_);
v___y_4480_ = v___y_4494_;
v___y_4481_ = v___y_4495_;
v___y_4482_ = v___y_4496_;
v___y_4483_ = v___y_4497_;
v___y_4484_ = v___y_4501_;
v___y_4485_ = v___y_4499_;
v___y_4486_ = v___y_4500_;
v___y_4487_ = v___x_4506_;
goto v___jp_4479_;
}
else
{
v___y_4480_ = v___y_4494_;
v___y_4481_ = v___y_4495_;
v___y_4482_ = v___y_4496_;
v___y_4483_ = v___y_4497_;
v___y_4484_ = v___y_4501_;
v___y_4485_ = v___y_4499_;
v___y_4486_ = v___y_4500_;
v___y_4487_ = v___x_4503_;
goto v___jp_4479_;
}
}
v___jp_4507_:
{
uint32_t v___x_4516_; uint8_t v___x_4517_; 
v___x_4516_ = 0;
v___x_4517_ = lean_uint32_dec_eq(v___y_4514_, v___x_4516_);
if (v___x_4517_ == 0)
{
uint64_t v___x_4518_; uint64_t v___x_4519_; uint64_t v___x_4520_; 
v___x_4518_ = lean_uint32_to_uint64(v___y_4510_);
v___x_4519_ = 8388608ULL;
v___x_4520_ = lean_uint64_lor(v___x_4518_, v___x_4519_);
v___y_4494_ = v___y_4508_;
v___y_4495_ = v___y_4509_;
v___y_4496_ = v___y_4515_;
v___y_4497_ = v___y_4511_;
v___y_4498_ = v___y_4513_;
v___y_4499_ = v___y_4512_;
v___y_4500_ = v___y_4514_;
v___y_4501_ = v___x_4520_;
goto v___jp_4493_;
}
else
{
uint64_t v___x_4521_; 
v___x_4521_ = lean_uint32_to_uint64(v___y_4510_);
v___y_4494_ = v___y_4508_;
v___y_4495_ = v___y_4509_;
v___y_4496_ = v___y_4515_;
v___y_4497_ = v___y_4511_;
v___y_4498_ = v___y_4513_;
v___y_4499_ = v___y_4512_;
v___y_4500_ = v___y_4514_;
v___y_4501_ = v___x_4521_;
goto v___jp_4493_;
}
}
v___jp_4522_:
{
uint32_t v___x_4528_; uint32_t v_xFraction_4529_; uint32_t v_yFraction_4530_; uint32_t v___x_4531_; uint8_t v___x_4532_; 
v___x_4528_ = 8388607;
v_xFraction_4529_ = lean_uint32_land(v_x_4109_, v___x_4528_);
v_yFraction_4530_ = lean_uint32_land(v_y_4110_, v___x_4528_);
v___x_4531_ = 0;
v___x_4532_ = lean_uint32_dec_eq(v___y_4525_, v___x_4531_);
if (v___x_4532_ == 0)
{
uint64_t v___x_4533_; uint64_t v___x_4534_; uint64_t v___x_4535_; 
v___x_4533_ = lean_uint32_to_uint64(v_xFraction_4529_);
v___x_4534_ = 8388608ULL;
v___x_4535_ = lean_uint64_lor(v___x_4533_, v___x_4534_);
v___y_4508_ = v___y_4527_;
v___y_4509_ = v___y_4523_;
v___y_4510_ = v_yFraction_4530_;
v___y_4511_ = v___y_4524_;
v___y_4512_ = v___x_4528_;
v___y_4513_ = v___y_4525_;
v___y_4514_ = v___y_4526_;
v___y_4515_ = v___x_4535_;
goto v___jp_4507_;
}
else
{
uint64_t v___x_4536_; 
v___x_4536_ = lean_uint32_to_uint64(v_xFraction_4529_);
v___y_4508_ = v___y_4527_;
v___y_4509_ = v___y_4523_;
v___y_4510_ = v_yFraction_4530_;
v___y_4511_ = v___y_4524_;
v___y_4512_ = v___x_4528_;
v___y_4513_ = v___y_4525_;
v___y_4514_ = v___y_4526_;
v___y_4515_ = v___x_4536_;
goto v___jp_4507_;
}
}
v___jp_4537_:
{
uint8_t v___x_4542_; 
v___x_4542_ = 1;
v___y_4523_ = v___y_4538_;
v___y_4524_ = v___y_4539_;
v___y_4525_ = v___y_4540_;
v___y_4526_ = v___y_4541_;
v___y_4527_ = v___x_4542_;
goto v___jp_4522_;
}
v___jp_4543_:
{
if (v___y_4546_ == 0)
{
if (v___y_4550_ == 0)
{
v___y_4523_ = v___y_4544_;
v___y_4524_ = v___y_4545_;
v___y_4525_ = v___y_4548_;
v___y_4526_ = v___y_4549_;
v___y_4527_ = v___y_4547_;
goto v___jp_4522_;
}
else
{
v___y_4538_ = v___y_4544_;
v___y_4539_ = v___y_4545_;
v___y_4540_ = v___y_4548_;
v___y_4541_ = v___y_4549_;
goto v___jp_4537_;
}
}
else
{
if (v___y_4550_ == 0)
{
v___y_4538_ = v___y_4544_;
v___y_4539_ = v___y_4545_;
v___y_4540_ = v___y_4548_;
v___y_4541_ = v___y_4549_;
goto v___jp_4537_;
}
else
{
v___y_4523_ = v___y_4544_;
v___y_4524_ = v___y_4545_;
v___y_4525_ = v___y_4548_;
v___y_4526_ = v___y_4549_;
v___y_4527_ = v___y_4547_;
goto v___jp_4522_;
}
}
}
v___jp_4551_:
{
uint32_t v___x_4558_; uint32_t v___x_4559_; uint32_t v___x_4560_; uint8_t v___x_4561_; 
v___x_4558_ = 2147483648;
v___x_4559_ = lean_uint32_land(v_y_4110_, v___x_4558_);
v___x_4560_ = 0;
v___x_4561_ = lean_uint32_dec_eq(v___x_4559_, v___x_4560_);
if (v___x_4561_ == 0)
{
uint8_t v___x_4562_; 
v___x_4562_ = 1;
v___y_4544_ = v___y_4552_;
v___y_4545_ = v___y_4553_;
v___y_4546_ = v___y_4557_;
v___y_4547_ = v___y_4554_;
v___y_4548_ = v___y_4555_;
v___y_4549_ = v___y_4556_;
v___y_4550_ = v___x_4562_;
goto v___jp_4543_;
}
else
{
v___y_4544_ = v___y_4552_;
v___y_4545_ = v___y_4553_;
v___y_4546_ = v___y_4557_;
v___y_4547_ = v___y_4554_;
v___y_4548_ = v___y_4555_;
v___y_4549_ = v___y_4556_;
v___y_4550_ = v___y_4554_;
goto v___jp_4543_;
}
}
v___jp_4563_:
{
if (v___y_4564_ == 0)
{
uint32_t v___x_4565_; uint32_t v___x_4566_; uint32_t v___x_4567_; uint32_t v_xExponent_4568_; uint32_t v___x_4569_; uint32_t v_yExponent_4570_; uint32_t v___x_4571_; uint32_t v___x_4572_; uint32_t v___x_4573_; uint8_t v___x_4574_; 
v___x_4565_ = 23;
v___x_4566_ = lean_uint32_shift_right(v_x_4109_, v___x_4565_);
v___x_4567_ = 255;
v_xExponent_4568_ = lean_uint32_land(v___x_4566_, v___x_4567_);
v___x_4569_ = lean_uint32_shift_right(v_y_4110_, v___x_4565_);
v_yExponent_4570_ = lean_uint32_land(v___x_4569_, v___x_4567_);
v___x_4571_ = 2147483648;
v___x_4572_ = lean_uint32_land(v_x_4109_, v___x_4571_);
v___x_4573_ = 0;
v___x_4574_ = lean_uint32_dec_eq(v___x_4572_, v___x_4573_);
if (v___x_4574_ == 0)
{
uint8_t v___x_4575_; 
v___x_4575_ = 1;
v___y_4552_ = v___x_4565_;
v___y_4553_ = v___x_4567_;
v___y_4554_ = v___y_4564_;
v___y_4555_ = v_xExponent_4568_;
v___y_4556_ = v_yExponent_4570_;
v___y_4557_ = v___x_4575_;
goto v___jp_4551_;
}
else
{
v___y_4552_ = v___x_4565_;
v___y_4553_ = v___x_4567_;
v___y_4554_ = v___y_4564_;
v___y_4555_ = v_xExponent_4568_;
v___y_4556_ = v_yExponent_4570_;
v___y_4557_ = v___y_4564_;
goto v___jp_4551_;
}
}
else
{
lean_object* v___x_4576_; lean_object* v___x_4577_; lean_object* v___x_4578_; lean_object* v___x_4579_; uint32_t v___x_4580_; 
v___x_4576_ = ((lean_object*)(lp_competition_Submission_TunedAdd_Fmt___closed__0));
v___x_4577_ = lean_uint32_to_nat(v_x_4109_);
v___x_4578_ = lean_uint32_to_nat(v_y_4110_);
v___x_4579_ = lp_floatlib_FloatLib_Floats_Formats_BinaryInterchange_Model_MulBackend_word(v___x_4576_, v___x_4577_, v___x_4578_);
v___x_4580_ = lean_uint32_of_nat(v___x_4579_);
lean_dec(v___x_4579_);
return v___x_4580_;
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_LowScale_mul___boxed(lean_object* v_x_4587_, lean_object* v_y_4588_){
_start:
{
uint32_t v_x_boxed_4589_; uint32_t v_y_boxed_4590_; uint32_t v_res_4591_; lean_object* v_r_4592_; 
v_x_boxed_4589_ = lean_unbox_uint32(v_x_4587_);
lean_dec(v_x_4587_);
v_y_boxed_4590_ = lean_unbox_uint32(v_y_4588_);
lean_dec(v_y_4588_);
v_res_4591_ = lp_competition_Submission_LowScale_mul(v_x_boxed_4589_, v_y_boxed_4590_);
v_r_4592_ = lean_box_uint32(v_res_4591_);
return v_r_4592_;
}
}
LEAN_EXPORT uint32_t lp_competition_Submission_addR6Parent(uint32_t v_x_4593_, uint32_t v_y_4594_){
_start:
{
float v___y_4596_; float v___y_4597_; float v___y_4601_; uint8_t v___y_4602_; float v___y_4617_; uint8_t v___y_4627_; uint32_t v___x_4641_; uint32_t v___x_4642_; uint32_t v___x_4643_; uint32_t v___x_4644_; uint8_t v___x_4645_; 
v___x_4641_ = 23;
v___x_4642_ = lean_uint32_shift_right(v_x_4593_, v___x_4641_);
v___x_4643_ = 255;
v___x_4644_ = lean_uint32_land(v___x_4642_, v___x_4643_);
v___x_4645_ = lean_uint32_dec_eq(v___x_4644_, v___x_4643_);
if (v___x_4645_ == 0)
{
uint32_t v___x_4646_; uint32_t v___x_4647_; uint8_t v___x_4648_; 
v___x_4646_ = lean_uint32_shift_right(v_y_4594_, v___x_4641_);
v___x_4647_ = lean_uint32_land(v___x_4646_, v___x_4643_);
v___x_4648_ = lean_uint32_dec_eq(v___x_4647_, v___x_4643_);
if (v___x_4648_ == 0)
{
uint32_t v___x_4649_; uint32_t v_a_4650_; uint32_t v___x_4651_; uint32_t v___x_4652_; uint32_t v___x_4653_; uint8_t v___x_4654_; 
v___x_4649_ = 2147483647;
v_a_4650_ = lean_uint32_land(v_x_4593_, v___x_4649_);
v___x_4651_ = 201326591;
v___x_4652_ = 1;
v___x_4653_ = lean_uint32_sub(v_a_4650_, v___x_4652_);
v___x_4654_ = lean_uint32_dec_le(v___x_4651_, v___x_4653_);
if (v___x_4654_ == 0)
{
v___y_4627_ = v___x_4654_;
goto v___jp_4626_;
}
else
{
uint32_t v___x_4655_; uint8_t v___x_4656_; 
v___x_4655_ = 2139095040;
v___x_4656_ = lean_uint32_dec_lt(v_a_4650_, v___x_4655_);
v___y_4627_ = v___x_4656_;
goto v___jp_4626_;
}
}
else
{
uint32_t v___x_4657_; 
v___x_4657_ = lp_competition_Submission_TunedAdd_add(v_x_4593_, v_y_4594_);
return v___x_4657_;
}
}
else
{
uint32_t v___x_4658_; 
v___x_4658_ = lp_competition_Submission_TunedAdd_add(v_x_4593_, v_y_4594_);
return v___x_4658_;
}
v___jp_4595_:
{
float v___x_4598_; uint32_t v___x_4599_; 
v___x_4598_ = lean_float32_add(v___y_4596_, v___y_4597_);
v___x_4599_ = lean_float32_to_bits(v___x_4598_);
return v___x_4599_;
}
v___jp_4600_:
{
if (v___y_4602_ == 0)
{
float v___x_4603_; 
v___x_4603_ = lean_float32_of_bits(v_y_4594_);
v___y_4596_ = v___y_4601_;
v___y_4597_ = v___x_4603_;
goto v___jp_4595_;
}
else
{
uint32_t v___x_4604_; uint32_t v___x_4605_; uint32_t v___x_4606_; uint32_t v___x_4607_; float v___x_4608_; lean_object* v___x_4609_; uint32_t v___x_4610_; uint32_t v___x_4611_; lean_object* v___x_4612_; lean_object* v___x_4613_; float v___x_4614_; float v___x_4615_; 
v___x_4604_ = 8388607;
v___x_4605_ = lean_uint32_land(v_y_4594_, v___x_4604_);
v___x_4606_ = 8388608;
v___x_4607_ = lean_uint32_lor(v___x_4605_, v___x_4606_);
v___x_4608_ = lean_uint32_to_float32(v___x_4607_);
v___x_4609_ = lp_competition_R2W01b_scaleTable;
v___x_4610_ = 23;
v___x_4611_ = lean_uint32_shift_right(v_y_4594_, v___x_4610_);
v___x_4612_ = lean_uint32_to_nat(v___x_4611_);
v___x_4613_ = lean_array_fget_borrowed(v___x_4609_, v___x_4612_);
lean_dec(v___x_4612_);
v___x_4614_ = lean_unbox_float32(v___x_4613_);
v___x_4615_ = lean_float32_mul(v___x_4608_, v___x_4614_);
v___y_4596_ = v___y_4601_;
v___y_4597_ = v___x_4615_;
goto v___jp_4595_;
}
}
v___jp_4616_:
{
uint32_t v___x_4618_; uint32_t v_a_4619_; uint32_t v___x_4620_; uint32_t v___x_4621_; uint32_t v___x_4622_; uint8_t v___x_4623_; 
v___x_4618_ = 2147483647;
v_a_4619_ = lean_uint32_land(v_y_4594_, v___x_4618_);
v___x_4620_ = 201326591;
v___x_4621_ = 1;
v___x_4622_ = lean_uint32_sub(v_a_4619_, v___x_4621_);
v___x_4623_ = lean_uint32_dec_le(v___x_4620_, v___x_4622_);
if (v___x_4623_ == 0)
{
v___y_4601_ = v___y_4617_;
v___y_4602_ = v___x_4623_;
goto v___jp_4600_;
}
else
{
uint32_t v___x_4624_; uint8_t v___x_4625_; 
v___x_4624_ = 2139095040;
v___x_4625_ = lean_uint32_dec_lt(v_a_4619_, v___x_4624_);
v___y_4601_ = v___y_4617_;
v___y_4602_ = v___x_4625_;
goto v___jp_4600_;
}
}
v___jp_4626_:
{
if (v___y_4627_ == 0)
{
float v___x_4628_; 
v___x_4628_ = lean_float32_of_bits(v_x_4593_);
v___y_4617_ = v___x_4628_;
goto v___jp_4616_;
}
else
{
uint32_t v___x_4629_; uint32_t v___x_4630_; uint32_t v___x_4631_; uint32_t v___x_4632_; float v___x_4633_; lean_object* v___x_4634_; uint32_t v___x_4635_; uint32_t v___x_4636_; lean_object* v___x_4637_; lean_object* v___x_4638_; float v___x_4639_; float v___x_4640_; 
v___x_4629_ = 8388607;
v___x_4630_ = lean_uint32_land(v_x_4593_, v___x_4629_);
v___x_4631_ = 8388608;
v___x_4632_ = lean_uint32_lor(v___x_4630_, v___x_4631_);
v___x_4633_ = lean_uint32_to_float32(v___x_4632_);
v___x_4634_ = lp_competition_R2W01b_scaleTable;
v___x_4635_ = 23;
v___x_4636_ = lean_uint32_shift_right(v_x_4593_, v___x_4635_);
v___x_4637_ = lean_uint32_to_nat(v___x_4636_);
v___x_4638_ = lean_array_fget_borrowed(v___x_4634_, v___x_4637_);
lean_dec(v___x_4637_);
v___x_4639_ = lean_unbox_float32(v___x_4638_);
v___x_4640_ = lean_float32_mul(v___x_4633_, v___x_4639_);
v___y_4617_ = v___x_4640_;
goto v___jp_4616_;
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_addR6Parent___boxed(lean_object* v_x_4659_, lean_object* v_y_4660_){
_start:
{
uint32_t v_x_boxed_4661_; uint32_t v_y_boxed_4662_; uint32_t v_res_4663_; lean_object* v_r_4664_; 
v_x_boxed_4661_ = lean_unbox_uint32(v_x_4659_);
lean_dec(v_x_4659_);
v_y_boxed_4662_ = lean_unbox_uint32(v_y_4660_);
lean_dec(v_y_4660_);
v_res_4663_ = lp_competition_Submission_addR6Parent(v_x_boxed_4661_, v_y_boxed_4662_);
v_r_4664_ = lean_box_uint32(v_res_4663_);
return v_r_4664_;
}
}
LEAN_EXPORT uint8_t lp_competition_Submission_R6NormalAdd_normalOK(uint32_t v_u_4665_){
_start:
{
uint32_t v___x_4666_; uint32_t v___x_4667_; uint32_t v___x_4668_; uint32_t v___x_4669_; uint32_t v___x_4670_; uint8_t v___x_4671_; 
v___x_4666_ = 2147483647;
v___x_4667_ = lean_uint32_land(v_u_4665_, v___x_4666_);
v___x_4668_ = 201326592;
v___x_4669_ = lean_uint32_sub(v___x_4667_, v___x_4668_);
v___x_4670_ = 1937768448;
v___x_4671_ = lean_uint32_dec_lt(v___x_4669_, v___x_4670_);
return v___x_4671_;
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_R6NormalAdd_normalOK___boxed(lean_object* v_u_4672_){
_start:
{
uint32_t v_u_boxed_4673_; uint8_t v_res_4674_; lean_object* v_r_4675_; 
v_u_boxed_4673_ = lean_unbox_uint32(v_u_4672_);
lean_dec(v_u_4672_);
v_res_4674_ = lp_competition_Submission_R6NormalAdd_normalOK(v_u_boxed_4673_);
v_r_4675_ = lean_box(v_res_4674_);
return v_r_4675_;
}
}
LEAN_EXPORT uint32_t lp_competition_Submission_add(uint32_t v_x_4676_, uint32_t v_y_4677_){
_start:
{
float v___y_4679_; float v___y_4680_; float v___y_4684_; uint8_t v___y_4685_; float v___y_4700_; uint8_t v___y_4710_; uint8_t v___y_4725_; uint32_t v___x_4766_; uint32_t v___x_4767_; uint32_t v___x_4768_; uint32_t v___x_4769_; uint32_t v___x_4770_; uint8_t v___x_4771_; 
v___x_4766_ = 2147483647;
v___x_4767_ = lean_uint32_land(v_x_4676_, v___x_4766_);
v___x_4768_ = 201326592;
v___x_4769_ = lean_uint32_sub(v___x_4767_, v___x_4768_);
v___x_4770_ = 1937768448;
v___x_4771_ = lean_uint32_dec_lt(v___x_4769_, v___x_4770_);
if (v___x_4771_ == 0)
{
v___y_4725_ = v___x_4771_;
goto v___jp_4724_;
}
else
{
uint32_t v___x_4772_; uint32_t v___x_4773_; uint8_t v___x_4774_; 
v___x_4772_ = lean_uint32_land(v_y_4677_, v___x_4766_);
v___x_4773_ = lean_uint32_sub(v___x_4772_, v___x_4768_);
v___x_4774_ = lean_uint32_dec_lt(v___x_4773_, v___x_4770_);
v___y_4725_ = v___x_4774_;
goto v___jp_4724_;
}
v___jp_4678_:
{
float v___x_4681_; uint32_t v___x_4682_; 
v___x_4681_ = lean_float32_add(v___y_4679_, v___y_4680_);
v___x_4682_ = lean_float32_to_bits(v___x_4681_);
return v___x_4682_;
}
v___jp_4683_:
{
if (v___y_4685_ == 0)
{
float v___x_4686_; 
v___x_4686_ = lean_float32_of_bits(v_y_4677_);
v___y_4679_ = v___y_4684_;
v___y_4680_ = v___x_4686_;
goto v___jp_4678_;
}
else
{
uint32_t v___x_4687_; uint32_t v___x_4688_; uint32_t v___x_4689_; uint32_t v___x_4690_; float v___x_4691_; lean_object* v___x_4692_; uint32_t v___x_4693_; uint32_t v___x_4694_; lean_object* v___x_4695_; lean_object* v___x_4696_; float v___x_4697_; float v___x_4698_; 
v___x_4687_ = 8388607;
v___x_4688_ = lean_uint32_land(v_y_4677_, v___x_4687_);
v___x_4689_ = 8388608;
v___x_4690_ = lean_uint32_lor(v___x_4688_, v___x_4689_);
v___x_4691_ = lean_uint32_to_float32(v___x_4690_);
v___x_4692_ = lp_competition_R2W01b_scaleTable;
v___x_4693_ = 23;
v___x_4694_ = lean_uint32_shift_right(v_y_4677_, v___x_4693_);
v___x_4695_ = lean_uint32_to_nat(v___x_4694_);
v___x_4696_ = lean_array_fget_borrowed(v___x_4692_, v___x_4695_);
lean_dec(v___x_4695_);
v___x_4697_ = lean_unbox_float32(v___x_4696_);
v___x_4698_ = lean_float32_mul(v___x_4691_, v___x_4697_);
v___y_4679_ = v___y_4684_;
v___y_4680_ = v___x_4698_;
goto v___jp_4678_;
}
}
v___jp_4699_:
{
uint32_t v___x_4701_; uint32_t v_a_4702_; uint32_t v___x_4703_; uint32_t v___x_4704_; uint32_t v___x_4705_; uint8_t v___x_4706_; 
v___x_4701_ = 2147483647;
v_a_4702_ = lean_uint32_land(v_y_4677_, v___x_4701_);
v___x_4703_ = 201326591;
v___x_4704_ = 1;
v___x_4705_ = lean_uint32_sub(v_a_4702_, v___x_4704_);
v___x_4706_ = lean_uint32_dec_le(v___x_4703_, v___x_4705_);
if (v___x_4706_ == 0)
{
v___y_4684_ = v___y_4700_;
v___y_4685_ = v___x_4706_;
goto v___jp_4683_;
}
else
{
uint32_t v___x_4707_; uint8_t v___x_4708_; 
v___x_4707_ = 2139095040;
v___x_4708_ = lean_uint32_dec_lt(v_a_4702_, v___x_4707_);
v___y_4684_ = v___y_4700_;
v___y_4685_ = v___x_4708_;
goto v___jp_4683_;
}
}
v___jp_4709_:
{
if (v___y_4710_ == 0)
{
float v___x_4711_; 
v___x_4711_ = lean_float32_of_bits(v_x_4676_);
v___y_4700_ = v___x_4711_;
goto v___jp_4699_;
}
else
{
uint32_t v___x_4712_; uint32_t v___x_4713_; uint32_t v___x_4714_; uint32_t v___x_4715_; float v___x_4716_; lean_object* v___x_4717_; uint32_t v___x_4718_; uint32_t v___x_4719_; lean_object* v___x_4720_; lean_object* v___x_4721_; float v___x_4722_; float v___x_4723_; 
v___x_4712_ = 8388607;
v___x_4713_ = lean_uint32_land(v_x_4676_, v___x_4712_);
v___x_4714_ = 8388608;
v___x_4715_ = lean_uint32_lor(v___x_4713_, v___x_4714_);
v___x_4716_ = lean_uint32_to_float32(v___x_4715_);
v___x_4717_ = lp_competition_R2W01b_scaleTable;
v___x_4718_ = 23;
v___x_4719_ = lean_uint32_shift_right(v_x_4676_, v___x_4718_);
v___x_4720_ = lean_uint32_to_nat(v___x_4719_);
v___x_4721_ = lean_array_fget_borrowed(v___x_4717_, v___x_4720_);
lean_dec(v___x_4720_);
v___x_4722_ = lean_unbox_float32(v___x_4721_);
v___x_4723_ = lean_float32_mul(v___x_4716_, v___x_4722_);
v___y_4700_ = v___x_4723_;
goto v___jp_4699_;
}
}
v___jp_4724_:
{
if (v___y_4725_ == 0)
{
uint32_t v___x_4726_; uint32_t v___x_4727_; uint32_t v___x_4728_; uint32_t v___x_4729_; uint8_t v___x_4730_; 
v___x_4726_ = 23;
v___x_4727_ = lean_uint32_shift_right(v_x_4676_, v___x_4726_);
v___x_4728_ = 255;
v___x_4729_ = lean_uint32_land(v___x_4727_, v___x_4728_);
v___x_4730_ = lean_uint32_dec_eq(v___x_4729_, v___x_4728_);
if (v___x_4730_ == 0)
{
uint32_t v___x_4731_; uint32_t v___x_4732_; uint8_t v___x_4733_; 
v___x_4731_ = lean_uint32_shift_right(v_y_4677_, v___x_4726_);
v___x_4732_ = lean_uint32_land(v___x_4731_, v___x_4728_);
v___x_4733_ = lean_uint32_dec_eq(v___x_4732_, v___x_4728_);
if (v___x_4733_ == 0)
{
uint32_t v___x_4734_; uint32_t v_a_4735_; uint32_t v___x_4736_; uint32_t v___x_4737_; uint32_t v___x_4738_; uint8_t v___x_4739_; 
v___x_4734_ = 2147483647;
v_a_4735_ = lean_uint32_land(v_x_4676_, v___x_4734_);
v___x_4736_ = 201326591;
v___x_4737_ = 1;
v___x_4738_ = lean_uint32_sub(v_a_4735_, v___x_4737_);
v___x_4739_ = lean_uint32_dec_le(v___x_4736_, v___x_4738_);
if (v___x_4739_ == 0)
{
v___y_4710_ = v___x_4739_;
goto v___jp_4709_;
}
else
{
uint32_t v___x_4740_; uint8_t v___x_4741_; 
v___x_4740_ = 2139095040;
v___x_4741_ = lean_uint32_dec_lt(v_a_4735_, v___x_4740_);
v___y_4710_ = v___x_4741_;
goto v___jp_4709_;
}
}
else
{
uint32_t v___x_4742_; 
v___x_4742_ = lp_competition_Submission_TunedAdd_add(v_x_4676_, v_y_4677_);
return v___x_4742_;
}
}
else
{
uint32_t v___x_4743_; 
v___x_4743_ = lp_competition_Submission_TunedAdd_add(v_x_4676_, v_y_4677_);
return v___x_4743_;
}
}
else
{
uint32_t v___x_4744_; uint32_t v___x_4745_; uint32_t v___x_4746_; uint32_t v___x_4747_; float v___x_4748_; lean_object* v___x_4749_; uint32_t v___x_4750_; uint32_t v___x_4751_; lean_object* v___x_4752_; lean_object* v___x_4753_; float v___x_4754_; float v___x_4755_; uint32_t v___x_4756_; uint32_t v___x_4757_; float v___x_4758_; uint32_t v___x_4759_; lean_object* v___x_4760_; lean_object* v___x_4761_; float v___x_4762_; float v___x_4763_; float v___x_4764_; uint32_t v___x_4765_; 
v___x_4744_ = 8388607;
v___x_4745_ = lean_uint32_land(v_x_4676_, v___x_4744_);
v___x_4746_ = 8388608;
v___x_4747_ = lean_uint32_lor(v___x_4745_, v___x_4746_);
v___x_4748_ = lean_uint32_to_float32(v___x_4747_);
v___x_4749_ = lp_competition_R2W01b_scaleTable;
v___x_4750_ = 23;
v___x_4751_ = lean_uint32_shift_right(v_x_4676_, v___x_4750_);
v___x_4752_ = lean_uint32_to_nat(v___x_4751_);
v___x_4753_ = lean_array_fget_borrowed(v___x_4749_, v___x_4752_);
lean_dec(v___x_4752_);
v___x_4754_ = lean_unbox_float32(v___x_4753_);
v___x_4755_ = lean_float32_mul(v___x_4748_, v___x_4754_);
v___x_4756_ = lean_uint32_land(v_y_4677_, v___x_4744_);
v___x_4757_ = lean_uint32_lor(v___x_4756_, v___x_4746_);
v___x_4758_ = lean_uint32_to_float32(v___x_4757_);
v___x_4759_ = lean_uint32_shift_right(v_y_4677_, v___x_4750_);
v___x_4760_ = lean_uint32_to_nat(v___x_4759_);
v___x_4761_ = lean_array_fget_borrowed(v___x_4749_, v___x_4760_);
lean_dec(v___x_4760_);
v___x_4762_ = lean_unbox_float32(v___x_4761_);
v___x_4763_ = lean_float32_mul(v___x_4758_, v___x_4762_);
v___x_4764_ = lean_float32_add(v___x_4755_, v___x_4763_);
v___x_4765_ = lean_float32_to_bits(v___x_4764_);
return v___x_4765_;
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_add___boxed(lean_object* v_x_4775_, lean_object* v_y_4776_){
_start:
{
uint32_t v_x_boxed_4777_; uint32_t v_y_boxed_4778_; uint32_t v_res_4779_; lean_object* v_r_4780_; 
v_x_boxed_4777_ = lean_unbox_uint32(v_x_4775_);
lean_dec(v_x_4775_);
v_y_boxed_4778_ = lean_unbox_uint32(v_y_4776_);
lean_dec(v_y_4776_);
v_res_4779_ = lp_competition_Submission_add(v_x_boxed_4777_, v_y_boxed_4778_);
v_r_4780_ = lean_box_uint32(v_res_4779_);
return v_r_4780_;
}
}
LEAN_EXPORT uint32_t lp_competition_Submission_nativeMul(uint32_t v_x_4781_, uint32_t v_y_4782_){
_start:
{
uint32_t v___x_4783_; uint32_t v___x_4784_; uint32_t v___x_4785_; uint32_t v___x_4786_; uint8_t v___x_4787_; 
v___x_4783_ = 23;
v___x_4784_ = lean_uint32_shift_right(v_x_4781_, v___x_4783_);
v___x_4785_ = 255;
v___x_4786_ = lean_uint32_land(v___x_4784_, v___x_4785_);
v___x_4787_ = lean_uint32_dec_eq(v___x_4786_, v___x_4785_);
if (v___x_4787_ == 0)
{
uint32_t v___x_4788_; uint32_t v___x_4789_; uint8_t v___x_4790_; 
v___x_4788_ = lean_uint32_shift_right(v_y_4782_, v___x_4783_);
v___x_4789_ = lean_uint32_land(v___x_4788_, v___x_4785_);
v___x_4790_ = lean_uint32_dec_eq(v___x_4789_, v___x_4785_);
if (v___x_4790_ == 0)
{
float v___x_4791_; float v___x_4792_; float v___x_4793_; uint32_t v___x_4794_; 
v___x_4791_ = lean_float32_of_bits(v_x_4781_);
v___x_4792_ = lean_float32_of_bits(v_y_4782_);
v___x_4793_ = lean_float32_mul(v___x_4791_, v___x_4792_);
v___x_4794_ = lean_float32_to_bits(v___x_4793_);
return v___x_4794_;
}
else
{
uint32_t v___x_4795_; 
v___x_4795_ = lp_competition_Submission_FastMul_mul(v_x_4781_, v_y_4782_);
return v___x_4795_;
}
}
else
{
uint32_t v___x_4796_; 
v___x_4796_ = lp_competition_Submission_FastMul_mul(v_x_4781_, v_y_4782_);
return v___x_4796_;
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_nativeMul___boxed(lean_object* v_x_4797_, lean_object* v_y_4798_){
_start:
{
uint32_t v_x_boxed_4799_; uint32_t v_y_boxed_4800_; uint32_t v_res_4801_; lean_object* v_r_4802_; 
v_x_boxed_4799_ = lean_unbox_uint32(v_x_4797_);
lean_dec(v_x_4797_);
v_y_boxed_4800_ = lean_unbox_uint32(v_y_4798_);
lean_dec(v_y_4798_);
v_res_4801_ = lp_competition_Submission_nativeMul(v_x_boxed_4799_, v_y_boxed_4800_);
v_r_4802_ = lean_box_uint32(v_res_4801_);
return v_r_4802_;
}
}
LEAN_EXPORT uint32_t lp_competition_Submission_mul(uint32_t v_x_4803_, uint32_t v_y_4804_){
_start:
{
uint32_t v___y_4811_; uint32_t v___y_4815_; uint32_t v___y_4819_; uint32_t v___y_4820_; uint32_t v___y_4821_; uint32_t v___y_4825_; uint64_t v___y_4826_; uint8_t v___y_4827_; uint64_t v___y_4828_; uint32_t v___y_4840_; uint32_t v___y_4841_; uint32_t v___y_4842_; uint64_t v___y_4846_; uint32_t v___y_4847_; uint8_t v___y_4848_; uint64_t v___y_4849_; uint32_t v___x_4860_; uint32_t v___x_4861_; uint32_t v___x_4862_; uint32_t v___y_4864_; uint32_t v___y_4865_; uint32_t v___y_4866_; uint32_t v___y_4867_; uint32_t v___y_4874_; uint8_t v___y_4875_; uint32_t v___y_4876_; uint32_t v___y_4877_; uint32_t v___y_4881_; uint64_t v___y_4882_; uint64_t v___y_4883_; uint8_t v___y_4884_; uint64_t v___y_4885_; uint64_t v___y_4895_; uint32_t v___y_4896_; uint64_t v___y_4897_; uint8_t v___y_4898_; uint8_t v___y_4899_; uint64_t v___y_4900_; uint64_t v___y_4907_; uint32_t v___y_4908_; uint64_t v___y_4909_; uint8_t v___y_4910_; uint64_t v___y_4911_; uint64_t v___y_4917_; uint32_t v___y_4918_; uint64_t v___y_4919_; uint64_t v___y_4920_; uint8_t v___y_4921_; uint64_t v___y_4922_; uint64_t v___y_4977_; uint64_t v___y_4978_; uint32_t v___y_4979_; uint64_t v___y_4980_; uint64_t v___y_4981_; uint8_t v___y_4982_; uint64_t v___y_4983_; uint64_t v___y_4989_; uint64_t v___y_4990_; uint32_t v___y_4991_; uint64_t v___y_4992_; uint64_t v___y_4993_; uint64_t v___y_4994_; uint8_t v___y_4995_; uint64_t v___y_4996_; uint64_t v___y_4997_; uint64_t v___y_5002_; uint32_t v___y_5003_; uint64_t v___y_5004_; uint64_t v___y_5005_; uint64_t v___y_5006_; uint8_t v___y_5007_; uint64_t v___y_5008_; uint64_t v___y_5013_; uint64_t v___y_5014_; uint32_t v___y_5015_; uint64_t v___y_5016_; uint64_t v___y_5017_; uint64_t v___y_5018_; uint8_t v___y_5019_; uint64_t v___y_5020_; uint64_t v___y_5021_; uint64_t v___y_5026_; uint64_t v___y_5027_; uint32_t v___y_5028_; uint64_t v___y_5029_; uint64_t v___y_5030_; uint8_t v___y_5031_; uint64_t v___y_5032_; uint64_t v___y_5037_; uint64_t v___y_5038_; uint64_t v___y_5039_; uint32_t v___y_5040_; uint64_t v___y_5041_; uint64_t v___y_5042_; uint64_t v___y_5043_; uint8_t v___y_5044_; uint64_t v___y_5045_; uint64_t v___y_5050_; uint32_t v___y_5051_; uint64_t v___y_5052_; uint64_t v___y_5053_; uint64_t v___y_5054_; uint8_t v___y_5055_; uint64_t v___y_5056_; uint64_t v___y_5061_; uint64_t v___y_5062_; uint32_t v___y_5063_; uint64_t v___y_5064_; uint64_t v___y_5065_; uint64_t v___y_5066_; uint64_t v___y_5067_; uint8_t v___y_5068_; uint64_t v___y_5069_; uint64_t v___y_5074_; uint32_t v___y_5075_; uint64_t v___y_5076_; uint64_t v___y_5077_; uint64_t v___y_5078_; uint8_t v___y_5079_; uint64_t v___y_5080_; uint64_t v___y_5085_; uint64_t v___y_5086_; uint32_t v___y_5087_; uint64_t v___y_5088_; uint64_t v___y_5089_; uint8_t v___y_5090_; uint64_t v___y_5091_; uint64_t v___y_5095_; uint32_t v___y_5096_; uint64_t v___y_5097_; uint8_t v___y_5098_; uint64_t v___y_5107_; uint32_t v___y_5108_; uint64_t v___y_5109_; uint64_t v___y_5110_; uint8_t v___y_5111_; uint64_t v___y_5112_; uint32_t v_ex_5145_; uint32_t v___x_5146_; uint32_t v_ey_5147_; uint64_t v___y_5149_; uint32_t v___y_5150_; uint64_t v___y_5151_; uint8_t v___y_5152_; uint64_t v___y_5153_; uint32_t v___y_5160_; uint64_t v___y_5161_; uint8_t v___y_5162_; uint64_t v___y_5163_; uint32_t v___y_5170_; uint32_t v___y_5171_; uint8_t v___y_5172_; uint64_t v___y_5173_; uint8_t v___y_5181_; uint32_t v___x_5191_; uint32_t v___x_5192_; uint8_t v___x_5193_; uint8_t v___y_5195_; uint8_t v___y_5196_; uint8_t v___y_5198_; uint8_t v___y_5199_; uint8_t v___y_5200_; uint8_t v___y_5202_; uint8_t v___y_5203_; uint8_t v___y_5209_; 
v___x_4860_ = 23;
v___x_4861_ = lean_uint32_shift_right(v_x_4803_, v___x_4860_);
v___x_4862_ = 255;
v_ex_5145_ = lean_uint32_land(v___x_4861_, v___x_4862_);
v___x_5146_ = lean_uint32_shift_right(v_y_4804_, v___x_4860_);
v_ey_5147_ = lean_uint32_land(v___x_5146_, v___x_4862_);
v___x_5191_ = lean_uint32_add(v_ex_5145_, v_ey_5147_);
v___x_5192_ = 128;
v___x_5193_ = lean_uint32_dec_lt(v___x_5191_, v___x_5192_);
if (v___x_5193_ == 0)
{
uint8_t v___x_5222_; 
v___x_5222_ = lean_uint32_dec_eq(v_ex_5145_, v___x_4862_);
if (v___x_5222_ == 0)
{
goto v___jp_5219_;
}
else
{
if (v___x_5193_ == 0)
{
uint32_t v___x_5223_; 
v___x_5223_ = lp_competition_Submission_FastMul_mul(v_x_4803_, v_y_4804_);
return v___x_5223_;
}
else
{
goto v___jp_5219_;
}
}
}
else
{
uint32_t v___x_5224_; uint32_t v___x_5225_; uint32_t v___x_5226_; uint8_t v___x_5227_; 
v___x_5224_ = 4278190080;
v___x_5225_ = 1;
v___x_5226_ = lean_uint32_shift_left(v_x_4803_, v___x_5225_);
v___x_5227_ = lean_uint32_dec_le(v___x_5224_, v___x_5226_);
if (v___x_5227_ == 0)
{
uint32_t v___x_5228_; uint8_t v___x_5229_; 
v___x_5228_ = lean_uint32_shift_left(v_y_4804_, v___x_5225_);
v___x_5229_ = lean_uint32_dec_le(v___x_5224_, v___x_5228_);
v___y_5209_ = v___x_5229_;
goto v___jp_5208_;
}
else
{
v___y_5209_ = v___x_5227_;
goto v___jp_5208_;
}
}
v___jp_4805_:
{
float v___x_4806_; float v___x_4807_; float v___x_4808_; uint32_t v___x_4809_; 
v___x_4806_ = lean_float32_of_bits(v_x_4803_);
v___x_4807_ = lean_float32_of_bits(v_y_4804_);
v___x_4808_ = lean_float32_mul(v___x_4806_, v___x_4807_);
v___x_4809_ = lean_float32_to_bits(v___x_4808_);
return v___x_4809_;
}
v___jp_4810_:
{
uint32_t v___x_4812_; uint32_t v___x_4813_; 
v___x_4812_ = 8388608;
v___x_4813_ = lean_uint32_lor(v___y_4811_, v___x_4812_);
return v___x_4813_;
}
v___jp_4814_:
{
uint32_t v___x_4816_; uint32_t v___x_4817_; 
v___x_4816_ = 8388608;
v___x_4817_ = lean_uint32_lor(v___y_4815_, v___x_4816_);
return v___x_4817_;
}
v___jp_4818_:
{
uint32_t v___x_4822_; uint32_t v___x_4823_; 
v___x_4822_ = lean_uint32_land(v___y_4820_, v___y_4819_);
v___x_4823_ = lean_uint32_lor(v___y_4821_, v___x_4822_);
return v___x_4823_;
}
v___jp_4824_:
{
uint8_t v___x_4829_; 
v___x_4829_ = lean_uint64_dec_eq(v___y_4828_, v___y_4826_);
if (v___x_4829_ == 0)
{
uint64_t v___x_4830_; uint8_t v___x_4831_; 
v___x_4830_ = 8388608ULL;
v___x_4831_ = lean_uint64_dec_eq(v___y_4828_, v___x_4830_);
if (v___x_4831_ == 0)
{
uint32_t v___x_4832_; 
v___x_4832_ = lean_uint64_to_uint32(v___y_4828_);
if (v___y_4827_ == 0)
{
uint32_t v___x_4833_; 
v___x_4833_ = 0;
v___y_4819_ = v___y_4825_;
v___y_4820_ = v___x_4832_;
v___y_4821_ = v___x_4833_;
goto v___jp_4818_;
}
else
{
uint32_t v___x_4834_; 
v___x_4834_ = 2147483648;
v___y_4819_ = v___y_4825_;
v___y_4820_ = v___x_4832_;
v___y_4821_ = v___x_4834_;
goto v___jp_4818_;
}
}
else
{
if (v___y_4827_ == 0)
{
uint32_t v___x_4835_; 
v___x_4835_ = 0;
v___y_4815_ = v___x_4835_;
goto v___jp_4814_;
}
else
{
uint32_t v___x_4836_; 
v___x_4836_ = 2147483648;
v___y_4815_ = v___x_4836_;
goto v___jp_4814_;
}
}
}
else
{
if (v___y_4827_ == 0)
{
uint32_t v___x_4837_; 
v___x_4837_ = 0;
return v___x_4837_;
}
else
{
uint32_t v___x_4838_; 
v___x_4838_ = 2147483648;
return v___x_4838_;
}
}
}
v___jp_4839_:
{
uint32_t v___x_4843_; uint32_t v___x_4844_; 
v___x_4843_ = lean_uint32_land(v___y_4841_, v___y_4840_);
v___x_4844_ = lean_uint32_lor(v___y_4842_, v___x_4843_);
return v___x_4844_;
}
v___jp_4845_:
{
uint8_t v___x_4850_; 
v___x_4850_ = lean_uint64_dec_eq(v___y_4849_, v___y_4846_);
if (v___x_4850_ == 0)
{
uint64_t v___x_4851_; uint8_t v___x_4852_; 
v___x_4851_ = 8388608ULL;
v___x_4852_ = lean_uint64_dec_eq(v___y_4849_, v___x_4851_);
if (v___x_4852_ == 0)
{
uint32_t v___x_4853_; 
v___x_4853_ = lean_uint64_to_uint32(v___y_4849_);
if (v___y_4848_ == 0)
{
uint32_t v___x_4854_; 
v___x_4854_ = 0;
v___y_4840_ = v___y_4847_;
v___y_4841_ = v___x_4853_;
v___y_4842_ = v___x_4854_;
goto v___jp_4839_;
}
else
{
uint32_t v___x_4855_; 
v___x_4855_ = 2147483648;
v___y_4840_ = v___y_4847_;
v___y_4841_ = v___x_4853_;
v___y_4842_ = v___x_4855_;
goto v___jp_4839_;
}
}
else
{
if (v___y_4848_ == 0)
{
uint32_t v___x_4856_; 
v___x_4856_ = 0;
v___y_4811_ = v___x_4856_;
goto v___jp_4810_;
}
else
{
uint32_t v___x_4857_; 
v___x_4857_ = 2147483648;
v___y_4811_ = v___x_4857_;
goto v___jp_4810_;
}
}
}
else
{
if (v___y_4848_ == 0)
{
uint32_t v___x_4858_; 
v___x_4858_ = 0;
return v___x_4858_;
}
else
{
uint32_t v___x_4859_; 
v___x_4859_ = 2147483648;
return v___x_4859_;
}
}
}
v___jp_4863_:
{
uint32_t v___x_4868_; uint32_t v___x_4869_; uint32_t v___x_4870_; uint32_t v___x_4871_; uint32_t v___x_4872_; 
v___x_4868_ = lean_uint32_land(v___y_4866_, v___x_4862_);
v___x_4869_ = lean_uint32_shift_left(v___x_4868_, v___x_4860_);
v___x_4870_ = lean_uint32_lor(v___y_4867_, v___x_4869_);
v___x_4871_ = lean_uint32_land(v___y_4864_, v___y_4865_);
v___x_4872_ = lean_uint32_lor(v___x_4870_, v___x_4871_);
return v___x_4872_;
}
v___jp_4873_:
{
if (v___y_4875_ == 0)
{
uint32_t v___x_4878_; 
v___x_4878_ = 0;
v___y_4864_ = v___y_4877_;
v___y_4865_ = v___y_4874_;
v___y_4866_ = v___y_4876_;
v___y_4867_ = v___x_4878_;
goto v___jp_4863_;
}
else
{
uint32_t v___x_4879_; 
v___x_4879_ = 2147483648;
v___y_4864_ = v___y_4877_;
v___y_4865_ = v___y_4874_;
v___y_4866_ = v___y_4876_;
v___y_4867_ = v___x_4879_;
goto v___jp_4863_;
}
}
v___jp_4880_:
{
uint64_t v___x_4886_; uint64_t v_encodedExponent_4887_; uint32_t v___x_4888_; uint64_t v___x_4889_; uint8_t v___x_4890_; 
v___x_4886_ = 171ULL;
v_encodedExponent_4887_ = lean_uint64_sub(v___y_4882_, v___x_4886_);
v___x_4888_ = lean_uint64_to_uint32(v_encodedExponent_4887_);
v___x_4889_ = 8388608ULL;
v___x_4890_ = lean_uint64_dec_lt(v___y_4885_, v___x_4889_);
if (v___x_4890_ == 0)
{
uint64_t v___x_4891_; uint32_t v___x_4892_; 
v___x_4891_ = lean_uint64_sub(v___y_4885_, v___x_4889_);
v___x_4892_ = lean_uint64_to_uint32(v___x_4891_);
v___y_4874_ = v___y_4881_;
v___y_4875_ = v___y_4884_;
v___y_4876_ = v___x_4888_;
v___y_4877_ = v___x_4892_;
goto v___jp_4873_;
}
else
{
uint32_t v___x_4893_; 
v___x_4893_ = lean_uint64_to_uint32(v___y_4883_);
v___y_4874_ = v___y_4881_;
v___y_4875_ = v___y_4884_;
v___y_4876_ = v___x_4888_;
v___y_4877_ = v___x_4893_;
goto v___jp_4873_;
}
}
v___jp_4894_:
{
uint64_t v___x_4901_; uint8_t v___x_4902_; 
v___x_4901_ = 425ULL;
v___x_4902_ = lean_uint64_dec_lt(v___x_4901_, v___y_4900_);
if (v___x_4902_ == 0)
{
if (v___y_4898_ == 0)
{
v___y_4881_ = v___y_4896_;
v___y_4882_ = v___y_4900_;
v___y_4883_ = v___y_4897_;
v___y_4884_ = v___y_4899_;
v___y_4885_ = v___y_4895_;
goto v___jp_4880_;
}
else
{
uint64_t v___x_4903_; 
v___x_4903_ = 8388608ULL;
v___y_4881_ = v___y_4896_;
v___y_4882_ = v___y_4900_;
v___y_4883_ = v___y_4897_;
v___y_4884_ = v___y_4899_;
v___y_4885_ = v___x_4903_;
goto v___jp_4880_;
}
}
else
{
if (v___y_4899_ == 0)
{
uint32_t v___x_4904_; 
v___x_4904_ = 2139095040;
return v___x_4904_;
}
else
{
uint32_t v___x_4905_; 
v___x_4905_ = 4286578688;
return v___x_4905_;
}
}
}
v___jp_4906_:
{
uint64_t v___x_4912_; uint8_t v_carry_4913_; 
v___x_4912_ = 16777216ULL;
v_carry_4913_ = lean_uint64_dec_eq(v___y_4911_, v___x_4912_);
if (v_carry_4913_ == 0)
{
v___y_4895_ = v___y_4911_;
v___y_4896_ = v___y_4908_;
v___y_4897_ = v___y_4909_;
v___y_4898_ = v_carry_4913_;
v___y_4899_ = v___y_4910_;
v___y_4900_ = v___y_4907_;
goto v___jp_4894_;
}
else
{
uint64_t v___x_4914_; uint64_t v___x_4915_; 
v___x_4914_ = 1ULL;
v___x_4915_ = lean_uint64_add(v___y_4907_, v___x_4914_);
v___y_4895_ = v___y_4911_;
v___y_4896_ = v___y_4908_;
v___y_4897_ = v___y_4909_;
v___y_4898_ = v_carry_4913_;
v___y_4899_ = v___y_4910_;
v___y_4900_ = v___x_4915_;
goto v___jp_4894_;
}
}
v___jp_4916_:
{
uint64_t v_position_4923_; uint64_t v___x_4924_; uint8_t v___x_4925_; 
v_position_4923_ = lean_uint64_add(v___y_4922_, v___y_4919_);
v___x_4924_ = 172ULL;
v___x_4925_ = lean_uint64_dec_lt(v_position_4923_, v___x_4924_);
if (v___x_4925_ == 0)
{
uint64_t v___x_4926_; uint8_t v___x_4927_; 
v___x_4926_ = 23ULL;
v___x_4927_ = lean_uint64_dec_lt(v___y_4922_, v___x_4926_);
if (v___x_4927_ == 0)
{
uint64_t v___x_4928_; uint8_t v___x_4929_; 
v___x_4928_ = lean_uint64_sub(v___y_4922_, v___x_4926_);
v___x_4929_ = lean_uint64_dec_eq(v___x_4928_, v___y_4920_);
if (v___x_4929_ == 0)
{
uint64_t v___x_4930_; uint8_t v___x_4931_; 
v___x_4930_ = 64ULL;
v___x_4931_ = lean_uint64_dec_lt(v___x_4928_, v___x_4930_);
if (v___x_4931_ == 0)
{
uint8_t v___x_4932_; 
v___x_4932_ = lean_uint64_dec_eq(v___x_4928_, v___x_4930_);
if (v___x_4932_ == 0)
{
v___y_4907_ = v_position_4923_;
v___y_4908_ = v___y_4918_;
v___y_4909_ = v___y_4920_;
v___y_4910_ = v___y_4921_;
v___y_4911_ = v___y_4920_;
goto v___jp_4906_;
}
else
{
uint64_t v___x_4933_; uint8_t v___x_4934_; 
v___x_4933_ = 9223372036854775808ULL;
v___x_4934_ = lean_uint64_dec_lt(v___x_4933_, v___y_4917_);
if (v___x_4934_ == 0)
{
v___y_4907_ = v_position_4923_;
v___y_4908_ = v___y_4918_;
v___y_4909_ = v___y_4920_;
v___y_4910_ = v___y_4921_;
v___y_4911_ = v___y_4920_;
goto v___jp_4906_;
}
else
{
uint64_t v___x_4935_; 
v___x_4935_ = 1ULL;
v___y_4907_ = v_position_4923_;
v___y_4908_ = v___y_4918_;
v___y_4909_ = v___y_4920_;
v___y_4910_ = v___y_4921_;
v___y_4911_ = v___x_4935_;
goto v___jp_4906_;
}
}
}
else
{
uint64_t v_quotient_4936_; uint64_t v___x_4937_; uint64_t v___x_4938_; uint64_t v___x_4939_; uint64_t v_remainder_4940_; uint64_t v___x_4941_; uint64_t v_half_4942_; uint8_t v___x_4943_; 
v_quotient_4936_ = lean_uint64_shift_right(v___y_4917_, v___x_4928_);
v___x_4937_ = 1ULL;
v___x_4938_ = lean_uint64_shift_left(v___x_4937_, v___x_4928_);
v___x_4939_ = lean_uint64_sub(v___x_4938_, v___x_4937_);
v_remainder_4940_ = lean_uint64_land(v___y_4917_, v___x_4939_);
v___x_4941_ = lean_uint64_sub(v___x_4928_, v___x_4937_);
v_half_4942_ = lean_uint64_shift_left(v___x_4937_, v___x_4941_);
v___x_4943_ = lean_uint64_dec_lt(v_remainder_4940_, v_half_4942_);
if (v___x_4943_ == 0)
{
uint8_t v___x_4944_; 
v___x_4944_ = lean_uint64_dec_lt(v_half_4942_, v_remainder_4940_);
if (v___x_4944_ == 0)
{
uint64_t v___x_4945_; uint8_t v___x_4946_; 
v___x_4945_ = lean_uint64_land(v_quotient_4936_, v___x_4937_);
v___x_4946_ = lean_uint64_dec_eq(v___x_4945_, v___y_4920_);
if (v___x_4946_ == 0)
{
uint64_t v___x_4947_; 
v___x_4947_ = lean_uint64_add(v_quotient_4936_, v___x_4937_);
v___y_4907_ = v_position_4923_;
v___y_4908_ = v___y_4918_;
v___y_4909_ = v___y_4920_;
v___y_4910_ = v___y_4921_;
v___y_4911_ = v___x_4947_;
goto v___jp_4906_;
}
else
{
v___y_4907_ = v_position_4923_;
v___y_4908_ = v___y_4918_;
v___y_4909_ = v___y_4920_;
v___y_4910_ = v___y_4921_;
v___y_4911_ = v_quotient_4936_;
goto v___jp_4906_;
}
}
else
{
uint64_t v___x_4948_; 
v___x_4948_ = lean_uint64_add(v_quotient_4936_, v___x_4937_);
v___y_4907_ = v_position_4923_;
v___y_4908_ = v___y_4918_;
v___y_4909_ = v___y_4920_;
v___y_4910_ = v___y_4921_;
v___y_4911_ = v___x_4948_;
goto v___jp_4906_;
}
}
else
{
v___y_4907_ = v_position_4923_;
v___y_4908_ = v___y_4918_;
v___y_4909_ = v___y_4920_;
v___y_4910_ = v___y_4921_;
v___y_4911_ = v_quotient_4936_;
goto v___jp_4906_;
}
}
}
else
{
v___y_4907_ = v_position_4923_;
v___y_4908_ = v___y_4918_;
v___y_4909_ = v___y_4920_;
v___y_4910_ = v___y_4921_;
v___y_4911_ = v___y_4917_;
goto v___jp_4906_;
}
}
else
{
uint64_t v___x_4949_; uint64_t v___x_4950_; 
v___x_4949_ = lean_uint64_sub(v___x_4926_, v___y_4922_);
v___x_4950_ = lean_uint64_shift_left(v___y_4917_, v___x_4949_);
v___y_4907_ = v_position_4923_;
v___y_4908_ = v___y_4918_;
v___y_4909_ = v___y_4920_;
v___y_4910_ = v___y_4921_;
v___y_4911_ = v___x_4950_;
goto v___jp_4906_;
}
}
else
{
uint64_t v___x_4951_; uint8_t v___x_4952_; 
v___x_4951_ = 149ULL;
v___x_4952_ = lean_uint64_dec_lt(v___y_4919_, v___x_4951_);
if (v___x_4952_ == 0)
{
uint64_t v___x_4953_; uint64_t v___x_4954_; 
v___x_4953_ = lean_uint64_sub(v___y_4919_, v___x_4951_);
v___x_4954_ = lean_uint64_shift_left(v___y_4917_, v___x_4953_);
v___y_4825_ = v___y_4918_;
v___y_4826_ = v___y_4920_;
v___y_4827_ = v___y_4921_;
v___y_4828_ = v___x_4954_;
goto v___jp_4824_;
}
else
{
uint64_t v___x_4955_; uint8_t v___x_4956_; 
v___x_4955_ = lean_uint64_sub(v___x_4951_, v___y_4919_);
v___x_4956_ = lean_uint64_dec_eq(v___x_4955_, v___y_4920_);
if (v___x_4956_ == 0)
{
uint64_t v___x_4957_; uint8_t v___x_4958_; 
v___x_4957_ = 64ULL;
v___x_4958_ = lean_uint64_dec_lt(v___x_4955_, v___x_4957_);
if (v___x_4958_ == 0)
{
uint8_t v___x_4959_; 
v___x_4959_ = lean_uint64_dec_eq(v___x_4955_, v___x_4957_);
if (v___x_4959_ == 0)
{
v___y_4825_ = v___y_4918_;
v___y_4826_ = v___y_4920_;
v___y_4827_ = v___y_4921_;
v___y_4828_ = v___y_4920_;
goto v___jp_4824_;
}
else
{
uint64_t v___x_4960_; uint8_t v___x_4961_; 
v___x_4960_ = 9223372036854775808ULL;
v___x_4961_ = lean_uint64_dec_lt(v___x_4960_, v___y_4917_);
if (v___x_4961_ == 0)
{
v___y_4825_ = v___y_4918_;
v___y_4826_ = v___y_4920_;
v___y_4827_ = v___y_4921_;
v___y_4828_ = v___y_4920_;
goto v___jp_4824_;
}
else
{
uint64_t v___x_4962_; 
v___x_4962_ = 1ULL;
v___y_4825_ = v___y_4918_;
v___y_4826_ = v___y_4920_;
v___y_4827_ = v___y_4921_;
v___y_4828_ = v___x_4962_;
goto v___jp_4824_;
}
}
}
else
{
uint64_t v_quotient_4963_; uint64_t v___x_4964_; uint64_t v___x_4965_; uint64_t v___x_4966_; uint64_t v_remainder_4967_; uint64_t v___x_4968_; uint64_t v_half_4969_; uint8_t v___x_4970_; 
v_quotient_4963_ = lean_uint64_shift_right(v___y_4917_, v___x_4955_);
v___x_4964_ = 1ULL;
v___x_4965_ = lean_uint64_shift_left(v___x_4964_, v___x_4955_);
v___x_4966_ = lean_uint64_sub(v___x_4965_, v___x_4964_);
v_remainder_4967_ = lean_uint64_land(v___y_4917_, v___x_4966_);
v___x_4968_ = lean_uint64_sub(v___x_4955_, v___x_4964_);
v_half_4969_ = lean_uint64_shift_left(v___x_4964_, v___x_4968_);
v___x_4970_ = lean_uint64_dec_lt(v_remainder_4967_, v_half_4969_);
if (v___x_4970_ == 0)
{
uint8_t v___x_4971_; 
v___x_4971_ = lean_uint64_dec_lt(v_half_4969_, v_remainder_4967_);
if (v___x_4971_ == 0)
{
uint64_t v___x_4972_; uint8_t v___x_4973_; 
v___x_4972_ = lean_uint64_land(v_quotient_4963_, v___x_4964_);
v___x_4973_ = lean_uint64_dec_eq(v___x_4972_, v___y_4920_);
if (v___x_4973_ == 0)
{
uint64_t v___x_4974_; 
v___x_4974_ = lean_uint64_add(v_quotient_4963_, v___x_4964_);
v___y_4825_ = v___y_4918_;
v___y_4826_ = v___y_4920_;
v___y_4827_ = v___y_4921_;
v___y_4828_ = v___x_4974_;
goto v___jp_4824_;
}
else
{
v___y_4825_ = v___y_4918_;
v___y_4826_ = v___y_4920_;
v___y_4827_ = v___y_4921_;
v___y_4828_ = v_quotient_4963_;
goto v___jp_4824_;
}
}
else
{
uint64_t v___x_4975_; 
v___x_4975_ = lean_uint64_add(v_quotient_4963_, v___x_4964_);
v___y_4825_ = v___y_4918_;
v___y_4826_ = v___y_4920_;
v___y_4827_ = v___y_4921_;
v___y_4828_ = v___x_4975_;
goto v___jp_4824_;
}
}
else
{
v___y_4825_ = v___y_4918_;
v___y_4826_ = v___y_4920_;
v___y_4827_ = v___y_4921_;
v___y_4828_ = v_quotient_4963_;
goto v___jp_4824_;
}
}
}
else
{
v___y_4825_ = v___y_4918_;
v___y_4826_ = v___y_4920_;
v___y_4827_ = v___y_4921_;
v___y_4828_ = v___y_4917_;
goto v___jp_4824_;
}
}
}
}
v___jp_4976_:
{
uint64_t v___x_4984_; uint64_t v___x_4985_; uint8_t v___x_4986_; 
v___x_4984_ = 1ULL;
v___x_4985_ = lean_uint64_shift_right(v___y_4977_, v___x_4984_);
v___x_4986_ = lean_uint64_dec_eq(v___x_4985_, v___y_4981_);
if (v___x_4986_ == 0)
{
uint64_t v___x_4987_; 
v___x_4987_ = lean_uint64_add(v___y_4983_, v___x_4984_);
v___y_4917_ = v___y_4978_;
v___y_4918_ = v___y_4979_;
v___y_4919_ = v___y_4980_;
v___y_4920_ = v___y_4981_;
v___y_4921_ = v___y_4982_;
v___y_4922_ = v___x_4987_;
goto v___jp_4916_;
}
else
{
v___y_4917_ = v___y_4978_;
v___y_4918_ = v___y_4979_;
v___y_4919_ = v___y_4980_;
v___y_4920_ = v___y_4981_;
v___y_4921_ = v___y_4982_;
v___y_4922_ = v___y_4983_;
goto v___jp_4916_;
}
}
v___jp_4988_:
{
uint64_t v___x_4998_; uint8_t v___x_4999_; 
v___x_4998_ = lean_uint64_shift_right(v___y_4990_, v___y_4994_);
v___x_4999_ = lean_uint64_dec_eq(v___x_4998_, v___y_4993_);
if (v___x_4999_ == 0)
{
uint64_t v___x_5000_; 
v___x_5000_ = lean_uint64_add(v___y_4996_, v___y_4994_);
v___y_4977_ = v___y_4997_;
v___y_4978_ = v___y_4989_;
v___y_4979_ = v___y_4991_;
v___y_4980_ = v___y_4992_;
v___y_4981_ = v___y_4993_;
v___y_4982_ = v___y_4995_;
v___y_4983_ = v___x_5000_;
goto v___jp_4976_;
}
else
{
v___y_4977_ = v___y_4997_;
v___y_4978_ = v___y_4989_;
v___y_4979_ = v___y_4991_;
v___y_4980_ = v___y_4992_;
v___y_4981_ = v___y_4993_;
v___y_4982_ = v___y_4995_;
v___y_4983_ = v___y_4996_;
goto v___jp_4976_;
}
}
v___jp_5001_:
{
uint64_t v___x_5009_; uint64_t v___x_5010_; uint8_t v___x_5011_; 
v___x_5009_ = 2ULL;
v___x_5010_ = lean_uint64_shift_right(v___y_5004_, v___x_5009_);
v___x_5011_ = lean_uint64_dec_eq(v___x_5010_, v___y_5006_);
if (v___x_5011_ == 0)
{
v___y_4989_ = v___y_5002_;
v___y_4990_ = v___y_5004_;
v___y_4991_ = v___y_5003_;
v___y_4992_ = v___y_5005_;
v___y_4993_ = v___y_5006_;
v___y_4994_ = v___x_5009_;
v___y_4995_ = v___y_5007_;
v___y_4996_ = v___y_5008_;
v___y_4997_ = v___x_5010_;
goto v___jp_4988_;
}
else
{
v___y_4989_ = v___y_5002_;
v___y_4990_ = v___y_5004_;
v___y_4991_ = v___y_5003_;
v___y_4992_ = v___y_5005_;
v___y_4993_ = v___y_5006_;
v___y_4994_ = v___x_5009_;
v___y_4995_ = v___y_5007_;
v___y_4996_ = v___y_5008_;
v___y_4997_ = v___y_5004_;
goto v___jp_4988_;
}
}
v___jp_5012_:
{
uint64_t v___x_5022_; uint8_t v___x_5023_; 
v___x_5022_ = lean_uint64_shift_right(v___y_5013_, v___y_5018_);
v___x_5023_ = lean_uint64_dec_eq(v___x_5022_, v___y_5017_);
if (v___x_5023_ == 0)
{
uint64_t v___x_5024_; 
v___x_5024_ = lean_uint64_add(v___y_5020_, v___y_5018_);
v___y_5002_ = v___y_5014_;
v___y_5003_ = v___y_5015_;
v___y_5004_ = v___y_5021_;
v___y_5005_ = v___y_5016_;
v___y_5006_ = v___y_5017_;
v___y_5007_ = v___y_5019_;
v___y_5008_ = v___x_5024_;
goto v___jp_5001_;
}
else
{
v___y_5002_ = v___y_5014_;
v___y_5003_ = v___y_5015_;
v___y_5004_ = v___y_5021_;
v___y_5005_ = v___y_5016_;
v___y_5006_ = v___y_5017_;
v___y_5007_ = v___y_5019_;
v___y_5008_ = v___y_5020_;
goto v___jp_5001_;
}
}
v___jp_5025_:
{
uint64_t v___x_5033_; uint64_t v___x_5034_; uint8_t v___x_5035_; 
v___x_5033_ = 4ULL;
v___x_5034_ = lean_uint64_shift_right(v___y_5027_, v___x_5033_);
v___x_5035_ = lean_uint64_dec_eq(v___x_5034_, v___y_5030_);
if (v___x_5035_ == 0)
{
v___y_5013_ = v___y_5027_;
v___y_5014_ = v___y_5026_;
v___y_5015_ = v___y_5028_;
v___y_5016_ = v___y_5029_;
v___y_5017_ = v___y_5030_;
v___y_5018_ = v___x_5033_;
v___y_5019_ = v___y_5031_;
v___y_5020_ = v___y_5032_;
v___y_5021_ = v___x_5034_;
goto v___jp_5012_;
}
else
{
v___y_5013_ = v___y_5027_;
v___y_5014_ = v___y_5026_;
v___y_5015_ = v___y_5028_;
v___y_5016_ = v___y_5029_;
v___y_5017_ = v___y_5030_;
v___y_5018_ = v___x_5033_;
v___y_5019_ = v___y_5031_;
v___y_5020_ = v___y_5032_;
v___y_5021_ = v___y_5027_;
goto v___jp_5012_;
}
}
v___jp_5036_:
{
uint64_t v___x_5046_; uint8_t v___x_5047_; 
v___x_5046_ = lean_uint64_shift_right(v___y_5041_, v___y_5037_);
v___x_5047_ = lean_uint64_dec_eq(v___x_5046_, v___y_5043_);
if (v___x_5047_ == 0)
{
uint64_t v___x_5048_; 
v___x_5048_ = lean_uint64_add(v___y_5038_, v___y_5037_);
v___y_5026_ = v___y_5039_;
v___y_5027_ = v___y_5045_;
v___y_5028_ = v___y_5040_;
v___y_5029_ = v___y_5042_;
v___y_5030_ = v___y_5043_;
v___y_5031_ = v___y_5044_;
v___y_5032_ = v___x_5048_;
goto v___jp_5025_;
}
else
{
v___y_5026_ = v___y_5039_;
v___y_5027_ = v___y_5045_;
v___y_5028_ = v___y_5040_;
v___y_5029_ = v___y_5042_;
v___y_5030_ = v___y_5043_;
v___y_5031_ = v___y_5044_;
v___y_5032_ = v___y_5038_;
goto v___jp_5025_;
}
}
v___jp_5049_:
{
uint64_t v___x_5057_; uint64_t v___x_5058_; uint8_t v___x_5059_; 
v___x_5057_ = 8ULL;
v___x_5058_ = lean_uint64_shift_right(v___y_5052_, v___x_5057_);
v___x_5059_ = lean_uint64_dec_eq(v___x_5058_, v___y_5054_);
if (v___x_5059_ == 0)
{
v___y_5037_ = v___x_5057_;
v___y_5038_ = v___y_5056_;
v___y_5039_ = v___y_5050_;
v___y_5040_ = v___y_5051_;
v___y_5041_ = v___y_5052_;
v___y_5042_ = v___y_5053_;
v___y_5043_ = v___y_5054_;
v___y_5044_ = v___y_5055_;
v___y_5045_ = v___x_5058_;
goto v___jp_5036_;
}
else
{
v___y_5037_ = v___x_5057_;
v___y_5038_ = v___y_5056_;
v___y_5039_ = v___y_5050_;
v___y_5040_ = v___y_5051_;
v___y_5041_ = v___y_5052_;
v___y_5042_ = v___y_5053_;
v___y_5043_ = v___y_5054_;
v___y_5044_ = v___y_5055_;
v___y_5045_ = v___y_5052_;
goto v___jp_5036_;
}
}
v___jp_5060_:
{
uint64_t v___x_5070_; uint8_t v___x_5071_; 
v___x_5070_ = lean_uint64_shift_right(v___y_5067_, v___y_5065_);
v___x_5071_ = lean_uint64_dec_eq(v___x_5070_, v___y_5066_);
if (v___x_5071_ == 0)
{
uint64_t v___x_5072_; 
v___x_5072_ = lean_uint64_add(v___y_5061_, v___y_5065_);
v___y_5050_ = v___y_5062_;
v___y_5051_ = v___y_5063_;
v___y_5052_ = v___y_5069_;
v___y_5053_ = v___y_5064_;
v___y_5054_ = v___y_5066_;
v___y_5055_ = v___y_5068_;
v___y_5056_ = v___x_5072_;
goto v___jp_5049_;
}
else
{
v___y_5050_ = v___y_5062_;
v___y_5051_ = v___y_5063_;
v___y_5052_ = v___y_5069_;
v___y_5053_ = v___y_5064_;
v___y_5054_ = v___y_5066_;
v___y_5055_ = v___y_5068_;
v___y_5056_ = v___y_5061_;
goto v___jp_5049_;
}
}
v___jp_5073_:
{
uint64_t v___x_5081_; uint64_t v___x_5082_; uint8_t v___x_5083_; 
v___x_5081_ = 16ULL;
v___x_5082_ = lean_uint64_shift_right(v___y_5078_, v___x_5081_);
v___x_5083_ = lean_uint64_dec_eq(v___x_5082_, v___y_5077_);
if (v___x_5083_ == 0)
{
v___y_5061_ = v___y_5080_;
v___y_5062_ = v___y_5074_;
v___y_5063_ = v___y_5075_;
v___y_5064_ = v___y_5076_;
v___y_5065_ = v___x_5081_;
v___y_5066_ = v___y_5077_;
v___y_5067_ = v___y_5078_;
v___y_5068_ = v___y_5079_;
v___y_5069_ = v___x_5082_;
goto v___jp_5060_;
}
else
{
v___y_5061_ = v___y_5080_;
v___y_5062_ = v___y_5074_;
v___y_5063_ = v___y_5075_;
v___y_5064_ = v___y_5076_;
v___y_5065_ = v___x_5081_;
v___y_5066_ = v___y_5077_;
v___y_5067_ = v___y_5078_;
v___y_5068_ = v___y_5079_;
v___y_5069_ = v___y_5078_;
goto v___jp_5060_;
}
}
v___jp_5084_:
{
uint64_t v___x_5092_; uint8_t v___x_5093_; 
v___x_5092_ = lean_uint64_shift_right(v___y_5086_, v___y_5085_);
v___x_5093_ = lean_uint64_dec_eq(v___x_5092_, v___y_5089_);
if (v___x_5093_ == 0)
{
v___y_5074_ = v___y_5086_;
v___y_5075_ = v___y_5087_;
v___y_5076_ = v___y_5088_;
v___y_5077_ = v___y_5089_;
v___y_5078_ = v___y_5091_;
v___y_5079_ = v___y_5090_;
v___y_5080_ = v___y_5085_;
goto v___jp_5073_;
}
else
{
v___y_5074_ = v___y_5086_;
v___y_5075_ = v___y_5087_;
v___y_5076_ = v___y_5088_;
v___y_5077_ = v___y_5089_;
v___y_5078_ = v___y_5091_;
v___y_5079_ = v___y_5090_;
v___y_5080_ = v___y_5089_;
goto v___jp_5073_;
}
}
v___jp_5094_:
{
uint64_t v___x_5099_; uint8_t v___x_5100_; 
v___x_5099_ = 0ULL;
v___x_5100_ = lean_uint64_dec_eq(v___y_5095_, v___x_5099_);
if (v___x_5100_ == 0)
{
uint64_t v___x_5101_; uint64_t v___x_5102_; uint8_t v___x_5103_; 
v___x_5101_ = 32ULL;
v___x_5102_ = lean_uint64_shift_right(v___y_5095_, v___x_5101_);
v___x_5103_ = lean_uint64_dec_eq(v___x_5102_, v___x_5099_);
if (v___x_5103_ == 0)
{
v___y_5085_ = v___x_5101_;
v___y_5086_ = v___y_5095_;
v___y_5087_ = v___y_5096_;
v___y_5088_ = v___y_5097_;
v___y_5089_ = v___x_5099_;
v___y_5090_ = v___y_5098_;
v___y_5091_ = v___x_5102_;
goto v___jp_5084_;
}
else
{
v___y_5085_ = v___x_5101_;
v___y_5086_ = v___y_5095_;
v___y_5087_ = v___y_5096_;
v___y_5088_ = v___y_5097_;
v___y_5089_ = v___x_5099_;
v___y_5090_ = v___y_5098_;
v___y_5091_ = v___y_5095_;
goto v___jp_5084_;
}
}
else
{
if (v___y_5098_ == 0)
{
uint32_t v___x_5104_; 
v___x_5104_ = 0;
return v___x_5104_;
}
else
{
uint32_t v___x_5105_; 
v___x_5105_ = 2147483648;
return v___x_5105_;
}
}
}
v___jp_5106_:
{
uint64_t v___x_5113_; uint64_t v___x_5114_; uint64_t v___x_5115_; uint8_t v___x_5116_; 
v___x_5113_ = lean_uint64_mul(v___y_5110_, v___y_5107_);
v___x_5114_ = lean_uint64_add(v___y_5109_, v___y_5112_);
v___x_5115_ = 281474976710656ULL;
v___x_5116_ = lean_uint64_dec_lt(v___x_5113_, v___x_5115_);
if (v___x_5116_ == 0)
{
v___y_5095_ = v___x_5113_;
v___y_5096_ = v___y_5108_;
v___y_5097_ = v___x_5114_;
v___y_5098_ = v___y_5111_;
goto v___jp_5094_;
}
else
{
uint64_t v___x_5117_; uint8_t v___x_5118_; 
v___x_5117_ = 123ULL;
v___x_5118_ = lean_uint64_dec_le(v___x_5114_, v___x_5117_);
if (v___x_5118_ == 0)
{
v___y_5095_ = v___x_5113_;
v___y_5096_ = v___y_5108_;
v___y_5097_ = v___x_5114_;
v___y_5098_ = v___y_5111_;
goto v___jp_5094_;
}
else
{
uint64_t v___x_5119_; uint8_t v___x_5120_; 
v___x_5119_ = 0ULL;
v___x_5120_ = lean_uint64_dec_eq(v___x_5113_, v___x_5119_);
if (v___x_5120_ == 0)
{
uint64_t v___x_5121_; uint64_t v___x_5122_; uint8_t v___x_5123_; 
v___x_5121_ = 149ULL;
v___x_5122_ = lean_uint64_sub(v___x_5121_, v___x_5114_);
v___x_5123_ = lean_uint64_dec_eq(v___x_5122_, v___x_5119_);
if (v___x_5123_ == 0)
{
uint64_t v___x_5124_; uint8_t v___x_5125_; 
v___x_5124_ = 64ULL;
v___x_5125_ = lean_uint64_dec_lt(v___x_5122_, v___x_5124_);
if (v___x_5125_ == 0)
{
uint8_t v___x_5126_; 
v___x_5126_ = lean_uint64_dec_eq(v___x_5122_, v___x_5124_);
if (v___x_5126_ == 0)
{
v___y_4846_ = v___x_5119_;
v___y_4847_ = v___y_5108_;
v___y_4848_ = v___y_5111_;
v___y_4849_ = v___x_5119_;
goto v___jp_4845_;
}
else
{
uint64_t v___x_5127_; uint8_t v___x_5128_; 
v___x_5127_ = 9223372036854775808ULL;
v___x_5128_ = lean_uint64_dec_lt(v___x_5127_, v___x_5113_);
if (v___x_5128_ == 0)
{
v___y_4846_ = v___x_5119_;
v___y_4847_ = v___y_5108_;
v___y_4848_ = v___y_5111_;
v___y_4849_ = v___x_5119_;
goto v___jp_4845_;
}
else
{
uint64_t v___x_5129_; 
v___x_5129_ = 1ULL;
v___y_4846_ = v___x_5119_;
v___y_4847_ = v___y_5108_;
v___y_4848_ = v___y_5111_;
v___y_4849_ = v___x_5129_;
goto v___jp_4845_;
}
}
}
else
{
uint64_t v_quotient_5130_; uint64_t v___x_5131_; uint64_t v___x_5132_; uint64_t v___x_5133_; uint64_t v_remainder_5134_; uint64_t v___x_5135_; uint64_t v_half_5136_; uint8_t v___x_5137_; 
v_quotient_5130_ = lean_uint64_shift_right(v___x_5113_, v___x_5122_);
v___x_5131_ = 1ULL;
v___x_5132_ = lean_uint64_shift_left(v___x_5131_, v___x_5122_);
v___x_5133_ = lean_uint64_sub(v___x_5132_, v___x_5131_);
v_remainder_5134_ = lean_uint64_land(v___x_5113_, v___x_5133_);
v___x_5135_ = lean_uint64_sub(v___x_5122_, v___x_5131_);
v_half_5136_ = lean_uint64_shift_left(v___x_5131_, v___x_5135_);
v___x_5137_ = lean_uint64_dec_lt(v_remainder_5134_, v_half_5136_);
if (v___x_5137_ == 0)
{
uint8_t v___x_5138_; 
v___x_5138_ = lean_uint64_dec_lt(v_half_5136_, v_remainder_5134_);
if (v___x_5138_ == 0)
{
uint64_t v___x_5139_; uint8_t v___x_5140_; 
v___x_5139_ = lean_uint64_land(v_quotient_5130_, v___x_5131_);
v___x_5140_ = lean_uint64_dec_eq(v___x_5139_, v___x_5119_);
if (v___x_5140_ == 0)
{
uint64_t v___x_5141_; 
v___x_5141_ = lean_uint64_add(v_quotient_5130_, v___x_5131_);
v___y_4846_ = v___x_5119_;
v___y_4847_ = v___y_5108_;
v___y_4848_ = v___y_5111_;
v___y_4849_ = v___x_5141_;
goto v___jp_4845_;
}
else
{
v___y_4846_ = v___x_5119_;
v___y_4847_ = v___y_5108_;
v___y_4848_ = v___y_5111_;
v___y_4849_ = v_quotient_5130_;
goto v___jp_4845_;
}
}
else
{
uint64_t v___x_5142_; 
v___x_5142_ = lean_uint64_add(v_quotient_5130_, v___x_5131_);
v___y_4846_ = v___x_5119_;
v___y_4847_ = v___y_5108_;
v___y_4848_ = v___y_5111_;
v___y_4849_ = v___x_5142_;
goto v___jp_4845_;
}
}
else
{
v___y_4846_ = v___x_5119_;
v___y_4847_ = v___y_5108_;
v___y_4848_ = v___y_5111_;
v___y_4849_ = v_quotient_5130_;
goto v___jp_4845_;
}
}
}
else
{
v___y_4846_ = v___x_5119_;
v___y_4847_ = v___y_5108_;
v___y_4848_ = v___y_5111_;
v___y_4849_ = v___x_5113_;
goto v___jp_4845_;
}
}
else
{
if (v___y_5111_ == 0)
{
uint32_t v___x_5143_; 
v___x_5143_ = 0;
return v___x_5143_;
}
else
{
uint32_t v___x_5144_; 
v___x_5144_ = 2147483648;
return v___x_5144_;
}
}
}
}
}
v___jp_5148_:
{
uint64_t v___x_5154_; uint64_t v___x_5155_; uint8_t v___x_5156_; 
v___x_5154_ = lean_uint32_to_uint64(v_ey_5147_);
v___x_5155_ = 0ULL;
v___x_5156_ = lean_uint64_dec_eq(v___x_5154_, v___x_5155_);
if (v___x_5156_ == 0)
{
uint64_t v___x_5157_; uint64_t v___x_5158_; 
v___x_5157_ = 1ULL;
v___x_5158_ = lean_uint64_sub(v___x_5154_, v___x_5157_);
v___y_5107_ = v___y_5149_;
v___y_5108_ = v___y_5150_;
v___y_5109_ = v___y_5153_;
v___y_5110_ = v___y_5151_;
v___y_5111_ = v___y_5152_;
v___y_5112_ = v___x_5158_;
goto v___jp_5106_;
}
else
{
v___y_5107_ = v___y_5149_;
v___y_5108_ = v___y_5150_;
v___y_5109_ = v___y_5153_;
v___y_5110_ = v___y_5151_;
v___y_5111_ = v___y_5152_;
v___y_5112_ = v___x_5155_;
goto v___jp_5106_;
}
}
v___jp_5159_:
{
uint64_t v___x_5164_; uint64_t v___x_5165_; uint8_t v___x_5166_; 
v___x_5164_ = lean_uint32_to_uint64(v_ex_5145_);
v___x_5165_ = 0ULL;
v___x_5166_ = lean_uint64_dec_eq(v___x_5164_, v___x_5165_);
if (v___x_5166_ == 0)
{
uint64_t v___x_5167_; uint64_t v___x_5168_; 
v___x_5167_ = 1ULL;
v___x_5168_ = lean_uint64_sub(v___x_5164_, v___x_5167_);
v___y_5149_ = v___y_5163_;
v___y_5150_ = v___y_5160_;
v___y_5151_ = v___y_5161_;
v___y_5152_ = v___y_5162_;
v___y_5153_ = v___x_5168_;
goto v___jp_5148_;
}
else
{
v___y_5149_ = v___y_5163_;
v___y_5150_ = v___y_5160_;
v___y_5151_ = v___y_5161_;
v___y_5152_ = v___y_5162_;
v___y_5153_ = v___x_5165_;
goto v___jp_5148_;
}
}
v___jp_5169_:
{
uint32_t v___x_5174_; uint8_t v___x_5175_; 
v___x_5174_ = 0;
v___x_5175_ = lean_uint32_dec_eq(v_ey_5147_, v___x_5174_);
if (v___x_5175_ == 0)
{
uint64_t v___x_5176_; uint64_t v___x_5177_; uint64_t v___x_5178_; 
v___x_5176_ = lean_uint32_to_uint64(v___y_5171_);
v___x_5177_ = 8388608ULL;
v___x_5178_ = lean_uint64_lor(v___x_5176_, v___x_5177_);
v___y_5160_ = v___y_5170_;
v___y_5161_ = v___y_5173_;
v___y_5162_ = v___y_5172_;
v___y_5163_ = v___x_5178_;
goto v___jp_5159_;
}
else
{
uint64_t v___x_5179_; 
v___x_5179_ = lean_uint32_to_uint64(v___y_5171_);
v___y_5160_ = v___y_5170_;
v___y_5161_ = v___y_5173_;
v___y_5162_ = v___y_5172_;
v___y_5163_ = v___x_5179_;
goto v___jp_5159_;
}
}
v___jp_5180_:
{
uint32_t v___x_5182_; uint32_t v_xFraction_5183_; uint32_t v_yFraction_5184_; uint32_t v___x_5185_; uint8_t v___x_5186_; 
v___x_5182_ = 8388607;
v_xFraction_5183_ = lean_uint32_land(v_x_4803_, v___x_5182_);
v_yFraction_5184_ = lean_uint32_land(v_y_4804_, v___x_5182_);
v___x_5185_ = 0;
v___x_5186_ = lean_uint32_dec_eq(v_ex_5145_, v___x_5185_);
if (v___x_5186_ == 0)
{
uint64_t v___x_5187_; uint64_t v___x_5188_; uint64_t v___x_5189_; 
v___x_5187_ = lean_uint32_to_uint64(v_xFraction_5183_);
v___x_5188_ = 8388608ULL;
v___x_5189_ = lean_uint64_lor(v___x_5187_, v___x_5188_);
v___y_5170_ = v___x_5182_;
v___y_5171_ = v_yFraction_5184_;
v___y_5172_ = v___y_5181_;
v___y_5173_ = v___x_5189_;
goto v___jp_5169_;
}
else
{
uint64_t v___x_5190_; 
v___x_5190_ = lean_uint32_to_uint64(v_xFraction_5183_);
v___y_5170_ = v___x_5182_;
v___y_5171_ = v_yFraction_5184_;
v___y_5172_ = v___y_5181_;
v___y_5173_ = v___x_5190_;
goto v___jp_5169_;
}
}
v___jp_5194_:
{
if (v___y_5196_ == 0)
{
v___y_5181_ = v___x_5193_;
goto v___jp_5180_;
}
else
{
v___y_5181_ = v___y_5195_;
goto v___jp_5180_;
}
}
v___jp_5197_:
{
if (v___y_5199_ == 0)
{
if (v___y_5200_ == 0)
{
v___y_5195_ = v___y_5198_;
v___y_5196_ = v___x_5193_;
goto v___jp_5194_;
}
else
{
v___y_5181_ = v___x_5193_;
goto v___jp_5180_;
}
}
else
{
v___y_5195_ = v___y_5198_;
v___y_5196_ = v___y_5200_;
goto v___jp_5194_;
}
}
v___jp_5201_:
{
uint32_t v___x_5204_; uint32_t v___x_5205_; uint32_t v___x_5206_; uint8_t v___x_5207_; 
v___x_5204_ = 2147483648;
v___x_5205_ = lean_uint32_land(v_y_4804_, v___x_5204_);
v___x_5206_ = 0;
v___x_5207_ = lean_uint32_dec_eq(v___x_5205_, v___x_5206_);
if (v___x_5207_ == 0)
{
v___y_5198_ = v___y_5202_;
v___y_5199_ = v___y_5203_;
v___y_5200_ = v___x_5193_;
goto v___jp_5197_;
}
else
{
v___y_5198_ = v___y_5202_;
v___y_5199_ = v___y_5203_;
v___y_5200_ = v___y_5202_;
goto v___jp_5197_;
}
}
v___jp_5208_:
{
if (v___y_5209_ == 0)
{
uint32_t v___x_5210_; uint32_t v___x_5211_; uint32_t v___x_5212_; uint8_t v___x_5213_; 
v___x_5210_ = 2147483648;
v___x_5211_ = lean_uint32_land(v_x_4803_, v___x_5210_);
v___x_5212_ = 0;
v___x_5213_ = lean_uint32_dec_eq(v___x_5211_, v___x_5212_);
if (v___x_5213_ == 0)
{
v___y_5202_ = v___y_5209_;
v___y_5203_ = v___x_5193_;
goto v___jp_5201_;
}
else
{
v___y_5202_ = v___y_5209_;
v___y_5203_ = v___y_5209_;
goto v___jp_5201_;
}
}
else
{
lean_object* v___x_5214_; lean_object* v___x_5215_; lean_object* v___x_5216_; lean_object* v___x_5217_; uint32_t v___x_5218_; 
v___x_5214_ = ((lean_object*)(lp_competition_Submission_TunedAdd_Fmt___closed__0));
v___x_5215_ = lean_uint32_to_nat(v_x_4803_);
v___x_5216_ = lean_uint32_to_nat(v_y_4804_);
v___x_5217_ = lp_floatlib_FloatLib_Floats_Formats_BinaryInterchange_Model_MulBackend_word(v___x_5214_, v___x_5215_, v___x_5216_);
v___x_5218_ = lean_uint32_of_nat(v___x_5217_);
lean_dec(v___x_5217_);
return v___x_5218_;
}
}
v___jp_5219_:
{
uint8_t v___x_5220_; 
v___x_5220_ = lean_uint32_dec_eq(v_ey_5147_, v___x_4862_);
if (v___x_5220_ == 0)
{
goto v___jp_4805_;
}
else
{
if (v___x_5193_ == 0)
{
uint32_t v___x_5221_; 
v___x_5221_ = lp_competition_Submission_FastMul_mul(v_x_4803_, v_y_4804_);
return v___x_5221_;
}
else
{
goto v___jp_4805_;
}
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_mul___boxed(lean_object* v_x_5230_, lean_object* v_y_5231_){
_start:
{
uint32_t v_x_boxed_5232_; uint32_t v_y_boxed_5233_; uint32_t v_res_5234_; lean_object* v_r_5235_; 
v_x_boxed_5232_ = lean_unbox_uint32(v_x_5230_);
lean_dec(v_x_5230_);
v_y_boxed_5233_ = lean_unbox_uint32(v_y_5231_);
lean_dec(v_y_5231_);
v_res_5234_ = lp_competition_Submission_mul(v_x_boxed_5232_, v_y_boxed_5233_);
v_r_5235_ = lean_box_uint32(v_res_5234_);
return v_r_5235_;
}
}
LEAN_EXPORT uint32_t lp_competition___private_Init_Data_Array_Basic_0__Array_foldlMUnsafe_fold___at___00Submission_referenceSum_spec__0(lean_object* v_as_5236_, size_t v_i_5237_, size_t v_stop_5238_, uint32_t v_b_5239_){
_start:
{
uint32_t v___y_5241_; float v___y_5246_; float v___y_5247_; uint8_t v___x_5250_; 
v___x_5250_ = lean_usize_dec_eq(v_i_5237_, v_stop_5238_);
if (v___x_5250_ == 0)
{
lean_object* v___x_5251_; float v___y_5253_; uint8_t v___y_5254_; float v___y_5272_; uint8_t v___y_5283_; uint8_t v___y_5298_; uint32_t v___x_5344_; uint32_t v___x_5345_; uint32_t v___x_5346_; uint32_t v___x_5347_; uint32_t v___x_5348_; uint8_t v___x_5349_; 
v___x_5251_ = lean_array_uget_borrowed(v_as_5236_, v_i_5237_);
v___x_5344_ = 2147483647;
v___x_5345_ = lean_uint32_land(v_b_5239_, v___x_5344_);
v___x_5346_ = 201326592;
v___x_5347_ = lean_uint32_sub(v___x_5345_, v___x_5346_);
v___x_5348_ = 1937768448;
v___x_5349_ = lean_uint32_dec_lt(v___x_5347_, v___x_5348_);
if (v___x_5349_ == 0)
{
v___y_5298_ = v___x_5349_;
goto v___jp_5297_;
}
else
{
uint32_t v___x_5350_; uint32_t v___x_5351_; uint32_t v___x_5352_; uint8_t v___x_5353_; 
v___x_5350_ = lean_unbox_uint32(v___x_5251_);
v___x_5351_ = lean_uint32_land(v___x_5350_, v___x_5344_);
v___x_5352_ = lean_uint32_sub(v___x_5351_, v___x_5346_);
v___x_5353_ = lean_uint32_dec_lt(v___x_5352_, v___x_5348_);
v___y_5298_ = v___x_5353_;
goto v___jp_5297_;
}
v___jp_5252_:
{
if (v___y_5254_ == 0)
{
uint32_t v___x_5255_; float v___x_5256_; 
v___x_5255_ = lean_unbox_uint32(v___x_5251_);
v___x_5256_ = lean_float32_of_bits(v___x_5255_);
v___y_5246_ = v___y_5253_;
v___y_5247_ = v___x_5256_;
goto v___jp_5245_;
}
else
{
uint32_t v___x_5257_; uint32_t v___x_5258_; uint32_t v___x_5259_; uint32_t v___x_5260_; uint32_t v___x_5261_; float v___x_5262_; lean_object* v___x_5263_; uint32_t v___x_5264_; uint32_t v___x_5265_; uint32_t v___x_5266_; lean_object* v___x_5267_; lean_object* v___x_5268_; float v___x_5269_; float v___x_5270_; 
v___x_5257_ = 8388607;
v___x_5258_ = lean_unbox_uint32(v___x_5251_);
v___x_5259_ = lean_uint32_land(v___x_5258_, v___x_5257_);
v___x_5260_ = 8388608;
v___x_5261_ = lean_uint32_lor(v___x_5259_, v___x_5260_);
v___x_5262_ = lean_uint32_to_float32(v___x_5261_);
v___x_5263_ = lp_competition_R2W01b_scaleTable;
v___x_5264_ = 23;
v___x_5265_ = lean_unbox_uint32(v___x_5251_);
v___x_5266_ = lean_uint32_shift_right(v___x_5265_, v___x_5264_);
v___x_5267_ = lean_uint32_to_nat(v___x_5266_);
v___x_5268_ = lean_array_fget_borrowed(v___x_5263_, v___x_5267_);
lean_dec(v___x_5267_);
v___x_5269_ = lean_unbox_float32(v___x_5268_);
v___x_5270_ = lean_float32_mul(v___x_5262_, v___x_5269_);
v___y_5246_ = v___y_5253_;
v___y_5247_ = v___x_5270_;
goto v___jp_5245_;
}
}
v___jp_5271_:
{
uint32_t v___x_5273_; uint32_t v___x_5274_; uint32_t v_a_5275_; uint32_t v___x_5276_; uint32_t v___x_5277_; uint32_t v___x_5278_; uint8_t v___x_5279_; 
v___x_5273_ = 2147483647;
v___x_5274_ = lean_unbox_uint32(v___x_5251_);
v_a_5275_ = lean_uint32_land(v___x_5274_, v___x_5273_);
v___x_5276_ = 201326591;
v___x_5277_ = 1;
v___x_5278_ = lean_uint32_sub(v_a_5275_, v___x_5277_);
v___x_5279_ = lean_uint32_dec_le(v___x_5276_, v___x_5278_);
if (v___x_5279_ == 0)
{
v___y_5253_ = v___y_5272_;
v___y_5254_ = v___x_5279_;
goto v___jp_5252_;
}
else
{
uint32_t v___x_5280_; uint8_t v___x_5281_; 
v___x_5280_ = 2139095040;
v___x_5281_ = lean_uint32_dec_lt(v_a_5275_, v___x_5280_);
v___y_5253_ = v___y_5272_;
v___y_5254_ = v___x_5281_;
goto v___jp_5252_;
}
}
v___jp_5282_:
{
if (v___y_5283_ == 0)
{
float v___x_5284_; 
v___x_5284_ = lean_float32_of_bits(v_b_5239_);
v___y_5272_ = v___x_5284_;
goto v___jp_5271_;
}
else
{
uint32_t v___x_5285_; uint32_t v___x_5286_; uint32_t v___x_5287_; uint32_t v___x_5288_; float v___x_5289_; lean_object* v___x_5290_; uint32_t v___x_5291_; uint32_t v___x_5292_; lean_object* v___x_5293_; lean_object* v___x_5294_; float v___x_5295_; float v___x_5296_; 
v___x_5285_ = 8388607;
v___x_5286_ = lean_uint32_land(v_b_5239_, v___x_5285_);
v___x_5287_ = 8388608;
v___x_5288_ = lean_uint32_lor(v___x_5286_, v___x_5287_);
v___x_5289_ = lean_uint32_to_float32(v___x_5288_);
v___x_5290_ = lp_competition_R2W01b_scaleTable;
v___x_5291_ = 23;
v___x_5292_ = lean_uint32_shift_right(v_b_5239_, v___x_5291_);
v___x_5293_ = lean_uint32_to_nat(v___x_5292_);
v___x_5294_ = lean_array_fget_borrowed(v___x_5290_, v___x_5293_);
lean_dec(v___x_5293_);
v___x_5295_ = lean_unbox_float32(v___x_5294_);
v___x_5296_ = lean_float32_mul(v___x_5289_, v___x_5295_);
v___y_5272_ = v___x_5296_;
goto v___jp_5271_;
}
}
v___jp_5297_:
{
if (v___y_5298_ == 0)
{
uint32_t v___x_5299_; uint32_t v___x_5300_; uint32_t v___x_5301_; uint32_t v___x_5302_; uint8_t v___x_5303_; 
v___x_5299_ = 23;
v___x_5300_ = lean_uint32_shift_right(v_b_5239_, v___x_5299_);
v___x_5301_ = 255;
v___x_5302_ = lean_uint32_land(v___x_5300_, v___x_5301_);
v___x_5303_ = lean_uint32_dec_eq(v___x_5302_, v___x_5301_);
if (v___x_5303_ == 0)
{
uint32_t v___x_5304_; uint32_t v___x_5305_; uint32_t v___x_5306_; uint8_t v___x_5307_; 
v___x_5304_ = lean_unbox_uint32(v___x_5251_);
v___x_5305_ = lean_uint32_shift_right(v___x_5304_, v___x_5299_);
v___x_5306_ = lean_uint32_land(v___x_5305_, v___x_5301_);
v___x_5307_ = lean_uint32_dec_eq(v___x_5306_, v___x_5301_);
if (v___x_5307_ == 0)
{
uint32_t v___x_5308_; uint32_t v_a_5309_; uint32_t v___x_5310_; uint32_t v___x_5311_; uint32_t v___x_5312_; uint8_t v___x_5313_; 
v___x_5308_ = 2147483647;
v_a_5309_ = lean_uint32_land(v_b_5239_, v___x_5308_);
v___x_5310_ = 201326591;
v___x_5311_ = 1;
v___x_5312_ = lean_uint32_sub(v_a_5309_, v___x_5311_);
v___x_5313_ = lean_uint32_dec_le(v___x_5310_, v___x_5312_);
if (v___x_5313_ == 0)
{
v___y_5283_ = v___x_5313_;
goto v___jp_5282_;
}
else
{
uint32_t v___x_5314_; uint8_t v___x_5315_; 
v___x_5314_ = 2139095040;
v___x_5315_ = lean_uint32_dec_lt(v_a_5309_, v___x_5314_);
v___y_5283_ = v___x_5315_;
goto v___jp_5282_;
}
}
else
{
uint32_t v___x_5316_; uint32_t v___x_5317_; 
v___x_5316_ = lean_unbox_uint32(v___x_5251_);
v___x_5317_ = lp_competition_Submission_TunedAdd_add(v_b_5239_, v___x_5316_);
v___y_5241_ = v___x_5317_;
goto v___jp_5240_;
}
}
else
{
uint32_t v___x_5318_; uint32_t v___x_5319_; 
v___x_5318_ = lean_unbox_uint32(v___x_5251_);
v___x_5319_ = lp_competition_Submission_TunedAdd_add(v_b_5239_, v___x_5318_);
v___y_5241_ = v___x_5319_;
goto v___jp_5240_;
}
}
else
{
uint32_t v___x_5320_; uint32_t v___x_5321_; uint32_t v___x_5322_; uint32_t v___x_5323_; float v___x_5324_; lean_object* v___x_5325_; uint32_t v___x_5326_; uint32_t v___x_5327_; lean_object* v___x_5328_; lean_object* v___x_5329_; float v___x_5330_; float v___x_5331_; uint32_t v___x_5332_; uint32_t v___x_5333_; uint32_t v___x_5334_; float v___x_5335_; uint32_t v___x_5336_; uint32_t v___x_5337_; lean_object* v___x_5338_; lean_object* v___x_5339_; float v___x_5340_; float v___x_5341_; float v___x_5342_; uint32_t v___x_5343_; 
v___x_5320_ = 8388607;
v___x_5321_ = lean_uint32_land(v_b_5239_, v___x_5320_);
v___x_5322_ = 8388608;
v___x_5323_ = lean_uint32_lor(v___x_5321_, v___x_5322_);
v___x_5324_ = lean_uint32_to_float32(v___x_5323_);
v___x_5325_ = lp_competition_R2W01b_scaleTable;
v___x_5326_ = 23;
v___x_5327_ = lean_uint32_shift_right(v_b_5239_, v___x_5326_);
v___x_5328_ = lean_uint32_to_nat(v___x_5327_);
v___x_5329_ = lean_array_fget_borrowed(v___x_5325_, v___x_5328_);
lean_dec(v___x_5328_);
v___x_5330_ = lean_unbox_float32(v___x_5329_);
v___x_5331_ = lean_float32_mul(v___x_5324_, v___x_5330_);
v___x_5332_ = lean_unbox_uint32(v___x_5251_);
v___x_5333_ = lean_uint32_land(v___x_5332_, v___x_5320_);
v___x_5334_ = lean_uint32_lor(v___x_5333_, v___x_5322_);
v___x_5335_ = lean_uint32_to_float32(v___x_5334_);
v___x_5336_ = lean_unbox_uint32(v___x_5251_);
v___x_5337_ = lean_uint32_shift_right(v___x_5336_, v___x_5326_);
v___x_5338_ = lean_uint32_to_nat(v___x_5337_);
v___x_5339_ = lean_array_fget_borrowed(v___x_5325_, v___x_5338_);
lean_dec(v___x_5338_);
v___x_5340_ = lean_unbox_float32(v___x_5339_);
v___x_5341_ = lean_float32_mul(v___x_5335_, v___x_5340_);
v___x_5342_ = lean_float32_add(v___x_5331_, v___x_5341_);
v___x_5343_ = lean_float32_to_bits(v___x_5342_);
v___y_5241_ = v___x_5343_;
goto v___jp_5240_;
}
}
}
else
{
return v_b_5239_;
}
v___jp_5240_:
{
size_t v___x_5242_; size_t v___x_5243_; 
v___x_5242_ = ((size_t)1ULL);
v___x_5243_ = lean_usize_add(v_i_5237_, v___x_5242_);
v_i_5237_ = v___x_5243_;
v_b_5239_ = v___y_5241_;
goto _start;
}
v___jp_5245_:
{
float v___x_5248_; uint32_t v___x_5249_; 
v___x_5248_ = lean_float32_add(v___y_5246_, v___y_5247_);
v___x_5249_ = lean_float32_to_bits(v___x_5248_);
v___y_5241_ = v___x_5249_;
goto v___jp_5240_;
}
}
}
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_foldlMUnsafe_fold___at___00Submission_referenceSum_spec__0___boxed(lean_object* v_as_5354_, lean_object* v_i_5355_, lean_object* v_stop_5356_, lean_object* v_b_5357_){
_start:
{
size_t v_i_boxed_5358_; size_t v_stop_boxed_5359_; uint32_t v_b_boxed_5360_; uint32_t v_res_5361_; lean_object* v_r_5362_; 
v_i_boxed_5358_ = lean_unbox_usize(v_i_5355_);
lean_dec(v_i_5355_);
v_stop_boxed_5359_ = lean_unbox_usize(v_stop_5356_);
lean_dec(v_stop_5356_);
v_b_boxed_5360_ = lean_unbox_uint32(v_b_5357_);
lean_dec(v_b_5357_);
v_res_5361_ = lp_competition___private_Init_Data_Array_Basic_0__Array_foldlMUnsafe_fold___at___00Submission_referenceSum_spec__0(v_as_5354_, v_i_boxed_5358_, v_stop_boxed_5359_, v_b_boxed_5360_);
lean_dec_ref(v_as_5354_);
v_r_5362_ = lean_box_uint32(v_res_5361_);
return v_r_5362_;
}
}
static lean_object* _init_lp_competition_Submission_referenceSum___redArg___closed__0(void){
_start:
{
lean_object* v___x_5363_; lean_object* v___x_5364_; lean_object* v___x_5365_; 
v___x_5363_ = lean_unsigned_to_nat(0u);
v___x_5364_ = lean_unsigned_to_nat(32u);
v___x_5365_ = l_BitVec_ofNat(v___x_5364_, v___x_5363_);
return v___x_5365_;
}
}
static uint32_t _init_lp_competition_Submission_referenceSum___redArg___closed__1(void){
_start:
{
lean_object* v___x_5366_; uint32_t v___x_5367_; 
v___x_5366_ = lean_obj_once(&lp_competition_Submission_referenceSum___redArg___closed__0, &lp_competition_Submission_referenceSum___redArg___closed__0_once, _init_lp_competition_Submission_referenceSum___redArg___closed__0);
v___x_5367_ = lean_uint32_of_nat(v___x_5366_);
return v___x_5367_;
}
}
LEAN_EXPORT uint32_t lp_competition_Submission_referenceSum___redArg(lean_object* v_x_5368_){
_start:
{
lean_object* v___x_5369_; uint32_t v___x_5370_; lean_object* v___x_5371_; uint8_t v___x_5372_; 
v___x_5369_ = lean_unsigned_to_nat(0u);
v___x_5370_ = lean_uint32_once(&lp_competition_Submission_referenceSum___redArg___closed__1, &lp_competition_Submission_referenceSum___redArg___closed__1_once, _init_lp_competition_Submission_referenceSum___redArg___closed__1);
v___x_5371_ = lean_array_get_size(v_x_5368_);
v___x_5372_ = lean_nat_dec_lt(v___x_5369_, v___x_5371_);
if (v___x_5372_ == 0)
{
return v___x_5370_;
}
else
{
uint8_t v___x_5373_; 
v___x_5373_ = lean_nat_dec_le(v___x_5371_, v___x_5371_);
if (v___x_5373_ == 0)
{
if (v___x_5372_ == 0)
{
return v___x_5370_;
}
else
{
size_t v___x_5374_; size_t v___x_5375_; uint32_t v___x_5376_; 
v___x_5374_ = ((size_t)0ULL);
v___x_5375_ = lean_usize_of_nat(v___x_5371_);
v___x_5376_ = lp_competition___private_Init_Data_Array_Basic_0__Array_foldlMUnsafe_fold___at___00Submission_referenceSum_spec__0(v_x_5368_, v___x_5374_, v___x_5375_, v___x_5370_);
return v___x_5376_;
}
}
else
{
size_t v___x_5377_; size_t v___x_5378_; uint32_t v___x_5379_; 
v___x_5377_ = ((size_t)0ULL);
v___x_5378_ = lean_usize_of_nat(v___x_5371_);
v___x_5379_ = lp_competition___private_Init_Data_Array_Basic_0__Array_foldlMUnsafe_fold___at___00Submission_referenceSum_spec__0(v_x_5368_, v___x_5377_, v___x_5378_, v___x_5370_);
return v___x_5379_;
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_referenceSum___redArg___boxed(lean_object* v_x_5380_){
_start:
{
uint32_t v_res_5381_; lean_object* v_r_5382_; 
v_res_5381_ = lp_competition_Submission_referenceSum___redArg(v_x_5380_);
lean_dec_ref(v_x_5380_);
v_r_5382_ = lean_box_uint32(v_res_5381_);
return v_r_5382_;
}
}
LEAN_EXPORT uint32_t lp_competition_Submission_referenceSum(lean_object* v_n_5383_, lean_object* v_x_5384_){
_start:
{
uint32_t v___x_5385_; 
v___x_5385_ = lp_competition_Submission_referenceSum___redArg(v_x_5384_);
return v___x_5385_;
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_referenceSum___boxed(lean_object* v_n_5386_, lean_object* v_x_5387_){
_start:
{
uint32_t v_res_5388_; lean_object* v_r_5389_; 
v_res_5388_ = lp_competition_Submission_referenceSum(v_n_5386_, v_x_5387_);
lean_dec_ref(v_x_5387_);
lean_dec(v_n_5386_);
v_r_5389_ = lean_box_uint32(v_res_5388_);
return v_r_5389_;
}
}
LEAN_EXPORT uint32_t lp_competition_Fin_foldl_loop___at___00Submission_referenceBmm_spec__0(lean_object* v_A_5390_, lean_object* v_fst_5391_, lean_object* v_m_5392_, lean_object* v_fst_5393_, lean_object* v_n_5394_, lean_object* v_B_5395_, lean_object* v_p_5396_, lean_object* v_snd_5397_, lean_object* v_n_5398_, uint32_t v_x_5399_, lean_object* v_i_5400_){
_start:
{
uint32_t v___y_5402_; float v___y_5407_; float v___y_5408_; uint32_t v___y_5412_; float v___y_5413_; uint8_t v___y_5414_; uint32_t v___y_5429_; float v___y_5430_; uint32_t v___y_5440_; uint8_t v___y_5441_; uint32_t v___y_5456_; uint8_t v___x_5458_; uint32_t v___y_5460_; uint8_t v___y_5461_; uint32_t v___y_5502_; uint32_t v___y_5513_; uint32_t v___y_5517_; uint32_t v___y_5521_; uint32_t v___y_5522_; uint32_t v___y_5523_; uint8_t v___y_5527_; uint64_t v___y_5528_; uint32_t v___y_5529_; uint64_t v___y_5530_; uint32_t v___y_5542_; uint32_t v___y_5543_; uint32_t v___y_5544_; uint32_t v___y_5545_; uint32_t v___y_5546_; uint32_t v___y_5547_; uint8_t v___y_5554_; uint32_t v___y_5555_; uint32_t v___y_5556_; uint32_t v___y_5557_; uint32_t v___y_5558_; uint32_t v___y_5559_; uint64_t v___y_5563_; uint8_t v___y_5564_; uint32_t v___y_5565_; uint32_t v___y_5566_; uint32_t v___y_5567_; uint64_t v___y_5568_; uint64_t v___y_5569_; uint8_t v___y_5579_; uint64_t v___y_5580_; uint32_t v___y_5581_; uint32_t v___y_5582_; uint64_t v___y_5583_; uint8_t v___y_5584_; uint32_t v___y_5585_; uint64_t v___y_5586_; uint64_t v___y_5593_; uint8_t v___y_5594_; uint32_t v___y_5595_; uint32_t v___y_5596_; uint64_t v___y_5597_; uint32_t v___y_5598_; uint64_t v___y_5599_; uint8_t v___y_5605_; uint64_t v___y_5606_; uint64_t v___y_5607_; uint32_t v___y_5608_; uint32_t v___y_5609_; uint64_t v___y_5610_; uint32_t v___y_5611_; uint64_t v___y_5612_; uint8_t v___y_5667_; uint64_t v___y_5668_; uint64_t v___y_5669_; uint32_t v___y_5670_; uint64_t v___y_5671_; uint32_t v___y_5672_; uint64_t v___y_5673_; uint32_t v___y_5674_; uint64_t v___y_5675_; uint64_t v___y_5681_; uint8_t v___y_5682_; uint64_t v___y_5683_; uint64_t v___y_5684_; uint64_t v___y_5685_; uint32_t v___y_5686_; uint64_t v___y_5687_; uint32_t v___y_5688_; uint64_t v___y_5689_; uint32_t v___y_5690_; uint64_t v___y_5691_; uint8_t v___y_5696_; uint64_t v___y_5697_; uint64_t v___y_5698_; uint64_t v___y_5699_; uint32_t v___y_5700_; uint64_t v___y_5701_; uint32_t v___y_5702_; uint32_t v___y_5703_; uint64_t v___y_5704_; uint64_t v___y_5709_; uint8_t v___y_5710_; uint64_t v___y_5711_; uint32_t v___y_5712_; uint64_t v___y_5713_; uint32_t v___y_5714_; uint64_t v___y_5715_; uint64_t v___y_5716_; uint64_t v___y_5717_; uint32_t v___y_5718_; uint64_t v___y_5719_; uint8_t v___y_5724_; uint64_t v___y_5725_; uint64_t v___y_5726_; uint32_t v___y_5727_; uint64_t v___y_5728_; uint64_t v___y_5729_; uint32_t v___y_5730_; uint32_t v___y_5731_; uint64_t v___y_5732_; uint64_t v___y_5737_; uint8_t v___y_5738_; uint64_t v___y_5739_; uint32_t v___y_5740_; uint32_t v___y_5741_; uint64_t v___y_5742_; uint64_t v___y_5743_; uint64_t v___y_5744_; uint64_t v___y_5745_; uint32_t v___y_5746_; uint64_t v___y_5747_; uint8_t v___y_5752_; uint64_t v___y_5753_; uint64_t v___y_5754_; uint32_t v___y_5755_; uint64_t v___y_5756_; uint32_t v___y_5757_; uint64_t v___y_5758_; uint32_t v___y_5759_; uint64_t v___y_5760_; uint64_t v___y_5765_; uint64_t v___y_5766_; uint8_t v___y_5767_; uint64_t v___y_5768_; uint64_t v___y_5769_; uint32_t v___y_5770_; uint32_t v___y_5771_; uint64_t v___y_5772_; uint64_t v___y_5773_; uint32_t v___y_5774_; uint64_t v___y_5775_; uint8_t v___y_5780_; uint64_t v___y_5781_; uint64_t v___y_5782_; uint64_t v___y_5783_; uint32_t v___y_5784_; uint64_t v___y_5785_; uint32_t v___y_5786_; uint32_t v___y_5787_; uint64_t v___y_5788_; uint64_t v___y_5793_; uint8_t v___y_5794_; uint64_t v___y_5795_; uint64_t v___y_5796_; uint32_t v___y_5797_; uint32_t v___y_5798_; uint64_t v___y_5799_; uint32_t v___y_5800_; uint64_t v___y_5801_; uint8_t v___y_5805_; uint64_t v___y_5806_; uint32_t v___y_5807_; uint64_t v___y_5808_; uint32_t v___y_5809_; uint32_t v___y_5810_; uint32_t v___y_5819_; uint32_t v___y_5820_; uint32_t v___y_5821_; uint8_t v___y_5825_; uint32_t v___y_5826_; uint64_t v___y_5827_; uint64_t v___y_5828_; uint8_t v___y_5840_; uint64_t v___y_5841_; uint32_t v___y_5842_; uint64_t v___y_5843_; uint32_t v___y_5844_; uint32_t v___y_5845_; uint64_t v___y_5846_; uint64_t v___y_5847_; uint8_t v___y_5881_; uint64_t v___y_5882_; uint32_t v___y_5883_; uint32_t v___y_5884_; uint32_t v___y_5885_; uint32_t v___y_5886_; uint64_t v___y_5887_; uint64_t v___y_5888_; uint8_t v___y_5895_; uint32_t v___y_5896_; uint32_t v___y_5897_; uint32_t v___y_5898_; uint32_t v___y_5899_; uint32_t v___y_5900_; uint64_t v___y_5901_; uint64_t v___y_5902_; uint8_t v___y_5909_; uint32_t v___y_5910_; uint32_t v___y_5911_; uint32_t v___y_5912_; uint32_t v___y_5913_; uint32_t v___y_5914_; uint32_t v___y_5915_; uint64_t v___y_5916_; uint32_t v___y_5924_; uint32_t v___y_5925_; uint32_t v___y_5926_; uint32_t v___y_5927_; uint32_t v___y_5928_; uint32_t v___y_5929_; uint8_t v___y_5930_; uint32_t v___y_5941_; uint32_t v___y_5942_; uint32_t v___y_5948_; uint8_t v___y_5949_; uint32_t v___y_5950_; uint32_t v___y_5951_; uint32_t v___y_5952_; uint8_t v___y_5953_; uint32_t v___y_5958_; uint8_t v___y_5959_; uint32_t v___y_5960_; uint32_t v___y_5961_; uint32_t v___y_5962_; uint32_t v___y_5963_; uint32_t v___y_5964_; uint8_t v___y_5965_; uint32_t v___y_5967_; uint8_t v___y_5968_; uint8_t v___y_5969_; uint32_t v___y_5970_; uint32_t v___y_5971_; uint32_t v___y_5972_; uint32_t v___y_5973_; uint32_t v___y_5974_; uint8_t v___y_5975_; uint32_t v___y_5977_; uint8_t v___y_5978_; uint32_t v___y_5979_; uint32_t v___y_5980_; uint32_t v___y_5981_; uint32_t v___y_5982_; uint32_t v___y_5983_; uint8_t v___y_5984_; uint32_t v___y_5990_; uint32_t v___y_5991_; uint32_t v___y_5992_; uint32_t v___y_5993_; uint32_t v___y_5994_; uint32_t v___y_5995_; uint8_t v___y_5996_; uint32_t v___y_6006_; uint32_t v___y_6007_; 
v___x_5458_ = lean_nat_dec_lt(v_i_5400_, v_n_5398_);
if (v___x_5458_ == 0)
{
lean_dec(v_i_5400_);
return v_x_5399_;
}
else
{
lean_object* v___x_6024_; lean_object* v___x_6025_; lean_object* v___x_6026_; lean_object* v___x_6027_; uint32_t v___x_6028_; uint32_t v___y_6030_; lean_object* v___x_6039_; uint8_t v___x_6040_; 
v___x_6024_ = lean_nat_mul(v_fst_5391_, v_m_5392_);
v___x_6025_ = lean_nat_add(v___x_6024_, v_fst_5393_);
lean_dec(v___x_6024_);
v___x_6026_ = lean_nat_mul(v___x_6025_, v_n_5394_);
lean_dec(v___x_6025_);
v___x_6027_ = lean_nat_add(v___x_6026_, v_i_5400_);
lean_dec(v___x_6026_);
v___x_6028_ = lean_uint32_once(&lp_competition_Submission_referenceSum___redArg___closed__1, &lp_competition_Submission_referenceSum___redArg___closed__1_once, _init_lp_competition_Submission_referenceSum___redArg___closed__1);
v___x_6039_ = lean_array_get_size(v_A_5390_);
v___x_6040_ = lean_nat_dec_lt(v___x_6027_, v___x_6039_);
if (v___x_6040_ == 0)
{
lean_dec(v___x_6027_);
v___y_6030_ = v___x_6028_;
goto v___jp_6029_;
}
else
{
lean_object* v___x_6041_; uint32_t v___x_6042_; 
v___x_6041_ = lean_array_fget_borrowed(v_A_5390_, v___x_6027_);
lean_dec(v___x_6027_);
v___x_6042_ = lean_unbox_uint32(v___x_6041_);
v___y_6030_ = v___x_6042_;
goto v___jp_6029_;
}
v___jp_6029_:
{
lean_object* v___x_6031_; lean_object* v___x_6032_; lean_object* v___x_6033_; lean_object* v___x_6034_; lean_object* v___x_6035_; uint8_t v___x_6036_; 
v___x_6031_ = lean_nat_mul(v_fst_5391_, v_n_5394_);
v___x_6032_ = lean_nat_add(v___x_6031_, v_i_5400_);
lean_dec(v___x_6031_);
v___x_6033_ = lean_nat_mul(v___x_6032_, v_p_5396_);
lean_dec(v___x_6032_);
v___x_6034_ = lean_nat_add(v___x_6033_, v_snd_5397_);
lean_dec(v___x_6033_);
v___x_6035_ = lean_array_get_size(v_B_5395_);
v___x_6036_ = lean_nat_dec_lt(v___x_6034_, v___x_6035_);
if (v___x_6036_ == 0)
{
lean_dec(v___x_6034_);
v___y_6006_ = v___y_6030_;
v___y_6007_ = v___x_6028_;
goto v___jp_6005_;
}
else
{
lean_object* v___x_6037_; uint32_t v___x_6038_; 
v___x_6037_ = lean_array_fget_borrowed(v_B_5395_, v___x_6034_);
lean_dec(v___x_6034_);
v___x_6038_ = lean_unbox_uint32(v___x_6037_);
v___y_6006_ = v___y_6030_;
v___y_6007_ = v___x_6038_;
goto v___jp_6005_;
}
}
}
v___jp_5401_:
{
lean_object* v___x_5403_; lean_object* v___x_5404_; 
v___x_5403_ = lean_unsigned_to_nat(1u);
v___x_5404_ = lean_nat_add(v_i_5400_, v___x_5403_);
lean_dec(v_i_5400_);
v_x_5399_ = v___y_5402_;
v_i_5400_ = v___x_5404_;
goto _start;
}
v___jp_5406_:
{
float v___x_5409_; uint32_t v___x_5410_; 
v___x_5409_ = lean_float32_add(v___y_5407_, v___y_5408_);
v___x_5410_ = lean_float32_to_bits(v___x_5409_);
v___y_5402_ = v___x_5410_;
goto v___jp_5401_;
}
v___jp_5411_:
{
if (v___y_5414_ == 0)
{
float v___x_5415_; 
v___x_5415_ = lean_float32_of_bits(v___y_5412_);
v___y_5407_ = v___y_5413_;
v___y_5408_ = v___x_5415_;
goto v___jp_5406_;
}
else
{
uint32_t v___x_5416_; uint32_t v___x_5417_; uint32_t v___x_5418_; uint32_t v___x_5419_; float v___x_5420_; lean_object* v___x_5421_; uint32_t v___x_5422_; uint32_t v___x_5423_; lean_object* v___x_5424_; lean_object* v___x_5425_; float v___x_5426_; float v___x_5427_; 
v___x_5416_ = 8388607;
v___x_5417_ = lean_uint32_land(v___y_5412_, v___x_5416_);
v___x_5418_ = 8388608;
v___x_5419_ = lean_uint32_lor(v___x_5417_, v___x_5418_);
v___x_5420_ = lean_uint32_to_float32(v___x_5419_);
v___x_5421_ = lp_competition_R2W01b_scaleTable;
v___x_5422_ = 23;
v___x_5423_ = lean_uint32_shift_right(v___y_5412_, v___x_5422_);
v___x_5424_ = lean_uint32_to_nat(v___x_5423_);
v___x_5425_ = lean_array_fget_borrowed(v___x_5421_, v___x_5424_);
lean_dec(v___x_5424_);
v___x_5426_ = lean_unbox_float32(v___x_5425_);
v___x_5427_ = lean_float32_mul(v___x_5420_, v___x_5426_);
v___y_5407_ = v___y_5413_;
v___y_5408_ = v___x_5427_;
goto v___jp_5406_;
}
}
v___jp_5428_:
{
uint32_t v___x_5431_; uint32_t v_a_5432_; uint32_t v___x_5433_; uint32_t v___x_5434_; uint32_t v___x_5435_; uint8_t v___x_5436_; 
v___x_5431_ = 2147483647;
v_a_5432_ = lean_uint32_land(v___y_5429_, v___x_5431_);
v___x_5433_ = 201326591;
v___x_5434_ = 1;
v___x_5435_ = lean_uint32_sub(v_a_5432_, v___x_5434_);
v___x_5436_ = lean_uint32_dec_le(v___x_5433_, v___x_5435_);
if (v___x_5436_ == 0)
{
v___y_5412_ = v___y_5429_;
v___y_5413_ = v___y_5430_;
v___y_5414_ = v___x_5436_;
goto v___jp_5411_;
}
else
{
uint32_t v___x_5437_; uint8_t v___x_5438_; 
v___x_5437_ = 2139095040;
v___x_5438_ = lean_uint32_dec_lt(v_a_5432_, v___x_5437_);
v___y_5412_ = v___y_5429_;
v___y_5413_ = v___y_5430_;
v___y_5414_ = v___x_5438_;
goto v___jp_5411_;
}
}
v___jp_5439_:
{
if (v___y_5441_ == 0)
{
float v___x_5442_; 
v___x_5442_ = lean_float32_of_bits(v_x_5399_);
v___y_5429_ = v___y_5440_;
v___y_5430_ = v___x_5442_;
goto v___jp_5428_;
}
else
{
uint32_t v___x_5443_; uint32_t v___x_5444_; uint32_t v___x_5445_; uint32_t v___x_5446_; float v___x_5447_; lean_object* v___x_5448_; uint32_t v___x_5449_; uint32_t v___x_5450_; lean_object* v___x_5451_; lean_object* v___x_5452_; float v___x_5453_; float v___x_5454_; 
v___x_5443_ = 8388607;
v___x_5444_ = lean_uint32_land(v_x_5399_, v___x_5443_);
v___x_5445_ = 8388608;
v___x_5446_ = lean_uint32_lor(v___x_5444_, v___x_5445_);
v___x_5447_ = lean_uint32_to_float32(v___x_5446_);
v___x_5448_ = lp_competition_R2W01b_scaleTable;
v___x_5449_ = 23;
v___x_5450_ = lean_uint32_shift_right(v_x_5399_, v___x_5449_);
v___x_5451_ = lean_uint32_to_nat(v___x_5450_);
v___x_5452_ = lean_array_fget_borrowed(v___x_5448_, v___x_5451_);
lean_dec(v___x_5451_);
v___x_5453_ = lean_unbox_float32(v___x_5452_);
v___x_5454_ = lean_float32_mul(v___x_5447_, v___x_5453_);
v___y_5429_ = v___y_5440_;
v___y_5430_ = v___x_5454_;
goto v___jp_5428_;
}
}
v___jp_5455_:
{
uint32_t v___x_5457_; 
v___x_5457_ = lp_competition_Submission_TunedAdd_add(v_x_5399_, v___y_5456_);
v___y_5402_ = v___x_5457_;
goto v___jp_5401_;
}
v___jp_5459_:
{
if (v___y_5461_ == 0)
{
uint32_t v___x_5462_; uint32_t v___x_5463_; uint32_t v___x_5464_; uint32_t v___x_5465_; uint8_t v___x_5466_; 
v___x_5462_ = 23;
v___x_5463_ = lean_uint32_shift_right(v_x_5399_, v___x_5462_);
v___x_5464_ = 255;
v___x_5465_ = lean_uint32_land(v___x_5463_, v___x_5464_);
v___x_5466_ = lean_uint32_dec_eq(v___x_5465_, v___x_5464_);
if (v___x_5466_ == 0)
{
if (v___x_5458_ == 0)
{
v___y_5456_ = v___y_5460_;
goto v___jp_5455_;
}
else
{
uint32_t v___x_5467_; uint32_t v___x_5468_; uint8_t v___x_5469_; 
v___x_5467_ = lean_uint32_shift_right(v___y_5460_, v___x_5462_);
v___x_5468_ = lean_uint32_land(v___x_5467_, v___x_5464_);
v___x_5469_ = lean_uint32_dec_eq(v___x_5468_, v___x_5464_);
if (v___x_5469_ == 0)
{
uint32_t v___x_5470_; uint32_t v_a_5471_; uint32_t v___x_5472_; uint32_t v___x_5473_; uint32_t v___x_5474_; uint8_t v___x_5475_; 
v___x_5470_ = 2147483647;
v_a_5471_ = lean_uint32_land(v_x_5399_, v___x_5470_);
v___x_5472_ = 201326591;
v___x_5473_ = 1;
v___x_5474_ = lean_uint32_sub(v_a_5471_, v___x_5473_);
v___x_5475_ = lean_uint32_dec_le(v___x_5472_, v___x_5474_);
if (v___x_5475_ == 0)
{
v___y_5440_ = v___y_5460_;
v___y_5441_ = v___x_5475_;
goto v___jp_5439_;
}
else
{
uint32_t v___x_5476_; uint8_t v___x_5477_; 
v___x_5476_ = 2139095040;
v___x_5477_ = lean_uint32_dec_lt(v_a_5471_, v___x_5476_);
v___y_5440_ = v___y_5460_;
v___y_5441_ = v___x_5477_;
goto v___jp_5439_;
}
}
else
{
uint32_t v___x_5478_; 
v___x_5478_ = lp_competition_Submission_TunedAdd_add(v_x_5399_, v___y_5460_);
v___y_5402_ = v___x_5478_;
goto v___jp_5401_;
}
}
}
else
{
v___y_5456_ = v___y_5460_;
goto v___jp_5455_;
}
}
else
{
uint32_t v___x_5479_; uint32_t v___x_5480_; uint32_t v___x_5481_; uint32_t v___x_5482_; float v___x_5483_; lean_object* v___x_5484_; uint32_t v___x_5485_; uint32_t v___x_5486_; lean_object* v___x_5487_; lean_object* v___x_5488_; float v___x_5489_; float v___x_5490_; uint32_t v___x_5491_; uint32_t v___x_5492_; float v___x_5493_; uint32_t v___x_5494_; lean_object* v___x_5495_; lean_object* v___x_5496_; float v___x_5497_; float v___x_5498_; float v___x_5499_; uint32_t v___x_5500_; 
v___x_5479_ = 8388607;
v___x_5480_ = lean_uint32_land(v_x_5399_, v___x_5479_);
v___x_5481_ = 8388608;
v___x_5482_ = lean_uint32_lor(v___x_5480_, v___x_5481_);
v___x_5483_ = lean_uint32_to_float32(v___x_5482_);
v___x_5484_ = lp_competition_R2W01b_scaleTable;
v___x_5485_ = 23;
v___x_5486_ = lean_uint32_shift_right(v_x_5399_, v___x_5485_);
v___x_5487_ = lean_uint32_to_nat(v___x_5486_);
v___x_5488_ = lean_array_fget_borrowed(v___x_5484_, v___x_5487_);
lean_dec(v___x_5487_);
v___x_5489_ = lean_unbox_float32(v___x_5488_);
v___x_5490_ = lean_float32_mul(v___x_5483_, v___x_5489_);
v___x_5491_ = lean_uint32_land(v___y_5460_, v___x_5479_);
v___x_5492_ = lean_uint32_lor(v___x_5491_, v___x_5481_);
v___x_5493_ = lean_uint32_to_float32(v___x_5492_);
v___x_5494_ = lean_uint32_shift_right(v___y_5460_, v___x_5485_);
v___x_5495_ = lean_uint32_to_nat(v___x_5494_);
v___x_5496_ = lean_array_fget_borrowed(v___x_5484_, v___x_5495_);
lean_dec(v___x_5495_);
v___x_5497_ = lean_unbox_float32(v___x_5496_);
v___x_5498_ = lean_float32_mul(v___x_5493_, v___x_5497_);
v___x_5499_ = lean_float32_add(v___x_5490_, v___x_5498_);
v___x_5500_ = lean_float32_to_bits(v___x_5499_);
v___y_5402_ = v___x_5500_;
goto v___jp_5401_;
}
}
v___jp_5501_:
{
uint32_t v___x_5503_; uint32_t v___x_5504_; uint32_t v___x_5505_; uint32_t v___x_5506_; uint32_t v___x_5507_; uint8_t v___x_5508_; 
v___x_5503_ = 2147483647;
v___x_5504_ = lean_uint32_land(v_x_5399_, v___x_5503_);
v___x_5505_ = 201326592;
v___x_5506_ = lean_uint32_sub(v___x_5504_, v___x_5505_);
v___x_5507_ = 1937768448;
v___x_5508_ = lean_uint32_dec_lt(v___x_5506_, v___x_5507_);
if (v___x_5508_ == 0)
{
v___y_5460_ = v___y_5502_;
v___y_5461_ = v___x_5508_;
goto v___jp_5459_;
}
else
{
uint32_t v___x_5509_; uint32_t v___x_5510_; uint8_t v___x_5511_; 
v___x_5509_ = lean_uint32_land(v___y_5502_, v___x_5503_);
v___x_5510_ = lean_uint32_sub(v___x_5509_, v___x_5505_);
v___x_5511_ = lean_uint32_dec_lt(v___x_5510_, v___x_5507_);
v___y_5460_ = v___y_5502_;
v___y_5461_ = v___x_5511_;
goto v___jp_5459_;
}
}
v___jp_5512_:
{
uint32_t v___x_5514_; uint32_t v___x_5515_; 
v___x_5514_ = 8388608;
v___x_5515_ = lean_uint32_lor(v___y_5513_, v___x_5514_);
v___y_5502_ = v___x_5515_;
goto v___jp_5501_;
}
v___jp_5516_:
{
uint32_t v___x_5518_; uint32_t v___x_5519_; 
v___x_5518_ = 8388608;
v___x_5519_ = lean_uint32_lor(v___y_5517_, v___x_5518_);
v___y_5502_ = v___x_5519_;
goto v___jp_5501_;
}
v___jp_5520_:
{
uint32_t v___x_5524_; uint32_t v___x_5525_; 
v___x_5524_ = lean_uint32_land(v___y_5522_, v___y_5521_);
v___x_5525_ = lean_uint32_lor(v___y_5523_, v___x_5524_);
v___y_5502_ = v___x_5525_;
goto v___jp_5501_;
}
v___jp_5526_:
{
uint8_t v___x_5531_; 
v___x_5531_ = lean_uint64_dec_eq(v___y_5530_, v___y_5528_);
if (v___x_5531_ == 0)
{
uint64_t v___x_5532_; uint8_t v___x_5533_; 
v___x_5532_ = 8388608ULL;
v___x_5533_ = lean_uint64_dec_eq(v___y_5530_, v___x_5532_);
if (v___x_5533_ == 0)
{
uint32_t v___x_5534_; 
v___x_5534_ = lean_uint64_to_uint32(v___y_5530_);
if (v___y_5527_ == 0)
{
uint32_t v___x_5535_; 
v___x_5535_ = 0;
v___y_5521_ = v___y_5529_;
v___y_5522_ = v___x_5534_;
v___y_5523_ = v___x_5535_;
goto v___jp_5520_;
}
else
{
uint32_t v___x_5536_; 
v___x_5536_ = 2147483648;
v___y_5521_ = v___y_5529_;
v___y_5522_ = v___x_5534_;
v___y_5523_ = v___x_5536_;
goto v___jp_5520_;
}
}
else
{
if (v___y_5527_ == 0)
{
uint32_t v___x_5537_; 
v___x_5537_ = 0;
v___y_5513_ = v___x_5537_;
goto v___jp_5512_;
}
else
{
uint32_t v___x_5538_; 
v___x_5538_ = 2147483648;
v___y_5513_ = v___x_5538_;
goto v___jp_5512_;
}
}
}
else
{
if (v___y_5527_ == 0)
{
uint32_t v___x_5539_; 
v___x_5539_ = 0;
v___y_5502_ = v___x_5539_;
goto v___jp_5501_;
}
else
{
uint32_t v___x_5540_; 
v___x_5540_ = 2147483648;
v___y_5502_ = v___x_5540_;
goto v___jp_5501_;
}
}
}
v___jp_5541_:
{
uint32_t v___x_5548_; uint32_t v___x_5549_; uint32_t v___x_5550_; uint32_t v___x_5551_; uint32_t v___x_5552_; 
v___x_5548_ = lean_uint32_land(v___y_5546_, v___y_5545_);
v___x_5549_ = lean_uint32_shift_left(v___x_5548_, v___y_5542_);
v___x_5550_ = lean_uint32_lor(v___y_5547_, v___x_5549_);
v___x_5551_ = lean_uint32_land(v___y_5544_, v___y_5543_);
v___x_5552_ = lean_uint32_lor(v___x_5550_, v___x_5551_);
v___y_5502_ = v___x_5552_;
goto v___jp_5501_;
}
v___jp_5553_:
{
if (v___y_5554_ == 0)
{
uint32_t v___x_5560_; 
v___x_5560_ = 0;
v___y_5542_ = v___y_5555_;
v___y_5543_ = v___y_5556_;
v___y_5544_ = v___y_5559_;
v___y_5545_ = v___y_5557_;
v___y_5546_ = v___y_5558_;
v___y_5547_ = v___x_5560_;
goto v___jp_5541_;
}
else
{
uint32_t v___x_5561_; 
v___x_5561_ = 2147483648;
v___y_5542_ = v___y_5555_;
v___y_5543_ = v___y_5556_;
v___y_5544_ = v___y_5559_;
v___y_5545_ = v___y_5557_;
v___y_5546_ = v___y_5558_;
v___y_5547_ = v___x_5561_;
goto v___jp_5541_;
}
}
v___jp_5562_:
{
uint64_t v___x_5570_; uint64_t v_encodedExponent_5571_; uint32_t v___x_5572_; uint64_t v___x_5573_; uint8_t v___x_5574_; 
v___x_5570_ = 171ULL;
v_encodedExponent_5571_ = lean_uint64_sub(v___y_5568_, v___x_5570_);
v___x_5572_ = lean_uint64_to_uint32(v_encodedExponent_5571_);
v___x_5573_ = 8388608ULL;
v___x_5574_ = lean_uint64_dec_lt(v___y_5569_, v___x_5573_);
if (v___x_5574_ == 0)
{
uint64_t v___x_5575_; uint32_t v___x_5576_; 
v___x_5575_ = lean_uint64_sub(v___y_5569_, v___x_5573_);
v___x_5576_ = lean_uint64_to_uint32(v___x_5575_);
v___y_5554_ = v___y_5564_;
v___y_5555_ = v___y_5565_;
v___y_5556_ = v___y_5566_;
v___y_5557_ = v___y_5567_;
v___y_5558_ = v___x_5572_;
v___y_5559_ = v___x_5576_;
goto v___jp_5553_;
}
else
{
uint32_t v___x_5577_; 
v___x_5577_ = lean_uint64_to_uint32(v___y_5563_);
v___y_5554_ = v___y_5564_;
v___y_5555_ = v___y_5565_;
v___y_5556_ = v___y_5566_;
v___y_5557_ = v___y_5567_;
v___y_5558_ = v___x_5572_;
v___y_5559_ = v___x_5577_;
goto v___jp_5553_;
}
}
v___jp_5578_:
{
uint64_t v___x_5587_; uint8_t v___x_5588_; 
v___x_5587_ = 425ULL;
v___x_5588_ = lean_uint64_dec_lt(v___x_5587_, v___y_5586_);
if (v___x_5588_ == 0)
{
if (v___y_5584_ == 0)
{
v___y_5563_ = v___y_5580_;
v___y_5564_ = v___y_5579_;
v___y_5565_ = v___y_5581_;
v___y_5566_ = v___y_5582_;
v___y_5567_ = v___y_5585_;
v___y_5568_ = v___y_5586_;
v___y_5569_ = v___y_5583_;
goto v___jp_5562_;
}
else
{
uint64_t v___x_5589_; 
v___x_5589_ = 8388608ULL;
v___y_5563_ = v___y_5580_;
v___y_5564_ = v___y_5579_;
v___y_5565_ = v___y_5581_;
v___y_5566_ = v___y_5582_;
v___y_5567_ = v___y_5585_;
v___y_5568_ = v___y_5586_;
v___y_5569_ = v___x_5589_;
goto v___jp_5562_;
}
}
else
{
if (v___y_5579_ == 0)
{
uint32_t v___x_5590_; 
v___x_5590_ = 2139095040;
v___y_5502_ = v___x_5590_;
goto v___jp_5501_;
}
else
{
uint32_t v___x_5591_; 
v___x_5591_ = 4286578688;
v___y_5502_ = v___x_5591_;
goto v___jp_5501_;
}
}
}
v___jp_5592_:
{
uint64_t v___x_5600_; uint8_t v_carry_5601_; 
v___x_5600_ = 16777216ULL;
v_carry_5601_ = lean_uint64_dec_eq(v___y_5599_, v___x_5600_);
if (v_carry_5601_ == 0)
{
v___y_5579_ = v___y_5594_;
v___y_5580_ = v___y_5593_;
v___y_5581_ = v___y_5595_;
v___y_5582_ = v___y_5596_;
v___y_5583_ = v___y_5599_;
v___y_5584_ = v_carry_5601_;
v___y_5585_ = v___y_5598_;
v___y_5586_ = v___y_5597_;
goto v___jp_5578_;
}
else
{
uint64_t v___x_5602_; uint64_t v___x_5603_; 
v___x_5602_ = 1ULL;
v___x_5603_ = lean_uint64_add(v___y_5597_, v___x_5602_);
v___y_5579_ = v___y_5594_;
v___y_5580_ = v___y_5593_;
v___y_5581_ = v___y_5595_;
v___y_5582_ = v___y_5596_;
v___y_5583_ = v___y_5599_;
v___y_5584_ = v_carry_5601_;
v___y_5585_ = v___y_5598_;
v___y_5586_ = v___x_5603_;
goto v___jp_5578_;
}
}
v___jp_5604_:
{
uint64_t v_position_5613_; uint64_t v___x_5614_; uint8_t v___x_5615_; 
v_position_5613_ = lean_uint64_add(v___y_5612_, v___y_5610_);
v___x_5614_ = 172ULL;
v___x_5615_ = lean_uint64_dec_lt(v_position_5613_, v___x_5614_);
if (v___x_5615_ == 0)
{
uint64_t v___x_5616_; uint8_t v___x_5617_; 
v___x_5616_ = 23ULL;
v___x_5617_ = lean_uint64_dec_lt(v___y_5612_, v___x_5616_);
if (v___x_5617_ == 0)
{
uint64_t v___x_5618_; uint8_t v___x_5619_; 
v___x_5618_ = lean_uint64_sub(v___y_5612_, v___x_5616_);
v___x_5619_ = lean_uint64_dec_eq(v___x_5618_, v___y_5606_);
if (v___x_5619_ == 0)
{
uint64_t v___x_5620_; uint8_t v___x_5621_; 
v___x_5620_ = 64ULL;
v___x_5621_ = lean_uint64_dec_lt(v___x_5618_, v___x_5620_);
if (v___x_5621_ == 0)
{
uint8_t v___x_5622_; 
v___x_5622_ = lean_uint64_dec_eq(v___x_5618_, v___x_5620_);
if (v___x_5622_ == 0)
{
v___y_5593_ = v___y_5606_;
v___y_5594_ = v___y_5605_;
v___y_5595_ = v___y_5608_;
v___y_5596_ = v___y_5609_;
v___y_5597_ = v_position_5613_;
v___y_5598_ = v___y_5611_;
v___y_5599_ = v___y_5606_;
goto v___jp_5592_;
}
else
{
uint64_t v___x_5623_; uint8_t v___x_5624_; 
v___x_5623_ = 9223372036854775808ULL;
v___x_5624_ = lean_uint64_dec_lt(v___x_5623_, v___y_5607_);
if (v___x_5624_ == 0)
{
v___y_5593_ = v___y_5606_;
v___y_5594_ = v___y_5605_;
v___y_5595_ = v___y_5608_;
v___y_5596_ = v___y_5609_;
v___y_5597_ = v_position_5613_;
v___y_5598_ = v___y_5611_;
v___y_5599_ = v___y_5606_;
goto v___jp_5592_;
}
else
{
uint64_t v___x_5625_; 
v___x_5625_ = 1ULL;
v___y_5593_ = v___y_5606_;
v___y_5594_ = v___y_5605_;
v___y_5595_ = v___y_5608_;
v___y_5596_ = v___y_5609_;
v___y_5597_ = v_position_5613_;
v___y_5598_ = v___y_5611_;
v___y_5599_ = v___x_5625_;
goto v___jp_5592_;
}
}
}
else
{
uint64_t v_quotient_5626_; uint64_t v___x_5627_; uint64_t v___x_5628_; uint64_t v___x_5629_; uint64_t v_remainder_5630_; uint64_t v___x_5631_; uint64_t v_half_5632_; uint8_t v___x_5633_; 
v_quotient_5626_ = lean_uint64_shift_right(v___y_5607_, v___x_5618_);
v___x_5627_ = 1ULL;
v___x_5628_ = lean_uint64_shift_left(v___x_5627_, v___x_5618_);
v___x_5629_ = lean_uint64_sub(v___x_5628_, v___x_5627_);
v_remainder_5630_ = lean_uint64_land(v___y_5607_, v___x_5629_);
v___x_5631_ = lean_uint64_sub(v___x_5618_, v___x_5627_);
v_half_5632_ = lean_uint64_shift_left(v___x_5627_, v___x_5631_);
v___x_5633_ = lean_uint64_dec_lt(v_remainder_5630_, v_half_5632_);
if (v___x_5633_ == 0)
{
uint8_t v___x_5634_; 
v___x_5634_ = lean_uint64_dec_lt(v_half_5632_, v_remainder_5630_);
if (v___x_5634_ == 0)
{
uint64_t v___x_5635_; uint8_t v___x_5636_; 
v___x_5635_ = lean_uint64_land(v_quotient_5626_, v___x_5627_);
v___x_5636_ = lean_uint64_dec_eq(v___x_5635_, v___y_5606_);
if (v___x_5636_ == 0)
{
uint64_t v___x_5637_; 
v___x_5637_ = lean_uint64_add(v_quotient_5626_, v___x_5627_);
v___y_5593_ = v___y_5606_;
v___y_5594_ = v___y_5605_;
v___y_5595_ = v___y_5608_;
v___y_5596_ = v___y_5609_;
v___y_5597_ = v_position_5613_;
v___y_5598_ = v___y_5611_;
v___y_5599_ = v___x_5637_;
goto v___jp_5592_;
}
else
{
v___y_5593_ = v___y_5606_;
v___y_5594_ = v___y_5605_;
v___y_5595_ = v___y_5608_;
v___y_5596_ = v___y_5609_;
v___y_5597_ = v_position_5613_;
v___y_5598_ = v___y_5611_;
v___y_5599_ = v_quotient_5626_;
goto v___jp_5592_;
}
}
else
{
uint64_t v___x_5638_; 
v___x_5638_ = lean_uint64_add(v_quotient_5626_, v___x_5627_);
v___y_5593_ = v___y_5606_;
v___y_5594_ = v___y_5605_;
v___y_5595_ = v___y_5608_;
v___y_5596_ = v___y_5609_;
v___y_5597_ = v_position_5613_;
v___y_5598_ = v___y_5611_;
v___y_5599_ = v___x_5638_;
goto v___jp_5592_;
}
}
else
{
v___y_5593_ = v___y_5606_;
v___y_5594_ = v___y_5605_;
v___y_5595_ = v___y_5608_;
v___y_5596_ = v___y_5609_;
v___y_5597_ = v_position_5613_;
v___y_5598_ = v___y_5611_;
v___y_5599_ = v_quotient_5626_;
goto v___jp_5592_;
}
}
}
else
{
v___y_5593_ = v___y_5606_;
v___y_5594_ = v___y_5605_;
v___y_5595_ = v___y_5608_;
v___y_5596_ = v___y_5609_;
v___y_5597_ = v_position_5613_;
v___y_5598_ = v___y_5611_;
v___y_5599_ = v___y_5607_;
goto v___jp_5592_;
}
}
else
{
uint64_t v___x_5639_; uint64_t v___x_5640_; 
v___x_5639_ = lean_uint64_sub(v___x_5616_, v___y_5612_);
v___x_5640_ = lean_uint64_shift_left(v___y_5607_, v___x_5639_);
v___y_5593_ = v___y_5606_;
v___y_5594_ = v___y_5605_;
v___y_5595_ = v___y_5608_;
v___y_5596_ = v___y_5609_;
v___y_5597_ = v_position_5613_;
v___y_5598_ = v___y_5611_;
v___y_5599_ = v___x_5640_;
goto v___jp_5592_;
}
}
else
{
uint64_t v___x_5641_; uint8_t v___x_5642_; 
v___x_5641_ = 149ULL;
v___x_5642_ = lean_uint64_dec_lt(v___y_5610_, v___x_5641_);
if (v___x_5642_ == 0)
{
uint64_t v___x_5643_; uint64_t v___x_5644_; 
v___x_5643_ = lean_uint64_sub(v___y_5610_, v___x_5641_);
v___x_5644_ = lean_uint64_shift_left(v___y_5607_, v___x_5643_);
v___y_5527_ = v___y_5605_;
v___y_5528_ = v___y_5606_;
v___y_5529_ = v___y_5609_;
v___y_5530_ = v___x_5644_;
goto v___jp_5526_;
}
else
{
uint64_t v___x_5645_; uint8_t v___x_5646_; 
v___x_5645_ = lean_uint64_sub(v___x_5641_, v___y_5610_);
v___x_5646_ = lean_uint64_dec_eq(v___x_5645_, v___y_5606_);
if (v___x_5646_ == 0)
{
uint64_t v___x_5647_; uint8_t v___x_5648_; 
v___x_5647_ = 64ULL;
v___x_5648_ = lean_uint64_dec_lt(v___x_5645_, v___x_5647_);
if (v___x_5648_ == 0)
{
uint8_t v___x_5649_; 
v___x_5649_ = lean_uint64_dec_eq(v___x_5645_, v___x_5647_);
if (v___x_5649_ == 0)
{
v___y_5527_ = v___y_5605_;
v___y_5528_ = v___y_5606_;
v___y_5529_ = v___y_5609_;
v___y_5530_ = v___y_5606_;
goto v___jp_5526_;
}
else
{
uint64_t v___x_5650_; uint8_t v___x_5651_; 
v___x_5650_ = 9223372036854775808ULL;
v___x_5651_ = lean_uint64_dec_lt(v___x_5650_, v___y_5607_);
if (v___x_5651_ == 0)
{
v___y_5527_ = v___y_5605_;
v___y_5528_ = v___y_5606_;
v___y_5529_ = v___y_5609_;
v___y_5530_ = v___y_5606_;
goto v___jp_5526_;
}
else
{
uint64_t v___x_5652_; 
v___x_5652_ = 1ULL;
v___y_5527_ = v___y_5605_;
v___y_5528_ = v___y_5606_;
v___y_5529_ = v___y_5609_;
v___y_5530_ = v___x_5652_;
goto v___jp_5526_;
}
}
}
else
{
uint64_t v_quotient_5653_; uint64_t v___x_5654_; uint64_t v___x_5655_; uint64_t v___x_5656_; uint64_t v_remainder_5657_; uint64_t v___x_5658_; uint64_t v_half_5659_; uint8_t v___x_5660_; 
v_quotient_5653_ = lean_uint64_shift_right(v___y_5607_, v___x_5645_);
v___x_5654_ = 1ULL;
v___x_5655_ = lean_uint64_shift_left(v___x_5654_, v___x_5645_);
v___x_5656_ = lean_uint64_sub(v___x_5655_, v___x_5654_);
v_remainder_5657_ = lean_uint64_land(v___y_5607_, v___x_5656_);
v___x_5658_ = lean_uint64_sub(v___x_5645_, v___x_5654_);
v_half_5659_ = lean_uint64_shift_left(v___x_5654_, v___x_5658_);
v___x_5660_ = lean_uint64_dec_lt(v_remainder_5657_, v_half_5659_);
if (v___x_5660_ == 0)
{
uint8_t v___x_5661_; 
v___x_5661_ = lean_uint64_dec_lt(v_half_5659_, v_remainder_5657_);
if (v___x_5661_ == 0)
{
uint64_t v___x_5662_; uint8_t v___x_5663_; 
v___x_5662_ = lean_uint64_land(v_quotient_5653_, v___x_5654_);
v___x_5663_ = lean_uint64_dec_eq(v___x_5662_, v___y_5606_);
if (v___x_5663_ == 0)
{
uint64_t v___x_5664_; 
v___x_5664_ = lean_uint64_add(v_quotient_5653_, v___x_5654_);
v___y_5527_ = v___y_5605_;
v___y_5528_ = v___y_5606_;
v___y_5529_ = v___y_5609_;
v___y_5530_ = v___x_5664_;
goto v___jp_5526_;
}
else
{
v___y_5527_ = v___y_5605_;
v___y_5528_ = v___y_5606_;
v___y_5529_ = v___y_5609_;
v___y_5530_ = v_quotient_5653_;
goto v___jp_5526_;
}
}
else
{
uint64_t v___x_5665_; 
v___x_5665_ = lean_uint64_add(v_quotient_5653_, v___x_5654_);
v___y_5527_ = v___y_5605_;
v___y_5528_ = v___y_5606_;
v___y_5529_ = v___y_5609_;
v___y_5530_ = v___x_5665_;
goto v___jp_5526_;
}
}
else
{
v___y_5527_ = v___y_5605_;
v___y_5528_ = v___y_5606_;
v___y_5529_ = v___y_5609_;
v___y_5530_ = v_quotient_5653_;
goto v___jp_5526_;
}
}
}
else
{
v___y_5527_ = v___y_5605_;
v___y_5528_ = v___y_5606_;
v___y_5529_ = v___y_5609_;
v___y_5530_ = v___y_5607_;
goto v___jp_5526_;
}
}
}
}
v___jp_5666_:
{
uint64_t v___x_5676_; uint64_t v___x_5677_; uint8_t v___x_5678_; 
v___x_5676_ = 1ULL;
v___x_5677_ = lean_uint64_shift_right(v___y_5673_, v___x_5676_);
v___x_5678_ = lean_uint64_dec_eq(v___x_5677_, v___y_5668_);
if (v___x_5678_ == 0)
{
uint64_t v___x_5679_; 
v___x_5679_ = lean_uint64_add(v___y_5675_, v___x_5676_);
v___y_5605_ = v___y_5667_;
v___y_5606_ = v___y_5668_;
v___y_5607_ = v___y_5669_;
v___y_5608_ = v___y_5670_;
v___y_5609_ = v___y_5672_;
v___y_5610_ = v___y_5671_;
v___y_5611_ = v___y_5674_;
v___y_5612_ = v___x_5679_;
goto v___jp_5604_;
}
else
{
v___y_5605_ = v___y_5667_;
v___y_5606_ = v___y_5668_;
v___y_5607_ = v___y_5669_;
v___y_5608_ = v___y_5670_;
v___y_5609_ = v___y_5672_;
v___y_5610_ = v___y_5671_;
v___y_5611_ = v___y_5674_;
v___y_5612_ = v___y_5675_;
goto v___jp_5604_;
}
}
v___jp_5680_:
{
uint64_t v___x_5692_; uint8_t v___x_5693_; 
v___x_5692_ = lean_uint64_shift_right(v___y_5684_, v___y_5683_);
v___x_5693_ = lean_uint64_dec_eq(v___x_5692_, v___y_5681_);
if (v___x_5693_ == 0)
{
uint64_t v___x_5694_; 
v___x_5694_ = lean_uint64_add(v___y_5687_, v___y_5683_);
v___y_5667_ = v___y_5682_;
v___y_5668_ = v___y_5681_;
v___y_5669_ = v___y_5685_;
v___y_5670_ = v___y_5686_;
v___y_5671_ = v___y_5689_;
v___y_5672_ = v___y_5688_;
v___y_5673_ = v___y_5691_;
v___y_5674_ = v___y_5690_;
v___y_5675_ = v___x_5694_;
goto v___jp_5666_;
}
else
{
v___y_5667_ = v___y_5682_;
v___y_5668_ = v___y_5681_;
v___y_5669_ = v___y_5685_;
v___y_5670_ = v___y_5686_;
v___y_5671_ = v___y_5689_;
v___y_5672_ = v___y_5688_;
v___y_5673_ = v___y_5691_;
v___y_5674_ = v___y_5690_;
v___y_5675_ = v___y_5687_;
goto v___jp_5666_;
}
}
v___jp_5695_:
{
uint64_t v___x_5705_; uint64_t v___x_5706_; uint8_t v___x_5707_; 
v___x_5705_ = 2ULL;
v___x_5706_ = lean_uint64_shift_right(v___y_5699_, v___x_5705_);
v___x_5707_ = lean_uint64_dec_eq(v___x_5706_, v___y_5697_);
if (v___x_5707_ == 0)
{
v___y_5681_ = v___y_5697_;
v___y_5682_ = v___y_5696_;
v___y_5683_ = v___x_5705_;
v___y_5684_ = v___y_5699_;
v___y_5685_ = v___y_5698_;
v___y_5686_ = v___y_5700_;
v___y_5687_ = v___y_5704_;
v___y_5688_ = v___y_5702_;
v___y_5689_ = v___y_5701_;
v___y_5690_ = v___y_5703_;
v___y_5691_ = v___x_5706_;
goto v___jp_5680_;
}
else
{
v___y_5681_ = v___y_5697_;
v___y_5682_ = v___y_5696_;
v___y_5683_ = v___x_5705_;
v___y_5684_ = v___y_5699_;
v___y_5685_ = v___y_5698_;
v___y_5686_ = v___y_5700_;
v___y_5687_ = v___y_5704_;
v___y_5688_ = v___y_5702_;
v___y_5689_ = v___y_5701_;
v___y_5690_ = v___y_5703_;
v___y_5691_ = v___y_5699_;
goto v___jp_5680_;
}
}
v___jp_5708_:
{
uint64_t v___x_5720_; uint8_t v___x_5721_; 
v___x_5720_ = lean_uint64_shift_right(v___y_5713_, v___y_5716_);
v___x_5721_ = lean_uint64_dec_eq(v___x_5720_, v___y_5709_);
if (v___x_5721_ == 0)
{
uint64_t v___x_5722_; 
v___x_5722_ = lean_uint64_add(v___y_5717_, v___y_5716_);
v___y_5696_ = v___y_5710_;
v___y_5697_ = v___y_5709_;
v___y_5698_ = v___y_5711_;
v___y_5699_ = v___y_5719_;
v___y_5700_ = v___y_5712_;
v___y_5701_ = v___y_5715_;
v___y_5702_ = v___y_5714_;
v___y_5703_ = v___y_5718_;
v___y_5704_ = v___x_5722_;
goto v___jp_5695_;
}
else
{
v___y_5696_ = v___y_5710_;
v___y_5697_ = v___y_5709_;
v___y_5698_ = v___y_5711_;
v___y_5699_ = v___y_5719_;
v___y_5700_ = v___y_5712_;
v___y_5701_ = v___y_5715_;
v___y_5702_ = v___y_5714_;
v___y_5703_ = v___y_5718_;
v___y_5704_ = v___y_5717_;
goto v___jp_5695_;
}
}
v___jp_5723_:
{
uint64_t v___x_5733_; uint64_t v___x_5734_; uint8_t v___x_5735_; 
v___x_5733_ = 4ULL;
v___x_5734_ = lean_uint64_shift_right(v___y_5728_, v___x_5733_);
v___x_5735_ = lean_uint64_dec_eq(v___x_5734_, v___y_5725_);
if (v___x_5735_ == 0)
{
v___y_5709_ = v___y_5725_;
v___y_5710_ = v___y_5724_;
v___y_5711_ = v___y_5726_;
v___y_5712_ = v___y_5727_;
v___y_5713_ = v___y_5728_;
v___y_5714_ = v___y_5730_;
v___y_5715_ = v___y_5729_;
v___y_5716_ = v___x_5733_;
v___y_5717_ = v___y_5732_;
v___y_5718_ = v___y_5731_;
v___y_5719_ = v___x_5734_;
goto v___jp_5708_;
}
else
{
v___y_5709_ = v___y_5725_;
v___y_5710_ = v___y_5724_;
v___y_5711_ = v___y_5726_;
v___y_5712_ = v___y_5727_;
v___y_5713_ = v___y_5728_;
v___y_5714_ = v___y_5730_;
v___y_5715_ = v___y_5729_;
v___y_5716_ = v___x_5733_;
v___y_5717_ = v___y_5732_;
v___y_5718_ = v___y_5731_;
v___y_5719_ = v___y_5728_;
goto v___jp_5708_;
}
}
v___jp_5736_:
{
uint64_t v___x_5748_; uint8_t v___x_5749_; 
v___x_5748_ = lean_uint64_shift_right(v___y_5744_, v___y_5743_);
v___x_5749_ = lean_uint64_dec_eq(v___x_5748_, v___y_5737_);
if (v___x_5749_ == 0)
{
uint64_t v___x_5750_; 
v___x_5750_ = lean_uint64_add(v___y_5745_, v___y_5743_);
v___y_5724_ = v___y_5738_;
v___y_5725_ = v___y_5737_;
v___y_5726_ = v___y_5739_;
v___y_5727_ = v___y_5740_;
v___y_5728_ = v___y_5747_;
v___y_5729_ = v___y_5742_;
v___y_5730_ = v___y_5741_;
v___y_5731_ = v___y_5746_;
v___y_5732_ = v___x_5750_;
goto v___jp_5723_;
}
else
{
v___y_5724_ = v___y_5738_;
v___y_5725_ = v___y_5737_;
v___y_5726_ = v___y_5739_;
v___y_5727_ = v___y_5740_;
v___y_5728_ = v___y_5747_;
v___y_5729_ = v___y_5742_;
v___y_5730_ = v___y_5741_;
v___y_5731_ = v___y_5746_;
v___y_5732_ = v___y_5745_;
goto v___jp_5723_;
}
}
v___jp_5751_:
{
uint64_t v___x_5761_; uint64_t v___x_5762_; uint8_t v___x_5763_; 
v___x_5761_ = 8ULL;
v___x_5762_ = lean_uint64_shift_right(v___y_5758_, v___x_5761_);
v___x_5763_ = lean_uint64_dec_eq(v___x_5762_, v___y_5753_);
if (v___x_5763_ == 0)
{
v___y_5737_ = v___y_5753_;
v___y_5738_ = v___y_5752_;
v___y_5739_ = v___y_5754_;
v___y_5740_ = v___y_5755_;
v___y_5741_ = v___y_5757_;
v___y_5742_ = v___y_5756_;
v___y_5743_ = v___x_5761_;
v___y_5744_ = v___y_5758_;
v___y_5745_ = v___y_5760_;
v___y_5746_ = v___y_5759_;
v___y_5747_ = v___x_5762_;
goto v___jp_5736_;
}
else
{
v___y_5737_ = v___y_5753_;
v___y_5738_ = v___y_5752_;
v___y_5739_ = v___y_5754_;
v___y_5740_ = v___y_5755_;
v___y_5741_ = v___y_5757_;
v___y_5742_ = v___y_5756_;
v___y_5743_ = v___x_5761_;
v___y_5744_ = v___y_5758_;
v___y_5745_ = v___y_5760_;
v___y_5746_ = v___y_5759_;
v___y_5747_ = v___y_5758_;
goto v___jp_5736_;
}
}
v___jp_5764_:
{
uint64_t v___x_5776_; uint8_t v___x_5777_; 
v___x_5776_ = lean_uint64_shift_right(v___y_5769_, v___y_5765_);
v___x_5777_ = lean_uint64_dec_eq(v___x_5776_, v___y_5766_);
if (v___x_5777_ == 0)
{
uint64_t v___x_5778_; 
v___x_5778_ = lean_uint64_add(v___y_5773_, v___y_5765_);
v___y_5752_ = v___y_5767_;
v___y_5753_ = v___y_5766_;
v___y_5754_ = v___y_5768_;
v___y_5755_ = v___y_5770_;
v___y_5756_ = v___y_5772_;
v___y_5757_ = v___y_5771_;
v___y_5758_ = v___y_5775_;
v___y_5759_ = v___y_5774_;
v___y_5760_ = v___x_5778_;
goto v___jp_5751_;
}
else
{
v___y_5752_ = v___y_5767_;
v___y_5753_ = v___y_5766_;
v___y_5754_ = v___y_5768_;
v___y_5755_ = v___y_5770_;
v___y_5756_ = v___y_5772_;
v___y_5757_ = v___y_5771_;
v___y_5758_ = v___y_5775_;
v___y_5759_ = v___y_5774_;
v___y_5760_ = v___y_5773_;
goto v___jp_5751_;
}
}
v___jp_5779_:
{
uint64_t v___x_5789_; uint64_t v___x_5790_; uint8_t v___x_5791_; 
v___x_5789_ = 16ULL;
v___x_5790_ = lean_uint64_shift_right(v___y_5783_, v___x_5789_);
v___x_5791_ = lean_uint64_dec_eq(v___x_5790_, v___y_5781_);
if (v___x_5791_ == 0)
{
v___y_5765_ = v___x_5789_;
v___y_5766_ = v___y_5781_;
v___y_5767_ = v___y_5780_;
v___y_5768_ = v___y_5782_;
v___y_5769_ = v___y_5783_;
v___y_5770_ = v___y_5784_;
v___y_5771_ = v___y_5786_;
v___y_5772_ = v___y_5785_;
v___y_5773_ = v___y_5788_;
v___y_5774_ = v___y_5787_;
v___y_5775_ = v___x_5790_;
goto v___jp_5764_;
}
else
{
v___y_5765_ = v___x_5789_;
v___y_5766_ = v___y_5781_;
v___y_5767_ = v___y_5780_;
v___y_5768_ = v___y_5782_;
v___y_5769_ = v___y_5783_;
v___y_5770_ = v___y_5784_;
v___y_5771_ = v___y_5786_;
v___y_5772_ = v___y_5785_;
v___y_5773_ = v___y_5788_;
v___y_5774_ = v___y_5787_;
v___y_5775_ = v___y_5783_;
goto v___jp_5764_;
}
}
v___jp_5792_:
{
uint64_t v___x_5802_; uint8_t v___x_5803_; 
v___x_5802_ = lean_uint64_shift_right(v___y_5795_, v___y_5796_);
v___x_5803_ = lean_uint64_dec_eq(v___x_5802_, v___y_5793_);
if (v___x_5803_ == 0)
{
v___y_5780_ = v___y_5794_;
v___y_5781_ = v___y_5793_;
v___y_5782_ = v___y_5795_;
v___y_5783_ = v___y_5801_;
v___y_5784_ = v___y_5797_;
v___y_5785_ = v___y_5799_;
v___y_5786_ = v___y_5798_;
v___y_5787_ = v___y_5800_;
v___y_5788_ = v___y_5796_;
goto v___jp_5779_;
}
else
{
v___y_5780_ = v___y_5794_;
v___y_5781_ = v___y_5793_;
v___y_5782_ = v___y_5795_;
v___y_5783_ = v___y_5801_;
v___y_5784_ = v___y_5797_;
v___y_5785_ = v___y_5799_;
v___y_5786_ = v___y_5798_;
v___y_5787_ = v___y_5800_;
v___y_5788_ = v___y_5793_;
goto v___jp_5779_;
}
}
v___jp_5804_:
{
uint64_t v___x_5811_; uint8_t v___x_5812_; 
v___x_5811_ = 0ULL;
v___x_5812_ = lean_uint64_dec_eq(v___y_5806_, v___x_5811_);
if (v___x_5812_ == 0)
{
uint64_t v___x_5813_; uint64_t v___x_5814_; uint8_t v___x_5815_; 
v___x_5813_ = 32ULL;
v___x_5814_ = lean_uint64_shift_right(v___y_5806_, v___x_5813_);
v___x_5815_ = lean_uint64_dec_eq(v___x_5814_, v___x_5811_);
if (v___x_5815_ == 0)
{
v___y_5793_ = v___x_5811_;
v___y_5794_ = v___y_5805_;
v___y_5795_ = v___y_5806_;
v___y_5796_ = v___x_5813_;
v___y_5797_ = v___y_5807_;
v___y_5798_ = v___y_5809_;
v___y_5799_ = v___y_5808_;
v___y_5800_ = v___y_5810_;
v___y_5801_ = v___x_5814_;
goto v___jp_5792_;
}
else
{
v___y_5793_ = v___x_5811_;
v___y_5794_ = v___y_5805_;
v___y_5795_ = v___y_5806_;
v___y_5796_ = v___x_5813_;
v___y_5797_ = v___y_5807_;
v___y_5798_ = v___y_5809_;
v___y_5799_ = v___y_5808_;
v___y_5800_ = v___y_5810_;
v___y_5801_ = v___y_5806_;
goto v___jp_5792_;
}
}
else
{
if (v___y_5805_ == 0)
{
uint32_t v___x_5816_; 
v___x_5816_ = 0;
v___y_5502_ = v___x_5816_;
goto v___jp_5501_;
}
else
{
uint32_t v___x_5817_; 
v___x_5817_ = 2147483648;
v___y_5502_ = v___x_5817_;
goto v___jp_5501_;
}
}
}
v___jp_5818_:
{
uint32_t v___x_5822_; uint32_t v___x_5823_; 
v___x_5822_ = lean_uint32_land(v___y_5820_, v___y_5819_);
v___x_5823_ = lean_uint32_lor(v___y_5821_, v___x_5822_);
v___y_5502_ = v___x_5823_;
goto v___jp_5501_;
}
v___jp_5824_:
{
uint8_t v___x_5829_; 
v___x_5829_ = lean_uint64_dec_eq(v___y_5828_, v___y_5827_);
if (v___x_5829_ == 0)
{
uint64_t v___x_5830_; uint8_t v___x_5831_; 
v___x_5830_ = 8388608ULL;
v___x_5831_ = lean_uint64_dec_eq(v___y_5828_, v___x_5830_);
if (v___x_5831_ == 0)
{
uint32_t v___x_5832_; 
v___x_5832_ = lean_uint64_to_uint32(v___y_5828_);
if (v___y_5825_ == 0)
{
uint32_t v___x_5833_; 
v___x_5833_ = 0;
v___y_5819_ = v___y_5826_;
v___y_5820_ = v___x_5832_;
v___y_5821_ = v___x_5833_;
goto v___jp_5818_;
}
else
{
uint32_t v___x_5834_; 
v___x_5834_ = 2147483648;
v___y_5819_ = v___y_5826_;
v___y_5820_ = v___x_5832_;
v___y_5821_ = v___x_5834_;
goto v___jp_5818_;
}
}
else
{
if (v___y_5825_ == 0)
{
uint32_t v___x_5835_; 
v___x_5835_ = 0;
v___y_5517_ = v___x_5835_;
goto v___jp_5516_;
}
else
{
uint32_t v___x_5836_; 
v___x_5836_ = 2147483648;
v___y_5517_ = v___x_5836_;
goto v___jp_5516_;
}
}
}
else
{
if (v___y_5825_ == 0)
{
uint32_t v___x_5837_; 
v___x_5837_ = 0;
v___y_5502_ = v___x_5837_;
goto v___jp_5501_;
}
else
{
uint32_t v___x_5838_; 
v___x_5838_ = 2147483648;
v___y_5502_ = v___x_5838_;
goto v___jp_5501_;
}
}
}
v___jp_5839_:
{
uint64_t v___x_5848_; uint64_t v___x_5849_; uint64_t v___x_5850_; uint8_t v___x_5851_; 
v___x_5848_ = lean_uint64_mul(v___y_5846_, v___y_5841_);
v___x_5849_ = lean_uint64_add(v___y_5843_, v___y_5847_);
v___x_5850_ = 281474976710656ULL;
v___x_5851_ = lean_uint64_dec_lt(v___x_5848_, v___x_5850_);
if (v___x_5851_ == 0)
{
v___y_5805_ = v___y_5840_;
v___y_5806_ = v___x_5848_;
v___y_5807_ = v___y_5842_;
v___y_5808_ = v___x_5849_;
v___y_5809_ = v___y_5844_;
v___y_5810_ = v___y_5845_;
goto v___jp_5804_;
}
else
{
uint64_t v___x_5852_; uint8_t v___x_5853_; 
v___x_5852_ = 123ULL;
v___x_5853_ = lean_uint64_dec_le(v___x_5849_, v___x_5852_);
if (v___x_5853_ == 0)
{
v___y_5805_ = v___y_5840_;
v___y_5806_ = v___x_5848_;
v___y_5807_ = v___y_5842_;
v___y_5808_ = v___x_5849_;
v___y_5809_ = v___y_5844_;
v___y_5810_ = v___y_5845_;
goto v___jp_5804_;
}
else
{
uint64_t v___x_5854_; uint8_t v___x_5855_; 
v___x_5854_ = 0ULL;
v___x_5855_ = lean_uint64_dec_eq(v___x_5848_, v___x_5854_);
if (v___x_5855_ == 0)
{
uint64_t v___x_5856_; uint64_t v___x_5857_; uint8_t v___x_5858_; 
v___x_5856_ = 149ULL;
v___x_5857_ = lean_uint64_sub(v___x_5856_, v___x_5849_);
v___x_5858_ = lean_uint64_dec_eq(v___x_5857_, v___x_5854_);
if (v___x_5858_ == 0)
{
uint64_t v___x_5859_; uint8_t v___x_5860_; 
v___x_5859_ = 64ULL;
v___x_5860_ = lean_uint64_dec_lt(v___x_5857_, v___x_5859_);
if (v___x_5860_ == 0)
{
uint8_t v___x_5861_; 
v___x_5861_ = lean_uint64_dec_eq(v___x_5857_, v___x_5859_);
if (v___x_5861_ == 0)
{
v___y_5825_ = v___y_5840_;
v___y_5826_ = v___y_5844_;
v___y_5827_ = v___x_5854_;
v___y_5828_ = v___x_5854_;
goto v___jp_5824_;
}
else
{
uint64_t v___x_5862_; uint8_t v___x_5863_; 
v___x_5862_ = 9223372036854775808ULL;
v___x_5863_ = lean_uint64_dec_lt(v___x_5862_, v___x_5848_);
if (v___x_5863_ == 0)
{
v___y_5825_ = v___y_5840_;
v___y_5826_ = v___y_5844_;
v___y_5827_ = v___x_5854_;
v___y_5828_ = v___x_5854_;
goto v___jp_5824_;
}
else
{
uint64_t v___x_5864_; 
v___x_5864_ = 1ULL;
v___y_5825_ = v___y_5840_;
v___y_5826_ = v___y_5844_;
v___y_5827_ = v___x_5854_;
v___y_5828_ = v___x_5864_;
goto v___jp_5824_;
}
}
}
else
{
uint64_t v_quotient_5865_; uint64_t v___x_5866_; uint64_t v___x_5867_; uint64_t v___x_5868_; uint64_t v_remainder_5869_; uint64_t v___x_5870_; uint64_t v_half_5871_; uint8_t v___x_5872_; 
v_quotient_5865_ = lean_uint64_shift_right(v___x_5848_, v___x_5857_);
v___x_5866_ = 1ULL;
v___x_5867_ = lean_uint64_shift_left(v___x_5866_, v___x_5857_);
v___x_5868_ = lean_uint64_sub(v___x_5867_, v___x_5866_);
v_remainder_5869_ = lean_uint64_land(v___x_5848_, v___x_5868_);
v___x_5870_ = lean_uint64_sub(v___x_5857_, v___x_5866_);
v_half_5871_ = lean_uint64_shift_left(v___x_5866_, v___x_5870_);
v___x_5872_ = lean_uint64_dec_lt(v_remainder_5869_, v_half_5871_);
if (v___x_5872_ == 0)
{
uint8_t v___x_5873_; 
v___x_5873_ = lean_uint64_dec_lt(v_half_5871_, v_remainder_5869_);
if (v___x_5873_ == 0)
{
uint64_t v___x_5874_; uint8_t v___x_5875_; 
v___x_5874_ = lean_uint64_land(v_quotient_5865_, v___x_5866_);
v___x_5875_ = lean_uint64_dec_eq(v___x_5874_, v___x_5854_);
if (v___x_5875_ == 0)
{
uint64_t v___x_5876_; 
v___x_5876_ = lean_uint64_add(v_quotient_5865_, v___x_5866_);
v___y_5825_ = v___y_5840_;
v___y_5826_ = v___y_5844_;
v___y_5827_ = v___x_5854_;
v___y_5828_ = v___x_5876_;
goto v___jp_5824_;
}
else
{
v___y_5825_ = v___y_5840_;
v___y_5826_ = v___y_5844_;
v___y_5827_ = v___x_5854_;
v___y_5828_ = v_quotient_5865_;
goto v___jp_5824_;
}
}
else
{
uint64_t v___x_5877_; 
v___x_5877_ = lean_uint64_add(v_quotient_5865_, v___x_5866_);
v___y_5825_ = v___y_5840_;
v___y_5826_ = v___y_5844_;
v___y_5827_ = v___x_5854_;
v___y_5828_ = v___x_5877_;
goto v___jp_5824_;
}
}
else
{
v___y_5825_ = v___y_5840_;
v___y_5826_ = v___y_5844_;
v___y_5827_ = v___x_5854_;
v___y_5828_ = v_quotient_5865_;
goto v___jp_5824_;
}
}
}
else
{
v___y_5825_ = v___y_5840_;
v___y_5826_ = v___y_5844_;
v___y_5827_ = v___x_5854_;
v___y_5828_ = v___x_5848_;
goto v___jp_5824_;
}
}
else
{
if (v___y_5840_ == 0)
{
uint32_t v___x_5878_; 
v___x_5878_ = 0;
v___y_5502_ = v___x_5878_;
goto v___jp_5501_;
}
else
{
uint32_t v___x_5879_; 
v___x_5879_ = 2147483648;
v___y_5502_ = v___x_5879_;
goto v___jp_5501_;
}
}
}
}
}
v___jp_5880_:
{
uint64_t v___x_5889_; uint64_t v___x_5890_; uint8_t v___x_5891_; 
v___x_5889_ = lean_uint32_to_uint64(v___y_5885_);
v___x_5890_ = 0ULL;
v___x_5891_ = lean_uint64_dec_eq(v___x_5889_, v___x_5890_);
if (v___x_5891_ == 0)
{
uint64_t v___x_5892_; uint64_t v___x_5893_; 
v___x_5892_ = 1ULL;
v___x_5893_ = lean_uint64_sub(v___x_5889_, v___x_5892_);
v___y_5840_ = v___y_5881_;
v___y_5841_ = v___y_5882_;
v___y_5842_ = v___y_5883_;
v___y_5843_ = v___y_5888_;
v___y_5844_ = v___y_5884_;
v___y_5845_ = v___y_5886_;
v___y_5846_ = v___y_5887_;
v___y_5847_ = v___x_5893_;
goto v___jp_5839_;
}
else
{
v___y_5840_ = v___y_5881_;
v___y_5841_ = v___y_5882_;
v___y_5842_ = v___y_5883_;
v___y_5843_ = v___y_5888_;
v___y_5844_ = v___y_5884_;
v___y_5845_ = v___y_5886_;
v___y_5846_ = v___y_5887_;
v___y_5847_ = v___x_5890_;
goto v___jp_5839_;
}
}
v___jp_5894_:
{
uint64_t v___x_5903_; uint64_t v___x_5904_; uint8_t v___x_5905_; 
v___x_5903_ = lean_uint32_to_uint64(v___y_5900_);
v___x_5904_ = 0ULL;
v___x_5905_ = lean_uint64_dec_eq(v___x_5903_, v___x_5904_);
if (v___x_5905_ == 0)
{
uint64_t v___x_5906_; uint64_t v___x_5907_; 
v___x_5906_ = 1ULL;
v___x_5907_ = lean_uint64_sub(v___x_5903_, v___x_5906_);
v___y_5881_ = v___y_5895_;
v___y_5882_ = v___y_5902_;
v___y_5883_ = v___y_5896_;
v___y_5884_ = v___y_5897_;
v___y_5885_ = v___y_5898_;
v___y_5886_ = v___y_5899_;
v___y_5887_ = v___y_5901_;
v___y_5888_ = v___x_5907_;
goto v___jp_5880_;
}
else
{
v___y_5881_ = v___y_5895_;
v___y_5882_ = v___y_5902_;
v___y_5883_ = v___y_5896_;
v___y_5884_ = v___y_5897_;
v___y_5885_ = v___y_5898_;
v___y_5886_ = v___y_5899_;
v___y_5887_ = v___y_5901_;
v___y_5888_ = v___x_5904_;
goto v___jp_5880_;
}
}
v___jp_5908_:
{
uint32_t v___x_5917_; uint8_t v___x_5918_; 
v___x_5917_ = 0;
v___x_5918_ = lean_uint32_dec_eq(v___y_5913_, v___x_5917_);
if (v___x_5918_ == 0)
{
uint64_t v___x_5919_; uint64_t v___x_5920_; uint64_t v___x_5921_; 
v___x_5919_ = lean_uint32_to_uint64(v___y_5912_);
v___x_5920_ = 8388608ULL;
v___x_5921_ = lean_uint64_lor(v___x_5919_, v___x_5920_);
v___y_5895_ = v___y_5909_;
v___y_5896_ = v___y_5910_;
v___y_5897_ = v___y_5911_;
v___y_5898_ = v___y_5913_;
v___y_5899_ = v___y_5914_;
v___y_5900_ = v___y_5915_;
v___y_5901_ = v___y_5916_;
v___y_5902_ = v___x_5921_;
goto v___jp_5894_;
}
else
{
uint64_t v___x_5922_; 
v___x_5922_ = lean_uint32_to_uint64(v___y_5912_);
v___y_5895_ = v___y_5909_;
v___y_5896_ = v___y_5910_;
v___y_5897_ = v___y_5911_;
v___y_5898_ = v___y_5913_;
v___y_5899_ = v___y_5914_;
v___y_5900_ = v___y_5915_;
v___y_5901_ = v___y_5916_;
v___y_5902_ = v___x_5922_;
goto v___jp_5894_;
}
}
v___jp_5923_:
{
uint32_t v___x_5931_; uint32_t v_xFraction_5932_; uint32_t v_yFraction_5933_; uint32_t v___x_5934_; uint8_t v___x_5935_; 
v___x_5931_ = 8388607;
v_xFraction_5932_ = lean_uint32_land(v___y_5924_, v___x_5931_);
v_yFraction_5933_ = lean_uint32_land(v___y_5928_, v___x_5931_);
v___x_5934_ = 0;
v___x_5935_ = lean_uint32_dec_eq(v___y_5929_, v___x_5934_);
if (v___x_5935_ == 0)
{
uint64_t v___x_5936_; uint64_t v___x_5937_; uint64_t v___x_5938_; 
v___x_5936_ = lean_uint32_to_uint64(v_xFraction_5932_);
v___x_5937_ = 8388608ULL;
v___x_5938_ = lean_uint64_lor(v___x_5936_, v___x_5937_);
v___y_5909_ = v___y_5930_;
v___y_5910_ = v___y_5925_;
v___y_5911_ = v___x_5931_;
v___y_5912_ = v_yFraction_5933_;
v___y_5913_ = v___y_5926_;
v___y_5914_ = v___y_5927_;
v___y_5915_ = v___y_5929_;
v___y_5916_ = v___x_5938_;
goto v___jp_5908_;
}
else
{
uint64_t v___x_5939_; 
v___x_5939_ = lean_uint32_to_uint64(v_xFraction_5932_);
v___y_5909_ = v___y_5930_;
v___y_5910_ = v___y_5925_;
v___y_5911_ = v___x_5931_;
v___y_5912_ = v_yFraction_5933_;
v___y_5913_ = v___y_5926_;
v___y_5914_ = v___y_5927_;
v___y_5915_ = v___y_5929_;
v___y_5916_ = v___x_5939_;
goto v___jp_5908_;
}
}
v___jp_5940_:
{
float v___x_5943_; float v___x_5944_; float v___x_5945_; uint32_t v___x_5946_; 
v___x_5943_ = lean_float32_of_bits(v___y_5941_);
v___x_5944_ = lean_float32_of_bits(v___y_5942_);
v___x_5945_ = lean_float32_mul(v___x_5943_, v___x_5944_);
v___x_5946_ = lean_float32_to_bits(v___x_5945_);
v___y_5502_ = v___x_5946_;
goto v___jp_5501_;
}
v___jp_5947_:
{
if (v___y_5953_ == 0)
{
uint32_t v___x_5954_; 
v___x_5954_ = lp_competition_Submission_FastMul_mul(v___y_5948_, v___y_5952_);
v___y_5502_ = v___x_5954_;
goto v___jp_5501_;
}
else
{
uint8_t v___x_5955_; 
v___x_5955_ = lean_uint32_dec_eq(v___y_5950_, v___y_5951_);
if (v___x_5955_ == 0)
{
v___y_5941_ = v___y_5948_;
v___y_5942_ = v___y_5952_;
goto v___jp_5940_;
}
else
{
if (v___y_5949_ == 0)
{
uint32_t v___x_5956_; 
v___x_5956_ = lp_competition_Submission_FastMul_mul(v___y_5948_, v___y_5952_);
v___y_5502_ = v___x_5956_;
goto v___jp_5501_;
}
else
{
v___y_5941_ = v___y_5948_;
v___y_5942_ = v___y_5952_;
goto v___jp_5940_;
}
}
}
}
v___jp_5957_:
{
if (v___y_5965_ == 0)
{
v___y_5924_ = v___y_5958_;
v___y_5925_ = v___y_5960_;
v___y_5926_ = v___y_5961_;
v___y_5927_ = v___y_5962_;
v___y_5928_ = v___y_5963_;
v___y_5929_ = v___y_5964_;
v___y_5930_ = v___x_5458_;
goto v___jp_5923_;
}
else
{
v___y_5924_ = v___y_5958_;
v___y_5925_ = v___y_5960_;
v___y_5926_ = v___y_5961_;
v___y_5927_ = v___y_5962_;
v___y_5928_ = v___y_5963_;
v___y_5929_ = v___y_5964_;
v___y_5930_ = v___y_5959_;
goto v___jp_5923_;
}
}
v___jp_5966_:
{
if (v___y_5968_ == 0)
{
if (v___y_5975_ == 0)
{
v___y_5958_ = v___y_5967_;
v___y_5959_ = v___y_5969_;
v___y_5960_ = v___y_5970_;
v___y_5961_ = v___y_5971_;
v___y_5962_ = v___y_5972_;
v___y_5963_ = v___y_5973_;
v___y_5964_ = v___y_5974_;
v___y_5965_ = v___x_5458_;
goto v___jp_5957_;
}
else
{
v___y_5924_ = v___y_5967_;
v___y_5925_ = v___y_5970_;
v___y_5926_ = v___y_5971_;
v___y_5927_ = v___y_5972_;
v___y_5928_ = v___y_5973_;
v___y_5929_ = v___y_5974_;
v___y_5930_ = v___x_5458_;
goto v___jp_5923_;
}
}
else
{
v___y_5958_ = v___y_5967_;
v___y_5959_ = v___y_5969_;
v___y_5960_ = v___y_5970_;
v___y_5961_ = v___y_5971_;
v___y_5962_ = v___y_5972_;
v___y_5963_ = v___y_5973_;
v___y_5964_ = v___y_5974_;
v___y_5965_ = v___y_5975_;
goto v___jp_5957_;
}
}
v___jp_5976_:
{
uint32_t v___x_5985_; uint32_t v___x_5986_; uint32_t v___x_5987_; uint8_t v___x_5988_; 
v___x_5985_ = 2147483648;
v___x_5986_ = lean_uint32_land(v___y_5982_, v___x_5985_);
v___x_5987_ = 0;
v___x_5988_ = lean_uint32_dec_eq(v___x_5986_, v___x_5987_);
if (v___x_5988_ == 0)
{
v___y_5967_ = v___y_5977_;
v___y_5968_ = v___y_5984_;
v___y_5969_ = v___y_5978_;
v___y_5970_ = v___y_5979_;
v___y_5971_ = v___y_5980_;
v___y_5972_ = v___y_5981_;
v___y_5973_ = v___y_5982_;
v___y_5974_ = v___y_5983_;
v___y_5975_ = v___x_5458_;
goto v___jp_5966_;
}
else
{
v___y_5967_ = v___y_5977_;
v___y_5968_ = v___y_5984_;
v___y_5969_ = v___y_5978_;
v___y_5970_ = v___y_5979_;
v___y_5971_ = v___y_5980_;
v___y_5972_ = v___y_5981_;
v___y_5973_ = v___y_5982_;
v___y_5974_ = v___y_5983_;
v___y_5975_ = v___y_5978_;
goto v___jp_5966_;
}
}
v___jp_5989_:
{
if (v___y_5996_ == 0)
{
uint32_t v___x_5997_; uint32_t v___x_5998_; uint32_t v___x_5999_; uint8_t v___x_6000_; 
v___x_5997_ = 2147483648;
v___x_5998_ = lean_uint32_land(v___y_5990_, v___x_5997_);
v___x_5999_ = 0;
v___x_6000_ = lean_uint32_dec_eq(v___x_5998_, v___x_5999_);
if (v___x_6000_ == 0)
{
v___y_5977_ = v___y_5990_;
v___y_5978_ = v___y_5996_;
v___y_5979_ = v___y_5991_;
v___y_5980_ = v___y_5992_;
v___y_5981_ = v___y_5993_;
v___y_5982_ = v___y_5994_;
v___y_5983_ = v___y_5995_;
v___y_5984_ = v___x_5458_;
goto v___jp_5976_;
}
else
{
v___y_5977_ = v___y_5990_;
v___y_5978_ = v___y_5996_;
v___y_5979_ = v___y_5991_;
v___y_5980_ = v___y_5992_;
v___y_5981_ = v___y_5993_;
v___y_5982_ = v___y_5994_;
v___y_5983_ = v___y_5995_;
v___y_5984_ = v___y_5996_;
goto v___jp_5976_;
}
}
else
{
lean_object* v___x_6001_; lean_object* v___x_6002_; lean_object* v___x_6003_; uint32_t v___x_6004_; 
v___x_6001_ = lean_uint32_to_nat(v___y_5990_);
v___x_6002_ = lean_uint32_to_nat(v___y_5994_);
v___x_6003_ = lp_floatlib_FloatLib_Floats_Formats_BinaryInterchange_Model_MulBackend_word___at___00FloatLib_Floats_Formats_BinaryInterchange_Configured_Plan_softwareMul32Certified_spec__1(v___x_6001_, v___x_6002_);
v___x_6004_ = lean_uint32_of_nat(v___x_6003_);
lean_dec(v___x_6003_);
v___y_5502_ = v___x_6004_;
goto v___jp_5501_;
}
}
v___jp_6005_:
{
uint32_t v___x_6008_; uint32_t v___x_6009_; uint32_t v___x_6010_; uint32_t v_ex_6011_; uint32_t v___x_6012_; uint32_t v_ey_6013_; uint32_t v___x_6014_; uint32_t v___x_6015_; uint8_t v___x_6016_; 
v___x_6008_ = 23;
v___x_6009_ = lean_uint32_shift_right(v___y_6006_, v___x_6008_);
v___x_6010_ = 255;
v_ex_6011_ = lean_uint32_land(v___x_6009_, v___x_6010_);
v___x_6012_ = lean_uint32_shift_right(v___y_6007_, v___x_6008_);
v_ey_6013_ = lean_uint32_land(v___x_6012_, v___x_6010_);
v___x_6014_ = lean_uint32_add(v_ex_6011_, v_ey_6013_);
v___x_6015_ = 128;
v___x_6016_ = lean_uint32_dec_lt(v___x_6014_, v___x_6015_);
if (v___x_6016_ == 0)
{
uint8_t v___x_6017_; 
v___x_6017_ = lean_uint32_dec_eq(v_ex_6011_, v___x_6010_);
if (v___x_6017_ == 0)
{
v___y_5948_ = v___y_6006_;
v___y_5949_ = v___x_6016_;
v___y_5950_ = v_ey_6013_;
v___y_5951_ = v___x_6010_;
v___y_5952_ = v___y_6007_;
v___y_5953_ = v___x_5458_;
goto v___jp_5947_;
}
else
{
v___y_5948_ = v___y_6006_;
v___y_5949_ = v___x_6016_;
v___y_5950_ = v_ey_6013_;
v___y_5951_ = v___x_6010_;
v___y_5952_ = v___y_6007_;
v___y_5953_ = v___x_6016_;
goto v___jp_5947_;
}
}
else
{
uint32_t v___x_6018_; uint32_t v___x_6019_; uint32_t v___x_6020_; uint8_t v___x_6021_; 
v___x_6018_ = 4278190080;
v___x_6019_ = 1;
v___x_6020_ = lean_uint32_shift_left(v___y_6006_, v___x_6019_);
v___x_6021_ = lean_uint32_dec_le(v___x_6018_, v___x_6020_);
if (v___x_6021_ == 0)
{
uint32_t v___x_6022_; uint8_t v___x_6023_; 
v___x_6022_ = lean_uint32_shift_left(v___y_6007_, v___x_6019_);
v___x_6023_ = lean_uint32_dec_le(v___x_6018_, v___x_6022_);
v___y_5990_ = v___y_6006_;
v___y_5991_ = v___x_6008_;
v___y_5992_ = v_ey_6013_;
v___y_5993_ = v___x_6010_;
v___y_5994_ = v___y_6007_;
v___y_5995_ = v_ex_6011_;
v___y_5996_ = v___x_6023_;
goto v___jp_5989_;
}
else
{
v___y_5990_ = v___y_6006_;
v___y_5991_ = v___x_6008_;
v___y_5992_ = v_ey_6013_;
v___y_5993_ = v___x_6010_;
v___y_5994_ = v___y_6007_;
v___y_5995_ = v_ex_6011_;
v___y_5996_ = v___x_6021_;
goto v___jp_5989_;
}
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_Fin_foldl_loop___at___00Submission_referenceBmm_spec__0___boxed(lean_object* v_A_6043_, lean_object* v_fst_6044_, lean_object* v_m_6045_, lean_object* v_fst_6046_, lean_object* v_n_6047_, lean_object* v_B_6048_, lean_object* v_p_6049_, lean_object* v_snd_6050_, lean_object* v_n_6051_, lean_object* v_x_6052_, lean_object* v_i_6053_){
_start:
{
uint32_t v_x_boxed_6054_; uint32_t v_res_6055_; lean_object* v_r_6056_; 
v_x_boxed_6054_ = lean_unbox_uint32(v_x_6052_);
lean_dec(v_x_6052_);
v_res_6055_ = lp_competition_Fin_foldl_loop___at___00Submission_referenceBmm_spec__0(v_A_6043_, v_fst_6044_, v_m_6045_, v_fst_6046_, v_n_6047_, v_B_6048_, v_p_6049_, v_snd_6050_, v_n_6051_, v_x_boxed_6054_, v_i_6053_);
lean_dec(v_n_6051_);
lean_dec(v_snd_6050_);
lean_dec(v_p_6049_);
lean_dec_ref(v_B_6048_);
lean_dec(v_n_6047_);
lean_dec(v_fst_6046_);
lean_dec(v_m_6045_);
lean_dec(v_fst_6044_);
lean_dec_ref(v_A_6043_);
v_r_6056_ = lean_box_uint32(v_res_6055_);
return v_r_6056_;
}
}
LEAN_EXPORT uint32_t lp_competition_Submission_referenceBmm___lam__0(lean_object* v_m_6057_, lean_object* v_p_6058_, lean_object* v_A_6059_, lean_object* v_n_6060_, lean_object* v_B_6061_, lean_object* v_q_6062_){
_start:
{
lean_object* v___x_6063_; lean_object* v_snd_6064_; lean_object* v_fst_6065_; lean_object* v_fst_6066_; lean_object* v_snd_6067_; lean_object* v___x_6068_; uint32_t v___x_6069_; uint32_t v___x_6070_; 
v___x_6063_ = lp_competition_Competition_bmmDecodeC(v_m_6057_, v_p_6058_, v_q_6062_);
v_snd_6064_ = lean_ctor_get(v___x_6063_, 1);
lean_inc(v_snd_6064_);
v_fst_6065_ = lean_ctor_get(v___x_6063_, 0);
lean_inc(v_fst_6065_);
lean_dec_ref(v___x_6063_);
v_fst_6066_ = lean_ctor_get(v_snd_6064_, 0);
lean_inc(v_fst_6066_);
v_snd_6067_ = lean_ctor_get(v_snd_6064_, 1);
lean_inc(v_snd_6067_);
lean_dec(v_snd_6064_);
v___x_6068_ = lean_unsigned_to_nat(0u);
v___x_6069_ = lean_uint32_once(&lp_competition_Submission_referenceSum___redArg___closed__1, &lp_competition_Submission_referenceSum___redArg___closed__1_once, _init_lp_competition_Submission_referenceSum___redArg___closed__1);
v___x_6070_ = lp_competition_Fin_foldl_loop___at___00Submission_referenceBmm_spec__0(v_A_6059_, v_fst_6065_, v_m_6057_, v_fst_6066_, v_n_6060_, v_B_6061_, v_p_6058_, v_snd_6067_, v_n_6060_, v___x_6069_, v___x_6068_);
lean_dec(v_snd_6067_);
lean_dec(v_fst_6066_);
lean_dec(v_fst_6065_);
return v___x_6070_;
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_referenceBmm___lam__0___boxed(lean_object* v_m_6071_, lean_object* v_p_6072_, lean_object* v_A_6073_, lean_object* v_n_6074_, lean_object* v_B_6075_, lean_object* v_q_6076_){
_start:
{
uint32_t v_res_6077_; lean_object* v_r_6078_; 
v_res_6077_ = lp_competition_Submission_referenceBmm___lam__0(v_m_6071_, v_p_6072_, v_A_6073_, v_n_6074_, v_B_6075_, v_q_6076_);
lean_dec(v_q_6076_);
lean_dec_ref(v_B_6075_);
lean_dec(v_n_6074_);
lean_dec_ref(v_A_6073_);
lean_dec(v_p_6072_);
lean_dec(v_m_6071_);
v_r_6078_ = lean_box_uint32(v_res_6077_);
return v_r_6078_;
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_referenceBmm(lean_object* v_batch_6079_, lean_object* v_m_6080_, lean_object* v_n_6081_, lean_object* v_p_6082_, lean_object* v_A_6083_, lean_object* v_B_6084_){
_start:
{
lean_object* v___f_6085_; lean_object* v___x_6086_; lean_object* v___x_6087_; lean_object* v___x_6088_; 
lean_inc(v_p_6082_);
lean_inc(v_m_6080_);
v___f_6085_ = lean_alloc_closure((void*)(lp_competition_Submission_referenceBmm___lam__0___boxed), 6, 5);
lean_closure_set(v___f_6085_, 0, v_m_6080_);
lean_closure_set(v___f_6085_, 1, v_p_6082_);
lean_closure_set(v___f_6085_, 2, v_A_6083_);
lean_closure_set(v___f_6085_, 3, v_n_6081_);
lean_closure_set(v___f_6085_, 4, v_B_6084_);
v___x_6086_ = lean_nat_mul(v_batch_6079_, v_m_6080_);
lean_dec(v_m_6080_);
v___x_6087_ = lean_nat_mul(v___x_6086_, v_p_6082_);
lean_dec(v_p_6082_);
lean_dec(v___x_6086_);
v___x_6088_ = l_Array_ofFn___redArg(v___x_6087_, v___f_6085_);
return v___x_6088_;
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_referenceBmm___boxed(lean_object* v_batch_6089_, lean_object* v_m_6090_, lean_object* v_n_6091_, lean_object* v_p_6092_, lean_object* v_A_6093_, lean_object* v_B_6094_){
_start:
{
lean_object* v_res_6095_; 
v_res_6095_ = lp_competition_Submission_referenceBmm(v_batch_6089_, v_m_6090_, v_n_6091_, v_p_6092_, v_A_6093_, v_B_6094_);
lean_dec(v_batch_6089_);
return v_res_6095_;
}
}
LEAN_EXPORT float lp_competition_Submission_NativeFinal_sumLoop(lean_object* v_n_6096_, lean_object* v_x_6097_, lean_object* v_k_6098_, float v_acc_6099_){
_start:
{
uint8_t v___x_6100_; 
v___x_6100_ = lean_nat_dec_lt(v_k_6098_, v_n_6096_);
if (v___x_6100_ == 0)
{
lean_dec(v_k_6098_);
return v_acc_6099_;
}
else
{
lean_object* v___x_6101_; lean_object* v___x_6102_; lean_object* v___x_6103_; uint32_t v___x_6104_; float v___x_6105_; float v___x_6106_; 
v___x_6101_ = lean_unsigned_to_nat(1u);
v___x_6102_ = lean_nat_add(v_k_6098_, v___x_6101_);
v___x_6103_ = lean_array_fget_borrowed(v_x_6097_, v_k_6098_);
lean_dec(v_k_6098_);
v___x_6104_ = lean_unbox_uint32(v___x_6103_);
v___x_6105_ = lean_float32_of_bits(v___x_6104_);
v___x_6106_ = lean_float32_add(v_acc_6099_, v___x_6105_);
v_k_6098_ = v___x_6102_;
v_acc_6099_ = v___x_6106_;
goto _start;
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_NativeFinal_sumLoop___boxed(lean_object* v_n_6108_, lean_object* v_x_6109_, lean_object* v_k_6110_, lean_object* v_acc_6111_){
_start:
{
float v_acc_boxed_6112_; float v_res_6113_; lean_object* v_r_6114_; 
v_acc_boxed_6112_ = lean_unbox_float32(v_acc_6111_);
lean_dec_ref(v_acc_6111_);
v_res_6113_ = lp_competition_Submission_NativeFinal_sumLoop(v_n_6108_, v_x_6109_, v_k_6110_, v_acc_boxed_6112_);
lean_dec_ref(v_x_6109_);
lean_dec(v_n_6108_);
v_r_6114_ = lean_box_float32(v_res_6113_);
return v_r_6114_;
}
}
LEAN_EXPORT float lp_competition_Submission_NativeFinal_dotLoop(lean_object* v_n_6115_, lean_object* v_baseA_6116_, lean_object* v_baseB_6117_, lean_object* v_p_6118_, lean_object* v_A_6119_, lean_object* v_B_6120_, lean_object* v_k_6121_, float v_acc_6122_){
_start:
{
float v___y_6124_; uint32_t v___y_6125_; uint8_t v___x_6132_; 
v___x_6132_ = lean_nat_dec_lt(v_k_6121_, v_n_6115_);
if (v___x_6132_ == 0)
{
lean_dec(v_k_6121_);
return v_acc_6122_;
}
else
{
lean_object* v___x_6133_; uint32_t v___x_6134_; uint32_t v___y_6136_; lean_object* v___x_6144_; uint8_t v___x_6145_; 
v___x_6133_ = lean_nat_add(v_baseA_6116_, v_k_6121_);
v___x_6134_ = lean_uint32_once(&lp_competition_Submission_referenceSum___redArg___closed__1, &lp_competition_Submission_referenceSum___redArg___closed__1_once, _init_lp_competition_Submission_referenceSum___redArg___closed__1);
v___x_6144_ = lean_array_get_size(v_A_6119_);
v___x_6145_ = lean_nat_dec_lt(v___x_6133_, v___x_6144_);
if (v___x_6145_ == 0)
{
lean_dec(v___x_6133_);
v___y_6136_ = v___x_6134_;
goto v___jp_6135_;
}
else
{
lean_object* v___x_6146_; uint32_t v___x_6147_; 
v___x_6146_ = lean_array_fget_borrowed(v_A_6119_, v___x_6133_);
lean_dec(v___x_6133_);
v___x_6147_ = lean_unbox_uint32(v___x_6146_);
v___y_6136_ = v___x_6147_;
goto v___jp_6135_;
}
v___jp_6135_:
{
float v_fa_6137_; lean_object* v___x_6138_; lean_object* v___x_6139_; lean_object* v___x_6140_; uint8_t v___x_6141_; 
v_fa_6137_ = lean_float32_of_bits(v___y_6136_);
v___x_6138_ = lean_nat_mul(v_k_6121_, v_p_6118_);
v___x_6139_ = lean_nat_add(v_baseB_6117_, v___x_6138_);
lean_dec(v___x_6138_);
v___x_6140_ = lean_array_get_size(v_B_6120_);
v___x_6141_ = lean_nat_dec_lt(v___x_6139_, v___x_6140_);
if (v___x_6141_ == 0)
{
lean_dec(v___x_6139_);
v___y_6124_ = v_fa_6137_;
v___y_6125_ = v___x_6134_;
goto v___jp_6123_;
}
else
{
lean_object* v___x_6142_; uint32_t v___x_6143_; 
v___x_6142_ = lean_array_fget_borrowed(v_B_6120_, v___x_6139_);
lean_dec(v___x_6139_);
v___x_6143_ = lean_unbox_uint32(v___x_6142_);
v___y_6124_ = v_fa_6137_;
v___y_6125_ = v___x_6143_;
goto v___jp_6123_;
}
}
}
v___jp_6123_:
{
float v_fb_6126_; lean_object* v___x_6127_; lean_object* v___x_6128_; float v___x_6129_; float v___x_6130_; 
v_fb_6126_ = lean_float32_of_bits(v___y_6125_);
v___x_6127_ = lean_unsigned_to_nat(1u);
v___x_6128_ = lean_nat_add(v_k_6121_, v___x_6127_);
lean_dec(v_k_6121_);
v___x_6129_ = lean_float32_mul(v___y_6124_, v_fb_6126_);
v___x_6130_ = lean_float32_add(v_acc_6122_, v___x_6129_);
v_k_6121_ = v___x_6128_;
v_acc_6122_ = v___x_6130_;
goto _start;
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_NativeFinal_dotLoop___boxed(lean_object* v_n_6148_, lean_object* v_baseA_6149_, lean_object* v_baseB_6150_, lean_object* v_p_6151_, lean_object* v_A_6152_, lean_object* v_B_6153_, lean_object* v_k_6154_, lean_object* v_acc_6155_){
_start:
{
float v_acc_boxed_6156_; float v_res_6157_; lean_object* v_r_6158_; 
v_acc_boxed_6156_ = lean_unbox_float32(v_acc_6155_);
lean_dec_ref(v_acc_6155_);
v_res_6157_ = lp_competition_Submission_NativeFinal_dotLoop(v_n_6148_, v_baseA_6149_, v_baseB_6150_, v_p_6151_, v_A_6152_, v_B_6153_, v_k_6154_, v_acc_boxed_6156_);
lean_dec_ref(v_B_6153_);
lean_dec_ref(v_A_6152_);
lean_dec(v_p_6151_);
lean_dec(v_baseB_6150_);
lean_dec(v_baseA_6149_);
lean_dec(v_n_6148_);
v_r_6158_ = lean_box_float32(v_res_6157_);
return v_r_6158_;
}
}
LEAN_EXPORT uint32_t lp_competition_Fin_foldl_loop___at___00Submission_NativeFinal_dot_spec__0(lean_object* v_baseA_6159_, lean_object* v_p_6160_, lean_object* v_baseB_6161_, lean_object* v_B_6162_, lean_object* v_A_6163_, lean_object* v_n_6164_, uint32_t v_x_6165_, lean_object* v_i_6166_){
_start:
{
uint32_t v___y_6168_; float v___y_6173_; float v___y_6174_; float v___y_6178_; uint32_t v___y_6179_; uint8_t v___y_6180_; uint32_t v___y_6195_; float v___y_6196_; uint32_t v___y_6206_; uint8_t v___y_6207_; uint32_t v___y_6222_; uint8_t v___x_6224_; uint32_t v___y_6226_; uint8_t v___y_6227_; uint32_t v___y_6268_; uint32_t v___y_6279_; uint32_t v___y_6283_; uint32_t v___y_6287_; uint32_t v___y_6288_; uint32_t v___y_6289_; uint64_t v___y_6293_; uint8_t v___y_6294_; uint32_t v___y_6295_; uint64_t v___y_6296_; uint32_t v___y_6308_; uint32_t v___y_6309_; uint32_t v___y_6310_; uint32_t v___y_6311_; uint32_t v___y_6312_; uint32_t v___y_6313_; uint32_t v___y_6320_; uint32_t v___y_6321_; uint8_t v___y_6322_; uint32_t v___y_6323_; uint32_t v___y_6324_; uint32_t v___y_6325_; uint64_t v___y_6329_; uint32_t v___y_6330_; uint32_t v___y_6331_; uint64_t v___y_6332_; uint8_t v___y_6333_; uint32_t v___y_6334_; uint64_t v___y_6335_; uint8_t v___y_6345_; uint32_t v___y_6346_; uint32_t v___y_6347_; uint64_t v___y_6348_; uint8_t v___y_6349_; uint32_t v___y_6350_; uint64_t v___y_6351_; uint64_t v___y_6352_; uint32_t v___y_6359_; uint64_t v___y_6360_; uint32_t v___y_6361_; uint64_t v___y_6362_; uint8_t v___y_6363_; uint32_t v___y_6364_; uint64_t v___y_6365_; uint32_t v___y_6371_; uint32_t v___y_6372_; uint64_t v___y_6373_; uint64_t v___y_6374_; uint8_t v___y_6375_; uint64_t v___y_6376_; uint32_t v___y_6377_; uint64_t v___y_6378_; uint64_t v___y_6433_; uint32_t v___y_6434_; uint64_t v___y_6435_; uint32_t v___y_6436_; uint64_t v___y_6437_; uint8_t v___y_6438_; uint32_t v___y_6439_; uint64_t v___y_6440_; uint64_t v___y_6441_; uint32_t v___y_6447_; uint32_t v___y_6448_; uint64_t v___y_6449_; uint64_t v___y_6450_; uint64_t v___y_6451_; uint64_t v___y_6452_; uint8_t v___y_6453_; uint64_t v___y_6454_; uint32_t v___y_6455_; uint64_t v___y_6456_; uint64_t v___y_6457_; uint32_t v___y_6462_; uint64_t v___y_6463_; uint32_t v___y_6464_; uint64_t v___y_6465_; uint8_t v___y_6466_; uint32_t v___y_6467_; uint64_t v___y_6468_; uint64_t v___y_6469_; uint64_t v___y_6470_; uint64_t v___y_6475_; uint32_t v___y_6476_; uint32_t v___y_6477_; uint64_t v___y_6478_; uint64_t v___y_6479_; uint8_t v___y_6480_; uint64_t v___y_6481_; uint32_t v___y_6482_; uint64_t v___y_6483_; uint64_t v___y_6484_; uint64_t v___y_6485_; uint64_t v___y_6490_; uint32_t v___y_6491_; uint64_t v___y_6492_; uint32_t v___y_6493_; uint64_t v___y_6494_; uint8_t v___y_6495_; uint32_t v___y_6496_; uint64_t v___y_6497_; uint64_t v___y_6498_; uint32_t v___y_6503_; uint64_t v___y_6504_; uint32_t v___y_6505_; uint64_t v___y_6506_; uint64_t v___y_6507_; uint64_t v___y_6508_; uint8_t v___y_6509_; uint64_t v___y_6510_; uint32_t v___y_6511_; uint64_t v___y_6512_; uint64_t v___y_6513_; uint32_t v___y_6518_; uint64_t v___y_6519_; uint32_t v___y_6520_; uint64_t v___y_6521_; uint64_t v___y_6522_; uint8_t v___y_6523_; uint32_t v___y_6524_; uint64_t v___y_6525_; uint64_t v___y_6526_; uint64_t v___y_6531_; uint32_t v___y_6532_; uint32_t v___y_6533_; uint64_t v___y_6534_; uint64_t v___y_6535_; uint64_t v___y_6536_; uint8_t v___y_6537_; uint64_t v___y_6538_; uint32_t v___y_6539_; uint64_t v___y_6540_; uint64_t v___y_6541_; uint32_t v___y_6546_; uint64_t v___y_6547_; uint32_t v___y_6548_; uint64_t v___y_6549_; uint8_t v___y_6550_; uint32_t v___y_6551_; uint64_t v___y_6552_; uint64_t v___y_6553_; uint64_t v___y_6554_; uint32_t v___y_6559_; uint32_t v___y_6560_; uint64_t v___y_6561_; uint64_t v___y_6562_; uint8_t v___y_6563_; uint64_t v___y_6564_; uint32_t v___y_6565_; uint64_t v___y_6566_; uint64_t v___y_6567_; uint32_t v___y_6571_; uint64_t v___y_6572_; uint32_t v___y_6573_; uint8_t v___y_6574_; uint64_t v___y_6575_; uint32_t v___y_6576_; uint32_t v___y_6585_; uint32_t v___y_6586_; uint32_t v___y_6587_; uint8_t v___y_6591_; uint32_t v___y_6592_; uint64_t v___y_6593_; uint64_t v___y_6594_; uint32_t v___y_6606_; uint32_t v___y_6607_; uint64_t v___y_6608_; uint8_t v___y_6609_; uint32_t v___y_6610_; uint64_t v___y_6611_; uint64_t v___y_6612_; uint64_t v___y_6613_; uint32_t v___y_6647_; uint32_t v___y_6648_; uint32_t v___y_6649_; uint8_t v___y_6650_; uint32_t v___y_6651_; uint64_t v___y_6652_; uint64_t v___y_6653_; uint64_t v___y_6654_; uint32_t v___y_6661_; uint32_t v___y_6662_; uint32_t v___y_6663_; uint8_t v___y_6664_; uint32_t v___y_6665_; uint64_t v___y_6666_; uint32_t v___y_6667_; uint64_t v___y_6668_; uint32_t v___y_6675_; uint32_t v___y_6676_; uint32_t v___y_6677_; uint8_t v___y_6678_; uint32_t v___y_6679_; uint32_t v___y_6680_; uint32_t v___y_6681_; uint64_t v___y_6682_; uint32_t v___y_6690_; uint32_t v___y_6691_; uint32_t v___y_6692_; uint32_t v___y_6693_; uint32_t v___y_6694_; uint32_t v___y_6695_; uint8_t v___y_6696_; uint32_t v___y_6707_; uint32_t v___y_6708_; uint32_t v___y_6714_; uint32_t v___y_6715_; uint32_t v___y_6716_; uint32_t v___y_6717_; uint8_t v___y_6718_; uint8_t v___y_6719_; uint32_t v___y_6724_; uint32_t v___y_6725_; uint32_t v___y_6726_; uint32_t v___y_6727_; uint8_t v___y_6728_; uint32_t v___y_6729_; uint32_t v___y_6730_; uint8_t v___y_6731_; uint32_t v___y_6733_; uint8_t v___y_6734_; uint32_t v___y_6735_; uint32_t v___y_6736_; uint32_t v___y_6737_; uint8_t v___y_6738_; uint32_t v___y_6739_; uint32_t v___y_6740_; uint8_t v___y_6741_; uint32_t v___y_6743_; uint32_t v___y_6744_; uint32_t v___y_6745_; uint32_t v___y_6746_; uint8_t v___y_6747_; uint32_t v___y_6748_; uint32_t v___y_6749_; uint8_t v___y_6750_; uint32_t v___y_6756_; uint32_t v___y_6757_; uint32_t v___y_6758_; uint32_t v___y_6759_; uint32_t v___y_6760_; uint32_t v___y_6761_; uint8_t v___y_6762_; uint32_t v___y_6772_; uint32_t v___y_6773_; 
v___x_6224_ = lean_nat_dec_lt(v_i_6166_, v_n_6164_);
if (v___x_6224_ == 0)
{
lean_dec(v_i_6166_);
return v_x_6165_;
}
else
{
lean_object* v___x_6790_; uint32_t v___x_6791_; uint32_t v___y_6793_; lean_object* v___x_6800_; uint8_t v___x_6801_; 
v___x_6790_ = lean_nat_add(v_baseA_6159_, v_i_6166_);
v___x_6791_ = lean_uint32_once(&lp_competition_Submission_referenceSum___redArg___closed__1, &lp_competition_Submission_referenceSum___redArg___closed__1_once, _init_lp_competition_Submission_referenceSum___redArg___closed__1);
v___x_6800_ = lean_array_get_size(v_A_6163_);
v___x_6801_ = lean_nat_dec_lt(v___x_6790_, v___x_6800_);
if (v___x_6801_ == 0)
{
lean_dec(v___x_6790_);
v___y_6793_ = v___x_6791_;
goto v___jp_6792_;
}
else
{
lean_object* v___x_6802_; uint32_t v___x_6803_; 
v___x_6802_ = lean_array_fget_borrowed(v_A_6163_, v___x_6790_);
lean_dec(v___x_6790_);
v___x_6803_ = lean_unbox_uint32(v___x_6802_);
v___y_6793_ = v___x_6803_;
goto v___jp_6792_;
}
v___jp_6792_:
{
lean_object* v___x_6794_; lean_object* v___x_6795_; lean_object* v___x_6796_; uint8_t v___x_6797_; 
v___x_6794_ = lean_nat_mul(v_i_6166_, v_p_6160_);
v___x_6795_ = lean_nat_add(v_baseB_6161_, v___x_6794_);
lean_dec(v___x_6794_);
v___x_6796_ = lean_array_get_size(v_B_6162_);
v___x_6797_ = lean_nat_dec_lt(v___x_6795_, v___x_6796_);
if (v___x_6797_ == 0)
{
lean_dec(v___x_6795_);
v___y_6772_ = v___y_6793_;
v___y_6773_ = v___x_6791_;
goto v___jp_6771_;
}
else
{
lean_object* v___x_6798_; uint32_t v___x_6799_; 
v___x_6798_ = lean_array_fget_borrowed(v_B_6162_, v___x_6795_);
lean_dec(v___x_6795_);
v___x_6799_ = lean_unbox_uint32(v___x_6798_);
v___y_6772_ = v___y_6793_;
v___y_6773_ = v___x_6799_;
goto v___jp_6771_;
}
}
}
v___jp_6167_:
{
lean_object* v___x_6169_; lean_object* v___x_6170_; 
v___x_6169_ = lean_unsigned_to_nat(1u);
v___x_6170_ = lean_nat_add(v_i_6166_, v___x_6169_);
lean_dec(v_i_6166_);
v_x_6165_ = v___y_6168_;
v_i_6166_ = v___x_6170_;
goto _start;
}
v___jp_6172_:
{
float v___x_6175_; uint32_t v___x_6176_; 
v___x_6175_ = lean_float32_add(v___y_6173_, v___y_6174_);
v___x_6176_ = lean_float32_to_bits(v___x_6175_);
v___y_6168_ = v___x_6176_;
goto v___jp_6167_;
}
v___jp_6177_:
{
if (v___y_6180_ == 0)
{
float v___x_6181_; 
v___x_6181_ = lean_float32_of_bits(v___y_6179_);
v___y_6173_ = v___y_6178_;
v___y_6174_ = v___x_6181_;
goto v___jp_6172_;
}
else
{
uint32_t v___x_6182_; uint32_t v___x_6183_; uint32_t v___x_6184_; uint32_t v___x_6185_; float v___x_6186_; lean_object* v___x_6187_; uint32_t v___x_6188_; uint32_t v___x_6189_; lean_object* v___x_6190_; lean_object* v___x_6191_; float v___x_6192_; float v___x_6193_; 
v___x_6182_ = 8388607;
v___x_6183_ = lean_uint32_land(v___y_6179_, v___x_6182_);
v___x_6184_ = 8388608;
v___x_6185_ = lean_uint32_lor(v___x_6183_, v___x_6184_);
v___x_6186_ = lean_uint32_to_float32(v___x_6185_);
v___x_6187_ = lp_competition_R2W01b_scaleTable;
v___x_6188_ = 23;
v___x_6189_ = lean_uint32_shift_right(v___y_6179_, v___x_6188_);
v___x_6190_ = lean_uint32_to_nat(v___x_6189_);
v___x_6191_ = lean_array_fget_borrowed(v___x_6187_, v___x_6190_);
lean_dec(v___x_6190_);
v___x_6192_ = lean_unbox_float32(v___x_6191_);
v___x_6193_ = lean_float32_mul(v___x_6186_, v___x_6192_);
v___y_6173_ = v___y_6178_;
v___y_6174_ = v___x_6193_;
goto v___jp_6172_;
}
}
v___jp_6194_:
{
uint32_t v___x_6197_; uint32_t v_a_6198_; uint32_t v___x_6199_; uint32_t v___x_6200_; uint32_t v___x_6201_; uint8_t v___x_6202_; 
v___x_6197_ = 2147483647;
v_a_6198_ = lean_uint32_land(v___y_6195_, v___x_6197_);
v___x_6199_ = 201326591;
v___x_6200_ = 1;
v___x_6201_ = lean_uint32_sub(v_a_6198_, v___x_6200_);
v___x_6202_ = lean_uint32_dec_le(v___x_6199_, v___x_6201_);
if (v___x_6202_ == 0)
{
v___y_6178_ = v___y_6196_;
v___y_6179_ = v___y_6195_;
v___y_6180_ = v___x_6202_;
goto v___jp_6177_;
}
else
{
uint32_t v___x_6203_; uint8_t v___x_6204_; 
v___x_6203_ = 2139095040;
v___x_6204_ = lean_uint32_dec_lt(v_a_6198_, v___x_6203_);
v___y_6178_ = v___y_6196_;
v___y_6179_ = v___y_6195_;
v___y_6180_ = v___x_6204_;
goto v___jp_6177_;
}
}
v___jp_6205_:
{
if (v___y_6207_ == 0)
{
float v___x_6208_; 
v___x_6208_ = lean_float32_of_bits(v_x_6165_);
v___y_6195_ = v___y_6206_;
v___y_6196_ = v___x_6208_;
goto v___jp_6194_;
}
else
{
uint32_t v___x_6209_; uint32_t v___x_6210_; uint32_t v___x_6211_; uint32_t v___x_6212_; float v___x_6213_; lean_object* v___x_6214_; uint32_t v___x_6215_; uint32_t v___x_6216_; lean_object* v___x_6217_; lean_object* v___x_6218_; float v___x_6219_; float v___x_6220_; 
v___x_6209_ = 8388607;
v___x_6210_ = lean_uint32_land(v_x_6165_, v___x_6209_);
v___x_6211_ = 8388608;
v___x_6212_ = lean_uint32_lor(v___x_6210_, v___x_6211_);
v___x_6213_ = lean_uint32_to_float32(v___x_6212_);
v___x_6214_ = lp_competition_R2W01b_scaleTable;
v___x_6215_ = 23;
v___x_6216_ = lean_uint32_shift_right(v_x_6165_, v___x_6215_);
v___x_6217_ = lean_uint32_to_nat(v___x_6216_);
v___x_6218_ = lean_array_fget_borrowed(v___x_6214_, v___x_6217_);
lean_dec(v___x_6217_);
v___x_6219_ = lean_unbox_float32(v___x_6218_);
v___x_6220_ = lean_float32_mul(v___x_6213_, v___x_6219_);
v___y_6195_ = v___y_6206_;
v___y_6196_ = v___x_6220_;
goto v___jp_6194_;
}
}
v___jp_6221_:
{
uint32_t v___x_6223_; 
v___x_6223_ = lp_competition_Submission_TunedAdd_add(v_x_6165_, v___y_6222_);
v___y_6168_ = v___x_6223_;
goto v___jp_6167_;
}
v___jp_6225_:
{
if (v___y_6227_ == 0)
{
uint32_t v___x_6228_; uint32_t v___x_6229_; uint32_t v___x_6230_; uint32_t v___x_6231_; uint8_t v___x_6232_; 
v___x_6228_ = 23;
v___x_6229_ = lean_uint32_shift_right(v_x_6165_, v___x_6228_);
v___x_6230_ = 255;
v___x_6231_ = lean_uint32_land(v___x_6229_, v___x_6230_);
v___x_6232_ = lean_uint32_dec_eq(v___x_6231_, v___x_6230_);
if (v___x_6232_ == 0)
{
if (v___x_6224_ == 0)
{
v___y_6222_ = v___y_6226_;
goto v___jp_6221_;
}
else
{
uint32_t v___x_6233_; uint32_t v___x_6234_; uint8_t v___x_6235_; 
v___x_6233_ = lean_uint32_shift_right(v___y_6226_, v___x_6228_);
v___x_6234_ = lean_uint32_land(v___x_6233_, v___x_6230_);
v___x_6235_ = lean_uint32_dec_eq(v___x_6234_, v___x_6230_);
if (v___x_6235_ == 0)
{
uint32_t v___x_6236_; uint32_t v_a_6237_; uint32_t v___x_6238_; uint32_t v___x_6239_; uint32_t v___x_6240_; uint8_t v___x_6241_; 
v___x_6236_ = 2147483647;
v_a_6237_ = lean_uint32_land(v_x_6165_, v___x_6236_);
v___x_6238_ = 201326591;
v___x_6239_ = 1;
v___x_6240_ = lean_uint32_sub(v_a_6237_, v___x_6239_);
v___x_6241_ = lean_uint32_dec_le(v___x_6238_, v___x_6240_);
if (v___x_6241_ == 0)
{
v___y_6206_ = v___y_6226_;
v___y_6207_ = v___x_6241_;
goto v___jp_6205_;
}
else
{
uint32_t v___x_6242_; uint8_t v___x_6243_; 
v___x_6242_ = 2139095040;
v___x_6243_ = lean_uint32_dec_lt(v_a_6237_, v___x_6242_);
v___y_6206_ = v___y_6226_;
v___y_6207_ = v___x_6243_;
goto v___jp_6205_;
}
}
else
{
uint32_t v___x_6244_; 
v___x_6244_ = lp_competition_Submission_TunedAdd_add(v_x_6165_, v___y_6226_);
v___y_6168_ = v___x_6244_;
goto v___jp_6167_;
}
}
}
else
{
v___y_6222_ = v___y_6226_;
goto v___jp_6221_;
}
}
else
{
uint32_t v___x_6245_; uint32_t v___x_6246_; uint32_t v___x_6247_; uint32_t v___x_6248_; float v___x_6249_; lean_object* v___x_6250_; uint32_t v___x_6251_; uint32_t v___x_6252_; lean_object* v___x_6253_; lean_object* v___x_6254_; float v___x_6255_; float v___x_6256_; uint32_t v___x_6257_; uint32_t v___x_6258_; float v___x_6259_; uint32_t v___x_6260_; lean_object* v___x_6261_; lean_object* v___x_6262_; float v___x_6263_; float v___x_6264_; float v___x_6265_; uint32_t v___x_6266_; 
v___x_6245_ = 8388607;
v___x_6246_ = lean_uint32_land(v_x_6165_, v___x_6245_);
v___x_6247_ = 8388608;
v___x_6248_ = lean_uint32_lor(v___x_6246_, v___x_6247_);
v___x_6249_ = lean_uint32_to_float32(v___x_6248_);
v___x_6250_ = lp_competition_R2W01b_scaleTable;
v___x_6251_ = 23;
v___x_6252_ = lean_uint32_shift_right(v_x_6165_, v___x_6251_);
v___x_6253_ = lean_uint32_to_nat(v___x_6252_);
v___x_6254_ = lean_array_fget_borrowed(v___x_6250_, v___x_6253_);
lean_dec(v___x_6253_);
v___x_6255_ = lean_unbox_float32(v___x_6254_);
v___x_6256_ = lean_float32_mul(v___x_6249_, v___x_6255_);
v___x_6257_ = lean_uint32_land(v___y_6226_, v___x_6245_);
v___x_6258_ = lean_uint32_lor(v___x_6257_, v___x_6247_);
v___x_6259_ = lean_uint32_to_float32(v___x_6258_);
v___x_6260_ = lean_uint32_shift_right(v___y_6226_, v___x_6251_);
v___x_6261_ = lean_uint32_to_nat(v___x_6260_);
v___x_6262_ = lean_array_fget_borrowed(v___x_6250_, v___x_6261_);
lean_dec(v___x_6261_);
v___x_6263_ = lean_unbox_float32(v___x_6262_);
v___x_6264_ = lean_float32_mul(v___x_6259_, v___x_6263_);
v___x_6265_ = lean_float32_add(v___x_6256_, v___x_6264_);
v___x_6266_ = lean_float32_to_bits(v___x_6265_);
v___y_6168_ = v___x_6266_;
goto v___jp_6167_;
}
}
v___jp_6267_:
{
uint32_t v___x_6269_; uint32_t v___x_6270_; uint32_t v___x_6271_; uint32_t v___x_6272_; uint32_t v___x_6273_; uint8_t v___x_6274_; 
v___x_6269_ = 2147483647;
v___x_6270_ = lean_uint32_land(v_x_6165_, v___x_6269_);
v___x_6271_ = 201326592;
v___x_6272_ = lean_uint32_sub(v___x_6270_, v___x_6271_);
v___x_6273_ = 1937768448;
v___x_6274_ = lean_uint32_dec_lt(v___x_6272_, v___x_6273_);
if (v___x_6274_ == 0)
{
v___y_6226_ = v___y_6268_;
v___y_6227_ = v___x_6274_;
goto v___jp_6225_;
}
else
{
uint32_t v___x_6275_; uint32_t v___x_6276_; uint8_t v___x_6277_; 
v___x_6275_ = lean_uint32_land(v___y_6268_, v___x_6269_);
v___x_6276_ = lean_uint32_sub(v___x_6275_, v___x_6271_);
v___x_6277_ = lean_uint32_dec_lt(v___x_6276_, v___x_6273_);
v___y_6226_ = v___y_6268_;
v___y_6227_ = v___x_6277_;
goto v___jp_6225_;
}
}
v___jp_6278_:
{
uint32_t v___x_6280_; uint32_t v___x_6281_; 
v___x_6280_ = 8388608;
v___x_6281_ = lean_uint32_lor(v___y_6279_, v___x_6280_);
v___y_6268_ = v___x_6281_;
goto v___jp_6267_;
}
v___jp_6282_:
{
uint32_t v___x_6284_; uint32_t v___x_6285_; 
v___x_6284_ = 8388608;
v___x_6285_ = lean_uint32_lor(v___y_6283_, v___x_6284_);
v___y_6268_ = v___x_6285_;
goto v___jp_6267_;
}
v___jp_6286_:
{
uint32_t v___x_6290_; uint32_t v___x_6291_; 
v___x_6290_ = lean_uint32_land(v___y_6287_, v___y_6288_);
v___x_6291_ = lean_uint32_lor(v___y_6289_, v___x_6290_);
v___y_6268_ = v___x_6291_;
goto v___jp_6267_;
}
v___jp_6292_:
{
uint8_t v___x_6297_; 
v___x_6297_ = lean_uint64_dec_eq(v___y_6296_, v___y_6293_);
if (v___x_6297_ == 0)
{
uint64_t v___x_6298_; uint8_t v___x_6299_; 
v___x_6298_ = 8388608ULL;
v___x_6299_ = lean_uint64_dec_eq(v___y_6296_, v___x_6298_);
if (v___x_6299_ == 0)
{
uint32_t v___x_6300_; 
v___x_6300_ = lean_uint64_to_uint32(v___y_6296_);
if (v___y_6294_ == 0)
{
uint32_t v___x_6301_; 
v___x_6301_ = 0;
v___y_6287_ = v___x_6300_;
v___y_6288_ = v___y_6295_;
v___y_6289_ = v___x_6301_;
goto v___jp_6286_;
}
else
{
uint32_t v___x_6302_; 
v___x_6302_ = 2147483648;
v___y_6287_ = v___x_6300_;
v___y_6288_ = v___y_6295_;
v___y_6289_ = v___x_6302_;
goto v___jp_6286_;
}
}
else
{
if (v___y_6294_ == 0)
{
uint32_t v___x_6303_; 
v___x_6303_ = 0;
v___y_6279_ = v___x_6303_;
goto v___jp_6278_;
}
else
{
uint32_t v___x_6304_; 
v___x_6304_ = 2147483648;
v___y_6279_ = v___x_6304_;
goto v___jp_6278_;
}
}
}
else
{
if (v___y_6294_ == 0)
{
uint32_t v___x_6305_; 
v___x_6305_ = 0;
v___y_6268_ = v___x_6305_;
goto v___jp_6267_;
}
else
{
uint32_t v___x_6306_; 
v___x_6306_ = 2147483648;
v___y_6268_ = v___x_6306_;
goto v___jp_6267_;
}
}
}
v___jp_6307_:
{
uint32_t v___x_6314_; uint32_t v___x_6315_; uint32_t v___x_6316_; uint32_t v___x_6317_; uint32_t v___x_6318_; 
v___x_6314_ = lean_uint32_land(v___y_6312_, v___y_6309_);
v___x_6315_ = lean_uint32_shift_left(v___x_6314_, v___y_6310_);
v___x_6316_ = lean_uint32_lor(v___y_6313_, v___x_6315_);
v___x_6317_ = lean_uint32_land(v___y_6308_, v___y_6311_);
v___x_6318_ = lean_uint32_lor(v___x_6316_, v___x_6317_);
v___y_6268_ = v___x_6318_;
goto v___jp_6267_;
}
v___jp_6319_:
{
if (v___y_6322_ == 0)
{
uint32_t v___x_6326_; 
v___x_6326_ = 0;
v___y_6308_ = v___y_6325_;
v___y_6309_ = v___y_6320_;
v___y_6310_ = v___y_6321_;
v___y_6311_ = v___y_6323_;
v___y_6312_ = v___y_6324_;
v___y_6313_ = v___x_6326_;
goto v___jp_6307_;
}
else
{
uint32_t v___x_6327_; 
v___x_6327_ = 2147483648;
v___y_6308_ = v___y_6325_;
v___y_6309_ = v___y_6320_;
v___y_6310_ = v___y_6321_;
v___y_6311_ = v___y_6323_;
v___y_6312_ = v___y_6324_;
v___y_6313_ = v___x_6327_;
goto v___jp_6307_;
}
}
v___jp_6328_:
{
uint64_t v___x_6336_; uint64_t v_encodedExponent_6337_; uint32_t v___x_6338_; uint64_t v___x_6339_; uint8_t v___x_6340_; 
v___x_6336_ = 171ULL;
v_encodedExponent_6337_ = lean_uint64_sub(v___y_6329_, v___x_6336_);
v___x_6338_ = lean_uint64_to_uint32(v_encodedExponent_6337_);
v___x_6339_ = 8388608ULL;
v___x_6340_ = lean_uint64_dec_lt(v___y_6335_, v___x_6339_);
if (v___x_6340_ == 0)
{
uint64_t v___x_6341_; uint32_t v___x_6342_; 
v___x_6341_ = lean_uint64_sub(v___y_6335_, v___x_6339_);
v___x_6342_ = lean_uint64_to_uint32(v___x_6341_);
v___y_6320_ = v___y_6330_;
v___y_6321_ = v___y_6331_;
v___y_6322_ = v___y_6333_;
v___y_6323_ = v___y_6334_;
v___y_6324_ = v___x_6338_;
v___y_6325_ = v___x_6342_;
goto v___jp_6319_;
}
else
{
uint32_t v___x_6343_; 
v___x_6343_ = lean_uint64_to_uint32(v___y_6332_);
v___y_6320_ = v___y_6330_;
v___y_6321_ = v___y_6331_;
v___y_6322_ = v___y_6333_;
v___y_6323_ = v___y_6334_;
v___y_6324_ = v___x_6338_;
v___y_6325_ = v___x_6343_;
goto v___jp_6319_;
}
}
v___jp_6344_:
{
uint64_t v___x_6353_; uint8_t v___x_6354_; 
v___x_6353_ = 425ULL;
v___x_6354_ = lean_uint64_dec_lt(v___x_6353_, v___y_6352_);
if (v___x_6354_ == 0)
{
if (v___y_6345_ == 0)
{
v___y_6329_ = v___y_6352_;
v___y_6330_ = v___y_6346_;
v___y_6331_ = v___y_6347_;
v___y_6332_ = v___y_6348_;
v___y_6333_ = v___y_6349_;
v___y_6334_ = v___y_6350_;
v___y_6335_ = v___y_6351_;
goto v___jp_6328_;
}
else
{
uint64_t v___x_6355_; 
v___x_6355_ = 8388608ULL;
v___y_6329_ = v___y_6352_;
v___y_6330_ = v___y_6346_;
v___y_6331_ = v___y_6347_;
v___y_6332_ = v___y_6348_;
v___y_6333_ = v___y_6349_;
v___y_6334_ = v___y_6350_;
v___y_6335_ = v___x_6355_;
goto v___jp_6328_;
}
}
else
{
if (v___y_6349_ == 0)
{
uint32_t v___x_6356_; 
v___x_6356_ = 2139095040;
v___y_6268_ = v___x_6356_;
goto v___jp_6267_;
}
else
{
uint32_t v___x_6357_; 
v___x_6357_ = 4286578688;
v___y_6268_ = v___x_6357_;
goto v___jp_6267_;
}
}
}
v___jp_6358_:
{
uint64_t v___x_6366_; uint8_t v_carry_6367_; 
v___x_6366_ = 16777216ULL;
v_carry_6367_ = lean_uint64_dec_eq(v___y_6365_, v___x_6366_);
if (v_carry_6367_ == 0)
{
v___y_6345_ = v_carry_6367_;
v___y_6346_ = v___y_6359_;
v___y_6347_ = v___y_6361_;
v___y_6348_ = v___y_6362_;
v___y_6349_ = v___y_6363_;
v___y_6350_ = v___y_6364_;
v___y_6351_ = v___y_6365_;
v___y_6352_ = v___y_6360_;
goto v___jp_6344_;
}
else
{
uint64_t v___x_6368_; uint64_t v___x_6369_; 
v___x_6368_ = 1ULL;
v___x_6369_ = lean_uint64_add(v___y_6360_, v___x_6368_);
v___y_6345_ = v_carry_6367_;
v___y_6346_ = v___y_6359_;
v___y_6347_ = v___y_6361_;
v___y_6348_ = v___y_6362_;
v___y_6349_ = v___y_6363_;
v___y_6350_ = v___y_6364_;
v___y_6351_ = v___y_6365_;
v___y_6352_ = v___x_6369_;
goto v___jp_6344_;
}
}
v___jp_6370_:
{
uint64_t v_position_6379_; uint64_t v___x_6380_; uint8_t v___x_6381_; 
v_position_6379_ = lean_uint64_add(v___y_6378_, v___y_6373_);
v___x_6380_ = 172ULL;
v___x_6381_ = lean_uint64_dec_lt(v_position_6379_, v___x_6380_);
if (v___x_6381_ == 0)
{
uint64_t v___x_6382_; uint8_t v___x_6383_; 
v___x_6382_ = 23ULL;
v___x_6383_ = lean_uint64_dec_lt(v___y_6378_, v___x_6382_);
if (v___x_6383_ == 0)
{
uint64_t v___x_6384_; uint8_t v___x_6385_; 
v___x_6384_ = lean_uint64_sub(v___y_6378_, v___x_6382_);
v___x_6385_ = lean_uint64_dec_eq(v___x_6384_, v___y_6374_);
if (v___x_6385_ == 0)
{
uint64_t v___x_6386_; uint8_t v___x_6387_; 
v___x_6386_ = 64ULL;
v___x_6387_ = lean_uint64_dec_lt(v___x_6384_, v___x_6386_);
if (v___x_6387_ == 0)
{
uint8_t v___x_6388_; 
v___x_6388_ = lean_uint64_dec_eq(v___x_6384_, v___x_6386_);
if (v___x_6388_ == 0)
{
v___y_6359_ = v___y_6371_;
v___y_6360_ = v_position_6379_;
v___y_6361_ = v___y_6372_;
v___y_6362_ = v___y_6374_;
v___y_6363_ = v___y_6375_;
v___y_6364_ = v___y_6377_;
v___y_6365_ = v___y_6374_;
goto v___jp_6358_;
}
else
{
uint64_t v___x_6389_; uint8_t v___x_6390_; 
v___x_6389_ = 9223372036854775808ULL;
v___x_6390_ = lean_uint64_dec_lt(v___x_6389_, v___y_6376_);
if (v___x_6390_ == 0)
{
v___y_6359_ = v___y_6371_;
v___y_6360_ = v_position_6379_;
v___y_6361_ = v___y_6372_;
v___y_6362_ = v___y_6374_;
v___y_6363_ = v___y_6375_;
v___y_6364_ = v___y_6377_;
v___y_6365_ = v___y_6374_;
goto v___jp_6358_;
}
else
{
uint64_t v___x_6391_; 
v___x_6391_ = 1ULL;
v___y_6359_ = v___y_6371_;
v___y_6360_ = v_position_6379_;
v___y_6361_ = v___y_6372_;
v___y_6362_ = v___y_6374_;
v___y_6363_ = v___y_6375_;
v___y_6364_ = v___y_6377_;
v___y_6365_ = v___x_6391_;
goto v___jp_6358_;
}
}
}
else
{
uint64_t v_quotient_6392_; uint64_t v___x_6393_; uint64_t v___x_6394_; uint64_t v___x_6395_; uint64_t v_remainder_6396_; uint64_t v___x_6397_; uint64_t v_half_6398_; uint8_t v___x_6399_; 
v_quotient_6392_ = lean_uint64_shift_right(v___y_6376_, v___x_6384_);
v___x_6393_ = 1ULL;
v___x_6394_ = lean_uint64_shift_left(v___x_6393_, v___x_6384_);
v___x_6395_ = lean_uint64_sub(v___x_6394_, v___x_6393_);
v_remainder_6396_ = lean_uint64_land(v___y_6376_, v___x_6395_);
v___x_6397_ = lean_uint64_sub(v___x_6384_, v___x_6393_);
v_half_6398_ = lean_uint64_shift_left(v___x_6393_, v___x_6397_);
v___x_6399_ = lean_uint64_dec_lt(v_remainder_6396_, v_half_6398_);
if (v___x_6399_ == 0)
{
uint8_t v___x_6400_; 
v___x_6400_ = lean_uint64_dec_lt(v_half_6398_, v_remainder_6396_);
if (v___x_6400_ == 0)
{
uint64_t v___x_6401_; uint8_t v___x_6402_; 
v___x_6401_ = lean_uint64_land(v_quotient_6392_, v___x_6393_);
v___x_6402_ = lean_uint64_dec_eq(v___x_6401_, v___y_6374_);
if (v___x_6402_ == 0)
{
uint64_t v___x_6403_; 
v___x_6403_ = lean_uint64_add(v_quotient_6392_, v___x_6393_);
v___y_6359_ = v___y_6371_;
v___y_6360_ = v_position_6379_;
v___y_6361_ = v___y_6372_;
v___y_6362_ = v___y_6374_;
v___y_6363_ = v___y_6375_;
v___y_6364_ = v___y_6377_;
v___y_6365_ = v___x_6403_;
goto v___jp_6358_;
}
else
{
v___y_6359_ = v___y_6371_;
v___y_6360_ = v_position_6379_;
v___y_6361_ = v___y_6372_;
v___y_6362_ = v___y_6374_;
v___y_6363_ = v___y_6375_;
v___y_6364_ = v___y_6377_;
v___y_6365_ = v_quotient_6392_;
goto v___jp_6358_;
}
}
else
{
uint64_t v___x_6404_; 
v___x_6404_ = lean_uint64_add(v_quotient_6392_, v___x_6393_);
v___y_6359_ = v___y_6371_;
v___y_6360_ = v_position_6379_;
v___y_6361_ = v___y_6372_;
v___y_6362_ = v___y_6374_;
v___y_6363_ = v___y_6375_;
v___y_6364_ = v___y_6377_;
v___y_6365_ = v___x_6404_;
goto v___jp_6358_;
}
}
else
{
v___y_6359_ = v___y_6371_;
v___y_6360_ = v_position_6379_;
v___y_6361_ = v___y_6372_;
v___y_6362_ = v___y_6374_;
v___y_6363_ = v___y_6375_;
v___y_6364_ = v___y_6377_;
v___y_6365_ = v_quotient_6392_;
goto v___jp_6358_;
}
}
}
else
{
v___y_6359_ = v___y_6371_;
v___y_6360_ = v_position_6379_;
v___y_6361_ = v___y_6372_;
v___y_6362_ = v___y_6374_;
v___y_6363_ = v___y_6375_;
v___y_6364_ = v___y_6377_;
v___y_6365_ = v___y_6376_;
goto v___jp_6358_;
}
}
else
{
uint64_t v___x_6405_; uint64_t v___x_6406_; 
v___x_6405_ = lean_uint64_sub(v___x_6382_, v___y_6378_);
v___x_6406_ = lean_uint64_shift_left(v___y_6376_, v___x_6405_);
v___y_6359_ = v___y_6371_;
v___y_6360_ = v_position_6379_;
v___y_6361_ = v___y_6372_;
v___y_6362_ = v___y_6374_;
v___y_6363_ = v___y_6375_;
v___y_6364_ = v___y_6377_;
v___y_6365_ = v___x_6406_;
goto v___jp_6358_;
}
}
else
{
uint64_t v___x_6407_; uint8_t v___x_6408_; 
v___x_6407_ = 149ULL;
v___x_6408_ = lean_uint64_dec_lt(v___y_6373_, v___x_6407_);
if (v___x_6408_ == 0)
{
uint64_t v___x_6409_; uint64_t v___x_6410_; 
v___x_6409_ = lean_uint64_sub(v___y_6373_, v___x_6407_);
v___x_6410_ = lean_uint64_shift_left(v___y_6376_, v___x_6409_);
v___y_6293_ = v___y_6374_;
v___y_6294_ = v___y_6375_;
v___y_6295_ = v___y_6377_;
v___y_6296_ = v___x_6410_;
goto v___jp_6292_;
}
else
{
uint64_t v___x_6411_; uint8_t v___x_6412_; 
v___x_6411_ = lean_uint64_sub(v___x_6407_, v___y_6373_);
v___x_6412_ = lean_uint64_dec_eq(v___x_6411_, v___y_6374_);
if (v___x_6412_ == 0)
{
uint64_t v___x_6413_; uint8_t v___x_6414_; 
v___x_6413_ = 64ULL;
v___x_6414_ = lean_uint64_dec_lt(v___x_6411_, v___x_6413_);
if (v___x_6414_ == 0)
{
uint8_t v___x_6415_; 
v___x_6415_ = lean_uint64_dec_eq(v___x_6411_, v___x_6413_);
if (v___x_6415_ == 0)
{
v___y_6293_ = v___y_6374_;
v___y_6294_ = v___y_6375_;
v___y_6295_ = v___y_6377_;
v___y_6296_ = v___y_6374_;
goto v___jp_6292_;
}
else
{
uint64_t v___x_6416_; uint8_t v___x_6417_; 
v___x_6416_ = 9223372036854775808ULL;
v___x_6417_ = lean_uint64_dec_lt(v___x_6416_, v___y_6376_);
if (v___x_6417_ == 0)
{
v___y_6293_ = v___y_6374_;
v___y_6294_ = v___y_6375_;
v___y_6295_ = v___y_6377_;
v___y_6296_ = v___y_6374_;
goto v___jp_6292_;
}
else
{
uint64_t v___x_6418_; 
v___x_6418_ = 1ULL;
v___y_6293_ = v___y_6374_;
v___y_6294_ = v___y_6375_;
v___y_6295_ = v___y_6377_;
v___y_6296_ = v___x_6418_;
goto v___jp_6292_;
}
}
}
else
{
uint64_t v_quotient_6419_; uint64_t v___x_6420_; uint64_t v___x_6421_; uint64_t v___x_6422_; uint64_t v_remainder_6423_; uint64_t v___x_6424_; uint64_t v_half_6425_; uint8_t v___x_6426_; 
v_quotient_6419_ = lean_uint64_shift_right(v___y_6376_, v___x_6411_);
v___x_6420_ = 1ULL;
v___x_6421_ = lean_uint64_shift_left(v___x_6420_, v___x_6411_);
v___x_6422_ = lean_uint64_sub(v___x_6421_, v___x_6420_);
v_remainder_6423_ = lean_uint64_land(v___y_6376_, v___x_6422_);
v___x_6424_ = lean_uint64_sub(v___x_6411_, v___x_6420_);
v_half_6425_ = lean_uint64_shift_left(v___x_6420_, v___x_6424_);
v___x_6426_ = lean_uint64_dec_lt(v_remainder_6423_, v_half_6425_);
if (v___x_6426_ == 0)
{
uint8_t v___x_6427_; 
v___x_6427_ = lean_uint64_dec_lt(v_half_6425_, v_remainder_6423_);
if (v___x_6427_ == 0)
{
uint64_t v___x_6428_; uint8_t v___x_6429_; 
v___x_6428_ = lean_uint64_land(v_quotient_6419_, v___x_6420_);
v___x_6429_ = lean_uint64_dec_eq(v___x_6428_, v___y_6374_);
if (v___x_6429_ == 0)
{
uint64_t v___x_6430_; 
v___x_6430_ = lean_uint64_add(v_quotient_6419_, v___x_6420_);
v___y_6293_ = v___y_6374_;
v___y_6294_ = v___y_6375_;
v___y_6295_ = v___y_6377_;
v___y_6296_ = v___x_6430_;
goto v___jp_6292_;
}
else
{
v___y_6293_ = v___y_6374_;
v___y_6294_ = v___y_6375_;
v___y_6295_ = v___y_6377_;
v___y_6296_ = v_quotient_6419_;
goto v___jp_6292_;
}
}
else
{
uint64_t v___x_6431_; 
v___x_6431_ = lean_uint64_add(v_quotient_6419_, v___x_6420_);
v___y_6293_ = v___y_6374_;
v___y_6294_ = v___y_6375_;
v___y_6295_ = v___y_6377_;
v___y_6296_ = v___x_6431_;
goto v___jp_6292_;
}
}
else
{
v___y_6293_ = v___y_6374_;
v___y_6294_ = v___y_6375_;
v___y_6295_ = v___y_6377_;
v___y_6296_ = v_quotient_6419_;
goto v___jp_6292_;
}
}
}
else
{
v___y_6293_ = v___y_6374_;
v___y_6294_ = v___y_6375_;
v___y_6295_ = v___y_6377_;
v___y_6296_ = v___y_6376_;
goto v___jp_6292_;
}
}
}
}
v___jp_6432_:
{
uint64_t v___x_6442_; uint64_t v___x_6443_; uint8_t v___x_6444_; 
v___x_6442_ = 1ULL;
v___x_6443_ = lean_uint64_shift_right(v___y_6433_, v___x_6442_);
v___x_6444_ = lean_uint64_dec_eq(v___x_6443_, v___y_6437_);
if (v___x_6444_ == 0)
{
uint64_t v___x_6445_; 
v___x_6445_ = lean_uint64_add(v___y_6441_, v___x_6442_);
v___y_6371_ = v___y_6434_;
v___y_6372_ = v___y_6436_;
v___y_6373_ = v___y_6435_;
v___y_6374_ = v___y_6437_;
v___y_6375_ = v___y_6438_;
v___y_6376_ = v___y_6440_;
v___y_6377_ = v___y_6439_;
v___y_6378_ = v___x_6445_;
goto v___jp_6370_;
}
else
{
v___y_6371_ = v___y_6434_;
v___y_6372_ = v___y_6436_;
v___y_6373_ = v___y_6435_;
v___y_6374_ = v___y_6437_;
v___y_6375_ = v___y_6438_;
v___y_6376_ = v___y_6440_;
v___y_6377_ = v___y_6439_;
v___y_6378_ = v___y_6441_;
goto v___jp_6370_;
}
}
v___jp_6446_:
{
uint64_t v___x_6458_; uint8_t v___x_6459_; 
v___x_6458_ = lean_uint64_shift_right(v___y_6456_, v___y_6450_);
v___x_6459_ = lean_uint64_dec_eq(v___x_6458_, v___y_6451_);
if (v___x_6459_ == 0)
{
uint64_t v___x_6460_; 
v___x_6460_ = lean_uint64_add(v___y_6452_, v___y_6450_);
v___y_6433_ = v___y_6457_;
v___y_6434_ = v___y_6447_;
v___y_6435_ = v___y_6449_;
v___y_6436_ = v___y_6448_;
v___y_6437_ = v___y_6451_;
v___y_6438_ = v___y_6453_;
v___y_6439_ = v___y_6455_;
v___y_6440_ = v___y_6454_;
v___y_6441_ = v___x_6460_;
goto v___jp_6432_;
}
else
{
v___y_6433_ = v___y_6457_;
v___y_6434_ = v___y_6447_;
v___y_6435_ = v___y_6449_;
v___y_6436_ = v___y_6448_;
v___y_6437_ = v___y_6451_;
v___y_6438_ = v___y_6453_;
v___y_6439_ = v___y_6455_;
v___y_6440_ = v___y_6454_;
v___y_6441_ = v___y_6452_;
goto v___jp_6432_;
}
}
v___jp_6461_:
{
uint64_t v___x_6471_; uint64_t v___x_6472_; uint8_t v___x_6473_; 
v___x_6471_ = 2ULL;
v___x_6472_ = lean_uint64_shift_right(v___y_6469_, v___x_6471_);
v___x_6473_ = lean_uint64_dec_eq(v___x_6472_, v___y_6465_);
if (v___x_6473_ == 0)
{
v___y_6447_ = v___y_6462_;
v___y_6448_ = v___y_6464_;
v___y_6449_ = v___y_6463_;
v___y_6450_ = v___x_6471_;
v___y_6451_ = v___y_6465_;
v___y_6452_ = v___y_6470_;
v___y_6453_ = v___y_6466_;
v___y_6454_ = v___y_6468_;
v___y_6455_ = v___y_6467_;
v___y_6456_ = v___y_6469_;
v___y_6457_ = v___x_6472_;
goto v___jp_6446_;
}
else
{
v___y_6447_ = v___y_6462_;
v___y_6448_ = v___y_6464_;
v___y_6449_ = v___y_6463_;
v___y_6450_ = v___x_6471_;
v___y_6451_ = v___y_6465_;
v___y_6452_ = v___y_6470_;
v___y_6453_ = v___y_6466_;
v___y_6454_ = v___y_6468_;
v___y_6455_ = v___y_6467_;
v___y_6456_ = v___y_6469_;
v___y_6457_ = v___y_6469_;
goto v___jp_6446_;
}
}
v___jp_6474_:
{
uint64_t v___x_6486_; uint8_t v___x_6487_; 
v___x_6486_ = lean_uint64_shift_right(v___y_6475_, v___y_6483_);
v___x_6487_ = lean_uint64_dec_eq(v___x_6486_, v___y_6479_);
if (v___x_6487_ == 0)
{
uint64_t v___x_6488_; 
v___x_6488_ = lean_uint64_add(v___y_6484_, v___y_6483_);
v___y_6462_ = v___y_6476_;
v___y_6463_ = v___y_6478_;
v___y_6464_ = v___y_6477_;
v___y_6465_ = v___y_6479_;
v___y_6466_ = v___y_6480_;
v___y_6467_ = v___y_6482_;
v___y_6468_ = v___y_6481_;
v___y_6469_ = v___y_6485_;
v___y_6470_ = v___x_6488_;
goto v___jp_6461_;
}
else
{
v___y_6462_ = v___y_6476_;
v___y_6463_ = v___y_6478_;
v___y_6464_ = v___y_6477_;
v___y_6465_ = v___y_6479_;
v___y_6466_ = v___y_6480_;
v___y_6467_ = v___y_6482_;
v___y_6468_ = v___y_6481_;
v___y_6469_ = v___y_6485_;
v___y_6470_ = v___y_6484_;
goto v___jp_6461_;
}
}
v___jp_6489_:
{
uint64_t v___x_6499_; uint64_t v___x_6500_; uint8_t v___x_6501_; 
v___x_6499_ = 4ULL;
v___x_6500_ = lean_uint64_shift_right(v___y_6490_, v___x_6499_);
v___x_6501_ = lean_uint64_dec_eq(v___x_6500_, v___y_6494_);
if (v___x_6501_ == 0)
{
v___y_6475_ = v___y_6490_;
v___y_6476_ = v___y_6491_;
v___y_6477_ = v___y_6493_;
v___y_6478_ = v___y_6492_;
v___y_6479_ = v___y_6494_;
v___y_6480_ = v___y_6495_;
v___y_6481_ = v___y_6497_;
v___y_6482_ = v___y_6496_;
v___y_6483_ = v___x_6499_;
v___y_6484_ = v___y_6498_;
v___y_6485_ = v___x_6500_;
goto v___jp_6474_;
}
else
{
v___y_6475_ = v___y_6490_;
v___y_6476_ = v___y_6491_;
v___y_6477_ = v___y_6493_;
v___y_6478_ = v___y_6492_;
v___y_6479_ = v___y_6494_;
v___y_6480_ = v___y_6495_;
v___y_6481_ = v___y_6497_;
v___y_6482_ = v___y_6496_;
v___y_6483_ = v___x_6499_;
v___y_6484_ = v___y_6498_;
v___y_6485_ = v___y_6490_;
goto v___jp_6474_;
}
}
v___jp_6502_:
{
uint64_t v___x_6514_; uint8_t v___x_6515_; 
v___x_6514_ = lean_uint64_shift_right(v___y_6504_, v___y_6508_);
v___x_6515_ = lean_uint64_dec_eq(v___x_6514_, v___y_6507_);
if (v___x_6515_ == 0)
{
uint64_t v___x_6516_; 
v___x_6516_ = lean_uint64_add(v___y_6512_, v___y_6508_);
v___y_6490_ = v___y_6513_;
v___y_6491_ = v___y_6503_;
v___y_6492_ = v___y_6506_;
v___y_6493_ = v___y_6505_;
v___y_6494_ = v___y_6507_;
v___y_6495_ = v___y_6509_;
v___y_6496_ = v___y_6511_;
v___y_6497_ = v___y_6510_;
v___y_6498_ = v___x_6516_;
goto v___jp_6489_;
}
else
{
v___y_6490_ = v___y_6513_;
v___y_6491_ = v___y_6503_;
v___y_6492_ = v___y_6506_;
v___y_6493_ = v___y_6505_;
v___y_6494_ = v___y_6507_;
v___y_6495_ = v___y_6509_;
v___y_6496_ = v___y_6511_;
v___y_6497_ = v___y_6510_;
v___y_6498_ = v___y_6512_;
goto v___jp_6489_;
}
}
v___jp_6517_:
{
uint64_t v___x_6527_; uint64_t v___x_6528_; uint8_t v___x_6529_; 
v___x_6527_ = 8ULL;
v___x_6528_ = lean_uint64_shift_right(v___y_6521_, v___x_6527_);
v___x_6529_ = lean_uint64_dec_eq(v___x_6528_, v___y_6522_);
if (v___x_6529_ == 0)
{
v___y_6503_ = v___y_6518_;
v___y_6504_ = v___y_6521_;
v___y_6505_ = v___y_6520_;
v___y_6506_ = v___y_6519_;
v___y_6507_ = v___y_6522_;
v___y_6508_ = v___x_6527_;
v___y_6509_ = v___y_6523_;
v___y_6510_ = v___y_6525_;
v___y_6511_ = v___y_6524_;
v___y_6512_ = v___y_6526_;
v___y_6513_ = v___x_6528_;
goto v___jp_6502_;
}
else
{
v___y_6503_ = v___y_6518_;
v___y_6504_ = v___y_6521_;
v___y_6505_ = v___y_6520_;
v___y_6506_ = v___y_6519_;
v___y_6507_ = v___y_6522_;
v___y_6508_ = v___x_6527_;
v___y_6509_ = v___y_6523_;
v___y_6510_ = v___y_6525_;
v___y_6511_ = v___y_6524_;
v___y_6512_ = v___y_6526_;
v___y_6513_ = v___y_6521_;
goto v___jp_6502_;
}
}
v___jp_6530_:
{
uint64_t v___x_6542_; uint8_t v___x_6543_; 
v___x_6542_ = lean_uint64_shift_right(v___y_6540_, v___y_6531_);
v___x_6543_ = lean_uint64_dec_eq(v___x_6542_, v___y_6536_);
if (v___x_6543_ == 0)
{
uint64_t v___x_6544_; 
v___x_6544_ = lean_uint64_add(v___y_6535_, v___y_6531_);
v___y_6518_ = v___y_6532_;
v___y_6519_ = v___y_6534_;
v___y_6520_ = v___y_6533_;
v___y_6521_ = v___y_6541_;
v___y_6522_ = v___y_6536_;
v___y_6523_ = v___y_6537_;
v___y_6524_ = v___y_6539_;
v___y_6525_ = v___y_6538_;
v___y_6526_ = v___x_6544_;
goto v___jp_6517_;
}
else
{
v___y_6518_ = v___y_6532_;
v___y_6519_ = v___y_6534_;
v___y_6520_ = v___y_6533_;
v___y_6521_ = v___y_6541_;
v___y_6522_ = v___y_6536_;
v___y_6523_ = v___y_6537_;
v___y_6524_ = v___y_6539_;
v___y_6525_ = v___y_6538_;
v___y_6526_ = v___y_6535_;
goto v___jp_6517_;
}
}
v___jp_6545_:
{
uint64_t v___x_6555_; uint64_t v___x_6556_; uint8_t v___x_6557_; 
v___x_6555_ = 16ULL;
v___x_6556_ = lean_uint64_shift_right(v___y_6553_, v___x_6555_);
v___x_6557_ = lean_uint64_dec_eq(v___x_6556_, v___y_6549_);
if (v___x_6557_ == 0)
{
v___y_6531_ = v___x_6555_;
v___y_6532_ = v___y_6546_;
v___y_6533_ = v___y_6548_;
v___y_6534_ = v___y_6547_;
v___y_6535_ = v___y_6554_;
v___y_6536_ = v___y_6549_;
v___y_6537_ = v___y_6550_;
v___y_6538_ = v___y_6552_;
v___y_6539_ = v___y_6551_;
v___y_6540_ = v___y_6553_;
v___y_6541_ = v___x_6556_;
goto v___jp_6530_;
}
else
{
v___y_6531_ = v___x_6555_;
v___y_6532_ = v___y_6546_;
v___y_6533_ = v___y_6548_;
v___y_6534_ = v___y_6547_;
v___y_6535_ = v___y_6554_;
v___y_6536_ = v___y_6549_;
v___y_6537_ = v___y_6550_;
v___y_6538_ = v___y_6552_;
v___y_6539_ = v___y_6551_;
v___y_6540_ = v___y_6553_;
v___y_6541_ = v___y_6553_;
goto v___jp_6530_;
}
}
v___jp_6558_:
{
uint64_t v___x_6568_; uint8_t v___x_6569_; 
v___x_6568_ = lean_uint64_shift_right(v___y_6564_, v___y_6566_);
v___x_6569_ = lean_uint64_dec_eq(v___x_6568_, v___y_6562_);
if (v___x_6569_ == 0)
{
v___y_6546_ = v___y_6559_;
v___y_6547_ = v___y_6561_;
v___y_6548_ = v___y_6560_;
v___y_6549_ = v___y_6562_;
v___y_6550_ = v___y_6563_;
v___y_6551_ = v___y_6565_;
v___y_6552_ = v___y_6564_;
v___y_6553_ = v___y_6567_;
v___y_6554_ = v___y_6566_;
goto v___jp_6545_;
}
else
{
v___y_6546_ = v___y_6559_;
v___y_6547_ = v___y_6561_;
v___y_6548_ = v___y_6560_;
v___y_6549_ = v___y_6562_;
v___y_6550_ = v___y_6563_;
v___y_6551_ = v___y_6565_;
v___y_6552_ = v___y_6564_;
v___y_6553_ = v___y_6567_;
v___y_6554_ = v___y_6562_;
goto v___jp_6545_;
}
}
v___jp_6570_:
{
uint64_t v___x_6577_; uint8_t v___x_6578_; 
v___x_6577_ = 0ULL;
v___x_6578_ = lean_uint64_dec_eq(v___y_6575_, v___x_6577_);
if (v___x_6578_ == 0)
{
uint64_t v___x_6579_; uint64_t v___x_6580_; uint8_t v___x_6581_; 
v___x_6579_ = 32ULL;
v___x_6580_ = lean_uint64_shift_right(v___y_6575_, v___x_6579_);
v___x_6581_ = lean_uint64_dec_eq(v___x_6580_, v___x_6577_);
if (v___x_6581_ == 0)
{
v___y_6559_ = v___y_6571_;
v___y_6560_ = v___y_6573_;
v___y_6561_ = v___y_6572_;
v___y_6562_ = v___x_6577_;
v___y_6563_ = v___y_6574_;
v___y_6564_ = v___y_6575_;
v___y_6565_ = v___y_6576_;
v___y_6566_ = v___x_6579_;
v___y_6567_ = v___x_6580_;
goto v___jp_6558_;
}
else
{
v___y_6559_ = v___y_6571_;
v___y_6560_ = v___y_6573_;
v___y_6561_ = v___y_6572_;
v___y_6562_ = v___x_6577_;
v___y_6563_ = v___y_6574_;
v___y_6564_ = v___y_6575_;
v___y_6565_ = v___y_6576_;
v___y_6566_ = v___x_6579_;
v___y_6567_ = v___y_6575_;
goto v___jp_6558_;
}
}
else
{
if (v___y_6574_ == 0)
{
uint32_t v___x_6582_; 
v___x_6582_ = 0;
v___y_6268_ = v___x_6582_;
goto v___jp_6267_;
}
else
{
uint32_t v___x_6583_; 
v___x_6583_ = 2147483648;
v___y_6268_ = v___x_6583_;
goto v___jp_6267_;
}
}
}
v___jp_6584_:
{
uint32_t v___x_6588_; uint32_t v___x_6589_; 
v___x_6588_ = lean_uint32_land(v___y_6585_, v___y_6586_);
v___x_6589_ = lean_uint32_lor(v___y_6587_, v___x_6588_);
v___y_6268_ = v___x_6589_;
goto v___jp_6267_;
}
v___jp_6590_:
{
uint8_t v___x_6595_; 
v___x_6595_ = lean_uint64_dec_eq(v___y_6594_, v___y_6593_);
if (v___x_6595_ == 0)
{
uint64_t v___x_6596_; uint8_t v___x_6597_; 
v___x_6596_ = 8388608ULL;
v___x_6597_ = lean_uint64_dec_eq(v___y_6594_, v___x_6596_);
if (v___x_6597_ == 0)
{
uint32_t v___x_6598_; 
v___x_6598_ = lean_uint64_to_uint32(v___y_6594_);
if (v___y_6591_ == 0)
{
uint32_t v___x_6599_; 
v___x_6599_ = 0;
v___y_6585_ = v___x_6598_;
v___y_6586_ = v___y_6592_;
v___y_6587_ = v___x_6599_;
goto v___jp_6584_;
}
else
{
uint32_t v___x_6600_; 
v___x_6600_ = 2147483648;
v___y_6585_ = v___x_6598_;
v___y_6586_ = v___y_6592_;
v___y_6587_ = v___x_6600_;
goto v___jp_6584_;
}
}
else
{
if (v___y_6591_ == 0)
{
uint32_t v___x_6601_; 
v___x_6601_ = 0;
v___y_6283_ = v___x_6601_;
goto v___jp_6282_;
}
else
{
uint32_t v___x_6602_; 
v___x_6602_ = 2147483648;
v___y_6283_ = v___x_6602_;
goto v___jp_6282_;
}
}
}
else
{
if (v___y_6591_ == 0)
{
uint32_t v___x_6603_; 
v___x_6603_ = 0;
v___y_6268_ = v___x_6603_;
goto v___jp_6267_;
}
else
{
uint32_t v___x_6604_; 
v___x_6604_ = 2147483648;
v___y_6268_ = v___x_6604_;
goto v___jp_6267_;
}
}
}
v___jp_6605_:
{
uint64_t v___x_6614_; uint64_t v___x_6615_; uint64_t v___x_6616_; uint8_t v___x_6617_; 
v___x_6614_ = lean_uint64_mul(v___y_6611_, v___y_6612_);
v___x_6615_ = lean_uint64_add(v___y_6608_, v___y_6613_);
v___x_6616_ = 281474976710656ULL;
v___x_6617_ = lean_uint64_dec_lt(v___x_6614_, v___x_6616_);
if (v___x_6617_ == 0)
{
v___y_6571_ = v___y_6606_;
v___y_6572_ = v___x_6615_;
v___y_6573_ = v___y_6607_;
v___y_6574_ = v___y_6609_;
v___y_6575_ = v___x_6614_;
v___y_6576_ = v___y_6610_;
goto v___jp_6570_;
}
else
{
uint64_t v___x_6618_; uint8_t v___x_6619_; 
v___x_6618_ = 123ULL;
v___x_6619_ = lean_uint64_dec_le(v___x_6615_, v___x_6618_);
if (v___x_6619_ == 0)
{
v___y_6571_ = v___y_6606_;
v___y_6572_ = v___x_6615_;
v___y_6573_ = v___y_6607_;
v___y_6574_ = v___y_6609_;
v___y_6575_ = v___x_6614_;
v___y_6576_ = v___y_6610_;
goto v___jp_6570_;
}
else
{
uint64_t v___x_6620_; uint8_t v___x_6621_; 
v___x_6620_ = 0ULL;
v___x_6621_ = lean_uint64_dec_eq(v___x_6614_, v___x_6620_);
if (v___x_6621_ == 0)
{
uint64_t v___x_6622_; uint64_t v___x_6623_; uint8_t v___x_6624_; 
v___x_6622_ = 149ULL;
v___x_6623_ = lean_uint64_sub(v___x_6622_, v___x_6615_);
v___x_6624_ = lean_uint64_dec_eq(v___x_6623_, v___x_6620_);
if (v___x_6624_ == 0)
{
uint64_t v___x_6625_; uint8_t v___x_6626_; 
v___x_6625_ = 64ULL;
v___x_6626_ = lean_uint64_dec_lt(v___x_6623_, v___x_6625_);
if (v___x_6626_ == 0)
{
uint8_t v___x_6627_; 
v___x_6627_ = lean_uint64_dec_eq(v___x_6623_, v___x_6625_);
if (v___x_6627_ == 0)
{
v___y_6591_ = v___y_6609_;
v___y_6592_ = v___y_6610_;
v___y_6593_ = v___x_6620_;
v___y_6594_ = v___x_6620_;
goto v___jp_6590_;
}
else
{
uint64_t v___x_6628_; uint8_t v___x_6629_; 
v___x_6628_ = 9223372036854775808ULL;
v___x_6629_ = lean_uint64_dec_lt(v___x_6628_, v___x_6614_);
if (v___x_6629_ == 0)
{
v___y_6591_ = v___y_6609_;
v___y_6592_ = v___y_6610_;
v___y_6593_ = v___x_6620_;
v___y_6594_ = v___x_6620_;
goto v___jp_6590_;
}
else
{
uint64_t v___x_6630_; 
v___x_6630_ = 1ULL;
v___y_6591_ = v___y_6609_;
v___y_6592_ = v___y_6610_;
v___y_6593_ = v___x_6620_;
v___y_6594_ = v___x_6630_;
goto v___jp_6590_;
}
}
}
else
{
uint64_t v_quotient_6631_; uint64_t v___x_6632_; uint64_t v___x_6633_; uint64_t v___x_6634_; uint64_t v_remainder_6635_; uint64_t v___x_6636_; uint64_t v_half_6637_; uint8_t v___x_6638_; 
v_quotient_6631_ = lean_uint64_shift_right(v___x_6614_, v___x_6623_);
v___x_6632_ = 1ULL;
v___x_6633_ = lean_uint64_shift_left(v___x_6632_, v___x_6623_);
v___x_6634_ = lean_uint64_sub(v___x_6633_, v___x_6632_);
v_remainder_6635_ = lean_uint64_land(v___x_6614_, v___x_6634_);
v___x_6636_ = lean_uint64_sub(v___x_6623_, v___x_6632_);
v_half_6637_ = lean_uint64_shift_left(v___x_6632_, v___x_6636_);
v___x_6638_ = lean_uint64_dec_lt(v_remainder_6635_, v_half_6637_);
if (v___x_6638_ == 0)
{
uint8_t v___x_6639_; 
v___x_6639_ = lean_uint64_dec_lt(v_half_6637_, v_remainder_6635_);
if (v___x_6639_ == 0)
{
uint64_t v___x_6640_; uint8_t v___x_6641_; 
v___x_6640_ = lean_uint64_land(v_quotient_6631_, v___x_6632_);
v___x_6641_ = lean_uint64_dec_eq(v___x_6640_, v___x_6620_);
if (v___x_6641_ == 0)
{
uint64_t v___x_6642_; 
v___x_6642_ = lean_uint64_add(v_quotient_6631_, v___x_6632_);
v___y_6591_ = v___y_6609_;
v___y_6592_ = v___y_6610_;
v___y_6593_ = v___x_6620_;
v___y_6594_ = v___x_6642_;
goto v___jp_6590_;
}
else
{
v___y_6591_ = v___y_6609_;
v___y_6592_ = v___y_6610_;
v___y_6593_ = v___x_6620_;
v___y_6594_ = v_quotient_6631_;
goto v___jp_6590_;
}
}
else
{
uint64_t v___x_6643_; 
v___x_6643_ = lean_uint64_add(v_quotient_6631_, v___x_6632_);
v___y_6591_ = v___y_6609_;
v___y_6592_ = v___y_6610_;
v___y_6593_ = v___x_6620_;
v___y_6594_ = v___x_6643_;
goto v___jp_6590_;
}
}
else
{
v___y_6591_ = v___y_6609_;
v___y_6592_ = v___y_6610_;
v___y_6593_ = v___x_6620_;
v___y_6594_ = v_quotient_6631_;
goto v___jp_6590_;
}
}
}
else
{
v___y_6591_ = v___y_6609_;
v___y_6592_ = v___y_6610_;
v___y_6593_ = v___x_6620_;
v___y_6594_ = v___x_6614_;
goto v___jp_6590_;
}
}
else
{
if (v___y_6609_ == 0)
{
uint32_t v___x_6644_; 
v___x_6644_ = 0;
v___y_6268_ = v___x_6644_;
goto v___jp_6267_;
}
else
{
uint32_t v___x_6645_; 
v___x_6645_ = 2147483648;
v___y_6268_ = v___x_6645_;
goto v___jp_6267_;
}
}
}
}
}
v___jp_6646_:
{
uint64_t v___x_6655_; uint64_t v___x_6656_; uint8_t v___x_6657_; 
v___x_6655_ = lean_uint32_to_uint64(v___y_6648_);
v___x_6656_ = 0ULL;
v___x_6657_ = lean_uint64_dec_eq(v___x_6655_, v___x_6656_);
if (v___x_6657_ == 0)
{
uint64_t v___x_6658_; uint64_t v___x_6659_; 
v___x_6658_ = 1ULL;
v___x_6659_ = lean_uint64_sub(v___x_6655_, v___x_6658_);
v___y_6606_ = v___y_6647_;
v___y_6607_ = v___y_6649_;
v___y_6608_ = v___y_6654_;
v___y_6609_ = v___y_6650_;
v___y_6610_ = v___y_6651_;
v___y_6611_ = v___y_6652_;
v___y_6612_ = v___y_6653_;
v___y_6613_ = v___x_6659_;
goto v___jp_6605_;
}
else
{
v___y_6606_ = v___y_6647_;
v___y_6607_ = v___y_6649_;
v___y_6608_ = v___y_6654_;
v___y_6609_ = v___y_6650_;
v___y_6610_ = v___y_6651_;
v___y_6611_ = v___y_6652_;
v___y_6612_ = v___y_6653_;
v___y_6613_ = v___x_6656_;
goto v___jp_6605_;
}
}
v___jp_6660_:
{
uint64_t v___x_6669_; uint64_t v___x_6670_; uint8_t v___x_6671_; 
v___x_6669_ = lean_uint32_to_uint64(v___y_6667_);
v___x_6670_ = 0ULL;
v___x_6671_ = lean_uint64_dec_eq(v___x_6669_, v___x_6670_);
if (v___x_6671_ == 0)
{
uint64_t v___x_6672_; uint64_t v___x_6673_; 
v___x_6672_ = 1ULL;
v___x_6673_ = lean_uint64_sub(v___x_6669_, v___x_6672_);
v___y_6647_ = v___y_6661_;
v___y_6648_ = v___y_6663_;
v___y_6649_ = v___y_6662_;
v___y_6650_ = v___y_6664_;
v___y_6651_ = v___y_6665_;
v___y_6652_ = v___y_6666_;
v___y_6653_ = v___y_6668_;
v___y_6654_ = v___x_6673_;
goto v___jp_6646_;
}
else
{
v___y_6647_ = v___y_6661_;
v___y_6648_ = v___y_6663_;
v___y_6649_ = v___y_6662_;
v___y_6650_ = v___y_6664_;
v___y_6651_ = v___y_6665_;
v___y_6652_ = v___y_6666_;
v___y_6653_ = v___y_6668_;
v___y_6654_ = v___x_6670_;
goto v___jp_6646_;
}
}
v___jp_6674_:
{
uint32_t v___x_6683_; uint8_t v___x_6684_; 
v___x_6683_ = 0;
v___x_6684_ = lean_uint32_dec_eq(v___y_6676_, v___x_6683_);
if (v___x_6684_ == 0)
{
uint64_t v___x_6685_; uint64_t v___x_6686_; uint64_t v___x_6687_; 
v___x_6685_ = lean_uint32_to_uint64(v___y_6680_);
v___x_6686_ = 8388608ULL;
v___x_6687_ = lean_uint64_lor(v___x_6685_, v___x_6686_);
v___y_6661_ = v___y_6675_;
v___y_6662_ = v___y_6677_;
v___y_6663_ = v___y_6676_;
v___y_6664_ = v___y_6678_;
v___y_6665_ = v___y_6679_;
v___y_6666_ = v___y_6682_;
v___y_6667_ = v___y_6681_;
v___y_6668_ = v___x_6687_;
goto v___jp_6660_;
}
else
{
uint64_t v___x_6688_; 
v___x_6688_ = lean_uint32_to_uint64(v___y_6680_);
v___y_6661_ = v___y_6675_;
v___y_6662_ = v___y_6677_;
v___y_6663_ = v___y_6676_;
v___y_6664_ = v___y_6678_;
v___y_6665_ = v___y_6679_;
v___y_6666_ = v___y_6682_;
v___y_6667_ = v___y_6681_;
v___y_6668_ = v___x_6688_;
goto v___jp_6660_;
}
}
v___jp_6689_:
{
uint32_t v___x_6697_; uint32_t v_xFraction_6698_; uint32_t v_yFraction_6699_; uint32_t v___x_6700_; uint8_t v___x_6701_; 
v___x_6697_ = 8388607;
v_xFraction_6698_ = lean_uint32_land(v___y_6690_, v___x_6697_);
v_yFraction_6699_ = lean_uint32_land(v___y_6695_, v___x_6697_);
v___x_6700_ = 0;
v___x_6701_ = lean_uint32_dec_eq(v___y_6694_, v___x_6700_);
if (v___x_6701_ == 0)
{
uint64_t v___x_6702_; uint64_t v___x_6703_; uint64_t v___x_6704_; 
v___x_6702_ = lean_uint32_to_uint64(v_xFraction_6698_);
v___x_6703_ = 8388608ULL;
v___x_6704_ = lean_uint64_lor(v___x_6702_, v___x_6703_);
v___y_6675_ = v___y_6691_;
v___y_6676_ = v___y_6693_;
v___y_6677_ = v___y_6692_;
v___y_6678_ = v___y_6696_;
v___y_6679_ = v___x_6697_;
v___y_6680_ = v_yFraction_6699_;
v___y_6681_ = v___y_6694_;
v___y_6682_ = v___x_6704_;
goto v___jp_6674_;
}
else
{
uint64_t v___x_6705_; 
v___x_6705_ = lean_uint32_to_uint64(v_xFraction_6698_);
v___y_6675_ = v___y_6691_;
v___y_6676_ = v___y_6693_;
v___y_6677_ = v___y_6692_;
v___y_6678_ = v___y_6696_;
v___y_6679_ = v___x_6697_;
v___y_6680_ = v_yFraction_6699_;
v___y_6681_ = v___y_6694_;
v___y_6682_ = v___x_6705_;
goto v___jp_6674_;
}
}
v___jp_6706_:
{
float v___x_6709_; float v___x_6710_; float v___x_6711_; uint32_t v___x_6712_; 
v___x_6709_ = lean_float32_of_bits(v___y_6707_);
v___x_6710_ = lean_float32_of_bits(v___y_6708_);
v___x_6711_ = lean_float32_mul(v___x_6709_, v___x_6710_);
v___x_6712_ = lean_float32_to_bits(v___x_6711_);
v___y_6268_ = v___x_6712_;
goto v___jp_6267_;
}
v___jp_6713_:
{
if (v___y_6719_ == 0)
{
uint32_t v___x_6720_; 
v___x_6720_ = lp_competition_Submission_FastMul_mul(v___y_6714_, v___y_6717_);
v___y_6268_ = v___x_6720_;
goto v___jp_6267_;
}
else
{
uint8_t v___x_6721_; 
v___x_6721_ = lean_uint32_dec_eq(v___y_6716_, v___y_6715_);
if (v___x_6721_ == 0)
{
v___y_6707_ = v___y_6714_;
v___y_6708_ = v___y_6717_;
goto v___jp_6706_;
}
else
{
if (v___y_6718_ == 0)
{
uint32_t v___x_6722_; 
v___x_6722_ = lp_competition_Submission_FastMul_mul(v___y_6714_, v___y_6717_);
v___y_6268_ = v___x_6722_;
goto v___jp_6267_;
}
else
{
v___y_6707_ = v___y_6714_;
v___y_6708_ = v___y_6717_;
goto v___jp_6706_;
}
}
}
}
v___jp_6723_:
{
if (v___y_6731_ == 0)
{
v___y_6690_ = v___y_6724_;
v___y_6691_ = v___y_6725_;
v___y_6692_ = v___y_6727_;
v___y_6693_ = v___y_6726_;
v___y_6694_ = v___y_6730_;
v___y_6695_ = v___y_6729_;
v___y_6696_ = v___x_6224_;
goto v___jp_6689_;
}
else
{
v___y_6690_ = v___y_6724_;
v___y_6691_ = v___y_6725_;
v___y_6692_ = v___y_6727_;
v___y_6693_ = v___y_6726_;
v___y_6694_ = v___y_6730_;
v___y_6695_ = v___y_6729_;
v___y_6696_ = v___y_6728_;
goto v___jp_6689_;
}
}
v___jp_6732_:
{
if (v___y_6734_ == 0)
{
if (v___y_6741_ == 0)
{
v___y_6724_ = v___y_6733_;
v___y_6725_ = v___y_6735_;
v___y_6726_ = v___y_6737_;
v___y_6727_ = v___y_6736_;
v___y_6728_ = v___y_6738_;
v___y_6729_ = v___y_6740_;
v___y_6730_ = v___y_6739_;
v___y_6731_ = v___x_6224_;
goto v___jp_6723_;
}
else
{
v___y_6690_ = v___y_6733_;
v___y_6691_ = v___y_6735_;
v___y_6692_ = v___y_6736_;
v___y_6693_ = v___y_6737_;
v___y_6694_ = v___y_6739_;
v___y_6695_ = v___y_6740_;
v___y_6696_ = v___x_6224_;
goto v___jp_6689_;
}
}
else
{
v___y_6724_ = v___y_6733_;
v___y_6725_ = v___y_6735_;
v___y_6726_ = v___y_6737_;
v___y_6727_ = v___y_6736_;
v___y_6728_ = v___y_6738_;
v___y_6729_ = v___y_6740_;
v___y_6730_ = v___y_6739_;
v___y_6731_ = v___y_6741_;
goto v___jp_6723_;
}
}
v___jp_6742_:
{
uint32_t v___x_6751_; uint32_t v___x_6752_; uint32_t v___x_6753_; uint8_t v___x_6754_; 
v___x_6751_ = 2147483648;
v___x_6752_ = lean_uint32_land(v___y_6748_, v___x_6751_);
v___x_6753_ = 0;
v___x_6754_ = lean_uint32_dec_eq(v___x_6752_, v___x_6753_);
if (v___x_6754_ == 0)
{
v___y_6733_ = v___y_6743_;
v___y_6734_ = v___y_6750_;
v___y_6735_ = v___y_6744_;
v___y_6736_ = v___y_6746_;
v___y_6737_ = v___y_6745_;
v___y_6738_ = v___y_6747_;
v___y_6739_ = v___y_6749_;
v___y_6740_ = v___y_6748_;
v___y_6741_ = v___x_6224_;
goto v___jp_6732_;
}
else
{
v___y_6733_ = v___y_6743_;
v___y_6734_ = v___y_6750_;
v___y_6735_ = v___y_6744_;
v___y_6736_ = v___y_6746_;
v___y_6737_ = v___y_6745_;
v___y_6738_ = v___y_6747_;
v___y_6739_ = v___y_6749_;
v___y_6740_ = v___y_6748_;
v___y_6741_ = v___y_6747_;
goto v___jp_6732_;
}
}
v___jp_6755_:
{
if (v___y_6762_ == 0)
{
uint32_t v___x_6763_; uint32_t v___x_6764_; uint32_t v___x_6765_; uint8_t v___x_6766_; 
v___x_6763_ = 2147483648;
v___x_6764_ = lean_uint32_land(v___y_6756_, v___x_6763_);
v___x_6765_ = 0;
v___x_6766_ = lean_uint32_dec_eq(v___x_6764_, v___x_6765_);
if (v___x_6766_ == 0)
{
v___y_6743_ = v___y_6756_;
v___y_6744_ = v___y_6757_;
v___y_6745_ = v___y_6759_;
v___y_6746_ = v___y_6758_;
v___y_6747_ = v___y_6762_;
v___y_6748_ = v___y_6761_;
v___y_6749_ = v___y_6760_;
v___y_6750_ = v___x_6224_;
goto v___jp_6742_;
}
else
{
v___y_6743_ = v___y_6756_;
v___y_6744_ = v___y_6757_;
v___y_6745_ = v___y_6759_;
v___y_6746_ = v___y_6758_;
v___y_6747_ = v___y_6762_;
v___y_6748_ = v___y_6761_;
v___y_6749_ = v___y_6760_;
v___y_6750_ = v___y_6762_;
goto v___jp_6742_;
}
}
else
{
lean_object* v___x_6767_; lean_object* v___x_6768_; lean_object* v___x_6769_; uint32_t v___x_6770_; 
v___x_6767_ = lean_uint32_to_nat(v___y_6756_);
v___x_6768_ = lean_uint32_to_nat(v___y_6761_);
v___x_6769_ = lp_floatlib_FloatLib_Floats_Formats_BinaryInterchange_Model_MulBackend_word___at___00FloatLib_Floats_Formats_BinaryInterchange_Configured_Plan_softwareMul32Certified_spec__1(v___x_6767_, v___x_6768_);
v___x_6770_ = lean_uint32_of_nat(v___x_6769_);
lean_dec(v___x_6769_);
v___y_6268_ = v___x_6770_;
goto v___jp_6267_;
}
}
v___jp_6771_:
{
uint32_t v___x_6774_; uint32_t v___x_6775_; uint32_t v___x_6776_; uint32_t v_ex_6777_; uint32_t v___x_6778_; uint32_t v_ey_6779_; uint32_t v___x_6780_; uint32_t v___x_6781_; uint8_t v___x_6782_; 
v___x_6774_ = 23;
v___x_6775_ = lean_uint32_shift_right(v___y_6772_, v___x_6774_);
v___x_6776_ = 255;
v_ex_6777_ = lean_uint32_land(v___x_6775_, v___x_6776_);
v___x_6778_ = lean_uint32_shift_right(v___y_6773_, v___x_6774_);
v_ey_6779_ = lean_uint32_land(v___x_6778_, v___x_6776_);
v___x_6780_ = lean_uint32_add(v_ex_6777_, v_ey_6779_);
v___x_6781_ = 128;
v___x_6782_ = lean_uint32_dec_lt(v___x_6780_, v___x_6781_);
if (v___x_6782_ == 0)
{
uint8_t v___x_6783_; 
v___x_6783_ = lean_uint32_dec_eq(v_ex_6777_, v___x_6776_);
if (v___x_6783_ == 0)
{
v___y_6714_ = v___y_6772_;
v___y_6715_ = v___x_6776_;
v___y_6716_ = v_ey_6779_;
v___y_6717_ = v___y_6773_;
v___y_6718_ = v___x_6782_;
v___y_6719_ = v___x_6224_;
goto v___jp_6713_;
}
else
{
v___y_6714_ = v___y_6772_;
v___y_6715_ = v___x_6776_;
v___y_6716_ = v_ey_6779_;
v___y_6717_ = v___y_6773_;
v___y_6718_ = v___x_6782_;
v___y_6719_ = v___x_6782_;
goto v___jp_6713_;
}
}
else
{
uint32_t v___x_6784_; uint32_t v___x_6785_; uint32_t v___x_6786_; uint8_t v___x_6787_; 
v___x_6784_ = 4278190080;
v___x_6785_ = 1;
v___x_6786_ = lean_uint32_shift_left(v___y_6772_, v___x_6785_);
v___x_6787_ = lean_uint32_dec_le(v___x_6784_, v___x_6786_);
if (v___x_6787_ == 0)
{
uint32_t v___x_6788_; uint8_t v___x_6789_; 
v___x_6788_ = lean_uint32_shift_left(v___y_6773_, v___x_6785_);
v___x_6789_ = lean_uint32_dec_le(v___x_6784_, v___x_6788_);
v___y_6756_ = v___y_6772_;
v___y_6757_ = v___x_6776_;
v___y_6758_ = v___x_6774_;
v___y_6759_ = v_ey_6779_;
v___y_6760_ = v_ex_6777_;
v___y_6761_ = v___y_6773_;
v___y_6762_ = v___x_6789_;
goto v___jp_6755_;
}
else
{
v___y_6756_ = v___y_6772_;
v___y_6757_ = v___x_6776_;
v___y_6758_ = v___x_6774_;
v___y_6759_ = v_ey_6779_;
v___y_6760_ = v_ex_6777_;
v___y_6761_ = v___y_6773_;
v___y_6762_ = v___x_6787_;
goto v___jp_6755_;
}
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_Fin_foldl_loop___at___00Submission_NativeFinal_dot_spec__0___boxed(lean_object* v_baseA_6804_, lean_object* v_p_6805_, lean_object* v_baseB_6806_, lean_object* v_B_6807_, lean_object* v_A_6808_, lean_object* v_n_6809_, lean_object* v_x_6810_, lean_object* v_i_6811_){
_start:
{
uint32_t v_x_boxed_6812_; uint32_t v_res_6813_; lean_object* v_r_6814_; 
v_x_boxed_6812_ = lean_unbox_uint32(v_x_6810_);
lean_dec(v_x_6810_);
v_res_6813_ = lp_competition_Fin_foldl_loop___at___00Submission_NativeFinal_dot_spec__0(v_baseA_6804_, v_p_6805_, v_baseB_6806_, v_B_6807_, v_A_6808_, v_n_6809_, v_x_boxed_6812_, v_i_6811_);
lean_dec(v_n_6809_);
lean_dec_ref(v_A_6808_);
lean_dec_ref(v_B_6807_);
lean_dec(v_baseB_6806_);
lean_dec(v_p_6805_);
lean_dec(v_baseA_6804_);
v_r_6814_ = lean_box_uint32(v_res_6813_);
return v_r_6814_;
}
}
static float _init_lp_competition_Submission_NativeFinal_dot___closed__0(void){
_start:
{
uint32_t v___x_6815_; float v___x_6816_; 
v___x_6815_ = 0;
v___x_6816_ = lean_float32_of_bits(v___x_6815_);
return v___x_6816_;
}
}
LEAN_EXPORT uint32_t lp_competition_Submission_NativeFinal_dot(lean_object* v_n_6817_, lean_object* v_baseA_6818_, lean_object* v_baseB_6819_, lean_object* v_p_6820_, lean_object* v_A_6821_, lean_object* v_B_6822_){
_start:
{
lean_object* v___x_6823_; float v___x_6824_; float v_result_6825_; uint8_t v___x_6826_; 
v___x_6823_ = lean_unsigned_to_nat(0u);
v___x_6824_ = lean_float32_once(&lp_competition_Submission_NativeFinal_dot___closed__0, &lp_competition_Submission_NativeFinal_dot___closed__0_once, _init_lp_competition_Submission_NativeFinal_dot___closed__0);
v_result_6825_ = lp_competition_Submission_NativeFinal_dotLoop(v_n_6817_, v_baseA_6818_, v_baseB_6819_, v_p_6820_, v_A_6821_, v_B_6822_, v___x_6823_, v___x_6824_);
v___x_6826_ = lean_float32_isfinite(v_result_6825_);
if (v___x_6826_ == 0)
{
uint32_t v___x_6827_; uint32_t v___x_6828_; 
v___x_6827_ = lean_uint32_once(&lp_competition_Submission_referenceSum___redArg___closed__1, &lp_competition_Submission_referenceSum___redArg___closed__1_once, _init_lp_competition_Submission_referenceSum___redArg___closed__1);
v___x_6828_ = lp_competition_Fin_foldl_loop___at___00Submission_NativeFinal_dot_spec__0(v_baseA_6818_, v_p_6820_, v_baseB_6819_, v_B_6822_, v_A_6821_, v_n_6817_, v___x_6827_, v___x_6823_);
return v___x_6828_;
}
else
{
uint32_t v___x_6829_; 
v___x_6829_ = lean_float32_to_bits(v_result_6825_);
return v___x_6829_;
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_NativeFinal_dot___boxed(lean_object* v_n_6830_, lean_object* v_baseA_6831_, lean_object* v_baseB_6832_, lean_object* v_p_6833_, lean_object* v_A_6834_, lean_object* v_B_6835_){
_start:
{
uint32_t v_res_6836_; lean_object* v_r_6837_; 
v_res_6836_ = lp_competition_Submission_NativeFinal_dot(v_n_6830_, v_baseA_6831_, v_baseB_6832_, v_p_6833_, v_A_6834_, v_B_6835_);
lean_dec_ref(v_B_6835_);
lean_dec_ref(v_A_6834_);
lean_dec(v_p_6833_);
lean_dec(v_baseB_6832_);
lean_dec(v_baseA_6831_);
lean_dec(v_n_6830_);
v_r_6837_ = lean_box_uint32(v_res_6836_);
return v_r_6837_;
}
}
LEAN_EXPORT uint32_t lp_competition_Submission_originalSum(lean_object* v_n_6838_, lean_object* v_x_6839_){
_start:
{
lean_object* v___x_6840_; float v___x_6841_; float v_result_6842_; uint8_t v___x_6843_; 
v___x_6840_ = lean_unsigned_to_nat(0u);
v___x_6841_ = lean_float32_once(&lp_competition_Submission_NativeFinal_dot___closed__0, &lp_competition_Submission_NativeFinal_dot___closed__0_once, _init_lp_competition_Submission_NativeFinal_dot___closed__0);
v_result_6842_ = lp_competition_Submission_NativeFinal_sumLoop(v_n_6838_, v_x_6839_, v___x_6840_, v___x_6841_);
v___x_6843_ = lean_float32_isfinite(v_result_6842_);
if (v___x_6843_ == 0)
{
uint32_t v___x_6844_; 
v___x_6844_ = lp_competition_Submission_referenceSum___redArg(v_x_6839_);
return v___x_6844_;
}
else
{
uint32_t v___x_6845_; 
v___x_6845_ = lean_float32_to_bits(v_result_6842_);
return v___x_6845_;
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_originalSum___boxed(lean_object* v_n_6846_, lean_object* v_x_6847_){
_start:
{
uint32_t v_res_6848_; lean_object* v_r_6849_; 
v_res_6848_ = lp_competition_Submission_originalSum(v_n_6846_, v_x_6847_);
lean_dec_ref(v_x_6847_);
lean_dec(v_n_6846_);
v_r_6849_ = lean_box_uint32(v_res_6848_);
return v_r_6849_;
}
}
static float _init_lp_competition_Submission_Packed10_zero32(void){
_start:
{
float v___x_6850_; 
v___x_6850_ = lean_float32_once(&lp_competition_Submission_NativeFinal_dot___closed__0, &lp_competition_Submission_NativeFinal_dot___closed__0_once, _init_lp_competition_Submission_NativeFinal_dot___closed__0);
return v___x_6850_;
}
}
static lean_object* _init_lp_competition_Submission_Packed10_zero10___closed__0(void){
_start:
{
float v___x_6851_; lean_object* v___x_6852_; 
v___x_6851_ = lean_float32_once(&lp_competition_Submission_NativeFinal_dot___closed__0, &lp_competition_Submission_NativeFinal_dot___closed__0_once, _init_lp_competition_Submission_NativeFinal_dot___closed__0);
v___x_6852_ = lean_alloc_ctor(0, 0, 40);
lean_ctor_set_float32(v___x_6852_, 0, v___x_6851_);
lean_ctor_set_float32(v___x_6852_, 4, v___x_6851_);
lean_ctor_set_float32(v___x_6852_, 8, v___x_6851_);
lean_ctor_set_float32(v___x_6852_, 12, v___x_6851_);
lean_ctor_set_float32(v___x_6852_, 16, v___x_6851_);
lean_ctor_set_float32(v___x_6852_, 20, v___x_6851_);
lean_ctor_set_float32(v___x_6852_, 24, v___x_6851_);
lean_ctor_set_float32(v___x_6852_, 28, v___x_6851_);
lean_ctor_set_float32(v___x_6852_, 32, v___x_6851_);
lean_ctor_set_float32(v___x_6852_, 36, v___x_6851_);
return v___x_6852_;
}
}
static lean_object* _init_lp_competition_Submission_Packed10_zero10(void){
_start:
{
lean_object* v___x_6853_; 
v___x_6853_ = lean_obj_once(&lp_competition_Submission_Packed10_zero10___closed__0, &lp_competition_Submission_Packed10_zero10___closed__0_once, _init_lp_competition_Submission_Packed10_zero10___closed__0);
return v___x_6853_;
}
}
LEAN_EXPORT float lp_competition_Submission_Packed10_lane(lean_object* v_v_6854_, lean_object* v_l_6855_){
_start:
{
lean_object* v___x_6856_; uint8_t v___x_6857_; 
v___x_6856_ = lean_unsigned_to_nat(0u);
v___x_6857_ = lean_nat_dec_eq(v_l_6855_, v___x_6856_);
if (v___x_6857_ == 0)
{
lean_object* v___x_6858_; uint8_t v___x_6859_; 
v___x_6858_ = lean_unsigned_to_nat(1u);
v___x_6859_ = lean_nat_dec_eq(v_l_6855_, v___x_6858_);
if (v___x_6859_ == 0)
{
lean_object* v___x_6860_; uint8_t v___x_6861_; 
v___x_6860_ = lean_unsigned_to_nat(2u);
v___x_6861_ = lean_nat_dec_eq(v_l_6855_, v___x_6860_);
if (v___x_6861_ == 0)
{
lean_object* v___x_6862_; uint8_t v___x_6863_; 
v___x_6862_ = lean_unsigned_to_nat(3u);
v___x_6863_ = lean_nat_dec_eq(v_l_6855_, v___x_6862_);
if (v___x_6863_ == 0)
{
lean_object* v___x_6864_; uint8_t v___x_6865_; 
v___x_6864_ = lean_unsigned_to_nat(4u);
v___x_6865_ = lean_nat_dec_eq(v_l_6855_, v___x_6864_);
if (v___x_6865_ == 0)
{
lean_object* v___x_6866_; uint8_t v___x_6867_; 
v___x_6866_ = lean_unsigned_to_nat(5u);
v___x_6867_ = lean_nat_dec_eq(v_l_6855_, v___x_6866_);
if (v___x_6867_ == 0)
{
lean_object* v___x_6868_; uint8_t v___x_6869_; 
v___x_6868_ = lean_unsigned_to_nat(6u);
v___x_6869_ = lean_nat_dec_eq(v_l_6855_, v___x_6868_);
if (v___x_6869_ == 0)
{
lean_object* v___x_6870_; uint8_t v___x_6871_; 
v___x_6870_ = lean_unsigned_to_nat(7u);
v___x_6871_ = lean_nat_dec_eq(v_l_6855_, v___x_6870_);
if (v___x_6871_ == 0)
{
lean_object* v___x_6872_; uint8_t v___x_6873_; 
v___x_6872_ = lean_unsigned_to_nat(8u);
v___x_6873_ = lean_nat_dec_eq(v_l_6855_, v___x_6872_);
if (v___x_6873_ == 0)
{
float v_s9_6874_; 
v_s9_6874_ = lean_ctor_get_float32(v_v_6854_, 36);
return v_s9_6874_;
}
else
{
float v_s8_6875_; 
v_s8_6875_ = lean_ctor_get_float32(v_v_6854_, 32);
return v_s8_6875_;
}
}
else
{
float v_s7_6876_; 
v_s7_6876_ = lean_ctor_get_float32(v_v_6854_, 28);
return v_s7_6876_;
}
}
else
{
float v_s6_6877_; 
v_s6_6877_ = lean_ctor_get_float32(v_v_6854_, 24);
return v_s6_6877_;
}
}
else
{
float v_s5_6878_; 
v_s5_6878_ = lean_ctor_get_float32(v_v_6854_, 20);
return v_s5_6878_;
}
}
else
{
float v_s4_6879_; 
v_s4_6879_ = lean_ctor_get_float32(v_v_6854_, 16);
return v_s4_6879_;
}
}
else
{
float v_s3_6880_; 
v_s3_6880_ = lean_ctor_get_float32(v_v_6854_, 12);
return v_s3_6880_;
}
}
else
{
float v_s2_6881_; 
v_s2_6881_ = lean_ctor_get_float32(v_v_6854_, 8);
return v_s2_6881_;
}
}
else
{
float v_s1_6882_; 
v_s1_6882_ = lean_ctor_get_float32(v_v_6854_, 4);
return v_s1_6882_;
}
}
else
{
float v_s0_6883_; 
v_s0_6883_ = lean_ctor_get_float32(v_v_6854_, 0);
return v_s0_6883_;
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_Packed10_lane___boxed(lean_object* v_v_6884_, lean_object* v_l_6885_){
_start:
{
float v_res_6886_; lean_object* v_r_6887_; 
v_res_6886_ = lp_competition_Submission_Packed10_lane(v_v_6884_, v_l_6885_);
lean_dec(v_l_6885_);
lean_dec_ref(v_v_6884_);
v_r_6887_ = lean_box_float32(v_res_6886_);
return v_r_6887_;
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_Packed10_packet(lean_object* v_read_6888_, lean_object* v_col_6889_){
_start:
{
lean_object* v___x_6890_; lean_object* v___x_6891_; lean_object* v___x_6892_; lean_object* v___x_6893_; lean_object* v___x_6894_; lean_object* v___x_6895_; lean_object* v___x_6896_; lean_object* v___x_6897_; lean_object* v___x_6898_; lean_object* v___x_6899_; lean_object* v___x_6900_; lean_object* v___x_6901_; lean_object* v___x_6902_; lean_object* v___x_6903_; lean_object* v___x_6904_; lean_object* v___x_6905_; lean_object* v___x_6906_; lean_object* v___x_6907_; lean_object* v___x_6908_; lean_object* v___x_6909_; lean_object* v___x_6910_; lean_object* v___x_6911_; lean_object* v___x_6912_; lean_object* v___x_6913_; lean_object* v___x_6914_; lean_object* v___x_6915_; lean_object* v___x_6916_; lean_object* v___x_6917_; lean_object* v___x_6918_; float v___x_6919_; float v___x_6920_; float v___x_6921_; float v___x_6922_; float v___x_6923_; float v___x_6924_; float v___x_6925_; float v___x_6926_; float v___x_6927_; float v___x_6928_; 
lean_inc_ref_n(v_read_6888_, 9);
lean_inc(v_col_6889_);
v___x_6890_ = lean_apply_1(v_read_6888_, v_col_6889_);
v___x_6891_ = lean_unsigned_to_nat(1u);
v___x_6892_ = lean_nat_add(v_col_6889_, v___x_6891_);
v___x_6893_ = lean_apply_1(v_read_6888_, v___x_6892_);
v___x_6894_ = lean_unsigned_to_nat(2u);
v___x_6895_ = lean_nat_add(v_col_6889_, v___x_6894_);
v___x_6896_ = lean_apply_1(v_read_6888_, v___x_6895_);
v___x_6897_ = lean_unsigned_to_nat(3u);
v___x_6898_ = lean_nat_add(v_col_6889_, v___x_6897_);
v___x_6899_ = lean_apply_1(v_read_6888_, v___x_6898_);
v___x_6900_ = lean_unsigned_to_nat(4u);
v___x_6901_ = lean_nat_add(v_col_6889_, v___x_6900_);
v___x_6902_ = lean_apply_1(v_read_6888_, v___x_6901_);
v___x_6903_ = lean_unsigned_to_nat(5u);
v___x_6904_ = lean_nat_add(v_col_6889_, v___x_6903_);
v___x_6905_ = lean_apply_1(v_read_6888_, v___x_6904_);
v___x_6906_ = lean_unsigned_to_nat(6u);
v___x_6907_ = lean_nat_add(v_col_6889_, v___x_6906_);
v___x_6908_ = lean_apply_1(v_read_6888_, v___x_6907_);
v___x_6909_ = lean_unsigned_to_nat(7u);
v___x_6910_ = lean_nat_add(v_col_6889_, v___x_6909_);
v___x_6911_ = lean_apply_1(v_read_6888_, v___x_6910_);
v___x_6912_ = lean_unsigned_to_nat(8u);
v___x_6913_ = lean_nat_add(v_col_6889_, v___x_6912_);
v___x_6914_ = lean_apply_1(v_read_6888_, v___x_6913_);
v___x_6915_ = lean_unsigned_to_nat(9u);
v___x_6916_ = lean_nat_add(v_col_6889_, v___x_6915_);
lean_dec(v_col_6889_);
v___x_6917_ = lean_apply_1(v_read_6888_, v___x_6916_);
v___x_6918_ = lean_alloc_ctor(0, 0, 40);
v___x_6919_ = lean_unbox_float32(v___x_6890_);
lean_dec_ref(v___x_6890_);
lean_ctor_set_float32(v___x_6918_, 0, v___x_6919_);
v___x_6920_ = lean_unbox_float32(v___x_6893_);
lean_dec_ref(v___x_6893_);
lean_ctor_set_float32(v___x_6918_, 4, v___x_6920_);
v___x_6921_ = lean_unbox_float32(v___x_6896_);
lean_dec_ref(v___x_6896_);
lean_ctor_set_float32(v___x_6918_, 8, v___x_6921_);
v___x_6922_ = lean_unbox_float32(v___x_6899_);
lean_dec_ref(v___x_6899_);
lean_ctor_set_float32(v___x_6918_, 12, v___x_6922_);
v___x_6923_ = lean_unbox_float32(v___x_6902_);
lean_dec_ref(v___x_6902_);
lean_ctor_set_float32(v___x_6918_, 16, v___x_6923_);
v___x_6924_ = lean_unbox_float32(v___x_6905_);
lean_dec_ref(v___x_6905_);
lean_ctor_set_float32(v___x_6918_, 20, v___x_6924_);
v___x_6925_ = lean_unbox_float32(v___x_6908_);
lean_dec_ref(v___x_6908_);
lean_ctor_set_float32(v___x_6918_, 24, v___x_6925_);
v___x_6926_ = lean_unbox_float32(v___x_6911_);
lean_dec_ref(v___x_6911_);
lean_ctor_set_float32(v___x_6918_, 28, v___x_6926_);
v___x_6927_ = lean_unbox_float32(v___x_6914_);
lean_dec_ref(v___x_6914_);
lean_ctor_set_float32(v___x_6918_, 32, v___x_6927_);
v___x_6928_ = lean_unbox_float32(v___x_6917_);
lean_dec_ref(v___x_6917_);
lean_ctor_set_float32(v___x_6918_, 36, v___x_6928_);
return v___x_6918_;
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_Packed10_update(lean_object* v_acc_6929_, float v_a_6930_, lean_object* v_v_6931_){
_start:
{
float v_s0_6932_; float v_s1_6933_; float v_s2_6934_; float v_s3_6935_; float v_s4_6936_; float v_s5_6937_; float v_s6_6938_; float v_s7_6939_; float v_s8_6940_; float v_s9_6941_; float v_s0_6942_; float v_s1_6943_; float v_s2_6944_; float v_s3_6945_; float v_s4_6946_; float v_s5_6947_; float v_s6_6948_; float v_s7_6949_; float v_s8_6950_; float v_s9_6951_; lean_object* v___x_6953_; uint8_t v_isShared_6954_; uint8_t v_isSharedCheck_6978_; 
v_s0_6932_ = lean_ctor_get_float32(v_acc_6929_, 0);
v_s1_6933_ = lean_ctor_get_float32(v_acc_6929_, 4);
v_s2_6934_ = lean_ctor_get_float32(v_acc_6929_, 8);
v_s3_6935_ = lean_ctor_get_float32(v_acc_6929_, 12);
v_s4_6936_ = lean_ctor_get_float32(v_acc_6929_, 16);
v_s5_6937_ = lean_ctor_get_float32(v_acc_6929_, 20);
v_s6_6938_ = lean_ctor_get_float32(v_acc_6929_, 24);
v_s7_6939_ = lean_ctor_get_float32(v_acc_6929_, 28);
v_s8_6940_ = lean_ctor_get_float32(v_acc_6929_, 32);
v_s9_6941_ = lean_ctor_get_float32(v_acc_6929_, 36);
v_s0_6942_ = lean_ctor_get_float32(v_v_6931_, 0);
v_s1_6943_ = lean_ctor_get_float32(v_v_6931_, 4);
v_s2_6944_ = lean_ctor_get_float32(v_v_6931_, 8);
v_s3_6945_ = lean_ctor_get_float32(v_v_6931_, 12);
v_s4_6946_ = lean_ctor_get_float32(v_v_6931_, 16);
v_s5_6947_ = lean_ctor_get_float32(v_v_6931_, 20);
v_s6_6948_ = lean_ctor_get_float32(v_v_6931_, 24);
v_s7_6949_ = lean_ctor_get_float32(v_v_6931_, 28);
v_s8_6950_ = lean_ctor_get_float32(v_v_6931_, 32);
v_s9_6951_ = lean_ctor_get_float32(v_v_6931_, 36);
v_isSharedCheck_6978_ = !lean_is_exclusive(v_v_6931_);
if (v_isSharedCheck_6978_ == 0)
{
v___x_6953_ = v_v_6931_;
v_isShared_6954_ = v_isSharedCheck_6978_;
goto v_resetjp_6952_;
}
else
{
lean_dec(v_v_6931_);
v___x_6953_ = lean_box(0);
v_isShared_6954_ = v_isSharedCheck_6978_;
goto v_resetjp_6952_;
}
v_resetjp_6952_:
{
float v___x_6955_; float v___x_6956_; float v___x_6957_; float v___x_6958_; float v___x_6959_; float v___x_6960_; float v___x_6961_; float v___x_6962_; float v___x_6963_; float v___x_6964_; float v___x_6965_; float v___x_6966_; float v___x_6967_; float v___x_6968_; float v___x_6969_; float v___x_6970_; float v___x_6971_; float v___x_6972_; float v___x_6973_; float v___x_6974_; lean_object* v___x_6976_; 
v___x_6955_ = lean_float32_mul(v_a_6930_, v_s0_6942_);
v___x_6956_ = lean_float32_add(v_s0_6932_, v___x_6955_);
v___x_6957_ = lean_float32_mul(v_a_6930_, v_s1_6943_);
v___x_6958_ = lean_float32_add(v_s1_6933_, v___x_6957_);
v___x_6959_ = lean_float32_mul(v_a_6930_, v_s2_6944_);
v___x_6960_ = lean_float32_add(v_s2_6934_, v___x_6959_);
v___x_6961_ = lean_float32_mul(v_a_6930_, v_s3_6945_);
v___x_6962_ = lean_float32_add(v_s3_6935_, v___x_6961_);
v___x_6963_ = lean_float32_mul(v_a_6930_, v_s4_6946_);
v___x_6964_ = lean_float32_add(v_s4_6936_, v___x_6963_);
v___x_6965_ = lean_float32_mul(v_a_6930_, v_s5_6947_);
v___x_6966_ = lean_float32_add(v_s5_6937_, v___x_6965_);
v___x_6967_ = lean_float32_mul(v_a_6930_, v_s6_6948_);
v___x_6968_ = lean_float32_add(v_s6_6938_, v___x_6967_);
v___x_6969_ = lean_float32_mul(v_a_6930_, v_s7_6949_);
v___x_6970_ = lean_float32_add(v_s7_6939_, v___x_6969_);
v___x_6971_ = lean_float32_mul(v_a_6930_, v_s8_6950_);
v___x_6972_ = lean_float32_add(v_s8_6940_, v___x_6971_);
v___x_6973_ = lean_float32_mul(v_a_6930_, v_s9_6951_);
v___x_6974_ = lean_float32_add(v_s9_6941_, v___x_6973_);
if (v_isShared_6954_ == 0)
{
v___x_6976_ = v___x_6953_;
goto v_reusejp_6975_;
}
else
{
lean_object* v_reuseFailAlloc_6977_; 
v_reuseFailAlloc_6977_ = lean_alloc_ctor(0, 0, 40);
v___x_6976_ = v_reuseFailAlloc_6977_;
goto v_reusejp_6975_;
}
v_reusejp_6975_:
{
lean_ctor_set_float32(v___x_6976_, 0, v___x_6956_);
lean_ctor_set_float32(v___x_6976_, 4, v___x_6958_);
lean_ctor_set_float32(v___x_6976_, 8, v___x_6960_);
lean_ctor_set_float32(v___x_6976_, 12, v___x_6962_);
lean_ctor_set_float32(v___x_6976_, 16, v___x_6964_);
lean_ctor_set_float32(v___x_6976_, 20, v___x_6966_);
lean_ctor_set_float32(v___x_6976_, 24, v___x_6968_);
lean_ctor_set_float32(v___x_6976_, 28, v___x_6970_);
lean_ctor_set_float32(v___x_6976_, 32, v___x_6972_);
lean_ctor_set_float32(v___x_6976_, 36, v___x_6974_);
return v___x_6976_;
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_Packed10_update___boxed(lean_object* v_acc_6979_, lean_object* v_a_6980_, lean_object* v_v_6981_){
_start:
{
float v_a_boxed_6982_; lean_object* v_res_6983_; 
v_a_boxed_6982_ = lean_unbox_float32(v_a_6980_);
lean_dec_ref(v_a_6980_);
v_res_6983_ = lp_competition_Submission_Packed10_update(v_acc_6979_, v_a_boxed_6982_, v_v_6981_);
lean_dec_ref(v_acc_6979_);
return v_res_6983_;
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_Packed10_groups(lean_object* v_p_6984_){
_start:
{
lean_object* v___x_6985_; lean_object* v___x_6986_; lean_object* v___x_6987_; lean_object* v___x_6988_; 
v___x_6985_ = lean_unsigned_to_nat(9u);
v___x_6986_ = lean_nat_add(v_p_6984_, v___x_6985_);
v___x_6987_ = lean_unsigned_to_nat(10u);
v___x_6988_ = lean_nat_div(v___x_6986_, v___x_6987_);
lean_dec(v___x_6986_);
return v___x_6988_;
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_Packed10_groups___boxed(lean_object* v_p_6989_){
_start:
{
lean_object* v_res_6990_; 
v_res_6990_ = lp_competition_Submission_Packed10_groups(v_p_6989_);
lean_dec(v_p_6989_);
return v_res_6990_;
}
}
LEAN_EXPORT float lp_competition_Submission_Packed10_packB___lam__0(lean_object* v_p_6991_, lean_object* v_base_6992_, lean_object* v_B_6993_, lean_object* v_j_6994_){
_start:
{
uint8_t v___x_6995_; 
v___x_6995_ = lean_nat_dec_lt(v_j_6994_, v_p_6991_);
if (v___x_6995_ == 0)
{
float v___x_6996_; 
v___x_6996_ = lean_float32_once(&lp_competition_Submission_NativeFinal_dot___closed__0, &lp_competition_Submission_NativeFinal_dot___closed__0_once, _init_lp_competition_Submission_NativeFinal_dot___closed__0);
return v___x_6996_;
}
else
{
lean_object* v___x_6997_; lean_object* v___x_6998_; uint32_t v___x_6999_; float v___x_7000_; 
v___x_6997_ = lean_nat_add(v_base_6992_, v_j_6994_);
v___x_6998_ = lean_array_fget_borrowed(v_B_6993_, v___x_6997_);
lean_dec(v___x_6997_);
v___x_6999_ = lean_unbox_uint32(v___x_6998_);
v___x_7000_ = lean_float32_of_bits(v___x_6999_);
return v___x_7000_;
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_Packed10_packB___lam__0___boxed(lean_object* v_p_7001_, lean_object* v_base_7002_, lean_object* v_B_7003_, lean_object* v_j_7004_){
_start:
{
float v_res_7005_; lean_object* v_r_7006_; 
v_res_7005_ = lp_competition_Submission_Packed10_packB___lam__0(v_p_7001_, v_base_7002_, v_B_7003_, v_j_7004_);
lean_dec(v_j_7004_);
lean_dec_ref(v_B_7003_);
lean_dec(v_base_7002_);
lean_dec(v_p_7001_);
v_r_7006_ = lean_box_float32(v_res_7005_);
return v_r_7006_;
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_Packed10_packB___lam__1(lean_object* v_b_7007_, lean_object* v_n_7008_, lean_object* v_p_7009_, lean_object* v_B_7010_, lean_object* v_g_7011_, lean_object* v_k_7012_){
_start:
{
lean_object* v___x_7013_; lean_object* v___x_7014_; lean_object* v_base_7015_; lean_object* v___x_7016_; lean_object* v___x_7017_; float v___x_7018_; lean_object* v___x_7019_; lean_object* v___x_7020_; float v___x_7021_; lean_object* v___x_7022_; lean_object* v___x_7023_; float v___x_7024_; lean_object* v___x_7025_; lean_object* v___x_7026_; float v___x_7027_; lean_object* v___x_7028_; lean_object* v___x_7029_; float v___x_7030_; lean_object* v___x_7031_; lean_object* v___x_7032_; float v___x_7033_; lean_object* v___x_7034_; lean_object* v___x_7035_; float v___x_7036_; lean_object* v___x_7037_; lean_object* v___x_7038_; float v___x_7039_; lean_object* v___x_7040_; lean_object* v___x_7041_; float v___x_7042_; lean_object* v___x_7043_; lean_object* v___x_7044_; float v___x_7045_; lean_object* v___x_7046_; 
v___x_7013_ = lean_nat_mul(v_b_7007_, v_n_7008_);
v___x_7014_ = lean_nat_add(v___x_7013_, v_k_7012_);
lean_dec(v___x_7013_);
v_base_7015_ = lean_nat_mul(v___x_7014_, v_p_7009_);
lean_dec(v___x_7014_);
v___x_7016_ = lean_unsigned_to_nat(10u);
v___x_7017_ = lean_nat_mul(v___x_7016_, v_g_7011_);
v___x_7018_ = lp_competition_Submission_Packed10_packB___lam__0(v_p_7009_, v_base_7015_, v_B_7010_, v___x_7017_);
v___x_7019_ = lean_unsigned_to_nat(1u);
v___x_7020_ = lean_nat_add(v___x_7017_, v___x_7019_);
v___x_7021_ = lp_competition_Submission_Packed10_packB___lam__0(v_p_7009_, v_base_7015_, v_B_7010_, v___x_7020_);
lean_dec(v___x_7020_);
v___x_7022_ = lean_unsigned_to_nat(2u);
v___x_7023_ = lean_nat_add(v___x_7017_, v___x_7022_);
v___x_7024_ = lp_competition_Submission_Packed10_packB___lam__0(v_p_7009_, v_base_7015_, v_B_7010_, v___x_7023_);
lean_dec(v___x_7023_);
v___x_7025_ = lean_unsigned_to_nat(3u);
v___x_7026_ = lean_nat_add(v___x_7017_, v___x_7025_);
v___x_7027_ = lp_competition_Submission_Packed10_packB___lam__0(v_p_7009_, v_base_7015_, v_B_7010_, v___x_7026_);
lean_dec(v___x_7026_);
v___x_7028_ = lean_unsigned_to_nat(4u);
v___x_7029_ = lean_nat_add(v___x_7017_, v___x_7028_);
v___x_7030_ = lp_competition_Submission_Packed10_packB___lam__0(v_p_7009_, v_base_7015_, v_B_7010_, v___x_7029_);
lean_dec(v___x_7029_);
v___x_7031_ = lean_unsigned_to_nat(5u);
v___x_7032_ = lean_nat_add(v___x_7017_, v___x_7031_);
v___x_7033_ = lp_competition_Submission_Packed10_packB___lam__0(v_p_7009_, v_base_7015_, v_B_7010_, v___x_7032_);
lean_dec(v___x_7032_);
v___x_7034_ = lean_unsigned_to_nat(6u);
v___x_7035_ = lean_nat_add(v___x_7017_, v___x_7034_);
v___x_7036_ = lp_competition_Submission_Packed10_packB___lam__0(v_p_7009_, v_base_7015_, v_B_7010_, v___x_7035_);
lean_dec(v___x_7035_);
v___x_7037_ = lean_unsigned_to_nat(7u);
v___x_7038_ = lean_nat_add(v___x_7017_, v___x_7037_);
v___x_7039_ = lp_competition_Submission_Packed10_packB___lam__0(v_p_7009_, v_base_7015_, v_B_7010_, v___x_7038_);
lean_dec(v___x_7038_);
v___x_7040_ = lean_unsigned_to_nat(8u);
v___x_7041_ = lean_nat_add(v___x_7017_, v___x_7040_);
v___x_7042_ = lp_competition_Submission_Packed10_packB___lam__0(v_p_7009_, v_base_7015_, v_B_7010_, v___x_7041_);
lean_dec(v___x_7041_);
v___x_7043_ = lean_unsigned_to_nat(9u);
v___x_7044_ = lean_nat_add(v___x_7017_, v___x_7043_);
lean_dec(v___x_7017_);
v___x_7045_ = lp_competition_Submission_Packed10_packB___lam__0(v_p_7009_, v_base_7015_, v_B_7010_, v___x_7044_);
lean_dec(v___x_7044_);
lean_dec(v_base_7015_);
v___x_7046_ = lean_alloc_ctor(0, 0, 40);
lean_ctor_set_float32(v___x_7046_, 0, v___x_7018_);
lean_ctor_set_float32(v___x_7046_, 4, v___x_7021_);
lean_ctor_set_float32(v___x_7046_, 8, v___x_7024_);
lean_ctor_set_float32(v___x_7046_, 12, v___x_7027_);
lean_ctor_set_float32(v___x_7046_, 16, v___x_7030_);
lean_ctor_set_float32(v___x_7046_, 20, v___x_7033_);
lean_ctor_set_float32(v___x_7046_, 24, v___x_7036_);
lean_ctor_set_float32(v___x_7046_, 28, v___x_7039_);
lean_ctor_set_float32(v___x_7046_, 32, v___x_7042_);
lean_ctor_set_float32(v___x_7046_, 36, v___x_7045_);
return v___x_7046_;
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_Packed10_packB___lam__1___boxed(lean_object* v_b_7047_, lean_object* v_n_7048_, lean_object* v_p_7049_, lean_object* v_B_7050_, lean_object* v_g_7051_, lean_object* v_k_7052_){
_start:
{
lean_object* v_res_7053_; 
v_res_7053_ = lp_competition_Submission_Packed10_packB___lam__1(v_b_7047_, v_n_7048_, v_p_7049_, v_B_7050_, v_g_7051_, v_k_7052_);
lean_dec(v_k_7052_);
lean_dec(v_g_7051_);
lean_dec_ref(v_B_7050_);
lean_dec(v_p_7049_);
lean_dec(v_n_7048_);
lean_dec(v_b_7047_);
return v_res_7053_;
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_Packed10_packB___lam__2(lean_object* v_b_7054_, lean_object* v_n_7055_, lean_object* v_p_7056_, lean_object* v_B_7057_, lean_object* v_g_7058_){
_start:
{
lean_object* v___f_7059_; lean_object* v___x_7060_; 
lean_inc(v_n_7055_);
v___f_7059_ = lean_alloc_closure((void*)(lp_competition_Submission_Packed10_packB___lam__1___boxed), 6, 5);
lean_closure_set(v___f_7059_, 0, v_b_7054_);
lean_closure_set(v___f_7059_, 1, v_n_7055_);
lean_closure_set(v___f_7059_, 2, v_p_7056_);
lean_closure_set(v___f_7059_, 3, v_B_7057_);
lean_closure_set(v___f_7059_, 4, v_g_7058_);
v___x_7060_ = l_Array_ofFn___redArg(v_n_7055_, v___f_7059_);
return v___x_7060_;
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_Packed10_packB___lam__3(lean_object* v_n_7061_, lean_object* v_p_7062_, lean_object* v_B_7063_, lean_object* v_b_7064_){
_start:
{
lean_object* v___f_7065_; lean_object* v___x_7066_; lean_object* v___x_7067_; lean_object* v___x_7068_; lean_object* v___x_7069_; lean_object* v___x_7070_; 
lean_inc(v_p_7062_);
v___f_7065_ = lean_alloc_closure((void*)(lp_competition_Submission_Packed10_packB___lam__2), 5, 4);
lean_closure_set(v___f_7065_, 0, v_b_7064_);
lean_closure_set(v___f_7065_, 1, v_n_7061_);
lean_closure_set(v___f_7065_, 2, v_p_7062_);
lean_closure_set(v___f_7065_, 3, v_B_7063_);
v___x_7066_ = lean_unsigned_to_nat(9u);
v___x_7067_ = lean_nat_add(v_p_7062_, v___x_7066_);
lean_dec(v_p_7062_);
v___x_7068_ = lean_unsigned_to_nat(10u);
v___x_7069_ = lean_nat_div(v___x_7067_, v___x_7068_);
lean_dec(v___x_7067_);
v___x_7070_ = l_Array_ofFn___redArg(v___x_7069_, v___f_7065_);
return v___x_7070_;
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_Packed10_packB(lean_object* v_batch_7071_, lean_object* v_n_7072_, lean_object* v_p_7073_, lean_object* v_B_7074_){
_start:
{
lean_object* v___f_7075_; lean_object* v___x_7076_; 
v___f_7075_ = lean_alloc_closure((void*)(lp_competition_Submission_Packed10_packB___lam__3), 4, 3);
lean_closure_set(v___f_7075_, 0, v_n_7072_);
lean_closure_set(v___f_7075_, 1, v_p_7073_);
lean_closure_set(v___f_7075_, 2, v_B_7074_);
v___x_7076_ = l_Array_ofFn___redArg(v_batch_7071_, v___f_7075_);
return v___x_7076_;
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_Packed10_dot10(lean_object* v_n_7077_, lean_object* v_baseA_7078_, lean_object* v_A_7079_, lean_object* v_B_7080_, lean_object* v_k_7081_, float v_s0_7082_, float v_s1_7083_, float v_s2_7084_, float v_s3_7085_, float v_s4_7086_, float v_s5_7087_, float v_s6_7088_, float v_s7_7089_, float v_s8_7090_, float v_s9_7091_){
_start:
{
float v___y_7093_; uint8_t v___x_7128_; 
v___x_7128_ = lean_nat_dec_lt(v_k_7081_, v_n_7077_);
if (v___x_7128_ == 0)
{
lean_object* v___x_7129_; 
lean_dec(v_k_7081_);
v___x_7129_ = lean_alloc_ctor(0, 0, 40);
lean_ctor_set_float32(v___x_7129_, 0, v_s0_7082_);
lean_ctor_set_float32(v___x_7129_, 4, v_s1_7083_);
lean_ctor_set_float32(v___x_7129_, 8, v_s2_7084_);
lean_ctor_set_float32(v___x_7129_, 12, v_s3_7085_);
lean_ctor_set_float32(v___x_7129_, 16, v_s4_7086_);
lean_ctor_set_float32(v___x_7129_, 20, v_s5_7087_);
lean_ctor_set_float32(v___x_7129_, 24, v_s6_7088_);
lean_ctor_set_float32(v___x_7129_, 28, v_s7_7089_);
lean_ctor_set_float32(v___x_7129_, 32, v_s8_7090_);
lean_ctor_set_float32(v___x_7129_, 36, v_s9_7091_);
return v___x_7129_;
}
else
{
lean_object* v___x_7130_; lean_object* v___x_7131_; uint8_t v___x_7132_; 
v___x_7130_ = lean_nat_add(v_baseA_7078_, v_k_7081_);
v___x_7131_ = lean_array_get_size(v_A_7079_);
v___x_7132_ = lean_nat_dec_lt(v___x_7130_, v___x_7131_);
if (v___x_7132_ == 0)
{
float v___x_7133_; 
lean_dec(v___x_7130_);
v___x_7133_ = lean_float32_once(&lp_competition_Submission_NativeFinal_dot___closed__0, &lp_competition_Submission_NativeFinal_dot___closed__0_once, _init_lp_competition_Submission_NativeFinal_dot___closed__0);
v___y_7093_ = v___x_7133_;
goto v___jp_7092_;
}
else
{
lean_object* v___x_7134_; float v___x_7135_; 
v___x_7134_ = lean_array_fget_borrowed(v_A_7079_, v___x_7130_);
lean_dec(v___x_7130_);
v___x_7135_ = lean_unbox_float32(v___x_7134_);
v___y_7093_ = v___x_7135_;
goto v___jp_7092_;
}
}
v___jp_7092_:
{
lean_object* v_v_7094_; float v_s0_7095_; float v_s1_7096_; float v_s2_7097_; float v_s3_7098_; float v_s4_7099_; float v_s5_7100_; float v_s6_7101_; float v_s7_7102_; float v_s8_7103_; float v_s9_7104_; lean_object* v___x_7105_; lean_object* v___x_7106_; float v___x_7107_; float v___x_7108_; float v___x_7109_; float v___x_7110_; float v___x_7111_; float v___x_7112_; float v___x_7113_; float v___x_7114_; float v___x_7115_; float v___x_7116_; float v___x_7117_; float v___x_7118_; float v___x_7119_; float v___x_7120_; float v___x_7121_; float v___x_7122_; float v___x_7123_; float v___x_7124_; float v___x_7125_; float v___x_7126_; 
v_v_7094_ = lean_array_fget_borrowed(v_B_7080_, v_k_7081_);
v_s0_7095_ = lean_ctor_get_float32(v_v_7094_, 0);
v_s1_7096_ = lean_ctor_get_float32(v_v_7094_, 4);
v_s2_7097_ = lean_ctor_get_float32(v_v_7094_, 8);
v_s3_7098_ = lean_ctor_get_float32(v_v_7094_, 12);
v_s4_7099_ = lean_ctor_get_float32(v_v_7094_, 16);
v_s5_7100_ = lean_ctor_get_float32(v_v_7094_, 20);
v_s6_7101_ = lean_ctor_get_float32(v_v_7094_, 24);
v_s7_7102_ = lean_ctor_get_float32(v_v_7094_, 28);
v_s8_7103_ = lean_ctor_get_float32(v_v_7094_, 32);
v_s9_7104_ = lean_ctor_get_float32(v_v_7094_, 36);
v___x_7105_ = lean_unsigned_to_nat(1u);
v___x_7106_ = lean_nat_add(v_k_7081_, v___x_7105_);
lean_dec(v_k_7081_);
v___x_7107_ = lean_float32_mul(v___y_7093_, v_s0_7095_);
v___x_7108_ = lean_float32_add(v_s0_7082_, v___x_7107_);
v___x_7109_ = lean_float32_mul(v___y_7093_, v_s1_7096_);
v___x_7110_ = lean_float32_add(v_s1_7083_, v___x_7109_);
v___x_7111_ = lean_float32_mul(v___y_7093_, v_s2_7097_);
v___x_7112_ = lean_float32_add(v_s2_7084_, v___x_7111_);
v___x_7113_ = lean_float32_mul(v___y_7093_, v_s3_7098_);
v___x_7114_ = lean_float32_add(v_s3_7085_, v___x_7113_);
v___x_7115_ = lean_float32_mul(v___y_7093_, v_s4_7099_);
v___x_7116_ = lean_float32_add(v_s4_7086_, v___x_7115_);
v___x_7117_ = lean_float32_mul(v___y_7093_, v_s5_7100_);
v___x_7118_ = lean_float32_add(v_s5_7087_, v___x_7117_);
v___x_7119_ = lean_float32_mul(v___y_7093_, v_s6_7101_);
v___x_7120_ = lean_float32_add(v_s6_7088_, v___x_7119_);
v___x_7121_ = lean_float32_mul(v___y_7093_, v_s7_7102_);
v___x_7122_ = lean_float32_add(v_s7_7089_, v___x_7121_);
v___x_7123_ = lean_float32_mul(v___y_7093_, v_s8_7103_);
v___x_7124_ = lean_float32_add(v_s8_7090_, v___x_7123_);
v___x_7125_ = lean_float32_mul(v___y_7093_, v_s9_7104_);
v___x_7126_ = lean_float32_add(v_s9_7091_, v___x_7125_);
v_k_7081_ = v___x_7106_;
v_s0_7082_ = v___x_7108_;
v_s1_7083_ = v___x_7110_;
v_s2_7084_ = v___x_7112_;
v_s3_7085_ = v___x_7114_;
v_s4_7086_ = v___x_7116_;
v_s5_7087_ = v___x_7118_;
v_s6_7088_ = v___x_7120_;
v_s7_7089_ = v___x_7122_;
v_s8_7090_ = v___x_7124_;
v_s9_7091_ = v___x_7126_;
goto _start;
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_Packed10_dot10___boxed(lean_object* v_n_7136_, lean_object* v_baseA_7137_, lean_object* v_A_7138_, lean_object* v_B_7139_, lean_object* v_k_7140_, lean_object* v_s0_7141_, lean_object* v_s1_7142_, lean_object* v_s2_7143_, lean_object* v_s3_7144_, lean_object* v_s4_7145_, lean_object* v_s5_7146_, lean_object* v_s6_7147_, lean_object* v_s7_7148_, lean_object* v_s8_7149_, lean_object* v_s9_7150_){
_start:
{
float v_s0_boxed_7151_; float v_s1_boxed_7152_; float v_s2_boxed_7153_; float v_s3_boxed_7154_; float v_s4_boxed_7155_; float v_s5_boxed_7156_; float v_s6_boxed_7157_; float v_s7_boxed_7158_; float v_s8_boxed_7159_; float v_s9_boxed_7160_; lean_object* v_res_7161_; 
v_s0_boxed_7151_ = lean_unbox_float32(v_s0_7141_);
lean_dec_ref(v_s0_7141_);
v_s1_boxed_7152_ = lean_unbox_float32(v_s1_7142_);
lean_dec_ref(v_s1_7142_);
v_s2_boxed_7153_ = lean_unbox_float32(v_s2_7143_);
lean_dec_ref(v_s2_7143_);
v_s3_boxed_7154_ = lean_unbox_float32(v_s3_7144_);
lean_dec_ref(v_s3_7144_);
v_s4_boxed_7155_ = lean_unbox_float32(v_s4_7145_);
lean_dec_ref(v_s4_7145_);
v_s5_boxed_7156_ = lean_unbox_float32(v_s5_7146_);
lean_dec_ref(v_s5_7146_);
v_s6_boxed_7157_ = lean_unbox_float32(v_s6_7147_);
lean_dec_ref(v_s6_7147_);
v_s7_boxed_7158_ = lean_unbox_float32(v_s7_7148_);
lean_dec_ref(v_s7_7148_);
v_s8_boxed_7159_ = lean_unbox_float32(v_s8_7149_);
lean_dec_ref(v_s8_7149_);
v_s9_boxed_7160_ = lean_unbox_float32(v_s9_7150_);
lean_dec_ref(v_s9_7150_);
v_res_7161_ = lp_competition_Submission_Packed10_dot10(v_n_7136_, v_baseA_7137_, v_A_7138_, v_B_7139_, v_k_7140_, v_s0_boxed_7151_, v_s1_boxed_7152_, v_s2_boxed_7153_, v_s3_boxed_7154_, v_s4_boxed_7155_, v_s5_boxed_7156_, v_s6_boxed_7157_, v_s7_boxed_7158_, v_s8_boxed_7159_, v_s9_boxed_7160_);
lean_dec_ref(v_B_7139_);
lean_dec_ref(v_A_7138_);
lean_dec(v_baseA_7137_);
lean_dec(v_n_7136_);
return v_res_7161_;
}
}
LEAN_EXPORT uint32_t lp_competition_Submission_Packed10_finish(lean_object* v_n_7162_, lean_object* v_baseA_7163_, lean_object* v_baseB_7164_, lean_object* v_p_7165_, lean_object* v_Araw_7166_, lean_object* v_Braw_7167_, float v_result_7168_){
_start:
{
uint8_t v___x_7169_; 
v___x_7169_ = lean_float32_isfinite(v_result_7168_);
if (v___x_7169_ == 0)
{
lean_object* v___x_7170_; uint32_t v___x_7171_; uint32_t v___x_7172_; 
v___x_7170_ = lean_unsigned_to_nat(0u);
v___x_7171_ = lean_uint32_once(&lp_competition_Submission_referenceSum___redArg___closed__1, &lp_competition_Submission_referenceSum___redArg___closed__1_once, _init_lp_competition_Submission_referenceSum___redArg___closed__1);
v___x_7172_ = lp_competition_Fin_foldl_loop___at___00Submission_NativeFinal_dot_spec__0(v_baseA_7163_, v_p_7165_, v_baseB_7164_, v_Braw_7167_, v_Araw_7166_, v_n_7162_, v___x_7171_, v___x_7170_);
return v___x_7172_;
}
else
{
uint32_t v___x_7173_; 
v___x_7173_ = lean_float32_to_bits(v_result_7168_);
return v___x_7173_;
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_Packed10_finish___boxed(lean_object* v_n_7174_, lean_object* v_baseA_7175_, lean_object* v_baseB_7176_, lean_object* v_p_7177_, lean_object* v_Araw_7178_, lean_object* v_Braw_7179_, lean_object* v_result_7180_){
_start:
{
float v_result_boxed_7181_; uint32_t v_res_7182_; lean_object* v_r_7183_; 
v_result_boxed_7181_ = lean_unbox_float32(v_result_7180_);
lean_dec_ref(v_result_7180_);
v_res_7182_ = lp_competition_Submission_Packed10_finish(v_n_7174_, v_baseA_7175_, v_baseB_7176_, v_p_7177_, v_Araw_7178_, v_Braw_7179_, v_result_boxed_7181_);
lean_dec_ref(v_Braw_7179_);
lean_dec_ref(v_Araw_7178_);
lean_dec(v_p_7177_);
lean_dec(v_baseB_7176_);
lean_dec(v_baseA_7175_);
lean_dec(v_n_7174_);
v_r_7183_ = lean_box_uint32(v_res_7182_);
return v_r_7183_;
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_Packed10Index_loop___redArg(size_t v_count_7184_, size_t v_baseA_7185_, lean_object* v_A_7186_, lean_object* v_B_7187_, size_t v_k_7188_, float v_s0_7189_, float v_s1_7190_, float v_s2_7191_, float v_s3_7192_, float v_s4_7193_, float v_s5_7194_, float v_s6_7195_, float v_s7_7196_, float v_s8_7197_, float v_s9_7198_){
_start:
{
uint8_t v___x_7199_; 
v___x_7199_ = lean_usize_dec_lt(v_k_7188_, v_count_7184_);
if (v___x_7199_ == 0)
{
lean_object* v___x_7200_; 
v___x_7200_ = lean_alloc_ctor(0, 0, 40);
lean_ctor_set_float32(v___x_7200_, 0, v_s0_7189_);
lean_ctor_set_float32(v___x_7200_, 4, v_s1_7190_);
lean_ctor_set_float32(v___x_7200_, 8, v_s2_7191_);
lean_ctor_set_float32(v___x_7200_, 12, v_s3_7192_);
lean_ctor_set_float32(v___x_7200_, 16, v_s4_7193_);
lean_ctor_set_float32(v___x_7200_, 20, v_s5_7194_);
lean_ctor_set_float32(v___x_7200_, 24, v_s6_7195_);
lean_ctor_set_float32(v___x_7200_, 28, v_s7_7196_);
lean_ctor_set_float32(v___x_7200_, 32, v_s8_7197_);
lean_ctor_set_float32(v___x_7200_, 36, v_s9_7198_);
return v___x_7200_;
}
else
{
size_t v___x_7201_; lean_object* v_v_7202_; float v_s0_7203_; float v_s1_7204_; float v_s2_7205_; float v_s3_7206_; float v_s4_7207_; float v_s5_7208_; float v_s6_7209_; float v_s7_7210_; float v_s8_7211_; float v_s9_7212_; lean_object* v_a_7213_; size_t v___x_7214_; size_t v___x_7215_; float v___x_7216_; float v___x_7217_; float v___x_7218_; float v___x_7219_; float v___x_7220_; float v___x_7221_; float v___x_7222_; float v___x_7223_; float v___x_7224_; float v___x_7225_; float v___x_7226_; float v___x_7227_; float v___x_7228_; float v___x_7229_; float v___x_7230_; float v___x_7231_; float v___x_7232_; float v___x_7233_; float v___x_7234_; float v___x_7235_; float v___x_7236_; float v___x_7237_; float v___x_7238_; float v___x_7239_; float v___x_7240_; float v___x_7241_; float v___x_7242_; float v___x_7243_; float v___x_7244_; float v___x_7245_; 
v___x_7201_ = lean_usize_add(v_baseA_7185_, v_k_7188_);
v_v_7202_ = lean_array_uget_borrowed(v_B_7187_, v_k_7188_);
v_s0_7203_ = lean_ctor_get_float32(v_v_7202_, 0);
v_s1_7204_ = lean_ctor_get_float32(v_v_7202_, 4);
v_s2_7205_ = lean_ctor_get_float32(v_v_7202_, 8);
v_s3_7206_ = lean_ctor_get_float32(v_v_7202_, 12);
v_s4_7207_ = lean_ctor_get_float32(v_v_7202_, 16);
v_s5_7208_ = lean_ctor_get_float32(v_v_7202_, 20);
v_s6_7209_ = lean_ctor_get_float32(v_v_7202_, 24);
v_s7_7210_ = lean_ctor_get_float32(v_v_7202_, 28);
v_s8_7211_ = lean_ctor_get_float32(v_v_7202_, 32);
v_s9_7212_ = lean_ctor_get_float32(v_v_7202_, 36);
v_a_7213_ = lean_array_uget_borrowed(v_A_7186_, v___x_7201_);
v___x_7214_ = ((size_t)1ULL);
v___x_7215_ = lean_usize_add(v_k_7188_, v___x_7214_);
v___x_7216_ = lean_unbox_float32(v_a_7213_);
v___x_7217_ = lean_float32_mul(v___x_7216_, v_s0_7203_);
v___x_7218_ = lean_float32_add(v_s0_7189_, v___x_7217_);
v___x_7219_ = lean_unbox_float32(v_a_7213_);
v___x_7220_ = lean_float32_mul(v___x_7219_, v_s1_7204_);
v___x_7221_ = lean_float32_add(v_s1_7190_, v___x_7220_);
v___x_7222_ = lean_unbox_float32(v_a_7213_);
v___x_7223_ = lean_float32_mul(v___x_7222_, v_s2_7205_);
v___x_7224_ = lean_float32_add(v_s2_7191_, v___x_7223_);
v___x_7225_ = lean_unbox_float32(v_a_7213_);
v___x_7226_ = lean_float32_mul(v___x_7225_, v_s3_7206_);
v___x_7227_ = lean_float32_add(v_s3_7192_, v___x_7226_);
v___x_7228_ = lean_unbox_float32(v_a_7213_);
v___x_7229_ = lean_float32_mul(v___x_7228_, v_s4_7207_);
v___x_7230_ = lean_float32_add(v_s4_7193_, v___x_7229_);
v___x_7231_ = lean_unbox_float32(v_a_7213_);
v___x_7232_ = lean_float32_mul(v___x_7231_, v_s5_7208_);
v___x_7233_ = lean_float32_add(v_s5_7194_, v___x_7232_);
v___x_7234_ = lean_unbox_float32(v_a_7213_);
v___x_7235_ = lean_float32_mul(v___x_7234_, v_s6_7209_);
v___x_7236_ = lean_float32_add(v_s6_7195_, v___x_7235_);
v___x_7237_ = lean_unbox_float32(v_a_7213_);
v___x_7238_ = lean_float32_mul(v___x_7237_, v_s7_7210_);
v___x_7239_ = lean_float32_add(v_s7_7196_, v___x_7238_);
v___x_7240_ = lean_unbox_float32(v_a_7213_);
v___x_7241_ = lean_float32_mul(v___x_7240_, v_s8_7211_);
v___x_7242_ = lean_float32_add(v_s8_7197_, v___x_7241_);
v___x_7243_ = lean_unbox_float32(v_a_7213_);
v___x_7244_ = lean_float32_mul(v___x_7243_, v_s9_7212_);
v___x_7245_ = lean_float32_add(v_s9_7198_, v___x_7244_);
v_k_7188_ = v___x_7215_;
v_s0_7189_ = v___x_7218_;
v_s1_7190_ = v___x_7221_;
v_s2_7191_ = v___x_7224_;
v_s3_7192_ = v___x_7227_;
v_s4_7193_ = v___x_7230_;
v_s5_7194_ = v___x_7233_;
v_s6_7195_ = v___x_7236_;
v_s7_7196_ = v___x_7239_;
v_s8_7197_ = v___x_7242_;
v_s9_7198_ = v___x_7245_;
goto _start;
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_Packed10Index_loop___redArg___boxed(lean_object* v_count_7247_, lean_object* v_baseA_7248_, lean_object* v_A_7249_, lean_object* v_B_7250_, lean_object* v_k_7251_, lean_object* v_s0_7252_, lean_object* v_s1_7253_, lean_object* v_s2_7254_, lean_object* v_s3_7255_, lean_object* v_s4_7256_, lean_object* v_s5_7257_, lean_object* v_s6_7258_, lean_object* v_s7_7259_, lean_object* v_s8_7260_, lean_object* v_s9_7261_){
_start:
{
size_t v_count_boxed_7262_; size_t v_baseA_boxed_7263_; size_t v_k_boxed_7264_; float v_s0_boxed_7265_; float v_s1_boxed_7266_; float v_s2_boxed_7267_; float v_s3_boxed_7268_; float v_s4_boxed_7269_; float v_s5_boxed_7270_; float v_s6_boxed_7271_; float v_s7_boxed_7272_; float v_s8_boxed_7273_; float v_s9_boxed_7274_; lean_object* v_res_7275_; 
v_count_boxed_7262_ = lean_unbox_usize(v_count_7247_);
lean_dec(v_count_7247_);
v_baseA_boxed_7263_ = lean_unbox_usize(v_baseA_7248_);
lean_dec(v_baseA_7248_);
v_k_boxed_7264_ = lean_unbox_usize(v_k_7251_);
lean_dec(v_k_7251_);
v_s0_boxed_7265_ = lean_unbox_float32(v_s0_7252_);
lean_dec_ref(v_s0_7252_);
v_s1_boxed_7266_ = lean_unbox_float32(v_s1_7253_);
lean_dec_ref(v_s1_7253_);
v_s2_boxed_7267_ = lean_unbox_float32(v_s2_7254_);
lean_dec_ref(v_s2_7254_);
v_s3_boxed_7268_ = lean_unbox_float32(v_s3_7255_);
lean_dec_ref(v_s3_7255_);
v_s4_boxed_7269_ = lean_unbox_float32(v_s4_7256_);
lean_dec_ref(v_s4_7256_);
v_s5_boxed_7270_ = lean_unbox_float32(v_s5_7257_);
lean_dec_ref(v_s5_7257_);
v_s6_boxed_7271_ = lean_unbox_float32(v_s6_7258_);
lean_dec_ref(v_s6_7258_);
v_s7_boxed_7272_ = lean_unbox_float32(v_s7_7259_);
lean_dec_ref(v_s7_7259_);
v_s8_boxed_7273_ = lean_unbox_float32(v_s8_7260_);
lean_dec_ref(v_s8_7260_);
v_s9_boxed_7274_ = lean_unbox_float32(v_s9_7261_);
lean_dec_ref(v_s9_7261_);
v_res_7275_ = lp_competition_Submission_Packed10Index_loop___redArg(v_count_boxed_7262_, v_baseA_boxed_7263_, v_A_7249_, v_B_7250_, v_k_boxed_7264_, v_s0_boxed_7265_, v_s1_boxed_7266_, v_s2_boxed_7267_, v_s3_boxed_7268_, v_s4_boxed_7269_, v_s5_boxed_7270_, v_s6_boxed_7271_, v_s7_boxed_7272_, v_s8_boxed_7273_, v_s9_boxed_7274_);
lean_dec_ref(v_B_7250_);
lean_dec_ref(v_A_7249_);
return v_res_7275_;
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_Packed10Index_loop(lean_object* v_n_7276_, size_t v_count_7277_, size_t v_baseA_7278_, lean_object* v_A_7279_, lean_object* v_B_7280_, lean_object* v_hn_7281_, lean_object* v_hA_7282_, lean_object* v_hAS_7283_, size_t v_k_7284_, float v_s0_7285_, float v_s1_7286_, float v_s2_7287_, float v_s3_7288_, float v_s4_7289_, float v_s5_7290_, float v_s6_7291_, float v_s7_7292_, float v_s8_7293_, float v_s9_7294_){
_start:
{
lean_object* v___x_7295_; 
v___x_7295_ = lp_competition_Submission_Packed10Index_loop___redArg(v_count_7277_, v_baseA_7278_, v_A_7279_, v_B_7280_, v_k_7284_, v_s0_7285_, v_s1_7286_, v_s2_7287_, v_s3_7288_, v_s4_7289_, v_s5_7290_, v_s6_7291_, v_s7_7292_, v_s8_7293_, v_s9_7294_);
return v___x_7295_;
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_Packed10Index_loop___boxed(lean_object** _args){
lean_object* v_n_7296_ = _args[0];
lean_object* v_count_7297_ = _args[1];
lean_object* v_baseA_7298_ = _args[2];
lean_object* v_A_7299_ = _args[3];
lean_object* v_B_7300_ = _args[4];
lean_object* v_hn_7301_ = _args[5];
lean_object* v_hA_7302_ = _args[6];
lean_object* v_hAS_7303_ = _args[7];
lean_object* v_k_7304_ = _args[8];
lean_object* v_s0_7305_ = _args[9];
lean_object* v_s1_7306_ = _args[10];
lean_object* v_s2_7307_ = _args[11];
lean_object* v_s3_7308_ = _args[12];
lean_object* v_s4_7309_ = _args[13];
lean_object* v_s5_7310_ = _args[14];
lean_object* v_s6_7311_ = _args[15];
lean_object* v_s7_7312_ = _args[16];
lean_object* v_s8_7313_ = _args[17];
lean_object* v_s9_7314_ = _args[18];
_start:
{
size_t v_count_boxed_7315_; size_t v_baseA_boxed_7316_; size_t v_k_boxed_7317_; float v_s0_boxed_7318_; float v_s1_boxed_7319_; float v_s2_boxed_7320_; float v_s3_boxed_7321_; float v_s4_boxed_7322_; float v_s5_boxed_7323_; float v_s6_boxed_7324_; float v_s7_boxed_7325_; float v_s8_boxed_7326_; float v_s9_boxed_7327_; lean_object* v_res_7328_; 
v_count_boxed_7315_ = lean_unbox_usize(v_count_7297_);
lean_dec(v_count_7297_);
v_baseA_boxed_7316_ = lean_unbox_usize(v_baseA_7298_);
lean_dec(v_baseA_7298_);
v_k_boxed_7317_ = lean_unbox_usize(v_k_7304_);
lean_dec(v_k_7304_);
v_s0_boxed_7318_ = lean_unbox_float32(v_s0_7305_);
lean_dec_ref(v_s0_7305_);
v_s1_boxed_7319_ = lean_unbox_float32(v_s1_7306_);
lean_dec_ref(v_s1_7306_);
v_s2_boxed_7320_ = lean_unbox_float32(v_s2_7307_);
lean_dec_ref(v_s2_7307_);
v_s3_boxed_7321_ = lean_unbox_float32(v_s3_7308_);
lean_dec_ref(v_s3_7308_);
v_s4_boxed_7322_ = lean_unbox_float32(v_s4_7309_);
lean_dec_ref(v_s4_7309_);
v_s5_boxed_7323_ = lean_unbox_float32(v_s5_7310_);
lean_dec_ref(v_s5_7310_);
v_s6_boxed_7324_ = lean_unbox_float32(v_s6_7311_);
lean_dec_ref(v_s6_7311_);
v_s7_boxed_7325_ = lean_unbox_float32(v_s7_7312_);
lean_dec_ref(v_s7_7312_);
v_s8_boxed_7326_ = lean_unbox_float32(v_s8_7313_);
lean_dec_ref(v_s8_7313_);
v_s9_boxed_7327_ = lean_unbox_float32(v_s9_7314_);
lean_dec_ref(v_s9_7314_);
v_res_7328_ = lp_competition_Submission_Packed10Index_loop(v_n_7296_, v_count_boxed_7315_, v_baseA_boxed_7316_, v_A_7299_, v_B_7300_, v_hn_7301_, v_hA_7302_, v_hAS_7303_, v_k_boxed_7317_, v_s0_boxed_7318_, v_s1_boxed_7319_, v_s2_boxed_7320_, v_s3_boxed_7321_, v_s4_boxed_7322_, v_s5_boxed_7323_, v_s6_boxed_7324_, v_s7_boxed_7325_, v_s8_boxed_7326_, v_s9_boxed_7327_);
lean_dec_ref(v_B_7300_);
lean_dec_ref(v_A_7299_);
lean_dec(v_n_7296_);
return v_res_7328_;
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_Packed10Index_within___redArg(lean_object* v_n_7329_, lean_object* v_baseA_7330_, lean_object* v_A_7331_, lean_object* v_B_7332_){
_start:
{
size_t v___x_7333_; size_t v___x_7334_; size_t v___x_7335_; float v___x_7336_; lean_object* v___x_7337_; 
v___x_7333_ = lean_usize_of_nat(v_n_7329_);
v___x_7334_ = lean_usize_of_nat(v_baseA_7330_);
v___x_7335_ = ((size_t)0ULL);
v___x_7336_ = lean_float32_once(&lp_competition_Submission_NativeFinal_dot___closed__0, &lp_competition_Submission_NativeFinal_dot___closed__0_once, _init_lp_competition_Submission_NativeFinal_dot___closed__0);
v___x_7337_ = lp_competition_Submission_Packed10Index_loop___redArg(v___x_7333_, v___x_7334_, v_A_7331_, v_B_7332_, v___x_7335_, v___x_7336_, v___x_7336_, v___x_7336_, v___x_7336_, v___x_7336_, v___x_7336_, v___x_7336_, v___x_7336_, v___x_7336_, v___x_7336_);
return v___x_7337_;
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_Packed10Index_within___redArg___boxed(lean_object* v_n_7338_, lean_object* v_baseA_7339_, lean_object* v_A_7340_, lean_object* v_B_7341_){
_start:
{
lean_object* v_res_7342_; 
v_res_7342_ = lp_competition_Submission_Packed10Index_within___redArg(v_n_7338_, v_baseA_7339_, v_A_7340_, v_B_7341_);
lean_dec_ref(v_B_7341_);
lean_dec_ref(v_A_7340_);
lean_dec(v_baseA_7339_);
lean_dec(v_n_7338_);
return v_res_7342_;
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_Packed10Index_within(lean_object* v_n_7343_, lean_object* v_baseA_7344_, lean_object* v_A_7345_, lean_object* v_B_7346_, lean_object* v_hn_7347_, lean_object* v_ha_7348_, lean_object* v_hA_7349_, lean_object* v_hAS_7350_){
_start:
{
size_t v___x_7351_; size_t v___x_7352_; size_t v___x_7353_; float v___x_7354_; lean_object* v___x_7355_; 
v___x_7351_ = lean_usize_of_nat(v_n_7343_);
v___x_7352_ = lean_usize_of_nat(v_baseA_7344_);
v___x_7353_ = ((size_t)0ULL);
v___x_7354_ = lean_float32_once(&lp_competition_Submission_NativeFinal_dot___closed__0, &lp_competition_Submission_NativeFinal_dot___closed__0_once, _init_lp_competition_Submission_NativeFinal_dot___closed__0);
v___x_7355_ = lp_competition_Submission_Packed10Index_loop___redArg(v___x_7351_, v___x_7352_, v_A_7345_, v_B_7346_, v___x_7353_, v___x_7354_, v___x_7354_, v___x_7354_, v___x_7354_, v___x_7354_, v___x_7354_, v___x_7354_, v___x_7354_, v___x_7354_, v___x_7354_);
return v___x_7355_;
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_Packed10Index_within___boxed(lean_object* v_n_7356_, lean_object* v_baseA_7357_, lean_object* v_A_7358_, lean_object* v_B_7359_, lean_object* v_hn_7360_, lean_object* v_ha_7361_, lean_object* v_hA_7362_, lean_object* v_hAS_7363_){
_start:
{
lean_object* v_res_7364_; 
v_res_7364_ = lp_competition_Submission_Packed10Index_within(v_n_7356_, v_baseA_7357_, v_A_7358_, v_B_7359_, v_hn_7360_, v_ha_7361_, v_hA_7362_, v_hAS_7363_);
lean_dec_ref(v_B_7359_);
lean_dec_ref(v_A_7358_);
lean_dec(v_baseA_7357_);
lean_dec(v_n_7356_);
return v_res_7364_;
}
}
static lean_object* _init_lp_competition_Submission_Packed10Index_runDot___closed__0(void){
_start:
{
lean_object* v___x_7365_; lean_object* v___x_7366_; lean_object* v___x_7367_; 
v___x_7365_ = l_System_Platform_numBits;
v___x_7366_ = lean_unsigned_to_nat(2u);
v___x_7367_ = lean_nat_pow(v___x_7366_, v___x_7365_);
return v___x_7367_;
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_Packed10Index_runDot(lean_object* v_n_7368_, lean_object* v_baseA_7369_, lean_object* v_A_7370_, lean_object* v_B_7371_){
_start:
{
lean_object* v___x_7376_; uint8_t v___x_7377_; 
v___x_7376_ = lean_obj_once(&lp_competition_Submission_Packed10Index_runDot___closed__0, &lp_competition_Submission_Packed10Index_runDot___closed__0_once, _init_lp_competition_Submission_Packed10Index_runDot___closed__0);
v___x_7377_ = lean_nat_dec_lt(v_n_7368_, v___x_7376_);
if (v___x_7377_ == 0)
{
goto v___jp_7372_;
}
else
{
uint8_t v___x_7378_; 
v___x_7378_ = lean_nat_dec_lt(v_baseA_7369_, v___x_7376_);
if (v___x_7378_ == 0)
{
goto v___jp_7372_;
}
else
{
lean_object* v___x_7379_; lean_object* v___x_7380_; lean_object* v___x_7381_; lean_object* v___x_7382_; uint8_t v___x_7383_; 
v___x_7379_ = lean_unsigned_to_nat(1u);
v___x_7380_ = lean_nat_sub(v_n_7368_, v___x_7379_);
v___x_7381_ = lean_nat_add(v_baseA_7369_, v___x_7380_);
lean_dec(v___x_7380_);
v___x_7382_ = lean_array_get_size(v_A_7370_);
v___x_7383_ = lean_nat_dec_lt(v___x_7381_, v___x_7382_);
lean_dec(v___x_7381_);
if (v___x_7383_ == 0)
{
goto v___jp_7372_;
}
else
{
uint8_t v___x_7384_; 
v___x_7384_ = lean_nat_dec_lt(v___x_7382_, v___x_7376_);
if (v___x_7384_ == 0)
{
goto v___jp_7372_;
}
else
{
size_t v___x_7385_; size_t v___x_7386_; size_t v___x_7387_; float v___x_7388_; lean_object* v___x_7389_; 
v___x_7385_ = lean_usize_of_nat(v_n_7368_);
v___x_7386_ = lean_usize_of_nat(v_baseA_7369_);
v___x_7387_ = ((size_t)0ULL);
v___x_7388_ = lean_float32_once(&lp_competition_Submission_NativeFinal_dot___closed__0, &lp_competition_Submission_NativeFinal_dot___closed__0_once, _init_lp_competition_Submission_NativeFinal_dot___closed__0);
v___x_7389_ = lp_competition_Submission_Packed10Index_loop___redArg(v___x_7385_, v___x_7386_, v_A_7370_, v_B_7371_, v___x_7387_, v___x_7388_, v___x_7388_, v___x_7388_, v___x_7388_, v___x_7388_, v___x_7388_, v___x_7388_, v___x_7388_, v___x_7388_, v___x_7388_);
return v___x_7389_;
}
}
}
}
v___jp_7372_:
{
lean_object* v___x_7373_; float v___x_7374_; lean_object* v___x_7375_; 
v___x_7373_ = lean_unsigned_to_nat(0u);
v___x_7374_ = lean_float32_once(&lp_competition_Submission_NativeFinal_dot___closed__0, &lp_competition_Submission_NativeFinal_dot___closed__0_once, _init_lp_competition_Submission_NativeFinal_dot___closed__0);
v___x_7375_ = lp_competition_Submission_Packed10_dot10(v_n_7368_, v_baseA_7369_, v_A_7370_, v_B_7371_, v___x_7373_, v___x_7374_, v___x_7374_, v___x_7374_, v___x_7374_, v___x_7374_, v___x_7374_, v___x_7374_, v___x_7374_, v___x_7374_, v___x_7374_);
return v___x_7375_;
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_Packed10Index_runDot___boxed(lean_object* v_n_7390_, lean_object* v_baseA_7391_, lean_object* v_A_7392_, lean_object* v_B_7393_){
_start:
{
lean_object* v_res_7394_; 
v_res_7394_ = lp_competition_Submission_Packed10Index_runDot(v_n_7390_, v_baseA_7391_, v_A_7392_, v_B_7393_);
lean_dec_ref(v_B_7393_);
lean_dec_ref(v_A_7392_);
lean_dec(v_baseA_7391_);
lean_dec(v_n_7390_);
return v_res_7394_;
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_Packed10_tileResults___lam__0(lean_object* v_b_7395_, lean_object* v_m_7396_, lean_object* v_i_7397_, lean_object* v_n_7398_, lean_object* v_B_7399_, lean_object* v_A_7400_, lean_object* v_g_7401_){
_start:
{
lean_object* v___x_7402_; lean_object* v___x_7403_; lean_object* v___x_7404_; lean_object* v___x_7405_; lean_object* v___x_7406_; lean_object* v___x_7411_; uint8_t v___x_7412_; 
v___x_7402_ = lean_nat_mul(v_b_7395_, v_m_7396_);
v___x_7403_ = lean_nat_add(v___x_7402_, v_i_7397_);
lean_dec(v___x_7402_);
v___x_7404_ = lean_nat_mul(v___x_7403_, v_n_7398_);
lean_dec(v___x_7403_);
v___x_7405_ = lean_array_fget_borrowed(v_B_7399_, v_b_7395_);
v___x_7406_ = lean_array_fget_borrowed(v___x_7405_, v_g_7401_);
v___x_7411_ = lean_obj_once(&lp_competition_Submission_Packed10Index_runDot___closed__0, &lp_competition_Submission_Packed10Index_runDot___closed__0_once, _init_lp_competition_Submission_Packed10Index_runDot___closed__0);
v___x_7412_ = lean_nat_dec_lt(v_n_7398_, v___x_7411_);
if (v___x_7412_ == 0)
{
goto v___jp_7407_;
}
else
{
uint8_t v___x_7413_; 
v___x_7413_ = lean_nat_dec_lt(v___x_7404_, v___x_7411_);
if (v___x_7413_ == 0)
{
goto v___jp_7407_;
}
else
{
lean_object* v___x_7414_; lean_object* v___x_7415_; lean_object* v___x_7416_; lean_object* v___x_7417_; uint8_t v___x_7418_; 
v___x_7414_ = lean_unsigned_to_nat(1u);
v___x_7415_ = lean_nat_sub(v_n_7398_, v___x_7414_);
v___x_7416_ = lean_nat_add(v___x_7404_, v___x_7415_);
lean_dec(v___x_7415_);
v___x_7417_ = lean_array_get_size(v_A_7400_);
v___x_7418_ = lean_nat_dec_lt(v___x_7416_, v___x_7417_);
lean_dec(v___x_7416_);
if (v___x_7418_ == 0)
{
goto v___jp_7407_;
}
else
{
uint8_t v___x_7419_; 
v___x_7419_ = lean_nat_dec_lt(v___x_7417_, v___x_7411_);
if (v___x_7419_ == 0)
{
goto v___jp_7407_;
}
else
{
size_t v___x_7420_; size_t v___x_7421_; size_t v___x_7422_; float v___x_7423_; lean_object* v___x_7424_; 
v___x_7420_ = lean_usize_of_nat(v_n_7398_);
v___x_7421_ = lean_usize_of_nat(v___x_7404_);
lean_dec(v___x_7404_);
v___x_7422_ = ((size_t)0ULL);
v___x_7423_ = lean_float32_once(&lp_competition_Submission_NativeFinal_dot___closed__0, &lp_competition_Submission_NativeFinal_dot___closed__0_once, _init_lp_competition_Submission_NativeFinal_dot___closed__0);
v___x_7424_ = lp_competition_Submission_Packed10Index_loop___redArg(v___x_7420_, v___x_7421_, v_A_7400_, v___x_7406_, v___x_7422_, v___x_7423_, v___x_7423_, v___x_7423_, v___x_7423_, v___x_7423_, v___x_7423_, v___x_7423_, v___x_7423_, v___x_7423_, v___x_7423_);
return v___x_7424_;
}
}
}
}
v___jp_7407_:
{
lean_object* v___x_7408_; float v___x_7409_; lean_object* v___x_7410_; 
v___x_7408_ = lean_unsigned_to_nat(0u);
v___x_7409_ = lean_float32_once(&lp_competition_Submission_NativeFinal_dot___closed__0, &lp_competition_Submission_NativeFinal_dot___closed__0_once, _init_lp_competition_Submission_NativeFinal_dot___closed__0);
v___x_7410_ = lp_competition_Submission_Packed10_dot10(v_n_7398_, v___x_7404_, v_A_7400_, v___x_7406_, v___x_7408_, v___x_7409_, v___x_7409_, v___x_7409_, v___x_7409_, v___x_7409_, v___x_7409_, v___x_7409_, v___x_7409_, v___x_7409_, v___x_7409_);
lean_dec(v___x_7404_);
return v___x_7410_;
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_Packed10_tileResults___lam__0___boxed(lean_object* v_b_7425_, lean_object* v_m_7426_, lean_object* v_i_7427_, lean_object* v_n_7428_, lean_object* v_B_7429_, lean_object* v_A_7430_, lean_object* v_g_7431_){
_start:
{
lean_object* v_res_7432_; 
v_res_7432_ = lp_competition_Submission_Packed10_tileResults___lam__0(v_b_7425_, v_m_7426_, v_i_7427_, v_n_7428_, v_B_7429_, v_A_7430_, v_g_7431_);
lean_dec(v_g_7431_);
lean_dec_ref(v_A_7430_);
lean_dec_ref(v_B_7429_);
lean_dec(v_n_7428_);
lean_dec(v_i_7427_);
lean_dec(v_m_7426_);
lean_dec(v_b_7425_);
return v_res_7432_;
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_Packed10_tileResults___lam__1(lean_object* v_b_7433_, lean_object* v_m_7434_, lean_object* v_n_7435_, lean_object* v_B_7436_, lean_object* v_A_7437_, lean_object* v_p_7438_, lean_object* v_i_7439_){
_start:
{
lean_object* v___f_7440_; lean_object* v___x_7441_; lean_object* v___x_7442_; lean_object* v___x_7443_; lean_object* v___x_7444_; lean_object* v___x_7445_; 
v___f_7440_ = lean_alloc_closure((void*)(lp_competition_Submission_Packed10_tileResults___lam__0___boxed), 7, 6);
lean_closure_set(v___f_7440_, 0, v_b_7433_);
lean_closure_set(v___f_7440_, 1, v_m_7434_);
lean_closure_set(v___f_7440_, 2, v_i_7439_);
lean_closure_set(v___f_7440_, 3, v_n_7435_);
lean_closure_set(v___f_7440_, 4, v_B_7436_);
lean_closure_set(v___f_7440_, 5, v_A_7437_);
v___x_7441_ = lean_unsigned_to_nat(9u);
v___x_7442_ = lean_nat_add(v_p_7438_, v___x_7441_);
v___x_7443_ = lean_unsigned_to_nat(10u);
v___x_7444_ = lean_nat_div(v___x_7442_, v___x_7443_);
lean_dec(v___x_7442_);
v___x_7445_ = l_Array_ofFn___redArg(v___x_7444_, v___f_7440_);
return v___x_7445_;
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_Packed10_tileResults___lam__1___boxed(lean_object* v_b_7446_, lean_object* v_m_7447_, lean_object* v_n_7448_, lean_object* v_B_7449_, lean_object* v_A_7450_, lean_object* v_p_7451_, lean_object* v_i_7452_){
_start:
{
lean_object* v_res_7453_; 
v_res_7453_ = lp_competition_Submission_Packed10_tileResults___lam__1(v_b_7446_, v_m_7447_, v_n_7448_, v_B_7449_, v_A_7450_, v_p_7451_, v_i_7452_);
lean_dec(v_p_7451_);
return v_res_7453_;
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_Packed10_tileResults___lam__2(lean_object* v_m_7454_, lean_object* v_n_7455_, lean_object* v_B_7456_, lean_object* v_A_7457_, lean_object* v_p_7458_, lean_object* v_b_7459_){
_start:
{
lean_object* v___f_7460_; lean_object* v___x_7461_; 
lean_inc(v_m_7454_);
v___f_7460_ = lean_alloc_closure((void*)(lp_competition_Submission_Packed10_tileResults___lam__1___boxed), 7, 6);
lean_closure_set(v___f_7460_, 0, v_b_7459_);
lean_closure_set(v___f_7460_, 1, v_m_7454_);
lean_closure_set(v___f_7460_, 2, v_n_7455_);
lean_closure_set(v___f_7460_, 3, v_B_7456_);
lean_closure_set(v___f_7460_, 4, v_A_7457_);
lean_closure_set(v___f_7460_, 5, v_p_7458_);
v___x_7461_ = l_Array_ofFn___redArg(v_m_7454_, v___f_7460_);
return v___x_7461_;
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_Packed10_tileResults(lean_object* v_batch_7462_, lean_object* v_m_7463_, lean_object* v_n_7464_, lean_object* v_p_7465_, lean_object* v_A_7466_, lean_object* v_B_7467_){
_start:
{
lean_object* v___f_7468_; lean_object* v___x_7469_; 
v___f_7468_ = lean_alloc_closure((void*)(lp_competition_Submission_Packed10_tileResults___lam__2), 6, 5);
lean_closure_set(v___f_7468_, 0, v_m_7463_);
lean_closure_set(v___f_7468_, 1, v_n_7464_);
lean_closure_set(v___f_7468_, 2, v_B_7467_);
lean_closure_set(v___f_7468_, 3, v_A_7466_);
lean_closure_set(v___f_7468_, 4, v_p_7465_);
v___x_7469_ = l_Array_ofFn___redArg(v_batch_7462_, v___f_7468_);
return v___x_7469_;
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_Packed10_inlineDecodeC(lean_object* v_m_7470_, lean_object* v_p_7471_, lean_object* v_q_7472_){
_start:
{
lean_object* v___y_7474_; lean_object* v___y_7475_; lean_object* v___y_7476_; lean_object* v_rowSize_7479_; lean_object* v___x_7480_; uint8_t v___x_7481_; uint8_t v___x_7482_; lean_object* v___y_7484_; lean_object* v___y_7485_; lean_object* v___y_7486_; lean_object* v___y_7489_; lean_object* v___y_7490_; lean_object* v___y_7493_; 
v_rowSize_7479_ = lean_nat_mul(v_m_7470_, v_p_7471_);
v___x_7480_ = lean_unsigned_to_nat(0u);
v___x_7481_ = lean_nat_dec_eq(v_rowSize_7479_, v___x_7480_);
v___x_7482_ = lean_nat_dec_eq(v_p_7471_, v___x_7480_);
if (v___x_7481_ == 0)
{
lean_object* v___x_7495_; 
v___x_7495_ = lean_nat_div(v_q_7472_, v_rowSize_7479_);
v___y_7493_ = v___x_7495_;
goto v___jp_7492_;
}
else
{
v___y_7493_ = v___x_7480_;
goto v___jp_7492_;
}
v___jp_7473_:
{
lean_object* v___x_7477_; lean_object* v___x_7478_; 
v___x_7477_ = lean_alloc_ctor(0, 2, 0);
lean_ctor_set(v___x_7477_, 0, v___y_7474_);
lean_ctor_set(v___x_7477_, 1, v___y_7476_);
v___x_7478_ = lean_alloc_ctor(0, 2, 0);
lean_ctor_set(v___x_7478_, 0, v___y_7475_);
lean_ctor_set(v___x_7478_, 1, v___x_7477_);
return v___x_7478_;
}
v___jp_7483_:
{
if (v___x_7482_ == 0)
{
lean_object* v___x_7487_; 
v___x_7487_ = lean_nat_mod(v___y_7484_, v_p_7471_);
lean_dec(v___y_7484_);
v___y_7474_ = v___y_7486_;
v___y_7475_ = v___y_7485_;
v___y_7476_ = v___x_7487_;
goto v___jp_7473_;
}
else
{
lean_dec(v___y_7484_);
v___y_7474_ = v___y_7486_;
v___y_7475_ = v___y_7485_;
v___y_7476_ = v___x_7480_;
goto v___jp_7473_;
}
}
v___jp_7488_:
{
if (v___x_7482_ == 0)
{
lean_object* v___x_7491_; 
v___x_7491_ = lean_nat_div(v___y_7490_, v_p_7471_);
v___y_7484_ = v___y_7490_;
v___y_7485_ = v___y_7489_;
v___y_7486_ = v___x_7491_;
goto v___jp_7483_;
}
else
{
v___y_7484_ = v___y_7490_;
v___y_7485_ = v___y_7489_;
v___y_7486_ = v___x_7480_;
goto v___jp_7483_;
}
}
v___jp_7492_:
{
if (v___x_7481_ == 0)
{
lean_object* v___x_7494_; 
v___x_7494_ = lean_nat_mod(v_q_7472_, v_rowSize_7479_);
lean_dec(v_rowSize_7479_);
v___y_7489_ = v___y_7493_;
v___y_7490_ = v___x_7494_;
goto v___jp_7488_;
}
else
{
lean_dec(v_rowSize_7479_);
v___y_7489_ = v___y_7493_;
v___y_7490_ = v___x_7480_;
goto v___jp_7488_;
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_Packed10_inlineDecodeC___boxed(lean_object* v_m_7496_, lean_object* v_p_7497_, lean_object* v_q_7498_){
_start:
{
lean_object* v_res_7499_; 
v_res_7499_ = lp_competition_Submission_Packed10_inlineDecodeC(v_m_7496_, v_p_7497_, v_q_7498_);
lean_dec(v_q_7498_);
lean_dec(v_p_7497_);
lean_dec(v_m_7496_);
return v_res_7499_;
}
}
LEAN_EXPORT uint32_t lp_competition_Submission_Packed10_outputFromTiles___redArg(lean_object* v_m_7500_, lean_object* v_n_7501_, lean_object* v_p_7502_, lean_object* v_A_7503_, lean_object* v_B_7504_, lean_object* v_tiles_7505_, lean_object* v_q_7506_){
_start:
{
lean_object* v_rowSize_7507_; lean_object* v___x_7508_; lean_object* v___y_7510_; lean_object* v___y_7511_; lean_object* v___y_7512_; uint8_t v___x_7562_; uint8_t v___x_7563_; lean_object* v___y_7565_; lean_object* v___y_7566_; lean_object* v___y_7567_; lean_object* v___y_7570_; lean_object* v___y_7571_; lean_object* v___y_7574_; 
v_rowSize_7507_ = lean_nat_mul(v_m_7500_, v_p_7502_);
v___x_7508_ = lean_unsigned_to_nat(0u);
v___x_7562_ = lean_nat_dec_eq(v_rowSize_7507_, v___x_7508_);
v___x_7563_ = lean_nat_dec_eq(v_p_7502_, v___x_7508_);
if (v___x_7562_ == 0)
{
lean_object* v___x_7576_; 
v___x_7576_ = lean_nat_div(v_q_7506_, v_rowSize_7507_);
v___y_7574_ = v___x_7576_;
goto v___jp_7573_;
}
else
{
v___y_7574_ = v___x_7508_;
goto v___jp_7573_;
}
v___jp_7509_:
{
lean_object* v___x_7513_; lean_object* v___x_7514_; lean_object* v___x_7515_; lean_object* v___x_7516_; lean_object* v___x_7517_; lean_object* v___x_7518_; lean_object* v___x_7519_; lean_object* v___x_7520_; lean_object* v___x_7521_; lean_object* v___x_7522_; lean_object* v___x_7523_; lean_object* v___x_7524_; uint8_t v___x_7525_; 
v___x_7513_ = lean_unsigned_to_nat(10u);
v___x_7514_ = lean_nat_div(v___y_7512_, v___x_7513_);
v___x_7515_ = lean_nat_mod(v___y_7512_, v___x_7513_);
v___x_7516_ = lean_nat_mul(v___y_7510_, v_m_7500_);
v___x_7517_ = lean_nat_add(v___x_7516_, v___y_7511_);
lean_dec(v___x_7516_);
v___x_7518_ = lean_nat_mul(v___x_7517_, v_n_7501_);
lean_dec(v___x_7517_);
v___x_7519_ = lean_nat_mul(v___y_7510_, v_n_7501_);
v___x_7520_ = lean_nat_mul(v___x_7519_, v_p_7502_);
lean_dec(v___x_7519_);
v___x_7521_ = lean_nat_add(v___x_7520_, v___y_7512_);
lean_dec(v___y_7512_);
lean_dec(v___x_7520_);
v___x_7522_ = lean_array_fget_borrowed(v_tiles_7505_, v___y_7510_);
lean_dec(v___y_7510_);
v___x_7523_ = lean_array_fget_borrowed(v___x_7522_, v___y_7511_);
lean_dec(v___y_7511_);
v___x_7524_ = lean_array_fget_borrowed(v___x_7523_, v___x_7514_);
lean_dec(v___x_7514_);
v___x_7525_ = lean_nat_dec_eq(v___x_7515_, v___x_7508_);
if (v___x_7525_ == 0)
{
lean_object* v___x_7526_; uint8_t v___x_7527_; 
v___x_7526_ = lean_unsigned_to_nat(1u);
v___x_7527_ = lean_nat_dec_eq(v___x_7515_, v___x_7526_);
if (v___x_7527_ == 0)
{
lean_object* v___x_7528_; uint8_t v___x_7529_; 
v___x_7528_ = lean_unsigned_to_nat(2u);
v___x_7529_ = lean_nat_dec_eq(v___x_7515_, v___x_7528_);
if (v___x_7529_ == 0)
{
lean_object* v___x_7530_; uint8_t v___x_7531_; 
v___x_7530_ = lean_unsigned_to_nat(3u);
v___x_7531_ = lean_nat_dec_eq(v___x_7515_, v___x_7530_);
if (v___x_7531_ == 0)
{
lean_object* v___x_7532_; uint8_t v___x_7533_; 
v___x_7532_ = lean_unsigned_to_nat(4u);
v___x_7533_ = lean_nat_dec_eq(v___x_7515_, v___x_7532_);
if (v___x_7533_ == 0)
{
lean_object* v___x_7534_; uint8_t v___x_7535_; 
v___x_7534_ = lean_unsigned_to_nat(5u);
v___x_7535_ = lean_nat_dec_eq(v___x_7515_, v___x_7534_);
if (v___x_7535_ == 0)
{
lean_object* v___x_7536_; uint8_t v___x_7537_; 
v___x_7536_ = lean_unsigned_to_nat(6u);
v___x_7537_ = lean_nat_dec_eq(v___x_7515_, v___x_7536_);
if (v___x_7537_ == 0)
{
lean_object* v___x_7538_; uint8_t v___x_7539_; 
v___x_7538_ = lean_unsigned_to_nat(7u);
v___x_7539_ = lean_nat_dec_eq(v___x_7515_, v___x_7538_);
if (v___x_7539_ == 0)
{
lean_object* v___x_7540_; uint8_t v___x_7541_; 
v___x_7540_ = lean_unsigned_to_nat(8u);
v___x_7541_ = lean_nat_dec_eq(v___x_7515_, v___x_7540_);
lean_dec(v___x_7515_);
if (v___x_7541_ == 0)
{
float v_s9_7542_; uint32_t v___x_7543_; 
v_s9_7542_ = lean_ctor_get_float32(v___x_7524_, 36);
v___x_7543_ = lp_competition_Submission_Packed10_finish(v_n_7501_, v___x_7518_, v___x_7521_, v_p_7502_, v_A_7503_, v_B_7504_, v_s9_7542_);
lean_dec(v___x_7521_);
lean_dec(v___x_7518_);
return v___x_7543_;
}
else
{
float v_s8_7544_; uint32_t v___x_7545_; 
v_s8_7544_ = lean_ctor_get_float32(v___x_7524_, 32);
v___x_7545_ = lp_competition_Submission_Packed10_finish(v_n_7501_, v___x_7518_, v___x_7521_, v_p_7502_, v_A_7503_, v_B_7504_, v_s8_7544_);
lean_dec(v___x_7521_);
lean_dec(v___x_7518_);
return v___x_7545_;
}
}
else
{
float v_s7_7546_; uint32_t v___x_7547_; 
lean_dec(v___x_7515_);
v_s7_7546_ = lean_ctor_get_float32(v___x_7524_, 28);
v___x_7547_ = lp_competition_Submission_Packed10_finish(v_n_7501_, v___x_7518_, v___x_7521_, v_p_7502_, v_A_7503_, v_B_7504_, v_s7_7546_);
lean_dec(v___x_7521_);
lean_dec(v___x_7518_);
return v___x_7547_;
}
}
else
{
float v_s6_7548_; uint32_t v___x_7549_; 
lean_dec(v___x_7515_);
v_s6_7548_ = lean_ctor_get_float32(v___x_7524_, 24);
v___x_7549_ = lp_competition_Submission_Packed10_finish(v_n_7501_, v___x_7518_, v___x_7521_, v_p_7502_, v_A_7503_, v_B_7504_, v_s6_7548_);
lean_dec(v___x_7521_);
lean_dec(v___x_7518_);
return v___x_7549_;
}
}
else
{
float v_s5_7550_; uint32_t v___x_7551_; 
lean_dec(v___x_7515_);
v_s5_7550_ = lean_ctor_get_float32(v___x_7524_, 20);
v___x_7551_ = lp_competition_Submission_Packed10_finish(v_n_7501_, v___x_7518_, v___x_7521_, v_p_7502_, v_A_7503_, v_B_7504_, v_s5_7550_);
lean_dec(v___x_7521_);
lean_dec(v___x_7518_);
return v___x_7551_;
}
}
else
{
float v_s4_7552_; uint32_t v___x_7553_; 
lean_dec(v___x_7515_);
v_s4_7552_ = lean_ctor_get_float32(v___x_7524_, 16);
v___x_7553_ = lp_competition_Submission_Packed10_finish(v_n_7501_, v___x_7518_, v___x_7521_, v_p_7502_, v_A_7503_, v_B_7504_, v_s4_7552_);
lean_dec(v___x_7521_);
lean_dec(v___x_7518_);
return v___x_7553_;
}
}
else
{
float v_s3_7554_; uint32_t v___x_7555_; 
lean_dec(v___x_7515_);
v_s3_7554_ = lean_ctor_get_float32(v___x_7524_, 12);
v___x_7555_ = lp_competition_Submission_Packed10_finish(v_n_7501_, v___x_7518_, v___x_7521_, v_p_7502_, v_A_7503_, v_B_7504_, v_s3_7554_);
lean_dec(v___x_7521_);
lean_dec(v___x_7518_);
return v___x_7555_;
}
}
else
{
float v_s2_7556_; uint32_t v___x_7557_; 
lean_dec(v___x_7515_);
v_s2_7556_ = lean_ctor_get_float32(v___x_7524_, 8);
v___x_7557_ = lp_competition_Submission_Packed10_finish(v_n_7501_, v___x_7518_, v___x_7521_, v_p_7502_, v_A_7503_, v_B_7504_, v_s2_7556_);
lean_dec(v___x_7521_);
lean_dec(v___x_7518_);
return v___x_7557_;
}
}
else
{
float v_s1_7558_; uint32_t v___x_7559_; 
lean_dec(v___x_7515_);
v_s1_7558_ = lean_ctor_get_float32(v___x_7524_, 4);
v___x_7559_ = lp_competition_Submission_Packed10_finish(v_n_7501_, v___x_7518_, v___x_7521_, v_p_7502_, v_A_7503_, v_B_7504_, v_s1_7558_);
lean_dec(v___x_7521_);
lean_dec(v___x_7518_);
return v___x_7559_;
}
}
else
{
float v_s0_7560_; uint32_t v___x_7561_; 
lean_dec(v___x_7515_);
v_s0_7560_ = lean_ctor_get_float32(v___x_7524_, 0);
v___x_7561_ = lp_competition_Submission_Packed10_finish(v_n_7501_, v___x_7518_, v___x_7521_, v_p_7502_, v_A_7503_, v_B_7504_, v_s0_7560_);
lean_dec(v___x_7521_);
lean_dec(v___x_7518_);
return v___x_7561_;
}
}
v___jp_7564_:
{
if (v___x_7563_ == 0)
{
lean_object* v___x_7568_; 
v___x_7568_ = lean_nat_mod(v___y_7566_, v_p_7502_);
lean_dec(v___y_7566_);
v___y_7510_ = v___y_7565_;
v___y_7511_ = v___y_7567_;
v___y_7512_ = v___x_7568_;
goto v___jp_7509_;
}
else
{
lean_dec(v___y_7566_);
v___y_7510_ = v___y_7565_;
v___y_7511_ = v___y_7567_;
v___y_7512_ = v___x_7508_;
goto v___jp_7509_;
}
}
v___jp_7569_:
{
if (v___x_7563_ == 0)
{
lean_object* v___x_7572_; 
v___x_7572_ = lean_nat_div(v___y_7571_, v_p_7502_);
v___y_7565_ = v___y_7570_;
v___y_7566_ = v___y_7571_;
v___y_7567_ = v___x_7572_;
goto v___jp_7564_;
}
else
{
v___y_7565_ = v___y_7570_;
v___y_7566_ = v___y_7571_;
v___y_7567_ = v___x_7508_;
goto v___jp_7564_;
}
}
v___jp_7573_:
{
if (v___x_7562_ == 0)
{
lean_object* v___x_7575_; 
v___x_7575_ = lean_nat_mod(v_q_7506_, v_rowSize_7507_);
lean_dec(v_rowSize_7507_);
v___y_7570_ = v___y_7574_;
v___y_7571_ = v___x_7575_;
goto v___jp_7569_;
}
else
{
lean_dec(v_rowSize_7507_);
v___y_7570_ = v___y_7574_;
v___y_7571_ = v___x_7508_;
goto v___jp_7569_;
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_Packed10_outputFromTiles___redArg___boxed(lean_object* v_m_7577_, lean_object* v_n_7578_, lean_object* v_p_7579_, lean_object* v_A_7580_, lean_object* v_B_7581_, lean_object* v_tiles_7582_, lean_object* v_q_7583_){
_start:
{
uint32_t v_res_7584_; lean_object* v_r_7585_; 
v_res_7584_ = lp_competition_Submission_Packed10_outputFromTiles___redArg(v_m_7577_, v_n_7578_, v_p_7579_, v_A_7580_, v_B_7581_, v_tiles_7582_, v_q_7583_);
lean_dec(v_q_7583_);
lean_dec_ref(v_tiles_7582_);
lean_dec_ref(v_B_7581_);
lean_dec_ref(v_A_7580_);
lean_dec(v_p_7579_);
lean_dec(v_n_7578_);
lean_dec(v_m_7577_);
v_r_7585_ = lean_box_uint32(v_res_7584_);
return v_r_7585_;
}
}
LEAN_EXPORT uint32_t lp_competition_Submission_Packed10_outputFromTiles(lean_object* v_batch_7586_, lean_object* v_m_7587_, lean_object* v_n_7588_, lean_object* v_p_7589_, lean_object* v_A_7590_, lean_object* v_B_7591_, lean_object* v_tiles_7592_, lean_object* v_q_7593_){
_start:
{
uint32_t v___x_7594_; 
v___x_7594_ = lp_competition_Submission_Packed10_outputFromTiles___redArg(v_m_7587_, v_n_7588_, v_p_7589_, v_A_7590_, v_B_7591_, v_tiles_7592_, v_q_7593_);
return v___x_7594_;
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_Packed10_outputFromTiles___boxed(lean_object* v_batch_7595_, lean_object* v_m_7596_, lean_object* v_n_7597_, lean_object* v_p_7598_, lean_object* v_A_7599_, lean_object* v_B_7600_, lean_object* v_tiles_7601_, lean_object* v_q_7602_){
_start:
{
uint32_t v_res_7603_; lean_object* v_r_7604_; 
v_res_7603_ = lp_competition_Submission_Packed10_outputFromTiles(v_batch_7595_, v_m_7596_, v_n_7597_, v_p_7598_, v_A_7599_, v_B_7600_, v_tiles_7601_, v_q_7602_);
lean_dec(v_q_7602_);
lean_dec_ref(v_tiles_7601_);
lean_dec_ref(v_B_7600_);
lean_dec_ref(v_A_7599_);
lean_dec(v_p_7598_);
lean_dec(v_n_7597_);
lean_dec(v_m_7596_);
lean_dec(v_batch_7595_);
v_r_7604_ = lean_box_uint32(v_res_7603_);
return v_r_7604_;
}
}
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_mapMUnsafe_map___at___00Submission_Packed10_core_spec__0(size_t v_sz_7605_, size_t v_i_7606_, lean_object* v_bs_7607_){
_start:
{
uint8_t v___x_7608_; 
v___x_7608_ = lean_usize_dec_lt(v_i_7606_, v_sz_7605_);
if (v___x_7608_ == 0)
{
return v_bs_7607_;
}
else
{
lean_object* v_v_7609_; lean_object* v___x_7610_; lean_object* v_bs_x27_7611_; uint32_t v___x_7612_; float v___x_7613_; size_t v___x_7614_; size_t v___x_7615_; lean_object* v___x_7616_; lean_object* v___x_7617_; 
v_v_7609_ = lean_array_uget(v_bs_7607_, v_i_7606_);
v___x_7610_ = lean_unsigned_to_nat(0u);
v_bs_x27_7611_ = lean_array_uset(v_bs_7607_, v_i_7606_, v___x_7610_);
v___x_7612_ = lean_unbox_uint32(v_v_7609_);
lean_dec(v_v_7609_);
v___x_7613_ = lean_float32_of_bits(v___x_7612_);
v___x_7614_ = ((size_t)1ULL);
v___x_7615_ = lean_usize_add(v_i_7606_, v___x_7614_);
v___x_7616_ = lean_box_float32(v___x_7613_);
v___x_7617_ = lean_array_uset(v_bs_x27_7611_, v_i_7606_, v___x_7616_);
v_i_7606_ = v___x_7615_;
v_bs_7607_ = v___x_7617_;
goto _start;
}
}
}
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_mapMUnsafe_map___at___00Submission_Packed10_core_spec__0___boxed(lean_object* v_sz_7619_, lean_object* v_i_7620_, lean_object* v_bs_7621_){
_start:
{
size_t v_sz_boxed_7622_; size_t v_i_boxed_7623_; lean_object* v_res_7624_; 
v_sz_boxed_7622_ = lean_unbox_usize(v_sz_7619_);
lean_dec(v_sz_7619_);
v_i_boxed_7623_ = lean_unbox_usize(v_i_7620_);
lean_dec(v_i_7620_);
v_res_7624_ = lp_competition___private_Init_Data_Array_Basic_0__Array_mapMUnsafe_map___at___00Submission_Packed10_core_spec__0(v_sz_boxed_7622_, v_i_boxed_7623_, v_bs_7621_);
return v_res_7624_;
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_Packed10_core(lean_object* v_batch_7625_, lean_object* v_m_7626_, lean_object* v_n_7627_, lean_object* v_p_7628_, lean_object* v_A_7629_, lean_object* v_B_7630_){
_start:
{
size_t v_sz_7631_; size_t v___x_7632_; lean_object* v_nativeA_7633_; lean_object* v_packedB_7634_; lean_object* v_tiles_7635_; lean_object* v___x_7636_; lean_object* v___x_7637_; lean_object* v___x_7638_; lean_object* v___x_7639_; 
v_sz_7631_ = lean_array_size(v_A_7629_);
v___x_7632_ = ((size_t)0ULL);
lean_inc_ref(v_A_7629_);
v_nativeA_7633_ = lp_competition___private_Init_Data_Array_Basic_0__Array_mapMUnsafe_map___at___00Submission_Packed10_core_spec__0(v_sz_7631_, v___x_7632_, v_A_7629_);
lean_inc_ref(v_B_7630_);
lean_inc_n(v_p_7628_, 2);
lean_inc_n(v_n_7627_, 2);
lean_inc_n(v_batch_7625_, 2);
v_packedB_7634_ = lp_competition_Submission_Packed10_packB(v_batch_7625_, v_n_7627_, v_p_7628_, v_B_7630_);
lean_inc(v_m_7626_);
v_tiles_7635_ = lp_competition_Submission_Packed10_tileResults(v_batch_7625_, v_m_7626_, v_n_7627_, v_p_7628_, v_nativeA_7633_, v_packedB_7634_);
v___x_7636_ = lean_nat_mul(v_batch_7625_, v_m_7626_);
v___x_7637_ = lean_nat_mul(v___x_7636_, v_p_7628_);
lean_dec(v___x_7636_);
v___x_7638_ = lean_alloc_closure((void*)(lp_competition_Submission_Packed10_outputFromTiles___boxed), 8, 7);
lean_closure_set(v___x_7638_, 0, v_batch_7625_);
lean_closure_set(v___x_7638_, 1, v_m_7626_);
lean_closure_set(v___x_7638_, 2, v_n_7627_);
lean_closure_set(v___x_7638_, 3, v_p_7628_);
lean_closure_set(v___x_7638_, 4, v_A_7629_);
lean_closure_set(v___x_7638_, 5, v_B_7630_);
lean_closure_set(v___x_7638_, 6, v_tiles_7635_);
v___x_7639_ = l_Array_ofFn___redArg(v___x_7637_, v___x_7638_);
return v___x_7639_;
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_bmmR4(lean_object* v_batch_7640_, lean_object* v_m_7641_, lean_object* v_n_7642_, lean_object* v_p_7643_, lean_object* v_A_7644_, lean_object* v_B_7645_){
_start:
{
lean_object* v___x_7646_; lean_object* v___x_7647_; lean_object* v___x_7648_; uint8_t v___x_7649_; 
v___x_7646_ = lean_nat_mul(v_batch_7640_, v_m_7641_);
v___x_7647_ = lean_nat_mul(v___x_7646_, v_p_7643_);
lean_dec(v___x_7646_);
v___x_7648_ = lean_unsigned_to_nat(0u);
v___x_7649_ = lean_nat_dec_eq(v___x_7647_, v___x_7648_);
lean_dec(v___x_7647_);
if (v___x_7649_ == 0)
{
uint8_t v___x_7650_; 
v___x_7650_ = lean_nat_dec_eq(v_n_7642_, v___x_7648_);
if (v___x_7650_ == 0)
{
lean_object* v___x_7651_; 
v___x_7651_ = lp_competition_Submission_Packed10_core(v_batch_7640_, v_m_7641_, v_n_7642_, v_p_7643_, v_A_7644_, v_B_7645_);
return v___x_7651_;
}
else
{
lean_object* v___x_7652_; 
v___x_7652_ = lp_competition_Submission_referenceBmm(v_batch_7640_, v_m_7641_, v_n_7642_, v_p_7643_, v_A_7644_, v_B_7645_);
lean_dec(v_batch_7640_);
return v___x_7652_;
}
}
else
{
lean_object* v___x_7653_; 
v___x_7653_ = lp_competition_Submission_referenceBmm(v_batch_7640_, v_m_7641_, v_n_7642_, v_p_7643_, v_A_7644_, v_B_7645_);
lean_dec(v_batch_7640_);
return v___x_7653_;
}
}
}
LEAN_EXPORT float lp_competition_Submission_NativeDecodeSum_decode(uint32_t v_x_7654_){
_start:
{
uint8_t v___y_7656_; uint32_t v___x_7670_; uint32_t v_a_7671_; uint32_t v___x_7672_; uint32_t v___x_7673_; uint32_t v___x_7674_; uint8_t v___x_7675_; 
v___x_7670_ = 2147483647;
v_a_7671_ = lean_uint32_land(v_x_7654_, v___x_7670_);
v___x_7672_ = 201326591;
v___x_7673_ = 1;
v___x_7674_ = lean_uint32_sub(v_a_7671_, v___x_7673_);
v___x_7675_ = lean_uint32_dec_le(v___x_7672_, v___x_7674_);
if (v___x_7675_ == 0)
{
v___y_7656_ = v___x_7675_;
goto v___jp_7655_;
}
else
{
uint32_t v___x_7676_; uint8_t v___x_7677_; 
v___x_7676_ = 2139095040;
v___x_7677_ = lean_uint32_dec_lt(v_a_7671_, v___x_7676_);
v___y_7656_ = v___x_7677_;
goto v___jp_7655_;
}
v___jp_7655_:
{
if (v___y_7656_ == 0)
{
float v___x_7657_; 
v___x_7657_ = lean_float32_of_bits(v_x_7654_);
return v___x_7657_;
}
else
{
uint32_t v___x_7658_; uint32_t v___x_7659_; uint32_t v___x_7660_; uint32_t v___x_7661_; float v___x_7662_; lean_object* v___x_7663_; uint32_t v___x_7664_; uint32_t v___x_7665_; lean_object* v___x_7666_; lean_object* v___x_7667_; float v___x_7668_; float v___x_7669_; 
v___x_7658_ = 8388607;
v___x_7659_ = lean_uint32_land(v_x_7654_, v___x_7658_);
v___x_7660_ = 8388608;
v___x_7661_ = lean_uint32_lor(v___x_7659_, v___x_7660_);
v___x_7662_ = lean_uint32_to_float32(v___x_7661_);
v___x_7663_ = lp_competition_R2W01b_scaleTable;
v___x_7664_ = 23;
v___x_7665_ = lean_uint32_shift_right(v_x_7654_, v___x_7664_);
v___x_7666_ = lean_uint32_to_nat(v___x_7665_);
v___x_7667_ = lean_array_fget_borrowed(v___x_7663_, v___x_7666_);
lean_dec(v___x_7666_);
v___x_7668_ = lean_unbox_float32(v___x_7667_);
v___x_7669_ = lean_float32_mul(v___x_7662_, v___x_7668_);
return v___x_7669_;
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_NativeDecodeSum_decode___boxed(lean_object* v_x_7678_){
_start:
{
uint32_t v_x_boxed_7679_; float v_res_7680_; lean_object* v_r_7681_; 
v_x_boxed_7679_ = lean_unbox_uint32(v_x_7678_);
lean_dec(v_x_7678_);
v_res_7680_ = lp_competition_Submission_NativeDecodeSum_decode(v_x_boxed_7679_);
v_r_7681_ = lean_box_float32(v_res_7680_);
return v_r_7681_;
}
}
LEAN_EXPORT float lp_competition_Submission_NativeDecodeSum_loop(lean_object* v_n_7682_, lean_object* v_x_7683_, lean_object* v_k_7684_, float v_acc_7685_){
_start:
{
uint8_t v___x_7686_; 
v___x_7686_ = lean_nat_dec_lt(v_k_7684_, v_n_7682_);
if (v___x_7686_ == 0)
{
lean_dec(v_k_7684_);
return v_acc_7685_;
}
else
{
lean_object* v___x_7687_; lean_object* v___x_7688_; float v___y_7690_; lean_object* v___x_7693_; uint8_t v___y_7695_; uint32_t v___x_7712_; uint32_t v___x_7713_; uint32_t v_a_7714_; uint32_t v___x_7715_; uint32_t v___x_7716_; uint32_t v___x_7717_; uint8_t v___x_7718_; 
v___x_7687_ = lean_unsigned_to_nat(1u);
v___x_7688_ = lean_nat_add(v_k_7684_, v___x_7687_);
v___x_7693_ = lean_array_fget_borrowed(v_x_7683_, v_k_7684_);
lean_dec(v_k_7684_);
v___x_7712_ = 2147483647;
v___x_7713_ = lean_unbox_uint32(v___x_7693_);
v_a_7714_ = lean_uint32_land(v___x_7713_, v___x_7712_);
v___x_7715_ = 201326591;
v___x_7716_ = 1;
v___x_7717_ = lean_uint32_sub(v_a_7714_, v___x_7716_);
v___x_7718_ = lean_uint32_dec_le(v___x_7715_, v___x_7717_);
if (v___x_7718_ == 0)
{
v___y_7695_ = v___x_7718_;
goto v___jp_7694_;
}
else
{
uint32_t v___x_7719_; uint8_t v___x_7720_; 
v___x_7719_ = 2139095040;
v___x_7720_ = lean_uint32_dec_lt(v_a_7714_, v___x_7719_);
v___y_7695_ = v___x_7720_;
goto v___jp_7694_;
}
v___jp_7689_:
{
float v___x_7691_; 
v___x_7691_ = lean_float32_add(v_acc_7685_, v___y_7690_);
v_k_7684_ = v___x_7688_;
v_acc_7685_ = v___x_7691_;
goto _start;
}
v___jp_7694_:
{
if (v___y_7695_ == 0)
{
uint32_t v___x_7696_; float v___x_7697_; 
v___x_7696_ = lean_unbox_uint32(v___x_7693_);
v___x_7697_ = lean_float32_of_bits(v___x_7696_);
v___y_7690_ = v___x_7697_;
goto v___jp_7689_;
}
else
{
uint32_t v___x_7698_; uint32_t v___x_7699_; uint32_t v___x_7700_; uint32_t v___x_7701_; uint32_t v___x_7702_; float v___x_7703_; lean_object* v___x_7704_; uint32_t v___x_7705_; uint32_t v___x_7706_; uint32_t v___x_7707_; lean_object* v___x_7708_; lean_object* v___x_7709_; float v___x_7710_; float v___x_7711_; 
v___x_7698_ = 8388607;
v___x_7699_ = lean_unbox_uint32(v___x_7693_);
v___x_7700_ = lean_uint32_land(v___x_7699_, v___x_7698_);
v___x_7701_ = 8388608;
v___x_7702_ = lean_uint32_lor(v___x_7700_, v___x_7701_);
v___x_7703_ = lean_uint32_to_float32(v___x_7702_);
v___x_7704_ = lp_competition_R2W01b_scaleTable;
v___x_7705_ = 23;
v___x_7706_ = lean_unbox_uint32(v___x_7693_);
v___x_7707_ = lean_uint32_shift_right(v___x_7706_, v___x_7705_);
v___x_7708_ = lean_uint32_to_nat(v___x_7707_);
v___x_7709_ = lean_array_fget_borrowed(v___x_7704_, v___x_7708_);
lean_dec(v___x_7708_);
v___x_7710_ = lean_unbox_float32(v___x_7709_);
v___x_7711_ = lean_float32_mul(v___x_7703_, v___x_7710_);
v___y_7690_ = v___x_7711_;
goto v___jp_7689_;
}
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_NativeDecodeSum_loop___boxed(lean_object* v_n_7721_, lean_object* v_x_7722_, lean_object* v_k_7723_, lean_object* v_acc_7724_){
_start:
{
float v_acc_boxed_7725_; float v_res_7726_; lean_object* v_r_7727_; 
v_acc_boxed_7725_ = lean_unbox_float32(v_acc_7724_);
lean_dec_ref(v_acc_7724_);
v_res_7726_ = lp_competition_Submission_NativeDecodeSum_loop(v_n_7721_, v_x_7722_, v_k_7723_, v_acc_boxed_7725_);
lean_dec_ref(v_x_7722_);
lean_dec(v_n_7721_);
v_r_7727_ = lean_box_float32(v_res_7726_);
return v_r_7727_;
}
}
LEAN_EXPORT float lp_competition_Submission_NativeDecodeSumWord_loop___redArg(lean_object* v_x_7728_, size_t v_count_7729_, size_t v_k_7730_, float v_acc_7731_){
_start:
{
uint8_t v___x_7732_; 
v___x_7732_ = lean_usize_dec_lt(v_k_7730_, v_count_7729_);
if (v___x_7732_ == 0)
{
return v_acc_7731_;
}
else
{
lean_object* v_value_7733_; size_t v___x_7734_; size_t v___x_7735_; float v___y_7737_; uint8_t v___y_7741_; uint32_t v___x_7758_; uint32_t v___x_7759_; uint32_t v_a_7760_; uint32_t v___x_7761_; uint32_t v___x_7762_; uint32_t v___x_7763_; uint8_t v___x_7764_; 
v_value_7733_ = lean_array_uget_borrowed(v_x_7728_, v_k_7730_);
v___x_7734_ = ((size_t)1ULL);
v___x_7735_ = lean_usize_add(v_k_7730_, v___x_7734_);
v___x_7758_ = 2147483647;
v___x_7759_ = lean_unbox_uint32(v_value_7733_);
v_a_7760_ = lean_uint32_land(v___x_7759_, v___x_7758_);
v___x_7761_ = 201326591;
v___x_7762_ = 1;
v___x_7763_ = lean_uint32_sub(v_a_7760_, v___x_7762_);
v___x_7764_ = lean_uint32_dec_le(v___x_7761_, v___x_7763_);
if (v___x_7764_ == 0)
{
v___y_7741_ = v___x_7764_;
goto v___jp_7740_;
}
else
{
uint32_t v___x_7765_; uint8_t v___x_7766_; 
v___x_7765_ = 2139095040;
v___x_7766_ = lean_uint32_dec_lt(v_a_7760_, v___x_7765_);
v___y_7741_ = v___x_7766_;
goto v___jp_7740_;
}
v___jp_7736_:
{
float v___x_7738_; 
v___x_7738_ = lean_float32_add(v_acc_7731_, v___y_7737_);
v_k_7730_ = v___x_7735_;
v_acc_7731_ = v___x_7738_;
goto _start;
}
v___jp_7740_:
{
if (v___y_7741_ == 0)
{
uint32_t v___x_7742_; float v___x_7743_; 
v___x_7742_ = lean_unbox_uint32(v_value_7733_);
v___x_7743_ = lean_float32_of_bits(v___x_7742_);
v___y_7737_ = v___x_7743_;
goto v___jp_7736_;
}
else
{
uint32_t v___x_7744_; uint32_t v___x_7745_; uint32_t v___x_7746_; uint32_t v___x_7747_; uint32_t v___x_7748_; float v___x_7749_; lean_object* v___x_7750_; uint32_t v___x_7751_; uint32_t v___x_7752_; uint32_t v___x_7753_; lean_object* v___x_7754_; lean_object* v___x_7755_; float v___x_7756_; float v___x_7757_; 
v___x_7744_ = 8388607;
v___x_7745_ = lean_unbox_uint32(v_value_7733_);
v___x_7746_ = lean_uint32_land(v___x_7745_, v___x_7744_);
v___x_7747_ = 8388608;
v___x_7748_ = lean_uint32_lor(v___x_7746_, v___x_7747_);
v___x_7749_ = lean_uint32_to_float32(v___x_7748_);
v___x_7750_ = lp_competition_R2W01b_scaleTable;
v___x_7751_ = 23;
v___x_7752_ = lean_unbox_uint32(v_value_7733_);
v___x_7753_ = lean_uint32_shift_right(v___x_7752_, v___x_7751_);
v___x_7754_ = lean_uint32_to_nat(v___x_7753_);
v___x_7755_ = lean_array_fget_borrowed(v___x_7750_, v___x_7754_);
lean_dec(v___x_7754_);
v___x_7756_ = lean_unbox_float32(v___x_7755_);
v___x_7757_ = lean_float32_mul(v___x_7749_, v___x_7756_);
v___y_7737_ = v___x_7757_;
goto v___jp_7736_;
}
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_NativeDecodeSumWord_loop___redArg___boxed(lean_object* v_x_7767_, lean_object* v_count_7768_, lean_object* v_k_7769_, lean_object* v_acc_7770_){
_start:
{
size_t v_count_boxed_7771_; size_t v_k_boxed_7772_; float v_acc_boxed_7773_; float v_res_7774_; lean_object* v_r_7775_; 
v_count_boxed_7771_ = lean_unbox_usize(v_count_7768_);
lean_dec(v_count_7768_);
v_k_boxed_7772_ = lean_unbox_usize(v_k_7769_);
lean_dec(v_k_7769_);
v_acc_boxed_7773_ = lean_unbox_float32(v_acc_7770_);
lean_dec_ref(v_acc_7770_);
v_res_7774_ = lp_competition_Submission_NativeDecodeSumWord_loop___redArg(v_x_7767_, v_count_boxed_7771_, v_k_boxed_7772_, v_acc_boxed_7773_);
lean_dec_ref(v_x_7767_);
v_r_7775_ = lean_box_float32(v_res_7774_);
return v_r_7775_;
}
}
LEAN_EXPORT float lp_competition_Submission_NativeDecodeSumWord_loop(lean_object* v_n_7776_, lean_object* v_x_7777_, size_t v_count_7778_, lean_object* v_hn_7779_, size_t v_k_7780_, float v_acc_7781_){
_start:
{
float v___x_7782_; 
v___x_7782_ = lp_competition_Submission_NativeDecodeSumWord_loop___redArg(v_x_7777_, v_count_7778_, v_k_7780_, v_acc_7781_);
return v___x_7782_;
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_NativeDecodeSumWord_loop___boxed(lean_object* v_n_7783_, lean_object* v_x_7784_, lean_object* v_count_7785_, lean_object* v_hn_7786_, lean_object* v_k_7787_, lean_object* v_acc_7788_){
_start:
{
size_t v_count_boxed_7789_; size_t v_k_boxed_7790_; float v_acc_boxed_7791_; float v_res_7792_; lean_object* v_r_7793_; 
v_count_boxed_7789_ = lean_unbox_usize(v_count_7785_);
lean_dec(v_count_7785_);
v_k_boxed_7790_ = lean_unbox_usize(v_k_7787_);
lean_dec(v_k_7787_);
v_acc_boxed_7791_ = lean_unbox_float32(v_acc_7788_);
lean_dec_ref(v_acc_7788_);
v_res_7792_ = lp_competition_Submission_NativeDecodeSumWord_loop(v_n_7783_, v_x_7784_, v_count_boxed_7789_, v_hn_7786_, v_k_boxed_7790_, v_acc_boxed_7791_);
lean_dec_ref(v_x_7784_);
lean_dec(v_n_7783_);
v_r_7793_ = lean_box_float32(v_res_7792_);
return v_r_7793_;
}
}
LEAN_EXPORT float lp_competition_Submission_NativeDecodeSumWord_run(lean_object* v_n_7794_, lean_object* v_x_7795_){
_start:
{
lean_object* v___x_7796_; uint8_t v___x_7797_; 
v___x_7796_ = lean_obj_once(&lp_competition_Submission_Packed10Index_runDot___closed__0, &lp_competition_Submission_Packed10Index_runDot___closed__0_once, _init_lp_competition_Submission_Packed10Index_runDot___closed__0);
v___x_7797_ = lean_nat_dec_lt(v_n_7794_, v___x_7796_);
if (v___x_7797_ == 0)
{
lean_object* v___x_7798_; float v___x_7799_; float v___x_7800_; 
v___x_7798_ = lean_unsigned_to_nat(0u);
v___x_7799_ = lean_float32_once(&lp_competition_Submission_NativeFinal_dot___closed__0, &lp_competition_Submission_NativeFinal_dot___closed__0_once, _init_lp_competition_Submission_NativeFinal_dot___closed__0);
v___x_7800_ = lp_competition_Submission_NativeDecodeSum_loop(v_n_7794_, v_x_7795_, v___x_7798_, v___x_7799_);
return v___x_7800_;
}
else
{
size_t v___x_7801_; size_t v___x_7802_; float v___x_7803_; float v___x_7804_; 
v___x_7801_ = lean_usize_of_nat(v_n_7794_);
v___x_7802_ = ((size_t)0ULL);
v___x_7803_ = lean_float32_once(&lp_competition_Submission_NativeFinal_dot___closed__0, &lp_competition_Submission_NativeFinal_dot___closed__0_once, _init_lp_competition_Submission_NativeFinal_dot___closed__0);
v___x_7804_ = lp_competition_Submission_NativeDecodeSumWord_loop___redArg(v_x_7795_, v___x_7801_, v___x_7802_, v___x_7803_);
return v___x_7804_;
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_NativeDecodeSumWord_run___boxed(lean_object* v_n_7805_, lean_object* v_x_7806_){
_start:
{
float v_res_7807_; lean_object* v_r_7808_; 
v_res_7807_ = lp_competition_Submission_NativeDecodeSumWord_run(v_n_7805_, v_x_7806_);
lean_dec_ref(v_x_7806_);
lean_dec(v_n_7805_);
v_r_7808_ = lean_box_float32(v_res_7807_);
return v_r_7808_;
}
}
LEAN_EXPORT uint32_t lp_competition_Submission_sum(lean_object* v_n_7809_, lean_object* v_x_7810_){
_start:
{
float v___y_7812_; lean_object* v___x_7816_; uint8_t v___x_7817_; 
v___x_7816_ = lean_obj_once(&lp_competition_Submission_Packed10Index_runDot___closed__0, &lp_competition_Submission_Packed10Index_runDot___closed__0_once, _init_lp_competition_Submission_Packed10Index_runDot___closed__0);
v___x_7817_ = lean_nat_dec_lt(v_n_7809_, v___x_7816_);
if (v___x_7817_ == 0)
{
lean_object* v___x_7818_; float v___x_7819_; float v___x_7820_; 
v___x_7818_ = lean_unsigned_to_nat(0u);
v___x_7819_ = lean_float32_once(&lp_competition_Submission_NativeFinal_dot___closed__0, &lp_competition_Submission_NativeFinal_dot___closed__0_once, _init_lp_competition_Submission_NativeFinal_dot___closed__0);
v___x_7820_ = lp_competition_Submission_NativeDecodeSum_loop(v_n_7809_, v_x_7810_, v___x_7818_, v___x_7819_);
v___y_7812_ = v___x_7820_;
goto v___jp_7811_;
}
else
{
size_t v___x_7821_; size_t v___x_7822_; float v___x_7823_; float v___x_7824_; 
v___x_7821_ = lean_usize_of_nat(v_n_7809_);
v___x_7822_ = ((size_t)0ULL);
v___x_7823_ = lean_float32_once(&lp_competition_Submission_NativeFinal_dot___closed__0, &lp_competition_Submission_NativeFinal_dot___closed__0_once, _init_lp_competition_Submission_NativeFinal_dot___closed__0);
v___x_7824_ = lp_competition_Submission_NativeDecodeSumWord_loop___redArg(v_x_7810_, v___x_7821_, v___x_7822_, v___x_7823_);
v___y_7812_ = v___x_7824_;
goto v___jp_7811_;
}
v___jp_7811_:
{
uint8_t v___x_7813_; 
v___x_7813_ = lean_float32_isfinite(v___y_7812_);
if (v___x_7813_ == 0)
{
uint32_t v___x_7814_; 
v___x_7814_ = lp_competition_Submission_referenceSum___redArg(v_x_7810_);
return v___x_7814_;
}
else
{
uint32_t v___x_7815_; 
v___x_7815_ = lean_float32_to_bits(v___y_7812_);
return v___x_7815_;
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_sum___boxed(lean_object* v_n_7825_, lean_object* v_x_7826_){
_start:
{
uint32_t v_res_7827_; lean_object* v_r_7828_; 
v_res_7827_ = lp_competition_Submission_sum(v_n_7825_, v_x_7826_);
lean_dec_ref(v_x_7826_);
lean_dec(v_n_7825_);
v_r_7828_ = lean_box_uint32(v_res_7827_);
return v_r_7828_;
}
}
LEAN_EXPORT uint32_t lp_competition_Submission_RowOutput_row___redArg___lam__0(lean_object* v_baseB_7829_, lean_object* v_tiles_7830_, lean_object* v_n_7831_, lean_object* v_baseA_7832_, lean_object* v_p_7833_, lean_object* v_A_7834_, lean_object* v_B_7835_, lean_object* v_j_7836_){
_start:
{
lean_object* v___x_7837_; lean_object* v___x_7838_; lean_object* v___x_7839_; lean_object* v___x_7840_; lean_object* v___x_7841_; lean_object* v___x_7842_; uint8_t v___x_7843_; 
v___x_7837_ = lean_unsigned_to_nat(10u);
v___x_7838_ = lean_nat_div(v_j_7836_, v___x_7837_);
v___x_7839_ = lean_nat_mod(v_j_7836_, v___x_7837_);
v___x_7840_ = lean_nat_add(v_baseB_7829_, v_j_7836_);
v___x_7841_ = lean_array_fget_borrowed(v_tiles_7830_, v___x_7838_);
lean_dec(v___x_7838_);
v___x_7842_ = lean_unsigned_to_nat(0u);
v___x_7843_ = lean_nat_dec_eq(v___x_7839_, v___x_7842_);
if (v___x_7843_ == 0)
{
lean_object* v___x_7844_; uint8_t v___x_7845_; 
v___x_7844_ = lean_unsigned_to_nat(1u);
v___x_7845_ = lean_nat_dec_eq(v___x_7839_, v___x_7844_);
if (v___x_7845_ == 0)
{
lean_object* v___x_7846_; uint8_t v___x_7847_; 
v___x_7846_ = lean_unsigned_to_nat(2u);
v___x_7847_ = lean_nat_dec_eq(v___x_7839_, v___x_7846_);
if (v___x_7847_ == 0)
{
lean_object* v___x_7848_; uint8_t v___x_7849_; 
v___x_7848_ = lean_unsigned_to_nat(3u);
v___x_7849_ = lean_nat_dec_eq(v___x_7839_, v___x_7848_);
if (v___x_7849_ == 0)
{
lean_object* v___x_7850_; uint8_t v___x_7851_; 
v___x_7850_ = lean_unsigned_to_nat(4u);
v___x_7851_ = lean_nat_dec_eq(v___x_7839_, v___x_7850_);
if (v___x_7851_ == 0)
{
lean_object* v___x_7852_; uint8_t v___x_7853_; 
v___x_7852_ = lean_unsigned_to_nat(5u);
v___x_7853_ = lean_nat_dec_eq(v___x_7839_, v___x_7852_);
if (v___x_7853_ == 0)
{
lean_object* v___x_7854_; uint8_t v___x_7855_; 
v___x_7854_ = lean_unsigned_to_nat(6u);
v___x_7855_ = lean_nat_dec_eq(v___x_7839_, v___x_7854_);
if (v___x_7855_ == 0)
{
lean_object* v___x_7856_; uint8_t v___x_7857_; 
v___x_7856_ = lean_unsigned_to_nat(7u);
v___x_7857_ = lean_nat_dec_eq(v___x_7839_, v___x_7856_);
if (v___x_7857_ == 0)
{
lean_object* v___x_7858_; uint8_t v___x_7859_; 
v___x_7858_ = lean_unsigned_to_nat(8u);
v___x_7859_ = lean_nat_dec_eq(v___x_7839_, v___x_7858_);
lean_dec(v___x_7839_);
if (v___x_7859_ == 0)
{
float v_s9_7860_; uint32_t v___x_7861_; 
v_s9_7860_ = lean_ctor_get_float32(v___x_7841_, 36);
v___x_7861_ = lp_competition_Submission_Packed10_finish(v_n_7831_, v_baseA_7832_, v___x_7840_, v_p_7833_, v_A_7834_, v_B_7835_, v_s9_7860_);
lean_dec(v___x_7840_);
return v___x_7861_;
}
else
{
float v_s8_7862_; uint32_t v___x_7863_; 
v_s8_7862_ = lean_ctor_get_float32(v___x_7841_, 32);
v___x_7863_ = lp_competition_Submission_Packed10_finish(v_n_7831_, v_baseA_7832_, v___x_7840_, v_p_7833_, v_A_7834_, v_B_7835_, v_s8_7862_);
lean_dec(v___x_7840_);
return v___x_7863_;
}
}
else
{
float v_s7_7864_; uint32_t v___x_7865_; 
lean_dec(v___x_7839_);
v_s7_7864_ = lean_ctor_get_float32(v___x_7841_, 28);
v___x_7865_ = lp_competition_Submission_Packed10_finish(v_n_7831_, v_baseA_7832_, v___x_7840_, v_p_7833_, v_A_7834_, v_B_7835_, v_s7_7864_);
lean_dec(v___x_7840_);
return v___x_7865_;
}
}
else
{
float v_s6_7866_; uint32_t v___x_7867_; 
lean_dec(v___x_7839_);
v_s6_7866_ = lean_ctor_get_float32(v___x_7841_, 24);
v___x_7867_ = lp_competition_Submission_Packed10_finish(v_n_7831_, v_baseA_7832_, v___x_7840_, v_p_7833_, v_A_7834_, v_B_7835_, v_s6_7866_);
lean_dec(v___x_7840_);
return v___x_7867_;
}
}
else
{
float v_s5_7868_; uint32_t v___x_7869_; 
lean_dec(v___x_7839_);
v_s5_7868_ = lean_ctor_get_float32(v___x_7841_, 20);
v___x_7869_ = lp_competition_Submission_Packed10_finish(v_n_7831_, v_baseA_7832_, v___x_7840_, v_p_7833_, v_A_7834_, v_B_7835_, v_s5_7868_);
lean_dec(v___x_7840_);
return v___x_7869_;
}
}
else
{
float v_s4_7870_; uint32_t v___x_7871_; 
lean_dec(v___x_7839_);
v_s4_7870_ = lean_ctor_get_float32(v___x_7841_, 16);
v___x_7871_ = lp_competition_Submission_Packed10_finish(v_n_7831_, v_baseA_7832_, v___x_7840_, v_p_7833_, v_A_7834_, v_B_7835_, v_s4_7870_);
lean_dec(v___x_7840_);
return v___x_7871_;
}
}
else
{
float v_s3_7872_; uint32_t v___x_7873_; 
lean_dec(v___x_7839_);
v_s3_7872_ = lean_ctor_get_float32(v___x_7841_, 12);
v___x_7873_ = lp_competition_Submission_Packed10_finish(v_n_7831_, v_baseA_7832_, v___x_7840_, v_p_7833_, v_A_7834_, v_B_7835_, v_s3_7872_);
lean_dec(v___x_7840_);
return v___x_7873_;
}
}
else
{
float v_s2_7874_; uint32_t v___x_7875_; 
lean_dec(v___x_7839_);
v_s2_7874_ = lean_ctor_get_float32(v___x_7841_, 8);
v___x_7875_ = lp_competition_Submission_Packed10_finish(v_n_7831_, v_baseA_7832_, v___x_7840_, v_p_7833_, v_A_7834_, v_B_7835_, v_s2_7874_);
lean_dec(v___x_7840_);
return v___x_7875_;
}
}
else
{
float v_s1_7876_; uint32_t v___x_7877_; 
lean_dec(v___x_7839_);
v_s1_7876_ = lean_ctor_get_float32(v___x_7841_, 4);
v___x_7877_ = lp_competition_Submission_Packed10_finish(v_n_7831_, v_baseA_7832_, v___x_7840_, v_p_7833_, v_A_7834_, v_B_7835_, v_s1_7876_);
lean_dec(v___x_7840_);
return v___x_7877_;
}
}
else
{
float v_s0_7878_; uint32_t v___x_7879_; 
lean_dec(v___x_7839_);
v_s0_7878_ = lean_ctor_get_float32(v___x_7841_, 0);
v___x_7879_ = lp_competition_Submission_Packed10_finish(v_n_7831_, v_baseA_7832_, v___x_7840_, v_p_7833_, v_A_7834_, v_B_7835_, v_s0_7878_);
lean_dec(v___x_7840_);
return v___x_7879_;
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_RowOutput_row___redArg___lam__0___boxed(lean_object* v_baseB_7880_, lean_object* v_tiles_7881_, lean_object* v_n_7882_, lean_object* v_baseA_7883_, lean_object* v_p_7884_, lean_object* v_A_7885_, lean_object* v_B_7886_, lean_object* v_j_7887_){
_start:
{
uint32_t v_res_7888_; lean_object* v_r_7889_; 
v_res_7888_ = lp_competition_Submission_RowOutput_row___redArg___lam__0(v_baseB_7880_, v_tiles_7881_, v_n_7882_, v_baseA_7883_, v_p_7884_, v_A_7885_, v_B_7886_, v_j_7887_);
lean_dec(v_j_7887_);
lean_dec_ref(v_B_7886_);
lean_dec_ref(v_A_7885_);
lean_dec(v_p_7884_);
lean_dec(v_baseA_7883_);
lean_dec(v_n_7882_);
lean_dec_ref(v_tiles_7881_);
lean_dec(v_baseB_7880_);
v_r_7889_ = lean_box_uint32(v_res_7888_);
return v_r_7889_;
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_RowOutput_row___redArg(lean_object* v_m_7890_, lean_object* v_n_7891_, lean_object* v_p_7892_, lean_object* v_A_7893_, lean_object* v_B_7894_, lean_object* v_b_7895_, lean_object* v_i_7896_, lean_object* v_tiles_7897_){
_start:
{
lean_object* v___x_7898_; lean_object* v___x_7899_; lean_object* v_baseA_7900_; lean_object* v___x_7901_; lean_object* v_baseB_7902_; lean_object* v___f_7903_; lean_object* v___x_7904_; 
v___x_7898_ = lean_nat_mul(v_b_7895_, v_m_7890_);
v___x_7899_ = lean_nat_add(v___x_7898_, v_i_7896_);
lean_dec(v___x_7898_);
v_baseA_7900_ = lean_nat_mul(v___x_7899_, v_n_7891_);
lean_dec(v___x_7899_);
v___x_7901_ = lean_nat_mul(v_b_7895_, v_n_7891_);
v_baseB_7902_ = lean_nat_mul(v___x_7901_, v_p_7892_);
lean_dec(v___x_7901_);
lean_inc(v_p_7892_);
v___f_7903_ = lean_alloc_closure((void*)(lp_competition_Submission_RowOutput_row___redArg___lam__0___boxed), 8, 7);
lean_closure_set(v___f_7903_, 0, v_baseB_7902_);
lean_closure_set(v___f_7903_, 1, v_tiles_7897_);
lean_closure_set(v___f_7903_, 2, v_n_7891_);
lean_closure_set(v___f_7903_, 3, v_baseA_7900_);
lean_closure_set(v___f_7903_, 4, v_p_7892_);
lean_closure_set(v___f_7903_, 5, v_A_7893_);
lean_closure_set(v___f_7903_, 6, v_B_7894_);
v___x_7904_ = l_Array_ofFn___redArg(v_p_7892_, v___f_7903_);
return v___x_7904_;
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_RowOutput_row___redArg___boxed(lean_object* v_m_7905_, lean_object* v_n_7906_, lean_object* v_p_7907_, lean_object* v_A_7908_, lean_object* v_B_7909_, lean_object* v_b_7910_, lean_object* v_i_7911_, lean_object* v_tiles_7912_){
_start:
{
lean_object* v_res_7913_; 
v_res_7913_ = lp_competition_Submission_RowOutput_row___redArg(v_m_7905_, v_n_7906_, v_p_7907_, v_A_7908_, v_B_7909_, v_b_7910_, v_i_7911_, v_tiles_7912_);
lean_dec(v_i_7911_);
lean_dec(v_b_7910_);
lean_dec(v_m_7905_);
return v_res_7913_;
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_RowOutput_row(lean_object* v_batch_7914_, lean_object* v_m_7915_, lean_object* v_n_7916_, lean_object* v_p_7917_, lean_object* v_A_7918_, lean_object* v_B_7919_, lean_object* v_b_7920_, lean_object* v_i_7921_, lean_object* v_tiles_7922_){
_start:
{
lean_object* v___x_7923_; 
v___x_7923_ = lp_competition_Submission_RowOutput_row___redArg(v_m_7915_, v_n_7916_, v_p_7917_, v_A_7918_, v_B_7919_, v_b_7920_, v_i_7921_, v_tiles_7922_);
return v___x_7923_;
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_RowOutput_row___boxed(lean_object* v_batch_7924_, lean_object* v_m_7925_, lean_object* v_n_7926_, lean_object* v_p_7927_, lean_object* v_A_7928_, lean_object* v_B_7929_, lean_object* v_b_7930_, lean_object* v_i_7931_, lean_object* v_tiles_7932_){
_start:
{
lean_object* v_res_7933_; 
v_res_7933_ = lp_competition_Submission_RowOutput_row(v_batch_7924_, v_m_7925_, v_n_7926_, v_p_7927_, v_A_7928_, v_B_7929_, v_b_7930_, v_i_7931_, v_tiles_7932_);
lean_dec(v_i_7931_);
lean_dec(v_b_7930_);
lean_dec(v_m_7925_);
lean_dec(v_batch_7924_);
return v_res_7933_;
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_RowOutput_output___lam__0(lean_object* v_batchTiles_7934_, lean_object* v_m_7935_, lean_object* v_n_7936_, lean_object* v_p_7937_, lean_object* v_A_7938_, lean_object* v_B_7939_, lean_object* v_b_7940_, lean_object* v_i_7941_){
_start:
{
lean_object* v___x_7942_; lean_object* v___x_7943_; 
v___x_7942_ = lean_array_fget_borrowed(v_batchTiles_7934_, v_i_7941_);
lean_inc(v___x_7942_);
v___x_7943_ = lp_competition_Submission_RowOutput_row___redArg(v_m_7935_, v_n_7936_, v_p_7937_, v_A_7938_, v_B_7939_, v_b_7940_, v_i_7941_, v___x_7942_);
return v___x_7943_;
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_RowOutput_output___lam__0___boxed(lean_object* v_batchTiles_7944_, lean_object* v_m_7945_, lean_object* v_n_7946_, lean_object* v_p_7947_, lean_object* v_A_7948_, lean_object* v_B_7949_, lean_object* v_b_7950_, lean_object* v_i_7951_){
_start:
{
lean_object* v_res_7952_; 
v_res_7952_ = lp_competition_Submission_RowOutput_output___lam__0(v_batchTiles_7944_, v_m_7945_, v_n_7946_, v_p_7947_, v_A_7948_, v_B_7949_, v_b_7950_, v_i_7951_);
lean_dec(v_i_7951_);
lean_dec(v_b_7950_);
lean_dec(v_m_7945_);
lean_dec_ref(v_batchTiles_7944_);
return v_res_7952_;
}
}
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_mapMUnsafe_map___at___00Submission_RowOutput_output_spec__0(size_t v_sz_7953_, size_t v_i_7954_, lean_object* v_bs_7955_){
_start:
{
uint8_t v___x_7956_; 
v___x_7956_ = lean_usize_dec_lt(v_i_7954_, v_sz_7953_);
if (v___x_7956_ == 0)
{
return v_bs_7955_;
}
else
{
lean_object* v_v_7957_; lean_object* v___x_7958_; lean_object* v_bs_x27_7959_; size_t v___x_7960_; size_t v___x_7961_; lean_object* v___x_7962_; 
v_v_7957_ = lean_array_uget(v_bs_7955_, v_i_7954_);
v___x_7958_ = lean_unsigned_to_nat(0u);
v_bs_x27_7959_ = lean_array_uset(v_bs_7955_, v_i_7954_, v___x_7958_);
v___x_7960_ = ((size_t)1ULL);
v___x_7961_ = lean_usize_add(v_i_7954_, v___x_7960_);
v___x_7962_ = lean_array_uset(v_bs_x27_7959_, v_i_7954_, v_v_7957_);
v_i_7954_ = v___x_7961_;
v_bs_7955_ = v___x_7962_;
goto _start;
}
}
}
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_mapMUnsafe_map___at___00Submission_RowOutput_output_spec__0___boxed(lean_object* v_sz_7964_, lean_object* v_i_7965_, lean_object* v_bs_7966_){
_start:
{
size_t v_sz_boxed_7967_; size_t v_i_boxed_7968_; lean_object* v_res_7969_; 
v_sz_boxed_7967_ = lean_unbox_usize(v_sz_7964_);
lean_dec(v_sz_7964_);
v_i_boxed_7968_ = lean_unbox_usize(v_i_7965_);
lean_dec(v_i_7965_);
v_res_7969_ = lp_competition___private_Init_Data_Array_Basic_0__Array_mapMUnsafe_map___at___00Submission_RowOutput_output_spec__0(v_sz_boxed_7967_, v_i_boxed_7968_, v_bs_7966_);
return v_res_7969_;
}
}
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_foldlMUnsafe_fold___at___00Submission_RowOutput_output_spec__1(lean_object* v_as_7970_, size_t v_i_7971_, size_t v_stop_7972_, lean_object* v_b_7973_){
_start:
{
uint8_t v___x_7974_; 
v___x_7974_ = lean_usize_dec_eq(v_i_7971_, v_stop_7972_);
if (v___x_7974_ == 0)
{
lean_object* v___x_7975_; lean_object* v___x_7976_; size_t v___x_7977_; size_t v___x_7978_; 
v___x_7975_ = lean_array_uget_borrowed(v_as_7970_, v_i_7971_);
v___x_7976_ = l_Array_append___redArg(v_b_7973_, v___x_7975_);
v___x_7977_ = ((size_t)1ULL);
v___x_7978_ = lean_usize_add(v_i_7971_, v___x_7977_);
v_i_7971_ = v___x_7978_;
v_b_7973_ = v___x_7976_;
goto _start;
}
else
{
return v_b_7973_;
}
}
}
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_foldlMUnsafe_fold___at___00Submission_RowOutput_output_spec__1___boxed(lean_object* v_as_7980_, lean_object* v_i_7981_, lean_object* v_stop_7982_, lean_object* v_b_7983_){
_start:
{
size_t v_i_boxed_7984_; size_t v_stop_boxed_7985_; lean_object* v_res_7986_; 
v_i_boxed_7984_ = lean_unbox_usize(v_i_7981_);
lean_dec(v_i_7981_);
v_stop_boxed_7985_ = lean_unbox_usize(v_stop_7982_);
lean_dec(v_stop_7982_);
v_res_7986_ = lp_competition___private_Init_Data_Array_Basic_0__Array_foldlMUnsafe_fold___at___00Submission_RowOutput_output_spec__1(v_as_7980_, v_i_boxed_7984_, v_stop_boxed_7985_, v_b_7983_);
lean_dec_ref(v_as_7980_);
return v_res_7986_;
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_RowOutput_output___lam__1(lean_object* v_tiles_7989_, lean_object* v_m_7990_, lean_object* v_n_7991_, lean_object* v_p_7992_, lean_object* v_A_7993_, lean_object* v_B_7994_, lean_object* v_b_7995_){
_start:
{
lean_object* v_batchTiles_7996_; lean_object* v___f_7997_; lean_object* v___x_7998_; size_t v_sz_7999_; size_t v___x_8000_; lean_object* v___x_8001_; lean_object* v___x_8002_; lean_object* v___x_8003_; lean_object* v___x_8004_; uint8_t v___x_8005_; 
v_batchTiles_7996_ = lean_array_fget_borrowed(v_tiles_7989_, v_b_7995_);
lean_inc(v_m_7990_);
lean_inc(v_batchTiles_7996_);
v___f_7997_ = lean_alloc_closure((void*)(lp_competition_Submission_RowOutput_output___lam__0___boxed), 8, 7);
lean_closure_set(v___f_7997_, 0, v_batchTiles_7996_);
lean_closure_set(v___f_7997_, 1, v_m_7990_);
lean_closure_set(v___f_7997_, 2, v_n_7991_);
lean_closure_set(v___f_7997_, 3, v_p_7992_);
lean_closure_set(v___f_7997_, 4, v_A_7993_);
lean_closure_set(v___f_7997_, 5, v_B_7994_);
lean_closure_set(v___f_7997_, 6, v_b_7995_);
v___x_7998_ = l_Array_ofFn___redArg(v_m_7990_, v___f_7997_);
v_sz_7999_ = lean_array_size(v___x_7998_);
v___x_8000_ = ((size_t)0ULL);
v___x_8001_ = lp_competition___private_Init_Data_Array_Basic_0__Array_mapMUnsafe_map___at___00Submission_RowOutput_output_spec__0(v_sz_7999_, v___x_8000_, v___x_7998_);
v___x_8002_ = lean_unsigned_to_nat(0u);
v___x_8003_ = ((lean_object*)(lp_competition_Submission_RowOutput_output___lam__1___closed__0));
v___x_8004_ = lean_array_get_size(v___x_8001_);
v___x_8005_ = lean_nat_dec_lt(v___x_8002_, v___x_8004_);
if (v___x_8005_ == 0)
{
lean_dec_ref(v___x_8001_);
return v___x_8003_;
}
else
{
uint8_t v___x_8006_; 
v___x_8006_ = lean_nat_dec_le(v___x_8004_, v___x_8004_);
if (v___x_8006_ == 0)
{
if (v___x_8005_ == 0)
{
lean_dec_ref(v___x_8001_);
return v___x_8003_;
}
else
{
size_t v___x_8007_; lean_object* v___x_8008_; 
v___x_8007_ = lean_usize_of_nat(v___x_8004_);
v___x_8008_ = lp_competition___private_Init_Data_Array_Basic_0__Array_foldlMUnsafe_fold___at___00Submission_RowOutput_output_spec__1(v___x_8001_, v___x_8000_, v___x_8007_, v___x_8003_);
lean_dec_ref(v___x_8001_);
return v___x_8008_;
}
}
else
{
size_t v___x_8009_; lean_object* v___x_8010_; 
v___x_8009_ = lean_usize_of_nat(v___x_8004_);
v___x_8010_ = lp_competition___private_Init_Data_Array_Basic_0__Array_foldlMUnsafe_fold___at___00Submission_RowOutput_output_spec__1(v___x_8001_, v___x_8000_, v___x_8009_, v___x_8003_);
lean_dec_ref(v___x_8001_);
return v___x_8010_;
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_RowOutput_output___lam__1___boxed(lean_object* v_tiles_8011_, lean_object* v_m_8012_, lean_object* v_n_8013_, lean_object* v_p_8014_, lean_object* v_A_8015_, lean_object* v_B_8016_, lean_object* v_b_8017_){
_start:
{
lean_object* v_res_8018_; 
v_res_8018_ = lp_competition_Submission_RowOutput_output___lam__1(v_tiles_8011_, v_m_8012_, v_n_8013_, v_p_8014_, v_A_8015_, v_B_8016_, v_b_8017_);
lean_dec_ref(v_tiles_8011_);
return v_res_8018_;
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_RowOutput_output(lean_object* v_batch_8019_, lean_object* v_m_8020_, lean_object* v_n_8021_, lean_object* v_p_8022_, lean_object* v_A_8023_, lean_object* v_B_8024_, lean_object* v_tiles_8025_){
_start:
{
lean_object* v___f_8026_; lean_object* v___x_8027_; size_t v_sz_8028_; size_t v___x_8029_; lean_object* v___x_8030_; lean_object* v___x_8031_; lean_object* v___x_8032_; lean_object* v___x_8033_; uint8_t v___x_8034_; 
v___f_8026_ = lean_alloc_closure((void*)(lp_competition_Submission_RowOutput_output___lam__1___boxed), 7, 6);
lean_closure_set(v___f_8026_, 0, v_tiles_8025_);
lean_closure_set(v___f_8026_, 1, v_m_8020_);
lean_closure_set(v___f_8026_, 2, v_n_8021_);
lean_closure_set(v___f_8026_, 3, v_p_8022_);
lean_closure_set(v___f_8026_, 4, v_A_8023_);
lean_closure_set(v___f_8026_, 5, v_B_8024_);
v___x_8027_ = l_Array_ofFn___redArg(v_batch_8019_, v___f_8026_);
v_sz_8028_ = lean_array_size(v___x_8027_);
v___x_8029_ = ((size_t)0ULL);
v___x_8030_ = lp_competition___private_Init_Data_Array_Basic_0__Array_mapMUnsafe_map___at___00Submission_RowOutput_output_spec__0(v_sz_8028_, v___x_8029_, v___x_8027_);
v___x_8031_ = lean_unsigned_to_nat(0u);
v___x_8032_ = ((lean_object*)(lp_competition_Submission_RowOutput_output___lam__1___closed__0));
v___x_8033_ = lean_array_get_size(v___x_8030_);
v___x_8034_ = lean_nat_dec_lt(v___x_8031_, v___x_8033_);
if (v___x_8034_ == 0)
{
lean_dec_ref(v___x_8030_);
return v___x_8032_;
}
else
{
uint8_t v___x_8035_; 
v___x_8035_ = lean_nat_dec_le(v___x_8033_, v___x_8033_);
if (v___x_8035_ == 0)
{
if (v___x_8034_ == 0)
{
lean_dec_ref(v___x_8030_);
return v___x_8032_;
}
else
{
size_t v___x_8036_; lean_object* v___x_8037_; 
v___x_8036_ = lean_usize_of_nat(v___x_8033_);
v___x_8037_ = lp_competition___private_Init_Data_Array_Basic_0__Array_foldlMUnsafe_fold___at___00Submission_RowOutput_output_spec__1(v___x_8030_, v___x_8029_, v___x_8036_, v___x_8032_);
lean_dec_ref(v___x_8030_);
return v___x_8037_;
}
}
else
{
size_t v___x_8038_; lean_object* v___x_8039_; 
v___x_8038_ = lean_usize_of_nat(v___x_8033_);
v___x_8039_ = lp_competition___private_Init_Data_Array_Basic_0__Array_foldlMUnsafe_fold___at___00Submission_RowOutput_output_spec__1(v___x_8030_, v___x_8029_, v___x_8038_, v___x_8032_);
lean_dec_ref(v___x_8030_);
return v___x_8039_;
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_RowOutput_core(lean_object* v_batch_8040_, lean_object* v_m_8041_, lean_object* v_n_8042_, lean_object* v_p_8043_, lean_object* v_A_8044_, lean_object* v_B_8045_){
_start:
{
size_t v_sz_8046_; size_t v___x_8047_; lean_object* v_nativeA_8048_; lean_object* v_packedB_8049_; lean_object* v_tiles_8050_; lean_object* v___x_8051_; 
v_sz_8046_ = lean_array_size(v_A_8044_);
v___x_8047_ = ((size_t)0ULL);
lean_inc_ref(v_A_8044_);
v_nativeA_8048_ = lp_competition___private_Init_Data_Array_Basic_0__Array_mapMUnsafe_map___at___00Submission_Packed10_core_spec__0(v_sz_8046_, v___x_8047_, v_A_8044_);
lean_inc_ref(v_B_8045_);
lean_inc_n(v_p_8043_, 2);
lean_inc_n(v_n_8042_, 2);
lean_inc_n(v_batch_8040_, 2);
v_packedB_8049_ = lp_competition_Submission_Packed10_packB(v_batch_8040_, v_n_8042_, v_p_8043_, v_B_8045_);
lean_inc(v_m_8041_);
v_tiles_8050_ = lp_competition_Submission_Packed10_tileResults(v_batch_8040_, v_m_8041_, v_n_8042_, v_p_8043_, v_nativeA_8048_, v_packedB_8049_);
v___x_8051_ = lp_competition_Submission_RowOutput_output(v_batch_8040_, v_m_8041_, v_n_8042_, v_p_8043_, v_A_8044_, v_B_8045_, v_tiles_8050_);
return v___x_8051_;
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_bmmRows(lean_object* v_batch_8052_, lean_object* v_m_8053_, lean_object* v_n_8054_, lean_object* v_p_8055_, lean_object* v_A_8056_, lean_object* v_B_8057_){
_start:
{
lean_object* v___x_8058_; lean_object* v___x_8059_; lean_object* v___x_8060_; uint8_t v___x_8061_; 
v___x_8058_ = lean_nat_mul(v_batch_8052_, v_m_8053_);
v___x_8059_ = lean_nat_mul(v___x_8058_, v_p_8055_);
lean_dec(v___x_8058_);
v___x_8060_ = lean_unsigned_to_nat(0u);
v___x_8061_ = lean_nat_dec_eq(v___x_8059_, v___x_8060_);
lean_dec(v___x_8059_);
if (v___x_8061_ == 0)
{
uint8_t v___x_8062_; 
v___x_8062_ = lean_nat_dec_eq(v_n_8054_, v___x_8060_);
if (v___x_8062_ == 0)
{
lean_object* v___x_8063_; 
v___x_8063_ = lp_competition_Submission_RowOutput_core(v_batch_8052_, v_m_8053_, v_n_8054_, v_p_8055_, v_A_8056_, v_B_8057_);
return v___x_8063_;
}
else
{
lean_object* v___x_8064_; 
v___x_8064_ = lp_competition_Submission_referenceBmm(v_batch_8052_, v_m_8053_, v_n_8054_, v_p_8055_, v_A_8056_, v_B_8057_);
lean_dec(v_batch_8052_);
return v___x_8064_;
}
}
else
{
lean_object* v___x_8065_; 
v___x_8065_ = lp_competition_Submission_referenceBmm(v_batch_8052_, v_m_8053_, v_n_8054_, v_p_8055_, v_A_8056_, v_B_8057_);
lean_dec(v_batch_8052_);
return v___x_8065_;
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_RowStream_core___lam__0(lean_object* v_r_8066_){
_start:
{
lean_inc(v_r_8066_);
return v_r_8066_;
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_RowStream_core___lam__0___boxed(lean_object* v_r_8067_){
_start:
{
lean_object* v_res_8068_; 
v_res_8068_ = lp_competition_Submission_RowStream_core___lam__0(v_r_8067_);
lean_dec(v_r_8067_);
return v_res_8068_;
}
}
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_foldlMUnsafe_fold___at___00Submission_RowStream_core_spec__0___redArg___lam__0(lean_object* v_b_8069_, lean_object* v_m_8070_, lean_object* v_i_8071_, lean_object* v_n_8072_, lean_object* v_packedB_8073_, lean_object* v_nativeA_8074_, lean_object* v_g_8075_){
_start:
{
lean_object* v___x_8076_; lean_object* v___x_8077_; lean_object* v___x_8078_; lean_object* v___x_8079_; lean_object* v___x_8080_; lean_object* v___x_8085_; uint8_t v___x_8086_; 
v___x_8076_ = lean_nat_mul(v_b_8069_, v_m_8070_);
v___x_8077_ = lean_nat_add(v___x_8076_, v_i_8071_);
lean_dec(v___x_8076_);
v___x_8078_ = lean_nat_mul(v___x_8077_, v_n_8072_);
lean_dec(v___x_8077_);
v___x_8079_ = lean_array_fget_borrowed(v_packedB_8073_, v_b_8069_);
v___x_8080_ = lean_array_fget_borrowed(v___x_8079_, v_g_8075_);
v___x_8085_ = lean_obj_once(&lp_competition_Submission_Packed10Index_runDot___closed__0, &lp_competition_Submission_Packed10Index_runDot___closed__0_once, _init_lp_competition_Submission_Packed10Index_runDot___closed__0);
v___x_8086_ = lean_nat_dec_lt(v_n_8072_, v___x_8085_);
if (v___x_8086_ == 0)
{
goto v___jp_8081_;
}
else
{
uint8_t v___x_8087_; 
v___x_8087_ = lean_nat_dec_lt(v___x_8078_, v___x_8085_);
if (v___x_8087_ == 0)
{
goto v___jp_8081_;
}
else
{
lean_object* v___x_8088_; lean_object* v___x_8089_; lean_object* v___x_8090_; lean_object* v___x_8091_; uint8_t v___x_8092_; 
v___x_8088_ = lean_unsigned_to_nat(1u);
v___x_8089_ = lean_nat_sub(v_n_8072_, v___x_8088_);
v___x_8090_ = lean_nat_add(v___x_8078_, v___x_8089_);
lean_dec(v___x_8089_);
v___x_8091_ = lean_array_get_size(v_nativeA_8074_);
v___x_8092_ = lean_nat_dec_lt(v___x_8090_, v___x_8091_);
lean_dec(v___x_8090_);
if (v___x_8092_ == 0)
{
goto v___jp_8081_;
}
else
{
uint8_t v___x_8093_; 
v___x_8093_ = lean_nat_dec_lt(v___x_8091_, v___x_8085_);
if (v___x_8093_ == 0)
{
goto v___jp_8081_;
}
else
{
size_t v___x_8094_; size_t v___x_8095_; size_t v___x_8096_; float v___x_8097_; lean_object* v___x_8098_; 
v___x_8094_ = lean_usize_of_nat(v_n_8072_);
v___x_8095_ = lean_usize_of_nat(v___x_8078_);
lean_dec(v___x_8078_);
v___x_8096_ = ((size_t)0ULL);
v___x_8097_ = lean_float32_once(&lp_competition_Submission_NativeFinal_dot___closed__0, &lp_competition_Submission_NativeFinal_dot___closed__0_once, _init_lp_competition_Submission_NativeFinal_dot___closed__0);
v___x_8098_ = lp_competition_Submission_Packed10Index_loop___redArg(v___x_8094_, v___x_8095_, v_nativeA_8074_, v___x_8080_, v___x_8096_, v___x_8097_, v___x_8097_, v___x_8097_, v___x_8097_, v___x_8097_, v___x_8097_, v___x_8097_, v___x_8097_, v___x_8097_, v___x_8097_);
return v___x_8098_;
}
}
}
}
v___jp_8081_:
{
lean_object* v___x_8082_; float v___x_8083_; lean_object* v___x_8084_; 
v___x_8082_ = lean_unsigned_to_nat(0u);
v___x_8083_ = lean_float32_once(&lp_competition_Submission_NativeFinal_dot___closed__0, &lp_competition_Submission_NativeFinal_dot___closed__0_once, _init_lp_competition_Submission_NativeFinal_dot___closed__0);
v___x_8084_ = lp_competition_Submission_Packed10_dot10(v_n_8072_, v___x_8078_, v_nativeA_8074_, v___x_8080_, v___x_8082_, v___x_8083_, v___x_8083_, v___x_8083_, v___x_8083_, v___x_8083_, v___x_8083_, v___x_8083_, v___x_8083_, v___x_8083_, v___x_8083_);
lean_dec(v___x_8078_);
return v___x_8084_;
}
}
}
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_foldlMUnsafe_fold___at___00Submission_RowStream_core_spec__0___redArg___lam__0___boxed(lean_object* v_b_8099_, lean_object* v_m_8100_, lean_object* v_i_8101_, lean_object* v_n_8102_, lean_object* v_packedB_8103_, lean_object* v_nativeA_8104_, lean_object* v_g_8105_){
_start:
{
lean_object* v_res_8106_; 
v_res_8106_ = lp_competition___private_Init_Data_Array_Basic_0__Array_foldlMUnsafe_fold___at___00Submission_RowStream_core_spec__0___redArg___lam__0(v_b_8099_, v_m_8100_, v_i_8101_, v_n_8102_, v_packedB_8103_, v_nativeA_8104_, v_g_8105_);
lean_dec(v_g_8105_);
lean_dec_ref(v_nativeA_8104_);
lean_dec_ref(v_packedB_8103_);
lean_dec(v_n_8102_);
lean_dec(v_i_8101_);
lean_dec(v_m_8100_);
lean_dec(v_b_8099_);
return v_res_8106_;
}
}
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_foldlMUnsafe_fold___at___00Submission_RowStream_core_spec__0___redArg(lean_object* v_m_8107_, lean_object* v_n_8108_, lean_object* v_packedB_8109_, lean_object* v_nativeA_8110_, lean_object* v_p_8111_, lean_object* v_A_8112_, lean_object* v_B_8113_, lean_object* v_as_8114_, size_t v_i_8115_, size_t v_stop_8116_, lean_object* v_b_8117_){
_start:
{
uint8_t v___x_8118_; 
v___x_8118_ = lean_usize_dec_eq(v_i_8115_, v_stop_8116_);
if (v___x_8118_ == 0)
{
lean_object* v___x_8119_; lean_object* v_b_8120_; lean_object* v_i_8121_; lean_object* v___f_8122_; lean_object* v___x_8123_; lean_object* v___x_8124_; lean_object* v___x_8125_; lean_object* v___x_8126_; lean_object* v_rowTiles_8127_; lean_object* v___x_8128_; lean_object* v___x_8129_; size_t v___x_8130_; size_t v___x_8131_; 
v___x_8119_ = lean_array_uget_borrowed(v_as_8114_, v_i_8115_);
v_b_8120_ = lean_nat_div(v___x_8119_, v_m_8107_);
v_i_8121_ = lean_nat_mod(v___x_8119_, v_m_8107_);
lean_inc_ref(v_nativeA_8110_);
lean_inc_ref(v_packedB_8109_);
lean_inc_n(v_n_8108_, 2);
lean_inc(v_i_8121_);
lean_inc(v_m_8107_);
lean_inc(v_b_8120_);
v___f_8122_ = lean_alloc_closure((void*)(lp_competition___private_Init_Data_Array_Basic_0__Array_foldlMUnsafe_fold___at___00Submission_RowStream_core_spec__0___redArg___lam__0___boxed), 7, 6);
lean_closure_set(v___f_8122_, 0, v_b_8120_);
lean_closure_set(v___f_8122_, 1, v_m_8107_);
lean_closure_set(v___f_8122_, 2, v_i_8121_);
lean_closure_set(v___f_8122_, 3, v_n_8108_);
lean_closure_set(v___f_8122_, 4, v_packedB_8109_);
lean_closure_set(v___f_8122_, 5, v_nativeA_8110_);
v___x_8123_ = lean_unsigned_to_nat(9u);
v___x_8124_ = lean_nat_add(v_p_8111_, v___x_8123_);
v___x_8125_ = lean_unsigned_to_nat(10u);
v___x_8126_ = lean_nat_div(v___x_8124_, v___x_8125_);
lean_dec(v___x_8124_);
v_rowTiles_8127_ = l_Array_ofFn___redArg(v___x_8126_, v___f_8122_);
lean_inc_ref(v_B_8113_);
lean_inc_ref(v_A_8112_);
lean_inc(v_p_8111_);
v___x_8128_ = lp_competition_Submission_RowOutput_row___redArg(v_m_8107_, v_n_8108_, v_p_8111_, v_A_8112_, v_B_8113_, v_b_8120_, v_i_8121_, v_rowTiles_8127_);
lean_dec(v_i_8121_);
lean_dec(v_b_8120_);
v___x_8129_ = l_Array_append___redArg(v_b_8117_, v___x_8128_);
lean_dec_ref(v___x_8128_);
v___x_8130_ = ((size_t)1ULL);
v___x_8131_ = lean_usize_add(v_i_8115_, v___x_8130_);
v_i_8115_ = v___x_8131_;
v_b_8117_ = v___x_8129_;
goto _start;
}
else
{
lean_dec_ref(v_B_8113_);
lean_dec_ref(v_A_8112_);
lean_dec(v_p_8111_);
lean_dec_ref(v_nativeA_8110_);
lean_dec_ref(v_packedB_8109_);
lean_dec(v_n_8108_);
lean_dec(v_m_8107_);
return v_b_8117_;
}
}
}
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_foldlMUnsafe_fold___at___00Submission_RowStream_core_spec__0___redArg___boxed(lean_object* v_m_8133_, lean_object* v_n_8134_, lean_object* v_packedB_8135_, lean_object* v_nativeA_8136_, lean_object* v_p_8137_, lean_object* v_A_8138_, lean_object* v_B_8139_, lean_object* v_as_8140_, lean_object* v_i_8141_, lean_object* v_stop_8142_, lean_object* v_b_8143_){
_start:
{
size_t v_i_boxed_8144_; size_t v_stop_boxed_8145_; lean_object* v_res_8146_; 
v_i_boxed_8144_ = lean_unbox_usize(v_i_8141_);
lean_dec(v_i_8141_);
v_stop_boxed_8145_ = lean_unbox_usize(v_stop_8142_);
lean_dec(v_stop_8142_);
v_res_8146_ = lp_competition___private_Init_Data_Array_Basic_0__Array_foldlMUnsafe_fold___at___00Submission_RowStream_core_spec__0___redArg(v_m_8133_, v_n_8134_, v_packedB_8135_, v_nativeA_8136_, v_p_8137_, v_A_8138_, v_B_8139_, v_as_8140_, v_i_boxed_8144_, v_stop_boxed_8145_, v_b_8143_);
lean_dec_ref(v_as_8140_);
return v_res_8146_;
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_RowStream_core(lean_object* v_batch_8148_, lean_object* v_m_8149_, lean_object* v_n_8150_, lean_object* v_p_8151_, lean_object* v_A_8152_, lean_object* v_B_8153_){
_start:
{
lean_object* v___f_8154_; lean_object* v___x_8155_; lean_object* v___x_8156_; lean_object* v___x_8157_; lean_object* v___x_8158_; lean_object* v___x_8159_; uint8_t v___x_8160_; 
v___f_8154_ = ((lean_object*)(lp_competition_Submission_RowStream_core___closed__0));
v___x_8155_ = lean_nat_mul(v_batch_8148_, v_m_8149_);
v___x_8156_ = l_Array_ofFn___redArg(v___x_8155_, v___f_8154_);
v___x_8157_ = lean_unsigned_to_nat(0u);
v___x_8158_ = ((lean_object*)(lp_competition_Submission_RowOutput_output___lam__1___closed__0));
v___x_8159_ = lean_array_get_size(v___x_8156_);
v___x_8160_ = lean_nat_dec_lt(v___x_8157_, v___x_8159_);
if (v___x_8160_ == 0)
{
lean_dec_ref(v___x_8156_);
lean_dec_ref(v_B_8153_);
lean_dec_ref(v_A_8152_);
lean_dec(v_p_8151_);
lean_dec(v_n_8150_);
lean_dec(v_m_8149_);
lean_dec(v_batch_8148_);
return v___x_8158_;
}
else
{
size_t v_sz_8161_; size_t v___x_8162_; lean_object* v_nativeA_8163_; lean_object* v_packedB_8164_; uint8_t v___x_8165_; 
v_sz_8161_ = lean_array_size(v_A_8152_);
v___x_8162_ = ((size_t)0ULL);
lean_inc_ref(v_A_8152_);
v_nativeA_8163_ = lp_competition___private_Init_Data_Array_Basic_0__Array_mapMUnsafe_map___at___00Submission_Packed10_core_spec__0(v_sz_8161_, v___x_8162_, v_A_8152_);
lean_inc_ref(v_B_8153_);
lean_inc(v_p_8151_);
lean_inc(v_n_8150_);
v_packedB_8164_ = lp_competition_Submission_Packed10_packB(v_batch_8148_, v_n_8150_, v_p_8151_, v_B_8153_);
v___x_8165_ = lean_nat_dec_le(v___x_8159_, v___x_8159_);
if (v___x_8165_ == 0)
{
if (v___x_8160_ == 0)
{
lean_dec_ref(v_packedB_8164_);
lean_dec_ref(v_nativeA_8163_);
lean_dec_ref(v___x_8156_);
lean_dec_ref(v_B_8153_);
lean_dec_ref(v_A_8152_);
lean_dec(v_p_8151_);
lean_dec(v_n_8150_);
lean_dec(v_m_8149_);
return v___x_8158_;
}
else
{
size_t v___x_8166_; lean_object* v___x_8167_; 
v___x_8166_ = lean_usize_of_nat(v___x_8159_);
v___x_8167_ = lp_competition___private_Init_Data_Array_Basic_0__Array_foldlMUnsafe_fold___at___00Submission_RowStream_core_spec__0___redArg(v_m_8149_, v_n_8150_, v_packedB_8164_, v_nativeA_8163_, v_p_8151_, v_A_8152_, v_B_8153_, v___x_8156_, v___x_8162_, v___x_8166_, v___x_8158_);
lean_dec_ref(v___x_8156_);
return v___x_8167_;
}
}
else
{
size_t v___x_8168_; lean_object* v___x_8169_; 
v___x_8168_ = lean_usize_of_nat(v___x_8159_);
v___x_8169_ = lp_competition___private_Init_Data_Array_Basic_0__Array_foldlMUnsafe_fold___at___00Submission_RowStream_core_spec__0___redArg(v_m_8149_, v_n_8150_, v_packedB_8164_, v_nativeA_8163_, v_p_8151_, v_A_8152_, v_B_8153_, v___x_8156_, v___x_8162_, v___x_8168_, v___x_8158_);
lean_dec_ref(v___x_8156_);
return v___x_8169_;
}
}
}
}
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_foldlMUnsafe_fold___at___00Submission_RowStream_core_spec__0(lean_object* v_m_8170_, lean_object* v_batch_8171_, lean_object* v_n_8172_, lean_object* v_packedB_8173_, lean_object* v_nativeA_8174_, lean_object* v_p_8175_, lean_object* v_A_8176_, lean_object* v_B_8177_, lean_object* v_as_8178_, size_t v_i_8179_, size_t v_stop_8180_, lean_object* v_b_8181_){
_start:
{
lean_object* v___x_8182_; 
v___x_8182_ = lp_competition___private_Init_Data_Array_Basic_0__Array_foldlMUnsafe_fold___at___00Submission_RowStream_core_spec__0___redArg(v_m_8170_, v_n_8172_, v_packedB_8173_, v_nativeA_8174_, v_p_8175_, v_A_8176_, v_B_8177_, v_as_8178_, v_i_8179_, v_stop_8180_, v_b_8181_);
return v___x_8182_;
}
}
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_foldlMUnsafe_fold___at___00Submission_RowStream_core_spec__0___boxed(lean_object* v_m_8183_, lean_object* v_batch_8184_, lean_object* v_n_8185_, lean_object* v_packedB_8186_, lean_object* v_nativeA_8187_, lean_object* v_p_8188_, lean_object* v_A_8189_, lean_object* v_B_8190_, lean_object* v_as_8191_, lean_object* v_i_8192_, lean_object* v_stop_8193_, lean_object* v_b_8194_){
_start:
{
size_t v_i_boxed_8195_; size_t v_stop_boxed_8196_; lean_object* v_res_8197_; 
v_i_boxed_8195_ = lean_unbox_usize(v_i_8192_);
lean_dec(v_i_8192_);
v_stop_boxed_8196_ = lean_unbox_usize(v_stop_8193_);
lean_dec(v_stop_8193_);
v_res_8197_ = lp_competition___private_Init_Data_Array_Basic_0__Array_foldlMUnsafe_fold___at___00Submission_RowStream_core_spec__0(v_m_8183_, v_batch_8184_, v_n_8185_, v_packedB_8186_, v_nativeA_8187_, v_p_8188_, v_A_8189_, v_B_8190_, v_as_8191_, v_i_boxed_8195_, v_stop_boxed_8196_, v_b_8194_);
lean_dec_ref(v_as_8191_);
lean_dec(v_batch_8184_);
return v_res_8197_;
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_bmm(lean_object* v_batch_8198_, lean_object* v_m_8199_, lean_object* v_n_8200_, lean_object* v_p_8201_, lean_object* v_A_8202_, lean_object* v_B_8203_){
_start:
{
lean_object* v___x_8204_; lean_object* v___x_8205_; lean_object* v___x_8206_; uint8_t v___x_8207_; 
v___x_8204_ = lean_nat_mul(v_batch_8198_, v_m_8199_);
v___x_8205_ = lean_nat_mul(v___x_8204_, v_p_8201_);
lean_dec(v___x_8204_);
v___x_8206_ = lean_unsigned_to_nat(0u);
v___x_8207_ = lean_nat_dec_eq(v___x_8205_, v___x_8206_);
lean_dec(v___x_8205_);
if (v___x_8207_ == 0)
{
uint8_t v___x_8208_; 
v___x_8208_ = lean_nat_dec_eq(v_n_8200_, v___x_8206_);
if (v___x_8208_ == 0)
{
lean_object* v___x_8209_; 
v___x_8209_ = lp_competition_Submission_RowStream_core(v_batch_8198_, v_m_8199_, v_n_8200_, v_p_8201_, v_A_8202_, v_B_8203_);
return v___x_8209_;
}
else
{
lean_object* v___x_8210_; 
v___x_8210_ = lp_competition_Submission_referenceBmm(v_batch_8198_, v_m_8199_, v_n_8200_, v_p_8201_, v_A_8202_, v_B_8203_);
lean_dec(v_batch_8198_);
return v___x_8210_;
}
}
else
{
lean_object* v___x_8211_; 
v___x_8211_ = lp_competition_Submission_referenceBmm(v_batch_8198_, v_m_8199_, v_n_8200_, v_p_8201_, v_A_8202_, v_B_8203_);
lean_dec(v_batch_8198_);
return v___x_8211_;
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
