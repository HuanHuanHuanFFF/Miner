// Lean compiler output
// Module: R24DotCostMain
// Imports: public import Init public meta import Init public import BenchFull public import BenchSuite public import Submission public import R24DotBarrier
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
lean_object* lean_mk_empty_array_with_capacity(lean_object*);
uint8_t lean_usize_dec_eq(size_t, size_t);
lean_object* lean_array_uget_borrowed(lean_object*, size_t);
uint8_t lean_nat_dec_lt(lean_object*, lean_object*);
size_t lean_usize_add(size_t, size_t);
lean_object* l_Lean_Name_mkStr2(lean_object*, lean_object*);
lean_object* l_Lean_Name_toStringWithToken___at___00Lean_Name_toString_spec__0(lean_object*, uint8_t);
uint32_t lp_competition_Submission_R24DotProbe_lazyPrepared(lean_object*, lean_object*);
lean_object* lean_nat_add(lean_object*, lean_object*);
lean_object* lean_nat_sub(lean_object*, lean_object*);
lean_object* lean_nat_div(lean_object*, lean_object*);
uint8_t lean_nat_dec_le(lean_object*, lean_object*);
uint32_t lp_competition_Submission_R24DotProbe_eagerPrepared(lean_object*, lean_object*);
lean_object* lean_io_mono_nanos_now();
lean_object* l_IO_lazyPure___redArg(lean_object*);
uint32_t lean_uint32_of_nat(lean_object*);
lean_object* lean_array_get_size(lean_object*);
uint32_t lp_competition_Submission_R24DotProbe_exactFull(lean_object*, lean_object*);
uint8_t lean_uint32_dec_eq(uint32_t, uint32_t);
lean_object* lean_string_append(lean_object*, lean_object*);
lean_object* lean_uint32_to_nat(uint32_t);
lean_object* l_Nat_reprFast(lean_object*);
lean_object* lean_nat_mul(lean_object*, lean_object*);
uint8_t lean_nat_dec_eq(lean_object*, lean_object*);
lean_object* lp_competition_R24DotBarrier_touchRaw(lean_object*, lean_object*);
uint32_t lean_uint32_add(uint32_t, uint32_t);
uint32_t lean_uint32_mul(uint32_t, uint32_t);
lean_object* lean_array_push(lean_object*, lean_object*);
size_t lean_array_size(lean_object*);
uint8_t lean_usize_dec_lt(size_t, size_t);
lean_object* lp_batteries_IO_println___at___00Batteries_Tactic_Lint_lintCore_spec__4(lean_object*);
lean_object* lp_proofwidgets_Lean_Json_getObjValAs_x3f___at___00ProofWidgets_MarkdownDisplay_instFromJsonProps_fromJson_spec__0(lean_object*, lean_object*);
lean_object* l_Lean_Name_mkStr1(lean_object*);
lean_object* l_Lean_Json_getObjValAs_x3f___at___00Lean_Lsp_instFromJsonLeanILeanHeaderSetupInfoParams_fromJson_spec__1(lean_object*, lean_object*);
lean_object* l_Lean_Json_getObjValAs_x3f___at___00Lean_Server_instFromJsonIlean_fromJson_spec__0(lean_object*, lean_object*);
lean_object* l_Lean_Json_getObjValD(lean_object*, lean_object*);
lean_object* l_Lean_Json_getInt_x3f(lean_object*);
lean_object* lean_array_uset(lean_object*, size_t, lean_object*);
uint32_t lp_competition_Submission_R24DotProbe_exactPrepared(lean_object*, lean_object*);
lean_object* lp_competition_R24DotBarrier_touchExact(lean_object*, lean_object*);
lean_object* l_Lean_Json_pretty(lean_object*, lean_object*);
uint32_t lp_competition_Submission_R24DotProbe_eagerFull(lean_object*, lean_object*);
uint64_t lean_uint64_of_nat(lean_object*);
uint32_t lp_competition_Submission_R24ExactDotCost_round128(uint8_t, uint64_t, uint64_t, lean_object*);
uint32_t lp_competition_Submission_R24DotProbe_lazyFull(lean_object*, lean_object*);
lean_object* lp_competition_R24DotBarrier_touchLazy(lean_object*, lean_object*);
lean_object* lean_array_uget(lean_object*, size_t);
lean_object* l_Lean_Json_getObjValAs_x3f___at___00Lean_Lsp_instFromJsonSemanticTokens_fromJson_spec__0(lean_object*, lean_object*);
lean_object* l_Lean_Json_getObjValAs_x3f___at___00Lean_Lsp_instFromJsonFileSystemWatcher_fromJson_spec__0(lean_object*, lean_object*);
lean_object* lean_io_getenv(lean_object*);
lean_object* l_IO_FS_readFile(lean_object*);
lean_object* l_Lean_Json_parse(lean_object*);
lean_object* lean_string_utf8_byte_size(lean_object*);
lean_object* l_String_Slice_toNat_x3f(lean_object*);
uint8_t lean_string_dec_eq(lean_object*, lean_object*);
lean_object* lp_competition_Submission_R24PortableF64_prepare(lean_object*);
lean_object* lp_competition_Submission_R24DotProbe_prepareEagerOperand(lean_object*);
lean_object* lp_competition_R24DotBarrier_touchEager(lean_object*, lean_object*);
lean_object* lp_competition_Submission_R24ExactDotCost_prepareOperand(lean_object*);
size_t lean_usize_of_nat(lean_object*);
uint32_t lean_uint32_shift_right(uint32_t, uint32_t);
uint32_t lean_uint32_land(uint32_t, uint32_t);
uint32_t lp_competition_Submission_R24ExactDotCost_referencePrepared(lean_object*);
uint32_t lp_competition_Submission_R24ExactDotCost_nativeLoop(lean_object*, lean_object*, uint32_t, lean_object*, uint8_t, uint64_t, uint64_t, uint64_t, uint64_t, lean_object*);
lean_object* lean_uint64_to_nat(uint64_t);
uint64_t lean_uint64_shift_right(uint64_t, uint64_t);
uint8_t lean_uint64_dec_eq(uint64_t, uint64_t);
uint64_t lean_uint64_add(uint64_t, uint64_t);
uint32_t lp_competition_Submission_R24PortableF64_attemptCold(lean_object*, lean_object*);
uint32_t lp_competition_Submission_R24PortableF64_attemptPrepared(lean_object*, lean_object*);
static const lean_string_object lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__0_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 5, .m_capacity = 5, .m_length = 4, .m_data = "name"};
static const lean_object* lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__0 = (const lean_object*)&lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__0_value;
static const lean_string_object lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__1_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 18, .m_capacity = 18, .m_length = 17, .m_data = "R24DotCostHarness"};
static const lean_object* lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__1 = (const lean_object*)&lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__1_value;
static const lean_string_object lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__2_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 8, .m_capacity = 8, .m_length = 7, .m_data = "DotCase"};
static const lean_object* lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__2 = (const lean_object*)&lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__2_value;
static const lean_ctor_object lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__3_value_aux_0 = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_ctor_object) + sizeof(void*)*2 + 8, .m_other = 2, .m_tag = 1}, .m_objs = {((lean_object*)(((size_t)(0) << 1) | 1)),((lean_object*)&lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__1_value),LEAN_SCALAR_PTR_LITERAL(225, 216, 27, 191, 156, 224, 54, 164)}};
static const lean_ctor_object lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__3_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_ctor_object) + sizeof(void*)*2 + 8, .m_other = 2, .m_tag = 1}, .m_objs = {((lean_object*)&lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__3_value_aux_0),((lean_object*)&lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__2_value),LEAN_SCALAR_PTR_LITERAL(1, 173, 141, 205, 17, 159, 123, 108)}};
static const lean_object* lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__3 = (const lean_object*)&lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__3_value;
static lean_once_cell_t lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__4_once = LEAN_ONCE_CELL_INITIALIZER;
static lean_object* lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__4;
static const lean_string_object lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__5_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 2, .m_capacity = 2, .m_length = 1, .m_data = "."};
static const lean_object* lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__5 = (const lean_object*)&lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__5_value;
static lean_once_cell_t lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__6_once = LEAN_ONCE_CELL_INITIALIZER;
static lean_object* lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__6;
static const lean_ctor_object lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__7_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_ctor_object) + sizeof(void*)*2 + 8, .m_other = 2, .m_tag = 1}, .m_objs = {((lean_object*)(((size_t)(0) << 1) | 1)),((lean_object*)&lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__0_value),LEAN_SCALAR_PTR_LITERAL(84, 246, 234, 130, 97, 205, 144, 82)}};
static const lean_object* lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__7 = (const lean_object*)&lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__7_value;
static lean_once_cell_t lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__8_once = LEAN_ONCE_CELL_INITIALIZER;
static lean_object* lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__8;
static lean_once_cell_t lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__9_once = LEAN_ONCE_CELL_INITIALIZER;
static lean_object* lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__9;
static const lean_string_object lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__10_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 3, .m_capacity = 3, .m_length = 2, .m_data = ": "};
static const lean_object* lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__10 = (const lean_object*)&lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__10_value;
static lean_once_cell_t lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__11_once = LEAN_ONCE_CELL_INITIALIZER;
static lean_object* lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__11;
static const lean_string_object lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__12_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 6, .m_capacity = 6, .m_length = 5, .m_data = "group"};
static const lean_object* lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__12 = (const lean_object*)&lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__12_value;
static const lean_ctor_object lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__13_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_ctor_object) + sizeof(void*)*2 + 8, .m_other = 2, .m_tag = 1}, .m_objs = {((lean_object*)(((size_t)(0) << 1) | 1)),((lean_object*)&lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__12_value),LEAN_SCALAR_PTR_LITERAL(206, 113, 20, 57, 188, 177, 187, 30)}};
static const lean_object* lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__13 = (const lean_object*)&lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__13_value;
static lean_once_cell_t lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__14_once = LEAN_ONCE_CELL_INITIALIZER;
static lean_object* lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__14;
static lean_once_cell_t lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__15_once = LEAN_ONCE_CELL_INITIALIZER;
static lean_object* lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__15;
static lean_once_cell_t lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__16_once = LEAN_ONCE_CELL_INITIALIZER;
static lean_object* lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__16;
static const lean_string_object lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__17_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 5, .m_capacity = 5, .m_length = 4, .m_data = "kind"};
static const lean_object* lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__17 = (const lean_object*)&lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__17_value;
static const lean_ctor_object lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__18_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_ctor_object) + sizeof(void*)*2 + 8, .m_other = 2, .m_tag = 1}, .m_objs = {((lean_object*)(((size_t)(0) << 1) | 1)),((lean_object*)&lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__17_value),LEAN_SCALAR_PTR_LITERAL(90, 186, 66, 236, 16, 221, 215, 158)}};
static const lean_object* lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__18 = (const lean_object*)&lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__18_value;
static lean_once_cell_t lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__19_once = LEAN_ONCE_CELL_INITIALIZER;
static lean_object* lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__19;
static lean_once_cell_t lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__20_once = LEAN_ONCE_CELL_INITIALIZER;
static lean_object* lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__20;
static lean_once_cell_t lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__21_once = LEAN_ONCE_CELL_INITIALIZER;
static lean_object* lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__21;
static const lean_string_object lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__22_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 2, .m_capacity = 2, .m_length = 1, .m_data = "x"};
static const lean_object* lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__22 = (const lean_object*)&lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__22_value;
static const lean_ctor_object lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__23_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_ctor_object) + sizeof(void*)*2 + 8, .m_other = 2, .m_tag = 1}, .m_objs = {((lean_object*)(((size_t)(0) << 1) | 1)),((lean_object*)&lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__22_value),LEAN_SCALAR_PTR_LITERAL(243, 101, 181, 186, 114, 114, 131, 189)}};
static const lean_object* lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__23 = (const lean_object*)&lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__23_value;
static lean_once_cell_t lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__24_once = LEAN_ONCE_CELL_INITIALIZER;
static lean_object* lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__24;
static lean_once_cell_t lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__25_once = LEAN_ONCE_CELL_INITIALIZER;
static lean_object* lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__25;
static lean_once_cell_t lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__26_once = LEAN_ONCE_CELL_INITIALIZER;
static lean_object* lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__26;
static const lean_string_object lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__27_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 2, .m_capacity = 2, .m_length = 1, .m_data = "y"};
static const lean_object* lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__27 = (const lean_object*)&lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__27_value;
static const lean_ctor_object lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__28_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_ctor_object) + sizeof(void*)*2 + 8, .m_other = 2, .m_tag = 1}, .m_objs = {((lean_object*)(((size_t)(0) << 1) | 1)),((lean_object*)&lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__27_value),LEAN_SCALAR_PTR_LITERAL(72, 55, 55, 9, 143, 73, 230, 150)}};
static const lean_object* lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__28 = (const lean_object*)&lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__28_value;
static lean_once_cell_t lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__29_once = LEAN_ONCE_CELL_INITIALIZER;
static lean_object* lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__29;
static lean_once_cell_t lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__30_once = LEAN_ONCE_CELL_INITIALIZER;
static lean_object* lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__30;
static lean_once_cell_t lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__31_once = LEAN_ONCE_CELL_INITIALIZER;
static lean_object* lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__31;
static const lean_string_object lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__32_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 9, .m_capacity = 9, .m_length = 8, .m_data = "expected"};
static const lean_object* lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__32 = (const lean_object*)&lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__32_value;
static const lean_ctor_object lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__33_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_ctor_object) + sizeof(void*)*2 + 8, .m_other = 2, .m_tag = 1}, .m_objs = {((lean_object*)(((size_t)(0) << 1) | 1)),((lean_object*)&lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__32_value),LEAN_SCALAR_PTR_LITERAL(224, 71, 164, 120, 254, 151, 172, 142)}};
static const lean_object* lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__33 = (const lean_object*)&lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__33_value;
static lean_once_cell_t lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__34_once = LEAN_ONCE_CELL_INITIALIZER;
static lean_object* lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__34;
static lean_once_cell_t lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__35_once = LEAN_ONCE_CELL_INITIALIZER;
static lean_object* lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__35;
static lean_once_cell_t lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__36_once = LEAN_ONCE_CELL_INITIALIZER;
static lean_object* lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__36;
static const lean_string_object lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__37_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 12, .m_capacity = 12, .m_length = 11, .m_data = "fast_result"};
static const lean_object* lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__37 = (const lean_object*)&lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__37_value;
static const lean_ctor_object lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__38_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_ctor_object) + sizeof(void*)*2 + 8, .m_other = 2, .m_tag = 1}, .m_objs = {((lean_object*)(((size_t)(0) << 1) | 1)),((lean_object*)&lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__37_value),LEAN_SCALAR_PTR_LITERAL(25, 58, 183, 95, 200, 247, 67, 141)}};
static const lean_object* lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__38 = (const lean_object*)&lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__38_value;
static lean_once_cell_t lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__39_once = LEAN_ONCE_CELL_INITIALIZER;
static lean_object* lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__39;
static lean_once_cell_t lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__40_once = LEAN_ONCE_CELL_INITIALIZER;
static lean_object* lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__40;
static lean_once_cell_t lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__41_once = LEAN_ONCE_CELL_INITIALIZER;
static lean_object* lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__41;
static const lean_string_object lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__42_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 6, .m_capacity = 6, .m_length = 5, .m_data = "timed"};
static const lean_object* lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__42 = (const lean_object*)&lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__42_value;
static const lean_ctor_object lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__43_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_ctor_object) + sizeof(void*)*2 + 8, .m_other = 2, .m_tag = 1}, .m_objs = {((lean_object*)(((size_t)(0) << 1) | 1)),((lean_object*)&lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__42_value),LEAN_SCALAR_PTR_LITERAL(136, 54, 60, 30, 1, 8, 250, 239)}};
static const lean_object* lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__43 = (const lean_object*)&lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__43_value;
static lean_once_cell_t lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__44_once = LEAN_ONCE_CELL_INITIALIZER;
static lean_object* lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__44;
static lean_once_cell_t lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__45_once = LEAN_ONCE_CELL_INITIALIZER;
static lean_object* lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__45;
static lean_once_cell_t lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__46_once = LEAN_ONCE_CELL_INITIALIZER;
static lean_object* lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__46;
LEAN_EXPORT lean_object* lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson(lean_object*);
static const lean_closure_object lp_competition_R24DotCostHarness_instFromJsonDotCase___closed__0_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_closure_object) + sizeof(void*)*0, .m_other = 0, .m_tag = 245}, .m_fun = (void*)lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson, .m_arity = 1, .m_num_fixed = 0, .m_objs = {} };
static const lean_object* lp_competition_R24DotCostHarness_instFromJsonDotCase___closed__0 = (const lean_object*)&lp_competition_R24DotCostHarness_instFromJsonDotCase___closed__0_value;
LEAN_EXPORT const lean_object* lp_competition_R24DotCostHarness_instFromJsonDotCase = (const lean_object*)&lp_competition_R24DotCostHarness_instFromJsonDotCase___closed__0_value;
LEAN_EXPORT lean_object* lp_competition_Lean_Json_getObjValAs_x3f___at___00R24DotCostHarness_instFromJsonRoundCase_fromJson_spec__0(lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_Lean_Json_getObjValAs_x3f___at___00R24DotCostHarness_instFromJsonRoundCase_fromJson_spec__0___boxed(lean_object*, lean_object*);
static const lean_string_object lp_competition_R24DotCostHarness_instFromJsonRoundCase_fromJson___closed__0_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 3, .m_capacity = 3, .m_length = 2, .m_data = "id"};
static const lean_object* lp_competition_R24DotCostHarness_instFromJsonRoundCase_fromJson___closed__0 = (const lean_object*)&lp_competition_R24DotCostHarness_instFromJsonRoundCase_fromJson___closed__0_value;
static const lean_string_object lp_competition_R24DotCostHarness_instFromJsonRoundCase_fromJson___closed__1_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 10, .m_capacity = 10, .m_length = 9, .m_data = "RoundCase"};
static const lean_object* lp_competition_R24DotCostHarness_instFromJsonRoundCase_fromJson___closed__1 = (const lean_object*)&lp_competition_R24DotCostHarness_instFromJsonRoundCase_fromJson___closed__1_value;
static const lean_ctor_object lp_competition_R24DotCostHarness_instFromJsonRoundCase_fromJson___closed__2_value_aux_0 = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_ctor_object) + sizeof(void*)*2 + 8, .m_other = 2, .m_tag = 1}, .m_objs = {((lean_object*)(((size_t)(0) << 1) | 1)),((lean_object*)&lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__1_value),LEAN_SCALAR_PTR_LITERAL(225, 216, 27, 191, 156, 224, 54, 164)}};
static const lean_ctor_object lp_competition_R24DotCostHarness_instFromJsonRoundCase_fromJson___closed__2_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_ctor_object) + sizeof(void*)*2 + 8, .m_other = 2, .m_tag = 1}, .m_objs = {((lean_object*)&lp_competition_R24DotCostHarness_instFromJsonRoundCase_fromJson___closed__2_value_aux_0),((lean_object*)&lp_competition_R24DotCostHarness_instFromJsonRoundCase_fromJson___closed__1_value),LEAN_SCALAR_PTR_LITERAL(187, 60, 111, 59, 166, 26, 213, 152)}};
static const lean_object* lp_competition_R24DotCostHarness_instFromJsonRoundCase_fromJson___closed__2 = (const lean_object*)&lp_competition_R24DotCostHarness_instFromJsonRoundCase_fromJson___closed__2_value;
static lean_once_cell_t lp_competition_R24DotCostHarness_instFromJsonRoundCase_fromJson___closed__3_once = LEAN_ONCE_CELL_INITIALIZER;
static lean_object* lp_competition_R24DotCostHarness_instFromJsonRoundCase_fromJson___closed__3;
static lean_once_cell_t lp_competition_R24DotCostHarness_instFromJsonRoundCase_fromJson___closed__4_once = LEAN_ONCE_CELL_INITIALIZER;
static lean_object* lp_competition_R24DotCostHarness_instFromJsonRoundCase_fromJson___closed__4;
static const lean_ctor_object lp_competition_R24DotCostHarness_instFromJsonRoundCase_fromJson___closed__5_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_ctor_object) + sizeof(void*)*2 + 8, .m_other = 2, .m_tag = 1}, .m_objs = {((lean_object*)(((size_t)(0) << 1) | 1)),((lean_object*)&lp_competition_R24DotCostHarness_instFromJsonRoundCase_fromJson___closed__0_value),LEAN_SCALAR_PTR_LITERAL(223, 78, 141, 85, 50, 255, 216, 83)}};
static const lean_object* lp_competition_R24DotCostHarness_instFromJsonRoundCase_fromJson___closed__5 = (const lean_object*)&lp_competition_R24DotCostHarness_instFromJsonRoundCase_fromJson___closed__5_value;
static lean_once_cell_t lp_competition_R24DotCostHarness_instFromJsonRoundCase_fromJson___closed__6_once = LEAN_ONCE_CELL_INITIALIZER;
static lean_object* lp_competition_R24DotCostHarness_instFromJsonRoundCase_fromJson___closed__6;
static lean_once_cell_t lp_competition_R24DotCostHarness_instFromJsonRoundCase_fromJson___closed__7_once = LEAN_ONCE_CELL_INITIALIZER;
static lean_object* lp_competition_R24DotCostHarness_instFromJsonRoundCase_fromJson___closed__7;
static lean_once_cell_t lp_competition_R24DotCostHarness_instFromJsonRoundCase_fromJson___closed__8_once = LEAN_ONCE_CELL_INITIALIZER;
static lean_object* lp_competition_R24DotCostHarness_instFromJsonRoundCase_fromJson___closed__8;
static const lean_string_object lp_competition_R24DotCostHarness_instFromJsonRoundCase_fromJson___closed__9_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 9, .m_capacity = 9, .m_length = 8, .m_data = "negative"};
static const lean_object* lp_competition_R24DotCostHarness_instFromJsonRoundCase_fromJson___closed__9 = (const lean_object*)&lp_competition_R24DotCostHarness_instFromJsonRoundCase_fromJson___closed__9_value;
static const lean_ctor_object lp_competition_R24DotCostHarness_instFromJsonRoundCase_fromJson___closed__10_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_ctor_object) + sizeof(void*)*2 + 8, .m_other = 2, .m_tag = 1}, .m_objs = {((lean_object*)(((size_t)(0) << 1) | 1)),((lean_object*)&lp_competition_R24DotCostHarness_instFromJsonRoundCase_fromJson___closed__9_value),LEAN_SCALAR_PTR_LITERAL(75, 116, 184, 180, 201, 96, 101, 171)}};
static const lean_object* lp_competition_R24DotCostHarness_instFromJsonRoundCase_fromJson___closed__10 = (const lean_object*)&lp_competition_R24DotCostHarness_instFromJsonRoundCase_fromJson___closed__10_value;
static lean_once_cell_t lp_competition_R24DotCostHarness_instFromJsonRoundCase_fromJson___closed__11_once = LEAN_ONCE_CELL_INITIALIZER;
static lean_object* lp_competition_R24DotCostHarness_instFromJsonRoundCase_fromJson___closed__11;
static lean_once_cell_t lp_competition_R24DotCostHarness_instFromJsonRoundCase_fromJson___closed__12_once = LEAN_ONCE_CELL_INITIALIZER;
static lean_object* lp_competition_R24DotCostHarness_instFromJsonRoundCase_fromJson___closed__12;
static lean_once_cell_t lp_competition_R24DotCostHarness_instFromJsonRoundCase_fromJson___closed__13_once = LEAN_ONCE_CELL_INITIALIZER;
static lean_object* lp_competition_R24DotCostHarness_instFromJsonRoundCase_fromJson___closed__13;
static const lean_string_object lp_competition_R24DotCostHarness_instFromJsonRoundCase_fromJson___closed__14_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 3, .m_capacity = 3, .m_length = 2, .m_data = "lo"};
static const lean_object* lp_competition_R24DotCostHarness_instFromJsonRoundCase_fromJson___closed__14 = (const lean_object*)&lp_competition_R24DotCostHarness_instFromJsonRoundCase_fromJson___closed__14_value;
static const lean_ctor_object lp_competition_R24DotCostHarness_instFromJsonRoundCase_fromJson___closed__15_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_ctor_object) + sizeof(void*)*2 + 8, .m_other = 2, .m_tag = 1}, .m_objs = {((lean_object*)(((size_t)(0) << 1) | 1)),((lean_object*)&lp_competition_R24DotCostHarness_instFromJsonRoundCase_fromJson___closed__14_value),LEAN_SCALAR_PTR_LITERAL(13, 201, 230, 212, 81, 25, 45, 175)}};
static const lean_object* lp_competition_R24DotCostHarness_instFromJsonRoundCase_fromJson___closed__15 = (const lean_object*)&lp_competition_R24DotCostHarness_instFromJsonRoundCase_fromJson___closed__15_value;
static lean_once_cell_t lp_competition_R24DotCostHarness_instFromJsonRoundCase_fromJson___closed__16_once = LEAN_ONCE_CELL_INITIALIZER;
static lean_object* lp_competition_R24DotCostHarness_instFromJsonRoundCase_fromJson___closed__16;
static lean_once_cell_t lp_competition_R24DotCostHarness_instFromJsonRoundCase_fromJson___closed__17_once = LEAN_ONCE_CELL_INITIALIZER;
static lean_object* lp_competition_R24DotCostHarness_instFromJsonRoundCase_fromJson___closed__17;
static lean_once_cell_t lp_competition_R24DotCostHarness_instFromJsonRoundCase_fromJson___closed__18_once = LEAN_ONCE_CELL_INITIALIZER;
static lean_object* lp_competition_R24DotCostHarness_instFromJsonRoundCase_fromJson___closed__18;
static const lean_string_object lp_competition_R24DotCostHarness_instFromJsonRoundCase_fromJson___closed__19_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 3, .m_capacity = 3, .m_length = 2, .m_data = "hi"};
static const lean_object* lp_competition_R24DotCostHarness_instFromJsonRoundCase_fromJson___closed__19 = (const lean_object*)&lp_competition_R24DotCostHarness_instFromJsonRoundCase_fromJson___closed__19_value;
static const lean_ctor_object lp_competition_R24DotCostHarness_instFromJsonRoundCase_fromJson___closed__20_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_ctor_object) + sizeof(void*)*2 + 8, .m_other = 2, .m_tag = 1}, .m_objs = {((lean_object*)(((size_t)(0) << 1) | 1)),((lean_object*)&lp_competition_R24DotCostHarness_instFromJsonRoundCase_fromJson___closed__19_value),LEAN_SCALAR_PTR_LITERAL(13, 105, 183, 27, 151, 203, 27, 169)}};
static const lean_object* lp_competition_R24DotCostHarness_instFromJsonRoundCase_fromJson___closed__20 = (const lean_object*)&lp_competition_R24DotCostHarness_instFromJsonRoundCase_fromJson___closed__20_value;
static lean_once_cell_t lp_competition_R24DotCostHarness_instFromJsonRoundCase_fromJson___closed__21_once = LEAN_ONCE_CELL_INITIALIZER;
static lean_object* lp_competition_R24DotCostHarness_instFromJsonRoundCase_fromJson___closed__21;
static lean_once_cell_t lp_competition_R24DotCostHarness_instFromJsonRoundCase_fromJson___closed__22_once = LEAN_ONCE_CELL_INITIALIZER;
static lean_object* lp_competition_R24DotCostHarness_instFromJsonRoundCase_fromJson___closed__22;
static lean_once_cell_t lp_competition_R24DotCostHarness_instFromJsonRoundCase_fromJson___closed__23_once = LEAN_ONCE_CELL_INITIALIZER;
static lean_object* lp_competition_R24DotCostHarness_instFromJsonRoundCase_fromJson___closed__23;
static const lean_string_object lp_competition_R24DotCostHarness_instFromJsonRoundCase_fromJson___closed__24_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 5, .m_capacity = 5, .m_length = 4, .m_data = "base"};
static const lean_object* lp_competition_R24DotCostHarness_instFromJsonRoundCase_fromJson___closed__24 = (const lean_object*)&lp_competition_R24DotCostHarness_instFromJsonRoundCase_fromJson___closed__24_value;
static const lean_ctor_object lp_competition_R24DotCostHarness_instFromJsonRoundCase_fromJson___closed__25_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_ctor_object) + sizeof(void*)*2 + 8, .m_other = 2, .m_tag = 1}, .m_objs = {((lean_object*)(((size_t)(0) << 1) | 1)),((lean_object*)&lp_competition_R24DotCostHarness_instFromJsonRoundCase_fromJson___closed__24_value),LEAN_SCALAR_PTR_LITERAL(203, 140, 185, 197, 212, 99, 116, 238)}};
static const lean_object* lp_competition_R24DotCostHarness_instFromJsonRoundCase_fromJson___closed__25 = (const lean_object*)&lp_competition_R24DotCostHarness_instFromJsonRoundCase_fromJson___closed__25_value;
static lean_once_cell_t lp_competition_R24DotCostHarness_instFromJsonRoundCase_fromJson___closed__26_once = LEAN_ONCE_CELL_INITIALIZER;
static lean_object* lp_competition_R24DotCostHarness_instFromJsonRoundCase_fromJson___closed__26;
static lean_once_cell_t lp_competition_R24DotCostHarness_instFromJsonRoundCase_fromJson___closed__27_once = LEAN_ONCE_CELL_INITIALIZER;
static lean_object* lp_competition_R24DotCostHarness_instFromJsonRoundCase_fromJson___closed__27;
static lean_once_cell_t lp_competition_R24DotCostHarness_instFromJsonRoundCase_fromJson___closed__28_once = LEAN_ONCE_CELL_INITIALIZER;
static lean_object* lp_competition_R24DotCostHarness_instFromJsonRoundCase_fromJson___closed__28;
static lean_once_cell_t lp_competition_R24DotCostHarness_instFromJsonRoundCase_fromJson___closed__29_once = LEAN_ONCE_CELL_INITIALIZER;
static lean_object* lp_competition_R24DotCostHarness_instFromJsonRoundCase_fromJson___closed__29;
static lean_once_cell_t lp_competition_R24DotCostHarness_instFromJsonRoundCase_fromJson___closed__30_once = LEAN_ONCE_CELL_INITIALIZER;
static lean_object* lp_competition_R24DotCostHarness_instFromJsonRoundCase_fromJson___closed__30;
LEAN_EXPORT lean_object* lp_competition_R24DotCostHarness_instFromJsonRoundCase_fromJson(lean_object*);
static const lean_closure_object lp_competition_R24DotCostHarness_instFromJsonRoundCase___closed__0_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_closure_object) + sizeof(void*)*0, .m_other = 0, .m_tag = 245}, .m_fun = (void*)lp_competition_R24DotCostHarness_instFromJsonRoundCase_fromJson, .m_arity = 1, .m_num_fixed = 0, .m_objs = {} };
static const lean_object* lp_competition_R24DotCostHarness_instFromJsonRoundCase___closed__0 = (const lean_object*)&lp_competition_R24DotCostHarness_instFromJsonRoundCase___closed__0_value;
LEAN_EXPORT const lean_object* lp_competition_R24DotCostHarness_instFromJsonRoundCase = (const lean_object*)&lp_competition_R24DotCostHarness_instFromJsonRoundCase___closed__0_value;
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_mapMUnsafe_map___at___00Lean_Array_fromJson_x3f___at___00Lean_Json_getObjValAs_x3f___at___00R24DotCostHarness_instFromJsonPlan_fromJson_spec__1_spec__2_spec__4(size_t, size_t, lean_object*);
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_mapMUnsafe_map___at___00Lean_Array_fromJson_x3f___at___00Lean_Json_getObjValAs_x3f___at___00R24DotCostHarness_instFromJsonPlan_fromJson_spec__1_spec__2_spec__4___boxed(lean_object*, lean_object*, lean_object*);
static const lean_string_object lp_competition_Lean_Array_fromJson_x3f___at___00Lean_Json_getObjValAs_x3f___at___00R24DotCostHarness_instFromJsonPlan_fromJson_spec__1_spec__2___closed__0_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 27, .m_capacity = 27, .m_length = 26, .m_data = "expected JSON array, got '"};
static const lean_object* lp_competition_Lean_Array_fromJson_x3f___at___00Lean_Json_getObjValAs_x3f___at___00R24DotCostHarness_instFromJsonPlan_fromJson_spec__1_spec__2___closed__0 = (const lean_object*)&lp_competition_Lean_Array_fromJson_x3f___at___00Lean_Json_getObjValAs_x3f___at___00R24DotCostHarness_instFromJsonPlan_fromJson_spec__1_spec__2___closed__0_value;
static const lean_string_object lp_competition_Lean_Array_fromJson_x3f___at___00Lean_Json_getObjValAs_x3f___at___00R24DotCostHarness_instFromJsonPlan_fromJson_spec__1_spec__2___closed__1_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 2, .m_capacity = 2, .m_length = 1, .m_data = "'"};
static const lean_object* lp_competition_Lean_Array_fromJson_x3f___at___00Lean_Json_getObjValAs_x3f___at___00R24DotCostHarness_instFromJsonPlan_fromJson_spec__1_spec__2___closed__1 = (const lean_object*)&lp_competition_Lean_Array_fromJson_x3f___at___00Lean_Json_getObjValAs_x3f___at___00R24DotCostHarness_instFromJsonPlan_fromJson_spec__1_spec__2___closed__1_value;
LEAN_EXPORT lean_object* lp_competition_Lean_Array_fromJson_x3f___at___00Lean_Json_getObjValAs_x3f___at___00R24DotCostHarness_instFromJsonPlan_fromJson_spec__1_spec__2(lean_object*);
LEAN_EXPORT lean_object* lp_competition_Lean_Json_getObjValAs_x3f___at___00R24DotCostHarness_instFromJsonPlan_fromJson_spec__1(lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_Lean_Json_getObjValAs_x3f___at___00R24DotCostHarness_instFromJsonPlan_fromJson_spec__1___boxed(lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_mapMUnsafe_map___at___00Lean_Array_fromJson_x3f___at___00Lean_Json_getObjValAs_x3f___at___00R24DotCostHarness_instFromJsonPlan_fromJson_spec__0_spec__0_spec__1(size_t, size_t, lean_object*);
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_mapMUnsafe_map___at___00Lean_Array_fromJson_x3f___at___00Lean_Json_getObjValAs_x3f___at___00R24DotCostHarness_instFromJsonPlan_fromJson_spec__0_spec__0_spec__1___boxed(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_Lean_Array_fromJson_x3f___at___00Lean_Json_getObjValAs_x3f___at___00R24DotCostHarness_instFromJsonPlan_fromJson_spec__0_spec__0(lean_object*);
LEAN_EXPORT lean_object* lp_competition_Lean_Json_getObjValAs_x3f___at___00R24DotCostHarness_instFromJsonPlan_fromJson_spec__0(lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_Lean_Json_getObjValAs_x3f___at___00R24DotCostHarness_instFromJsonPlan_fromJson_spec__0___boxed(lean_object*, lean_object*);
static const lean_string_object lp_competition_R24DotCostHarness_instFromJsonPlan_fromJson___closed__0_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 6, .m_capacity = 6, .m_length = 5, .m_data = "cases"};
static const lean_object* lp_competition_R24DotCostHarness_instFromJsonPlan_fromJson___closed__0 = (const lean_object*)&lp_competition_R24DotCostHarness_instFromJsonPlan_fromJson___closed__0_value;
static const lean_string_object lp_competition_R24DotCostHarness_instFromJsonPlan_fromJson___closed__1_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 5, .m_capacity = 5, .m_length = 4, .m_data = "Plan"};
static const lean_object* lp_competition_R24DotCostHarness_instFromJsonPlan_fromJson___closed__1 = (const lean_object*)&lp_competition_R24DotCostHarness_instFromJsonPlan_fromJson___closed__1_value;
static const lean_ctor_object lp_competition_R24DotCostHarness_instFromJsonPlan_fromJson___closed__2_value_aux_0 = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_ctor_object) + sizeof(void*)*2 + 8, .m_other = 2, .m_tag = 1}, .m_objs = {((lean_object*)(((size_t)(0) << 1) | 1)),((lean_object*)&lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__1_value),LEAN_SCALAR_PTR_LITERAL(225, 216, 27, 191, 156, 224, 54, 164)}};
static const lean_ctor_object lp_competition_R24DotCostHarness_instFromJsonPlan_fromJson___closed__2_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_ctor_object) + sizeof(void*)*2 + 8, .m_other = 2, .m_tag = 1}, .m_objs = {((lean_object*)&lp_competition_R24DotCostHarness_instFromJsonPlan_fromJson___closed__2_value_aux_0),((lean_object*)&lp_competition_R24DotCostHarness_instFromJsonPlan_fromJson___closed__1_value),LEAN_SCALAR_PTR_LITERAL(203, 37, 11, 203, 33, 119, 32, 178)}};
static const lean_object* lp_competition_R24DotCostHarness_instFromJsonPlan_fromJson___closed__2 = (const lean_object*)&lp_competition_R24DotCostHarness_instFromJsonPlan_fromJson___closed__2_value;
static lean_once_cell_t lp_competition_R24DotCostHarness_instFromJsonPlan_fromJson___closed__3_once = LEAN_ONCE_CELL_INITIALIZER;
static lean_object* lp_competition_R24DotCostHarness_instFromJsonPlan_fromJson___closed__3;
static lean_once_cell_t lp_competition_R24DotCostHarness_instFromJsonPlan_fromJson___closed__4_once = LEAN_ONCE_CELL_INITIALIZER;
static lean_object* lp_competition_R24DotCostHarness_instFromJsonPlan_fromJson___closed__4;
static const lean_ctor_object lp_competition_R24DotCostHarness_instFromJsonPlan_fromJson___closed__5_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_ctor_object) + sizeof(void*)*2 + 8, .m_other = 2, .m_tag = 1}, .m_objs = {((lean_object*)(((size_t)(0) << 1) | 1)),((lean_object*)&lp_competition_R24DotCostHarness_instFromJsonPlan_fromJson___closed__0_value),LEAN_SCALAR_PTR_LITERAL(220, 93, 203, 178, 149, 199, 118, 190)}};
static const lean_object* lp_competition_R24DotCostHarness_instFromJsonPlan_fromJson___closed__5 = (const lean_object*)&lp_competition_R24DotCostHarness_instFromJsonPlan_fromJson___closed__5_value;
static lean_once_cell_t lp_competition_R24DotCostHarness_instFromJsonPlan_fromJson___closed__6_once = LEAN_ONCE_CELL_INITIALIZER;
static lean_object* lp_competition_R24DotCostHarness_instFromJsonPlan_fromJson___closed__6;
static lean_once_cell_t lp_competition_R24DotCostHarness_instFromJsonPlan_fromJson___closed__7_once = LEAN_ONCE_CELL_INITIALIZER;
static lean_object* lp_competition_R24DotCostHarness_instFromJsonPlan_fromJson___closed__7;
static lean_once_cell_t lp_competition_R24DotCostHarness_instFromJsonPlan_fromJson___closed__8_once = LEAN_ONCE_CELL_INITIALIZER;
static lean_object* lp_competition_R24DotCostHarness_instFromJsonPlan_fromJson___closed__8;
static const lean_string_object lp_competition_R24DotCostHarness_instFromJsonPlan_fromJson___closed__9_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 12, .m_capacity = 12, .m_length = 11, .m_data = "round_cases"};
static const lean_object* lp_competition_R24DotCostHarness_instFromJsonPlan_fromJson___closed__9 = (const lean_object*)&lp_competition_R24DotCostHarness_instFromJsonPlan_fromJson___closed__9_value;
static const lean_ctor_object lp_competition_R24DotCostHarness_instFromJsonPlan_fromJson___closed__10_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_ctor_object) + sizeof(void*)*2 + 8, .m_other = 2, .m_tag = 1}, .m_objs = {((lean_object*)(((size_t)(0) << 1) | 1)),((lean_object*)&lp_competition_R24DotCostHarness_instFromJsonPlan_fromJson___closed__9_value),LEAN_SCALAR_PTR_LITERAL(123, 178, 22, 243, 79, 61, 60, 123)}};
static const lean_object* lp_competition_R24DotCostHarness_instFromJsonPlan_fromJson___closed__10 = (const lean_object*)&lp_competition_R24DotCostHarness_instFromJsonPlan_fromJson___closed__10_value;
static lean_once_cell_t lp_competition_R24DotCostHarness_instFromJsonPlan_fromJson___closed__11_once = LEAN_ONCE_CELL_INITIALIZER;
static lean_object* lp_competition_R24DotCostHarness_instFromJsonPlan_fromJson___closed__11;
static lean_once_cell_t lp_competition_R24DotCostHarness_instFromJsonPlan_fromJson___closed__12_once = LEAN_ONCE_CELL_INITIALIZER;
static lean_object* lp_competition_R24DotCostHarness_instFromJsonPlan_fromJson___closed__12;
static lean_once_cell_t lp_competition_R24DotCostHarness_instFromJsonPlan_fromJson___closed__13_once = LEAN_ONCE_CELL_INITIALIZER;
static lean_object* lp_competition_R24DotCostHarness_instFromJsonPlan_fromJson___closed__13;
LEAN_EXPORT lean_object* lp_competition_R24DotCostHarness_instFromJsonPlan_fromJson(lean_object*);
static const lean_closure_object lp_competition_R24DotCostHarness_instFromJsonPlan___closed__0_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_closure_object) + sizeof(void*)*0, .m_other = 0, .m_tag = 245}, .m_fun = (void*)lp_competition_R24DotCostHarness_instFromJsonPlan_fromJson, .m_arity = 1, .m_num_fixed = 0, .m_objs = {} };
static const lean_object* lp_competition_R24DotCostHarness_instFromJsonPlan___closed__0 = (const lean_object*)&lp_competition_R24DotCostHarness_instFromJsonPlan___closed__0_value;
LEAN_EXPORT const lean_object* lp_competition_R24DotCostHarness_instFromJsonPlan = (const lean_object*)&lp_competition_R24DotCostHarness_instFromJsonPlan___closed__0_value;
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_mapMUnsafe_map___at___00R24DotCostHarness_words_spec__0(size_t, size_t, lean_object*);
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_mapMUnsafe_map___at___00R24DotCostHarness_words_spec__0___boxed(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_R24DotCostHarness_words(lean_object*);
LEAN_EXPORT uint8_t lp_competition___private_Init_Data_Array_Basic_0__Array_anyMUnsafe_any___at___00R24DotCostHarness_supported_spec__0(lean_object*, lean_object*, lean_object*, size_t, size_t);
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_anyMUnsafe_any___at___00R24DotCostHarness_supported_spec__0___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT uint8_t lp_competition___private_Init_Data_Array_Basic_0__Array_anyMUnsafe_any___at___00R24DotCostHarness_supported_spec__1(lean_object*, lean_object*, lean_object*, size_t, size_t);
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_anyMUnsafe_any___at___00R24DotCostHarness_supported_spec__1___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT uint8_t lp_competition_R24DotCostHarness_supported(lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_R24DotCostHarness_supported___boxed(lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_R24DotCostHarness_repeats(lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_R24DotCostHarness_repeats___boxed(lean_object*, lean_object*);
LEAN_EXPORT uint32_t lp_competition_R24DotCostHarness_seed(lean_object*);
LEAN_EXPORT lean_object* lp_competition_R24DotCostHarness_seed___boxed(lean_object*);
LEAN_EXPORT uint32_t lp_competition_R24DotCostHarness_sinkExpected(uint32_t, uint32_t, lean_object*);
LEAN_EXPORT lean_object* lp_competition_R24DotCostHarness_sinkExpected___boxed(lean_object*, lean_object*, lean_object*);
static const lean_string_object lp_competition_R24DotCostHarness_checkWord___closed__0_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 6, .m_capacity = 6, .m_length = 5, .m_data = " got="};
static const lean_object* lp_competition_R24DotCostHarness_checkWord___closed__0 = (const lean_object*)&lp_competition_R24DotCostHarness_checkWord___closed__0_value;
static const lean_string_object lp_competition_R24DotCostHarness_checkWord___closed__1_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 11, .m_capacity = 11, .m_length = 10, .m_data = " expected="};
static const lean_object* lp_competition_R24DotCostHarness_checkWord___closed__1 = (const lean_object*)&lp_competition_R24DotCostHarness_checkWord___closed__1_value;
LEAN_EXPORT lean_object* lp_competition_R24DotCostHarness_checkWord(lean_object*, lean_object*, uint32_t, uint32_t);
LEAN_EXPORT lean_object* lp_competition_R24DotCostHarness_checkWord___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
static const lean_string_object lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotCostHarness_emit_spec__0___closed__0_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 12, .m_capacity = 12, .m_length = 11, .m_data = "DOT_SAMPLE\t"};
static const lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotCostHarness_emit_spec__0___closed__0 = (const lean_object*)&lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotCostHarness_emit_spec__0___closed__0_value;
static const lean_string_object lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotCostHarness_emit_spec__0___closed__1_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 2, .m_capacity = 2, .m_length = 1, .m_data = "\t"};
static const lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotCostHarness_emit_spec__0___closed__1 = (const lean_object*)&lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotCostHarness_emit_spec__0___closed__1_value;
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotCostHarness_emit_spec__0(lean_object*, lean_object*, lean_object*, lean_object*, size_t, size_t, uint32_t);
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotCostHarness_emit_spec__0___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
static const lean_string_object lp_competition_R24DotCostHarness_emit___closed__0_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 11, .m_capacity = 11, .m_length = 10, .m_data = "DOT_SETUP\t"};
static const lean_object* lp_competition_R24DotCostHarness_emit___closed__0 = (const lean_object*)&lp_competition_R24DotCostHarness_emit___closed__0_value;
LEAN_EXPORT lean_object* lp_competition_R24DotCostHarness_emit(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_R24DotCostHarness_emit___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT uint32_t lp_competition_R24DotCostHarness_passExactFull(lean_object*, uint32_t, lean_object*);
LEAN_EXPORT lean_object* lp_competition_R24DotCostHarness_passExactFull___boxed(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_R24DotCostHarness_benchExactFull___lam__0();
LEAN_EXPORT lean_object* lp_competition_R24DotCostHarness_benchExactFull___lam__0___boxed(lean_object*);
LEAN_EXPORT lean_object* lp_competition_R24DotCostHarness_benchExactFull___lam__1(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT uint32_t lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchExactFull_spec__0___redArg___lam__1(lean_object*, uint32_t, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchExactFull_spec__0___redArg___lam__1___boxed(lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT uint32_t lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchExactFull_spec__0___redArg___lam__0(lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchExactFull_spec__0___redArg___lam__0___boxed(lean_object*, lean_object*);
static const lean_string_object lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00__private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchExactFull_spec__0_spec__0___redArg___closed__0_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 15, .m_capacity = 15, .m_length = 14, .m_data = "ExactFull:warm"};
static const lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00__private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchExactFull_spec__0_spec__0___redArg___closed__0 = (const lean_object*)&lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00__private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchExactFull_spec__0_spec__0___redArg___closed__0_value;
static const lean_string_object lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00__private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchExactFull_spec__0_spec__0___redArg___closed__1_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 15, .m_capacity = 15, .m_length = 14, .m_data = "ExactFull:sink"};
static const lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00__private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchExactFull_spec__0_spec__0___redArg___closed__1 = (const lean_object*)&lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00__private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchExactFull_spec__0_spec__0___redArg___closed__1_value;
static const lean_string_object lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00__private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchExactFull_spec__0_spec__0___redArg___closed__2_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 15, .m_capacity = 15, .m_length = 14, .m_data = "ExactFull:keep"};
static const lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00__private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchExactFull_spec__0_spec__0___redArg___closed__2 = (const lean_object*)&lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00__private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchExactFull_spec__0_spec__0___redArg___closed__2_value;
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00__private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchExactFull_spec__0_spec__0___redArg(lean_object*, lean_object*, uint32_t, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00__private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchExactFull_spec__0_spec__0___redArg___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchExactFull_spec__0___redArg(lean_object*, lean_object*, uint32_t, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchExactFull_spec__0___redArg___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
static const lean_array_object lp_competition_R24DotCostHarness_benchExactFull___closed__0_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_array_object) + sizeof(void*)*0, .m_other = 0, .m_tag = 246}, .m_size = 0, .m_capacity = 0, .m_data = {}};
static const lean_object* lp_competition_R24DotCostHarness_benchExactFull___closed__0 = (const lean_object*)&lp_competition_R24DotCostHarness_benchExactFull___closed__0_value;
static const lean_ctor_object lp_competition_R24DotCostHarness_benchExactFull___closed__1_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_ctor_object) + sizeof(void*)*3 + 0, .m_other = 3, .m_tag = 0}, .m_objs = {((lean_object*)(((size_t)(0) << 1) | 1)),((lean_object*)(((size_t)(3) << 1) | 1)),((lean_object*)(((size_t)(1) << 1) | 1))}};
static const lean_object* lp_competition_R24DotCostHarness_benchExactFull___closed__1 = (const lean_object*)&lp_competition_R24DotCostHarness_benchExactFull___closed__1_value;
static const lean_string_object lp_competition_R24DotCostHarness_benchExactFull___closed__2_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 6, .m_capacity = 6, .m_length = 5, .m_data = "exact"};
static const lean_object* lp_competition_R24DotCostHarness_benchExactFull___closed__2 = (const lean_object*)&lp_competition_R24DotCostHarness_benchExactFull___closed__2_value;
static const lean_string_object lp_competition_R24DotCostHarness_benchExactFull___closed__3_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 5, .m_capacity = 5, .m_length = 4, .m_data = "full"};
static const lean_object* lp_competition_R24DotCostHarness_benchExactFull___closed__3 = (const lean_object*)&lp_competition_R24DotCostHarness_benchExactFull___closed__3_value;
LEAN_EXPORT lean_object* lp_competition_R24DotCostHarness_benchExactFull(lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_R24DotCostHarness_benchExactFull___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchExactFull_spec__0(lean_object*, lean_object*, uint32_t, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchExactFull_spec__0___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00__private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchExactFull_spec__0_spec__0(lean_object*, lean_object*, uint32_t, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00__private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchExactFull_spec__0_spec__0___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT uint32_t lp_competition_R24DotCostHarness_passEagerFull(lean_object*, uint32_t, lean_object*);
LEAN_EXPORT lean_object* lp_competition_R24DotCostHarness_passEagerFull___boxed(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT uint32_t lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchEagerFull_spec__0___redArg___lam__0(lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchEagerFull_spec__0___redArg___lam__0___boxed(lean_object*, lean_object*);
LEAN_EXPORT uint32_t lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchEagerFull_spec__0___redArg___lam__1(lean_object*, uint32_t, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchEagerFull_spec__0___redArg___lam__1___boxed(lean_object*, lean_object*, lean_object*, lean_object*);
static const lean_string_object lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00__private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchEagerFull_spec__0_spec__0___redArg___closed__0_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 15, .m_capacity = 15, .m_length = 14, .m_data = "EagerFull:warm"};
static const lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00__private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchEagerFull_spec__0_spec__0___redArg___closed__0 = (const lean_object*)&lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00__private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchEagerFull_spec__0_spec__0___redArg___closed__0_value;
static const lean_string_object lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00__private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchEagerFull_spec__0_spec__0___redArg___closed__1_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 15, .m_capacity = 15, .m_length = 14, .m_data = "EagerFull:sink"};
static const lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00__private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchEagerFull_spec__0_spec__0___redArg___closed__1 = (const lean_object*)&lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00__private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchEagerFull_spec__0_spec__0___redArg___closed__1_value;
static const lean_string_object lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00__private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchEagerFull_spec__0_spec__0___redArg___closed__2_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 15, .m_capacity = 15, .m_length = 14, .m_data = "EagerFull:keep"};
static const lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00__private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchEagerFull_spec__0_spec__0___redArg___closed__2 = (const lean_object*)&lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00__private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchEagerFull_spec__0_spec__0___redArg___closed__2_value;
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00__private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchEagerFull_spec__0_spec__0___redArg(lean_object*, lean_object*, uint32_t, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00__private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchEagerFull_spec__0_spec__0___redArg___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchEagerFull_spec__0___redArg(lean_object*, lean_object*, uint32_t, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchEagerFull_spec__0___redArg___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
static const lean_string_object lp_competition_R24DotCostHarness_benchEagerFull___closed__0_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 6, .m_capacity = 6, .m_length = 5, .m_data = "eager"};
static const lean_object* lp_competition_R24DotCostHarness_benchEagerFull___closed__0 = (const lean_object*)&lp_competition_R24DotCostHarness_benchEagerFull___closed__0_value;
LEAN_EXPORT lean_object* lp_competition_R24DotCostHarness_benchEagerFull(lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_R24DotCostHarness_benchEagerFull___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchEagerFull_spec__0(lean_object*, lean_object*, uint32_t, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchEagerFull_spec__0___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00__private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchEagerFull_spec__0_spec__0(lean_object*, lean_object*, uint32_t, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00__private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchEagerFull_spec__0_spec__0___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT uint32_t lp_competition_R24DotCostHarness_passLazyFull(lean_object*, uint32_t, lean_object*);
LEAN_EXPORT lean_object* lp_competition_R24DotCostHarness_passLazyFull___boxed(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT uint32_t lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchLazyFull_spec__0___redArg___lam__1(lean_object*, uint32_t, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchLazyFull_spec__0___redArg___lam__1___boxed(lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT uint32_t lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchLazyFull_spec__0___redArg___lam__0(lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchLazyFull_spec__0___redArg___lam__0___boxed(lean_object*, lean_object*);
static const lean_string_object lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00__private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchLazyFull_spec__0_spec__0___redArg___closed__0_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 14, .m_capacity = 14, .m_length = 13, .m_data = "LazyFull:warm"};
static const lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00__private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchLazyFull_spec__0_spec__0___redArg___closed__0 = (const lean_object*)&lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00__private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchLazyFull_spec__0_spec__0___redArg___closed__0_value;
static const lean_string_object lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00__private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchLazyFull_spec__0_spec__0___redArg___closed__1_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 14, .m_capacity = 14, .m_length = 13, .m_data = "LazyFull:sink"};
static const lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00__private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchLazyFull_spec__0_spec__0___redArg___closed__1 = (const lean_object*)&lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00__private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchLazyFull_spec__0_spec__0___redArg___closed__1_value;
static const lean_string_object lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00__private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchLazyFull_spec__0_spec__0___redArg___closed__2_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 14, .m_capacity = 14, .m_length = 13, .m_data = "LazyFull:keep"};
static const lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00__private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchLazyFull_spec__0_spec__0___redArg___closed__2 = (const lean_object*)&lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00__private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchLazyFull_spec__0_spec__0___redArg___closed__2_value;
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00__private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchLazyFull_spec__0_spec__0___redArg(lean_object*, lean_object*, uint32_t, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00__private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchLazyFull_spec__0_spec__0___redArg___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchLazyFull_spec__0___redArg(lean_object*, lean_object*, uint32_t, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchLazyFull_spec__0___redArg___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
static const lean_string_object lp_competition_R24DotCostHarness_benchLazyFull___closed__0_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 5, .m_capacity = 5, .m_length = 4, .m_data = "lazy"};
static const lean_object* lp_competition_R24DotCostHarness_benchLazyFull___closed__0 = (const lean_object*)&lp_competition_R24DotCostHarness_benchLazyFull___closed__0_value;
LEAN_EXPORT lean_object* lp_competition_R24DotCostHarness_benchLazyFull(lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_R24DotCostHarness_benchLazyFull___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchLazyFull_spec__0(lean_object*, lean_object*, uint32_t, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchLazyFull_spec__0___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00__private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchLazyFull_spec__0_spec__0(lean_object*, lean_object*, uint32_t, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00__private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchLazyFull_spec__0_spec__0___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT uint32_t lp_competition_R24DotCostHarness_passExactPrepared(lean_object*, uint32_t, lean_object*);
LEAN_EXPORT lean_object* lp_competition_R24DotCostHarness_passExactPrepared___boxed(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_R24DotCostHarness_benchExactPrepared___lam__1(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT uint32_t lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchExactPrepared_spec__0___redArg___lam__0(lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchExactPrepared_spec__0___redArg___lam__0___boxed(lean_object*, lean_object*);
LEAN_EXPORT uint32_t lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchExactPrepared_spec__0___redArg___lam__1(lean_object*, uint32_t, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchExactPrepared_spec__0___redArg___lam__1___boxed(lean_object*, lean_object*, lean_object*, lean_object*);
static const lean_string_object lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00__private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchExactPrepared_spec__0_spec__0___redArg___closed__0_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 19, .m_capacity = 19, .m_length = 18, .m_data = "ExactPrepared:warm"};
static const lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00__private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchExactPrepared_spec__0_spec__0___redArg___closed__0 = (const lean_object*)&lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00__private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchExactPrepared_spec__0_spec__0___redArg___closed__0_value;
static const lean_string_object lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00__private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchExactPrepared_spec__0_spec__0___redArg___closed__1_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 19, .m_capacity = 19, .m_length = 18, .m_data = "ExactPrepared:sink"};
static const lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00__private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchExactPrepared_spec__0_spec__0___redArg___closed__1 = (const lean_object*)&lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00__private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchExactPrepared_spec__0_spec__0___redArg___closed__1_value;
static const lean_string_object lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00__private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchExactPrepared_spec__0_spec__0___redArg___closed__2_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 19, .m_capacity = 19, .m_length = 18, .m_data = "ExactPrepared:keep"};
static const lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00__private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchExactPrepared_spec__0_spec__0___redArg___closed__2 = (const lean_object*)&lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00__private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchExactPrepared_spec__0_spec__0___redArg___closed__2_value;
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00__private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchExactPrepared_spec__0_spec__0___redArg(lean_object*, lean_object*, uint32_t, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00__private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchExactPrepared_spec__0_spec__0___redArg___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchExactPrepared_spec__0___redArg(lean_object*, lean_object*, uint32_t, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchExactPrepared_spec__0___redArg___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
static const lean_string_object lp_competition_R24DotCostHarness_benchExactPrepared___closed__0_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 9, .m_capacity = 9, .m_length = 8, .m_data = "prepared"};
static const lean_object* lp_competition_R24DotCostHarness_benchExactPrepared___closed__0 = (const lean_object*)&lp_competition_R24DotCostHarness_benchExactPrepared___closed__0_value;
LEAN_EXPORT lean_object* lp_competition_R24DotCostHarness_benchExactPrepared(lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_R24DotCostHarness_benchExactPrepared___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchExactPrepared_spec__0(lean_object*, lean_object*, uint32_t, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchExactPrepared_spec__0___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00__private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchExactPrepared_spec__0_spec__0(lean_object*, lean_object*, uint32_t, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00__private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchExactPrepared_spec__0_spec__0___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT uint32_t lp_competition_R24DotCostHarness_passEagerPrepared(lean_object*, uint32_t, lean_object*);
LEAN_EXPORT lean_object* lp_competition_R24DotCostHarness_passEagerPrepared___boxed(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_R24DotCostHarness_benchEagerPrepared___lam__1(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT uint32_t lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchEagerPrepared_spec__0___redArg___lam__0(lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchEagerPrepared_spec__0___redArg___lam__0___boxed(lean_object*, lean_object*);
LEAN_EXPORT uint32_t lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchEagerPrepared_spec__0___redArg___lam__1(lean_object*, uint32_t, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchEagerPrepared_spec__0___redArg___lam__1___boxed(lean_object*, lean_object*, lean_object*, lean_object*);
static const lean_string_object lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00__private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchEagerPrepared_spec__0_spec__0___redArg___closed__0_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 19, .m_capacity = 19, .m_length = 18, .m_data = "EagerPrepared:warm"};
static const lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00__private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchEagerPrepared_spec__0_spec__0___redArg___closed__0 = (const lean_object*)&lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00__private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchEagerPrepared_spec__0_spec__0___redArg___closed__0_value;
static const lean_string_object lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00__private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchEagerPrepared_spec__0_spec__0___redArg___closed__1_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 19, .m_capacity = 19, .m_length = 18, .m_data = "EagerPrepared:sink"};
static const lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00__private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchEagerPrepared_spec__0_spec__0___redArg___closed__1 = (const lean_object*)&lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00__private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchEagerPrepared_spec__0_spec__0___redArg___closed__1_value;
static const lean_string_object lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00__private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchEagerPrepared_spec__0_spec__0___redArg___closed__2_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 19, .m_capacity = 19, .m_length = 18, .m_data = "EagerPrepared:keep"};
static const lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00__private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchEagerPrepared_spec__0_spec__0___redArg___closed__2 = (const lean_object*)&lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00__private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchEagerPrepared_spec__0_spec__0___redArg___closed__2_value;
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00__private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchEagerPrepared_spec__0_spec__0___redArg(lean_object*, lean_object*, uint32_t, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00__private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchEagerPrepared_spec__0_spec__0___redArg___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchEagerPrepared_spec__0___redArg(lean_object*, lean_object*, uint32_t, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchEagerPrepared_spec__0___redArg___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_R24DotCostHarness_benchEagerPrepared(lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_R24DotCostHarness_benchEagerPrepared___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchEagerPrepared_spec__0(lean_object*, lean_object*, uint32_t, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchEagerPrepared_spec__0___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00__private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchEagerPrepared_spec__0_spec__0(lean_object*, lean_object*, uint32_t, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00__private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchEagerPrepared_spec__0_spec__0___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT uint32_t lp_competition_R24DotCostHarness_passLazyPrepared(lean_object*, uint32_t, lean_object*);
LEAN_EXPORT lean_object* lp_competition_R24DotCostHarness_passLazyPrepared___boxed(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_R24DotCostHarness_benchLazyPrepared___lam__1(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT uint32_t lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchLazyPrepared_spec__0___redArg___lam__1(lean_object*, uint32_t, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchLazyPrepared_spec__0___redArg___lam__1___boxed(lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT uint32_t lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchLazyPrepared_spec__0___redArg___lam__0(lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchLazyPrepared_spec__0___redArg___lam__0___boxed(lean_object*, lean_object*);
static const lean_string_object lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00__private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchLazyPrepared_spec__0_spec__0___redArg___closed__0_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 18, .m_capacity = 18, .m_length = 17, .m_data = "LazyPrepared:warm"};
static const lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00__private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchLazyPrepared_spec__0_spec__0___redArg___closed__0 = (const lean_object*)&lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00__private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchLazyPrepared_spec__0_spec__0___redArg___closed__0_value;
static const lean_string_object lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00__private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchLazyPrepared_spec__0_spec__0___redArg___closed__1_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 18, .m_capacity = 18, .m_length = 17, .m_data = "LazyPrepared:sink"};
static const lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00__private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchLazyPrepared_spec__0_spec__0___redArg___closed__1 = (const lean_object*)&lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00__private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchLazyPrepared_spec__0_spec__0___redArg___closed__1_value;
static const lean_string_object lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00__private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchLazyPrepared_spec__0_spec__0___redArg___closed__2_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 18, .m_capacity = 18, .m_length = 17, .m_data = "LazyPrepared:keep"};
static const lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00__private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchLazyPrepared_spec__0_spec__0___redArg___closed__2 = (const lean_object*)&lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00__private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchLazyPrepared_spec__0_spec__0___redArg___closed__2_value;
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00__private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchLazyPrepared_spec__0_spec__0___redArg(lean_object*, lean_object*, uint32_t, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00__private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchLazyPrepared_spec__0_spec__0___redArg___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchLazyPrepared_spec__0___redArg(lean_object*, lean_object*, uint32_t, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchLazyPrepared_spec__0___redArg___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_R24DotCostHarness_benchLazyPrepared(lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_R24DotCostHarness_benchLazyPrepared___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchLazyPrepared_spec__0(lean_object*, lean_object*, uint32_t, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchLazyPrepared_spec__0___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00__private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchLazyPrepared_spec__0_spec__0(lean_object*, lean_object*, uint32_t, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00__private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchLazyPrepared_spec__0_spec__0___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT uint8_t lp_competition___private_Init_Data_Array_Basic_0__Array_anyMUnsafe_any___at___00R24DotCostHarness_verify_spec__0(lean_object*, size_t, size_t);
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_anyMUnsafe_any___at___00R24DotCostHarness_verify_spec__0___boxed(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT uint32_t lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotCostHarness_verify_spec__1___lam__5(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotCostHarness_verify_spec__1___lam__5___boxed(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT uint32_t lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotCostHarness_verify_spec__1___lam__9(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotCostHarness_verify_spec__1___lam__9___boxed(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT uint32_t lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotCostHarness_verify_spec__1___lam__6(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotCostHarness_verify_spec__1___lam__6___boxed(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT uint32_t lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotCostHarness_verify_spec__1___lam__8(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotCostHarness_verify_spec__1___lam__8___boxed(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT uint32_t lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotCostHarness_verify_spec__1___lam__3(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotCostHarness_verify_spec__1___lam__3___boxed(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT uint32_t lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotCostHarness_verify_spec__1___lam__7(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotCostHarness_verify_spec__1___lam__7___boxed(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT uint32_t lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotCostHarness_verify_spec__1___lam__0(uint8_t, lean_object*, uint8_t, uint8_t, lean_object*, lean_object*, uint32_t, lean_object*, uint32_t, uint8_t, lean_object*);
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotCostHarness_verify_spec__1___lam__0___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT uint32_t lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotCostHarness_verify_spec__1___lam__4(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotCostHarness_verify_spec__1___lam__4___boxed(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT uint32_t lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotCostHarness_verify_spec__1___lam__2(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotCostHarness_verify_spec__1___lam__2___boxed(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT uint32_t lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotCostHarness_verify_spec__1___lam__1(lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotCostHarness_verify_spec__1___lam__1___boxed(lean_object*, lean_object*);
static const lean_string_object lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotCostHarness_verify_spec__1___closed__0_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 12, .m_capacity = 12, .m_length = 11, .m_data = "DOT_VERIFY\t"};
static const lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotCostHarness_verify_spec__1___closed__0 = (const lean_object*)&lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotCostHarness_verify_spec__1___closed__0_value;
static const lean_string_object lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotCostHarness_verify_spec__1___closed__1_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 6, .m_capacity = 6, .m_length = 5, .m_data = "\ttrue"};
static const lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotCostHarness_verify_spec__1___closed__1 = (const lean_object*)&lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotCostHarness_verify_spec__1___closed__1_value;
static const lean_string_object lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotCostHarness_verify_spec__1___closed__2_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 37, .m_capacity = 37, .m_length = 36, .m_data = ": unknown fast proposal is incorrect"};
static const lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotCostHarness_verify_spec__1___closed__2 = (const lean_object*)&lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotCostHarness_verify_spec__1___closed__2_value;
static const lean_string_object lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotCostHarness_verify_spec__1___closed__3_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 10, .m_capacity = 10, .m_length = 9, .m_data = "exactFull"};
static const lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotCostHarness_verify_spec__1___closed__3 = (const lean_object*)&lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotCostHarness_verify_spec__1___closed__3_value;
static const lean_string_object lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotCostHarness_verify_spec__1___closed__4_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 10, .m_capacity = 10, .m_length = 9, .m_data = "eagerFull"};
static const lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotCostHarness_verify_spec__1___closed__4 = (const lean_object*)&lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotCostHarness_verify_spec__1___closed__4_value;
static const lean_string_object lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotCostHarness_verify_spec__1___closed__5_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 9, .m_capacity = 9, .m_length = 8, .m_data = "lazyFull"};
static const lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotCostHarness_verify_spec__1___closed__5 = (const lean_object*)&lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotCostHarness_verify_spec__1___closed__5_value;
static const lean_string_object lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotCostHarness_verify_spec__1___closed__6_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 14, .m_capacity = 14, .m_length = 13, .m_data = "exactPrepared"};
static const lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotCostHarness_verify_spec__1___closed__6 = (const lean_object*)&lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotCostHarness_verify_spec__1___closed__6_value;
static const lean_string_object lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotCostHarness_verify_spec__1___closed__7_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 14, .m_capacity = 14, .m_length = 13, .m_data = "eagerPrepared"};
static const lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotCostHarness_verify_spec__1___closed__7 = (const lean_object*)&lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotCostHarness_verify_spec__1___closed__7_value;
static const lean_string_object lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotCostHarness_verify_spec__1___closed__8_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 13, .m_capacity = 13, .m_length = 12, .m_data = "lazyPrepared"};
static const lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotCostHarness_verify_spec__1___closed__8 = (const lean_object*)&lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotCostHarness_verify_spec__1___closed__8_value;
static const lean_string_object lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotCostHarness_verify_spec__1___closed__9_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 12, .m_capacity = 12, .m_length = 11, .m_data = "baseline128"};
static const lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotCostHarness_verify_spec__1___closed__9 = (const lean_object*)&lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotCostHarness_verify_spec__1___closed__9_value;
static const lean_string_object lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotCostHarness_verify_spec__1___closed__10_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 10, .m_capacity = 10, .m_length = 9, .m_data = "reference"};
static const lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotCostHarness_verify_spec__1___closed__10 = (const lean_object*)&lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotCostHarness_verify_spec__1___closed__10_value;
static const lean_string_object lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotCostHarness_verify_spec__1___closed__11_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 30, .m_capacity = 30, .m_length = 29, .m_data = ": fixture word exceeds UInt32"};
static const lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotCostHarness_verify_spec__1___closed__11 = (const lean_object*)&lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotCostHarness_verify_spec__1___closed__11_value;
static const lean_string_object lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotCostHarness_verify_spec__1___closed__12_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 9, .m_capacity = 9, .m_length = 8, .m_data = "fastCold"};
static const lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotCostHarness_verify_spec__1___closed__12 = (const lean_object*)&lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotCostHarness_verify_spec__1___closed__12_value;
static const lean_string_object lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotCostHarness_verify_spec__1___closed__13_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 13, .m_capacity = 13, .m_length = 12, .m_data = "fastPrepared"};
static const lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotCostHarness_verify_spec__1___closed__13 = (const lean_object*)&lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotCostHarness_verify_spec__1___closed__13_value;
static const lean_string_object lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotCostHarness_verify_spec__1___closed__14_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 29, .m_capacity = 29, .m_length = 28, .m_data = ": fast_result exceeds UInt32"};
static const lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotCostHarness_verify_spec__1___closed__14 = (const lean_object*)&lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotCostHarness_verify_spec__1___closed__14_value;
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotCostHarness_verify_spec__1(lean_object*, size_t, size_t, lean_object*);
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotCostHarness_verify_spec__1___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT uint32_t lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotCostHarness_verify_spec__2___lam__0(lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotCostHarness_verify_spec__2___lam__0___boxed(lean_object*, lean_object*);
static const lean_string_object lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotCostHarness_verify_spec__2___closed__0_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 34, .m_capacity = 34, .m_length = 33, .m_data = ": round fixture word out of range"};
static const lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotCostHarness_verify_spec__2___closed__0 = (const lean_object*)&lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotCostHarness_verify_spec__2___closed__0_value;
static const lean_string_object lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotCostHarness_verify_spec__2___closed__1_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 9, .m_capacity = 9, .m_length = 8, .m_data = "round128"};
static const lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotCostHarness_verify_spec__2___closed__1 = (const lean_object*)&lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotCostHarness_verify_spec__2___closed__1_value;
static const lean_string_object lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotCostHarness_verify_spec__2___closed__2_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 11, .m_capacity = 11, .m_length = 10, .m_data = "DOT_ROUND\t"};
static const lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotCostHarness_verify_spec__2___closed__2 = (const lean_object*)&lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotCostHarness_verify_spec__2___closed__2_value;
static lean_once_cell_t lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotCostHarness_verify_spec__2___closed__3_once = LEAN_ONCE_CELL_INITIALIZER;
static lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotCostHarness_verify_spec__2___closed__3;
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotCostHarness_verify_spec__2(lean_object*, size_t, size_t, lean_object*);
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotCostHarness_verify_spec__2___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
static const lean_ctor_object lp_competition_R24DotCostHarness_verify___closed__0_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_ctor_object) + sizeof(void*)*2 + 0, .m_other = 2, .m_tag = 0}, .m_objs = {((lean_object*)(((size_t)(0) << 1) | 1)),((lean_object*)(((size_t)(0) << 1) | 1))}};
static const lean_object* lp_competition_R24DotCostHarness_verify___closed__0 = (const lean_object*)&lp_competition_R24DotCostHarness_verify___closed__0_value;
static const lean_string_object lp_competition_R24DotCostHarness_verify___closed__1_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 17, .m_capacity = 17, .m_length = 16, .m_data = "DOT_VERIFY_DONE\t"};
static const lean_object* lp_competition_R24DotCostHarness_verify___closed__1 = (const lean_object*)&lp_competition_R24DotCostHarness_verify___closed__1_value;
LEAN_EXPORT lean_object* lp_competition_R24DotCostHarness_verify(lean_object*);
LEAN_EXPORT lean_object* lp_competition_R24DotCostHarness_verify___boxed(lean_object*, lean_object*);
static const lean_string_object lp_competition_R24DotCostHarness_env___closed__0_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 9, .m_capacity = 9, .m_length = 8, .m_data = "Missing "};
static const lean_object* lp_competition_R24DotCostHarness_env___closed__0 = (const lean_object*)&lp_competition_R24DotCostHarness_env___closed__0_value;
LEAN_EXPORT lean_object* lp_competition_R24DotCostHarness_env(lean_object*);
LEAN_EXPORT lean_object* lp_competition_R24DotCostHarness_env___boxed(lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotCostHarness_run_spec__0___lam__3(lean_object*, lean_object*);
LEAN_EXPORT uint8_t lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotCostHarness_run_spec__0___lam__0(lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotCostHarness_run_spec__0___lam__0___boxed(lean_object*, lean_object*);
LEAN_EXPORT uint8_t lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotCostHarness_run_spec__0___lam__1(lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotCostHarness_run_spec__0___lam__1___boxed(lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotCostHarness_run_spec__0___lam__2(lean_object*, lean_object*);
static const lean_string_object lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotCostHarness_run_spec__0___closed__0_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 21, .m_capacity = 21, .m_length = 20, .m_data = "Unreachable dot mode"};
static const lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotCostHarness_run_spec__0___closed__0 = (const lean_object*)&lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotCostHarness_run_spec__0___closed__0_value;
static const lean_ctor_object lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotCostHarness_run_spec__0___closed__1_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_ctor_object) + sizeof(void*)*1 + 0, .m_other = 1, .m_tag = 18}, .m_objs = {((lean_object*)&lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotCostHarness_run_spec__0___closed__0_value)}};
static const lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotCostHarness_run_spec__0___closed__1 = (const lean_object*)&lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotCostHarness_run_spec__0___closed__1_value;
static const lean_string_object lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotCostHarness_run_spec__0___closed__2_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 10, .m_capacity = 10, .m_length = 9, .m_data = "DOT_SKIP\t"};
static const lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotCostHarness_run_spec__0___closed__2 = (const lean_object*)&lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotCostHarness_run_spec__0___closed__2_value;
static const lean_string_object lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotCostHarness_run_spec__0___closed__3_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 22, .m_capacity = 22, .m_length = 21, .m_data = "\tunsupported_or_empty"};
static const lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotCostHarness_run_spec__0___closed__3 = (const lean_object*)&lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotCostHarness_run_spec__0___closed__3_value;
static const lean_string_object lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotCostHarness_run_spec__0___closed__4_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 9, .m_capacity = 9, .m_length = 8, .m_data = "directed"};
static const lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotCostHarness_run_spec__0___closed__4 = (const lean_object*)&lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotCostHarness_run_spec__0___closed__4_value;
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotCostHarness_run_spec__0(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, size_t, size_t, lean_object*);
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotCostHarness_run_spec__0___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
static const lean_string_object lp_competition_R24DotCostHarness_run___closed__0_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 18, .m_capacity = 18, .m_length = 17, .m_data = "BENCH_DOT_FIXTURE"};
static const lean_object* lp_competition_R24DotCostHarness_run___closed__0 = (const lean_object*)&lp_competition_R24DotCostHarness_run___closed__0_value;
static const lean_string_object lp_competition_R24DotCostHarness_run___closed__1_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 20, .m_capacity = 20, .m_length = 19, .m_data = "BENCH_DOT_FIXTURE: "};
static const lean_object* lp_competition_R24DotCostHarness_run___closed__1 = (const lean_object*)&lp_competition_R24DotCostHarness_run___closed__1_value;
static const lean_string_object lp_competition_R24DotCostHarness_run___closed__2_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 18, .m_capacity = 18, .m_length = 17, .m_data = "DOT_MEASURE_DONE\t"};
static const lean_object* lp_competition_R24DotCostHarness_run___closed__2 = (const lean_object*)&lp_competition_R24DotCostHarness_run___closed__2_value;
static const lean_string_object lp_competition_R24DotCostHarness_run___closed__3_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 3, .m_capacity = 3, .m_length = 2, .m_data = "\t3"};
static const lean_object* lp_competition_R24DotCostHarness_run___closed__3 = (const lean_object*)&lp_competition_R24DotCostHarness_run___closed__3_value;
static const lean_string_object lp_competition_R24DotCostHarness_run___closed__4_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 27, .m_capacity = 27, .m_length = 26, .m_data = "BENCH_DOT_MACS exceeds2^24"};
static const lean_object* lp_competition_R24DotCostHarness_run___closed__4 = (const lean_object*)&lp_competition_R24DotCostHarness_run___closed__4_value;
static const lean_ctor_object lp_competition_R24DotCostHarness_run___closed__5_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_ctor_object) + sizeof(void*)*1 + 0, .m_other = 1, .m_tag = 18}, .m_objs = {((lean_object*)&lp_competition_R24DotCostHarness_run___closed__4_value)}};
static const lean_object* lp_competition_R24DotCostHarness_run___closed__5 = (const lean_object*)&lp_competition_R24DotCostHarness_run___closed__5_value;
static const lean_string_object lp_competition_R24DotCostHarness_run___closed__6_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 23, .m_capacity = 23, .m_length = 22, .m_data = "Invalid BENCH_DOT_MACS"};
static const lean_object* lp_competition_R24DotCostHarness_run___closed__6 = (const lean_object*)&lp_competition_R24DotCostHarness_run___closed__6_value;
static const lean_ctor_object lp_competition_R24DotCostHarness_run___closed__7_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_ctor_object) + sizeof(void*)*1 + 0, .m_other = 1, .m_tag = 18}, .m_objs = {((lean_object*)&lp_competition_R24DotCostHarness_run___closed__6_value)}};
static const lean_object* lp_competition_R24DotCostHarness_run___closed__7 = (const lean_object*)&lp_competition_R24DotCostHarness_run___closed__7_value;
static const lean_string_object lp_competition_R24DotCostHarness_run___closed__8_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 15, .m_capacity = 15, .m_length = 14, .m_data = "BENCH_DOT_MACS"};
static const lean_object* lp_competition_R24DotCostHarness_run___closed__8 = (const lean_object*)&lp_competition_R24DotCostHarness_run___closed__8_value;
static const lean_string_object lp_competition_R24DotCostHarness_run___closed__9_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 7, .m_capacity = 7, .m_length = 6, .m_data = "131072"};
static const lean_object* lp_competition_R24DotCostHarness_run___closed__9 = (const lean_object*)&lp_competition_R24DotCostHarness_run___closed__9_value;
static const lean_string_object lp_competition_R24DotCostHarness_run___closed__10_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 27, .m_capacity = 27, .m_length = 26, .m_data = "Invalid BENCH_DOT_BOUNDARY"};
static const lean_object* lp_competition_R24DotCostHarness_run___closed__10 = (const lean_object*)&lp_competition_R24DotCostHarness_run___closed__10_value;
static const lean_ctor_object lp_competition_R24DotCostHarness_run___closed__11_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_ctor_object) + sizeof(void*)*1 + 0, .m_other = 1, .m_tag = 18}, .m_objs = {((lean_object*)&lp_competition_R24DotCostHarness_run___closed__10_value)}};
static const lean_object* lp_competition_R24DotCostHarness_run___closed__11 = (const lean_object*)&lp_competition_R24DotCostHarness_run___closed__11_value;
static const lean_string_object lp_competition_R24DotCostHarness_run___closed__12_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 26, .m_capacity = 26, .m_length = 25, .m_data = "Invalid BENCH_DOT_VARIANT"};
static const lean_object* lp_competition_R24DotCostHarness_run___closed__12 = (const lean_object*)&lp_competition_R24DotCostHarness_run___closed__12_value;
static const lean_ctor_object lp_competition_R24DotCostHarness_run___closed__13_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_ctor_object) + sizeof(void*)*1 + 0, .m_other = 1, .m_tag = 18}, .m_objs = {((lean_object*)&lp_competition_R24DotCostHarness_run___closed__12_value)}};
static const lean_object* lp_competition_R24DotCostHarness_run___closed__13 = (const lean_object*)&lp_competition_R24DotCostHarness_run___closed__13_value;
static const lean_string_object lp_competition_R24DotCostHarness_run___closed__14_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 9, .m_capacity = 9, .m_length = 8, .m_data = "24282405"};
static const lean_object* lp_competition_R24DotCostHarness_run___closed__14 = (const lean_object*)&lp_competition_R24DotCostHarness_run___closed__14_value;
static const lean_string_object lp_competition_R24DotCostHarness_run___closed__15_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 24, .m_capacity = 24, .m_length = 23, .m_data = "Invalid BENCH_DOT_GROUP"};
static const lean_object* lp_competition_R24DotCostHarness_run___closed__15 = (const lean_object*)&lp_competition_R24DotCostHarness_run___closed__15_value;
static const lean_ctor_object lp_competition_R24DotCostHarness_run___closed__16_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_ctor_object) + sizeof(void*)*1 + 0, .m_other = 1, .m_tag = 18}, .m_objs = {((lean_object*)&lp_competition_R24DotCostHarness_run___closed__15_value)}};
static const lean_object* lp_competition_R24DotCostHarness_run___closed__16 = (const lean_object*)&lp_competition_R24DotCostHarness_run___closed__16_value;
static const lean_string_object lp_competition_R24DotCostHarness_run___closed__17_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 15, .m_capacity = 15, .m_length = 14, .m_data = "BENCH_DOT_MODE"};
static const lean_object* lp_competition_R24DotCostHarness_run___closed__17 = (const lean_object*)&lp_competition_R24DotCostHarness_run___closed__17_value;
static const lean_string_object lp_competition_R24DotCostHarness_run___closed__18_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 41, .m_capacity = 41, .m_length = 40, .m_data = "BENCH_DOT_MODE must be verify or measure"};
static const lean_object* lp_competition_R24DotCostHarness_run___closed__18 = (const lean_object*)&lp_competition_R24DotCostHarness_run___closed__18_value;
static const lean_ctor_object lp_competition_R24DotCostHarness_run___closed__19_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_ctor_object) + sizeof(void*)*1 + 0, .m_other = 1, .m_tag = 18}, .m_objs = {((lean_object*)&lp_competition_R24DotCostHarness_run___closed__18_value)}};
static const lean_object* lp_competition_R24DotCostHarness_run___closed__19 = (const lean_object*)&lp_competition_R24DotCostHarness_run___closed__19_value;
static const lean_string_object lp_competition_R24DotCostHarness_run___closed__20_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 7, .m_capacity = 7, .m_length = 6, .m_data = "verify"};
static const lean_object* lp_competition_R24DotCostHarness_run___closed__20 = (const lean_object*)&lp_competition_R24DotCostHarness_run___closed__20_value;
static const lean_string_object lp_competition_R24DotCostHarness_run___closed__21_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 8, .m_capacity = 8, .m_length = 7, .m_data = "measure"};
static const lean_object* lp_competition_R24DotCostHarness_run___closed__21 = (const lean_object*)&lp_competition_R24DotCostHarness_run___closed__21_value;
static const lean_string_object lp_competition_R24DotCostHarness_run___closed__22_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 16, .m_capacity = 16, .m_length = 15, .m_data = "BENCH_DOT_GROUP"};
static const lean_object* lp_competition_R24DotCostHarness_run___closed__22 = (const lean_object*)&lp_competition_R24DotCostHarness_run___closed__22_value;
static const lean_string_object lp_competition_R24DotCostHarness_run___closed__23_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 18, .m_capacity = 18, .m_length = 17, .m_data = "BENCH_DOT_VARIANT"};
static const lean_object* lp_competition_R24DotCostHarness_run___closed__23 = (const lean_object*)&lp_competition_R24DotCostHarness_run___closed__23_value;
static const lean_string_object lp_competition_R24DotCostHarness_run___closed__24_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 19, .m_capacity = 19, .m_length = 18, .m_data = "BENCH_DOT_BOUNDARY"};
static const lean_object* lp_competition_R24DotCostHarness_run___closed__24 = (const lean_object*)&lp_competition_R24DotCostHarness_run___closed__24_value;
static const lean_string_object lp_competition_R24DotCostHarness_run___closed__25_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 9, .m_capacity = 9, .m_length = 8, .m_data = "24282403"};
static const lean_object* lp_competition_R24DotCostHarness_run___closed__25 = (const lean_object*)&lp_competition_R24DotCostHarness_run___closed__25_value;
LEAN_EXPORT lean_object* lp_competition_R24DotCostHarness_run___boxed__const__1;
LEAN_EXPORT lean_object* lp_competition_R24DotCostHarness_run();
LEAN_EXPORT lean_object* lp_competition_R24DotCostHarness_run___boxed(lean_object*);
LEAN_EXPORT lean_object* _lean_main();
LEAN_EXPORT lean_object* lp_competition_main___boxed(lean_object*);
static lean_object* _init_lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__4(void){
_start:
{
uint8_t v___x_7_; lean_object* v___x_8_; lean_object* v___x_9_; 
v___x_7_ = 1;
v___x_8_ = ((lean_object*)(lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__3));
v___x_9_ = l_Lean_Name_toStringWithToken___at___00Lean_Name_toString_spec__0(v___x_8_, v___x_7_);
return v___x_9_;
}
}
static lean_object* _init_lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__6(void){
_start:
{
lean_object* v___x_11_; lean_object* v___x_12_; lean_object* v___x_13_; 
v___x_11_ = ((lean_object*)(lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__5));
v___x_12_ = lean_obj_once(&lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__4, &lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__4_once, _init_lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__4);
v___x_13_ = lean_string_append(v___x_12_, v___x_11_);
return v___x_13_;
}
}
static lean_object* _init_lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__8(void){
_start:
{
uint8_t v___x_16_; lean_object* v___x_17_; lean_object* v___x_18_; 
v___x_16_ = 1;
v___x_17_ = ((lean_object*)(lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__7));
v___x_18_ = l_Lean_Name_toStringWithToken___at___00Lean_Name_toString_spec__0(v___x_17_, v___x_16_);
return v___x_18_;
}
}
static lean_object* _init_lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__9(void){
_start:
{
lean_object* v___x_19_; lean_object* v___x_20_; lean_object* v___x_21_; 
v___x_19_ = lean_obj_once(&lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__8, &lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__8_once, _init_lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__8);
v___x_20_ = lean_obj_once(&lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__6, &lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__6_once, _init_lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__6);
v___x_21_ = lean_string_append(v___x_20_, v___x_19_);
return v___x_21_;
}
}
static lean_object* _init_lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__11(void){
_start:
{
lean_object* v___x_23_; lean_object* v___x_24_; lean_object* v___x_25_; 
v___x_23_ = ((lean_object*)(lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__10));
v___x_24_ = lean_obj_once(&lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__9, &lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__9_once, _init_lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__9);
v___x_25_ = lean_string_append(v___x_24_, v___x_23_);
return v___x_25_;
}
}
static lean_object* _init_lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__14(void){
_start:
{
uint8_t v___x_29_; lean_object* v___x_30_; lean_object* v___x_31_; 
v___x_29_ = 1;
v___x_30_ = ((lean_object*)(lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__13));
v___x_31_ = l_Lean_Name_toStringWithToken___at___00Lean_Name_toString_spec__0(v___x_30_, v___x_29_);
return v___x_31_;
}
}
static lean_object* _init_lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__15(void){
_start:
{
lean_object* v___x_32_; lean_object* v___x_33_; lean_object* v___x_34_; 
v___x_32_ = lean_obj_once(&lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__14, &lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__14_once, _init_lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__14);
v___x_33_ = lean_obj_once(&lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__6, &lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__6_once, _init_lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__6);
v___x_34_ = lean_string_append(v___x_33_, v___x_32_);
return v___x_34_;
}
}
static lean_object* _init_lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__16(void){
_start:
{
lean_object* v___x_35_; lean_object* v___x_36_; lean_object* v___x_37_; 
v___x_35_ = ((lean_object*)(lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__10));
v___x_36_ = lean_obj_once(&lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__15, &lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__15_once, _init_lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__15);
v___x_37_ = lean_string_append(v___x_36_, v___x_35_);
return v___x_37_;
}
}
static lean_object* _init_lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__19(void){
_start:
{
uint8_t v___x_41_; lean_object* v___x_42_; lean_object* v___x_43_; 
v___x_41_ = 1;
v___x_42_ = ((lean_object*)(lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__18));
v___x_43_ = l_Lean_Name_toStringWithToken___at___00Lean_Name_toString_spec__0(v___x_42_, v___x_41_);
return v___x_43_;
}
}
static lean_object* _init_lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__20(void){
_start:
{
lean_object* v___x_44_; lean_object* v___x_45_; lean_object* v___x_46_; 
v___x_44_ = lean_obj_once(&lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__19, &lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__19_once, _init_lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__19);
v___x_45_ = lean_obj_once(&lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__6, &lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__6_once, _init_lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__6);
v___x_46_ = lean_string_append(v___x_45_, v___x_44_);
return v___x_46_;
}
}
static lean_object* _init_lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__21(void){
_start:
{
lean_object* v___x_47_; lean_object* v___x_48_; lean_object* v___x_49_; 
v___x_47_ = ((lean_object*)(lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__10));
v___x_48_ = lean_obj_once(&lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__20, &lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__20_once, _init_lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__20);
v___x_49_ = lean_string_append(v___x_48_, v___x_47_);
return v___x_49_;
}
}
static lean_object* _init_lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__24(void){
_start:
{
uint8_t v___x_53_; lean_object* v___x_54_; lean_object* v___x_55_; 
v___x_53_ = 1;
v___x_54_ = ((lean_object*)(lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__23));
v___x_55_ = l_Lean_Name_toStringWithToken___at___00Lean_Name_toString_spec__0(v___x_54_, v___x_53_);
return v___x_55_;
}
}
static lean_object* _init_lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__25(void){
_start:
{
lean_object* v___x_56_; lean_object* v___x_57_; lean_object* v___x_58_; 
v___x_56_ = lean_obj_once(&lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__24, &lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__24_once, _init_lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__24);
v___x_57_ = lean_obj_once(&lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__6, &lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__6_once, _init_lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__6);
v___x_58_ = lean_string_append(v___x_57_, v___x_56_);
return v___x_58_;
}
}
static lean_object* _init_lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__26(void){
_start:
{
lean_object* v___x_59_; lean_object* v___x_60_; lean_object* v___x_61_; 
v___x_59_ = ((lean_object*)(lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__10));
v___x_60_ = lean_obj_once(&lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__25, &lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__25_once, _init_lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__25);
v___x_61_ = lean_string_append(v___x_60_, v___x_59_);
return v___x_61_;
}
}
static lean_object* _init_lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__29(void){
_start:
{
uint8_t v___x_65_; lean_object* v___x_66_; lean_object* v___x_67_; 
v___x_65_ = 1;
v___x_66_ = ((lean_object*)(lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__28));
v___x_67_ = l_Lean_Name_toStringWithToken___at___00Lean_Name_toString_spec__0(v___x_66_, v___x_65_);
return v___x_67_;
}
}
static lean_object* _init_lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__30(void){
_start:
{
lean_object* v___x_68_; lean_object* v___x_69_; lean_object* v___x_70_; 
v___x_68_ = lean_obj_once(&lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__29, &lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__29_once, _init_lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__29);
v___x_69_ = lean_obj_once(&lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__6, &lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__6_once, _init_lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__6);
v___x_70_ = lean_string_append(v___x_69_, v___x_68_);
return v___x_70_;
}
}
static lean_object* _init_lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__31(void){
_start:
{
lean_object* v___x_71_; lean_object* v___x_72_; lean_object* v___x_73_; 
v___x_71_ = ((lean_object*)(lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__10));
v___x_72_ = lean_obj_once(&lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__30, &lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__30_once, _init_lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__30);
v___x_73_ = lean_string_append(v___x_72_, v___x_71_);
return v___x_73_;
}
}
static lean_object* _init_lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__34(void){
_start:
{
uint8_t v___x_77_; lean_object* v___x_78_; lean_object* v___x_79_; 
v___x_77_ = 1;
v___x_78_ = ((lean_object*)(lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__33));
v___x_79_ = l_Lean_Name_toStringWithToken___at___00Lean_Name_toString_spec__0(v___x_78_, v___x_77_);
return v___x_79_;
}
}
static lean_object* _init_lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__35(void){
_start:
{
lean_object* v___x_80_; lean_object* v___x_81_; lean_object* v___x_82_; 
v___x_80_ = lean_obj_once(&lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__34, &lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__34_once, _init_lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__34);
v___x_81_ = lean_obj_once(&lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__6, &lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__6_once, _init_lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__6);
v___x_82_ = lean_string_append(v___x_81_, v___x_80_);
return v___x_82_;
}
}
static lean_object* _init_lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__36(void){
_start:
{
lean_object* v___x_83_; lean_object* v___x_84_; lean_object* v___x_85_; 
v___x_83_ = ((lean_object*)(lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__10));
v___x_84_ = lean_obj_once(&lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__35, &lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__35_once, _init_lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__35);
v___x_85_ = lean_string_append(v___x_84_, v___x_83_);
return v___x_85_;
}
}
static lean_object* _init_lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__39(void){
_start:
{
uint8_t v___x_89_; lean_object* v___x_90_; lean_object* v___x_91_; 
v___x_89_ = 1;
v___x_90_ = ((lean_object*)(lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__38));
v___x_91_ = l_Lean_Name_toStringWithToken___at___00Lean_Name_toString_spec__0(v___x_90_, v___x_89_);
return v___x_91_;
}
}
static lean_object* _init_lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__40(void){
_start:
{
lean_object* v___x_92_; lean_object* v___x_93_; lean_object* v___x_94_; 
v___x_92_ = lean_obj_once(&lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__39, &lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__39_once, _init_lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__39);
v___x_93_ = lean_obj_once(&lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__6, &lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__6_once, _init_lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__6);
v___x_94_ = lean_string_append(v___x_93_, v___x_92_);
return v___x_94_;
}
}
static lean_object* _init_lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__41(void){
_start:
{
lean_object* v___x_95_; lean_object* v___x_96_; lean_object* v___x_97_; 
v___x_95_ = ((lean_object*)(lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__10));
v___x_96_ = lean_obj_once(&lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__40, &lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__40_once, _init_lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__40);
v___x_97_ = lean_string_append(v___x_96_, v___x_95_);
return v___x_97_;
}
}
static lean_object* _init_lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__44(void){
_start:
{
uint8_t v___x_101_; lean_object* v___x_102_; lean_object* v___x_103_; 
v___x_101_ = 1;
v___x_102_ = ((lean_object*)(lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__43));
v___x_103_ = l_Lean_Name_toStringWithToken___at___00Lean_Name_toString_spec__0(v___x_102_, v___x_101_);
return v___x_103_;
}
}
static lean_object* _init_lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__45(void){
_start:
{
lean_object* v___x_104_; lean_object* v___x_105_; lean_object* v___x_106_; 
v___x_104_ = lean_obj_once(&lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__44, &lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__44_once, _init_lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__44);
v___x_105_ = lean_obj_once(&lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__6, &lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__6_once, _init_lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__6);
v___x_106_ = lean_string_append(v___x_105_, v___x_104_);
return v___x_106_;
}
}
static lean_object* _init_lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__46(void){
_start:
{
lean_object* v___x_107_; lean_object* v___x_108_; lean_object* v___x_109_; 
v___x_107_ = ((lean_object*)(lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__10));
v___x_108_ = lean_obj_once(&lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__45, &lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__45_once, _init_lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__45);
v___x_109_ = lean_string_append(v___x_108_, v___x_107_);
return v___x_109_;
}
}
LEAN_EXPORT lean_object* lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson(lean_object* v_json_110_){
_start:
{
lean_object* v___x_111_; lean_object* v___x_112_; 
v___x_111_ = ((lean_object*)(lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__0));
lean_inc(v_json_110_);
v___x_112_ = lp_proofwidgets_Lean_Json_getObjValAs_x3f___at___00ProofWidgets_MarkdownDisplay_instFromJsonProps_fromJson_spec__0(v_json_110_, v___x_111_);
if (lean_obj_tag(v___x_112_) == 0)
{
lean_object* v_a_113_; lean_object* v___x_115_; uint8_t v_isShared_116_; uint8_t v_isSharedCheck_122_; 
lean_dec(v_json_110_);
v_a_113_ = lean_ctor_get(v___x_112_, 0);
v_isSharedCheck_122_ = !lean_is_exclusive(v___x_112_);
if (v_isSharedCheck_122_ == 0)
{
v___x_115_ = v___x_112_;
v_isShared_116_ = v_isSharedCheck_122_;
goto v_resetjp_114_;
}
else
{
lean_inc(v_a_113_);
lean_dec(v___x_112_);
v___x_115_ = lean_box(0);
v_isShared_116_ = v_isSharedCheck_122_;
goto v_resetjp_114_;
}
v_resetjp_114_:
{
lean_object* v___x_117_; lean_object* v___x_118_; lean_object* v___x_120_; 
v___x_117_ = lean_obj_once(&lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__11, &lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__11_once, _init_lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__11);
v___x_118_ = lean_string_append(v___x_117_, v_a_113_);
lean_dec(v_a_113_);
if (v_isShared_116_ == 0)
{
lean_ctor_set(v___x_115_, 0, v___x_118_);
v___x_120_ = v___x_115_;
goto v_reusejp_119_;
}
else
{
lean_object* v_reuseFailAlloc_121_; 
v_reuseFailAlloc_121_ = lean_alloc_ctor(0, 1, 0);
lean_ctor_set(v_reuseFailAlloc_121_, 0, v___x_118_);
v___x_120_ = v_reuseFailAlloc_121_;
goto v_reusejp_119_;
}
v_reusejp_119_:
{
return v___x_120_;
}
}
}
else
{
if (lean_obj_tag(v___x_112_) == 0)
{
lean_object* v_a_123_; lean_object* v___x_125_; uint8_t v_isShared_126_; uint8_t v_isSharedCheck_130_; 
lean_dec(v_json_110_);
v_a_123_ = lean_ctor_get(v___x_112_, 0);
v_isSharedCheck_130_ = !lean_is_exclusive(v___x_112_);
if (v_isSharedCheck_130_ == 0)
{
v___x_125_ = v___x_112_;
v_isShared_126_ = v_isSharedCheck_130_;
goto v_resetjp_124_;
}
else
{
lean_inc(v_a_123_);
lean_dec(v___x_112_);
v___x_125_ = lean_box(0);
v_isShared_126_ = v_isSharedCheck_130_;
goto v_resetjp_124_;
}
v_resetjp_124_:
{
lean_object* v___x_128_; 
if (v_isShared_126_ == 0)
{
lean_ctor_set_tag(v___x_125_, 0);
v___x_128_ = v___x_125_;
goto v_reusejp_127_;
}
else
{
lean_object* v_reuseFailAlloc_129_; 
v_reuseFailAlloc_129_ = lean_alloc_ctor(0, 1, 0);
lean_ctor_set(v_reuseFailAlloc_129_, 0, v_a_123_);
v___x_128_ = v_reuseFailAlloc_129_;
goto v_reusejp_127_;
}
v_reusejp_127_:
{
return v___x_128_;
}
}
}
else
{
lean_object* v_a_131_; lean_object* v___x_132_; lean_object* v___x_133_; 
v_a_131_ = lean_ctor_get(v___x_112_, 0);
lean_inc(v_a_131_);
lean_dec_ref_known(v___x_112_, 1);
v___x_132_ = ((lean_object*)(lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__12));
lean_inc(v_json_110_);
v___x_133_ = lp_proofwidgets_Lean_Json_getObjValAs_x3f___at___00ProofWidgets_MarkdownDisplay_instFromJsonProps_fromJson_spec__0(v_json_110_, v___x_132_);
if (lean_obj_tag(v___x_133_) == 0)
{
lean_object* v_a_134_; lean_object* v___x_136_; uint8_t v_isShared_137_; uint8_t v_isSharedCheck_143_; 
lean_dec(v_a_131_);
lean_dec(v_json_110_);
v_a_134_ = lean_ctor_get(v___x_133_, 0);
v_isSharedCheck_143_ = !lean_is_exclusive(v___x_133_);
if (v_isSharedCheck_143_ == 0)
{
v___x_136_ = v___x_133_;
v_isShared_137_ = v_isSharedCheck_143_;
goto v_resetjp_135_;
}
else
{
lean_inc(v_a_134_);
lean_dec(v___x_133_);
v___x_136_ = lean_box(0);
v_isShared_137_ = v_isSharedCheck_143_;
goto v_resetjp_135_;
}
v_resetjp_135_:
{
lean_object* v___x_138_; lean_object* v___x_139_; lean_object* v___x_141_; 
v___x_138_ = lean_obj_once(&lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__16, &lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__16_once, _init_lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__16);
v___x_139_ = lean_string_append(v___x_138_, v_a_134_);
lean_dec(v_a_134_);
if (v_isShared_137_ == 0)
{
lean_ctor_set(v___x_136_, 0, v___x_139_);
v___x_141_ = v___x_136_;
goto v_reusejp_140_;
}
else
{
lean_object* v_reuseFailAlloc_142_; 
v_reuseFailAlloc_142_ = lean_alloc_ctor(0, 1, 0);
lean_ctor_set(v_reuseFailAlloc_142_, 0, v___x_139_);
v___x_141_ = v_reuseFailAlloc_142_;
goto v_reusejp_140_;
}
v_reusejp_140_:
{
return v___x_141_;
}
}
}
else
{
if (lean_obj_tag(v___x_133_) == 0)
{
lean_object* v_a_144_; lean_object* v___x_146_; uint8_t v_isShared_147_; uint8_t v_isSharedCheck_151_; 
lean_dec(v_a_131_);
lean_dec(v_json_110_);
v_a_144_ = lean_ctor_get(v___x_133_, 0);
v_isSharedCheck_151_ = !lean_is_exclusive(v___x_133_);
if (v_isSharedCheck_151_ == 0)
{
v___x_146_ = v___x_133_;
v_isShared_147_ = v_isSharedCheck_151_;
goto v_resetjp_145_;
}
else
{
lean_inc(v_a_144_);
lean_dec(v___x_133_);
v___x_146_ = lean_box(0);
v_isShared_147_ = v_isSharedCheck_151_;
goto v_resetjp_145_;
}
v_resetjp_145_:
{
lean_object* v___x_149_; 
if (v_isShared_147_ == 0)
{
lean_ctor_set_tag(v___x_146_, 0);
v___x_149_ = v___x_146_;
goto v_reusejp_148_;
}
else
{
lean_object* v_reuseFailAlloc_150_; 
v_reuseFailAlloc_150_ = lean_alloc_ctor(0, 1, 0);
lean_ctor_set(v_reuseFailAlloc_150_, 0, v_a_144_);
v___x_149_ = v_reuseFailAlloc_150_;
goto v_reusejp_148_;
}
v_reusejp_148_:
{
return v___x_149_;
}
}
}
else
{
lean_object* v_a_152_; lean_object* v___x_153_; lean_object* v___x_154_; 
v_a_152_ = lean_ctor_get(v___x_133_, 0);
lean_inc(v_a_152_);
lean_dec_ref_known(v___x_133_, 1);
v___x_153_ = ((lean_object*)(lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__17));
lean_inc(v_json_110_);
v___x_154_ = lp_proofwidgets_Lean_Json_getObjValAs_x3f___at___00ProofWidgets_MarkdownDisplay_instFromJsonProps_fromJson_spec__0(v_json_110_, v___x_153_);
if (lean_obj_tag(v___x_154_) == 0)
{
lean_object* v_a_155_; lean_object* v___x_157_; uint8_t v_isShared_158_; uint8_t v_isSharedCheck_164_; 
lean_dec(v_a_152_);
lean_dec(v_a_131_);
lean_dec(v_json_110_);
v_a_155_ = lean_ctor_get(v___x_154_, 0);
v_isSharedCheck_164_ = !lean_is_exclusive(v___x_154_);
if (v_isSharedCheck_164_ == 0)
{
v___x_157_ = v___x_154_;
v_isShared_158_ = v_isSharedCheck_164_;
goto v_resetjp_156_;
}
else
{
lean_inc(v_a_155_);
lean_dec(v___x_154_);
v___x_157_ = lean_box(0);
v_isShared_158_ = v_isSharedCheck_164_;
goto v_resetjp_156_;
}
v_resetjp_156_:
{
lean_object* v___x_159_; lean_object* v___x_160_; lean_object* v___x_162_; 
v___x_159_ = lean_obj_once(&lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__21, &lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__21_once, _init_lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__21);
v___x_160_ = lean_string_append(v___x_159_, v_a_155_);
lean_dec(v_a_155_);
if (v_isShared_158_ == 0)
{
lean_ctor_set(v___x_157_, 0, v___x_160_);
v___x_162_ = v___x_157_;
goto v_reusejp_161_;
}
else
{
lean_object* v_reuseFailAlloc_163_; 
v_reuseFailAlloc_163_ = lean_alloc_ctor(0, 1, 0);
lean_ctor_set(v_reuseFailAlloc_163_, 0, v___x_160_);
v___x_162_ = v_reuseFailAlloc_163_;
goto v_reusejp_161_;
}
v_reusejp_161_:
{
return v___x_162_;
}
}
}
else
{
if (lean_obj_tag(v___x_154_) == 0)
{
lean_object* v_a_165_; lean_object* v___x_167_; uint8_t v_isShared_168_; uint8_t v_isSharedCheck_172_; 
lean_dec(v_a_152_);
lean_dec(v_a_131_);
lean_dec(v_json_110_);
v_a_165_ = lean_ctor_get(v___x_154_, 0);
v_isSharedCheck_172_ = !lean_is_exclusive(v___x_154_);
if (v_isSharedCheck_172_ == 0)
{
v___x_167_ = v___x_154_;
v_isShared_168_ = v_isSharedCheck_172_;
goto v_resetjp_166_;
}
else
{
lean_inc(v_a_165_);
lean_dec(v___x_154_);
v___x_167_ = lean_box(0);
v_isShared_168_ = v_isSharedCheck_172_;
goto v_resetjp_166_;
}
v_resetjp_166_:
{
lean_object* v___x_170_; 
if (v_isShared_168_ == 0)
{
lean_ctor_set_tag(v___x_167_, 0);
v___x_170_ = v___x_167_;
goto v_reusejp_169_;
}
else
{
lean_object* v_reuseFailAlloc_171_; 
v_reuseFailAlloc_171_ = lean_alloc_ctor(0, 1, 0);
lean_ctor_set(v_reuseFailAlloc_171_, 0, v_a_165_);
v___x_170_ = v_reuseFailAlloc_171_;
goto v_reusejp_169_;
}
v_reusejp_169_:
{
return v___x_170_;
}
}
}
else
{
lean_object* v_a_173_; lean_object* v___x_174_; lean_object* v___x_175_; 
v_a_173_ = lean_ctor_get(v___x_154_, 0);
lean_inc(v_a_173_);
lean_dec_ref_known(v___x_154_, 1);
v___x_174_ = ((lean_object*)(lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__22));
lean_inc(v_json_110_);
v___x_175_ = l_Lean_Json_getObjValAs_x3f___at___00Lean_Lsp_instFromJsonSemanticTokens_fromJson_spec__0(v_json_110_, v___x_174_);
if (lean_obj_tag(v___x_175_) == 0)
{
lean_object* v_a_176_; lean_object* v___x_178_; uint8_t v_isShared_179_; uint8_t v_isSharedCheck_185_; 
lean_dec(v_a_173_);
lean_dec(v_a_152_);
lean_dec(v_a_131_);
lean_dec(v_json_110_);
v_a_176_ = lean_ctor_get(v___x_175_, 0);
v_isSharedCheck_185_ = !lean_is_exclusive(v___x_175_);
if (v_isSharedCheck_185_ == 0)
{
v___x_178_ = v___x_175_;
v_isShared_179_ = v_isSharedCheck_185_;
goto v_resetjp_177_;
}
else
{
lean_inc(v_a_176_);
lean_dec(v___x_175_);
v___x_178_ = lean_box(0);
v_isShared_179_ = v_isSharedCheck_185_;
goto v_resetjp_177_;
}
v_resetjp_177_:
{
lean_object* v___x_180_; lean_object* v___x_181_; lean_object* v___x_183_; 
v___x_180_ = lean_obj_once(&lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__26, &lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__26_once, _init_lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__26);
v___x_181_ = lean_string_append(v___x_180_, v_a_176_);
lean_dec(v_a_176_);
if (v_isShared_179_ == 0)
{
lean_ctor_set(v___x_178_, 0, v___x_181_);
v___x_183_ = v___x_178_;
goto v_reusejp_182_;
}
else
{
lean_object* v_reuseFailAlloc_184_; 
v_reuseFailAlloc_184_ = lean_alloc_ctor(0, 1, 0);
lean_ctor_set(v_reuseFailAlloc_184_, 0, v___x_181_);
v___x_183_ = v_reuseFailAlloc_184_;
goto v_reusejp_182_;
}
v_reusejp_182_:
{
return v___x_183_;
}
}
}
else
{
if (lean_obj_tag(v___x_175_) == 0)
{
lean_object* v_a_186_; lean_object* v___x_188_; uint8_t v_isShared_189_; uint8_t v_isSharedCheck_193_; 
lean_dec(v_a_173_);
lean_dec(v_a_152_);
lean_dec(v_a_131_);
lean_dec(v_json_110_);
v_a_186_ = lean_ctor_get(v___x_175_, 0);
v_isSharedCheck_193_ = !lean_is_exclusive(v___x_175_);
if (v_isSharedCheck_193_ == 0)
{
v___x_188_ = v___x_175_;
v_isShared_189_ = v_isSharedCheck_193_;
goto v_resetjp_187_;
}
else
{
lean_inc(v_a_186_);
lean_dec(v___x_175_);
v___x_188_ = lean_box(0);
v_isShared_189_ = v_isSharedCheck_193_;
goto v_resetjp_187_;
}
v_resetjp_187_:
{
lean_object* v___x_191_; 
if (v_isShared_189_ == 0)
{
lean_ctor_set_tag(v___x_188_, 0);
v___x_191_ = v___x_188_;
goto v_reusejp_190_;
}
else
{
lean_object* v_reuseFailAlloc_192_; 
v_reuseFailAlloc_192_ = lean_alloc_ctor(0, 1, 0);
lean_ctor_set(v_reuseFailAlloc_192_, 0, v_a_186_);
v___x_191_ = v_reuseFailAlloc_192_;
goto v_reusejp_190_;
}
v_reusejp_190_:
{
return v___x_191_;
}
}
}
else
{
lean_object* v_a_194_; lean_object* v___x_195_; lean_object* v___x_196_; 
v_a_194_ = lean_ctor_get(v___x_175_, 0);
lean_inc(v_a_194_);
lean_dec_ref_known(v___x_175_, 1);
v___x_195_ = ((lean_object*)(lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__27));
lean_inc(v_json_110_);
v___x_196_ = l_Lean_Json_getObjValAs_x3f___at___00Lean_Lsp_instFromJsonSemanticTokens_fromJson_spec__0(v_json_110_, v___x_195_);
if (lean_obj_tag(v___x_196_) == 0)
{
lean_object* v_a_197_; lean_object* v___x_199_; uint8_t v_isShared_200_; uint8_t v_isSharedCheck_206_; 
lean_dec(v_a_194_);
lean_dec(v_a_173_);
lean_dec(v_a_152_);
lean_dec(v_a_131_);
lean_dec(v_json_110_);
v_a_197_ = lean_ctor_get(v___x_196_, 0);
v_isSharedCheck_206_ = !lean_is_exclusive(v___x_196_);
if (v_isSharedCheck_206_ == 0)
{
v___x_199_ = v___x_196_;
v_isShared_200_ = v_isSharedCheck_206_;
goto v_resetjp_198_;
}
else
{
lean_inc(v_a_197_);
lean_dec(v___x_196_);
v___x_199_ = lean_box(0);
v_isShared_200_ = v_isSharedCheck_206_;
goto v_resetjp_198_;
}
v_resetjp_198_:
{
lean_object* v___x_201_; lean_object* v___x_202_; lean_object* v___x_204_; 
v___x_201_ = lean_obj_once(&lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__31, &lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__31_once, _init_lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__31);
v___x_202_ = lean_string_append(v___x_201_, v_a_197_);
lean_dec(v_a_197_);
if (v_isShared_200_ == 0)
{
lean_ctor_set(v___x_199_, 0, v___x_202_);
v___x_204_ = v___x_199_;
goto v_reusejp_203_;
}
else
{
lean_object* v_reuseFailAlloc_205_; 
v_reuseFailAlloc_205_ = lean_alloc_ctor(0, 1, 0);
lean_ctor_set(v_reuseFailAlloc_205_, 0, v___x_202_);
v___x_204_ = v_reuseFailAlloc_205_;
goto v_reusejp_203_;
}
v_reusejp_203_:
{
return v___x_204_;
}
}
}
else
{
if (lean_obj_tag(v___x_196_) == 0)
{
lean_object* v_a_207_; lean_object* v___x_209_; uint8_t v_isShared_210_; uint8_t v_isSharedCheck_214_; 
lean_dec(v_a_194_);
lean_dec(v_a_173_);
lean_dec(v_a_152_);
lean_dec(v_a_131_);
lean_dec(v_json_110_);
v_a_207_ = lean_ctor_get(v___x_196_, 0);
v_isSharedCheck_214_ = !lean_is_exclusive(v___x_196_);
if (v_isSharedCheck_214_ == 0)
{
v___x_209_ = v___x_196_;
v_isShared_210_ = v_isSharedCheck_214_;
goto v_resetjp_208_;
}
else
{
lean_inc(v_a_207_);
lean_dec(v___x_196_);
v___x_209_ = lean_box(0);
v_isShared_210_ = v_isSharedCheck_214_;
goto v_resetjp_208_;
}
v_resetjp_208_:
{
lean_object* v___x_212_; 
if (v_isShared_210_ == 0)
{
lean_ctor_set_tag(v___x_209_, 0);
v___x_212_ = v___x_209_;
goto v_reusejp_211_;
}
else
{
lean_object* v_reuseFailAlloc_213_; 
v_reuseFailAlloc_213_ = lean_alloc_ctor(0, 1, 0);
lean_ctor_set(v_reuseFailAlloc_213_, 0, v_a_207_);
v___x_212_ = v_reuseFailAlloc_213_;
goto v_reusejp_211_;
}
v_reusejp_211_:
{
return v___x_212_;
}
}
}
else
{
lean_object* v_a_215_; lean_object* v___x_216_; lean_object* v___x_217_; 
v_a_215_ = lean_ctor_get(v___x_196_, 0);
lean_inc(v_a_215_);
lean_dec_ref_known(v___x_196_, 1);
v___x_216_ = ((lean_object*)(lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__32));
lean_inc(v_json_110_);
v___x_217_ = l_Lean_Json_getObjValAs_x3f___at___00Lean_Server_instFromJsonIlean_fromJson_spec__0(v_json_110_, v___x_216_);
if (lean_obj_tag(v___x_217_) == 0)
{
lean_object* v_a_218_; lean_object* v___x_220_; uint8_t v_isShared_221_; uint8_t v_isSharedCheck_227_; 
lean_dec(v_a_215_);
lean_dec(v_a_194_);
lean_dec(v_a_173_);
lean_dec(v_a_152_);
lean_dec(v_a_131_);
lean_dec(v_json_110_);
v_a_218_ = lean_ctor_get(v___x_217_, 0);
v_isSharedCheck_227_ = !lean_is_exclusive(v___x_217_);
if (v_isSharedCheck_227_ == 0)
{
v___x_220_ = v___x_217_;
v_isShared_221_ = v_isSharedCheck_227_;
goto v_resetjp_219_;
}
else
{
lean_inc(v_a_218_);
lean_dec(v___x_217_);
v___x_220_ = lean_box(0);
v_isShared_221_ = v_isSharedCheck_227_;
goto v_resetjp_219_;
}
v_resetjp_219_:
{
lean_object* v___x_222_; lean_object* v___x_223_; lean_object* v___x_225_; 
v___x_222_ = lean_obj_once(&lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__36, &lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__36_once, _init_lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__36);
v___x_223_ = lean_string_append(v___x_222_, v_a_218_);
lean_dec(v_a_218_);
if (v_isShared_221_ == 0)
{
lean_ctor_set(v___x_220_, 0, v___x_223_);
v___x_225_ = v___x_220_;
goto v_reusejp_224_;
}
else
{
lean_object* v_reuseFailAlloc_226_; 
v_reuseFailAlloc_226_ = lean_alloc_ctor(0, 1, 0);
lean_ctor_set(v_reuseFailAlloc_226_, 0, v___x_223_);
v___x_225_ = v_reuseFailAlloc_226_;
goto v_reusejp_224_;
}
v_reusejp_224_:
{
return v___x_225_;
}
}
}
else
{
if (lean_obj_tag(v___x_217_) == 0)
{
lean_object* v_a_228_; lean_object* v___x_230_; uint8_t v_isShared_231_; uint8_t v_isSharedCheck_235_; 
lean_dec(v_a_215_);
lean_dec(v_a_194_);
lean_dec(v_a_173_);
lean_dec(v_a_152_);
lean_dec(v_a_131_);
lean_dec(v_json_110_);
v_a_228_ = lean_ctor_get(v___x_217_, 0);
v_isSharedCheck_235_ = !lean_is_exclusive(v___x_217_);
if (v_isSharedCheck_235_ == 0)
{
v___x_230_ = v___x_217_;
v_isShared_231_ = v_isSharedCheck_235_;
goto v_resetjp_229_;
}
else
{
lean_inc(v_a_228_);
lean_dec(v___x_217_);
v___x_230_ = lean_box(0);
v_isShared_231_ = v_isSharedCheck_235_;
goto v_resetjp_229_;
}
v_resetjp_229_:
{
lean_object* v___x_233_; 
if (v_isShared_231_ == 0)
{
lean_ctor_set_tag(v___x_230_, 0);
v___x_233_ = v___x_230_;
goto v_reusejp_232_;
}
else
{
lean_object* v_reuseFailAlloc_234_; 
v_reuseFailAlloc_234_ = lean_alloc_ctor(0, 1, 0);
lean_ctor_set(v_reuseFailAlloc_234_, 0, v_a_228_);
v___x_233_ = v_reuseFailAlloc_234_;
goto v_reusejp_232_;
}
v_reusejp_232_:
{
return v___x_233_;
}
}
}
else
{
lean_object* v_a_236_; lean_object* v___x_237_; lean_object* v___x_238_; 
v_a_236_ = lean_ctor_get(v___x_217_, 0);
lean_inc(v_a_236_);
lean_dec_ref_known(v___x_217_, 1);
v___x_237_ = ((lean_object*)(lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__37));
lean_inc(v_json_110_);
v___x_238_ = l_Lean_Json_getObjValAs_x3f___at___00Lean_Lsp_instFromJsonFileSystemWatcher_fromJson_spec__0(v_json_110_, v___x_237_);
if (lean_obj_tag(v___x_238_) == 0)
{
lean_object* v_a_239_; lean_object* v___x_241_; uint8_t v_isShared_242_; uint8_t v_isSharedCheck_248_; 
lean_dec(v_a_236_);
lean_dec(v_a_215_);
lean_dec(v_a_194_);
lean_dec(v_a_173_);
lean_dec(v_a_152_);
lean_dec(v_a_131_);
lean_dec(v_json_110_);
v_a_239_ = lean_ctor_get(v___x_238_, 0);
v_isSharedCheck_248_ = !lean_is_exclusive(v___x_238_);
if (v_isSharedCheck_248_ == 0)
{
v___x_241_ = v___x_238_;
v_isShared_242_ = v_isSharedCheck_248_;
goto v_resetjp_240_;
}
else
{
lean_inc(v_a_239_);
lean_dec(v___x_238_);
v___x_241_ = lean_box(0);
v_isShared_242_ = v_isSharedCheck_248_;
goto v_resetjp_240_;
}
v_resetjp_240_:
{
lean_object* v___x_243_; lean_object* v___x_244_; lean_object* v___x_246_; 
v___x_243_ = lean_obj_once(&lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__41, &lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__41_once, _init_lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__41);
v___x_244_ = lean_string_append(v___x_243_, v_a_239_);
lean_dec(v_a_239_);
if (v_isShared_242_ == 0)
{
lean_ctor_set(v___x_241_, 0, v___x_244_);
v___x_246_ = v___x_241_;
goto v_reusejp_245_;
}
else
{
lean_object* v_reuseFailAlloc_247_; 
v_reuseFailAlloc_247_ = lean_alloc_ctor(0, 1, 0);
lean_ctor_set(v_reuseFailAlloc_247_, 0, v___x_244_);
v___x_246_ = v_reuseFailAlloc_247_;
goto v_reusejp_245_;
}
v_reusejp_245_:
{
return v___x_246_;
}
}
}
else
{
if (lean_obj_tag(v___x_238_) == 0)
{
lean_object* v_a_249_; lean_object* v___x_251_; uint8_t v_isShared_252_; uint8_t v_isSharedCheck_256_; 
lean_dec(v_a_236_);
lean_dec(v_a_215_);
lean_dec(v_a_194_);
lean_dec(v_a_173_);
lean_dec(v_a_152_);
lean_dec(v_a_131_);
lean_dec(v_json_110_);
v_a_249_ = lean_ctor_get(v___x_238_, 0);
v_isSharedCheck_256_ = !lean_is_exclusive(v___x_238_);
if (v_isSharedCheck_256_ == 0)
{
v___x_251_ = v___x_238_;
v_isShared_252_ = v_isSharedCheck_256_;
goto v_resetjp_250_;
}
else
{
lean_inc(v_a_249_);
lean_dec(v___x_238_);
v___x_251_ = lean_box(0);
v_isShared_252_ = v_isSharedCheck_256_;
goto v_resetjp_250_;
}
v_resetjp_250_:
{
lean_object* v___x_254_; 
if (v_isShared_252_ == 0)
{
lean_ctor_set_tag(v___x_251_, 0);
v___x_254_ = v___x_251_;
goto v_reusejp_253_;
}
else
{
lean_object* v_reuseFailAlloc_255_; 
v_reuseFailAlloc_255_ = lean_alloc_ctor(0, 1, 0);
lean_ctor_set(v_reuseFailAlloc_255_, 0, v_a_249_);
v___x_254_ = v_reuseFailAlloc_255_;
goto v_reusejp_253_;
}
v_reusejp_253_:
{
return v___x_254_;
}
}
}
else
{
lean_object* v_a_257_; lean_object* v___x_258_; lean_object* v___x_259_; 
v_a_257_ = lean_ctor_get(v___x_238_, 0);
lean_inc(v_a_257_);
lean_dec_ref_known(v___x_238_, 1);
v___x_258_ = ((lean_object*)(lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__42));
v___x_259_ = l_Lean_Json_getObjValAs_x3f___at___00Lean_Lsp_instFromJsonLeanILeanHeaderSetupInfoParams_fromJson_spec__1(v_json_110_, v___x_258_);
if (lean_obj_tag(v___x_259_) == 0)
{
lean_object* v_a_260_; lean_object* v___x_262_; uint8_t v_isShared_263_; uint8_t v_isSharedCheck_269_; 
lean_dec(v_a_257_);
lean_dec(v_a_236_);
lean_dec(v_a_215_);
lean_dec(v_a_194_);
lean_dec(v_a_173_);
lean_dec(v_a_152_);
lean_dec(v_a_131_);
v_a_260_ = lean_ctor_get(v___x_259_, 0);
v_isSharedCheck_269_ = !lean_is_exclusive(v___x_259_);
if (v_isSharedCheck_269_ == 0)
{
v___x_262_ = v___x_259_;
v_isShared_263_ = v_isSharedCheck_269_;
goto v_resetjp_261_;
}
else
{
lean_inc(v_a_260_);
lean_dec(v___x_259_);
v___x_262_ = lean_box(0);
v_isShared_263_ = v_isSharedCheck_269_;
goto v_resetjp_261_;
}
v_resetjp_261_:
{
lean_object* v___x_264_; lean_object* v___x_265_; lean_object* v___x_267_; 
v___x_264_ = lean_obj_once(&lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__46, &lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__46_once, _init_lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__46);
v___x_265_ = lean_string_append(v___x_264_, v_a_260_);
lean_dec(v_a_260_);
if (v_isShared_263_ == 0)
{
lean_ctor_set(v___x_262_, 0, v___x_265_);
v___x_267_ = v___x_262_;
goto v_reusejp_266_;
}
else
{
lean_object* v_reuseFailAlloc_268_; 
v_reuseFailAlloc_268_ = lean_alloc_ctor(0, 1, 0);
lean_ctor_set(v_reuseFailAlloc_268_, 0, v___x_265_);
v___x_267_ = v_reuseFailAlloc_268_;
goto v_reusejp_266_;
}
v_reusejp_266_:
{
return v___x_267_;
}
}
}
else
{
if (lean_obj_tag(v___x_259_) == 0)
{
lean_object* v_a_270_; lean_object* v___x_272_; uint8_t v_isShared_273_; uint8_t v_isSharedCheck_277_; 
lean_dec(v_a_257_);
lean_dec(v_a_236_);
lean_dec(v_a_215_);
lean_dec(v_a_194_);
lean_dec(v_a_173_);
lean_dec(v_a_152_);
lean_dec(v_a_131_);
v_a_270_ = lean_ctor_get(v___x_259_, 0);
v_isSharedCheck_277_ = !lean_is_exclusive(v___x_259_);
if (v_isSharedCheck_277_ == 0)
{
v___x_272_ = v___x_259_;
v_isShared_273_ = v_isSharedCheck_277_;
goto v_resetjp_271_;
}
else
{
lean_inc(v_a_270_);
lean_dec(v___x_259_);
v___x_272_ = lean_box(0);
v_isShared_273_ = v_isSharedCheck_277_;
goto v_resetjp_271_;
}
v_resetjp_271_:
{
lean_object* v___x_275_; 
if (v_isShared_273_ == 0)
{
lean_ctor_set_tag(v___x_272_, 0);
v___x_275_ = v___x_272_;
goto v_reusejp_274_;
}
else
{
lean_object* v_reuseFailAlloc_276_; 
v_reuseFailAlloc_276_ = lean_alloc_ctor(0, 1, 0);
lean_ctor_set(v_reuseFailAlloc_276_, 0, v_a_270_);
v___x_275_ = v_reuseFailAlloc_276_;
goto v_reusejp_274_;
}
v_reusejp_274_:
{
return v___x_275_;
}
}
}
else
{
lean_object* v_a_278_; lean_object* v___x_280_; uint8_t v_isShared_281_; uint8_t v_isSharedCheck_287_; 
v_a_278_ = lean_ctor_get(v___x_259_, 0);
v_isSharedCheck_287_ = !lean_is_exclusive(v___x_259_);
if (v_isSharedCheck_287_ == 0)
{
v___x_280_ = v___x_259_;
v_isShared_281_ = v_isSharedCheck_287_;
goto v_resetjp_279_;
}
else
{
lean_inc(v_a_278_);
lean_dec(v___x_259_);
v___x_280_ = lean_box(0);
v_isShared_281_ = v_isSharedCheck_287_;
goto v_resetjp_279_;
}
v_resetjp_279_:
{
lean_object* v___x_282_; uint8_t v___x_283_; lean_object* v___x_285_; 
v___x_282_ = lean_alloc_ctor(0, 7, 1);
lean_ctor_set(v___x_282_, 0, v_a_131_);
lean_ctor_set(v___x_282_, 1, v_a_152_);
lean_ctor_set(v___x_282_, 2, v_a_173_);
lean_ctor_set(v___x_282_, 3, v_a_194_);
lean_ctor_set(v___x_282_, 4, v_a_215_);
lean_ctor_set(v___x_282_, 5, v_a_236_);
lean_ctor_set(v___x_282_, 6, v_a_257_);
v___x_283_ = lean_unbox(v_a_278_);
lean_dec(v_a_278_);
lean_ctor_set_uint8(v___x_282_, sizeof(void*)*7, v___x_283_);
if (v_isShared_281_ == 0)
{
lean_ctor_set(v___x_280_, 0, v___x_282_);
v___x_285_ = v___x_280_;
goto v_reusejp_284_;
}
else
{
lean_object* v_reuseFailAlloc_286_; 
v_reuseFailAlloc_286_ = lean_alloc_ctor(1, 1, 0);
lean_ctor_set(v_reuseFailAlloc_286_, 0, v___x_282_);
v___x_285_ = v_reuseFailAlloc_286_;
goto v_reusejp_284_;
}
v_reusejp_284_:
{
return v___x_285_;
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
LEAN_EXPORT lean_object* lp_competition_Lean_Json_getObjValAs_x3f___at___00R24DotCostHarness_instFromJsonRoundCase_fromJson_spec__0(lean_object* v_j_290_, lean_object* v_k_291_){
_start:
{
lean_object* v___x_292_; lean_object* v___x_293_; 
v___x_292_ = l_Lean_Json_getObjValD(v_j_290_, v_k_291_);
v___x_293_ = l_Lean_Json_getInt_x3f(v___x_292_);
return v___x_293_;
}
}
LEAN_EXPORT lean_object* lp_competition_Lean_Json_getObjValAs_x3f___at___00R24DotCostHarness_instFromJsonRoundCase_fromJson_spec__0___boxed(lean_object* v_j_294_, lean_object* v_k_295_){
_start:
{
lean_object* v_res_296_; 
v_res_296_ = lp_competition_Lean_Json_getObjValAs_x3f___at___00R24DotCostHarness_instFromJsonRoundCase_fromJson_spec__0(v_j_294_, v_k_295_);
lean_dec_ref(v_k_295_);
return v_res_296_;
}
}
static lean_object* _init_lp_competition_R24DotCostHarness_instFromJsonRoundCase_fromJson___closed__3(void){
_start:
{
uint8_t v___x_302_; lean_object* v___x_303_; lean_object* v___x_304_; 
v___x_302_ = 1;
v___x_303_ = ((lean_object*)(lp_competition_R24DotCostHarness_instFromJsonRoundCase_fromJson___closed__2));
v___x_304_ = l_Lean_Name_toStringWithToken___at___00Lean_Name_toString_spec__0(v___x_303_, v___x_302_);
return v___x_304_;
}
}
static lean_object* _init_lp_competition_R24DotCostHarness_instFromJsonRoundCase_fromJson___closed__4(void){
_start:
{
lean_object* v___x_305_; lean_object* v___x_306_; lean_object* v___x_307_; 
v___x_305_ = ((lean_object*)(lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__5));
v___x_306_ = lean_obj_once(&lp_competition_R24DotCostHarness_instFromJsonRoundCase_fromJson___closed__3, &lp_competition_R24DotCostHarness_instFromJsonRoundCase_fromJson___closed__3_once, _init_lp_competition_R24DotCostHarness_instFromJsonRoundCase_fromJson___closed__3);
v___x_307_ = lean_string_append(v___x_306_, v___x_305_);
return v___x_307_;
}
}
static lean_object* _init_lp_competition_R24DotCostHarness_instFromJsonRoundCase_fromJson___closed__6(void){
_start:
{
uint8_t v___x_310_; lean_object* v___x_311_; lean_object* v___x_312_; 
v___x_310_ = 1;
v___x_311_ = ((lean_object*)(lp_competition_R24DotCostHarness_instFromJsonRoundCase_fromJson___closed__5));
v___x_312_ = l_Lean_Name_toStringWithToken___at___00Lean_Name_toString_spec__0(v___x_311_, v___x_310_);
return v___x_312_;
}
}
static lean_object* _init_lp_competition_R24DotCostHarness_instFromJsonRoundCase_fromJson___closed__7(void){
_start:
{
lean_object* v___x_313_; lean_object* v___x_314_; lean_object* v___x_315_; 
v___x_313_ = lean_obj_once(&lp_competition_R24DotCostHarness_instFromJsonRoundCase_fromJson___closed__6, &lp_competition_R24DotCostHarness_instFromJsonRoundCase_fromJson___closed__6_once, _init_lp_competition_R24DotCostHarness_instFromJsonRoundCase_fromJson___closed__6);
v___x_314_ = lean_obj_once(&lp_competition_R24DotCostHarness_instFromJsonRoundCase_fromJson___closed__4, &lp_competition_R24DotCostHarness_instFromJsonRoundCase_fromJson___closed__4_once, _init_lp_competition_R24DotCostHarness_instFromJsonRoundCase_fromJson___closed__4);
v___x_315_ = lean_string_append(v___x_314_, v___x_313_);
return v___x_315_;
}
}
static lean_object* _init_lp_competition_R24DotCostHarness_instFromJsonRoundCase_fromJson___closed__8(void){
_start:
{
lean_object* v___x_316_; lean_object* v___x_317_; lean_object* v___x_318_; 
v___x_316_ = ((lean_object*)(lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__10));
v___x_317_ = lean_obj_once(&lp_competition_R24DotCostHarness_instFromJsonRoundCase_fromJson___closed__7, &lp_competition_R24DotCostHarness_instFromJsonRoundCase_fromJson___closed__7_once, _init_lp_competition_R24DotCostHarness_instFromJsonRoundCase_fromJson___closed__7);
v___x_318_ = lean_string_append(v___x_317_, v___x_316_);
return v___x_318_;
}
}
static lean_object* _init_lp_competition_R24DotCostHarness_instFromJsonRoundCase_fromJson___closed__11(void){
_start:
{
uint8_t v___x_322_; lean_object* v___x_323_; lean_object* v___x_324_; 
v___x_322_ = 1;
v___x_323_ = ((lean_object*)(lp_competition_R24DotCostHarness_instFromJsonRoundCase_fromJson___closed__10));
v___x_324_ = l_Lean_Name_toStringWithToken___at___00Lean_Name_toString_spec__0(v___x_323_, v___x_322_);
return v___x_324_;
}
}
static lean_object* _init_lp_competition_R24DotCostHarness_instFromJsonRoundCase_fromJson___closed__12(void){
_start:
{
lean_object* v___x_325_; lean_object* v___x_326_; lean_object* v___x_327_; 
v___x_325_ = lean_obj_once(&lp_competition_R24DotCostHarness_instFromJsonRoundCase_fromJson___closed__11, &lp_competition_R24DotCostHarness_instFromJsonRoundCase_fromJson___closed__11_once, _init_lp_competition_R24DotCostHarness_instFromJsonRoundCase_fromJson___closed__11);
v___x_326_ = lean_obj_once(&lp_competition_R24DotCostHarness_instFromJsonRoundCase_fromJson___closed__4, &lp_competition_R24DotCostHarness_instFromJsonRoundCase_fromJson___closed__4_once, _init_lp_competition_R24DotCostHarness_instFromJsonRoundCase_fromJson___closed__4);
v___x_327_ = lean_string_append(v___x_326_, v___x_325_);
return v___x_327_;
}
}
static lean_object* _init_lp_competition_R24DotCostHarness_instFromJsonRoundCase_fromJson___closed__13(void){
_start:
{
lean_object* v___x_328_; lean_object* v___x_329_; lean_object* v___x_330_; 
v___x_328_ = ((lean_object*)(lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__10));
v___x_329_ = lean_obj_once(&lp_competition_R24DotCostHarness_instFromJsonRoundCase_fromJson___closed__12, &lp_competition_R24DotCostHarness_instFromJsonRoundCase_fromJson___closed__12_once, _init_lp_competition_R24DotCostHarness_instFromJsonRoundCase_fromJson___closed__12);
v___x_330_ = lean_string_append(v___x_329_, v___x_328_);
return v___x_330_;
}
}
static lean_object* _init_lp_competition_R24DotCostHarness_instFromJsonRoundCase_fromJson___closed__16(void){
_start:
{
uint8_t v___x_334_; lean_object* v___x_335_; lean_object* v___x_336_; 
v___x_334_ = 1;
v___x_335_ = ((lean_object*)(lp_competition_R24DotCostHarness_instFromJsonRoundCase_fromJson___closed__15));
v___x_336_ = l_Lean_Name_toStringWithToken___at___00Lean_Name_toString_spec__0(v___x_335_, v___x_334_);
return v___x_336_;
}
}
static lean_object* _init_lp_competition_R24DotCostHarness_instFromJsonRoundCase_fromJson___closed__17(void){
_start:
{
lean_object* v___x_337_; lean_object* v___x_338_; lean_object* v___x_339_; 
v___x_337_ = lean_obj_once(&lp_competition_R24DotCostHarness_instFromJsonRoundCase_fromJson___closed__16, &lp_competition_R24DotCostHarness_instFromJsonRoundCase_fromJson___closed__16_once, _init_lp_competition_R24DotCostHarness_instFromJsonRoundCase_fromJson___closed__16);
v___x_338_ = lean_obj_once(&lp_competition_R24DotCostHarness_instFromJsonRoundCase_fromJson___closed__4, &lp_competition_R24DotCostHarness_instFromJsonRoundCase_fromJson___closed__4_once, _init_lp_competition_R24DotCostHarness_instFromJsonRoundCase_fromJson___closed__4);
v___x_339_ = lean_string_append(v___x_338_, v___x_337_);
return v___x_339_;
}
}
static lean_object* _init_lp_competition_R24DotCostHarness_instFromJsonRoundCase_fromJson___closed__18(void){
_start:
{
lean_object* v___x_340_; lean_object* v___x_341_; lean_object* v___x_342_; 
v___x_340_ = ((lean_object*)(lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__10));
v___x_341_ = lean_obj_once(&lp_competition_R24DotCostHarness_instFromJsonRoundCase_fromJson___closed__17, &lp_competition_R24DotCostHarness_instFromJsonRoundCase_fromJson___closed__17_once, _init_lp_competition_R24DotCostHarness_instFromJsonRoundCase_fromJson___closed__17);
v___x_342_ = lean_string_append(v___x_341_, v___x_340_);
return v___x_342_;
}
}
static lean_object* _init_lp_competition_R24DotCostHarness_instFromJsonRoundCase_fromJson___closed__21(void){
_start:
{
uint8_t v___x_346_; lean_object* v___x_347_; lean_object* v___x_348_; 
v___x_346_ = 1;
v___x_347_ = ((lean_object*)(lp_competition_R24DotCostHarness_instFromJsonRoundCase_fromJson___closed__20));
v___x_348_ = l_Lean_Name_toStringWithToken___at___00Lean_Name_toString_spec__0(v___x_347_, v___x_346_);
return v___x_348_;
}
}
static lean_object* _init_lp_competition_R24DotCostHarness_instFromJsonRoundCase_fromJson___closed__22(void){
_start:
{
lean_object* v___x_349_; lean_object* v___x_350_; lean_object* v___x_351_; 
v___x_349_ = lean_obj_once(&lp_competition_R24DotCostHarness_instFromJsonRoundCase_fromJson___closed__21, &lp_competition_R24DotCostHarness_instFromJsonRoundCase_fromJson___closed__21_once, _init_lp_competition_R24DotCostHarness_instFromJsonRoundCase_fromJson___closed__21);
v___x_350_ = lean_obj_once(&lp_competition_R24DotCostHarness_instFromJsonRoundCase_fromJson___closed__4, &lp_competition_R24DotCostHarness_instFromJsonRoundCase_fromJson___closed__4_once, _init_lp_competition_R24DotCostHarness_instFromJsonRoundCase_fromJson___closed__4);
v___x_351_ = lean_string_append(v___x_350_, v___x_349_);
return v___x_351_;
}
}
static lean_object* _init_lp_competition_R24DotCostHarness_instFromJsonRoundCase_fromJson___closed__23(void){
_start:
{
lean_object* v___x_352_; lean_object* v___x_353_; lean_object* v___x_354_; 
v___x_352_ = ((lean_object*)(lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__10));
v___x_353_ = lean_obj_once(&lp_competition_R24DotCostHarness_instFromJsonRoundCase_fromJson___closed__22, &lp_competition_R24DotCostHarness_instFromJsonRoundCase_fromJson___closed__22_once, _init_lp_competition_R24DotCostHarness_instFromJsonRoundCase_fromJson___closed__22);
v___x_354_ = lean_string_append(v___x_353_, v___x_352_);
return v___x_354_;
}
}
static lean_object* _init_lp_competition_R24DotCostHarness_instFromJsonRoundCase_fromJson___closed__26(void){
_start:
{
uint8_t v___x_358_; lean_object* v___x_359_; lean_object* v___x_360_; 
v___x_358_ = 1;
v___x_359_ = ((lean_object*)(lp_competition_R24DotCostHarness_instFromJsonRoundCase_fromJson___closed__25));
v___x_360_ = l_Lean_Name_toStringWithToken___at___00Lean_Name_toString_spec__0(v___x_359_, v___x_358_);
return v___x_360_;
}
}
static lean_object* _init_lp_competition_R24DotCostHarness_instFromJsonRoundCase_fromJson___closed__27(void){
_start:
{
lean_object* v___x_361_; lean_object* v___x_362_; lean_object* v___x_363_; 
v___x_361_ = lean_obj_once(&lp_competition_R24DotCostHarness_instFromJsonRoundCase_fromJson___closed__26, &lp_competition_R24DotCostHarness_instFromJsonRoundCase_fromJson___closed__26_once, _init_lp_competition_R24DotCostHarness_instFromJsonRoundCase_fromJson___closed__26);
v___x_362_ = lean_obj_once(&lp_competition_R24DotCostHarness_instFromJsonRoundCase_fromJson___closed__4, &lp_competition_R24DotCostHarness_instFromJsonRoundCase_fromJson___closed__4_once, _init_lp_competition_R24DotCostHarness_instFromJsonRoundCase_fromJson___closed__4);
v___x_363_ = lean_string_append(v___x_362_, v___x_361_);
return v___x_363_;
}
}
static lean_object* _init_lp_competition_R24DotCostHarness_instFromJsonRoundCase_fromJson___closed__28(void){
_start:
{
lean_object* v___x_364_; lean_object* v___x_365_; lean_object* v___x_366_; 
v___x_364_ = ((lean_object*)(lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__10));
v___x_365_ = lean_obj_once(&lp_competition_R24DotCostHarness_instFromJsonRoundCase_fromJson___closed__27, &lp_competition_R24DotCostHarness_instFromJsonRoundCase_fromJson___closed__27_once, _init_lp_competition_R24DotCostHarness_instFromJsonRoundCase_fromJson___closed__27);
v___x_366_ = lean_string_append(v___x_365_, v___x_364_);
return v___x_366_;
}
}
static lean_object* _init_lp_competition_R24DotCostHarness_instFromJsonRoundCase_fromJson___closed__29(void){
_start:
{
lean_object* v___x_367_; lean_object* v___x_368_; lean_object* v___x_369_; 
v___x_367_ = lean_obj_once(&lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__34, &lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__34_once, _init_lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__34);
v___x_368_ = lean_obj_once(&lp_competition_R24DotCostHarness_instFromJsonRoundCase_fromJson___closed__4, &lp_competition_R24DotCostHarness_instFromJsonRoundCase_fromJson___closed__4_once, _init_lp_competition_R24DotCostHarness_instFromJsonRoundCase_fromJson___closed__4);
v___x_369_ = lean_string_append(v___x_368_, v___x_367_);
return v___x_369_;
}
}
static lean_object* _init_lp_competition_R24DotCostHarness_instFromJsonRoundCase_fromJson___closed__30(void){
_start:
{
lean_object* v___x_370_; lean_object* v___x_371_; lean_object* v___x_372_; 
v___x_370_ = ((lean_object*)(lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__10));
v___x_371_ = lean_obj_once(&lp_competition_R24DotCostHarness_instFromJsonRoundCase_fromJson___closed__29, &lp_competition_R24DotCostHarness_instFromJsonRoundCase_fromJson___closed__29_once, _init_lp_competition_R24DotCostHarness_instFromJsonRoundCase_fromJson___closed__29);
v___x_372_ = lean_string_append(v___x_371_, v___x_370_);
return v___x_372_;
}
}
LEAN_EXPORT lean_object* lp_competition_R24DotCostHarness_instFromJsonRoundCase_fromJson(lean_object* v_json_373_){
_start:
{
lean_object* v___x_374_; lean_object* v___x_375_; 
v___x_374_ = ((lean_object*)(lp_competition_R24DotCostHarness_instFromJsonRoundCase_fromJson___closed__0));
lean_inc(v_json_373_);
v___x_375_ = lp_proofwidgets_Lean_Json_getObjValAs_x3f___at___00ProofWidgets_MarkdownDisplay_instFromJsonProps_fromJson_spec__0(v_json_373_, v___x_374_);
if (lean_obj_tag(v___x_375_) == 0)
{
lean_object* v_a_376_; lean_object* v___x_378_; uint8_t v_isShared_379_; uint8_t v_isSharedCheck_385_; 
lean_dec(v_json_373_);
v_a_376_ = lean_ctor_get(v___x_375_, 0);
v_isSharedCheck_385_ = !lean_is_exclusive(v___x_375_);
if (v_isSharedCheck_385_ == 0)
{
v___x_378_ = v___x_375_;
v_isShared_379_ = v_isSharedCheck_385_;
goto v_resetjp_377_;
}
else
{
lean_inc(v_a_376_);
lean_dec(v___x_375_);
v___x_378_ = lean_box(0);
v_isShared_379_ = v_isSharedCheck_385_;
goto v_resetjp_377_;
}
v_resetjp_377_:
{
lean_object* v___x_380_; lean_object* v___x_381_; lean_object* v___x_383_; 
v___x_380_ = lean_obj_once(&lp_competition_R24DotCostHarness_instFromJsonRoundCase_fromJson___closed__8, &lp_competition_R24DotCostHarness_instFromJsonRoundCase_fromJson___closed__8_once, _init_lp_competition_R24DotCostHarness_instFromJsonRoundCase_fromJson___closed__8);
v___x_381_ = lean_string_append(v___x_380_, v_a_376_);
lean_dec(v_a_376_);
if (v_isShared_379_ == 0)
{
lean_ctor_set(v___x_378_, 0, v___x_381_);
v___x_383_ = v___x_378_;
goto v_reusejp_382_;
}
else
{
lean_object* v_reuseFailAlloc_384_; 
v_reuseFailAlloc_384_ = lean_alloc_ctor(0, 1, 0);
lean_ctor_set(v_reuseFailAlloc_384_, 0, v___x_381_);
v___x_383_ = v_reuseFailAlloc_384_;
goto v_reusejp_382_;
}
v_reusejp_382_:
{
return v___x_383_;
}
}
}
else
{
if (lean_obj_tag(v___x_375_) == 0)
{
lean_object* v_a_386_; lean_object* v___x_388_; uint8_t v_isShared_389_; uint8_t v_isSharedCheck_393_; 
lean_dec(v_json_373_);
v_a_386_ = lean_ctor_get(v___x_375_, 0);
v_isSharedCheck_393_ = !lean_is_exclusive(v___x_375_);
if (v_isSharedCheck_393_ == 0)
{
v___x_388_ = v___x_375_;
v_isShared_389_ = v_isSharedCheck_393_;
goto v_resetjp_387_;
}
else
{
lean_inc(v_a_386_);
lean_dec(v___x_375_);
v___x_388_ = lean_box(0);
v_isShared_389_ = v_isSharedCheck_393_;
goto v_resetjp_387_;
}
v_resetjp_387_:
{
lean_object* v___x_391_; 
if (v_isShared_389_ == 0)
{
lean_ctor_set_tag(v___x_388_, 0);
v___x_391_ = v___x_388_;
goto v_reusejp_390_;
}
else
{
lean_object* v_reuseFailAlloc_392_; 
v_reuseFailAlloc_392_ = lean_alloc_ctor(0, 1, 0);
lean_ctor_set(v_reuseFailAlloc_392_, 0, v_a_386_);
v___x_391_ = v_reuseFailAlloc_392_;
goto v_reusejp_390_;
}
v_reusejp_390_:
{
return v___x_391_;
}
}
}
else
{
lean_object* v_a_394_; lean_object* v___x_395_; lean_object* v___x_396_; 
v_a_394_ = lean_ctor_get(v___x_375_, 0);
lean_inc(v_a_394_);
lean_dec_ref_known(v___x_375_, 1);
v___x_395_ = ((lean_object*)(lp_competition_R24DotCostHarness_instFromJsonRoundCase_fromJson___closed__9));
lean_inc(v_json_373_);
v___x_396_ = l_Lean_Json_getObjValAs_x3f___at___00Lean_Lsp_instFromJsonLeanILeanHeaderSetupInfoParams_fromJson_spec__1(v_json_373_, v___x_395_);
if (lean_obj_tag(v___x_396_) == 0)
{
lean_object* v_a_397_; lean_object* v___x_399_; uint8_t v_isShared_400_; uint8_t v_isSharedCheck_406_; 
lean_dec(v_a_394_);
lean_dec(v_json_373_);
v_a_397_ = lean_ctor_get(v___x_396_, 0);
v_isSharedCheck_406_ = !lean_is_exclusive(v___x_396_);
if (v_isSharedCheck_406_ == 0)
{
v___x_399_ = v___x_396_;
v_isShared_400_ = v_isSharedCheck_406_;
goto v_resetjp_398_;
}
else
{
lean_inc(v_a_397_);
lean_dec(v___x_396_);
v___x_399_ = lean_box(0);
v_isShared_400_ = v_isSharedCheck_406_;
goto v_resetjp_398_;
}
v_resetjp_398_:
{
lean_object* v___x_401_; lean_object* v___x_402_; lean_object* v___x_404_; 
v___x_401_ = lean_obj_once(&lp_competition_R24DotCostHarness_instFromJsonRoundCase_fromJson___closed__13, &lp_competition_R24DotCostHarness_instFromJsonRoundCase_fromJson___closed__13_once, _init_lp_competition_R24DotCostHarness_instFromJsonRoundCase_fromJson___closed__13);
v___x_402_ = lean_string_append(v___x_401_, v_a_397_);
lean_dec(v_a_397_);
if (v_isShared_400_ == 0)
{
lean_ctor_set(v___x_399_, 0, v___x_402_);
v___x_404_ = v___x_399_;
goto v_reusejp_403_;
}
else
{
lean_object* v_reuseFailAlloc_405_; 
v_reuseFailAlloc_405_ = lean_alloc_ctor(0, 1, 0);
lean_ctor_set(v_reuseFailAlloc_405_, 0, v___x_402_);
v___x_404_ = v_reuseFailAlloc_405_;
goto v_reusejp_403_;
}
v_reusejp_403_:
{
return v___x_404_;
}
}
}
else
{
if (lean_obj_tag(v___x_396_) == 0)
{
lean_object* v_a_407_; lean_object* v___x_409_; uint8_t v_isShared_410_; uint8_t v_isSharedCheck_414_; 
lean_dec(v_a_394_);
lean_dec(v_json_373_);
v_a_407_ = lean_ctor_get(v___x_396_, 0);
v_isSharedCheck_414_ = !lean_is_exclusive(v___x_396_);
if (v_isSharedCheck_414_ == 0)
{
v___x_409_ = v___x_396_;
v_isShared_410_ = v_isSharedCheck_414_;
goto v_resetjp_408_;
}
else
{
lean_inc(v_a_407_);
lean_dec(v___x_396_);
v___x_409_ = lean_box(0);
v_isShared_410_ = v_isSharedCheck_414_;
goto v_resetjp_408_;
}
v_resetjp_408_:
{
lean_object* v___x_412_; 
if (v_isShared_410_ == 0)
{
lean_ctor_set_tag(v___x_409_, 0);
v___x_412_ = v___x_409_;
goto v_reusejp_411_;
}
else
{
lean_object* v_reuseFailAlloc_413_; 
v_reuseFailAlloc_413_ = lean_alloc_ctor(0, 1, 0);
lean_ctor_set(v_reuseFailAlloc_413_, 0, v_a_407_);
v___x_412_ = v_reuseFailAlloc_413_;
goto v_reusejp_411_;
}
v_reusejp_411_:
{
return v___x_412_;
}
}
}
else
{
lean_object* v_a_415_; lean_object* v___x_416_; lean_object* v___x_417_; 
v_a_415_ = lean_ctor_get(v___x_396_, 0);
lean_inc(v_a_415_);
lean_dec_ref_known(v___x_396_, 1);
v___x_416_ = ((lean_object*)(lp_competition_R24DotCostHarness_instFromJsonRoundCase_fromJson___closed__14));
lean_inc(v_json_373_);
v___x_417_ = l_Lean_Json_getObjValAs_x3f___at___00Lean_Server_instFromJsonIlean_fromJson_spec__0(v_json_373_, v___x_416_);
if (lean_obj_tag(v___x_417_) == 0)
{
lean_object* v_a_418_; lean_object* v___x_420_; uint8_t v_isShared_421_; uint8_t v_isSharedCheck_427_; 
lean_dec(v_a_415_);
lean_dec(v_a_394_);
lean_dec(v_json_373_);
v_a_418_ = lean_ctor_get(v___x_417_, 0);
v_isSharedCheck_427_ = !lean_is_exclusive(v___x_417_);
if (v_isSharedCheck_427_ == 0)
{
v___x_420_ = v___x_417_;
v_isShared_421_ = v_isSharedCheck_427_;
goto v_resetjp_419_;
}
else
{
lean_inc(v_a_418_);
lean_dec(v___x_417_);
v___x_420_ = lean_box(0);
v_isShared_421_ = v_isSharedCheck_427_;
goto v_resetjp_419_;
}
v_resetjp_419_:
{
lean_object* v___x_422_; lean_object* v___x_423_; lean_object* v___x_425_; 
v___x_422_ = lean_obj_once(&lp_competition_R24DotCostHarness_instFromJsonRoundCase_fromJson___closed__18, &lp_competition_R24DotCostHarness_instFromJsonRoundCase_fromJson___closed__18_once, _init_lp_competition_R24DotCostHarness_instFromJsonRoundCase_fromJson___closed__18);
v___x_423_ = lean_string_append(v___x_422_, v_a_418_);
lean_dec(v_a_418_);
if (v_isShared_421_ == 0)
{
lean_ctor_set(v___x_420_, 0, v___x_423_);
v___x_425_ = v___x_420_;
goto v_reusejp_424_;
}
else
{
lean_object* v_reuseFailAlloc_426_; 
v_reuseFailAlloc_426_ = lean_alloc_ctor(0, 1, 0);
lean_ctor_set(v_reuseFailAlloc_426_, 0, v___x_423_);
v___x_425_ = v_reuseFailAlloc_426_;
goto v_reusejp_424_;
}
v_reusejp_424_:
{
return v___x_425_;
}
}
}
else
{
if (lean_obj_tag(v___x_417_) == 0)
{
lean_object* v_a_428_; lean_object* v___x_430_; uint8_t v_isShared_431_; uint8_t v_isSharedCheck_435_; 
lean_dec(v_a_415_);
lean_dec(v_a_394_);
lean_dec(v_json_373_);
v_a_428_ = lean_ctor_get(v___x_417_, 0);
v_isSharedCheck_435_ = !lean_is_exclusive(v___x_417_);
if (v_isSharedCheck_435_ == 0)
{
v___x_430_ = v___x_417_;
v_isShared_431_ = v_isSharedCheck_435_;
goto v_resetjp_429_;
}
else
{
lean_inc(v_a_428_);
lean_dec(v___x_417_);
v___x_430_ = lean_box(0);
v_isShared_431_ = v_isSharedCheck_435_;
goto v_resetjp_429_;
}
v_resetjp_429_:
{
lean_object* v___x_433_; 
if (v_isShared_431_ == 0)
{
lean_ctor_set_tag(v___x_430_, 0);
v___x_433_ = v___x_430_;
goto v_reusejp_432_;
}
else
{
lean_object* v_reuseFailAlloc_434_; 
v_reuseFailAlloc_434_ = lean_alloc_ctor(0, 1, 0);
lean_ctor_set(v_reuseFailAlloc_434_, 0, v_a_428_);
v___x_433_ = v_reuseFailAlloc_434_;
goto v_reusejp_432_;
}
v_reusejp_432_:
{
return v___x_433_;
}
}
}
else
{
lean_object* v_a_436_; lean_object* v___x_437_; lean_object* v___x_438_; 
v_a_436_ = lean_ctor_get(v___x_417_, 0);
lean_inc(v_a_436_);
lean_dec_ref_known(v___x_417_, 1);
v___x_437_ = ((lean_object*)(lp_competition_R24DotCostHarness_instFromJsonRoundCase_fromJson___closed__19));
lean_inc(v_json_373_);
v___x_438_ = l_Lean_Json_getObjValAs_x3f___at___00Lean_Server_instFromJsonIlean_fromJson_spec__0(v_json_373_, v___x_437_);
if (lean_obj_tag(v___x_438_) == 0)
{
lean_object* v_a_439_; lean_object* v___x_441_; uint8_t v_isShared_442_; uint8_t v_isSharedCheck_448_; 
lean_dec(v_a_436_);
lean_dec(v_a_415_);
lean_dec(v_a_394_);
lean_dec(v_json_373_);
v_a_439_ = lean_ctor_get(v___x_438_, 0);
v_isSharedCheck_448_ = !lean_is_exclusive(v___x_438_);
if (v_isSharedCheck_448_ == 0)
{
v___x_441_ = v___x_438_;
v_isShared_442_ = v_isSharedCheck_448_;
goto v_resetjp_440_;
}
else
{
lean_inc(v_a_439_);
lean_dec(v___x_438_);
v___x_441_ = lean_box(0);
v_isShared_442_ = v_isSharedCheck_448_;
goto v_resetjp_440_;
}
v_resetjp_440_:
{
lean_object* v___x_443_; lean_object* v___x_444_; lean_object* v___x_446_; 
v___x_443_ = lean_obj_once(&lp_competition_R24DotCostHarness_instFromJsonRoundCase_fromJson___closed__23, &lp_competition_R24DotCostHarness_instFromJsonRoundCase_fromJson___closed__23_once, _init_lp_competition_R24DotCostHarness_instFromJsonRoundCase_fromJson___closed__23);
v___x_444_ = lean_string_append(v___x_443_, v_a_439_);
lean_dec(v_a_439_);
if (v_isShared_442_ == 0)
{
lean_ctor_set(v___x_441_, 0, v___x_444_);
v___x_446_ = v___x_441_;
goto v_reusejp_445_;
}
else
{
lean_object* v_reuseFailAlloc_447_; 
v_reuseFailAlloc_447_ = lean_alloc_ctor(0, 1, 0);
lean_ctor_set(v_reuseFailAlloc_447_, 0, v___x_444_);
v___x_446_ = v_reuseFailAlloc_447_;
goto v_reusejp_445_;
}
v_reusejp_445_:
{
return v___x_446_;
}
}
}
else
{
if (lean_obj_tag(v___x_438_) == 0)
{
lean_object* v_a_449_; lean_object* v___x_451_; uint8_t v_isShared_452_; uint8_t v_isSharedCheck_456_; 
lean_dec(v_a_436_);
lean_dec(v_a_415_);
lean_dec(v_a_394_);
lean_dec(v_json_373_);
v_a_449_ = lean_ctor_get(v___x_438_, 0);
v_isSharedCheck_456_ = !lean_is_exclusive(v___x_438_);
if (v_isSharedCheck_456_ == 0)
{
v___x_451_ = v___x_438_;
v_isShared_452_ = v_isSharedCheck_456_;
goto v_resetjp_450_;
}
else
{
lean_inc(v_a_449_);
lean_dec(v___x_438_);
v___x_451_ = lean_box(0);
v_isShared_452_ = v_isSharedCheck_456_;
goto v_resetjp_450_;
}
v_resetjp_450_:
{
lean_object* v___x_454_; 
if (v_isShared_452_ == 0)
{
lean_ctor_set_tag(v___x_451_, 0);
v___x_454_ = v___x_451_;
goto v_reusejp_453_;
}
else
{
lean_object* v_reuseFailAlloc_455_; 
v_reuseFailAlloc_455_ = lean_alloc_ctor(0, 1, 0);
lean_ctor_set(v_reuseFailAlloc_455_, 0, v_a_449_);
v___x_454_ = v_reuseFailAlloc_455_;
goto v_reusejp_453_;
}
v_reusejp_453_:
{
return v___x_454_;
}
}
}
else
{
lean_object* v_a_457_; lean_object* v___x_458_; lean_object* v___x_459_; 
v_a_457_ = lean_ctor_get(v___x_438_, 0);
lean_inc(v_a_457_);
lean_dec_ref_known(v___x_438_, 1);
v___x_458_ = ((lean_object*)(lp_competition_R24DotCostHarness_instFromJsonRoundCase_fromJson___closed__24));
lean_inc(v_json_373_);
v___x_459_ = lp_competition_Lean_Json_getObjValAs_x3f___at___00R24DotCostHarness_instFromJsonRoundCase_fromJson_spec__0(v_json_373_, v___x_458_);
if (lean_obj_tag(v___x_459_) == 0)
{
lean_object* v_a_460_; lean_object* v___x_462_; uint8_t v_isShared_463_; uint8_t v_isSharedCheck_469_; 
lean_dec(v_a_457_);
lean_dec(v_a_436_);
lean_dec(v_a_415_);
lean_dec(v_a_394_);
lean_dec(v_json_373_);
v_a_460_ = lean_ctor_get(v___x_459_, 0);
v_isSharedCheck_469_ = !lean_is_exclusive(v___x_459_);
if (v_isSharedCheck_469_ == 0)
{
v___x_462_ = v___x_459_;
v_isShared_463_ = v_isSharedCheck_469_;
goto v_resetjp_461_;
}
else
{
lean_inc(v_a_460_);
lean_dec(v___x_459_);
v___x_462_ = lean_box(0);
v_isShared_463_ = v_isSharedCheck_469_;
goto v_resetjp_461_;
}
v_resetjp_461_:
{
lean_object* v___x_464_; lean_object* v___x_465_; lean_object* v___x_467_; 
v___x_464_ = lean_obj_once(&lp_competition_R24DotCostHarness_instFromJsonRoundCase_fromJson___closed__28, &lp_competition_R24DotCostHarness_instFromJsonRoundCase_fromJson___closed__28_once, _init_lp_competition_R24DotCostHarness_instFromJsonRoundCase_fromJson___closed__28);
v___x_465_ = lean_string_append(v___x_464_, v_a_460_);
lean_dec(v_a_460_);
if (v_isShared_463_ == 0)
{
lean_ctor_set(v___x_462_, 0, v___x_465_);
v___x_467_ = v___x_462_;
goto v_reusejp_466_;
}
else
{
lean_object* v_reuseFailAlloc_468_; 
v_reuseFailAlloc_468_ = lean_alloc_ctor(0, 1, 0);
lean_ctor_set(v_reuseFailAlloc_468_, 0, v___x_465_);
v___x_467_ = v_reuseFailAlloc_468_;
goto v_reusejp_466_;
}
v_reusejp_466_:
{
return v___x_467_;
}
}
}
else
{
if (lean_obj_tag(v___x_459_) == 0)
{
lean_object* v_a_470_; lean_object* v___x_472_; uint8_t v_isShared_473_; uint8_t v_isSharedCheck_477_; 
lean_dec(v_a_457_);
lean_dec(v_a_436_);
lean_dec(v_a_415_);
lean_dec(v_a_394_);
lean_dec(v_json_373_);
v_a_470_ = lean_ctor_get(v___x_459_, 0);
v_isSharedCheck_477_ = !lean_is_exclusive(v___x_459_);
if (v_isSharedCheck_477_ == 0)
{
v___x_472_ = v___x_459_;
v_isShared_473_ = v_isSharedCheck_477_;
goto v_resetjp_471_;
}
else
{
lean_inc(v_a_470_);
lean_dec(v___x_459_);
v___x_472_ = lean_box(0);
v_isShared_473_ = v_isSharedCheck_477_;
goto v_resetjp_471_;
}
v_resetjp_471_:
{
lean_object* v___x_475_; 
if (v_isShared_473_ == 0)
{
lean_ctor_set_tag(v___x_472_, 0);
v___x_475_ = v___x_472_;
goto v_reusejp_474_;
}
else
{
lean_object* v_reuseFailAlloc_476_; 
v_reuseFailAlloc_476_ = lean_alloc_ctor(0, 1, 0);
lean_ctor_set(v_reuseFailAlloc_476_, 0, v_a_470_);
v___x_475_ = v_reuseFailAlloc_476_;
goto v_reusejp_474_;
}
v_reusejp_474_:
{
return v___x_475_;
}
}
}
else
{
lean_object* v_a_478_; lean_object* v___x_479_; lean_object* v___x_480_; 
v_a_478_ = lean_ctor_get(v___x_459_, 0);
lean_inc(v_a_478_);
lean_dec_ref_known(v___x_459_, 1);
v___x_479_ = ((lean_object*)(lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__32));
v___x_480_ = l_Lean_Json_getObjValAs_x3f___at___00Lean_Server_instFromJsonIlean_fromJson_spec__0(v_json_373_, v___x_479_);
if (lean_obj_tag(v___x_480_) == 0)
{
lean_object* v_a_481_; lean_object* v___x_483_; uint8_t v_isShared_484_; uint8_t v_isSharedCheck_490_; 
lean_dec(v_a_478_);
lean_dec(v_a_457_);
lean_dec(v_a_436_);
lean_dec(v_a_415_);
lean_dec(v_a_394_);
v_a_481_ = lean_ctor_get(v___x_480_, 0);
v_isSharedCheck_490_ = !lean_is_exclusive(v___x_480_);
if (v_isSharedCheck_490_ == 0)
{
v___x_483_ = v___x_480_;
v_isShared_484_ = v_isSharedCheck_490_;
goto v_resetjp_482_;
}
else
{
lean_inc(v_a_481_);
lean_dec(v___x_480_);
v___x_483_ = lean_box(0);
v_isShared_484_ = v_isSharedCheck_490_;
goto v_resetjp_482_;
}
v_resetjp_482_:
{
lean_object* v___x_485_; lean_object* v___x_486_; lean_object* v___x_488_; 
v___x_485_ = lean_obj_once(&lp_competition_R24DotCostHarness_instFromJsonRoundCase_fromJson___closed__30, &lp_competition_R24DotCostHarness_instFromJsonRoundCase_fromJson___closed__30_once, _init_lp_competition_R24DotCostHarness_instFromJsonRoundCase_fromJson___closed__30);
v___x_486_ = lean_string_append(v___x_485_, v_a_481_);
lean_dec(v_a_481_);
if (v_isShared_484_ == 0)
{
lean_ctor_set(v___x_483_, 0, v___x_486_);
v___x_488_ = v___x_483_;
goto v_reusejp_487_;
}
else
{
lean_object* v_reuseFailAlloc_489_; 
v_reuseFailAlloc_489_ = lean_alloc_ctor(0, 1, 0);
lean_ctor_set(v_reuseFailAlloc_489_, 0, v___x_486_);
v___x_488_ = v_reuseFailAlloc_489_;
goto v_reusejp_487_;
}
v_reusejp_487_:
{
return v___x_488_;
}
}
}
else
{
if (lean_obj_tag(v___x_480_) == 0)
{
lean_object* v_a_491_; lean_object* v___x_493_; uint8_t v_isShared_494_; uint8_t v_isSharedCheck_498_; 
lean_dec(v_a_478_);
lean_dec(v_a_457_);
lean_dec(v_a_436_);
lean_dec(v_a_415_);
lean_dec(v_a_394_);
v_a_491_ = lean_ctor_get(v___x_480_, 0);
v_isSharedCheck_498_ = !lean_is_exclusive(v___x_480_);
if (v_isSharedCheck_498_ == 0)
{
v___x_493_ = v___x_480_;
v_isShared_494_ = v_isSharedCheck_498_;
goto v_resetjp_492_;
}
else
{
lean_inc(v_a_491_);
lean_dec(v___x_480_);
v___x_493_ = lean_box(0);
v_isShared_494_ = v_isSharedCheck_498_;
goto v_resetjp_492_;
}
v_resetjp_492_:
{
lean_object* v___x_496_; 
if (v_isShared_494_ == 0)
{
lean_ctor_set_tag(v___x_493_, 0);
v___x_496_ = v___x_493_;
goto v_reusejp_495_;
}
else
{
lean_object* v_reuseFailAlloc_497_; 
v_reuseFailAlloc_497_ = lean_alloc_ctor(0, 1, 0);
lean_ctor_set(v_reuseFailAlloc_497_, 0, v_a_491_);
v___x_496_ = v_reuseFailAlloc_497_;
goto v_reusejp_495_;
}
v_reusejp_495_:
{
return v___x_496_;
}
}
}
else
{
lean_object* v_a_499_; lean_object* v___x_501_; uint8_t v_isShared_502_; uint8_t v_isSharedCheck_508_; 
v_a_499_ = lean_ctor_get(v___x_480_, 0);
v_isSharedCheck_508_ = !lean_is_exclusive(v___x_480_);
if (v_isSharedCheck_508_ == 0)
{
v___x_501_ = v___x_480_;
v_isShared_502_ = v_isSharedCheck_508_;
goto v_resetjp_500_;
}
else
{
lean_inc(v_a_499_);
lean_dec(v___x_480_);
v___x_501_ = lean_box(0);
v_isShared_502_ = v_isSharedCheck_508_;
goto v_resetjp_500_;
}
v_resetjp_500_:
{
lean_object* v___x_503_; uint8_t v___x_504_; lean_object* v___x_506_; 
v___x_503_ = lean_alloc_ctor(0, 5, 1);
lean_ctor_set(v___x_503_, 0, v_a_394_);
lean_ctor_set(v___x_503_, 1, v_a_436_);
lean_ctor_set(v___x_503_, 2, v_a_457_);
lean_ctor_set(v___x_503_, 3, v_a_478_);
lean_ctor_set(v___x_503_, 4, v_a_499_);
v___x_504_ = lean_unbox(v_a_415_);
lean_dec(v_a_415_);
lean_ctor_set_uint8(v___x_503_, sizeof(void*)*5, v___x_504_);
if (v_isShared_502_ == 0)
{
lean_ctor_set(v___x_501_, 0, v___x_503_);
v___x_506_ = v___x_501_;
goto v_reusejp_505_;
}
else
{
lean_object* v_reuseFailAlloc_507_; 
v_reuseFailAlloc_507_ = lean_alloc_ctor(1, 1, 0);
lean_ctor_set(v_reuseFailAlloc_507_, 0, v___x_503_);
v___x_506_ = v_reuseFailAlloc_507_;
goto v_reusejp_505_;
}
v_reusejp_505_:
{
return v___x_506_;
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
}
}
}
}
}
}
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_mapMUnsafe_map___at___00Lean_Array_fromJson_x3f___at___00Lean_Json_getObjValAs_x3f___at___00R24DotCostHarness_instFromJsonPlan_fromJson_spec__1_spec__2_spec__4(size_t v_sz_511_, size_t v_i_512_, lean_object* v_bs_513_){
_start:
{
uint8_t v___x_514_; 
v___x_514_ = lean_usize_dec_lt(v_i_512_, v_sz_511_);
if (v___x_514_ == 0)
{
lean_object* v___x_515_; 
v___x_515_ = lean_alloc_ctor(1, 1, 0);
lean_ctor_set(v___x_515_, 0, v_bs_513_);
return v___x_515_;
}
else
{
lean_object* v_v_516_; lean_object* v___x_517_; 
v_v_516_ = lean_array_uget_borrowed(v_bs_513_, v_i_512_);
lean_inc(v_v_516_);
v___x_517_ = lp_competition_R24DotCostHarness_instFromJsonRoundCase_fromJson(v_v_516_);
if (lean_obj_tag(v___x_517_) == 0)
{
lean_object* v_a_518_; lean_object* v___x_520_; uint8_t v_isShared_521_; uint8_t v_isSharedCheck_525_; 
lean_dec_ref(v_bs_513_);
v_a_518_ = lean_ctor_get(v___x_517_, 0);
v_isSharedCheck_525_ = !lean_is_exclusive(v___x_517_);
if (v_isSharedCheck_525_ == 0)
{
v___x_520_ = v___x_517_;
v_isShared_521_ = v_isSharedCheck_525_;
goto v_resetjp_519_;
}
else
{
lean_inc(v_a_518_);
lean_dec(v___x_517_);
v___x_520_ = lean_box(0);
v_isShared_521_ = v_isSharedCheck_525_;
goto v_resetjp_519_;
}
v_resetjp_519_:
{
lean_object* v___x_523_; 
if (v_isShared_521_ == 0)
{
v___x_523_ = v___x_520_;
goto v_reusejp_522_;
}
else
{
lean_object* v_reuseFailAlloc_524_; 
v_reuseFailAlloc_524_ = lean_alloc_ctor(0, 1, 0);
lean_ctor_set(v_reuseFailAlloc_524_, 0, v_a_518_);
v___x_523_ = v_reuseFailAlloc_524_;
goto v_reusejp_522_;
}
v_reusejp_522_:
{
return v___x_523_;
}
}
}
else
{
lean_object* v_a_526_; lean_object* v___x_527_; lean_object* v_bs_x27_528_; size_t v___x_529_; size_t v___x_530_; lean_object* v___x_531_; 
v_a_526_ = lean_ctor_get(v___x_517_, 0);
lean_inc(v_a_526_);
lean_dec_ref_known(v___x_517_, 1);
v___x_527_ = lean_unsigned_to_nat(0u);
v_bs_x27_528_ = lean_array_uset(v_bs_513_, v_i_512_, v___x_527_);
v___x_529_ = ((size_t)1ULL);
v___x_530_ = lean_usize_add(v_i_512_, v___x_529_);
v___x_531_ = lean_array_uset(v_bs_x27_528_, v_i_512_, v_a_526_);
v_i_512_ = v___x_530_;
v_bs_513_ = v___x_531_;
goto _start;
}
}
}
}
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_mapMUnsafe_map___at___00Lean_Array_fromJson_x3f___at___00Lean_Json_getObjValAs_x3f___at___00R24DotCostHarness_instFromJsonPlan_fromJson_spec__1_spec__2_spec__4___boxed(lean_object* v_sz_533_, lean_object* v_i_534_, lean_object* v_bs_535_){
_start:
{
size_t v_sz_boxed_536_; size_t v_i_boxed_537_; lean_object* v_res_538_; 
v_sz_boxed_536_ = lean_unbox_usize(v_sz_533_);
lean_dec(v_sz_533_);
v_i_boxed_537_ = lean_unbox_usize(v_i_534_);
lean_dec(v_i_534_);
v_res_538_ = lp_competition___private_Init_Data_Array_Basic_0__Array_mapMUnsafe_map___at___00Lean_Array_fromJson_x3f___at___00Lean_Json_getObjValAs_x3f___at___00R24DotCostHarness_instFromJsonPlan_fromJson_spec__1_spec__2_spec__4(v_sz_boxed_536_, v_i_boxed_537_, v_bs_535_);
return v_res_538_;
}
}
LEAN_EXPORT lean_object* lp_competition_Lean_Array_fromJson_x3f___at___00Lean_Json_getObjValAs_x3f___at___00R24DotCostHarness_instFromJsonPlan_fromJson_spec__1_spec__2(lean_object* v_x_541_){
_start:
{
if (lean_obj_tag(v_x_541_) == 4)
{
lean_object* v_elems_542_; size_t v_sz_543_; size_t v___x_544_; lean_object* v___x_545_; 
v_elems_542_ = lean_ctor_get(v_x_541_, 0);
lean_inc_ref(v_elems_542_);
lean_dec_ref_known(v_x_541_, 1);
v_sz_543_ = lean_array_size(v_elems_542_);
v___x_544_ = ((size_t)0ULL);
v___x_545_ = lp_competition___private_Init_Data_Array_Basic_0__Array_mapMUnsafe_map___at___00Lean_Array_fromJson_x3f___at___00Lean_Json_getObjValAs_x3f___at___00R24DotCostHarness_instFromJsonPlan_fromJson_spec__1_spec__2_spec__4(v_sz_543_, v___x_544_, v_elems_542_);
return v___x_545_;
}
else
{
lean_object* v___x_546_; lean_object* v___x_547_; lean_object* v___x_548_; lean_object* v___x_549_; lean_object* v___x_550_; lean_object* v___x_551_; lean_object* v___x_552_; 
v___x_546_ = ((lean_object*)(lp_competition_Lean_Array_fromJson_x3f___at___00Lean_Json_getObjValAs_x3f___at___00R24DotCostHarness_instFromJsonPlan_fromJson_spec__1_spec__2___closed__0));
v___x_547_ = lean_unsigned_to_nat(80u);
v___x_548_ = l_Lean_Json_pretty(v_x_541_, v___x_547_);
v___x_549_ = lean_string_append(v___x_546_, v___x_548_);
lean_dec_ref(v___x_548_);
v___x_550_ = ((lean_object*)(lp_competition_Lean_Array_fromJson_x3f___at___00Lean_Json_getObjValAs_x3f___at___00R24DotCostHarness_instFromJsonPlan_fromJson_spec__1_spec__2___closed__1));
v___x_551_ = lean_string_append(v___x_549_, v___x_550_);
v___x_552_ = lean_alloc_ctor(0, 1, 0);
lean_ctor_set(v___x_552_, 0, v___x_551_);
return v___x_552_;
}
}
}
LEAN_EXPORT lean_object* lp_competition_Lean_Json_getObjValAs_x3f___at___00R24DotCostHarness_instFromJsonPlan_fromJson_spec__1(lean_object* v_j_553_, lean_object* v_k_554_){
_start:
{
lean_object* v___x_555_; lean_object* v___x_556_; 
v___x_555_ = l_Lean_Json_getObjValD(v_j_553_, v_k_554_);
v___x_556_ = lp_competition_Lean_Array_fromJson_x3f___at___00Lean_Json_getObjValAs_x3f___at___00R24DotCostHarness_instFromJsonPlan_fromJson_spec__1_spec__2(v___x_555_);
return v___x_556_;
}
}
LEAN_EXPORT lean_object* lp_competition_Lean_Json_getObjValAs_x3f___at___00R24DotCostHarness_instFromJsonPlan_fromJson_spec__1___boxed(lean_object* v_j_557_, lean_object* v_k_558_){
_start:
{
lean_object* v_res_559_; 
v_res_559_ = lp_competition_Lean_Json_getObjValAs_x3f___at___00R24DotCostHarness_instFromJsonPlan_fromJson_spec__1(v_j_557_, v_k_558_);
lean_dec_ref(v_k_558_);
return v_res_559_;
}
}
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_mapMUnsafe_map___at___00Lean_Array_fromJson_x3f___at___00Lean_Json_getObjValAs_x3f___at___00R24DotCostHarness_instFromJsonPlan_fromJson_spec__0_spec__0_spec__1(size_t v_sz_560_, size_t v_i_561_, lean_object* v_bs_562_){
_start:
{
uint8_t v___x_563_; 
v___x_563_ = lean_usize_dec_lt(v_i_561_, v_sz_560_);
if (v___x_563_ == 0)
{
lean_object* v___x_564_; 
v___x_564_ = lean_alloc_ctor(1, 1, 0);
lean_ctor_set(v___x_564_, 0, v_bs_562_);
return v___x_564_;
}
else
{
lean_object* v_v_565_; lean_object* v___x_566_; 
v_v_565_ = lean_array_uget_borrowed(v_bs_562_, v_i_561_);
lean_inc(v_v_565_);
v___x_566_ = lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson(v_v_565_);
if (lean_obj_tag(v___x_566_) == 0)
{
lean_object* v_a_567_; lean_object* v___x_569_; uint8_t v_isShared_570_; uint8_t v_isSharedCheck_574_; 
lean_dec_ref(v_bs_562_);
v_a_567_ = lean_ctor_get(v___x_566_, 0);
v_isSharedCheck_574_ = !lean_is_exclusive(v___x_566_);
if (v_isSharedCheck_574_ == 0)
{
v___x_569_ = v___x_566_;
v_isShared_570_ = v_isSharedCheck_574_;
goto v_resetjp_568_;
}
else
{
lean_inc(v_a_567_);
lean_dec(v___x_566_);
v___x_569_ = lean_box(0);
v_isShared_570_ = v_isSharedCheck_574_;
goto v_resetjp_568_;
}
v_resetjp_568_:
{
lean_object* v___x_572_; 
if (v_isShared_570_ == 0)
{
v___x_572_ = v___x_569_;
goto v_reusejp_571_;
}
else
{
lean_object* v_reuseFailAlloc_573_; 
v_reuseFailAlloc_573_ = lean_alloc_ctor(0, 1, 0);
lean_ctor_set(v_reuseFailAlloc_573_, 0, v_a_567_);
v___x_572_ = v_reuseFailAlloc_573_;
goto v_reusejp_571_;
}
v_reusejp_571_:
{
return v___x_572_;
}
}
}
else
{
lean_object* v_a_575_; lean_object* v___x_576_; lean_object* v_bs_x27_577_; size_t v___x_578_; size_t v___x_579_; lean_object* v___x_580_; 
v_a_575_ = lean_ctor_get(v___x_566_, 0);
lean_inc(v_a_575_);
lean_dec_ref_known(v___x_566_, 1);
v___x_576_ = lean_unsigned_to_nat(0u);
v_bs_x27_577_ = lean_array_uset(v_bs_562_, v_i_561_, v___x_576_);
v___x_578_ = ((size_t)1ULL);
v___x_579_ = lean_usize_add(v_i_561_, v___x_578_);
v___x_580_ = lean_array_uset(v_bs_x27_577_, v_i_561_, v_a_575_);
v_i_561_ = v___x_579_;
v_bs_562_ = v___x_580_;
goto _start;
}
}
}
}
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_mapMUnsafe_map___at___00Lean_Array_fromJson_x3f___at___00Lean_Json_getObjValAs_x3f___at___00R24DotCostHarness_instFromJsonPlan_fromJson_spec__0_spec__0_spec__1___boxed(lean_object* v_sz_582_, lean_object* v_i_583_, lean_object* v_bs_584_){
_start:
{
size_t v_sz_boxed_585_; size_t v_i_boxed_586_; lean_object* v_res_587_; 
v_sz_boxed_585_ = lean_unbox_usize(v_sz_582_);
lean_dec(v_sz_582_);
v_i_boxed_586_ = lean_unbox_usize(v_i_583_);
lean_dec(v_i_583_);
v_res_587_ = lp_competition___private_Init_Data_Array_Basic_0__Array_mapMUnsafe_map___at___00Lean_Array_fromJson_x3f___at___00Lean_Json_getObjValAs_x3f___at___00R24DotCostHarness_instFromJsonPlan_fromJson_spec__0_spec__0_spec__1(v_sz_boxed_585_, v_i_boxed_586_, v_bs_584_);
return v_res_587_;
}
}
LEAN_EXPORT lean_object* lp_competition_Lean_Array_fromJson_x3f___at___00Lean_Json_getObjValAs_x3f___at___00R24DotCostHarness_instFromJsonPlan_fromJson_spec__0_spec__0(lean_object* v_x_588_){
_start:
{
if (lean_obj_tag(v_x_588_) == 4)
{
lean_object* v_elems_589_; size_t v_sz_590_; size_t v___x_591_; lean_object* v___x_592_; 
v_elems_589_ = lean_ctor_get(v_x_588_, 0);
lean_inc_ref(v_elems_589_);
lean_dec_ref_known(v_x_588_, 1);
v_sz_590_ = lean_array_size(v_elems_589_);
v___x_591_ = ((size_t)0ULL);
v___x_592_ = lp_competition___private_Init_Data_Array_Basic_0__Array_mapMUnsafe_map___at___00Lean_Array_fromJson_x3f___at___00Lean_Json_getObjValAs_x3f___at___00R24DotCostHarness_instFromJsonPlan_fromJson_spec__0_spec__0_spec__1(v_sz_590_, v___x_591_, v_elems_589_);
return v___x_592_;
}
else
{
lean_object* v___x_593_; lean_object* v___x_594_; lean_object* v___x_595_; lean_object* v___x_596_; lean_object* v___x_597_; lean_object* v___x_598_; lean_object* v___x_599_; 
v___x_593_ = ((lean_object*)(lp_competition_Lean_Array_fromJson_x3f___at___00Lean_Json_getObjValAs_x3f___at___00R24DotCostHarness_instFromJsonPlan_fromJson_spec__1_spec__2___closed__0));
v___x_594_ = lean_unsigned_to_nat(80u);
v___x_595_ = l_Lean_Json_pretty(v_x_588_, v___x_594_);
v___x_596_ = lean_string_append(v___x_593_, v___x_595_);
lean_dec_ref(v___x_595_);
v___x_597_ = ((lean_object*)(lp_competition_Lean_Array_fromJson_x3f___at___00Lean_Json_getObjValAs_x3f___at___00R24DotCostHarness_instFromJsonPlan_fromJson_spec__1_spec__2___closed__1));
v___x_598_ = lean_string_append(v___x_596_, v___x_597_);
v___x_599_ = lean_alloc_ctor(0, 1, 0);
lean_ctor_set(v___x_599_, 0, v___x_598_);
return v___x_599_;
}
}
}
LEAN_EXPORT lean_object* lp_competition_Lean_Json_getObjValAs_x3f___at___00R24DotCostHarness_instFromJsonPlan_fromJson_spec__0(lean_object* v_j_600_, lean_object* v_k_601_){
_start:
{
lean_object* v___x_602_; lean_object* v___x_603_; 
v___x_602_ = l_Lean_Json_getObjValD(v_j_600_, v_k_601_);
v___x_603_ = lp_competition_Lean_Array_fromJson_x3f___at___00Lean_Json_getObjValAs_x3f___at___00R24DotCostHarness_instFromJsonPlan_fromJson_spec__0_spec__0(v___x_602_);
return v___x_603_;
}
}
LEAN_EXPORT lean_object* lp_competition_Lean_Json_getObjValAs_x3f___at___00R24DotCostHarness_instFromJsonPlan_fromJson_spec__0___boxed(lean_object* v_j_604_, lean_object* v_k_605_){
_start:
{
lean_object* v_res_606_; 
v_res_606_ = lp_competition_Lean_Json_getObjValAs_x3f___at___00R24DotCostHarness_instFromJsonPlan_fromJson_spec__0(v_j_604_, v_k_605_);
lean_dec_ref(v_k_605_);
return v_res_606_;
}
}
static lean_object* _init_lp_competition_R24DotCostHarness_instFromJsonPlan_fromJson___closed__3(void){
_start:
{
uint8_t v___x_612_; lean_object* v___x_613_; lean_object* v___x_614_; 
v___x_612_ = 1;
v___x_613_ = ((lean_object*)(lp_competition_R24DotCostHarness_instFromJsonPlan_fromJson___closed__2));
v___x_614_ = l_Lean_Name_toStringWithToken___at___00Lean_Name_toString_spec__0(v___x_613_, v___x_612_);
return v___x_614_;
}
}
static lean_object* _init_lp_competition_R24DotCostHarness_instFromJsonPlan_fromJson___closed__4(void){
_start:
{
lean_object* v___x_615_; lean_object* v___x_616_; lean_object* v___x_617_; 
v___x_615_ = ((lean_object*)(lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__5));
v___x_616_ = lean_obj_once(&lp_competition_R24DotCostHarness_instFromJsonPlan_fromJson___closed__3, &lp_competition_R24DotCostHarness_instFromJsonPlan_fromJson___closed__3_once, _init_lp_competition_R24DotCostHarness_instFromJsonPlan_fromJson___closed__3);
v___x_617_ = lean_string_append(v___x_616_, v___x_615_);
return v___x_617_;
}
}
static lean_object* _init_lp_competition_R24DotCostHarness_instFromJsonPlan_fromJson___closed__6(void){
_start:
{
uint8_t v___x_620_; lean_object* v___x_621_; lean_object* v___x_622_; 
v___x_620_ = 1;
v___x_621_ = ((lean_object*)(lp_competition_R24DotCostHarness_instFromJsonPlan_fromJson___closed__5));
v___x_622_ = l_Lean_Name_toStringWithToken___at___00Lean_Name_toString_spec__0(v___x_621_, v___x_620_);
return v___x_622_;
}
}
static lean_object* _init_lp_competition_R24DotCostHarness_instFromJsonPlan_fromJson___closed__7(void){
_start:
{
lean_object* v___x_623_; lean_object* v___x_624_; lean_object* v___x_625_; 
v___x_623_ = lean_obj_once(&lp_competition_R24DotCostHarness_instFromJsonPlan_fromJson___closed__6, &lp_competition_R24DotCostHarness_instFromJsonPlan_fromJson___closed__6_once, _init_lp_competition_R24DotCostHarness_instFromJsonPlan_fromJson___closed__6);
v___x_624_ = lean_obj_once(&lp_competition_R24DotCostHarness_instFromJsonPlan_fromJson___closed__4, &lp_competition_R24DotCostHarness_instFromJsonPlan_fromJson___closed__4_once, _init_lp_competition_R24DotCostHarness_instFromJsonPlan_fromJson___closed__4);
v___x_625_ = lean_string_append(v___x_624_, v___x_623_);
return v___x_625_;
}
}
static lean_object* _init_lp_competition_R24DotCostHarness_instFromJsonPlan_fromJson___closed__8(void){
_start:
{
lean_object* v___x_626_; lean_object* v___x_627_; lean_object* v___x_628_; 
v___x_626_ = ((lean_object*)(lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__10));
v___x_627_ = lean_obj_once(&lp_competition_R24DotCostHarness_instFromJsonPlan_fromJson___closed__7, &lp_competition_R24DotCostHarness_instFromJsonPlan_fromJson___closed__7_once, _init_lp_competition_R24DotCostHarness_instFromJsonPlan_fromJson___closed__7);
v___x_628_ = lean_string_append(v___x_627_, v___x_626_);
return v___x_628_;
}
}
static lean_object* _init_lp_competition_R24DotCostHarness_instFromJsonPlan_fromJson___closed__11(void){
_start:
{
uint8_t v___x_632_; lean_object* v___x_633_; lean_object* v___x_634_; 
v___x_632_ = 1;
v___x_633_ = ((lean_object*)(lp_competition_R24DotCostHarness_instFromJsonPlan_fromJson___closed__10));
v___x_634_ = l_Lean_Name_toStringWithToken___at___00Lean_Name_toString_spec__0(v___x_633_, v___x_632_);
return v___x_634_;
}
}
static lean_object* _init_lp_competition_R24DotCostHarness_instFromJsonPlan_fromJson___closed__12(void){
_start:
{
lean_object* v___x_635_; lean_object* v___x_636_; lean_object* v___x_637_; 
v___x_635_ = lean_obj_once(&lp_competition_R24DotCostHarness_instFromJsonPlan_fromJson___closed__11, &lp_competition_R24DotCostHarness_instFromJsonPlan_fromJson___closed__11_once, _init_lp_competition_R24DotCostHarness_instFromJsonPlan_fromJson___closed__11);
v___x_636_ = lean_obj_once(&lp_competition_R24DotCostHarness_instFromJsonPlan_fromJson___closed__4, &lp_competition_R24DotCostHarness_instFromJsonPlan_fromJson___closed__4_once, _init_lp_competition_R24DotCostHarness_instFromJsonPlan_fromJson___closed__4);
v___x_637_ = lean_string_append(v___x_636_, v___x_635_);
return v___x_637_;
}
}
static lean_object* _init_lp_competition_R24DotCostHarness_instFromJsonPlan_fromJson___closed__13(void){
_start:
{
lean_object* v___x_638_; lean_object* v___x_639_; lean_object* v___x_640_; 
v___x_638_ = ((lean_object*)(lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__10));
v___x_639_ = lean_obj_once(&lp_competition_R24DotCostHarness_instFromJsonPlan_fromJson___closed__12, &lp_competition_R24DotCostHarness_instFromJsonPlan_fromJson___closed__12_once, _init_lp_competition_R24DotCostHarness_instFromJsonPlan_fromJson___closed__12);
v___x_640_ = lean_string_append(v___x_639_, v___x_638_);
return v___x_640_;
}
}
LEAN_EXPORT lean_object* lp_competition_R24DotCostHarness_instFromJsonPlan_fromJson(lean_object* v_json_641_){
_start:
{
lean_object* v___x_642_; lean_object* v___x_643_; 
v___x_642_ = ((lean_object*)(lp_competition_R24DotCostHarness_instFromJsonPlan_fromJson___closed__0));
lean_inc(v_json_641_);
v___x_643_ = lp_competition_Lean_Json_getObjValAs_x3f___at___00R24DotCostHarness_instFromJsonPlan_fromJson_spec__0(v_json_641_, v___x_642_);
if (lean_obj_tag(v___x_643_) == 0)
{
lean_object* v_a_644_; lean_object* v___x_646_; uint8_t v_isShared_647_; uint8_t v_isSharedCheck_653_; 
lean_dec(v_json_641_);
v_a_644_ = lean_ctor_get(v___x_643_, 0);
v_isSharedCheck_653_ = !lean_is_exclusive(v___x_643_);
if (v_isSharedCheck_653_ == 0)
{
v___x_646_ = v___x_643_;
v_isShared_647_ = v_isSharedCheck_653_;
goto v_resetjp_645_;
}
else
{
lean_inc(v_a_644_);
lean_dec(v___x_643_);
v___x_646_ = lean_box(0);
v_isShared_647_ = v_isSharedCheck_653_;
goto v_resetjp_645_;
}
v_resetjp_645_:
{
lean_object* v___x_648_; lean_object* v___x_649_; lean_object* v___x_651_; 
v___x_648_ = lean_obj_once(&lp_competition_R24DotCostHarness_instFromJsonPlan_fromJson___closed__8, &lp_competition_R24DotCostHarness_instFromJsonPlan_fromJson___closed__8_once, _init_lp_competition_R24DotCostHarness_instFromJsonPlan_fromJson___closed__8);
v___x_649_ = lean_string_append(v___x_648_, v_a_644_);
lean_dec(v_a_644_);
if (v_isShared_647_ == 0)
{
lean_ctor_set(v___x_646_, 0, v___x_649_);
v___x_651_ = v___x_646_;
goto v_reusejp_650_;
}
else
{
lean_object* v_reuseFailAlloc_652_; 
v_reuseFailAlloc_652_ = lean_alloc_ctor(0, 1, 0);
lean_ctor_set(v_reuseFailAlloc_652_, 0, v___x_649_);
v___x_651_ = v_reuseFailAlloc_652_;
goto v_reusejp_650_;
}
v_reusejp_650_:
{
return v___x_651_;
}
}
}
else
{
if (lean_obj_tag(v___x_643_) == 0)
{
lean_object* v_a_654_; lean_object* v___x_656_; uint8_t v_isShared_657_; uint8_t v_isSharedCheck_661_; 
lean_dec(v_json_641_);
v_a_654_ = lean_ctor_get(v___x_643_, 0);
v_isSharedCheck_661_ = !lean_is_exclusive(v___x_643_);
if (v_isSharedCheck_661_ == 0)
{
v___x_656_ = v___x_643_;
v_isShared_657_ = v_isSharedCheck_661_;
goto v_resetjp_655_;
}
else
{
lean_inc(v_a_654_);
lean_dec(v___x_643_);
v___x_656_ = lean_box(0);
v_isShared_657_ = v_isSharedCheck_661_;
goto v_resetjp_655_;
}
v_resetjp_655_:
{
lean_object* v___x_659_; 
if (v_isShared_657_ == 0)
{
lean_ctor_set_tag(v___x_656_, 0);
v___x_659_ = v___x_656_;
goto v_reusejp_658_;
}
else
{
lean_object* v_reuseFailAlloc_660_; 
v_reuseFailAlloc_660_ = lean_alloc_ctor(0, 1, 0);
lean_ctor_set(v_reuseFailAlloc_660_, 0, v_a_654_);
v___x_659_ = v_reuseFailAlloc_660_;
goto v_reusejp_658_;
}
v_reusejp_658_:
{
return v___x_659_;
}
}
}
else
{
lean_object* v_a_662_; lean_object* v___x_663_; lean_object* v___x_664_; 
v_a_662_ = lean_ctor_get(v___x_643_, 0);
lean_inc(v_a_662_);
lean_dec_ref_known(v___x_643_, 1);
v___x_663_ = ((lean_object*)(lp_competition_R24DotCostHarness_instFromJsonPlan_fromJson___closed__9));
v___x_664_ = lp_competition_Lean_Json_getObjValAs_x3f___at___00R24DotCostHarness_instFromJsonPlan_fromJson_spec__1(v_json_641_, v___x_663_);
if (lean_obj_tag(v___x_664_) == 0)
{
lean_object* v_a_665_; lean_object* v___x_667_; uint8_t v_isShared_668_; uint8_t v_isSharedCheck_674_; 
lean_dec(v_a_662_);
v_a_665_ = lean_ctor_get(v___x_664_, 0);
v_isSharedCheck_674_ = !lean_is_exclusive(v___x_664_);
if (v_isSharedCheck_674_ == 0)
{
v___x_667_ = v___x_664_;
v_isShared_668_ = v_isSharedCheck_674_;
goto v_resetjp_666_;
}
else
{
lean_inc(v_a_665_);
lean_dec(v___x_664_);
v___x_667_ = lean_box(0);
v_isShared_668_ = v_isSharedCheck_674_;
goto v_resetjp_666_;
}
v_resetjp_666_:
{
lean_object* v___x_669_; lean_object* v___x_670_; lean_object* v___x_672_; 
v___x_669_ = lean_obj_once(&lp_competition_R24DotCostHarness_instFromJsonPlan_fromJson___closed__13, &lp_competition_R24DotCostHarness_instFromJsonPlan_fromJson___closed__13_once, _init_lp_competition_R24DotCostHarness_instFromJsonPlan_fromJson___closed__13);
v___x_670_ = lean_string_append(v___x_669_, v_a_665_);
lean_dec(v_a_665_);
if (v_isShared_668_ == 0)
{
lean_ctor_set(v___x_667_, 0, v___x_670_);
v___x_672_ = v___x_667_;
goto v_reusejp_671_;
}
else
{
lean_object* v_reuseFailAlloc_673_; 
v_reuseFailAlloc_673_ = lean_alloc_ctor(0, 1, 0);
lean_ctor_set(v_reuseFailAlloc_673_, 0, v___x_670_);
v___x_672_ = v_reuseFailAlloc_673_;
goto v_reusejp_671_;
}
v_reusejp_671_:
{
return v___x_672_;
}
}
}
else
{
if (lean_obj_tag(v___x_664_) == 0)
{
lean_object* v_a_675_; lean_object* v___x_677_; uint8_t v_isShared_678_; uint8_t v_isSharedCheck_682_; 
lean_dec(v_a_662_);
v_a_675_ = lean_ctor_get(v___x_664_, 0);
v_isSharedCheck_682_ = !lean_is_exclusive(v___x_664_);
if (v_isSharedCheck_682_ == 0)
{
v___x_677_ = v___x_664_;
v_isShared_678_ = v_isSharedCheck_682_;
goto v_resetjp_676_;
}
else
{
lean_inc(v_a_675_);
lean_dec(v___x_664_);
v___x_677_ = lean_box(0);
v_isShared_678_ = v_isSharedCheck_682_;
goto v_resetjp_676_;
}
v_resetjp_676_:
{
lean_object* v___x_680_; 
if (v_isShared_678_ == 0)
{
lean_ctor_set_tag(v___x_677_, 0);
v___x_680_ = v___x_677_;
goto v_reusejp_679_;
}
else
{
lean_object* v_reuseFailAlloc_681_; 
v_reuseFailAlloc_681_ = lean_alloc_ctor(0, 1, 0);
lean_ctor_set(v_reuseFailAlloc_681_, 0, v_a_675_);
v___x_680_ = v_reuseFailAlloc_681_;
goto v_reusejp_679_;
}
v_reusejp_679_:
{
return v___x_680_;
}
}
}
else
{
lean_object* v_a_683_; lean_object* v___x_685_; uint8_t v_isShared_686_; uint8_t v_isSharedCheck_691_; 
v_a_683_ = lean_ctor_get(v___x_664_, 0);
v_isSharedCheck_691_ = !lean_is_exclusive(v___x_664_);
if (v_isSharedCheck_691_ == 0)
{
v___x_685_ = v___x_664_;
v_isShared_686_ = v_isSharedCheck_691_;
goto v_resetjp_684_;
}
else
{
lean_inc(v_a_683_);
lean_dec(v___x_664_);
v___x_685_ = lean_box(0);
v_isShared_686_ = v_isSharedCheck_691_;
goto v_resetjp_684_;
}
v_resetjp_684_:
{
lean_object* v___x_687_; lean_object* v___x_689_; 
v___x_687_ = lean_alloc_ctor(0, 2, 0);
lean_ctor_set(v___x_687_, 0, v_a_662_);
lean_ctor_set(v___x_687_, 1, v_a_683_);
if (v_isShared_686_ == 0)
{
lean_ctor_set(v___x_685_, 0, v___x_687_);
v___x_689_ = v___x_685_;
goto v_reusejp_688_;
}
else
{
lean_object* v_reuseFailAlloc_690_; 
v_reuseFailAlloc_690_ = lean_alloc_ctor(1, 1, 0);
lean_ctor_set(v_reuseFailAlloc_690_, 0, v___x_687_);
v___x_689_ = v_reuseFailAlloc_690_;
goto v_reusejp_688_;
}
v_reusejp_688_:
{
return v___x_689_;
}
}
}
}
}
}
}
}
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_mapMUnsafe_map___at___00R24DotCostHarness_words_spec__0(size_t v_sz_694_, size_t v_i_695_, lean_object* v_bs_696_){
_start:
{
uint8_t v___x_697_; 
v___x_697_ = lean_usize_dec_lt(v_i_695_, v_sz_694_);
if (v___x_697_ == 0)
{
return v_bs_696_;
}
else
{
lean_object* v_v_698_; lean_object* v___x_699_; lean_object* v_bs_x27_700_; uint32_t v___x_701_; size_t v___x_702_; size_t v___x_703_; lean_object* v___x_704_; lean_object* v___x_705_; 
v_v_698_ = lean_array_uget(v_bs_696_, v_i_695_);
v___x_699_ = lean_unsigned_to_nat(0u);
v_bs_x27_700_ = lean_array_uset(v_bs_696_, v_i_695_, v___x_699_);
v___x_701_ = lean_uint32_of_nat(v_v_698_);
lean_dec(v_v_698_);
v___x_702_ = ((size_t)1ULL);
v___x_703_ = lean_usize_add(v_i_695_, v___x_702_);
v___x_704_ = lean_box_uint32(v___x_701_);
v___x_705_ = lean_array_uset(v_bs_x27_700_, v_i_695_, v___x_704_);
v_i_695_ = v___x_703_;
v_bs_696_ = v___x_705_;
goto _start;
}
}
}
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_mapMUnsafe_map___at___00R24DotCostHarness_words_spec__0___boxed(lean_object* v_sz_707_, lean_object* v_i_708_, lean_object* v_bs_709_){
_start:
{
size_t v_sz_boxed_710_; size_t v_i_boxed_711_; lean_object* v_res_712_; 
v_sz_boxed_710_ = lean_unbox_usize(v_sz_707_);
lean_dec(v_sz_707_);
v_i_boxed_711_ = lean_unbox_usize(v_i_708_);
lean_dec(v_i_708_);
v_res_712_ = lp_competition___private_Init_Data_Array_Basic_0__Array_mapMUnsafe_map___at___00R24DotCostHarness_words_spec__0(v_sz_boxed_710_, v_i_boxed_711_, v_bs_709_);
return v_res_712_;
}
}
LEAN_EXPORT lean_object* lp_competition_R24DotCostHarness_words(lean_object* v_xs_713_){
_start:
{
size_t v_sz_714_; size_t v___x_715_; lean_object* v___x_716_; 
v_sz_714_ = lean_array_size(v_xs_713_);
v___x_715_ = ((size_t)0ULL);
v___x_716_ = lp_competition___private_Init_Data_Array_Basic_0__Array_mapMUnsafe_map___at___00R24DotCostHarness_words_spec__0(v_sz_714_, v___x_715_, v_xs_713_);
return v___x_716_;
}
}
LEAN_EXPORT uint8_t lp_competition___private_Init_Data_Array_Basic_0__Array_anyMUnsafe_any___at___00R24DotCostHarness_supported_spec__0(lean_object* v___x_717_, lean_object* v___x_718_, lean_object* v_as_719_, size_t v_i_720_, size_t v_stop_721_){
_start:
{
uint8_t v___x_722_; 
v___x_722_ = lean_usize_dec_eq(v_i_720_, v_stop_721_);
if (v___x_722_ == 0)
{
uint8_t v___x_723_; uint8_t v___x_724_; uint8_t v___y_726_; lean_object* v___x_730_; uint32_t v___x_731_; uint32_t v___x_732_; uint32_t v___x_733_; uint32_t v___x_734_; uint32_t v___x_735_; uint8_t v___x_736_; 
v___x_723_ = lean_nat_dec_eq(v___x_717_, v___x_718_);
v___x_724_ = 1;
v___x_730_ = lean_array_uget_borrowed(v_as_719_, v_i_720_);
v___x_731_ = 23;
v___x_732_ = lean_unbox_uint32(v___x_730_);
v___x_733_ = lean_uint32_shift_right(v___x_732_, v___x_731_);
v___x_734_ = 255;
v___x_735_ = lean_uint32_land(v___x_733_, v___x_734_);
v___x_736_ = lean_uint32_dec_eq(v___x_735_, v___x_734_);
if (v___x_736_ == 0)
{
if (v___x_723_ == 0)
{
v___y_726_ = v___x_723_;
goto v___jp_725_;
}
else
{
v___y_726_ = v___x_736_;
goto v___jp_725_;
}
}
else
{
v___y_726_ = v___x_723_;
goto v___jp_725_;
}
v___jp_725_:
{
if (v___y_726_ == 0)
{
size_t v___x_727_; size_t v___x_728_; 
v___x_727_ = ((size_t)1ULL);
v___x_728_ = lean_usize_add(v_i_720_, v___x_727_);
v_i_720_ = v___x_728_;
goto _start;
}
else
{
return v___x_724_;
}
}
}
else
{
uint8_t v___x_737_; 
v___x_737_ = 0;
return v___x_737_;
}
}
}
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_anyMUnsafe_any___at___00R24DotCostHarness_supported_spec__0___boxed(lean_object* v___x_738_, lean_object* v___x_739_, lean_object* v_as_740_, lean_object* v_i_741_, lean_object* v_stop_742_){
_start:
{
size_t v_i_boxed_743_; size_t v_stop_boxed_744_; uint8_t v_res_745_; lean_object* v_r_746_; 
v_i_boxed_743_ = lean_unbox_usize(v_i_741_);
lean_dec(v_i_741_);
v_stop_boxed_744_ = lean_unbox_usize(v_stop_742_);
lean_dec(v_stop_742_);
v_res_745_ = lp_competition___private_Init_Data_Array_Basic_0__Array_anyMUnsafe_any___at___00R24DotCostHarness_supported_spec__0(v___x_738_, v___x_739_, v_as_740_, v_i_boxed_743_, v_stop_boxed_744_);
lean_dec_ref(v_as_740_);
lean_dec(v___x_739_);
lean_dec(v___x_738_);
v_r_746_ = lean_box(v_res_745_);
return v_r_746_;
}
}
LEAN_EXPORT uint8_t lp_competition___private_Init_Data_Array_Basic_0__Array_anyMUnsafe_any___at___00R24DotCostHarness_supported_spec__1(lean_object* v___x_747_, lean_object* v___x_748_, lean_object* v_as_749_, size_t v_i_750_, size_t v_stop_751_){
_start:
{
uint8_t v___x_752_; 
v___x_752_ = lean_usize_dec_eq(v_i_750_, v_stop_751_);
if (v___x_752_ == 0)
{
uint8_t v___x_753_; uint8_t v___y_755_; lean_object* v___x_759_; uint32_t v___x_760_; uint32_t v___x_761_; uint32_t v___x_762_; uint32_t v___x_763_; uint32_t v___x_764_; uint8_t v___x_765_; 
v___x_753_ = 1;
v___x_759_ = lean_array_uget_borrowed(v_as_749_, v_i_750_);
v___x_760_ = 23;
v___x_761_ = lean_unbox_uint32(v___x_759_);
v___x_762_ = lean_uint32_shift_right(v___x_761_, v___x_760_);
v___x_763_ = 255;
v___x_764_ = lean_uint32_land(v___x_762_, v___x_763_);
v___x_765_ = lean_uint32_dec_eq(v___x_764_, v___x_763_);
if (v___x_765_ == 0)
{
v___y_755_ = v___x_765_;
goto v___jp_754_;
}
else
{
uint8_t v___x_766_; 
v___x_766_ = lean_nat_dec_eq(v___x_747_, v___x_748_);
v___y_755_ = v___x_766_;
goto v___jp_754_;
}
v___jp_754_:
{
if (v___y_755_ == 0)
{
size_t v___x_756_; size_t v___x_757_; 
v___x_756_ = ((size_t)1ULL);
v___x_757_ = lean_usize_add(v_i_750_, v___x_756_);
v_i_750_ = v___x_757_;
goto _start;
}
else
{
return v___x_753_;
}
}
}
else
{
uint8_t v___x_767_; 
v___x_767_ = 0;
return v___x_767_;
}
}
}
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_anyMUnsafe_any___at___00R24DotCostHarness_supported_spec__1___boxed(lean_object* v___x_768_, lean_object* v___x_769_, lean_object* v_as_770_, lean_object* v_i_771_, lean_object* v_stop_772_){
_start:
{
size_t v_i_boxed_773_; size_t v_stop_boxed_774_; uint8_t v_res_775_; lean_object* v_r_776_; 
v_i_boxed_773_ = lean_unbox_usize(v_i_771_);
lean_dec(v_i_771_);
v_stop_boxed_774_ = lean_unbox_usize(v_stop_772_);
lean_dec(v_stop_772_);
v_res_775_ = lp_competition___private_Init_Data_Array_Basic_0__Array_anyMUnsafe_any___at___00R24DotCostHarness_supported_spec__1(v___x_768_, v___x_769_, v_as_770_, v_i_boxed_773_, v_stop_boxed_774_);
lean_dec_ref(v_as_770_);
lean_dec(v___x_769_);
lean_dec(v___x_768_);
v_r_776_ = lean_box(v_res_775_);
return v_r_776_;
}
}
LEAN_EXPORT uint8_t lp_competition_R24DotCostHarness_supported(lean_object* v_a_777_, lean_object* v_b_778_){
_start:
{
lean_object* v___x_779_; lean_object* v___x_780_; uint8_t v___x_781_; 
v___x_779_ = lean_array_get_size(v_a_777_);
v___x_780_ = lean_unsigned_to_nat(0u);
v___x_781_ = lean_nat_dec_eq(v___x_779_, v___x_780_);
if (v___x_781_ == 0)
{
lean_object* v___x_782_; uint8_t v___x_783_; 
v___x_782_ = lean_array_get_size(v_b_778_);
v___x_783_ = lean_nat_dec_eq(v___x_779_, v___x_782_);
if (v___x_783_ == 0)
{
return v___x_783_;
}
else
{
uint8_t v___x_789_; 
v___x_789_ = lean_nat_dec_lt(v___x_780_, v___x_779_);
if (v___x_789_ == 0)
{
goto v___jp_784_;
}
else
{
if (v___x_789_ == 0)
{
goto v___jp_784_;
}
else
{
size_t v___x_790_; size_t v___x_791_; uint8_t v___x_792_; 
v___x_790_ = ((size_t)0ULL);
v___x_791_ = lean_usize_of_nat(v___x_779_);
v___x_792_ = lp_competition___private_Init_Data_Array_Basic_0__Array_anyMUnsafe_any___at___00R24DotCostHarness_supported_spec__1(v___x_779_, v___x_782_, v_a_777_, v___x_790_, v___x_791_);
if (v___x_792_ == 0)
{
goto v___jp_784_;
}
else
{
return v___x_781_;
}
}
}
}
v___jp_784_:
{
uint8_t v___x_785_; 
v___x_785_ = lean_nat_dec_lt(v___x_780_, v___x_782_);
if (v___x_785_ == 0)
{
return v___x_783_;
}
else
{
if (v___x_785_ == 0)
{
return v___x_783_;
}
else
{
size_t v___x_786_; size_t v___x_787_; uint8_t v___x_788_; 
v___x_786_ = ((size_t)0ULL);
v___x_787_ = lean_usize_of_nat(v___x_782_);
v___x_788_ = lp_competition___private_Init_Data_Array_Basic_0__Array_anyMUnsafe_any___at___00R24DotCostHarness_supported_spec__0(v___x_779_, v___x_782_, v_b_778_, v___x_786_, v___x_787_);
if (v___x_788_ == 0)
{
return v___x_783_;
}
else
{
return v___x_781_;
}
}
}
}
}
else
{
uint8_t v___x_793_; 
v___x_793_ = 0;
return v___x_793_;
}
}
}
LEAN_EXPORT lean_object* lp_competition_R24DotCostHarness_supported___boxed(lean_object* v_a_794_, lean_object* v_b_795_){
_start:
{
uint8_t v_res_796_; lean_object* v_r_797_; 
v_res_796_ = lp_competition_R24DotCostHarness_supported(v_a_794_, v_b_795_);
lean_dec_ref(v_b_795_);
lean_dec_ref(v_a_794_);
v_r_797_ = lean_box(v_res_796_);
return v_r_797_;
}
}
LEAN_EXPORT lean_object* lp_competition_R24DotCostHarness_repeats(lean_object* v_macs_798_, lean_object* v_n_799_){
_start:
{
lean_object* v___x_800_; lean_object* v___y_802_; uint8_t v___x_807_; 
v___x_800_ = lean_unsigned_to_nat(1u);
v___x_807_ = lean_nat_dec_le(v___x_800_, v_n_799_);
if (v___x_807_ == 0)
{
v___y_802_ = v___x_800_;
goto v___jp_801_;
}
else
{
v___y_802_ = v_n_799_;
goto v___jp_801_;
}
v___jp_801_:
{
lean_object* v___x_803_; lean_object* v___x_804_; lean_object* v___x_805_; uint8_t v___x_806_; 
v___x_803_ = lean_nat_add(v_macs_798_, v___y_802_);
v___x_804_ = lean_nat_sub(v___x_803_, v___x_800_);
lean_dec(v___x_803_);
v___x_805_ = lean_nat_div(v___x_804_, v___y_802_);
lean_dec(v___x_804_);
v___x_806_ = lean_nat_dec_le(v___x_800_, v___x_805_);
if (v___x_806_ == 0)
{
lean_dec(v___x_805_);
return v___x_800_;
}
else
{
return v___x_805_;
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_R24DotCostHarness_repeats___boxed(lean_object* v_macs_808_, lean_object* v_n_809_){
_start:
{
lean_object* v_res_810_; 
v_res_810_ = lp_competition_R24DotCostHarness_repeats(v_macs_808_, v_n_809_);
lean_dec(v_n_809_);
lean_dec(v_macs_808_);
return v_res_810_;
}
}
LEAN_EXPORT uint32_t lp_competition_R24DotCostHarness_seed(lean_object* v_trial_811_){
_start:
{
lean_object* v___x_812_; lean_object* v___x_813_; lean_object* v___x_814_; lean_object* v___x_815_; uint32_t v___x_816_; 
v___x_812_ = lean_unsigned_to_nat(2654435769u);
v___x_813_ = lean_unsigned_to_nat(1664525u);
v___x_814_ = lean_nat_mul(v___x_813_, v_trial_811_);
v___x_815_ = lean_nat_add(v___x_812_, v___x_814_);
lean_dec(v___x_814_);
v___x_816_ = lean_uint32_of_nat(v___x_815_);
lean_dec(v___x_815_);
return v___x_816_;
}
}
LEAN_EXPORT lean_object* lp_competition_R24DotCostHarness_seed___boxed(lean_object* v_trial_817_){
_start:
{
uint32_t v_res_818_; lean_object* v_r_819_; 
v_res_818_ = lp_competition_R24DotCostHarness_seed(v_trial_817_);
lean_dec(v_trial_817_);
v_r_819_ = lean_box_uint32(v_res_818_);
return v_r_819_;
}
}
LEAN_EXPORT uint32_t lp_competition_R24DotCostHarness_sinkExpected(uint32_t v_s_820_, uint32_t v_expected_821_, lean_object* v_iters_822_){
_start:
{
uint32_t v___x_823_; uint32_t v___x_824_; uint32_t v___x_825_; 
v___x_823_ = lean_uint32_of_nat(v_iters_822_);
v___x_824_ = lean_uint32_mul(v___x_823_, v_expected_821_);
v___x_825_ = lean_uint32_add(v_s_820_, v___x_824_);
return v___x_825_;
}
}
LEAN_EXPORT lean_object* lp_competition_R24DotCostHarness_sinkExpected___boxed(lean_object* v_s_826_, lean_object* v_expected_827_, lean_object* v_iters_828_){
_start:
{
uint32_t v_s_boxed_829_; uint32_t v_expected_boxed_830_; uint32_t v_res_831_; lean_object* v_r_832_; 
v_s_boxed_829_ = lean_unbox_uint32(v_s_826_);
lean_dec(v_s_826_);
v_expected_boxed_830_ = lean_unbox_uint32(v_expected_827_);
lean_dec(v_expected_827_);
v_res_831_ = lp_competition_R24DotCostHarness_sinkExpected(v_s_boxed_829_, v_expected_boxed_830_, v_iters_828_);
lean_dec(v_iters_828_);
v_r_832_ = lean_box_uint32(v_res_831_);
return v_r_832_;
}
}
LEAN_EXPORT lean_object* lp_competition_R24DotCostHarness_checkWord(lean_object* v_name_835_, lean_object* v_stage_836_, uint32_t v_got_837_, uint32_t v_expected_838_){
_start:
{
uint8_t v___x_840_; 
v___x_840_ = lean_uint32_dec_eq(v_got_837_, v_expected_838_);
if (v___x_840_ == 0)
{
lean_object* v___x_841_; lean_object* v___x_842_; lean_object* v___x_843_; lean_object* v___x_844_; lean_object* v___x_845_; lean_object* v___x_846_; lean_object* v___x_847_; lean_object* v___x_848_; lean_object* v___x_849_; lean_object* v___x_850_; lean_object* v___x_851_; lean_object* v___x_852_; lean_object* v___x_853_; lean_object* v___x_854_; lean_object* v___x_855_; 
v___x_841_ = ((lean_object*)(lp_competition_R24DotCostHarness_instFromJsonDotCase_fromJson___closed__10));
v___x_842_ = lean_string_append(v_name_835_, v___x_841_);
v___x_843_ = lean_string_append(v___x_842_, v_stage_836_);
v___x_844_ = ((lean_object*)(lp_competition_R24DotCostHarness_checkWord___closed__0));
v___x_845_ = lean_string_append(v___x_843_, v___x_844_);
v___x_846_ = lean_uint32_to_nat(v_got_837_);
v___x_847_ = l_Nat_reprFast(v___x_846_);
v___x_848_ = lean_string_append(v___x_845_, v___x_847_);
lean_dec_ref(v___x_847_);
v___x_849_ = ((lean_object*)(lp_competition_R24DotCostHarness_checkWord___closed__1));
v___x_850_ = lean_string_append(v___x_848_, v___x_849_);
v___x_851_ = lean_uint32_to_nat(v_expected_838_);
v___x_852_ = l_Nat_reprFast(v___x_851_);
v___x_853_ = lean_string_append(v___x_850_, v___x_852_);
lean_dec_ref(v___x_852_);
v___x_854_ = lean_alloc_ctor(18, 1, 0);
lean_ctor_set(v___x_854_, 0, v___x_853_);
v___x_855_ = lean_alloc_ctor(1, 1, 0);
lean_ctor_set(v___x_855_, 0, v___x_854_);
return v___x_855_;
}
else
{
lean_object* v___x_856_; lean_object* v___x_857_; 
lean_dec_ref(v_name_835_);
v___x_856_ = lean_box(0);
v___x_857_ = lean_alloc_ctor(0, 1, 0);
lean_ctor_set(v___x_857_, 0, v___x_856_);
return v___x_857_;
}
}
}
LEAN_EXPORT lean_object* lp_competition_R24DotCostHarness_checkWord___boxed(lean_object* v_name_858_, lean_object* v_stage_859_, lean_object* v_got_860_, lean_object* v_expected_861_, lean_object* v_a_862_){
_start:
{
uint32_t v_got_boxed_863_; uint32_t v_expected_boxed_864_; lean_object* v_res_865_; 
v_got_boxed_863_ = lean_unbox_uint32(v_got_860_);
lean_dec(v_got_860_);
v_expected_boxed_864_ = lean_unbox_uint32(v_expected_861_);
lean_dec(v_expected_861_);
v_res_865_ = lp_competition_R24DotCostHarness_checkWord(v_name_858_, v_stage_859_, v_got_boxed_863_, v_expected_boxed_864_);
lean_dec_ref(v_stage_859_);
return v_res_865_;
}
}
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotCostHarness_emit_spec__0(lean_object* v_c_868_, lean_object* v_variant_869_, lean_object* v_boundary_870_, lean_object* v_as_871_, size_t v_sz_872_, size_t v_i_873_, uint32_t v_b_874_){
_start:
{
uint8_t v___x_876_; 
v___x_876_ = lean_usize_dec_lt(v_i_873_, v_sz_872_);
if (v___x_876_ == 0)
{
lean_object* v___x_877_; lean_object* v___x_878_; 
v___x_877_ = lean_box_uint32(v_b_874_);
v___x_878_ = lean_alloc_ctor(0, 1, 0);
lean_ctor_set(v___x_878_, 0, v___x_877_);
return v___x_878_;
}
else
{
lean_object* v_name_879_; lean_object* v_group_880_; lean_object* v_a_881_; lean_object* v_trial_882_; lean_object* v_n_883_; lean_object* v_iters_884_; lean_object* v_ns_885_; uint32_t v_sink_886_; uint32_t v_expectedSink_887_; uint32_t v_keepWord_888_; lean_object* v___x_889_; lean_object* v___x_890_; lean_object* v___x_891_; lean_object* v___x_892_; lean_object* v___x_893_; lean_object* v___x_894_; lean_object* v___x_895_; lean_object* v___x_896_; lean_object* v___x_897_; lean_object* v___x_898_; lean_object* v___x_899_; lean_object* v___x_900_; lean_object* v___x_901_; lean_object* v___x_902_; lean_object* v___x_903_; lean_object* v___x_904_; lean_object* v___x_905_; lean_object* v___x_906_; lean_object* v___x_907_; lean_object* v___x_908_; lean_object* v___x_909_; lean_object* v___x_910_; lean_object* v___x_911_; lean_object* v___x_912_; lean_object* v___x_913_; lean_object* v___x_914_; lean_object* v___x_915_; lean_object* v___x_916_; lean_object* v___x_917_; lean_object* v___x_918_; lean_object* v___x_919_; lean_object* v___x_920_; lean_object* v___x_921_; lean_object* v___x_922_; lean_object* v___x_923_; lean_object* v___x_924_; lean_object* v___x_925_; lean_object* v___x_926_; 
v_name_879_ = lean_ctor_get(v_c_868_, 0);
v_group_880_ = lean_ctor_get(v_c_868_, 1);
v_a_881_ = lean_array_uget_borrowed(v_as_871_, v_i_873_);
v_trial_882_ = lean_ctor_get(v_a_881_, 0);
v_n_883_ = lean_ctor_get(v_a_881_, 1);
v_iters_884_ = lean_ctor_get(v_a_881_, 2);
v_ns_885_ = lean_ctor_get(v_a_881_, 3);
v_sink_886_ = lean_ctor_get_uint32(v_a_881_, sizeof(void*)*4);
v_expectedSink_887_ = lean_ctor_get_uint32(v_a_881_, sizeof(void*)*4 + 4);
v_keepWord_888_ = lean_ctor_get_uint32(v_a_881_, sizeof(void*)*4 + 8);
v___x_889_ = ((lean_object*)(lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotCostHarness_emit_spec__0___closed__0));
v___x_890_ = lean_string_append(v___x_889_, v_name_879_);
v___x_891_ = ((lean_object*)(lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotCostHarness_emit_spec__0___closed__1));
v___x_892_ = lean_string_append(v___x_890_, v___x_891_);
v___x_893_ = lean_string_append(v___x_892_, v_group_880_);
v___x_894_ = lean_string_append(v___x_893_, v___x_891_);
v___x_895_ = lean_string_append(v___x_894_, v_variant_869_);
v___x_896_ = lean_string_append(v___x_895_, v___x_891_);
v___x_897_ = lean_string_append(v___x_896_, v_boundary_870_);
v___x_898_ = lean_string_append(v___x_897_, v___x_891_);
lean_inc(v_trial_882_);
v___x_899_ = l_Nat_reprFast(v_trial_882_);
v___x_900_ = lean_string_append(v___x_898_, v___x_899_);
lean_dec_ref(v___x_899_);
v___x_901_ = lean_string_append(v___x_900_, v___x_891_);
lean_inc(v_n_883_);
v___x_902_ = l_Nat_reprFast(v_n_883_);
v___x_903_ = lean_string_append(v___x_901_, v___x_902_);
lean_dec_ref(v___x_902_);
v___x_904_ = lean_string_append(v___x_903_, v___x_891_);
lean_inc(v_iters_884_);
v___x_905_ = l_Nat_reprFast(v_iters_884_);
v___x_906_ = lean_string_append(v___x_904_, v___x_905_);
lean_dec_ref(v___x_905_);
v___x_907_ = lean_string_append(v___x_906_, v___x_891_);
v___x_908_ = lean_nat_mul(v_n_883_, v_iters_884_);
v___x_909_ = l_Nat_reprFast(v___x_908_);
v___x_910_ = lean_string_append(v___x_907_, v___x_909_);
lean_dec_ref(v___x_909_);
v___x_911_ = lean_string_append(v___x_910_, v___x_891_);
lean_inc(v_ns_885_);
v___x_912_ = l_Nat_reprFast(v_ns_885_);
v___x_913_ = lean_string_append(v___x_911_, v___x_912_);
lean_dec_ref(v___x_912_);
v___x_914_ = lean_string_append(v___x_913_, v___x_891_);
v___x_915_ = lean_uint32_to_nat(v_sink_886_);
v___x_916_ = l_Nat_reprFast(v___x_915_);
v___x_917_ = lean_string_append(v___x_914_, v___x_916_);
lean_dec_ref(v___x_916_);
v___x_918_ = lean_string_append(v___x_917_, v___x_891_);
v___x_919_ = lean_uint32_to_nat(v_expectedSink_887_);
v___x_920_ = l_Nat_reprFast(v___x_919_);
v___x_921_ = lean_string_append(v___x_918_, v___x_920_);
lean_dec_ref(v___x_920_);
v___x_922_ = lean_string_append(v___x_921_, v___x_891_);
v___x_923_ = lean_uint32_to_nat(v_keepWord_888_);
v___x_924_ = l_Nat_reprFast(v___x_923_);
v___x_925_ = lean_string_append(v___x_922_, v___x_924_);
lean_dec_ref(v___x_924_);
v___x_926_ = lp_batteries_IO_println___at___00Batteries_Tactic_Lint_lintCore_spec__4(v___x_925_);
if (lean_obj_tag(v___x_926_) == 0)
{
size_t v___x_927_; size_t v___x_928_; 
lean_dec_ref_known(v___x_926_, 1);
v___x_927_ = ((size_t)1ULL);
v___x_928_ = lean_usize_add(v_i_873_, v___x_927_);
v_i_873_ = v___x_928_;
v_b_874_ = v_keepWord_888_;
goto _start;
}
else
{
lean_object* v_a_930_; lean_object* v___x_932_; uint8_t v_isShared_933_; uint8_t v_isSharedCheck_937_; 
v_a_930_ = lean_ctor_get(v___x_926_, 0);
v_isSharedCheck_937_ = !lean_is_exclusive(v___x_926_);
if (v_isSharedCheck_937_ == 0)
{
v___x_932_ = v___x_926_;
v_isShared_933_ = v_isSharedCheck_937_;
goto v_resetjp_931_;
}
else
{
lean_inc(v_a_930_);
lean_dec(v___x_926_);
v___x_932_ = lean_box(0);
v_isShared_933_ = v_isSharedCheck_937_;
goto v_resetjp_931_;
}
v_resetjp_931_:
{
lean_object* v___x_935_; 
if (v_isShared_933_ == 0)
{
v___x_935_ = v___x_932_;
goto v_reusejp_934_;
}
else
{
lean_object* v_reuseFailAlloc_936_; 
v_reuseFailAlloc_936_ = lean_alloc_ctor(1, 1, 0);
lean_ctor_set(v_reuseFailAlloc_936_, 0, v_a_930_);
v___x_935_ = v_reuseFailAlloc_936_;
goto v_reusejp_934_;
}
v_reusejp_934_:
{
return v___x_935_;
}
}
}
}
}
}
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotCostHarness_emit_spec__0___boxed(lean_object* v_c_938_, lean_object* v_variant_939_, lean_object* v_boundary_940_, lean_object* v_as_941_, lean_object* v_sz_942_, lean_object* v_i_943_, lean_object* v_b_944_, lean_object* v___y_945_){
_start:
{
size_t v_sz_boxed_946_; size_t v_i_boxed_947_; uint32_t v_b_boxed_948_; lean_object* v_res_949_; 
v_sz_boxed_946_ = lean_unbox_usize(v_sz_942_);
lean_dec(v_sz_942_);
v_i_boxed_947_ = lean_unbox_usize(v_i_943_);
lean_dec(v_i_943_);
v_b_boxed_948_ = lean_unbox_uint32(v_b_944_);
lean_dec(v_b_944_);
v_res_949_ = lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotCostHarness_emit_spec__0(v_c_938_, v_variant_939_, v_boundary_940_, v_as_941_, v_sz_boxed_946_, v_i_boxed_947_, v_b_boxed_948_);
lean_dec_ref(v_as_941_);
lean_dec_ref(v_boundary_940_);
lean_dec_ref(v_variant_939_);
lean_dec_ref(v_c_938_);
return v_res_949_;
}
}
LEAN_EXPORT lean_object* lp_competition_R24DotCostHarness_emit(lean_object* v_c_951_, lean_object* v_variant_952_, lean_object* v_boundary_953_, lean_object* v_prep_954_, lean_object* v_life_955_, lean_object* v_rows_956_){
_start:
{
uint32_t v_last_958_; size_t v_sz_959_; size_t v___x_960_; lean_object* v___x_961_; 
v_last_958_ = 0;
v_sz_959_ = lean_array_size(v_rows_956_);
v___x_960_ = ((size_t)0ULL);
v___x_961_ = lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotCostHarness_emit_spec__0(v_c_951_, v_variant_952_, v_boundary_953_, v_rows_956_, v_sz_959_, v___x_960_, v_last_958_);
if (lean_obj_tag(v___x_961_) == 0)
{
lean_object* v_a_962_; lean_object* v_name_963_; lean_object* v_group_964_; lean_object* v___x_965_; lean_object* v___x_966_; lean_object* v___x_967_; lean_object* v___x_968_; lean_object* v___x_969_; lean_object* v___x_970_; lean_object* v___x_971_; lean_object* v___x_972_; lean_object* v___x_973_; lean_object* v___x_974_; lean_object* v___x_975_; lean_object* v___x_976_; lean_object* v___x_977_; lean_object* v___x_978_; lean_object* v___x_979_; lean_object* v___x_980_; lean_object* v___x_981_; lean_object* v___x_982_; lean_object* v___x_983_; lean_object* v___x_984_; uint32_t v___x_985_; lean_object* v___x_986_; lean_object* v___x_987_; lean_object* v___x_988_; lean_object* v___x_989_; 
v_a_962_ = lean_ctor_get(v___x_961_, 0);
lean_inc(v_a_962_);
lean_dec_ref_known(v___x_961_, 1);
v_name_963_ = lean_ctor_get(v_c_951_, 0);
v_group_964_ = lean_ctor_get(v_c_951_, 1);
v___x_965_ = ((lean_object*)(lp_competition_R24DotCostHarness_emit___closed__0));
v___x_966_ = lean_string_append(v___x_965_, v_name_963_);
v___x_967_ = ((lean_object*)(lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotCostHarness_emit_spec__0___closed__1));
v___x_968_ = lean_string_append(v___x_966_, v___x_967_);
v___x_969_ = lean_string_append(v___x_968_, v_group_964_);
v___x_970_ = lean_string_append(v___x_969_, v___x_967_);
v___x_971_ = lean_string_append(v___x_970_, v_variant_952_);
v___x_972_ = lean_string_append(v___x_971_, v___x_967_);
v___x_973_ = lean_string_append(v___x_972_, v_boundary_953_);
v___x_974_ = lean_string_append(v___x_973_, v___x_967_);
v___x_975_ = l_Nat_reprFast(v_prep_954_);
v___x_976_ = lean_string_append(v___x_974_, v___x_975_);
lean_dec_ref(v___x_975_);
v___x_977_ = lean_string_append(v___x_976_, v___x_967_);
v___x_978_ = l_Nat_reprFast(v_life_955_);
v___x_979_ = lean_string_append(v___x_977_, v___x_978_);
lean_dec_ref(v___x_978_);
v___x_980_ = lean_string_append(v___x_979_, v___x_967_);
v___x_981_ = lean_array_get_size(v_rows_956_);
v___x_982_ = l_Nat_reprFast(v___x_981_);
v___x_983_ = lean_string_append(v___x_980_, v___x_982_);
lean_dec_ref(v___x_982_);
v___x_984_ = lean_string_append(v___x_983_, v___x_967_);
v___x_985_ = lean_unbox_uint32(v_a_962_);
lean_dec(v_a_962_);
v___x_986_ = lean_uint32_to_nat(v___x_985_);
v___x_987_ = l_Nat_reprFast(v___x_986_);
v___x_988_ = lean_string_append(v___x_984_, v___x_987_);
lean_dec_ref(v___x_987_);
v___x_989_ = lp_batteries_IO_println___at___00Batteries_Tactic_Lint_lintCore_spec__4(v___x_988_);
return v___x_989_;
}
else
{
lean_object* v_a_990_; lean_object* v___x_992_; uint8_t v_isShared_993_; uint8_t v_isSharedCheck_997_; 
lean_dec(v_life_955_);
lean_dec(v_prep_954_);
v_a_990_ = lean_ctor_get(v___x_961_, 0);
v_isSharedCheck_997_ = !lean_is_exclusive(v___x_961_);
if (v_isSharedCheck_997_ == 0)
{
v___x_992_ = v___x_961_;
v_isShared_993_ = v_isSharedCheck_997_;
goto v_resetjp_991_;
}
else
{
lean_inc(v_a_990_);
lean_dec(v___x_961_);
v___x_992_ = lean_box(0);
v_isShared_993_ = v_isSharedCheck_997_;
goto v_resetjp_991_;
}
v_resetjp_991_:
{
lean_object* v___x_995_; 
if (v_isShared_993_ == 0)
{
v___x_995_ = v___x_992_;
goto v_reusejp_994_;
}
else
{
lean_object* v_reuseFailAlloc_996_; 
v_reuseFailAlloc_996_ = lean_alloc_ctor(1, 1, 0);
lean_ctor_set(v_reuseFailAlloc_996_, 0, v_a_990_);
v___x_995_ = v_reuseFailAlloc_996_;
goto v_reusejp_994_;
}
v_reusejp_994_:
{
return v___x_995_;
}
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_R24DotCostHarness_emit___boxed(lean_object* v_c_998_, lean_object* v_variant_999_, lean_object* v_boundary_1000_, lean_object* v_prep_1001_, lean_object* v_life_1002_, lean_object* v_rows_1003_, lean_object* v_a_1004_){
_start:
{
lean_object* v_res_1005_; 
v_res_1005_ = lp_competition_R24DotCostHarness_emit(v_c_998_, v_variant_999_, v_boundary_1000_, v_prep_1001_, v_life_1002_, v_rows_1003_);
lean_dec_ref(v_rows_1003_);
lean_dec_ref(v_boundary_1000_);
lean_dec_ref(v_variant_999_);
lean_dec_ref(v_c_998_);
return v_res_1005_;
}
}
LEAN_EXPORT uint32_t lp_competition_R24DotCostHarness_passExactFull(lean_object* v_p_1006_, uint32_t v_s_1007_, lean_object* v_iters_1008_){
_start:
{
lean_object* v_zero_1009_; uint8_t v_isZero_1010_; 
v_zero_1009_ = lean_unsigned_to_nat(0u);
v_isZero_1010_ = lean_nat_dec_eq(v_iters_1008_, v_zero_1009_);
if (v_isZero_1010_ == 1)
{
lean_dec(v_iters_1008_);
lean_dec_ref(v_p_1006_);
return v_s_1007_;
}
else
{
lean_object* v_one_1011_; lean_object* v_n_1012_; lean_object* v_p_1013_; lean_object* v_fst_1014_; lean_object* v_snd_1015_; uint32_t v_word_1016_; uint32_t v___x_1017_; 
v_one_1011_ = lean_unsigned_to_nat(1u);
v_n_1012_ = lean_nat_sub(v_iters_1008_, v_one_1011_);
lean_dec(v_iters_1008_);
v_p_1013_ = lp_competition_R24DotBarrier_touchRaw(v_n_1012_, v_p_1006_);
v_fst_1014_ = lean_ctor_get(v_p_1013_, 0);
lean_inc(v_fst_1014_);
v_snd_1015_ = lean_ctor_get(v_p_1013_, 1);
lean_inc(v_snd_1015_);
v_word_1016_ = lp_competition_Submission_R24DotProbe_exactFull(v_fst_1014_, v_snd_1015_);
v___x_1017_ = lean_uint32_add(v_s_1007_, v_word_1016_);
v_p_1006_ = v_p_1013_;
v_s_1007_ = v___x_1017_;
v_iters_1008_ = v_n_1012_;
goto _start;
}
}
}
LEAN_EXPORT lean_object* lp_competition_R24DotCostHarness_passExactFull___boxed(lean_object* v_p_1019_, lean_object* v_s_1020_, lean_object* v_iters_1021_){
_start:
{
uint32_t v_s_boxed_1022_; uint32_t v_res_1023_; lean_object* v_r_1024_; 
v_s_boxed_1022_ = lean_unbox_uint32(v_s_1020_);
lean_dec(v_s_1020_);
v_res_1023_ = lp_competition_R24DotCostHarness_passExactFull(v_p_1019_, v_s_boxed_1022_, v_iters_1021_);
v_r_1024_ = lean_box_uint32(v_res_1023_);
return v_r_1024_;
}
}
LEAN_EXPORT lean_object* lp_competition_R24DotCostHarness_benchExactFull___lam__0(){
_start:
{
lean_object* v___x_1026_; lean_object* v___x_1027_; 
v___x_1026_ = lean_io_mono_nanos_now();
v___x_1027_ = lean_alloc_ctor(0, 1, 0);
lean_ctor_set(v___x_1027_, 0, v___x_1026_);
return v___x_1027_;
}
}
LEAN_EXPORT lean_object* lp_competition_R24DotCostHarness_benchExactFull___lam__0___boxed(lean_object* v___y_1028_){
_start:
{
lean_object* v_res_1029_; 
v_res_1029_ = lp_competition_R24DotCostHarness_benchExactFull___lam__0();
return v_res_1029_;
}
}
LEAN_EXPORT lean_object* lp_competition_R24DotCostHarness_benchExactFull___lam__1(lean_object* v_a_1030_, lean_object* v_b_1031_, lean_object* v_x_1032_){
_start:
{
lean_object* v___x_1033_; 
v___x_1033_ = lean_alloc_ctor(0, 2, 0);
lean_ctor_set(v___x_1033_, 0, v_a_1030_);
lean_ctor_set(v___x_1033_, 1, v_b_1031_);
return v___x_1033_;
}
}
LEAN_EXPORT uint32_t lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchExactFull_spec__0___redArg___lam__1(lean_object* v_a_1034_, uint32_t v___x_1035_, lean_object* v_iters_1036_, lean_object* v_x_1037_){
_start:
{
uint32_t v___x_1038_; 
v___x_1038_ = lp_competition_R24DotCostHarness_passExactFull(v_a_1034_, v___x_1035_, v_iters_1036_);
return v___x_1038_;
}
}
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchExactFull_spec__0___redArg___lam__1___boxed(lean_object* v_a_1039_, lean_object* v___x_1040_, lean_object* v_iters_1041_, lean_object* v_x_1042_){
_start:
{
uint32_t v___x_1779__boxed_1043_; uint32_t v_res_1044_; lean_object* v_r_1045_; 
v___x_1779__boxed_1043_ = lean_unbox_uint32(v___x_1040_);
lean_dec(v___x_1040_);
v_res_1044_ = lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchExactFull_spec__0___redArg___lam__1(v_a_1039_, v___x_1779__boxed_1043_, v_iters_1041_, v_x_1042_);
v_r_1045_ = lean_box_uint32(v_res_1044_);
return v_r_1045_;
}
}
LEAN_EXPORT uint32_t lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchExactFull_spec__0___redArg___lam__0(lean_object* v_a_1046_, lean_object* v_x_1047_){
_start:
{
lean_object* v_fst_1048_; lean_object* v_snd_1049_; uint32_t v___x_1050_; 
v_fst_1048_ = lean_ctor_get(v_a_1046_, 0);
lean_inc(v_fst_1048_);
v_snd_1049_ = lean_ctor_get(v_a_1046_, 1);
lean_inc(v_snd_1049_);
lean_dec_ref(v_a_1046_);
v___x_1050_ = lp_competition_Submission_R24DotProbe_exactFull(v_fst_1048_, v_snd_1049_);
return v___x_1050_;
}
}
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchExactFull_spec__0___redArg___lam__0___boxed(lean_object* v_a_1051_, lean_object* v_x_1052_){
_start:
{
uint32_t v_res_1053_; lean_object* v_r_1054_; 
v_res_1053_ = lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchExactFull_spec__0___redArg___lam__0(v_a_1051_, v_x_1052_);
v_r_1054_ = lean_box_uint32(v_res_1053_);
return v_r_1054_;
}
}
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00__private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchExactFull_spec__0_spec__0___redArg(lean_object* v_a_1058_, lean_object* v_c_1059_, uint32_t v_expected_1060_, lean_object* v_iters_1061_, lean_object* v___x_1062_, lean_object* v_range_1063_, lean_object* v_b_1064_, lean_object* v_i_1065_){
_start:
{
lean_object* v_stop_1067_; lean_object* v_step_1068_; uint8_t v___x_1069_; 
v_stop_1067_ = lean_ctor_get(v_range_1063_, 1);
v_step_1068_ = lean_ctor_get(v_range_1063_, 2);
v___x_1069_ = lean_nat_dec_lt(v_i_1065_, v_stop_1067_);
if (v___x_1069_ == 0)
{
lean_object* v___x_1070_; 
lean_dec(v_i_1065_);
lean_dec(v___x_1062_);
lean_dec(v_iters_1061_);
lean_dec_ref(v_c_1059_);
lean_dec_ref(v_a_1058_);
v___x_1070_ = lean_alloc_ctor(0, 1, 0);
lean_ctor_set(v___x_1070_, 0, v_b_1064_);
return v___x_1070_;
}
else
{
lean_object* v___f_1071_; lean_object* v___x_1072_; lean_object* v_a_1073_; lean_object* v_name_1074_; lean_object* v___x_1075_; uint32_t v___x_1076_; lean_object* v___x_1077_; 
lean_inc_ref(v_a_1058_);
v___f_1071_ = lean_alloc_closure((void*)(lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchExactFull_spec__0___redArg___lam__0___boxed), 2, 1);
lean_closure_set(v___f_1071_, 0, v_a_1058_);
lean_inc_ref(v___f_1071_);
v___x_1072_ = l_IO_lazyPure___redArg(v___f_1071_);
v_a_1073_ = lean_ctor_get(v___x_1072_, 0);
lean_inc(v_a_1073_);
lean_dec_ref(v___x_1072_);
v_name_1074_ = lean_ctor_get(v_c_1059_, 0);
v___x_1075_ = ((lean_object*)(lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00__private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchExactFull_spec__0_spec__0___redArg___closed__0));
v___x_1076_ = lean_unbox_uint32(v_a_1073_);
lean_dec(v_a_1073_);
lean_inc_ref(v_name_1074_);
v___x_1077_ = lp_competition_R24DotCostHarness_checkWord(v_name_1074_, v___x_1075_, v___x_1076_, v_expected_1060_);
if (lean_obj_tag(v___x_1077_) == 0)
{
lean_object* v___x_1078_; uint32_t v___x_1079_; lean_object* v___x_1080_; lean_object* v___f_1081_; lean_object* v___x_1082_; lean_object* v_a_1083_; lean_object* v___x_1084_; uint32_t v___x_1085_; lean_object* v___x_1086_; uint32_t v___x_1087_; lean_object* v___x_1088_; 
lean_dec_ref_known(v___x_1077_, 1);
v___x_1078_ = lean_io_mono_nanos_now();
v___x_1079_ = lp_competition_R24DotCostHarness_seed(v_i_1065_);
v___x_1080_ = lean_box_uint32(v___x_1079_);
lean_inc(v_iters_1061_);
lean_inc_ref(v_a_1058_);
v___f_1081_ = lean_alloc_closure((void*)(lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchExactFull_spec__0___redArg___lam__1___boxed), 4, 3);
lean_closure_set(v___f_1081_, 0, v_a_1058_);
lean_closure_set(v___f_1081_, 1, v___x_1080_);
lean_closure_set(v___f_1081_, 2, v_iters_1061_);
v___x_1082_ = l_IO_lazyPure___redArg(v___f_1081_);
v_a_1083_ = lean_ctor_get(v___x_1082_, 0);
lean_inc(v_a_1083_);
lean_dec_ref(v___x_1082_);
v___x_1084_ = lean_io_mono_nanos_now();
v___x_1085_ = lp_competition_R24DotCostHarness_sinkExpected(v___x_1079_, v_expected_1060_, v_iters_1061_);
v___x_1086_ = ((lean_object*)(lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00__private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchExactFull_spec__0_spec__0___redArg___closed__1));
v___x_1087_ = lean_unbox_uint32(v_a_1083_);
lean_inc_ref(v_name_1074_);
v___x_1088_ = lp_competition_R24DotCostHarness_checkWord(v_name_1074_, v___x_1086_, v___x_1087_, v___x_1085_);
if (lean_obj_tag(v___x_1088_) == 0)
{
lean_object* v___x_1089_; lean_object* v_a_1090_; lean_object* v___x_1091_; uint32_t v___x_1092_; lean_object* v___x_1093_; 
lean_dec_ref_known(v___x_1088_, 1);
v___x_1089_ = l_IO_lazyPure___redArg(v___f_1071_);
v_a_1090_ = lean_ctor_get(v___x_1089_, 0);
lean_inc(v_a_1090_);
lean_dec_ref(v___x_1089_);
v___x_1091_ = ((lean_object*)(lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00__private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchExactFull_spec__0_spec__0___redArg___closed__2));
v___x_1092_ = lean_unbox_uint32(v_a_1090_);
lean_inc_ref(v_name_1074_);
v___x_1093_ = lp_competition_R24DotCostHarness_checkWord(v_name_1074_, v___x_1091_, v___x_1092_, v_expected_1060_);
if (lean_obj_tag(v___x_1093_) == 0)
{
lean_object* v___x_1094_; lean_object* v___x_1095_; uint32_t v___x_1096_; uint32_t v___x_1097_; lean_object* v___x_1098_; lean_object* v___x_1099_; 
lean_dec_ref_known(v___x_1093_, 1);
v___x_1094_ = lean_nat_sub(v___x_1084_, v___x_1078_);
lean_dec(v___x_1078_);
lean_dec(v___x_1084_);
lean_inc(v_iters_1061_);
lean_inc(v___x_1062_);
lean_inc(v_i_1065_);
v___x_1095_ = lean_alloc_ctor(0, 4, 12);
lean_ctor_set(v___x_1095_, 0, v_i_1065_);
lean_ctor_set(v___x_1095_, 1, v___x_1062_);
lean_ctor_set(v___x_1095_, 2, v_iters_1061_);
lean_ctor_set(v___x_1095_, 3, v___x_1094_);
v___x_1096_ = lean_unbox_uint32(v_a_1083_);
lean_dec(v_a_1083_);
lean_ctor_set_uint32(v___x_1095_, sizeof(void*)*4, v___x_1096_);
lean_ctor_set_uint32(v___x_1095_, sizeof(void*)*4 + 4, v___x_1085_);
v___x_1097_ = lean_unbox_uint32(v_a_1090_);
lean_dec(v_a_1090_);
lean_ctor_set_uint32(v___x_1095_, sizeof(void*)*4 + 8, v___x_1097_);
v___x_1098_ = lean_array_push(v_b_1064_, v___x_1095_);
v___x_1099_ = lean_nat_add(v_i_1065_, v_step_1068_);
lean_dec(v_i_1065_);
v_b_1064_ = v___x_1098_;
v_i_1065_ = v___x_1099_;
goto _start;
}
else
{
lean_object* v_a_1101_; lean_object* v___x_1103_; uint8_t v_isShared_1104_; uint8_t v_isSharedCheck_1108_; 
lean_dec(v_a_1090_);
lean_dec(v___x_1084_);
lean_dec(v_a_1083_);
lean_dec(v___x_1078_);
lean_dec(v_i_1065_);
lean_dec_ref(v_b_1064_);
lean_dec(v___x_1062_);
lean_dec(v_iters_1061_);
lean_dec_ref(v_c_1059_);
lean_dec_ref(v_a_1058_);
v_a_1101_ = lean_ctor_get(v___x_1093_, 0);
v_isSharedCheck_1108_ = !lean_is_exclusive(v___x_1093_);
if (v_isSharedCheck_1108_ == 0)
{
v___x_1103_ = v___x_1093_;
v_isShared_1104_ = v_isSharedCheck_1108_;
goto v_resetjp_1102_;
}
else
{
lean_inc(v_a_1101_);
lean_dec(v___x_1093_);
v___x_1103_ = lean_box(0);
v_isShared_1104_ = v_isSharedCheck_1108_;
goto v_resetjp_1102_;
}
v_resetjp_1102_:
{
lean_object* v___x_1106_; 
if (v_isShared_1104_ == 0)
{
v___x_1106_ = v___x_1103_;
goto v_reusejp_1105_;
}
else
{
lean_object* v_reuseFailAlloc_1107_; 
v_reuseFailAlloc_1107_ = lean_alloc_ctor(1, 1, 0);
lean_ctor_set(v_reuseFailAlloc_1107_, 0, v_a_1101_);
v___x_1106_ = v_reuseFailAlloc_1107_;
goto v_reusejp_1105_;
}
v_reusejp_1105_:
{
return v___x_1106_;
}
}
}
}
else
{
lean_object* v_a_1109_; lean_object* v___x_1111_; uint8_t v_isShared_1112_; uint8_t v_isSharedCheck_1116_; 
lean_dec(v___x_1084_);
lean_dec(v_a_1083_);
lean_dec(v___x_1078_);
lean_dec_ref(v___f_1071_);
lean_dec(v_i_1065_);
lean_dec_ref(v_b_1064_);
lean_dec(v___x_1062_);
lean_dec(v_iters_1061_);
lean_dec_ref(v_c_1059_);
lean_dec_ref(v_a_1058_);
v_a_1109_ = lean_ctor_get(v___x_1088_, 0);
v_isSharedCheck_1116_ = !lean_is_exclusive(v___x_1088_);
if (v_isSharedCheck_1116_ == 0)
{
v___x_1111_ = v___x_1088_;
v_isShared_1112_ = v_isSharedCheck_1116_;
goto v_resetjp_1110_;
}
else
{
lean_inc(v_a_1109_);
lean_dec(v___x_1088_);
v___x_1111_ = lean_box(0);
v_isShared_1112_ = v_isSharedCheck_1116_;
goto v_resetjp_1110_;
}
v_resetjp_1110_:
{
lean_object* v___x_1114_; 
if (v_isShared_1112_ == 0)
{
v___x_1114_ = v___x_1111_;
goto v_reusejp_1113_;
}
else
{
lean_object* v_reuseFailAlloc_1115_; 
v_reuseFailAlloc_1115_ = lean_alloc_ctor(1, 1, 0);
lean_ctor_set(v_reuseFailAlloc_1115_, 0, v_a_1109_);
v___x_1114_ = v_reuseFailAlloc_1115_;
goto v_reusejp_1113_;
}
v_reusejp_1113_:
{
return v___x_1114_;
}
}
}
}
else
{
lean_object* v_a_1117_; lean_object* v___x_1119_; uint8_t v_isShared_1120_; uint8_t v_isSharedCheck_1124_; 
lean_dec_ref(v___f_1071_);
lean_dec(v_i_1065_);
lean_dec_ref(v_b_1064_);
lean_dec(v___x_1062_);
lean_dec(v_iters_1061_);
lean_dec_ref(v_c_1059_);
lean_dec_ref(v_a_1058_);
v_a_1117_ = lean_ctor_get(v___x_1077_, 0);
v_isSharedCheck_1124_ = !lean_is_exclusive(v___x_1077_);
if (v_isSharedCheck_1124_ == 0)
{
v___x_1119_ = v___x_1077_;
v_isShared_1120_ = v_isSharedCheck_1124_;
goto v_resetjp_1118_;
}
else
{
lean_inc(v_a_1117_);
lean_dec(v___x_1077_);
v___x_1119_ = lean_box(0);
v_isShared_1120_ = v_isSharedCheck_1124_;
goto v_resetjp_1118_;
}
v_resetjp_1118_:
{
lean_object* v___x_1122_; 
if (v_isShared_1120_ == 0)
{
v___x_1122_ = v___x_1119_;
goto v_reusejp_1121_;
}
else
{
lean_object* v_reuseFailAlloc_1123_; 
v_reuseFailAlloc_1123_ = lean_alloc_ctor(1, 1, 0);
lean_ctor_set(v_reuseFailAlloc_1123_, 0, v_a_1117_);
v___x_1122_ = v_reuseFailAlloc_1123_;
goto v_reusejp_1121_;
}
v_reusejp_1121_:
{
return v___x_1122_;
}
}
}
}
}
}
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00__private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchExactFull_spec__0_spec__0___redArg___boxed(lean_object* v_a_1125_, lean_object* v_c_1126_, lean_object* v_expected_1127_, lean_object* v_iters_1128_, lean_object* v___x_1129_, lean_object* v_range_1130_, lean_object* v_b_1131_, lean_object* v_i_1132_, lean_object* v___y_1133_){
_start:
{
uint32_t v_expected_boxed_1134_; lean_object* v_res_1135_; 
v_expected_boxed_1134_ = lean_unbox_uint32(v_expected_1127_);
lean_dec(v_expected_1127_);
v_res_1135_ = lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00__private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchExactFull_spec__0_spec__0___redArg(v_a_1125_, v_c_1126_, v_expected_boxed_1134_, v_iters_1128_, v___x_1129_, v_range_1130_, v_b_1131_, v_i_1132_);
lean_dec_ref(v_range_1130_);
return v_res_1135_;
}
}
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchExactFull_spec__0___redArg(lean_object* v_a_1136_, lean_object* v_c_1137_, uint32_t v_expected_1138_, lean_object* v_iters_1139_, lean_object* v___x_1140_, lean_object* v_range_1141_, lean_object* v_b_1142_, lean_object* v_i_1143_){
_start:
{
lean_object* v_stop_1145_; lean_object* v_step_1146_; uint8_t v___x_1147_; 
v_stop_1145_ = lean_ctor_get(v_range_1141_, 1);
v_step_1146_ = lean_ctor_get(v_range_1141_, 2);
v___x_1147_ = lean_nat_dec_lt(v_i_1143_, v_stop_1145_);
if (v___x_1147_ == 0)
{
lean_object* v___x_1148_; 
lean_dec(v_i_1143_);
lean_dec(v___x_1140_);
lean_dec(v_iters_1139_);
lean_dec_ref(v_c_1137_);
lean_dec_ref(v_a_1136_);
v___x_1148_ = lean_alloc_ctor(0, 1, 0);
lean_ctor_set(v___x_1148_, 0, v_b_1142_);
return v___x_1148_;
}
else
{
lean_object* v___f_1149_; lean_object* v___x_1150_; lean_object* v_a_1151_; lean_object* v_name_1152_; lean_object* v___x_1153_; uint32_t v___x_1154_; lean_object* v___x_1155_; 
lean_inc_ref(v_a_1136_);
v___f_1149_ = lean_alloc_closure((void*)(lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchExactFull_spec__0___redArg___lam__0___boxed), 2, 1);
lean_closure_set(v___f_1149_, 0, v_a_1136_);
lean_inc_ref(v___f_1149_);
v___x_1150_ = l_IO_lazyPure___redArg(v___f_1149_);
v_a_1151_ = lean_ctor_get(v___x_1150_, 0);
lean_inc(v_a_1151_);
lean_dec_ref(v___x_1150_);
v_name_1152_ = lean_ctor_get(v_c_1137_, 0);
v___x_1153_ = ((lean_object*)(lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00__private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchExactFull_spec__0_spec__0___redArg___closed__0));
v___x_1154_ = lean_unbox_uint32(v_a_1151_);
lean_dec(v_a_1151_);
lean_inc_ref(v_name_1152_);
v___x_1155_ = lp_competition_R24DotCostHarness_checkWord(v_name_1152_, v___x_1153_, v___x_1154_, v_expected_1138_);
if (lean_obj_tag(v___x_1155_) == 0)
{
lean_object* v___x_1156_; uint32_t v___x_1157_; lean_object* v___x_1158_; lean_object* v___f_1159_; lean_object* v___x_1160_; lean_object* v_a_1161_; lean_object* v___x_1162_; uint32_t v___x_1163_; lean_object* v___x_1164_; uint32_t v___x_1165_; lean_object* v___x_1166_; 
lean_dec_ref_known(v___x_1155_, 1);
v___x_1156_ = lean_io_mono_nanos_now();
v___x_1157_ = lp_competition_R24DotCostHarness_seed(v_i_1143_);
v___x_1158_ = lean_box_uint32(v___x_1157_);
lean_inc(v_iters_1139_);
lean_inc_ref(v_a_1136_);
v___f_1159_ = lean_alloc_closure((void*)(lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchExactFull_spec__0___redArg___lam__1___boxed), 4, 3);
lean_closure_set(v___f_1159_, 0, v_a_1136_);
lean_closure_set(v___f_1159_, 1, v___x_1158_);
lean_closure_set(v___f_1159_, 2, v_iters_1139_);
v___x_1160_ = l_IO_lazyPure___redArg(v___f_1159_);
v_a_1161_ = lean_ctor_get(v___x_1160_, 0);
lean_inc(v_a_1161_);
lean_dec_ref(v___x_1160_);
v___x_1162_ = lean_io_mono_nanos_now();
v___x_1163_ = lp_competition_R24DotCostHarness_sinkExpected(v___x_1157_, v_expected_1138_, v_iters_1139_);
v___x_1164_ = ((lean_object*)(lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00__private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchExactFull_spec__0_spec__0___redArg___closed__1));
v___x_1165_ = lean_unbox_uint32(v_a_1161_);
lean_inc_ref(v_name_1152_);
v___x_1166_ = lp_competition_R24DotCostHarness_checkWord(v_name_1152_, v___x_1164_, v___x_1165_, v___x_1163_);
if (lean_obj_tag(v___x_1166_) == 0)
{
lean_object* v___x_1167_; lean_object* v_a_1168_; lean_object* v___x_1169_; uint32_t v___x_1170_; lean_object* v___x_1171_; 
lean_dec_ref_known(v___x_1166_, 1);
v___x_1167_ = l_IO_lazyPure___redArg(v___f_1149_);
v_a_1168_ = lean_ctor_get(v___x_1167_, 0);
lean_inc(v_a_1168_);
lean_dec_ref(v___x_1167_);
v___x_1169_ = ((lean_object*)(lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00__private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchExactFull_spec__0_spec__0___redArg___closed__2));
v___x_1170_ = lean_unbox_uint32(v_a_1168_);
lean_inc_ref(v_name_1152_);
v___x_1171_ = lp_competition_R24DotCostHarness_checkWord(v_name_1152_, v___x_1169_, v___x_1170_, v_expected_1138_);
if (lean_obj_tag(v___x_1171_) == 0)
{
lean_object* v___x_1172_; lean_object* v___x_1173_; uint32_t v___x_1174_; uint32_t v___x_1175_; lean_object* v___x_1176_; lean_object* v___x_1177_; lean_object* v___x_1178_; 
lean_dec_ref_known(v___x_1171_, 1);
v___x_1172_ = lean_nat_sub(v___x_1162_, v___x_1156_);
lean_dec(v___x_1156_);
lean_dec(v___x_1162_);
lean_inc(v_iters_1139_);
lean_inc(v___x_1140_);
lean_inc(v_i_1143_);
v___x_1173_ = lean_alloc_ctor(0, 4, 12);
lean_ctor_set(v___x_1173_, 0, v_i_1143_);
lean_ctor_set(v___x_1173_, 1, v___x_1140_);
lean_ctor_set(v___x_1173_, 2, v_iters_1139_);
lean_ctor_set(v___x_1173_, 3, v___x_1172_);
v___x_1174_ = lean_unbox_uint32(v_a_1161_);
lean_dec(v_a_1161_);
lean_ctor_set_uint32(v___x_1173_, sizeof(void*)*4, v___x_1174_);
lean_ctor_set_uint32(v___x_1173_, sizeof(void*)*4 + 4, v___x_1163_);
v___x_1175_ = lean_unbox_uint32(v_a_1168_);
lean_dec(v_a_1168_);
lean_ctor_set_uint32(v___x_1173_, sizeof(void*)*4 + 8, v___x_1175_);
v___x_1176_ = lean_array_push(v_b_1142_, v___x_1173_);
v___x_1177_ = lean_nat_add(v_i_1143_, v_step_1146_);
lean_dec(v_i_1143_);
v___x_1178_ = lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00__private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchExactFull_spec__0_spec__0___redArg(v_a_1136_, v_c_1137_, v_expected_1138_, v_iters_1139_, v___x_1140_, v_range_1141_, v___x_1176_, v___x_1177_);
return v___x_1178_;
}
else
{
lean_object* v_a_1179_; lean_object* v___x_1181_; uint8_t v_isShared_1182_; uint8_t v_isSharedCheck_1186_; 
lean_dec(v_a_1168_);
lean_dec(v___x_1162_);
lean_dec(v_a_1161_);
lean_dec(v___x_1156_);
lean_dec(v_i_1143_);
lean_dec_ref(v_b_1142_);
lean_dec(v___x_1140_);
lean_dec(v_iters_1139_);
lean_dec_ref(v_c_1137_);
lean_dec_ref(v_a_1136_);
v_a_1179_ = lean_ctor_get(v___x_1171_, 0);
v_isSharedCheck_1186_ = !lean_is_exclusive(v___x_1171_);
if (v_isSharedCheck_1186_ == 0)
{
v___x_1181_ = v___x_1171_;
v_isShared_1182_ = v_isSharedCheck_1186_;
goto v_resetjp_1180_;
}
else
{
lean_inc(v_a_1179_);
lean_dec(v___x_1171_);
v___x_1181_ = lean_box(0);
v_isShared_1182_ = v_isSharedCheck_1186_;
goto v_resetjp_1180_;
}
v_resetjp_1180_:
{
lean_object* v___x_1184_; 
if (v_isShared_1182_ == 0)
{
v___x_1184_ = v___x_1181_;
goto v_reusejp_1183_;
}
else
{
lean_object* v_reuseFailAlloc_1185_; 
v_reuseFailAlloc_1185_ = lean_alloc_ctor(1, 1, 0);
lean_ctor_set(v_reuseFailAlloc_1185_, 0, v_a_1179_);
v___x_1184_ = v_reuseFailAlloc_1185_;
goto v_reusejp_1183_;
}
v_reusejp_1183_:
{
return v___x_1184_;
}
}
}
}
else
{
lean_object* v_a_1187_; lean_object* v___x_1189_; uint8_t v_isShared_1190_; uint8_t v_isSharedCheck_1194_; 
lean_dec(v___x_1162_);
lean_dec(v_a_1161_);
lean_dec(v___x_1156_);
lean_dec_ref(v___f_1149_);
lean_dec(v_i_1143_);
lean_dec_ref(v_b_1142_);
lean_dec(v___x_1140_);
lean_dec(v_iters_1139_);
lean_dec_ref(v_c_1137_);
lean_dec_ref(v_a_1136_);
v_a_1187_ = lean_ctor_get(v___x_1166_, 0);
v_isSharedCheck_1194_ = !lean_is_exclusive(v___x_1166_);
if (v_isSharedCheck_1194_ == 0)
{
v___x_1189_ = v___x_1166_;
v_isShared_1190_ = v_isSharedCheck_1194_;
goto v_resetjp_1188_;
}
else
{
lean_inc(v_a_1187_);
lean_dec(v___x_1166_);
v___x_1189_ = lean_box(0);
v_isShared_1190_ = v_isSharedCheck_1194_;
goto v_resetjp_1188_;
}
v_resetjp_1188_:
{
lean_object* v___x_1192_; 
if (v_isShared_1190_ == 0)
{
v___x_1192_ = v___x_1189_;
goto v_reusejp_1191_;
}
else
{
lean_object* v_reuseFailAlloc_1193_; 
v_reuseFailAlloc_1193_ = lean_alloc_ctor(1, 1, 0);
lean_ctor_set(v_reuseFailAlloc_1193_, 0, v_a_1187_);
v___x_1192_ = v_reuseFailAlloc_1193_;
goto v_reusejp_1191_;
}
v_reusejp_1191_:
{
return v___x_1192_;
}
}
}
}
else
{
lean_object* v_a_1195_; lean_object* v___x_1197_; uint8_t v_isShared_1198_; uint8_t v_isSharedCheck_1202_; 
lean_dec_ref(v___f_1149_);
lean_dec(v_i_1143_);
lean_dec_ref(v_b_1142_);
lean_dec(v___x_1140_);
lean_dec(v_iters_1139_);
lean_dec_ref(v_c_1137_);
lean_dec_ref(v_a_1136_);
v_a_1195_ = lean_ctor_get(v___x_1155_, 0);
v_isSharedCheck_1202_ = !lean_is_exclusive(v___x_1155_);
if (v_isSharedCheck_1202_ == 0)
{
v___x_1197_ = v___x_1155_;
v_isShared_1198_ = v_isSharedCheck_1202_;
goto v_resetjp_1196_;
}
else
{
lean_inc(v_a_1195_);
lean_dec(v___x_1155_);
v___x_1197_ = lean_box(0);
v_isShared_1198_ = v_isSharedCheck_1202_;
goto v_resetjp_1196_;
}
v_resetjp_1196_:
{
lean_object* v___x_1200_; 
if (v_isShared_1198_ == 0)
{
v___x_1200_ = v___x_1197_;
goto v_reusejp_1199_;
}
else
{
lean_object* v_reuseFailAlloc_1201_; 
v_reuseFailAlloc_1201_ = lean_alloc_ctor(1, 1, 0);
lean_ctor_set(v_reuseFailAlloc_1201_, 0, v_a_1195_);
v___x_1200_ = v_reuseFailAlloc_1201_;
goto v_reusejp_1199_;
}
v_reusejp_1199_:
{
return v___x_1200_;
}
}
}
}
}
}
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchExactFull_spec__0___redArg___boxed(lean_object* v_a_1203_, lean_object* v_c_1204_, lean_object* v_expected_1205_, lean_object* v_iters_1206_, lean_object* v___x_1207_, lean_object* v_range_1208_, lean_object* v_b_1209_, lean_object* v_i_1210_, lean_object* v___y_1211_){
_start:
{
uint32_t v_expected_boxed_1212_; lean_object* v_res_1213_; 
v_expected_boxed_1212_ = lean_unbox_uint32(v_expected_1205_);
lean_dec(v_expected_1205_);
v_res_1213_ = lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchExactFull_spec__0___redArg(v_a_1203_, v_c_1204_, v_expected_boxed_1212_, v_iters_1206_, v___x_1207_, v_range_1208_, v_b_1209_, v_i_1210_);
lean_dec_ref(v_range_1208_);
return v_res_1213_;
}
}
LEAN_EXPORT lean_object* lp_competition_R24DotCostHarness_benchExactFull(lean_object* v_c_1222_, lean_object* v_a_1223_, lean_object* v_b_1224_, lean_object* v_macs_1225_){
_start:
{
lean_object* v___x_1227_; lean_object* v_a_1228_; lean_object* v___x_1229_; lean_object* v___f_1230_; lean_object* v___x_1231_; lean_object* v_a_1232_; lean_object* v___x_1233_; lean_object* v_expected_1234_; uint32_t v_expected_1235_; lean_object* v___x_1236_; lean_object* v_iters_1237_; lean_object* v___x_1238_; lean_object* v___x_1239_; lean_object* v___x_1240_; lean_object* v___x_1241_; 
v___x_1227_ = lp_competition_R24DotCostHarness_benchExactFull___lam__0();
v_a_1228_ = lean_ctor_get(v___x_1227_, 0);
lean_inc(v_a_1228_);
lean_dec_ref(v___x_1227_);
v___x_1229_ = lp_competition_R24DotCostHarness_benchExactFull___lam__0();
lean_dec_ref(v___x_1229_);
lean_inc_ref(v_a_1223_);
v___f_1230_ = lean_alloc_closure((void*)(lp_competition_R24DotCostHarness_benchExactFull___lam__1), 3, 2);
lean_closure_set(v___f_1230_, 0, v_a_1223_);
lean_closure_set(v___f_1230_, 1, v_b_1224_);
v___x_1231_ = l_IO_lazyPure___redArg(v___f_1230_);
v_a_1232_ = lean_ctor_get(v___x_1231_, 0);
lean_inc(v_a_1232_);
lean_dec_ref(v___x_1231_);
v___x_1233_ = lp_competition_R24DotCostHarness_benchExactFull___lam__0();
lean_dec_ref(v___x_1233_);
v_expected_1234_ = lean_ctor_get(v_c_1222_, 5);
v_expected_1235_ = lean_uint32_of_nat(v_expected_1234_);
v___x_1236_ = lean_array_get_size(v_a_1223_);
lean_dec_ref(v_a_1223_);
v_iters_1237_ = lp_competition_R24DotCostHarness_repeats(v_macs_1225_, v___x_1236_);
v___x_1238_ = lean_unsigned_to_nat(0u);
v___x_1239_ = ((lean_object*)(lp_competition_R24DotCostHarness_benchExactFull___closed__0));
v___x_1240_ = ((lean_object*)(lp_competition_R24DotCostHarness_benchExactFull___closed__1));
lean_inc_ref(v_c_1222_);
v___x_1241_ = lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchExactFull_spec__0___redArg(v_a_1232_, v_c_1222_, v_expected_1235_, v_iters_1237_, v___x_1236_, v___x_1240_, v___x_1239_, v___x_1238_);
if (lean_obj_tag(v___x_1241_) == 0)
{
lean_object* v_a_1242_; lean_object* v___x_1243_; lean_object* v_a_1244_; lean_object* v___x_1245_; lean_object* v___x_1246_; lean_object* v___x_1247_; lean_object* v___x_1248_; 
v_a_1242_ = lean_ctor_get(v___x_1241_, 0);
lean_inc(v_a_1242_);
lean_dec_ref_known(v___x_1241_, 1);
v___x_1243_ = lp_competition_R24DotCostHarness_benchExactFull___lam__0();
v_a_1244_ = lean_ctor_get(v___x_1243_, 0);
lean_inc(v_a_1244_);
lean_dec_ref(v___x_1243_);
v___x_1245_ = ((lean_object*)(lp_competition_R24DotCostHarness_benchExactFull___closed__2));
v___x_1246_ = ((lean_object*)(lp_competition_R24DotCostHarness_benchExactFull___closed__3));
v___x_1247_ = lean_nat_sub(v_a_1244_, v_a_1228_);
lean_dec(v_a_1228_);
lean_dec(v_a_1244_);
v___x_1248_ = lp_competition_R24DotCostHarness_emit(v_c_1222_, v___x_1245_, v___x_1246_, v___x_1238_, v___x_1247_, v_a_1242_);
lean_dec(v_a_1242_);
lean_dec_ref(v_c_1222_);
return v___x_1248_;
}
else
{
lean_object* v_a_1249_; lean_object* v___x_1251_; uint8_t v_isShared_1252_; uint8_t v_isSharedCheck_1256_; 
lean_dec(v_a_1228_);
lean_dec_ref(v_c_1222_);
v_a_1249_ = lean_ctor_get(v___x_1241_, 0);
v_isSharedCheck_1256_ = !lean_is_exclusive(v___x_1241_);
if (v_isSharedCheck_1256_ == 0)
{
v___x_1251_ = v___x_1241_;
v_isShared_1252_ = v_isSharedCheck_1256_;
goto v_resetjp_1250_;
}
else
{
lean_inc(v_a_1249_);
lean_dec(v___x_1241_);
v___x_1251_ = lean_box(0);
v_isShared_1252_ = v_isSharedCheck_1256_;
goto v_resetjp_1250_;
}
v_resetjp_1250_:
{
lean_object* v___x_1254_; 
if (v_isShared_1252_ == 0)
{
v___x_1254_ = v___x_1251_;
goto v_reusejp_1253_;
}
else
{
lean_object* v_reuseFailAlloc_1255_; 
v_reuseFailAlloc_1255_ = lean_alloc_ctor(1, 1, 0);
lean_ctor_set(v_reuseFailAlloc_1255_, 0, v_a_1249_);
v___x_1254_ = v_reuseFailAlloc_1255_;
goto v_reusejp_1253_;
}
v_reusejp_1253_:
{
return v___x_1254_;
}
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_R24DotCostHarness_benchExactFull___boxed(lean_object* v_c_1257_, lean_object* v_a_1258_, lean_object* v_b_1259_, lean_object* v_macs_1260_, lean_object* v_a_1261_){
_start:
{
lean_object* v_res_1262_; 
v_res_1262_ = lp_competition_R24DotCostHarness_benchExactFull(v_c_1257_, v_a_1258_, v_b_1259_, v_macs_1260_);
lean_dec(v_macs_1260_);
return v_res_1262_;
}
}
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchExactFull_spec__0(lean_object* v_a_1263_, lean_object* v_c_1264_, uint32_t v_expected_1265_, lean_object* v_iters_1266_, lean_object* v___x_1267_, lean_object* v_range_1268_, lean_object* v_b_1269_, lean_object* v_i_1270_, lean_object* v_hs_1271_, lean_object* v_hl_1272_){
_start:
{
lean_object* v___x_1274_; 
v___x_1274_ = lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchExactFull_spec__0___redArg(v_a_1263_, v_c_1264_, v_expected_1265_, v_iters_1266_, v___x_1267_, v_range_1268_, v_b_1269_, v_i_1270_);
return v___x_1274_;
}
}
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchExactFull_spec__0___boxed(lean_object* v_a_1275_, lean_object* v_c_1276_, lean_object* v_expected_1277_, lean_object* v_iters_1278_, lean_object* v___x_1279_, lean_object* v_range_1280_, lean_object* v_b_1281_, lean_object* v_i_1282_, lean_object* v_hs_1283_, lean_object* v_hl_1284_, lean_object* v___y_1285_){
_start:
{
uint32_t v_expected_boxed_1286_; lean_object* v_res_1287_; 
v_expected_boxed_1286_ = lean_unbox_uint32(v_expected_1277_);
lean_dec(v_expected_1277_);
v_res_1287_ = lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchExactFull_spec__0(v_a_1275_, v_c_1276_, v_expected_boxed_1286_, v_iters_1278_, v___x_1279_, v_range_1280_, v_b_1281_, v_i_1282_, v_hs_1283_, v_hl_1284_);
lean_dec_ref(v_range_1280_);
return v_res_1287_;
}
}
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00__private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchExactFull_spec__0_spec__0(lean_object* v_a_1288_, lean_object* v_c_1289_, uint32_t v_expected_1290_, lean_object* v_iters_1291_, lean_object* v___x_1292_, lean_object* v_range_1293_, lean_object* v_b_1294_, lean_object* v_i_1295_, lean_object* v_hs_1296_, lean_object* v_hl_1297_){
_start:
{
lean_object* v___x_1299_; 
v___x_1299_ = lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00__private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchExactFull_spec__0_spec__0___redArg(v_a_1288_, v_c_1289_, v_expected_1290_, v_iters_1291_, v___x_1292_, v_range_1293_, v_b_1294_, v_i_1295_);
return v___x_1299_;
}
}
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00__private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchExactFull_spec__0_spec__0___boxed(lean_object* v_a_1300_, lean_object* v_c_1301_, lean_object* v_expected_1302_, lean_object* v_iters_1303_, lean_object* v___x_1304_, lean_object* v_range_1305_, lean_object* v_b_1306_, lean_object* v_i_1307_, lean_object* v_hs_1308_, lean_object* v_hl_1309_, lean_object* v___y_1310_){
_start:
{
uint32_t v_expected_boxed_1311_; lean_object* v_res_1312_; 
v_expected_boxed_1311_ = lean_unbox_uint32(v_expected_1302_);
lean_dec(v_expected_1302_);
v_res_1312_ = lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00__private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchExactFull_spec__0_spec__0(v_a_1300_, v_c_1301_, v_expected_boxed_1311_, v_iters_1303_, v___x_1304_, v_range_1305_, v_b_1306_, v_i_1307_, v_hs_1308_, v_hl_1309_);
lean_dec_ref(v_range_1305_);
return v_res_1312_;
}
}
LEAN_EXPORT uint32_t lp_competition_R24DotCostHarness_passEagerFull(lean_object* v_p_1313_, uint32_t v_s_1314_, lean_object* v_iters_1315_){
_start:
{
lean_object* v_zero_1316_; uint8_t v_isZero_1317_; 
v_zero_1316_ = lean_unsigned_to_nat(0u);
v_isZero_1317_ = lean_nat_dec_eq(v_iters_1315_, v_zero_1316_);
if (v_isZero_1317_ == 1)
{
lean_dec(v_iters_1315_);
lean_dec_ref(v_p_1313_);
return v_s_1314_;
}
else
{
lean_object* v_one_1318_; lean_object* v_n_1319_; lean_object* v_p_1320_; lean_object* v_fst_1321_; lean_object* v_snd_1322_; uint32_t v_word_1323_; uint32_t v___x_1324_; 
v_one_1318_ = lean_unsigned_to_nat(1u);
v_n_1319_ = lean_nat_sub(v_iters_1315_, v_one_1318_);
lean_dec(v_iters_1315_);
v_p_1320_ = lp_competition_R24DotBarrier_touchRaw(v_n_1319_, v_p_1313_);
v_fst_1321_ = lean_ctor_get(v_p_1320_, 0);
lean_inc(v_fst_1321_);
v_snd_1322_ = lean_ctor_get(v_p_1320_, 1);
lean_inc(v_snd_1322_);
v_word_1323_ = lp_competition_Submission_R24DotProbe_eagerFull(v_fst_1321_, v_snd_1322_);
v___x_1324_ = lean_uint32_add(v_s_1314_, v_word_1323_);
v_p_1313_ = v_p_1320_;
v_s_1314_ = v___x_1324_;
v_iters_1315_ = v_n_1319_;
goto _start;
}
}
}
LEAN_EXPORT lean_object* lp_competition_R24DotCostHarness_passEagerFull___boxed(lean_object* v_p_1326_, lean_object* v_s_1327_, lean_object* v_iters_1328_){
_start:
{
uint32_t v_s_boxed_1329_; uint32_t v_res_1330_; lean_object* v_r_1331_; 
v_s_boxed_1329_ = lean_unbox_uint32(v_s_1327_);
lean_dec(v_s_1327_);
v_res_1330_ = lp_competition_R24DotCostHarness_passEagerFull(v_p_1326_, v_s_boxed_1329_, v_iters_1328_);
v_r_1331_ = lean_box_uint32(v_res_1330_);
return v_r_1331_;
}
}
LEAN_EXPORT uint32_t lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchEagerFull_spec__0___redArg___lam__0(lean_object* v_a_1332_, lean_object* v_x_1333_){
_start:
{
lean_object* v_fst_1334_; lean_object* v_snd_1335_; uint32_t v___x_1336_; 
v_fst_1334_ = lean_ctor_get(v_a_1332_, 0);
lean_inc(v_fst_1334_);
v_snd_1335_ = lean_ctor_get(v_a_1332_, 1);
lean_inc(v_snd_1335_);
lean_dec_ref(v_a_1332_);
v___x_1336_ = lp_competition_Submission_R24DotProbe_eagerFull(v_fst_1334_, v_snd_1335_);
return v___x_1336_;
}
}
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchEagerFull_spec__0___redArg___lam__0___boxed(lean_object* v_a_1337_, lean_object* v_x_1338_){
_start:
{
uint32_t v_res_1339_; lean_object* v_r_1340_; 
v_res_1339_ = lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchEagerFull_spec__0___redArg___lam__0(v_a_1337_, v_x_1338_);
v_r_1340_ = lean_box_uint32(v_res_1339_);
return v_r_1340_;
}
}
LEAN_EXPORT uint32_t lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchEagerFull_spec__0___redArg___lam__1(lean_object* v_a_1341_, uint32_t v___x_1342_, lean_object* v_iters_1343_, lean_object* v_x_1344_){
_start:
{
uint32_t v___x_1345_; 
v___x_1345_ = lp_competition_R24DotCostHarness_passEagerFull(v_a_1341_, v___x_1342_, v_iters_1343_);
return v___x_1345_;
}
}
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchEagerFull_spec__0___redArg___lam__1___boxed(lean_object* v_a_1346_, lean_object* v___x_1347_, lean_object* v_iters_1348_, lean_object* v_x_1349_){
_start:
{
uint32_t v___x_1776__boxed_1350_; uint32_t v_res_1351_; lean_object* v_r_1352_; 
v___x_1776__boxed_1350_ = lean_unbox_uint32(v___x_1347_);
lean_dec(v___x_1347_);
v_res_1351_ = lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchEagerFull_spec__0___redArg___lam__1(v_a_1346_, v___x_1776__boxed_1350_, v_iters_1348_, v_x_1349_);
v_r_1352_ = lean_box_uint32(v_res_1351_);
return v_r_1352_;
}
}
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00__private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchEagerFull_spec__0_spec__0___redArg(lean_object* v_a_1356_, lean_object* v_c_1357_, uint32_t v_expected_1358_, lean_object* v_iters_1359_, lean_object* v___x_1360_, lean_object* v_range_1361_, lean_object* v_b_1362_, lean_object* v_i_1363_){
_start:
{
lean_object* v_stop_1365_; lean_object* v_step_1366_; uint8_t v___x_1367_; 
v_stop_1365_ = lean_ctor_get(v_range_1361_, 1);
v_step_1366_ = lean_ctor_get(v_range_1361_, 2);
v___x_1367_ = lean_nat_dec_lt(v_i_1363_, v_stop_1365_);
if (v___x_1367_ == 0)
{
lean_object* v___x_1368_; 
lean_dec(v_i_1363_);
lean_dec(v___x_1360_);
lean_dec(v_iters_1359_);
lean_dec_ref(v_c_1357_);
lean_dec_ref(v_a_1356_);
v___x_1368_ = lean_alloc_ctor(0, 1, 0);
lean_ctor_set(v___x_1368_, 0, v_b_1362_);
return v___x_1368_;
}
else
{
lean_object* v___f_1369_; lean_object* v___x_1370_; lean_object* v_a_1371_; lean_object* v_name_1372_; lean_object* v___x_1373_; uint32_t v___x_1374_; lean_object* v___x_1375_; 
lean_inc_ref(v_a_1356_);
v___f_1369_ = lean_alloc_closure((void*)(lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchEagerFull_spec__0___redArg___lam__0___boxed), 2, 1);
lean_closure_set(v___f_1369_, 0, v_a_1356_);
lean_inc_ref(v___f_1369_);
v___x_1370_ = l_IO_lazyPure___redArg(v___f_1369_);
v_a_1371_ = lean_ctor_get(v___x_1370_, 0);
lean_inc(v_a_1371_);
lean_dec_ref(v___x_1370_);
v_name_1372_ = lean_ctor_get(v_c_1357_, 0);
v___x_1373_ = ((lean_object*)(lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00__private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchEagerFull_spec__0_spec__0___redArg___closed__0));
v___x_1374_ = lean_unbox_uint32(v_a_1371_);
lean_dec(v_a_1371_);
lean_inc_ref(v_name_1372_);
v___x_1375_ = lp_competition_R24DotCostHarness_checkWord(v_name_1372_, v___x_1373_, v___x_1374_, v_expected_1358_);
if (lean_obj_tag(v___x_1375_) == 0)
{
lean_object* v___x_1376_; uint32_t v___x_1377_; lean_object* v___x_1378_; lean_object* v___f_1379_; lean_object* v___x_1380_; lean_object* v_a_1381_; lean_object* v___x_1382_; uint32_t v___x_1383_; lean_object* v___x_1384_; uint32_t v___x_1385_; lean_object* v___x_1386_; 
lean_dec_ref_known(v___x_1375_, 1);
v___x_1376_ = lean_io_mono_nanos_now();
v___x_1377_ = lp_competition_R24DotCostHarness_seed(v_i_1363_);
v___x_1378_ = lean_box_uint32(v___x_1377_);
lean_inc(v_iters_1359_);
lean_inc_ref(v_a_1356_);
v___f_1379_ = lean_alloc_closure((void*)(lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchEagerFull_spec__0___redArg___lam__1___boxed), 4, 3);
lean_closure_set(v___f_1379_, 0, v_a_1356_);
lean_closure_set(v___f_1379_, 1, v___x_1378_);
lean_closure_set(v___f_1379_, 2, v_iters_1359_);
v___x_1380_ = l_IO_lazyPure___redArg(v___f_1379_);
v_a_1381_ = lean_ctor_get(v___x_1380_, 0);
lean_inc(v_a_1381_);
lean_dec_ref(v___x_1380_);
v___x_1382_ = lean_io_mono_nanos_now();
v___x_1383_ = lp_competition_R24DotCostHarness_sinkExpected(v___x_1377_, v_expected_1358_, v_iters_1359_);
v___x_1384_ = ((lean_object*)(lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00__private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchEagerFull_spec__0_spec__0___redArg___closed__1));
v___x_1385_ = lean_unbox_uint32(v_a_1381_);
lean_inc_ref(v_name_1372_);
v___x_1386_ = lp_competition_R24DotCostHarness_checkWord(v_name_1372_, v___x_1384_, v___x_1385_, v___x_1383_);
if (lean_obj_tag(v___x_1386_) == 0)
{
lean_object* v___x_1387_; lean_object* v_a_1388_; lean_object* v___x_1389_; uint32_t v___x_1390_; lean_object* v___x_1391_; 
lean_dec_ref_known(v___x_1386_, 1);
v___x_1387_ = l_IO_lazyPure___redArg(v___f_1369_);
v_a_1388_ = lean_ctor_get(v___x_1387_, 0);
lean_inc(v_a_1388_);
lean_dec_ref(v___x_1387_);
v___x_1389_ = ((lean_object*)(lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00__private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchEagerFull_spec__0_spec__0___redArg___closed__2));
v___x_1390_ = lean_unbox_uint32(v_a_1388_);
lean_inc_ref(v_name_1372_);
v___x_1391_ = lp_competition_R24DotCostHarness_checkWord(v_name_1372_, v___x_1389_, v___x_1390_, v_expected_1358_);
if (lean_obj_tag(v___x_1391_) == 0)
{
lean_object* v___x_1392_; lean_object* v___x_1393_; uint32_t v___x_1394_; uint32_t v___x_1395_; lean_object* v___x_1396_; lean_object* v___x_1397_; 
lean_dec_ref_known(v___x_1391_, 1);
v___x_1392_ = lean_nat_sub(v___x_1382_, v___x_1376_);
lean_dec(v___x_1376_);
lean_dec(v___x_1382_);
lean_inc(v_iters_1359_);
lean_inc(v___x_1360_);
lean_inc(v_i_1363_);
v___x_1393_ = lean_alloc_ctor(0, 4, 12);
lean_ctor_set(v___x_1393_, 0, v_i_1363_);
lean_ctor_set(v___x_1393_, 1, v___x_1360_);
lean_ctor_set(v___x_1393_, 2, v_iters_1359_);
lean_ctor_set(v___x_1393_, 3, v___x_1392_);
v___x_1394_ = lean_unbox_uint32(v_a_1381_);
lean_dec(v_a_1381_);
lean_ctor_set_uint32(v___x_1393_, sizeof(void*)*4, v___x_1394_);
lean_ctor_set_uint32(v___x_1393_, sizeof(void*)*4 + 4, v___x_1383_);
v___x_1395_ = lean_unbox_uint32(v_a_1388_);
lean_dec(v_a_1388_);
lean_ctor_set_uint32(v___x_1393_, sizeof(void*)*4 + 8, v___x_1395_);
v___x_1396_ = lean_array_push(v_b_1362_, v___x_1393_);
v___x_1397_ = lean_nat_add(v_i_1363_, v_step_1366_);
lean_dec(v_i_1363_);
v_b_1362_ = v___x_1396_;
v_i_1363_ = v___x_1397_;
goto _start;
}
else
{
lean_object* v_a_1399_; lean_object* v___x_1401_; uint8_t v_isShared_1402_; uint8_t v_isSharedCheck_1406_; 
lean_dec(v_a_1388_);
lean_dec(v___x_1382_);
lean_dec(v_a_1381_);
lean_dec(v___x_1376_);
lean_dec(v_i_1363_);
lean_dec_ref(v_b_1362_);
lean_dec(v___x_1360_);
lean_dec(v_iters_1359_);
lean_dec_ref(v_c_1357_);
lean_dec_ref(v_a_1356_);
v_a_1399_ = lean_ctor_get(v___x_1391_, 0);
v_isSharedCheck_1406_ = !lean_is_exclusive(v___x_1391_);
if (v_isSharedCheck_1406_ == 0)
{
v___x_1401_ = v___x_1391_;
v_isShared_1402_ = v_isSharedCheck_1406_;
goto v_resetjp_1400_;
}
else
{
lean_inc(v_a_1399_);
lean_dec(v___x_1391_);
v___x_1401_ = lean_box(0);
v_isShared_1402_ = v_isSharedCheck_1406_;
goto v_resetjp_1400_;
}
v_resetjp_1400_:
{
lean_object* v___x_1404_; 
if (v_isShared_1402_ == 0)
{
v___x_1404_ = v___x_1401_;
goto v_reusejp_1403_;
}
else
{
lean_object* v_reuseFailAlloc_1405_; 
v_reuseFailAlloc_1405_ = lean_alloc_ctor(1, 1, 0);
lean_ctor_set(v_reuseFailAlloc_1405_, 0, v_a_1399_);
v___x_1404_ = v_reuseFailAlloc_1405_;
goto v_reusejp_1403_;
}
v_reusejp_1403_:
{
return v___x_1404_;
}
}
}
}
else
{
lean_object* v_a_1407_; lean_object* v___x_1409_; uint8_t v_isShared_1410_; uint8_t v_isSharedCheck_1414_; 
lean_dec(v___x_1382_);
lean_dec(v_a_1381_);
lean_dec(v___x_1376_);
lean_dec_ref(v___f_1369_);
lean_dec(v_i_1363_);
lean_dec_ref(v_b_1362_);
lean_dec(v___x_1360_);
lean_dec(v_iters_1359_);
lean_dec_ref(v_c_1357_);
lean_dec_ref(v_a_1356_);
v_a_1407_ = lean_ctor_get(v___x_1386_, 0);
v_isSharedCheck_1414_ = !lean_is_exclusive(v___x_1386_);
if (v_isSharedCheck_1414_ == 0)
{
v___x_1409_ = v___x_1386_;
v_isShared_1410_ = v_isSharedCheck_1414_;
goto v_resetjp_1408_;
}
else
{
lean_inc(v_a_1407_);
lean_dec(v___x_1386_);
v___x_1409_ = lean_box(0);
v_isShared_1410_ = v_isSharedCheck_1414_;
goto v_resetjp_1408_;
}
v_resetjp_1408_:
{
lean_object* v___x_1412_; 
if (v_isShared_1410_ == 0)
{
v___x_1412_ = v___x_1409_;
goto v_reusejp_1411_;
}
else
{
lean_object* v_reuseFailAlloc_1413_; 
v_reuseFailAlloc_1413_ = lean_alloc_ctor(1, 1, 0);
lean_ctor_set(v_reuseFailAlloc_1413_, 0, v_a_1407_);
v___x_1412_ = v_reuseFailAlloc_1413_;
goto v_reusejp_1411_;
}
v_reusejp_1411_:
{
return v___x_1412_;
}
}
}
}
else
{
lean_object* v_a_1415_; lean_object* v___x_1417_; uint8_t v_isShared_1418_; uint8_t v_isSharedCheck_1422_; 
lean_dec_ref(v___f_1369_);
lean_dec(v_i_1363_);
lean_dec_ref(v_b_1362_);
lean_dec(v___x_1360_);
lean_dec(v_iters_1359_);
lean_dec_ref(v_c_1357_);
lean_dec_ref(v_a_1356_);
v_a_1415_ = lean_ctor_get(v___x_1375_, 0);
v_isSharedCheck_1422_ = !lean_is_exclusive(v___x_1375_);
if (v_isSharedCheck_1422_ == 0)
{
v___x_1417_ = v___x_1375_;
v_isShared_1418_ = v_isSharedCheck_1422_;
goto v_resetjp_1416_;
}
else
{
lean_inc(v_a_1415_);
lean_dec(v___x_1375_);
v___x_1417_ = lean_box(0);
v_isShared_1418_ = v_isSharedCheck_1422_;
goto v_resetjp_1416_;
}
v_resetjp_1416_:
{
lean_object* v___x_1420_; 
if (v_isShared_1418_ == 0)
{
v___x_1420_ = v___x_1417_;
goto v_reusejp_1419_;
}
else
{
lean_object* v_reuseFailAlloc_1421_; 
v_reuseFailAlloc_1421_ = lean_alloc_ctor(1, 1, 0);
lean_ctor_set(v_reuseFailAlloc_1421_, 0, v_a_1415_);
v___x_1420_ = v_reuseFailAlloc_1421_;
goto v_reusejp_1419_;
}
v_reusejp_1419_:
{
return v___x_1420_;
}
}
}
}
}
}
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00__private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchEagerFull_spec__0_spec__0___redArg___boxed(lean_object* v_a_1423_, lean_object* v_c_1424_, lean_object* v_expected_1425_, lean_object* v_iters_1426_, lean_object* v___x_1427_, lean_object* v_range_1428_, lean_object* v_b_1429_, lean_object* v_i_1430_, lean_object* v___y_1431_){
_start:
{
uint32_t v_expected_boxed_1432_; lean_object* v_res_1433_; 
v_expected_boxed_1432_ = lean_unbox_uint32(v_expected_1425_);
lean_dec(v_expected_1425_);
v_res_1433_ = lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00__private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchEagerFull_spec__0_spec__0___redArg(v_a_1423_, v_c_1424_, v_expected_boxed_1432_, v_iters_1426_, v___x_1427_, v_range_1428_, v_b_1429_, v_i_1430_);
lean_dec_ref(v_range_1428_);
return v_res_1433_;
}
}
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchEagerFull_spec__0___redArg(lean_object* v_a_1434_, lean_object* v_c_1435_, uint32_t v_expected_1436_, lean_object* v_iters_1437_, lean_object* v___x_1438_, lean_object* v_range_1439_, lean_object* v_b_1440_, lean_object* v_i_1441_){
_start:
{
lean_object* v_stop_1443_; lean_object* v_step_1444_; uint8_t v___x_1445_; 
v_stop_1443_ = lean_ctor_get(v_range_1439_, 1);
v_step_1444_ = lean_ctor_get(v_range_1439_, 2);
v___x_1445_ = lean_nat_dec_lt(v_i_1441_, v_stop_1443_);
if (v___x_1445_ == 0)
{
lean_object* v___x_1446_; 
lean_dec(v_i_1441_);
lean_dec(v___x_1438_);
lean_dec(v_iters_1437_);
lean_dec_ref(v_c_1435_);
lean_dec_ref(v_a_1434_);
v___x_1446_ = lean_alloc_ctor(0, 1, 0);
lean_ctor_set(v___x_1446_, 0, v_b_1440_);
return v___x_1446_;
}
else
{
lean_object* v___f_1447_; lean_object* v___x_1448_; lean_object* v_a_1449_; lean_object* v_name_1450_; lean_object* v___x_1451_; uint32_t v___x_1452_; lean_object* v___x_1453_; 
lean_inc_ref(v_a_1434_);
v___f_1447_ = lean_alloc_closure((void*)(lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchEagerFull_spec__0___redArg___lam__0___boxed), 2, 1);
lean_closure_set(v___f_1447_, 0, v_a_1434_);
lean_inc_ref(v___f_1447_);
v___x_1448_ = l_IO_lazyPure___redArg(v___f_1447_);
v_a_1449_ = lean_ctor_get(v___x_1448_, 0);
lean_inc(v_a_1449_);
lean_dec_ref(v___x_1448_);
v_name_1450_ = lean_ctor_get(v_c_1435_, 0);
v___x_1451_ = ((lean_object*)(lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00__private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchEagerFull_spec__0_spec__0___redArg___closed__0));
v___x_1452_ = lean_unbox_uint32(v_a_1449_);
lean_dec(v_a_1449_);
lean_inc_ref(v_name_1450_);
v___x_1453_ = lp_competition_R24DotCostHarness_checkWord(v_name_1450_, v___x_1451_, v___x_1452_, v_expected_1436_);
if (lean_obj_tag(v___x_1453_) == 0)
{
lean_object* v___x_1454_; uint32_t v___x_1455_; lean_object* v___x_1456_; lean_object* v___f_1457_; lean_object* v___x_1458_; lean_object* v_a_1459_; lean_object* v___x_1460_; uint32_t v___x_1461_; lean_object* v___x_1462_; uint32_t v___x_1463_; lean_object* v___x_1464_; 
lean_dec_ref_known(v___x_1453_, 1);
v___x_1454_ = lean_io_mono_nanos_now();
v___x_1455_ = lp_competition_R24DotCostHarness_seed(v_i_1441_);
v___x_1456_ = lean_box_uint32(v___x_1455_);
lean_inc(v_iters_1437_);
lean_inc_ref(v_a_1434_);
v___f_1457_ = lean_alloc_closure((void*)(lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchEagerFull_spec__0___redArg___lam__1___boxed), 4, 3);
lean_closure_set(v___f_1457_, 0, v_a_1434_);
lean_closure_set(v___f_1457_, 1, v___x_1456_);
lean_closure_set(v___f_1457_, 2, v_iters_1437_);
v___x_1458_ = l_IO_lazyPure___redArg(v___f_1457_);
v_a_1459_ = lean_ctor_get(v___x_1458_, 0);
lean_inc(v_a_1459_);
lean_dec_ref(v___x_1458_);
v___x_1460_ = lean_io_mono_nanos_now();
v___x_1461_ = lp_competition_R24DotCostHarness_sinkExpected(v___x_1455_, v_expected_1436_, v_iters_1437_);
v___x_1462_ = ((lean_object*)(lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00__private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchEagerFull_spec__0_spec__0___redArg___closed__1));
v___x_1463_ = lean_unbox_uint32(v_a_1459_);
lean_inc_ref(v_name_1450_);
v___x_1464_ = lp_competition_R24DotCostHarness_checkWord(v_name_1450_, v___x_1462_, v___x_1463_, v___x_1461_);
if (lean_obj_tag(v___x_1464_) == 0)
{
lean_object* v___x_1465_; lean_object* v_a_1466_; lean_object* v___x_1467_; uint32_t v___x_1468_; lean_object* v___x_1469_; 
lean_dec_ref_known(v___x_1464_, 1);
v___x_1465_ = l_IO_lazyPure___redArg(v___f_1447_);
v_a_1466_ = lean_ctor_get(v___x_1465_, 0);
lean_inc(v_a_1466_);
lean_dec_ref(v___x_1465_);
v___x_1467_ = ((lean_object*)(lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00__private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchEagerFull_spec__0_spec__0___redArg___closed__2));
v___x_1468_ = lean_unbox_uint32(v_a_1466_);
lean_inc_ref(v_name_1450_);
v___x_1469_ = lp_competition_R24DotCostHarness_checkWord(v_name_1450_, v___x_1467_, v___x_1468_, v_expected_1436_);
if (lean_obj_tag(v___x_1469_) == 0)
{
lean_object* v___x_1470_; lean_object* v___x_1471_; uint32_t v___x_1472_; uint32_t v___x_1473_; lean_object* v___x_1474_; lean_object* v___x_1475_; lean_object* v___x_1476_; 
lean_dec_ref_known(v___x_1469_, 1);
v___x_1470_ = lean_nat_sub(v___x_1460_, v___x_1454_);
lean_dec(v___x_1454_);
lean_dec(v___x_1460_);
lean_inc(v_iters_1437_);
lean_inc(v___x_1438_);
lean_inc(v_i_1441_);
v___x_1471_ = lean_alloc_ctor(0, 4, 12);
lean_ctor_set(v___x_1471_, 0, v_i_1441_);
lean_ctor_set(v___x_1471_, 1, v___x_1438_);
lean_ctor_set(v___x_1471_, 2, v_iters_1437_);
lean_ctor_set(v___x_1471_, 3, v___x_1470_);
v___x_1472_ = lean_unbox_uint32(v_a_1459_);
lean_dec(v_a_1459_);
lean_ctor_set_uint32(v___x_1471_, sizeof(void*)*4, v___x_1472_);
lean_ctor_set_uint32(v___x_1471_, sizeof(void*)*4 + 4, v___x_1461_);
v___x_1473_ = lean_unbox_uint32(v_a_1466_);
lean_dec(v_a_1466_);
lean_ctor_set_uint32(v___x_1471_, sizeof(void*)*4 + 8, v___x_1473_);
v___x_1474_ = lean_array_push(v_b_1440_, v___x_1471_);
v___x_1475_ = lean_nat_add(v_i_1441_, v_step_1444_);
lean_dec(v_i_1441_);
v___x_1476_ = lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00__private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchEagerFull_spec__0_spec__0___redArg(v_a_1434_, v_c_1435_, v_expected_1436_, v_iters_1437_, v___x_1438_, v_range_1439_, v___x_1474_, v___x_1475_);
return v___x_1476_;
}
else
{
lean_object* v_a_1477_; lean_object* v___x_1479_; uint8_t v_isShared_1480_; uint8_t v_isSharedCheck_1484_; 
lean_dec(v_a_1466_);
lean_dec(v___x_1460_);
lean_dec(v_a_1459_);
lean_dec(v___x_1454_);
lean_dec(v_i_1441_);
lean_dec_ref(v_b_1440_);
lean_dec(v___x_1438_);
lean_dec(v_iters_1437_);
lean_dec_ref(v_c_1435_);
lean_dec_ref(v_a_1434_);
v_a_1477_ = lean_ctor_get(v___x_1469_, 0);
v_isSharedCheck_1484_ = !lean_is_exclusive(v___x_1469_);
if (v_isSharedCheck_1484_ == 0)
{
v___x_1479_ = v___x_1469_;
v_isShared_1480_ = v_isSharedCheck_1484_;
goto v_resetjp_1478_;
}
else
{
lean_inc(v_a_1477_);
lean_dec(v___x_1469_);
v___x_1479_ = lean_box(0);
v_isShared_1480_ = v_isSharedCheck_1484_;
goto v_resetjp_1478_;
}
v_resetjp_1478_:
{
lean_object* v___x_1482_; 
if (v_isShared_1480_ == 0)
{
v___x_1482_ = v___x_1479_;
goto v_reusejp_1481_;
}
else
{
lean_object* v_reuseFailAlloc_1483_; 
v_reuseFailAlloc_1483_ = lean_alloc_ctor(1, 1, 0);
lean_ctor_set(v_reuseFailAlloc_1483_, 0, v_a_1477_);
v___x_1482_ = v_reuseFailAlloc_1483_;
goto v_reusejp_1481_;
}
v_reusejp_1481_:
{
return v___x_1482_;
}
}
}
}
else
{
lean_object* v_a_1485_; lean_object* v___x_1487_; uint8_t v_isShared_1488_; uint8_t v_isSharedCheck_1492_; 
lean_dec(v___x_1460_);
lean_dec(v_a_1459_);
lean_dec(v___x_1454_);
lean_dec_ref(v___f_1447_);
lean_dec(v_i_1441_);
lean_dec_ref(v_b_1440_);
lean_dec(v___x_1438_);
lean_dec(v_iters_1437_);
lean_dec_ref(v_c_1435_);
lean_dec_ref(v_a_1434_);
v_a_1485_ = lean_ctor_get(v___x_1464_, 0);
v_isSharedCheck_1492_ = !lean_is_exclusive(v___x_1464_);
if (v_isSharedCheck_1492_ == 0)
{
v___x_1487_ = v___x_1464_;
v_isShared_1488_ = v_isSharedCheck_1492_;
goto v_resetjp_1486_;
}
else
{
lean_inc(v_a_1485_);
lean_dec(v___x_1464_);
v___x_1487_ = lean_box(0);
v_isShared_1488_ = v_isSharedCheck_1492_;
goto v_resetjp_1486_;
}
v_resetjp_1486_:
{
lean_object* v___x_1490_; 
if (v_isShared_1488_ == 0)
{
v___x_1490_ = v___x_1487_;
goto v_reusejp_1489_;
}
else
{
lean_object* v_reuseFailAlloc_1491_; 
v_reuseFailAlloc_1491_ = lean_alloc_ctor(1, 1, 0);
lean_ctor_set(v_reuseFailAlloc_1491_, 0, v_a_1485_);
v___x_1490_ = v_reuseFailAlloc_1491_;
goto v_reusejp_1489_;
}
v_reusejp_1489_:
{
return v___x_1490_;
}
}
}
}
else
{
lean_object* v_a_1493_; lean_object* v___x_1495_; uint8_t v_isShared_1496_; uint8_t v_isSharedCheck_1500_; 
lean_dec_ref(v___f_1447_);
lean_dec(v_i_1441_);
lean_dec_ref(v_b_1440_);
lean_dec(v___x_1438_);
lean_dec(v_iters_1437_);
lean_dec_ref(v_c_1435_);
lean_dec_ref(v_a_1434_);
v_a_1493_ = lean_ctor_get(v___x_1453_, 0);
v_isSharedCheck_1500_ = !lean_is_exclusive(v___x_1453_);
if (v_isSharedCheck_1500_ == 0)
{
v___x_1495_ = v___x_1453_;
v_isShared_1496_ = v_isSharedCheck_1500_;
goto v_resetjp_1494_;
}
else
{
lean_inc(v_a_1493_);
lean_dec(v___x_1453_);
v___x_1495_ = lean_box(0);
v_isShared_1496_ = v_isSharedCheck_1500_;
goto v_resetjp_1494_;
}
v_resetjp_1494_:
{
lean_object* v___x_1498_; 
if (v_isShared_1496_ == 0)
{
v___x_1498_ = v___x_1495_;
goto v_reusejp_1497_;
}
else
{
lean_object* v_reuseFailAlloc_1499_; 
v_reuseFailAlloc_1499_ = lean_alloc_ctor(1, 1, 0);
lean_ctor_set(v_reuseFailAlloc_1499_, 0, v_a_1493_);
v___x_1498_ = v_reuseFailAlloc_1499_;
goto v_reusejp_1497_;
}
v_reusejp_1497_:
{
return v___x_1498_;
}
}
}
}
}
}
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchEagerFull_spec__0___redArg___boxed(lean_object* v_a_1501_, lean_object* v_c_1502_, lean_object* v_expected_1503_, lean_object* v_iters_1504_, lean_object* v___x_1505_, lean_object* v_range_1506_, lean_object* v_b_1507_, lean_object* v_i_1508_, lean_object* v___y_1509_){
_start:
{
uint32_t v_expected_boxed_1510_; lean_object* v_res_1511_; 
v_expected_boxed_1510_ = lean_unbox_uint32(v_expected_1503_);
lean_dec(v_expected_1503_);
v_res_1511_ = lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchEagerFull_spec__0___redArg(v_a_1501_, v_c_1502_, v_expected_boxed_1510_, v_iters_1504_, v___x_1505_, v_range_1506_, v_b_1507_, v_i_1508_);
lean_dec_ref(v_range_1506_);
return v_res_1511_;
}
}
LEAN_EXPORT lean_object* lp_competition_R24DotCostHarness_benchEagerFull(lean_object* v_c_1513_, lean_object* v_a_1514_, lean_object* v_b_1515_, lean_object* v_macs_1516_){
_start:
{
lean_object* v___x_1518_; lean_object* v_a_1519_; lean_object* v___x_1520_; lean_object* v___f_1521_; lean_object* v___x_1522_; lean_object* v_a_1523_; lean_object* v___x_1524_; lean_object* v_expected_1525_; uint32_t v_expected_1526_; lean_object* v___x_1527_; lean_object* v_iters_1528_; lean_object* v___x_1529_; lean_object* v___x_1530_; lean_object* v___x_1531_; lean_object* v___x_1532_; 
v___x_1518_ = lp_competition_R24DotCostHarness_benchExactFull___lam__0();
v_a_1519_ = lean_ctor_get(v___x_1518_, 0);
lean_inc(v_a_1519_);
lean_dec_ref(v___x_1518_);
v___x_1520_ = lp_competition_R24DotCostHarness_benchExactFull___lam__0();
lean_dec_ref(v___x_1520_);
lean_inc_ref(v_a_1514_);
v___f_1521_ = lean_alloc_closure((void*)(lp_competition_R24DotCostHarness_benchExactFull___lam__1), 3, 2);
lean_closure_set(v___f_1521_, 0, v_a_1514_);
lean_closure_set(v___f_1521_, 1, v_b_1515_);
v___x_1522_ = l_IO_lazyPure___redArg(v___f_1521_);
v_a_1523_ = lean_ctor_get(v___x_1522_, 0);
lean_inc(v_a_1523_);
lean_dec_ref(v___x_1522_);
v___x_1524_ = lp_competition_R24DotCostHarness_benchExactFull___lam__0();
lean_dec_ref(v___x_1524_);
v_expected_1525_ = lean_ctor_get(v_c_1513_, 5);
v_expected_1526_ = lean_uint32_of_nat(v_expected_1525_);
v___x_1527_ = lean_array_get_size(v_a_1514_);
lean_dec_ref(v_a_1514_);
v_iters_1528_ = lp_competition_R24DotCostHarness_repeats(v_macs_1516_, v___x_1527_);
v___x_1529_ = lean_unsigned_to_nat(0u);
v___x_1530_ = ((lean_object*)(lp_competition_R24DotCostHarness_benchExactFull___closed__0));
v___x_1531_ = ((lean_object*)(lp_competition_R24DotCostHarness_benchExactFull___closed__1));
lean_inc_ref(v_c_1513_);
v___x_1532_ = lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchEagerFull_spec__0___redArg(v_a_1523_, v_c_1513_, v_expected_1526_, v_iters_1528_, v___x_1527_, v___x_1531_, v___x_1530_, v___x_1529_);
if (lean_obj_tag(v___x_1532_) == 0)
{
lean_object* v_a_1533_; lean_object* v___x_1534_; lean_object* v_a_1535_; lean_object* v___x_1536_; lean_object* v___x_1537_; lean_object* v___x_1538_; lean_object* v___x_1539_; 
v_a_1533_ = lean_ctor_get(v___x_1532_, 0);
lean_inc(v_a_1533_);
lean_dec_ref_known(v___x_1532_, 1);
v___x_1534_ = lp_competition_R24DotCostHarness_benchExactFull___lam__0();
v_a_1535_ = lean_ctor_get(v___x_1534_, 0);
lean_inc(v_a_1535_);
lean_dec_ref(v___x_1534_);
v___x_1536_ = ((lean_object*)(lp_competition_R24DotCostHarness_benchEagerFull___closed__0));
v___x_1537_ = ((lean_object*)(lp_competition_R24DotCostHarness_benchExactFull___closed__3));
v___x_1538_ = lean_nat_sub(v_a_1535_, v_a_1519_);
lean_dec(v_a_1519_);
lean_dec(v_a_1535_);
v___x_1539_ = lp_competition_R24DotCostHarness_emit(v_c_1513_, v___x_1536_, v___x_1537_, v___x_1529_, v___x_1538_, v_a_1533_);
lean_dec(v_a_1533_);
lean_dec_ref(v_c_1513_);
return v___x_1539_;
}
else
{
lean_object* v_a_1540_; lean_object* v___x_1542_; uint8_t v_isShared_1543_; uint8_t v_isSharedCheck_1547_; 
lean_dec(v_a_1519_);
lean_dec_ref(v_c_1513_);
v_a_1540_ = lean_ctor_get(v___x_1532_, 0);
v_isSharedCheck_1547_ = !lean_is_exclusive(v___x_1532_);
if (v_isSharedCheck_1547_ == 0)
{
v___x_1542_ = v___x_1532_;
v_isShared_1543_ = v_isSharedCheck_1547_;
goto v_resetjp_1541_;
}
else
{
lean_inc(v_a_1540_);
lean_dec(v___x_1532_);
v___x_1542_ = lean_box(0);
v_isShared_1543_ = v_isSharedCheck_1547_;
goto v_resetjp_1541_;
}
v_resetjp_1541_:
{
lean_object* v___x_1545_; 
if (v_isShared_1543_ == 0)
{
v___x_1545_ = v___x_1542_;
goto v_reusejp_1544_;
}
else
{
lean_object* v_reuseFailAlloc_1546_; 
v_reuseFailAlloc_1546_ = lean_alloc_ctor(1, 1, 0);
lean_ctor_set(v_reuseFailAlloc_1546_, 0, v_a_1540_);
v___x_1545_ = v_reuseFailAlloc_1546_;
goto v_reusejp_1544_;
}
v_reusejp_1544_:
{
return v___x_1545_;
}
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_R24DotCostHarness_benchEagerFull___boxed(lean_object* v_c_1548_, lean_object* v_a_1549_, lean_object* v_b_1550_, lean_object* v_macs_1551_, lean_object* v_a_1552_){
_start:
{
lean_object* v_res_1553_; 
v_res_1553_ = lp_competition_R24DotCostHarness_benchEagerFull(v_c_1548_, v_a_1549_, v_b_1550_, v_macs_1551_);
lean_dec(v_macs_1551_);
return v_res_1553_;
}
}
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchEagerFull_spec__0(lean_object* v_a_1554_, lean_object* v_c_1555_, uint32_t v_expected_1556_, lean_object* v_iters_1557_, lean_object* v___x_1558_, lean_object* v_range_1559_, lean_object* v_b_1560_, lean_object* v_i_1561_, lean_object* v_hs_1562_, lean_object* v_hl_1563_){
_start:
{
lean_object* v___x_1565_; 
v___x_1565_ = lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchEagerFull_spec__0___redArg(v_a_1554_, v_c_1555_, v_expected_1556_, v_iters_1557_, v___x_1558_, v_range_1559_, v_b_1560_, v_i_1561_);
return v___x_1565_;
}
}
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchEagerFull_spec__0___boxed(lean_object* v_a_1566_, lean_object* v_c_1567_, lean_object* v_expected_1568_, lean_object* v_iters_1569_, lean_object* v___x_1570_, lean_object* v_range_1571_, lean_object* v_b_1572_, lean_object* v_i_1573_, lean_object* v_hs_1574_, lean_object* v_hl_1575_, lean_object* v___y_1576_){
_start:
{
uint32_t v_expected_boxed_1577_; lean_object* v_res_1578_; 
v_expected_boxed_1577_ = lean_unbox_uint32(v_expected_1568_);
lean_dec(v_expected_1568_);
v_res_1578_ = lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchEagerFull_spec__0(v_a_1566_, v_c_1567_, v_expected_boxed_1577_, v_iters_1569_, v___x_1570_, v_range_1571_, v_b_1572_, v_i_1573_, v_hs_1574_, v_hl_1575_);
lean_dec_ref(v_range_1571_);
return v_res_1578_;
}
}
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00__private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchEagerFull_spec__0_spec__0(lean_object* v_a_1579_, lean_object* v_c_1580_, uint32_t v_expected_1581_, lean_object* v_iters_1582_, lean_object* v___x_1583_, lean_object* v_range_1584_, lean_object* v_b_1585_, lean_object* v_i_1586_, lean_object* v_hs_1587_, lean_object* v_hl_1588_){
_start:
{
lean_object* v___x_1590_; 
v___x_1590_ = lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00__private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchEagerFull_spec__0_spec__0___redArg(v_a_1579_, v_c_1580_, v_expected_1581_, v_iters_1582_, v___x_1583_, v_range_1584_, v_b_1585_, v_i_1586_);
return v___x_1590_;
}
}
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00__private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchEagerFull_spec__0_spec__0___boxed(lean_object* v_a_1591_, lean_object* v_c_1592_, lean_object* v_expected_1593_, lean_object* v_iters_1594_, lean_object* v___x_1595_, lean_object* v_range_1596_, lean_object* v_b_1597_, lean_object* v_i_1598_, lean_object* v_hs_1599_, lean_object* v_hl_1600_, lean_object* v___y_1601_){
_start:
{
uint32_t v_expected_boxed_1602_; lean_object* v_res_1603_; 
v_expected_boxed_1602_ = lean_unbox_uint32(v_expected_1593_);
lean_dec(v_expected_1593_);
v_res_1603_ = lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00__private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchEagerFull_spec__0_spec__0(v_a_1591_, v_c_1592_, v_expected_boxed_1602_, v_iters_1594_, v___x_1595_, v_range_1596_, v_b_1597_, v_i_1598_, v_hs_1599_, v_hl_1600_);
lean_dec_ref(v_range_1596_);
return v_res_1603_;
}
}
LEAN_EXPORT uint32_t lp_competition_R24DotCostHarness_passLazyFull(lean_object* v_p_1604_, uint32_t v_s_1605_, lean_object* v_iters_1606_){
_start:
{
lean_object* v_zero_1607_; uint8_t v_isZero_1608_; 
v_zero_1607_ = lean_unsigned_to_nat(0u);
v_isZero_1608_ = lean_nat_dec_eq(v_iters_1606_, v_zero_1607_);
if (v_isZero_1608_ == 1)
{
lean_dec(v_iters_1606_);
lean_dec_ref(v_p_1604_);
return v_s_1605_;
}
else
{
lean_object* v_one_1609_; lean_object* v_n_1610_; lean_object* v_p_1611_; lean_object* v_fst_1612_; lean_object* v_snd_1613_; uint32_t v_word_1614_; uint32_t v___x_1615_; 
v_one_1609_ = lean_unsigned_to_nat(1u);
v_n_1610_ = lean_nat_sub(v_iters_1606_, v_one_1609_);
lean_dec(v_iters_1606_);
v_p_1611_ = lp_competition_R24DotBarrier_touchRaw(v_n_1610_, v_p_1604_);
v_fst_1612_ = lean_ctor_get(v_p_1611_, 0);
lean_inc(v_fst_1612_);
v_snd_1613_ = lean_ctor_get(v_p_1611_, 1);
lean_inc(v_snd_1613_);
v_word_1614_ = lp_competition_Submission_R24DotProbe_lazyFull(v_fst_1612_, v_snd_1613_);
v___x_1615_ = lean_uint32_add(v_s_1605_, v_word_1614_);
v_p_1604_ = v_p_1611_;
v_s_1605_ = v___x_1615_;
v_iters_1606_ = v_n_1610_;
goto _start;
}
}
}
LEAN_EXPORT lean_object* lp_competition_R24DotCostHarness_passLazyFull___boxed(lean_object* v_p_1617_, lean_object* v_s_1618_, lean_object* v_iters_1619_){
_start:
{
uint32_t v_s_boxed_1620_; uint32_t v_res_1621_; lean_object* v_r_1622_; 
v_s_boxed_1620_ = lean_unbox_uint32(v_s_1618_);
lean_dec(v_s_1618_);
v_res_1621_ = lp_competition_R24DotCostHarness_passLazyFull(v_p_1617_, v_s_boxed_1620_, v_iters_1619_);
v_r_1622_ = lean_box_uint32(v_res_1621_);
return v_r_1622_;
}
}
LEAN_EXPORT uint32_t lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchLazyFull_spec__0___redArg___lam__1(lean_object* v_a_1623_, uint32_t v___x_1624_, lean_object* v_iters_1625_, lean_object* v_x_1626_){
_start:
{
uint32_t v___x_1627_; 
v___x_1627_ = lp_competition_R24DotCostHarness_passLazyFull(v_a_1623_, v___x_1624_, v_iters_1625_);
return v___x_1627_;
}
}
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchLazyFull_spec__0___redArg___lam__1___boxed(lean_object* v_a_1628_, lean_object* v___x_1629_, lean_object* v_iters_1630_, lean_object* v_x_1631_){
_start:
{
uint32_t v___x_1768__boxed_1632_; uint32_t v_res_1633_; lean_object* v_r_1634_; 
v___x_1768__boxed_1632_ = lean_unbox_uint32(v___x_1629_);
lean_dec(v___x_1629_);
v_res_1633_ = lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchLazyFull_spec__0___redArg___lam__1(v_a_1628_, v___x_1768__boxed_1632_, v_iters_1630_, v_x_1631_);
v_r_1634_ = lean_box_uint32(v_res_1633_);
return v_r_1634_;
}
}
LEAN_EXPORT uint32_t lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchLazyFull_spec__0___redArg___lam__0(lean_object* v_a_1635_, lean_object* v_x_1636_){
_start:
{
lean_object* v_fst_1637_; lean_object* v_snd_1638_; uint32_t v___x_1639_; 
v_fst_1637_ = lean_ctor_get(v_a_1635_, 0);
lean_inc(v_fst_1637_);
v_snd_1638_ = lean_ctor_get(v_a_1635_, 1);
lean_inc(v_snd_1638_);
lean_dec_ref(v_a_1635_);
v___x_1639_ = lp_competition_Submission_R24DotProbe_lazyFull(v_fst_1637_, v_snd_1638_);
return v___x_1639_;
}
}
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchLazyFull_spec__0___redArg___lam__0___boxed(lean_object* v_a_1640_, lean_object* v_x_1641_){
_start:
{
uint32_t v_res_1642_; lean_object* v_r_1643_; 
v_res_1642_ = lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchLazyFull_spec__0___redArg___lam__0(v_a_1640_, v_x_1641_);
v_r_1643_ = lean_box_uint32(v_res_1642_);
return v_r_1643_;
}
}
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00__private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchLazyFull_spec__0_spec__0___redArg(lean_object* v_a_1647_, lean_object* v_c_1648_, uint32_t v_expected_1649_, lean_object* v_iters_1650_, lean_object* v___x_1651_, lean_object* v_range_1652_, lean_object* v_b_1653_, lean_object* v_i_1654_){
_start:
{
lean_object* v_stop_1656_; lean_object* v_step_1657_; uint8_t v___x_1658_; 
v_stop_1656_ = lean_ctor_get(v_range_1652_, 1);
v_step_1657_ = lean_ctor_get(v_range_1652_, 2);
v___x_1658_ = lean_nat_dec_lt(v_i_1654_, v_stop_1656_);
if (v___x_1658_ == 0)
{
lean_object* v___x_1659_; 
lean_dec(v_i_1654_);
lean_dec(v___x_1651_);
lean_dec(v_iters_1650_);
lean_dec_ref(v_c_1648_);
lean_dec_ref(v_a_1647_);
v___x_1659_ = lean_alloc_ctor(0, 1, 0);
lean_ctor_set(v___x_1659_, 0, v_b_1653_);
return v___x_1659_;
}
else
{
lean_object* v___f_1660_; lean_object* v___x_1661_; lean_object* v_a_1662_; lean_object* v_name_1663_; lean_object* v___x_1664_; uint32_t v___x_1665_; lean_object* v___x_1666_; 
lean_inc_ref(v_a_1647_);
v___f_1660_ = lean_alloc_closure((void*)(lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchLazyFull_spec__0___redArg___lam__0___boxed), 2, 1);
lean_closure_set(v___f_1660_, 0, v_a_1647_);
lean_inc_ref(v___f_1660_);
v___x_1661_ = l_IO_lazyPure___redArg(v___f_1660_);
v_a_1662_ = lean_ctor_get(v___x_1661_, 0);
lean_inc(v_a_1662_);
lean_dec_ref(v___x_1661_);
v_name_1663_ = lean_ctor_get(v_c_1648_, 0);
v___x_1664_ = ((lean_object*)(lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00__private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchLazyFull_spec__0_spec__0___redArg___closed__0));
v___x_1665_ = lean_unbox_uint32(v_a_1662_);
lean_dec(v_a_1662_);
lean_inc_ref(v_name_1663_);
v___x_1666_ = lp_competition_R24DotCostHarness_checkWord(v_name_1663_, v___x_1664_, v___x_1665_, v_expected_1649_);
if (lean_obj_tag(v___x_1666_) == 0)
{
lean_object* v___x_1667_; uint32_t v___x_1668_; lean_object* v___x_1669_; lean_object* v___f_1670_; lean_object* v___x_1671_; lean_object* v_a_1672_; lean_object* v___x_1673_; uint32_t v___x_1674_; lean_object* v___x_1675_; uint32_t v___x_1676_; lean_object* v___x_1677_; 
lean_dec_ref_known(v___x_1666_, 1);
v___x_1667_ = lean_io_mono_nanos_now();
v___x_1668_ = lp_competition_R24DotCostHarness_seed(v_i_1654_);
v___x_1669_ = lean_box_uint32(v___x_1668_);
lean_inc(v_iters_1650_);
lean_inc_ref(v_a_1647_);
v___f_1670_ = lean_alloc_closure((void*)(lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchLazyFull_spec__0___redArg___lam__1___boxed), 4, 3);
lean_closure_set(v___f_1670_, 0, v_a_1647_);
lean_closure_set(v___f_1670_, 1, v___x_1669_);
lean_closure_set(v___f_1670_, 2, v_iters_1650_);
v___x_1671_ = l_IO_lazyPure___redArg(v___f_1670_);
v_a_1672_ = lean_ctor_get(v___x_1671_, 0);
lean_inc(v_a_1672_);
lean_dec_ref(v___x_1671_);
v___x_1673_ = lean_io_mono_nanos_now();
v___x_1674_ = lp_competition_R24DotCostHarness_sinkExpected(v___x_1668_, v_expected_1649_, v_iters_1650_);
v___x_1675_ = ((lean_object*)(lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00__private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchLazyFull_spec__0_spec__0___redArg___closed__1));
v___x_1676_ = lean_unbox_uint32(v_a_1672_);
lean_inc_ref(v_name_1663_);
v___x_1677_ = lp_competition_R24DotCostHarness_checkWord(v_name_1663_, v___x_1675_, v___x_1676_, v___x_1674_);
if (lean_obj_tag(v___x_1677_) == 0)
{
lean_object* v___x_1678_; lean_object* v_a_1679_; lean_object* v___x_1680_; uint32_t v___x_1681_; lean_object* v___x_1682_; 
lean_dec_ref_known(v___x_1677_, 1);
v___x_1678_ = l_IO_lazyPure___redArg(v___f_1660_);
v_a_1679_ = lean_ctor_get(v___x_1678_, 0);
lean_inc(v_a_1679_);
lean_dec_ref(v___x_1678_);
v___x_1680_ = ((lean_object*)(lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00__private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchLazyFull_spec__0_spec__0___redArg___closed__2));
v___x_1681_ = lean_unbox_uint32(v_a_1679_);
lean_inc_ref(v_name_1663_);
v___x_1682_ = lp_competition_R24DotCostHarness_checkWord(v_name_1663_, v___x_1680_, v___x_1681_, v_expected_1649_);
if (lean_obj_tag(v___x_1682_) == 0)
{
lean_object* v___x_1683_; lean_object* v___x_1684_; uint32_t v___x_1685_; uint32_t v___x_1686_; lean_object* v___x_1687_; lean_object* v___x_1688_; 
lean_dec_ref_known(v___x_1682_, 1);
v___x_1683_ = lean_nat_sub(v___x_1673_, v___x_1667_);
lean_dec(v___x_1667_);
lean_dec(v___x_1673_);
lean_inc(v_iters_1650_);
lean_inc(v___x_1651_);
lean_inc(v_i_1654_);
v___x_1684_ = lean_alloc_ctor(0, 4, 12);
lean_ctor_set(v___x_1684_, 0, v_i_1654_);
lean_ctor_set(v___x_1684_, 1, v___x_1651_);
lean_ctor_set(v___x_1684_, 2, v_iters_1650_);
lean_ctor_set(v___x_1684_, 3, v___x_1683_);
v___x_1685_ = lean_unbox_uint32(v_a_1672_);
lean_dec(v_a_1672_);
lean_ctor_set_uint32(v___x_1684_, sizeof(void*)*4, v___x_1685_);
lean_ctor_set_uint32(v___x_1684_, sizeof(void*)*4 + 4, v___x_1674_);
v___x_1686_ = lean_unbox_uint32(v_a_1679_);
lean_dec(v_a_1679_);
lean_ctor_set_uint32(v___x_1684_, sizeof(void*)*4 + 8, v___x_1686_);
v___x_1687_ = lean_array_push(v_b_1653_, v___x_1684_);
v___x_1688_ = lean_nat_add(v_i_1654_, v_step_1657_);
lean_dec(v_i_1654_);
v_b_1653_ = v___x_1687_;
v_i_1654_ = v___x_1688_;
goto _start;
}
else
{
lean_object* v_a_1690_; lean_object* v___x_1692_; uint8_t v_isShared_1693_; uint8_t v_isSharedCheck_1697_; 
lean_dec(v_a_1679_);
lean_dec(v___x_1673_);
lean_dec(v_a_1672_);
lean_dec(v___x_1667_);
lean_dec(v_i_1654_);
lean_dec_ref(v_b_1653_);
lean_dec(v___x_1651_);
lean_dec(v_iters_1650_);
lean_dec_ref(v_c_1648_);
lean_dec_ref(v_a_1647_);
v_a_1690_ = lean_ctor_get(v___x_1682_, 0);
v_isSharedCheck_1697_ = !lean_is_exclusive(v___x_1682_);
if (v_isSharedCheck_1697_ == 0)
{
v___x_1692_ = v___x_1682_;
v_isShared_1693_ = v_isSharedCheck_1697_;
goto v_resetjp_1691_;
}
else
{
lean_inc(v_a_1690_);
lean_dec(v___x_1682_);
v___x_1692_ = lean_box(0);
v_isShared_1693_ = v_isSharedCheck_1697_;
goto v_resetjp_1691_;
}
v_resetjp_1691_:
{
lean_object* v___x_1695_; 
if (v_isShared_1693_ == 0)
{
v___x_1695_ = v___x_1692_;
goto v_reusejp_1694_;
}
else
{
lean_object* v_reuseFailAlloc_1696_; 
v_reuseFailAlloc_1696_ = lean_alloc_ctor(1, 1, 0);
lean_ctor_set(v_reuseFailAlloc_1696_, 0, v_a_1690_);
v___x_1695_ = v_reuseFailAlloc_1696_;
goto v_reusejp_1694_;
}
v_reusejp_1694_:
{
return v___x_1695_;
}
}
}
}
else
{
lean_object* v_a_1698_; lean_object* v___x_1700_; uint8_t v_isShared_1701_; uint8_t v_isSharedCheck_1705_; 
lean_dec(v___x_1673_);
lean_dec(v_a_1672_);
lean_dec(v___x_1667_);
lean_dec_ref(v___f_1660_);
lean_dec(v_i_1654_);
lean_dec_ref(v_b_1653_);
lean_dec(v___x_1651_);
lean_dec(v_iters_1650_);
lean_dec_ref(v_c_1648_);
lean_dec_ref(v_a_1647_);
v_a_1698_ = lean_ctor_get(v___x_1677_, 0);
v_isSharedCheck_1705_ = !lean_is_exclusive(v___x_1677_);
if (v_isSharedCheck_1705_ == 0)
{
v___x_1700_ = v___x_1677_;
v_isShared_1701_ = v_isSharedCheck_1705_;
goto v_resetjp_1699_;
}
else
{
lean_inc(v_a_1698_);
lean_dec(v___x_1677_);
v___x_1700_ = lean_box(0);
v_isShared_1701_ = v_isSharedCheck_1705_;
goto v_resetjp_1699_;
}
v_resetjp_1699_:
{
lean_object* v___x_1703_; 
if (v_isShared_1701_ == 0)
{
v___x_1703_ = v___x_1700_;
goto v_reusejp_1702_;
}
else
{
lean_object* v_reuseFailAlloc_1704_; 
v_reuseFailAlloc_1704_ = lean_alloc_ctor(1, 1, 0);
lean_ctor_set(v_reuseFailAlloc_1704_, 0, v_a_1698_);
v___x_1703_ = v_reuseFailAlloc_1704_;
goto v_reusejp_1702_;
}
v_reusejp_1702_:
{
return v___x_1703_;
}
}
}
}
else
{
lean_object* v_a_1706_; lean_object* v___x_1708_; uint8_t v_isShared_1709_; uint8_t v_isSharedCheck_1713_; 
lean_dec_ref(v___f_1660_);
lean_dec(v_i_1654_);
lean_dec_ref(v_b_1653_);
lean_dec(v___x_1651_);
lean_dec(v_iters_1650_);
lean_dec_ref(v_c_1648_);
lean_dec_ref(v_a_1647_);
v_a_1706_ = lean_ctor_get(v___x_1666_, 0);
v_isSharedCheck_1713_ = !lean_is_exclusive(v___x_1666_);
if (v_isSharedCheck_1713_ == 0)
{
v___x_1708_ = v___x_1666_;
v_isShared_1709_ = v_isSharedCheck_1713_;
goto v_resetjp_1707_;
}
else
{
lean_inc(v_a_1706_);
lean_dec(v___x_1666_);
v___x_1708_ = lean_box(0);
v_isShared_1709_ = v_isSharedCheck_1713_;
goto v_resetjp_1707_;
}
v_resetjp_1707_:
{
lean_object* v___x_1711_; 
if (v_isShared_1709_ == 0)
{
v___x_1711_ = v___x_1708_;
goto v_reusejp_1710_;
}
else
{
lean_object* v_reuseFailAlloc_1712_; 
v_reuseFailAlloc_1712_ = lean_alloc_ctor(1, 1, 0);
lean_ctor_set(v_reuseFailAlloc_1712_, 0, v_a_1706_);
v___x_1711_ = v_reuseFailAlloc_1712_;
goto v_reusejp_1710_;
}
v_reusejp_1710_:
{
return v___x_1711_;
}
}
}
}
}
}
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00__private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchLazyFull_spec__0_spec__0___redArg___boxed(lean_object* v_a_1714_, lean_object* v_c_1715_, lean_object* v_expected_1716_, lean_object* v_iters_1717_, lean_object* v___x_1718_, lean_object* v_range_1719_, lean_object* v_b_1720_, lean_object* v_i_1721_, lean_object* v___y_1722_){
_start:
{
uint32_t v_expected_boxed_1723_; lean_object* v_res_1724_; 
v_expected_boxed_1723_ = lean_unbox_uint32(v_expected_1716_);
lean_dec(v_expected_1716_);
v_res_1724_ = lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00__private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchLazyFull_spec__0_spec__0___redArg(v_a_1714_, v_c_1715_, v_expected_boxed_1723_, v_iters_1717_, v___x_1718_, v_range_1719_, v_b_1720_, v_i_1721_);
lean_dec_ref(v_range_1719_);
return v_res_1724_;
}
}
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchLazyFull_spec__0___redArg(lean_object* v_a_1725_, lean_object* v_c_1726_, uint32_t v_expected_1727_, lean_object* v_iters_1728_, lean_object* v___x_1729_, lean_object* v_range_1730_, lean_object* v_b_1731_, lean_object* v_i_1732_){
_start:
{
lean_object* v_stop_1734_; lean_object* v_step_1735_; uint8_t v___x_1736_; 
v_stop_1734_ = lean_ctor_get(v_range_1730_, 1);
v_step_1735_ = lean_ctor_get(v_range_1730_, 2);
v___x_1736_ = lean_nat_dec_lt(v_i_1732_, v_stop_1734_);
if (v___x_1736_ == 0)
{
lean_object* v___x_1737_; 
lean_dec(v_i_1732_);
lean_dec(v___x_1729_);
lean_dec(v_iters_1728_);
lean_dec_ref(v_c_1726_);
lean_dec_ref(v_a_1725_);
v___x_1737_ = lean_alloc_ctor(0, 1, 0);
lean_ctor_set(v___x_1737_, 0, v_b_1731_);
return v___x_1737_;
}
else
{
lean_object* v___f_1738_; lean_object* v___x_1739_; lean_object* v_a_1740_; lean_object* v_name_1741_; lean_object* v___x_1742_; uint32_t v___x_1743_; lean_object* v___x_1744_; 
lean_inc_ref(v_a_1725_);
v___f_1738_ = lean_alloc_closure((void*)(lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchLazyFull_spec__0___redArg___lam__0___boxed), 2, 1);
lean_closure_set(v___f_1738_, 0, v_a_1725_);
lean_inc_ref(v___f_1738_);
v___x_1739_ = l_IO_lazyPure___redArg(v___f_1738_);
v_a_1740_ = lean_ctor_get(v___x_1739_, 0);
lean_inc(v_a_1740_);
lean_dec_ref(v___x_1739_);
v_name_1741_ = lean_ctor_get(v_c_1726_, 0);
v___x_1742_ = ((lean_object*)(lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00__private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchLazyFull_spec__0_spec__0___redArg___closed__0));
v___x_1743_ = lean_unbox_uint32(v_a_1740_);
lean_dec(v_a_1740_);
lean_inc_ref(v_name_1741_);
v___x_1744_ = lp_competition_R24DotCostHarness_checkWord(v_name_1741_, v___x_1742_, v___x_1743_, v_expected_1727_);
if (lean_obj_tag(v___x_1744_) == 0)
{
lean_object* v___x_1745_; uint32_t v___x_1746_; lean_object* v___x_1747_; lean_object* v___f_1748_; lean_object* v___x_1749_; lean_object* v_a_1750_; lean_object* v___x_1751_; uint32_t v___x_1752_; lean_object* v___x_1753_; uint32_t v___x_1754_; lean_object* v___x_1755_; 
lean_dec_ref_known(v___x_1744_, 1);
v___x_1745_ = lean_io_mono_nanos_now();
v___x_1746_ = lp_competition_R24DotCostHarness_seed(v_i_1732_);
v___x_1747_ = lean_box_uint32(v___x_1746_);
lean_inc(v_iters_1728_);
lean_inc_ref(v_a_1725_);
v___f_1748_ = lean_alloc_closure((void*)(lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchLazyFull_spec__0___redArg___lam__1___boxed), 4, 3);
lean_closure_set(v___f_1748_, 0, v_a_1725_);
lean_closure_set(v___f_1748_, 1, v___x_1747_);
lean_closure_set(v___f_1748_, 2, v_iters_1728_);
v___x_1749_ = l_IO_lazyPure___redArg(v___f_1748_);
v_a_1750_ = lean_ctor_get(v___x_1749_, 0);
lean_inc(v_a_1750_);
lean_dec_ref(v___x_1749_);
v___x_1751_ = lean_io_mono_nanos_now();
v___x_1752_ = lp_competition_R24DotCostHarness_sinkExpected(v___x_1746_, v_expected_1727_, v_iters_1728_);
v___x_1753_ = ((lean_object*)(lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00__private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchLazyFull_spec__0_spec__0___redArg___closed__1));
v___x_1754_ = lean_unbox_uint32(v_a_1750_);
lean_inc_ref(v_name_1741_);
v___x_1755_ = lp_competition_R24DotCostHarness_checkWord(v_name_1741_, v___x_1753_, v___x_1754_, v___x_1752_);
if (lean_obj_tag(v___x_1755_) == 0)
{
lean_object* v___x_1756_; lean_object* v_a_1757_; lean_object* v___x_1758_; uint32_t v___x_1759_; lean_object* v___x_1760_; 
lean_dec_ref_known(v___x_1755_, 1);
v___x_1756_ = l_IO_lazyPure___redArg(v___f_1738_);
v_a_1757_ = lean_ctor_get(v___x_1756_, 0);
lean_inc(v_a_1757_);
lean_dec_ref(v___x_1756_);
v___x_1758_ = ((lean_object*)(lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00__private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchLazyFull_spec__0_spec__0___redArg___closed__2));
v___x_1759_ = lean_unbox_uint32(v_a_1757_);
lean_inc_ref(v_name_1741_);
v___x_1760_ = lp_competition_R24DotCostHarness_checkWord(v_name_1741_, v___x_1758_, v___x_1759_, v_expected_1727_);
if (lean_obj_tag(v___x_1760_) == 0)
{
lean_object* v___x_1761_; lean_object* v___x_1762_; uint32_t v___x_1763_; uint32_t v___x_1764_; lean_object* v___x_1765_; lean_object* v___x_1766_; lean_object* v___x_1767_; 
lean_dec_ref_known(v___x_1760_, 1);
v___x_1761_ = lean_nat_sub(v___x_1751_, v___x_1745_);
lean_dec(v___x_1745_);
lean_dec(v___x_1751_);
lean_inc(v_iters_1728_);
lean_inc(v___x_1729_);
lean_inc(v_i_1732_);
v___x_1762_ = lean_alloc_ctor(0, 4, 12);
lean_ctor_set(v___x_1762_, 0, v_i_1732_);
lean_ctor_set(v___x_1762_, 1, v___x_1729_);
lean_ctor_set(v___x_1762_, 2, v_iters_1728_);
lean_ctor_set(v___x_1762_, 3, v___x_1761_);
v___x_1763_ = lean_unbox_uint32(v_a_1750_);
lean_dec(v_a_1750_);
lean_ctor_set_uint32(v___x_1762_, sizeof(void*)*4, v___x_1763_);
lean_ctor_set_uint32(v___x_1762_, sizeof(void*)*4 + 4, v___x_1752_);
v___x_1764_ = lean_unbox_uint32(v_a_1757_);
lean_dec(v_a_1757_);
lean_ctor_set_uint32(v___x_1762_, sizeof(void*)*4 + 8, v___x_1764_);
v___x_1765_ = lean_array_push(v_b_1731_, v___x_1762_);
v___x_1766_ = lean_nat_add(v_i_1732_, v_step_1735_);
lean_dec(v_i_1732_);
v___x_1767_ = lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00__private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchLazyFull_spec__0_spec__0___redArg(v_a_1725_, v_c_1726_, v_expected_1727_, v_iters_1728_, v___x_1729_, v_range_1730_, v___x_1765_, v___x_1766_);
return v___x_1767_;
}
else
{
lean_object* v_a_1768_; lean_object* v___x_1770_; uint8_t v_isShared_1771_; uint8_t v_isSharedCheck_1775_; 
lean_dec(v_a_1757_);
lean_dec(v___x_1751_);
lean_dec(v_a_1750_);
lean_dec(v___x_1745_);
lean_dec(v_i_1732_);
lean_dec_ref(v_b_1731_);
lean_dec(v___x_1729_);
lean_dec(v_iters_1728_);
lean_dec_ref(v_c_1726_);
lean_dec_ref(v_a_1725_);
v_a_1768_ = lean_ctor_get(v___x_1760_, 0);
v_isSharedCheck_1775_ = !lean_is_exclusive(v___x_1760_);
if (v_isSharedCheck_1775_ == 0)
{
v___x_1770_ = v___x_1760_;
v_isShared_1771_ = v_isSharedCheck_1775_;
goto v_resetjp_1769_;
}
else
{
lean_inc(v_a_1768_);
lean_dec(v___x_1760_);
v___x_1770_ = lean_box(0);
v_isShared_1771_ = v_isSharedCheck_1775_;
goto v_resetjp_1769_;
}
v_resetjp_1769_:
{
lean_object* v___x_1773_; 
if (v_isShared_1771_ == 0)
{
v___x_1773_ = v___x_1770_;
goto v_reusejp_1772_;
}
else
{
lean_object* v_reuseFailAlloc_1774_; 
v_reuseFailAlloc_1774_ = lean_alloc_ctor(1, 1, 0);
lean_ctor_set(v_reuseFailAlloc_1774_, 0, v_a_1768_);
v___x_1773_ = v_reuseFailAlloc_1774_;
goto v_reusejp_1772_;
}
v_reusejp_1772_:
{
return v___x_1773_;
}
}
}
}
else
{
lean_object* v_a_1776_; lean_object* v___x_1778_; uint8_t v_isShared_1779_; uint8_t v_isSharedCheck_1783_; 
lean_dec(v___x_1751_);
lean_dec(v_a_1750_);
lean_dec(v___x_1745_);
lean_dec_ref(v___f_1738_);
lean_dec(v_i_1732_);
lean_dec_ref(v_b_1731_);
lean_dec(v___x_1729_);
lean_dec(v_iters_1728_);
lean_dec_ref(v_c_1726_);
lean_dec_ref(v_a_1725_);
v_a_1776_ = lean_ctor_get(v___x_1755_, 0);
v_isSharedCheck_1783_ = !lean_is_exclusive(v___x_1755_);
if (v_isSharedCheck_1783_ == 0)
{
v___x_1778_ = v___x_1755_;
v_isShared_1779_ = v_isSharedCheck_1783_;
goto v_resetjp_1777_;
}
else
{
lean_inc(v_a_1776_);
lean_dec(v___x_1755_);
v___x_1778_ = lean_box(0);
v_isShared_1779_ = v_isSharedCheck_1783_;
goto v_resetjp_1777_;
}
v_resetjp_1777_:
{
lean_object* v___x_1781_; 
if (v_isShared_1779_ == 0)
{
v___x_1781_ = v___x_1778_;
goto v_reusejp_1780_;
}
else
{
lean_object* v_reuseFailAlloc_1782_; 
v_reuseFailAlloc_1782_ = lean_alloc_ctor(1, 1, 0);
lean_ctor_set(v_reuseFailAlloc_1782_, 0, v_a_1776_);
v___x_1781_ = v_reuseFailAlloc_1782_;
goto v_reusejp_1780_;
}
v_reusejp_1780_:
{
return v___x_1781_;
}
}
}
}
else
{
lean_object* v_a_1784_; lean_object* v___x_1786_; uint8_t v_isShared_1787_; uint8_t v_isSharedCheck_1791_; 
lean_dec_ref(v___f_1738_);
lean_dec(v_i_1732_);
lean_dec_ref(v_b_1731_);
lean_dec(v___x_1729_);
lean_dec(v_iters_1728_);
lean_dec_ref(v_c_1726_);
lean_dec_ref(v_a_1725_);
v_a_1784_ = lean_ctor_get(v___x_1744_, 0);
v_isSharedCheck_1791_ = !lean_is_exclusive(v___x_1744_);
if (v_isSharedCheck_1791_ == 0)
{
v___x_1786_ = v___x_1744_;
v_isShared_1787_ = v_isSharedCheck_1791_;
goto v_resetjp_1785_;
}
else
{
lean_inc(v_a_1784_);
lean_dec(v___x_1744_);
v___x_1786_ = lean_box(0);
v_isShared_1787_ = v_isSharedCheck_1791_;
goto v_resetjp_1785_;
}
v_resetjp_1785_:
{
lean_object* v___x_1789_; 
if (v_isShared_1787_ == 0)
{
v___x_1789_ = v___x_1786_;
goto v_reusejp_1788_;
}
else
{
lean_object* v_reuseFailAlloc_1790_; 
v_reuseFailAlloc_1790_ = lean_alloc_ctor(1, 1, 0);
lean_ctor_set(v_reuseFailAlloc_1790_, 0, v_a_1784_);
v___x_1789_ = v_reuseFailAlloc_1790_;
goto v_reusejp_1788_;
}
v_reusejp_1788_:
{
return v___x_1789_;
}
}
}
}
}
}
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchLazyFull_spec__0___redArg___boxed(lean_object* v_a_1792_, lean_object* v_c_1793_, lean_object* v_expected_1794_, lean_object* v_iters_1795_, lean_object* v___x_1796_, lean_object* v_range_1797_, lean_object* v_b_1798_, lean_object* v_i_1799_, lean_object* v___y_1800_){
_start:
{
uint32_t v_expected_boxed_1801_; lean_object* v_res_1802_; 
v_expected_boxed_1801_ = lean_unbox_uint32(v_expected_1794_);
lean_dec(v_expected_1794_);
v_res_1802_ = lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchLazyFull_spec__0___redArg(v_a_1792_, v_c_1793_, v_expected_boxed_1801_, v_iters_1795_, v___x_1796_, v_range_1797_, v_b_1798_, v_i_1799_);
lean_dec_ref(v_range_1797_);
return v_res_1802_;
}
}
LEAN_EXPORT lean_object* lp_competition_R24DotCostHarness_benchLazyFull(lean_object* v_c_1804_, lean_object* v_a_1805_, lean_object* v_b_1806_, lean_object* v_macs_1807_){
_start:
{
lean_object* v___x_1809_; lean_object* v_a_1810_; lean_object* v___x_1811_; lean_object* v___f_1812_; lean_object* v___x_1813_; lean_object* v_a_1814_; lean_object* v___x_1815_; lean_object* v_expected_1816_; uint32_t v_expected_1817_; lean_object* v___x_1818_; lean_object* v_iters_1819_; lean_object* v___x_1820_; lean_object* v___x_1821_; lean_object* v___x_1822_; lean_object* v___x_1823_; 
v___x_1809_ = lp_competition_R24DotCostHarness_benchExactFull___lam__0();
v_a_1810_ = lean_ctor_get(v___x_1809_, 0);
lean_inc(v_a_1810_);
lean_dec_ref(v___x_1809_);
v___x_1811_ = lp_competition_R24DotCostHarness_benchExactFull___lam__0();
lean_dec_ref(v___x_1811_);
lean_inc_ref(v_a_1805_);
v___f_1812_ = lean_alloc_closure((void*)(lp_competition_R24DotCostHarness_benchExactFull___lam__1), 3, 2);
lean_closure_set(v___f_1812_, 0, v_a_1805_);
lean_closure_set(v___f_1812_, 1, v_b_1806_);
v___x_1813_ = l_IO_lazyPure___redArg(v___f_1812_);
v_a_1814_ = lean_ctor_get(v___x_1813_, 0);
lean_inc(v_a_1814_);
lean_dec_ref(v___x_1813_);
v___x_1815_ = lp_competition_R24DotCostHarness_benchExactFull___lam__0();
lean_dec_ref(v___x_1815_);
v_expected_1816_ = lean_ctor_get(v_c_1804_, 5);
v_expected_1817_ = lean_uint32_of_nat(v_expected_1816_);
v___x_1818_ = lean_array_get_size(v_a_1805_);
lean_dec_ref(v_a_1805_);
v_iters_1819_ = lp_competition_R24DotCostHarness_repeats(v_macs_1807_, v___x_1818_);
v___x_1820_ = lean_unsigned_to_nat(0u);
v___x_1821_ = ((lean_object*)(lp_competition_R24DotCostHarness_benchExactFull___closed__0));
v___x_1822_ = ((lean_object*)(lp_competition_R24DotCostHarness_benchExactFull___closed__1));
lean_inc_ref(v_c_1804_);
v___x_1823_ = lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchLazyFull_spec__0___redArg(v_a_1814_, v_c_1804_, v_expected_1817_, v_iters_1819_, v___x_1818_, v___x_1822_, v___x_1821_, v___x_1820_);
if (lean_obj_tag(v___x_1823_) == 0)
{
lean_object* v_a_1824_; lean_object* v___x_1825_; lean_object* v_a_1826_; lean_object* v___x_1827_; lean_object* v___x_1828_; lean_object* v___x_1829_; lean_object* v___x_1830_; 
v_a_1824_ = lean_ctor_get(v___x_1823_, 0);
lean_inc(v_a_1824_);
lean_dec_ref_known(v___x_1823_, 1);
v___x_1825_ = lp_competition_R24DotCostHarness_benchExactFull___lam__0();
v_a_1826_ = lean_ctor_get(v___x_1825_, 0);
lean_inc(v_a_1826_);
lean_dec_ref(v___x_1825_);
v___x_1827_ = ((lean_object*)(lp_competition_R24DotCostHarness_benchLazyFull___closed__0));
v___x_1828_ = ((lean_object*)(lp_competition_R24DotCostHarness_benchExactFull___closed__3));
v___x_1829_ = lean_nat_sub(v_a_1826_, v_a_1810_);
lean_dec(v_a_1810_);
lean_dec(v_a_1826_);
v___x_1830_ = lp_competition_R24DotCostHarness_emit(v_c_1804_, v___x_1827_, v___x_1828_, v___x_1820_, v___x_1829_, v_a_1824_);
lean_dec(v_a_1824_);
lean_dec_ref(v_c_1804_);
return v___x_1830_;
}
else
{
lean_object* v_a_1831_; lean_object* v___x_1833_; uint8_t v_isShared_1834_; uint8_t v_isSharedCheck_1838_; 
lean_dec(v_a_1810_);
lean_dec_ref(v_c_1804_);
v_a_1831_ = lean_ctor_get(v___x_1823_, 0);
v_isSharedCheck_1838_ = !lean_is_exclusive(v___x_1823_);
if (v_isSharedCheck_1838_ == 0)
{
v___x_1833_ = v___x_1823_;
v_isShared_1834_ = v_isSharedCheck_1838_;
goto v_resetjp_1832_;
}
else
{
lean_inc(v_a_1831_);
lean_dec(v___x_1823_);
v___x_1833_ = lean_box(0);
v_isShared_1834_ = v_isSharedCheck_1838_;
goto v_resetjp_1832_;
}
v_resetjp_1832_:
{
lean_object* v___x_1836_; 
if (v_isShared_1834_ == 0)
{
v___x_1836_ = v___x_1833_;
goto v_reusejp_1835_;
}
else
{
lean_object* v_reuseFailAlloc_1837_; 
v_reuseFailAlloc_1837_ = lean_alloc_ctor(1, 1, 0);
lean_ctor_set(v_reuseFailAlloc_1837_, 0, v_a_1831_);
v___x_1836_ = v_reuseFailAlloc_1837_;
goto v_reusejp_1835_;
}
v_reusejp_1835_:
{
return v___x_1836_;
}
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_R24DotCostHarness_benchLazyFull___boxed(lean_object* v_c_1839_, lean_object* v_a_1840_, lean_object* v_b_1841_, lean_object* v_macs_1842_, lean_object* v_a_1843_){
_start:
{
lean_object* v_res_1844_; 
v_res_1844_ = lp_competition_R24DotCostHarness_benchLazyFull(v_c_1839_, v_a_1840_, v_b_1841_, v_macs_1842_);
lean_dec(v_macs_1842_);
return v_res_1844_;
}
}
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchLazyFull_spec__0(lean_object* v_a_1845_, lean_object* v_c_1846_, uint32_t v_expected_1847_, lean_object* v_iters_1848_, lean_object* v___x_1849_, lean_object* v_range_1850_, lean_object* v_b_1851_, lean_object* v_i_1852_, lean_object* v_hs_1853_, lean_object* v_hl_1854_){
_start:
{
lean_object* v___x_1856_; 
v___x_1856_ = lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchLazyFull_spec__0___redArg(v_a_1845_, v_c_1846_, v_expected_1847_, v_iters_1848_, v___x_1849_, v_range_1850_, v_b_1851_, v_i_1852_);
return v___x_1856_;
}
}
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchLazyFull_spec__0___boxed(lean_object* v_a_1857_, lean_object* v_c_1858_, lean_object* v_expected_1859_, lean_object* v_iters_1860_, lean_object* v___x_1861_, lean_object* v_range_1862_, lean_object* v_b_1863_, lean_object* v_i_1864_, lean_object* v_hs_1865_, lean_object* v_hl_1866_, lean_object* v___y_1867_){
_start:
{
uint32_t v_expected_boxed_1868_; lean_object* v_res_1869_; 
v_expected_boxed_1868_ = lean_unbox_uint32(v_expected_1859_);
lean_dec(v_expected_1859_);
v_res_1869_ = lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchLazyFull_spec__0(v_a_1857_, v_c_1858_, v_expected_boxed_1868_, v_iters_1860_, v___x_1861_, v_range_1862_, v_b_1863_, v_i_1864_, v_hs_1865_, v_hl_1866_);
lean_dec_ref(v_range_1862_);
return v_res_1869_;
}
}
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00__private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchLazyFull_spec__0_spec__0(lean_object* v_a_1870_, lean_object* v_c_1871_, uint32_t v_expected_1872_, lean_object* v_iters_1873_, lean_object* v___x_1874_, lean_object* v_range_1875_, lean_object* v_b_1876_, lean_object* v_i_1877_, lean_object* v_hs_1878_, lean_object* v_hl_1879_){
_start:
{
lean_object* v___x_1881_; 
v___x_1881_ = lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00__private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchLazyFull_spec__0_spec__0___redArg(v_a_1870_, v_c_1871_, v_expected_1872_, v_iters_1873_, v___x_1874_, v_range_1875_, v_b_1876_, v_i_1877_);
return v___x_1881_;
}
}
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00__private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchLazyFull_spec__0_spec__0___boxed(lean_object* v_a_1882_, lean_object* v_c_1883_, lean_object* v_expected_1884_, lean_object* v_iters_1885_, lean_object* v___x_1886_, lean_object* v_range_1887_, lean_object* v_b_1888_, lean_object* v_i_1889_, lean_object* v_hs_1890_, lean_object* v_hl_1891_, lean_object* v___y_1892_){
_start:
{
uint32_t v_expected_boxed_1893_; lean_object* v_res_1894_; 
v_expected_boxed_1893_ = lean_unbox_uint32(v_expected_1884_);
lean_dec(v_expected_1884_);
v_res_1894_ = lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00__private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchLazyFull_spec__0_spec__0(v_a_1882_, v_c_1883_, v_expected_boxed_1893_, v_iters_1885_, v___x_1886_, v_range_1887_, v_b_1888_, v_i_1889_, v_hs_1890_, v_hl_1891_);
lean_dec_ref(v_range_1887_);
return v_res_1894_;
}
}
LEAN_EXPORT uint32_t lp_competition_R24DotCostHarness_passExactPrepared(lean_object* v_p_1895_, uint32_t v_s_1896_, lean_object* v_iters_1897_){
_start:
{
lean_object* v_zero_1898_; uint8_t v_isZero_1899_; 
v_zero_1898_ = lean_unsigned_to_nat(0u);
v_isZero_1899_ = lean_nat_dec_eq(v_iters_1897_, v_zero_1898_);
if (v_isZero_1899_ == 1)
{
lean_dec(v_iters_1897_);
lean_dec_ref(v_p_1895_);
return v_s_1896_;
}
else
{
lean_object* v_one_1900_; lean_object* v_n_1901_; lean_object* v_p_1902_; lean_object* v_fst_1903_; lean_object* v_snd_1904_; uint32_t v_word_1905_; uint32_t v___x_1906_; 
v_one_1900_ = lean_unsigned_to_nat(1u);
v_n_1901_ = lean_nat_sub(v_iters_1897_, v_one_1900_);
lean_dec(v_iters_1897_);
v_p_1902_ = lp_competition_R24DotBarrier_touchExact(v_n_1901_, v_p_1895_);
v_fst_1903_ = lean_ctor_get(v_p_1902_, 0);
lean_inc(v_fst_1903_);
v_snd_1904_ = lean_ctor_get(v_p_1902_, 1);
lean_inc(v_snd_1904_);
v_word_1905_ = lp_competition_Submission_R24DotProbe_exactPrepared(v_fst_1903_, v_snd_1904_);
v___x_1906_ = lean_uint32_add(v_s_1896_, v_word_1905_);
v_p_1895_ = v_p_1902_;
v_s_1896_ = v___x_1906_;
v_iters_1897_ = v_n_1901_;
goto _start;
}
}
}
LEAN_EXPORT lean_object* lp_competition_R24DotCostHarness_passExactPrepared___boxed(lean_object* v_p_1908_, lean_object* v_s_1909_, lean_object* v_iters_1910_){
_start:
{
uint32_t v_s_boxed_1911_; uint32_t v_res_1912_; lean_object* v_r_1913_; 
v_s_boxed_1911_ = lean_unbox_uint32(v_s_1909_);
lean_dec(v_s_1909_);
v_res_1912_ = lp_competition_R24DotCostHarness_passExactPrepared(v_p_1908_, v_s_boxed_1911_, v_iters_1910_);
v_r_1913_ = lean_box_uint32(v_res_1912_);
return v_r_1913_;
}
}
LEAN_EXPORT lean_object* lp_competition_R24DotCostHarness_benchExactPrepared___lam__1(lean_object* v_a_1914_, lean_object* v_b_1915_, lean_object* v_x_1916_){
_start:
{
lean_object* v___x_1917_; lean_object* v___x_1918_; lean_object* v___x_1919_; 
v___x_1917_ = lp_competition_Submission_R24ExactDotCost_prepareOperand(v_a_1914_);
v___x_1918_ = lp_competition_Submission_R24ExactDotCost_prepareOperand(v_b_1915_);
v___x_1919_ = lean_alloc_ctor(0, 2, 0);
lean_ctor_set(v___x_1919_, 0, v___x_1917_);
lean_ctor_set(v___x_1919_, 1, v___x_1918_);
return v___x_1919_;
}
}
LEAN_EXPORT uint32_t lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchExactPrepared_spec__0___redArg___lam__0(lean_object* v_a_1920_, lean_object* v_x_1921_){
_start:
{
lean_object* v_fst_1922_; lean_object* v_snd_1923_; uint32_t v___x_1924_; 
v_fst_1922_ = lean_ctor_get(v_a_1920_, 0);
lean_inc(v_fst_1922_);
v_snd_1923_ = lean_ctor_get(v_a_1920_, 1);
lean_inc(v_snd_1923_);
lean_dec_ref(v_a_1920_);
v___x_1924_ = lp_competition_Submission_R24DotProbe_exactPrepared(v_fst_1922_, v_snd_1923_);
return v___x_1924_;
}
}
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchExactPrepared_spec__0___redArg___lam__0___boxed(lean_object* v_a_1925_, lean_object* v_x_1926_){
_start:
{
uint32_t v_res_1927_; lean_object* v_r_1928_; 
v_res_1927_ = lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchExactPrepared_spec__0___redArg___lam__0(v_a_1925_, v_x_1926_);
v_r_1928_ = lean_box_uint32(v_res_1927_);
return v_r_1928_;
}
}
LEAN_EXPORT uint32_t lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchExactPrepared_spec__0___redArg___lam__1(lean_object* v_a_1929_, uint32_t v___x_1930_, lean_object* v_iters_1931_, lean_object* v_x_1932_){
_start:
{
uint32_t v___x_1933_; 
v___x_1933_ = lp_competition_R24DotCostHarness_passExactPrepared(v_a_1929_, v___x_1930_, v_iters_1931_);
return v___x_1933_;
}
}
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchExactPrepared_spec__0___redArg___lam__1___boxed(lean_object* v_a_1934_, lean_object* v___x_1935_, lean_object* v_iters_1936_, lean_object* v_x_1937_){
_start:
{
uint32_t v___x_1802__boxed_1938_; uint32_t v_res_1939_; lean_object* v_r_1940_; 
v___x_1802__boxed_1938_ = lean_unbox_uint32(v___x_1935_);
lean_dec(v___x_1935_);
v_res_1939_ = lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchExactPrepared_spec__0___redArg___lam__1(v_a_1934_, v___x_1802__boxed_1938_, v_iters_1936_, v_x_1937_);
v_r_1940_ = lean_box_uint32(v_res_1939_);
return v_r_1940_;
}
}
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00__private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchExactPrepared_spec__0_spec__0___redArg(lean_object* v_a_1944_, lean_object* v_c_1945_, uint32_t v_expected_1946_, lean_object* v_iters_1947_, lean_object* v___x_1948_, lean_object* v_range_1949_, lean_object* v_b_1950_, lean_object* v_i_1951_){
_start:
{
lean_object* v_stop_1953_; lean_object* v_step_1954_; uint8_t v___x_1955_; 
v_stop_1953_ = lean_ctor_get(v_range_1949_, 1);
v_step_1954_ = lean_ctor_get(v_range_1949_, 2);
v___x_1955_ = lean_nat_dec_lt(v_i_1951_, v_stop_1953_);
if (v___x_1955_ == 0)
{
lean_object* v___x_1956_; 
lean_dec(v_i_1951_);
lean_dec(v___x_1948_);
lean_dec(v_iters_1947_);
lean_dec_ref(v_c_1945_);
lean_dec_ref(v_a_1944_);
v___x_1956_ = lean_alloc_ctor(0, 1, 0);
lean_ctor_set(v___x_1956_, 0, v_b_1950_);
return v___x_1956_;
}
else
{
lean_object* v___f_1957_; lean_object* v___x_1958_; lean_object* v_a_1959_; lean_object* v_name_1960_; lean_object* v___x_1961_; uint32_t v___x_1962_; lean_object* v___x_1963_; 
lean_inc_ref(v_a_1944_);
v___f_1957_ = lean_alloc_closure((void*)(lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchExactPrepared_spec__0___redArg___lam__0___boxed), 2, 1);
lean_closure_set(v___f_1957_, 0, v_a_1944_);
lean_inc_ref(v___f_1957_);
v___x_1958_ = l_IO_lazyPure___redArg(v___f_1957_);
v_a_1959_ = lean_ctor_get(v___x_1958_, 0);
lean_inc(v_a_1959_);
lean_dec_ref(v___x_1958_);
v_name_1960_ = lean_ctor_get(v_c_1945_, 0);
v___x_1961_ = ((lean_object*)(lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00__private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchExactPrepared_spec__0_spec__0___redArg___closed__0));
v___x_1962_ = lean_unbox_uint32(v_a_1959_);
lean_dec(v_a_1959_);
lean_inc_ref(v_name_1960_);
v___x_1963_ = lp_competition_R24DotCostHarness_checkWord(v_name_1960_, v___x_1961_, v___x_1962_, v_expected_1946_);
if (lean_obj_tag(v___x_1963_) == 0)
{
lean_object* v___x_1964_; uint32_t v___x_1965_; lean_object* v___x_1966_; lean_object* v___f_1967_; lean_object* v___x_1968_; lean_object* v_a_1969_; lean_object* v___x_1970_; uint32_t v___x_1971_; lean_object* v___x_1972_; uint32_t v___x_1973_; lean_object* v___x_1974_; 
lean_dec_ref_known(v___x_1963_, 1);
v___x_1964_ = lean_io_mono_nanos_now();
v___x_1965_ = lp_competition_R24DotCostHarness_seed(v_i_1951_);
v___x_1966_ = lean_box_uint32(v___x_1965_);
lean_inc(v_iters_1947_);
lean_inc_ref(v_a_1944_);
v___f_1967_ = lean_alloc_closure((void*)(lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchExactPrepared_spec__0___redArg___lam__1___boxed), 4, 3);
lean_closure_set(v___f_1967_, 0, v_a_1944_);
lean_closure_set(v___f_1967_, 1, v___x_1966_);
lean_closure_set(v___f_1967_, 2, v_iters_1947_);
v___x_1968_ = l_IO_lazyPure___redArg(v___f_1967_);
v_a_1969_ = lean_ctor_get(v___x_1968_, 0);
lean_inc(v_a_1969_);
lean_dec_ref(v___x_1968_);
v___x_1970_ = lean_io_mono_nanos_now();
v___x_1971_ = lp_competition_R24DotCostHarness_sinkExpected(v___x_1965_, v_expected_1946_, v_iters_1947_);
v___x_1972_ = ((lean_object*)(lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00__private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchExactPrepared_spec__0_spec__0___redArg___closed__1));
v___x_1973_ = lean_unbox_uint32(v_a_1969_);
lean_inc_ref(v_name_1960_);
v___x_1974_ = lp_competition_R24DotCostHarness_checkWord(v_name_1960_, v___x_1972_, v___x_1973_, v___x_1971_);
if (lean_obj_tag(v___x_1974_) == 0)
{
lean_object* v___x_1975_; lean_object* v_a_1976_; lean_object* v___x_1977_; uint32_t v___x_1978_; lean_object* v___x_1979_; 
lean_dec_ref_known(v___x_1974_, 1);
v___x_1975_ = l_IO_lazyPure___redArg(v___f_1957_);
v_a_1976_ = lean_ctor_get(v___x_1975_, 0);
lean_inc(v_a_1976_);
lean_dec_ref(v___x_1975_);
v___x_1977_ = ((lean_object*)(lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00__private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchExactPrepared_spec__0_spec__0___redArg___closed__2));
v___x_1978_ = lean_unbox_uint32(v_a_1976_);
lean_inc_ref(v_name_1960_);
v___x_1979_ = lp_competition_R24DotCostHarness_checkWord(v_name_1960_, v___x_1977_, v___x_1978_, v_expected_1946_);
if (lean_obj_tag(v___x_1979_) == 0)
{
lean_object* v___x_1980_; lean_object* v___x_1981_; uint32_t v___x_1982_; uint32_t v___x_1983_; lean_object* v___x_1984_; lean_object* v___x_1985_; 
lean_dec_ref_known(v___x_1979_, 1);
v___x_1980_ = lean_nat_sub(v___x_1970_, v___x_1964_);
lean_dec(v___x_1964_);
lean_dec(v___x_1970_);
lean_inc(v_iters_1947_);
lean_inc(v___x_1948_);
lean_inc(v_i_1951_);
v___x_1981_ = lean_alloc_ctor(0, 4, 12);
lean_ctor_set(v___x_1981_, 0, v_i_1951_);
lean_ctor_set(v___x_1981_, 1, v___x_1948_);
lean_ctor_set(v___x_1981_, 2, v_iters_1947_);
lean_ctor_set(v___x_1981_, 3, v___x_1980_);
v___x_1982_ = lean_unbox_uint32(v_a_1969_);
lean_dec(v_a_1969_);
lean_ctor_set_uint32(v___x_1981_, sizeof(void*)*4, v___x_1982_);
lean_ctor_set_uint32(v___x_1981_, sizeof(void*)*4 + 4, v___x_1971_);
v___x_1983_ = lean_unbox_uint32(v_a_1976_);
lean_dec(v_a_1976_);
lean_ctor_set_uint32(v___x_1981_, sizeof(void*)*4 + 8, v___x_1983_);
v___x_1984_ = lean_array_push(v_b_1950_, v___x_1981_);
v___x_1985_ = lean_nat_add(v_i_1951_, v_step_1954_);
lean_dec(v_i_1951_);
v_b_1950_ = v___x_1984_;
v_i_1951_ = v___x_1985_;
goto _start;
}
else
{
lean_object* v_a_1987_; lean_object* v___x_1989_; uint8_t v_isShared_1990_; uint8_t v_isSharedCheck_1994_; 
lean_dec(v_a_1976_);
lean_dec(v___x_1970_);
lean_dec(v_a_1969_);
lean_dec(v___x_1964_);
lean_dec(v_i_1951_);
lean_dec_ref(v_b_1950_);
lean_dec(v___x_1948_);
lean_dec(v_iters_1947_);
lean_dec_ref(v_c_1945_);
lean_dec_ref(v_a_1944_);
v_a_1987_ = lean_ctor_get(v___x_1979_, 0);
v_isSharedCheck_1994_ = !lean_is_exclusive(v___x_1979_);
if (v_isSharedCheck_1994_ == 0)
{
v___x_1989_ = v___x_1979_;
v_isShared_1990_ = v_isSharedCheck_1994_;
goto v_resetjp_1988_;
}
else
{
lean_inc(v_a_1987_);
lean_dec(v___x_1979_);
v___x_1989_ = lean_box(0);
v_isShared_1990_ = v_isSharedCheck_1994_;
goto v_resetjp_1988_;
}
v_resetjp_1988_:
{
lean_object* v___x_1992_; 
if (v_isShared_1990_ == 0)
{
v___x_1992_ = v___x_1989_;
goto v_reusejp_1991_;
}
else
{
lean_object* v_reuseFailAlloc_1993_; 
v_reuseFailAlloc_1993_ = lean_alloc_ctor(1, 1, 0);
lean_ctor_set(v_reuseFailAlloc_1993_, 0, v_a_1987_);
v___x_1992_ = v_reuseFailAlloc_1993_;
goto v_reusejp_1991_;
}
v_reusejp_1991_:
{
return v___x_1992_;
}
}
}
}
else
{
lean_object* v_a_1995_; lean_object* v___x_1997_; uint8_t v_isShared_1998_; uint8_t v_isSharedCheck_2002_; 
lean_dec(v___x_1970_);
lean_dec(v_a_1969_);
lean_dec(v___x_1964_);
lean_dec_ref(v___f_1957_);
lean_dec(v_i_1951_);
lean_dec_ref(v_b_1950_);
lean_dec(v___x_1948_);
lean_dec(v_iters_1947_);
lean_dec_ref(v_c_1945_);
lean_dec_ref(v_a_1944_);
v_a_1995_ = lean_ctor_get(v___x_1974_, 0);
v_isSharedCheck_2002_ = !lean_is_exclusive(v___x_1974_);
if (v_isSharedCheck_2002_ == 0)
{
v___x_1997_ = v___x_1974_;
v_isShared_1998_ = v_isSharedCheck_2002_;
goto v_resetjp_1996_;
}
else
{
lean_inc(v_a_1995_);
lean_dec(v___x_1974_);
v___x_1997_ = lean_box(0);
v_isShared_1998_ = v_isSharedCheck_2002_;
goto v_resetjp_1996_;
}
v_resetjp_1996_:
{
lean_object* v___x_2000_; 
if (v_isShared_1998_ == 0)
{
v___x_2000_ = v___x_1997_;
goto v_reusejp_1999_;
}
else
{
lean_object* v_reuseFailAlloc_2001_; 
v_reuseFailAlloc_2001_ = lean_alloc_ctor(1, 1, 0);
lean_ctor_set(v_reuseFailAlloc_2001_, 0, v_a_1995_);
v___x_2000_ = v_reuseFailAlloc_2001_;
goto v_reusejp_1999_;
}
v_reusejp_1999_:
{
return v___x_2000_;
}
}
}
}
else
{
lean_object* v_a_2003_; lean_object* v___x_2005_; uint8_t v_isShared_2006_; uint8_t v_isSharedCheck_2010_; 
lean_dec_ref(v___f_1957_);
lean_dec(v_i_1951_);
lean_dec_ref(v_b_1950_);
lean_dec(v___x_1948_);
lean_dec(v_iters_1947_);
lean_dec_ref(v_c_1945_);
lean_dec_ref(v_a_1944_);
v_a_2003_ = lean_ctor_get(v___x_1963_, 0);
v_isSharedCheck_2010_ = !lean_is_exclusive(v___x_1963_);
if (v_isSharedCheck_2010_ == 0)
{
v___x_2005_ = v___x_1963_;
v_isShared_2006_ = v_isSharedCheck_2010_;
goto v_resetjp_2004_;
}
else
{
lean_inc(v_a_2003_);
lean_dec(v___x_1963_);
v___x_2005_ = lean_box(0);
v_isShared_2006_ = v_isSharedCheck_2010_;
goto v_resetjp_2004_;
}
v_resetjp_2004_:
{
lean_object* v___x_2008_; 
if (v_isShared_2006_ == 0)
{
v___x_2008_ = v___x_2005_;
goto v_reusejp_2007_;
}
else
{
lean_object* v_reuseFailAlloc_2009_; 
v_reuseFailAlloc_2009_ = lean_alloc_ctor(1, 1, 0);
lean_ctor_set(v_reuseFailAlloc_2009_, 0, v_a_2003_);
v___x_2008_ = v_reuseFailAlloc_2009_;
goto v_reusejp_2007_;
}
v_reusejp_2007_:
{
return v___x_2008_;
}
}
}
}
}
}
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00__private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchExactPrepared_spec__0_spec__0___redArg___boxed(lean_object* v_a_2011_, lean_object* v_c_2012_, lean_object* v_expected_2013_, lean_object* v_iters_2014_, lean_object* v___x_2015_, lean_object* v_range_2016_, lean_object* v_b_2017_, lean_object* v_i_2018_, lean_object* v___y_2019_){
_start:
{
uint32_t v_expected_boxed_2020_; lean_object* v_res_2021_; 
v_expected_boxed_2020_ = lean_unbox_uint32(v_expected_2013_);
lean_dec(v_expected_2013_);
v_res_2021_ = lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00__private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchExactPrepared_spec__0_spec__0___redArg(v_a_2011_, v_c_2012_, v_expected_boxed_2020_, v_iters_2014_, v___x_2015_, v_range_2016_, v_b_2017_, v_i_2018_);
lean_dec_ref(v_range_2016_);
return v_res_2021_;
}
}
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchExactPrepared_spec__0___redArg(lean_object* v_a_2022_, lean_object* v_c_2023_, uint32_t v_expected_2024_, lean_object* v_iters_2025_, lean_object* v___x_2026_, lean_object* v_range_2027_, lean_object* v_b_2028_, lean_object* v_i_2029_){
_start:
{
lean_object* v_stop_2031_; lean_object* v_step_2032_; uint8_t v___x_2033_; 
v_stop_2031_ = lean_ctor_get(v_range_2027_, 1);
v_step_2032_ = lean_ctor_get(v_range_2027_, 2);
v___x_2033_ = lean_nat_dec_lt(v_i_2029_, v_stop_2031_);
if (v___x_2033_ == 0)
{
lean_object* v___x_2034_; 
lean_dec(v_i_2029_);
lean_dec(v___x_2026_);
lean_dec(v_iters_2025_);
lean_dec_ref(v_c_2023_);
lean_dec_ref(v_a_2022_);
v___x_2034_ = lean_alloc_ctor(0, 1, 0);
lean_ctor_set(v___x_2034_, 0, v_b_2028_);
return v___x_2034_;
}
else
{
lean_object* v___f_2035_; lean_object* v___x_2036_; lean_object* v_a_2037_; lean_object* v_name_2038_; lean_object* v___x_2039_; uint32_t v___x_2040_; lean_object* v___x_2041_; 
lean_inc_ref(v_a_2022_);
v___f_2035_ = lean_alloc_closure((void*)(lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchExactPrepared_spec__0___redArg___lam__0___boxed), 2, 1);
lean_closure_set(v___f_2035_, 0, v_a_2022_);
lean_inc_ref(v___f_2035_);
v___x_2036_ = l_IO_lazyPure___redArg(v___f_2035_);
v_a_2037_ = lean_ctor_get(v___x_2036_, 0);
lean_inc(v_a_2037_);
lean_dec_ref(v___x_2036_);
v_name_2038_ = lean_ctor_get(v_c_2023_, 0);
v___x_2039_ = ((lean_object*)(lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00__private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchExactPrepared_spec__0_spec__0___redArg___closed__0));
v___x_2040_ = lean_unbox_uint32(v_a_2037_);
lean_dec(v_a_2037_);
lean_inc_ref(v_name_2038_);
v___x_2041_ = lp_competition_R24DotCostHarness_checkWord(v_name_2038_, v___x_2039_, v___x_2040_, v_expected_2024_);
if (lean_obj_tag(v___x_2041_) == 0)
{
lean_object* v___x_2042_; uint32_t v___x_2043_; lean_object* v___x_2044_; lean_object* v___f_2045_; lean_object* v___x_2046_; lean_object* v_a_2047_; lean_object* v___x_2048_; uint32_t v___x_2049_; lean_object* v___x_2050_; uint32_t v___x_2051_; lean_object* v___x_2052_; 
lean_dec_ref_known(v___x_2041_, 1);
v___x_2042_ = lean_io_mono_nanos_now();
v___x_2043_ = lp_competition_R24DotCostHarness_seed(v_i_2029_);
v___x_2044_ = lean_box_uint32(v___x_2043_);
lean_inc(v_iters_2025_);
lean_inc_ref(v_a_2022_);
v___f_2045_ = lean_alloc_closure((void*)(lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchExactPrepared_spec__0___redArg___lam__1___boxed), 4, 3);
lean_closure_set(v___f_2045_, 0, v_a_2022_);
lean_closure_set(v___f_2045_, 1, v___x_2044_);
lean_closure_set(v___f_2045_, 2, v_iters_2025_);
v___x_2046_ = l_IO_lazyPure___redArg(v___f_2045_);
v_a_2047_ = lean_ctor_get(v___x_2046_, 0);
lean_inc(v_a_2047_);
lean_dec_ref(v___x_2046_);
v___x_2048_ = lean_io_mono_nanos_now();
v___x_2049_ = lp_competition_R24DotCostHarness_sinkExpected(v___x_2043_, v_expected_2024_, v_iters_2025_);
v___x_2050_ = ((lean_object*)(lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00__private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchExactPrepared_spec__0_spec__0___redArg___closed__1));
v___x_2051_ = lean_unbox_uint32(v_a_2047_);
lean_inc_ref(v_name_2038_);
v___x_2052_ = lp_competition_R24DotCostHarness_checkWord(v_name_2038_, v___x_2050_, v___x_2051_, v___x_2049_);
if (lean_obj_tag(v___x_2052_) == 0)
{
lean_object* v___x_2053_; lean_object* v_a_2054_; lean_object* v___x_2055_; uint32_t v___x_2056_; lean_object* v___x_2057_; 
lean_dec_ref_known(v___x_2052_, 1);
v___x_2053_ = l_IO_lazyPure___redArg(v___f_2035_);
v_a_2054_ = lean_ctor_get(v___x_2053_, 0);
lean_inc(v_a_2054_);
lean_dec_ref(v___x_2053_);
v___x_2055_ = ((lean_object*)(lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00__private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchExactPrepared_spec__0_spec__0___redArg___closed__2));
v___x_2056_ = lean_unbox_uint32(v_a_2054_);
lean_inc_ref(v_name_2038_);
v___x_2057_ = lp_competition_R24DotCostHarness_checkWord(v_name_2038_, v___x_2055_, v___x_2056_, v_expected_2024_);
if (lean_obj_tag(v___x_2057_) == 0)
{
lean_object* v___x_2058_; lean_object* v___x_2059_; uint32_t v___x_2060_; uint32_t v___x_2061_; lean_object* v___x_2062_; lean_object* v___x_2063_; lean_object* v___x_2064_; 
lean_dec_ref_known(v___x_2057_, 1);
v___x_2058_ = lean_nat_sub(v___x_2048_, v___x_2042_);
lean_dec(v___x_2042_);
lean_dec(v___x_2048_);
lean_inc(v_iters_2025_);
lean_inc(v___x_2026_);
lean_inc(v_i_2029_);
v___x_2059_ = lean_alloc_ctor(0, 4, 12);
lean_ctor_set(v___x_2059_, 0, v_i_2029_);
lean_ctor_set(v___x_2059_, 1, v___x_2026_);
lean_ctor_set(v___x_2059_, 2, v_iters_2025_);
lean_ctor_set(v___x_2059_, 3, v___x_2058_);
v___x_2060_ = lean_unbox_uint32(v_a_2047_);
lean_dec(v_a_2047_);
lean_ctor_set_uint32(v___x_2059_, sizeof(void*)*4, v___x_2060_);
lean_ctor_set_uint32(v___x_2059_, sizeof(void*)*4 + 4, v___x_2049_);
v___x_2061_ = lean_unbox_uint32(v_a_2054_);
lean_dec(v_a_2054_);
lean_ctor_set_uint32(v___x_2059_, sizeof(void*)*4 + 8, v___x_2061_);
v___x_2062_ = lean_array_push(v_b_2028_, v___x_2059_);
v___x_2063_ = lean_nat_add(v_i_2029_, v_step_2032_);
lean_dec(v_i_2029_);
v___x_2064_ = lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00__private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchExactPrepared_spec__0_spec__0___redArg(v_a_2022_, v_c_2023_, v_expected_2024_, v_iters_2025_, v___x_2026_, v_range_2027_, v___x_2062_, v___x_2063_);
return v___x_2064_;
}
else
{
lean_object* v_a_2065_; lean_object* v___x_2067_; uint8_t v_isShared_2068_; uint8_t v_isSharedCheck_2072_; 
lean_dec(v_a_2054_);
lean_dec(v___x_2048_);
lean_dec(v_a_2047_);
lean_dec(v___x_2042_);
lean_dec(v_i_2029_);
lean_dec_ref(v_b_2028_);
lean_dec(v___x_2026_);
lean_dec(v_iters_2025_);
lean_dec_ref(v_c_2023_);
lean_dec_ref(v_a_2022_);
v_a_2065_ = lean_ctor_get(v___x_2057_, 0);
v_isSharedCheck_2072_ = !lean_is_exclusive(v___x_2057_);
if (v_isSharedCheck_2072_ == 0)
{
v___x_2067_ = v___x_2057_;
v_isShared_2068_ = v_isSharedCheck_2072_;
goto v_resetjp_2066_;
}
else
{
lean_inc(v_a_2065_);
lean_dec(v___x_2057_);
v___x_2067_ = lean_box(0);
v_isShared_2068_ = v_isSharedCheck_2072_;
goto v_resetjp_2066_;
}
v_resetjp_2066_:
{
lean_object* v___x_2070_; 
if (v_isShared_2068_ == 0)
{
v___x_2070_ = v___x_2067_;
goto v_reusejp_2069_;
}
else
{
lean_object* v_reuseFailAlloc_2071_; 
v_reuseFailAlloc_2071_ = lean_alloc_ctor(1, 1, 0);
lean_ctor_set(v_reuseFailAlloc_2071_, 0, v_a_2065_);
v___x_2070_ = v_reuseFailAlloc_2071_;
goto v_reusejp_2069_;
}
v_reusejp_2069_:
{
return v___x_2070_;
}
}
}
}
else
{
lean_object* v_a_2073_; lean_object* v___x_2075_; uint8_t v_isShared_2076_; uint8_t v_isSharedCheck_2080_; 
lean_dec(v___x_2048_);
lean_dec(v_a_2047_);
lean_dec(v___x_2042_);
lean_dec_ref(v___f_2035_);
lean_dec(v_i_2029_);
lean_dec_ref(v_b_2028_);
lean_dec(v___x_2026_);
lean_dec(v_iters_2025_);
lean_dec_ref(v_c_2023_);
lean_dec_ref(v_a_2022_);
v_a_2073_ = lean_ctor_get(v___x_2052_, 0);
v_isSharedCheck_2080_ = !lean_is_exclusive(v___x_2052_);
if (v_isSharedCheck_2080_ == 0)
{
v___x_2075_ = v___x_2052_;
v_isShared_2076_ = v_isSharedCheck_2080_;
goto v_resetjp_2074_;
}
else
{
lean_inc(v_a_2073_);
lean_dec(v___x_2052_);
v___x_2075_ = lean_box(0);
v_isShared_2076_ = v_isSharedCheck_2080_;
goto v_resetjp_2074_;
}
v_resetjp_2074_:
{
lean_object* v___x_2078_; 
if (v_isShared_2076_ == 0)
{
v___x_2078_ = v___x_2075_;
goto v_reusejp_2077_;
}
else
{
lean_object* v_reuseFailAlloc_2079_; 
v_reuseFailAlloc_2079_ = lean_alloc_ctor(1, 1, 0);
lean_ctor_set(v_reuseFailAlloc_2079_, 0, v_a_2073_);
v___x_2078_ = v_reuseFailAlloc_2079_;
goto v_reusejp_2077_;
}
v_reusejp_2077_:
{
return v___x_2078_;
}
}
}
}
else
{
lean_object* v_a_2081_; lean_object* v___x_2083_; uint8_t v_isShared_2084_; uint8_t v_isSharedCheck_2088_; 
lean_dec_ref(v___f_2035_);
lean_dec(v_i_2029_);
lean_dec_ref(v_b_2028_);
lean_dec(v___x_2026_);
lean_dec(v_iters_2025_);
lean_dec_ref(v_c_2023_);
lean_dec_ref(v_a_2022_);
v_a_2081_ = lean_ctor_get(v___x_2041_, 0);
v_isSharedCheck_2088_ = !lean_is_exclusive(v___x_2041_);
if (v_isSharedCheck_2088_ == 0)
{
v___x_2083_ = v___x_2041_;
v_isShared_2084_ = v_isSharedCheck_2088_;
goto v_resetjp_2082_;
}
else
{
lean_inc(v_a_2081_);
lean_dec(v___x_2041_);
v___x_2083_ = lean_box(0);
v_isShared_2084_ = v_isSharedCheck_2088_;
goto v_resetjp_2082_;
}
v_resetjp_2082_:
{
lean_object* v___x_2086_; 
if (v_isShared_2084_ == 0)
{
v___x_2086_ = v___x_2083_;
goto v_reusejp_2085_;
}
else
{
lean_object* v_reuseFailAlloc_2087_; 
v_reuseFailAlloc_2087_ = lean_alloc_ctor(1, 1, 0);
lean_ctor_set(v_reuseFailAlloc_2087_, 0, v_a_2081_);
v___x_2086_ = v_reuseFailAlloc_2087_;
goto v_reusejp_2085_;
}
v_reusejp_2085_:
{
return v___x_2086_;
}
}
}
}
}
}
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchExactPrepared_spec__0___redArg___boxed(lean_object* v_a_2089_, lean_object* v_c_2090_, lean_object* v_expected_2091_, lean_object* v_iters_2092_, lean_object* v___x_2093_, lean_object* v_range_2094_, lean_object* v_b_2095_, lean_object* v_i_2096_, lean_object* v___y_2097_){
_start:
{
uint32_t v_expected_boxed_2098_; lean_object* v_res_2099_; 
v_expected_boxed_2098_ = lean_unbox_uint32(v_expected_2091_);
lean_dec(v_expected_2091_);
v_res_2099_ = lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchExactPrepared_spec__0___redArg(v_a_2089_, v_c_2090_, v_expected_boxed_2098_, v_iters_2092_, v___x_2093_, v_range_2094_, v_b_2095_, v_i_2096_);
lean_dec_ref(v_range_2094_);
return v_res_2099_;
}
}
LEAN_EXPORT lean_object* lp_competition_R24DotCostHarness_benchExactPrepared(lean_object* v_c_2101_, lean_object* v_a_2102_, lean_object* v_b_2103_, lean_object* v_macs_2104_){
_start:
{
lean_object* v___x_2106_; lean_object* v_a_2107_; lean_object* v___x_2108_; lean_object* v_a_2109_; lean_object* v___f_2110_; lean_object* v___x_2111_; lean_object* v_a_2112_; lean_object* v___x_2113_; lean_object* v_a_2114_; lean_object* v_expected_2115_; uint32_t v_expected_2116_; lean_object* v___x_2117_; lean_object* v_iters_2118_; lean_object* v___x_2119_; lean_object* v___x_2120_; lean_object* v___x_2121_; lean_object* v___x_2122_; 
v___x_2106_ = lp_competition_R24DotCostHarness_benchExactFull___lam__0();
v_a_2107_ = lean_ctor_get(v___x_2106_, 0);
lean_inc(v_a_2107_);
lean_dec_ref(v___x_2106_);
v___x_2108_ = lp_competition_R24DotCostHarness_benchExactFull___lam__0();
v_a_2109_ = lean_ctor_get(v___x_2108_, 0);
lean_inc(v_a_2109_);
lean_dec_ref(v___x_2108_);
lean_inc_ref(v_a_2102_);
v___f_2110_ = lean_alloc_closure((void*)(lp_competition_R24DotCostHarness_benchExactPrepared___lam__1), 3, 2);
lean_closure_set(v___f_2110_, 0, v_a_2102_);
lean_closure_set(v___f_2110_, 1, v_b_2103_);
v___x_2111_ = l_IO_lazyPure___redArg(v___f_2110_);
v_a_2112_ = lean_ctor_get(v___x_2111_, 0);
lean_inc(v_a_2112_);
lean_dec_ref(v___x_2111_);
v___x_2113_ = lp_competition_R24DotCostHarness_benchExactFull___lam__0();
v_a_2114_ = lean_ctor_get(v___x_2113_, 0);
lean_inc(v_a_2114_);
lean_dec_ref(v___x_2113_);
v_expected_2115_ = lean_ctor_get(v_c_2101_, 5);
v_expected_2116_ = lean_uint32_of_nat(v_expected_2115_);
v___x_2117_ = lean_array_get_size(v_a_2102_);
lean_dec_ref(v_a_2102_);
v_iters_2118_ = lp_competition_R24DotCostHarness_repeats(v_macs_2104_, v___x_2117_);
v___x_2119_ = lean_unsigned_to_nat(0u);
v___x_2120_ = ((lean_object*)(lp_competition_R24DotCostHarness_benchExactFull___closed__0));
v___x_2121_ = ((lean_object*)(lp_competition_R24DotCostHarness_benchExactFull___closed__1));
lean_inc_ref(v_c_2101_);
v___x_2122_ = lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchExactPrepared_spec__0___redArg(v_a_2112_, v_c_2101_, v_expected_2116_, v_iters_2118_, v___x_2117_, v___x_2121_, v___x_2120_, v___x_2119_);
if (lean_obj_tag(v___x_2122_) == 0)
{
lean_object* v_a_2123_; lean_object* v___x_2124_; lean_object* v_a_2125_; lean_object* v___x_2126_; lean_object* v___x_2127_; lean_object* v___x_2128_; lean_object* v___x_2129_; lean_object* v___x_2130_; 
v_a_2123_ = lean_ctor_get(v___x_2122_, 0);
lean_inc(v_a_2123_);
lean_dec_ref_known(v___x_2122_, 1);
v___x_2124_ = lp_competition_R24DotCostHarness_benchExactFull___lam__0();
v_a_2125_ = lean_ctor_get(v___x_2124_, 0);
lean_inc(v_a_2125_);
lean_dec_ref(v___x_2124_);
v___x_2126_ = lean_nat_sub(v_a_2114_, v_a_2109_);
lean_dec(v_a_2109_);
lean_dec(v_a_2114_);
v___x_2127_ = ((lean_object*)(lp_competition_R24DotCostHarness_benchExactFull___closed__2));
v___x_2128_ = ((lean_object*)(lp_competition_R24DotCostHarness_benchExactPrepared___closed__0));
v___x_2129_ = lean_nat_sub(v_a_2125_, v_a_2107_);
lean_dec(v_a_2107_);
lean_dec(v_a_2125_);
v___x_2130_ = lp_competition_R24DotCostHarness_emit(v_c_2101_, v___x_2127_, v___x_2128_, v___x_2126_, v___x_2129_, v_a_2123_);
lean_dec(v_a_2123_);
lean_dec_ref(v_c_2101_);
return v___x_2130_;
}
else
{
lean_object* v_a_2131_; lean_object* v___x_2133_; uint8_t v_isShared_2134_; uint8_t v_isSharedCheck_2138_; 
lean_dec(v_a_2114_);
lean_dec(v_a_2109_);
lean_dec(v_a_2107_);
lean_dec_ref(v_c_2101_);
v_a_2131_ = lean_ctor_get(v___x_2122_, 0);
v_isSharedCheck_2138_ = !lean_is_exclusive(v___x_2122_);
if (v_isSharedCheck_2138_ == 0)
{
v___x_2133_ = v___x_2122_;
v_isShared_2134_ = v_isSharedCheck_2138_;
goto v_resetjp_2132_;
}
else
{
lean_inc(v_a_2131_);
lean_dec(v___x_2122_);
v___x_2133_ = lean_box(0);
v_isShared_2134_ = v_isSharedCheck_2138_;
goto v_resetjp_2132_;
}
v_resetjp_2132_:
{
lean_object* v___x_2136_; 
if (v_isShared_2134_ == 0)
{
v___x_2136_ = v___x_2133_;
goto v_reusejp_2135_;
}
else
{
lean_object* v_reuseFailAlloc_2137_; 
v_reuseFailAlloc_2137_ = lean_alloc_ctor(1, 1, 0);
lean_ctor_set(v_reuseFailAlloc_2137_, 0, v_a_2131_);
v___x_2136_ = v_reuseFailAlloc_2137_;
goto v_reusejp_2135_;
}
v_reusejp_2135_:
{
return v___x_2136_;
}
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_R24DotCostHarness_benchExactPrepared___boxed(lean_object* v_c_2139_, lean_object* v_a_2140_, lean_object* v_b_2141_, lean_object* v_macs_2142_, lean_object* v_a_2143_){
_start:
{
lean_object* v_res_2144_; 
v_res_2144_ = lp_competition_R24DotCostHarness_benchExactPrepared(v_c_2139_, v_a_2140_, v_b_2141_, v_macs_2142_);
lean_dec(v_macs_2142_);
return v_res_2144_;
}
}
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchExactPrepared_spec__0(lean_object* v_a_2145_, lean_object* v_c_2146_, uint32_t v_expected_2147_, lean_object* v_iters_2148_, lean_object* v___x_2149_, lean_object* v_range_2150_, lean_object* v_b_2151_, lean_object* v_i_2152_, lean_object* v_hs_2153_, lean_object* v_hl_2154_){
_start:
{
lean_object* v___x_2156_; 
v___x_2156_ = lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchExactPrepared_spec__0___redArg(v_a_2145_, v_c_2146_, v_expected_2147_, v_iters_2148_, v___x_2149_, v_range_2150_, v_b_2151_, v_i_2152_);
return v___x_2156_;
}
}
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchExactPrepared_spec__0___boxed(lean_object* v_a_2157_, lean_object* v_c_2158_, lean_object* v_expected_2159_, lean_object* v_iters_2160_, lean_object* v___x_2161_, lean_object* v_range_2162_, lean_object* v_b_2163_, lean_object* v_i_2164_, lean_object* v_hs_2165_, lean_object* v_hl_2166_, lean_object* v___y_2167_){
_start:
{
uint32_t v_expected_boxed_2168_; lean_object* v_res_2169_; 
v_expected_boxed_2168_ = lean_unbox_uint32(v_expected_2159_);
lean_dec(v_expected_2159_);
v_res_2169_ = lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchExactPrepared_spec__0(v_a_2157_, v_c_2158_, v_expected_boxed_2168_, v_iters_2160_, v___x_2161_, v_range_2162_, v_b_2163_, v_i_2164_, v_hs_2165_, v_hl_2166_);
lean_dec_ref(v_range_2162_);
return v_res_2169_;
}
}
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00__private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchExactPrepared_spec__0_spec__0(lean_object* v_a_2170_, lean_object* v_c_2171_, uint32_t v_expected_2172_, lean_object* v_iters_2173_, lean_object* v___x_2174_, lean_object* v_range_2175_, lean_object* v_b_2176_, lean_object* v_i_2177_, lean_object* v_hs_2178_, lean_object* v_hl_2179_){
_start:
{
lean_object* v___x_2181_; 
v___x_2181_ = lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00__private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchExactPrepared_spec__0_spec__0___redArg(v_a_2170_, v_c_2171_, v_expected_2172_, v_iters_2173_, v___x_2174_, v_range_2175_, v_b_2176_, v_i_2177_);
return v___x_2181_;
}
}
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00__private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchExactPrepared_spec__0_spec__0___boxed(lean_object* v_a_2182_, lean_object* v_c_2183_, lean_object* v_expected_2184_, lean_object* v_iters_2185_, lean_object* v___x_2186_, lean_object* v_range_2187_, lean_object* v_b_2188_, lean_object* v_i_2189_, lean_object* v_hs_2190_, lean_object* v_hl_2191_, lean_object* v___y_2192_){
_start:
{
uint32_t v_expected_boxed_2193_; lean_object* v_res_2194_; 
v_expected_boxed_2193_ = lean_unbox_uint32(v_expected_2184_);
lean_dec(v_expected_2184_);
v_res_2194_ = lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00__private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchExactPrepared_spec__0_spec__0(v_a_2182_, v_c_2183_, v_expected_boxed_2193_, v_iters_2185_, v___x_2186_, v_range_2187_, v_b_2188_, v_i_2189_, v_hs_2190_, v_hl_2191_);
lean_dec_ref(v_range_2187_);
return v_res_2194_;
}
}
LEAN_EXPORT uint32_t lp_competition_R24DotCostHarness_passEagerPrepared(lean_object* v_p_2195_, uint32_t v_s_2196_, lean_object* v_iters_2197_){
_start:
{
lean_object* v_zero_2198_; uint8_t v_isZero_2199_; 
v_zero_2198_ = lean_unsigned_to_nat(0u);
v_isZero_2199_ = lean_nat_dec_eq(v_iters_2197_, v_zero_2198_);
if (v_isZero_2199_ == 1)
{
lean_dec(v_iters_2197_);
lean_dec_ref(v_p_2195_);
return v_s_2196_;
}
else
{
lean_object* v_one_2200_; lean_object* v_n_2201_; lean_object* v_p_2202_; lean_object* v_fst_2203_; lean_object* v_snd_2204_; uint32_t v_word_2205_; uint32_t v___x_2206_; 
v_one_2200_ = lean_unsigned_to_nat(1u);
v_n_2201_ = lean_nat_sub(v_iters_2197_, v_one_2200_);
lean_dec(v_iters_2197_);
v_p_2202_ = lp_competition_R24DotBarrier_touchEager(v_n_2201_, v_p_2195_);
v_fst_2203_ = lean_ctor_get(v_p_2202_, 0);
lean_inc(v_fst_2203_);
v_snd_2204_ = lean_ctor_get(v_p_2202_, 1);
lean_inc(v_snd_2204_);
v_word_2205_ = lp_competition_Submission_R24DotProbe_eagerPrepared(v_fst_2203_, v_snd_2204_);
v___x_2206_ = lean_uint32_add(v_s_2196_, v_word_2205_);
v_p_2195_ = v_p_2202_;
v_s_2196_ = v___x_2206_;
v_iters_2197_ = v_n_2201_;
goto _start;
}
}
}
LEAN_EXPORT lean_object* lp_competition_R24DotCostHarness_passEagerPrepared___boxed(lean_object* v_p_2208_, lean_object* v_s_2209_, lean_object* v_iters_2210_){
_start:
{
uint32_t v_s_boxed_2211_; uint32_t v_res_2212_; lean_object* v_r_2213_; 
v_s_boxed_2211_ = lean_unbox_uint32(v_s_2209_);
lean_dec(v_s_2209_);
v_res_2212_ = lp_competition_R24DotCostHarness_passEagerPrepared(v_p_2208_, v_s_boxed_2211_, v_iters_2210_);
v_r_2213_ = lean_box_uint32(v_res_2212_);
return v_r_2213_;
}
}
LEAN_EXPORT lean_object* lp_competition_R24DotCostHarness_benchEagerPrepared___lam__1(lean_object* v_a_2214_, lean_object* v_b_2215_, lean_object* v_x_2216_){
_start:
{
lean_object* v___x_2217_; lean_object* v___x_2218_; lean_object* v___x_2219_; 
v___x_2217_ = lp_competition_Submission_R24DotProbe_prepareEagerOperand(v_a_2214_);
v___x_2218_ = lp_competition_Submission_R24DotProbe_prepareEagerOperand(v_b_2215_);
v___x_2219_ = lean_alloc_ctor(0, 2, 0);
lean_ctor_set(v___x_2219_, 0, v___x_2217_);
lean_ctor_set(v___x_2219_, 1, v___x_2218_);
return v___x_2219_;
}
}
LEAN_EXPORT uint32_t lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchEagerPrepared_spec__0___redArg___lam__0(lean_object* v_a_2220_, lean_object* v_x_2221_){
_start:
{
lean_object* v_fst_2222_; lean_object* v_snd_2223_; uint32_t v___x_2224_; 
v_fst_2222_ = lean_ctor_get(v_a_2220_, 0);
lean_inc(v_fst_2222_);
v_snd_2223_ = lean_ctor_get(v_a_2220_, 1);
lean_inc(v_snd_2223_);
lean_dec_ref(v_a_2220_);
v___x_2224_ = lp_competition_Submission_R24DotProbe_eagerPrepared(v_fst_2222_, v_snd_2223_);
return v___x_2224_;
}
}
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchEagerPrepared_spec__0___redArg___lam__0___boxed(lean_object* v_a_2225_, lean_object* v_x_2226_){
_start:
{
uint32_t v_res_2227_; lean_object* v_r_2228_; 
v_res_2227_ = lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchEagerPrepared_spec__0___redArg___lam__0(v_a_2225_, v_x_2226_);
v_r_2228_ = lean_box_uint32(v_res_2227_);
return v_r_2228_;
}
}
LEAN_EXPORT uint32_t lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchEagerPrepared_spec__0___redArg___lam__1(lean_object* v_a_2229_, uint32_t v___x_2230_, lean_object* v_iters_2231_, lean_object* v_x_2232_){
_start:
{
uint32_t v___x_2233_; 
v___x_2233_ = lp_competition_R24DotCostHarness_passEagerPrepared(v_a_2229_, v___x_2230_, v_iters_2231_);
return v___x_2233_;
}
}
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchEagerPrepared_spec__0___redArg___lam__1___boxed(lean_object* v_a_2234_, lean_object* v___x_2235_, lean_object* v_iters_2236_, lean_object* v_x_2237_){
_start:
{
uint32_t v___x_1802__boxed_2238_; uint32_t v_res_2239_; lean_object* v_r_2240_; 
v___x_1802__boxed_2238_ = lean_unbox_uint32(v___x_2235_);
lean_dec(v___x_2235_);
v_res_2239_ = lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchEagerPrepared_spec__0___redArg___lam__1(v_a_2234_, v___x_1802__boxed_2238_, v_iters_2236_, v_x_2237_);
v_r_2240_ = lean_box_uint32(v_res_2239_);
return v_r_2240_;
}
}
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00__private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchEagerPrepared_spec__0_spec__0___redArg(lean_object* v_a_2244_, lean_object* v_c_2245_, uint32_t v_expected_2246_, lean_object* v_iters_2247_, lean_object* v___x_2248_, lean_object* v_range_2249_, lean_object* v_b_2250_, lean_object* v_i_2251_){
_start:
{
lean_object* v_stop_2253_; lean_object* v_step_2254_; uint8_t v___x_2255_; 
v_stop_2253_ = lean_ctor_get(v_range_2249_, 1);
v_step_2254_ = lean_ctor_get(v_range_2249_, 2);
v___x_2255_ = lean_nat_dec_lt(v_i_2251_, v_stop_2253_);
if (v___x_2255_ == 0)
{
lean_object* v___x_2256_; 
lean_dec(v_i_2251_);
lean_dec(v___x_2248_);
lean_dec(v_iters_2247_);
lean_dec_ref(v_c_2245_);
lean_dec_ref(v_a_2244_);
v___x_2256_ = lean_alloc_ctor(0, 1, 0);
lean_ctor_set(v___x_2256_, 0, v_b_2250_);
return v___x_2256_;
}
else
{
lean_object* v___f_2257_; lean_object* v___x_2258_; lean_object* v_a_2259_; lean_object* v_name_2260_; lean_object* v___x_2261_; uint32_t v___x_2262_; lean_object* v___x_2263_; 
lean_inc_ref(v_a_2244_);
v___f_2257_ = lean_alloc_closure((void*)(lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchEagerPrepared_spec__0___redArg___lam__0___boxed), 2, 1);
lean_closure_set(v___f_2257_, 0, v_a_2244_);
lean_inc_ref(v___f_2257_);
v___x_2258_ = l_IO_lazyPure___redArg(v___f_2257_);
v_a_2259_ = lean_ctor_get(v___x_2258_, 0);
lean_inc(v_a_2259_);
lean_dec_ref(v___x_2258_);
v_name_2260_ = lean_ctor_get(v_c_2245_, 0);
v___x_2261_ = ((lean_object*)(lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00__private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchEagerPrepared_spec__0_spec__0___redArg___closed__0));
v___x_2262_ = lean_unbox_uint32(v_a_2259_);
lean_dec(v_a_2259_);
lean_inc_ref(v_name_2260_);
v___x_2263_ = lp_competition_R24DotCostHarness_checkWord(v_name_2260_, v___x_2261_, v___x_2262_, v_expected_2246_);
if (lean_obj_tag(v___x_2263_) == 0)
{
lean_object* v___x_2264_; uint32_t v___x_2265_; lean_object* v___x_2266_; lean_object* v___f_2267_; lean_object* v___x_2268_; lean_object* v_a_2269_; lean_object* v___x_2270_; uint32_t v___x_2271_; lean_object* v___x_2272_; uint32_t v___x_2273_; lean_object* v___x_2274_; 
lean_dec_ref_known(v___x_2263_, 1);
v___x_2264_ = lean_io_mono_nanos_now();
v___x_2265_ = lp_competition_R24DotCostHarness_seed(v_i_2251_);
v___x_2266_ = lean_box_uint32(v___x_2265_);
lean_inc(v_iters_2247_);
lean_inc_ref(v_a_2244_);
v___f_2267_ = lean_alloc_closure((void*)(lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchEagerPrepared_spec__0___redArg___lam__1___boxed), 4, 3);
lean_closure_set(v___f_2267_, 0, v_a_2244_);
lean_closure_set(v___f_2267_, 1, v___x_2266_);
lean_closure_set(v___f_2267_, 2, v_iters_2247_);
v___x_2268_ = l_IO_lazyPure___redArg(v___f_2267_);
v_a_2269_ = lean_ctor_get(v___x_2268_, 0);
lean_inc(v_a_2269_);
lean_dec_ref(v___x_2268_);
v___x_2270_ = lean_io_mono_nanos_now();
v___x_2271_ = lp_competition_R24DotCostHarness_sinkExpected(v___x_2265_, v_expected_2246_, v_iters_2247_);
v___x_2272_ = ((lean_object*)(lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00__private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchEagerPrepared_spec__0_spec__0___redArg___closed__1));
v___x_2273_ = lean_unbox_uint32(v_a_2269_);
lean_inc_ref(v_name_2260_);
v___x_2274_ = lp_competition_R24DotCostHarness_checkWord(v_name_2260_, v___x_2272_, v___x_2273_, v___x_2271_);
if (lean_obj_tag(v___x_2274_) == 0)
{
lean_object* v___x_2275_; lean_object* v_a_2276_; lean_object* v___x_2277_; uint32_t v___x_2278_; lean_object* v___x_2279_; 
lean_dec_ref_known(v___x_2274_, 1);
v___x_2275_ = l_IO_lazyPure___redArg(v___f_2257_);
v_a_2276_ = lean_ctor_get(v___x_2275_, 0);
lean_inc(v_a_2276_);
lean_dec_ref(v___x_2275_);
v___x_2277_ = ((lean_object*)(lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00__private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchEagerPrepared_spec__0_spec__0___redArg___closed__2));
v___x_2278_ = lean_unbox_uint32(v_a_2276_);
lean_inc_ref(v_name_2260_);
v___x_2279_ = lp_competition_R24DotCostHarness_checkWord(v_name_2260_, v___x_2277_, v___x_2278_, v_expected_2246_);
if (lean_obj_tag(v___x_2279_) == 0)
{
lean_object* v___x_2280_; lean_object* v___x_2281_; uint32_t v___x_2282_; uint32_t v___x_2283_; lean_object* v___x_2284_; lean_object* v___x_2285_; 
lean_dec_ref_known(v___x_2279_, 1);
v___x_2280_ = lean_nat_sub(v___x_2270_, v___x_2264_);
lean_dec(v___x_2264_);
lean_dec(v___x_2270_);
lean_inc(v_iters_2247_);
lean_inc(v___x_2248_);
lean_inc(v_i_2251_);
v___x_2281_ = lean_alloc_ctor(0, 4, 12);
lean_ctor_set(v___x_2281_, 0, v_i_2251_);
lean_ctor_set(v___x_2281_, 1, v___x_2248_);
lean_ctor_set(v___x_2281_, 2, v_iters_2247_);
lean_ctor_set(v___x_2281_, 3, v___x_2280_);
v___x_2282_ = lean_unbox_uint32(v_a_2269_);
lean_dec(v_a_2269_);
lean_ctor_set_uint32(v___x_2281_, sizeof(void*)*4, v___x_2282_);
lean_ctor_set_uint32(v___x_2281_, sizeof(void*)*4 + 4, v___x_2271_);
v___x_2283_ = lean_unbox_uint32(v_a_2276_);
lean_dec(v_a_2276_);
lean_ctor_set_uint32(v___x_2281_, sizeof(void*)*4 + 8, v___x_2283_);
v___x_2284_ = lean_array_push(v_b_2250_, v___x_2281_);
v___x_2285_ = lean_nat_add(v_i_2251_, v_step_2254_);
lean_dec(v_i_2251_);
v_b_2250_ = v___x_2284_;
v_i_2251_ = v___x_2285_;
goto _start;
}
else
{
lean_object* v_a_2287_; lean_object* v___x_2289_; uint8_t v_isShared_2290_; uint8_t v_isSharedCheck_2294_; 
lean_dec(v_a_2276_);
lean_dec(v___x_2270_);
lean_dec(v_a_2269_);
lean_dec(v___x_2264_);
lean_dec(v_i_2251_);
lean_dec_ref(v_b_2250_);
lean_dec(v___x_2248_);
lean_dec(v_iters_2247_);
lean_dec_ref(v_c_2245_);
lean_dec_ref(v_a_2244_);
v_a_2287_ = lean_ctor_get(v___x_2279_, 0);
v_isSharedCheck_2294_ = !lean_is_exclusive(v___x_2279_);
if (v_isSharedCheck_2294_ == 0)
{
v___x_2289_ = v___x_2279_;
v_isShared_2290_ = v_isSharedCheck_2294_;
goto v_resetjp_2288_;
}
else
{
lean_inc(v_a_2287_);
lean_dec(v___x_2279_);
v___x_2289_ = lean_box(0);
v_isShared_2290_ = v_isSharedCheck_2294_;
goto v_resetjp_2288_;
}
v_resetjp_2288_:
{
lean_object* v___x_2292_; 
if (v_isShared_2290_ == 0)
{
v___x_2292_ = v___x_2289_;
goto v_reusejp_2291_;
}
else
{
lean_object* v_reuseFailAlloc_2293_; 
v_reuseFailAlloc_2293_ = lean_alloc_ctor(1, 1, 0);
lean_ctor_set(v_reuseFailAlloc_2293_, 0, v_a_2287_);
v___x_2292_ = v_reuseFailAlloc_2293_;
goto v_reusejp_2291_;
}
v_reusejp_2291_:
{
return v___x_2292_;
}
}
}
}
else
{
lean_object* v_a_2295_; lean_object* v___x_2297_; uint8_t v_isShared_2298_; uint8_t v_isSharedCheck_2302_; 
lean_dec(v___x_2270_);
lean_dec(v_a_2269_);
lean_dec(v___x_2264_);
lean_dec_ref(v___f_2257_);
lean_dec(v_i_2251_);
lean_dec_ref(v_b_2250_);
lean_dec(v___x_2248_);
lean_dec(v_iters_2247_);
lean_dec_ref(v_c_2245_);
lean_dec_ref(v_a_2244_);
v_a_2295_ = lean_ctor_get(v___x_2274_, 0);
v_isSharedCheck_2302_ = !lean_is_exclusive(v___x_2274_);
if (v_isSharedCheck_2302_ == 0)
{
v___x_2297_ = v___x_2274_;
v_isShared_2298_ = v_isSharedCheck_2302_;
goto v_resetjp_2296_;
}
else
{
lean_inc(v_a_2295_);
lean_dec(v___x_2274_);
v___x_2297_ = lean_box(0);
v_isShared_2298_ = v_isSharedCheck_2302_;
goto v_resetjp_2296_;
}
v_resetjp_2296_:
{
lean_object* v___x_2300_; 
if (v_isShared_2298_ == 0)
{
v___x_2300_ = v___x_2297_;
goto v_reusejp_2299_;
}
else
{
lean_object* v_reuseFailAlloc_2301_; 
v_reuseFailAlloc_2301_ = lean_alloc_ctor(1, 1, 0);
lean_ctor_set(v_reuseFailAlloc_2301_, 0, v_a_2295_);
v___x_2300_ = v_reuseFailAlloc_2301_;
goto v_reusejp_2299_;
}
v_reusejp_2299_:
{
return v___x_2300_;
}
}
}
}
else
{
lean_object* v_a_2303_; lean_object* v___x_2305_; uint8_t v_isShared_2306_; uint8_t v_isSharedCheck_2310_; 
lean_dec_ref(v___f_2257_);
lean_dec(v_i_2251_);
lean_dec_ref(v_b_2250_);
lean_dec(v___x_2248_);
lean_dec(v_iters_2247_);
lean_dec_ref(v_c_2245_);
lean_dec_ref(v_a_2244_);
v_a_2303_ = lean_ctor_get(v___x_2263_, 0);
v_isSharedCheck_2310_ = !lean_is_exclusive(v___x_2263_);
if (v_isSharedCheck_2310_ == 0)
{
v___x_2305_ = v___x_2263_;
v_isShared_2306_ = v_isSharedCheck_2310_;
goto v_resetjp_2304_;
}
else
{
lean_inc(v_a_2303_);
lean_dec(v___x_2263_);
v___x_2305_ = lean_box(0);
v_isShared_2306_ = v_isSharedCheck_2310_;
goto v_resetjp_2304_;
}
v_resetjp_2304_:
{
lean_object* v___x_2308_; 
if (v_isShared_2306_ == 0)
{
v___x_2308_ = v___x_2305_;
goto v_reusejp_2307_;
}
else
{
lean_object* v_reuseFailAlloc_2309_; 
v_reuseFailAlloc_2309_ = lean_alloc_ctor(1, 1, 0);
lean_ctor_set(v_reuseFailAlloc_2309_, 0, v_a_2303_);
v___x_2308_ = v_reuseFailAlloc_2309_;
goto v_reusejp_2307_;
}
v_reusejp_2307_:
{
return v___x_2308_;
}
}
}
}
}
}
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00__private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchEagerPrepared_spec__0_spec__0___redArg___boxed(lean_object* v_a_2311_, lean_object* v_c_2312_, lean_object* v_expected_2313_, lean_object* v_iters_2314_, lean_object* v___x_2315_, lean_object* v_range_2316_, lean_object* v_b_2317_, lean_object* v_i_2318_, lean_object* v___y_2319_){
_start:
{
uint32_t v_expected_boxed_2320_; lean_object* v_res_2321_; 
v_expected_boxed_2320_ = lean_unbox_uint32(v_expected_2313_);
lean_dec(v_expected_2313_);
v_res_2321_ = lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00__private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchEagerPrepared_spec__0_spec__0___redArg(v_a_2311_, v_c_2312_, v_expected_boxed_2320_, v_iters_2314_, v___x_2315_, v_range_2316_, v_b_2317_, v_i_2318_);
lean_dec_ref(v_range_2316_);
return v_res_2321_;
}
}
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchEagerPrepared_spec__0___redArg(lean_object* v_a_2322_, lean_object* v_c_2323_, uint32_t v_expected_2324_, lean_object* v_iters_2325_, lean_object* v___x_2326_, lean_object* v_range_2327_, lean_object* v_b_2328_, lean_object* v_i_2329_){
_start:
{
lean_object* v_stop_2331_; lean_object* v_step_2332_; uint8_t v___x_2333_; 
v_stop_2331_ = lean_ctor_get(v_range_2327_, 1);
v_step_2332_ = lean_ctor_get(v_range_2327_, 2);
v___x_2333_ = lean_nat_dec_lt(v_i_2329_, v_stop_2331_);
if (v___x_2333_ == 0)
{
lean_object* v___x_2334_; 
lean_dec(v_i_2329_);
lean_dec(v___x_2326_);
lean_dec(v_iters_2325_);
lean_dec_ref(v_c_2323_);
lean_dec_ref(v_a_2322_);
v___x_2334_ = lean_alloc_ctor(0, 1, 0);
lean_ctor_set(v___x_2334_, 0, v_b_2328_);
return v___x_2334_;
}
else
{
lean_object* v___f_2335_; lean_object* v___x_2336_; lean_object* v_a_2337_; lean_object* v_name_2338_; lean_object* v___x_2339_; uint32_t v___x_2340_; lean_object* v___x_2341_; 
lean_inc_ref(v_a_2322_);
v___f_2335_ = lean_alloc_closure((void*)(lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchEagerPrepared_spec__0___redArg___lam__0___boxed), 2, 1);
lean_closure_set(v___f_2335_, 0, v_a_2322_);
lean_inc_ref(v___f_2335_);
v___x_2336_ = l_IO_lazyPure___redArg(v___f_2335_);
v_a_2337_ = lean_ctor_get(v___x_2336_, 0);
lean_inc(v_a_2337_);
lean_dec_ref(v___x_2336_);
v_name_2338_ = lean_ctor_get(v_c_2323_, 0);
v___x_2339_ = ((lean_object*)(lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00__private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchEagerPrepared_spec__0_spec__0___redArg___closed__0));
v___x_2340_ = lean_unbox_uint32(v_a_2337_);
lean_dec(v_a_2337_);
lean_inc_ref(v_name_2338_);
v___x_2341_ = lp_competition_R24DotCostHarness_checkWord(v_name_2338_, v___x_2339_, v___x_2340_, v_expected_2324_);
if (lean_obj_tag(v___x_2341_) == 0)
{
lean_object* v___x_2342_; uint32_t v___x_2343_; lean_object* v___x_2344_; lean_object* v___f_2345_; lean_object* v___x_2346_; lean_object* v_a_2347_; lean_object* v___x_2348_; uint32_t v___x_2349_; lean_object* v___x_2350_; uint32_t v___x_2351_; lean_object* v___x_2352_; 
lean_dec_ref_known(v___x_2341_, 1);
v___x_2342_ = lean_io_mono_nanos_now();
v___x_2343_ = lp_competition_R24DotCostHarness_seed(v_i_2329_);
v___x_2344_ = lean_box_uint32(v___x_2343_);
lean_inc(v_iters_2325_);
lean_inc_ref(v_a_2322_);
v___f_2345_ = lean_alloc_closure((void*)(lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchEagerPrepared_spec__0___redArg___lam__1___boxed), 4, 3);
lean_closure_set(v___f_2345_, 0, v_a_2322_);
lean_closure_set(v___f_2345_, 1, v___x_2344_);
lean_closure_set(v___f_2345_, 2, v_iters_2325_);
v___x_2346_ = l_IO_lazyPure___redArg(v___f_2345_);
v_a_2347_ = lean_ctor_get(v___x_2346_, 0);
lean_inc(v_a_2347_);
lean_dec_ref(v___x_2346_);
v___x_2348_ = lean_io_mono_nanos_now();
v___x_2349_ = lp_competition_R24DotCostHarness_sinkExpected(v___x_2343_, v_expected_2324_, v_iters_2325_);
v___x_2350_ = ((lean_object*)(lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00__private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchEagerPrepared_spec__0_spec__0___redArg___closed__1));
v___x_2351_ = lean_unbox_uint32(v_a_2347_);
lean_inc_ref(v_name_2338_);
v___x_2352_ = lp_competition_R24DotCostHarness_checkWord(v_name_2338_, v___x_2350_, v___x_2351_, v___x_2349_);
if (lean_obj_tag(v___x_2352_) == 0)
{
lean_object* v___x_2353_; lean_object* v_a_2354_; lean_object* v___x_2355_; uint32_t v___x_2356_; lean_object* v___x_2357_; 
lean_dec_ref_known(v___x_2352_, 1);
v___x_2353_ = l_IO_lazyPure___redArg(v___f_2335_);
v_a_2354_ = lean_ctor_get(v___x_2353_, 0);
lean_inc(v_a_2354_);
lean_dec_ref(v___x_2353_);
v___x_2355_ = ((lean_object*)(lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00__private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchEagerPrepared_spec__0_spec__0___redArg___closed__2));
v___x_2356_ = lean_unbox_uint32(v_a_2354_);
lean_inc_ref(v_name_2338_);
v___x_2357_ = lp_competition_R24DotCostHarness_checkWord(v_name_2338_, v___x_2355_, v___x_2356_, v_expected_2324_);
if (lean_obj_tag(v___x_2357_) == 0)
{
lean_object* v___x_2358_; lean_object* v___x_2359_; uint32_t v___x_2360_; uint32_t v___x_2361_; lean_object* v___x_2362_; lean_object* v___x_2363_; lean_object* v___x_2364_; 
lean_dec_ref_known(v___x_2357_, 1);
v___x_2358_ = lean_nat_sub(v___x_2348_, v___x_2342_);
lean_dec(v___x_2342_);
lean_dec(v___x_2348_);
lean_inc(v_iters_2325_);
lean_inc(v___x_2326_);
lean_inc(v_i_2329_);
v___x_2359_ = lean_alloc_ctor(0, 4, 12);
lean_ctor_set(v___x_2359_, 0, v_i_2329_);
lean_ctor_set(v___x_2359_, 1, v___x_2326_);
lean_ctor_set(v___x_2359_, 2, v_iters_2325_);
lean_ctor_set(v___x_2359_, 3, v___x_2358_);
v___x_2360_ = lean_unbox_uint32(v_a_2347_);
lean_dec(v_a_2347_);
lean_ctor_set_uint32(v___x_2359_, sizeof(void*)*4, v___x_2360_);
lean_ctor_set_uint32(v___x_2359_, sizeof(void*)*4 + 4, v___x_2349_);
v___x_2361_ = lean_unbox_uint32(v_a_2354_);
lean_dec(v_a_2354_);
lean_ctor_set_uint32(v___x_2359_, sizeof(void*)*4 + 8, v___x_2361_);
v___x_2362_ = lean_array_push(v_b_2328_, v___x_2359_);
v___x_2363_ = lean_nat_add(v_i_2329_, v_step_2332_);
lean_dec(v_i_2329_);
v___x_2364_ = lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00__private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchEagerPrepared_spec__0_spec__0___redArg(v_a_2322_, v_c_2323_, v_expected_2324_, v_iters_2325_, v___x_2326_, v_range_2327_, v___x_2362_, v___x_2363_);
return v___x_2364_;
}
else
{
lean_object* v_a_2365_; lean_object* v___x_2367_; uint8_t v_isShared_2368_; uint8_t v_isSharedCheck_2372_; 
lean_dec(v_a_2354_);
lean_dec(v___x_2348_);
lean_dec(v_a_2347_);
lean_dec(v___x_2342_);
lean_dec(v_i_2329_);
lean_dec_ref(v_b_2328_);
lean_dec(v___x_2326_);
lean_dec(v_iters_2325_);
lean_dec_ref(v_c_2323_);
lean_dec_ref(v_a_2322_);
v_a_2365_ = lean_ctor_get(v___x_2357_, 0);
v_isSharedCheck_2372_ = !lean_is_exclusive(v___x_2357_);
if (v_isSharedCheck_2372_ == 0)
{
v___x_2367_ = v___x_2357_;
v_isShared_2368_ = v_isSharedCheck_2372_;
goto v_resetjp_2366_;
}
else
{
lean_inc(v_a_2365_);
lean_dec(v___x_2357_);
v___x_2367_ = lean_box(0);
v_isShared_2368_ = v_isSharedCheck_2372_;
goto v_resetjp_2366_;
}
v_resetjp_2366_:
{
lean_object* v___x_2370_; 
if (v_isShared_2368_ == 0)
{
v___x_2370_ = v___x_2367_;
goto v_reusejp_2369_;
}
else
{
lean_object* v_reuseFailAlloc_2371_; 
v_reuseFailAlloc_2371_ = lean_alloc_ctor(1, 1, 0);
lean_ctor_set(v_reuseFailAlloc_2371_, 0, v_a_2365_);
v___x_2370_ = v_reuseFailAlloc_2371_;
goto v_reusejp_2369_;
}
v_reusejp_2369_:
{
return v___x_2370_;
}
}
}
}
else
{
lean_object* v_a_2373_; lean_object* v___x_2375_; uint8_t v_isShared_2376_; uint8_t v_isSharedCheck_2380_; 
lean_dec(v___x_2348_);
lean_dec(v_a_2347_);
lean_dec(v___x_2342_);
lean_dec_ref(v___f_2335_);
lean_dec(v_i_2329_);
lean_dec_ref(v_b_2328_);
lean_dec(v___x_2326_);
lean_dec(v_iters_2325_);
lean_dec_ref(v_c_2323_);
lean_dec_ref(v_a_2322_);
v_a_2373_ = lean_ctor_get(v___x_2352_, 0);
v_isSharedCheck_2380_ = !lean_is_exclusive(v___x_2352_);
if (v_isSharedCheck_2380_ == 0)
{
v___x_2375_ = v___x_2352_;
v_isShared_2376_ = v_isSharedCheck_2380_;
goto v_resetjp_2374_;
}
else
{
lean_inc(v_a_2373_);
lean_dec(v___x_2352_);
v___x_2375_ = lean_box(0);
v_isShared_2376_ = v_isSharedCheck_2380_;
goto v_resetjp_2374_;
}
v_resetjp_2374_:
{
lean_object* v___x_2378_; 
if (v_isShared_2376_ == 0)
{
v___x_2378_ = v___x_2375_;
goto v_reusejp_2377_;
}
else
{
lean_object* v_reuseFailAlloc_2379_; 
v_reuseFailAlloc_2379_ = lean_alloc_ctor(1, 1, 0);
lean_ctor_set(v_reuseFailAlloc_2379_, 0, v_a_2373_);
v___x_2378_ = v_reuseFailAlloc_2379_;
goto v_reusejp_2377_;
}
v_reusejp_2377_:
{
return v___x_2378_;
}
}
}
}
else
{
lean_object* v_a_2381_; lean_object* v___x_2383_; uint8_t v_isShared_2384_; uint8_t v_isSharedCheck_2388_; 
lean_dec_ref(v___f_2335_);
lean_dec(v_i_2329_);
lean_dec_ref(v_b_2328_);
lean_dec(v___x_2326_);
lean_dec(v_iters_2325_);
lean_dec_ref(v_c_2323_);
lean_dec_ref(v_a_2322_);
v_a_2381_ = lean_ctor_get(v___x_2341_, 0);
v_isSharedCheck_2388_ = !lean_is_exclusive(v___x_2341_);
if (v_isSharedCheck_2388_ == 0)
{
v___x_2383_ = v___x_2341_;
v_isShared_2384_ = v_isSharedCheck_2388_;
goto v_resetjp_2382_;
}
else
{
lean_inc(v_a_2381_);
lean_dec(v___x_2341_);
v___x_2383_ = lean_box(0);
v_isShared_2384_ = v_isSharedCheck_2388_;
goto v_resetjp_2382_;
}
v_resetjp_2382_:
{
lean_object* v___x_2386_; 
if (v_isShared_2384_ == 0)
{
v___x_2386_ = v___x_2383_;
goto v_reusejp_2385_;
}
else
{
lean_object* v_reuseFailAlloc_2387_; 
v_reuseFailAlloc_2387_ = lean_alloc_ctor(1, 1, 0);
lean_ctor_set(v_reuseFailAlloc_2387_, 0, v_a_2381_);
v___x_2386_ = v_reuseFailAlloc_2387_;
goto v_reusejp_2385_;
}
v_reusejp_2385_:
{
return v___x_2386_;
}
}
}
}
}
}
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchEagerPrepared_spec__0___redArg___boxed(lean_object* v_a_2389_, lean_object* v_c_2390_, lean_object* v_expected_2391_, lean_object* v_iters_2392_, lean_object* v___x_2393_, lean_object* v_range_2394_, lean_object* v_b_2395_, lean_object* v_i_2396_, lean_object* v___y_2397_){
_start:
{
uint32_t v_expected_boxed_2398_; lean_object* v_res_2399_; 
v_expected_boxed_2398_ = lean_unbox_uint32(v_expected_2391_);
lean_dec(v_expected_2391_);
v_res_2399_ = lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchEagerPrepared_spec__0___redArg(v_a_2389_, v_c_2390_, v_expected_boxed_2398_, v_iters_2392_, v___x_2393_, v_range_2394_, v_b_2395_, v_i_2396_);
lean_dec_ref(v_range_2394_);
return v_res_2399_;
}
}
LEAN_EXPORT lean_object* lp_competition_R24DotCostHarness_benchEagerPrepared(lean_object* v_c_2400_, lean_object* v_a_2401_, lean_object* v_b_2402_, lean_object* v_macs_2403_){
_start:
{
lean_object* v___x_2405_; lean_object* v_a_2406_; lean_object* v___x_2407_; lean_object* v_a_2408_; lean_object* v___f_2409_; lean_object* v___x_2410_; lean_object* v_a_2411_; lean_object* v___x_2412_; lean_object* v_a_2413_; lean_object* v_expected_2414_; uint32_t v_expected_2415_; lean_object* v___x_2416_; lean_object* v_iters_2417_; lean_object* v___x_2418_; lean_object* v___x_2419_; lean_object* v___x_2420_; lean_object* v___x_2421_; 
v___x_2405_ = lp_competition_R24DotCostHarness_benchExactFull___lam__0();
v_a_2406_ = lean_ctor_get(v___x_2405_, 0);
lean_inc(v_a_2406_);
lean_dec_ref(v___x_2405_);
v___x_2407_ = lp_competition_R24DotCostHarness_benchExactFull___lam__0();
v_a_2408_ = lean_ctor_get(v___x_2407_, 0);
lean_inc(v_a_2408_);
lean_dec_ref(v___x_2407_);
lean_inc_ref(v_a_2401_);
v___f_2409_ = lean_alloc_closure((void*)(lp_competition_R24DotCostHarness_benchEagerPrepared___lam__1), 3, 2);
lean_closure_set(v___f_2409_, 0, v_a_2401_);
lean_closure_set(v___f_2409_, 1, v_b_2402_);
v___x_2410_ = l_IO_lazyPure___redArg(v___f_2409_);
v_a_2411_ = lean_ctor_get(v___x_2410_, 0);
lean_inc(v_a_2411_);
lean_dec_ref(v___x_2410_);
v___x_2412_ = lp_competition_R24DotCostHarness_benchExactFull___lam__0();
v_a_2413_ = lean_ctor_get(v___x_2412_, 0);
lean_inc(v_a_2413_);
lean_dec_ref(v___x_2412_);
v_expected_2414_ = lean_ctor_get(v_c_2400_, 5);
v_expected_2415_ = lean_uint32_of_nat(v_expected_2414_);
v___x_2416_ = lean_array_get_size(v_a_2401_);
lean_dec_ref(v_a_2401_);
v_iters_2417_ = lp_competition_R24DotCostHarness_repeats(v_macs_2403_, v___x_2416_);
v___x_2418_ = lean_unsigned_to_nat(0u);
v___x_2419_ = ((lean_object*)(lp_competition_R24DotCostHarness_benchExactFull___closed__0));
v___x_2420_ = ((lean_object*)(lp_competition_R24DotCostHarness_benchExactFull___closed__1));
lean_inc_ref(v_c_2400_);
v___x_2421_ = lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchEagerPrepared_spec__0___redArg(v_a_2411_, v_c_2400_, v_expected_2415_, v_iters_2417_, v___x_2416_, v___x_2420_, v___x_2419_, v___x_2418_);
if (lean_obj_tag(v___x_2421_) == 0)
{
lean_object* v_a_2422_; lean_object* v___x_2423_; lean_object* v_a_2424_; lean_object* v___x_2425_; lean_object* v___x_2426_; lean_object* v___x_2427_; lean_object* v___x_2428_; lean_object* v___x_2429_; 
v_a_2422_ = lean_ctor_get(v___x_2421_, 0);
lean_inc(v_a_2422_);
lean_dec_ref_known(v___x_2421_, 1);
v___x_2423_ = lp_competition_R24DotCostHarness_benchExactFull___lam__0();
v_a_2424_ = lean_ctor_get(v___x_2423_, 0);
lean_inc(v_a_2424_);
lean_dec_ref(v___x_2423_);
v___x_2425_ = lean_nat_sub(v_a_2413_, v_a_2408_);
lean_dec(v_a_2408_);
lean_dec(v_a_2413_);
v___x_2426_ = ((lean_object*)(lp_competition_R24DotCostHarness_benchEagerFull___closed__0));
v___x_2427_ = ((lean_object*)(lp_competition_R24DotCostHarness_benchExactPrepared___closed__0));
v___x_2428_ = lean_nat_sub(v_a_2424_, v_a_2406_);
lean_dec(v_a_2406_);
lean_dec(v_a_2424_);
v___x_2429_ = lp_competition_R24DotCostHarness_emit(v_c_2400_, v___x_2426_, v___x_2427_, v___x_2425_, v___x_2428_, v_a_2422_);
lean_dec(v_a_2422_);
lean_dec_ref(v_c_2400_);
return v___x_2429_;
}
else
{
lean_object* v_a_2430_; lean_object* v___x_2432_; uint8_t v_isShared_2433_; uint8_t v_isSharedCheck_2437_; 
lean_dec(v_a_2413_);
lean_dec(v_a_2408_);
lean_dec(v_a_2406_);
lean_dec_ref(v_c_2400_);
v_a_2430_ = lean_ctor_get(v___x_2421_, 0);
v_isSharedCheck_2437_ = !lean_is_exclusive(v___x_2421_);
if (v_isSharedCheck_2437_ == 0)
{
v___x_2432_ = v___x_2421_;
v_isShared_2433_ = v_isSharedCheck_2437_;
goto v_resetjp_2431_;
}
else
{
lean_inc(v_a_2430_);
lean_dec(v___x_2421_);
v___x_2432_ = lean_box(0);
v_isShared_2433_ = v_isSharedCheck_2437_;
goto v_resetjp_2431_;
}
v_resetjp_2431_:
{
lean_object* v___x_2435_; 
if (v_isShared_2433_ == 0)
{
v___x_2435_ = v___x_2432_;
goto v_reusejp_2434_;
}
else
{
lean_object* v_reuseFailAlloc_2436_; 
v_reuseFailAlloc_2436_ = lean_alloc_ctor(1, 1, 0);
lean_ctor_set(v_reuseFailAlloc_2436_, 0, v_a_2430_);
v___x_2435_ = v_reuseFailAlloc_2436_;
goto v_reusejp_2434_;
}
v_reusejp_2434_:
{
return v___x_2435_;
}
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_R24DotCostHarness_benchEagerPrepared___boxed(lean_object* v_c_2438_, lean_object* v_a_2439_, lean_object* v_b_2440_, lean_object* v_macs_2441_, lean_object* v_a_2442_){
_start:
{
lean_object* v_res_2443_; 
v_res_2443_ = lp_competition_R24DotCostHarness_benchEagerPrepared(v_c_2438_, v_a_2439_, v_b_2440_, v_macs_2441_);
lean_dec(v_macs_2441_);
return v_res_2443_;
}
}
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchEagerPrepared_spec__0(lean_object* v_a_2444_, lean_object* v_c_2445_, uint32_t v_expected_2446_, lean_object* v_iters_2447_, lean_object* v___x_2448_, lean_object* v_range_2449_, lean_object* v_b_2450_, lean_object* v_i_2451_, lean_object* v_hs_2452_, lean_object* v_hl_2453_){
_start:
{
lean_object* v___x_2455_; 
v___x_2455_ = lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchEagerPrepared_spec__0___redArg(v_a_2444_, v_c_2445_, v_expected_2446_, v_iters_2447_, v___x_2448_, v_range_2449_, v_b_2450_, v_i_2451_);
return v___x_2455_;
}
}
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchEagerPrepared_spec__0___boxed(lean_object* v_a_2456_, lean_object* v_c_2457_, lean_object* v_expected_2458_, lean_object* v_iters_2459_, lean_object* v___x_2460_, lean_object* v_range_2461_, lean_object* v_b_2462_, lean_object* v_i_2463_, lean_object* v_hs_2464_, lean_object* v_hl_2465_, lean_object* v___y_2466_){
_start:
{
uint32_t v_expected_boxed_2467_; lean_object* v_res_2468_; 
v_expected_boxed_2467_ = lean_unbox_uint32(v_expected_2458_);
lean_dec(v_expected_2458_);
v_res_2468_ = lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchEagerPrepared_spec__0(v_a_2456_, v_c_2457_, v_expected_boxed_2467_, v_iters_2459_, v___x_2460_, v_range_2461_, v_b_2462_, v_i_2463_, v_hs_2464_, v_hl_2465_);
lean_dec_ref(v_range_2461_);
return v_res_2468_;
}
}
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00__private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchEagerPrepared_spec__0_spec__0(lean_object* v_a_2469_, lean_object* v_c_2470_, uint32_t v_expected_2471_, lean_object* v_iters_2472_, lean_object* v___x_2473_, lean_object* v_range_2474_, lean_object* v_b_2475_, lean_object* v_i_2476_, lean_object* v_hs_2477_, lean_object* v_hl_2478_){
_start:
{
lean_object* v___x_2480_; 
v___x_2480_ = lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00__private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchEagerPrepared_spec__0_spec__0___redArg(v_a_2469_, v_c_2470_, v_expected_2471_, v_iters_2472_, v___x_2473_, v_range_2474_, v_b_2475_, v_i_2476_);
return v___x_2480_;
}
}
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00__private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchEagerPrepared_spec__0_spec__0___boxed(lean_object* v_a_2481_, lean_object* v_c_2482_, lean_object* v_expected_2483_, lean_object* v_iters_2484_, lean_object* v___x_2485_, lean_object* v_range_2486_, lean_object* v_b_2487_, lean_object* v_i_2488_, lean_object* v_hs_2489_, lean_object* v_hl_2490_, lean_object* v___y_2491_){
_start:
{
uint32_t v_expected_boxed_2492_; lean_object* v_res_2493_; 
v_expected_boxed_2492_ = lean_unbox_uint32(v_expected_2483_);
lean_dec(v_expected_2483_);
v_res_2493_ = lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00__private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchEagerPrepared_spec__0_spec__0(v_a_2481_, v_c_2482_, v_expected_boxed_2492_, v_iters_2484_, v___x_2485_, v_range_2486_, v_b_2487_, v_i_2488_, v_hs_2489_, v_hl_2490_);
lean_dec_ref(v_range_2486_);
return v_res_2493_;
}
}
LEAN_EXPORT uint32_t lp_competition_R24DotCostHarness_passLazyPrepared(lean_object* v_p_2494_, uint32_t v_s_2495_, lean_object* v_iters_2496_){
_start:
{
lean_object* v_zero_2497_; uint8_t v_isZero_2498_; 
v_zero_2497_ = lean_unsigned_to_nat(0u);
v_isZero_2498_ = lean_nat_dec_eq(v_iters_2496_, v_zero_2497_);
if (v_isZero_2498_ == 1)
{
lean_dec(v_iters_2496_);
lean_dec_ref(v_p_2494_);
return v_s_2495_;
}
else
{
lean_object* v_one_2499_; lean_object* v_n_2500_; lean_object* v_p_2501_; lean_object* v_fst_2502_; lean_object* v_snd_2503_; uint32_t v_word_2504_; uint32_t v___x_2505_; 
v_one_2499_ = lean_unsigned_to_nat(1u);
v_n_2500_ = lean_nat_sub(v_iters_2496_, v_one_2499_);
lean_dec(v_iters_2496_);
v_p_2501_ = lp_competition_R24DotBarrier_touchLazy(v_n_2500_, v_p_2494_);
v_fst_2502_ = lean_ctor_get(v_p_2501_, 0);
lean_inc(v_fst_2502_);
v_snd_2503_ = lean_ctor_get(v_p_2501_, 1);
lean_inc(v_snd_2503_);
v_word_2504_ = lp_competition_Submission_R24DotProbe_lazyPrepared(v_fst_2502_, v_snd_2503_);
v___x_2505_ = lean_uint32_add(v_s_2495_, v_word_2504_);
v_p_2494_ = v_p_2501_;
v_s_2495_ = v___x_2505_;
v_iters_2496_ = v_n_2500_;
goto _start;
}
}
}
LEAN_EXPORT lean_object* lp_competition_R24DotCostHarness_passLazyPrepared___boxed(lean_object* v_p_2507_, lean_object* v_s_2508_, lean_object* v_iters_2509_){
_start:
{
uint32_t v_s_boxed_2510_; uint32_t v_res_2511_; lean_object* v_r_2512_; 
v_s_boxed_2510_ = lean_unbox_uint32(v_s_2508_);
lean_dec(v_s_2508_);
v_res_2511_ = lp_competition_R24DotCostHarness_passLazyPrepared(v_p_2507_, v_s_boxed_2510_, v_iters_2509_);
v_r_2512_ = lean_box_uint32(v_res_2511_);
return v_r_2512_;
}
}
LEAN_EXPORT lean_object* lp_competition_R24DotCostHarness_benchLazyPrepared___lam__1(lean_object* v_a_2513_, lean_object* v_b_2514_, lean_object* v_x_2515_){
_start:
{
lean_object* v___x_2516_; lean_object* v___x_2517_; lean_object* v___x_2518_; 
v___x_2516_ = lp_competition_Submission_R24PortableF64_prepare(v_a_2513_);
v___x_2517_ = lp_competition_Submission_R24PortableF64_prepare(v_b_2514_);
v___x_2518_ = lean_alloc_ctor(0, 2, 0);
lean_ctor_set(v___x_2518_, 0, v___x_2516_);
lean_ctor_set(v___x_2518_, 1, v___x_2517_);
return v___x_2518_;
}
}
LEAN_EXPORT uint32_t lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchLazyPrepared_spec__0___redArg___lam__1(lean_object* v_a_2519_, uint32_t v___x_2520_, lean_object* v_iters_2521_, lean_object* v_x_2522_){
_start:
{
uint32_t v___x_2523_; 
v___x_2523_ = lp_competition_R24DotCostHarness_passLazyPrepared(v_a_2519_, v___x_2520_, v_iters_2521_);
return v___x_2523_;
}
}
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchLazyPrepared_spec__0___redArg___lam__1___boxed(lean_object* v_a_2524_, lean_object* v___x_2525_, lean_object* v_iters_2526_, lean_object* v_x_2527_){
_start:
{
uint32_t v___x_1794__boxed_2528_; uint32_t v_res_2529_; lean_object* v_r_2530_; 
v___x_1794__boxed_2528_ = lean_unbox_uint32(v___x_2525_);
lean_dec(v___x_2525_);
v_res_2529_ = lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchLazyPrepared_spec__0___redArg___lam__1(v_a_2524_, v___x_1794__boxed_2528_, v_iters_2526_, v_x_2527_);
v_r_2530_ = lean_box_uint32(v_res_2529_);
return v_r_2530_;
}
}
LEAN_EXPORT uint32_t lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchLazyPrepared_spec__0___redArg___lam__0(lean_object* v_a_2531_, lean_object* v_x_2532_){
_start:
{
lean_object* v_fst_2533_; lean_object* v_snd_2534_; uint32_t v___x_2535_; 
v_fst_2533_ = lean_ctor_get(v_a_2531_, 0);
lean_inc(v_fst_2533_);
v_snd_2534_ = lean_ctor_get(v_a_2531_, 1);
lean_inc(v_snd_2534_);
lean_dec_ref(v_a_2531_);
v___x_2535_ = lp_competition_Submission_R24DotProbe_lazyPrepared(v_fst_2533_, v_snd_2534_);
return v___x_2535_;
}
}
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchLazyPrepared_spec__0___redArg___lam__0___boxed(lean_object* v_a_2536_, lean_object* v_x_2537_){
_start:
{
uint32_t v_res_2538_; lean_object* v_r_2539_; 
v_res_2538_ = lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchLazyPrepared_spec__0___redArg___lam__0(v_a_2536_, v_x_2537_);
v_r_2539_ = lean_box_uint32(v_res_2538_);
return v_r_2539_;
}
}
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00__private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchLazyPrepared_spec__0_spec__0___redArg(lean_object* v_a_2543_, lean_object* v_c_2544_, uint32_t v_expected_2545_, lean_object* v_iters_2546_, lean_object* v___x_2547_, lean_object* v_range_2548_, lean_object* v_b_2549_, lean_object* v_i_2550_){
_start:
{
lean_object* v_stop_2552_; lean_object* v_step_2553_; uint8_t v___x_2554_; 
v_stop_2552_ = lean_ctor_get(v_range_2548_, 1);
v_step_2553_ = lean_ctor_get(v_range_2548_, 2);
v___x_2554_ = lean_nat_dec_lt(v_i_2550_, v_stop_2552_);
if (v___x_2554_ == 0)
{
lean_object* v___x_2555_; 
lean_dec(v_i_2550_);
lean_dec(v___x_2547_);
lean_dec(v_iters_2546_);
lean_dec_ref(v_c_2544_);
lean_dec_ref(v_a_2543_);
v___x_2555_ = lean_alloc_ctor(0, 1, 0);
lean_ctor_set(v___x_2555_, 0, v_b_2549_);
return v___x_2555_;
}
else
{
lean_object* v___f_2556_; lean_object* v___x_2557_; lean_object* v_a_2558_; lean_object* v_name_2559_; lean_object* v___x_2560_; uint32_t v___x_2561_; lean_object* v___x_2562_; 
lean_inc_ref(v_a_2543_);
v___f_2556_ = lean_alloc_closure((void*)(lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchLazyPrepared_spec__0___redArg___lam__0___boxed), 2, 1);
lean_closure_set(v___f_2556_, 0, v_a_2543_);
lean_inc_ref(v___f_2556_);
v___x_2557_ = l_IO_lazyPure___redArg(v___f_2556_);
v_a_2558_ = lean_ctor_get(v___x_2557_, 0);
lean_inc(v_a_2558_);
lean_dec_ref(v___x_2557_);
v_name_2559_ = lean_ctor_get(v_c_2544_, 0);
v___x_2560_ = ((lean_object*)(lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00__private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchLazyPrepared_spec__0_spec__0___redArg___closed__0));
v___x_2561_ = lean_unbox_uint32(v_a_2558_);
lean_dec(v_a_2558_);
lean_inc_ref(v_name_2559_);
v___x_2562_ = lp_competition_R24DotCostHarness_checkWord(v_name_2559_, v___x_2560_, v___x_2561_, v_expected_2545_);
if (lean_obj_tag(v___x_2562_) == 0)
{
lean_object* v___x_2563_; uint32_t v___x_2564_; lean_object* v___x_2565_; lean_object* v___f_2566_; lean_object* v___x_2567_; lean_object* v_a_2568_; lean_object* v___x_2569_; uint32_t v___x_2570_; lean_object* v___x_2571_; uint32_t v___x_2572_; lean_object* v___x_2573_; 
lean_dec_ref_known(v___x_2562_, 1);
v___x_2563_ = lean_io_mono_nanos_now();
v___x_2564_ = lp_competition_R24DotCostHarness_seed(v_i_2550_);
v___x_2565_ = lean_box_uint32(v___x_2564_);
lean_inc(v_iters_2546_);
lean_inc_ref(v_a_2543_);
v___f_2566_ = lean_alloc_closure((void*)(lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchLazyPrepared_spec__0___redArg___lam__1___boxed), 4, 3);
lean_closure_set(v___f_2566_, 0, v_a_2543_);
lean_closure_set(v___f_2566_, 1, v___x_2565_);
lean_closure_set(v___f_2566_, 2, v_iters_2546_);
v___x_2567_ = l_IO_lazyPure___redArg(v___f_2566_);
v_a_2568_ = lean_ctor_get(v___x_2567_, 0);
lean_inc(v_a_2568_);
lean_dec_ref(v___x_2567_);
v___x_2569_ = lean_io_mono_nanos_now();
v___x_2570_ = lp_competition_R24DotCostHarness_sinkExpected(v___x_2564_, v_expected_2545_, v_iters_2546_);
v___x_2571_ = ((lean_object*)(lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00__private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchLazyPrepared_spec__0_spec__0___redArg___closed__1));
v___x_2572_ = lean_unbox_uint32(v_a_2568_);
lean_inc_ref(v_name_2559_);
v___x_2573_ = lp_competition_R24DotCostHarness_checkWord(v_name_2559_, v___x_2571_, v___x_2572_, v___x_2570_);
if (lean_obj_tag(v___x_2573_) == 0)
{
lean_object* v___x_2574_; lean_object* v_a_2575_; lean_object* v___x_2576_; uint32_t v___x_2577_; lean_object* v___x_2578_; 
lean_dec_ref_known(v___x_2573_, 1);
v___x_2574_ = l_IO_lazyPure___redArg(v___f_2556_);
v_a_2575_ = lean_ctor_get(v___x_2574_, 0);
lean_inc(v_a_2575_);
lean_dec_ref(v___x_2574_);
v___x_2576_ = ((lean_object*)(lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00__private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchLazyPrepared_spec__0_spec__0___redArg___closed__2));
v___x_2577_ = lean_unbox_uint32(v_a_2575_);
lean_inc_ref(v_name_2559_);
v___x_2578_ = lp_competition_R24DotCostHarness_checkWord(v_name_2559_, v___x_2576_, v___x_2577_, v_expected_2545_);
if (lean_obj_tag(v___x_2578_) == 0)
{
lean_object* v___x_2579_; lean_object* v___x_2580_; uint32_t v___x_2581_; uint32_t v___x_2582_; lean_object* v___x_2583_; lean_object* v___x_2584_; 
lean_dec_ref_known(v___x_2578_, 1);
v___x_2579_ = lean_nat_sub(v___x_2569_, v___x_2563_);
lean_dec(v___x_2563_);
lean_dec(v___x_2569_);
lean_inc(v_iters_2546_);
lean_inc(v___x_2547_);
lean_inc(v_i_2550_);
v___x_2580_ = lean_alloc_ctor(0, 4, 12);
lean_ctor_set(v___x_2580_, 0, v_i_2550_);
lean_ctor_set(v___x_2580_, 1, v___x_2547_);
lean_ctor_set(v___x_2580_, 2, v_iters_2546_);
lean_ctor_set(v___x_2580_, 3, v___x_2579_);
v___x_2581_ = lean_unbox_uint32(v_a_2568_);
lean_dec(v_a_2568_);
lean_ctor_set_uint32(v___x_2580_, sizeof(void*)*4, v___x_2581_);
lean_ctor_set_uint32(v___x_2580_, sizeof(void*)*4 + 4, v___x_2570_);
v___x_2582_ = lean_unbox_uint32(v_a_2575_);
lean_dec(v_a_2575_);
lean_ctor_set_uint32(v___x_2580_, sizeof(void*)*4 + 8, v___x_2582_);
v___x_2583_ = lean_array_push(v_b_2549_, v___x_2580_);
v___x_2584_ = lean_nat_add(v_i_2550_, v_step_2553_);
lean_dec(v_i_2550_);
v_b_2549_ = v___x_2583_;
v_i_2550_ = v___x_2584_;
goto _start;
}
else
{
lean_object* v_a_2586_; lean_object* v___x_2588_; uint8_t v_isShared_2589_; uint8_t v_isSharedCheck_2593_; 
lean_dec(v_a_2575_);
lean_dec(v___x_2569_);
lean_dec(v_a_2568_);
lean_dec(v___x_2563_);
lean_dec(v_i_2550_);
lean_dec_ref(v_b_2549_);
lean_dec(v___x_2547_);
lean_dec(v_iters_2546_);
lean_dec_ref(v_c_2544_);
lean_dec_ref(v_a_2543_);
v_a_2586_ = lean_ctor_get(v___x_2578_, 0);
v_isSharedCheck_2593_ = !lean_is_exclusive(v___x_2578_);
if (v_isSharedCheck_2593_ == 0)
{
v___x_2588_ = v___x_2578_;
v_isShared_2589_ = v_isSharedCheck_2593_;
goto v_resetjp_2587_;
}
else
{
lean_inc(v_a_2586_);
lean_dec(v___x_2578_);
v___x_2588_ = lean_box(0);
v_isShared_2589_ = v_isSharedCheck_2593_;
goto v_resetjp_2587_;
}
v_resetjp_2587_:
{
lean_object* v___x_2591_; 
if (v_isShared_2589_ == 0)
{
v___x_2591_ = v___x_2588_;
goto v_reusejp_2590_;
}
else
{
lean_object* v_reuseFailAlloc_2592_; 
v_reuseFailAlloc_2592_ = lean_alloc_ctor(1, 1, 0);
lean_ctor_set(v_reuseFailAlloc_2592_, 0, v_a_2586_);
v___x_2591_ = v_reuseFailAlloc_2592_;
goto v_reusejp_2590_;
}
v_reusejp_2590_:
{
return v___x_2591_;
}
}
}
}
else
{
lean_object* v_a_2594_; lean_object* v___x_2596_; uint8_t v_isShared_2597_; uint8_t v_isSharedCheck_2601_; 
lean_dec(v___x_2569_);
lean_dec(v_a_2568_);
lean_dec(v___x_2563_);
lean_dec_ref(v___f_2556_);
lean_dec(v_i_2550_);
lean_dec_ref(v_b_2549_);
lean_dec(v___x_2547_);
lean_dec(v_iters_2546_);
lean_dec_ref(v_c_2544_);
lean_dec_ref(v_a_2543_);
v_a_2594_ = lean_ctor_get(v___x_2573_, 0);
v_isSharedCheck_2601_ = !lean_is_exclusive(v___x_2573_);
if (v_isSharedCheck_2601_ == 0)
{
v___x_2596_ = v___x_2573_;
v_isShared_2597_ = v_isSharedCheck_2601_;
goto v_resetjp_2595_;
}
else
{
lean_inc(v_a_2594_);
lean_dec(v___x_2573_);
v___x_2596_ = lean_box(0);
v_isShared_2597_ = v_isSharedCheck_2601_;
goto v_resetjp_2595_;
}
v_resetjp_2595_:
{
lean_object* v___x_2599_; 
if (v_isShared_2597_ == 0)
{
v___x_2599_ = v___x_2596_;
goto v_reusejp_2598_;
}
else
{
lean_object* v_reuseFailAlloc_2600_; 
v_reuseFailAlloc_2600_ = lean_alloc_ctor(1, 1, 0);
lean_ctor_set(v_reuseFailAlloc_2600_, 0, v_a_2594_);
v___x_2599_ = v_reuseFailAlloc_2600_;
goto v_reusejp_2598_;
}
v_reusejp_2598_:
{
return v___x_2599_;
}
}
}
}
else
{
lean_object* v_a_2602_; lean_object* v___x_2604_; uint8_t v_isShared_2605_; uint8_t v_isSharedCheck_2609_; 
lean_dec_ref(v___f_2556_);
lean_dec(v_i_2550_);
lean_dec_ref(v_b_2549_);
lean_dec(v___x_2547_);
lean_dec(v_iters_2546_);
lean_dec_ref(v_c_2544_);
lean_dec_ref(v_a_2543_);
v_a_2602_ = lean_ctor_get(v___x_2562_, 0);
v_isSharedCheck_2609_ = !lean_is_exclusive(v___x_2562_);
if (v_isSharedCheck_2609_ == 0)
{
v___x_2604_ = v___x_2562_;
v_isShared_2605_ = v_isSharedCheck_2609_;
goto v_resetjp_2603_;
}
else
{
lean_inc(v_a_2602_);
lean_dec(v___x_2562_);
v___x_2604_ = lean_box(0);
v_isShared_2605_ = v_isSharedCheck_2609_;
goto v_resetjp_2603_;
}
v_resetjp_2603_:
{
lean_object* v___x_2607_; 
if (v_isShared_2605_ == 0)
{
v___x_2607_ = v___x_2604_;
goto v_reusejp_2606_;
}
else
{
lean_object* v_reuseFailAlloc_2608_; 
v_reuseFailAlloc_2608_ = lean_alloc_ctor(1, 1, 0);
lean_ctor_set(v_reuseFailAlloc_2608_, 0, v_a_2602_);
v___x_2607_ = v_reuseFailAlloc_2608_;
goto v_reusejp_2606_;
}
v_reusejp_2606_:
{
return v___x_2607_;
}
}
}
}
}
}
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00__private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchLazyPrepared_spec__0_spec__0___redArg___boxed(lean_object* v_a_2610_, lean_object* v_c_2611_, lean_object* v_expected_2612_, lean_object* v_iters_2613_, lean_object* v___x_2614_, lean_object* v_range_2615_, lean_object* v_b_2616_, lean_object* v_i_2617_, lean_object* v___y_2618_){
_start:
{
uint32_t v_expected_boxed_2619_; lean_object* v_res_2620_; 
v_expected_boxed_2619_ = lean_unbox_uint32(v_expected_2612_);
lean_dec(v_expected_2612_);
v_res_2620_ = lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00__private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchLazyPrepared_spec__0_spec__0___redArg(v_a_2610_, v_c_2611_, v_expected_boxed_2619_, v_iters_2613_, v___x_2614_, v_range_2615_, v_b_2616_, v_i_2617_);
lean_dec_ref(v_range_2615_);
return v_res_2620_;
}
}
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchLazyPrepared_spec__0___redArg(lean_object* v_a_2621_, lean_object* v_c_2622_, uint32_t v_expected_2623_, lean_object* v_iters_2624_, lean_object* v___x_2625_, lean_object* v_range_2626_, lean_object* v_b_2627_, lean_object* v_i_2628_){
_start:
{
lean_object* v_stop_2630_; lean_object* v_step_2631_; uint8_t v___x_2632_; 
v_stop_2630_ = lean_ctor_get(v_range_2626_, 1);
v_step_2631_ = lean_ctor_get(v_range_2626_, 2);
v___x_2632_ = lean_nat_dec_lt(v_i_2628_, v_stop_2630_);
if (v___x_2632_ == 0)
{
lean_object* v___x_2633_; 
lean_dec(v_i_2628_);
lean_dec(v___x_2625_);
lean_dec(v_iters_2624_);
lean_dec_ref(v_c_2622_);
lean_dec_ref(v_a_2621_);
v___x_2633_ = lean_alloc_ctor(0, 1, 0);
lean_ctor_set(v___x_2633_, 0, v_b_2627_);
return v___x_2633_;
}
else
{
lean_object* v___f_2634_; lean_object* v___x_2635_; lean_object* v_a_2636_; lean_object* v_name_2637_; lean_object* v___x_2638_; uint32_t v___x_2639_; lean_object* v___x_2640_; 
lean_inc_ref(v_a_2621_);
v___f_2634_ = lean_alloc_closure((void*)(lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchLazyPrepared_spec__0___redArg___lam__0___boxed), 2, 1);
lean_closure_set(v___f_2634_, 0, v_a_2621_);
lean_inc_ref(v___f_2634_);
v___x_2635_ = l_IO_lazyPure___redArg(v___f_2634_);
v_a_2636_ = lean_ctor_get(v___x_2635_, 0);
lean_inc(v_a_2636_);
lean_dec_ref(v___x_2635_);
v_name_2637_ = lean_ctor_get(v_c_2622_, 0);
v___x_2638_ = ((lean_object*)(lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00__private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchLazyPrepared_spec__0_spec__0___redArg___closed__0));
v___x_2639_ = lean_unbox_uint32(v_a_2636_);
lean_dec(v_a_2636_);
lean_inc_ref(v_name_2637_);
v___x_2640_ = lp_competition_R24DotCostHarness_checkWord(v_name_2637_, v___x_2638_, v___x_2639_, v_expected_2623_);
if (lean_obj_tag(v___x_2640_) == 0)
{
lean_object* v___x_2641_; uint32_t v___x_2642_; lean_object* v___x_2643_; lean_object* v___f_2644_; lean_object* v___x_2645_; lean_object* v_a_2646_; lean_object* v___x_2647_; uint32_t v___x_2648_; lean_object* v___x_2649_; uint32_t v___x_2650_; lean_object* v___x_2651_; 
lean_dec_ref_known(v___x_2640_, 1);
v___x_2641_ = lean_io_mono_nanos_now();
v___x_2642_ = lp_competition_R24DotCostHarness_seed(v_i_2628_);
v___x_2643_ = lean_box_uint32(v___x_2642_);
lean_inc(v_iters_2624_);
lean_inc_ref(v_a_2621_);
v___f_2644_ = lean_alloc_closure((void*)(lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchLazyPrepared_spec__0___redArg___lam__1___boxed), 4, 3);
lean_closure_set(v___f_2644_, 0, v_a_2621_);
lean_closure_set(v___f_2644_, 1, v___x_2643_);
lean_closure_set(v___f_2644_, 2, v_iters_2624_);
v___x_2645_ = l_IO_lazyPure___redArg(v___f_2644_);
v_a_2646_ = lean_ctor_get(v___x_2645_, 0);
lean_inc(v_a_2646_);
lean_dec_ref(v___x_2645_);
v___x_2647_ = lean_io_mono_nanos_now();
v___x_2648_ = lp_competition_R24DotCostHarness_sinkExpected(v___x_2642_, v_expected_2623_, v_iters_2624_);
v___x_2649_ = ((lean_object*)(lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00__private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchLazyPrepared_spec__0_spec__0___redArg___closed__1));
v___x_2650_ = lean_unbox_uint32(v_a_2646_);
lean_inc_ref(v_name_2637_);
v___x_2651_ = lp_competition_R24DotCostHarness_checkWord(v_name_2637_, v___x_2649_, v___x_2650_, v___x_2648_);
if (lean_obj_tag(v___x_2651_) == 0)
{
lean_object* v___x_2652_; lean_object* v_a_2653_; lean_object* v___x_2654_; uint32_t v___x_2655_; lean_object* v___x_2656_; 
lean_dec_ref_known(v___x_2651_, 1);
v___x_2652_ = l_IO_lazyPure___redArg(v___f_2634_);
v_a_2653_ = lean_ctor_get(v___x_2652_, 0);
lean_inc(v_a_2653_);
lean_dec_ref(v___x_2652_);
v___x_2654_ = ((lean_object*)(lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00__private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchLazyPrepared_spec__0_spec__0___redArg___closed__2));
v___x_2655_ = lean_unbox_uint32(v_a_2653_);
lean_inc_ref(v_name_2637_);
v___x_2656_ = lp_competition_R24DotCostHarness_checkWord(v_name_2637_, v___x_2654_, v___x_2655_, v_expected_2623_);
if (lean_obj_tag(v___x_2656_) == 0)
{
lean_object* v___x_2657_; lean_object* v___x_2658_; uint32_t v___x_2659_; uint32_t v___x_2660_; lean_object* v___x_2661_; lean_object* v___x_2662_; lean_object* v___x_2663_; 
lean_dec_ref_known(v___x_2656_, 1);
v___x_2657_ = lean_nat_sub(v___x_2647_, v___x_2641_);
lean_dec(v___x_2641_);
lean_dec(v___x_2647_);
lean_inc(v_iters_2624_);
lean_inc(v___x_2625_);
lean_inc(v_i_2628_);
v___x_2658_ = lean_alloc_ctor(0, 4, 12);
lean_ctor_set(v___x_2658_, 0, v_i_2628_);
lean_ctor_set(v___x_2658_, 1, v___x_2625_);
lean_ctor_set(v___x_2658_, 2, v_iters_2624_);
lean_ctor_set(v___x_2658_, 3, v___x_2657_);
v___x_2659_ = lean_unbox_uint32(v_a_2646_);
lean_dec(v_a_2646_);
lean_ctor_set_uint32(v___x_2658_, sizeof(void*)*4, v___x_2659_);
lean_ctor_set_uint32(v___x_2658_, sizeof(void*)*4 + 4, v___x_2648_);
v___x_2660_ = lean_unbox_uint32(v_a_2653_);
lean_dec(v_a_2653_);
lean_ctor_set_uint32(v___x_2658_, sizeof(void*)*4 + 8, v___x_2660_);
v___x_2661_ = lean_array_push(v_b_2627_, v___x_2658_);
v___x_2662_ = lean_nat_add(v_i_2628_, v_step_2631_);
lean_dec(v_i_2628_);
v___x_2663_ = lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00__private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchLazyPrepared_spec__0_spec__0___redArg(v_a_2621_, v_c_2622_, v_expected_2623_, v_iters_2624_, v___x_2625_, v_range_2626_, v___x_2661_, v___x_2662_);
return v___x_2663_;
}
else
{
lean_object* v_a_2664_; lean_object* v___x_2666_; uint8_t v_isShared_2667_; uint8_t v_isSharedCheck_2671_; 
lean_dec(v_a_2653_);
lean_dec(v___x_2647_);
lean_dec(v_a_2646_);
lean_dec(v___x_2641_);
lean_dec(v_i_2628_);
lean_dec_ref(v_b_2627_);
lean_dec(v___x_2625_);
lean_dec(v_iters_2624_);
lean_dec_ref(v_c_2622_);
lean_dec_ref(v_a_2621_);
v_a_2664_ = lean_ctor_get(v___x_2656_, 0);
v_isSharedCheck_2671_ = !lean_is_exclusive(v___x_2656_);
if (v_isSharedCheck_2671_ == 0)
{
v___x_2666_ = v___x_2656_;
v_isShared_2667_ = v_isSharedCheck_2671_;
goto v_resetjp_2665_;
}
else
{
lean_inc(v_a_2664_);
lean_dec(v___x_2656_);
v___x_2666_ = lean_box(0);
v_isShared_2667_ = v_isSharedCheck_2671_;
goto v_resetjp_2665_;
}
v_resetjp_2665_:
{
lean_object* v___x_2669_; 
if (v_isShared_2667_ == 0)
{
v___x_2669_ = v___x_2666_;
goto v_reusejp_2668_;
}
else
{
lean_object* v_reuseFailAlloc_2670_; 
v_reuseFailAlloc_2670_ = lean_alloc_ctor(1, 1, 0);
lean_ctor_set(v_reuseFailAlloc_2670_, 0, v_a_2664_);
v___x_2669_ = v_reuseFailAlloc_2670_;
goto v_reusejp_2668_;
}
v_reusejp_2668_:
{
return v___x_2669_;
}
}
}
}
else
{
lean_object* v_a_2672_; lean_object* v___x_2674_; uint8_t v_isShared_2675_; uint8_t v_isSharedCheck_2679_; 
lean_dec(v___x_2647_);
lean_dec(v_a_2646_);
lean_dec(v___x_2641_);
lean_dec_ref(v___f_2634_);
lean_dec(v_i_2628_);
lean_dec_ref(v_b_2627_);
lean_dec(v___x_2625_);
lean_dec(v_iters_2624_);
lean_dec_ref(v_c_2622_);
lean_dec_ref(v_a_2621_);
v_a_2672_ = lean_ctor_get(v___x_2651_, 0);
v_isSharedCheck_2679_ = !lean_is_exclusive(v___x_2651_);
if (v_isSharedCheck_2679_ == 0)
{
v___x_2674_ = v___x_2651_;
v_isShared_2675_ = v_isSharedCheck_2679_;
goto v_resetjp_2673_;
}
else
{
lean_inc(v_a_2672_);
lean_dec(v___x_2651_);
v___x_2674_ = lean_box(0);
v_isShared_2675_ = v_isSharedCheck_2679_;
goto v_resetjp_2673_;
}
v_resetjp_2673_:
{
lean_object* v___x_2677_; 
if (v_isShared_2675_ == 0)
{
v___x_2677_ = v___x_2674_;
goto v_reusejp_2676_;
}
else
{
lean_object* v_reuseFailAlloc_2678_; 
v_reuseFailAlloc_2678_ = lean_alloc_ctor(1, 1, 0);
lean_ctor_set(v_reuseFailAlloc_2678_, 0, v_a_2672_);
v___x_2677_ = v_reuseFailAlloc_2678_;
goto v_reusejp_2676_;
}
v_reusejp_2676_:
{
return v___x_2677_;
}
}
}
}
else
{
lean_object* v_a_2680_; lean_object* v___x_2682_; uint8_t v_isShared_2683_; uint8_t v_isSharedCheck_2687_; 
lean_dec_ref(v___f_2634_);
lean_dec(v_i_2628_);
lean_dec_ref(v_b_2627_);
lean_dec(v___x_2625_);
lean_dec(v_iters_2624_);
lean_dec_ref(v_c_2622_);
lean_dec_ref(v_a_2621_);
v_a_2680_ = lean_ctor_get(v___x_2640_, 0);
v_isSharedCheck_2687_ = !lean_is_exclusive(v___x_2640_);
if (v_isSharedCheck_2687_ == 0)
{
v___x_2682_ = v___x_2640_;
v_isShared_2683_ = v_isSharedCheck_2687_;
goto v_resetjp_2681_;
}
else
{
lean_inc(v_a_2680_);
lean_dec(v___x_2640_);
v___x_2682_ = lean_box(0);
v_isShared_2683_ = v_isSharedCheck_2687_;
goto v_resetjp_2681_;
}
v_resetjp_2681_:
{
lean_object* v___x_2685_; 
if (v_isShared_2683_ == 0)
{
v___x_2685_ = v___x_2682_;
goto v_reusejp_2684_;
}
else
{
lean_object* v_reuseFailAlloc_2686_; 
v_reuseFailAlloc_2686_ = lean_alloc_ctor(1, 1, 0);
lean_ctor_set(v_reuseFailAlloc_2686_, 0, v_a_2680_);
v___x_2685_ = v_reuseFailAlloc_2686_;
goto v_reusejp_2684_;
}
v_reusejp_2684_:
{
return v___x_2685_;
}
}
}
}
}
}
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchLazyPrepared_spec__0___redArg___boxed(lean_object* v_a_2688_, lean_object* v_c_2689_, lean_object* v_expected_2690_, lean_object* v_iters_2691_, lean_object* v___x_2692_, lean_object* v_range_2693_, lean_object* v_b_2694_, lean_object* v_i_2695_, lean_object* v___y_2696_){
_start:
{
uint32_t v_expected_boxed_2697_; lean_object* v_res_2698_; 
v_expected_boxed_2697_ = lean_unbox_uint32(v_expected_2690_);
lean_dec(v_expected_2690_);
v_res_2698_ = lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchLazyPrepared_spec__0___redArg(v_a_2688_, v_c_2689_, v_expected_boxed_2697_, v_iters_2691_, v___x_2692_, v_range_2693_, v_b_2694_, v_i_2695_);
lean_dec_ref(v_range_2693_);
return v_res_2698_;
}
}
LEAN_EXPORT lean_object* lp_competition_R24DotCostHarness_benchLazyPrepared(lean_object* v_c_2699_, lean_object* v_a_2700_, lean_object* v_b_2701_, lean_object* v_macs_2702_){
_start:
{
lean_object* v___x_2704_; lean_object* v_a_2705_; lean_object* v___x_2706_; lean_object* v_a_2707_; lean_object* v___f_2708_; lean_object* v___x_2709_; lean_object* v_a_2710_; lean_object* v___x_2711_; lean_object* v_a_2712_; lean_object* v_expected_2713_; uint32_t v_expected_2714_; lean_object* v___x_2715_; lean_object* v_iters_2716_; lean_object* v___x_2717_; lean_object* v___x_2718_; lean_object* v___x_2719_; lean_object* v___x_2720_; 
v___x_2704_ = lp_competition_R24DotCostHarness_benchExactFull___lam__0();
v_a_2705_ = lean_ctor_get(v___x_2704_, 0);
lean_inc(v_a_2705_);
lean_dec_ref(v___x_2704_);
v___x_2706_ = lp_competition_R24DotCostHarness_benchExactFull___lam__0();
v_a_2707_ = lean_ctor_get(v___x_2706_, 0);
lean_inc(v_a_2707_);
lean_dec_ref(v___x_2706_);
lean_inc_ref(v_a_2700_);
v___f_2708_ = lean_alloc_closure((void*)(lp_competition_R24DotCostHarness_benchLazyPrepared___lam__1), 3, 2);
lean_closure_set(v___f_2708_, 0, v_a_2700_);
lean_closure_set(v___f_2708_, 1, v_b_2701_);
v___x_2709_ = l_IO_lazyPure___redArg(v___f_2708_);
v_a_2710_ = lean_ctor_get(v___x_2709_, 0);
lean_inc(v_a_2710_);
lean_dec_ref(v___x_2709_);
v___x_2711_ = lp_competition_R24DotCostHarness_benchExactFull___lam__0();
v_a_2712_ = lean_ctor_get(v___x_2711_, 0);
lean_inc(v_a_2712_);
lean_dec_ref(v___x_2711_);
v_expected_2713_ = lean_ctor_get(v_c_2699_, 5);
v_expected_2714_ = lean_uint32_of_nat(v_expected_2713_);
v___x_2715_ = lean_array_get_size(v_a_2700_);
lean_dec_ref(v_a_2700_);
v_iters_2716_ = lp_competition_R24DotCostHarness_repeats(v_macs_2702_, v___x_2715_);
v___x_2717_ = lean_unsigned_to_nat(0u);
v___x_2718_ = ((lean_object*)(lp_competition_R24DotCostHarness_benchExactFull___closed__0));
v___x_2719_ = ((lean_object*)(lp_competition_R24DotCostHarness_benchExactFull___closed__1));
lean_inc_ref(v_c_2699_);
v___x_2720_ = lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchLazyPrepared_spec__0___redArg(v_a_2710_, v_c_2699_, v_expected_2714_, v_iters_2716_, v___x_2715_, v___x_2719_, v___x_2718_, v___x_2717_);
if (lean_obj_tag(v___x_2720_) == 0)
{
lean_object* v_a_2721_; lean_object* v___x_2722_; lean_object* v_a_2723_; lean_object* v___x_2724_; lean_object* v___x_2725_; lean_object* v___x_2726_; lean_object* v___x_2727_; lean_object* v___x_2728_; 
v_a_2721_ = lean_ctor_get(v___x_2720_, 0);
lean_inc(v_a_2721_);
lean_dec_ref_known(v___x_2720_, 1);
v___x_2722_ = lp_competition_R24DotCostHarness_benchExactFull___lam__0();
v_a_2723_ = lean_ctor_get(v___x_2722_, 0);
lean_inc(v_a_2723_);
lean_dec_ref(v___x_2722_);
v___x_2724_ = lean_nat_sub(v_a_2712_, v_a_2707_);
lean_dec(v_a_2707_);
lean_dec(v_a_2712_);
v___x_2725_ = ((lean_object*)(lp_competition_R24DotCostHarness_benchLazyFull___closed__0));
v___x_2726_ = ((lean_object*)(lp_competition_R24DotCostHarness_benchExactPrepared___closed__0));
v___x_2727_ = lean_nat_sub(v_a_2723_, v_a_2705_);
lean_dec(v_a_2705_);
lean_dec(v_a_2723_);
v___x_2728_ = lp_competition_R24DotCostHarness_emit(v_c_2699_, v___x_2725_, v___x_2726_, v___x_2724_, v___x_2727_, v_a_2721_);
lean_dec(v_a_2721_);
lean_dec_ref(v_c_2699_);
return v___x_2728_;
}
else
{
lean_object* v_a_2729_; lean_object* v___x_2731_; uint8_t v_isShared_2732_; uint8_t v_isSharedCheck_2736_; 
lean_dec(v_a_2712_);
lean_dec(v_a_2707_);
lean_dec(v_a_2705_);
lean_dec_ref(v_c_2699_);
v_a_2729_ = lean_ctor_get(v___x_2720_, 0);
v_isSharedCheck_2736_ = !lean_is_exclusive(v___x_2720_);
if (v_isSharedCheck_2736_ == 0)
{
v___x_2731_ = v___x_2720_;
v_isShared_2732_ = v_isSharedCheck_2736_;
goto v_resetjp_2730_;
}
else
{
lean_inc(v_a_2729_);
lean_dec(v___x_2720_);
v___x_2731_ = lean_box(0);
v_isShared_2732_ = v_isSharedCheck_2736_;
goto v_resetjp_2730_;
}
v_resetjp_2730_:
{
lean_object* v___x_2734_; 
if (v_isShared_2732_ == 0)
{
v___x_2734_ = v___x_2731_;
goto v_reusejp_2733_;
}
else
{
lean_object* v_reuseFailAlloc_2735_; 
v_reuseFailAlloc_2735_ = lean_alloc_ctor(1, 1, 0);
lean_ctor_set(v_reuseFailAlloc_2735_, 0, v_a_2729_);
v___x_2734_ = v_reuseFailAlloc_2735_;
goto v_reusejp_2733_;
}
v_reusejp_2733_:
{
return v___x_2734_;
}
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_R24DotCostHarness_benchLazyPrepared___boxed(lean_object* v_c_2737_, lean_object* v_a_2738_, lean_object* v_b_2739_, lean_object* v_macs_2740_, lean_object* v_a_2741_){
_start:
{
lean_object* v_res_2742_; 
v_res_2742_ = lp_competition_R24DotCostHarness_benchLazyPrepared(v_c_2737_, v_a_2738_, v_b_2739_, v_macs_2740_);
lean_dec(v_macs_2740_);
return v_res_2742_;
}
}
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchLazyPrepared_spec__0(lean_object* v_a_2743_, lean_object* v_c_2744_, uint32_t v_expected_2745_, lean_object* v_iters_2746_, lean_object* v___x_2747_, lean_object* v_range_2748_, lean_object* v_b_2749_, lean_object* v_i_2750_, lean_object* v_hs_2751_, lean_object* v_hl_2752_){
_start:
{
lean_object* v___x_2754_; 
v___x_2754_ = lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchLazyPrepared_spec__0___redArg(v_a_2743_, v_c_2744_, v_expected_2745_, v_iters_2746_, v___x_2747_, v_range_2748_, v_b_2749_, v_i_2750_);
return v___x_2754_;
}
}
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchLazyPrepared_spec__0___boxed(lean_object* v_a_2755_, lean_object* v_c_2756_, lean_object* v_expected_2757_, lean_object* v_iters_2758_, lean_object* v___x_2759_, lean_object* v_range_2760_, lean_object* v_b_2761_, lean_object* v_i_2762_, lean_object* v_hs_2763_, lean_object* v_hl_2764_, lean_object* v___y_2765_){
_start:
{
uint32_t v_expected_boxed_2766_; lean_object* v_res_2767_; 
v_expected_boxed_2766_ = lean_unbox_uint32(v_expected_2757_);
lean_dec(v_expected_2757_);
v_res_2767_ = lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchLazyPrepared_spec__0(v_a_2755_, v_c_2756_, v_expected_boxed_2766_, v_iters_2758_, v___x_2759_, v_range_2760_, v_b_2761_, v_i_2762_, v_hs_2763_, v_hl_2764_);
lean_dec_ref(v_range_2760_);
return v_res_2767_;
}
}
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00__private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchLazyPrepared_spec__0_spec__0(lean_object* v_a_2768_, lean_object* v_c_2769_, uint32_t v_expected_2770_, lean_object* v_iters_2771_, lean_object* v___x_2772_, lean_object* v_range_2773_, lean_object* v_b_2774_, lean_object* v_i_2775_, lean_object* v_hs_2776_, lean_object* v_hl_2777_){
_start:
{
lean_object* v___x_2779_; 
v___x_2779_ = lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00__private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchLazyPrepared_spec__0_spec__0___redArg(v_a_2768_, v_c_2769_, v_expected_2770_, v_iters_2771_, v___x_2772_, v_range_2773_, v_b_2774_, v_i_2775_);
return v___x_2779_;
}
}
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00__private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchLazyPrepared_spec__0_spec__0___boxed(lean_object* v_a_2780_, lean_object* v_c_2781_, lean_object* v_expected_2782_, lean_object* v_iters_2783_, lean_object* v___x_2784_, lean_object* v_range_2785_, lean_object* v_b_2786_, lean_object* v_i_2787_, lean_object* v_hs_2788_, lean_object* v_hl_2789_, lean_object* v___y_2790_){
_start:
{
uint32_t v_expected_boxed_2791_; lean_object* v_res_2792_; 
v_expected_boxed_2791_ = lean_unbox_uint32(v_expected_2782_);
lean_dec(v_expected_2782_);
v_res_2792_ = lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00__private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotCostHarness_benchLazyPrepared_spec__0_spec__0(v_a_2780_, v_c_2781_, v_expected_boxed_2791_, v_iters_2783_, v___x_2784_, v_range_2785_, v_b_2786_, v_i_2787_, v_hs_2788_, v_hl_2789_);
lean_dec_ref(v_range_2785_);
return v_res_2792_;
}
}
LEAN_EXPORT uint8_t lp_competition___private_Init_Data_Array_Basic_0__Array_anyMUnsafe_any___at___00R24DotCostHarness_verify_spec__0(lean_object* v_as_2793_, size_t v_i_2794_, size_t v_stop_2795_){
_start:
{
uint8_t v___x_2796_; 
v___x_2796_ = lean_usize_dec_eq(v_i_2794_, v_stop_2795_);
if (v___x_2796_ == 0)
{
lean_object* v___x_2797_; lean_object* v___x_2798_; uint8_t v___x_2799_; 
v___x_2797_ = lean_array_uget_borrowed(v_as_2793_, v_i_2794_);
v___x_2798_ = lean_unsigned_to_nat(4294967295u);
v___x_2799_ = lean_nat_dec_lt(v___x_2798_, v___x_2797_);
if (v___x_2799_ == 0)
{
size_t v___x_2800_; size_t v___x_2801_; 
v___x_2800_ = ((size_t)1ULL);
v___x_2801_ = lean_usize_add(v_i_2794_, v___x_2800_);
v_i_2794_ = v___x_2801_;
goto _start;
}
else
{
return v___x_2799_;
}
}
else
{
uint8_t v___x_2803_; 
v___x_2803_ = 0;
return v___x_2803_;
}
}
}
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_anyMUnsafe_any___at___00R24DotCostHarness_verify_spec__0___boxed(lean_object* v_as_2804_, lean_object* v_i_2805_, lean_object* v_stop_2806_){
_start:
{
size_t v_i_boxed_2807_; size_t v_stop_boxed_2808_; uint8_t v_res_2809_; lean_object* v_r_2810_; 
v_i_boxed_2807_ = lean_unbox_usize(v_i_2805_);
lean_dec(v_i_2805_);
v_stop_boxed_2808_ = lean_unbox_usize(v_stop_2806_);
lean_dec(v_stop_2806_);
v_res_2809_ = lp_competition___private_Init_Data_Array_Basic_0__Array_anyMUnsafe_any___at___00R24DotCostHarness_verify_spec__0(v_as_2804_, v_i_boxed_2807_, v_stop_boxed_2808_);
lean_dec_ref(v_as_2804_);
v_r_2810_ = lean_box(v_res_2809_);
return v_r_2810_;
}
}
LEAN_EXPORT uint32_t lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotCostHarness_verify_spec__1___lam__5(lean_object* v___x_2811_, lean_object* v___x_2812_, lean_object* v_x_2813_){
_start:
{
uint32_t v___x_2814_; 
v___x_2814_ = lp_competition_Submission_R24DotProbe_exactFull(v___x_2811_, v___x_2812_);
return v___x_2814_;
}
}
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotCostHarness_verify_spec__1___lam__5___boxed(lean_object* v___x_2815_, lean_object* v___x_2816_, lean_object* v_x_2817_){
_start:
{
uint32_t v_res_2818_; lean_object* v_r_2819_; 
v_res_2818_ = lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotCostHarness_verify_spec__1___lam__5(v___x_2815_, v___x_2816_, v_x_2817_);
v_r_2819_ = lean_box_uint32(v_res_2818_);
return v_r_2819_;
}
}
LEAN_EXPORT uint32_t lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotCostHarness_verify_spec__1___lam__9(lean_object* v___x_2820_, lean_object* v___x_2821_, lean_object* v_x_2822_){
_start:
{
uint32_t v___x_2823_; 
v___x_2823_ = lp_competition_Submission_R24DotProbe_eagerPrepared(v___x_2820_, v___x_2821_);
return v___x_2823_;
}
}
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotCostHarness_verify_spec__1___lam__9___boxed(lean_object* v___x_2824_, lean_object* v___x_2825_, lean_object* v_x_2826_){
_start:
{
uint32_t v_res_2827_; lean_object* v_r_2828_; 
v_res_2827_ = lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotCostHarness_verify_spec__1___lam__9(v___x_2824_, v___x_2825_, v_x_2826_);
v_r_2828_ = lean_box_uint32(v_res_2827_);
return v_r_2828_;
}
}
LEAN_EXPORT uint32_t lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotCostHarness_verify_spec__1___lam__6(lean_object* v___x_2829_, lean_object* v___x_2830_, lean_object* v_x_2831_){
_start:
{
uint32_t v___x_2832_; 
v___x_2832_ = lp_competition_Submission_R24DotProbe_exactPrepared(v___x_2829_, v___x_2830_);
return v___x_2832_;
}
}
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotCostHarness_verify_spec__1___lam__6___boxed(lean_object* v___x_2833_, lean_object* v___x_2834_, lean_object* v_x_2835_){
_start:
{
uint32_t v_res_2836_; lean_object* v_r_2837_; 
v_res_2836_ = lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotCostHarness_verify_spec__1___lam__6(v___x_2833_, v___x_2834_, v_x_2835_);
v_r_2837_ = lean_box_uint32(v_res_2836_);
return v_r_2837_;
}
}
LEAN_EXPORT uint32_t lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotCostHarness_verify_spec__1___lam__8(lean_object* v___x_2838_, lean_object* v___x_2839_, lean_object* v_x_2840_){
_start:
{
uint32_t v___x_2841_; 
v___x_2841_ = lp_competition_Submission_R24DotProbe_lazyPrepared(v___x_2838_, v___x_2839_);
return v___x_2841_;
}
}
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotCostHarness_verify_spec__1___lam__8___boxed(lean_object* v___x_2842_, lean_object* v___x_2843_, lean_object* v_x_2844_){
_start:
{
uint32_t v_res_2845_; lean_object* v_r_2846_; 
v_res_2845_ = lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotCostHarness_verify_spec__1___lam__8(v___x_2842_, v___x_2843_, v_x_2844_);
v_r_2846_ = lean_box_uint32(v_res_2845_);
return v_r_2846_;
}
}
LEAN_EXPORT uint32_t lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotCostHarness_verify_spec__1___lam__3(lean_object* v___x_2847_, lean_object* v___x_2848_, lean_object* v_x_2849_){
_start:
{
uint32_t v___x_2850_; 
v___x_2850_ = lp_competition_Submission_R24DotProbe_lazyFull(v___x_2847_, v___x_2848_);
return v___x_2850_;
}
}
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotCostHarness_verify_spec__1___lam__3___boxed(lean_object* v___x_2851_, lean_object* v___x_2852_, lean_object* v_x_2853_){
_start:
{
uint32_t v_res_2854_; lean_object* v_r_2855_; 
v_res_2854_ = lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotCostHarness_verify_spec__1___lam__3(v___x_2851_, v___x_2852_, v_x_2853_);
v_r_2855_ = lean_box_uint32(v_res_2854_);
return v_r_2855_;
}
}
LEAN_EXPORT uint32_t lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotCostHarness_verify_spec__1___lam__7(lean_object* v___x_2856_, lean_object* v___x_2857_, lean_object* v_x_2858_){
_start:
{
uint32_t v___x_2859_; 
v___x_2859_ = lp_competition_Submission_R24PortableF64_attemptPrepared(v___x_2856_, v___x_2857_);
return v___x_2859_;
}
}
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotCostHarness_verify_spec__1___lam__7___boxed(lean_object* v___x_2860_, lean_object* v___x_2861_, lean_object* v_x_2862_){
_start:
{
uint32_t v_res_2863_; lean_object* v_r_2864_; 
v_res_2863_ = lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotCostHarness_verify_spec__1___lam__7(v___x_2860_, v___x_2861_, v_x_2862_);
lean_dec_ref(v___x_2861_);
lean_dec_ref(v___x_2860_);
v_r_2864_ = lean_box_uint32(v_res_2863_);
return v_r_2864_;
}
}
LEAN_EXPORT uint32_t lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotCostHarness_verify_spec__1___lam__0(uint8_t v___x_2865_, lean_object* v___x_2866_, uint8_t v_normal_2867_, uint8_t v_normal_2868_, lean_object* v_data_2869_, lean_object* v_data_2870_, uint32_t v___y_2871_, lean_object* v_accepts_2872_, uint32_t v___y_2873_, uint8_t v___y_2874_, lean_object* v_x_2875_){
_start:
{
if (v___x_2865_ == 0)
{
uint32_t v___x_2876_; 
lean_dec(v_accepts_2872_);
v___x_2876_ = lp_competition_Submission_R24ExactDotCost_referencePrepared(v___x_2866_);
return v___x_2876_;
}
else
{
if (v_normal_2867_ == 0)
{
uint32_t v___x_2877_; 
lean_dec(v_accepts_2872_);
v___x_2877_ = lp_competition_Submission_R24ExactDotCost_referencePrepared(v___x_2866_);
return v___x_2877_;
}
else
{
if (v_normal_2868_ == 0)
{
uint32_t v___x_2878_; 
lean_dec(v_accepts_2872_);
v___x_2878_ = lp_competition_Submission_R24ExactDotCost_referencePrepared(v___x_2866_);
return v___x_2878_;
}
else
{
lean_object* v___x_2879_; uint8_t v___y_2881_; lean_object* v___x_2884_; uint8_t v___x_2885_; 
v___x_2879_ = lean_array_get_size(v_data_2869_);
v___x_2884_ = lean_unsigned_to_nat(1048576u);
v___x_2885_ = lean_nat_dec_le(v___x_2879_, v___x_2884_);
if (v___x_2885_ == 0)
{
uint32_t v___x_2886_; 
lean_dec(v_accepts_2872_);
v___x_2886_ = lp_competition_Submission_R24ExactDotCost_referencePrepared(v___x_2866_);
return v___x_2886_;
}
else
{
lean_object* v___x_2887_; lean_object* v___x_2888_; lean_object* v___x_2889_; lean_object* v___x_2890_; lean_object* v___x_2891_; lean_object* v___y_2893_; lean_object* v___x_2899_; uint64_t v___y_2901_; uint64_t v___y_2905_; uint64_t v___y_2906_; uint64_t v___y_2913_; uint64_t v___y_2914_; uint64_t v___y_2915_; uint64_t v___y_2916_; uint64_t v___y_2922_; uint64_t v___y_2923_; uint64_t v___y_2929_; uint64_t v___y_2930_; uint64_t v___y_2931_; uint64_t v___y_2932_; uint64_t v___y_2938_; uint64_t v___y_2939_; uint64_t v___y_2945_; uint64_t v___y_2946_; uint64_t v___y_2947_; uint64_t v___y_2948_; uint64_t v___y_2954_; uint64_t v___y_2955_; uint64_t v___y_2961_; uint64_t v___y_2962_; uint64_t v___y_2963_; uint64_t v___y_2964_; uint64_t v___y_2970_; uint64_t v___y_2971_; uint8_t v___x_2976_; 
v___x_2887_ = lean_unsigned_to_nat(48u);
v___x_2888_ = lean_uint32_to_nat(v___y_2873_);
v___x_2889_ = lean_uint32_to_nat(v___y_2871_);
v___x_2890_ = lean_nat_sub(v___x_2888_, v___x_2889_);
lean_dec(v___x_2889_);
lean_dec(v___x_2888_);
v___x_2891_ = lean_nat_add(v___x_2887_, v___x_2890_);
lean_dec(v___x_2890_);
v___x_2899_ = lean_unsigned_to_nat(1u);
v___x_2976_ = lean_nat_dec_le(v___x_2879_, v___x_2899_);
if (v___x_2976_ == 0)
{
lean_object* v___x_2977_; uint64_t v___x_2978_; uint64_t v___x_2979_; uint64_t v___y_2981_; uint64_t v___x_2985_; uint64_t v___x_2986_; uint8_t v___x_2987_; 
v___x_2977_ = lean_nat_sub(v___x_2879_, v___x_2899_);
v___x_2978_ = lean_uint64_of_nat(v___x_2977_);
lean_dec(v___x_2977_);
v___x_2979_ = 32ULL;
v___x_2985_ = lean_uint64_shift_right(v___x_2978_, v___x_2979_);
v___x_2986_ = 0ULL;
v___x_2987_ = lean_uint64_dec_eq(v___x_2985_, v___x_2986_);
if (v___x_2987_ == 0)
{
v___y_2981_ = v___x_2985_;
goto v___jp_2980_;
}
else
{
v___y_2981_ = v___x_2978_;
goto v___jp_2980_;
}
v___jp_2980_:
{
uint64_t v___x_2982_; uint64_t v___x_2983_; uint8_t v___x_2984_; 
v___x_2982_ = lean_uint64_shift_right(v___x_2978_, v___x_2979_);
v___x_2983_ = 0ULL;
v___x_2984_ = lean_uint64_dec_eq(v___x_2982_, v___x_2983_);
if (v___x_2984_ == 0)
{
v___y_2970_ = v___y_2981_;
v___y_2971_ = v___x_2979_;
goto v___jp_2969_;
}
else
{
v___y_2970_ = v___y_2981_;
v___y_2971_ = v___x_2983_;
goto v___jp_2969_;
}
}
}
else
{
lean_inc(v_accepts_2872_);
v___y_2893_ = v_accepts_2872_;
goto v___jp_2892_;
}
v___jp_2892_:
{
lean_object* v___x_2894_; lean_object* v___x_2895_; uint8_t v___x_2896_; 
v___x_2894_ = lean_nat_add(v___x_2891_, v___y_2893_);
lean_dec(v___y_2893_);
lean_dec(v___x_2891_);
v___x_2895_ = lean_unsigned_to_nat(128u);
v___x_2896_ = lean_nat_dec_le(v___x_2894_, v___x_2895_);
lean_dec(v___x_2894_);
if (v___x_2896_ == 0)
{
uint32_t v___x_2897_; 
lean_dec(v_accepts_2872_);
v___x_2897_ = lp_competition_Submission_R24ExactDotCost_referencePrepared(v___x_2866_);
return v___x_2897_;
}
else
{
uint8_t v___x_2898_; 
v___x_2898_ = lean_nat_dec_eq(v___x_2879_, v_accepts_2872_);
if (v___x_2898_ == 0)
{
v___y_2881_ = v___x_2896_;
goto v___jp_2880_;
}
else
{
v___y_2881_ = v___y_2874_;
goto v___jp_2880_;
}
}
}
v___jp_2900_:
{
lean_object* v___x_2902_; lean_object* v___x_2903_; 
v___x_2902_ = lean_uint64_to_nat(v___y_2901_);
v___x_2903_ = lean_nat_add(v___x_2902_, v___x_2899_);
lean_dec(v___x_2902_);
v___y_2893_ = v___x_2903_;
goto v___jp_2892_;
}
v___jp_2904_:
{
uint64_t v___x_2907_; uint64_t v___x_2908_; uint64_t v___x_2909_; uint8_t v___x_2910_; 
v___x_2907_ = 1ULL;
v___x_2908_ = lean_uint64_shift_right(v___y_2905_, v___x_2907_);
v___x_2909_ = 0ULL;
v___x_2910_ = lean_uint64_dec_eq(v___x_2908_, v___x_2909_);
if (v___x_2910_ == 0)
{
uint64_t v___x_2911_; 
v___x_2911_ = lean_uint64_add(v___y_2906_, v___x_2907_);
v___y_2901_ = v___x_2911_;
goto v___jp_2900_;
}
else
{
v___y_2901_ = v___y_2906_;
goto v___jp_2900_;
}
}
v___jp_2912_:
{
uint64_t v___x_2917_; uint64_t v___x_2918_; uint8_t v___x_2919_; 
v___x_2917_ = lean_uint64_shift_right(v___y_2915_, v___y_2913_);
v___x_2918_ = 0ULL;
v___x_2919_ = lean_uint64_dec_eq(v___x_2917_, v___x_2918_);
if (v___x_2919_ == 0)
{
uint64_t v___x_2920_; 
v___x_2920_ = lean_uint64_add(v___y_2914_, v___y_2913_);
v___y_2905_ = v___y_2916_;
v___y_2906_ = v___x_2920_;
goto v___jp_2904_;
}
else
{
v___y_2905_ = v___y_2916_;
v___y_2906_ = v___y_2914_;
goto v___jp_2904_;
}
}
v___jp_2921_:
{
uint64_t v___x_2924_; uint64_t v___x_2925_; uint64_t v___x_2926_; uint8_t v___x_2927_; 
v___x_2924_ = 2ULL;
v___x_2925_ = lean_uint64_shift_right(v___y_2922_, v___x_2924_);
v___x_2926_ = 0ULL;
v___x_2927_ = lean_uint64_dec_eq(v___x_2925_, v___x_2926_);
if (v___x_2927_ == 0)
{
v___y_2913_ = v___x_2924_;
v___y_2914_ = v___y_2923_;
v___y_2915_ = v___y_2922_;
v___y_2916_ = v___x_2925_;
goto v___jp_2912_;
}
else
{
v___y_2913_ = v___x_2924_;
v___y_2914_ = v___y_2923_;
v___y_2915_ = v___y_2922_;
v___y_2916_ = v___y_2922_;
goto v___jp_2912_;
}
}
v___jp_2928_:
{
uint64_t v___x_2933_; uint64_t v___x_2934_; uint8_t v___x_2935_; 
v___x_2933_ = lean_uint64_shift_right(v___y_2929_, v___y_2931_);
v___x_2934_ = 0ULL;
v___x_2935_ = lean_uint64_dec_eq(v___x_2933_, v___x_2934_);
if (v___x_2935_ == 0)
{
uint64_t v___x_2936_; 
v___x_2936_ = lean_uint64_add(v___y_2930_, v___y_2931_);
v___y_2922_ = v___y_2932_;
v___y_2923_ = v___x_2936_;
goto v___jp_2921_;
}
else
{
v___y_2922_ = v___y_2932_;
v___y_2923_ = v___y_2930_;
goto v___jp_2921_;
}
}
v___jp_2937_:
{
uint64_t v___x_2940_; uint64_t v___x_2941_; uint64_t v___x_2942_; uint8_t v___x_2943_; 
v___x_2940_ = 4ULL;
v___x_2941_ = lean_uint64_shift_right(v___y_2938_, v___x_2940_);
v___x_2942_ = 0ULL;
v___x_2943_ = lean_uint64_dec_eq(v___x_2941_, v___x_2942_);
if (v___x_2943_ == 0)
{
v___y_2929_ = v___y_2938_;
v___y_2930_ = v___y_2939_;
v___y_2931_ = v___x_2940_;
v___y_2932_ = v___x_2941_;
goto v___jp_2928_;
}
else
{
v___y_2929_ = v___y_2938_;
v___y_2930_ = v___y_2939_;
v___y_2931_ = v___x_2940_;
v___y_2932_ = v___y_2938_;
goto v___jp_2928_;
}
}
v___jp_2944_:
{
uint64_t v___x_2949_; uint64_t v___x_2950_; uint8_t v___x_2951_; 
v___x_2949_ = lean_uint64_shift_right(v___y_2946_, v___y_2945_);
v___x_2950_ = 0ULL;
v___x_2951_ = lean_uint64_dec_eq(v___x_2949_, v___x_2950_);
if (v___x_2951_ == 0)
{
uint64_t v___x_2952_; 
v___x_2952_ = lean_uint64_add(v___y_2947_, v___y_2945_);
v___y_2938_ = v___y_2948_;
v___y_2939_ = v___x_2952_;
goto v___jp_2937_;
}
else
{
v___y_2938_ = v___y_2948_;
v___y_2939_ = v___y_2947_;
goto v___jp_2937_;
}
}
v___jp_2953_:
{
uint64_t v___x_2956_; uint64_t v___x_2957_; uint64_t v___x_2958_; uint8_t v___x_2959_; 
v___x_2956_ = 8ULL;
v___x_2957_ = lean_uint64_shift_right(v___y_2954_, v___x_2956_);
v___x_2958_ = 0ULL;
v___x_2959_ = lean_uint64_dec_eq(v___x_2957_, v___x_2958_);
if (v___x_2959_ == 0)
{
v___y_2945_ = v___x_2956_;
v___y_2946_ = v___y_2954_;
v___y_2947_ = v___y_2955_;
v___y_2948_ = v___x_2957_;
goto v___jp_2944_;
}
else
{
v___y_2945_ = v___x_2956_;
v___y_2946_ = v___y_2954_;
v___y_2947_ = v___y_2955_;
v___y_2948_ = v___y_2954_;
goto v___jp_2944_;
}
}
v___jp_2960_:
{
uint64_t v___x_2965_; uint64_t v___x_2966_; uint8_t v___x_2967_; 
v___x_2965_ = lean_uint64_shift_right(v___y_2962_, v___y_2963_);
v___x_2966_ = 0ULL;
v___x_2967_ = lean_uint64_dec_eq(v___x_2965_, v___x_2966_);
if (v___x_2967_ == 0)
{
uint64_t v___x_2968_; 
v___x_2968_ = lean_uint64_add(v___y_2961_, v___y_2963_);
v___y_2954_ = v___y_2964_;
v___y_2955_ = v___x_2968_;
goto v___jp_2953_;
}
else
{
v___y_2954_ = v___y_2964_;
v___y_2955_ = v___y_2961_;
goto v___jp_2953_;
}
}
v___jp_2969_:
{
uint64_t v___x_2972_; uint64_t v___x_2973_; uint64_t v___x_2974_; uint8_t v___x_2975_; 
v___x_2972_ = 16ULL;
v___x_2973_ = lean_uint64_shift_right(v___y_2970_, v___x_2972_);
v___x_2974_ = 0ULL;
v___x_2975_ = lean_uint64_dec_eq(v___x_2973_, v___x_2974_);
if (v___x_2975_ == 0)
{
v___y_2961_ = v___y_2971_;
v___y_2962_ = v___y_2970_;
v___y_2963_ = v___x_2972_;
v___y_2964_ = v___x_2973_;
goto v___jp_2960_;
}
else
{
v___y_2961_ = v___y_2971_;
v___y_2962_ = v___y_2970_;
v___y_2963_ = v___x_2972_;
v___y_2964_ = v___y_2970_;
goto v___jp_2960_;
}
}
}
v___jp_2880_:
{
uint64_t v___x_2882_; uint32_t v___x_2883_; 
v___x_2882_ = 0ULL;
v___x_2883_ = lp_competition_Submission_R24ExactDotCost_nativeLoop(v_data_2869_, v_data_2870_, v___y_2871_, v_accepts_2872_, v___y_2881_, v___x_2882_, v___x_2882_, v___x_2882_, v___x_2882_, v___x_2879_);
return v___x_2883_;
}
}
}
}
}
}
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotCostHarness_verify_spec__1___lam__0___boxed(lean_object* v___x_2988_, lean_object* v___x_2989_, lean_object* v_normal_2990_, lean_object* v_normal_2991_, lean_object* v_data_2992_, lean_object* v_data_2993_, lean_object* v___y_2994_, lean_object* v_accepts_2995_, lean_object* v___y_2996_, lean_object* v___y_2997_, lean_object* v_x_2998_){
_start:
{
uint8_t v___x_11669__boxed_2999_; uint8_t v_normal_boxed_3000_; uint8_t v_normal_boxed_3001_; uint32_t v___y_11671__boxed_3002_; uint32_t v___y_11672__boxed_3003_; uint8_t v___y_11673__boxed_3004_; uint32_t v_res_3005_; lean_object* v_r_3006_; 
v___x_11669__boxed_2999_ = lean_unbox(v___x_2988_);
v_normal_boxed_3000_ = lean_unbox(v_normal_2990_);
v_normal_boxed_3001_ = lean_unbox(v_normal_2991_);
v___y_11671__boxed_3002_ = lean_unbox_uint32(v___y_2994_);
lean_dec(v___y_2994_);
v___y_11672__boxed_3003_ = lean_unbox_uint32(v___y_2996_);
lean_dec(v___y_2996_);
v___y_11673__boxed_3004_ = lean_unbox(v___y_2997_);
v_res_3005_ = lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotCostHarness_verify_spec__1___lam__0(v___x_11669__boxed_2999_, v___x_2989_, v_normal_boxed_3000_, v_normal_boxed_3001_, v_data_2992_, v_data_2993_, v___y_11671__boxed_3002_, v_accepts_2995_, v___y_11672__boxed_3003_, v___y_11673__boxed_3004_, v_x_2998_);
lean_dec_ref(v_data_2993_);
lean_dec_ref(v_data_2992_);
lean_dec_ref(v___x_2989_);
v_r_3006_ = lean_box_uint32(v_res_3005_);
return v_r_3006_;
}
}
LEAN_EXPORT uint32_t lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotCostHarness_verify_spec__1___lam__4(lean_object* v___x_3007_, lean_object* v___x_3008_, lean_object* v_x_3009_){
_start:
{
uint32_t v___x_3010_; 
v___x_3010_ = lp_competition_Submission_R24DotProbe_eagerFull(v___x_3007_, v___x_3008_);
return v___x_3010_;
}
}
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotCostHarness_verify_spec__1___lam__4___boxed(lean_object* v___x_3011_, lean_object* v___x_3012_, lean_object* v_x_3013_){
_start:
{
uint32_t v_res_3014_; lean_object* v_r_3015_; 
v_res_3014_ = lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotCostHarness_verify_spec__1___lam__4(v___x_3011_, v___x_3012_, v_x_3013_);
v_r_3015_ = lean_box_uint32(v_res_3014_);
return v_r_3015_;
}
}
LEAN_EXPORT uint32_t lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotCostHarness_verify_spec__1___lam__2(lean_object* v___x_3016_, lean_object* v___x_3017_, lean_object* v_x_3018_){
_start:
{
uint32_t v___x_3019_; 
v___x_3019_ = lp_competition_Submission_R24PortableF64_attemptCold(v___x_3016_, v___x_3017_);
return v___x_3019_;
}
}
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotCostHarness_verify_spec__1___lam__2___boxed(lean_object* v___x_3020_, lean_object* v___x_3021_, lean_object* v_x_3022_){
_start:
{
uint32_t v_res_3023_; lean_object* v_r_3024_; 
v_res_3023_ = lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotCostHarness_verify_spec__1___lam__2(v___x_3020_, v___x_3021_, v_x_3022_);
v_r_3024_ = lean_box_uint32(v_res_3023_);
return v_r_3024_;
}
}
LEAN_EXPORT uint32_t lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotCostHarness_verify_spec__1___lam__1(lean_object* v___x_3025_, lean_object* v_x_3026_){
_start:
{
uint32_t v___x_3027_; 
v___x_3027_ = lp_competition_Submission_R24ExactDotCost_referencePrepared(v___x_3025_);
return v___x_3027_;
}
}
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotCostHarness_verify_spec__1___lam__1___boxed(lean_object* v___x_3028_, lean_object* v_x_3029_){
_start:
{
uint32_t v_res_3030_; lean_object* v_r_3031_; 
v_res_3030_ = lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotCostHarness_verify_spec__1___lam__1(v___x_3028_, v_x_3029_);
lean_dec_ref(v___x_3028_);
v_r_3031_ = lean_box_uint32(v_res_3030_);
return v_r_3031_;
}
}
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotCostHarness_verify_spec__1(lean_object* v_as_3047_, size_t v_sz_3048_, size_t v_i_3049_, lean_object* v_b_3050_){
_start:
{
uint32_t v___y_3053_; lean_object* v___y_3054_; uint32_t v___y_3055_; lean_object* v___y_3056_; uint32_t v___y_3057_; uint32_t v___y_3058_; uint32_t v___y_3059_; uint32_t v___y_3060_; uint32_t v___y_3061_; uint32_t v___y_3062_; uint32_t v___y_3063_; uint32_t v___y_3064_; uint32_t v___y_3065_; lean_object* v_accepts_3066_; lean_object* v___y_3130_; uint8_t v___x_3135_; 
v___x_3135_ = lean_usize_dec_lt(v_i_3049_, v_sz_3048_);
if (v___x_3135_ == 0)
{
lean_object* v___x_3136_; 
v___x_3136_ = lean_alloc_ctor(0, 1, 0);
lean_ctor_set(v___x_3136_, 0, v_b_3050_);
return v___x_3136_;
}
else
{
lean_object* v_fst_3137_; lean_object* v_snd_3138_; lean_object* v___x_3140_; uint8_t v_isShared_3141_; uint8_t v_isSharedCheck_3576_; 
v_fst_3137_ = lean_ctor_get(v_b_3050_, 0);
v_snd_3138_ = lean_ctor_get(v_b_3050_, 1);
v_isSharedCheck_3576_ = !lean_is_exclusive(v_b_3050_);
if (v_isSharedCheck_3576_ == 0)
{
v___x_3140_ = v_b_3050_;
v_isShared_3141_ = v_isSharedCheck_3576_;
goto v_resetjp_3139_;
}
else
{
lean_inc(v_snd_3138_);
lean_inc(v_fst_3137_);
lean_dec(v_b_3050_);
v___x_3140_ = lean_box(0);
v_isShared_3141_ = v_isSharedCheck_3576_;
goto v_resetjp_3139_;
}
v_resetjp_3139_:
{
lean_object* v___y_3143_; lean_object* v___y_3144_; lean_object* v___y_3145_; lean_object* v___y_3146_; lean_object* v___y_3147_; lean_object* v___y_3148_; uint32_t v___y_3149_; uint32_t v___y_3150_; lean_object* v___y_3151_; lean_object* v___y_3152_; uint32_t v___y_3153_; lean_object* v___y_3154_; lean_object* v_unknown_3155_; lean_object* v___y_3345_; lean_object* v___y_3346_; lean_object* v___y_3347_; lean_object* v___y_3348_; lean_object* v___y_3349_; lean_object* v___y_3350_; lean_object* v___y_3351_; lean_object* v___y_3352_; uint32_t v___y_3353_; uint32_t v___y_3354_; lean_object* v___y_3355_; lean_object* v___y_3356_; uint32_t v___y_3357_; lean_object* v___y_3362_; lean_object* v___y_3363_; lean_object* v___y_3364_; lean_object* v___y_3365_; lean_object* v___y_3366_; lean_object* v___y_3367_; lean_object* v___y_3368_; lean_object* v___y_3369_; uint32_t v___y_3370_; uint32_t v___y_3371_; lean_object* v___y_3372_; lean_object* v___y_3373_; uint32_t v___y_3374_; uint8_t v___y_3375_; lean_object* v_a_3377_; lean_object* v_x_3384_; lean_object* v_expected_3385_; lean_object* v_accepts_3386_; lean_object* v___y_3388_; lean_object* v___y_3389_; lean_object* v___y_3390_; uint32_t v___y_3391_; uint32_t v___y_3392_; lean_object* v___y_3393_; lean_object* v___y_3394_; lean_object* v___y_3395_; lean_object* v___y_3396_; lean_object* v_raw_3397_; lean_object* v_data_3398_; uint8_t v_normal_3399_; lean_object* v___y_3400_; uint8_t v___y_3401_; lean_object* v___y_3402_; lean_object* v___y_3403_; lean_object* v___y_3404_; lean_object* v___y_3405_; lean_object* v_raw_3406_; lean_object* v_data_3407_; uint8_t v_normal_3408_; uint8_t v___y_3409_; uint32_t v___y_3410_; lean_object* v___y_3499_; uint8_t v___y_3500_; lean_object* v___y_3501_; lean_object* v___y_3502_; lean_object* v___y_3503_; lean_object* v___y_3504_; lean_object* v___y_3505_; lean_object* v___y_3506_; lean_object* v___y_3507_; lean_object* v___y_3508_; lean_object* v___y_3509_; uint32_t v___y_3510_; lean_object* v___y_3511_; lean_object* v___y_3512_; uint8_t v___y_3513_; uint8_t v___y_3522_; uint8_t v___y_3562_; lean_object* v___x_3569_; uint8_t v___x_3570_; 
v_a_3377_ = lean_array_uget_borrowed(v_as_3047_, v_i_3049_);
v_x_3384_ = lean_ctor_get(v_a_3377_, 3);
v_expected_3385_ = lean_ctor_get(v_a_3377_, 5);
v_accepts_3386_ = lean_unsigned_to_nat(0u);
v___x_3569_ = lean_unsigned_to_nat(4294967295u);
v___x_3570_ = lean_nat_dec_lt(v___x_3569_, v_expected_3385_);
if (v___x_3570_ == 0)
{
lean_object* v___x_3571_; uint8_t v___x_3572_; 
v___x_3571_ = lean_array_get_size(v_x_3384_);
v___x_3572_ = lean_nat_dec_lt(v_accepts_3386_, v___x_3571_);
if (v___x_3572_ == 0)
{
v___y_3562_ = v___x_3570_;
goto v___jp_3561_;
}
else
{
if (v___x_3572_ == 0)
{
v___y_3562_ = v___x_3570_;
goto v___jp_3561_;
}
else
{
size_t v___x_3573_; size_t v___x_3574_; uint8_t v___x_3575_; 
v___x_3573_ = ((size_t)0ULL);
v___x_3574_ = lean_usize_of_nat(v___x_3571_);
v___x_3575_ = lp_competition___private_Init_Data_Array_Basic_0__Array_anyMUnsafe_any___at___00R24DotCostHarness_verify_spec__0(v_x_3384_, v___x_3573_, v___x_3574_);
v___y_3562_ = v___x_3575_;
goto v___jp_3561_;
}
}
}
else
{
v___y_3562_ = v___x_3570_;
goto v___jp_3561_;
}
v___jp_3142_:
{
lean_object* v___x_3156_; 
v___x_3156_ = l_IO_lazyPure___redArg(v___y_3145_);
if (lean_obj_tag(v___x_3156_) == 0)
{
lean_object* v_a_3157_; lean_object* v___x_3158_; 
v_a_3157_ = lean_ctor_get(v___x_3156_, 0);
lean_inc(v_a_3157_);
lean_dec_ref_known(v___x_3156_, 1);
v___x_3158_ = l_IO_lazyPure___redArg(v___y_3143_);
if (lean_obj_tag(v___x_3158_) == 0)
{
lean_object* v_a_3159_; lean_object* v___x_3160_; 
v_a_3159_ = lean_ctor_get(v___x_3158_, 0);
lean_inc(v_a_3159_);
lean_dec_ref_known(v___x_3158_, 1);
v___x_3160_ = l_IO_lazyPure___redArg(v___y_3151_);
if (lean_obj_tag(v___x_3160_) == 0)
{
lean_object* v_a_3161_; lean_object* v___x_3162_; 
v_a_3161_ = lean_ctor_get(v___x_3160_, 0);
lean_inc(v_a_3161_);
lean_dec_ref_known(v___x_3160_, 1);
v___x_3162_ = l_IO_lazyPure___redArg(v___y_3144_);
if (lean_obj_tag(v___x_3162_) == 0)
{
lean_object* v_a_3163_; lean_object* v___x_3164_; 
v_a_3163_ = lean_ctor_get(v___x_3162_, 0);
lean_inc(v_a_3163_);
lean_dec_ref_known(v___x_3162_, 1);
v___x_3164_ = l_IO_lazyPure___redArg(v___y_3152_);
if (lean_obj_tag(v___x_3164_) == 0)
{
lean_object* v_a_3165_; lean_object* v___x_3166_; 
v_a_3165_ = lean_ctor_get(v___x_3164_, 0);
lean_inc(v_a_3165_);
lean_dec_ref_known(v___x_3164_, 1);
v___x_3166_ = l_IO_lazyPure___redArg(v___y_3148_);
if (lean_obj_tag(v___x_3166_) == 0)
{
lean_object* v_a_3167_; lean_object* v___x_3168_; 
v_a_3167_ = lean_ctor_get(v___x_3166_, 0);
lean_inc(v_a_3167_);
lean_dec_ref_known(v___x_3166_, 1);
v___x_3168_ = l_IO_lazyPure___redArg(v___y_3154_);
if (lean_obj_tag(v___x_3168_) == 0)
{
lean_object* v_a_3169_; lean_object* v___x_3170_; 
v_a_3169_ = lean_ctor_get(v___x_3168_, 0);
lean_inc(v_a_3169_);
lean_dec_ref_known(v___x_3168_, 1);
v___x_3170_ = l_IO_lazyPure___redArg(v___y_3147_);
if (lean_obj_tag(v___x_3170_) == 0)
{
lean_object* v_a_3171_; lean_object* v___x_3172_; uint32_t v___x_3173_; lean_object* v___x_3174_; 
v_a_3171_ = lean_ctor_get(v___x_3170_, 0);
lean_inc(v_a_3171_);
lean_dec_ref_known(v___x_3170_, 1);
v___x_3172_ = ((lean_object*)(lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotCostHarness_verify_spec__1___closed__3));
v___x_3173_ = lean_unbox_uint32(v_a_3157_);
lean_inc_ref(v___y_3146_);
v___x_3174_ = lp_competition_R24DotCostHarness_checkWord(v___y_3146_, v___x_3172_, v___x_3173_, v___y_3150_);
if (lean_obj_tag(v___x_3174_) == 0)
{
lean_object* v___x_3175_; uint32_t v___x_3176_; lean_object* v___x_3177_; 
lean_dec_ref_known(v___x_3174_, 1);
v___x_3175_ = ((lean_object*)(lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotCostHarness_verify_spec__1___closed__4));
v___x_3176_ = lean_unbox_uint32(v_a_3159_);
lean_inc_ref(v___y_3146_);
v___x_3177_ = lp_competition_R24DotCostHarness_checkWord(v___y_3146_, v___x_3175_, v___x_3176_, v___y_3150_);
if (lean_obj_tag(v___x_3177_) == 0)
{
lean_object* v___x_3178_; uint32_t v___x_3179_; lean_object* v___x_3180_; 
lean_dec_ref_known(v___x_3177_, 1);
v___x_3178_ = ((lean_object*)(lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotCostHarness_verify_spec__1___closed__5));
v___x_3179_ = lean_unbox_uint32(v_a_3161_);
lean_inc_ref(v___y_3146_);
v___x_3180_ = lp_competition_R24DotCostHarness_checkWord(v___y_3146_, v___x_3178_, v___x_3179_, v___y_3150_);
if (lean_obj_tag(v___x_3180_) == 0)
{
lean_object* v___x_3181_; uint32_t v___x_3182_; lean_object* v___x_3183_; 
lean_dec_ref_known(v___x_3180_, 1);
v___x_3181_ = ((lean_object*)(lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotCostHarness_verify_spec__1___closed__6));
v___x_3182_ = lean_unbox_uint32(v_a_3163_);
lean_inc_ref(v___y_3146_);
v___x_3183_ = lp_competition_R24DotCostHarness_checkWord(v___y_3146_, v___x_3181_, v___x_3182_, v___y_3150_);
if (lean_obj_tag(v___x_3183_) == 0)
{
lean_object* v___x_3184_; uint32_t v___x_3185_; lean_object* v___x_3186_; 
lean_dec_ref_known(v___x_3183_, 1);
v___x_3184_ = ((lean_object*)(lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotCostHarness_verify_spec__1___closed__7));
v___x_3185_ = lean_unbox_uint32(v_a_3165_);
lean_inc_ref(v___y_3146_);
v___x_3186_ = lp_competition_R24DotCostHarness_checkWord(v___y_3146_, v___x_3184_, v___x_3185_, v___y_3150_);
if (lean_obj_tag(v___x_3186_) == 0)
{
lean_object* v___x_3187_; uint32_t v___x_3188_; lean_object* v___x_3189_; 
lean_dec_ref_known(v___x_3186_, 1);
v___x_3187_ = ((lean_object*)(lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotCostHarness_verify_spec__1___closed__8));
v___x_3188_ = lean_unbox_uint32(v_a_3167_);
lean_inc_ref(v___y_3146_);
v___x_3189_ = lp_competition_R24DotCostHarness_checkWord(v___y_3146_, v___x_3187_, v___x_3188_, v___y_3150_);
if (lean_obj_tag(v___x_3189_) == 0)
{
lean_object* v___x_3190_; uint32_t v___x_3191_; lean_object* v___x_3192_; 
lean_dec_ref_known(v___x_3189_, 1);
v___x_3190_ = ((lean_object*)(lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotCostHarness_verify_spec__1___closed__9));
v___x_3191_ = lean_unbox_uint32(v_a_3169_);
lean_inc_ref(v___y_3146_);
v___x_3192_ = lp_competition_R24DotCostHarness_checkWord(v___y_3146_, v___x_3190_, v___x_3191_, v___y_3150_);
if (lean_obj_tag(v___x_3192_) == 0)
{
lean_object* v___x_3193_; uint32_t v___x_3194_; lean_object* v___x_3195_; 
lean_dec_ref_known(v___x_3192_, 1);
v___x_3193_ = ((lean_object*)(lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotCostHarness_verify_spec__1___closed__10));
v___x_3194_ = lean_unbox_uint32(v_a_3171_);
lean_inc_ref(v___y_3146_);
v___x_3195_ = lp_competition_R24DotCostHarness_checkWord(v___y_3146_, v___x_3193_, v___x_3194_, v___y_3150_);
if (lean_obj_tag(v___x_3195_) == 0)
{
uint32_t v___x_3196_; uint8_t v___x_3197_; 
lean_dec_ref_known(v___x_3195_, 1);
v___x_3196_ = 0;
v___x_3197_ = lean_uint32_dec_eq(v___y_3149_, v___x_3196_);
if (v___x_3197_ == 0)
{
lean_object* v___x_3198_; lean_object* v___x_3199_; uint32_t v___x_3200_; uint32_t v___x_3201_; uint32_t v___x_3202_; uint32_t v___x_3203_; uint32_t v___x_3204_; uint32_t v___x_3205_; uint32_t v___x_3206_; uint32_t v___x_3207_; 
v___x_3198_ = lean_unsigned_to_nat(1u);
v___x_3199_ = lean_nat_add(v_fst_3137_, v___x_3198_);
lean_dec(v_fst_3137_);
v___x_3200_ = lean_unbox_uint32(v_a_3167_);
lean_dec(v_a_3167_);
v___x_3201_ = lean_unbox_uint32(v_a_3157_);
lean_dec(v_a_3157_);
v___x_3202_ = lean_unbox_uint32(v_a_3169_);
lean_dec(v_a_3169_);
v___x_3203_ = lean_unbox_uint32(v_a_3163_);
lean_dec(v_a_3163_);
v___x_3204_ = lean_unbox_uint32(v_a_3171_);
lean_dec(v_a_3171_);
v___x_3205_ = lean_unbox_uint32(v_a_3161_);
lean_dec(v_a_3161_);
v___x_3206_ = lean_unbox_uint32(v_a_3159_);
lean_dec(v_a_3159_);
v___x_3207_ = lean_unbox_uint32(v_a_3165_);
lean_dec(v_a_3165_);
v___y_3053_ = v___x_3200_;
v___y_3054_ = v_unknown_3155_;
v___y_3055_ = v___x_3201_;
v___y_3056_ = v___y_3146_;
v___y_3057_ = v___x_3202_;
v___y_3058_ = v___y_3149_;
v___y_3059_ = v___x_3203_;
v___y_3060_ = v___x_3204_;
v___y_3061_ = v___y_3150_;
v___y_3062_ = v___x_3205_;
v___y_3063_ = v___y_3153_;
v___y_3064_ = v___x_3206_;
v___y_3065_ = v___x_3207_;
v_accepts_3066_ = v___x_3199_;
goto v___jp_3052_;
}
else
{
uint32_t v___x_3208_; uint32_t v___x_3209_; uint32_t v___x_3210_; uint32_t v___x_3211_; uint32_t v___x_3212_; uint32_t v___x_3213_; uint32_t v___x_3214_; uint32_t v___x_3215_; 
v___x_3208_ = lean_unbox_uint32(v_a_3167_);
lean_dec(v_a_3167_);
v___x_3209_ = lean_unbox_uint32(v_a_3157_);
lean_dec(v_a_3157_);
v___x_3210_ = lean_unbox_uint32(v_a_3169_);
lean_dec(v_a_3169_);
v___x_3211_ = lean_unbox_uint32(v_a_3163_);
lean_dec(v_a_3163_);
v___x_3212_ = lean_unbox_uint32(v_a_3171_);
lean_dec(v_a_3171_);
v___x_3213_ = lean_unbox_uint32(v_a_3161_);
lean_dec(v_a_3161_);
v___x_3214_ = lean_unbox_uint32(v_a_3159_);
lean_dec(v_a_3159_);
v___x_3215_ = lean_unbox_uint32(v_a_3165_);
lean_dec(v_a_3165_);
v___y_3053_ = v___x_3208_;
v___y_3054_ = v_unknown_3155_;
v___y_3055_ = v___x_3209_;
v___y_3056_ = v___y_3146_;
v___y_3057_ = v___x_3210_;
v___y_3058_ = v___y_3149_;
v___y_3059_ = v___x_3211_;
v___y_3060_ = v___x_3212_;
v___y_3061_ = v___y_3150_;
v___y_3062_ = v___x_3213_;
v___y_3063_ = v___y_3153_;
v___y_3064_ = v___x_3214_;
v___y_3065_ = v___x_3215_;
v_accepts_3066_ = v_fst_3137_;
goto v___jp_3052_;
}
}
else
{
lean_object* v_a_3216_; lean_object* v___x_3218_; uint8_t v_isShared_3219_; uint8_t v_isSharedCheck_3223_; 
lean_dec(v_a_3171_);
lean_dec(v_a_3169_);
lean_dec(v_a_3167_);
lean_dec(v_a_3165_);
lean_dec(v_a_3163_);
lean_dec(v_a_3161_);
lean_dec(v_a_3159_);
lean_dec(v_a_3157_);
lean_dec(v_unknown_3155_);
lean_dec_ref(v___y_3146_);
lean_dec(v_fst_3137_);
v_a_3216_ = lean_ctor_get(v___x_3195_, 0);
v_isSharedCheck_3223_ = !lean_is_exclusive(v___x_3195_);
if (v_isSharedCheck_3223_ == 0)
{
v___x_3218_ = v___x_3195_;
v_isShared_3219_ = v_isSharedCheck_3223_;
goto v_resetjp_3217_;
}
else
{
lean_inc(v_a_3216_);
lean_dec(v___x_3195_);
v___x_3218_ = lean_box(0);
v_isShared_3219_ = v_isSharedCheck_3223_;
goto v_resetjp_3217_;
}
v_resetjp_3217_:
{
lean_object* v___x_3221_; 
if (v_isShared_3219_ == 0)
{
v___x_3221_ = v___x_3218_;
goto v_reusejp_3220_;
}
else
{
lean_object* v_reuseFailAlloc_3222_; 
v_reuseFailAlloc_3222_ = lean_alloc_ctor(1, 1, 0);
lean_ctor_set(v_reuseFailAlloc_3222_, 0, v_a_3216_);
v___x_3221_ = v_reuseFailAlloc_3222_;
goto v_reusejp_3220_;
}
v_reusejp_3220_:
{
return v___x_3221_;
}
}
}
}
else
{
lean_object* v_a_3224_; lean_object* v___x_3226_; uint8_t v_isShared_3227_; uint8_t v_isSharedCheck_3231_; 
lean_dec(v_a_3171_);
lean_dec(v_a_3169_);
lean_dec(v_a_3167_);
lean_dec(v_a_3165_);
lean_dec(v_a_3163_);
lean_dec(v_a_3161_);
lean_dec(v_a_3159_);
lean_dec(v_a_3157_);
lean_dec(v_unknown_3155_);
lean_dec_ref(v___y_3146_);
lean_dec(v_fst_3137_);
v_a_3224_ = lean_ctor_get(v___x_3192_, 0);
v_isSharedCheck_3231_ = !lean_is_exclusive(v___x_3192_);
if (v_isSharedCheck_3231_ == 0)
{
v___x_3226_ = v___x_3192_;
v_isShared_3227_ = v_isSharedCheck_3231_;
goto v_resetjp_3225_;
}
else
{
lean_inc(v_a_3224_);
lean_dec(v___x_3192_);
v___x_3226_ = lean_box(0);
v_isShared_3227_ = v_isSharedCheck_3231_;
goto v_resetjp_3225_;
}
v_resetjp_3225_:
{
lean_object* v___x_3229_; 
if (v_isShared_3227_ == 0)
{
v___x_3229_ = v___x_3226_;
goto v_reusejp_3228_;
}
else
{
lean_object* v_reuseFailAlloc_3230_; 
v_reuseFailAlloc_3230_ = lean_alloc_ctor(1, 1, 0);
lean_ctor_set(v_reuseFailAlloc_3230_, 0, v_a_3224_);
v___x_3229_ = v_reuseFailAlloc_3230_;
goto v_reusejp_3228_;
}
v_reusejp_3228_:
{
return v___x_3229_;
}
}
}
}
else
{
lean_object* v_a_3232_; lean_object* v___x_3234_; uint8_t v_isShared_3235_; uint8_t v_isSharedCheck_3239_; 
lean_dec(v_a_3171_);
lean_dec(v_a_3169_);
lean_dec(v_a_3167_);
lean_dec(v_a_3165_);
lean_dec(v_a_3163_);
lean_dec(v_a_3161_);
lean_dec(v_a_3159_);
lean_dec(v_a_3157_);
lean_dec(v_unknown_3155_);
lean_dec_ref(v___y_3146_);
lean_dec(v_fst_3137_);
v_a_3232_ = lean_ctor_get(v___x_3189_, 0);
v_isSharedCheck_3239_ = !lean_is_exclusive(v___x_3189_);
if (v_isSharedCheck_3239_ == 0)
{
v___x_3234_ = v___x_3189_;
v_isShared_3235_ = v_isSharedCheck_3239_;
goto v_resetjp_3233_;
}
else
{
lean_inc(v_a_3232_);
lean_dec(v___x_3189_);
v___x_3234_ = lean_box(0);
v_isShared_3235_ = v_isSharedCheck_3239_;
goto v_resetjp_3233_;
}
v_resetjp_3233_:
{
lean_object* v___x_3237_; 
if (v_isShared_3235_ == 0)
{
v___x_3237_ = v___x_3234_;
goto v_reusejp_3236_;
}
else
{
lean_object* v_reuseFailAlloc_3238_; 
v_reuseFailAlloc_3238_ = lean_alloc_ctor(1, 1, 0);
lean_ctor_set(v_reuseFailAlloc_3238_, 0, v_a_3232_);
v___x_3237_ = v_reuseFailAlloc_3238_;
goto v_reusejp_3236_;
}
v_reusejp_3236_:
{
return v___x_3237_;
}
}
}
}
else
{
lean_object* v_a_3240_; lean_object* v___x_3242_; uint8_t v_isShared_3243_; uint8_t v_isSharedCheck_3247_; 
lean_dec(v_a_3171_);
lean_dec(v_a_3169_);
lean_dec(v_a_3167_);
lean_dec(v_a_3165_);
lean_dec(v_a_3163_);
lean_dec(v_a_3161_);
lean_dec(v_a_3159_);
lean_dec(v_a_3157_);
lean_dec(v_unknown_3155_);
lean_dec_ref(v___y_3146_);
lean_dec(v_fst_3137_);
v_a_3240_ = lean_ctor_get(v___x_3186_, 0);
v_isSharedCheck_3247_ = !lean_is_exclusive(v___x_3186_);
if (v_isSharedCheck_3247_ == 0)
{
v___x_3242_ = v___x_3186_;
v_isShared_3243_ = v_isSharedCheck_3247_;
goto v_resetjp_3241_;
}
else
{
lean_inc(v_a_3240_);
lean_dec(v___x_3186_);
v___x_3242_ = lean_box(0);
v_isShared_3243_ = v_isSharedCheck_3247_;
goto v_resetjp_3241_;
}
v_resetjp_3241_:
{
lean_object* v___x_3245_; 
if (v_isShared_3243_ == 0)
{
v___x_3245_ = v___x_3242_;
goto v_reusejp_3244_;
}
else
{
lean_object* v_reuseFailAlloc_3246_; 
v_reuseFailAlloc_3246_ = lean_alloc_ctor(1, 1, 0);
lean_ctor_set(v_reuseFailAlloc_3246_, 0, v_a_3240_);
v___x_3245_ = v_reuseFailAlloc_3246_;
goto v_reusejp_3244_;
}
v_reusejp_3244_:
{
return v___x_3245_;
}
}
}
}
else
{
lean_object* v_a_3248_; lean_object* v___x_3250_; uint8_t v_isShared_3251_; uint8_t v_isSharedCheck_3255_; 
lean_dec(v_a_3171_);
lean_dec(v_a_3169_);
lean_dec(v_a_3167_);
lean_dec(v_a_3165_);
lean_dec(v_a_3163_);
lean_dec(v_a_3161_);
lean_dec(v_a_3159_);
lean_dec(v_a_3157_);
lean_dec(v_unknown_3155_);
lean_dec_ref(v___y_3146_);
lean_dec(v_fst_3137_);
v_a_3248_ = lean_ctor_get(v___x_3183_, 0);
v_isSharedCheck_3255_ = !lean_is_exclusive(v___x_3183_);
if (v_isSharedCheck_3255_ == 0)
{
v___x_3250_ = v___x_3183_;
v_isShared_3251_ = v_isSharedCheck_3255_;
goto v_resetjp_3249_;
}
else
{
lean_inc(v_a_3248_);
lean_dec(v___x_3183_);
v___x_3250_ = lean_box(0);
v_isShared_3251_ = v_isSharedCheck_3255_;
goto v_resetjp_3249_;
}
v_resetjp_3249_:
{
lean_object* v___x_3253_; 
if (v_isShared_3251_ == 0)
{
v___x_3253_ = v___x_3250_;
goto v_reusejp_3252_;
}
else
{
lean_object* v_reuseFailAlloc_3254_; 
v_reuseFailAlloc_3254_ = lean_alloc_ctor(1, 1, 0);
lean_ctor_set(v_reuseFailAlloc_3254_, 0, v_a_3248_);
v___x_3253_ = v_reuseFailAlloc_3254_;
goto v_reusejp_3252_;
}
v_reusejp_3252_:
{
return v___x_3253_;
}
}
}
}
else
{
lean_object* v_a_3256_; lean_object* v___x_3258_; uint8_t v_isShared_3259_; uint8_t v_isSharedCheck_3263_; 
lean_dec(v_a_3171_);
lean_dec(v_a_3169_);
lean_dec(v_a_3167_);
lean_dec(v_a_3165_);
lean_dec(v_a_3163_);
lean_dec(v_a_3161_);
lean_dec(v_a_3159_);
lean_dec(v_a_3157_);
lean_dec(v_unknown_3155_);
lean_dec_ref(v___y_3146_);
lean_dec(v_fst_3137_);
v_a_3256_ = lean_ctor_get(v___x_3180_, 0);
v_isSharedCheck_3263_ = !lean_is_exclusive(v___x_3180_);
if (v_isSharedCheck_3263_ == 0)
{
v___x_3258_ = v___x_3180_;
v_isShared_3259_ = v_isSharedCheck_3263_;
goto v_resetjp_3257_;
}
else
{
lean_inc(v_a_3256_);
lean_dec(v___x_3180_);
v___x_3258_ = lean_box(0);
v_isShared_3259_ = v_isSharedCheck_3263_;
goto v_resetjp_3257_;
}
v_resetjp_3257_:
{
lean_object* v___x_3261_; 
if (v_isShared_3259_ == 0)
{
v___x_3261_ = v___x_3258_;
goto v_reusejp_3260_;
}
else
{
lean_object* v_reuseFailAlloc_3262_; 
v_reuseFailAlloc_3262_ = lean_alloc_ctor(1, 1, 0);
lean_ctor_set(v_reuseFailAlloc_3262_, 0, v_a_3256_);
v___x_3261_ = v_reuseFailAlloc_3262_;
goto v_reusejp_3260_;
}
v_reusejp_3260_:
{
return v___x_3261_;
}
}
}
}
else
{
lean_object* v_a_3264_; lean_object* v___x_3266_; uint8_t v_isShared_3267_; uint8_t v_isSharedCheck_3271_; 
lean_dec(v_a_3171_);
lean_dec(v_a_3169_);
lean_dec(v_a_3167_);
lean_dec(v_a_3165_);
lean_dec(v_a_3163_);
lean_dec(v_a_3161_);
lean_dec(v_a_3159_);
lean_dec(v_a_3157_);
lean_dec(v_unknown_3155_);
lean_dec_ref(v___y_3146_);
lean_dec(v_fst_3137_);
v_a_3264_ = lean_ctor_get(v___x_3177_, 0);
v_isSharedCheck_3271_ = !lean_is_exclusive(v___x_3177_);
if (v_isSharedCheck_3271_ == 0)
{
v___x_3266_ = v___x_3177_;
v_isShared_3267_ = v_isSharedCheck_3271_;
goto v_resetjp_3265_;
}
else
{
lean_inc(v_a_3264_);
lean_dec(v___x_3177_);
v___x_3266_ = lean_box(0);
v_isShared_3267_ = v_isSharedCheck_3271_;
goto v_resetjp_3265_;
}
v_resetjp_3265_:
{
lean_object* v___x_3269_; 
if (v_isShared_3267_ == 0)
{
v___x_3269_ = v___x_3266_;
goto v_reusejp_3268_;
}
else
{
lean_object* v_reuseFailAlloc_3270_; 
v_reuseFailAlloc_3270_ = lean_alloc_ctor(1, 1, 0);
lean_ctor_set(v_reuseFailAlloc_3270_, 0, v_a_3264_);
v___x_3269_ = v_reuseFailAlloc_3270_;
goto v_reusejp_3268_;
}
v_reusejp_3268_:
{
return v___x_3269_;
}
}
}
}
else
{
lean_object* v_a_3272_; lean_object* v___x_3274_; uint8_t v_isShared_3275_; uint8_t v_isSharedCheck_3279_; 
lean_dec(v_a_3171_);
lean_dec(v_a_3169_);
lean_dec(v_a_3167_);
lean_dec(v_a_3165_);
lean_dec(v_a_3163_);
lean_dec(v_a_3161_);
lean_dec(v_a_3159_);
lean_dec(v_a_3157_);
lean_dec(v_unknown_3155_);
lean_dec_ref(v___y_3146_);
lean_dec(v_fst_3137_);
v_a_3272_ = lean_ctor_get(v___x_3174_, 0);
v_isSharedCheck_3279_ = !lean_is_exclusive(v___x_3174_);
if (v_isSharedCheck_3279_ == 0)
{
v___x_3274_ = v___x_3174_;
v_isShared_3275_ = v_isSharedCheck_3279_;
goto v_resetjp_3273_;
}
else
{
lean_inc(v_a_3272_);
lean_dec(v___x_3174_);
v___x_3274_ = lean_box(0);
v_isShared_3275_ = v_isSharedCheck_3279_;
goto v_resetjp_3273_;
}
v_resetjp_3273_:
{
lean_object* v___x_3277_; 
if (v_isShared_3275_ == 0)
{
v___x_3277_ = v___x_3274_;
goto v_reusejp_3276_;
}
else
{
lean_object* v_reuseFailAlloc_3278_; 
v_reuseFailAlloc_3278_ = lean_alloc_ctor(1, 1, 0);
lean_ctor_set(v_reuseFailAlloc_3278_, 0, v_a_3272_);
v___x_3277_ = v_reuseFailAlloc_3278_;
goto v_reusejp_3276_;
}
v_reusejp_3276_:
{
return v___x_3277_;
}
}
}
}
else
{
lean_object* v_a_3280_; lean_object* v___x_3282_; uint8_t v_isShared_3283_; uint8_t v_isSharedCheck_3287_; 
lean_dec(v_a_3169_);
lean_dec(v_a_3167_);
lean_dec(v_a_3165_);
lean_dec(v_a_3163_);
lean_dec(v_a_3161_);
lean_dec(v_a_3159_);
lean_dec(v_a_3157_);
lean_dec(v_unknown_3155_);
lean_dec_ref(v___y_3146_);
lean_dec(v_fst_3137_);
v_a_3280_ = lean_ctor_get(v___x_3170_, 0);
v_isSharedCheck_3287_ = !lean_is_exclusive(v___x_3170_);
if (v_isSharedCheck_3287_ == 0)
{
v___x_3282_ = v___x_3170_;
v_isShared_3283_ = v_isSharedCheck_3287_;
goto v_resetjp_3281_;
}
else
{
lean_inc(v_a_3280_);
lean_dec(v___x_3170_);
v___x_3282_ = lean_box(0);
v_isShared_3283_ = v_isSharedCheck_3287_;
goto v_resetjp_3281_;
}
v_resetjp_3281_:
{
lean_object* v___x_3285_; 
if (v_isShared_3283_ == 0)
{
v___x_3285_ = v___x_3282_;
goto v_reusejp_3284_;
}
else
{
lean_object* v_reuseFailAlloc_3286_; 
v_reuseFailAlloc_3286_ = lean_alloc_ctor(1, 1, 0);
lean_ctor_set(v_reuseFailAlloc_3286_, 0, v_a_3280_);
v___x_3285_ = v_reuseFailAlloc_3286_;
goto v_reusejp_3284_;
}
v_reusejp_3284_:
{
return v___x_3285_;
}
}
}
}
else
{
lean_object* v_a_3288_; lean_object* v___x_3290_; uint8_t v_isShared_3291_; uint8_t v_isSharedCheck_3295_; 
lean_dec(v_a_3167_);
lean_dec(v_a_3165_);
lean_dec(v_a_3163_);
lean_dec(v_a_3161_);
lean_dec(v_a_3159_);
lean_dec(v_a_3157_);
lean_dec(v_unknown_3155_);
lean_dec_ref(v___y_3147_);
lean_dec_ref(v___y_3146_);
lean_dec(v_fst_3137_);
v_a_3288_ = lean_ctor_get(v___x_3168_, 0);
v_isSharedCheck_3295_ = !lean_is_exclusive(v___x_3168_);
if (v_isSharedCheck_3295_ == 0)
{
v___x_3290_ = v___x_3168_;
v_isShared_3291_ = v_isSharedCheck_3295_;
goto v_resetjp_3289_;
}
else
{
lean_inc(v_a_3288_);
lean_dec(v___x_3168_);
v___x_3290_ = lean_box(0);
v_isShared_3291_ = v_isSharedCheck_3295_;
goto v_resetjp_3289_;
}
v_resetjp_3289_:
{
lean_object* v___x_3293_; 
if (v_isShared_3291_ == 0)
{
v___x_3293_ = v___x_3290_;
goto v_reusejp_3292_;
}
else
{
lean_object* v_reuseFailAlloc_3294_; 
v_reuseFailAlloc_3294_ = lean_alloc_ctor(1, 1, 0);
lean_ctor_set(v_reuseFailAlloc_3294_, 0, v_a_3288_);
v___x_3293_ = v_reuseFailAlloc_3294_;
goto v_reusejp_3292_;
}
v_reusejp_3292_:
{
return v___x_3293_;
}
}
}
}
else
{
lean_object* v_a_3296_; lean_object* v___x_3298_; uint8_t v_isShared_3299_; uint8_t v_isSharedCheck_3303_; 
lean_dec(v_a_3165_);
lean_dec(v_a_3163_);
lean_dec(v_a_3161_);
lean_dec(v_a_3159_);
lean_dec(v_a_3157_);
lean_dec(v_unknown_3155_);
lean_dec_ref(v___y_3154_);
lean_dec_ref(v___y_3147_);
lean_dec_ref(v___y_3146_);
lean_dec(v_fst_3137_);
v_a_3296_ = lean_ctor_get(v___x_3166_, 0);
v_isSharedCheck_3303_ = !lean_is_exclusive(v___x_3166_);
if (v_isSharedCheck_3303_ == 0)
{
v___x_3298_ = v___x_3166_;
v_isShared_3299_ = v_isSharedCheck_3303_;
goto v_resetjp_3297_;
}
else
{
lean_inc(v_a_3296_);
lean_dec(v___x_3166_);
v___x_3298_ = lean_box(0);
v_isShared_3299_ = v_isSharedCheck_3303_;
goto v_resetjp_3297_;
}
v_resetjp_3297_:
{
lean_object* v___x_3301_; 
if (v_isShared_3299_ == 0)
{
v___x_3301_ = v___x_3298_;
goto v_reusejp_3300_;
}
else
{
lean_object* v_reuseFailAlloc_3302_; 
v_reuseFailAlloc_3302_ = lean_alloc_ctor(1, 1, 0);
lean_ctor_set(v_reuseFailAlloc_3302_, 0, v_a_3296_);
v___x_3301_ = v_reuseFailAlloc_3302_;
goto v_reusejp_3300_;
}
v_reusejp_3300_:
{
return v___x_3301_;
}
}
}
}
else
{
lean_object* v_a_3304_; lean_object* v___x_3306_; uint8_t v_isShared_3307_; uint8_t v_isSharedCheck_3311_; 
lean_dec(v_a_3163_);
lean_dec(v_a_3161_);
lean_dec(v_a_3159_);
lean_dec(v_a_3157_);
lean_dec(v_unknown_3155_);
lean_dec_ref(v___y_3154_);
lean_dec_ref(v___y_3148_);
lean_dec_ref(v___y_3147_);
lean_dec_ref(v___y_3146_);
lean_dec(v_fst_3137_);
v_a_3304_ = lean_ctor_get(v___x_3164_, 0);
v_isSharedCheck_3311_ = !lean_is_exclusive(v___x_3164_);
if (v_isSharedCheck_3311_ == 0)
{
v___x_3306_ = v___x_3164_;
v_isShared_3307_ = v_isSharedCheck_3311_;
goto v_resetjp_3305_;
}
else
{
lean_inc(v_a_3304_);
lean_dec(v___x_3164_);
v___x_3306_ = lean_box(0);
v_isShared_3307_ = v_isSharedCheck_3311_;
goto v_resetjp_3305_;
}
v_resetjp_3305_:
{
lean_object* v___x_3309_; 
if (v_isShared_3307_ == 0)
{
v___x_3309_ = v___x_3306_;
goto v_reusejp_3308_;
}
else
{
lean_object* v_reuseFailAlloc_3310_; 
v_reuseFailAlloc_3310_ = lean_alloc_ctor(1, 1, 0);
lean_ctor_set(v_reuseFailAlloc_3310_, 0, v_a_3304_);
v___x_3309_ = v_reuseFailAlloc_3310_;
goto v_reusejp_3308_;
}
v_reusejp_3308_:
{
return v___x_3309_;
}
}
}
}
else
{
lean_object* v_a_3312_; lean_object* v___x_3314_; uint8_t v_isShared_3315_; uint8_t v_isSharedCheck_3319_; 
lean_dec(v_a_3161_);
lean_dec(v_a_3159_);
lean_dec(v_a_3157_);
lean_dec(v_unknown_3155_);
lean_dec_ref(v___y_3154_);
lean_dec_ref(v___y_3152_);
lean_dec_ref(v___y_3148_);
lean_dec_ref(v___y_3147_);
lean_dec_ref(v___y_3146_);
lean_dec(v_fst_3137_);
v_a_3312_ = lean_ctor_get(v___x_3162_, 0);
v_isSharedCheck_3319_ = !lean_is_exclusive(v___x_3162_);
if (v_isSharedCheck_3319_ == 0)
{
v___x_3314_ = v___x_3162_;
v_isShared_3315_ = v_isSharedCheck_3319_;
goto v_resetjp_3313_;
}
else
{
lean_inc(v_a_3312_);
lean_dec(v___x_3162_);
v___x_3314_ = lean_box(0);
v_isShared_3315_ = v_isSharedCheck_3319_;
goto v_resetjp_3313_;
}
v_resetjp_3313_:
{
lean_object* v___x_3317_; 
if (v_isShared_3315_ == 0)
{
v___x_3317_ = v___x_3314_;
goto v_reusejp_3316_;
}
else
{
lean_object* v_reuseFailAlloc_3318_; 
v_reuseFailAlloc_3318_ = lean_alloc_ctor(1, 1, 0);
lean_ctor_set(v_reuseFailAlloc_3318_, 0, v_a_3312_);
v___x_3317_ = v_reuseFailAlloc_3318_;
goto v_reusejp_3316_;
}
v_reusejp_3316_:
{
return v___x_3317_;
}
}
}
}
else
{
lean_object* v_a_3320_; lean_object* v___x_3322_; uint8_t v_isShared_3323_; uint8_t v_isSharedCheck_3327_; 
lean_dec(v_a_3159_);
lean_dec(v_a_3157_);
lean_dec(v_unknown_3155_);
lean_dec_ref(v___y_3154_);
lean_dec_ref(v___y_3152_);
lean_dec_ref(v___y_3148_);
lean_dec_ref(v___y_3147_);
lean_dec_ref(v___y_3146_);
lean_dec_ref(v___y_3144_);
lean_dec(v_fst_3137_);
v_a_3320_ = lean_ctor_get(v___x_3160_, 0);
v_isSharedCheck_3327_ = !lean_is_exclusive(v___x_3160_);
if (v_isSharedCheck_3327_ == 0)
{
v___x_3322_ = v___x_3160_;
v_isShared_3323_ = v_isSharedCheck_3327_;
goto v_resetjp_3321_;
}
else
{
lean_inc(v_a_3320_);
lean_dec(v___x_3160_);
v___x_3322_ = lean_box(0);
v_isShared_3323_ = v_isSharedCheck_3327_;
goto v_resetjp_3321_;
}
v_resetjp_3321_:
{
lean_object* v___x_3325_; 
if (v_isShared_3323_ == 0)
{
v___x_3325_ = v___x_3322_;
goto v_reusejp_3324_;
}
else
{
lean_object* v_reuseFailAlloc_3326_; 
v_reuseFailAlloc_3326_ = lean_alloc_ctor(1, 1, 0);
lean_ctor_set(v_reuseFailAlloc_3326_, 0, v_a_3320_);
v___x_3325_ = v_reuseFailAlloc_3326_;
goto v_reusejp_3324_;
}
v_reusejp_3324_:
{
return v___x_3325_;
}
}
}
}
else
{
lean_object* v_a_3328_; lean_object* v___x_3330_; uint8_t v_isShared_3331_; uint8_t v_isSharedCheck_3335_; 
lean_dec(v_a_3157_);
lean_dec(v_unknown_3155_);
lean_dec_ref(v___y_3154_);
lean_dec_ref(v___y_3152_);
lean_dec_ref(v___y_3151_);
lean_dec_ref(v___y_3148_);
lean_dec_ref(v___y_3147_);
lean_dec_ref(v___y_3146_);
lean_dec_ref(v___y_3144_);
lean_dec(v_fst_3137_);
v_a_3328_ = lean_ctor_get(v___x_3158_, 0);
v_isSharedCheck_3335_ = !lean_is_exclusive(v___x_3158_);
if (v_isSharedCheck_3335_ == 0)
{
v___x_3330_ = v___x_3158_;
v_isShared_3331_ = v_isSharedCheck_3335_;
goto v_resetjp_3329_;
}
else
{
lean_inc(v_a_3328_);
lean_dec(v___x_3158_);
v___x_3330_ = lean_box(0);
v_isShared_3331_ = v_isSharedCheck_3335_;
goto v_resetjp_3329_;
}
v_resetjp_3329_:
{
lean_object* v___x_3333_; 
if (v_isShared_3331_ == 0)
{
v___x_3333_ = v___x_3330_;
goto v_reusejp_3332_;
}
else
{
lean_object* v_reuseFailAlloc_3334_; 
v_reuseFailAlloc_3334_ = lean_alloc_ctor(1, 1, 0);
lean_ctor_set(v_reuseFailAlloc_3334_, 0, v_a_3328_);
v___x_3333_ = v_reuseFailAlloc_3334_;
goto v_reusejp_3332_;
}
v_reusejp_3332_:
{
return v___x_3333_;
}
}
}
}
else
{
lean_object* v_a_3336_; lean_object* v___x_3338_; uint8_t v_isShared_3339_; uint8_t v_isSharedCheck_3343_; 
lean_dec(v_unknown_3155_);
lean_dec_ref(v___y_3154_);
lean_dec_ref(v___y_3152_);
lean_dec_ref(v___y_3151_);
lean_dec_ref(v___y_3148_);
lean_dec_ref(v___y_3147_);
lean_dec_ref(v___y_3146_);
lean_dec_ref(v___y_3144_);
lean_dec_ref(v___y_3143_);
lean_dec(v_fst_3137_);
v_a_3336_ = lean_ctor_get(v___x_3156_, 0);
v_isSharedCheck_3343_ = !lean_is_exclusive(v___x_3156_);
if (v_isSharedCheck_3343_ == 0)
{
v___x_3338_ = v___x_3156_;
v_isShared_3339_ = v_isSharedCheck_3343_;
goto v_resetjp_3337_;
}
else
{
lean_inc(v_a_3336_);
lean_dec(v___x_3156_);
v___x_3338_ = lean_box(0);
v_isShared_3339_ = v_isSharedCheck_3343_;
goto v_resetjp_3337_;
}
v_resetjp_3337_:
{
lean_object* v___x_3341_; 
if (v_isShared_3339_ == 0)
{
v___x_3341_ = v___x_3338_;
goto v_reusejp_3340_;
}
else
{
lean_object* v_reuseFailAlloc_3342_; 
v_reuseFailAlloc_3342_ = lean_alloc_ctor(1, 1, 0);
lean_ctor_set(v_reuseFailAlloc_3342_, 0, v_a_3336_);
v___x_3341_ = v_reuseFailAlloc_3342_;
goto v_reusejp_3340_;
}
v_reusejp_3340_:
{
return v___x_3341_;
}
}
}
}
v___jp_3344_:
{
uint32_t v___x_3358_; uint8_t v___x_3359_; 
v___x_3358_ = 0;
v___x_3359_ = lean_uint32_dec_eq(v___y_3353_, v___x_3358_);
if (v___x_3359_ == 0)
{
uint8_t v___x_3360_; 
v___x_3360_ = lean_uint32_dec_eq(v___y_3353_, v___y_3354_);
if (v___x_3360_ == 0)
{
lean_dec_ref(v___y_3356_);
lean_dec_ref(v___y_3355_);
lean_dec_ref(v___y_3351_);
lean_dec(v___y_3350_);
lean_dec_ref(v___y_3349_);
lean_dec_ref(v___y_3348_);
lean_dec_ref(v___y_3347_);
lean_dec_ref(v___y_3346_);
lean_dec_ref(v___y_3345_);
lean_dec(v_fst_3137_);
v___y_3130_ = v___y_3352_;
goto v___jp_3129_;
}
else
{
v___y_3143_ = v___y_3345_;
v___y_3144_ = v___y_3346_;
v___y_3145_ = v___y_3351_;
v___y_3146_ = v___y_3352_;
v___y_3147_ = v___y_3347_;
v___y_3148_ = v___y_3348_;
v___y_3149_ = v___y_3353_;
v___y_3150_ = v___y_3354_;
v___y_3151_ = v___y_3349_;
v___y_3152_ = v___y_3355_;
v___y_3153_ = v___y_3357_;
v___y_3154_ = v___y_3356_;
v_unknown_3155_ = v___y_3350_;
goto v___jp_3142_;
}
}
else
{
v___y_3143_ = v___y_3345_;
v___y_3144_ = v___y_3346_;
v___y_3145_ = v___y_3351_;
v___y_3146_ = v___y_3352_;
v___y_3147_ = v___y_3347_;
v___y_3148_ = v___y_3348_;
v___y_3149_ = v___y_3353_;
v___y_3150_ = v___y_3354_;
v___y_3151_ = v___y_3349_;
v___y_3152_ = v___y_3355_;
v___y_3153_ = v___y_3357_;
v___y_3154_ = v___y_3356_;
v_unknown_3155_ = v___y_3350_;
goto v___jp_3142_;
}
}
v___jp_3361_:
{
uint8_t v___x_3376_; 
v___x_3376_ = lean_uint32_dec_eq(v___y_3374_, v___y_3371_);
if (v___x_3376_ == 0)
{
lean_dec_ref(v___y_3373_);
lean_dec_ref(v___y_3372_);
lean_dec_ref(v___y_3368_);
lean_dec(v___y_3367_);
lean_dec_ref(v___y_3366_);
lean_dec_ref(v___y_3365_);
lean_dec_ref(v___y_3364_);
lean_dec_ref(v___y_3363_);
lean_dec_ref(v___y_3362_);
lean_dec(v_fst_3137_);
v___y_3130_ = v___y_3369_;
goto v___jp_3129_;
}
else
{
if (v___y_3375_ == 0)
{
v___y_3345_ = v___y_3362_;
v___y_3346_ = v___y_3363_;
v___y_3347_ = v___y_3364_;
v___y_3348_ = v___y_3365_;
v___y_3349_ = v___y_3366_;
v___y_3350_ = v___y_3367_;
v___y_3351_ = v___y_3368_;
v___y_3352_ = v___y_3369_;
v___y_3353_ = v___y_3370_;
v___y_3354_ = v___y_3371_;
v___y_3355_ = v___y_3372_;
v___y_3356_ = v___y_3373_;
v___y_3357_ = v___y_3374_;
goto v___jp_3344_;
}
else
{
lean_dec_ref(v___y_3373_);
lean_dec_ref(v___y_3372_);
lean_dec_ref(v___y_3368_);
lean_dec(v___y_3367_);
lean_dec_ref(v___y_3366_);
lean_dec_ref(v___y_3365_);
lean_dec_ref(v___y_3364_);
lean_dec_ref(v___y_3363_);
lean_dec_ref(v___y_3362_);
lean_dec(v_fst_3137_);
v___y_3130_ = v___y_3369_;
goto v___jp_3129_;
}
}
}
v___jp_3378_:
{
lean_object* v_name_3379_; lean_object* v___x_3380_; lean_object* v___x_3381_; lean_object* v___x_3382_; lean_object* v___x_3383_; 
v_name_3379_ = lean_ctor_get(v_a_3377_, 0);
v___x_3380_ = ((lean_object*)(lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotCostHarness_verify_spec__1___closed__11));
lean_inc_ref(v_name_3379_);
v___x_3381_ = lean_string_append(v_name_3379_, v___x_3380_);
v___x_3382_ = lean_alloc_ctor(18, 1, 0);
lean_ctor_set(v___x_3382_, 0, v___x_3381_);
v___x_3383_ = lean_alloc_ctor(1, 1, 0);
lean_ctor_set(v___x_3383_, 0, v___x_3382_);
return v___x_3383_;
}
v___jp_3387_:
{
lean_object* v___x_3411_; 
v___x_3411_ = l_IO_lazyPure___redArg(v___y_3395_);
if (lean_obj_tag(v___x_3411_) == 0)
{
lean_object* v_a_3412_; lean_object* v___x_3413_; 
v_a_3412_ = lean_ctor_get(v___x_3411_, 0);
lean_inc(v_a_3412_);
lean_dec_ref_known(v___x_3411_, 1);
v___x_3413_ = l_IO_lazyPure___redArg(v___y_3400_);
if (lean_obj_tag(v___x_3413_) == 0)
{
lean_object* v_a_3414_; lean_object* v___x_3416_; uint8_t v_isShared_3417_; uint8_t v_isSharedCheck_3481_; 
v_a_3414_ = lean_ctor_get(v___x_3413_, 0);
v_isSharedCheck_3481_ = !lean_is_exclusive(v___x_3413_);
if (v_isSharedCheck_3481_ == 0)
{
v___x_3416_ = v___x_3413_;
v_isShared_3417_ = v_isSharedCheck_3481_;
goto v_resetjp_3415_;
}
else
{
lean_inc(v_a_3414_);
lean_dec(v___x_3413_);
v___x_3416_ = lean_box(0);
v_isShared_3417_ = v_isSharedCheck_3481_;
goto v_resetjp_3415_;
}
v_resetjp_3415_:
{
lean_object* v___x_3418_; lean_object* v___x_3419_; uint8_t v___x_3420_; lean_object* v___x_3421_; lean_object* v___x_3422_; lean_object* v___x_3423_; lean_object* v___x_3424_; lean_object* v___x_3425_; lean_object* v___x_3426_; lean_object* v___x_3427_; lean_object* v___f_3428_; lean_object* v___f_3429_; 
v___x_3418_ = lean_array_get_size(v_raw_3397_);
lean_dec_ref(v_raw_3397_);
v___x_3419_ = lean_array_get_size(v_raw_3406_);
lean_dec_ref(v_raw_3406_);
v___x_3420_ = lean_nat_dec_eq(v___x_3418_, v___x_3419_);
v___x_3421_ = lean_alloc_ctor(0, 2, 9);
lean_ctor_set(v___x_3421_, 0, v___y_3396_);
lean_ctor_set(v___x_3421_, 1, v___y_3405_);
lean_ctor_set_uint32(v___x_3421_, sizeof(void*)*2, v___y_3392_);
lean_ctor_set_uint32(v___x_3421_, sizeof(void*)*2 + 4, v___y_3410_);
lean_ctor_set_uint8(v___x_3421_, sizeof(void*)*2 + 8, v___x_3420_);
v___x_3422_ = lean_box(v___x_3420_);
v___x_3423_ = lean_box(v_normal_3399_);
v___x_3424_ = lean_box(v_normal_3408_);
v___x_3425_ = lean_box_uint32(v___y_3392_);
v___x_3426_ = lean_box_uint32(v___y_3410_);
v___x_3427_ = lean_box(v___y_3409_);
lean_inc_ref(v___x_3421_);
v___f_3428_ = lean_alloc_closure((void*)(lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotCostHarness_verify_spec__1___lam__0___boxed), 11, 10);
lean_closure_set(v___f_3428_, 0, v___x_3422_);
lean_closure_set(v___f_3428_, 1, v___x_3421_);
lean_closure_set(v___f_3428_, 2, v___x_3423_);
lean_closure_set(v___f_3428_, 3, v___x_3424_);
lean_closure_set(v___f_3428_, 4, v_data_3398_);
lean_closure_set(v___f_3428_, 5, v_data_3407_);
lean_closure_set(v___f_3428_, 6, v___x_3425_);
lean_closure_set(v___f_3428_, 7, v_accepts_3386_);
lean_closure_set(v___f_3428_, 8, v___x_3426_);
lean_closure_set(v___f_3428_, 9, v___x_3427_);
v___f_3429_ = lean_alloc_closure((void*)(lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotCostHarness_verify_spec__1___lam__1___boxed), 2, 1);
lean_closure_set(v___f_3429_, 0, v___x_3421_);
if (lean_obj_tag(v___y_3403_) == 0)
{
lean_object* v___x_3430_; lean_object* v___x_3431_; uint32_t v___x_3432_; uint32_t v___x_3433_; uint8_t v___x_3434_; 
lean_del_object(v___x_3416_);
v___x_3430_ = lean_unsigned_to_nat(1u);
v___x_3431_ = lean_nat_add(v_snd_3138_, v___x_3430_);
lean_dec(v_snd_3138_);
v___x_3432_ = 0;
v___x_3433_ = lean_unbox_uint32(v_a_3412_);
v___x_3434_ = lean_uint32_dec_eq(v___x_3433_, v___x_3432_);
if (v___x_3434_ == 0)
{
uint32_t v___x_3435_; uint32_t v___x_3436_; 
v___x_3435_ = lean_unbox_uint32(v_a_3414_);
lean_dec(v_a_3414_);
v___x_3436_ = lean_unbox_uint32(v_a_3412_);
lean_dec(v_a_3412_);
v___y_3362_ = v___y_3393_;
v___y_3363_ = v___y_3389_;
v___y_3364_ = v___f_3429_;
v___y_3365_ = v___y_3404_;
v___y_3366_ = v___y_3394_;
v___y_3367_ = v___x_3431_;
v___y_3368_ = v___y_3390_;
v___y_3369_ = v___y_3388_;
v___y_3370_ = v___x_3435_;
v___y_3371_ = v___y_3391_;
v___y_3372_ = v___y_3402_;
v___y_3373_ = v___f_3428_;
v___y_3374_ = v___x_3436_;
v___y_3375_ = v___y_3401_;
goto v___jp_3361_;
}
else
{
if (v___y_3401_ == 0)
{
uint32_t v___x_3437_; uint32_t v___x_3438_; 
v___x_3437_ = lean_unbox_uint32(v_a_3414_);
lean_dec(v_a_3414_);
v___x_3438_ = lean_unbox_uint32(v_a_3412_);
lean_dec(v_a_3412_);
v___y_3345_ = v___y_3393_;
v___y_3346_ = v___y_3389_;
v___y_3347_ = v___f_3429_;
v___y_3348_ = v___y_3404_;
v___y_3349_ = v___y_3394_;
v___y_3350_ = v___x_3431_;
v___y_3351_ = v___y_3390_;
v___y_3352_ = v___y_3388_;
v___y_3353_ = v___x_3437_;
v___y_3354_ = v___y_3391_;
v___y_3355_ = v___y_3402_;
v___y_3356_ = v___f_3428_;
v___y_3357_ = v___x_3438_;
goto v___jp_3344_;
}
else
{
uint32_t v___x_3439_; uint32_t v___x_3440_; 
v___x_3439_ = lean_unbox_uint32(v_a_3414_);
lean_dec(v_a_3414_);
v___x_3440_ = lean_unbox_uint32(v_a_3412_);
lean_dec(v_a_3412_);
v___y_3362_ = v___y_3393_;
v___y_3363_ = v___y_3389_;
v___y_3364_ = v___f_3429_;
v___y_3365_ = v___y_3404_;
v___y_3366_ = v___y_3394_;
v___y_3367_ = v___x_3431_;
v___y_3368_ = v___y_3390_;
v___y_3369_ = v___y_3388_;
v___y_3370_ = v___x_3439_;
v___y_3371_ = v___y_3391_;
v___y_3372_ = v___y_3402_;
v___y_3373_ = v___f_3428_;
v___y_3374_ = v___x_3440_;
v___y_3375_ = v___y_3401_;
goto v___jp_3361_;
}
}
}
else
{
lean_object* v_val_3441_; lean_object* v___x_3443_; uint8_t v_isShared_3444_; uint8_t v_isSharedCheck_3480_; 
v_val_3441_ = lean_ctor_get(v___y_3403_, 0);
v_isSharedCheck_3480_ = !lean_is_exclusive(v___y_3403_);
if (v_isSharedCheck_3480_ == 0)
{
v___x_3443_ = v___y_3403_;
v_isShared_3444_ = v_isSharedCheck_3480_;
goto v_resetjp_3442_;
}
else
{
lean_inc(v_val_3441_);
lean_dec(v___y_3403_);
v___x_3443_ = lean_box(0);
v_isShared_3444_ = v_isSharedCheck_3480_;
goto v_resetjp_3442_;
}
v_resetjp_3442_:
{
lean_object* v___x_3445_; uint8_t v___x_3446_; 
v___x_3445_ = lean_unsigned_to_nat(4294967295u);
v___x_3446_ = lean_nat_dec_lt(v___x_3445_, v_val_3441_);
if (v___x_3446_ == 0)
{
lean_object* v___x_3447_; uint32_t v___x_3448_; uint32_t v___x_3449_; lean_object* v___x_3450_; 
lean_del_object(v___x_3443_);
lean_del_object(v___x_3416_);
v___x_3447_ = ((lean_object*)(lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotCostHarness_verify_spec__1___closed__12));
v___x_3448_ = lean_uint32_of_nat(v_val_3441_);
lean_dec(v_val_3441_);
v___x_3449_ = lean_unbox_uint32(v_a_3412_);
lean_inc_ref(v___y_3388_);
v___x_3450_ = lp_competition_R24DotCostHarness_checkWord(v___y_3388_, v___x_3447_, v___x_3449_, v___x_3448_);
if (lean_obj_tag(v___x_3450_) == 0)
{
lean_object* v___x_3451_; uint32_t v___x_3452_; lean_object* v___x_3453_; 
lean_dec_ref_known(v___x_3450_, 1);
v___x_3451_ = ((lean_object*)(lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotCostHarness_verify_spec__1___closed__13));
v___x_3452_ = lean_unbox_uint32(v_a_3414_);
lean_inc_ref(v___y_3388_);
v___x_3453_ = lp_competition_R24DotCostHarness_checkWord(v___y_3388_, v___x_3451_, v___x_3452_, v___x_3448_);
if (lean_obj_tag(v___x_3453_) == 0)
{
uint32_t v___x_3454_; uint32_t v___x_3455_; 
lean_dec_ref_known(v___x_3453_, 1);
v___x_3454_ = lean_unbox_uint32(v_a_3414_);
lean_dec(v_a_3414_);
v___x_3455_ = lean_unbox_uint32(v_a_3412_);
lean_dec(v_a_3412_);
v___y_3143_ = v___y_3393_;
v___y_3144_ = v___y_3389_;
v___y_3145_ = v___y_3390_;
v___y_3146_ = v___y_3388_;
v___y_3147_ = v___f_3429_;
v___y_3148_ = v___y_3404_;
v___y_3149_ = v___x_3454_;
v___y_3150_ = v___y_3391_;
v___y_3151_ = v___y_3394_;
v___y_3152_ = v___y_3402_;
v___y_3153_ = v___x_3455_;
v___y_3154_ = v___f_3428_;
v_unknown_3155_ = v_snd_3138_;
goto v___jp_3142_;
}
else
{
lean_object* v_a_3456_; lean_object* v___x_3458_; uint8_t v_isShared_3459_; uint8_t v_isSharedCheck_3463_; 
lean_dec_ref(v___f_3429_);
lean_dec_ref(v___f_3428_);
lean_dec(v_a_3414_);
lean_dec(v_a_3412_);
lean_dec_ref(v___y_3404_);
lean_dec_ref(v___y_3402_);
lean_dec_ref(v___y_3394_);
lean_dec_ref(v___y_3393_);
lean_dec_ref(v___y_3390_);
lean_dec_ref(v___y_3389_);
lean_dec_ref(v___y_3388_);
lean_dec(v_snd_3138_);
lean_dec(v_fst_3137_);
v_a_3456_ = lean_ctor_get(v___x_3453_, 0);
v_isSharedCheck_3463_ = !lean_is_exclusive(v___x_3453_);
if (v_isSharedCheck_3463_ == 0)
{
v___x_3458_ = v___x_3453_;
v_isShared_3459_ = v_isSharedCheck_3463_;
goto v_resetjp_3457_;
}
else
{
lean_inc(v_a_3456_);
lean_dec(v___x_3453_);
v___x_3458_ = lean_box(0);
v_isShared_3459_ = v_isSharedCheck_3463_;
goto v_resetjp_3457_;
}
v_resetjp_3457_:
{
lean_object* v___x_3461_; 
if (v_isShared_3459_ == 0)
{
v___x_3461_ = v___x_3458_;
goto v_reusejp_3460_;
}
else
{
lean_object* v_reuseFailAlloc_3462_; 
v_reuseFailAlloc_3462_ = lean_alloc_ctor(1, 1, 0);
lean_ctor_set(v_reuseFailAlloc_3462_, 0, v_a_3456_);
v___x_3461_ = v_reuseFailAlloc_3462_;
goto v_reusejp_3460_;
}
v_reusejp_3460_:
{
return v___x_3461_;
}
}
}
}
else
{
lean_object* v_a_3464_; lean_object* v___x_3466_; uint8_t v_isShared_3467_; uint8_t v_isSharedCheck_3471_; 
lean_dec_ref(v___f_3429_);
lean_dec_ref(v___f_3428_);
lean_dec(v_a_3414_);
lean_dec(v_a_3412_);
lean_dec_ref(v___y_3404_);
lean_dec_ref(v___y_3402_);
lean_dec_ref(v___y_3394_);
lean_dec_ref(v___y_3393_);
lean_dec_ref(v___y_3390_);
lean_dec_ref(v___y_3389_);
lean_dec_ref(v___y_3388_);
lean_dec(v_snd_3138_);
lean_dec(v_fst_3137_);
v_a_3464_ = lean_ctor_get(v___x_3450_, 0);
v_isSharedCheck_3471_ = !lean_is_exclusive(v___x_3450_);
if (v_isSharedCheck_3471_ == 0)
{
v___x_3466_ = v___x_3450_;
v_isShared_3467_ = v_isSharedCheck_3471_;
goto v_resetjp_3465_;
}
else
{
lean_inc(v_a_3464_);
lean_dec(v___x_3450_);
v___x_3466_ = lean_box(0);
v_isShared_3467_ = v_isSharedCheck_3471_;
goto v_resetjp_3465_;
}
v_resetjp_3465_:
{
lean_object* v___x_3469_; 
if (v_isShared_3467_ == 0)
{
v___x_3469_ = v___x_3466_;
goto v_reusejp_3468_;
}
else
{
lean_object* v_reuseFailAlloc_3470_; 
v_reuseFailAlloc_3470_ = lean_alloc_ctor(1, 1, 0);
lean_ctor_set(v_reuseFailAlloc_3470_, 0, v_a_3464_);
v___x_3469_ = v_reuseFailAlloc_3470_;
goto v_reusejp_3468_;
}
v_reusejp_3468_:
{
return v___x_3469_;
}
}
}
}
else
{
lean_object* v___x_3472_; lean_object* v___x_3473_; lean_object* v___x_3475_; 
lean_dec(v_val_3441_);
lean_dec_ref(v___f_3429_);
lean_dec_ref(v___f_3428_);
lean_dec(v_a_3414_);
lean_dec(v_a_3412_);
lean_dec_ref(v___y_3404_);
lean_dec_ref(v___y_3402_);
lean_dec_ref(v___y_3394_);
lean_dec_ref(v___y_3393_);
lean_dec_ref(v___y_3390_);
lean_dec_ref(v___y_3389_);
lean_dec(v_snd_3138_);
lean_dec(v_fst_3137_);
v___x_3472_ = ((lean_object*)(lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotCostHarness_verify_spec__1___closed__14));
v___x_3473_ = lean_string_append(v___y_3388_, v___x_3472_);
if (v_isShared_3444_ == 0)
{
lean_ctor_set_tag(v___x_3443_, 18);
lean_ctor_set(v___x_3443_, 0, v___x_3473_);
v___x_3475_ = v___x_3443_;
goto v_reusejp_3474_;
}
else
{
lean_object* v_reuseFailAlloc_3479_; 
v_reuseFailAlloc_3479_ = lean_alloc_ctor(18, 1, 0);
lean_ctor_set(v_reuseFailAlloc_3479_, 0, v___x_3473_);
v___x_3475_ = v_reuseFailAlloc_3479_;
goto v_reusejp_3474_;
}
v_reusejp_3474_:
{
lean_object* v___x_3477_; 
if (v_isShared_3417_ == 0)
{
lean_ctor_set_tag(v___x_3416_, 1);
lean_ctor_set(v___x_3416_, 0, v___x_3475_);
v___x_3477_ = v___x_3416_;
goto v_reusejp_3476_;
}
else
{
lean_object* v_reuseFailAlloc_3478_; 
v_reuseFailAlloc_3478_ = lean_alloc_ctor(1, 1, 0);
lean_ctor_set(v_reuseFailAlloc_3478_, 0, v___x_3475_);
v___x_3477_ = v_reuseFailAlloc_3478_;
goto v_reusejp_3476_;
}
v_reusejp_3476_:
{
return v___x_3477_;
}
}
}
}
}
}
}
else
{
lean_object* v_a_3482_; lean_object* v___x_3484_; uint8_t v_isShared_3485_; uint8_t v_isSharedCheck_3489_; 
lean_dec(v_a_3412_);
lean_dec_ref(v_data_3407_);
lean_dec_ref(v_raw_3406_);
lean_dec_ref(v___y_3405_);
lean_dec_ref(v___y_3404_);
lean_dec(v___y_3403_);
lean_dec_ref(v___y_3402_);
lean_dec_ref(v_data_3398_);
lean_dec_ref(v_raw_3397_);
lean_dec_ref(v___y_3396_);
lean_dec_ref(v___y_3394_);
lean_dec_ref(v___y_3393_);
lean_dec_ref(v___y_3390_);
lean_dec_ref(v___y_3389_);
lean_dec_ref(v___y_3388_);
lean_dec(v_snd_3138_);
lean_dec(v_fst_3137_);
v_a_3482_ = lean_ctor_get(v___x_3413_, 0);
v_isSharedCheck_3489_ = !lean_is_exclusive(v___x_3413_);
if (v_isSharedCheck_3489_ == 0)
{
v___x_3484_ = v___x_3413_;
v_isShared_3485_ = v_isSharedCheck_3489_;
goto v_resetjp_3483_;
}
else
{
lean_inc(v_a_3482_);
lean_dec(v___x_3413_);
v___x_3484_ = lean_box(0);
v_isShared_3485_ = v_isSharedCheck_3489_;
goto v_resetjp_3483_;
}
v_resetjp_3483_:
{
lean_object* v___x_3487_; 
if (v_isShared_3485_ == 0)
{
v___x_3487_ = v___x_3484_;
goto v_reusejp_3486_;
}
else
{
lean_object* v_reuseFailAlloc_3488_; 
v_reuseFailAlloc_3488_ = lean_alloc_ctor(1, 1, 0);
lean_ctor_set(v_reuseFailAlloc_3488_, 0, v_a_3482_);
v___x_3487_ = v_reuseFailAlloc_3488_;
goto v_reusejp_3486_;
}
v_reusejp_3486_:
{
return v___x_3487_;
}
}
}
}
else
{
lean_object* v_a_3490_; lean_object* v___x_3492_; uint8_t v_isShared_3493_; uint8_t v_isSharedCheck_3497_; 
lean_dec_ref(v_data_3407_);
lean_dec_ref(v_raw_3406_);
lean_dec_ref(v___y_3405_);
lean_dec_ref(v___y_3404_);
lean_dec(v___y_3403_);
lean_dec_ref(v___y_3402_);
lean_dec_ref(v___y_3400_);
lean_dec_ref(v_data_3398_);
lean_dec_ref(v_raw_3397_);
lean_dec_ref(v___y_3396_);
lean_dec_ref(v___y_3394_);
lean_dec_ref(v___y_3393_);
lean_dec_ref(v___y_3390_);
lean_dec_ref(v___y_3389_);
lean_dec_ref(v___y_3388_);
lean_dec(v_snd_3138_);
lean_dec(v_fst_3137_);
v_a_3490_ = lean_ctor_get(v___x_3411_, 0);
v_isSharedCheck_3497_ = !lean_is_exclusive(v___x_3411_);
if (v_isSharedCheck_3497_ == 0)
{
v___x_3492_ = v___x_3411_;
v_isShared_3493_ = v_isSharedCheck_3497_;
goto v_resetjp_3491_;
}
else
{
lean_inc(v_a_3490_);
lean_dec(v___x_3411_);
v___x_3492_ = lean_box(0);
v_isShared_3493_ = v_isSharedCheck_3497_;
goto v_resetjp_3491_;
}
v_resetjp_3491_:
{
lean_object* v___x_3495_; 
if (v_isShared_3493_ == 0)
{
v___x_3495_ = v___x_3492_;
goto v_reusejp_3494_;
}
else
{
lean_object* v_reuseFailAlloc_3496_; 
v_reuseFailAlloc_3496_ = lean_alloc_ctor(1, 1, 0);
lean_ctor_set(v_reuseFailAlloc_3496_, 0, v_a_3490_);
v___x_3495_ = v_reuseFailAlloc_3496_;
goto v_reusejp_3494_;
}
v_reusejp_3494_:
{
return v___x_3495_;
}
}
}
}
v___jp_3498_:
{
uint32_t v___x_3514_; lean_object* v_raw_3515_; lean_object* v_data_3516_; uint8_t v_normal_3517_; lean_object* v_raw_3518_; lean_object* v_data_3519_; uint8_t v_normal_3520_; 
v___x_3514_ = 0;
v_raw_3515_ = lean_ctor_get(v___y_3511_, 0);
lean_inc_ref(v_raw_3515_);
v_data_3516_ = lean_ctor_get(v___y_3511_, 1);
lean_inc_ref(v_data_3516_);
v_normal_3517_ = lean_ctor_get_uint8(v___y_3511_, sizeof(void*)*2 + 8);
v_raw_3518_ = lean_ctor_get(v___y_3499_, 0);
lean_inc_ref(v_raw_3518_);
v_data_3519_ = lean_ctor_get(v___y_3499_, 1);
lean_inc_ref(v_data_3519_);
v_normal_3520_ = lean_ctor_get_uint8(v___y_3499_, sizeof(void*)*2 + 8);
v___y_3388_ = v___y_3509_;
v___y_3389_ = v___y_3502_;
v___y_3390_ = v___y_3507_;
v___y_3391_ = v___y_3510_;
v___y_3392_ = v___x_3514_;
v___y_3393_ = v___y_3501_;
v___y_3394_ = v___y_3506_;
v___y_3395_ = v___y_3504_;
v___y_3396_ = v___y_3511_;
v_raw_3397_ = v_raw_3515_;
v_data_3398_ = v_data_3516_;
v_normal_3399_ = v_normal_3517_;
v___y_3400_ = v___y_3503_;
v___y_3401_ = v___y_3513_;
v___y_3402_ = v___y_3512_;
v___y_3403_ = v___y_3508_;
v___y_3404_ = v___y_3505_;
v___y_3405_ = v___y_3499_;
v_raw_3406_ = v_raw_3518_;
v_data_3407_ = v_data_3519_;
v_normal_3408_ = v_normal_3520_;
v___y_3409_ = v___y_3500_;
v___y_3410_ = v___x_3514_;
goto v___jp_3387_;
}
v___jp_3521_:
{
lean_object* v_name_3523_; lean_object* v_x_3524_; lean_object* v_y_3525_; lean_object* v_expected_3526_; lean_object* v_fast__result_3527_; lean_object* v___x_3528_; lean_object* v___x_3529_; uint8_t v_hasNonzero_3530_; lean_object* v___x_3531_; lean_object* v___x_3532_; lean_object* v___f_3533_; lean_object* v___f_3534_; lean_object* v___f_3535_; lean_object* v___f_3536_; uint32_t v___x_3537_; lean_object* v___f_3538_; lean_object* v___x_3539_; lean_object* v___x_3540_; lean_object* v___f_3541_; lean_object* v___f_3542_; lean_object* v___x_3544_; 
v_name_3523_ = lean_ctor_get(v_a_3377_, 0);
v_x_3524_ = lean_ctor_get(v_a_3377_, 3);
v_y_3525_ = lean_ctor_get(v_a_3377_, 4);
v_expected_3526_ = lean_ctor_get(v_a_3377_, 5);
v_fast__result_3527_ = lean_ctor_get(v_a_3377_, 6);
lean_inc_ref(v_x_3524_);
v___x_3528_ = lp_competition_R24DotCostHarness_words(v_x_3524_);
lean_inc_ref_n(v___x_3528_, 5);
v___x_3529_ = lp_competition_Submission_R24ExactDotCost_prepareOperand(v___x_3528_);
v_hasNonzero_3530_ = lean_ctor_get_uint8(v___x_3529_, sizeof(void*)*2 + 10);
lean_inc_ref(v_y_3525_);
v___x_3531_ = lp_competition_R24DotCostHarness_words(v_y_3525_);
lean_inc_ref_n(v___x_3531_, 5);
v___x_3532_ = lp_competition_Submission_R24ExactDotCost_prepareOperand(v___x_3531_);
v___f_3533_ = lean_alloc_closure((void*)(lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotCostHarness_verify_spec__1___lam__2___boxed), 3, 2);
lean_closure_set(v___f_3533_, 0, v___x_3528_);
lean_closure_set(v___f_3533_, 1, v___x_3531_);
v___f_3534_ = lean_alloc_closure((void*)(lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotCostHarness_verify_spec__1___lam__3___boxed), 3, 2);
lean_closure_set(v___f_3534_, 0, v___x_3528_);
lean_closure_set(v___f_3534_, 1, v___x_3531_);
v___f_3535_ = lean_alloc_closure((void*)(lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotCostHarness_verify_spec__1___lam__4___boxed), 3, 2);
lean_closure_set(v___f_3535_, 0, v___x_3528_);
lean_closure_set(v___f_3535_, 1, v___x_3531_);
v___f_3536_ = lean_alloc_closure((void*)(lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotCostHarness_verify_spec__1___lam__5___boxed), 3, 2);
lean_closure_set(v___f_3536_, 0, v___x_3528_);
lean_closure_set(v___f_3536_, 1, v___x_3531_);
v___x_3537_ = lean_uint32_of_nat(v_expected_3526_);
lean_inc_ref(v___x_3532_);
lean_inc_ref_n(v___x_3529_, 2);
v___f_3538_ = lean_alloc_closure((void*)(lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotCostHarness_verify_spec__1___lam__6___boxed), 3, 2);
lean_closure_set(v___f_3538_, 0, v___x_3529_);
lean_closure_set(v___f_3538_, 1, v___x_3532_);
v___x_3539_ = lp_competition_Submission_R24PortableF64_prepare(v___x_3528_);
v___x_3540_ = lp_competition_Submission_R24PortableF64_prepare(v___x_3531_);
lean_inc_ref_n(v___x_3540_, 2);
lean_inc_ref_n(v___x_3539_, 2);
v___f_3541_ = lean_alloc_closure((void*)(lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotCostHarness_verify_spec__1___lam__7___boxed), 3, 2);
lean_closure_set(v___f_3541_, 0, v___x_3539_);
lean_closure_set(v___f_3541_, 1, v___x_3540_);
v___f_3542_ = lean_alloc_closure((void*)(lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotCostHarness_verify_spec__1___lam__8___boxed), 3, 2);
lean_closure_set(v___f_3542_, 0, v___x_3539_);
lean_closure_set(v___f_3542_, 1, v___x_3540_);
if (v_isShared_3141_ == 0)
{
lean_ctor_set(v___x_3140_, 1, v___x_3539_);
lean_ctor_set(v___x_3140_, 0, v___x_3529_);
v___x_3544_ = v___x_3140_;
goto v_reusejp_3543_;
}
else
{
lean_object* v_reuseFailAlloc_3560_; 
v_reuseFailAlloc_3560_ = lean_alloc_ctor(0, 2, 0);
lean_ctor_set(v_reuseFailAlloc_3560_, 0, v___x_3529_);
lean_ctor_set(v_reuseFailAlloc_3560_, 1, v___x_3539_);
v___x_3544_ = v_reuseFailAlloc_3560_;
goto v_reusejp_3543_;
}
v_reusejp_3543_:
{
lean_object* v___x_3545_; lean_object* v___f_3546_; 
lean_inc_ref(v___x_3532_);
v___x_3545_ = lean_alloc_ctor(0, 2, 0);
lean_ctor_set(v___x_3545_, 0, v___x_3532_);
lean_ctor_set(v___x_3545_, 1, v___x_3540_);
v___f_3546_ = lean_alloc_closure((void*)(lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotCostHarness_verify_spec__1___lam__9___boxed), 3, 2);
lean_closure_set(v___f_3546_, 0, v___x_3544_);
lean_closure_set(v___f_3546_, 1, v___x_3545_);
if (v_hasNonzero_3530_ == 0)
{
lean_inc_ref(v_name_3523_);
lean_inc(v_fast__result_3527_);
v___y_3499_ = v___x_3532_;
v___y_3500_ = v___y_3522_;
v___y_3501_ = v___f_3535_;
v___y_3502_ = v___f_3538_;
v___y_3503_ = v___f_3541_;
v___y_3504_ = v___f_3533_;
v___y_3505_ = v___f_3542_;
v___y_3506_ = v___f_3534_;
v___y_3507_ = v___f_3536_;
v___y_3508_ = v_fast__result_3527_;
v___y_3509_ = v_name_3523_;
v___y_3510_ = v___x_3537_;
v___y_3511_ = v___x_3529_;
v___y_3512_ = v___f_3546_;
v___y_3513_ = v___y_3522_;
goto v___jp_3498_;
}
else
{
uint8_t v_hasNonzero_3547_; 
v_hasNonzero_3547_ = lean_ctor_get_uint8(v___x_3532_, sizeof(void*)*2 + 10);
if (v_hasNonzero_3547_ == 0)
{
lean_inc_ref(v_name_3523_);
lean_inc(v_fast__result_3527_);
v___y_3499_ = v___x_3532_;
v___y_3500_ = v___y_3522_;
v___y_3501_ = v___f_3535_;
v___y_3502_ = v___f_3538_;
v___y_3503_ = v___f_3541_;
v___y_3504_ = v___f_3533_;
v___y_3505_ = v___f_3542_;
v___y_3506_ = v___f_3534_;
v___y_3507_ = v___f_3536_;
v___y_3508_ = v_fast__result_3527_;
v___y_3509_ = v_name_3523_;
v___y_3510_ = v___x_3537_;
v___y_3511_ = v___x_3529_;
v___y_3512_ = v___f_3546_;
v___y_3513_ = v___y_3522_;
goto v___jp_3498_;
}
else
{
uint32_t v_minIdx_3548_; uint32_t v_minIdx_3549_; uint32_t v___x_3550_; lean_object* v_raw_3551_; lean_object* v_data_3552_; uint32_t v_maxIdx_3553_; uint8_t v_normal_3554_; lean_object* v_raw_3555_; lean_object* v_data_3556_; uint32_t v_maxIdx_3557_; uint8_t v_normal_3558_; uint32_t v___x_3559_; 
v_minIdx_3548_ = lean_ctor_get_uint32(v___x_3529_, sizeof(void*)*2);
v_minIdx_3549_ = lean_ctor_get_uint32(v___x_3532_, sizeof(void*)*2);
v___x_3550_ = lean_uint32_add(v_minIdx_3548_, v_minIdx_3549_);
v_raw_3551_ = lean_ctor_get(v___x_3529_, 0);
lean_inc_ref(v_raw_3551_);
v_data_3552_ = lean_ctor_get(v___x_3529_, 1);
lean_inc_ref(v_data_3552_);
v_maxIdx_3553_ = lean_ctor_get_uint32(v___x_3529_, sizeof(void*)*2 + 4);
v_normal_3554_ = lean_ctor_get_uint8(v___x_3529_, sizeof(void*)*2 + 8);
v_raw_3555_ = lean_ctor_get(v___x_3532_, 0);
lean_inc_ref(v_raw_3555_);
v_data_3556_ = lean_ctor_get(v___x_3532_, 1);
lean_inc_ref(v_data_3556_);
v_maxIdx_3557_ = lean_ctor_get_uint32(v___x_3532_, sizeof(void*)*2 + 4);
v_normal_3558_ = lean_ctor_get_uint8(v___x_3532_, sizeof(void*)*2 + 8);
v___x_3559_ = lean_uint32_add(v_maxIdx_3553_, v_maxIdx_3557_);
lean_inc(v_fast__result_3527_);
lean_inc_ref(v_name_3523_);
v___y_3388_ = v_name_3523_;
v___y_3389_ = v___f_3538_;
v___y_3390_ = v___f_3536_;
v___y_3391_ = v___x_3537_;
v___y_3392_ = v___x_3550_;
v___y_3393_ = v___f_3535_;
v___y_3394_ = v___f_3534_;
v___y_3395_ = v___f_3533_;
v___y_3396_ = v___x_3529_;
v_raw_3397_ = v_raw_3551_;
v_data_3398_ = v_data_3552_;
v_normal_3399_ = v_normal_3554_;
v___y_3400_ = v___f_3541_;
v___y_3401_ = v___y_3522_;
v___y_3402_ = v___f_3546_;
v___y_3403_ = v_fast__result_3527_;
v___y_3404_ = v___f_3542_;
v___y_3405_ = v___x_3532_;
v_raw_3406_ = v_raw_3555_;
v_data_3407_ = v_data_3556_;
v_normal_3408_ = v_normal_3558_;
v___y_3409_ = v___y_3522_;
v___y_3410_ = v___x_3559_;
goto v___jp_3387_;
}
}
}
}
v___jp_3561_:
{
if (v___y_3562_ == 0)
{
lean_object* v_y_3563_; lean_object* v___x_3564_; uint8_t v___x_3565_; 
v_y_3563_ = lean_ctor_get(v_a_3377_, 4);
v___x_3564_ = lean_array_get_size(v_y_3563_);
v___x_3565_ = lean_nat_dec_lt(v_accepts_3386_, v___x_3564_);
if (v___x_3565_ == 0)
{
v___y_3522_ = v___y_3562_;
goto v___jp_3521_;
}
else
{
if (v___x_3565_ == 0)
{
v___y_3522_ = v___y_3562_;
goto v___jp_3521_;
}
else
{
size_t v___x_3566_; size_t v___x_3567_; uint8_t v___x_3568_; 
v___x_3566_ = ((size_t)0ULL);
v___x_3567_ = lean_usize_of_nat(v___x_3564_);
v___x_3568_ = lp_competition___private_Init_Data_Array_Basic_0__Array_anyMUnsafe_any___at___00R24DotCostHarness_verify_spec__0(v_y_3563_, v___x_3566_, v___x_3567_);
if (v___x_3568_ == 0)
{
v___y_3522_ = v___x_3568_;
goto v___jp_3521_;
}
else
{
lean_del_object(v___x_3140_);
lean_dec(v_snd_3138_);
lean_dec(v_fst_3137_);
goto v___jp_3378_;
}
}
}
}
else
{
lean_del_object(v___x_3140_);
lean_dec(v_snd_3138_);
lean_dec(v_fst_3137_);
goto v___jp_3378_;
}
}
}
}
v___jp_3052_:
{
lean_object* v___x_3067_; lean_object* v___x_3068_; lean_object* v___x_3069_; lean_object* v___x_3070_; lean_object* v___x_3071_; lean_object* v___x_3072_; lean_object* v___x_3073_; lean_object* v___x_3074_; lean_object* v___x_3075_; lean_object* v___x_3076_; lean_object* v___x_3077_; lean_object* v___x_3078_; lean_object* v___x_3079_; lean_object* v___x_3080_; lean_object* v___x_3081_; lean_object* v___x_3082_; lean_object* v___x_3083_; lean_object* v___x_3084_; lean_object* v___x_3085_; lean_object* v___x_3086_; lean_object* v___x_3087_; lean_object* v___x_3088_; lean_object* v___x_3089_; lean_object* v___x_3090_; lean_object* v___x_3091_; lean_object* v___x_3092_; lean_object* v___x_3093_; lean_object* v___x_3094_; lean_object* v___x_3095_; lean_object* v___x_3096_; lean_object* v___x_3097_; lean_object* v___x_3098_; lean_object* v___x_3099_; lean_object* v___x_3100_; lean_object* v___x_3101_; lean_object* v___x_3102_; lean_object* v___x_3103_; lean_object* v___x_3104_; lean_object* v___x_3105_; lean_object* v___x_3106_; lean_object* v___x_3107_; lean_object* v___x_3108_; lean_object* v___x_3109_; lean_object* v___x_3110_; lean_object* v___x_3111_; lean_object* v___x_3112_; lean_object* v___x_3113_; lean_object* v___x_3114_; lean_object* v___x_3115_; lean_object* v___x_3116_; 
v___x_3067_ = ((lean_object*)(lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotCostHarness_verify_spec__1___closed__0));
v___x_3068_ = lean_string_append(v___x_3067_, v___y_3056_);
lean_dec_ref(v___y_3056_);
v___x_3069_ = ((lean_object*)(lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotCostHarness_emit_spec__0___closed__1));
v___x_3070_ = lean_string_append(v___x_3068_, v___x_3069_);
v___x_3071_ = lean_uint32_to_nat(v___y_3061_);
v___x_3072_ = l_Nat_reprFast(v___x_3071_);
v___x_3073_ = lean_string_append(v___x_3070_, v___x_3072_);
lean_dec_ref(v___x_3072_);
v___x_3074_ = lean_string_append(v___x_3073_, v___x_3069_);
v___x_3075_ = lean_uint32_to_nat(v___y_3063_);
v___x_3076_ = l_Nat_reprFast(v___x_3075_);
v___x_3077_ = lean_string_append(v___x_3074_, v___x_3076_);
lean_dec_ref(v___x_3076_);
v___x_3078_ = lean_string_append(v___x_3077_, v___x_3069_);
v___x_3079_ = lean_uint32_to_nat(v___y_3058_);
v___x_3080_ = l_Nat_reprFast(v___x_3079_);
v___x_3081_ = lean_string_append(v___x_3078_, v___x_3080_);
lean_dec_ref(v___x_3080_);
v___x_3082_ = lean_string_append(v___x_3081_, v___x_3069_);
v___x_3083_ = lean_uint32_to_nat(v___y_3055_);
v___x_3084_ = l_Nat_reprFast(v___x_3083_);
v___x_3085_ = lean_string_append(v___x_3082_, v___x_3084_);
lean_dec_ref(v___x_3084_);
v___x_3086_ = lean_string_append(v___x_3085_, v___x_3069_);
v___x_3087_ = lean_uint32_to_nat(v___y_3064_);
v___x_3088_ = l_Nat_reprFast(v___x_3087_);
v___x_3089_ = lean_string_append(v___x_3086_, v___x_3088_);
lean_dec_ref(v___x_3088_);
v___x_3090_ = lean_string_append(v___x_3089_, v___x_3069_);
v___x_3091_ = lean_uint32_to_nat(v___y_3062_);
v___x_3092_ = l_Nat_reprFast(v___x_3091_);
v___x_3093_ = lean_string_append(v___x_3090_, v___x_3092_);
lean_dec_ref(v___x_3092_);
v___x_3094_ = lean_string_append(v___x_3093_, v___x_3069_);
v___x_3095_ = lean_uint32_to_nat(v___y_3059_);
v___x_3096_ = l_Nat_reprFast(v___x_3095_);
v___x_3097_ = lean_string_append(v___x_3094_, v___x_3096_);
lean_dec_ref(v___x_3096_);
v___x_3098_ = lean_string_append(v___x_3097_, v___x_3069_);
v___x_3099_ = lean_uint32_to_nat(v___y_3065_);
v___x_3100_ = l_Nat_reprFast(v___x_3099_);
v___x_3101_ = lean_string_append(v___x_3098_, v___x_3100_);
lean_dec_ref(v___x_3100_);
v___x_3102_ = lean_string_append(v___x_3101_, v___x_3069_);
v___x_3103_ = lean_uint32_to_nat(v___y_3053_);
v___x_3104_ = l_Nat_reprFast(v___x_3103_);
v___x_3105_ = lean_string_append(v___x_3102_, v___x_3104_);
lean_dec_ref(v___x_3104_);
v___x_3106_ = lean_string_append(v___x_3105_, v___x_3069_);
v___x_3107_ = lean_uint32_to_nat(v___y_3057_);
v___x_3108_ = l_Nat_reprFast(v___x_3107_);
v___x_3109_ = lean_string_append(v___x_3106_, v___x_3108_);
lean_dec_ref(v___x_3108_);
v___x_3110_ = lean_string_append(v___x_3109_, v___x_3069_);
v___x_3111_ = lean_uint32_to_nat(v___y_3060_);
v___x_3112_ = l_Nat_reprFast(v___x_3111_);
v___x_3113_ = lean_string_append(v___x_3110_, v___x_3112_);
lean_dec_ref(v___x_3112_);
v___x_3114_ = ((lean_object*)(lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotCostHarness_verify_spec__1___closed__1));
v___x_3115_ = lean_string_append(v___x_3113_, v___x_3114_);
v___x_3116_ = lp_batteries_IO_println___at___00Batteries_Tactic_Lint_lintCore_spec__4(v___x_3115_);
if (lean_obj_tag(v___x_3116_) == 0)
{
lean_object* v___x_3117_; size_t v___x_3118_; size_t v___x_3119_; 
lean_dec_ref_known(v___x_3116_, 1);
v___x_3117_ = lean_alloc_ctor(0, 2, 0);
lean_ctor_set(v___x_3117_, 0, v_accepts_3066_);
lean_ctor_set(v___x_3117_, 1, v___y_3054_);
v___x_3118_ = ((size_t)1ULL);
v___x_3119_ = lean_usize_add(v_i_3049_, v___x_3118_);
v_i_3049_ = v___x_3119_;
v_b_3050_ = v___x_3117_;
goto _start;
}
else
{
lean_object* v_a_3121_; lean_object* v___x_3123_; uint8_t v_isShared_3124_; uint8_t v_isSharedCheck_3128_; 
lean_dec(v_accepts_3066_);
lean_dec(v___y_3054_);
v_a_3121_ = lean_ctor_get(v___x_3116_, 0);
v_isSharedCheck_3128_ = !lean_is_exclusive(v___x_3116_);
if (v_isSharedCheck_3128_ == 0)
{
v___x_3123_ = v___x_3116_;
v_isShared_3124_ = v_isSharedCheck_3128_;
goto v_resetjp_3122_;
}
else
{
lean_inc(v_a_3121_);
lean_dec(v___x_3116_);
v___x_3123_ = lean_box(0);
v_isShared_3124_ = v_isSharedCheck_3128_;
goto v_resetjp_3122_;
}
v_resetjp_3122_:
{
lean_object* v___x_3126_; 
if (v_isShared_3124_ == 0)
{
v___x_3126_ = v___x_3123_;
goto v_reusejp_3125_;
}
else
{
lean_object* v_reuseFailAlloc_3127_; 
v_reuseFailAlloc_3127_ = lean_alloc_ctor(1, 1, 0);
lean_ctor_set(v_reuseFailAlloc_3127_, 0, v_a_3121_);
v___x_3126_ = v_reuseFailAlloc_3127_;
goto v_reusejp_3125_;
}
v_reusejp_3125_:
{
return v___x_3126_;
}
}
}
}
v___jp_3129_:
{
lean_object* v___x_3131_; lean_object* v___x_3132_; lean_object* v___x_3133_; lean_object* v___x_3134_; 
v___x_3131_ = ((lean_object*)(lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotCostHarness_verify_spec__1___closed__2));
v___x_3132_ = lean_string_append(v___y_3130_, v___x_3131_);
v___x_3133_ = lean_alloc_ctor(18, 1, 0);
lean_ctor_set(v___x_3133_, 0, v___x_3132_);
v___x_3134_ = lean_alloc_ctor(1, 1, 0);
lean_ctor_set(v___x_3134_, 0, v___x_3133_);
return v___x_3134_;
}
}
}
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotCostHarness_verify_spec__1___boxed(lean_object* v_as_3577_, lean_object* v_sz_3578_, lean_object* v_i_3579_, lean_object* v_b_3580_, lean_object* v___y_3581_){
_start:
{
size_t v_sz_boxed_3582_; size_t v_i_boxed_3583_; lean_object* v_res_3584_; 
v_sz_boxed_3582_ = lean_unbox_usize(v_sz_3578_);
lean_dec(v_sz_3578_);
v_i_boxed_3583_ = lean_unbox_usize(v_i_3579_);
lean_dec(v_i_3579_);
v_res_3584_ = lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotCostHarness_verify_spec__1(v_as_3577_, v_sz_boxed_3582_, v_i_boxed_3583_, v_b_3580_);
lean_dec_ref(v_as_3577_);
return v_res_3584_;
}
}
LEAN_EXPORT uint32_t lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotCostHarness_verify_spec__2___lam__0(lean_object* v_a_3585_, lean_object* v_x_3586_){
_start:
{
uint8_t v_negative_3587_; lean_object* v_lo_3588_; lean_object* v_hi_3589_; lean_object* v_base_3590_; uint64_t v___x_3591_; uint64_t v___x_3592_; uint32_t v___x_3593_; 
v_negative_3587_ = lean_ctor_get_uint8(v_a_3585_, sizeof(void*)*5);
v_lo_3588_ = lean_ctor_get(v_a_3585_, 1);
v_hi_3589_ = lean_ctor_get(v_a_3585_, 2);
v_base_3590_ = lean_ctor_get(v_a_3585_, 3);
v___x_3591_ = lean_uint64_of_nat(v_lo_3588_);
v___x_3592_ = lean_uint64_of_nat(v_hi_3589_);
v___x_3593_ = lp_competition_Submission_R24ExactDotCost_round128(v_negative_3587_, v___x_3591_, v___x_3592_, v_base_3590_);
return v___x_3593_;
}
}
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotCostHarness_verify_spec__2___lam__0___boxed(lean_object* v_a_3594_, lean_object* v_x_3595_){
_start:
{
uint32_t v_res_3596_; lean_object* v_r_3597_; 
v_res_3596_ = lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotCostHarness_verify_spec__2___lam__0(v_a_3594_, v_x_3595_);
lean_dec_ref(v_a_3594_);
v_r_3597_ = lean_box_uint32(v_res_3596_);
return v_r_3597_;
}
}
static lean_object* _init_lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotCostHarness_verify_spec__2___closed__3(void){
_start:
{
lean_object* v___x_3601_; 
v___x_3601_ = lean_cstr_to_nat("18446744073709551615");
return v___x_3601_;
}
}
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotCostHarness_verify_spec__2(lean_object* v_as_3602_, size_t v_sz_3603_, size_t v_i_3604_, lean_object* v_b_3605_){
_start:
{
uint8_t v___x_3607_; 
v___x_3607_ = lean_usize_dec_lt(v_i_3604_, v_sz_3603_);
if (v___x_3607_ == 0)
{
lean_object* v___x_3608_; 
v___x_3608_ = lean_alloc_ctor(0, 1, 0);
lean_ctor_set(v___x_3608_, 0, v_b_3605_);
return v___x_3608_;
}
else
{
lean_object* v_a_3609_; lean_object* v_lo_3616_; lean_object* v_hi_3617_; lean_object* v___x_3618_; lean_object* v___f_3619_; uint8_t v___y_3621_; lean_object* v___x_3657_; uint8_t v___x_3658_; 
v_a_3609_ = lean_array_uget_borrowed(v_as_3602_, v_i_3604_);
v_lo_3616_ = lean_ctor_get(v_a_3609_, 1);
v_hi_3617_ = lean_ctor_get(v_a_3609_, 2);
v___x_3618_ = lean_box(0);
lean_inc(v_a_3609_);
v___f_3619_ = lean_alloc_closure((void*)(lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotCostHarness_verify_spec__2___lam__0___boxed), 2, 1);
lean_closure_set(v___f_3619_, 0, v_a_3609_);
v___x_3657_ = lean_obj_once(&lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotCostHarness_verify_spec__2___closed__3, &lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotCostHarness_verify_spec__2___closed__3_once, _init_lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotCostHarness_verify_spec__2___closed__3);
v___x_3658_ = lean_nat_dec_lt(v___x_3657_, v_lo_3616_);
if (v___x_3658_ == 0)
{
uint8_t v___x_3659_; 
v___x_3659_ = lean_nat_dec_lt(v___x_3657_, v_hi_3617_);
v___y_3621_ = v___x_3659_;
goto v___jp_3620_;
}
else
{
v___y_3621_ = v___x_3658_;
goto v___jp_3620_;
}
v___jp_3610_:
{
lean_object* v_id_3611_; lean_object* v___x_3612_; lean_object* v___x_3613_; lean_object* v___x_3614_; lean_object* v___x_3615_; 
v_id_3611_ = lean_ctor_get(v_a_3609_, 0);
v___x_3612_ = ((lean_object*)(lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotCostHarness_verify_spec__2___closed__0));
lean_inc_ref(v_id_3611_);
v___x_3613_ = lean_string_append(v_id_3611_, v___x_3612_);
v___x_3614_ = lean_alloc_ctor(18, 1, 0);
lean_ctor_set(v___x_3614_, 0, v___x_3613_);
v___x_3615_ = lean_alloc_ctor(1, 1, 0);
lean_ctor_set(v___x_3615_, 0, v___x_3614_);
return v___x_3615_;
}
v___jp_3620_:
{
if (v___y_3621_ == 0)
{
lean_object* v_id_3622_; lean_object* v_expected_3623_; lean_object* v___x_3624_; uint8_t v___x_3625_; 
v_id_3622_ = lean_ctor_get(v_a_3609_, 0);
v_expected_3623_ = lean_ctor_get(v_a_3609_, 4);
v___x_3624_ = lean_unsigned_to_nat(4294967295u);
v___x_3625_ = lean_nat_dec_lt(v___x_3624_, v_expected_3623_);
if (v___x_3625_ == 0)
{
lean_object* v___x_3626_; 
v___x_3626_ = l_IO_lazyPure___redArg(v___f_3619_);
if (lean_obj_tag(v___x_3626_) == 0)
{
lean_object* v_a_3627_; lean_object* v___x_3628_; uint32_t v___x_3629_; uint32_t v___x_3630_; lean_object* v___x_3631_; 
v_a_3627_ = lean_ctor_get(v___x_3626_, 0);
lean_inc(v_a_3627_);
lean_dec_ref_known(v___x_3626_, 1);
v___x_3628_ = ((lean_object*)(lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotCostHarness_verify_spec__2___closed__1));
v___x_3629_ = lean_uint32_of_nat(v_expected_3623_);
v___x_3630_ = lean_unbox_uint32(v_a_3627_);
lean_inc_ref(v_id_3622_);
v___x_3631_ = lp_competition_R24DotCostHarness_checkWord(v_id_3622_, v___x_3628_, v___x_3630_, v___x_3629_);
if (lean_obj_tag(v___x_3631_) == 0)
{
lean_object* v___x_3632_; lean_object* v___x_3633_; lean_object* v___x_3634_; lean_object* v___x_3635_; lean_object* v___x_3636_; lean_object* v___x_3637_; lean_object* v___x_3638_; uint32_t v___x_3639_; lean_object* v___x_3640_; lean_object* v___x_3641_; lean_object* v___x_3642_; lean_object* v___x_3643_; lean_object* v___x_3644_; lean_object* v___x_3645_; 
lean_dec_ref_known(v___x_3631_, 1);
v___x_3632_ = ((lean_object*)(lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotCostHarness_verify_spec__2___closed__2));
v___x_3633_ = lean_string_append(v___x_3632_, v_id_3622_);
v___x_3634_ = ((lean_object*)(lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotCostHarness_emit_spec__0___closed__1));
v___x_3635_ = lean_string_append(v___x_3633_, v___x_3634_);
lean_inc(v_expected_3623_);
v___x_3636_ = l_Nat_reprFast(v_expected_3623_);
v___x_3637_ = lean_string_append(v___x_3635_, v___x_3636_);
lean_dec_ref(v___x_3636_);
v___x_3638_ = lean_string_append(v___x_3637_, v___x_3634_);
v___x_3639_ = lean_unbox_uint32(v_a_3627_);
lean_dec(v_a_3627_);
v___x_3640_ = lean_uint32_to_nat(v___x_3639_);
v___x_3641_ = l_Nat_reprFast(v___x_3640_);
v___x_3642_ = lean_string_append(v___x_3638_, v___x_3641_);
lean_dec_ref(v___x_3641_);
v___x_3643_ = ((lean_object*)(lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotCostHarness_verify_spec__1___closed__1));
v___x_3644_ = lean_string_append(v___x_3642_, v___x_3643_);
v___x_3645_ = lp_batteries_IO_println___at___00Batteries_Tactic_Lint_lintCore_spec__4(v___x_3644_);
if (lean_obj_tag(v___x_3645_) == 0)
{
size_t v___x_3646_; size_t v___x_3647_; 
lean_dec_ref_known(v___x_3645_, 1);
v___x_3646_ = ((size_t)1ULL);
v___x_3647_ = lean_usize_add(v_i_3604_, v___x_3646_);
v_i_3604_ = v___x_3647_;
v_b_3605_ = v___x_3618_;
goto _start;
}
else
{
return v___x_3645_;
}
}
else
{
lean_dec(v_a_3627_);
return v___x_3631_;
}
}
else
{
lean_object* v_a_3649_; lean_object* v___x_3651_; uint8_t v_isShared_3652_; uint8_t v_isSharedCheck_3656_; 
v_a_3649_ = lean_ctor_get(v___x_3626_, 0);
v_isSharedCheck_3656_ = !lean_is_exclusive(v___x_3626_);
if (v_isSharedCheck_3656_ == 0)
{
v___x_3651_ = v___x_3626_;
v_isShared_3652_ = v_isSharedCheck_3656_;
goto v_resetjp_3650_;
}
else
{
lean_inc(v_a_3649_);
lean_dec(v___x_3626_);
v___x_3651_ = lean_box(0);
v_isShared_3652_ = v_isSharedCheck_3656_;
goto v_resetjp_3650_;
}
v_resetjp_3650_:
{
lean_object* v___x_3654_; 
if (v_isShared_3652_ == 0)
{
v___x_3654_ = v___x_3651_;
goto v_reusejp_3653_;
}
else
{
lean_object* v_reuseFailAlloc_3655_; 
v_reuseFailAlloc_3655_ = lean_alloc_ctor(1, 1, 0);
lean_ctor_set(v_reuseFailAlloc_3655_, 0, v_a_3649_);
v___x_3654_ = v_reuseFailAlloc_3655_;
goto v_reusejp_3653_;
}
v_reusejp_3653_:
{
return v___x_3654_;
}
}
}
}
else
{
lean_dec_ref(v___f_3619_);
goto v___jp_3610_;
}
}
else
{
lean_dec_ref(v___f_3619_);
goto v___jp_3610_;
}
}
}
}
}
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotCostHarness_verify_spec__2___boxed(lean_object* v_as_3660_, lean_object* v_sz_3661_, lean_object* v_i_3662_, lean_object* v_b_3663_, lean_object* v___y_3664_){
_start:
{
size_t v_sz_boxed_3665_; size_t v_i_boxed_3666_; lean_object* v_res_3667_; 
v_sz_boxed_3665_ = lean_unbox_usize(v_sz_3661_);
lean_dec(v_sz_3661_);
v_i_boxed_3666_ = lean_unbox_usize(v_i_3662_);
lean_dec(v_i_3662_);
v_res_3667_ = lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotCostHarness_verify_spec__2(v_as_3660_, v_sz_boxed_3665_, v_i_boxed_3666_, v_b_3663_);
lean_dec_ref(v_as_3660_);
return v_res_3667_;
}
}
LEAN_EXPORT lean_object* lp_competition_R24DotCostHarness_verify(lean_object* v_plan_3671_){
_start:
{
lean_object* v_cases_3673_; lean_object* v_round__cases_3674_; lean_object* v___x_3675_; size_t v_sz_3676_; size_t v___x_3677_; lean_object* v___x_3678_; 
v_cases_3673_ = lean_ctor_get(v_plan_3671_, 0);
v_round__cases_3674_ = lean_ctor_get(v_plan_3671_, 1);
v___x_3675_ = ((lean_object*)(lp_competition_R24DotCostHarness_verify___closed__0));
v_sz_3676_ = lean_array_size(v_cases_3673_);
v___x_3677_ = ((size_t)0ULL);
v___x_3678_ = lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotCostHarness_verify_spec__1(v_cases_3673_, v_sz_3676_, v___x_3677_, v___x_3675_);
if (lean_obj_tag(v___x_3678_) == 0)
{
lean_object* v_a_3679_; lean_object* v___x_3680_; size_t v_sz_3681_; lean_object* v___x_3682_; 
v_a_3679_ = lean_ctor_get(v___x_3678_, 0);
lean_inc(v_a_3679_);
lean_dec_ref_known(v___x_3678_, 1);
v___x_3680_ = lean_box(0);
v_sz_3681_ = lean_array_size(v_round__cases_3674_);
v___x_3682_ = lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotCostHarness_verify_spec__2(v_round__cases_3674_, v_sz_3681_, v___x_3677_, v___x_3680_);
if (lean_obj_tag(v___x_3682_) == 0)
{
lean_object* v_fst_3683_; lean_object* v_snd_3684_; lean_object* v___x_3685_; lean_object* v___x_3686_; lean_object* v___x_3687_; lean_object* v___x_3688_; lean_object* v___x_3689_; lean_object* v___x_3690_; lean_object* v___x_3691_; lean_object* v___x_3692_; lean_object* v___x_3693_; lean_object* v___x_3694_; lean_object* v___x_3695_; lean_object* v___x_3696_; lean_object* v___x_3697_; lean_object* v___x_3698_; lean_object* v___x_3699_; lean_object* v___x_3700_; 
lean_dec_ref_known(v___x_3682_, 1);
v_fst_3683_ = lean_ctor_get(v_a_3679_, 0);
lean_inc(v_fst_3683_);
v_snd_3684_ = lean_ctor_get(v_a_3679_, 1);
lean_inc(v_snd_3684_);
lean_dec(v_a_3679_);
v___x_3685_ = ((lean_object*)(lp_competition_R24DotCostHarness_verify___closed__1));
v___x_3686_ = lean_array_get_size(v_cases_3673_);
v___x_3687_ = l_Nat_reprFast(v___x_3686_);
v___x_3688_ = lean_string_append(v___x_3685_, v___x_3687_);
lean_dec_ref(v___x_3687_);
v___x_3689_ = ((lean_object*)(lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotCostHarness_emit_spec__0___closed__1));
v___x_3690_ = lean_string_append(v___x_3688_, v___x_3689_);
v___x_3691_ = lean_array_get_size(v_round__cases_3674_);
v___x_3692_ = l_Nat_reprFast(v___x_3691_);
v___x_3693_ = lean_string_append(v___x_3690_, v___x_3692_);
lean_dec_ref(v___x_3692_);
v___x_3694_ = lean_string_append(v___x_3693_, v___x_3689_);
v___x_3695_ = l_Nat_reprFast(v_fst_3683_);
v___x_3696_ = lean_string_append(v___x_3694_, v___x_3695_);
lean_dec_ref(v___x_3695_);
v___x_3697_ = lean_string_append(v___x_3696_, v___x_3689_);
v___x_3698_ = l_Nat_reprFast(v_snd_3684_);
v___x_3699_ = lean_string_append(v___x_3697_, v___x_3698_);
lean_dec_ref(v___x_3698_);
v___x_3700_ = lp_batteries_IO_println___at___00Batteries_Tactic_Lint_lintCore_spec__4(v___x_3699_);
return v___x_3700_;
}
else
{
lean_dec(v_a_3679_);
return v___x_3682_;
}
}
else
{
lean_object* v_a_3701_; lean_object* v___x_3703_; uint8_t v_isShared_3704_; uint8_t v_isSharedCheck_3708_; 
v_a_3701_ = lean_ctor_get(v___x_3678_, 0);
v_isSharedCheck_3708_ = !lean_is_exclusive(v___x_3678_);
if (v_isSharedCheck_3708_ == 0)
{
v___x_3703_ = v___x_3678_;
v_isShared_3704_ = v_isSharedCheck_3708_;
goto v_resetjp_3702_;
}
else
{
lean_inc(v_a_3701_);
lean_dec(v___x_3678_);
v___x_3703_ = lean_box(0);
v_isShared_3704_ = v_isSharedCheck_3708_;
goto v_resetjp_3702_;
}
v_resetjp_3702_:
{
lean_object* v___x_3706_; 
if (v_isShared_3704_ == 0)
{
v___x_3706_ = v___x_3703_;
goto v_reusejp_3705_;
}
else
{
lean_object* v_reuseFailAlloc_3707_; 
v_reuseFailAlloc_3707_ = lean_alloc_ctor(1, 1, 0);
lean_ctor_set(v_reuseFailAlloc_3707_, 0, v_a_3701_);
v___x_3706_ = v_reuseFailAlloc_3707_;
goto v_reusejp_3705_;
}
v_reusejp_3705_:
{
return v___x_3706_;
}
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_R24DotCostHarness_verify___boxed(lean_object* v_plan_3709_, lean_object* v_a_3710_){
_start:
{
lean_object* v_res_3711_; 
v_res_3711_ = lp_competition_R24DotCostHarness_verify(v_plan_3709_);
lean_dec_ref(v_plan_3709_);
return v_res_3711_;
}
}
LEAN_EXPORT lean_object* lp_competition_R24DotCostHarness_env(lean_object* v_name_3713_){
_start:
{
lean_object* v___x_3715_; 
v___x_3715_ = lean_io_getenv(v_name_3713_);
if (lean_obj_tag(v___x_3715_) == 1)
{
lean_object* v_val_3716_; lean_object* v___x_3718_; uint8_t v_isShared_3719_; uint8_t v_isSharedCheck_3723_; 
v_val_3716_ = lean_ctor_get(v___x_3715_, 0);
v_isSharedCheck_3723_ = !lean_is_exclusive(v___x_3715_);
if (v_isSharedCheck_3723_ == 0)
{
v___x_3718_ = v___x_3715_;
v_isShared_3719_ = v_isSharedCheck_3723_;
goto v_resetjp_3717_;
}
else
{
lean_inc(v_val_3716_);
lean_dec(v___x_3715_);
v___x_3718_ = lean_box(0);
v_isShared_3719_ = v_isSharedCheck_3723_;
goto v_resetjp_3717_;
}
v_resetjp_3717_:
{
lean_object* v___x_3721_; 
if (v_isShared_3719_ == 0)
{
lean_ctor_set_tag(v___x_3718_, 0);
v___x_3721_ = v___x_3718_;
goto v_reusejp_3720_;
}
else
{
lean_object* v_reuseFailAlloc_3722_; 
v_reuseFailAlloc_3722_ = lean_alloc_ctor(0, 1, 0);
lean_ctor_set(v_reuseFailAlloc_3722_, 0, v_val_3716_);
v___x_3721_ = v_reuseFailAlloc_3722_;
goto v_reusejp_3720_;
}
v_reusejp_3720_:
{
return v___x_3721_;
}
}
}
else
{
lean_object* v___x_3724_; lean_object* v___x_3725_; lean_object* v___x_3726_; lean_object* v___x_3727_; 
lean_dec(v___x_3715_);
v___x_3724_ = ((lean_object*)(lp_competition_R24DotCostHarness_env___closed__0));
v___x_3725_ = lean_string_append(v___x_3724_, v_name_3713_);
v___x_3726_ = lean_alloc_ctor(18, 1, 0);
lean_ctor_set(v___x_3726_, 0, v___x_3725_);
v___x_3727_ = lean_alloc_ctor(1, 1, 0);
lean_ctor_set(v___x_3727_, 0, v___x_3726_);
return v___x_3727_;
}
}
}
LEAN_EXPORT lean_object* lp_competition_R24DotCostHarness_env___boxed(lean_object* v_name_3728_, lean_object* v_a_3729_){
_start:
{
lean_object* v_res_3730_; 
v_res_3730_ = lp_competition_R24DotCostHarness_env(v_name_3728_);
lean_dec_ref(v_name_3728_);
return v_res_3730_;
}
}
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotCostHarness_run_spec__0___lam__3(lean_object* v_a_3731_, lean_object* v_x_3732_){
_start:
{
lean_object* v_y_3733_; lean_object* v___x_3734_; 
v_y_3733_ = lean_ctor_get(v_a_3731_, 4);
lean_inc_ref(v_y_3733_);
lean_dec_ref(v_a_3731_);
v___x_3734_ = lp_competition_R24DotCostHarness_words(v_y_3733_);
return v___x_3734_;
}
}
LEAN_EXPORT uint8_t lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotCostHarness_run_spec__0___lam__0(lean_object* v_a_3735_, lean_object* v_00___3736_){
_start:
{
lean_object* v___x_3737_; uint8_t v___x_3738_; 
v___x_3737_ = ((lean_object*)(lp_competition_R24DotCostHarness_benchExactFull___closed__3));
v___x_3738_ = lean_string_dec_eq(v_a_3735_, v___x_3737_);
return v___x_3738_;
}
}
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotCostHarness_run_spec__0___lam__0___boxed(lean_object* v_a_3739_, lean_object* v_00___3740_){
_start:
{
uint8_t v_res_3741_; lean_object* v_r_3742_; 
v_res_3741_ = lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotCostHarness_run_spec__0___lam__0(v_a_3739_, v_00___3740_);
lean_dec_ref(v_a_3739_);
v_r_3742_ = lean_box(v_res_3741_);
return v_r_3742_;
}
}
LEAN_EXPORT uint8_t lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotCostHarness_run_spec__0___lam__1(lean_object* v_a_3743_, lean_object* v_00___3744_){
_start:
{
lean_object* v___x_3745_; uint8_t v___x_3746_; 
v___x_3745_ = ((lean_object*)(lp_competition_R24DotCostHarness_benchExactPrepared___closed__0));
v___x_3746_ = lean_string_dec_eq(v_a_3743_, v___x_3745_);
return v___x_3746_;
}
}
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotCostHarness_run_spec__0___lam__1___boxed(lean_object* v_a_3747_, lean_object* v_00___3748_){
_start:
{
uint8_t v_res_3749_; lean_object* v_r_3750_; 
v_res_3749_ = lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotCostHarness_run_spec__0___lam__1(v_a_3747_, v_00___3748_);
lean_dec_ref(v_a_3747_);
v_r_3750_ = lean_box(v_res_3749_);
return v_r_3750_;
}
}
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotCostHarness_run_spec__0___lam__2(lean_object* v_a_3751_, lean_object* v_x_3752_){
_start:
{
lean_object* v_x_3753_; lean_object* v___x_3754_; 
v_x_3753_ = lean_ctor_get(v_a_3751_, 3);
lean_inc_ref(v_x_3753_);
lean_dec_ref(v_a_3751_);
v___x_3754_ = lp_competition_R24DotCostHarness_words(v_x_3753_);
return v___x_3754_;
}
}
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotCostHarness_run_spec__0(lean_object* v_val_3761_, lean_object* v_a_3762_, lean_object* v_a_3763_, lean_object* v_a_3764_, lean_object* v_as_3765_, size_t v_sz_3766_, size_t v_i_3767_, lean_object* v_b_3768_){
_start:
{
lean_object* v_a_3771_; uint8_t v___x_3781_; 
v___x_3781_ = lean_usize_dec_lt(v_i_3767_, v_sz_3766_);
if (v___x_3781_ == 0)
{
lean_object* v___x_3782_; 
v___x_3782_ = lean_alloc_ctor(0, 1, 0);
lean_ctor_set(v___x_3782_, 0, v_b_3768_);
return v___x_3782_;
}
else
{
lean_object* v_a_3783_; uint8_t v_timed_3784_; 
v_a_3783_ = lean_array_uget_borrowed(v_as_3765_, v_i_3767_);
v_timed_3784_ = lean_ctor_get_uint8(v_a_3783_, sizeof(void*)*7);
if (v_timed_3784_ == 0)
{
v_a_3771_ = v_b_3768_;
goto v___jp_3770_;
}
else
{
lean_object* v_group_3785_; lean_object* v___y_3787_; uint8_t v___y_3788_; lean_object* v___y_3789_; lean_object* v___y_3802_; uint8_t v___y_3803_; uint8_t v___y_3804_; lean_object* v___y_3805_; lean_object* v___y_3818_; uint8_t v___y_3819_; uint8_t v___y_3820_; uint8_t v___y_3821_; lean_object* v___y_3822_; uint8_t v___y_3823_; uint8_t v___y_3845_; lean_object* v___y_3846_; uint8_t v___y_3847_; lean_object* v___y_3848_; uint8_t v___y_3849_; lean_object* v___y_3864_; uint8_t v___y_3865_; lean_object* v___y_3866_; uint8_t v___y_3867_; lean_object* v___f_3881_; lean_object* v___f_3882_; uint8_t v___x_3927_; 
v_group_3785_ = lean_ctor_get(v_a_3783_, 1);
lean_inc_n(v_a_3783_, 2);
v___f_3881_ = lean_alloc_closure((void*)(lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotCostHarness_run_spec__0___lam__2), 2, 1);
lean_closure_set(v___f_3881_, 0, v_a_3783_);
v___f_3882_ = lean_alloc_closure((void*)(lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotCostHarness_run_spec__0___lam__3), 2, 1);
lean_closure_set(v___f_3882_, 0, v_a_3783_);
v___x_3927_ = lean_string_dec_eq(v_group_3785_, v_a_3764_);
if (v___x_3927_ == 0)
{
lean_object* v___x_3928_; uint8_t v___x_3929_; 
v___x_3928_ = ((lean_object*)(lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotCostHarness_run_spec__0___closed__4));
v___x_3929_ = lean_string_dec_eq(v_group_3785_, v___x_3928_);
if (v___x_3929_ == 0)
{
lean_dec_ref(v___f_3882_);
lean_dec_ref(v___f_3881_);
v_a_3771_ = v_b_3768_;
goto v___jp_3770_;
}
else
{
goto v___jp_3883_;
}
}
else
{
goto v___jp_3883_;
}
v___jp_3786_:
{
if (v___y_3788_ == 0)
{
lean_dec_ref(v___y_3789_);
lean_dec_ref(v___y_3787_);
lean_dec(v_b_3768_);
goto v___jp_3778_;
}
else
{
lean_object* v___x_3790_; uint8_t v___x_3791_; 
v___x_3790_ = lean_box(0);
v___x_3791_ = lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotCostHarness_run_spec__0___lam__1(v_a_3763_, v___x_3790_);
if (v___x_3791_ == 0)
{
lean_dec_ref(v___y_3789_);
lean_dec_ref(v___y_3787_);
lean_dec(v_b_3768_);
goto v___jp_3778_;
}
else
{
lean_object* v___x_3792_; 
lean_inc(v_a_3783_);
v___x_3792_ = lp_competition_R24DotCostHarness_benchLazyPrepared(v_a_3783_, v___y_3787_, v___y_3789_, v_val_3761_);
if (lean_obj_tag(v___x_3792_) == 0)
{
lean_dec_ref_known(v___x_3792_, 1);
goto v___jp_3775_;
}
else
{
lean_object* v_a_3793_; lean_object* v___x_3795_; uint8_t v_isShared_3796_; uint8_t v_isSharedCheck_3800_; 
lean_dec(v_b_3768_);
v_a_3793_ = lean_ctor_get(v___x_3792_, 0);
v_isSharedCheck_3800_ = !lean_is_exclusive(v___x_3792_);
if (v_isSharedCheck_3800_ == 0)
{
v___x_3795_ = v___x_3792_;
v_isShared_3796_ = v_isSharedCheck_3800_;
goto v_resetjp_3794_;
}
else
{
lean_inc(v_a_3793_);
lean_dec(v___x_3792_);
v___x_3795_ = lean_box(0);
v_isShared_3796_ = v_isSharedCheck_3800_;
goto v_resetjp_3794_;
}
v_resetjp_3794_:
{
lean_object* v___x_3798_; 
if (v_isShared_3796_ == 0)
{
v___x_3798_ = v___x_3795_;
goto v_reusejp_3797_;
}
else
{
lean_object* v_reuseFailAlloc_3799_; 
v_reuseFailAlloc_3799_ = lean_alloc_ctor(1, 1, 0);
lean_ctor_set(v_reuseFailAlloc_3799_, 0, v_a_3793_);
v___x_3798_ = v_reuseFailAlloc_3799_;
goto v_reusejp_3797_;
}
v_reusejp_3797_:
{
return v___x_3798_;
}
}
}
}
}
}
v___jp_3801_:
{
if (v___y_3803_ == 0)
{
v___y_3787_ = v___y_3802_;
v___y_3788_ = v___y_3804_;
v___y_3789_ = v___y_3805_;
goto v___jp_3786_;
}
else
{
lean_object* v___x_3806_; uint8_t v___x_3807_; 
v___x_3806_ = lean_box(0);
v___x_3807_ = lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotCostHarness_run_spec__0___lam__1(v_a_3763_, v___x_3806_);
if (v___x_3807_ == 0)
{
v___y_3787_ = v___y_3802_;
v___y_3788_ = v___y_3804_;
v___y_3789_ = v___y_3805_;
goto v___jp_3786_;
}
else
{
lean_object* v___x_3808_; 
lean_inc(v_a_3783_);
v___x_3808_ = lp_competition_R24DotCostHarness_benchEagerPrepared(v_a_3783_, v___y_3802_, v___y_3805_, v_val_3761_);
if (lean_obj_tag(v___x_3808_) == 0)
{
lean_dec_ref_known(v___x_3808_, 1);
goto v___jp_3775_;
}
else
{
lean_object* v_a_3809_; lean_object* v___x_3811_; uint8_t v_isShared_3812_; uint8_t v_isSharedCheck_3816_; 
lean_dec(v_b_3768_);
v_a_3809_ = lean_ctor_get(v___x_3808_, 0);
v_isSharedCheck_3816_ = !lean_is_exclusive(v___x_3808_);
if (v_isSharedCheck_3816_ == 0)
{
v___x_3811_ = v___x_3808_;
v_isShared_3812_ = v_isSharedCheck_3816_;
goto v_resetjp_3810_;
}
else
{
lean_inc(v_a_3809_);
lean_dec(v___x_3808_);
v___x_3811_ = lean_box(0);
v_isShared_3812_ = v_isSharedCheck_3816_;
goto v_resetjp_3810_;
}
v_resetjp_3810_:
{
lean_object* v___x_3814_; 
if (v_isShared_3812_ == 0)
{
v___x_3814_ = v___x_3811_;
goto v_reusejp_3813_;
}
else
{
lean_object* v_reuseFailAlloc_3815_; 
v_reuseFailAlloc_3815_ = lean_alloc_ctor(1, 1, 0);
lean_ctor_set(v_reuseFailAlloc_3815_, 0, v_a_3809_);
v___x_3814_ = v_reuseFailAlloc_3815_;
goto v_reusejp_3813_;
}
v_reusejp_3813_:
{
return v___x_3814_;
}
}
}
}
}
}
v___jp_3817_:
{
if (v___y_3823_ == 0)
{
if (v___y_3819_ == 0)
{
v___y_3802_ = v___y_3818_;
v___y_3803_ = v___y_3820_;
v___y_3804_ = v___y_3821_;
v___y_3805_ = v___y_3822_;
goto v___jp_3801_;
}
else
{
lean_object* v___x_3824_; uint8_t v___x_3825_; 
v___x_3824_ = lean_box(0);
v___x_3825_ = lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotCostHarness_run_spec__0___lam__1(v_a_3763_, v___x_3824_);
if (v___x_3825_ == 0)
{
v___y_3802_ = v___y_3818_;
v___y_3803_ = v___y_3820_;
v___y_3804_ = v___y_3821_;
v___y_3805_ = v___y_3822_;
goto v___jp_3801_;
}
else
{
lean_object* v___x_3826_; 
lean_inc(v_a_3783_);
v___x_3826_ = lp_competition_R24DotCostHarness_benchExactPrepared(v_a_3783_, v___y_3818_, v___y_3822_, v_val_3761_);
if (lean_obj_tag(v___x_3826_) == 0)
{
lean_dec_ref_known(v___x_3826_, 1);
goto v___jp_3775_;
}
else
{
lean_object* v_a_3827_; lean_object* v___x_3829_; uint8_t v_isShared_3830_; uint8_t v_isSharedCheck_3834_; 
lean_dec(v_b_3768_);
v_a_3827_ = lean_ctor_get(v___x_3826_, 0);
v_isSharedCheck_3834_ = !lean_is_exclusive(v___x_3826_);
if (v_isSharedCheck_3834_ == 0)
{
v___x_3829_ = v___x_3826_;
v_isShared_3830_ = v_isSharedCheck_3834_;
goto v_resetjp_3828_;
}
else
{
lean_inc(v_a_3827_);
lean_dec(v___x_3826_);
v___x_3829_ = lean_box(0);
v_isShared_3830_ = v_isSharedCheck_3834_;
goto v_resetjp_3828_;
}
v_resetjp_3828_:
{
lean_object* v___x_3832_; 
if (v_isShared_3830_ == 0)
{
v___x_3832_ = v___x_3829_;
goto v_reusejp_3831_;
}
else
{
lean_object* v_reuseFailAlloc_3833_; 
v_reuseFailAlloc_3833_ = lean_alloc_ctor(1, 1, 0);
lean_ctor_set(v_reuseFailAlloc_3833_, 0, v_a_3827_);
v___x_3832_ = v_reuseFailAlloc_3833_;
goto v_reusejp_3831_;
}
v_reusejp_3831_:
{
return v___x_3832_;
}
}
}
}
}
}
else
{
lean_object* v___x_3835_; 
lean_inc(v_a_3783_);
v___x_3835_ = lp_competition_R24DotCostHarness_benchLazyFull(v_a_3783_, v___y_3818_, v___y_3822_, v_val_3761_);
if (lean_obj_tag(v___x_3835_) == 0)
{
lean_dec_ref_known(v___x_3835_, 1);
goto v___jp_3775_;
}
else
{
lean_object* v_a_3836_; lean_object* v___x_3838_; uint8_t v_isShared_3839_; uint8_t v_isSharedCheck_3843_; 
lean_dec(v_b_3768_);
v_a_3836_ = lean_ctor_get(v___x_3835_, 0);
v_isSharedCheck_3843_ = !lean_is_exclusive(v___x_3835_);
if (v_isSharedCheck_3843_ == 0)
{
v___x_3838_ = v___x_3835_;
v_isShared_3839_ = v_isSharedCheck_3843_;
goto v_resetjp_3837_;
}
else
{
lean_inc(v_a_3836_);
lean_dec(v___x_3835_);
v___x_3838_ = lean_box(0);
v_isShared_3839_ = v_isSharedCheck_3843_;
goto v_resetjp_3837_;
}
v_resetjp_3837_:
{
lean_object* v___x_3841_; 
if (v_isShared_3839_ == 0)
{
v___x_3841_ = v___x_3838_;
goto v_reusejp_3840_;
}
else
{
lean_object* v_reuseFailAlloc_3842_; 
v_reuseFailAlloc_3842_ = lean_alloc_ctor(1, 1, 0);
lean_ctor_set(v_reuseFailAlloc_3842_, 0, v_a_3836_);
v___x_3841_ = v_reuseFailAlloc_3842_;
goto v_reusejp_3840_;
}
v_reusejp_3840_:
{
return v___x_3841_;
}
}
}
}
}
v___jp_3844_:
{
if (v___y_3849_ == 0)
{
lean_object* v___x_3850_; uint8_t v___x_3851_; 
v___x_3850_ = ((lean_object*)(lp_competition_R24DotCostHarness_benchLazyFull___closed__0));
v___x_3851_ = lean_string_dec_eq(v_a_3762_, v___x_3850_);
if (v___x_3851_ == 0)
{
v___y_3818_ = v___y_3846_;
v___y_3819_ = v___y_3845_;
v___y_3820_ = v___y_3847_;
v___y_3821_ = v___x_3851_;
v___y_3822_ = v___y_3848_;
v___y_3823_ = v___x_3851_;
goto v___jp_3817_;
}
else
{
lean_object* v___x_3852_; uint8_t v___x_3853_; 
v___x_3852_ = lean_box(0);
v___x_3853_ = lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotCostHarness_run_spec__0___lam__0(v_a_3763_, v___x_3852_);
v___y_3818_ = v___y_3846_;
v___y_3819_ = v___y_3845_;
v___y_3820_ = v___y_3847_;
v___y_3821_ = v___x_3851_;
v___y_3822_ = v___y_3848_;
v___y_3823_ = v___x_3853_;
goto v___jp_3817_;
}
}
else
{
lean_object* v___x_3854_; 
lean_inc(v_a_3783_);
v___x_3854_ = lp_competition_R24DotCostHarness_benchEagerFull(v_a_3783_, v___y_3846_, v___y_3848_, v_val_3761_);
if (lean_obj_tag(v___x_3854_) == 0)
{
lean_dec_ref_known(v___x_3854_, 1);
goto v___jp_3775_;
}
else
{
lean_object* v_a_3855_; lean_object* v___x_3857_; uint8_t v_isShared_3858_; uint8_t v_isSharedCheck_3862_; 
lean_dec(v_b_3768_);
v_a_3855_ = lean_ctor_get(v___x_3854_, 0);
v_isSharedCheck_3862_ = !lean_is_exclusive(v___x_3854_);
if (v_isSharedCheck_3862_ == 0)
{
v___x_3857_ = v___x_3854_;
v_isShared_3858_ = v_isSharedCheck_3862_;
goto v_resetjp_3856_;
}
else
{
lean_inc(v_a_3855_);
lean_dec(v___x_3854_);
v___x_3857_ = lean_box(0);
v_isShared_3858_ = v_isSharedCheck_3862_;
goto v_resetjp_3856_;
}
v_resetjp_3856_:
{
lean_object* v___x_3860_; 
if (v_isShared_3858_ == 0)
{
v___x_3860_ = v___x_3857_;
goto v_reusejp_3859_;
}
else
{
lean_object* v_reuseFailAlloc_3861_; 
v_reuseFailAlloc_3861_ = lean_alloc_ctor(1, 1, 0);
lean_ctor_set(v_reuseFailAlloc_3861_, 0, v_a_3855_);
v___x_3860_ = v_reuseFailAlloc_3861_;
goto v_reusejp_3859_;
}
v_reusejp_3859_:
{
return v___x_3860_;
}
}
}
}
}
v___jp_3863_:
{
if (v___y_3867_ == 0)
{
lean_object* v___x_3868_; uint8_t v___x_3869_; 
v___x_3868_ = ((lean_object*)(lp_competition_R24DotCostHarness_benchEagerFull___closed__0));
v___x_3869_ = lean_string_dec_eq(v_a_3762_, v___x_3868_);
if (v___x_3869_ == 0)
{
v___y_3845_ = v___y_3865_;
v___y_3846_ = v___y_3864_;
v___y_3847_ = v___x_3869_;
v___y_3848_ = v___y_3866_;
v___y_3849_ = v___x_3869_;
goto v___jp_3844_;
}
else
{
lean_object* v___x_3870_; uint8_t v___x_3871_; 
v___x_3870_ = lean_box(0);
v___x_3871_ = lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotCostHarness_run_spec__0___lam__0(v_a_3763_, v___x_3870_);
v___y_3845_ = v___y_3865_;
v___y_3846_ = v___y_3864_;
v___y_3847_ = v___x_3869_;
v___y_3848_ = v___y_3866_;
v___y_3849_ = v___x_3871_;
goto v___jp_3844_;
}
}
else
{
lean_object* v___x_3872_; 
lean_inc(v_a_3783_);
v___x_3872_ = lp_competition_R24DotCostHarness_benchExactFull(v_a_3783_, v___y_3864_, v___y_3866_, v_val_3761_);
if (lean_obj_tag(v___x_3872_) == 0)
{
lean_dec_ref_known(v___x_3872_, 1);
goto v___jp_3775_;
}
else
{
lean_object* v_a_3873_; lean_object* v___x_3875_; uint8_t v_isShared_3876_; uint8_t v_isSharedCheck_3880_; 
lean_dec(v_b_3768_);
v_a_3873_ = lean_ctor_get(v___x_3872_, 0);
v_isSharedCheck_3880_ = !lean_is_exclusive(v___x_3872_);
if (v_isSharedCheck_3880_ == 0)
{
v___x_3875_ = v___x_3872_;
v_isShared_3876_ = v_isSharedCheck_3880_;
goto v_resetjp_3874_;
}
else
{
lean_inc(v_a_3873_);
lean_dec(v___x_3872_);
v___x_3875_ = lean_box(0);
v_isShared_3876_ = v_isSharedCheck_3880_;
goto v_resetjp_3874_;
}
v_resetjp_3874_:
{
lean_object* v___x_3878_; 
if (v_isShared_3876_ == 0)
{
v___x_3878_ = v___x_3875_;
goto v_reusejp_3877_;
}
else
{
lean_object* v_reuseFailAlloc_3879_; 
v_reuseFailAlloc_3879_ = lean_alloc_ctor(1, 1, 0);
lean_ctor_set(v_reuseFailAlloc_3879_, 0, v_a_3873_);
v___x_3878_ = v_reuseFailAlloc_3879_;
goto v_reusejp_3877_;
}
v_reusejp_3877_:
{
return v___x_3878_;
}
}
}
}
}
v___jp_3883_:
{
lean_object* v___x_3884_; 
v___x_3884_ = l_IO_lazyPure___redArg(v___f_3881_);
if (lean_obj_tag(v___x_3884_) == 0)
{
lean_object* v_a_3885_; lean_object* v___x_3886_; 
v_a_3885_ = lean_ctor_get(v___x_3884_, 0);
lean_inc(v_a_3885_);
lean_dec_ref_known(v___x_3884_, 1);
v___x_3886_ = l_IO_lazyPure___redArg(v___f_3882_);
if (lean_obj_tag(v___x_3886_) == 0)
{
lean_object* v_a_3887_; uint8_t v___x_3888_; 
v_a_3887_ = lean_ctor_get(v___x_3886_, 0);
lean_inc(v_a_3887_);
lean_dec_ref_known(v___x_3886_, 1);
v___x_3888_ = lp_competition_R24DotCostHarness_supported(v_a_3885_, v_a_3887_);
if (v___x_3888_ == 0)
{
lean_object* v_name_3889_; lean_object* v_group_3890_; lean_object* v___x_3891_; lean_object* v___x_3892_; lean_object* v___x_3893_; lean_object* v___x_3894_; lean_object* v___x_3895_; lean_object* v___x_3896_; lean_object* v___x_3897_; lean_object* v___x_3898_; 
lean_dec(v_a_3887_);
lean_dec(v_a_3885_);
v_name_3889_ = lean_ctor_get(v_a_3783_, 0);
v_group_3890_ = lean_ctor_get(v_a_3783_, 1);
v___x_3891_ = ((lean_object*)(lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotCostHarness_run_spec__0___closed__2));
v___x_3892_ = lean_string_append(v___x_3891_, v_name_3889_);
v___x_3893_ = ((lean_object*)(lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotCostHarness_emit_spec__0___closed__1));
v___x_3894_ = lean_string_append(v___x_3892_, v___x_3893_);
v___x_3895_ = lean_string_append(v___x_3894_, v_group_3890_);
v___x_3896_ = ((lean_object*)(lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotCostHarness_run_spec__0___closed__3));
v___x_3897_ = lean_string_append(v___x_3895_, v___x_3896_);
v___x_3898_ = lp_batteries_IO_println___at___00Batteries_Tactic_Lint_lintCore_spec__4(v___x_3897_);
if (lean_obj_tag(v___x_3898_) == 0)
{
lean_dec_ref_known(v___x_3898_, 1);
v_a_3771_ = v_b_3768_;
goto v___jp_3770_;
}
else
{
lean_object* v_a_3899_; lean_object* v___x_3901_; uint8_t v_isShared_3902_; uint8_t v_isSharedCheck_3906_; 
lean_dec(v_b_3768_);
v_a_3899_ = lean_ctor_get(v___x_3898_, 0);
v_isSharedCheck_3906_ = !lean_is_exclusive(v___x_3898_);
if (v_isSharedCheck_3906_ == 0)
{
v___x_3901_ = v___x_3898_;
v_isShared_3902_ = v_isSharedCheck_3906_;
goto v_resetjp_3900_;
}
else
{
lean_inc(v_a_3899_);
lean_dec(v___x_3898_);
v___x_3901_ = lean_box(0);
v_isShared_3902_ = v_isSharedCheck_3906_;
goto v_resetjp_3900_;
}
v_resetjp_3900_:
{
lean_object* v___x_3904_; 
if (v_isShared_3902_ == 0)
{
v___x_3904_ = v___x_3901_;
goto v_reusejp_3903_;
}
else
{
lean_object* v_reuseFailAlloc_3905_; 
v_reuseFailAlloc_3905_ = lean_alloc_ctor(1, 1, 0);
lean_ctor_set(v_reuseFailAlloc_3905_, 0, v_a_3899_);
v___x_3904_ = v_reuseFailAlloc_3905_;
goto v_reusejp_3903_;
}
v_reusejp_3903_:
{
return v___x_3904_;
}
}
}
}
else
{
lean_object* v___x_3907_; uint8_t v___x_3908_; 
v___x_3907_ = ((lean_object*)(lp_competition_R24DotCostHarness_benchExactFull___closed__2));
v___x_3908_ = lean_string_dec_eq(v_a_3762_, v___x_3907_);
if (v___x_3908_ == 0)
{
v___y_3864_ = v_a_3885_;
v___y_3865_ = v___x_3908_;
v___y_3866_ = v_a_3887_;
v___y_3867_ = v___x_3908_;
goto v___jp_3863_;
}
else
{
lean_object* v___x_3909_; uint8_t v___x_3910_; 
v___x_3909_ = lean_box(0);
v___x_3910_ = lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotCostHarness_run_spec__0___lam__0(v_a_3763_, v___x_3909_);
v___y_3864_ = v_a_3885_;
v___y_3865_ = v___x_3908_;
v___y_3866_ = v_a_3887_;
v___y_3867_ = v___x_3910_;
goto v___jp_3863_;
}
}
}
else
{
lean_object* v_a_3911_; lean_object* v___x_3913_; uint8_t v_isShared_3914_; uint8_t v_isSharedCheck_3918_; 
lean_dec(v_a_3885_);
lean_dec(v_b_3768_);
v_a_3911_ = lean_ctor_get(v___x_3886_, 0);
v_isSharedCheck_3918_ = !lean_is_exclusive(v___x_3886_);
if (v_isSharedCheck_3918_ == 0)
{
v___x_3913_ = v___x_3886_;
v_isShared_3914_ = v_isSharedCheck_3918_;
goto v_resetjp_3912_;
}
else
{
lean_inc(v_a_3911_);
lean_dec(v___x_3886_);
v___x_3913_ = lean_box(0);
v_isShared_3914_ = v_isSharedCheck_3918_;
goto v_resetjp_3912_;
}
v_resetjp_3912_:
{
lean_object* v___x_3916_; 
if (v_isShared_3914_ == 0)
{
v___x_3916_ = v___x_3913_;
goto v_reusejp_3915_;
}
else
{
lean_object* v_reuseFailAlloc_3917_; 
v_reuseFailAlloc_3917_ = lean_alloc_ctor(1, 1, 0);
lean_ctor_set(v_reuseFailAlloc_3917_, 0, v_a_3911_);
v___x_3916_ = v_reuseFailAlloc_3917_;
goto v_reusejp_3915_;
}
v_reusejp_3915_:
{
return v___x_3916_;
}
}
}
}
else
{
lean_object* v_a_3919_; lean_object* v___x_3921_; uint8_t v_isShared_3922_; uint8_t v_isSharedCheck_3926_; 
lean_dec_ref(v___f_3882_);
lean_dec(v_b_3768_);
v_a_3919_ = lean_ctor_get(v___x_3884_, 0);
v_isSharedCheck_3926_ = !lean_is_exclusive(v___x_3884_);
if (v_isSharedCheck_3926_ == 0)
{
v___x_3921_ = v___x_3884_;
v_isShared_3922_ = v_isSharedCheck_3926_;
goto v_resetjp_3920_;
}
else
{
lean_inc(v_a_3919_);
lean_dec(v___x_3884_);
v___x_3921_ = lean_box(0);
v_isShared_3922_ = v_isSharedCheck_3926_;
goto v_resetjp_3920_;
}
v_resetjp_3920_:
{
lean_object* v___x_3924_; 
if (v_isShared_3922_ == 0)
{
v___x_3924_ = v___x_3921_;
goto v_reusejp_3923_;
}
else
{
lean_object* v_reuseFailAlloc_3925_; 
v_reuseFailAlloc_3925_ = lean_alloc_ctor(1, 1, 0);
lean_ctor_set(v_reuseFailAlloc_3925_, 0, v_a_3919_);
v___x_3924_ = v_reuseFailAlloc_3925_;
goto v_reusejp_3923_;
}
v_reusejp_3923_:
{
return v___x_3924_;
}
}
}
}
}
}
v___jp_3770_:
{
size_t v___x_3772_; size_t v___x_3773_; 
v___x_3772_ = ((size_t)1ULL);
v___x_3773_ = lean_usize_add(v_i_3767_, v___x_3772_);
v_i_3767_ = v___x_3773_;
v_b_3768_ = v_a_3771_;
goto _start;
}
v___jp_3775_:
{
lean_object* v___x_3776_; lean_object* v___x_3777_; 
v___x_3776_ = lean_unsigned_to_nat(1u);
v___x_3777_ = lean_nat_add(v_b_3768_, v___x_3776_);
lean_dec(v_b_3768_);
v_a_3771_ = v___x_3777_;
goto v___jp_3770_;
}
v___jp_3778_:
{
lean_object* v___x_3779_; lean_object* v___x_3780_; 
v___x_3779_ = ((lean_object*)(lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotCostHarness_run_spec__0___closed__1));
v___x_3780_ = lean_alloc_ctor(1, 1, 0);
lean_ctor_set(v___x_3780_, 0, v___x_3779_);
return v___x_3780_;
}
}
}
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotCostHarness_run_spec__0___boxed(lean_object* v_val_3930_, lean_object* v_a_3931_, lean_object* v_a_3932_, lean_object* v_a_3933_, lean_object* v_as_3934_, lean_object* v_sz_3935_, lean_object* v_i_3936_, lean_object* v_b_3937_, lean_object* v___y_3938_){
_start:
{
size_t v_sz_boxed_3939_; size_t v_i_boxed_3940_; lean_object* v_res_3941_; 
v_sz_boxed_3939_ = lean_unbox_usize(v_sz_3935_);
lean_dec(v_sz_3935_);
v_i_boxed_3940_ = lean_unbox_usize(v_i_3936_);
lean_dec(v_i_3936_);
v_res_3941_ = lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotCostHarness_run_spec__0(v_val_3930_, v_a_3931_, v_a_3932_, v_a_3933_, v_as_3934_, v_sz_boxed_3939_, v_i_boxed_3940_, v_b_3937_);
lean_dec_ref(v_as_3934_);
lean_dec_ref(v_a_3933_);
lean_dec_ref(v_a_3932_);
lean_dec_ref(v_a_3931_);
lean_dec(v_val_3930_);
return v_res_3941_;
}
}
static lean_object* _init_lp_competition_R24DotCostHarness_run___boxed__const__1(void){
_start:
{
uint32_t v___x_3974_; lean_object* v___x_3975_; 
v___x_3974_ = 0;
v___x_3975_ = lean_box_uint32(v___x_3974_);
return v___x_3975_;
}
}
LEAN_EXPORT lean_object* lp_competition_R24DotCostHarness_run(){
_start:
{
lean_object* v___x_3977_; lean_object* v___x_3978_; 
v___x_3977_ = ((lean_object*)(lp_competition_R24DotCostHarness_run___closed__0));
v___x_3978_ = lp_competition_R24DotCostHarness_env(v___x_3977_);
if (lean_obj_tag(v___x_3978_) == 0)
{
lean_object* v_a_3979_; lean_object* v___x_3981_; uint8_t v_isShared_3982_; uint8_t v_isSharedCheck_4215_; 
v_a_3979_ = lean_ctor_get(v___x_3978_, 0);
v_isSharedCheck_4215_ = !lean_is_exclusive(v___x_3978_);
if (v_isSharedCheck_4215_ == 0)
{
v___x_3981_ = v___x_3978_;
v_isShared_3982_ = v_isSharedCheck_4215_;
goto v_resetjp_3980_;
}
else
{
lean_inc(v_a_3979_);
lean_dec(v___x_3978_);
v___x_3981_ = lean_box(0);
v_isShared_3982_ = v_isSharedCheck_4215_;
goto v_resetjp_3980_;
}
v_resetjp_3980_:
{
lean_object* v___x_3983_; 
v___x_3983_ = l_IO_FS_readFile(v_a_3979_);
lean_dec(v_a_3979_);
if (lean_obj_tag(v___x_3983_) == 0)
{
lean_object* v_a_3984_; lean_object* v___x_3986_; uint8_t v_isShared_3987_; uint8_t v_isSharedCheck_4206_; 
v_a_3984_ = lean_ctor_get(v___x_3983_, 0);
v_isSharedCheck_4206_ = !lean_is_exclusive(v___x_3983_);
if (v_isSharedCheck_4206_ == 0)
{
v___x_3986_ = v___x_3983_;
v_isShared_3987_ = v_isSharedCheck_4206_;
goto v_resetjp_3985_;
}
else
{
lean_inc(v_a_3984_);
lean_dec(v___x_3983_);
v___x_3986_ = lean_box(0);
v_isShared_3987_ = v_isSharedCheck_4206_;
goto v_resetjp_3985_;
}
v_resetjp_3985_:
{
lean_object* v_a_3989_; lean_object* v___x_3996_; 
v___x_3996_ = l_Lean_Json_parse(v_a_3984_);
if (lean_obj_tag(v___x_3996_) == 0)
{
lean_object* v_a_3997_; 
lean_del_object(v___x_3981_);
v_a_3997_ = lean_ctor_get(v___x_3996_, 0);
lean_inc(v_a_3997_);
lean_dec_ref_known(v___x_3996_, 1);
v_a_3989_ = v_a_3997_;
goto v___jp_3988_;
}
else
{
lean_object* v_a_3998_; lean_object* v___x_4000_; uint8_t v_isShared_4001_; uint8_t v_isSharedCheck_4205_; 
v_a_3998_ = lean_ctor_get(v___x_3996_, 0);
v_isSharedCheck_4205_ = !lean_is_exclusive(v___x_3996_);
if (v_isSharedCheck_4205_ == 0)
{
v___x_4000_ = v___x_3996_;
v_isShared_4001_ = v_isSharedCheck_4205_;
goto v_resetjp_3999_;
}
else
{
lean_inc(v_a_3998_);
lean_dec(v___x_3996_);
v___x_4000_ = lean_box(0);
v_isShared_4001_ = v_isSharedCheck_4205_;
goto v_resetjp_3999_;
}
v_resetjp_3999_:
{
lean_object* v___x_4002_; 
v___x_4002_ = lp_competition_R24DotCostHarness_instFromJsonPlan_fromJson(v_a_3998_);
if (lean_obj_tag(v___x_4002_) == 0)
{
lean_object* v_a_4003_; 
lean_del_object(v___x_4000_);
lean_del_object(v___x_3981_);
v_a_4003_ = lean_ctor_get(v___x_4002_, 0);
lean_inc(v_a_4003_);
lean_dec_ref_known(v___x_4002_, 1);
v_a_3989_ = v_a_4003_;
goto v___jp_3988_;
}
else
{
lean_object* v_a_4004_; lean_object* v___x_4006_; uint8_t v_isShared_4007_; uint8_t v_isSharedCheck_4204_; 
lean_del_object(v___x_3986_);
v_a_4004_ = lean_ctor_get(v___x_4002_, 0);
v_isSharedCheck_4204_ = !lean_is_exclusive(v___x_4002_);
if (v_isSharedCheck_4204_ == 0)
{
v___x_4006_ = v___x_4002_;
v_isShared_4007_ = v_isSharedCheck_4204_;
goto v_resetjp_4005_;
}
else
{
lean_inc(v_a_4004_);
lean_dec(v___x_4002_);
v___x_4006_ = lean_box(0);
v_isShared_4007_ = v_isSharedCheck_4204_;
goto v_resetjp_4005_;
}
v_resetjp_4005_:
{
lean_object* v___y_4009_; lean_object* v___y_4010_; lean_object* v___y_4011_; lean_object* v___y_4012_; lean_object* v___y_4072_; lean_object* v___y_4073_; lean_object* v___y_4074_; lean_object* v___y_4080_; lean_object* v___y_4081_; lean_object* v___y_4082_; uint8_t v___y_4083_; lean_object* v___y_4091_; lean_object* v___y_4092_; lean_object* v___y_4093_; uint8_t v___y_4094_; uint8_t v___y_4095_; lean_object* v___y_4099_; lean_object* v___y_4100_; uint8_t v___y_4101_; lean_object* v___y_4102_; uint8_t v___y_4103_; lean_object* v___y_4111_; lean_object* v___y_4112_; uint8_t v___y_4113_; lean_object* v___y_4114_; uint8_t v___y_4115_; uint8_t v___y_4116_; lean_object* v___y_4120_; lean_object* v___y_4121_; lean_object* v___y_4122_; uint8_t v___y_4123_; uint8_t v___y_4124_; lean_object* v___y_4128_; lean_object* v___y_4129_; uint8_t v___y_4130_; lean_object* v___y_4131_; uint8_t v___y_4132_; uint8_t v___y_4133_; lean_object* v___x_4138_; lean_object* v___x_4139_; lean_object* v___y_4144_; 
v___x_4138_ = ((lean_object*)(lp_competition_R24DotCostHarness_run___closed__17));
v___x_4139_ = lean_io_getenv(v___x_4138_);
if (lean_obj_tag(v___x_4139_) == 0)
{
lean_object* v___x_4202_; 
v___x_4202_ = ((lean_object*)(lp_competition_R24DotCostHarness_run___closed__20));
v___y_4144_ = v___x_4202_;
goto v___jp_4143_;
}
else
{
lean_object* v_val_4203_; 
v_val_4203_ = lean_ctor_get(v___x_4139_, 0);
lean_inc(v_val_4203_);
lean_dec_ref_known(v___x_4139_, 1);
v___y_4144_ = v_val_4203_;
goto v___jp_4143_;
}
v___jp_4008_:
{
lean_object* v___x_4013_; lean_object* v___x_4014_; lean_object* v___x_4015_; lean_object* v___x_4016_; 
v___x_4013_ = lean_unsigned_to_nat(0u);
v___x_4014_ = lean_string_utf8_byte_size(v___y_4012_);
v___x_4015_ = lean_alloc_ctor(0, 3, 0);
lean_ctor_set(v___x_4015_, 0, v___y_4012_);
lean_ctor_set(v___x_4015_, 1, v___x_4013_);
lean_ctor_set(v___x_4015_, 2, v___x_4014_);
v___x_4016_ = l_String_Slice_toNat_x3f(v___x_4015_);
lean_dec_ref_known(v___x_4015_, 3);
if (lean_obj_tag(v___x_4016_) == 1)
{
lean_object* v_val_4017_; lean_object* v___x_4018_; uint8_t v___x_4019_; 
v_val_4017_ = lean_ctor_get(v___x_4016_, 0);
lean_inc(v_val_4017_);
lean_dec_ref_known(v___x_4016_, 1);
v___x_4018_ = lean_unsigned_to_nat(16777216u);
v___x_4019_ = lean_nat_dec_lt(v___x_4018_, v_val_4017_);
if (v___x_4019_ == 0)
{
lean_object* v_cases_4020_; size_t v_sz_4021_; size_t v___x_4022_; lean_object* v___x_4023_; 
lean_del_object(v___x_3981_);
v_cases_4020_ = lean_ctor_get(v_a_4004_, 0);
lean_inc_ref(v_cases_4020_);
lean_dec(v_a_4004_);
v_sz_4021_ = lean_array_size(v_cases_4020_);
v___x_4022_ = ((size_t)0ULL);
v___x_4023_ = lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotCostHarness_run_spec__0(v_val_4017_, v___y_4009_, v___y_4011_, v___y_4010_, v_cases_4020_, v_sz_4021_, v___x_4022_, v___x_4013_);
lean_dec_ref(v_cases_4020_);
lean_dec(v_val_4017_);
if (lean_obj_tag(v___x_4023_) == 0)
{
lean_object* v_a_4024_; lean_object* v___x_4025_; lean_object* v___x_4026_; lean_object* v___x_4027_; lean_object* v___x_4028_; lean_object* v___x_4029_; lean_object* v___x_4030_; lean_object* v___x_4031_; lean_object* v___x_4032_; lean_object* v___x_4033_; lean_object* v___x_4034_; lean_object* v___x_4035_; lean_object* v___x_4036_; lean_object* v___x_4037_; 
v_a_4024_ = lean_ctor_get(v___x_4023_, 0);
lean_inc(v_a_4024_);
lean_dec_ref_known(v___x_4023_, 1);
v___x_4025_ = ((lean_object*)(lp_competition_R24DotCostHarness_run___closed__2));
v___x_4026_ = lean_string_append(v___x_4025_, v___y_4010_);
lean_dec_ref(v___y_4010_);
v___x_4027_ = ((lean_object*)(lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotCostHarness_emit_spec__0___closed__1));
v___x_4028_ = lean_string_append(v___x_4026_, v___x_4027_);
v___x_4029_ = lean_string_append(v___x_4028_, v___y_4009_);
lean_dec_ref(v___y_4009_);
v___x_4030_ = lean_string_append(v___x_4029_, v___x_4027_);
v___x_4031_ = lean_string_append(v___x_4030_, v___y_4011_);
lean_dec_ref(v___y_4011_);
v___x_4032_ = lean_string_append(v___x_4031_, v___x_4027_);
v___x_4033_ = l_Nat_reprFast(v_a_4024_);
v___x_4034_ = lean_string_append(v___x_4032_, v___x_4033_);
lean_dec_ref(v___x_4033_);
v___x_4035_ = ((lean_object*)(lp_competition_R24DotCostHarness_run___closed__3));
v___x_4036_ = lean_string_append(v___x_4034_, v___x_4035_);
v___x_4037_ = lp_batteries_IO_println___at___00Batteries_Tactic_Lint_lintCore_spec__4(v___x_4036_);
if (lean_obj_tag(v___x_4037_) == 0)
{
lean_object* v___x_4039_; uint8_t v_isShared_4040_; uint8_t v_isSharedCheck_4045_; 
v_isSharedCheck_4045_ = !lean_is_exclusive(v___x_4037_);
if (v_isSharedCheck_4045_ == 0)
{
lean_object* v_unused_4046_; 
v_unused_4046_ = lean_ctor_get(v___x_4037_, 0);
lean_dec(v_unused_4046_);
v___x_4039_ = v___x_4037_;
v_isShared_4040_ = v_isSharedCheck_4045_;
goto v_resetjp_4038_;
}
else
{
lean_dec(v___x_4037_);
v___x_4039_ = lean_box(0);
v_isShared_4040_ = v_isSharedCheck_4045_;
goto v_resetjp_4038_;
}
v_resetjp_4038_:
{
lean_object* v___x_4041_; lean_object* v___x_4043_; 
v___x_4041_ = lp_competition_R24DotCostHarness_run___boxed__const__1;
if (v_isShared_4040_ == 0)
{
lean_ctor_set(v___x_4039_, 0, v___x_4041_);
v___x_4043_ = v___x_4039_;
goto v_reusejp_4042_;
}
else
{
lean_object* v_reuseFailAlloc_4044_; 
v_reuseFailAlloc_4044_ = lean_alloc_ctor(0, 1, 0);
lean_ctor_set(v_reuseFailAlloc_4044_, 0, v___x_4041_);
v___x_4043_ = v_reuseFailAlloc_4044_;
goto v_reusejp_4042_;
}
v_reusejp_4042_:
{
return v___x_4043_;
}
}
}
else
{
lean_object* v_a_4047_; lean_object* v___x_4049_; uint8_t v_isShared_4050_; uint8_t v_isSharedCheck_4054_; 
v_a_4047_ = lean_ctor_get(v___x_4037_, 0);
v_isSharedCheck_4054_ = !lean_is_exclusive(v___x_4037_);
if (v_isSharedCheck_4054_ == 0)
{
v___x_4049_ = v___x_4037_;
v_isShared_4050_ = v_isSharedCheck_4054_;
goto v_resetjp_4048_;
}
else
{
lean_inc(v_a_4047_);
lean_dec(v___x_4037_);
v___x_4049_ = lean_box(0);
v_isShared_4050_ = v_isSharedCheck_4054_;
goto v_resetjp_4048_;
}
v_resetjp_4048_:
{
lean_object* v___x_4052_; 
if (v_isShared_4050_ == 0)
{
v___x_4052_ = v___x_4049_;
goto v_reusejp_4051_;
}
else
{
lean_object* v_reuseFailAlloc_4053_; 
v_reuseFailAlloc_4053_ = lean_alloc_ctor(1, 1, 0);
lean_ctor_set(v_reuseFailAlloc_4053_, 0, v_a_4047_);
v___x_4052_ = v_reuseFailAlloc_4053_;
goto v_reusejp_4051_;
}
v_reusejp_4051_:
{
return v___x_4052_;
}
}
}
}
else
{
lean_object* v_a_4055_; lean_object* v___x_4057_; uint8_t v_isShared_4058_; uint8_t v_isSharedCheck_4062_; 
lean_dec_ref(v___y_4011_);
lean_dec_ref(v___y_4010_);
lean_dec_ref(v___y_4009_);
v_a_4055_ = lean_ctor_get(v___x_4023_, 0);
v_isSharedCheck_4062_ = !lean_is_exclusive(v___x_4023_);
if (v_isSharedCheck_4062_ == 0)
{
v___x_4057_ = v___x_4023_;
v_isShared_4058_ = v_isSharedCheck_4062_;
goto v_resetjp_4056_;
}
else
{
lean_inc(v_a_4055_);
lean_dec(v___x_4023_);
v___x_4057_ = lean_box(0);
v_isShared_4058_ = v_isSharedCheck_4062_;
goto v_resetjp_4056_;
}
v_resetjp_4056_:
{
lean_object* v___x_4060_; 
if (v_isShared_4058_ == 0)
{
v___x_4060_ = v___x_4057_;
goto v_reusejp_4059_;
}
else
{
lean_object* v_reuseFailAlloc_4061_; 
v_reuseFailAlloc_4061_ = lean_alloc_ctor(1, 1, 0);
lean_ctor_set(v_reuseFailAlloc_4061_, 0, v_a_4055_);
v___x_4060_ = v_reuseFailAlloc_4061_;
goto v_reusejp_4059_;
}
v_reusejp_4059_:
{
return v___x_4060_;
}
}
}
}
else
{
lean_object* v___x_4063_; lean_object* v___x_4065_; 
lean_dec(v_val_4017_);
lean_dec_ref(v___y_4011_);
lean_dec_ref(v___y_4010_);
lean_dec_ref(v___y_4009_);
lean_dec(v_a_4004_);
v___x_4063_ = ((lean_object*)(lp_competition_R24DotCostHarness_run___closed__5));
if (v_isShared_3982_ == 0)
{
lean_ctor_set_tag(v___x_3981_, 1);
lean_ctor_set(v___x_3981_, 0, v___x_4063_);
v___x_4065_ = v___x_3981_;
goto v_reusejp_4064_;
}
else
{
lean_object* v_reuseFailAlloc_4066_; 
v_reuseFailAlloc_4066_ = lean_alloc_ctor(1, 1, 0);
lean_ctor_set(v_reuseFailAlloc_4066_, 0, v___x_4063_);
v___x_4065_ = v_reuseFailAlloc_4066_;
goto v_reusejp_4064_;
}
v_reusejp_4064_:
{
return v___x_4065_;
}
}
}
else
{
lean_object* v___x_4067_; lean_object* v___x_4069_; 
lean_dec(v___x_4016_);
lean_dec_ref(v___y_4011_);
lean_dec_ref(v___y_4010_);
lean_dec_ref(v___y_4009_);
lean_dec(v_a_4004_);
v___x_4067_ = ((lean_object*)(lp_competition_R24DotCostHarness_run___closed__7));
if (v_isShared_3982_ == 0)
{
lean_ctor_set_tag(v___x_3981_, 1);
lean_ctor_set(v___x_3981_, 0, v___x_4067_);
v___x_4069_ = v___x_3981_;
goto v_reusejp_4068_;
}
else
{
lean_object* v_reuseFailAlloc_4070_; 
v_reuseFailAlloc_4070_ = lean_alloc_ctor(1, 1, 0);
lean_ctor_set(v_reuseFailAlloc_4070_, 0, v___x_4067_);
v___x_4069_ = v_reuseFailAlloc_4070_;
goto v_reusejp_4068_;
}
v_reusejp_4068_:
{
return v___x_4069_;
}
}
}
v___jp_4071_:
{
lean_object* v___x_4075_; lean_object* v___x_4076_; 
v___x_4075_ = ((lean_object*)(lp_competition_R24DotCostHarness_run___closed__8));
v___x_4076_ = lean_io_getenv(v___x_4075_);
if (lean_obj_tag(v___x_4076_) == 0)
{
lean_object* v___x_4077_; 
v___x_4077_ = ((lean_object*)(lp_competition_R24DotCostHarness_run___closed__9));
v___y_4009_ = v___y_4072_;
v___y_4010_ = v___y_4073_;
v___y_4011_ = v___y_4074_;
v___y_4012_ = v___x_4077_;
goto v___jp_4008_;
}
else
{
lean_object* v_val_4078_; 
v_val_4078_ = lean_ctor_get(v___x_4076_, 0);
lean_inc(v_val_4078_);
lean_dec_ref_known(v___x_4076_, 1);
v___y_4009_ = v___y_4072_;
v___y_4010_ = v___y_4073_;
v___y_4011_ = v___y_4074_;
v___y_4012_ = v_val_4078_;
goto v___jp_4008_;
}
}
v___jp_4079_:
{
if (v___y_4083_ == 0)
{
lean_del_object(v___x_4006_);
v___y_4072_ = v___y_4080_;
v___y_4073_ = v___y_4081_;
v___y_4074_ = v___y_4082_;
goto v___jp_4071_;
}
else
{
lean_object* v___x_4084_; uint8_t v___x_4085_; 
v___x_4084_ = ((lean_object*)(lp_competition_R24DotCostHarness_benchExactPrepared___closed__0));
v___x_4085_ = lean_string_dec_eq(v___y_4082_, v___x_4084_);
if (v___x_4085_ == 0)
{
lean_object* v___x_4086_; lean_object* v___x_4088_; 
lean_dec_ref(v___y_4082_);
lean_dec_ref(v___y_4081_);
lean_dec_ref(v___y_4080_);
lean_dec(v_a_4004_);
lean_del_object(v___x_3981_);
v___x_4086_ = ((lean_object*)(lp_competition_R24DotCostHarness_run___closed__11));
if (v_isShared_4007_ == 0)
{
lean_ctor_set(v___x_4006_, 0, v___x_4086_);
v___x_4088_ = v___x_4006_;
goto v_reusejp_4087_;
}
else
{
lean_object* v_reuseFailAlloc_4089_; 
v_reuseFailAlloc_4089_ = lean_alloc_ctor(1, 1, 0);
lean_ctor_set(v_reuseFailAlloc_4089_, 0, v___x_4086_);
v___x_4088_ = v_reuseFailAlloc_4089_;
goto v_reusejp_4087_;
}
v_reusejp_4087_:
{
return v___x_4088_;
}
}
else
{
lean_del_object(v___x_4006_);
v___y_4072_ = v___y_4080_;
v___y_4073_ = v___y_4081_;
v___y_4074_ = v___y_4082_;
goto v___jp_4071_;
}
}
}
v___jp_4090_:
{
lean_object* v___x_4096_; uint8_t v___x_4097_; 
v___x_4096_ = ((lean_object*)(lp_competition_R24DotCostHarness_benchExactFull___closed__3));
v___x_4097_ = lean_string_dec_eq(v___y_4093_, v___x_4096_);
if (v___x_4097_ == 0)
{
v___y_4080_ = v___y_4091_;
v___y_4081_ = v___y_4092_;
v___y_4082_ = v___y_4093_;
v___y_4083_ = v___y_4094_;
goto v___jp_4079_;
}
else
{
v___y_4080_ = v___y_4091_;
v___y_4081_ = v___y_4092_;
v___y_4082_ = v___y_4093_;
v___y_4083_ = v___y_4095_;
goto v___jp_4079_;
}
}
v___jp_4098_:
{
lean_object* v___x_4104_; uint8_t v___x_4105_; 
v___x_4104_ = ((lean_object*)(lp_competition_R24DotCostHarness_benchLazyFull___closed__0));
v___x_4105_ = lean_string_dec_eq(v___y_4099_, v___x_4104_);
if (v___x_4105_ == 0)
{
lean_object* v___x_4106_; lean_object* v___x_4108_; 
lean_dec_ref(v___y_4102_);
lean_dec_ref(v___y_4100_);
lean_dec_ref(v___y_4099_);
lean_del_object(v___x_4006_);
lean_dec(v_a_4004_);
lean_del_object(v___x_3981_);
v___x_4106_ = ((lean_object*)(lp_competition_R24DotCostHarness_run___closed__13));
if (v_isShared_4001_ == 0)
{
lean_ctor_set(v___x_4000_, 0, v___x_4106_);
v___x_4108_ = v___x_4000_;
goto v_reusejp_4107_;
}
else
{
lean_object* v_reuseFailAlloc_4109_; 
v_reuseFailAlloc_4109_ = lean_alloc_ctor(1, 1, 0);
lean_ctor_set(v_reuseFailAlloc_4109_, 0, v___x_4106_);
v___x_4108_ = v_reuseFailAlloc_4109_;
goto v_reusejp_4107_;
}
v_reusejp_4107_:
{
return v___x_4108_;
}
}
else
{
lean_del_object(v___x_4000_);
v___y_4091_ = v___y_4099_;
v___y_4092_ = v___y_4100_;
v___y_4093_ = v___y_4102_;
v___y_4094_ = v___y_4103_;
v___y_4095_ = v___y_4101_;
goto v___jp_4090_;
}
}
v___jp_4110_:
{
if (v___y_4116_ == 0)
{
lean_del_object(v___x_4000_);
v___y_4091_ = v___y_4111_;
v___y_4092_ = v___y_4112_;
v___y_4093_ = v___y_4114_;
v___y_4094_ = v___y_4115_;
v___y_4095_ = v___y_4116_;
goto v___jp_4090_;
}
else
{
lean_object* v___x_4117_; uint8_t v___x_4118_; 
v___x_4117_ = ((lean_object*)(lp_competition_R24DotCostHarness_benchEagerFull___closed__0));
v___x_4118_ = lean_string_dec_eq(v___y_4111_, v___x_4117_);
if (v___x_4118_ == 0)
{
v___y_4099_ = v___y_4111_;
v___y_4100_ = v___y_4112_;
v___y_4101_ = v___y_4113_;
v___y_4102_ = v___y_4114_;
v___y_4103_ = v___y_4115_;
goto v___jp_4098_;
}
else
{
if (v___y_4113_ == 0)
{
lean_del_object(v___x_4000_);
v___y_4091_ = v___y_4111_;
v___y_4092_ = v___y_4112_;
v___y_4093_ = v___y_4114_;
v___y_4094_ = v___y_4115_;
v___y_4095_ = v___y_4113_;
goto v___jp_4090_;
}
else
{
v___y_4099_ = v___y_4111_;
v___y_4100_ = v___y_4112_;
v___y_4101_ = v___y_4113_;
v___y_4102_ = v___y_4114_;
v___y_4103_ = v___y_4115_;
goto v___jp_4098_;
}
}
}
}
v___jp_4119_:
{
lean_object* v___x_4125_; uint8_t v___x_4126_; 
v___x_4125_ = ((lean_object*)(lp_competition_R24DotCostHarness_benchExactFull___closed__2));
v___x_4126_ = lean_string_dec_eq(v___y_4120_, v___x_4125_);
if (v___x_4126_ == 0)
{
v___y_4111_ = v___y_4120_;
v___y_4112_ = v___y_4121_;
v___y_4113_ = v___y_4124_;
v___y_4114_ = v___y_4122_;
v___y_4115_ = v___y_4123_;
v___y_4116_ = v___y_4123_;
goto v___jp_4110_;
}
else
{
v___y_4111_ = v___y_4120_;
v___y_4112_ = v___y_4121_;
v___y_4113_ = v___y_4124_;
v___y_4114_ = v___y_4122_;
v___y_4115_ = v___y_4123_;
v___y_4116_ = v___y_4124_;
goto v___jp_4110_;
}
}
v___jp_4127_:
{
if (v___y_4133_ == 0)
{
v___y_4120_ = v___y_4128_;
v___y_4121_ = v___y_4129_;
v___y_4122_ = v___y_4131_;
v___y_4123_ = v___y_4132_;
v___y_4124_ = v___y_4133_;
goto v___jp_4119_;
}
else
{
lean_object* v___x_4134_; uint8_t v___x_4135_; 
v___x_4134_ = ((lean_object*)(lp_competition_R24DotCostHarness_run___closed__14));
v___x_4135_ = lean_string_dec_eq(v___y_4129_, v___x_4134_);
if (v___x_4135_ == 0)
{
lean_object* v___x_4136_; lean_object* v___x_4137_; 
lean_dec_ref(v___y_4131_);
lean_dec_ref(v___y_4129_);
lean_dec_ref(v___y_4128_);
lean_del_object(v___x_4006_);
lean_dec(v_a_4004_);
lean_del_object(v___x_4000_);
lean_del_object(v___x_3981_);
v___x_4136_ = ((lean_object*)(lp_competition_R24DotCostHarness_run___closed__16));
v___x_4137_ = lean_alloc_ctor(1, 1, 0);
lean_ctor_set(v___x_4137_, 0, v___x_4136_);
return v___x_4137_;
}
else
{
v___y_4120_ = v___y_4128_;
v___y_4121_ = v___y_4129_;
v___y_4122_ = v___y_4131_;
v___y_4123_ = v___y_4132_;
v___y_4124_ = v___y_4130_;
goto v___jp_4119_;
}
}
}
v___jp_4140_:
{
lean_object* v___x_4141_; lean_object* v___x_4142_; 
v___x_4141_ = ((lean_object*)(lp_competition_R24DotCostHarness_run___closed__19));
v___x_4142_ = lean_alloc_ctor(1, 1, 0);
lean_ctor_set(v___x_4142_, 0, v___x_4141_);
return v___x_4142_;
}
v___jp_4143_:
{
lean_object* v___x_4145_; uint8_t v___x_4146_; 
v___x_4145_ = ((lean_object*)(lp_competition_R24DotCostHarness_run___closed__20));
v___x_4146_ = lean_string_dec_eq(v___y_4144_, v___x_4145_);
if (v___x_4146_ == 0)
{
lean_object* v___x_4147_; uint8_t v___x_4148_; 
v___x_4147_ = ((lean_object*)(lp_competition_R24DotCostHarness_run___closed__21));
v___x_4148_ = lean_string_dec_eq(v___y_4144_, v___x_4147_);
lean_dec_ref(v___y_4144_);
if (v___x_4148_ == 0)
{
lean_del_object(v___x_4006_);
lean_dec(v_a_4004_);
lean_del_object(v___x_4000_);
lean_del_object(v___x_3981_);
goto v___jp_4140_;
}
else
{
if (v___x_4146_ == 0)
{
lean_object* v___x_4149_; lean_object* v___x_4150_; 
v___x_4149_ = ((lean_object*)(lp_competition_R24DotCostHarness_run___closed__22));
v___x_4150_ = lp_competition_R24DotCostHarness_env(v___x_4149_);
if (lean_obj_tag(v___x_4150_) == 0)
{
lean_object* v_a_4151_; lean_object* v___x_4152_; lean_object* v___x_4153_; 
v_a_4151_ = lean_ctor_get(v___x_4150_, 0);
lean_inc(v_a_4151_);
lean_dec_ref_known(v___x_4150_, 1);
v___x_4152_ = ((lean_object*)(lp_competition_R24DotCostHarness_run___closed__23));
v___x_4153_ = lp_competition_R24DotCostHarness_env(v___x_4152_);
if (lean_obj_tag(v___x_4153_) == 0)
{
lean_object* v_a_4154_; lean_object* v___x_4155_; lean_object* v___x_4156_; 
v_a_4154_ = lean_ctor_get(v___x_4153_, 0);
lean_inc(v_a_4154_);
lean_dec_ref_known(v___x_4153_, 1);
v___x_4155_ = ((lean_object*)(lp_competition_R24DotCostHarness_run___closed__24));
v___x_4156_ = lp_competition_R24DotCostHarness_env(v___x_4155_);
if (lean_obj_tag(v___x_4156_) == 0)
{
lean_object* v_a_4157_; lean_object* v___x_4158_; uint8_t v___x_4159_; 
v_a_4157_ = lean_ctor_get(v___x_4156_, 0);
lean_inc(v_a_4157_);
lean_dec_ref_known(v___x_4156_, 1);
v___x_4158_ = ((lean_object*)(lp_competition_R24DotCostHarness_run___closed__25));
v___x_4159_ = lean_string_dec_eq(v_a_4151_, v___x_4158_);
if (v___x_4159_ == 0)
{
v___y_4128_ = v_a_4154_;
v___y_4129_ = v_a_4151_;
v___y_4130_ = v___x_4146_;
v___y_4131_ = v_a_4157_;
v___y_4132_ = v___x_4148_;
v___y_4133_ = v___x_4148_;
goto v___jp_4127_;
}
else
{
v___y_4128_ = v_a_4154_;
v___y_4129_ = v_a_4151_;
v___y_4130_ = v___x_4146_;
v___y_4131_ = v_a_4157_;
v___y_4132_ = v___x_4148_;
v___y_4133_ = v___x_4146_;
goto v___jp_4127_;
}
}
else
{
lean_object* v_a_4160_; lean_object* v___x_4162_; uint8_t v_isShared_4163_; uint8_t v_isSharedCheck_4167_; 
lean_dec(v_a_4154_);
lean_dec(v_a_4151_);
lean_del_object(v___x_4006_);
lean_dec(v_a_4004_);
lean_del_object(v___x_4000_);
lean_del_object(v___x_3981_);
v_a_4160_ = lean_ctor_get(v___x_4156_, 0);
v_isSharedCheck_4167_ = !lean_is_exclusive(v___x_4156_);
if (v_isSharedCheck_4167_ == 0)
{
v___x_4162_ = v___x_4156_;
v_isShared_4163_ = v_isSharedCheck_4167_;
goto v_resetjp_4161_;
}
else
{
lean_inc(v_a_4160_);
lean_dec(v___x_4156_);
v___x_4162_ = lean_box(0);
v_isShared_4163_ = v_isSharedCheck_4167_;
goto v_resetjp_4161_;
}
v_resetjp_4161_:
{
lean_object* v___x_4165_; 
if (v_isShared_4163_ == 0)
{
v___x_4165_ = v___x_4162_;
goto v_reusejp_4164_;
}
else
{
lean_object* v_reuseFailAlloc_4166_; 
v_reuseFailAlloc_4166_ = lean_alloc_ctor(1, 1, 0);
lean_ctor_set(v_reuseFailAlloc_4166_, 0, v_a_4160_);
v___x_4165_ = v_reuseFailAlloc_4166_;
goto v_reusejp_4164_;
}
v_reusejp_4164_:
{
return v___x_4165_;
}
}
}
}
else
{
lean_object* v_a_4168_; lean_object* v___x_4170_; uint8_t v_isShared_4171_; uint8_t v_isSharedCheck_4175_; 
lean_dec(v_a_4151_);
lean_del_object(v___x_4006_);
lean_dec(v_a_4004_);
lean_del_object(v___x_4000_);
lean_del_object(v___x_3981_);
v_a_4168_ = lean_ctor_get(v___x_4153_, 0);
v_isSharedCheck_4175_ = !lean_is_exclusive(v___x_4153_);
if (v_isSharedCheck_4175_ == 0)
{
v___x_4170_ = v___x_4153_;
v_isShared_4171_ = v_isSharedCheck_4175_;
goto v_resetjp_4169_;
}
else
{
lean_inc(v_a_4168_);
lean_dec(v___x_4153_);
v___x_4170_ = lean_box(0);
v_isShared_4171_ = v_isSharedCheck_4175_;
goto v_resetjp_4169_;
}
v_resetjp_4169_:
{
lean_object* v___x_4173_; 
if (v_isShared_4171_ == 0)
{
v___x_4173_ = v___x_4170_;
goto v_reusejp_4172_;
}
else
{
lean_object* v_reuseFailAlloc_4174_; 
v_reuseFailAlloc_4174_ = lean_alloc_ctor(1, 1, 0);
lean_ctor_set(v_reuseFailAlloc_4174_, 0, v_a_4168_);
v___x_4173_ = v_reuseFailAlloc_4174_;
goto v_reusejp_4172_;
}
v_reusejp_4172_:
{
return v___x_4173_;
}
}
}
}
else
{
lean_object* v_a_4176_; lean_object* v___x_4178_; uint8_t v_isShared_4179_; uint8_t v_isSharedCheck_4183_; 
lean_del_object(v___x_4006_);
lean_dec(v_a_4004_);
lean_del_object(v___x_4000_);
lean_del_object(v___x_3981_);
v_a_4176_ = lean_ctor_get(v___x_4150_, 0);
v_isSharedCheck_4183_ = !lean_is_exclusive(v___x_4150_);
if (v_isSharedCheck_4183_ == 0)
{
v___x_4178_ = v___x_4150_;
v_isShared_4179_ = v_isSharedCheck_4183_;
goto v_resetjp_4177_;
}
else
{
lean_inc(v_a_4176_);
lean_dec(v___x_4150_);
v___x_4178_ = lean_box(0);
v_isShared_4179_ = v_isSharedCheck_4183_;
goto v_resetjp_4177_;
}
v_resetjp_4177_:
{
lean_object* v___x_4181_; 
if (v_isShared_4179_ == 0)
{
v___x_4181_ = v___x_4178_;
goto v_reusejp_4180_;
}
else
{
lean_object* v_reuseFailAlloc_4182_; 
v_reuseFailAlloc_4182_ = lean_alloc_ctor(1, 1, 0);
lean_ctor_set(v_reuseFailAlloc_4182_, 0, v_a_4176_);
v___x_4181_ = v_reuseFailAlloc_4182_;
goto v_reusejp_4180_;
}
v_reusejp_4180_:
{
return v___x_4181_;
}
}
}
}
else
{
lean_del_object(v___x_4006_);
lean_dec(v_a_4004_);
lean_del_object(v___x_4000_);
lean_del_object(v___x_3981_);
goto v___jp_4140_;
}
}
}
else
{
lean_object* v___x_4184_; 
lean_dec_ref(v___y_4144_);
lean_del_object(v___x_4006_);
lean_del_object(v___x_4000_);
lean_del_object(v___x_3981_);
v___x_4184_ = lp_competition_R24DotCostHarness_verify(v_a_4004_);
lean_dec(v_a_4004_);
if (lean_obj_tag(v___x_4184_) == 0)
{
lean_object* v___x_4186_; uint8_t v_isShared_4187_; uint8_t v_isSharedCheck_4192_; 
v_isSharedCheck_4192_ = !lean_is_exclusive(v___x_4184_);
if (v_isSharedCheck_4192_ == 0)
{
lean_object* v_unused_4193_; 
v_unused_4193_ = lean_ctor_get(v___x_4184_, 0);
lean_dec(v_unused_4193_);
v___x_4186_ = v___x_4184_;
v_isShared_4187_ = v_isSharedCheck_4192_;
goto v_resetjp_4185_;
}
else
{
lean_dec(v___x_4184_);
v___x_4186_ = lean_box(0);
v_isShared_4187_ = v_isSharedCheck_4192_;
goto v_resetjp_4185_;
}
v_resetjp_4185_:
{
lean_object* v___x_4188_; lean_object* v___x_4190_; 
v___x_4188_ = lp_competition_R24DotCostHarness_run___boxed__const__1;
if (v_isShared_4187_ == 0)
{
lean_ctor_set(v___x_4186_, 0, v___x_4188_);
v___x_4190_ = v___x_4186_;
goto v_reusejp_4189_;
}
else
{
lean_object* v_reuseFailAlloc_4191_; 
v_reuseFailAlloc_4191_ = lean_alloc_ctor(0, 1, 0);
lean_ctor_set(v_reuseFailAlloc_4191_, 0, v___x_4188_);
v___x_4190_ = v_reuseFailAlloc_4191_;
goto v_reusejp_4189_;
}
v_reusejp_4189_:
{
return v___x_4190_;
}
}
}
else
{
lean_object* v_a_4194_; lean_object* v___x_4196_; uint8_t v_isShared_4197_; uint8_t v_isSharedCheck_4201_; 
v_a_4194_ = lean_ctor_get(v___x_4184_, 0);
v_isSharedCheck_4201_ = !lean_is_exclusive(v___x_4184_);
if (v_isSharedCheck_4201_ == 0)
{
v___x_4196_ = v___x_4184_;
v_isShared_4197_ = v_isSharedCheck_4201_;
goto v_resetjp_4195_;
}
else
{
lean_inc(v_a_4194_);
lean_dec(v___x_4184_);
v___x_4196_ = lean_box(0);
v_isShared_4197_ = v_isSharedCheck_4201_;
goto v_resetjp_4195_;
}
v_resetjp_4195_:
{
lean_object* v___x_4199_; 
if (v_isShared_4197_ == 0)
{
v___x_4199_ = v___x_4196_;
goto v_reusejp_4198_;
}
else
{
lean_object* v_reuseFailAlloc_4200_; 
v_reuseFailAlloc_4200_ = lean_alloc_ctor(1, 1, 0);
lean_ctor_set(v_reuseFailAlloc_4200_, 0, v_a_4194_);
v___x_4199_ = v_reuseFailAlloc_4200_;
goto v_reusejp_4198_;
}
v_reusejp_4198_:
{
return v___x_4199_;
}
}
}
}
}
}
}
}
}
v___jp_3988_:
{
lean_object* v___x_3990_; lean_object* v___x_3991_; lean_object* v___x_3992_; lean_object* v___x_3994_; 
v___x_3990_ = ((lean_object*)(lp_competition_R24DotCostHarness_run___closed__1));
v___x_3991_ = lean_string_append(v___x_3990_, v_a_3989_);
lean_dec_ref(v_a_3989_);
v___x_3992_ = lean_alloc_ctor(18, 1, 0);
lean_ctor_set(v___x_3992_, 0, v___x_3991_);
if (v_isShared_3987_ == 0)
{
lean_ctor_set_tag(v___x_3986_, 1);
lean_ctor_set(v___x_3986_, 0, v___x_3992_);
v___x_3994_ = v___x_3986_;
goto v_reusejp_3993_;
}
else
{
lean_object* v_reuseFailAlloc_3995_; 
v_reuseFailAlloc_3995_ = lean_alloc_ctor(1, 1, 0);
lean_ctor_set(v_reuseFailAlloc_3995_, 0, v___x_3992_);
v___x_3994_ = v_reuseFailAlloc_3995_;
goto v_reusejp_3993_;
}
v_reusejp_3993_:
{
return v___x_3994_;
}
}
}
}
else
{
lean_object* v_a_4207_; lean_object* v___x_4209_; uint8_t v_isShared_4210_; uint8_t v_isSharedCheck_4214_; 
lean_del_object(v___x_3981_);
v_a_4207_ = lean_ctor_get(v___x_3983_, 0);
v_isSharedCheck_4214_ = !lean_is_exclusive(v___x_3983_);
if (v_isSharedCheck_4214_ == 0)
{
v___x_4209_ = v___x_3983_;
v_isShared_4210_ = v_isSharedCheck_4214_;
goto v_resetjp_4208_;
}
else
{
lean_inc(v_a_4207_);
lean_dec(v___x_3983_);
v___x_4209_ = lean_box(0);
v_isShared_4210_ = v_isSharedCheck_4214_;
goto v_resetjp_4208_;
}
v_resetjp_4208_:
{
lean_object* v___x_4212_; 
if (v_isShared_4210_ == 0)
{
v___x_4212_ = v___x_4209_;
goto v_reusejp_4211_;
}
else
{
lean_object* v_reuseFailAlloc_4213_; 
v_reuseFailAlloc_4213_ = lean_alloc_ctor(1, 1, 0);
lean_ctor_set(v_reuseFailAlloc_4213_, 0, v_a_4207_);
v___x_4212_ = v_reuseFailAlloc_4213_;
goto v_reusejp_4211_;
}
v_reusejp_4211_:
{
return v___x_4212_;
}
}
}
}
}
else
{
lean_object* v_a_4216_; lean_object* v___x_4218_; uint8_t v_isShared_4219_; uint8_t v_isSharedCheck_4223_; 
v_a_4216_ = lean_ctor_get(v___x_3978_, 0);
v_isSharedCheck_4223_ = !lean_is_exclusive(v___x_3978_);
if (v_isSharedCheck_4223_ == 0)
{
v___x_4218_ = v___x_3978_;
v_isShared_4219_ = v_isSharedCheck_4223_;
goto v_resetjp_4217_;
}
else
{
lean_inc(v_a_4216_);
lean_dec(v___x_3978_);
v___x_4218_ = lean_box(0);
v_isShared_4219_ = v_isSharedCheck_4223_;
goto v_resetjp_4217_;
}
v_resetjp_4217_:
{
lean_object* v___x_4221_; 
if (v_isShared_4219_ == 0)
{
v___x_4221_ = v___x_4218_;
goto v_reusejp_4220_;
}
else
{
lean_object* v_reuseFailAlloc_4222_; 
v_reuseFailAlloc_4222_ = lean_alloc_ctor(1, 1, 0);
lean_ctor_set(v_reuseFailAlloc_4222_, 0, v_a_4216_);
v___x_4221_ = v_reuseFailAlloc_4222_;
goto v_reusejp_4220_;
}
v_reusejp_4220_:
{
return v___x_4221_;
}
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_R24DotCostHarness_run___boxed(lean_object* v_a_4224_){
_start:
{
lean_object* v_res_4225_; 
v_res_4225_ = lp_competition_R24DotCostHarness_run();
return v_res_4225_;
}
}
LEAN_EXPORT lean_object* _lean_main(){
_start:
{
lean_object* v___x_4227_; 
v___x_4227_ = lp_competition_R24DotCostHarness_run();
return v___x_4227_;
}
}
LEAN_EXPORT lean_object* lp_competition_main___boxed(lean_object* v_a_4228_){
_start:
{
lean_object* v_res_4229_; 
v_res_4229_ = _lean_main();
return v_res_4229_;
}
}
lean_object* initialize_Init(uint8_t builtin);
lean_object* initialize_Init(uint8_t builtin);
lean_object* initialize_competition_BenchFull(uint8_t builtin);
lean_object* initialize_competition_BenchSuite(uint8_t builtin);
lean_object* initialize_competition_Submission(uint8_t builtin);
lean_object* initialize_competition_R24DotBarrier(uint8_t builtin);
void lean_initialize();
static bool _G_initialized = false;
LEAN_EXPORT lean_object* initialize_competition_R24DotCostMain(uint8_t builtin) {
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
res = initialize_competition_BenchFull(builtin);
if (lean_io_result_is_error(res)) return res;
lean_dec_ref(res);
res = initialize_competition_BenchSuite(builtin);
if (lean_io_result_is_error(res)) return res;
lean_dec_ref(res);
res = initialize_competition_Submission(builtin);
if (lean_io_result_is_error(res)) return res;
lean_dec_ref(res);
res = initialize_competition_R24DotBarrier(builtin);
if (lean_io_result_is_error(res)) return res;
lean_dec_ref(res);
lp_competition_R24DotCostHarness_run___boxed__const__1 = _init_lp_competition_R24DotCostHarness_run___boxed__const__1();
lean_mark_persistent(lp_competition_R24DotCostHarness_run___boxed__const__1);
return lean_io_result_mk_ok(lean_box(0));
}
char ** lean_setup_args(int argc, char ** argv);
#if defined(WIN32) || defined(_WIN32)
#include <windows.h>
#endif
lean_object* run_main(int argc, char ** argv) {
    return _lean_main();
}
int main(int argc, char ** argv) {
#if defined(WIN32) || defined(_WIN32)
  SetErrorMode(SEM_FAILCRITICALERRORS);
  SetConsoleOutputCP(CP_UTF8);
#endif
  lean_object* res;
  argv = lean_setup_args(argc, argv);
  res = initialize_competition_R24DotCostMain(1 /* builtin */);
  lean_io_mark_end_initialization();
  if (lean_io_result_is_ok(res)) {
    lean_dec_ref(res);
    lean_init_task_manager();
    res = lean_run_main(&run_main, argc, argv);
  }
  lean_finalize_task_manager();
  if (lean_io_result_is_ok(res)) {
    int ret = lean_unbox_uint32(lean_io_result_get_value(res));
    lean_dec_ref(res);
    return ret;
  } else {
    lean_io_result_show_error(res);
    lean_dec_ref(res);
    return 1;
  }
}
#ifdef __cplusplus
}
#endif
