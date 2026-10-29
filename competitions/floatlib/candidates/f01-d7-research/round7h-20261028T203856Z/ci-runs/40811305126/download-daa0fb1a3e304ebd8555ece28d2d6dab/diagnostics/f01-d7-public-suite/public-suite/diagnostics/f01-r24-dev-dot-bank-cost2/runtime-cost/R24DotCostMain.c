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
lean_object* l_Lean_Name_mkStr1(lean_object*);
lean_object* l_Lean_Name_toStringWithToken___at___00Lean_Name_toString_spec__0(lean_object*, uint8_t);
lean_object* l_Lean_Name_mkStr2(lean_object*, lean_object*);
lean_object* lean_string_append(lean_object*, lean_object*);
lean_object* lean_nat_add(lean_object*, lean_object*);
lean_object* lean_nat_sub(lean_object*, lean_object*);
lean_object* lean_nat_div(lean_object*, lean_object*);
uint8_t lean_nat_dec_le(lean_object*, lean_object*);
lean_object* lean_array_get_size(lean_object*);
uint8_t lean_nat_dec_eq(lean_object*, lean_object*);
uint8_t lean_nat_dec_lt(lean_object*, lean_object*);
lean_object* lean_array_get_borrowed(lean_object*, lean_object*, lean_object*);
uint8_t lean_uint32_dec_eq(uint32_t, uint32_t);
lean_object* l_Nat_reprFast(lean_object*);
lean_object* lp_competition_Submission_R24GenericDotBank_lazyBank(lean_object*, lean_object*);
uint32_t lean_uint32_add(uint32_t, uint32_t);
lean_object* l_IO_lazyPure___redArg(lean_object*);
lean_object* lean_uint32_to_nat(uint32_t);
lean_object* lean_io_mono_nanos_now();
lean_object* lean_nat_mul(lean_object*, lean_object*);
uint32_t lean_uint32_of_nat(lean_object*);
lean_object* lp_competition_R24DotBarrier_touchBank(lean_object*, lean_object*);
uint32_t lean_uint32_mul(uint32_t, uint32_t);
lean_object* lean_array_push(lean_object*, lean_object*);
lean_object* lp_competition_Submission_R24GenericDotBank_eagerBank(lean_object*, lean_object*);
uint8_t lean_usize_dec_lt(size_t, size_t);
lean_object* lean_array_uget_borrowed(lean_object*, size_t);
lean_object* l_Lean_Array_fromJson_x3f___at___00Lean_Json_getObjValAs_x3f___at___00Lean_Lsp_instFromJsonSemanticTokens_fromJson_spec__0_spec__0(lean_object*);
lean_object* lean_array_uset(lean_object*, size_t, lean_object*);
size_t lean_usize_add(size_t, size_t);
uint8_t lean_usize_dec_eq(size_t, size_t);
size_t lean_usize_of_nat(lean_object*);
size_t lean_array_size(lean_object*);
lean_object* lean_array_uget(lean_object*, size_t);
lean_object* lp_competition_Submission_R24GenericDotBank_exactBank(lean_object*, lean_object*);
lean_object* lp_batteries_IO_println___at___00Batteries_Tactic_Lint_lintCore_spec__4(lean_object*);
lean_object* lean_io_getenv(lean_object*);
lean_object* l_IO_FS_readFile(lean_object*);
lean_object* l_Lean_Json_parse(lean_object*);
lean_object* l_Lean_Json_getObjValD(lean_object*, lean_object*);
lean_object* lp_proofwidgets_Lean_Json_getObjValAs_x3f___at___00ProofWidgets_MarkdownDisplay_instFromJsonProps_fromJson_spec__0(lean_object*, lean_object*);
lean_object* l_Lean_Json_getObjValAs_x3f___at___00Lean_Server_instFromJsonIlean_fromJson_spec__0(lean_object*, lean_object*);
lean_object* l_Lean_Json_pretty(lean_object*, lean_object*);
lean_object* l_Lean_Json_getObjValAs_x3f___at___00Lean_Lsp_instFromJsonSemanticTokens_fromJson_spec__0(lean_object*, lean_object*);
lean_object* lean_string_utf8_byte_size(lean_object*);
lean_object* l_String_Slice_toNat_x3f(lean_object*);
uint8_t lean_string_dec_eq(lean_object*, lean_object*);
lean_object* lean_mk_empty_array_with_capacity(lean_object*);
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_mapMUnsafe_map___at___00Lean_Array_fromJson_x3f___at___00Lean_Json_getObjValAs_x3f___at___00R24DotBankHarness_instFromJsonBankCase_fromJson_spec__0_spec__0_spec__1(size_t, size_t, lean_object*);
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_mapMUnsafe_map___at___00Lean_Array_fromJson_x3f___at___00Lean_Json_getObjValAs_x3f___at___00R24DotBankHarness_instFromJsonBankCase_fromJson_spec__0_spec__0_spec__1___boxed(lean_object*, lean_object*, lean_object*);
static const lean_string_object lp_competition_Lean_Array_fromJson_x3f___at___00Lean_Json_getObjValAs_x3f___at___00R24DotBankHarness_instFromJsonBankCase_fromJson_spec__0_spec__0___closed__0_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 27, .m_capacity = 27, .m_length = 26, .m_data = "expected JSON array, got '"};
static const lean_object* lp_competition_Lean_Array_fromJson_x3f___at___00Lean_Json_getObjValAs_x3f___at___00R24DotBankHarness_instFromJsonBankCase_fromJson_spec__0_spec__0___closed__0 = (const lean_object*)&lp_competition_Lean_Array_fromJson_x3f___at___00Lean_Json_getObjValAs_x3f___at___00R24DotBankHarness_instFromJsonBankCase_fromJson_spec__0_spec__0___closed__0_value;
static const lean_string_object lp_competition_Lean_Array_fromJson_x3f___at___00Lean_Json_getObjValAs_x3f___at___00R24DotBankHarness_instFromJsonBankCase_fromJson_spec__0_spec__0___closed__1_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 2, .m_capacity = 2, .m_length = 1, .m_data = "'"};
static const lean_object* lp_competition_Lean_Array_fromJson_x3f___at___00Lean_Json_getObjValAs_x3f___at___00R24DotBankHarness_instFromJsonBankCase_fromJson_spec__0_spec__0___closed__1 = (const lean_object*)&lp_competition_Lean_Array_fromJson_x3f___at___00Lean_Json_getObjValAs_x3f___at___00R24DotBankHarness_instFromJsonBankCase_fromJson_spec__0_spec__0___closed__1_value;
LEAN_EXPORT lean_object* lp_competition_Lean_Array_fromJson_x3f___at___00Lean_Json_getObjValAs_x3f___at___00R24DotBankHarness_instFromJsonBankCase_fromJson_spec__0_spec__0(lean_object*);
LEAN_EXPORT lean_object* lp_competition_Lean_Json_getObjValAs_x3f___at___00R24DotBankHarness_instFromJsonBankCase_fromJson_spec__0(lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_Lean_Json_getObjValAs_x3f___at___00R24DotBankHarness_instFromJsonBankCase_fromJson_spec__0___boxed(lean_object*, lean_object*);
static const lean_string_object lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__0_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 5, .m_capacity = 5, .m_length = 4, .m_data = "name"};
static const lean_object* lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__0 = (const lean_object*)&lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__0_value;
static const lean_string_object lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__1_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 18, .m_capacity = 18, .m_length = 17, .m_data = "R24DotBankHarness"};
static const lean_object* lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__1 = (const lean_object*)&lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__1_value;
static const lean_string_object lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__2_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 9, .m_capacity = 9, .m_length = 8, .m_data = "BankCase"};
static const lean_object* lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__2 = (const lean_object*)&lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__2_value;
static const lean_ctor_object lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__3_value_aux_0 = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_ctor_object) + sizeof(void*)*2 + 8, .m_other = 2, .m_tag = 1}, .m_objs = {((lean_object*)(((size_t)(0) << 1) | 1)),((lean_object*)&lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__1_value),LEAN_SCALAR_PTR_LITERAL(193, 250, 200, 33, 9, 84, 70, 249)}};
static const lean_ctor_object lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__3_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_ctor_object) + sizeof(void*)*2 + 8, .m_other = 2, .m_tag = 1}, .m_objs = {((lean_object*)&lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__3_value_aux_0),((lean_object*)&lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__2_value),LEAN_SCALAR_PTR_LITERAL(47, 246, 47, 78, 172, 235, 161, 144)}};
static const lean_object* lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__3 = (const lean_object*)&lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__3_value;
static lean_once_cell_t lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__4_once = LEAN_ONCE_CELL_INITIALIZER;
static lean_object* lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__4;
static const lean_string_object lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__5_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 2, .m_capacity = 2, .m_length = 1, .m_data = "."};
static const lean_object* lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__5 = (const lean_object*)&lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__5_value;
static lean_once_cell_t lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__6_once = LEAN_ONCE_CELL_INITIALIZER;
static lean_object* lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__6;
static const lean_ctor_object lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__7_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_ctor_object) + sizeof(void*)*2 + 8, .m_other = 2, .m_tag = 1}, .m_objs = {((lean_object*)(((size_t)(0) << 1) | 1)),((lean_object*)&lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__0_value),LEAN_SCALAR_PTR_LITERAL(84, 246, 234, 130, 97, 205, 144, 82)}};
static const lean_object* lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__7 = (const lean_object*)&lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__7_value;
static lean_once_cell_t lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__8_once = LEAN_ONCE_CELL_INITIALIZER;
static lean_object* lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__8;
static lean_once_cell_t lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__9_once = LEAN_ONCE_CELL_INITIALIZER;
static lean_object* lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__9;
static const lean_string_object lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__10_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 3, .m_capacity = 3, .m_length = 2, .m_data = ": "};
static const lean_object* lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__10 = (const lean_object*)&lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__10_value;
static lean_once_cell_t lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__11_once = LEAN_ONCE_CELL_INITIALIZER;
static lean_object* lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__11;
static const lean_string_object lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__12_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 6, .m_capacity = 6, .m_length = 5, .m_data = "group"};
static const lean_object* lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__12 = (const lean_object*)&lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__12_value;
static const lean_ctor_object lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__13_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_ctor_object) + sizeof(void*)*2 + 8, .m_other = 2, .m_tag = 1}, .m_objs = {((lean_object*)(((size_t)(0) << 1) | 1)),((lean_object*)&lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__12_value),LEAN_SCALAR_PTR_LITERAL(206, 113, 20, 57, 188, 177, 187, 30)}};
static const lean_object* lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__13 = (const lean_object*)&lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__13_value;
static lean_once_cell_t lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__14_once = LEAN_ONCE_CELL_INITIALIZER;
static lean_object* lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__14;
static lean_once_cell_t lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__15_once = LEAN_ONCE_CELL_INITIALIZER;
static lean_object* lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__15;
static lean_once_cell_t lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__16_once = LEAN_ONCE_CELL_INITIALIZER;
static lean_object* lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__16;
static const lean_string_object lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__17_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 6, .m_capacity = 6, .m_length = 5, .m_data = "inner"};
static const lean_object* lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__17 = (const lean_object*)&lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__17_value;
static const lean_ctor_object lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__18_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_ctor_object) + sizeof(void*)*2 + 8, .m_other = 2, .m_tag = 1}, .m_objs = {((lean_object*)(((size_t)(0) << 1) | 1)),((lean_object*)&lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__17_value),LEAN_SCALAR_PTR_LITERAL(15, 178, 134, 60, 250, 254, 81, 250)}};
static const lean_object* lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__18 = (const lean_object*)&lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__18_value;
static lean_once_cell_t lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__19_once = LEAN_ONCE_CELL_INITIALIZER;
static lean_object* lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__19;
static lean_once_cell_t lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__20_once = LEAN_ONCE_CELL_INITIALIZER;
static lean_object* lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__20;
static lean_once_cell_t lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__21_once = LEAN_ONCE_CELL_INITIALIZER;
static lean_object* lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__21;
static const lean_string_object lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__22_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 5, .m_capacity = 5, .m_length = 4, .m_data = "rows"};
static const lean_object* lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__22 = (const lean_object*)&lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__22_value;
static const lean_ctor_object lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__23_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_ctor_object) + sizeof(void*)*2 + 8, .m_other = 2, .m_tag = 1}, .m_objs = {((lean_object*)(((size_t)(0) << 1) | 1)),((lean_object*)&lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__22_value),LEAN_SCALAR_PTR_LITERAL(222, 13, 125, 142, 180, 173, 148, 24)}};
static const lean_object* lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__23 = (const lean_object*)&lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__23_value;
static lean_once_cell_t lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__24_once = LEAN_ONCE_CELL_INITIALIZER;
static lean_object* lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__24;
static lean_once_cell_t lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__25_once = LEAN_ONCE_CELL_INITIALIZER;
static lean_object* lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__25;
static lean_once_cell_t lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__26_once = LEAN_ONCE_CELL_INITIALIZER;
static lean_object* lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__26;
static const lean_string_object lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__27_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 5, .m_capacity = 5, .m_length = 4, .m_data = "cols"};
static const lean_object* lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__27 = (const lean_object*)&lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__27_value;
static const lean_ctor_object lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__28_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_ctor_object) + sizeof(void*)*2 + 8, .m_other = 2, .m_tag = 1}, .m_objs = {((lean_object*)(((size_t)(0) << 1) | 1)),((lean_object*)&lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__27_value),LEAN_SCALAR_PTR_LITERAL(74, 239, 172, 173, 135, 73, 244, 251)}};
static const lean_object* lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__28 = (const lean_object*)&lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__28_value;
static lean_once_cell_t lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__29_once = LEAN_ONCE_CELL_INITIALIZER;
static lean_object* lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__29;
static lean_once_cell_t lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__30_once = LEAN_ONCE_CELL_INITIALIZER;
static lean_object* lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__30;
static lean_once_cell_t lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__31_once = LEAN_ONCE_CELL_INITIALIZER;
static lean_object* lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__31;
static const lean_string_object lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__32_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 6, .m_capacity = 6, .m_length = 5, .m_data = "rowsA"};
static const lean_object* lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__32 = (const lean_object*)&lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__32_value;
static const lean_ctor_object lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__33_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_ctor_object) + sizeof(void*)*2 + 8, .m_other = 2, .m_tag = 1}, .m_objs = {((lean_object*)(((size_t)(0) << 1) | 1)),((lean_object*)&lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__32_value),LEAN_SCALAR_PTR_LITERAL(26, 115, 241, 42, 151, 115, 4, 1)}};
static const lean_object* lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__33 = (const lean_object*)&lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__33_value;
static lean_once_cell_t lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__34_once = LEAN_ONCE_CELL_INITIALIZER;
static lean_object* lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__34;
static lean_once_cell_t lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__35_once = LEAN_ONCE_CELL_INITIALIZER;
static lean_object* lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__35;
static lean_once_cell_t lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__36_once = LEAN_ONCE_CELL_INITIALIZER;
static lean_object* lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__36;
static const lean_string_object lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__37_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 6, .m_capacity = 6, .m_length = 5, .m_data = "rowsB"};
static const lean_object* lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__37 = (const lean_object*)&lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__37_value;
static const lean_ctor_object lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__38_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_ctor_object) + sizeof(void*)*2 + 8, .m_other = 2, .m_tag = 1}, .m_objs = {((lean_object*)(((size_t)(0) << 1) | 1)),((lean_object*)&lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__37_value),LEAN_SCALAR_PTR_LITERAL(19, 45, 6, 184, 37, 176, 216, 33)}};
static const lean_object* lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__38 = (const lean_object*)&lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__38_value;
static lean_once_cell_t lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__39_once = LEAN_ONCE_CELL_INITIALIZER;
static lean_object* lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__39;
static lean_once_cell_t lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__40_once = LEAN_ONCE_CELL_INITIALIZER;
static lean_object* lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__40;
static lean_once_cell_t lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__41_once = LEAN_ONCE_CELL_INITIALIZER;
static lean_object* lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__41;
static const lean_string_object lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__42_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 9, .m_capacity = 9, .m_length = 8, .m_data = "expected"};
static const lean_object* lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__42 = (const lean_object*)&lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__42_value;
static const lean_ctor_object lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__43_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_ctor_object) + sizeof(void*)*2 + 8, .m_other = 2, .m_tag = 1}, .m_objs = {((lean_object*)(((size_t)(0) << 1) | 1)),((lean_object*)&lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__42_value),LEAN_SCALAR_PTR_LITERAL(224, 71, 164, 120, 254, 151, 172, 142)}};
static const lean_object* lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__43 = (const lean_object*)&lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__43_value;
static lean_once_cell_t lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__44_once = LEAN_ONCE_CELL_INITIALIZER;
static lean_object* lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__44;
static lean_once_cell_t lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__45_once = LEAN_ONCE_CELL_INITIALIZER;
static lean_object* lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__45;
static lean_once_cell_t lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__46_once = LEAN_ONCE_CELL_INITIALIZER;
static lean_object* lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__46;
LEAN_EXPORT lean_object* lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson(lean_object*);
static const lean_closure_object lp_competition_R24DotBankHarness_instFromJsonBankCase___closed__0_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_closure_object) + sizeof(void*)*0, .m_other = 0, .m_tag = 245}, .m_fun = (void*)lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson, .m_arity = 1, .m_num_fixed = 0, .m_objs = {} };
static const lean_object* lp_competition_R24DotBankHarness_instFromJsonBankCase___closed__0 = (const lean_object*)&lp_competition_R24DotBankHarness_instFromJsonBankCase___closed__0_value;
LEAN_EXPORT const lean_object* lp_competition_R24DotBankHarness_instFromJsonBankCase = (const lean_object*)&lp_competition_R24DotBankHarness_instFromJsonBankCase___closed__0_value;
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_mapMUnsafe_map___at___00Lean_Array_fromJson_x3f___at___00Lean_Json_getObjValAs_x3f___at___00R24DotBankHarness_instFromJsonPlan_fromJson_spec__0_spec__0_spec__1(size_t, size_t, lean_object*);
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_mapMUnsafe_map___at___00Lean_Array_fromJson_x3f___at___00Lean_Json_getObjValAs_x3f___at___00R24DotBankHarness_instFromJsonPlan_fromJson_spec__0_spec__0_spec__1___boxed(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_Lean_Array_fromJson_x3f___at___00Lean_Json_getObjValAs_x3f___at___00R24DotBankHarness_instFromJsonPlan_fromJson_spec__0_spec__0(lean_object*);
LEAN_EXPORT lean_object* lp_competition_Lean_Json_getObjValAs_x3f___at___00R24DotBankHarness_instFromJsonPlan_fromJson_spec__0(lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_Lean_Json_getObjValAs_x3f___at___00R24DotBankHarness_instFromJsonPlan_fromJson_spec__0___boxed(lean_object*, lean_object*);
static const lean_string_object lp_competition_R24DotBankHarness_instFromJsonPlan_fromJson___closed__0_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 6, .m_capacity = 6, .m_length = 5, .m_data = "cases"};
static const lean_object* lp_competition_R24DotBankHarness_instFromJsonPlan_fromJson___closed__0 = (const lean_object*)&lp_competition_R24DotBankHarness_instFromJsonPlan_fromJson___closed__0_value;
static const lean_string_object lp_competition_R24DotBankHarness_instFromJsonPlan_fromJson___closed__1_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 5, .m_capacity = 5, .m_length = 4, .m_data = "Plan"};
static const lean_object* lp_competition_R24DotBankHarness_instFromJsonPlan_fromJson___closed__1 = (const lean_object*)&lp_competition_R24DotBankHarness_instFromJsonPlan_fromJson___closed__1_value;
static const lean_ctor_object lp_competition_R24DotBankHarness_instFromJsonPlan_fromJson___closed__2_value_aux_0 = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_ctor_object) + sizeof(void*)*2 + 8, .m_other = 2, .m_tag = 1}, .m_objs = {((lean_object*)(((size_t)(0) << 1) | 1)),((lean_object*)&lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__1_value),LEAN_SCALAR_PTR_LITERAL(193, 250, 200, 33, 9, 84, 70, 249)}};
static const lean_ctor_object lp_competition_R24DotBankHarness_instFromJsonPlan_fromJson___closed__2_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_ctor_object) + sizeof(void*)*2 + 8, .m_other = 2, .m_tag = 1}, .m_objs = {((lean_object*)&lp_competition_R24DotBankHarness_instFromJsonPlan_fromJson___closed__2_value_aux_0),((lean_object*)&lp_competition_R24DotBankHarness_instFromJsonPlan_fromJson___closed__1_value),LEAN_SCALAR_PTR_LITERAL(107, 226, 151, 249, 111, 250, 42, 186)}};
static const lean_object* lp_competition_R24DotBankHarness_instFromJsonPlan_fromJson___closed__2 = (const lean_object*)&lp_competition_R24DotBankHarness_instFromJsonPlan_fromJson___closed__2_value;
static lean_once_cell_t lp_competition_R24DotBankHarness_instFromJsonPlan_fromJson___closed__3_once = LEAN_ONCE_CELL_INITIALIZER;
static lean_object* lp_competition_R24DotBankHarness_instFromJsonPlan_fromJson___closed__3;
static lean_once_cell_t lp_competition_R24DotBankHarness_instFromJsonPlan_fromJson___closed__4_once = LEAN_ONCE_CELL_INITIALIZER;
static lean_object* lp_competition_R24DotBankHarness_instFromJsonPlan_fromJson___closed__4;
static const lean_ctor_object lp_competition_R24DotBankHarness_instFromJsonPlan_fromJson___closed__5_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_ctor_object) + sizeof(void*)*2 + 8, .m_other = 2, .m_tag = 1}, .m_objs = {((lean_object*)(((size_t)(0) << 1) | 1)),((lean_object*)&lp_competition_R24DotBankHarness_instFromJsonPlan_fromJson___closed__0_value),LEAN_SCALAR_PTR_LITERAL(220, 93, 203, 178, 149, 199, 118, 190)}};
static const lean_object* lp_competition_R24DotBankHarness_instFromJsonPlan_fromJson___closed__5 = (const lean_object*)&lp_competition_R24DotBankHarness_instFromJsonPlan_fromJson___closed__5_value;
static lean_once_cell_t lp_competition_R24DotBankHarness_instFromJsonPlan_fromJson___closed__6_once = LEAN_ONCE_CELL_INITIALIZER;
static lean_object* lp_competition_R24DotBankHarness_instFromJsonPlan_fromJson___closed__6;
static lean_once_cell_t lp_competition_R24DotBankHarness_instFromJsonPlan_fromJson___closed__7_once = LEAN_ONCE_CELL_INITIALIZER;
static lean_object* lp_competition_R24DotBankHarness_instFromJsonPlan_fromJson___closed__7;
static lean_once_cell_t lp_competition_R24DotBankHarness_instFromJsonPlan_fromJson___closed__8_once = LEAN_ONCE_CELL_INITIALIZER;
static lean_object* lp_competition_R24DotBankHarness_instFromJsonPlan_fromJson___closed__8;
LEAN_EXPORT lean_object* lp_competition_R24DotBankHarness_instFromJsonPlan_fromJson(lean_object*);
static const lean_closure_object lp_competition_R24DotBankHarness_instFromJsonPlan___closed__0_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_closure_object) + sizeof(void*)*0, .m_other = 0, .m_tag = 245}, .m_fun = (void*)lp_competition_R24DotBankHarness_instFromJsonPlan_fromJson, .m_arity = 1, .m_num_fixed = 0, .m_objs = {} };
static const lean_object* lp_competition_R24DotBankHarness_instFromJsonPlan___closed__0 = (const lean_object*)&lp_competition_R24DotBankHarness_instFromJsonPlan___closed__0_value;
LEAN_EXPORT const lean_object* lp_competition_R24DotBankHarness_instFromJsonPlan = (const lean_object*)&lp_competition_R24DotBankHarness_instFromJsonPlan___closed__0_value;
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_mapMUnsafe_map___at___00R24DotBankHarness_words_spec__0(size_t, size_t, lean_object*);
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_mapMUnsafe_map___at___00R24DotBankHarness_words_spec__0___boxed(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_mapMUnsafe_map___at___00R24DotBankHarness_words_spec__1(size_t, size_t, lean_object*);
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_mapMUnsafe_map___at___00R24DotBankHarness_words_spec__1___boxed(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_R24DotBankHarness_words(lean_object*);
LEAN_EXPORT lean_object* lp_competition_R24DotBankHarness_outputWords(lean_object*);
LEAN_EXPORT lean_object* lp_competition_R24DotBankHarness_sumRemaining___boxed__const__1;
LEAN_EXPORT uint32_t lp_competition_R24DotBankHarness_sumRemaining(lean_object*, lean_object*, uint32_t, lean_object*);
LEAN_EXPORT lean_object* lp_competition_R24DotBankHarness_sumRemaining___boxed(lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT uint32_t lp_competition_R24DotBankHarness_hashAll(lean_object*);
LEAN_EXPORT lean_object* lp_competition_R24DotBankHarness_hashAll___boxed(lean_object*);
LEAN_EXPORT uint32_t lp_competition_R24DotBankHarness_seed(lean_object*);
LEAN_EXPORT lean_object* lp_competition_R24DotBankHarness_seed___boxed(lean_object*);
LEAN_EXPORT lean_object* lp_competition_R24DotBankHarness_repeats(lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_R24DotBankHarness_repeats___boxed(lean_object*, lean_object*);
static const lean_string_object lp_competition_R24DotBankHarness_checkWord___closed__0_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 6, .m_capacity = 6, .m_length = 5, .m_data = " got="};
static const lean_object* lp_competition_R24DotBankHarness_checkWord___closed__0 = (const lean_object*)&lp_competition_R24DotBankHarness_checkWord___closed__0_value;
static const lean_string_object lp_competition_R24DotBankHarness_checkWord___closed__1_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 11, .m_capacity = 11, .m_length = 10, .m_data = " expected="};
static const lean_object* lp_competition_R24DotBankHarness_checkWord___closed__1 = (const lean_object*)&lp_competition_R24DotBankHarness_checkWord___closed__1_value;
LEAN_EXPORT lean_object* lp_competition_R24DotBankHarness_checkWord(lean_object*, lean_object*, uint32_t, uint32_t);
LEAN_EXPORT lean_object* lp_competition_R24DotBankHarness_checkWord___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
static const lean_string_object lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotBankHarness_checkArray_spec__0___redArg___closed__0_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 9, .m_capacity = 9, .m_length = 8, .m_data = " output "};
static const lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotBankHarness_checkArray_spec__0___redArg___closed__0 = (const lean_object*)&lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotBankHarness_checkArray_spec__0___redArg___closed__0_value;
static const lean_string_object lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotBankHarness_checkArray_spec__0___redArg___closed__1_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 9, .m_capacity = 9, .m_length = 8, .m_data = " differs"};
static const lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotBankHarness_checkArray_spec__0___redArg___closed__1 = (const lean_object*)&lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotBankHarness_checkArray_spec__0___redArg___closed__1_value;
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotBankHarness_checkArray_spec__0___redArg(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotBankHarness_checkArray_spec__0___redArg___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
static const lean_string_object lp_competition_R24DotBankHarness_checkArray___closed__0_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 15, .m_capacity = 15, .m_length = 14, .m_data = " output length"};
static const lean_object* lp_competition_R24DotBankHarness_checkArray___closed__0 = (const lean_object*)&lp_competition_R24DotBankHarness_checkArray___closed__0_value;
LEAN_EXPORT lean_object* lp_competition_R24DotBankHarness_checkArray(lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_R24DotBankHarness_checkArray___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotBankHarness_checkArray_spec__0(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotBankHarness_checkArray_spec__0___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT uint8_t lp_competition___private_Init_Data_Array_Basic_0__Array_anyMUnsafe_any___at___00R24DotBankHarness_checkCase_spec__0(lean_object*, size_t, size_t);
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_anyMUnsafe_any___at___00R24DotBankHarness_checkCase_spec__0___boxed(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT uint8_t lp_competition___private_Init_Data_Array_Basic_0__Array_anyMUnsafe_any___at___00R24DotBankHarness_checkCase_spec__1(lean_object*, lean_object*, lean_object*, uint8_t, lean_object*, size_t, size_t);
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_anyMUnsafe_any___at___00R24DotBankHarness_checkCase_spec__1___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT uint8_t lp_competition___private_Init_Data_Array_Basic_0__Array_anyMUnsafe_any___at___00R24DotBankHarness_checkCase_spec__2(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, size_t, size_t);
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_anyMUnsafe_any___at___00R24DotBankHarness_checkCase_spec__2___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
static const lean_string_object lp_competition_R24DotBankHarness_checkCase___closed__0_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 25, .m_capacity = 25, .m_length = 24, .m_data = ": shape metadata differs"};
static const lean_object* lp_competition_R24DotBankHarness_checkCase___closed__0 = (const lean_object*)&lp_competition_R24DotBankHarness_checkCase___closed__0_value;
static const lean_string_object lp_competition_R24DotBankHarness_checkCase___closed__1_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 13, .m_capacity = 13, .m_length = 12, .m_data = ": empty bank"};
static const lean_object* lp_competition_R24DotBankHarness_checkCase___closed__1 = (const lean_object*)&lp_competition_R24DotBankHarness_checkCase___closed__1_value;
static const lean_string_object lp_competition_R24DotBankHarness_checkCase___closed__2_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 22, .m_capacity = 22, .m_length = 21, .m_data = ": invalid row or word"};
static const lean_object* lp_competition_R24DotBankHarness_checkCase___closed__2 = (const lean_object*)&lp_competition_R24DotBankHarness_checkCase___closed__2_value;
LEAN_EXPORT lean_object* lp_competition_R24DotBankHarness_checkCase(lean_object*);
LEAN_EXPORT lean_object* lp_competition_R24DotBankHarness_checkCase___boxed(lean_object*, lean_object*);
static const lean_string_object lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotBankHarness_emit_spec__0___closed__0_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 13, .m_capacity = 13, .m_length = 12, .m_data = "BANK_SAMPLE\t"};
static const lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotBankHarness_emit_spec__0___closed__0 = (const lean_object*)&lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotBankHarness_emit_spec__0___closed__0_value;
static const lean_string_object lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotBankHarness_emit_spec__0___closed__1_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 2, .m_capacity = 2, .m_length = 1, .m_data = "\t"};
static const lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotBankHarness_emit_spec__0___closed__1 = (const lean_object*)&lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotBankHarness_emit_spec__0___closed__1_value;
static const lean_string_object lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotBankHarness_emit_spec__0___closed__2_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 7, .m_capacity = 7, .m_length = 6, .m_data = "\tfull\t"};
static const lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotBankHarness_emit_spec__0___closed__2 = (const lean_object*)&lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotBankHarness_emit_spec__0___closed__2_value;
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotBankHarness_emit_spec__0(lean_object*, lean_object*, lean_object*, size_t, size_t, uint32_t);
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotBankHarness_emit_spec__0___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
static const lean_string_object lp_competition_R24DotBankHarness_emit___closed__0_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 12, .m_capacity = 12, .m_length = 11, .m_data = "BANK_SETUP\t"};
static const lean_object* lp_competition_R24DotBankHarness_emit___closed__0 = (const lean_object*)&lp_competition_R24DotBankHarness_emit___closed__0_value;
static const lean_string_object lp_competition_R24DotBankHarness_emit___closed__1_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 9, .m_capacity = 9, .m_length = 8, .m_data = "\tfull\t0\t"};
static const lean_object* lp_competition_R24DotBankHarness_emit___closed__1 = (const lean_object*)&lp_competition_R24DotBankHarness_emit___closed__1_value;
LEAN_EXPORT lean_object* lp_competition_R24DotBankHarness_emit(lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_R24DotBankHarness_emit___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT uint32_t lp_competition_R24DotBankHarness_passExact(lean_object*, uint32_t, lean_object*);
LEAN_EXPORT lean_object* lp_competition_R24DotBankHarness_passExact___boxed(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_R24DotBankHarness_benchExact___lam__0(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_R24DotBankHarness_benchExact___lam__1();
LEAN_EXPORT lean_object* lp_competition_R24DotBankHarness_benchExact___lam__1___boxed(lean_object*);
LEAN_EXPORT uint32_t lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotBankHarness_benchExact_spec__0___redArg___lam__1(lean_object*, uint32_t, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotBankHarness_benchExact_spec__0___redArg___lam__1___boxed(lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT uint32_t lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotBankHarness_benchExact_spec__0___redArg___lam__0(lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotBankHarness_benchExact_spec__0___redArg___lam__0___boxed(lean_object*, lean_object*);
static const lean_string_object lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00__private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotBankHarness_benchExact_spec__0_spec__0___redArg___closed__0_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 11, .m_capacity = 11, .m_length = 10, .m_data = "exact:warm"};
static const lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00__private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotBankHarness_benchExact_spec__0_spec__0___redArg___closed__0 = (const lean_object*)&lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00__private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotBankHarness_benchExact_spec__0_spec__0___redArg___closed__0_value;
static const lean_string_object lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00__private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotBankHarness_benchExact_spec__0_spec__0___redArg___closed__1_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 11, .m_capacity = 11, .m_length = 10, .m_data = "exact:sink"};
static const lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00__private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotBankHarness_benchExact_spec__0_spec__0___redArg___closed__1 = (const lean_object*)&lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00__private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotBankHarness_benchExact_spec__0_spec__0___redArg___closed__1_value;
static const lean_string_object lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00__private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotBankHarness_benchExact_spec__0_spec__0___redArg___closed__2_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 11, .m_capacity = 11, .m_length = 10, .m_data = "exact:keep"};
static const lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00__private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotBankHarness_benchExact_spec__0_spec__0___redArg___closed__2 = (const lean_object*)&lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00__private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotBankHarness_benchExact_spec__0_spec__0___redArg___closed__2_value;
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00__private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotBankHarness_benchExact_spec__0_spec__0___redArg(lean_object*, lean_object*, uint32_t, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00__private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotBankHarness_benchExact_spec__0_spec__0___redArg___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotBankHarness_benchExact_spec__0___redArg(lean_object*, lean_object*, uint32_t, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotBankHarness_benchExact_spec__0___redArg___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
static const lean_array_object lp_competition_R24DotBankHarness_benchExact___closed__0_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_array_object) + sizeof(void*)*0, .m_other = 0, .m_tag = 246}, .m_size = 0, .m_capacity = 0, .m_data = {}};
static const lean_object* lp_competition_R24DotBankHarness_benchExact___closed__0 = (const lean_object*)&lp_competition_R24DotBankHarness_benchExact___closed__0_value;
static const lean_ctor_object lp_competition_R24DotBankHarness_benchExact___closed__1_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_ctor_object) + sizeof(void*)*3 + 0, .m_other = 3, .m_tag = 0}, .m_objs = {((lean_object*)(((size_t)(0) << 1) | 1)),((lean_object*)(((size_t)(3) << 1) | 1)),((lean_object*)(((size_t)(1) << 1) | 1))}};
static const lean_object* lp_competition_R24DotBankHarness_benchExact___closed__1 = (const lean_object*)&lp_competition_R24DotBankHarness_benchExact___closed__1_value;
static const lean_string_object lp_competition_R24DotBankHarness_benchExact___closed__2_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 6, .m_capacity = 6, .m_length = 5, .m_data = "exact"};
static const lean_object* lp_competition_R24DotBankHarness_benchExact___closed__2 = (const lean_object*)&lp_competition_R24DotBankHarness_benchExact___closed__2_value;
LEAN_EXPORT lean_object* lp_competition_R24DotBankHarness_benchExact(lean_object*, lean_object*, lean_object*, lean_object*, uint32_t);
LEAN_EXPORT lean_object* lp_competition_R24DotBankHarness_benchExact___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotBankHarness_benchExact_spec__0(lean_object*, lean_object*, uint32_t, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotBankHarness_benchExact_spec__0___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00__private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotBankHarness_benchExact_spec__0_spec__0(lean_object*, lean_object*, uint32_t, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00__private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotBankHarness_benchExact_spec__0_spec__0___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT uint32_t lp_competition_R24DotBankHarness_passEager(lean_object*, uint32_t, lean_object*);
LEAN_EXPORT lean_object* lp_competition_R24DotBankHarness_passEager___boxed(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT uint32_t lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotBankHarness_benchEager_spec__0___redArg___lam__0(lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotBankHarness_benchEager_spec__0___redArg___lam__0___boxed(lean_object*, lean_object*);
LEAN_EXPORT uint32_t lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotBankHarness_benchEager_spec__0___redArg___lam__1(lean_object*, uint32_t, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotBankHarness_benchEager_spec__0___redArg___lam__1___boxed(lean_object*, lean_object*, lean_object*, lean_object*);
static const lean_string_object lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00__private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotBankHarness_benchEager_spec__0_spec__0___redArg___closed__0_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 11, .m_capacity = 11, .m_length = 10, .m_data = "eager:warm"};
static const lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00__private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotBankHarness_benchEager_spec__0_spec__0___redArg___closed__0 = (const lean_object*)&lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00__private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotBankHarness_benchEager_spec__0_spec__0___redArg___closed__0_value;
static const lean_string_object lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00__private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotBankHarness_benchEager_spec__0_spec__0___redArg___closed__1_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 11, .m_capacity = 11, .m_length = 10, .m_data = "eager:sink"};
static const lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00__private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotBankHarness_benchEager_spec__0_spec__0___redArg___closed__1 = (const lean_object*)&lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00__private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotBankHarness_benchEager_spec__0_spec__0___redArg___closed__1_value;
static const lean_string_object lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00__private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotBankHarness_benchEager_spec__0_spec__0___redArg___closed__2_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 11, .m_capacity = 11, .m_length = 10, .m_data = "eager:keep"};
static const lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00__private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotBankHarness_benchEager_spec__0_spec__0___redArg___closed__2 = (const lean_object*)&lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00__private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotBankHarness_benchEager_spec__0_spec__0___redArg___closed__2_value;
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00__private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotBankHarness_benchEager_spec__0_spec__0___redArg(lean_object*, lean_object*, uint32_t, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00__private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotBankHarness_benchEager_spec__0_spec__0___redArg___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotBankHarness_benchEager_spec__0___redArg(lean_object*, lean_object*, uint32_t, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotBankHarness_benchEager_spec__0___redArg___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
static const lean_string_object lp_competition_R24DotBankHarness_benchEager___closed__0_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 6, .m_capacity = 6, .m_length = 5, .m_data = "eager"};
static const lean_object* lp_competition_R24DotBankHarness_benchEager___closed__0 = (const lean_object*)&lp_competition_R24DotBankHarness_benchEager___closed__0_value;
LEAN_EXPORT lean_object* lp_competition_R24DotBankHarness_benchEager(lean_object*, lean_object*, lean_object*, lean_object*, uint32_t);
LEAN_EXPORT lean_object* lp_competition_R24DotBankHarness_benchEager___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotBankHarness_benchEager_spec__0(lean_object*, lean_object*, uint32_t, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotBankHarness_benchEager_spec__0___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00__private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotBankHarness_benchEager_spec__0_spec__0(lean_object*, lean_object*, uint32_t, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00__private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotBankHarness_benchEager_spec__0_spec__0___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT uint32_t lp_competition_R24DotBankHarness_passLazy(lean_object*, uint32_t, lean_object*);
LEAN_EXPORT lean_object* lp_competition_R24DotBankHarness_passLazy___boxed(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT uint32_t lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotBankHarness_benchLazy_spec__0___redArg___lam__0(lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotBankHarness_benchLazy_spec__0___redArg___lam__0___boxed(lean_object*, lean_object*);
LEAN_EXPORT uint32_t lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotBankHarness_benchLazy_spec__0___redArg___lam__1(lean_object*, uint32_t, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotBankHarness_benchLazy_spec__0___redArg___lam__1___boxed(lean_object*, lean_object*, lean_object*, lean_object*);
static const lean_string_object lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00__private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotBankHarness_benchLazy_spec__0_spec__0___redArg___closed__0_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 10, .m_capacity = 10, .m_length = 9, .m_data = "lazy:warm"};
static const lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00__private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotBankHarness_benchLazy_spec__0_spec__0___redArg___closed__0 = (const lean_object*)&lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00__private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotBankHarness_benchLazy_spec__0_spec__0___redArg___closed__0_value;
static const lean_string_object lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00__private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotBankHarness_benchLazy_spec__0_spec__0___redArg___closed__1_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 10, .m_capacity = 10, .m_length = 9, .m_data = "lazy:sink"};
static const lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00__private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotBankHarness_benchLazy_spec__0_spec__0___redArg___closed__1 = (const lean_object*)&lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00__private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotBankHarness_benchLazy_spec__0_spec__0___redArg___closed__1_value;
static const lean_string_object lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00__private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotBankHarness_benchLazy_spec__0_spec__0___redArg___closed__2_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 10, .m_capacity = 10, .m_length = 9, .m_data = "lazy:keep"};
static const lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00__private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotBankHarness_benchLazy_spec__0_spec__0___redArg___closed__2 = (const lean_object*)&lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00__private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotBankHarness_benchLazy_spec__0_spec__0___redArg___closed__2_value;
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00__private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotBankHarness_benchLazy_spec__0_spec__0___redArg(lean_object*, lean_object*, uint32_t, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00__private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotBankHarness_benchLazy_spec__0_spec__0___redArg___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotBankHarness_benchLazy_spec__0___redArg(lean_object*, lean_object*, uint32_t, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotBankHarness_benchLazy_spec__0___redArg___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
static const lean_string_object lp_competition_R24DotBankHarness_benchLazy___closed__0_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 5, .m_capacity = 5, .m_length = 4, .m_data = "lazy"};
static const lean_object* lp_competition_R24DotBankHarness_benchLazy___closed__0 = (const lean_object*)&lp_competition_R24DotBankHarness_benchLazy___closed__0_value;
LEAN_EXPORT lean_object* lp_competition_R24DotBankHarness_benchLazy(lean_object*, lean_object*, lean_object*, lean_object*, uint32_t);
LEAN_EXPORT lean_object* lp_competition_R24DotBankHarness_benchLazy___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotBankHarness_benchLazy_spec__0(lean_object*, lean_object*, uint32_t, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotBankHarness_benchLazy_spec__0___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00__private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotBankHarness_benchLazy_spec__0_spec__0(lean_object*, lean_object*, uint32_t, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00__private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotBankHarness_benchLazy_spec__0_spec__0___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotBankHarness_verify_spec__0___lam__0(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotBankHarness_verify_spec__0___lam__0___boxed(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotBankHarness_verify_spec__0___lam__2(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotBankHarness_verify_spec__0___lam__2___boxed(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotBankHarness_verify_spec__0___lam__1(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotBankHarness_verify_spec__0___lam__1___boxed(lean_object*, lean_object*, lean_object*);
static const lean_string_object lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotBankHarness_verify_spec__0___closed__0_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 9, .m_capacity = 9, .m_length = 8, .m_data = "exactSum"};
static const lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotBankHarness_verify_spec__0___closed__0 = (const lean_object*)&lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotBankHarness_verify_spec__0___closed__0_value;
static const lean_string_object lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotBankHarness_verify_spec__0___closed__1_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 9, .m_capacity = 9, .m_length = 8, .m_data = "eagerSum"};
static const lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotBankHarness_verify_spec__0___closed__1 = (const lean_object*)&lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotBankHarness_verify_spec__0___closed__1_value;
static const lean_string_object lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotBankHarness_verify_spec__0___closed__2_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 8, .m_capacity = 8, .m_length = 7, .m_data = "lazySum"};
static const lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotBankHarness_verify_spec__0___closed__2 = (const lean_object*)&lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotBankHarness_verify_spec__0___closed__2_value;
static const lean_string_object lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotBankHarness_verify_spec__0___closed__3_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 13, .m_capacity = 13, .m_length = 12, .m_data = "BANK_VERIFY\t"};
static const lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotBankHarness_verify_spec__0___closed__3 = (const lean_object*)&lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotBankHarness_verify_spec__0___closed__3_value;
static const lean_string_object lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotBankHarness_verify_spec__0___closed__4_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 6, .m_capacity = 6, .m_length = 5, .m_data = "\ttrue"};
static const lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotBankHarness_verify_spec__0___closed__4 = (const lean_object*)&lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotBankHarness_verify_spec__0___closed__4_value;
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotBankHarness_verify_spec__0(lean_object*, size_t, size_t, lean_object*);
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotBankHarness_verify_spec__0___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
static const lean_string_object lp_competition_R24DotBankHarness_verify___closed__0_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 18, .m_capacity = 18, .m_length = 17, .m_data = "BANK_VERIFY_DONE\t"};
static const lean_object* lp_competition_R24DotBankHarness_verify___closed__0 = (const lean_object*)&lp_competition_R24DotBankHarness_verify___closed__0_value;
static const lean_string_object lp_competition_R24DotBankHarness_verify___closed__1_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 3, .m_capacity = 3, .m_length = 2, .m_data = "\t3"};
static const lean_object* lp_competition_R24DotBankHarness_verify___closed__1 = (const lean_object*)&lp_competition_R24DotBankHarness_verify___closed__1_value;
LEAN_EXPORT lean_object* lp_competition_R24DotBankHarness_verify(lean_object*);
LEAN_EXPORT lean_object* lp_competition_R24DotBankHarness_verify___boxed(lean_object*, lean_object*);
static const lean_string_object lp_competition_R24DotBankHarness_env___closed__0_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 9, .m_capacity = 9, .m_length = 8, .m_data = "Missing "};
static const lean_object* lp_competition_R24DotBankHarness_env___closed__0 = (const lean_object*)&lp_competition_R24DotBankHarness_env___closed__0_value;
LEAN_EXPORT lean_object* lp_competition_R24DotBankHarness_env(lean_object*);
LEAN_EXPORT lean_object* lp_competition_R24DotBankHarness_env___boxed(lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotBankHarness_run_spec__0___lam__0(lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotBankHarness_run_spec__0___lam__1(lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotBankHarness_run_spec__0(lean_object*, lean_object*, lean_object*, lean_object*, size_t, size_t, lean_object*);
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotBankHarness_run_spec__0___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
static const lean_string_object lp_competition_R24DotBankHarness_run___closed__0_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 18, .m_capacity = 18, .m_length = 17, .m_data = "BENCH_DOT_FIXTURE"};
static const lean_object* lp_competition_R24DotBankHarness_run___closed__0 = (const lean_object*)&lp_competition_R24DotBankHarness_run___closed__0_value;
static const lean_string_object lp_competition_R24DotBankHarness_run___closed__1_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 15, .m_capacity = 15, .m_length = 14, .m_data = "bank fixture: "};
static const lean_object* lp_competition_R24DotBankHarness_run___closed__1 = (const lean_object*)&lp_competition_R24DotBankHarness_run___closed__1_value;
static const lean_string_object lp_competition_R24DotBankHarness_run___closed__2_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 19, .m_capacity = 19, .m_length = 18, .m_data = "BANK_MEASURE_DONE\t"};
static const lean_object* lp_competition_R24DotBankHarness_run___closed__2 = (const lean_object*)&lp_competition_R24DotBankHarness_run___closed__2_value;
static const lean_string_object lp_competition_R24DotBankHarness_run___closed__3_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 17, .m_capacity = 17, .m_length = 16, .m_data = "MACS exceeds2^24"};
static const lean_object* lp_competition_R24DotBankHarness_run___closed__3 = (const lean_object*)&lp_competition_R24DotBankHarness_run___closed__3_value;
static const lean_ctor_object lp_competition_R24DotBankHarness_run___closed__4_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_ctor_object) + sizeof(void*)*1 + 0, .m_other = 1, .m_tag = 18}, .m_objs = {((lean_object*)&lp_competition_R24DotBankHarness_run___closed__3_value)}};
static const lean_object* lp_competition_R24DotBankHarness_run___closed__4 = (const lean_object*)&lp_competition_R24DotBankHarness_run___closed__4_value;
static const lean_string_object lp_competition_R24DotBankHarness_run___closed__5_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 23, .m_capacity = 23, .m_length = 22, .m_data = "Invalid BENCH_DOT_MACS"};
static const lean_object* lp_competition_R24DotBankHarness_run___closed__5 = (const lean_object*)&lp_competition_R24DotBankHarness_run___closed__5_value;
static const lean_ctor_object lp_competition_R24DotBankHarness_run___closed__6_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_ctor_object) + sizeof(void*)*1 + 0, .m_other = 1, .m_tag = 18}, .m_objs = {((lean_object*)&lp_competition_R24DotBankHarness_run___closed__5_value)}};
static const lean_object* lp_competition_R24DotBankHarness_run___closed__6 = (const lean_object*)&lp_competition_R24DotBankHarness_run___closed__6_value;
static const lean_string_object lp_competition_R24DotBankHarness_run___closed__7_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 5, .m_capacity = 5, .m_length = 4, .m_data = "full"};
static const lean_object* lp_competition_R24DotBankHarness_run___closed__7 = (const lean_object*)&lp_competition_R24DotBankHarness_run___closed__7_value;
static const lean_string_object lp_competition_R24DotBankHarness_run___closed__8_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 30, .m_capacity = 30, .m_length = 29, .m_data = "Bank has no prepared boundary"};
static const lean_object* lp_competition_R24DotBankHarness_run___closed__8 = (const lean_object*)&lp_competition_R24DotBankHarness_run___closed__8_value;
static const lean_ctor_object lp_competition_R24DotBankHarness_run___closed__9_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_ctor_object) + sizeof(void*)*1 + 0, .m_other = 1, .m_tag = 18}, .m_objs = {((lean_object*)&lp_competition_R24DotBankHarness_run___closed__8_value)}};
static const lean_object* lp_competition_R24DotBankHarness_run___closed__9 = (const lean_object*)&lp_competition_R24DotBankHarness_run___closed__9_value;
static const lean_string_object lp_competition_R24DotBankHarness_run___closed__10_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 15, .m_capacity = 15, .m_length = 14, .m_data = "BENCH_DOT_MACS"};
static const lean_object* lp_competition_R24DotBankHarness_run___closed__10 = (const lean_object*)&lp_competition_R24DotBankHarness_run___closed__10_value;
static const lean_string_object lp_competition_R24DotBankHarness_run___closed__11_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 7, .m_capacity = 7, .m_length = 6, .m_data = "131072"};
static const lean_object* lp_competition_R24DotBankHarness_run___closed__11 = (const lean_object*)&lp_competition_R24DotBankHarness_run___closed__11_value;
static const lean_string_object lp_competition_R24DotBankHarness_run___closed__12_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 21, .m_capacity = 21, .m_length = 20, .m_data = "Invalid bank variant"};
static const lean_object* lp_competition_R24DotBankHarness_run___closed__12 = (const lean_object*)&lp_competition_R24DotBankHarness_run___closed__12_value;
static const lean_ctor_object lp_competition_R24DotBankHarness_run___closed__13_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_ctor_object) + sizeof(void*)*1 + 0, .m_other = 1, .m_tag = 18}, .m_objs = {((lean_object*)&lp_competition_R24DotBankHarness_run___closed__12_value)}};
static const lean_object* lp_competition_R24DotBankHarness_run___closed__13 = (const lean_object*)&lp_competition_R24DotBankHarness_run___closed__13_value;
static const lean_string_object lp_competition_R24DotBankHarness_run___closed__14_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 9, .m_capacity = 9, .m_length = 8, .m_data = "24282603"};
static const lean_object* lp_competition_R24DotBankHarness_run___closed__14 = (const lean_object*)&lp_competition_R24DotBankHarness_run___closed__14_value;
static const lean_string_object lp_competition_R24DotBankHarness_run___closed__15_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 19, .m_capacity = 19, .m_length = 18, .m_data = "Invalid bank group"};
static const lean_object* lp_competition_R24DotBankHarness_run___closed__15 = (const lean_object*)&lp_competition_R24DotBankHarness_run___closed__15_value;
static const lean_ctor_object lp_competition_R24DotBankHarness_run___closed__16_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_ctor_object) + sizeof(void*)*1 + 0, .m_other = 1, .m_tag = 18}, .m_objs = {((lean_object*)&lp_competition_R24DotBankHarness_run___closed__15_value)}};
static const lean_object* lp_competition_R24DotBankHarness_run___closed__16 = (const lean_object*)&lp_competition_R24DotBankHarness_run___closed__16_value;
static const lean_string_object lp_competition_R24DotBankHarness_run___closed__17_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 9, .m_capacity = 9, .m_length = 8, .m_data = "24282601"};
static const lean_object* lp_competition_R24DotBankHarness_run___closed__17 = (const lean_object*)&lp_competition_R24DotBankHarness_run___closed__17_value;
static const lean_string_object lp_competition_R24DotBankHarness_run___closed__18_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 15, .m_capacity = 15, .m_length = 14, .m_data = "BENCH_DOT_MODE"};
static const lean_object* lp_competition_R24DotBankHarness_run___closed__18 = (const lean_object*)&lp_competition_R24DotBankHarness_run___closed__18_value;
static const lean_string_object lp_competition_R24DotBankHarness_run___closed__19_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 23, .m_capacity = 23, .m_length = 22, .m_data = "Invalid BENCH_DOT_MODE"};
static const lean_object* lp_competition_R24DotBankHarness_run___closed__19 = (const lean_object*)&lp_competition_R24DotBankHarness_run___closed__19_value;
static const lean_ctor_object lp_competition_R24DotBankHarness_run___closed__20_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_ctor_object) + sizeof(void*)*1 + 0, .m_other = 1, .m_tag = 18}, .m_objs = {((lean_object*)&lp_competition_R24DotBankHarness_run___closed__19_value)}};
static const lean_object* lp_competition_R24DotBankHarness_run___closed__20 = (const lean_object*)&lp_competition_R24DotBankHarness_run___closed__20_value;
static const lean_string_object lp_competition_R24DotBankHarness_run___closed__21_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 7, .m_capacity = 7, .m_length = 6, .m_data = "verify"};
static const lean_object* lp_competition_R24DotBankHarness_run___closed__21 = (const lean_object*)&lp_competition_R24DotBankHarness_run___closed__21_value;
static const lean_string_object lp_competition_R24DotBankHarness_run___closed__22_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 8, .m_capacity = 8, .m_length = 7, .m_data = "measure"};
static const lean_object* lp_competition_R24DotBankHarness_run___closed__22 = (const lean_object*)&lp_competition_R24DotBankHarness_run___closed__22_value;
static const lean_string_object lp_competition_R24DotBankHarness_run___closed__23_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 16, .m_capacity = 16, .m_length = 15, .m_data = "BENCH_DOT_GROUP"};
static const lean_object* lp_competition_R24DotBankHarness_run___closed__23 = (const lean_object*)&lp_competition_R24DotBankHarness_run___closed__23_value;
static const lean_string_object lp_competition_R24DotBankHarness_run___closed__24_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 18, .m_capacity = 18, .m_length = 17, .m_data = "BENCH_DOT_VARIANT"};
static const lean_object* lp_competition_R24DotBankHarness_run___closed__24 = (const lean_object*)&lp_competition_R24DotBankHarness_run___closed__24_value;
static const lean_string_object lp_competition_R24DotBankHarness_run___closed__25_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 19, .m_capacity = 19, .m_length = 18, .m_data = "BENCH_DOT_BOUNDARY"};
static const lean_object* lp_competition_R24DotBankHarness_run___closed__25 = (const lean_object*)&lp_competition_R24DotBankHarness_run___closed__25_value;
LEAN_EXPORT lean_object* lp_competition_R24DotBankHarness_run();
LEAN_EXPORT lean_object* lp_competition_R24DotBankHarness_run___boxed(lean_object*);
LEAN_EXPORT lean_object* _lean_main();
LEAN_EXPORT lean_object* lp_competition_main___boxed(lean_object*);
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_mapMUnsafe_map___at___00Lean_Array_fromJson_x3f___at___00Lean_Json_getObjValAs_x3f___at___00R24DotBankHarness_instFromJsonBankCase_fromJson_spec__0_spec__0_spec__1(size_t v_sz_1_, size_t v_i_2_, lean_object* v_bs_3_){
_start:
{
uint8_t v___x_4_; 
v___x_4_ = lean_usize_dec_lt(v_i_2_, v_sz_1_);
if (v___x_4_ == 0)
{
lean_object* v___x_5_; 
v___x_5_ = lean_alloc_ctor(1, 1, 0);
lean_ctor_set(v___x_5_, 0, v_bs_3_);
return v___x_5_;
}
else
{
lean_object* v_v_6_; lean_object* v___x_7_; 
v_v_6_ = lean_array_uget_borrowed(v_bs_3_, v_i_2_);
lean_inc(v_v_6_);
v___x_7_ = l_Lean_Array_fromJson_x3f___at___00Lean_Json_getObjValAs_x3f___at___00Lean_Lsp_instFromJsonSemanticTokens_fromJson_spec__0_spec__0(v_v_6_);
if (lean_obj_tag(v___x_7_) == 0)
{
lean_object* v_a_8_; lean_object* v___x_10_; uint8_t v_isShared_11_; uint8_t v_isSharedCheck_15_; 
lean_dec_ref(v_bs_3_);
v_a_8_ = lean_ctor_get(v___x_7_, 0);
v_isSharedCheck_15_ = !lean_is_exclusive(v___x_7_);
if (v_isSharedCheck_15_ == 0)
{
v___x_10_ = v___x_7_;
v_isShared_11_ = v_isSharedCheck_15_;
goto v_resetjp_9_;
}
else
{
lean_inc(v_a_8_);
lean_dec(v___x_7_);
v___x_10_ = lean_box(0);
v_isShared_11_ = v_isSharedCheck_15_;
goto v_resetjp_9_;
}
v_resetjp_9_:
{
lean_object* v___x_13_; 
if (v_isShared_11_ == 0)
{
v___x_13_ = v___x_10_;
goto v_reusejp_12_;
}
else
{
lean_object* v_reuseFailAlloc_14_; 
v_reuseFailAlloc_14_ = lean_alloc_ctor(0, 1, 0);
lean_ctor_set(v_reuseFailAlloc_14_, 0, v_a_8_);
v___x_13_ = v_reuseFailAlloc_14_;
goto v_reusejp_12_;
}
v_reusejp_12_:
{
return v___x_13_;
}
}
}
else
{
lean_object* v_a_16_; lean_object* v___x_17_; lean_object* v_bs_x27_18_; size_t v___x_19_; size_t v___x_20_; lean_object* v___x_21_; 
v_a_16_ = lean_ctor_get(v___x_7_, 0);
lean_inc(v_a_16_);
lean_dec_ref_known(v___x_7_, 1);
v___x_17_ = lean_unsigned_to_nat(0u);
v_bs_x27_18_ = lean_array_uset(v_bs_3_, v_i_2_, v___x_17_);
v___x_19_ = ((size_t)1ULL);
v___x_20_ = lean_usize_add(v_i_2_, v___x_19_);
v___x_21_ = lean_array_uset(v_bs_x27_18_, v_i_2_, v_a_16_);
v_i_2_ = v___x_20_;
v_bs_3_ = v___x_21_;
goto _start;
}
}
}
}
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_mapMUnsafe_map___at___00Lean_Array_fromJson_x3f___at___00Lean_Json_getObjValAs_x3f___at___00R24DotBankHarness_instFromJsonBankCase_fromJson_spec__0_spec__0_spec__1___boxed(lean_object* v_sz_23_, lean_object* v_i_24_, lean_object* v_bs_25_){
_start:
{
size_t v_sz_boxed_26_; size_t v_i_boxed_27_; lean_object* v_res_28_; 
v_sz_boxed_26_ = lean_unbox_usize(v_sz_23_);
lean_dec(v_sz_23_);
v_i_boxed_27_ = lean_unbox_usize(v_i_24_);
lean_dec(v_i_24_);
v_res_28_ = lp_competition___private_Init_Data_Array_Basic_0__Array_mapMUnsafe_map___at___00Lean_Array_fromJson_x3f___at___00Lean_Json_getObjValAs_x3f___at___00R24DotBankHarness_instFromJsonBankCase_fromJson_spec__0_spec__0_spec__1(v_sz_boxed_26_, v_i_boxed_27_, v_bs_25_);
return v_res_28_;
}
}
LEAN_EXPORT lean_object* lp_competition_Lean_Array_fromJson_x3f___at___00Lean_Json_getObjValAs_x3f___at___00R24DotBankHarness_instFromJsonBankCase_fromJson_spec__0_spec__0(lean_object* v_x_31_){
_start:
{
if (lean_obj_tag(v_x_31_) == 4)
{
lean_object* v_elems_32_; size_t v_sz_33_; size_t v___x_34_; lean_object* v___x_35_; 
v_elems_32_ = lean_ctor_get(v_x_31_, 0);
lean_inc_ref(v_elems_32_);
lean_dec_ref_known(v_x_31_, 1);
v_sz_33_ = lean_array_size(v_elems_32_);
v___x_34_ = ((size_t)0ULL);
v___x_35_ = lp_competition___private_Init_Data_Array_Basic_0__Array_mapMUnsafe_map___at___00Lean_Array_fromJson_x3f___at___00Lean_Json_getObjValAs_x3f___at___00R24DotBankHarness_instFromJsonBankCase_fromJson_spec__0_spec__0_spec__1(v_sz_33_, v___x_34_, v_elems_32_);
return v___x_35_;
}
else
{
lean_object* v___x_36_; lean_object* v___x_37_; lean_object* v___x_38_; lean_object* v___x_39_; lean_object* v___x_40_; lean_object* v___x_41_; lean_object* v___x_42_; 
v___x_36_ = ((lean_object*)(lp_competition_Lean_Array_fromJson_x3f___at___00Lean_Json_getObjValAs_x3f___at___00R24DotBankHarness_instFromJsonBankCase_fromJson_spec__0_spec__0___closed__0));
v___x_37_ = lean_unsigned_to_nat(80u);
v___x_38_ = l_Lean_Json_pretty(v_x_31_, v___x_37_);
v___x_39_ = lean_string_append(v___x_36_, v___x_38_);
lean_dec_ref(v___x_38_);
v___x_40_ = ((lean_object*)(lp_competition_Lean_Array_fromJson_x3f___at___00Lean_Json_getObjValAs_x3f___at___00R24DotBankHarness_instFromJsonBankCase_fromJson_spec__0_spec__0___closed__1));
v___x_41_ = lean_string_append(v___x_39_, v___x_40_);
v___x_42_ = lean_alloc_ctor(0, 1, 0);
lean_ctor_set(v___x_42_, 0, v___x_41_);
return v___x_42_;
}
}
}
LEAN_EXPORT lean_object* lp_competition_Lean_Json_getObjValAs_x3f___at___00R24DotBankHarness_instFromJsonBankCase_fromJson_spec__0(lean_object* v_j_43_, lean_object* v_k_44_){
_start:
{
lean_object* v___x_45_; lean_object* v___x_46_; 
v___x_45_ = l_Lean_Json_getObjValD(v_j_43_, v_k_44_);
v___x_46_ = lp_competition_Lean_Array_fromJson_x3f___at___00Lean_Json_getObjValAs_x3f___at___00R24DotBankHarness_instFromJsonBankCase_fromJson_spec__0_spec__0(v___x_45_);
return v___x_46_;
}
}
LEAN_EXPORT lean_object* lp_competition_Lean_Json_getObjValAs_x3f___at___00R24DotBankHarness_instFromJsonBankCase_fromJson_spec__0___boxed(lean_object* v_j_47_, lean_object* v_k_48_){
_start:
{
lean_object* v_res_49_; 
v_res_49_ = lp_competition_Lean_Json_getObjValAs_x3f___at___00R24DotBankHarness_instFromJsonBankCase_fromJson_spec__0(v_j_47_, v_k_48_);
lean_dec_ref(v_k_48_);
return v_res_49_;
}
}
static lean_object* _init_lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__4(void){
_start:
{
uint8_t v___x_56_; lean_object* v___x_57_; lean_object* v___x_58_; 
v___x_56_ = 1;
v___x_57_ = ((lean_object*)(lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__3));
v___x_58_ = l_Lean_Name_toStringWithToken___at___00Lean_Name_toString_spec__0(v___x_57_, v___x_56_);
return v___x_58_;
}
}
static lean_object* _init_lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__6(void){
_start:
{
lean_object* v___x_60_; lean_object* v___x_61_; lean_object* v___x_62_; 
v___x_60_ = ((lean_object*)(lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__5));
v___x_61_ = lean_obj_once(&lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__4, &lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__4_once, _init_lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__4);
v___x_62_ = lean_string_append(v___x_61_, v___x_60_);
return v___x_62_;
}
}
static lean_object* _init_lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__8(void){
_start:
{
uint8_t v___x_65_; lean_object* v___x_66_; lean_object* v___x_67_; 
v___x_65_ = 1;
v___x_66_ = ((lean_object*)(lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__7));
v___x_67_ = l_Lean_Name_toStringWithToken___at___00Lean_Name_toString_spec__0(v___x_66_, v___x_65_);
return v___x_67_;
}
}
static lean_object* _init_lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__9(void){
_start:
{
lean_object* v___x_68_; lean_object* v___x_69_; lean_object* v___x_70_; 
v___x_68_ = lean_obj_once(&lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__8, &lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__8_once, _init_lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__8);
v___x_69_ = lean_obj_once(&lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__6, &lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__6_once, _init_lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__6);
v___x_70_ = lean_string_append(v___x_69_, v___x_68_);
return v___x_70_;
}
}
static lean_object* _init_lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__11(void){
_start:
{
lean_object* v___x_72_; lean_object* v___x_73_; lean_object* v___x_74_; 
v___x_72_ = ((lean_object*)(lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__10));
v___x_73_ = lean_obj_once(&lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__9, &lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__9_once, _init_lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__9);
v___x_74_ = lean_string_append(v___x_73_, v___x_72_);
return v___x_74_;
}
}
static lean_object* _init_lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__14(void){
_start:
{
uint8_t v___x_78_; lean_object* v___x_79_; lean_object* v___x_80_; 
v___x_78_ = 1;
v___x_79_ = ((lean_object*)(lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__13));
v___x_80_ = l_Lean_Name_toStringWithToken___at___00Lean_Name_toString_spec__0(v___x_79_, v___x_78_);
return v___x_80_;
}
}
static lean_object* _init_lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__15(void){
_start:
{
lean_object* v___x_81_; lean_object* v___x_82_; lean_object* v___x_83_; 
v___x_81_ = lean_obj_once(&lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__14, &lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__14_once, _init_lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__14);
v___x_82_ = lean_obj_once(&lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__6, &lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__6_once, _init_lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__6);
v___x_83_ = lean_string_append(v___x_82_, v___x_81_);
return v___x_83_;
}
}
static lean_object* _init_lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__16(void){
_start:
{
lean_object* v___x_84_; lean_object* v___x_85_; lean_object* v___x_86_; 
v___x_84_ = ((lean_object*)(lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__10));
v___x_85_ = lean_obj_once(&lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__15, &lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__15_once, _init_lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__15);
v___x_86_ = lean_string_append(v___x_85_, v___x_84_);
return v___x_86_;
}
}
static lean_object* _init_lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__19(void){
_start:
{
uint8_t v___x_90_; lean_object* v___x_91_; lean_object* v___x_92_; 
v___x_90_ = 1;
v___x_91_ = ((lean_object*)(lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__18));
v___x_92_ = l_Lean_Name_toStringWithToken___at___00Lean_Name_toString_spec__0(v___x_91_, v___x_90_);
return v___x_92_;
}
}
static lean_object* _init_lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__20(void){
_start:
{
lean_object* v___x_93_; lean_object* v___x_94_; lean_object* v___x_95_; 
v___x_93_ = lean_obj_once(&lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__19, &lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__19_once, _init_lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__19);
v___x_94_ = lean_obj_once(&lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__6, &lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__6_once, _init_lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__6);
v___x_95_ = lean_string_append(v___x_94_, v___x_93_);
return v___x_95_;
}
}
static lean_object* _init_lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__21(void){
_start:
{
lean_object* v___x_96_; lean_object* v___x_97_; lean_object* v___x_98_; 
v___x_96_ = ((lean_object*)(lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__10));
v___x_97_ = lean_obj_once(&lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__20, &lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__20_once, _init_lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__20);
v___x_98_ = lean_string_append(v___x_97_, v___x_96_);
return v___x_98_;
}
}
static lean_object* _init_lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__24(void){
_start:
{
uint8_t v___x_102_; lean_object* v___x_103_; lean_object* v___x_104_; 
v___x_102_ = 1;
v___x_103_ = ((lean_object*)(lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__23));
v___x_104_ = l_Lean_Name_toStringWithToken___at___00Lean_Name_toString_spec__0(v___x_103_, v___x_102_);
return v___x_104_;
}
}
static lean_object* _init_lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__25(void){
_start:
{
lean_object* v___x_105_; lean_object* v___x_106_; lean_object* v___x_107_; 
v___x_105_ = lean_obj_once(&lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__24, &lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__24_once, _init_lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__24);
v___x_106_ = lean_obj_once(&lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__6, &lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__6_once, _init_lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__6);
v___x_107_ = lean_string_append(v___x_106_, v___x_105_);
return v___x_107_;
}
}
static lean_object* _init_lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__26(void){
_start:
{
lean_object* v___x_108_; lean_object* v___x_109_; lean_object* v___x_110_; 
v___x_108_ = ((lean_object*)(lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__10));
v___x_109_ = lean_obj_once(&lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__25, &lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__25_once, _init_lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__25);
v___x_110_ = lean_string_append(v___x_109_, v___x_108_);
return v___x_110_;
}
}
static lean_object* _init_lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__29(void){
_start:
{
uint8_t v___x_114_; lean_object* v___x_115_; lean_object* v___x_116_; 
v___x_114_ = 1;
v___x_115_ = ((lean_object*)(lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__28));
v___x_116_ = l_Lean_Name_toStringWithToken___at___00Lean_Name_toString_spec__0(v___x_115_, v___x_114_);
return v___x_116_;
}
}
static lean_object* _init_lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__30(void){
_start:
{
lean_object* v___x_117_; lean_object* v___x_118_; lean_object* v___x_119_; 
v___x_117_ = lean_obj_once(&lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__29, &lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__29_once, _init_lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__29);
v___x_118_ = lean_obj_once(&lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__6, &lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__6_once, _init_lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__6);
v___x_119_ = lean_string_append(v___x_118_, v___x_117_);
return v___x_119_;
}
}
static lean_object* _init_lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__31(void){
_start:
{
lean_object* v___x_120_; lean_object* v___x_121_; lean_object* v___x_122_; 
v___x_120_ = ((lean_object*)(lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__10));
v___x_121_ = lean_obj_once(&lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__30, &lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__30_once, _init_lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__30);
v___x_122_ = lean_string_append(v___x_121_, v___x_120_);
return v___x_122_;
}
}
static lean_object* _init_lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__34(void){
_start:
{
uint8_t v___x_126_; lean_object* v___x_127_; lean_object* v___x_128_; 
v___x_126_ = 1;
v___x_127_ = ((lean_object*)(lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__33));
v___x_128_ = l_Lean_Name_toStringWithToken___at___00Lean_Name_toString_spec__0(v___x_127_, v___x_126_);
return v___x_128_;
}
}
static lean_object* _init_lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__35(void){
_start:
{
lean_object* v___x_129_; lean_object* v___x_130_; lean_object* v___x_131_; 
v___x_129_ = lean_obj_once(&lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__34, &lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__34_once, _init_lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__34);
v___x_130_ = lean_obj_once(&lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__6, &lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__6_once, _init_lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__6);
v___x_131_ = lean_string_append(v___x_130_, v___x_129_);
return v___x_131_;
}
}
static lean_object* _init_lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__36(void){
_start:
{
lean_object* v___x_132_; lean_object* v___x_133_; lean_object* v___x_134_; 
v___x_132_ = ((lean_object*)(lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__10));
v___x_133_ = lean_obj_once(&lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__35, &lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__35_once, _init_lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__35);
v___x_134_ = lean_string_append(v___x_133_, v___x_132_);
return v___x_134_;
}
}
static lean_object* _init_lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__39(void){
_start:
{
uint8_t v___x_138_; lean_object* v___x_139_; lean_object* v___x_140_; 
v___x_138_ = 1;
v___x_139_ = ((lean_object*)(lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__38));
v___x_140_ = l_Lean_Name_toStringWithToken___at___00Lean_Name_toString_spec__0(v___x_139_, v___x_138_);
return v___x_140_;
}
}
static lean_object* _init_lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__40(void){
_start:
{
lean_object* v___x_141_; lean_object* v___x_142_; lean_object* v___x_143_; 
v___x_141_ = lean_obj_once(&lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__39, &lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__39_once, _init_lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__39);
v___x_142_ = lean_obj_once(&lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__6, &lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__6_once, _init_lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__6);
v___x_143_ = lean_string_append(v___x_142_, v___x_141_);
return v___x_143_;
}
}
static lean_object* _init_lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__41(void){
_start:
{
lean_object* v___x_144_; lean_object* v___x_145_; lean_object* v___x_146_; 
v___x_144_ = ((lean_object*)(lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__10));
v___x_145_ = lean_obj_once(&lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__40, &lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__40_once, _init_lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__40);
v___x_146_ = lean_string_append(v___x_145_, v___x_144_);
return v___x_146_;
}
}
static lean_object* _init_lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__44(void){
_start:
{
uint8_t v___x_150_; lean_object* v___x_151_; lean_object* v___x_152_; 
v___x_150_ = 1;
v___x_151_ = ((lean_object*)(lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__43));
v___x_152_ = l_Lean_Name_toStringWithToken___at___00Lean_Name_toString_spec__0(v___x_151_, v___x_150_);
return v___x_152_;
}
}
static lean_object* _init_lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__45(void){
_start:
{
lean_object* v___x_153_; lean_object* v___x_154_; lean_object* v___x_155_; 
v___x_153_ = lean_obj_once(&lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__44, &lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__44_once, _init_lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__44);
v___x_154_ = lean_obj_once(&lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__6, &lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__6_once, _init_lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__6);
v___x_155_ = lean_string_append(v___x_154_, v___x_153_);
return v___x_155_;
}
}
static lean_object* _init_lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__46(void){
_start:
{
lean_object* v___x_156_; lean_object* v___x_157_; lean_object* v___x_158_; 
v___x_156_ = ((lean_object*)(lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__10));
v___x_157_ = lean_obj_once(&lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__45, &lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__45_once, _init_lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__45);
v___x_158_ = lean_string_append(v___x_157_, v___x_156_);
return v___x_158_;
}
}
LEAN_EXPORT lean_object* lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson(lean_object* v_json_159_){
_start:
{
lean_object* v___x_160_; lean_object* v___x_161_; 
v___x_160_ = ((lean_object*)(lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__0));
lean_inc(v_json_159_);
v___x_161_ = lp_proofwidgets_Lean_Json_getObjValAs_x3f___at___00ProofWidgets_MarkdownDisplay_instFromJsonProps_fromJson_spec__0(v_json_159_, v___x_160_);
if (lean_obj_tag(v___x_161_) == 0)
{
lean_object* v_a_162_; lean_object* v___x_164_; uint8_t v_isShared_165_; uint8_t v_isSharedCheck_171_; 
lean_dec(v_json_159_);
v_a_162_ = lean_ctor_get(v___x_161_, 0);
v_isSharedCheck_171_ = !lean_is_exclusive(v___x_161_);
if (v_isSharedCheck_171_ == 0)
{
v___x_164_ = v___x_161_;
v_isShared_165_ = v_isSharedCheck_171_;
goto v_resetjp_163_;
}
else
{
lean_inc(v_a_162_);
lean_dec(v___x_161_);
v___x_164_ = lean_box(0);
v_isShared_165_ = v_isSharedCheck_171_;
goto v_resetjp_163_;
}
v_resetjp_163_:
{
lean_object* v___x_166_; lean_object* v___x_167_; lean_object* v___x_169_; 
v___x_166_ = lean_obj_once(&lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__11, &lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__11_once, _init_lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__11);
v___x_167_ = lean_string_append(v___x_166_, v_a_162_);
lean_dec(v_a_162_);
if (v_isShared_165_ == 0)
{
lean_ctor_set(v___x_164_, 0, v___x_167_);
v___x_169_ = v___x_164_;
goto v_reusejp_168_;
}
else
{
lean_object* v_reuseFailAlloc_170_; 
v_reuseFailAlloc_170_ = lean_alloc_ctor(0, 1, 0);
lean_ctor_set(v_reuseFailAlloc_170_, 0, v___x_167_);
v___x_169_ = v_reuseFailAlloc_170_;
goto v_reusejp_168_;
}
v_reusejp_168_:
{
return v___x_169_;
}
}
}
else
{
if (lean_obj_tag(v___x_161_) == 0)
{
lean_object* v_a_172_; lean_object* v___x_174_; uint8_t v_isShared_175_; uint8_t v_isSharedCheck_179_; 
lean_dec(v_json_159_);
v_a_172_ = lean_ctor_get(v___x_161_, 0);
v_isSharedCheck_179_ = !lean_is_exclusive(v___x_161_);
if (v_isSharedCheck_179_ == 0)
{
v___x_174_ = v___x_161_;
v_isShared_175_ = v_isSharedCheck_179_;
goto v_resetjp_173_;
}
else
{
lean_inc(v_a_172_);
lean_dec(v___x_161_);
v___x_174_ = lean_box(0);
v_isShared_175_ = v_isSharedCheck_179_;
goto v_resetjp_173_;
}
v_resetjp_173_:
{
lean_object* v___x_177_; 
if (v_isShared_175_ == 0)
{
lean_ctor_set_tag(v___x_174_, 0);
v___x_177_ = v___x_174_;
goto v_reusejp_176_;
}
else
{
lean_object* v_reuseFailAlloc_178_; 
v_reuseFailAlloc_178_ = lean_alloc_ctor(0, 1, 0);
lean_ctor_set(v_reuseFailAlloc_178_, 0, v_a_172_);
v___x_177_ = v_reuseFailAlloc_178_;
goto v_reusejp_176_;
}
v_reusejp_176_:
{
return v___x_177_;
}
}
}
else
{
lean_object* v_a_180_; lean_object* v___x_181_; lean_object* v___x_182_; 
v_a_180_ = lean_ctor_get(v___x_161_, 0);
lean_inc(v_a_180_);
lean_dec_ref_known(v___x_161_, 1);
v___x_181_ = ((lean_object*)(lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__12));
lean_inc(v_json_159_);
v___x_182_ = lp_proofwidgets_Lean_Json_getObjValAs_x3f___at___00ProofWidgets_MarkdownDisplay_instFromJsonProps_fromJson_spec__0(v_json_159_, v___x_181_);
if (lean_obj_tag(v___x_182_) == 0)
{
lean_object* v_a_183_; lean_object* v___x_185_; uint8_t v_isShared_186_; uint8_t v_isSharedCheck_192_; 
lean_dec(v_a_180_);
lean_dec(v_json_159_);
v_a_183_ = lean_ctor_get(v___x_182_, 0);
v_isSharedCheck_192_ = !lean_is_exclusive(v___x_182_);
if (v_isSharedCheck_192_ == 0)
{
v___x_185_ = v___x_182_;
v_isShared_186_ = v_isSharedCheck_192_;
goto v_resetjp_184_;
}
else
{
lean_inc(v_a_183_);
lean_dec(v___x_182_);
v___x_185_ = lean_box(0);
v_isShared_186_ = v_isSharedCheck_192_;
goto v_resetjp_184_;
}
v_resetjp_184_:
{
lean_object* v___x_187_; lean_object* v___x_188_; lean_object* v___x_190_; 
v___x_187_ = lean_obj_once(&lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__16, &lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__16_once, _init_lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__16);
v___x_188_ = lean_string_append(v___x_187_, v_a_183_);
lean_dec(v_a_183_);
if (v_isShared_186_ == 0)
{
lean_ctor_set(v___x_185_, 0, v___x_188_);
v___x_190_ = v___x_185_;
goto v_reusejp_189_;
}
else
{
lean_object* v_reuseFailAlloc_191_; 
v_reuseFailAlloc_191_ = lean_alloc_ctor(0, 1, 0);
lean_ctor_set(v_reuseFailAlloc_191_, 0, v___x_188_);
v___x_190_ = v_reuseFailAlloc_191_;
goto v_reusejp_189_;
}
v_reusejp_189_:
{
return v___x_190_;
}
}
}
else
{
if (lean_obj_tag(v___x_182_) == 0)
{
lean_object* v_a_193_; lean_object* v___x_195_; uint8_t v_isShared_196_; uint8_t v_isSharedCheck_200_; 
lean_dec(v_a_180_);
lean_dec(v_json_159_);
v_a_193_ = lean_ctor_get(v___x_182_, 0);
v_isSharedCheck_200_ = !lean_is_exclusive(v___x_182_);
if (v_isSharedCheck_200_ == 0)
{
v___x_195_ = v___x_182_;
v_isShared_196_ = v_isSharedCheck_200_;
goto v_resetjp_194_;
}
else
{
lean_inc(v_a_193_);
lean_dec(v___x_182_);
v___x_195_ = lean_box(0);
v_isShared_196_ = v_isSharedCheck_200_;
goto v_resetjp_194_;
}
v_resetjp_194_:
{
lean_object* v___x_198_; 
if (v_isShared_196_ == 0)
{
lean_ctor_set_tag(v___x_195_, 0);
v___x_198_ = v___x_195_;
goto v_reusejp_197_;
}
else
{
lean_object* v_reuseFailAlloc_199_; 
v_reuseFailAlloc_199_ = lean_alloc_ctor(0, 1, 0);
lean_ctor_set(v_reuseFailAlloc_199_, 0, v_a_193_);
v___x_198_ = v_reuseFailAlloc_199_;
goto v_reusejp_197_;
}
v_reusejp_197_:
{
return v___x_198_;
}
}
}
else
{
lean_object* v_a_201_; lean_object* v___x_202_; lean_object* v___x_203_; 
v_a_201_ = lean_ctor_get(v___x_182_, 0);
lean_inc(v_a_201_);
lean_dec_ref_known(v___x_182_, 1);
v___x_202_ = ((lean_object*)(lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__17));
lean_inc(v_json_159_);
v___x_203_ = l_Lean_Json_getObjValAs_x3f___at___00Lean_Server_instFromJsonIlean_fromJson_spec__0(v_json_159_, v___x_202_);
if (lean_obj_tag(v___x_203_) == 0)
{
lean_object* v_a_204_; lean_object* v___x_206_; uint8_t v_isShared_207_; uint8_t v_isSharedCheck_213_; 
lean_dec(v_a_201_);
lean_dec(v_a_180_);
lean_dec(v_json_159_);
v_a_204_ = lean_ctor_get(v___x_203_, 0);
v_isSharedCheck_213_ = !lean_is_exclusive(v___x_203_);
if (v_isSharedCheck_213_ == 0)
{
v___x_206_ = v___x_203_;
v_isShared_207_ = v_isSharedCheck_213_;
goto v_resetjp_205_;
}
else
{
lean_inc(v_a_204_);
lean_dec(v___x_203_);
v___x_206_ = lean_box(0);
v_isShared_207_ = v_isSharedCheck_213_;
goto v_resetjp_205_;
}
v_resetjp_205_:
{
lean_object* v___x_208_; lean_object* v___x_209_; lean_object* v___x_211_; 
v___x_208_ = lean_obj_once(&lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__21, &lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__21_once, _init_lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__21);
v___x_209_ = lean_string_append(v___x_208_, v_a_204_);
lean_dec(v_a_204_);
if (v_isShared_207_ == 0)
{
lean_ctor_set(v___x_206_, 0, v___x_209_);
v___x_211_ = v___x_206_;
goto v_reusejp_210_;
}
else
{
lean_object* v_reuseFailAlloc_212_; 
v_reuseFailAlloc_212_ = lean_alloc_ctor(0, 1, 0);
lean_ctor_set(v_reuseFailAlloc_212_, 0, v___x_209_);
v___x_211_ = v_reuseFailAlloc_212_;
goto v_reusejp_210_;
}
v_reusejp_210_:
{
return v___x_211_;
}
}
}
else
{
if (lean_obj_tag(v___x_203_) == 0)
{
lean_object* v_a_214_; lean_object* v___x_216_; uint8_t v_isShared_217_; uint8_t v_isSharedCheck_221_; 
lean_dec(v_a_201_);
lean_dec(v_a_180_);
lean_dec(v_json_159_);
v_a_214_ = lean_ctor_get(v___x_203_, 0);
v_isSharedCheck_221_ = !lean_is_exclusive(v___x_203_);
if (v_isSharedCheck_221_ == 0)
{
v___x_216_ = v___x_203_;
v_isShared_217_ = v_isSharedCheck_221_;
goto v_resetjp_215_;
}
else
{
lean_inc(v_a_214_);
lean_dec(v___x_203_);
v___x_216_ = lean_box(0);
v_isShared_217_ = v_isSharedCheck_221_;
goto v_resetjp_215_;
}
v_resetjp_215_:
{
lean_object* v___x_219_; 
if (v_isShared_217_ == 0)
{
lean_ctor_set_tag(v___x_216_, 0);
v___x_219_ = v___x_216_;
goto v_reusejp_218_;
}
else
{
lean_object* v_reuseFailAlloc_220_; 
v_reuseFailAlloc_220_ = lean_alloc_ctor(0, 1, 0);
lean_ctor_set(v_reuseFailAlloc_220_, 0, v_a_214_);
v___x_219_ = v_reuseFailAlloc_220_;
goto v_reusejp_218_;
}
v_reusejp_218_:
{
return v___x_219_;
}
}
}
else
{
lean_object* v_a_222_; lean_object* v___x_223_; lean_object* v___x_224_; 
v_a_222_ = lean_ctor_get(v___x_203_, 0);
lean_inc(v_a_222_);
lean_dec_ref_known(v___x_203_, 1);
v___x_223_ = ((lean_object*)(lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__22));
lean_inc(v_json_159_);
v___x_224_ = l_Lean_Json_getObjValAs_x3f___at___00Lean_Server_instFromJsonIlean_fromJson_spec__0(v_json_159_, v___x_223_);
if (lean_obj_tag(v___x_224_) == 0)
{
lean_object* v_a_225_; lean_object* v___x_227_; uint8_t v_isShared_228_; uint8_t v_isSharedCheck_234_; 
lean_dec(v_a_222_);
lean_dec(v_a_201_);
lean_dec(v_a_180_);
lean_dec(v_json_159_);
v_a_225_ = lean_ctor_get(v___x_224_, 0);
v_isSharedCheck_234_ = !lean_is_exclusive(v___x_224_);
if (v_isSharedCheck_234_ == 0)
{
v___x_227_ = v___x_224_;
v_isShared_228_ = v_isSharedCheck_234_;
goto v_resetjp_226_;
}
else
{
lean_inc(v_a_225_);
lean_dec(v___x_224_);
v___x_227_ = lean_box(0);
v_isShared_228_ = v_isSharedCheck_234_;
goto v_resetjp_226_;
}
v_resetjp_226_:
{
lean_object* v___x_229_; lean_object* v___x_230_; lean_object* v___x_232_; 
v___x_229_ = lean_obj_once(&lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__26, &lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__26_once, _init_lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__26);
v___x_230_ = lean_string_append(v___x_229_, v_a_225_);
lean_dec(v_a_225_);
if (v_isShared_228_ == 0)
{
lean_ctor_set(v___x_227_, 0, v___x_230_);
v___x_232_ = v___x_227_;
goto v_reusejp_231_;
}
else
{
lean_object* v_reuseFailAlloc_233_; 
v_reuseFailAlloc_233_ = lean_alloc_ctor(0, 1, 0);
lean_ctor_set(v_reuseFailAlloc_233_, 0, v___x_230_);
v___x_232_ = v_reuseFailAlloc_233_;
goto v_reusejp_231_;
}
v_reusejp_231_:
{
return v___x_232_;
}
}
}
else
{
if (lean_obj_tag(v___x_224_) == 0)
{
lean_object* v_a_235_; lean_object* v___x_237_; uint8_t v_isShared_238_; uint8_t v_isSharedCheck_242_; 
lean_dec(v_a_222_);
lean_dec(v_a_201_);
lean_dec(v_a_180_);
lean_dec(v_json_159_);
v_a_235_ = lean_ctor_get(v___x_224_, 0);
v_isSharedCheck_242_ = !lean_is_exclusive(v___x_224_);
if (v_isSharedCheck_242_ == 0)
{
v___x_237_ = v___x_224_;
v_isShared_238_ = v_isSharedCheck_242_;
goto v_resetjp_236_;
}
else
{
lean_inc(v_a_235_);
lean_dec(v___x_224_);
v___x_237_ = lean_box(0);
v_isShared_238_ = v_isSharedCheck_242_;
goto v_resetjp_236_;
}
v_resetjp_236_:
{
lean_object* v___x_240_; 
if (v_isShared_238_ == 0)
{
lean_ctor_set_tag(v___x_237_, 0);
v___x_240_ = v___x_237_;
goto v_reusejp_239_;
}
else
{
lean_object* v_reuseFailAlloc_241_; 
v_reuseFailAlloc_241_ = lean_alloc_ctor(0, 1, 0);
lean_ctor_set(v_reuseFailAlloc_241_, 0, v_a_235_);
v___x_240_ = v_reuseFailAlloc_241_;
goto v_reusejp_239_;
}
v_reusejp_239_:
{
return v___x_240_;
}
}
}
else
{
lean_object* v_a_243_; lean_object* v___x_244_; lean_object* v___x_245_; 
v_a_243_ = lean_ctor_get(v___x_224_, 0);
lean_inc(v_a_243_);
lean_dec_ref_known(v___x_224_, 1);
v___x_244_ = ((lean_object*)(lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__27));
lean_inc(v_json_159_);
v___x_245_ = l_Lean_Json_getObjValAs_x3f___at___00Lean_Server_instFromJsonIlean_fromJson_spec__0(v_json_159_, v___x_244_);
if (lean_obj_tag(v___x_245_) == 0)
{
lean_object* v_a_246_; lean_object* v___x_248_; uint8_t v_isShared_249_; uint8_t v_isSharedCheck_255_; 
lean_dec(v_a_243_);
lean_dec(v_a_222_);
lean_dec(v_a_201_);
lean_dec(v_a_180_);
lean_dec(v_json_159_);
v_a_246_ = lean_ctor_get(v___x_245_, 0);
v_isSharedCheck_255_ = !lean_is_exclusive(v___x_245_);
if (v_isSharedCheck_255_ == 0)
{
v___x_248_ = v___x_245_;
v_isShared_249_ = v_isSharedCheck_255_;
goto v_resetjp_247_;
}
else
{
lean_inc(v_a_246_);
lean_dec(v___x_245_);
v___x_248_ = lean_box(0);
v_isShared_249_ = v_isSharedCheck_255_;
goto v_resetjp_247_;
}
v_resetjp_247_:
{
lean_object* v___x_250_; lean_object* v___x_251_; lean_object* v___x_253_; 
v___x_250_ = lean_obj_once(&lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__31, &lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__31_once, _init_lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__31);
v___x_251_ = lean_string_append(v___x_250_, v_a_246_);
lean_dec(v_a_246_);
if (v_isShared_249_ == 0)
{
lean_ctor_set(v___x_248_, 0, v___x_251_);
v___x_253_ = v___x_248_;
goto v_reusejp_252_;
}
else
{
lean_object* v_reuseFailAlloc_254_; 
v_reuseFailAlloc_254_ = lean_alloc_ctor(0, 1, 0);
lean_ctor_set(v_reuseFailAlloc_254_, 0, v___x_251_);
v___x_253_ = v_reuseFailAlloc_254_;
goto v_reusejp_252_;
}
v_reusejp_252_:
{
return v___x_253_;
}
}
}
else
{
if (lean_obj_tag(v___x_245_) == 0)
{
lean_object* v_a_256_; lean_object* v___x_258_; uint8_t v_isShared_259_; uint8_t v_isSharedCheck_263_; 
lean_dec(v_a_243_);
lean_dec(v_a_222_);
lean_dec(v_a_201_);
lean_dec(v_a_180_);
lean_dec(v_json_159_);
v_a_256_ = lean_ctor_get(v___x_245_, 0);
v_isSharedCheck_263_ = !lean_is_exclusive(v___x_245_);
if (v_isSharedCheck_263_ == 0)
{
v___x_258_ = v___x_245_;
v_isShared_259_ = v_isSharedCheck_263_;
goto v_resetjp_257_;
}
else
{
lean_inc(v_a_256_);
lean_dec(v___x_245_);
v___x_258_ = lean_box(0);
v_isShared_259_ = v_isSharedCheck_263_;
goto v_resetjp_257_;
}
v_resetjp_257_:
{
lean_object* v___x_261_; 
if (v_isShared_259_ == 0)
{
lean_ctor_set_tag(v___x_258_, 0);
v___x_261_ = v___x_258_;
goto v_reusejp_260_;
}
else
{
lean_object* v_reuseFailAlloc_262_; 
v_reuseFailAlloc_262_ = lean_alloc_ctor(0, 1, 0);
lean_ctor_set(v_reuseFailAlloc_262_, 0, v_a_256_);
v___x_261_ = v_reuseFailAlloc_262_;
goto v_reusejp_260_;
}
v_reusejp_260_:
{
return v___x_261_;
}
}
}
else
{
lean_object* v_a_264_; lean_object* v___x_265_; lean_object* v___x_266_; 
v_a_264_ = lean_ctor_get(v___x_245_, 0);
lean_inc(v_a_264_);
lean_dec_ref_known(v___x_245_, 1);
v___x_265_ = ((lean_object*)(lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__32));
lean_inc(v_json_159_);
v___x_266_ = lp_competition_Lean_Json_getObjValAs_x3f___at___00R24DotBankHarness_instFromJsonBankCase_fromJson_spec__0(v_json_159_, v___x_265_);
if (lean_obj_tag(v___x_266_) == 0)
{
lean_object* v_a_267_; lean_object* v___x_269_; uint8_t v_isShared_270_; uint8_t v_isSharedCheck_276_; 
lean_dec(v_a_264_);
lean_dec(v_a_243_);
lean_dec(v_a_222_);
lean_dec(v_a_201_);
lean_dec(v_a_180_);
lean_dec(v_json_159_);
v_a_267_ = lean_ctor_get(v___x_266_, 0);
v_isSharedCheck_276_ = !lean_is_exclusive(v___x_266_);
if (v_isSharedCheck_276_ == 0)
{
v___x_269_ = v___x_266_;
v_isShared_270_ = v_isSharedCheck_276_;
goto v_resetjp_268_;
}
else
{
lean_inc(v_a_267_);
lean_dec(v___x_266_);
v___x_269_ = lean_box(0);
v_isShared_270_ = v_isSharedCheck_276_;
goto v_resetjp_268_;
}
v_resetjp_268_:
{
lean_object* v___x_271_; lean_object* v___x_272_; lean_object* v___x_274_; 
v___x_271_ = lean_obj_once(&lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__36, &lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__36_once, _init_lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__36);
v___x_272_ = lean_string_append(v___x_271_, v_a_267_);
lean_dec(v_a_267_);
if (v_isShared_270_ == 0)
{
lean_ctor_set(v___x_269_, 0, v___x_272_);
v___x_274_ = v___x_269_;
goto v_reusejp_273_;
}
else
{
lean_object* v_reuseFailAlloc_275_; 
v_reuseFailAlloc_275_ = lean_alloc_ctor(0, 1, 0);
lean_ctor_set(v_reuseFailAlloc_275_, 0, v___x_272_);
v___x_274_ = v_reuseFailAlloc_275_;
goto v_reusejp_273_;
}
v_reusejp_273_:
{
return v___x_274_;
}
}
}
else
{
if (lean_obj_tag(v___x_266_) == 0)
{
lean_object* v_a_277_; lean_object* v___x_279_; uint8_t v_isShared_280_; uint8_t v_isSharedCheck_284_; 
lean_dec(v_a_264_);
lean_dec(v_a_243_);
lean_dec(v_a_222_);
lean_dec(v_a_201_);
lean_dec(v_a_180_);
lean_dec(v_json_159_);
v_a_277_ = lean_ctor_get(v___x_266_, 0);
v_isSharedCheck_284_ = !lean_is_exclusive(v___x_266_);
if (v_isSharedCheck_284_ == 0)
{
v___x_279_ = v___x_266_;
v_isShared_280_ = v_isSharedCheck_284_;
goto v_resetjp_278_;
}
else
{
lean_inc(v_a_277_);
lean_dec(v___x_266_);
v___x_279_ = lean_box(0);
v_isShared_280_ = v_isSharedCheck_284_;
goto v_resetjp_278_;
}
v_resetjp_278_:
{
lean_object* v___x_282_; 
if (v_isShared_280_ == 0)
{
lean_ctor_set_tag(v___x_279_, 0);
v___x_282_ = v___x_279_;
goto v_reusejp_281_;
}
else
{
lean_object* v_reuseFailAlloc_283_; 
v_reuseFailAlloc_283_ = lean_alloc_ctor(0, 1, 0);
lean_ctor_set(v_reuseFailAlloc_283_, 0, v_a_277_);
v___x_282_ = v_reuseFailAlloc_283_;
goto v_reusejp_281_;
}
v_reusejp_281_:
{
return v___x_282_;
}
}
}
else
{
lean_object* v_a_285_; lean_object* v___x_286_; lean_object* v___x_287_; 
v_a_285_ = lean_ctor_get(v___x_266_, 0);
lean_inc(v_a_285_);
lean_dec_ref_known(v___x_266_, 1);
v___x_286_ = ((lean_object*)(lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__37));
lean_inc(v_json_159_);
v___x_287_ = lp_competition_Lean_Json_getObjValAs_x3f___at___00R24DotBankHarness_instFromJsonBankCase_fromJson_spec__0(v_json_159_, v___x_286_);
if (lean_obj_tag(v___x_287_) == 0)
{
lean_object* v_a_288_; lean_object* v___x_290_; uint8_t v_isShared_291_; uint8_t v_isSharedCheck_297_; 
lean_dec(v_a_285_);
lean_dec(v_a_264_);
lean_dec(v_a_243_);
lean_dec(v_a_222_);
lean_dec(v_a_201_);
lean_dec(v_a_180_);
lean_dec(v_json_159_);
v_a_288_ = lean_ctor_get(v___x_287_, 0);
v_isSharedCheck_297_ = !lean_is_exclusive(v___x_287_);
if (v_isSharedCheck_297_ == 0)
{
v___x_290_ = v___x_287_;
v_isShared_291_ = v_isSharedCheck_297_;
goto v_resetjp_289_;
}
else
{
lean_inc(v_a_288_);
lean_dec(v___x_287_);
v___x_290_ = lean_box(0);
v_isShared_291_ = v_isSharedCheck_297_;
goto v_resetjp_289_;
}
v_resetjp_289_:
{
lean_object* v___x_292_; lean_object* v___x_293_; lean_object* v___x_295_; 
v___x_292_ = lean_obj_once(&lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__41, &lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__41_once, _init_lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__41);
v___x_293_ = lean_string_append(v___x_292_, v_a_288_);
lean_dec(v_a_288_);
if (v_isShared_291_ == 0)
{
lean_ctor_set(v___x_290_, 0, v___x_293_);
v___x_295_ = v___x_290_;
goto v_reusejp_294_;
}
else
{
lean_object* v_reuseFailAlloc_296_; 
v_reuseFailAlloc_296_ = lean_alloc_ctor(0, 1, 0);
lean_ctor_set(v_reuseFailAlloc_296_, 0, v___x_293_);
v___x_295_ = v_reuseFailAlloc_296_;
goto v_reusejp_294_;
}
v_reusejp_294_:
{
return v___x_295_;
}
}
}
else
{
if (lean_obj_tag(v___x_287_) == 0)
{
lean_object* v_a_298_; lean_object* v___x_300_; uint8_t v_isShared_301_; uint8_t v_isSharedCheck_305_; 
lean_dec(v_a_285_);
lean_dec(v_a_264_);
lean_dec(v_a_243_);
lean_dec(v_a_222_);
lean_dec(v_a_201_);
lean_dec(v_a_180_);
lean_dec(v_json_159_);
v_a_298_ = lean_ctor_get(v___x_287_, 0);
v_isSharedCheck_305_ = !lean_is_exclusive(v___x_287_);
if (v_isSharedCheck_305_ == 0)
{
v___x_300_ = v___x_287_;
v_isShared_301_ = v_isSharedCheck_305_;
goto v_resetjp_299_;
}
else
{
lean_inc(v_a_298_);
lean_dec(v___x_287_);
v___x_300_ = lean_box(0);
v_isShared_301_ = v_isSharedCheck_305_;
goto v_resetjp_299_;
}
v_resetjp_299_:
{
lean_object* v___x_303_; 
if (v_isShared_301_ == 0)
{
lean_ctor_set_tag(v___x_300_, 0);
v___x_303_ = v___x_300_;
goto v_reusejp_302_;
}
else
{
lean_object* v_reuseFailAlloc_304_; 
v_reuseFailAlloc_304_ = lean_alloc_ctor(0, 1, 0);
lean_ctor_set(v_reuseFailAlloc_304_, 0, v_a_298_);
v___x_303_ = v_reuseFailAlloc_304_;
goto v_reusejp_302_;
}
v_reusejp_302_:
{
return v___x_303_;
}
}
}
else
{
lean_object* v_a_306_; lean_object* v___x_307_; lean_object* v___x_308_; 
v_a_306_ = lean_ctor_get(v___x_287_, 0);
lean_inc(v_a_306_);
lean_dec_ref_known(v___x_287_, 1);
v___x_307_ = ((lean_object*)(lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__42));
v___x_308_ = l_Lean_Json_getObjValAs_x3f___at___00Lean_Lsp_instFromJsonSemanticTokens_fromJson_spec__0(v_json_159_, v___x_307_);
if (lean_obj_tag(v___x_308_) == 0)
{
lean_object* v_a_309_; lean_object* v___x_311_; uint8_t v_isShared_312_; uint8_t v_isSharedCheck_318_; 
lean_dec(v_a_306_);
lean_dec(v_a_285_);
lean_dec(v_a_264_);
lean_dec(v_a_243_);
lean_dec(v_a_222_);
lean_dec(v_a_201_);
lean_dec(v_a_180_);
v_a_309_ = lean_ctor_get(v___x_308_, 0);
v_isSharedCheck_318_ = !lean_is_exclusive(v___x_308_);
if (v_isSharedCheck_318_ == 0)
{
v___x_311_ = v___x_308_;
v_isShared_312_ = v_isSharedCheck_318_;
goto v_resetjp_310_;
}
else
{
lean_inc(v_a_309_);
lean_dec(v___x_308_);
v___x_311_ = lean_box(0);
v_isShared_312_ = v_isSharedCheck_318_;
goto v_resetjp_310_;
}
v_resetjp_310_:
{
lean_object* v___x_313_; lean_object* v___x_314_; lean_object* v___x_316_; 
v___x_313_ = lean_obj_once(&lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__46, &lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__46_once, _init_lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__46);
v___x_314_ = lean_string_append(v___x_313_, v_a_309_);
lean_dec(v_a_309_);
if (v_isShared_312_ == 0)
{
lean_ctor_set(v___x_311_, 0, v___x_314_);
v___x_316_ = v___x_311_;
goto v_reusejp_315_;
}
else
{
lean_object* v_reuseFailAlloc_317_; 
v_reuseFailAlloc_317_ = lean_alloc_ctor(0, 1, 0);
lean_ctor_set(v_reuseFailAlloc_317_, 0, v___x_314_);
v___x_316_ = v_reuseFailAlloc_317_;
goto v_reusejp_315_;
}
v_reusejp_315_:
{
return v___x_316_;
}
}
}
else
{
if (lean_obj_tag(v___x_308_) == 0)
{
lean_object* v_a_319_; lean_object* v___x_321_; uint8_t v_isShared_322_; uint8_t v_isSharedCheck_326_; 
lean_dec(v_a_306_);
lean_dec(v_a_285_);
lean_dec(v_a_264_);
lean_dec(v_a_243_);
lean_dec(v_a_222_);
lean_dec(v_a_201_);
lean_dec(v_a_180_);
v_a_319_ = lean_ctor_get(v___x_308_, 0);
v_isSharedCheck_326_ = !lean_is_exclusive(v___x_308_);
if (v_isSharedCheck_326_ == 0)
{
v___x_321_ = v___x_308_;
v_isShared_322_ = v_isSharedCheck_326_;
goto v_resetjp_320_;
}
else
{
lean_inc(v_a_319_);
lean_dec(v___x_308_);
v___x_321_ = lean_box(0);
v_isShared_322_ = v_isSharedCheck_326_;
goto v_resetjp_320_;
}
v_resetjp_320_:
{
lean_object* v___x_324_; 
if (v_isShared_322_ == 0)
{
lean_ctor_set_tag(v___x_321_, 0);
v___x_324_ = v___x_321_;
goto v_reusejp_323_;
}
else
{
lean_object* v_reuseFailAlloc_325_; 
v_reuseFailAlloc_325_ = lean_alloc_ctor(0, 1, 0);
lean_ctor_set(v_reuseFailAlloc_325_, 0, v_a_319_);
v___x_324_ = v_reuseFailAlloc_325_;
goto v_reusejp_323_;
}
v_reusejp_323_:
{
return v___x_324_;
}
}
}
else
{
lean_object* v_a_327_; lean_object* v___x_329_; uint8_t v_isShared_330_; uint8_t v_isSharedCheck_335_; 
v_a_327_ = lean_ctor_get(v___x_308_, 0);
v_isSharedCheck_335_ = !lean_is_exclusive(v___x_308_);
if (v_isSharedCheck_335_ == 0)
{
v___x_329_ = v___x_308_;
v_isShared_330_ = v_isSharedCheck_335_;
goto v_resetjp_328_;
}
else
{
lean_inc(v_a_327_);
lean_dec(v___x_308_);
v___x_329_ = lean_box(0);
v_isShared_330_ = v_isSharedCheck_335_;
goto v_resetjp_328_;
}
v_resetjp_328_:
{
lean_object* v___x_331_; lean_object* v___x_333_; 
v___x_331_ = lean_alloc_ctor(0, 8, 0);
lean_ctor_set(v___x_331_, 0, v_a_180_);
lean_ctor_set(v___x_331_, 1, v_a_201_);
lean_ctor_set(v___x_331_, 2, v_a_222_);
lean_ctor_set(v___x_331_, 3, v_a_243_);
lean_ctor_set(v___x_331_, 4, v_a_264_);
lean_ctor_set(v___x_331_, 5, v_a_285_);
lean_ctor_set(v___x_331_, 6, v_a_306_);
lean_ctor_set(v___x_331_, 7, v_a_327_);
if (v_isShared_330_ == 0)
{
lean_ctor_set(v___x_329_, 0, v___x_331_);
v___x_333_ = v___x_329_;
goto v_reusejp_332_;
}
else
{
lean_object* v_reuseFailAlloc_334_; 
v_reuseFailAlloc_334_ = lean_alloc_ctor(1, 1, 0);
lean_ctor_set(v_reuseFailAlloc_334_, 0, v___x_331_);
v___x_333_ = v_reuseFailAlloc_334_;
goto v_reusejp_332_;
}
v_reusejp_332_:
{
return v___x_333_;
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
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_mapMUnsafe_map___at___00Lean_Array_fromJson_x3f___at___00Lean_Json_getObjValAs_x3f___at___00R24DotBankHarness_instFromJsonPlan_fromJson_spec__0_spec__0_spec__1(size_t v_sz_338_, size_t v_i_339_, lean_object* v_bs_340_){
_start:
{
uint8_t v___x_341_; 
v___x_341_ = lean_usize_dec_lt(v_i_339_, v_sz_338_);
if (v___x_341_ == 0)
{
lean_object* v___x_342_; 
v___x_342_ = lean_alloc_ctor(1, 1, 0);
lean_ctor_set(v___x_342_, 0, v_bs_340_);
return v___x_342_;
}
else
{
lean_object* v_v_343_; lean_object* v___x_344_; 
v_v_343_ = lean_array_uget_borrowed(v_bs_340_, v_i_339_);
lean_inc(v_v_343_);
v___x_344_ = lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson(v_v_343_);
if (lean_obj_tag(v___x_344_) == 0)
{
lean_object* v_a_345_; lean_object* v___x_347_; uint8_t v_isShared_348_; uint8_t v_isSharedCheck_352_; 
lean_dec_ref(v_bs_340_);
v_a_345_ = lean_ctor_get(v___x_344_, 0);
v_isSharedCheck_352_ = !lean_is_exclusive(v___x_344_);
if (v_isSharedCheck_352_ == 0)
{
v___x_347_ = v___x_344_;
v_isShared_348_ = v_isSharedCheck_352_;
goto v_resetjp_346_;
}
else
{
lean_inc(v_a_345_);
lean_dec(v___x_344_);
v___x_347_ = lean_box(0);
v_isShared_348_ = v_isSharedCheck_352_;
goto v_resetjp_346_;
}
v_resetjp_346_:
{
lean_object* v___x_350_; 
if (v_isShared_348_ == 0)
{
v___x_350_ = v___x_347_;
goto v_reusejp_349_;
}
else
{
lean_object* v_reuseFailAlloc_351_; 
v_reuseFailAlloc_351_ = lean_alloc_ctor(0, 1, 0);
lean_ctor_set(v_reuseFailAlloc_351_, 0, v_a_345_);
v___x_350_ = v_reuseFailAlloc_351_;
goto v_reusejp_349_;
}
v_reusejp_349_:
{
return v___x_350_;
}
}
}
else
{
lean_object* v_a_353_; lean_object* v___x_354_; lean_object* v_bs_x27_355_; size_t v___x_356_; size_t v___x_357_; lean_object* v___x_358_; 
v_a_353_ = lean_ctor_get(v___x_344_, 0);
lean_inc(v_a_353_);
lean_dec_ref_known(v___x_344_, 1);
v___x_354_ = lean_unsigned_to_nat(0u);
v_bs_x27_355_ = lean_array_uset(v_bs_340_, v_i_339_, v___x_354_);
v___x_356_ = ((size_t)1ULL);
v___x_357_ = lean_usize_add(v_i_339_, v___x_356_);
v___x_358_ = lean_array_uset(v_bs_x27_355_, v_i_339_, v_a_353_);
v_i_339_ = v___x_357_;
v_bs_340_ = v___x_358_;
goto _start;
}
}
}
}
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_mapMUnsafe_map___at___00Lean_Array_fromJson_x3f___at___00Lean_Json_getObjValAs_x3f___at___00R24DotBankHarness_instFromJsonPlan_fromJson_spec__0_spec__0_spec__1___boxed(lean_object* v_sz_360_, lean_object* v_i_361_, lean_object* v_bs_362_){
_start:
{
size_t v_sz_boxed_363_; size_t v_i_boxed_364_; lean_object* v_res_365_; 
v_sz_boxed_363_ = lean_unbox_usize(v_sz_360_);
lean_dec(v_sz_360_);
v_i_boxed_364_ = lean_unbox_usize(v_i_361_);
lean_dec(v_i_361_);
v_res_365_ = lp_competition___private_Init_Data_Array_Basic_0__Array_mapMUnsafe_map___at___00Lean_Array_fromJson_x3f___at___00Lean_Json_getObjValAs_x3f___at___00R24DotBankHarness_instFromJsonPlan_fromJson_spec__0_spec__0_spec__1(v_sz_boxed_363_, v_i_boxed_364_, v_bs_362_);
return v_res_365_;
}
}
LEAN_EXPORT lean_object* lp_competition_Lean_Array_fromJson_x3f___at___00Lean_Json_getObjValAs_x3f___at___00R24DotBankHarness_instFromJsonPlan_fromJson_spec__0_spec__0(lean_object* v_x_366_){
_start:
{
if (lean_obj_tag(v_x_366_) == 4)
{
lean_object* v_elems_367_; size_t v_sz_368_; size_t v___x_369_; lean_object* v___x_370_; 
v_elems_367_ = lean_ctor_get(v_x_366_, 0);
lean_inc_ref(v_elems_367_);
lean_dec_ref_known(v_x_366_, 1);
v_sz_368_ = lean_array_size(v_elems_367_);
v___x_369_ = ((size_t)0ULL);
v___x_370_ = lp_competition___private_Init_Data_Array_Basic_0__Array_mapMUnsafe_map___at___00Lean_Array_fromJson_x3f___at___00Lean_Json_getObjValAs_x3f___at___00R24DotBankHarness_instFromJsonPlan_fromJson_spec__0_spec__0_spec__1(v_sz_368_, v___x_369_, v_elems_367_);
return v___x_370_;
}
else
{
lean_object* v___x_371_; lean_object* v___x_372_; lean_object* v___x_373_; lean_object* v___x_374_; lean_object* v___x_375_; lean_object* v___x_376_; lean_object* v___x_377_; 
v___x_371_ = ((lean_object*)(lp_competition_Lean_Array_fromJson_x3f___at___00Lean_Json_getObjValAs_x3f___at___00R24DotBankHarness_instFromJsonBankCase_fromJson_spec__0_spec__0___closed__0));
v___x_372_ = lean_unsigned_to_nat(80u);
v___x_373_ = l_Lean_Json_pretty(v_x_366_, v___x_372_);
v___x_374_ = lean_string_append(v___x_371_, v___x_373_);
lean_dec_ref(v___x_373_);
v___x_375_ = ((lean_object*)(lp_competition_Lean_Array_fromJson_x3f___at___00Lean_Json_getObjValAs_x3f___at___00R24DotBankHarness_instFromJsonBankCase_fromJson_spec__0_spec__0___closed__1));
v___x_376_ = lean_string_append(v___x_374_, v___x_375_);
v___x_377_ = lean_alloc_ctor(0, 1, 0);
lean_ctor_set(v___x_377_, 0, v___x_376_);
return v___x_377_;
}
}
}
LEAN_EXPORT lean_object* lp_competition_Lean_Json_getObjValAs_x3f___at___00R24DotBankHarness_instFromJsonPlan_fromJson_spec__0(lean_object* v_j_378_, lean_object* v_k_379_){
_start:
{
lean_object* v___x_380_; lean_object* v___x_381_; 
v___x_380_ = l_Lean_Json_getObjValD(v_j_378_, v_k_379_);
v___x_381_ = lp_competition_Lean_Array_fromJson_x3f___at___00Lean_Json_getObjValAs_x3f___at___00R24DotBankHarness_instFromJsonPlan_fromJson_spec__0_spec__0(v___x_380_);
return v___x_381_;
}
}
LEAN_EXPORT lean_object* lp_competition_Lean_Json_getObjValAs_x3f___at___00R24DotBankHarness_instFromJsonPlan_fromJson_spec__0___boxed(lean_object* v_j_382_, lean_object* v_k_383_){
_start:
{
lean_object* v_res_384_; 
v_res_384_ = lp_competition_Lean_Json_getObjValAs_x3f___at___00R24DotBankHarness_instFromJsonPlan_fromJson_spec__0(v_j_382_, v_k_383_);
lean_dec_ref(v_k_383_);
return v_res_384_;
}
}
static lean_object* _init_lp_competition_R24DotBankHarness_instFromJsonPlan_fromJson___closed__3(void){
_start:
{
uint8_t v___x_390_; lean_object* v___x_391_; lean_object* v___x_392_; 
v___x_390_ = 1;
v___x_391_ = ((lean_object*)(lp_competition_R24DotBankHarness_instFromJsonPlan_fromJson___closed__2));
v___x_392_ = l_Lean_Name_toStringWithToken___at___00Lean_Name_toString_spec__0(v___x_391_, v___x_390_);
return v___x_392_;
}
}
static lean_object* _init_lp_competition_R24DotBankHarness_instFromJsonPlan_fromJson___closed__4(void){
_start:
{
lean_object* v___x_393_; lean_object* v___x_394_; lean_object* v___x_395_; 
v___x_393_ = ((lean_object*)(lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__5));
v___x_394_ = lean_obj_once(&lp_competition_R24DotBankHarness_instFromJsonPlan_fromJson___closed__3, &lp_competition_R24DotBankHarness_instFromJsonPlan_fromJson___closed__3_once, _init_lp_competition_R24DotBankHarness_instFromJsonPlan_fromJson___closed__3);
v___x_395_ = lean_string_append(v___x_394_, v___x_393_);
return v___x_395_;
}
}
static lean_object* _init_lp_competition_R24DotBankHarness_instFromJsonPlan_fromJson___closed__6(void){
_start:
{
uint8_t v___x_398_; lean_object* v___x_399_; lean_object* v___x_400_; 
v___x_398_ = 1;
v___x_399_ = ((lean_object*)(lp_competition_R24DotBankHarness_instFromJsonPlan_fromJson___closed__5));
v___x_400_ = l_Lean_Name_toStringWithToken___at___00Lean_Name_toString_spec__0(v___x_399_, v___x_398_);
return v___x_400_;
}
}
static lean_object* _init_lp_competition_R24DotBankHarness_instFromJsonPlan_fromJson___closed__7(void){
_start:
{
lean_object* v___x_401_; lean_object* v___x_402_; lean_object* v___x_403_; 
v___x_401_ = lean_obj_once(&lp_competition_R24DotBankHarness_instFromJsonPlan_fromJson___closed__6, &lp_competition_R24DotBankHarness_instFromJsonPlan_fromJson___closed__6_once, _init_lp_competition_R24DotBankHarness_instFromJsonPlan_fromJson___closed__6);
v___x_402_ = lean_obj_once(&lp_competition_R24DotBankHarness_instFromJsonPlan_fromJson___closed__4, &lp_competition_R24DotBankHarness_instFromJsonPlan_fromJson___closed__4_once, _init_lp_competition_R24DotBankHarness_instFromJsonPlan_fromJson___closed__4);
v___x_403_ = lean_string_append(v___x_402_, v___x_401_);
return v___x_403_;
}
}
static lean_object* _init_lp_competition_R24DotBankHarness_instFromJsonPlan_fromJson___closed__8(void){
_start:
{
lean_object* v___x_404_; lean_object* v___x_405_; lean_object* v___x_406_; 
v___x_404_ = ((lean_object*)(lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__10));
v___x_405_ = lean_obj_once(&lp_competition_R24DotBankHarness_instFromJsonPlan_fromJson___closed__7, &lp_competition_R24DotBankHarness_instFromJsonPlan_fromJson___closed__7_once, _init_lp_competition_R24DotBankHarness_instFromJsonPlan_fromJson___closed__7);
v___x_406_ = lean_string_append(v___x_405_, v___x_404_);
return v___x_406_;
}
}
LEAN_EXPORT lean_object* lp_competition_R24DotBankHarness_instFromJsonPlan_fromJson(lean_object* v_json_407_){
_start:
{
lean_object* v___x_408_; lean_object* v___x_409_; 
v___x_408_ = ((lean_object*)(lp_competition_R24DotBankHarness_instFromJsonPlan_fromJson___closed__0));
v___x_409_ = lp_competition_Lean_Json_getObjValAs_x3f___at___00R24DotBankHarness_instFromJsonPlan_fromJson_spec__0(v_json_407_, v___x_408_);
if (lean_obj_tag(v___x_409_) == 0)
{
lean_object* v_a_410_; lean_object* v___x_412_; uint8_t v_isShared_413_; uint8_t v_isSharedCheck_419_; 
v_a_410_ = lean_ctor_get(v___x_409_, 0);
v_isSharedCheck_419_ = !lean_is_exclusive(v___x_409_);
if (v_isSharedCheck_419_ == 0)
{
v___x_412_ = v___x_409_;
v_isShared_413_ = v_isSharedCheck_419_;
goto v_resetjp_411_;
}
else
{
lean_inc(v_a_410_);
lean_dec(v___x_409_);
v___x_412_ = lean_box(0);
v_isShared_413_ = v_isSharedCheck_419_;
goto v_resetjp_411_;
}
v_resetjp_411_:
{
lean_object* v___x_414_; lean_object* v___x_415_; lean_object* v___x_417_; 
v___x_414_ = lean_obj_once(&lp_competition_R24DotBankHarness_instFromJsonPlan_fromJson___closed__8, &lp_competition_R24DotBankHarness_instFromJsonPlan_fromJson___closed__8_once, _init_lp_competition_R24DotBankHarness_instFromJsonPlan_fromJson___closed__8);
v___x_415_ = lean_string_append(v___x_414_, v_a_410_);
lean_dec(v_a_410_);
if (v_isShared_413_ == 0)
{
lean_ctor_set(v___x_412_, 0, v___x_415_);
v___x_417_ = v___x_412_;
goto v_reusejp_416_;
}
else
{
lean_object* v_reuseFailAlloc_418_; 
v_reuseFailAlloc_418_ = lean_alloc_ctor(0, 1, 0);
lean_ctor_set(v_reuseFailAlloc_418_, 0, v___x_415_);
v___x_417_ = v_reuseFailAlloc_418_;
goto v_reusejp_416_;
}
v_reusejp_416_:
{
return v___x_417_;
}
}
}
else
{
if (lean_obj_tag(v___x_409_) == 0)
{
lean_object* v_a_420_; lean_object* v___x_422_; uint8_t v_isShared_423_; uint8_t v_isSharedCheck_427_; 
v_a_420_ = lean_ctor_get(v___x_409_, 0);
v_isSharedCheck_427_ = !lean_is_exclusive(v___x_409_);
if (v_isSharedCheck_427_ == 0)
{
v___x_422_ = v___x_409_;
v_isShared_423_ = v_isSharedCheck_427_;
goto v_resetjp_421_;
}
else
{
lean_inc(v_a_420_);
lean_dec(v___x_409_);
v___x_422_ = lean_box(0);
v_isShared_423_ = v_isSharedCheck_427_;
goto v_resetjp_421_;
}
v_resetjp_421_:
{
lean_object* v___x_425_; 
if (v_isShared_423_ == 0)
{
lean_ctor_set_tag(v___x_422_, 0);
v___x_425_ = v___x_422_;
goto v_reusejp_424_;
}
else
{
lean_object* v_reuseFailAlloc_426_; 
v_reuseFailAlloc_426_ = lean_alloc_ctor(0, 1, 0);
lean_ctor_set(v_reuseFailAlloc_426_, 0, v_a_420_);
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
lean_object* v_a_428_; lean_object* v___x_430_; uint8_t v_isShared_431_; uint8_t v_isSharedCheck_435_; 
v_a_428_ = lean_ctor_get(v___x_409_, 0);
v_isSharedCheck_435_ = !lean_is_exclusive(v___x_409_);
if (v_isSharedCheck_435_ == 0)
{
v___x_430_ = v___x_409_;
v_isShared_431_ = v_isSharedCheck_435_;
goto v_resetjp_429_;
}
else
{
lean_inc(v_a_428_);
lean_dec(v___x_409_);
v___x_430_ = lean_box(0);
v_isShared_431_ = v_isSharedCheck_435_;
goto v_resetjp_429_;
}
v_resetjp_429_:
{
lean_object* v___x_433_; 
if (v_isShared_431_ == 0)
{
v___x_433_ = v___x_430_;
goto v_reusejp_432_;
}
else
{
lean_object* v_reuseFailAlloc_434_; 
v_reuseFailAlloc_434_ = lean_alloc_ctor(1, 1, 0);
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
}
}
}
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_mapMUnsafe_map___at___00R24DotBankHarness_words_spec__0(size_t v_sz_438_, size_t v_i_439_, lean_object* v_bs_440_){
_start:
{
uint8_t v___x_441_; 
v___x_441_ = lean_usize_dec_lt(v_i_439_, v_sz_438_);
if (v___x_441_ == 0)
{
return v_bs_440_;
}
else
{
lean_object* v_v_442_; lean_object* v___x_443_; lean_object* v_bs_x27_444_; uint32_t v___x_445_; size_t v___x_446_; size_t v___x_447_; lean_object* v___x_448_; lean_object* v___x_449_; 
v_v_442_ = lean_array_uget(v_bs_440_, v_i_439_);
v___x_443_ = lean_unsigned_to_nat(0u);
v_bs_x27_444_ = lean_array_uset(v_bs_440_, v_i_439_, v___x_443_);
v___x_445_ = lean_uint32_of_nat(v_v_442_);
lean_dec(v_v_442_);
v___x_446_ = ((size_t)1ULL);
v___x_447_ = lean_usize_add(v_i_439_, v___x_446_);
v___x_448_ = lean_box_uint32(v___x_445_);
v___x_449_ = lean_array_uset(v_bs_x27_444_, v_i_439_, v___x_448_);
v_i_439_ = v___x_447_;
v_bs_440_ = v___x_449_;
goto _start;
}
}
}
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_mapMUnsafe_map___at___00R24DotBankHarness_words_spec__0___boxed(lean_object* v_sz_451_, lean_object* v_i_452_, lean_object* v_bs_453_){
_start:
{
size_t v_sz_boxed_454_; size_t v_i_boxed_455_; lean_object* v_res_456_; 
v_sz_boxed_454_ = lean_unbox_usize(v_sz_451_);
lean_dec(v_sz_451_);
v_i_boxed_455_ = lean_unbox_usize(v_i_452_);
lean_dec(v_i_452_);
v_res_456_ = lp_competition___private_Init_Data_Array_Basic_0__Array_mapMUnsafe_map___at___00R24DotBankHarness_words_spec__0(v_sz_boxed_454_, v_i_boxed_455_, v_bs_453_);
return v_res_456_;
}
}
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_mapMUnsafe_map___at___00R24DotBankHarness_words_spec__1(size_t v_sz_457_, size_t v_i_458_, lean_object* v_bs_459_){
_start:
{
uint8_t v___x_460_; 
v___x_460_ = lean_usize_dec_lt(v_i_458_, v_sz_457_);
if (v___x_460_ == 0)
{
return v_bs_459_;
}
else
{
lean_object* v_v_461_; lean_object* v___x_462_; lean_object* v_bs_x27_463_; size_t v_sz_464_; size_t v___x_465_; lean_object* v___x_466_; size_t v___x_467_; size_t v___x_468_; lean_object* v___x_469_; 
v_v_461_ = lean_array_uget(v_bs_459_, v_i_458_);
v___x_462_ = lean_unsigned_to_nat(0u);
v_bs_x27_463_ = lean_array_uset(v_bs_459_, v_i_458_, v___x_462_);
v_sz_464_ = lean_array_size(v_v_461_);
v___x_465_ = ((size_t)0ULL);
v___x_466_ = lp_competition___private_Init_Data_Array_Basic_0__Array_mapMUnsafe_map___at___00R24DotBankHarness_words_spec__0(v_sz_464_, v___x_465_, v_v_461_);
v___x_467_ = ((size_t)1ULL);
v___x_468_ = lean_usize_add(v_i_458_, v___x_467_);
v___x_469_ = lean_array_uset(v_bs_x27_463_, v_i_458_, v___x_466_);
v_i_458_ = v___x_468_;
v_bs_459_ = v___x_469_;
goto _start;
}
}
}
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_mapMUnsafe_map___at___00R24DotBankHarness_words_spec__1___boxed(lean_object* v_sz_471_, lean_object* v_i_472_, lean_object* v_bs_473_){
_start:
{
size_t v_sz_boxed_474_; size_t v_i_boxed_475_; lean_object* v_res_476_; 
v_sz_boxed_474_ = lean_unbox_usize(v_sz_471_);
lean_dec(v_sz_471_);
v_i_boxed_475_ = lean_unbox_usize(v_i_472_);
lean_dec(v_i_472_);
v_res_476_ = lp_competition___private_Init_Data_Array_Basic_0__Array_mapMUnsafe_map___at___00R24DotBankHarness_words_spec__1(v_sz_boxed_474_, v_i_boxed_475_, v_bs_473_);
return v_res_476_;
}
}
LEAN_EXPORT lean_object* lp_competition_R24DotBankHarness_words(lean_object* v_xs_477_){
_start:
{
size_t v_sz_478_; size_t v___x_479_; lean_object* v___x_480_; 
v_sz_478_ = lean_array_size(v_xs_477_);
v___x_479_ = ((size_t)0ULL);
v___x_480_ = lp_competition___private_Init_Data_Array_Basic_0__Array_mapMUnsafe_map___at___00R24DotBankHarness_words_spec__1(v_sz_478_, v___x_479_, v_xs_477_);
return v___x_480_;
}
}
LEAN_EXPORT lean_object* lp_competition_R24DotBankHarness_outputWords(lean_object* v_xs_481_){
_start:
{
size_t v_sz_482_; size_t v___x_483_; lean_object* v___x_484_; 
v_sz_482_ = lean_array_size(v_xs_481_);
v___x_483_ = ((size_t)0ULL);
v___x_484_ = lp_competition___private_Init_Data_Array_Basic_0__Array_mapMUnsafe_map___at___00R24DotBankHarness_words_spec__0(v_sz_482_, v___x_483_, v_xs_481_);
return v___x_484_;
}
}
static lean_object* _init_lp_competition_R24DotBankHarness_sumRemaining___boxed__const__1(void){
_start:
{
uint32_t v___x_485_; lean_object* v___x_486_; 
v___x_485_ = 0;
v___x_486_ = lean_box_uint32(v___x_485_);
return v___x_486_;
}
}
LEAN_EXPORT uint32_t lp_competition_R24DotBankHarness_sumRemaining(lean_object* v_out_487_, lean_object* v_index_488_, uint32_t v_acc_489_, lean_object* v_remaining_490_){
_start:
{
lean_object* v_zero_491_; uint8_t v_isZero_492_; 
v_zero_491_ = lean_unsigned_to_nat(0u);
v_isZero_492_ = lean_nat_dec_eq(v_remaining_490_, v_zero_491_);
if (v_isZero_492_ == 1)
{
lean_dec(v_remaining_490_);
lean_dec(v_index_488_);
return v_acc_489_;
}
else
{
lean_object* v_one_493_; lean_object* v_n_494_; lean_object* v___x_495_; lean_object* v___x_496_; lean_object* v___x_497_; uint32_t v___x_498_; uint32_t v___x_499_; 
v_one_493_ = lean_unsigned_to_nat(1u);
v_n_494_ = lean_nat_sub(v_remaining_490_, v_one_493_);
lean_dec(v_remaining_490_);
v___x_495_ = lean_nat_add(v_index_488_, v_one_493_);
v___x_496_ = lp_competition_R24DotBankHarness_sumRemaining___boxed__const__1;
v___x_497_ = lean_array_get_borrowed(v___x_496_, v_out_487_, v_index_488_);
lean_dec(v_index_488_);
v___x_498_ = lean_unbox_uint32(v___x_497_);
v___x_499_ = lean_uint32_add(v_acc_489_, v___x_498_);
v_index_488_ = v___x_495_;
v_acc_489_ = v___x_499_;
v_remaining_490_ = v_n_494_;
goto _start;
}
}
}
LEAN_EXPORT lean_object* lp_competition_R24DotBankHarness_sumRemaining___boxed(lean_object* v_out_501_, lean_object* v_index_502_, lean_object* v_acc_503_, lean_object* v_remaining_504_){
_start:
{
uint32_t v_acc_boxed_505_; uint32_t v_res_506_; lean_object* v_r_507_; 
v_acc_boxed_505_ = lean_unbox_uint32(v_acc_503_);
lean_dec(v_acc_503_);
v_res_506_ = lp_competition_R24DotBankHarness_sumRemaining(v_out_501_, v_index_502_, v_acc_boxed_505_, v_remaining_504_);
lean_dec_ref(v_out_501_);
v_r_507_ = lean_box_uint32(v_res_506_);
return v_r_507_;
}
}
LEAN_EXPORT uint32_t lp_competition_R24DotBankHarness_hashAll(lean_object* v_out_508_){
_start:
{
lean_object* v___x_509_; uint32_t v___x_510_; lean_object* v___x_511_; uint32_t v___x_512_; 
v___x_509_ = lean_unsigned_to_nat(0u);
v___x_510_ = 0;
v___x_511_ = lean_array_get_size(v_out_508_);
v___x_512_ = lp_competition_R24DotBankHarness_sumRemaining(v_out_508_, v___x_509_, v___x_510_, v___x_511_);
return v___x_512_;
}
}
LEAN_EXPORT lean_object* lp_competition_R24DotBankHarness_hashAll___boxed(lean_object* v_out_513_){
_start:
{
uint32_t v_res_514_; lean_object* v_r_515_; 
v_res_514_ = lp_competition_R24DotBankHarness_hashAll(v_out_513_);
lean_dec_ref(v_out_513_);
v_r_515_ = lean_box_uint32(v_res_514_);
return v_r_515_;
}
}
LEAN_EXPORT uint32_t lp_competition_R24DotBankHarness_seed(lean_object* v_trial_516_){
_start:
{
lean_object* v___x_517_; lean_object* v___x_518_; lean_object* v___x_519_; lean_object* v___x_520_; uint32_t v___x_521_; 
v___x_517_ = lean_unsigned_to_nat(2654435769u);
v___x_518_ = lean_unsigned_to_nat(1664525u);
v___x_519_ = lean_nat_mul(v___x_518_, v_trial_516_);
v___x_520_ = lean_nat_add(v___x_517_, v___x_519_);
lean_dec(v___x_519_);
v___x_521_ = lean_uint32_of_nat(v___x_520_);
lean_dec(v___x_520_);
return v___x_521_;
}
}
LEAN_EXPORT lean_object* lp_competition_R24DotBankHarness_seed___boxed(lean_object* v_trial_522_){
_start:
{
uint32_t v_res_523_; lean_object* v_r_524_; 
v_res_523_ = lp_competition_R24DotBankHarness_seed(v_trial_522_);
lean_dec(v_trial_522_);
v_r_524_ = lean_box_uint32(v_res_523_);
return v_r_524_;
}
}
LEAN_EXPORT lean_object* lp_competition_R24DotBankHarness_repeats(lean_object* v_macs_525_, lean_object* v_work_526_){
_start:
{
lean_object* v___x_527_; lean_object* v___y_529_; uint8_t v___x_534_; 
v___x_527_ = lean_unsigned_to_nat(1u);
v___x_534_ = lean_nat_dec_le(v___x_527_, v_work_526_);
if (v___x_534_ == 0)
{
v___y_529_ = v___x_527_;
goto v___jp_528_;
}
else
{
v___y_529_ = v_work_526_;
goto v___jp_528_;
}
v___jp_528_:
{
lean_object* v___x_530_; lean_object* v___x_531_; lean_object* v___x_532_; uint8_t v___x_533_; 
v___x_530_ = lean_nat_add(v_macs_525_, v___y_529_);
v___x_531_ = lean_nat_sub(v___x_530_, v___x_527_);
lean_dec(v___x_530_);
v___x_532_ = lean_nat_div(v___x_531_, v___y_529_);
lean_dec(v___x_531_);
v___x_533_ = lean_nat_dec_le(v___x_527_, v___x_532_);
if (v___x_533_ == 0)
{
lean_dec(v___x_532_);
return v___x_527_;
}
else
{
return v___x_532_;
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_R24DotBankHarness_repeats___boxed(lean_object* v_macs_535_, lean_object* v_work_536_){
_start:
{
lean_object* v_res_537_; 
v_res_537_ = lp_competition_R24DotBankHarness_repeats(v_macs_535_, v_work_536_);
lean_dec(v_work_536_);
lean_dec(v_macs_535_);
return v_res_537_;
}
}
LEAN_EXPORT lean_object* lp_competition_R24DotBankHarness_checkWord(lean_object* v_name_540_, lean_object* v_stage_541_, uint32_t v_got_542_, uint32_t v_expected_543_){
_start:
{
uint8_t v___x_545_; 
v___x_545_ = lean_uint32_dec_eq(v_got_542_, v_expected_543_);
if (v___x_545_ == 0)
{
lean_object* v___x_546_; lean_object* v___x_547_; lean_object* v___x_548_; lean_object* v___x_549_; lean_object* v___x_550_; lean_object* v___x_551_; lean_object* v___x_552_; lean_object* v___x_553_; lean_object* v___x_554_; lean_object* v___x_555_; lean_object* v___x_556_; lean_object* v___x_557_; lean_object* v___x_558_; lean_object* v___x_559_; lean_object* v___x_560_; 
v___x_546_ = ((lean_object*)(lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__10));
v___x_547_ = lean_string_append(v_name_540_, v___x_546_);
v___x_548_ = lean_string_append(v___x_547_, v_stage_541_);
v___x_549_ = ((lean_object*)(lp_competition_R24DotBankHarness_checkWord___closed__0));
v___x_550_ = lean_string_append(v___x_548_, v___x_549_);
v___x_551_ = lean_uint32_to_nat(v_got_542_);
v___x_552_ = l_Nat_reprFast(v___x_551_);
v___x_553_ = lean_string_append(v___x_550_, v___x_552_);
lean_dec_ref(v___x_552_);
v___x_554_ = ((lean_object*)(lp_competition_R24DotBankHarness_checkWord___closed__1));
v___x_555_ = lean_string_append(v___x_553_, v___x_554_);
v___x_556_ = lean_uint32_to_nat(v_expected_543_);
v___x_557_ = l_Nat_reprFast(v___x_556_);
v___x_558_ = lean_string_append(v___x_555_, v___x_557_);
lean_dec_ref(v___x_557_);
v___x_559_ = lean_alloc_ctor(18, 1, 0);
lean_ctor_set(v___x_559_, 0, v___x_558_);
v___x_560_ = lean_alloc_ctor(1, 1, 0);
lean_ctor_set(v___x_560_, 0, v___x_559_);
return v___x_560_;
}
else
{
lean_object* v___x_561_; lean_object* v___x_562_; 
lean_dec_ref(v_name_540_);
v___x_561_ = lean_box(0);
v___x_562_ = lean_alloc_ctor(0, 1, 0);
lean_ctor_set(v___x_562_, 0, v___x_561_);
return v___x_562_;
}
}
}
LEAN_EXPORT lean_object* lp_competition_R24DotBankHarness_checkWord___boxed(lean_object* v_name_563_, lean_object* v_stage_564_, lean_object* v_got_565_, lean_object* v_expected_566_, lean_object* v_a_567_){
_start:
{
uint32_t v_got_boxed_568_; uint32_t v_expected_boxed_569_; lean_object* v_res_570_; 
v_got_boxed_568_ = lean_unbox_uint32(v_got_565_);
lean_dec(v_got_565_);
v_expected_boxed_569_ = lean_unbox_uint32(v_expected_566_);
lean_dec(v_expected_566_);
v_res_570_ = lp_competition_R24DotBankHarness_checkWord(v_name_563_, v_stage_564_, v_got_boxed_568_, v_expected_boxed_569_);
lean_dec_ref(v_stage_564_);
return v_res_570_;
}
}
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotBankHarness_checkArray_spec__0___redArg(lean_object* v_got_573_, lean_object* v_expected_574_, lean_object* v_name_575_, lean_object* v_stage_576_, lean_object* v_range_577_, lean_object* v_b_578_, lean_object* v_i_579_){
_start:
{
lean_object* v_stop_581_; lean_object* v_step_582_; uint8_t v___x_583_; 
v_stop_581_ = lean_ctor_get(v_range_577_, 1);
v_step_582_ = lean_ctor_get(v_range_577_, 2);
v___x_583_ = lean_nat_dec_lt(v_i_579_, v_stop_581_);
if (v___x_583_ == 0)
{
lean_object* v___x_584_; 
lean_dec(v_i_579_);
lean_dec_ref(v_name_575_);
v___x_584_ = lean_alloc_ctor(0, 1, 0);
lean_ctor_set(v___x_584_, 0, v_b_578_);
return v___x_584_;
}
else
{
lean_object* v___x_585_; lean_object* v___x_586_; lean_object* v___x_587_; lean_object* v___x_588_; uint32_t v___x_589_; uint32_t v___x_590_; uint8_t v___x_591_; 
v___x_585_ = lp_competition_R24DotBankHarness_sumRemaining___boxed__const__1;
v___x_586_ = lean_array_get_borrowed(v___x_585_, v_got_573_, v_i_579_);
v___x_587_ = lp_competition_R24DotBankHarness_sumRemaining___boxed__const__1;
v___x_588_ = lean_array_get_borrowed(v___x_587_, v_expected_574_, v_i_579_);
v___x_589_ = lean_unbox_uint32(v___x_586_);
v___x_590_ = lean_unbox_uint32(v___x_588_);
v___x_591_ = lean_uint32_dec_eq(v___x_589_, v___x_590_);
if (v___x_591_ == 0)
{
lean_object* v___x_592_; lean_object* v___x_593_; lean_object* v___x_594_; lean_object* v___x_595_; lean_object* v___x_596_; lean_object* v___x_597_; lean_object* v___x_598_; lean_object* v___x_599_; lean_object* v___x_600_; lean_object* v___x_601_; lean_object* v___x_602_; 
v___x_592_ = ((lean_object*)(lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__10));
v___x_593_ = lean_string_append(v_name_575_, v___x_592_);
v___x_594_ = lean_string_append(v___x_593_, v_stage_576_);
v___x_595_ = ((lean_object*)(lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotBankHarness_checkArray_spec__0___redArg___closed__0));
v___x_596_ = lean_string_append(v___x_594_, v___x_595_);
v___x_597_ = l_Nat_reprFast(v_i_579_);
v___x_598_ = lean_string_append(v___x_596_, v___x_597_);
lean_dec_ref(v___x_597_);
v___x_599_ = ((lean_object*)(lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotBankHarness_checkArray_spec__0___redArg___closed__1));
v___x_600_ = lean_string_append(v___x_598_, v___x_599_);
v___x_601_ = lean_alloc_ctor(18, 1, 0);
lean_ctor_set(v___x_601_, 0, v___x_600_);
v___x_602_ = lean_alloc_ctor(1, 1, 0);
lean_ctor_set(v___x_602_, 0, v___x_601_);
return v___x_602_;
}
else
{
lean_object* v___x_603_; lean_object* v___x_604_; 
v___x_603_ = lean_box(0);
v___x_604_ = lean_nat_add(v_i_579_, v_step_582_);
lean_dec(v_i_579_);
v_b_578_ = v___x_603_;
v_i_579_ = v___x_604_;
goto _start;
}
}
}
}
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotBankHarness_checkArray_spec__0___redArg___boxed(lean_object* v_got_606_, lean_object* v_expected_607_, lean_object* v_name_608_, lean_object* v_stage_609_, lean_object* v_range_610_, lean_object* v_b_611_, lean_object* v_i_612_, lean_object* v___y_613_){
_start:
{
lean_object* v_res_614_; 
v_res_614_ = lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotBankHarness_checkArray_spec__0___redArg(v_got_606_, v_expected_607_, v_name_608_, v_stage_609_, v_range_610_, v_b_611_, v_i_612_);
lean_dec_ref(v_range_610_);
lean_dec_ref(v_stage_609_);
lean_dec_ref(v_expected_607_);
lean_dec_ref(v_got_606_);
return v_res_614_;
}
}
LEAN_EXPORT lean_object* lp_competition_R24DotBankHarness_checkArray(lean_object* v_name_616_, lean_object* v_stage_617_, lean_object* v_got_618_, lean_object* v_expected_619_){
_start:
{
lean_object* v___x_621_; lean_object* v___x_622_; uint8_t v___x_623_; 
v___x_621_ = lean_array_get_size(v_got_618_);
v___x_622_ = lean_array_get_size(v_expected_619_);
v___x_623_ = lean_nat_dec_eq(v___x_621_, v___x_622_);
if (v___x_623_ == 0)
{
lean_object* v___x_624_; lean_object* v___x_625_; lean_object* v___x_626_; lean_object* v___x_627_; lean_object* v___x_628_; lean_object* v___x_629_; lean_object* v___x_630_; 
v___x_624_ = ((lean_object*)(lp_competition_R24DotBankHarness_instFromJsonBankCase_fromJson___closed__10));
v___x_625_ = lean_string_append(v_name_616_, v___x_624_);
v___x_626_ = lean_string_append(v___x_625_, v_stage_617_);
v___x_627_ = ((lean_object*)(lp_competition_R24DotBankHarness_checkArray___closed__0));
v___x_628_ = lean_string_append(v___x_626_, v___x_627_);
v___x_629_ = lean_alloc_ctor(18, 1, 0);
lean_ctor_set(v___x_629_, 0, v___x_628_);
v___x_630_ = lean_alloc_ctor(1, 1, 0);
lean_ctor_set(v___x_630_, 0, v___x_629_);
return v___x_630_;
}
else
{
lean_object* v___x_631_; lean_object* v___x_632_; lean_object* v___x_633_; lean_object* v___x_634_; lean_object* v___x_635_; 
v___x_631_ = lean_unsigned_to_nat(0u);
v___x_632_ = lean_unsigned_to_nat(1u);
v___x_633_ = lean_alloc_ctor(0, 3, 0);
lean_ctor_set(v___x_633_, 0, v___x_631_);
lean_ctor_set(v___x_633_, 1, v___x_622_);
lean_ctor_set(v___x_633_, 2, v___x_632_);
v___x_634_ = lean_box(0);
v___x_635_ = lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotBankHarness_checkArray_spec__0___redArg(v_got_618_, v_expected_619_, v_name_616_, v_stage_617_, v___x_633_, v___x_634_, v___x_631_);
lean_dec_ref_known(v___x_633_, 3);
if (lean_obj_tag(v___x_635_) == 0)
{
lean_object* v___x_637_; uint8_t v_isShared_638_; uint8_t v_isSharedCheck_642_; 
v_isSharedCheck_642_ = !lean_is_exclusive(v___x_635_);
if (v_isSharedCheck_642_ == 0)
{
lean_object* v_unused_643_; 
v_unused_643_ = lean_ctor_get(v___x_635_, 0);
lean_dec(v_unused_643_);
v___x_637_ = v___x_635_;
v_isShared_638_ = v_isSharedCheck_642_;
goto v_resetjp_636_;
}
else
{
lean_dec(v___x_635_);
v___x_637_ = lean_box(0);
v_isShared_638_ = v_isSharedCheck_642_;
goto v_resetjp_636_;
}
v_resetjp_636_:
{
lean_object* v___x_640_; 
if (v_isShared_638_ == 0)
{
lean_ctor_set(v___x_637_, 0, v___x_634_);
v___x_640_ = v___x_637_;
goto v_reusejp_639_;
}
else
{
lean_object* v_reuseFailAlloc_641_; 
v_reuseFailAlloc_641_ = lean_alloc_ctor(0, 1, 0);
lean_ctor_set(v_reuseFailAlloc_641_, 0, v___x_634_);
v___x_640_ = v_reuseFailAlloc_641_;
goto v_reusejp_639_;
}
v_reusejp_639_:
{
return v___x_640_;
}
}
}
else
{
return v___x_635_;
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_R24DotBankHarness_checkArray___boxed(lean_object* v_name_644_, lean_object* v_stage_645_, lean_object* v_got_646_, lean_object* v_expected_647_, lean_object* v_a_648_){
_start:
{
lean_object* v_res_649_; 
v_res_649_ = lp_competition_R24DotBankHarness_checkArray(v_name_644_, v_stage_645_, v_got_646_, v_expected_647_);
lean_dec_ref(v_expected_647_);
lean_dec_ref(v_got_646_);
lean_dec_ref(v_stage_645_);
return v_res_649_;
}
}
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotBankHarness_checkArray_spec__0(lean_object* v_got_650_, lean_object* v_expected_651_, lean_object* v_name_652_, lean_object* v_stage_653_, lean_object* v_range_654_, lean_object* v_b_655_, lean_object* v_i_656_, lean_object* v_hs_657_, lean_object* v_hl_658_){
_start:
{
lean_object* v___x_660_; 
v___x_660_ = lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotBankHarness_checkArray_spec__0___redArg(v_got_650_, v_expected_651_, v_name_652_, v_stage_653_, v_range_654_, v_b_655_, v_i_656_);
return v___x_660_;
}
}
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotBankHarness_checkArray_spec__0___boxed(lean_object* v_got_661_, lean_object* v_expected_662_, lean_object* v_name_663_, lean_object* v_stage_664_, lean_object* v_range_665_, lean_object* v_b_666_, lean_object* v_i_667_, lean_object* v_hs_668_, lean_object* v_hl_669_, lean_object* v___y_670_){
_start:
{
lean_object* v_res_671_; 
v_res_671_ = lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotBankHarness_checkArray_spec__0(v_got_661_, v_expected_662_, v_name_663_, v_stage_664_, v_range_665_, v_b_666_, v_i_667_, v_hs_668_, v_hl_669_);
lean_dec_ref(v_range_665_);
lean_dec_ref(v_stage_664_);
lean_dec_ref(v_expected_662_);
lean_dec_ref(v_got_661_);
return v_res_671_;
}
}
LEAN_EXPORT uint8_t lp_competition___private_Init_Data_Array_Basic_0__Array_anyMUnsafe_any___at___00R24DotBankHarness_checkCase_spec__0(lean_object* v_as_672_, size_t v_i_673_, size_t v_stop_674_){
_start:
{
uint8_t v___x_675_; 
v___x_675_ = lean_usize_dec_eq(v_i_673_, v_stop_674_);
if (v___x_675_ == 0)
{
lean_object* v___x_676_; lean_object* v___x_677_; uint8_t v___x_678_; 
v___x_676_ = lean_array_uget_borrowed(v_as_672_, v_i_673_);
v___x_677_ = lean_unsigned_to_nat(4294967295u);
v___x_678_ = lean_nat_dec_lt(v___x_677_, v___x_676_);
if (v___x_678_ == 0)
{
size_t v___x_679_; size_t v___x_680_; 
v___x_679_ = ((size_t)1ULL);
v___x_680_ = lean_usize_add(v_i_673_, v___x_679_);
v_i_673_ = v___x_680_;
goto _start;
}
else
{
return v___x_678_;
}
}
else
{
uint8_t v___x_682_; 
v___x_682_ = 0;
return v___x_682_;
}
}
}
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_anyMUnsafe_any___at___00R24DotBankHarness_checkCase_spec__0___boxed(lean_object* v_as_683_, lean_object* v_i_684_, lean_object* v_stop_685_){
_start:
{
size_t v_i_boxed_686_; size_t v_stop_boxed_687_; uint8_t v_res_688_; lean_object* v_r_689_; 
v_i_boxed_686_ = lean_unbox_usize(v_i_684_);
lean_dec(v_i_684_);
v_stop_boxed_687_ = lean_unbox_usize(v_stop_685_);
lean_dec(v_stop_685_);
v_res_688_ = lp_competition___private_Init_Data_Array_Basic_0__Array_anyMUnsafe_any___at___00R24DotBankHarness_checkCase_spec__0(v_as_683_, v_i_boxed_686_, v_stop_boxed_687_);
lean_dec_ref(v_as_683_);
v_r_689_ = lean_box(v_res_688_);
return v_r_689_;
}
}
LEAN_EXPORT uint8_t lp_competition___private_Init_Data_Array_Basic_0__Array_anyMUnsafe_any___at___00R24DotBankHarness_checkCase_spec__1(lean_object* v_c_690_, lean_object* v___x_691_, lean_object* v___x_692_, uint8_t v___y_693_, lean_object* v_as_694_, size_t v_i_695_, size_t v_stop_696_){
_start:
{
uint8_t v___x_697_; 
v___x_697_ = lean_usize_dec_eq(v_i_695_, v_stop_696_);
if (v___x_697_ == 0)
{
lean_object* v_inner_698_; uint8_t v___x_699_; uint8_t v___y_701_; lean_object* v___x_705_; lean_object* v___x_706_; uint8_t v___x_707_; 
v_inner_698_ = lean_ctor_get(v_c_690_, 2);
v___x_699_ = 1;
v___x_705_ = lean_array_uget_borrowed(v_as_694_, v_i_695_);
v___x_706_ = lean_array_get_size(v___x_705_);
v___x_707_ = lean_nat_dec_eq(v___x_706_, v_inner_698_);
if (v___x_707_ == 0)
{
uint8_t v___x_708_; 
v___x_708_ = lean_nat_dec_eq(v___x_691_, v___x_692_);
v___y_701_ = v___x_708_;
goto v___jp_700_;
}
else
{
lean_object* v___x_709_; uint8_t v___x_710_; 
v___x_709_ = lean_unsigned_to_nat(0u);
v___x_710_ = lean_nat_dec_lt(v___x_709_, v___x_706_);
if (v___x_710_ == 0)
{
v___y_701_ = v___y_693_;
goto v___jp_700_;
}
else
{
if (v___x_710_ == 0)
{
v___y_701_ = v___y_693_;
goto v___jp_700_;
}
else
{
size_t v___x_711_; size_t v___x_712_; uint8_t v___x_713_; 
v___x_711_ = ((size_t)0ULL);
v___x_712_ = lean_usize_of_nat(v___x_706_);
v___x_713_ = lp_competition___private_Init_Data_Array_Basic_0__Array_anyMUnsafe_any___at___00R24DotBankHarness_checkCase_spec__0(v___x_705_, v___x_711_, v___x_712_);
v___y_701_ = v___x_713_;
goto v___jp_700_;
}
}
}
v___jp_700_:
{
if (v___y_701_ == 0)
{
size_t v___x_702_; size_t v___x_703_; 
v___x_702_ = ((size_t)1ULL);
v___x_703_ = lean_usize_add(v_i_695_, v___x_702_);
v_i_695_ = v___x_703_;
goto _start;
}
else
{
return v___x_699_;
}
}
}
else
{
uint8_t v___x_714_; 
v___x_714_ = 0;
return v___x_714_;
}
}
}
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_anyMUnsafe_any___at___00R24DotBankHarness_checkCase_spec__1___boxed(lean_object* v_c_715_, lean_object* v___x_716_, lean_object* v___x_717_, lean_object* v___y_718_, lean_object* v_as_719_, lean_object* v_i_720_, lean_object* v_stop_721_){
_start:
{
uint8_t v___y_3246__boxed_722_; size_t v_i_boxed_723_; size_t v_stop_boxed_724_; uint8_t v_res_725_; lean_object* v_r_726_; 
v___y_3246__boxed_722_ = lean_unbox(v___y_718_);
v_i_boxed_723_ = lean_unbox_usize(v_i_720_);
lean_dec(v_i_720_);
v_stop_boxed_724_ = lean_unbox_usize(v_stop_721_);
lean_dec(v_stop_721_);
v_res_725_ = lp_competition___private_Init_Data_Array_Basic_0__Array_anyMUnsafe_any___at___00R24DotBankHarness_checkCase_spec__1(v_c_715_, v___x_716_, v___x_717_, v___y_3246__boxed_722_, v_as_719_, v_i_boxed_723_, v_stop_boxed_724_);
lean_dec_ref(v_as_719_);
lean_dec(v___x_717_);
lean_dec(v___x_716_);
lean_dec_ref(v_c_715_);
v_r_726_ = lean_box(v_res_725_);
return v_r_726_;
}
}
LEAN_EXPORT uint8_t lp_competition___private_Init_Data_Array_Basic_0__Array_anyMUnsafe_any___at___00R24DotBankHarness_checkCase_spec__2(lean_object* v_c_727_, lean_object* v___x_728_, lean_object* v___x_729_, lean_object* v___x_730_, lean_object* v_as_731_, size_t v_i_732_, size_t v_stop_733_){
_start:
{
uint8_t v___x_734_; 
v___x_734_ = lean_usize_dec_eq(v_i_732_, v_stop_733_);
if (v___x_734_ == 0)
{
lean_object* v_inner_735_; uint8_t v___x_736_; uint8_t v___y_738_; lean_object* v___x_742_; lean_object* v___x_743_; uint8_t v___x_744_; 
v_inner_735_ = lean_ctor_get(v_c_727_, 2);
v___x_736_ = 1;
v___x_742_ = lean_array_uget_borrowed(v_as_731_, v_i_732_);
v___x_743_ = lean_array_get_size(v___x_742_);
v___x_744_ = lean_nat_dec_eq(v___x_743_, v_inner_735_);
if (v___x_744_ == 0)
{
uint8_t v___x_745_; 
v___x_745_ = lean_nat_dec_eq(v___x_728_, v___x_729_);
v___y_738_ = v___x_745_;
goto v___jp_737_;
}
else
{
lean_object* v___x_746_; uint8_t v___x_747_; uint8_t v___x_748_; 
v___x_746_ = lean_unsigned_to_nat(0u);
v___x_747_ = lean_nat_dec_eq(v___x_730_, v___x_746_);
v___x_748_ = lean_nat_dec_lt(v___x_746_, v___x_743_);
if (v___x_748_ == 0)
{
v___y_738_ = v___x_747_;
goto v___jp_737_;
}
else
{
if (v___x_748_ == 0)
{
v___y_738_ = v___x_747_;
goto v___jp_737_;
}
else
{
size_t v___x_749_; size_t v___x_750_; uint8_t v___x_751_; 
v___x_749_ = ((size_t)0ULL);
v___x_750_ = lean_usize_of_nat(v___x_743_);
v___x_751_ = lp_competition___private_Init_Data_Array_Basic_0__Array_anyMUnsafe_any___at___00R24DotBankHarness_checkCase_spec__0(v___x_742_, v___x_749_, v___x_750_);
v___y_738_ = v___x_751_;
goto v___jp_737_;
}
}
}
v___jp_737_:
{
if (v___y_738_ == 0)
{
size_t v___x_739_; size_t v___x_740_; 
v___x_739_ = ((size_t)1ULL);
v___x_740_ = lean_usize_add(v_i_732_, v___x_739_);
v_i_732_ = v___x_740_;
goto _start;
}
else
{
return v___x_736_;
}
}
}
else
{
uint8_t v___x_752_; 
v___x_752_ = 0;
return v___x_752_;
}
}
}
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_anyMUnsafe_any___at___00R24DotBankHarness_checkCase_spec__2___boxed(lean_object* v_c_753_, lean_object* v___x_754_, lean_object* v___x_755_, lean_object* v___x_756_, lean_object* v_as_757_, lean_object* v_i_758_, lean_object* v_stop_759_){
_start:
{
size_t v_i_boxed_760_; size_t v_stop_boxed_761_; uint8_t v_res_762_; lean_object* v_r_763_; 
v_i_boxed_760_ = lean_unbox_usize(v_i_758_);
lean_dec(v_i_758_);
v_stop_boxed_761_ = lean_unbox_usize(v_stop_759_);
lean_dec(v_stop_759_);
v_res_762_ = lp_competition___private_Init_Data_Array_Basic_0__Array_anyMUnsafe_any___at___00R24DotBankHarness_checkCase_spec__2(v_c_753_, v___x_754_, v___x_755_, v___x_756_, v_as_757_, v_i_boxed_760_, v_stop_boxed_761_);
lean_dec_ref(v_as_757_);
lean_dec(v___x_756_);
lean_dec(v___x_755_);
lean_dec(v___x_754_);
lean_dec_ref(v_c_753_);
v_r_763_ = lean_box(v_res_762_);
return v_r_763_;
}
}
LEAN_EXPORT lean_object* lp_competition_R24DotBankHarness_checkCase(lean_object* v_c_767_){
_start:
{
lean_object* v_name_772_; lean_object* v_inner_773_; lean_object* v_rows_774_; lean_object* v_cols_775_; lean_object* v_rowsA_776_; lean_object* v_rowsB_777_; lean_object* v_expected_778_; lean_object* v___x_801_; uint8_t v___x_802_; 
v_name_772_ = lean_ctor_get(v_c_767_, 0);
lean_inc_ref(v_name_772_);
v_inner_773_ = lean_ctor_get(v_c_767_, 2);
v_rows_774_ = lean_ctor_get(v_c_767_, 3);
v_cols_775_ = lean_ctor_get(v_c_767_, 4);
v_rowsA_776_ = lean_ctor_get(v_c_767_, 5);
v_rowsB_777_ = lean_ctor_get(v_c_767_, 6);
lean_inc_ref(v_rowsB_777_);
v_expected_778_ = lean_ctor_get(v_c_767_, 7);
lean_inc_ref(v_expected_778_);
v___x_801_ = lean_array_get_size(v_rowsA_776_);
v___x_802_ = lean_nat_dec_eq(v___x_801_, v_rows_774_);
if (v___x_802_ == 0)
{
lean_dec_ref(v_expected_778_);
lean_dec_ref(v_rowsB_777_);
lean_dec_ref(v_c_767_);
goto v___jp_779_;
}
else
{
lean_object* v___x_803_; uint8_t v___x_804_; 
v___x_803_ = lean_array_get_size(v_rowsB_777_);
v___x_804_ = lean_nat_dec_eq(v___x_803_, v_cols_775_);
if (v___x_804_ == 0)
{
lean_dec_ref(v_expected_778_);
lean_dec_ref(v_rowsB_777_);
lean_dec_ref(v_c_767_);
goto v___jp_779_;
}
else
{
lean_object* v___x_805_; lean_object* v___x_806_; uint8_t v___y_808_; uint8_t v___y_815_; uint8_t v___x_822_; 
v___x_805_ = lean_array_get_size(v_expected_778_);
v___x_806_ = lean_nat_mul(v_rows_774_, v_cols_775_);
v___x_822_ = lean_nat_dec_eq(v___x_805_, v___x_806_);
if (v___x_822_ == 0)
{
lean_dec(v___x_806_);
lean_dec_ref(v_expected_778_);
lean_dec_ref(v_rowsB_777_);
lean_dec_ref(v_c_767_);
goto v___jp_779_;
}
else
{
lean_object* v___x_823_; uint8_t v___x_824_; 
v___x_823_ = lean_unsigned_to_nat(0u);
v___x_824_ = lean_nat_dec_eq(v_inner_773_, v___x_823_);
if (v___x_824_ == 0)
{
uint8_t v___x_825_; 
v___x_825_ = lean_nat_dec_eq(v_rows_774_, v___x_823_);
v___y_815_ = v___x_825_;
goto v___jp_814_;
}
else
{
v___y_815_ = v___x_824_;
goto v___jp_814_;
}
}
v___jp_807_:
{
if (v___y_808_ == 0)
{
lean_object* v___x_809_; uint8_t v___x_810_; 
v___x_809_ = lean_unsigned_to_nat(0u);
v___x_810_ = lean_nat_dec_lt(v___x_809_, v___x_803_);
if (v___x_810_ == 0)
{
lean_dec(v___x_806_);
lean_dec_ref(v_rowsB_777_);
lean_dec_ref(v_c_767_);
goto v___jp_794_;
}
else
{
if (v___x_810_ == 0)
{
lean_dec(v___x_806_);
lean_dec_ref(v_rowsB_777_);
lean_dec_ref(v_c_767_);
goto v___jp_794_;
}
else
{
size_t v___x_811_; size_t v___x_812_; uint8_t v___x_813_; 
v___x_811_ = ((size_t)0ULL);
v___x_812_ = lean_usize_of_nat(v___x_803_);
v___x_813_ = lp_competition___private_Init_Data_Array_Basic_0__Array_anyMUnsafe_any___at___00R24DotBankHarness_checkCase_spec__1(v_c_767_, v___x_805_, v___x_806_, v___y_808_, v_rowsB_777_, v___x_811_, v___x_812_);
lean_dec_ref(v_rowsB_777_);
lean_dec(v___x_806_);
lean_dec_ref(v_c_767_);
if (v___x_813_ == 0)
{
goto v___jp_794_;
}
else
{
lean_dec_ref(v_expected_778_);
goto v___jp_789_;
}
}
}
}
else
{
lean_dec(v___x_806_);
lean_dec_ref(v_expected_778_);
lean_dec_ref(v_rowsB_777_);
lean_dec_ref(v_c_767_);
goto v___jp_789_;
}
}
v___jp_814_:
{
if (v___y_815_ == 0)
{
lean_object* v___x_816_; uint8_t v___x_817_; 
v___x_816_ = lean_unsigned_to_nat(0u);
v___x_817_ = lean_nat_dec_eq(v_cols_775_, v___x_816_);
if (v___x_817_ == 0)
{
uint8_t v___x_818_; 
v___x_818_ = lean_nat_dec_lt(v___x_816_, v___x_801_);
if (v___x_818_ == 0)
{
v___y_808_ = v___x_817_;
goto v___jp_807_;
}
else
{
if (v___x_818_ == 0)
{
v___y_808_ = v___x_817_;
goto v___jp_807_;
}
else
{
size_t v___x_819_; size_t v___x_820_; uint8_t v___x_821_; 
v___x_819_ = ((size_t)0ULL);
v___x_820_ = lean_usize_of_nat(v___x_801_);
v___x_821_ = lp_competition___private_Init_Data_Array_Basic_0__Array_anyMUnsafe_any___at___00R24DotBankHarness_checkCase_spec__2(v_c_767_, v___x_805_, v___x_806_, v_cols_775_, v_rowsA_776_, v___x_819_, v___x_820_);
v___y_808_ = v___x_821_;
goto v___jp_807_;
}
}
}
else
{
lean_dec(v___x_806_);
lean_dec_ref(v_expected_778_);
lean_dec_ref(v_rowsB_777_);
lean_dec_ref(v_c_767_);
goto v___jp_784_;
}
}
else
{
lean_dec(v___x_806_);
lean_dec_ref(v_expected_778_);
lean_dec_ref(v_rowsB_777_);
lean_dec_ref(v_c_767_);
goto v___jp_784_;
}
}
}
}
v___jp_769_:
{
lean_object* v___x_770_; lean_object* v___x_771_; 
v___x_770_ = lean_box(0);
v___x_771_ = lean_alloc_ctor(0, 1, 0);
lean_ctor_set(v___x_771_, 0, v___x_770_);
return v___x_771_;
}
v___jp_779_:
{
lean_object* v___x_780_; lean_object* v___x_781_; lean_object* v___x_782_; lean_object* v___x_783_; 
v___x_780_ = ((lean_object*)(lp_competition_R24DotBankHarness_checkCase___closed__0));
v___x_781_ = lean_string_append(v_name_772_, v___x_780_);
v___x_782_ = lean_alloc_ctor(18, 1, 0);
lean_ctor_set(v___x_782_, 0, v___x_781_);
v___x_783_ = lean_alloc_ctor(1, 1, 0);
lean_ctor_set(v___x_783_, 0, v___x_782_);
return v___x_783_;
}
v___jp_784_:
{
lean_object* v___x_785_; lean_object* v___x_786_; lean_object* v___x_787_; lean_object* v___x_788_; 
v___x_785_ = ((lean_object*)(lp_competition_R24DotBankHarness_checkCase___closed__1));
v___x_786_ = lean_string_append(v_name_772_, v___x_785_);
v___x_787_ = lean_alloc_ctor(18, 1, 0);
lean_ctor_set(v___x_787_, 0, v___x_786_);
v___x_788_ = lean_alloc_ctor(1, 1, 0);
lean_ctor_set(v___x_788_, 0, v___x_787_);
return v___x_788_;
}
v___jp_789_:
{
lean_object* v___x_790_; lean_object* v___x_791_; lean_object* v___x_792_; lean_object* v___x_793_; 
v___x_790_ = ((lean_object*)(lp_competition_R24DotBankHarness_checkCase___closed__2));
v___x_791_ = lean_string_append(v_name_772_, v___x_790_);
v___x_792_ = lean_alloc_ctor(18, 1, 0);
lean_ctor_set(v___x_792_, 0, v___x_791_);
v___x_793_ = lean_alloc_ctor(1, 1, 0);
lean_ctor_set(v___x_793_, 0, v___x_792_);
return v___x_793_;
}
v___jp_794_:
{
lean_object* v___x_795_; lean_object* v___x_796_; uint8_t v___x_797_; 
v___x_795_ = lean_unsigned_to_nat(0u);
v___x_796_ = lean_array_get_size(v_expected_778_);
v___x_797_ = lean_nat_dec_lt(v___x_795_, v___x_796_);
if (v___x_797_ == 0)
{
lean_dec_ref(v_expected_778_);
lean_dec_ref(v_name_772_);
goto v___jp_769_;
}
else
{
if (v___x_797_ == 0)
{
lean_dec_ref(v_expected_778_);
lean_dec_ref(v_name_772_);
goto v___jp_769_;
}
else
{
size_t v___x_798_; size_t v___x_799_; uint8_t v___x_800_; 
v___x_798_ = ((size_t)0ULL);
v___x_799_ = lean_usize_of_nat(v___x_796_);
v___x_800_ = lp_competition___private_Init_Data_Array_Basic_0__Array_anyMUnsafe_any___at___00R24DotBankHarness_checkCase_spec__0(v_expected_778_, v___x_798_, v___x_799_);
lean_dec_ref(v_expected_778_);
if (v___x_800_ == 0)
{
lean_dec_ref(v_name_772_);
goto v___jp_769_;
}
else
{
goto v___jp_789_;
}
}
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_R24DotBankHarness_checkCase___boxed(lean_object* v_c_826_, lean_object* v_a_827_){
_start:
{
lean_object* v_res_828_; 
v_res_828_ = lp_competition_R24DotBankHarness_checkCase(v_c_826_);
return v_res_828_;
}
}
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotBankHarness_emit_spec__0(lean_object* v_c_832_, lean_object* v_variant_833_, lean_object* v_as_834_, size_t v_sz_835_, size_t v_i_836_, uint32_t v_b_837_){
_start:
{
uint8_t v___x_839_; 
v___x_839_ = lean_usize_dec_lt(v_i_836_, v_sz_835_);
if (v___x_839_ == 0)
{
lean_object* v___x_840_; lean_object* v___x_841_; 
v___x_840_ = lean_box_uint32(v_b_837_);
v___x_841_ = lean_alloc_ctor(0, 1, 0);
lean_ctor_set(v___x_841_, 0, v___x_840_);
return v___x_841_;
}
else
{
lean_object* v_name_842_; lean_object* v_group_843_; lean_object* v_a_844_; lean_object* v_trial_845_; lean_object* v_work_846_; lean_object* v_iters_847_; lean_object* v_ns_848_; uint32_t v_sink_849_; uint32_t v_expectedSink_850_; uint32_t v_keepWord_851_; lean_object* v___x_852_; lean_object* v___x_853_; lean_object* v___x_854_; lean_object* v___x_855_; lean_object* v___x_856_; lean_object* v___x_857_; lean_object* v___x_858_; lean_object* v___x_859_; lean_object* v___x_860_; lean_object* v___x_861_; lean_object* v___x_862_; lean_object* v___x_863_; lean_object* v___x_864_; lean_object* v___x_865_; lean_object* v___x_866_; lean_object* v___x_867_; lean_object* v___x_868_; lean_object* v___x_869_; lean_object* v___x_870_; lean_object* v___x_871_; lean_object* v___x_872_; lean_object* v___x_873_; lean_object* v___x_874_; lean_object* v___x_875_; lean_object* v___x_876_; lean_object* v___x_877_; lean_object* v___x_878_; lean_object* v___x_879_; lean_object* v___x_880_; lean_object* v___x_881_; lean_object* v___x_882_; lean_object* v___x_883_; lean_object* v___x_884_; lean_object* v___x_885_; lean_object* v___x_886_; lean_object* v___x_887_; lean_object* v___x_888_; 
v_name_842_ = lean_ctor_get(v_c_832_, 0);
v_group_843_ = lean_ctor_get(v_c_832_, 1);
v_a_844_ = lean_array_uget_borrowed(v_as_834_, v_i_836_);
v_trial_845_ = lean_ctor_get(v_a_844_, 0);
v_work_846_ = lean_ctor_get(v_a_844_, 1);
v_iters_847_ = lean_ctor_get(v_a_844_, 2);
v_ns_848_ = lean_ctor_get(v_a_844_, 3);
v_sink_849_ = lean_ctor_get_uint32(v_a_844_, sizeof(void*)*4);
v_expectedSink_850_ = lean_ctor_get_uint32(v_a_844_, sizeof(void*)*4 + 4);
v_keepWord_851_ = lean_ctor_get_uint32(v_a_844_, sizeof(void*)*4 + 8);
v___x_852_ = ((lean_object*)(lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotBankHarness_emit_spec__0___closed__0));
v___x_853_ = lean_string_append(v___x_852_, v_name_842_);
v___x_854_ = ((lean_object*)(lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotBankHarness_emit_spec__0___closed__1));
v___x_855_ = lean_string_append(v___x_853_, v___x_854_);
v___x_856_ = lean_string_append(v___x_855_, v_group_843_);
v___x_857_ = lean_string_append(v___x_856_, v___x_854_);
v___x_858_ = lean_string_append(v___x_857_, v_variant_833_);
v___x_859_ = ((lean_object*)(lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotBankHarness_emit_spec__0___closed__2));
v___x_860_ = lean_string_append(v___x_858_, v___x_859_);
lean_inc(v_trial_845_);
v___x_861_ = l_Nat_reprFast(v_trial_845_);
v___x_862_ = lean_string_append(v___x_860_, v___x_861_);
lean_dec_ref(v___x_861_);
v___x_863_ = lean_string_append(v___x_862_, v___x_854_);
lean_inc(v_work_846_);
v___x_864_ = l_Nat_reprFast(v_work_846_);
v___x_865_ = lean_string_append(v___x_863_, v___x_864_);
lean_dec_ref(v___x_864_);
v___x_866_ = lean_string_append(v___x_865_, v___x_854_);
lean_inc(v_iters_847_);
v___x_867_ = l_Nat_reprFast(v_iters_847_);
v___x_868_ = lean_string_append(v___x_866_, v___x_867_);
lean_dec_ref(v___x_867_);
v___x_869_ = lean_string_append(v___x_868_, v___x_854_);
v___x_870_ = lean_nat_mul(v_work_846_, v_iters_847_);
v___x_871_ = l_Nat_reprFast(v___x_870_);
v___x_872_ = lean_string_append(v___x_869_, v___x_871_);
lean_dec_ref(v___x_871_);
v___x_873_ = lean_string_append(v___x_872_, v___x_854_);
lean_inc(v_ns_848_);
v___x_874_ = l_Nat_reprFast(v_ns_848_);
v___x_875_ = lean_string_append(v___x_873_, v___x_874_);
lean_dec_ref(v___x_874_);
v___x_876_ = lean_string_append(v___x_875_, v___x_854_);
v___x_877_ = lean_uint32_to_nat(v_sink_849_);
v___x_878_ = l_Nat_reprFast(v___x_877_);
v___x_879_ = lean_string_append(v___x_876_, v___x_878_);
lean_dec_ref(v___x_878_);
v___x_880_ = lean_string_append(v___x_879_, v___x_854_);
v___x_881_ = lean_uint32_to_nat(v_expectedSink_850_);
v___x_882_ = l_Nat_reprFast(v___x_881_);
v___x_883_ = lean_string_append(v___x_880_, v___x_882_);
lean_dec_ref(v___x_882_);
v___x_884_ = lean_string_append(v___x_883_, v___x_854_);
v___x_885_ = lean_uint32_to_nat(v_keepWord_851_);
v___x_886_ = l_Nat_reprFast(v___x_885_);
v___x_887_ = lean_string_append(v___x_884_, v___x_886_);
lean_dec_ref(v___x_886_);
v___x_888_ = lp_batteries_IO_println___at___00Batteries_Tactic_Lint_lintCore_spec__4(v___x_887_);
if (lean_obj_tag(v___x_888_) == 0)
{
size_t v___x_889_; size_t v___x_890_; 
lean_dec_ref_known(v___x_888_, 1);
v___x_889_ = ((size_t)1ULL);
v___x_890_ = lean_usize_add(v_i_836_, v___x_889_);
v_i_836_ = v___x_890_;
v_b_837_ = v_keepWord_851_;
goto _start;
}
else
{
lean_object* v_a_892_; lean_object* v___x_894_; uint8_t v_isShared_895_; uint8_t v_isSharedCheck_899_; 
v_a_892_ = lean_ctor_get(v___x_888_, 0);
v_isSharedCheck_899_ = !lean_is_exclusive(v___x_888_);
if (v_isSharedCheck_899_ == 0)
{
v___x_894_ = v___x_888_;
v_isShared_895_ = v_isSharedCheck_899_;
goto v_resetjp_893_;
}
else
{
lean_inc(v_a_892_);
lean_dec(v___x_888_);
v___x_894_ = lean_box(0);
v_isShared_895_ = v_isSharedCheck_899_;
goto v_resetjp_893_;
}
v_resetjp_893_:
{
lean_object* v___x_897_; 
if (v_isShared_895_ == 0)
{
v___x_897_ = v___x_894_;
goto v_reusejp_896_;
}
else
{
lean_object* v_reuseFailAlloc_898_; 
v_reuseFailAlloc_898_ = lean_alloc_ctor(1, 1, 0);
lean_ctor_set(v_reuseFailAlloc_898_, 0, v_a_892_);
v___x_897_ = v_reuseFailAlloc_898_;
goto v_reusejp_896_;
}
v_reusejp_896_:
{
return v___x_897_;
}
}
}
}
}
}
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotBankHarness_emit_spec__0___boxed(lean_object* v_c_900_, lean_object* v_variant_901_, lean_object* v_as_902_, lean_object* v_sz_903_, lean_object* v_i_904_, lean_object* v_b_905_, lean_object* v___y_906_){
_start:
{
size_t v_sz_boxed_907_; size_t v_i_boxed_908_; uint32_t v_b_boxed_909_; lean_object* v_res_910_; 
v_sz_boxed_907_ = lean_unbox_usize(v_sz_903_);
lean_dec(v_sz_903_);
v_i_boxed_908_ = lean_unbox_usize(v_i_904_);
lean_dec(v_i_904_);
v_b_boxed_909_ = lean_unbox_uint32(v_b_905_);
lean_dec(v_b_905_);
v_res_910_ = lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotBankHarness_emit_spec__0(v_c_900_, v_variant_901_, v_as_902_, v_sz_boxed_907_, v_i_boxed_908_, v_b_boxed_909_);
lean_dec_ref(v_as_902_);
lean_dec_ref(v_variant_901_);
lean_dec_ref(v_c_900_);
return v_res_910_;
}
}
LEAN_EXPORT lean_object* lp_competition_R24DotBankHarness_emit(lean_object* v_c_913_, lean_object* v_variant_914_, lean_object* v_life_915_, lean_object* v_rows_916_){
_start:
{
uint32_t v_last_918_; size_t v_sz_919_; size_t v___x_920_; lean_object* v___x_921_; 
v_last_918_ = 0;
v_sz_919_ = lean_array_size(v_rows_916_);
v___x_920_ = ((size_t)0ULL);
v___x_921_ = lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotBankHarness_emit_spec__0(v_c_913_, v_variant_914_, v_rows_916_, v_sz_919_, v___x_920_, v_last_918_);
if (lean_obj_tag(v___x_921_) == 0)
{
lean_object* v_a_922_; lean_object* v_name_923_; lean_object* v_group_924_; lean_object* v___x_925_; lean_object* v___x_926_; lean_object* v___x_927_; lean_object* v___x_928_; lean_object* v___x_929_; lean_object* v___x_930_; lean_object* v___x_931_; lean_object* v___x_932_; lean_object* v___x_933_; lean_object* v___x_934_; lean_object* v___x_935_; lean_object* v___x_936_; lean_object* v___x_937_; lean_object* v___x_938_; lean_object* v___x_939_; lean_object* v___x_940_; uint32_t v___x_941_; lean_object* v___x_942_; lean_object* v___x_943_; lean_object* v___x_944_; lean_object* v___x_945_; 
v_a_922_ = lean_ctor_get(v___x_921_, 0);
lean_inc(v_a_922_);
lean_dec_ref_known(v___x_921_, 1);
v_name_923_ = lean_ctor_get(v_c_913_, 0);
v_group_924_ = lean_ctor_get(v_c_913_, 1);
v___x_925_ = ((lean_object*)(lp_competition_R24DotBankHarness_emit___closed__0));
v___x_926_ = lean_string_append(v___x_925_, v_name_923_);
v___x_927_ = ((lean_object*)(lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotBankHarness_emit_spec__0___closed__1));
v___x_928_ = lean_string_append(v___x_926_, v___x_927_);
v___x_929_ = lean_string_append(v___x_928_, v_group_924_);
v___x_930_ = lean_string_append(v___x_929_, v___x_927_);
v___x_931_ = lean_string_append(v___x_930_, v_variant_914_);
v___x_932_ = ((lean_object*)(lp_competition_R24DotBankHarness_emit___closed__1));
v___x_933_ = lean_string_append(v___x_931_, v___x_932_);
v___x_934_ = l_Nat_reprFast(v_life_915_);
v___x_935_ = lean_string_append(v___x_933_, v___x_934_);
lean_dec_ref(v___x_934_);
v___x_936_ = lean_string_append(v___x_935_, v___x_927_);
v___x_937_ = lean_array_get_size(v_rows_916_);
v___x_938_ = l_Nat_reprFast(v___x_937_);
v___x_939_ = lean_string_append(v___x_936_, v___x_938_);
lean_dec_ref(v___x_938_);
v___x_940_ = lean_string_append(v___x_939_, v___x_927_);
v___x_941_ = lean_unbox_uint32(v_a_922_);
lean_dec(v_a_922_);
v___x_942_ = lean_uint32_to_nat(v___x_941_);
v___x_943_ = l_Nat_reprFast(v___x_942_);
v___x_944_ = lean_string_append(v___x_940_, v___x_943_);
lean_dec_ref(v___x_943_);
v___x_945_ = lp_batteries_IO_println___at___00Batteries_Tactic_Lint_lintCore_spec__4(v___x_944_);
return v___x_945_;
}
else
{
lean_object* v_a_946_; lean_object* v___x_948_; uint8_t v_isShared_949_; uint8_t v_isSharedCheck_953_; 
lean_dec(v_life_915_);
v_a_946_ = lean_ctor_get(v___x_921_, 0);
v_isSharedCheck_953_ = !lean_is_exclusive(v___x_921_);
if (v_isSharedCheck_953_ == 0)
{
v___x_948_ = v___x_921_;
v_isShared_949_ = v_isSharedCheck_953_;
goto v_resetjp_947_;
}
else
{
lean_inc(v_a_946_);
lean_dec(v___x_921_);
v___x_948_ = lean_box(0);
v_isShared_949_ = v_isSharedCheck_953_;
goto v_resetjp_947_;
}
v_resetjp_947_:
{
lean_object* v___x_951_; 
if (v_isShared_949_ == 0)
{
v___x_951_ = v___x_948_;
goto v_reusejp_950_;
}
else
{
lean_object* v_reuseFailAlloc_952_; 
v_reuseFailAlloc_952_ = lean_alloc_ctor(1, 1, 0);
lean_ctor_set(v_reuseFailAlloc_952_, 0, v_a_946_);
v___x_951_ = v_reuseFailAlloc_952_;
goto v_reusejp_950_;
}
v_reusejp_950_:
{
return v___x_951_;
}
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_R24DotBankHarness_emit___boxed(lean_object* v_c_954_, lean_object* v_variant_955_, lean_object* v_life_956_, lean_object* v_rows_957_, lean_object* v_a_958_){
_start:
{
lean_object* v_res_959_; 
v_res_959_ = lp_competition_R24DotBankHarness_emit(v_c_954_, v_variant_955_, v_life_956_, v_rows_957_);
lean_dec_ref(v_rows_957_);
lean_dec_ref(v_variant_955_);
lean_dec_ref(v_c_954_);
return v_res_959_;
}
}
LEAN_EXPORT uint32_t lp_competition_R24DotBankHarness_passExact(lean_object* v_p_960_, uint32_t v_s_961_, lean_object* v_iters_962_){
_start:
{
lean_object* v_zero_963_; uint8_t v_isZero_964_; 
v_zero_963_ = lean_unsigned_to_nat(0u);
v_isZero_964_ = lean_nat_dec_eq(v_iters_962_, v_zero_963_);
if (v_isZero_964_ == 1)
{
lean_dec(v_iters_962_);
lean_dec_ref(v_p_960_);
return v_s_961_;
}
else
{
lean_object* v_one_965_; lean_object* v_n_966_; lean_object* v_p_967_; lean_object* v_fst_968_; lean_object* v_snd_969_; lean_object* v_out_970_; uint32_t v_word_971_; uint32_t v___x_972_; 
v_one_965_ = lean_unsigned_to_nat(1u);
v_n_966_ = lean_nat_sub(v_iters_962_, v_one_965_);
lean_dec(v_iters_962_);
v_p_967_ = lp_competition_R24DotBarrier_touchBank(v_n_966_, v_p_960_);
v_fst_968_ = lean_ctor_get(v_p_967_, 0);
lean_inc(v_fst_968_);
v_snd_969_ = lean_ctor_get(v_p_967_, 1);
lean_inc(v_snd_969_);
v_out_970_ = lp_competition_Submission_R24GenericDotBank_exactBank(v_fst_968_, v_snd_969_);
lean_dec(v_snd_969_);
lean_dec(v_fst_968_);
v_word_971_ = lp_competition_R24DotBankHarness_hashAll(v_out_970_);
lean_dec_ref(v_out_970_);
v___x_972_ = lean_uint32_add(v_s_961_, v_word_971_);
v_p_960_ = v_p_967_;
v_s_961_ = v___x_972_;
v_iters_962_ = v_n_966_;
goto _start;
}
}
}
LEAN_EXPORT lean_object* lp_competition_R24DotBankHarness_passExact___boxed(lean_object* v_p_974_, lean_object* v_s_975_, lean_object* v_iters_976_){
_start:
{
uint32_t v_s_boxed_977_; uint32_t v_res_978_; lean_object* v_r_979_; 
v_s_boxed_977_ = lean_unbox_uint32(v_s_975_);
lean_dec(v_s_975_);
v_res_978_ = lp_competition_R24DotBankHarness_passExact(v_p_974_, v_s_boxed_977_, v_iters_976_);
v_r_979_ = lean_box_uint32(v_res_978_);
return v_r_979_;
}
}
LEAN_EXPORT lean_object* lp_competition_R24DotBankHarness_benchExact___lam__0(lean_object* v_a_980_, lean_object* v_b_981_, lean_object* v_x_982_){
_start:
{
lean_object* v___x_983_; 
v___x_983_ = lean_alloc_ctor(0, 2, 0);
lean_ctor_set(v___x_983_, 0, v_a_980_);
lean_ctor_set(v___x_983_, 1, v_b_981_);
return v___x_983_;
}
}
LEAN_EXPORT lean_object* lp_competition_R24DotBankHarness_benchExact___lam__1(){
_start:
{
lean_object* v___x_985_; lean_object* v___x_986_; 
v___x_985_ = lean_io_mono_nanos_now();
v___x_986_ = lean_alloc_ctor(0, 1, 0);
lean_ctor_set(v___x_986_, 0, v___x_985_);
return v___x_986_;
}
}
LEAN_EXPORT lean_object* lp_competition_R24DotBankHarness_benchExact___lam__1___boxed(lean_object* v___y_987_){
_start:
{
lean_object* v_res_988_; 
v_res_988_ = lp_competition_R24DotBankHarness_benchExact___lam__1();
return v_res_988_;
}
}
LEAN_EXPORT uint32_t lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotBankHarness_benchExact_spec__0___redArg___lam__1(lean_object* v_a_989_, uint32_t v___x_990_, lean_object* v_iters_991_, lean_object* v_x_992_){
_start:
{
uint32_t v___x_993_; 
v___x_993_ = lp_competition_R24DotBankHarness_passExact(v_a_989_, v___x_990_, v_iters_991_);
return v___x_993_;
}
}
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotBankHarness_benchExact_spec__0___redArg___lam__1___boxed(lean_object* v_a_994_, lean_object* v___x_995_, lean_object* v_iters_996_, lean_object* v_x_997_){
_start:
{
uint32_t v___x_1541__boxed_998_; uint32_t v_res_999_; lean_object* v_r_1000_; 
v___x_1541__boxed_998_ = lean_unbox_uint32(v___x_995_);
lean_dec(v___x_995_);
v_res_999_ = lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotBankHarness_benchExact_spec__0___redArg___lam__1(v_a_994_, v___x_1541__boxed_998_, v_iters_996_, v_x_997_);
v_r_1000_ = lean_box_uint32(v_res_999_);
return v_r_1000_;
}
}
LEAN_EXPORT uint32_t lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotBankHarness_benchExact_spec__0___redArg___lam__0(lean_object* v_a_1001_, lean_object* v_x_1002_){
_start:
{
lean_object* v_fst_1003_; lean_object* v_snd_1004_; lean_object* v___x_1005_; uint32_t v___x_1006_; 
v_fst_1003_ = lean_ctor_get(v_a_1001_, 0);
v_snd_1004_ = lean_ctor_get(v_a_1001_, 1);
v___x_1005_ = lp_competition_Submission_R24GenericDotBank_exactBank(v_fst_1003_, v_snd_1004_);
v___x_1006_ = lp_competition_R24DotBankHarness_hashAll(v___x_1005_);
lean_dec_ref(v___x_1005_);
return v___x_1006_;
}
}
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotBankHarness_benchExact_spec__0___redArg___lam__0___boxed(lean_object* v_a_1007_, lean_object* v_x_1008_){
_start:
{
uint32_t v_res_1009_; lean_object* v_r_1010_; 
v_res_1009_ = lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotBankHarness_benchExact_spec__0___redArg___lam__0(v_a_1007_, v_x_1008_);
lean_dec_ref(v_a_1007_);
v_r_1010_ = lean_box_uint32(v_res_1009_);
return v_r_1010_;
}
}
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00__private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotBankHarness_benchExact_spec__0_spec__0___redArg(lean_object* v_a_1014_, lean_object* v_c_1015_, uint32_t v_expected_1016_, lean_object* v_iters_1017_, lean_object* v_work_1018_, lean_object* v_range_1019_, lean_object* v_b_1020_, lean_object* v_i_1021_){
_start:
{
lean_object* v_stop_1023_; lean_object* v_step_1024_; uint8_t v___x_1025_; 
v_stop_1023_ = lean_ctor_get(v_range_1019_, 1);
v_step_1024_ = lean_ctor_get(v_range_1019_, 2);
v___x_1025_ = lean_nat_dec_lt(v_i_1021_, v_stop_1023_);
if (v___x_1025_ == 0)
{
lean_object* v___x_1026_; 
lean_dec(v_i_1021_);
lean_dec(v_work_1018_);
lean_dec(v_iters_1017_);
lean_dec_ref(v_c_1015_);
lean_dec_ref(v_a_1014_);
v___x_1026_ = lean_alloc_ctor(0, 1, 0);
lean_ctor_set(v___x_1026_, 0, v_b_1020_);
return v___x_1026_;
}
else
{
lean_object* v___f_1027_; lean_object* v___x_1028_; lean_object* v_a_1029_; lean_object* v_name_1030_; lean_object* v___x_1031_; uint32_t v___x_1032_; lean_object* v___x_1033_; 
lean_inc_ref(v_a_1014_);
v___f_1027_ = lean_alloc_closure((void*)(lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotBankHarness_benchExact_spec__0___redArg___lam__0___boxed), 2, 1);
lean_closure_set(v___f_1027_, 0, v_a_1014_);
lean_inc_ref(v___f_1027_);
v___x_1028_ = l_IO_lazyPure___redArg(v___f_1027_);
v_a_1029_ = lean_ctor_get(v___x_1028_, 0);
lean_inc(v_a_1029_);
lean_dec_ref(v___x_1028_);
v_name_1030_ = lean_ctor_get(v_c_1015_, 0);
v___x_1031_ = ((lean_object*)(lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00__private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotBankHarness_benchExact_spec__0_spec__0___redArg___closed__0));
v___x_1032_ = lean_unbox_uint32(v_a_1029_);
lean_dec(v_a_1029_);
lean_inc_ref(v_name_1030_);
v___x_1033_ = lp_competition_R24DotBankHarness_checkWord(v_name_1030_, v___x_1031_, v___x_1032_, v_expected_1016_);
if (lean_obj_tag(v___x_1033_) == 0)
{
lean_object* v___x_1034_; uint32_t v___x_1035_; lean_object* v___x_1036_; lean_object* v___f_1037_; lean_object* v___x_1038_; lean_object* v_a_1039_; lean_object* v___x_1040_; uint32_t v___x_1041_; uint32_t v___x_1042_; uint32_t v___x_1043_; lean_object* v___x_1044_; uint32_t v___x_1045_; lean_object* v___x_1046_; 
lean_dec_ref_known(v___x_1033_, 1);
v___x_1034_ = lean_io_mono_nanos_now();
v___x_1035_ = lp_competition_R24DotBankHarness_seed(v_i_1021_);
v___x_1036_ = lean_box_uint32(v___x_1035_);
lean_inc(v_iters_1017_);
lean_inc_ref(v_a_1014_);
v___f_1037_ = lean_alloc_closure((void*)(lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotBankHarness_benchExact_spec__0___redArg___lam__1___boxed), 4, 3);
lean_closure_set(v___f_1037_, 0, v_a_1014_);
lean_closure_set(v___f_1037_, 1, v___x_1036_);
lean_closure_set(v___f_1037_, 2, v_iters_1017_);
v___x_1038_ = l_IO_lazyPure___redArg(v___f_1037_);
v_a_1039_ = lean_ctor_get(v___x_1038_, 0);
lean_inc(v_a_1039_);
lean_dec_ref(v___x_1038_);
v___x_1040_ = lean_io_mono_nanos_now();
v___x_1041_ = lean_uint32_of_nat(v_iters_1017_);
v___x_1042_ = lean_uint32_mul(v___x_1041_, v_expected_1016_);
v___x_1043_ = lean_uint32_add(v___x_1035_, v___x_1042_);
v___x_1044_ = ((lean_object*)(lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00__private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotBankHarness_benchExact_spec__0_spec__0___redArg___closed__1));
v___x_1045_ = lean_unbox_uint32(v_a_1039_);
lean_inc_ref(v_name_1030_);
v___x_1046_ = lp_competition_R24DotBankHarness_checkWord(v_name_1030_, v___x_1044_, v___x_1045_, v___x_1043_);
if (lean_obj_tag(v___x_1046_) == 0)
{
lean_object* v___x_1047_; lean_object* v_a_1048_; lean_object* v___x_1049_; uint32_t v___x_1050_; lean_object* v___x_1051_; 
lean_dec_ref_known(v___x_1046_, 1);
v___x_1047_ = l_IO_lazyPure___redArg(v___f_1027_);
v_a_1048_ = lean_ctor_get(v___x_1047_, 0);
lean_inc(v_a_1048_);
lean_dec_ref(v___x_1047_);
v___x_1049_ = ((lean_object*)(lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00__private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotBankHarness_benchExact_spec__0_spec__0___redArg___closed__2));
v___x_1050_ = lean_unbox_uint32(v_a_1048_);
lean_inc_ref(v_name_1030_);
v___x_1051_ = lp_competition_R24DotBankHarness_checkWord(v_name_1030_, v___x_1049_, v___x_1050_, v_expected_1016_);
if (lean_obj_tag(v___x_1051_) == 0)
{
lean_object* v___x_1052_; lean_object* v___x_1053_; uint32_t v___x_1054_; uint32_t v___x_1055_; lean_object* v___x_1056_; lean_object* v___x_1057_; 
lean_dec_ref_known(v___x_1051_, 1);
v___x_1052_ = lean_nat_sub(v___x_1040_, v___x_1034_);
lean_dec(v___x_1034_);
lean_dec(v___x_1040_);
lean_inc(v_iters_1017_);
lean_inc(v_work_1018_);
lean_inc(v_i_1021_);
v___x_1053_ = lean_alloc_ctor(0, 4, 12);
lean_ctor_set(v___x_1053_, 0, v_i_1021_);
lean_ctor_set(v___x_1053_, 1, v_work_1018_);
lean_ctor_set(v___x_1053_, 2, v_iters_1017_);
lean_ctor_set(v___x_1053_, 3, v___x_1052_);
v___x_1054_ = lean_unbox_uint32(v_a_1039_);
lean_dec(v_a_1039_);
lean_ctor_set_uint32(v___x_1053_, sizeof(void*)*4, v___x_1054_);
lean_ctor_set_uint32(v___x_1053_, sizeof(void*)*4 + 4, v___x_1043_);
v___x_1055_ = lean_unbox_uint32(v_a_1048_);
lean_dec(v_a_1048_);
lean_ctor_set_uint32(v___x_1053_, sizeof(void*)*4 + 8, v___x_1055_);
v___x_1056_ = lean_array_push(v_b_1020_, v___x_1053_);
v___x_1057_ = lean_nat_add(v_i_1021_, v_step_1024_);
lean_dec(v_i_1021_);
v_b_1020_ = v___x_1056_;
v_i_1021_ = v___x_1057_;
goto _start;
}
else
{
lean_object* v_a_1059_; lean_object* v___x_1061_; uint8_t v_isShared_1062_; uint8_t v_isSharedCheck_1066_; 
lean_dec(v_a_1048_);
lean_dec(v___x_1040_);
lean_dec(v_a_1039_);
lean_dec(v___x_1034_);
lean_dec(v_i_1021_);
lean_dec_ref(v_b_1020_);
lean_dec(v_work_1018_);
lean_dec(v_iters_1017_);
lean_dec_ref(v_c_1015_);
lean_dec_ref(v_a_1014_);
v_a_1059_ = lean_ctor_get(v___x_1051_, 0);
v_isSharedCheck_1066_ = !lean_is_exclusive(v___x_1051_);
if (v_isSharedCheck_1066_ == 0)
{
v___x_1061_ = v___x_1051_;
v_isShared_1062_ = v_isSharedCheck_1066_;
goto v_resetjp_1060_;
}
else
{
lean_inc(v_a_1059_);
lean_dec(v___x_1051_);
v___x_1061_ = lean_box(0);
v_isShared_1062_ = v_isSharedCheck_1066_;
goto v_resetjp_1060_;
}
v_resetjp_1060_:
{
lean_object* v___x_1064_; 
if (v_isShared_1062_ == 0)
{
v___x_1064_ = v___x_1061_;
goto v_reusejp_1063_;
}
else
{
lean_object* v_reuseFailAlloc_1065_; 
v_reuseFailAlloc_1065_ = lean_alloc_ctor(1, 1, 0);
lean_ctor_set(v_reuseFailAlloc_1065_, 0, v_a_1059_);
v___x_1064_ = v_reuseFailAlloc_1065_;
goto v_reusejp_1063_;
}
v_reusejp_1063_:
{
return v___x_1064_;
}
}
}
}
else
{
lean_object* v_a_1067_; lean_object* v___x_1069_; uint8_t v_isShared_1070_; uint8_t v_isSharedCheck_1074_; 
lean_dec(v___x_1040_);
lean_dec(v_a_1039_);
lean_dec(v___x_1034_);
lean_dec_ref(v___f_1027_);
lean_dec(v_i_1021_);
lean_dec_ref(v_b_1020_);
lean_dec(v_work_1018_);
lean_dec(v_iters_1017_);
lean_dec_ref(v_c_1015_);
lean_dec_ref(v_a_1014_);
v_a_1067_ = lean_ctor_get(v___x_1046_, 0);
v_isSharedCheck_1074_ = !lean_is_exclusive(v___x_1046_);
if (v_isSharedCheck_1074_ == 0)
{
v___x_1069_ = v___x_1046_;
v_isShared_1070_ = v_isSharedCheck_1074_;
goto v_resetjp_1068_;
}
else
{
lean_inc(v_a_1067_);
lean_dec(v___x_1046_);
v___x_1069_ = lean_box(0);
v_isShared_1070_ = v_isSharedCheck_1074_;
goto v_resetjp_1068_;
}
v_resetjp_1068_:
{
lean_object* v___x_1072_; 
if (v_isShared_1070_ == 0)
{
v___x_1072_ = v___x_1069_;
goto v_reusejp_1071_;
}
else
{
lean_object* v_reuseFailAlloc_1073_; 
v_reuseFailAlloc_1073_ = lean_alloc_ctor(1, 1, 0);
lean_ctor_set(v_reuseFailAlloc_1073_, 0, v_a_1067_);
v___x_1072_ = v_reuseFailAlloc_1073_;
goto v_reusejp_1071_;
}
v_reusejp_1071_:
{
return v___x_1072_;
}
}
}
}
else
{
lean_object* v_a_1075_; lean_object* v___x_1077_; uint8_t v_isShared_1078_; uint8_t v_isSharedCheck_1082_; 
lean_dec_ref(v___f_1027_);
lean_dec(v_i_1021_);
lean_dec_ref(v_b_1020_);
lean_dec(v_work_1018_);
lean_dec(v_iters_1017_);
lean_dec_ref(v_c_1015_);
lean_dec_ref(v_a_1014_);
v_a_1075_ = lean_ctor_get(v___x_1033_, 0);
v_isSharedCheck_1082_ = !lean_is_exclusive(v___x_1033_);
if (v_isSharedCheck_1082_ == 0)
{
v___x_1077_ = v___x_1033_;
v_isShared_1078_ = v_isSharedCheck_1082_;
goto v_resetjp_1076_;
}
else
{
lean_inc(v_a_1075_);
lean_dec(v___x_1033_);
v___x_1077_ = lean_box(0);
v_isShared_1078_ = v_isSharedCheck_1082_;
goto v_resetjp_1076_;
}
v_resetjp_1076_:
{
lean_object* v___x_1080_; 
if (v_isShared_1078_ == 0)
{
v___x_1080_ = v___x_1077_;
goto v_reusejp_1079_;
}
else
{
lean_object* v_reuseFailAlloc_1081_; 
v_reuseFailAlloc_1081_ = lean_alloc_ctor(1, 1, 0);
lean_ctor_set(v_reuseFailAlloc_1081_, 0, v_a_1075_);
v___x_1080_ = v_reuseFailAlloc_1081_;
goto v_reusejp_1079_;
}
v_reusejp_1079_:
{
return v___x_1080_;
}
}
}
}
}
}
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00__private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotBankHarness_benchExact_spec__0_spec__0___redArg___boxed(lean_object* v_a_1083_, lean_object* v_c_1084_, lean_object* v_expected_1085_, lean_object* v_iters_1086_, lean_object* v_work_1087_, lean_object* v_range_1088_, lean_object* v_b_1089_, lean_object* v_i_1090_, lean_object* v___y_1091_){
_start:
{
uint32_t v_expected_boxed_1092_; lean_object* v_res_1093_; 
v_expected_boxed_1092_ = lean_unbox_uint32(v_expected_1085_);
lean_dec(v_expected_1085_);
v_res_1093_ = lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00__private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotBankHarness_benchExact_spec__0_spec__0___redArg(v_a_1083_, v_c_1084_, v_expected_boxed_1092_, v_iters_1086_, v_work_1087_, v_range_1088_, v_b_1089_, v_i_1090_);
lean_dec_ref(v_range_1088_);
return v_res_1093_;
}
}
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotBankHarness_benchExact_spec__0___redArg(lean_object* v_a_1094_, lean_object* v_c_1095_, uint32_t v_expected_1096_, lean_object* v_iters_1097_, lean_object* v_work_1098_, lean_object* v_range_1099_, lean_object* v_b_1100_, lean_object* v_i_1101_){
_start:
{
lean_object* v_stop_1103_; lean_object* v_step_1104_; uint8_t v___x_1105_; 
v_stop_1103_ = lean_ctor_get(v_range_1099_, 1);
v_step_1104_ = lean_ctor_get(v_range_1099_, 2);
v___x_1105_ = lean_nat_dec_lt(v_i_1101_, v_stop_1103_);
if (v___x_1105_ == 0)
{
lean_object* v___x_1106_; 
lean_dec(v_i_1101_);
lean_dec(v_work_1098_);
lean_dec(v_iters_1097_);
lean_dec_ref(v_c_1095_);
lean_dec_ref(v_a_1094_);
v___x_1106_ = lean_alloc_ctor(0, 1, 0);
lean_ctor_set(v___x_1106_, 0, v_b_1100_);
return v___x_1106_;
}
else
{
lean_object* v___f_1107_; lean_object* v___x_1108_; lean_object* v_a_1109_; lean_object* v_name_1110_; lean_object* v___x_1111_; uint32_t v___x_1112_; lean_object* v___x_1113_; 
lean_inc_ref(v_a_1094_);
v___f_1107_ = lean_alloc_closure((void*)(lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotBankHarness_benchExact_spec__0___redArg___lam__0___boxed), 2, 1);
lean_closure_set(v___f_1107_, 0, v_a_1094_);
lean_inc_ref(v___f_1107_);
v___x_1108_ = l_IO_lazyPure___redArg(v___f_1107_);
v_a_1109_ = lean_ctor_get(v___x_1108_, 0);
lean_inc(v_a_1109_);
lean_dec_ref(v___x_1108_);
v_name_1110_ = lean_ctor_get(v_c_1095_, 0);
v___x_1111_ = ((lean_object*)(lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00__private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotBankHarness_benchExact_spec__0_spec__0___redArg___closed__0));
v___x_1112_ = lean_unbox_uint32(v_a_1109_);
lean_dec(v_a_1109_);
lean_inc_ref(v_name_1110_);
v___x_1113_ = lp_competition_R24DotBankHarness_checkWord(v_name_1110_, v___x_1111_, v___x_1112_, v_expected_1096_);
if (lean_obj_tag(v___x_1113_) == 0)
{
lean_object* v___x_1114_; uint32_t v___x_1115_; lean_object* v___x_1116_; lean_object* v___f_1117_; lean_object* v___x_1118_; lean_object* v_a_1119_; lean_object* v___x_1120_; uint32_t v___x_1121_; uint32_t v___x_1122_; uint32_t v___x_1123_; lean_object* v___x_1124_; uint32_t v___x_1125_; lean_object* v___x_1126_; 
lean_dec_ref_known(v___x_1113_, 1);
v___x_1114_ = lean_io_mono_nanos_now();
v___x_1115_ = lp_competition_R24DotBankHarness_seed(v_i_1101_);
v___x_1116_ = lean_box_uint32(v___x_1115_);
lean_inc(v_iters_1097_);
lean_inc_ref(v_a_1094_);
v___f_1117_ = lean_alloc_closure((void*)(lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotBankHarness_benchExact_spec__0___redArg___lam__1___boxed), 4, 3);
lean_closure_set(v___f_1117_, 0, v_a_1094_);
lean_closure_set(v___f_1117_, 1, v___x_1116_);
lean_closure_set(v___f_1117_, 2, v_iters_1097_);
v___x_1118_ = l_IO_lazyPure___redArg(v___f_1117_);
v_a_1119_ = lean_ctor_get(v___x_1118_, 0);
lean_inc(v_a_1119_);
lean_dec_ref(v___x_1118_);
v___x_1120_ = lean_io_mono_nanos_now();
v___x_1121_ = lean_uint32_of_nat(v_iters_1097_);
v___x_1122_ = lean_uint32_mul(v___x_1121_, v_expected_1096_);
v___x_1123_ = lean_uint32_add(v___x_1115_, v___x_1122_);
v___x_1124_ = ((lean_object*)(lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00__private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotBankHarness_benchExact_spec__0_spec__0___redArg___closed__1));
v___x_1125_ = lean_unbox_uint32(v_a_1119_);
lean_inc_ref(v_name_1110_);
v___x_1126_ = lp_competition_R24DotBankHarness_checkWord(v_name_1110_, v___x_1124_, v___x_1125_, v___x_1123_);
if (lean_obj_tag(v___x_1126_) == 0)
{
lean_object* v___x_1127_; lean_object* v_a_1128_; lean_object* v___x_1129_; uint32_t v___x_1130_; lean_object* v___x_1131_; 
lean_dec_ref_known(v___x_1126_, 1);
v___x_1127_ = l_IO_lazyPure___redArg(v___f_1107_);
v_a_1128_ = lean_ctor_get(v___x_1127_, 0);
lean_inc(v_a_1128_);
lean_dec_ref(v___x_1127_);
v___x_1129_ = ((lean_object*)(lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00__private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotBankHarness_benchExact_spec__0_spec__0___redArg___closed__2));
v___x_1130_ = lean_unbox_uint32(v_a_1128_);
lean_inc_ref(v_name_1110_);
v___x_1131_ = lp_competition_R24DotBankHarness_checkWord(v_name_1110_, v___x_1129_, v___x_1130_, v_expected_1096_);
if (lean_obj_tag(v___x_1131_) == 0)
{
lean_object* v___x_1132_; lean_object* v___x_1133_; uint32_t v___x_1134_; uint32_t v___x_1135_; lean_object* v___x_1136_; lean_object* v___x_1137_; lean_object* v___x_1138_; 
lean_dec_ref_known(v___x_1131_, 1);
v___x_1132_ = lean_nat_sub(v___x_1120_, v___x_1114_);
lean_dec(v___x_1114_);
lean_dec(v___x_1120_);
lean_inc(v_iters_1097_);
lean_inc(v_work_1098_);
lean_inc(v_i_1101_);
v___x_1133_ = lean_alloc_ctor(0, 4, 12);
lean_ctor_set(v___x_1133_, 0, v_i_1101_);
lean_ctor_set(v___x_1133_, 1, v_work_1098_);
lean_ctor_set(v___x_1133_, 2, v_iters_1097_);
lean_ctor_set(v___x_1133_, 3, v___x_1132_);
v___x_1134_ = lean_unbox_uint32(v_a_1119_);
lean_dec(v_a_1119_);
lean_ctor_set_uint32(v___x_1133_, sizeof(void*)*4, v___x_1134_);
lean_ctor_set_uint32(v___x_1133_, sizeof(void*)*4 + 4, v___x_1123_);
v___x_1135_ = lean_unbox_uint32(v_a_1128_);
lean_dec(v_a_1128_);
lean_ctor_set_uint32(v___x_1133_, sizeof(void*)*4 + 8, v___x_1135_);
v___x_1136_ = lean_array_push(v_b_1100_, v___x_1133_);
v___x_1137_ = lean_nat_add(v_i_1101_, v_step_1104_);
lean_dec(v_i_1101_);
v___x_1138_ = lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00__private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotBankHarness_benchExact_spec__0_spec__0___redArg(v_a_1094_, v_c_1095_, v_expected_1096_, v_iters_1097_, v_work_1098_, v_range_1099_, v___x_1136_, v___x_1137_);
return v___x_1138_;
}
else
{
lean_object* v_a_1139_; lean_object* v___x_1141_; uint8_t v_isShared_1142_; uint8_t v_isSharedCheck_1146_; 
lean_dec(v_a_1128_);
lean_dec(v___x_1120_);
lean_dec(v_a_1119_);
lean_dec(v___x_1114_);
lean_dec(v_i_1101_);
lean_dec_ref(v_b_1100_);
lean_dec(v_work_1098_);
lean_dec(v_iters_1097_);
lean_dec_ref(v_c_1095_);
lean_dec_ref(v_a_1094_);
v_a_1139_ = lean_ctor_get(v___x_1131_, 0);
v_isSharedCheck_1146_ = !lean_is_exclusive(v___x_1131_);
if (v_isSharedCheck_1146_ == 0)
{
v___x_1141_ = v___x_1131_;
v_isShared_1142_ = v_isSharedCheck_1146_;
goto v_resetjp_1140_;
}
else
{
lean_inc(v_a_1139_);
lean_dec(v___x_1131_);
v___x_1141_ = lean_box(0);
v_isShared_1142_ = v_isSharedCheck_1146_;
goto v_resetjp_1140_;
}
v_resetjp_1140_:
{
lean_object* v___x_1144_; 
if (v_isShared_1142_ == 0)
{
v___x_1144_ = v___x_1141_;
goto v_reusejp_1143_;
}
else
{
lean_object* v_reuseFailAlloc_1145_; 
v_reuseFailAlloc_1145_ = lean_alloc_ctor(1, 1, 0);
lean_ctor_set(v_reuseFailAlloc_1145_, 0, v_a_1139_);
v___x_1144_ = v_reuseFailAlloc_1145_;
goto v_reusejp_1143_;
}
v_reusejp_1143_:
{
return v___x_1144_;
}
}
}
}
else
{
lean_object* v_a_1147_; lean_object* v___x_1149_; uint8_t v_isShared_1150_; uint8_t v_isSharedCheck_1154_; 
lean_dec(v___x_1120_);
lean_dec(v_a_1119_);
lean_dec(v___x_1114_);
lean_dec_ref(v___f_1107_);
lean_dec(v_i_1101_);
lean_dec_ref(v_b_1100_);
lean_dec(v_work_1098_);
lean_dec(v_iters_1097_);
lean_dec_ref(v_c_1095_);
lean_dec_ref(v_a_1094_);
v_a_1147_ = lean_ctor_get(v___x_1126_, 0);
v_isSharedCheck_1154_ = !lean_is_exclusive(v___x_1126_);
if (v_isSharedCheck_1154_ == 0)
{
v___x_1149_ = v___x_1126_;
v_isShared_1150_ = v_isSharedCheck_1154_;
goto v_resetjp_1148_;
}
else
{
lean_inc(v_a_1147_);
lean_dec(v___x_1126_);
v___x_1149_ = lean_box(0);
v_isShared_1150_ = v_isSharedCheck_1154_;
goto v_resetjp_1148_;
}
v_resetjp_1148_:
{
lean_object* v___x_1152_; 
if (v_isShared_1150_ == 0)
{
v___x_1152_ = v___x_1149_;
goto v_reusejp_1151_;
}
else
{
lean_object* v_reuseFailAlloc_1153_; 
v_reuseFailAlloc_1153_ = lean_alloc_ctor(1, 1, 0);
lean_ctor_set(v_reuseFailAlloc_1153_, 0, v_a_1147_);
v___x_1152_ = v_reuseFailAlloc_1153_;
goto v_reusejp_1151_;
}
v_reusejp_1151_:
{
return v___x_1152_;
}
}
}
}
else
{
lean_object* v_a_1155_; lean_object* v___x_1157_; uint8_t v_isShared_1158_; uint8_t v_isSharedCheck_1162_; 
lean_dec_ref(v___f_1107_);
lean_dec(v_i_1101_);
lean_dec_ref(v_b_1100_);
lean_dec(v_work_1098_);
lean_dec(v_iters_1097_);
lean_dec_ref(v_c_1095_);
lean_dec_ref(v_a_1094_);
v_a_1155_ = lean_ctor_get(v___x_1113_, 0);
v_isSharedCheck_1162_ = !lean_is_exclusive(v___x_1113_);
if (v_isSharedCheck_1162_ == 0)
{
v___x_1157_ = v___x_1113_;
v_isShared_1158_ = v_isSharedCheck_1162_;
goto v_resetjp_1156_;
}
else
{
lean_inc(v_a_1155_);
lean_dec(v___x_1113_);
v___x_1157_ = lean_box(0);
v_isShared_1158_ = v_isSharedCheck_1162_;
goto v_resetjp_1156_;
}
v_resetjp_1156_:
{
lean_object* v___x_1160_; 
if (v_isShared_1158_ == 0)
{
v___x_1160_ = v___x_1157_;
goto v_reusejp_1159_;
}
else
{
lean_object* v_reuseFailAlloc_1161_; 
v_reuseFailAlloc_1161_ = lean_alloc_ctor(1, 1, 0);
lean_ctor_set(v_reuseFailAlloc_1161_, 0, v_a_1155_);
v___x_1160_ = v_reuseFailAlloc_1161_;
goto v_reusejp_1159_;
}
v_reusejp_1159_:
{
return v___x_1160_;
}
}
}
}
}
}
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotBankHarness_benchExact_spec__0___redArg___boxed(lean_object* v_a_1163_, lean_object* v_c_1164_, lean_object* v_expected_1165_, lean_object* v_iters_1166_, lean_object* v_work_1167_, lean_object* v_range_1168_, lean_object* v_b_1169_, lean_object* v_i_1170_, lean_object* v___y_1171_){
_start:
{
uint32_t v_expected_boxed_1172_; lean_object* v_res_1173_; 
v_expected_boxed_1172_ = lean_unbox_uint32(v_expected_1165_);
lean_dec(v_expected_1165_);
v_res_1173_ = lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotBankHarness_benchExact_spec__0___redArg(v_a_1163_, v_c_1164_, v_expected_boxed_1172_, v_iters_1166_, v_work_1167_, v_range_1168_, v_b_1169_, v_i_1170_);
lean_dec_ref(v_range_1168_);
return v_res_1173_;
}
}
LEAN_EXPORT lean_object* lp_competition_R24DotBankHarness_benchExact(lean_object* v_c_1181_, lean_object* v_a_1182_, lean_object* v_b_1183_, lean_object* v_macs_1184_, uint32_t v_expected_1185_){
_start:
{
lean_object* v___f_1187_; lean_object* v___x_1188_; lean_object* v_a_1189_; lean_object* v___x_1190_; lean_object* v_a_1191_; lean_object* v_inner_1192_; lean_object* v_rows_1193_; lean_object* v_cols_1194_; lean_object* v___x_1195_; lean_object* v_work_1196_; lean_object* v_iters_1197_; lean_object* v___x_1198_; lean_object* v___x_1199_; lean_object* v___x_1200_; lean_object* v___x_1201_; 
v___f_1187_ = lean_alloc_closure((void*)(lp_competition_R24DotBankHarness_benchExact___lam__0), 3, 2);
lean_closure_set(v___f_1187_, 0, v_a_1182_);
lean_closure_set(v___f_1187_, 1, v_b_1183_);
v___x_1188_ = l_IO_lazyPure___redArg(v___f_1187_);
v_a_1189_ = lean_ctor_get(v___x_1188_, 0);
lean_inc(v_a_1189_);
lean_dec_ref(v___x_1188_);
v___x_1190_ = lp_competition_R24DotBankHarness_benchExact___lam__1();
v_a_1191_ = lean_ctor_get(v___x_1190_, 0);
lean_inc(v_a_1191_);
lean_dec_ref(v___x_1190_);
v_inner_1192_ = lean_ctor_get(v_c_1181_, 2);
v_rows_1193_ = lean_ctor_get(v_c_1181_, 3);
v_cols_1194_ = lean_ctor_get(v_c_1181_, 4);
v___x_1195_ = lean_nat_mul(v_rows_1193_, v_cols_1194_);
v_work_1196_ = lean_nat_mul(v___x_1195_, v_inner_1192_);
lean_dec(v___x_1195_);
v_iters_1197_ = lp_competition_R24DotBankHarness_repeats(v_macs_1184_, v_work_1196_);
v___x_1198_ = lean_unsigned_to_nat(0u);
v___x_1199_ = ((lean_object*)(lp_competition_R24DotBankHarness_benchExact___closed__0));
v___x_1200_ = ((lean_object*)(lp_competition_R24DotBankHarness_benchExact___closed__1));
lean_inc_ref(v_c_1181_);
v___x_1201_ = lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotBankHarness_benchExact_spec__0___redArg(v_a_1189_, v_c_1181_, v_expected_1185_, v_iters_1197_, v_work_1196_, v___x_1200_, v___x_1199_, v___x_1198_);
if (lean_obj_tag(v___x_1201_) == 0)
{
lean_object* v_a_1202_; lean_object* v___x_1203_; lean_object* v_a_1204_; lean_object* v___x_1205_; lean_object* v___x_1206_; lean_object* v___x_1207_; 
v_a_1202_ = lean_ctor_get(v___x_1201_, 0);
lean_inc(v_a_1202_);
lean_dec_ref_known(v___x_1201_, 1);
v___x_1203_ = lp_competition_R24DotBankHarness_benchExact___lam__1();
v_a_1204_ = lean_ctor_get(v___x_1203_, 0);
lean_inc(v_a_1204_);
lean_dec_ref(v___x_1203_);
v___x_1205_ = ((lean_object*)(lp_competition_R24DotBankHarness_benchExact___closed__2));
v___x_1206_ = lean_nat_sub(v_a_1204_, v_a_1191_);
lean_dec(v_a_1191_);
lean_dec(v_a_1204_);
v___x_1207_ = lp_competition_R24DotBankHarness_emit(v_c_1181_, v___x_1205_, v___x_1206_, v_a_1202_);
lean_dec(v_a_1202_);
lean_dec_ref(v_c_1181_);
return v___x_1207_;
}
else
{
lean_object* v_a_1208_; lean_object* v___x_1210_; uint8_t v_isShared_1211_; uint8_t v_isSharedCheck_1215_; 
lean_dec(v_a_1191_);
lean_dec_ref(v_c_1181_);
v_a_1208_ = lean_ctor_get(v___x_1201_, 0);
v_isSharedCheck_1215_ = !lean_is_exclusive(v___x_1201_);
if (v_isSharedCheck_1215_ == 0)
{
v___x_1210_ = v___x_1201_;
v_isShared_1211_ = v_isSharedCheck_1215_;
goto v_resetjp_1209_;
}
else
{
lean_inc(v_a_1208_);
lean_dec(v___x_1201_);
v___x_1210_ = lean_box(0);
v_isShared_1211_ = v_isSharedCheck_1215_;
goto v_resetjp_1209_;
}
v_resetjp_1209_:
{
lean_object* v___x_1213_; 
if (v_isShared_1211_ == 0)
{
v___x_1213_ = v___x_1210_;
goto v_reusejp_1212_;
}
else
{
lean_object* v_reuseFailAlloc_1214_; 
v_reuseFailAlloc_1214_ = lean_alloc_ctor(1, 1, 0);
lean_ctor_set(v_reuseFailAlloc_1214_, 0, v_a_1208_);
v___x_1213_ = v_reuseFailAlloc_1214_;
goto v_reusejp_1212_;
}
v_reusejp_1212_:
{
return v___x_1213_;
}
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_R24DotBankHarness_benchExact___boxed(lean_object* v_c_1216_, lean_object* v_a_1217_, lean_object* v_b_1218_, lean_object* v_macs_1219_, lean_object* v_expected_1220_, lean_object* v_a_1221_){
_start:
{
uint32_t v_expected_boxed_1222_; lean_object* v_res_1223_; 
v_expected_boxed_1222_ = lean_unbox_uint32(v_expected_1220_);
lean_dec(v_expected_1220_);
v_res_1223_ = lp_competition_R24DotBankHarness_benchExact(v_c_1216_, v_a_1217_, v_b_1218_, v_macs_1219_, v_expected_boxed_1222_);
lean_dec(v_macs_1219_);
return v_res_1223_;
}
}
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotBankHarness_benchExact_spec__0(lean_object* v_a_1224_, lean_object* v_c_1225_, uint32_t v_expected_1226_, lean_object* v_iters_1227_, lean_object* v_work_1228_, lean_object* v_range_1229_, lean_object* v_b_1230_, lean_object* v_i_1231_, lean_object* v_hs_1232_, lean_object* v_hl_1233_){
_start:
{
lean_object* v___x_1235_; 
v___x_1235_ = lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotBankHarness_benchExact_spec__0___redArg(v_a_1224_, v_c_1225_, v_expected_1226_, v_iters_1227_, v_work_1228_, v_range_1229_, v_b_1230_, v_i_1231_);
return v___x_1235_;
}
}
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotBankHarness_benchExact_spec__0___boxed(lean_object* v_a_1236_, lean_object* v_c_1237_, lean_object* v_expected_1238_, lean_object* v_iters_1239_, lean_object* v_work_1240_, lean_object* v_range_1241_, lean_object* v_b_1242_, lean_object* v_i_1243_, lean_object* v_hs_1244_, lean_object* v_hl_1245_, lean_object* v___y_1246_){
_start:
{
uint32_t v_expected_boxed_1247_; lean_object* v_res_1248_; 
v_expected_boxed_1247_ = lean_unbox_uint32(v_expected_1238_);
lean_dec(v_expected_1238_);
v_res_1248_ = lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotBankHarness_benchExact_spec__0(v_a_1236_, v_c_1237_, v_expected_boxed_1247_, v_iters_1239_, v_work_1240_, v_range_1241_, v_b_1242_, v_i_1243_, v_hs_1244_, v_hl_1245_);
lean_dec_ref(v_range_1241_);
return v_res_1248_;
}
}
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00__private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotBankHarness_benchExact_spec__0_spec__0(lean_object* v_a_1249_, lean_object* v_c_1250_, uint32_t v_expected_1251_, lean_object* v_iters_1252_, lean_object* v_work_1253_, lean_object* v_range_1254_, lean_object* v_b_1255_, lean_object* v_i_1256_, lean_object* v_hs_1257_, lean_object* v_hl_1258_){
_start:
{
lean_object* v___x_1260_; 
v___x_1260_ = lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00__private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotBankHarness_benchExact_spec__0_spec__0___redArg(v_a_1249_, v_c_1250_, v_expected_1251_, v_iters_1252_, v_work_1253_, v_range_1254_, v_b_1255_, v_i_1256_);
return v___x_1260_;
}
}
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00__private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotBankHarness_benchExact_spec__0_spec__0___boxed(lean_object* v_a_1261_, lean_object* v_c_1262_, lean_object* v_expected_1263_, lean_object* v_iters_1264_, lean_object* v_work_1265_, lean_object* v_range_1266_, lean_object* v_b_1267_, lean_object* v_i_1268_, lean_object* v_hs_1269_, lean_object* v_hl_1270_, lean_object* v___y_1271_){
_start:
{
uint32_t v_expected_boxed_1272_; lean_object* v_res_1273_; 
v_expected_boxed_1272_ = lean_unbox_uint32(v_expected_1263_);
lean_dec(v_expected_1263_);
v_res_1273_ = lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00__private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotBankHarness_benchExact_spec__0_spec__0(v_a_1261_, v_c_1262_, v_expected_boxed_1272_, v_iters_1264_, v_work_1265_, v_range_1266_, v_b_1267_, v_i_1268_, v_hs_1269_, v_hl_1270_);
lean_dec_ref(v_range_1266_);
return v_res_1273_;
}
}
LEAN_EXPORT uint32_t lp_competition_R24DotBankHarness_passEager(lean_object* v_p_1274_, uint32_t v_s_1275_, lean_object* v_iters_1276_){
_start:
{
lean_object* v_zero_1277_; uint8_t v_isZero_1278_; 
v_zero_1277_ = lean_unsigned_to_nat(0u);
v_isZero_1278_ = lean_nat_dec_eq(v_iters_1276_, v_zero_1277_);
if (v_isZero_1278_ == 1)
{
lean_dec(v_iters_1276_);
lean_dec_ref(v_p_1274_);
return v_s_1275_;
}
else
{
lean_object* v_one_1279_; lean_object* v_n_1280_; lean_object* v_p_1281_; lean_object* v_fst_1282_; lean_object* v_snd_1283_; lean_object* v_out_1284_; uint32_t v_word_1285_; uint32_t v___x_1286_; 
v_one_1279_ = lean_unsigned_to_nat(1u);
v_n_1280_ = lean_nat_sub(v_iters_1276_, v_one_1279_);
lean_dec(v_iters_1276_);
v_p_1281_ = lp_competition_R24DotBarrier_touchBank(v_n_1280_, v_p_1274_);
v_fst_1282_ = lean_ctor_get(v_p_1281_, 0);
lean_inc(v_fst_1282_);
v_snd_1283_ = lean_ctor_get(v_p_1281_, 1);
lean_inc(v_snd_1283_);
v_out_1284_ = lp_competition_Submission_R24GenericDotBank_eagerBank(v_fst_1282_, v_snd_1283_);
lean_dec(v_snd_1283_);
lean_dec(v_fst_1282_);
v_word_1285_ = lp_competition_R24DotBankHarness_hashAll(v_out_1284_);
lean_dec_ref(v_out_1284_);
v___x_1286_ = lean_uint32_add(v_s_1275_, v_word_1285_);
v_p_1274_ = v_p_1281_;
v_s_1275_ = v___x_1286_;
v_iters_1276_ = v_n_1280_;
goto _start;
}
}
}
LEAN_EXPORT lean_object* lp_competition_R24DotBankHarness_passEager___boxed(lean_object* v_p_1288_, lean_object* v_s_1289_, lean_object* v_iters_1290_){
_start:
{
uint32_t v_s_boxed_1291_; uint32_t v_res_1292_; lean_object* v_r_1293_; 
v_s_boxed_1291_ = lean_unbox_uint32(v_s_1289_);
lean_dec(v_s_1289_);
v_res_1292_ = lp_competition_R24DotBankHarness_passEager(v_p_1288_, v_s_boxed_1291_, v_iters_1290_);
v_r_1293_ = lean_box_uint32(v_res_1292_);
return v_r_1293_;
}
}
LEAN_EXPORT uint32_t lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotBankHarness_benchEager_spec__0___redArg___lam__0(lean_object* v_a_1294_, lean_object* v_x_1295_){
_start:
{
lean_object* v_fst_1296_; lean_object* v_snd_1297_; lean_object* v___x_1298_; uint32_t v___x_1299_; 
v_fst_1296_ = lean_ctor_get(v_a_1294_, 0);
v_snd_1297_ = lean_ctor_get(v_a_1294_, 1);
v___x_1298_ = lp_competition_Submission_R24GenericDotBank_eagerBank(v_fst_1296_, v_snd_1297_);
v___x_1299_ = lp_competition_R24DotBankHarness_hashAll(v___x_1298_);
lean_dec_ref(v___x_1298_);
return v___x_1299_;
}
}
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotBankHarness_benchEager_spec__0___redArg___lam__0___boxed(lean_object* v_a_1300_, lean_object* v_x_1301_){
_start:
{
uint32_t v_res_1302_; lean_object* v_r_1303_; 
v_res_1302_ = lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotBankHarness_benchEager_spec__0___redArg___lam__0(v_a_1300_, v_x_1301_);
lean_dec_ref(v_a_1300_);
v_r_1303_ = lean_box_uint32(v_res_1302_);
return v_r_1303_;
}
}
LEAN_EXPORT uint32_t lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotBankHarness_benchEager_spec__0___redArg___lam__1(lean_object* v_a_1304_, uint32_t v___x_1305_, lean_object* v_iters_1306_, lean_object* v_x_1307_){
_start:
{
uint32_t v___x_1308_; 
v___x_1308_ = lp_competition_R24DotBankHarness_passEager(v_a_1304_, v___x_1305_, v_iters_1306_);
return v___x_1308_;
}
}
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotBankHarness_benchEager_spec__0___redArg___lam__1___boxed(lean_object* v_a_1309_, lean_object* v___x_1310_, lean_object* v_iters_1311_, lean_object* v_x_1312_){
_start:
{
uint32_t v___x_1540__boxed_1313_; uint32_t v_res_1314_; lean_object* v_r_1315_; 
v___x_1540__boxed_1313_ = lean_unbox_uint32(v___x_1310_);
lean_dec(v___x_1310_);
v_res_1314_ = lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotBankHarness_benchEager_spec__0___redArg___lam__1(v_a_1309_, v___x_1540__boxed_1313_, v_iters_1311_, v_x_1312_);
v_r_1315_ = lean_box_uint32(v_res_1314_);
return v_r_1315_;
}
}
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00__private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotBankHarness_benchEager_spec__0_spec__0___redArg(lean_object* v_a_1319_, lean_object* v_c_1320_, uint32_t v_expected_1321_, lean_object* v_iters_1322_, lean_object* v_work_1323_, lean_object* v_range_1324_, lean_object* v_b_1325_, lean_object* v_i_1326_){
_start:
{
lean_object* v_stop_1328_; lean_object* v_step_1329_; uint8_t v___x_1330_; 
v_stop_1328_ = lean_ctor_get(v_range_1324_, 1);
v_step_1329_ = lean_ctor_get(v_range_1324_, 2);
v___x_1330_ = lean_nat_dec_lt(v_i_1326_, v_stop_1328_);
if (v___x_1330_ == 0)
{
lean_object* v___x_1331_; 
lean_dec(v_i_1326_);
lean_dec(v_work_1323_);
lean_dec(v_iters_1322_);
lean_dec_ref(v_c_1320_);
lean_dec_ref(v_a_1319_);
v___x_1331_ = lean_alloc_ctor(0, 1, 0);
lean_ctor_set(v___x_1331_, 0, v_b_1325_);
return v___x_1331_;
}
else
{
lean_object* v___f_1332_; lean_object* v___x_1333_; lean_object* v_a_1334_; lean_object* v_name_1335_; lean_object* v___x_1336_; uint32_t v___x_1337_; lean_object* v___x_1338_; 
lean_inc_ref(v_a_1319_);
v___f_1332_ = lean_alloc_closure((void*)(lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotBankHarness_benchEager_spec__0___redArg___lam__0___boxed), 2, 1);
lean_closure_set(v___f_1332_, 0, v_a_1319_);
lean_inc_ref(v___f_1332_);
v___x_1333_ = l_IO_lazyPure___redArg(v___f_1332_);
v_a_1334_ = lean_ctor_get(v___x_1333_, 0);
lean_inc(v_a_1334_);
lean_dec_ref(v___x_1333_);
v_name_1335_ = lean_ctor_get(v_c_1320_, 0);
v___x_1336_ = ((lean_object*)(lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00__private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotBankHarness_benchEager_spec__0_spec__0___redArg___closed__0));
v___x_1337_ = lean_unbox_uint32(v_a_1334_);
lean_dec(v_a_1334_);
lean_inc_ref(v_name_1335_);
v___x_1338_ = lp_competition_R24DotBankHarness_checkWord(v_name_1335_, v___x_1336_, v___x_1337_, v_expected_1321_);
if (lean_obj_tag(v___x_1338_) == 0)
{
lean_object* v___x_1339_; uint32_t v___x_1340_; lean_object* v___x_1341_; lean_object* v___f_1342_; lean_object* v___x_1343_; lean_object* v_a_1344_; lean_object* v___x_1345_; uint32_t v___x_1346_; uint32_t v___x_1347_; uint32_t v___x_1348_; lean_object* v___x_1349_; uint32_t v___x_1350_; lean_object* v___x_1351_; 
lean_dec_ref_known(v___x_1338_, 1);
v___x_1339_ = lean_io_mono_nanos_now();
v___x_1340_ = lp_competition_R24DotBankHarness_seed(v_i_1326_);
v___x_1341_ = lean_box_uint32(v___x_1340_);
lean_inc(v_iters_1322_);
lean_inc_ref(v_a_1319_);
v___f_1342_ = lean_alloc_closure((void*)(lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotBankHarness_benchEager_spec__0___redArg___lam__1___boxed), 4, 3);
lean_closure_set(v___f_1342_, 0, v_a_1319_);
lean_closure_set(v___f_1342_, 1, v___x_1341_);
lean_closure_set(v___f_1342_, 2, v_iters_1322_);
v___x_1343_ = l_IO_lazyPure___redArg(v___f_1342_);
v_a_1344_ = lean_ctor_get(v___x_1343_, 0);
lean_inc(v_a_1344_);
lean_dec_ref(v___x_1343_);
v___x_1345_ = lean_io_mono_nanos_now();
v___x_1346_ = lean_uint32_of_nat(v_iters_1322_);
v___x_1347_ = lean_uint32_mul(v___x_1346_, v_expected_1321_);
v___x_1348_ = lean_uint32_add(v___x_1340_, v___x_1347_);
v___x_1349_ = ((lean_object*)(lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00__private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotBankHarness_benchEager_spec__0_spec__0___redArg___closed__1));
v___x_1350_ = lean_unbox_uint32(v_a_1344_);
lean_inc_ref(v_name_1335_);
v___x_1351_ = lp_competition_R24DotBankHarness_checkWord(v_name_1335_, v___x_1349_, v___x_1350_, v___x_1348_);
if (lean_obj_tag(v___x_1351_) == 0)
{
lean_object* v___x_1352_; lean_object* v_a_1353_; lean_object* v___x_1354_; uint32_t v___x_1355_; lean_object* v___x_1356_; 
lean_dec_ref_known(v___x_1351_, 1);
v___x_1352_ = l_IO_lazyPure___redArg(v___f_1332_);
v_a_1353_ = lean_ctor_get(v___x_1352_, 0);
lean_inc(v_a_1353_);
lean_dec_ref(v___x_1352_);
v___x_1354_ = ((lean_object*)(lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00__private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotBankHarness_benchEager_spec__0_spec__0___redArg___closed__2));
v___x_1355_ = lean_unbox_uint32(v_a_1353_);
lean_inc_ref(v_name_1335_);
v___x_1356_ = lp_competition_R24DotBankHarness_checkWord(v_name_1335_, v___x_1354_, v___x_1355_, v_expected_1321_);
if (lean_obj_tag(v___x_1356_) == 0)
{
lean_object* v___x_1357_; lean_object* v___x_1358_; uint32_t v___x_1359_; uint32_t v___x_1360_; lean_object* v___x_1361_; lean_object* v___x_1362_; 
lean_dec_ref_known(v___x_1356_, 1);
v___x_1357_ = lean_nat_sub(v___x_1345_, v___x_1339_);
lean_dec(v___x_1339_);
lean_dec(v___x_1345_);
lean_inc(v_iters_1322_);
lean_inc(v_work_1323_);
lean_inc(v_i_1326_);
v___x_1358_ = lean_alloc_ctor(0, 4, 12);
lean_ctor_set(v___x_1358_, 0, v_i_1326_);
lean_ctor_set(v___x_1358_, 1, v_work_1323_);
lean_ctor_set(v___x_1358_, 2, v_iters_1322_);
lean_ctor_set(v___x_1358_, 3, v___x_1357_);
v___x_1359_ = lean_unbox_uint32(v_a_1344_);
lean_dec(v_a_1344_);
lean_ctor_set_uint32(v___x_1358_, sizeof(void*)*4, v___x_1359_);
lean_ctor_set_uint32(v___x_1358_, sizeof(void*)*4 + 4, v___x_1348_);
v___x_1360_ = lean_unbox_uint32(v_a_1353_);
lean_dec(v_a_1353_);
lean_ctor_set_uint32(v___x_1358_, sizeof(void*)*4 + 8, v___x_1360_);
v___x_1361_ = lean_array_push(v_b_1325_, v___x_1358_);
v___x_1362_ = lean_nat_add(v_i_1326_, v_step_1329_);
lean_dec(v_i_1326_);
v_b_1325_ = v___x_1361_;
v_i_1326_ = v___x_1362_;
goto _start;
}
else
{
lean_object* v_a_1364_; lean_object* v___x_1366_; uint8_t v_isShared_1367_; uint8_t v_isSharedCheck_1371_; 
lean_dec(v_a_1353_);
lean_dec(v___x_1345_);
lean_dec(v_a_1344_);
lean_dec(v___x_1339_);
lean_dec(v_i_1326_);
lean_dec_ref(v_b_1325_);
lean_dec(v_work_1323_);
lean_dec(v_iters_1322_);
lean_dec_ref(v_c_1320_);
lean_dec_ref(v_a_1319_);
v_a_1364_ = lean_ctor_get(v___x_1356_, 0);
v_isSharedCheck_1371_ = !lean_is_exclusive(v___x_1356_);
if (v_isSharedCheck_1371_ == 0)
{
v___x_1366_ = v___x_1356_;
v_isShared_1367_ = v_isSharedCheck_1371_;
goto v_resetjp_1365_;
}
else
{
lean_inc(v_a_1364_);
lean_dec(v___x_1356_);
v___x_1366_ = lean_box(0);
v_isShared_1367_ = v_isSharedCheck_1371_;
goto v_resetjp_1365_;
}
v_resetjp_1365_:
{
lean_object* v___x_1369_; 
if (v_isShared_1367_ == 0)
{
v___x_1369_ = v___x_1366_;
goto v_reusejp_1368_;
}
else
{
lean_object* v_reuseFailAlloc_1370_; 
v_reuseFailAlloc_1370_ = lean_alloc_ctor(1, 1, 0);
lean_ctor_set(v_reuseFailAlloc_1370_, 0, v_a_1364_);
v___x_1369_ = v_reuseFailAlloc_1370_;
goto v_reusejp_1368_;
}
v_reusejp_1368_:
{
return v___x_1369_;
}
}
}
}
else
{
lean_object* v_a_1372_; lean_object* v___x_1374_; uint8_t v_isShared_1375_; uint8_t v_isSharedCheck_1379_; 
lean_dec(v___x_1345_);
lean_dec(v_a_1344_);
lean_dec(v___x_1339_);
lean_dec_ref(v___f_1332_);
lean_dec(v_i_1326_);
lean_dec_ref(v_b_1325_);
lean_dec(v_work_1323_);
lean_dec(v_iters_1322_);
lean_dec_ref(v_c_1320_);
lean_dec_ref(v_a_1319_);
v_a_1372_ = lean_ctor_get(v___x_1351_, 0);
v_isSharedCheck_1379_ = !lean_is_exclusive(v___x_1351_);
if (v_isSharedCheck_1379_ == 0)
{
v___x_1374_ = v___x_1351_;
v_isShared_1375_ = v_isSharedCheck_1379_;
goto v_resetjp_1373_;
}
else
{
lean_inc(v_a_1372_);
lean_dec(v___x_1351_);
v___x_1374_ = lean_box(0);
v_isShared_1375_ = v_isSharedCheck_1379_;
goto v_resetjp_1373_;
}
v_resetjp_1373_:
{
lean_object* v___x_1377_; 
if (v_isShared_1375_ == 0)
{
v___x_1377_ = v___x_1374_;
goto v_reusejp_1376_;
}
else
{
lean_object* v_reuseFailAlloc_1378_; 
v_reuseFailAlloc_1378_ = lean_alloc_ctor(1, 1, 0);
lean_ctor_set(v_reuseFailAlloc_1378_, 0, v_a_1372_);
v___x_1377_ = v_reuseFailAlloc_1378_;
goto v_reusejp_1376_;
}
v_reusejp_1376_:
{
return v___x_1377_;
}
}
}
}
else
{
lean_object* v_a_1380_; lean_object* v___x_1382_; uint8_t v_isShared_1383_; uint8_t v_isSharedCheck_1387_; 
lean_dec_ref(v___f_1332_);
lean_dec(v_i_1326_);
lean_dec_ref(v_b_1325_);
lean_dec(v_work_1323_);
lean_dec(v_iters_1322_);
lean_dec_ref(v_c_1320_);
lean_dec_ref(v_a_1319_);
v_a_1380_ = lean_ctor_get(v___x_1338_, 0);
v_isSharedCheck_1387_ = !lean_is_exclusive(v___x_1338_);
if (v_isSharedCheck_1387_ == 0)
{
v___x_1382_ = v___x_1338_;
v_isShared_1383_ = v_isSharedCheck_1387_;
goto v_resetjp_1381_;
}
else
{
lean_inc(v_a_1380_);
lean_dec(v___x_1338_);
v___x_1382_ = lean_box(0);
v_isShared_1383_ = v_isSharedCheck_1387_;
goto v_resetjp_1381_;
}
v_resetjp_1381_:
{
lean_object* v___x_1385_; 
if (v_isShared_1383_ == 0)
{
v___x_1385_ = v___x_1382_;
goto v_reusejp_1384_;
}
else
{
lean_object* v_reuseFailAlloc_1386_; 
v_reuseFailAlloc_1386_ = lean_alloc_ctor(1, 1, 0);
lean_ctor_set(v_reuseFailAlloc_1386_, 0, v_a_1380_);
v___x_1385_ = v_reuseFailAlloc_1386_;
goto v_reusejp_1384_;
}
v_reusejp_1384_:
{
return v___x_1385_;
}
}
}
}
}
}
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00__private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotBankHarness_benchEager_spec__0_spec__0___redArg___boxed(lean_object* v_a_1388_, lean_object* v_c_1389_, lean_object* v_expected_1390_, lean_object* v_iters_1391_, lean_object* v_work_1392_, lean_object* v_range_1393_, lean_object* v_b_1394_, lean_object* v_i_1395_, lean_object* v___y_1396_){
_start:
{
uint32_t v_expected_boxed_1397_; lean_object* v_res_1398_; 
v_expected_boxed_1397_ = lean_unbox_uint32(v_expected_1390_);
lean_dec(v_expected_1390_);
v_res_1398_ = lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00__private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotBankHarness_benchEager_spec__0_spec__0___redArg(v_a_1388_, v_c_1389_, v_expected_boxed_1397_, v_iters_1391_, v_work_1392_, v_range_1393_, v_b_1394_, v_i_1395_);
lean_dec_ref(v_range_1393_);
return v_res_1398_;
}
}
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotBankHarness_benchEager_spec__0___redArg(lean_object* v_a_1399_, lean_object* v_c_1400_, uint32_t v_expected_1401_, lean_object* v_iters_1402_, lean_object* v_work_1403_, lean_object* v_range_1404_, lean_object* v_b_1405_, lean_object* v_i_1406_){
_start:
{
lean_object* v_stop_1408_; lean_object* v_step_1409_; uint8_t v___x_1410_; 
v_stop_1408_ = lean_ctor_get(v_range_1404_, 1);
v_step_1409_ = lean_ctor_get(v_range_1404_, 2);
v___x_1410_ = lean_nat_dec_lt(v_i_1406_, v_stop_1408_);
if (v___x_1410_ == 0)
{
lean_object* v___x_1411_; 
lean_dec(v_i_1406_);
lean_dec(v_work_1403_);
lean_dec(v_iters_1402_);
lean_dec_ref(v_c_1400_);
lean_dec_ref(v_a_1399_);
v___x_1411_ = lean_alloc_ctor(0, 1, 0);
lean_ctor_set(v___x_1411_, 0, v_b_1405_);
return v___x_1411_;
}
else
{
lean_object* v___f_1412_; lean_object* v___x_1413_; lean_object* v_a_1414_; lean_object* v_name_1415_; lean_object* v___x_1416_; uint32_t v___x_1417_; lean_object* v___x_1418_; 
lean_inc_ref(v_a_1399_);
v___f_1412_ = lean_alloc_closure((void*)(lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotBankHarness_benchEager_spec__0___redArg___lam__0___boxed), 2, 1);
lean_closure_set(v___f_1412_, 0, v_a_1399_);
lean_inc_ref(v___f_1412_);
v___x_1413_ = l_IO_lazyPure___redArg(v___f_1412_);
v_a_1414_ = lean_ctor_get(v___x_1413_, 0);
lean_inc(v_a_1414_);
lean_dec_ref(v___x_1413_);
v_name_1415_ = lean_ctor_get(v_c_1400_, 0);
v___x_1416_ = ((lean_object*)(lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00__private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotBankHarness_benchEager_spec__0_spec__0___redArg___closed__0));
v___x_1417_ = lean_unbox_uint32(v_a_1414_);
lean_dec(v_a_1414_);
lean_inc_ref(v_name_1415_);
v___x_1418_ = lp_competition_R24DotBankHarness_checkWord(v_name_1415_, v___x_1416_, v___x_1417_, v_expected_1401_);
if (lean_obj_tag(v___x_1418_) == 0)
{
lean_object* v___x_1419_; uint32_t v___x_1420_; lean_object* v___x_1421_; lean_object* v___f_1422_; lean_object* v___x_1423_; lean_object* v_a_1424_; lean_object* v___x_1425_; uint32_t v___x_1426_; uint32_t v___x_1427_; uint32_t v___x_1428_; lean_object* v___x_1429_; uint32_t v___x_1430_; lean_object* v___x_1431_; 
lean_dec_ref_known(v___x_1418_, 1);
v___x_1419_ = lean_io_mono_nanos_now();
v___x_1420_ = lp_competition_R24DotBankHarness_seed(v_i_1406_);
v___x_1421_ = lean_box_uint32(v___x_1420_);
lean_inc(v_iters_1402_);
lean_inc_ref(v_a_1399_);
v___f_1422_ = lean_alloc_closure((void*)(lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotBankHarness_benchEager_spec__0___redArg___lam__1___boxed), 4, 3);
lean_closure_set(v___f_1422_, 0, v_a_1399_);
lean_closure_set(v___f_1422_, 1, v___x_1421_);
lean_closure_set(v___f_1422_, 2, v_iters_1402_);
v___x_1423_ = l_IO_lazyPure___redArg(v___f_1422_);
v_a_1424_ = lean_ctor_get(v___x_1423_, 0);
lean_inc(v_a_1424_);
lean_dec_ref(v___x_1423_);
v___x_1425_ = lean_io_mono_nanos_now();
v___x_1426_ = lean_uint32_of_nat(v_iters_1402_);
v___x_1427_ = lean_uint32_mul(v___x_1426_, v_expected_1401_);
v___x_1428_ = lean_uint32_add(v___x_1420_, v___x_1427_);
v___x_1429_ = ((lean_object*)(lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00__private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotBankHarness_benchEager_spec__0_spec__0___redArg___closed__1));
v___x_1430_ = lean_unbox_uint32(v_a_1424_);
lean_inc_ref(v_name_1415_);
v___x_1431_ = lp_competition_R24DotBankHarness_checkWord(v_name_1415_, v___x_1429_, v___x_1430_, v___x_1428_);
if (lean_obj_tag(v___x_1431_) == 0)
{
lean_object* v___x_1432_; lean_object* v_a_1433_; lean_object* v___x_1434_; uint32_t v___x_1435_; lean_object* v___x_1436_; 
lean_dec_ref_known(v___x_1431_, 1);
v___x_1432_ = l_IO_lazyPure___redArg(v___f_1412_);
v_a_1433_ = lean_ctor_get(v___x_1432_, 0);
lean_inc(v_a_1433_);
lean_dec_ref(v___x_1432_);
v___x_1434_ = ((lean_object*)(lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00__private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotBankHarness_benchEager_spec__0_spec__0___redArg___closed__2));
v___x_1435_ = lean_unbox_uint32(v_a_1433_);
lean_inc_ref(v_name_1415_);
v___x_1436_ = lp_competition_R24DotBankHarness_checkWord(v_name_1415_, v___x_1434_, v___x_1435_, v_expected_1401_);
if (lean_obj_tag(v___x_1436_) == 0)
{
lean_object* v___x_1437_; lean_object* v___x_1438_; uint32_t v___x_1439_; uint32_t v___x_1440_; lean_object* v___x_1441_; lean_object* v___x_1442_; lean_object* v___x_1443_; 
lean_dec_ref_known(v___x_1436_, 1);
v___x_1437_ = lean_nat_sub(v___x_1425_, v___x_1419_);
lean_dec(v___x_1419_);
lean_dec(v___x_1425_);
lean_inc(v_iters_1402_);
lean_inc(v_work_1403_);
lean_inc(v_i_1406_);
v___x_1438_ = lean_alloc_ctor(0, 4, 12);
lean_ctor_set(v___x_1438_, 0, v_i_1406_);
lean_ctor_set(v___x_1438_, 1, v_work_1403_);
lean_ctor_set(v___x_1438_, 2, v_iters_1402_);
lean_ctor_set(v___x_1438_, 3, v___x_1437_);
v___x_1439_ = lean_unbox_uint32(v_a_1424_);
lean_dec(v_a_1424_);
lean_ctor_set_uint32(v___x_1438_, sizeof(void*)*4, v___x_1439_);
lean_ctor_set_uint32(v___x_1438_, sizeof(void*)*4 + 4, v___x_1428_);
v___x_1440_ = lean_unbox_uint32(v_a_1433_);
lean_dec(v_a_1433_);
lean_ctor_set_uint32(v___x_1438_, sizeof(void*)*4 + 8, v___x_1440_);
v___x_1441_ = lean_array_push(v_b_1405_, v___x_1438_);
v___x_1442_ = lean_nat_add(v_i_1406_, v_step_1409_);
lean_dec(v_i_1406_);
v___x_1443_ = lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00__private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotBankHarness_benchEager_spec__0_spec__0___redArg(v_a_1399_, v_c_1400_, v_expected_1401_, v_iters_1402_, v_work_1403_, v_range_1404_, v___x_1441_, v___x_1442_);
return v___x_1443_;
}
else
{
lean_object* v_a_1444_; lean_object* v___x_1446_; uint8_t v_isShared_1447_; uint8_t v_isSharedCheck_1451_; 
lean_dec(v_a_1433_);
lean_dec(v___x_1425_);
lean_dec(v_a_1424_);
lean_dec(v___x_1419_);
lean_dec(v_i_1406_);
lean_dec_ref(v_b_1405_);
lean_dec(v_work_1403_);
lean_dec(v_iters_1402_);
lean_dec_ref(v_c_1400_);
lean_dec_ref(v_a_1399_);
v_a_1444_ = lean_ctor_get(v___x_1436_, 0);
v_isSharedCheck_1451_ = !lean_is_exclusive(v___x_1436_);
if (v_isSharedCheck_1451_ == 0)
{
v___x_1446_ = v___x_1436_;
v_isShared_1447_ = v_isSharedCheck_1451_;
goto v_resetjp_1445_;
}
else
{
lean_inc(v_a_1444_);
lean_dec(v___x_1436_);
v___x_1446_ = lean_box(0);
v_isShared_1447_ = v_isSharedCheck_1451_;
goto v_resetjp_1445_;
}
v_resetjp_1445_:
{
lean_object* v___x_1449_; 
if (v_isShared_1447_ == 0)
{
v___x_1449_ = v___x_1446_;
goto v_reusejp_1448_;
}
else
{
lean_object* v_reuseFailAlloc_1450_; 
v_reuseFailAlloc_1450_ = lean_alloc_ctor(1, 1, 0);
lean_ctor_set(v_reuseFailAlloc_1450_, 0, v_a_1444_);
v___x_1449_ = v_reuseFailAlloc_1450_;
goto v_reusejp_1448_;
}
v_reusejp_1448_:
{
return v___x_1449_;
}
}
}
}
else
{
lean_object* v_a_1452_; lean_object* v___x_1454_; uint8_t v_isShared_1455_; uint8_t v_isSharedCheck_1459_; 
lean_dec(v___x_1425_);
lean_dec(v_a_1424_);
lean_dec(v___x_1419_);
lean_dec_ref(v___f_1412_);
lean_dec(v_i_1406_);
lean_dec_ref(v_b_1405_);
lean_dec(v_work_1403_);
lean_dec(v_iters_1402_);
lean_dec_ref(v_c_1400_);
lean_dec_ref(v_a_1399_);
v_a_1452_ = lean_ctor_get(v___x_1431_, 0);
v_isSharedCheck_1459_ = !lean_is_exclusive(v___x_1431_);
if (v_isSharedCheck_1459_ == 0)
{
v___x_1454_ = v___x_1431_;
v_isShared_1455_ = v_isSharedCheck_1459_;
goto v_resetjp_1453_;
}
else
{
lean_inc(v_a_1452_);
lean_dec(v___x_1431_);
v___x_1454_ = lean_box(0);
v_isShared_1455_ = v_isSharedCheck_1459_;
goto v_resetjp_1453_;
}
v_resetjp_1453_:
{
lean_object* v___x_1457_; 
if (v_isShared_1455_ == 0)
{
v___x_1457_ = v___x_1454_;
goto v_reusejp_1456_;
}
else
{
lean_object* v_reuseFailAlloc_1458_; 
v_reuseFailAlloc_1458_ = lean_alloc_ctor(1, 1, 0);
lean_ctor_set(v_reuseFailAlloc_1458_, 0, v_a_1452_);
v___x_1457_ = v_reuseFailAlloc_1458_;
goto v_reusejp_1456_;
}
v_reusejp_1456_:
{
return v___x_1457_;
}
}
}
}
else
{
lean_object* v_a_1460_; lean_object* v___x_1462_; uint8_t v_isShared_1463_; uint8_t v_isSharedCheck_1467_; 
lean_dec_ref(v___f_1412_);
lean_dec(v_i_1406_);
lean_dec_ref(v_b_1405_);
lean_dec(v_work_1403_);
lean_dec(v_iters_1402_);
lean_dec_ref(v_c_1400_);
lean_dec_ref(v_a_1399_);
v_a_1460_ = lean_ctor_get(v___x_1418_, 0);
v_isSharedCheck_1467_ = !lean_is_exclusive(v___x_1418_);
if (v_isSharedCheck_1467_ == 0)
{
v___x_1462_ = v___x_1418_;
v_isShared_1463_ = v_isSharedCheck_1467_;
goto v_resetjp_1461_;
}
else
{
lean_inc(v_a_1460_);
lean_dec(v___x_1418_);
v___x_1462_ = lean_box(0);
v_isShared_1463_ = v_isSharedCheck_1467_;
goto v_resetjp_1461_;
}
v_resetjp_1461_:
{
lean_object* v___x_1465_; 
if (v_isShared_1463_ == 0)
{
v___x_1465_ = v___x_1462_;
goto v_reusejp_1464_;
}
else
{
lean_object* v_reuseFailAlloc_1466_; 
v_reuseFailAlloc_1466_ = lean_alloc_ctor(1, 1, 0);
lean_ctor_set(v_reuseFailAlloc_1466_, 0, v_a_1460_);
v___x_1465_ = v_reuseFailAlloc_1466_;
goto v_reusejp_1464_;
}
v_reusejp_1464_:
{
return v___x_1465_;
}
}
}
}
}
}
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotBankHarness_benchEager_spec__0___redArg___boxed(lean_object* v_a_1468_, lean_object* v_c_1469_, lean_object* v_expected_1470_, lean_object* v_iters_1471_, lean_object* v_work_1472_, lean_object* v_range_1473_, lean_object* v_b_1474_, lean_object* v_i_1475_, lean_object* v___y_1476_){
_start:
{
uint32_t v_expected_boxed_1477_; lean_object* v_res_1478_; 
v_expected_boxed_1477_ = lean_unbox_uint32(v_expected_1470_);
lean_dec(v_expected_1470_);
v_res_1478_ = lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotBankHarness_benchEager_spec__0___redArg(v_a_1468_, v_c_1469_, v_expected_boxed_1477_, v_iters_1471_, v_work_1472_, v_range_1473_, v_b_1474_, v_i_1475_);
lean_dec_ref(v_range_1473_);
return v_res_1478_;
}
}
LEAN_EXPORT lean_object* lp_competition_R24DotBankHarness_benchEager(lean_object* v_c_1480_, lean_object* v_a_1481_, lean_object* v_b_1482_, lean_object* v_macs_1483_, uint32_t v_expected_1484_){
_start:
{
lean_object* v___f_1486_; lean_object* v___x_1487_; lean_object* v_a_1488_; lean_object* v___x_1489_; lean_object* v_a_1490_; lean_object* v_inner_1491_; lean_object* v_rows_1492_; lean_object* v_cols_1493_; lean_object* v___x_1494_; lean_object* v_work_1495_; lean_object* v_iters_1496_; lean_object* v___x_1497_; lean_object* v___x_1498_; lean_object* v___x_1499_; lean_object* v___x_1500_; 
v___f_1486_ = lean_alloc_closure((void*)(lp_competition_R24DotBankHarness_benchExact___lam__0), 3, 2);
lean_closure_set(v___f_1486_, 0, v_a_1481_);
lean_closure_set(v___f_1486_, 1, v_b_1482_);
v___x_1487_ = l_IO_lazyPure___redArg(v___f_1486_);
v_a_1488_ = lean_ctor_get(v___x_1487_, 0);
lean_inc(v_a_1488_);
lean_dec_ref(v___x_1487_);
v___x_1489_ = lp_competition_R24DotBankHarness_benchExact___lam__1();
v_a_1490_ = lean_ctor_get(v___x_1489_, 0);
lean_inc(v_a_1490_);
lean_dec_ref(v___x_1489_);
v_inner_1491_ = lean_ctor_get(v_c_1480_, 2);
v_rows_1492_ = lean_ctor_get(v_c_1480_, 3);
v_cols_1493_ = lean_ctor_get(v_c_1480_, 4);
v___x_1494_ = lean_nat_mul(v_rows_1492_, v_cols_1493_);
v_work_1495_ = lean_nat_mul(v___x_1494_, v_inner_1491_);
lean_dec(v___x_1494_);
v_iters_1496_ = lp_competition_R24DotBankHarness_repeats(v_macs_1483_, v_work_1495_);
v___x_1497_ = lean_unsigned_to_nat(0u);
v___x_1498_ = ((lean_object*)(lp_competition_R24DotBankHarness_benchExact___closed__0));
v___x_1499_ = ((lean_object*)(lp_competition_R24DotBankHarness_benchExact___closed__1));
lean_inc_ref(v_c_1480_);
v___x_1500_ = lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotBankHarness_benchEager_spec__0___redArg(v_a_1488_, v_c_1480_, v_expected_1484_, v_iters_1496_, v_work_1495_, v___x_1499_, v___x_1498_, v___x_1497_);
if (lean_obj_tag(v___x_1500_) == 0)
{
lean_object* v_a_1501_; lean_object* v___x_1502_; lean_object* v_a_1503_; lean_object* v___x_1504_; lean_object* v___x_1505_; lean_object* v___x_1506_; 
v_a_1501_ = lean_ctor_get(v___x_1500_, 0);
lean_inc(v_a_1501_);
lean_dec_ref_known(v___x_1500_, 1);
v___x_1502_ = lp_competition_R24DotBankHarness_benchExact___lam__1();
v_a_1503_ = lean_ctor_get(v___x_1502_, 0);
lean_inc(v_a_1503_);
lean_dec_ref(v___x_1502_);
v___x_1504_ = ((lean_object*)(lp_competition_R24DotBankHarness_benchEager___closed__0));
v___x_1505_ = lean_nat_sub(v_a_1503_, v_a_1490_);
lean_dec(v_a_1490_);
lean_dec(v_a_1503_);
v___x_1506_ = lp_competition_R24DotBankHarness_emit(v_c_1480_, v___x_1504_, v___x_1505_, v_a_1501_);
lean_dec(v_a_1501_);
lean_dec_ref(v_c_1480_);
return v___x_1506_;
}
else
{
lean_object* v_a_1507_; lean_object* v___x_1509_; uint8_t v_isShared_1510_; uint8_t v_isSharedCheck_1514_; 
lean_dec(v_a_1490_);
lean_dec_ref(v_c_1480_);
v_a_1507_ = lean_ctor_get(v___x_1500_, 0);
v_isSharedCheck_1514_ = !lean_is_exclusive(v___x_1500_);
if (v_isSharedCheck_1514_ == 0)
{
v___x_1509_ = v___x_1500_;
v_isShared_1510_ = v_isSharedCheck_1514_;
goto v_resetjp_1508_;
}
else
{
lean_inc(v_a_1507_);
lean_dec(v___x_1500_);
v___x_1509_ = lean_box(0);
v_isShared_1510_ = v_isSharedCheck_1514_;
goto v_resetjp_1508_;
}
v_resetjp_1508_:
{
lean_object* v___x_1512_; 
if (v_isShared_1510_ == 0)
{
v___x_1512_ = v___x_1509_;
goto v_reusejp_1511_;
}
else
{
lean_object* v_reuseFailAlloc_1513_; 
v_reuseFailAlloc_1513_ = lean_alloc_ctor(1, 1, 0);
lean_ctor_set(v_reuseFailAlloc_1513_, 0, v_a_1507_);
v___x_1512_ = v_reuseFailAlloc_1513_;
goto v_reusejp_1511_;
}
v_reusejp_1511_:
{
return v___x_1512_;
}
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_R24DotBankHarness_benchEager___boxed(lean_object* v_c_1515_, lean_object* v_a_1516_, lean_object* v_b_1517_, lean_object* v_macs_1518_, lean_object* v_expected_1519_, lean_object* v_a_1520_){
_start:
{
uint32_t v_expected_boxed_1521_; lean_object* v_res_1522_; 
v_expected_boxed_1521_ = lean_unbox_uint32(v_expected_1519_);
lean_dec(v_expected_1519_);
v_res_1522_ = lp_competition_R24DotBankHarness_benchEager(v_c_1515_, v_a_1516_, v_b_1517_, v_macs_1518_, v_expected_boxed_1521_);
lean_dec(v_macs_1518_);
return v_res_1522_;
}
}
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotBankHarness_benchEager_spec__0(lean_object* v_a_1523_, lean_object* v_c_1524_, uint32_t v_expected_1525_, lean_object* v_iters_1526_, lean_object* v_work_1527_, lean_object* v_range_1528_, lean_object* v_b_1529_, lean_object* v_i_1530_, lean_object* v_hs_1531_, lean_object* v_hl_1532_){
_start:
{
lean_object* v___x_1534_; 
v___x_1534_ = lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotBankHarness_benchEager_spec__0___redArg(v_a_1523_, v_c_1524_, v_expected_1525_, v_iters_1526_, v_work_1527_, v_range_1528_, v_b_1529_, v_i_1530_);
return v___x_1534_;
}
}
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotBankHarness_benchEager_spec__0___boxed(lean_object* v_a_1535_, lean_object* v_c_1536_, lean_object* v_expected_1537_, lean_object* v_iters_1538_, lean_object* v_work_1539_, lean_object* v_range_1540_, lean_object* v_b_1541_, lean_object* v_i_1542_, lean_object* v_hs_1543_, lean_object* v_hl_1544_, lean_object* v___y_1545_){
_start:
{
uint32_t v_expected_boxed_1546_; lean_object* v_res_1547_; 
v_expected_boxed_1546_ = lean_unbox_uint32(v_expected_1537_);
lean_dec(v_expected_1537_);
v_res_1547_ = lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotBankHarness_benchEager_spec__0(v_a_1535_, v_c_1536_, v_expected_boxed_1546_, v_iters_1538_, v_work_1539_, v_range_1540_, v_b_1541_, v_i_1542_, v_hs_1543_, v_hl_1544_);
lean_dec_ref(v_range_1540_);
return v_res_1547_;
}
}
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00__private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotBankHarness_benchEager_spec__0_spec__0(lean_object* v_a_1548_, lean_object* v_c_1549_, uint32_t v_expected_1550_, lean_object* v_iters_1551_, lean_object* v_work_1552_, lean_object* v_range_1553_, lean_object* v_b_1554_, lean_object* v_i_1555_, lean_object* v_hs_1556_, lean_object* v_hl_1557_){
_start:
{
lean_object* v___x_1559_; 
v___x_1559_ = lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00__private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotBankHarness_benchEager_spec__0_spec__0___redArg(v_a_1548_, v_c_1549_, v_expected_1550_, v_iters_1551_, v_work_1552_, v_range_1553_, v_b_1554_, v_i_1555_);
return v___x_1559_;
}
}
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00__private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotBankHarness_benchEager_spec__0_spec__0___boxed(lean_object* v_a_1560_, lean_object* v_c_1561_, lean_object* v_expected_1562_, lean_object* v_iters_1563_, lean_object* v_work_1564_, lean_object* v_range_1565_, lean_object* v_b_1566_, lean_object* v_i_1567_, lean_object* v_hs_1568_, lean_object* v_hl_1569_, lean_object* v___y_1570_){
_start:
{
uint32_t v_expected_boxed_1571_; lean_object* v_res_1572_; 
v_expected_boxed_1571_ = lean_unbox_uint32(v_expected_1562_);
lean_dec(v_expected_1562_);
v_res_1572_ = lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00__private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotBankHarness_benchEager_spec__0_spec__0(v_a_1560_, v_c_1561_, v_expected_boxed_1571_, v_iters_1563_, v_work_1564_, v_range_1565_, v_b_1566_, v_i_1567_, v_hs_1568_, v_hl_1569_);
lean_dec_ref(v_range_1565_);
return v_res_1572_;
}
}
LEAN_EXPORT uint32_t lp_competition_R24DotBankHarness_passLazy(lean_object* v_p_1573_, uint32_t v_s_1574_, lean_object* v_iters_1575_){
_start:
{
lean_object* v_zero_1576_; uint8_t v_isZero_1577_; 
v_zero_1576_ = lean_unsigned_to_nat(0u);
v_isZero_1577_ = lean_nat_dec_eq(v_iters_1575_, v_zero_1576_);
if (v_isZero_1577_ == 1)
{
lean_dec(v_iters_1575_);
lean_dec_ref(v_p_1573_);
return v_s_1574_;
}
else
{
lean_object* v_one_1578_; lean_object* v_n_1579_; lean_object* v_p_1580_; lean_object* v_fst_1581_; lean_object* v_snd_1582_; lean_object* v_out_1583_; uint32_t v_word_1584_; uint32_t v___x_1585_; 
v_one_1578_ = lean_unsigned_to_nat(1u);
v_n_1579_ = lean_nat_sub(v_iters_1575_, v_one_1578_);
lean_dec(v_iters_1575_);
v_p_1580_ = lp_competition_R24DotBarrier_touchBank(v_n_1579_, v_p_1573_);
v_fst_1581_ = lean_ctor_get(v_p_1580_, 0);
lean_inc(v_fst_1581_);
v_snd_1582_ = lean_ctor_get(v_p_1580_, 1);
lean_inc(v_snd_1582_);
v_out_1583_ = lp_competition_Submission_R24GenericDotBank_lazyBank(v_fst_1581_, v_snd_1582_);
lean_dec(v_snd_1582_);
lean_dec(v_fst_1581_);
v_word_1584_ = lp_competition_R24DotBankHarness_hashAll(v_out_1583_);
lean_dec_ref(v_out_1583_);
v___x_1585_ = lean_uint32_add(v_s_1574_, v_word_1584_);
v_p_1573_ = v_p_1580_;
v_s_1574_ = v___x_1585_;
v_iters_1575_ = v_n_1579_;
goto _start;
}
}
}
LEAN_EXPORT lean_object* lp_competition_R24DotBankHarness_passLazy___boxed(lean_object* v_p_1587_, lean_object* v_s_1588_, lean_object* v_iters_1589_){
_start:
{
uint32_t v_s_boxed_1590_; uint32_t v_res_1591_; lean_object* v_r_1592_; 
v_s_boxed_1590_ = lean_unbox_uint32(v_s_1588_);
lean_dec(v_s_1588_);
v_res_1591_ = lp_competition_R24DotBankHarness_passLazy(v_p_1587_, v_s_boxed_1590_, v_iters_1589_);
v_r_1592_ = lean_box_uint32(v_res_1591_);
return v_r_1592_;
}
}
LEAN_EXPORT uint32_t lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotBankHarness_benchLazy_spec__0___redArg___lam__0(lean_object* v_a_1593_, lean_object* v_x_1594_){
_start:
{
lean_object* v_fst_1595_; lean_object* v_snd_1596_; lean_object* v___x_1597_; uint32_t v___x_1598_; 
v_fst_1595_ = lean_ctor_get(v_a_1593_, 0);
v_snd_1596_ = lean_ctor_get(v_a_1593_, 1);
v___x_1597_ = lp_competition_Submission_R24GenericDotBank_lazyBank(v_fst_1595_, v_snd_1596_);
v___x_1598_ = lp_competition_R24DotBankHarness_hashAll(v___x_1597_);
lean_dec_ref(v___x_1597_);
return v___x_1598_;
}
}
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotBankHarness_benchLazy_spec__0___redArg___lam__0___boxed(lean_object* v_a_1599_, lean_object* v_x_1600_){
_start:
{
uint32_t v_res_1601_; lean_object* v_r_1602_; 
v_res_1601_ = lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotBankHarness_benchLazy_spec__0___redArg___lam__0(v_a_1599_, v_x_1600_);
lean_dec_ref(v_a_1599_);
v_r_1602_ = lean_box_uint32(v_res_1601_);
return v_r_1602_;
}
}
LEAN_EXPORT uint32_t lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotBankHarness_benchLazy_spec__0___redArg___lam__1(lean_object* v_a_1603_, uint32_t v___x_1604_, lean_object* v_iters_1605_, lean_object* v_x_1606_){
_start:
{
uint32_t v___x_1607_; 
v___x_1607_ = lp_competition_R24DotBankHarness_passLazy(v_a_1603_, v___x_1604_, v_iters_1605_);
return v___x_1607_;
}
}
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotBankHarness_benchLazy_spec__0___redArg___lam__1___boxed(lean_object* v_a_1608_, lean_object* v___x_1609_, lean_object* v_iters_1610_, lean_object* v_x_1611_){
_start:
{
uint32_t v___x_1540__boxed_1612_; uint32_t v_res_1613_; lean_object* v_r_1614_; 
v___x_1540__boxed_1612_ = lean_unbox_uint32(v___x_1609_);
lean_dec(v___x_1609_);
v_res_1613_ = lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotBankHarness_benchLazy_spec__0___redArg___lam__1(v_a_1608_, v___x_1540__boxed_1612_, v_iters_1610_, v_x_1611_);
v_r_1614_ = lean_box_uint32(v_res_1613_);
return v_r_1614_;
}
}
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00__private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotBankHarness_benchLazy_spec__0_spec__0___redArg(lean_object* v_a_1618_, lean_object* v_c_1619_, uint32_t v_expected_1620_, lean_object* v_iters_1621_, lean_object* v_work_1622_, lean_object* v_range_1623_, lean_object* v_b_1624_, lean_object* v_i_1625_){
_start:
{
lean_object* v_stop_1627_; lean_object* v_step_1628_; uint8_t v___x_1629_; 
v_stop_1627_ = lean_ctor_get(v_range_1623_, 1);
v_step_1628_ = lean_ctor_get(v_range_1623_, 2);
v___x_1629_ = lean_nat_dec_lt(v_i_1625_, v_stop_1627_);
if (v___x_1629_ == 0)
{
lean_object* v___x_1630_; 
lean_dec(v_i_1625_);
lean_dec(v_work_1622_);
lean_dec(v_iters_1621_);
lean_dec_ref(v_c_1619_);
lean_dec_ref(v_a_1618_);
v___x_1630_ = lean_alloc_ctor(0, 1, 0);
lean_ctor_set(v___x_1630_, 0, v_b_1624_);
return v___x_1630_;
}
else
{
lean_object* v___f_1631_; lean_object* v___x_1632_; lean_object* v_a_1633_; lean_object* v_name_1634_; lean_object* v___x_1635_; uint32_t v___x_1636_; lean_object* v___x_1637_; 
lean_inc_ref(v_a_1618_);
v___f_1631_ = lean_alloc_closure((void*)(lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotBankHarness_benchLazy_spec__0___redArg___lam__0___boxed), 2, 1);
lean_closure_set(v___f_1631_, 0, v_a_1618_);
lean_inc_ref(v___f_1631_);
v___x_1632_ = l_IO_lazyPure___redArg(v___f_1631_);
v_a_1633_ = lean_ctor_get(v___x_1632_, 0);
lean_inc(v_a_1633_);
lean_dec_ref(v___x_1632_);
v_name_1634_ = lean_ctor_get(v_c_1619_, 0);
v___x_1635_ = ((lean_object*)(lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00__private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotBankHarness_benchLazy_spec__0_spec__0___redArg___closed__0));
v___x_1636_ = lean_unbox_uint32(v_a_1633_);
lean_dec(v_a_1633_);
lean_inc_ref(v_name_1634_);
v___x_1637_ = lp_competition_R24DotBankHarness_checkWord(v_name_1634_, v___x_1635_, v___x_1636_, v_expected_1620_);
if (lean_obj_tag(v___x_1637_) == 0)
{
lean_object* v___x_1638_; uint32_t v___x_1639_; lean_object* v___x_1640_; lean_object* v___f_1641_; lean_object* v___x_1642_; lean_object* v_a_1643_; lean_object* v___x_1644_; uint32_t v___x_1645_; uint32_t v___x_1646_; uint32_t v___x_1647_; lean_object* v___x_1648_; uint32_t v___x_1649_; lean_object* v___x_1650_; 
lean_dec_ref_known(v___x_1637_, 1);
v___x_1638_ = lean_io_mono_nanos_now();
v___x_1639_ = lp_competition_R24DotBankHarness_seed(v_i_1625_);
v___x_1640_ = lean_box_uint32(v___x_1639_);
lean_inc(v_iters_1621_);
lean_inc_ref(v_a_1618_);
v___f_1641_ = lean_alloc_closure((void*)(lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotBankHarness_benchLazy_spec__0___redArg___lam__1___boxed), 4, 3);
lean_closure_set(v___f_1641_, 0, v_a_1618_);
lean_closure_set(v___f_1641_, 1, v___x_1640_);
lean_closure_set(v___f_1641_, 2, v_iters_1621_);
v___x_1642_ = l_IO_lazyPure___redArg(v___f_1641_);
v_a_1643_ = lean_ctor_get(v___x_1642_, 0);
lean_inc(v_a_1643_);
lean_dec_ref(v___x_1642_);
v___x_1644_ = lean_io_mono_nanos_now();
v___x_1645_ = lean_uint32_of_nat(v_iters_1621_);
v___x_1646_ = lean_uint32_mul(v___x_1645_, v_expected_1620_);
v___x_1647_ = lean_uint32_add(v___x_1639_, v___x_1646_);
v___x_1648_ = ((lean_object*)(lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00__private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotBankHarness_benchLazy_spec__0_spec__0___redArg___closed__1));
v___x_1649_ = lean_unbox_uint32(v_a_1643_);
lean_inc_ref(v_name_1634_);
v___x_1650_ = lp_competition_R24DotBankHarness_checkWord(v_name_1634_, v___x_1648_, v___x_1649_, v___x_1647_);
if (lean_obj_tag(v___x_1650_) == 0)
{
lean_object* v___x_1651_; lean_object* v_a_1652_; lean_object* v___x_1653_; uint32_t v___x_1654_; lean_object* v___x_1655_; 
lean_dec_ref_known(v___x_1650_, 1);
v___x_1651_ = l_IO_lazyPure___redArg(v___f_1631_);
v_a_1652_ = lean_ctor_get(v___x_1651_, 0);
lean_inc(v_a_1652_);
lean_dec_ref(v___x_1651_);
v___x_1653_ = ((lean_object*)(lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00__private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotBankHarness_benchLazy_spec__0_spec__0___redArg___closed__2));
v___x_1654_ = lean_unbox_uint32(v_a_1652_);
lean_inc_ref(v_name_1634_);
v___x_1655_ = lp_competition_R24DotBankHarness_checkWord(v_name_1634_, v___x_1653_, v___x_1654_, v_expected_1620_);
if (lean_obj_tag(v___x_1655_) == 0)
{
lean_object* v___x_1656_; lean_object* v___x_1657_; uint32_t v___x_1658_; uint32_t v___x_1659_; lean_object* v___x_1660_; lean_object* v___x_1661_; 
lean_dec_ref_known(v___x_1655_, 1);
v___x_1656_ = lean_nat_sub(v___x_1644_, v___x_1638_);
lean_dec(v___x_1638_);
lean_dec(v___x_1644_);
lean_inc(v_iters_1621_);
lean_inc(v_work_1622_);
lean_inc(v_i_1625_);
v___x_1657_ = lean_alloc_ctor(0, 4, 12);
lean_ctor_set(v___x_1657_, 0, v_i_1625_);
lean_ctor_set(v___x_1657_, 1, v_work_1622_);
lean_ctor_set(v___x_1657_, 2, v_iters_1621_);
lean_ctor_set(v___x_1657_, 3, v___x_1656_);
v___x_1658_ = lean_unbox_uint32(v_a_1643_);
lean_dec(v_a_1643_);
lean_ctor_set_uint32(v___x_1657_, sizeof(void*)*4, v___x_1658_);
lean_ctor_set_uint32(v___x_1657_, sizeof(void*)*4 + 4, v___x_1647_);
v___x_1659_ = lean_unbox_uint32(v_a_1652_);
lean_dec(v_a_1652_);
lean_ctor_set_uint32(v___x_1657_, sizeof(void*)*4 + 8, v___x_1659_);
v___x_1660_ = lean_array_push(v_b_1624_, v___x_1657_);
v___x_1661_ = lean_nat_add(v_i_1625_, v_step_1628_);
lean_dec(v_i_1625_);
v_b_1624_ = v___x_1660_;
v_i_1625_ = v___x_1661_;
goto _start;
}
else
{
lean_object* v_a_1663_; lean_object* v___x_1665_; uint8_t v_isShared_1666_; uint8_t v_isSharedCheck_1670_; 
lean_dec(v_a_1652_);
lean_dec(v___x_1644_);
lean_dec(v_a_1643_);
lean_dec(v___x_1638_);
lean_dec(v_i_1625_);
lean_dec_ref(v_b_1624_);
lean_dec(v_work_1622_);
lean_dec(v_iters_1621_);
lean_dec_ref(v_c_1619_);
lean_dec_ref(v_a_1618_);
v_a_1663_ = lean_ctor_get(v___x_1655_, 0);
v_isSharedCheck_1670_ = !lean_is_exclusive(v___x_1655_);
if (v_isSharedCheck_1670_ == 0)
{
v___x_1665_ = v___x_1655_;
v_isShared_1666_ = v_isSharedCheck_1670_;
goto v_resetjp_1664_;
}
else
{
lean_inc(v_a_1663_);
lean_dec(v___x_1655_);
v___x_1665_ = lean_box(0);
v_isShared_1666_ = v_isSharedCheck_1670_;
goto v_resetjp_1664_;
}
v_resetjp_1664_:
{
lean_object* v___x_1668_; 
if (v_isShared_1666_ == 0)
{
v___x_1668_ = v___x_1665_;
goto v_reusejp_1667_;
}
else
{
lean_object* v_reuseFailAlloc_1669_; 
v_reuseFailAlloc_1669_ = lean_alloc_ctor(1, 1, 0);
lean_ctor_set(v_reuseFailAlloc_1669_, 0, v_a_1663_);
v___x_1668_ = v_reuseFailAlloc_1669_;
goto v_reusejp_1667_;
}
v_reusejp_1667_:
{
return v___x_1668_;
}
}
}
}
else
{
lean_object* v_a_1671_; lean_object* v___x_1673_; uint8_t v_isShared_1674_; uint8_t v_isSharedCheck_1678_; 
lean_dec(v___x_1644_);
lean_dec(v_a_1643_);
lean_dec(v___x_1638_);
lean_dec_ref(v___f_1631_);
lean_dec(v_i_1625_);
lean_dec_ref(v_b_1624_);
lean_dec(v_work_1622_);
lean_dec(v_iters_1621_);
lean_dec_ref(v_c_1619_);
lean_dec_ref(v_a_1618_);
v_a_1671_ = lean_ctor_get(v___x_1650_, 0);
v_isSharedCheck_1678_ = !lean_is_exclusive(v___x_1650_);
if (v_isSharedCheck_1678_ == 0)
{
v___x_1673_ = v___x_1650_;
v_isShared_1674_ = v_isSharedCheck_1678_;
goto v_resetjp_1672_;
}
else
{
lean_inc(v_a_1671_);
lean_dec(v___x_1650_);
v___x_1673_ = lean_box(0);
v_isShared_1674_ = v_isSharedCheck_1678_;
goto v_resetjp_1672_;
}
v_resetjp_1672_:
{
lean_object* v___x_1676_; 
if (v_isShared_1674_ == 0)
{
v___x_1676_ = v___x_1673_;
goto v_reusejp_1675_;
}
else
{
lean_object* v_reuseFailAlloc_1677_; 
v_reuseFailAlloc_1677_ = lean_alloc_ctor(1, 1, 0);
lean_ctor_set(v_reuseFailAlloc_1677_, 0, v_a_1671_);
v___x_1676_ = v_reuseFailAlloc_1677_;
goto v_reusejp_1675_;
}
v_reusejp_1675_:
{
return v___x_1676_;
}
}
}
}
else
{
lean_object* v_a_1679_; lean_object* v___x_1681_; uint8_t v_isShared_1682_; uint8_t v_isSharedCheck_1686_; 
lean_dec_ref(v___f_1631_);
lean_dec(v_i_1625_);
lean_dec_ref(v_b_1624_);
lean_dec(v_work_1622_);
lean_dec(v_iters_1621_);
lean_dec_ref(v_c_1619_);
lean_dec_ref(v_a_1618_);
v_a_1679_ = lean_ctor_get(v___x_1637_, 0);
v_isSharedCheck_1686_ = !lean_is_exclusive(v___x_1637_);
if (v_isSharedCheck_1686_ == 0)
{
v___x_1681_ = v___x_1637_;
v_isShared_1682_ = v_isSharedCheck_1686_;
goto v_resetjp_1680_;
}
else
{
lean_inc(v_a_1679_);
lean_dec(v___x_1637_);
v___x_1681_ = lean_box(0);
v_isShared_1682_ = v_isSharedCheck_1686_;
goto v_resetjp_1680_;
}
v_resetjp_1680_:
{
lean_object* v___x_1684_; 
if (v_isShared_1682_ == 0)
{
v___x_1684_ = v___x_1681_;
goto v_reusejp_1683_;
}
else
{
lean_object* v_reuseFailAlloc_1685_; 
v_reuseFailAlloc_1685_ = lean_alloc_ctor(1, 1, 0);
lean_ctor_set(v_reuseFailAlloc_1685_, 0, v_a_1679_);
v___x_1684_ = v_reuseFailAlloc_1685_;
goto v_reusejp_1683_;
}
v_reusejp_1683_:
{
return v___x_1684_;
}
}
}
}
}
}
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00__private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotBankHarness_benchLazy_spec__0_spec__0___redArg___boxed(lean_object* v_a_1687_, lean_object* v_c_1688_, lean_object* v_expected_1689_, lean_object* v_iters_1690_, lean_object* v_work_1691_, lean_object* v_range_1692_, lean_object* v_b_1693_, lean_object* v_i_1694_, lean_object* v___y_1695_){
_start:
{
uint32_t v_expected_boxed_1696_; lean_object* v_res_1697_; 
v_expected_boxed_1696_ = lean_unbox_uint32(v_expected_1689_);
lean_dec(v_expected_1689_);
v_res_1697_ = lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00__private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotBankHarness_benchLazy_spec__0_spec__0___redArg(v_a_1687_, v_c_1688_, v_expected_boxed_1696_, v_iters_1690_, v_work_1691_, v_range_1692_, v_b_1693_, v_i_1694_);
lean_dec_ref(v_range_1692_);
return v_res_1697_;
}
}
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotBankHarness_benchLazy_spec__0___redArg(lean_object* v_a_1698_, lean_object* v_c_1699_, uint32_t v_expected_1700_, lean_object* v_iters_1701_, lean_object* v_work_1702_, lean_object* v_range_1703_, lean_object* v_b_1704_, lean_object* v_i_1705_){
_start:
{
lean_object* v_stop_1707_; lean_object* v_step_1708_; uint8_t v___x_1709_; 
v_stop_1707_ = lean_ctor_get(v_range_1703_, 1);
v_step_1708_ = lean_ctor_get(v_range_1703_, 2);
v___x_1709_ = lean_nat_dec_lt(v_i_1705_, v_stop_1707_);
if (v___x_1709_ == 0)
{
lean_object* v___x_1710_; 
lean_dec(v_i_1705_);
lean_dec(v_work_1702_);
lean_dec(v_iters_1701_);
lean_dec_ref(v_c_1699_);
lean_dec_ref(v_a_1698_);
v___x_1710_ = lean_alloc_ctor(0, 1, 0);
lean_ctor_set(v___x_1710_, 0, v_b_1704_);
return v___x_1710_;
}
else
{
lean_object* v___f_1711_; lean_object* v___x_1712_; lean_object* v_a_1713_; lean_object* v_name_1714_; lean_object* v___x_1715_; uint32_t v___x_1716_; lean_object* v___x_1717_; 
lean_inc_ref(v_a_1698_);
v___f_1711_ = lean_alloc_closure((void*)(lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotBankHarness_benchLazy_spec__0___redArg___lam__0___boxed), 2, 1);
lean_closure_set(v___f_1711_, 0, v_a_1698_);
lean_inc_ref(v___f_1711_);
v___x_1712_ = l_IO_lazyPure___redArg(v___f_1711_);
v_a_1713_ = lean_ctor_get(v___x_1712_, 0);
lean_inc(v_a_1713_);
lean_dec_ref(v___x_1712_);
v_name_1714_ = lean_ctor_get(v_c_1699_, 0);
v___x_1715_ = ((lean_object*)(lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00__private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotBankHarness_benchLazy_spec__0_spec__0___redArg___closed__0));
v___x_1716_ = lean_unbox_uint32(v_a_1713_);
lean_dec(v_a_1713_);
lean_inc_ref(v_name_1714_);
v___x_1717_ = lp_competition_R24DotBankHarness_checkWord(v_name_1714_, v___x_1715_, v___x_1716_, v_expected_1700_);
if (lean_obj_tag(v___x_1717_) == 0)
{
lean_object* v___x_1718_; uint32_t v___x_1719_; lean_object* v___x_1720_; lean_object* v___f_1721_; lean_object* v___x_1722_; lean_object* v_a_1723_; lean_object* v___x_1724_; uint32_t v___x_1725_; uint32_t v___x_1726_; uint32_t v___x_1727_; lean_object* v___x_1728_; uint32_t v___x_1729_; lean_object* v___x_1730_; 
lean_dec_ref_known(v___x_1717_, 1);
v___x_1718_ = lean_io_mono_nanos_now();
v___x_1719_ = lp_competition_R24DotBankHarness_seed(v_i_1705_);
v___x_1720_ = lean_box_uint32(v___x_1719_);
lean_inc(v_iters_1701_);
lean_inc_ref(v_a_1698_);
v___f_1721_ = lean_alloc_closure((void*)(lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotBankHarness_benchLazy_spec__0___redArg___lam__1___boxed), 4, 3);
lean_closure_set(v___f_1721_, 0, v_a_1698_);
lean_closure_set(v___f_1721_, 1, v___x_1720_);
lean_closure_set(v___f_1721_, 2, v_iters_1701_);
v___x_1722_ = l_IO_lazyPure___redArg(v___f_1721_);
v_a_1723_ = lean_ctor_get(v___x_1722_, 0);
lean_inc(v_a_1723_);
lean_dec_ref(v___x_1722_);
v___x_1724_ = lean_io_mono_nanos_now();
v___x_1725_ = lean_uint32_of_nat(v_iters_1701_);
v___x_1726_ = lean_uint32_mul(v___x_1725_, v_expected_1700_);
v___x_1727_ = lean_uint32_add(v___x_1719_, v___x_1726_);
v___x_1728_ = ((lean_object*)(lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00__private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotBankHarness_benchLazy_spec__0_spec__0___redArg___closed__1));
v___x_1729_ = lean_unbox_uint32(v_a_1723_);
lean_inc_ref(v_name_1714_);
v___x_1730_ = lp_competition_R24DotBankHarness_checkWord(v_name_1714_, v___x_1728_, v___x_1729_, v___x_1727_);
if (lean_obj_tag(v___x_1730_) == 0)
{
lean_object* v___x_1731_; lean_object* v_a_1732_; lean_object* v___x_1733_; uint32_t v___x_1734_; lean_object* v___x_1735_; 
lean_dec_ref_known(v___x_1730_, 1);
v___x_1731_ = l_IO_lazyPure___redArg(v___f_1711_);
v_a_1732_ = lean_ctor_get(v___x_1731_, 0);
lean_inc(v_a_1732_);
lean_dec_ref(v___x_1731_);
v___x_1733_ = ((lean_object*)(lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00__private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotBankHarness_benchLazy_spec__0_spec__0___redArg___closed__2));
v___x_1734_ = lean_unbox_uint32(v_a_1732_);
lean_inc_ref(v_name_1714_);
v___x_1735_ = lp_competition_R24DotBankHarness_checkWord(v_name_1714_, v___x_1733_, v___x_1734_, v_expected_1700_);
if (lean_obj_tag(v___x_1735_) == 0)
{
lean_object* v___x_1736_; lean_object* v___x_1737_; uint32_t v___x_1738_; uint32_t v___x_1739_; lean_object* v___x_1740_; lean_object* v___x_1741_; lean_object* v___x_1742_; 
lean_dec_ref_known(v___x_1735_, 1);
v___x_1736_ = lean_nat_sub(v___x_1724_, v___x_1718_);
lean_dec(v___x_1718_);
lean_dec(v___x_1724_);
lean_inc(v_iters_1701_);
lean_inc(v_work_1702_);
lean_inc(v_i_1705_);
v___x_1737_ = lean_alloc_ctor(0, 4, 12);
lean_ctor_set(v___x_1737_, 0, v_i_1705_);
lean_ctor_set(v___x_1737_, 1, v_work_1702_);
lean_ctor_set(v___x_1737_, 2, v_iters_1701_);
lean_ctor_set(v___x_1737_, 3, v___x_1736_);
v___x_1738_ = lean_unbox_uint32(v_a_1723_);
lean_dec(v_a_1723_);
lean_ctor_set_uint32(v___x_1737_, sizeof(void*)*4, v___x_1738_);
lean_ctor_set_uint32(v___x_1737_, sizeof(void*)*4 + 4, v___x_1727_);
v___x_1739_ = lean_unbox_uint32(v_a_1732_);
lean_dec(v_a_1732_);
lean_ctor_set_uint32(v___x_1737_, sizeof(void*)*4 + 8, v___x_1739_);
v___x_1740_ = lean_array_push(v_b_1704_, v___x_1737_);
v___x_1741_ = lean_nat_add(v_i_1705_, v_step_1708_);
lean_dec(v_i_1705_);
v___x_1742_ = lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00__private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotBankHarness_benchLazy_spec__0_spec__0___redArg(v_a_1698_, v_c_1699_, v_expected_1700_, v_iters_1701_, v_work_1702_, v_range_1703_, v___x_1740_, v___x_1741_);
return v___x_1742_;
}
else
{
lean_object* v_a_1743_; lean_object* v___x_1745_; uint8_t v_isShared_1746_; uint8_t v_isSharedCheck_1750_; 
lean_dec(v_a_1732_);
lean_dec(v___x_1724_);
lean_dec(v_a_1723_);
lean_dec(v___x_1718_);
lean_dec(v_i_1705_);
lean_dec_ref(v_b_1704_);
lean_dec(v_work_1702_);
lean_dec(v_iters_1701_);
lean_dec_ref(v_c_1699_);
lean_dec_ref(v_a_1698_);
v_a_1743_ = lean_ctor_get(v___x_1735_, 0);
v_isSharedCheck_1750_ = !lean_is_exclusive(v___x_1735_);
if (v_isSharedCheck_1750_ == 0)
{
v___x_1745_ = v___x_1735_;
v_isShared_1746_ = v_isSharedCheck_1750_;
goto v_resetjp_1744_;
}
else
{
lean_inc(v_a_1743_);
lean_dec(v___x_1735_);
v___x_1745_ = lean_box(0);
v_isShared_1746_ = v_isSharedCheck_1750_;
goto v_resetjp_1744_;
}
v_resetjp_1744_:
{
lean_object* v___x_1748_; 
if (v_isShared_1746_ == 0)
{
v___x_1748_ = v___x_1745_;
goto v_reusejp_1747_;
}
else
{
lean_object* v_reuseFailAlloc_1749_; 
v_reuseFailAlloc_1749_ = lean_alloc_ctor(1, 1, 0);
lean_ctor_set(v_reuseFailAlloc_1749_, 0, v_a_1743_);
v___x_1748_ = v_reuseFailAlloc_1749_;
goto v_reusejp_1747_;
}
v_reusejp_1747_:
{
return v___x_1748_;
}
}
}
}
else
{
lean_object* v_a_1751_; lean_object* v___x_1753_; uint8_t v_isShared_1754_; uint8_t v_isSharedCheck_1758_; 
lean_dec(v___x_1724_);
lean_dec(v_a_1723_);
lean_dec(v___x_1718_);
lean_dec_ref(v___f_1711_);
lean_dec(v_i_1705_);
lean_dec_ref(v_b_1704_);
lean_dec(v_work_1702_);
lean_dec(v_iters_1701_);
lean_dec_ref(v_c_1699_);
lean_dec_ref(v_a_1698_);
v_a_1751_ = lean_ctor_get(v___x_1730_, 0);
v_isSharedCheck_1758_ = !lean_is_exclusive(v___x_1730_);
if (v_isSharedCheck_1758_ == 0)
{
v___x_1753_ = v___x_1730_;
v_isShared_1754_ = v_isSharedCheck_1758_;
goto v_resetjp_1752_;
}
else
{
lean_inc(v_a_1751_);
lean_dec(v___x_1730_);
v___x_1753_ = lean_box(0);
v_isShared_1754_ = v_isSharedCheck_1758_;
goto v_resetjp_1752_;
}
v_resetjp_1752_:
{
lean_object* v___x_1756_; 
if (v_isShared_1754_ == 0)
{
v___x_1756_ = v___x_1753_;
goto v_reusejp_1755_;
}
else
{
lean_object* v_reuseFailAlloc_1757_; 
v_reuseFailAlloc_1757_ = lean_alloc_ctor(1, 1, 0);
lean_ctor_set(v_reuseFailAlloc_1757_, 0, v_a_1751_);
v___x_1756_ = v_reuseFailAlloc_1757_;
goto v_reusejp_1755_;
}
v_reusejp_1755_:
{
return v___x_1756_;
}
}
}
}
else
{
lean_object* v_a_1759_; lean_object* v___x_1761_; uint8_t v_isShared_1762_; uint8_t v_isSharedCheck_1766_; 
lean_dec_ref(v___f_1711_);
lean_dec(v_i_1705_);
lean_dec_ref(v_b_1704_);
lean_dec(v_work_1702_);
lean_dec(v_iters_1701_);
lean_dec_ref(v_c_1699_);
lean_dec_ref(v_a_1698_);
v_a_1759_ = lean_ctor_get(v___x_1717_, 0);
v_isSharedCheck_1766_ = !lean_is_exclusive(v___x_1717_);
if (v_isSharedCheck_1766_ == 0)
{
v___x_1761_ = v___x_1717_;
v_isShared_1762_ = v_isSharedCheck_1766_;
goto v_resetjp_1760_;
}
else
{
lean_inc(v_a_1759_);
lean_dec(v___x_1717_);
v___x_1761_ = lean_box(0);
v_isShared_1762_ = v_isSharedCheck_1766_;
goto v_resetjp_1760_;
}
v_resetjp_1760_:
{
lean_object* v___x_1764_; 
if (v_isShared_1762_ == 0)
{
v___x_1764_ = v___x_1761_;
goto v_reusejp_1763_;
}
else
{
lean_object* v_reuseFailAlloc_1765_; 
v_reuseFailAlloc_1765_ = lean_alloc_ctor(1, 1, 0);
lean_ctor_set(v_reuseFailAlloc_1765_, 0, v_a_1759_);
v___x_1764_ = v_reuseFailAlloc_1765_;
goto v_reusejp_1763_;
}
v_reusejp_1763_:
{
return v___x_1764_;
}
}
}
}
}
}
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotBankHarness_benchLazy_spec__0___redArg___boxed(lean_object* v_a_1767_, lean_object* v_c_1768_, lean_object* v_expected_1769_, lean_object* v_iters_1770_, lean_object* v_work_1771_, lean_object* v_range_1772_, lean_object* v_b_1773_, lean_object* v_i_1774_, lean_object* v___y_1775_){
_start:
{
uint32_t v_expected_boxed_1776_; lean_object* v_res_1777_; 
v_expected_boxed_1776_ = lean_unbox_uint32(v_expected_1769_);
lean_dec(v_expected_1769_);
v_res_1777_ = lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotBankHarness_benchLazy_spec__0___redArg(v_a_1767_, v_c_1768_, v_expected_boxed_1776_, v_iters_1770_, v_work_1771_, v_range_1772_, v_b_1773_, v_i_1774_);
lean_dec_ref(v_range_1772_);
return v_res_1777_;
}
}
LEAN_EXPORT lean_object* lp_competition_R24DotBankHarness_benchLazy(lean_object* v_c_1779_, lean_object* v_a_1780_, lean_object* v_b_1781_, lean_object* v_macs_1782_, uint32_t v_expected_1783_){
_start:
{
lean_object* v___f_1785_; lean_object* v___x_1786_; lean_object* v_a_1787_; lean_object* v___x_1788_; lean_object* v_a_1789_; lean_object* v_inner_1790_; lean_object* v_rows_1791_; lean_object* v_cols_1792_; lean_object* v___x_1793_; lean_object* v_work_1794_; lean_object* v_iters_1795_; lean_object* v___x_1796_; lean_object* v___x_1797_; lean_object* v___x_1798_; lean_object* v___x_1799_; 
v___f_1785_ = lean_alloc_closure((void*)(lp_competition_R24DotBankHarness_benchExact___lam__0), 3, 2);
lean_closure_set(v___f_1785_, 0, v_a_1780_);
lean_closure_set(v___f_1785_, 1, v_b_1781_);
v___x_1786_ = l_IO_lazyPure___redArg(v___f_1785_);
v_a_1787_ = lean_ctor_get(v___x_1786_, 0);
lean_inc(v_a_1787_);
lean_dec_ref(v___x_1786_);
v___x_1788_ = lp_competition_R24DotBankHarness_benchExact___lam__1();
v_a_1789_ = lean_ctor_get(v___x_1788_, 0);
lean_inc(v_a_1789_);
lean_dec_ref(v___x_1788_);
v_inner_1790_ = lean_ctor_get(v_c_1779_, 2);
v_rows_1791_ = lean_ctor_get(v_c_1779_, 3);
v_cols_1792_ = lean_ctor_get(v_c_1779_, 4);
v___x_1793_ = lean_nat_mul(v_rows_1791_, v_cols_1792_);
v_work_1794_ = lean_nat_mul(v___x_1793_, v_inner_1790_);
lean_dec(v___x_1793_);
v_iters_1795_ = lp_competition_R24DotBankHarness_repeats(v_macs_1782_, v_work_1794_);
v___x_1796_ = lean_unsigned_to_nat(0u);
v___x_1797_ = ((lean_object*)(lp_competition_R24DotBankHarness_benchExact___closed__0));
v___x_1798_ = ((lean_object*)(lp_competition_R24DotBankHarness_benchExact___closed__1));
lean_inc_ref(v_c_1779_);
v___x_1799_ = lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotBankHarness_benchLazy_spec__0___redArg(v_a_1787_, v_c_1779_, v_expected_1783_, v_iters_1795_, v_work_1794_, v___x_1798_, v___x_1797_, v___x_1796_);
if (lean_obj_tag(v___x_1799_) == 0)
{
lean_object* v_a_1800_; lean_object* v___x_1801_; lean_object* v_a_1802_; lean_object* v___x_1803_; lean_object* v___x_1804_; lean_object* v___x_1805_; 
v_a_1800_ = lean_ctor_get(v___x_1799_, 0);
lean_inc(v_a_1800_);
lean_dec_ref_known(v___x_1799_, 1);
v___x_1801_ = lp_competition_R24DotBankHarness_benchExact___lam__1();
v_a_1802_ = lean_ctor_get(v___x_1801_, 0);
lean_inc(v_a_1802_);
lean_dec_ref(v___x_1801_);
v___x_1803_ = ((lean_object*)(lp_competition_R24DotBankHarness_benchLazy___closed__0));
v___x_1804_ = lean_nat_sub(v_a_1802_, v_a_1789_);
lean_dec(v_a_1789_);
lean_dec(v_a_1802_);
v___x_1805_ = lp_competition_R24DotBankHarness_emit(v_c_1779_, v___x_1803_, v___x_1804_, v_a_1800_);
lean_dec(v_a_1800_);
lean_dec_ref(v_c_1779_);
return v___x_1805_;
}
else
{
lean_object* v_a_1806_; lean_object* v___x_1808_; uint8_t v_isShared_1809_; uint8_t v_isSharedCheck_1813_; 
lean_dec(v_a_1789_);
lean_dec_ref(v_c_1779_);
v_a_1806_ = lean_ctor_get(v___x_1799_, 0);
v_isSharedCheck_1813_ = !lean_is_exclusive(v___x_1799_);
if (v_isSharedCheck_1813_ == 0)
{
v___x_1808_ = v___x_1799_;
v_isShared_1809_ = v_isSharedCheck_1813_;
goto v_resetjp_1807_;
}
else
{
lean_inc(v_a_1806_);
lean_dec(v___x_1799_);
v___x_1808_ = lean_box(0);
v_isShared_1809_ = v_isSharedCheck_1813_;
goto v_resetjp_1807_;
}
v_resetjp_1807_:
{
lean_object* v___x_1811_; 
if (v_isShared_1809_ == 0)
{
v___x_1811_ = v___x_1808_;
goto v_reusejp_1810_;
}
else
{
lean_object* v_reuseFailAlloc_1812_; 
v_reuseFailAlloc_1812_ = lean_alloc_ctor(1, 1, 0);
lean_ctor_set(v_reuseFailAlloc_1812_, 0, v_a_1806_);
v___x_1811_ = v_reuseFailAlloc_1812_;
goto v_reusejp_1810_;
}
v_reusejp_1810_:
{
return v___x_1811_;
}
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_R24DotBankHarness_benchLazy___boxed(lean_object* v_c_1814_, lean_object* v_a_1815_, lean_object* v_b_1816_, lean_object* v_macs_1817_, lean_object* v_expected_1818_, lean_object* v_a_1819_){
_start:
{
uint32_t v_expected_boxed_1820_; lean_object* v_res_1821_; 
v_expected_boxed_1820_ = lean_unbox_uint32(v_expected_1818_);
lean_dec(v_expected_1818_);
v_res_1821_ = lp_competition_R24DotBankHarness_benchLazy(v_c_1814_, v_a_1815_, v_b_1816_, v_macs_1817_, v_expected_boxed_1820_);
lean_dec(v_macs_1817_);
return v_res_1821_;
}
}
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotBankHarness_benchLazy_spec__0(lean_object* v_a_1822_, lean_object* v_c_1823_, uint32_t v_expected_1824_, lean_object* v_iters_1825_, lean_object* v_work_1826_, lean_object* v_range_1827_, lean_object* v_b_1828_, lean_object* v_i_1829_, lean_object* v_hs_1830_, lean_object* v_hl_1831_){
_start:
{
lean_object* v___x_1833_; 
v___x_1833_ = lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotBankHarness_benchLazy_spec__0___redArg(v_a_1822_, v_c_1823_, v_expected_1824_, v_iters_1825_, v_work_1826_, v_range_1827_, v_b_1828_, v_i_1829_);
return v___x_1833_;
}
}
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotBankHarness_benchLazy_spec__0___boxed(lean_object* v_a_1834_, lean_object* v_c_1835_, lean_object* v_expected_1836_, lean_object* v_iters_1837_, lean_object* v_work_1838_, lean_object* v_range_1839_, lean_object* v_b_1840_, lean_object* v_i_1841_, lean_object* v_hs_1842_, lean_object* v_hl_1843_, lean_object* v___y_1844_){
_start:
{
uint32_t v_expected_boxed_1845_; lean_object* v_res_1846_; 
v_expected_boxed_1845_ = lean_unbox_uint32(v_expected_1836_);
lean_dec(v_expected_1836_);
v_res_1846_ = lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotBankHarness_benchLazy_spec__0(v_a_1834_, v_c_1835_, v_expected_boxed_1845_, v_iters_1837_, v_work_1838_, v_range_1839_, v_b_1840_, v_i_1841_, v_hs_1842_, v_hl_1843_);
lean_dec_ref(v_range_1839_);
return v_res_1846_;
}
}
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00__private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotBankHarness_benchLazy_spec__0_spec__0(lean_object* v_a_1847_, lean_object* v_c_1848_, uint32_t v_expected_1849_, lean_object* v_iters_1850_, lean_object* v_work_1851_, lean_object* v_range_1852_, lean_object* v_b_1853_, lean_object* v_i_1854_, lean_object* v_hs_1855_, lean_object* v_hl_1856_){
_start:
{
lean_object* v___x_1858_; 
v___x_1858_ = lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00__private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotBankHarness_benchLazy_spec__0_spec__0___redArg(v_a_1847_, v_c_1848_, v_expected_1849_, v_iters_1850_, v_work_1851_, v_range_1852_, v_b_1853_, v_i_1854_);
return v___x_1858_;
}
}
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00__private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotBankHarness_benchLazy_spec__0_spec__0___boxed(lean_object* v_a_1859_, lean_object* v_c_1860_, lean_object* v_expected_1861_, lean_object* v_iters_1862_, lean_object* v_work_1863_, lean_object* v_range_1864_, lean_object* v_b_1865_, lean_object* v_i_1866_, lean_object* v_hs_1867_, lean_object* v_hl_1868_, lean_object* v___y_1869_){
_start:
{
uint32_t v_expected_boxed_1870_; lean_object* v_res_1871_; 
v_expected_boxed_1870_ = lean_unbox_uint32(v_expected_1861_);
lean_dec(v_expected_1861_);
v_res_1871_ = lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00__private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00R24DotBankHarness_benchLazy_spec__0_spec__0(v_a_1859_, v_c_1860_, v_expected_boxed_1870_, v_iters_1862_, v_work_1863_, v_range_1864_, v_b_1865_, v_i_1866_, v_hs_1867_, v_hl_1868_);
lean_dec_ref(v_range_1864_);
return v_res_1871_;
}
}
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotBankHarness_verify_spec__0___lam__0(lean_object* v___x_1872_, lean_object* v___x_1873_, lean_object* v_x_1874_){
_start:
{
lean_object* v___x_1875_; 
v___x_1875_ = lp_competition_Submission_R24GenericDotBank_exactBank(v___x_1872_, v___x_1873_);
return v___x_1875_;
}
}
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotBankHarness_verify_spec__0___lam__0___boxed(lean_object* v___x_1876_, lean_object* v___x_1877_, lean_object* v_x_1878_){
_start:
{
lean_object* v_res_1879_; 
v_res_1879_ = lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotBankHarness_verify_spec__0___lam__0(v___x_1876_, v___x_1877_, v_x_1878_);
lean_dec_ref(v___x_1877_);
lean_dec_ref(v___x_1876_);
return v_res_1879_;
}
}
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotBankHarness_verify_spec__0___lam__2(lean_object* v___x_1880_, lean_object* v___x_1881_, lean_object* v_x_1882_){
_start:
{
lean_object* v___x_1883_; 
v___x_1883_ = lp_competition_Submission_R24GenericDotBank_lazyBank(v___x_1880_, v___x_1881_);
return v___x_1883_;
}
}
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotBankHarness_verify_spec__0___lam__2___boxed(lean_object* v___x_1884_, lean_object* v___x_1885_, lean_object* v_x_1886_){
_start:
{
lean_object* v_res_1887_; 
v_res_1887_ = lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotBankHarness_verify_spec__0___lam__2(v___x_1884_, v___x_1885_, v_x_1886_);
lean_dec_ref(v___x_1885_);
lean_dec_ref(v___x_1884_);
return v_res_1887_;
}
}
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotBankHarness_verify_spec__0___lam__1(lean_object* v___x_1888_, lean_object* v___x_1889_, lean_object* v_x_1890_){
_start:
{
lean_object* v___x_1891_; 
v___x_1891_ = lp_competition_Submission_R24GenericDotBank_eagerBank(v___x_1888_, v___x_1889_);
return v___x_1891_;
}
}
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotBankHarness_verify_spec__0___lam__1___boxed(lean_object* v___x_1892_, lean_object* v___x_1893_, lean_object* v_x_1894_){
_start:
{
lean_object* v_res_1895_; 
v_res_1895_ = lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotBankHarness_verify_spec__0___lam__1(v___x_1892_, v___x_1893_, v_x_1894_);
lean_dec_ref(v___x_1893_);
lean_dec_ref(v___x_1892_);
return v_res_1895_;
}
}
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotBankHarness_verify_spec__0(lean_object* v_as_1901_, size_t v_sz_1902_, size_t v_i_1903_, lean_object* v_b_1904_){
_start:
{
uint8_t v___x_1906_; 
v___x_1906_ = lean_usize_dec_lt(v_i_1903_, v_sz_1902_);
if (v___x_1906_ == 0)
{
lean_object* v___x_1907_; 
v___x_1907_ = lean_alloc_ctor(0, 1, 0);
lean_ctor_set(v___x_1907_, 0, v_b_1904_);
return v___x_1907_;
}
else
{
lean_object* v_a_1908_; lean_object* v___x_1909_; 
v_a_1908_ = lean_array_uget_borrowed(v_as_1901_, v_i_1903_);
lean_inc(v_a_1908_);
v___x_1909_ = lp_competition_R24DotBankHarness_checkCase(v_a_1908_);
if (lean_obj_tag(v___x_1909_) == 0)
{
lean_object* v_name_1910_; lean_object* v_rowsA_1911_; lean_object* v_rowsB_1912_; lean_object* v_expected_1913_; lean_object* v___x_1914_; lean_object* v___x_1915_; lean_object* v___f_1916_; lean_object* v___x_1917_; 
lean_dec_ref_known(v___x_1909_, 1);
v_name_1910_ = lean_ctor_get(v_a_1908_, 0);
v_rowsA_1911_ = lean_ctor_get(v_a_1908_, 5);
v_rowsB_1912_ = lean_ctor_get(v_a_1908_, 6);
v_expected_1913_ = lean_ctor_get(v_a_1908_, 7);
lean_inc_ref(v_rowsA_1911_);
v___x_1914_ = lp_competition_R24DotBankHarness_words(v_rowsA_1911_);
lean_inc_ref(v_rowsB_1912_);
v___x_1915_ = lp_competition_R24DotBankHarness_words(v_rowsB_1912_);
lean_inc_ref(v___x_1915_);
lean_inc_ref(v___x_1914_);
v___f_1916_ = lean_alloc_closure((void*)(lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotBankHarness_verify_spec__0___lam__0___boxed), 3, 2);
lean_closure_set(v___f_1916_, 0, v___x_1914_);
lean_closure_set(v___f_1916_, 1, v___x_1915_);
v___x_1917_ = l_IO_lazyPure___redArg(v___f_1916_);
if (lean_obj_tag(v___x_1917_) == 0)
{
lean_object* v_a_1918_; lean_object* v___f_1919_; lean_object* v___x_1920_; 
v_a_1918_ = lean_ctor_get(v___x_1917_, 0);
lean_inc(v_a_1918_);
lean_dec_ref_known(v___x_1917_, 1);
lean_inc_ref(v___x_1915_);
lean_inc_ref(v___x_1914_);
v___f_1919_ = lean_alloc_closure((void*)(lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotBankHarness_verify_spec__0___lam__1___boxed), 3, 2);
lean_closure_set(v___f_1919_, 0, v___x_1914_);
lean_closure_set(v___f_1919_, 1, v___x_1915_);
v___x_1920_ = l_IO_lazyPure___redArg(v___f_1919_);
if (lean_obj_tag(v___x_1920_) == 0)
{
lean_object* v_a_1921_; lean_object* v___f_1922_; lean_object* v___x_1923_; 
v_a_1921_ = lean_ctor_get(v___x_1920_, 0);
lean_inc(v_a_1921_);
lean_dec_ref_known(v___x_1920_, 1);
v___f_1922_ = lean_alloc_closure((void*)(lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotBankHarness_verify_spec__0___lam__2___boxed), 3, 2);
lean_closure_set(v___f_1922_, 0, v___x_1914_);
lean_closure_set(v___f_1922_, 1, v___x_1915_);
v___x_1923_ = l_IO_lazyPure___redArg(v___f_1922_);
if (lean_obj_tag(v___x_1923_) == 0)
{
lean_object* v_a_1924_; lean_object* v___x_1925_; lean_object* v___x_1926_; lean_object* v___x_1927_; 
v_a_1924_ = lean_ctor_get(v___x_1923_, 0);
lean_inc(v_a_1924_);
lean_dec_ref_known(v___x_1923_, 1);
lean_inc_ref(v_expected_1913_);
v___x_1925_ = lp_competition_R24DotBankHarness_outputWords(v_expected_1913_);
v___x_1926_ = ((lean_object*)(lp_competition_R24DotBankHarness_benchExact___closed__2));
lean_inc_ref(v_name_1910_);
v___x_1927_ = lp_competition_R24DotBankHarness_checkArray(v_name_1910_, v___x_1926_, v_a_1918_, v___x_1925_);
if (lean_obj_tag(v___x_1927_) == 0)
{
lean_object* v___x_1928_; lean_object* v___x_1929_; 
lean_dec_ref_known(v___x_1927_, 1);
v___x_1928_ = ((lean_object*)(lp_competition_R24DotBankHarness_benchEager___closed__0));
lean_inc_ref(v_name_1910_);
v___x_1929_ = lp_competition_R24DotBankHarness_checkArray(v_name_1910_, v___x_1928_, v_a_1921_, v___x_1925_);
if (lean_obj_tag(v___x_1929_) == 0)
{
lean_object* v___x_1930_; lean_object* v___x_1931_; 
lean_dec_ref_known(v___x_1929_, 1);
v___x_1930_ = ((lean_object*)(lp_competition_R24DotBankHarness_benchLazy___closed__0));
lean_inc_ref(v_name_1910_);
v___x_1931_ = lp_competition_R24DotBankHarness_checkArray(v_name_1910_, v___x_1930_, v_a_1924_, v___x_1925_);
if (lean_obj_tag(v___x_1931_) == 0)
{
uint32_t v___x_1932_; uint32_t v___x_1933_; lean_object* v___x_1934_; lean_object* v___x_1935_; 
lean_dec_ref_known(v___x_1931_, 1);
v___x_1932_ = lp_competition_R24DotBankHarness_hashAll(v___x_1925_);
lean_dec_ref(v___x_1925_);
v___x_1933_ = lp_competition_R24DotBankHarness_hashAll(v_a_1918_);
lean_dec(v_a_1918_);
v___x_1934_ = ((lean_object*)(lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotBankHarness_verify_spec__0___closed__0));
lean_inc_ref(v_name_1910_);
v___x_1935_ = lp_competition_R24DotBankHarness_checkWord(v_name_1910_, v___x_1934_, v___x_1933_, v___x_1932_);
if (lean_obj_tag(v___x_1935_) == 0)
{
uint32_t v___x_1936_; lean_object* v___x_1937_; lean_object* v___x_1938_; 
lean_dec_ref_known(v___x_1935_, 1);
v___x_1936_ = lp_competition_R24DotBankHarness_hashAll(v_a_1921_);
lean_dec(v_a_1921_);
v___x_1937_ = ((lean_object*)(lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotBankHarness_verify_spec__0___closed__1));
lean_inc_ref(v_name_1910_);
v___x_1938_ = lp_competition_R24DotBankHarness_checkWord(v_name_1910_, v___x_1937_, v___x_1936_, v___x_1932_);
if (lean_obj_tag(v___x_1938_) == 0)
{
uint32_t v___x_1939_; lean_object* v___x_1940_; lean_object* v___x_1941_; 
lean_dec_ref_known(v___x_1938_, 1);
v___x_1939_ = lp_competition_R24DotBankHarness_hashAll(v_a_1924_);
lean_dec(v_a_1924_);
v___x_1940_ = ((lean_object*)(lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotBankHarness_verify_spec__0___closed__2));
lean_inc_ref(v_name_1910_);
v___x_1941_ = lp_competition_R24DotBankHarness_checkWord(v_name_1910_, v___x_1940_, v___x_1939_, v___x_1932_);
if (lean_obj_tag(v___x_1941_) == 0)
{
lean_object* v___x_1942_; lean_object* v___x_1943_; lean_object* v___x_1944_; lean_object* v___x_1945_; lean_object* v___x_1946_; lean_object* v___x_1947_; lean_object* v___x_1948_; lean_object* v___x_1949_; lean_object* v___x_1950_; lean_object* v___x_1951_; lean_object* v___x_1952_; lean_object* v___x_1953_; lean_object* v___x_1954_; lean_object* v___x_1955_; lean_object* v___x_1956_; lean_object* v___x_1957_; lean_object* v___x_1958_; lean_object* v___x_1959_; lean_object* v___x_1960_; lean_object* v___x_1961_; lean_object* v___x_1962_; lean_object* v___x_1963_; lean_object* v___x_1964_; lean_object* v___x_1965_; lean_object* v___x_1966_; lean_object* v___x_1967_; lean_object* v___x_1968_; 
lean_dec_ref_known(v___x_1941_, 1);
v___x_1942_ = lean_array_get_size(v_expected_1913_);
v___x_1943_ = lean_nat_add(v_b_1904_, v___x_1942_);
lean_dec(v_b_1904_);
v___x_1944_ = ((lean_object*)(lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotBankHarness_verify_spec__0___closed__3));
v___x_1945_ = lean_string_append(v___x_1944_, v_name_1910_);
v___x_1946_ = ((lean_object*)(lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotBankHarness_emit_spec__0___closed__1));
v___x_1947_ = lean_string_append(v___x_1945_, v___x_1946_);
v___x_1948_ = l_Nat_reprFast(v___x_1942_);
v___x_1949_ = lean_string_append(v___x_1947_, v___x_1948_);
lean_dec_ref(v___x_1948_);
v___x_1950_ = lean_string_append(v___x_1949_, v___x_1946_);
v___x_1951_ = lean_uint32_to_nat(v___x_1932_);
v___x_1952_ = l_Nat_reprFast(v___x_1951_);
v___x_1953_ = lean_string_append(v___x_1950_, v___x_1952_);
lean_dec_ref(v___x_1952_);
v___x_1954_ = lean_string_append(v___x_1953_, v___x_1946_);
v___x_1955_ = lean_uint32_to_nat(v___x_1933_);
v___x_1956_ = l_Nat_reprFast(v___x_1955_);
v___x_1957_ = lean_string_append(v___x_1954_, v___x_1956_);
lean_dec_ref(v___x_1956_);
v___x_1958_ = lean_string_append(v___x_1957_, v___x_1946_);
v___x_1959_ = lean_uint32_to_nat(v___x_1936_);
v___x_1960_ = l_Nat_reprFast(v___x_1959_);
v___x_1961_ = lean_string_append(v___x_1958_, v___x_1960_);
lean_dec_ref(v___x_1960_);
v___x_1962_ = lean_string_append(v___x_1961_, v___x_1946_);
v___x_1963_ = lean_uint32_to_nat(v___x_1939_);
v___x_1964_ = l_Nat_reprFast(v___x_1963_);
v___x_1965_ = lean_string_append(v___x_1962_, v___x_1964_);
lean_dec_ref(v___x_1964_);
v___x_1966_ = ((lean_object*)(lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotBankHarness_verify_spec__0___closed__4));
v___x_1967_ = lean_string_append(v___x_1965_, v___x_1966_);
v___x_1968_ = lp_batteries_IO_println___at___00Batteries_Tactic_Lint_lintCore_spec__4(v___x_1967_);
if (lean_obj_tag(v___x_1968_) == 0)
{
size_t v___x_1969_; size_t v___x_1970_; 
lean_dec_ref_known(v___x_1968_, 1);
v___x_1969_ = ((size_t)1ULL);
v___x_1970_ = lean_usize_add(v_i_1903_, v___x_1969_);
v_i_1903_ = v___x_1970_;
v_b_1904_ = v___x_1943_;
goto _start;
}
else
{
lean_object* v_a_1972_; lean_object* v___x_1974_; uint8_t v_isShared_1975_; uint8_t v_isSharedCheck_1979_; 
lean_dec(v___x_1943_);
v_a_1972_ = lean_ctor_get(v___x_1968_, 0);
v_isSharedCheck_1979_ = !lean_is_exclusive(v___x_1968_);
if (v_isSharedCheck_1979_ == 0)
{
v___x_1974_ = v___x_1968_;
v_isShared_1975_ = v_isSharedCheck_1979_;
goto v_resetjp_1973_;
}
else
{
lean_inc(v_a_1972_);
lean_dec(v___x_1968_);
v___x_1974_ = lean_box(0);
v_isShared_1975_ = v_isSharedCheck_1979_;
goto v_resetjp_1973_;
}
v_resetjp_1973_:
{
lean_object* v___x_1977_; 
if (v_isShared_1975_ == 0)
{
v___x_1977_ = v___x_1974_;
goto v_reusejp_1976_;
}
else
{
lean_object* v_reuseFailAlloc_1978_; 
v_reuseFailAlloc_1978_ = lean_alloc_ctor(1, 1, 0);
lean_ctor_set(v_reuseFailAlloc_1978_, 0, v_a_1972_);
v___x_1977_ = v_reuseFailAlloc_1978_;
goto v_reusejp_1976_;
}
v_reusejp_1976_:
{
return v___x_1977_;
}
}
}
}
else
{
lean_object* v_a_1980_; lean_object* v___x_1982_; uint8_t v_isShared_1983_; uint8_t v_isSharedCheck_1987_; 
lean_dec(v_b_1904_);
v_a_1980_ = lean_ctor_get(v___x_1941_, 0);
v_isSharedCheck_1987_ = !lean_is_exclusive(v___x_1941_);
if (v_isSharedCheck_1987_ == 0)
{
v___x_1982_ = v___x_1941_;
v_isShared_1983_ = v_isSharedCheck_1987_;
goto v_resetjp_1981_;
}
else
{
lean_inc(v_a_1980_);
lean_dec(v___x_1941_);
v___x_1982_ = lean_box(0);
v_isShared_1983_ = v_isSharedCheck_1987_;
goto v_resetjp_1981_;
}
v_resetjp_1981_:
{
lean_object* v___x_1985_; 
if (v_isShared_1983_ == 0)
{
v___x_1985_ = v___x_1982_;
goto v_reusejp_1984_;
}
else
{
lean_object* v_reuseFailAlloc_1986_; 
v_reuseFailAlloc_1986_ = lean_alloc_ctor(1, 1, 0);
lean_ctor_set(v_reuseFailAlloc_1986_, 0, v_a_1980_);
v___x_1985_ = v_reuseFailAlloc_1986_;
goto v_reusejp_1984_;
}
v_reusejp_1984_:
{
return v___x_1985_;
}
}
}
}
else
{
lean_object* v_a_1988_; lean_object* v___x_1990_; uint8_t v_isShared_1991_; uint8_t v_isSharedCheck_1995_; 
lean_dec(v_a_1924_);
lean_dec(v_b_1904_);
v_a_1988_ = lean_ctor_get(v___x_1938_, 0);
v_isSharedCheck_1995_ = !lean_is_exclusive(v___x_1938_);
if (v_isSharedCheck_1995_ == 0)
{
v___x_1990_ = v___x_1938_;
v_isShared_1991_ = v_isSharedCheck_1995_;
goto v_resetjp_1989_;
}
else
{
lean_inc(v_a_1988_);
lean_dec(v___x_1938_);
v___x_1990_ = lean_box(0);
v_isShared_1991_ = v_isSharedCheck_1995_;
goto v_resetjp_1989_;
}
v_resetjp_1989_:
{
lean_object* v___x_1993_; 
if (v_isShared_1991_ == 0)
{
v___x_1993_ = v___x_1990_;
goto v_reusejp_1992_;
}
else
{
lean_object* v_reuseFailAlloc_1994_; 
v_reuseFailAlloc_1994_ = lean_alloc_ctor(1, 1, 0);
lean_ctor_set(v_reuseFailAlloc_1994_, 0, v_a_1988_);
v___x_1993_ = v_reuseFailAlloc_1994_;
goto v_reusejp_1992_;
}
v_reusejp_1992_:
{
return v___x_1993_;
}
}
}
}
else
{
lean_object* v_a_1996_; lean_object* v___x_1998_; uint8_t v_isShared_1999_; uint8_t v_isSharedCheck_2003_; 
lean_dec(v_a_1924_);
lean_dec(v_a_1921_);
lean_dec(v_b_1904_);
v_a_1996_ = lean_ctor_get(v___x_1935_, 0);
v_isSharedCheck_2003_ = !lean_is_exclusive(v___x_1935_);
if (v_isSharedCheck_2003_ == 0)
{
v___x_1998_ = v___x_1935_;
v_isShared_1999_ = v_isSharedCheck_2003_;
goto v_resetjp_1997_;
}
else
{
lean_inc(v_a_1996_);
lean_dec(v___x_1935_);
v___x_1998_ = lean_box(0);
v_isShared_1999_ = v_isSharedCheck_2003_;
goto v_resetjp_1997_;
}
v_resetjp_1997_:
{
lean_object* v___x_2001_; 
if (v_isShared_1999_ == 0)
{
v___x_2001_ = v___x_1998_;
goto v_reusejp_2000_;
}
else
{
lean_object* v_reuseFailAlloc_2002_; 
v_reuseFailAlloc_2002_ = lean_alloc_ctor(1, 1, 0);
lean_ctor_set(v_reuseFailAlloc_2002_, 0, v_a_1996_);
v___x_2001_ = v_reuseFailAlloc_2002_;
goto v_reusejp_2000_;
}
v_reusejp_2000_:
{
return v___x_2001_;
}
}
}
}
else
{
lean_object* v_a_2004_; lean_object* v___x_2006_; uint8_t v_isShared_2007_; uint8_t v_isSharedCheck_2011_; 
lean_dec_ref(v___x_1925_);
lean_dec(v_a_1924_);
lean_dec(v_a_1921_);
lean_dec(v_a_1918_);
lean_dec(v_b_1904_);
v_a_2004_ = lean_ctor_get(v___x_1931_, 0);
v_isSharedCheck_2011_ = !lean_is_exclusive(v___x_1931_);
if (v_isSharedCheck_2011_ == 0)
{
v___x_2006_ = v___x_1931_;
v_isShared_2007_ = v_isSharedCheck_2011_;
goto v_resetjp_2005_;
}
else
{
lean_inc(v_a_2004_);
lean_dec(v___x_1931_);
v___x_2006_ = lean_box(0);
v_isShared_2007_ = v_isSharedCheck_2011_;
goto v_resetjp_2005_;
}
v_resetjp_2005_:
{
lean_object* v___x_2009_; 
if (v_isShared_2007_ == 0)
{
v___x_2009_ = v___x_2006_;
goto v_reusejp_2008_;
}
else
{
lean_object* v_reuseFailAlloc_2010_; 
v_reuseFailAlloc_2010_ = lean_alloc_ctor(1, 1, 0);
lean_ctor_set(v_reuseFailAlloc_2010_, 0, v_a_2004_);
v___x_2009_ = v_reuseFailAlloc_2010_;
goto v_reusejp_2008_;
}
v_reusejp_2008_:
{
return v___x_2009_;
}
}
}
}
else
{
lean_object* v_a_2012_; lean_object* v___x_2014_; uint8_t v_isShared_2015_; uint8_t v_isSharedCheck_2019_; 
lean_dec_ref(v___x_1925_);
lean_dec(v_a_1924_);
lean_dec(v_a_1921_);
lean_dec(v_a_1918_);
lean_dec(v_b_1904_);
v_a_2012_ = lean_ctor_get(v___x_1929_, 0);
v_isSharedCheck_2019_ = !lean_is_exclusive(v___x_1929_);
if (v_isSharedCheck_2019_ == 0)
{
v___x_2014_ = v___x_1929_;
v_isShared_2015_ = v_isSharedCheck_2019_;
goto v_resetjp_2013_;
}
else
{
lean_inc(v_a_2012_);
lean_dec(v___x_1929_);
v___x_2014_ = lean_box(0);
v_isShared_2015_ = v_isSharedCheck_2019_;
goto v_resetjp_2013_;
}
v_resetjp_2013_:
{
lean_object* v___x_2017_; 
if (v_isShared_2015_ == 0)
{
v___x_2017_ = v___x_2014_;
goto v_reusejp_2016_;
}
else
{
lean_object* v_reuseFailAlloc_2018_; 
v_reuseFailAlloc_2018_ = lean_alloc_ctor(1, 1, 0);
lean_ctor_set(v_reuseFailAlloc_2018_, 0, v_a_2012_);
v___x_2017_ = v_reuseFailAlloc_2018_;
goto v_reusejp_2016_;
}
v_reusejp_2016_:
{
return v___x_2017_;
}
}
}
}
else
{
lean_object* v_a_2020_; lean_object* v___x_2022_; uint8_t v_isShared_2023_; uint8_t v_isSharedCheck_2027_; 
lean_dec_ref(v___x_1925_);
lean_dec(v_a_1924_);
lean_dec(v_a_1921_);
lean_dec(v_a_1918_);
lean_dec(v_b_1904_);
v_a_2020_ = lean_ctor_get(v___x_1927_, 0);
v_isSharedCheck_2027_ = !lean_is_exclusive(v___x_1927_);
if (v_isSharedCheck_2027_ == 0)
{
v___x_2022_ = v___x_1927_;
v_isShared_2023_ = v_isSharedCheck_2027_;
goto v_resetjp_2021_;
}
else
{
lean_inc(v_a_2020_);
lean_dec(v___x_1927_);
v___x_2022_ = lean_box(0);
v_isShared_2023_ = v_isSharedCheck_2027_;
goto v_resetjp_2021_;
}
v_resetjp_2021_:
{
lean_object* v___x_2025_; 
if (v_isShared_2023_ == 0)
{
v___x_2025_ = v___x_2022_;
goto v_reusejp_2024_;
}
else
{
lean_object* v_reuseFailAlloc_2026_; 
v_reuseFailAlloc_2026_ = lean_alloc_ctor(1, 1, 0);
lean_ctor_set(v_reuseFailAlloc_2026_, 0, v_a_2020_);
v___x_2025_ = v_reuseFailAlloc_2026_;
goto v_reusejp_2024_;
}
v_reusejp_2024_:
{
return v___x_2025_;
}
}
}
}
else
{
lean_object* v_a_2028_; lean_object* v___x_2030_; uint8_t v_isShared_2031_; uint8_t v_isSharedCheck_2035_; 
lean_dec(v_a_1921_);
lean_dec(v_a_1918_);
lean_dec(v_b_1904_);
v_a_2028_ = lean_ctor_get(v___x_1923_, 0);
v_isSharedCheck_2035_ = !lean_is_exclusive(v___x_1923_);
if (v_isSharedCheck_2035_ == 0)
{
v___x_2030_ = v___x_1923_;
v_isShared_2031_ = v_isSharedCheck_2035_;
goto v_resetjp_2029_;
}
else
{
lean_inc(v_a_2028_);
lean_dec(v___x_1923_);
v___x_2030_ = lean_box(0);
v_isShared_2031_ = v_isSharedCheck_2035_;
goto v_resetjp_2029_;
}
v_resetjp_2029_:
{
lean_object* v___x_2033_; 
if (v_isShared_2031_ == 0)
{
v___x_2033_ = v___x_2030_;
goto v_reusejp_2032_;
}
else
{
lean_object* v_reuseFailAlloc_2034_; 
v_reuseFailAlloc_2034_ = lean_alloc_ctor(1, 1, 0);
lean_ctor_set(v_reuseFailAlloc_2034_, 0, v_a_2028_);
v___x_2033_ = v_reuseFailAlloc_2034_;
goto v_reusejp_2032_;
}
v_reusejp_2032_:
{
return v___x_2033_;
}
}
}
}
else
{
lean_object* v_a_2036_; lean_object* v___x_2038_; uint8_t v_isShared_2039_; uint8_t v_isSharedCheck_2043_; 
lean_dec(v_a_1918_);
lean_dec_ref(v___x_1915_);
lean_dec_ref(v___x_1914_);
lean_dec(v_b_1904_);
v_a_2036_ = lean_ctor_get(v___x_1920_, 0);
v_isSharedCheck_2043_ = !lean_is_exclusive(v___x_1920_);
if (v_isSharedCheck_2043_ == 0)
{
v___x_2038_ = v___x_1920_;
v_isShared_2039_ = v_isSharedCheck_2043_;
goto v_resetjp_2037_;
}
else
{
lean_inc(v_a_2036_);
lean_dec(v___x_1920_);
v___x_2038_ = lean_box(0);
v_isShared_2039_ = v_isSharedCheck_2043_;
goto v_resetjp_2037_;
}
v_resetjp_2037_:
{
lean_object* v___x_2041_; 
if (v_isShared_2039_ == 0)
{
v___x_2041_ = v___x_2038_;
goto v_reusejp_2040_;
}
else
{
lean_object* v_reuseFailAlloc_2042_; 
v_reuseFailAlloc_2042_ = lean_alloc_ctor(1, 1, 0);
lean_ctor_set(v_reuseFailAlloc_2042_, 0, v_a_2036_);
v___x_2041_ = v_reuseFailAlloc_2042_;
goto v_reusejp_2040_;
}
v_reusejp_2040_:
{
return v___x_2041_;
}
}
}
}
else
{
lean_object* v_a_2044_; lean_object* v___x_2046_; uint8_t v_isShared_2047_; uint8_t v_isSharedCheck_2051_; 
lean_dec_ref(v___x_1915_);
lean_dec_ref(v___x_1914_);
lean_dec(v_b_1904_);
v_a_2044_ = lean_ctor_get(v___x_1917_, 0);
v_isSharedCheck_2051_ = !lean_is_exclusive(v___x_1917_);
if (v_isSharedCheck_2051_ == 0)
{
v___x_2046_ = v___x_1917_;
v_isShared_2047_ = v_isSharedCheck_2051_;
goto v_resetjp_2045_;
}
else
{
lean_inc(v_a_2044_);
lean_dec(v___x_1917_);
v___x_2046_ = lean_box(0);
v_isShared_2047_ = v_isSharedCheck_2051_;
goto v_resetjp_2045_;
}
v_resetjp_2045_:
{
lean_object* v___x_2049_; 
if (v_isShared_2047_ == 0)
{
v___x_2049_ = v___x_2046_;
goto v_reusejp_2048_;
}
else
{
lean_object* v_reuseFailAlloc_2050_; 
v_reuseFailAlloc_2050_ = lean_alloc_ctor(1, 1, 0);
lean_ctor_set(v_reuseFailAlloc_2050_, 0, v_a_2044_);
v___x_2049_ = v_reuseFailAlloc_2050_;
goto v_reusejp_2048_;
}
v_reusejp_2048_:
{
return v___x_2049_;
}
}
}
}
else
{
lean_object* v_a_2052_; lean_object* v___x_2054_; uint8_t v_isShared_2055_; uint8_t v_isSharedCheck_2059_; 
lean_dec(v_b_1904_);
v_a_2052_ = lean_ctor_get(v___x_1909_, 0);
v_isSharedCheck_2059_ = !lean_is_exclusive(v___x_1909_);
if (v_isSharedCheck_2059_ == 0)
{
v___x_2054_ = v___x_1909_;
v_isShared_2055_ = v_isSharedCheck_2059_;
goto v_resetjp_2053_;
}
else
{
lean_inc(v_a_2052_);
lean_dec(v___x_1909_);
v___x_2054_ = lean_box(0);
v_isShared_2055_ = v_isSharedCheck_2059_;
goto v_resetjp_2053_;
}
v_resetjp_2053_:
{
lean_object* v___x_2057_; 
if (v_isShared_2055_ == 0)
{
v___x_2057_ = v___x_2054_;
goto v_reusejp_2056_;
}
else
{
lean_object* v_reuseFailAlloc_2058_; 
v_reuseFailAlloc_2058_ = lean_alloc_ctor(1, 1, 0);
lean_ctor_set(v_reuseFailAlloc_2058_, 0, v_a_2052_);
v___x_2057_ = v_reuseFailAlloc_2058_;
goto v_reusejp_2056_;
}
v_reusejp_2056_:
{
return v___x_2057_;
}
}
}
}
}
}
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotBankHarness_verify_spec__0___boxed(lean_object* v_as_2060_, lean_object* v_sz_2061_, lean_object* v_i_2062_, lean_object* v_b_2063_, lean_object* v___y_2064_){
_start:
{
size_t v_sz_boxed_2065_; size_t v_i_boxed_2066_; lean_object* v_res_2067_; 
v_sz_boxed_2065_ = lean_unbox_usize(v_sz_2061_);
lean_dec(v_sz_2061_);
v_i_boxed_2066_ = lean_unbox_usize(v_i_2062_);
lean_dec(v_i_2062_);
v_res_2067_ = lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotBankHarness_verify_spec__0(v_as_2060_, v_sz_boxed_2065_, v_i_boxed_2066_, v_b_2063_);
lean_dec_ref(v_as_2060_);
return v_res_2067_;
}
}
LEAN_EXPORT lean_object* lp_competition_R24DotBankHarness_verify(lean_object* v_plan_2070_){
_start:
{
lean_object* v_total_2072_; size_t v_sz_2073_; size_t v___x_2074_; lean_object* v___x_2075_; 
v_total_2072_ = lean_unsigned_to_nat(0u);
v_sz_2073_ = lean_array_size(v_plan_2070_);
v___x_2074_ = ((size_t)0ULL);
v___x_2075_ = lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotBankHarness_verify_spec__0(v_plan_2070_, v_sz_2073_, v___x_2074_, v_total_2072_);
if (lean_obj_tag(v___x_2075_) == 0)
{
lean_object* v_a_2076_; lean_object* v___x_2077_; lean_object* v___x_2078_; lean_object* v___x_2079_; lean_object* v___x_2080_; lean_object* v___x_2081_; lean_object* v___x_2082_; lean_object* v___x_2083_; lean_object* v___x_2084_; lean_object* v___x_2085_; lean_object* v___x_2086_; lean_object* v___x_2087_; 
v_a_2076_ = lean_ctor_get(v___x_2075_, 0);
lean_inc(v_a_2076_);
lean_dec_ref_known(v___x_2075_, 1);
v___x_2077_ = ((lean_object*)(lp_competition_R24DotBankHarness_verify___closed__0));
v___x_2078_ = lean_array_get_size(v_plan_2070_);
v___x_2079_ = l_Nat_reprFast(v___x_2078_);
v___x_2080_ = lean_string_append(v___x_2077_, v___x_2079_);
lean_dec_ref(v___x_2079_);
v___x_2081_ = ((lean_object*)(lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotBankHarness_emit_spec__0___closed__1));
v___x_2082_ = lean_string_append(v___x_2080_, v___x_2081_);
v___x_2083_ = l_Nat_reprFast(v_a_2076_);
v___x_2084_ = lean_string_append(v___x_2082_, v___x_2083_);
lean_dec_ref(v___x_2083_);
v___x_2085_ = ((lean_object*)(lp_competition_R24DotBankHarness_verify___closed__1));
v___x_2086_ = lean_string_append(v___x_2084_, v___x_2085_);
v___x_2087_ = lp_batteries_IO_println___at___00Batteries_Tactic_Lint_lintCore_spec__4(v___x_2086_);
return v___x_2087_;
}
else
{
lean_object* v_a_2088_; lean_object* v___x_2090_; uint8_t v_isShared_2091_; uint8_t v_isSharedCheck_2095_; 
v_a_2088_ = lean_ctor_get(v___x_2075_, 0);
v_isSharedCheck_2095_ = !lean_is_exclusive(v___x_2075_);
if (v_isSharedCheck_2095_ == 0)
{
v___x_2090_ = v___x_2075_;
v_isShared_2091_ = v_isSharedCheck_2095_;
goto v_resetjp_2089_;
}
else
{
lean_inc(v_a_2088_);
lean_dec(v___x_2075_);
v___x_2090_ = lean_box(0);
v_isShared_2091_ = v_isSharedCheck_2095_;
goto v_resetjp_2089_;
}
v_resetjp_2089_:
{
lean_object* v___x_2093_; 
if (v_isShared_2091_ == 0)
{
v___x_2093_ = v___x_2090_;
goto v_reusejp_2092_;
}
else
{
lean_object* v_reuseFailAlloc_2094_; 
v_reuseFailAlloc_2094_ = lean_alloc_ctor(1, 1, 0);
lean_ctor_set(v_reuseFailAlloc_2094_, 0, v_a_2088_);
v___x_2093_ = v_reuseFailAlloc_2094_;
goto v_reusejp_2092_;
}
v_reusejp_2092_:
{
return v___x_2093_;
}
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_R24DotBankHarness_verify___boxed(lean_object* v_plan_2096_, lean_object* v_a_2097_){
_start:
{
lean_object* v_res_2098_; 
v_res_2098_ = lp_competition_R24DotBankHarness_verify(v_plan_2096_);
lean_dec_ref(v_plan_2096_);
return v_res_2098_;
}
}
LEAN_EXPORT lean_object* lp_competition_R24DotBankHarness_env(lean_object* v_name_2100_){
_start:
{
lean_object* v___x_2102_; 
v___x_2102_ = lean_io_getenv(v_name_2100_);
if (lean_obj_tag(v___x_2102_) == 1)
{
lean_object* v_val_2103_; lean_object* v___x_2105_; uint8_t v_isShared_2106_; uint8_t v_isSharedCheck_2110_; 
v_val_2103_ = lean_ctor_get(v___x_2102_, 0);
v_isSharedCheck_2110_ = !lean_is_exclusive(v___x_2102_);
if (v_isSharedCheck_2110_ == 0)
{
v___x_2105_ = v___x_2102_;
v_isShared_2106_ = v_isSharedCheck_2110_;
goto v_resetjp_2104_;
}
else
{
lean_inc(v_val_2103_);
lean_dec(v___x_2102_);
v___x_2105_ = lean_box(0);
v_isShared_2106_ = v_isSharedCheck_2110_;
goto v_resetjp_2104_;
}
v_resetjp_2104_:
{
lean_object* v___x_2108_; 
if (v_isShared_2106_ == 0)
{
lean_ctor_set_tag(v___x_2105_, 0);
v___x_2108_ = v___x_2105_;
goto v_reusejp_2107_;
}
else
{
lean_object* v_reuseFailAlloc_2109_; 
v_reuseFailAlloc_2109_ = lean_alloc_ctor(0, 1, 0);
lean_ctor_set(v_reuseFailAlloc_2109_, 0, v_val_2103_);
v___x_2108_ = v_reuseFailAlloc_2109_;
goto v_reusejp_2107_;
}
v_reusejp_2107_:
{
return v___x_2108_;
}
}
}
else
{
lean_object* v___x_2111_; lean_object* v___x_2112_; lean_object* v___x_2113_; lean_object* v___x_2114_; 
lean_dec(v___x_2102_);
v___x_2111_ = ((lean_object*)(lp_competition_R24DotBankHarness_env___closed__0));
v___x_2112_ = lean_string_append(v___x_2111_, v_name_2100_);
v___x_2113_ = lean_alloc_ctor(18, 1, 0);
lean_ctor_set(v___x_2113_, 0, v___x_2112_);
v___x_2114_ = lean_alloc_ctor(1, 1, 0);
lean_ctor_set(v___x_2114_, 0, v___x_2113_);
return v___x_2114_;
}
}
}
LEAN_EXPORT lean_object* lp_competition_R24DotBankHarness_env___boxed(lean_object* v_name_2115_, lean_object* v_a_2116_){
_start:
{
lean_object* v_res_2117_; 
v_res_2117_ = lp_competition_R24DotBankHarness_env(v_name_2115_);
lean_dec_ref(v_name_2115_);
return v_res_2117_;
}
}
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotBankHarness_run_spec__0___lam__0(lean_object* v_a_2118_, lean_object* v_x_2119_){
_start:
{
lean_object* v_rowsA_2120_; lean_object* v___x_2121_; 
v_rowsA_2120_ = lean_ctor_get(v_a_2118_, 5);
lean_inc_ref(v_rowsA_2120_);
lean_dec_ref(v_a_2118_);
v___x_2121_ = lp_competition_R24DotBankHarness_words(v_rowsA_2120_);
return v___x_2121_;
}
}
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotBankHarness_run_spec__0___lam__1(lean_object* v_a_2122_, lean_object* v_x_2123_){
_start:
{
lean_object* v_rowsB_2124_; lean_object* v___x_2125_; 
v_rowsB_2124_ = lean_ctor_get(v_a_2122_, 6);
lean_inc_ref(v_rowsB_2124_);
lean_dec_ref(v_a_2122_);
v___x_2125_ = lp_competition_R24DotBankHarness_words(v_rowsB_2124_);
return v___x_2125_;
}
}
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotBankHarness_run_spec__0(lean_object* v_a_2126_, lean_object* v_a_2127_, lean_object* v_val_2128_, lean_object* v_as_2129_, size_t v_sz_2130_, size_t v_i_2131_, lean_object* v_b_2132_){
_start:
{
lean_object* v_a_2135_; uint8_t v___x_2142_; 
v___x_2142_ = lean_usize_dec_lt(v_i_2131_, v_sz_2130_);
if (v___x_2142_ == 0)
{
lean_object* v___x_2143_; 
v___x_2143_ = lean_alloc_ctor(0, 1, 0);
lean_ctor_set(v___x_2143_, 0, v_b_2132_);
return v___x_2143_;
}
else
{
lean_object* v_a_2144_; lean_object* v_group_2145_; lean_object* v_expected_2146_; uint8_t v___x_2147_; 
v_a_2144_ = lean_array_uget_borrowed(v_as_2129_, v_i_2131_);
v_group_2145_ = lean_ctor_get(v_a_2144_, 1);
v_expected_2146_ = lean_ctor_get(v_a_2144_, 7);
v___x_2147_ = lean_string_dec_eq(v_group_2145_, v_a_2126_);
if (v___x_2147_ == 0)
{
v_a_2135_ = v_b_2132_;
goto v___jp_2134_;
}
else
{
lean_object* v___x_2148_; 
lean_inc(v_a_2144_);
v___x_2148_ = lp_competition_R24DotBankHarness_checkCase(v_a_2144_);
if (lean_obj_tag(v___x_2148_) == 0)
{
lean_object* v___f_2149_; lean_object* v___x_2150_; 
lean_dec_ref_known(v___x_2148_, 1);
lean_inc(v_a_2144_);
v___f_2149_ = lean_alloc_closure((void*)(lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotBankHarness_run_spec__0___lam__0), 2, 1);
lean_closure_set(v___f_2149_, 0, v_a_2144_);
v___x_2150_ = l_IO_lazyPure___redArg(v___f_2149_);
if (lean_obj_tag(v___x_2150_) == 0)
{
lean_object* v_a_2151_; lean_object* v___f_2152_; lean_object* v___x_2153_; 
v_a_2151_ = lean_ctor_get(v___x_2150_, 0);
lean_inc(v_a_2151_);
lean_dec_ref_known(v___x_2150_, 1);
lean_inc(v_a_2144_);
v___f_2152_ = lean_alloc_closure((void*)(lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotBankHarness_run_spec__0___lam__1), 2, 1);
lean_closure_set(v___f_2152_, 0, v_a_2144_);
v___x_2153_ = l_IO_lazyPure___redArg(v___f_2152_);
if (lean_obj_tag(v___x_2153_) == 0)
{
lean_object* v_a_2154_; lean_object* v___x_2155_; uint32_t v___x_2156_; lean_object* v___x_2157_; uint8_t v___x_2158_; 
v_a_2154_ = lean_ctor_get(v___x_2153_, 0);
lean_inc(v_a_2154_);
lean_dec_ref_known(v___x_2153_, 1);
lean_inc_ref(v_expected_2146_);
v___x_2155_ = lp_competition_R24DotBankHarness_outputWords(v_expected_2146_);
v___x_2156_ = lp_competition_R24DotBankHarness_hashAll(v___x_2155_);
lean_dec_ref(v___x_2155_);
v___x_2157_ = ((lean_object*)(lp_competition_R24DotBankHarness_benchExact___closed__2));
v___x_2158_ = lean_string_dec_eq(v_a_2127_, v___x_2157_);
if (v___x_2158_ == 0)
{
lean_object* v___x_2159_; uint8_t v___x_2160_; 
v___x_2159_ = ((lean_object*)(lp_competition_R24DotBankHarness_benchEager___closed__0));
v___x_2160_ = lean_string_dec_eq(v_a_2127_, v___x_2159_);
if (v___x_2160_ == 0)
{
lean_object* v___x_2161_; 
lean_inc(v_a_2144_);
v___x_2161_ = lp_competition_R24DotBankHarness_benchLazy(v_a_2144_, v_a_2151_, v_a_2154_, v_val_2128_, v___x_2156_);
if (lean_obj_tag(v___x_2161_) == 0)
{
lean_dec_ref_known(v___x_2161_, 1);
goto v___jp_2139_;
}
else
{
lean_object* v_a_2162_; lean_object* v___x_2164_; uint8_t v_isShared_2165_; uint8_t v_isSharedCheck_2169_; 
lean_dec(v_b_2132_);
v_a_2162_ = lean_ctor_get(v___x_2161_, 0);
v_isSharedCheck_2169_ = !lean_is_exclusive(v___x_2161_);
if (v_isSharedCheck_2169_ == 0)
{
v___x_2164_ = v___x_2161_;
v_isShared_2165_ = v_isSharedCheck_2169_;
goto v_resetjp_2163_;
}
else
{
lean_inc(v_a_2162_);
lean_dec(v___x_2161_);
v___x_2164_ = lean_box(0);
v_isShared_2165_ = v_isSharedCheck_2169_;
goto v_resetjp_2163_;
}
v_resetjp_2163_:
{
lean_object* v___x_2167_; 
if (v_isShared_2165_ == 0)
{
v___x_2167_ = v___x_2164_;
goto v_reusejp_2166_;
}
else
{
lean_object* v_reuseFailAlloc_2168_; 
v_reuseFailAlloc_2168_ = lean_alloc_ctor(1, 1, 0);
lean_ctor_set(v_reuseFailAlloc_2168_, 0, v_a_2162_);
v___x_2167_ = v_reuseFailAlloc_2168_;
goto v_reusejp_2166_;
}
v_reusejp_2166_:
{
return v___x_2167_;
}
}
}
}
else
{
lean_object* v___x_2170_; 
lean_inc(v_a_2144_);
v___x_2170_ = lp_competition_R24DotBankHarness_benchEager(v_a_2144_, v_a_2151_, v_a_2154_, v_val_2128_, v___x_2156_);
if (lean_obj_tag(v___x_2170_) == 0)
{
lean_dec_ref_known(v___x_2170_, 1);
goto v___jp_2139_;
}
else
{
lean_object* v_a_2171_; lean_object* v___x_2173_; uint8_t v_isShared_2174_; uint8_t v_isSharedCheck_2178_; 
lean_dec(v_b_2132_);
v_a_2171_ = lean_ctor_get(v___x_2170_, 0);
v_isSharedCheck_2178_ = !lean_is_exclusive(v___x_2170_);
if (v_isSharedCheck_2178_ == 0)
{
v___x_2173_ = v___x_2170_;
v_isShared_2174_ = v_isSharedCheck_2178_;
goto v_resetjp_2172_;
}
else
{
lean_inc(v_a_2171_);
lean_dec(v___x_2170_);
v___x_2173_ = lean_box(0);
v_isShared_2174_ = v_isSharedCheck_2178_;
goto v_resetjp_2172_;
}
v_resetjp_2172_:
{
lean_object* v___x_2176_; 
if (v_isShared_2174_ == 0)
{
v___x_2176_ = v___x_2173_;
goto v_reusejp_2175_;
}
else
{
lean_object* v_reuseFailAlloc_2177_; 
v_reuseFailAlloc_2177_ = lean_alloc_ctor(1, 1, 0);
lean_ctor_set(v_reuseFailAlloc_2177_, 0, v_a_2171_);
v___x_2176_ = v_reuseFailAlloc_2177_;
goto v_reusejp_2175_;
}
v_reusejp_2175_:
{
return v___x_2176_;
}
}
}
}
}
else
{
lean_object* v___x_2179_; 
lean_inc(v_a_2144_);
v___x_2179_ = lp_competition_R24DotBankHarness_benchExact(v_a_2144_, v_a_2151_, v_a_2154_, v_val_2128_, v___x_2156_);
if (lean_obj_tag(v___x_2179_) == 0)
{
lean_dec_ref_known(v___x_2179_, 1);
goto v___jp_2139_;
}
else
{
lean_object* v_a_2180_; lean_object* v___x_2182_; uint8_t v_isShared_2183_; uint8_t v_isSharedCheck_2187_; 
lean_dec(v_b_2132_);
v_a_2180_ = lean_ctor_get(v___x_2179_, 0);
v_isSharedCheck_2187_ = !lean_is_exclusive(v___x_2179_);
if (v_isSharedCheck_2187_ == 0)
{
v___x_2182_ = v___x_2179_;
v_isShared_2183_ = v_isSharedCheck_2187_;
goto v_resetjp_2181_;
}
else
{
lean_inc(v_a_2180_);
lean_dec(v___x_2179_);
v___x_2182_ = lean_box(0);
v_isShared_2183_ = v_isSharedCheck_2187_;
goto v_resetjp_2181_;
}
v_resetjp_2181_:
{
lean_object* v___x_2185_; 
if (v_isShared_2183_ == 0)
{
v___x_2185_ = v___x_2182_;
goto v_reusejp_2184_;
}
else
{
lean_object* v_reuseFailAlloc_2186_; 
v_reuseFailAlloc_2186_ = lean_alloc_ctor(1, 1, 0);
lean_ctor_set(v_reuseFailAlloc_2186_, 0, v_a_2180_);
v___x_2185_ = v_reuseFailAlloc_2186_;
goto v_reusejp_2184_;
}
v_reusejp_2184_:
{
return v___x_2185_;
}
}
}
}
}
else
{
lean_object* v_a_2188_; lean_object* v___x_2190_; uint8_t v_isShared_2191_; uint8_t v_isSharedCheck_2195_; 
lean_dec(v_a_2151_);
lean_dec(v_b_2132_);
v_a_2188_ = lean_ctor_get(v___x_2153_, 0);
v_isSharedCheck_2195_ = !lean_is_exclusive(v___x_2153_);
if (v_isSharedCheck_2195_ == 0)
{
v___x_2190_ = v___x_2153_;
v_isShared_2191_ = v_isSharedCheck_2195_;
goto v_resetjp_2189_;
}
else
{
lean_inc(v_a_2188_);
lean_dec(v___x_2153_);
v___x_2190_ = lean_box(0);
v_isShared_2191_ = v_isSharedCheck_2195_;
goto v_resetjp_2189_;
}
v_resetjp_2189_:
{
lean_object* v___x_2193_; 
if (v_isShared_2191_ == 0)
{
v___x_2193_ = v___x_2190_;
goto v_reusejp_2192_;
}
else
{
lean_object* v_reuseFailAlloc_2194_; 
v_reuseFailAlloc_2194_ = lean_alloc_ctor(1, 1, 0);
lean_ctor_set(v_reuseFailAlloc_2194_, 0, v_a_2188_);
v___x_2193_ = v_reuseFailAlloc_2194_;
goto v_reusejp_2192_;
}
v_reusejp_2192_:
{
return v___x_2193_;
}
}
}
}
else
{
lean_object* v_a_2196_; lean_object* v___x_2198_; uint8_t v_isShared_2199_; uint8_t v_isSharedCheck_2203_; 
lean_dec(v_b_2132_);
v_a_2196_ = lean_ctor_get(v___x_2150_, 0);
v_isSharedCheck_2203_ = !lean_is_exclusive(v___x_2150_);
if (v_isSharedCheck_2203_ == 0)
{
v___x_2198_ = v___x_2150_;
v_isShared_2199_ = v_isSharedCheck_2203_;
goto v_resetjp_2197_;
}
else
{
lean_inc(v_a_2196_);
lean_dec(v___x_2150_);
v___x_2198_ = lean_box(0);
v_isShared_2199_ = v_isSharedCheck_2203_;
goto v_resetjp_2197_;
}
v_resetjp_2197_:
{
lean_object* v___x_2201_; 
if (v_isShared_2199_ == 0)
{
v___x_2201_ = v___x_2198_;
goto v_reusejp_2200_;
}
else
{
lean_object* v_reuseFailAlloc_2202_; 
v_reuseFailAlloc_2202_ = lean_alloc_ctor(1, 1, 0);
lean_ctor_set(v_reuseFailAlloc_2202_, 0, v_a_2196_);
v___x_2201_ = v_reuseFailAlloc_2202_;
goto v_reusejp_2200_;
}
v_reusejp_2200_:
{
return v___x_2201_;
}
}
}
}
else
{
lean_object* v_a_2204_; lean_object* v___x_2206_; uint8_t v_isShared_2207_; uint8_t v_isSharedCheck_2211_; 
lean_dec(v_b_2132_);
v_a_2204_ = lean_ctor_get(v___x_2148_, 0);
v_isSharedCheck_2211_ = !lean_is_exclusive(v___x_2148_);
if (v_isSharedCheck_2211_ == 0)
{
v___x_2206_ = v___x_2148_;
v_isShared_2207_ = v_isSharedCheck_2211_;
goto v_resetjp_2205_;
}
else
{
lean_inc(v_a_2204_);
lean_dec(v___x_2148_);
v___x_2206_ = lean_box(0);
v_isShared_2207_ = v_isSharedCheck_2211_;
goto v_resetjp_2205_;
}
v_resetjp_2205_:
{
lean_object* v___x_2209_; 
if (v_isShared_2207_ == 0)
{
v___x_2209_ = v___x_2206_;
goto v_reusejp_2208_;
}
else
{
lean_object* v_reuseFailAlloc_2210_; 
v_reuseFailAlloc_2210_ = lean_alloc_ctor(1, 1, 0);
lean_ctor_set(v_reuseFailAlloc_2210_, 0, v_a_2204_);
v___x_2209_ = v_reuseFailAlloc_2210_;
goto v_reusejp_2208_;
}
v_reusejp_2208_:
{
return v___x_2209_;
}
}
}
}
}
v___jp_2134_:
{
size_t v___x_2136_; size_t v___x_2137_; 
v___x_2136_ = ((size_t)1ULL);
v___x_2137_ = lean_usize_add(v_i_2131_, v___x_2136_);
v_i_2131_ = v___x_2137_;
v_b_2132_ = v_a_2135_;
goto _start;
}
v___jp_2139_:
{
lean_object* v___x_2140_; lean_object* v___x_2141_; 
v___x_2140_ = lean_unsigned_to_nat(1u);
v___x_2141_ = lean_nat_add(v_b_2132_, v___x_2140_);
lean_dec(v_b_2132_);
v_a_2135_ = v___x_2141_;
goto v___jp_2134_;
}
}
}
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotBankHarness_run_spec__0___boxed(lean_object* v_a_2212_, lean_object* v_a_2213_, lean_object* v_val_2214_, lean_object* v_as_2215_, lean_object* v_sz_2216_, lean_object* v_i_2217_, lean_object* v_b_2218_, lean_object* v___y_2219_){
_start:
{
size_t v_sz_boxed_2220_; size_t v_i_boxed_2221_; lean_object* v_res_2222_; 
v_sz_boxed_2220_ = lean_unbox_usize(v_sz_2216_);
lean_dec(v_sz_2216_);
v_i_boxed_2221_ = lean_unbox_usize(v_i_2217_);
lean_dec(v_i_2217_);
v_res_2222_ = lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotBankHarness_run_spec__0(v_a_2212_, v_a_2213_, v_val_2214_, v_as_2215_, v_sz_boxed_2220_, v_i_boxed_2221_, v_b_2218_);
lean_dec_ref(v_as_2215_);
lean_dec(v_val_2214_);
lean_dec_ref(v_a_2213_);
lean_dec_ref(v_a_2212_);
return v_res_2222_;
}
}
LEAN_EXPORT lean_object* lp_competition_R24DotBankHarness_run(){
_start:
{
lean_object* v___x_2256_; lean_object* v___x_2257_; 
v___x_2256_ = ((lean_object*)(lp_competition_R24DotBankHarness_run___closed__0));
v___x_2257_ = lp_competition_R24DotBankHarness_env(v___x_2256_);
if (lean_obj_tag(v___x_2257_) == 0)
{
lean_object* v_a_2258_; lean_object* v___x_2260_; uint8_t v_isShared_2261_; uint8_t v_isSharedCheck_2474_; 
v_a_2258_ = lean_ctor_get(v___x_2257_, 0);
v_isSharedCheck_2474_ = !lean_is_exclusive(v___x_2257_);
if (v_isSharedCheck_2474_ == 0)
{
v___x_2260_ = v___x_2257_;
v_isShared_2261_ = v_isSharedCheck_2474_;
goto v_resetjp_2259_;
}
else
{
lean_inc(v_a_2258_);
lean_dec(v___x_2257_);
v___x_2260_ = lean_box(0);
v_isShared_2261_ = v_isSharedCheck_2474_;
goto v_resetjp_2259_;
}
v_resetjp_2259_:
{
lean_object* v___x_2262_; 
v___x_2262_ = l_IO_FS_readFile(v_a_2258_);
lean_dec(v_a_2258_);
if (lean_obj_tag(v___x_2262_) == 0)
{
lean_object* v_a_2263_; lean_object* v___x_2265_; uint8_t v_isShared_2266_; uint8_t v_isSharedCheck_2465_; 
v_a_2263_ = lean_ctor_get(v___x_2262_, 0);
v_isSharedCheck_2465_ = !lean_is_exclusive(v___x_2262_);
if (v_isSharedCheck_2465_ == 0)
{
v___x_2265_ = v___x_2262_;
v_isShared_2266_ = v_isSharedCheck_2465_;
goto v_resetjp_2264_;
}
else
{
lean_inc(v_a_2263_);
lean_dec(v___x_2262_);
v___x_2265_ = lean_box(0);
v_isShared_2266_ = v_isSharedCheck_2465_;
goto v_resetjp_2264_;
}
v_resetjp_2264_:
{
lean_object* v_a_2268_; lean_object* v___x_2275_; 
v___x_2275_ = l_Lean_Json_parse(v_a_2263_);
if (lean_obj_tag(v___x_2275_) == 0)
{
lean_object* v_a_2276_; 
lean_del_object(v___x_2260_);
v_a_2276_ = lean_ctor_get(v___x_2275_, 0);
lean_inc(v_a_2276_);
lean_dec_ref_known(v___x_2275_, 1);
v_a_2268_ = v_a_2276_;
goto v___jp_2267_;
}
else
{
lean_object* v_a_2277_; lean_object* v___x_2279_; uint8_t v_isShared_2280_; uint8_t v_isSharedCheck_2464_; 
v_a_2277_ = lean_ctor_get(v___x_2275_, 0);
v_isSharedCheck_2464_ = !lean_is_exclusive(v___x_2275_);
if (v_isSharedCheck_2464_ == 0)
{
v___x_2279_ = v___x_2275_;
v_isShared_2280_ = v_isSharedCheck_2464_;
goto v_resetjp_2278_;
}
else
{
lean_inc(v_a_2277_);
lean_dec(v___x_2275_);
v___x_2279_ = lean_box(0);
v_isShared_2280_ = v_isSharedCheck_2464_;
goto v_resetjp_2278_;
}
v_resetjp_2278_:
{
lean_object* v___x_2281_; 
v___x_2281_ = lp_competition_R24DotBankHarness_instFromJsonPlan_fromJson(v_a_2277_);
if (lean_obj_tag(v___x_2281_) == 0)
{
lean_object* v_a_2282_; 
lean_del_object(v___x_2279_);
lean_del_object(v___x_2260_);
v_a_2282_ = lean_ctor_get(v___x_2281_, 0);
lean_inc(v_a_2282_);
lean_dec_ref_known(v___x_2281_, 1);
v_a_2268_ = v_a_2282_;
goto v___jp_2267_;
}
else
{
lean_object* v_a_2283_; lean_object* v___x_2285_; uint8_t v_isShared_2286_; uint8_t v_isSharedCheck_2463_; 
lean_del_object(v___x_2265_);
v_a_2283_ = lean_ctor_get(v___x_2281_, 0);
v_isSharedCheck_2463_ = !lean_is_exclusive(v___x_2281_);
if (v_isSharedCheck_2463_ == 0)
{
v___x_2285_ = v___x_2281_;
v_isShared_2286_ = v_isSharedCheck_2463_;
goto v_resetjp_2284_;
}
else
{
lean_inc(v_a_2283_);
lean_dec(v___x_2281_);
v___x_2285_ = lean_box(0);
v_isShared_2286_ = v_isSharedCheck_2463_;
goto v_resetjp_2284_;
}
v_resetjp_2284_:
{
lean_object* v___y_2288_; lean_object* v___y_2289_; lean_object* v___y_2290_; lean_object* v___y_2348_; lean_object* v___y_2349_; lean_object* v___y_2350_; lean_object* v___y_2362_; lean_object* v___y_2363_; lean_object* v___y_2364_; lean_object* v___y_2372_; lean_object* v___y_2373_; uint8_t v___y_2374_; lean_object* v___y_2375_; uint8_t v___y_2376_; uint8_t v___y_2380_; lean_object* v___y_2381_; lean_object* v___y_2382_; lean_object* v___y_2383_; uint8_t v___y_2384_; uint8_t v___y_2388_; uint8_t v___y_2389_; lean_object* v___y_2390_; lean_object* v___y_2391_; lean_object* v___y_2392_; uint8_t v___y_2393_; uint8_t v___y_2399_; uint8_t v___y_2400_; lean_object* v___y_2401_; lean_object* v___y_2402_; lean_object* v___y_2403_; lean_object* v___x_2406_; lean_object* v___x_2407_; lean_object* v___y_2412_; 
v___x_2406_ = ((lean_object*)(lp_competition_R24DotBankHarness_run___closed__18));
v___x_2407_ = lean_io_getenv(v___x_2406_);
if (lean_obj_tag(v___x_2407_) == 0)
{
lean_object* v___x_2461_; 
v___x_2461_ = ((lean_object*)(lp_competition_R24DotBankHarness_run___closed__21));
v___y_2412_ = v___x_2461_;
goto v___jp_2411_;
}
else
{
lean_object* v_val_2462_; 
v_val_2462_ = lean_ctor_get(v___x_2407_, 0);
lean_inc(v_val_2462_);
lean_dec_ref_known(v___x_2407_, 1);
v___y_2412_ = v_val_2462_;
goto v___jp_2411_;
}
v___jp_2287_:
{
lean_object* v___x_2291_; lean_object* v___x_2292_; lean_object* v___x_2293_; lean_object* v___x_2294_; 
v___x_2291_ = lean_unsigned_to_nat(0u);
v___x_2292_ = lean_string_utf8_byte_size(v___y_2290_);
v___x_2293_ = lean_alloc_ctor(0, 3, 0);
lean_ctor_set(v___x_2293_, 0, v___y_2290_);
lean_ctor_set(v___x_2293_, 1, v___x_2291_);
lean_ctor_set(v___x_2293_, 2, v___x_2292_);
v___x_2294_ = l_String_Slice_toNat_x3f(v___x_2293_);
lean_dec_ref_known(v___x_2293_, 3);
if (lean_obj_tag(v___x_2294_) == 1)
{
lean_object* v_val_2295_; lean_object* v___x_2296_; uint8_t v___x_2297_; 
v_val_2295_ = lean_ctor_get(v___x_2294_, 0);
lean_inc(v_val_2295_);
lean_dec_ref_known(v___x_2294_, 1);
v___x_2296_ = lean_unsigned_to_nat(16777216u);
v___x_2297_ = lean_nat_dec_lt(v___x_2296_, v_val_2295_);
if (v___x_2297_ == 0)
{
size_t v_sz_2298_; size_t v___x_2299_; lean_object* v___x_2300_; 
lean_del_object(v___x_2260_);
v_sz_2298_ = lean_array_size(v_a_2283_);
v___x_2299_ = ((size_t)0ULL);
v___x_2300_ = lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotBankHarness_run_spec__0(v___y_2289_, v___y_2288_, v_val_2295_, v_a_2283_, v_sz_2298_, v___x_2299_, v___x_2291_);
lean_dec(v_a_2283_);
lean_dec(v_val_2295_);
if (lean_obj_tag(v___x_2300_) == 0)
{
lean_object* v_a_2301_; lean_object* v___x_2302_; lean_object* v___x_2303_; lean_object* v___x_2304_; lean_object* v___x_2305_; lean_object* v___x_2306_; lean_object* v___x_2307_; lean_object* v___x_2308_; lean_object* v___x_2309_; lean_object* v___x_2310_; lean_object* v___x_2311_; lean_object* v___x_2312_; lean_object* v___x_2313_; 
v_a_2301_ = lean_ctor_get(v___x_2300_, 0);
lean_inc(v_a_2301_);
lean_dec_ref_known(v___x_2300_, 1);
v___x_2302_ = ((lean_object*)(lp_competition_R24DotBankHarness_run___closed__2));
v___x_2303_ = lean_string_append(v___x_2302_, v___y_2289_);
lean_dec_ref(v___y_2289_);
v___x_2304_ = ((lean_object*)(lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotBankHarness_emit_spec__0___closed__1));
v___x_2305_ = lean_string_append(v___x_2303_, v___x_2304_);
v___x_2306_ = lean_string_append(v___x_2305_, v___y_2288_);
lean_dec_ref(v___y_2288_);
v___x_2307_ = ((lean_object*)(lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00R24DotBankHarness_emit_spec__0___closed__2));
v___x_2308_ = lean_string_append(v___x_2306_, v___x_2307_);
v___x_2309_ = l_Nat_reprFast(v_a_2301_);
v___x_2310_ = lean_string_append(v___x_2308_, v___x_2309_);
lean_dec_ref(v___x_2309_);
v___x_2311_ = ((lean_object*)(lp_competition_R24DotBankHarness_verify___closed__1));
v___x_2312_ = lean_string_append(v___x_2310_, v___x_2311_);
v___x_2313_ = lp_batteries_IO_println___at___00Batteries_Tactic_Lint_lintCore_spec__4(v___x_2312_);
if (lean_obj_tag(v___x_2313_) == 0)
{
lean_object* v___x_2315_; uint8_t v_isShared_2316_; uint8_t v_isSharedCheck_2321_; 
v_isSharedCheck_2321_ = !lean_is_exclusive(v___x_2313_);
if (v_isSharedCheck_2321_ == 0)
{
lean_object* v_unused_2322_; 
v_unused_2322_ = lean_ctor_get(v___x_2313_, 0);
lean_dec(v_unused_2322_);
v___x_2315_ = v___x_2313_;
v_isShared_2316_ = v_isSharedCheck_2321_;
goto v_resetjp_2314_;
}
else
{
lean_dec(v___x_2313_);
v___x_2315_ = lean_box(0);
v_isShared_2316_ = v_isSharedCheck_2321_;
goto v_resetjp_2314_;
}
v_resetjp_2314_:
{
lean_object* v___x_2317_; lean_object* v___x_2319_; 
v___x_2317_ = lp_competition_R24DotBankHarness_sumRemaining___boxed__const__1;
if (v_isShared_2316_ == 0)
{
lean_ctor_set(v___x_2315_, 0, v___x_2317_);
v___x_2319_ = v___x_2315_;
goto v_reusejp_2318_;
}
else
{
lean_object* v_reuseFailAlloc_2320_; 
v_reuseFailAlloc_2320_ = lean_alloc_ctor(0, 1, 0);
lean_ctor_set(v_reuseFailAlloc_2320_, 0, v___x_2317_);
v___x_2319_ = v_reuseFailAlloc_2320_;
goto v_reusejp_2318_;
}
v_reusejp_2318_:
{
return v___x_2319_;
}
}
}
else
{
lean_object* v_a_2323_; lean_object* v___x_2325_; uint8_t v_isShared_2326_; uint8_t v_isSharedCheck_2330_; 
v_a_2323_ = lean_ctor_get(v___x_2313_, 0);
v_isSharedCheck_2330_ = !lean_is_exclusive(v___x_2313_);
if (v_isSharedCheck_2330_ == 0)
{
v___x_2325_ = v___x_2313_;
v_isShared_2326_ = v_isSharedCheck_2330_;
goto v_resetjp_2324_;
}
else
{
lean_inc(v_a_2323_);
lean_dec(v___x_2313_);
v___x_2325_ = lean_box(0);
v_isShared_2326_ = v_isSharedCheck_2330_;
goto v_resetjp_2324_;
}
v_resetjp_2324_:
{
lean_object* v___x_2328_; 
if (v_isShared_2326_ == 0)
{
v___x_2328_ = v___x_2325_;
goto v_reusejp_2327_;
}
else
{
lean_object* v_reuseFailAlloc_2329_; 
v_reuseFailAlloc_2329_ = lean_alloc_ctor(1, 1, 0);
lean_ctor_set(v_reuseFailAlloc_2329_, 0, v_a_2323_);
v___x_2328_ = v_reuseFailAlloc_2329_;
goto v_reusejp_2327_;
}
v_reusejp_2327_:
{
return v___x_2328_;
}
}
}
}
else
{
lean_object* v_a_2331_; lean_object* v___x_2333_; uint8_t v_isShared_2334_; uint8_t v_isSharedCheck_2338_; 
lean_dec_ref(v___y_2289_);
lean_dec_ref(v___y_2288_);
v_a_2331_ = lean_ctor_get(v___x_2300_, 0);
v_isSharedCheck_2338_ = !lean_is_exclusive(v___x_2300_);
if (v_isSharedCheck_2338_ == 0)
{
v___x_2333_ = v___x_2300_;
v_isShared_2334_ = v_isSharedCheck_2338_;
goto v_resetjp_2332_;
}
else
{
lean_inc(v_a_2331_);
lean_dec(v___x_2300_);
v___x_2333_ = lean_box(0);
v_isShared_2334_ = v_isSharedCheck_2338_;
goto v_resetjp_2332_;
}
v_resetjp_2332_:
{
lean_object* v___x_2336_; 
if (v_isShared_2334_ == 0)
{
v___x_2336_ = v___x_2333_;
goto v_reusejp_2335_;
}
else
{
lean_object* v_reuseFailAlloc_2337_; 
v_reuseFailAlloc_2337_ = lean_alloc_ctor(1, 1, 0);
lean_ctor_set(v_reuseFailAlloc_2337_, 0, v_a_2331_);
v___x_2336_ = v_reuseFailAlloc_2337_;
goto v_reusejp_2335_;
}
v_reusejp_2335_:
{
return v___x_2336_;
}
}
}
}
else
{
lean_object* v___x_2339_; lean_object* v___x_2341_; 
lean_dec(v_val_2295_);
lean_dec_ref(v___y_2289_);
lean_dec_ref(v___y_2288_);
lean_dec(v_a_2283_);
v___x_2339_ = ((lean_object*)(lp_competition_R24DotBankHarness_run___closed__4));
if (v_isShared_2261_ == 0)
{
lean_ctor_set_tag(v___x_2260_, 1);
lean_ctor_set(v___x_2260_, 0, v___x_2339_);
v___x_2341_ = v___x_2260_;
goto v_reusejp_2340_;
}
else
{
lean_object* v_reuseFailAlloc_2342_; 
v_reuseFailAlloc_2342_ = lean_alloc_ctor(1, 1, 0);
lean_ctor_set(v_reuseFailAlloc_2342_, 0, v___x_2339_);
v___x_2341_ = v_reuseFailAlloc_2342_;
goto v_reusejp_2340_;
}
v_reusejp_2340_:
{
return v___x_2341_;
}
}
}
else
{
lean_object* v___x_2343_; lean_object* v___x_2345_; 
lean_dec(v___x_2294_);
lean_dec_ref(v___y_2289_);
lean_dec_ref(v___y_2288_);
lean_dec(v_a_2283_);
v___x_2343_ = ((lean_object*)(lp_competition_R24DotBankHarness_run___closed__6));
if (v_isShared_2261_ == 0)
{
lean_ctor_set_tag(v___x_2260_, 1);
lean_ctor_set(v___x_2260_, 0, v___x_2343_);
v___x_2345_ = v___x_2260_;
goto v_reusejp_2344_;
}
else
{
lean_object* v_reuseFailAlloc_2346_; 
v_reuseFailAlloc_2346_ = lean_alloc_ctor(1, 1, 0);
lean_ctor_set(v_reuseFailAlloc_2346_, 0, v___x_2343_);
v___x_2345_ = v_reuseFailAlloc_2346_;
goto v_reusejp_2344_;
}
v_reusejp_2344_:
{
return v___x_2345_;
}
}
}
v___jp_2347_:
{
lean_object* v___x_2351_; uint8_t v___x_2352_; 
v___x_2351_ = ((lean_object*)(lp_competition_R24DotBankHarness_run___closed__7));
v___x_2352_ = lean_string_dec_eq(v___y_2348_, v___x_2351_);
lean_dec_ref(v___y_2348_);
if (v___x_2352_ == 0)
{
lean_object* v___x_2353_; lean_object* v___x_2355_; 
lean_dec_ref(v___y_2350_);
lean_dec_ref(v___y_2349_);
lean_dec(v_a_2283_);
lean_del_object(v___x_2260_);
v___x_2353_ = ((lean_object*)(lp_competition_R24DotBankHarness_run___closed__9));
if (v_isShared_2286_ == 0)
{
lean_ctor_set(v___x_2285_, 0, v___x_2353_);
v___x_2355_ = v___x_2285_;
goto v_reusejp_2354_;
}
else
{
lean_object* v_reuseFailAlloc_2356_; 
v_reuseFailAlloc_2356_ = lean_alloc_ctor(1, 1, 0);
lean_ctor_set(v_reuseFailAlloc_2356_, 0, v___x_2353_);
v___x_2355_ = v_reuseFailAlloc_2356_;
goto v_reusejp_2354_;
}
v_reusejp_2354_:
{
return v___x_2355_;
}
}
else
{
lean_object* v___x_2357_; lean_object* v___x_2358_; 
lean_del_object(v___x_2285_);
v___x_2357_ = ((lean_object*)(lp_competition_R24DotBankHarness_run___closed__10));
v___x_2358_ = lean_io_getenv(v___x_2357_);
if (lean_obj_tag(v___x_2358_) == 0)
{
lean_object* v___x_2359_; 
v___x_2359_ = ((lean_object*)(lp_competition_R24DotBankHarness_run___closed__11));
v___y_2288_ = v___y_2349_;
v___y_2289_ = v___y_2350_;
v___y_2290_ = v___x_2359_;
goto v___jp_2287_;
}
else
{
lean_object* v_val_2360_; 
v_val_2360_ = lean_ctor_get(v___x_2358_, 0);
lean_inc(v_val_2360_);
lean_dec_ref_known(v___x_2358_, 1);
v___y_2288_ = v___y_2349_;
v___y_2289_ = v___y_2350_;
v___y_2290_ = v_val_2360_;
goto v___jp_2287_;
}
}
}
v___jp_2361_:
{
lean_object* v___x_2365_; uint8_t v___x_2366_; 
v___x_2365_ = ((lean_object*)(lp_competition_R24DotBankHarness_benchLazy___closed__0));
v___x_2366_ = lean_string_dec_eq(v___y_2363_, v___x_2365_);
if (v___x_2366_ == 0)
{
lean_object* v___x_2367_; lean_object* v___x_2369_; 
lean_dec_ref(v___y_2364_);
lean_dec_ref(v___y_2363_);
lean_dec_ref(v___y_2362_);
lean_del_object(v___x_2285_);
lean_dec(v_a_2283_);
lean_del_object(v___x_2260_);
v___x_2367_ = ((lean_object*)(lp_competition_R24DotBankHarness_run___closed__13));
if (v_isShared_2280_ == 0)
{
lean_ctor_set(v___x_2279_, 0, v___x_2367_);
v___x_2369_ = v___x_2279_;
goto v_reusejp_2368_;
}
else
{
lean_object* v_reuseFailAlloc_2370_; 
v_reuseFailAlloc_2370_ = lean_alloc_ctor(1, 1, 0);
lean_ctor_set(v_reuseFailAlloc_2370_, 0, v___x_2367_);
v___x_2369_ = v_reuseFailAlloc_2370_;
goto v_reusejp_2368_;
}
v_reusejp_2368_:
{
return v___x_2369_;
}
}
else
{
lean_del_object(v___x_2279_);
v___y_2348_ = v___y_2362_;
v___y_2349_ = v___y_2363_;
v___y_2350_ = v___y_2364_;
goto v___jp_2347_;
}
}
v___jp_2371_:
{
if (v___y_2376_ == 0)
{
lean_del_object(v___x_2279_);
v___y_2348_ = v___y_2372_;
v___y_2349_ = v___y_2373_;
v___y_2350_ = v___y_2375_;
goto v___jp_2347_;
}
else
{
lean_object* v___x_2377_; uint8_t v___x_2378_; 
v___x_2377_ = ((lean_object*)(lp_competition_R24DotBankHarness_benchEager___closed__0));
v___x_2378_ = lean_string_dec_eq(v___y_2373_, v___x_2377_);
if (v___x_2378_ == 0)
{
v___y_2362_ = v___y_2372_;
v___y_2363_ = v___y_2373_;
v___y_2364_ = v___y_2375_;
goto v___jp_2361_;
}
else
{
if (v___y_2374_ == 0)
{
lean_del_object(v___x_2279_);
v___y_2348_ = v___y_2372_;
v___y_2349_ = v___y_2373_;
v___y_2350_ = v___y_2375_;
goto v___jp_2347_;
}
else
{
v___y_2362_ = v___y_2372_;
v___y_2363_ = v___y_2373_;
v___y_2364_ = v___y_2375_;
goto v___jp_2361_;
}
}
}
}
v___jp_2379_:
{
lean_object* v___x_2385_; uint8_t v___x_2386_; 
v___x_2385_ = ((lean_object*)(lp_competition_R24DotBankHarness_benchExact___closed__2));
v___x_2386_ = lean_string_dec_eq(v___y_2382_, v___x_2385_);
if (v___x_2386_ == 0)
{
v___y_2372_ = v___y_2381_;
v___y_2373_ = v___y_2382_;
v___y_2374_ = v___y_2384_;
v___y_2375_ = v___y_2383_;
v___y_2376_ = v___y_2380_;
goto v___jp_2371_;
}
else
{
v___y_2372_ = v___y_2381_;
v___y_2373_ = v___y_2382_;
v___y_2374_ = v___y_2384_;
v___y_2375_ = v___y_2383_;
v___y_2376_ = v___y_2384_;
goto v___jp_2371_;
}
}
v___jp_2387_:
{
if (v___y_2393_ == 0)
{
v___y_2380_ = v___y_2389_;
v___y_2381_ = v___y_2390_;
v___y_2382_ = v___y_2391_;
v___y_2383_ = v___y_2392_;
v___y_2384_ = v___y_2393_;
goto v___jp_2379_;
}
else
{
lean_object* v___x_2394_; uint8_t v___x_2395_; 
v___x_2394_ = ((lean_object*)(lp_competition_R24DotBankHarness_run___closed__14));
v___x_2395_ = lean_string_dec_eq(v___y_2392_, v___x_2394_);
if (v___x_2395_ == 0)
{
lean_object* v___x_2396_; lean_object* v___x_2397_; 
lean_dec_ref(v___y_2392_);
lean_dec_ref(v___y_2391_);
lean_dec_ref(v___y_2390_);
lean_del_object(v___x_2285_);
lean_dec(v_a_2283_);
lean_del_object(v___x_2279_);
lean_del_object(v___x_2260_);
v___x_2396_ = ((lean_object*)(lp_competition_R24DotBankHarness_run___closed__16));
v___x_2397_ = lean_alloc_ctor(1, 1, 0);
lean_ctor_set(v___x_2397_, 0, v___x_2396_);
return v___x_2397_;
}
else
{
v___y_2380_ = v___y_2389_;
v___y_2381_ = v___y_2390_;
v___y_2382_ = v___y_2391_;
v___y_2383_ = v___y_2392_;
v___y_2384_ = v___y_2388_;
goto v___jp_2379_;
}
}
}
v___jp_2398_:
{
lean_object* v___x_2404_; uint8_t v___x_2405_; 
v___x_2404_ = ((lean_object*)(lp_competition_R24DotBankHarness_run___closed__17));
v___x_2405_ = lean_string_dec_eq(v___y_2402_, v___x_2404_);
if (v___x_2405_ == 0)
{
v___y_2388_ = v___y_2399_;
v___y_2389_ = v___y_2400_;
v___y_2390_ = v___y_2403_;
v___y_2391_ = v___y_2401_;
v___y_2392_ = v___y_2402_;
v___y_2393_ = v___y_2400_;
goto v___jp_2387_;
}
else
{
v___y_2388_ = v___y_2399_;
v___y_2389_ = v___y_2400_;
v___y_2390_ = v___y_2403_;
v___y_2391_ = v___y_2401_;
v___y_2392_ = v___y_2402_;
v___y_2393_ = v___y_2399_;
goto v___jp_2387_;
}
}
v___jp_2408_:
{
lean_object* v___x_2409_; lean_object* v___x_2410_; 
v___x_2409_ = ((lean_object*)(lp_competition_R24DotBankHarness_run___closed__20));
v___x_2410_ = lean_alloc_ctor(1, 1, 0);
lean_ctor_set(v___x_2410_, 0, v___x_2409_);
return v___x_2410_;
}
v___jp_2411_:
{
lean_object* v___x_2413_; uint8_t v___x_2414_; 
v___x_2413_ = ((lean_object*)(lp_competition_R24DotBankHarness_run___closed__21));
v___x_2414_ = lean_string_dec_eq(v___y_2412_, v___x_2413_);
if (v___x_2414_ == 0)
{
lean_object* v___x_2415_; uint8_t v___x_2416_; 
v___x_2415_ = ((lean_object*)(lp_competition_R24DotBankHarness_run___closed__22));
v___x_2416_ = lean_string_dec_eq(v___y_2412_, v___x_2415_);
lean_dec_ref(v___y_2412_);
if (v___x_2416_ == 0)
{
lean_del_object(v___x_2285_);
lean_dec(v_a_2283_);
lean_del_object(v___x_2279_);
lean_del_object(v___x_2260_);
goto v___jp_2408_;
}
else
{
if (v___x_2414_ == 0)
{
lean_object* v___x_2417_; lean_object* v___x_2418_; 
v___x_2417_ = ((lean_object*)(lp_competition_R24DotBankHarness_run___closed__23));
v___x_2418_ = lp_competition_R24DotBankHarness_env(v___x_2417_);
if (lean_obj_tag(v___x_2418_) == 0)
{
lean_object* v_a_2419_; lean_object* v___x_2420_; lean_object* v___x_2421_; 
v_a_2419_ = lean_ctor_get(v___x_2418_, 0);
lean_inc(v_a_2419_);
lean_dec_ref_known(v___x_2418_, 1);
v___x_2420_ = ((lean_object*)(lp_competition_R24DotBankHarness_run___closed__24));
v___x_2421_ = lp_competition_R24DotBankHarness_env(v___x_2420_);
if (lean_obj_tag(v___x_2421_) == 0)
{
lean_object* v_a_2422_; lean_object* v___x_2423_; lean_object* v___x_2424_; 
v_a_2422_ = lean_ctor_get(v___x_2421_, 0);
lean_inc(v_a_2422_);
lean_dec_ref_known(v___x_2421_, 1);
v___x_2423_ = ((lean_object*)(lp_competition_R24DotBankHarness_run___closed__25));
v___x_2424_ = lean_io_getenv(v___x_2423_);
if (lean_obj_tag(v___x_2424_) == 0)
{
lean_object* v___x_2425_; 
v___x_2425_ = ((lean_object*)(lp_competition_R24DotBankHarness_run___closed__7));
v___y_2399_ = v___x_2414_;
v___y_2400_ = v___x_2416_;
v___y_2401_ = v_a_2422_;
v___y_2402_ = v_a_2419_;
v___y_2403_ = v___x_2425_;
goto v___jp_2398_;
}
else
{
lean_object* v_val_2426_; 
v_val_2426_ = lean_ctor_get(v___x_2424_, 0);
lean_inc(v_val_2426_);
lean_dec_ref_known(v___x_2424_, 1);
v___y_2399_ = v___x_2414_;
v___y_2400_ = v___x_2416_;
v___y_2401_ = v_a_2422_;
v___y_2402_ = v_a_2419_;
v___y_2403_ = v_val_2426_;
goto v___jp_2398_;
}
}
else
{
lean_object* v_a_2427_; lean_object* v___x_2429_; uint8_t v_isShared_2430_; uint8_t v_isSharedCheck_2434_; 
lean_dec(v_a_2419_);
lean_del_object(v___x_2285_);
lean_dec(v_a_2283_);
lean_del_object(v___x_2279_);
lean_del_object(v___x_2260_);
v_a_2427_ = lean_ctor_get(v___x_2421_, 0);
v_isSharedCheck_2434_ = !lean_is_exclusive(v___x_2421_);
if (v_isSharedCheck_2434_ == 0)
{
v___x_2429_ = v___x_2421_;
v_isShared_2430_ = v_isSharedCheck_2434_;
goto v_resetjp_2428_;
}
else
{
lean_inc(v_a_2427_);
lean_dec(v___x_2421_);
v___x_2429_ = lean_box(0);
v_isShared_2430_ = v_isSharedCheck_2434_;
goto v_resetjp_2428_;
}
v_resetjp_2428_:
{
lean_object* v___x_2432_; 
if (v_isShared_2430_ == 0)
{
v___x_2432_ = v___x_2429_;
goto v_reusejp_2431_;
}
else
{
lean_object* v_reuseFailAlloc_2433_; 
v_reuseFailAlloc_2433_ = lean_alloc_ctor(1, 1, 0);
lean_ctor_set(v_reuseFailAlloc_2433_, 0, v_a_2427_);
v___x_2432_ = v_reuseFailAlloc_2433_;
goto v_reusejp_2431_;
}
v_reusejp_2431_:
{
return v___x_2432_;
}
}
}
}
else
{
lean_object* v_a_2435_; lean_object* v___x_2437_; uint8_t v_isShared_2438_; uint8_t v_isSharedCheck_2442_; 
lean_del_object(v___x_2285_);
lean_dec(v_a_2283_);
lean_del_object(v___x_2279_);
lean_del_object(v___x_2260_);
v_a_2435_ = lean_ctor_get(v___x_2418_, 0);
v_isSharedCheck_2442_ = !lean_is_exclusive(v___x_2418_);
if (v_isSharedCheck_2442_ == 0)
{
v___x_2437_ = v___x_2418_;
v_isShared_2438_ = v_isSharedCheck_2442_;
goto v_resetjp_2436_;
}
else
{
lean_inc(v_a_2435_);
lean_dec(v___x_2418_);
v___x_2437_ = lean_box(0);
v_isShared_2438_ = v_isSharedCheck_2442_;
goto v_resetjp_2436_;
}
v_resetjp_2436_:
{
lean_object* v___x_2440_; 
if (v_isShared_2438_ == 0)
{
v___x_2440_ = v___x_2437_;
goto v_reusejp_2439_;
}
else
{
lean_object* v_reuseFailAlloc_2441_; 
v_reuseFailAlloc_2441_ = lean_alloc_ctor(1, 1, 0);
lean_ctor_set(v_reuseFailAlloc_2441_, 0, v_a_2435_);
v___x_2440_ = v_reuseFailAlloc_2441_;
goto v_reusejp_2439_;
}
v_reusejp_2439_:
{
return v___x_2440_;
}
}
}
}
else
{
lean_del_object(v___x_2285_);
lean_dec(v_a_2283_);
lean_del_object(v___x_2279_);
lean_del_object(v___x_2260_);
goto v___jp_2408_;
}
}
}
else
{
lean_object* v___x_2443_; 
lean_dec_ref(v___y_2412_);
lean_del_object(v___x_2285_);
lean_del_object(v___x_2279_);
lean_del_object(v___x_2260_);
v___x_2443_ = lp_competition_R24DotBankHarness_verify(v_a_2283_);
lean_dec(v_a_2283_);
if (lean_obj_tag(v___x_2443_) == 0)
{
lean_object* v___x_2445_; uint8_t v_isShared_2446_; uint8_t v_isSharedCheck_2451_; 
v_isSharedCheck_2451_ = !lean_is_exclusive(v___x_2443_);
if (v_isSharedCheck_2451_ == 0)
{
lean_object* v_unused_2452_; 
v_unused_2452_ = lean_ctor_get(v___x_2443_, 0);
lean_dec(v_unused_2452_);
v___x_2445_ = v___x_2443_;
v_isShared_2446_ = v_isSharedCheck_2451_;
goto v_resetjp_2444_;
}
else
{
lean_dec(v___x_2443_);
v___x_2445_ = lean_box(0);
v_isShared_2446_ = v_isSharedCheck_2451_;
goto v_resetjp_2444_;
}
v_resetjp_2444_:
{
lean_object* v___x_2447_; lean_object* v___x_2449_; 
v___x_2447_ = lp_competition_R24DotBankHarness_sumRemaining___boxed__const__1;
if (v_isShared_2446_ == 0)
{
lean_ctor_set(v___x_2445_, 0, v___x_2447_);
v___x_2449_ = v___x_2445_;
goto v_reusejp_2448_;
}
else
{
lean_object* v_reuseFailAlloc_2450_; 
v_reuseFailAlloc_2450_ = lean_alloc_ctor(0, 1, 0);
lean_ctor_set(v_reuseFailAlloc_2450_, 0, v___x_2447_);
v___x_2449_ = v_reuseFailAlloc_2450_;
goto v_reusejp_2448_;
}
v_reusejp_2448_:
{
return v___x_2449_;
}
}
}
else
{
lean_object* v_a_2453_; lean_object* v___x_2455_; uint8_t v_isShared_2456_; uint8_t v_isSharedCheck_2460_; 
v_a_2453_ = lean_ctor_get(v___x_2443_, 0);
v_isSharedCheck_2460_ = !lean_is_exclusive(v___x_2443_);
if (v_isSharedCheck_2460_ == 0)
{
v___x_2455_ = v___x_2443_;
v_isShared_2456_ = v_isSharedCheck_2460_;
goto v_resetjp_2454_;
}
else
{
lean_inc(v_a_2453_);
lean_dec(v___x_2443_);
v___x_2455_ = lean_box(0);
v_isShared_2456_ = v_isSharedCheck_2460_;
goto v_resetjp_2454_;
}
v_resetjp_2454_:
{
lean_object* v___x_2458_; 
if (v_isShared_2456_ == 0)
{
v___x_2458_ = v___x_2455_;
goto v_reusejp_2457_;
}
else
{
lean_object* v_reuseFailAlloc_2459_; 
v_reuseFailAlloc_2459_ = lean_alloc_ctor(1, 1, 0);
lean_ctor_set(v_reuseFailAlloc_2459_, 0, v_a_2453_);
v___x_2458_ = v_reuseFailAlloc_2459_;
goto v_reusejp_2457_;
}
v_reusejp_2457_:
{
return v___x_2458_;
}
}
}
}
}
}
}
}
}
v___jp_2267_:
{
lean_object* v___x_2269_; lean_object* v___x_2270_; lean_object* v___x_2271_; lean_object* v___x_2273_; 
v___x_2269_ = ((lean_object*)(lp_competition_R24DotBankHarness_run___closed__1));
v___x_2270_ = lean_string_append(v___x_2269_, v_a_2268_);
lean_dec_ref(v_a_2268_);
v___x_2271_ = lean_alloc_ctor(18, 1, 0);
lean_ctor_set(v___x_2271_, 0, v___x_2270_);
if (v_isShared_2266_ == 0)
{
lean_ctor_set_tag(v___x_2265_, 1);
lean_ctor_set(v___x_2265_, 0, v___x_2271_);
v___x_2273_ = v___x_2265_;
goto v_reusejp_2272_;
}
else
{
lean_object* v_reuseFailAlloc_2274_; 
v_reuseFailAlloc_2274_ = lean_alloc_ctor(1, 1, 0);
lean_ctor_set(v_reuseFailAlloc_2274_, 0, v___x_2271_);
v___x_2273_ = v_reuseFailAlloc_2274_;
goto v_reusejp_2272_;
}
v_reusejp_2272_:
{
return v___x_2273_;
}
}
}
}
else
{
lean_object* v_a_2466_; lean_object* v___x_2468_; uint8_t v_isShared_2469_; uint8_t v_isSharedCheck_2473_; 
lean_del_object(v___x_2260_);
v_a_2466_ = lean_ctor_get(v___x_2262_, 0);
v_isSharedCheck_2473_ = !lean_is_exclusive(v___x_2262_);
if (v_isSharedCheck_2473_ == 0)
{
v___x_2468_ = v___x_2262_;
v_isShared_2469_ = v_isSharedCheck_2473_;
goto v_resetjp_2467_;
}
else
{
lean_inc(v_a_2466_);
lean_dec(v___x_2262_);
v___x_2468_ = lean_box(0);
v_isShared_2469_ = v_isSharedCheck_2473_;
goto v_resetjp_2467_;
}
v_resetjp_2467_:
{
lean_object* v___x_2471_; 
if (v_isShared_2469_ == 0)
{
v___x_2471_ = v___x_2468_;
goto v_reusejp_2470_;
}
else
{
lean_object* v_reuseFailAlloc_2472_; 
v_reuseFailAlloc_2472_ = lean_alloc_ctor(1, 1, 0);
lean_ctor_set(v_reuseFailAlloc_2472_, 0, v_a_2466_);
v___x_2471_ = v_reuseFailAlloc_2472_;
goto v_reusejp_2470_;
}
v_reusejp_2470_:
{
return v___x_2471_;
}
}
}
}
}
else
{
lean_object* v_a_2475_; lean_object* v___x_2477_; uint8_t v_isShared_2478_; uint8_t v_isSharedCheck_2482_; 
v_a_2475_ = lean_ctor_get(v___x_2257_, 0);
v_isSharedCheck_2482_ = !lean_is_exclusive(v___x_2257_);
if (v_isSharedCheck_2482_ == 0)
{
v___x_2477_ = v___x_2257_;
v_isShared_2478_ = v_isSharedCheck_2482_;
goto v_resetjp_2476_;
}
else
{
lean_inc(v_a_2475_);
lean_dec(v___x_2257_);
v___x_2477_ = lean_box(0);
v_isShared_2478_ = v_isSharedCheck_2482_;
goto v_resetjp_2476_;
}
v_resetjp_2476_:
{
lean_object* v___x_2480_; 
if (v_isShared_2478_ == 0)
{
v___x_2480_ = v___x_2477_;
goto v_reusejp_2479_;
}
else
{
lean_object* v_reuseFailAlloc_2481_; 
v_reuseFailAlloc_2481_ = lean_alloc_ctor(1, 1, 0);
lean_ctor_set(v_reuseFailAlloc_2481_, 0, v_a_2475_);
v___x_2480_ = v_reuseFailAlloc_2481_;
goto v_reusejp_2479_;
}
v_reusejp_2479_:
{
return v___x_2480_;
}
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_R24DotBankHarness_run___boxed(lean_object* v_a_2483_){
_start:
{
lean_object* v_res_2484_; 
v_res_2484_ = lp_competition_R24DotBankHarness_run();
return v_res_2484_;
}
}
LEAN_EXPORT lean_object* _lean_main(){
_start:
{
lean_object* v___x_2486_; 
v___x_2486_ = lp_competition_R24DotBankHarness_run();
return v___x_2486_;
}
}
LEAN_EXPORT lean_object* lp_competition_main___boxed(lean_object* v_a_2487_){
_start:
{
lean_object* v_res_2488_; 
v_res_2488_ = _lean_main();
return v_res_2488_;
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
lp_competition_R24DotBankHarness_sumRemaining___boxed__const__1 = _init_lp_competition_R24DotBankHarness_sumRemaining___boxed__const__1();
lean_mark_persistent(lp_competition_R24DotBankHarness_sumRemaining___boxed__const__1);
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
