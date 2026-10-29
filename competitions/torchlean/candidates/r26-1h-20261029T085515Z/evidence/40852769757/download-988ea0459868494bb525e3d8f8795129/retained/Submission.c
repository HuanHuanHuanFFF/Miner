// Lean compiler output
// Module: Submission
// Imports: public import Init public meta import Init public import ContractExact
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
lean_object* lean_nat_sub(lean_object*, lean_object*);
lean_object* lean_nat_add(lean_object*, lean_object*);
lean_object* lean_array_get_size(lean_object*);
uint8_t lean_nat_dec_lt(lean_object*, lean_object*);
lean_object* lean_array_fget(lean_object*, lean_object*);
lean_object* lean_array_fset(lean_object*, lean_object*, lean_object*);
uint64_t lean_uint64_of_nat(lean_object*);
lean_object* lean_nat_shiftr(lean_object*, lean_object*);
lean_object* lean_nat_mod(lean_object*, lean_object*);
uint64_t lean_uint64_sub(uint64_t, uint64_t);
uint64_t lean_uint64_shift_left(uint64_t, uint64_t);
uint64_t lean_uint64_mod(uint64_t, uint64_t);
uint64_t lean_uint64_shift_right(uint64_t, uint64_t);
lean_object* lean_uint64_to_nat(uint64_t);
lean_object* lean_nat_mul(lean_object*, lean_object*);
lean_object* lean_array_get_borrowed(lean_object*, lean_object*, lean_object*);
uint32_t lean_uint32_shift_right(uint32_t, uint32_t);
uint32_t lean_uint32_land(uint32_t, uint32_t);
uint8_t lean_uint32_dec_eq(uint32_t, uint32_t);
lean_object* lean_uint32_to_nat(uint32_t);
lean_object* l_BitVec_ofNat(lean_object*, lean_object*);
uint32_t lean_uint32_of_nat(lean_object*);
lean_object* lp_competition_ExactRuntime_ConvShape_ho(lean_object*);
lean_object* lp_competition_ExactRuntime_ConvShape_wo(lean_object*);
lean_object* lean_nat_div(lean_object*, lean_object*);
lean_object* lean_mk_array(lean_object*, lean_object*);
uint8_t lean_nat_dec_le(lean_object*, lean_object*);
lean_object* lean_nat_to_int(lean_object*);
lean_object* lean_int_neg(lean_object*);
lean_object* lean_nat_land(lean_object*, lean_object*);
lean_object* lean_nat_lor(lean_object*, lean_object*);
lean_object* lean_nat_shiftl(lean_object*, lean_object*);
lean_object* lean_int_add(lean_object*, lean_object*);
lean_object* l_Int_toNat(lean_object*);
uint8_t lean_int_dec_lt(lean_object*, lean_object*);
lean_object* lean_int_sub(lean_object*, lean_object*);
uint8_t lean_int_dec_eq(lean_object*, lean_object*);
lean_object* lp_competition_ExactRuntime_ofIntDyadic(lean_object*, lean_object*);
lean_object* lean_nat_log2(lean_object*);
lean_object* lean_nat_abs(lean_object*);
lean_object* l_Array_extract___redArg(lean_object*, lean_object*, lean_object*);
size_t lean_usize_of_nat(lean_object*);
uint8_t lean_usize_dec_eq(size_t, size_t);
size_t lean_usize_sub(size_t, size_t);
lean_object* lean_array_uget_borrowed(lean_object*, size_t);
lean_object* lp_competition_ExactRuntime_lowLimb(lean_object*, lean_object*, lean_object*, lean_object*);
lean_object* lean_array_push(lean_object*, lean_object*);
lean_object* lean_mk_empty_array_with_capacity(lean_object*);
lean_object* l_Array_ofFn___redArg(lean_object*, lean_object*);
uint32_t lp_competition_ExactRuntime_dotSpec(lean_object*, lean_object*);
lean_object* lean_array_get(lean_object*, lean_object*, lean_object*);
uint32_t lp_competition_ExactRuntime_natW(lean_object*);
lean_object* lp_floatlib_FloatLib_Floats_Formats_BinaryInterchange_Model_DivBackend_word___at___00FloatLib_Floats_Formats_BinaryInterchange_Configured_Plan_softwareDiv32Certified_spec__1(lean_object*, lean_object*);
lean_object* lp_floatlib_FloatLib_Floats_Formats_BinaryInterchange_Model_AddBackend_subWord___at___00FloatLib_Floats_Formats_BinaryInterchange_Configured_Plan_softwareSub32Certified_spec__1(lean_object*, lean_object*);
uint32_t lp_competition_ExactRuntime_invStd(lean_object*, uint32_t, uint32_t);
lean_object* lp_floatlib_FloatLib_Floats_Formats_BinaryInterchange_Model_MulBackend_word___at___00FloatLib_Floats_Formats_BinaryInterchange_Configured_Plan_softwareMul32Certified_spec__1(lean_object*, lean_object*);
lean_object* lp_floatlib_FloatLib_Floats_Formats_BinaryInterchange_Model_AddBackend_word___at___00FloatLib_Floats_Formats_BinaryInterchange_Configured_Plan_softwareAdd32Certified_spec__1(lean_object*, lean_object*);
extern lean_object* l_instInhabitedRat;
size_t lean_array_size(lean_object*);
uint8_t lean_usize_dec_lt(size_t, size_t);
lean_object* lean_array_uget(lean_object*, size_t);
lean_object* lean_array_uset(lean_object*, size_t, lean_object*);
lean_object* lp_competition_ExactRuntime_rationalWord(uint32_t);
size_t lean_usize_add(size_t, size_t);
lean_object* lp_mathlib_Nat_cast___at___00CompareReals_instCommRingQ_spec__0(lean_object*);
lean_object* l_List_range(lean_object*);
lean_object* l_Rat_add(lean_object*, lean_object*);
lean_object* l_Rat_div(lean_object*, lean_object*);
lean_object* l_Rat_sub(lean_object*, lean_object*);
lean_object* l_Rat_pow(lean_object*, lean_object*);
uint32_t lp_competition_ExactRuntime_sqrtRational(lean_object*);
lean_object* l_Rat_mul(lean_object*, lean_object*);
uint32_t lp_competition_ExactRuntime_roundRational(lean_object*);
uint8_t lp_competition___private_Init_Data_Array_Basic_0__Array_anyMUnsafe_any___at___00ExactRuntime_stableNormDomain_spec__0(uint8_t, lean_object*, size_t, size_t);
uint8_t lp_competition_ExactRuntime_stableNormDomain(lean_object*, lean_object*, uint32_t, lean_object*, lean_object*);
uint8_t l_Nat_testBit(lean_object*, lean_object*);
lean_object* lp_floatlib_FloatLib_Floats_Formats_BinaryInterchange_Model_maximum(lean_object*, lean_object*, lean_object*);
lean_object* lp_competition_ExactRuntime_scaleShiftSpec___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
lean_object* lp_competition_ExactRuntime_addReluSpec___boxed(lean_object*, lean_object*, lean_object*);
lean_object* lean_array_to_list(lean_object*);
lean_object* lp_competition_ExactRuntime_limbVal(lean_object*);
static lean_once_cell_t lp_competition_Submission_Acc_empty___closed__0_once = LEAN_ONCE_CELL_INITIALIZER;
static lean_object* lp_competition_Submission_Acc_empty___closed__0;
static lean_once_cell_t lp_competition_Submission_Acc_empty___closed__1_once = LEAN_ONCE_CELL_INITIALIZER;
static lean_object* lp_competition_Submission_Acc_empty___closed__1;
LEAN_EXPORT lean_object* lp_competition_Submission_Acc_empty;
LEAN_EXPORT lean_object* lp_competition_Submission_Acc_total(lean_object*);
LEAN_EXPORT lean_object* lp_competition_Submission_Acc_add(lean_object*, lean_object*, lean_object*, uint8_t);
LEAN_EXPORT lean_object* lp_competition_Submission_Acc_add___boxed(lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_Submission_Acc_markSpecial(lean_object*);
LEAN_EXPORT lean_object* lp_competition___private_Submission_0__Submission_Acc_add_match__1_splitter___redArg(lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition___private_Submission_0__Submission_Acc_add_match__1_splitter(lean_object*, lean_object*, lean_object*);
static lean_once_cell_t lp_competition___private_Submission_0__FloatLib_Floats_Formats_BinaryInterchange_Model_roundDyadicGeneral_match__1_splitter___redArg___closed__0_once = LEAN_ONCE_CELL_INITIALIZER;
static lean_object* lp_competition___private_Submission_0__FloatLib_Floats_Formats_BinaryInterchange_Model_roundDyadicGeneral_match__1_splitter___redArg___closed__0;
LEAN_EXPORT lean_object* lp_competition___private_Submission_0__FloatLib_Floats_Formats_BinaryInterchange_Model_roundDyadicGeneral_match__1_splitter___redArg(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition___private_Submission_0__FloatLib_Floats_Formats_BinaryInterchange_Model_roundDyadicGeneral_match__1_splitter___redArg___boxed(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition___private_Submission_0__FloatLib_Floats_Formats_BinaryInterchange_Model_roundDyadicGeneral_match__1_splitter(lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition___private_Submission_0__FloatLib_Floats_Formats_BinaryInterchange_Model_roundDyadicGeneral_match__1_splitter___boxed(lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_Submission_winVal(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_Submission_winVal___boxed(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition___private_Submission_0__Submission_winVal_match__1_splitter___redArg(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition___private_Submission_0__Submission_winVal_match__1_splitter___redArg___boxed(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition___private_Submission_0__Submission_winVal_match__1_splitter(lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition___private_Submission_0__Submission_winVal_match__1_splitter___boxed(lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_Submission_diffGo(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_Submission_diffGo___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_Submission_topGo(lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_Submission_topGo___boxed(lean_object*, lean_object*);
LEAN_EXPORT uint8_t lp_competition_Submission_anyGo(lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_Submission_anyGo___boxed(lean_object*, lean_object*);
static lean_once_cell_t lp_competition_Submission_finishDigits___closed__0_once = LEAN_ONCE_CELL_INITIALIZER;
static lean_object* lp_competition_Submission_finishDigits___closed__0;
static lean_once_cell_t lp_competition_Submission_finishDigits___closed__1_once = LEAN_ONCE_CELL_INITIALIZER;
static uint32_t lp_competition_Submission_finishDigits___closed__1;
static lean_once_cell_t lp_competition_Submission_finishDigits___closed__2_once = LEAN_ONCE_CELL_INITIALIZER;
static lean_object* lp_competition_Submission_finishDigits___closed__2;
static lean_once_cell_t lp_competition_Submission_finishDigits___closed__3_once = LEAN_ONCE_CELL_INITIALIZER;
static uint32_t lp_competition_Submission_finishDigits___closed__3;
static lean_once_cell_t lp_competition_Submission_finishDigits___closed__4_once = LEAN_ONCE_CELL_INITIALIZER;
static lean_object* lp_competition_Submission_finishDigits___closed__4;
static lean_once_cell_t lp_competition_Submission_finishDigits___closed__5_once = LEAN_ONCE_CELL_INITIALIZER;
static uint32_t lp_competition_Submission_finishDigits___closed__5;
static lean_once_cell_t lp_competition_Submission_finishDigits___closed__6_once = LEAN_ONCE_CELL_INITIALIZER;
static lean_object* lp_competition_Submission_finishDigits___closed__6;
static lean_once_cell_t lp_competition_Submission_finishDigits___closed__7_once = LEAN_ONCE_CELL_INITIALIZER;
static lean_object* lp_competition_Submission_finishDigits___closed__7;
static lean_once_cell_t lp_competition_Submission_finishDigits___closed__8_once = LEAN_ONCE_CELL_INITIALIZER;
static lean_object* lp_competition_Submission_finishDigits___closed__8;
static lean_once_cell_t lp_competition_Submission_finishDigits___closed__9_once = LEAN_ONCE_CELL_INITIALIZER;
static lean_object* lp_competition_Submission_finishDigits___closed__9;
static lean_once_cell_t lp_competition_Submission_finishDigits___closed__10_once = LEAN_ONCE_CELL_INITIALIZER;
static lean_object* lp_competition_Submission_finishDigits___closed__10;
static lean_once_cell_t lp_competition_Submission_finishDigits___closed__11_once = LEAN_ONCE_CELL_INITIALIZER;
static uint32_t lp_competition_Submission_finishDigits___closed__11;
static lean_once_cell_t lp_competition_Submission_finishDigits___closed__12_once = LEAN_ONCE_CELL_INITIALIZER;
static uint8_t lp_competition_Submission_finishDigits___closed__12;
LEAN_EXPORT uint32_t lp_competition_Submission_finishDigits(uint8_t, lean_object*, lean_object*, uint8_t);
LEAN_EXPORT lean_object* lp_competition_Submission_finishDigits___boxed(lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition___private_Submission_0__Submission_finishDigits_match__1_splitter___redArg(lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition___private_Submission_0__Submission_finishDigits_match__1_splitter___redArg___boxed(lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition___private_Submission_0__Submission_finishDigits_match__1_splitter(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition___private_Submission_0__Submission_finishDigits_match__1_splitter___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_Submission_highLimb(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_Submission_highLimb___boxed(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_foldrMUnsafe_fold___at___00Submission_finishFast_spec__0(lean_object*, size_t, size_t, lean_object*);
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_foldrMUnsafe_fold___at___00Submission_finishFast_spec__0___boxed(lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT uint32_t lp_competition_Submission_finishFast(lean_object*, lean_object*, lean_object*, uint8_t);
LEAN_EXPORT lean_object* lp_competition_Submission_finishFast___boxed(lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_Submission_dotStep(lean_object*, uint32_t, uint32_t);
LEAN_EXPORT lean_object* lp_competition_Submission_dotStep___boxed(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_Submission_dotLoop(lean_object*, lean_object*, lean_object*, lean_object*, uint8_t, uint8_t, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_Submission_dotLoop___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT uint32_t lp_competition_Submission_dotFn___lam__0(lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_Submission_dotFn___lam__0___boxed(lean_object*, lean_object*);
LEAN_EXPORT uint32_t lp_competition_Submission_dotFn___lam__1(lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_Submission_dotFn___lam__1___boxed(lean_object*, lean_object*);
static lean_once_cell_t lp_competition_Submission_dotFn___closed__0_once = LEAN_ONCE_CELL_INITIALIZER;
static lean_object* lp_competition_Submission_dotFn___closed__0;
static lean_once_cell_t lp_competition_Submission_dotFn___closed__1_once = LEAN_ONCE_CELL_INITIALIZER;
static lean_object* lp_competition_Submission_dotFn___closed__1;
LEAN_EXPORT uint32_t lp_competition_Submission_dotFn(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_Submission_dotFn___boxed(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_Submission_dotX___lam__0___boxed__const__1;
LEAN_EXPORT uint32_t lp_competition_Submission_dotX___lam__0(lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_Submission_dotX___lam__0___boxed(lean_object*, lean_object*);
LEAN_EXPORT uint32_t lp_competition_Submission_dotX___lam__1(lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_Submission_dotX___lam__1___boxed(lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_Submission_dotLoop___at___00Submission_dotX_spec__0(lean_object*, lean_object*, lean_object*, lean_object*, uint8_t, uint8_t, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_Submission_dotLoop___at___00Submission_dotX_spec__0___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT uint32_t lp_competition_Submission_dotX(lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_Submission_dotX___boxed(lean_object*, lean_object*);
LEAN_EXPORT uint32_t lp_competition_Submission_sumX___lam__0(lean_object*);
LEAN_EXPORT lean_object* lp_competition_Submission_sumX___lam__0___boxed(lean_object*);
LEAN_EXPORT uint32_t lp_competition_Submission_sumX___lam__1(uint32_t, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_Submission_sumX___lam__1___boxed(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_Submission_dotLoop___at___00Submission_sumX_spec__0(lean_object*, lean_object*, lean_object*, uint8_t, uint8_t, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_Submission_dotLoop___at___00Submission_sumX_spec__0___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
static const lean_closure_object lp_competition_Submission_sumX___closed__0_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_closure_object) + sizeof(void*)*0, .m_other = 0, .m_tag = 245}, .m_fun = (void*)lp_competition_Submission_sumX___lam__0___boxed, .m_arity = 1, .m_num_fixed = 0, .m_objs = {} };
static const lean_object* lp_competition_Submission_sumX___closed__0 = (const lean_object*)&lp_competition_Submission_sumX___closed__0_value;
LEAN_EXPORT uint32_t lp_competition_Submission_sumX(lean_object*);
LEAN_EXPORT lean_object* lp_competition_Submission_sumX___boxed(lean_object*);
LEAN_EXPORT lean_object* lp_competition_Submission_keyOf(uint32_t);
LEAN_EXPORT lean_object* lp_competition_Submission_keyOf___boxed(lean_object*);
static lean_once_cell_t lp_competition_Submission_maxW___closed__0_once = LEAN_ONCE_CELL_INITIALIZER;
static lean_object* lp_competition_Submission_maxW___closed__0;
static lean_once_cell_t lp_competition_Submission_maxW___closed__1_once = LEAN_ONCE_CELL_INITIALIZER;
static lean_object* lp_competition_Submission_maxW___closed__1;
static const lean_ctor_object lp_competition_Submission_maxW___closed__2_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_ctor_object) + sizeof(void*)*3 + 8, .m_other = 3, .m_tag = 0}, .m_objs = {((lean_object*)(((size_t)(8) << 1) | 1)),((lean_object*)(((size_t)(23) << 1) | 1)),((lean_object*)(((size_t)(127) << 1) | 1)),LEAN_SCALAR_PTR_LITERAL(0, 0, 0, 0, 0, 0, 0, 0)}};
static const lean_object* lp_competition_Submission_maxW___closed__2 = (const lean_object*)&lp_competition_Submission_maxW___closed__2_value;
LEAN_EXPORT uint32_t lp_competition_Submission_maxW(uint32_t, uint32_t);
LEAN_EXPORT lean_object* lp_competition_Submission_maxW___boxed(lean_object*, lean_object*);
LEAN_EXPORT uint32_t lp_competition_List_foldl___at___00List_foldl___at___00Submission_maxpoolW_spec__0_spec__0(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, uint32_t, lean_object*);
LEAN_EXPORT lean_object* lp_competition_List_foldl___at___00List_foldl___at___00Submission_maxpoolW_spec__0_spec__0___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT uint32_t lp_competition_List_foldl___at___00Submission_maxpoolW_spec__0(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, uint32_t, lean_object*);
LEAN_EXPORT lean_object* lp_competition_List_foldl___at___00Submission_maxpoolW_spec__0___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT uint32_t lp_competition_Submission_maxpoolW___lam__0(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_Submission_maxpoolW___lam__0___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_Submission_maxpoolW(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_Submission_maxpoolW___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_mapMUnsafe_map___at___00Submission_cacheRats_spec__0(size_t, size_t, lean_object*);
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_mapMUnsafe_map___at___00Submission_cacheRats_spec__0___boxed(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_Submission_cacheRats(lean_object*);
LEAN_EXPORT lean_object* lp_competition_List_foldl___at___00Submission_rowMeanCached_spec__0(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_List_foldl___at___00Submission_rowMeanCached_spec__0___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
static lean_once_cell_t lp_competition_Submission_rowMeanCached___closed__0_once = LEAN_ONCE_CELL_INITIALIZER;
static lean_object* lp_competition_Submission_rowMeanCached___closed__0;
LEAN_EXPORT lean_object* lp_competition_Submission_rowMeanCached(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_Submission_rowMeanCached___boxed(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_List_foldl___at___00Submission_rowVarianceCached_spec__0(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_List_foldl___at___00Submission_rowVarianceCached_spec__0___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_Submission_rowVarianceCached(lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_Submission_rowVarianceCached___boxed(lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT uint32_t lp_competition_Submission_rmsnormStableCached___lam__0(lean_object*, lean_object*, uint32_t, lean_object*);
LEAN_EXPORT lean_object* lp_competition_Submission_rmsnormStableCached___lam__0___boxed(lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT uint32_t lp_competition_Submission_rmsnormStableCached___lam__1(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_Submission_rmsnormStableCached___lam__1___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_Submission_rmsnormStableCached(lean_object*, lean_object*, uint32_t, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_Submission_rmsnormStableCached___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_Submission_layernormStableCached___lam__0(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_Submission_layernormStableCached___lam__0___boxed(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT uint32_t lp_competition_Submission_layernormStableCached___lam__1(lean_object*, lean_object*, lean_object*, lean_object*, uint32_t, lean_object*);
LEAN_EXPORT lean_object* lp_competition_Submission_layernormStableCached___lam__1___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT uint32_t lp_competition_Submission_layernormStableCached___lam__2(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_Submission_layernormStableCached___lam__2___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_Submission_layernormStableCached(lean_object*, lean_object*, uint32_t, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_Submission_layernormStableCached___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT uint32_t lp_competition_ExactRuntime_rmsnormLegacyWith___at___00Submission_rmsnormCached_spec__1___lam__2(uint32_t, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_ExactRuntime_rmsnormLegacyWith___at___00Submission_rmsnormCached_spec__1___lam__2___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT uint32_t lp_competition_ExactRuntime_rmsnormLegacyWith___at___00Submission_rmsnormCached_spec__1___lam__1(lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_ExactRuntime_rmsnormLegacyWith___at___00Submission_rmsnormCached_spec__1___lam__1___boxed(lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_Submission_dotLoop___at___00Submission_dotLoop___at___00Submission_rmsnormCached_spec__0___at___00ExactRuntime_rmsnormLegacyWith___at___00Submission_rmsnormCached_spec__1_spec__1_spec__2(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, uint8_t, uint8_t, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_Submission_dotLoop___at___00Submission_dotLoop___at___00Submission_rmsnormCached_spec__0___at___00ExactRuntime_rmsnormLegacyWith___at___00Submission_rmsnormCached_spec__1_spec__1_spec__2___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_Submission_dotLoop___at___00Submission_rmsnormCached_spec__0___at___00ExactRuntime_rmsnormLegacyWith___at___00Submission_rmsnormCached_spec__1_spec__1(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, uint8_t, uint8_t, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_Submission_dotLoop___at___00Submission_rmsnormCached_spec__0___at___00ExactRuntime_rmsnormLegacyWith___at___00Submission_rmsnormCached_spec__1_spec__1___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT uint32_t lp_competition_ExactRuntime_rmsnormLegacyWith___at___00Submission_rmsnormCached_spec__1___lam__0(lean_object*, lean_object*, uint32_t, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_ExactRuntime_rmsnormLegacyWith___at___00Submission_rmsnormCached_spec__1___lam__0___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT uint32_t lp_competition_ExactRuntime_rmsnormLegacyWith___at___00Submission_rmsnormCached_spec__1___lam__3(lean_object*, lean_object*, uint8_t, uint32_t, uint32_t, lean_object*);
LEAN_EXPORT lean_object* lp_competition_ExactRuntime_rmsnormLegacyWith___at___00Submission_rmsnormCached_spec__1___lam__3___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_ExactRuntime_rmsnormLegacyWith___at___00Submission_rmsnormCached_spec__1(uint8_t, lean_object*, lean_object*, uint32_t, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_ExactRuntime_rmsnormLegacyWith___at___00Submission_rmsnormCached_spec__1___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_Submission_rmsnormCached(lean_object*, lean_object*, uint32_t, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_Submission_rmsnormCached___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_Submission_dotLoop___at___00Submission_rmsnormCached_spec__0(lean_object*, lean_object*, lean_object*, lean_object*, uint8_t, uint8_t, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_Submission_dotLoop___at___00Submission_rmsnormCached_spec__0___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT uint32_t lp_competition_ExactRuntime_layernormLegacyWith___at___00Submission_layernormCached_spec__0___lam__4(lean_object*, uint32_t, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_ExactRuntime_layernormLegacyWith___at___00Submission_layernormCached_spec__0___lam__4___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT uint32_t lp_competition_ExactRuntime_layernormLegacyWith___at___00Submission_layernormCached_spec__0___lam__0(lean_object*);
LEAN_EXPORT lean_object* lp_competition_ExactRuntime_layernormLegacyWith___at___00Submission_layernormCached_spec__0___lam__0___boxed(lean_object*);
LEAN_EXPORT uint32_t lp_competition_ExactRuntime_layernormLegacyWith___at___00Submission_layernormCached_spec__0___lam__2(uint32_t, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_ExactRuntime_layernormLegacyWith___at___00Submission_layernormCached_spec__0___lam__2___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT uint32_t lp_competition_ExactRuntime_layernormLegacyWith___at___00Submission_layernormCached_spec__0___lam__5(uint32_t, lean_object*, lean_object*, lean_object*, lean_object*, uint32_t, lean_object*);
LEAN_EXPORT lean_object* lp_competition_ExactRuntime_layernormLegacyWith___at___00Submission_layernormCached_spec__0___lam__5___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT uint32_t lp_competition_ExactRuntime_layernormLegacyWith___at___00Submission_layernormCached_spec__0___lam__6(lean_object*, uint32_t, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_ExactRuntime_layernormLegacyWith___at___00Submission_layernormCached_spec__0___lam__6___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT uint32_t lp_competition_ExactRuntime_layernormLegacyWith___at___00Submission_layernormCached_spec__0___lam__1(lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_ExactRuntime_layernormLegacyWith___at___00Submission_layernormCached_spec__0___lam__1___boxed(lean_object*, lean_object*);
LEAN_EXPORT uint32_t lp_competition_ExactRuntime_layernormLegacyWith___at___00Submission_layernormCached_spec__0___lam__3(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_ExactRuntime_layernormLegacyWith___at___00Submission_layernormCached_spec__0___lam__3___boxed(lean_object*, lean_object*, lean_object*);
static const lean_closure_object lp_competition_ExactRuntime_layernormLegacyWith___at___00Submission_layernormCached_spec__0___closed__0_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_closure_object) + sizeof(void*)*0, .m_other = 0, .m_tag = 245}, .m_fun = (void*)lp_competition_ExactRuntime_layernormLegacyWith___at___00Submission_layernormCached_spec__0___lam__0___boxed, .m_arity = 1, .m_num_fixed = 0, .m_objs = {} };
static const lean_object* lp_competition_ExactRuntime_layernormLegacyWith___at___00Submission_layernormCached_spec__0___closed__0 = (const lean_object*)&lp_competition_ExactRuntime_layernormLegacyWith___at___00Submission_layernormCached_spec__0___closed__0_value;
static const lean_closure_object lp_competition_ExactRuntime_layernormLegacyWith___at___00Submission_layernormCached_spec__0___closed__1_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_closure_object) + sizeof(void*)*0, .m_other = 0, .m_tag = 245}, .m_fun = (void*)lp_competition_ExactRuntime_layernormLegacyWith___at___00Submission_layernormCached_spec__0___lam__3___boxed, .m_arity = 3, .m_num_fixed = 0, .m_objs = {} };
static const lean_object* lp_competition_ExactRuntime_layernormLegacyWith___at___00Submission_layernormCached_spec__0___closed__1 = (const lean_object*)&lp_competition_ExactRuntime_layernormLegacyWith___at___00Submission_layernormCached_spec__0___closed__1_value;
LEAN_EXPORT lean_object* lp_competition_ExactRuntime_layernormLegacyWith___at___00Submission_layernormCached_spec__0(lean_object*, lean_object*, uint32_t, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_ExactRuntime_layernormLegacyWith___at___00Submission_layernormCached_spec__0___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_Submission_layernormCached(lean_object*, lean_object*, uint32_t, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_Submission_layernormCached___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT uint32_t lp_competition_ExactRuntime_conv2dWith___at___00Submission_kernels_spec__2___lam__1(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_ExactRuntime_conv2dWith___at___00Submission_kernels_spec__2___lam__1___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT uint32_t lp_competition_ExactRuntime_conv2dWith___at___00Submission_kernels_spec__2___lam__0(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_ExactRuntime_conv2dWith___at___00Submission_kernels_spec__2___lam__0___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_Submission_dotLoop___at___00Submission_rmsnormCached_spec__0___at___00ExactRuntime_conv2dWith___at___00Submission_kernels_spec__2_spec__4(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, uint8_t, uint8_t, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_Submission_dotLoop___at___00Submission_rmsnormCached_spec__0___at___00ExactRuntime_conv2dWith___at___00Submission_kernels_spec__2_spec__4___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT uint32_t lp_competition_ExactRuntime_conv2dWith___at___00Submission_kernels_spec__2___lam__2(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, uint8_t, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_ExactRuntime_conv2dWith___at___00Submission_kernels_spec__2___lam__2___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_ExactRuntime_conv2dWith___at___00Submission_kernels_spec__2(lean_object*, uint8_t, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_ExactRuntime_conv2dWith___at___00Submission_kernels_spec__2___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT uint32_t lp_competition_ExactRuntime_gemmWith___at___00Submission_kernels_spec__1___lam__0(lean_object*, lean_object*, lean_object*, lean_object*, uint32_t, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_ExactRuntime_gemmWith___at___00Submission_kernels_spec__1___lam__0___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_Submission_dotLoop___at___00Submission_rmsnormCached_spec__0___at___00ExactRuntime_gemmWith___at___00Submission_kernels_spec__1_spec__2(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, uint8_t, uint8_t, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_Submission_dotLoop___at___00Submission_rmsnormCached_spec__0___at___00ExactRuntime_gemmWith___at___00Submission_kernels_spec__1_spec__2___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT uint32_t lp_competition_ExactRuntime_gemmWith___at___00Submission_kernels_spec__1___lam__1(lean_object*, lean_object*, lean_object*, lean_object*, uint32_t, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_ExactRuntime_gemmWith___at___00Submission_kernels_spec__1___lam__1___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT uint32_t lp_competition_ExactRuntime_gemmWith___at___00Submission_kernels_spec__1___lam__2(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, uint32_t, lean_object*);
LEAN_EXPORT lean_object* lp_competition_ExactRuntime_gemmWith___at___00Submission_kernels_spec__1___lam__2___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_ExactRuntime_gemmWith___at___00Submission_kernels_spec__1(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_ExactRuntime_gemmWith___at___00Submission_kernels_spec__1___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT uint32_t lp_competition_ExactRuntime_linearWith___at___00Submission_kernels_spec__0___lam__1(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_ExactRuntime_linearWith___at___00Submission_kernels_spec__0___lam__1___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT uint32_t lp_competition_ExactRuntime_linearWith___at___00Submission_kernels_spec__0___lam__0(lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_ExactRuntime_linearWith___at___00Submission_kernels_spec__0___lam__0___boxed(lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_Submission_dotLoop___at___00Submission_rmsnormCached_spec__0___at___00ExactRuntime_linearWith___at___00Submission_kernels_spec__0_spec__0(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, uint8_t, uint8_t, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_Submission_dotLoop___at___00Submission_rmsnormCached_spec__0___at___00ExactRuntime_linearWith___at___00Submission_kernels_spec__0_spec__0___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT uint32_t lp_competition_ExactRuntime_linearWith___at___00Submission_kernels_spec__0___lam__2(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, uint8_t, lean_object*);
LEAN_EXPORT lean_object* lp_competition_ExactRuntime_linearWith___at___00Submission_kernels_spec__0___lam__2___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_ExactRuntime_linearWith___at___00Submission_kernels_spec__0(lean_object*, lean_object*, lean_object*, uint8_t, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_ExactRuntime_linearWith___at___00Submission_kernels_spec__0___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT uint32_t lp_competition_ExactRuntime_avgpoolWith___at___00Submission_kernels_spec__4___lam__1(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_ExactRuntime_avgpoolWith___at___00Submission_kernels_spec__4___lam__1___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_Submission_dotLoop___at___00Submission_rmsnormCached_spec__0___at___00ExactRuntime_avgpoolWith___at___00Submission_kernels_spec__4_spec__8(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, uint8_t, uint8_t, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_Submission_dotLoop___at___00Submission_rmsnormCached_spec__0___at___00ExactRuntime_avgpoolWith___at___00Submission_kernels_spec__4_spec__8___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT uint32_t lp_competition_ExactRuntime_avgpoolWith___at___00Submission_kernels_spec__4___lam__0(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_ExactRuntime_avgpoolWith___at___00Submission_kernels_spec__4___lam__0___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_ExactRuntime_avgpoolWith___at___00Submission_kernels_spec__4(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_ExactRuntime_avgpoolWith___at___00Submission_kernels_spec__4___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT uint32_t lp_competition_ExactRuntime_depthwiseWith___at___00Submission_kernels_spec__3___lam__1(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_ExactRuntime_depthwiseWith___at___00Submission_kernels_spec__3___lam__1___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT uint32_t lp_competition_ExactRuntime_depthwiseWith___at___00Submission_kernels_spec__3___lam__0(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_ExactRuntime_depthwiseWith___at___00Submission_kernels_spec__3___lam__0___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_Submission_dotLoop___at___00Submission_rmsnormCached_spec__0___at___00ExactRuntime_depthwiseWith___at___00Submission_kernels_spec__3_spec__6(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, uint8_t, uint8_t, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_Submission_dotLoop___at___00Submission_rmsnormCached_spec__0___at___00ExactRuntime_depthwiseWith___at___00Submission_kernels_spec__3_spec__6___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT uint32_t lp_competition_ExactRuntime_depthwiseWith___at___00Submission_kernels_spec__3___lam__2(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, uint8_t, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_ExactRuntime_depthwiseWith___at___00Submission_kernels_spec__3___lam__2___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_ExactRuntime_depthwiseWith___at___00Submission_kernels_spec__3(lean_object*, uint8_t, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_ExactRuntime_depthwiseWith___at___00Submission_kernels_spec__3___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
static const lean_closure_object lp_competition_Submission_kernels___closed__0_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_closure_object) + sizeof(void*)*0, .m_other = 0, .m_tag = 245}, .m_fun = (void*)lp_competition_Submission_sumX___boxed, .m_arity = 1, .m_num_fixed = 0, .m_objs = {} };
static const lean_object* lp_competition_Submission_kernels___closed__0 = (const lean_object*)&lp_competition_Submission_kernels___closed__0_value;
static const lean_closure_object lp_competition_Submission_kernels___closed__1_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_closure_object) + sizeof(void*)*0, .m_other = 0, .m_tag = 245}, .m_fun = (void*)lp_competition_Submission_dotX___boxed, .m_arity = 2, .m_num_fixed = 0, .m_objs = {} };
static const lean_object* lp_competition_Submission_kernels___closed__1 = (const lean_object*)&lp_competition_Submission_kernels___closed__1_value;
static const lean_ctor_object lp_competition_Submission_kernels___closed__2_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_ctor_object) + sizeof(void*)*2 + 0, .m_other = 2, .m_tag = 0}, .m_objs = {((lean_object*)&lp_competition_Submission_kernels___closed__0_value),((lean_object*)&lp_competition_Submission_kernels___closed__1_value)}};
static const lean_object* lp_competition_Submission_kernels___closed__2 = (const lean_object*)&lp_competition_Submission_kernels___closed__2_value;
static const lean_closure_object lp_competition_Submission_kernels___closed__3_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_closure_object) + sizeof(void*)*0, .m_other = 0, .m_tag = 245}, .m_fun = (void*)lp_competition_ExactRuntime_linearWith___at___00Submission_kernels_spec__0___boxed, .m_arity = 7, .m_num_fixed = 0, .m_objs = {} };
static const lean_object* lp_competition_Submission_kernels___closed__3 = (const lean_object*)&lp_competition_Submission_kernels___closed__3_value;
static const lean_closure_object lp_competition_Submission_kernels___closed__4_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_closure_object) + sizeof(void*)*0, .m_other = 0, .m_tag = 245}, .m_fun = (void*)lp_competition_ExactRuntime_gemmWith___at___00Submission_kernels_spec__1___boxed, .m_arity = 6, .m_num_fixed = 0, .m_objs = {} };
static const lean_object* lp_competition_Submission_kernels___closed__4 = (const lean_object*)&lp_competition_Submission_kernels___closed__4_value;
static const lean_ctor_object lp_competition_Submission_kernels___closed__5_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_ctor_object) + sizeof(void*)*2 + 0, .m_other = 2, .m_tag = 0}, .m_objs = {((lean_object*)&lp_competition_Submission_kernels___closed__3_value),((lean_object*)&lp_competition_Submission_kernels___closed__4_value)}};
static const lean_object* lp_competition_Submission_kernels___closed__5 = (const lean_object*)&lp_competition_Submission_kernels___closed__5_value;
static const lean_closure_object lp_competition_Submission_kernels___closed__6_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_closure_object) + sizeof(void*)*0, .m_other = 0, .m_tag = 245}, .m_fun = (void*)lp_competition_ExactRuntime_conv2dWith___at___00Submission_kernels_spec__2___boxed, .m_arity = 5, .m_num_fixed = 0, .m_objs = {} };
static const lean_object* lp_competition_Submission_kernels___closed__6 = (const lean_object*)&lp_competition_Submission_kernels___closed__6_value;
static const lean_closure_object lp_competition_Submission_kernels___closed__7_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_closure_object) + sizeof(void*)*0, .m_other = 0, .m_tag = 245}, .m_fun = (void*)lp_competition_ExactRuntime_depthwiseWith___at___00Submission_kernels_spec__3___boxed, .m_arity = 5, .m_num_fixed = 0, .m_objs = {} };
static const lean_object* lp_competition_Submission_kernels___closed__7 = (const lean_object*)&lp_competition_Submission_kernels___closed__7_value;
static const lean_ctor_object lp_competition_Submission_kernels___closed__8_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_ctor_object) + sizeof(void*)*2 + 0, .m_other = 2, .m_tag = 0}, .m_objs = {((lean_object*)&lp_competition_Submission_kernels___closed__6_value),((lean_object*)&lp_competition_Submission_kernels___closed__7_value)}};
static const lean_object* lp_competition_Submission_kernels___closed__8 = (const lean_object*)&lp_competition_Submission_kernels___closed__8_value;
static const lean_closure_object lp_competition_Submission_kernels___closed__9_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_closure_object) + sizeof(void*)*0, .m_other = 0, .m_tag = 245}, .m_fun = (void*)lp_competition_ExactRuntime_avgpoolWith___at___00Submission_kernels_spec__4___boxed, .m_arity = 5, .m_num_fixed = 0, .m_objs = {} };
static const lean_object* lp_competition_Submission_kernels___closed__9 = (const lean_object*)&lp_competition_Submission_kernels___closed__9_value;
static const lean_closure_object lp_competition_Submission_kernels___closed__10_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_closure_object) + sizeof(void*)*0, .m_other = 0, .m_tag = 245}, .m_fun = (void*)lp_competition_Submission_maxpoolW___boxed, .m_arity = 5, .m_num_fixed = 0, .m_objs = {} };
static const lean_object* lp_competition_Submission_kernels___closed__10 = (const lean_object*)&lp_competition_Submission_kernels___closed__10_value;
static const lean_closure_object lp_competition_Submission_kernels___closed__11_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_closure_object) + sizeof(void*)*0, .m_other = 0, .m_tag = 245}, .m_fun = (void*)lp_competition_ExactRuntime_addReluSpec___boxed, .m_arity = 3, .m_num_fixed = 0, .m_objs = {} };
static const lean_object* lp_competition_Submission_kernels___closed__11 = (const lean_object*)&lp_competition_Submission_kernels___closed__11_value;
static const lean_closure_object lp_competition_Submission_kernels___closed__12_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_closure_object) + sizeof(void*)*0, .m_other = 0, .m_tag = 245}, .m_fun = (void*)lp_competition_ExactRuntime_scaleShiftSpec___boxed, .m_arity = 6, .m_num_fixed = 0, .m_objs = {} };
static const lean_object* lp_competition_Submission_kernels___closed__12 = (const lean_object*)&lp_competition_Submission_kernels___closed__12_value;
static const lean_ctor_object lp_competition_Submission_kernels___closed__13_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_ctor_object) + sizeof(void*)*4 + 0, .m_other = 4, .m_tag = 0}, .m_objs = {((lean_object*)&lp_competition_Submission_kernels___closed__9_value),((lean_object*)&lp_competition_Submission_kernels___closed__10_value),((lean_object*)&lp_competition_Submission_kernels___closed__11_value),((lean_object*)&lp_competition_Submission_kernels___closed__12_value)}};
static const lean_object* lp_competition_Submission_kernels___closed__13 = (const lean_object*)&lp_competition_Submission_kernels___closed__13_value;
static const lean_closure_object lp_competition_Submission_kernels___closed__14_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_closure_object) + sizeof(void*)*0, .m_other = 0, .m_tag = 245}, .m_fun = (void*)lp_competition_Submission_rmsnormCached___boxed, .m_arity = 5, .m_num_fixed = 0, .m_objs = {} };
static const lean_object* lp_competition_Submission_kernels___closed__14 = (const lean_object*)&lp_competition_Submission_kernels___closed__14_value;
static const lean_closure_object lp_competition_Submission_kernels___closed__15_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_closure_object) + sizeof(void*)*0, .m_other = 0, .m_tag = 245}, .m_fun = (void*)lp_competition_Submission_layernormCached___boxed, .m_arity = 6, .m_num_fixed = 0, .m_objs = {} };
static const lean_object* lp_competition_Submission_kernels___closed__15 = (const lean_object*)&lp_competition_Submission_kernels___closed__15_value;
static const lean_ctor_object lp_competition_Submission_kernels___closed__16_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_ctor_object) + sizeof(void*)*2 + 0, .m_other = 2, .m_tag = 0}, .m_objs = {((lean_object*)&lp_competition_Submission_kernels___closed__14_value),((lean_object*)&lp_competition_Submission_kernels___closed__15_value)}};
static const lean_object* lp_competition_Submission_kernels___closed__16 = (const lean_object*)&lp_competition_Submission_kernels___closed__16_value;
static const lean_ctor_object lp_competition_Submission_kernels___closed__17_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_ctor_object) + sizeof(void*)*5 + 0, .m_other = 5, .m_tag = 0}, .m_objs = {((lean_object*)&lp_competition_Submission_kernels___closed__2_value),((lean_object*)&lp_competition_Submission_kernels___closed__5_value),((lean_object*)&lp_competition_Submission_kernels___closed__8_value),((lean_object*)&lp_competition_Submission_kernels___closed__13_value),((lean_object*)&lp_competition_Submission_kernels___closed__16_value)}};
static const lean_object* lp_competition_Submission_kernels___closed__17 = (const lean_object*)&lp_competition_Submission_kernels___closed__17_value;
LEAN_EXPORT const lean_object* lp_competition_Submission_kernels = (const lean_object*)&lp_competition_Submission_kernels___closed__17_value;
static lean_object* _init_lp_competition_Submission_Acc_empty___closed__0(void){
_start:
{
lean_object* v___x_1_; lean_object* v___x_2_; lean_object* v___x_3_; 
v___x_1_ = lean_unsigned_to_nat(0u);
v___x_2_ = lean_unsigned_to_nat(18u);
v___x_3_ = lean_mk_array(v___x_2_, v___x_1_);
return v___x_3_;
}
}
static lean_object* _init_lp_competition_Submission_Acc_empty___closed__1(void){
_start:
{
uint8_t v___x_4_; uint8_t v___x_5_; lean_object* v___x_6_; lean_object* v___x_7_; 
v___x_4_ = 1;
v___x_5_ = 0;
v___x_6_ = lean_obj_once(&lp_competition_Submission_Acc_empty___closed__0, &lp_competition_Submission_Acc_empty___closed__0_once, _init_lp_competition_Submission_Acc_empty___closed__0);
v___x_7_ = lean_alloc_ctor(0, 2, 2);
lean_ctor_set(v___x_7_, 0, v___x_6_);
lean_ctor_set(v___x_7_, 1, v___x_6_);
lean_ctor_set_uint8(v___x_7_, sizeof(void*)*2, v___x_5_);
lean_ctor_set_uint8(v___x_7_, sizeof(void*)*2 + 1, v___x_4_);
return v___x_7_;
}
}
static lean_object* _init_lp_competition_Submission_Acc_empty(void){
_start:
{
lean_object* v___x_8_; 
v___x_8_ = lean_obj_once(&lp_competition_Submission_Acc_empty___closed__1, &lp_competition_Submission_Acc_empty___closed__1_once, _init_lp_competition_Submission_Acc_empty___closed__1);
return v___x_8_;
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_Acc_total(lean_object* v_acc_9_){
_start:
{
lean_object* v_pos_10_; lean_object* v_neg_11_; lean_object* v___x_12_; lean_object* v___x_13_; lean_object* v___x_14_; lean_object* v___x_15_; lean_object* v___x_16_; lean_object* v___x_17_; lean_object* v___x_18_; 
v_pos_10_ = lean_ctor_get(v_acc_9_, 0);
lean_inc_ref(v_pos_10_);
v_neg_11_ = lean_ctor_get(v_acc_9_, 1);
lean_inc_ref(v_neg_11_);
lean_dec_ref(v_acc_9_);
v___x_12_ = lean_array_to_list(v_pos_10_);
v___x_13_ = lp_competition_ExactRuntime_limbVal(v___x_12_);
lean_dec(v___x_12_);
v___x_14_ = lean_nat_to_int(v___x_13_);
v___x_15_ = lean_array_to_list(v_neg_11_);
v___x_16_ = lp_competition_ExactRuntime_limbVal(v___x_15_);
lean_dec(v___x_15_);
v___x_17_ = lean_nat_to_int(v___x_16_);
v___x_18_ = lean_int_sub(v___x_14_, v___x_17_);
lean_dec(v___x_17_);
lean_dec(v___x_14_);
return v___x_18_;
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_Acc_add(lean_object* v_acc_19_, lean_object* v_m_20_, lean_object* v_idx_21_, uint8_t v_neg_22_){
_start:
{
lean_object* v_pos_23_; lean_object* v_neg_24_; uint8_t v_special_25_; uint8_t v_negZero_26_; lean_object* v___x_27_; uint8_t v___x_28_; 
v_pos_23_ = lean_ctor_get(v_acc_19_, 0);
v_neg_24_ = lean_ctor_get(v_acc_19_, 1);
v_special_25_ = lean_ctor_get_uint8(v_acc_19_, sizeof(void*)*2);
v_negZero_26_ = lean_ctor_get_uint8(v_acc_19_, sizeof(void*)*2 + 1);
v___x_27_ = lean_unsigned_to_nat(0u);
v___x_28_ = lean_nat_dec_eq(v_m_20_, v___x_27_);
if (v___x_28_ == 0)
{
lean_object* v___x_30_; uint8_t v_isShared_31_; uint8_t v_isSharedCheck_110_; 
lean_inc_ref(v_neg_24_);
lean_inc_ref(v_pos_23_);
v_isSharedCheck_110_ = !lean_is_exclusive(v_acc_19_);
if (v_isSharedCheck_110_ == 0)
{
lean_object* v_unused_111_; lean_object* v_unused_112_; 
v_unused_111_ = lean_ctor_get(v_acc_19_, 1);
lean_dec(v_unused_111_);
v_unused_112_ = lean_ctor_get(v_acc_19_, 0);
lean_dec(v_unused_112_);
v___x_30_ = v_acc_19_;
v_isShared_31_ = v_isSharedCheck_110_;
goto v_resetjp_29_;
}
else
{
lean_dec(v_acc_19_);
v___x_30_ = lean_box(0);
v_isShared_31_ = v_isSharedCheck_110_;
goto v_resetjp_29_;
}
v_resetjp_29_:
{
if (v_neg_22_ == 0)
{
uint64_t v___x_32_; lean_object* v___x_33_; lean_object* v___x_34_; lean_object* v_l_35_; lean_object* v___x_36_; uint64_t v_r_37_; lean_object* v___x_38_; uint64_t v___x_39_; uint64_t v___x_40_; uint64_t v___x_41_; uint64_t v___x_42_; uint64_t v___x_43_; uint64_t v___x_44_; lean_object* v_hi_45_; lean_object* v___y_47_; lean_object* v___x_62_; uint8_t v___x_63_; 
v___x_32_ = lean_uint64_of_nat(v_m_20_);
v___x_33_ = lean_unsigned_to_nat(32u);
v___x_34_ = lean_unsigned_to_nat(5u);
v_l_35_ = lean_nat_shiftr(v_idx_21_, v___x_34_);
v___x_36_ = lean_nat_mod(v_idx_21_, v___x_33_);
v_r_37_ = lean_uint64_of_nat(v___x_36_);
lean_dec(v___x_36_);
v___x_38_ = lean_unsigned_to_nat(1u);
v___x_39_ = 1ULL;
v___x_40_ = 32ULL;
v___x_41_ = lean_uint64_sub(v___x_40_, v_r_37_);
v___x_42_ = lean_uint64_shift_left(v___x_39_, v___x_41_);
v___x_43_ = lean_uint64_mod(v___x_32_, v___x_42_);
v___x_44_ = lean_uint64_shift_right(v___x_32_, v___x_41_);
v_hi_45_ = lean_uint64_to_nat(v___x_44_);
v___x_62_ = lean_array_get_size(v_pos_23_);
v___x_63_ = lean_nat_dec_lt(v_l_35_, v___x_62_);
if (v___x_63_ == 0)
{
v___y_47_ = v_pos_23_;
goto v___jp_46_;
}
else
{
uint64_t v___x_64_; lean_object* v_lo_65_; lean_object* v_v_66_; lean_object* v___x_67_; lean_object* v_xs_x27_68_; lean_object* v___x_69_; lean_object* v___x_70_; 
v___x_64_ = lean_uint64_shift_left(v___x_43_, v_r_37_);
v_lo_65_ = lean_uint64_to_nat(v___x_64_);
v_v_66_ = lean_array_fget(v_pos_23_, v_l_35_);
v___x_67_ = lean_box(0);
v_xs_x27_68_ = lean_array_fset(v_pos_23_, v_l_35_, v___x_67_);
v___x_69_ = lean_nat_add(v_v_66_, v_lo_65_);
lean_dec(v_lo_65_);
lean_dec(v_v_66_);
v___x_70_ = lean_array_fset(v_xs_x27_68_, v_l_35_, v___x_69_);
v___y_47_ = v___x_70_;
goto v___jp_46_;
}
v___jp_46_:
{
lean_object* v___x_48_; lean_object* v___x_49_; uint8_t v___x_50_; 
v___x_48_ = lean_nat_add(v_l_35_, v___x_38_);
lean_dec(v_l_35_);
v___x_49_ = lean_array_get_size(v___y_47_);
v___x_50_ = lean_nat_dec_lt(v___x_48_, v___x_49_);
if (v___x_50_ == 0)
{
lean_object* v___x_52_; 
lean_dec(v___x_48_);
lean_dec(v_hi_45_);
if (v_isShared_31_ == 0)
{
lean_ctor_set(v___x_30_, 0, v___y_47_);
v___x_52_ = v___x_30_;
goto v_reusejp_51_;
}
else
{
lean_object* v_reuseFailAlloc_53_; 
v_reuseFailAlloc_53_ = lean_alloc_ctor(0, 2, 2);
lean_ctor_set(v_reuseFailAlloc_53_, 0, v___y_47_);
lean_ctor_set(v_reuseFailAlloc_53_, 1, v_neg_24_);
lean_ctor_set_uint8(v_reuseFailAlloc_53_, sizeof(void*)*2, v_special_25_);
v___x_52_ = v_reuseFailAlloc_53_;
goto v_reusejp_51_;
}
v_reusejp_51_:
{
lean_ctor_set_uint8(v___x_52_, sizeof(void*)*2 + 1, v_neg_22_);
return v___x_52_;
}
}
else
{
lean_object* v_v_54_; lean_object* v___x_55_; lean_object* v_xs_x27_56_; lean_object* v___x_57_; lean_object* v___x_58_; lean_object* v___x_60_; 
v_v_54_ = lean_array_fget(v___y_47_, v___x_48_);
v___x_55_ = lean_box(0);
v_xs_x27_56_ = lean_array_fset(v___y_47_, v___x_48_, v___x_55_);
v___x_57_ = lean_nat_add(v_v_54_, v_hi_45_);
lean_dec(v_hi_45_);
lean_dec(v_v_54_);
v___x_58_ = lean_array_fset(v_xs_x27_56_, v___x_48_, v___x_57_);
lean_dec(v___x_48_);
if (v_isShared_31_ == 0)
{
lean_ctor_set(v___x_30_, 0, v___x_58_);
v___x_60_ = v___x_30_;
goto v_reusejp_59_;
}
else
{
lean_object* v_reuseFailAlloc_61_; 
v_reuseFailAlloc_61_ = lean_alloc_ctor(0, 2, 2);
lean_ctor_set(v_reuseFailAlloc_61_, 0, v___x_58_);
lean_ctor_set(v_reuseFailAlloc_61_, 1, v_neg_24_);
lean_ctor_set_uint8(v_reuseFailAlloc_61_, sizeof(void*)*2, v_special_25_);
v___x_60_ = v_reuseFailAlloc_61_;
goto v_reusejp_59_;
}
v_reusejp_59_:
{
lean_ctor_set_uint8(v___x_60_, sizeof(void*)*2 + 1, v_neg_22_);
return v___x_60_;
}
}
}
}
else
{
uint64_t v___x_71_; lean_object* v___x_72_; lean_object* v___x_73_; lean_object* v_l_74_; lean_object* v___x_75_; uint64_t v_r_76_; lean_object* v___x_77_; uint64_t v___x_78_; uint64_t v___x_79_; uint64_t v___x_80_; uint64_t v___x_81_; uint64_t v___x_82_; uint64_t v___x_83_; lean_object* v_hi_84_; lean_object* v___y_86_; lean_object* v___x_101_; uint8_t v___x_102_; 
v___x_71_ = lean_uint64_of_nat(v_m_20_);
v___x_72_ = lean_unsigned_to_nat(32u);
v___x_73_ = lean_unsigned_to_nat(5u);
v_l_74_ = lean_nat_shiftr(v_idx_21_, v___x_73_);
v___x_75_ = lean_nat_mod(v_idx_21_, v___x_72_);
v_r_76_ = lean_uint64_of_nat(v___x_75_);
lean_dec(v___x_75_);
v___x_77_ = lean_unsigned_to_nat(1u);
v___x_78_ = 1ULL;
v___x_79_ = 32ULL;
v___x_80_ = lean_uint64_sub(v___x_79_, v_r_76_);
v___x_81_ = lean_uint64_shift_left(v___x_78_, v___x_80_);
v___x_82_ = lean_uint64_mod(v___x_71_, v___x_81_);
v___x_83_ = lean_uint64_shift_right(v___x_71_, v___x_80_);
v_hi_84_ = lean_uint64_to_nat(v___x_83_);
v___x_101_ = lean_array_get_size(v_neg_24_);
v___x_102_ = lean_nat_dec_lt(v_l_74_, v___x_101_);
if (v___x_102_ == 0)
{
v___y_86_ = v_neg_24_;
goto v___jp_85_;
}
else
{
uint64_t v___x_103_; lean_object* v_lo_104_; lean_object* v_v_105_; lean_object* v___x_106_; lean_object* v_xs_x27_107_; lean_object* v___x_108_; lean_object* v___x_109_; 
v___x_103_ = lean_uint64_shift_left(v___x_82_, v_r_76_);
v_lo_104_ = lean_uint64_to_nat(v___x_103_);
v_v_105_ = lean_array_fget(v_neg_24_, v_l_74_);
v___x_106_ = lean_box(0);
v_xs_x27_107_ = lean_array_fset(v_neg_24_, v_l_74_, v___x_106_);
v___x_108_ = lean_nat_add(v_v_105_, v_lo_104_);
lean_dec(v_lo_104_);
lean_dec(v_v_105_);
v___x_109_ = lean_array_fset(v_xs_x27_107_, v_l_74_, v___x_108_);
v___y_86_ = v___x_109_;
goto v___jp_85_;
}
v___jp_85_:
{
lean_object* v___x_87_; lean_object* v___x_88_; uint8_t v___x_89_; 
v___x_87_ = lean_nat_add(v_l_74_, v___x_77_);
lean_dec(v_l_74_);
v___x_88_ = lean_array_get_size(v___y_86_);
v___x_89_ = lean_nat_dec_lt(v___x_87_, v___x_88_);
if (v___x_89_ == 0)
{
lean_object* v___x_91_; 
lean_dec(v___x_87_);
lean_dec(v_hi_84_);
if (v_isShared_31_ == 0)
{
lean_ctor_set(v___x_30_, 1, v___y_86_);
v___x_91_ = v___x_30_;
goto v_reusejp_90_;
}
else
{
lean_object* v_reuseFailAlloc_92_; 
v_reuseFailAlloc_92_ = lean_alloc_ctor(0, 2, 2);
lean_ctor_set(v_reuseFailAlloc_92_, 0, v_pos_23_);
lean_ctor_set(v_reuseFailAlloc_92_, 1, v___y_86_);
lean_ctor_set_uint8(v_reuseFailAlloc_92_, sizeof(void*)*2, v_special_25_);
v___x_91_ = v_reuseFailAlloc_92_;
goto v_reusejp_90_;
}
v_reusejp_90_:
{
lean_ctor_set_uint8(v___x_91_, sizeof(void*)*2 + 1, v___x_28_);
return v___x_91_;
}
}
else
{
lean_object* v_v_93_; lean_object* v___x_94_; lean_object* v_xs_x27_95_; lean_object* v___x_96_; lean_object* v___x_97_; lean_object* v___x_99_; 
v_v_93_ = lean_array_fget(v___y_86_, v___x_87_);
v___x_94_ = lean_box(0);
v_xs_x27_95_ = lean_array_fset(v___y_86_, v___x_87_, v___x_94_);
v___x_96_ = lean_nat_add(v_v_93_, v_hi_84_);
lean_dec(v_hi_84_);
lean_dec(v_v_93_);
v___x_97_ = lean_array_fset(v_xs_x27_95_, v___x_87_, v___x_96_);
lean_dec(v___x_87_);
if (v_isShared_31_ == 0)
{
lean_ctor_set(v___x_30_, 1, v___x_97_);
v___x_99_ = v___x_30_;
goto v_reusejp_98_;
}
else
{
lean_object* v_reuseFailAlloc_100_; 
v_reuseFailAlloc_100_ = lean_alloc_ctor(0, 2, 2);
lean_ctor_set(v_reuseFailAlloc_100_, 0, v_pos_23_);
lean_ctor_set(v_reuseFailAlloc_100_, 1, v___x_97_);
lean_ctor_set_uint8(v_reuseFailAlloc_100_, sizeof(void*)*2, v_special_25_);
v___x_99_ = v_reuseFailAlloc_100_;
goto v_reusejp_98_;
}
v_reusejp_98_:
{
lean_ctor_set_uint8(v___x_99_, sizeof(void*)*2 + 1, v___x_28_);
return v___x_99_;
}
}
}
}
}
}
else
{
if (v_negZero_26_ == 0)
{
return v_acc_19_;
}
else
{
lean_object* v___x_114_; uint8_t v_isShared_115_; uint8_t v_isSharedCheck_119_; 
lean_inc_ref(v_neg_24_);
lean_inc_ref(v_pos_23_);
v_isSharedCheck_119_ = !lean_is_exclusive(v_acc_19_);
if (v_isSharedCheck_119_ == 0)
{
lean_object* v_unused_120_; lean_object* v_unused_121_; 
v_unused_120_ = lean_ctor_get(v_acc_19_, 1);
lean_dec(v_unused_120_);
v_unused_121_ = lean_ctor_get(v_acc_19_, 0);
lean_dec(v_unused_121_);
v___x_114_ = v_acc_19_;
v_isShared_115_ = v_isSharedCheck_119_;
goto v_resetjp_113_;
}
else
{
lean_dec(v_acc_19_);
v___x_114_ = lean_box(0);
v_isShared_115_ = v_isSharedCheck_119_;
goto v_resetjp_113_;
}
v_resetjp_113_:
{
lean_object* v___x_117_; 
if (v_isShared_115_ == 0)
{
v___x_117_ = v___x_114_;
goto v_reusejp_116_;
}
else
{
lean_object* v_reuseFailAlloc_118_; 
v_reuseFailAlloc_118_ = lean_alloc_ctor(0, 2, 2);
lean_ctor_set(v_reuseFailAlloc_118_, 0, v_pos_23_);
lean_ctor_set(v_reuseFailAlloc_118_, 1, v_neg_24_);
lean_ctor_set_uint8(v_reuseFailAlloc_118_, sizeof(void*)*2, v_special_25_);
v___x_117_ = v_reuseFailAlloc_118_;
goto v_reusejp_116_;
}
v_reusejp_116_:
{
lean_ctor_set_uint8(v___x_117_, sizeof(void*)*2 + 1, v_neg_22_);
return v___x_117_;
}
}
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_Acc_add___boxed(lean_object* v_acc_122_, lean_object* v_m_123_, lean_object* v_idx_124_, lean_object* v_neg_125_){
_start:
{
uint8_t v_neg_boxed_126_; lean_object* v_res_127_; 
v_neg_boxed_126_ = lean_unbox(v_neg_125_);
v_res_127_ = lp_competition_Submission_Acc_add(v_acc_122_, v_m_123_, v_idx_124_, v_neg_boxed_126_);
lean_dec(v_idx_124_);
lean_dec(v_m_123_);
return v_res_127_;
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_Acc_markSpecial(lean_object* v_acc_128_){
_start:
{
lean_object* v_pos_129_; lean_object* v_neg_130_; uint8_t v_negZero_131_; lean_object* v___x_133_; uint8_t v_isShared_134_; uint8_t v_isSharedCheck_139_; 
v_pos_129_ = lean_ctor_get(v_acc_128_, 0);
v_neg_130_ = lean_ctor_get(v_acc_128_, 1);
v_negZero_131_ = lean_ctor_get_uint8(v_acc_128_, sizeof(void*)*2 + 1);
v_isSharedCheck_139_ = !lean_is_exclusive(v_acc_128_);
if (v_isSharedCheck_139_ == 0)
{
v___x_133_ = v_acc_128_;
v_isShared_134_ = v_isSharedCheck_139_;
goto v_resetjp_132_;
}
else
{
lean_inc(v_neg_130_);
lean_inc(v_pos_129_);
lean_dec(v_acc_128_);
v___x_133_ = lean_box(0);
v_isShared_134_ = v_isSharedCheck_139_;
goto v_resetjp_132_;
}
v_resetjp_132_:
{
uint8_t v___x_135_; lean_object* v___x_137_; 
v___x_135_ = 1;
if (v_isShared_134_ == 0)
{
v___x_137_ = v___x_133_;
goto v_reusejp_136_;
}
else
{
lean_object* v_reuseFailAlloc_138_; 
v_reuseFailAlloc_138_ = lean_alloc_ctor(0, 2, 2);
lean_ctor_set(v_reuseFailAlloc_138_, 0, v_pos_129_);
lean_ctor_set(v_reuseFailAlloc_138_, 1, v_neg_130_);
lean_ctor_set_uint8(v_reuseFailAlloc_138_, sizeof(void*)*2 + 1, v_negZero_131_);
v___x_137_ = v_reuseFailAlloc_138_;
goto v_reusejp_136_;
}
v_reusejp_136_:
{
lean_ctor_set_uint8(v___x_137_, sizeof(void*)*2, v___x_135_);
return v___x_137_;
}
}
}
}
LEAN_EXPORT lean_object* lp_competition___private_Submission_0__Submission_Acc_add_match__1_splitter___redArg(lean_object* v_acc_140_, lean_object* v_h__1_141_){
_start:
{
lean_object* v_pos_142_; lean_object* v_neg_143_; uint8_t v_special_144_; uint8_t v_negZero_145_; lean_object* v___x_146_; lean_object* v___x_147_; lean_object* v___x_148_; 
v_pos_142_ = lean_ctor_get(v_acc_140_, 0);
lean_inc_ref(v_pos_142_);
v_neg_143_ = lean_ctor_get(v_acc_140_, 1);
lean_inc_ref(v_neg_143_);
v_special_144_ = lean_ctor_get_uint8(v_acc_140_, sizeof(void*)*2);
v_negZero_145_ = lean_ctor_get_uint8(v_acc_140_, sizeof(void*)*2 + 1);
lean_dec_ref(v_acc_140_);
v___x_146_ = lean_box(v_special_144_);
v___x_147_ = lean_box(v_negZero_145_);
v___x_148_ = lean_apply_4(v_h__1_141_, v_pos_142_, v_neg_143_, v___x_146_, v___x_147_);
return v___x_148_;
}
}
LEAN_EXPORT lean_object* lp_competition___private_Submission_0__Submission_Acc_add_match__1_splitter(lean_object* v_motive_149_, lean_object* v_acc_150_, lean_object* v_h__1_151_){
_start:
{
lean_object* v_pos_152_; lean_object* v_neg_153_; uint8_t v_special_154_; uint8_t v_negZero_155_; lean_object* v___x_156_; lean_object* v___x_157_; lean_object* v___x_158_; 
v_pos_152_ = lean_ctor_get(v_acc_150_, 0);
lean_inc_ref(v_pos_152_);
v_neg_153_ = lean_ctor_get(v_acc_150_, 1);
lean_inc_ref(v_neg_153_);
v_special_154_ = lean_ctor_get_uint8(v_acc_150_, sizeof(void*)*2);
v_negZero_155_ = lean_ctor_get_uint8(v_acc_150_, sizeof(void*)*2 + 1);
lean_dec_ref(v_acc_150_);
v___x_156_ = lean_box(v_special_154_);
v___x_157_ = lean_box(v_negZero_155_);
v___x_158_ = lean_apply_4(v_h__1_151_, v_pos_152_, v_neg_153_, v___x_156_, v___x_157_);
return v___x_158_;
}
}
static lean_object* _init_lp_competition___private_Submission_0__FloatLib_Floats_Formats_BinaryInterchange_Model_roundDyadicGeneral_match__1_splitter___redArg___closed__0(void){
_start:
{
lean_object* v_natZero_159_; lean_object* v_intZero_160_; 
v_natZero_159_ = lean_unsigned_to_nat(0u);
v_intZero_160_ = lean_nat_to_int(v_natZero_159_);
return v_intZero_160_;
}
}
LEAN_EXPORT lean_object* lp_competition___private_Submission_0__FloatLib_Floats_Formats_BinaryInterchange_Model_roundDyadicGeneral_match__1_splitter___redArg(lean_object* v_x_161_, lean_object* v_h__1_162_, lean_object* v_h__2_163_){
_start:
{
lean_object* v_intZero_164_; uint8_t v_isNeg_165_; 
v_intZero_164_ = lean_obj_once(&lp_competition___private_Submission_0__FloatLib_Floats_Formats_BinaryInterchange_Model_roundDyadicGeneral_match__1_splitter___redArg___closed__0, &lp_competition___private_Submission_0__FloatLib_Floats_Formats_BinaryInterchange_Model_roundDyadicGeneral_match__1_splitter___redArg___closed__0_once, _init_lp_competition___private_Submission_0__FloatLib_Floats_Formats_BinaryInterchange_Model_roundDyadicGeneral_match__1_splitter___redArg___closed__0);
v_isNeg_165_ = lean_int_dec_lt(v_x_161_, v_intZero_164_);
if (v_isNeg_165_ == 0)
{
lean_object* v_a_166_; lean_object* v___x_167_; 
lean_dec(v_h__2_163_);
v_a_166_ = lean_nat_abs(v_x_161_);
v___x_167_ = lean_apply_1(v_h__1_162_, v_a_166_);
return v___x_167_;
}
else
{
lean_object* v_abs_168_; lean_object* v_one_169_; lean_object* v_a_170_; lean_object* v___x_171_; 
lean_dec(v_h__1_162_);
v_abs_168_ = lean_nat_abs(v_x_161_);
v_one_169_ = lean_unsigned_to_nat(1u);
v_a_170_ = lean_nat_sub(v_abs_168_, v_one_169_);
lean_dec(v_abs_168_);
v___x_171_ = lean_apply_1(v_h__2_163_, v_a_170_);
return v___x_171_;
}
}
}
LEAN_EXPORT lean_object* lp_competition___private_Submission_0__FloatLib_Floats_Formats_BinaryInterchange_Model_roundDyadicGeneral_match__1_splitter___redArg___boxed(lean_object* v_x_172_, lean_object* v_h__1_173_, lean_object* v_h__2_174_){
_start:
{
lean_object* v_res_175_; 
v_res_175_ = lp_competition___private_Submission_0__FloatLib_Floats_Formats_BinaryInterchange_Model_roundDyadicGeneral_match__1_splitter___redArg(v_x_172_, v_h__1_173_, v_h__2_174_);
lean_dec(v_x_172_);
return v_res_175_;
}
}
LEAN_EXPORT lean_object* lp_competition___private_Submission_0__FloatLib_Floats_Formats_BinaryInterchange_Model_roundDyadicGeneral_match__1_splitter(lean_object* v_motive_176_, lean_object* v_x_177_, lean_object* v_h__1_178_, lean_object* v_h__2_179_){
_start:
{
lean_object* v_intZero_180_; uint8_t v_isNeg_181_; 
v_intZero_180_ = lean_obj_once(&lp_competition___private_Submission_0__FloatLib_Floats_Formats_BinaryInterchange_Model_roundDyadicGeneral_match__1_splitter___redArg___closed__0, &lp_competition___private_Submission_0__FloatLib_Floats_Formats_BinaryInterchange_Model_roundDyadicGeneral_match__1_splitter___redArg___closed__0_once, _init_lp_competition___private_Submission_0__FloatLib_Floats_Formats_BinaryInterchange_Model_roundDyadicGeneral_match__1_splitter___redArg___closed__0);
v_isNeg_181_ = lean_int_dec_lt(v_x_177_, v_intZero_180_);
if (v_isNeg_181_ == 0)
{
lean_object* v_a_182_; lean_object* v___x_183_; 
lean_dec(v_h__2_179_);
v_a_182_ = lean_nat_abs(v_x_177_);
v___x_183_ = lean_apply_1(v_h__1_178_, v_a_182_);
return v___x_183_;
}
else
{
lean_object* v_abs_184_; lean_object* v_one_185_; lean_object* v_a_186_; lean_object* v___x_187_; 
lean_dec(v_h__1_178_);
v_abs_184_ = lean_nat_abs(v_x_177_);
v_one_185_ = lean_unsigned_to_nat(1u);
v_a_186_ = lean_nat_sub(v_abs_184_, v_one_185_);
lean_dec(v_abs_184_);
v___x_187_ = lean_apply_1(v_h__2_179_, v_a_186_);
return v___x_187_;
}
}
}
LEAN_EXPORT lean_object* lp_competition___private_Submission_0__FloatLib_Floats_Formats_BinaryInterchange_Model_roundDyadicGeneral_match__1_splitter___boxed(lean_object* v_motive_188_, lean_object* v_x_189_, lean_object* v_h__1_190_, lean_object* v_h__2_191_){
_start:
{
lean_object* v_res_192_; 
v_res_192_ = lp_competition___private_Submission_0__FloatLib_Floats_Formats_BinaryInterchange_Model_roundDyadicGeneral_match__1_splitter(v_motive_188_, v_x_189_, v_h__1_190_, v_h__2_191_);
lean_dec(v_x_189_);
return v_res_192_;
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_winVal(lean_object* v_a_193_, lean_object* v_i_194_, lean_object* v_x_195_){
_start:
{
lean_object* v_zero_196_; uint8_t v_isZero_197_; 
v_zero_196_ = lean_unsigned_to_nat(0u);
v_isZero_197_ = lean_nat_dec_eq(v_x_195_, v_zero_196_);
if (v_isZero_197_ == 1)
{
return v_zero_196_;
}
else
{
lean_object* v_one_198_; lean_object* v_n_199_; lean_object* v___x_200_; lean_object* v___x_201_; lean_object* v___x_202_; lean_object* v___x_203_; lean_object* v___x_204_; lean_object* v___x_205_; 
v_one_198_ = lean_unsigned_to_nat(1u);
v_n_199_ = lean_nat_sub(v_x_195_, v_one_198_);
v___x_200_ = lean_array_get_borrowed(v_zero_196_, v_a_193_, v_i_194_);
v___x_201_ = lean_cstr_to_nat("4294967296");
v___x_202_ = lean_nat_add(v_i_194_, v_one_198_);
v___x_203_ = lp_competition_Submission_winVal(v_a_193_, v___x_202_, v_n_199_);
lean_dec(v_n_199_);
lean_dec(v___x_202_);
v___x_204_ = lean_nat_mul(v___x_201_, v___x_203_);
lean_dec(v___x_203_);
v___x_205_ = lean_nat_add(v___x_200_, v___x_204_);
lean_dec(v___x_204_);
return v___x_205_;
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_winVal___boxed(lean_object* v_a_206_, lean_object* v_i_207_, lean_object* v_x_208_){
_start:
{
lean_object* v_res_209_; 
v_res_209_ = lp_competition_Submission_winVal(v_a_206_, v_i_207_, v_x_208_);
lean_dec(v_x_208_);
lean_dec(v_i_207_);
lean_dec_ref(v_a_206_);
return v_res_209_;
}
}
LEAN_EXPORT lean_object* lp_competition___private_Submission_0__Submission_winVal_match__1_splitter___redArg(lean_object* v_x_210_, lean_object* v_h__1_211_, lean_object* v_h__2_212_){
_start:
{
lean_object* v_zero_213_; uint8_t v_isZero_214_; 
v_zero_213_ = lean_unsigned_to_nat(0u);
v_isZero_214_ = lean_nat_dec_eq(v_x_210_, v_zero_213_);
if (v_isZero_214_ == 1)
{
lean_object* v___x_215_; lean_object* v___x_216_; 
lean_dec(v_h__2_212_);
v___x_215_ = lean_box(0);
v___x_216_ = lean_apply_1(v_h__1_211_, v___x_215_);
return v___x_216_;
}
else
{
lean_object* v_one_217_; lean_object* v_n_218_; lean_object* v___x_219_; 
lean_dec(v_h__1_211_);
v_one_217_ = lean_unsigned_to_nat(1u);
v_n_218_ = lean_nat_sub(v_x_210_, v_one_217_);
v___x_219_ = lean_apply_1(v_h__2_212_, v_n_218_);
return v___x_219_;
}
}
}
LEAN_EXPORT lean_object* lp_competition___private_Submission_0__Submission_winVal_match__1_splitter___redArg___boxed(lean_object* v_x_220_, lean_object* v_h__1_221_, lean_object* v_h__2_222_){
_start:
{
lean_object* v_res_223_; 
v_res_223_ = lp_competition___private_Submission_0__Submission_winVal_match__1_splitter___redArg(v_x_220_, v_h__1_221_, v_h__2_222_);
lean_dec(v_x_220_);
return v_res_223_;
}
}
LEAN_EXPORT lean_object* lp_competition___private_Submission_0__Submission_winVal_match__1_splitter(lean_object* v_motive_224_, lean_object* v_x_225_, lean_object* v_h__1_226_, lean_object* v_h__2_227_){
_start:
{
lean_object* v_zero_228_; uint8_t v_isZero_229_; 
v_zero_228_ = lean_unsigned_to_nat(0u);
v_isZero_229_ = lean_nat_dec_eq(v_x_225_, v_zero_228_);
if (v_isZero_229_ == 1)
{
lean_object* v___x_230_; lean_object* v___x_231_; 
lean_dec(v_h__2_227_);
v___x_230_ = lean_box(0);
v___x_231_ = lean_apply_1(v_h__1_226_, v___x_230_);
return v___x_231_;
}
else
{
lean_object* v_one_232_; lean_object* v_n_233_; lean_object* v___x_234_; 
lean_dec(v_h__1_226_);
v_one_232_ = lean_unsigned_to_nat(1u);
v_n_233_ = lean_nat_sub(v_x_225_, v_one_232_);
v___x_234_ = lean_apply_1(v_h__2_227_, v_n_233_);
return v___x_234_;
}
}
}
LEAN_EXPORT lean_object* lp_competition___private_Submission_0__Submission_winVal_match__1_splitter___boxed(lean_object* v_motive_235_, lean_object* v_x_236_, lean_object* v_h__1_237_, lean_object* v_h__2_238_){
_start:
{
lean_object* v_res_239_; 
v_res_239_ = lp_competition___private_Submission_0__Submission_winVal_match__1_splitter(v_motive_235_, v_x_236_, v_h__1_237_, v_h__2_238_);
lean_dec(v_x_236_);
return v_res_239_;
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_diffGo(lean_object* v_a_240_, lean_object* v_b_241_, lean_object* v_i_242_, lean_object* v_ca_243_, lean_object* v_cb_244_, lean_object* v_br_245_, lean_object* v_out_246_, lean_object* v_x_247_){
_start:
{
lean_object* v_zero_248_; uint8_t v_isZero_249_; 
v_zero_248_ = lean_unsigned_to_nat(0u);
v_isZero_249_ = lean_nat_dec_eq(v_x_247_, v_zero_248_);
if (v_isZero_249_ == 1)
{
lean_object* v___x_250_; lean_object* v___x_251_; lean_object* v___x_252_; 
lean_dec(v_x_247_);
lean_dec(v_i_242_);
v___x_250_ = lean_alloc_ctor(0, 2, 0);
lean_ctor_set(v___x_250_, 0, v_cb_244_);
lean_ctor_set(v___x_250_, 1, v_br_245_);
v___x_251_ = lean_alloc_ctor(0, 2, 0);
lean_ctor_set(v___x_251_, 0, v_ca_243_);
lean_ctor_set(v___x_251_, 1, v___x_250_);
v___x_252_ = lean_alloc_ctor(0, 2, 0);
lean_ctor_set(v___x_252_, 0, v_out_246_);
lean_ctor_set(v___x_252_, 1, v___x_251_);
return v___x_252_;
}
else
{
lean_object* v_one_253_; lean_object* v_n_254_; lean_object* v___x_255_; lean_object* v_ta_256_; lean_object* v___x_257_; lean_object* v_tb_258_; lean_object* v___x_259_; lean_object* v___x_260_; lean_object* v___x_261_; lean_object* v___x_262_; lean_object* v___x_263_; lean_object* v_t_264_; lean_object* v___x_265_; lean_object* v___x_266_; lean_object* v___x_267_; lean_object* v___x_268_; lean_object* v___x_269_; lean_object* v___x_270_; lean_object* v___x_271_; lean_object* v___x_272_; 
v_one_253_ = lean_unsigned_to_nat(1u);
v_n_254_ = lean_nat_sub(v_x_247_, v_one_253_);
lean_dec(v_x_247_);
v___x_255_ = lean_array_get_borrowed(v_zero_248_, v_a_240_, v_i_242_);
v_ta_256_ = lean_nat_add(v___x_255_, v_ca_243_);
lean_dec(v_ca_243_);
v___x_257_ = lean_array_get_borrowed(v_zero_248_, v_b_241_, v_i_242_);
v_tb_258_ = lean_nat_add(v___x_257_, v_cb_244_);
lean_dec(v_cb_244_);
v___x_259_ = lean_cstr_to_nat("4294967296");
v___x_260_ = lean_nat_mod(v_ta_256_, v___x_259_);
v___x_261_ = lean_nat_add(v___x_260_, v___x_259_);
lean_dec(v___x_260_);
v___x_262_ = lean_nat_mod(v_tb_258_, v___x_259_);
v___x_263_ = lean_nat_sub(v___x_261_, v___x_262_);
lean_dec(v___x_262_);
lean_dec(v___x_261_);
v_t_264_ = lean_nat_sub(v___x_263_, v_br_245_);
lean_dec(v_br_245_);
lean_dec(v___x_263_);
v___x_265_ = lean_nat_add(v_i_242_, v_one_253_);
lean_dec(v_i_242_);
v___x_266_ = lean_unsigned_to_nat(32u);
v___x_267_ = lean_nat_shiftr(v_ta_256_, v___x_266_);
lean_dec(v_ta_256_);
v___x_268_ = lean_nat_shiftr(v_tb_258_, v___x_266_);
lean_dec(v_tb_258_);
v___x_269_ = lean_nat_shiftr(v_t_264_, v___x_266_);
v___x_270_ = lean_nat_sub(v_one_253_, v___x_269_);
lean_dec(v___x_269_);
v___x_271_ = lean_nat_mod(v_t_264_, v___x_259_);
lean_dec(v_t_264_);
v___x_272_ = lean_array_push(v_out_246_, v___x_271_);
v_i_242_ = v___x_265_;
v_ca_243_ = v___x_267_;
v_cb_244_ = v___x_268_;
v_br_245_ = v___x_270_;
v_out_246_ = v___x_272_;
v_x_247_ = v_n_254_;
goto _start;
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_diffGo___boxed(lean_object* v_a_274_, lean_object* v_b_275_, lean_object* v_i_276_, lean_object* v_ca_277_, lean_object* v_cb_278_, lean_object* v_br_279_, lean_object* v_out_280_, lean_object* v_x_281_){
_start:
{
lean_object* v_res_282_; 
v_res_282_ = lp_competition_Submission_diffGo(v_a_274_, v_b_275_, v_i_276_, v_ca_277_, v_cb_278_, v_br_279_, v_out_280_, v_x_281_);
lean_dec_ref(v_b_275_);
lean_dec_ref(v_a_274_);
return v_res_282_;
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_topGo(lean_object* v_r_283_, lean_object* v_x_284_){
_start:
{
lean_object* v_zero_285_; uint8_t v_isZero_286_; 
v_zero_285_ = lean_unsigned_to_nat(0u);
v_isZero_286_ = lean_nat_dec_eq(v_x_284_, v_zero_285_);
if (v_isZero_286_ == 1)
{
lean_object* v___x_287_; 
lean_dec(v_x_284_);
v___x_287_ = lean_box(0);
return v___x_287_;
}
else
{
lean_object* v_one_288_; lean_object* v_n_289_; lean_object* v___x_290_; uint8_t v___x_291_; 
v_one_288_ = lean_unsigned_to_nat(1u);
v_n_289_ = lean_nat_sub(v_x_284_, v_one_288_);
lean_dec(v_x_284_);
v___x_290_ = lean_array_get_borrowed(v_zero_285_, v_r_283_, v_n_289_);
v___x_291_ = lean_nat_dec_eq(v___x_290_, v_zero_285_);
if (v___x_291_ == 0)
{
lean_object* v___x_292_; 
v___x_292_ = lean_alloc_ctor(1, 1, 0);
lean_ctor_set(v___x_292_, 0, v_n_289_);
return v___x_292_;
}
else
{
v_x_284_ = v_n_289_;
goto _start;
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_topGo___boxed(lean_object* v_r_294_, lean_object* v_x_295_){
_start:
{
lean_object* v_res_296_; 
v_res_296_ = lp_competition_Submission_topGo(v_r_294_, v_x_295_);
lean_dec_ref(v_r_294_);
return v_res_296_;
}
}
LEAN_EXPORT uint8_t lp_competition_Submission_anyGo(lean_object* v_r_297_, lean_object* v_x_298_){
_start:
{
lean_object* v_zero_299_; uint8_t v_isZero_300_; 
v_zero_299_ = lean_unsigned_to_nat(0u);
v_isZero_300_ = lean_nat_dec_eq(v_x_298_, v_zero_299_);
if (v_isZero_300_ == 1)
{
uint8_t v___x_301_; 
lean_dec(v_x_298_);
v___x_301_ = 0;
return v___x_301_;
}
else
{
lean_object* v_one_302_; lean_object* v_n_303_; lean_object* v___x_304_; uint8_t v___x_305_; 
v_one_302_ = lean_unsigned_to_nat(1u);
v_n_303_ = lean_nat_sub(v_x_298_, v_one_302_);
lean_dec(v_x_298_);
v___x_304_ = lean_array_get_borrowed(v_zero_299_, v_r_297_, v_n_303_);
v___x_305_ = lean_nat_dec_eq(v___x_304_, v_zero_299_);
if (v___x_305_ == 0)
{
uint8_t v___x_306_; 
lean_dec(v_n_303_);
v___x_306_ = 1;
return v___x_306_;
}
else
{
v_x_298_ = v_n_303_;
goto _start;
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_anyGo___boxed(lean_object* v_r_308_, lean_object* v_x_309_){
_start:
{
uint8_t v_res_310_; lean_object* v_r_311_; 
v_res_310_ = lp_competition_Submission_anyGo(v_r_308_, v_x_309_);
lean_dec_ref(v_r_308_);
v_r_311_ = lean_box(v_res_310_);
return v_r_311_;
}
}
static lean_object* _init_lp_competition_Submission_finishDigits___closed__0(void){
_start:
{
lean_object* v___x_312_; lean_object* v___x_313_; lean_object* v___x_314_; 
v___x_312_ = lean_unsigned_to_nat(2147483648u);
v___x_313_ = lean_unsigned_to_nat(32u);
v___x_314_ = l_BitVec_ofNat(v___x_313_, v___x_312_);
return v___x_314_;
}
}
static uint32_t _init_lp_competition_Submission_finishDigits___closed__1(void){
_start:
{
lean_object* v___x_315_; uint32_t v___x_316_; 
v___x_315_ = lean_obj_once(&lp_competition_Submission_finishDigits___closed__0, &lp_competition_Submission_finishDigits___closed__0_once, _init_lp_competition_Submission_finishDigits___closed__0);
v___x_316_ = lean_uint32_of_nat(v___x_315_);
return v___x_316_;
}
}
static lean_object* _init_lp_competition_Submission_finishDigits___closed__2(void){
_start:
{
lean_object* v___x_317_; lean_object* v___x_318_; lean_object* v___x_319_; 
v___x_317_ = lean_unsigned_to_nat(2139095040u);
v___x_318_ = lean_unsigned_to_nat(32u);
v___x_319_ = l_BitVec_ofNat(v___x_318_, v___x_317_);
return v___x_319_;
}
}
static uint32_t _init_lp_competition_Submission_finishDigits___closed__3(void){
_start:
{
lean_object* v___x_320_; uint32_t v___x_321_; 
v___x_320_ = lean_obj_once(&lp_competition_Submission_finishDigits___closed__2, &lp_competition_Submission_finishDigits___closed__2_once, _init_lp_competition_Submission_finishDigits___closed__2);
v___x_321_ = lean_uint32_of_nat(v___x_320_);
return v___x_321_;
}
}
static lean_object* _init_lp_competition_Submission_finishDigits___closed__4(void){
_start:
{
lean_object* v___x_322_; lean_object* v___x_323_; lean_object* v___x_324_; 
v___x_322_ = lean_obj_once(&lp_competition_Submission_finishDigits___closed__2, &lp_competition_Submission_finishDigits___closed__2_once, _init_lp_competition_Submission_finishDigits___closed__2);
v___x_323_ = lean_obj_once(&lp_competition_Submission_finishDigits___closed__0, &lp_competition_Submission_finishDigits___closed__0_once, _init_lp_competition_Submission_finishDigits___closed__0);
v___x_324_ = lean_nat_lor(v___x_323_, v___x_322_);
return v___x_324_;
}
}
static uint32_t _init_lp_competition_Submission_finishDigits___closed__5(void){
_start:
{
lean_object* v___x_325_; uint32_t v___x_326_; 
v___x_325_ = lean_obj_once(&lp_competition_Submission_finishDigits___closed__4, &lp_competition_Submission_finishDigits___closed__4_once, _init_lp_competition_Submission_finishDigits___closed__4);
v___x_326_ = lean_uint32_of_nat(v___x_325_);
return v___x_326_;
}
}
static lean_object* _init_lp_competition_Submission_finishDigits___closed__6(void){
_start:
{
lean_object* v___x_327_; lean_object* v___x_328_; 
v___x_327_ = lean_unsigned_to_nat(1u);
v___x_328_ = lean_nat_to_int(v___x_327_);
return v___x_328_;
}
}
static lean_object* _init_lp_competition_Submission_finishDigits___closed__7(void){
_start:
{
lean_object* v___x_329_; lean_object* v___x_330_; 
v___x_329_ = lean_unsigned_to_nat(127u);
v___x_330_ = lean_nat_to_int(v___x_329_);
return v___x_330_;
}
}
static lean_object* _init_lp_competition_Submission_finishDigits___closed__8(void){
_start:
{
lean_object* v___x_331_; lean_object* v___x_332_; lean_object* v___x_333_; 
v___x_331_ = lean_obj_once(&lp_competition_Submission_finishDigits___closed__7, &lp_competition_Submission_finishDigits___closed__7_once, _init_lp_competition_Submission_finishDigits___closed__7);
v___x_332_ = lean_obj_once(&lp_competition_Submission_finishDigits___closed__6, &lp_competition_Submission_finishDigits___closed__6_once, _init_lp_competition_Submission_finishDigits___closed__6);
v___x_333_ = lean_int_sub(v___x_332_, v___x_331_);
return v___x_333_;
}
}
static lean_object* _init_lp_competition_Submission_finishDigits___closed__9(void){
_start:
{
lean_object* v___x_334_; lean_object* v___x_335_; 
v___x_334_ = lean_unsigned_to_nat(149u);
v___x_335_ = lean_nat_to_int(v___x_334_);
return v___x_335_;
}
}
static lean_object* _init_lp_competition_Submission_finishDigits___closed__10(void){
_start:
{
lean_object* v___x_336_; lean_object* v___x_337_; lean_object* v___x_338_; 
v___x_336_ = lean_unsigned_to_nat(0u);
v___x_337_ = lean_unsigned_to_nat(32u);
v___x_338_ = l_BitVec_ofNat(v___x_337_, v___x_336_);
return v___x_338_;
}
}
static uint32_t _init_lp_competition_Submission_finishDigits___closed__11(void){
_start:
{
lean_object* v___x_339_; uint32_t v___x_340_; 
v___x_339_ = lean_obj_once(&lp_competition_Submission_finishDigits___closed__10, &lp_competition_Submission_finishDigits___closed__10_once, _init_lp_competition_Submission_finishDigits___closed__10);
v___x_340_ = lean_uint32_of_nat(v___x_339_);
return v___x_340_;
}
}
static uint8_t _init_lp_competition_Submission_finishDigits___closed__12(void){
_start:
{
lean_object* v___x_341_; uint8_t v___x_342_; 
v___x_341_ = lean_obj_once(&lp_competition___private_Submission_0__FloatLib_Floats_Formats_BinaryInterchange_Model_roundDyadicGeneral_match__1_splitter___redArg___closed__0, &lp_competition___private_Submission_0__FloatLib_Floats_Formats_BinaryInterchange_Model_roundDyadicGeneral_match__1_splitter___redArg___closed__0_once, _init_lp_competition___private_Submission_0__FloatLib_Floats_Formats_BinaryInterchange_Model_roundDyadicGeneral_match__1_splitter___redArg___closed__0);
v___x_342_ = lean_int_dec_eq(v___x_341_, v___x_341_);
return v___x_342_;
}
}
LEAN_EXPORT uint32_t lp_competition_Submission_finishDigits(uint8_t v_neg_343_, lean_object* v_r_344_, lean_object* v_e_345_, uint8_t v_negZero_346_){
_start:
{
lean_object* v___y_348_; lean_object* v___y_349_; lean_object* v___y_353_; lean_object* v___y_354_; lean_object* v___y_360_; lean_object* v___y_361_; lean_object* v___y_367_; lean_object* v___y_368_; lean_object* v___y_372_; lean_object* v___y_373_; lean_object* v___y_374_; lean_object* v___y_388_; lean_object* v___y_389_; lean_object* v___y_390_; lean_object* v___y_391_; uint8_t v___y_401_; lean_object* v___y_402_; lean_object* v___y_403_; lean_object* v___y_404_; lean_object* v___y_405_; lean_object* v___y_406_; uint8_t v___y_413_; uint8_t v___y_414_; lean_object* v___y_415_; lean_object* v___y_416_; lean_object* v___y_417_; lean_object* v___y_418_; lean_object* v___y_419_; lean_object* v___y_425_; uint8_t v___y_426_; lean_object* v___y_427_; lean_object* v___y_428_; lean_object* v___y_429_; lean_object* v___y_430_; lean_object* v___y_431_; lean_object* v___y_436_; lean_object* v___y_501_; lean_object* v___y_502_; lean_object* v___y_508_; lean_object* v___y_509_; lean_object* v___y_513_; lean_object* v___y_514_; lean_object* v___y_515_; lean_object* v___y_527_; lean_object* v___y_528_; lean_object* v___y_529_; lean_object* v___y_530_; lean_object* v___y_540_; lean_object* v___y_541_; lean_object* v___y_542_; lean_object* v___y_543_; lean_object* v___y_544_; uint8_t v___y_551_; lean_object* v___y_552_; lean_object* v___y_553_; lean_object* v___y_554_; lean_object* v___y_555_; lean_object* v___y_556_; lean_object* v___y_557_; lean_object* v___y_570_; lean_object* v___y_571_; lean_object* v___y_572_; lean_object* v___y_573_; lean_object* v___y_574_; lean_object* v___y_575_; lean_object* v___y_576_; lean_object* v___x_580_; lean_object* v___x_581_; 
v___x_580_ = lean_array_get_size(v_r_344_);
v___x_581_ = lp_competition_Submission_topGo(v_r_344_, v___x_580_);
if (lean_obj_tag(v___x_581_) == 0)
{
lean_object* v___x_582_; lean_object* v___x_583_; uint8_t v___x_584_; 
v___x_582_ = lean_unsigned_to_nat(0u);
v___x_583_ = lean_obj_once(&lp_competition___private_Submission_0__FloatLib_Floats_Formats_BinaryInterchange_Model_roundDyadicGeneral_match__1_splitter___redArg___closed__0, &lp_competition___private_Submission_0__FloatLib_Floats_Formats_BinaryInterchange_Model_roundDyadicGeneral_match__1_splitter___redArg___closed__0_once, _init_lp_competition___private_Submission_0__FloatLib_Floats_Formats_BinaryInterchange_Model_roundDyadicGeneral_match__1_splitter___redArg___closed__0);
v___x_584_ = lean_uint8_once(&lp_competition_Submission_finishDigits___closed__12, &lp_competition_Submission_finishDigits___closed__12_once, _init_lp_competition_Submission_finishDigits___closed__12);
if (v___x_584_ == 0)
{
lean_object* v___x_585_; lean_object* v___y_587_; uint8_t v_negative_598_; lean_object* v_significand_599_; lean_object* v_exponent_600_; uint8_t v___x_601_; 
v___x_585_ = lp_competition_ExactRuntime_ofIntDyadic(v___x_583_, v_e_345_);
v_negative_598_ = lean_ctor_get_uint8(v___x_585_, sizeof(void*)*2);
v_significand_599_ = lean_ctor_get(v___x_585_, 0);
lean_inc(v_significand_599_);
v_exponent_600_ = lean_ctor_get(v___x_585_, 1);
lean_inc(v_exponent_600_);
v___x_601_ = lean_nat_dec_eq(v_significand_599_, v___x_582_);
if (v___x_601_ == 0)
{
lean_object* v_leading_602_; lean_object* v___x_603_; lean_object* v_totalExponent_604_; lean_object* v___x_605_; lean_object* v___x_606_; lean_object* v___x_607_; lean_object* v___x_608_; uint8_t v___x_609_; 
v_leading_602_ = lean_nat_log2(v_significand_599_);
lean_inc(v_leading_602_);
v___x_603_ = lean_nat_to_int(v_leading_602_);
v_totalExponent_604_ = lean_int_add(v___x_603_, v_exponent_600_);
lean_dec(v___x_603_);
v___x_605_ = lean_unsigned_to_nat(1u);
v___x_606_ = lean_obj_once(&lp_competition_Submission_finishDigits___closed__6, &lp_competition_Submission_finishDigits___closed__6_once, _init_lp_competition_Submission_finishDigits___closed__6);
v___x_607_ = lean_obj_once(&lp_competition_Submission_finishDigits___closed__7, &lp_competition_Submission_finishDigits___closed__7_once, _init_lp_competition_Submission_finishDigits___closed__7);
v___x_608_ = lean_obj_once(&lp_competition_Submission_finishDigits___closed__8, &lp_competition_Submission_finishDigits___closed__8_once, _init_lp_competition_Submission_finishDigits___closed__8);
v___x_609_ = lean_int_dec_lt(v_totalExponent_604_, v___x_608_);
if (v___x_609_ == 0)
{
lean_object* v___x_610_; lean_object* v___y_612_; lean_object* v___y_613_; lean_object* v___y_614_; lean_object* v___y_624_; lean_object* v___y_625_; lean_object* v___y_632_; uint8_t v___y_633_; lean_object* v___y_634_; lean_object* v___y_640_; uint8_t v___x_644_; 
lean_dec(v_exponent_600_);
lean_dec_ref(v___x_585_);
v___x_610_ = lean_unsigned_to_nat(23u);
v___x_644_ = lean_nat_dec_le(v___x_610_, v_leading_602_);
if (v___x_644_ == 0)
{
lean_object* v___x_645_; lean_object* v___x_646_; 
v___x_645_ = lean_nat_sub(v___x_610_, v_leading_602_);
lean_dec(v_leading_602_);
v___x_646_ = lean_nat_shiftl(v_significand_599_, v___x_645_);
lean_dec(v___x_645_);
lean_dec(v_significand_599_);
v___y_640_ = v___x_646_;
goto v___jp_639_;
}
else
{
lean_object* v___x_647_; uint8_t v___x_648_; 
v___x_647_ = lean_nat_sub(v_leading_602_, v___x_610_);
v___x_648_ = lean_nat_dec_eq(v___x_647_, v___x_582_);
if (v___x_648_ == 0)
{
lean_object* v___x_649_; uint8_t v___x_650_; 
v___x_649_ = lean_nat_add(v_leading_602_, v___x_605_);
lean_dec(v_leading_602_);
v___x_650_ = lean_nat_dec_lt(v___x_649_, v___x_647_);
lean_dec(v___x_649_);
if (v___x_650_ == 0)
{
lean_object* v_quotient_651_; lean_object* v___x_652_; lean_object* v_remainder_653_; lean_object* v___x_654_; lean_object* v_half_655_; uint8_t v___x_656_; 
v_quotient_651_ = lean_nat_shiftr(v_significand_599_, v___x_647_);
v___x_652_ = lean_nat_shiftl(v_quotient_651_, v___x_647_);
v_remainder_653_ = lean_nat_sub(v_significand_599_, v___x_652_);
lean_dec(v___x_652_);
lean_dec(v_significand_599_);
v___x_654_ = lean_nat_sub(v___x_647_, v___x_605_);
lean_dec(v___x_647_);
v_half_655_ = lean_nat_shiftl(v___x_605_, v___x_654_);
lean_dec(v___x_654_);
v___x_656_ = lean_nat_dec_lt(v_remainder_653_, v_half_655_);
if (v___x_656_ == 0)
{
uint8_t v___x_657_; 
v___x_657_ = lean_nat_dec_lt(v_half_655_, v_remainder_653_);
lean_dec(v_remainder_653_);
lean_dec(v_half_655_);
if (v___x_657_ == 0)
{
lean_object* v___x_658_; lean_object* v___x_659_; uint8_t v___x_660_; 
v___x_658_ = lean_unsigned_to_nat(2u);
v___x_659_ = lean_nat_mod(v_quotient_651_, v___x_658_);
v___x_660_ = lean_nat_dec_eq(v___x_659_, v___x_582_);
lean_dec(v___x_659_);
if (v___x_660_ == 0)
{
lean_object* v___x_661_; 
v___x_661_ = lean_nat_add(v_quotient_651_, v___x_605_);
lean_dec(v_quotient_651_);
v___y_640_ = v___x_661_;
goto v___jp_639_;
}
else
{
v___y_640_ = v_quotient_651_;
goto v___jp_639_;
}
}
else
{
lean_object* v___x_662_; 
v___x_662_ = lean_nat_add(v_quotient_651_, v___x_605_);
lean_dec(v_quotient_651_);
v___y_640_ = v___x_662_;
goto v___jp_639_;
}
}
else
{
lean_dec(v_half_655_);
lean_dec(v_remainder_653_);
v___y_640_ = v_quotient_651_;
goto v___jp_639_;
}
}
else
{
lean_dec(v___x_647_);
lean_dec(v_significand_599_);
v___y_640_ = v___x_582_;
goto v___jp_639_;
}
}
else
{
lean_dec(v___x_647_);
lean_dec(v_leading_602_);
v___y_640_ = v_significand_599_;
goto v___jp_639_;
}
}
v___jp_611_:
{
lean_object* v___x_615_; lean_object* v___x_616_; lean_object* v___x_617_; lean_object* v___x_618_; lean_object* v___x_619_; lean_object* v___x_620_; lean_object* v___x_621_; uint32_t v___x_622_; 
v___x_615_ = lean_unsigned_to_nat(255u);
v___x_616_ = lean_nat_land(v___y_612_, v___x_615_);
lean_dec(v___y_612_);
v___x_617_ = lean_nat_shiftl(v___x_616_, v___x_610_);
lean_dec(v___x_616_);
v___x_618_ = lean_nat_lor(v___y_614_, v___x_617_);
lean_dec(v___x_617_);
lean_dec(v___y_614_);
v___x_619_ = lean_unsigned_to_nat(8388607u);
v___x_620_ = lean_nat_land(v___y_613_, v___x_619_);
lean_dec(v___y_613_);
v___x_621_ = lean_nat_lor(v___x_618_, v___x_620_);
lean_dec(v___x_620_);
lean_dec(v___x_618_);
v___x_622_ = lean_uint32_of_nat(v___x_621_);
lean_dec(v___x_621_);
return v___x_622_;
}
v___jp_623_:
{
lean_object* v___x_626_; lean_object* v___x_627_; lean_object* v___x_628_; lean_object* v___x_629_; 
v___x_626_ = lean_int_add(v___y_624_, v___x_607_);
lean_dec(v___y_624_);
v___x_627_ = l_Int_toNat(v___x_626_);
lean_dec(v___x_626_);
v___x_628_ = lean_unsigned_to_nat(8388608u);
v___x_629_ = lean_nat_sub(v___y_625_, v___x_628_);
lean_dec(v___y_625_);
if (v_negative_598_ == 0)
{
v___y_612_ = v___x_627_;
v___y_613_ = v___x_629_;
v___y_614_ = v___x_582_;
goto v___jp_611_;
}
else
{
lean_object* v___x_630_; 
v___x_630_ = lean_unsigned_to_nat(2147483648u);
v___y_612_ = v___x_627_;
v___y_613_ = v___x_629_;
v___y_614_ = v___x_630_;
goto v___jp_611_;
}
}
v___jp_631_:
{
uint8_t v___x_635_; 
v___x_635_ = lean_int_dec_lt(v___x_607_, v___y_634_);
if (v___x_635_ == 0)
{
if (v___y_633_ == 0)
{
v___y_624_ = v___y_634_;
v___y_625_ = v___y_632_;
goto v___jp_623_;
}
else
{
lean_object* v___x_636_; 
lean_dec(v___y_632_);
v___x_636_ = lean_unsigned_to_nat(8388608u);
v___y_624_ = v___y_634_;
v___y_625_ = v___x_636_;
goto v___jp_623_;
}
}
else
{
lean_dec(v___y_634_);
lean_dec(v___y_632_);
if (v_negative_598_ == 0)
{
uint32_t v___x_637_; 
v___x_637_ = lean_uint32_once(&lp_competition_Submission_finishDigits___closed__3, &lp_competition_Submission_finishDigits___closed__3_once, _init_lp_competition_Submission_finishDigits___closed__3);
return v___x_637_;
}
else
{
uint32_t v___x_638_; 
v___x_638_ = lean_uint32_once(&lp_competition_Submission_finishDigits___closed__5, &lp_competition_Submission_finishDigits___closed__5_once, _init_lp_competition_Submission_finishDigits___closed__5);
return v___x_638_;
}
}
}
v___jp_639_:
{
lean_object* v___x_641_; uint8_t v_carry_642_; 
v___x_641_ = lean_unsigned_to_nat(16777216u);
v_carry_642_ = lean_nat_dec_eq(v___y_640_, v___x_641_);
if (v_carry_642_ == 0)
{
v___y_632_ = v___y_640_;
v___y_633_ = v_carry_642_;
v___y_634_ = v_totalExponent_604_;
goto v___jp_631_;
}
else
{
lean_object* v___x_643_; 
v___x_643_ = lean_int_add(v_totalExponent_604_, v___x_606_);
lean_dec(v_totalExponent_604_);
v___y_632_ = v___y_640_;
v___y_633_ = v_carry_642_;
v___y_634_ = v___x_643_;
goto v___jp_631_;
}
}
}
else
{
lean_object* v___x_663_; lean_object* v___x_664_; uint8_t v_isNeg_665_; 
lean_dec(v_totalExponent_604_);
v___x_663_ = lean_obj_once(&lp_competition_Submission_finishDigits___closed__9, &lp_competition_Submission_finishDigits___closed__9_once, _init_lp_competition_Submission_finishDigits___closed__9);
v___x_664_ = lean_int_add(v_exponent_600_, v___x_663_);
lean_dec(v_exponent_600_);
v_isNeg_665_ = lean_int_dec_lt(v___x_664_, v___x_583_);
if (v_isNeg_665_ == 0)
{
lean_object* v_a_666_; lean_object* v___x_667_; 
lean_dec(v_leading_602_);
v_a_666_ = lean_nat_abs(v___x_664_);
lean_dec(v___x_664_);
v___x_667_ = lean_nat_shiftl(v_significand_599_, v_a_666_);
lean_dec(v_a_666_);
lean_dec(v_significand_599_);
v___y_587_ = v___x_667_;
goto v___jp_586_;
}
else
{
lean_object* v_abs_668_; lean_object* v_a_669_; lean_object* v___x_670_; uint8_t v___x_671_; 
v_abs_668_ = lean_nat_abs(v___x_664_);
lean_dec(v___x_664_);
v_a_669_ = lean_nat_sub(v_abs_668_, v___x_605_);
lean_dec(v_abs_668_);
v___x_670_ = lean_nat_add(v_a_669_, v___x_605_);
lean_dec(v_a_669_);
v___x_671_ = lean_nat_dec_eq(v___x_670_, v___x_582_);
if (v___x_671_ == 0)
{
lean_object* v___x_672_; uint8_t v___x_673_; 
v___x_672_ = lean_nat_add(v_leading_602_, v___x_605_);
lean_dec(v_leading_602_);
v___x_673_ = lean_nat_dec_lt(v___x_672_, v___x_670_);
lean_dec(v___x_672_);
if (v___x_673_ == 0)
{
lean_object* v_quotient_674_; lean_object* v___x_675_; lean_object* v_remainder_676_; lean_object* v___x_677_; lean_object* v_half_678_; uint8_t v___x_679_; 
v_quotient_674_ = lean_nat_shiftr(v_significand_599_, v___x_670_);
v___x_675_ = lean_nat_shiftl(v_quotient_674_, v___x_670_);
v_remainder_676_ = lean_nat_sub(v_significand_599_, v___x_675_);
lean_dec(v___x_675_);
lean_dec(v_significand_599_);
v___x_677_ = lean_nat_sub(v___x_670_, v___x_605_);
lean_dec(v___x_670_);
v_half_678_ = lean_nat_shiftl(v___x_605_, v___x_677_);
lean_dec(v___x_677_);
v___x_679_ = lean_nat_dec_lt(v_remainder_676_, v_half_678_);
if (v___x_679_ == 0)
{
uint8_t v___x_680_; 
v___x_680_ = lean_nat_dec_lt(v_half_678_, v_remainder_676_);
lean_dec(v_remainder_676_);
lean_dec(v_half_678_);
if (v___x_680_ == 0)
{
lean_object* v___x_681_; lean_object* v___x_682_; uint8_t v___x_683_; 
v___x_681_ = lean_unsigned_to_nat(2u);
v___x_682_ = lean_nat_mod(v_quotient_674_, v___x_681_);
v___x_683_ = lean_nat_dec_eq(v___x_682_, v___x_582_);
lean_dec(v___x_682_);
if (v___x_683_ == 0)
{
lean_object* v___x_684_; 
v___x_684_ = lean_nat_add(v_quotient_674_, v___x_605_);
lean_dec(v_quotient_674_);
v___y_587_ = v___x_684_;
goto v___jp_586_;
}
else
{
v___y_587_ = v_quotient_674_;
goto v___jp_586_;
}
}
else
{
lean_object* v___x_685_; 
v___x_685_ = lean_nat_add(v_quotient_674_, v___x_605_);
lean_dec(v_quotient_674_);
v___y_587_ = v___x_685_;
goto v___jp_586_;
}
}
else
{
lean_dec(v_half_678_);
lean_dec(v_remainder_676_);
v___y_587_ = v_quotient_674_;
goto v___jp_586_;
}
}
else
{
lean_dec(v___x_670_);
lean_dec(v_significand_599_);
v___y_587_ = v___x_582_;
goto v___jp_586_;
}
}
else
{
lean_dec(v___x_670_);
lean_dec(v_leading_602_);
v___y_587_ = v_significand_599_;
goto v___jp_586_;
}
}
}
}
else
{
lean_dec(v_exponent_600_);
lean_dec(v_significand_599_);
lean_dec_ref(v___x_585_);
if (v_negative_598_ == 0)
{
uint32_t v___x_686_; 
v___x_686_ = lean_uint32_once(&lp_competition_Submission_finishDigits___closed__11, &lp_competition_Submission_finishDigits___closed__11_once, _init_lp_competition_Submission_finishDigits___closed__11);
return v___x_686_;
}
else
{
uint32_t v___x_687_; 
v___x_687_ = lean_uint32_once(&lp_competition_Submission_finishDigits___closed__1, &lp_competition_Submission_finishDigits___closed__1_once, _init_lp_competition_Submission_finishDigits___closed__1);
return v___x_687_;
}
}
v___jp_586_:
{
uint8_t v___x_588_; 
v___x_588_ = lean_nat_dec_eq(v___y_587_, v___x_582_);
if (v___x_588_ == 0)
{
lean_object* v___x_589_; uint8_t v___x_590_; 
v___x_589_ = lean_unsigned_to_nat(8388608u);
v___x_590_ = lean_nat_dec_eq(v___y_587_, v___x_589_);
if (v___x_590_ == 0)
{
uint8_t v_negative_591_; 
v_negative_591_ = lean_ctor_get_uint8(v___x_585_, sizeof(void*)*2);
lean_dec_ref(v___x_585_);
if (v_negative_591_ == 0)
{
v___y_353_ = v___y_587_;
v___y_354_ = v___x_582_;
goto v___jp_352_;
}
else
{
lean_object* v___x_592_; 
v___x_592_ = lean_unsigned_to_nat(2147483648u);
v___y_353_ = v___y_587_;
v___y_354_ = v___x_592_;
goto v___jp_352_;
}
}
else
{
uint8_t v_negative_593_; 
lean_dec(v___y_587_);
v_negative_593_ = lean_ctor_get_uint8(v___x_585_, sizeof(void*)*2);
lean_dec_ref(v___x_585_);
if (v_negative_593_ == 0)
{
v___y_348_ = v___x_589_;
v___y_349_ = v___x_582_;
goto v___jp_347_;
}
else
{
lean_object* v___x_594_; 
v___x_594_ = lean_unsigned_to_nat(2147483648u);
v___y_348_ = v___x_589_;
v___y_349_ = v___x_594_;
goto v___jp_347_;
}
}
}
else
{
uint8_t v_negative_595_; 
lean_dec(v___y_587_);
v_negative_595_ = lean_ctor_get_uint8(v___x_585_, sizeof(void*)*2);
lean_dec_ref(v___x_585_);
if (v_negative_595_ == 0)
{
uint32_t v___x_596_; 
v___x_596_ = lean_uint32_once(&lp_competition_Submission_finishDigits___closed__11, &lp_competition_Submission_finishDigits___closed__11_once, _init_lp_competition_Submission_finishDigits___closed__11);
return v___x_596_;
}
else
{
uint32_t v___x_597_; 
v___x_597_ = lean_uint32_once(&lp_competition_Submission_finishDigits___closed__1, &lp_competition_Submission_finishDigits___closed__1_once, _init_lp_competition_Submission_finishDigits___closed__1);
return v___x_597_;
}
}
}
}
else
{
lean_dec(v_e_345_);
if (v_negZero_346_ == 0)
{
uint32_t v___x_688_; 
v___x_688_ = 0;
return v___x_688_;
}
else
{
uint32_t v___x_689_; 
v___x_689_ = 2147483648;
return v___x_689_;
}
}
}
else
{
lean_object* v_val_690_; lean_object* v___x_691_; uint8_t v_isZero_692_; 
v_val_690_ = lean_ctor_get(v___x_581_, 0);
lean_inc(v_val_690_);
lean_dec_ref_known(v___x_581_, 1);
v___x_691_ = lean_unsigned_to_nat(0u);
v_isZero_692_ = lean_nat_dec_eq(v_val_690_, v___x_691_);
if (v_isZero_692_ == 1)
{
lean_dec(v_val_690_);
if (v_neg_343_ == 0)
{
lean_object* v___x_693_; lean_object* v___x_694_; 
v___x_693_ = lean_array_get_borrowed(v___x_691_, v_r_344_, v___x_691_);
lean_inc(v___x_693_);
v___x_694_ = lean_nat_to_int(v___x_693_);
v___y_436_ = v___x_694_;
goto v___jp_435_;
}
else
{
lean_object* v___x_695_; lean_object* v___x_696_; lean_object* v___x_697_; 
v___x_695_ = lean_array_get_borrowed(v___x_691_, v_r_344_, v___x_691_);
lean_inc(v___x_695_);
v___x_696_ = lean_nat_to_int(v___x_695_);
v___x_697_ = lean_int_neg(v___x_696_);
lean_dec(v___x_696_);
v___y_436_ = v___x_697_;
goto v___jp_435_;
}
}
else
{
lean_object* v_one_698_; lean_object* v_n_699_; lean_object* v___y_701_; lean_object* v_x_760_; lean_object* v___x_761_; lean_object* v___x_762_; lean_object* v___x_763_; lean_object* v___x_764_; lean_object* v___x_765_; lean_object* v___x_766_; lean_object* v___x_767_; lean_object* v_v_768_; lean_object* v___x_771_; uint8_t v___x_772_; 
v_one_698_ = lean_unsigned_to_nat(1u);
v_n_699_ = lean_nat_sub(v_val_690_, v_one_698_);
lean_dec(v_val_690_);
v_x_760_ = lean_array_get_borrowed(v___x_691_, v_r_344_, v_n_699_);
v___x_761_ = lean_nat_add(v_n_699_, v_one_698_);
v___x_762_ = lean_array_get_borrowed(v___x_691_, v_r_344_, v___x_761_);
lean_dec(v___x_761_);
v___x_763_ = lean_unsigned_to_nat(1073741824u);
v___x_764_ = lean_nat_mul(v___x_762_, v___x_763_);
v___x_765_ = lean_unsigned_to_nat(4u);
v___x_766_ = lean_unsigned_to_nat(2u);
v___x_767_ = lean_nat_shiftr(v_x_760_, v___x_766_);
v_v_768_ = lean_nat_add(v___x_764_, v___x_767_);
lean_dec(v___x_767_);
lean_dec(v___x_764_);
v___x_771_ = lean_nat_mod(v_x_760_, v___x_765_);
v___x_772_ = lean_nat_dec_eq(v___x_771_, v___x_691_);
lean_dec(v___x_771_);
if (v___x_772_ == 0)
{
goto v___jp_769_;
}
else
{
uint8_t v___x_773_; 
lean_inc(v_n_699_);
v___x_773_ = lp_competition_Submission_anyGo(v_r_344_, v_n_699_);
if (v___x_773_ == 0)
{
v___y_701_ = v_v_768_;
goto v___jp_700_;
}
else
{
goto v___jp_769_;
}
}
v___jp_700_:
{
lean_object* v___x_702_; uint8_t v___x_703_; 
v___x_702_ = lean_unsigned_to_nat(32u);
v___x_703_ = lean_nat_dec_eq(v___y_701_, v___x_691_);
if (v___x_703_ == 0)
{
lean_object* v___x_704_; lean_object* v___x_705_; lean_object* v___x_706_; lean_object* v___x_707_; lean_object* v___x_708_; lean_object* v_leading_709_; lean_object* v___x_710_; lean_object* v_totalExponent_711_; lean_object* v___x_712_; lean_object* v___x_713_; lean_object* v___x_714_; uint8_t v___x_715_; 
v___x_704_ = lean_nat_mul(v___x_702_, v_n_699_);
lean_dec(v_n_699_);
v___x_705_ = lean_unsigned_to_nat(2u);
v___x_706_ = lean_nat_add(v___x_704_, v___x_705_);
lean_dec(v___x_704_);
v___x_707_ = lean_nat_to_int(v___x_706_);
v___x_708_ = lean_int_add(v_e_345_, v___x_707_);
lean_dec(v___x_707_);
lean_dec(v_e_345_);
v_leading_709_ = lean_nat_log2(v___y_701_);
lean_inc(v_leading_709_);
v___x_710_ = lean_nat_to_int(v_leading_709_);
v_totalExponent_711_ = lean_int_add(v___x_710_, v___x_708_);
lean_dec(v___x_710_);
v___x_712_ = lean_obj_once(&lp_competition_Submission_finishDigits___closed__6, &lp_competition_Submission_finishDigits___closed__6_once, _init_lp_competition_Submission_finishDigits___closed__6);
v___x_713_ = lean_obj_once(&lp_competition_Submission_finishDigits___closed__7, &lp_competition_Submission_finishDigits___closed__7_once, _init_lp_competition_Submission_finishDigits___closed__7);
v___x_714_ = lean_obj_once(&lp_competition_Submission_finishDigits___closed__8, &lp_competition_Submission_finishDigits___closed__8_once, _init_lp_competition_Submission_finishDigits___closed__8);
v___x_715_ = lean_int_dec_lt(v_totalExponent_711_, v___x_714_);
if (v___x_715_ == 0)
{
lean_object* v___x_716_; uint8_t v___x_717_; 
lean_dec(v___x_708_);
v___x_716_ = lean_unsigned_to_nat(23u);
v___x_717_ = lean_nat_dec_le(v___x_716_, v_leading_709_);
if (v___x_717_ == 0)
{
lean_object* v___x_718_; lean_object* v___x_719_; 
v___x_718_ = lean_nat_sub(v___x_716_, v_leading_709_);
lean_dec(v_leading_709_);
v___x_719_ = lean_nat_shiftl(v___y_701_, v___x_718_);
lean_dec(v___x_718_);
lean_dec(v___y_701_);
v___y_570_ = v_totalExponent_711_;
v___y_571_ = v___x_716_;
v___y_572_ = v___x_713_;
v___y_573_ = v___x_712_;
v___y_574_ = v___x_691_;
v___y_575_ = v___x_702_;
v___y_576_ = v___x_719_;
goto v___jp_569_;
}
else
{
lean_object* v___x_720_; uint8_t v___x_721_; 
v___x_720_ = lean_nat_sub(v_leading_709_, v___x_716_);
v___x_721_ = lean_nat_dec_eq(v___x_720_, v___x_691_);
if (v___x_721_ == 0)
{
lean_object* v___x_722_; uint8_t v___x_723_; 
v___x_722_ = lean_nat_add(v_leading_709_, v_one_698_);
lean_dec(v_leading_709_);
v___x_723_ = lean_nat_dec_lt(v___x_722_, v___x_720_);
lean_dec(v___x_722_);
if (v___x_723_ == 0)
{
lean_object* v_quotient_724_; lean_object* v___x_725_; lean_object* v_remainder_726_; lean_object* v___x_727_; lean_object* v_half_728_; uint8_t v___x_729_; 
v_quotient_724_ = lean_nat_shiftr(v___y_701_, v___x_720_);
v___x_725_ = lean_nat_shiftl(v_quotient_724_, v___x_720_);
v_remainder_726_ = lean_nat_sub(v___y_701_, v___x_725_);
lean_dec(v___x_725_);
lean_dec(v___y_701_);
v___x_727_ = lean_nat_sub(v___x_720_, v_one_698_);
lean_dec(v___x_720_);
v_half_728_ = lean_nat_shiftl(v_one_698_, v___x_727_);
lean_dec(v___x_727_);
v___x_729_ = lean_nat_dec_lt(v_remainder_726_, v_half_728_);
if (v___x_729_ == 0)
{
uint8_t v___x_730_; 
v___x_730_ = lean_nat_dec_lt(v_half_728_, v_remainder_726_);
lean_dec(v_remainder_726_);
lean_dec(v_half_728_);
if (v___x_730_ == 0)
{
lean_object* v___x_731_; uint8_t v___x_732_; 
v___x_731_ = lean_nat_mod(v_quotient_724_, v___x_705_);
v___x_732_ = lean_nat_dec_eq(v___x_731_, v___x_691_);
lean_dec(v___x_731_);
if (v___x_732_ == 0)
{
lean_object* v___x_733_; 
v___x_733_ = lean_nat_add(v_quotient_724_, v_one_698_);
lean_dec(v_quotient_724_);
v___y_570_ = v_totalExponent_711_;
v___y_571_ = v___x_716_;
v___y_572_ = v___x_713_;
v___y_573_ = v___x_712_;
v___y_574_ = v___x_691_;
v___y_575_ = v___x_702_;
v___y_576_ = v___x_733_;
goto v___jp_569_;
}
else
{
v___y_570_ = v_totalExponent_711_;
v___y_571_ = v___x_716_;
v___y_572_ = v___x_713_;
v___y_573_ = v___x_712_;
v___y_574_ = v___x_691_;
v___y_575_ = v___x_702_;
v___y_576_ = v_quotient_724_;
goto v___jp_569_;
}
}
else
{
lean_object* v___x_734_; 
v___x_734_ = lean_nat_add(v_quotient_724_, v_one_698_);
lean_dec(v_quotient_724_);
v___y_570_ = v_totalExponent_711_;
v___y_571_ = v___x_716_;
v___y_572_ = v___x_713_;
v___y_573_ = v___x_712_;
v___y_574_ = v___x_691_;
v___y_575_ = v___x_702_;
v___y_576_ = v___x_734_;
goto v___jp_569_;
}
}
else
{
lean_dec(v_half_728_);
lean_dec(v_remainder_726_);
v___y_570_ = v_totalExponent_711_;
v___y_571_ = v___x_716_;
v___y_572_ = v___x_713_;
v___y_573_ = v___x_712_;
v___y_574_ = v___x_691_;
v___y_575_ = v___x_702_;
v___y_576_ = v_quotient_724_;
goto v___jp_569_;
}
}
else
{
lean_dec(v___x_720_);
lean_dec(v___y_701_);
v___y_570_ = v_totalExponent_711_;
v___y_571_ = v___x_716_;
v___y_572_ = v___x_713_;
v___y_573_ = v___x_712_;
v___y_574_ = v___x_691_;
v___y_575_ = v___x_702_;
v___y_576_ = v___x_691_;
goto v___jp_569_;
}
}
else
{
lean_dec(v___x_720_);
lean_dec(v_leading_709_);
v___y_570_ = v_totalExponent_711_;
v___y_571_ = v___x_716_;
v___y_572_ = v___x_713_;
v___y_573_ = v___x_712_;
v___y_574_ = v___x_691_;
v___y_575_ = v___x_702_;
v___y_576_ = v___y_701_;
goto v___jp_569_;
}
}
}
else
{
lean_object* v___x_735_; lean_object* v___x_736_; lean_object* v_intZero_737_; uint8_t v_isNeg_738_; 
lean_dec(v_totalExponent_711_);
v___x_735_ = lean_obj_once(&lp_competition_Submission_finishDigits___closed__9, &lp_competition_Submission_finishDigits___closed__9_once, _init_lp_competition_Submission_finishDigits___closed__9);
v___x_736_ = lean_int_add(v___x_708_, v___x_735_);
lean_dec(v___x_708_);
v_intZero_737_ = lean_obj_once(&lp_competition___private_Submission_0__FloatLib_Floats_Formats_BinaryInterchange_Model_roundDyadicGeneral_match__1_splitter___redArg___closed__0, &lp_competition___private_Submission_0__FloatLib_Floats_Formats_BinaryInterchange_Model_roundDyadicGeneral_match__1_splitter___redArg___closed__0_once, _init_lp_competition___private_Submission_0__FloatLib_Floats_Formats_BinaryInterchange_Model_roundDyadicGeneral_match__1_splitter___redArg___closed__0);
v_isNeg_738_ = lean_int_dec_lt(v___x_736_, v_intZero_737_);
if (v_isNeg_738_ == 0)
{
lean_object* v_a_739_; lean_object* v___x_740_; 
lean_dec(v_leading_709_);
v_a_739_ = lean_nat_abs(v___x_736_);
lean_dec(v___x_736_);
v___x_740_ = lean_nat_shiftl(v___y_701_, v_a_739_);
lean_dec(v_a_739_);
lean_dec(v___y_701_);
v___y_513_ = v___x_702_;
v___y_514_ = v___x_691_;
v___y_515_ = v___x_740_;
goto v___jp_512_;
}
else
{
lean_object* v_abs_741_; lean_object* v_a_742_; lean_object* v___x_743_; uint8_t v___x_744_; 
v_abs_741_ = lean_nat_abs(v___x_736_);
lean_dec(v___x_736_);
v_a_742_ = lean_nat_sub(v_abs_741_, v_one_698_);
lean_dec(v_abs_741_);
v___x_743_ = lean_nat_add(v_a_742_, v_one_698_);
lean_dec(v_a_742_);
v___x_744_ = lean_nat_dec_eq(v___x_743_, v___x_691_);
if (v___x_744_ == 0)
{
lean_object* v___x_745_; uint8_t v___x_746_; 
v___x_745_ = lean_nat_add(v_leading_709_, v_one_698_);
lean_dec(v_leading_709_);
v___x_746_ = lean_nat_dec_lt(v___x_745_, v___x_743_);
lean_dec(v___x_745_);
if (v___x_746_ == 0)
{
lean_object* v_quotient_747_; lean_object* v___x_748_; lean_object* v_remainder_749_; lean_object* v___x_750_; lean_object* v_half_751_; uint8_t v___x_752_; 
v_quotient_747_ = lean_nat_shiftr(v___y_701_, v___x_743_);
v___x_748_ = lean_nat_shiftl(v_quotient_747_, v___x_743_);
v_remainder_749_ = lean_nat_sub(v___y_701_, v___x_748_);
lean_dec(v___x_748_);
lean_dec(v___y_701_);
v___x_750_ = lean_nat_sub(v___x_743_, v_one_698_);
lean_dec(v___x_743_);
v_half_751_ = lean_nat_shiftl(v_one_698_, v___x_750_);
lean_dec(v___x_750_);
v___x_752_ = lean_nat_dec_lt(v_remainder_749_, v_half_751_);
if (v___x_752_ == 0)
{
uint8_t v___x_753_; 
v___x_753_ = lean_nat_dec_lt(v_half_751_, v_remainder_749_);
lean_dec(v_remainder_749_);
lean_dec(v_half_751_);
if (v___x_753_ == 0)
{
lean_object* v___x_754_; uint8_t v___x_755_; 
v___x_754_ = lean_nat_mod(v_quotient_747_, v___x_705_);
v___x_755_ = lean_nat_dec_eq(v___x_754_, v___x_691_);
lean_dec(v___x_754_);
if (v___x_755_ == 0)
{
lean_object* v___x_756_; 
v___x_756_ = lean_nat_add(v_quotient_747_, v_one_698_);
lean_dec(v_quotient_747_);
v___y_513_ = v___x_702_;
v___y_514_ = v___x_691_;
v___y_515_ = v___x_756_;
goto v___jp_512_;
}
else
{
v___y_513_ = v___x_702_;
v___y_514_ = v___x_691_;
v___y_515_ = v_quotient_747_;
goto v___jp_512_;
}
}
else
{
lean_object* v___x_757_; 
v___x_757_ = lean_nat_add(v_quotient_747_, v_one_698_);
lean_dec(v_quotient_747_);
v___y_513_ = v___x_702_;
v___y_514_ = v___x_691_;
v___y_515_ = v___x_757_;
goto v___jp_512_;
}
}
else
{
lean_dec(v_half_751_);
lean_dec(v_remainder_749_);
v___y_513_ = v___x_702_;
v___y_514_ = v___x_691_;
v___y_515_ = v_quotient_747_;
goto v___jp_512_;
}
}
else
{
lean_dec(v___x_743_);
lean_dec(v___y_701_);
v___y_513_ = v___x_702_;
v___y_514_ = v___x_691_;
v___y_515_ = v___x_691_;
goto v___jp_512_;
}
}
else
{
lean_dec(v___x_743_);
lean_dec(v_leading_709_);
v___y_513_ = v___x_702_;
v___y_514_ = v___x_691_;
v___y_515_ = v___y_701_;
goto v___jp_512_;
}
}
}
}
else
{
lean_dec(v___y_701_);
lean_dec(v_n_699_);
lean_dec(v_e_345_);
if (v_neg_343_ == 0)
{
uint32_t v___x_758_; 
v___x_758_ = lean_uint32_once(&lp_competition_Submission_finishDigits___closed__11, &lp_competition_Submission_finishDigits___closed__11_once, _init_lp_competition_Submission_finishDigits___closed__11);
return v___x_758_;
}
else
{
uint32_t v___x_759_; 
v___x_759_ = lean_uint32_once(&lp_competition_Submission_finishDigits___closed__1, &lp_competition_Submission_finishDigits___closed__1_once, _init_lp_competition_Submission_finishDigits___closed__1);
return v___x_759_;
}
}
}
v___jp_769_:
{
lean_object* v___x_770_; 
v___x_770_ = lean_nat_lor(v_v_768_, v_one_698_);
lean_dec(v_v_768_);
v___y_701_ = v___x_770_;
goto v___jp_700_;
}
}
}
v___jp_347_:
{
lean_object* v___x_350_; uint32_t v___x_351_; 
v___x_350_ = lean_nat_lor(v___y_349_, v___y_348_);
lean_dec(v___y_349_);
v___x_351_ = lean_uint32_of_nat(v___x_350_);
lean_dec(v___x_350_);
return v___x_351_;
}
v___jp_352_:
{
lean_object* v___x_355_; lean_object* v___x_356_; lean_object* v___x_357_; uint32_t v___x_358_; 
v___x_355_ = lean_unsigned_to_nat(8388607u);
v___x_356_ = lean_nat_land(v___y_353_, v___x_355_);
lean_dec(v___y_353_);
v___x_357_ = lean_nat_lor(v___y_354_, v___x_356_);
lean_dec(v___x_356_);
lean_dec(v___y_354_);
v___x_358_ = lean_uint32_of_nat(v___x_357_);
lean_dec(v___x_357_);
return v___x_358_;
}
v___jp_359_:
{
lean_object* v___x_362_; lean_object* v___x_363_; lean_object* v___x_364_; uint32_t v___x_365_; 
v___x_362_ = lean_unsigned_to_nat(8388607u);
v___x_363_ = lean_nat_land(v___y_360_, v___x_362_);
lean_dec(v___y_360_);
v___x_364_ = lean_nat_lor(v___y_361_, v___x_363_);
lean_dec(v___x_363_);
lean_dec(v___y_361_);
v___x_365_ = lean_uint32_of_nat(v___x_364_);
lean_dec(v___x_364_);
return v___x_365_;
}
v___jp_366_:
{
lean_object* v___x_369_; uint32_t v___x_370_; 
v___x_369_ = lean_nat_lor(v___y_368_, v___y_367_);
lean_dec(v___y_368_);
v___x_370_ = lean_uint32_of_nat(v___x_369_);
lean_dec(v___x_369_);
return v___x_370_;
}
v___jp_371_:
{
uint8_t v___x_375_; 
v___x_375_ = lean_nat_dec_eq(v___y_374_, v___y_372_);
if (v___x_375_ == 0)
{
lean_object* v___x_376_; uint8_t v___x_377_; 
v___x_376_ = lean_unsigned_to_nat(8388608u);
v___x_377_ = lean_nat_dec_eq(v___y_374_, v___x_376_);
if (v___x_377_ == 0)
{
uint8_t v_negative_378_; 
v_negative_378_ = lean_ctor_get_uint8(v___y_373_, sizeof(void*)*2);
lean_dec_ref(v___y_373_);
if (v_negative_378_ == 0)
{
v___y_360_ = v___y_374_;
v___y_361_ = v___y_372_;
goto v___jp_359_;
}
else
{
lean_object* v___x_379_; 
lean_dec(v___y_372_);
v___x_379_ = lean_unsigned_to_nat(2147483648u);
v___y_360_ = v___y_374_;
v___y_361_ = v___x_379_;
goto v___jp_359_;
}
}
else
{
uint8_t v_negative_380_; 
lean_dec(v___y_374_);
v_negative_380_ = lean_ctor_get_uint8(v___y_373_, sizeof(void*)*2);
lean_dec_ref(v___y_373_);
if (v_negative_380_ == 0)
{
v___y_367_ = v___x_376_;
v___y_368_ = v___y_372_;
goto v___jp_366_;
}
else
{
lean_object* v___x_381_; 
lean_dec(v___y_372_);
v___x_381_ = lean_unsigned_to_nat(2147483648u);
v___y_367_ = v___x_376_;
v___y_368_ = v___x_381_;
goto v___jp_366_;
}
}
}
else
{
uint8_t v_negative_382_; 
lean_dec(v___y_374_);
v_negative_382_ = lean_ctor_get_uint8(v___y_373_, sizeof(void*)*2);
lean_dec_ref(v___y_373_);
if (v_negative_382_ == 0)
{
lean_object* v___x_383_; lean_object* v___x_384_; uint32_t v___x_385_; 
v___x_383_ = lean_unsigned_to_nat(32u);
v___x_384_ = l_BitVec_ofNat(v___x_383_, v___y_372_);
lean_dec(v___y_372_);
v___x_385_ = lean_uint32_of_nat(v___x_384_);
lean_dec(v___x_384_);
return v___x_385_;
}
else
{
uint32_t v___x_386_; 
lean_dec(v___y_372_);
v___x_386_ = lean_uint32_once(&lp_competition_Submission_finishDigits___closed__1, &lp_competition_Submission_finishDigits___closed__1_once, _init_lp_competition_Submission_finishDigits___closed__1);
return v___x_386_;
}
}
}
v___jp_387_:
{
lean_object* v___x_392_; lean_object* v___x_393_; lean_object* v___x_394_; lean_object* v___x_395_; lean_object* v___x_396_; lean_object* v___x_397_; lean_object* v___x_398_; uint32_t v___x_399_; 
v___x_392_ = lean_unsigned_to_nat(255u);
v___x_393_ = lean_nat_land(v___y_389_, v___x_392_);
lean_dec(v___y_389_);
v___x_394_ = lean_nat_shiftl(v___x_393_, v___y_390_);
lean_dec(v___x_393_);
v___x_395_ = lean_nat_lor(v___y_391_, v___x_394_);
lean_dec(v___x_394_);
lean_dec(v___y_391_);
v___x_396_ = lean_unsigned_to_nat(8388607u);
v___x_397_ = lean_nat_land(v___y_388_, v___x_396_);
lean_dec(v___y_388_);
v___x_398_ = lean_nat_lor(v___x_395_, v___x_397_);
lean_dec(v___x_397_);
lean_dec(v___x_395_);
v___x_399_ = lean_uint32_of_nat(v___x_398_);
lean_dec(v___x_398_);
return v___x_399_;
}
v___jp_400_:
{
lean_object* v___x_407_; lean_object* v___x_408_; lean_object* v___x_409_; lean_object* v___x_410_; 
v___x_407_ = lean_int_add(v___y_405_, v___y_402_);
lean_dec(v___y_405_);
v___x_408_ = l_Int_toNat(v___x_407_);
lean_dec(v___x_407_);
v___x_409_ = lean_unsigned_to_nat(8388608u);
v___x_410_ = lean_nat_sub(v___y_406_, v___x_409_);
lean_dec(v___y_406_);
if (v___y_401_ == 0)
{
v___y_388_ = v___x_410_;
v___y_389_ = v___x_408_;
v___y_390_ = v___y_404_;
v___y_391_ = v___y_403_;
goto v___jp_387_;
}
else
{
lean_object* v___x_411_; 
lean_dec(v___y_403_);
v___x_411_ = lean_unsigned_to_nat(2147483648u);
v___y_388_ = v___x_410_;
v___y_389_ = v___x_408_;
v___y_390_ = v___y_404_;
v___y_391_ = v___x_411_;
goto v___jp_387_;
}
}
v___jp_412_:
{
uint8_t v___x_420_; 
v___x_420_ = lean_int_dec_lt(v___y_416_, v___y_419_);
if (v___x_420_ == 0)
{
if (v___y_413_ == 0)
{
v___y_401_ = v___y_414_;
v___y_402_ = v___y_416_;
v___y_403_ = v___y_417_;
v___y_404_ = v___y_418_;
v___y_405_ = v___y_419_;
v___y_406_ = v___y_415_;
goto v___jp_400_;
}
else
{
lean_object* v___x_421_; 
lean_dec(v___y_415_);
v___x_421_ = lean_unsigned_to_nat(8388608u);
v___y_401_ = v___y_414_;
v___y_402_ = v___y_416_;
v___y_403_ = v___y_417_;
v___y_404_ = v___y_418_;
v___y_405_ = v___y_419_;
v___y_406_ = v___x_421_;
goto v___jp_400_;
}
}
else
{
lean_dec(v___y_419_);
lean_dec(v___y_417_);
lean_dec(v___y_415_);
if (v___y_414_ == 0)
{
uint32_t v___x_422_; 
v___x_422_ = lean_uint32_once(&lp_competition_Submission_finishDigits___closed__3, &lp_competition_Submission_finishDigits___closed__3_once, _init_lp_competition_Submission_finishDigits___closed__3);
return v___x_422_;
}
else
{
uint32_t v___x_423_; 
v___x_423_ = lean_uint32_once(&lp_competition_Submission_finishDigits___closed__5, &lp_competition_Submission_finishDigits___closed__5_once, _init_lp_competition_Submission_finishDigits___closed__5);
return v___x_423_;
}
}
}
v___jp_424_:
{
lean_object* v___x_432_; uint8_t v_carry_433_; 
v___x_432_ = lean_unsigned_to_nat(16777216u);
v_carry_433_ = lean_nat_dec_eq(v___y_431_, v___x_432_);
if (v_carry_433_ == 0)
{
v___y_413_ = v_carry_433_;
v___y_414_ = v___y_426_;
v___y_415_ = v___y_431_;
v___y_416_ = v___y_428_;
v___y_417_ = v___y_429_;
v___y_418_ = v___y_430_;
v___y_419_ = v___y_425_;
goto v___jp_412_;
}
else
{
lean_object* v___x_434_; 
v___x_434_ = lean_int_add(v___y_425_, v___y_427_);
lean_dec(v___y_425_);
v___y_413_ = v_carry_433_;
v___y_414_ = v___y_426_;
v___y_415_ = v___y_431_;
v___y_416_ = v___y_428_;
v___y_417_ = v___y_429_;
v___y_418_ = v___y_430_;
v___y_419_ = v___x_434_;
goto v___jp_412_;
}
}
v___jp_435_:
{
lean_object* v___x_437_; lean_object* v___x_438_; uint8_t v___x_439_; 
v___x_437_ = lean_unsigned_to_nat(0u);
v___x_438_ = lean_obj_once(&lp_competition___private_Submission_0__FloatLib_Floats_Formats_BinaryInterchange_Model_roundDyadicGeneral_match__1_splitter___redArg___closed__0, &lp_competition___private_Submission_0__FloatLib_Floats_Formats_BinaryInterchange_Model_roundDyadicGeneral_match__1_splitter___redArg___closed__0_once, _init_lp_competition___private_Submission_0__FloatLib_Floats_Formats_BinaryInterchange_Model_roundDyadicGeneral_match__1_splitter___redArg___closed__0);
v___x_439_ = lean_int_dec_eq(v___y_436_, v___x_438_);
if (v___x_439_ == 0)
{
lean_object* v___x_440_; uint8_t v_negative_441_; lean_object* v_significand_442_; lean_object* v_exponent_443_; uint8_t v___x_444_; 
v___x_440_ = lp_competition_ExactRuntime_ofIntDyadic(v___y_436_, v_e_345_);
lean_dec(v___y_436_);
v_negative_441_ = lean_ctor_get_uint8(v___x_440_, sizeof(void*)*2);
v_significand_442_ = lean_ctor_get(v___x_440_, 0);
lean_inc(v_significand_442_);
v_exponent_443_ = lean_ctor_get(v___x_440_, 1);
lean_inc(v_exponent_443_);
v___x_444_ = lean_nat_dec_eq(v_significand_442_, v___x_437_);
if (v___x_444_ == 0)
{
lean_object* v_leading_445_; lean_object* v___x_446_; lean_object* v_totalExponent_447_; lean_object* v___x_448_; lean_object* v___x_449_; lean_object* v___x_450_; lean_object* v___x_451_; uint8_t v___x_452_; 
v_leading_445_ = lean_nat_log2(v_significand_442_);
lean_inc(v_leading_445_);
v___x_446_ = lean_nat_to_int(v_leading_445_);
v_totalExponent_447_ = lean_int_add(v___x_446_, v_exponent_443_);
lean_dec(v___x_446_);
v___x_448_ = lean_unsigned_to_nat(1u);
v___x_449_ = lean_obj_once(&lp_competition_Submission_finishDigits___closed__6, &lp_competition_Submission_finishDigits___closed__6_once, _init_lp_competition_Submission_finishDigits___closed__6);
v___x_450_ = lean_obj_once(&lp_competition_Submission_finishDigits___closed__7, &lp_competition_Submission_finishDigits___closed__7_once, _init_lp_competition_Submission_finishDigits___closed__7);
v___x_451_ = lean_obj_once(&lp_competition_Submission_finishDigits___closed__8, &lp_competition_Submission_finishDigits___closed__8_once, _init_lp_competition_Submission_finishDigits___closed__8);
v___x_452_ = lean_int_dec_lt(v_totalExponent_447_, v___x_451_);
if (v___x_452_ == 0)
{
lean_object* v___x_453_; uint8_t v___x_454_; 
lean_dec(v_exponent_443_);
lean_dec_ref(v___x_440_);
v___x_453_ = lean_unsigned_to_nat(23u);
v___x_454_ = lean_nat_dec_le(v___x_453_, v_leading_445_);
if (v___x_454_ == 0)
{
lean_object* v___x_455_; lean_object* v___x_456_; 
v___x_455_ = lean_nat_sub(v___x_453_, v_leading_445_);
lean_dec(v_leading_445_);
v___x_456_ = lean_nat_shiftl(v_significand_442_, v___x_455_);
lean_dec(v___x_455_);
lean_dec(v_significand_442_);
v___y_425_ = v_totalExponent_447_;
v___y_426_ = v_negative_441_;
v___y_427_ = v___x_449_;
v___y_428_ = v___x_450_;
v___y_429_ = v___x_437_;
v___y_430_ = v___x_453_;
v___y_431_ = v___x_456_;
goto v___jp_424_;
}
else
{
lean_object* v___x_457_; uint8_t v___x_458_; 
v___x_457_ = lean_nat_sub(v_leading_445_, v___x_453_);
v___x_458_ = lean_nat_dec_eq(v___x_457_, v___x_437_);
if (v___x_458_ == 0)
{
lean_object* v___x_459_; uint8_t v___x_460_; 
v___x_459_ = lean_nat_add(v_leading_445_, v___x_448_);
lean_dec(v_leading_445_);
v___x_460_ = lean_nat_dec_lt(v___x_459_, v___x_457_);
lean_dec(v___x_459_);
if (v___x_460_ == 0)
{
lean_object* v_quotient_461_; lean_object* v___x_462_; lean_object* v_remainder_463_; lean_object* v___x_464_; lean_object* v_half_465_; uint8_t v___x_466_; 
v_quotient_461_ = lean_nat_shiftr(v_significand_442_, v___x_457_);
v___x_462_ = lean_nat_shiftl(v_quotient_461_, v___x_457_);
v_remainder_463_ = lean_nat_sub(v_significand_442_, v___x_462_);
lean_dec(v___x_462_);
lean_dec(v_significand_442_);
v___x_464_ = lean_nat_sub(v___x_457_, v___x_448_);
lean_dec(v___x_457_);
v_half_465_ = lean_nat_shiftl(v___x_448_, v___x_464_);
lean_dec(v___x_464_);
v___x_466_ = lean_nat_dec_lt(v_remainder_463_, v_half_465_);
if (v___x_466_ == 0)
{
uint8_t v___x_467_; 
v___x_467_ = lean_nat_dec_lt(v_half_465_, v_remainder_463_);
lean_dec(v_remainder_463_);
lean_dec(v_half_465_);
if (v___x_467_ == 0)
{
lean_object* v___x_468_; lean_object* v___x_469_; uint8_t v___x_470_; 
v___x_468_ = lean_unsigned_to_nat(2u);
v___x_469_ = lean_nat_mod(v_quotient_461_, v___x_468_);
v___x_470_ = lean_nat_dec_eq(v___x_469_, v___x_437_);
lean_dec(v___x_469_);
if (v___x_470_ == 0)
{
lean_object* v___x_471_; 
v___x_471_ = lean_nat_add(v_quotient_461_, v___x_448_);
lean_dec(v_quotient_461_);
v___y_425_ = v_totalExponent_447_;
v___y_426_ = v_negative_441_;
v___y_427_ = v___x_449_;
v___y_428_ = v___x_450_;
v___y_429_ = v___x_437_;
v___y_430_ = v___x_453_;
v___y_431_ = v___x_471_;
goto v___jp_424_;
}
else
{
v___y_425_ = v_totalExponent_447_;
v___y_426_ = v_negative_441_;
v___y_427_ = v___x_449_;
v___y_428_ = v___x_450_;
v___y_429_ = v___x_437_;
v___y_430_ = v___x_453_;
v___y_431_ = v_quotient_461_;
goto v___jp_424_;
}
}
else
{
lean_object* v___x_472_; 
v___x_472_ = lean_nat_add(v_quotient_461_, v___x_448_);
lean_dec(v_quotient_461_);
v___y_425_ = v_totalExponent_447_;
v___y_426_ = v_negative_441_;
v___y_427_ = v___x_449_;
v___y_428_ = v___x_450_;
v___y_429_ = v___x_437_;
v___y_430_ = v___x_453_;
v___y_431_ = v___x_472_;
goto v___jp_424_;
}
}
else
{
lean_dec(v_half_465_);
lean_dec(v_remainder_463_);
v___y_425_ = v_totalExponent_447_;
v___y_426_ = v_negative_441_;
v___y_427_ = v___x_449_;
v___y_428_ = v___x_450_;
v___y_429_ = v___x_437_;
v___y_430_ = v___x_453_;
v___y_431_ = v_quotient_461_;
goto v___jp_424_;
}
}
else
{
lean_dec(v___x_457_);
lean_dec(v_significand_442_);
v___y_425_ = v_totalExponent_447_;
v___y_426_ = v_negative_441_;
v___y_427_ = v___x_449_;
v___y_428_ = v___x_450_;
v___y_429_ = v___x_437_;
v___y_430_ = v___x_453_;
v___y_431_ = v___x_437_;
goto v___jp_424_;
}
}
else
{
lean_dec(v___x_457_);
lean_dec(v_leading_445_);
v___y_425_ = v_totalExponent_447_;
v___y_426_ = v_negative_441_;
v___y_427_ = v___x_449_;
v___y_428_ = v___x_450_;
v___y_429_ = v___x_437_;
v___y_430_ = v___x_453_;
v___y_431_ = v_significand_442_;
goto v___jp_424_;
}
}
}
else
{
lean_object* v___x_473_; lean_object* v___x_474_; uint8_t v_isNeg_475_; 
lean_dec(v_totalExponent_447_);
v___x_473_ = lean_obj_once(&lp_competition_Submission_finishDigits___closed__9, &lp_competition_Submission_finishDigits___closed__9_once, _init_lp_competition_Submission_finishDigits___closed__9);
v___x_474_ = lean_int_add(v_exponent_443_, v___x_473_);
lean_dec(v_exponent_443_);
v_isNeg_475_ = lean_int_dec_lt(v___x_474_, v___x_438_);
if (v_isNeg_475_ == 0)
{
lean_object* v_a_476_; lean_object* v___x_477_; 
lean_dec(v_leading_445_);
v_a_476_ = lean_nat_abs(v___x_474_);
lean_dec(v___x_474_);
v___x_477_ = lean_nat_shiftl(v_significand_442_, v_a_476_);
lean_dec(v_a_476_);
lean_dec(v_significand_442_);
v___y_372_ = v___x_437_;
v___y_373_ = v___x_440_;
v___y_374_ = v___x_477_;
goto v___jp_371_;
}
else
{
lean_object* v_abs_478_; lean_object* v_a_479_; lean_object* v___x_480_; uint8_t v___x_481_; 
v_abs_478_ = lean_nat_abs(v___x_474_);
lean_dec(v___x_474_);
v_a_479_ = lean_nat_sub(v_abs_478_, v___x_448_);
lean_dec(v_abs_478_);
v___x_480_ = lean_nat_add(v_a_479_, v___x_448_);
lean_dec(v_a_479_);
v___x_481_ = lean_nat_dec_eq(v___x_480_, v___x_437_);
if (v___x_481_ == 0)
{
lean_object* v___x_482_; uint8_t v___x_483_; 
v___x_482_ = lean_nat_add(v_leading_445_, v___x_448_);
lean_dec(v_leading_445_);
v___x_483_ = lean_nat_dec_lt(v___x_482_, v___x_480_);
lean_dec(v___x_482_);
if (v___x_483_ == 0)
{
lean_object* v_quotient_484_; lean_object* v___x_485_; lean_object* v_remainder_486_; lean_object* v___x_487_; lean_object* v_half_488_; uint8_t v___x_489_; 
v_quotient_484_ = lean_nat_shiftr(v_significand_442_, v___x_480_);
v___x_485_ = lean_nat_shiftl(v_quotient_484_, v___x_480_);
v_remainder_486_ = lean_nat_sub(v_significand_442_, v___x_485_);
lean_dec(v___x_485_);
lean_dec(v_significand_442_);
v___x_487_ = lean_nat_sub(v___x_480_, v___x_448_);
lean_dec(v___x_480_);
v_half_488_ = lean_nat_shiftl(v___x_448_, v___x_487_);
lean_dec(v___x_487_);
v___x_489_ = lean_nat_dec_lt(v_remainder_486_, v_half_488_);
if (v___x_489_ == 0)
{
uint8_t v___x_490_; 
v___x_490_ = lean_nat_dec_lt(v_half_488_, v_remainder_486_);
lean_dec(v_remainder_486_);
lean_dec(v_half_488_);
if (v___x_490_ == 0)
{
lean_object* v___x_491_; lean_object* v___x_492_; uint8_t v___x_493_; 
v___x_491_ = lean_unsigned_to_nat(2u);
v___x_492_ = lean_nat_mod(v_quotient_484_, v___x_491_);
v___x_493_ = lean_nat_dec_eq(v___x_492_, v___x_437_);
lean_dec(v___x_492_);
if (v___x_493_ == 0)
{
lean_object* v___x_494_; 
v___x_494_ = lean_nat_add(v_quotient_484_, v___x_448_);
lean_dec(v_quotient_484_);
v___y_372_ = v___x_437_;
v___y_373_ = v___x_440_;
v___y_374_ = v___x_494_;
goto v___jp_371_;
}
else
{
v___y_372_ = v___x_437_;
v___y_373_ = v___x_440_;
v___y_374_ = v_quotient_484_;
goto v___jp_371_;
}
}
else
{
lean_object* v___x_495_; 
v___x_495_ = lean_nat_add(v_quotient_484_, v___x_448_);
lean_dec(v_quotient_484_);
v___y_372_ = v___x_437_;
v___y_373_ = v___x_440_;
v___y_374_ = v___x_495_;
goto v___jp_371_;
}
}
else
{
lean_dec(v_half_488_);
lean_dec(v_remainder_486_);
v___y_372_ = v___x_437_;
v___y_373_ = v___x_440_;
v___y_374_ = v_quotient_484_;
goto v___jp_371_;
}
}
else
{
lean_dec(v___x_480_);
lean_dec(v_significand_442_);
v___y_372_ = v___x_437_;
v___y_373_ = v___x_440_;
v___y_374_ = v___x_437_;
goto v___jp_371_;
}
}
else
{
lean_dec(v___x_480_);
lean_dec(v_leading_445_);
v___y_372_ = v___x_437_;
v___y_373_ = v___x_440_;
v___y_374_ = v_significand_442_;
goto v___jp_371_;
}
}
}
}
else
{
lean_dec(v_exponent_443_);
lean_dec(v_significand_442_);
lean_dec_ref(v___x_440_);
if (v_negative_441_ == 0)
{
uint32_t v___x_496_; 
v___x_496_ = lean_uint32_once(&lp_competition_Submission_finishDigits___closed__11, &lp_competition_Submission_finishDigits___closed__11_once, _init_lp_competition_Submission_finishDigits___closed__11);
return v___x_496_;
}
else
{
uint32_t v___x_497_; 
v___x_497_ = lean_uint32_once(&lp_competition_Submission_finishDigits___closed__1, &lp_competition_Submission_finishDigits___closed__1_once, _init_lp_competition_Submission_finishDigits___closed__1);
return v___x_497_;
}
}
}
else
{
lean_dec(v___y_436_);
lean_dec(v_e_345_);
if (v_negZero_346_ == 0)
{
uint32_t v___x_498_; 
v___x_498_ = 0;
return v___x_498_;
}
else
{
uint32_t v___x_499_; 
v___x_499_ = 2147483648;
return v___x_499_;
}
}
}
v___jp_500_:
{
lean_object* v___x_503_; lean_object* v___x_504_; lean_object* v___x_505_; uint32_t v___x_506_; 
v___x_503_ = lean_unsigned_to_nat(8388607u);
v___x_504_ = lean_nat_land(v___y_501_, v___x_503_);
lean_dec(v___y_501_);
v___x_505_ = lean_nat_lor(v___y_502_, v___x_504_);
lean_dec(v___x_504_);
lean_dec(v___y_502_);
v___x_506_ = lean_uint32_of_nat(v___x_505_);
lean_dec(v___x_505_);
return v___x_506_;
}
v___jp_507_:
{
lean_object* v___x_510_; uint32_t v___x_511_; 
v___x_510_ = lean_nat_lor(v___y_509_, v___y_508_);
lean_dec(v___y_509_);
v___x_511_ = lean_uint32_of_nat(v___x_510_);
lean_dec(v___x_510_);
return v___x_511_;
}
v___jp_512_:
{
uint8_t v___x_516_; 
v___x_516_ = lean_nat_dec_eq(v___y_515_, v___y_514_);
if (v___x_516_ == 0)
{
lean_object* v___x_517_; uint8_t v___x_518_; 
v___x_517_ = lean_unsigned_to_nat(8388608u);
v___x_518_ = lean_nat_dec_eq(v___y_515_, v___x_517_);
if (v___x_518_ == 0)
{
if (v_neg_343_ == 0)
{
v___y_501_ = v___y_515_;
v___y_502_ = v___y_514_;
goto v___jp_500_;
}
else
{
lean_object* v___x_519_; 
lean_dec(v___y_514_);
v___x_519_ = lean_unsigned_to_nat(2147483648u);
v___y_501_ = v___y_515_;
v___y_502_ = v___x_519_;
goto v___jp_500_;
}
}
else
{
lean_dec(v___y_515_);
if (v_neg_343_ == 0)
{
v___y_508_ = v___x_517_;
v___y_509_ = v___y_514_;
goto v___jp_507_;
}
else
{
lean_object* v___x_520_; 
lean_dec(v___y_514_);
v___x_520_ = lean_unsigned_to_nat(2147483648u);
v___y_508_ = v___x_517_;
v___y_509_ = v___x_520_;
goto v___jp_507_;
}
}
}
else
{
lean_dec(v___y_515_);
if (v_neg_343_ == 0)
{
lean_object* v___x_521_; uint32_t v___x_522_; 
v___x_521_ = l_BitVec_ofNat(v___y_513_, v___y_514_);
lean_dec(v___y_514_);
v___x_522_ = lean_uint32_of_nat(v___x_521_);
lean_dec(v___x_521_);
return v___x_522_;
}
else
{
lean_object* v___x_523_; lean_object* v___x_524_; uint32_t v___x_525_; 
lean_dec(v___y_514_);
v___x_523_ = lean_unsigned_to_nat(2147483648u);
v___x_524_ = l_BitVec_ofNat(v___y_513_, v___x_523_);
v___x_525_ = lean_uint32_of_nat(v___x_524_);
lean_dec(v___x_524_);
return v___x_525_;
}
}
}
v___jp_526_:
{
lean_object* v___x_531_; lean_object* v___x_532_; lean_object* v___x_533_; lean_object* v___x_534_; lean_object* v___x_535_; lean_object* v___x_536_; lean_object* v___x_537_; uint32_t v___x_538_; 
v___x_531_ = lean_unsigned_to_nat(255u);
v___x_532_ = lean_nat_land(v___y_529_, v___x_531_);
lean_dec(v___y_529_);
v___x_533_ = lean_nat_shiftl(v___x_532_, v___y_528_);
lean_dec(v___x_532_);
v___x_534_ = lean_nat_lor(v___y_530_, v___x_533_);
lean_dec(v___x_533_);
lean_dec(v___y_530_);
v___x_535_ = lean_unsigned_to_nat(8388607u);
v___x_536_ = lean_nat_land(v___y_527_, v___x_535_);
lean_dec(v___y_527_);
v___x_537_ = lean_nat_lor(v___x_534_, v___x_536_);
lean_dec(v___x_536_);
lean_dec(v___x_534_);
v___x_538_ = lean_uint32_of_nat(v___x_537_);
lean_dec(v___x_537_);
return v___x_538_;
}
v___jp_539_:
{
lean_object* v___x_545_; lean_object* v___x_546_; lean_object* v___x_547_; lean_object* v___x_548_; 
v___x_545_ = lean_int_add(v___y_543_, v___y_541_);
lean_dec(v___y_543_);
v___x_546_ = l_Int_toNat(v___x_545_);
lean_dec(v___x_545_);
v___x_547_ = lean_unsigned_to_nat(8388608u);
v___x_548_ = lean_nat_sub(v___y_544_, v___x_547_);
lean_dec(v___y_544_);
if (v_neg_343_ == 0)
{
v___y_527_ = v___x_548_;
v___y_528_ = v___y_540_;
v___y_529_ = v___x_546_;
v___y_530_ = v___y_542_;
goto v___jp_526_;
}
else
{
lean_object* v___x_549_; 
lean_dec(v___y_542_);
v___x_549_ = lean_unsigned_to_nat(2147483648u);
v___y_527_ = v___x_548_;
v___y_528_ = v___y_540_;
v___y_529_ = v___x_546_;
v___y_530_ = v___x_549_;
goto v___jp_526_;
}
}
v___jp_550_:
{
uint8_t v___x_558_; 
v___x_558_ = lean_int_dec_lt(v___y_553_, v___y_557_);
if (v___x_558_ == 0)
{
if (v___y_551_ == 0)
{
v___y_540_ = v___y_552_;
v___y_541_ = v___y_553_;
v___y_542_ = v___y_556_;
v___y_543_ = v___y_557_;
v___y_544_ = v___y_554_;
goto v___jp_539_;
}
else
{
lean_object* v___x_559_; 
lean_dec(v___y_554_);
v___x_559_ = lean_unsigned_to_nat(8388608u);
v___y_540_ = v___y_552_;
v___y_541_ = v___y_553_;
v___y_542_ = v___y_556_;
v___y_543_ = v___y_557_;
v___y_544_ = v___x_559_;
goto v___jp_539_;
}
}
else
{
lean_dec(v___y_557_);
lean_dec(v___y_556_);
lean_dec(v___y_554_);
if (v_neg_343_ == 0)
{
lean_object* v___x_560_; lean_object* v___x_561_; uint32_t v___x_562_; 
v___x_560_ = lean_unsigned_to_nat(2139095040u);
v___x_561_ = l_BitVec_ofNat(v___y_555_, v___x_560_);
v___x_562_ = lean_uint32_of_nat(v___x_561_);
lean_dec(v___x_561_);
return v___x_562_;
}
else
{
lean_object* v___x_563_; lean_object* v___x_564_; lean_object* v___x_565_; lean_object* v___x_566_; lean_object* v___x_567_; uint32_t v___x_568_; 
v___x_563_ = lean_unsigned_to_nat(2147483648u);
v___x_564_ = l_BitVec_ofNat(v___y_555_, v___x_563_);
v___x_565_ = lean_unsigned_to_nat(2139095040u);
v___x_566_ = l_BitVec_ofNat(v___y_555_, v___x_565_);
v___x_567_ = lean_nat_lor(v___x_564_, v___x_566_);
lean_dec(v___x_566_);
lean_dec(v___x_564_);
v___x_568_ = lean_uint32_of_nat(v___x_567_);
lean_dec(v___x_567_);
return v___x_568_;
}
}
}
v___jp_569_:
{
lean_object* v___x_577_; uint8_t v_carry_578_; 
v___x_577_ = lean_unsigned_to_nat(16777216u);
v_carry_578_ = lean_nat_dec_eq(v___y_576_, v___x_577_);
if (v_carry_578_ == 0)
{
v___y_551_ = v_carry_578_;
v___y_552_ = v___y_571_;
v___y_553_ = v___y_572_;
v___y_554_ = v___y_576_;
v___y_555_ = v___y_575_;
v___y_556_ = v___y_574_;
v___y_557_ = v___y_570_;
goto v___jp_550_;
}
else
{
lean_object* v___x_579_; 
v___x_579_ = lean_int_add(v___y_570_, v___y_573_);
lean_dec(v___y_570_);
v___y_551_ = v_carry_578_;
v___y_552_ = v___y_571_;
v___y_553_ = v___y_572_;
v___y_554_ = v___y_576_;
v___y_555_ = v___y_575_;
v___y_556_ = v___y_574_;
v___y_557_ = v___x_579_;
goto v___jp_550_;
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_finishDigits___boxed(lean_object* v_neg_774_, lean_object* v_r_775_, lean_object* v_e_776_, lean_object* v_negZero_777_){
_start:
{
uint8_t v_neg_boxed_778_; uint8_t v_negZero_boxed_779_; uint32_t v_res_780_; lean_object* v_r_781_; 
v_neg_boxed_778_ = lean_unbox(v_neg_774_);
v_negZero_boxed_779_ = lean_unbox(v_negZero_777_);
v_res_780_ = lp_competition_Submission_finishDigits(v_neg_boxed_778_, v_r_775_, v_e_776_, v_negZero_boxed_779_);
lean_dec_ref(v_r_775_);
v_r_781_ = lean_box_uint32(v_res_780_);
return v_r_781_;
}
}
LEAN_EXPORT lean_object* lp_competition___private_Submission_0__Submission_finishDigits_match__1_splitter___redArg(lean_object* v_x_782_, lean_object* v_h__1_783_, lean_object* v_h__2_784_, lean_object* v_h__3_785_){
_start:
{
if (lean_obj_tag(v_x_782_) == 0)
{
lean_object* v___x_786_; lean_object* v___x_787_; 
lean_dec(v_h__3_785_);
lean_dec(v_h__2_784_);
v___x_786_ = lean_box(0);
v___x_787_ = lean_apply_1(v_h__1_783_, v___x_786_);
return v___x_787_;
}
else
{
lean_object* v_val_788_; lean_object* v_zero_789_; uint8_t v_isZero_790_; 
lean_dec(v_h__1_783_);
v_val_788_ = lean_ctor_get(v_x_782_, 0);
v_zero_789_ = lean_unsigned_to_nat(0u);
v_isZero_790_ = lean_nat_dec_eq(v_val_788_, v_zero_789_);
if (v_isZero_790_ == 1)
{
lean_object* v___x_791_; lean_object* v___x_792_; 
lean_dec(v_h__3_785_);
v___x_791_ = lean_box(0);
v___x_792_ = lean_apply_1(v_h__2_784_, v___x_791_);
return v___x_792_;
}
else
{
lean_object* v_one_793_; lean_object* v_n_794_; lean_object* v___x_795_; 
lean_dec(v_h__2_784_);
v_one_793_ = lean_unsigned_to_nat(1u);
v_n_794_ = lean_nat_sub(v_val_788_, v_one_793_);
v___x_795_ = lean_apply_1(v_h__3_785_, v_n_794_);
return v___x_795_;
}
}
}
}
LEAN_EXPORT lean_object* lp_competition___private_Submission_0__Submission_finishDigits_match__1_splitter___redArg___boxed(lean_object* v_x_796_, lean_object* v_h__1_797_, lean_object* v_h__2_798_, lean_object* v_h__3_799_){
_start:
{
lean_object* v_res_800_; 
v_res_800_ = lp_competition___private_Submission_0__Submission_finishDigits_match__1_splitter___redArg(v_x_796_, v_h__1_797_, v_h__2_798_, v_h__3_799_);
lean_dec(v_x_796_);
return v_res_800_;
}
}
LEAN_EXPORT lean_object* lp_competition___private_Submission_0__Submission_finishDigits_match__1_splitter(lean_object* v_motive_801_, lean_object* v_x_802_, lean_object* v_h__1_803_, lean_object* v_h__2_804_, lean_object* v_h__3_805_){
_start:
{
if (lean_obj_tag(v_x_802_) == 0)
{
lean_object* v___x_806_; lean_object* v___x_807_; 
lean_dec(v_h__3_805_);
lean_dec(v_h__2_804_);
v___x_806_ = lean_box(0);
v___x_807_ = lean_apply_1(v_h__1_803_, v___x_806_);
return v___x_807_;
}
else
{
lean_object* v_val_808_; lean_object* v_zero_809_; uint8_t v_isZero_810_; 
lean_dec(v_h__1_803_);
v_val_808_ = lean_ctor_get(v_x_802_, 0);
v_zero_809_ = lean_unsigned_to_nat(0u);
v_isZero_810_ = lean_nat_dec_eq(v_val_808_, v_zero_809_);
if (v_isZero_810_ == 1)
{
lean_object* v___x_811_; lean_object* v___x_812_; 
lean_dec(v_h__3_805_);
v___x_811_ = lean_box(0);
v___x_812_ = lean_apply_1(v_h__2_804_, v___x_811_);
return v___x_812_;
}
else
{
lean_object* v_one_813_; lean_object* v_n_814_; lean_object* v___x_815_; 
lean_dec(v_h__2_804_);
v_one_813_ = lean_unsigned_to_nat(1u);
v_n_814_ = lean_nat_sub(v_val_808_, v_one_813_);
v___x_815_ = lean_apply_1(v_h__3_805_, v_n_814_);
return v___x_815_;
}
}
}
}
LEAN_EXPORT lean_object* lp_competition___private_Submission_0__Submission_finishDigits_match__1_splitter___boxed(lean_object* v_motive_816_, lean_object* v_x_817_, lean_object* v_h__1_818_, lean_object* v_h__2_819_, lean_object* v_h__3_820_){
_start:
{
lean_object* v_res_821_; 
v_res_821_ = lp_competition___private_Submission_0__Submission_finishDigits_match__1_splitter(v_motive_816_, v_x_817_, v_h__1_818_, v_h__2_819_, v_h__3_820_);
lean_dec(v_x_817_);
return v_res_821_;
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_highLimb(lean_object* v_pos_822_, lean_object* v_neg_823_, lean_object* v_x_824_){
_start:
{
lean_object* v_zero_825_; uint8_t v_isZero_826_; 
v_zero_825_ = lean_unsigned_to_nat(0u);
v_isZero_826_ = lean_nat_dec_eq(v_x_824_, v_zero_825_);
if (v_isZero_826_ == 1)
{
lean_dec(v_x_824_);
return v_zero_825_;
}
else
{
lean_object* v_one_827_; lean_object* v_n_828_; lean_object* v___x_831_; uint8_t v___x_832_; 
v_one_827_ = lean_unsigned_to_nat(1u);
v_n_828_ = lean_nat_sub(v_x_824_, v_one_827_);
lean_dec(v_x_824_);
v___x_831_ = lean_array_get_borrowed(v_zero_825_, v_pos_822_, v_n_828_);
v___x_832_ = lean_nat_dec_eq(v___x_831_, v_zero_825_);
if (v___x_832_ == 0)
{
goto v___jp_829_;
}
else
{
lean_object* v___x_833_; uint8_t v___x_834_; 
v___x_833_ = lean_array_get_borrowed(v_zero_825_, v_neg_823_, v_n_828_);
v___x_834_ = lean_nat_dec_eq(v___x_833_, v_zero_825_);
if (v___x_834_ == 0)
{
goto v___jp_829_;
}
else
{
v_x_824_ = v_n_828_;
goto _start;
}
}
v___jp_829_:
{
lean_object* v___x_830_; 
v___x_830_ = lean_nat_add(v_n_828_, v_one_827_);
lean_dec(v_n_828_);
return v___x_830_;
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_highLimb___boxed(lean_object* v_pos_836_, lean_object* v_neg_837_, lean_object* v_x_838_){
_start:
{
lean_object* v_res_839_; 
v_res_839_ = lp_competition_Submission_highLimb(v_pos_836_, v_neg_837_, v_x_838_);
lean_dec_ref(v_neg_837_);
lean_dec_ref(v_pos_836_);
return v_res_839_;
}
}
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_foldrMUnsafe_fold___at___00Submission_finishFast_spec__0(lean_object* v_as_840_, size_t v_i_841_, size_t v_stop_842_, lean_object* v_b_843_){
_start:
{
uint8_t v___x_844_; 
v___x_844_ = lean_usize_dec_eq(v_i_841_, v_stop_842_);
if (v___x_844_ == 0)
{
size_t v___x_845_; size_t v___x_846_; lean_object* v___x_847_; lean_object* v___x_848_; lean_object* v___x_849_; lean_object* v___x_850_; 
v___x_845_ = ((size_t)1ULL);
v___x_846_ = lean_usize_sub(v_i_841_, v___x_845_);
v___x_847_ = lean_array_uget_borrowed(v_as_840_, v___x_846_);
v___x_848_ = lean_unsigned_to_nat(32u);
v___x_849_ = lean_nat_shiftl(v_b_843_, v___x_848_);
lean_dec(v_b_843_);
v___x_850_ = lean_nat_add(v___x_849_, v___x_847_);
lean_dec(v___x_849_);
v_i_841_ = v___x_846_;
v_b_843_ = v___x_850_;
goto _start;
}
else
{
return v_b_843_;
}
}
}
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_foldrMUnsafe_fold___at___00Submission_finishFast_spec__0___boxed(lean_object* v_as_852_, lean_object* v_i_853_, lean_object* v_stop_854_, lean_object* v_b_855_){
_start:
{
size_t v_i_boxed_856_; size_t v_stop_boxed_857_; lean_object* v_res_858_; 
v_i_boxed_856_ = lean_unbox_usize(v_i_853_);
lean_dec(v_i_853_);
v_stop_boxed_857_ = lean_unbox_usize(v_stop_854_);
lean_dec(v_stop_854_);
v_res_858_ = lp_competition___private_Init_Data_Array_Basic_0__Array_foldrMUnsafe_fold___at___00Submission_finishFast_spec__0(v_as_852_, v_i_boxed_856_, v_stop_boxed_857_, v_b_855_);
lean_dec_ref(v_as_852_);
return v_res_858_;
}
}
LEAN_EXPORT uint32_t lp_competition_Submission_finishFast(lean_object* v_pos_859_, lean_object* v_neg_860_, lean_object* v_e_861_, uint8_t v_negZero_862_){
_start:
{
lean_object* v___y_864_; lean_object* v___y_865_; lean_object* v___y_871_; lean_object* v___y_872_; lean_object* v___y_876_; lean_object* v___y_877_; lean_object* v___y_878_; lean_object* v___y_879_; lean_object* v___y_894_; lean_object* v___y_895_; lean_object* v___y_896_; lean_object* v___y_897_; lean_object* v___y_907_; lean_object* v___y_908_; lean_object* v___y_909_; uint8_t v___y_910_; lean_object* v___y_911_; lean_object* v___y_912_; uint8_t v___y_919_; lean_object* v___y_920_; lean_object* v___y_921_; lean_object* v___y_922_; lean_object* v___y_923_; uint8_t v___y_924_; lean_object* v___y_925_; lean_object* v___y_926_; lean_object* v___y_939_; lean_object* v___y_940_; lean_object* v___y_941_; lean_object* v___y_942_; lean_object* v___y_943_; uint8_t v___y_944_; lean_object* v___y_945_; lean_object* v___y_946_; lean_object* v___y_951_; lean_object* v___y_952_; lean_object* v___y_953_; lean_object* v___y_954_; lean_object* v___y_1026_; lean_object* v___y_1027_; lean_object* v___y_1028_; lean_object* v___x_1047_; lean_object* v___x_1048_; lean_object* v_lo_1049_; lean_object* v___y_1051_; lean_object* v___y_1052_; lean_object* v___y_1053_; lean_object* v___y_1066_; lean_object* v___x_1088_; uint8_t v___x_1089_; 
v___x_1047_ = lean_array_get_size(v_pos_859_);
v___x_1048_ = lean_unsigned_to_nat(0u);
v_lo_1049_ = lp_competition_ExactRuntime_lowLimb(v_pos_859_, v_neg_860_, v___x_1047_, v___x_1048_);
v___x_1088_ = lean_array_get_size(v_neg_860_);
v___x_1089_ = lean_nat_dec_le(v___x_1047_, v___x_1088_);
if (v___x_1089_ == 0)
{
v___y_1066_ = v___x_1047_;
goto v___jp_1065_;
}
else
{
v___y_1066_ = v___x_1088_;
goto v___jp_1065_;
}
v___jp_863_:
{
lean_object* v___x_866_; lean_object* v___x_867_; lean_object* v___x_868_; uint32_t v___x_869_; 
v___x_866_ = lean_unsigned_to_nat(8388607u);
v___x_867_ = lean_nat_land(v___y_864_, v___x_866_);
lean_dec(v___y_864_);
v___x_868_ = lean_nat_lor(v___y_865_, v___x_867_);
lean_dec(v___x_867_);
lean_dec(v___y_865_);
v___x_869_ = lean_uint32_of_nat(v___x_868_);
lean_dec(v___x_868_);
return v___x_869_;
}
v___jp_870_:
{
lean_object* v___x_873_; uint32_t v___x_874_; 
v___x_873_ = lean_nat_lor(v___y_872_, v___y_871_);
lean_dec(v___y_872_);
v___x_874_ = lean_uint32_of_nat(v___x_873_);
lean_dec(v___x_873_);
return v___x_874_;
}
v___jp_875_:
{
uint8_t v___x_880_; 
v___x_880_ = lean_nat_dec_eq(v___y_879_, v___y_878_);
if (v___x_880_ == 0)
{
lean_object* v___x_881_; uint8_t v___x_882_; 
v___x_881_ = lean_unsigned_to_nat(8388608u);
v___x_882_ = lean_nat_dec_eq(v___y_879_, v___x_881_);
if (v___x_882_ == 0)
{
uint8_t v_negative_883_; 
v_negative_883_ = lean_ctor_get_uint8(v___y_876_, sizeof(void*)*2);
lean_dec_ref(v___y_876_);
if (v_negative_883_ == 0)
{
v___y_864_ = v___y_879_;
v___y_865_ = v___y_878_;
goto v___jp_863_;
}
else
{
lean_object* v___x_884_; 
lean_dec(v___y_878_);
v___x_884_ = lean_unsigned_to_nat(2147483648u);
v___y_864_ = v___y_879_;
v___y_865_ = v___x_884_;
goto v___jp_863_;
}
}
else
{
uint8_t v_negative_885_; 
lean_dec(v___y_879_);
v_negative_885_ = lean_ctor_get_uint8(v___y_876_, sizeof(void*)*2);
lean_dec_ref(v___y_876_);
if (v_negative_885_ == 0)
{
v___y_871_ = v___x_881_;
v___y_872_ = v___y_878_;
goto v___jp_870_;
}
else
{
lean_object* v___x_886_; 
lean_dec(v___y_878_);
v___x_886_ = lean_unsigned_to_nat(2147483648u);
v___y_871_ = v___x_881_;
v___y_872_ = v___x_886_;
goto v___jp_870_;
}
}
}
else
{
uint8_t v_negative_887_; 
lean_dec(v___y_879_);
v_negative_887_ = lean_ctor_get_uint8(v___y_876_, sizeof(void*)*2);
lean_dec_ref(v___y_876_);
if (v_negative_887_ == 0)
{
lean_object* v___x_888_; uint32_t v___x_889_; 
v___x_888_ = l_BitVec_ofNat(v___y_877_, v___y_878_);
lean_dec(v___y_878_);
v___x_889_ = lean_uint32_of_nat(v___x_888_);
lean_dec(v___x_888_);
return v___x_889_;
}
else
{
lean_object* v___x_890_; lean_object* v___x_891_; uint32_t v___x_892_; 
lean_dec(v___y_878_);
v___x_890_ = lean_unsigned_to_nat(2147483648u);
v___x_891_ = l_BitVec_ofNat(v___y_877_, v___x_890_);
v___x_892_ = lean_uint32_of_nat(v___x_891_);
lean_dec(v___x_891_);
return v___x_892_;
}
}
}
v___jp_893_:
{
lean_object* v___x_898_; lean_object* v___x_899_; lean_object* v___x_900_; lean_object* v___x_901_; lean_object* v___x_902_; lean_object* v___x_903_; lean_object* v___x_904_; uint32_t v___x_905_; 
v___x_898_ = lean_unsigned_to_nat(255u);
v___x_899_ = lean_nat_land(v___y_895_, v___x_898_);
lean_dec(v___y_895_);
v___x_900_ = lean_nat_shiftl(v___x_899_, v___y_896_);
lean_dec(v___x_899_);
v___x_901_ = lean_nat_lor(v___y_897_, v___x_900_);
lean_dec(v___x_900_);
lean_dec(v___y_897_);
v___x_902_ = lean_unsigned_to_nat(8388607u);
v___x_903_ = lean_nat_land(v___y_894_, v___x_902_);
lean_dec(v___y_894_);
v___x_904_ = lean_nat_lor(v___x_901_, v___x_903_);
lean_dec(v___x_903_);
lean_dec(v___x_901_);
v___x_905_ = lean_uint32_of_nat(v___x_904_);
lean_dec(v___x_904_);
return v___x_905_;
}
v___jp_906_:
{
lean_object* v___x_913_; lean_object* v___x_914_; lean_object* v___x_915_; lean_object* v___x_916_; 
v___x_913_ = lean_int_add(v___y_907_, v___y_909_);
lean_dec(v___y_907_);
v___x_914_ = l_Int_toNat(v___x_913_);
lean_dec(v___x_913_);
v___x_915_ = lean_unsigned_to_nat(8388608u);
v___x_916_ = lean_nat_sub(v___y_912_, v___x_915_);
lean_dec(v___y_912_);
if (v___y_910_ == 0)
{
v___y_894_ = v___x_916_;
v___y_895_ = v___x_914_;
v___y_896_ = v___y_908_;
v___y_897_ = v___y_911_;
goto v___jp_893_;
}
else
{
lean_object* v___x_917_; 
lean_dec(v___y_911_);
v___x_917_ = lean_unsigned_to_nat(2147483648u);
v___y_894_ = v___x_916_;
v___y_895_ = v___x_914_;
v___y_896_ = v___y_908_;
v___y_897_ = v___x_917_;
goto v___jp_893_;
}
}
v___jp_918_:
{
uint8_t v___x_927_; 
v___x_927_ = lean_int_dec_lt(v___y_922_, v___y_926_);
if (v___x_927_ == 0)
{
if (v___y_919_ == 0)
{
v___y_907_ = v___y_926_;
v___y_908_ = v___y_923_;
v___y_909_ = v___y_922_;
v___y_910_ = v___y_924_;
v___y_911_ = v___y_925_;
v___y_912_ = v___y_920_;
goto v___jp_906_;
}
else
{
lean_object* v___x_928_; 
lean_dec(v___y_920_);
v___x_928_ = lean_unsigned_to_nat(8388608u);
v___y_907_ = v___y_926_;
v___y_908_ = v___y_923_;
v___y_909_ = v___y_922_;
v___y_910_ = v___y_924_;
v___y_911_ = v___y_925_;
v___y_912_ = v___x_928_;
goto v___jp_906_;
}
}
else
{
lean_dec(v___y_926_);
lean_dec(v___y_925_);
lean_dec(v___y_920_);
if (v___y_924_ == 0)
{
lean_object* v___x_929_; lean_object* v___x_930_; uint32_t v___x_931_; 
v___x_929_ = lean_unsigned_to_nat(2139095040u);
v___x_930_ = l_BitVec_ofNat(v___y_921_, v___x_929_);
v___x_931_ = lean_uint32_of_nat(v___x_930_);
lean_dec(v___x_930_);
return v___x_931_;
}
else
{
lean_object* v___x_932_; lean_object* v___x_933_; lean_object* v___x_934_; lean_object* v___x_935_; lean_object* v___x_936_; uint32_t v___x_937_; 
v___x_932_ = lean_unsigned_to_nat(2147483648u);
v___x_933_ = l_BitVec_ofNat(v___y_921_, v___x_932_);
v___x_934_ = lean_unsigned_to_nat(2139095040u);
v___x_935_ = l_BitVec_ofNat(v___y_921_, v___x_934_);
v___x_936_ = lean_nat_lor(v___x_933_, v___x_935_);
lean_dec(v___x_935_);
lean_dec(v___x_933_);
v___x_937_ = lean_uint32_of_nat(v___x_936_);
lean_dec(v___x_936_);
return v___x_937_;
}
}
}
v___jp_938_:
{
lean_object* v___x_947_; uint8_t v_carry_948_; 
v___x_947_ = lean_unsigned_to_nat(16777216u);
v_carry_948_ = lean_nat_dec_eq(v___y_946_, v___x_947_);
if (v_carry_948_ == 0)
{
v___y_919_ = v_carry_948_;
v___y_920_ = v___y_946_;
v___y_921_ = v___y_941_;
v___y_922_ = v___y_943_;
v___y_923_ = v___y_942_;
v___y_924_ = v___y_944_;
v___y_925_ = v___y_945_;
v___y_926_ = v___y_940_;
goto v___jp_918_;
}
else
{
lean_object* v___x_949_; 
v___x_949_ = lean_int_add(v___y_940_, v___y_939_);
lean_dec(v___y_940_);
v___y_919_ = v_carry_948_;
v___y_920_ = v___y_946_;
v___y_921_ = v___y_941_;
v___y_922_ = v___y_943_;
v___y_923_ = v___y_942_;
v___y_924_ = v___y_944_;
v___y_925_ = v___y_945_;
v___y_926_ = v___x_949_;
goto v___jp_918_;
}
}
v___jp_950_:
{
lean_object* v___x_955_; lean_object* v___x_956_; lean_object* v___x_957_; uint8_t v___x_958_; 
v___x_955_ = lean_nat_to_int(v___y_954_);
v___x_956_ = lean_int_sub(v___y_951_, v___x_955_);
lean_dec(v___x_955_);
lean_dec(v___y_951_);
lean_inc(v___y_953_);
v___x_957_ = lean_nat_to_int(v___y_953_);
v___x_958_ = lean_int_dec_eq(v___x_956_, v___x_957_);
lean_dec(v___x_957_);
if (v___x_958_ == 0)
{
lean_object* v___x_959_; lean_object* v___x_960_; lean_object* v___x_961_; lean_object* v___x_962_; lean_object* v___x_963_; uint8_t v_negative_964_; lean_object* v_significand_965_; lean_object* v_exponent_966_; uint8_t v___x_967_; 
v___x_959_ = lean_unsigned_to_nat(32u);
v___x_960_ = lean_nat_mul(v___x_959_, v___y_952_);
lean_dec(v___y_952_);
v___x_961_ = lean_nat_to_int(v___x_960_);
v___x_962_ = lean_int_add(v_e_861_, v___x_961_);
lean_dec(v___x_961_);
v___x_963_ = lp_competition_ExactRuntime_ofIntDyadic(v___x_956_, v___x_962_);
lean_dec(v___x_956_);
v_negative_964_ = lean_ctor_get_uint8(v___x_963_, sizeof(void*)*2);
v_significand_965_ = lean_ctor_get(v___x_963_, 0);
lean_inc(v_significand_965_);
v_exponent_966_ = lean_ctor_get(v___x_963_, 1);
lean_inc(v_exponent_966_);
v___x_967_ = lean_nat_dec_eq(v_significand_965_, v___y_953_);
if (v___x_967_ == 0)
{
lean_object* v_leading_968_; lean_object* v___x_969_; lean_object* v_totalExponent_970_; lean_object* v___x_971_; lean_object* v___x_972_; lean_object* v___x_973_; lean_object* v___x_974_; uint8_t v___x_975_; 
v_leading_968_ = lean_nat_log2(v_significand_965_);
lean_inc(v_leading_968_);
v___x_969_ = lean_nat_to_int(v_leading_968_);
v_totalExponent_970_ = lean_int_add(v___x_969_, v_exponent_966_);
lean_dec(v___x_969_);
v___x_971_ = lean_unsigned_to_nat(1u);
v___x_972_ = lean_obj_once(&lp_competition_Submission_finishDigits___closed__6, &lp_competition_Submission_finishDigits___closed__6_once, _init_lp_competition_Submission_finishDigits___closed__6);
v___x_973_ = lean_obj_once(&lp_competition_Submission_finishDigits___closed__7, &lp_competition_Submission_finishDigits___closed__7_once, _init_lp_competition_Submission_finishDigits___closed__7);
v___x_974_ = lean_obj_once(&lp_competition_Submission_finishDigits___closed__8, &lp_competition_Submission_finishDigits___closed__8_once, _init_lp_competition_Submission_finishDigits___closed__8);
v___x_975_ = lean_int_dec_lt(v_totalExponent_970_, v___x_974_);
if (v___x_975_ == 0)
{
lean_object* v___x_976_; uint8_t v___x_977_; 
lean_dec(v_exponent_966_);
lean_dec_ref(v___x_963_);
v___x_976_ = lean_unsigned_to_nat(23u);
v___x_977_ = lean_nat_dec_le(v___x_976_, v_leading_968_);
if (v___x_977_ == 0)
{
lean_object* v___x_978_; lean_object* v___x_979_; 
v___x_978_ = lean_nat_sub(v___x_976_, v_leading_968_);
lean_dec(v_leading_968_);
v___x_979_ = lean_nat_shiftl(v_significand_965_, v___x_978_);
lean_dec(v___x_978_);
lean_dec(v_significand_965_);
v___y_939_ = v___x_972_;
v___y_940_ = v_totalExponent_970_;
v___y_941_ = v___x_959_;
v___y_942_ = v___x_976_;
v___y_943_ = v___x_973_;
v___y_944_ = v_negative_964_;
v___y_945_ = v___y_953_;
v___y_946_ = v___x_979_;
goto v___jp_938_;
}
else
{
lean_object* v___x_980_; uint8_t v___x_981_; 
v___x_980_ = lean_nat_sub(v_leading_968_, v___x_976_);
v___x_981_ = lean_nat_dec_eq(v___x_980_, v___y_953_);
if (v___x_981_ == 0)
{
lean_object* v___x_982_; uint8_t v___x_983_; 
v___x_982_ = lean_nat_add(v_leading_968_, v___x_971_);
lean_dec(v_leading_968_);
v___x_983_ = lean_nat_dec_lt(v___x_982_, v___x_980_);
lean_dec(v___x_982_);
if (v___x_983_ == 0)
{
lean_object* v_quotient_984_; lean_object* v___x_985_; lean_object* v_remainder_986_; lean_object* v___x_987_; lean_object* v_half_988_; uint8_t v___x_989_; 
v_quotient_984_ = lean_nat_shiftr(v_significand_965_, v___x_980_);
v___x_985_ = lean_nat_shiftl(v_quotient_984_, v___x_980_);
v_remainder_986_ = lean_nat_sub(v_significand_965_, v___x_985_);
lean_dec(v___x_985_);
lean_dec(v_significand_965_);
v___x_987_ = lean_nat_sub(v___x_980_, v___x_971_);
lean_dec(v___x_980_);
v_half_988_ = lean_nat_shiftl(v___x_971_, v___x_987_);
lean_dec(v___x_987_);
v___x_989_ = lean_nat_dec_lt(v_remainder_986_, v_half_988_);
if (v___x_989_ == 0)
{
uint8_t v___x_990_; 
v___x_990_ = lean_nat_dec_lt(v_half_988_, v_remainder_986_);
lean_dec(v_remainder_986_);
lean_dec(v_half_988_);
if (v___x_990_ == 0)
{
lean_object* v___x_991_; lean_object* v___x_992_; uint8_t v___x_993_; 
v___x_991_ = lean_unsigned_to_nat(2u);
v___x_992_ = lean_nat_mod(v_quotient_984_, v___x_991_);
v___x_993_ = lean_nat_dec_eq(v___x_992_, v___y_953_);
lean_dec(v___x_992_);
if (v___x_993_ == 0)
{
lean_object* v___x_994_; 
v___x_994_ = lean_nat_add(v_quotient_984_, v___x_971_);
lean_dec(v_quotient_984_);
v___y_939_ = v___x_972_;
v___y_940_ = v_totalExponent_970_;
v___y_941_ = v___x_959_;
v___y_942_ = v___x_976_;
v___y_943_ = v___x_973_;
v___y_944_ = v_negative_964_;
v___y_945_ = v___y_953_;
v___y_946_ = v___x_994_;
goto v___jp_938_;
}
else
{
v___y_939_ = v___x_972_;
v___y_940_ = v_totalExponent_970_;
v___y_941_ = v___x_959_;
v___y_942_ = v___x_976_;
v___y_943_ = v___x_973_;
v___y_944_ = v_negative_964_;
v___y_945_ = v___y_953_;
v___y_946_ = v_quotient_984_;
goto v___jp_938_;
}
}
else
{
lean_object* v___x_995_; 
v___x_995_ = lean_nat_add(v_quotient_984_, v___x_971_);
lean_dec(v_quotient_984_);
v___y_939_ = v___x_972_;
v___y_940_ = v_totalExponent_970_;
v___y_941_ = v___x_959_;
v___y_942_ = v___x_976_;
v___y_943_ = v___x_973_;
v___y_944_ = v_negative_964_;
v___y_945_ = v___y_953_;
v___y_946_ = v___x_995_;
goto v___jp_938_;
}
}
else
{
lean_dec(v_half_988_);
lean_dec(v_remainder_986_);
v___y_939_ = v___x_972_;
v___y_940_ = v_totalExponent_970_;
v___y_941_ = v___x_959_;
v___y_942_ = v___x_976_;
v___y_943_ = v___x_973_;
v___y_944_ = v_negative_964_;
v___y_945_ = v___y_953_;
v___y_946_ = v_quotient_984_;
goto v___jp_938_;
}
}
else
{
lean_dec(v___x_980_);
lean_dec(v_significand_965_);
lean_inc(v___y_953_);
v___y_939_ = v___x_972_;
v___y_940_ = v_totalExponent_970_;
v___y_941_ = v___x_959_;
v___y_942_ = v___x_976_;
v___y_943_ = v___x_973_;
v___y_944_ = v_negative_964_;
v___y_945_ = v___y_953_;
v___y_946_ = v___y_953_;
goto v___jp_938_;
}
}
else
{
lean_dec(v___x_980_);
lean_dec(v_leading_968_);
v___y_939_ = v___x_972_;
v___y_940_ = v_totalExponent_970_;
v___y_941_ = v___x_959_;
v___y_942_ = v___x_976_;
v___y_943_ = v___x_973_;
v___y_944_ = v_negative_964_;
v___y_945_ = v___y_953_;
v___y_946_ = v_significand_965_;
goto v___jp_938_;
}
}
}
else
{
lean_object* v___x_996_; lean_object* v___x_997_; lean_object* v_intZero_998_; uint8_t v_isNeg_999_; 
lean_dec(v_totalExponent_970_);
v___x_996_ = lean_obj_once(&lp_competition_Submission_finishDigits___closed__9, &lp_competition_Submission_finishDigits___closed__9_once, _init_lp_competition_Submission_finishDigits___closed__9);
v___x_997_ = lean_int_add(v_exponent_966_, v___x_996_);
lean_dec(v_exponent_966_);
v_intZero_998_ = lean_obj_once(&lp_competition___private_Submission_0__FloatLib_Floats_Formats_BinaryInterchange_Model_roundDyadicGeneral_match__1_splitter___redArg___closed__0, &lp_competition___private_Submission_0__FloatLib_Floats_Formats_BinaryInterchange_Model_roundDyadicGeneral_match__1_splitter___redArg___closed__0_once, _init_lp_competition___private_Submission_0__FloatLib_Floats_Formats_BinaryInterchange_Model_roundDyadicGeneral_match__1_splitter___redArg___closed__0);
v_isNeg_999_ = lean_int_dec_lt(v___x_997_, v_intZero_998_);
if (v_isNeg_999_ == 0)
{
lean_object* v_a_1000_; lean_object* v___x_1001_; 
lean_dec(v_leading_968_);
v_a_1000_ = lean_nat_abs(v___x_997_);
lean_dec(v___x_997_);
v___x_1001_ = lean_nat_shiftl(v_significand_965_, v_a_1000_);
lean_dec(v_a_1000_);
lean_dec(v_significand_965_);
v___y_876_ = v___x_963_;
v___y_877_ = v___x_959_;
v___y_878_ = v___y_953_;
v___y_879_ = v___x_1001_;
goto v___jp_875_;
}
else
{
lean_object* v_abs_1002_; lean_object* v_a_1003_; lean_object* v___x_1004_; uint8_t v___x_1005_; 
v_abs_1002_ = lean_nat_abs(v___x_997_);
lean_dec(v___x_997_);
v_a_1003_ = lean_nat_sub(v_abs_1002_, v___x_971_);
lean_dec(v_abs_1002_);
v___x_1004_ = lean_nat_add(v_a_1003_, v___x_971_);
lean_dec(v_a_1003_);
v___x_1005_ = lean_nat_dec_eq(v___x_1004_, v___y_953_);
if (v___x_1005_ == 0)
{
lean_object* v___x_1006_; uint8_t v___x_1007_; 
v___x_1006_ = lean_nat_add(v_leading_968_, v___x_971_);
lean_dec(v_leading_968_);
v___x_1007_ = lean_nat_dec_lt(v___x_1006_, v___x_1004_);
lean_dec(v___x_1006_);
if (v___x_1007_ == 0)
{
lean_object* v_quotient_1008_; lean_object* v___x_1009_; lean_object* v_remainder_1010_; lean_object* v___x_1011_; lean_object* v_half_1012_; uint8_t v___x_1013_; 
v_quotient_1008_ = lean_nat_shiftr(v_significand_965_, v___x_1004_);
v___x_1009_ = lean_nat_shiftl(v_quotient_1008_, v___x_1004_);
v_remainder_1010_ = lean_nat_sub(v_significand_965_, v___x_1009_);
lean_dec(v___x_1009_);
lean_dec(v_significand_965_);
v___x_1011_ = lean_nat_sub(v___x_1004_, v___x_971_);
lean_dec(v___x_1004_);
v_half_1012_ = lean_nat_shiftl(v___x_971_, v___x_1011_);
lean_dec(v___x_1011_);
v___x_1013_ = lean_nat_dec_lt(v_remainder_1010_, v_half_1012_);
if (v___x_1013_ == 0)
{
uint8_t v___x_1014_; 
v___x_1014_ = lean_nat_dec_lt(v_half_1012_, v_remainder_1010_);
lean_dec(v_remainder_1010_);
lean_dec(v_half_1012_);
if (v___x_1014_ == 0)
{
lean_object* v___x_1015_; lean_object* v___x_1016_; uint8_t v___x_1017_; 
v___x_1015_ = lean_unsigned_to_nat(2u);
v___x_1016_ = lean_nat_mod(v_quotient_1008_, v___x_1015_);
v___x_1017_ = lean_nat_dec_eq(v___x_1016_, v___y_953_);
lean_dec(v___x_1016_);
if (v___x_1017_ == 0)
{
lean_object* v___x_1018_; 
v___x_1018_ = lean_nat_add(v_quotient_1008_, v___x_971_);
lean_dec(v_quotient_1008_);
v___y_876_ = v___x_963_;
v___y_877_ = v___x_959_;
v___y_878_ = v___y_953_;
v___y_879_ = v___x_1018_;
goto v___jp_875_;
}
else
{
v___y_876_ = v___x_963_;
v___y_877_ = v___x_959_;
v___y_878_ = v___y_953_;
v___y_879_ = v_quotient_1008_;
goto v___jp_875_;
}
}
else
{
lean_object* v___x_1019_; 
v___x_1019_ = lean_nat_add(v_quotient_1008_, v___x_971_);
lean_dec(v_quotient_1008_);
v___y_876_ = v___x_963_;
v___y_877_ = v___x_959_;
v___y_878_ = v___y_953_;
v___y_879_ = v___x_1019_;
goto v___jp_875_;
}
}
else
{
lean_dec(v_half_1012_);
lean_dec(v_remainder_1010_);
v___y_876_ = v___x_963_;
v___y_877_ = v___x_959_;
v___y_878_ = v___y_953_;
v___y_879_ = v_quotient_1008_;
goto v___jp_875_;
}
}
else
{
lean_dec(v___x_1004_);
lean_dec(v_significand_965_);
lean_inc(v___y_953_);
v___y_876_ = v___x_963_;
v___y_877_ = v___x_959_;
v___y_878_ = v___y_953_;
v___y_879_ = v___y_953_;
goto v___jp_875_;
}
}
else
{
lean_dec(v___x_1004_);
lean_dec(v_leading_968_);
v___y_876_ = v___x_963_;
v___y_877_ = v___x_959_;
v___y_878_ = v___y_953_;
v___y_879_ = v_significand_965_;
goto v___jp_875_;
}
}
}
}
else
{
lean_dec(v_exponent_966_);
lean_dec(v_significand_965_);
lean_dec_ref(v___x_963_);
if (v_negative_964_ == 0)
{
lean_object* v___x_1020_; uint32_t v___x_1021_; 
v___x_1020_ = l_BitVec_ofNat(v___x_959_, v___y_953_);
lean_dec(v___y_953_);
v___x_1021_ = lean_uint32_of_nat(v___x_1020_);
lean_dec(v___x_1020_);
return v___x_1021_;
}
else
{
uint32_t v___x_1022_; 
lean_dec(v___y_953_);
v___x_1022_ = lean_uint32_once(&lp_competition_Submission_finishDigits___closed__1, &lp_competition_Submission_finishDigits___closed__1_once, _init_lp_competition_Submission_finishDigits___closed__1);
return v___x_1022_;
}
}
}
else
{
lean_dec(v___x_956_);
lean_dec(v___y_953_);
lean_dec(v___y_952_);
if (v_negZero_862_ == 0)
{
uint32_t v___x_1023_; 
v___x_1023_ = 0;
return v___x_1023_;
}
else
{
uint32_t v___x_1024_; 
v___x_1024_ = 2147483648;
return v___x_1024_;
}
}
}
v___jp_1025_:
{
lean_object* v___x_1029_; lean_object* v___x_1030_; lean_object* v___x_1031_; lean_object* v___x_1032_; uint8_t v___x_1033_; 
v___x_1029_ = lean_nat_to_int(v___y_1028_);
v___x_1030_ = lean_array_get_size(v_neg_860_);
lean_inc(v___y_1026_);
v___x_1031_ = l_Array_extract___redArg(v_neg_860_, v___y_1026_, v___x_1030_);
v___x_1032_ = lean_array_get_size(v___x_1031_);
v___x_1033_ = lean_nat_dec_lt(v___y_1027_, v___x_1032_);
if (v___x_1033_ == 0)
{
lean_dec_ref(v___x_1031_);
lean_inc(v___y_1027_);
v___y_951_ = v___x_1029_;
v___y_952_ = v___y_1026_;
v___y_953_ = v___y_1027_;
v___y_954_ = v___y_1027_;
goto v___jp_950_;
}
else
{
size_t v___x_1034_; size_t v___x_1035_; lean_object* v___x_1036_; 
v___x_1034_ = lean_usize_of_nat(v___x_1032_);
v___x_1035_ = ((size_t)0ULL);
lean_inc(v___y_1027_);
v___x_1036_ = lp_competition___private_Init_Data_Array_Basic_0__Array_foldrMUnsafe_fold___at___00Submission_finishFast_spec__0(v___x_1031_, v___x_1034_, v___x_1035_, v___y_1027_);
lean_dec_ref(v___x_1031_);
v___y_951_ = v___x_1029_;
v___y_952_ = v___y_1026_;
v___y_953_ = v___y_1027_;
v___y_954_ = v___x_1036_;
goto v___jp_950_;
}
}
v___jp_1037_:
{
lean_object* v___x_1038_; lean_object* v___x_1039_; lean_object* v_lo_1040_; lean_object* v___x_1041_; lean_object* v___x_1042_; uint8_t v___x_1043_; 
v___x_1038_ = lean_array_get_size(v_pos_859_);
v___x_1039_ = lean_unsigned_to_nat(0u);
v_lo_1040_ = lp_competition_ExactRuntime_lowLimb(v_pos_859_, v_neg_860_, v___x_1038_, v___x_1039_);
lean_inc(v_lo_1040_);
v___x_1041_ = l_Array_extract___redArg(v_pos_859_, v_lo_1040_, v___x_1038_);
v___x_1042_ = lean_array_get_size(v___x_1041_);
v___x_1043_ = lean_nat_dec_lt(v___x_1039_, v___x_1042_);
if (v___x_1043_ == 0)
{
lean_dec_ref(v___x_1041_);
v___y_1026_ = v_lo_1040_;
v___y_1027_ = v___x_1039_;
v___y_1028_ = v___x_1039_;
goto v___jp_1025_;
}
else
{
size_t v___x_1044_; size_t v___x_1045_; lean_object* v___x_1046_; 
v___x_1044_ = lean_usize_of_nat(v___x_1042_);
v___x_1045_ = ((size_t)0ULL);
v___x_1046_ = lp_competition___private_Init_Data_Array_Basic_0__Array_foldrMUnsafe_fold___at___00Submission_finishFast_spec__0(v___x_1041_, v___x_1044_, v___x_1045_, v___x_1039_);
lean_dec_ref(v___x_1041_);
v___y_1026_ = v_lo_1040_;
v___y_1027_ = v___x_1039_;
v___y_1028_ = v___x_1046_;
goto v___jp_1025_;
}
}
v___jp_1050_:
{
lean_object* v_d_x27_1054_; lean_object* v_snd_1055_; lean_object* v_fst_1056_; lean_object* v_fst_1057_; lean_object* v_snd_1058_; uint8_t v___x_1059_; 
v_d_x27_1054_ = lp_competition_Submission_diffGo(v_neg_860_, v_pos_859_, v_lo_1049_, v___x_1048_, v___x_1048_, v___x_1048_, v___y_1052_, v___y_1053_);
v_snd_1055_ = lean_ctor_get(v_d_x27_1054_, 1);
lean_inc(v_snd_1055_);
v_fst_1056_ = lean_ctor_get(v_d_x27_1054_, 0);
lean_inc(v_fst_1056_);
lean_dec_ref(v_d_x27_1054_);
v_fst_1057_ = lean_ctor_get(v_snd_1055_, 0);
lean_inc(v_fst_1057_);
v_snd_1058_ = lean_ctor_get(v_snd_1055_, 1);
lean_inc(v_snd_1058_);
lean_dec(v_snd_1055_);
v___x_1059_ = lean_nat_dec_eq(v_fst_1057_, v___x_1048_);
lean_dec(v_fst_1057_);
if (v___x_1059_ == 0)
{
lean_dec(v_snd_1058_);
lean_dec(v_fst_1056_);
lean_dec(v___y_1051_);
goto v___jp_1037_;
}
else
{
lean_object* v_fst_1060_; lean_object* v_snd_1061_; uint8_t v___x_1062_; 
v_fst_1060_ = lean_ctor_get(v_snd_1058_, 0);
lean_inc(v_fst_1060_);
v_snd_1061_ = lean_ctor_get(v_snd_1058_, 1);
lean_inc(v_snd_1061_);
lean_dec(v_snd_1058_);
v___x_1062_ = lean_nat_dec_eq(v_fst_1060_, v___x_1048_);
lean_dec(v_fst_1060_);
if (v___x_1062_ == 0)
{
lean_dec(v_snd_1061_);
lean_dec(v_fst_1056_);
lean_dec(v___y_1051_);
goto v___jp_1037_;
}
else
{
uint8_t v___x_1063_; 
v___x_1063_ = lean_nat_dec_eq(v_snd_1061_, v___x_1048_);
lean_dec(v_snd_1061_);
if (v___x_1063_ == 0)
{
lean_dec(v_fst_1056_);
lean_dec(v___y_1051_);
goto v___jp_1037_;
}
else
{
uint32_t v___x_1064_; 
v___x_1064_ = lp_competition_Submission_finishDigits(v___x_1063_, v_fst_1056_, v___y_1051_, v_negZero_862_);
lean_dec(v_fst_1056_);
return v___x_1064_;
}
}
}
}
v___jp_1065_:
{
lean_object* v___x_1067_; lean_object* v___x_1068_; lean_object* v___x_1069_; lean_object* v_n_1070_; lean_object* v___x_1071_; lean_object* v___x_1072_; lean_object* v___x_1073_; lean_object* v_d_1074_; lean_object* v_snd_1075_; lean_object* v_fst_1076_; lean_object* v_fst_1077_; lean_object* v_snd_1078_; lean_object* v___x_1079_; lean_object* v_e_x27_1080_; uint8_t v___x_1081_; 
v___x_1067_ = lp_competition_Submission_highLimb(v_pos_859_, v_neg_860_, v___y_1066_);
v___x_1068_ = lean_unsigned_to_nat(1u);
v___x_1069_ = lean_nat_add(v___x_1067_, v___x_1068_);
lean_dec(v___x_1067_);
v_n_1070_ = lean_nat_sub(v___x_1069_, v_lo_1049_);
lean_dec(v___x_1069_);
v___x_1071_ = lean_unsigned_to_nat(32u);
v___x_1072_ = lean_nat_mul(v___x_1071_, v_lo_1049_);
v___x_1073_ = lean_mk_empty_array_with_capacity(v_n_1070_);
lean_inc(v_n_1070_);
lean_inc_ref(v___x_1073_);
lean_inc(v_lo_1049_);
v_d_1074_ = lp_competition_Submission_diffGo(v_pos_859_, v_neg_860_, v_lo_1049_, v___x_1048_, v___x_1048_, v___x_1048_, v___x_1073_, v_n_1070_);
v_snd_1075_ = lean_ctor_get(v_d_1074_, 1);
lean_inc(v_snd_1075_);
v_fst_1076_ = lean_ctor_get(v_d_1074_, 0);
lean_inc(v_fst_1076_);
lean_dec_ref(v_d_1074_);
v_fst_1077_ = lean_ctor_get(v_snd_1075_, 0);
lean_inc(v_fst_1077_);
v_snd_1078_ = lean_ctor_get(v_snd_1075_, 1);
lean_inc(v_snd_1078_);
lean_dec(v_snd_1075_);
v___x_1079_ = lean_nat_to_int(v___x_1072_);
v_e_x27_1080_ = lean_int_add(v_e_861_, v___x_1079_);
lean_dec(v___x_1079_);
v___x_1081_ = lean_nat_dec_eq(v_fst_1077_, v___x_1048_);
lean_dec(v_fst_1077_);
if (v___x_1081_ == 0)
{
lean_dec(v_snd_1078_);
lean_dec(v_fst_1076_);
v___y_1051_ = v_e_x27_1080_;
v___y_1052_ = v___x_1073_;
v___y_1053_ = v_n_1070_;
goto v___jp_1050_;
}
else
{
lean_object* v_fst_1082_; lean_object* v_snd_1083_; uint8_t v___x_1084_; 
v_fst_1082_ = lean_ctor_get(v_snd_1078_, 0);
lean_inc(v_fst_1082_);
v_snd_1083_ = lean_ctor_get(v_snd_1078_, 1);
lean_inc(v_snd_1083_);
lean_dec(v_snd_1078_);
v___x_1084_ = lean_nat_dec_eq(v_fst_1082_, v___x_1048_);
lean_dec(v_fst_1082_);
if (v___x_1084_ == 0)
{
lean_dec(v_snd_1083_);
lean_dec(v_fst_1076_);
v___y_1051_ = v_e_x27_1080_;
v___y_1052_ = v___x_1073_;
v___y_1053_ = v_n_1070_;
goto v___jp_1050_;
}
else
{
uint8_t v___x_1085_; 
v___x_1085_ = lean_nat_dec_eq(v_snd_1083_, v___x_1048_);
lean_dec(v_snd_1083_);
if (v___x_1085_ == 0)
{
lean_dec(v_fst_1076_);
v___y_1051_ = v_e_x27_1080_;
v___y_1052_ = v___x_1073_;
v___y_1053_ = v_n_1070_;
goto v___jp_1050_;
}
else
{
uint8_t v___x_1086_; uint32_t v___x_1087_; 
lean_dec_ref(v___x_1073_);
lean_dec(v_n_1070_);
lean_dec(v_lo_1049_);
v___x_1086_ = 0;
v___x_1087_ = lp_competition_Submission_finishDigits(v___x_1086_, v_fst_1076_, v_e_x27_1080_, v_negZero_862_);
lean_dec(v_fst_1076_);
return v___x_1087_;
}
}
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_finishFast___boxed(lean_object* v_pos_1090_, lean_object* v_neg_1091_, lean_object* v_e_1092_, lean_object* v_negZero_1093_){
_start:
{
uint8_t v_negZero_boxed_1094_; uint32_t v_res_1095_; lean_object* v_r_1096_; 
v_negZero_boxed_1094_ = lean_unbox(v_negZero_1093_);
v_res_1095_ = lp_competition_Submission_finishFast(v_pos_1090_, v_neg_1091_, v_e_1092_, v_negZero_boxed_1094_);
lean_dec(v_e_1092_);
lean_dec_ref(v_neg_1091_);
lean_dec_ref(v_pos_1090_);
v_r_1096_ = lean_box_uint32(v_res_1095_);
return v_r_1096_;
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_dotStep(lean_object* v_acc_1097_, uint32_t v_wa_1098_, uint32_t v_wb_1099_){
_start:
{
uint8_t v___y_1113_; lean_object* v___y_1114_; uint8_t v___y_1115_; lean_object* v___y_1116_; lean_object* v___y_1117_; lean_object* v___y_1118_; lean_object* v___y_1119_; uint32_t v___x_1130_; uint32_t v___x_1131_; uint32_t v___x_1132_; uint32_t v___x_1133_; uint8_t v___x_1134_; 
v___x_1130_ = 23;
v___x_1131_ = lean_uint32_shift_right(v_wa_1098_, v___x_1130_);
v___x_1132_ = 255;
v___x_1133_ = lean_uint32_land(v___x_1131_, v___x_1132_);
v___x_1134_ = lean_uint32_dec_eq(v___x_1133_, v___x_1132_);
if (v___x_1134_ == 0)
{
uint32_t v___x_1135_; uint32_t v___x_1136_; uint8_t v___x_1137_; lean_object* v___y_1139_; lean_object* v___y_1140_; lean_object* v___y_1141_; uint8_t v___y_1142_; lean_object* v___y_1143_; lean_object* v___y_1144_; lean_object* v___y_1156_; lean_object* v___y_1157_; uint8_t v___y_1158_; lean_object* v___y_1221_; lean_object* v___y_1222_; lean_object* v___y_1225_; lean_object* v___y_1226_; uint8_t v___y_1227_; uint8_t v___y_1228_; lean_object* v___y_1230_; lean_object* v___y_1231_; uint8_t v___y_1232_; lean_object* v___y_1239_; lean_object* v___y_1240_; lean_object* v___y_1241_; lean_object* v___y_1249_; lean_object* v___y_1250_; lean_object* v___y_1258_; lean_object* v___y_1259_; lean_object* v___y_1268_; 
v___x_1135_ = lean_uint32_shift_right(v_wb_1099_, v___x_1130_);
v___x_1136_ = lean_uint32_land(v___x_1135_, v___x_1132_);
v___x_1137_ = lean_uint32_dec_eq(v___x_1136_, v___x_1132_);
if (v___x_1137_ == 0)
{
uint32_t v___x_1279_; uint8_t v___x_1280_; 
v___x_1279_ = 0;
v___x_1280_ = lean_uint32_dec_eq(v___x_1133_, v___x_1279_);
if (v___x_1280_ == 0)
{
lean_object* v___x_1281_; uint32_t v___x_1282_; uint32_t v___x_1283_; lean_object* v___x_1284_; lean_object* v___x_1285_; 
v___x_1281_ = lean_unsigned_to_nat(8388608u);
v___x_1282_ = 8388607;
v___x_1283_ = lean_uint32_land(v_wa_1098_, v___x_1282_);
v___x_1284_ = lean_uint32_to_nat(v___x_1283_);
v___x_1285_ = lean_nat_add(v___x_1281_, v___x_1284_);
lean_dec(v___x_1284_);
v___y_1268_ = v___x_1285_;
goto v___jp_1267_;
}
else
{
uint32_t v___x_1286_; uint32_t v___x_1287_; lean_object* v___x_1288_; 
v___x_1286_ = 8388607;
v___x_1287_ = lean_uint32_land(v_wa_1098_, v___x_1286_);
v___x_1288_ = lean_uint32_to_nat(v___x_1287_);
v___y_1268_ = v___x_1288_;
goto v___jp_1267_;
}
}
else
{
goto v___jp_1100_;
}
v___jp_1138_:
{
lean_object* v___x_1145_; lean_object* v___x_1146_; uint8_t v___x_1147_; 
v___x_1145_ = lean_nat_add(v___y_1141_, v___y_1139_);
lean_dec(v___y_1141_);
v___x_1146_ = lean_array_get_size(v___y_1144_);
v___x_1147_ = lean_nat_dec_lt(v___x_1145_, v___x_1146_);
if (v___x_1147_ == 0)
{
lean_object* v___x_1148_; 
lean_dec(v___x_1145_);
lean_dec(v___y_1143_);
v___x_1148_ = lean_alloc_ctor(0, 2, 2);
lean_ctor_set(v___x_1148_, 0, v___y_1140_);
lean_ctor_set(v___x_1148_, 1, v___y_1144_);
lean_ctor_set_uint8(v___x_1148_, sizeof(void*)*2, v___y_1142_);
lean_ctor_set_uint8(v___x_1148_, sizeof(void*)*2 + 1, v___x_1137_);
return v___x_1148_;
}
else
{
lean_object* v_v_1149_; lean_object* v___x_1150_; lean_object* v_xs_x27_1151_; lean_object* v___x_1152_; lean_object* v___x_1153_; lean_object* v___x_1154_; 
v_v_1149_ = lean_array_fget(v___y_1144_, v___x_1145_);
v___x_1150_ = lean_box(0);
v_xs_x27_1151_ = lean_array_fset(v___y_1144_, v___x_1145_, v___x_1150_);
v___x_1152_ = lean_nat_add(v_v_1149_, v___y_1143_);
lean_dec(v___y_1143_);
lean_dec(v_v_1149_);
v___x_1153_ = lean_array_fset(v_xs_x27_1151_, v___x_1145_, v___x_1152_);
lean_dec(v___x_1145_);
v___x_1154_ = lean_alloc_ctor(0, 2, 2);
lean_ctor_set(v___x_1154_, 0, v___y_1140_);
lean_ctor_set(v___x_1154_, 1, v___x_1153_);
lean_ctor_set_uint8(v___x_1154_, sizeof(void*)*2, v___y_1142_);
lean_ctor_set_uint8(v___x_1154_, sizeof(void*)*2 + 1, v___x_1137_);
return v___x_1154_;
}
}
v___jp_1155_:
{
lean_object* v_pos_1159_; lean_object* v_neg_1160_; uint8_t v_special_1161_; uint8_t v_negZero_1162_; lean_object* v___x_1163_; uint8_t v___x_1164_; 
v_pos_1159_ = lean_ctor_get(v_acc_1097_, 0);
v_neg_1160_ = lean_ctor_get(v_acc_1097_, 1);
v_special_1161_ = lean_ctor_get_uint8(v_acc_1097_, sizeof(void*)*2);
v_negZero_1162_ = lean_ctor_get_uint8(v_acc_1097_, sizeof(void*)*2 + 1);
v___x_1163_ = lean_unsigned_to_nat(0u);
v___x_1164_ = lean_nat_dec_eq(v___y_1157_, v___x_1163_);
if (v___x_1164_ == 0)
{
lean_inc_ref(v_neg_1160_);
lean_inc_ref(v_pos_1159_);
lean_dec_ref(v_acc_1097_);
if (v___y_1158_ == 0)
{
uint64_t v___x_1165_; lean_object* v___x_1166_; lean_object* v___x_1167_; lean_object* v_l_1168_; lean_object* v___x_1169_; uint64_t v_r_1170_; lean_object* v___x_1171_; uint64_t v___x_1172_; uint64_t v___x_1173_; uint64_t v___x_1174_; uint64_t v___x_1175_; uint64_t v___x_1176_; uint64_t v___x_1177_; lean_object* v_hi_1178_; lean_object* v___x_1179_; uint8_t v___x_1180_; 
v___x_1165_ = lean_uint64_of_nat(v___y_1157_);
lean_dec(v___y_1157_);
v___x_1166_ = lean_unsigned_to_nat(32u);
v___x_1167_ = lean_unsigned_to_nat(5u);
v_l_1168_ = lean_nat_shiftr(v___y_1156_, v___x_1167_);
v___x_1169_ = lean_nat_mod(v___y_1156_, v___x_1166_);
lean_dec(v___y_1156_);
v_r_1170_ = lean_uint64_of_nat(v___x_1169_);
lean_dec(v___x_1169_);
v___x_1171_ = lean_unsigned_to_nat(1u);
v___x_1172_ = 1ULL;
v___x_1173_ = 32ULL;
v___x_1174_ = lean_uint64_sub(v___x_1173_, v_r_1170_);
v___x_1175_ = lean_uint64_shift_left(v___x_1172_, v___x_1174_);
v___x_1176_ = lean_uint64_mod(v___x_1165_, v___x_1175_);
v___x_1177_ = lean_uint64_shift_right(v___x_1165_, v___x_1174_);
v_hi_1178_ = lean_uint64_to_nat(v___x_1177_);
v___x_1179_ = lean_array_get_size(v_pos_1159_);
v___x_1180_ = lean_nat_dec_lt(v_l_1168_, v___x_1179_);
if (v___x_1180_ == 0)
{
v___y_1113_ = v___y_1158_;
v___y_1114_ = v_neg_1160_;
v___y_1115_ = v_special_1161_;
v___y_1116_ = v_l_1168_;
v___y_1117_ = v_hi_1178_;
v___y_1118_ = v___x_1171_;
v___y_1119_ = v_pos_1159_;
goto v___jp_1112_;
}
else
{
uint64_t v___x_1181_; lean_object* v_lo_1182_; lean_object* v_v_1183_; lean_object* v___x_1184_; lean_object* v_xs_x27_1185_; lean_object* v___x_1186_; lean_object* v___x_1187_; 
v___x_1181_ = lean_uint64_shift_left(v___x_1176_, v_r_1170_);
v_lo_1182_ = lean_uint64_to_nat(v___x_1181_);
v_v_1183_ = lean_array_fget(v_pos_1159_, v_l_1168_);
v___x_1184_ = lean_box(0);
v_xs_x27_1185_ = lean_array_fset(v_pos_1159_, v_l_1168_, v___x_1184_);
v___x_1186_ = lean_nat_add(v_v_1183_, v_lo_1182_);
lean_dec(v_lo_1182_);
lean_dec(v_v_1183_);
v___x_1187_ = lean_array_fset(v_xs_x27_1185_, v_l_1168_, v___x_1186_);
v___y_1113_ = v___y_1158_;
v___y_1114_ = v_neg_1160_;
v___y_1115_ = v_special_1161_;
v___y_1116_ = v_l_1168_;
v___y_1117_ = v_hi_1178_;
v___y_1118_ = v___x_1171_;
v___y_1119_ = v___x_1187_;
goto v___jp_1112_;
}
}
else
{
uint64_t v___x_1188_; lean_object* v___x_1189_; lean_object* v___x_1190_; lean_object* v_l_1191_; lean_object* v___x_1192_; uint64_t v_r_1193_; lean_object* v___x_1194_; uint64_t v___x_1195_; uint64_t v___x_1196_; uint64_t v___x_1197_; uint64_t v___x_1198_; uint64_t v___x_1199_; uint64_t v___x_1200_; lean_object* v_hi_1201_; lean_object* v___x_1202_; uint8_t v___x_1203_; 
v___x_1188_ = lean_uint64_of_nat(v___y_1157_);
lean_dec(v___y_1157_);
v___x_1189_ = lean_unsigned_to_nat(32u);
v___x_1190_ = lean_unsigned_to_nat(5u);
v_l_1191_ = lean_nat_shiftr(v___y_1156_, v___x_1190_);
v___x_1192_ = lean_nat_mod(v___y_1156_, v___x_1189_);
lean_dec(v___y_1156_);
v_r_1193_ = lean_uint64_of_nat(v___x_1192_);
lean_dec(v___x_1192_);
v___x_1194_ = lean_unsigned_to_nat(1u);
v___x_1195_ = 1ULL;
v___x_1196_ = 32ULL;
v___x_1197_ = lean_uint64_sub(v___x_1196_, v_r_1193_);
v___x_1198_ = lean_uint64_shift_left(v___x_1195_, v___x_1197_);
v___x_1199_ = lean_uint64_mod(v___x_1188_, v___x_1198_);
v___x_1200_ = lean_uint64_shift_right(v___x_1188_, v___x_1197_);
v_hi_1201_ = lean_uint64_to_nat(v___x_1200_);
v___x_1202_ = lean_array_get_size(v_neg_1160_);
v___x_1203_ = lean_nat_dec_lt(v_l_1191_, v___x_1202_);
if (v___x_1203_ == 0)
{
v___y_1139_ = v___x_1194_;
v___y_1140_ = v_pos_1159_;
v___y_1141_ = v_l_1191_;
v___y_1142_ = v_special_1161_;
v___y_1143_ = v_hi_1201_;
v___y_1144_ = v_neg_1160_;
goto v___jp_1138_;
}
else
{
uint64_t v___x_1204_; lean_object* v_lo_1205_; lean_object* v_v_1206_; lean_object* v___x_1207_; lean_object* v_xs_x27_1208_; lean_object* v___x_1209_; lean_object* v___x_1210_; 
v___x_1204_ = lean_uint64_shift_left(v___x_1199_, v_r_1193_);
v_lo_1205_ = lean_uint64_to_nat(v___x_1204_);
v_v_1206_ = lean_array_fget(v_neg_1160_, v_l_1191_);
v___x_1207_ = lean_box(0);
v_xs_x27_1208_ = lean_array_fset(v_neg_1160_, v_l_1191_, v___x_1207_);
v___x_1209_ = lean_nat_add(v_v_1206_, v_lo_1205_);
lean_dec(v_lo_1205_);
lean_dec(v_v_1206_);
v___x_1210_ = lean_array_fset(v_xs_x27_1208_, v_l_1191_, v___x_1209_);
v___y_1139_ = v___x_1194_;
v___y_1140_ = v_pos_1159_;
v___y_1141_ = v_l_1191_;
v___y_1142_ = v_special_1161_;
v___y_1143_ = v_hi_1201_;
v___y_1144_ = v___x_1210_;
goto v___jp_1138_;
}
}
}
else
{
lean_dec(v___y_1157_);
lean_dec(v___y_1156_);
if (v_negZero_1162_ == 0)
{
return v_acc_1097_;
}
else
{
lean_object* v___x_1212_; uint8_t v_isShared_1213_; uint8_t v_isSharedCheck_1217_; 
lean_inc_ref(v_neg_1160_);
lean_inc_ref(v_pos_1159_);
v_isSharedCheck_1217_ = !lean_is_exclusive(v_acc_1097_);
if (v_isSharedCheck_1217_ == 0)
{
lean_object* v_unused_1218_; lean_object* v_unused_1219_; 
v_unused_1218_ = lean_ctor_get(v_acc_1097_, 1);
lean_dec(v_unused_1218_);
v_unused_1219_ = lean_ctor_get(v_acc_1097_, 0);
lean_dec(v_unused_1219_);
v___x_1212_ = v_acc_1097_;
v_isShared_1213_ = v_isSharedCheck_1217_;
goto v_resetjp_1211_;
}
else
{
lean_dec(v_acc_1097_);
v___x_1212_ = lean_box(0);
v_isShared_1213_ = v_isSharedCheck_1217_;
goto v_resetjp_1211_;
}
v_resetjp_1211_:
{
lean_object* v___x_1215_; 
if (v_isShared_1213_ == 0)
{
v___x_1215_ = v___x_1212_;
goto v_reusejp_1214_;
}
else
{
lean_object* v_reuseFailAlloc_1216_; 
v_reuseFailAlloc_1216_ = lean_alloc_ctor(0, 2, 2);
lean_ctor_set(v_reuseFailAlloc_1216_, 0, v_pos_1159_);
lean_ctor_set(v_reuseFailAlloc_1216_, 1, v_neg_1160_);
lean_ctor_set_uint8(v_reuseFailAlloc_1216_, sizeof(void*)*2, v_special_1161_);
v___x_1215_ = v_reuseFailAlloc_1216_;
goto v_reusejp_1214_;
}
v_reusejp_1214_:
{
lean_ctor_set_uint8(v___x_1215_, sizeof(void*)*2 + 1, v___y_1158_);
return v___x_1215_;
}
}
}
}
}
v___jp_1220_:
{
uint8_t v___x_1223_; 
v___x_1223_ = 1;
v___y_1156_ = v___y_1221_;
v___y_1157_ = v___y_1222_;
v___y_1158_ = v___x_1223_;
goto v___jp_1155_;
}
v___jp_1224_:
{
if (v___y_1227_ == 0)
{
if (v___y_1228_ == 0)
{
v___y_1156_ = v___y_1225_;
v___y_1157_ = v___y_1226_;
v___y_1158_ = v___x_1137_;
goto v___jp_1155_;
}
else
{
v___y_1221_ = v___y_1225_;
v___y_1222_ = v___y_1226_;
goto v___jp_1220_;
}
}
else
{
if (v___y_1228_ == 0)
{
v___y_1221_ = v___y_1225_;
v___y_1222_ = v___y_1226_;
goto v___jp_1220_;
}
else
{
v___y_1156_ = v___y_1225_;
v___y_1157_ = v___y_1226_;
v___y_1158_ = v___x_1137_;
goto v___jp_1155_;
}
}
}
v___jp_1229_:
{
uint32_t v___x_1233_; uint32_t v___x_1234_; uint32_t v___x_1235_; uint8_t v___x_1236_; 
v___x_1233_ = 2147483648;
v___x_1234_ = lean_uint32_land(v_wb_1099_, v___x_1233_);
v___x_1235_ = 0;
v___x_1236_ = lean_uint32_dec_eq(v___x_1234_, v___x_1235_);
if (v___x_1236_ == 0)
{
uint8_t v___x_1237_; 
v___x_1237_ = 1;
v___y_1225_ = v___y_1230_;
v___y_1226_ = v___y_1231_;
v___y_1227_ = v___y_1232_;
v___y_1228_ = v___x_1237_;
goto v___jp_1224_;
}
else
{
v___y_1225_ = v___y_1230_;
v___y_1226_ = v___y_1231_;
v___y_1227_ = v___y_1232_;
v___y_1228_ = v___x_1137_;
goto v___jp_1224_;
}
}
v___jp_1238_:
{
lean_object* v___x_1242_; uint32_t v___x_1243_; uint32_t v___x_1244_; uint32_t v___x_1245_; uint8_t v___x_1246_; 
v___x_1242_ = lean_nat_add(v___y_1240_, v___y_1241_);
lean_dec(v___y_1241_);
lean_dec(v___y_1240_);
v___x_1243_ = 2147483648;
v___x_1244_ = lean_uint32_land(v_wa_1098_, v___x_1243_);
v___x_1245_ = 0;
v___x_1246_ = lean_uint32_dec_eq(v___x_1244_, v___x_1245_);
if (v___x_1246_ == 0)
{
uint8_t v___x_1247_; 
v___x_1247_ = 1;
v___y_1230_ = v___x_1242_;
v___y_1231_ = v___y_1239_;
v___y_1232_ = v___x_1247_;
goto v___jp_1229_;
}
else
{
v___y_1230_ = v___x_1242_;
v___y_1231_ = v___y_1239_;
v___y_1232_ = v___x_1137_;
goto v___jp_1229_;
}
}
v___jp_1248_:
{
uint32_t v___x_1251_; uint8_t v___x_1252_; 
v___x_1251_ = 0;
v___x_1252_ = lean_uint32_dec_eq(v___x_1136_, v___x_1251_);
if (v___x_1252_ == 0)
{
lean_object* v___x_1253_; lean_object* v___x_1254_; lean_object* v___x_1255_; 
v___x_1253_ = lean_uint32_to_nat(v___x_1136_);
v___x_1254_ = lean_unsigned_to_nat(1u);
v___x_1255_ = lean_nat_sub(v___x_1253_, v___x_1254_);
lean_dec(v___x_1253_);
v___y_1239_ = v___y_1249_;
v___y_1240_ = v___y_1250_;
v___y_1241_ = v___x_1255_;
goto v___jp_1238_;
}
else
{
lean_object* v___x_1256_; 
v___x_1256_ = lean_unsigned_to_nat(0u);
v___y_1239_ = v___y_1249_;
v___y_1240_ = v___y_1250_;
v___y_1241_ = v___x_1256_;
goto v___jp_1238_;
}
}
v___jp_1257_:
{
lean_object* v___x_1260_; uint32_t v___x_1261_; uint8_t v___x_1262_; 
v___x_1260_ = lean_nat_mul(v___y_1258_, v___y_1259_);
lean_dec(v___y_1259_);
lean_dec(v___y_1258_);
v___x_1261_ = 0;
v___x_1262_ = lean_uint32_dec_eq(v___x_1133_, v___x_1261_);
if (v___x_1262_ == 0)
{
lean_object* v___x_1263_; lean_object* v___x_1264_; lean_object* v___x_1265_; 
v___x_1263_ = lean_uint32_to_nat(v___x_1133_);
v___x_1264_ = lean_unsigned_to_nat(1u);
v___x_1265_ = lean_nat_sub(v___x_1263_, v___x_1264_);
lean_dec(v___x_1263_);
v___y_1249_ = v___x_1260_;
v___y_1250_ = v___x_1265_;
goto v___jp_1248_;
}
else
{
lean_object* v___x_1266_; 
v___x_1266_ = lean_unsigned_to_nat(0u);
v___y_1249_ = v___x_1260_;
v___y_1250_ = v___x_1266_;
goto v___jp_1248_;
}
}
v___jp_1267_:
{
uint32_t v___x_1269_; uint8_t v___x_1270_; 
v___x_1269_ = 0;
v___x_1270_ = lean_uint32_dec_eq(v___x_1136_, v___x_1269_);
if (v___x_1270_ == 0)
{
lean_object* v___x_1271_; uint32_t v___x_1272_; uint32_t v___x_1273_; lean_object* v___x_1274_; lean_object* v___x_1275_; 
v___x_1271_ = lean_unsigned_to_nat(8388608u);
v___x_1272_ = 8388607;
v___x_1273_ = lean_uint32_land(v_wb_1099_, v___x_1272_);
v___x_1274_ = lean_uint32_to_nat(v___x_1273_);
v___x_1275_ = lean_nat_add(v___x_1271_, v___x_1274_);
lean_dec(v___x_1274_);
v___y_1258_ = v___y_1268_;
v___y_1259_ = v___x_1275_;
goto v___jp_1257_;
}
else
{
uint32_t v___x_1276_; uint32_t v___x_1277_; lean_object* v___x_1278_; 
v___x_1276_ = 8388607;
v___x_1277_ = lean_uint32_land(v_wb_1099_, v___x_1276_);
v___x_1278_ = lean_uint32_to_nat(v___x_1277_);
v___y_1258_ = v___y_1268_;
v___y_1259_ = v___x_1278_;
goto v___jp_1257_;
}
}
}
else
{
goto v___jp_1100_;
}
v___jp_1100_:
{
lean_object* v_pos_1101_; lean_object* v_neg_1102_; uint8_t v_negZero_1103_; lean_object* v___x_1105_; uint8_t v_isShared_1106_; uint8_t v_isSharedCheck_1111_; 
v_pos_1101_ = lean_ctor_get(v_acc_1097_, 0);
v_neg_1102_ = lean_ctor_get(v_acc_1097_, 1);
v_negZero_1103_ = lean_ctor_get_uint8(v_acc_1097_, sizeof(void*)*2 + 1);
v_isSharedCheck_1111_ = !lean_is_exclusive(v_acc_1097_);
if (v_isSharedCheck_1111_ == 0)
{
v___x_1105_ = v_acc_1097_;
v_isShared_1106_ = v_isSharedCheck_1111_;
goto v_resetjp_1104_;
}
else
{
lean_inc(v_neg_1102_);
lean_inc(v_pos_1101_);
lean_dec(v_acc_1097_);
v___x_1105_ = lean_box(0);
v_isShared_1106_ = v_isSharedCheck_1111_;
goto v_resetjp_1104_;
}
v_resetjp_1104_:
{
uint8_t v___x_1107_; lean_object* v___x_1109_; 
v___x_1107_ = 1;
if (v_isShared_1106_ == 0)
{
v___x_1109_ = v___x_1105_;
goto v_reusejp_1108_;
}
else
{
lean_object* v_reuseFailAlloc_1110_; 
v_reuseFailAlloc_1110_ = lean_alloc_ctor(0, 2, 2);
lean_ctor_set(v_reuseFailAlloc_1110_, 0, v_pos_1101_);
lean_ctor_set(v_reuseFailAlloc_1110_, 1, v_neg_1102_);
lean_ctor_set_uint8(v_reuseFailAlloc_1110_, sizeof(void*)*2 + 1, v_negZero_1103_);
v___x_1109_ = v_reuseFailAlloc_1110_;
goto v_reusejp_1108_;
}
v_reusejp_1108_:
{
lean_ctor_set_uint8(v___x_1109_, sizeof(void*)*2, v___x_1107_);
return v___x_1109_;
}
}
}
v___jp_1112_:
{
lean_object* v___x_1120_; lean_object* v___x_1121_; uint8_t v___x_1122_; 
v___x_1120_ = lean_nat_add(v___y_1116_, v___y_1118_);
lean_dec(v___y_1116_);
v___x_1121_ = lean_array_get_size(v___y_1119_);
v___x_1122_ = lean_nat_dec_lt(v___x_1120_, v___x_1121_);
if (v___x_1122_ == 0)
{
lean_object* v___x_1123_; 
lean_dec(v___x_1120_);
lean_dec(v___y_1117_);
v___x_1123_ = lean_alloc_ctor(0, 2, 2);
lean_ctor_set(v___x_1123_, 0, v___y_1119_);
lean_ctor_set(v___x_1123_, 1, v___y_1114_);
lean_ctor_set_uint8(v___x_1123_, sizeof(void*)*2, v___y_1115_);
lean_ctor_set_uint8(v___x_1123_, sizeof(void*)*2 + 1, v___y_1113_);
return v___x_1123_;
}
else
{
lean_object* v_v_1124_; lean_object* v___x_1125_; lean_object* v_xs_x27_1126_; lean_object* v___x_1127_; lean_object* v___x_1128_; lean_object* v___x_1129_; 
v_v_1124_ = lean_array_fget(v___y_1119_, v___x_1120_);
v___x_1125_ = lean_box(0);
v_xs_x27_1126_ = lean_array_fset(v___y_1119_, v___x_1120_, v___x_1125_);
v___x_1127_ = lean_nat_add(v_v_1124_, v___y_1117_);
lean_dec(v___y_1117_);
lean_dec(v_v_1124_);
v___x_1128_ = lean_array_fset(v_xs_x27_1126_, v___x_1120_, v___x_1127_);
lean_dec(v___x_1120_);
v___x_1129_ = lean_alloc_ctor(0, 2, 2);
lean_ctor_set(v___x_1129_, 0, v___x_1128_);
lean_ctor_set(v___x_1129_, 1, v___y_1114_);
lean_ctor_set_uint8(v___x_1129_, sizeof(void*)*2, v___y_1115_);
lean_ctor_set_uint8(v___x_1129_, sizeof(void*)*2 + 1, v___y_1113_);
return v___x_1129_;
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_dotStep___boxed(lean_object* v_acc_1289_, lean_object* v_wa_1290_, lean_object* v_wb_1291_){
_start:
{
uint32_t v_wa_boxed_1292_; uint32_t v_wb_boxed_1293_; lean_object* v_res_1294_; 
v_wa_boxed_1292_ = lean_unbox_uint32(v_wa_1290_);
lean_dec(v_wa_1290_);
v_wb_boxed_1293_ = lean_unbox_uint32(v_wb_1291_);
lean_dec(v_wb_1291_);
v_res_1294_ = lp_competition_Submission_dotStep(v_acc_1289_, v_wa_boxed_1292_, v_wb_boxed_1293_);
return v_res_1294_;
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_dotLoop(lean_object* v_fa_1295_, lean_object* v_fb_1296_, lean_object* v_pos_1297_, lean_object* v_neg_1298_, uint8_t v_sp_1299_, uint8_t v_nz_1300_, lean_object* v_index_1301_, lean_object* v_x_1302_){
_start:
{
lean_object* v_zero_1303_; uint8_t v_isZero_1304_; 
v_zero_1303_ = lean_unsigned_to_nat(0u);
v_isZero_1304_ = lean_nat_dec_eq(v_x_1302_, v_zero_1303_);
if (v_isZero_1304_ == 1)
{
lean_object* v___x_1305_; 
lean_dec(v_x_1302_);
lean_dec(v_index_1301_);
lean_dec_ref(v_fb_1296_);
lean_dec_ref(v_fa_1295_);
v___x_1305_ = lean_alloc_ctor(0, 2, 2);
lean_ctor_set(v___x_1305_, 0, v_pos_1297_);
lean_ctor_set(v___x_1305_, 1, v_neg_1298_);
lean_ctor_set_uint8(v___x_1305_, sizeof(void*)*2, v_sp_1299_);
lean_ctor_set_uint8(v___x_1305_, sizeof(void*)*2 + 1, v_nz_1300_);
return v___x_1305_;
}
else
{
lean_object* v_one_1306_; lean_object* v_n_1307_; lean_object* v_pos_1309_; lean_object* v_neg_1310_; uint8_t v_special_1311_; uint8_t v_negZero_1312_; uint8_t v___y_1318_; lean_object* v___y_1319_; lean_object* v___y_1320_; lean_object* v___y_1321_; lean_object* v___y_1322_; lean_object* v___y_1332_; lean_object* v___y_1333_; lean_object* v___y_1334_; lean_object* v___y_1335_; lean_object* v___y_1345_; lean_object* v___y_1346_; uint8_t v___y_1347_; lean_object* v___y_1394_; lean_object* v___y_1395_; lean_object* v___x_1397_; uint32_t v___x_1398_; uint32_t v___x_1399_; uint32_t v___x_1400_; uint32_t v___x_1401_; uint32_t v___x_1402_; uint8_t v___x_1403_; uint8_t v___y_1405_; lean_object* v___y_1406_; lean_object* v___y_1407_; uint8_t v___y_1408_; 
v_one_1306_ = lean_unsigned_to_nat(1u);
v_n_1307_ = lean_nat_sub(v_x_1302_, v_one_1306_);
lean_dec(v_x_1302_);
lean_inc_ref(v_fa_1295_);
lean_inc(v_index_1301_);
v___x_1397_ = lean_apply_1(v_fa_1295_, v_index_1301_);
v___x_1398_ = 23;
v___x_1399_ = lean_unbox_uint32(v___x_1397_);
v___x_1400_ = lean_uint32_shift_right(v___x_1399_, v___x_1398_);
v___x_1401_ = 255;
v___x_1402_ = lean_uint32_land(v___x_1400_, v___x_1401_);
v___x_1403_ = lean_uint32_dec_eq(v___x_1402_, v___x_1401_);
if (v___x_1403_ == 0)
{
lean_object* v___x_1409_; lean_object* v___y_1411_; lean_object* v___y_1412_; uint8_t v___y_1413_; lean_object* v___y_1421_; lean_object* v___y_1422_; lean_object* v___y_1423_; lean_object* v___y_1432_; lean_object* v___y_1433_; lean_object* v___y_1442_; lean_object* v___y_1443_; lean_object* v___y_1450_; uint32_t v___x_1466_; uint32_t v___x_1467_; uint32_t v___x_1468_; uint8_t v___x_1469_; 
lean_inc_ref(v_fb_1296_);
lean_inc(v_index_1301_);
v___x_1409_ = lean_apply_1(v_fb_1296_, v_index_1301_);
v___x_1466_ = lean_unbox_uint32(v___x_1409_);
v___x_1467_ = lean_uint32_shift_right(v___x_1466_, v___x_1398_);
v___x_1468_ = lean_uint32_land(v___x_1467_, v___x_1401_);
v___x_1469_ = lean_uint32_dec_eq(v___x_1468_, v___x_1401_);
if (v___x_1469_ == 0)
{
uint32_t v___x_1470_; uint8_t v___x_1471_; 
v___x_1470_ = 0;
v___x_1471_ = lean_uint32_dec_eq(v___x_1402_, v___x_1470_);
if (v___x_1471_ == 0)
{
lean_object* v___x_1472_; uint32_t v___x_1473_; uint32_t v___x_1474_; uint32_t v___x_1475_; lean_object* v___x_1476_; lean_object* v___x_1477_; 
v___x_1472_ = lean_unsigned_to_nat(8388608u);
v___x_1473_ = 8388607;
v___x_1474_ = lean_unbox_uint32(v___x_1397_);
v___x_1475_ = lean_uint32_land(v___x_1474_, v___x_1473_);
v___x_1476_ = lean_uint32_to_nat(v___x_1475_);
v___x_1477_ = lean_nat_add(v___x_1472_, v___x_1476_);
lean_dec(v___x_1476_);
v___y_1450_ = v___x_1477_;
goto v___jp_1449_;
}
else
{
uint32_t v___x_1478_; uint32_t v___x_1479_; uint32_t v___x_1480_; lean_object* v___x_1481_; 
v___x_1478_ = 8388607;
v___x_1479_ = lean_unbox_uint32(v___x_1397_);
v___x_1480_ = lean_uint32_land(v___x_1479_, v___x_1478_);
v___x_1481_ = lean_uint32_to_nat(v___x_1480_);
v___y_1450_ = v___x_1481_;
goto v___jp_1449_;
}
}
else
{
lean_dec(v___x_1409_);
lean_dec(v___x_1397_);
goto v___jp_1315_;
}
v___jp_1410_:
{
uint32_t v___x_1414_; uint32_t v___x_1415_; uint32_t v___x_1416_; uint32_t v___x_1417_; uint8_t v___x_1418_; 
v___x_1414_ = 2147483648;
v___x_1415_ = lean_unbox_uint32(v___x_1409_);
lean_dec(v___x_1409_);
v___x_1416_ = lean_uint32_land(v___x_1415_, v___x_1414_);
v___x_1417_ = 0;
v___x_1418_ = lean_uint32_dec_eq(v___x_1416_, v___x_1417_);
if (v___x_1418_ == 0)
{
uint8_t v___x_1419_; 
v___x_1419_ = 1;
v___y_1405_ = v___y_1413_;
v___y_1406_ = v___y_1411_;
v___y_1407_ = v___y_1412_;
v___y_1408_ = v___x_1419_;
goto v___jp_1404_;
}
else
{
v___y_1405_ = v___y_1413_;
v___y_1406_ = v___y_1411_;
v___y_1407_ = v___y_1412_;
v___y_1408_ = v___x_1403_;
goto v___jp_1404_;
}
}
v___jp_1420_:
{
lean_object* v___x_1424_; uint32_t v___x_1425_; uint32_t v___x_1426_; uint32_t v___x_1427_; uint32_t v___x_1428_; uint8_t v___x_1429_; 
v___x_1424_ = lean_nat_add(v___y_1421_, v___y_1423_);
lean_dec(v___y_1423_);
lean_dec(v___y_1421_);
v___x_1425_ = 2147483648;
v___x_1426_ = lean_unbox_uint32(v___x_1397_);
lean_dec(v___x_1397_);
v___x_1427_ = lean_uint32_land(v___x_1426_, v___x_1425_);
v___x_1428_ = 0;
v___x_1429_ = lean_uint32_dec_eq(v___x_1427_, v___x_1428_);
if (v___x_1429_ == 0)
{
uint8_t v___x_1430_; 
v___x_1430_ = 1;
v___y_1411_ = v___y_1422_;
v___y_1412_ = v___x_1424_;
v___y_1413_ = v___x_1430_;
goto v___jp_1410_;
}
else
{
v___y_1411_ = v___y_1422_;
v___y_1412_ = v___x_1424_;
v___y_1413_ = v___x_1403_;
goto v___jp_1410_;
}
}
v___jp_1431_:
{
uint32_t v___x_1434_; uint32_t v___x_1435_; uint32_t v___x_1436_; uint32_t v___x_1437_; uint8_t v___x_1438_; 
v___x_1434_ = lean_unbox_uint32(v___x_1409_);
v___x_1435_ = lean_uint32_shift_right(v___x_1434_, v___x_1398_);
v___x_1436_ = lean_uint32_land(v___x_1435_, v___x_1401_);
v___x_1437_ = 0;
v___x_1438_ = lean_uint32_dec_eq(v___x_1436_, v___x_1437_);
if (v___x_1438_ == 0)
{
lean_object* v___x_1439_; lean_object* v___x_1440_; 
v___x_1439_ = lean_uint32_to_nat(v___x_1436_);
v___x_1440_ = lean_nat_sub(v___x_1439_, v_one_1306_);
lean_dec(v___x_1439_);
v___y_1421_ = v___y_1433_;
v___y_1422_ = v___y_1432_;
v___y_1423_ = v___x_1440_;
goto v___jp_1420_;
}
else
{
v___y_1421_ = v___y_1433_;
v___y_1422_ = v___y_1432_;
v___y_1423_ = v_zero_1303_;
goto v___jp_1420_;
}
}
v___jp_1441_:
{
lean_object* v___x_1444_; uint32_t v___x_1445_; uint8_t v___x_1446_; 
v___x_1444_ = lean_nat_mul(v___y_1442_, v___y_1443_);
lean_dec(v___y_1443_);
lean_dec(v___y_1442_);
v___x_1445_ = 0;
v___x_1446_ = lean_uint32_dec_eq(v___x_1402_, v___x_1445_);
if (v___x_1446_ == 0)
{
lean_object* v___x_1447_; lean_object* v___x_1448_; 
v___x_1447_ = lean_uint32_to_nat(v___x_1402_);
v___x_1448_ = lean_nat_sub(v___x_1447_, v_one_1306_);
lean_dec(v___x_1447_);
v___y_1432_ = v___x_1444_;
v___y_1433_ = v___x_1448_;
goto v___jp_1431_;
}
else
{
v___y_1432_ = v___x_1444_;
v___y_1433_ = v_zero_1303_;
goto v___jp_1431_;
}
}
v___jp_1449_:
{
uint32_t v___x_1451_; uint32_t v___x_1452_; uint32_t v___x_1453_; uint32_t v___x_1454_; uint8_t v___x_1455_; 
v___x_1451_ = lean_unbox_uint32(v___x_1409_);
v___x_1452_ = lean_uint32_shift_right(v___x_1451_, v___x_1398_);
v___x_1453_ = lean_uint32_land(v___x_1452_, v___x_1401_);
v___x_1454_ = 0;
v___x_1455_ = lean_uint32_dec_eq(v___x_1453_, v___x_1454_);
if (v___x_1455_ == 0)
{
lean_object* v___x_1456_; uint32_t v___x_1457_; uint32_t v___x_1458_; uint32_t v___x_1459_; lean_object* v___x_1460_; lean_object* v___x_1461_; 
v___x_1456_ = lean_unsigned_to_nat(8388608u);
v___x_1457_ = 8388607;
v___x_1458_ = lean_unbox_uint32(v___x_1409_);
v___x_1459_ = lean_uint32_land(v___x_1458_, v___x_1457_);
v___x_1460_ = lean_uint32_to_nat(v___x_1459_);
v___x_1461_ = lean_nat_add(v___x_1456_, v___x_1460_);
lean_dec(v___x_1460_);
v___y_1442_ = v___y_1450_;
v___y_1443_ = v___x_1461_;
goto v___jp_1441_;
}
else
{
uint32_t v___x_1462_; uint32_t v___x_1463_; uint32_t v___x_1464_; lean_object* v___x_1465_; 
v___x_1462_ = 8388607;
v___x_1463_ = lean_unbox_uint32(v___x_1409_);
v___x_1464_ = lean_uint32_land(v___x_1463_, v___x_1462_);
v___x_1465_ = lean_uint32_to_nat(v___x_1464_);
v___y_1442_ = v___y_1450_;
v___y_1443_ = v___x_1465_;
goto v___jp_1441_;
}
}
}
else
{
lean_dec(v___x_1397_);
goto v___jp_1315_;
}
v___jp_1308_:
{
lean_object* v___x_1313_; 
v___x_1313_ = lean_nat_add(v_index_1301_, v_one_1306_);
lean_dec(v_index_1301_);
v_pos_1297_ = v_pos_1309_;
v_neg_1298_ = v_neg_1310_;
v_sp_1299_ = v_special_1311_;
v_nz_1300_ = v_negZero_1312_;
v_index_1301_ = v___x_1313_;
v_x_1302_ = v_n_1307_;
goto _start;
}
v___jp_1315_:
{
uint8_t v___x_1316_; 
v___x_1316_ = 1;
v_pos_1309_ = v_pos_1297_;
v_neg_1310_ = v_neg_1298_;
v_special_1311_ = v___x_1316_;
v_negZero_1312_ = v_nz_1300_;
goto v___jp_1308_;
}
v___jp_1317_:
{
lean_object* v___x_1323_; lean_object* v___x_1324_; uint8_t v___x_1325_; 
v___x_1323_ = lean_nat_add(v___y_1320_, v___y_1319_);
lean_dec(v___y_1320_);
v___x_1324_ = lean_array_get_size(v___y_1322_);
v___x_1325_ = lean_nat_dec_lt(v___x_1323_, v___x_1324_);
if (v___x_1325_ == 0)
{
lean_dec(v___x_1323_);
lean_dec(v___y_1321_);
v_pos_1309_ = v___y_1322_;
v_neg_1310_ = v_neg_1298_;
v_special_1311_ = v_sp_1299_;
v_negZero_1312_ = v___y_1318_;
goto v___jp_1308_;
}
else
{
lean_object* v_v_1326_; lean_object* v___x_1327_; lean_object* v_xs_x27_1328_; lean_object* v___x_1329_; lean_object* v___x_1330_; 
v_v_1326_ = lean_array_fget(v___y_1322_, v___x_1323_);
v___x_1327_ = lean_box(0);
v_xs_x27_1328_ = lean_array_fset(v___y_1322_, v___x_1323_, v___x_1327_);
v___x_1329_ = lean_nat_add(v_v_1326_, v___y_1321_);
lean_dec(v___y_1321_);
lean_dec(v_v_1326_);
v___x_1330_ = lean_array_fset(v_xs_x27_1328_, v___x_1323_, v___x_1329_);
lean_dec(v___x_1323_);
v_pos_1309_ = v___x_1330_;
v_neg_1310_ = v_neg_1298_;
v_special_1311_ = v_sp_1299_;
v_negZero_1312_ = v___y_1318_;
goto v___jp_1308_;
}
}
v___jp_1331_:
{
lean_object* v___x_1336_; lean_object* v___x_1337_; uint8_t v___x_1338_; 
v___x_1336_ = lean_nat_add(v___y_1333_, v___y_1332_);
lean_dec(v___y_1333_);
v___x_1337_ = lean_array_get_size(v___y_1335_);
v___x_1338_ = lean_nat_dec_lt(v___x_1336_, v___x_1337_);
if (v___x_1338_ == 0)
{
lean_dec(v___x_1336_);
lean_dec(v___y_1334_);
v_pos_1309_ = v_pos_1297_;
v_neg_1310_ = v___y_1335_;
v_special_1311_ = v_sp_1299_;
v_negZero_1312_ = v_isZero_1304_;
goto v___jp_1308_;
}
else
{
lean_object* v_v_1339_; lean_object* v___x_1340_; lean_object* v_xs_x27_1341_; lean_object* v___x_1342_; lean_object* v___x_1343_; 
v_v_1339_ = lean_array_fget(v___y_1335_, v___x_1336_);
v___x_1340_ = lean_box(0);
v_xs_x27_1341_ = lean_array_fset(v___y_1335_, v___x_1336_, v___x_1340_);
v___x_1342_ = lean_nat_add(v_v_1339_, v___y_1334_);
lean_dec(v___y_1334_);
lean_dec(v_v_1339_);
v___x_1343_ = lean_array_fset(v_xs_x27_1341_, v___x_1336_, v___x_1342_);
lean_dec(v___x_1336_);
v_pos_1309_ = v_pos_1297_;
v_neg_1310_ = v___x_1343_;
v_special_1311_ = v_sp_1299_;
v_negZero_1312_ = v_isZero_1304_;
goto v___jp_1308_;
}
}
v___jp_1344_:
{
uint8_t v___x_1348_; 
v___x_1348_ = lean_nat_dec_eq(v___y_1345_, v_zero_1303_);
if (v___x_1348_ == 0)
{
if (v___y_1347_ == 0)
{
uint64_t v___x_1349_; lean_object* v___x_1350_; lean_object* v___x_1351_; lean_object* v_l_1352_; lean_object* v___x_1353_; uint64_t v_r_1354_; uint64_t v___x_1355_; uint64_t v___x_1356_; uint64_t v___x_1357_; uint64_t v___x_1358_; uint64_t v___x_1359_; uint64_t v___x_1360_; lean_object* v_hi_1361_; lean_object* v___x_1362_; uint8_t v___x_1363_; 
v___x_1349_ = lean_uint64_of_nat(v___y_1345_);
lean_dec(v___y_1345_);
v___x_1350_ = lean_unsigned_to_nat(32u);
v___x_1351_ = lean_unsigned_to_nat(5u);
v_l_1352_ = lean_nat_shiftr(v___y_1346_, v___x_1351_);
v___x_1353_ = lean_nat_mod(v___y_1346_, v___x_1350_);
lean_dec(v___y_1346_);
v_r_1354_ = lean_uint64_of_nat(v___x_1353_);
lean_dec(v___x_1353_);
v___x_1355_ = 1ULL;
v___x_1356_ = 32ULL;
v___x_1357_ = lean_uint64_sub(v___x_1356_, v_r_1354_);
v___x_1358_ = lean_uint64_shift_left(v___x_1355_, v___x_1357_);
v___x_1359_ = lean_uint64_mod(v___x_1349_, v___x_1358_);
v___x_1360_ = lean_uint64_shift_right(v___x_1349_, v___x_1357_);
v_hi_1361_ = lean_uint64_to_nat(v___x_1360_);
v___x_1362_ = lean_array_get_size(v_pos_1297_);
v___x_1363_ = lean_nat_dec_lt(v_l_1352_, v___x_1362_);
if (v___x_1363_ == 0)
{
v___y_1318_ = v___y_1347_;
v___y_1319_ = v_one_1306_;
v___y_1320_ = v_l_1352_;
v___y_1321_ = v_hi_1361_;
v___y_1322_ = v_pos_1297_;
goto v___jp_1317_;
}
else
{
uint64_t v___x_1364_; lean_object* v_lo_1365_; lean_object* v_v_1366_; lean_object* v___x_1367_; lean_object* v_xs_x27_1368_; lean_object* v___x_1369_; lean_object* v___x_1370_; 
v___x_1364_ = lean_uint64_shift_left(v___x_1359_, v_r_1354_);
v_lo_1365_ = lean_uint64_to_nat(v___x_1364_);
v_v_1366_ = lean_array_fget(v_pos_1297_, v_l_1352_);
v___x_1367_ = lean_box(0);
v_xs_x27_1368_ = lean_array_fset(v_pos_1297_, v_l_1352_, v___x_1367_);
v___x_1369_ = lean_nat_add(v_v_1366_, v_lo_1365_);
lean_dec(v_lo_1365_);
lean_dec(v_v_1366_);
v___x_1370_ = lean_array_fset(v_xs_x27_1368_, v_l_1352_, v___x_1369_);
v___y_1318_ = v___y_1347_;
v___y_1319_ = v_one_1306_;
v___y_1320_ = v_l_1352_;
v___y_1321_ = v_hi_1361_;
v___y_1322_ = v___x_1370_;
goto v___jp_1317_;
}
}
else
{
uint64_t v___x_1371_; lean_object* v___x_1372_; lean_object* v___x_1373_; lean_object* v_l_1374_; lean_object* v___x_1375_; uint64_t v_r_1376_; uint64_t v___x_1377_; uint64_t v___x_1378_; uint64_t v___x_1379_; uint64_t v___x_1380_; uint64_t v___x_1381_; uint64_t v___x_1382_; lean_object* v_hi_1383_; lean_object* v___x_1384_; uint8_t v___x_1385_; 
v___x_1371_ = lean_uint64_of_nat(v___y_1345_);
lean_dec(v___y_1345_);
v___x_1372_ = lean_unsigned_to_nat(32u);
v___x_1373_ = lean_unsigned_to_nat(5u);
v_l_1374_ = lean_nat_shiftr(v___y_1346_, v___x_1373_);
v___x_1375_ = lean_nat_mod(v___y_1346_, v___x_1372_);
lean_dec(v___y_1346_);
v_r_1376_ = lean_uint64_of_nat(v___x_1375_);
lean_dec(v___x_1375_);
v___x_1377_ = 1ULL;
v___x_1378_ = 32ULL;
v___x_1379_ = lean_uint64_sub(v___x_1378_, v_r_1376_);
v___x_1380_ = lean_uint64_shift_left(v___x_1377_, v___x_1379_);
v___x_1381_ = lean_uint64_mod(v___x_1371_, v___x_1380_);
v___x_1382_ = lean_uint64_shift_right(v___x_1371_, v___x_1379_);
v_hi_1383_ = lean_uint64_to_nat(v___x_1382_);
v___x_1384_ = lean_array_get_size(v_neg_1298_);
v___x_1385_ = lean_nat_dec_lt(v_l_1374_, v___x_1384_);
if (v___x_1385_ == 0)
{
v___y_1332_ = v_one_1306_;
v___y_1333_ = v_l_1374_;
v___y_1334_ = v_hi_1383_;
v___y_1335_ = v_neg_1298_;
goto v___jp_1331_;
}
else
{
uint64_t v___x_1386_; lean_object* v_lo_1387_; lean_object* v_v_1388_; lean_object* v___x_1389_; lean_object* v_xs_x27_1390_; lean_object* v___x_1391_; lean_object* v___x_1392_; 
v___x_1386_ = lean_uint64_shift_left(v___x_1381_, v_r_1376_);
v_lo_1387_ = lean_uint64_to_nat(v___x_1386_);
v_v_1388_ = lean_array_fget(v_neg_1298_, v_l_1374_);
v___x_1389_ = lean_box(0);
v_xs_x27_1390_ = lean_array_fset(v_neg_1298_, v_l_1374_, v___x_1389_);
v___x_1391_ = lean_nat_add(v_v_1388_, v_lo_1387_);
lean_dec(v_lo_1387_);
lean_dec(v_v_1388_);
v___x_1392_ = lean_array_fset(v_xs_x27_1390_, v_l_1374_, v___x_1391_);
v___y_1332_ = v_one_1306_;
v___y_1333_ = v_l_1374_;
v___y_1334_ = v_hi_1383_;
v___y_1335_ = v___x_1392_;
goto v___jp_1331_;
}
}
}
else
{
lean_dec(v___y_1346_);
lean_dec(v___y_1345_);
if (v_nz_1300_ == 0)
{
v_pos_1309_ = v_pos_1297_;
v_neg_1310_ = v_neg_1298_;
v_special_1311_ = v_sp_1299_;
v_negZero_1312_ = v_nz_1300_;
goto v___jp_1308_;
}
else
{
v_pos_1309_ = v_pos_1297_;
v_neg_1310_ = v_neg_1298_;
v_special_1311_ = v_sp_1299_;
v_negZero_1312_ = v___y_1347_;
goto v___jp_1308_;
}
}
}
v___jp_1393_:
{
uint8_t v___x_1396_; 
v___x_1396_ = 1;
v___y_1345_ = v___y_1394_;
v___y_1346_ = v___y_1395_;
v___y_1347_ = v___x_1396_;
goto v___jp_1344_;
}
v___jp_1404_:
{
if (v___y_1405_ == 0)
{
if (v___y_1408_ == 0)
{
v___y_1345_ = v___y_1406_;
v___y_1346_ = v___y_1407_;
v___y_1347_ = v___x_1403_;
goto v___jp_1344_;
}
else
{
v___y_1394_ = v___y_1406_;
v___y_1395_ = v___y_1407_;
goto v___jp_1393_;
}
}
else
{
if (v___y_1408_ == 0)
{
v___y_1394_ = v___y_1406_;
v___y_1395_ = v___y_1407_;
goto v___jp_1393_;
}
else
{
v___y_1345_ = v___y_1406_;
v___y_1346_ = v___y_1407_;
v___y_1347_ = v___x_1403_;
goto v___jp_1344_;
}
}
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_dotLoop___boxed(lean_object* v_fa_1482_, lean_object* v_fb_1483_, lean_object* v_pos_1484_, lean_object* v_neg_1485_, lean_object* v_sp_1486_, lean_object* v_nz_1487_, lean_object* v_index_1488_, lean_object* v_x_1489_){
_start:
{
uint8_t v_sp_boxed_1490_; uint8_t v_nz_boxed_1491_; lean_object* v_res_1492_; 
v_sp_boxed_1490_ = lean_unbox(v_sp_1486_);
v_nz_boxed_1491_ = lean_unbox(v_nz_1487_);
v_res_1492_ = lp_competition_Submission_dotLoop(v_fa_1482_, v_fb_1483_, v_pos_1484_, v_neg_1485_, v_sp_boxed_1490_, v_nz_boxed_1491_, v_index_1488_, v_x_1489_);
return v_res_1492_;
}
}
LEAN_EXPORT uint32_t lp_competition_Submission_dotFn___lam__0(lean_object* v_fa_1493_, lean_object* v_i_1494_){
_start:
{
lean_object* v___x_1495_; uint32_t v___x_1496_; 
v___x_1495_ = lean_apply_1(v_fa_1493_, v_i_1494_);
v___x_1496_ = lean_unbox_uint32(v___x_1495_);
lean_dec(v___x_1495_);
return v___x_1496_;
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_dotFn___lam__0___boxed(lean_object* v_fa_1497_, lean_object* v_i_1498_){
_start:
{
uint32_t v_res_1499_; lean_object* v_r_1500_; 
v_res_1499_ = lp_competition_Submission_dotFn___lam__0(v_fa_1497_, v_i_1498_);
v_r_1500_ = lean_box_uint32(v_res_1499_);
return v_r_1500_;
}
}
LEAN_EXPORT uint32_t lp_competition_Submission_dotFn___lam__1(lean_object* v_fb_1501_, lean_object* v_i_1502_){
_start:
{
lean_object* v___x_1503_; uint32_t v___x_1504_; 
v___x_1503_ = lean_apply_1(v_fb_1501_, v_i_1502_);
v___x_1504_ = lean_unbox_uint32(v___x_1503_);
lean_dec(v___x_1503_);
return v___x_1504_;
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_dotFn___lam__1___boxed(lean_object* v_fb_1505_, lean_object* v_i_1506_){
_start:
{
uint32_t v_res_1507_; lean_object* v_r_1508_; 
v_res_1507_ = lp_competition_Submission_dotFn___lam__1(v_fb_1505_, v_i_1506_);
v_r_1508_ = lean_box_uint32(v_res_1507_);
return v_r_1508_;
}
}
static lean_object* _init_lp_competition_Submission_dotFn___closed__0(void){
_start:
{
lean_object* v___x_1509_; lean_object* v___x_1510_; 
v___x_1509_ = lean_unsigned_to_nat(298u);
v___x_1510_ = lean_nat_to_int(v___x_1509_);
return v___x_1510_;
}
}
static lean_object* _init_lp_competition_Submission_dotFn___closed__1(void){
_start:
{
lean_object* v___x_1511_; lean_object* v___x_1512_; 
v___x_1511_ = lean_obj_once(&lp_competition_Submission_dotFn___closed__0, &lp_competition_Submission_dotFn___closed__0_once, _init_lp_competition_Submission_dotFn___closed__0);
v___x_1512_ = lean_int_neg(v___x_1511_);
return v___x_1512_;
}
}
LEAN_EXPORT uint32_t lp_competition_Submission_dotFn(lean_object* v_n_1513_, lean_object* v_fa_1514_, lean_object* v_fb_1515_){
_start:
{
lean_object* v___x_1516_; lean_object* v___x_1517_; uint8_t v___x_1518_; uint8_t v___x_1519_; lean_object* v_acc_1520_; uint8_t v_special_1521_; 
v___x_1516_ = lean_unsigned_to_nat(0u);
v___x_1517_ = lean_obj_once(&lp_competition_Submission_Acc_empty___closed__0, &lp_competition_Submission_Acc_empty___closed__0_once, _init_lp_competition_Submission_Acc_empty___closed__0);
v___x_1518_ = 0;
v___x_1519_ = 1;
lean_inc(v_n_1513_);
lean_inc_ref(v_fb_1515_);
lean_inc_ref(v_fa_1514_);
v_acc_1520_ = lp_competition_Submission_dotLoop(v_fa_1514_, v_fb_1515_, v___x_1517_, v___x_1517_, v___x_1518_, v___x_1519_, v___x_1516_, v_n_1513_);
v_special_1521_ = lean_ctor_get_uint8(v_acc_1520_, sizeof(void*)*2);
if (v_special_1521_ == 0)
{
lean_object* v_pos_1522_; lean_object* v_neg_1523_; uint8_t v_negZero_1524_; lean_object* v___x_1525_; uint8_t v___x_1526_; 
lean_dec_ref(v_fb_1515_);
lean_dec_ref(v_fa_1514_);
v_pos_1522_ = lean_ctor_get(v_acc_1520_, 0);
lean_inc_ref(v_pos_1522_);
v_neg_1523_ = lean_ctor_get(v_acc_1520_, 1);
lean_inc_ref(v_neg_1523_);
v_negZero_1524_ = lean_ctor_get_uint8(v_acc_1520_, sizeof(void*)*2 + 1);
lean_dec_ref(v_acc_1520_);
v___x_1525_ = lean_obj_once(&lp_competition_Submission_dotFn___closed__1, &lp_competition_Submission_dotFn___closed__1_once, _init_lp_competition_Submission_dotFn___closed__1);
v___x_1526_ = lean_nat_dec_eq(v_n_1513_, v___x_1516_);
lean_dec(v_n_1513_);
if (v___x_1526_ == 0)
{
uint32_t v___x_1527_; 
v___x_1527_ = lp_competition_Submission_finishFast(v_pos_1522_, v_neg_1523_, v___x_1525_, v_negZero_1524_);
lean_dec_ref(v_neg_1523_);
lean_dec_ref(v_pos_1522_);
return v___x_1527_;
}
else
{
uint32_t v___x_1528_; 
v___x_1528_ = lp_competition_Submission_finishFast(v_pos_1522_, v_neg_1523_, v___x_1525_, v___x_1518_);
lean_dec_ref(v_neg_1523_);
lean_dec_ref(v_pos_1522_);
return v___x_1528_;
}
}
else
{
lean_object* v___f_1529_; lean_object* v___f_1530_; lean_object* v___x_1531_; lean_object* v___x_1532_; uint32_t v___x_1533_; 
lean_dec_ref(v_acc_1520_);
v___f_1529_ = lean_alloc_closure((void*)(lp_competition_Submission_dotFn___lam__0___boxed), 2, 1);
lean_closure_set(v___f_1529_, 0, v_fa_1514_);
v___f_1530_ = lean_alloc_closure((void*)(lp_competition_Submission_dotFn___lam__1___boxed), 2, 1);
lean_closure_set(v___f_1530_, 0, v_fb_1515_);
lean_inc(v_n_1513_);
v___x_1531_ = l_Array_ofFn___redArg(v_n_1513_, v___f_1529_);
v___x_1532_ = l_Array_ofFn___redArg(v_n_1513_, v___f_1530_);
v___x_1533_ = lp_competition_ExactRuntime_dotSpec(v___x_1531_, v___x_1532_);
return v___x_1533_;
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_dotFn___boxed(lean_object* v_n_1534_, lean_object* v_fa_1535_, lean_object* v_fb_1536_){
_start:
{
uint32_t v_res_1537_; lean_object* v_r_1538_; 
v_res_1537_ = lp_competition_Submission_dotFn(v_n_1534_, v_fa_1535_, v_fb_1536_);
v_r_1538_ = lean_box_uint32(v_res_1537_);
return v_r_1538_;
}
}
static lean_object* _init_lp_competition_Submission_dotX___lam__0___boxed__const__1(void){
_start:
{
uint32_t v___x_1539_; lean_object* v___x_1540_; 
v___x_1539_ = 0;
v___x_1540_ = lean_box_uint32(v___x_1539_);
return v___x_1540_;
}
}
LEAN_EXPORT uint32_t lp_competition_Submission_dotX___lam__0(lean_object* v_a_1541_, lean_object* v_i_1542_){
_start:
{
lean_object* v___x_1543_; lean_object* v___x_1544_; uint32_t v___x_1545_; 
v___x_1543_ = lp_competition_Submission_dotX___lam__0___boxed__const__1;
v___x_1544_ = lean_array_get_borrowed(v___x_1543_, v_a_1541_, v_i_1542_);
v___x_1545_ = lean_unbox_uint32(v___x_1544_);
return v___x_1545_;
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_dotX___lam__0___boxed(lean_object* v_a_1546_, lean_object* v_i_1547_){
_start:
{
uint32_t v_res_1548_; lean_object* v_r_1549_; 
v_res_1548_ = lp_competition_Submission_dotX___lam__0(v_a_1546_, v_i_1547_);
lean_dec(v_i_1547_);
lean_dec_ref(v_a_1546_);
v_r_1549_ = lean_box_uint32(v_res_1548_);
return v_r_1549_;
}
}
LEAN_EXPORT uint32_t lp_competition_Submission_dotX___lam__1(lean_object* v_b_1550_, lean_object* v_i_1551_){
_start:
{
lean_object* v___x_1552_; lean_object* v___x_1553_; uint32_t v___x_1554_; 
v___x_1552_ = lp_competition_Submission_dotX___lam__0___boxed__const__1;
v___x_1553_ = lean_array_get_borrowed(v___x_1552_, v_b_1550_, v_i_1551_);
v___x_1554_ = lean_unbox_uint32(v___x_1553_);
return v___x_1554_;
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_dotX___lam__1___boxed(lean_object* v_b_1555_, lean_object* v_i_1556_){
_start:
{
uint32_t v_res_1557_; lean_object* v_r_1558_; 
v_res_1557_ = lp_competition_Submission_dotX___lam__1(v_b_1555_, v_i_1556_);
lean_dec(v_i_1556_);
lean_dec_ref(v_b_1555_);
v_r_1558_ = lean_box_uint32(v_res_1557_);
return v_r_1558_;
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_dotLoop___at___00Submission_dotX_spec__0(lean_object* v_a_1559_, lean_object* v_b_1560_, lean_object* v_pos_1561_, lean_object* v_neg_1562_, uint8_t v_sp_1563_, uint8_t v_nz_1564_, lean_object* v_index_1565_, lean_object* v_x_1566_){
_start:
{
lean_object* v_zero_1567_; uint8_t v_isZero_1568_; 
v_zero_1567_ = lean_unsigned_to_nat(0u);
v_isZero_1568_ = lean_nat_dec_eq(v_x_1566_, v_zero_1567_);
if (v_isZero_1568_ == 1)
{
lean_object* v___x_1569_; 
lean_dec(v_x_1566_);
lean_dec(v_index_1565_);
v___x_1569_ = lean_alloc_ctor(0, 2, 2);
lean_ctor_set(v___x_1569_, 0, v_pos_1561_);
lean_ctor_set(v___x_1569_, 1, v_neg_1562_);
lean_ctor_set_uint8(v___x_1569_, sizeof(void*)*2, v_sp_1563_);
lean_ctor_set_uint8(v___x_1569_, sizeof(void*)*2 + 1, v_nz_1564_);
return v___x_1569_;
}
else
{
lean_object* v_one_1570_; lean_object* v_n_1571_; lean_object* v_pos_1573_; lean_object* v_neg_1574_; uint8_t v_special_1575_; uint8_t v_negZero_1576_; lean_object* v___y_1582_; lean_object* v___y_1583_; uint8_t v___y_1584_; lean_object* v___y_1585_; lean_object* v___y_1586_; lean_object* v___y_1596_; lean_object* v___y_1597_; lean_object* v___y_1598_; lean_object* v___y_1599_; lean_object* v___y_1609_; lean_object* v___y_1610_; uint8_t v___y_1611_; lean_object* v___y_1658_; lean_object* v___y_1659_; uint32_t v___x_1661_; lean_object* v___x_1662_; lean_object* v___x_1663_; uint32_t v___x_1664_; uint32_t v___x_1665_; uint32_t v___x_1666_; uint32_t v___x_1667_; uint32_t v___x_1668_; uint8_t v___x_1669_; lean_object* v___y_1671_; uint8_t v___y_1672_; lean_object* v___y_1673_; uint8_t v___y_1674_; 
v_one_1570_ = lean_unsigned_to_nat(1u);
v_n_1571_ = lean_nat_sub(v_x_1566_, v_one_1570_);
lean_dec(v_x_1566_);
v___x_1661_ = 0;
v___x_1662_ = lp_competition_Submission_dotX___lam__0___boxed__const__1;
v___x_1663_ = lean_array_get_borrowed(v___x_1662_, v_a_1559_, v_index_1565_);
v___x_1664_ = 23;
v___x_1665_ = lean_unbox_uint32(v___x_1663_);
v___x_1666_ = lean_uint32_shift_right(v___x_1665_, v___x_1664_);
v___x_1667_ = 255;
v___x_1668_ = lean_uint32_land(v___x_1666_, v___x_1667_);
v___x_1669_ = lean_uint32_dec_eq(v___x_1668_, v___x_1667_);
if (v___x_1669_ == 0)
{
lean_object* v___x_1675_; lean_object* v___x_1676_; lean_object* v___y_1678_; lean_object* v___y_1679_; uint8_t v___y_1680_; lean_object* v___y_1687_; lean_object* v___y_1688_; lean_object* v___y_1689_; lean_object* v___y_1697_; lean_object* v___y_1698_; lean_object* v___y_1706_; lean_object* v___y_1707_; lean_object* v___y_1713_; uint32_t v___x_1728_; uint32_t v___x_1729_; uint32_t v___x_1730_; uint8_t v___x_1731_; 
v___x_1675_ = lp_competition_Submission_dotX___lam__0___boxed__const__1;
v___x_1676_ = lean_array_get_borrowed(v___x_1675_, v_b_1560_, v_index_1565_);
v___x_1728_ = lean_unbox_uint32(v___x_1676_);
v___x_1729_ = lean_uint32_shift_right(v___x_1728_, v___x_1664_);
v___x_1730_ = lean_uint32_land(v___x_1729_, v___x_1667_);
v___x_1731_ = lean_uint32_dec_eq(v___x_1730_, v___x_1667_);
if (v___x_1731_ == 0)
{
uint8_t v___x_1732_; 
v___x_1732_ = lean_uint32_dec_eq(v___x_1668_, v___x_1661_);
if (v___x_1732_ == 0)
{
lean_object* v___x_1733_; uint32_t v___x_1734_; uint32_t v___x_1735_; uint32_t v___x_1736_; lean_object* v___x_1737_; lean_object* v___x_1738_; 
v___x_1733_ = lean_unsigned_to_nat(8388608u);
v___x_1734_ = 8388607;
v___x_1735_ = lean_unbox_uint32(v___x_1663_);
v___x_1736_ = lean_uint32_land(v___x_1735_, v___x_1734_);
v___x_1737_ = lean_uint32_to_nat(v___x_1736_);
v___x_1738_ = lean_nat_add(v___x_1733_, v___x_1737_);
lean_dec(v___x_1737_);
v___y_1713_ = v___x_1738_;
goto v___jp_1712_;
}
else
{
uint32_t v___x_1739_; uint32_t v___x_1740_; uint32_t v___x_1741_; lean_object* v___x_1742_; 
v___x_1739_ = 8388607;
v___x_1740_ = lean_unbox_uint32(v___x_1663_);
v___x_1741_ = lean_uint32_land(v___x_1740_, v___x_1739_);
v___x_1742_ = lean_uint32_to_nat(v___x_1741_);
v___y_1713_ = v___x_1742_;
goto v___jp_1712_;
}
}
else
{
goto v___jp_1579_;
}
v___jp_1677_:
{
uint32_t v___x_1681_; uint32_t v___x_1682_; uint32_t v___x_1683_; uint8_t v___x_1684_; 
v___x_1681_ = 2147483648;
v___x_1682_ = lean_unbox_uint32(v___x_1676_);
v___x_1683_ = lean_uint32_land(v___x_1682_, v___x_1681_);
v___x_1684_ = lean_uint32_dec_eq(v___x_1683_, v___x_1661_);
if (v___x_1684_ == 0)
{
uint8_t v___x_1685_; 
v___x_1685_ = 1;
v___y_1671_ = v___y_1678_;
v___y_1672_ = v___y_1680_;
v___y_1673_ = v___y_1679_;
v___y_1674_ = v___x_1685_;
goto v___jp_1670_;
}
else
{
v___y_1671_ = v___y_1678_;
v___y_1672_ = v___y_1680_;
v___y_1673_ = v___y_1679_;
v___y_1674_ = v___x_1669_;
goto v___jp_1670_;
}
}
v___jp_1686_:
{
lean_object* v___x_1690_; uint32_t v___x_1691_; uint32_t v___x_1692_; uint32_t v___x_1693_; uint8_t v___x_1694_; 
v___x_1690_ = lean_nat_add(v___y_1687_, v___y_1689_);
lean_dec(v___y_1689_);
lean_dec(v___y_1687_);
v___x_1691_ = 2147483648;
v___x_1692_ = lean_unbox_uint32(v___x_1663_);
v___x_1693_ = lean_uint32_land(v___x_1692_, v___x_1691_);
v___x_1694_ = lean_uint32_dec_eq(v___x_1693_, v___x_1661_);
if (v___x_1694_ == 0)
{
uint8_t v___x_1695_; 
v___x_1695_ = 1;
v___y_1678_ = v___x_1690_;
v___y_1679_ = v___y_1688_;
v___y_1680_ = v___x_1695_;
goto v___jp_1677_;
}
else
{
v___y_1678_ = v___x_1690_;
v___y_1679_ = v___y_1688_;
v___y_1680_ = v___x_1669_;
goto v___jp_1677_;
}
}
v___jp_1696_:
{
uint32_t v___x_1699_; uint32_t v___x_1700_; uint32_t v___x_1701_; uint8_t v___x_1702_; 
v___x_1699_ = lean_unbox_uint32(v___x_1676_);
v___x_1700_ = lean_uint32_shift_right(v___x_1699_, v___x_1664_);
v___x_1701_ = lean_uint32_land(v___x_1700_, v___x_1667_);
v___x_1702_ = lean_uint32_dec_eq(v___x_1701_, v___x_1661_);
if (v___x_1702_ == 0)
{
lean_object* v___x_1703_; lean_object* v___x_1704_; 
v___x_1703_ = lean_uint32_to_nat(v___x_1701_);
v___x_1704_ = lean_nat_sub(v___x_1703_, v_one_1570_);
lean_dec(v___x_1703_);
v___y_1687_ = v___y_1698_;
v___y_1688_ = v___y_1697_;
v___y_1689_ = v___x_1704_;
goto v___jp_1686_;
}
else
{
v___y_1687_ = v___y_1698_;
v___y_1688_ = v___y_1697_;
v___y_1689_ = v_zero_1567_;
goto v___jp_1686_;
}
}
v___jp_1705_:
{
lean_object* v___x_1708_; uint8_t v___x_1709_; 
v___x_1708_ = lean_nat_mul(v___y_1706_, v___y_1707_);
lean_dec(v___y_1707_);
lean_dec(v___y_1706_);
v___x_1709_ = lean_uint32_dec_eq(v___x_1668_, v___x_1661_);
if (v___x_1709_ == 0)
{
lean_object* v___x_1710_; lean_object* v___x_1711_; 
v___x_1710_ = lean_uint32_to_nat(v___x_1668_);
v___x_1711_ = lean_nat_sub(v___x_1710_, v_one_1570_);
lean_dec(v___x_1710_);
v___y_1697_ = v___x_1708_;
v___y_1698_ = v___x_1711_;
goto v___jp_1696_;
}
else
{
v___y_1697_ = v___x_1708_;
v___y_1698_ = v_zero_1567_;
goto v___jp_1696_;
}
}
v___jp_1712_:
{
uint32_t v___x_1714_; uint32_t v___x_1715_; uint32_t v___x_1716_; uint8_t v___x_1717_; 
v___x_1714_ = lean_unbox_uint32(v___x_1676_);
v___x_1715_ = lean_uint32_shift_right(v___x_1714_, v___x_1664_);
v___x_1716_ = lean_uint32_land(v___x_1715_, v___x_1667_);
v___x_1717_ = lean_uint32_dec_eq(v___x_1716_, v___x_1661_);
if (v___x_1717_ == 0)
{
lean_object* v___x_1718_; uint32_t v___x_1719_; uint32_t v___x_1720_; uint32_t v___x_1721_; lean_object* v___x_1722_; lean_object* v___x_1723_; 
v___x_1718_ = lean_unsigned_to_nat(8388608u);
v___x_1719_ = 8388607;
v___x_1720_ = lean_unbox_uint32(v___x_1676_);
v___x_1721_ = lean_uint32_land(v___x_1720_, v___x_1719_);
v___x_1722_ = lean_uint32_to_nat(v___x_1721_);
v___x_1723_ = lean_nat_add(v___x_1718_, v___x_1722_);
lean_dec(v___x_1722_);
v___y_1706_ = v___y_1713_;
v___y_1707_ = v___x_1723_;
goto v___jp_1705_;
}
else
{
uint32_t v___x_1724_; uint32_t v___x_1725_; uint32_t v___x_1726_; lean_object* v___x_1727_; 
v___x_1724_ = 8388607;
v___x_1725_ = lean_unbox_uint32(v___x_1676_);
v___x_1726_ = lean_uint32_land(v___x_1725_, v___x_1724_);
v___x_1727_ = lean_uint32_to_nat(v___x_1726_);
v___y_1706_ = v___y_1713_;
v___y_1707_ = v___x_1727_;
goto v___jp_1705_;
}
}
}
else
{
goto v___jp_1579_;
}
v___jp_1572_:
{
lean_object* v___x_1577_; 
v___x_1577_ = lean_nat_add(v_index_1565_, v_one_1570_);
lean_dec(v_index_1565_);
v_pos_1561_ = v_pos_1573_;
v_neg_1562_ = v_neg_1574_;
v_sp_1563_ = v_special_1575_;
v_nz_1564_ = v_negZero_1576_;
v_index_1565_ = v___x_1577_;
v_x_1566_ = v_n_1571_;
goto _start;
}
v___jp_1579_:
{
uint8_t v___x_1580_; 
v___x_1580_ = 1;
v_pos_1573_ = v_pos_1561_;
v_neg_1574_ = v_neg_1562_;
v_special_1575_ = v___x_1580_;
v_negZero_1576_ = v_nz_1564_;
goto v___jp_1572_;
}
v___jp_1581_:
{
lean_object* v___x_1587_; lean_object* v___x_1588_; uint8_t v___x_1589_; 
v___x_1587_ = lean_nat_add(v___y_1583_, v___y_1585_);
lean_dec(v___y_1583_);
v___x_1588_ = lean_array_get_size(v___y_1586_);
v___x_1589_ = lean_nat_dec_lt(v___x_1587_, v___x_1588_);
if (v___x_1589_ == 0)
{
lean_dec(v___x_1587_);
lean_dec(v___y_1582_);
v_pos_1573_ = v___y_1586_;
v_neg_1574_ = v_neg_1562_;
v_special_1575_ = v_sp_1563_;
v_negZero_1576_ = v___y_1584_;
goto v___jp_1572_;
}
else
{
lean_object* v_v_1590_; lean_object* v___x_1591_; lean_object* v_xs_x27_1592_; lean_object* v___x_1593_; lean_object* v___x_1594_; 
v_v_1590_ = lean_array_fget(v___y_1586_, v___x_1587_);
v___x_1591_ = lean_box(0);
v_xs_x27_1592_ = lean_array_fset(v___y_1586_, v___x_1587_, v___x_1591_);
v___x_1593_ = lean_nat_add(v_v_1590_, v___y_1582_);
lean_dec(v___y_1582_);
lean_dec(v_v_1590_);
v___x_1594_ = lean_array_fset(v_xs_x27_1592_, v___x_1587_, v___x_1593_);
lean_dec(v___x_1587_);
v_pos_1573_ = v___x_1594_;
v_neg_1574_ = v_neg_1562_;
v_special_1575_ = v_sp_1563_;
v_negZero_1576_ = v___y_1584_;
goto v___jp_1572_;
}
}
v___jp_1595_:
{
lean_object* v___x_1600_; lean_object* v___x_1601_; uint8_t v___x_1602_; 
v___x_1600_ = lean_nat_add(v___y_1597_, v___y_1596_);
lean_dec(v___y_1597_);
v___x_1601_ = lean_array_get_size(v___y_1599_);
v___x_1602_ = lean_nat_dec_lt(v___x_1600_, v___x_1601_);
if (v___x_1602_ == 0)
{
lean_dec(v___x_1600_);
lean_dec(v___y_1598_);
v_pos_1573_ = v_pos_1561_;
v_neg_1574_ = v___y_1599_;
v_special_1575_ = v_sp_1563_;
v_negZero_1576_ = v_isZero_1568_;
goto v___jp_1572_;
}
else
{
lean_object* v_v_1603_; lean_object* v___x_1604_; lean_object* v_xs_x27_1605_; lean_object* v___x_1606_; lean_object* v___x_1607_; 
v_v_1603_ = lean_array_fget(v___y_1599_, v___x_1600_);
v___x_1604_ = lean_box(0);
v_xs_x27_1605_ = lean_array_fset(v___y_1599_, v___x_1600_, v___x_1604_);
v___x_1606_ = lean_nat_add(v_v_1603_, v___y_1598_);
lean_dec(v___y_1598_);
lean_dec(v_v_1603_);
v___x_1607_ = lean_array_fset(v_xs_x27_1605_, v___x_1600_, v___x_1606_);
lean_dec(v___x_1600_);
v_pos_1573_ = v_pos_1561_;
v_neg_1574_ = v___x_1607_;
v_special_1575_ = v_sp_1563_;
v_negZero_1576_ = v_isZero_1568_;
goto v___jp_1572_;
}
}
v___jp_1608_:
{
uint8_t v___x_1612_; 
v___x_1612_ = lean_nat_dec_eq(v___y_1610_, v_zero_1567_);
if (v___x_1612_ == 0)
{
if (v___y_1611_ == 0)
{
uint64_t v___x_1613_; lean_object* v___x_1614_; lean_object* v___x_1615_; lean_object* v_l_1616_; lean_object* v___x_1617_; uint64_t v_r_1618_; uint64_t v___x_1619_; uint64_t v___x_1620_; uint64_t v___x_1621_; uint64_t v___x_1622_; uint64_t v___x_1623_; uint64_t v___x_1624_; lean_object* v_hi_1625_; lean_object* v___x_1626_; uint8_t v___x_1627_; 
v___x_1613_ = lean_uint64_of_nat(v___y_1610_);
lean_dec(v___y_1610_);
v___x_1614_ = lean_unsigned_to_nat(32u);
v___x_1615_ = lean_unsigned_to_nat(5u);
v_l_1616_ = lean_nat_shiftr(v___y_1609_, v___x_1615_);
v___x_1617_ = lean_nat_mod(v___y_1609_, v___x_1614_);
lean_dec(v___y_1609_);
v_r_1618_ = lean_uint64_of_nat(v___x_1617_);
lean_dec(v___x_1617_);
v___x_1619_ = 1ULL;
v___x_1620_ = 32ULL;
v___x_1621_ = lean_uint64_sub(v___x_1620_, v_r_1618_);
v___x_1622_ = lean_uint64_shift_left(v___x_1619_, v___x_1621_);
v___x_1623_ = lean_uint64_mod(v___x_1613_, v___x_1622_);
v___x_1624_ = lean_uint64_shift_right(v___x_1613_, v___x_1621_);
v_hi_1625_ = lean_uint64_to_nat(v___x_1624_);
v___x_1626_ = lean_array_get_size(v_pos_1561_);
v___x_1627_ = lean_nat_dec_lt(v_l_1616_, v___x_1626_);
if (v___x_1627_ == 0)
{
v___y_1582_ = v_hi_1625_;
v___y_1583_ = v_l_1616_;
v___y_1584_ = v___y_1611_;
v___y_1585_ = v_one_1570_;
v___y_1586_ = v_pos_1561_;
goto v___jp_1581_;
}
else
{
uint64_t v___x_1628_; lean_object* v_lo_1629_; lean_object* v_v_1630_; lean_object* v___x_1631_; lean_object* v_xs_x27_1632_; lean_object* v___x_1633_; lean_object* v___x_1634_; 
v___x_1628_ = lean_uint64_shift_left(v___x_1623_, v_r_1618_);
v_lo_1629_ = lean_uint64_to_nat(v___x_1628_);
v_v_1630_ = lean_array_fget(v_pos_1561_, v_l_1616_);
v___x_1631_ = lean_box(0);
v_xs_x27_1632_ = lean_array_fset(v_pos_1561_, v_l_1616_, v___x_1631_);
v___x_1633_ = lean_nat_add(v_v_1630_, v_lo_1629_);
lean_dec(v_lo_1629_);
lean_dec(v_v_1630_);
v___x_1634_ = lean_array_fset(v_xs_x27_1632_, v_l_1616_, v___x_1633_);
v___y_1582_ = v_hi_1625_;
v___y_1583_ = v_l_1616_;
v___y_1584_ = v___y_1611_;
v___y_1585_ = v_one_1570_;
v___y_1586_ = v___x_1634_;
goto v___jp_1581_;
}
}
else
{
uint64_t v___x_1635_; lean_object* v___x_1636_; lean_object* v___x_1637_; lean_object* v_l_1638_; lean_object* v___x_1639_; uint64_t v_r_1640_; uint64_t v___x_1641_; uint64_t v___x_1642_; uint64_t v___x_1643_; uint64_t v___x_1644_; uint64_t v___x_1645_; uint64_t v___x_1646_; lean_object* v_hi_1647_; lean_object* v___x_1648_; uint8_t v___x_1649_; 
v___x_1635_ = lean_uint64_of_nat(v___y_1610_);
lean_dec(v___y_1610_);
v___x_1636_ = lean_unsigned_to_nat(32u);
v___x_1637_ = lean_unsigned_to_nat(5u);
v_l_1638_ = lean_nat_shiftr(v___y_1609_, v___x_1637_);
v___x_1639_ = lean_nat_mod(v___y_1609_, v___x_1636_);
lean_dec(v___y_1609_);
v_r_1640_ = lean_uint64_of_nat(v___x_1639_);
lean_dec(v___x_1639_);
v___x_1641_ = 1ULL;
v___x_1642_ = 32ULL;
v___x_1643_ = lean_uint64_sub(v___x_1642_, v_r_1640_);
v___x_1644_ = lean_uint64_shift_left(v___x_1641_, v___x_1643_);
v___x_1645_ = lean_uint64_mod(v___x_1635_, v___x_1644_);
v___x_1646_ = lean_uint64_shift_right(v___x_1635_, v___x_1643_);
v_hi_1647_ = lean_uint64_to_nat(v___x_1646_);
v___x_1648_ = lean_array_get_size(v_neg_1562_);
v___x_1649_ = lean_nat_dec_lt(v_l_1638_, v___x_1648_);
if (v___x_1649_ == 0)
{
v___y_1596_ = v_one_1570_;
v___y_1597_ = v_l_1638_;
v___y_1598_ = v_hi_1647_;
v___y_1599_ = v_neg_1562_;
goto v___jp_1595_;
}
else
{
uint64_t v___x_1650_; lean_object* v_lo_1651_; lean_object* v_v_1652_; lean_object* v___x_1653_; lean_object* v_xs_x27_1654_; lean_object* v___x_1655_; lean_object* v___x_1656_; 
v___x_1650_ = lean_uint64_shift_left(v___x_1645_, v_r_1640_);
v_lo_1651_ = lean_uint64_to_nat(v___x_1650_);
v_v_1652_ = lean_array_fget(v_neg_1562_, v_l_1638_);
v___x_1653_ = lean_box(0);
v_xs_x27_1654_ = lean_array_fset(v_neg_1562_, v_l_1638_, v___x_1653_);
v___x_1655_ = lean_nat_add(v_v_1652_, v_lo_1651_);
lean_dec(v_lo_1651_);
lean_dec(v_v_1652_);
v___x_1656_ = lean_array_fset(v_xs_x27_1654_, v_l_1638_, v___x_1655_);
v___y_1596_ = v_one_1570_;
v___y_1597_ = v_l_1638_;
v___y_1598_ = v_hi_1647_;
v___y_1599_ = v___x_1656_;
goto v___jp_1595_;
}
}
}
else
{
lean_dec(v___y_1610_);
lean_dec(v___y_1609_);
if (v_nz_1564_ == 0)
{
v_pos_1573_ = v_pos_1561_;
v_neg_1574_ = v_neg_1562_;
v_special_1575_ = v_sp_1563_;
v_negZero_1576_ = v_nz_1564_;
goto v___jp_1572_;
}
else
{
v_pos_1573_ = v_pos_1561_;
v_neg_1574_ = v_neg_1562_;
v_special_1575_ = v_sp_1563_;
v_negZero_1576_ = v___y_1611_;
goto v___jp_1572_;
}
}
}
v___jp_1657_:
{
uint8_t v___x_1660_; 
v___x_1660_ = 1;
v___y_1609_ = v___y_1658_;
v___y_1610_ = v___y_1659_;
v___y_1611_ = v___x_1660_;
goto v___jp_1608_;
}
v___jp_1670_:
{
if (v___y_1672_ == 0)
{
if (v___y_1674_ == 0)
{
v___y_1609_ = v___y_1671_;
v___y_1610_ = v___y_1673_;
v___y_1611_ = v___x_1669_;
goto v___jp_1608_;
}
else
{
v___y_1658_ = v___y_1671_;
v___y_1659_ = v___y_1673_;
goto v___jp_1657_;
}
}
else
{
if (v___y_1674_ == 0)
{
v___y_1658_ = v___y_1671_;
v___y_1659_ = v___y_1673_;
goto v___jp_1657_;
}
else
{
v___y_1609_ = v___y_1671_;
v___y_1610_ = v___y_1673_;
v___y_1611_ = v___x_1669_;
goto v___jp_1608_;
}
}
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_dotLoop___at___00Submission_dotX_spec__0___boxed(lean_object* v_a_1743_, lean_object* v_b_1744_, lean_object* v_pos_1745_, lean_object* v_neg_1746_, lean_object* v_sp_1747_, lean_object* v_nz_1748_, lean_object* v_index_1749_, lean_object* v_x_1750_){
_start:
{
uint8_t v_sp_boxed_1751_; uint8_t v_nz_boxed_1752_; lean_object* v_res_1753_; 
v_sp_boxed_1751_ = lean_unbox(v_sp_1747_);
v_nz_boxed_1752_ = lean_unbox(v_nz_1748_);
v_res_1753_ = lp_competition_Submission_dotLoop___at___00Submission_dotX_spec__0(v_a_1743_, v_b_1744_, v_pos_1745_, v_neg_1746_, v_sp_boxed_1751_, v_nz_boxed_1752_, v_index_1749_, v_x_1750_);
lean_dec_ref(v_b_1744_);
lean_dec_ref(v_a_1743_);
return v_res_1753_;
}
}
LEAN_EXPORT uint32_t lp_competition_Submission_dotX(lean_object* v_a_1754_, lean_object* v_b_1755_){
_start:
{
lean_object* v___x_1756_; lean_object* v___x_1757_; uint8_t v___x_1758_; 
v___x_1756_ = lean_array_get_size(v_a_1754_);
v___x_1757_ = lean_array_get_size(v_b_1755_);
v___x_1758_ = lean_nat_dec_eq(v___x_1756_, v___x_1757_);
if (v___x_1758_ == 0)
{
uint32_t v___x_1759_; 
v___x_1759_ = lp_competition_ExactRuntime_dotSpec(v_a_1754_, v_b_1755_);
return v___x_1759_;
}
else
{
lean_object* v___x_1760_; lean_object* v___x_1761_; uint8_t v___x_1762_; lean_object* v_acc_1763_; uint8_t v_special_1764_; 
v___x_1760_ = lean_unsigned_to_nat(0u);
v___x_1761_ = lean_obj_once(&lp_competition_Submission_Acc_empty___closed__0, &lp_competition_Submission_Acc_empty___closed__0_once, _init_lp_competition_Submission_Acc_empty___closed__0);
v___x_1762_ = 0;
v_acc_1763_ = lp_competition_Submission_dotLoop___at___00Submission_dotX_spec__0(v_a_1754_, v_b_1755_, v___x_1761_, v___x_1761_, v___x_1762_, v___x_1758_, v___x_1760_, v___x_1756_);
v_special_1764_ = lean_ctor_get_uint8(v_acc_1763_, sizeof(void*)*2);
if (v_special_1764_ == 0)
{
lean_object* v_pos_1765_; lean_object* v_neg_1766_; uint8_t v_negZero_1767_; lean_object* v___x_1768_; uint8_t v___x_1769_; 
lean_dec_ref(v_b_1755_);
lean_dec_ref(v_a_1754_);
v_pos_1765_ = lean_ctor_get(v_acc_1763_, 0);
lean_inc_ref(v_pos_1765_);
v_neg_1766_ = lean_ctor_get(v_acc_1763_, 1);
lean_inc_ref(v_neg_1766_);
v_negZero_1767_ = lean_ctor_get_uint8(v_acc_1763_, sizeof(void*)*2 + 1);
lean_dec_ref(v_acc_1763_);
v___x_1768_ = lean_obj_once(&lp_competition_Submission_dotFn___closed__1, &lp_competition_Submission_dotFn___closed__1_once, _init_lp_competition_Submission_dotFn___closed__1);
v___x_1769_ = lean_nat_dec_eq(v___x_1756_, v___x_1760_);
if (v___x_1769_ == 0)
{
if (v___x_1758_ == 0)
{
uint32_t v___x_1770_; 
v___x_1770_ = lp_competition_Submission_finishFast(v_pos_1765_, v_neg_1766_, v___x_1768_, v___x_1762_);
lean_dec_ref(v_neg_1766_);
lean_dec_ref(v_pos_1765_);
return v___x_1770_;
}
else
{
uint32_t v___x_1771_; 
v___x_1771_ = lp_competition_Submission_finishFast(v_pos_1765_, v_neg_1766_, v___x_1768_, v_negZero_1767_);
lean_dec_ref(v_neg_1766_);
lean_dec_ref(v_pos_1765_);
return v___x_1771_;
}
}
else
{
uint32_t v___x_1772_; 
v___x_1772_ = lp_competition_Submission_finishFast(v_pos_1765_, v_neg_1766_, v___x_1768_, v___x_1762_);
lean_dec_ref(v_neg_1766_);
lean_dec_ref(v_pos_1765_);
return v___x_1772_;
}
}
else
{
lean_object* v___f_1773_; lean_object* v___f_1774_; lean_object* v___x_1775_; lean_object* v___x_1776_; uint32_t v___x_1777_; 
lean_dec_ref(v_acc_1763_);
v___f_1773_ = lean_alloc_closure((void*)(lp_competition_Submission_dotX___lam__0___boxed), 2, 1);
lean_closure_set(v___f_1773_, 0, v_a_1754_);
v___f_1774_ = lean_alloc_closure((void*)(lp_competition_Submission_dotX___lam__1___boxed), 2, 1);
lean_closure_set(v___f_1774_, 0, v_b_1755_);
v___x_1775_ = l_Array_ofFn___redArg(v___x_1756_, v___f_1773_);
v___x_1776_ = l_Array_ofFn___redArg(v___x_1756_, v___f_1774_);
v___x_1777_ = lp_competition_ExactRuntime_dotSpec(v___x_1775_, v___x_1776_);
return v___x_1777_;
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_dotX___boxed(lean_object* v_a_1778_, lean_object* v_b_1779_){
_start:
{
uint32_t v_res_1780_; lean_object* v_r_1781_; 
v_res_1780_ = lp_competition_Submission_dotX(v_a_1778_, v_b_1779_);
v_r_1781_ = lean_box_uint32(v_res_1780_);
return v_r_1781_;
}
}
LEAN_EXPORT uint32_t lp_competition_Submission_sumX___lam__0(lean_object* v_i_1782_){
_start:
{
uint32_t v___x_1783_; 
v___x_1783_ = 1065353216;
return v___x_1783_;
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_sumX___lam__0___boxed(lean_object* v_i_1784_){
_start:
{
uint32_t v_res_1785_; lean_object* v_r_1786_; 
v_res_1785_ = lp_competition_Submission_sumX___lam__0(v_i_1784_);
lean_dec(v_i_1784_);
v_r_1786_ = lean_box_uint32(v_res_1785_);
return v_r_1786_;
}
}
LEAN_EXPORT uint32_t lp_competition_Submission_sumX___lam__1(uint32_t v___x_1787_, lean_object* v_x_1788_, lean_object* v_i_1789_){
_start:
{
lean_object* v___x_1790_; lean_object* v___x_1791_; uint32_t v___x_1792_; 
v___x_1790_ = lean_box_uint32(v___x_1787_);
v___x_1791_ = lean_array_get(v___x_1790_, v_x_1788_, v_i_1789_);
lean_dec(v___x_1790_);
v___x_1792_ = lean_unbox_uint32(v___x_1791_);
lean_dec(v___x_1791_);
return v___x_1792_;
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_sumX___lam__1___boxed(lean_object* v___x_1793_, lean_object* v_x_1794_, lean_object* v_i_1795_){
_start:
{
uint32_t v___x_600__boxed_1796_; uint32_t v_res_1797_; lean_object* v_r_1798_; 
v___x_600__boxed_1796_ = lean_unbox_uint32(v___x_1793_);
lean_dec(v___x_1793_);
v_res_1797_ = lp_competition_Submission_sumX___lam__1(v___x_600__boxed_1796_, v_x_1794_, v_i_1795_);
lean_dec(v_i_1795_);
lean_dec_ref(v_x_1794_);
v_r_1798_ = lean_box_uint32(v_res_1797_);
return v_r_1798_;
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_dotLoop___at___00Submission_sumX_spec__0(lean_object* v_x_1799_, lean_object* v_pos_1800_, lean_object* v_neg_1801_, uint8_t v_sp_1802_, uint8_t v_nz_1803_, lean_object* v_index_1804_, lean_object* v_x_1805_){
_start:
{
lean_object* v_zero_1806_; uint8_t v_isZero_1807_; 
v_zero_1806_ = lean_unsigned_to_nat(0u);
v_isZero_1807_ = lean_nat_dec_eq(v_x_1805_, v_zero_1806_);
if (v_isZero_1807_ == 1)
{
lean_object* v___x_1808_; 
lean_dec(v_x_1805_);
lean_dec(v_index_1804_);
v___x_1808_ = lean_alloc_ctor(0, 2, 2);
lean_ctor_set(v___x_1808_, 0, v_pos_1800_);
lean_ctor_set(v___x_1808_, 1, v_neg_1801_);
lean_ctor_set_uint8(v___x_1808_, sizeof(void*)*2, v_sp_1802_);
lean_ctor_set_uint8(v___x_1808_, sizeof(void*)*2 + 1, v_nz_1803_);
return v___x_1808_;
}
else
{
uint32_t v___x_1809_; lean_object* v_one_1810_; lean_object* v_n_1811_; lean_object* v_pos_1813_; lean_object* v_neg_1814_; uint8_t v_special_1815_; uint8_t v_negZero_1816_; lean_object* v___y_1820_; uint8_t v___y_1821_; lean_object* v___y_1822_; lean_object* v___y_1823_; lean_object* v___y_1824_; lean_object* v___y_1834_; lean_object* v___y_1835_; lean_object* v___y_1836_; lean_object* v___y_1837_; lean_object* v___y_1847_; lean_object* v___y_1848_; uint8_t v___y_1849_; lean_object* v___y_1896_; lean_object* v___y_1897_; lean_object* v___x_1899_; lean_object* v___x_1900_; uint32_t v___x_1901_; uint32_t v___x_1902_; uint32_t v___x_1903_; uint32_t v___x_1904_; uint32_t v___x_1905_; uint8_t v___x_1906_; lean_object* v___y_1908_; lean_object* v___y_1909_; lean_object* v___y_1911_; lean_object* v___y_1912_; lean_object* v___y_1920_; 
v___x_1809_ = 0;
v_one_1810_ = lean_unsigned_to_nat(1u);
v_n_1811_ = lean_nat_sub(v_x_1805_, v_one_1810_);
lean_dec(v_x_1805_);
v___x_1899_ = lp_competition_Submission_dotX___lam__0___boxed__const__1;
v___x_1900_ = lean_array_get_borrowed(v___x_1899_, v_x_1799_, v_index_1804_);
v___x_1901_ = 23;
v___x_1902_ = lean_unbox_uint32(v___x_1900_);
v___x_1903_ = lean_uint32_shift_right(v___x_1902_, v___x_1901_);
v___x_1904_ = 255;
v___x_1905_ = lean_uint32_land(v___x_1903_, v___x_1904_);
v___x_1906_ = lean_uint32_dec_eq(v___x_1905_, v___x_1904_);
if (v___x_1906_ == 0)
{
uint8_t v___x_1926_; 
v___x_1926_ = lean_uint32_dec_eq(v___x_1905_, v___x_1809_);
if (v___x_1926_ == 0)
{
lean_object* v___x_1927_; uint32_t v___x_1928_; uint32_t v___x_1929_; uint32_t v___x_1930_; lean_object* v___x_1931_; lean_object* v___x_1932_; 
v___x_1927_ = lean_unsigned_to_nat(8388608u);
v___x_1928_ = 8388607;
v___x_1929_ = lean_unbox_uint32(v___x_1900_);
v___x_1930_ = lean_uint32_land(v___x_1929_, v___x_1928_);
v___x_1931_ = lean_uint32_to_nat(v___x_1930_);
v___x_1932_ = lean_nat_add(v___x_1927_, v___x_1931_);
lean_dec(v___x_1931_);
v___y_1920_ = v___x_1932_;
goto v___jp_1919_;
}
else
{
uint32_t v___x_1933_; uint32_t v___x_1934_; uint32_t v___x_1935_; lean_object* v___x_1936_; 
v___x_1933_ = 8388607;
v___x_1934_ = lean_unbox_uint32(v___x_1900_);
v___x_1935_ = lean_uint32_land(v___x_1934_, v___x_1933_);
v___x_1936_ = lean_uint32_to_nat(v___x_1935_);
v___y_1920_ = v___x_1936_;
goto v___jp_1919_;
}
}
else
{
v_pos_1813_ = v_pos_1800_;
v_neg_1814_ = v_neg_1801_;
v_special_1815_ = v___x_1906_;
v_negZero_1816_ = v_nz_1803_;
goto v___jp_1812_;
}
v___jp_1812_:
{
lean_object* v___x_1817_; 
v___x_1817_ = lean_nat_add(v_index_1804_, v_one_1810_);
lean_dec(v_index_1804_);
v_pos_1800_ = v_pos_1813_;
v_neg_1801_ = v_neg_1814_;
v_sp_1802_ = v_special_1815_;
v_nz_1803_ = v_negZero_1816_;
v_index_1804_ = v___x_1817_;
v_x_1805_ = v_n_1811_;
goto _start;
}
v___jp_1819_:
{
lean_object* v___x_1825_; lean_object* v___x_1826_; uint8_t v___x_1827_; 
v___x_1825_ = lean_nat_add(v___y_1823_, v___y_1822_);
lean_dec(v___y_1823_);
v___x_1826_ = lean_array_get_size(v___y_1824_);
v___x_1827_ = lean_nat_dec_lt(v___x_1825_, v___x_1826_);
if (v___x_1827_ == 0)
{
lean_dec(v___x_1825_);
lean_dec(v___y_1820_);
v_pos_1813_ = v___y_1824_;
v_neg_1814_ = v_neg_1801_;
v_special_1815_ = v_sp_1802_;
v_negZero_1816_ = v___y_1821_;
goto v___jp_1812_;
}
else
{
lean_object* v_v_1828_; lean_object* v___x_1829_; lean_object* v_xs_x27_1830_; lean_object* v___x_1831_; lean_object* v___x_1832_; 
v_v_1828_ = lean_array_fget(v___y_1824_, v___x_1825_);
v___x_1829_ = lean_box(0);
v_xs_x27_1830_ = lean_array_fset(v___y_1824_, v___x_1825_, v___x_1829_);
v___x_1831_ = lean_nat_add(v_v_1828_, v___y_1820_);
lean_dec(v___y_1820_);
lean_dec(v_v_1828_);
v___x_1832_ = lean_array_fset(v_xs_x27_1830_, v___x_1825_, v___x_1831_);
lean_dec(v___x_1825_);
v_pos_1813_ = v___x_1832_;
v_neg_1814_ = v_neg_1801_;
v_special_1815_ = v_sp_1802_;
v_negZero_1816_ = v___y_1821_;
goto v___jp_1812_;
}
}
v___jp_1833_:
{
lean_object* v___x_1838_; lean_object* v___x_1839_; uint8_t v___x_1840_; 
v___x_1838_ = lean_nat_add(v___y_1834_, v___y_1836_);
lean_dec(v___y_1834_);
v___x_1839_ = lean_array_get_size(v___y_1837_);
v___x_1840_ = lean_nat_dec_lt(v___x_1838_, v___x_1839_);
if (v___x_1840_ == 0)
{
lean_dec(v___x_1838_);
lean_dec(v___y_1835_);
v_pos_1813_ = v_pos_1800_;
v_neg_1814_ = v___y_1837_;
v_special_1815_ = v_sp_1802_;
v_negZero_1816_ = v_isZero_1807_;
goto v___jp_1812_;
}
else
{
lean_object* v_v_1841_; lean_object* v___x_1842_; lean_object* v_xs_x27_1843_; lean_object* v___x_1844_; lean_object* v___x_1845_; 
v_v_1841_ = lean_array_fget(v___y_1837_, v___x_1838_);
v___x_1842_ = lean_box(0);
v_xs_x27_1843_ = lean_array_fset(v___y_1837_, v___x_1838_, v___x_1842_);
v___x_1844_ = lean_nat_add(v_v_1841_, v___y_1835_);
lean_dec(v___y_1835_);
lean_dec(v_v_1841_);
v___x_1845_ = lean_array_fset(v_xs_x27_1843_, v___x_1838_, v___x_1844_);
lean_dec(v___x_1838_);
v_pos_1813_ = v_pos_1800_;
v_neg_1814_ = v___x_1845_;
v_special_1815_ = v_sp_1802_;
v_negZero_1816_ = v_isZero_1807_;
goto v___jp_1812_;
}
}
v___jp_1846_:
{
uint8_t v___x_1850_; 
v___x_1850_ = lean_nat_dec_eq(v___y_1848_, v_zero_1806_);
if (v___x_1850_ == 0)
{
if (v___y_1849_ == 0)
{
uint64_t v___x_1851_; lean_object* v___x_1852_; lean_object* v___x_1853_; lean_object* v_l_1854_; lean_object* v___x_1855_; uint64_t v_r_1856_; uint64_t v___x_1857_; uint64_t v___x_1858_; uint64_t v___x_1859_; uint64_t v___x_1860_; uint64_t v___x_1861_; uint64_t v___x_1862_; lean_object* v_hi_1863_; lean_object* v___x_1864_; uint8_t v___x_1865_; 
v___x_1851_ = lean_uint64_of_nat(v___y_1848_);
lean_dec(v___y_1848_);
v___x_1852_ = lean_unsigned_to_nat(32u);
v___x_1853_ = lean_unsigned_to_nat(5u);
v_l_1854_ = lean_nat_shiftr(v___y_1847_, v___x_1853_);
v___x_1855_ = lean_nat_mod(v___y_1847_, v___x_1852_);
lean_dec(v___y_1847_);
v_r_1856_ = lean_uint64_of_nat(v___x_1855_);
lean_dec(v___x_1855_);
v___x_1857_ = 1ULL;
v___x_1858_ = 32ULL;
v___x_1859_ = lean_uint64_sub(v___x_1858_, v_r_1856_);
v___x_1860_ = lean_uint64_shift_left(v___x_1857_, v___x_1859_);
v___x_1861_ = lean_uint64_mod(v___x_1851_, v___x_1860_);
v___x_1862_ = lean_uint64_shift_right(v___x_1851_, v___x_1859_);
v_hi_1863_ = lean_uint64_to_nat(v___x_1862_);
v___x_1864_ = lean_array_get_size(v_pos_1800_);
v___x_1865_ = lean_nat_dec_lt(v_l_1854_, v___x_1864_);
if (v___x_1865_ == 0)
{
v___y_1820_ = v_hi_1863_;
v___y_1821_ = v___y_1849_;
v___y_1822_ = v_one_1810_;
v___y_1823_ = v_l_1854_;
v___y_1824_ = v_pos_1800_;
goto v___jp_1819_;
}
else
{
uint64_t v___x_1866_; lean_object* v_lo_1867_; lean_object* v_v_1868_; lean_object* v___x_1869_; lean_object* v_xs_x27_1870_; lean_object* v___x_1871_; lean_object* v___x_1872_; 
v___x_1866_ = lean_uint64_shift_left(v___x_1861_, v_r_1856_);
v_lo_1867_ = lean_uint64_to_nat(v___x_1866_);
v_v_1868_ = lean_array_fget(v_pos_1800_, v_l_1854_);
v___x_1869_ = lean_box(0);
v_xs_x27_1870_ = lean_array_fset(v_pos_1800_, v_l_1854_, v___x_1869_);
v___x_1871_ = lean_nat_add(v_v_1868_, v_lo_1867_);
lean_dec(v_lo_1867_);
lean_dec(v_v_1868_);
v___x_1872_ = lean_array_fset(v_xs_x27_1870_, v_l_1854_, v___x_1871_);
v___y_1820_ = v_hi_1863_;
v___y_1821_ = v___y_1849_;
v___y_1822_ = v_one_1810_;
v___y_1823_ = v_l_1854_;
v___y_1824_ = v___x_1872_;
goto v___jp_1819_;
}
}
else
{
uint64_t v___x_1873_; lean_object* v___x_1874_; lean_object* v___x_1875_; lean_object* v_l_1876_; lean_object* v___x_1877_; uint64_t v_r_1878_; uint64_t v___x_1879_; uint64_t v___x_1880_; uint64_t v___x_1881_; uint64_t v___x_1882_; uint64_t v___x_1883_; uint64_t v___x_1884_; lean_object* v_hi_1885_; lean_object* v___x_1886_; uint8_t v___x_1887_; 
v___x_1873_ = lean_uint64_of_nat(v___y_1848_);
lean_dec(v___y_1848_);
v___x_1874_ = lean_unsigned_to_nat(32u);
v___x_1875_ = lean_unsigned_to_nat(5u);
v_l_1876_ = lean_nat_shiftr(v___y_1847_, v___x_1875_);
v___x_1877_ = lean_nat_mod(v___y_1847_, v___x_1874_);
lean_dec(v___y_1847_);
v_r_1878_ = lean_uint64_of_nat(v___x_1877_);
lean_dec(v___x_1877_);
v___x_1879_ = 1ULL;
v___x_1880_ = 32ULL;
v___x_1881_ = lean_uint64_sub(v___x_1880_, v_r_1878_);
v___x_1882_ = lean_uint64_shift_left(v___x_1879_, v___x_1881_);
v___x_1883_ = lean_uint64_mod(v___x_1873_, v___x_1882_);
v___x_1884_ = lean_uint64_shift_right(v___x_1873_, v___x_1881_);
v_hi_1885_ = lean_uint64_to_nat(v___x_1884_);
v___x_1886_ = lean_array_get_size(v_neg_1801_);
v___x_1887_ = lean_nat_dec_lt(v_l_1876_, v___x_1886_);
if (v___x_1887_ == 0)
{
v___y_1834_ = v_l_1876_;
v___y_1835_ = v_hi_1885_;
v___y_1836_ = v_one_1810_;
v___y_1837_ = v_neg_1801_;
goto v___jp_1833_;
}
else
{
uint64_t v___x_1888_; lean_object* v_lo_1889_; lean_object* v_v_1890_; lean_object* v___x_1891_; lean_object* v_xs_x27_1892_; lean_object* v___x_1893_; lean_object* v___x_1894_; 
v___x_1888_ = lean_uint64_shift_left(v___x_1883_, v_r_1878_);
v_lo_1889_ = lean_uint64_to_nat(v___x_1888_);
v_v_1890_ = lean_array_fget(v_neg_1801_, v_l_1876_);
v___x_1891_ = lean_box(0);
v_xs_x27_1892_ = lean_array_fset(v_neg_1801_, v_l_1876_, v___x_1891_);
v___x_1893_ = lean_nat_add(v_v_1890_, v_lo_1889_);
lean_dec(v_lo_1889_);
lean_dec(v_v_1890_);
v___x_1894_ = lean_array_fset(v_xs_x27_1892_, v_l_1876_, v___x_1893_);
v___y_1834_ = v_l_1876_;
v___y_1835_ = v_hi_1885_;
v___y_1836_ = v_one_1810_;
v___y_1837_ = v___x_1894_;
goto v___jp_1833_;
}
}
}
else
{
lean_dec(v___y_1848_);
lean_dec(v___y_1847_);
if (v_nz_1803_ == 0)
{
v_pos_1813_ = v_pos_1800_;
v_neg_1814_ = v_neg_1801_;
v_special_1815_ = v_sp_1802_;
v_negZero_1816_ = v_nz_1803_;
goto v___jp_1812_;
}
else
{
v_pos_1813_ = v_pos_1800_;
v_neg_1814_ = v_neg_1801_;
v_special_1815_ = v_sp_1802_;
v_negZero_1816_ = v___y_1849_;
goto v___jp_1812_;
}
}
}
v___jp_1895_:
{
uint8_t v___x_1898_; 
v___x_1898_ = 1;
v___y_1847_ = v___y_1897_;
v___y_1848_ = v___y_1896_;
v___y_1849_ = v___x_1898_;
goto v___jp_1846_;
}
v___jp_1907_:
{
if (v___x_1906_ == 0)
{
v___y_1896_ = v___y_1909_;
v___y_1897_ = v___y_1908_;
goto v___jp_1895_;
}
else
{
v___y_1847_ = v___y_1908_;
v___y_1848_ = v___y_1909_;
v___y_1849_ = v___x_1906_;
goto v___jp_1846_;
}
}
v___jp_1910_:
{
lean_object* v___x_1913_; lean_object* v___x_1914_; uint32_t v___x_1915_; uint32_t v___x_1916_; uint32_t v___x_1917_; uint8_t v___x_1918_; 
v___x_1913_ = lean_unsigned_to_nat(126u);
v___x_1914_ = lean_nat_add(v___y_1912_, v___x_1913_);
lean_dec(v___y_1912_);
v___x_1915_ = 2147483648;
v___x_1916_ = lean_unbox_uint32(v___x_1900_);
v___x_1917_ = lean_uint32_land(v___x_1916_, v___x_1915_);
v___x_1918_ = lean_uint32_dec_eq(v___x_1917_, v___x_1809_);
if (v___x_1918_ == 0)
{
v___y_1908_ = v___x_1914_;
v___y_1909_ = v___y_1911_;
goto v___jp_1907_;
}
else
{
if (v___x_1906_ == 0)
{
if (v___x_1906_ == 0)
{
v___y_1847_ = v___x_1914_;
v___y_1848_ = v___y_1911_;
v___y_1849_ = v___x_1906_;
goto v___jp_1846_;
}
else
{
v___y_1896_ = v___y_1911_;
v___y_1897_ = v___x_1914_;
goto v___jp_1895_;
}
}
else
{
v___y_1908_ = v___x_1914_;
v___y_1909_ = v___y_1911_;
goto v___jp_1907_;
}
}
}
v___jp_1919_:
{
lean_object* v___x_1921_; lean_object* v___x_1922_; uint8_t v___x_1923_; 
v___x_1921_ = lean_unsigned_to_nat(8388608u);
v___x_1922_ = lean_nat_mul(v___y_1920_, v___x_1921_);
lean_dec(v___y_1920_);
v___x_1923_ = lean_uint32_dec_eq(v___x_1905_, v___x_1809_);
if (v___x_1923_ == 0)
{
lean_object* v___x_1924_; lean_object* v___x_1925_; 
v___x_1924_ = lean_uint32_to_nat(v___x_1905_);
v___x_1925_ = lean_nat_sub(v___x_1924_, v_one_1810_);
lean_dec(v___x_1924_);
v___y_1911_ = v___x_1922_;
v___y_1912_ = v___x_1925_;
goto v___jp_1910_;
}
else
{
v___y_1911_ = v___x_1922_;
v___y_1912_ = v_zero_1806_;
goto v___jp_1910_;
}
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_dotLoop___at___00Submission_sumX_spec__0___boxed(lean_object* v_x_1937_, lean_object* v_pos_1938_, lean_object* v_neg_1939_, lean_object* v_sp_1940_, lean_object* v_nz_1941_, lean_object* v_index_1942_, lean_object* v_x_1943_){
_start:
{
uint8_t v_sp_boxed_1944_; uint8_t v_nz_boxed_1945_; lean_object* v_res_1946_; 
v_sp_boxed_1944_ = lean_unbox(v_sp_1940_);
v_nz_boxed_1945_ = lean_unbox(v_nz_1941_);
v_res_1946_ = lp_competition_Submission_dotLoop___at___00Submission_sumX_spec__0(v_x_1937_, v_pos_1938_, v_neg_1939_, v_sp_boxed_1944_, v_nz_boxed_1945_, v_index_1942_, v_x_1943_);
lean_dec_ref(v_x_1937_);
return v_res_1946_;
}
}
LEAN_EXPORT uint32_t lp_competition_Submission_sumX(lean_object* v_x_1948_){
_start:
{
lean_object* v___x_1949_; lean_object* v___x_1950_; lean_object* v___x_1951_; uint8_t v___x_1952_; uint8_t v___x_1953_; lean_object* v_acc_1954_; uint8_t v_special_1955_; 
v___x_1949_ = lean_array_get_size(v_x_1948_);
v___x_1950_ = lean_unsigned_to_nat(0u);
v___x_1951_ = lean_obj_once(&lp_competition_Submission_Acc_empty___closed__0, &lp_competition_Submission_Acc_empty___closed__0_once, _init_lp_competition_Submission_Acc_empty___closed__0);
v___x_1952_ = 0;
v___x_1953_ = 1;
v_acc_1954_ = lp_competition_Submission_dotLoop___at___00Submission_sumX_spec__0(v_x_1948_, v___x_1951_, v___x_1951_, v___x_1952_, v___x_1953_, v___x_1950_, v___x_1949_);
v_special_1955_ = lean_ctor_get_uint8(v_acc_1954_, sizeof(void*)*2);
if (v_special_1955_ == 0)
{
lean_object* v_pos_1956_; lean_object* v_neg_1957_; uint8_t v_negZero_1958_; lean_object* v___x_1959_; uint8_t v___x_1960_; 
lean_dec_ref(v_x_1948_);
v_pos_1956_ = lean_ctor_get(v_acc_1954_, 0);
lean_inc_ref(v_pos_1956_);
v_neg_1957_ = lean_ctor_get(v_acc_1954_, 1);
lean_inc_ref(v_neg_1957_);
v_negZero_1958_ = lean_ctor_get_uint8(v_acc_1954_, sizeof(void*)*2 + 1);
lean_dec_ref(v_acc_1954_);
v___x_1959_ = lean_obj_once(&lp_competition_Submission_dotFn___closed__1, &lp_competition_Submission_dotFn___closed__1_once, _init_lp_competition_Submission_dotFn___closed__1);
v___x_1960_ = lean_nat_dec_eq(v___x_1949_, v___x_1950_);
if (v___x_1960_ == 0)
{
uint32_t v___x_1961_; 
v___x_1961_ = lp_competition_Submission_finishFast(v_pos_1956_, v_neg_1957_, v___x_1959_, v_negZero_1958_);
lean_dec_ref(v_neg_1957_);
lean_dec_ref(v_pos_1956_);
return v___x_1961_;
}
else
{
uint32_t v___x_1962_; 
v___x_1962_ = lp_competition_Submission_finishFast(v_pos_1956_, v_neg_1957_, v___x_1959_, v___x_1952_);
lean_dec_ref(v_neg_1957_);
lean_dec_ref(v_pos_1956_);
return v___x_1962_;
}
}
else
{
lean_object* v___f_1963_; lean_object* v___x_1964_; lean_object* v___f_1965_; lean_object* v___x_1966_; lean_object* v___x_1967_; uint32_t v___x_1968_; 
lean_dec_ref(v_acc_1954_);
v___f_1963_ = ((lean_object*)(lp_competition_Submission_sumX___closed__0));
v___x_1964_ = lp_competition_Submission_dotX___lam__0___boxed__const__1;
v___f_1965_ = lean_alloc_closure((void*)(lp_competition_Submission_sumX___lam__1___boxed), 3, 2);
lean_closure_set(v___f_1965_, 0, v___x_1964_);
lean_closure_set(v___f_1965_, 1, v_x_1948_);
v___x_1966_ = l_Array_ofFn___redArg(v___x_1949_, v___f_1965_);
v___x_1967_ = l_Array_ofFn___redArg(v___x_1949_, v___f_1963_);
v___x_1968_ = lp_competition_ExactRuntime_dotSpec(v___x_1966_, v___x_1967_);
return v___x_1968_;
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_sumX___boxed(lean_object* v_x_1969_){
_start:
{
uint32_t v_res_1970_; lean_object* v_r_1971_; 
v_res_1970_ = lp_competition_Submission_sumX(v_x_1969_);
v_r_1971_ = lean_box_uint32(v_res_1970_);
return v_r_1971_;
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_keyOf(uint32_t v_w_1972_){
_start:
{
lean_object* v___y_1974_; lean_object* v___y_1975_; lean_object* v___y_1979_; lean_object* v___y_1980_; uint32_t v___x_1984_; uint32_t v___x_1985_; uint32_t v___x_1986_; lean_object* v___y_1988_; lean_object* v___y_1999_; uint8_t v___x_2009_; 
v___x_1984_ = 2147483648;
v___x_1985_ = lean_uint32_land(v_w_1972_, v___x_1984_);
v___x_1986_ = 0;
v___x_2009_ = lean_uint32_dec_eq(v___x_1985_, v___x_1986_);
if (v___x_2009_ == 0)
{
uint32_t v___x_2010_; uint32_t v___x_2011_; uint32_t v___x_2012_; uint32_t v___x_2013_; uint8_t v___x_2014_; 
v___x_2010_ = 23;
v___x_2011_ = lean_uint32_shift_right(v_w_1972_, v___x_2010_);
v___x_2012_ = 255;
v___x_2013_ = lean_uint32_land(v___x_2011_, v___x_2012_);
v___x_2014_ = lean_uint32_dec_eq(v___x_2013_, v___x_1986_);
if (v___x_2014_ == 0)
{
lean_object* v___x_2015_; uint32_t v___x_2016_; uint32_t v___x_2017_; lean_object* v___x_2018_; lean_object* v___x_2019_; 
v___x_2015_ = lean_unsigned_to_nat(8388608u);
v___x_2016_ = 8388607;
v___x_2017_ = lean_uint32_land(v_w_1972_, v___x_2016_);
v___x_2018_ = lean_uint32_to_nat(v___x_2017_);
v___x_2019_ = lean_nat_add(v___x_2015_, v___x_2018_);
lean_dec(v___x_2018_);
v___y_1999_ = v___x_2019_;
goto v___jp_1998_;
}
else
{
uint32_t v___x_2020_; uint32_t v___x_2021_; lean_object* v___x_2022_; 
v___x_2020_ = 8388607;
v___x_2021_ = lean_uint32_land(v_w_1972_, v___x_2020_);
v___x_2022_ = lean_uint32_to_nat(v___x_2021_);
v___y_1999_ = v___x_2022_;
goto v___jp_1998_;
}
}
else
{
uint32_t v___x_2023_; uint32_t v___x_2024_; uint32_t v___x_2025_; uint32_t v___x_2026_; uint8_t v___x_2027_; 
v___x_2023_ = 23;
v___x_2024_ = lean_uint32_shift_right(v_w_1972_, v___x_2023_);
v___x_2025_ = 255;
v___x_2026_ = lean_uint32_land(v___x_2024_, v___x_2025_);
v___x_2027_ = lean_uint32_dec_eq(v___x_2026_, v___x_1986_);
if (v___x_2027_ == 0)
{
lean_object* v___x_2028_; uint32_t v___x_2029_; uint32_t v___x_2030_; lean_object* v___x_2031_; lean_object* v___x_2032_; 
v___x_2028_ = lean_unsigned_to_nat(8388608u);
v___x_2029_ = 8388607;
v___x_2030_ = lean_uint32_land(v_w_1972_, v___x_2029_);
v___x_2031_ = lean_uint32_to_nat(v___x_2030_);
v___x_2032_ = lean_nat_add(v___x_2028_, v___x_2031_);
lean_dec(v___x_2031_);
v___y_1988_ = v___x_2032_;
goto v___jp_1987_;
}
else
{
uint32_t v___x_2033_; uint32_t v___x_2034_; lean_object* v___x_2035_; 
v___x_2033_ = 8388607;
v___x_2034_ = lean_uint32_land(v_w_1972_, v___x_2033_);
v___x_2035_ = lean_uint32_to_nat(v___x_2034_);
v___y_1988_ = v___x_2035_;
goto v___jp_1987_;
}
}
v___jp_1973_:
{
lean_object* v___x_1976_; lean_object* v___x_1977_; 
v___x_1976_ = lean_nat_shiftl(v___y_1974_, v___y_1975_);
lean_dec(v___y_1975_);
lean_dec(v___y_1974_);
v___x_1977_ = lean_nat_to_int(v___x_1976_);
return v___x_1977_;
}
v___jp_1978_:
{
lean_object* v___x_1981_; lean_object* v___x_1982_; lean_object* v___x_1983_; 
v___x_1981_ = lean_nat_shiftl(v___y_1979_, v___y_1980_);
lean_dec(v___y_1980_);
lean_dec(v___y_1979_);
v___x_1982_ = lean_nat_to_int(v___x_1981_);
v___x_1983_ = lean_int_neg(v___x_1982_);
lean_dec(v___x_1982_);
return v___x_1983_;
}
v___jp_1987_:
{
uint32_t v___x_1989_; uint32_t v___x_1990_; uint32_t v___x_1991_; uint32_t v___x_1992_; uint8_t v___x_1993_; 
v___x_1989_ = 23;
v___x_1990_ = lean_uint32_shift_right(v_w_1972_, v___x_1989_);
v___x_1991_ = 255;
v___x_1992_ = lean_uint32_land(v___x_1990_, v___x_1991_);
v___x_1993_ = lean_uint32_dec_eq(v___x_1992_, v___x_1986_);
if (v___x_1993_ == 0)
{
lean_object* v___x_1994_; lean_object* v___x_1995_; lean_object* v___x_1996_; 
v___x_1994_ = lean_uint32_to_nat(v___x_1992_);
v___x_1995_ = lean_unsigned_to_nat(1u);
v___x_1996_ = lean_nat_sub(v___x_1994_, v___x_1995_);
lean_dec(v___x_1994_);
v___y_1974_ = v___y_1988_;
v___y_1975_ = v___x_1996_;
goto v___jp_1973_;
}
else
{
lean_object* v___x_1997_; 
v___x_1997_ = lean_unsigned_to_nat(0u);
v___y_1974_ = v___y_1988_;
v___y_1975_ = v___x_1997_;
goto v___jp_1973_;
}
}
v___jp_1998_:
{
uint32_t v___x_2000_; uint32_t v___x_2001_; uint32_t v___x_2002_; uint32_t v___x_2003_; uint8_t v___x_2004_; 
v___x_2000_ = 23;
v___x_2001_ = lean_uint32_shift_right(v_w_1972_, v___x_2000_);
v___x_2002_ = 255;
v___x_2003_ = lean_uint32_land(v___x_2001_, v___x_2002_);
v___x_2004_ = lean_uint32_dec_eq(v___x_2003_, v___x_1986_);
if (v___x_2004_ == 0)
{
lean_object* v___x_2005_; lean_object* v___x_2006_; lean_object* v___x_2007_; 
v___x_2005_ = lean_uint32_to_nat(v___x_2003_);
v___x_2006_ = lean_unsigned_to_nat(1u);
v___x_2007_ = lean_nat_sub(v___x_2005_, v___x_2006_);
lean_dec(v___x_2005_);
v___y_1979_ = v___y_1999_;
v___y_1980_ = v___x_2007_;
goto v___jp_1978_;
}
else
{
lean_object* v___x_2008_; 
v___x_2008_ = lean_unsigned_to_nat(0u);
v___y_1979_ = v___y_1999_;
v___y_1980_ = v___x_2008_;
goto v___jp_1978_;
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_keyOf___boxed(lean_object* v_w_2036_){
_start:
{
uint32_t v_w_boxed_2037_; lean_object* v_res_2038_; 
v_w_boxed_2037_ = lean_unbox_uint32(v_w_2036_);
lean_dec(v_w_2036_);
v_res_2038_ = lp_competition_Submission_keyOf(v_w_boxed_2037_);
return v_res_2038_;
}
}
static lean_object* _init_lp_competition_Submission_maxW___closed__0(void){
_start:
{
lean_object* v___x_2039_; lean_object* v___x_2040_; lean_object* v___x_2041_; 
v___x_2039_ = lean_unsigned_to_nat(255u);
v___x_2040_ = lean_unsigned_to_nat(32u);
v___x_2041_ = l_BitVec_ofNat(v___x_2040_, v___x_2039_);
return v___x_2041_;
}
}
static lean_object* _init_lp_competition_Submission_maxW___closed__1(void){
_start:
{
lean_object* v___x_2042_; lean_object* v___x_2043_; lean_object* v___x_2044_; 
v___x_2042_ = lean_unsigned_to_nat(8388607u);
v___x_2043_ = lean_unsigned_to_nat(32u);
v___x_2044_ = l_BitVec_ofNat(v___x_2043_, v___x_2042_);
return v___x_2044_;
}
}
LEAN_EXPORT uint32_t lp_competition_Submission_maxW(uint32_t v_a_2050_, uint32_t v_b_2051_){
_start:
{
uint8_t v___y_2055_; uint8_t v___y_2056_; uint8_t v___y_2059_; lean_object* v___y_2060_; lean_object* v___y_2061_; uint8_t v___y_2062_; lean_object* v___y_2070_; uint8_t v___y_2071_; lean_object* v___y_2072_; lean_object* v___y_2073_; uint8_t v___y_2074_; lean_object* v___y_2089_; lean_object* v___y_2090_; lean_object* v___y_2106_; lean_object* v___y_2107_; lean_object* v___y_2108_; uint32_t v___y_2113_; lean_object* v___y_2114_; lean_object* v___y_2115_; lean_object* v___y_2126_; lean_object* v___y_2127_; lean_object* v___y_2128_; uint32_t v___y_2132_; lean_object* v___y_2133_; lean_object* v___y_2134_; lean_object* v___y_2145_; lean_object* v___y_2177_; lean_object* v___y_2178_; lean_object* v___y_2182_; lean_object* v___y_2183_; uint32_t v___x_2196_; uint32_t v___x_2197_; uint32_t v___x_2198_; uint32_t v___x_2199_; uint8_t v___x_2200_; 
v___x_2196_ = 23;
v___x_2197_ = lean_uint32_shift_right(v_a_2050_, v___x_2196_);
v___x_2198_ = 255;
v___x_2199_ = lean_uint32_land(v___x_2197_, v___x_2198_);
v___x_2200_ = lean_uint32_dec_eq(v___x_2199_, v___x_2198_);
if (v___x_2200_ == 0)
{
uint32_t v___x_2201_; uint32_t v___x_2202_; uint8_t v___x_2203_; 
v___x_2201_ = lean_uint32_shift_right(v_b_2051_, v___x_2196_);
v___x_2202_ = lean_uint32_land(v___x_2201_, v___x_2198_);
v___x_2203_ = lean_uint32_dec_eq(v___x_2202_, v___x_2198_);
if (v___x_2203_ == 0)
{
uint32_t v___x_2204_; uint32_t v___x_2205_; uint32_t v___x_2206_; lean_object* v___y_2208_; lean_object* v___y_2215_; uint8_t v___x_2221_; 
v___x_2204_ = 2147483648;
v___x_2205_ = lean_uint32_land(v_a_2050_, v___x_2204_);
v___x_2206_ = 0;
v___x_2221_ = lean_uint32_dec_eq(v___x_2205_, v___x_2206_);
if (v___x_2221_ == 0)
{
uint8_t v___x_2222_; 
v___x_2222_ = lean_uint32_dec_eq(v___x_2199_, v___x_2206_);
if (v___x_2222_ == 0)
{
lean_object* v___x_2223_; uint32_t v___x_2224_; uint32_t v___x_2225_; lean_object* v___x_2226_; lean_object* v___x_2227_; 
v___x_2223_ = lean_unsigned_to_nat(8388608u);
v___x_2224_ = 8388607;
v___x_2225_ = lean_uint32_land(v_a_2050_, v___x_2224_);
v___x_2226_ = lean_uint32_to_nat(v___x_2225_);
v___x_2227_ = lean_nat_add(v___x_2223_, v___x_2226_);
lean_dec(v___x_2226_);
v___y_2215_ = v___x_2227_;
goto v___jp_2214_;
}
else
{
uint32_t v___x_2228_; uint32_t v___x_2229_; lean_object* v___x_2230_; 
v___x_2228_ = 8388607;
v___x_2229_ = lean_uint32_land(v_a_2050_, v___x_2228_);
v___x_2230_ = lean_uint32_to_nat(v___x_2229_);
v___y_2215_ = v___x_2230_;
goto v___jp_2214_;
}
}
else
{
uint8_t v___x_2231_; 
v___x_2231_ = lean_uint32_dec_eq(v___x_2199_, v___x_2206_);
if (v___x_2231_ == 0)
{
lean_object* v___x_2232_; uint32_t v___x_2233_; uint32_t v___x_2234_; lean_object* v___x_2235_; lean_object* v___x_2236_; 
v___x_2232_ = lean_unsigned_to_nat(8388608u);
v___x_2233_ = 8388607;
v___x_2234_ = lean_uint32_land(v_a_2050_, v___x_2233_);
v___x_2235_ = lean_uint32_to_nat(v___x_2234_);
v___x_2236_ = lean_nat_add(v___x_2232_, v___x_2235_);
lean_dec(v___x_2235_);
v___y_2208_ = v___x_2236_;
goto v___jp_2207_;
}
else
{
uint32_t v___x_2237_; uint32_t v___x_2238_; lean_object* v___x_2239_; 
v___x_2237_ = 8388607;
v___x_2238_ = lean_uint32_land(v_a_2050_, v___x_2237_);
v___x_2239_ = lean_uint32_to_nat(v___x_2238_);
v___y_2208_ = v___x_2239_;
goto v___jp_2207_;
}
}
v___jp_2207_:
{
uint8_t v___x_2209_; 
v___x_2209_ = lean_uint32_dec_eq(v___x_2199_, v___x_2206_);
if (v___x_2209_ == 0)
{
lean_object* v___x_2210_; lean_object* v___x_2211_; lean_object* v___x_2212_; 
v___x_2210_ = lean_uint32_to_nat(v___x_2199_);
v___x_2211_ = lean_unsigned_to_nat(1u);
v___x_2212_ = lean_nat_sub(v___x_2210_, v___x_2211_);
lean_dec(v___x_2210_);
v___y_2177_ = v___y_2208_;
v___y_2178_ = v___x_2212_;
goto v___jp_2176_;
}
else
{
lean_object* v___x_2213_; 
v___x_2213_ = lean_unsigned_to_nat(0u);
v___y_2177_ = v___y_2208_;
v___y_2178_ = v___x_2213_;
goto v___jp_2176_;
}
}
v___jp_2214_:
{
uint8_t v___x_2216_; 
v___x_2216_ = lean_uint32_dec_eq(v___x_2199_, v___x_2206_);
if (v___x_2216_ == 0)
{
lean_object* v___x_2217_; lean_object* v___x_2218_; lean_object* v___x_2219_; 
v___x_2217_ = lean_uint32_to_nat(v___x_2199_);
v___x_2218_ = lean_unsigned_to_nat(1u);
v___x_2219_ = lean_nat_sub(v___x_2217_, v___x_2218_);
lean_dec(v___x_2217_);
v___y_2182_ = v___y_2215_;
v___y_2183_ = v___x_2219_;
goto v___jp_2181_;
}
else
{
lean_object* v___x_2220_; 
v___x_2220_ = lean_unsigned_to_nat(0u);
v___y_2182_ = v___y_2215_;
v___y_2183_ = v___x_2220_;
goto v___jp_2181_;
}
}
}
else
{
goto v___jp_2187_;
}
}
else
{
goto v___jp_2187_;
}
v___jp_2052_:
{
uint32_t v___x_2053_; 
v___x_2053_ = lean_uint32_once(&lp_competition_Submission_finishDigits___closed__11, &lp_competition_Submission_finishDigits___closed__11_once, _init_lp_competition_Submission_finishDigits___closed__11);
return v___x_2053_;
}
v___jp_2054_:
{
if (v___y_2056_ == 0)
{
goto v___jp_2052_;
}
else
{
if (v___y_2055_ == 0)
{
uint32_t v___x_2057_; 
v___x_2057_ = lean_uint32_once(&lp_competition_Submission_finishDigits___closed__1, &lp_competition_Submission_finishDigits___closed__1_once, _init_lp_competition_Submission_finishDigits___closed__1);
return v___x_2057_;
}
else
{
goto v___jp_2052_;
}
}
}
v___jp_2058_:
{
if (v___y_2062_ == 0)
{
uint32_t v___x_2063_; 
v___x_2063_ = lean_uint32_of_nat(v___y_2061_);
lean_dec(v___y_2061_);
return v___x_2063_;
}
else
{
lean_object* v___x_2064_; uint8_t v___x_2065_; 
v___x_2064_ = lean_unsigned_to_nat(31u);
v___x_2065_ = l_Nat_testBit(v___y_2061_, v___x_2064_);
lean_dec(v___y_2061_);
if (v___x_2065_ == 0)
{
v___y_2055_ = v___y_2059_;
v___y_2056_ = v___x_2065_;
goto v___jp_2054_;
}
else
{
lean_object* v___x_2066_; lean_object* v___x_2067_; uint8_t v___x_2068_; 
v___x_2066_ = lean_uint32_to_nat(v_b_2051_);
v___x_2067_ = l_BitVec_ofNat(v___y_2060_, v___x_2066_);
lean_dec(v___x_2066_);
v___x_2068_ = l_Nat_testBit(v___x_2067_, v___x_2064_);
lean_dec(v___x_2067_);
v___y_2055_ = v___y_2059_;
v___y_2056_ = v___x_2068_;
goto v___jp_2054_;
}
}
}
v___jp_2069_:
{
if (v___y_2074_ == 0)
{
uint32_t v___x_2075_; 
v___x_2075_ = lean_uint32_of_nat(v___y_2073_);
lean_dec(v___y_2073_);
return v___x_2075_;
}
else
{
lean_object* v___x_2076_; lean_object* v___x_2077_; lean_object* v___x_2078_; lean_object* v___x_2079_; lean_object* v___x_2080_; lean_object* v___x_2081_; lean_object* v___x_2082_; uint8_t v___x_2083_; 
v___x_2076_ = lean_uint32_to_nat(v_b_2051_);
v___x_2077_ = l_BitVec_ofNat(v___y_2072_, v___x_2076_);
lean_dec(v___x_2076_);
v___x_2078_ = lean_nat_shiftr(v___x_2077_, v___y_2070_);
v___x_2079_ = lean_unsigned_to_nat(255u);
v___x_2080_ = l_BitVec_ofNat(v___y_2072_, v___x_2079_);
v___x_2081_ = lean_nat_land(v___x_2078_, v___x_2080_);
lean_dec(v___x_2080_);
lean_dec(v___x_2078_);
v___x_2082_ = lean_unsigned_to_nat(0u);
v___x_2083_ = lean_nat_dec_eq(v___x_2081_, v___x_2082_);
lean_dec(v___x_2081_);
if (v___x_2083_ == 0)
{
lean_dec(v___x_2077_);
v___y_2059_ = v___y_2071_;
v___y_2060_ = v___y_2072_;
v___y_2061_ = v___y_2073_;
v___y_2062_ = v___x_2083_;
goto v___jp_2058_;
}
else
{
lean_object* v___x_2084_; lean_object* v___x_2085_; lean_object* v___x_2086_; uint8_t v___x_2087_; 
v___x_2084_ = lean_unsigned_to_nat(8388607u);
v___x_2085_ = l_BitVec_ofNat(v___y_2072_, v___x_2084_);
v___x_2086_ = lean_nat_land(v___x_2077_, v___x_2085_);
lean_dec(v___x_2085_);
lean_dec(v___x_2077_);
v___x_2087_ = lean_nat_dec_eq(v___x_2086_, v___x_2082_);
lean_dec(v___x_2086_);
v___y_2059_ = v___y_2071_;
v___y_2060_ = v___y_2072_;
v___y_2061_ = v___y_2073_;
v___y_2062_ = v___x_2087_;
goto v___jp_2058_;
}
}
}
v___jp_2088_:
{
uint8_t v___x_2091_; 
v___x_2091_ = lean_int_dec_lt(v___y_2089_, v___y_2090_);
if (v___x_2091_ == 0)
{
uint8_t v___x_2092_; 
v___x_2092_ = lean_int_dec_eq(v___y_2089_, v___y_2090_);
lean_dec(v___y_2090_);
lean_dec(v___y_2089_);
if (v___x_2092_ == 0)
{
return v_a_2050_;
}
else
{
lean_object* v___x_2093_; lean_object* v___x_2094_; lean_object* v___x_2095_; lean_object* v___x_2096_; lean_object* v___x_2097_; lean_object* v___x_2098_; lean_object* v___x_2099_; lean_object* v___x_2100_; uint8_t v___x_2101_; 
v___x_2093_ = lean_unsigned_to_nat(23u);
v___x_2094_ = lean_uint32_to_nat(v_a_2050_);
v___x_2095_ = lean_unsigned_to_nat(32u);
v___x_2096_ = l_BitVec_ofNat(v___x_2095_, v___x_2094_);
lean_dec(v___x_2094_);
v___x_2097_ = lean_nat_shiftr(v___x_2096_, v___x_2093_);
v___x_2098_ = lean_obj_once(&lp_competition_Submission_maxW___closed__0, &lp_competition_Submission_maxW___closed__0_once, _init_lp_competition_Submission_maxW___closed__0);
v___x_2099_ = lean_nat_land(v___x_2097_, v___x_2098_);
lean_dec(v___x_2097_);
v___x_2100_ = lean_unsigned_to_nat(0u);
v___x_2101_ = lean_nat_dec_eq(v___x_2099_, v___x_2100_);
lean_dec(v___x_2099_);
if (v___x_2101_ == 0)
{
v___y_2070_ = v___x_2093_;
v___y_2071_ = v___x_2091_;
v___y_2072_ = v___x_2095_;
v___y_2073_ = v___x_2096_;
v___y_2074_ = v___x_2101_;
goto v___jp_2069_;
}
else
{
lean_object* v___x_2102_; lean_object* v___x_2103_; uint8_t v___x_2104_; 
v___x_2102_ = lean_obj_once(&lp_competition_Submission_maxW___closed__1, &lp_competition_Submission_maxW___closed__1_once, _init_lp_competition_Submission_maxW___closed__1);
v___x_2103_ = lean_nat_land(v___x_2096_, v___x_2102_);
v___x_2104_ = lean_nat_dec_eq(v___x_2103_, v___x_2100_);
lean_dec(v___x_2103_);
v___y_2070_ = v___x_2093_;
v___y_2071_ = v___x_2091_;
v___y_2072_ = v___x_2095_;
v___y_2073_ = v___x_2096_;
v___y_2074_ = v___x_2104_;
goto v___jp_2069_;
}
}
}
else
{
lean_dec(v___y_2090_);
lean_dec(v___y_2089_);
return v_b_2051_;
}
}
v___jp_2105_:
{
lean_object* v___x_2109_; lean_object* v___x_2110_; lean_object* v___x_2111_; 
v___x_2109_ = lean_nat_shiftl(v___y_2106_, v___y_2108_);
lean_dec(v___y_2108_);
lean_dec(v___y_2106_);
v___x_2110_ = lean_nat_to_int(v___x_2109_);
v___x_2111_ = lean_int_neg(v___x_2110_);
lean_dec(v___x_2110_);
v___y_2089_ = v___y_2107_;
v___y_2090_ = v___x_2111_;
goto v___jp_2088_;
}
v___jp_2112_:
{
uint32_t v___x_2116_; uint32_t v___x_2117_; uint32_t v___x_2118_; uint32_t v___x_2119_; uint8_t v___x_2120_; 
v___x_2116_ = 23;
v___x_2117_ = lean_uint32_shift_right(v_b_2051_, v___x_2116_);
v___x_2118_ = 255;
v___x_2119_ = lean_uint32_land(v___x_2117_, v___x_2118_);
v___x_2120_ = lean_uint32_dec_eq(v___x_2119_, v___y_2113_);
if (v___x_2120_ == 0)
{
lean_object* v___x_2121_; lean_object* v___x_2122_; lean_object* v___x_2123_; 
v___x_2121_ = lean_uint32_to_nat(v___x_2119_);
v___x_2122_ = lean_unsigned_to_nat(1u);
v___x_2123_ = lean_nat_sub(v___x_2121_, v___x_2122_);
lean_dec(v___x_2121_);
v___y_2106_ = v___y_2115_;
v___y_2107_ = v___y_2114_;
v___y_2108_ = v___x_2123_;
goto v___jp_2105_;
}
else
{
lean_object* v___x_2124_; 
v___x_2124_ = lean_unsigned_to_nat(0u);
v___y_2106_ = v___y_2115_;
v___y_2107_ = v___y_2114_;
v___y_2108_ = v___x_2124_;
goto v___jp_2105_;
}
}
v___jp_2125_:
{
lean_object* v___x_2129_; lean_object* v___x_2130_; 
v___x_2129_ = lean_nat_shiftl(v___y_2126_, v___y_2128_);
lean_dec(v___y_2128_);
lean_dec(v___y_2126_);
v___x_2130_ = lean_nat_to_int(v___x_2129_);
v___y_2089_ = v___y_2127_;
v___y_2090_ = v___x_2130_;
goto v___jp_2088_;
}
v___jp_2131_:
{
uint32_t v___x_2135_; uint32_t v___x_2136_; uint32_t v___x_2137_; uint32_t v___x_2138_; uint8_t v___x_2139_; 
v___x_2135_ = 23;
v___x_2136_ = lean_uint32_shift_right(v_b_2051_, v___x_2135_);
v___x_2137_ = 255;
v___x_2138_ = lean_uint32_land(v___x_2136_, v___x_2137_);
v___x_2139_ = lean_uint32_dec_eq(v___x_2138_, v___y_2132_);
if (v___x_2139_ == 0)
{
lean_object* v___x_2140_; lean_object* v___x_2141_; lean_object* v___x_2142_; 
v___x_2140_ = lean_uint32_to_nat(v___x_2138_);
v___x_2141_ = lean_unsigned_to_nat(1u);
v___x_2142_ = lean_nat_sub(v___x_2140_, v___x_2141_);
lean_dec(v___x_2140_);
v___y_2126_ = v___y_2134_;
v___y_2127_ = v___y_2133_;
v___y_2128_ = v___x_2142_;
goto v___jp_2125_;
}
else
{
lean_object* v___x_2143_; 
v___x_2143_ = lean_unsigned_to_nat(0u);
v___y_2126_ = v___y_2134_;
v___y_2127_ = v___y_2133_;
v___y_2128_ = v___x_2143_;
goto v___jp_2125_;
}
}
v___jp_2144_:
{
uint32_t v___x_2146_; uint32_t v___x_2147_; uint32_t v___x_2148_; uint8_t v___x_2149_; 
v___x_2146_ = 2147483648;
v___x_2147_ = lean_uint32_land(v_b_2051_, v___x_2146_);
v___x_2148_ = 0;
v___x_2149_ = lean_uint32_dec_eq(v___x_2147_, v___x_2148_);
if (v___x_2149_ == 0)
{
uint32_t v___x_2150_; uint32_t v___x_2151_; uint32_t v___x_2152_; uint32_t v___x_2153_; uint8_t v___x_2154_; 
v___x_2150_ = 23;
v___x_2151_ = lean_uint32_shift_right(v_b_2051_, v___x_2150_);
v___x_2152_ = 255;
v___x_2153_ = lean_uint32_land(v___x_2151_, v___x_2152_);
v___x_2154_ = lean_uint32_dec_eq(v___x_2153_, v___x_2148_);
if (v___x_2154_ == 0)
{
lean_object* v___x_2155_; uint32_t v___x_2156_; uint32_t v___x_2157_; lean_object* v___x_2158_; lean_object* v___x_2159_; 
v___x_2155_ = lean_unsigned_to_nat(8388608u);
v___x_2156_ = 8388607;
v___x_2157_ = lean_uint32_land(v_b_2051_, v___x_2156_);
v___x_2158_ = lean_uint32_to_nat(v___x_2157_);
v___x_2159_ = lean_nat_add(v___x_2155_, v___x_2158_);
lean_dec(v___x_2158_);
v___y_2113_ = v___x_2148_;
v___y_2114_ = v___y_2145_;
v___y_2115_ = v___x_2159_;
goto v___jp_2112_;
}
else
{
uint32_t v___x_2160_; uint32_t v___x_2161_; lean_object* v___x_2162_; 
v___x_2160_ = 8388607;
v___x_2161_ = lean_uint32_land(v_b_2051_, v___x_2160_);
v___x_2162_ = lean_uint32_to_nat(v___x_2161_);
v___y_2113_ = v___x_2148_;
v___y_2114_ = v___y_2145_;
v___y_2115_ = v___x_2162_;
goto v___jp_2112_;
}
}
else
{
uint32_t v___x_2163_; uint32_t v___x_2164_; uint32_t v___x_2165_; uint32_t v___x_2166_; uint8_t v___x_2167_; 
v___x_2163_ = 23;
v___x_2164_ = lean_uint32_shift_right(v_b_2051_, v___x_2163_);
v___x_2165_ = 255;
v___x_2166_ = lean_uint32_land(v___x_2164_, v___x_2165_);
v___x_2167_ = lean_uint32_dec_eq(v___x_2166_, v___x_2148_);
if (v___x_2167_ == 0)
{
lean_object* v___x_2168_; uint32_t v___x_2169_; uint32_t v___x_2170_; lean_object* v___x_2171_; lean_object* v___x_2172_; 
v___x_2168_ = lean_unsigned_to_nat(8388608u);
v___x_2169_ = 8388607;
v___x_2170_ = lean_uint32_land(v_b_2051_, v___x_2169_);
v___x_2171_ = lean_uint32_to_nat(v___x_2170_);
v___x_2172_ = lean_nat_add(v___x_2168_, v___x_2171_);
lean_dec(v___x_2171_);
v___y_2132_ = v___x_2148_;
v___y_2133_ = v___y_2145_;
v___y_2134_ = v___x_2172_;
goto v___jp_2131_;
}
else
{
uint32_t v___x_2173_; uint32_t v___x_2174_; lean_object* v___x_2175_; 
v___x_2173_ = 8388607;
v___x_2174_ = lean_uint32_land(v_b_2051_, v___x_2173_);
v___x_2175_ = lean_uint32_to_nat(v___x_2174_);
v___y_2132_ = v___x_2148_;
v___y_2133_ = v___y_2145_;
v___y_2134_ = v___x_2175_;
goto v___jp_2131_;
}
}
}
v___jp_2176_:
{
lean_object* v___x_2179_; lean_object* v___x_2180_; 
v___x_2179_ = lean_nat_shiftl(v___y_2177_, v___y_2178_);
lean_dec(v___y_2178_);
lean_dec(v___y_2177_);
v___x_2180_ = lean_nat_to_int(v___x_2179_);
v___y_2145_ = v___x_2180_;
goto v___jp_2144_;
}
v___jp_2181_:
{
lean_object* v___x_2184_; lean_object* v___x_2185_; lean_object* v___x_2186_; 
v___x_2184_ = lean_nat_shiftl(v___y_2182_, v___y_2183_);
lean_dec(v___y_2183_);
lean_dec(v___y_2182_);
v___x_2185_ = lean_nat_to_int(v___x_2184_);
v___x_2186_ = lean_int_neg(v___x_2185_);
lean_dec(v___x_2185_);
v___y_2145_ = v___x_2186_;
goto v___jp_2144_;
}
v___jp_2187_:
{
lean_object* v___x_2188_; lean_object* v___x_2189_; lean_object* v___x_2190_; lean_object* v___x_2191_; lean_object* v___x_2192_; lean_object* v___x_2193_; lean_object* v___x_2194_; uint32_t v___x_2195_; 
v___x_2188_ = ((lean_object*)(lp_competition_Submission_maxW___closed__2));
v___x_2189_ = lean_uint32_to_nat(v_a_2050_);
v___x_2190_ = lean_unsigned_to_nat(32u);
v___x_2191_ = l_BitVec_ofNat(v___x_2190_, v___x_2189_);
lean_dec(v___x_2189_);
v___x_2192_ = lean_uint32_to_nat(v_b_2051_);
v___x_2193_ = l_BitVec_ofNat(v___x_2190_, v___x_2192_);
lean_dec(v___x_2192_);
v___x_2194_ = lp_floatlib_FloatLib_Floats_Formats_BinaryInterchange_Model_maximum(v___x_2188_, v___x_2191_, v___x_2193_);
v___x_2195_ = lean_uint32_of_nat(v___x_2194_);
lean_dec(v___x_2194_);
return v___x_2195_;
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_maxW___boxed(lean_object* v_a_2240_, lean_object* v_b_2241_){
_start:
{
uint32_t v_a_boxed_2242_; uint32_t v_b_boxed_2243_; uint32_t v_res_2244_; lean_object* v_r_2245_; 
v_a_boxed_2242_ = lean_unbox_uint32(v_a_2240_);
lean_dec(v_a_2240_);
v_b_boxed_2243_ = lean_unbox_uint32(v_b_2241_);
lean_dec(v_b_2241_);
v_res_2244_ = lp_competition_Submission_maxW(v_a_boxed_2242_, v_b_boxed_2243_);
v_r_2245_ = lean_box_uint32(v_res_2244_);
return v_r_2245_;
}
}
LEAN_EXPORT uint32_t lp_competition_List_foldl___at___00List_foldl___at___00Submission_maxpoolW_spec__0_spec__0(lean_object* v_ch_2246_, lean_object* v_h_2247_, lean_object* v_y_2248_, lean_object* v_k_2249_, lean_object* v_w_2250_, lean_object* v_x_2251_, lean_object* v_inp_2252_, uint32_t v_x_2253_, lean_object* v_x_2254_){
_start:
{
if (lean_obj_tag(v_x_2254_) == 0)
{
return v_x_2253_;
}
else
{
lean_object* v_head_2255_; lean_object* v_tail_2256_; lean_object* v___y_2258_; uint8_t v___y_2264_; uint8_t v___y_2265_; uint32_t v___x_2267_; lean_object* v___x_2268_; lean_object* v___x_2269_; lean_object* v___x_2270_; lean_object* v___x_2271_; lean_object* v___x_2272_; lean_object* v___x_2273_; lean_object* v___x_2274_; lean_object* v___x_2275_; lean_object* v___x_2276_; lean_object* v___x_2277_; lean_object* v___x_2278_; lean_object* v___x_2279_; uint8_t v___y_2292_; lean_object* v___y_2293_; lean_object* v___y_2294_; uint8_t v___y_2295_; uint8_t v___y_2303_; lean_object* v___y_2304_; lean_object* v___y_2305_; lean_object* v___y_2306_; uint8_t v___y_2307_; lean_object* v___y_2322_; lean_object* v___y_2323_; lean_object* v___y_2342_; lean_object* v___y_2343_; lean_object* v___y_2344_; lean_object* v___y_2349_; lean_object* v___y_2350_; lean_object* v___y_2351_; uint32_t v___y_2355_; lean_object* v___y_2356_; lean_object* v___y_2357_; uint32_t v___y_2369_; lean_object* v___y_2370_; lean_object* v___y_2371_; lean_object* v___y_2383_; lean_object* v___y_2421_; lean_object* v___y_2422_; lean_object* v___y_2426_; lean_object* v___y_2427_; uint32_t v___x_2431_; uint32_t v___x_2432_; uint32_t v___x_2433_; uint32_t v___x_2434_; uint8_t v___x_2435_; 
v_head_2255_ = lean_ctor_get(v_x_2254_, 0);
v_tail_2256_ = lean_ctor_get(v_x_2254_, 1);
v___x_2267_ = 0;
v___x_2268_ = lean_nat_mul(v_ch_2246_, v_h_2247_);
v___x_2269_ = lean_nat_mul(v_y_2248_, v_k_2249_);
v___x_2270_ = lean_nat_add(v___x_2268_, v___x_2269_);
lean_dec(v___x_2269_);
lean_dec(v___x_2268_);
v___x_2271_ = lean_nat_div(v_head_2255_, v_k_2249_);
v___x_2272_ = lean_nat_add(v___x_2270_, v___x_2271_);
lean_dec(v___x_2271_);
lean_dec(v___x_2270_);
v___x_2273_ = lean_nat_mul(v___x_2272_, v_w_2250_);
lean_dec(v___x_2272_);
v___x_2274_ = lean_nat_mul(v_x_2251_, v_k_2249_);
v___x_2275_ = lean_nat_add(v___x_2273_, v___x_2274_);
lean_dec(v___x_2274_);
lean_dec(v___x_2273_);
v___x_2276_ = lean_nat_mod(v_head_2255_, v_k_2249_);
v___x_2277_ = lean_nat_add(v___x_2275_, v___x_2276_);
lean_dec(v___x_2276_);
lean_dec(v___x_2275_);
v___x_2278_ = lp_competition_Submission_dotX___lam__0___boxed__const__1;
v___x_2279_ = lean_array_get_borrowed(v___x_2278_, v_inp_2252_, v___x_2277_);
lean_dec(v___x_2277_);
v___x_2431_ = 23;
v___x_2432_ = lean_uint32_shift_right(v_x_2253_, v___x_2431_);
v___x_2433_ = 255;
v___x_2434_ = lean_uint32_land(v___x_2432_, v___x_2433_);
v___x_2435_ = lean_uint32_dec_eq(v___x_2434_, v___x_2433_);
if (v___x_2435_ == 0)
{
uint32_t v___x_2436_; uint32_t v___x_2437_; uint32_t v___x_2438_; uint8_t v___x_2439_; 
v___x_2436_ = lean_unbox_uint32(v___x_2279_);
v___x_2437_ = lean_uint32_shift_right(v___x_2436_, v___x_2431_);
v___x_2438_ = lean_uint32_land(v___x_2437_, v___x_2433_);
v___x_2439_ = lean_uint32_dec_eq(v___x_2438_, v___x_2433_);
if (v___x_2439_ == 0)
{
uint32_t v___x_2440_; uint32_t v___x_2441_; lean_object* v___y_2443_; lean_object* v___y_2450_; uint8_t v___x_2456_; 
v___x_2440_ = 2147483648;
v___x_2441_ = lean_uint32_land(v_x_2253_, v___x_2440_);
v___x_2456_ = lean_uint32_dec_eq(v___x_2441_, v___x_2267_);
if (v___x_2456_ == 0)
{
uint8_t v___x_2457_; 
v___x_2457_ = lean_uint32_dec_eq(v___x_2434_, v___x_2267_);
if (v___x_2457_ == 0)
{
lean_object* v___x_2458_; uint32_t v___x_2459_; uint32_t v___x_2460_; lean_object* v___x_2461_; lean_object* v___x_2462_; 
v___x_2458_ = lean_unsigned_to_nat(8388608u);
v___x_2459_ = 8388607;
v___x_2460_ = lean_uint32_land(v_x_2253_, v___x_2459_);
v___x_2461_ = lean_uint32_to_nat(v___x_2460_);
v___x_2462_ = lean_nat_add(v___x_2458_, v___x_2461_);
lean_dec(v___x_2461_);
v___y_2450_ = v___x_2462_;
goto v___jp_2449_;
}
else
{
uint32_t v___x_2463_; uint32_t v___x_2464_; lean_object* v___x_2465_; 
v___x_2463_ = 8388607;
v___x_2464_ = lean_uint32_land(v_x_2253_, v___x_2463_);
v___x_2465_ = lean_uint32_to_nat(v___x_2464_);
v___y_2450_ = v___x_2465_;
goto v___jp_2449_;
}
}
else
{
uint8_t v___x_2466_; 
v___x_2466_ = lean_uint32_dec_eq(v___x_2434_, v___x_2267_);
if (v___x_2466_ == 0)
{
lean_object* v___x_2467_; uint32_t v___x_2468_; uint32_t v___x_2469_; lean_object* v___x_2470_; lean_object* v___x_2471_; 
v___x_2467_ = lean_unsigned_to_nat(8388608u);
v___x_2468_ = 8388607;
v___x_2469_ = lean_uint32_land(v_x_2253_, v___x_2468_);
v___x_2470_ = lean_uint32_to_nat(v___x_2469_);
v___x_2471_ = lean_nat_add(v___x_2467_, v___x_2470_);
lean_dec(v___x_2470_);
v___y_2443_ = v___x_2471_;
goto v___jp_2442_;
}
else
{
uint32_t v___x_2472_; uint32_t v___x_2473_; lean_object* v___x_2474_; 
v___x_2472_ = 8388607;
v___x_2473_ = lean_uint32_land(v_x_2253_, v___x_2472_);
v___x_2474_ = lean_uint32_to_nat(v___x_2473_);
v___y_2443_ = v___x_2474_;
goto v___jp_2442_;
}
}
v___jp_2442_:
{
uint8_t v___x_2444_; 
v___x_2444_ = lean_uint32_dec_eq(v___x_2434_, v___x_2267_);
if (v___x_2444_ == 0)
{
lean_object* v___x_2445_; lean_object* v___x_2446_; lean_object* v___x_2447_; 
v___x_2445_ = lean_uint32_to_nat(v___x_2434_);
v___x_2446_ = lean_unsigned_to_nat(1u);
v___x_2447_ = lean_nat_sub(v___x_2445_, v___x_2446_);
lean_dec(v___x_2445_);
v___y_2421_ = v___y_2443_;
v___y_2422_ = v___x_2447_;
goto v___jp_2420_;
}
else
{
lean_object* v___x_2448_; 
v___x_2448_ = lean_unsigned_to_nat(0u);
v___y_2421_ = v___y_2443_;
v___y_2422_ = v___x_2448_;
goto v___jp_2420_;
}
}
v___jp_2449_:
{
uint8_t v___x_2451_; 
v___x_2451_ = lean_uint32_dec_eq(v___x_2434_, v___x_2267_);
if (v___x_2451_ == 0)
{
lean_object* v___x_2452_; lean_object* v___x_2453_; lean_object* v___x_2454_; 
v___x_2452_ = lean_uint32_to_nat(v___x_2434_);
v___x_2453_ = lean_unsigned_to_nat(1u);
v___x_2454_ = lean_nat_sub(v___x_2452_, v___x_2453_);
lean_dec(v___x_2452_);
v___y_2426_ = v___y_2450_;
v___y_2427_ = v___x_2454_;
goto v___jp_2425_;
}
else
{
lean_object* v___x_2455_; 
v___x_2455_ = lean_unsigned_to_nat(0u);
v___y_2426_ = v___y_2450_;
v___y_2427_ = v___x_2455_;
goto v___jp_2425_;
}
}
}
else
{
goto v___jp_2280_;
}
}
else
{
goto v___jp_2280_;
}
v___jp_2257_:
{
uint32_t v___x_2259_; 
v___x_2259_ = lean_uint32_of_nat(v___y_2258_);
lean_dec(v___y_2258_);
v_x_2253_ = v___x_2259_;
v_x_2254_ = v_tail_2256_;
goto _start;
}
v___jp_2261_:
{
lean_object* v___x_2262_; 
v___x_2262_ = lean_obj_once(&lp_competition_Submission_finishDigits___closed__10, &lp_competition_Submission_finishDigits___closed__10_once, _init_lp_competition_Submission_finishDigits___closed__10);
v___y_2258_ = v___x_2262_;
goto v___jp_2257_;
}
v___jp_2263_:
{
if (v___y_2265_ == 0)
{
goto v___jp_2261_;
}
else
{
if (v___y_2264_ == 0)
{
lean_object* v___x_2266_; 
v___x_2266_ = lean_obj_once(&lp_competition_Submission_finishDigits___closed__0, &lp_competition_Submission_finishDigits___closed__0_once, _init_lp_competition_Submission_finishDigits___closed__0);
v___y_2258_ = v___x_2266_;
goto v___jp_2257_;
}
else
{
goto v___jp_2261_;
}
}
}
v___jp_2280_:
{
lean_object* v___x_2281_; lean_object* v___x_2282_; lean_object* v___x_2283_; lean_object* v___x_2284_; uint32_t v___x_2285_; lean_object* v___x_2286_; lean_object* v___x_2287_; lean_object* v___x_2288_; uint32_t v___x_2289_; 
v___x_2281_ = ((lean_object*)(lp_competition_Submission_maxW___closed__2));
v___x_2282_ = lean_uint32_to_nat(v_x_2253_);
v___x_2283_ = lean_unsigned_to_nat(32u);
v___x_2284_ = l_BitVec_ofNat(v___x_2283_, v___x_2282_);
lean_dec(v___x_2282_);
v___x_2285_ = lean_unbox_uint32(v___x_2279_);
v___x_2286_ = lean_uint32_to_nat(v___x_2285_);
v___x_2287_ = l_BitVec_ofNat(v___x_2283_, v___x_2286_);
lean_dec(v___x_2286_);
v___x_2288_ = lp_floatlib_FloatLib_Floats_Formats_BinaryInterchange_Model_maximum(v___x_2281_, v___x_2284_, v___x_2287_);
v___x_2289_ = lean_uint32_of_nat(v___x_2288_);
lean_dec(v___x_2288_);
v_x_2253_ = v___x_2289_;
v_x_2254_ = v_tail_2256_;
goto _start;
}
v___jp_2291_:
{
if (v___y_2295_ == 0)
{
v___y_2258_ = v___y_2294_;
goto v___jp_2257_;
}
else
{
lean_object* v___x_2296_; uint8_t v___x_2297_; 
v___x_2296_ = lean_unsigned_to_nat(31u);
v___x_2297_ = l_Nat_testBit(v___y_2294_, v___x_2296_);
lean_dec(v___y_2294_);
if (v___x_2297_ == 0)
{
v___y_2264_ = v___y_2292_;
v___y_2265_ = v___x_2297_;
goto v___jp_2263_;
}
else
{
uint32_t v___x_2298_; lean_object* v___x_2299_; lean_object* v___x_2300_; uint8_t v___x_2301_; 
v___x_2298_ = lean_unbox_uint32(v___x_2279_);
v___x_2299_ = lean_uint32_to_nat(v___x_2298_);
v___x_2300_ = l_BitVec_ofNat(v___y_2293_, v___x_2299_);
lean_dec(v___x_2299_);
v___x_2301_ = l_Nat_testBit(v___x_2300_, v___x_2296_);
lean_dec(v___x_2300_);
v___y_2264_ = v___y_2292_;
v___y_2265_ = v___x_2301_;
goto v___jp_2263_;
}
}
}
v___jp_2302_:
{
if (v___y_2307_ == 0)
{
v___y_2258_ = v___y_2305_;
goto v___jp_2257_;
}
else
{
uint32_t v___x_2308_; lean_object* v___x_2309_; lean_object* v___x_2310_; lean_object* v___x_2311_; lean_object* v___x_2312_; lean_object* v___x_2313_; lean_object* v___x_2314_; lean_object* v___x_2315_; uint8_t v___x_2316_; 
v___x_2308_ = lean_unbox_uint32(v___x_2279_);
v___x_2309_ = lean_uint32_to_nat(v___x_2308_);
v___x_2310_ = l_BitVec_ofNat(v___y_2304_, v___x_2309_);
lean_dec(v___x_2309_);
v___x_2311_ = lean_nat_shiftr(v___x_2310_, v___y_2306_);
v___x_2312_ = lean_unsigned_to_nat(255u);
v___x_2313_ = l_BitVec_ofNat(v___y_2304_, v___x_2312_);
v___x_2314_ = lean_nat_land(v___x_2311_, v___x_2313_);
lean_dec(v___x_2313_);
lean_dec(v___x_2311_);
v___x_2315_ = lean_unsigned_to_nat(0u);
v___x_2316_ = lean_nat_dec_eq(v___x_2314_, v___x_2315_);
lean_dec(v___x_2314_);
if (v___x_2316_ == 0)
{
lean_dec(v___x_2310_);
v___y_2292_ = v___y_2303_;
v___y_2293_ = v___y_2304_;
v___y_2294_ = v___y_2305_;
v___y_2295_ = v___x_2316_;
goto v___jp_2291_;
}
else
{
lean_object* v___x_2317_; lean_object* v___x_2318_; lean_object* v___x_2319_; uint8_t v___x_2320_; 
v___x_2317_ = lean_unsigned_to_nat(8388607u);
v___x_2318_ = l_BitVec_ofNat(v___y_2304_, v___x_2317_);
v___x_2319_ = lean_nat_land(v___x_2310_, v___x_2318_);
lean_dec(v___x_2318_);
lean_dec(v___x_2310_);
v___x_2320_ = lean_nat_dec_eq(v___x_2319_, v___x_2315_);
lean_dec(v___x_2319_);
v___y_2292_ = v___y_2303_;
v___y_2293_ = v___y_2304_;
v___y_2294_ = v___y_2305_;
v___y_2295_ = v___x_2320_;
goto v___jp_2291_;
}
}
}
v___jp_2321_:
{
uint8_t v___x_2324_; 
v___x_2324_ = lean_int_dec_lt(v___y_2322_, v___y_2323_);
if (v___x_2324_ == 0)
{
uint8_t v___x_2325_; 
v___x_2325_ = lean_int_dec_eq(v___y_2322_, v___y_2323_);
lean_dec(v___y_2323_);
lean_dec(v___y_2322_);
if (v___x_2325_ == 0)
{
v_x_2254_ = v_tail_2256_;
goto _start;
}
else
{
lean_object* v___x_2327_; lean_object* v___x_2328_; lean_object* v___x_2329_; lean_object* v___x_2330_; lean_object* v___x_2331_; lean_object* v___x_2332_; lean_object* v___x_2333_; lean_object* v___x_2334_; uint8_t v___x_2335_; 
v___x_2327_ = lean_unsigned_to_nat(23u);
v___x_2328_ = lean_uint32_to_nat(v_x_2253_);
v___x_2329_ = lean_unsigned_to_nat(32u);
v___x_2330_ = l_BitVec_ofNat(v___x_2329_, v___x_2328_);
lean_dec(v___x_2328_);
v___x_2331_ = lean_nat_shiftr(v___x_2330_, v___x_2327_);
v___x_2332_ = lean_obj_once(&lp_competition_Submission_maxW___closed__0, &lp_competition_Submission_maxW___closed__0_once, _init_lp_competition_Submission_maxW___closed__0);
v___x_2333_ = lean_nat_land(v___x_2331_, v___x_2332_);
lean_dec(v___x_2331_);
v___x_2334_ = lean_unsigned_to_nat(0u);
v___x_2335_ = lean_nat_dec_eq(v___x_2333_, v___x_2334_);
lean_dec(v___x_2333_);
if (v___x_2335_ == 0)
{
v___y_2303_ = v___x_2324_;
v___y_2304_ = v___x_2329_;
v___y_2305_ = v___x_2330_;
v___y_2306_ = v___x_2327_;
v___y_2307_ = v___x_2335_;
goto v___jp_2302_;
}
else
{
lean_object* v___x_2336_; lean_object* v___x_2337_; uint8_t v___x_2338_; 
v___x_2336_ = lean_obj_once(&lp_competition_Submission_maxW___closed__1, &lp_competition_Submission_maxW___closed__1_once, _init_lp_competition_Submission_maxW___closed__1);
v___x_2337_ = lean_nat_land(v___x_2330_, v___x_2336_);
v___x_2338_ = lean_nat_dec_eq(v___x_2337_, v___x_2334_);
lean_dec(v___x_2337_);
v___y_2303_ = v___x_2324_;
v___y_2304_ = v___x_2329_;
v___y_2305_ = v___x_2330_;
v___y_2306_ = v___x_2327_;
v___y_2307_ = v___x_2338_;
goto v___jp_2302_;
}
}
}
else
{
uint32_t v___x_2339_; 
lean_dec(v___y_2323_);
lean_dec(v___y_2322_);
v___x_2339_ = lean_unbox_uint32(v___x_2279_);
v_x_2253_ = v___x_2339_;
v_x_2254_ = v_tail_2256_;
goto _start;
}
}
v___jp_2341_:
{
lean_object* v___x_2345_; lean_object* v___x_2346_; lean_object* v___x_2347_; 
v___x_2345_ = lean_nat_shiftl(v___y_2342_, v___y_2344_);
lean_dec(v___y_2344_);
lean_dec(v___y_2342_);
v___x_2346_ = lean_nat_to_int(v___x_2345_);
v___x_2347_ = lean_int_neg(v___x_2346_);
lean_dec(v___x_2346_);
v___y_2322_ = v___y_2343_;
v___y_2323_ = v___x_2347_;
goto v___jp_2321_;
}
v___jp_2348_:
{
lean_object* v___x_2352_; lean_object* v___x_2353_; 
v___x_2352_ = lean_nat_shiftl(v___y_2350_, v___y_2351_);
lean_dec(v___y_2351_);
lean_dec(v___y_2350_);
v___x_2353_ = lean_nat_to_int(v___x_2352_);
v___y_2322_ = v___y_2349_;
v___y_2323_ = v___x_2353_;
goto v___jp_2321_;
}
v___jp_2354_:
{
uint32_t v___x_2358_; uint32_t v___x_2359_; uint32_t v___x_2360_; uint32_t v___x_2361_; uint32_t v___x_2362_; uint8_t v___x_2363_; 
v___x_2358_ = 23;
v___x_2359_ = lean_unbox_uint32(v___x_2279_);
v___x_2360_ = lean_uint32_shift_right(v___x_2359_, v___x_2358_);
v___x_2361_ = 255;
v___x_2362_ = lean_uint32_land(v___x_2360_, v___x_2361_);
v___x_2363_ = lean_uint32_dec_eq(v___x_2362_, v___y_2355_);
if (v___x_2363_ == 0)
{
lean_object* v___x_2364_; lean_object* v___x_2365_; lean_object* v___x_2366_; 
v___x_2364_ = lean_uint32_to_nat(v___x_2362_);
v___x_2365_ = lean_unsigned_to_nat(1u);
v___x_2366_ = lean_nat_sub(v___x_2364_, v___x_2365_);
lean_dec(v___x_2364_);
v___y_2342_ = v___y_2357_;
v___y_2343_ = v___y_2356_;
v___y_2344_ = v___x_2366_;
goto v___jp_2341_;
}
else
{
lean_object* v___x_2367_; 
v___x_2367_ = lean_unsigned_to_nat(0u);
v___y_2342_ = v___y_2357_;
v___y_2343_ = v___y_2356_;
v___y_2344_ = v___x_2367_;
goto v___jp_2341_;
}
}
v___jp_2368_:
{
uint32_t v___x_2372_; uint32_t v___x_2373_; uint32_t v___x_2374_; uint32_t v___x_2375_; uint32_t v___x_2376_; uint8_t v___x_2377_; 
v___x_2372_ = 23;
v___x_2373_ = lean_unbox_uint32(v___x_2279_);
v___x_2374_ = lean_uint32_shift_right(v___x_2373_, v___x_2372_);
v___x_2375_ = 255;
v___x_2376_ = lean_uint32_land(v___x_2374_, v___x_2375_);
v___x_2377_ = lean_uint32_dec_eq(v___x_2376_, v___y_2369_);
if (v___x_2377_ == 0)
{
lean_object* v___x_2378_; lean_object* v___x_2379_; lean_object* v___x_2380_; 
v___x_2378_ = lean_uint32_to_nat(v___x_2376_);
v___x_2379_ = lean_unsigned_to_nat(1u);
v___x_2380_ = lean_nat_sub(v___x_2378_, v___x_2379_);
lean_dec(v___x_2378_);
v___y_2349_ = v___y_2370_;
v___y_2350_ = v___y_2371_;
v___y_2351_ = v___x_2380_;
goto v___jp_2348_;
}
else
{
lean_object* v___x_2381_; 
v___x_2381_ = lean_unsigned_to_nat(0u);
v___y_2349_ = v___y_2370_;
v___y_2350_ = v___y_2371_;
v___y_2351_ = v___x_2381_;
goto v___jp_2348_;
}
}
v___jp_2382_:
{
uint32_t v___x_2384_; uint32_t v___x_2385_; uint32_t v___x_2386_; uint8_t v___x_2387_; 
v___x_2384_ = 2147483648;
v___x_2385_ = lean_unbox_uint32(v___x_2279_);
v___x_2386_ = lean_uint32_land(v___x_2385_, v___x_2384_);
v___x_2387_ = lean_uint32_dec_eq(v___x_2386_, v___x_2267_);
if (v___x_2387_ == 0)
{
uint32_t v___x_2388_; uint32_t v___x_2389_; uint32_t v___x_2390_; uint32_t v___x_2391_; uint32_t v___x_2392_; uint8_t v___x_2393_; 
v___x_2388_ = 23;
v___x_2389_ = lean_unbox_uint32(v___x_2279_);
v___x_2390_ = lean_uint32_shift_right(v___x_2389_, v___x_2388_);
v___x_2391_ = 255;
v___x_2392_ = lean_uint32_land(v___x_2390_, v___x_2391_);
v___x_2393_ = lean_uint32_dec_eq(v___x_2392_, v___x_2267_);
if (v___x_2393_ == 0)
{
lean_object* v___x_2394_; uint32_t v___x_2395_; uint32_t v___x_2396_; uint32_t v___x_2397_; lean_object* v___x_2398_; lean_object* v___x_2399_; 
v___x_2394_ = lean_unsigned_to_nat(8388608u);
v___x_2395_ = 8388607;
v___x_2396_ = lean_unbox_uint32(v___x_2279_);
v___x_2397_ = lean_uint32_land(v___x_2396_, v___x_2395_);
v___x_2398_ = lean_uint32_to_nat(v___x_2397_);
v___x_2399_ = lean_nat_add(v___x_2394_, v___x_2398_);
lean_dec(v___x_2398_);
v___y_2355_ = v___x_2267_;
v___y_2356_ = v___y_2383_;
v___y_2357_ = v___x_2399_;
goto v___jp_2354_;
}
else
{
uint32_t v___x_2400_; uint32_t v___x_2401_; uint32_t v___x_2402_; lean_object* v___x_2403_; 
v___x_2400_ = 8388607;
v___x_2401_ = lean_unbox_uint32(v___x_2279_);
v___x_2402_ = lean_uint32_land(v___x_2401_, v___x_2400_);
v___x_2403_ = lean_uint32_to_nat(v___x_2402_);
v___y_2355_ = v___x_2267_;
v___y_2356_ = v___y_2383_;
v___y_2357_ = v___x_2403_;
goto v___jp_2354_;
}
}
else
{
uint32_t v___x_2404_; uint32_t v___x_2405_; uint32_t v___x_2406_; uint32_t v___x_2407_; uint32_t v___x_2408_; uint8_t v___x_2409_; 
v___x_2404_ = 23;
v___x_2405_ = lean_unbox_uint32(v___x_2279_);
v___x_2406_ = lean_uint32_shift_right(v___x_2405_, v___x_2404_);
v___x_2407_ = 255;
v___x_2408_ = lean_uint32_land(v___x_2406_, v___x_2407_);
v___x_2409_ = lean_uint32_dec_eq(v___x_2408_, v___x_2267_);
if (v___x_2409_ == 0)
{
lean_object* v___x_2410_; uint32_t v___x_2411_; uint32_t v___x_2412_; uint32_t v___x_2413_; lean_object* v___x_2414_; lean_object* v___x_2415_; 
v___x_2410_ = lean_unsigned_to_nat(8388608u);
v___x_2411_ = 8388607;
v___x_2412_ = lean_unbox_uint32(v___x_2279_);
v___x_2413_ = lean_uint32_land(v___x_2412_, v___x_2411_);
v___x_2414_ = lean_uint32_to_nat(v___x_2413_);
v___x_2415_ = lean_nat_add(v___x_2410_, v___x_2414_);
lean_dec(v___x_2414_);
v___y_2369_ = v___x_2267_;
v___y_2370_ = v___y_2383_;
v___y_2371_ = v___x_2415_;
goto v___jp_2368_;
}
else
{
uint32_t v___x_2416_; uint32_t v___x_2417_; uint32_t v___x_2418_; lean_object* v___x_2419_; 
v___x_2416_ = 8388607;
v___x_2417_ = lean_unbox_uint32(v___x_2279_);
v___x_2418_ = lean_uint32_land(v___x_2417_, v___x_2416_);
v___x_2419_ = lean_uint32_to_nat(v___x_2418_);
v___y_2369_ = v___x_2267_;
v___y_2370_ = v___y_2383_;
v___y_2371_ = v___x_2419_;
goto v___jp_2368_;
}
}
}
v___jp_2420_:
{
lean_object* v___x_2423_; lean_object* v___x_2424_; 
v___x_2423_ = lean_nat_shiftl(v___y_2421_, v___y_2422_);
lean_dec(v___y_2422_);
lean_dec(v___y_2421_);
v___x_2424_ = lean_nat_to_int(v___x_2423_);
v___y_2383_ = v___x_2424_;
goto v___jp_2382_;
}
v___jp_2425_:
{
lean_object* v___x_2428_; lean_object* v___x_2429_; lean_object* v___x_2430_; 
v___x_2428_ = lean_nat_shiftl(v___y_2426_, v___y_2427_);
lean_dec(v___y_2427_);
lean_dec(v___y_2426_);
v___x_2429_ = lean_nat_to_int(v___x_2428_);
v___x_2430_ = lean_int_neg(v___x_2429_);
lean_dec(v___x_2429_);
v___y_2383_ = v___x_2430_;
goto v___jp_2382_;
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_List_foldl___at___00List_foldl___at___00Submission_maxpoolW_spec__0_spec__0___boxed(lean_object* v_ch_2475_, lean_object* v_h_2476_, lean_object* v_y_2477_, lean_object* v_k_2478_, lean_object* v_w_2479_, lean_object* v_x_2480_, lean_object* v_inp_2481_, lean_object* v_x_2482_, lean_object* v_x_2483_){
_start:
{
uint32_t v_x_1512__boxed_2484_; uint32_t v_res_2485_; lean_object* v_r_2486_; 
v_x_1512__boxed_2484_ = lean_unbox_uint32(v_x_2482_);
lean_dec(v_x_2482_);
v_res_2485_ = lp_competition_List_foldl___at___00List_foldl___at___00Submission_maxpoolW_spec__0_spec__0(v_ch_2475_, v_h_2476_, v_y_2477_, v_k_2478_, v_w_2479_, v_x_2480_, v_inp_2481_, v_x_1512__boxed_2484_, v_x_2483_);
lean_dec(v_x_2483_);
lean_dec_ref(v_inp_2481_);
lean_dec(v_x_2480_);
lean_dec(v_w_2479_);
lean_dec(v_k_2478_);
lean_dec(v_y_2477_);
lean_dec(v_h_2476_);
lean_dec(v_ch_2475_);
v_r_2486_ = lean_box_uint32(v_res_2485_);
return v_r_2486_;
}
}
LEAN_EXPORT uint32_t lp_competition_List_foldl___at___00Submission_maxpoolW_spec__0(lean_object* v_ch_2487_, lean_object* v_h_2488_, lean_object* v_y_2489_, lean_object* v_k_2490_, lean_object* v_w_2491_, lean_object* v_x_2492_, lean_object* v_inp_2493_, uint32_t v_x_2494_, lean_object* v_x_2495_){
_start:
{
if (lean_obj_tag(v_x_2495_) == 0)
{
return v_x_2494_;
}
else
{
lean_object* v_head_2496_; lean_object* v_tail_2497_; lean_object* v___y_2499_; uint8_t v___y_2505_; uint8_t v___y_2506_; uint32_t v___x_2508_; lean_object* v___x_2509_; lean_object* v___x_2510_; lean_object* v___x_2511_; lean_object* v___x_2512_; lean_object* v___x_2513_; lean_object* v___x_2514_; lean_object* v___x_2515_; lean_object* v___x_2516_; lean_object* v___x_2517_; lean_object* v___x_2518_; lean_object* v___x_2519_; lean_object* v___x_2520_; lean_object* v___y_2533_; lean_object* v___y_2534_; uint8_t v___y_2535_; uint8_t v___y_2536_; lean_object* v___y_2544_; lean_object* v___y_2545_; lean_object* v___y_2546_; uint8_t v___y_2547_; uint8_t v___y_2548_; lean_object* v___y_2563_; lean_object* v___y_2564_; lean_object* v___y_2583_; lean_object* v___y_2584_; lean_object* v___y_2585_; lean_object* v___y_2590_; lean_object* v___y_2591_; lean_object* v___y_2592_; lean_object* v___y_2596_; uint32_t v___y_2597_; lean_object* v___y_2598_; lean_object* v___y_2610_; uint32_t v___y_2611_; lean_object* v___y_2612_; lean_object* v___y_2624_; lean_object* v___y_2662_; lean_object* v___y_2663_; lean_object* v___y_2667_; lean_object* v___y_2668_; uint32_t v___x_2672_; uint32_t v___x_2673_; uint32_t v___x_2674_; uint32_t v___x_2675_; uint8_t v___x_2676_; 
v_head_2496_ = lean_ctor_get(v_x_2495_, 0);
v_tail_2497_ = lean_ctor_get(v_x_2495_, 1);
v___x_2508_ = 0;
v___x_2509_ = lean_nat_mul(v_ch_2487_, v_h_2488_);
v___x_2510_ = lean_nat_mul(v_y_2489_, v_k_2490_);
v___x_2511_ = lean_nat_add(v___x_2509_, v___x_2510_);
lean_dec(v___x_2510_);
lean_dec(v___x_2509_);
v___x_2512_ = lean_nat_div(v_head_2496_, v_k_2490_);
v___x_2513_ = lean_nat_add(v___x_2511_, v___x_2512_);
lean_dec(v___x_2512_);
lean_dec(v___x_2511_);
v___x_2514_ = lean_nat_mul(v___x_2513_, v_w_2491_);
lean_dec(v___x_2513_);
v___x_2515_ = lean_nat_mul(v_x_2492_, v_k_2490_);
v___x_2516_ = lean_nat_add(v___x_2514_, v___x_2515_);
lean_dec(v___x_2515_);
lean_dec(v___x_2514_);
v___x_2517_ = lean_nat_mod(v_head_2496_, v_k_2490_);
v___x_2518_ = lean_nat_add(v___x_2516_, v___x_2517_);
lean_dec(v___x_2517_);
lean_dec(v___x_2516_);
v___x_2519_ = lp_competition_Submission_dotX___lam__0___boxed__const__1;
v___x_2520_ = lean_array_get_borrowed(v___x_2519_, v_inp_2493_, v___x_2518_);
lean_dec(v___x_2518_);
v___x_2672_ = 23;
v___x_2673_ = lean_uint32_shift_right(v_x_2494_, v___x_2672_);
v___x_2674_ = 255;
v___x_2675_ = lean_uint32_land(v___x_2673_, v___x_2674_);
v___x_2676_ = lean_uint32_dec_eq(v___x_2675_, v___x_2674_);
if (v___x_2676_ == 0)
{
uint32_t v___x_2677_; uint32_t v___x_2678_; uint32_t v___x_2679_; uint8_t v___x_2680_; 
v___x_2677_ = lean_unbox_uint32(v___x_2520_);
v___x_2678_ = lean_uint32_shift_right(v___x_2677_, v___x_2672_);
v___x_2679_ = lean_uint32_land(v___x_2678_, v___x_2674_);
v___x_2680_ = lean_uint32_dec_eq(v___x_2679_, v___x_2674_);
if (v___x_2680_ == 0)
{
uint32_t v___x_2681_; uint32_t v___x_2682_; lean_object* v___y_2684_; lean_object* v___y_2691_; uint8_t v___x_2697_; 
v___x_2681_ = 2147483648;
v___x_2682_ = lean_uint32_land(v_x_2494_, v___x_2681_);
v___x_2697_ = lean_uint32_dec_eq(v___x_2682_, v___x_2508_);
if (v___x_2697_ == 0)
{
uint8_t v___x_2698_; 
v___x_2698_ = lean_uint32_dec_eq(v___x_2675_, v___x_2508_);
if (v___x_2698_ == 0)
{
lean_object* v___x_2699_; uint32_t v___x_2700_; uint32_t v___x_2701_; lean_object* v___x_2702_; lean_object* v___x_2703_; 
v___x_2699_ = lean_unsigned_to_nat(8388608u);
v___x_2700_ = 8388607;
v___x_2701_ = lean_uint32_land(v_x_2494_, v___x_2700_);
v___x_2702_ = lean_uint32_to_nat(v___x_2701_);
v___x_2703_ = lean_nat_add(v___x_2699_, v___x_2702_);
lean_dec(v___x_2702_);
v___y_2691_ = v___x_2703_;
goto v___jp_2690_;
}
else
{
uint32_t v___x_2704_; uint32_t v___x_2705_; lean_object* v___x_2706_; 
v___x_2704_ = 8388607;
v___x_2705_ = lean_uint32_land(v_x_2494_, v___x_2704_);
v___x_2706_ = lean_uint32_to_nat(v___x_2705_);
v___y_2691_ = v___x_2706_;
goto v___jp_2690_;
}
}
else
{
uint8_t v___x_2707_; 
v___x_2707_ = lean_uint32_dec_eq(v___x_2675_, v___x_2508_);
if (v___x_2707_ == 0)
{
lean_object* v___x_2708_; uint32_t v___x_2709_; uint32_t v___x_2710_; lean_object* v___x_2711_; lean_object* v___x_2712_; 
v___x_2708_ = lean_unsigned_to_nat(8388608u);
v___x_2709_ = 8388607;
v___x_2710_ = lean_uint32_land(v_x_2494_, v___x_2709_);
v___x_2711_ = lean_uint32_to_nat(v___x_2710_);
v___x_2712_ = lean_nat_add(v___x_2708_, v___x_2711_);
lean_dec(v___x_2711_);
v___y_2684_ = v___x_2712_;
goto v___jp_2683_;
}
else
{
uint32_t v___x_2713_; uint32_t v___x_2714_; lean_object* v___x_2715_; 
v___x_2713_ = 8388607;
v___x_2714_ = lean_uint32_land(v_x_2494_, v___x_2713_);
v___x_2715_ = lean_uint32_to_nat(v___x_2714_);
v___y_2684_ = v___x_2715_;
goto v___jp_2683_;
}
}
v___jp_2683_:
{
uint8_t v___x_2685_; 
v___x_2685_ = lean_uint32_dec_eq(v___x_2675_, v___x_2508_);
if (v___x_2685_ == 0)
{
lean_object* v___x_2686_; lean_object* v___x_2687_; lean_object* v___x_2688_; 
v___x_2686_ = lean_uint32_to_nat(v___x_2675_);
v___x_2687_ = lean_unsigned_to_nat(1u);
v___x_2688_ = lean_nat_sub(v___x_2686_, v___x_2687_);
lean_dec(v___x_2686_);
v___y_2662_ = v___y_2684_;
v___y_2663_ = v___x_2688_;
goto v___jp_2661_;
}
else
{
lean_object* v___x_2689_; 
v___x_2689_ = lean_unsigned_to_nat(0u);
v___y_2662_ = v___y_2684_;
v___y_2663_ = v___x_2689_;
goto v___jp_2661_;
}
}
v___jp_2690_:
{
uint8_t v___x_2692_; 
v___x_2692_ = lean_uint32_dec_eq(v___x_2675_, v___x_2508_);
if (v___x_2692_ == 0)
{
lean_object* v___x_2693_; lean_object* v___x_2694_; lean_object* v___x_2695_; 
v___x_2693_ = lean_uint32_to_nat(v___x_2675_);
v___x_2694_ = lean_unsigned_to_nat(1u);
v___x_2695_ = lean_nat_sub(v___x_2693_, v___x_2694_);
lean_dec(v___x_2693_);
v___y_2667_ = v___y_2691_;
v___y_2668_ = v___x_2695_;
goto v___jp_2666_;
}
else
{
lean_object* v___x_2696_; 
v___x_2696_ = lean_unsigned_to_nat(0u);
v___y_2667_ = v___y_2691_;
v___y_2668_ = v___x_2696_;
goto v___jp_2666_;
}
}
}
else
{
goto v___jp_2521_;
}
}
else
{
goto v___jp_2521_;
}
v___jp_2498_:
{
uint32_t v___x_2500_; uint32_t v___x_2501_; 
v___x_2500_ = lean_uint32_of_nat(v___y_2499_);
lean_dec(v___y_2499_);
v___x_2501_ = lp_competition_List_foldl___at___00List_foldl___at___00Submission_maxpoolW_spec__0_spec__0(v_ch_2487_, v_h_2488_, v_y_2489_, v_k_2490_, v_w_2491_, v_x_2492_, v_inp_2493_, v___x_2500_, v_tail_2497_);
return v___x_2501_;
}
v___jp_2502_:
{
lean_object* v___x_2503_; 
v___x_2503_ = lean_obj_once(&lp_competition_Submission_finishDigits___closed__10, &lp_competition_Submission_finishDigits___closed__10_once, _init_lp_competition_Submission_finishDigits___closed__10);
v___y_2499_ = v___x_2503_;
goto v___jp_2498_;
}
v___jp_2504_:
{
if (v___y_2506_ == 0)
{
goto v___jp_2502_;
}
else
{
if (v___y_2505_ == 0)
{
lean_object* v___x_2507_; 
v___x_2507_ = lean_obj_once(&lp_competition_Submission_finishDigits___closed__0, &lp_competition_Submission_finishDigits___closed__0_once, _init_lp_competition_Submission_finishDigits___closed__0);
v___y_2499_ = v___x_2507_;
goto v___jp_2498_;
}
else
{
goto v___jp_2502_;
}
}
}
v___jp_2521_:
{
lean_object* v___x_2522_; lean_object* v___x_2523_; lean_object* v___x_2524_; lean_object* v___x_2525_; uint32_t v___x_2526_; lean_object* v___x_2527_; lean_object* v___x_2528_; lean_object* v___x_2529_; uint32_t v___x_2530_; uint32_t v___x_2531_; 
v___x_2522_ = ((lean_object*)(lp_competition_Submission_maxW___closed__2));
v___x_2523_ = lean_uint32_to_nat(v_x_2494_);
v___x_2524_ = lean_unsigned_to_nat(32u);
v___x_2525_ = l_BitVec_ofNat(v___x_2524_, v___x_2523_);
lean_dec(v___x_2523_);
v___x_2526_ = lean_unbox_uint32(v___x_2520_);
v___x_2527_ = lean_uint32_to_nat(v___x_2526_);
v___x_2528_ = l_BitVec_ofNat(v___x_2524_, v___x_2527_);
lean_dec(v___x_2527_);
v___x_2529_ = lp_floatlib_FloatLib_Floats_Formats_BinaryInterchange_Model_maximum(v___x_2522_, v___x_2525_, v___x_2528_);
v___x_2530_ = lean_uint32_of_nat(v___x_2529_);
lean_dec(v___x_2529_);
v___x_2531_ = lp_competition_List_foldl___at___00List_foldl___at___00Submission_maxpoolW_spec__0_spec__0(v_ch_2487_, v_h_2488_, v_y_2489_, v_k_2490_, v_w_2491_, v_x_2492_, v_inp_2493_, v___x_2530_, v_tail_2497_);
return v___x_2531_;
}
v___jp_2532_:
{
if (v___y_2536_ == 0)
{
v___y_2499_ = v___y_2534_;
goto v___jp_2498_;
}
else
{
lean_object* v___x_2537_; uint8_t v___x_2538_; 
v___x_2537_ = lean_unsigned_to_nat(31u);
v___x_2538_ = l_Nat_testBit(v___y_2534_, v___x_2537_);
lean_dec(v___y_2534_);
if (v___x_2538_ == 0)
{
v___y_2505_ = v___y_2535_;
v___y_2506_ = v___x_2538_;
goto v___jp_2504_;
}
else
{
uint32_t v___x_2539_; lean_object* v___x_2540_; lean_object* v___x_2541_; uint8_t v___x_2542_; 
v___x_2539_ = lean_unbox_uint32(v___x_2520_);
v___x_2540_ = lean_uint32_to_nat(v___x_2539_);
v___x_2541_ = l_BitVec_ofNat(v___y_2533_, v___x_2540_);
lean_dec(v___x_2540_);
v___x_2542_ = l_Nat_testBit(v___x_2541_, v___x_2537_);
lean_dec(v___x_2541_);
v___y_2505_ = v___y_2535_;
v___y_2506_ = v___x_2542_;
goto v___jp_2504_;
}
}
}
v___jp_2543_:
{
if (v___y_2548_ == 0)
{
v___y_2499_ = v___y_2546_;
goto v___jp_2498_;
}
else
{
uint32_t v___x_2549_; lean_object* v___x_2550_; lean_object* v___x_2551_; lean_object* v___x_2552_; lean_object* v___x_2553_; lean_object* v___x_2554_; lean_object* v___x_2555_; lean_object* v___x_2556_; uint8_t v___x_2557_; 
v___x_2549_ = lean_unbox_uint32(v___x_2520_);
v___x_2550_ = lean_uint32_to_nat(v___x_2549_);
v___x_2551_ = l_BitVec_ofNat(v___y_2544_, v___x_2550_);
lean_dec(v___x_2550_);
v___x_2552_ = lean_nat_shiftr(v___x_2551_, v___y_2545_);
v___x_2553_ = lean_unsigned_to_nat(255u);
v___x_2554_ = l_BitVec_ofNat(v___y_2544_, v___x_2553_);
v___x_2555_ = lean_nat_land(v___x_2552_, v___x_2554_);
lean_dec(v___x_2554_);
lean_dec(v___x_2552_);
v___x_2556_ = lean_unsigned_to_nat(0u);
v___x_2557_ = lean_nat_dec_eq(v___x_2555_, v___x_2556_);
lean_dec(v___x_2555_);
if (v___x_2557_ == 0)
{
lean_dec(v___x_2551_);
v___y_2533_ = v___y_2544_;
v___y_2534_ = v___y_2546_;
v___y_2535_ = v___y_2547_;
v___y_2536_ = v___x_2557_;
goto v___jp_2532_;
}
else
{
lean_object* v___x_2558_; lean_object* v___x_2559_; lean_object* v___x_2560_; uint8_t v___x_2561_; 
v___x_2558_ = lean_unsigned_to_nat(8388607u);
v___x_2559_ = l_BitVec_ofNat(v___y_2544_, v___x_2558_);
v___x_2560_ = lean_nat_land(v___x_2551_, v___x_2559_);
lean_dec(v___x_2559_);
lean_dec(v___x_2551_);
v___x_2561_ = lean_nat_dec_eq(v___x_2560_, v___x_2556_);
lean_dec(v___x_2560_);
v___y_2533_ = v___y_2544_;
v___y_2534_ = v___y_2546_;
v___y_2535_ = v___y_2547_;
v___y_2536_ = v___x_2561_;
goto v___jp_2532_;
}
}
}
v___jp_2562_:
{
uint8_t v___x_2565_; 
v___x_2565_ = lean_int_dec_lt(v___y_2563_, v___y_2564_);
if (v___x_2565_ == 0)
{
uint8_t v___x_2566_; 
v___x_2566_ = lean_int_dec_eq(v___y_2563_, v___y_2564_);
lean_dec(v___y_2564_);
lean_dec(v___y_2563_);
if (v___x_2566_ == 0)
{
uint32_t v___x_2567_; 
v___x_2567_ = lp_competition_List_foldl___at___00List_foldl___at___00Submission_maxpoolW_spec__0_spec__0(v_ch_2487_, v_h_2488_, v_y_2489_, v_k_2490_, v_w_2491_, v_x_2492_, v_inp_2493_, v_x_2494_, v_tail_2497_);
return v___x_2567_;
}
else
{
lean_object* v___x_2568_; lean_object* v___x_2569_; lean_object* v___x_2570_; lean_object* v___x_2571_; lean_object* v___x_2572_; lean_object* v___x_2573_; lean_object* v___x_2574_; lean_object* v___x_2575_; uint8_t v___x_2576_; 
v___x_2568_ = lean_unsigned_to_nat(23u);
v___x_2569_ = lean_uint32_to_nat(v_x_2494_);
v___x_2570_ = lean_unsigned_to_nat(32u);
v___x_2571_ = l_BitVec_ofNat(v___x_2570_, v___x_2569_);
lean_dec(v___x_2569_);
v___x_2572_ = lean_nat_shiftr(v___x_2571_, v___x_2568_);
v___x_2573_ = lean_obj_once(&lp_competition_Submission_maxW___closed__0, &lp_competition_Submission_maxW___closed__0_once, _init_lp_competition_Submission_maxW___closed__0);
v___x_2574_ = lean_nat_land(v___x_2572_, v___x_2573_);
lean_dec(v___x_2572_);
v___x_2575_ = lean_unsigned_to_nat(0u);
v___x_2576_ = lean_nat_dec_eq(v___x_2574_, v___x_2575_);
lean_dec(v___x_2574_);
if (v___x_2576_ == 0)
{
v___y_2544_ = v___x_2570_;
v___y_2545_ = v___x_2568_;
v___y_2546_ = v___x_2571_;
v___y_2547_ = v___x_2565_;
v___y_2548_ = v___x_2576_;
goto v___jp_2543_;
}
else
{
lean_object* v___x_2577_; lean_object* v___x_2578_; uint8_t v___x_2579_; 
v___x_2577_ = lean_obj_once(&lp_competition_Submission_maxW___closed__1, &lp_competition_Submission_maxW___closed__1_once, _init_lp_competition_Submission_maxW___closed__1);
v___x_2578_ = lean_nat_land(v___x_2571_, v___x_2577_);
v___x_2579_ = lean_nat_dec_eq(v___x_2578_, v___x_2575_);
lean_dec(v___x_2578_);
v___y_2544_ = v___x_2570_;
v___y_2545_ = v___x_2568_;
v___y_2546_ = v___x_2571_;
v___y_2547_ = v___x_2565_;
v___y_2548_ = v___x_2579_;
goto v___jp_2543_;
}
}
}
else
{
uint32_t v___x_2580_; uint32_t v___x_2581_; 
lean_dec(v___y_2564_);
lean_dec(v___y_2563_);
v___x_2580_ = lean_unbox_uint32(v___x_2520_);
v___x_2581_ = lp_competition_List_foldl___at___00List_foldl___at___00Submission_maxpoolW_spec__0_spec__0(v_ch_2487_, v_h_2488_, v_y_2489_, v_k_2490_, v_w_2491_, v_x_2492_, v_inp_2493_, v___x_2580_, v_tail_2497_);
return v___x_2581_;
}
}
v___jp_2582_:
{
lean_object* v___x_2586_; lean_object* v___x_2587_; lean_object* v___x_2588_; 
v___x_2586_ = lean_nat_shiftl(v___y_2584_, v___y_2585_);
lean_dec(v___y_2585_);
lean_dec(v___y_2584_);
v___x_2587_ = lean_nat_to_int(v___x_2586_);
v___x_2588_ = lean_int_neg(v___x_2587_);
lean_dec(v___x_2587_);
v___y_2563_ = v___y_2583_;
v___y_2564_ = v___x_2588_;
goto v___jp_2562_;
}
v___jp_2589_:
{
lean_object* v___x_2593_; lean_object* v___x_2594_; 
v___x_2593_ = lean_nat_shiftl(v___y_2590_, v___y_2592_);
lean_dec(v___y_2592_);
lean_dec(v___y_2590_);
v___x_2594_ = lean_nat_to_int(v___x_2593_);
v___y_2563_ = v___y_2591_;
v___y_2564_ = v___x_2594_;
goto v___jp_2562_;
}
v___jp_2595_:
{
uint32_t v___x_2599_; uint32_t v___x_2600_; uint32_t v___x_2601_; uint32_t v___x_2602_; uint32_t v___x_2603_; uint8_t v___x_2604_; 
v___x_2599_ = 23;
v___x_2600_ = lean_unbox_uint32(v___x_2520_);
v___x_2601_ = lean_uint32_shift_right(v___x_2600_, v___x_2599_);
v___x_2602_ = 255;
v___x_2603_ = lean_uint32_land(v___x_2601_, v___x_2602_);
v___x_2604_ = lean_uint32_dec_eq(v___x_2603_, v___y_2597_);
if (v___x_2604_ == 0)
{
lean_object* v___x_2605_; lean_object* v___x_2606_; lean_object* v___x_2607_; 
v___x_2605_ = lean_uint32_to_nat(v___x_2603_);
v___x_2606_ = lean_unsigned_to_nat(1u);
v___x_2607_ = lean_nat_sub(v___x_2605_, v___x_2606_);
lean_dec(v___x_2605_);
v___y_2583_ = v___y_2596_;
v___y_2584_ = v___y_2598_;
v___y_2585_ = v___x_2607_;
goto v___jp_2582_;
}
else
{
lean_object* v___x_2608_; 
v___x_2608_ = lean_unsigned_to_nat(0u);
v___y_2583_ = v___y_2596_;
v___y_2584_ = v___y_2598_;
v___y_2585_ = v___x_2608_;
goto v___jp_2582_;
}
}
v___jp_2609_:
{
uint32_t v___x_2613_; uint32_t v___x_2614_; uint32_t v___x_2615_; uint32_t v___x_2616_; uint32_t v___x_2617_; uint8_t v___x_2618_; 
v___x_2613_ = 23;
v___x_2614_ = lean_unbox_uint32(v___x_2520_);
v___x_2615_ = lean_uint32_shift_right(v___x_2614_, v___x_2613_);
v___x_2616_ = 255;
v___x_2617_ = lean_uint32_land(v___x_2615_, v___x_2616_);
v___x_2618_ = lean_uint32_dec_eq(v___x_2617_, v___y_2611_);
if (v___x_2618_ == 0)
{
lean_object* v___x_2619_; lean_object* v___x_2620_; lean_object* v___x_2621_; 
v___x_2619_ = lean_uint32_to_nat(v___x_2617_);
v___x_2620_ = lean_unsigned_to_nat(1u);
v___x_2621_ = lean_nat_sub(v___x_2619_, v___x_2620_);
lean_dec(v___x_2619_);
v___y_2590_ = v___y_2612_;
v___y_2591_ = v___y_2610_;
v___y_2592_ = v___x_2621_;
goto v___jp_2589_;
}
else
{
lean_object* v___x_2622_; 
v___x_2622_ = lean_unsigned_to_nat(0u);
v___y_2590_ = v___y_2612_;
v___y_2591_ = v___y_2610_;
v___y_2592_ = v___x_2622_;
goto v___jp_2589_;
}
}
v___jp_2623_:
{
uint32_t v___x_2625_; uint32_t v___x_2626_; uint32_t v___x_2627_; uint8_t v___x_2628_; 
v___x_2625_ = 2147483648;
v___x_2626_ = lean_unbox_uint32(v___x_2520_);
v___x_2627_ = lean_uint32_land(v___x_2626_, v___x_2625_);
v___x_2628_ = lean_uint32_dec_eq(v___x_2627_, v___x_2508_);
if (v___x_2628_ == 0)
{
uint32_t v___x_2629_; uint32_t v___x_2630_; uint32_t v___x_2631_; uint32_t v___x_2632_; uint32_t v___x_2633_; uint8_t v___x_2634_; 
v___x_2629_ = 23;
v___x_2630_ = lean_unbox_uint32(v___x_2520_);
v___x_2631_ = lean_uint32_shift_right(v___x_2630_, v___x_2629_);
v___x_2632_ = 255;
v___x_2633_ = lean_uint32_land(v___x_2631_, v___x_2632_);
v___x_2634_ = lean_uint32_dec_eq(v___x_2633_, v___x_2508_);
if (v___x_2634_ == 0)
{
lean_object* v___x_2635_; uint32_t v___x_2636_; uint32_t v___x_2637_; uint32_t v___x_2638_; lean_object* v___x_2639_; lean_object* v___x_2640_; 
v___x_2635_ = lean_unsigned_to_nat(8388608u);
v___x_2636_ = 8388607;
v___x_2637_ = lean_unbox_uint32(v___x_2520_);
v___x_2638_ = lean_uint32_land(v___x_2637_, v___x_2636_);
v___x_2639_ = lean_uint32_to_nat(v___x_2638_);
v___x_2640_ = lean_nat_add(v___x_2635_, v___x_2639_);
lean_dec(v___x_2639_);
v___y_2596_ = v___y_2624_;
v___y_2597_ = v___x_2508_;
v___y_2598_ = v___x_2640_;
goto v___jp_2595_;
}
else
{
uint32_t v___x_2641_; uint32_t v___x_2642_; uint32_t v___x_2643_; lean_object* v___x_2644_; 
v___x_2641_ = 8388607;
v___x_2642_ = lean_unbox_uint32(v___x_2520_);
v___x_2643_ = lean_uint32_land(v___x_2642_, v___x_2641_);
v___x_2644_ = lean_uint32_to_nat(v___x_2643_);
v___y_2596_ = v___y_2624_;
v___y_2597_ = v___x_2508_;
v___y_2598_ = v___x_2644_;
goto v___jp_2595_;
}
}
else
{
uint32_t v___x_2645_; uint32_t v___x_2646_; uint32_t v___x_2647_; uint32_t v___x_2648_; uint32_t v___x_2649_; uint8_t v___x_2650_; 
v___x_2645_ = 23;
v___x_2646_ = lean_unbox_uint32(v___x_2520_);
v___x_2647_ = lean_uint32_shift_right(v___x_2646_, v___x_2645_);
v___x_2648_ = 255;
v___x_2649_ = lean_uint32_land(v___x_2647_, v___x_2648_);
v___x_2650_ = lean_uint32_dec_eq(v___x_2649_, v___x_2508_);
if (v___x_2650_ == 0)
{
lean_object* v___x_2651_; uint32_t v___x_2652_; uint32_t v___x_2653_; uint32_t v___x_2654_; lean_object* v___x_2655_; lean_object* v___x_2656_; 
v___x_2651_ = lean_unsigned_to_nat(8388608u);
v___x_2652_ = 8388607;
v___x_2653_ = lean_unbox_uint32(v___x_2520_);
v___x_2654_ = lean_uint32_land(v___x_2653_, v___x_2652_);
v___x_2655_ = lean_uint32_to_nat(v___x_2654_);
v___x_2656_ = lean_nat_add(v___x_2651_, v___x_2655_);
lean_dec(v___x_2655_);
v___y_2610_ = v___y_2624_;
v___y_2611_ = v___x_2508_;
v___y_2612_ = v___x_2656_;
goto v___jp_2609_;
}
else
{
uint32_t v___x_2657_; uint32_t v___x_2658_; uint32_t v___x_2659_; lean_object* v___x_2660_; 
v___x_2657_ = 8388607;
v___x_2658_ = lean_unbox_uint32(v___x_2520_);
v___x_2659_ = lean_uint32_land(v___x_2658_, v___x_2657_);
v___x_2660_ = lean_uint32_to_nat(v___x_2659_);
v___y_2610_ = v___y_2624_;
v___y_2611_ = v___x_2508_;
v___y_2612_ = v___x_2660_;
goto v___jp_2609_;
}
}
}
v___jp_2661_:
{
lean_object* v___x_2664_; lean_object* v___x_2665_; 
v___x_2664_ = lean_nat_shiftl(v___y_2662_, v___y_2663_);
lean_dec(v___y_2663_);
lean_dec(v___y_2662_);
v___x_2665_ = lean_nat_to_int(v___x_2664_);
v___y_2624_ = v___x_2665_;
goto v___jp_2623_;
}
v___jp_2666_:
{
lean_object* v___x_2669_; lean_object* v___x_2670_; lean_object* v___x_2671_; 
v___x_2669_ = lean_nat_shiftl(v___y_2667_, v___y_2668_);
lean_dec(v___y_2668_);
lean_dec(v___y_2667_);
v___x_2670_ = lean_nat_to_int(v___x_2669_);
v___x_2671_ = lean_int_neg(v___x_2670_);
lean_dec(v___x_2670_);
v___y_2624_ = v___x_2671_;
goto v___jp_2623_;
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_List_foldl___at___00Submission_maxpoolW_spec__0___boxed(lean_object* v_ch_2716_, lean_object* v_h_2717_, lean_object* v_y_2718_, lean_object* v_k_2719_, lean_object* v_w_2720_, lean_object* v_x_2721_, lean_object* v_inp_2722_, lean_object* v_x_2723_, lean_object* v_x_2724_){
_start:
{
uint32_t v_x_1987__boxed_2725_; uint32_t v_res_2726_; lean_object* v_r_2727_; 
v_x_1987__boxed_2725_ = lean_unbox_uint32(v_x_2723_);
lean_dec(v_x_2723_);
v_res_2726_ = lp_competition_List_foldl___at___00Submission_maxpoolW_spec__0(v_ch_2716_, v_h_2717_, v_y_2718_, v_k_2719_, v_w_2720_, v_x_2721_, v_inp_2722_, v_x_1987__boxed_2725_, v_x_2724_);
lean_dec(v_x_2724_);
lean_dec_ref(v_inp_2722_);
lean_dec(v_x_2721_);
lean_dec(v_w_2720_);
lean_dec(v_k_2719_);
lean_dec(v_y_2718_);
lean_dec(v_h_2717_);
lean_dec(v_ch_2716_);
v_r_2727_ = lean_box_uint32(v_res_2726_);
return v_r_2727_;
}
}
LEAN_EXPORT uint32_t lp_competition_Submission_maxpoolW___lam__0(lean_object* v___x_2728_, lean_object* v___x_2729_, lean_object* v___x_2730_, lean_object* v_h_2731_, lean_object* v_k_2732_, lean_object* v_w_2733_, lean_object* v_inp_2734_, lean_object* v_q_2735_){
_start:
{
lean_object* v_ch_2736_; lean_object* v___x_2737_; lean_object* v_y_2738_; lean_object* v_x_2739_; lean_object* v___x_2740_; lean_object* v___x_2741_; lean_object* v___x_2742_; lean_object* v___x_2743_; lean_object* v___x_2744_; lean_object* v___x_2745_; lean_object* v___x_2746_; lean_object* v___x_2747_; lean_object* v___x_2748_; lean_object* v___x_2749_; lean_object* v___x_2750_; lean_object* v___x_2751_; lean_object* v___x_2752_; lean_object* v___x_2753_; lean_object* v___x_2754_; uint32_t v___x_2755_; uint32_t v___x_2756_; 
v_ch_2736_ = lean_nat_div(v_q_2735_, v___x_2728_);
v___x_2737_ = lean_nat_div(v_q_2735_, v___x_2729_);
v_y_2738_ = lean_nat_mod(v___x_2737_, v___x_2730_);
lean_dec(v___x_2737_);
v_x_2739_ = lean_nat_mod(v_q_2735_, v___x_2729_);
v___x_2740_ = lean_unsigned_to_nat(0u);
v___x_2741_ = lean_nat_mul(v_ch_2736_, v_h_2731_);
v___x_2742_ = lean_nat_mul(v_y_2738_, v_k_2732_);
v___x_2743_ = lean_nat_add(v___x_2741_, v___x_2742_);
lean_dec(v___x_2742_);
lean_dec(v___x_2741_);
v___x_2744_ = lean_nat_div(v___x_2740_, v_k_2732_);
v___x_2745_ = lean_nat_add(v___x_2743_, v___x_2744_);
lean_dec(v___x_2744_);
lean_dec(v___x_2743_);
v___x_2746_ = lean_nat_mul(v___x_2745_, v_w_2733_);
lean_dec(v___x_2745_);
v___x_2747_ = lean_nat_mul(v_x_2739_, v_k_2732_);
v___x_2748_ = lean_nat_add(v___x_2746_, v___x_2747_);
lean_dec(v___x_2747_);
lean_dec(v___x_2746_);
v___x_2749_ = lean_nat_mod(v___x_2740_, v_k_2732_);
v___x_2750_ = lean_nat_add(v___x_2748_, v___x_2749_);
lean_dec(v___x_2749_);
lean_dec(v___x_2748_);
v___x_2751_ = lp_competition_Submission_dotX___lam__0___boxed__const__1;
v___x_2752_ = lean_array_get_borrowed(v___x_2751_, v_inp_2734_, v___x_2750_);
lean_dec(v___x_2750_);
v___x_2753_ = lean_nat_mul(v_k_2732_, v_k_2732_);
v___x_2754_ = l_List_range(v___x_2753_);
v___x_2755_ = lean_unbox_uint32(v___x_2752_);
v___x_2756_ = lp_competition_List_foldl___at___00Submission_maxpoolW_spec__0(v_ch_2736_, v_h_2731_, v_y_2738_, v_k_2732_, v_w_2733_, v_x_2739_, v_inp_2734_, v___x_2755_, v___x_2754_);
lean_dec(v___x_2754_);
lean_dec(v_x_2739_);
lean_dec(v_y_2738_);
lean_dec(v_ch_2736_);
return v___x_2756_;
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_maxpoolW___lam__0___boxed(lean_object* v___x_2757_, lean_object* v___x_2758_, lean_object* v___x_2759_, lean_object* v_h_2760_, lean_object* v_k_2761_, lean_object* v_w_2762_, lean_object* v_inp_2763_, lean_object* v_q_2764_){
_start:
{
uint32_t v_res_2765_; lean_object* v_r_2766_; 
v_res_2765_ = lp_competition_Submission_maxpoolW___lam__0(v___x_2757_, v___x_2758_, v___x_2759_, v_h_2760_, v_k_2761_, v_w_2762_, v_inp_2763_, v_q_2764_);
lean_dec(v_q_2764_);
lean_dec_ref(v_inp_2763_);
lean_dec(v_w_2762_);
lean_dec(v_k_2761_);
lean_dec(v_h_2760_);
lean_dec(v___x_2759_);
lean_dec(v___x_2758_);
lean_dec(v___x_2757_);
v_r_2766_ = lean_box_uint32(v_res_2765_);
return v_r_2766_;
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_maxpoolW(lean_object* v_c_2767_, lean_object* v_h_2768_, lean_object* v_w_2769_, lean_object* v_k_2770_, lean_object* v_inp_2771_){
_start:
{
lean_object* v___x_2772_; lean_object* v___x_2773_; lean_object* v___x_2774_; lean_object* v___f_2775_; lean_object* v___x_2776_; lean_object* v___x_2777_; 
v___x_2772_ = lean_nat_div(v_h_2768_, v_k_2770_);
v___x_2773_ = lean_nat_div(v_w_2769_, v_k_2770_);
v___x_2774_ = lean_nat_mul(v___x_2772_, v___x_2773_);
lean_inc(v___x_2774_);
v___f_2775_ = lean_alloc_closure((void*)(lp_competition_Submission_maxpoolW___lam__0___boxed), 8, 7);
lean_closure_set(v___f_2775_, 0, v___x_2774_);
lean_closure_set(v___f_2775_, 1, v___x_2773_);
lean_closure_set(v___f_2775_, 2, v___x_2772_);
lean_closure_set(v___f_2775_, 3, v_h_2768_);
lean_closure_set(v___f_2775_, 4, v_k_2770_);
lean_closure_set(v___f_2775_, 5, v_w_2769_);
lean_closure_set(v___f_2775_, 6, v_inp_2771_);
v___x_2776_ = lean_nat_mul(v_c_2767_, v___x_2774_);
lean_dec(v___x_2774_);
v___x_2777_ = l_Array_ofFn___redArg(v___x_2776_, v___f_2775_);
return v___x_2777_;
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_maxpoolW___boxed(lean_object* v_c_2778_, lean_object* v_h_2779_, lean_object* v_w_2780_, lean_object* v_k_2781_, lean_object* v_inp_2782_){
_start:
{
lean_object* v_res_2783_; 
v_res_2783_ = lp_competition_Submission_maxpoolW(v_c_2778_, v_h_2779_, v_w_2780_, v_k_2781_, v_inp_2782_);
lean_dec(v_c_2778_);
return v_res_2783_;
}
}
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_mapMUnsafe_map___at___00Submission_cacheRats_spec__0(size_t v_sz_2784_, size_t v_i_2785_, lean_object* v_bs_2786_){
_start:
{
uint8_t v___x_2787_; 
v___x_2787_ = lean_usize_dec_lt(v_i_2785_, v_sz_2784_);
if (v___x_2787_ == 0)
{
return v_bs_2786_;
}
else
{
lean_object* v_v_2788_; lean_object* v___x_2789_; lean_object* v_bs_x27_2790_; uint32_t v___x_2791_; lean_object* v___x_2792_; size_t v___x_2793_; size_t v___x_2794_; lean_object* v___x_2795_; 
v_v_2788_ = lean_array_uget(v_bs_2786_, v_i_2785_);
v___x_2789_ = lean_unsigned_to_nat(0u);
v_bs_x27_2790_ = lean_array_uset(v_bs_2786_, v_i_2785_, v___x_2789_);
v___x_2791_ = lean_unbox_uint32(v_v_2788_);
lean_dec(v_v_2788_);
v___x_2792_ = lp_competition_ExactRuntime_rationalWord(v___x_2791_);
v___x_2793_ = ((size_t)1ULL);
v___x_2794_ = lean_usize_add(v_i_2785_, v___x_2793_);
v___x_2795_ = lean_array_uset(v_bs_x27_2790_, v_i_2785_, v___x_2792_);
v_i_2785_ = v___x_2794_;
v_bs_2786_ = v___x_2795_;
goto _start;
}
}
}
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_mapMUnsafe_map___at___00Submission_cacheRats_spec__0___boxed(lean_object* v_sz_2797_, lean_object* v_i_2798_, lean_object* v_bs_2799_){
_start:
{
size_t v_sz_boxed_2800_; size_t v_i_boxed_2801_; lean_object* v_res_2802_; 
v_sz_boxed_2800_ = lean_unbox_usize(v_sz_2797_);
lean_dec(v_sz_2797_);
v_i_boxed_2801_ = lean_unbox_usize(v_i_2798_);
lean_dec(v_i_2798_);
v_res_2802_ = lp_competition___private_Init_Data_Array_Basic_0__Array_mapMUnsafe_map___at___00Submission_cacheRats_spec__0(v_sz_boxed_2800_, v_i_boxed_2801_, v_bs_2799_);
return v_res_2802_;
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_cacheRats(lean_object* v_a_2803_){
_start:
{
size_t v_sz_2804_; size_t v___x_2805_; lean_object* v___x_2806_; 
v_sz_2804_ = lean_array_size(v_a_2803_);
v___x_2805_ = ((size_t)0ULL);
v___x_2806_ = lp_competition___private_Init_Data_Array_Basic_0__Array_mapMUnsafe_map___at___00Submission_cacheRats_spec__0(v_sz_2804_, v___x_2805_, v_a_2803_);
return v___x_2806_;
}
}
LEAN_EXPORT lean_object* lp_competition_List_foldl___at___00Submission_rowMeanCached_spec__0(lean_object* v_row_2807_, lean_object* v_n_2808_, lean_object* v_x_2809_, lean_object* v_x_2810_, lean_object* v_x_2811_){
_start:
{
if (lean_obj_tag(v_x_2811_) == 0)
{
return v_x_2810_;
}
else
{
lean_object* v_head_2812_; lean_object* v_tail_2813_; lean_object* v___x_2814_; lean_object* v___x_2815_; lean_object* v___x_2816_; lean_object* v___x_2817_; lean_object* v___x_2818_; 
v_head_2812_ = lean_ctor_get(v_x_2811_, 0);
v_tail_2813_ = lean_ctor_get(v_x_2811_, 1);
v___x_2814_ = l_instInhabitedRat;
v___x_2815_ = lean_nat_mul(v_row_2807_, v_n_2808_);
v___x_2816_ = lean_nat_add(v___x_2815_, v_head_2812_);
lean_dec(v___x_2815_);
v___x_2817_ = lean_array_get_borrowed(v___x_2814_, v_x_2809_, v___x_2816_);
lean_dec(v___x_2816_);
lean_inc(v___x_2817_);
v___x_2818_ = l_Rat_add(v_x_2810_, v___x_2817_);
v_x_2810_ = v___x_2818_;
v_x_2811_ = v_tail_2813_;
goto _start;
}
}
}
LEAN_EXPORT lean_object* lp_competition_List_foldl___at___00Submission_rowMeanCached_spec__0___boxed(lean_object* v_row_2820_, lean_object* v_n_2821_, lean_object* v_x_2822_, lean_object* v_x_2823_, lean_object* v_x_2824_){
_start:
{
lean_object* v_res_2825_; 
v_res_2825_ = lp_competition_List_foldl___at___00Submission_rowMeanCached_spec__0(v_row_2820_, v_n_2821_, v_x_2822_, v_x_2823_, v_x_2824_);
lean_dec(v_x_2824_);
lean_dec_ref(v_x_2822_);
lean_dec(v_n_2821_);
lean_dec(v_row_2820_);
return v_res_2825_;
}
}
static lean_object* _init_lp_competition_Submission_rowMeanCached___closed__0(void){
_start:
{
lean_object* v___x_2826_; lean_object* v___x_2827_; 
v___x_2826_ = lean_unsigned_to_nat(0u);
v___x_2827_ = lp_mathlib_Nat_cast___at___00CompareReals_instCommRingQ_spec__0(v___x_2826_);
return v___x_2827_;
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_rowMeanCached(lean_object* v_n_2828_, lean_object* v_x_2829_, lean_object* v_row_2830_){
_start:
{
lean_object* v___x_2831_; lean_object* v___x_2832_; lean_object* v___x_2833_; lean_object* v___x_2834_; lean_object* v___x_2835_; 
v___x_2831_ = lean_obj_once(&lp_competition_Submission_rowMeanCached___closed__0, &lp_competition_Submission_rowMeanCached___closed__0_once, _init_lp_competition_Submission_rowMeanCached___closed__0);
lean_inc(v_n_2828_);
v___x_2832_ = l_List_range(v_n_2828_);
v___x_2833_ = lp_competition_List_foldl___at___00Submission_rowMeanCached_spec__0(v_row_2830_, v_n_2828_, v_x_2829_, v___x_2831_, v___x_2832_);
lean_dec(v___x_2832_);
v___x_2834_ = lp_mathlib_Nat_cast___at___00CompareReals_instCommRingQ_spec__0(v_n_2828_);
v___x_2835_ = l_Rat_div(v___x_2833_, v___x_2834_);
lean_dec_ref(v___x_2833_);
return v___x_2835_;
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_rowMeanCached___boxed(lean_object* v_n_2836_, lean_object* v_x_2837_, lean_object* v_row_2838_){
_start:
{
lean_object* v_res_2839_; 
v_res_2839_ = lp_competition_Submission_rowMeanCached(v_n_2836_, v_x_2837_, v_row_2838_);
lean_dec(v_row_2838_);
lean_dec_ref(v_x_2837_);
return v_res_2839_;
}
}
LEAN_EXPORT lean_object* lp_competition_List_foldl___at___00Submission_rowVarianceCached_spec__0(lean_object* v_row_2840_, lean_object* v_n_2841_, lean_object* v_x_2842_, lean_object* v_mean_2843_, lean_object* v_x_2844_, lean_object* v_x_2845_){
_start:
{
if (lean_obj_tag(v_x_2845_) == 0)
{
lean_dec_ref(v_mean_2843_);
return v_x_2844_;
}
else
{
lean_object* v_head_2846_; lean_object* v_tail_2847_; lean_object* v___x_2848_; lean_object* v___x_2849_; lean_object* v___x_2850_; lean_object* v___x_2851_; lean_object* v___x_2852_; lean_object* v___x_2853_; lean_object* v___x_2854_; lean_object* v___x_2855_; 
v_head_2846_ = lean_ctor_get(v_x_2845_, 0);
v_tail_2847_ = lean_ctor_get(v_x_2845_, 1);
v___x_2848_ = l_instInhabitedRat;
v___x_2849_ = lean_nat_mul(v_row_2840_, v_n_2841_);
v___x_2850_ = lean_nat_add(v___x_2849_, v_head_2846_);
lean_dec(v___x_2849_);
v___x_2851_ = lean_array_get_borrowed(v___x_2848_, v_x_2842_, v___x_2850_);
lean_dec(v___x_2850_);
lean_inc_ref(v_mean_2843_);
lean_inc(v___x_2851_);
v___x_2852_ = l_Rat_sub(v___x_2851_, v_mean_2843_);
v___x_2853_ = lean_unsigned_to_nat(2u);
v___x_2854_ = l_Rat_pow(v___x_2852_, v___x_2853_);
v___x_2855_ = l_Rat_add(v_x_2844_, v___x_2854_);
v_x_2844_ = v___x_2855_;
v_x_2845_ = v_tail_2847_;
goto _start;
}
}
}
LEAN_EXPORT lean_object* lp_competition_List_foldl___at___00Submission_rowVarianceCached_spec__0___boxed(lean_object* v_row_2857_, lean_object* v_n_2858_, lean_object* v_x_2859_, lean_object* v_mean_2860_, lean_object* v_x_2861_, lean_object* v_x_2862_){
_start:
{
lean_object* v_res_2863_; 
v_res_2863_ = lp_competition_List_foldl___at___00Submission_rowVarianceCached_spec__0(v_row_2857_, v_n_2858_, v_x_2859_, v_mean_2860_, v_x_2861_, v_x_2862_);
lean_dec(v_x_2862_);
lean_dec_ref(v_x_2859_);
lean_dec(v_n_2858_);
lean_dec(v_row_2857_);
return v_res_2863_;
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_rowVarianceCached(lean_object* v_n_2864_, lean_object* v_x_2865_, lean_object* v_row_2866_, lean_object* v_mean_2867_){
_start:
{
lean_object* v___x_2868_; lean_object* v___x_2869_; lean_object* v___x_2870_; lean_object* v___x_2871_; lean_object* v___x_2872_; 
v___x_2868_ = lean_obj_once(&lp_competition_Submission_rowMeanCached___closed__0, &lp_competition_Submission_rowMeanCached___closed__0_once, _init_lp_competition_Submission_rowMeanCached___closed__0);
lean_inc(v_n_2864_);
v___x_2869_ = l_List_range(v_n_2864_);
v___x_2870_ = lp_competition_List_foldl___at___00Submission_rowVarianceCached_spec__0(v_row_2866_, v_n_2864_, v_x_2865_, v_mean_2867_, v___x_2868_, v___x_2869_);
lean_dec(v___x_2869_);
v___x_2871_ = lp_mathlib_Nat_cast___at___00CompareReals_instCommRingQ_spec__0(v_n_2864_);
v___x_2872_ = l_Rat_div(v___x_2870_, v___x_2871_);
lean_dec_ref(v___x_2870_);
return v___x_2872_;
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_rowVarianceCached___boxed(lean_object* v_n_2873_, lean_object* v_x_2874_, lean_object* v_row_2875_, lean_object* v_mean_2876_){
_start:
{
lean_object* v_res_2877_; 
v_res_2877_ = lp_competition_Submission_rowVarianceCached(v_n_2873_, v_x_2874_, v_row_2875_, v_mean_2876_);
lean_dec(v_row_2875_);
lean_dec_ref(v_x_2874_);
return v_res_2877_;
}
}
LEAN_EXPORT uint32_t lp_competition_Submission_rmsnormStableCached___lam__0(lean_object* v_n_2878_, lean_object* v_rx_2879_, uint32_t v_eps_2880_, lean_object* v_r_2881_){
_start:
{
lean_object* v___x_2882_; lean_object* v___x_2883_; lean_object* v___x_2884_; lean_object* v___x_2885_; uint32_t v___x_2886_; 
v___x_2882_ = lean_obj_once(&lp_competition_Submission_rowMeanCached___closed__0, &lp_competition_Submission_rowMeanCached___closed__0_once, _init_lp_competition_Submission_rowMeanCached___closed__0);
v___x_2883_ = lp_competition_Submission_rowVarianceCached(v_n_2878_, v_rx_2879_, v_r_2881_, v___x_2882_);
v___x_2884_ = lp_competition_ExactRuntime_rationalWord(v_eps_2880_);
v___x_2885_ = l_Rat_add(v___x_2883_, v___x_2884_);
v___x_2886_ = lp_competition_ExactRuntime_sqrtRational(v___x_2885_);
return v___x_2886_;
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_rmsnormStableCached___lam__0___boxed(lean_object* v_n_2887_, lean_object* v_rx_2888_, lean_object* v_eps_2889_, lean_object* v_r_2890_){
_start:
{
uint32_t v_eps_boxed_2891_; uint32_t v_res_2892_; lean_object* v_r_2893_; 
v_eps_boxed_2891_ = lean_unbox_uint32(v_eps_2889_);
lean_dec(v_eps_2889_);
v_res_2892_ = lp_competition_Submission_rmsnormStableCached___lam__0(v_n_2887_, v_rx_2888_, v_eps_boxed_2891_, v_r_2890_);
lean_dec(v_r_2890_);
lean_dec_ref(v_rx_2888_);
v_r_2893_ = lean_box_uint32(v_res_2892_);
return v_r_2893_;
}
}
LEAN_EXPORT uint32_t lp_competition_Submission_rmsnormStableCached___lam__1(lean_object* v___x_2894_, lean_object* v_rx_2895_, lean_object* v_n_2896_, lean_object* v_rg_2897_, lean_object* v_rd_2898_, lean_object* v_q_2899_){
_start:
{
lean_object* v___x_2900_; lean_object* v___x_2901_; lean_object* v___x_2902_; lean_object* v___x_2903_; lean_object* v___x_2904_; lean_object* v___x_2905_; lean_object* v___x_2906_; uint32_t v___x_2907_; 
v___x_2900_ = lean_array_get_borrowed(v___x_2894_, v_rx_2895_, v_q_2899_);
v___x_2901_ = lean_nat_mod(v_q_2899_, v_n_2896_);
v___x_2902_ = lean_array_get_borrowed(v___x_2894_, v_rg_2897_, v___x_2901_);
lean_dec(v___x_2901_);
lean_inc(v___x_2902_);
v___x_2903_ = l_Rat_mul(v___x_2900_, v___x_2902_);
v___x_2904_ = lean_nat_div(v_q_2899_, v_n_2896_);
v___x_2905_ = lean_array_get_borrowed(v___x_2894_, v_rd_2898_, v___x_2904_);
lean_dec(v___x_2904_);
lean_inc(v___x_2905_);
v___x_2906_ = l_Rat_div(v___x_2903_, v___x_2905_);
lean_dec_ref(v___x_2903_);
v___x_2907_ = lp_competition_ExactRuntime_roundRational(v___x_2906_);
return v___x_2907_;
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_rmsnormStableCached___lam__1___boxed(lean_object* v___x_2908_, lean_object* v_rx_2909_, lean_object* v_n_2910_, lean_object* v_rg_2911_, lean_object* v_rd_2912_, lean_object* v_q_2913_){
_start:
{
uint32_t v_res_2914_; lean_object* v_r_2915_; 
v_res_2914_ = lp_competition_Submission_rmsnormStableCached___lam__1(v___x_2908_, v_rx_2909_, v_n_2910_, v_rg_2911_, v_rd_2912_, v_q_2913_);
lean_dec(v_q_2913_);
lean_dec_ref(v_rd_2912_);
lean_dec_ref(v_rg_2911_);
lean_dec(v_n_2910_);
lean_dec_ref(v_rx_2909_);
lean_dec_ref(v___x_2908_);
v_r_2915_ = lean_box_uint32(v_res_2914_);
return v_r_2915_;
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_rmsnormStableCached(lean_object* v_rows_2916_, lean_object* v_n_2917_, uint32_t v_eps_2918_, lean_object* v_x_2919_, lean_object* v_g_2920_){
_start:
{
lean_object* v___x_2921_; lean_object* v_rx_2922_; lean_object* v___x_2923_; lean_object* v___f_2924_; lean_object* v_rg_2925_; lean_object* v_den_2926_; lean_object* v_rd_2927_; lean_object* v___f_2928_; lean_object* v___x_2929_; lean_object* v___x_2930_; 
v___x_2921_ = l_instInhabitedRat;
v_rx_2922_ = lp_competition_Submission_cacheRats(v_x_2919_);
v___x_2923_ = lean_box_uint32(v_eps_2918_);
lean_inc_ref(v_rx_2922_);
lean_inc_n(v_n_2917_, 2);
v___f_2924_ = lean_alloc_closure((void*)(lp_competition_Submission_rmsnormStableCached___lam__0___boxed), 4, 3);
lean_closure_set(v___f_2924_, 0, v_n_2917_);
lean_closure_set(v___f_2924_, 1, v_rx_2922_);
lean_closure_set(v___f_2924_, 2, v___x_2923_);
v_rg_2925_ = lp_competition_Submission_cacheRats(v_g_2920_);
lean_inc(v_rows_2916_);
v_den_2926_ = l_Array_ofFn___redArg(v_rows_2916_, v___f_2924_);
v_rd_2927_ = lp_competition_Submission_cacheRats(v_den_2926_);
v___f_2928_ = lean_alloc_closure((void*)(lp_competition_Submission_rmsnormStableCached___lam__1___boxed), 6, 5);
lean_closure_set(v___f_2928_, 0, v___x_2921_);
lean_closure_set(v___f_2928_, 1, v_rx_2922_);
lean_closure_set(v___f_2928_, 2, v_n_2917_);
lean_closure_set(v___f_2928_, 3, v_rg_2925_);
lean_closure_set(v___f_2928_, 4, v_rd_2927_);
v___x_2929_ = lean_nat_mul(v_rows_2916_, v_n_2917_);
lean_dec(v_n_2917_);
lean_dec(v_rows_2916_);
v___x_2930_ = l_Array_ofFn___redArg(v___x_2929_, v___f_2928_);
return v___x_2930_;
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_rmsnormStableCached___boxed(lean_object* v_rows_2931_, lean_object* v_n_2932_, lean_object* v_eps_2933_, lean_object* v_x_2934_, lean_object* v_g_2935_){
_start:
{
uint32_t v_eps_boxed_2936_; lean_object* v_res_2937_; 
v_eps_boxed_2936_ = lean_unbox_uint32(v_eps_2933_);
lean_dec(v_eps_2933_);
v_res_2937_ = lp_competition_Submission_rmsnormStableCached(v_rows_2931_, v_n_2932_, v_eps_boxed_2936_, v_x_2934_, v_g_2935_);
return v_res_2937_;
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_layernormStableCached___lam__0(lean_object* v_n_2938_, lean_object* v_rx_2939_, lean_object* v_r_2940_){
_start:
{
lean_object* v___x_2941_; 
v___x_2941_ = lp_competition_Submission_rowMeanCached(v_n_2938_, v_rx_2939_, v_r_2940_);
return v___x_2941_;
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_layernormStableCached___lam__0___boxed(lean_object* v_n_2942_, lean_object* v_rx_2943_, lean_object* v_r_2944_){
_start:
{
lean_object* v_res_2945_; 
v_res_2945_ = lp_competition_Submission_layernormStableCached___lam__0(v_n_2942_, v_rx_2943_, v_r_2944_);
lean_dec(v_r_2944_);
lean_dec_ref(v_rx_2943_);
return v_res_2945_;
}
}
LEAN_EXPORT uint32_t lp_competition_Submission_layernormStableCached___lam__1(lean_object* v___x_2946_, lean_object* v_means_2947_, lean_object* v_n_2948_, lean_object* v_rx_2949_, uint32_t v_eps_2950_, lean_object* v_r_2951_){
_start:
{
lean_object* v___x_2952_; lean_object* v___x_2953_; lean_object* v___x_2954_; lean_object* v___x_2955_; uint32_t v___x_2956_; 
v___x_2952_ = lean_array_get_borrowed(v___x_2946_, v_means_2947_, v_r_2951_);
lean_inc(v___x_2952_);
v___x_2953_ = lp_competition_Submission_rowVarianceCached(v_n_2948_, v_rx_2949_, v_r_2951_, v___x_2952_);
v___x_2954_ = lp_competition_ExactRuntime_rationalWord(v_eps_2950_);
v___x_2955_ = l_Rat_add(v___x_2953_, v___x_2954_);
v___x_2956_ = lp_competition_ExactRuntime_sqrtRational(v___x_2955_);
return v___x_2956_;
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_layernormStableCached___lam__1___boxed(lean_object* v___x_2957_, lean_object* v_means_2958_, lean_object* v_n_2959_, lean_object* v_rx_2960_, lean_object* v_eps_2961_, lean_object* v_r_2962_){
_start:
{
uint32_t v_eps_boxed_2963_; uint32_t v_res_2964_; lean_object* v_r_2965_; 
v_eps_boxed_2963_ = lean_unbox_uint32(v_eps_2961_);
lean_dec(v_eps_2961_);
v_res_2964_ = lp_competition_Submission_layernormStableCached___lam__1(v___x_2957_, v_means_2958_, v_n_2959_, v_rx_2960_, v_eps_boxed_2963_, v_r_2962_);
lean_dec(v_r_2962_);
lean_dec_ref(v_rx_2960_);
lean_dec_ref(v_means_2958_);
lean_dec_ref(v___x_2957_);
v_r_2965_ = lean_box_uint32(v_res_2964_);
return v_r_2965_;
}
}
LEAN_EXPORT uint32_t lp_competition_Submission_layernormStableCached___lam__2(lean_object* v___x_2966_, lean_object* v_rx_2967_, lean_object* v_n_2968_, lean_object* v_means_2969_, lean_object* v_rg_2970_, lean_object* v_rd_2971_, lean_object* v_rb_2972_, lean_object* v_q_2973_){
_start:
{
lean_object* v___x_2974_; lean_object* v___x_2975_; lean_object* v___x_2976_; lean_object* v___x_2977_; lean_object* v___x_2978_; lean_object* v___x_2979_; lean_object* v___x_2980_; lean_object* v___x_2981_; lean_object* v___x_2982_; lean_object* v___x_2983_; lean_object* v___x_2984_; uint32_t v___x_2985_; 
v___x_2974_ = lean_array_get_borrowed(v___x_2966_, v_rx_2967_, v_q_2973_);
v___x_2975_ = lean_nat_div(v_q_2973_, v_n_2968_);
v___x_2976_ = lean_array_get_borrowed(v___x_2966_, v_means_2969_, v___x_2975_);
lean_inc(v___x_2976_);
lean_inc(v___x_2974_);
v___x_2977_ = l_Rat_sub(v___x_2974_, v___x_2976_);
v___x_2978_ = lean_nat_mod(v_q_2973_, v_n_2968_);
v___x_2979_ = lean_array_get_borrowed(v___x_2966_, v_rg_2970_, v___x_2978_);
lean_inc(v___x_2979_);
v___x_2980_ = l_Rat_mul(v___x_2977_, v___x_2979_);
lean_dec_ref(v___x_2977_);
v___x_2981_ = lean_array_get_borrowed(v___x_2966_, v_rd_2971_, v___x_2975_);
lean_dec(v___x_2975_);
lean_inc(v___x_2981_);
v___x_2982_ = l_Rat_div(v___x_2980_, v___x_2981_);
lean_dec_ref(v___x_2980_);
v___x_2983_ = lean_array_get_borrowed(v___x_2966_, v_rb_2972_, v___x_2978_);
lean_dec(v___x_2978_);
lean_inc(v___x_2983_);
v___x_2984_ = l_Rat_add(v___x_2982_, v___x_2983_);
v___x_2985_ = lp_competition_ExactRuntime_roundRational(v___x_2984_);
return v___x_2985_;
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_layernormStableCached___lam__2___boxed(lean_object* v___x_2986_, lean_object* v_rx_2987_, lean_object* v_n_2988_, lean_object* v_means_2989_, lean_object* v_rg_2990_, lean_object* v_rd_2991_, lean_object* v_rb_2992_, lean_object* v_q_2993_){
_start:
{
uint32_t v_res_2994_; lean_object* v_r_2995_; 
v_res_2994_ = lp_competition_Submission_layernormStableCached___lam__2(v___x_2986_, v_rx_2987_, v_n_2988_, v_means_2989_, v_rg_2990_, v_rd_2991_, v_rb_2992_, v_q_2993_);
lean_dec(v_q_2993_);
lean_dec_ref(v_rb_2992_);
lean_dec_ref(v_rd_2991_);
lean_dec_ref(v_rg_2990_);
lean_dec_ref(v_means_2989_);
lean_dec(v_n_2988_);
lean_dec_ref(v_rx_2987_);
lean_dec_ref(v___x_2986_);
v_r_2995_ = lean_box_uint32(v_res_2994_);
return v_r_2995_;
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_layernormStableCached(lean_object* v_rows_2996_, lean_object* v_n_2997_, uint32_t v_eps_2998_, lean_object* v_x_2999_, lean_object* v_g_3000_, lean_object* v_b_3001_){
_start:
{
lean_object* v___x_3002_; lean_object* v_rx_3003_; lean_object* v___f_3004_; lean_object* v_rg_3005_; lean_object* v_rb_3006_; lean_object* v_means_3007_; lean_object* v___x_3008_; lean_object* v___f_3009_; lean_object* v_den_3010_; lean_object* v_rd_3011_; lean_object* v___f_3012_; lean_object* v___x_3013_; lean_object* v___x_3014_; 
v___x_3002_ = l_instInhabitedRat;
v_rx_3003_ = lp_competition_Submission_cacheRats(v_x_2999_);
lean_inc_ref_n(v_rx_3003_, 2);
lean_inc_n(v_n_2997_, 3);
v___f_3004_ = lean_alloc_closure((void*)(lp_competition_Submission_layernormStableCached___lam__0___boxed), 3, 2);
lean_closure_set(v___f_3004_, 0, v_n_2997_);
lean_closure_set(v___f_3004_, 1, v_rx_3003_);
v_rg_3005_ = lp_competition_Submission_cacheRats(v_g_3000_);
v_rb_3006_ = lp_competition_Submission_cacheRats(v_b_3001_);
lean_inc_n(v_rows_2996_, 2);
v_means_3007_ = l_Array_ofFn___redArg(v_rows_2996_, v___f_3004_);
v___x_3008_ = lean_box_uint32(v_eps_2998_);
lean_inc_ref(v_means_3007_);
v___f_3009_ = lean_alloc_closure((void*)(lp_competition_Submission_layernormStableCached___lam__1___boxed), 6, 5);
lean_closure_set(v___f_3009_, 0, v___x_3002_);
lean_closure_set(v___f_3009_, 1, v_means_3007_);
lean_closure_set(v___f_3009_, 2, v_n_2997_);
lean_closure_set(v___f_3009_, 3, v_rx_3003_);
lean_closure_set(v___f_3009_, 4, v___x_3008_);
v_den_3010_ = l_Array_ofFn___redArg(v_rows_2996_, v___f_3009_);
v_rd_3011_ = lp_competition_Submission_cacheRats(v_den_3010_);
v___f_3012_ = lean_alloc_closure((void*)(lp_competition_Submission_layernormStableCached___lam__2___boxed), 8, 7);
lean_closure_set(v___f_3012_, 0, v___x_3002_);
lean_closure_set(v___f_3012_, 1, v_rx_3003_);
lean_closure_set(v___f_3012_, 2, v_n_2997_);
lean_closure_set(v___f_3012_, 3, v_means_3007_);
lean_closure_set(v___f_3012_, 4, v_rg_3005_);
lean_closure_set(v___f_3012_, 5, v_rd_3011_);
lean_closure_set(v___f_3012_, 6, v_rb_3006_);
v___x_3013_ = lean_nat_mul(v_rows_2996_, v_n_2997_);
lean_dec(v_n_2997_);
lean_dec(v_rows_2996_);
v___x_3014_ = l_Array_ofFn___redArg(v___x_3013_, v___f_3012_);
return v___x_3014_;
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_layernormStableCached___boxed(lean_object* v_rows_3015_, lean_object* v_n_3016_, lean_object* v_eps_3017_, lean_object* v_x_3018_, lean_object* v_g_3019_, lean_object* v_b_3020_){
_start:
{
uint32_t v_eps_boxed_3021_; lean_object* v_res_3022_; 
v_eps_boxed_3021_ = lean_unbox_uint32(v_eps_3017_);
lean_dec(v_eps_3017_);
v_res_3022_ = lp_competition_Submission_layernormStableCached(v_rows_3015_, v_n_3016_, v_eps_boxed_3021_, v_x_3018_, v_g_3019_, v_b_3020_);
return v_res_3022_;
}
}
LEAN_EXPORT uint32_t lp_competition_ExactRuntime_rmsnormLegacyWith___at___00Submission_rmsnormCached_spec__1___lam__2(uint32_t v___x_3023_, lean_object* v_x_3024_, lean_object* v_n_3025_, lean_object* v_scale_3026_, lean_object* v_g_3027_, lean_object* v_q_3028_){
_start:
{
lean_object* v___x_3029_; lean_object* v___x_3030_; uint32_t v___x_3031_; lean_object* v___x_3032_; lean_object* v___x_3033_; lean_object* v___x_3034_; lean_object* v___x_3035_; lean_object* v___x_3036_; lean_object* v___x_3037_; uint32_t v___x_3038_; lean_object* v___x_3039_; lean_object* v___x_3040_; lean_object* v___x_3041_; lean_object* v___x_3042_; lean_object* v___x_3043_; lean_object* v___x_3044_; uint32_t v___x_3045_; lean_object* v___x_3046_; lean_object* v___x_3047_; lean_object* v___x_3048_; uint32_t v___x_3049_; 
v___x_3029_ = lean_box_uint32(v___x_3023_);
v___x_3030_ = lean_array_get(v___x_3029_, v_x_3024_, v_q_3028_);
lean_dec(v___x_3029_);
v___x_3031_ = lean_unbox_uint32(v___x_3030_);
lean_dec(v___x_3030_);
v___x_3032_ = lean_uint32_to_nat(v___x_3031_);
v___x_3033_ = lean_unsigned_to_nat(32u);
v___x_3034_ = l_BitVec_ofNat(v___x_3033_, v___x_3032_);
lean_dec(v___x_3032_);
v___x_3035_ = lean_nat_div(v_q_3028_, v_n_3025_);
v___x_3036_ = lean_box_uint32(v___x_3023_);
v___x_3037_ = lean_array_get(v___x_3036_, v_scale_3026_, v___x_3035_);
lean_dec(v___x_3035_);
lean_dec(v___x_3036_);
v___x_3038_ = lean_unbox_uint32(v___x_3037_);
lean_dec(v___x_3037_);
v___x_3039_ = lean_uint32_to_nat(v___x_3038_);
v___x_3040_ = l_BitVec_ofNat(v___x_3033_, v___x_3039_);
lean_dec(v___x_3039_);
v___x_3041_ = lp_floatlib_FloatLib_Floats_Formats_BinaryInterchange_Model_MulBackend_word___at___00FloatLib_Floats_Formats_BinaryInterchange_Configured_Plan_softwareMul32Certified_spec__1(v___x_3034_, v___x_3040_);
v___x_3042_ = lean_nat_mod(v_q_3028_, v_n_3025_);
v___x_3043_ = lean_box_uint32(v___x_3023_);
v___x_3044_ = lean_array_get(v___x_3043_, v_g_3027_, v___x_3042_);
lean_dec(v___x_3042_);
lean_dec(v___x_3043_);
v___x_3045_ = lean_unbox_uint32(v___x_3044_);
lean_dec(v___x_3044_);
v___x_3046_ = lean_uint32_to_nat(v___x_3045_);
v___x_3047_ = l_BitVec_ofNat(v___x_3033_, v___x_3046_);
lean_dec(v___x_3046_);
v___x_3048_ = lp_floatlib_FloatLib_Floats_Formats_BinaryInterchange_Model_MulBackend_word___at___00FloatLib_Floats_Formats_BinaryInterchange_Configured_Plan_softwareMul32Certified_spec__1(v___x_3041_, v___x_3047_);
v___x_3049_ = lean_uint32_of_nat(v___x_3048_);
lean_dec(v___x_3048_);
return v___x_3049_;
}
}
LEAN_EXPORT lean_object* lp_competition_ExactRuntime_rmsnormLegacyWith___at___00Submission_rmsnormCached_spec__1___lam__2___boxed(lean_object* v___x_3050_, lean_object* v_x_3051_, lean_object* v_n_3052_, lean_object* v_scale_3053_, lean_object* v_g_3054_, lean_object* v_q_3055_){
_start:
{
uint32_t v___x_1379__boxed_3056_; uint32_t v_res_3057_; lean_object* v_r_3058_; 
v___x_1379__boxed_3056_ = lean_unbox_uint32(v___x_3050_);
lean_dec(v___x_3050_);
v_res_3057_ = lp_competition_ExactRuntime_rmsnormLegacyWith___at___00Submission_rmsnormCached_spec__1___lam__2(v___x_1379__boxed_3056_, v_x_3051_, v_n_3052_, v_scale_3053_, v_g_3054_, v_q_3055_);
lean_dec(v_q_3055_);
lean_dec_ref(v_g_3054_);
lean_dec_ref(v_scale_3053_);
lean_dec(v_n_3052_);
lean_dec_ref(v_x_3051_);
v_r_3058_ = lean_box_uint32(v_res_3057_);
return v_r_3058_;
}
}
LEAN_EXPORT uint32_t lp_competition_ExactRuntime_rmsnormLegacyWith___at___00Submission_rmsnormCached_spec__1___lam__1(lean_object* v___f_3059_, lean_object* v_i_3060_){
_start:
{
lean_object* v___x_3061_; uint32_t v___x_3062_; 
v___x_3061_ = lean_apply_1(v___f_3059_, v_i_3060_);
v___x_3062_ = lean_unbox_uint32(v___x_3061_);
lean_dec(v___x_3061_);
return v___x_3062_;
}
}
LEAN_EXPORT lean_object* lp_competition_ExactRuntime_rmsnormLegacyWith___at___00Submission_rmsnormCached_spec__1___lam__1___boxed(lean_object* v___f_3063_, lean_object* v_i_3064_){
_start:
{
uint32_t v_res_3065_; lean_object* v_r_3066_; 
v_res_3065_ = lp_competition_ExactRuntime_rmsnormLegacyWith___at___00Submission_rmsnormCached_spec__1___lam__1(v___f_3063_, v_i_3064_);
v_r_3066_ = lean_box_uint32(v_res_3065_);
return v_r_3066_;
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_dotLoop___at___00Submission_dotLoop___at___00Submission_rmsnormCached_spec__0___at___00ExactRuntime_rmsnormLegacyWith___at___00Submission_rmsnormCached_spec__1_spec__1_spec__2(lean_object* v_r_3067_, lean_object* v_n_3068_, lean_object* v_x_3069_, lean_object* v_pos_3070_, lean_object* v_neg_3071_, uint8_t v_sp_3072_, uint8_t v_nz_3073_, lean_object* v_index_3074_, lean_object* v_x_3075_){
_start:
{
lean_object* v_zero_3076_; uint8_t v_isZero_3077_; 
v_zero_3076_ = lean_unsigned_to_nat(0u);
v_isZero_3077_ = lean_nat_dec_eq(v_x_3075_, v_zero_3076_);
if (v_isZero_3077_ == 1)
{
lean_object* v___x_3078_; 
lean_dec(v_x_3075_);
lean_dec(v_index_3074_);
v___x_3078_ = lean_alloc_ctor(0, 2, 2);
lean_ctor_set(v___x_3078_, 0, v_pos_3070_);
lean_ctor_set(v___x_3078_, 1, v_neg_3071_);
lean_ctor_set_uint8(v___x_3078_, sizeof(void*)*2, v_sp_3072_);
lean_ctor_set_uint8(v___x_3078_, sizeof(void*)*2 + 1, v_nz_3073_);
return v___x_3078_;
}
else
{
uint32_t v___x_3079_; lean_object* v_one_3080_; lean_object* v_n_3081_; lean_object* v_pos_3083_; lean_object* v_neg_3084_; uint8_t v_special_3085_; uint8_t v_negZero_3086_; uint8_t v___y_3092_; lean_object* v___y_3093_; lean_object* v___y_3094_; lean_object* v___y_3095_; lean_object* v___y_3096_; lean_object* v___y_3106_; lean_object* v___y_3107_; lean_object* v___y_3108_; lean_object* v___y_3109_; lean_object* v___y_3119_; lean_object* v___y_3120_; uint8_t v___y_3121_; lean_object* v___y_3168_; lean_object* v___y_3169_; lean_object* v___x_3171_; lean_object* v___x_3172_; lean_object* v___x_3173_; lean_object* v___x_3174_; uint32_t v___x_3175_; uint32_t v___x_3176_; uint32_t v___x_3177_; uint32_t v___x_3178_; uint32_t v___x_3179_; uint8_t v___x_3180_; lean_object* v___y_3182_; lean_object* v___y_3183_; uint8_t v___y_3184_; uint8_t v___y_3185_; lean_object* v___y_3187_; lean_object* v___y_3188_; uint8_t v___y_3189_; lean_object* v___y_3196_; lean_object* v___y_3197_; lean_object* v___y_3198_; lean_object* v___y_3206_; lean_object* v___y_3207_; lean_object* v___y_3212_; lean_object* v___y_3213_; lean_object* v___y_3219_; 
v___x_3079_ = 0;
v_one_3080_ = lean_unsigned_to_nat(1u);
v_n_3081_ = lean_nat_sub(v_x_3075_, v_one_3080_);
lean_dec(v_x_3075_);
v___x_3171_ = lean_nat_mul(v_r_3067_, v_n_3068_);
v___x_3172_ = lean_nat_add(v___x_3171_, v_index_3074_);
lean_dec(v___x_3171_);
v___x_3173_ = lp_competition_Submission_dotX___lam__0___boxed__const__1;
v___x_3174_ = lean_array_get_borrowed(v___x_3173_, v_x_3069_, v___x_3172_);
lean_dec(v___x_3172_);
v___x_3175_ = 23;
v___x_3176_ = lean_unbox_uint32(v___x_3174_);
v___x_3177_ = lean_uint32_shift_right(v___x_3176_, v___x_3175_);
v___x_3178_ = 255;
v___x_3179_ = lean_uint32_land(v___x_3177_, v___x_3178_);
v___x_3180_ = lean_uint32_dec_eq(v___x_3179_, v___x_3178_);
if (v___x_3180_ == 0)
{
if (v___x_3180_ == 0)
{
uint8_t v___x_3231_; 
v___x_3231_ = lean_uint32_dec_eq(v___x_3179_, v___x_3079_);
if (v___x_3231_ == 0)
{
lean_object* v___x_3232_; uint32_t v___x_3233_; uint32_t v___x_3234_; uint32_t v___x_3235_; lean_object* v___x_3236_; lean_object* v___x_3237_; 
v___x_3232_ = lean_unsigned_to_nat(8388608u);
v___x_3233_ = 8388607;
v___x_3234_ = lean_unbox_uint32(v___x_3174_);
v___x_3235_ = lean_uint32_land(v___x_3234_, v___x_3233_);
v___x_3236_ = lean_uint32_to_nat(v___x_3235_);
v___x_3237_ = lean_nat_add(v___x_3232_, v___x_3236_);
lean_dec(v___x_3236_);
v___y_3219_ = v___x_3237_;
goto v___jp_3218_;
}
else
{
uint32_t v___x_3238_; uint32_t v___x_3239_; uint32_t v___x_3240_; lean_object* v___x_3241_; 
v___x_3238_ = 8388607;
v___x_3239_ = lean_unbox_uint32(v___x_3174_);
v___x_3240_ = lean_uint32_land(v___x_3239_, v___x_3238_);
v___x_3241_ = lean_uint32_to_nat(v___x_3240_);
v___y_3219_ = v___x_3241_;
goto v___jp_3218_;
}
}
else
{
goto v___jp_3089_;
}
}
else
{
goto v___jp_3089_;
}
v___jp_3082_:
{
lean_object* v___x_3087_; 
v___x_3087_ = lean_nat_add(v_index_3074_, v_one_3080_);
lean_dec(v_index_3074_);
v_pos_3070_ = v_pos_3083_;
v_neg_3071_ = v_neg_3084_;
v_sp_3072_ = v_special_3085_;
v_nz_3073_ = v_negZero_3086_;
v_index_3074_ = v___x_3087_;
v_x_3075_ = v_n_3081_;
goto _start;
}
v___jp_3089_:
{
uint8_t v___x_3090_; 
v___x_3090_ = 1;
v_pos_3083_ = v_pos_3070_;
v_neg_3084_ = v_neg_3071_;
v_special_3085_ = v___x_3090_;
v_negZero_3086_ = v_nz_3073_;
goto v___jp_3082_;
}
v___jp_3091_:
{
lean_object* v___x_3097_; lean_object* v___x_3098_; uint8_t v___x_3099_; 
v___x_3097_ = lean_nat_add(v___y_3095_, v___y_3094_);
lean_dec(v___y_3095_);
v___x_3098_ = lean_array_get_size(v___y_3096_);
v___x_3099_ = lean_nat_dec_lt(v___x_3097_, v___x_3098_);
if (v___x_3099_ == 0)
{
lean_dec(v___x_3097_);
lean_dec(v___y_3093_);
v_pos_3083_ = v___y_3096_;
v_neg_3084_ = v_neg_3071_;
v_special_3085_ = v_sp_3072_;
v_negZero_3086_ = v___y_3092_;
goto v___jp_3082_;
}
else
{
lean_object* v_v_3100_; lean_object* v___x_3101_; lean_object* v_xs_x27_3102_; lean_object* v___x_3103_; lean_object* v___x_3104_; 
v_v_3100_ = lean_array_fget(v___y_3096_, v___x_3097_);
v___x_3101_ = lean_box(0);
v_xs_x27_3102_ = lean_array_fset(v___y_3096_, v___x_3097_, v___x_3101_);
v___x_3103_ = lean_nat_add(v_v_3100_, v___y_3093_);
lean_dec(v___y_3093_);
lean_dec(v_v_3100_);
v___x_3104_ = lean_array_fset(v_xs_x27_3102_, v___x_3097_, v___x_3103_);
lean_dec(v___x_3097_);
v_pos_3083_ = v___x_3104_;
v_neg_3084_ = v_neg_3071_;
v_special_3085_ = v_sp_3072_;
v_negZero_3086_ = v___y_3092_;
goto v___jp_3082_;
}
}
v___jp_3105_:
{
lean_object* v___x_3110_; lean_object* v___x_3111_; uint8_t v___x_3112_; 
v___x_3110_ = lean_nat_add(v___y_3107_, v___y_3106_);
lean_dec(v___y_3107_);
v___x_3111_ = lean_array_get_size(v___y_3109_);
v___x_3112_ = lean_nat_dec_lt(v___x_3110_, v___x_3111_);
if (v___x_3112_ == 0)
{
lean_dec(v___x_3110_);
lean_dec(v___y_3108_);
v_pos_3083_ = v_pos_3070_;
v_neg_3084_ = v___y_3109_;
v_special_3085_ = v_sp_3072_;
v_negZero_3086_ = v_isZero_3077_;
goto v___jp_3082_;
}
else
{
lean_object* v_v_3113_; lean_object* v___x_3114_; lean_object* v_xs_x27_3115_; lean_object* v___x_3116_; lean_object* v___x_3117_; 
v_v_3113_ = lean_array_fget(v___y_3109_, v___x_3110_);
v___x_3114_ = lean_box(0);
v_xs_x27_3115_ = lean_array_fset(v___y_3109_, v___x_3110_, v___x_3114_);
v___x_3116_ = lean_nat_add(v_v_3113_, v___y_3108_);
lean_dec(v___y_3108_);
lean_dec(v_v_3113_);
v___x_3117_ = lean_array_fset(v_xs_x27_3115_, v___x_3110_, v___x_3116_);
lean_dec(v___x_3110_);
v_pos_3083_ = v_pos_3070_;
v_neg_3084_ = v___x_3117_;
v_special_3085_ = v_sp_3072_;
v_negZero_3086_ = v_isZero_3077_;
goto v___jp_3082_;
}
}
v___jp_3118_:
{
uint8_t v___x_3122_; 
v___x_3122_ = lean_nat_dec_eq(v___y_3120_, v_zero_3076_);
if (v___x_3122_ == 0)
{
if (v___y_3121_ == 0)
{
uint64_t v___x_3123_; lean_object* v___x_3124_; lean_object* v___x_3125_; lean_object* v_l_3126_; lean_object* v___x_3127_; uint64_t v_r_3128_; uint64_t v___x_3129_; uint64_t v___x_3130_; uint64_t v___x_3131_; uint64_t v___x_3132_; uint64_t v___x_3133_; uint64_t v___x_3134_; lean_object* v_hi_3135_; lean_object* v___x_3136_; uint8_t v___x_3137_; 
v___x_3123_ = lean_uint64_of_nat(v___y_3120_);
lean_dec(v___y_3120_);
v___x_3124_ = lean_unsigned_to_nat(32u);
v___x_3125_ = lean_unsigned_to_nat(5u);
v_l_3126_ = lean_nat_shiftr(v___y_3119_, v___x_3125_);
v___x_3127_ = lean_nat_mod(v___y_3119_, v___x_3124_);
lean_dec(v___y_3119_);
v_r_3128_ = lean_uint64_of_nat(v___x_3127_);
lean_dec(v___x_3127_);
v___x_3129_ = 1ULL;
v___x_3130_ = 32ULL;
v___x_3131_ = lean_uint64_sub(v___x_3130_, v_r_3128_);
v___x_3132_ = lean_uint64_shift_left(v___x_3129_, v___x_3131_);
v___x_3133_ = lean_uint64_mod(v___x_3123_, v___x_3132_);
v___x_3134_ = lean_uint64_shift_right(v___x_3123_, v___x_3131_);
v_hi_3135_ = lean_uint64_to_nat(v___x_3134_);
v___x_3136_ = lean_array_get_size(v_pos_3070_);
v___x_3137_ = lean_nat_dec_lt(v_l_3126_, v___x_3136_);
if (v___x_3137_ == 0)
{
v___y_3092_ = v___y_3121_;
v___y_3093_ = v_hi_3135_;
v___y_3094_ = v_one_3080_;
v___y_3095_ = v_l_3126_;
v___y_3096_ = v_pos_3070_;
goto v___jp_3091_;
}
else
{
uint64_t v___x_3138_; lean_object* v_lo_3139_; lean_object* v_v_3140_; lean_object* v___x_3141_; lean_object* v_xs_x27_3142_; lean_object* v___x_3143_; lean_object* v___x_3144_; 
v___x_3138_ = lean_uint64_shift_left(v___x_3133_, v_r_3128_);
v_lo_3139_ = lean_uint64_to_nat(v___x_3138_);
v_v_3140_ = lean_array_fget(v_pos_3070_, v_l_3126_);
v___x_3141_ = lean_box(0);
v_xs_x27_3142_ = lean_array_fset(v_pos_3070_, v_l_3126_, v___x_3141_);
v___x_3143_ = lean_nat_add(v_v_3140_, v_lo_3139_);
lean_dec(v_lo_3139_);
lean_dec(v_v_3140_);
v___x_3144_ = lean_array_fset(v_xs_x27_3142_, v_l_3126_, v___x_3143_);
v___y_3092_ = v___y_3121_;
v___y_3093_ = v_hi_3135_;
v___y_3094_ = v_one_3080_;
v___y_3095_ = v_l_3126_;
v___y_3096_ = v___x_3144_;
goto v___jp_3091_;
}
}
else
{
uint64_t v___x_3145_; lean_object* v___x_3146_; lean_object* v___x_3147_; lean_object* v_l_3148_; lean_object* v___x_3149_; uint64_t v_r_3150_; uint64_t v___x_3151_; uint64_t v___x_3152_; uint64_t v___x_3153_; uint64_t v___x_3154_; uint64_t v___x_3155_; uint64_t v___x_3156_; lean_object* v_hi_3157_; lean_object* v___x_3158_; uint8_t v___x_3159_; 
v___x_3145_ = lean_uint64_of_nat(v___y_3120_);
lean_dec(v___y_3120_);
v___x_3146_ = lean_unsigned_to_nat(32u);
v___x_3147_ = lean_unsigned_to_nat(5u);
v_l_3148_ = lean_nat_shiftr(v___y_3119_, v___x_3147_);
v___x_3149_ = lean_nat_mod(v___y_3119_, v___x_3146_);
lean_dec(v___y_3119_);
v_r_3150_ = lean_uint64_of_nat(v___x_3149_);
lean_dec(v___x_3149_);
v___x_3151_ = 1ULL;
v___x_3152_ = 32ULL;
v___x_3153_ = lean_uint64_sub(v___x_3152_, v_r_3150_);
v___x_3154_ = lean_uint64_shift_left(v___x_3151_, v___x_3153_);
v___x_3155_ = lean_uint64_mod(v___x_3145_, v___x_3154_);
v___x_3156_ = lean_uint64_shift_right(v___x_3145_, v___x_3153_);
v_hi_3157_ = lean_uint64_to_nat(v___x_3156_);
v___x_3158_ = lean_array_get_size(v_neg_3071_);
v___x_3159_ = lean_nat_dec_lt(v_l_3148_, v___x_3158_);
if (v___x_3159_ == 0)
{
v___y_3106_ = v_one_3080_;
v___y_3107_ = v_l_3148_;
v___y_3108_ = v_hi_3157_;
v___y_3109_ = v_neg_3071_;
goto v___jp_3105_;
}
else
{
uint64_t v___x_3160_; lean_object* v_lo_3161_; lean_object* v_v_3162_; lean_object* v___x_3163_; lean_object* v_xs_x27_3164_; lean_object* v___x_3165_; lean_object* v___x_3166_; 
v___x_3160_ = lean_uint64_shift_left(v___x_3155_, v_r_3150_);
v_lo_3161_ = lean_uint64_to_nat(v___x_3160_);
v_v_3162_ = lean_array_fget(v_neg_3071_, v_l_3148_);
v___x_3163_ = lean_box(0);
v_xs_x27_3164_ = lean_array_fset(v_neg_3071_, v_l_3148_, v___x_3163_);
v___x_3165_ = lean_nat_add(v_v_3162_, v_lo_3161_);
lean_dec(v_lo_3161_);
lean_dec(v_v_3162_);
v___x_3166_ = lean_array_fset(v_xs_x27_3164_, v_l_3148_, v___x_3165_);
v___y_3106_ = v_one_3080_;
v___y_3107_ = v_l_3148_;
v___y_3108_ = v_hi_3157_;
v___y_3109_ = v___x_3166_;
goto v___jp_3105_;
}
}
}
else
{
lean_dec(v___y_3120_);
lean_dec(v___y_3119_);
if (v_nz_3073_ == 0)
{
v_pos_3083_ = v_pos_3070_;
v_neg_3084_ = v_neg_3071_;
v_special_3085_ = v_sp_3072_;
v_negZero_3086_ = v_nz_3073_;
goto v___jp_3082_;
}
else
{
v_pos_3083_ = v_pos_3070_;
v_neg_3084_ = v_neg_3071_;
v_special_3085_ = v_sp_3072_;
v_negZero_3086_ = v___y_3121_;
goto v___jp_3082_;
}
}
}
v___jp_3167_:
{
uint8_t v___x_3170_; 
v___x_3170_ = 1;
v___y_3119_ = v___y_3168_;
v___y_3120_ = v___y_3169_;
v___y_3121_ = v___x_3170_;
goto v___jp_3118_;
}
v___jp_3181_:
{
if (v___y_3184_ == 0)
{
if (v___y_3185_ == 0)
{
v___y_3119_ = v___y_3182_;
v___y_3120_ = v___y_3183_;
v___y_3121_ = v___x_3180_;
goto v___jp_3118_;
}
else
{
v___y_3168_ = v___y_3182_;
v___y_3169_ = v___y_3183_;
goto v___jp_3167_;
}
}
else
{
if (v___y_3185_ == 0)
{
v___y_3168_ = v___y_3182_;
v___y_3169_ = v___y_3183_;
goto v___jp_3167_;
}
else
{
v___y_3119_ = v___y_3182_;
v___y_3120_ = v___y_3183_;
v___y_3121_ = v___x_3180_;
goto v___jp_3118_;
}
}
}
v___jp_3186_:
{
uint32_t v___x_3190_; uint32_t v___x_3191_; uint32_t v___x_3192_; uint8_t v___x_3193_; 
v___x_3190_ = 2147483648;
v___x_3191_ = lean_unbox_uint32(v___x_3174_);
v___x_3192_ = lean_uint32_land(v___x_3191_, v___x_3190_);
v___x_3193_ = lean_uint32_dec_eq(v___x_3192_, v___x_3079_);
if (v___x_3193_ == 0)
{
uint8_t v___x_3194_; 
v___x_3194_ = 1;
v___y_3182_ = v___y_3187_;
v___y_3183_ = v___y_3188_;
v___y_3184_ = v___y_3189_;
v___y_3185_ = v___x_3194_;
goto v___jp_3181_;
}
else
{
v___y_3182_ = v___y_3187_;
v___y_3183_ = v___y_3188_;
v___y_3184_ = v___y_3189_;
v___y_3185_ = v___x_3180_;
goto v___jp_3181_;
}
}
v___jp_3195_:
{
lean_object* v___x_3199_; uint32_t v___x_3200_; uint32_t v___x_3201_; uint32_t v___x_3202_; uint8_t v___x_3203_; 
v___x_3199_ = lean_nat_add(v___y_3196_, v___y_3198_);
lean_dec(v___y_3198_);
lean_dec(v___y_3196_);
v___x_3200_ = 2147483648;
v___x_3201_ = lean_unbox_uint32(v___x_3174_);
v___x_3202_ = lean_uint32_land(v___x_3201_, v___x_3200_);
v___x_3203_ = lean_uint32_dec_eq(v___x_3202_, v___x_3079_);
if (v___x_3203_ == 0)
{
uint8_t v___x_3204_; 
v___x_3204_ = 1;
v___y_3187_ = v___x_3199_;
v___y_3188_ = v___y_3197_;
v___y_3189_ = v___x_3204_;
goto v___jp_3186_;
}
else
{
v___y_3187_ = v___x_3199_;
v___y_3188_ = v___y_3197_;
v___y_3189_ = v___x_3180_;
goto v___jp_3186_;
}
}
v___jp_3205_:
{
uint8_t v___x_3208_; 
v___x_3208_ = lean_uint32_dec_eq(v___x_3179_, v___x_3079_);
if (v___x_3208_ == 0)
{
lean_object* v___x_3209_; lean_object* v___x_3210_; 
v___x_3209_ = lean_uint32_to_nat(v___x_3179_);
v___x_3210_ = lean_nat_sub(v___x_3209_, v_one_3080_);
lean_dec(v___x_3209_);
v___y_3196_ = v___y_3207_;
v___y_3197_ = v___y_3206_;
v___y_3198_ = v___x_3210_;
goto v___jp_3195_;
}
else
{
v___y_3196_ = v___y_3207_;
v___y_3197_ = v___y_3206_;
v___y_3198_ = v_zero_3076_;
goto v___jp_3195_;
}
}
v___jp_3211_:
{
lean_object* v___x_3214_; uint8_t v___x_3215_; 
v___x_3214_ = lean_nat_mul(v___y_3212_, v___y_3213_);
lean_dec(v___y_3213_);
lean_dec(v___y_3212_);
v___x_3215_ = lean_uint32_dec_eq(v___x_3179_, v___x_3079_);
if (v___x_3215_ == 0)
{
lean_object* v___x_3216_; lean_object* v___x_3217_; 
v___x_3216_ = lean_uint32_to_nat(v___x_3179_);
v___x_3217_ = lean_nat_sub(v___x_3216_, v_one_3080_);
lean_dec(v___x_3216_);
v___y_3206_ = v___x_3214_;
v___y_3207_ = v___x_3217_;
goto v___jp_3205_;
}
else
{
v___y_3206_ = v___x_3214_;
v___y_3207_ = v_zero_3076_;
goto v___jp_3205_;
}
}
v___jp_3218_:
{
uint8_t v___x_3220_; 
v___x_3220_ = lean_uint32_dec_eq(v___x_3179_, v___x_3079_);
if (v___x_3220_ == 0)
{
lean_object* v___x_3221_; uint32_t v___x_3222_; uint32_t v___x_3223_; uint32_t v___x_3224_; lean_object* v___x_3225_; lean_object* v___x_3226_; 
v___x_3221_ = lean_unsigned_to_nat(8388608u);
v___x_3222_ = 8388607;
v___x_3223_ = lean_unbox_uint32(v___x_3174_);
v___x_3224_ = lean_uint32_land(v___x_3223_, v___x_3222_);
v___x_3225_ = lean_uint32_to_nat(v___x_3224_);
v___x_3226_ = lean_nat_add(v___x_3221_, v___x_3225_);
lean_dec(v___x_3225_);
v___y_3212_ = v___y_3219_;
v___y_3213_ = v___x_3226_;
goto v___jp_3211_;
}
else
{
uint32_t v___x_3227_; uint32_t v___x_3228_; uint32_t v___x_3229_; lean_object* v___x_3230_; 
v___x_3227_ = 8388607;
v___x_3228_ = lean_unbox_uint32(v___x_3174_);
v___x_3229_ = lean_uint32_land(v___x_3228_, v___x_3227_);
v___x_3230_ = lean_uint32_to_nat(v___x_3229_);
v___y_3212_ = v___y_3219_;
v___y_3213_ = v___x_3230_;
goto v___jp_3211_;
}
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_dotLoop___at___00Submission_dotLoop___at___00Submission_rmsnormCached_spec__0___at___00ExactRuntime_rmsnormLegacyWith___at___00Submission_rmsnormCached_spec__1_spec__1_spec__2___boxed(lean_object* v_r_3242_, lean_object* v_n_3243_, lean_object* v_x_3244_, lean_object* v_pos_3245_, lean_object* v_neg_3246_, lean_object* v_sp_3247_, lean_object* v_nz_3248_, lean_object* v_index_3249_, lean_object* v_x_3250_){
_start:
{
uint8_t v_sp_boxed_3251_; uint8_t v_nz_boxed_3252_; lean_object* v_res_3253_; 
v_sp_boxed_3251_ = lean_unbox(v_sp_3247_);
v_nz_boxed_3252_ = lean_unbox(v_nz_3248_);
v_res_3253_ = lp_competition_Submission_dotLoop___at___00Submission_dotLoop___at___00Submission_rmsnormCached_spec__0___at___00ExactRuntime_rmsnormLegacyWith___at___00Submission_rmsnormCached_spec__1_spec__1_spec__2(v_r_3242_, v_n_3243_, v_x_3244_, v_pos_3245_, v_neg_3246_, v_sp_boxed_3251_, v_nz_boxed_3252_, v_index_3249_, v_x_3250_);
lean_dec_ref(v_x_3244_);
lean_dec(v_n_3243_);
lean_dec(v_r_3242_);
return v_res_3253_;
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_dotLoop___at___00Submission_rmsnormCached_spec__0___at___00ExactRuntime_rmsnormLegacyWith___at___00Submission_rmsnormCached_spec__1_spec__1(lean_object* v_r_3254_, lean_object* v_n_3255_, lean_object* v_x_3256_, lean_object* v_pos_3257_, lean_object* v_neg_3258_, uint8_t v_sp_3259_, uint8_t v_nz_3260_, lean_object* v_index_3261_, lean_object* v_x_3262_){
_start:
{
lean_object* v_zero_3263_; uint8_t v_isZero_3264_; 
v_zero_3263_ = lean_unsigned_to_nat(0u);
v_isZero_3264_ = lean_nat_dec_eq(v_x_3262_, v_zero_3263_);
if (v_isZero_3264_ == 1)
{
lean_object* v___x_3265_; 
v___x_3265_ = lean_alloc_ctor(0, 2, 2);
lean_ctor_set(v___x_3265_, 0, v_pos_3257_);
lean_ctor_set(v___x_3265_, 1, v_neg_3258_);
lean_ctor_set_uint8(v___x_3265_, sizeof(void*)*2, v_sp_3259_);
lean_ctor_set_uint8(v___x_3265_, sizeof(void*)*2 + 1, v_nz_3260_);
return v___x_3265_;
}
else
{
uint32_t v___x_3266_; lean_object* v_one_3267_; lean_object* v_n_3268_; lean_object* v_pos_3270_; lean_object* v_neg_3271_; uint8_t v_special_3272_; uint8_t v_negZero_3273_; lean_object* v___y_3279_; uint8_t v___y_3280_; lean_object* v___y_3281_; lean_object* v___y_3282_; lean_object* v___y_3283_; lean_object* v___y_3293_; lean_object* v___y_3294_; lean_object* v___y_3295_; lean_object* v___y_3296_; lean_object* v___y_3306_; lean_object* v___y_3307_; uint8_t v___y_3308_; lean_object* v___y_3355_; lean_object* v___y_3356_; lean_object* v___x_3358_; lean_object* v___x_3359_; lean_object* v___x_3360_; lean_object* v___x_3361_; uint32_t v___x_3362_; uint32_t v___x_3363_; uint32_t v___x_3364_; uint32_t v___x_3365_; uint32_t v___x_3366_; uint8_t v___x_3367_; lean_object* v___y_3369_; uint8_t v___y_3370_; lean_object* v___y_3371_; uint8_t v___y_3372_; lean_object* v___y_3374_; lean_object* v___y_3375_; uint8_t v___y_3376_; lean_object* v___y_3383_; lean_object* v___y_3384_; lean_object* v___y_3385_; lean_object* v___y_3393_; lean_object* v___y_3394_; lean_object* v___y_3399_; lean_object* v___y_3400_; lean_object* v___y_3406_; 
v___x_3266_ = 0;
v_one_3267_ = lean_unsigned_to_nat(1u);
v_n_3268_ = lean_nat_sub(v_x_3262_, v_one_3267_);
v___x_3358_ = lean_nat_mul(v_r_3254_, v_n_3255_);
v___x_3359_ = lean_nat_add(v___x_3358_, v_index_3261_);
lean_dec(v___x_3358_);
v___x_3360_ = lp_competition_Submission_dotX___lam__0___boxed__const__1;
v___x_3361_ = lean_array_get_borrowed(v___x_3360_, v_x_3256_, v___x_3359_);
lean_dec(v___x_3359_);
v___x_3362_ = 23;
v___x_3363_ = lean_unbox_uint32(v___x_3361_);
v___x_3364_ = lean_uint32_shift_right(v___x_3363_, v___x_3362_);
v___x_3365_ = 255;
v___x_3366_ = lean_uint32_land(v___x_3364_, v___x_3365_);
v___x_3367_ = lean_uint32_dec_eq(v___x_3366_, v___x_3365_);
if (v___x_3367_ == 0)
{
if (v___x_3367_ == 0)
{
uint8_t v___x_3418_; 
v___x_3418_ = lean_uint32_dec_eq(v___x_3366_, v___x_3266_);
if (v___x_3418_ == 0)
{
lean_object* v___x_3419_; uint32_t v___x_3420_; uint32_t v___x_3421_; uint32_t v___x_3422_; lean_object* v___x_3423_; lean_object* v___x_3424_; 
v___x_3419_ = lean_unsigned_to_nat(8388608u);
v___x_3420_ = 8388607;
v___x_3421_ = lean_unbox_uint32(v___x_3361_);
v___x_3422_ = lean_uint32_land(v___x_3421_, v___x_3420_);
v___x_3423_ = lean_uint32_to_nat(v___x_3422_);
v___x_3424_ = lean_nat_add(v___x_3419_, v___x_3423_);
lean_dec(v___x_3423_);
v___y_3406_ = v___x_3424_;
goto v___jp_3405_;
}
else
{
uint32_t v___x_3425_; uint32_t v___x_3426_; uint32_t v___x_3427_; lean_object* v___x_3428_; 
v___x_3425_ = 8388607;
v___x_3426_ = lean_unbox_uint32(v___x_3361_);
v___x_3427_ = lean_uint32_land(v___x_3426_, v___x_3425_);
v___x_3428_ = lean_uint32_to_nat(v___x_3427_);
v___y_3406_ = v___x_3428_;
goto v___jp_3405_;
}
}
else
{
goto v___jp_3276_;
}
}
else
{
goto v___jp_3276_;
}
v___jp_3269_:
{
lean_object* v___x_3274_; lean_object* v___x_3275_; 
v___x_3274_ = lean_nat_add(v_index_3261_, v_one_3267_);
v___x_3275_ = lp_competition_Submission_dotLoop___at___00Submission_dotLoop___at___00Submission_rmsnormCached_spec__0___at___00ExactRuntime_rmsnormLegacyWith___at___00Submission_rmsnormCached_spec__1_spec__1_spec__2(v_r_3254_, v_n_3255_, v_x_3256_, v_pos_3270_, v_neg_3271_, v_special_3272_, v_negZero_3273_, v___x_3274_, v_n_3268_);
return v___x_3275_;
}
v___jp_3276_:
{
uint8_t v___x_3277_; 
v___x_3277_ = 1;
v_pos_3270_ = v_pos_3257_;
v_neg_3271_ = v_neg_3258_;
v_special_3272_ = v___x_3277_;
v_negZero_3273_ = v_nz_3260_;
goto v___jp_3269_;
}
v___jp_3278_:
{
lean_object* v___x_3284_; lean_object* v___x_3285_; uint8_t v___x_3286_; 
v___x_3284_ = lean_nat_add(v___y_3279_, v___y_3282_);
lean_dec(v___y_3279_);
v___x_3285_ = lean_array_get_size(v___y_3283_);
v___x_3286_ = lean_nat_dec_lt(v___x_3284_, v___x_3285_);
if (v___x_3286_ == 0)
{
lean_dec(v___x_3284_);
lean_dec(v___y_3281_);
v_pos_3270_ = v___y_3283_;
v_neg_3271_ = v_neg_3258_;
v_special_3272_ = v_sp_3259_;
v_negZero_3273_ = v___y_3280_;
goto v___jp_3269_;
}
else
{
lean_object* v_v_3287_; lean_object* v___x_3288_; lean_object* v_xs_x27_3289_; lean_object* v___x_3290_; lean_object* v___x_3291_; 
v_v_3287_ = lean_array_fget(v___y_3283_, v___x_3284_);
v___x_3288_ = lean_box(0);
v_xs_x27_3289_ = lean_array_fset(v___y_3283_, v___x_3284_, v___x_3288_);
v___x_3290_ = lean_nat_add(v_v_3287_, v___y_3281_);
lean_dec(v___y_3281_);
lean_dec(v_v_3287_);
v___x_3291_ = lean_array_fset(v_xs_x27_3289_, v___x_3284_, v___x_3290_);
lean_dec(v___x_3284_);
v_pos_3270_ = v___x_3291_;
v_neg_3271_ = v_neg_3258_;
v_special_3272_ = v_sp_3259_;
v_negZero_3273_ = v___y_3280_;
goto v___jp_3269_;
}
}
v___jp_3292_:
{
lean_object* v___x_3297_; lean_object* v___x_3298_; uint8_t v___x_3299_; 
v___x_3297_ = lean_nat_add(v___y_3293_, v___y_3294_);
lean_dec(v___y_3293_);
v___x_3298_ = lean_array_get_size(v___y_3296_);
v___x_3299_ = lean_nat_dec_lt(v___x_3297_, v___x_3298_);
if (v___x_3299_ == 0)
{
lean_dec(v___x_3297_);
lean_dec(v___y_3295_);
v_pos_3270_ = v_pos_3257_;
v_neg_3271_ = v___y_3296_;
v_special_3272_ = v_sp_3259_;
v_negZero_3273_ = v_isZero_3264_;
goto v___jp_3269_;
}
else
{
lean_object* v_v_3300_; lean_object* v___x_3301_; lean_object* v_xs_x27_3302_; lean_object* v___x_3303_; lean_object* v___x_3304_; 
v_v_3300_ = lean_array_fget(v___y_3296_, v___x_3297_);
v___x_3301_ = lean_box(0);
v_xs_x27_3302_ = lean_array_fset(v___y_3296_, v___x_3297_, v___x_3301_);
v___x_3303_ = lean_nat_add(v_v_3300_, v___y_3295_);
lean_dec(v___y_3295_);
lean_dec(v_v_3300_);
v___x_3304_ = lean_array_fset(v_xs_x27_3302_, v___x_3297_, v___x_3303_);
lean_dec(v___x_3297_);
v_pos_3270_ = v_pos_3257_;
v_neg_3271_ = v___x_3304_;
v_special_3272_ = v_sp_3259_;
v_negZero_3273_ = v_isZero_3264_;
goto v___jp_3269_;
}
}
v___jp_3305_:
{
uint8_t v___x_3309_; 
v___x_3309_ = lean_nat_dec_eq(v___y_3307_, v_zero_3263_);
if (v___x_3309_ == 0)
{
if (v___y_3308_ == 0)
{
uint64_t v___x_3310_; lean_object* v___x_3311_; lean_object* v___x_3312_; lean_object* v_l_3313_; lean_object* v___x_3314_; uint64_t v_r_3315_; uint64_t v___x_3316_; uint64_t v___x_3317_; uint64_t v___x_3318_; uint64_t v___x_3319_; uint64_t v___x_3320_; uint64_t v___x_3321_; lean_object* v_hi_3322_; lean_object* v___x_3323_; uint8_t v___x_3324_; 
v___x_3310_ = lean_uint64_of_nat(v___y_3307_);
lean_dec(v___y_3307_);
v___x_3311_ = lean_unsigned_to_nat(32u);
v___x_3312_ = lean_unsigned_to_nat(5u);
v_l_3313_ = lean_nat_shiftr(v___y_3306_, v___x_3312_);
v___x_3314_ = lean_nat_mod(v___y_3306_, v___x_3311_);
lean_dec(v___y_3306_);
v_r_3315_ = lean_uint64_of_nat(v___x_3314_);
lean_dec(v___x_3314_);
v___x_3316_ = 1ULL;
v___x_3317_ = 32ULL;
v___x_3318_ = lean_uint64_sub(v___x_3317_, v_r_3315_);
v___x_3319_ = lean_uint64_shift_left(v___x_3316_, v___x_3318_);
v___x_3320_ = lean_uint64_mod(v___x_3310_, v___x_3319_);
v___x_3321_ = lean_uint64_shift_right(v___x_3310_, v___x_3318_);
v_hi_3322_ = lean_uint64_to_nat(v___x_3321_);
v___x_3323_ = lean_array_get_size(v_pos_3257_);
v___x_3324_ = lean_nat_dec_lt(v_l_3313_, v___x_3323_);
if (v___x_3324_ == 0)
{
v___y_3279_ = v_l_3313_;
v___y_3280_ = v___y_3308_;
v___y_3281_ = v_hi_3322_;
v___y_3282_ = v_one_3267_;
v___y_3283_ = v_pos_3257_;
goto v___jp_3278_;
}
else
{
uint64_t v___x_3325_; lean_object* v_lo_3326_; lean_object* v_v_3327_; lean_object* v___x_3328_; lean_object* v_xs_x27_3329_; lean_object* v___x_3330_; lean_object* v___x_3331_; 
v___x_3325_ = lean_uint64_shift_left(v___x_3320_, v_r_3315_);
v_lo_3326_ = lean_uint64_to_nat(v___x_3325_);
v_v_3327_ = lean_array_fget(v_pos_3257_, v_l_3313_);
v___x_3328_ = lean_box(0);
v_xs_x27_3329_ = lean_array_fset(v_pos_3257_, v_l_3313_, v___x_3328_);
v___x_3330_ = lean_nat_add(v_v_3327_, v_lo_3326_);
lean_dec(v_lo_3326_);
lean_dec(v_v_3327_);
v___x_3331_ = lean_array_fset(v_xs_x27_3329_, v_l_3313_, v___x_3330_);
v___y_3279_ = v_l_3313_;
v___y_3280_ = v___y_3308_;
v___y_3281_ = v_hi_3322_;
v___y_3282_ = v_one_3267_;
v___y_3283_ = v___x_3331_;
goto v___jp_3278_;
}
}
else
{
uint64_t v___x_3332_; lean_object* v___x_3333_; lean_object* v___x_3334_; lean_object* v_l_3335_; lean_object* v___x_3336_; uint64_t v_r_3337_; uint64_t v___x_3338_; uint64_t v___x_3339_; uint64_t v___x_3340_; uint64_t v___x_3341_; uint64_t v___x_3342_; uint64_t v___x_3343_; lean_object* v_hi_3344_; lean_object* v___x_3345_; uint8_t v___x_3346_; 
v___x_3332_ = lean_uint64_of_nat(v___y_3307_);
lean_dec(v___y_3307_);
v___x_3333_ = lean_unsigned_to_nat(32u);
v___x_3334_ = lean_unsigned_to_nat(5u);
v_l_3335_ = lean_nat_shiftr(v___y_3306_, v___x_3334_);
v___x_3336_ = lean_nat_mod(v___y_3306_, v___x_3333_);
lean_dec(v___y_3306_);
v_r_3337_ = lean_uint64_of_nat(v___x_3336_);
lean_dec(v___x_3336_);
v___x_3338_ = 1ULL;
v___x_3339_ = 32ULL;
v___x_3340_ = lean_uint64_sub(v___x_3339_, v_r_3337_);
v___x_3341_ = lean_uint64_shift_left(v___x_3338_, v___x_3340_);
v___x_3342_ = lean_uint64_mod(v___x_3332_, v___x_3341_);
v___x_3343_ = lean_uint64_shift_right(v___x_3332_, v___x_3340_);
v_hi_3344_ = lean_uint64_to_nat(v___x_3343_);
v___x_3345_ = lean_array_get_size(v_neg_3258_);
v___x_3346_ = lean_nat_dec_lt(v_l_3335_, v___x_3345_);
if (v___x_3346_ == 0)
{
v___y_3293_ = v_l_3335_;
v___y_3294_ = v_one_3267_;
v___y_3295_ = v_hi_3344_;
v___y_3296_ = v_neg_3258_;
goto v___jp_3292_;
}
else
{
uint64_t v___x_3347_; lean_object* v_lo_3348_; lean_object* v_v_3349_; lean_object* v___x_3350_; lean_object* v_xs_x27_3351_; lean_object* v___x_3352_; lean_object* v___x_3353_; 
v___x_3347_ = lean_uint64_shift_left(v___x_3342_, v_r_3337_);
v_lo_3348_ = lean_uint64_to_nat(v___x_3347_);
v_v_3349_ = lean_array_fget(v_neg_3258_, v_l_3335_);
v___x_3350_ = lean_box(0);
v_xs_x27_3351_ = lean_array_fset(v_neg_3258_, v_l_3335_, v___x_3350_);
v___x_3352_ = lean_nat_add(v_v_3349_, v_lo_3348_);
lean_dec(v_lo_3348_);
lean_dec(v_v_3349_);
v___x_3353_ = lean_array_fset(v_xs_x27_3351_, v_l_3335_, v___x_3352_);
v___y_3293_ = v_l_3335_;
v___y_3294_ = v_one_3267_;
v___y_3295_ = v_hi_3344_;
v___y_3296_ = v___x_3353_;
goto v___jp_3292_;
}
}
}
else
{
lean_dec(v___y_3307_);
lean_dec(v___y_3306_);
if (v_nz_3260_ == 0)
{
v_pos_3270_ = v_pos_3257_;
v_neg_3271_ = v_neg_3258_;
v_special_3272_ = v_sp_3259_;
v_negZero_3273_ = v_nz_3260_;
goto v___jp_3269_;
}
else
{
v_pos_3270_ = v_pos_3257_;
v_neg_3271_ = v_neg_3258_;
v_special_3272_ = v_sp_3259_;
v_negZero_3273_ = v___y_3308_;
goto v___jp_3269_;
}
}
}
v___jp_3354_:
{
uint8_t v___x_3357_; 
v___x_3357_ = 1;
v___y_3306_ = v___y_3355_;
v___y_3307_ = v___y_3356_;
v___y_3308_ = v___x_3357_;
goto v___jp_3305_;
}
v___jp_3368_:
{
if (v___y_3370_ == 0)
{
if (v___y_3372_ == 0)
{
v___y_3306_ = v___y_3369_;
v___y_3307_ = v___y_3371_;
v___y_3308_ = v___x_3367_;
goto v___jp_3305_;
}
else
{
v___y_3355_ = v___y_3369_;
v___y_3356_ = v___y_3371_;
goto v___jp_3354_;
}
}
else
{
if (v___y_3372_ == 0)
{
v___y_3355_ = v___y_3369_;
v___y_3356_ = v___y_3371_;
goto v___jp_3354_;
}
else
{
v___y_3306_ = v___y_3369_;
v___y_3307_ = v___y_3371_;
v___y_3308_ = v___x_3367_;
goto v___jp_3305_;
}
}
}
v___jp_3373_:
{
uint32_t v___x_3377_; uint32_t v___x_3378_; uint32_t v___x_3379_; uint8_t v___x_3380_; 
v___x_3377_ = 2147483648;
v___x_3378_ = lean_unbox_uint32(v___x_3361_);
v___x_3379_ = lean_uint32_land(v___x_3378_, v___x_3377_);
v___x_3380_ = lean_uint32_dec_eq(v___x_3379_, v___x_3266_);
if (v___x_3380_ == 0)
{
uint8_t v___x_3381_; 
v___x_3381_ = 1;
v___y_3369_ = v___y_3374_;
v___y_3370_ = v___y_3376_;
v___y_3371_ = v___y_3375_;
v___y_3372_ = v___x_3381_;
goto v___jp_3368_;
}
else
{
v___y_3369_ = v___y_3374_;
v___y_3370_ = v___y_3376_;
v___y_3371_ = v___y_3375_;
v___y_3372_ = v___x_3367_;
goto v___jp_3368_;
}
}
v___jp_3382_:
{
lean_object* v___x_3386_; uint32_t v___x_3387_; uint32_t v___x_3388_; uint32_t v___x_3389_; uint8_t v___x_3390_; 
v___x_3386_ = lean_nat_add(v___y_3383_, v___y_3385_);
lean_dec(v___y_3385_);
lean_dec(v___y_3383_);
v___x_3387_ = 2147483648;
v___x_3388_ = lean_unbox_uint32(v___x_3361_);
v___x_3389_ = lean_uint32_land(v___x_3388_, v___x_3387_);
v___x_3390_ = lean_uint32_dec_eq(v___x_3389_, v___x_3266_);
if (v___x_3390_ == 0)
{
uint8_t v___x_3391_; 
v___x_3391_ = 1;
v___y_3374_ = v___x_3386_;
v___y_3375_ = v___y_3384_;
v___y_3376_ = v___x_3391_;
goto v___jp_3373_;
}
else
{
v___y_3374_ = v___x_3386_;
v___y_3375_ = v___y_3384_;
v___y_3376_ = v___x_3367_;
goto v___jp_3373_;
}
}
v___jp_3392_:
{
uint8_t v___x_3395_; 
v___x_3395_ = lean_uint32_dec_eq(v___x_3366_, v___x_3266_);
if (v___x_3395_ == 0)
{
lean_object* v___x_3396_; lean_object* v___x_3397_; 
v___x_3396_ = lean_uint32_to_nat(v___x_3366_);
v___x_3397_ = lean_nat_sub(v___x_3396_, v_one_3267_);
lean_dec(v___x_3396_);
v___y_3383_ = v___y_3394_;
v___y_3384_ = v___y_3393_;
v___y_3385_ = v___x_3397_;
goto v___jp_3382_;
}
else
{
v___y_3383_ = v___y_3394_;
v___y_3384_ = v___y_3393_;
v___y_3385_ = v_zero_3263_;
goto v___jp_3382_;
}
}
v___jp_3398_:
{
lean_object* v___x_3401_; uint8_t v___x_3402_; 
v___x_3401_ = lean_nat_mul(v___y_3399_, v___y_3400_);
lean_dec(v___y_3400_);
lean_dec(v___y_3399_);
v___x_3402_ = lean_uint32_dec_eq(v___x_3366_, v___x_3266_);
if (v___x_3402_ == 0)
{
lean_object* v___x_3403_; lean_object* v___x_3404_; 
v___x_3403_ = lean_uint32_to_nat(v___x_3366_);
v___x_3404_ = lean_nat_sub(v___x_3403_, v_one_3267_);
lean_dec(v___x_3403_);
v___y_3393_ = v___x_3401_;
v___y_3394_ = v___x_3404_;
goto v___jp_3392_;
}
else
{
v___y_3393_ = v___x_3401_;
v___y_3394_ = v_zero_3263_;
goto v___jp_3392_;
}
}
v___jp_3405_:
{
uint8_t v___x_3407_; 
v___x_3407_ = lean_uint32_dec_eq(v___x_3366_, v___x_3266_);
if (v___x_3407_ == 0)
{
lean_object* v___x_3408_; uint32_t v___x_3409_; uint32_t v___x_3410_; uint32_t v___x_3411_; lean_object* v___x_3412_; lean_object* v___x_3413_; 
v___x_3408_ = lean_unsigned_to_nat(8388608u);
v___x_3409_ = 8388607;
v___x_3410_ = lean_unbox_uint32(v___x_3361_);
v___x_3411_ = lean_uint32_land(v___x_3410_, v___x_3409_);
v___x_3412_ = lean_uint32_to_nat(v___x_3411_);
v___x_3413_ = lean_nat_add(v___x_3408_, v___x_3412_);
lean_dec(v___x_3412_);
v___y_3399_ = v___y_3406_;
v___y_3400_ = v___x_3413_;
goto v___jp_3398_;
}
else
{
uint32_t v___x_3414_; uint32_t v___x_3415_; uint32_t v___x_3416_; lean_object* v___x_3417_; 
v___x_3414_ = 8388607;
v___x_3415_ = lean_unbox_uint32(v___x_3361_);
v___x_3416_ = lean_uint32_land(v___x_3415_, v___x_3414_);
v___x_3417_ = lean_uint32_to_nat(v___x_3416_);
v___y_3399_ = v___y_3406_;
v___y_3400_ = v___x_3417_;
goto v___jp_3398_;
}
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_dotLoop___at___00Submission_rmsnormCached_spec__0___at___00ExactRuntime_rmsnormLegacyWith___at___00Submission_rmsnormCached_spec__1_spec__1___boxed(lean_object* v_r_3429_, lean_object* v_n_3430_, lean_object* v_x_3431_, lean_object* v_pos_3432_, lean_object* v_neg_3433_, lean_object* v_sp_3434_, lean_object* v_nz_3435_, lean_object* v_index_3436_, lean_object* v_x_3437_){
_start:
{
uint8_t v_sp_boxed_3438_; uint8_t v_nz_boxed_3439_; lean_object* v_res_3440_; 
v_sp_boxed_3438_ = lean_unbox(v_sp_3434_);
v_nz_boxed_3439_ = lean_unbox(v_nz_3435_);
v_res_3440_ = lp_competition_Submission_dotLoop___at___00Submission_rmsnormCached_spec__0___at___00ExactRuntime_rmsnormLegacyWith___at___00Submission_rmsnormCached_spec__1_spec__1(v_r_3429_, v_n_3430_, v_x_3431_, v_pos_3432_, v_neg_3433_, v_sp_boxed_3438_, v_nz_boxed_3439_, v_index_3436_, v_x_3437_);
lean_dec(v_x_3437_);
lean_dec(v_index_3436_);
lean_dec_ref(v_x_3431_);
lean_dec(v_n_3430_);
lean_dec(v_r_3429_);
return v_res_3440_;
}
}
LEAN_EXPORT uint32_t lp_competition_ExactRuntime_rmsnormLegacyWith___at___00Submission_rmsnormCached_spec__1___lam__0(lean_object* v_r_3441_, lean_object* v_n_3442_, uint32_t v___x_3443_, lean_object* v_x_3444_, lean_object* v_t_3445_){
_start:
{
lean_object* v___x_3446_; lean_object* v___x_3447_; lean_object* v___x_3448_; lean_object* v___x_3449_; uint32_t v___x_3450_; 
v___x_3446_ = lean_nat_mul(v_r_3441_, v_n_3442_);
v___x_3447_ = lean_nat_add(v___x_3446_, v_t_3445_);
lean_dec(v___x_3446_);
v___x_3448_ = lean_box_uint32(v___x_3443_);
v___x_3449_ = lean_array_get(v___x_3448_, v_x_3444_, v___x_3447_);
lean_dec(v___x_3447_);
lean_dec(v___x_3448_);
v___x_3450_ = lean_unbox_uint32(v___x_3449_);
lean_dec(v___x_3449_);
return v___x_3450_;
}
}
LEAN_EXPORT lean_object* lp_competition_ExactRuntime_rmsnormLegacyWith___at___00Submission_rmsnormCached_spec__1___lam__0___boxed(lean_object* v_r_3451_, lean_object* v_n_3452_, lean_object* v___x_3453_, lean_object* v_x_3454_, lean_object* v_t_3455_){
_start:
{
uint32_t v___x_2029__boxed_3456_; uint32_t v_res_3457_; lean_object* v_r_3458_; 
v___x_2029__boxed_3456_ = lean_unbox_uint32(v___x_3453_);
lean_dec(v___x_3453_);
v_res_3457_ = lp_competition_ExactRuntime_rmsnormLegacyWith___at___00Submission_rmsnormCached_spec__1___lam__0(v_r_3451_, v_n_3452_, v___x_2029__boxed_3456_, v_x_3454_, v_t_3455_);
lean_dec(v_t_3455_);
lean_dec_ref(v_x_3454_);
lean_dec(v_n_3452_);
lean_dec(v_r_3451_);
v_r_3458_ = lean_box_uint32(v_res_3457_);
return v_r_3458_;
}
}
LEAN_EXPORT uint32_t lp_competition_ExactRuntime_rmsnormLegacyWith___at___00Submission_rmsnormCached_spec__1___lam__3(lean_object* v_n_3459_, lean_object* v_x_3460_, uint8_t v___x_3461_, uint32_t v_eps_3462_, uint32_t v___x_3463_, lean_object* v_r_3464_){
_start:
{
lean_object* v___x_3465_; lean_object* v___x_3466_; uint8_t v___x_3467_; lean_object* v_acc_3468_; uint8_t v_special_3469_; 
v___x_3465_ = lean_unsigned_to_nat(0u);
v___x_3466_ = lean_obj_once(&lp_competition_Submission_Acc_empty___closed__0, &lp_competition_Submission_Acc_empty___closed__0_once, _init_lp_competition_Submission_Acc_empty___closed__0);
v___x_3467_ = 1;
v_acc_3468_ = lp_competition_Submission_dotLoop___at___00Submission_rmsnormCached_spec__0___at___00ExactRuntime_rmsnormLegacyWith___at___00Submission_rmsnormCached_spec__1_spec__1(v_r_3464_, v_n_3459_, v_x_3460_, v___x_3466_, v___x_3466_, v___x_3461_, v___x_3467_, v___x_3465_, v_n_3459_);
v_special_3469_ = lean_ctor_get_uint8(v_acc_3468_, sizeof(void*)*2);
if (v_special_3469_ == 0)
{
lean_object* v_pos_3470_; lean_object* v_neg_3471_; uint8_t v_negZero_3472_; lean_object* v___x_3473_; uint8_t v___x_3474_; 
lean_dec(v_r_3464_);
lean_dec_ref(v_x_3460_);
v_pos_3470_ = lean_ctor_get(v_acc_3468_, 0);
lean_inc_ref(v_pos_3470_);
v_neg_3471_ = lean_ctor_get(v_acc_3468_, 1);
lean_inc_ref(v_neg_3471_);
v_negZero_3472_ = lean_ctor_get_uint8(v_acc_3468_, sizeof(void*)*2 + 1);
lean_dec_ref(v_acc_3468_);
v___x_3473_ = lean_obj_once(&lp_competition_Submission_dotFn___closed__1, &lp_competition_Submission_dotFn___closed__1_once, _init_lp_competition_Submission_dotFn___closed__1);
v___x_3474_ = lean_nat_dec_eq(v_n_3459_, v___x_3465_);
if (v___x_3474_ == 0)
{
uint32_t v___x_3475_; uint32_t v___x_3476_; 
v___x_3475_ = lp_competition_Submission_finishFast(v_pos_3470_, v_neg_3471_, v___x_3473_, v_negZero_3472_);
lean_dec_ref(v_neg_3471_);
lean_dec_ref(v_pos_3470_);
v___x_3476_ = lp_competition_ExactRuntime_invStd(v_n_3459_, v_eps_3462_, v___x_3475_);
return v___x_3476_;
}
else
{
uint32_t v___x_3477_; uint32_t v___x_3478_; 
v___x_3477_ = lp_competition_Submission_finishFast(v_pos_3470_, v_neg_3471_, v___x_3473_, v___x_3461_);
lean_dec_ref(v_neg_3471_);
lean_dec_ref(v_pos_3470_);
v___x_3478_ = lp_competition_ExactRuntime_invStd(v_n_3459_, v_eps_3462_, v___x_3477_);
return v___x_3478_;
}
}
else
{
lean_object* v___x_3479_; lean_object* v___f_3480_; lean_object* v___f_3481_; lean_object* v___x_3482_; uint32_t v___x_3483_; uint32_t v___x_3484_; 
lean_dec_ref(v_acc_3468_);
v___x_3479_ = lean_box_uint32(v___x_3463_);
lean_inc_n(v_n_3459_, 2);
v___f_3480_ = lean_alloc_closure((void*)(lp_competition_ExactRuntime_rmsnormLegacyWith___at___00Submission_rmsnormCached_spec__1___lam__0___boxed), 5, 4);
lean_closure_set(v___f_3480_, 0, v_r_3464_);
lean_closure_set(v___f_3480_, 1, v_n_3459_);
lean_closure_set(v___f_3480_, 2, v___x_3479_);
lean_closure_set(v___f_3480_, 3, v_x_3460_);
v___f_3481_ = lean_alloc_closure((void*)(lp_competition_ExactRuntime_rmsnormLegacyWith___at___00Submission_rmsnormCached_spec__1___lam__1___boxed), 2, 1);
lean_closure_set(v___f_3481_, 0, v___f_3480_);
v___x_3482_ = l_Array_ofFn___redArg(v_n_3459_, v___f_3481_);
lean_inc_ref(v___x_3482_);
v___x_3483_ = lp_competition_ExactRuntime_dotSpec(v___x_3482_, v___x_3482_);
v___x_3484_ = lp_competition_ExactRuntime_invStd(v_n_3459_, v_eps_3462_, v___x_3483_);
return v___x_3484_;
}
}
}
LEAN_EXPORT lean_object* lp_competition_ExactRuntime_rmsnormLegacyWith___at___00Submission_rmsnormCached_spec__1___lam__3___boxed(lean_object* v_n_3485_, lean_object* v_x_3486_, lean_object* v___x_3487_, lean_object* v_eps_3488_, lean_object* v___x_3489_, lean_object* v_r_3490_){
_start:
{
uint8_t v___x_2049__boxed_3491_; uint32_t v_eps_boxed_3492_; uint32_t v___x_2050__boxed_3493_; uint32_t v_res_3494_; lean_object* v_r_3495_; 
v___x_2049__boxed_3491_ = lean_unbox(v___x_3487_);
v_eps_boxed_3492_ = lean_unbox_uint32(v_eps_3488_);
lean_dec(v_eps_3488_);
v___x_2050__boxed_3493_ = lean_unbox_uint32(v___x_3489_);
lean_dec(v___x_3489_);
v_res_3494_ = lp_competition_ExactRuntime_rmsnormLegacyWith___at___00Submission_rmsnormCached_spec__1___lam__3(v_n_3485_, v_x_3486_, v___x_2049__boxed_3491_, v_eps_boxed_3492_, v___x_2050__boxed_3493_, v_r_3490_);
v_r_3495_ = lean_box_uint32(v_res_3494_);
return v_r_3495_;
}
}
LEAN_EXPORT lean_object* lp_competition_ExactRuntime_rmsnormLegacyWith___at___00Submission_rmsnormCached_spec__1(uint8_t v___x_3496_, lean_object* v_rows_3497_, lean_object* v_n_3498_, uint32_t v_eps_3499_, lean_object* v_x_3500_, lean_object* v_g_3501_){
_start:
{
lean_object* v___x_3502_; lean_object* v___x_3503_; lean_object* v___x_3504_; lean_object* v___f_3505_; lean_object* v_scale_3506_; lean_object* v___x_3507_; lean_object* v___f_3508_; lean_object* v___x_3509_; lean_object* v___x_3510_; 
v___x_3502_ = lean_box(v___x_3496_);
v___x_3503_ = lean_box_uint32(v_eps_3499_);
v___x_3504_ = lp_competition_Submission_dotX___lam__0___boxed__const__1;
lean_inc_ref(v_x_3500_);
lean_inc_n(v_n_3498_, 2);
v___f_3505_ = lean_alloc_closure((void*)(lp_competition_ExactRuntime_rmsnormLegacyWith___at___00Submission_rmsnormCached_spec__1___lam__3___boxed), 6, 5);
lean_closure_set(v___f_3505_, 0, v_n_3498_);
lean_closure_set(v___f_3505_, 1, v_x_3500_);
lean_closure_set(v___f_3505_, 2, v___x_3502_);
lean_closure_set(v___f_3505_, 3, v___x_3503_);
lean_closure_set(v___f_3505_, 4, v___x_3504_);
lean_inc(v_rows_3497_);
v_scale_3506_ = l_Array_ofFn___redArg(v_rows_3497_, v___f_3505_);
v___x_3507_ = lp_competition_Submission_dotX___lam__0___boxed__const__1;
v___f_3508_ = lean_alloc_closure((void*)(lp_competition_ExactRuntime_rmsnormLegacyWith___at___00Submission_rmsnormCached_spec__1___lam__2___boxed), 6, 5);
lean_closure_set(v___f_3508_, 0, v___x_3507_);
lean_closure_set(v___f_3508_, 1, v_x_3500_);
lean_closure_set(v___f_3508_, 2, v_n_3498_);
lean_closure_set(v___f_3508_, 3, v_scale_3506_);
lean_closure_set(v___f_3508_, 4, v_g_3501_);
v___x_3509_ = lean_nat_mul(v_rows_3497_, v_n_3498_);
lean_dec(v_n_3498_);
lean_dec(v_rows_3497_);
v___x_3510_ = l_Array_ofFn___redArg(v___x_3509_, v___f_3508_);
return v___x_3510_;
}
}
LEAN_EXPORT lean_object* lp_competition_ExactRuntime_rmsnormLegacyWith___at___00Submission_rmsnormCached_spec__1___boxed(lean_object* v___x_3511_, lean_object* v_rows_3512_, lean_object* v_n_3513_, lean_object* v_eps_3514_, lean_object* v_x_3515_, lean_object* v_g_3516_){
_start:
{
uint8_t v___x_2088__boxed_3517_; uint32_t v_eps_boxed_3518_; lean_object* v_res_3519_; 
v___x_2088__boxed_3517_ = lean_unbox(v___x_3511_);
v_eps_boxed_3518_ = lean_unbox_uint32(v_eps_3514_);
lean_dec(v_eps_3514_);
v_res_3519_ = lp_competition_ExactRuntime_rmsnormLegacyWith___at___00Submission_rmsnormCached_spec__1(v___x_2088__boxed_3517_, v_rows_3512_, v_n_3513_, v_eps_boxed_3518_, v_x_3515_, v_g_3516_);
return v_res_3519_;
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_rmsnormCached(lean_object* v_rows_3520_, lean_object* v_n_3521_, uint32_t v_eps_3522_, lean_object* v_x_3523_, lean_object* v_g_3524_){
_start:
{
uint8_t v___x_3525_; 
v___x_3525_ = lp_competition_ExactRuntime_stableNormDomain(v_rows_3520_, v_n_3521_, v_eps_3522_, v_x_3523_, v_g_3524_);
if (v___x_3525_ == 0)
{
lean_object* v___x_3526_; 
v___x_3526_ = lp_competition_ExactRuntime_rmsnormLegacyWith___at___00Submission_rmsnormCached_spec__1(v___x_3525_, v_rows_3520_, v_n_3521_, v_eps_3522_, v_x_3523_, v_g_3524_);
return v___x_3526_;
}
else
{
lean_object* v___x_3527_; 
v___x_3527_ = lp_competition_Submission_rmsnormStableCached(v_rows_3520_, v_n_3521_, v_eps_3522_, v_x_3523_, v_g_3524_);
return v___x_3527_;
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_rmsnormCached___boxed(lean_object* v_rows_3528_, lean_object* v_n_3529_, lean_object* v_eps_3530_, lean_object* v_x_3531_, lean_object* v_g_3532_){
_start:
{
uint32_t v_eps_boxed_3533_; lean_object* v_res_3534_; 
v_eps_boxed_3533_ = lean_unbox_uint32(v_eps_3530_);
lean_dec(v_eps_3530_);
v_res_3534_ = lp_competition_Submission_rmsnormCached(v_rows_3528_, v_n_3529_, v_eps_boxed_3533_, v_x_3531_, v_g_3532_);
return v_res_3534_;
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_dotLoop___at___00Submission_rmsnormCached_spec__0(lean_object* v___y_3535_, lean_object* v___y_3536_, lean_object* v_pos_3537_, lean_object* v_neg_3538_, uint8_t v_sp_3539_, uint8_t v_nz_3540_, lean_object* v_index_3541_, lean_object* v_x_3542_){
_start:
{
lean_object* v_zero_3543_; uint8_t v_isZero_3544_; 
v_zero_3543_ = lean_unsigned_to_nat(0u);
v_isZero_3544_ = lean_nat_dec_eq(v_x_3542_, v_zero_3543_);
if (v_isZero_3544_ == 1)
{
lean_object* v___x_3545_; 
lean_dec(v_x_3542_);
lean_dec(v_index_3541_);
lean_dec_ref(v___y_3536_);
lean_dec_ref(v___y_3535_);
v___x_3545_ = lean_alloc_ctor(0, 2, 2);
lean_ctor_set(v___x_3545_, 0, v_pos_3537_);
lean_ctor_set(v___x_3545_, 1, v_neg_3538_);
lean_ctor_set_uint8(v___x_3545_, sizeof(void*)*2, v_sp_3539_);
lean_ctor_set_uint8(v___x_3545_, sizeof(void*)*2 + 1, v_nz_3540_);
return v___x_3545_;
}
else
{
lean_object* v_one_3546_; lean_object* v_n_3547_; lean_object* v_pos_3549_; lean_object* v_neg_3550_; uint8_t v_special_3551_; uint8_t v_negZero_3552_; lean_object* v___y_3558_; uint8_t v___y_3559_; lean_object* v___y_3560_; lean_object* v___y_3561_; lean_object* v___y_3562_; lean_object* v___y_3572_; lean_object* v___y_3573_; lean_object* v___y_3574_; lean_object* v___y_3575_; lean_object* v___y_3585_; lean_object* v___y_3586_; uint8_t v___y_3587_; lean_object* v___y_3634_; lean_object* v___y_3635_; lean_object* v___x_3637_; uint32_t v___x_3638_; uint32_t v___x_3639_; uint32_t v___x_3640_; uint32_t v___x_3641_; uint32_t v___x_3642_; uint8_t v___x_3643_; lean_object* v___y_3645_; lean_object* v___y_3646_; uint8_t v___y_3647_; uint8_t v___y_3648_; 
v_one_3546_ = lean_unsigned_to_nat(1u);
v_n_3547_ = lean_nat_sub(v_x_3542_, v_one_3546_);
lean_dec(v_x_3542_);
lean_inc_ref(v___y_3535_);
lean_inc(v_index_3541_);
v___x_3637_ = lean_apply_1(v___y_3535_, v_index_3541_);
v___x_3638_ = 23;
v___x_3639_ = lean_unbox_uint32(v___x_3637_);
v___x_3640_ = lean_uint32_shift_right(v___x_3639_, v___x_3638_);
v___x_3641_ = 255;
v___x_3642_ = lean_uint32_land(v___x_3640_, v___x_3641_);
v___x_3643_ = lean_uint32_dec_eq(v___x_3642_, v___x_3641_);
if (v___x_3643_ == 0)
{
lean_object* v___x_3649_; lean_object* v___y_3651_; lean_object* v___y_3652_; uint8_t v___y_3653_; lean_object* v___y_3661_; lean_object* v___y_3662_; lean_object* v___y_3663_; lean_object* v___y_3672_; lean_object* v___y_3673_; lean_object* v___y_3682_; lean_object* v___y_3683_; lean_object* v___y_3690_; uint32_t v___x_3706_; uint32_t v___x_3707_; uint32_t v___x_3708_; uint8_t v___x_3709_; 
lean_inc_ref(v___y_3536_);
lean_inc(v_index_3541_);
v___x_3649_ = lean_apply_1(v___y_3536_, v_index_3541_);
v___x_3706_ = lean_unbox_uint32(v___x_3649_);
v___x_3707_ = lean_uint32_shift_right(v___x_3706_, v___x_3638_);
v___x_3708_ = lean_uint32_land(v___x_3707_, v___x_3641_);
v___x_3709_ = lean_uint32_dec_eq(v___x_3708_, v___x_3641_);
if (v___x_3709_ == 0)
{
uint32_t v___x_3710_; uint8_t v___x_3711_; 
v___x_3710_ = 0;
v___x_3711_ = lean_uint32_dec_eq(v___x_3642_, v___x_3710_);
if (v___x_3711_ == 0)
{
lean_object* v___x_3712_; uint32_t v___x_3713_; uint32_t v___x_3714_; uint32_t v___x_3715_; lean_object* v___x_3716_; lean_object* v___x_3717_; 
v___x_3712_ = lean_unsigned_to_nat(8388608u);
v___x_3713_ = 8388607;
v___x_3714_ = lean_unbox_uint32(v___x_3637_);
v___x_3715_ = lean_uint32_land(v___x_3714_, v___x_3713_);
v___x_3716_ = lean_uint32_to_nat(v___x_3715_);
v___x_3717_ = lean_nat_add(v___x_3712_, v___x_3716_);
lean_dec(v___x_3716_);
v___y_3690_ = v___x_3717_;
goto v___jp_3689_;
}
else
{
uint32_t v___x_3718_; uint32_t v___x_3719_; uint32_t v___x_3720_; lean_object* v___x_3721_; 
v___x_3718_ = 8388607;
v___x_3719_ = lean_unbox_uint32(v___x_3637_);
v___x_3720_ = lean_uint32_land(v___x_3719_, v___x_3718_);
v___x_3721_ = lean_uint32_to_nat(v___x_3720_);
v___y_3690_ = v___x_3721_;
goto v___jp_3689_;
}
}
else
{
lean_dec(v___x_3649_);
lean_dec(v___x_3637_);
goto v___jp_3555_;
}
v___jp_3650_:
{
uint32_t v___x_3654_; uint32_t v___x_3655_; uint32_t v___x_3656_; uint32_t v___x_3657_; uint8_t v___x_3658_; 
v___x_3654_ = 2147483648;
v___x_3655_ = lean_unbox_uint32(v___x_3649_);
lean_dec(v___x_3649_);
v___x_3656_ = lean_uint32_land(v___x_3655_, v___x_3654_);
v___x_3657_ = 0;
v___x_3658_ = lean_uint32_dec_eq(v___x_3656_, v___x_3657_);
if (v___x_3658_ == 0)
{
uint8_t v___x_3659_; 
v___x_3659_ = 1;
v___y_3645_ = v___y_3651_;
v___y_3646_ = v___y_3652_;
v___y_3647_ = v___y_3653_;
v___y_3648_ = v___x_3659_;
goto v___jp_3644_;
}
else
{
v___y_3645_ = v___y_3651_;
v___y_3646_ = v___y_3652_;
v___y_3647_ = v___y_3653_;
v___y_3648_ = v___x_3643_;
goto v___jp_3644_;
}
}
v___jp_3660_:
{
lean_object* v___x_3664_; uint32_t v___x_3665_; uint32_t v___x_3666_; uint32_t v___x_3667_; uint32_t v___x_3668_; uint8_t v___x_3669_; 
v___x_3664_ = lean_nat_add(v___y_3662_, v___y_3663_);
lean_dec(v___y_3663_);
lean_dec(v___y_3662_);
v___x_3665_ = 2147483648;
v___x_3666_ = lean_unbox_uint32(v___x_3637_);
lean_dec(v___x_3637_);
v___x_3667_ = lean_uint32_land(v___x_3666_, v___x_3665_);
v___x_3668_ = 0;
v___x_3669_ = lean_uint32_dec_eq(v___x_3667_, v___x_3668_);
if (v___x_3669_ == 0)
{
uint8_t v___x_3670_; 
v___x_3670_ = 1;
v___y_3651_ = v___y_3661_;
v___y_3652_ = v___x_3664_;
v___y_3653_ = v___x_3670_;
goto v___jp_3650_;
}
else
{
v___y_3651_ = v___y_3661_;
v___y_3652_ = v___x_3664_;
v___y_3653_ = v___x_3643_;
goto v___jp_3650_;
}
}
v___jp_3671_:
{
uint32_t v___x_3674_; uint32_t v___x_3675_; uint32_t v___x_3676_; uint32_t v___x_3677_; uint8_t v___x_3678_; 
v___x_3674_ = lean_unbox_uint32(v___x_3649_);
v___x_3675_ = lean_uint32_shift_right(v___x_3674_, v___x_3638_);
v___x_3676_ = lean_uint32_land(v___x_3675_, v___x_3641_);
v___x_3677_ = 0;
v___x_3678_ = lean_uint32_dec_eq(v___x_3676_, v___x_3677_);
if (v___x_3678_ == 0)
{
lean_object* v___x_3679_; lean_object* v___x_3680_; 
v___x_3679_ = lean_uint32_to_nat(v___x_3676_);
v___x_3680_ = lean_nat_sub(v___x_3679_, v_one_3546_);
lean_dec(v___x_3679_);
v___y_3661_ = v___y_3672_;
v___y_3662_ = v___y_3673_;
v___y_3663_ = v___x_3680_;
goto v___jp_3660_;
}
else
{
v___y_3661_ = v___y_3672_;
v___y_3662_ = v___y_3673_;
v___y_3663_ = v_zero_3543_;
goto v___jp_3660_;
}
}
v___jp_3681_:
{
lean_object* v___x_3684_; uint32_t v___x_3685_; uint8_t v___x_3686_; 
v___x_3684_ = lean_nat_mul(v___y_3682_, v___y_3683_);
lean_dec(v___y_3683_);
lean_dec(v___y_3682_);
v___x_3685_ = 0;
v___x_3686_ = lean_uint32_dec_eq(v___x_3642_, v___x_3685_);
if (v___x_3686_ == 0)
{
lean_object* v___x_3687_; lean_object* v___x_3688_; 
v___x_3687_ = lean_uint32_to_nat(v___x_3642_);
v___x_3688_ = lean_nat_sub(v___x_3687_, v_one_3546_);
lean_dec(v___x_3687_);
v___y_3672_ = v___x_3684_;
v___y_3673_ = v___x_3688_;
goto v___jp_3671_;
}
else
{
v___y_3672_ = v___x_3684_;
v___y_3673_ = v_zero_3543_;
goto v___jp_3671_;
}
}
v___jp_3689_:
{
uint32_t v___x_3691_; uint32_t v___x_3692_; uint32_t v___x_3693_; uint32_t v___x_3694_; uint8_t v___x_3695_; 
v___x_3691_ = lean_unbox_uint32(v___x_3649_);
v___x_3692_ = lean_uint32_shift_right(v___x_3691_, v___x_3638_);
v___x_3693_ = lean_uint32_land(v___x_3692_, v___x_3641_);
v___x_3694_ = 0;
v___x_3695_ = lean_uint32_dec_eq(v___x_3693_, v___x_3694_);
if (v___x_3695_ == 0)
{
lean_object* v___x_3696_; uint32_t v___x_3697_; uint32_t v___x_3698_; uint32_t v___x_3699_; lean_object* v___x_3700_; lean_object* v___x_3701_; 
v___x_3696_ = lean_unsigned_to_nat(8388608u);
v___x_3697_ = 8388607;
v___x_3698_ = lean_unbox_uint32(v___x_3649_);
v___x_3699_ = lean_uint32_land(v___x_3698_, v___x_3697_);
v___x_3700_ = lean_uint32_to_nat(v___x_3699_);
v___x_3701_ = lean_nat_add(v___x_3696_, v___x_3700_);
lean_dec(v___x_3700_);
v___y_3682_ = v___y_3690_;
v___y_3683_ = v___x_3701_;
goto v___jp_3681_;
}
else
{
uint32_t v___x_3702_; uint32_t v___x_3703_; uint32_t v___x_3704_; lean_object* v___x_3705_; 
v___x_3702_ = 8388607;
v___x_3703_ = lean_unbox_uint32(v___x_3649_);
v___x_3704_ = lean_uint32_land(v___x_3703_, v___x_3702_);
v___x_3705_ = lean_uint32_to_nat(v___x_3704_);
v___y_3682_ = v___y_3690_;
v___y_3683_ = v___x_3705_;
goto v___jp_3681_;
}
}
}
else
{
lean_dec(v___x_3637_);
goto v___jp_3555_;
}
v___jp_3548_:
{
lean_object* v___x_3553_; 
v___x_3553_ = lean_nat_add(v_index_3541_, v_one_3546_);
lean_dec(v_index_3541_);
v_pos_3537_ = v_pos_3549_;
v_neg_3538_ = v_neg_3550_;
v_sp_3539_ = v_special_3551_;
v_nz_3540_ = v_negZero_3552_;
v_index_3541_ = v___x_3553_;
v_x_3542_ = v_n_3547_;
goto _start;
}
v___jp_3555_:
{
uint8_t v___x_3556_; 
v___x_3556_ = 1;
v_pos_3549_ = v_pos_3537_;
v_neg_3550_ = v_neg_3538_;
v_special_3551_ = v___x_3556_;
v_negZero_3552_ = v_nz_3540_;
goto v___jp_3548_;
}
v___jp_3557_:
{
lean_object* v___x_3563_; lean_object* v___x_3564_; uint8_t v___x_3565_; 
v___x_3563_ = lean_nat_add(v___y_3561_, v___y_3558_);
lean_dec(v___y_3561_);
v___x_3564_ = lean_array_get_size(v___y_3562_);
v___x_3565_ = lean_nat_dec_lt(v___x_3563_, v___x_3564_);
if (v___x_3565_ == 0)
{
lean_dec(v___x_3563_);
lean_dec(v___y_3560_);
v_pos_3549_ = v___y_3562_;
v_neg_3550_ = v_neg_3538_;
v_special_3551_ = v_sp_3539_;
v_negZero_3552_ = v___y_3559_;
goto v___jp_3548_;
}
else
{
lean_object* v_v_3566_; lean_object* v___x_3567_; lean_object* v_xs_x27_3568_; lean_object* v___x_3569_; lean_object* v___x_3570_; 
v_v_3566_ = lean_array_fget(v___y_3562_, v___x_3563_);
v___x_3567_ = lean_box(0);
v_xs_x27_3568_ = lean_array_fset(v___y_3562_, v___x_3563_, v___x_3567_);
v___x_3569_ = lean_nat_add(v_v_3566_, v___y_3560_);
lean_dec(v___y_3560_);
lean_dec(v_v_3566_);
v___x_3570_ = lean_array_fset(v_xs_x27_3568_, v___x_3563_, v___x_3569_);
lean_dec(v___x_3563_);
v_pos_3549_ = v___x_3570_;
v_neg_3550_ = v_neg_3538_;
v_special_3551_ = v_sp_3539_;
v_negZero_3552_ = v___y_3559_;
goto v___jp_3548_;
}
}
v___jp_3571_:
{
lean_object* v___x_3576_; lean_object* v___x_3577_; uint8_t v___x_3578_; 
v___x_3576_ = lean_nat_add(v___y_3573_, v___y_3574_);
lean_dec(v___y_3573_);
v___x_3577_ = lean_array_get_size(v___y_3575_);
v___x_3578_ = lean_nat_dec_lt(v___x_3576_, v___x_3577_);
if (v___x_3578_ == 0)
{
lean_dec(v___x_3576_);
lean_dec(v___y_3572_);
v_pos_3549_ = v_pos_3537_;
v_neg_3550_ = v___y_3575_;
v_special_3551_ = v_sp_3539_;
v_negZero_3552_ = v_isZero_3544_;
goto v___jp_3548_;
}
else
{
lean_object* v_v_3579_; lean_object* v___x_3580_; lean_object* v_xs_x27_3581_; lean_object* v___x_3582_; lean_object* v___x_3583_; 
v_v_3579_ = lean_array_fget(v___y_3575_, v___x_3576_);
v___x_3580_ = lean_box(0);
v_xs_x27_3581_ = lean_array_fset(v___y_3575_, v___x_3576_, v___x_3580_);
v___x_3582_ = lean_nat_add(v_v_3579_, v___y_3572_);
lean_dec(v___y_3572_);
lean_dec(v_v_3579_);
v___x_3583_ = lean_array_fset(v_xs_x27_3581_, v___x_3576_, v___x_3582_);
lean_dec(v___x_3576_);
v_pos_3549_ = v_pos_3537_;
v_neg_3550_ = v___x_3583_;
v_special_3551_ = v_sp_3539_;
v_negZero_3552_ = v_isZero_3544_;
goto v___jp_3548_;
}
}
v___jp_3584_:
{
uint8_t v___x_3588_; 
v___x_3588_ = lean_nat_dec_eq(v___y_3585_, v_zero_3543_);
if (v___x_3588_ == 0)
{
if (v___y_3587_ == 0)
{
uint64_t v___x_3589_; lean_object* v___x_3590_; lean_object* v___x_3591_; lean_object* v_l_3592_; lean_object* v___x_3593_; uint64_t v_r_3594_; uint64_t v___x_3595_; uint64_t v___x_3596_; uint64_t v___x_3597_; uint64_t v___x_3598_; uint64_t v___x_3599_; uint64_t v___x_3600_; lean_object* v_hi_3601_; lean_object* v___x_3602_; uint8_t v___x_3603_; 
v___x_3589_ = lean_uint64_of_nat(v___y_3585_);
lean_dec(v___y_3585_);
v___x_3590_ = lean_unsigned_to_nat(32u);
v___x_3591_ = lean_unsigned_to_nat(5u);
v_l_3592_ = lean_nat_shiftr(v___y_3586_, v___x_3591_);
v___x_3593_ = lean_nat_mod(v___y_3586_, v___x_3590_);
lean_dec(v___y_3586_);
v_r_3594_ = lean_uint64_of_nat(v___x_3593_);
lean_dec(v___x_3593_);
v___x_3595_ = 1ULL;
v___x_3596_ = 32ULL;
v___x_3597_ = lean_uint64_sub(v___x_3596_, v_r_3594_);
v___x_3598_ = lean_uint64_shift_left(v___x_3595_, v___x_3597_);
v___x_3599_ = lean_uint64_mod(v___x_3589_, v___x_3598_);
v___x_3600_ = lean_uint64_shift_right(v___x_3589_, v___x_3597_);
v_hi_3601_ = lean_uint64_to_nat(v___x_3600_);
v___x_3602_ = lean_array_get_size(v_pos_3537_);
v___x_3603_ = lean_nat_dec_lt(v_l_3592_, v___x_3602_);
if (v___x_3603_ == 0)
{
v___y_3558_ = v_one_3546_;
v___y_3559_ = v___y_3587_;
v___y_3560_ = v_hi_3601_;
v___y_3561_ = v_l_3592_;
v___y_3562_ = v_pos_3537_;
goto v___jp_3557_;
}
else
{
uint64_t v___x_3604_; lean_object* v_lo_3605_; lean_object* v_v_3606_; lean_object* v___x_3607_; lean_object* v_xs_x27_3608_; lean_object* v___x_3609_; lean_object* v___x_3610_; 
v___x_3604_ = lean_uint64_shift_left(v___x_3599_, v_r_3594_);
v_lo_3605_ = lean_uint64_to_nat(v___x_3604_);
v_v_3606_ = lean_array_fget(v_pos_3537_, v_l_3592_);
v___x_3607_ = lean_box(0);
v_xs_x27_3608_ = lean_array_fset(v_pos_3537_, v_l_3592_, v___x_3607_);
v___x_3609_ = lean_nat_add(v_v_3606_, v_lo_3605_);
lean_dec(v_lo_3605_);
lean_dec(v_v_3606_);
v___x_3610_ = lean_array_fset(v_xs_x27_3608_, v_l_3592_, v___x_3609_);
v___y_3558_ = v_one_3546_;
v___y_3559_ = v___y_3587_;
v___y_3560_ = v_hi_3601_;
v___y_3561_ = v_l_3592_;
v___y_3562_ = v___x_3610_;
goto v___jp_3557_;
}
}
else
{
uint64_t v___x_3611_; lean_object* v___x_3612_; lean_object* v___x_3613_; lean_object* v_l_3614_; lean_object* v___x_3615_; uint64_t v_r_3616_; uint64_t v___x_3617_; uint64_t v___x_3618_; uint64_t v___x_3619_; uint64_t v___x_3620_; uint64_t v___x_3621_; uint64_t v___x_3622_; lean_object* v_hi_3623_; lean_object* v___x_3624_; uint8_t v___x_3625_; 
v___x_3611_ = lean_uint64_of_nat(v___y_3585_);
lean_dec(v___y_3585_);
v___x_3612_ = lean_unsigned_to_nat(32u);
v___x_3613_ = lean_unsigned_to_nat(5u);
v_l_3614_ = lean_nat_shiftr(v___y_3586_, v___x_3613_);
v___x_3615_ = lean_nat_mod(v___y_3586_, v___x_3612_);
lean_dec(v___y_3586_);
v_r_3616_ = lean_uint64_of_nat(v___x_3615_);
lean_dec(v___x_3615_);
v___x_3617_ = 1ULL;
v___x_3618_ = 32ULL;
v___x_3619_ = lean_uint64_sub(v___x_3618_, v_r_3616_);
v___x_3620_ = lean_uint64_shift_left(v___x_3617_, v___x_3619_);
v___x_3621_ = lean_uint64_mod(v___x_3611_, v___x_3620_);
v___x_3622_ = lean_uint64_shift_right(v___x_3611_, v___x_3619_);
v_hi_3623_ = lean_uint64_to_nat(v___x_3622_);
v___x_3624_ = lean_array_get_size(v_neg_3538_);
v___x_3625_ = lean_nat_dec_lt(v_l_3614_, v___x_3624_);
if (v___x_3625_ == 0)
{
v___y_3572_ = v_hi_3623_;
v___y_3573_ = v_l_3614_;
v___y_3574_ = v_one_3546_;
v___y_3575_ = v_neg_3538_;
goto v___jp_3571_;
}
else
{
uint64_t v___x_3626_; lean_object* v_lo_3627_; lean_object* v_v_3628_; lean_object* v___x_3629_; lean_object* v_xs_x27_3630_; lean_object* v___x_3631_; lean_object* v___x_3632_; 
v___x_3626_ = lean_uint64_shift_left(v___x_3621_, v_r_3616_);
v_lo_3627_ = lean_uint64_to_nat(v___x_3626_);
v_v_3628_ = lean_array_fget(v_neg_3538_, v_l_3614_);
v___x_3629_ = lean_box(0);
v_xs_x27_3630_ = lean_array_fset(v_neg_3538_, v_l_3614_, v___x_3629_);
v___x_3631_ = lean_nat_add(v_v_3628_, v_lo_3627_);
lean_dec(v_lo_3627_);
lean_dec(v_v_3628_);
v___x_3632_ = lean_array_fset(v_xs_x27_3630_, v_l_3614_, v___x_3631_);
v___y_3572_ = v_hi_3623_;
v___y_3573_ = v_l_3614_;
v___y_3574_ = v_one_3546_;
v___y_3575_ = v___x_3632_;
goto v___jp_3571_;
}
}
}
else
{
lean_dec(v___y_3586_);
lean_dec(v___y_3585_);
if (v_nz_3540_ == 0)
{
v_pos_3549_ = v_pos_3537_;
v_neg_3550_ = v_neg_3538_;
v_special_3551_ = v_sp_3539_;
v_negZero_3552_ = v_nz_3540_;
goto v___jp_3548_;
}
else
{
v_pos_3549_ = v_pos_3537_;
v_neg_3550_ = v_neg_3538_;
v_special_3551_ = v_sp_3539_;
v_negZero_3552_ = v___y_3587_;
goto v___jp_3548_;
}
}
}
v___jp_3633_:
{
uint8_t v___x_3636_; 
v___x_3636_ = 1;
v___y_3585_ = v___y_3634_;
v___y_3586_ = v___y_3635_;
v___y_3587_ = v___x_3636_;
goto v___jp_3584_;
}
v___jp_3644_:
{
if (v___y_3647_ == 0)
{
if (v___y_3648_ == 0)
{
v___y_3585_ = v___y_3645_;
v___y_3586_ = v___y_3646_;
v___y_3587_ = v___x_3643_;
goto v___jp_3584_;
}
else
{
v___y_3634_ = v___y_3645_;
v___y_3635_ = v___y_3646_;
goto v___jp_3633_;
}
}
else
{
if (v___y_3648_ == 0)
{
v___y_3634_ = v___y_3645_;
v___y_3635_ = v___y_3646_;
goto v___jp_3633_;
}
else
{
v___y_3585_ = v___y_3645_;
v___y_3586_ = v___y_3646_;
v___y_3587_ = v___x_3643_;
goto v___jp_3584_;
}
}
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_dotLoop___at___00Submission_rmsnormCached_spec__0___boxed(lean_object* v___y_3722_, lean_object* v___y_3723_, lean_object* v_pos_3724_, lean_object* v_neg_3725_, lean_object* v_sp_3726_, lean_object* v_nz_3727_, lean_object* v_index_3728_, lean_object* v_x_3729_){
_start:
{
uint8_t v_sp_boxed_3730_; uint8_t v_nz_boxed_3731_; lean_object* v_res_3732_; 
v_sp_boxed_3730_ = lean_unbox(v_sp_3726_);
v_nz_boxed_3731_ = lean_unbox(v_nz_3727_);
v_res_3732_ = lp_competition_Submission_dotLoop___at___00Submission_rmsnormCached_spec__0(v___y_3722_, v___y_3723_, v_pos_3724_, v_neg_3725_, v_sp_boxed_3730_, v_nz_boxed_3731_, v_index_3728_, v_x_3729_);
return v_res_3732_;
}
}
LEAN_EXPORT uint32_t lp_competition_ExactRuntime_layernormLegacyWith___at___00Submission_layernormCached_spec__0___lam__4(lean_object* v_n_3733_, uint32_t v___x_3734_, lean_object* v_x_3735_, lean_object* v___f_3736_, lean_object* v___f_3737_, lean_object* v_r_3738_){
_start:
{
lean_object* v___x_3739_; lean_object* v___f_3740_; lean_object* v___x_3741_; uint32_t v___x_3742_; lean_object* v___x_3743_; lean_object* v___x_3744_; lean_object* v___x_3745_; uint32_t v___x_3746_; lean_object* v___x_3747_; lean_object* v___x_3748_; lean_object* v___x_3749_; uint32_t v___x_3750_; 
v___x_3739_ = lean_box_uint32(v___x_3734_);
lean_inc_n(v_n_3733_, 2);
v___f_3740_ = lean_alloc_closure((void*)(lp_competition_ExactRuntime_rmsnormLegacyWith___at___00Submission_rmsnormCached_spec__1___lam__0___boxed), 5, 4);
lean_closure_set(v___f_3740_, 0, v_r_3738_);
lean_closure_set(v___f_3740_, 1, v_n_3733_);
lean_closure_set(v___f_3740_, 2, v___x_3739_);
lean_closure_set(v___f_3740_, 3, v_x_3735_);
v___x_3741_ = lean_apply_3(v___f_3736_, v_n_3733_, v___f_3740_, v___f_3737_);
v___x_3742_ = lean_unbox_uint32(v___x_3741_);
lean_dec(v___x_3741_);
v___x_3743_ = lean_uint32_to_nat(v___x_3742_);
v___x_3744_ = lean_unsigned_to_nat(32u);
v___x_3745_ = l_BitVec_ofNat(v___x_3744_, v___x_3743_);
lean_dec(v___x_3743_);
v___x_3746_ = lp_competition_ExactRuntime_natW(v_n_3733_);
v___x_3747_ = lean_uint32_to_nat(v___x_3746_);
v___x_3748_ = l_BitVec_ofNat(v___x_3744_, v___x_3747_);
lean_dec(v___x_3747_);
v___x_3749_ = lp_floatlib_FloatLib_Floats_Formats_BinaryInterchange_Model_DivBackend_word___at___00FloatLib_Floats_Formats_BinaryInterchange_Configured_Plan_softwareDiv32Certified_spec__1(v___x_3745_, v___x_3748_);
v___x_3750_ = lean_uint32_of_nat(v___x_3749_);
lean_dec(v___x_3749_);
return v___x_3750_;
}
}
LEAN_EXPORT lean_object* lp_competition_ExactRuntime_layernormLegacyWith___at___00Submission_layernormCached_spec__0___lam__4___boxed(lean_object* v_n_3751_, lean_object* v___x_3752_, lean_object* v_x_3753_, lean_object* v___f_3754_, lean_object* v___f_3755_, lean_object* v_r_3756_){
_start:
{
uint32_t v___x_519__boxed_3757_; uint32_t v_res_3758_; lean_object* v_r_3759_; 
v___x_519__boxed_3757_ = lean_unbox_uint32(v___x_3752_);
lean_dec(v___x_3752_);
v_res_3758_ = lp_competition_ExactRuntime_layernormLegacyWith___at___00Submission_layernormCached_spec__0___lam__4(v_n_3751_, v___x_519__boxed_3757_, v_x_3753_, v___f_3754_, v___f_3755_, v_r_3756_);
v_r_3759_ = lean_box_uint32(v_res_3758_);
return v_r_3759_;
}
}
LEAN_EXPORT uint32_t lp_competition_ExactRuntime_layernormLegacyWith___at___00Submission_layernormCached_spec__0___lam__0(lean_object* v_x_3760_){
_start:
{
uint32_t v___x_3761_; 
v___x_3761_ = 1065353216;
return v___x_3761_;
}
}
LEAN_EXPORT lean_object* lp_competition_ExactRuntime_layernormLegacyWith___at___00Submission_layernormCached_spec__0___lam__0___boxed(lean_object* v_x_3762_){
_start:
{
uint32_t v_res_3763_; lean_object* v_r_3764_; 
v_res_3763_ = lp_competition_ExactRuntime_layernormLegacyWith___at___00Submission_layernormCached_spec__0___lam__0(v_x_3762_);
lean_dec(v_x_3762_);
v_r_3764_ = lean_box_uint32(v_res_3763_);
return v_r_3764_;
}
}
LEAN_EXPORT uint32_t lp_competition_ExactRuntime_layernormLegacyWith___at___00Submission_layernormCached_spec__0___lam__2(uint32_t v___x_3765_, lean_object* v_mean_3766_, lean_object* v_r_3767_, lean_object* v_n_3768_, lean_object* v_x_3769_, lean_object* v_t_3770_){
_start:
{
lean_object* v___x_3771_; lean_object* v___x_3772_; lean_object* v___x_3773_; lean_object* v___x_3774_; lean_object* v___x_3775_; lean_object* v___x_3776_; uint32_t v___x_3777_; lean_object* v___x_3778_; lean_object* v___x_3779_; lean_object* v___x_3780_; uint32_t v___x_3781_; lean_object* v___x_3782_; lean_object* v___x_3783_; lean_object* v___x_3784_; uint32_t v___x_3785_; 
v___x_3771_ = lean_box_uint32(v___x_3765_);
v___x_3772_ = lean_array_get(v___x_3771_, v_mean_3766_, v_r_3767_);
lean_dec(v___x_3771_);
v___x_3773_ = lean_nat_mul(v_r_3767_, v_n_3768_);
v___x_3774_ = lean_nat_add(v___x_3773_, v_t_3770_);
lean_dec(v___x_3773_);
v___x_3775_ = lean_box_uint32(v___x_3765_);
v___x_3776_ = lean_array_get(v___x_3775_, v_x_3769_, v___x_3774_);
lean_dec(v___x_3774_);
lean_dec(v___x_3775_);
v___x_3777_ = lean_unbox_uint32(v___x_3776_);
lean_dec(v___x_3776_);
v___x_3778_ = lean_uint32_to_nat(v___x_3777_);
v___x_3779_ = lean_unsigned_to_nat(32u);
v___x_3780_ = l_BitVec_ofNat(v___x_3779_, v___x_3778_);
lean_dec(v___x_3778_);
v___x_3781_ = lean_unbox_uint32(v___x_3772_);
lean_dec(v___x_3772_);
v___x_3782_ = lean_uint32_to_nat(v___x_3781_);
v___x_3783_ = l_BitVec_ofNat(v___x_3779_, v___x_3782_);
lean_dec(v___x_3782_);
v___x_3784_ = lp_floatlib_FloatLib_Floats_Formats_BinaryInterchange_Model_AddBackend_subWord___at___00FloatLib_Floats_Formats_BinaryInterchange_Configured_Plan_softwareSub32Certified_spec__1(v___x_3780_, v___x_3783_);
v___x_3785_ = lean_uint32_of_nat(v___x_3784_);
lean_dec(v___x_3784_);
return v___x_3785_;
}
}
LEAN_EXPORT lean_object* lp_competition_ExactRuntime_layernormLegacyWith___at___00Submission_layernormCached_spec__0___lam__2___boxed(lean_object* v___x_3786_, lean_object* v_mean_3787_, lean_object* v_r_3788_, lean_object* v_n_3789_, lean_object* v_x_3790_, lean_object* v_t_3791_){
_start:
{
uint32_t v___x_557__boxed_3792_; uint32_t v_res_3793_; lean_object* v_r_3794_; 
v___x_557__boxed_3792_ = lean_unbox_uint32(v___x_3786_);
lean_dec(v___x_3786_);
v_res_3793_ = lp_competition_ExactRuntime_layernormLegacyWith___at___00Submission_layernormCached_spec__0___lam__2(v___x_557__boxed_3792_, v_mean_3787_, v_r_3788_, v_n_3789_, v_x_3790_, v_t_3791_);
lean_dec(v_t_3791_);
lean_dec_ref(v_x_3790_);
lean_dec(v_n_3789_);
lean_dec(v_r_3788_);
lean_dec_ref(v_mean_3787_);
v_r_3794_ = lean_box_uint32(v_res_3793_);
return v_r_3794_;
}
}
LEAN_EXPORT uint32_t lp_competition_ExactRuntime_layernormLegacyWith___at___00Submission_layernormCached_spec__0___lam__5(uint32_t v___x_3795_, lean_object* v_mean_3796_, lean_object* v_n_3797_, lean_object* v_x_3798_, lean_object* v___f_3799_, uint32_t v_eps_3800_, lean_object* v_r_3801_){
_start:
{
lean_object* v___x_3802_; lean_object* v___f_3803_; lean_object* v___x_3804_; uint32_t v___x_3805_; uint32_t v___x_3806_; 
v___x_3802_ = lean_box_uint32(v___x_3795_);
lean_inc_n(v_n_3797_, 2);
v___f_3803_ = lean_alloc_closure((void*)(lp_competition_ExactRuntime_layernormLegacyWith___at___00Submission_layernormCached_spec__0___lam__2___boxed), 6, 5);
lean_closure_set(v___f_3803_, 0, v___x_3802_);
lean_closure_set(v___f_3803_, 1, v_mean_3796_);
lean_closure_set(v___f_3803_, 2, v_r_3801_);
lean_closure_set(v___f_3803_, 3, v_n_3797_);
lean_closure_set(v___f_3803_, 4, v_x_3798_);
lean_inc_ref(v___f_3803_);
v___x_3804_ = lean_apply_3(v___f_3799_, v_n_3797_, v___f_3803_, v___f_3803_);
v___x_3805_ = lean_unbox_uint32(v___x_3804_);
lean_dec(v___x_3804_);
v___x_3806_ = lp_competition_ExactRuntime_invStd(v_n_3797_, v_eps_3800_, v___x_3805_);
return v___x_3806_;
}
}
LEAN_EXPORT lean_object* lp_competition_ExactRuntime_layernormLegacyWith___at___00Submission_layernormCached_spec__0___lam__5___boxed(lean_object* v___x_3807_, lean_object* v_mean_3808_, lean_object* v_n_3809_, lean_object* v_x_3810_, lean_object* v___f_3811_, lean_object* v_eps_3812_, lean_object* v_r_3813_){
_start:
{
uint32_t v___x_590__boxed_3814_; uint32_t v_eps_boxed_3815_; uint32_t v_res_3816_; lean_object* v_r_3817_; 
v___x_590__boxed_3814_ = lean_unbox_uint32(v___x_3807_);
lean_dec(v___x_3807_);
v_eps_boxed_3815_ = lean_unbox_uint32(v_eps_3812_);
lean_dec(v_eps_3812_);
v_res_3816_ = lp_competition_ExactRuntime_layernormLegacyWith___at___00Submission_layernormCached_spec__0___lam__5(v___x_590__boxed_3814_, v_mean_3808_, v_n_3809_, v_x_3810_, v___f_3811_, v_eps_boxed_3815_, v_r_3813_);
v_r_3817_ = lean_box_uint32(v_res_3816_);
return v_r_3817_;
}
}
LEAN_EXPORT uint32_t lp_competition_ExactRuntime_layernormLegacyWith___at___00Submission_layernormCached_spec__0___lam__6(lean_object* v_n_3818_, uint32_t v___x_3819_, lean_object* v_mean_3820_, lean_object* v_x_3821_, lean_object* v_scale_3822_, lean_object* v_g_3823_, lean_object* v_b_3824_, lean_object* v_q_3825_){
_start:
{
lean_object* v___x_3826_; lean_object* v___x_3827_; lean_object* v___x_3828_; lean_object* v___x_3829_; lean_object* v___x_3830_; uint32_t v___x_3831_; lean_object* v___x_3832_; lean_object* v___x_3833_; lean_object* v___x_3834_; uint32_t v___x_3835_; lean_object* v___x_3836_; lean_object* v___x_3837_; lean_object* v___x_3838_; uint32_t v___x_3839_; lean_object* v___x_3840_; lean_object* v___x_3841_; lean_object* v___x_3842_; lean_object* v___x_3843_; uint32_t v___x_3844_; lean_object* v___x_3845_; lean_object* v___x_3846_; lean_object* v___x_3847_; lean_object* v___x_3848_; lean_object* v___x_3849_; lean_object* v___x_3850_; uint32_t v___x_3851_; lean_object* v___x_3852_; lean_object* v___x_3853_; lean_object* v___x_3854_; lean_object* v___x_3855_; lean_object* v___x_3856_; uint32_t v___x_3857_; lean_object* v___x_3858_; lean_object* v___x_3859_; lean_object* v___x_3860_; uint32_t v___x_3861_; 
v___x_3826_ = lean_nat_div(v_q_3825_, v_n_3818_);
v___x_3827_ = lean_box_uint32(v___x_3819_);
v___x_3828_ = lean_array_get(v___x_3827_, v_mean_3820_, v___x_3826_);
lean_dec(v___x_3827_);
v___x_3829_ = lean_box_uint32(v___x_3819_);
v___x_3830_ = lean_array_get(v___x_3829_, v_x_3821_, v_q_3825_);
lean_dec(v___x_3829_);
v___x_3831_ = lean_unbox_uint32(v___x_3830_);
lean_dec(v___x_3830_);
v___x_3832_ = lean_uint32_to_nat(v___x_3831_);
v___x_3833_ = lean_unsigned_to_nat(32u);
v___x_3834_ = l_BitVec_ofNat(v___x_3833_, v___x_3832_);
lean_dec(v___x_3832_);
v___x_3835_ = lean_unbox_uint32(v___x_3828_);
lean_dec(v___x_3828_);
v___x_3836_ = lean_uint32_to_nat(v___x_3835_);
v___x_3837_ = l_BitVec_ofNat(v___x_3833_, v___x_3836_);
lean_dec(v___x_3836_);
v___x_3838_ = lp_floatlib_FloatLib_Floats_Formats_BinaryInterchange_Model_AddBackend_subWord___at___00FloatLib_Floats_Formats_BinaryInterchange_Configured_Plan_softwareSub32Certified_spec__1(v___x_3834_, v___x_3837_);
v___x_3839_ = lean_uint32_of_nat(v___x_3838_);
lean_dec(v___x_3838_);
v___x_3840_ = lean_uint32_to_nat(v___x_3839_);
v___x_3841_ = l_BitVec_ofNat(v___x_3833_, v___x_3840_);
lean_dec(v___x_3840_);
v___x_3842_ = lean_box_uint32(v___x_3819_);
v___x_3843_ = lean_array_get(v___x_3842_, v_scale_3822_, v___x_3826_);
lean_dec(v___x_3826_);
lean_dec(v___x_3842_);
v___x_3844_ = lean_unbox_uint32(v___x_3843_);
lean_dec(v___x_3843_);
v___x_3845_ = lean_uint32_to_nat(v___x_3844_);
v___x_3846_ = l_BitVec_ofNat(v___x_3833_, v___x_3845_);
lean_dec(v___x_3845_);
v___x_3847_ = lp_floatlib_FloatLib_Floats_Formats_BinaryInterchange_Model_MulBackend_word___at___00FloatLib_Floats_Formats_BinaryInterchange_Configured_Plan_softwareMul32Certified_spec__1(v___x_3841_, v___x_3846_);
v___x_3848_ = lean_nat_mod(v_q_3825_, v_n_3818_);
v___x_3849_ = lean_box_uint32(v___x_3819_);
v___x_3850_ = lean_array_get(v___x_3849_, v_g_3823_, v___x_3848_);
lean_dec(v___x_3849_);
v___x_3851_ = lean_unbox_uint32(v___x_3850_);
lean_dec(v___x_3850_);
v___x_3852_ = lean_uint32_to_nat(v___x_3851_);
v___x_3853_ = l_BitVec_ofNat(v___x_3833_, v___x_3852_);
lean_dec(v___x_3852_);
v___x_3854_ = lp_floatlib_FloatLib_Floats_Formats_BinaryInterchange_Model_MulBackend_word___at___00FloatLib_Floats_Formats_BinaryInterchange_Configured_Plan_softwareMul32Certified_spec__1(v___x_3847_, v___x_3853_);
v___x_3855_ = lean_box_uint32(v___x_3819_);
v___x_3856_ = lean_array_get(v___x_3855_, v_b_3824_, v___x_3848_);
lean_dec(v___x_3848_);
lean_dec(v___x_3855_);
v___x_3857_ = lean_unbox_uint32(v___x_3856_);
lean_dec(v___x_3856_);
v___x_3858_ = lean_uint32_to_nat(v___x_3857_);
v___x_3859_ = l_BitVec_ofNat(v___x_3833_, v___x_3858_);
lean_dec(v___x_3858_);
v___x_3860_ = lp_floatlib_FloatLib_Floats_Formats_BinaryInterchange_Model_AddBackend_word___at___00FloatLib_Floats_Formats_BinaryInterchange_Configured_Plan_softwareAdd32Certified_spec__1(v___x_3854_, v___x_3859_);
v___x_3861_ = lean_uint32_of_nat(v___x_3860_);
lean_dec(v___x_3860_);
return v___x_3861_;
}
}
LEAN_EXPORT lean_object* lp_competition_ExactRuntime_layernormLegacyWith___at___00Submission_layernormCached_spec__0___lam__6___boxed(lean_object* v_n_3862_, lean_object* v___x_3863_, lean_object* v_mean_3864_, lean_object* v_x_3865_, lean_object* v_scale_3866_, lean_object* v_g_3867_, lean_object* v_b_3868_, lean_object* v_q_3869_){
_start:
{
uint32_t v___x_606__boxed_3870_; uint32_t v_res_3871_; lean_object* v_r_3872_; 
v___x_606__boxed_3870_ = lean_unbox_uint32(v___x_3863_);
lean_dec(v___x_3863_);
v_res_3871_ = lp_competition_ExactRuntime_layernormLegacyWith___at___00Submission_layernormCached_spec__0___lam__6(v_n_3862_, v___x_606__boxed_3870_, v_mean_3864_, v_x_3865_, v_scale_3866_, v_g_3867_, v_b_3868_, v_q_3869_);
lean_dec(v_q_3869_);
lean_dec_ref(v_b_3868_);
lean_dec_ref(v_g_3867_);
lean_dec_ref(v_scale_3866_);
lean_dec_ref(v_x_3865_);
lean_dec_ref(v_mean_3864_);
lean_dec(v_n_3862_);
v_r_3872_ = lean_box_uint32(v_res_3871_);
return v_r_3872_;
}
}
LEAN_EXPORT uint32_t lp_competition_ExactRuntime_layernormLegacyWith___at___00Submission_layernormCached_spec__0___lam__1(lean_object* v___y_3873_, lean_object* v_i_3874_){
_start:
{
lean_object* v___x_3875_; uint32_t v___x_3876_; 
v___x_3875_ = lean_apply_1(v___y_3873_, v_i_3874_);
v___x_3876_ = lean_unbox_uint32(v___x_3875_);
lean_dec(v___x_3875_);
return v___x_3876_;
}
}
LEAN_EXPORT lean_object* lp_competition_ExactRuntime_layernormLegacyWith___at___00Submission_layernormCached_spec__0___lam__1___boxed(lean_object* v___y_3877_, lean_object* v_i_3878_){
_start:
{
uint32_t v_res_3879_; lean_object* v_r_3880_; 
v_res_3879_ = lp_competition_ExactRuntime_layernormLegacyWith___at___00Submission_layernormCached_spec__0___lam__1(v___y_3877_, v_i_3878_);
v_r_3880_ = lean_box_uint32(v_res_3879_);
return v_r_3880_;
}
}
LEAN_EXPORT uint32_t lp_competition_ExactRuntime_layernormLegacyWith___at___00Submission_layernormCached_spec__0___lam__3(lean_object* v___y_3881_, lean_object* v___y_3882_, lean_object* v___y_3883_){
_start:
{
lean_object* v___x_3884_; lean_object* v___x_3885_; uint8_t v___x_3886_; uint8_t v___x_3887_; lean_object* v_acc_3888_; uint8_t v_special_3889_; 
v___x_3884_ = lean_unsigned_to_nat(0u);
v___x_3885_ = lean_obj_once(&lp_competition_Submission_Acc_empty___closed__0, &lp_competition_Submission_Acc_empty___closed__0_once, _init_lp_competition_Submission_Acc_empty___closed__0);
v___x_3886_ = 0;
v___x_3887_ = 1;
lean_inc(v___y_3881_);
lean_inc_ref(v___y_3883_);
lean_inc_ref(v___y_3882_);
v_acc_3888_ = lp_competition_Submission_dotLoop___at___00Submission_rmsnormCached_spec__0(v___y_3882_, v___y_3883_, v___x_3885_, v___x_3885_, v___x_3886_, v___x_3887_, v___x_3884_, v___y_3881_);
v_special_3889_ = lean_ctor_get_uint8(v_acc_3888_, sizeof(void*)*2);
if (v_special_3889_ == 0)
{
lean_object* v_pos_3890_; lean_object* v_neg_3891_; uint8_t v_negZero_3892_; lean_object* v___x_3893_; uint8_t v___x_3894_; 
lean_dec_ref(v___y_3883_);
lean_dec_ref(v___y_3882_);
v_pos_3890_ = lean_ctor_get(v_acc_3888_, 0);
lean_inc_ref(v_pos_3890_);
v_neg_3891_ = lean_ctor_get(v_acc_3888_, 1);
lean_inc_ref(v_neg_3891_);
v_negZero_3892_ = lean_ctor_get_uint8(v_acc_3888_, sizeof(void*)*2 + 1);
lean_dec_ref(v_acc_3888_);
v___x_3893_ = lean_obj_once(&lp_competition_Submission_dotFn___closed__1, &lp_competition_Submission_dotFn___closed__1_once, _init_lp_competition_Submission_dotFn___closed__1);
v___x_3894_ = lean_nat_dec_eq(v___y_3881_, v___x_3884_);
lean_dec(v___y_3881_);
if (v___x_3894_ == 0)
{
uint32_t v___x_3895_; 
v___x_3895_ = lp_competition_Submission_finishFast(v_pos_3890_, v_neg_3891_, v___x_3893_, v_negZero_3892_);
lean_dec_ref(v_neg_3891_);
lean_dec_ref(v_pos_3890_);
return v___x_3895_;
}
else
{
uint32_t v___x_3896_; 
v___x_3896_ = lp_competition_Submission_finishFast(v_pos_3890_, v_neg_3891_, v___x_3893_, v___x_3886_);
lean_dec_ref(v_neg_3891_);
lean_dec_ref(v_pos_3890_);
return v___x_3896_;
}
}
else
{
lean_object* v___f_3897_; lean_object* v___f_3898_; lean_object* v___x_3899_; lean_object* v___x_3900_; uint32_t v___x_3901_; 
lean_dec_ref(v_acc_3888_);
v___f_3897_ = lean_alloc_closure((void*)(lp_competition_ExactRuntime_layernormLegacyWith___at___00Submission_layernormCached_spec__0___lam__1___boxed), 2, 1);
lean_closure_set(v___f_3897_, 0, v___y_3883_);
v___f_3898_ = lean_alloc_closure((void*)(lp_competition_ExactRuntime_layernormLegacyWith___at___00Submission_layernormCached_spec__0___lam__1___boxed), 2, 1);
lean_closure_set(v___f_3898_, 0, v___y_3882_);
lean_inc(v___y_3881_);
v___x_3899_ = l_Array_ofFn___redArg(v___y_3881_, v___f_3898_);
v___x_3900_ = l_Array_ofFn___redArg(v___y_3881_, v___f_3897_);
v___x_3901_ = lp_competition_ExactRuntime_dotSpec(v___x_3899_, v___x_3900_);
return v___x_3901_;
}
}
}
LEAN_EXPORT lean_object* lp_competition_ExactRuntime_layernormLegacyWith___at___00Submission_layernormCached_spec__0___lam__3___boxed(lean_object* v___y_3902_, lean_object* v___y_3903_, lean_object* v___y_3904_){
_start:
{
uint32_t v_res_3905_; lean_object* v_r_3906_; 
v_res_3905_ = lp_competition_ExactRuntime_layernormLegacyWith___at___00Submission_layernormCached_spec__0___lam__3(v___y_3902_, v___y_3903_, v___y_3904_);
v_r_3906_ = lean_box_uint32(v_res_3905_);
return v_r_3906_;
}
}
LEAN_EXPORT lean_object* lp_competition_ExactRuntime_layernormLegacyWith___at___00Submission_layernormCached_spec__0(lean_object* v_rows_3909_, lean_object* v_n_3910_, uint32_t v_eps_3911_, lean_object* v_x_3912_, lean_object* v_g_3913_, lean_object* v_b_3914_){
_start:
{
lean_object* v___f_3915_; lean_object* v___f_3916_; lean_object* v___x_3917_; lean_object* v___f_3918_; lean_object* v_mean_3919_; lean_object* v___x_3920_; lean_object* v___x_3921_; lean_object* v___f_3922_; lean_object* v_scale_3923_; lean_object* v___x_3924_; lean_object* v___f_3925_; lean_object* v___x_3926_; lean_object* v___x_3927_; 
v___f_3915_ = ((lean_object*)(lp_competition_ExactRuntime_layernormLegacyWith___at___00Submission_layernormCached_spec__0___closed__0));
v___f_3916_ = ((lean_object*)(lp_competition_ExactRuntime_layernormLegacyWith___at___00Submission_layernormCached_spec__0___closed__1));
v___x_3917_ = lp_competition_Submission_dotX___lam__0___boxed__const__1;
lean_inc_ref_n(v_x_3912_, 2);
lean_inc_n(v_n_3910_, 3);
v___f_3918_ = lean_alloc_closure((void*)(lp_competition_ExactRuntime_layernormLegacyWith___at___00Submission_layernormCached_spec__0___lam__4___boxed), 6, 5);
lean_closure_set(v___f_3918_, 0, v_n_3910_);
lean_closure_set(v___f_3918_, 1, v___x_3917_);
lean_closure_set(v___f_3918_, 2, v_x_3912_);
lean_closure_set(v___f_3918_, 3, v___f_3916_);
lean_closure_set(v___f_3918_, 4, v___f_3915_);
lean_inc_n(v_rows_3909_, 2);
v_mean_3919_ = l_Array_ofFn___redArg(v_rows_3909_, v___f_3918_);
v___x_3920_ = lp_competition_Submission_dotX___lam__0___boxed__const__1;
v___x_3921_ = lean_box_uint32(v_eps_3911_);
lean_inc_ref(v_mean_3919_);
v___f_3922_ = lean_alloc_closure((void*)(lp_competition_ExactRuntime_layernormLegacyWith___at___00Submission_layernormCached_spec__0___lam__5___boxed), 7, 6);
lean_closure_set(v___f_3922_, 0, v___x_3920_);
lean_closure_set(v___f_3922_, 1, v_mean_3919_);
lean_closure_set(v___f_3922_, 2, v_n_3910_);
lean_closure_set(v___f_3922_, 3, v_x_3912_);
lean_closure_set(v___f_3922_, 4, v___f_3916_);
lean_closure_set(v___f_3922_, 5, v___x_3921_);
v_scale_3923_ = l_Array_ofFn___redArg(v_rows_3909_, v___f_3922_);
v___x_3924_ = lp_competition_Submission_dotX___lam__0___boxed__const__1;
v___f_3925_ = lean_alloc_closure((void*)(lp_competition_ExactRuntime_layernormLegacyWith___at___00Submission_layernormCached_spec__0___lam__6___boxed), 8, 7);
lean_closure_set(v___f_3925_, 0, v_n_3910_);
lean_closure_set(v___f_3925_, 1, v___x_3924_);
lean_closure_set(v___f_3925_, 2, v_mean_3919_);
lean_closure_set(v___f_3925_, 3, v_x_3912_);
lean_closure_set(v___f_3925_, 4, v_scale_3923_);
lean_closure_set(v___f_3925_, 5, v_g_3913_);
lean_closure_set(v___f_3925_, 6, v_b_3914_);
v___x_3926_ = lean_nat_mul(v_rows_3909_, v_n_3910_);
lean_dec(v_n_3910_);
lean_dec(v_rows_3909_);
v___x_3927_ = l_Array_ofFn___redArg(v___x_3926_, v___f_3925_);
return v___x_3927_;
}
}
LEAN_EXPORT lean_object* lp_competition_ExactRuntime_layernormLegacyWith___at___00Submission_layernormCached_spec__0___boxed(lean_object* v_rows_3928_, lean_object* v_n_3929_, lean_object* v_eps_3930_, lean_object* v_x_3931_, lean_object* v_g_3932_, lean_object* v_b_3933_){
_start:
{
uint32_t v_eps_boxed_3934_; lean_object* v_res_3935_; 
v_eps_boxed_3934_ = lean_unbox_uint32(v_eps_3930_);
lean_dec(v_eps_3930_);
v_res_3935_ = lp_competition_ExactRuntime_layernormLegacyWith___at___00Submission_layernormCached_spec__0(v_rows_3928_, v_n_3929_, v_eps_boxed_3934_, v_x_3931_, v_g_3932_, v_b_3933_);
return v_res_3935_;
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_layernormCached(lean_object* v_rows_3936_, lean_object* v_n_3937_, uint32_t v_eps_3938_, lean_object* v_x_3939_, lean_object* v_g_3940_, lean_object* v_b_3941_){
_start:
{
uint8_t v___y_3943_; uint8_t v___x_3955_; 
v___x_3955_ = lp_competition_ExactRuntime_stableNormDomain(v_rows_3936_, v_n_3937_, v_eps_3938_, v_x_3939_, v_g_3940_);
if (v___x_3955_ == 0)
{
v___y_3943_ = v___x_3955_;
goto v___jp_3942_;
}
else
{
lean_object* v___x_3956_; uint8_t v___x_3957_; 
v___x_3956_ = lean_array_get_size(v_b_3941_);
v___x_3957_ = lean_nat_dec_eq(v___x_3956_, v_n_3937_);
v___y_3943_ = v___x_3957_;
goto v___jp_3942_;
}
v___jp_3942_:
{
if (v___y_3943_ == 0)
{
lean_object* v___x_3944_; 
v___x_3944_ = lp_competition_ExactRuntime_layernormLegacyWith___at___00Submission_layernormCached_spec__0(v_rows_3936_, v_n_3937_, v_eps_3938_, v_x_3939_, v_g_3940_, v_b_3941_);
return v___x_3944_;
}
else
{
lean_object* v___x_3945_; lean_object* v___x_3946_; uint8_t v___x_3947_; 
v___x_3945_ = lean_unsigned_to_nat(0u);
v___x_3946_ = lean_array_get_size(v_b_3941_);
v___x_3947_ = lean_nat_dec_lt(v___x_3945_, v___x_3946_);
if (v___x_3947_ == 0)
{
lean_object* v___x_3948_; 
v___x_3948_ = lp_competition_Submission_layernormStableCached(v_rows_3936_, v_n_3937_, v_eps_3938_, v_x_3939_, v_g_3940_, v_b_3941_);
return v___x_3948_;
}
else
{
if (v___x_3947_ == 0)
{
lean_object* v___x_3949_; 
v___x_3949_ = lp_competition_Submission_layernormStableCached(v_rows_3936_, v_n_3937_, v_eps_3938_, v_x_3939_, v_g_3940_, v_b_3941_);
return v___x_3949_;
}
else
{
size_t v___x_3950_; size_t v___x_3951_; uint8_t v___x_3952_; 
v___x_3950_ = ((size_t)0ULL);
v___x_3951_ = lean_usize_of_nat(v___x_3946_);
v___x_3952_ = lp_competition___private_Init_Data_Array_Basic_0__Array_anyMUnsafe_any___at___00ExactRuntime_stableNormDomain_spec__0(v___y_3943_, v_b_3941_, v___x_3950_, v___x_3951_);
if (v___x_3952_ == 0)
{
lean_object* v___x_3953_; 
v___x_3953_ = lp_competition_Submission_layernormStableCached(v_rows_3936_, v_n_3937_, v_eps_3938_, v_x_3939_, v_g_3940_, v_b_3941_);
return v___x_3953_;
}
else
{
lean_object* v___x_3954_; 
v___x_3954_ = lp_competition_ExactRuntime_layernormLegacyWith___at___00Submission_layernormCached_spec__0(v_rows_3936_, v_n_3937_, v_eps_3938_, v_x_3939_, v_g_3940_, v_b_3941_);
return v___x_3954_;
}
}
}
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_layernormCached___boxed(lean_object* v_rows_3958_, lean_object* v_n_3959_, lean_object* v_eps_3960_, lean_object* v_x_3961_, lean_object* v_g_3962_, lean_object* v_b_3963_){
_start:
{
uint32_t v_eps_boxed_3964_; lean_object* v_res_3965_; 
v_eps_boxed_3964_ = lean_unbox_uint32(v_eps_3960_);
lean_dec(v_eps_3960_);
v_res_3965_ = lp_competition_Submission_layernormCached(v_rows_3958_, v_n_3959_, v_eps_boxed_3964_, v_x_3961_, v_g_3962_, v_b_3963_);
return v_res_3965_;
}
}
LEAN_EXPORT uint32_t lp_competition_ExactRuntime_conv2dWith___at___00Submission_kernels_spec__2___lam__1(lean_object* v_k_3966_, lean_object* v_kw_3967_, lean_object* v_kh_3968_, lean_object* v_y_3969_, lean_object* v_stride_3970_, lean_object* v_pad_3971_, lean_object* v_x_3972_, lean_object* v_h_3973_, lean_object* v_w_3974_, lean_object* v_inp_3975_, lean_object* v_i_3976_){
_start:
{
uint8_t v___x_3977_; 
v___x_3977_ = lean_nat_dec_lt(v_i_3976_, v_k_3966_);
if (v___x_3977_ == 0)
{
uint32_t v___x_3978_; 
v___x_3978_ = 1065353216;
return v___x_3978_;
}
else
{
lean_object* v___x_3979_; lean_object* v_dy_3980_; lean_object* v___x_3981_; lean_object* v_yy_3982_; uint8_t v___x_3983_; 
v___x_3979_ = lean_nat_div(v_i_3976_, v_kw_3967_);
v_dy_3980_ = lean_nat_mod(v___x_3979_, v_kh_3968_);
lean_dec(v___x_3979_);
v___x_3981_ = lean_nat_mul(v_y_3969_, v_stride_3970_);
v_yy_3982_ = lean_nat_add(v___x_3981_, v_dy_3980_);
lean_dec(v_dy_3980_);
lean_dec(v___x_3981_);
v___x_3983_ = lean_nat_dec_lt(v_yy_3982_, v_pad_3971_);
if (v___x_3983_ == 0)
{
lean_object* v_dx_3984_; lean_object* v___x_3985_; lean_object* v_xx_3986_; uint8_t v___x_3987_; 
v_dx_3984_ = lean_nat_mod(v_i_3976_, v_kw_3967_);
v___x_3985_ = lean_nat_mul(v_x_3972_, v_stride_3970_);
v_xx_3986_ = lean_nat_add(v___x_3985_, v_dx_3984_);
lean_dec(v_dx_3984_);
lean_dec(v___x_3985_);
v___x_3987_ = lean_nat_dec_lt(v_xx_3986_, v_pad_3971_);
if (v___x_3987_ == 0)
{
lean_object* v___x_3988_; uint8_t v___x_3989_; 
v___x_3988_ = lean_nat_sub(v_yy_3982_, v_pad_3971_);
lean_dec(v_yy_3982_);
v___x_3989_ = lean_nat_dec_le(v_h_3973_, v___x_3988_);
if (v___x_3989_ == 0)
{
lean_object* v___x_3990_; uint8_t v___x_3991_; 
v___x_3990_ = lean_nat_sub(v_xx_3986_, v_pad_3971_);
lean_dec(v_xx_3986_);
v___x_3991_ = lean_nat_dec_le(v_w_3974_, v___x_3990_);
if (v___x_3991_ == 0)
{
lean_object* v___x_3992_; lean_object* v_c_3993_; lean_object* v___x_3994_; lean_object* v___x_3995_; lean_object* v___x_3996_; lean_object* v___x_3997_; lean_object* v___x_3998_; lean_object* v___x_3999_; uint32_t v___x_4000_; 
v___x_3992_ = lean_nat_mul(v_kh_3968_, v_kw_3967_);
v_c_3993_ = lean_nat_div(v_i_3976_, v___x_3992_);
lean_dec(v___x_3992_);
v___x_3994_ = lean_nat_mul(v_c_3993_, v_h_3973_);
lean_dec(v_c_3993_);
v___x_3995_ = lean_nat_add(v___x_3994_, v___x_3988_);
lean_dec(v___x_3988_);
lean_dec(v___x_3994_);
v___x_3996_ = lean_nat_mul(v___x_3995_, v_w_3974_);
lean_dec(v___x_3995_);
v___x_3997_ = lean_nat_add(v___x_3996_, v___x_3990_);
lean_dec(v___x_3990_);
lean_dec(v___x_3996_);
v___x_3998_ = lp_competition_Submission_dotX___lam__0___boxed__const__1;
v___x_3999_ = lean_array_get_borrowed(v___x_3998_, v_inp_3975_, v___x_3997_);
lean_dec(v___x_3997_);
v___x_4000_ = lean_unbox_uint32(v___x_3999_);
return v___x_4000_;
}
else
{
uint32_t v___x_4001_; 
lean_dec(v___x_3990_);
lean_dec(v___x_3988_);
v___x_4001_ = 0;
return v___x_4001_;
}
}
else
{
uint32_t v___x_4002_; 
lean_dec(v___x_3988_);
lean_dec(v_xx_3986_);
v___x_4002_ = 0;
return v___x_4002_;
}
}
else
{
uint32_t v___x_4003_; 
lean_dec(v_xx_3986_);
lean_dec(v_yy_3982_);
v___x_4003_ = 0;
return v___x_4003_;
}
}
else
{
uint32_t v___x_4004_; 
lean_dec(v_yy_3982_);
v___x_4004_ = 0;
return v___x_4004_;
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_ExactRuntime_conv2dWith___at___00Submission_kernels_spec__2___lam__1___boxed(lean_object* v_k_4005_, lean_object* v_kw_4006_, lean_object* v_kh_4007_, lean_object* v_y_4008_, lean_object* v_stride_4009_, lean_object* v_pad_4010_, lean_object* v_x_4011_, lean_object* v_h_4012_, lean_object* v_w_4013_, lean_object* v_inp_4014_, lean_object* v_i_4015_){
_start:
{
uint32_t v_res_4016_; lean_object* v_r_4017_; 
v_res_4016_ = lp_competition_ExactRuntime_conv2dWith___at___00Submission_kernels_spec__2___lam__1(v_k_4005_, v_kw_4006_, v_kh_4007_, v_y_4008_, v_stride_4009_, v_pad_4010_, v_x_4011_, v_h_4012_, v_w_4013_, v_inp_4014_, v_i_4015_);
lean_dec(v_i_4015_);
lean_dec_ref(v_inp_4014_);
lean_dec(v_w_4013_);
lean_dec(v_h_4012_);
lean_dec(v_x_4011_);
lean_dec(v_pad_4010_);
lean_dec(v_stride_4009_);
lean_dec(v_y_4008_);
lean_dec(v_kh_4007_);
lean_dec(v_kw_4006_);
lean_dec(v_k_4005_);
v_r_4017_ = lean_box_uint32(v_res_4016_);
return v_r_4017_;
}
}
LEAN_EXPORT uint32_t lp_competition_ExactRuntime_conv2dWith___at___00Submission_kernels_spec__2___lam__0(lean_object* v_k_4018_, lean_object* v_b_4019_, lean_object* v_o_4020_, lean_object* v_wts_4021_, lean_object* v_i_4022_){
_start:
{
uint8_t v___x_4023_; 
v___x_4023_ = lean_nat_dec_lt(v_i_4022_, v_k_4018_);
if (v___x_4023_ == 0)
{
lean_object* v___x_4024_; lean_object* v___x_4025_; uint32_t v___x_4026_; 
v___x_4024_ = lp_competition_Submission_dotX___lam__0___boxed__const__1;
v___x_4025_ = lean_array_get_borrowed(v___x_4024_, v_b_4019_, v_o_4020_);
v___x_4026_ = lean_unbox_uint32(v___x_4025_);
return v___x_4026_;
}
else
{
lean_object* v___x_4027_; lean_object* v___x_4028_; lean_object* v___x_4029_; lean_object* v___x_4030_; uint32_t v___x_4031_; 
v___x_4027_ = lean_nat_mul(v_o_4020_, v_k_4018_);
v___x_4028_ = lean_nat_add(v___x_4027_, v_i_4022_);
lean_dec(v___x_4027_);
v___x_4029_ = lp_competition_Submission_dotX___lam__0___boxed__const__1;
v___x_4030_ = lean_array_get_borrowed(v___x_4029_, v_wts_4021_, v___x_4028_);
lean_dec(v___x_4028_);
v___x_4031_ = lean_unbox_uint32(v___x_4030_);
return v___x_4031_;
}
}
}
LEAN_EXPORT lean_object* lp_competition_ExactRuntime_conv2dWith___at___00Submission_kernels_spec__2___lam__0___boxed(lean_object* v_k_4032_, lean_object* v_b_4033_, lean_object* v_o_4034_, lean_object* v_wts_4035_, lean_object* v_i_4036_){
_start:
{
uint32_t v_res_4037_; lean_object* v_r_4038_; 
v_res_4037_ = lp_competition_ExactRuntime_conv2dWith___at___00Submission_kernels_spec__2___lam__0(v_k_4032_, v_b_4033_, v_o_4034_, v_wts_4035_, v_i_4036_);
lean_dec(v_i_4036_);
lean_dec_ref(v_wts_4035_);
lean_dec(v_o_4034_);
lean_dec_ref(v_b_4033_);
lean_dec(v_k_4032_);
v_r_4038_ = lean_box_uint32(v_res_4037_);
return v_r_4038_;
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_dotLoop___at___00Submission_rmsnormCached_spec__0___at___00ExactRuntime_conv2dWith___at___00Submission_kernels_spec__2_spec__4(lean_object* v_k_4039_, lean_object* v___x_4040_, lean_object* v___x_4041_, lean_object* v_s_4042_, lean_object* v_y_4043_, lean_object* v_x_4044_, lean_object* v_inp_4045_, lean_object* v_b_4046_, lean_object* v_o_4047_, lean_object* v_wts_4048_, lean_object* v_pos_4049_, lean_object* v_neg_4050_, uint8_t v_sp_4051_, uint8_t v_nz_4052_, lean_object* v_index_4053_, lean_object* v_x_4054_){
_start:
{
lean_object* v_zero_4055_; uint8_t v_isZero_4056_; 
v_zero_4055_ = lean_unsigned_to_nat(0u);
v_isZero_4056_ = lean_nat_dec_eq(v_x_4054_, v_zero_4055_);
if (v_isZero_4056_ == 1)
{
lean_object* v___x_4057_; 
lean_dec(v_x_4054_);
lean_dec(v_index_4053_);
v___x_4057_ = lean_alloc_ctor(0, 2, 2);
lean_ctor_set(v___x_4057_, 0, v_pos_4049_);
lean_ctor_set(v___x_4057_, 1, v_neg_4050_);
lean_ctor_set_uint8(v___x_4057_, sizeof(void*)*2, v_sp_4051_);
lean_ctor_set_uint8(v___x_4057_, sizeof(void*)*2 + 1, v_nz_4052_);
return v___x_4057_;
}
else
{
lean_object* v_one_4058_; lean_object* v_n_4059_; lean_object* v_pos_4061_; lean_object* v_neg_4062_; uint8_t v_special_4063_; uint8_t v_negZero_4064_; uint8_t v___y_4070_; lean_object* v___y_4071_; lean_object* v___y_4072_; lean_object* v___y_4073_; lean_object* v___y_4074_; lean_object* v___y_4084_; lean_object* v___y_4085_; lean_object* v___y_4086_; lean_object* v___y_4087_; lean_object* v___y_4097_; lean_object* v___y_4098_; uint8_t v___y_4099_; lean_object* v___y_4146_; lean_object* v___y_4147_; uint8_t v___y_4150_; uint8_t v___y_4151_; lean_object* v___y_4152_; lean_object* v___y_4153_; uint8_t v___y_4154_; uint8_t v___y_4156_; uint32_t v___y_4157_; lean_object* v___y_4158_; lean_object* v___y_4159_; uint8_t v___y_4160_; lean_object* v___y_4167_; uint8_t v___y_4168_; uint32_t v___y_4169_; uint32_t v___y_4170_; lean_object* v___y_4171_; lean_object* v___y_4172_; uint8_t v___y_4180_; uint32_t v___y_4181_; uint32_t v___y_4182_; uint32_t v___y_4183_; lean_object* v___y_4184_; uint32_t v___y_4185_; lean_object* v___y_4186_; uint8_t v___y_4194_; uint32_t v___y_4195_; uint32_t v___y_4196_; uint32_t v___y_4197_; uint32_t v___y_4198_; uint32_t v___y_4199_; lean_object* v___y_4200_; lean_object* v___y_4201_; uint8_t v___y_4208_; uint32_t v___y_4209_; uint32_t v___y_4210_; uint32_t v___y_4211_; uint32_t v___y_4212_; uint32_t v___y_4213_; lean_object* v___y_4214_; uint8_t v___y_4228_; uint32_t v___y_4229_; uint32_t v___y_4230_; uint32_t v___y_4231_; uint32_t v___y_4232_; uint32_t v___y_4233_; uint32_t v___y_4248_; uint8_t v___x_4263_; 
v_one_4058_ = lean_unsigned_to_nat(1u);
v_n_4059_ = lean_nat_sub(v_x_4054_, v_one_4058_);
lean_dec(v_x_4054_);
v___x_4263_ = lean_nat_dec_lt(v_index_4053_, v_k_4039_);
if (v___x_4263_ == 0)
{
uint32_t v___x_4264_; 
v___x_4264_ = 1065353216;
v___y_4248_ = v___x_4264_;
goto v___jp_4247_;
}
else
{
lean_object* v_h_4265_; lean_object* v_w_4266_; lean_object* v_stride_4267_; lean_object* v_pad_4268_; lean_object* v___x_4269_; lean_object* v_dy_4270_; lean_object* v___x_4271_; lean_object* v_yy_4272_; uint8_t v___x_4273_; 
v_h_4265_ = lean_ctor_get(v_s_4042_, 1);
v_w_4266_ = lean_ctor_get(v_s_4042_, 2);
v_stride_4267_ = lean_ctor_get(v_s_4042_, 6);
v_pad_4268_ = lean_ctor_get(v_s_4042_, 7);
v___x_4269_ = lean_nat_div(v_index_4053_, v___x_4040_);
v_dy_4270_ = lean_nat_mod(v___x_4269_, v___x_4041_);
lean_dec(v___x_4269_);
v___x_4271_ = lean_nat_mul(v_y_4043_, v_stride_4267_);
v_yy_4272_ = lean_nat_add(v___x_4271_, v_dy_4270_);
lean_dec(v_dy_4270_);
lean_dec(v___x_4271_);
v___x_4273_ = lean_nat_dec_lt(v_yy_4272_, v_pad_4268_);
if (v___x_4273_ == 0)
{
lean_object* v_dx_4274_; lean_object* v___x_4275_; lean_object* v_xx_4276_; uint8_t v___x_4277_; 
v_dx_4274_ = lean_nat_mod(v_index_4053_, v___x_4040_);
v___x_4275_ = lean_nat_mul(v_x_4044_, v_stride_4267_);
v_xx_4276_ = lean_nat_add(v___x_4275_, v_dx_4274_);
lean_dec(v_dx_4274_);
lean_dec(v___x_4275_);
v___x_4277_ = lean_nat_dec_lt(v_xx_4276_, v_pad_4268_);
if (v___x_4277_ == 0)
{
lean_object* v___x_4278_; uint8_t v___x_4279_; 
v___x_4278_ = lean_nat_sub(v_yy_4272_, v_pad_4268_);
lean_dec(v_yy_4272_);
v___x_4279_ = lean_nat_dec_le(v_h_4265_, v___x_4278_);
if (v___x_4279_ == 0)
{
lean_object* v___x_4280_; uint8_t v___x_4281_; 
v___x_4280_ = lean_nat_sub(v_xx_4276_, v_pad_4268_);
lean_dec(v_xx_4276_);
v___x_4281_ = lean_nat_dec_le(v_w_4266_, v___x_4280_);
if (v___x_4281_ == 0)
{
lean_object* v___x_4282_; lean_object* v_c_4283_; lean_object* v___x_4284_; lean_object* v___x_4285_; lean_object* v___x_4286_; lean_object* v___x_4287_; lean_object* v___x_4288_; lean_object* v___x_4289_; uint32_t v___x_4290_; 
v___x_4282_ = lean_nat_mul(v___x_4041_, v___x_4040_);
v_c_4283_ = lean_nat_div(v_index_4053_, v___x_4282_);
lean_dec(v___x_4282_);
v___x_4284_ = lean_nat_mul(v_c_4283_, v_h_4265_);
lean_dec(v_c_4283_);
v___x_4285_ = lean_nat_add(v___x_4284_, v___x_4278_);
lean_dec(v___x_4278_);
lean_dec(v___x_4284_);
v___x_4286_ = lean_nat_mul(v___x_4285_, v_w_4266_);
lean_dec(v___x_4285_);
v___x_4287_ = lean_nat_add(v___x_4286_, v___x_4280_);
lean_dec(v___x_4280_);
lean_dec(v___x_4286_);
v___x_4288_ = lp_competition_Submission_dotX___lam__0___boxed__const__1;
v___x_4289_ = lean_array_get_borrowed(v___x_4288_, v_inp_4045_, v___x_4287_);
lean_dec(v___x_4287_);
v___x_4290_ = lean_unbox_uint32(v___x_4289_);
v___y_4248_ = v___x_4290_;
goto v___jp_4247_;
}
else
{
uint32_t v___x_4291_; 
lean_dec(v___x_4280_);
lean_dec(v___x_4278_);
v___x_4291_ = 0;
v___y_4248_ = v___x_4291_;
goto v___jp_4247_;
}
}
else
{
uint32_t v___x_4292_; 
lean_dec(v___x_4278_);
lean_dec(v_xx_4276_);
v___x_4292_ = 0;
v___y_4248_ = v___x_4292_;
goto v___jp_4247_;
}
}
else
{
uint32_t v___x_4293_; 
lean_dec(v_xx_4276_);
lean_dec(v_yy_4272_);
v___x_4293_ = 0;
v___y_4248_ = v___x_4293_;
goto v___jp_4247_;
}
}
else
{
uint32_t v___x_4294_; 
lean_dec(v_yy_4272_);
v___x_4294_ = 0;
v___y_4248_ = v___x_4294_;
goto v___jp_4247_;
}
}
v___jp_4060_:
{
lean_object* v___x_4065_; 
v___x_4065_ = lean_nat_add(v_index_4053_, v_one_4058_);
lean_dec(v_index_4053_);
v_pos_4049_ = v_pos_4061_;
v_neg_4050_ = v_neg_4062_;
v_sp_4051_ = v_special_4063_;
v_nz_4052_ = v_negZero_4064_;
v_index_4053_ = v___x_4065_;
v_x_4054_ = v_n_4059_;
goto _start;
}
v___jp_4067_:
{
uint8_t v___x_4068_; 
v___x_4068_ = 1;
v_pos_4061_ = v_pos_4049_;
v_neg_4062_ = v_neg_4050_;
v_special_4063_ = v___x_4068_;
v_negZero_4064_ = v_nz_4052_;
goto v___jp_4060_;
}
v___jp_4069_:
{
lean_object* v___x_4075_; lean_object* v___x_4076_; uint8_t v___x_4077_; 
v___x_4075_ = lean_nat_add(v___y_4071_, v___y_4073_);
lean_dec(v___y_4071_);
v___x_4076_ = lean_array_get_size(v___y_4074_);
v___x_4077_ = lean_nat_dec_lt(v___x_4075_, v___x_4076_);
if (v___x_4077_ == 0)
{
lean_dec(v___x_4075_);
lean_dec(v___y_4072_);
v_pos_4061_ = v___y_4074_;
v_neg_4062_ = v_neg_4050_;
v_special_4063_ = v_sp_4051_;
v_negZero_4064_ = v___y_4070_;
goto v___jp_4060_;
}
else
{
lean_object* v_v_4078_; lean_object* v___x_4079_; lean_object* v_xs_x27_4080_; lean_object* v___x_4081_; lean_object* v___x_4082_; 
v_v_4078_ = lean_array_fget(v___y_4074_, v___x_4075_);
v___x_4079_ = lean_box(0);
v_xs_x27_4080_ = lean_array_fset(v___y_4074_, v___x_4075_, v___x_4079_);
v___x_4081_ = lean_nat_add(v_v_4078_, v___y_4072_);
lean_dec(v___y_4072_);
lean_dec(v_v_4078_);
v___x_4082_ = lean_array_fset(v_xs_x27_4080_, v___x_4075_, v___x_4081_);
lean_dec(v___x_4075_);
v_pos_4061_ = v___x_4082_;
v_neg_4062_ = v_neg_4050_;
v_special_4063_ = v_sp_4051_;
v_negZero_4064_ = v___y_4070_;
goto v___jp_4060_;
}
}
v___jp_4083_:
{
lean_object* v___x_4088_; lean_object* v___x_4089_; uint8_t v___x_4090_; 
v___x_4088_ = lean_nat_add(v___y_4084_, v___y_4086_);
lean_dec(v___y_4084_);
v___x_4089_ = lean_array_get_size(v___y_4087_);
v___x_4090_ = lean_nat_dec_lt(v___x_4088_, v___x_4089_);
if (v___x_4090_ == 0)
{
lean_dec(v___x_4088_);
lean_dec(v___y_4085_);
v_pos_4061_ = v_pos_4049_;
v_neg_4062_ = v___y_4087_;
v_special_4063_ = v_sp_4051_;
v_negZero_4064_ = v_isZero_4056_;
goto v___jp_4060_;
}
else
{
lean_object* v_v_4091_; lean_object* v___x_4092_; lean_object* v_xs_x27_4093_; lean_object* v___x_4094_; lean_object* v___x_4095_; 
v_v_4091_ = lean_array_fget(v___y_4087_, v___x_4088_);
v___x_4092_ = lean_box(0);
v_xs_x27_4093_ = lean_array_fset(v___y_4087_, v___x_4088_, v___x_4092_);
v___x_4094_ = lean_nat_add(v_v_4091_, v___y_4085_);
lean_dec(v___y_4085_);
lean_dec(v_v_4091_);
v___x_4095_ = lean_array_fset(v_xs_x27_4093_, v___x_4088_, v___x_4094_);
lean_dec(v___x_4088_);
v_pos_4061_ = v_pos_4049_;
v_neg_4062_ = v___x_4095_;
v_special_4063_ = v_sp_4051_;
v_negZero_4064_ = v_isZero_4056_;
goto v___jp_4060_;
}
}
v___jp_4096_:
{
uint8_t v___x_4100_; 
v___x_4100_ = lean_nat_dec_eq(v___y_4098_, v_zero_4055_);
if (v___x_4100_ == 0)
{
if (v___y_4099_ == 0)
{
uint64_t v___x_4101_; lean_object* v___x_4102_; lean_object* v___x_4103_; lean_object* v_l_4104_; lean_object* v___x_4105_; uint64_t v_r_4106_; uint64_t v___x_4107_; uint64_t v___x_4108_; uint64_t v___x_4109_; uint64_t v___x_4110_; uint64_t v___x_4111_; uint64_t v___x_4112_; lean_object* v_hi_4113_; lean_object* v___x_4114_; uint8_t v___x_4115_; 
v___x_4101_ = lean_uint64_of_nat(v___y_4098_);
lean_dec(v___y_4098_);
v___x_4102_ = lean_unsigned_to_nat(32u);
v___x_4103_ = lean_unsigned_to_nat(5u);
v_l_4104_ = lean_nat_shiftr(v___y_4097_, v___x_4103_);
v___x_4105_ = lean_nat_mod(v___y_4097_, v___x_4102_);
lean_dec(v___y_4097_);
v_r_4106_ = lean_uint64_of_nat(v___x_4105_);
lean_dec(v___x_4105_);
v___x_4107_ = 1ULL;
v___x_4108_ = 32ULL;
v___x_4109_ = lean_uint64_sub(v___x_4108_, v_r_4106_);
v___x_4110_ = lean_uint64_shift_left(v___x_4107_, v___x_4109_);
v___x_4111_ = lean_uint64_mod(v___x_4101_, v___x_4110_);
v___x_4112_ = lean_uint64_shift_right(v___x_4101_, v___x_4109_);
v_hi_4113_ = lean_uint64_to_nat(v___x_4112_);
v___x_4114_ = lean_array_get_size(v_pos_4049_);
v___x_4115_ = lean_nat_dec_lt(v_l_4104_, v___x_4114_);
if (v___x_4115_ == 0)
{
v___y_4070_ = v___y_4099_;
v___y_4071_ = v_l_4104_;
v___y_4072_ = v_hi_4113_;
v___y_4073_ = v_one_4058_;
v___y_4074_ = v_pos_4049_;
goto v___jp_4069_;
}
else
{
uint64_t v___x_4116_; lean_object* v_lo_4117_; lean_object* v_v_4118_; lean_object* v___x_4119_; lean_object* v_xs_x27_4120_; lean_object* v___x_4121_; lean_object* v___x_4122_; 
v___x_4116_ = lean_uint64_shift_left(v___x_4111_, v_r_4106_);
v_lo_4117_ = lean_uint64_to_nat(v___x_4116_);
v_v_4118_ = lean_array_fget(v_pos_4049_, v_l_4104_);
v___x_4119_ = lean_box(0);
v_xs_x27_4120_ = lean_array_fset(v_pos_4049_, v_l_4104_, v___x_4119_);
v___x_4121_ = lean_nat_add(v_v_4118_, v_lo_4117_);
lean_dec(v_lo_4117_);
lean_dec(v_v_4118_);
v___x_4122_ = lean_array_fset(v_xs_x27_4120_, v_l_4104_, v___x_4121_);
v___y_4070_ = v___y_4099_;
v___y_4071_ = v_l_4104_;
v___y_4072_ = v_hi_4113_;
v___y_4073_ = v_one_4058_;
v___y_4074_ = v___x_4122_;
goto v___jp_4069_;
}
}
else
{
uint64_t v___x_4123_; lean_object* v___x_4124_; lean_object* v___x_4125_; lean_object* v_l_4126_; lean_object* v___x_4127_; uint64_t v_r_4128_; uint64_t v___x_4129_; uint64_t v___x_4130_; uint64_t v___x_4131_; uint64_t v___x_4132_; uint64_t v___x_4133_; uint64_t v___x_4134_; lean_object* v_hi_4135_; lean_object* v___x_4136_; uint8_t v___x_4137_; 
v___x_4123_ = lean_uint64_of_nat(v___y_4098_);
lean_dec(v___y_4098_);
v___x_4124_ = lean_unsigned_to_nat(32u);
v___x_4125_ = lean_unsigned_to_nat(5u);
v_l_4126_ = lean_nat_shiftr(v___y_4097_, v___x_4125_);
v___x_4127_ = lean_nat_mod(v___y_4097_, v___x_4124_);
lean_dec(v___y_4097_);
v_r_4128_ = lean_uint64_of_nat(v___x_4127_);
lean_dec(v___x_4127_);
v___x_4129_ = 1ULL;
v___x_4130_ = 32ULL;
v___x_4131_ = lean_uint64_sub(v___x_4130_, v_r_4128_);
v___x_4132_ = lean_uint64_shift_left(v___x_4129_, v___x_4131_);
v___x_4133_ = lean_uint64_mod(v___x_4123_, v___x_4132_);
v___x_4134_ = lean_uint64_shift_right(v___x_4123_, v___x_4131_);
v_hi_4135_ = lean_uint64_to_nat(v___x_4134_);
v___x_4136_ = lean_array_get_size(v_neg_4050_);
v___x_4137_ = lean_nat_dec_lt(v_l_4126_, v___x_4136_);
if (v___x_4137_ == 0)
{
v___y_4084_ = v_l_4126_;
v___y_4085_ = v_hi_4135_;
v___y_4086_ = v_one_4058_;
v___y_4087_ = v_neg_4050_;
goto v___jp_4083_;
}
else
{
uint64_t v___x_4138_; lean_object* v_lo_4139_; lean_object* v_v_4140_; lean_object* v___x_4141_; lean_object* v_xs_x27_4142_; lean_object* v___x_4143_; lean_object* v___x_4144_; 
v___x_4138_ = lean_uint64_shift_left(v___x_4133_, v_r_4128_);
v_lo_4139_ = lean_uint64_to_nat(v___x_4138_);
v_v_4140_ = lean_array_fget(v_neg_4050_, v_l_4126_);
v___x_4141_ = lean_box(0);
v_xs_x27_4142_ = lean_array_fset(v_neg_4050_, v_l_4126_, v___x_4141_);
v___x_4143_ = lean_nat_add(v_v_4140_, v_lo_4139_);
lean_dec(v_lo_4139_);
lean_dec(v_v_4140_);
v___x_4144_ = lean_array_fset(v_xs_x27_4142_, v_l_4126_, v___x_4143_);
v___y_4084_ = v_l_4126_;
v___y_4085_ = v_hi_4135_;
v___y_4086_ = v_one_4058_;
v___y_4087_ = v___x_4144_;
goto v___jp_4083_;
}
}
}
else
{
lean_dec(v___y_4098_);
lean_dec(v___y_4097_);
if (v_nz_4052_ == 0)
{
v_pos_4061_ = v_pos_4049_;
v_neg_4062_ = v_neg_4050_;
v_special_4063_ = v_sp_4051_;
v_negZero_4064_ = v_nz_4052_;
goto v___jp_4060_;
}
else
{
v_pos_4061_ = v_pos_4049_;
v_neg_4062_ = v_neg_4050_;
v_special_4063_ = v_sp_4051_;
v_negZero_4064_ = v___y_4099_;
goto v___jp_4060_;
}
}
}
v___jp_4145_:
{
uint8_t v___x_4148_; 
v___x_4148_ = 1;
v___y_4097_ = v___y_4147_;
v___y_4098_ = v___y_4146_;
v___y_4099_ = v___x_4148_;
goto v___jp_4096_;
}
v___jp_4149_:
{
if (v___y_4151_ == 0)
{
if (v___y_4154_ == 0)
{
v___y_4097_ = v___y_4153_;
v___y_4098_ = v___y_4152_;
v___y_4099_ = v___y_4150_;
goto v___jp_4096_;
}
else
{
v___y_4146_ = v___y_4152_;
v___y_4147_ = v___y_4153_;
goto v___jp_4145_;
}
}
else
{
if (v___y_4154_ == 0)
{
v___y_4146_ = v___y_4152_;
v___y_4147_ = v___y_4153_;
goto v___jp_4145_;
}
else
{
v___y_4097_ = v___y_4153_;
v___y_4098_ = v___y_4152_;
v___y_4099_ = v___y_4150_;
goto v___jp_4096_;
}
}
}
v___jp_4155_:
{
uint32_t v___x_4161_; uint32_t v___x_4162_; uint32_t v___x_4163_; uint8_t v___x_4164_; 
v___x_4161_ = 2147483648;
v___x_4162_ = lean_uint32_land(v___y_4157_, v___x_4161_);
v___x_4163_ = 0;
v___x_4164_ = lean_uint32_dec_eq(v___x_4162_, v___x_4163_);
if (v___x_4164_ == 0)
{
uint8_t v___x_4165_; 
v___x_4165_ = 1;
v___y_4150_ = v___y_4156_;
v___y_4151_ = v___y_4160_;
v___y_4152_ = v___y_4159_;
v___y_4153_ = v___y_4158_;
v___y_4154_ = v___x_4165_;
goto v___jp_4149_;
}
else
{
v___y_4150_ = v___y_4156_;
v___y_4151_ = v___y_4160_;
v___y_4152_ = v___y_4159_;
v___y_4153_ = v___y_4158_;
v___y_4154_ = v___y_4156_;
goto v___jp_4149_;
}
}
v___jp_4166_:
{
lean_object* v___x_4173_; uint32_t v___x_4174_; uint32_t v___x_4175_; uint32_t v___x_4176_; uint8_t v___x_4177_; 
v___x_4173_ = lean_nat_add(v___y_4167_, v___y_4172_);
lean_dec(v___y_4172_);
lean_dec(v___y_4167_);
v___x_4174_ = 2147483648;
v___x_4175_ = lean_uint32_land(v___y_4169_, v___x_4174_);
v___x_4176_ = 0;
v___x_4177_ = lean_uint32_dec_eq(v___x_4175_, v___x_4176_);
if (v___x_4177_ == 0)
{
uint8_t v___x_4178_; 
v___x_4178_ = 1;
v___y_4156_ = v___y_4168_;
v___y_4157_ = v___y_4170_;
v___y_4158_ = v___x_4173_;
v___y_4159_ = v___y_4171_;
v___y_4160_ = v___x_4178_;
goto v___jp_4155_;
}
else
{
v___y_4156_ = v___y_4168_;
v___y_4157_ = v___y_4170_;
v___y_4158_ = v___x_4173_;
v___y_4159_ = v___y_4171_;
v___y_4160_ = v___y_4168_;
goto v___jp_4155_;
}
}
v___jp_4179_:
{
uint32_t v___x_4187_; uint32_t v___x_4188_; uint32_t v___x_4189_; uint8_t v___x_4190_; 
v___x_4187_ = lean_uint32_shift_right(v___y_4182_, v___y_4181_);
v___x_4188_ = lean_uint32_land(v___x_4187_, v___y_4185_);
v___x_4189_ = 0;
v___x_4190_ = lean_uint32_dec_eq(v___x_4188_, v___x_4189_);
if (v___x_4190_ == 0)
{
lean_object* v___x_4191_; lean_object* v___x_4192_; 
v___x_4191_ = lean_uint32_to_nat(v___x_4188_);
v___x_4192_ = lean_nat_sub(v___x_4191_, v_one_4058_);
lean_dec(v___x_4191_);
v___y_4167_ = v___y_4186_;
v___y_4168_ = v___y_4180_;
v___y_4169_ = v___y_4183_;
v___y_4170_ = v___y_4182_;
v___y_4171_ = v___y_4184_;
v___y_4172_ = v___x_4192_;
goto v___jp_4166_;
}
else
{
v___y_4167_ = v___y_4186_;
v___y_4168_ = v___y_4180_;
v___y_4169_ = v___y_4183_;
v___y_4170_ = v___y_4182_;
v___y_4171_ = v___y_4184_;
v___y_4172_ = v_zero_4055_;
goto v___jp_4166_;
}
}
v___jp_4193_:
{
lean_object* v___x_4202_; uint32_t v___x_4203_; uint8_t v___x_4204_; 
v___x_4202_ = lean_nat_mul(v___y_4200_, v___y_4201_);
lean_dec(v___y_4201_);
lean_dec(v___y_4200_);
v___x_4203_ = 0;
v___x_4204_ = lean_uint32_dec_eq(v___y_4198_, v___x_4203_);
if (v___x_4204_ == 0)
{
lean_object* v___x_4205_; lean_object* v___x_4206_; 
v___x_4205_ = lean_uint32_to_nat(v___y_4198_);
v___x_4206_ = lean_nat_sub(v___x_4205_, v_one_4058_);
lean_dec(v___x_4205_);
v___y_4180_ = v___y_4194_;
v___y_4181_ = v___y_4197_;
v___y_4182_ = v___y_4196_;
v___y_4183_ = v___y_4195_;
v___y_4184_ = v___x_4202_;
v___y_4185_ = v___y_4199_;
v___y_4186_ = v___x_4206_;
goto v___jp_4179_;
}
else
{
v___y_4180_ = v___y_4194_;
v___y_4181_ = v___y_4197_;
v___y_4182_ = v___y_4196_;
v___y_4183_ = v___y_4195_;
v___y_4184_ = v___x_4202_;
v___y_4185_ = v___y_4199_;
v___y_4186_ = v_zero_4055_;
goto v___jp_4179_;
}
}
v___jp_4207_:
{
uint32_t v___x_4215_; uint32_t v___x_4216_; uint32_t v___x_4217_; uint8_t v___x_4218_; 
v___x_4215_ = lean_uint32_shift_right(v___y_4210_, v___y_4209_);
v___x_4216_ = lean_uint32_land(v___x_4215_, v___y_4213_);
v___x_4217_ = 0;
v___x_4218_ = lean_uint32_dec_eq(v___x_4216_, v___x_4217_);
if (v___x_4218_ == 0)
{
lean_object* v___x_4219_; uint32_t v___x_4220_; uint32_t v___x_4221_; lean_object* v___x_4222_; lean_object* v___x_4223_; 
v___x_4219_ = lean_unsigned_to_nat(8388608u);
v___x_4220_ = 8388607;
v___x_4221_ = lean_uint32_land(v___y_4210_, v___x_4220_);
v___x_4222_ = lean_uint32_to_nat(v___x_4221_);
v___x_4223_ = lean_nat_add(v___x_4219_, v___x_4222_);
lean_dec(v___x_4222_);
v___y_4194_ = v___y_4208_;
v___y_4195_ = v___y_4211_;
v___y_4196_ = v___y_4210_;
v___y_4197_ = v___y_4209_;
v___y_4198_ = v___y_4212_;
v___y_4199_ = v___y_4213_;
v___y_4200_ = v___y_4214_;
v___y_4201_ = v___x_4223_;
goto v___jp_4193_;
}
else
{
uint32_t v___x_4224_; uint32_t v___x_4225_; lean_object* v___x_4226_; 
v___x_4224_ = 8388607;
v___x_4225_ = lean_uint32_land(v___y_4210_, v___x_4224_);
v___x_4226_ = lean_uint32_to_nat(v___x_4225_);
v___y_4194_ = v___y_4208_;
v___y_4195_ = v___y_4211_;
v___y_4196_ = v___y_4210_;
v___y_4197_ = v___y_4209_;
v___y_4198_ = v___y_4212_;
v___y_4199_ = v___y_4213_;
v___y_4200_ = v___y_4214_;
v___y_4201_ = v___x_4226_;
goto v___jp_4193_;
}
}
v___jp_4227_:
{
uint32_t v___x_4234_; uint32_t v___x_4235_; uint8_t v___x_4236_; 
v___x_4234_ = lean_uint32_shift_right(v___y_4233_, v___y_4230_);
v___x_4235_ = lean_uint32_land(v___x_4234_, v___y_4232_);
v___x_4236_ = lean_uint32_dec_eq(v___x_4235_, v___y_4232_);
if (v___x_4236_ == 0)
{
uint32_t v___x_4237_; uint8_t v___x_4238_; 
v___x_4237_ = 0;
v___x_4238_ = lean_uint32_dec_eq(v___y_4231_, v___x_4237_);
if (v___x_4238_ == 0)
{
lean_object* v___x_4239_; uint32_t v___x_4240_; uint32_t v___x_4241_; lean_object* v___x_4242_; lean_object* v___x_4243_; 
v___x_4239_ = lean_unsigned_to_nat(8388608u);
v___x_4240_ = 8388607;
v___x_4241_ = lean_uint32_land(v___y_4229_, v___x_4240_);
v___x_4242_ = lean_uint32_to_nat(v___x_4241_);
v___x_4243_ = lean_nat_add(v___x_4239_, v___x_4242_);
lean_dec(v___x_4242_);
v___y_4208_ = v___y_4228_;
v___y_4209_ = v___y_4230_;
v___y_4210_ = v___y_4233_;
v___y_4211_ = v___y_4229_;
v___y_4212_ = v___y_4231_;
v___y_4213_ = v___y_4232_;
v___y_4214_ = v___x_4243_;
goto v___jp_4207_;
}
else
{
uint32_t v___x_4244_; uint32_t v___x_4245_; lean_object* v___x_4246_; 
v___x_4244_ = 8388607;
v___x_4245_ = lean_uint32_land(v___y_4229_, v___x_4244_);
v___x_4246_ = lean_uint32_to_nat(v___x_4245_);
v___y_4208_ = v___y_4228_;
v___y_4209_ = v___y_4230_;
v___y_4210_ = v___y_4233_;
v___y_4211_ = v___y_4229_;
v___y_4212_ = v___y_4231_;
v___y_4213_ = v___y_4232_;
v___y_4214_ = v___x_4246_;
goto v___jp_4207_;
}
}
else
{
goto v___jp_4067_;
}
}
v___jp_4247_:
{
uint32_t v___x_4249_; uint32_t v___x_4250_; uint32_t v___x_4251_; uint32_t v___x_4252_; uint8_t v___x_4253_; 
v___x_4249_ = 23;
v___x_4250_ = lean_uint32_shift_right(v___y_4248_, v___x_4249_);
v___x_4251_ = 255;
v___x_4252_ = lean_uint32_land(v___x_4250_, v___x_4251_);
v___x_4253_ = lean_uint32_dec_eq(v___x_4252_, v___x_4251_);
if (v___x_4253_ == 0)
{
uint8_t v___x_4254_; 
v___x_4254_ = lean_nat_dec_lt(v_index_4053_, v_k_4039_);
if (v___x_4254_ == 0)
{
lean_object* v___x_4255_; lean_object* v___x_4256_; uint32_t v___x_4257_; 
v___x_4255_ = lp_competition_Submission_dotX___lam__0___boxed__const__1;
v___x_4256_ = lean_array_get_borrowed(v___x_4255_, v_b_4046_, v_o_4047_);
v___x_4257_ = lean_unbox_uint32(v___x_4256_);
v___y_4228_ = v___x_4253_;
v___y_4229_ = v___y_4248_;
v___y_4230_ = v___x_4249_;
v___y_4231_ = v___x_4252_;
v___y_4232_ = v___x_4251_;
v___y_4233_ = v___x_4257_;
goto v___jp_4227_;
}
else
{
lean_object* v___x_4258_; lean_object* v___x_4259_; lean_object* v___x_4260_; lean_object* v___x_4261_; uint32_t v___x_4262_; 
v___x_4258_ = lean_nat_mul(v_o_4047_, v_k_4039_);
v___x_4259_ = lean_nat_add(v___x_4258_, v_index_4053_);
lean_dec(v___x_4258_);
v___x_4260_ = lp_competition_Submission_dotX___lam__0___boxed__const__1;
v___x_4261_ = lean_array_get_borrowed(v___x_4260_, v_wts_4048_, v___x_4259_);
lean_dec(v___x_4259_);
v___x_4262_ = lean_unbox_uint32(v___x_4261_);
v___y_4228_ = v___x_4253_;
v___y_4229_ = v___y_4248_;
v___y_4230_ = v___x_4249_;
v___y_4231_ = v___x_4252_;
v___y_4232_ = v___x_4251_;
v___y_4233_ = v___x_4262_;
goto v___jp_4227_;
}
}
else
{
goto v___jp_4067_;
}
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_dotLoop___at___00Submission_rmsnormCached_spec__0___at___00ExactRuntime_conv2dWith___at___00Submission_kernels_spec__2_spec__4___boxed(lean_object* v_k_4295_, lean_object* v___x_4296_, lean_object* v___x_4297_, lean_object* v_s_4298_, lean_object* v_y_4299_, lean_object* v_x_4300_, lean_object* v_inp_4301_, lean_object* v_b_4302_, lean_object* v_o_4303_, lean_object* v_wts_4304_, lean_object* v_pos_4305_, lean_object* v_neg_4306_, lean_object* v_sp_4307_, lean_object* v_nz_4308_, lean_object* v_index_4309_, lean_object* v_x_4310_){
_start:
{
uint8_t v_sp_boxed_4311_; uint8_t v_nz_boxed_4312_; lean_object* v_res_4313_; 
v_sp_boxed_4311_ = lean_unbox(v_sp_4307_);
v_nz_boxed_4312_ = lean_unbox(v_nz_4308_);
v_res_4313_ = lp_competition_Submission_dotLoop___at___00Submission_rmsnormCached_spec__0___at___00ExactRuntime_conv2dWith___at___00Submission_kernels_spec__2_spec__4(v_k_4295_, v___x_4296_, v___x_4297_, v_s_4298_, v_y_4299_, v_x_4300_, v_inp_4301_, v_b_4302_, v_o_4303_, v_wts_4304_, v_pos_4305_, v_neg_4306_, v_sp_boxed_4311_, v_nz_boxed_4312_, v_index_4309_, v_x_4310_);
lean_dec_ref(v_wts_4304_);
lean_dec(v_o_4303_);
lean_dec_ref(v_b_4302_);
lean_dec_ref(v_inp_4301_);
lean_dec(v_x_4300_);
lean_dec(v_y_4299_);
lean_dec_ref(v_s_4298_);
lean_dec(v___x_4297_);
lean_dec(v___x_4296_);
lean_dec(v_k_4295_);
return v_res_4313_;
}
}
LEAN_EXPORT uint32_t lp_competition_ExactRuntime_conv2dWith___at___00Submission_kernels_spec__2___lam__2(lean_object* v___x_4314_, lean_object* v___x_4315_, lean_object* v___x_4316_, lean_object* v_k_4317_, lean_object* v_kw_4318_, lean_object* v_kh_4319_, lean_object* v_s_4320_, lean_object* v_inp_4321_, lean_object* v_b_4322_, lean_object* v_wts_4323_, uint8_t v_relu_4324_, lean_object* v_stride_4325_, lean_object* v_pad_4326_, lean_object* v_h_4327_, lean_object* v_w_4328_, lean_object* v_q_4329_){
_start:
{
uint32_t v___y_4331_; lean_object* v_o_4344_; lean_object* v___x_4345_; lean_object* v_y_4346_; lean_object* v_x_4347_; lean_object* v___x_4348_; lean_object* v___x_4349_; lean_object* v___x_4350_; lean_object* v___x_4351_; uint8_t v___x_4352_; uint8_t v___x_4353_; lean_object* v_acc_4354_; uint8_t v_special_4355_; 
v_o_4344_ = lean_nat_div(v_q_4329_, v___x_4314_);
v___x_4345_ = lean_nat_div(v_q_4329_, v___x_4315_);
v_y_4346_ = lean_nat_mod(v___x_4345_, v___x_4316_);
lean_dec(v___x_4345_);
v_x_4347_ = lean_nat_mod(v_q_4329_, v___x_4315_);
v___x_4348_ = lean_unsigned_to_nat(1u);
v___x_4349_ = lean_nat_add(v_k_4317_, v___x_4348_);
v___x_4350_ = lean_unsigned_to_nat(0u);
v___x_4351_ = lean_obj_once(&lp_competition_Submission_Acc_empty___closed__0, &lp_competition_Submission_Acc_empty___closed__0_once, _init_lp_competition_Submission_Acc_empty___closed__0);
v___x_4352_ = 0;
v___x_4353_ = 1;
lean_inc(v___x_4349_);
v_acc_4354_ = lp_competition_Submission_dotLoop___at___00Submission_rmsnormCached_spec__0___at___00ExactRuntime_conv2dWith___at___00Submission_kernels_spec__2_spec__4(v_k_4317_, v_kw_4318_, v_kh_4319_, v_s_4320_, v_y_4346_, v_x_4347_, v_inp_4321_, v_b_4322_, v_o_4344_, v_wts_4323_, v___x_4351_, v___x_4351_, v___x_4352_, v___x_4353_, v___x_4350_, v___x_4349_);
v_special_4355_ = lean_ctor_get_uint8(v_acc_4354_, sizeof(void*)*2);
if (v_special_4355_ == 0)
{
lean_object* v_pos_4356_; lean_object* v_neg_4357_; uint8_t v_negZero_4358_; lean_object* v___x_4359_; uint8_t v___x_4360_; 
lean_dec(v_x_4347_);
lean_dec(v_y_4346_);
lean_dec(v_o_4344_);
lean_dec(v_w_4328_);
lean_dec(v_h_4327_);
lean_dec(v_pad_4326_);
lean_dec(v_stride_4325_);
lean_dec_ref(v_wts_4323_);
lean_dec_ref(v_b_4322_);
lean_dec_ref(v_inp_4321_);
lean_dec(v_kh_4319_);
lean_dec(v_kw_4318_);
lean_dec(v_k_4317_);
v_pos_4356_ = lean_ctor_get(v_acc_4354_, 0);
lean_inc_ref(v_pos_4356_);
v_neg_4357_ = lean_ctor_get(v_acc_4354_, 1);
lean_inc_ref(v_neg_4357_);
v_negZero_4358_ = lean_ctor_get_uint8(v_acc_4354_, sizeof(void*)*2 + 1);
lean_dec_ref(v_acc_4354_);
v___x_4359_ = lean_obj_once(&lp_competition_Submission_dotFn___closed__1, &lp_competition_Submission_dotFn___closed__1_once, _init_lp_competition_Submission_dotFn___closed__1);
v___x_4360_ = lean_nat_dec_eq(v___x_4349_, v___x_4350_);
lean_dec(v___x_4349_);
if (v___x_4360_ == 0)
{
uint32_t v___x_4361_; 
v___x_4361_ = lp_competition_Submission_finishFast(v_pos_4356_, v_neg_4357_, v___x_4359_, v_negZero_4358_);
lean_dec_ref(v_neg_4357_);
lean_dec_ref(v_pos_4356_);
v___y_4331_ = v___x_4361_;
goto v___jp_4330_;
}
else
{
uint32_t v___x_4362_; 
v___x_4362_ = lp_competition_Submission_finishFast(v_pos_4356_, v_neg_4357_, v___x_4359_, v___x_4352_);
lean_dec_ref(v_neg_4357_);
lean_dec_ref(v_pos_4356_);
v___y_4331_ = v___x_4362_;
goto v___jp_4330_;
}
}
else
{
lean_object* v___f_4363_; lean_object* v___f_4364_; lean_object* v___x_4365_; lean_object* v___x_4366_; uint32_t v___x_4367_; 
lean_dec_ref(v_acc_4354_);
lean_inc(v_k_4317_);
v___f_4363_ = lean_alloc_closure((void*)(lp_competition_ExactRuntime_conv2dWith___at___00Submission_kernels_spec__2___lam__0___boxed), 5, 4);
lean_closure_set(v___f_4363_, 0, v_k_4317_);
lean_closure_set(v___f_4363_, 1, v_b_4322_);
lean_closure_set(v___f_4363_, 2, v_o_4344_);
lean_closure_set(v___f_4363_, 3, v_wts_4323_);
v___f_4364_ = lean_alloc_closure((void*)(lp_competition_ExactRuntime_conv2dWith___at___00Submission_kernels_spec__2___lam__1___boxed), 11, 10);
lean_closure_set(v___f_4364_, 0, v_k_4317_);
lean_closure_set(v___f_4364_, 1, v_kw_4318_);
lean_closure_set(v___f_4364_, 2, v_kh_4319_);
lean_closure_set(v___f_4364_, 3, v_y_4346_);
lean_closure_set(v___f_4364_, 4, v_stride_4325_);
lean_closure_set(v___f_4364_, 5, v_pad_4326_);
lean_closure_set(v___f_4364_, 6, v_x_4347_);
lean_closure_set(v___f_4364_, 7, v_h_4327_);
lean_closure_set(v___f_4364_, 8, v_w_4328_);
lean_closure_set(v___f_4364_, 9, v_inp_4321_);
lean_inc(v___x_4349_);
v___x_4365_ = l_Array_ofFn___redArg(v___x_4349_, v___f_4364_);
v___x_4366_ = l_Array_ofFn___redArg(v___x_4349_, v___f_4363_);
v___x_4367_ = lp_competition_ExactRuntime_dotSpec(v___x_4365_, v___x_4366_);
v___y_4331_ = v___x_4367_;
goto v___jp_4330_;
}
v___jp_4330_:
{
if (v_relu_4324_ == 0)
{
return v___y_4331_;
}
else
{
uint32_t v___x_4332_; uint32_t v___x_4333_; uint32_t v___x_4334_; uint8_t v___x_4335_; 
v___x_4332_ = 2147483648;
v___x_4333_ = lean_uint32_land(v___y_4331_, v___x_4332_);
v___x_4334_ = 0;
v___x_4335_ = lean_uint32_dec_eq(v___x_4333_, v___x_4334_);
if (v___x_4335_ == 0)
{
uint32_t v___x_4336_; uint32_t v___x_4337_; uint32_t v___x_4338_; uint32_t v___x_4339_; uint8_t v___x_4340_; 
v___x_4336_ = 23;
v___x_4337_ = lean_uint32_shift_right(v___y_4331_, v___x_4336_);
v___x_4338_ = 255;
v___x_4339_ = lean_uint32_land(v___x_4337_, v___x_4338_);
v___x_4340_ = lean_uint32_dec_eq(v___x_4339_, v___x_4338_);
if (v___x_4340_ == 0)
{
if (v___x_4340_ == 0)
{
return v___x_4334_;
}
else
{
return v___y_4331_;
}
}
else
{
uint32_t v___x_4341_; uint32_t v___x_4342_; uint8_t v___x_4343_; 
v___x_4341_ = 8388607;
v___x_4342_ = lean_uint32_land(v___y_4331_, v___x_4341_);
v___x_4343_ = lean_uint32_dec_eq(v___x_4342_, v___x_4334_);
if (v___x_4343_ == 0)
{
if (v___x_4340_ == 0)
{
return v___x_4334_;
}
else
{
return v___y_4331_;
}
}
else
{
return v___x_4334_;
}
}
}
else
{
return v___y_4331_;
}
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_ExactRuntime_conv2dWith___at___00Submission_kernels_spec__2___lam__2___boxed(lean_object* v___x_4368_, lean_object* v___x_4369_, lean_object* v___x_4370_, lean_object* v_k_4371_, lean_object* v_kw_4372_, lean_object* v_kh_4373_, lean_object* v_s_4374_, lean_object* v_inp_4375_, lean_object* v_b_4376_, lean_object* v_wts_4377_, lean_object* v_relu_4378_, lean_object* v_stride_4379_, lean_object* v_pad_4380_, lean_object* v_h_4381_, lean_object* v_w_4382_, lean_object* v_q_4383_){
_start:
{
uint8_t v_relu_boxed_4384_; uint32_t v_res_4385_; lean_object* v_r_4386_; 
v_relu_boxed_4384_ = lean_unbox(v_relu_4378_);
v_res_4385_ = lp_competition_ExactRuntime_conv2dWith___at___00Submission_kernels_spec__2___lam__2(v___x_4368_, v___x_4369_, v___x_4370_, v_k_4371_, v_kw_4372_, v_kh_4373_, v_s_4374_, v_inp_4375_, v_b_4376_, v_wts_4377_, v_relu_boxed_4384_, v_stride_4379_, v_pad_4380_, v_h_4381_, v_w_4382_, v_q_4383_);
lean_dec(v_q_4383_);
lean_dec_ref(v_s_4374_);
lean_dec(v___x_4370_);
lean_dec(v___x_4369_);
lean_dec(v___x_4368_);
v_r_4386_ = lean_box_uint32(v_res_4385_);
return v_r_4386_;
}
}
LEAN_EXPORT lean_object* lp_competition_ExactRuntime_conv2dWith___at___00Submission_kernels_spec__2(lean_object* v_s_4387_, uint8_t v_relu_4388_, lean_object* v_inp_4389_, lean_object* v_wts_4390_, lean_object* v_b_4391_){
_start:
{
lean_object* v_cin_4392_; lean_object* v_h_4393_; lean_object* v_w_4394_; lean_object* v_cout_4395_; lean_object* v_kh_4396_; lean_object* v_kw_4397_; lean_object* v_stride_4398_; lean_object* v_pad_4399_; lean_object* v___x_4400_; lean_object* v_k_4401_; lean_object* v___x_4402_; lean_object* v___x_4403_; lean_object* v___x_4404_; lean_object* v___x_4405_; lean_object* v___f_4406_; lean_object* v___x_4407_; lean_object* v___x_4408_; 
v_cin_4392_ = lean_ctor_get(v_s_4387_, 0);
v_h_4393_ = lean_ctor_get(v_s_4387_, 1);
lean_inc(v_h_4393_);
v_w_4394_ = lean_ctor_get(v_s_4387_, 2);
lean_inc(v_w_4394_);
v_cout_4395_ = lean_ctor_get(v_s_4387_, 3);
lean_inc(v_cout_4395_);
v_kh_4396_ = lean_ctor_get(v_s_4387_, 4);
lean_inc(v_kh_4396_);
v_kw_4397_ = lean_ctor_get(v_s_4387_, 5);
lean_inc(v_kw_4397_);
v_stride_4398_ = lean_ctor_get(v_s_4387_, 6);
lean_inc(v_stride_4398_);
v_pad_4399_ = lean_ctor_get(v_s_4387_, 7);
lean_inc(v_pad_4399_);
v___x_4400_ = lean_nat_mul(v_cin_4392_, v_kh_4396_);
v_k_4401_ = lean_nat_mul(v___x_4400_, v_kw_4397_);
lean_dec(v___x_4400_);
v___x_4402_ = lp_competition_ExactRuntime_ConvShape_ho(v_s_4387_);
v___x_4403_ = lp_competition_ExactRuntime_ConvShape_wo(v_s_4387_);
v___x_4404_ = lean_nat_mul(v___x_4402_, v___x_4403_);
v___x_4405_ = lean_box(v_relu_4388_);
lean_inc(v___x_4404_);
v___f_4406_ = lean_alloc_closure((void*)(lp_competition_ExactRuntime_conv2dWith___at___00Submission_kernels_spec__2___lam__2___boxed), 16, 15);
lean_closure_set(v___f_4406_, 0, v___x_4404_);
lean_closure_set(v___f_4406_, 1, v___x_4403_);
lean_closure_set(v___f_4406_, 2, v___x_4402_);
lean_closure_set(v___f_4406_, 3, v_k_4401_);
lean_closure_set(v___f_4406_, 4, v_kw_4397_);
lean_closure_set(v___f_4406_, 5, v_kh_4396_);
lean_closure_set(v___f_4406_, 6, v_s_4387_);
lean_closure_set(v___f_4406_, 7, v_inp_4389_);
lean_closure_set(v___f_4406_, 8, v_b_4391_);
lean_closure_set(v___f_4406_, 9, v_wts_4390_);
lean_closure_set(v___f_4406_, 10, v___x_4405_);
lean_closure_set(v___f_4406_, 11, v_stride_4398_);
lean_closure_set(v___f_4406_, 12, v_pad_4399_);
lean_closure_set(v___f_4406_, 13, v_h_4393_);
lean_closure_set(v___f_4406_, 14, v_w_4394_);
v___x_4407_ = lean_nat_mul(v_cout_4395_, v___x_4404_);
lean_dec(v___x_4404_);
lean_dec(v_cout_4395_);
v___x_4408_ = l_Array_ofFn___redArg(v___x_4407_, v___f_4406_);
return v___x_4408_;
}
}
LEAN_EXPORT lean_object* lp_competition_ExactRuntime_conv2dWith___at___00Submission_kernels_spec__2___boxed(lean_object* v_s_4409_, lean_object* v_relu_4410_, lean_object* v_inp_4411_, lean_object* v_wts_4412_, lean_object* v_b_4413_){
_start:
{
uint8_t v_relu_boxed_4414_; lean_object* v_res_4415_; 
v_relu_boxed_4414_ = lean_unbox(v_relu_4410_);
v_res_4415_ = lp_competition_ExactRuntime_conv2dWith___at___00Submission_kernels_spec__2(v_s_4409_, v_relu_boxed_4414_, v_inp_4411_, v_wts_4412_, v_b_4413_);
return v_res_4415_;
}
}
LEAN_EXPORT uint32_t lp_competition_ExactRuntime_gemmWith___at___00Submission_kernels_spec__1___lam__0(lean_object* v_00_u03b2_4416_, lean_object* v_m_4417_, lean_object* v_i_4418_, lean_object* v_k_4419_, uint32_t v___x_4420_, lean_object* v_A_4421_, lean_object* v_i_4422_){
_start:
{
lean_object* v___x_4423_; lean_object* v___x_4424_; lean_object* v___x_4425_; lean_object* v___x_4426_; lean_object* v___x_4427_; lean_object* v___x_4428_; uint32_t v___x_4429_; 
v___x_4423_ = lean_nat_mul(v_00_u03b2_4416_, v_m_4417_);
v___x_4424_ = lean_nat_add(v___x_4423_, v_i_4418_);
lean_dec(v___x_4423_);
v___x_4425_ = lean_nat_mul(v___x_4424_, v_k_4419_);
lean_dec(v___x_4424_);
v___x_4426_ = lean_nat_add(v___x_4425_, v_i_4422_);
lean_dec(v___x_4425_);
v___x_4427_ = lean_box_uint32(v___x_4420_);
v___x_4428_ = lean_array_get(v___x_4427_, v_A_4421_, v___x_4426_);
lean_dec(v___x_4426_);
lean_dec(v___x_4427_);
v___x_4429_ = lean_unbox_uint32(v___x_4428_);
lean_dec(v___x_4428_);
return v___x_4429_;
}
}
LEAN_EXPORT lean_object* lp_competition_ExactRuntime_gemmWith___at___00Submission_kernels_spec__1___lam__0___boxed(lean_object* v_00_u03b2_4430_, lean_object* v_m_4431_, lean_object* v_i_4432_, lean_object* v_k_4433_, lean_object* v___x_4434_, lean_object* v_A_4435_, lean_object* v_i_4436_){
_start:
{
uint32_t v___x_4300__boxed_4437_; uint32_t v_res_4438_; lean_object* v_r_4439_; 
v___x_4300__boxed_4437_ = lean_unbox_uint32(v___x_4434_);
lean_dec(v___x_4434_);
v_res_4438_ = lp_competition_ExactRuntime_gemmWith___at___00Submission_kernels_spec__1___lam__0(v_00_u03b2_4430_, v_m_4431_, v_i_4432_, v_k_4433_, v___x_4300__boxed_4437_, v_A_4435_, v_i_4436_);
lean_dec(v_i_4436_);
lean_dec_ref(v_A_4435_);
lean_dec(v_k_4433_);
lean_dec(v_i_4432_);
lean_dec(v_m_4431_);
lean_dec(v_00_u03b2_4430_);
v_r_4439_ = lean_box_uint32(v_res_4438_);
return v_r_4439_;
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_dotLoop___at___00Submission_rmsnormCached_spec__0___at___00ExactRuntime_gemmWith___at___00Submission_kernels_spec__1_spec__2(lean_object* v_00_u03b2_4440_, lean_object* v_m_4441_, lean_object* v_i_4442_, lean_object* v_k_4443_, lean_object* v_A_4444_, lean_object* v_n_4445_, lean_object* v_j_4446_, lean_object* v_B_4447_, lean_object* v_pos_4448_, lean_object* v_neg_4449_, uint8_t v_sp_4450_, uint8_t v_nz_4451_, lean_object* v_index_4452_, lean_object* v_x_4453_){
_start:
{
lean_object* v_zero_4454_; uint8_t v_isZero_4455_; 
v_zero_4454_ = lean_unsigned_to_nat(0u);
v_isZero_4455_ = lean_nat_dec_eq(v_x_4453_, v_zero_4454_);
if (v_isZero_4455_ == 1)
{
lean_object* v___x_4456_; 
lean_dec(v_x_4453_);
lean_dec(v_index_4452_);
v___x_4456_ = lean_alloc_ctor(0, 2, 2);
lean_ctor_set(v___x_4456_, 0, v_pos_4448_);
lean_ctor_set(v___x_4456_, 1, v_neg_4449_);
lean_ctor_set_uint8(v___x_4456_, sizeof(void*)*2, v_sp_4450_);
lean_ctor_set_uint8(v___x_4456_, sizeof(void*)*2 + 1, v_nz_4451_);
return v___x_4456_;
}
else
{
uint32_t v___x_4457_; lean_object* v_one_4458_; lean_object* v_n_4459_; lean_object* v_pos_4461_; lean_object* v_neg_4462_; uint8_t v_special_4463_; uint8_t v_negZero_4464_; lean_object* v___y_4470_; lean_object* v___y_4471_; lean_object* v___y_4472_; uint8_t v___y_4473_; lean_object* v___y_4474_; lean_object* v___y_4484_; lean_object* v___y_4485_; lean_object* v___y_4486_; lean_object* v___y_4487_; lean_object* v___y_4497_; lean_object* v___y_4498_; uint8_t v___y_4499_; lean_object* v___y_4546_; lean_object* v___y_4547_; lean_object* v___x_4549_; lean_object* v___x_4550_; lean_object* v___x_4551_; lean_object* v___x_4552_; lean_object* v___x_4553_; lean_object* v___x_4554_; uint32_t v___x_4555_; uint32_t v___x_4556_; uint32_t v___x_4557_; uint32_t v___x_4558_; uint32_t v___x_4559_; uint8_t v___x_4560_; lean_object* v___y_4562_; uint8_t v___y_4563_; lean_object* v___y_4564_; uint8_t v___y_4565_; 
v___x_4457_ = 0;
v_one_4458_ = lean_unsigned_to_nat(1u);
v_n_4459_ = lean_nat_sub(v_x_4453_, v_one_4458_);
lean_dec(v_x_4453_);
v___x_4549_ = lean_nat_mul(v_00_u03b2_4440_, v_m_4441_);
v___x_4550_ = lean_nat_add(v___x_4549_, v_i_4442_);
lean_dec(v___x_4549_);
v___x_4551_ = lean_nat_mul(v___x_4550_, v_k_4443_);
lean_dec(v___x_4550_);
v___x_4552_ = lean_nat_add(v___x_4551_, v_index_4452_);
lean_dec(v___x_4551_);
v___x_4553_ = lp_competition_Submission_dotX___lam__0___boxed__const__1;
v___x_4554_ = lean_array_get_borrowed(v___x_4553_, v_A_4444_, v___x_4552_);
lean_dec(v___x_4552_);
v___x_4555_ = 23;
v___x_4556_ = lean_unbox_uint32(v___x_4554_);
v___x_4557_ = lean_uint32_shift_right(v___x_4556_, v___x_4555_);
v___x_4558_ = 255;
v___x_4559_ = lean_uint32_land(v___x_4557_, v___x_4558_);
v___x_4560_ = lean_uint32_dec_eq(v___x_4559_, v___x_4558_);
if (v___x_4560_ == 0)
{
lean_object* v___x_4566_; lean_object* v___x_4567_; lean_object* v___x_4568_; lean_object* v___x_4569_; lean_object* v___x_4570_; lean_object* v___x_4571_; lean_object* v___y_4573_; lean_object* v___y_4574_; uint8_t v___y_4575_; lean_object* v___y_4582_; lean_object* v___y_4583_; lean_object* v___y_4584_; lean_object* v___y_4592_; lean_object* v___y_4593_; lean_object* v___y_4601_; lean_object* v___y_4602_; lean_object* v___y_4608_; uint32_t v___x_4623_; uint32_t v___x_4624_; uint32_t v___x_4625_; uint8_t v___x_4626_; 
v___x_4566_ = lean_nat_mul(v_00_u03b2_4440_, v_k_4443_);
v___x_4567_ = lean_nat_add(v___x_4566_, v_index_4452_);
lean_dec(v___x_4566_);
v___x_4568_ = lean_nat_mul(v___x_4567_, v_n_4445_);
lean_dec(v___x_4567_);
v___x_4569_ = lean_nat_add(v___x_4568_, v_j_4446_);
lean_dec(v___x_4568_);
v___x_4570_ = lp_competition_Submission_dotX___lam__0___boxed__const__1;
v___x_4571_ = lean_array_get_borrowed(v___x_4570_, v_B_4447_, v___x_4569_);
lean_dec(v___x_4569_);
v___x_4623_ = lean_unbox_uint32(v___x_4571_);
v___x_4624_ = lean_uint32_shift_right(v___x_4623_, v___x_4555_);
v___x_4625_ = lean_uint32_land(v___x_4624_, v___x_4558_);
v___x_4626_ = lean_uint32_dec_eq(v___x_4625_, v___x_4558_);
if (v___x_4626_ == 0)
{
uint8_t v___x_4627_; 
v___x_4627_ = lean_uint32_dec_eq(v___x_4559_, v___x_4457_);
if (v___x_4627_ == 0)
{
lean_object* v___x_4628_; uint32_t v___x_4629_; uint32_t v___x_4630_; uint32_t v___x_4631_; lean_object* v___x_4632_; lean_object* v___x_4633_; 
v___x_4628_ = lean_unsigned_to_nat(8388608u);
v___x_4629_ = 8388607;
v___x_4630_ = lean_unbox_uint32(v___x_4554_);
v___x_4631_ = lean_uint32_land(v___x_4630_, v___x_4629_);
v___x_4632_ = lean_uint32_to_nat(v___x_4631_);
v___x_4633_ = lean_nat_add(v___x_4628_, v___x_4632_);
lean_dec(v___x_4632_);
v___y_4608_ = v___x_4633_;
goto v___jp_4607_;
}
else
{
uint32_t v___x_4634_; uint32_t v___x_4635_; uint32_t v___x_4636_; lean_object* v___x_4637_; 
v___x_4634_ = 8388607;
v___x_4635_ = lean_unbox_uint32(v___x_4554_);
v___x_4636_ = lean_uint32_land(v___x_4635_, v___x_4634_);
v___x_4637_ = lean_uint32_to_nat(v___x_4636_);
v___y_4608_ = v___x_4637_;
goto v___jp_4607_;
}
}
else
{
goto v___jp_4467_;
}
v___jp_4572_:
{
uint32_t v___x_4576_; uint32_t v___x_4577_; uint32_t v___x_4578_; uint8_t v___x_4579_; 
v___x_4576_ = 2147483648;
v___x_4577_ = lean_unbox_uint32(v___x_4571_);
v___x_4578_ = lean_uint32_land(v___x_4577_, v___x_4576_);
v___x_4579_ = lean_uint32_dec_eq(v___x_4578_, v___x_4457_);
if (v___x_4579_ == 0)
{
uint8_t v___x_4580_; 
v___x_4580_ = 1;
v___y_4562_ = v___y_4573_;
v___y_4563_ = v___y_4575_;
v___y_4564_ = v___y_4574_;
v___y_4565_ = v___x_4580_;
goto v___jp_4561_;
}
else
{
v___y_4562_ = v___y_4573_;
v___y_4563_ = v___y_4575_;
v___y_4564_ = v___y_4574_;
v___y_4565_ = v___x_4560_;
goto v___jp_4561_;
}
}
v___jp_4581_:
{
lean_object* v___x_4585_; uint32_t v___x_4586_; uint32_t v___x_4587_; uint32_t v___x_4588_; uint8_t v___x_4589_; 
v___x_4585_ = lean_nat_add(v___y_4583_, v___y_4584_);
lean_dec(v___y_4584_);
lean_dec(v___y_4583_);
v___x_4586_ = 2147483648;
v___x_4587_ = lean_unbox_uint32(v___x_4554_);
v___x_4588_ = lean_uint32_land(v___x_4587_, v___x_4586_);
v___x_4589_ = lean_uint32_dec_eq(v___x_4588_, v___x_4457_);
if (v___x_4589_ == 0)
{
uint8_t v___x_4590_; 
v___x_4590_ = 1;
v___y_4573_ = v___y_4582_;
v___y_4574_ = v___x_4585_;
v___y_4575_ = v___x_4590_;
goto v___jp_4572_;
}
else
{
v___y_4573_ = v___y_4582_;
v___y_4574_ = v___x_4585_;
v___y_4575_ = v___x_4560_;
goto v___jp_4572_;
}
}
v___jp_4591_:
{
uint32_t v___x_4594_; uint32_t v___x_4595_; uint32_t v___x_4596_; uint8_t v___x_4597_; 
v___x_4594_ = lean_unbox_uint32(v___x_4571_);
v___x_4595_ = lean_uint32_shift_right(v___x_4594_, v___x_4555_);
v___x_4596_ = lean_uint32_land(v___x_4595_, v___x_4558_);
v___x_4597_ = lean_uint32_dec_eq(v___x_4596_, v___x_4457_);
if (v___x_4597_ == 0)
{
lean_object* v___x_4598_; lean_object* v___x_4599_; 
v___x_4598_ = lean_uint32_to_nat(v___x_4596_);
v___x_4599_ = lean_nat_sub(v___x_4598_, v_one_4458_);
lean_dec(v___x_4598_);
v___y_4582_ = v___y_4592_;
v___y_4583_ = v___y_4593_;
v___y_4584_ = v___x_4599_;
goto v___jp_4581_;
}
else
{
v___y_4582_ = v___y_4592_;
v___y_4583_ = v___y_4593_;
v___y_4584_ = v_zero_4454_;
goto v___jp_4581_;
}
}
v___jp_4600_:
{
lean_object* v___x_4603_; uint8_t v___x_4604_; 
v___x_4603_ = lean_nat_mul(v___y_4601_, v___y_4602_);
lean_dec(v___y_4602_);
lean_dec(v___y_4601_);
v___x_4604_ = lean_uint32_dec_eq(v___x_4559_, v___x_4457_);
if (v___x_4604_ == 0)
{
lean_object* v___x_4605_; lean_object* v___x_4606_; 
v___x_4605_ = lean_uint32_to_nat(v___x_4559_);
v___x_4606_ = lean_nat_sub(v___x_4605_, v_one_4458_);
lean_dec(v___x_4605_);
v___y_4592_ = v___x_4603_;
v___y_4593_ = v___x_4606_;
goto v___jp_4591_;
}
else
{
v___y_4592_ = v___x_4603_;
v___y_4593_ = v_zero_4454_;
goto v___jp_4591_;
}
}
v___jp_4607_:
{
uint32_t v___x_4609_; uint32_t v___x_4610_; uint32_t v___x_4611_; uint8_t v___x_4612_; 
v___x_4609_ = lean_unbox_uint32(v___x_4571_);
v___x_4610_ = lean_uint32_shift_right(v___x_4609_, v___x_4555_);
v___x_4611_ = lean_uint32_land(v___x_4610_, v___x_4558_);
v___x_4612_ = lean_uint32_dec_eq(v___x_4611_, v___x_4457_);
if (v___x_4612_ == 0)
{
lean_object* v___x_4613_; uint32_t v___x_4614_; uint32_t v___x_4615_; uint32_t v___x_4616_; lean_object* v___x_4617_; lean_object* v___x_4618_; 
v___x_4613_ = lean_unsigned_to_nat(8388608u);
v___x_4614_ = 8388607;
v___x_4615_ = lean_unbox_uint32(v___x_4571_);
v___x_4616_ = lean_uint32_land(v___x_4615_, v___x_4614_);
v___x_4617_ = lean_uint32_to_nat(v___x_4616_);
v___x_4618_ = lean_nat_add(v___x_4613_, v___x_4617_);
lean_dec(v___x_4617_);
v___y_4601_ = v___y_4608_;
v___y_4602_ = v___x_4618_;
goto v___jp_4600_;
}
else
{
uint32_t v___x_4619_; uint32_t v___x_4620_; uint32_t v___x_4621_; lean_object* v___x_4622_; 
v___x_4619_ = 8388607;
v___x_4620_ = lean_unbox_uint32(v___x_4571_);
v___x_4621_ = lean_uint32_land(v___x_4620_, v___x_4619_);
v___x_4622_ = lean_uint32_to_nat(v___x_4621_);
v___y_4601_ = v___y_4608_;
v___y_4602_ = v___x_4622_;
goto v___jp_4600_;
}
}
}
else
{
goto v___jp_4467_;
}
v___jp_4460_:
{
lean_object* v___x_4465_; 
v___x_4465_ = lean_nat_add(v_index_4452_, v_one_4458_);
lean_dec(v_index_4452_);
v_pos_4448_ = v_pos_4461_;
v_neg_4449_ = v_neg_4462_;
v_sp_4450_ = v_special_4463_;
v_nz_4451_ = v_negZero_4464_;
v_index_4452_ = v___x_4465_;
v_x_4453_ = v_n_4459_;
goto _start;
}
v___jp_4467_:
{
uint8_t v___x_4468_; 
v___x_4468_ = 1;
v_pos_4461_ = v_pos_4448_;
v_neg_4462_ = v_neg_4449_;
v_special_4463_ = v___x_4468_;
v_negZero_4464_ = v_nz_4451_;
goto v___jp_4460_;
}
v___jp_4469_:
{
lean_object* v___x_4475_; lean_object* v___x_4476_; uint8_t v___x_4477_; 
v___x_4475_ = lean_nat_add(v___y_4472_, v___y_4470_);
lean_dec(v___y_4472_);
v___x_4476_ = lean_array_get_size(v___y_4474_);
v___x_4477_ = lean_nat_dec_lt(v___x_4475_, v___x_4476_);
if (v___x_4477_ == 0)
{
lean_dec(v___x_4475_);
lean_dec(v___y_4471_);
v_pos_4461_ = v___y_4474_;
v_neg_4462_ = v_neg_4449_;
v_special_4463_ = v_sp_4450_;
v_negZero_4464_ = v___y_4473_;
goto v___jp_4460_;
}
else
{
lean_object* v_v_4478_; lean_object* v___x_4479_; lean_object* v_xs_x27_4480_; lean_object* v___x_4481_; lean_object* v___x_4482_; 
v_v_4478_ = lean_array_fget(v___y_4474_, v___x_4475_);
v___x_4479_ = lean_box(0);
v_xs_x27_4480_ = lean_array_fset(v___y_4474_, v___x_4475_, v___x_4479_);
v___x_4481_ = lean_nat_add(v_v_4478_, v___y_4471_);
lean_dec(v___y_4471_);
lean_dec(v_v_4478_);
v___x_4482_ = lean_array_fset(v_xs_x27_4480_, v___x_4475_, v___x_4481_);
lean_dec(v___x_4475_);
v_pos_4461_ = v___x_4482_;
v_neg_4462_ = v_neg_4449_;
v_special_4463_ = v_sp_4450_;
v_negZero_4464_ = v___y_4473_;
goto v___jp_4460_;
}
}
v___jp_4483_:
{
lean_object* v___x_4488_; lean_object* v___x_4489_; uint8_t v___x_4490_; 
v___x_4488_ = lean_nat_add(v___y_4485_, v___y_4486_);
lean_dec(v___y_4485_);
v___x_4489_ = lean_array_get_size(v___y_4487_);
v___x_4490_ = lean_nat_dec_lt(v___x_4488_, v___x_4489_);
if (v___x_4490_ == 0)
{
lean_dec(v___x_4488_);
lean_dec(v___y_4484_);
v_pos_4461_ = v_pos_4448_;
v_neg_4462_ = v___y_4487_;
v_special_4463_ = v_sp_4450_;
v_negZero_4464_ = v_isZero_4455_;
goto v___jp_4460_;
}
else
{
lean_object* v_v_4491_; lean_object* v___x_4492_; lean_object* v_xs_x27_4493_; lean_object* v___x_4494_; lean_object* v___x_4495_; 
v_v_4491_ = lean_array_fget(v___y_4487_, v___x_4488_);
v___x_4492_ = lean_box(0);
v_xs_x27_4493_ = lean_array_fset(v___y_4487_, v___x_4488_, v___x_4492_);
v___x_4494_ = lean_nat_add(v_v_4491_, v___y_4484_);
lean_dec(v___y_4484_);
lean_dec(v_v_4491_);
v___x_4495_ = lean_array_fset(v_xs_x27_4493_, v___x_4488_, v___x_4494_);
lean_dec(v___x_4488_);
v_pos_4461_ = v_pos_4448_;
v_neg_4462_ = v___x_4495_;
v_special_4463_ = v_sp_4450_;
v_negZero_4464_ = v_isZero_4455_;
goto v___jp_4460_;
}
}
v___jp_4496_:
{
uint8_t v___x_4500_; 
v___x_4500_ = lean_nat_dec_eq(v___y_4497_, v_zero_4454_);
if (v___x_4500_ == 0)
{
if (v___y_4499_ == 0)
{
uint64_t v___x_4501_; lean_object* v___x_4502_; lean_object* v___x_4503_; lean_object* v_l_4504_; lean_object* v___x_4505_; uint64_t v_r_4506_; uint64_t v___x_4507_; uint64_t v___x_4508_; uint64_t v___x_4509_; uint64_t v___x_4510_; uint64_t v___x_4511_; uint64_t v___x_4512_; lean_object* v_hi_4513_; lean_object* v___x_4514_; uint8_t v___x_4515_; 
v___x_4501_ = lean_uint64_of_nat(v___y_4497_);
lean_dec(v___y_4497_);
v___x_4502_ = lean_unsigned_to_nat(32u);
v___x_4503_ = lean_unsigned_to_nat(5u);
v_l_4504_ = lean_nat_shiftr(v___y_4498_, v___x_4503_);
v___x_4505_ = lean_nat_mod(v___y_4498_, v___x_4502_);
lean_dec(v___y_4498_);
v_r_4506_ = lean_uint64_of_nat(v___x_4505_);
lean_dec(v___x_4505_);
v___x_4507_ = 1ULL;
v___x_4508_ = 32ULL;
v___x_4509_ = lean_uint64_sub(v___x_4508_, v_r_4506_);
v___x_4510_ = lean_uint64_shift_left(v___x_4507_, v___x_4509_);
v___x_4511_ = lean_uint64_mod(v___x_4501_, v___x_4510_);
v___x_4512_ = lean_uint64_shift_right(v___x_4501_, v___x_4509_);
v_hi_4513_ = lean_uint64_to_nat(v___x_4512_);
v___x_4514_ = lean_array_get_size(v_pos_4448_);
v___x_4515_ = lean_nat_dec_lt(v_l_4504_, v___x_4514_);
if (v___x_4515_ == 0)
{
v___y_4470_ = v_one_4458_;
v___y_4471_ = v_hi_4513_;
v___y_4472_ = v_l_4504_;
v___y_4473_ = v___y_4499_;
v___y_4474_ = v_pos_4448_;
goto v___jp_4469_;
}
else
{
uint64_t v___x_4516_; lean_object* v_lo_4517_; lean_object* v_v_4518_; lean_object* v___x_4519_; lean_object* v_xs_x27_4520_; lean_object* v___x_4521_; lean_object* v___x_4522_; 
v___x_4516_ = lean_uint64_shift_left(v___x_4511_, v_r_4506_);
v_lo_4517_ = lean_uint64_to_nat(v___x_4516_);
v_v_4518_ = lean_array_fget(v_pos_4448_, v_l_4504_);
v___x_4519_ = lean_box(0);
v_xs_x27_4520_ = lean_array_fset(v_pos_4448_, v_l_4504_, v___x_4519_);
v___x_4521_ = lean_nat_add(v_v_4518_, v_lo_4517_);
lean_dec(v_lo_4517_);
lean_dec(v_v_4518_);
v___x_4522_ = lean_array_fset(v_xs_x27_4520_, v_l_4504_, v___x_4521_);
v___y_4470_ = v_one_4458_;
v___y_4471_ = v_hi_4513_;
v___y_4472_ = v_l_4504_;
v___y_4473_ = v___y_4499_;
v___y_4474_ = v___x_4522_;
goto v___jp_4469_;
}
}
else
{
uint64_t v___x_4523_; lean_object* v___x_4524_; lean_object* v___x_4525_; lean_object* v_l_4526_; lean_object* v___x_4527_; uint64_t v_r_4528_; uint64_t v___x_4529_; uint64_t v___x_4530_; uint64_t v___x_4531_; uint64_t v___x_4532_; uint64_t v___x_4533_; uint64_t v___x_4534_; lean_object* v_hi_4535_; lean_object* v___x_4536_; uint8_t v___x_4537_; 
v___x_4523_ = lean_uint64_of_nat(v___y_4497_);
lean_dec(v___y_4497_);
v___x_4524_ = lean_unsigned_to_nat(32u);
v___x_4525_ = lean_unsigned_to_nat(5u);
v_l_4526_ = lean_nat_shiftr(v___y_4498_, v___x_4525_);
v___x_4527_ = lean_nat_mod(v___y_4498_, v___x_4524_);
lean_dec(v___y_4498_);
v_r_4528_ = lean_uint64_of_nat(v___x_4527_);
lean_dec(v___x_4527_);
v___x_4529_ = 1ULL;
v___x_4530_ = 32ULL;
v___x_4531_ = lean_uint64_sub(v___x_4530_, v_r_4528_);
v___x_4532_ = lean_uint64_shift_left(v___x_4529_, v___x_4531_);
v___x_4533_ = lean_uint64_mod(v___x_4523_, v___x_4532_);
v___x_4534_ = lean_uint64_shift_right(v___x_4523_, v___x_4531_);
v_hi_4535_ = lean_uint64_to_nat(v___x_4534_);
v___x_4536_ = lean_array_get_size(v_neg_4449_);
v___x_4537_ = lean_nat_dec_lt(v_l_4526_, v___x_4536_);
if (v___x_4537_ == 0)
{
v___y_4484_ = v_hi_4535_;
v___y_4485_ = v_l_4526_;
v___y_4486_ = v_one_4458_;
v___y_4487_ = v_neg_4449_;
goto v___jp_4483_;
}
else
{
uint64_t v___x_4538_; lean_object* v_lo_4539_; lean_object* v_v_4540_; lean_object* v___x_4541_; lean_object* v_xs_x27_4542_; lean_object* v___x_4543_; lean_object* v___x_4544_; 
v___x_4538_ = lean_uint64_shift_left(v___x_4533_, v_r_4528_);
v_lo_4539_ = lean_uint64_to_nat(v___x_4538_);
v_v_4540_ = lean_array_fget(v_neg_4449_, v_l_4526_);
v___x_4541_ = lean_box(0);
v_xs_x27_4542_ = lean_array_fset(v_neg_4449_, v_l_4526_, v___x_4541_);
v___x_4543_ = lean_nat_add(v_v_4540_, v_lo_4539_);
lean_dec(v_lo_4539_);
lean_dec(v_v_4540_);
v___x_4544_ = lean_array_fset(v_xs_x27_4542_, v_l_4526_, v___x_4543_);
v___y_4484_ = v_hi_4535_;
v___y_4485_ = v_l_4526_;
v___y_4486_ = v_one_4458_;
v___y_4487_ = v___x_4544_;
goto v___jp_4483_;
}
}
}
else
{
lean_dec(v___y_4498_);
lean_dec(v___y_4497_);
if (v_nz_4451_ == 0)
{
v_pos_4461_ = v_pos_4448_;
v_neg_4462_ = v_neg_4449_;
v_special_4463_ = v_sp_4450_;
v_negZero_4464_ = v_nz_4451_;
goto v___jp_4460_;
}
else
{
v_pos_4461_ = v_pos_4448_;
v_neg_4462_ = v_neg_4449_;
v_special_4463_ = v_sp_4450_;
v_negZero_4464_ = v___y_4499_;
goto v___jp_4460_;
}
}
}
v___jp_4545_:
{
uint8_t v___x_4548_; 
v___x_4548_ = 1;
v___y_4497_ = v___y_4546_;
v___y_4498_ = v___y_4547_;
v___y_4499_ = v___x_4548_;
goto v___jp_4496_;
}
v___jp_4561_:
{
if (v___y_4563_ == 0)
{
if (v___y_4565_ == 0)
{
v___y_4497_ = v___y_4562_;
v___y_4498_ = v___y_4564_;
v___y_4499_ = v___x_4560_;
goto v___jp_4496_;
}
else
{
v___y_4546_ = v___y_4562_;
v___y_4547_ = v___y_4564_;
goto v___jp_4545_;
}
}
else
{
if (v___y_4565_ == 0)
{
v___y_4546_ = v___y_4562_;
v___y_4547_ = v___y_4564_;
goto v___jp_4545_;
}
else
{
v___y_4497_ = v___y_4562_;
v___y_4498_ = v___y_4564_;
v___y_4499_ = v___x_4560_;
goto v___jp_4496_;
}
}
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_dotLoop___at___00Submission_rmsnormCached_spec__0___at___00ExactRuntime_gemmWith___at___00Submission_kernels_spec__1_spec__2___boxed(lean_object* v_00_u03b2_4638_, lean_object* v_m_4639_, lean_object* v_i_4640_, lean_object* v_k_4641_, lean_object* v_A_4642_, lean_object* v_n_4643_, lean_object* v_j_4644_, lean_object* v_B_4645_, lean_object* v_pos_4646_, lean_object* v_neg_4647_, lean_object* v_sp_4648_, lean_object* v_nz_4649_, lean_object* v_index_4650_, lean_object* v_x_4651_){
_start:
{
uint8_t v_sp_boxed_4652_; uint8_t v_nz_boxed_4653_; lean_object* v_res_4654_; 
v_sp_boxed_4652_ = lean_unbox(v_sp_4648_);
v_nz_boxed_4653_ = lean_unbox(v_nz_4649_);
v_res_4654_ = lp_competition_Submission_dotLoop___at___00Submission_rmsnormCached_spec__0___at___00ExactRuntime_gemmWith___at___00Submission_kernels_spec__1_spec__2(v_00_u03b2_4638_, v_m_4639_, v_i_4640_, v_k_4641_, v_A_4642_, v_n_4643_, v_j_4644_, v_B_4645_, v_pos_4646_, v_neg_4647_, v_sp_boxed_4652_, v_nz_boxed_4653_, v_index_4650_, v_x_4651_);
lean_dec_ref(v_B_4645_);
lean_dec(v_j_4644_);
lean_dec(v_n_4643_);
lean_dec_ref(v_A_4642_);
lean_dec(v_k_4641_);
lean_dec(v_i_4640_);
lean_dec(v_m_4639_);
lean_dec(v_00_u03b2_4638_);
return v_res_4654_;
}
}
LEAN_EXPORT uint32_t lp_competition_ExactRuntime_gemmWith___at___00Submission_kernels_spec__1___lam__1(lean_object* v_00_u03b2_4655_, lean_object* v_k_4656_, lean_object* v_n_4657_, lean_object* v_j_4658_, uint32_t v___x_4659_, lean_object* v_B_4660_, lean_object* v_i_4661_){
_start:
{
lean_object* v___x_4662_; lean_object* v___x_4663_; lean_object* v___x_4664_; lean_object* v___x_4665_; lean_object* v___x_4666_; lean_object* v___x_4667_; uint32_t v___x_4668_; 
v___x_4662_ = lean_nat_mul(v_00_u03b2_4655_, v_k_4656_);
v___x_4663_ = lean_nat_add(v___x_4662_, v_i_4661_);
lean_dec(v___x_4662_);
v___x_4664_ = lean_nat_mul(v___x_4663_, v_n_4657_);
lean_dec(v___x_4663_);
v___x_4665_ = lean_nat_add(v___x_4664_, v_j_4658_);
lean_dec(v___x_4664_);
v___x_4666_ = lean_box_uint32(v___x_4659_);
v___x_4667_ = lean_array_get(v___x_4666_, v_B_4660_, v___x_4665_);
lean_dec(v___x_4665_);
lean_dec(v___x_4666_);
v___x_4668_ = lean_unbox_uint32(v___x_4667_);
lean_dec(v___x_4667_);
return v___x_4668_;
}
}
LEAN_EXPORT lean_object* lp_competition_ExactRuntime_gemmWith___at___00Submission_kernels_spec__1___lam__1___boxed(lean_object* v_00_u03b2_4669_, lean_object* v_k_4670_, lean_object* v_n_4671_, lean_object* v_j_4672_, lean_object* v___x_4673_, lean_object* v_B_4674_, lean_object* v_i_4675_){
_start:
{
uint32_t v___x_4654__boxed_4676_; uint32_t v_res_4677_; lean_object* v_r_4678_; 
v___x_4654__boxed_4676_ = lean_unbox_uint32(v___x_4673_);
lean_dec(v___x_4673_);
v_res_4677_ = lp_competition_ExactRuntime_gemmWith___at___00Submission_kernels_spec__1___lam__1(v_00_u03b2_4669_, v_k_4670_, v_n_4671_, v_j_4672_, v___x_4654__boxed_4676_, v_B_4674_, v_i_4675_);
lean_dec(v_i_4675_);
lean_dec_ref(v_B_4674_);
lean_dec(v_j_4672_);
lean_dec(v_n_4671_);
lean_dec(v_k_4670_);
lean_dec(v_00_u03b2_4669_);
v_r_4678_ = lean_box_uint32(v_res_4677_);
return v_r_4678_;
}
}
LEAN_EXPORT uint32_t lp_competition_ExactRuntime_gemmWith___at___00Submission_kernels_spec__1___lam__2(lean_object* v___x_4679_, lean_object* v_n_4680_, lean_object* v_m_4681_, lean_object* v_k_4682_, lean_object* v_A_4683_, lean_object* v_B_4684_, uint32_t v___x_4685_, lean_object* v_q_4686_){
_start:
{
lean_object* v_00_u03b2_4687_; lean_object* v___x_4688_; lean_object* v_i_4689_; lean_object* v_j_4690_; lean_object* v___x_4691_; lean_object* v___x_4692_; uint8_t v___x_4693_; uint8_t v___x_4694_; lean_object* v_acc_4695_; uint8_t v_special_4696_; 
v_00_u03b2_4687_ = lean_nat_div(v_q_4686_, v___x_4679_);
v___x_4688_ = lean_nat_div(v_q_4686_, v_n_4680_);
v_i_4689_ = lean_nat_mod(v___x_4688_, v_m_4681_);
lean_dec(v___x_4688_);
v_j_4690_ = lean_nat_mod(v_q_4686_, v_n_4680_);
v___x_4691_ = lean_unsigned_to_nat(0u);
v___x_4692_ = lean_obj_once(&lp_competition_Submission_Acc_empty___closed__0, &lp_competition_Submission_Acc_empty___closed__0_once, _init_lp_competition_Submission_Acc_empty___closed__0);
v___x_4693_ = 0;
v___x_4694_ = 1;
lean_inc(v_k_4682_);
v_acc_4695_ = lp_competition_Submission_dotLoop___at___00Submission_rmsnormCached_spec__0___at___00ExactRuntime_gemmWith___at___00Submission_kernels_spec__1_spec__2(v_00_u03b2_4687_, v_m_4681_, v_i_4689_, v_k_4682_, v_A_4683_, v_n_4680_, v_j_4690_, v_B_4684_, v___x_4692_, v___x_4692_, v___x_4693_, v___x_4694_, v___x_4691_, v_k_4682_);
v_special_4696_ = lean_ctor_get_uint8(v_acc_4695_, sizeof(void*)*2);
if (v_special_4696_ == 0)
{
lean_object* v_pos_4697_; lean_object* v_neg_4698_; uint8_t v_negZero_4699_; lean_object* v___x_4700_; uint8_t v___x_4701_; 
lean_dec(v_j_4690_);
lean_dec(v_i_4689_);
lean_dec(v_00_u03b2_4687_);
lean_dec_ref(v_B_4684_);
lean_dec_ref(v_A_4683_);
lean_dec(v_m_4681_);
lean_dec(v_n_4680_);
v_pos_4697_ = lean_ctor_get(v_acc_4695_, 0);
lean_inc_ref(v_pos_4697_);
v_neg_4698_ = lean_ctor_get(v_acc_4695_, 1);
lean_inc_ref(v_neg_4698_);
v_negZero_4699_ = lean_ctor_get_uint8(v_acc_4695_, sizeof(void*)*2 + 1);
lean_dec_ref(v_acc_4695_);
v___x_4700_ = lean_obj_once(&lp_competition_Submission_dotFn___closed__1, &lp_competition_Submission_dotFn___closed__1_once, _init_lp_competition_Submission_dotFn___closed__1);
v___x_4701_ = lean_nat_dec_eq(v_k_4682_, v___x_4691_);
lean_dec(v_k_4682_);
if (v___x_4701_ == 0)
{
uint32_t v___x_4702_; 
v___x_4702_ = lp_competition_Submission_finishFast(v_pos_4697_, v_neg_4698_, v___x_4700_, v_negZero_4699_);
lean_dec_ref(v_neg_4698_);
lean_dec_ref(v_pos_4697_);
return v___x_4702_;
}
else
{
uint32_t v___x_4703_; 
v___x_4703_ = lp_competition_Submission_finishFast(v_pos_4697_, v_neg_4698_, v___x_4700_, v___x_4693_);
lean_dec_ref(v_neg_4698_);
lean_dec_ref(v_pos_4697_);
return v___x_4703_;
}
}
else
{
lean_object* v___x_4704_; lean_object* v___f_4705_; lean_object* v___x_4706_; lean_object* v___f_4707_; lean_object* v___x_4708_; lean_object* v___x_4709_; uint32_t v___x_4710_; 
lean_dec_ref(v_acc_4695_);
v___x_4704_ = lean_box_uint32(v___x_4685_);
lean_inc_n(v_k_4682_, 3);
lean_inc(v_00_u03b2_4687_);
v___f_4705_ = lean_alloc_closure((void*)(lp_competition_ExactRuntime_gemmWith___at___00Submission_kernels_spec__1___lam__0___boxed), 7, 6);
lean_closure_set(v___f_4705_, 0, v_00_u03b2_4687_);
lean_closure_set(v___f_4705_, 1, v_m_4681_);
lean_closure_set(v___f_4705_, 2, v_i_4689_);
lean_closure_set(v___f_4705_, 3, v_k_4682_);
lean_closure_set(v___f_4705_, 4, v___x_4704_);
lean_closure_set(v___f_4705_, 5, v_A_4683_);
v___x_4706_ = lean_box_uint32(v___x_4685_);
v___f_4707_ = lean_alloc_closure((void*)(lp_competition_ExactRuntime_gemmWith___at___00Submission_kernels_spec__1___lam__1___boxed), 7, 6);
lean_closure_set(v___f_4707_, 0, v_00_u03b2_4687_);
lean_closure_set(v___f_4707_, 1, v_k_4682_);
lean_closure_set(v___f_4707_, 2, v_n_4680_);
lean_closure_set(v___f_4707_, 3, v_j_4690_);
lean_closure_set(v___f_4707_, 4, v___x_4706_);
lean_closure_set(v___f_4707_, 5, v_B_4684_);
v___x_4708_ = l_Array_ofFn___redArg(v_k_4682_, v___f_4705_);
v___x_4709_ = l_Array_ofFn___redArg(v_k_4682_, v___f_4707_);
v___x_4710_ = lp_competition_ExactRuntime_dotSpec(v___x_4708_, v___x_4709_);
return v___x_4710_;
}
}
}
LEAN_EXPORT lean_object* lp_competition_ExactRuntime_gemmWith___at___00Submission_kernels_spec__1___lam__2___boxed(lean_object* v___x_4711_, lean_object* v_n_4712_, lean_object* v_m_4713_, lean_object* v_k_4714_, lean_object* v_A_4715_, lean_object* v_B_4716_, lean_object* v___x_4717_, lean_object* v_q_4718_){
_start:
{
uint32_t v___x_4679__boxed_4719_; uint32_t v_res_4720_; lean_object* v_r_4721_; 
v___x_4679__boxed_4719_ = lean_unbox_uint32(v___x_4717_);
lean_dec(v___x_4717_);
v_res_4720_ = lp_competition_ExactRuntime_gemmWith___at___00Submission_kernels_spec__1___lam__2(v___x_4711_, v_n_4712_, v_m_4713_, v_k_4714_, v_A_4715_, v_B_4716_, v___x_4679__boxed_4719_, v_q_4718_);
lean_dec(v_q_4718_);
lean_dec(v___x_4711_);
v_r_4721_ = lean_box_uint32(v_res_4720_);
return v_r_4721_;
}
}
LEAN_EXPORT lean_object* lp_competition_ExactRuntime_gemmWith___at___00Submission_kernels_spec__1(lean_object* v_batch_4722_, lean_object* v_m_4723_, lean_object* v_k_4724_, lean_object* v_n_4725_, lean_object* v_A_4726_, lean_object* v_B_4727_){
_start:
{
lean_object* v___x_4728_; lean_object* v___x_4729_; lean_object* v___f_4730_; lean_object* v___x_4731_; lean_object* v___x_4732_; 
v___x_4728_ = lean_nat_mul(v_m_4723_, v_n_4725_);
v___x_4729_ = lp_competition_Submission_dotX___lam__0___boxed__const__1;
lean_inc(v___x_4728_);
v___f_4730_ = lean_alloc_closure((void*)(lp_competition_ExactRuntime_gemmWith___at___00Submission_kernels_spec__1___lam__2___boxed), 8, 7);
lean_closure_set(v___f_4730_, 0, v___x_4728_);
lean_closure_set(v___f_4730_, 1, v_n_4725_);
lean_closure_set(v___f_4730_, 2, v_m_4723_);
lean_closure_set(v___f_4730_, 3, v_k_4724_);
lean_closure_set(v___f_4730_, 4, v_A_4726_);
lean_closure_set(v___f_4730_, 5, v_B_4727_);
lean_closure_set(v___f_4730_, 6, v___x_4729_);
v___x_4731_ = lean_nat_mul(v_batch_4722_, v___x_4728_);
lean_dec(v___x_4728_);
v___x_4732_ = l_Array_ofFn___redArg(v___x_4731_, v___f_4730_);
return v___x_4732_;
}
}
LEAN_EXPORT lean_object* lp_competition_ExactRuntime_gemmWith___at___00Submission_kernels_spec__1___boxed(lean_object* v_batch_4733_, lean_object* v_m_4734_, lean_object* v_k_4735_, lean_object* v_n_4736_, lean_object* v_A_4737_, lean_object* v_B_4738_){
_start:
{
lean_object* v_res_4739_; 
v_res_4739_ = lp_competition_ExactRuntime_gemmWith___at___00Submission_kernels_spec__1(v_batch_4733_, v_m_4734_, v_k_4735_, v_n_4736_, v_A_4737_, v_B_4738_);
lean_dec(v_batch_4733_);
return v_res_4739_;
}
}
LEAN_EXPORT uint32_t lp_competition_ExactRuntime_linearWith___at___00Submission_kernels_spec__0___lam__1(lean_object* v_inW_4740_, lean_object* v_b_4741_, lean_object* v_j_4742_, lean_object* v_W_4743_, lean_object* v_i_4744_){
_start:
{
uint8_t v___x_4745_; 
v___x_4745_ = lean_nat_dec_lt(v_i_4744_, v_inW_4740_);
if (v___x_4745_ == 0)
{
lean_object* v___x_4746_; lean_object* v___x_4747_; uint32_t v___x_4748_; 
v___x_4746_ = lp_competition_Submission_dotX___lam__0___boxed__const__1;
v___x_4747_ = lean_array_get_borrowed(v___x_4746_, v_b_4741_, v_j_4742_);
v___x_4748_ = lean_unbox_uint32(v___x_4747_);
return v___x_4748_;
}
else
{
lean_object* v___x_4749_; lean_object* v___x_4750_; lean_object* v___x_4751_; lean_object* v___x_4752_; uint32_t v___x_4753_; 
v___x_4749_ = lean_nat_mul(v_j_4742_, v_inW_4740_);
v___x_4750_ = lean_nat_add(v___x_4749_, v_i_4744_);
lean_dec(v___x_4749_);
v___x_4751_ = lp_competition_Submission_dotX___lam__0___boxed__const__1;
v___x_4752_ = lean_array_get_borrowed(v___x_4751_, v_W_4743_, v___x_4750_);
lean_dec(v___x_4750_);
v___x_4753_ = lean_unbox_uint32(v___x_4752_);
return v___x_4753_;
}
}
}
LEAN_EXPORT lean_object* lp_competition_ExactRuntime_linearWith___at___00Submission_kernels_spec__0___lam__1___boxed(lean_object* v_inW_4754_, lean_object* v_b_4755_, lean_object* v_j_4756_, lean_object* v_W_4757_, lean_object* v_i_4758_){
_start:
{
uint32_t v_res_4759_; lean_object* v_r_4760_; 
v_res_4759_ = lp_competition_ExactRuntime_linearWith___at___00Submission_kernels_spec__0___lam__1(v_inW_4754_, v_b_4755_, v_j_4756_, v_W_4757_, v_i_4758_);
lean_dec(v_i_4758_);
lean_dec_ref(v_W_4757_);
lean_dec(v_j_4756_);
lean_dec_ref(v_b_4755_);
lean_dec(v_inW_4754_);
v_r_4760_ = lean_box_uint32(v_res_4759_);
return v_r_4760_;
}
}
LEAN_EXPORT uint32_t lp_competition_ExactRuntime_linearWith___at___00Submission_kernels_spec__0___lam__0(lean_object* v_inW_4761_, lean_object* v_i_4762_, lean_object* v_X_4763_, lean_object* v_i_4764_){
_start:
{
uint8_t v___x_4765_; 
v___x_4765_ = lean_nat_dec_lt(v_i_4764_, v_inW_4761_);
if (v___x_4765_ == 0)
{
uint32_t v___x_4766_; 
v___x_4766_ = 1065353216;
return v___x_4766_;
}
else
{
lean_object* v___x_4767_; lean_object* v___x_4768_; lean_object* v___x_4769_; lean_object* v___x_4770_; uint32_t v___x_4771_; 
v___x_4767_ = lean_nat_mul(v_i_4762_, v_inW_4761_);
v___x_4768_ = lean_nat_add(v___x_4767_, v_i_4764_);
lean_dec(v___x_4767_);
v___x_4769_ = lp_competition_Submission_dotX___lam__0___boxed__const__1;
v___x_4770_ = lean_array_get_borrowed(v___x_4769_, v_X_4763_, v___x_4768_);
lean_dec(v___x_4768_);
v___x_4771_ = lean_unbox_uint32(v___x_4770_);
return v___x_4771_;
}
}
}
LEAN_EXPORT lean_object* lp_competition_ExactRuntime_linearWith___at___00Submission_kernels_spec__0___lam__0___boxed(lean_object* v_inW_4772_, lean_object* v_i_4773_, lean_object* v_X_4774_, lean_object* v_i_4775_){
_start:
{
uint32_t v_res_4776_; lean_object* v_r_4777_; 
v_res_4776_ = lp_competition_ExactRuntime_linearWith___at___00Submission_kernels_spec__0___lam__0(v_inW_4772_, v_i_4773_, v_X_4774_, v_i_4775_);
lean_dec(v_i_4775_);
lean_dec_ref(v_X_4774_);
lean_dec(v_i_4773_);
lean_dec(v_inW_4772_);
v_r_4777_ = lean_box_uint32(v_res_4776_);
return v_r_4777_;
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_dotLoop___at___00Submission_rmsnormCached_spec__0___at___00ExactRuntime_linearWith___at___00Submission_kernels_spec__0_spec__0(lean_object* v_inW_4778_, lean_object* v_i_4779_, lean_object* v_X_4780_, lean_object* v_b_4781_, lean_object* v_j_4782_, lean_object* v_W_4783_, lean_object* v_pos_4784_, lean_object* v_neg_4785_, uint8_t v_sp_4786_, uint8_t v_nz_4787_, lean_object* v_index_4788_, lean_object* v_x_4789_){
_start:
{
lean_object* v_zero_4790_; uint8_t v_isZero_4791_; 
v_zero_4790_ = lean_unsigned_to_nat(0u);
v_isZero_4791_ = lean_nat_dec_eq(v_x_4789_, v_zero_4790_);
if (v_isZero_4791_ == 1)
{
lean_object* v___x_4792_; 
lean_dec(v_x_4789_);
lean_dec(v_index_4788_);
v___x_4792_ = lean_alloc_ctor(0, 2, 2);
lean_ctor_set(v___x_4792_, 0, v_pos_4784_);
lean_ctor_set(v___x_4792_, 1, v_neg_4785_);
lean_ctor_set_uint8(v___x_4792_, sizeof(void*)*2, v_sp_4786_);
lean_ctor_set_uint8(v___x_4792_, sizeof(void*)*2 + 1, v_nz_4787_);
return v___x_4792_;
}
else
{
lean_object* v_one_4793_; lean_object* v_n_4794_; lean_object* v_pos_4796_; lean_object* v_neg_4797_; uint8_t v_special_4798_; uint8_t v_negZero_4799_; lean_object* v___y_4805_; lean_object* v___y_4806_; uint8_t v___y_4807_; lean_object* v___y_4808_; lean_object* v___y_4809_; lean_object* v___y_4819_; lean_object* v___y_4820_; lean_object* v___y_4821_; lean_object* v___y_4822_; lean_object* v___y_4832_; lean_object* v___y_4833_; uint8_t v___y_4834_; lean_object* v___y_4881_; lean_object* v___y_4882_; lean_object* v___y_4885_; lean_object* v___y_4886_; uint8_t v___y_4887_; uint8_t v___y_4888_; uint8_t v___y_4889_; lean_object* v___y_4891_; lean_object* v___y_4892_; uint32_t v___y_4893_; uint8_t v___y_4894_; uint8_t v___y_4895_; lean_object* v___y_4902_; uint32_t v___y_4903_; uint32_t v___y_4904_; lean_object* v___y_4905_; uint8_t v___y_4906_; lean_object* v___y_4907_; lean_object* v___y_4915_; uint32_t v___y_4916_; uint32_t v___y_4917_; uint32_t v___y_4918_; uint32_t v___y_4919_; uint8_t v___y_4920_; lean_object* v___y_4921_; uint32_t v___y_4929_; uint32_t v___y_4930_; uint32_t v___y_4931_; uint32_t v___y_4932_; lean_object* v___y_4933_; uint32_t v___y_4934_; uint8_t v___y_4935_; lean_object* v___y_4936_; uint32_t v___y_4943_; uint32_t v___y_4944_; uint32_t v___y_4945_; uint32_t v___y_4946_; uint32_t v___y_4947_; uint8_t v___y_4948_; lean_object* v___y_4949_; uint32_t v___y_4963_; uint32_t v___y_4964_; uint32_t v___y_4965_; uint32_t v___y_4966_; uint8_t v___y_4967_; uint32_t v___y_4968_; uint32_t v___y_4983_; uint8_t v___x_4998_; 
v_one_4793_ = lean_unsigned_to_nat(1u);
v_n_4794_ = lean_nat_sub(v_x_4789_, v_one_4793_);
lean_dec(v_x_4789_);
v___x_4998_ = lean_nat_dec_lt(v_index_4788_, v_inW_4778_);
if (v___x_4998_ == 0)
{
uint32_t v___x_4999_; 
v___x_4999_ = 1065353216;
v___y_4983_ = v___x_4999_;
goto v___jp_4982_;
}
else
{
lean_object* v___x_5000_; lean_object* v___x_5001_; lean_object* v___x_5002_; lean_object* v___x_5003_; uint32_t v___x_5004_; 
v___x_5000_ = lean_nat_mul(v_i_4779_, v_inW_4778_);
v___x_5001_ = lean_nat_add(v___x_5000_, v_index_4788_);
lean_dec(v___x_5000_);
v___x_5002_ = lp_competition_Submission_dotX___lam__0___boxed__const__1;
v___x_5003_ = lean_array_get_borrowed(v___x_5002_, v_X_4780_, v___x_5001_);
lean_dec(v___x_5001_);
v___x_5004_ = lean_unbox_uint32(v___x_5003_);
v___y_4983_ = v___x_5004_;
goto v___jp_4982_;
}
v___jp_4795_:
{
lean_object* v___x_4800_; 
v___x_4800_ = lean_nat_add(v_index_4788_, v_one_4793_);
lean_dec(v_index_4788_);
v_pos_4784_ = v_pos_4796_;
v_neg_4785_ = v_neg_4797_;
v_sp_4786_ = v_special_4798_;
v_nz_4787_ = v_negZero_4799_;
v_index_4788_ = v___x_4800_;
v_x_4789_ = v_n_4794_;
goto _start;
}
v___jp_4802_:
{
uint8_t v___x_4803_; 
v___x_4803_ = 1;
v_pos_4796_ = v_pos_4784_;
v_neg_4797_ = v_neg_4785_;
v_special_4798_ = v___x_4803_;
v_negZero_4799_ = v_nz_4787_;
goto v___jp_4795_;
}
v___jp_4804_:
{
lean_object* v___x_4810_; lean_object* v___x_4811_; uint8_t v___x_4812_; 
v___x_4810_ = lean_nat_add(v___y_4805_, v___y_4806_);
lean_dec(v___y_4805_);
v___x_4811_ = lean_array_get_size(v___y_4809_);
v___x_4812_ = lean_nat_dec_lt(v___x_4810_, v___x_4811_);
if (v___x_4812_ == 0)
{
lean_dec(v___x_4810_);
lean_dec(v___y_4808_);
v_pos_4796_ = v___y_4809_;
v_neg_4797_ = v_neg_4785_;
v_special_4798_ = v_sp_4786_;
v_negZero_4799_ = v___y_4807_;
goto v___jp_4795_;
}
else
{
lean_object* v_v_4813_; lean_object* v___x_4814_; lean_object* v_xs_x27_4815_; lean_object* v___x_4816_; lean_object* v___x_4817_; 
v_v_4813_ = lean_array_fget(v___y_4809_, v___x_4810_);
v___x_4814_ = lean_box(0);
v_xs_x27_4815_ = lean_array_fset(v___y_4809_, v___x_4810_, v___x_4814_);
v___x_4816_ = lean_nat_add(v_v_4813_, v___y_4808_);
lean_dec(v___y_4808_);
lean_dec(v_v_4813_);
v___x_4817_ = lean_array_fset(v_xs_x27_4815_, v___x_4810_, v___x_4816_);
lean_dec(v___x_4810_);
v_pos_4796_ = v___x_4817_;
v_neg_4797_ = v_neg_4785_;
v_special_4798_ = v_sp_4786_;
v_negZero_4799_ = v___y_4807_;
goto v___jp_4795_;
}
}
v___jp_4818_:
{
lean_object* v___x_4823_; lean_object* v___x_4824_; uint8_t v___x_4825_; 
v___x_4823_ = lean_nat_add(v___y_4821_, v___y_4819_);
lean_dec(v___y_4821_);
v___x_4824_ = lean_array_get_size(v___y_4822_);
v___x_4825_ = lean_nat_dec_lt(v___x_4823_, v___x_4824_);
if (v___x_4825_ == 0)
{
lean_dec(v___x_4823_);
lean_dec(v___y_4820_);
v_pos_4796_ = v_pos_4784_;
v_neg_4797_ = v___y_4822_;
v_special_4798_ = v_sp_4786_;
v_negZero_4799_ = v_isZero_4791_;
goto v___jp_4795_;
}
else
{
lean_object* v_v_4826_; lean_object* v___x_4827_; lean_object* v_xs_x27_4828_; lean_object* v___x_4829_; lean_object* v___x_4830_; 
v_v_4826_ = lean_array_fget(v___y_4822_, v___x_4823_);
v___x_4827_ = lean_box(0);
v_xs_x27_4828_ = lean_array_fset(v___y_4822_, v___x_4823_, v___x_4827_);
v___x_4829_ = lean_nat_add(v_v_4826_, v___y_4820_);
lean_dec(v___y_4820_);
lean_dec(v_v_4826_);
v___x_4830_ = lean_array_fset(v_xs_x27_4828_, v___x_4823_, v___x_4829_);
lean_dec(v___x_4823_);
v_pos_4796_ = v_pos_4784_;
v_neg_4797_ = v___x_4830_;
v_special_4798_ = v_sp_4786_;
v_negZero_4799_ = v_isZero_4791_;
goto v___jp_4795_;
}
}
v___jp_4831_:
{
uint8_t v___x_4835_; 
v___x_4835_ = lean_nat_dec_eq(v___y_4832_, v_zero_4790_);
if (v___x_4835_ == 0)
{
if (v___y_4834_ == 0)
{
uint64_t v___x_4836_; lean_object* v___x_4837_; lean_object* v___x_4838_; lean_object* v_l_4839_; lean_object* v___x_4840_; uint64_t v_r_4841_; uint64_t v___x_4842_; uint64_t v___x_4843_; uint64_t v___x_4844_; uint64_t v___x_4845_; uint64_t v___x_4846_; uint64_t v___x_4847_; lean_object* v_hi_4848_; lean_object* v___x_4849_; uint8_t v___x_4850_; 
v___x_4836_ = lean_uint64_of_nat(v___y_4832_);
lean_dec(v___y_4832_);
v___x_4837_ = lean_unsigned_to_nat(32u);
v___x_4838_ = lean_unsigned_to_nat(5u);
v_l_4839_ = lean_nat_shiftr(v___y_4833_, v___x_4838_);
v___x_4840_ = lean_nat_mod(v___y_4833_, v___x_4837_);
lean_dec(v___y_4833_);
v_r_4841_ = lean_uint64_of_nat(v___x_4840_);
lean_dec(v___x_4840_);
v___x_4842_ = 1ULL;
v___x_4843_ = 32ULL;
v___x_4844_ = lean_uint64_sub(v___x_4843_, v_r_4841_);
v___x_4845_ = lean_uint64_shift_left(v___x_4842_, v___x_4844_);
v___x_4846_ = lean_uint64_mod(v___x_4836_, v___x_4845_);
v___x_4847_ = lean_uint64_shift_right(v___x_4836_, v___x_4844_);
v_hi_4848_ = lean_uint64_to_nat(v___x_4847_);
v___x_4849_ = lean_array_get_size(v_pos_4784_);
v___x_4850_ = lean_nat_dec_lt(v_l_4839_, v___x_4849_);
if (v___x_4850_ == 0)
{
v___y_4805_ = v_l_4839_;
v___y_4806_ = v_one_4793_;
v___y_4807_ = v___y_4834_;
v___y_4808_ = v_hi_4848_;
v___y_4809_ = v_pos_4784_;
goto v___jp_4804_;
}
else
{
uint64_t v___x_4851_; lean_object* v_lo_4852_; lean_object* v_v_4853_; lean_object* v___x_4854_; lean_object* v_xs_x27_4855_; lean_object* v___x_4856_; lean_object* v___x_4857_; 
v___x_4851_ = lean_uint64_shift_left(v___x_4846_, v_r_4841_);
v_lo_4852_ = lean_uint64_to_nat(v___x_4851_);
v_v_4853_ = lean_array_fget(v_pos_4784_, v_l_4839_);
v___x_4854_ = lean_box(0);
v_xs_x27_4855_ = lean_array_fset(v_pos_4784_, v_l_4839_, v___x_4854_);
v___x_4856_ = lean_nat_add(v_v_4853_, v_lo_4852_);
lean_dec(v_lo_4852_);
lean_dec(v_v_4853_);
v___x_4857_ = lean_array_fset(v_xs_x27_4855_, v_l_4839_, v___x_4856_);
v___y_4805_ = v_l_4839_;
v___y_4806_ = v_one_4793_;
v___y_4807_ = v___y_4834_;
v___y_4808_ = v_hi_4848_;
v___y_4809_ = v___x_4857_;
goto v___jp_4804_;
}
}
else
{
uint64_t v___x_4858_; lean_object* v___x_4859_; lean_object* v___x_4860_; lean_object* v_l_4861_; lean_object* v___x_4862_; uint64_t v_r_4863_; uint64_t v___x_4864_; uint64_t v___x_4865_; uint64_t v___x_4866_; uint64_t v___x_4867_; uint64_t v___x_4868_; uint64_t v___x_4869_; lean_object* v_hi_4870_; lean_object* v___x_4871_; uint8_t v___x_4872_; 
v___x_4858_ = lean_uint64_of_nat(v___y_4832_);
lean_dec(v___y_4832_);
v___x_4859_ = lean_unsigned_to_nat(32u);
v___x_4860_ = lean_unsigned_to_nat(5u);
v_l_4861_ = lean_nat_shiftr(v___y_4833_, v___x_4860_);
v___x_4862_ = lean_nat_mod(v___y_4833_, v___x_4859_);
lean_dec(v___y_4833_);
v_r_4863_ = lean_uint64_of_nat(v___x_4862_);
lean_dec(v___x_4862_);
v___x_4864_ = 1ULL;
v___x_4865_ = 32ULL;
v___x_4866_ = lean_uint64_sub(v___x_4865_, v_r_4863_);
v___x_4867_ = lean_uint64_shift_left(v___x_4864_, v___x_4866_);
v___x_4868_ = lean_uint64_mod(v___x_4858_, v___x_4867_);
v___x_4869_ = lean_uint64_shift_right(v___x_4858_, v___x_4866_);
v_hi_4870_ = lean_uint64_to_nat(v___x_4869_);
v___x_4871_ = lean_array_get_size(v_neg_4785_);
v___x_4872_ = lean_nat_dec_lt(v_l_4861_, v___x_4871_);
if (v___x_4872_ == 0)
{
v___y_4819_ = v_one_4793_;
v___y_4820_ = v_hi_4870_;
v___y_4821_ = v_l_4861_;
v___y_4822_ = v_neg_4785_;
goto v___jp_4818_;
}
else
{
uint64_t v___x_4873_; lean_object* v_lo_4874_; lean_object* v_v_4875_; lean_object* v___x_4876_; lean_object* v_xs_x27_4877_; lean_object* v___x_4878_; lean_object* v___x_4879_; 
v___x_4873_ = lean_uint64_shift_left(v___x_4868_, v_r_4863_);
v_lo_4874_ = lean_uint64_to_nat(v___x_4873_);
v_v_4875_ = lean_array_fget(v_neg_4785_, v_l_4861_);
v___x_4876_ = lean_box(0);
v_xs_x27_4877_ = lean_array_fset(v_neg_4785_, v_l_4861_, v___x_4876_);
v___x_4878_ = lean_nat_add(v_v_4875_, v_lo_4874_);
lean_dec(v_lo_4874_);
lean_dec(v_v_4875_);
v___x_4879_ = lean_array_fset(v_xs_x27_4877_, v_l_4861_, v___x_4878_);
v___y_4819_ = v_one_4793_;
v___y_4820_ = v_hi_4870_;
v___y_4821_ = v_l_4861_;
v___y_4822_ = v___x_4879_;
goto v___jp_4818_;
}
}
}
else
{
lean_dec(v___y_4833_);
lean_dec(v___y_4832_);
if (v_nz_4787_ == 0)
{
v_pos_4796_ = v_pos_4784_;
v_neg_4797_ = v_neg_4785_;
v_special_4798_ = v_sp_4786_;
v_negZero_4799_ = v_nz_4787_;
goto v___jp_4795_;
}
else
{
v_pos_4796_ = v_pos_4784_;
v_neg_4797_ = v_neg_4785_;
v_special_4798_ = v_sp_4786_;
v_negZero_4799_ = v___y_4834_;
goto v___jp_4795_;
}
}
}
v___jp_4880_:
{
uint8_t v___x_4883_; 
v___x_4883_ = 1;
v___y_4832_ = v___y_4881_;
v___y_4833_ = v___y_4882_;
v___y_4834_ = v___x_4883_;
goto v___jp_4831_;
}
v___jp_4884_:
{
if (v___y_4887_ == 0)
{
if (v___y_4889_ == 0)
{
v___y_4832_ = v___y_4885_;
v___y_4833_ = v___y_4886_;
v___y_4834_ = v___y_4888_;
goto v___jp_4831_;
}
else
{
v___y_4881_ = v___y_4885_;
v___y_4882_ = v___y_4886_;
goto v___jp_4880_;
}
}
else
{
if (v___y_4889_ == 0)
{
v___y_4881_ = v___y_4885_;
v___y_4882_ = v___y_4886_;
goto v___jp_4880_;
}
else
{
v___y_4832_ = v___y_4885_;
v___y_4833_ = v___y_4886_;
v___y_4834_ = v___y_4888_;
goto v___jp_4831_;
}
}
}
v___jp_4890_:
{
uint32_t v___x_4896_; uint32_t v___x_4897_; uint32_t v___x_4898_; uint8_t v___x_4899_; 
v___x_4896_ = 2147483648;
v___x_4897_ = lean_uint32_land(v___y_4893_, v___x_4896_);
v___x_4898_ = 0;
v___x_4899_ = lean_uint32_dec_eq(v___x_4897_, v___x_4898_);
if (v___x_4899_ == 0)
{
uint8_t v___x_4900_; 
v___x_4900_ = 1;
v___y_4885_ = v___y_4891_;
v___y_4886_ = v___y_4892_;
v___y_4887_ = v___y_4895_;
v___y_4888_ = v___y_4894_;
v___y_4889_ = v___x_4900_;
goto v___jp_4884_;
}
else
{
v___y_4885_ = v___y_4891_;
v___y_4886_ = v___y_4892_;
v___y_4887_ = v___y_4895_;
v___y_4888_ = v___y_4894_;
v___y_4889_ = v___y_4894_;
goto v___jp_4884_;
}
}
v___jp_4901_:
{
lean_object* v___x_4908_; uint32_t v___x_4909_; uint32_t v___x_4910_; uint32_t v___x_4911_; uint8_t v___x_4912_; 
v___x_4908_ = lean_nat_add(v___y_4905_, v___y_4907_);
lean_dec(v___y_4907_);
lean_dec(v___y_4905_);
v___x_4909_ = 2147483648;
v___x_4910_ = lean_uint32_land(v___y_4904_, v___x_4909_);
v___x_4911_ = 0;
v___x_4912_ = lean_uint32_dec_eq(v___x_4910_, v___x_4911_);
if (v___x_4912_ == 0)
{
uint8_t v___x_4913_; 
v___x_4913_ = 1;
v___y_4891_ = v___y_4902_;
v___y_4892_ = v___x_4908_;
v___y_4893_ = v___y_4903_;
v___y_4894_ = v___y_4906_;
v___y_4895_ = v___x_4913_;
goto v___jp_4890_;
}
else
{
v___y_4891_ = v___y_4902_;
v___y_4892_ = v___x_4908_;
v___y_4893_ = v___y_4903_;
v___y_4894_ = v___y_4906_;
v___y_4895_ = v___y_4906_;
goto v___jp_4890_;
}
}
v___jp_4914_:
{
uint32_t v___x_4922_; uint32_t v___x_4923_; uint32_t v___x_4924_; uint8_t v___x_4925_; 
v___x_4922_ = lean_uint32_shift_right(v___y_4918_, v___y_4916_);
v___x_4923_ = lean_uint32_land(v___x_4922_, v___y_4917_);
v___x_4924_ = 0;
v___x_4925_ = lean_uint32_dec_eq(v___x_4923_, v___x_4924_);
if (v___x_4925_ == 0)
{
lean_object* v___x_4926_; lean_object* v___x_4927_; 
v___x_4926_ = lean_uint32_to_nat(v___x_4923_);
v___x_4927_ = lean_nat_sub(v___x_4926_, v_one_4793_);
lean_dec(v___x_4926_);
v___y_4902_ = v___y_4915_;
v___y_4903_ = v___y_4918_;
v___y_4904_ = v___y_4919_;
v___y_4905_ = v___y_4921_;
v___y_4906_ = v___y_4920_;
v___y_4907_ = v___x_4927_;
goto v___jp_4901_;
}
else
{
v___y_4902_ = v___y_4915_;
v___y_4903_ = v___y_4918_;
v___y_4904_ = v___y_4919_;
v___y_4905_ = v___y_4921_;
v___y_4906_ = v___y_4920_;
v___y_4907_ = v_zero_4790_;
goto v___jp_4901_;
}
}
v___jp_4928_:
{
lean_object* v___x_4937_; uint32_t v___x_4938_; uint8_t v___x_4939_; 
v___x_4937_ = lean_nat_mul(v___y_4933_, v___y_4936_);
lean_dec(v___y_4936_);
lean_dec(v___y_4933_);
v___x_4938_ = 0;
v___x_4939_ = lean_uint32_dec_eq(v___y_4929_, v___x_4938_);
if (v___x_4939_ == 0)
{
lean_object* v___x_4940_; lean_object* v___x_4941_; 
v___x_4940_ = lean_uint32_to_nat(v___y_4929_);
v___x_4941_ = lean_nat_sub(v___x_4940_, v_one_4793_);
lean_dec(v___x_4940_);
v___y_4915_ = v___x_4937_;
v___y_4916_ = v___y_4930_;
v___y_4917_ = v___y_4932_;
v___y_4918_ = v___y_4931_;
v___y_4919_ = v___y_4934_;
v___y_4920_ = v___y_4935_;
v___y_4921_ = v___x_4941_;
goto v___jp_4914_;
}
else
{
v___y_4915_ = v___x_4937_;
v___y_4916_ = v___y_4930_;
v___y_4917_ = v___y_4932_;
v___y_4918_ = v___y_4931_;
v___y_4919_ = v___y_4934_;
v___y_4920_ = v___y_4935_;
v___y_4921_ = v_zero_4790_;
goto v___jp_4914_;
}
}
v___jp_4942_:
{
uint32_t v___x_4950_; uint32_t v___x_4951_; uint32_t v___x_4952_; uint8_t v___x_4953_; 
v___x_4950_ = lean_uint32_shift_right(v___y_4946_, v___y_4944_);
v___x_4951_ = lean_uint32_land(v___x_4950_, v___y_4945_);
v___x_4952_ = 0;
v___x_4953_ = lean_uint32_dec_eq(v___x_4951_, v___x_4952_);
if (v___x_4953_ == 0)
{
lean_object* v___x_4954_; uint32_t v___x_4955_; uint32_t v___x_4956_; lean_object* v___x_4957_; lean_object* v___x_4958_; 
v___x_4954_ = lean_unsigned_to_nat(8388608u);
v___x_4955_ = 8388607;
v___x_4956_ = lean_uint32_land(v___y_4946_, v___x_4955_);
v___x_4957_ = lean_uint32_to_nat(v___x_4956_);
v___x_4958_ = lean_nat_add(v___x_4954_, v___x_4957_);
lean_dec(v___x_4957_);
v___y_4929_ = v___y_4943_;
v___y_4930_ = v___y_4944_;
v___y_4931_ = v___y_4946_;
v___y_4932_ = v___y_4945_;
v___y_4933_ = v___y_4949_;
v___y_4934_ = v___y_4947_;
v___y_4935_ = v___y_4948_;
v___y_4936_ = v___x_4958_;
goto v___jp_4928_;
}
else
{
uint32_t v___x_4959_; uint32_t v___x_4960_; lean_object* v___x_4961_; 
v___x_4959_ = 8388607;
v___x_4960_ = lean_uint32_land(v___y_4946_, v___x_4959_);
v___x_4961_ = lean_uint32_to_nat(v___x_4960_);
v___y_4929_ = v___y_4943_;
v___y_4930_ = v___y_4944_;
v___y_4931_ = v___y_4946_;
v___y_4932_ = v___y_4945_;
v___y_4933_ = v___y_4949_;
v___y_4934_ = v___y_4947_;
v___y_4935_ = v___y_4948_;
v___y_4936_ = v___x_4961_;
goto v___jp_4928_;
}
}
v___jp_4962_:
{
uint32_t v___x_4969_; uint32_t v___x_4970_; uint8_t v___x_4971_; 
v___x_4969_ = lean_uint32_shift_right(v___y_4968_, v___y_4964_);
v___x_4970_ = lean_uint32_land(v___x_4969_, v___y_4965_);
v___x_4971_ = lean_uint32_dec_eq(v___x_4970_, v___y_4965_);
if (v___x_4971_ == 0)
{
uint32_t v___x_4972_; uint8_t v___x_4973_; 
v___x_4972_ = 0;
v___x_4973_ = lean_uint32_dec_eq(v___y_4963_, v___x_4972_);
if (v___x_4973_ == 0)
{
lean_object* v___x_4974_; uint32_t v___x_4975_; uint32_t v___x_4976_; lean_object* v___x_4977_; lean_object* v___x_4978_; 
v___x_4974_ = lean_unsigned_to_nat(8388608u);
v___x_4975_ = 8388607;
v___x_4976_ = lean_uint32_land(v___y_4966_, v___x_4975_);
v___x_4977_ = lean_uint32_to_nat(v___x_4976_);
v___x_4978_ = lean_nat_add(v___x_4974_, v___x_4977_);
lean_dec(v___x_4977_);
v___y_4943_ = v___y_4963_;
v___y_4944_ = v___y_4964_;
v___y_4945_ = v___y_4965_;
v___y_4946_ = v___y_4968_;
v___y_4947_ = v___y_4966_;
v___y_4948_ = v___y_4967_;
v___y_4949_ = v___x_4978_;
goto v___jp_4942_;
}
else
{
uint32_t v___x_4979_; uint32_t v___x_4980_; lean_object* v___x_4981_; 
v___x_4979_ = 8388607;
v___x_4980_ = lean_uint32_land(v___y_4966_, v___x_4979_);
v___x_4981_ = lean_uint32_to_nat(v___x_4980_);
v___y_4943_ = v___y_4963_;
v___y_4944_ = v___y_4964_;
v___y_4945_ = v___y_4965_;
v___y_4946_ = v___y_4968_;
v___y_4947_ = v___y_4966_;
v___y_4948_ = v___y_4967_;
v___y_4949_ = v___x_4981_;
goto v___jp_4942_;
}
}
else
{
goto v___jp_4802_;
}
}
v___jp_4982_:
{
uint32_t v___x_4984_; uint32_t v___x_4985_; uint32_t v___x_4986_; uint32_t v___x_4987_; uint8_t v___x_4988_; 
v___x_4984_ = 23;
v___x_4985_ = lean_uint32_shift_right(v___y_4983_, v___x_4984_);
v___x_4986_ = 255;
v___x_4987_ = lean_uint32_land(v___x_4985_, v___x_4986_);
v___x_4988_ = lean_uint32_dec_eq(v___x_4987_, v___x_4986_);
if (v___x_4988_ == 0)
{
uint8_t v___x_4989_; 
v___x_4989_ = lean_nat_dec_lt(v_index_4788_, v_inW_4778_);
if (v___x_4989_ == 0)
{
lean_object* v___x_4990_; lean_object* v___x_4991_; uint32_t v___x_4992_; 
v___x_4990_ = lp_competition_Submission_dotX___lam__0___boxed__const__1;
v___x_4991_ = lean_array_get_borrowed(v___x_4990_, v_b_4781_, v_j_4782_);
v___x_4992_ = lean_unbox_uint32(v___x_4991_);
v___y_4963_ = v___x_4987_;
v___y_4964_ = v___x_4984_;
v___y_4965_ = v___x_4986_;
v___y_4966_ = v___y_4983_;
v___y_4967_ = v___x_4988_;
v___y_4968_ = v___x_4992_;
goto v___jp_4962_;
}
else
{
lean_object* v___x_4993_; lean_object* v___x_4994_; lean_object* v___x_4995_; lean_object* v___x_4996_; uint32_t v___x_4997_; 
v___x_4993_ = lean_nat_mul(v_j_4782_, v_inW_4778_);
v___x_4994_ = lean_nat_add(v___x_4993_, v_index_4788_);
lean_dec(v___x_4993_);
v___x_4995_ = lp_competition_Submission_dotX___lam__0___boxed__const__1;
v___x_4996_ = lean_array_get_borrowed(v___x_4995_, v_W_4783_, v___x_4994_);
lean_dec(v___x_4994_);
v___x_4997_ = lean_unbox_uint32(v___x_4996_);
v___y_4963_ = v___x_4987_;
v___y_4964_ = v___x_4984_;
v___y_4965_ = v___x_4986_;
v___y_4966_ = v___y_4983_;
v___y_4967_ = v___x_4988_;
v___y_4968_ = v___x_4997_;
goto v___jp_4962_;
}
}
else
{
goto v___jp_4802_;
}
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_dotLoop___at___00Submission_rmsnormCached_spec__0___at___00ExactRuntime_linearWith___at___00Submission_kernels_spec__0_spec__0___boxed(lean_object* v_inW_5005_, lean_object* v_i_5006_, lean_object* v_X_5007_, lean_object* v_b_5008_, lean_object* v_j_5009_, lean_object* v_W_5010_, lean_object* v_pos_5011_, lean_object* v_neg_5012_, lean_object* v_sp_5013_, lean_object* v_nz_5014_, lean_object* v_index_5015_, lean_object* v_x_5016_){
_start:
{
uint8_t v_sp_boxed_5017_; uint8_t v_nz_boxed_5018_; lean_object* v_res_5019_; 
v_sp_boxed_5017_ = lean_unbox(v_sp_5013_);
v_nz_boxed_5018_ = lean_unbox(v_nz_5014_);
v_res_5019_ = lp_competition_Submission_dotLoop___at___00Submission_rmsnormCached_spec__0___at___00ExactRuntime_linearWith___at___00Submission_kernels_spec__0_spec__0(v_inW_5005_, v_i_5006_, v_X_5007_, v_b_5008_, v_j_5009_, v_W_5010_, v_pos_5011_, v_neg_5012_, v_sp_boxed_5017_, v_nz_boxed_5018_, v_index_5015_, v_x_5016_);
lean_dec_ref(v_W_5010_);
lean_dec(v_j_5009_);
lean_dec_ref(v_b_5008_);
lean_dec_ref(v_X_5007_);
lean_dec(v_i_5006_);
lean_dec(v_inW_5005_);
return v_res_5019_;
}
}
LEAN_EXPORT uint32_t lp_competition_ExactRuntime_linearWith___at___00Submission_kernels_spec__0___lam__2(lean_object* v_outW_5020_, lean_object* v_inW_5021_, lean_object* v_X_5022_, lean_object* v_b_5023_, lean_object* v_W_5024_, uint8_t v_relu_5025_, lean_object* v_q_5026_){
_start:
{
uint32_t v___y_5028_; lean_object* v_i_5041_; lean_object* v_j_5042_; lean_object* v___x_5043_; lean_object* v___x_5044_; lean_object* v___x_5045_; lean_object* v___x_5046_; uint8_t v___x_5047_; uint8_t v___x_5048_; lean_object* v_acc_5049_; uint8_t v_special_5050_; 
v_i_5041_ = lean_nat_div(v_q_5026_, v_outW_5020_);
v_j_5042_ = lean_nat_mod(v_q_5026_, v_outW_5020_);
v___x_5043_ = lean_unsigned_to_nat(1u);
v___x_5044_ = lean_nat_add(v_inW_5021_, v___x_5043_);
v___x_5045_ = lean_unsigned_to_nat(0u);
v___x_5046_ = lean_obj_once(&lp_competition_Submission_Acc_empty___closed__0, &lp_competition_Submission_Acc_empty___closed__0_once, _init_lp_competition_Submission_Acc_empty___closed__0);
v___x_5047_ = 0;
v___x_5048_ = 1;
lean_inc(v___x_5044_);
v_acc_5049_ = lp_competition_Submission_dotLoop___at___00Submission_rmsnormCached_spec__0___at___00ExactRuntime_linearWith___at___00Submission_kernels_spec__0_spec__0(v_inW_5021_, v_i_5041_, v_X_5022_, v_b_5023_, v_j_5042_, v_W_5024_, v___x_5046_, v___x_5046_, v___x_5047_, v___x_5048_, v___x_5045_, v___x_5044_);
v_special_5050_ = lean_ctor_get_uint8(v_acc_5049_, sizeof(void*)*2);
if (v_special_5050_ == 0)
{
lean_object* v_pos_5051_; lean_object* v_neg_5052_; uint8_t v_negZero_5053_; lean_object* v___x_5054_; uint8_t v___x_5055_; 
lean_dec(v_j_5042_);
lean_dec(v_i_5041_);
lean_dec_ref(v_W_5024_);
lean_dec_ref(v_b_5023_);
lean_dec_ref(v_X_5022_);
lean_dec(v_inW_5021_);
v_pos_5051_ = lean_ctor_get(v_acc_5049_, 0);
lean_inc_ref(v_pos_5051_);
v_neg_5052_ = lean_ctor_get(v_acc_5049_, 1);
lean_inc_ref(v_neg_5052_);
v_negZero_5053_ = lean_ctor_get_uint8(v_acc_5049_, sizeof(void*)*2 + 1);
lean_dec_ref(v_acc_5049_);
v___x_5054_ = lean_obj_once(&lp_competition_Submission_dotFn___closed__1, &lp_competition_Submission_dotFn___closed__1_once, _init_lp_competition_Submission_dotFn___closed__1);
v___x_5055_ = lean_nat_dec_eq(v___x_5044_, v___x_5045_);
lean_dec(v___x_5044_);
if (v___x_5055_ == 0)
{
uint32_t v___x_5056_; 
v___x_5056_ = lp_competition_Submission_finishFast(v_pos_5051_, v_neg_5052_, v___x_5054_, v_negZero_5053_);
lean_dec_ref(v_neg_5052_);
lean_dec_ref(v_pos_5051_);
v___y_5028_ = v___x_5056_;
goto v___jp_5027_;
}
else
{
uint32_t v___x_5057_; 
v___x_5057_ = lp_competition_Submission_finishFast(v_pos_5051_, v_neg_5052_, v___x_5054_, v___x_5047_);
lean_dec_ref(v_neg_5052_);
lean_dec_ref(v_pos_5051_);
v___y_5028_ = v___x_5057_;
goto v___jp_5027_;
}
}
else
{
lean_object* v___f_5058_; lean_object* v___f_5059_; lean_object* v___x_5060_; lean_object* v___x_5061_; uint32_t v___x_5062_; 
lean_dec_ref(v_acc_5049_);
lean_inc(v_inW_5021_);
v___f_5058_ = lean_alloc_closure((void*)(lp_competition_ExactRuntime_linearWith___at___00Submission_kernels_spec__0___lam__0___boxed), 4, 3);
lean_closure_set(v___f_5058_, 0, v_inW_5021_);
lean_closure_set(v___f_5058_, 1, v_i_5041_);
lean_closure_set(v___f_5058_, 2, v_X_5022_);
v___f_5059_ = lean_alloc_closure((void*)(lp_competition_ExactRuntime_linearWith___at___00Submission_kernels_spec__0___lam__1___boxed), 5, 4);
lean_closure_set(v___f_5059_, 0, v_inW_5021_);
lean_closure_set(v___f_5059_, 1, v_b_5023_);
lean_closure_set(v___f_5059_, 2, v_j_5042_);
lean_closure_set(v___f_5059_, 3, v_W_5024_);
lean_inc(v___x_5044_);
v___x_5060_ = l_Array_ofFn___redArg(v___x_5044_, v___f_5058_);
v___x_5061_ = l_Array_ofFn___redArg(v___x_5044_, v___f_5059_);
v___x_5062_ = lp_competition_ExactRuntime_dotSpec(v___x_5060_, v___x_5061_);
v___y_5028_ = v___x_5062_;
goto v___jp_5027_;
}
v___jp_5027_:
{
if (v_relu_5025_ == 0)
{
return v___y_5028_;
}
else
{
uint32_t v___x_5029_; uint32_t v___x_5030_; uint32_t v___x_5031_; uint8_t v___x_5032_; 
v___x_5029_ = 2147483648;
v___x_5030_ = lean_uint32_land(v___y_5028_, v___x_5029_);
v___x_5031_ = 0;
v___x_5032_ = lean_uint32_dec_eq(v___x_5030_, v___x_5031_);
if (v___x_5032_ == 0)
{
uint32_t v___x_5033_; uint32_t v___x_5034_; uint32_t v___x_5035_; uint32_t v___x_5036_; uint8_t v___x_5037_; 
v___x_5033_ = 23;
v___x_5034_ = lean_uint32_shift_right(v___y_5028_, v___x_5033_);
v___x_5035_ = 255;
v___x_5036_ = lean_uint32_land(v___x_5034_, v___x_5035_);
v___x_5037_ = lean_uint32_dec_eq(v___x_5036_, v___x_5035_);
if (v___x_5037_ == 0)
{
if (v___x_5037_ == 0)
{
return v___x_5031_;
}
else
{
return v___y_5028_;
}
}
else
{
uint32_t v___x_5038_; uint32_t v___x_5039_; uint8_t v___x_5040_; 
v___x_5038_ = 8388607;
v___x_5039_ = lean_uint32_land(v___y_5028_, v___x_5038_);
v___x_5040_ = lean_uint32_dec_eq(v___x_5039_, v___x_5031_);
if (v___x_5040_ == 0)
{
if (v___x_5037_ == 0)
{
return v___x_5031_;
}
else
{
return v___y_5028_;
}
}
else
{
return v___x_5031_;
}
}
}
else
{
return v___y_5028_;
}
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_ExactRuntime_linearWith___at___00Submission_kernels_spec__0___lam__2___boxed(lean_object* v_outW_5063_, lean_object* v_inW_5064_, lean_object* v_X_5065_, lean_object* v_b_5066_, lean_object* v_W_5067_, lean_object* v_relu_5068_, lean_object* v_q_5069_){
_start:
{
uint8_t v_relu_boxed_5070_; uint32_t v_res_5071_; lean_object* v_r_5072_; 
v_relu_boxed_5070_ = lean_unbox(v_relu_5068_);
v_res_5071_ = lp_competition_ExactRuntime_linearWith___at___00Submission_kernels_spec__0___lam__2(v_outW_5063_, v_inW_5064_, v_X_5065_, v_b_5066_, v_W_5067_, v_relu_boxed_5070_, v_q_5069_);
lean_dec(v_q_5069_);
lean_dec(v_outW_5063_);
v_r_5072_ = lean_box_uint32(v_res_5071_);
return v_r_5072_;
}
}
LEAN_EXPORT lean_object* lp_competition_ExactRuntime_linearWith___at___00Submission_kernels_spec__0(lean_object* v_rows_5073_, lean_object* v_inW_5074_, lean_object* v_outW_5075_, uint8_t v_relu_5076_, lean_object* v_X_5077_, lean_object* v_W_5078_, lean_object* v_b_5079_){
_start:
{
lean_object* v___x_5080_; lean_object* v___f_5081_; lean_object* v___x_5082_; lean_object* v___x_5083_; 
v___x_5080_ = lean_box(v_relu_5076_);
lean_inc(v_outW_5075_);
v___f_5081_ = lean_alloc_closure((void*)(lp_competition_ExactRuntime_linearWith___at___00Submission_kernels_spec__0___lam__2___boxed), 7, 6);
lean_closure_set(v___f_5081_, 0, v_outW_5075_);
lean_closure_set(v___f_5081_, 1, v_inW_5074_);
lean_closure_set(v___f_5081_, 2, v_X_5077_);
lean_closure_set(v___f_5081_, 3, v_b_5079_);
lean_closure_set(v___f_5081_, 4, v_W_5078_);
lean_closure_set(v___f_5081_, 5, v___x_5080_);
v___x_5082_ = lean_nat_mul(v_rows_5073_, v_outW_5075_);
lean_dec(v_outW_5075_);
v___x_5083_ = l_Array_ofFn___redArg(v___x_5082_, v___f_5081_);
return v___x_5083_;
}
}
LEAN_EXPORT lean_object* lp_competition_ExactRuntime_linearWith___at___00Submission_kernels_spec__0___boxed(lean_object* v_rows_5084_, lean_object* v_inW_5085_, lean_object* v_outW_5086_, lean_object* v_relu_5087_, lean_object* v_X_5088_, lean_object* v_W_5089_, lean_object* v_b_5090_){
_start:
{
uint8_t v_relu_boxed_5091_; lean_object* v_res_5092_; 
v_relu_boxed_5091_ = lean_unbox(v_relu_5087_);
v_res_5092_ = lp_competition_ExactRuntime_linearWith___at___00Submission_kernels_spec__0(v_rows_5084_, v_inW_5085_, v_outW_5086_, v_relu_boxed_5091_, v_X_5088_, v_W_5089_, v_b_5090_);
lean_dec(v_rows_5084_);
return v_res_5092_;
}
}
LEAN_EXPORT uint32_t lp_competition_ExactRuntime_avgpoolWith___at___00Submission_kernels_spec__4___lam__1(lean_object* v_ch_5093_, lean_object* v_h_5094_, lean_object* v_y_5095_, lean_object* v_k_5096_, lean_object* v_w_5097_, lean_object* v_x_5098_, lean_object* v_inp_5099_, lean_object* v_i_5100_){
_start:
{
lean_object* v___x_5101_; lean_object* v___x_5102_; lean_object* v___x_5103_; lean_object* v___x_5104_; lean_object* v___x_5105_; lean_object* v___x_5106_; lean_object* v___x_5107_; lean_object* v___x_5108_; lean_object* v___x_5109_; lean_object* v___x_5110_; lean_object* v___x_5111_; lean_object* v___x_5112_; uint32_t v___x_5113_; 
v___x_5101_ = lean_nat_mul(v_ch_5093_, v_h_5094_);
v___x_5102_ = lean_nat_mul(v_y_5095_, v_k_5096_);
v___x_5103_ = lean_nat_add(v___x_5101_, v___x_5102_);
lean_dec(v___x_5102_);
lean_dec(v___x_5101_);
v___x_5104_ = lean_nat_div(v_i_5100_, v_k_5096_);
v___x_5105_ = lean_nat_add(v___x_5103_, v___x_5104_);
lean_dec(v___x_5104_);
lean_dec(v___x_5103_);
v___x_5106_ = lean_nat_mul(v___x_5105_, v_w_5097_);
lean_dec(v___x_5105_);
v___x_5107_ = lean_nat_mul(v_x_5098_, v_k_5096_);
v___x_5108_ = lean_nat_add(v___x_5106_, v___x_5107_);
lean_dec(v___x_5107_);
lean_dec(v___x_5106_);
v___x_5109_ = lean_nat_mod(v_i_5100_, v_k_5096_);
v___x_5110_ = lean_nat_add(v___x_5108_, v___x_5109_);
lean_dec(v___x_5109_);
lean_dec(v___x_5108_);
v___x_5111_ = lp_competition_Submission_dotX___lam__0___boxed__const__1;
v___x_5112_ = lean_array_get_borrowed(v___x_5111_, v_inp_5099_, v___x_5110_);
lean_dec(v___x_5110_);
v___x_5113_ = lean_unbox_uint32(v___x_5112_);
return v___x_5113_;
}
}
LEAN_EXPORT lean_object* lp_competition_ExactRuntime_avgpoolWith___at___00Submission_kernels_spec__4___lam__1___boxed(lean_object* v_ch_5114_, lean_object* v_h_5115_, lean_object* v_y_5116_, lean_object* v_k_5117_, lean_object* v_w_5118_, lean_object* v_x_5119_, lean_object* v_inp_5120_, lean_object* v_i_5121_){
_start:
{
uint32_t v_res_5122_; lean_object* v_r_5123_; 
v_res_5122_ = lp_competition_ExactRuntime_avgpoolWith___at___00Submission_kernels_spec__4___lam__1(v_ch_5114_, v_h_5115_, v_y_5116_, v_k_5117_, v_w_5118_, v_x_5119_, v_inp_5120_, v_i_5121_);
lean_dec(v_i_5121_);
lean_dec_ref(v_inp_5120_);
lean_dec(v_x_5119_);
lean_dec(v_w_5118_);
lean_dec(v_k_5117_);
lean_dec(v_y_5116_);
lean_dec(v_h_5115_);
lean_dec(v_ch_5114_);
v_r_5123_ = lean_box_uint32(v_res_5122_);
return v_r_5123_;
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_dotLoop___at___00Submission_rmsnormCached_spec__0___at___00ExactRuntime_avgpoolWith___at___00Submission_kernels_spec__4_spec__8(lean_object* v_ch_5124_, lean_object* v_h_5125_, lean_object* v_y_5126_, lean_object* v_k_5127_, lean_object* v_w_5128_, lean_object* v_x_5129_, lean_object* v_inp_5130_, lean_object* v_pos_5131_, lean_object* v_neg_5132_, uint8_t v_sp_5133_, uint8_t v_nz_5134_, lean_object* v_index_5135_, lean_object* v_x_5136_){
_start:
{
lean_object* v_zero_5137_; uint8_t v_isZero_5138_; 
v_zero_5137_ = lean_unsigned_to_nat(0u);
v_isZero_5138_ = lean_nat_dec_eq(v_x_5136_, v_zero_5137_);
if (v_isZero_5138_ == 1)
{
lean_object* v___x_5139_; 
lean_dec(v_x_5136_);
lean_dec(v_index_5135_);
v___x_5139_ = lean_alloc_ctor(0, 2, 2);
lean_ctor_set(v___x_5139_, 0, v_pos_5131_);
lean_ctor_set(v___x_5139_, 1, v_neg_5132_);
lean_ctor_set_uint8(v___x_5139_, sizeof(void*)*2, v_sp_5133_);
lean_ctor_set_uint8(v___x_5139_, sizeof(void*)*2 + 1, v_nz_5134_);
return v___x_5139_;
}
else
{
lean_object* v_one_5140_; lean_object* v_n_5141_; lean_object* v_pos_5143_; lean_object* v_neg_5144_; uint8_t v_special_5145_; uint8_t v_negZero_5146_; lean_object* v___y_5150_; lean_object* v___y_5151_; uint8_t v___y_5152_; lean_object* v___y_5153_; lean_object* v___y_5154_; lean_object* v___y_5164_; lean_object* v___y_5165_; lean_object* v___y_5166_; lean_object* v___y_5167_; lean_object* v___y_5177_; lean_object* v___y_5178_; uint8_t v___y_5179_; lean_object* v___y_5226_; lean_object* v___y_5227_; uint32_t v___x_5229_; lean_object* v___x_5230_; lean_object* v___x_5231_; lean_object* v___x_5232_; lean_object* v___x_5233_; lean_object* v___x_5234_; lean_object* v___x_5235_; lean_object* v___x_5236_; lean_object* v___x_5237_; lean_object* v___x_5238_; lean_object* v___x_5239_; lean_object* v___x_5240_; lean_object* v___x_5241_; uint32_t v___x_5242_; uint32_t v___x_5243_; uint32_t v___x_5244_; uint32_t v___x_5245_; uint32_t v___x_5246_; uint8_t v___x_5247_; lean_object* v___y_5249_; lean_object* v___y_5250_; lean_object* v___y_5252_; lean_object* v___y_5253_; lean_object* v___y_5261_; 
v_one_5140_ = lean_unsigned_to_nat(1u);
v_n_5141_ = lean_nat_sub(v_x_5136_, v_one_5140_);
lean_dec(v_x_5136_);
v___x_5229_ = 0;
v___x_5230_ = lean_nat_mul(v_ch_5124_, v_h_5125_);
v___x_5231_ = lean_nat_mul(v_y_5126_, v_k_5127_);
v___x_5232_ = lean_nat_add(v___x_5230_, v___x_5231_);
lean_dec(v___x_5231_);
lean_dec(v___x_5230_);
v___x_5233_ = lean_nat_div(v_index_5135_, v_k_5127_);
v___x_5234_ = lean_nat_add(v___x_5232_, v___x_5233_);
lean_dec(v___x_5233_);
lean_dec(v___x_5232_);
v___x_5235_ = lean_nat_mul(v___x_5234_, v_w_5128_);
lean_dec(v___x_5234_);
v___x_5236_ = lean_nat_mul(v_x_5129_, v_k_5127_);
v___x_5237_ = lean_nat_add(v___x_5235_, v___x_5236_);
lean_dec(v___x_5236_);
lean_dec(v___x_5235_);
v___x_5238_ = lean_nat_mod(v_index_5135_, v_k_5127_);
v___x_5239_ = lean_nat_add(v___x_5237_, v___x_5238_);
lean_dec(v___x_5238_);
lean_dec(v___x_5237_);
v___x_5240_ = lp_competition_Submission_dotX___lam__0___boxed__const__1;
v___x_5241_ = lean_array_get_borrowed(v___x_5240_, v_inp_5130_, v___x_5239_);
lean_dec(v___x_5239_);
v___x_5242_ = 23;
v___x_5243_ = lean_unbox_uint32(v___x_5241_);
v___x_5244_ = lean_uint32_shift_right(v___x_5243_, v___x_5242_);
v___x_5245_ = 255;
v___x_5246_ = lean_uint32_land(v___x_5244_, v___x_5245_);
v___x_5247_ = lean_uint32_dec_eq(v___x_5246_, v___x_5245_);
if (v___x_5247_ == 0)
{
uint8_t v___x_5267_; 
v___x_5267_ = lean_uint32_dec_eq(v___x_5246_, v___x_5229_);
if (v___x_5267_ == 0)
{
lean_object* v___x_5268_; uint32_t v___x_5269_; uint32_t v___x_5270_; uint32_t v___x_5271_; lean_object* v___x_5272_; lean_object* v___x_5273_; 
v___x_5268_ = lean_unsigned_to_nat(8388608u);
v___x_5269_ = 8388607;
v___x_5270_ = lean_unbox_uint32(v___x_5241_);
v___x_5271_ = lean_uint32_land(v___x_5270_, v___x_5269_);
v___x_5272_ = lean_uint32_to_nat(v___x_5271_);
v___x_5273_ = lean_nat_add(v___x_5268_, v___x_5272_);
lean_dec(v___x_5272_);
v___y_5261_ = v___x_5273_;
goto v___jp_5260_;
}
else
{
uint32_t v___x_5274_; uint32_t v___x_5275_; uint32_t v___x_5276_; lean_object* v___x_5277_; 
v___x_5274_ = 8388607;
v___x_5275_ = lean_unbox_uint32(v___x_5241_);
v___x_5276_ = lean_uint32_land(v___x_5275_, v___x_5274_);
v___x_5277_ = lean_uint32_to_nat(v___x_5276_);
v___y_5261_ = v___x_5277_;
goto v___jp_5260_;
}
}
else
{
v_pos_5143_ = v_pos_5131_;
v_neg_5144_ = v_neg_5132_;
v_special_5145_ = v___x_5247_;
v_negZero_5146_ = v_nz_5134_;
goto v___jp_5142_;
}
v___jp_5142_:
{
lean_object* v___x_5147_; 
v___x_5147_ = lean_nat_add(v_index_5135_, v_one_5140_);
lean_dec(v_index_5135_);
v_pos_5131_ = v_pos_5143_;
v_neg_5132_ = v_neg_5144_;
v_sp_5133_ = v_special_5145_;
v_nz_5134_ = v_negZero_5146_;
v_index_5135_ = v___x_5147_;
v_x_5136_ = v_n_5141_;
goto _start;
}
v___jp_5149_:
{
lean_object* v___x_5155_; lean_object* v___x_5156_; uint8_t v___x_5157_; 
v___x_5155_ = lean_nat_add(v___y_5153_, v___y_5150_);
lean_dec(v___y_5153_);
v___x_5156_ = lean_array_get_size(v___y_5154_);
v___x_5157_ = lean_nat_dec_lt(v___x_5155_, v___x_5156_);
if (v___x_5157_ == 0)
{
lean_dec(v___x_5155_);
lean_dec(v___y_5151_);
v_pos_5143_ = v___y_5154_;
v_neg_5144_ = v_neg_5132_;
v_special_5145_ = v_sp_5133_;
v_negZero_5146_ = v___y_5152_;
goto v___jp_5142_;
}
else
{
lean_object* v_v_5158_; lean_object* v___x_5159_; lean_object* v_xs_x27_5160_; lean_object* v___x_5161_; lean_object* v___x_5162_; 
v_v_5158_ = lean_array_fget(v___y_5154_, v___x_5155_);
v___x_5159_ = lean_box(0);
v_xs_x27_5160_ = lean_array_fset(v___y_5154_, v___x_5155_, v___x_5159_);
v___x_5161_ = lean_nat_add(v_v_5158_, v___y_5151_);
lean_dec(v___y_5151_);
lean_dec(v_v_5158_);
v___x_5162_ = lean_array_fset(v_xs_x27_5160_, v___x_5155_, v___x_5161_);
lean_dec(v___x_5155_);
v_pos_5143_ = v___x_5162_;
v_neg_5144_ = v_neg_5132_;
v_special_5145_ = v_sp_5133_;
v_negZero_5146_ = v___y_5152_;
goto v___jp_5142_;
}
}
v___jp_5163_:
{
lean_object* v___x_5168_; lean_object* v___x_5169_; uint8_t v___x_5170_; 
v___x_5168_ = lean_nat_add(v___y_5166_, v___y_5165_);
lean_dec(v___y_5166_);
v___x_5169_ = lean_array_get_size(v___y_5167_);
v___x_5170_ = lean_nat_dec_lt(v___x_5168_, v___x_5169_);
if (v___x_5170_ == 0)
{
lean_dec(v___x_5168_);
lean_dec(v___y_5164_);
v_pos_5143_ = v_pos_5131_;
v_neg_5144_ = v___y_5167_;
v_special_5145_ = v_sp_5133_;
v_negZero_5146_ = v_isZero_5138_;
goto v___jp_5142_;
}
else
{
lean_object* v_v_5171_; lean_object* v___x_5172_; lean_object* v_xs_x27_5173_; lean_object* v___x_5174_; lean_object* v___x_5175_; 
v_v_5171_ = lean_array_fget(v___y_5167_, v___x_5168_);
v___x_5172_ = lean_box(0);
v_xs_x27_5173_ = lean_array_fset(v___y_5167_, v___x_5168_, v___x_5172_);
v___x_5174_ = lean_nat_add(v_v_5171_, v___y_5164_);
lean_dec(v___y_5164_);
lean_dec(v_v_5171_);
v___x_5175_ = lean_array_fset(v_xs_x27_5173_, v___x_5168_, v___x_5174_);
lean_dec(v___x_5168_);
v_pos_5143_ = v_pos_5131_;
v_neg_5144_ = v___x_5175_;
v_special_5145_ = v_sp_5133_;
v_negZero_5146_ = v_isZero_5138_;
goto v___jp_5142_;
}
}
v___jp_5176_:
{
uint8_t v___x_5180_; 
v___x_5180_ = lean_nat_dec_eq(v___y_5178_, v_zero_5137_);
if (v___x_5180_ == 0)
{
if (v___y_5179_ == 0)
{
uint64_t v___x_5181_; lean_object* v___x_5182_; lean_object* v___x_5183_; lean_object* v_l_5184_; lean_object* v___x_5185_; uint64_t v_r_5186_; uint64_t v___x_5187_; uint64_t v___x_5188_; uint64_t v___x_5189_; uint64_t v___x_5190_; uint64_t v___x_5191_; uint64_t v___x_5192_; lean_object* v_hi_5193_; lean_object* v___x_5194_; uint8_t v___x_5195_; 
v___x_5181_ = lean_uint64_of_nat(v___y_5178_);
lean_dec(v___y_5178_);
v___x_5182_ = lean_unsigned_to_nat(32u);
v___x_5183_ = lean_unsigned_to_nat(5u);
v_l_5184_ = lean_nat_shiftr(v___y_5177_, v___x_5183_);
v___x_5185_ = lean_nat_mod(v___y_5177_, v___x_5182_);
lean_dec(v___y_5177_);
v_r_5186_ = lean_uint64_of_nat(v___x_5185_);
lean_dec(v___x_5185_);
v___x_5187_ = 1ULL;
v___x_5188_ = 32ULL;
v___x_5189_ = lean_uint64_sub(v___x_5188_, v_r_5186_);
v___x_5190_ = lean_uint64_shift_left(v___x_5187_, v___x_5189_);
v___x_5191_ = lean_uint64_mod(v___x_5181_, v___x_5190_);
v___x_5192_ = lean_uint64_shift_right(v___x_5181_, v___x_5189_);
v_hi_5193_ = lean_uint64_to_nat(v___x_5192_);
v___x_5194_ = lean_array_get_size(v_pos_5131_);
v___x_5195_ = lean_nat_dec_lt(v_l_5184_, v___x_5194_);
if (v___x_5195_ == 0)
{
v___y_5150_ = v_one_5140_;
v___y_5151_ = v_hi_5193_;
v___y_5152_ = v___y_5179_;
v___y_5153_ = v_l_5184_;
v___y_5154_ = v_pos_5131_;
goto v___jp_5149_;
}
else
{
uint64_t v___x_5196_; lean_object* v_lo_5197_; lean_object* v_v_5198_; lean_object* v___x_5199_; lean_object* v_xs_x27_5200_; lean_object* v___x_5201_; lean_object* v___x_5202_; 
v___x_5196_ = lean_uint64_shift_left(v___x_5191_, v_r_5186_);
v_lo_5197_ = lean_uint64_to_nat(v___x_5196_);
v_v_5198_ = lean_array_fget(v_pos_5131_, v_l_5184_);
v___x_5199_ = lean_box(0);
v_xs_x27_5200_ = lean_array_fset(v_pos_5131_, v_l_5184_, v___x_5199_);
v___x_5201_ = lean_nat_add(v_v_5198_, v_lo_5197_);
lean_dec(v_lo_5197_);
lean_dec(v_v_5198_);
v___x_5202_ = lean_array_fset(v_xs_x27_5200_, v_l_5184_, v___x_5201_);
v___y_5150_ = v_one_5140_;
v___y_5151_ = v_hi_5193_;
v___y_5152_ = v___y_5179_;
v___y_5153_ = v_l_5184_;
v___y_5154_ = v___x_5202_;
goto v___jp_5149_;
}
}
else
{
uint64_t v___x_5203_; lean_object* v___x_5204_; lean_object* v___x_5205_; lean_object* v_l_5206_; lean_object* v___x_5207_; uint64_t v_r_5208_; uint64_t v___x_5209_; uint64_t v___x_5210_; uint64_t v___x_5211_; uint64_t v___x_5212_; uint64_t v___x_5213_; uint64_t v___x_5214_; lean_object* v_hi_5215_; lean_object* v___x_5216_; uint8_t v___x_5217_; 
v___x_5203_ = lean_uint64_of_nat(v___y_5178_);
lean_dec(v___y_5178_);
v___x_5204_ = lean_unsigned_to_nat(32u);
v___x_5205_ = lean_unsigned_to_nat(5u);
v_l_5206_ = lean_nat_shiftr(v___y_5177_, v___x_5205_);
v___x_5207_ = lean_nat_mod(v___y_5177_, v___x_5204_);
lean_dec(v___y_5177_);
v_r_5208_ = lean_uint64_of_nat(v___x_5207_);
lean_dec(v___x_5207_);
v___x_5209_ = 1ULL;
v___x_5210_ = 32ULL;
v___x_5211_ = lean_uint64_sub(v___x_5210_, v_r_5208_);
v___x_5212_ = lean_uint64_shift_left(v___x_5209_, v___x_5211_);
v___x_5213_ = lean_uint64_mod(v___x_5203_, v___x_5212_);
v___x_5214_ = lean_uint64_shift_right(v___x_5203_, v___x_5211_);
v_hi_5215_ = lean_uint64_to_nat(v___x_5214_);
v___x_5216_ = lean_array_get_size(v_neg_5132_);
v___x_5217_ = lean_nat_dec_lt(v_l_5206_, v___x_5216_);
if (v___x_5217_ == 0)
{
v___y_5164_ = v_hi_5215_;
v___y_5165_ = v_one_5140_;
v___y_5166_ = v_l_5206_;
v___y_5167_ = v_neg_5132_;
goto v___jp_5163_;
}
else
{
uint64_t v___x_5218_; lean_object* v_lo_5219_; lean_object* v_v_5220_; lean_object* v___x_5221_; lean_object* v_xs_x27_5222_; lean_object* v___x_5223_; lean_object* v___x_5224_; 
v___x_5218_ = lean_uint64_shift_left(v___x_5213_, v_r_5208_);
v_lo_5219_ = lean_uint64_to_nat(v___x_5218_);
v_v_5220_ = lean_array_fget(v_neg_5132_, v_l_5206_);
v___x_5221_ = lean_box(0);
v_xs_x27_5222_ = lean_array_fset(v_neg_5132_, v_l_5206_, v___x_5221_);
v___x_5223_ = lean_nat_add(v_v_5220_, v_lo_5219_);
lean_dec(v_lo_5219_);
lean_dec(v_v_5220_);
v___x_5224_ = lean_array_fset(v_xs_x27_5222_, v_l_5206_, v___x_5223_);
v___y_5164_ = v_hi_5215_;
v___y_5165_ = v_one_5140_;
v___y_5166_ = v_l_5206_;
v___y_5167_ = v___x_5224_;
goto v___jp_5163_;
}
}
}
else
{
lean_dec(v___y_5178_);
lean_dec(v___y_5177_);
if (v_nz_5134_ == 0)
{
v_pos_5143_ = v_pos_5131_;
v_neg_5144_ = v_neg_5132_;
v_special_5145_ = v_sp_5133_;
v_negZero_5146_ = v_nz_5134_;
goto v___jp_5142_;
}
else
{
v_pos_5143_ = v_pos_5131_;
v_neg_5144_ = v_neg_5132_;
v_special_5145_ = v_sp_5133_;
v_negZero_5146_ = v___y_5179_;
goto v___jp_5142_;
}
}
}
v___jp_5225_:
{
uint8_t v___x_5228_; 
v___x_5228_ = 1;
v___y_5177_ = v___y_5226_;
v___y_5178_ = v___y_5227_;
v___y_5179_ = v___x_5228_;
goto v___jp_5176_;
}
v___jp_5248_:
{
if (v___x_5247_ == 0)
{
v___y_5226_ = v___y_5249_;
v___y_5227_ = v___y_5250_;
goto v___jp_5225_;
}
else
{
v___y_5177_ = v___y_5249_;
v___y_5178_ = v___y_5250_;
v___y_5179_ = v___x_5247_;
goto v___jp_5176_;
}
}
v___jp_5251_:
{
lean_object* v___x_5254_; lean_object* v___x_5255_; uint32_t v___x_5256_; uint32_t v___x_5257_; uint32_t v___x_5258_; uint8_t v___x_5259_; 
v___x_5254_ = lean_unsigned_to_nat(126u);
v___x_5255_ = lean_nat_add(v___y_5253_, v___x_5254_);
lean_dec(v___y_5253_);
v___x_5256_ = 2147483648;
v___x_5257_ = lean_unbox_uint32(v___x_5241_);
v___x_5258_ = lean_uint32_land(v___x_5257_, v___x_5256_);
v___x_5259_ = lean_uint32_dec_eq(v___x_5258_, v___x_5229_);
if (v___x_5259_ == 0)
{
v___y_5249_ = v___x_5255_;
v___y_5250_ = v___y_5252_;
goto v___jp_5248_;
}
else
{
if (v___x_5247_ == 0)
{
if (v___x_5247_ == 0)
{
v___y_5177_ = v___x_5255_;
v___y_5178_ = v___y_5252_;
v___y_5179_ = v___x_5247_;
goto v___jp_5176_;
}
else
{
v___y_5226_ = v___x_5255_;
v___y_5227_ = v___y_5252_;
goto v___jp_5225_;
}
}
else
{
v___y_5249_ = v___x_5255_;
v___y_5250_ = v___y_5252_;
goto v___jp_5248_;
}
}
}
v___jp_5260_:
{
lean_object* v___x_5262_; lean_object* v___x_5263_; uint8_t v___x_5264_; 
v___x_5262_ = lean_unsigned_to_nat(8388608u);
v___x_5263_ = lean_nat_mul(v___y_5261_, v___x_5262_);
lean_dec(v___y_5261_);
v___x_5264_ = lean_uint32_dec_eq(v___x_5246_, v___x_5229_);
if (v___x_5264_ == 0)
{
lean_object* v___x_5265_; lean_object* v___x_5266_; 
v___x_5265_ = lean_uint32_to_nat(v___x_5246_);
v___x_5266_ = lean_nat_sub(v___x_5265_, v_one_5140_);
lean_dec(v___x_5265_);
v___y_5252_ = v___x_5263_;
v___y_5253_ = v___x_5266_;
goto v___jp_5251_;
}
else
{
v___y_5252_ = v___x_5263_;
v___y_5253_ = v_zero_5137_;
goto v___jp_5251_;
}
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_dotLoop___at___00Submission_rmsnormCached_spec__0___at___00ExactRuntime_avgpoolWith___at___00Submission_kernels_spec__4_spec__8___boxed(lean_object* v_ch_5278_, lean_object* v_h_5279_, lean_object* v_y_5280_, lean_object* v_k_5281_, lean_object* v_w_5282_, lean_object* v_x_5283_, lean_object* v_inp_5284_, lean_object* v_pos_5285_, lean_object* v_neg_5286_, lean_object* v_sp_5287_, lean_object* v_nz_5288_, lean_object* v_index_5289_, lean_object* v_x_5290_){
_start:
{
uint8_t v_sp_boxed_5291_; uint8_t v_nz_boxed_5292_; lean_object* v_res_5293_; 
v_sp_boxed_5291_ = lean_unbox(v_sp_5287_);
v_nz_boxed_5292_ = lean_unbox(v_nz_5288_);
v_res_5293_ = lp_competition_Submission_dotLoop___at___00Submission_rmsnormCached_spec__0___at___00ExactRuntime_avgpoolWith___at___00Submission_kernels_spec__4_spec__8(v_ch_5278_, v_h_5279_, v_y_5280_, v_k_5281_, v_w_5282_, v_x_5283_, v_inp_5284_, v_pos_5285_, v_neg_5286_, v_sp_boxed_5291_, v_nz_boxed_5292_, v_index_5289_, v_x_5290_);
lean_dec_ref(v_inp_5284_);
lean_dec(v_x_5283_);
lean_dec(v_w_5282_);
lean_dec(v_k_5281_);
lean_dec(v_y_5280_);
lean_dec(v_h_5279_);
lean_dec(v_ch_5278_);
return v_res_5293_;
}
}
LEAN_EXPORT uint32_t lp_competition_ExactRuntime_avgpoolWith___at___00Submission_kernels_spec__4___lam__0(lean_object* v___x_5294_, lean_object* v___x_5295_, lean_object* v___x_5296_, lean_object* v_k_5297_, lean_object* v_h_5298_, lean_object* v_w_5299_, lean_object* v_inp_5300_, lean_object* v___f_5301_, lean_object* v_q_5302_){
_start:
{
lean_object* v_ch_5303_; lean_object* v___x_5304_; lean_object* v_y_5305_; lean_object* v_x_5306_; lean_object* v___x_5307_; uint32_t v___y_5309_; lean_object* v___x_5318_; lean_object* v___x_5319_; uint8_t v___x_5320_; uint8_t v___x_5321_; lean_object* v_acc_5322_; uint8_t v_special_5323_; 
v_ch_5303_ = lean_nat_div(v_q_5302_, v___x_5294_);
v___x_5304_ = lean_nat_div(v_q_5302_, v___x_5295_);
v_y_5305_ = lean_nat_mod(v___x_5304_, v___x_5296_);
lean_dec(v___x_5304_);
v_x_5306_ = lean_nat_mod(v_q_5302_, v___x_5295_);
v___x_5307_ = lean_nat_mul(v_k_5297_, v_k_5297_);
v___x_5318_ = lean_unsigned_to_nat(0u);
v___x_5319_ = lean_obj_once(&lp_competition_Submission_Acc_empty___closed__0, &lp_competition_Submission_Acc_empty___closed__0_once, _init_lp_competition_Submission_Acc_empty___closed__0);
v___x_5320_ = 0;
v___x_5321_ = 1;
lean_inc(v___x_5307_);
v_acc_5322_ = lp_competition_Submission_dotLoop___at___00Submission_rmsnormCached_spec__0___at___00ExactRuntime_avgpoolWith___at___00Submission_kernels_spec__4_spec__8(v_ch_5303_, v_h_5298_, v_y_5305_, v_k_5297_, v_w_5299_, v_x_5306_, v_inp_5300_, v___x_5319_, v___x_5319_, v___x_5320_, v___x_5321_, v___x_5318_, v___x_5307_);
v_special_5323_ = lean_ctor_get_uint8(v_acc_5322_, sizeof(void*)*2);
if (v_special_5323_ == 0)
{
lean_object* v_pos_5324_; lean_object* v_neg_5325_; uint8_t v_negZero_5326_; lean_object* v___x_5327_; uint8_t v___x_5328_; 
lean_dec(v_x_5306_);
lean_dec(v_y_5305_);
lean_dec(v_ch_5303_);
lean_dec_ref(v___f_5301_);
lean_dec_ref(v_inp_5300_);
lean_dec(v_w_5299_);
lean_dec(v_h_5298_);
lean_dec(v_k_5297_);
v_pos_5324_ = lean_ctor_get(v_acc_5322_, 0);
lean_inc_ref(v_pos_5324_);
v_neg_5325_ = lean_ctor_get(v_acc_5322_, 1);
lean_inc_ref(v_neg_5325_);
v_negZero_5326_ = lean_ctor_get_uint8(v_acc_5322_, sizeof(void*)*2 + 1);
lean_dec_ref(v_acc_5322_);
v___x_5327_ = lean_obj_once(&lp_competition_Submission_dotFn___closed__1, &lp_competition_Submission_dotFn___closed__1_once, _init_lp_competition_Submission_dotFn___closed__1);
v___x_5328_ = lean_nat_dec_eq(v___x_5307_, v___x_5318_);
if (v___x_5328_ == 0)
{
uint32_t v___x_5329_; 
v___x_5329_ = lp_competition_Submission_finishFast(v_pos_5324_, v_neg_5325_, v___x_5327_, v_negZero_5326_);
lean_dec_ref(v_neg_5325_);
lean_dec_ref(v_pos_5324_);
v___y_5309_ = v___x_5329_;
goto v___jp_5308_;
}
else
{
uint32_t v___x_5330_; 
v___x_5330_ = lp_competition_Submission_finishFast(v_pos_5324_, v_neg_5325_, v___x_5327_, v___x_5320_);
lean_dec_ref(v_neg_5325_);
lean_dec_ref(v_pos_5324_);
v___y_5309_ = v___x_5330_;
goto v___jp_5308_;
}
}
else
{
lean_object* v___f_5331_; lean_object* v___x_5332_; lean_object* v___x_5333_; uint32_t v___x_5334_; 
lean_dec_ref(v_acc_5322_);
v___f_5331_ = lean_alloc_closure((void*)(lp_competition_ExactRuntime_avgpoolWith___at___00Submission_kernels_spec__4___lam__1___boxed), 8, 7);
lean_closure_set(v___f_5331_, 0, v_ch_5303_);
lean_closure_set(v___f_5331_, 1, v_h_5298_);
lean_closure_set(v___f_5331_, 2, v_y_5305_);
lean_closure_set(v___f_5331_, 3, v_k_5297_);
lean_closure_set(v___f_5331_, 4, v_w_5299_);
lean_closure_set(v___f_5331_, 5, v_x_5306_);
lean_closure_set(v___f_5331_, 6, v_inp_5300_);
lean_inc_n(v___x_5307_, 2);
v___x_5332_ = l_Array_ofFn___redArg(v___x_5307_, v___f_5331_);
v___x_5333_ = l_Array_ofFn___redArg(v___x_5307_, v___f_5301_);
v___x_5334_ = lp_competition_ExactRuntime_dotSpec(v___x_5332_, v___x_5333_);
v___y_5309_ = v___x_5334_;
goto v___jp_5308_;
}
v___jp_5308_:
{
lean_object* v___x_5310_; lean_object* v___x_5311_; lean_object* v___x_5312_; uint32_t v___x_5313_; lean_object* v___x_5314_; lean_object* v___x_5315_; lean_object* v___x_5316_; uint32_t v___x_5317_; 
v___x_5310_ = lean_uint32_to_nat(v___y_5309_);
v___x_5311_ = lean_unsigned_to_nat(32u);
v___x_5312_ = l_BitVec_ofNat(v___x_5311_, v___x_5310_);
lean_dec(v___x_5310_);
v___x_5313_ = lp_competition_ExactRuntime_natW(v___x_5307_);
v___x_5314_ = lean_uint32_to_nat(v___x_5313_);
v___x_5315_ = l_BitVec_ofNat(v___x_5311_, v___x_5314_);
lean_dec(v___x_5314_);
v___x_5316_ = lp_floatlib_FloatLib_Floats_Formats_BinaryInterchange_Model_DivBackend_word___at___00FloatLib_Floats_Formats_BinaryInterchange_Configured_Plan_softwareDiv32Certified_spec__1(v___x_5312_, v___x_5315_);
v___x_5317_ = lean_uint32_of_nat(v___x_5316_);
lean_dec(v___x_5316_);
return v___x_5317_;
}
}
}
LEAN_EXPORT lean_object* lp_competition_ExactRuntime_avgpoolWith___at___00Submission_kernels_spec__4___lam__0___boxed(lean_object* v___x_5335_, lean_object* v___x_5336_, lean_object* v___x_5337_, lean_object* v_k_5338_, lean_object* v_h_5339_, lean_object* v_w_5340_, lean_object* v_inp_5341_, lean_object* v___f_5342_, lean_object* v_q_5343_){
_start:
{
uint32_t v_res_5344_; lean_object* v_r_5345_; 
v_res_5344_ = lp_competition_ExactRuntime_avgpoolWith___at___00Submission_kernels_spec__4___lam__0(v___x_5335_, v___x_5336_, v___x_5337_, v_k_5338_, v_h_5339_, v_w_5340_, v_inp_5341_, v___f_5342_, v_q_5343_);
lean_dec(v_q_5343_);
lean_dec(v___x_5337_);
lean_dec(v___x_5336_);
lean_dec(v___x_5335_);
v_r_5345_ = lean_box_uint32(v_res_5344_);
return v_r_5345_;
}
}
LEAN_EXPORT lean_object* lp_competition_ExactRuntime_avgpoolWith___at___00Submission_kernels_spec__4(lean_object* v_c_5346_, lean_object* v_h_5347_, lean_object* v_w_5348_, lean_object* v_k_5349_, lean_object* v_inp_5350_){
_start:
{
lean_object* v___f_5351_; lean_object* v___x_5352_; lean_object* v___x_5353_; lean_object* v___x_5354_; lean_object* v___f_5355_; lean_object* v___x_5356_; lean_object* v___x_5357_; 
v___f_5351_ = ((lean_object*)(lp_competition_Submission_sumX___closed__0));
v___x_5352_ = lean_nat_div(v_h_5347_, v_k_5349_);
v___x_5353_ = lean_nat_div(v_w_5348_, v_k_5349_);
v___x_5354_ = lean_nat_mul(v___x_5352_, v___x_5353_);
lean_inc(v___x_5354_);
v___f_5355_ = lean_alloc_closure((void*)(lp_competition_ExactRuntime_avgpoolWith___at___00Submission_kernels_spec__4___lam__0___boxed), 9, 8);
lean_closure_set(v___f_5355_, 0, v___x_5354_);
lean_closure_set(v___f_5355_, 1, v___x_5353_);
lean_closure_set(v___f_5355_, 2, v___x_5352_);
lean_closure_set(v___f_5355_, 3, v_k_5349_);
lean_closure_set(v___f_5355_, 4, v_h_5347_);
lean_closure_set(v___f_5355_, 5, v_w_5348_);
lean_closure_set(v___f_5355_, 6, v_inp_5350_);
lean_closure_set(v___f_5355_, 7, v___f_5351_);
v___x_5356_ = lean_nat_mul(v_c_5346_, v___x_5354_);
lean_dec(v___x_5354_);
v___x_5357_ = l_Array_ofFn___redArg(v___x_5356_, v___f_5355_);
return v___x_5357_;
}
}
LEAN_EXPORT lean_object* lp_competition_ExactRuntime_avgpoolWith___at___00Submission_kernels_spec__4___boxed(lean_object* v_c_5358_, lean_object* v_h_5359_, lean_object* v_w_5360_, lean_object* v_k_5361_, lean_object* v_inp_5362_){
_start:
{
lean_object* v_res_5363_; 
v_res_5363_ = lp_competition_ExactRuntime_avgpoolWith___at___00Submission_kernels_spec__4(v_c_5358_, v_h_5359_, v_w_5360_, v_k_5361_, v_inp_5362_);
lean_dec(v_c_5358_);
return v_res_5363_;
}
}
LEAN_EXPORT uint32_t lp_competition_ExactRuntime_depthwiseWith___at___00Submission_kernels_spec__3___lam__1(lean_object* v_k_5364_, lean_object* v_c_5365_, lean_object* v_kw_5366_, lean_object* v_kh_5367_, lean_object* v_y_5368_, lean_object* v_stride_5369_, lean_object* v_pad_5370_, lean_object* v_x_5371_, lean_object* v_h_5372_, lean_object* v_w_5373_, lean_object* v_inp_5374_, lean_object* v_i_5375_){
_start:
{
uint8_t v___x_5376_; 
v___x_5376_ = lean_nat_dec_lt(v_i_5375_, v_k_5364_);
if (v___x_5376_ == 0)
{
uint32_t v___x_5377_; 
v___x_5377_ = 1065353216;
return v___x_5377_;
}
else
{
lean_object* v___x_5378_; lean_object* v___x_5379_; lean_object* v___x_5380_; lean_object* v_dy_5381_; lean_object* v___x_5382_; lean_object* v_yy_5383_; uint8_t v___x_5384_; 
v___x_5378_ = lean_nat_mul(v_c_5365_, v_k_5364_);
v___x_5379_ = lean_nat_add(v___x_5378_, v_i_5375_);
lean_dec(v___x_5378_);
v___x_5380_ = lean_nat_div(v___x_5379_, v_kw_5366_);
v_dy_5381_ = lean_nat_mod(v___x_5380_, v_kh_5367_);
lean_dec(v___x_5380_);
v___x_5382_ = lean_nat_mul(v_y_5368_, v_stride_5369_);
v_yy_5383_ = lean_nat_add(v___x_5382_, v_dy_5381_);
lean_dec(v_dy_5381_);
lean_dec(v___x_5382_);
v___x_5384_ = lean_nat_dec_lt(v_yy_5383_, v_pad_5370_);
if (v___x_5384_ == 0)
{
lean_object* v_dx_5385_; lean_object* v___x_5386_; lean_object* v_xx_5387_; uint8_t v___x_5388_; 
v_dx_5385_ = lean_nat_mod(v___x_5379_, v_kw_5366_);
v___x_5386_ = lean_nat_mul(v_x_5371_, v_stride_5369_);
v_xx_5387_ = lean_nat_add(v___x_5386_, v_dx_5385_);
lean_dec(v_dx_5385_);
lean_dec(v___x_5386_);
v___x_5388_ = lean_nat_dec_lt(v_xx_5387_, v_pad_5370_);
if (v___x_5388_ == 0)
{
lean_object* v___x_5389_; uint8_t v___x_5390_; 
v___x_5389_ = lean_nat_sub(v_yy_5383_, v_pad_5370_);
lean_dec(v_yy_5383_);
v___x_5390_ = lean_nat_dec_le(v_h_5372_, v___x_5389_);
if (v___x_5390_ == 0)
{
lean_object* v___x_5391_; uint8_t v___x_5392_; 
v___x_5391_ = lean_nat_sub(v_xx_5387_, v_pad_5370_);
lean_dec(v_xx_5387_);
v___x_5392_ = lean_nat_dec_le(v_w_5373_, v___x_5391_);
if (v___x_5392_ == 0)
{
lean_object* v_c_5393_; lean_object* v___x_5394_; lean_object* v___x_5395_; lean_object* v___x_5396_; lean_object* v___x_5397_; lean_object* v___x_5398_; lean_object* v___x_5399_; uint32_t v___x_5400_; 
v_c_5393_ = lean_nat_div(v___x_5379_, v_k_5364_);
lean_dec(v___x_5379_);
v___x_5394_ = lean_nat_mul(v_c_5393_, v_h_5372_);
lean_dec(v_c_5393_);
v___x_5395_ = lean_nat_add(v___x_5394_, v___x_5389_);
lean_dec(v___x_5389_);
lean_dec(v___x_5394_);
v___x_5396_ = lean_nat_mul(v___x_5395_, v_w_5373_);
lean_dec(v___x_5395_);
v___x_5397_ = lean_nat_add(v___x_5396_, v___x_5391_);
lean_dec(v___x_5391_);
lean_dec(v___x_5396_);
v___x_5398_ = lp_competition_Submission_dotX___lam__0___boxed__const__1;
v___x_5399_ = lean_array_get_borrowed(v___x_5398_, v_inp_5374_, v___x_5397_);
lean_dec(v___x_5397_);
v___x_5400_ = lean_unbox_uint32(v___x_5399_);
return v___x_5400_;
}
else
{
uint32_t v___x_5401_; 
lean_dec(v___x_5391_);
lean_dec(v___x_5389_);
lean_dec(v___x_5379_);
v___x_5401_ = 0;
return v___x_5401_;
}
}
else
{
uint32_t v___x_5402_; 
lean_dec(v___x_5389_);
lean_dec(v_xx_5387_);
lean_dec(v___x_5379_);
v___x_5402_ = 0;
return v___x_5402_;
}
}
else
{
uint32_t v___x_5403_; 
lean_dec(v_xx_5387_);
lean_dec(v_yy_5383_);
lean_dec(v___x_5379_);
v___x_5403_ = 0;
return v___x_5403_;
}
}
else
{
uint32_t v___x_5404_; 
lean_dec(v_yy_5383_);
lean_dec(v___x_5379_);
v___x_5404_ = 0;
return v___x_5404_;
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_ExactRuntime_depthwiseWith___at___00Submission_kernels_spec__3___lam__1___boxed(lean_object* v_k_5405_, lean_object* v_c_5406_, lean_object* v_kw_5407_, lean_object* v_kh_5408_, lean_object* v_y_5409_, lean_object* v_stride_5410_, lean_object* v_pad_5411_, lean_object* v_x_5412_, lean_object* v_h_5413_, lean_object* v_w_5414_, lean_object* v_inp_5415_, lean_object* v_i_5416_){
_start:
{
uint32_t v_res_5417_; lean_object* v_r_5418_; 
v_res_5417_ = lp_competition_ExactRuntime_depthwiseWith___at___00Submission_kernels_spec__3___lam__1(v_k_5405_, v_c_5406_, v_kw_5407_, v_kh_5408_, v_y_5409_, v_stride_5410_, v_pad_5411_, v_x_5412_, v_h_5413_, v_w_5414_, v_inp_5415_, v_i_5416_);
lean_dec(v_i_5416_);
lean_dec_ref(v_inp_5415_);
lean_dec(v_w_5414_);
lean_dec(v_h_5413_);
lean_dec(v_x_5412_);
lean_dec(v_pad_5411_);
lean_dec(v_stride_5410_);
lean_dec(v_y_5409_);
lean_dec(v_kh_5408_);
lean_dec(v_kw_5407_);
lean_dec(v_c_5406_);
lean_dec(v_k_5405_);
v_r_5418_ = lean_box_uint32(v_res_5417_);
return v_r_5418_;
}
}
LEAN_EXPORT uint32_t lp_competition_ExactRuntime_depthwiseWith___at___00Submission_kernels_spec__3___lam__0(lean_object* v_k_5419_, lean_object* v_b_5420_, lean_object* v_c_5421_, lean_object* v_wts_5422_, lean_object* v_i_5423_){
_start:
{
uint8_t v___x_5424_; 
v___x_5424_ = lean_nat_dec_lt(v_i_5423_, v_k_5419_);
if (v___x_5424_ == 0)
{
lean_object* v___x_5425_; lean_object* v___x_5426_; uint32_t v___x_5427_; 
v___x_5425_ = lp_competition_Submission_dotX___lam__0___boxed__const__1;
v___x_5426_ = lean_array_get_borrowed(v___x_5425_, v_b_5420_, v_c_5421_);
v___x_5427_ = lean_unbox_uint32(v___x_5426_);
return v___x_5427_;
}
else
{
lean_object* v___x_5428_; lean_object* v___x_5429_; lean_object* v___x_5430_; lean_object* v___x_5431_; uint32_t v___x_5432_; 
v___x_5428_ = lean_nat_mul(v_c_5421_, v_k_5419_);
v___x_5429_ = lean_nat_add(v___x_5428_, v_i_5423_);
lean_dec(v___x_5428_);
v___x_5430_ = lp_competition_Submission_dotX___lam__0___boxed__const__1;
v___x_5431_ = lean_array_get_borrowed(v___x_5430_, v_wts_5422_, v___x_5429_);
lean_dec(v___x_5429_);
v___x_5432_ = lean_unbox_uint32(v___x_5431_);
return v___x_5432_;
}
}
}
LEAN_EXPORT lean_object* lp_competition_ExactRuntime_depthwiseWith___at___00Submission_kernels_spec__3___lam__0___boxed(lean_object* v_k_5433_, lean_object* v_b_5434_, lean_object* v_c_5435_, lean_object* v_wts_5436_, lean_object* v_i_5437_){
_start:
{
uint32_t v_res_5438_; lean_object* v_r_5439_; 
v_res_5438_ = lp_competition_ExactRuntime_depthwiseWith___at___00Submission_kernels_spec__3___lam__0(v_k_5433_, v_b_5434_, v_c_5435_, v_wts_5436_, v_i_5437_);
lean_dec(v_i_5437_);
lean_dec_ref(v_wts_5436_);
lean_dec(v_c_5435_);
lean_dec_ref(v_b_5434_);
lean_dec(v_k_5433_);
v_r_5439_ = lean_box_uint32(v_res_5438_);
return v_r_5439_;
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_dotLoop___at___00Submission_rmsnormCached_spec__0___at___00ExactRuntime_depthwiseWith___at___00Submission_kernels_spec__3_spec__6(lean_object* v_k_5440_, lean_object* v_c_5441_, lean_object* v___x_5442_, lean_object* v___x_5443_, lean_object* v_s_5444_, lean_object* v_y_5445_, lean_object* v_x_5446_, lean_object* v_inp_5447_, lean_object* v_b_5448_, lean_object* v_wts_5449_, lean_object* v_pos_5450_, lean_object* v_neg_5451_, uint8_t v_sp_5452_, uint8_t v_nz_5453_, lean_object* v_index_5454_, lean_object* v_x_5455_){
_start:
{
lean_object* v_zero_5456_; uint8_t v_isZero_5457_; 
v_zero_5456_ = lean_unsigned_to_nat(0u);
v_isZero_5457_ = lean_nat_dec_eq(v_x_5455_, v_zero_5456_);
if (v_isZero_5457_ == 1)
{
lean_object* v___x_5458_; 
lean_dec(v_x_5455_);
lean_dec(v_index_5454_);
v___x_5458_ = lean_alloc_ctor(0, 2, 2);
lean_ctor_set(v___x_5458_, 0, v_pos_5450_);
lean_ctor_set(v___x_5458_, 1, v_neg_5451_);
lean_ctor_set_uint8(v___x_5458_, sizeof(void*)*2, v_sp_5452_);
lean_ctor_set_uint8(v___x_5458_, sizeof(void*)*2 + 1, v_nz_5453_);
return v___x_5458_;
}
else
{
lean_object* v_one_5459_; lean_object* v_n_5460_; lean_object* v_pos_5462_; lean_object* v_neg_5463_; uint8_t v_special_5464_; uint8_t v_negZero_5465_; lean_object* v___y_5471_; lean_object* v___y_5472_; lean_object* v___y_5473_; uint8_t v___y_5474_; lean_object* v___y_5475_; lean_object* v___y_5485_; lean_object* v___y_5486_; lean_object* v___y_5487_; lean_object* v___y_5488_; lean_object* v___y_5498_; lean_object* v___y_5499_; uint8_t v___y_5500_; lean_object* v___y_5547_; lean_object* v___y_5548_; lean_object* v___y_5551_; lean_object* v___y_5552_; uint8_t v___y_5553_; uint8_t v___y_5554_; uint8_t v___y_5555_; lean_object* v___y_5557_; lean_object* v___y_5558_; uint32_t v___y_5559_; uint8_t v___y_5560_; uint8_t v___y_5561_; lean_object* v___y_5568_; uint32_t v___y_5569_; lean_object* v___y_5570_; uint32_t v___y_5571_; uint8_t v___y_5572_; lean_object* v___y_5573_; uint32_t v___y_5581_; uint32_t v___y_5582_; lean_object* v___y_5583_; uint32_t v___y_5584_; uint32_t v___y_5585_; uint8_t v___y_5586_; lean_object* v___y_5587_; uint32_t v___y_5595_; lean_object* v___y_5596_; uint32_t v___y_5597_; uint32_t v___y_5598_; uint32_t v___y_5599_; uint32_t v___y_5600_; uint8_t v___y_5601_; lean_object* v___y_5602_; uint32_t v___y_5609_; uint32_t v___y_5610_; uint32_t v___y_5611_; uint32_t v___y_5612_; uint32_t v___y_5613_; uint8_t v___y_5614_; lean_object* v___y_5615_; uint32_t v___y_5629_; uint32_t v___y_5630_; uint32_t v___y_5631_; uint32_t v___y_5632_; uint8_t v___y_5633_; uint32_t v___y_5634_; uint32_t v___y_5649_; uint8_t v___x_5664_; 
v_one_5459_ = lean_unsigned_to_nat(1u);
v_n_5460_ = lean_nat_sub(v_x_5455_, v_one_5459_);
lean_dec(v_x_5455_);
v___x_5664_ = lean_nat_dec_lt(v_index_5454_, v_k_5440_);
if (v___x_5664_ == 0)
{
uint32_t v___x_5665_; 
v___x_5665_ = 1065353216;
v___y_5649_ = v___x_5665_;
goto v___jp_5648_;
}
else
{
lean_object* v_h_5666_; lean_object* v_w_5667_; lean_object* v_stride_5668_; lean_object* v_pad_5669_; lean_object* v___x_5670_; lean_object* v___x_5671_; lean_object* v___x_5672_; lean_object* v_dy_5673_; lean_object* v___x_5674_; lean_object* v_yy_5675_; uint8_t v___x_5676_; 
v_h_5666_ = lean_ctor_get(v_s_5444_, 1);
v_w_5667_ = lean_ctor_get(v_s_5444_, 2);
v_stride_5668_ = lean_ctor_get(v_s_5444_, 6);
v_pad_5669_ = lean_ctor_get(v_s_5444_, 7);
v___x_5670_ = lean_nat_mul(v_c_5441_, v_k_5440_);
v___x_5671_ = lean_nat_add(v___x_5670_, v_index_5454_);
lean_dec(v___x_5670_);
v___x_5672_ = lean_nat_div(v___x_5671_, v___x_5442_);
v_dy_5673_ = lean_nat_mod(v___x_5672_, v___x_5443_);
lean_dec(v___x_5672_);
v___x_5674_ = lean_nat_mul(v_y_5445_, v_stride_5668_);
v_yy_5675_ = lean_nat_add(v___x_5674_, v_dy_5673_);
lean_dec(v_dy_5673_);
lean_dec(v___x_5674_);
v___x_5676_ = lean_nat_dec_lt(v_yy_5675_, v_pad_5669_);
if (v___x_5676_ == 0)
{
lean_object* v_dx_5677_; lean_object* v___x_5678_; lean_object* v_xx_5679_; uint8_t v___x_5680_; 
v_dx_5677_ = lean_nat_mod(v___x_5671_, v___x_5442_);
v___x_5678_ = lean_nat_mul(v_x_5446_, v_stride_5668_);
v_xx_5679_ = lean_nat_add(v___x_5678_, v_dx_5677_);
lean_dec(v_dx_5677_);
lean_dec(v___x_5678_);
v___x_5680_ = lean_nat_dec_lt(v_xx_5679_, v_pad_5669_);
if (v___x_5680_ == 0)
{
lean_object* v___x_5681_; uint8_t v___x_5682_; 
v___x_5681_ = lean_nat_sub(v_yy_5675_, v_pad_5669_);
lean_dec(v_yy_5675_);
v___x_5682_ = lean_nat_dec_le(v_h_5666_, v___x_5681_);
if (v___x_5682_ == 0)
{
lean_object* v___x_5683_; uint8_t v___x_5684_; 
v___x_5683_ = lean_nat_sub(v_xx_5679_, v_pad_5669_);
lean_dec(v_xx_5679_);
v___x_5684_ = lean_nat_dec_le(v_w_5667_, v___x_5683_);
if (v___x_5684_ == 0)
{
lean_object* v_c_5685_; lean_object* v___x_5686_; lean_object* v___x_5687_; lean_object* v___x_5688_; lean_object* v___x_5689_; lean_object* v___x_5690_; lean_object* v___x_5691_; uint32_t v___x_5692_; 
v_c_5685_ = lean_nat_div(v___x_5671_, v_k_5440_);
lean_dec(v___x_5671_);
v___x_5686_ = lean_nat_mul(v_c_5685_, v_h_5666_);
lean_dec(v_c_5685_);
v___x_5687_ = lean_nat_add(v___x_5686_, v___x_5681_);
lean_dec(v___x_5681_);
lean_dec(v___x_5686_);
v___x_5688_ = lean_nat_mul(v___x_5687_, v_w_5667_);
lean_dec(v___x_5687_);
v___x_5689_ = lean_nat_add(v___x_5688_, v___x_5683_);
lean_dec(v___x_5683_);
lean_dec(v___x_5688_);
v___x_5690_ = lp_competition_Submission_dotX___lam__0___boxed__const__1;
v___x_5691_ = lean_array_get_borrowed(v___x_5690_, v_inp_5447_, v___x_5689_);
lean_dec(v___x_5689_);
v___x_5692_ = lean_unbox_uint32(v___x_5691_);
v___y_5649_ = v___x_5692_;
goto v___jp_5648_;
}
else
{
uint32_t v___x_5693_; 
lean_dec(v___x_5683_);
lean_dec(v___x_5681_);
lean_dec(v___x_5671_);
v___x_5693_ = 0;
v___y_5649_ = v___x_5693_;
goto v___jp_5648_;
}
}
else
{
uint32_t v___x_5694_; 
lean_dec(v___x_5681_);
lean_dec(v_xx_5679_);
lean_dec(v___x_5671_);
v___x_5694_ = 0;
v___y_5649_ = v___x_5694_;
goto v___jp_5648_;
}
}
else
{
uint32_t v___x_5695_; 
lean_dec(v_xx_5679_);
lean_dec(v_yy_5675_);
lean_dec(v___x_5671_);
v___x_5695_ = 0;
v___y_5649_ = v___x_5695_;
goto v___jp_5648_;
}
}
else
{
uint32_t v___x_5696_; 
lean_dec(v_yy_5675_);
lean_dec(v___x_5671_);
v___x_5696_ = 0;
v___y_5649_ = v___x_5696_;
goto v___jp_5648_;
}
}
v___jp_5461_:
{
lean_object* v___x_5466_; 
v___x_5466_ = lean_nat_add(v_index_5454_, v_one_5459_);
lean_dec(v_index_5454_);
v_pos_5450_ = v_pos_5462_;
v_neg_5451_ = v_neg_5463_;
v_sp_5452_ = v_special_5464_;
v_nz_5453_ = v_negZero_5465_;
v_index_5454_ = v___x_5466_;
v_x_5455_ = v_n_5460_;
goto _start;
}
v___jp_5468_:
{
uint8_t v___x_5469_; 
v___x_5469_ = 1;
v_pos_5462_ = v_pos_5450_;
v_neg_5463_ = v_neg_5451_;
v_special_5464_ = v___x_5469_;
v_negZero_5465_ = v_nz_5453_;
goto v___jp_5461_;
}
v___jp_5470_:
{
lean_object* v___x_5476_; lean_object* v___x_5477_; uint8_t v___x_5478_; 
v___x_5476_ = lean_nat_add(v___y_5473_, v___y_5472_);
lean_dec(v___y_5473_);
v___x_5477_ = lean_array_get_size(v___y_5475_);
v___x_5478_ = lean_nat_dec_lt(v___x_5476_, v___x_5477_);
if (v___x_5478_ == 0)
{
lean_dec(v___x_5476_);
lean_dec(v___y_5471_);
v_pos_5462_ = v___y_5475_;
v_neg_5463_ = v_neg_5451_;
v_special_5464_ = v_sp_5452_;
v_negZero_5465_ = v___y_5474_;
goto v___jp_5461_;
}
else
{
lean_object* v_v_5479_; lean_object* v___x_5480_; lean_object* v_xs_x27_5481_; lean_object* v___x_5482_; lean_object* v___x_5483_; 
v_v_5479_ = lean_array_fget(v___y_5475_, v___x_5476_);
v___x_5480_ = lean_box(0);
v_xs_x27_5481_ = lean_array_fset(v___y_5475_, v___x_5476_, v___x_5480_);
v___x_5482_ = lean_nat_add(v_v_5479_, v___y_5471_);
lean_dec(v___y_5471_);
lean_dec(v_v_5479_);
v___x_5483_ = lean_array_fset(v_xs_x27_5481_, v___x_5476_, v___x_5482_);
lean_dec(v___x_5476_);
v_pos_5462_ = v___x_5483_;
v_neg_5463_ = v_neg_5451_;
v_special_5464_ = v_sp_5452_;
v_negZero_5465_ = v___y_5474_;
goto v___jp_5461_;
}
}
v___jp_5484_:
{
lean_object* v___x_5489_; lean_object* v___x_5490_; uint8_t v___x_5491_; 
v___x_5489_ = lean_nat_add(v___y_5487_, v___y_5486_);
lean_dec(v___y_5487_);
v___x_5490_ = lean_array_get_size(v___y_5488_);
v___x_5491_ = lean_nat_dec_lt(v___x_5489_, v___x_5490_);
if (v___x_5491_ == 0)
{
lean_dec(v___x_5489_);
lean_dec(v___y_5485_);
v_pos_5462_ = v_pos_5450_;
v_neg_5463_ = v___y_5488_;
v_special_5464_ = v_sp_5452_;
v_negZero_5465_ = v_isZero_5457_;
goto v___jp_5461_;
}
else
{
lean_object* v_v_5492_; lean_object* v___x_5493_; lean_object* v_xs_x27_5494_; lean_object* v___x_5495_; lean_object* v___x_5496_; 
v_v_5492_ = lean_array_fget(v___y_5488_, v___x_5489_);
v___x_5493_ = lean_box(0);
v_xs_x27_5494_ = lean_array_fset(v___y_5488_, v___x_5489_, v___x_5493_);
v___x_5495_ = lean_nat_add(v_v_5492_, v___y_5485_);
lean_dec(v___y_5485_);
lean_dec(v_v_5492_);
v___x_5496_ = lean_array_fset(v_xs_x27_5494_, v___x_5489_, v___x_5495_);
lean_dec(v___x_5489_);
v_pos_5462_ = v_pos_5450_;
v_neg_5463_ = v___x_5496_;
v_special_5464_ = v_sp_5452_;
v_negZero_5465_ = v_isZero_5457_;
goto v___jp_5461_;
}
}
v___jp_5497_:
{
uint8_t v___x_5501_; 
v___x_5501_ = lean_nat_dec_eq(v___y_5499_, v_zero_5456_);
if (v___x_5501_ == 0)
{
if (v___y_5500_ == 0)
{
uint64_t v___x_5502_; lean_object* v___x_5503_; lean_object* v___x_5504_; lean_object* v_l_5505_; lean_object* v___x_5506_; uint64_t v_r_5507_; uint64_t v___x_5508_; uint64_t v___x_5509_; uint64_t v___x_5510_; uint64_t v___x_5511_; uint64_t v___x_5512_; uint64_t v___x_5513_; lean_object* v_hi_5514_; lean_object* v___x_5515_; uint8_t v___x_5516_; 
v___x_5502_ = lean_uint64_of_nat(v___y_5499_);
lean_dec(v___y_5499_);
v___x_5503_ = lean_unsigned_to_nat(32u);
v___x_5504_ = lean_unsigned_to_nat(5u);
v_l_5505_ = lean_nat_shiftr(v___y_5498_, v___x_5504_);
v___x_5506_ = lean_nat_mod(v___y_5498_, v___x_5503_);
lean_dec(v___y_5498_);
v_r_5507_ = lean_uint64_of_nat(v___x_5506_);
lean_dec(v___x_5506_);
v___x_5508_ = 1ULL;
v___x_5509_ = 32ULL;
v___x_5510_ = lean_uint64_sub(v___x_5509_, v_r_5507_);
v___x_5511_ = lean_uint64_shift_left(v___x_5508_, v___x_5510_);
v___x_5512_ = lean_uint64_mod(v___x_5502_, v___x_5511_);
v___x_5513_ = lean_uint64_shift_right(v___x_5502_, v___x_5510_);
v_hi_5514_ = lean_uint64_to_nat(v___x_5513_);
v___x_5515_ = lean_array_get_size(v_pos_5450_);
v___x_5516_ = lean_nat_dec_lt(v_l_5505_, v___x_5515_);
if (v___x_5516_ == 0)
{
v___y_5471_ = v_hi_5514_;
v___y_5472_ = v_one_5459_;
v___y_5473_ = v_l_5505_;
v___y_5474_ = v___y_5500_;
v___y_5475_ = v_pos_5450_;
goto v___jp_5470_;
}
else
{
uint64_t v___x_5517_; lean_object* v_lo_5518_; lean_object* v_v_5519_; lean_object* v___x_5520_; lean_object* v_xs_x27_5521_; lean_object* v___x_5522_; lean_object* v___x_5523_; 
v___x_5517_ = lean_uint64_shift_left(v___x_5512_, v_r_5507_);
v_lo_5518_ = lean_uint64_to_nat(v___x_5517_);
v_v_5519_ = lean_array_fget(v_pos_5450_, v_l_5505_);
v___x_5520_ = lean_box(0);
v_xs_x27_5521_ = lean_array_fset(v_pos_5450_, v_l_5505_, v___x_5520_);
v___x_5522_ = lean_nat_add(v_v_5519_, v_lo_5518_);
lean_dec(v_lo_5518_);
lean_dec(v_v_5519_);
v___x_5523_ = lean_array_fset(v_xs_x27_5521_, v_l_5505_, v___x_5522_);
v___y_5471_ = v_hi_5514_;
v___y_5472_ = v_one_5459_;
v___y_5473_ = v_l_5505_;
v___y_5474_ = v___y_5500_;
v___y_5475_ = v___x_5523_;
goto v___jp_5470_;
}
}
else
{
uint64_t v___x_5524_; lean_object* v___x_5525_; lean_object* v___x_5526_; lean_object* v_l_5527_; lean_object* v___x_5528_; uint64_t v_r_5529_; uint64_t v___x_5530_; uint64_t v___x_5531_; uint64_t v___x_5532_; uint64_t v___x_5533_; uint64_t v___x_5534_; uint64_t v___x_5535_; lean_object* v_hi_5536_; lean_object* v___x_5537_; uint8_t v___x_5538_; 
v___x_5524_ = lean_uint64_of_nat(v___y_5499_);
lean_dec(v___y_5499_);
v___x_5525_ = lean_unsigned_to_nat(32u);
v___x_5526_ = lean_unsigned_to_nat(5u);
v_l_5527_ = lean_nat_shiftr(v___y_5498_, v___x_5526_);
v___x_5528_ = lean_nat_mod(v___y_5498_, v___x_5525_);
lean_dec(v___y_5498_);
v_r_5529_ = lean_uint64_of_nat(v___x_5528_);
lean_dec(v___x_5528_);
v___x_5530_ = 1ULL;
v___x_5531_ = 32ULL;
v___x_5532_ = lean_uint64_sub(v___x_5531_, v_r_5529_);
v___x_5533_ = lean_uint64_shift_left(v___x_5530_, v___x_5532_);
v___x_5534_ = lean_uint64_mod(v___x_5524_, v___x_5533_);
v___x_5535_ = lean_uint64_shift_right(v___x_5524_, v___x_5532_);
v_hi_5536_ = lean_uint64_to_nat(v___x_5535_);
v___x_5537_ = lean_array_get_size(v_neg_5451_);
v___x_5538_ = lean_nat_dec_lt(v_l_5527_, v___x_5537_);
if (v___x_5538_ == 0)
{
v___y_5485_ = v_hi_5536_;
v___y_5486_ = v_one_5459_;
v___y_5487_ = v_l_5527_;
v___y_5488_ = v_neg_5451_;
goto v___jp_5484_;
}
else
{
uint64_t v___x_5539_; lean_object* v_lo_5540_; lean_object* v_v_5541_; lean_object* v___x_5542_; lean_object* v_xs_x27_5543_; lean_object* v___x_5544_; lean_object* v___x_5545_; 
v___x_5539_ = lean_uint64_shift_left(v___x_5534_, v_r_5529_);
v_lo_5540_ = lean_uint64_to_nat(v___x_5539_);
v_v_5541_ = lean_array_fget(v_neg_5451_, v_l_5527_);
v___x_5542_ = lean_box(0);
v_xs_x27_5543_ = lean_array_fset(v_neg_5451_, v_l_5527_, v___x_5542_);
v___x_5544_ = lean_nat_add(v_v_5541_, v_lo_5540_);
lean_dec(v_lo_5540_);
lean_dec(v_v_5541_);
v___x_5545_ = lean_array_fset(v_xs_x27_5543_, v_l_5527_, v___x_5544_);
v___y_5485_ = v_hi_5536_;
v___y_5486_ = v_one_5459_;
v___y_5487_ = v_l_5527_;
v___y_5488_ = v___x_5545_;
goto v___jp_5484_;
}
}
}
else
{
lean_dec(v___y_5499_);
lean_dec(v___y_5498_);
if (v_nz_5453_ == 0)
{
v_pos_5462_ = v_pos_5450_;
v_neg_5463_ = v_neg_5451_;
v_special_5464_ = v_sp_5452_;
v_negZero_5465_ = v_nz_5453_;
goto v___jp_5461_;
}
else
{
v_pos_5462_ = v_pos_5450_;
v_neg_5463_ = v_neg_5451_;
v_special_5464_ = v_sp_5452_;
v_negZero_5465_ = v___y_5500_;
goto v___jp_5461_;
}
}
}
v___jp_5546_:
{
uint8_t v___x_5549_; 
v___x_5549_ = 1;
v___y_5498_ = v___y_5547_;
v___y_5499_ = v___y_5548_;
v___y_5500_ = v___x_5549_;
goto v___jp_5497_;
}
v___jp_5550_:
{
if (v___y_5553_ == 0)
{
if (v___y_5555_ == 0)
{
v___y_5498_ = v___y_5551_;
v___y_5499_ = v___y_5552_;
v___y_5500_ = v___y_5554_;
goto v___jp_5497_;
}
else
{
v___y_5547_ = v___y_5551_;
v___y_5548_ = v___y_5552_;
goto v___jp_5546_;
}
}
else
{
if (v___y_5555_ == 0)
{
v___y_5547_ = v___y_5551_;
v___y_5548_ = v___y_5552_;
goto v___jp_5546_;
}
else
{
v___y_5498_ = v___y_5551_;
v___y_5499_ = v___y_5552_;
v___y_5500_ = v___y_5554_;
goto v___jp_5497_;
}
}
}
v___jp_5556_:
{
uint32_t v___x_5562_; uint32_t v___x_5563_; uint32_t v___x_5564_; uint8_t v___x_5565_; 
v___x_5562_ = 2147483648;
v___x_5563_ = lean_uint32_land(v___y_5559_, v___x_5562_);
v___x_5564_ = 0;
v___x_5565_ = lean_uint32_dec_eq(v___x_5563_, v___x_5564_);
if (v___x_5565_ == 0)
{
uint8_t v___x_5566_; 
v___x_5566_ = 1;
v___y_5551_ = v___y_5557_;
v___y_5552_ = v___y_5558_;
v___y_5553_ = v___y_5561_;
v___y_5554_ = v___y_5560_;
v___y_5555_ = v___x_5566_;
goto v___jp_5550_;
}
else
{
v___y_5551_ = v___y_5557_;
v___y_5552_ = v___y_5558_;
v___y_5553_ = v___y_5561_;
v___y_5554_ = v___y_5560_;
v___y_5555_ = v___y_5560_;
goto v___jp_5550_;
}
}
v___jp_5567_:
{
lean_object* v___x_5574_; uint32_t v___x_5575_; uint32_t v___x_5576_; uint32_t v___x_5577_; uint8_t v___x_5578_; 
v___x_5574_ = lean_nat_add(v___y_5568_, v___y_5573_);
lean_dec(v___y_5573_);
lean_dec(v___y_5568_);
v___x_5575_ = 2147483648;
v___x_5576_ = lean_uint32_land(v___y_5569_, v___x_5575_);
v___x_5577_ = 0;
v___x_5578_ = lean_uint32_dec_eq(v___x_5576_, v___x_5577_);
if (v___x_5578_ == 0)
{
uint8_t v___x_5579_; 
v___x_5579_ = 1;
v___y_5557_ = v___x_5574_;
v___y_5558_ = v___y_5570_;
v___y_5559_ = v___y_5571_;
v___y_5560_ = v___y_5572_;
v___y_5561_ = v___x_5579_;
goto v___jp_5556_;
}
else
{
v___y_5557_ = v___x_5574_;
v___y_5558_ = v___y_5570_;
v___y_5559_ = v___y_5571_;
v___y_5560_ = v___y_5572_;
v___y_5561_ = v___y_5572_;
goto v___jp_5556_;
}
}
v___jp_5580_:
{
uint32_t v___x_5588_; uint32_t v___x_5589_; uint32_t v___x_5590_; uint8_t v___x_5591_; 
v___x_5588_ = lean_uint32_shift_right(v___y_5584_, v___y_5581_);
v___x_5589_ = lean_uint32_land(v___x_5588_, v___y_5585_);
v___x_5590_ = 0;
v___x_5591_ = lean_uint32_dec_eq(v___x_5589_, v___x_5590_);
if (v___x_5591_ == 0)
{
lean_object* v___x_5592_; lean_object* v___x_5593_; 
v___x_5592_ = lean_uint32_to_nat(v___x_5589_);
v___x_5593_ = lean_nat_sub(v___x_5592_, v_one_5459_);
lean_dec(v___x_5592_);
v___y_5568_ = v___y_5587_;
v___y_5569_ = v___y_5582_;
v___y_5570_ = v___y_5583_;
v___y_5571_ = v___y_5584_;
v___y_5572_ = v___y_5586_;
v___y_5573_ = v___x_5593_;
goto v___jp_5567_;
}
else
{
v___y_5568_ = v___y_5587_;
v___y_5569_ = v___y_5582_;
v___y_5570_ = v___y_5583_;
v___y_5571_ = v___y_5584_;
v___y_5572_ = v___y_5586_;
v___y_5573_ = v_zero_5456_;
goto v___jp_5567_;
}
}
v___jp_5594_:
{
lean_object* v___x_5603_; uint32_t v___x_5604_; uint8_t v___x_5605_; 
v___x_5603_ = lean_nat_mul(v___y_5596_, v___y_5602_);
lean_dec(v___y_5602_);
lean_dec(v___y_5596_);
v___x_5604_ = 0;
v___x_5605_ = lean_uint32_dec_eq(v___y_5599_, v___x_5604_);
if (v___x_5605_ == 0)
{
lean_object* v___x_5606_; lean_object* v___x_5607_; 
v___x_5606_ = lean_uint32_to_nat(v___y_5599_);
v___x_5607_ = lean_nat_sub(v___x_5606_, v_one_5459_);
lean_dec(v___x_5606_);
v___y_5581_ = v___y_5595_;
v___y_5582_ = v___y_5597_;
v___y_5583_ = v___x_5603_;
v___y_5584_ = v___y_5598_;
v___y_5585_ = v___y_5600_;
v___y_5586_ = v___y_5601_;
v___y_5587_ = v___x_5607_;
goto v___jp_5580_;
}
else
{
v___y_5581_ = v___y_5595_;
v___y_5582_ = v___y_5597_;
v___y_5583_ = v___x_5603_;
v___y_5584_ = v___y_5598_;
v___y_5585_ = v___y_5600_;
v___y_5586_ = v___y_5601_;
v___y_5587_ = v_zero_5456_;
goto v___jp_5580_;
}
}
v___jp_5608_:
{
uint32_t v___x_5616_; uint32_t v___x_5617_; uint32_t v___x_5618_; uint8_t v___x_5619_; 
v___x_5616_ = lean_uint32_shift_right(v___y_5611_, v___y_5609_);
v___x_5617_ = lean_uint32_land(v___x_5616_, v___y_5613_);
v___x_5618_ = 0;
v___x_5619_ = lean_uint32_dec_eq(v___x_5617_, v___x_5618_);
if (v___x_5619_ == 0)
{
lean_object* v___x_5620_; uint32_t v___x_5621_; uint32_t v___x_5622_; lean_object* v___x_5623_; lean_object* v___x_5624_; 
v___x_5620_ = lean_unsigned_to_nat(8388608u);
v___x_5621_ = 8388607;
v___x_5622_ = lean_uint32_land(v___y_5611_, v___x_5621_);
v___x_5623_ = lean_uint32_to_nat(v___x_5622_);
v___x_5624_ = lean_nat_add(v___x_5620_, v___x_5623_);
lean_dec(v___x_5623_);
v___y_5595_ = v___y_5609_;
v___y_5596_ = v___y_5615_;
v___y_5597_ = v___y_5610_;
v___y_5598_ = v___y_5611_;
v___y_5599_ = v___y_5612_;
v___y_5600_ = v___y_5613_;
v___y_5601_ = v___y_5614_;
v___y_5602_ = v___x_5624_;
goto v___jp_5594_;
}
else
{
uint32_t v___x_5625_; uint32_t v___x_5626_; lean_object* v___x_5627_; 
v___x_5625_ = 8388607;
v___x_5626_ = lean_uint32_land(v___y_5611_, v___x_5625_);
v___x_5627_ = lean_uint32_to_nat(v___x_5626_);
v___y_5595_ = v___y_5609_;
v___y_5596_ = v___y_5615_;
v___y_5597_ = v___y_5610_;
v___y_5598_ = v___y_5611_;
v___y_5599_ = v___y_5612_;
v___y_5600_ = v___y_5613_;
v___y_5601_ = v___y_5614_;
v___y_5602_ = v___x_5627_;
goto v___jp_5594_;
}
}
v___jp_5628_:
{
uint32_t v___x_5635_; uint32_t v___x_5636_; uint8_t v___x_5637_; 
v___x_5635_ = lean_uint32_shift_right(v___y_5634_, v___y_5629_);
v___x_5636_ = lean_uint32_land(v___x_5635_, v___y_5632_);
v___x_5637_ = lean_uint32_dec_eq(v___x_5636_, v___y_5632_);
if (v___x_5637_ == 0)
{
uint32_t v___x_5638_; uint8_t v___x_5639_; 
v___x_5638_ = 0;
v___x_5639_ = lean_uint32_dec_eq(v___y_5631_, v___x_5638_);
if (v___x_5639_ == 0)
{
lean_object* v___x_5640_; uint32_t v___x_5641_; uint32_t v___x_5642_; lean_object* v___x_5643_; lean_object* v___x_5644_; 
v___x_5640_ = lean_unsigned_to_nat(8388608u);
v___x_5641_ = 8388607;
v___x_5642_ = lean_uint32_land(v___y_5630_, v___x_5641_);
v___x_5643_ = lean_uint32_to_nat(v___x_5642_);
v___x_5644_ = lean_nat_add(v___x_5640_, v___x_5643_);
lean_dec(v___x_5643_);
v___y_5609_ = v___y_5629_;
v___y_5610_ = v___y_5630_;
v___y_5611_ = v___y_5634_;
v___y_5612_ = v___y_5631_;
v___y_5613_ = v___y_5632_;
v___y_5614_ = v___y_5633_;
v___y_5615_ = v___x_5644_;
goto v___jp_5608_;
}
else
{
uint32_t v___x_5645_; uint32_t v___x_5646_; lean_object* v___x_5647_; 
v___x_5645_ = 8388607;
v___x_5646_ = lean_uint32_land(v___y_5630_, v___x_5645_);
v___x_5647_ = lean_uint32_to_nat(v___x_5646_);
v___y_5609_ = v___y_5629_;
v___y_5610_ = v___y_5630_;
v___y_5611_ = v___y_5634_;
v___y_5612_ = v___y_5631_;
v___y_5613_ = v___y_5632_;
v___y_5614_ = v___y_5633_;
v___y_5615_ = v___x_5647_;
goto v___jp_5608_;
}
}
else
{
goto v___jp_5468_;
}
}
v___jp_5648_:
{
uint32_t v___x_5650_; uint32_t v___x_5651_; uint32_t v___x_5652_; uint32_t v___x_5653_; uint8_t v___x_5654_; 
v___x_5650_ = 23;
v___x_5651_ = lean_uint32_shift_right(v___y_5649_, v___x_5650_);
v___x_5652_ = 255;
v___x_5653_ = lean_uint32_land(v___x_5651_, v___x_5652_);
v___x_5654_ = lean_uint32_dec_eq(v___x_5653_, v___x_5652_);
if (v___x_5654_ == 0)
{
uint8_t v___x_5655_; 
v___x_5655_ = lean_nat_dec_lt(v_index_5454_, v_k_5440_);
if (v___x_5655_ == 0)
{
lean_object* v___x_5656_; lean_object* v___x_5657_; uint32_t v___x_5658_; 
v___x_5656_ = lp_competition_Submission_dotX___lam__0___boxed__const__1;
v___x_5657_ = lean_array_get_borrowed(v___x_5656_, v_b_5448_, v_c_5441_);
v___x_5658_ = lean_unbox_uint32(v___x_5657_);
v___y_5629_ = v___x_5650_;
v___y_5630_ = v___y_5649_;
v___y_5631_ = v___x_5653_;
v___y_5632_ = v___x_5652_;
v___y_5633_ = v___x_5654_;
v___y_5634_ = v___x_5658_;
goto v___jp_5628_;
}
else
{
lean_object* v___x_5659_; lean_object* v___x_5660_; lean_object* v___x_5661_; lean_object* v___x_5662_; uint32_t v___x_5663_; 
v___x_5659_ = lean_nat_mul(v_c_5441_, v_k_5440_);
v___x_5660_ = lean_nat_add(v___x_5659_, v_index_5454_);
lean_dec(v___x_5659_);
v___x_5661_ = lp_competition_Submission_dotX___lam__0___boxed__const__1;
v___x_5662_ = lean_array_get_borrowed(v___x_5661_, v_wts_5449_, v___x_5660_);
lean_dec(v___x_5660_);
v___x_5663_ = lean_unbox_uint32(v___x_5662_);
v___y_5629_ = v___x_5650_;
v___y_5630_ = v___y_5649_;
v___y_5631_ = v___x_5653_;
v___y_5632_ = v___x_5652_;
v___y_5633_ = v___x_5654_;
v___y_5634_ = v___x_5663_;
goto v___jp_5628_;
}
}
else
{
goto v___jp_5468_;
}
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_Submission_dotLoop___at___00Submission_rmsnormCached_spec__0___at___00ExactRuntime_depthwiseWith___at___00Submission_kernels_spec__3_spec__6___boxed(lean_object* v_k_5697_, lean_object* v_c_5698_, lean_object* v___x_5699_, lean_object* v___x_5700_, lean_object* v_s_5701_, lean_object* v_y_5702_, lean_object* v_x_5703_, lean_object* v_inp_5704_, lean_object* v_b_5705_, lean_object* v_wts_5706_, lean_object* v_pos_5707_, lean_object* v_neg_5708_, lean_object* v_sp_5709_, lean_object* v_nz_5710_, lean_object* v_index_5711_, lean_object* v_x_5712_){
_start:
{
uint8_t v_sp_boxed_5713_; uint8_t v_nz_boxed_5714_; lean_object* v_res_5715_; 
v_sp_boxed_5713_ = lean_unbox(v_sp_5709_);
v_nz_boxed_5714_ = lean_unbox(v_nz_5710_);
v_res_5715_ = lp_competition_Submission_dotLoop___at___00Submission_rmsnormCached_spec__0___at___00ExactRuntime_depthwiseWith___at___00Submission_kernels_spec__3_spec__6(v_k_5697_, v_c_5698_, v___x_5699_, v___x_5700_, v_s_5701_, v_y_5702_, v_x_5703_, v_inp_5704_, v_b_5705_, v_wts_5706_, v_pos_5707_, v_neg_5708_, v_sp_boxed_5713_, v_nz_boxed_5714_, v_index_5711_, v_x_5712_);
lean_dec_ref(v_wts_5706_);
lean_dec_ref(v_b_5705_);
lean_dec_ref(v_inp_5704_);
lean_dec(v_x_5703_);
lean_dec(v_y_5702_);
lean_dec_ref(v_s_5701_);
lean_dec(v___x_5700_);
lean_dec(v___x_5699_);
lean_dec(v_c_5698_);
lean_dec(v_k_5697_);
return v_res_5715_;
}
}
LEAN_EXPORT uint32_t lp_competition_ExactRuntime_depthwiseWith___at___00Submission_kernels_spec__3___lam__2(lean_object* v___x_5716_, lean_object* v___x_5717_, lean_object* v___x_5718_, lean_object* v_k_5719_, lean_object* v_kw_5720_, lean_object* v_kh_5721_, lean_object* v_s_5722_, lean_object* v_inp_5723_, lean_object* v_b_5724_, lean_object* v_wts_5725_, uint8_t v_relu_5726_, lean_object* v_stride_5727_, lean_object* v_pad_5728_, lean_object* v_h_5729_, lean_object* v_w_5730_, lean_object* v_q_5731_){
_start:
{
uint32_t v___y_5733_; lean_object* v_c_5746_; lean_object* v___x_5747_; lean_object* v_y_5748_; lean_object* v_x_5749_; lean_object* v___x_5750_; lean_object* v___x_5751_; lean_object* v___x_5752_; lean_object* v___x_5753_; uint8_t v___x_5754_; uint8_t v___x_5755_; lean_object* v_acc_5756_; uint8_t v_special_5757_; 
v_c_5746_ = lean_nat_div(v_q_5731_, v___x_5716_);
v___x_5747_ = lean_nat_div(v_q_5731_, v___x_5717_);
v_y_5748_ = lean_nat_mod(v___x_5747_, v___x_5718_);
lean_dec(v___x_5747_);
v_x_5749_ = lean_nat_mod(v_q_5731_, v___x_5717_);
v___x_5750_ = lean_unsigned_to_nat(1u);
v___x_5751_ = lean_nat_add(v_k_5719_, v___x_5750_);
v___x_5752_ = lean_unsigned_to_nat(0u);
v___x_5753_ = lean_obj_once(&lp_competition_Submission_Acc_empty___closed__0, &lp_competition_Submission_Acc_empty___closed__0_once, _init_lp_competition_Submission_Acc_empty___closed__0);
v___x_5754_ = 0;
v___x_5755_ = 1;
lean_inc(v___x_5751_);
v_acc_5756_ = lp_competition_Submission_dotLoop___at___00Submission_rmsnormCached_spec__0___at___00ExactRuntime_depthwiseWith___at___00Submission_kernels_spec__3_spec__6(v_k_5719_, v_c_5746_, v_kw_5720_, v_kh_5721_, v_s_5722_, v_y_5748_, v_x_5749_, v_inp_5723_, v_b_5724_, v_wts_5725_, v___x_5753_, v___x_5753_, v___x_5754_, v___x_5755_, v___x_5752_, v___x_5751_);
v_special_5757_ = lean_ctor_get_uint8(v_acc_5756_, sizeof(void*)*2);
if (v_special_5757_ == 0)
{
lean_object* v_pos_5758_; lean_object* v_neg_5759_; uint8_t v_negZero_5760_; lean_object* v___x_5761_; uint8_t v___x_5762_; 
lean_dec(v_x_5749_);
lean_dec(v_y_5748_);
lean_dec(v_c_5746_);
lean_dec(v_w_5730_);
lean_dec(v_h_5729_);
lean_dec(v_pad_5728_);
lean_dec(v_stride_5727_);
lean_dec_ref(v_wts_5725_);
lean_dec_ref(v_b_5724_);
lean_dec_ref(v_inp_5723_);
lean_dec(v_kh_5721_);
lean_dec(v_kw_5720_);
lean_dec(v_k_5719_);
v_pos_5758_ = lean_ctor_get(v_acc_5756_, 0);
lean_inc_ref(v_pos_5758_);
v_neg_5759_ = lean_ctor_get(v_acc_5756_, 1);
lean_inc_ref(v_neg_5759_);
v_negZero_5760_ = lean_ctor_get_uint8(v_acc_5756_, sizeof(void*)*2 + 1);
lean_dec_ref(v_acc_5756_);
v___x_5761_ = lean_obj_once(&lp_competition_Submission_dotFn___closed__1, &lp_competition_Submission_dotFn___closed__1_once, _init_lp_competition_Submission_dotFn___closed__1);
v___x_5762_ = lean_nat_dec_eq(v___x_5751_, v___x_5752_);
lean_dec(v___x_5751_);
if (v___x_5762_ == 0)
{
uint32_t v___x_5763_; 
v___x_5763_ = lp_competition_Submission_finishFast(v_pos_5758_, v_neg_5759_, v___x_5761_, v_negZero_5760_);
lean_dec_ref(v_neg_5759_);
lean_dec_ref(v_pos_5758_);
v___y_5733_ = v___x_5763_;
goto v___jp_5732_;
}
else
{
uint32_t v___x_5764_; 
v___x_5764_ = lp_competition_Submission_finishFast(v_pos_5758_, v_neg_5759_, v___x_5761_, v___x_5754_);
lean_dec_ref(v_neg_5759_);
lean_dec_ref(v_pos_5758_);
v___y_5733_ = v___x_5764_;
goto v___jp_5732_;
}
}
else
{
lean_object* v___f_5765_; lean_object* v___f_5766_; lean_object* v___x_5767_; lean_object* v___x_5768_; uint32_t v___x_5769_; 
lean_dec_ref(v_acc_5756_);
lean_inc(v_c_5746_);
lean_inc(v_k_5719_);
v___f_5765_ = lean_alloc_closure((void*)(lp_competition_ExactRuntime_depthwiseWith___at___00Submission_kernels_spec__3___lam__0___boxed), 5, 4);
lean_closure_set(v___f_5765_, 0, v_k_5719_);
lean_closure_set(v___f_5765_, 1, v_b_5724_);
lean_closure_set(v___f_5765_, 2, v_c_5746_);
lean_closure_set(v___f_5765_, 3, v_wts_5725_);
v___f_5766_ = lean_alloc_closure((void*)(lp_competition_ExactRuntime_depthwiseWith___at___00Submission_kernels_spec__3___lam__1___boxed), 12, 11);
lean_closure_set(v___f_5766_, 0, v_k_5719_);
lean_closure_set(v___f_5766_, 1, v_c_5746_);
lean_closure_set(v___f_5766_, 2, v_kw_5720_);
lean_closure_set(v___f_5766_, 3, v_kh_5721_);
lean_closure_set(v___f_5766_, 4, v_y_5748_);
lean_closure_set(v___f_5766_, 5, v_stride_5727_);
lean_closure_set(v___f_5766_, 6, v_pad_5728_);
lean_closure_set(v___f_5766_, 7, v_x_5749_);
lean_closure_set(v___f_5766_, 8, v_h_5729_);
lean_closure_set(v___f_5766_, 9, v_w_5730_);
lean_closure_set(v___f_5766_, 10, v_inp_5723_);
lean_inc(v___x_5751_);
v___x_5767_ = l_Array_ofFn___redArg(v___x_5751_, v___f_5766_);
v___x_5768_ = l_Array_ofFn___redArg(v___x_5751_, v___f_5765_);
v___x_5769_ = lp_competition_ExactRuntime_dotSpec(v___x_5767_, v___x_5768_);
v___y_5733_ = v___x_5769_;
goto v___jp_5732_;
}
v___jp_5732_:
{
if (v_relu_5726_ == 0)
{
return v___y_5733_;
}
else
{
uint32_t v___x_5734_; uint32_t v___x_5735_; uint32_t v___x_5736_; uint8_t v___x_5737_; 
v___x_5734_ = 2147483648;
v___x_5735_ = lean_uint32_land(v___y_5733_, v___x_5734_);
v___x_5736_ = 0;
v___x_5737_ = lean_uint32_dec_eq(v___x_5735_, v___x_5736_);
if (v___x_5737_ == 0)
{
uint32_t v___x_5738_; uint32_t v___x_5739_; uint32_t v___x_5740_; uint32_t v___x_5741_; uint8_t v___x_5742_; 
v___x_5738_ = 23;
v___x_5739_ = lean_uint32_shift_right(v___y_5733_, v___x_5738_);
v___x_5740_ = 255;
v___x_5741_ = lean_uint32_land(v___x_5739_, v___x_5740_);
v___x_5742_ = lean_uint32_dec_eq(v___x_5741_, v___x_5740_);
if (v___x_5742_ == 0)
{
if (v___x_5742_ == 0)
{
return v___x_5736_;
}
else
{
return v___y_5733_;
}
}
else
{
uint32_t v___x_5743_; uint32_t v___x_5744_; uint8_t v___x_5745_; 
v___x_5743_ = 8388607;
v___x_5744_ = lean_uint32_land(v___y_5733_, v___x_5743_);
v___x_5745_ = lean_uint32_dec_eq(v___x_5744_, v___x_5736_);
if (v___x_5745_ == 0)
{
if (v___x_5742_ == 0)
{
return v___x_5736_;
}
else
{
return v___y_5733_;
}
}
else
{
return v___x_5736_;
}
}
}
else
{
return v___y_5733_;
}
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_ExactRuntime_depthwiseWith___at___00Submission_kernels_spec__3___lam__2___boxed(lean_object* v___x_5770_, lean_object* v___x_5771_, lean_object* v___x_5772_, lean_object* v_k_5773_, lean_object* v_kw_5774_, lean_object* v_kh_5775_, lean_object* v_s_5776_, lean_object* v_inp_5777_, lean_object* v_b_5778_, lean_object* v_wts_5779_, lean_object* v_relu_5780_, lean_object* v_stride_5781_, lean_object* v_pad_5782_, lean_object* v_h_5783_, lean_object* v_w_5784_, lean_object* v_q_5785_){
_start:
{
uint8_t v_relu_boxed_5786_; uint32_t v_res_5787_; lean_object* v_r_5788_; 
v_relu_boxed_5786_ = lean_unbox(v_relu_5780_);
v_res_5787_ = lp_competition_ExactRuntime_depthwiseWith___at___00Submission_kernels_spec__3___lam__2(v___x_5770_, v___x_5771_, v___x_5772_, v_k_5773_, v_kw_5774_, v_kh_5775_, v_s_5776_, v_inp_5777_, v_b_5778_, v_wts_5779_, v_relu_boxed_5786_, v_stride_5781_, v_pad_5782_, v_h_5783_, v_w_5784_, v_q_5785_);
lean_dec(v_q_5785_);
lean_dec_ref(v_s_5776_);
lean_dec(v___x_5772_);
lean_dec(v___x_5771_);
lean_dec(v___x_5770_);
v_r_5788_ = lean_box_uint32(v_res_5787_);
return v_r_5788_;
}
}
LEAN_EXPORT lean_object* lp_competition_ExactRuntime_depthwiseWith___at___00Submission_kernels_spec__3(lean_object* v_s_5789_, uint8_t v_relu_5790_, lean_object* v_inp_5791_, lean_object* v_wts_5792_, lean_object* v_b_5793_){
_start:
{
lean_object* v_cin_5794_; lean_object* v_h_5795_; lean_object* v_w_5796_; lean_object* v_kh_5797_; lean_object* v_kw_5798_; lean_object* v_stride_5799_; lean_object* v_pad_5800_; lean_object* v_k_5801_; lean_object* v___x_5802_; lean_object* v___x_5803_; lean_object* v___x_5804_; lean_object* v___x_5805_; lean_object* v___f_5806_; lean_object* v___x_5807_; lean_object* v___x_5808_; 
v_cin_5794_ = lean_ctor_get(v_s_5789_, 0);
lean_inc(v_cin_5794_);
v_h_5795_ = lean_ctor_get(v_s_5789_, 1);
lean_inc(v_h_5795_);
v_w_5796_ = lean_ctor_get(v_s_5789_, 2);
lean_inc(v_w_5796_);
v_kh_5797_ = lean_ctor_get(v_s_5789_, 4);
lean_inc(v_kh_5797_);
v_kw_5798_ = lean_ctor_get(v_s_5789_, 5);
lean_inc(v_kw_5798_);
v_stride_5799_ = lean_ctor_get(v_s_5789_, 6);
lean_inc(v_stride_5799_);
v_pad_5800_ = lean_ctor_get(v_s_5789_, 7);
lean_inc(v_pad_5800_);
v_k_5801_ = lean_nat_mul(v_kh_5797_, v_kw_5798_);
v___x_5802_ = lp_competition_ExactRuntime_ConvShape_ho(v_s_5789_);
v___x_5803_ = lp_competition_ExactRuntime_ConvShape_wo(v_s_5789_);
v___x_5804_ = lean_nat_mul(v___x_5802_, v___x_5803_);
v___x_5805_ = lean_box(v_relu_5790_);
lean_inc(v___x_5804_);
v___f_5806_ = lean_alloc_closure((void*)(lp_competition_ExactRuntime_depthwiseWith___at___00Submission_kernels_spec__3___lam__2___boxed), 16, 15);
lean_closure_set(v___f_5806_, 0, v___x_5804_);
lean_closure_set(v___f_5806_, 1, v___x_5803_);
lean_closure_set(v___f_5806_, 2, v___x_5802_);
lean_closure_set(v___f_5806_, 3, v_k_5801_);
lean_closure_set(v___f_5806_, 4, v_kw_5798_);
lean_closure_set(v___f_5806_, 5, v_kh_5797_);
lean_closure_set(v___f_5806_, 6, v_s_5789_);
lean_closure_set(v___f_5806_, 7, v_inp_5791_);
lean_closure_set(v___f_5806_, 8, v_b_5793_);
lean_closure_set(v___f_5806_, 9, v_wts_5792_);
lean_closure_set(v___f_5806_, 10, v___x_5805_);
lean_closure_set(v___f_5806_, 11, v_stride_5799_);
lean_closure_set(v___f_5806_, 12, v_pad_5800_);
lean_closure_set(v___f_5806_, 13, v_h_5795_);
lean_closure_set(v___f_5806_, 14, v_w_5796_);
v___x_5807_ = lean_nat_mul(v_cin_5794_, v___x_5804_);
lean_dec(v___x_5804_);
lean_dec(v_cin_5794_);
v___x_5808_ = l_Array_ofFn___redArg(v___x_5807_, v___f_5806_);
return v___x_5808_;
}
}
LEAN_EXPORT lean_object* lp_competition_ExactRuntime_depthwiseWith___at___00Submission_kernels_spec__3___boxed(lean_object* v_s_5809_, lean_object* v_relu_5810_, lean_object* v_inp_5811_, lean_object* v_wts_5812_, lean_object* v_b_5813_){
_start:
{
uint8_t v_relu_boxed_5814_; lean_object* v_res_5815_; 
v_relu_boxed_5814_ = lean_unbox(v_relu_5810_);
v_res_5815_ = lp_competition_ExactRuntime_depthwiseWith___at___00Submission_kernels_spec__3(v_s_5809_, v_relu_boxed_5814_, v_inp_5811_, v_wts_5812_, v_b_5813_);
return v_res_5815_;
}
}
lean_object* initialize_Init(uint8_t builtin);
lean_object* initialize_Init(uint8_t builtin);
lean_object* initialize_competition_ContractExact(uint8_t builtin);
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
res = initialize_competition_ContractExact(builtin);
if (lean_io_result_is_error(res)) return res;
lean_dec_ref(res);
lp_competition_Submission_Acc_empty = _init_lp_competition_Submission_Acc_empty();
lean_mark_persistent(lp_competition_Submission_Acc_empty);
lp_competition_Submission_dotX___lam__0___boxed__const__1 = _init_lp_competition_Submission_dotX___lam__0___boxed__const__1();
lean_mark_persistent(lp_competition_Submission_dotX___lam__0___boxed__const__1);
return lean_io_result_mk_ok(lean_box(0));
}
#ifdef __cplusplus
}
#endif
