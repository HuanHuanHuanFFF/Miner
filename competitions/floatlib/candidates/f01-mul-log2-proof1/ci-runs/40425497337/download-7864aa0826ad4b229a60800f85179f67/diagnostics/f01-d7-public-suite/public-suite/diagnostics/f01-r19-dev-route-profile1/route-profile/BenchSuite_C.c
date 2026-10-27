// Lean compiler output
// Module: BenchSuite
// Imports: public import Init public meta import Init public import BenchBmm public import Lean.Data.Json
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
lean_object* l_Lean_Name_mkStr3(lean_object*, lean_object*, lean_object*);
lean_object* lean_string_append(lean_object*, lean_object*);
size_t lean_array_size(lean_object*);
uint8_t lean_usize_dec_lt(size_t, size_t);
lean_object* lean_array_uget_borrowed(lean_object*, size_t);
uint32_t lean_uint32_xor(uint32_t, uint32_t);
uint32_t lean_uint32_mul(uint32_t, uint32_t);
size_t lean_usize_add(size_t, size_t);
lean_object* lean_nat_mul(lean_object*, lean_object*);
lean_object* lean_nat_add(lean_object*, lean_object*);
uint64_t lean_uint64_of_nat(lean_object*);
uint64_t lean_uint64_mul(uint64_t, uint64_t);
uint64_t lean_uint64_add(uint64_t, uint64_t);
uint64_t lean_uint64_shift_right(uint64_t, uint64_t);
uint64_t lean_uint64_xor(uint64_t, uint64_t);
uint32_t lean_uint64_to_uint32(uint64_t);
lean_object* lean_uint32_to_nat(uint32_t);
lean_object* lean_nat_mod(lean_object*, lean_object*);
uint8_t lean_nat_dec_lt(lean_object*, lean_object*);
uint8_t lean_nat_dec_eq(lean_object*, lean_object*);
lean_object* lean_nat_sub(lean_object*, lean_object*);
lean_object* lean_nat_div(lean_object*, lean_object*);
lean_object* lean_nat_shiftr(lean_object*, lean_object*);
lean_object* l_Int_toNat(lean_object*);
uint32_t lean_uint32_of_nat(lean_object*);
uint32_t lean_uint32_shift_left(uint32_t, uint32_t);
uint32_t lean_uint32_lor(uint32_t, uint32_t);
uint8_t lean_int_dec_le(lean_object*, lean_object*);
lean_object* lean_int_add(lean_object*, lean_object*);
lean_object* lean_nat_to_int(lean_object*);
uint32_t lean_uint32_land(uint32_t, uint32_t);
uint8_t lean_nat_dec_le(lean_object*, lean_object*);
uint32_t lean_uint32_sub(uint32_t, uint32_t);
lean_object* lean_int_sub(lean_object*, lean_object*);
uint32_t lean_uint32_shift_right(uint32_t, uint32_t);
uint8_t lean_uint32_dec_eq(uint32_t, uint32_t);
lean_object* l_List_range(lean_object*);
lean_object* l_Array_ofFn___redArg(lean_object*, lean_object*);
lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00Bench_runBmm_spec__0(lean_object*, size_t, size_t, uint32_t);
lean_object* l_Nat_reprFast(lean_object*);
lean_object* lp_batteries_IO_println___at___00Batteries_Tactic_Lint_lintCore_spec__4(lean_object*);
lean_object* lean_io_mono_nanos_now();
uint32_t lean_uint32_complement(uint32_t);
uint8_t lean_string_dec_eq(lean_object*, lean_object*);
lean_object* lp_proofwidgets_Lean_Json_getObjValAs_x3f___at___00ProofWidgets_MarkdownDisplay_instFromJsonProps_fromJson_spec__0(lean_object*, lean_object*);
lean_object* l_Lean_Json_getObjValAs_x3f___at___00Lean_Lsp_instFromJsonLeanILeanHeaderSetupInfoParams_fromJson_spec__1(lean_object*, lean_object*);
lean_object* l_Lean_Json_getObjValAs_x3f___at___00Lean_Server_instFromJsonIlean_fromJson_spec__0(lean_object*, lean_object*);
lean_object* lean_io_getenv(lean_object*);
lean_object* l_Lean_Json_parse(lean_object*);
lean_object* l_Lean_Json_getObjValD(lean_object*, lean_object*);
lean_object* lean_array_uset(lean_object*, size_t, lean_object*);
lean_object* l_Lean_Json_pretty(lean_object*, lean_object*);
lean_object* lp_competition_Bench_envNat(lean_object*, lean_object*);
static const lean_string_object lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__0_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 5, .m_capacity = 5, .m_length = 4, .m_data = "name"};
static const lean_object* lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__0 = (const lean_object*)&lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__0_value;
static const lean_string_object lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__1_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 6, .m_capacity = 6, .m_length = 5, .m_data = "Bench"};
static const lean_object* lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__1 = (const lean_object*)&lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__1_value;
static const lean_string_object lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__2_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 6, .m_capacity = 6, .m_length = 5, .m_data = "Suite"};
static const lean_object* lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__2 = (const lean_object*)&lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__2_value;
static const lean_string_object lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__3_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 5, .m_capacity = 5, .m_length = 4, .m_data = "Case"};
static const lean_object* lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__3 = (const lean_object*)&lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__3_value;
static const lean_ctor_object lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__4_value_aux_0 = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_ctor_object) + sizeof(void*)*2 + 8, .m_other = 2, .m_tag = 1}, .m_objs = {((lean_object*)(((size_t)(0) << 1) | 1)),((lean_object*)&lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__1_value),LEAN_SCALAR_PTR_LITERAL(100, 190, 76, 150, 26, 12, 63, 36)}};
static const lean_ctor_object lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__4_value_aux_1 = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_ctor_object) + sizeof(void*)*2 + 8, .m_other = 2, .m_tag = 1}, .m_objs = {((lean_object*)&lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__4_value_aux_0),((lean_object*)&lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__2_value),LEAN_SCALAR_PTR_LITERAL(41, 253, 102, 34, 90, 216, 165, 14)}};
static const lean_ctor_object lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__4_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_ctor_object) + sizeof(void*)*2 + 8, .m_other = 2, .m_tag = 1}, .m_objs = {((lean_object*)&lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__4_value_aux_1),((lean_object*)&lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__3_value),LEAN_SCALAR_PTR_LITERAL(100, 111, 48, 98, 151, 197, 188, 169)}};
static const lean_object* lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__4 = (const lean_object*)&lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__4_value;
static lean_once_cell_t lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__5_once = LEAN_ONCE_CELL_INITIALIZER;
static lean_object* lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__5;
static const lean_string_object lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__6_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 2, .m_capacity = 2, .m_length = 1, .m_data = "."};
static const lean_object* lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__6 = (const lean_object*)&lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__6_value;
static lean_once_cell_t lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__7_once = LEAN_ONCE_CELL_INITIALIZER;
static lean_object* lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__7;
static const lean_ctor_object lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__8_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_ctor_object) + sizeof(void*)*2 + 8, .m_other = 2, .m_tag = 1}, .m_objs = {((lean_object*)(((size_t)(0) << 1) | 1)),((lean_object*)&lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__0_value),LEAN_SCALAR_PTR_LITERAL(84, 246, 234, 130, 97, 205, 144, 82)}};
static const lean_object* lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__8 = (const lean_object*)&lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__8_value;
static lean_once_cell_t lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__9_once = LEAN_ONCE_CELL_INITIALIZER;
static lean_object* lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__9;
static lean_once_cell_t lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__10_once = LEAN_ONCE_CELL_INITIALIZER;
static lean_object* lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__10;
static const lean_string_object lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__11_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 3, .m_capacity = 3, .m_length = 2, .m_data = ": "};
static const lean_object* lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__11 = (const lean_object*)&lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__11_value;
static lean_once_cell_t lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__12_once = LEAN_ONCE_CELL_INITIALIZER;
static lean_object* lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__12;
static const lean_string_object lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__13_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 7, .m_capacity = 7, .m_length = 6, .m_data = "kernel"};
static const lean_object* lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__13 = (const lean_object*)&lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__13_value;
static const lean_ctor_object lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__14_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_ctor_object) + sizeof(void*)*2 + 8, .m_other = 2, .m_tag = 1}, .m_objs = {((lean_object*)(((size_t)(0) << 1) | 1)),((lean_object*)&lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__13_value),LEAN_SCALAR_PTR_LITERAL(78, 244, 187, 126, 175, 157, 90, 69)}};
static const lean_object* lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__14 = (const lean_object*)&lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__14_value;
static lean_once_cell_t lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__15_once = LEAN_ONCE_CELL_INITIALIZER;
static lean_object* lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__15;
static lean_once_cell_t lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__16_once = LEAN_ONCE_CELL_INITIALIZER;
static lean_object* lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__16;
static lean_once_cell_t lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__17_once = LEAN_ONCE_CELL_INITIALIZER;
static lean_object* lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__17;
static const lean_string_object lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__18_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 6, .m_capacity = 6, .m_length = 5, .m_data = "timed"};
static const lean_object* lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__18 = (const lean_object*)&lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__18_value;
static const lean_ctor_object lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__19_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_ctor_object) + sizeof(void*)*2 + 8, .m_other = 2, .m_tag = 1}, .m_objs = {((lean_object*)(((size_t)(0) << 1) | 1)),((lean_object*)&lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__18_value),LEAN_SCALAR_PTR_LITERAL(136, 54, 60, 30, 1, 8, 250, 239)}};
static const lean_object* lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__19 = (const lean_object*)&lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__19_value;
static lean_once_cell_t lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__20_once = LEAN_ONCE_CELL_INITIALIZER;
static lean_object* lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__20;
static lean_once_cell_t lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__21_once = LEAN_ONCE_CELL_INITIALIZER;
static lean_object* lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__21;
static lean_once_cell_t lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__22_once = LEAN_ONCE_CELL_INITIALIZER;
static lean_object* lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__22;
static const lean_string_object lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__23_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 5, .m_capacity = 5, .m_length = 4, .m_data = "seed"};
static const lean_object* lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__23 = (const lean_object*)&lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__23_value;
static const lean_ctor_object lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__24_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_ctor_object) + sizeof(void*)*2 + 8, .m_other = 2, .m_tag = 1}, .m_objs = {((lean_object*)(((size_t)(0) << 1) | 1)),((lean_object*)&lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__23_value),LEAN_SCALAR_PTR_LITERAL(48, 123, 194, 170, 254, 69, 11, 177)}};
static const lean_object* lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__24 = (const lean_object*)&lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__24_value;
static lean_once_cell_t lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__25_once = LEAN_ONCE_CELL_INITIALIZER;
static lean_object* lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__25;
static lean_once_cell_t lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__26_once = LEAN_ONCE_CELL_INITIALIZER;
static lean_object* lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__26;
static lean_once_cell_t lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__27_once = LEAN_ONCE_CELL_INITIALIZER;
static lean_object* lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__27;
static const lean_string_object lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__28_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 4, .m_capacity = 4, .m_length = 3, .m_data = "mag"};
static const lean_object* lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__28 = (const lean_object*)&lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__28_value;
static const lean_ctor_object lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__29_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_ctor_object) + sizeof(void*)*2 + 8, .m_other = 2, .m_tag = 1}, .m_objs = {((lean_object*)(((size_t)(0) << 1) | 1)),((lean_object*)&lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__28_value),LEAN_SCALAR_PTR_LITERAL(185, 180, 90, 132, 158, 184, 209, 93)}};
static const lean_object* lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__29 = (const lean_object*)&lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__29_value;
static lean_once_cell_t lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__30_once = LEAN_ONCE_CELL_INITIALIZER;
static lean_object* lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__30;
static lean_once_cell_t lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__31_once = LEAN_ONCE_CELL_INITIALIZER;
static lean_object* lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__31;
static lean_once_cell_t lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__32_once = LEAN_ONCE_CELL_INITIALIZER;
static lean_object* lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__32;
static const lean_string_object lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__33_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 7, .m_capacity = 7, .m_length = 6, .m_data = "center"};
static const lean_object* lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__33 = (const lean_object*)&lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__33_value;
static const lean_ctor_object lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__34_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_ctor_object) + sizeof(void*)*2 + 8, .m_other = 2, .m_tag = 1}, .m_objs = {((lean_object*)(((size_t)(0) << 1) | 1)),((lean_object*)&lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__33_value),LEAN_SCALAR_PTR_LITERAL(172, 212, 3, 206, 58, 40, 26, 210)}};
static const lean_object* lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__34 = (const lean_object*)&lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__34_value;
static lean_once_cell_t lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__35_once = LEAN_ONCE_CELL_INITIALIZER;
static lean_object* lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__35;
static lean_once_cell_t lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__36_once = LEAN_ONCE_CELL_INITIALIZER;
static lean_object* lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__36;
static lean_once_cell_t lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__37_once = LEAN_ONCE_CELL_INITIALIZER;
static lean_object* lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__37;
static const lean_string_object lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__38_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 7, .m_capacity = 7, .m_length = 6, .m_data = "spread"};
static const lean_object* lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__38 = (const lean_object*)&lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__38_value;
static const lean_ctor_object lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__39_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_ctor_object) + sizeof(void*)*2 + 8, .m_other = 2, .m_tag = 1}, .m_objs = {((lean_object*)(((size_t)(0) << 1) | 1)),((lean_object*)&lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__38_value),LEAN_SCALAR_PTR_LITERAL(89, 130, 127, 53, 242, 238, 153, 14)}};
static const lean_object* lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__39 = (const lean_object*)&lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__39_value;
static lean_once_cell_t lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__40_once = LEAN_ONCE_CELL_INITIALIZER;
static lean_object* lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__40;
static lean_once_cell_t lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__41_once = LEAN_ONCE_CELL_INITIALIZER;
static lean_object* lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__41;
static lean_once_cell_t lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__42_once = LEAN_ONCE_CELL_INITIALIZER;
static lean_object* lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__42;
static const lean_string_object lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__43_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 9, .m_capacity = 9, .m_length = 8, .m_data = "positive"};
static const lean_object* lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__43 = (const lean_object*)&lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__43_value;
static const lean_ctor_object lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__44_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_ctor_object) + sizeof(void*)*2 + 8, .m_other = 2, .m_tag = 1}, .m_objs = {((lean_object*)(((size_t)(0) << 1) | 1)),((lean_object*)&lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__43_value),LEAN_SCALAR_PTR_LITERAL(12, 131, 189, 142, 124, 21, 23, 62)}};
static const lean_object* lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__44 = (const lean_object*)&lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__44_value;
static lean_once_cell_t lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__45_once = LEAN_ONCE_CELL_INITIALIZER;
static lean_object* lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__45;
static lean_once_cell_t lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__46_once = LEAN_ONCE_CELL_INITIALIZER;
static lean_object* lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__46;
static lean_once_cell_t lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__47_once = LEAN_ONCE_CELL_INITIALIZER;
static lean_object* lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__47;
static const lean_string_object lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__48_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 9, .m_capacity = 9, .m_length = 8, .m_data = "mantBits"};
static const lean_object* lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__48 = (const lean_object*)&lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__48_value;
static const lean_ctor_object lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__49_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_ctor_object) + sizeof(void*)*2 + 8, .m_other = 2, .m_tag = 1}, .m_objs = {((lean_object*)(((size_t)(0) << 1) | 1)),((lean_object*)&lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__48_value),LEAN_SCALAR_PTR_LITERAL(40, 151, 91, 162, 194, 26, 19, 93)}};
static const lean_object* lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__49 = (const lean_object*)&lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__49_value;
static lean_once_cell_t lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__50_once = LEAN_ONCE_CELL_INITIALIZER;
static lean_object* lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__50;
static lean_once_cell_t lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__51_once = LEAN_ONCE_CELL_INITIALIZER;
static lean_object* lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__51;
static lean_once_cell_t lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__52_once = LEAN_ONCE_CELL_INITIALIZER;
static lean_object* lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__52;
static const lean_string_object lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__53_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 9, .m_capacity = 9, .m_length = 8, .m_data = "codebook"};
static const lean_object* lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__53 = (const lean_object*)&lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__53_value;
static const lean_ctor_object lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__54_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_ctor_object) + sizeof(void*)*2 + 8, .m_other = 2, .m_tag = 1}, .m_objs = {((lean_object*)(((size_t)(0) << 1) | 1)),((lean_object*)&lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__53_value),LEAN_SCALAR_PTR_LITERAL(15, 87, 240, 59, 54, 28, 154, 35)}};
static const lean_object* lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__54 = (const lean_object*)&lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__54_value;
static lean_once_cell_t lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__55_once = LEAN_ONCE_CELL_INITIALIZER;
static lean_object* lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__55;
static lean_once_cell_t lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__56_once = LEAN_ONCE_CELL_INITIALIZER;
static lean_object* lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__56;
static lean_once_cell_t lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__57_once = LEAN_ONCE_CELL_INITIALIZER;
static lean_object* lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__57;
static const lean_string_object lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__58_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 11, .m_capacity = 11, .m_length = 10, .m_data = "scaleBlock"};
static const lean_object* lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__58 = (const lean_object*)&lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__58_value;
static const lean_ctor_object lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__59_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_ctor_object) + sizeof(void*)*2 + 8, .m_other = 2, .m_tag = 1}, .m_objs = {((lean_object*)(((size_t)(0) << 1) | 1)),((lean_object*)&lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__58_value),LEAN_SCALAR_PTR_LITERAL(27, 72, 249, 223, 158, 4, 190, 188)}};
static const lean_object* lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__59 = (const lean_object*)&lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__59_value;
static lean_once_cell_t lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__60_once = LEAN_ONCE_CELL_INITIALIZER;
static lean_object* lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__60;
static lean_once_cell_t lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__61_once = LEAN_ONCE_CELL_INITIALIZER;
static lean_object* lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__61;
static lean_once_cell_t lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__62_once = LEAN_ONCE_CELL_INITIALIZER;
static lean_object* lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__62;
static const lean_string_object lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__63_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 11, .m_capacity = 11, .m_length = 10, .m_data = "scaleShift"};
static const lean_object* lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__63 = (const lean_object*)&lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__63_value;
static const lean_ctor_object lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__64_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_ctor_object) + sizeof(void*)*2 + 8, .m_other = 2, .m_tag = 1}, .m_objs = {((lean_object*)(((size_t)(0) << 1) | 1)),((lean_object*)&lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__63_value),LEAN_SCALAR_PTR_LITERAL(143, 239, 34, 98, 218, 86, 200, 148)}};
static const lean_object* lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__64 = (const lean_object*)&lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__64_value;
static lean_once_cell_t lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__65_once = LEAN_ONCE_CELL_INITIALIZER;
static lean_object* lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__65;
static lean_once_cell_t lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__66_once = LEAN_ONCE_CELL_INITIALIZER;
static lean_object* lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__66;
static lean_once_cell_t lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__67_once = LEAN_ONCE_CELL_INITIALIZER;
static lean_object* lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__67;
static const lean_string_object lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__68_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 8, .m_capacity = 8, .m_length = 7, .m_data = "zeroPct"};
static const lean_object* lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__68 = (const lean_object*)&lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__68_value;
static const lean_ctor_object lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__69_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_ctor_object) + sizeof(void*)*2 + 8, .m_other = 2, .m_tag = 1}, .m_objs = {((lean_object*)(((size_t)(0) << 1) | 1)),((lean_object*)&lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__68_value),LEAN_SCALAR_PTR_LITERAL(95, 198, 226, 145, 55, 27, 18, 207)}};
static const lean_object* lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__69 = (const lean_object*)&lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__69_value;
static lean_once_cell_t lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__70_once = LEAN_ONCE_CELL_INITIALIZER;
static lean_object* lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__70;
static lean_once_cell_t lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__71_once = LEAN_ONCE_CELL_INITIALIZER;
static lean_object* lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__71;
static lean_once_cell_t lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__72_once = LEAN_ONCE_CELL_INITIALIZER;
static lean_object* lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__72;
static const lean_string_object lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__73_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 12, .m_capacity = 12, .m_length = 11, .m_data = "zeroCluster"};
static const lean_object* lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__73 = (const lean_object*)&lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__73_value;
static const lean_ctor_object lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__74_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_ctor_object) + sizeof(void*)*2 + 8, .m_other = 2, .m_tag = 1}, .m_objs = {((lean_object*)(((size_t)(0) << 1) | 1)),((lean_object*)&lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__73_value),LEAN_SCALAR_PTR_LITERAL(154, 66, 99, 156, 163, 137, 136, 162)}};
static const lean_object* lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__74 = (const lean_object*)&lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__74_value;
static lean_once_cell_t lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__75_once = LEAN_ONCE_CELL_INITIALIZER;
static lean_object* lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__75;
static lean_once_cell_t lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__76_once = LEAN_ONCE_CELL_INITIALIZER;
static lean_object* lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__76;
static lean_once_cell_t lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__77_once = LEAN_ONCE_CELL_INITIALIZER;
static lean_object* lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__77;
static const lean_string_object lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__78_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 9, .m_capacity = 9, .m_length = 8, .m_data = "zeroKind"};
static const lean_object* lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__78 = (const lean_object*)&lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__78_value;
static const lean_ctor_object lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__79_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_ctor_object) + sizeof(void*)*2 + 8, .m_other = 2, .m_tag = 1}, .m_objs = {((lean_object*)(((size_t)(0) << 1) | 1)),((lean_object*)&lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__78_value),LEAN_SCALAR_PTR_LITERAL(130, 80, 140, 134, 58, 95, 145, 227)}};
static const lean_object* lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__79 = (const lean_object*)&lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__79_value;
static lean_once_cell_t lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__80_once = LEAN_ONCE_CELL_INITIALIZER;
static lean_object* lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__80;
static lean_once_cell_t lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__81_once = LEAN_ONCE_CELL_INITIALIZER;
static lean_object* lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__81;
static lean_once_cell_t lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__82_once = LEAN_ONCE_CELL_INITIALIZER;
static lean_object* lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__82;
static const lean_string_object lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__83_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 7, .m_capacity = 7, .m_length = 6, .m_data = "subPct"};
static const lean_object* lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__83 = (const lean_object*)&lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__83_value;
static const lean_ctor_object lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__84_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_ctor_object) + sizeof(void*)*2 + 8, .m_other = 2, .m_tag = 1}, .m_objs = {((lean_object*)(((size_t)(0) << 1) | 1)),((lean_object*)&lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__83_value),LEAN_SCALAR_PTR_LITERAL(152, 123, 125, 184, 49, 104, 70, 160)}};
static const lean_object* lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__84 = (const lean_object*)&lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__84_value;
static lean_once_cell_t lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__85_once = LEAN_ONCE_CELL_INITIALIZER;
static lean_object* lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__85;
static lean_once_cell_t lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__86_once = LEAN_ONCE_CELL_INITIALIZER;
static lean_object* lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__86;
static lean_once_cell_t lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__87_once = LEAN_ONCE_CELL_INITIALIZER;
static lean_object* lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__87;
static const lean_string_object lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__88_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 9, .m_capacity = 9, .m_length = 8, .m_data = "subBlock"};
static const lean_object* lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__88 = (const lean_object*)&lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__88_value;
static const lean_ctor_object lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__89_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_ctor_object) + sizeof(void*)*2 + 8, .m_other = 2, .m_tag = 1}, .m_objs = {((lean_object*)(((size_t)(0) << 1) | 1)),((lean_object*)&lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__88_value),LEAN_SCALAR_PTR_LITERAL(243, 119, 68, 218, 139, 41, 191, 184)}};
static const lean_object* lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__89 = (const lean_object*)&lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__89_value;
static lean_once_cell_t lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__90_once = LEAN_ONCE_CELL_INITIALIZER;
static lean_object* lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__90;
static lean_once_cell_t lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__91_once = LEAN_ONCE_CELL_INITIALIZER;
static lean_object* lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__91;
static lean_once_cell_t lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__92_once = LEAN_ONCE_CELL_INITIALIZER;
static lean_object* lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__92;
static const lean_string_object lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__93_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 9, .m_capacity = 9, .m_length = 8, .m_data = "specRate"};
static const lean_object* lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__93 = (const lean_object*)&lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__93_value;
static const lean_ctor_object lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__94_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_ctor_object) + sizeof(void*)*2 + 8, .m_other = 2, .m_tag = 1}, .m_objs = {((lean_object*)(((size_t)(0) << 1) | 1)),((lean_object*)&lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__93_value),LEAN_SCALAR_PTR_LITERAL(220, 22, 3, 52, 113, 81, 253, 236)}};
static const lean_object* lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__94 = (const lean_object*)&lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__94_value;
static lean_once_cell_t lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__95_once = LEAN_ONCE_CELL_INITIALIZER;
static lean_object* lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__95;
static lean_once_cell_t lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__96_once = LEAN_ONCE_CELL_INITIALIZER;
static lean_object* lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__96;
static lean_once_cell_t lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__97_once = LEAN_ONCE_CELL_INITIALIZER;
static lean_object* lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__97;
static const lean_string_object lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__98_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 10, .m_capacity = 10, .m_length = 9, .m_data = "specPlace"};
static const lean_object* lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__98 = (const lean_object*)&lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__98_value;
static const lean_ctor_object lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__99_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_ctor_object) + sizeof(void*)*2 + 8, .m_other = 2, .m_tag = 1}, .m_objs = {((lean_object*)(((size_t)(0) << 1) | 1)),((lean_object*)&lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__98_value),LEAN_SCALAR_PTR_LITERAL(8, 227, 92, 156, 149, 128, 24, 100)}};
static const lean_object* lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__99 = (const lean_object*)&lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__99_value;
static lean_once_cell_t lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__100_once = LEAN_ONCE_CELL_INITIALIZER;
static lean_object* lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__100;
static lean_once_cell_t lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__101_once = LEAN_ONCE_CELL_INITIALIZER;
static lean_object* lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__101;
static lean_once_cell_t lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__102_once = LEAN_ONCE_CELL_INITIALIZER;
static lean_object* lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__102;
static const lean_string_object lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__103_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 11, .m_capacity = 11, .m_length = 10, .m_data = "specPeriod"};
static const lean_object* lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__103 = (const lean_object*)&lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__103_value;
static const lean_ctor_object lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__104_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_ctor_object) + sizeof(void*)*2 + 8, .m_other = 2, .m_tag = 1}, .m_objs = {((lean_object*)(((size_t)(0) << 1) | 1)),((lean_object*)&lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__103_value),LEAN_SCALAR_PTR_LITERAL(243, 210, 56, 83, 55, 191, 199, 144)}};
static const lean_object* lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__104 = (const lean_object*)&lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__104_value;
static lean_once_cell_t lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__105_once = LEAN_ONCE_CELL_INITIALIZER;
static lean_object* lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__105;
static lean_once_cell_t lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__106_once = LEAN_ONCE_CELL_INITIALIZER;
static lean_object* lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__106;
static lean_once_cell_t lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__107_once = LEAN_ONCE_CELL_INITIALIZER;
static lean_object* lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__107;
static const lean_string_object lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__108_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 10, .m_capacity = 10, .m_length = 9, .m_data = "specBurst"};
static const lean_object* lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__108 = (const lean_object*)&lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__108_value;
static const lean_ctor_object lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__109_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_ctor_object) + sizeof(void*)*2 + 8, .m_other = 2, .m_tag = 1}, .m_objs = {((lean_object*)(((size_t)(0) << 1) | 1)),((lean_object*)&lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__108_value),LEAN_SCALAR_PTR_LITERAL(33, 145, 83, 74, 161, 247, 248, 135)}};
static const lean_object* lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__109 = (const lean_object*)&lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__109_value;
static lean_once_cell_t lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__110_once = LEAN_ONCE_CELL_INITIALIZER;
static lean_object* lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__110;
static lean_once_cell_t lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__111_once = LEAN_ONCE_CELL_INITIALIZER;
static lean_object* lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__111;
static lean_once_cell_t lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__112_once = LEAN_ONCE_CELL_INITIALIZER;
static lean_object* lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__112;
static const lean_string_object lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__113_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 9, .m_capacity = 9, .m_length = 8, .m_data = "specMask"};
static const lean_object* lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__113 = (const lean_object*)&lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__113_value;
static const lean_ctor_object lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__114_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_ctor_object) + sizeof(void*)*2 + 8, .m_other = 2, .m_tag = 1}, .m_objs = {((lean_object*)(((size_t)(0) << 1) | 1)),((lean_object*)&lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__113_value),LEAN_SCALAR_PTR_LITERAL(116, 171, 253, 59, 91, 94, 104, 101)}};
static const lean_object* lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__114 = (const lean_object*)&lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__114_value;
static lean_once_cell_t lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__115_once = LEAN_ONCE_CELL_INITIALIZER;
static lean_object* lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__115;
static lean_once_cell_t lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__116_once = LEAN_ONCE_CELL_INITIALIZER;
static lean_object* lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__116;
static lean_once_cell_t lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__117_once = LEAN_ONCE_CELL_INITIALIZER;
static lean_object* lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__117;
static const lean_string_object lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__118_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 9, .m_capacity = 9, .m_length = 8, .m_data = "relation"};
static const lean_object* lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__118 = (const lean_object*)&lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__118_value;
static const lean_ctor_object lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__119_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_ctor_object) + sizeof(void*)*2 + 8, .m_other = 2, .m_tag = 1}, .m_objs = {((lean_object*)(((size_t)(0) << 1) | 1)),((lean_object*)&lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__118_value),LEAN_SCALAR_PTR_LITERAL(70, 193, 156, 252, 136, 32, 87, 94)}};
static const lean_object* lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__119 = (const lean_object*)&lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__119_value;
static lean_once_cell_t lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__120_once = LEAN_ONCE_CELL_INITIALIZER;
static lean_object* lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__120;
static lean_once_cell_t lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__121_once = LEAN_ONCE_CELL_INITIALIZER;
static lean_object* lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__121;
static lean_once_cell_t lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__122_once = LEAN_ONCE_CELL_INITIALIZER;
static lean_object* lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__122;
static const lean_string_object lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__123_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 9, .m_capacity = 9, .m_length = 8, .m_data = "relParam"};
static const lean_object* lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__123 = (const lean_object*)&lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__123_value;
static const lean_ctor_object lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__124_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_ctor_object) + sizeof(void*)*2 + 8, .m_other = 2, .m_tag = 1}, .m_objs = {((lean_object*)(((size_t)(0) << 1) | 1)),((lean_object*)&lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__123_value),LEAN_SCALAR_PTR_LITERAL(198, 132, 82, 189, 171, 196, 112, 248)}};
static const lean_object* lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__124 = (const lean_object*)&lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__124_value;
static lean_once_cell_t lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__125_once = LEAN_ONCE_CELL_INITIALIZER;
static lean_object* lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__125;
static lean_once_cell_t lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__126_once = LEAN_ONCE_CELL_INITIALIZER;
static lean_object* lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__126;
static lean_once_cell_t lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__127_once = LEAN_ONCE_CELL_INITIALIZER;
static lean_object* lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__127;
static const lean_string_object lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__128_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 7, .m_capacity = 7, .m_length = 6, .m_data = "length"};
static const lean_object* lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__128 = (const lean_object*)&lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__128_value;
static const lean_ctor_object lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__129_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_ctor_object) + sizeof(void*)*2 + 8, .m_other = 2, .m_tag = 1}, .m_objs = {((lean_object*)(((size_t)(0) << 1) | 1)),((lean_object*)&lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__128_value),LEAN_SCALAR_PTR_LITERAL(69, 96, 6, 102, 8, 206, 152, 82)}};
static const lean_object* lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__129 = (const lean_object*)&lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__129_value;
static lean_once_cell_t lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__130_once = LEAN_ONCE_CELL_INITIALIZER;
static lean_object* lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__130;
static lean_once_cell_t lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__131_once = LEAN_ONCE_CELL_INITIALIZER;
static lean_object* lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__131;
static lean_once_cell_t lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__132_once = LEAN_ONCE_CELL_INITIALIZER;
static lean_object* lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__132;
static const lean_string_object lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__133_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 2, .m_capacity = 2, .m_length = 1, .m_data = "m"};
static const lean_object* lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__133 = (const lean_object*)&lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__133_value;
static const lean_ctor_object lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__134_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_ctor_object) + sizeof(void*)*2 + 8, .m_other = 2, .m_tag = 1}, .m_objs = {((lean_object*)(((size_t)(0) << 1) | 1)),((lean_object*)&lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__133_value),LEAN_SCALAR_PTR_LITERAL(165, 239, 73, 172, 230, 126, 139, 134)}};
static const lean_object* lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__134 = (const lean_object*)&lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__134_value;
static lean_once_cell_t lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__135_once = LEAN_ONCE_CELL_INITIALIZER;
static lean_object* lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__135;
static lean_once_cell_t lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__136_once = LEAN_ONCE_CELL_INITIALIZER;
static lean_object* lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__136;
static lean_once_cell_t lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__137_once = LEAN_ONCE_CELL_INITIALIZER;
static lean_object* lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__137;
static const lean_string_object lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__138_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 2, .m_capacity = 2, .m_length = 1, .m_data = "n"};
static const lean_object* lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__138 = (const lean_object*)&lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__138_value;
static const lean_ctor_object lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__139_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_ctor_object) + sizeof(void*)*2 + 8, .m_other = 2, .m_tag = 1}, .m_objs = {((lean_object*)(((size_t)(0) << 1) | 1)),((lean_object*)&lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__138_value),LEAN_SCALAR_PTR_LITERAL(85, 67, 188, 79, 172, 243, 130, 138)}};
static const lean_object* lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__139 = (const lean_object*)&lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__139_value;
static lean_once_cell_t lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__140_once = LEAN_ONCE_CELL_INITIALIZER;
static lean_object* lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__140;
static lean_once_cell_t lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__141_once = LEAN_ONCE_CELL_INITIALIZER;
static lean_object* lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__141;
static lean_once_cell_t lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__142_once = LEAN_ONCE_CELL_INITIALIZER;
static lean_object* lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__142;
static const lean_string_object lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__143_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 2, .m_capacity = 2, .m_length = 1, .m_data = "p"};
static const lean_object* lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__143 = (const lean_object*)&lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__143_value;
static const lean_ctor_object lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__144_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_ctor_object) + sizeof(void*)*2 + 8, .m_other = 2, .m_tag = 1}, .m_objs = {((lean_object*)(((size_t)(0) << 1) | 1)),((lean_object*)&lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__143_value),LEAN_SCALAR_PTR_LITERAL(34, 153, 146, 175, 179, 220, 230, 134)}};
static const lean_object* lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__144 = (const lean_object*)&lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__144_value;
static lean_once_cell_t lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__145_once = LEAN_ONCE_CELL_INITIALIZER;
static lean_object* lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__145;
static lean_once_cell_t lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__146_once = LEAN_ONCE_CELL_INITIALIZER;
static lean_object* lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__146;
static lean_once_cell_t lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__147_once = LEAN_ONCE_CELL_INITIALIZER;
static lean_object* lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__147;
static const lean_string_object lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__148_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 6, .m_capacity = 6, .m_length = 5, .m_data = "batch"};
static const lean_object* lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__148 = (const lean_object*)&lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__148_value;
static const lean_ctor_object lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__149_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_ctor_object) + sizeof(void*)*2 + 8, .m_other = 2, .m_tag = 1}, .m_objs = {((lean_object*)(((size_t)(0) << 1) | 1)),((lean_object*)&lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__148_value),LEAN_SCALAR_PTR_LITERAL(30, 82, 32, 115, 126, 155, 213, 117)}};
static const lean_object* lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__149 = (const lean_object*)&lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__149_value;
static lean_once_cell_t lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__150_once = LEAN_ONCE_CELL_INITIALIZER;
static lean_object* lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__150;
static lean_once_cell_t lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__151_once = LEAN_ONCE_CELL_INITIALIZER;
static lean_object* lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__151;
static lean_once_cell_t lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__152_once = LEAN_ONCE_CELL_INITIALIZER;
static lean_object* lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__152;
static const lean_string_object lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__153_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 5, .m_capacity = 5, .m_length = 4, .m_data = "work"};
static const lean_object* lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__153 = (const lean_object*)&lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__153_value;
static const lean_ctor_object lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__154_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_ctor_object) + sizeof(void*)*2 + 8, .m_other = 2, .m_tag = 1}, .m_objs = {((lean_object*)(((size_t)(0) << 1) | 1)),((lean_object*)&lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__153_value),LEAN_SCALAR_PTR_LITERAL(145, 180, 227, 144, 115, 0, 122, 91)}};
static const lean_object* lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__154 = (const lean_object*)&lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__154_value;
static lean_once_cell_t lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__155_once = LEAN_ONCE_CELL_INITIALIZER;
static lean_object* lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__155;
static lean_once_cell_t lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__156_once = LEAN_ONCE_CELL_INITIALIZER;
static lean_object* lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__156;
static lean_once_cell_t lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__157_once = LEAN_ONCE_CELL_INITIALIZER;
static lean_object* lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__157;
LEAN_EXPORT lean_object* lp_competition_Bench_Suite_instFromJsonCase_fromJson(lean_object*);
static const lean_closure_object lp_competition_Bench_Suite_instFromJsonCase___closed__0_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_closure_object) + sizeof(void*)*0, .m_other = 0, .m_tag = 245}, .m_fun = (void*)lp_competition_Bench_Suite_instFromJsonCase_fromJson, .m_arity = 1, .m_num_fixed = 0, .m_objs = {} };
static const lean_object* lp_competition_Bench_Suite_instFromJsonCase___closed__0 = (const lean_object*)&lp_competition_Bench_Suite_instFromJsonCase___closed__0_value;
LEAN_EXPORT const lean_object* lp_competition_Bench_Suite_instFromJsonCase = (const lean_object*)&lp_competition_Bench_Suite_instFromJsonCase___closed__0_value;
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_mapMUnsafe_map___at___00Lean_Array_fromJson_x3f___at___00Lean_Json_getObjValAs_x3f___at___00Bench_Suite_instFromJsonPlan_fromJson_spec__0_spec__0_spec__1(size_t, size_t, lean_object*);
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_mapMUnsafe_map___at___00Lean_Array_fromJson_x3f___at___00Lean_Json_getObjValAs_x3f___at___00Bench_Suite_instFromJsonPlan_fromJson_spec__0_spec__0_spec__1___boxed(lean_object*, lean_object*, lean_object*);
static const lean_string_object lp_competition_Lean_Array_fromJson_x3f___at___00Lean_Json_getObjValAs_x3f___at___00Bench_Suite_instFromJsonPlan_fromJson_spec__0_spec__0___closed__0_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 27, .m_capacity = 27, .m_length = 26, .m_data = "expected JSON array, got '"};
static const lean_object* lp_competition_Lean_Array_fromJson_x3f___at___00Lean_Json_getObjValAs_x3f___at___00Bench_Suite_instFromJsonPlan_fromJson_spec__0_spec__0___closed__0 = (const lean_object*)&lp_competition_Lean_Array_fromJson_x3f___at___00Lean_Json_getObjValAs_x3f___at___00Bench_Suite_instFromJsonPlan_fromJson_spec__0_spec__0___closed__0_value;
static const lean_string_object lp_competition_Lean_Array_fromJson_x3f___at___00Lean_Json_getObjValAs_x3f___at___00Bench_Suite_instFromJsonPlan_fromJson_spec__0_spec__0___closed__1_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 2, .m_capacity = 2, .m_length = 1, .m_data = "'"};
static const lean_object* lp_competition_Lean_Array_fromJson_x3f___at___00Lean_Json_getObjValAs_x3f___at___00Bench_Suite_instFromJsonPlan_fromJson_spec__0_spec__0___closed__1 = (const lean_object*)&lp_competition_Lean_Array_fromJson_x3f___at___00Lean_Json_getObjValAs_x3f___at___00Bench_Suite_instFromJsonPlan_fromJson_spec__0_spec__0___closed__1_value;
LEAN_EXPORT lean_object* lp_competition_Lean_Array_fromJson_x3f___at___00Lean_Json_getObjValAs_x3f___at___00Bench_Suite_instFromJsonPlan_fromJson_spec__0_spec__0(lean_object*);
LEAN_EXPORT lean_object* lp_competition_Lean_Json_getObjValAs_x3f___at___00Bench_Suite_instFromJsonPlan_fromJson_spec__0(lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_Lean_Json_getObjValAs_x3f___at___00Bench_Suite_instFromJsonPlan_fromJson_spec__0___boxed(lean_object*, lean_object*);
static const lean_string_object lp_competition_Bench_Suite_instFromJsonPlan_fromJson___closed__0_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 8, .m_capacity = 8, .m_length = 7, .m_data = "version"};
static const lean_object* lp_competition_Bench_Suite_instFromJsonPlan_fromJson___closed__0 = (const lean_object*)&lp_competition_Bench_Suite_instFromJsonPlan_fromJson___closed__0_value;
static const lean_string_object lp_competition_Bench_Suite_instFromJsonPlan_fromJson___closed__1_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 5, .m_capacity = 5, .m_length = 4, .m_data = "Plan"};
static const lean_object* lp_competition_Bench_Suite_instFromJsonPlan_fromJson___closed__1 = (const lean_object*)&lp_competition_Bench_Suite_instFromJsonPlan_fromJson___closed__1_value;
static const lean_ctor_object lp_competition_Bench_Suite_instFromJsonPlan_fromJson___closed__2_value_aux_0 = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_ctor_object) + sizeof(void*)*2 + 8, .m_other = 2, .m_tag = 1}, .m_objs = {((lean_object*)(((size_t)(0) << 1) | 1)),((lean_object*)&lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__1_value),LEAN_SCALAR_PTR_LITERAL(100, 190, 76, 150, 26, 12, 63, 36)}};
static const lean_ctor_object lp_competition_Bench_Suite_instFromJsonPlan_fromJson___closed__2_value_aux_1 = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_ctor_object) + sizeof(void*)*2 + 8, .m_other = 2, .m_tag = 1}, .m_objs = {((lean_object*)&lp_competition_Bench_Suite_instFromJsonPlan_fromJson___closed__2_value_aux_0),((lean_object*)&lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__2_value),LEAN_SCALAR_PTR_LITERAL(41, 253, 102, 34, 90, 216, 165, 14)}};
static const lean_ctor_object lp_competition_Bench_Suite_instFromJsonPlan_fromJson___closed__2_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_ctor_object) + sizeof(void*)*2 + 8, .m_other = 2, .m_tag = 1}, .m_objs = {((lean_object*)&lp_competition_Bench_Suite_instFromJsonPlan_fromJson___closed__2_value_aux_1),((lean_object*)&lp_competition_Bench_Suite_instFromJsonPlan_fromJson___closed__1_value),LEAN_SCALAR_PTR_LITERAL(99, 200, 143, 36, 132, 9, 108, 164)}};
static const lean_object* lp_competition_Bench_Suite_instFromJsonPlan_fromJson___closed__2 = (const lean_object*)&lp_competition_Bench_Suite_instFromJsonPlan_fromJson___closed__2_value;
static lean_once_cell_t lp_competition_Bench_Suite_instFromJsonPlan_fromJson___closed__3_once = LEAN_ONCE_CELL_INITIALIZER;
static lean_object* lp_competition_Bench_Suite_instFromJsonPlan_fromJson___closed__3;
static lean_once_cell_t lp_competition_Bench_Suite_instFromJsonPlan_fromJson___closed__4_once = LEAN_ONCE_CELL_INITIALIZER;
static lean_object* lp_competition_Bench_Suite_instFromJsonPlan_fromJson___closed__4;
static const lean_ctor_object lp_competition_Bench_Suite_instFromJsonPlan_fromJson___closed__5_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_ctor_object) + sizeof(void*)*2 + 8, .m_other = 2, .m_tag = 1}, .m_objs = {((lean_object*)(((size_t)(0) << 1) | 1)),((lean_object*)&lp_competition_Bench_Suite_instFromJsonPlan_fromJson___closed__0_value),LEAN_SCALAR_PTR_LITERAL(167, 68, 50, 73, 160, 48, 142, 108)}};
static const lean_object* lp_competition_Bench_Suite_instFromJsonPlan_fromJson___closed__5 = (const lean_object*)&lp_competition_Bench_Suite_instFromJsonPlan_fromJson___closed__5_value;
static lean_once_cell_t lp_competition_Bench_Suite_instFromJsonPlan_fromJson___closed__6_once = LEAN_ONCE_CELL_INITIALIZER;
static lean_object* lp_competition_Bench_Suite_instFromJsonPlan_fromJson___closed__6;
static lean_once_cell_t lp_competition_Bench_Suite_instFromJsonPlan_fromJson___closed__7_once = LEAN_ONCE_CELL_INITIALIZER;
static lean_object* lp_competition_Bench_Suite_instFromJsonPlan_fromJson___closed__7;
static lean_once_cell_t lp_competition_Bench_Suite_instFromJsonPlan_fromJson___closed__8_once = LEAN_ONCE_CELL_INITIALIZER;
static lean_object* lp_competition_Bench_Suite_instFromJsonPlan_fromJson___closed__8;
static const lean_string_object lp_competition_Bench_Suite_instFromJsonPlan_fromJson___closed__9_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 6, .m_capacity = 6, .m_length = 5, .m_data = "cases"};
static const lean_object* lp_competition_Bench_Suite_instFromJsonPlan_fromJson___closed__9 = (const lean_object*)&lp_competition_Bench_Suite_instFromJsonPlan_fromJson___closed__9_value;
static const lean_ctor_object lp_competition_Bench_Suite_instFromJsonPlan_fromJson___closed__10_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_ctor_object) + sizeof(void*)*2 + 8, .m_other = 2, .m_tag = 1}, .m_objs = {((lean_object*)(((size_t)(0) << 1) | 1)),((lean_object*)&lp_competition_Bench_Suite_instFromJsonPlan_fromJson___closed__9_value),LEAN_SCALAR_PTR_LITERAL(220, 93, 203, 178, 149, 199, 118, 190)}};
static const lean_object* lp_competition_Bench_Suite_instFromJsonPlan_fromJson___closed__10 = (const lean_object*)&lp_competition_Bench_Suite_instFromJsonPlan_fromJson___closed__10_value;
static lean_once_cell_t lp_competition_Bench_Suite_instFromJsonPlan_fromJson___closed__11_once = LEAN_ONCE_CELL_INITIALIZER;
static lean_object* lp_competition_Bench_Suite_instFromJsonPlan_fromJson___closed__11;
static lean_once_cell_t lp_competition_Bench_Suite_instFromJsonPlan_fromJson___closed__12_once = LEAN_ONCE_CELL_INITIALIZER;
static lean_object* lp_competition_Bench_Suite_instFromJsonPlan_fromJson___closed__12;
static lean_once_cell_t lp_competition_Bench_Suite_instFromJsonPlan_fromJson___closed__13_once = LEAN_ONCE_CELL_INITIALIZER;
static lean_object* lp_competition_Bench_Suite_instFromJsonPlan_fromJson___closed__13;
LEAN_EXPORT lean_object* lp_competition_Bench_Suite_instFromJsonPlan_fromJson(lean_object*);
static const lean_closure_object lp_competition_Bench_Suite_instFromJsonPlan___closed__0_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_closure_object) + sizeof(void*)*0, .m_other = 0, .m_tag = 245}, .m_fun = (void*)lp_competition_Bench_Suite_instFromJsonPlan_fromJson, .m_arity = 1, .m_num_fixed = 0, .m_objs = {} };
static const lean_object* lp_competition_Bench_Suite_instFromJsonPlan___closed__0 = (const lean_object*)&lp_competition_Bench_Suite_instFromJsonPlan___closed__0_value;
LEAN_EXPORT const lean_object* lp_competition_Bench_Suite_instFromJsonPlan = (const lean_object*)&lp_competition_Bench_Suite_instFromJsonPlan___closed__0_value;
LEAN_EXPORT uint32_t lp_competition_Bench_Suite_word(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_Bench_Suite_word___boxed(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT uint32_t lp_competition_Bench_Suite_draw(lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_Bench_Suite_draw___boxed(lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_Bench_Suite_pct(uint32_t);
LEAN_EXPORT lean_object* lp_competition_Bench_Suite_pct___boxed(lean_object*);
LEAN_EXPORT lean_object* lp_competition_Bench_Suite_perLakh(uint32_t);
LEAN_EXPORT lean_object* lp_competition_Bench_Suite_perLakh___boxed(lean_object*);
static const lean_ctor_object lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00Bench_Suite_ctz_spec__0___redArg___closed__0_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_ctor_object) + sizeof(void*)*2 + 0, .m_other = 2, .m_tag = 0}, .m_objs = {((lean_object*)(((size_t)(0) << 1) | 1)),((lean_object*)(((size_t)(0) << 1) | 1))}};
static const lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00Bench_Suite_ctz_spec__0___redArg___closed__0 = (const lean_object*)&lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00Bench_Suite_ctz_spec__0___redArg___closed__0_value;
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00Bench_Suite_ctz_spec__0___redArg(uint32_t, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00Bench_Suite_ctz_spec__0___redArg___boxed(lean_object*, lean_object*, lean_object*, lean_object*);
static const lean_ctor_object lp_competition_Bench_Suite_ctz___closed__0_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_ctor_object) + sizeof(void*)*3 + 0, .m_other = 3, .m_tag = 0}, .m_objs = {((lean_object*)(((size_t)(0) << 1) | 1)),((lean_object*)(((size_t)(32) << 1) | 1)),((lean_object*)(((size_t)(1) << 1) | 1))}};
static const lean_object* lp_competition_Bench_Suite_ctz___closed__0 = (const lean_object*)&lp_competition_Bench_Suite_ctz___closed__0_value;
LEAN_EXPORT lean_object* lp_competition_Bench_Suite_ctz(uint32_t);
LEAN_EXPORT lean_object* lp_competition_Bench_Suite_ctz___boxed(lean_object*);
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00Bench_Suite_ctz_spec__0(uint32_t, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00Bench_Suite_ctz_spec__0___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
static lean_once_cell_t lp_competition_Bench_Suite_clampExp___closed__0_once = LEAN_ONCE_CELL_INITIALIZER;
static lean_object* lp_competition_Bench_Suite_clampExp___closed__0;
static lean_once_cell_t lp_competition_Bench_Suite_clampExp___closed__1_once = LEAN_ONCE_CELL_INITIALIZER;
static lean_object* lp_competition_Bench_Suite_clampExp___closed__1;
LEAN_EXPORT uint32_t lp_competition_Bench_Suite_clampExp(lean_object*);
LEAN_EXPORT lean_object* lp_competition_Bench_Suite_clampExp___boxed(lean_object*);
static lean_once_cell_t lp_competition_Bench_Suite_ordinary___closed__0_once = LEAN_ONCE_CELL_INITIALIZER;
static lean_object* lp_competition_Bench_Suite_ordinary___closed__0;
LEAN_EXPORT uint32_t lp_competition_Bench_Suite_ordinary(lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_Bench_Suite_ordinary___boxed(lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00Bench_Suite_nthKind_spec__0___redArg(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00Bench_Suite_nthKind_spec__0___redArg___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
static const lean_ctor_object lp_competition_Bench_Suite_nthKind___closed__0_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_ctor_object) + sizeof(void*)*3 + 0, .m_other = 3, .m_tag = 0}, .m_objs = {((lean_object*)(((size_t)(0) << 1) | 1)),((lean_object*)(((size_t)(5) << 1) | 1)),((lean_object*)(((size_t)(1) << 1) | 1))}};
static const lean_object* lp_competition_Bench_Suite_nthKind___closed__0 = (const lean_object*)&lp_competition_Bench_Suite_nthKind___closed__0_value;
static const lean_ctor_object lp_competition_Bench_Suite_nthKind___closed__1_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_ctor_object) + sizeof(void*)*2 + 0, .m_other = 2, .m_tag = 0}, .m_objs = {((lean_object*)(((size_t)(0) << 1) | 1)),((lean_object*)(((size_t)(0) << 1) | 1))}};
static const lean_object* lp_competition_Bench_Suite_nthKind___closed__1 = (const lean_object*)&lp_competition_Bench_Suite_nthKind___closed__1_value;
LEAN_EXPORT lean_object* lp_competition_Bench_Suite_nthKind(lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_Bench_Suite_nthKind___boxed(lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00Bench_Suite_nthKind_spec__0(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00Bench_Suite_nthKind_spec__0___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_List_countP_go___at___00Bench_Suite_special_spec__0(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_List_countP_go___at___00Bench_Suite_special_spec__0___boxed(lean_object*, lean_object*, lean_object*);
static lean_once_cell_t lp_competition_Bench_Suite_special___closed__0_once = LEAN_ONCE_CELL_INITIALIZER;
static lean_object* lp_competition_Bench_Suite_special___closed__0;
LEAN_EXPORT uint32_t lp_competition_Bench_Suite_special(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_Bench_Suite_special___boxed(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT uint8_t lp_competition_Bench_Suite_isSpecial(lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_Bench_Suite_isSpecial___boxed(lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT uint32_t lp_competition_Bench_Suite_zero(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_Bench_Suite_zero___boxed(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT uint32_t lp_competition_Bench_Suite_element(lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_Bench_Suite_element___boxed(lean_object*, lean_object*, lean_object*, lean_object*);
static const lean_string_object lp_competition_Bench_Suite_partner___closed__0_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 4, .m_capacity = 4, .m_length = 3, .m_data = "add"};
static const lean_object* lp_competition_Bench_Suite_partner___closed__0 = (const lean_object*)&lp_competition_Bench_Suite_partner___closed__0_value;
LEAN_EXPORT uint32_t lp_competition_Bench_Suite_partner(lean_object*, lean_object*, uint32_t);
LEAN_EXPORT lean_object* lp_competition_Bench_Suite_partner___boxed(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT uint32_t lp_competition_Bench_Suite_float(uint32_t);
LEAN_EXPORT lean_object* lp_competition_Bench_Suite_float___boxed(lean_object*);
static const lean_string_object lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00Bench_Suite_measure_spec__0___redArg___closed__0_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 9, .m_capacity = 9, .m_length = 8, .m_data = "unlikely"};
static const lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00Bench_Suite_measure_spec__0___redArg___closed__0 = (const lean_object*)&lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00Bench_Suite_measure_spec__0___redArg___closed__0_value;
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00Bench_Suite_measure_spec__0___redArg(lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00Bench_Suite_measure_spec__0___redArg___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
static const lean_string_object lp_competition_Bench_Suite_measure___closed__0_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 2, .m_capacity = 2, .m_length = 1, .m_data = " "};
static const lean_object* lp_competition_Bench_Suite_measure___closed__0 = (const lean_object*)&lp_competition_Bench_Suite_measure___closed__0_value;
static const lean_string_object lp_competition_Bench_Suite_measure___closed__1_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 6, .m_capacity = 6, .m_length = 5, .m_data = "false"};
static const lean_object* lp_competition_Bench_Suite_measure___closed__1 = (const lean_object*)&lp_competition_Bench_Suite_measure___closed__1_value;
static const lean_string_object lp_competition_Bench_Suite_measure___closed__2_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 5, .m_capacity = 5, .m_length = 4, .m_data = "true"};
static const lean_object* lp_competition_Bench_Suite_measure___closed__2 = (const lean_object*)&lp_competition_Bench_Suite_measure___closed__2_value;
LEAN_EXPORT lean_object* lp_competition_Bench_Suite_measure___boxed__const__1;
LEAN_EXPORT lean_object* lp_competition_Bench_Suite_measure(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_Bench_Suite_measure___boxed(lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00Bench_Suite_measure_spec__0(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00Bench_Suite_measure_spec__0___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_Bench_Suite_runScalar___lam__0(lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_Bench_Suite_runScalar___lam__0___boxed(lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00Bench_Suite_runScalar_spec__0(lean_object*, lean_object*, size_t, size_t, uint32_t);
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00Bench_Suite_runScalar_spec__0___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_Bench_Suite_runScalar___lam__1(lean_object*, lean_object*, uint32_t);
LEAN_EXPORT lean_object* lp_competition_Bench_Suite_runScalar___lam__1___boxed(lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_Bench_Suite_runScalar(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_Bench_Suite_runScalar___boxed(lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT uint32_t lp_competition_Bench_Suite_runSum___lam__0(lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_Bench_Suite_runSum___lam__0___boxed(lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_Bench_Suite_runSum___lam__1(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00Bench_Suite_runSum_spec__0(lean_object*, lean_object*, lean_object*, size_t, size_t, uint32_t);
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00Bench_Suite_runSum_spec__0___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_Bench_Suite_runSum___lam__2(lean_object*, lean_object*, lean_object*, uint32_t);
LEAN_EXPORT lean_object* lp_competition_Bench_Suite_runSum___lam__2___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_Bench_Suite_runSum(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_Bench_Suite_runSum___boxed(lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT uint32_t lp_competition_Bench_Suite_runBmm___lam__0(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_Bench_Suite_runBmm___lam__0___boxed(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT uint32_t lp_competition_Bench_Suite_runBmm___lam__1(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_Bench_Suite_runBmm___lam__1___boxed(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_Bench_Suite_runBmm___lam__2(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, uint32_t);
LEAN_EXPORT lean_object* lp_competition_Bench_Suite_runBmm___lam__2___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_Bench_Suite_runBmm(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_Bench_Suite_runBmm___boxed(lean_object*, lean_object*, lean_object*, lean_object*);
static const lean_string_object lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00Bench_Suite_run_spec__0___closed__0_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 22, .m_capacity = 22, .m_length = 21, .m_data = "empty benchmark case "};
static const lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00Bench_Suite_run_spec__0___closed__0 = (const lean_object*)&lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00Bench_Suite_run_spec__0___closed__0_value;
static const lean_string_object lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00Bench_Suite_run_spec__0___closed__1_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 4, .m_capacity = 4, .m_length = 3, .m_data = "mul"};
static const lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00Bench_Suite_run_spec__0___closed__1 = (const lean_object*)&lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00Bench_Suite_run_spec__0___closed__1_value;
static const lean_string_object lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00Bench_Suite_run_spec__0___closed__2_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 4, .m_capacity = 4, .m_length = 3, .m_data = "sum"};
static const lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00Bench_Suite_run_spec__0___closed__2 = (const lean_object*)&lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00Bench_Suite_run_spec__0___closed__2_value;
static const lean_string_object lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00Bench_Suite_run_spec__0___closed__3_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 4, .m_capacity = 4, .m_length = 3, .m_data = "bmm"};
static const lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00Bench_Suite_run_spec__0___closed__3 = (const lean_object*)&lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00Bench_Suite_run_spec__0___closed__3_value;
static const lean_string_object lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00Bench_Suite_run_spec__0___closed__4_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 25, .m_capacity = 25, .m_length = 24, .m_data = "unknown benchmark kernel"};
static const lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00Bench_Suite_run_spec__0___closed__4 = (const lean_object*)&lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00Bench_Suite_run_spec__0___closed__4_value;
static const lean_ctor_object lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00Bench_Suite_run_spec__0___closed__5_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_ctor_object) + sizeof(void*)*1 + 0, .m_other = 1, .m_tag = 18}, .m_objs = {((lean_object*)&lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00Bench_Suite_run_spec__0___closed__4_value)}};
static const lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00Bench_Suite_run_spec__0___closed__5 = (const lean_object*)&lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00Bench_Suite_run_spec__0___closed__5_value;
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00Bench_Suite_run_spec__0(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, size_t, size_t, lean_object*);
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00Bench_Suite_run_spec__0___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
static const lean_string_object lp_competition_Bench_Suite_run___closed__0_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 11, .m_capacity = 11, .m_length = 10, .m_data = "BENCH_PLAN"};
static const lean_object* lp_competition_Bench_Suite_run___closed__0 = (const lean_object*)&lp_competition_Bench_Suite_run___closed__0_value;
static const lean_string_object lp_competition_Bench_Suite_run___closed__1_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 21, .m_capacity = 21, .m_length = 20, .m_data = "invalid BENCH_PLAN: "};
static const lean_object* lp_competition_Bench_Suite_run___closed__1 = (const lean_object*)&lp_competition_Bench_Suite_run___closed__1_value;
static const lean_string_object lp_competition_Bench_Suite_run___closed__2_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 9, .m_capacity = 9, .m_length = 8, .m_data = "suite-v2"};
static const lean_object* lp_competition_Bench_Suite_run___closed__2 = (const lean_object*)&lp_competition_Bench_Suite_run___closed__2_value;
static const lean_string_object lp_competition_Bench_Suite_run___closed__3_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 27, .m_capacity = 27, .m_length = 26, .m_data = "unsupported benchmark plan"};
static const lean_object* lp_competition_Bench_Suite_run___closed__3 = (const lean_object*)&lp_competition_Bench_Suite_run___closed__3_value;
static const lean_ctor_object lp_competition_Bench_Suite_run___closed__4_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_ctor_object) + sizeof(void*)*1 + 0, .m_other = 1, .m_tag = 18}, .m_objs = {((lean_object*)&lp_competition_Bench_Suite_run___closed__3_value)}};
static const lean_object* lp_competition_Bench_Suite_run___closed__4 = (const lean_object*)&lp_competition_Bench_Suite_run___closed__4_value;
static const lean_string_object lp_competition_Bench_Suite_run___closed__5_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 12, .m_capacity = 12, .m_length = 11, .m_data = "BENCH_INNER"};
static const lean_object* lp_competition_Bench_Suite_run___closed__5 = (const lean_object*)&lp_competition_Bench_Suite_run___closed__5_value;
static const lean_string_object lp_competition_Bench_Suite_run___closed__6_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 29, .m_capacity = 29, .m_length = 28, .m_data = "BENCH_INNER must be positive"};
static const lean_object* lp_competition_Bench_Suite_run___closed__6 = (const lean_object*)&lp_competition_Bench_Suite_run___closed__6_value;
static const lean_ctor_object lp_competition_Bench_Suite_run___closed__7_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_ctor_object) + sizeof(void*)*1 + 0, .m_other = 1, .m_tag = 18}, .m_objs = {((lean_object*)&lp_competition_Bench_Suite_run___closed__6_value)}};
static const lean_object* lp_competition_Bench_Suite_run___closed__7 = (const lean_object*)&lp_competition_Bench_Suite_run___closed__7_value;
static const lean_string_object lp_competition_Bench_Suite_run___closed__8_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 47, .m_capacity = 47, .m_length = 46, .m_data = "BENCH_PLAN is required for the suite benchmark"};
static const lean_object* lp_competition_Bench_Suite_run___closed__8 = (const lean_object*)&lp_competition_Bench_Suite_run___closed__8_value;
static const lean_ctor_object lp_competition_Bench_Suite_run___closed__9_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_ctor_object) + sizeof(void*)*1 + 0, .m_other = 1, .m_tag = 18}, .m_objs = {((lean_object*)&lp_competition_Bench_Suite_run___closed__8_value)}};
static const lean_object* lp_competition_Bench_Suite_run___closed__9 = (const lean_object*)&lp_competition_Bench_Suite_run___closed__9_value;
LEAN_EXPORT lean_object* lp_competition_Bench_Suite_run(lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_Bench_Suite_run___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
static lean_object* _init_lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__5(void){
_start:
{
uint8_t v___x_9_; lean_object* v___x_10_; lean_object* v___x_11_; 
v___x_9_ = 1;
v___x_10_ = ((lean_object*)(lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__4));
v___x_11_ = l_Lean_Name_toStringWithToken___at___00Lean_Name_toString_spec__0(v___x_10_, v___x_9_);
return v___x_11_;
}
}
static lean_object* _init_lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__7(void){
_start:
{
lean_object* v___x_13_; lean_object* v___x_14_; lean_object* v___x_15_; 
v___x_13_ = ((lean_object*)(lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__6));
v___x_14_ = lean_obj_once(&lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__5, &lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__5_once, _init_lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__5);
v___x_15_ = lean_string_append(v___x_14_, v___x_13_);
return v___x_15_;
}
}
static lean_object* _init_lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__9(void){
_start:
{
uint8_t v___x_18_; lean_object* v___x_19_; lean_object* v___x_20_; 
v___x_18_ = 1;
v___x_19_ = ((lean_object*)(lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__8));
v___x_20_ = l_Lean_Name_toStringWithToken___at___00Lean_Name_toString_spec__0(v___x_19_, v___x_18_);
return v___x_20_;
}
}
static lean_object* _init_lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__10(void){
_start:
{
lean_object* v___x_21_; lean_object* v___x_22_; lean_object* v___x_23_; 
v___x_21_ = lean_obj_once(&lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__9, &lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__9_once, _init_lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__9);
v___x_22_ = lean_obj_once(&lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__7, &lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__7_once, _init_lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__7);
v___x_23_ = lean_string_append(v___x_22_, v___x_21_);
return v___x_23_;
}
}
static lean_object* _init_lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__12(void){
_start:
{
lean_object* v___x_25_; lean_object* v___x_26_; lean_object* v___x_27_; 
v___x_25_ = ((lean_object*)(lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__11));
v___x_26_ = lean_obj_once(&lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__10, &lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__10_once, _init_lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__10);
v___x_27_ = lean_string_append(v___x_26_, v___x_25_);
return v___x_27_;
}
}
static lean_object* _init_lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__15(void){
_start:
{
uint8_t v___x_31_; lean_object* v___x_32_; lean_object* v___x_33_; 
v___x_31_ = 1;
v___x_32_ = ((lean_object*)(lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__14));
v___x_33_ = l_Lean_Name_toStringWithToken___at___00Lean_Name_toString_spec__0(v___x_32_, v___x_31_);
return v___x_33_;
}
}
static lean_object* _init_lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__16(void){
_start:
{
lean_object* v___x_34_; lean_object* v___x_35_; lean_object* v___x_36_; 
v___x_34_ = lean_obj_once(&lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__15, &lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__15_once, _init_lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__15);
v___x_35_ = lean_obj_once(&lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__7, &lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__7_once, _init_lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__7);
v___x_36_ = lean_string_append(v___x_35_, v___x_34_);
return v___x_36_;
}
}
static lean_object* _init_lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__17(void){
_start:
{
lean_object* v___x_37_; lean_object* v___x_38_; lean_object* v___x_39_; 
v___x_37_ = ((lean_object*)(lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__11));
v___x_38_ = lean_obj_once(&lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__16, &lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__16_once, _init_lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__16);
v___x_39_ = lean_string_append(v___x_38_, v___x_37_);
return v___x_39_;
}
}
static lean_object* _init_lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__20(void){
_start:
{
uint8_t v___x_43_; lean_object* v___x_44_; lean_object* v___x_45_; 
v___x_43_ = 1;
v___x_44_ = ((lean_object*)(lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__19));
v___x_45_ = l_Lean_Name_toStringWithToken___at___00Lean_Name_toString_spec__0(v___x_44_, v___x_43_);
return v___x_45_;
}
}
static lean_object* _init_lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__21(void){
_start:
{
lean_object* v___x_46_; lean_object* v___x_47_; lean_object* v___x_48_; 
v___x_46_ = lean_obj_once(&lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__20, &lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__20_once, _init_lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__20);
v___x_47_ = lean_obj_once(&lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__7, &lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__7_once, _init_lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__7);
v___x_48_ = lean_string_append(v___x_47_, v___x_46_);
return v___x_48_;
}
}
static lean_object* _init_lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__22(void){
_start:
{
lean_object* v___x_49_; lean_object* v___x_50_; lean_object* v___x_51_; 
v___x_49_ = ((lean_object*)(lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__11));
v___x_50_ = lean_obj_once(&lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__21, &lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__21_once, _init_lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__21);
v___x_51_ = lean_string_append(v___x_50_, v___x_49_);
return v___x_51_;
}
}
static lean_object* _init_lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__25(void){
_start:
{
uint8_t v___x_55_; lean_object* v___x_56_; lean_object* v___x_57_; 
v___x_55_ = 1;
v___x_56_ = ((lean_object*)(lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__24));
v___x_57_ = l_Lean_Name_toStringWithToken___at___00Lean_Name_toString_spec__0(v___x_56_, v___x_55_);
return v___x_57_;
}
}
static lean_object* _init_lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__26(void){
_start:
{
lean_object* v___x_58_; lean_object* v___x_59_; lean_object* v___x_60_; 
v___x_58_ = lean_obj_once(&lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__25, &lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__25_once, _init_lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__25);
v___x_59_ = lean_obj_once(&lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__7, &lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__7_once, _init_lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__7);
v___x_60_ = lean_string_append(v___x_59_, v___x_58_);
return v___x_60_;
}
}
static lean_object* _init_lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__27(void){
_start:
{
lean_object* v___x_61_; lean_object* v___x_62_; lean_object* v___x_63_; 
v___x_61_ = ((lean_object*)(lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__11));
v___x_62_ = lean_obj_once(&lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__26, &lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__26_once, _init_lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__26);
v___x_63_ = lean_string_append(v___x_62_, v___x_61_);
return v___x_63_;
}
}
static lean_object* _init_lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__30(void){
_start:
{
uint8_t v___x_67_; lean_object* v___x_68_; lean_object* v___x_69_; 
v___x_67_ = 1;
v___x_68_ = ((lean_object*)(lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__29));
v___x_69_ = l_Lean_Name_toStringWithToken___at___00Lean_Name_toString_spec__0(v___x_68_, v___x_67_);
return v___x_69_;
}
}
static lean_object* _init_lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__31(void){
_start:
{
lean_object* v___x_70_; lean_object* v___x_71_; lean_object* v___x_72_; 
v___x_70_ = lean_obj_once(&lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__30, &lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__30_once, _init_lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__30);
v___x_71_ = lean_obj_once(&lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__7, &lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__7_once, _init_lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__7);
v___x_72_ = lean_string_append(v___x_71_, v___x_70_);
return v___x_72_;
}
}
static lean_object* _init_lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__32(void){
_start:
{
lean_object* v___x_73_; lean_object* v___x_74_; lean_object* v___x_75_; 
v___x_73_ = ((lean_object*)(lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__11));
v___x_74_ = lean_obj_once(&lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__31, &lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__31_once, _init_lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__31);
v___x_75_ = lean_string_append(v___x_74_, v___x_73_);
return v___x_75_;
}
}
static lean_object* _init_lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__35(void){
_start:
{
uint8_t v___x_79_; lean_object* v___x_80_; lean_object* v___x_81_; 
v___x_79_ = 1;
v___x_80_ = ((lean_object*)(lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__34));
v___x_81_ = l_Lean_Name_toStringWithToken___at___00Lean_Name_toString_spec__0(v___x_80_, v___x_79_);
return v___x_81_;
}
}
static lean_object* _init_lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__36(void){
_start:
{
lean_object* v___x_82_; lean_object* v___x_83_; lean_object* v___x_84_; 
v___x_82_ = lean_obj_once(&lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__35, &lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__35_once, _init_lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__35);
v___x_83_ = lean_obj_once(&lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__7, &lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__7_once, _init_lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__7);
v___x_84_ = lean_string_append(v___x_83_, v___x_82_);
return v___x_84_;
}
}
static lean_object* _init_lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__37(void){
_start:
{
lean_object* v___x_85_; lean_object* v___x_86_; lean_object* v___x_87_; 
v___x_85_ = ((lean_object*)(lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__11));
v___x_86_ = lean_obj_once(&lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__36, &lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__36_once, _init_lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__36);
v___x_87_ = lean_string_append(v___x_86_, v___x_85_);
return v___x_87_;
}
}
static lean_object* _init_lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__40(void){
_start:
{
uint8_t v___x_91_; lean_object* v___x_92_; lean_object* v___x_93_; 
v___x_91_ = 1;
v___x_92_ = ((lean_object*)(lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__39));
v___x_93_ = l_Lean_Name_toStringWithToken___at___00Lean_Name_toString_spec__0(v___x_92_, v___x_91_);
return v___x_93_;
}
}
static lean_object* _init_lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__41(void){
_start:
{
lean_object* v___x_94_; lean_object* v___x_95_; lean_object* v___x_96_; 
v___x_94_ = lean_obj_once(&lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__40, &lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__40_once, _init_lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__40);
v___x_95_ = lean_obj_once(&lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__7, &lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__7_once, _init_lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__7);
v___x_96_ = lean_string_append(v___x_95_, v___x_94_);
return v___x_96_;
}
}
static lean_object* _init_lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__42(void){
_start:
{
lean_object* v___x_97_; lean_object* v___x_98_; lean_object* v___x_99_; 
v___x_97_ = ((lean_object*)(lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__11));
v___x_98_ = lean_obj_once(&lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__41, &lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__41_once, _init_lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__41);
v___x_99_ = lean_string_append(v___x_98_, v___x_97_);
return v___x_99_;
}
}
static lean_object* _init_lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__45(void){
_start:
{
uint8_t v___x_103_; lean_object* v___x_104_; lean_object* v___x_105_; 
v___x_103_ = 1;
v___x_104_ = ((lean_object*)(lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__44));
v___x_105_ = l_Lean_Name_toStringWithToken___at___00Lean_Name_toString_spec__0(v___x_104_, v___x_103_);
return v___x_105_;
}
}
static lean_object* _init_lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__46(void){
_start:
{
lean_object* v___x_106_; lean_object* v___x_107_; lean_object* v___x_108_; 
v___x_106_ = lean_obj_once(&lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__45, &lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__45_once, _init_lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__45);
v___x_107_ = lean_obj_once(&lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__7, &lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__7_once, _init_lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__7);
v___x_108_ = lean_string_append(v___x_107_, v___x_106_);
return v___x_108_;
}
}
static lean_object* _init_lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__47(void){
_start:
{
lean_object* v___x_109_; lean_object* v___x_110_; lean_object* v___x_111_; 
v___x_109_ = ((lean_object*)(lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__11));
v___x_110_ = lean_obj_once(&lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__46, &lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__46_once, _init_lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__46);
v___x_111_ = lean_string_append(v___x_110_, v___x_109_);
return v___x_111_;
}
}
static lean_object* _init_lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__50(void){
_start:
{
uint8_t v___x_115_; lean_object* v___x_116_; lean_object* v___x_117_; 
v___x_115_ = 1;
v___x_116_ = ((lean_object*)(lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__49));
v___x_117_ = l_Lean_Name_toStringWithToken___at___00Lean_Name_toString_spec__0(v___x_116_, v___x_115_);
return v___x_117_;
}
}
static lean_object* _init_lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__51(void){
_start:
{
lean_object* v___x_118_; lean_object* v___x_119_; lean_object* v___x_120_; 
v___x_118_ = lean_obj_once(&lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__50, &lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__50_once, _init_lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__50);
v___x_119_ = lean_obj_once(&lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__7, &lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__7_once, _init_lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__7);
v___x_120_ = lean_string_append(v___x_119_, v___x_118_);
return v___x_120_;
}
}
static lean_object* _init_lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__52(void){
_start:
{
lean_object* v___x_121_; lean_object* v___x_122_; lean_object* v___x_123_; 
v___x_121_ = ((lean_object*)(lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__11));
v___x_122_ = lean_obj_once(&lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__51, &lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__51_once, _init_lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__51);
v___x_123_ = lean_string_append(v___x_122_, v___x_121_);
return v___x_123_;
}
}
static lean_object* _init_lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__55(void){
_start:
{
uint8_t v___x_127_; lean_object* v___x_128_; lean_object* v___x_129_; 
v___x_127_ = 1;
v___x_128_ = ((lean_object*)(lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__54));
v___x_129_ = l_Lean_Name_toStringWithToken___at___00Lean_Name_toString_spec__0(v___x_128_, v___x_127_);
return v___x_129_;
}
}
static lean_object* _init_lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__56(void){
_start:
{
lean_object* v___x_130_; lean_object* v___x_131_; lean_object* v___x_132_; 
v___x_130_ = lean_obj_once(&lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__55, &lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__55_once, _init_lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__55);
v___x_131_ = lean_obj_once(&lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__7, &lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__7_once, _init_lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__7);
v___x_132_ = lean_string_append(v___x_131_, v___x_130_);
return v___x_132_;
}
}
static lean_object* _init_lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__57(void){
_start:
{
lean_object* v___x_133_; lean_object* v___x_134_; lean_object* v___x_135_; 
v___x_133_ = ((lean_object*)(lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__11));
v___x_134_ = lean_obj_once(&lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__56, &lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__56_once, _init_lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__56);
v___x_135_ = lean_string_append(v___x_134_, v___x_133_);
return v___x_135_;
}
}
static lean_object* _init_lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__60(void){
_start:
{
uint8_t v___x_139_; lean_object* v___x_140_; lean_object* v___x_141_; 
v___x_139_ = 1;
v___x_140_ = ((lean_object*)(lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__59));
v___x_141_ = l_Lean_Name_toStringWithToken___at___00Lean_Name_toString_spec__0(v___x_140_, v___x_139_);
return v___x_141_;
}
}
static lean_object* _init_lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__61(void){
_start:
{
lean_object* v___x_142_; lean_object* v___x_143_; lean_object* v___x_144_; 
v___x_142_ = lean_obj_once(&lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__60, &lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__60_once, _init_lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__60);
v___x_143_ = lean_obj_once(&lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__7, &lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__7_once, _init_lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__7);
v___x_144_ = lean_string_append(v___x_143_, v___x_142_);
return v___x_144_;
}
}
static lean_object* _init_lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__62(void){
_start:
{
lean_object* v___x_145_; lean_object* v___x_146_; lean_object* v___x_147_; 
v___x_145_ = ((lean_object*)(lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__11));
v___x_146_ = lean_obj_once(&lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__61, &lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__61_once, _init_lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__61);
v___x_147_ = lean_string_append(v___x_146_, v___x_145_);
return v___x_147_;
}
}
static lean_object* _init_lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__65(void){
_start:
{
uint8_t v___x_151_; lean_object* v___x_152_; lean_object* v___x_153_; 
v___x_151_ = 1;
v___x_152_ = ((lean_object*)(lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__64));
v___x_153_ = l_Lean_Name_toStringWithToken___at___00Lean_Name_toString_spec__0(v___x_152_, v___x_151_);
return v___x_153_;
}
}
static lean_object* _init_lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__66(void){
_start:
{
lean_object* v___x_154_; lean_object* v___x_155_; lean_object* v___x_156_; 
v___x_154_ = lean_obj_once(&lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__65, &lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__65_once, _init_lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__65);
v___x_155_ = lean_obj_once(&lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__7, &lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__7_once, _init_lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__7);
v___x_156_ = lean_string_append(v___x_155_, v___x_154_);
return v___x_156_;
}
}
static lean_object* _init_lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__67(void){
_start:
{
lean_object* v___x_157_; lean_object* v___x_158_; lean_object* v___x_159_; 
v___x_157_ = ((lean_object*)(lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__11));
v___x_158_ = lean_obj_once(&lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__66, &lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__66_once, _init_lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__66);
v___x_159_ = lean_string_append(v___x_158_, v___x_157_);
return v___x_159_;
}
}
static lean_object* _init_lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__70(void){
_start:
{
uint8_t v___x_163_; lean_object* v___x_164_; lean_object* v___x_165_; 
v___x_163_ = 1;
v___x_164_ = ((lean_object*)(lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__69));
v___x_165_ = l_Lean_Name_toStringWithToken___at___00Lean_Name_toString_spec__0(v___x_164_, v___x_163_);
return v___x_165_;
}
}
static lean_object* _init_lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__71(void){
_start:
{
lean_object* v___x_166_; lean_object* v___x_167_; lean_object* v___x_168_; 
v___x_166_ = lean_obj_once(&lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__70, &lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__70_once, _init_lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__70);
v___x_167_ = lean_obj_once(&lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__7, &lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__7_once, _init_lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__7);
v___x_168_ = lean_string_append(v___x_167_, v___x_166_);
return v___x_168_;
}
}
static lean_object* _init_lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__72(void){
_start:
{
lean_object* v___x_169_; lean_object* v___x_170_; lean_object* v___x_171_; 
v___x_169_ = ((lean_object*)(lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__11));
v___x_170_ = lean_obj_once(&lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__71, &lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__71_once, _init_lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__71);
v___x_171_ = lean_string_append(v___x_170_, v___x_169_);
return v___x_171_;
}
}
static lean_object* _init_lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__75(void){
_start:
{
uint8_t v___x_175_; lean_object* v___x_176_; lean_object* v___x_177_; 
v___x_175_ = 1;
v___x_176_ = ((lean_object*)(lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__74));
v___x_177_ = l_Lean_Name_toStringWithToken___at___00Lean_Name_toString_spec__0(v___x_176_, v___x_175_);
return v___x_177_;
}
}
static lean_object* _init_lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__76(void){
_start:
{
lean_object* v___x_178_; lean_object* v___x_179_; lean_object* v___x_180_; 
v___x_178_ = lean_obj_once(&lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__75, &lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__75_once, _init_lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__75);
v___x_179_ = lean_obj_once(&lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__7, &lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__7_once, _init_lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__7);
v___x_180_ = lean_string_append(v___x_179_, v___x_178_);
return v___x_180_;
}
}
static lean_object* _init_lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__77(void){
_start:
{
lean_object* v___x_181_; lean_object* v___x_182_; lean_object* v___x_183_; 
v___x_181_ = ((lean_object*)(lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__11));
v___x_182_ = lean_obj_once(&lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__76, &lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__76_once, _init_lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__76);
v___x_183_ = lean_string_append(v___x_182_, v___x_181_);
return v___x_183_;
}
}
static lean_object* _init_lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__80(void){
_start:
{
uint8_t v___x_187_; lean_object* v___x_188_; lean_object* v___x_189_; 
v___x_187_ = 1;
v___x_188_ = ((lean_object*)(lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__79));
v___x_189_ = l_Lean_Name_toStringWithToken___at___00Lean_Name_toString_spec__0(v___x_188_, v___x_187_);
return v___x_189_;
}
}
static lean_object* _init_lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__81(void){
_start:
{
lean_object* v___x_190_; lean_object* v___x_191_; lean_object* v___x_192_; 
v___x_190_ = lean_obj_once(&lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__80, &lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__80_once, _init_lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__80);
v___x_191_ = lean_obj_once(&lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__7, &lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__7_once, _init_lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__7);
v___x_192_ = lean_string_append(v___x_191_, v___x_190_);
return v___x_192_;
}
}
static lean_object* _init_lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__82(void){
_start:
{
lean_object* v___x_193_; lean_object* v___x_194_; lean_object* v___x_195_; 
v___x_193_ = ((lean_object*)(lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__11));
v___x_194_ = lean_obj_once(&lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__81, &lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__81_once, _init_lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__81);
v___x_195_ = lean_string_append(v___x_194_, v___x_193_);
return v___x_195_;
}
}
static lean_object* _init_lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__85(void){
_start:
{
uint8_t v___x_199_; lean_object* v___x_200_; lean_object* v___x_201_; 
v___x_199_ = 1;
v___x_200_ = ((lean_object*)(lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__84));
v___x_201_ = l_Lean_Name_toStringWithToken___at___00Lean_Name_toString_spec__0(v___x_200_, v___x_199_);
return v___x_201_;
}
}
static lean_object* _init_lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__86(void){
_start:
{
lean_object* v___x_202_; lean_object* v___x_203_; lean_object* v___x_204_; 
v___x_202_ = lean_obj_once(&lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__85, &lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__85_once, _init_lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__85);
v___x_203_ = lean_obj_once(&lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__7, &lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__7_once, _init_lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__7);
v___x_204_ = lean_string_append(v___x_203_, v___x_202_);
return v___x_204_;
}
}
static lean_object* _init_lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__87(void){
_start:
{
lean_object* v___x_205_; lean_object* v___x_206_; lean_object* v___x_207_; 
v___x_205_ = ((lean_object*)(lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__11));
v___x_206_ = lean_obj_once(&lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__86, &lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__86_once, _init_lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__86);
v___x_207_ = lean_string_append(v___x_206_, v___x_205_);
return v___x_207_;
}
}
static lean_object* _init_lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__90(void){
_start:
{
uint8_t v___x_211_; lean_object* v___x_212_; lean_object* v___x_213_; 
v___x_211_ = 1;
v___x_212_ = ((lean_object*)(lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__89));
v___x_213_ = l_Lean_Name_toStringWithToken___at___00Lean_Name_toString_spec__0(v___x_212_, v___x_211_);
return v___x_213_;
}
}
static lean_object* _init_lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__91(void){
_start:
{
lean_object* v___x_214_; lean_object* v___x_215_; lean_object* v___x_216_; 
v___x_214_ = lean_obj_once(&lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__90, &lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__90_once, _init_lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__90);
v___x_215_ = lean_obj_once(&lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__7, &lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__7_once, _init_lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__7);
v___x_216_ = lean_string_append(v___x_215_, v___x_214_);
return v___x_216_;
}
}
static lean_object* _init_lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__92(void){
_start:
{
lean_object* v___x_217_; lean_object* v___x_218_; lean_object* v___x_219_; 
v___x_217_ = ((lean_object*)(lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__11));
v___x_218_ = lean_obj_once(&lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__91, &lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__91_once, _init_lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__91);
v___x_219_ = lean_string_append(v___x_218_, v___x_217_);
return v___x_219_;
}
}
static lean_object* _init_lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__95(void){
_start:
{
uint8_t v___x_223_; lean_object* v___x_224_; lean_object* v___x_225_; 
v___x_223_ = 1;
v___x_224_ = ((lean_object*)(lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__94));
v___x_225_ = l_Lean_Name_toStringWithToken___at___00Lean_Name_toString_spec__0(v___x_224_, v___x_223_);
return v___x_225_;
}
}
static lean_object* _init_lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__96(void){
_start:
{
lean_object* v___x_226_; lean_object* v___x_227_; lean_object* v___x_228_; 
v___x_226_ = lean_obj_once(&lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__95, &lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__95_once, _init_lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__95);
v___x_227_ = lean_obj_once(&lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__7, &lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__7_once, _init_lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__7);
v___x_228_ = lean_string_append(v___x_227_, v___x_226_);
return v___x_228_;
}
}
static lean_object* _init_lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__97(void){
_start:
{
lean_object* v___x_229_; lean_object* v___x_230_; lean_object* v___x_231_; 
v___x_229_ = ((lean_object*)(lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__11));
v___x_230_ = lean_obj_once(&lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__96, &lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__96_once, _init_lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__96);
v___x_231_ = lean_string_append(v___x_230_, v___x_229_);
return v___x_231_;
}
}
static lean_object* _init_lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__100(void){
_start:
{
uint8_t v___x_235_; lean_object* v___x_236_; lean_object* v___x_237_; 
v___x_235_ = 1;
v___x_236_ = ((lean_object*)(lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__99));
v___x_237_ = l_Lean_Name_toStringWithToken___at___00Lean_Name_toString_spec__0(v___x_236_, v___x_235_);
return v___x_237_;
}
}
static lean_object* _init_lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__101(void){
_start:
{
lean_object* v___x_238_; lean_object* v___x_239_; lean_object* v___x_240_; 
v___x_238_ = lean_obj_once(&lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__100, &lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__100_once, _init_lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__100);
v___x_239_ = lean_obj_once(&lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__7, &lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__7_once, _init_lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__7);
v___x_240_ = lean_string_append(v___x_239_, v___x_238_);
return v___x_240_;
}
}
static lean_object* _init_lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__102(void){
_start:
{
lean_object* v___x_241_; lean_object* v___x_242_; lean_object* v___x_243_; 
v___x_241_ = ((lean_object*)(lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__11));
v___x_242_ = lean_obj_once(&lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__101, &lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__101_once, _init_lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__101);
v___x_243_ = lean_string_append(v___x_242_, v___x_241_);
return v___x_243_;
}
}
static lean_object* _init_lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__105(void){
_start:
{
uint8_t v___x_247_; lean_object* v___x_248_; lean_object* v___x_249_; 
v___x_247_ = 1;
v___x_248_ = ((lean_object*)(lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__104));
v___x_249_ = l_Lean_Name_toStringWithToken___at___00Lean_Name_toString_spec__0(v___x_248_, v___x_247_);
return v___x_249_;
}
}
static lean_object* _init_lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__106(void){
_start:
{
lean_object* v___x_250_; lean_object* v___x_251_; lean_object* v___x_252_; 
v___x_250_ = lean_obj_once(&lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__105, &lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__105_once, _init_lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__105);
v___x_251_ = lean_obj_once(&lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__7, &lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__7_once, _init_lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__7);
v___x_252_ = lean_string_append(v___x_251_, v___x_250_);
return v___x_252_;
}
}
static lean_object* _init_lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__107(void){
_start:
{
lean_object* v___x_253_; lean_object* v___x_254_; lean_object* v___x_255_; 
v___x_253_ = ((lean_object*)(lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__11));
v___x_254_ = lean_obj_once(&lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__106, &lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__106_once, _init_lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__106);
v___x_255_ = lean_string_append(v___x_254_, v___x_253_);
return v___x_255_;
}
}
static lean_object* _init_lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__110(void){
_start:
{
uint8_t v___x_259_; lean_object* v___x_260_; lean_object* v___x_261_; 
v___x_259_ = 1;
v___x_260_ = ((lean_object*)(lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__109));
v___x_261_ = l_Lean_Name_toStringWithToken___at___00Lean_Name_toString_spec__0(v___x_260_, v___x_259_);
return v___x_261_;
}
}
static lean_object* _init_lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__111(void){
_start:
{
lean_object* v___x_262_; lean_object* v___x_263_; lean_object* v___x_264_; 
v___x_262_ = lean_obj_once(&lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__110, &lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__110_once, _init_lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__110);
v___x_263_ = lean_obj_once(&lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__7, &lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__7_once, _init_lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__7);
v___x_264_ = lean_string_append(v___x_263_, v___x_262_);
return v___x_264_;
}
}
static lean_object* _init_lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__112(void){
_start:
{
lean_object* v___x_265_; lean_object* v___x_266_; lean_object* v___x_267_; 
v___x_265_ = ((lean_object*)(lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__11));
v___x_266_ = lean_obj_once(&lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__111, &lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__111_once, _init_lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__111);
v___x_267_ = lean_string_append(v___x_266_, v___x_265_);
return v___x_267_;
}
}
static lean_object* _init_lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__115(void){
_start:
{
uint8_t v___x_271_; lean_object* v___x_272_; lean_object* v___x_273_; 
v___x_271_ = 1;
v___x_272_ = ((lean_object*)(lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__114));
v___x_273_ = l_Lean_Name_toStringWithToken___at___00Lean_Name_toString_spec__0(v___x_272_, v___x_271_);
return v___x_273_;
}
}
static lean_object* _init_lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__116(void){
_start:
{
lean_object* v___x_274_; lean_object* v___x_275_; lean_object* v___x_276_; 
v___x_274_ = lean_obj_once(&lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__115, &lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__115_once, _init_lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__115);
v___x_275_ = lean_obj_once(&lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__7, &lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__7_once, _init_lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__7);
v___x_276_ = lean_string_append(v___x_275_, v___x_274_);
return v___x_276_;
}
}
static lean_object* _init_lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__117(void){
_start:
{
lean_object* v___x_277_; lean_object* v___x_278_; lean_object* v___x_279_; 
v___x_277_ = ((lean_object*)(lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__11));
v___x_278_ = lean_obj_once(&lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__116, &lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__116_once, _init_lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__116);
v___x_279_ = lean_string_append(v___x_278_, v___x_277_);
return v___x_279_;
}
}
static lean_object* _init_lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__120(void){
_start:
{
uint8_t v___x_283_; lean_object* v___x_284_; lean_object* v___x_285_; 
v___x_283_ = 1;
v___x_284_ = ((lean_object*)(lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__119));
v___x_285_ = l_Lean_Name_toStringWithToken___at___00Lean_Name_toString_spec__0(v___x_284_, v___x_283_);
return v___x_285_;
}
}
static lean_object* _init_lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__121(void){
_start:
{
lean_object* v___x_286_; lean_object* v___x_287_; lean_object* v___x_288_; 
v___x_286_ = lean_obj_once(&lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__120, &lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__120_once, _init_lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__120);
v___x_287_ = lean_obj_once(&lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__7, &lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__7_once, _init_lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__7);
v___x_288_ = lean_string_append(v___x_287_, v___x_286_);
return v___x_288_;
}
}
static lean_object* _init_lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__122(void){
_start:
{
lean_object* v___x_289_; lean_object* v___x_290_; lean_object* v___x_291_; 
v___x_289_ = ((lean_object*)(lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__11));
v___x_290_ = lean_obj_once(&lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__121, &lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__121_once, _init_lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__121);
v___x_291_ = lean_string_append(v___x_290_, v___x_289_);
return v___x_291_;
}
}
static lean_object* _init_lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__125(void){
_start:
{
uint8_t v___x_295_; lean_object* v___x_296_; lean_object* v___x_297_; 
v___x_295_ = 1;
v___x_296_ = ((lean_object*)(lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__124));
v___x_297_ = l_Lean_Name_toStringWithToken___at___00Lean_Name_toString_spec__0(v___x_296_, v___x_295_);
return v___x_297_;
}
}
static lean_object* _init_lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__126(void){
_start:
{
lean_object* v___x_298_; lean_object* v___x_299_; lean_object* v___x_300_; 
v___x_298_ = lean_obj_once(&lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__125, &lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__125_once, _init_lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__125);
v___x_299_ = lean_obj_once(&lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__7, &lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__7_once, _init_lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__7);
v___x_300_ = lean_string_append(v___x_299_, v___x_298_);
return v___x_300_;
}
}
static lean_object* _init_lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__127(void){
_start:
{
lean_object* v___x_301_; lean_object* v___x_302_; lean_object* v___x_303_; 
v___x_301_ = ((lean_object*)(lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__11));
v___x_302_ = lean_obj_once(&lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__126, &lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__126_once, _init_lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__126);
v___x_303_ = lean_string_append(v___x_302_, v___x_301_);
return v___x_303_;
}
}
static lean_object* _init_lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__130(void){
_start:
{
uint8_t v___x_307_; lean_object* v___x_308_; lean_object* v___x_309_; 
v___x_307_ = 1;
v___x_308_ = ((lean_object*)(lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__129));
v___x_309_ = l_Lean_Name_toStringWithToken___at___00Lean_Name_toString_spec__0(v___x_308_, v___x_307_);
return v___x_309_;
}
}
static lean_object* _init_lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__131(void){
_start:
{
lean_object* v___x_310_; lean_object* v___x_311_; lean_object* v___x_312_; 
v___x_310_ = lean_obj_once(&lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__130, &lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__130_once, _init_lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__130);
v___x_311_ = lean_obj_once(&lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__7, &lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__7_once, _init_lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__7);
v___x_312_ = lean_string_append(v___x_311_, v___x_310_);
return v___x_312_;
}
}
static lean_object* _init_lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__132(void){
_start:
{
lean_object* v___x_313_; lean_object* v___x_314_; lean_object* v___x_315_; 
v___x_313_ = ((lean_object*)(lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__11));
v___x_314_ = lean_obj_once(&lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__131, &lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__131_once, _init_lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__131);
v___x_315_ = lean_string_append(v___x_314_, v___x_313_);
return v___x_315_;
}
}
static lean_object* _init_lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__135(void){
_start:
{
uint8_t v___x_319_; lean_object* v___x_320_; lean_object* v___x_321_; 
v___x_319_ = 1;
v___x_320_ = ((lean_object*)(lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__134));
v___x_321_ = l_Lean_Name_toStringWithToken___at___00Lean_Name_toString_spec__0(v___x_320_, v___x_319_);
return v___x_321_;
}
}
static lean_object* _init_lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__136(void){
_start:
{
lean_object* v___x_322_; lean_object* v___x_323_; lean_object* v___x_324_; 
v___x_322_ = lean_obj_once(&lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__135, &lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__135_once, _init_lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__135);
v___x_323_ = lean_obj_once(&lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__7, &lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__7_once, _init_lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__7);
v___x_324_ = lean_string_append(v___x_323_, v___x_322_);
return v___x_324_;
}
}
static lean_object* _init_lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__137(void){
_start:
{
lean_object* v___x_325_; lean_object* v___x_326_; lean_object* v___x_327_; 
v___x_325_ = ((lean_object*)(lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__11));
v___x_326_ = lean_obj_once(&lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__136, &lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__136_once, _init_lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__136);
v___x_327_ = lean_string_append(v___x_326_, v___x_325_);
return v___x_327_;
}
}
static lean_object* _init_lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__140(void){
_start:
{
uint8_t v___x_331_; lean_object* v___x_332_; lean_object* v___x_333_; 
v___x_331_ = 1;
v___x_332_ = ((lean_object*)(lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__139));
v___x_333_ = l_Lean_Name_toStringWithToken___at___00Lean_Name_toString_spec__0(v___x_332_, v___x_331_);
return v___x_333_;
}
}
static lean_object* _init_lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__141(void){
_start:
{
lean_object* v___x_334_; lean_object* v___x_335_; lean_object* v___x_336_; 
v___x_334_ = lean_obj_once(&lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__140, &lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__140_once, _init_lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__140);
v___x_335_ = lean_obj_once(&lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__7, &lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__7_once, _init_lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__7);
v___x_336_ = lean_string_append(v___x_335_, v___x_334_);
return v___x_336_;
}
}
static lean_object* _init_lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__142(void){
_start:
{
lean_object* v___x_337_; lean_object* v___x_338_; lean_object* v___x_339_; 
v___x_337_ = ((lean_object*)(lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__11));
v___x_338_ = lean_obj_once(&lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__141, &lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__141_once, _init_lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__141);
v___x_339_ = lean_string_append(v___x_338_, v___x_337_);
return v___x_339_;
}
}
static lean_object* _init_lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__145(void){
_start:
{
uint8_t v___x_343_; lean_object* v___x_344_; lean_object* v___x_345_; 
v___x_343_ = 1;
v___x_344_ = ((lean_object*)(lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__144));
v___x_345_ = l_Lean_Name_toStringWithToken___at___00Lean_Name_toString_spec__0(v___x_344_, v___x_343_);
return v___x_345_;
}
}
static lean_object* _init_lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__146(void){
_start:
{
lean_object* v___x_346_; lean_object* v___x_347_; lean_object* v___x_348_; 
v___x_346_ = lean_obj_once(&lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__145, &lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__145_once, _init_lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__145);
v___x_347_ = lean_obj_once(&lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__7, &lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__7_once, _init_lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__7);
v___x_348_ = lean_string_append(v___x_347_, v___x_346_);
return v___x_348_;
}
}
static lean_object* _init_lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__147(void){
_start:
{
lean_object* v___x_349_; lean_object* v___x_350_; lean_object* v___x_351_; 
v___x_349_ = ((lean_object*)(lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__11));
v___x_350_ = lean_obj_once(&lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__146, &lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__146_once, _init_lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__146);
v___x_351_ = lean_string_append(v___x_350_, v___x_349_);
return v___x_351_;
}
}
static lean_object* _init_lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__150(void){
_start:
{
uint8_t v___x_355_; lean_object* v___x_356_; lean_object* v___x_357_; 
v___x_355_ = 1;
v___x_356_ = ((lean_object*)(lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__149));
v___x_357_ = l_Lean_Name_toStringWithToken___at___00Lean_Name_toString_spec__0(v___x_356_, v___x_355_);
return v___x_357_;
}
}
static lean_object* _init_lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__151(void){
_start:
{
lean_object* v___x_358_; lean_object* v___x_359_; lean_object* v___x_360_; 
v___x_358_ = lean_obj_once(&lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__150, &lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__150_once, _init_lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__150);
v___x_359_ = lean_obj_once(&lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__7, &lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__7_once, _init_lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__7);
v___x_360_ = lean_string_append(v___x_359_, v___x_358_);
return v___x_360_;
}
}
static lean_object* _init_lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__152(void){
_start:
{
lean_object* v___x_361_; lean_object* v___x_362_; lean_object* v___x_363_; 
v___x_361_ = ((lean_object*)(lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__11));
v___x_362_ = lean_obj_once(&lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__151, &lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__151_once, _init_lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__151);
v___x_363_ = lean_string_append(v___x_362_, v___x_361_);
return v___x_363_;
}
}
static lean_object* _init_lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__155(void){
_start:
{
uint8_t v___x_367_; lean_object* v___x_368_; lean_object* v___x_369_; 
v___x_367_ = 1;
v___x_368_ = ((lean_object*)(lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__154));
v___x_369_ = l_Lean_Name_toStringWithToken___at___00Lean_Name_toString_spec__0(v___x_368_, v___x_367_);
return v___x_369_;
}
}
static lean_object* _init_lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__156(void){
_start:
{
lean_object* v___x_370_; lean_object* v___x_371_; lean_object* v___x_372_; 
v___x_370_ = lean_obj_once(&lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__155, &lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__155_once, _init_lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__155);
v___x_371_ = lean_obj_once(&lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__7, &lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__7_once, _init_lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__7);
v___x_372_ = lean_string_append(v___x_371_, v___x_370_);
return v___x_372_;
}
}
static lean_object* _init_lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__157(void){
_start:
{
lean_object* v___x_373_; lean_object* v___x_374_; lean_object* v___x_375_; 
v___x_373_ = ((lean_object*)(lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__11));
v___x_374_ = lean_obj_once(&lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__156, &lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__156_once, _init_lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__156);
v___x_375_ = lean_string_append(v___x_374_, v___x_373_);
return v___x_375_;
}
}
LEAN_EXPORT lean_object* lp_competition_Bench_Suite_instFromJsonCase_fromJson(lean_object* v_json_376_){
_start:
{
lean_object* v___x_377_; lean_object* v___x_378_; 
v___x_377_ = ((lean_object*)(lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__0));
lean_inc(v_json_376_);
v___x_378_ = lp_proofwidgets_Lean_Json_getObjValAs_x3f___at___00ProofWidgets_MarkdownDisplay_instFromJsonProps_fromJson_spec__0(v_json_376_, v___x_377_);
if (lean_obj_tag(v___x_378_) == 0)
{
lean_object* v_a_379_; lean_object* v___x_381_; uint8_t v_isShared_382_; uint8_t v_isSharedCheck_388_; 
lean_dec(v_json_376_);
v_a_379_ = lean_ctor_get(v___x_378_, 0);
v_isSharedCheck_388_ = !lean_is_exclusive(v___x_378_);
if (v_isSharedCheck_388_ == 0)
{
v___x_381_ = v___x_378_;
v_isShared_382_ = v_isSharedCheck_388_;
goto v_resetjp_380_;
}
else
{
lean_inc(v_a_379_);
lean_dec(v___x_378_);
v___x_381_ = lean_box(0);
v_isShared_382_ = v_isSharedCheck_388_;
goto v_resetjp_380_;
}
v_resetjp_380_:
{
lean_object* v___x_383_; lean_object* v___x_384_; lean_object* v___x_386_; 
v___x_383_ = lean_obj_once(&lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__12, &lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__12_once, _init_lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__12);
v___x_384_ = lean_string_append(v___x_383_, v_a_379_);
lean_dec(v_a_379_);
if (v_isShared_382_ == 0)
{
lean_ctor_set(v___x_381_, 0, v___x_384_);
v___x_386_ = v___x_381_;
goto v_reusejp_385_;
}
else
{
lean_object* v_reuseFailAlloc_387_; 
v_reuseFailAlloc_387_ = lean_alloc_ctor(0, 1, 0);
lean_ctor_set(v_reuseFailAlloc_387_, 0, v___x_384_);
v___x_386_ = v_reuseFailAlloc_387_;
goto v_reusejp_385_;
}
v_reusejp_385_:
{
return v___x_386_;
}
}
}
else
{
if (lean_obj_tag(v___x_378_) == 0)
{
lean_object* v_a_389_; lean_object* v___x_391_; uint8_t v_isShared_392_; uint8_t v_isSharedCheck_396_; 
lean_dec(v_json_376_);
v_a_389_ = lean_ctor_get(v___x_378_, 0);
v_isSharedCheck_396_ = !lean_is_exclusive(v___x_378_);
if (v_isSharedCheck_396_ == 0)
{
v___x_391_ = v___x_378_;
v_isShared_392_ = v_isSharedCheck_396_;
goto v_resetjp_390_;
}
else
{
lean_inc(v_a_389_);
lean_dec(v___x_378_);
v___x_391_ = lean_box(0);
v_isShared_392_ = v_isSharedCheck_396_;
goto v_resetjp_390_;
}
v_resetjp_390_:
{
lean_object* v___x_394_; 
if (v_isShared_392_ == 0)
{
lean_ctor_set_tag(v___x_391_, 0);
v___x_394_ = v___x_391_;
goto v_reusejp_393_;
}
else
{
lean_object* v_reuseFailAlloc_395_; 
v_reuseFailAlloc_395_ = lean_alloc_ctor(0, 1, 0);
lean_ctor_set(v_reuseFailAlloc_395_, 0, v_a_389_);
v___x_394_ = v_reuseFailAlloc_395_;
goto v_reusejp_393_;
}
v_reusejp_393_:
{
return v___x_394_;
}
}
}
else
{
lean_object* v_a_397_; lean_object* v___x_398_; lean_object* v___x_399_; 
v_a_397_ = lean_ctor_get(v___x_378_, 0);
lean_inc(v_a_397_);
lean_dec_ref_known(v___x_378_, 1);
v___x_398_ = ((lean_object*)(lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__13));
lean_inc(v_json_376_);
v___x_399_ = lp_proofwidgets_Lean_Json_getObjValAs_x3f___at___00ProofWidgets_MarkdownDisplay_instFromJsonProps_fromJson_spec__0(v_json_376_, v___x_398_);
if (lean_obj_tag(v___x_399_) == 0)
{
lean_object* v_a_400_; lean_object* v___x_402_; uint8_t v_isShared_403_; uint8_t v_isSharedCheck_409_; 
lean_dec(v_a_397_);
lean_dec(v_json_376_);
v_a_400_ = lean_ctor_get(v___x_399_, 0);
v_isSharedCheck_409_ = !lean_is_exclusive(v___x_399_);
if (v_isSharedCheck_409_ == 0)
{
v___x_402_ = v___x_399_;
v_isShared_403_ = v_isSharedCheck_409_;
goto v_resetjp_401_;
}
else
{
lean_inc(v_a_400_);
lean_dec(v___x_399_);
v___x_402_ = lean_box(0);
v_isShared_403_ = v_isSharedCheck_409_;
goto v_resetjp_401_;
}
v_resetjp_401_:
{
lean_object* v___x_404_; lean_object* v___x_405_; lean_object* v___x_407_; 
v___x_404_ = lean_obj_once(&lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__17, &lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__17_once, _init_lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__17);
v___x_405_ = lean_string_append(v___x_404_, v_a_400_);
lean_dec(v_a_400_);
if (v_isShared_403_ == 0)
{
lean_ctor_set(v___x_402_, 0, v___x_405_);
v___x_407_ = v___x_402_;
goto v_reusejp_406_;
}
else
{
lean_object* v_reuseFailAlloc_408_; 
v_reuseFailAlloc_408_ = lean_alloc_ctor(0, 1, 0);
lean_ctor_set(v_reuseFailAlloc_408_, 0, v___x_405_);
v___x_407_ = v_reuseFailAlloc_408_;
goto v_reusejp_406_;
}
v_reusejp_406_:
{
return v___x_407_;
}
}
}
else
{
if (lean_obj_tag(v___x_399_) == 0)
{
lean_object* v_a_410_; lean_object* v___x_412_; uint8_t v_isShared_413_; uint8_t v_isSharedCheck_417_; 
lean_dec(v_a_397_);
lean_dec(v_json_376_);
v_a_410_ = lean_ctor_get(v___x_399_, 0);
v_isSharedCheck_417_ = !lean_is_exclusive(v___x_399_);
if (v_isSharedCheck_417_ == 0)
{
v___x_412_ = v___x_399_;
v_isShared_413_ = v_isSharedCheck_417_;
goto v_resetjp_411_;
}
else
{
lean_inc(v_a_410_);
lean_dec(v___x_399_);
v___x_412_ = lean_box(0);
v_isShared_413_ = v_isSharedCheck_417_;
goto v_resetjp_411_;
}
v_resetjp_411_:
{
lean_object* v___x_415_; 
if (v_isShared_413_ == 0)
{
lean_ctor_set_tag(v___x_412_, 0);
v___x_415_ = v___x_412_;
goto v_reusejp_414_;
}
else
{
lean_object* v_reuseFailAlloc_416_; 
v_reuseFailAlloc_416_ = lean_alloc_ctor(0, 1, 0);
lean_ctor_set(v_reuseFailAlloc_416_, 0, v_a_410_);
v___x_415_ = v_reuseFailAlloc_416_;
goto v_reusejp_414_;
}
v_reusejp_414_:
{
return v___x_415_;
}
}
}
else
{
lean_object* v_a_418_; lean_object* v___x_419_; lean_object* v___x_420_; 
v_a_418_ = lean_ctor_get(v___x_399_, 0);
lean_inc(v_a_418_);
lean_dec_ref_known(v___x_399_, 1);
v___x_419_ = ((lean_object*)(lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__18));
lean_inc(v_json_376_);
v___x_420_ = l_Lean_Json_getObjValAs_x3f___at___00Lean_Lsp_instFromJsonLeanILeanHeaderSetupInfoParams_fromJson_spec__1(v_json_376_, v___x_419_);
if (lean_obj_tag(v___x_420_) == 0)
{
lean_object* v_a_421_; lean_object* v___x_423_; uint8_t v_isShared_424_; uint8_t v_isSharedCheck_430_; 
lean_dec(v_a_418_);
lean_dec(v_a_397_);
lean_dec(v_json_376_);
v_a_421_ = lean_ctor_get(v___x_420_, 0);
v_isSharedCheck_430_ = !lean_is_exclusive(v___x_420_);
if (v_isSharedCheck_430_ == 0)
{
v___x_423_ = v___x_420_;
v_isShared_424_ = v_isSharedCheck_430_;
goto v_resetjp_422_;
}
else
{
lean_inc(v_a_421_);
lean_dec(v___x_420_);
v___x_423_ = lean_box(0);
v_isShared_424_ = v_isSharedCheck_430_;
goto v_resetjp_422_;
}
v_resetjp_422_:
{
lean_object* v___x_425_; lean_object* v___x_426_; lean_object* v___x_428_; 
v___x_425_ = lean_obj_once(&lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__22, &lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__22_once, _init_lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__22);
v___x_426_ = lean_string_append(v___x_425_, v_a_421_);
lean_dec(v_a_421_);
if (v_isShared_424_ == 0)
{
lean_ctor_set(v___x_423_, 0, v___x_426_);
v___x_428_ = v___x_423_;
goto v_reusejp_427_;
}
else
{
lean_object* v_reuseFailAlloc_429_; 
v_reuseFailAlloc_429_ = lean_alloc_ctor(0, 1, 0);
lean_ctor_set(v_reuseFailAlloc_429_, 0, v___x_426_);
v___x_428_ = v_reuseFailAlloc_429_;
goto v_reusejp_427_;
}
v_reusejp_427_:
{
return v___x_428_;
}
}
}
else
{
if (lean_obj_tag(v___x_420_) == 0)
{
lean_object* v_a_431_; lean_object* v___x_433_; uint8_t v_isShared_434_; uint8_t v_isSharedCheck_438_; 
lean_dec(v_a_418_);
lean_dec(v_a_397_);
lean_dec(v_json_376_);
v_a_431_ = lean_ctor_get(v___x_420_, 0);
v_isSharedCheck_438_ = !lean_is_exclusive(v___x_420_);
if (v_isSharedCheck_438_ == 0)
{
v___x_433_ = v___x_420_;
v_isShared_434_ = v_isSharedCheck_438_;
goto v_resetjp_432_;
}
else
{
lean_inc(v_a_431_);
lean_dec(v___x_420_);
v___x_433_ = lean_box(0);
v_isShared_434_ = v_isSharedCheck_438_;
goto v_resetjp_432_;
}
v_resetjp_432_:
{
lean_object* v___x_436_; 
if (v_isShared_434_ == 0)
{
lean_ctor_set_tag(v___x_433_, 0);
v___x_436_ = v___x_433_;
goto v_reusejp_435_;
}
else
{
lean_object* v_reuseFailAlloc_437_; 
v_reuseFailAlloc_437_ = lean_alloc_ctor(0, 1, 0);
lean_ctor_set(v_reuseFailAlloc_437_, 0, v_a_431_);
v___x_436_ = v_reuseFailAlloc_437_;
goto v_reusejp_435_;
}
v_reusejp_435_:
{
return v___x_436_;
}
}
}
else
{
lean_object* v_a_439_; lean_object* v___x_440_; lean_object* v___x_441_; 
v_a_439_ = lean_ctor_get(v___x_420_, 0);
lean_inc(v_a_439_);
lean_dec_ref_known(v___x_420_, 1);
v___x_440_ = ((lean_object*)(lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__23));
lean_inc(v_json_376_);
v___x_441_ = l_Lean_Json_getObjValAs_x3f___at___00Lean_Server_instFromJsonIlean_fromJson_spec__0(v_json_376_, v___x_440_);
if (lean_obj_tag(v___x_441_) == 0)
{
lean_object* v_a_442_; lean_object* v___x_444_; uint8_t v_isShared_445_; uint8_t v_isSharedCheck_451_; 
lean_dec(v_a_439_);
lean_dec(v_a_418_);
lean_dec(v_a_397_);
lean_dec(v_json_376_);
v_a_442_ = lean_ctor_get(v___x_441_, 0);
v_isSharedCheck_451_ = !lean_is_exclusive(v___x_441_);
if (v_isSharedCheck_451_ == 0)
{
v___x_444_ = v___x_441_;
v_isShared_445_ = v_isSharedCheck_451_;
goto v_resetjp_443_;
}
else
{
lean_inc(v_a_442_);
lean_dec(v___x_441_);
v___x_444_ = lean_box(0);
v_isShared_445_ = v_isSharedCheck_451_;
goto v_resetjp_443_;
}
v_resetjp_443_:
{
lean_object* v___x_446_; lean_object* v___x_447_; lean_object* v___x_449_; 
v___x_446_ = lean_obj_once(&lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__27, &lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__27_once, _init_lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__27);
v___x_447_ = lean_string_append(v___x_446_, v_a_442_);
lean_dec(v_a_442_);
if (v_isShared_445_ == 0)
{
lean_ctor_set(v___x_444_, 0, v___x_447_);
v___x_449_ = v___x_444_;
goto v_reusejp_448_;
}
else
{
lean_object* v_reuseFailAlloc_450_; 
v_reuseFailAlloc_450_ = lean_alloc_ctor(0, 1, 0);
lean_ctor_set(v_reuseFailAlloc_450_, 0, v___x_447_);
v___x_449_ = v_reuseFailAlloc_450_;
goto v_reusejp_448_;
}
v_reusejp_448_:
{
return v___x_449_;
}
}
}
else
{
if (lean_obj_tag(v___x_441_) == 0)
{
lean_object* v_a_452_; lean_object* v___x_454_; uint8_t v_isShared_455_; uint8_t v_isSharedCheck_459_; 
lean_dec(v_a_439_);
lean_dec(v_a_418_);
lean_dec(v_a_397_);
lean_dec(v_json_376_);
v_a_452_ = lean_ctor_get(v___x_441_, 0);
v_isSharedCheck_459_ = !lean_is_exclusive(v___x_441_);
if (v_isSharedCheck_459_ == 0)
{
v___x_454_ = v___x_441_;
v_isShared_455_ = v_isSharedCheck_459_;
goto v_resetjp_453_;
}
else
{
lean_inc(v_a_452_);
lean_dec(v___x_441_);
v___x_454_ = lean_box(0);
v_isShared_455_ = v_isSharedCheck_459_;
goto v_resetjp_453_;
}
v_resetjp_453_:
{
lean_object* v___x_457_; 
if (v_isShared_455_ == 0)
{
lean_ctor_set_tag(v___x_454_, 0);
v___x_457_ = v___x_454_;
goto v_reusejp_456_;
}
else
{
lean_object* v_reuseFailAlloc_458_; 
v_reuseFailAlloc_458_ = lean_alloc_ctor(0, 1, 0);
lean_ctor_set(v_reuseFailAlloc_458_, 0, v_a_452_);
v___x_457_ = v_reuseFailAlloc_458_;
goto v_reusejp_456_;
}
v_reusejp_456_:
{
return v___x_457_;
}
}
}
else
{
lean_object* v_a_460_; lean_object* v___x_461_; lean_object* v___x_462_; 
v_a_460_ = lean_ctor_get(v___x_441_, 0);
lean_inc(v_a_460_);
lean_dec_ref_known(v___x_441_, 1);
v___x_461_ = ((lean_object*)(lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__28));
lean_inc(v_json_376_);
v___x_462_ = l_Lean_Json_getObjValAs_x3f___at___00Lean_Server_instFromJsonIlean_fromJson_spec__0(v_json_376_, v___x_461_);
if (lean_obj_tag(v___x_462_) == 0)
{
lean_object* v_a_463_; lean_object* v___x_465_; uint8_t v_isShared_466_; uint8_t v_isSharedCheck_472_; 
lean_dec(v_a_460_);
lean_dec(v_a_439_);
lean_dec(v_a_418_);
lean_dec(v_a_397_);
lean_dec(v_json_376_);
v_a_463_ = lean_ctor_get(v___x_462_, 0);
v_isSharedCheck_472_ = !lean_is_exclusive(v___x_462_);
if (v_isSharedCheck_472_ == 0)
{
v___x_465_ = v___x_462_;
v_isShared_466_ = v_isSharedCheck_472_;
goto v_resetjp_464_;
}
else
{
lean_inc(v_a_463_);
lean_dec(v___x_462_);
v___x_465_ = lean_box(0);
v_isShared_466_ = v_isSharedCheck_472_;
goto v_resetjp_464_;
}
v_resetjp_464_:
{
lean_object* v___x_467_; lean_object* v___x_468_; lean_object* v___x_470_; 
v___x_467_ = lean_obj_once(&lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__32, &lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__32_once, _init_lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__32);
v___x_468_ = lean_string_append(v___x_467_, v_a_463_);
lean_dec(v_a_463_);
if (v_isShared_466_ == 0)
{
lean_ctor_set(v___x_465_, 0, v___x_468_);
v___x_470_ = v___x_465_;
goto v_reusejp_469_;
}
else
{
lean_object* v_reuseFailAlloc_471_; 
v_reuseFailAlloc_471_ = lean_alloc_ctor(0, 1, 0);
lean_ctor_set(v_reuseFailAlloc_471_, 0, v___x_468_);
v___x_470_ = v_reuseFailAlloc_471_;
goto v_reusejp_469_;
}
v_reusejp_469_:
{
return v___x_470_;
}
}
}
else
{
if (lean_obj_tag(v___x_462_) == 0)
{
lean_object* v_a_473_; lean_object* v___x_475_; uint8_t v_isShared_476_; uint8_t v_isSharedCheck_480_; 
lean_dec(v_a_460_);
lean_dec(v_a_439_);
lean_dec(v_a_418_);
lean_dec(v_a_397_);
lean_dec(v_json_376_);
v_a_473_ = lean_ctor_get(v___x_462_, 0);
v_isSharedCheck_480_ = !lean_is_exclusive(v___x_462_);
if (v_isSharedCheck_480_ == 0)
{
v___x_475_ = v___x_462_;
v_isShared_476_ = v_isSharedCheck_480_;
goto v_resetjp_474_;
}
else
{
lean_inc(v_a_473_);
lean_dec(v___x_462_);
v___x_475_ = lean_box(0);
v_isShared_476_ = v_isSharedCheck_480_;
goto v_resetjp_474_;
}
v_resetjp_474_:
{
lean_object* v___x_478_; 
if (v_isShared_476_ == 0)
{
lean_ctor_set_tag(v___x_475_, 0);
v___x_478_ = v___x_475_;
goto v_reusejp_477_;
}
else
{
lean_object* v_reuseFailAlloc_479_; 
v_reuseFailAlloc_479_ = lean_alloc_ctor(0, 1, 0);
lean_ctor_set(v_reuseFailAlloc_479_, 0, v_a_473_);
v___x_478_ = v_reuseFailAlloc_479_;
goto v_reusejp_477_;
}
v_reusejp_477_:
{
return v___x_478_;
}
}
}
else
{
lean_object* v_a_481_; lean_object* v___x_482_; lean_object* v___x_483_; 
v_a_481_ = lean_ctor_get(v___x_462_, 0);
lean_inc(v_a_481_);
lean_dec_ref_known(v___x_462_, 1);
v___x_482_ = ((lean_object*)(lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__33));
lean_inc(v_json_376_);
v___x_483_ = l_Lean_Json_getObjValAs_x3f___at___00Lean_Server_instFromJsonIlean_fromJson_spec__0(v_json_376_, v___x_482_);
if (lean_obj_tag(v___x_483_) == 0)
{
lean_object* v_a_484_; lean_object* v___x_486_; uint8_t v_isShared_487_; uint8_t v_isSharedCheck_493_; 
lean_dec(v_a_481_);
lean_dec(v_a_460_);
lean_dec(v_a_439_);
lean_dec(v_a_418_);
lean_dec(v_a_397_);
lean_dec(v_json_376_);
v_a_484_ = lean_ctor_get(v___x_483_, 0);
v_isSharedCheck_493_ = !lean_is_exclusive(v___x_483_);
if (v_isSharedCheck_493_ == 0)
{
v___x_486_ = v___x_483_;
v_isShared_487_ = v_isSharedCheck_493_;
goto v_resetjp_485_;
}
else
{
lean_inc(v_a_484_);
lean_dec(v___x_483_);
v___x_486_ = lean_box(0);
v_isShared_487_ = v_isSharedCheck_493_;
goto v_resetjp_485_;
}
v_resetjp_485_:
{
lean_object* v___x_488_; lean_object* v___x_489_; lean_object* v___x_491_; 
v___x_488_ = lean_obj_once(&lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__37, &lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__37_once, _init_lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__37);
v___x_489_ = lean_string_append(v___x_488_, v_a_484_);
lean_dec(v_a_484_);
if (v_isShared_487_ == 0)
{
lean_ctor_set(v___x_486_, 0, v___x_489_);
v___x_491_ = v___x_486_;
goto v_reusejp_490_;
}
else
{
lean_object* v_reuseFailAlloc_492_; 
v_reuseFailAlloc_492_ = lean_alloc_ctor(0, 1, 0);
lean_ctor_set(v_reuseFailAlloc_492_, 0, v___x_489_);
v___x_491_ = v_reuseFailAlloc_492_;
goto v_reusejp_490_;
}
v_reusejp_490_:
{
return v___x_491_;
}
}
}
else
{
if (lean_obj_tag(v___x_483_) == 0)
{
lean_object* v_a_494_; lean_object* v___x_496_; uint8_t v_isShared_497_; uint8_t v_isSharedCheck_501_; 
lean_dec(v_a_481_);
lean_dec(v_a_460_);
lean_dec(v_a_439_);
lean_dec(v_a_418_);
lean_dec(v_a_397_);
lean_dec(v_json_376_);
v_a_494_ = lean_ctor_get(v___x_483_, 0);
v_isSharedCheck_501_ = !lean_is_exclusive(v___x_483_);
if (v_isSharedCheck_501_ == 0)
{
v___x_496_ = v___x_483_;
v_isShared_497_ = v_isSharedCheck_501_;
goto v_resetjp_495_;
}
else
{
lean_inc(v_a_494_);
lean_dec(v___x_483_);
v___x_496_ = lean_box(0);
v_isShared_497_ = v_isSharedCheck_501_;
goto v_resetjp_495_;
}
v_resetjp_495_:
{
lean_object* v___x_499_; 
if (v_isShared_497_ == 0)
{
lean_ctor_set_tag(v___x_496_, 0);
v___x_499_ = v___x_496_;
goto v_reusejp_498_;
}
else
{
lean_object* v_reuseFailAlloc_500_; 
v_reuseFailAlloc_500_ = lean_alloc_ctor(0, 1, 0);
lean_ctor_set(v_reuseFailAlloc_500_, 0, v_a_494_);
v___x_499_ = v_reuseFailAlloc_500_;
goto v_reusejp_498_;
}
v_reusejp_498_:
{
return v___x_499_;
}
}
}
else
{
lean_object* v_a_502_; lean_object* v___x_503_; lean_object* v___x_504_; 
v_a_502_ = lean_ctor_get(v___x_483_, 0);
lean_inc(v_a_502_);
lean_dec_ref_known(v___x_483_, 1);
v___x_503_ = ((lean_object*)(lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__38));
lean_inc(v_json_376_);
v___x_504_ = l_Lean_Json_getObjValAs_x3f___at___00Lean_Server_instFromJsonIlean_fromJson_spec__0(v_json_376_, v___x_503_);
if (lean_obj_tag(v___x_504_) == 0)
{
lean_object* v_a_505_; lean_object* v___x_507_; uint8_t v_isShared_508_; uint8_t v_isSharedCheck_514_; 
lean_dec(v_a_502_);
lean_dec(v_a_481_);
lean_dec(v_a_460_);
lean_dec(v_a_439_);
lean_dec(v_a_418_);
lean_dec(v_a_397_);
lean_dec(v_json_376_);
v_a_505_ = lean_ctor_get(v___x_504_, 0);
v_isSharedCheck_514_ = !lean_is_exclusive(v___x_504_);
if (v_isSharedCheck_514_ == 0)
{
v___x_507_ = v___x_504_;
v_isShared_508_ = v_isSharedCheck_514_;
goto v_resetjp_506_;
}
else
{
lean_inc(v_a_505_);
lean_dec(v___x_504_);
v___x_507_ = lean_box(0);
v_isShared_508_ = v_isSharedCheck_514_;
goto v_resetjp_506_;
}
v_resetjp_506_:
{
lean_object* v___x_509_; lean_object* v___x_510_; lean_object* v___x_512_; 
v___x_509_ = lean_obj_once(&lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__42, &lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__42_once, _init_lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__42);
v___x_510_ = lean_string_append(v___x_509_, v_a_505_);
lean_dec(v_a_505_);
if (v_isShared_508_ == 0)
{
lean_ctor_set(v___x_507_, 0, v___x_510_);
v___x_512_ = v___x_507_;
goto v_reusejp_511_;
}
else
{
lean_object* v_reuseFailAlloc_513_; 
v_reuseFailAlloc_513_ = lean_alloc_ctor(0, 1, 0);
lean_ctor_set(v_reuseFailAlloc_513_, 0, v___x_510_);
v___x_512_ = v_reuseFailAlloc_513_;
goto v_reusejp_511_;
}
v_reusejp_511_:
{
return v___x_512_;
}
}
}
else
{
if (lean_obj_tag(v___x_504_) == 0)
{
lean_object* v_a_515_; lean_object* v___x_517_; uint8_t v_isShared_518_; uint8_t v_isSharedCheck_522_; 
lean_dec(v_a_502_);
lean_dec(v_a_481_);
lean_dec(v_a_460_);
lean_dec(v_a_439_);
lean_dec(v_a_418_);
lean_dec(v_a_397_);
lean_dec(v_json_376_);
v_a_515_ = lean_ctor_get(v___x_504_, 0);
v_isSharedCheck_522_ = !lean_is_exclusive(v___x_504_);
if (v_isSharedCheck_522_ == 0)
{
v___x_517_ = v___x_504_;
v_isShared_518_ = v_isSharedCheck_522_;
goto v_resetjp_516_;
}
else
{
lean_inc(v_a_515_);
lean_dec(v___x_504_);
v___x_517_ = lean_box(0);
v_isShared_518_ = v_isSharedCheck_522_;
goto v_resetjp_516_;
}
v_resetjp_516_:
{
lean_object* v___x_520_; 
if (v_isShared_518_ == 0)
{
lean_ctor_set_tag(v___x_517_, 0);
v___x_520_ = v___x_517_;
goto v_reusejp_519_;
}
else
{
lean_object* v_reuseFailAlloc_521_; 
v_reuseFailAlloc_521_ = lean_alloc_ctor(0, 1, 0);
lean_ctor_set(v_reuseFailAlloc_521_, 0, v_a_515_);
v___x_520_ = v_reuseFailAlloc_521_;
goto v_reusejp_519_;
}
v_reusejp_519_:
{
return v___x_520_;
}
}
}
else
{
lean_object* v_a_523_; lean_object* v___x_524_; lean_object* v___x_525_; 
v_a_523_ = lean_ctor_get(v___x_504_, 0);
lean_inc(v_a_523_);
lean_dec_ref_known(v___x_504_, 1);
v___x_524_ = ((lean_object*)(lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__43));
lean_inc(v_json_376_);
v___x_525_ = l_Lean_Json_getObjValAs_x3f___at___00Lean_Server_instFromJsonIlean_fromJson_spec__0(v_json_376_, v___x_524_);
if (lean_obj_tag(v___x_525_) == 0)
{
lean_object* v_a_526_; lean_object* v___x_528_; uint8_t v_isShared_529_; uint8_t v_isSharedCheck_535_; 
lean_dec(v_a_523_);
lean_dec(v_a_502_);
lean_dec(v_a_481_);
lean_dec(v_a_460_);
lean_dec(v_a_439_);
lean_dec(v_a_418_);
lean_dec(v_a_397_);
lean_dec(v_json_376_);
v_a_526_ = lean_ctor_get(v___x_525_, 0);
v_isSharedCheck_535_ = !lean_is_exclusive(v___x_525_);
if (v_isSharedCheck_535_ == 0)
{
v___x_528_ = v___x_525_;
v_isShared_529_ = v_isSharedCheck_535_;
goto v_resetjp_527_;
}
else
{
lean_inc(v_a_526_);
lean_dec(v___x_525_);
v___x_528_ = lean_box(0);
v_isShared_529_ = v_isSharedCheck_535_;
goto v_resetjp_527_;
}
v_resetjp_527_:
{
lean_object* v___x_530_; lean_object* v___x_531_; lean_object* v___x_533_; 
v___x_530_ = lean_obj_once(&lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__47, &lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__47_once, _init_lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__47);
v___x_531_ = lean_string_append(v___x_530_, v_a_526_);
lean_dec(v_a_526_);
if (v_isShared_529_ == 0)
{
lean_ctor_set(v___x_528_, 0, v___x_531_);
v___x_533_ = v___x_528_;
goto v_reusejp_532_;
}
else
{
lean_object* v_reuseFailAlloc_534_; 
v_reuseFailAlloc_534_ = lean_alloc_ctor(0, 1, 0);
lean_ctor_set(v_reuseFailAlloc_534_, 0, v___x_531_);
v___x_533_ = v_reuseFailAlloc_534_;
goto v_reusejp_532_;
}
v_reusejp_532_:
{
return v___x_533_;
}
}
}
else
{
if (lean_obj_tag(v___x_525_) == 0)
{
lean_object* v_a_536_; lean_object* v___x_538_; uint8_t v_isShared_539_; uint8_t v_isSharedCheck_543_; 
lean_dec(v_a_523_);
lean_dec(v_a_502_);
lean_dec(v_a_481_);
lean_dec(v_a_460_);
lean_dec(v_a_439_);
lean_dec(v_a_418_);
lean_dec(v_a_397_);
lean_dec(v_json_376_);
v_a_536_ = lean_ctor_get(v___x_525_, 0);
v_isSharedCheck_543_ = !lean_is_exclusive(v___x_525_);
if (v_isSharedCheck_543_ == 0)
{
v___x_538_ = v___x_525_;
v_isShared_539_ = v_isSharedCheck_543_;
goto v_resetjp_537_;
}
else
{
lean_inc(v_a_536_);
lean_dec(v___x_525_);
v___x_538_ = lean_box(0);
v_isShared_539_ = v_isSharedCheck_543_;
goto v_resetjp_537_;
}
v_resetjp_537_:
{
lean_object* v___x_541_; 
if (v_isShared_539_ == 0)
{
lean_ctor_set_tag(v___x_538_, 0);
v___x_541_ = v___x_538_;
goto v_reusejp_540_;
}
else
{
lean_object* v_reuseFailAlloc_542_; 
v_reuseFailAlloc_542_ = lean_alloc_ctor(0, 1, 0);
lean_ctor_set(v_reuseFailAlloc_542_, 0, v_a_536_);
v___x_541_ = v_reuseFailAlloc_542_;
goto v_reusejp_540_;
}
v_reusejp_540_:
{
return v___x_541_;
}
}
}
else
{
lean_object* v_a_544_; lean_object* v___x_545_; lean_object* v___x_546_; 
v_a_544_ = lean_ctor_get(v___x_525_, 0);
lean_inc(v_a_544_);
lean_dec_ref_known(v___x_525_, 1);
v___x_545_ = ((lean_object*)(lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__48));
lean_inc(v_json_376_);
v___x_546_ = l_Lean_Json_getObjValAs_x3f___at___00Lean_Server_instFromJsonIlean_fromJson_spec__0(v_json_376_, v___x_545_);
if (lean_obj_tag(v___x_546_) == 0)
{
lean_object* v_a_547_; lean_object* v___x_549_; uint8_t v_isShared_550_; uint8_t v_isSharedCheck_556_; 
lean_dec(v_a_544_);
lean_dec(v_a_523_);
lean_dec(v_a_502_);
lean_dec(v_a_481_);
lean_dec(v_a_460_);
lean_dec(v_a_439_);
lean_dec(v_a_418_);
lean_dec(v_a_397_);
lean_dec(v_json_376_);
v_a_547_ = lean_ctor_get(v___x_546_, 0);
v_isSharedCheck_556_ = !lean_is_exclusive(v___x_546_);
if (v_isSharedCheck_556_ == 0)
{
v___x_549_ = v___x_546_;
v_isShared_550_ = v_isSharedCheck_556_;
goto v_resetjp_548_;
}
else
{
lean_inc(v_a_547_);
lean_dec(v___x_546_);
v___x_549_ = lean_box(0);
v_isShared_550_ = v_isSharedCheck_556_;
goto v_resetjp_548_;
}
v_resetjp_548_:
{
lean_object* v___x_551_; lean_object* v___x_552_; lean_object* v___x_554_; 
v___x_551_ = lean_obj_once(&lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__52, &lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__52_once, _init_lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__52);
v___x_552_ = lean_string_append(v___x_551_, v_a_547_);
lean_dec(v_a_547_);
if (v_isShared_550_ == 0)
{
lean_ctor_set(v___x_549_, 0, v___x_552_);
v___x_554_ = v___x_549_;
goto v_reusejp_553_;
}
else
{
lean_object* v_reuseFailAlloc_555_; 
v_reuseFailAlloc_555_ = lean_alloc_ctor(0, 1, 0);
lean_ctor_set(v_reuseFailAlloc_555_, 0, v___x_552_);
v___x_554_ = v_reuseFailAlloc_555_;
goto v_reusejp_553_;
}
v_reusejp_553_:
{
return v___x_554_;
}
}
}
else
{
if (lean_obj_tag(v___x_546_) == 0)
{
lean_object* v_a_557_; lean_object* v___x_559_; uint8_t v_isShared_560_; uint8_t v_isSharedCheck_564_; 
lean_dec(v_a_544_);
lean_dec(v_a_523_);
lean_dec(v_a_502_);
lean_dec(v_a_481_);
lean_dec(v_a_460_);
lean_dec(v_a_439_);
lean_dec(v_a_418_);
lean_dec(v_a_397_);
lean_dec(v_json_376_);
v_a_557_ = lean_ctor_get(v___x_546_, 0);
v_isSharedCheck_564_ = !lean_is_exclusive(v___x_546_);
if (v_isSharedCheck_564_ == 0)
{
v___x_559_ = v___x_546_;
v_isShared_560_ = v_isSharedCheck_564_;
goto v_resetjp_558_;
}
else
{
lean_inc(v_a_557_);
lean_dec(v___x_546_);
v___x_559_ = lean_box(0);
v_isShared_560_ = v_isSharedCheck_564_;
goto v_resetjp_558_;
}
v_resetjp_558_:
{
lean_object* v___x_562_; 
if (v_isShared_560_ == 0)
{
lean_ctor_set_tag(v___x_559_, 0);
v___x_562_ = v___x_559_;
goto v_reusejp_561_;
}
else
{
lean_object* v_reuseFailAlloc_563_; 
v_reuseFailAlloc_563_ = lean_alloc_ctor(0, 1, 0);
lean_ctor_set(v_reuseFailAlloc_563_, 0, v_a_557_);
v___x_562_ = v_reuseFailAlloc_563_;
goto v_reusejp_561_;
}
v_reusejp_561_:
{
return v___x_562_;
}
}
}
else
{
lean_object* v_a_565_; lean_object* v___x_566_; lean_object* v___x_567_; 
v_a_565_ = lean_ctor_get(v___x_546_, 0);
lean_inc(v_a_565_);
lean_dec_ref_known(v___x_546_, 1);
v___x_566_ = ((lean_object*)(lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__53));
lean_inc(v_json_376_);
v___x_567_ = l_Lean_Json_getObjValAs_x3f___at___00Lean_Server_instFromJsonIlean_fromJson_spec__0(v_json_376_, v___x_566_);
if (lean_obj_tag(v___x_567_) == 0)
{
lean_object* v_a_568_; lean_object* v___x_570_; uint8_t v_isShared_571_; uint8_t v_isSharedCheck_577_; 
lean_dec(v_a_565_);
lean_dec(v_a_544_);
lean_dec(v_a_523_);
lean_dec(v_a_502_);
lean_dec(v_a_481_);
lean_dec(v_a_460_);
lean_dec(v_a_439_);
lean_dec(v_a_418_);
lean_dec(v_a_397_);
lean_dec(v_json_376_);
v_a_568_ = lean_ctor_get(v___x_567_, 0);
v_isSharedCheck_577_ = !lean_is_exclusive(v___x_567_);
if (v_isSharedCheck_577_ == 0)
{
v___x_570_ = v___x_567_;
v_isShared_571_ = v_isSharedCheck_577_;
goto v_resetjp_569_;
}
else
{
lean_inc(v_a_568_);
lean_dec(v___x_567_);
v___x_570_ = lean_box(0);
v_isShared_571_ = v_isSharedCheck_577_;
goto v_resetjp_569_;
}
v_resetjp_569_:
{
lean_object* v___x_572_; lean_object* v___x_573_; lean_object* v___x_575_; 
v___x_572_ = lean_obj_once(&lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__57, &lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__57_once, _init_lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__57);
v___x_573_ = lean_string_append(v___x_572_, v_a_568_);
lean_dec(v_a_568_);
if (v_isShared_571_ == 0)
{
lean_ctor_set(v___x_570_, 0, v___x_573_);
v___x_575_ = v___x_570_;
goto v_reusejp_574_;
}
else
{
lean_object* v_reuseFailAlloc_576_; 
v_reuseFailAlloc_576_ = lean_alloc_ctor(0, 1, 0);
lean_ctor_set(v_reuseFailAlloc_576_, 0, v___x_573_);
v___x_575_ = v_reuseFailAlloc_576_;
goto v_reusejp_574_;
}
v_reusejp_574_:
{
return v___x_575_;
}
}
}
else
{
if (lean_obj_tag(v___x_567_) == 0)
{
lean_object* v_a_578_; lean_object* v___x_580_; uint8_t v_isShared_581_; uint8_t v_isSharedCheck_585_; 
lean_dec(v_a_565_);
lean_dec(v_a_544_);
lean_dec(v_a_523_);
lean_dec(v_a_502_);
lean_dec(v_a_481_);
lean_dec(v_a_460_);
lean_dec(v_a_439_);
lean_dec(v_a_418_);
lean_dec(v_a_397_);
lean_dec(v_json_376_);
v_a_578_ = lean_ctor_get(v___x_567_, 0);
v_isSharedCheck_585_ = !lean_is_exclusive(v___x_567_);
if (v_isSharedCheck_585_ == 0)
{
v___x_580_ = v___x_567_;
v_isShared_581_ = v_isSharedCheck_585_;
goto v_resetjp_579_;
}
else
{
lean_inc(v_a_578_);
lean_dec(v___x_567_);
v___x_580_ = lean_box(0);
v_isShared_581_ = v_isSharedCheck_585_;
goto v_resetjp_579_;
}
v_resetjp_579_:
{
lean_object* v___x_583_; 
if (v_isShared_581_ == 0)
{
lean_ctor_set_tag(v___x_580_, 0);
v___x_583_ = v___x_580_;
goto v_reusejp_582_;
}
else
{
lean_object* v_reuseFailAlloc_584_; 
v_reuseFailAlloc_584_ = lean_alloc_ctor(0, 1, 0);
lean_ctor_set(v_reuseFailAlloc_584_, 0, v_a_578_);
v___x_583_ = v_reuseFailAlloc_584_;
goto v_reusejp_582_;
}
v_reusejp_582_:
{
return v___x_583_;
}
}
}
else
{
lean_object* v_a_586_; lean_object* v___x_587_; lean_object* v___x_588_; 
v_a_586_ = lean_ctor_get(v___x_567_, 0);
lean_inc(v_a_586_);
lean_dec_ref_known(v___x_567_, 1);
v___x_587_ = ((lean_object*)(lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__58));
lean_inc(v_json_376_);
v___x_588_ = l_Lean_Json_getObjValAs_x3f___at___00Lean_Server_instFromJsonIlean_fromJson_spec__0(v_json_376_, v___x_587_);
if (lean_obj_tag(v___x_588_) == 0)
{
lean_object* v_a_589_; lean_object* v___x_591_; uint8_t v_isShared_592_; uint8_t v_isSharedCheck_598_; 
lean_dec(v_a_586_);
lean_dec(v_a_565_);
lean_dec(v_a_544_);
lean_dec(v_a_523_);
lean_dec(v_a_502_);
lean_dec(v_a_481_);
lean_dec(v_a_460_);
lean_dec(v_a_439_);
lean_dec(v_a_418_);
lean_dec(v_a_397_);
lean_dec(v_json_376_);
v_a_589_ = lean_ctor_get(v___x_588_, 0);
v_isSharedCheck_598_ = !lean_is_exclusive(v___x_588_);
if (v_isSharedCheck_598_ == 0)
{
v___x_591_ = v___x_588_;
v_isShared_592_ = v_isSharedCheck_598_;
goto v_resetjp_590_;
}
else
{
lean_inc(v_a_589_);
lean_dec(v___x_588_);
v___x_591_ = lean_box(0);
v_isShared_592_ = v_isSharedCheck_598_;
goto v_resetjp_590_;
}
v_resetjp_590_:
{
lean_object* v___x_593_; lean_object* v___x_594_; lean_object* v___x_596_; 
v___x_593_ = lean_obj_once(&lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__62, &lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__62_once, _init_lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__62);
v___x_594_ = lean_string_append(v___x_593_, v_a_589_);
lean_dec(v_a_589_);
if (v_isShared_592_ == 0)
{
lean_ctor_set(v___x_591_, 0, v___x_594_);
v___x_596_ = v___x_591_;
goto v_reusejp_595_;
}
else
{
lean_object* v_reuseFailAlloc_597_; 
v_reuseFailAlloc_597_ = lean_alloc_ctor(0, 1, 0);
lean_ctor_set(v_reuseFailAlloc_597_, 0, v___x_594_);
v___x_596_ = v_reuseFailAlloc_597_;
goto v_reusejp_595_;
}
v_reusejp_595_:
{
return v___x_596_;
}
}
}
else
{
if (lean_obj_tag(v___x_588_) == 0)
{
lean_object* v_a_599_; lean_object* v___x_601_; uint8_t v_isShared_602_; uint8_t v_isSharedCheck_606_; 
lean_dec(v_a_586_);
lean_dec(v_a_565_);
lean_dec(v_a_544_);
lean_dec(v_a_523_);
lean_dec(v_a_502_);
lean_dec(v_a_481_);
lean_dec(v_a_460_);
lean_dec(v_a_439_);
lean_dec(v_a_418_);
lean_dec(v_a_397_);
lean_dec(v_json_376_);
v_a_599_ = lean_ctor_get(v___x_588_, 0);
v_isSharedCheck_606_ = !lean_is_exclusive(v___x_588_);
if (v_isSharedCheck_606_ == 0)
{
v___x_601_ = v___x_588_;
v_isShared_602_ = v_isSharedCheck_606_;
goto v_resetjp_600_;
}
else
{
lean_inc(v_a_599_);
lean_dec(v___x_588_);
v___x_601_ = lean_box(0);
v_isShared_602_ = v_isSharedCheck_606_;
goto v_resetjp_600_;
}
v_resetjp_600_:
{
lean_object* v___x_604_; 
if (v_isShared_602_ == 0)
{
lean_ctor_set_tag(v___x_601_, 0);
v___x_604_ = v___x_601_;
goto v_reusejp_603_;
}
else
{
lean_object* v_reuseFailAlloc_605_; 
v_reuseFailAlloc_605_ = lean_alloc_ctor(0, 1, 0);
lean_ctor_set(v_reuseFailAlloc_605_, 0, v_a_599_);
v___x_604_ = v_reuseFailAlloc_605_;
goto v_reusejp_603_;
}
v_reusejp_603_:
{
return v___x_604_;
}
}
}
else
{
lean_object* v_a_607_; lean_object* v___x_608_; lean_object* v___x_609_; 
v_a_607_ = lean_ctor_get(v___x_588_, 0);
lean_inc(v_a_607_);
lean_dec_ref_known(v___x_588_, 1);
v___x_608_ = ((lean_object*)(lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__63));
lean_inc(v_json_376_);
v___x_609_ = l_Lean_Json_getObjValAs_x3f___at___00Lean_Server_instFromJsonIlean_fromJson_spec__0(v_json_376_, v___x_608_);
if (lean_obj_tag(v___x_609_) == 0)
{
lean_object* v_a_610_; lean_object* v___x_612_; uint8_t v_isShared_613_; uint8_t v_isSharedCheck_619_; 
lean_dec(v_a_607_);
lean_dec(v_a_586_);
lean_dec(v_a_565_);
lean_dec(v_a_544_);
lean_dec(v_a_523_);
lean_dec(v_a_502_);
lean_dec(v_a_481_);
lean_dec(v_a_460_);
lean_dec(v_a_439_);
lean_dec(v_a_418_);
lean_dec(v_a_397_);
lean_dec(v_json_376_);
v_a_610_ = lean_ctor_get(v___x_609_, 0);
v_isSharedCheck_619_ = !lean_is_exclusive(v___x_609_);
if (v_isSharedCheck_619_ == 0)
{
v___x_612_ = v___x_609_;
v_isShared_613_ = v_isSharedCheck_619_;
goto v_resetjp_611_;
}
else
{
lean_inc(v_a_610_);
lean_dec(v___x_609_);
v___x_612_ = lean_box(0);
v_isShared_613_ = v_isSharedCheck_619_;
goto v_resetjp_611_;
}
v_resetjp_611_:
{
lean_object* v___x_614_; lean_object* v___x_615_; lean_object* v___x_617_; 
v___x_614_ = lean_obj_once(&lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__67, &lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__67_once, _init_lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__67);
v___x_615_ = lean_string_append(v___x_614_, v_a_610_);
lean_dec(v_a_610_);
if (v_isShared_613_ == 0)
{
lean_ctor_set(v___x_612_, 0, v___x_615_);
v___x_617_ = v___x_612_;
goto v_reusejp_616_;
}
else
{
lean_object* v_reuseFailAlloc_618_; 
v_reuseFailAlloc_618_ = lean_alloc_ctor(0, 1, 0);
lean_ctor_set(v_reuseFailAlloc_618_, 0, v___x_615_);
v___x_617_ = v_reuseFailAlloc_618_;
goto v_reusejp_616_;
}
v_reusejp_616_:
{
return v___x_617_;
}
}
}
else
{
if (lean_obj_tag(v___x_609_) == 0)
{
lean_object* v_a_620_; lean_object* v___x_622_; uint8_t v_isShared_623_; uint8_t v_isSharedCheck_627_; 
lean_dec(v_a_607_);
lean_dec(v_a_586_);
lean_dec(v_a_565_);
lean_dec(v_a_544_);
lean_dec(v_a_523_);
lean_dec(v_a_502_);
lean_dec(v_a_481_);
lean_dec(v_a_460_);
lean_dec(v_a_439_);
lean_dec(v_a_418_);
lean_dec(v_a_397_);
lean_dec(v_json_376_);
v_a_620_ = lean_ctor_get(v___x_609_, 0);
v_isSharedCheck_627_ = !lean_is_exclusive(v___x_609_);
if (v_isSharedCheck_627_ == 0)
{
v___x_622_ = v___x_609_;
v_isShared_623_ = v_isSharedCheck_627_;
goto v_resetjp_621_;
}
else
{
lean_inc(v_a_620_);
lean_dec(v___x_609_);
v___x_622_ = lean_box(0);
v_isShared_623_ = v_isSharedCheck_627_;
goto v_resetjp_621_;
}
v_resetjp_621_:
{
lean_object* v___x_625_; 
if (v_isShared_623_ == 0)
{
lean_ctor_set_tag(v___x_622_, 0);
v___x_625_ = v___x_622_;
goto v_reusejp_624_;
}
else
{
lean_object* v_reuseFailAlloc_626_; 
v_reuseFailAlloc_626_ = lean_alloc_ctor(0, 1, 0);
lean_ctor_set(v_reuseFailAlloc_626_, 0, v_a_620_);
v___x_625_ = v_reuseFailAlloc_626_;
goto v_reusejp_624_;
}
v_reusejp_624_:
{
return v___x_625_;
}
}
}
else
{
lean_object* v_a_628_; lean_object* v___x_629_; lean_object* v___x_630_; 
v_a_628_ = lean_ctor_get(v___x_609_, 0);
lean_inc(v_a_628_);
lean_dec_ref_known(v___x_609_, 1);
v___x_629_ = ((lean_object*)(lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__68));
lean_inc(v_json_376_);
v___x_630_ = l_Lean_Json_getObjValAs_x3f___at___00Lean_Server_instFromJsonIlean_fromJson_spec__0(v_json_376_, v___x_629_);
if (lean_obj_tag(v___x_630_) == 0)
{
lean_object* v_a_631_; lean_object* v___x_633_; uint8_t v_isShared_634_; uint8_t v_isSharedCheck_640_; 
lean_dec(v_a_628_);
lean_dec(v_a_607_);
lean_dec(v_a_586_);
lean_dec(v_a_565_);
lean_dec(v_a_544_);
lean_dec(v_a_523_);
lean_dec(v_a_502_);
lean_dec(v_a_481_);
lean_dec(v_a_460_);
lean_dec(v_a_439_);
lean_dec(v_a_418_);
lean_dec(v_a_397_);
lean_dec(v_json_376_);
v_a_631_ = lean_ctor_get(v___x_630_, 0);
v_isSharedCheck_640_ = !lean_is_exclusive(v___x_630_);
if (v_isSharedCheck_640_ == 0)
{
v___x_633_ = v___x_630_;
v_isShared_634_ = v_isSharedCheck_640_;
goto v_resetjp_632_;
}
else
{
lean_inc(v_a_631_);
lean_dec(v___x_630_);
v___x_633_ = lean_box(0);
v_isShared_634_ = v_isSharedCheck_640_;
goto v_resetjp_632_;
}
v_resetjp_632_:
{
lean_object* v___x_635_; lean_object* v___x_636_; lean_object* v___x_638_; 
v___x_635_ = lean_obj_once(&lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__72, &lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__72_once, _init_lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__72);
v___x_636_ = lean_string_append(v___x_635_, v_a_631_);
lean_dec(v_a_631_);
if (v_isShared_634_ == 0)
{
lean_ctor_set(v___x_633_, 0, v___x_636_);
v___x_638_ = v___x_633_;
goto v_reusejp_637_;
}
else
{
lean_object* v_reuseFailAlloc_639_; 
v_reuseFailAlloc_639_ = lean_alloc_ctor(0, 1, 0);
lean_ctor_set(v_reuseFailAlloc_639_, 0, v___x_636_);
v___x_638_ = v_reuseFailAlloc_639_;
goto v_reusejp_637_;
}
v_reusejp_637_:
{
return v___x_638_;
}
}
}
else
{
if (lean_obj_tag(v___x_630_) == 0)
{
lean_object* v_a_641_; lean_object* v___x_643_; uint8_t v_isShared_644_; uint8_t v_isSharedCheck_648_; 
lean_dec(v_a_628_);
lean_dec(v_a_607_);
lean_dec(v_a_586_);
lean_dec(v_a_565_);
lean_dec(v_a_544_);
lean_dec(v_a_523_);
lean_dec(v_a_502_);
lean_dec(v_a_481_);
lean_dec(v_a_460_);
lean_dec(v_a_439_);
lean_dec(v_a_418_);
lean_dec(v_a_397_);
lean_dec(v_json_376_);
v_a_641_ = lean_ctor_get(v___x_630_, 0);
v_isSharedCheck_648_ = !lean_is_exclusive(v___x_630_);
if (v_isSharedCheck_648_ == 0)
{
v___x_643_ = v___x_630_;
v_isShared_644_ = v_isSharedCheck_648_;
goto v_resetjp_642_;
}
else
{
lean_inc(v_a_641_);
lean_dec(v___x_630_);
v___x_643_ = lean_box(0);
v_isShared_644_ = v_isSharedCheck_648_;
goto v_resetjp_642_;
}
v_resetjp_642_:
{
lean_object* v___x_646_; 
if (v_isShared_644_ == 0)
{
lean_ctor_set_tag(v___x_643_, 0);
v___x_646_ = v___x_643_;
goto v_reusejp_645_;
}
else
{
lean_object* v_reuseFailAlloc_647_; 
v_reuseFailAlloc_647_ = lean_alloc_ctor(0, 1, 0);
lean_ctor_set(v_reuseFailAlloc_647_, 0, v_a_641_);
v___x_646_ = v_reuseFailAlloc_647_;
goto v_reusejp_645_;
}
v_reusejp_645_:
{
return v___x_646_;
}
}
}
else
{
lean_object* v_a_649_; lean_object* v___x_650_; lean_object* v___x_651_; 
v_a_649_ = lean_ctor_get(v___x_630_, 0);
lean_inc(v_a_649_);
lean_dec_ref_known(v___x_630_, 1);
v___x_650_ = ((lean_object*)(lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__73));
lean_inc(v_json_376_);
v___x_651_ = l_Lean_Json_getObjValAs_x3f___at___00Lean_Server_instFromJsonIlean_fromJson_spec__0(v_json_376_, v___x_650_);
if (lean_obj_tag(v___x_651_) == 0)
{
lean_object* v_a_652_; lean_object* v___x_654_; uint8_t v_isShared_655_; uint8_t v_isSharedCheck_661_; 
lean_dec(v_a_649_);
lean_dec(v_a_628_);
lean_dec(v_a_607_);
lean_dec(v_a_586_);
lean_dec(v_a_565_);
lean_dec(v_a_544_);
lean_dec(v_a_523_);
lean_dec(v_a_502_);
lean_dec(v_a_481_);
lean_dec(v_a_460_);
lean_dec(v_a_439_);
lean_dec(v_a_418_);
lean_dec(v_a_397_);
lean_dec(v_json_376_);
v_a_652_ = lean_ctor_get(v___x_651_, 0);
v_isSharedCheck_661_ = !lean_is_exclusive(v___x_651_);
if (v_isSharedCheck_661_ == 0)
{
v___x_654_ = v___x_651_;
v_isShared_655_ = v_isSharedCheck_661_;
goto v_resetjp_653_;
}
else
{
lean_inc(v_a_652_);
lean_dec(v___x_651_);
v___x_654_ = lean_box(0);
v_isShared_655_ = v_isSharedCheck_661_;
goto v_resetjp_653_;
}
v_resetjp_653_:
{
lean_object* v___x_656_; lean_object* v___x_657_; lean_object* v___x_659_; 
v___x_656_ = lean_obj_once(&lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__77, &lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__77_once, _init_lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__77);
v___x_657_ = lean_string_append(v___x_656_, v_a_652_);
lean_dec(v_a_652_);
if (v_isShared_655_ == 0)
{
lean_ctor_set(v___x_654_, 0, v___x_657_);
v___x_659_ = v___x_654_;
goto v_reusejp_658_;
}
else
{
lean_object* v_reuseFailAlloc_660_; 
v_reuseFailAlloc_660_ = lean_alloc_ctor(0, 1, 0);
lean_ctor_set(v_reuseFailAlloc_660_, 0, v___x_657_);
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
if (lean_obj_tag(v___x_651_) == 0)
{
lean_object* v_a_662_; lean_object* v___x_664_; uint8_t v_isShared_665_; uint8_t v_isSharedCheck_669_; 
lean_dec(v_a_649_);
lean_dec(v_a_628_);
lean_dec(v_a_607_);
lean_dec(v_a_586_);
lean_dec(v_a_565_);
lean_dec(v_a_544_);
lean_dec(v_a_523_);
lean_dec(v_a_502_);
lean_dec(v_a_481_);
lean_dec(v_a_460_);
lean_dec(v_a_439_);
lean_dec(v_a_418_);
lean_dec(v_a_397_);
lean_dec(v_json_376_);
v_a_662_ = lean_ctor_get(v___x_651_, 0);
v_isSharedCheck_669_ = !lean_is_exclusive(v___x_651_);
if (v_isSharedCheck_669_ == 0)
{
v___x_664_ = v___x_651_;
v_isShared_665_ = v_isSharedCheck_669_;
goto v_resetjp_663_;
}
else
{
lean_inc(v_a_662_);
lean_dec(v___x_651_);
v___x_664_ = lean_box(0);
v_isShared_665_ = v_isSharedCheck_669_;
goto v_resetjp_663_;
}
v_resetjp_663_:
{
lean_object* v___x_667_; 
if (v_isShared_665_ == 0)
{
lean_ctor_set_tag(v___x_664_, 0);
v___x_667_ = v___x_664_;
goto v_reusejp_666_;
}
else
{
lean_object* v_reuseFailAlloc_668_; 
v_reuseFailAlloc_668_ = lean_alloc_ctor(0, 1, 0);
lean_ctor_set(v_reuseFailAlloc_668_, 0, v_a_662_);
v___x_667_ = v_reuseFailAlloc_668_;
goto v_reusejp_666_;
}
v_reusejp_666_:
{
return v___x_667_;
}
}
}
else
{
lean_object* v_a_670_; lean_object* v___x_671_; lean_object* v___x_672_; 
v_a_670_ = lean_ctor_get(v___x_651_, 0);
lean_inc(v_a_670_);
lean_dec_ref_known(v___x_651_, 1);
v___x_671_ = ((lean_object*)(lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__78));
lean_inc(v_json_376_);
v___x_672_ = l_Lean_Json_getObjValAs_x3f___at___00Lean_Server_instFromJsonIlean_fromJson_spec__0(v_json_376_, v___x_671_);
if (lean_obj_tag(v___x_672_) == 0)
{
lean_object* v_a_673_; lean_object* v___x_675_; uint8_t v_isShared_676_; uint8_t v_isSharedCheck_682_; 
lean_dec(v_a_670_);
lean_dec(v_a_649_);
lean_dec(v_a_628_);
lean_dec(v_a_607_);
lean_dec(v_a_586_);
lean_dec(v_a_565_);
lean_dec(v_a_544_);
lean_dec(v_a_523_);
lean_dec(v_a_502_);
lean_dec(v_a_481_);
lean_dec(v_a_460_);
lean_dec(v_a_439_);
lean_dec(v_a_418_);
lean_dec(v_a_397_);
lean_dec(v_json_376_);
v_a_673_ = lean_ctor_get(v___x_672_, 0);
v_isSharedCheck_682_ = !lean_is_exclusive(v___x_672_);
if (v_isSharedCheck_682_ == 0)
{
v___x_675_ = v___x_672_;
v_isShared_676_ = v_isSharedCheck_682_;
goto v_resetjp_674_;
}
else
{
lean_inc(v_a_673_);
lean_dec(v___x_672_);
v___x_675_ = lean_box(0);
v_isShared_676_ = v_isSharedCheck_682_;
goto v_resetjp_674_;
}
v_resetjp_674_:
{
lean_object* v___x_677_; lean_object* v___x_678_; lean_object* v___x_680_; 
v___x_677_ = lean_obj_once(&lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__82, &lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__82_once, _init_lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__82);
v___x_678_ = lean_string_append(v___x_677_, v_a_673_);
lean_dec(v_a_673_);
if (v_isShared_676_ == 0)
{
lean_ctor_set(v___x_675_, 0, v___x_678_);
v___x_680_ = v___x_675_;
goto v_reusejp_679_;
}
else
{
lean_object* v_reuseFailAlloc_681_; 
v_reuseFailAlloc_681_ = lean_alloc_ctor(0, 1, 0);
lean_ctor_set(v_reuseFailAlloc_681_, 0, v___x_678_);
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
if (lean_obj_tag(v___x_672_) == 0)
{
lean_object* v_a_683_; lean_object* v___x_685_; uint8_t v_isShared_686_; uint8_t v_isSharedCheck_690_; 
lean_dec(v_a_670_);
lean_dec(v_a_649_);
lean_dec(v_a_628_);
lean_dec(v_a_607_);
lean_dec(v_a_586_);
lean_dec(v_a_565_);
lean_dec(v_a_544_);
lean_dec(v_a_523_);
lean_dec(v_a_502_);
lean_dec(v_a_481_);
lean_dec(v_a_460_);
lean_dec(v_a_439_);
lean_dec(v_a_418_);
lean_dec(v_a_397_);
lean_dec(v_json_376_);
v_a_683_ = lean_ctor_get(v___x_672_, 0);
v_isSharedCheck_690_ = !lean_is_exclusive(v___x_672_);
if (v_isSharedCheck_690_ == 0)
{
v___x_685_ = v___x_672_;
v_isShared_686_ = v_isSharedCheck_690_;
goto v_resetjp_684_;
}
else
{
lean_inc(v_a_683_);
lean_dec(v___x_672_);
v___x_685_ = lean_box(0);
v_isShared_686_ = v_isSharedCheck_690_;
goto v_resetjp_684_;
}
v_resetjp_684_:
{
lean_object* v___x_688_; 
if (v_isShared_686_ == 0)
{
lean_ctor_set_tag(v___x_685_, 0);
v___x_688_ = v___x_685_;
goto v_reusejp_687_;
}
else
{
lean_object* v_reuseFailAlloc_689_; 
v_reuseFailAlloc_689_ = lean_alloc_ctor(0, 1, 0);
lean_ctor_set(v_reuseFailAlloc_689_, 0, v_a_683_);
v___x_688_ = v_reuseFailAlloc_689_;
goto v_reusejp_687_;
}
v_reusejp_687_:
{
return v___x_688_;
}
}
}
else
{
lean_object* v_a_691_; lean_object* v___x_692_; lean_object* v___x_693_; 
v_a_691_ = lean_ctor_get(v___x_672_, 0);
lean_inc(v_a_691_);
lean_dec_ref_known(v___x_672_, 1);
v___x_692_ = ((lean_object*)(lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__83));
lean_inc(v_json_376_);
v___x_693_ = l_Lean_Json_getObjValAs_x3f___at___00Lean_Server_instFromJsonIlean_fromJson_spec__0(v_json_376_, v___x_692_);
if (lean_obj_tag(v___x_693_) == 0)
{
lean_object* v_a_694_; lean_object* v___x_696_; uint8_t v_isShared_697_; uint8_t v_isSharedCheck_703_; 
lean_dec(v_a_691_);
lean_dec(v_a_670_);
lean_dec(v_a_649_);
lean_dec(v_a_628_);
lean_dec(v_a_607_);
lean_dec(v_a_586_);
lean_dec(v_a_565_);
lean_dec(v_a_544_);
lean_dec(v_a_523_);
lean_dec(v_a_502_);
lean_dec(v_a_481_);
lean_dec(v_a_460_);
lean_dec(v_a_439_);
lean_dec(v_a_418_);
lean_dec(v_a_397_);
lean_dec(v_json_376_);
v_a_694_ = lean_ctor_get(v___x_693_, 0);
v_isSharedCheck_703_ = !lean_is_exclusive(v___x_693_);
if (v_isSharedCheck_703_ == 0)
{
v___x_696_ = v___x_693_;
v_isShared_697_ = v_isSharedCheck_703_;
goto v_resetjp_695_;
}
else
{
lean_inc(v_a_694_);
lean_dec(v___x_693_);
v___x_696_ = lean_box(0);
v_isShared_697_ = v_isSharedCheck_703_;
goto v_resetjp_695_;
}
v_resetjp_695_:
{
lean_object* v___x_698_; lean_object* v___x_699_; lean_object* v___x_701_; 
v___x_698_ = lean_obj_once(&lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__87, &lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__87_once, _init_lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__87);
v___x_699_ = lean_string_append(v___x_698_, v_a_694_);
lean_dec(v_a_694_);
if (v_isShared_697_ == 0)
{
lean_ctor_set(v___x_696_, 0, v___x_699_);
v___x_701_ = v___x_696_;
goto v_reusejp_700_;
}
else
{
lean_object* v_reuseFailAlloc_702_; 
v_reuseFailAlloc_702_ = lean_alloc_ctor(0, 1, 0);
lean_ctor_set(v_reuseFailAlloc_702_, 0, v___x_699_);
v___x_701_ = v_reuseFailAlloc_702_;
goto v_reusejp_700_;
}
v_reusejp_700_:
{
return v___x_701_;
}
}
}
else
{
if (lean_obj_tag(v___x_693_) == 0)
{
lean_object* v_a_704_; lean_object* v___x_706_; uint8_t v_isShared_707_; uint8_t v_isSharedCheck_711_; 
lean_dec(v_a_691_);
lean_dec(v_a_670_);
lean_dec(v_a_649_);
lean_dec(v_a_628_);
lean_dec(v_a_607_);
lean_dec(v_a_586_);
lean_dec(v_a_565_);
lean_dec(v_a_544_);
lean_dec(v_a_523_);
lean_dec(v_a_502_);
lean_dec(v_a_481_);
lean_dec(v_a_460_);
lean_dec(v_a_439_);
lean_dec(v_a_418_);
lean_dec(v_a_397_);
lean_dec(v_json_376_);
v_a_704_ = lean_ctor_get(v___x_693_, 0);
v_isSharedCheck_711_ = !lean_is_exclusive(v___x_693_);
if (v_isSharedCheck_711_ == 0)
{
v___x_706_ = v___x_693_;
v_isShared_707_ = v_isSharedCheck_711_;
goto v_resetjp_705_;
}
else
{
lean_inc(v_a_704_);
lean_dec(v___x_693_);
v___x_706_ = lean_box(0);
v_isShared_707_ = v_isSharedCheck_711_;
goto v_resetjp_705_;
}
v_resetjp_705_:
{
lean_object* v___x_709_; 
if (v_isShared_707_ == 0)
{
lean_ctor_set_tag(v___x_706_, 0);
v___x_709_ = v___x_706_;
goto v_reusejp_708_;
}
else
{
lean_object* v_reuseFailAlloc_710_; 
v_reuseFailAlloc_710_ = lean_alloc_ctor(0, 1, 0);
lean_ctor_set(v_reuseFailAlloc_710_, 0, v_a_704_);
v___x_709_ = v_reuseFailAlloc_710_;
goto v_reusejp_708_;
}
v_reusejp_708_:
{
return v___x_709_;
}
}
}
else
{
lean_object* v_a_712_; lean_object* v___x_713_; lean_object* v___x_714_; 
v_a_712_ = lean_ctor_get(v___x_693_, 0);
lean_inc(v_a_712_);
lean_dec_ref_known(v___x_693_, 1);
v___x_713_ = ((lean_object*)(lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__88));
lean_inc(v_json_376_);
v___x_714_ = l_Lean_Json_getObjValAs_x3f___at___00Lean_Server_instFromJsonIlean_fromJson_spec__0(v_json_376_, v___x_713_);
if (lean_obj_tag(v___x_714_) == 0)
{
lean_object* v_a_715_; lean_object* v___x_717_; uint8_t v_isShared_718_; uint8_t v_isSharedCheck_724_; 
lean_dec(v_a_712_);
lean_dec(v_a_691_);
lean_dec(v_a_670_);
lean_dec(v_a_649_);
lean_dec(v_a_628_);
lean_dec(v_a_607_);
lean_dec(v_a_586_);
lean_dec(v_a_565_);
lean_dec(v_a_544_);
lean_dec(v_a_523_);
lean_dec(v_a_502_);
lean_dec(v_a_481_);
lean_dec(v_a_460_);
lean_dec(v_a_439_);
lean_dec(v_a_418_);
lean_dec(v_a_397_);
lean_dec(v_json_376_);
v_a_715_ = lean_ctor_get(v___x_714_, 0);
v_isSharedCheck_724_ = !lean_is_exclusive(v___x_714_);
if (v_isSharedCheck_724_ == 0)
{
v___x_717_ = v___x_714_;
v_isShared_718_ = v_isSharedCheck_724_;
goto v_resetjp_716_;
}
else
{
lean_inc(v_a_715_);
lean_dec(v___x_714_);
v___x_717_ = lean_box(0);
v_isShared_718_ = v_isSharedCheck_724_;
goto v_resetjp_716_;
}
v_resetjp_716_:
{
lean_object* v___x_719_; lean_object* v___x_720_; lean_object* v___x_722_; 
v___x_719_ = lean_obj_once(&lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__92, &lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__92_once, _init_lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__92);
v___x_720_ = lean_string_append(v___x_719_, v_a_715_);
lean_dec(v_a_715_);
if (v_isShared_718_ == 0)
{
lean_ctor_set(v___x_717_, 0, v___x_720_);
v___x_722_ = v___x_717_;
goto v_reusejp_721_;
}
else
{
lean_object* v_reuseFailAlloc_723_; 
v_reuseFailAlloc_723_ = lean_alloc_ctor(0, 1, 0);
lean_ctor_set(v_reuseFailAlloc_723_, 0, v___x_720_);
v___x_722_ = v_reuseFailAlloc_723_;
goto v_reusejp_721_;
}
v_reusejp_721_:
{
return v___x_722_;
}
}
}
else
{
if (lean_obj_tag(v___x_714_) == 0)
{
lean_object* v_a_725_; lean_object* v___x_727_; uint8_t v_isShared_728_; uint8_t v_isSharedCheck_732_; 
lean_dec(v_a_712_);
lean_dec(v_a_691_);
lean_dec(v_a_670_);
lean_dec(v_a_649_);
lean_dec(v_a_628_);
lean_dec(v_a_607_);
lean_dec(v_a_586_);
lean_dec(v_a_565_);
lean_dec(v_a_544_);
lean_dec(v_a_523_);
lean_dec(v_a_502_);
lean_dec(v_a_481_);
lean_dec(v_a_460_);
lean_dec(v_a_439_);
lean_dec(v_a_418_);
lean_dec(v_a_397_);
lean_dec(v_json_376_);
v_a_725_ = lean_ctor_get(v___x_714_, 0);
v_isSharedCheck_732_ = !lean_is_exclusive(v___x_714_);
if (v_isSharedCheck_732_ == 0)
{
v___x_727_ = v___x_714_;
v_isShared_728_ = v_isSharedCheck_732_;
goto v_resetjp_726_;
}
else
{
lean_inc(v_a_725_);
lean_dec(v___x_714_);
v___x_727_ = lean_box(0);
v_isShared_728_ = v_isSharedCheck_732_;
goto v_resetjp_726_;
}
v_resetjp_726_:
{
lean_object* v___x_730_; 
if (v_isShared_728_ == 0)
{
lean_ctor_set_tag(v___x_727_, 0);
v___x_730_ = v___x_727_;
goto v_reusejp_729_;
}
else
{
lean_object* v_reuseFailAlloc_731_; 
v_reuseFailAlloc_731_ = lean_alloc_ctor(0, 1, 0);
lean_ctor_set(v_reuseFailAlloc_731_, 0, v_a_725_);
v___x_730_ = v_reuseFailAlloc_731_;
goto v_reusejp_729_;
}
v_reusejp_729_:
{
return v___x_730_;
}
}
}
else
{
lean_object* v_a_733_; lean_object* v___x_734_; lean_object* v___x_735_; 
v_a_733_ = lean_ctor_get(v___x_714_, 0);
lean_inc(v_a_733_);
lean_dec_ref_known(v___x_714_, 1);
v___x_734_ = ((lean_object*)(lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__93));
lean_inc(v_json_376_);
v___x_735_ = l_Lean_Json_getObjValAs_x3f___at___00Lean_Server_instFromJsonIlean_fromJson_spec__0(v_json_376_, v___x_734_);
if (lean_obj_tag(v___x_735_) == 0)
{
lean_object* v_a_736_; lean_object* v___x_738_; uint8_t v_isShared_739_; uint8_t v_isSharedCheck_745_; 
lean_dec(v_a_733_);
lean_dec(v_a_712_);
lean_dec(v_a_691_);
lean_dec(v_a_670_);
lean_dec(v_a_649_);
lean_dec(v_a_628_);
lean_dec(v_a_607_);
lean_dec(v_a_586_);
lean_dec(v_a_565_);
lean_dec(v_a_544_);
lean_dec(v_a_523_);
lean_dec(v_a_502_);
lean_dec(v_a_481_);
lean_dec(v_a_460_);
lean_dec(v_a_439_);
lean_dec(v_a_418_);
lean_dec(v_a_397_);
lean_dec(v_json_376_);
v_a_736_ = lean_ctor_get(v___x_735_, 0);
v_isSharedCheck_745_ = !lean_is_exclusive(v___x_735_);
if (v_isSharedCheck_745_ == 0)
{
v___x_738_ = v___x_735_;
v_isShared_739_ = v_isSharedCheck_745_;
goto v_resetjp_737_;
}
else
{
lean_inc(v_a_736_);
lean_dec(v___x_735_);
v___x_738_ = lean_box(0);
v_isShared_739_ = v_isSharedCheck_745_;
goto v_resetjp_737_;
}
v_resetjp_737_:
{
lean_object* v___x_740_; lean_object* v___x_741_; lean_object* v___x_743_; 
v___x_740_ = lean_obj_once(&lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__97, &lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__97_once, _init_lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__97);
v___x_741_ = lean_string_append(v___x_740_, v_a_736_);
lean_dec(v_a_736_);
if (v_isShared_739_ == 0)
{
lean_ctor_set(v___x_738_, 0, v___x_741_);
v___x_743_ = v___x_738_;
goto v_reusejp_742_;
}
else
{
lean_object* v_reuseFailAlloc_744_; 
v_reuseFailAlloc_744_ = lean_alloc_ctor(0, 1, 0);
lean_ctor_set(v_reuseFailAlloc_744_, 0, v___x_741_);
v___x_743_ = v_reuseFailAlloc_744_;
goto v_reusejp_742_;
}
v_reusejp_742_:
{
return v___x_743_;
}
}
}
else
{
if (lean_obj_tag(v___x_735_) == 0)
{
lean_object* v_a_746_; lean_object* v___x_748_; uint8_t v_isShared_749_; uint8_t v_isSharedCheck_753_; 
lean_dec(v_a_733_);
lean_dec(v_a_712_);
lean_dec(v_a_691_);
lean_dec(v_a_670_);
lean_dec(v_a_649_);
lean_dec(v_a_628_);
lean_dec(v_a_607_);
lean_dec(v_a_586_);
lean_dec(v_a_565_);
lean_dec(v_a_544_);
lean_dec(v_a_523_);
lean_dec(v_a_502_);
lean_dec(v_a_481_);
lean_dec(v_a_460_);
lean_dec(v_a_439_);
lean_dec(v_a_418_);
lean_dec(v_a_397_);
lean_dec(v_json_376_);
v_a_746_ = lean_ctor_get(v___x_735_, 0);
v_isSharedCheck_753_ = !lean_is_exclusive(v___x_735_);
if (v_isSharedCheck_753_ == 0)
{
v___x_748_ = v___x_735_;
v_isShared_749_ = v_isSharedCheck_753_;
goto v_resetjp_747_;
}
else
{
lean_inc(v_a_746_);
lean_dec(v___x_735_);
v___x_748_ = lean_box(0);
v_isShared_749_ = v_isSharedCheck_753_;
goto v_resetjp_747_;
}
v_resetjp_747_:
{
lean_object* v___x_751_; 
if (v_isShared_749_ == 0)
{
lean_ctor_set_tag(v___x_748_, 0);
v___x_751_ = v___x_748_;
goto v_reusejp_750_;
}
else
{
lean_object* v_reuseFailAlloc_752_; 
v_reuseFailAlloc_752_ = lean_alloc_ctor(0, 1, 0);
lean_ctor_set(v_reuseFailAlloc_752_, 0, v_a_746_);
v___x_751_ = v_reuseFailAlloc_752_;
goto v_reusejp_750_;
}
v_reusejp_750_:
{
return v___x_751_;
}
}
}
else
{
lean_object* v_a_754_; lean_object* v___x_755_; lean_object* v___x_756_; 
v_a_754_ = lean_ctor_get(v___x_735_, 0);
lean_inc(v_a_754_);
lean_dec_ref_known(v___x_735_, 1);
v___x_755_ = ((lean_object*)(lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__98));
lean_inc(v_json_376_);
v___x_756_ = l_Lean_Json_getObjValAs_x3f___at___00Lean_Server_instFromJsonIlean_fromJson_spec__0(v_json_376_, v___x_755_);
if (lean_obj_tag(v___x_756_) == 0)
{
lean_object* v_a_757_; lean_object* v___x_759_; uint8_t v_isShared_760_; uint8_t v_isSharedCheck_766_; 
lean_dec(v_a_754_);
lean_dec(v_a_733_);
lean_dec(v_a_712_);
lean_dec(v_a_691_);
lean_dec(v_a_670_);
lean_dec(v_a_649_);
lean_dec(v_a_628_);
lean_dec(v_a_607_);
lean_dec(v_a_586_);
lean_dec(v_a_565_);
lean_dec(v_a_544_);
lean_dec(v_a_523_);
lean_dec(v_a_502_);
lean_dec(v_a_481_);
lean_dec(v_a_460_);
lean_dec(v_a_439_);
lean_dec(v_a_418_);
lean_dec(v_a_397_);
lean_dec(v_json_376_);
v_a_757_ = lean_ctor_get(v___x_756_, 0);
v_isSharedCheck_766_ = !lean_is_exclusive(v___x_756_);
if (v_isSharedCheck_766_ == 0)
{
v___x_759_ = v___x_756_;
v_isShared_760_ = v_isSharedCheck_766_;
goto v_resetjp_758_;
}
else
{
lean_inc(v_a_757_);
lean_dec(v___x_756_);
v___x_759_ = lean_box(0);
v_isShared_760_ = v_isSharedCheck_766_;
goto v_resetjp_758_;
}
v_resetjp_758_:
{
lean_object* v___x_761_; lean_object* v___x_762_; lean_object* v___x_764_; 
v___x_761_ = lean_obj_once(&lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__102, &lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__102_once, _init_lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__102);
v___x_762_ = lean_string_append(v___x_761_, v_a_757_);
lean_dec(v_a_757_);
if (v_isShared_760_ == 0)
{
lean_ctor_set(v___x_759_, 0, v___x_762_);
v___x_764_ = v___x_759_;
goto v_reusejp_763_;
}
else
{
lean_object* v_reuseFailAlloc_765_; 
v_reuseFailAlloc_765_ = lean_alloc_ctor(0, 1, 0);
lean_ctor_set(v_reuseFailAlloc_765_, 0, v___x_762_);
v___x_764_ = v_reuseFailAlloc_765_;
goto v_reusejp_763_;
}
v_reusejp_763_:
{
return v___x_764_;
}
}
}
else
{
if (lean_obj_tag(v___x_756_) == 0)
{
lean_object* v_a_767_; lean_object* v___x_769_; uint8_t v_isShared_770_; uint8_t v_isSharedCheck_774_; 
lean_dec(v_a_754_);
lean_dec(v_a_733_);
lean_dec(v_a_712_);
lean_dec(v_a_691_);
lean_dec(v_a_670_);
lean_dec(v_a_649_);
lean_dec(v_a_628_);
lean_dec(v_a_607_);
lean_dec(v_a_586_);
lean_dec(v_a_565_);
lean_dec(v_a_544_);
lean_dec(v_a_523_);
lean_dec(v_a_502_);
lean_dec(v_a_481_);
lean_dec(v_a_460_);
lean_dec(v_a_439_);
lean_dec(v_a_418_);
lean_dec(v_a_397_);
lean_dec(v_json_376_);
v_a_767_ = lean_ctor_get(v___x_756_, 0);
v_isSharedCheck_774_ = !lean_is_exclusive(v___x_756_);
if (v_isSharedCheck_774_ == 0)
{
v___x_769_ = v___x_756_;
v_isShared_770_ = v_isSharedCheck_774_;
goto v_resetjp_768_;
}
else
{
lean_inc(v_a_767_);
lean_dec(v___x_756_);
v___x_769_ = lean_box(0);
v_isShared_770_ = v_isSharedCheck_774_;
goto v_resetjp_768_;
}
v_resetjp_768_:
{
lean_object* v___x_772_; 
if (v_isShared_770_ == 0)
{
lean_ctor_set_tag(v___x_769_, 0);
v___x_772_ = v___x_769_;
goto v_reusejp_771_;
}
else
{
lean_object* v_reuseFailAlloc_773_; 
v_reuseFailAlloc_773_ = lean_alloc_ctor(0, 1, 0);
lean_ctor_set(v_reuseFailAlloc_773_, 0, v_a_767_);
v___x_772_ = v_reuseFailAlloc_773_;
goto v_reusejp_771_;
}
v_reusejp_771_:
{
return v___x_772_;
}
}
}
else
{
lean_object* v_a_775_; lean_object* v___x_776_; lean_object* v___x_777_; 
v_a_775_ = lean_ctor_get(v___x_756_, 0);
lean_inc(v_a_775_);
lean_dec_ref_known(v___x_756_, 1);
v___x_776_ = ((lean_object*)(lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__103));
lean_inc(v_json_376_);
v___x_777_ = l_Lean_Json_getObjValAs_x3f___at___00Lean_Server_instFromJsonIlean_fromJson_spec__0(v_json_376_, v___x_776_);
if (lean_obj_tag(v___x_777_) == 0)
{
lean_object* v_a_778_; lean_object* v___x_780_; uint8_t v_isShared_781_; uint8_t v_isSharedCheck_787_; 
lean_dec(v_a_775_);
lean_dec(v_a_754_);
lean_dec(v_a_733_);
lean_dec(v_a_712_);
lean_dec(v_a_691_);
lean_dec(v_a_670_);
lean_dec(v_a_649_);
lean_dec(v_a_628_);
lean_dec(v_a_607_);
lean_dec(v_a_586_);
lean_dec(v_a_565_);
lean_dec(v_a_544_);
lean_dec(v_a_523_);
lean_dec(v_a_502_);
lean_dec(v_a_481_);
lean_dec(v_a_460_);
lean_dec(v_a_439_);
lean_dec(v_a_418_);
lean_dec(v_a_397_);
lean_dec(v_json_376_);
v_a_778_ = lean_ctor_get(v___x_777_, 0);
v_isSharedCheck_787_ = !lean_is_exclusive(v___x_777_);
if (v_isSharedCheck_787_ == 0)
{
v___x_780_ = v___x_777_;
v_isShared_781_ = v_isSharedCheck_787_;
goto v_resetjp_779_;
}
else
{
lean_inc(v_a_778_);
lean_dec(v___x_777_);
v___x_780_ = lean_box(0);
v_isShared_781_ = v_isSharedCheck_787_;
goto v_resetjp_779_;
}
v_resetjp_779_:
{
lean_object* v___x_782_; lean_object* v___x_783_; lean_object* v___x_785_; 
v___x_782_ = lean_obj_once(&lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__107, &lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__107_once, _init_lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__107);
v___x_783_ = lean_string_append(v___x_782_, v_a_778_);
lean_dec(v_a_778_);
if (v_isShared_781_ == 0)
{
lean_ctor_set(v___x_780_, 0, v___x_783_);
v___x_785_ = v___x_780_;
goto v_reusejp_784_;
}
else
{
lean_object* v_reuseFailAlloc_786_; 
v_reuseFailAlloc_786_ = lean_alloc_ctor(0, 1, 0);
lean_ctor_set(v_reuseFailAlloc_786_, 0, v___x_783_);
v___x_785_ = v_reuseFailAlloc_786_;
goto v_reusejp_784_;
}
v_reusejp_784_:
{
return v___x_785_;
}
}
}
else
{
if (lean_obj_tag(v___x_777_) == 0)
{
lean_object* v_a_788_; lean_object* v___x_790_; uint8_t v_isShared_791_; uint8_t v_isSharedCheck_795_; 
lean_dec(v_a_775_);
lean_dec(v_a_754_);
lean_dec(v_a_733_);
lean_dec(v_a_712_);
lean_dec(v_a_691_);
lean_dec(v_a_670_);
lean_dec(v_a_649_);
lean_dec(v_a_628_);
lean_dec(v_a_607_);
lean_dec(v_a_586_);
lean_dec(v_a_565_);
lean_dec(v_a_544_);
lean_dec(v_a_523_);
lean_dec(v_a_502_);
lean_dec(v_a_481_);
lean_dec(v_a_460_);
lean_dec(v_a_439_);
lean_dec(v_a_418_);
lean_dec(v_a_397_);
lean_dec(v_json_376_);
v_a_788_ = lean_ctor_get(v___x_777_, 0);
v_isSharedCheck_795_ = !lean_is_exclusive(v___x_777_);
if (v_isSharedCheck_795_ == 0)
{
v___x_790_ = v___x_777_;
v_isShared_791_ = v_isSharedCheck_795_;
goto v_resetjp_789_;
}
else
{
lean_inc(v_a_788_);
lean_dec(v___x_777_);
v___x_790_ = lean_box(0);
v_isShared_791_ = v_isSharedCheck_795_;
goto v_resetjp_789_;
}
v_resetjp_789_:
{
lean_object* v___x_793_; 
if (v_isShared_791_ == 0)
{
lean_ctor_set_tag(v___x_790_, 0);
v___x_793_ = v___x_790_;
goto v_reusejp_792_;
}
else
{
lean_object* v_reuseFailAlloc_794_; 
v_reuseFailAlloc_794_ = lean_alloc_ctor(0, 1, 0);
lean_ctor_set(v_reuseFailAlloc_794_, 0, v_a_788_);
v___x_793_ = v_reuseFailAlloc_794_;
goto v_reusejp_792_;
}
v_reusejp_792_:
{
return v___x_793_;
}
}
}
else
{
lean_object* v_a_796_; lean_object* v___x_797_; lean_object* v___x_798_; 
v_a_796_ = lean_ctor_get(v___x_777_, 0);
lean_inc(v_a_796_);
lean_dec_ref_known(v___x_777_, 1);
v___x_797_ = ((lean_object*)(lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__108));
lean_inc(v_json_376_);
v___x_798_ = l_Lean_Json_getObjValAs_x3f___at___00Lean_Server_instFromJsonIlean_fromJson_spec__0(v_json_376_, v___x_797_);
if (lean_obj_tag(v___x_798_) == 0)
{
lean_object* v_a_799_; lean_object* v___x_801_; uint8_t v_isShared_802_; uint8_t v_isSharedCheck_808_; 
lean_dec(v_a_796_);
lean_dec(v_a_775_);
lean_dec(v_a_754_);
lean_dec(v_a_733_);
lean_dec(v_a_712_);
lean_dec(v_a_691_);
lean_dec(v_a_670_);
lean_dec(v_a_649_);
lean_dec(v_a_628_);
lean_dec(v_a_607_);
lean_dec(v_a_586_);
lean_dec(v_a_565_);
lean_dec(v_a_544_);
lean_dec(v_a_523_);
lean_dec(v_a_502_);
lean_dec(v_a_481_);
lean_dec(v_a_460_);
lean_dec(v_a_439_);
lean_dec(v_a_418_);
lean_dec(v_a_397_);
lean_dec(v_json_376_);
v_a_799_ = lean_ctor_get(v___x_798_, 0);
v_isSharedCheck_808_ = !lean_is_exclusive(v___x_798_);
if (v_isSharedCheck_808_ == 0)
{
v___x_801_ = v___x_798_;
v_isShared_802_ = v_isSharedCheck_808_;
goto v_resetjp_800_;
}
else
{
lean_inc(v_a_799_);
lean_dec(v___x_798_);
v___x_801_ = lean_box(0);
v_isShared_802_ = v_isSharedCheck_808_;
goto v_resetjp_800_;
}
v_resetjp_800_:
{
lean_object* v___x_803_; lean_object* v___x_804_; lean_object* v___x_806_; 
v___x_803_ = lean_obj_once(&lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__112, &lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__112_once, _init_lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__112);
v___x_804_ = lean_string_append(v___x_803_, v_a_799_);
lean_dec(v_a_799_);
if (v_isShared_802_ == 0)
{
lean_ctor_set(v___x_801_, 0, v___x_804_);
v___x_806_ = v___x_801_;
goto v_reusejp_805_;
}
else
{
lean_object* v_reuseFailAlloc_807_; 
v_reuseFailAlloc_807_ = lean_alloc_ctor(0, 1, 0);
lean_ctor_set(v_reuseFailAlloc_807_, 0, v___x_804_);
v___x_806_ = v_reuseFailAlloc_807_;
goto v_reusejp_805_;
}
v_reusejp_805_:
{
return v___x_806_;
}
}
}
else
{
if (lean_obj_tag(v___x_798_) == 0)
{
lean_object* v_a_809_; lean_object* v___x_811_; uint8_t v_isShared_812_; uint8_t v_isSharedCheck_816_; 
lean_dec(v_a_796_);
lean_dec(v_a_775_);
lean_dec(v_a_754_);
lean_dec(v_a_733_);
lean_dec(v_a_712_);
lean_dec(v_a_691_);
lean_dec(v_a_670_);
lean_dec(v_a_649_);
lean_dec(v_a_628_);
lean_dec(v_a_607_);
lean_dec(v_a_586_);
lean_dec(v_a_565_);
lean_dec(v_a_544_);
lean_dec(v_a_523_);
lean_dec(v_a_502_);
lean_dec(v_a_481_);
lean_dec(v_a_460_);
lean_dec(v_a_439_);
lean_dec(v_a_418_);
lean_dec(v_a_397_);
lean_dec(v_json_376_);
v_a_809_ = lean_ctor_get(v___x_798_, 0);
v_isSharedCheck_816_ = !lean_is_exclusive(v___x_798_);
if (v_isSharedCheck_816_ == 0)
{
v___x_811_ = v___x_798_;
v_isShared_812_ = v_isSharedCheck_816_;
goto v_resetjp_810_;
}
else
{
lean_inc(v_a_809_);
lean_dec(v___x_798_);
v___x_811_ = lean_box(0);
v_isShared_812_ = v_isSharedCheck_816_;
goto v_resetjp_810_;
}
v_resetjp_810_:
{
lean_object* v___x_814_; 
if (v_isShared_812_ == 0)
{
lean_ctor_set_tag(v___x_811_, 0);
v___x_814_ = v___x_811_;
goto v_reusejp_813_;
}
else
{
lean_object* v_reuseFailAlloc_815_; 
v_reuseFailAlloc_815_ = lean_alloc_ctor(0, 1, 0);
lean_ctor_set(v_reuseFailAlloc_815_, 0, v_a_809_);
v___x_814_ = v_reuseFailAlloc_815_;
goto v_reusejp_813_;
}
v_reusejp_813_:
{
return v___x_814_;
}
}
}
else
{
lean_object* v_a_817_; lean_object* v___x_818_; lean_object* v___x_819_; 
v_a_817_ = lean_ctor_get(v___x_798_, 0);
lean_inc(v_a_817_);
lean_dec_ref_known(v___x_798_, 1);
v___x_818_ = ((lean_object*)(lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__113));
lean_inc(v_json_376_);
v___x_819_ = l_Lean_Json_getObjValAs_x3f___at___00Lean_Server_instFromJsonIlean_fromJson_spec__0(v_json_376_, v___x_818_);
if (lean_obj_tag(v___x_819_) == 0)
{
lean_object* v_a_820_; lean_object* v___x_822_; uint8_t v_isShared_823_; uint8_t v_isSharedCheck_829_; 
lean_dec(v_a_817_);
lean_dec(v_a_796_);
lean_dec(v_a_775_);
lean_dec(v_a_754_);
lean_dec(v_a_733_);
lean_dec(v_a_712_);
lean_dec(v_a_691_);
lean_dec(v_a_670_);
lean_dec(v_a_649_);
lean_dec(v_a_628_);
lean_dec(v_a_607_);
lean_dec(v_a_586_);
lean_dec(v_a_565_);
lean_dec(v_a_544_);
lean_dec(v_a_523_);
lean_dec(v_a_502_);
lean_dec(v_a_481_);
lean_dec(v_a_460_);
lean_dec(v_a_439_);
lean_dec(v_a_418_);
lean_dec(v_a_397_);
lean_dec(v_json_376_);
v_a_820_ = lean_ctor_get(v___x_819_, 0);
v_isSharedCheck_829_ = !lean_is_exclusive(v___x_819_);
if (v_isSharedCheck_829_ == 0)
{
v___x_822_ = v___x_819_;
v_isShared_823_ = v_isSharedCheck_829_;
goto v_resetjp_821_;
}
else
{
lean_inc(v_a_820_);
lean_dec(v___x_819_);
v___x_822_ = lean_box(0);
v_isShared_823_ = v_isSharedCheck_829_;
goto v_resetjp_821_;
}
v_resetjp_821_:
{
lean_object* v___x_824_; lean_object* v___x_825_; lean_object* v___x_827_; 
v___x_824_ = lean_obj_once(&lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__117, &lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__117_once, _init_lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__117);
v___x_825_ = lean_string_append(v___x_824_, v_a_820_);
lean_dec(v_a_820_);
if (v_isShared_823_ == 0)
{
lean_ctor_set(v___x_822_, 0, v___x_825_);
v___x_827_ = v___x_822_;
goto v_reusejp_826_;
}
else
{
lean_object* v_reuseFailAlloc_828_; 
v_reuseFailAlloc_828_ = lean_alloc_ctor(0, 1, 0);
lean_ctor_set(v_reuseFailAlloc_828_, 0, v___x_825_);
v___x_827_ = v_reuseFailAlloc_828_;
goto v_reusejp_826_;
}
v_reusejp_826_:
{
return v___x_827_;
}
}
}
else
{
if (lean_obj_tag(v___x_819_) == 0)
{
lean_object* v_a_830_; lean_object* v___x_832_; uint8_t v_isShared_833_; uint8_t v_isSharedCheck_837_; 
lean_dec(v_a_817_);
lean_dec(v_a_796_);
lean_dec(v_a_775_);
lean_dec(v_a_754_);
lean_dec(v_a_733_);
lean_dec(v_a_712_);
lean_dec(v_a_691_);
lean_dec(v_a_670_);
lean_dec(v_a_649_);
lean_dec(v_a_628_);
lean_dec(v_a_607_);
lean_dec(v_a_586_);
lean_dec(v_a_565_);
lean_dec(v_a_544_);
lean_dec(v_a_523_);
lean_dec(v_a_502_);
lean_dec(v_a_481_);
lean_dec(v_a_460_);
lean_dec(v_a_439_);
lean_dec(v_a_418_);
lean_dec(v_a_397_);
lean_dec(v_json_376_);
v_a_830_ = lean_ctor_get(v___x_819_, 0);
v_isSharedCheck_837_ = !lean_is_exclusive(v___x_819_);
if (v_isSharedCheck_837_ == 0)
{
v___x_832_ = v___x_819_;
v_isShared_833_ = v_isSharedCheck_837_;
goto v_resetjp_831_;
}
else
{
lean_inc(v_a_830_);
lean_dec(v___x_819_);
v___x_832_ = lean_box(0);
v_isShared_833_ = v_isSharedCheck_837_;
goto v_resetjp_831_;
}
v_resetjp_831_:
{
lean_object* v___x_835_; 
if (v_isShared_833_ == 0)
{
lean_ctor_set_tag(v___x_832_, 0);
v___x_835_ = v___x_832_;
goto v_reusejp_834_;
}
else
{
lean_object* v_reuseFailAlloc_836_; 
v_reuseFailAlloc_836_ = lean_alloc_ctor(0, 1, 0);
lean_ctor_set(v_reuseFailAlloc_836_, 0, v_a_830_);
v___x_835_ = v_reuseFailAlloc_836_;
goto v_reusejp_834_;
}
v_reusejp_834_:
{
return v___x_835_;
}
}
}
else
{
lean_object* v_a_838_; lean_object* v___x_839_; lean_object* v___x_840_; 
v_a_838_ = lean_ctor_get(v___x_819_, 0);
lean_inc(v_a_838_);
lean_dec_ref_known(v___x_819_, 1);
v___x_839_ = ((lean_object*)(lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__118));
lean_inc(v_json_376_);
v___x_840_ = l_Lean_Json_getObjValAs_x3f___at___00Lean_Server_instFromJsonIlean_fromJson_spec__0(v_json_376_, v___x_839_);
if (lean_obj_tag(v___x_840_) == 0)
{
lean_object* v_a_841_; lean_object* v___x_843_; uint8_t v_isShared_844_; uint8_t v_isSharedCheck_850_; 
lean_dec(v_a_838_);
lean_dec(v_a_817_);
lean_dec(v_a_796_);
lean_dec(v_a_775_);
lean_dec(v_a_754_);
lean_dec(v_a_733_);
lean_dec(v_a_712_);
lean_dec(v_a_691_);
lean_dec(v_a_670_);
lean_dec(v_a_649_);
lean_dec(v_a_628_);
lean_dec(v_a_607_);
lean_dec(v_a_586_);
lean_dec(v_a_565_);
lean_dec(v_a_544_);
lean_dec(v_a_523_);
lean_dec(v_a_502_);
lean_dec(v_a_481_);
lean_dec(v_a_460_);
lean_dec(v_a_439_);
lean_dec(v_a_418_);
lean_dec(v_a_397_);
lean_dec(v_json_376_);
v_a_841_ = lean_ctor_get(v___x_840_, 0);
v_isSharedCheck_850_ = !lean_is_exclusive(v___x_840_);
if (v_isSharedCheck_850_ == 0)
{
v___x_843_ = v___x_840_;
v_isShared_844_ = v_isSharedCheck_850_;
goto v_resetjp_842_;
}
else
{
lean_inc(v_a_841_);
lean_dec(v___x_840_);
v___x_843_ = lean_box(0);
v_isShared_844_ = v_isSharedCheck_850_;
goto v_resetjp_842_;
}
v_resetjp_842_:
{
lean_object* v___x_845_; lean_object* v___x_846_; lean_object* v___x_848_; 
v___x_845_ = lean_obj_once(&lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__122, &lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__122_once, _init_lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__122);
v___x_846_ = lean_string_append(v___x_845_, v_a_841_);
lean_dec(v_a_841_);
if (v_isShared_844_ == 0)
{
lean_ctor_set(v___x_843_, 0, v___x_846_);
v___x_848_ = v___x_843_;
goto v_reusejp_847_;
}
else
{
lean_object* v_reuseFailAlloc_849_; 
v_reuseFailAlloc_849_ = lean_alloc_ctor(0, 1, 0);
lean_ctor_set(v_reuseFailAlloc_849_, 0, v___x_846_);
v___x_848_ = v_reuseFailAlloc_849_;
goto v_reusejp_847_;
}
v_reusejp_847_:
{
return v___x_848_;
}
}
}
else
{
if (lean_obj_tag(v___x_840_) == 0)
{
lean_object* v_a_851_; lean_object* v___x_853_; uint8_t v_isShared_854_; uint8_t v_isSharedCheck_858_; 
lean_dec(v_a_838_);
lean_dec(v_a_817_);
lean_dec(v_a_796_);
lean_dec(v_a_775_);
lean_dec(v_a_754_);
lean_dec(v_a_733_);
lean_dec(v_a_712_);
lean_dec(v_a_691_);
lean_dec(v_a_670_);
lean_dec(v_a_649_);
lean_dec(v_a_628_);
lean_dec(v_a_607_);
lean_dec(v_a_586_);
lean_dec(v_a_565_);
lean_dec(v_a_544_);
lean_dec(v_a_523_);
lean_dec(v_a_502_);
lean_dec(v_a_481_);
lean_dec(v_a_460_);
lean_dec(v_a_439_);
lean_dec(v_a_418_);
lean_dec(v_a_397_);
lean_dec(v_json_376_);
v_a_851_ = lean_ctor_get(v___x_840_, 0);
v_isSharedCheck_858_ = !lean_is_exclusive(v___x_840_);
if (v_isSharedCheck_858_ == 0)
{
v___x_853_ = v___x_840_;
v_isShared_854_ = v_isSharedCheck_858_;
goto v_resetjp_852_;
}
else
{
lean_inc(v_a_851_);
lean_dec(v___x_840_);
v___x_853_ = lean_box(0);
v_isShared_854_ = v_isSharedCheck_858_;
goto v_resetjp_852_;
}
v_resetjp_852_:
{
lean_object* v___x_856_; 
if (v_isShared_854_ == 0)
{
lean_ctor_set_tag(v___x_853_, 0);
v___x_856_ = v___x_853_;
goto v_reusejp_855_;
}
else
{
lean_object* v_reuseFailAlloc_857_; 
v_reuseFailAlloc_857_ = lean_alloc_ctor(0, 1, 0);
lean_ctor_set(v_reuseFailAlloc_857_, 0, v_a_851_);
v___x_856_ = v_reuseFailAlloc_857_;
goto v_reusejp_855_;
}
v_reusejp_855_:
{
return v___x_856_;
}
}
}
else
{
lean_object* v_a_859_; lean_object* v___x_860_; lean_object* v___x_861_; 
v_a_859_ = lean_ctor_get(v___x_840_, 0);
lean_inc(v_a_859_);
lean_dec_ref_known(v___x_840_, 1);
v___x_860_ = ((lean_object*)(lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__123));
lean_inc(v_json_376_);
v___x_861_ = l_Lean_Json_getObjValAs_x3f___at___00Lean_Server_instFromJsonIlean_fromJson_spec__0(v_json_376_, v___x_860_);
if (lean_obj_tag(v___x_861_) == 0)
{
lean_object* v_a_862_; lean_object* v___x_864_; uint8_t v_isShared_865_; uint8_t v_isSharedCheck_871_; 
lean_dec(v_a_859_);
lean_dec(v_a_838_);
lean_dec(v_a_817_);
lean_dec(v_a_796_);
lean_dec(v_a_775_);
lean_dec(v_a_754_);
lean_dec(v_a_733_);
lean_dec(v_a_712_);
lean_dec(v_a_691_);
lean_dec(v_a_670_);
lean_dec(v_a_649_);
lean_dec(v_a_628_);
lean_dec(v_a_607_);
lean_dec(v_a_586_);
lean_dec(v_a_565_);
lean_dec(v_a_544_);
lean_dec(v_a_523_);
lean_dec(v_a_502_);
lean_dec(v_a_481_);
lean_dec(v_a_460_);
lean_dec(v_a_439_);
lean_dec(v_a_418_);
lean_dec(v_a_397_);
lean_dec(v_json_376_);
v_a_862_ = lean_ctor_get(v___x_861_, 0);
v_isSharedCheck_871_ = !lean_is_exclusive(v___x_861_);
if (v_isSharedCheck_871_ == 0)
{
v___x_864_ = v___x_861_;
v_isShared_865_ = v_isSharedCheck_871_;
goto v_resetjp_863_;
}
else
{
lean_inc(v_a_862_);
lean_dec(v___x_861_);
v___x_864_ = lean_box(0);
v_isShared_865_ = v_isSharedCheck_871_;
goto v_resetjp_863_;
}
v_resetjp_863_:
{
lean_object* v___x_866_; lean_object* v___x_867_; lean_object* v___x_869_; 
v___x_866_ = lean_obj_once(&lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__127, &lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__127_once, _init_lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__127);
v___x_867_ = lean_string_append(v___x_866_, v_a_862_);
lean_dec(v_a_862_);
if (v_isShared_865_ == 0)
{
lean_ctor_set(v___x_864_, 0, v___x_867_);
v___x_869_ = v___x_864_;
goto v_reusejp_868_;
}
else
{
lean_object* v_reuseFailAlloc_870_; 
v_reuseFailAlloc_870_ = lean_alloc_ctor(0, 1, 0);
lean_ctor_set(v_reuseFailAlloc_870_, 0, v___x_867_);
v___x_869_ = v_reuseFailAlloc_870_;
goto v_reusejp_868_;
}
v_reusejp_868_:
{
return v___x_869_;
}
}
}
else
{
if (lean_obj_tag(v___x_861_) == 0)
{
lean_object* v_a_872_; lean_object* v___x_874_; uint8_t v_isShared_875_; uint8_t v_isSharedCheck_879_; 
lean_dec(v_a_859_);
lean_dec(v_a_838_);
lean_dec(v_a_817_);
lean_dec(v_a_796_);
lean_dec(v_a_775_);
lean_dec(v_a_754_);
lean_dec(v_a_733_);
lean_dec(v_a_712_);
lean_dec(v_a_691_);
lean_dec(v_a_670_);
lean_dec(v_a_649_);
lean_dec(v_a_628_);
lean_dec(v_a_607_);
lean_dec(v_a_586_);
lean_dec(v_a_565_);
lean_dec(v_a_544_);
lean_dec(v_a_523_);
lean_dec(v_a_502_);
lean_dec(v_a_481_);
lean_dec(v_a_460_);
lean_dec(v_a_439_);
lean_dec(v_a_418_);
lean_dec(v_a_397_);
lean_dec(v_json_376_);
v_a_872_ = lean_ctor_get(v___x_861_, 0);
v_isSharedCheck_879_ = !lean_is_exclusive(v___x_861_);
if (v_isSharedCheck_879_ == 0)
{
v___x_874_ = v___x_861_;
v_isShared_875_ = v_isSharedCheck_879_;
goto v_resetjp_873_;
}
else
{
lean_inc(v_a_872_);
lean_dec(v___x_861_);
v___x_874_ = lean_box(0);
v_isShared_875_ = v_isSharedCheck_879_;
goto v_resetjp_873_;
}
v_resetjp_873_:
{
lean_object* v___x_877_; 
if (v_isShared_875_ == 0)
{
lean_ctor_set_tag(v___x_874_, 0);
v___x_877_ = v___x_874_;
goto v_reusejp_876_;
}
else
{
lean_object* v_reuseFailAlloc_878_; 
v_reuseFailAlloc_878_ = lean_alloc_ctor(0, 1, 0);
lean_ctor_set(v_reuseFailAlloc_878_, 0, v_a_872_);
v___x_877_ = v_reuseFailAlloc_878_;
goto v_reusejp_876_;
}
v_reusejp_876_:
{
return v___x_877_;
}
}
}
else
{
lean_object* v_a_880_; lean_object* v___x_881_; lean_object* v___x_882_; 
v_a_880_ = lean_ctor_get(v___x_861_, 0);
lean_inc(v_a_880_);
lean_dec_ref_known(v___x_861_, 1);
v___x_881_ = ((lean_object*)(lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__128));
lean_inc(v_json_376_);
v___x_882_ = l_Lean_Json_getObjValAs_x3f___at___00Lean_Server_instFromJsonIlean_fromJson_spec__0(v_json_376_, v___x_881_);
if (lean_obj_tag(v___x_882_) == 0)
{
lean_object* v_a_883_; lean_object* v___x_885_; uint8_t v_isShared_886_; uint8_t v_isSharedCheck_892_; 
lean_dec(v_a_880_);
lean_dec(v_a_859_);
lean_dec(v_a_838_);
lean_dec(v_a_817_);
lean_dec(v_a_796_);
lean_dec(v_a_775_);
lean_dec(v_a_754_);
lean_dec(v_a_733_);
lean_dec(v_a_712_);
lean_dec(v_a_691_);
lean_dec(v_a_670_);
lean_dec(v_a_649_);
lean_dec(v_a_628_);
lean_dec(v_a_607_);
lean_dec(v_a_586_);
lean_dec(v_a_565_);
lean_dec(v_a_544_);
lean_dec(v_a_523_);
lean_dec(v_a_502_);
lean_dec(v_a_481_);
lean_dec(v_a_460_);
lean_dec(v_a_439_);
lean_dec(v_a_418_);
lean_dec(v_a_397_);
lean_dec(v_json_376_);
v_a_883_ = lean_ctor_get(v___x_882_, 0);
v_isSharedCheck_892_ = !lean_is_exclusive(v___x_882_);
if (v_isSharedCheck_892_ == 0)
{
v___x_885_ = v___x_882_;
v_isShared_886_ = v_isSharedCheck_892_;
goto v_resetjp_884_;
}
else
{
lean_inc(v_a_883_);
lean_dec(v___x_882_);
v___x_885_ = lean_box(0);
v_isShared_886_ = v_isSharedCheck_892_;
goto v_resetjp_884_;
}
v_resetjp_884_:
{
lean_object* v___x_887_; lean_object* v___x_888_; lean_object* v___x_890_; 
v___x_887_ = lean_obj_once(&lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__132, &lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__132_once, _init_lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__132);
v___x_888_ = lean_string_append(v___x_887_, v_a_883_);
lean_dec(v_a_883_);
if (v_isShared_886_ == 0)
{
lean_ctor_set(v___x_885_, 0, v___x_888_);
v___x_890_ = v___x_885_;
goto v_reusejp_889_;
}
else
{
lean_object* v_reuseFailAlloc_891_; 
v_reuseFailAlloc_891_ = lean_alloc_ctor(0, 1, 0);
lean_ctor_set(v_reuseFailAlloc_891_, 0, v___x_888_);
v___x_890_ = v_reuseFailAlloc_891_;
goto v_reusejp_889_;
}
v_reusejp_889_:
{
return v___x_890_;
}
}
}
else
{
if (lean_obj_tag(v___x_882_) == 0)
{
lean_object* v_a_893_; lean_object* v___x_895_; uint8_t v_isShared_896_; uint8_t v_isSharedCheck_900_; 
lean_dec(v_a_880_);
lean_dec(v_a_859_);
lean_dec(v_a_838_);
lean_dec(v_a_817_);
lean_dec(v_a_796_);
lean_dec(v_a_775_);
lean_dec(v_a_754_);
lean_dec(v_a_733_);
lean_dec(v_a_712_);
lean_dec(v_a_691_);
lean_dec(v_a_670_);
lean_dec(v_a_649_);
lean_dec(v_a_628_);
lean_dec(v_a_607_);
lean_dec(v_a_586_);
lean_dec(v_a_565_);
lean_dec(v_a_544_);
lean_dec(v_a_523_);
lean_dec(v_a_502_);
lean_dec(v_a_481_);
lean_dec(v_a_460_);
lean_dec(v_a_439_);
lean_dec(v_a_418_);
lean_dec(v_a_397_);
lean_dec(v_json_376_);
v_a_893_ = lean_ctor_get(v___x_882_, 0);
v_isSharedCheck_900_ = !lean_is_exclusive(v___x_882_);
if (v_isSharedCheck_900_ == 0)
{
v___x_895_ = v___x_882_;
v_isShared_896_ = v_isSharedCheck_900_;
goto v_resetjp_894_;
}
else
{
lean_inc(v_a_893_);
lean_dec(v___x_882_);
v___x_895_ = lean_box(0);
v_isShared_896_ = v_isSharedCheck_900_;
goto v_resetjp_894_;
}
v_resetjp_894_:
{
lean_object* v___x_898_; 
if (v_isShared_896_ == 0)
{
lean_ctor_set_tag(v___x_895_, 0);
v___x_898_ = v___x_895_;
goto v_reusejp_897_;
}
else
{
lean_object* v_reuseFailAlloc_899_; 
v_reuseFailAlloc_899_ = lean_alloc_ctor(0, 1, 0);
lean_ctor_set(v_reuseFailAlloc_899_, 0, v_a_893_);
v___x_898_ = v_reuseFailAlloc_899_;
goto v_reusejp_897_;
}
v_reusejp_897_:
{
return v___x_898_;
}
}
}
else
{
lean_object* v_a_901_; lean_object* v___x_902_; lean_object* v___x_903_; 
v_a_901_ = lean_ctor_get(v___x_882_, 0);
lean_inc(v_a_901_);
lean_dec_ref_known(v___x_882_, 1);
v___x_902_ = ((lean_object*)(lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__133));
lean_inc(v_json_376_);
v___x_903_ = l_Lean_Json_getObjValAs_x3f___at___00Lean_Server_instFromJsonIlean_fromJson_spec__0(v_json_376_, v___x_902_);
if (lean_obj_tag(v___x_903_) == 0)
{
lean_object* v_a_904_; lean_object* v___x_906_; uint8_t v_isShared_907_; uint8_t v_isSharedCheck_913_; 
lean_dec(v_a_901_);
lean_dec(v_a_880_);
lean_dec(v_a_859_);
lean_dec(v_a_838_);
lean_dec(v_a_817_);
lean_dec(v_a_796_);
lean_dec(v_a_775_);
lean_dec(v_a_754_);
lean_dec(v_a_733_);
lean_dec(v_a_712_);
lean_dec(v_a_691_);
lean_dec(v_a_670_);
lean_dec(v_a_649_);
lean_dec(v_a_628_);
lean_dec(v_a_607_);
lean_dec(v_a_586_);
lean_dec(v_a_565_);
lean_dec(v_a_544_);
lean_dec(v_a_523_);
lean_dec(v_a_502_);
lean_dec(v_a_481_);
lean_dec(v_a_460_);
lean_dec(v_a_439_);
lean_dec(v_a_418_);
lean_dec(v_a_397_);
lean_dec(v_json_376_);
v_a_904_ = lean_ctor_get(v___x_903_, 0);
v_isSharedCheck_913_ = !lean_is_exclusive(v___x_903_);
if (v_isSharedCheck_913_ == 0)
{
v___x_906_ = v___x_903_;
v_isShared_907_ = v_isSharedCheck_913_;
goto v_resetjp_905_;
}
else
{
lean_inc(v_a_904_);
lean_dec(v___x_903_);
v___x_906_ = lean_box(0);
v_isShared_907_ = v_isSharedCheck_913_;
goto v_resetjp_905_;
}
v_resetjp_905_:
{
lean_object* v___x_908_; lean_object* v___x_909_; lean_object* v___x_911_; 
v___x_908_ = lean_obj_once(&lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__137, &lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__137_once, _init_lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__137);
v___x_909_ = lean_string_append(v___x_908_, v_a_904_);
lean_dec(v_a_904_);
if (v_isShared_907_ == 0)
{
lean_ctor_set(v___x_906_, 0, v___x_909_);
v___x_911_ = v___x_906_;
goto v_reusejp_910_;
}
else
{
lean_object* v_reuseFailAlloc_912_; 
v_reuseFailAlloc_912_ = lean_alloc_ctor(0, 1, 0);
lean_ctor_set(v_reuseFailAlloc_912_, 0, v___x_909_);
v___x_911_ = v_reuseFailAlloc_912_;
goto v_reusejp_910_;
}
v_reusejp_910_:
{
return v___x_911_;
}
}
}
else
{
if (lean_obj_tag(v___x_903_) == 0)
{
lean_object* v_a_914_; lean_object* v___x_916_; uint8_t v_isShared_917_; uint8_t v_isSharedCheck_921_; 
lean_dec(v_a_901_);
lean_dec(v_a_880_);
lean_dec(v_a_859_);
lean_dec(v_a_838_);
lean_dec(v_a_817_);
lean_dec(v_a_796_);
lean_dec(v_a_775_);
lean_dec(v_a_754_);
lean_dec(v_a_733_);
lean_dec(v_a_712_);
lean_dec(v_a_691_);
lean_dec(v_a_670_);
lean_dec(v_a_649_);
lean_dec(v_a_628_);
lean_dec(v_a_607_);
lean_dec(v_a_586_);
lean_dec(v_a_565_);
lean_dec(v_a_544_);
lean_dec(v_a_523_);
lean_dec(v_a_502_);
lean_dec(v_a_481_);
lean_dec(v_a_460_);
lean_dec(v_a_439_);
lean_dec(v_a_418_);
lean_dec(v_a_397_);
lean_dec(v_json_376_);
v_a_914_ = lean_ctor_get(v___x_903_, 0);
v_isSharedCheck_921_ = !lean_is_exclusive(v___x_903_);
if (v_isSharedCheck_921_ == 0)
{
v___x_916_ = v___x_903_;
v_isShared_917_ = v_isSharedCheck_921_;
goto v_resetjp_915_;
}
else
{
lean_inc(v_a_914_);
lean_dec(v___x_903_);
v___x_916_ = lean_box(0);
v_isShared_917_ = v_isSharedCheck_921_;
goto v_resetjp_915_;
}
v_resetjp_915_:
{
lean_object* v___x_919_; 
if (v_isShared_917_ == 0)
{
lean_ctor_set_tag(v___x_916_, 0);
v___x_919_ = v___x_916_;
goto v_reusejp_918_;
}
else
{
lean_object* v_reuseFailAlloc_920_; 
v_reuseFailAlloc_920_ = lean_alloc_ctor(0, 1, 0);
lean_ctor_set(v_reuseFailAlloc_920_, 0, v_a_914_);
v___x_919_ = v_reuseFailAlloc_920_;
goto v_reusejp_918_;
}
v_reusejp_918_:
{
return v___x_919_;
}
}
}
else
{
lean_object* v_a_922_; lean_object* v___x_923_; lean_object* v___x_924_; 
v_a_922_ = lean_ctor_get(v___x_903_, 0);
lean_inc(v_a_922_);
lean_dec_ref_known(v___x_903_, 1);
v___x_923_ = ((lean_object*)(lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__138));
lean_inc(v_json_376_);
v___x_924_ = l_Lean_Json_getObjValAs_x3f___at___00Lean_Server_instFromJsonIlean_fromJson_spec__0(v_json_376_, v___x_923_);
if (lean_obj_tag(v___x_924_) == 0)
{
lean_object* v_a_925_; lean_object* v___x_927_; uint8_t v_isShared_928_; uint8_t v_isSharedCheck_934_; 
lean_dec(v_a_922_);
lean_dec(v_a_901_);
lean_dec(v_a_880_);
lean_dec(v_a_859_);
lean_dec(v_a_838_);
lean_dec(v_a_817_);
lean_dec(v_a_796_);
lean_dec(v_a_775_);
lean_dec(v_a_754_);
lean_dec(v_a_733_);
lean_dec(v_a_712_);
lean_dec(v_a_691_);
lean_dec(v_a_670_);
lean_dec(v_a_649_);
lean_dec(v_a_628_);
lean_dec(v_a_607_);
lean_dec(v_a_586_);
lean_dec(v_a_565_);
lean_dec(v_a_544_);
lean_dec(v_a_523_);
lean_dec(v_a_502_);
lean_dec(v_a_481_);
lean_dec(v_a_460_);
lean_dec(v_a_439_);
lean_dec(v_a_418_);
lean_dec(v_a_397_);
lean_dec(v_json_376_);
v_a_925_ = lean_ctor_get(v___x_924_, 0);
v_isSharedCheck_934_ = !lean_is_exclusive(v___x_924_);
if (v_isSharedCheck_934_ == 0)
{
v___x_927_ = v___x_924_;
v_isShared_928_ = v_isSharedCheck_934_;
goto v_resetjp_926_;
}
else
{
lean_inc(v_a_925_);
lean_dec(v___x_924_);
v___x_927_ = lean_box(0);
v_isShared_928_ = v_isSharedCheck_934_;
goto v_resetjp_926_;
}
v_resetjp_926_:
{
lean_object* v___x_929_; lean_object* v___x_930_; lean_object* v___x_932_; 
v___x_929_ = lean_obj_once(&lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__142, &lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__142_once, _init_lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__142);
v___x_930_ = lean_string_append(v___x_929_, v_a_925_);
lean_dec(v_a_925_);
if (v_isShared_928_ == 0)
{
lean_ctor_set(v___x_927_, 0, v___x_930_);
v___x_932_ = v___x_927_;
goto v_reusejp_931_;
}
else
{
lean_object* v_reuseFailAlloc_933_; 
v_reuseFailAlloc_933_ = lean_alloc_ctor(0, 1, 0);
lean_ctor_set(v_reuseFailAlloc_933_, 0, v___x_930_);
v___x_932_ = v_reuseFailAlloc_933_;
goto v_reusejp_931_;
}
v_reusejp_931_:
{
return v___x_932_;
}
}
}
else
{
if (lean_obj_tag(v___x_924_) == 0)
{
lean_object* v_a_935_; lean_object* v___x_937_; uint8_t v_isShared_938_; uint8_t v_isSharedCheck_942_; 
lean_dec(v_a_922_);
lean_dec(v_a_901_);
lean_dec(v_a_880_);
lean_dec(v_a_859_);
lean_dec(v_a_838_);
lean_dec(v_a_817_);
lean_dec(v_a_796_);
lean_dec(v_a_775_);
lean_dec(v_a_754_);
lean_dec(v_a_733_);
lean_dec(v_a_712_);
lean_dec(v_a_691_);
lean_dec(v_a_670_);
lean_dec(v_a_649_);
lean_dec(v_a_628_);
lean_dec(v_a_607_);
lean_dec(v_a_586_);
lean_dec(v_a_565_);
lean_dec(v_a_544_);
lean_dec(v_a_523_);
lean_dec(v_a_502_);
lean_dec(v_a_481_);
lean_dec(v_a_460_);
lean_dec(v_a_439_);
lean_dec(v_a_418_);
lean_dec(v_a_397_);
lean_dec(v_json_376_);
v_a_935_ = lean_ctor_get(v___x_924_, 0);
v_isSharedCheck_942_ = !lean_is_exclusive(v___x_924_);
if (v_isSharedCheck_942_ == 0)
{
v___x_937_ = v___x_924_;
v_isShared_938_ = v_isSharedCheck_942_;
goto v_resetjp_936_;
}
else
{
lean_inc(v_a_935_);
lean_dec(v___x_924_);
v___x_937_ = lean_box(0);
v_isShared_938_ = v_isSharedCheck_942_;
goto v_resetjp_936_;
}
v_resetjp_936_:
{
lean_object* v___x_940_; 
if (v_isShared_938_ == 0)
{
lean_ctor_set_tag(v___x_937_, 0);
v___x_940_ = v___x_937_;
goto v_reusejp_939_;
}
else
{
lean_object* v_reuseFailAlloc_941_; 
v_reuseFailAlloc_941_ = lean_alloc_ctor(0, 1, 0);
lean_ctor_set(v_reuseFailAlloc_941_, 0, v_a_935_);
v___x_940_ = v_reuseFailAlloc_941_;
goto v_reusejp_939_;
}
v_reusejp_939_:
{
return v___x_940_;
}
}
}
else
{
lean_object* v_a_943_; lean_object* v___x_944_; lean_object* v___x_945_; 
v_a_943_ = lean_ctor_get(v___x_924_, 0);
lean_inc(v_a_943_);
lean_dec_ref_known(v___x_924_, 1);
v___x_944_ = ((lean_object*)(lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__143));
lean_inc(v_json_376_);
v___x_945_ = l_Lean_Json_getObjValAs_x3f___at___00Lean_Server_instFromJsonIlean_fromJson_spec__0(v_json_376_, v___x_944_);
if (lean_obj_tag(v___x_945_) == 0)
{
lean_object* v_a_946_; lean_object* v___x_948_; uint8_t v_isShared_949_; uint8_t v_isSharedCheck_955_; 
lean_dec(v_a_943_);
lean_dec(v_a_922_);
lean_dec(v_a_901_);
lean_dec(v_a_880_);
lean_dec(v_a_859_);
lean_dec(v_a_838_);
lean_dec(v_a_817_);
lean_dec(v_a_796_);
lean_dec(v_a_775_);
lean_dec(v_a_754_);
lean_dec(v_a_733_);
lean_dec(v_a_712_);
lean_dec(v_a_691_);
lean_dec(v_a_670_);
lean_dec(v_a_649_);
lean_dec(v_a_628_);
lean_dec(v_a_607_);
lean_dec(v_a_586_);
lean_dec(v_a_565_);
lean_dec(v_a_544_);
lean_dec(v_a_523_);
lean_dec(v_a_502_);
lean_dec(v_a_481_);
lean_dec(v_a_460_);
lean_dec(v_a_439_);
lean_dec(v_a_418_);
lean_dec(v_a_397_);
lean_dec(v_json_376_);
v_a_946_ = lean_ctor_get(v___x_945_, 0);
v_isSharedCheck_955_ = !lean_is_exclusive(v___x_945_);
if (v_isSharedCheck_955_ == 0)
{
v___x_948_ = v___x_945_;
v_isShared_949_ = v_isSharedCheck_955_;
goto v_resetjp_947_;
}
else
{
lean_inc(v_a_946_);
lean_dec(v___x_945_);
v___x_948_ = lean_box(0);
v_isShared_949_ = v_isSharedCheck_955_;
goto v_resetjp_947_;
}
v_resetjp_947_:
{
lean_object* v___x_950_; lean_object* v___x_951_; lean_object* v___x_953_; 
v___x_950_ = lean_obj_once(&lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__147, &lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__147_once, _init_lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__147);
v___x_951_ = lean_string_append(v___x_950_, v_a_946_);
lean_dec(v_a_946_);
if (v_isShared_949_ == 0)
{
lean_ctor_set(v___x_948_, 0, v___x_951_);
v___x_953_ = v___x_948_;
goto v_reusejp_952_;
}
else
{
lean_object* v_reuseFailAlloc_954_; 
v_reuseFailAlloc_954_ = lean_alloc_ctor(0, 1, 0);
lean_ctor_set(v_reuseFailAlloc_954_, 0, v___x_951_);
v___x_953_ = v_reuseFailAlloc_954_;
goto v_reusejp_952_;
}
v_reusejp_952_:
{
return v___x_953_;
}
}
}
else
{
if (lean_obj_tag(v___x_945_) == 0)
{
lean_object* v_a_956_; lean_object* v___x_958_; uint8_t v_isShared_959_; uint8_t v_isSharedCheck_963_; 
lean_dec(v_a_943_);
lean_dec(v_a_922_);
lean_dec(v_a_901_);
lean_dec(v_a_880_);
lean_dec(v_a_859_);
lean_dec(v_a_838_);
lean_dec(v_a_817_);
lean_dec(v_a_796_);
lean_dec(v_a_775_);
lean_dec(v_a_754_);
lean_dec(v_a_733_);
lean_dec(v_a_712_);
lean_dec(v_a_691_);
lean_dec(v_a_670_);
lean_dec(v_a_649_);
lean_dec(v_a_628_);
lean_dec(v_a_607_);
lean_dec(v_a_586_);
lean_dec(v_a_565_);
lean_dec(v_a_544_);
lean_dec(v_a_523_);
lean_dec(v_a_502_);
lean_dec(v_a_481_);
lean_dec(v_a_460_);
lean_dec(v_a_439_);
lean_dec(v_a_418_);
lean_dec(v_a_397_);
lean_dec(v_json_376_);
v_a_956_ = lean_ctor_get(v___x_945_, 0);
v_isSharedCheck_963_ = !lean_is_exclusive(v___x_945_);
if (v_isSharedCheck_963_ == 0)
{
v___x_958_ = v___x_945_;
v_isShared_959_ = v_isSharedCheck_963_;
goto v_resetjp_957_;
}
else
{
lean_inc(v_a_956_);
lean_dec(v___x_945_);
v___x_958_ = lean_box(0);
v_isShared_959_ = v_isSharedCheck_963_;
goto v_resetjp_957_;
}
v_resetjp_957_:
{
lean_object* v___x_961_; 
if (v_isShared_959_ == 0)
{
lean_ctor_set_tag(v___x_958_, 0);
v___x_961_ = v___x_958_;
goto v_reusejp_960_;
}
else
{
lean_object* v_reuseFailAlloc_962_; 
v_reuseFailAlloc_962_ = lean_alloc_ctor(0, 1, 0);
lean_ctor_set(v_reuseFailAlloc_962_, 0, v_a_956_);
v___x_961_ = v_reuseFailAlloc_962_;
goto v_reusejp_960_;
}
v_reusejp_960_:
{
return v___x_961_;
}
}
}
else
{
lean_object* v_a_964_; lean_object* v___x_965_; lean_object* v___x_966_; 
v_a_964_ = lean_ctor_get(v___x_945_, 0);
lean_inc(v_a_964_);
lean_dec_ref_known(v___x_945_, 1);
v___x_965_ = ((lean_object*)(lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__148));
lean_inc(v_json_376_);
v___x_966_ = l_Lean_Json_getObjValAs_x3f___at___00Lean_Server_instFromJsonIlean_fromJson_spec__0(v_json_376_, v___x_965_);
if (lean_obj_tag(v___x_966_) == 0)
{
lean_object* v_a_967_; lean_object* v___x_969_; uint8_t v_isShared_970_; uint8_t v_isSharedCheck_976_; 
lean_dec(v_a_964_);
lean_dec(v_a_943_);
lean_dec(v_a_922_);
lean_dec(v_a_901_);
lean_dec(v_a_880_);
lean_dec(v_a_859_);
lean_dec(v_a_838_);
lean_dec(v_a_817_);
lean_dec(v_a_796_);
lean_dec(v_a_775_);
lean_dec(v_a_754_);
lean_dec(v_a_733_);
lean_dec(v_a_712_);
lean_dec(v_a_691_);
lean_dec(v_a_670_);
lean_dec(v_a_649_);
lean_dec(v_a_628_);
lean_dec(v_a_607_);
lean_dec(v_a_586_);
lean_dec(v_a_565_);
lean_dec(v_a_544_);
lean_dec(v_a_523_);
lean_dec(v_a_502_);
lean_dec(v_a_481_);
lean_dec(v_a_460_);
lean_dec(v_a_439_);
lean_dec(v_a_418_);
lean_dec(v_a_397_);
lean_dec(v_json_376_);
v_a_967_ = lean_ctor_get(v___x_966_, 0);
v_isSharedCheck_976_ = !lean_is_exclusive(v___x_966_);
if (v_isSharedCheck_976_ == 0)
{
v___x_969_ = v___x_966_;
v_isShared_970_ = v_isSharedCheck_976_;
goto v_resetjp_968_;
}
else
{
lean_inc(v_a_967_);
lean_dec(v___x_966_);
v___x_969_ = lean_box(0);
v_isShared_970_ = v_isSharedCheck_976_;
goto v_resetjp_968_;
}
v_resetjp_968_:
{
lean_object* v___x_971_; lean_object* v___x_972_; lean_object* v___x_974_; 
v___x_971_ = lean_obj_once(&lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__152, &lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__152_once, _init_lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__152);
v___x_972_ = lean_string_append(v___x_971_, v_a_967_);
lean_dec(v_a_967_);
if (v_isShared_970_ == 0)
{
lean_ctor_set(v___x_969_, 0, v___x_972_);
v___x_974_ = v___x_969_;
goto v_reusejp_973_;
}
else
{
lean_object* v_reuseFailAlloc_975_; 
v_reuseFailAlloc_975_ = lean_alloc_ctor(0, 1, 0);
lean_ctor_set(v_reuseFailAlloc_975_, 0, v___x_972_);
v___x_974_ = v_reuseFailAlloc_975_;
goto v_reusejp_973_;
}
v_reusejp_973_:
{
return v___x_974_;
}
}
}
else
{
if (lean_obj_tag(v___x_966_) == 0)
{
lean_object* v_a_977_; lean_object* v___x_979_; uint8_t v_isShared_980_; uint8_t v_isSharedCheck_984_; 
lean_dec(v_a_964_);
lean_dec(v_a_943_);
lean_dec(v_a_922_);
lean_dec(v_a_901_);
lean_dec(v_a_880_);
lean_dec(v_a_859_);
lean_dec(v_a_838_);
lean_dec(v_a_817_);
lean_dec(v_a_796_);
lean_dec(v_a_775_);
lean_dec(v_a_754_);
lean_dec(v_a_733_);
lean_dec(v_a_712_);
lean_dec(v_a_691_);
lean_dec(v_a_670_);
lean_dec(v_a_649_);
lean_dec(v_a_628_);
lean_dec(v_a_607_);
lean_dec(v_a_586_);
lean_dec(v_a_565_);
lean_dec(v_a_544_);
lean_dec(v_a_523_);
lean_dec(v_a_502_);
lean_dec(v_a_481_);
lean_dec(v_a_460_);
lean_dec(v_a_439_);
lean_dec(v_a_418_);
lean_dec(v_a_397_);
lean_dec(v_json_376_);
v_a_977_ = lean_ctor_get(v___x_966_, 0);
v_isSharedCheck_984_ = !lean_is_exclusive(v___x_966_);
if (v_isSharedCheck_984_ == 0)
{
v___x_979_ = v___x_966_;
v_isShared_980_ = v_isSharedCheck_984_;
goto v_resetjp_978_;
}
else
{
lean_inc(v_a_977_);
lean_dec(v___x_966_);
v___x_979_ = lean_box(0);
v_isShared_980_ = v_isSharedCheck_984_;
goto v_resetjp_978_;
}
v_resetjp_978_:
{
lean_object* v___x_982_; 
if (v_isShared_980_ == 0)
{
lean_ctor_set_tag(v___x_979_, 0);
v___x_982_ = v___x_979_;
goto v_reusejp_981_;
}
else
{
lean_object* v_reuseFailAlloc_983_; 
v_reuseFailAlloc_983_ = lean_alloc_ctor(0, 1, 0);
lean_ctor_set(v_reuseFailAlloc_983_, 0, v_a_977_);
v___x_982_ = v_reuseFailAlloc_983_;
goto v_reusejp_981_;
}
v_reusejp_981_:
{
return v___x_982_;
}
}
}
else
{
lean_object* v_a_985_; lean_object* v___x_986_; lean_object* v___x_987_; 
v_a_985_ = lean_ctor_get(v___x_966_, 0);
lean_inc(v_a_985_);
lean_dec_ref_known(v___x_966_, 1);
v___x_986_ = ((lean_object*)(lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__153));
v___x_987_ = l_Lean_Json_getObjValAs_x3f___at___00Lean_Server_instFromJsonIlean_fromJson_spec__0(v_json_376_, v___x_986_);
if (lean_obj_tag(v___x_987_) == 0)
{
lean_object* v_a_988_; lean_object* v___x_990_; uint8_t v_isShared_991_; uint8_t v_isSharedCheck_997_; 
lean_dec(v_a_985_);
lean_dec(v_a_964_);
lean_dec(v_a_943_);
lean_dec(v_a_922_);
lean_dec(v_a_901_);
lean_dec(v_a_880_);
lean_dec(v_a_859_);
lean_dec(v_a_838_);
lean_dec(v_a_817_);
lean_dec(v_a_796_);
lean_dec(v_a_775_);
lean_dec(v_a_754_);
lean_dec(v_a_733_);
lean_dec(v_a_712_);
lean_dec(v_a_691_);
lean_dec(v_a_670_);
lean_dec(v_a_649_);
lean_dec(v_a_628_);
lean_dec(v_a_607_);
lean_dec(v_a_586_);
lean_dec(v_a_565_);
lean_dec(v_a_544_);
lean_dec(v_a_523_);
lean_dec(v_a_502_);
lean_dec(v_a_481_);
lean_dec(v_a_460_);
lean_dec(v_a_439_);
lean_dec(v_a_418_);
lean_dec(v_a_397_);
v_a_988_ = lean_ctor_get(v___x_987_, 0);
v_isSharedCheck_997_ = !lean_is_exclusive(v___x_987_);
if (v_isSharedCheck_997_ == 0)
{
v___x_990_ = v___x_987_;
v_isShared_991_ = v_isSharedCheck_997_;
goto v_resetjp_989_;
}
else
{
lean_inc(v_a_988_);
lean_dec(v___x_987_);
v___x_990_ = lean_box(0);
v_isShared_991_ = v_isSharedCheck_997_;
goto v_resetjp_989_;
}
v_resetjp_989_:
{
lean_object* v___x_992_; lean_object* v___x_993_; lean_object* v___x_995_; 
v___x_992_ = lean_obj_once(&lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__157, &lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__157_once, _init_lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__157);
v___x_993_ = lean_string_append(v___x_992_, v_a_988_);
lean_dec(v_a_988_);
if (v_isShared_991_ == 0)
{
lean_ctor_set(v___x_990_, 0, v___x_993_);
v___x_995_ = v___x_990_;
goto v_reusejp_994_;
}
else
{
lean_object* v_reuseFailAlloc_996_; 
v_reuseFailAlloc_996_ = lean_alloc_ctor(0, 1, 0);
lean_ctor_set(v_reuseFailAlloc_996_, 0, v___x_993_);
v___x_995_ = v_reuseFailAlloc_996_;
goto v_reusejp_994_;
}
v_reusejp_994_:
{
return v___x_995_;
}
}
}
else
{
if (lean_obj_tag(v___x_987_) == 0)
{
lean_object* v_a_998_; lean_object* v___x_1000_; uint8_t v_isShared_1001_; uint8_t v_isSharedCheck_1005_; 
lean_dec(v_a_985_);
lean_dec(v_a_964_);
lean_dec(v_a_943_);
lean_dec(v_a_922_);
lean_dec(v_a_901_);
lean_dec(v_a_880_);
lean_dec(v_a_859_);
lean_dec(v_a_838_);
lean_dec(v_a_817_);
lean_dec(v_a_796_);
lean_dec(v_a_775_);
lean_dec(v_a_754_);
lean_dec(v_a_733_);
lean_dec(v_a_712_);
lean_dec(v_a_691_);
lean_dec(v_a_670_);
lean_dec(v_a_649_);
lean_dec(v_a_628_);
lean_dec(v_a_607_);
lean_dec(v_a_586_);
lean_dec(v_a_565_);
lean_dec(v_a_544_);
lean_dec(v_a_523_);
lean_dec(v_a_502_);
lean_dec(v_a_481_);
lean_dec(v_a_460_);
lean_dec(v_a_439_);
lean_dec(v_a_418_);
lean_dec(v_a_397_);
v_a_998_ = lean_ctor_get(v___x_987_, 0);
v_isSharedCheck_1005_ = !lean_is_exclusive(v___x_987_);
if (v_isSharedCheck_1005_ == 0)
{
v___x_1000_ = v___x_987_;
v_isShared_1001_ = v_isSharedCheck_1005_;
goto v_resetjp_999_;
}
else
{
lean_inc(v_a_998_);
lean_dec(v___x_987_);
v___x_1000_ = lean_box(0);
v_isShared_1001_ = v_isSharedCheck_1005_;
goto v_resetjp_999_;
}
v_resetjp_999_:
{
lean_object* v___x_1003_; 
if (v_isShared_1001_ == 0)
{
lean_ctor_set_tag(v___x_1000_, 0);
v___x_1003_ = v___x_1000_;
goto v_reusejp_1002_;
}
else
{
lean_object* v_reuseFailAlloc_1004_; 
v_reuseFailAlloc_1004_ = lean_alloc_ctor(0, 1, 0);
lean_ctor_set(v_reuseFailAlloc_1004_, 0, v_a_998_);
v___x_1003_ = v_reuseFailAlloc_1004_;
goto v_reusejp_1002_;
}
v_reusejp_1002_:
{
return v___x_1003_;
}
}
}
else
{
lean_object* v_a_1006_; lean_object* v___x_1008_; uint8_t v_isShared_1009_; uint8_t v_isSharedCheck_1015_; 
v_a_1006_ = lean_ctor_get(v___x_987_, 0);
v_isSharedCheck_1015_ = !lean_is_exclusive(v___x_987_);
if (v_isSharedCheck_1015_ == 0)
{
v___x_1008_ = v___x_987_;
v_isShared_1009_ = v_isSharedCheck_1015_;
goto v_resetjp_1007_;
}
else
{
lean_inc(v_a_1006_);
lean_dec(v___x_987_);
v___x_1008_ = lean_box(0);
v_isShared_1009_ = v_isSharedCheck_1015_;
goto v_resetjp_1007_;
}
v_resetjp_1007_:
{
lean_object* v___x_1010_; uint8_t v___x_1011_; lean_object* v___x_1013_; 
v___x_1010_ = lean_alloc_ctor(0, 29, 1);
lean_ctor_set(v___x_1010_, 0, v_a_397_);
lean_ctor_set(v___x_1010_, 1, v_a_418_);
lean_ctor_set(v___x_1010_, 2, v_a_460_);
lean_ctor_set(v___x_1010_, 3, v_a_481_);
lean_ctor_set(v___x_1010_, 4, v_a_502_);
lean_ctor_set(v___x_1010_, 5, v_a_523_);
lean_ctor_set(v___x_1010_, 6, v_a_544_);
lean_ctor_set(v___x_1010_, 7, v_a_565_);
lean_ctor_set(v___x_1010_, 8, v_a_586_);
lean_ctor_set(v___x_1010_, 9, v_a_607_);
lean_ctor_set(v___x_1010_, 10, v_a_628_);
lean_ctor_set(v___x_1010_, 11, v_a_649_);
lean_ctor_set(v___x_1010_, 12, v_a_670_);
lean_ctor_set(v___x_1010_, 13, v_a_691_);
lean_ctor_set(v___x_1010_, 14, v_a_712_);
lean_ctor_set(v___x_1010_, 15, v_a_733_);
lean_ctor_set(v___x_1010_, 16, v_a_754_);
lean_ctor_set(v___x_1010_, 17, v_a_775_);
lean_ctor_set(v___x_1010_, 18, v_a_796_);
lean_ctor_set(v___x_1010_, 19, v_a_817_);
lean_ctor_set(v___x_1010_, 20, v_a_838_);
lean_ctor_set(v___x_1010_, 21, v_a_859_);
lean_ctor_set(v___x_1010_, 22, v_a_880_);
lean_ctor_set(v___x_1010_, 23, v_a_901_);
lean_ctor_set(v___x_1010_, 24, v_a_922_);
lean_ctor_set(v___x_1010_, 25, v_a_943_);
lean_ctor_set(v___x_1010_, 26, v_a_964_);
lean_ctor_set(v___x_1010_, 27, v_a_985_);
lean_ctor_set(v___x_1010_, 28, v_a_1006_);
v___x_1011_ = lean_unbox(v_a_439_);
lean_dec(v_a_439_);
lean_ctor_set_uint8(v___x_1010_, sizeof(void*)*29, v___x_1011_);
if (v_isShared_1009_ == 0)
{
lean_ctor_set(v___x_1008_, 0, v___x_1010_);
v___x_1013_ = v___x_1008_;
goto v_reusejp_1012_;
}
else
{
lean_object* v_reuseFailAlloc_1014_; 
v_reuseFailAlloc_1014_ = lean_alloc_ctor(1, 1, 0);
lean_ctor_set(v_reuseFailAlloc_1014_, 0, v___x_1010_);
v___x_1013_ = v_reuseFailAlloc_1014_;
goto v_reusejp_1012_;
}
v_reusejp_1012_:
{
return v___x_1013_;
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
}
}
}
}
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_mapMUnsafe_map___at___00Lean_Array_fromJson_x3f___at___00Lean_Json_getObjValAs_x3f___at___00Bench_Suite_instFromJsonPlan_fromJson_spec__0_spec__0_spec__1(size_t v_sz_1018_, size_t v_i_1019_, lean_object* v_bs_1020_){
_start:
{
uint8_t v___x_1021_; 
v___x_1021_ = lean_usize_dec_lt(v_i_1019_, v_sz_1018_);
if (v___x_1021_ == 0)
{
lean_object* v___x_1022_; 
v___x_1022_ = lean_alloc_ctor(1, 1, 0);
lean_ctor_set(v___x_1022_, 0, v_bs_1020_);
return v___x_1022_;
}
else
{
lean_object* v_v_1023_; lean_object* v___x_1024_; 
v_v_1023_ = lean_array_uget_borrowed(v_bs_1020_, v_i_1019_);
lean_inc(v_v_1023_);
v___x_1024_ = lp_competition_Bench_Suite_instFromJsonCase_fromJson(v_v_1023_);
if (lean_obj_tag(v___x_1024_) == 0)
{
lean_object* v_a_1025_; lean_object* v___x_1027_; uint8_t v_isShared_1028_; uint8_t v_isSharedCheck_1032_; 
lean_dec_ref(v_bs_1020_);
v_a_1025_ = lean_ctor_get(v___x_1024_, 0);
v_isSharedCheck_1032_ = !lean_is_exclusive(v___x_1024_);
if (v_isSharedCheck_1032_ == 0)
{
v___x_1027_ = v___x_1024_;
v_isShared_1028_ = v_isSharedCheck_1032_;
goto v_resetjp_1026_;
}
else
{
lean_inc(v_a_1025_);
lean_dec(v___x_1024_);
v___x_1027_ = lean_box(0);
v_isShared_1028_ = v_isSharedCheck_1032_;
goto v_resetjp_1026_;
}
v_resetjp_1026_:
{
lean_object* v___x_1030_; 
if (v_isShared_1028_ == 0)
{
v___x_1030_ = v___x_1027_;
goto v_reusejp_1029_;
}
else
{
lean_object* v_reuseFailAlloc_1031_; 
v_reuseFailAlloc_1031_ = lean_alloc_ctor(0, 1, 0);
lean_ctor_set(v_reuseFailAlloc_1031_, 0, v_a_1025_);
v___x_1030_ = v_reuseFailAlloc_1031_;
goto v_reusejp_1029_;
}
v_reusejp_1029_:
{
return v___x_1030_;
}
}
}
else
{
lean_object* v_a_1033_; lean_object* v___x_1034_; lean_object* v_bs_x27_1035_; size_t v___x_1036_; size_t v___x_1037_; lean_object* v___x_1038_; 
v_a_1033_ = lean_ctor_get(v___x_1024_, 0);
lean_inc(v_a_1033_);
lean_dec_ref_known(v___x_1024_, 1);
v___x_1034_ = lean_unsigned_to_nat(0u);
v_bs_x27_1035_ = lean_array_uset(v_bs_1020_, v_i_1019_, v___x_1034_);
v___x_1036_ = ((size_t)1ULL);
v___x_1037_ = lean_usize_add(v_i_1019_, v___x_1036_);
v___x_1038_ = lean_array_uset(v_bs_x27_1035_, v_i_1019_, v_a_1033_);
v_i_1019_ = v___x_1037_;
v_bs_1020_ = v___x_1038_;
goto _start;
}
}
}
}
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_mapMUnsafe_map___at___00Lean_Array_fromJson_x3f___at___00Lean_Json_getObjValAs_x3f___at___00Bench_Suite_instFromJsonPlan_fromJson_spec__0_spec__0_spec__1___boxed(lean_object* v_sz_1040_, lean_object* v_i_1041_, lean_object* v_bs_1042_){
_start:
{
size_t v_sz_boxed_1043_; size_t v_i_boxed_1044_; lean_object* v_res_1045_; 
v_sz_boxed_1043_ = lean_unbox_usize(v_sz_1040_);
lean_dec(v_sz_1040_);
v_i_boxed_1044_ = lean_unbox_usize(v_i_1041_);
lean_dec(v_i_1041_);
v_res_1045_ = lp_competition___private_Init_Data_Array_Basic_0__Array_mapMUnsafe_map___at___00Lean_Array_fromJson_x3f___at___00Lean_Json_getObjValAs_x3f___at___00Bench_Suite_instFromJsonPlan_fromJson_spec__0_spec__0_spec__1(v_sz_boxed_1043_, v_i_boxed_1044_, v_bs_1042_);
return v_res_1045_;
}
}
LEAN_EXPORT lean_object* lp_competition_Lean_Array_fromJson_x3f___at___00Lean_Json_getObjValAs_x3f___at___00Bench_Suite_instFromJsonPlan_fromJson_spec__0_spec__0(lean_object* v_x_1048_){
_start:
{
if (lean_obj_tag(v_x_1048_) == 4)
{
lean_object* v_elems_1049_; size_t v_sz_1050_; size_t v___x_1051_; lean_object* v___x_1052_; 
v_elems_1049_ = lean_ctor_get(v_x_1048_, 0);
lean_inc_ref(v_elems_1049_);
lean_dec_ref_known(v_x_1048_, 1);
v_sz_1050_ = lean_array_size(v_elems_1049_);
v___x_1051_ = ((size_t)0ULL);
v___x_1052_ = lp_competition___private_Init_Data_Array_Basic_0__Array_mapMUnsafe_map___at___00Lean_Array_fromJson_x3f___at___00Lean_Json_getObjValAs_x3f___at___00Bench_Suite_instFromJsonPlan_fromJson_spec__0_spec__0_spec__1(v_sz_1050_, v___x_1051_, v_elems_1049_);
return v___x_1052_;
}
else
{
lean_object* v___x_1053_; lean_object* v___x_1054_; lean_object* v___x_1055_; lean_object* v___x_1056_; lean_object* v___x_1057_; lean_object* v___x_1058_; lean_object* v___x_1059_; 
v___x_1053_ = ((lean_object*)(lp_competition_Lean_Array_fromJson_x3f___at___00Lean_Json_getObjValAs_x3f___at___00Bench_Suite_instFromJsonPlan_fromJson_spec__0_spec__0___closed__0));
v___x_1054_ = lean_unsigned_to_nat(80u);
v___x_1055_ = l_Lean_Json_pretty(v_x_1048_, v___x_1054_);
v___x_1056_ = lean_string_append(v___x_1053_, v___x_1055_);
lean_dec_ref(v___x_1055_);
v___x_1057_ = ((lean_object*)(lp_competition_Lean_Array_fromJson_x3f___at___00Lean_Json_getObjValAs_x3f___at___00Bench_Suite_instFromJsonPlan_fromJson_spec__0_spec__0___closed__1));
v___x_1058_ = lean_string_append(v___x_1056_, v___x_1057_);
v___x_1059_ = lean_alloc_ctor(0, 1, 0);
lean_ctor_set(v___x_1059_, 0, v___x_1058_);
return v___x_1059_;
}
}
}
LEAN_EXPORT lean_object* lp_competition_Lean_Json_getObjValAs_x3f___at___00Bench_Suite_instFromJsonPlan_fromJson_spec__0(lean_object* v_j_1060_, lean_object* v_k_1061_){
_start:
{
lean_object* v___x_1062_; lean_object* v___x_1063_; 
v___x_1062_ = l_Lean_Json_getObjValD(v_j_1060_, v_k_1061_);
v___x_1063_ = lp_competition_Lean_Array_fromJson_x3f___at___00Lean_Json_getObjValAs_x3f___at___00Bench_Suite_instFromJsonPlan_fromJson_spec__0_spec__0(v___x_1062_);
return v___x_1063_;
}
}
LEAN_EXPORT lean_object* lp_competition_Lean_Json_getObjValAs_x3f___at___00Bench_Suite_instFromJsonPlan_fromJson_spec__0___boxed(lean_object* v_j_1064_, lean_object* v_k_1065_){
_start:
{
lean_object* v_res_1066_; 
v_res_1066_ = lp_competition_Lean_Json_getObjValAs_x3f___at___00Bench_Suite_instFromJsonPlan_fromJson_spec__0(v_j_1064_, v_k_1065_);
lean_dec_ref(v_k_1065_);
return v_res_1066_;
}
}
static lean_object* _init_lp_competition_Bench_Suite_instFromJsonPlan_fromJson___closed__3(void){
_start:
{
uint8_t v___x_1073_; lean_object* v___x_1074_; lean_object* v___x_1075_; 
v___x_1073_ = 1;
v___x_1074_ = ((lean_object*)(lp_competition_Bench_Suite_instFromJsonPlan_fromJson___closed__2));
v___x_1075_ = l_Lean_Name_toStringWithToken___at___00Lean_Name_toString_spec__0(v___x_1074_, v___x_1073_);
return v___x_1075_;
}
}
static lean_object* _init_lp_competition_Bench_Suite_instFromJsonPlan_fromJson___closed__4(void){
_start:
{
lean_object* v___x_1076_; lean_object* v___x_1077_; lean_object* v___x_1078_; 
v___x_1076_ = ((lean_object*)(lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__6));
v___x_1077_ = lean_obj_once(&lp_competition_Bench_Suite_instFromJsonPlan_fromJson___closed__3, &lp_competition_Bench_Suite_instFromJsonPlan_fromJson___closed__3_once, _init_lp_competition_Bench_Suite_instFromJsonPlan_fromJson___closed__3);
v___x_1078_ = lean_string_append(v___x_1077_, v___x_1076_);
return v___x_1078_;
}
}
static lean_object* _init_lp_competition_Bench_Suite_instFromJsonPlan_fromJson___closed__6(void){
_start:
{
uint8_t v___x_1081_; lean_object* v___x_1082_; lean_object* v___x_1083_; 
v___x_1081_ = 1;
v___x_1082_ = ((lean_object*)(lp_competition_Bench_Suite_instFromJsonPlan_fromJson___closed__5));
v___x_1083_ = l_Lean_Name_toStringWithToken___at___00Lean_Name_toString_spec__0(v___x_1082_, v___x_1081_);
return v___x_1083_;
}
}
static lean_object* _init_lp_competition_Bench_Suite_instFromJsonPlan_fromJson___closed__7(void){
_start:
{
lean_object* v___x_1084_; lean_object* v___x_1085_; lean_object* v___x_1086_; 
v___x_1084_ = lean_obj_once(&lp_competition_Bench_Suite_instFromJsonPlan_fromJson___closed__6, &lp_competition_Bench_Suite_instFromJsonPlan_fromJson___closed__6_once, _init_lp_competition_Bench_Suite_instFromJsonPlan_fromJson___closed__6);
v___x_1085_ = lean_obj_once(&lp_competition_Bench_Suite_instFromJsonPlan_fromJson___closed__4, &lp_competition_Bench_Suite_instFromJsonPlan_fromJson___closed__4_once, _init_lp_competition_Bench_Suite_instFromJsonPlan_fromJson___closed__4);
v___x_1086_ = lean_string_append(v___x_1085_, v___x_1084_);
return v___x_1086_;
}
}
static lean_object* _init_lp_competition_Bench_Suite_instFromJsonPlan_fromJson___closed__8(void){
_start:
{
lean_object* v___x_1087_; lean_object* v___x_1088_; lean_object* v___x_1089_; 
v___x_1087_ = ((lean_object*)(lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__11));
v___x_1088_ = lean_obj_once(&lp_competition_Bench_Suite_instFromJsonPlan_fromJson___closed__7, &lp_competition_Bench_Suite_instFromJsonPlan_fromJson___closed__7_once, _init_lp_competition_Bench_Suite_instFromJsonPlan_fromJson___closed__7);
v___x_1089_ = lean_string_append(v___x_1088_, v___x_1087_);
return v___x_1089_;
}
}
static lean_object* _init_lp_competition_Bench_Suite_instFromJsonPlan_fromJson___closed__11(void){
_start:
{
uint8_t v___x_1093_; lean_object* v___x_1094_; lean_object* v___x_1095_; 
v___x_1093_ = 1;
v___x_1094_ = ((lean_object*)(lp_competition_Bench_Suite_instFromJsonPlan_fromJson___closed__10));
v___x_1095_ = l_Lean_Name_toStringWithToken___at___00Lean_Name_toString_spec__0(v___x_1094_, v___x_1093_);
return v___x_1095_;
}
}
static lean_object* _init_lp_competition_Bench_Suite_instFromJsonPlan_fromJson___closed__12(void){
_start:
{
lean_object* v___x_1096_; lean_object* v___x_1097_; lean_object* v___x_1098_; 
v___x_1096_ = lean_obj_once(&lp_competition_Bench_Suite_instFromJsonPlan_fromJson___closed__11, &lp_competition_Bench_Suite_instFromJsonPlan_fromJson___closed__11_once, _init_lp_competition_Bench_Suite_instFromJsonPlan_fromJson___closed__11);
v___x_1097_ = lean_obj_once(&lp_competition_Bench_Suite_instFromJsonPlan_fromJson___closed__4, &lp_competition_Bench_Suite_instFromJsonPlan_fromJson___closed__4_once, _init_lp_competition_Bench_Suite_instFromJsonPlan_fromJson___closed__4);
v___x_1098_ = lean_string_append(v___x_1097_, v___x_1096_);
return v___x_1098_;
}
}
static lean_object* _init_lp_competition_Bench_Suite_instFromJsonPlan_fromJson___closed__13(void){
_start:
{
lean_object* v___x_1099_; lean_object* v___x_1100_; lean_object* v___x_1101_; 
v___x_1099_ = ((lean_object*)(lp_competition_Bench_Suite_instFromJsonCase_fromJson___closed__11));
v___x_1100_ = lean_obj_once(&lp_competition_Bench_Suite_instFromJsonPlan_fromJson___closed__12, &lp_competition_Bench_Suite_instFromJsonPlan_fromJson___closed__12_once, _init_lp_competition_Bench_Suite_instFromJsonPlan_fromJson___closed__12);
v___x_1101_ = lean_string_append(v___x_1100_, v___x_1099_);
return v___x_1101_;
}
}
LEAN_EXPORT lean_object* lp_competition_Bench_Suite_instFromJsonPlan_fromJson(lean_object* v_json_1102_){
_start:
{
lean_object* v___x_1103_; lean_object* v___x_1104_; 
v___x_1103_ = ((lean_object*)(lp_competition_Bench_Suite_instFromJsonPlan_fromJson___closed__0));
lean_inc(v_json_1102_);
v___x_1104_ = lp_proofwidgets_Lean_Json_getObjValAs_x3f___at___00ProofWidgets_MarkdownDisplay_instFromJsonProps_fromJson_spec__0(v_json_1102_, v___x_1103_);
if (lean_obj_tag(v___x_1104_) == 0)
{
lean_object* v_a_1105_; lean_object* v___x_1107_; uint8_t v_isShared_1108_; uint8_t v_isSharedCheck_1114_; 
lean_dec(v_json_1102_);
v_a_1105_ = lean_ctor_get(v___x_1104_, 0);
v_isSharedCheck_1114_ = !lean_is_exclusive(v___x_1104_);
if (v_isSharedCheck_1114_ == 0)
{
v___x_1107_ = v___x_1104_;
v_isShared_1108_ = v_isSharedCheck_1114_;
goto v_resetjp_1106_;
}
else
{
lean_inc(v_a_1105_);
lean_dec(v___x_1104_);
v___x_1107_ = lean_box(0);
v_isShared_1108_ = v_isSharedCheck_1114_;
goto v_resetjp_1106_;
}
v_resetjp_1106_:
{
lean_object* v___x_1109_; lean_object* v___x_1110_; lean_object* v___x_1112_; 
v___x_1109_ = lean_obj_once(&lp_competition_Bench_Suite_instFromJsonPlan_fromJson___closed__8, &lp_competition_Bench_Suite_instFromJsonPlan_fromJson___closed__8_once, _init_lp_competition_Bench_Suite_instFromJsonPlan_fromJson___closed__8);
v___x_1110_ = lean_string_append(v___x_1109_, v_a_1105_);
lean_dec(v_a_1105_);
if (v_isShared_1108_ == 0)
{
lean_ctor_set(v___x_1107_, 0, v___x_1110_);
v___x_1112_ = v___x_1107_;
goto v_reusejp_1111_;
}
else
{
lean_object* v_reuseFailAlloc_1113_; 
v_reuseFailAlloc_1113_ = lean_alloc_ctor(0, 1, 0);
lean_ctor_set(v_reuseFailAlloc_1113_, 0, v___x_1110_);
v___x_1112_ = v_reuseFailAlloc_1113_;
goto v_reusejp_1111_;
}
v_reusejp_1111_:
{
return v___x_1112_;
}
}
}
else
{
if (lean_obj_tag(v___x_1104_) == 0)
{
lean_object* v_a_1115_; lean_object* v___x_1117_; uint8_t v_isShared_1118_; uint8_t v_isSharedCheck_1122_; 
lean_dec(v_json_1102_);
v_a_1115_ = lean_ctor_get(v___x_1104_, 0);
v_isSharedCheck_1122_ = !lean_is_exclusive(v___x_1104_);
if (v_isSharedCheck_1122_ == 0)
{
v___x_1117_ = v___x_1104_;
v_isShared_1118_ = v_isSharedCheck_1122_;
goto v_resetjp_1116_;
}
else
{
lean_inc(v_a_1115_);
lean_dec(v___x_1104_);
v___x_1117_ = lean_box(0);
v_isShared_1118_ = v_isSharedCheck_1122_;
goto v_resetjp_1116_;
}
v_resetjp_1116_:
{
lean_object* v___x_1120_; 
if (v_isShared_1118_ == 0)
{
lean_ctor_set_tag(v___x_1117_, 0);
v___x_1120_ = v___x_1117_;
goto v_reusejp_1119_;
}
else
{
lean_object* v_reuseFailAlloc_1121_; 
v_reuseFailAlloc_1121_ = lean_alloc_ctor(0, 1, 0);
lean_ctor_set(v_reuseFailAlloc_1121_, 0, v_a_1115_);
v___x_1120_ = v_reuseFailAlloc_1121_;
goto v_reusejp_1119_;
}
v_reusejp_1119_:
{
return v___x_1120_;
}
}
}
else
{
lean_object* v_a_1123_; lean_object* v___x_1124_; lean_object* v___x_1125_; 
v_a_1123_ = lean_ctor_get(v___x_1104_, 0);
lean_inc(v_a_1123_);
lean_dec_ref_known(v___x_1104_, 1);
v___x_1124_ = ((lean_object*)(lp_competition_Bench_Suite_instFromJsonPlan_fromJson___closed__9));
v___x_1125_ = lp_competition_Lean_Json_getObjValAs_x3f___at___00Bench_Suite_instFromJsonPlan_fromJson_spec__0(v_json_1102_, v___x_1124_);
if (lean_obj_tag(v___x_1125_) == 0)
{
lean_object* v_a_1126_; lean_object* v___x_1128_; uint8_t v_isShared_1129_; uint8_t v_isSharedCheck_1135_; 
lean_dec(v_a_1123_);
v_a_1126_ = lean_ctor_get(v___x_1125_, 0);
v_isSharedCheck_1135_ = !lean_is_exclusive(v___x_1125_);
if (v_isSharedCheck_1135_ == 0)
{
v___x_1128_ = v___x_1125_;
v_isShared_1129_ = v_isSharedCheck_1135_;
goto v_resetjp_1127_;
}
else
{
lean_inc(v_a_1126_);
lean_dec(v___x_1125_);
v___x_1128_ = lean_box(0);
v_isShared_1129_ = v_isSharedCheck_1135_;
goto v_resetjp_1127_;
}
v_resetjp_1127_:
{
lean_object* v___x_1130_; lean_object* v___x_1131_; lean_object* v___x_1133_; 
v___x_1130_ = lean_obj_once(&lp_competition_Bench_Suite_instFromJsonPlan_fromJson___closed__13, &lp_competition_Bench_Suite_instFromJsonPlan_fromJson___closed__13_once, _init_lp_competition_Bench_Suite_instFromJsonPlan_fromJson___closed__13);
v___x_1131_ = lean_string_append(v___x_1130_, v_a_1126_);
lean_dec(v_a_1126_);
if (v_isShared_1129_ == 0)
{
lean_ctor_set(v___x_1128_, 0, v___x_1131_);
v___x_1133_ = v___x_1128_;
goto v_reusejp_1132_;
}
else
{
lean_object* v_reuseFailAlloc_1134_; 
v_reuseFailAlloc_1134_ = lean_alloc_ctor(0, 1, 0);
lean_ctor_set(v_reuseFailAlloc_1134_, 0, v___x_1131_);
v___x_1133_ = v_reuseFailAlloc_1134_;
goto v_reusejp_1132_;
}
v_reusejp_1132_:
{
return v___x_1133_;
}
}
}
else
{
if (lean_obj_tag(v___x_1125_) == 0)
{
lean_object* v_a_1136_; lean_object* v___x_1138_; uint8_t v_isShared_1139_; uint8_t v_isSharedCheck_1143_; 
lean_dec(v_a_1123_);
v_a_1136_ = lean_ctor_get(v___x_1125_, 0);
v_isSharedCheck_1143_ = !lean_is_exclusive(v___x_1125_);
if (v_isSharedCheck_1143_ == 0)
{
v___x_1138_ = v___x_1125_;
v_isShared_1139_ = v_isSharedCheck_1143_;
goto v_resetjp_1137_;
}
else
{
lean_inc(v_a_1136_);
lean_dec(v___x_1125_);
v___x_1138_ = lean_box(0);
v_isShared_1139_ = v_isSharedCheck_1143_;
goto v_resetjp_1137_;
}
v_resetjp_1137_:
{
lean_object* v___x_1141_; 
if (v_isShared_1139_ == 0)
{
lean_ctor_set_tag(v___x_1138_, 0);
v___x_1141_ = v___x_1138_;
goto v_reusejp_1140_;
}
else
{
lean_object* v_reuseFailAlloc_1142_; 
v_reuseFailAlloc_1142_ = lean_alloc_ctor(0, 1, 0);
lean_ctor_set(v_reuseFailAlloc_1142_, 0, v_a_1136_);
v___x_1141_ = v_reuseFailAlloc_1142_;
goto v_reusejp_1140_;
}
v_reusejp_1140_:
{
return v___x_1141_;
}
}
}
else
{
lean_object* v_a_1144_; lean_object* v___x_1146_; uint8_t v_isShared_1147_; uint8_t v_isSharedCheck_1152_; 
v_a_1144_ = lean_ctor_get(v___x_1125_, 0);
v_isSharedCheck_1152_ = !lean_is_exclusive(v___x_1125_);
if (v_isSharedCheck_1152_ == 0)
{
v___x_1146_ = v___x_1125_;
v_isShared_1147_ = v_isSharedCheck_1152_;
goto v_resetjp_1145_;
}
else
{
lean_inc(v_a_1144_);
lean_dec(v___x_1125_);
v___x_1146_ = lean_box(0);
v_isShared_1147_ = v_isSharedCheck_1152_;
goto v_resetjp_1145_;
}
v_resetjp_1145_:
{
lean_object* v___x_1148_; lean_object* v___x_1150_; 
v___x_1148_ = lean_alloc_ctor(0, 2, 0);
lean_ctor_set(v___x_1148_, 0, v_a_1123_);
lean_ctor_set(v___x_1148_, 1, v_a_1144_);
if (v_isShared_1147_ == 0)
{
lean_ctor_set(v___x_1146_, 0, v___x_1148_);
v___x_1150_ = v___x_1146_;
goto v_reusejp_1149_;
}
else
{
lean_object* v_reuseFailAlloc_1151_; 
v_reuseFailAlloc_1151_ = lean_alloc_ctor(1, 1, 0);
lean_ctor_set(v_reuseFailAlloc_1151_, 0, v___x_1148_);
v___x_1150_ = v_reuseFailAlloc_1151_;
goto v_reusejp_1149_;
}
v_reusejp_1149_:
{
return v___x_1150_;
}
}
}
}
}
}
}
}
LEAN_EXPORT uint32_t lp_competition_Bench_Suite_word(lean_object* v_seed_1155_, lean_object* v_index_1156_, lean_object* v_stream_1157_){
_start:
{
uint64_t v___x_1158_; uint64_t v___x_1159_; uint64_t v___x_1160_; uint64_t v___x_1161_; uint64_t v___x_1162_; uint64_t v___x_1163_; uint64_t v___x_1164_; uint64_t v___x_1165_; uint64_t v_z_1166_; uint64_t v___x_1167_; uint64_t v___x_1168_; uint64_t v___x_1169_; uint64_t v___x_1170_; uint64_t v_z_1171_; uint64_t v___x_1172_; uint64_t v___x_1173_; uint64_t v___x_1174_; uint64_t v___x_1175_; uint64_t v_z_1176_; uint64_t v___x_1177_; uint64_t v___x_1178_; uint64_t v___x_1179_; uint32_t v___x_1180_; 
v___x_1158_ = lean_uint64_of_nat(v_seed_1155_);
v___x_1159_ = lean_uint64_of_nat(v_index_1156_);
v___x_1160_ = 11400714819323198485ULL;
v___x_1161_ = lean_uint64_mul(v___x_1159_, v___x_1160_);
v___x_1162_ = lean_uint64_add(v___x_1158_, v___x_1161_);
v___x_1163_ = lean_uint64_of_nat(v_stream_1157_);
v___x_1164_ = 15111065706836454659ULL;
v___x_1165_ = lean_uint64_mul(v___x_1163_, v___x_1164_);
v_z_1166_ = lean_uint64_add(v___x_1162_, v___x_1165_);
v___x_1167_ = 30ULL;
v___x_1168_ = lean_uint64_shift_right(v_z_1166_, v___x_1167_);
v___x_1169_ = lean_uint64_xor(v_z_1166_, v___x_1168_);
v___x_1170_ = 13787848793156543929ULL;
v_z_1171_ = lean_uint64_mul(v___x_1169_, v___x_1170_);
v___x_1172_ = 27ULL;
v___x_1173_ = lean_uint64_shift_right(v_z_1171_, v___x_1172_);
v___x_1174_ = lean_uint64_xor(v_z_1171_, v___x_1173_);
v___x_1175_ = 10723151780598845931ULL;
v_z_1176_ = lean_uint64_mul(v___x_1174_, v___x_1175_);
v___x_1177_ = 31ULL;
v___x_1178_ = lean_uint64_shift_right(v_z_1176_, v___x_1177_);
v___x_1179_ = lean_uint64_xor(v_z_1176_, v___x_1178_);
v___x_1180_ = lean_uint64_to_uint32(v___x_1179_);
return v___x_1180_;
}
}
LEAN_EXPORT lean_object* lp_competition_Bench_Suite_word___boxed(lean_object* v_seed_1181_, lean_object* v_index_1182_, lean_object* v_stream_1183_){
_start:
{
uint32_t v_res_1184_; lean_object* v_r_1185_; 
v_res_1184_ = lp_competition_Bench_Suite_word(v_seed_1181_, v_index_1182_, v_stream_1183_);
lean_dec(v_stream_1183_);
lean_dec(v_index_1182_);
lean_dec(v_seed_1181_);
v_r_1185_ = lean_box_uint32(v_res_1184_);
return v_r_1185_;
}
}
LEAN_EXPORT uint32_t lp_competition_Bench_Suite_draw(lean_object* v_c_1186_, lean_object* v_i_1187_, lean_object* v_role_1188_, lean_object* v_k_1189_){
_start:
{
lean_object* v_seed_1190_; lean_object* v___x_1191_; lean_object* v___x_1192_; lean_object* v___x_1193_; uint64_t v___x_1194_; uint64_t v___x_1195_; uint64_t v___x_1196_; uint64_t v___x_1197_; uint64_t v___x_1198_; uint64_t v___x_1199_; uint64_t v___x_1200_; uint64_t v___x_1201_; uint64_t v_z_1202_; uint64_t v___x_1203_; uint64_t v___x_1204_; uint64_t v___x_1205_; uint64_t v___x_1206_; uint64_t v_z_1207_; uint64_t v___x_1208_; uint64_t v___x_1209_; uint64_t v___x_1210_; uint64_t v___x_1211_; uint64_t v_z_1212_; uint64_t v___x_1213_; uint64_t v___x_1214_; uint64_t v___x_1215_; uint32_t v___x_1216_; 
v_seed_1190_ = lean_ctor_get(v_c_1186_, 2);
v___x_1191_ = lean_unsigned_to_nat(16u);
v___x_1192_ = lean_nat_mul(v_role_1188_, v___x_1191_);
v___x_1193_ = lean_nat_add(v___x_1192_, v_k_1189_);
lean_dec(v___x_1192_);
v___x_1194_ = lean_uint64_of_nat(v_seed_1190_);
v___x_1195_ = lean_uint64_of_nat(v_i_1187_);
v___x_1196_ = 11400714819323198485ULL;
v___x_1197_ = lean_uint64_mul(v___x_1195_, v___x_1196_);
v___x_1198_ = lean_uint64_add(v___x_1194_, v___x_1197_);
v___x_1199_ = lean_uint64_of_nat(v___x_1193_);
lean_dec(v___x_1193_);
v___x_1200_ = 15111065706836454659ULL;
v___x_1201_ = lean_uint64_mul(v___x_1199_, v___x_1200_);
v_z_1202_ = lean_uint64_add(v___x_1198_, v___x_1201_);
v___x_1203_ = 30ULL;
v___x_1204_ = lean_uint64_shift_right(v_z_1202_, v___x_1203_);
v___x_1205_ = lean_uint64_xor(v_z_1202_, v___x_1204_);
v___x_1206_ = 13787848793156543929ULL;
v_z_1207_ = lean_uint64_mul(v___x_1205_, v___x_1206_);
v___x_1208_ = 27ULL;
v___x_1209_ = lean_uint64_shift_right(v_z_1207_, v___x_1208_);
v___x_1210_ = lean_uint64_xor(v_z_1207_, v___x_1209_);
v___x_1211_ = 10723151780598845931ULL;
v_z_1212_ = lean_uint64_mul(v___x_1210_, v___x_1211_);
v___x_1213_ = 31ULL;
v___x_1214_ = lean_uint64_shift_right(v_z_1212_, v___x_1213_);
v___x_1215_ = lean_uint64_xor(v_z_1212_, v___x_1214_);
v___x_1216_ = lean_uint64_to_uint32(v___x_1215_);
return v___x_1216_;
}
}
LEAN_EXPORT lean_object* lp_competition_Bench_Suite_draw___boxed(lean_object* v_c_1217_, lean_object* v_i_1218_, lean_object* v_role_1219_, lean_object* v_k_1220_){
_start:
{
uint32_t v_res_1221_; lean_object* v_r_1222_; 
v_res_1221_ = lp_competition_Bench_Suite_draw(v_c_1217_, v_i_1218_, v_role_1219_, v_k_1220_);
lean_dec(v_k_1220_);
lean_dec(v_role_1219_);
lean_dec(v_i_1218_);
lean_dec_ref(v_c_1217_);
v_r_1222_ = lean_box_uint32(v_res_1221_);
return v_r_1222_;
}
}
LEAN_EXPORT lean_object* lp_competition_Bench_Suite_pct(uint32_t v_w_1223_){
_start:
{
lean_object* v___x_1224_; lean_object* v___x_1225_; lean_object* v___x_1226_; 
v___x_1224_ = lean_uint32_to_nat(v_w_1223_);
v___x_1225_ = lean_unsigned_to_nat(100u);
v___x_1226_ = lean_nat_mod(v___x_1224_, v___x_1225_);
lean_dec(v___x_1224_);
return v___x_1226_;
}
}
LEAN_EXPORT lean_object* lp_competition_Bench_Suite_pct___boxed(lean_object* v_w_1227_){
_start:
{
uint32_t v_w_boxed_1228_; lean_object* v_res_1229_; 
v_w_boxed_1228_ = lean_unbox_uint32(v_w_1227_);
lean_dec(v_w_1227_);
v_res_1229_ = lp_competition_Bench_Suite_pct(v_w_boxed_1228_);
return v_res_1229_;
}
}
LEAN_EXPORT lean_object* lp_competition_Bench_Suite_perLakh(uint32_t v_w_1230_){
_start:
{
lean_object* v___x_1231_; lean_object* v___x_1232_; lean_object* v___x_1233_; 
v___x_1231_ = lean_uint32_to_nat(v_w_1230_);
v___x_1232_ = lean_unsigned_to_nat(100000u);
v___x_1233_ = lean_nat_mod(v___x_1231_, v___x_1232_);
lean_dec(v___x_1231_);
return v___x_1233_;
}
}
LEAN_EXPORT lean_object* lp_competition_Bench_Suite_perLakh___boxed(lean_object* v_w_1234_){
_start:
{
uint32_t v_w_boxed_1235_; lean_object* v_res_1236_; 
v_w_boxed_1235_ = lean_unbox_uint32(v_w_1234_);
lean_dec(v_w_1234_);
v_res_1236_ = lp_competition_Bench_Suite_perLakh(v_w_boxed_1235_);
return v_res_1236_;
}
}
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00Bench_Suite_ctz_spec__0___redArg(uint32_t v_w_1240_, lean_object* v_range_1241_, lean_object* v_b_1242_, lean_object* v_i_1243_){
_start:
{
lean_object* v_stop_1244_; lean_object* v_step_1245_; uint8_t v___x_1246_; 
v_stop_1244_ = lean_ctor_get(v_range_1241_, 1);
v_step_1245_ = lean_ctor_get(v_range_1241_, 2);
v___x_1246_ = lean_nat_dec_lt(v_i_1243_, v_stop_1244_);
if (v___x_1246_ == 0)
{
lean_dec(v_i_1243_);
lean_inc_ref(v_b_1242_);
return v_b_1242_;
}
else
{
lean_object* v___x_1247_; uint32_t v___x_1248_; uint32_t v___x_1249_; uint32_t v___x_1250_; uint32_t v___x_1251_; uint8_t v___x_1252_; 
v___x_1247_ = lean_box(0);
v___x_1248_ = lean_uint32_of_nat(v_i_1243_);
v___x_1249_ = lean_uint32_shift_right(v_w_1240_, v___x_1248_);
v___x_1250_ = 1;
v___x_1251_ = lean_uint32_land(v___x_1249_, v___x_1250_);
v___x_1252_ = lean_uint32_dec_eq(v___x_1251_, v___x_1250_);
if (v___x_1252_ == 0)
{
lean_object* v___x_1253_; lean_object* v___x_1254_; 
v___x_1253_ = ((lean_object*)(lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00Bench_Suite_ctz_spec__0___redArg___closed__0));
v___x_1254_ = lean_nat_add(v_i_1243_, v_step_1245_);
lean_dec(v_i_1243_);
v_b_1242_ = v___x_1253_;
v_i_1243_ = v___x_1254_;
goto _start;
}
else
{
lean_object* v___x_1256_; lean_object* v___x_1257_; 
v___x_1256_ = lean_alloc_ctor(1, 1, 0);
lean_ctor_set(v___x_1256_, 0, v_i_1243_);
v___x_1257_ = lean_alloc_ctor(0, 2, 0);
lean_ctor_set(v___x_1257_, 0, v___x_1256_);
lean_ctor_set(v___x_1257_, 1, v___x_1247_);
return v___x_1257_;
}
}
}
}
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00Bench_Suite_ctz_spec__0___redArg___boxed(lean_object* v_w_1258_, lean_object* v_range_1259_, lean_object* v_b_1260_, lean_object* v_i_1261_){
_start:
{
uint32_t v_w_boxed_1262_; lean_object* v_res_1263_; 
v_w_boxed_1262_ = lean_unbox_uint32(v_w_1258_);
lean_dec(v_w_1258_);
v_res_1263_ = lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00Bench_Suite_ctz_spec__0___redArg(v_w_boxed_1262_, v_range_1259_, v_b_1260_, v_i_1261_);
lean_dec_ref(v_b_1260_);
lean_dec_ref(v_range_1259_);
return v_res_1263_;
}
}
LEAN_EXPORT lean_object* lp_competition_Bench_Suite_ctz(uint32_t v_w_1268_){
_start:
{
lean_object* v___x_1269_; lean_object* v___x_1270_; lean_object* v___x_1271_; lean_object* v___x_1272_; lean_object* v___x_1273_; lean_object* v_fst_1274_; 
v___x_1269_ = lean_unsigned_to_nat(0u);
v___x_1270_ = lean_unsigned_to_nat(32u);
v___x_1271_ = ((lean_object*)(lp_competition_Bench_Suite_ctz___closed__0));
v___x_1272_ = ((lean_object*)(lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00Bench_Suite_ctz_spec__0___redArg___closed__0));
v___x_1273_ = lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00Bench_Suite_ctz_spec__0___redArg(v_w_1268_, v___x_1271_, v___x_1272_, v___x_1269_);
v_fst_1274_ = lean_ctor_get(v___x_1273_, 0);
lean_inc(v_fst_1274_);
lean_dec_ref(v___x_1273_);
if (lean_obj_tag(v_fst_1274_) == 0)
{
return v___x_1270_;
}
else
{
lean_object* v_val_1275_; 
v_val_1275_ = lean_ctor_get(v_fst_1274_, 0);
lean_inc(v_val_1275_);
lean_dec_ref_known(v_fst_1274_, 1);
return v_val_1275_;
}
}
}
LEAN_EXPORT lean_object* lp_competition_Bench_Suite_ctz___boxed(lean_object* v_w_1276_){
_start:
{
uint32_t v_w_boxed_1277_; lean_object* v_res_1278_; 
v_w_boxed_1277_ = lean_unbox_uint32(v_w_1276_);
lean_dec(v_w_1276_);
v_res_1278_ = lp_competition_Bench_Suite_ctz(v_w_boxed_1277_);
return v_res_1278_;
}
}
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00Bench_Suite_ctz_spec__0(uint32_t v_w_1279_, lean_object* v_range_1280_, lean_object* v_b_1281_, lean_object* v_i_1282_, lean_object* v_hs_1283_, lean_object* v_hl_1284_){
_start:
{
lean_object* v___x_1285_; 
v___x_1285_ = lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00Bench_Suite_ctz_spec__0___redArg(v_w_1279_, v_range_1280_, v_b_1281_, v_i_1282_);
return v___x_1285_;
}
}
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00Bench_Suite_ctz_spec__0___boxed(lean_object* v_w_1286_, lean_object* v_range_1287_, lean_object* v_b_1288_, lean_object* v_i_1289_, lean_object* v_hs_1290_, lean_object* v_hl_1291_){
_start:
{
uint32_t v_w_boxed_1292_; lean_object* v_res_1293_; 
v_w_boxed_1292_ = lean_unbox_uint32(v_w_1286_);
lean_dec(v_w_1286_);
v_res_1293_ = lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00Bench_Suite_ctz_spec__0(v_w_boxed_1292_, v_range_1287_, v_b_1288_, v_i_1289_, v_hs_1290_, v_hl_1291_);
lean_dec_ref(v_b_1288_);
lean_dec_ref(v_range_1287_);
return v_res_1293_;
}
}
static lean_object* _init_lp_competition_Bench_Suite_clampExp___closed__0(void){
_start:
{
lean_object* v___x_1294_; lean_object* v___x_1295_; 
v___x_1294_ = lean_unsigned_to_nat(1u);
v___x_1295_ = lean_nat_to_int(v___x_1294_);
return v___x_1295_;
}
}
static lean_object* _init_lp_competition_Bench_Suite_clampExp___closed__1(void){
_start:
{
lean_object* v___x_1296_; lean_object* v___x_1297_; 
v___x_1296_ = lean_unsigned_to_nat(254u);
v___x_1297_ = lean_nat_to_int(v___x_1296_);
return v___x_1297_;
}
}
LEAN_EXPORT uint32_t lp_competition_Bench_Suite_clampExp(lean_object* v_e_1298_){
_start:
{
lean_object* v___y_1300_; lean_object* v___x_1303_; lean_object* v___y_1305_; lean_object* v___x_1307_; uint8_t v___x_1308_; 
v___x_1303_ = lean_obj_once(&lp_competition_Bench_Suite_clampExp___closed__0, &lp_competition_Bench_Suite_clampExp___closed__0_once, _init_lp_competition_Bench_Suite_clampExp___closed__0);
v___x_1307_ = lean_obj_once(&lp_competition_Bench_Suite_clampExp___closed__1, &lp_competition_Bench_Suite_clampExp___closed__1_once, _init_lp_competition_Bench_Suite_clampExp___closed__1);
v___x_1308_ = lean_int_dec_le(v___x_1307_, v_e_1298_);
if (v___x_1308_ == 0)
{
v___y_1305_ = v_e_1298_;
goto v___jp_1304_;
}
else
{
v___y_1305_ = v___x_1307_;
goto v___jp_1304_;
}
v___jp_1299_:
{
lean_object* v___x_1301_; uint32_t v___x_1302_; 
v___x_1301_ = l_Int_toNat(v___y_1300_);
v___x_1302_ = lean_uint32_of_nat(v___x_1301_);
lean_dec(v___x_1301_);
return v___x_1302_;
}
v___jp_1304_:
{
uint8_t v___x_1306_; 
v___x_1306_ = lean_int_dec_le(v___x_1303_, v___y_1305_);
if (v___x_1306_ == 0)
{
v___y_1300_ = v___x_1303_;
goto v___jp_1299_;
}
else
{
v___y_1300_ = v___y_1305_;
goto v___jp_1299_;
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_Bench_Suite_clampExp___boxed(lean_object* v_e_1309_){
_start:
{
uint32_t v_res_1310_; lean_object* v_r_1311_; 
v_res_1310_ = lp_competition_Bench_Suite_clampExp(v_e_1309_);
lean_dec(v_e_1309_);
v_r_1311_ = lean_box_uint32(v_res_1310_);
return v_r_1311_;
}
}
static lean_object* _init_lp_competition_Bench_Suite_ordinary___closed__0(void){
_start:
{
lean_object* v___x_1312_; lean_object* v___x_1313_; 
v___x_1312_ = lean_unsigned_to_nat(0u);
v___x_1313_ = lean_nat_to_int(v___x_1312_);
return v___x_1313_;
}
}
LEAN_EXPORT uint32_t lp_competition_Bench_Suite_ordinary(lean_object* v_c_1314_, lean_object* v_i_1315_, lean_object* v_j_1316_, lean_object* v_role_1317_){
_start:
{
uint32_t v___y_1319_; uint32_t v___y_1320_; lean_object* v___y_1321_; lean_object* v___y_1329_; uint32_t v___y_1330_; uint32_t v___y_1331_; lean_object* v___y_1332_; lean_object* v_seed_1334_; lean_object* v_mag_1335_; lean_object* v_center_1336_; lean_object* v_spread_1337_; lean_object* v_positive_1338_; lean_object* v_mantBits_1339_; lean_object* v_scaleBlock_1340_; lean_object* v_scaleShift_1341_; lean_object* v___x_1342_; lean_object* v___y_1344_; lean_object* v___y_1345_; uint32_t v___y_1346_; uint32_t v___y_1347_; lean_object* v___y_1353_; lean_object* v___y_1354_; uint32_t v___y_1355_; lean_object* v___y_1405_; lean_object* v___y_1406_; lean_object* v___y_1418_; lean_object* v___x_1457_; lean_object* v___x_1458_; lean_object* v___x_1459_; uint64_t v___x_1460_; uint64_t v___x_1461_; uint64_t v___x_1462_; uint64_t v___x_1463_; uint64_t v___x_1464_; uint64_t v___x_1465_; uint64_t v___x_1466_; uint64_t v___x_1467_; uint64_t v_z_1468_; uint64_t v___x_1469_; uint64_t v___x_1470_; uint64_t v___x_1471_; uint64_t v___x_1472_; uint64_t v_z_1473_; uint64_t v___x_1474_; uint64_t v___x_1475_; uint64_t v___x_1476_; uint64_t v___x_1477_; uint64_t v_z_1478_; uint64_t v___x_1479_; uint64_t v___x_1480_; uint64_t v___x_1481_; uint32_t v_w_1482_; lean_object* v_centre_1483_; lean_object* v___y_1485_; uint8_t v___x_1488_; 
v_seed_1334_ = lean_ctor_get(v_c_1314_, 2);
lean_inc(v_seed_1334_);
v_mag_1335_ = lean_ctor_get(v_c_1314_, 3);
lean_inc(v_mag_1335_);
v_center_1336_ = lean_ctor_get(v_c_1314_, 4);
lean_inc(v_center_1336_);
v_spread_1337_ = lean_ctor_get(v_c_1314_, 5);
lean_inc(v_spread_1337_);
v_positive_1338_ = lean_ctor_get(v_c_1314_, 6);
lean_inc(v_positive_1338_);
v_mantBits_1339_ = lean_ctor_get(v_c_1314_, 7);
lean_inc(v_mantBits_1339_);
v_scaleBlock_1340_ = lean_ctor_get(v_c_1314_, 9);
lean_inc(v_scaleBlock_1340_);
v_scaleShift_1341_ = lean_ctor_get(v_c_1314_, 10);
lean_inc(v_scaleShift_1341_);
lean_dec_ref(v_c_1314_);
v___x_1342_ = lean_unsigned_to_nat(1u);
v___x_1457_ = lean_unsigned_to_nat(16u);
v___x_1458_ = lean_nat_mul(v_role_1317_, v___x_1457_);
v___x_1459_ = lean_nat_add(v___x_1458_, v___x_1342_);
lean_dec(v___x_1458_);
v___x_1460_ = lean_uint64_of_nat(v_seed_1334_);
v___x_1461_ = lean_uint64_of_nat(v_j_1316_);
v___x_1462_ = 11400714819323198485ULL;
v___x_1463_ = lean_uint64_mul(v___x_1461_, v___x_1462_);
v___x_1464_ = lean_uint64_add(v___x_1460_, v___x_1463_);
v___x_1465_ = lean_uint64_of_nat(v___x_1459_);
lean_dec(v___x_1459_);
v___x_1466_ = 15111065706836454659ULL;
v___x_1467_ = lean_uint64_mul(v___x_1465_, v___x_1466_);
v_z_1468_ = lean_uint64_add(v___x_1464_, v___x_1467_);
v___x_1469_ = 30ULL;
v___x_1470_ = lean_uint64_shift_right(v_z_1468_, v___x_1469_);
v___x_1471_ = lean_uint64_xor(v_z_1468_, v___x_1470_);
v___x_1472_ = 13787848793156543929ULL;
v_z_1473_ = lean_uint64_mul(v___x_1471_, v___x_1472_);
v___x_1474_ = 27ULL;
v___x_1475_ = lean_uint64_shift_right(v_z_1473_, v___x_1474_);
v___x_1476_ = lean_uint64_xor(v_z_1473_, v___x_1475_);
v___x_1477_ = 10723151780598845931ULL;
v_z_1478_ = lean_uint64_mul(v___x_1476_, v___x_1477_);
v___x_1479_ = 31ULL;
v___x_1480_ = lean_uint64_shift_right(v_z_1478_, v___x_1479_);
v___x_1481_ = lean_uint64_xor(v_z_1478_, v___x_1480_);
v_w_1482_ = lean_uint64_to_uint32(v___x_1481_);
v_centre_1483_ = lean_nat_to_int(v_center_1336_);
v___x_1488_ = lean_nat_dec_eq(v_mag_1335_, v___x_1342_);
lean_dec(v_mag_1335_);
if (v___x_1488_ == 0)
{
lean_object* v___x_1489_; lean_object* v___x_1490_; lean_object* v___x_1491_; lean_object* v___x_1492_; lean_object* v___x_1493_; lean_object* v___x_1494_; lean_object* v___x_1495_; lean_object* v___x_1496_; lean_object* v___x_1497_; 
lean_inc(v_spread_1337_);
v___x_1489_ = lean_nat_to_int(v_spread_1337_);
v___x_1490_ = lean_int_sub(v_centre_1483_, v___x_1489_);
lean_dec(v___x_1489_);
lean_dec(v_centre_1483_);
v___x_1491_ = lean_uint32_to_nat(v_w_1482_);
v___x_1492_ = lean_unsigned_to_nat(2u);
v___x_1493_ = lean_nat_mul(v___x_1492_, v_spread_1337_);
lean_dec(v_spread_1337_);
v___x_1494_ = lean_nat_add(v___x_1493_, v___x_1342_);
lean_dec(v___x_1493_);
v___x_1495_ = lean_nat_mod(v___x_1491_, v___x_1494_);
lean_dec(v___x_1494_);
lean_dec(v___x_1491_);
v___x_1496_ = lean_nat_to_int(v___x_1495_);
v___x_1497_ = lean_int_add(v___x_1490_, v___x_1496_);
lean_dec(v___x_1496_);
lean_dec(v___x_1490_);
v___y_1418_ = v___x_1497_;
goto v___jp_1417_;
}
else
{
lean_object* v___x_1498_; uint8_t v___x_1499_; 
v___x_1498_ = lp_competition_Bench_Suite_ctz(v_w_1482_);
v___x_1499_ = lean_nat_dec_le(v___x_1498_, v_spread_1337_);
if (v___x_1499_ == 0)
{
lean_dec(v___x_1498_);
v___y_1485_ = v_spread_1337_;
goto v___jp_1484_;
}
else
{
lean_dec(v_spread_1337_);
v___y_1485_ = v___x_1498_;
goto v___jp_1484_;
}
}
v___jp_1318_:
{
lean_object* v___x_1322_; uint32_t v___x_1323_; uint32_t v___x_1324_; uint32_t v___x_1325_; uint32_t v___x_1326_; uint32_t v___x_1327_; 
v___x_1322_ = l_Int_toNat(v___y_1321_);
lean_dec(v___y_1321_);
v___x_1323_ = lean_uint32_of_nat(v___x_1322_);
lean_dec(v___x_1322_);
v___x_1324_ = 23;
v___x_1325_ = lean_uint32_shift_left(v___x_1323_, v___x_1324_);
v___x_1326_ = lean_uint32_lor(v___y_1319_, v___x_1325_);
v___x_1327_ = lean_uint32_lor(v___x_1326_, v___y_1320_);
return v___x_1327_;
}
v___jp_1328_:
{
uint8_t v___x_1333_; 
v___x_1333_ = lean_int_dec_le(v___y_1329_, v___y_1332_);
if (v___x_1333_ == 0)
{
lean_dec(v___y_1332_);
lean_inc(v___y_1329_);
v___y_1319_ = v___y_1330_;
v___y_1320_ = v___y_1331_;
v___y_1321_ = v___y_1329_;
goto v___jp_1318_;
}
else
{
v___y_1319_ = v___y_1330_;
v___y_1320_ = v___y_1331_;
v___y_1321_ = v___y_1332_;
goto v___jp_1318_;
}
}
v___jp_1343_:
{
lean_object* v___x_1348_; lean_object* v___x_1349_; lean_object* v___x_1350_; uint8_t v___x_1351_; 
v___x_1348_ = lean_int_add(v___y_1344_, v___y_1345_);
lean_dec(v___y_1345_);
lean_dec(v___y_1344_);
v___x_1349_ = lean_obj_once(&lp_competition_Bench_Suite_clampExp___closed__0, &lp_competition_Bench_Suite_clampExp___closed__0_once, _init_lp_competition_Bench_Suite_clampExp___closed__0);
v___x_1350_ = lean_obj_once(&lp_competition_Bench_Suite_clampExp___closed__1, &lp_competition_Bench_Suite_clampExp___closed__1_once, _init_lp_competition_Bench_Suite_clampExp___closed__1);
v___x_1351_ = lean_int_dec_le(v___x_1350_, v___x_1348_);
if (v___x_1351_ == 0)
{
v___y_1329_ = v___x_1349_;
v___y_1330_ = v___y_1347_;
v___y_1331_ = v___y_1346_;
v___y_1332_ = v___x_1348_;
goto v___jp_1328_;
}
else
{
lean_dec(v___x_1348_);
v___y_1329_ = v___x_1349_;
v___y_1330_ = v___y_1347_;
v___y_1331_ = v___y_1346_;
v___y_1332_ = v___x_1350_;
goto v___jp_1328_;
}
}
v___jp_1352_:
{
lean_object* v___x_1356_; lean_object* v___x_1357_; lean_object* v___x_1358_; lean_object* v___x_1359_; uint64_t v___x_1360_; uint64_t v___x_1361_; uint64_t v___x_1362_; uint64_t v___x_1363_; uint64_t v___x_1364_; uint64_t v___x_1365_; uint64_t v___x_1366_; uint64_t v___x_1367_; uint64_t v_z_1368_; uint64_t v___x_1369_; uint64_t v___x_1370_; uint64_t v___x_1371_; uint64_t v___x_1372_; uint64_t v_z_1373_; uint64_t v___x_1374_; uint64_t v___x_1375_; uint64_t v___x_1376_; uint64_t v___x_1377_; uint64_t v_z_1378_; uint64_t v___x_1379_; uint64_t v___x_1380_; uint64_t v___x_1381_; uint32_t v___x_1382_; uint32_t v_frac_1383_; lean_object* v___x_1384_; lean_object* v___x_1385_; uint64_t v___x_1386_; uint64_t v___x_1387_; uint64_t v_z_1388_; uint64_t v___x_1389_; uint64_t v___x_1390_; uint64_t v_z_1391_; uint64_t v___x_1392_; uint64_t v___x_1393_; uint64_t v_z_1394_; uint64_t v___x_1395_; uint64_t v___x_1396_; uint32_t v___x_1397_; lean_object* v___x_1398_; lean_object* v___x_1399_; lean_object* v___x_1400_; uint8_t v___x_1401_; 
v___x_1356_ = lean_unsigned_to_nat(3u);
v___x_1357_ = lean_unsigned_to_nat(16u);
v___x_1358_ = lean_nat_mul(v_role_1317_, v___x_1357_);
v___x_1359_ = lean_nat_add(v___x_1358_, v___x_1356_);
v___x_1360_ = lean_uint64_of_nat(v_seed_1334_);
lean_dec(v_seed_1334_);
v___x_1361_ = lean_uint64_of_nat(v_j_1316_);
v___x_1362_ = 11400714819323198485ULL;
v___x_1363_ = lean_uint64_mul(v___x_1361_, v___x_1362_);
v___x_1364_ = lean_uint64_add(v___x_1360_, v___x_1363_);
v___x_1365_ = lean_uint64_of_nat(v___x_1359_);
lean_dec(v___x_1359_);
v___x_1366_ = 15111065706836454659ULL;
v___x_1367_ = lean_uint64_mul(v___x_1365_, v___x_1366_);
v_z_1368_ = lean_uint64_add(v___x_1364_, v___x_1367_);
v___x_1369_ = 30ULL;
v___x_1370_ = lean_uint64_shift_right(v_z_1368_, v___x_1369_);
v___x_1371_ = lean_uint64_xor(v_z_1368_, v___x_1370_);
v___x_1372_ = 13787848793156543929ULL;
v_z_1373_ = lean_uint64_mul(v___x_1371_, v___x_1372_);
v___x_1374_ = 27ULL;
v___x_1375_ = lean_uint64_shift_right(v_z_1373_, v___x_1374_);
v___x_1376_ = lean_uint64_xor(v_z_1373_, v___x_1375_);
v___x_1377_ = 10723151780598845931ULL;
v_z_1378_ = lean_uint64_mul(v___x_1376_, v___x_1377_);
v___x_1379_ = 31ULL;
v___x_1380_ = lean_uint64_shift_right(v_z_1378_, v___x_1379_);
v___x_1381_ = lean_uint64_xor(v_z_1378_, v___x_1380_);
v___x_1382_ = lean_uint64_to_uint32(v___x_1381_);
v_frac_1383_ = lean_uint32_land(v___x_1382_, v___y_1355_);
v___x_1384_ = lean_unsigned_to_nat(4u);
v___x_1385_ = lean_nat_add(v___x_1358_, v___x_1384_);
lean_dec(v___x_1358_);
v___x_1386_ = lean_uint64_of_nat(v___x_1385_);
lean_dec(v___x_1385_);
v___x_1387_ = lean_uint64_mul(v___x_1386_, v___x_1366_);
v_z_1388_ = lean_uint64_add(v___x_1364_, v___x_1387_);
v___x_1389_ = lean_uint64_shift_right(v_z_1388_, v___x_1369_);
v___x_1390_ = lean_uint64_xor(v_z_1388_, v___x_1389_);
v_z_1391_ = lean_uint64_mul(v___x_1390_, v___x_1372_);
v___x_1392_ = lean_uint64_shift_right(v_z_1391_, v___x_1374_);
v___x_1393_ = lean_uint64_xor(v_z_1391_, v___x_1392_);
v_z_1394_ = lean_uint64_mul(v___x_1393_, v___x_1377_);
v___x_1395_ = lean_uint64_shift_right(v_z_1394_, v___x_1379_);
v___x_1396_ = lean_uint64_xor(v_z_1394_, v___x_1395_);
v___x_1397_ = lean_uint64_to_uint32(v___x_1396_);
v___x_1398_ = lean_uint32_to_nat(v___x_1397_);
v___x_1399_ = lean_unsigned_to_nat(100u);
v___x_1400_ = lean_nat_mod(v___x_1398_, v___x_1399_);
lean_dec(v___x_1398_);
v___x_1401_ = lean_nat_dec_lt(v___x_1400_, v_positive_1338_);
lean_dec(v_positive_1338_);
lean_dec(v___x_1400_);
if (v___x_1401_ == 0)
{
uint32_t v___x_1402_; 
v___x_1402_ = 2147483648;
v___y_1344_ = v___y_1353_;
v___y_1345_ = v___y_1354_;
v___y_1346_ = v_frac_1383_;
v___y_1347_ = v___x_1402_;
goto v___jp_1343_;
}
else
{
uint32_t v___x_1403_; 
v___x_1403_ = 0;
v___y_1344_ = v___y_1353_;
v___y_1345_ = v___y_1354_;
v___y_1346_ = v_frac_1383_;
v___y_1347_ = v___x_1403_;
goto v___jp_1343_;
}
}
v___jp_1404_:
{
lean_object* v___x_1407_; uint8_t v___x_1408_; 
v___x_1407_ = lean_unsigned_to_nat(23u);
v___x_1408_ = lean_nat_dec_le(v___x_1407_, v_mantBits_1339_);
if (v___x_1408_ == 0)
{
uint32_t v___x_1409_; uint32_t v___x_1410_; lean_object* v___x_1411_; uint32_t v___x_1412_; uint32_t v___x_1413_; uint32_t v___x_1414_; uint32_t v___x_1415_; 
v___x_1409_ = 8388607;
v___x_1410_ = 1;
v___x_1411_ = lean_nat_sub(v___x_1407_, v_mantBits_1339_);
lean_dec(v_mantBits_1339_);
v___x_1412_ = lean_uint32_of_nat(v___x_1411_);
lean_dec(v___x_1411_);
v___x_1413_ = lean_uint32_shift_left(v___x_1410_, v___x_1412_);
v___x_1414_ = lean_uint32_sub(v___x_1413_, v___x_1410_);
v___x_1415_ = lean_uint32_xor(v___x_1409_, v___x_1414_);
v___y_1353_ = v___y_1405_;
v___y_1354_ = v___y_1406_;
v___y_1355_ = v___x_1415_;
goto v___jp_1352_;
}
else
{
uint32_t v___x_1416_; 
lean_dec(v_mantBits_1339_);
v___x_1416_ = 8388607;
v___y_1353_ = v___y_1405_;
v___y_1354_ = v___y_1406_;
v___y_1355_ = v___x_1416_;
goto v___jp_1352_;
}
}
v___jp_1417_:
{
lean_object* v___x_1419_; uint8_t v___x_1420_; 
v___x_1419_ = lean_unsigned_to_nat(0u);
v___x_1420_ = lean_nat_dec_eq(v_scaleBlock_1340_, v___x_1419_);
if (v___x_1420_ == 0)
{
lean_object* v___x_1421_; lean_object* v___x_1422_; lean_object* v___x_1423_; lean_object* v___x_1424_; lean_object* v___x_1425_; uint64_t v___x_1426_; uint64_t v___x_1427_; uint64_t v___x_1428_; uint64_t v___x_1429_; uint64_t v___x_1430_; uint64_t v___x_1431_; uint64_t v___x_1432_; uint64_t v___x_1433_; uint64_t v_z_1434_; uint64_t v___x_1435_; uint64_t v___x_1436_; uint64_t v___x_1437_; uint64_t v___x_1438_; uint64_t v_z_1439_; uint64_t v___x_1440_; uint64_t v___x_1441_; uint64_t v___x_1442_; uint64_t v___x_1443_; uint64_t v_z_1444_; uint64_t v___x_1445_; uint64_t v___x_1446_; uint64_t v___x_1447_; uint32_t v___x_1448_; lean_object* v___x_1449_; lean_object* v___x_1450_; lean_object* v___x_1451_; lean_object* v___x_1452_; lean_object* v___x_1453_; lean_object* v___x_1454_; lean_object* v___x_1455_; 
v___x_1421_ = lean_nat_div(v_i_1315_, v_scaleBlock_1340_);
lean_dec(v_scaleBlock_1340_);
v___x_1422_ = lean_unsigned_to_nat(2u);
v___x_1423_ = lean_unsigned_to_nat(16u);
v___x_1424_ = lean_nat_mul(v_role_1317_, v___x_1423_);
v___x_1425_ = lean_nat_add(v___x_1424_, v___x_1422_);
lean_dec(v___x_1424_);
v___x_1426_ = lean_uint64_of_nat(v_seed_1334_);
v___x_1427_ = lean_uint64_of_nat(v___x_1421_);
lean_dec(v___x_1421_);
v___x_1428_ = 11400714819323198485ULL;
v___x_1429_ = lean_uint64_mul(v___x_1427_, v___x_1428_);
v___x_1430_ = lean_uint64_add(v___x_1426_, v___x_1429_);
v___x_1431_ = lean_uint64_of_nat(v___x_1425_);
lean_dec(v___x_1425_);
v___x_1432_ = 15111065706836454659ULL;
v___x_1433_ = lean_uint64_mul(v___x_1431_, v___x_1432_);
v_z_1434_ = lean_uint64_add(v___x_1430_, v___x_1433_);
v___x_1435_ = 30ULL;
v___x_1436_ = lean_uint64_shift_right(v_z_1434_, v___x_1435_);
v___x_1437_ = lean_uint64_xor(v_z_1434_, v___x_1436_);
v___x_1438_ = 13787848793156543929ULL;
v_z_1439_ = lean_uint64_mul(v___x_1437_, v___x_1438_);
v___x_1440_ = 27ULL;
v___x_1441_ = lean_uint64_shift_right(v_z_1439_, v___x_1440_);
v___x_1442_ = lean_uint64_xor(v_z_1439_, v___x_1441_);
v___x_1443_ = 10723151780598845931ULL;
v_z_1444_ = lean_uint64_mul(v___x_1442_, v___x_1443_);
v___x_1445_ = 31ULL;
v___x_1446_ = lean_uint64_shift_right(v_z_1444_, v___x_1445_);
v___x_1447_ = lean_uint64_xor(v_z_1444_, v___x_1446_);
v___x_1448_ = lean_uint64_to_uint32(v___x_1447_);
v___x_1449_ = lean_uint32_to_nat(v___x_1448_);
v___x_1450_ = lean_nat_mul(v___x_1422_, v_scaleShift_1341_);
v___x_1451_ = lean_nat_add(v___x_1450_, v___x_1342_);
lean_dec(v___x_1450_);
v___x_1452_ = lean_nat_mod(v___x_1449_, v___x_1451_);
lean_dec(v___x_1451_);
lean_dec(v___x_1449_);
v___x_1453_ = lean_nat_to_int(v___x_1452_);
v___x_1454_ = lean_nat_to_int(v_scaleShift_1341_);
v___x_1455_ = lean_int_sub(v___x_1453_, v___x_1454_);
lean_dec(v___x_1454_);
lean_dec(v___x_1453_);
v___y_1405_ = v___y_1418_;
v___y_1406_ = v___x_1455_;
goto v___jp_1404_;
}
else
{
lean_object* v___x_1456_; 
lean_dec(v_scaleShift_1341_);
lean_dec(v_scaleBlock_1340_);
v___x_1456_ = lean_obj_once(&lp_competition_Bench_Suite_ordinary___closed__0, &lp_competition_Bench_Suite_ordinary___closed__0_once, _init_lp_competition_Bench_Suite_ordinary___closed__0);
v___y_1405_ = v___y_1418_;
v___y_1406_ = v___x_1456_;
goto v___jp_1404_;
}
}
v___jp_1484_:
{
lean_object* v___x_1486_; lean_object* v___x_1487_; 
v___x_1486_ = lean_nat_to_int(v___y_1485_);
v___x_1487_ = lean_int_sub(v_centre_1483_, v___x_1486_);
lean_dec(v___x_1486_);
lean_dec(v_centre_1483_);
v___y_1418_ = v___x_1487_;
goto v___jp_1417_;
}
}
}
LEAN_EXPORT lean_object* lp_competition_Bench_Suite_ordinary___boxed(lean_object* v_c_1500_, lean_object* v_i_1501_, lean_object* v_j_1502_, lean_object* v_role_1503_){
_start:
{
uint32_t v_res_1504_; lean_object* v_r_1505_; 
v_res_1504_ = lp_competition_Bench_Suite_ordinary(v_c_1500_, v_i_1501_, v_j_1502_, v_role_1503_);
lean_dec(v_role_1503_);
lean_dec(v_j_1502_);
lean_dec(v_i_1501_);
v_r_1505_ = lean_box_uint32(v_res_1504_);
return v_r_1505_;
}
}
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00Bench_Suite_nthKind_spec__0___redArg(lean_object* v_mask_1506_, lean_object* v_r_1507_, lean_object* v_range_1508_, lean_object* v_b_1509_, lean_object* v_i_1510_){
_start:
{
lean_object* v_stop_1511_; lean_object* v_step_1512_; lean_object* v_a_1514_; uint8_t v___x_1517_; 
v_stop_1511_ = lean_ctor_get(v_range_1508_, 1);
v_step_1512_ = lean_ctor_get(v_range_1508_, 2);
v___x_1517_ = lean_nat_dec_lt(v_i_1510_, v_stop_1511_);
if (v___x_1517_ == 0)
{
lean_dec(v_i_1510_);
return v_b_1509_;
}
else
{
lean_object* v_snd_1518_; lean_object* v___x_1520_; uint8_t v_isShared_1521_; uint8_t v_isSharedCheck_1540_; 
v_snd_1518_ = lean_ctor_get(v_b_1509_, 1);
v_isSharedCheck_1540_ = !lean_is_exclusive(v_b_1509_);
if (v_isSharedCheck_1540_ == 0)
{
lean_object* v_unused_1541_; 
v_unused_1541_ = lean_ctor_get(v_b_1509_, 0);
lean_dec(v_unused_1541_);
v___x_1520_ = v_b_1509_;
v_isShared_1521_ = v_isSharedCheck_1540_;
goto v_resetjp_1519_;
}
else
{
lean_inc(v_snd_1518_);
lean_dec(v_b_1509_);
v___x_1520_ = lean_box(0);
v_isShared_1521_ = v_isSharedCheck_1540_;
goto v_resetjp_1519_;
}
v_resetjp_1519_:
{
lean_object* v___x_1522_; lean_object* v___x_1523_; lean_object* v___x_1524_; lean_object* v___x_1525_; lean_object* v___x_1526_; uint8_t v___x_1527_; 
v___x_1522_ = lean_unsigned_to_nat(1u);
v___x_1523_ = lean_box(0);
v___x_1524_ = lean_nat_shiftr(v_mask_1506_, v_i_1510_);
v___x_1525_ = lean_unsigned_to_nat(2u);
v___x_1526_ = lean_nat_mod(v___x_1524_, v___x_1525_);
lean_dec(v___x_1524_);
v___x_1527_ = lean_nat_dec_eq(v___x_1526_, v___x_1522_);
lean_dec(v___x_1526_);
if (v___x_1527_ == 0)
{
lean_object* v___x_1529_; 
if (v_isShared_1521_ == 0)
{
lean_ctor_set(v___x_1520_, 0, v___x_1523_);
v___x_1529_ = v___x_1520_;
goto v_reusejp_1528_;
}
else
{
lean_object* v_reuseFailAlloc_1530_; 
v_reuseFailAlloc_1530_ = lean_alloc_ctor(0, 2, 0);
lean_ctor_set(v_reuseFailAlloc_1530_, 0, v___x_1523_);
lean_ctor_set(v_reuseFailAlloc_1530_, 1, v_snd_1518_);
v___x_1529_ = v_reuseFailAlloc_1530_;
goto v_reusejp_1528_;
}
v_reusejp_1528_:
{
v_a_1514_ = v___x_1529_;
goto v___jp_1513_;
}
}
else
{
uint8_t v___x_1531_; 
v___x_1531_ = lean_nat_dec_eq(v_snd_1518_, v_r_1507_);
if (v___x_1531_ == 0)
{
lean_object* v___x_1532_; lean_object* v___x_1534_; 
v___x_1532_ = lean_nat_add(v_snd_1518_, v___x_1522_);
lean_dec(v_snd_1518_);
if (v_isShared_1521_ == 0)
{
lean_ctor_set(v___x_1520_, 1, v___x_1532_);
lean_ctor_set(v___x_1520_, 0, v___x_1523_);
v___x_1534_ = v___x_1520_;
goto v_reusejp_1533_;
}
else
{
lean_object* v_reuseFailAlloc_1535_; 
v_reuseFailAlloc_1535_ = lean_alloc_ctor(0, 2, 0);
lean_ctor_set(v_reuseFailAlloc_1535_, 0, v___x_1523_);
lean_ctor_set(v_reuseFailAlloc_1535_, 1, v___x_1532_);
v___x_1534_ = v_reuseFailAlloc_1535_;
goto v_reusejp_1533_;
}
v_reusejp_1533_:
{
v_a_1514_ = v___x_1534_;
goto v___jp_1513_;
}
}
else
{
lean_object* v___x_1536_; lean_object* v___x_1538_; 
v___x_1536_ = lean_alloc_ctor(1, 1, 0);
lean_ctor_set(v___x_1536_, 0, v_i_1510_);
if (v_isShared_1521_ == 0)
{
lean_ctor_set(v___x_1520_, 0, v___x_1536_);
v___x_1538_ = v___x_1520_;
goto v_reusejp_1537_;
}
else
{
lean_object* v_reuseFailAlloc_1539_; 
v_reuseFailAlloc_1539_ = lean_alloc_ctor(0, 2, 0);
lean_ctor_set(v_reuseFailAlloc_1539_, 0, v___x_1536_);
lean_ctor_set(v_reuseFailAlloc_1539_, 1, v_snd_1518_);
v___x_1538_ = v_reuseFailAlloc_1539_;
goto v_reusejp_1537_;
}
v_reusejp_1537_:
{
return v___x_1538_;
}
}
}
}
}
v___jp_1513_:
{
lean_object* v___x_1515_; 
v___x_1515_ = lean_nat_add(v_i_1510_, v_step_1512_);
lean_dec(v_i_1510_);
v_b_1509_ = v_a_1514_;
v_i_1510_ = v___x_1515_;
goto _start;
}
}
}
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00Bench_Suite_nthKind_spec__0___redArg___boxed(lean_object* v_mask_1542_, lean_object* v_r_1543_, lean_object* v_range_1544_, lean_object* v_b_1545_, lean_object* v_i_1546_){
_start:
{
lean_object* v_res_1547_; 
v_res_1547_ = lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00Bench_Suite_nthKind_spec__0___redArg(v_mask_1542_, v_r_1543_, v_range_1544_, v_b_1545_, v_i_1546_);
lean_dec_ref(v_range_1544_);
lean_dec(v_r_1543_);
lean_dec(v_mask_1542_);
return v_res_1547_;
}
}
LEAN_EXPORT lean_object* lp_competition_Bench_Suite_nthKind(lean_object* v_mask_1555_, lean_object* v_r_1556_){
_start:
{
lean_object* v_seen_1557_; lean_object* v___x_1558_; lean_object* v___x_1559_; lean_object* v___x_1560_; lean_object* v___x_1561_; lean_object* v_fst_1562_; 
v_seen_1557_ = lean_unsigned_to_nat(0u);
v___x_1558_ = lean_unsigned_to_nat(1u);
v___x_1559_ = ((lean_object*)(lp_competition_Bench_Suite_nthKind___closed__0));
v___x_1560_ = ((lean_object*)(lp_competition_Bench_Suite_nthKind___closed__1));
v___x_1561_ = lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00Bench_Suite_nthKind_spec__0___redArg(v_mask_1555_, v_r_1556_, v___x_1559_, v___x_1560_, v_seen_1557_);
v_fst_1562_ = lean_ctor_get(v___x_1561_, 0);
lean_inc(v_fst_1562_);
lean_dec_ref(v___x_1561_);
if (lean_obj_tag(v_fst_1562_) == 0)
{
return v___x_1558_;
}
else
{
lean_object* v_val_1563_; 
v_val_1563_ = lean_ctor_get(v_fst_1562_, 0);
lean_inc(v_val_1563_);
lean_dec_ref_known(v_fst_1562_, 1);
return v_val_1563_;
}
}
}
LEAN_EXPORT lean_object* lp_competition_Bench_Suite_nthKind___boxed(lean_object* v_mask_1564_, lean_object* v_r_1565_){
_start:
{
lean_object* v_res_1566_; 
v_res_1566_ = lp_competition_Bench_Suite_nthKind(v_mask_1564_, v_r_1565_);
lean_dec(v_r_1565_);
lean_dec(v_mask_1564_);
return v_res_1566_;
}
}
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00Bench_Suite_nthKind_spec__0(lean_object* v_mask_1567_, lean_object* v_r_1568_, lean_object* v_range_1569_, lean_object* v_b_1570_, lean_object* v_i_1571_, lean_object* v_hs_1572_, lean_object* v_hl_1573_){
_start:
{
lean_object* v___x_1574_; 
v___x_1574_ = lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00Bench_Suite_nthKind_spec__0___redArg(v_mask_1567_, v_r_1568_, v_range_1569_, v_b_1570_, v_i_1571_);
return v___x_1574_;
}
}
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00Bench_Suite_nthKind_spec__0___boxed(lean_object* v_mask_1575_, lean_object* v_r_1576_, lean_object* v_range_1577_, lean_object* v_b_1578_, lean_object* v_i_1579_, lean_object* v_hs_1580_, lean_object* v_hl_1581_){
_start:
{
lean_object* v_res_1582_; 
v_res_1582_ = lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00Bench_Suite_nthKind_spec__0(v_mask_1575_, v_r_1576_, v_range_1577_, v_b_1578_, v_i_1579_, v_hs_1580_, v_hl_1581_);
lean_dec_ref(v_range_1577_);
lean_dec(v_r_1576_);
lean_dec(v_mask_1575_);
return v_res_1582_;
}
}
LEAN_EXPORT lean_object* lp_competition_List_countP_go___at___00Bench_Suite_special_spec__0(lean_object* v_c_1583_, lean_object* v_a_1584_, lean_object* v_a_1585_){
_start:
{
if (lean_obj_tag(v_a_1584_) == 0)
{
return v_a_1585_;
}
else
{
lean_object* v_head_1586_; lean_object* v_tail_1587_; lean_object* v_specMask_1588_; lean_object* v___x_1589_; lean_object* v___x_1590_; lean_object* v___x_1591_; lean_object* v___x_1592_; uint8_t v___x_1593_; 
v_head_1586_ = lean_ctor_get(v_a_1584_, 0);
v_tail_1587_ = lean_ctor_get(v_a_1584_, 1);
v_specMask_1588_ = lean_ctor_get(v_c_1583_, 20);
v___x_1589_ = lean_nat_shiftr(v_specMask_1588_, v_head_1586_);
v___x_1590_ = lean_unsigned_to_nat(2u);
v___x_1591_ = lean_nat_mod(v___x_1589_, v___x_1590_);
lean_dec(v___x_1589_);
v___x_1592_ = lean_unsigned_to_nat(1u);
v___x_1593_ = lean_nat_dec_eq(v___x_1591_, v___x_1592_);
lean_dec(v___x_1591_);
if (v___x_1593_ == 0)
{
v_a_1584_ = v_tail_1587_;
goto _start;
}
else
{
lean_object* v___x_1595_; 
v___x_1595_ = lean_nat_add(v_a_1585_, v___x_1592_);
lean_dec(v_a_1585_);
v_a_1584_ = v_tail_1587_;
v_a_1585_ = v___x_1595_;
goto _start;
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_List_countP_go___at___00Bench_Suite_special_spec__0___boxed(lean_object* v_c_1597_, lean_object* v_a_1598_, lean_object* v_a_1599_){
_start:
{
lean_object* v_res_1600_; 
v_res_1600_ = lp_competition_List_countP_go___at___00Bench_Suite_special_spec__0(v_c_1597_, v_a_1598_, v_a_1599_);
lean_dec(v_a_1598_);
lean_dec_ref(v_c_1597_);
return v_res_1600_;
}
}
static lean_object* _init_lp_competition_Bench_Suite_special___closed__0(void){
_start:
{
lean_object* v___x_1601_; lean_object* v___x_1602_; 
v___x_1601_ = lean_unsigned_to_nat(5u);
v___x_1602_ = l_List_range(v___x_1601_);
return v___x_1602_;
}
}
LEAN_EXPORT uint32_t lp_competition_Bench_Suite_special(lean_object* v_c_1603_, lean_object* v_i_1604_, lean_object* v_role_1605_){
_start:
{
lean_object* v_seed_1606_; lean_object* v_specMask_1607_; lean_object* v___x_1608_; lean_object* v___x_1609_; lean_object* v___x_1610_; lean_object* v_count_1611_; lean_object* v___x_1612_; lean_object* v___x_1613_; lean_object* v___x_1614_; uint64_t v___x_1615_; uint64_t v___x_1616_; uint64_t v___x_1617_; uint64_t v___x_1618_; uint64_t v___x_1619_; uint64_t v___x_1620_; uint64_t v___x_1621_; uint64_t v___x_1622_; uint64_t v_z_1623_; uint64_t v___x_1624_; uint64_t v___x_1625_; uint64_t v___x_1626_; uint64_t v___x_1627_; uint64_t v_z_1628_; uint64_t v___x_1629_; uint64_t v___x_1630_; uint64_t v___x_1631_; uint64_t v___x_1632_; uint64_t v_z_1633_; uint64_t v___x_1634_; uint64_t v___x_1635_; uint64_t v___x_1636_; uint32_t v___x_1637_; lean_object* v___x_1638_; lean_object* v___x_1639_; lean_object* v___y_1641_; uint8_t v___x_1694_; 
v_seed_1606_ = lean_ctor_get(v_c_1603_, 2);
v_specMask_1607_ = lean_ctor_get(v_c_1603_, 20);
v___x_1608_ = lean_unsigned_to_nat(5u);
v___x_1609_ = lean_obj_once(&lp_competition_Bench_Suite_special___closed__0, &lp_competition_Bench_Suite_special___closed__0_once, _init_lp_competition_Bench_Suite_special___closed__0);
v___x_1610_ = lean_unsigned_to_nat(0u);
v_count_1611_ = lp_competition_List_countP_go___at___00Bench_Suite_special_spec__0(v_c_1603_, v___x_1609_, v___x_1610_);
v___x_1612_ = lean_unsigned_to_nat(16u);
v___x_1613_ = lean_nat_mul(v_role_1605_, v___x_1612_);
v___x_1614_ = lean_nat_add(v___x_1613_, v___x_1608_);
v___x_1615_ = lean_uint64_of_nat(v_seed_1606_);
v___x_1616_ = lean_uint64_of_nat(v_i_1604_);
v___x_1617_ = 11400714819323198485ULL;
v___x_1618_ = lean_uint64_mul(v___x_1616_, v___x_1617_);
v___x_1619_ = lean_uint64_add(v___x_1615_, v___x_1618_);
v___x_1620_ = lean_uint64_of_nat(v___x_1614_);
lean_dec(v___x_1614_);
v___x_1621_ = 15111065706836454659ULL;
v___x_1622_ = lean_uint64_mul(v___x_1620_, v___x_1621_);
v_z_1623_ = lean_uint64_add(v___x_1619_, v___x_1622_);
v___x_1624_ = 30ULL;
v___x_1625_ = lean_uint64_shift_right(v_z_1623_, v___x_1624_);
v___x_1626_ = lean_uint64_xor(v_z_1623_, v___x_1625_);
v___x_1627_ = 13787848793156543929ULL;
v_z_1628_ = lean_uint64_mul(v___x_1626_, v___x_1627_);
v___x_1629_ = 27ULL;
v___x_1630_ = lean_uint64_shift_right(v_z_1628_, v___x_1629_);
v___x_1631_ = lean_uint64_xor(v_z_1628_, v___x_1630_);
v___x_1632_ = 10723151780598845931ULL;
v_z_1633_ = lean_uint64_mul(v___x_1631_, v___x_1632_);
v___x_1634_ = 31ULL;
v___x_1635_ = lean_uint64_shift_right(v_z_1633_, v___x_1634_);
v___x_1636_ = lean_uint64_xor(v_z_1633_, v___x_1635_);
v___x_1637_ = lean_uint64_to_uint32(v___x_1636_);
v___x_1638_ = lean_uint32_to_nat(v___x_1637_);
v___x_1639_ = lean_unsigned_to_nat(1u);
v___x_1694_ = lean_nat_dec_le(v___x_1639_, v_count_1611_);
if (v___x_1694_ == 0)
{
lean_dec(v_count_1611_);
v___y_1641_ = v___x_1639_;
goto v___jp_1640_;
}
else
{
v___y_1641_ = v_count_1611_;
goto v___jp_1640_;
}
v___jp_1640_:
{
lean_object* v___x_1642_; lean_object* v_kind_1643_; lean_object* v___x_1644_; lean_object* v___x_1645_; uint64_t v___x_1646_; uint64_t v___x_1647_; uint64_t v_z_1648_; uint64_t v___x_1649_; uint64_t v___x_1650_; uint64_t v_z_1651_; uint64_t v___x_1652_; uint64_t v___x_1653_; uint64_t v_z_1654_; uint64_t v___x_1655_; uint64_t v___x_1656_; uint32_t v___x_1657_; uint32_t v___x_1658_; uint32_t v_sign_1659_; lean_object* v___x_1660_; lean_object* v___x_1661_; uint64_t v___x_1662_; uint64_t v___x_1663_; uint64_t v_z_1664_; uint64_t v___x_1665_; uint8_t v___x_1666_; 
v___x_1642_ = lean_nat_mod(v___x_1638_, v___y_1641_);
lean_dec(v___y_1641_);
lean_dec(v___x_1638_);
v_kind_1643_ = lp_competition_Bench_Suite_nthKind(v_specMask_1607_, v___x_1642_);
lean_dec(v___x_1642_);
v___x_1644_ = lean_unsigned_to_nat(6u);
v___x_1645_ = lean_nat_add(v___x_1613_, v___x_1644_);
v___x_1646_ = lean_uint64_of_nat(v___x_1645_);
lean_dec(v___x_1645_);
v___x_1647_ = lean_uint64_mul(v___x_1646_, v___x_1621_);
v_z_1648_ = lean_uint64_add(v___x_1619_, v___x_1647_);
v___x_1649_ = lean_uint64_shift_right(v_z_1648_, v___x_1624_);
v___x_1650_ = lean_uint64_xor(v_z_1648_, v___x_1649_);
v_z_1651_ = lean_uint64_mul(v___x_1650_, v___x_1627_);
v___x_1652_ = lean_uint64_shift_right(v_z_1651_, v___x_1629_);
v___x_1653_ = lean_uint64_xor(v_z_1651_, v___x_1652_);
v_z_1654_ = lean_uint64_mul(v___x_1653_, v___x_1632_);
v___x_1655_ = lean_uint64_shift_right(v_z_1654_, v___x_1634_);
v___x_1656_ = lean_uint64_xor(v_z_1654_, v___x_1655_);
v___x_1657_ = lean_uint64_to_uint32(v___x_1656_);
v___x_1658_ = 2147483648;
v_sign_1659_ = lean_uint32_land(v___x_1657_, v___x_1658_);
v___x_1660_ = lean_unsigned_to_nat(7u);
v___x_1661_ = lean_nat_add(v___x_1613_, v___x_1660_);
lean_dec(v___x_1613_);
v___x_1662_ = lean_uint64_of_nat(v___x_1661_);
lean_dec(v___x_1661_);
v___x_1663_ = lean_uint64_mul(v___x_1662_, v___x_1621_);
v_z_1664_ = lean_uint64_add(v___x_1619_, v___x_1663_);
v___x_1665_ = lean_uint64_shift_right(v_z_1664_, v___x_1624_);
v___x_1666_ = lean_nat_dec_eq(v_kind_1643_, v___x_1610_);
if (v___x_1666_ == 0)
{
uint64_t v___x_1667_; uint64_t v_z_1668_; uint64_t v___x_1669_; uint64_t v___x_1670_; uint64_t v_z_1671_; uint64_t v___x_1672_; uint64_t v___x_1673_; uint32_t v___x_1674_; uint32_t v___x_1675_; uint32_t v_low_1676_; uint8_t v___x_1677_; 
v___x_1667_ = lean_uint64_xor(v_z_1664_, v___x_1665_);
v_z_1668_ = lean_uint64_mul(v___x_1667_, v___x_1627_);
v___x_1669_ = lean_uint64_shift_right(v_z_1668_, v___x_1629_);
v___x_1670_ = lean_uint64_xor(v_z_1668_, v___x_1669_);
v_z_1671_ = lean_uint64_mul(v___x_1670_, v___x_1632_);
v___x_1672_ = lean_uint64_shift_right(v_z_1671_, v___x_1634_);
v___x_1673_ = lean_uint64_xor(v_z_1671_, v___x_1672_);
v___x_1674_ = lean_uint64_to_uint32(v___x_1673_);
v___x_1675_ = 8388607;
v_low_1676_ = lean_uint32_land(v___x_1674_, v___x_1675_);
v___x_1677_ = lean_nat_dec_eq(v_kind_1643_, v___x_1639_);
if (v___x_1677_ == 0)
{
lean_object* v___x_1678_; uint8_t v___x_1679_; 
v___x_1678_ = lean_unsigned_to_nat(2u);
v___x_1679_ = lean_nat_dec_eq(v_kind_1643_, v___x_1678_);
if (v___x_1679_ == 0)
{
lean_object* v___x_1680_; uint8_t v___x_1681_; 
v___x_1680_ = lean_unsigned_to_nat(3u);
v___x_1681_ = lean_nat_dec_eq(v_kind_1643_, v___x_1680_);
lean_dec(v_kind_1643_);
if (v___x_1681_ == 0)
{
return v_sign_1659_;
}
else
{
uint32_t v___x_1682_; uint32_t v___x_1683_; uint32_t v___x_1684_; 
v___x_1682_ = 1;
v___x_1683_ = lean_uint32_lor(v_low_1676_, v___x_1682_);
v___x_1684_ = lean_uint32_lor(v_sign_1659_, v___x_1683_);
return v___x_1684_;
}
}
else
{
uint32_t v___x_1685_; uint32_t v___x_1686_; 
lean_dec(v_kind_1643_);
v___x_1685_ = 2139095039;
v___x_1686_ = lean_uint32_lor(v_sign_1659_, v___x_1685_);
return v___x_1686_;
}
}
else
{
uint32_t v___x_1687_; uint32_t v___x_1688_; uint32_t v___x_1689_; uint32_t v___x_1690_; uint32_t v___x_1691_; 
lean_dec(v_kind_1643_);
v___x_1687_ = 2139095040;
v___x_1688_ = lean_uint32_lor(v_sign_1659_, v___x_1687_);
v___x_1689_ = 1;
v___x_1690_ = lean_uint32_lor(v_low_1676_, v___x_1689_);
v___x_1691_ = lean_uint32_lor(v___x_1688_, v___x_1690_);
return v___x_1691_;
}
}
else
{
uint32_t v___x_1692_; uint32_t v___x_1693_; 
lean_dec(v_kind_1643_);
v___x_1692_ = 2139095040;
v___x_1693_ = lean_uint32_lor(v_sign_1659_, v___x_1692_);
return v___x_1693_;
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_Bench_Suite_special___boxed(lean_object* v_c_1695_, lean_object* v_i_1696_, lean_object* v_role_1697_){
_start:
{
uint32_t v_res_1698_; lean_object* v_r_1699_; 
v_res_1698_ = lp_competition_Bench_Suite_special(v_c_1695_, v_i_1696_, v_role_1697_);
lean_dec(v_role_1697_);
lean_dec(v_i_1696_);
lean_dec_ref(v_c_1695_);
v_r_1699_ = lean_box_uint32(v_res_1698_);
return v_r_1699_;
}
}
LEAN_EXPORT uint8_t lp_competition_Bench_Suite_isSpecial(lean_object* v_c_1700_, lean_object* v_i_1701_, lean_object* v_role_1702_, lean_object* v_row_1703_){
_start:
{
lean_object* v_seed_1704_; lean_object* v_specRate_1705_; lean_object* v_specPlace_1706_; lean_object* v_specPeriod_1707_; lean_object* v_specBurst_1708_; uint8_t v___y_1710_; lean_object* v___x_1742_; uint8_t v___x_1743_; 
v_seed_1704_ = lean_ctor_get(v_c_1700_, 2);
v_specRate_1705_ = lean_ctor_get(v_c_1700_, 16);
v_specPlace_1706_ = lean_ctor_get(v_c_1700_, 17);
v_specPeriod_1707_ = lean_ctor_get(v_c_1700_, 18);
v_specBurst_1708_ = lean_ctor_get(v_c_1700_, 19);
v___x_1742_ = lean_unsigned_to_nat(0u);
v___x_1743_ = lean_nat_dec_lt(v___x_1742_, v_specRate_1705_);
if (v___x_1743_ == 0)
{
return v___x_1743_;
}
else
{
lean_object* v___x_1744_; uint8_t v___x_1745_; 
v___x_1744_ = lean_unsigned_to_nat(1u);
v___x_1745_ = lean_nat_dec_eq(v_specPlace_1706_, v___x_1744_);
if (v___x_1745_ == 0)
{
lean_object* v___x_1746_; uint8_t v___x_1747_; 
v___x_1746_ = lean_unsigned_to_nat(2u);
v___x_1747_ = lean_nat_dec_eq(v_specPlace_1706_, v___x_1746_);
if (v___x_1747_ == 0)
{
lean_object* v___x_1748_; uint8_t v___x_1749_; 
v___x_1748_ = lean_unsigned_to_nat(3u);
v___x_1749_ = lean_nat_dec_eq(v_specPlace_1706_, v___x_1748_);
if (v___x_1749_ == 0)
{
lean_object* v___x_1750_; lean_object* v___x_1751_; lean_object* v___x_1752_; lean_object* v___x_1753_; uint64_t v___x_1754_; uint64_t v___x_1755_; uint64_t v___x_1756_; uint64_t v___x_1757_; uint64_t v___x_1758_; uint64_t v___x_1759_; uint64_t v___x_1760_; uint64_t v___x_1761_; uint64_t v_z_1762_; uint64_t v___x_1763_; uint64_t v___x_1764_; uint64_t v___x_1765_; uint64_t v___x_1766_; uint64_t v_z_1767_; uint64_t v___x_1768_; uint64_t v___x_1769_; uint64_t v___x_1770_; uint64_t v___x_1771_; uint64_t v_z_1772_; uint64_t v___x_1773_; uint64_t v___x_1774_; uint64_t v___x_1775_; uint32_t v___x_1776_; lean_object* v___x_1777_; lean_object* v___x_1778_; lean_object* v___x_1779_; uint8_t v___x_1780_; 
v___x_1750_ = lean_unsigned_to_nat(9u);
v___x_1751_ = lean_unsigned_to_nat(16u);
v___x_1752_ = lean_nat_mul(v_role_1702_, v___x_1751_);
v___x_1753_ = lean_nat_add(v___x_1752_, v___x_1750_);
lean_dec(v___x_1752_);
v___x_1754_ = lean_uint64_of_nat(v_seed_1704_);
v___x_1755_ = lean_uint64_of_nat(v_i_1701_);
v___x_1756_ = 11400714819323198485ULL;
v___x_1757_ = lean_uint64_mul(v___x_1755_, v___x_1756_);
v___x_1758_ = lean_uint64_add(v___x_1754_, v___x_1757_);
v___x_1759_ = lean_uint64_of_nat(v___x_1753_);
lean_dec(v___x_1753_);
v___x_1760_ = 15111065706836454659ULL;
v___x_1761_ = lean_uint64_mul(v___x_1759_, v___x_1760_);
v_z_1762_ = lean_uint64_add(v___x_1758_, v___x_1761_);
v___x_1763_ = 30ULL;
v___x_1764_ = lean_uint64_shift_right(v_z_1762_, v___x_1763_);
v___x_1765_ = lean_uint64_xor(v_z_1762_, v___x_1764_);
v___x_1766_ = 13787848793156543929ULL;
v_z_1767_ = lean_uint64_mul(v___x_1765_, v___x_1766_);
v___x_1768_ = 27ULL;
v___x_1769_ = lean_uint64_shift_right(v_z_1767_, v___x_1768_);
v___x_1770_ = lean_uint64_xor(v_z_1767_, v___x_1769_);
v___x_1771_ = 10723151780598845931ULL;
v_z_1772_ = lean_uint64_mul(v___x_1770_, v___x_1771_);
v___x_1773_ = 31ULL;
v___x_1774_ = lean_uint64_shift_right(v_z_1772_, v___x_1773_);
v___x_1775_ = lean_uint64_xor(v_z_1772_, v___x_1774_);
v___x_1776_ = lean_uint64_to_uint32(v___x_1775_);
v___x_1777_ = lean_uint32_to_nat(v___x_1776_);
v___x_1778_ = lean_unsigned_to_nat(100000u);
v___x_1779_ = lean_nat_mod(v___x_1777_, v___x_1778_);
lean_dec(v___x_1777_);
v___x_1780_ = lean_nat_dec_lt(v___x_1779_, v_specRate_1705_);
lean_dec(v___x_1779_);
return v___x_1780_;
}
else
{
lean_object* v___x_1781_; uint8_t v___x_1782_; 
v___x_1781_ = lean_nat_mod(v_i_1701_, v_row_1703_);
v___x_1782_ = lean_nat_dec_eq(v___x_1781_, v___x_1742_);
if (v___x_1782_ == 0)
{
lean_object* v___x_1783_; uint8_t v___x_1784_; 
v___x_1783_ = lean_nat_sub(v_row_1703_, v___x_1744_);
v___x_1784_ = lean_nat_dec_eq(v___x_1781_, v___x_1783_);
lean_dec(v___x_1783_);
lean_dec(v___x_1781_);
v___y_1710_ = v___x_1784_;
goto v___jp_1709_;
}
else
{
lean_dec(v___x_1781_);
v___y_1710_ = v___x_1782_;
goto v___jp_1709_;
}
}
}
else
{
lean_object* v___x_1785_; lean_object* v___x_1786_; lean_object* v___x_1787_; lean_object* v___x_1788_; lean_object* v___x_1789_; uint64_t v___x_1790_; uint64_t v___x_1791_; uint64_t v___x_1792_; uint64_t v___x_1793_; uint64_t v___x_1794_; uint64_t v___x_1795_; uint64_t v___x_1796_; uint64_t v___x_1797_; uint64_t v_z_1798_; uint64_t v___x_1799_; uint64_t v___x_1800_; uint64_t v___x_1801_; uint64_t v___x_1802_; uint64_t v_z_1803_; uint64_t v___x_1804_; uint64_t v___x_1805_; uint64_t v___x_1806_; uint64_t v___x_1807_; uint64_t v_z_1808_; uint64_t v___x_1809_; uint64_t v___x_1810_; uint64_t v___x_1811_; uint32_t v___x_1812_; lean_object* v___x_1813_; lean_object* v___x_1814_; lean_object* v___x_1815_; uint8_t v___x_1816_; 
v___x_1785_ = lean_nat_div(v_i_1701_, v_specBurst_1708_);
v___x_1786_ = lean_unsigned_to_nat(8u);
v___x_1787_ = lean_unsigned_to_nat(16u);
v___x_1788_ = lean_nat_mul(v_role_1702_, v___x_1787_);
v___x_1789_ = lean_nat_add(v___x_1788_, v___x_1786_);
lean_dec(v___x_1788_);
v___x_1790_ = lean_uint64_of_nat(v_seed_1704_);
v___x_1791_ = lean_uint64_of_nat(v___x_1785_);
lean_dec(v___x_1785_);
v___x_1792_ = 11400714819323198485ULL;
v___x_1793_ = lean_uint64_mul(v___x_1791_, v___x_1792_);
v___x_1794_ = lean_uint64_add(v___x_1790_, v___x_1793_);
v___x_1795_ = lean_uint64_of_nat(v___x_1789_);
lean_dec(v___x_1789_);
v___x_1796_ = 15111065706836454659ULL;
v___x_1797_ = lean_uint64_mul(v___x_1795_, v___x_1796_);
v_z_1798_ = lean_uint64_add(v___x_1794_, v___x_1797_);
v___x_1799_ = 30ULL;
v___x_1800_ = lean_uint64_shift_right(v_z_1798_, v___x_1799_);
v___x_1801_ = lean_uint64_xor(v_z_1798_, v___x_1800_);
v___x_1802_ = 13787848793156543929ULL;
v_z_1803_ = lean_uint64_mul(v___x_1801_, v___x_1802_);
v___x_1804_ = 27ULL;
v___x_1805_ = lean_uint64_shift_right(v_z_1803_, v___x_1804_);
v___x_1806_ = lean_uint64_xor(v_z_1803_, v___x_1805_);
v___x_1807_ = 10723151780598845931ULL;
v_z_1808_ = lean_uint64_mul(v___x_1806_, v___x_1807_);
v___x_1809_ = 31ULL;
v___x_1810_ = lean_uint64_shift_right(v_z_1808_, v___x_1809_);
v___x_1811_ = lean_uint64_xor(v_z_1808_, v___x_1810_);
v___x_1812_ = lean_uint64_to_uint32(v___x_1811_);
v___x_1813_ = lean_uint32_to_nat(v___x_1812_);
v___x_1814_ = lean_unsigned_to_nat(100000u);
v___x_1815_ = lean_nat_mod(v___x_1813_, v___x_1814_);
lean_dec(v___x_1813_);
v___x_1816_ = lean_nat_dec_lt(v___x_1815_, v_specRate_1705_);
lean_dec(v___x_1815_);
return v___x_1816_;
}
}
else
{
lean_object* v___x_1817_; lean_object* v___x_1818_; lean_object* v___x_1819_; lean_object* v___x_1820_; lean_object* v___x_1821_; uint8_t v___x_1822_; 
v___x_1817_ = lean_nat_add(v_i_1701_, v_seed_1704_);
v___x_1818_ = lean_unsigned_to_nat(7u);
v___x_1819_ = lean_nat_mul(v___x_1818_, v_role_1702_);
v___x_1820_ = lean_nat_add(v___x_1817_, v___x_1819_);
lean_dec(v___x_1819_);
lean_dec(v___x_1817_);
v___x_1821_ = lean_nat_mod(v___x_1820_, v_specPeriod_1707_);
lean_dec(v___x_1820_);
v___x_1822_ = lean_nat_dec_eq(v___x_1821_, v___x_1742_);
lean_dec(v___x_1821_);
return v___x_1822_;
}
}
v___jp_1709_:
{
if (v___y_1710_ == 0)
{
return v___y_1710_;
}
else
{
lean_object* v___x_1711_; lean_object* v___x_1712_; lean_object* v___x_1713_; lean_object* v___x_1714_; uint64_t v___x_1715_; uint64_t v___x_1716_; uint64_t v___x_1717_; uint64_t v___x_1718_; uint64_t v___x_1719_; uint64_t v___x_1720_; uint64_t v___x_1721_; uint64_t v___x_1722_; uint64_t v_z_1723_; uint64_t v___x_1724_; uint64_t v___x_1725_; uint64_t v___x_1726_; uint64_t v___x_1727_; uint64_t v_z_1728_; uint64_t v___x_1729_; uint64_t v___x_1730_; uint64_t v___x_1731_; uint64_t v___x_1732_; uint64_t v_z_1733_; uint64_t v___x_1734_; uint64_t v___x_1735_; uint64_t v___x_1736_; uint32_t v___x_1737_; lean_object* v___x_1738_; lean_object* v___x_1739_; lean_object* v___x_1740_; uint8_t v___x_1741_; 
v___x_1711_ = lean_unsigned_to_nat(9u);
v___x_1712_ = lean_unsigned_to_nat(16u);
v___x_1713_ = lean_nat_mul(v_role_1702_, v___x_1712_);
v___x_1714_ = lean_nat_add(v___x_1713_, v___x_1711_);
lean_dec(v___x_1713_);
v___x_1715_ = lean_uint64_of_nat(v_seed_1704_);
v___x_1716_ = lean_uint64_of_nat(v_i_1701_);
v___x_1717_ = 11400714819323198485ULL;
v___x_1718_ = lean_uint64_mul(v___x_1716_, v___x_1717_);
v___x_1719_ = lean_uint64_add(v___x_1715_, v___x_1718_);
v___x_1720_ = lean_uint64_of_nat(v___x_1714_);
lean_dec(v___x_1714_);
v___x_1721_ = 15111065706836454659ULL;
v___x_1722_ = lean_uint64_mul(v___x_1720_, v___x_1721_);
v_z_1723_ = lean_uint64_add(v___x_1719_, v___x_1722_);
v___x_1724_ = 30ULL;
v___x_1725_ = lean_uint64_shift_right(v_z_1723_, v___x_1724_);
v___x_1726_ = lean_uint64_xor(v_z_1723_, v___x_1725_);
v___x_1727_ = 13787848793156543929ULL;
v_z_1728_ = lean_uint64_mul(v___x_1726_, v___x_1727_);
v___x_1729_ = 27ULL;
v___x_1730_ = lean_uint64_shift_right(v_z_1728_, v___x_1729_);
v___x_1731_ = lean_uint64_xor(v_z_1728_, v___x_1730_);
v___x_1732_ = 10723151780598845931ULL;
v_z_1733_ = lean_uint64_mul(v___x_1731_, v___x_1732_);
v___x_1734_ = 31ULL;
v___x_1735_ = lean_uint64_shift_right(v_z_1733_, v___x_1734_);
v___x_1736_ = lean_uint64_xor(v_z_1733_, v___x_1735_);
v___x_1737_ = lean_uint64_to_uint32(v___x_1736_);
v___x_1738_ = lean_uint32_to_nat(v___x_1737_);
v___x_1739_ = lean_unsigned_to_nat(100000u);
v___x_1740_ = lean_nat_mod(v___x_1738_, v___x_1739_);
lean_dec(v___x_1738_);
v___x_1741_ = lean_nat_dec_lt(v___x_1740_, v_specRate_1705_);
lean_dec(v___x_1740_);
return v___x_1741_;
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_Bench_Suite_isSpecial___boxed(lean_object* v_c_1823_, lean_object* v_i_1824_, lean_object* v_role_1825_, lean_object* v_row_1826_){
_start:
{
uint8_t v_res_1827_; lean_object* v_r_1828_; 
v_res_1827_ = lp_competition_Bench_Suite_isSpecial(v_c_1823_, v_i_1824_, v_role_1825_, v_row_1826_);
lean_dec(v_row_1826_);
lean_dec(v_role_1825_);
lean_dec(v_i_1824_);
lean_dec_ref(v_c_1823_);
v_r_1828_ = lean_box(v_res_1827_);
return v_r_1828_;
}
}
LEAN_EXPORT uint32_t lp_competition_Bench_Suite_zero(lean_object* v_c_1829_, lean_object* v_i_1830_, lean_object* v_role_1831_){
_start:
{
lean_object* v_seed_1832_; lean_object* v_zeroKind_1833_; lean_object* v___x_1834_; lean_object* v___x_1835_; lean_object* v___x_1836_; lean_object* v___x_1837_; uint64_t v___x_1838_; uint64_t v___x_1839_; uint64_t v___x_1840_; uint64_t v___x_1841_; uint64_t v___x_1842_; uint64_t v___x_1843_; uint64_t v___x_1844_; uint64_t v___x_1845_; uint64_t v_z_1846_; uint64_t v___x_1847_; uint64_t v___x_1848_; lean_object* v___x_1849_; uint8_t v___x_1850_; 
v_seed_1832_ = lean_ctor_get(v_c_1829_, 2);
v_zeroKind_1833_ = lean_ctor_get(v_c_1829_, 13);
v___x_1834_ = lean_unsigned_to_nat(10u);
v___x_1835_ = lean_unsigned_to_nat(16u);
v___x_1836_ = lean_nat_mul(v_role_1831_, v___x_1835_);
v___x_1837_ = lean_nat_add(v___x_1836_, v___x_1834_);
lean_dec(v___x_1836_);
v___x_1838_ = lean_uint64_of_nat(v_seed_1832_);
v___x_1839_ = lean_uint64_of_nat(v_i_1830_);
v___x_1840_ = 11400714819323198485ULL;
v___x_1841_ = lean_uint64_mul(v___x_1839_, v___x_1840_);
v___x_1842_ = lean_uint64_add(v___x_1838_, v___x_1841_);
v___x_1843_ = lean_uint64_of_nat(v___x_1837_);
lean_dec(v___x_1837_);
v___x_1844_ = 15111065706836454659ULL;
v___x_1845_ = lean_uint64_mul(v___x_1843_, v___x_1844_);
v_z_1846_ = lean_uint64_add(v___x_1842_, v___x_1845_);
v___x_1847_ = 30ULL;
v___x_1848_ = lean_uint64_shift_right(v_z_1846_, v___x_1847_);
v___x_1849_ = lean_unsigned_to_nat(1u);
v___x_1850_ = lean_nat_dec_eq(v_zeroKind_1833_, v___x_1849_);
if (v___x_1850_ == 0)
{
uint64_t v___x_1851_; uint64_t v___x_1852_; uint64_t v_z_1853_; uint64_t v___x_1854_; uint64_t v___x_1855_; uint64_t v___x_1856_; uint64_t v___x_1857_; uint64_t v_z_1858_; uint64_t v___x_1859_; uint64_t v___x_1860_; uint64_t v___x_1861_; uint32_t v_w_1862_; lean_object* v___x_1863_; uint8_t v___x_1864_; 
v___x_1851_ = lean_uint64_xor(v_z_1846_, v___x_1848_);
v___x_1852_ = 13787848793156543929ULL;
v_z_1853_ = lean_uint64_mul(v___x_1851_, v___x_1852_);
v___x_1854_ = 27ULL;
v___x_1855_ = lean_uint64_shift_right(v_z_1853_, v___x_1854_);
v___x_1856_ = lean_uint64_xor(v_z_1853_, v___x_1855_);
v___x_1857_ = 10723151780598845931ULL;
v_z_1858_ = lean_uint64_mul(v___x_1856_, v___x_1857_);
v___x_1859_ = 31ULL;
v___x_1860_ = lean_uint64_shift_right(v_z_1858_, v___x_1859_);
v___x_1861_ = lean_uint64_xor(v_z_1858_, v___x_1860_);
v_w_1862_ = lean_uint64_to_uint32(v___x_1861_);
v___x_1863_ = lean_unsigned_to_nat(2u);
v___x_1864_ = lean_nat_dec_eq(v_zeroKind_1833_, v___x_1863_);
if (v___x_1864_ == 0)
{
lean_object* v___x_1865_; uint8_t v___x_1866_; 
v___x_1865_ = lean_unsigned_to_nat(3u);
v___x_1866_ = lean_nat_dec_eq(v_zeroKind_1833_, v___x_1865_);
if (v___x_1866_ == 0)
{
uint32_t v___x_1867_; 
v___x_1867_ = 0;
return v___x_1867_;
}
else
{
uint32_t v___x_1868_; uint32_t v___x_1869_; lean_object* v___x_1870_; lean_object* v___x_1871_; lean_object* v___x_1872_; lean_object* v___x_1873_; uint32_t v___x_1874_; uint32_t v___x_1875_; uint32_t v___x_1876_; uint32_t v___x_1877_; 
v___x_1868_ = 2155872255;
v___x_1869_ = lean_uint32_land(v_w_1862_, v___x_1868_);
v___x_1870_ = lean_uint32_to_nat(v_w_1862_);
v___x_1871_ = lean_unsigned_to_nat(30u);
v___x_1872_ = lean_nat_mod(v___x_1870_, v___x_1871_);
lean_dec(v___x_1870_);
v___x_1873_ = lean_nat_add(v___x_1849_, v___x_1872_);
lean_dec(v___x_1872_);
v___x_1874_ = lean_uint32_of_nat(v___x_1873_);
lean_dec(v___x_1873_);
v___x_1875_ = 23;
v___x_1876_ = lean_uint32_shift_left(v___x_1874_, v___x_1875_);
v___x_1877_ = lean_uint32_lor(v___x_1869_, v___x_1876_);
return v___x_1877_;
}
}
else
{
uint32_t v___x_1878_; uint32_t v___x_1879_; 
v___x_1878_ = 2147483648;
v___x_1879_ = lean_uint32_land(v_w_1862_, v___x_1878_);
return v___x_1879_;
}
}
else
{
uint32_t v___x_1880_; 
v___x_1880_ = 2147483648;
return v___x_1880_;
}
}
}
LEAN_EXPORT lean_object* lp_competition_Bench_Suite_zero___boxed(lean_object* v_c_1881_, lean_object* v_i_1882_, lean_object* v_role_1883_){
_start:
{
uint32_t v_res_1884_; lean_object* v_r_1885_; 
v_res_1884_ = lp_competition_Bench_Suite_zero(v_c_1881_, v_i_1882_, v_role_1883_);
lean_dec(v_role_1883_);
lean_dec(v_i_1882_);
lean_dec_ref(v_c_1881_);
v_r_1885_ = lean_box_uint32(v_res_1884_);
return v_r_1885_;
}
}
LEAN_EXPORT uint32_t lp_competition_Bench_Suite_element(lean_object* v_c_1886_, lean_object* v_i_1887_, lean_object* v_role_1888_, lean_object* v_row_1889_){
_start:
{
lean_object* v_seed_1890_; lean_object* v_mag_1891_; lean_object* v_codebook_1892_; lean_object* v_zeroPct_1893_; lean_object* v_zeroCluster_1894_; lean_object* v_subPct_1895_; lean_object* v_subBlock_1896_; lean_object* v___x_1897_; uint8_t v___x_1898_; 
v_seed_1890_ = lean_ctor_get(v_c_1886_, 2);
v_mag_1891_ = lean_ctor_get(v_c_1886_, 3);
v_codebook_1892_ = lean_ctor_get(v_c_1886_, 8);
v_zeroPct_1893_ = lean_ctor_get(v_c_1886_, 11);
v_zeroCluster_1894_ = lean_ctor_get(v_c_1886_, 12);
v_subPct_1895_ = lean_ctor_get(v_c_1886_, 14);
v_subBlock_1896_ = lean_ctor_get(v_c_1886_, 15);
v___x_1897_ = lean_unsigned_to_nat(2u);
v___x_1898_ = lean_nat_dec_eq(v_mag_1891_, v___x_1897_);
if (v___x_1898_ == 0)
{
uint8_t v___x_1899_; 
v___x_1899_ = lp_competition_Bench_Suite_isSpecial(v_c_1886_, v_i_1887_, v_role_1888_, v_row_1889_);
if (v___x_1899_ == 0)
{
lean_object* v___x_1900_; uint8_t v___y_1902_; uint8_t v___y_1967_; uint8_t v___x_2002_; 
v___x_1900_ = lean_unsigned_to_nat(0u);
v___x_2002_ = lean_nat_dec_lt(v___x_1900_, v_zeroPct_1893_);
if (v___x_2002_ == 0)
{
v___y_1967_ = v___x_2002_;
goto v___jp_1966_;
}
else
{
lean_object* v___x_2003_; lean_object* v___x_2004_; lean_object* v___x_2005_; lean_object* v___x_2006_; lean_object* v___x_2007_; uint64_t v___x_2008_; uint64_t v___x_2009_; uint64_t v___x_2010_; uint64_t v___x_2011_; uint64_t v___x_2012_; uint64_t v___x_2013_; uint64_t v___x_2014_; uint64_t v___x_2015_; uint64_t v_z_2016_; uint64_t v___x_2017_; uint64_t v___x_2018_; uint64_t v___x_2019_; uint64_t v___x_2020_; uint64_t v_z_2021_; uint64_t v___x_2022_; uint64_t v___x_2023_; uint64_t v___x_2024_; uint64_t v___x_2025_; uint64_t v_z_2026_; uint64_t v___x_2027_; uint64_t v___x_2028_; uint64_t v___x_2029_; uint32_t v___x_2030_; lean_object* v___x_2031_; lean_object* v___x_2032_; lean_object* v___x_2033_; uint8_t v___x_2034_; 
v___x_2003_ = lean_nat_div(v_i_1887_, v_zeroCluster_1894_);
v___x_2004_ = lean_unsigned_to_nat(11u);
v___x_2005_ = lean_unsigned_to_nat(16u);
v___x_2006_ = lean_nat_mul(v_role_1888_, v___x_2005_);
v___x_2007_ = lean_nat_add(v___x_2006_, v___x_2004_);
lean_dec(v___x_2006_);
v___x_2008_ = lean_uint64_of_nat(v_seed_1890_);
v___x_2009_ = lean_uint64_of_nat(v___x_2003_);
lean_dec(v___x_2003_);
v___x_2010_ = 11400714819323198485ULL;
v___x_2011_ = lean_uint64_mul(v___x_2009_, v___x_2010_);
v___x_2012_ = lean_uint64_add(v___x_2008_, v___x_2011_);
v___x_2013_ = lean_uint64_of_nat(v___x_2007_);
lean_dec(v___x_2007_);
v___x_2014_ = 15111065706836454659ULL;
v___x_2015_ = lean_uint64_mul(v___x_2013_, v___x_2014_);
v_z_2016_ = lean_uint64_add(v___x_2012_, v___x_2015_);
v___x_2017_ = 30ULL;
v___x_2018_ = lean_uint64_shift_right(v_z_2016_, v___x_2017_);
v___x_2019_ = lean_uint64_xor(v_z_2016_, v___x_2018_);
v___x_2020_ = 13787848793156543929ULL;
v_z_2021_ = lean_uint64_mul(v___x_2019_, v___x_2020_);
v___x_2022_ = 27ULL;
v___x_2023_ = lean_uint64_shift_right(v_z_2021_, v___x_2022_);
v___x_2024_ = lean_uint64_xor(v_z_2021_, v___x_2023_);
v___x_2025_ = 10723151780598845931ULL;
v_z_2026_ = lean_uint64_mul(v___x_2024_, v___x_2025_);
v___x_2027_ = 31ULL;
v___x_2028_ = lean_uint64_shift_right(v_z_2026_, v___x_2027_);
v___x_2029_ = lean_uint64_xor(v_z_2026_, v___x_2028_);
v___x_2030_ = lean_uint64_to_uint32(v___x_2029_);
v___x_2031_ = lean_uint32_to_nat(v___x_2030_);
v___x_2032_ = lean_unsigned_to_nat(100u);
v___x_2033_ = lean_nat_mod(v___x_2031_, v___x_2032_);
lean_dec(v___x_2031_);
v___x_2034_ = lean_nat_dec_lt(v___x_2033_, v_zeroPct_1893_);
lean_dec(v___x_2033_);
v___y_1967_ = v___x_2034_;
goto v___jp_1966_;
}
v___jp_1901_:
{
if (v___y_1902_ == 0)
{
uint8_t v___x_1903_; 
v___x_1903_ = lean_nat_dec_lt(v___x_1900_, v_codebook_1892_);
if (v___x_1903_ == 0)
{
uint32_t v___x_1904_; 
v___x_1904_ = lp_competition_Bench_Suite_ordinary(v_c_1886_, v_i_1887_, v_i_1887_, v_role_1888_);
return v___x_1904_;
}
else
{
lean_object* v___x_1905_; lean_object* v___x_1906_; lean_object* v___x_1907_; lean_object* v___x_1908_; uint64_t v___x_1909_; uint64_t v___x_1910_; uint64_t v___x_1911_; uint64_t v___x_1912_; uint64_t v___x_1913_; uint64_t v___x_1914_; uint64_t v___x_1915_; uint64_t v___x_1916_; uint64_t v_z_1917_; uint64_t v___x_1918_; uint64_t v___x_1919_; uint64_t v___x_1920_; uint64_t v___x_1921_; uint64_t v_z_1922_; uint64_t v___x_1923_; uint64_t v___x_1924_; uint64_t v___x_1925_; uint64_t v___x_1926_; uint64_t v_z_1927_; uint64_t v___x_1928_; uint64_t v___x_1929_; uint64_t v___x_1930_; uint32_t v___x_1931_; lean_object* v___x_1932_; lean_object* v___x_1933_; uint32_t v___x_1934_; 
v___x_1905_ = lean_unsigned_to_nat(14u);
v___x_1906_ = lean_unsigned_to_nat(16u);
v___x_1907_ = lean_nat_mul(v_role_1888_, v___x_1906_);
v___x_1908_ = lean_nat_add(v___x_1907_, v___x_1905_);
lean_dec(v___x_1907_);
v___x_1909_ = lean_uint64_of_nat(v_seed_1890_);
v___x_1910_ = lean_uint64_of_nat(v_i_1887_);
v___x_1911_ = 11400714819323198485ULL;
v___x_1912_ = lean_uint64_mul(v___x_1910_, v___x_1911_);
v___x_1913_ = lean_uint64_add(v___x_1909_, v___x_1912_);
v___x_1914_ = lean_uint64_of_nat(v___x_1908_);
lean_dec(v___x_1908_);
v___x_1915_ = 15111065706836454659ULL;
v___x_1916_ = lean_uint64_mul(v___x_1914_, v___x_1915_);
v_z_1917_ = lean_uint64_add(v___x_1913_, v___x_1916_);
v___x_1918_ = 30ULL;
v___x_1919_ = lean_uint64_shift_right(v_z_1917_, v___x_1918_);
v___x_1920_ = lean_uint64_xor(v_z_1917_, v___x_1919_);
v___x_1921_ = 13787848793156543929ULL;
v_z_1922_ = lean_uint64_mul(v___x_1920_, v___x_1921_);
v___x_1923_ = 27ULL;
v___x_1924_ = lean_uint64_shift_right(v_z_1922_, v___x_1923_);
v___x_1925_ = lean_uint64_xor(v_z_1922_, v___x_1924_);
v___x_1926_ = 10723151780598845931ULL;
v_z_1927_ = lean_uint64_mul(v___x_1925_, v___x_1926_);
v___x_1928_ = 31ULL;
v___x_1929_ = lean_uint64_shift_right(v_z_1927_, v___x_1928_);
v___x_1930_ = lean_uint64_xor(v_z_1927_, v___x_1929_);
v___x_1931_ = lean_uint64_to_uint32(v___x_1930_);
v___x_1932_ = lean_uint32_to_nat(v___x_1931_);
v___x_1933_ = lean_nat_mod(v___x_1932_, v_codebook_1892_);
lean_dec(v___x_1932_);
v___x_1934_ = lp_competition_Bench_Suite_ordinary(v_c_1886_, v_i_1887_, v___x_1933_, v_role_1888_);
lean_dec(v___x_1933_);
return v___x_1934_;
}
}
else
{
lean_object* v___x_1935_; lean_object* v___x_1936_; lean_object* v___x_1937_; lean_object* v___x_1938_; uint64_t v___x_1939_; uint64_t v___x_1940_; uint64_t v___x_1941_; uint64_t v___x_1942_; uint64_t v___x_1943_; uint64_t v___x_1944_; uint64_t v___x_1945_; uint64_t v___x_1946_; uint64_t v_z_1947_; uint64_t v___x_1948_; uint64_t v___x_1949_; uint64_t v___x_1950_; uint64_t v___x_1951_; uint64_t v_z_1952_; uint64_t v___x_1953_; uint64_t v___x_1954_; uint64_t v___x_1955_; uint64_t v___x_1956_; uint64_t v_z_1957_; uint64_t v___x_1958_; uint64_t v___x_1959_; uint64_t v___x_1960_; uint32_t v___x_1961_; uint32_t v___x_1962_; uint32_t v___x_1963_; uint32_t v___x_1964_; uint32_t v___x_1965_; 
lean_inc(v_seed_1890_);
lean_dec_ref(v_c_1886_);
v___x_1935_ = lean_unsigned_to_nat(13u);
v___x_1936_ = lean_unsigned_to_nat(16u);
v___x_1937_ = lean_nat_mul(v_role_1888_, v___x_1936_);
v___x_1938_ = lean_nat_add(v___x_1937_, v___x_1935_);
lean_dec(v___x_1937_);
v___x_1939_ = lean_uint64_of_nat(v_seed_1890_);
lean_dec(v_seed_1890_);
v___x_1940_ = lean_uint64_of_nat(v_i_1887_);
v___x_1941_ = 11400714819323198485ULL;
v___x_1942_ = lean_uint64_mul(v___x_1940_, v___x_1941_);
v___x_1943_ = lean_uint64_add(v___x_1939_, v___x_1942_);
v___x_1944_ = lean_uint64_of_nat(v___x_1938_);
lean_dec(v___x_1938_);
v___x_1945_ = 15111065706836454659ULL;
v___x_1946_ = lean_uint64_mul(v___x_1944_, v___x_1945_);
v_z_1947_ = lean_uint64_add(v___x_1943_, v___x_1946_);
v___x_1948_ = 30ULL;
v___x_1949_ = lean_uint64_shift_right(v_z_1947_, v___x_1948_);
v___x_1950_ = lean_uint64_xor(v_z_1947_, v___x_1949_);
v___x_1951_ = 13787848793156543929ULL;
v_z_1952_ = lean_uint64_mul(v___x_1950_, v___x_1951_);
v___x_1953_ = 27ULL;
v___x_1954_ = lean_uint64_shift_right(v_z_1952_, v___x_1953_);
v___x_1955_ = lean_uint64_xor(v_z_1952_, v___x_1954_);
v___x_1956_ = 10723151780598845931ULL;
v_z_1957_ = lean_uint64_mul(v___x_1955_, v___x_1956_);
v___x_1958_ = 31ULL;
v___x_1959_ = lean_uint64_shift_right(v_z_1957_, v___x_1958_);
v___x_1960_ = lean_uint64_xor(v_z_1957_, v___x_1959_);
v___x_1961_ = lean_uint64_to_uint32(v___x_1960_);
v___x_1962_ = 2155872255;
v___x_1963_ = lean_uint32_land(v___x_1961_, v___x_1962_);
v___x_1964_ = 1;
v___x_1965_ = lean_uint32_lor(v___x_1963_, v___x_1964_);
return v___x_1965_;
}
}
v___jp_1966_:
{
if (v___y_1967_ == 0)
{
uint8_t v___x_1968_; 
v___x_1968_ = lean_nat_dec_lt(v___x_1900_, v_subPct_1895_);
if (v___x_1968_ == 0)
{
v___y_1902_ = v___x_1968_;
goto v___jp_1901_;
}
else
{
lean_object* v___x_1969_; lean_object* v___x_1970_; lean_object* v___x_1971_; lean_object* v___x_1972_; lean_object* v___x_1973_; uint64_t v___x_1974_; uint64_t v___x_1975_; uint64_t v___x_1976_; uint64_t v___x_1977_; uint64_t v___x_1978_; uint64_t v___x_1979_; uint64_t v___x_1980_; uint64_t v___x_1981_; uint64_t v_z_1982_; uint64_t v___x_1983_; uint64_t v___x_1984_; uint64_t v___x_1985_; uint64_t v___x_1986_; uint64_t v_z_1987_; uint64_t v___x_1988_; uint64_t v___x_1989_; uint64_t v___x_1990_; uint64_t v___x_1991_; uint64_t v_z_1992_; uint64_t v___x_1993_; uint64_t v___x_1994_; uint64_t v___x_1995_; uint32_t v___x_1996_; lean_object* v___x_1997_; lean_object* v___x_1998_; lean_object* v___x_1999_; uint8_t v___x_2000_; 
v___x_1969_ = lean_nat_div(v_i_1887_, v_subBlock_1896_);
v___x_1970_ = lean_unsigned_to_nat(12u);
v___x_1971_ = lean_unsigned_to_nat(16u);
v___x_1972_ = lean_nat_mul(v_role_1888_, v___x_1971_);
v___x_1973_ = lean_nat_add(v___x_1972_, v___x_1970_);
lean_dec(v___x_1972_);
v___x_1974_ = lean_uint64_of_nat(v_seed_1890_);
v___x_1975_ = lean_uint64_of_nat(v___x_1969_);
lean_dec(v___x_1969_);
v___x_1976_ = 11400714819323198485ULL;
v___x_1977_ = lean_uint64_mul(v___x_1975_, v___x_1976_);
v___x_1978_ = lean_uint64_add(v___x_1974_, v___x_1977_);
v___x_1979_ = lean_uint64_of_nat(v___x_1973_);
lean_dec(v___x_1973_);
v___x_1980_ = 15111065706836454659ULL;
v___x_1981_ = lean_uint64_mul(v___x_1979_, v___x_1980_);
v_z_1982_ = lean_uint64_add(v___x_1978_, v___x_1981_);
v___x_1983_ = 30ULL;
v___x_1984_ = lean_uint64_shift_right(v_z_1982_, v___x_1983_);
v___x_1985_ = lean_uint64_xor(v_z_1982_, v___x_1984_);
v___x_1986_ = 13787848793156543929ULL;
v_z_1987_ = lean_uint64_mul(v___x_1985_, v___x_1986_);
v___x_1988_ = 27ULL;
v___x_1989_ = lean_uint64_shift_right(v_z_1987_, v___x_1988_);
v___x_1990_ = lean_uint64_xor(v_z_1987_, v___x_1989_);
v___x_1991_ = 10723151780598845931ULL;
v_z_1992_ = lean_uint64_mul(v___x_1990_, v___x_1991_);
v___x_1993_ = 31ULL;
v___x_1994_ = lean_uint64_shift_right(v_z_1992_, v___x_1993_);
v___x_1995_ = lean_uint64_xor(v_z_1992_, v___x_1994_);
v___x_1996_ = lean_uint64_to_uint32(v___x_1995_);
v___x_1997_ = lean_uint32_to_nat(v___x_1996_);
v___x_1998_ = lean_unsigned_to_nat(100u);
v___x_1999_ = lean_nat_mod(v___x_1997_, v___x_1998_);
lean_dec(v___x_1997_);
v___x_2000_ = lean_nat_dec_lt(v___x_1999_, v_subPct_1895_);
lean_dec(v___x_1999_);
v___y_1902_ = v___x_2000_;
goto v___jp_1901_;
}
}
else
{
uint32_t v___x_2001_; 
v___x_2001_ = lp_competition_Bench_Suite_zero(v_c_1886_, v_i_1887_, v_role_1888_);
lean_dec_ref(v_c_1886_);
return v___x_2001_;
}
}
}
else
{
uint32_t v___x_2035_; 
v___x_2035_ = lp_competition_Bench_Suite_special(v_c_1886_, v_i_1887_, v_role_1888_);
lean_dec_ref(v_c_1886_);
return v___x_2035_;
}
}
else
{
lean_object* v___x_2036_; lean_object* v___x_2037_; uint64_t v___x_2038_; uint64_t v___x_2039_; uint64_t v___x_2040_; uint64_t v___x_2041_; uint64_t v___x_2042_; uint64_t v___x_2043_; uint64_t v___x_2044_; uint64_t v___x_2045_; uint64_t v_z_2046_; uint64_t v___x_2047_; uint64_t v___x_2048_; uint64_t v___x_2049_; uint64_t v___x_2050_; uint64_t v_z_2051_; uint64_t v___x_2052_; uint64_t v___x_2053_; uint64_t v___x_2054_; uint64_t v___x_2055_; uint64_t v_z_2056_; uint64_t v___x_2057_; uint64_t v___x_2058_; uint64_t v___x_2059_; uint32_t v___x_2060_; 
lean_inc(v_seed_1890_);
lean_dec_ref(v_c_1886_);
v___x_2036_ = lean_unsigned_to_nat(16u);
v___x_2037_ = lean_nat_mul(v_role_1888_, v___x_2036_);
v___x_2038_ = lean_uint64_of_nat(v_seed_1890_);
lean_dec(v_seed_1890_);
v___x_2039_ = lean_uint64_of_nat(v_i_1887_);
v___x_2040_ = 11400714819323198485ULL;
v___x_2041_ = lean_uint64_mul(v___x_2039_, v___x_2040_);
v___x_2042_ = lean_uint64_add(v___x_2038_, v___x_2041_);
v___x_2043_ = lean_uint64_of_nat(v___x_2037_);
lean_dec(v___x_2037_);
v___x_2044_ = 15111065706836454659ULL;
v___x_2045_ = lean_uint64_mul(v___x_2043_, v___x_2044_);
v_z_2046_ = lean_uint64_add(v___x_2042_, v___x_2045_);
v___x_2047_ = 30ULL;
v___x_2048_ = lean_uint64_shift_right(v_z_2046_, v___x_2047_);
v___x_2049_ = lean_uint64_xor(v_z_2046_, v___x_2048_);
v___x_2050_ = 13787848793156543929ULL;
v_z_2051_ = lean_uint64_mul(v___x_2049_, v___x_2050_);
v___x_2052_ = 27ULL;
v___x_2053_ = lean_uint64_shift_right(v_z_2051_, v___x_2052_);
v___x_2054_ = lean_uint64_xor(v_z_2051_, v___x_2053_);
v___x_2055_ = 10723151780598845931ULL;
v_z_2056_ = lean_uint64_mul(v___x_2054_, v___x_2055_);
v___x_2057_ = 31ULL;
v___x_2058_ = lean_uint64_shift_right(v_z_2056_, v___x_2057_);
v___x_2059_ = lean_uint64_xor(v_z_2056_, v___x_2058_);
v___x_2060_ = lean_uint64_to_uint32(v___x_2059_);
return v___x_2060_;
}
}
}
LEAN_EXPORT lean_object* lp_competition_Bench_Suite_element___boxed(lean_object* v_c_2061_, lean_object* v_i_2062_, lean_object* v_role_2063_, lean_object* v_row_2064_){
_start:
{
uint32_t v_res_2065_; lean_object* v_r_2066_; 
v_res_2065_ = lp_competition_Bench_Suite_element(v_c_2061_, v_i_2062_, v_role_2063_, v_row_2064_);
lean_dec(v_row_2064_);
lean_dec(v_role_2063_);
lean_dec(v_i_2062_);
v_r_2066_ = lean_box_uint32(v_res_2065_);
return v_r_2066_;
}
}
LEAN_EXPORT uint32_t lp_competition_Bench_Suite_partner(lean_object* v_c_2068_, lean_object* v_i_2069_, uint32_t v_a_2070_){
_start:
{
lean_object* v_kernel_2071_; lean_object* v_seed_2072_; lean_object* v_relation_2073_; lean_object* v_relParam_2074_; lean_object* v___x_2075_; uint64_t v___x_2076_; uint64_t v___x_2077_; uint64_t v___x_2078_; uint64_t v___x_2079_; uint64_t v___x_2080_; uint64_t v___x_2081_; uint64_t v_z_2082_; uint64_t v___x_2083_; uint64_t v___x_2084_; uint8_t v___x_2085_; 
v_kernel_2071_ = lean_ctor_get(v_c_2068_, 1);
v_seed_2072_ = lean_ctor_get(v_c_2068_, 2);
v_relation_2073_ = lean_ctor_get(v_c_2068_, 21);
v_relParam_2074_ = lean_ctor_get(v_c_2068_, 22);
v___x_2075_ = lean_unsigned_to_nat(1u);
v___x_2076_ = lean_uint64_of_nat(v_seed_2072_);
v___x_2077_ = lean_uint64_of_nat(v_i_2069_);
v___x_2078_ = 11400714819323198485ULL;
v___x_2079_ = lean_uint64_mul(v___x_2077_, v___x_2078_);
v___x_2080_ = lean_uint64_add(v___x_2076_, v___x_2079_);
v___x_2081_ = 7274435069191304029ULL;
v_z_2082_ = lean_uint64_add(v___x_2080_, v___x_2081_);
v___x_2083_ = 30ULL;
v___x_2084_ = lean_uint64_shift_right(v_z_2082_, v___x_2083_);
v___x_2085_ = lean_nat_dec_eq(v_relation_2073_, v___x_2075_);
if (v___x_2085_ == 0)
{
lean_object* v___x_2086_; uint8_t v___x_2087_; 
v___x_2086_ = lean_unsigned_to_nat(2u);
v___x_2087_ = lean_nat_dec_eq(v_relation_2073_, v___x_2086_);
if (v___x_2087_ == 0)
{
uint64_t v___x_2088_; uint64_t v___x_2089_; uint64_t v_z_2090_; uint64_t v___x_2091_; uint64_t v___x_2092_; uint64_t v___x_2093_; uint64_t v___x_2094_; uint64_t v_z_2095_; uint64_t v___x_2096_; uint64_t v___x_2097_; uint64_t v___x_2098_; uint32_t v_w_2099_; uint32_t v___y_2101_; lean_object* v___y_2102_; lean_object* v___x_2118_; uint8_t v___x_2119_; 
v___x_2088_ = lean_uint64_xor(v_z_2082_, v___x_2084_);
v___x_2089_ = 13787848793156543929ULL;
v_z_2090_ = lean_uint64_mul(v___x_2088_, v___x_2089_);
v___x_2091_ = 27ULL;
v___x_2092_ = lean_uint64_shift_right(v_z_2090_, v___x_2091_);
v___x_2093_ = lean_uint64_xor(v_z_2090_, v___x_2092_);
v___x_2094_ = 10723151780598845931ULL;
v_z_2095_ = lean_uint64_mul(v___x_2093_, v___x_2094_);
v___x_2096_ = 31ULL;
v___x_2097_ = lean_uint64_shift_right(v_z_2095_, v___x_2096_);
v___x_2098_ = lean_uint64_xor(v_z_2095_, v___x_2097_);
v_w_2099_ = lean_uint64_to_uint32(v___x_2098_);
v___x_2118_ = lean_unsigned_to_nat(3u);
v___x_2119_ = lean_nat_dec_eq(v_relation_2073_, v___x_2118_);
if (v___x_2119_ == 0)
{
lean_object* v___x_2120_; uint8_t v___x_2121_; 
v___x_2120_ = lean_unsigned_to_nat(7u);
v___x_2121_ = lean_nat_dec_eq(v_relation_2073_, v___x_2120_);
if (v___x_2121_ == 0)
{
lean_object* v___x_2122_; uint8_t v___x_2123_; 
v___x_2122_ = lean_unsigned_to_nat(4u);
v___x_2123_ = lean_nat_dec_eq(v_relation_2073_, v___x_2122_);
if (v___x_2123_ == 0)
{
lean_object* v___x_2124_; uint8_t v___x_2125_; 
v___x_2124_ = lean_unsigned_to_nat(5u);
v___x_2125_ = lean_nat_dec_eq(v_relation_2073_, v___x_2124_);
if (v___x_2125_ == 0)
{
lean_object* v___x_2126_; uint8_t v___x_2127_; 
v___x_2126_ = lean_unsigned_to_nat(6u);
v___x_2127_ = lean_nat_dec_eq(v_relation_2073_, v___x_2126_);
if (v___x_2127_ == 0)
{
lean_object* v___x_2128_; uint32_t v___x_2129_; 
v___x_2128_ = lean_unsigned_to_nat(31u);
v___x_2129_ = lp_competition_Bench_Suite_element(v_c_2068_, v_i_2069_, v___x_2075_, v___x_2128_);
return v___x_2129_;
}
else
{
uint32_t v___x_2130_; uint32_t v___y_2132_; lean_object* v___y_2133_; uint32_t v___y_2139_; lean_object* v___y_2140_; lean_object* v___y_2141_; uint32_t v___x_2143_; uint32_t v___x_2144_; uint32_t v_ea_2145_; uint8_t v___y_2147_; uint32_t v___x_2159_; uint8_t v___x_2160_; 
v___x_2130_ = 23;
v___x_2143_ = lean_uint32_shift_right(v_a_2070_, v___x_2130_);
v___x_2144_ = 255;
v_ea_2145_ = lean_uint32_land(v___x_2143_, v___x_2144_);
v___x_2159_ = 0;
v___x_2160_ = lean_uint32_dec_eq(v_ea_2145_, v___x_2159_);
if (v___x_2160_ == 0)
{
uint8_t v___x_2161_; 
v___x_2161_ = lean_uint32_dec_eq(v_ea_2145_, v___x_2144_);
v___y_2147_ = v___x_2161_;
goto v___jp_2146_;
}
else
{
v___y_2147_ = v___x_2160_;
goto v___jp_2146_;
}
v___jp_2131_:
{
lean_object* v___x_2134_; uint32_t v___x_2135_; uint32_t v___x_2136_; uint32_t v___x_2137_; 
v___x_2134_ = l_Int_toNat(v___y_2133_);
lean_dec(v___y_2133_);
v___x_2135_ = lean_uint32_of_nat(v___x_2134_);
lean_dec(v___x_2134_);
v___x_2136_ = lean_uint32_shift_left(v___x_2135_, v___x_2130_);
v___x_2137_ = lean_uint32_lor(v___y_2132_, v___x_2136_);
return v___x_2137_;
}
v___jp_2138_:
{
uint8_t v___x_2142_; 
v___x_2142_ = lean_int_dec_le(v___y_2140_, v___y_2141_);
if (v___x_2142_ == 0)
{
lean_dec(v___y_2141_);
lean_inc(v___y_2140_);
v___y_2132_ = v___y_2139_;
v___y_2133_ = v___y_2140_;
goto v___jp_2131_;
}
else
{
v___y_2132_ = v___y_2139_;
v___y_2133_ = v___y_2141_;
goto v___jp_2131_;
}
}
v___jp_2146_:
{
if (v___y_2147_ == 0)
{
uint32_t v___x_2148_; uint32_t v___x_2149_; lean_object* v___x_2150_; lean_object* v___x_2151_; lean_object* v___x_2152_; lean_object* v___x_2153_; lean_object* v___x_2154_; lean_object* v___x_2155_; uint8_t v___x_2156_; 
lean_inc(v_relParam_2074_);
lean_dec_ref(v_c_2068_);
v___x_2148_ = 2155872255;
v___x_2149_ = lean_uint32_land(v_w_2099_, v___x_2148_);
v___x_2150_ = lean_uint32_to_nat(v_ea_2145_);
v___x_2151_ = lean_nat_to_int(v___x_2150_);
v___x_2152_ = lean_nat_to_int(v_relParam_2074_);
v___x_2153_ = lean_int_sub(v___x_2151_, v___x_2152_);
lean_dec(v___x_2152_);
lean_dec(v___x_2151_);
v___x_2154_ = lean_obj_once(&lp_competition_Bench_Suite_clampExp___closed__0, &lp_competition_Bench_Suite_clampExp___closed__0_once, _init_lp_competition_Bench_Suite_clampExp___closed__0);
v___x_2155_ = lean_obj_once(&lp_competition_Bench_Suite_clampExp___closed__1, &lp_competition_Bench_Suite_clampExp___closed__1_once, _init_lp_competition_Bench_Suite_clampExp___closed__1);
v___x_2156_ = lean_int_dec_le(v___x_2155_, v___x_2153_);
if (v___x_2156_ == 0)
{
v___y_2139_ = v___x_2149_;
v___y_2140_ = v___x_2154_;
v___y_2141_ = v___x_2153_;
goto v___jp_2138_;
}
else
{
lean_dec(v___x_2153_);
v___y_2139_ = v___x_2149_;
v___y_2140_ = v___x_2154_;
v___y_2141_ = v___x_2155_;
goto v___jp_2138_;
}
}
else
{
lean_object* v___x_2157_; uint32_t v___x_2158_; 
v___x_2157_ = lean_unsigned_to_nat(31u);
v___x_2158_ = lp_competition_Bench_Suite_element(v_c_2068_, v_i_2069_, v___x_2075_, v___x_2157_);
return v___x_2158_;
}
}
}
}
else
{
lean_object* v___x_2162_; lean_object* v___x_2163_; lean_object* v___x_2164_; uint8_t v___x_2165_; 
v___x_2162_ = lean_uint32_to_nat(v_w_2099_);
v___x_2163_ = lean_unsigned_to_nat(100u);
v___x_2164_ = lean_nat_mod(v___x_2162_, v___x_2163_);
lean_dec(v___x_2162_);
v___x_2165_ = lean_nat_dec_lt(v___x_2164_, v_relParam_2074_);
lean_dec(v___x_2164_);
if (v___x_2165_ == 0)
{
lean_object* v___x_2166_; uint32_t v___x_2167_; 
v___x_2166_ = lean_unsigned_to_nat(31u);
v___x_2167_ = lp_competition_Bench_Suite_element(v_c_2068_, v_i_2069_, v___x_2075_, v___x_2166_);
return v___x_2167_;
}
else
{
lean_object* v___x_2168_; uint8_t v___x_2169_; 
lean_inc_ref(v_kernel_2071_);
lean_dec_ref(v_c_2068_);
v___x_2168_ = ((lean_object*)(lp_competition_Bench_Suite_partner___closed__0));
v___x_2169_ = lean_string_dec_eq(v_kernel_2071_, v___x_2168_);
lean_dec_ref(v_kernel_2071_);
if (v___x_2169_ == 0)
{
uint32_t v___x_2170_; uint32_t v___x_2171_; uint32_t v___x_2172_; uint32_t v___x_2173_; 
v___x_2170_ = 2147483648;
v___x_2171_ = lean_uint32_land(v_w_2099_, v___x_2170_);
v___x_2172_ = 1065353216;
v___x_2173_ = lean_uint32_lor(v___x_2171_, v___x_2172_);
return v___x_2173_;
}
else
{
uint32_t v___x_2174_; uint32_t v___x_2175_; 
v___x_2174_ = 2147483648;
v___x_2175_ = lean_uint32_land(v_w_2099_, v___x_2174_);
return v___x_2175_;
}
}
}
}
else
{
lean_object* v___x_2176_; lean_object* v___x_2177_; uint32_t v___x_2178_; 
v___x_2176_ = lean_unsigned_to_nat(0u);
v___x_2177_ = lean_unsigned_to_nat(31u);
v___x_2178_ = lp_competition_Bench_Suite_element(v_c_2068_, v___x_2176_, v___x_2075_, v___x_2177_);
return v___x_2178_;
}
}
else
{
lean_inc(v_relParam_2074_);
lean_inc(v_relation_2073_);
lean_dec_ref(v_c_2068_);
goto v___jp_2114_;
}
}
else
{
lean_inc(v_relParam_2074_);
lean_inc(v_relation_2073_);
lean_dec_ref(v_c_2068_);
goto v___jp_2114_;
}
v___jp_2100_:
{
uint32_t v___x_2103_; uint32_t v___x_2104_; uint32_t v_mask_2105_; uint32_t v___x_2106_; uint32_t v___x_2107_; uint32_t v___x_2108_; uint32_t v_b_2109_; lean_object* v___x_2110_; uint8_t v___x_2111_; 
v___x_2103_ = lean_uint32_of_nat(v___y_2102_);
lean_dec(v___y_2102_);
v___x_2104_ = lean_uint32_shift_left(v___y_2101_, v___x_2103_);
v_mask_2105_ = lean_uint32_sub(v___x_2104_, v___y_2101_);
v___x_2106_ = lean_uint32_complement(v_mask_2105_);
v___x_2107_ = lean_uint32_land(v_a_2070_, v___x_2106_);
v___x_2108_ = lean_uint32_land(v_w_2099_, v_mask_2105_);
v_b_2109_ = lean_uint32_lor(v___x_2107_, v___x_2108_);
v___x_2110_ = lean_unsigned_to_nat(3u);
v___x_2111_ = lean_nat_dec_eq(v_relation_2073_, v___x_2110_);
lean_dec(v_relation_2073_);
if (v___x_2111_ == 0)
{
return v_b_2109_;
}
else
{
uint32_t v___x_2112_; uint32_t v___x_2113_; 
v___x_2112_ = 2147483648;
v___x_2113_ = lean_uint32_xor(v_b_2109_, v___x_2112_);
return v___x_2113_;
}
}
v___jp_2114_:
{
uint32_t v___x_2115_; lean_object* v___x_2116_; uint8_t v___x_2117_; 
v___x_2115_ = 1;
v___x_2116_ = lean_unsigned_to_nat(23u);
v___x_2117_ = lean_nat_dec_le(v___x_2116_, v_relParam_2074_);
if (v___x_2117_ == 0)
{
v___y_2101_ = v___x_2115_;
v___y_2102_ = v_relParam_2074_;
goto v___jp_2100_;
}
else
{
lean_dec(v_relParam_2074_);
v___y_2101_ = v___x_2115_;
v___y_2102_ = v___x_2116_;
goto v___jp_2100_;
}
}
}
else
{
uint32_t v___x_2179_; uint32_t v___x_2180_; 
lean_dec_ref(v_c_2068_);
v___x_2179_ = 2147483648;
v___x_2180_ = lean_uint32_xor(v_a_2070_, v___x_2179_);
return v___x_2180_;
}
}
else
{
lean_dec_ref(v_c_2068_);
return v_a_2070_;
}
}
}
LEAN_EXPORT lean_object* lp_competition_Bench_Suite_partner___boxed(lean_object* v_c_2181_, lean_object* v_i_2182_, lean_object* v_a_2183_){
_start:
{
uint32_t v_a_boxed_2184_; uint32_t v_res_2185_; lean_object* v_r_2186_; 
v_a_boxed_2184_ = lean_unbox_uint32(v_a_2183_);
lean_dec(v_a_2183_);
v_res_2185_ = lp_competition_Bench_Suite_partner(v_c_2181_, v_i_2182_, v_a_boxed_2184_);
lean_dec(v_i_2182_);
v_r_2186_ = lean_box_uint32(v_res_2185_);
return v_r_2186_;
}
}
LEAN_EXPORT uint32_t lp_competition_Bench_Suite_float(uint32_t v_w_2187_){
_start:
{
return v_w_2187_;
}
}
LEAN_EXPORT lean_object* lp_competition_Bench_Suite_float___boxed(lean_object* v_w_2188_){
_start:
{
uint32_t v_w_boxed_2189_; uint32_t v_res_2190_; lean_object* v_r_2191_; 
v_w_boxed_2189_ = lean_unbox_uint32(v_w_2188_);
lean_dec(v_w_2188_);
v_res_2190_ = lp_competition_Bench_Suite_float(v_w_boxed_2189_);
v_r_2191_ = lean_box_uint32(v_res_2190_);
return v_r_2191_;
}
}
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00Bench_Suite_measure_spec__0___redArg(lean_object* v_pass_2193_, lean_object* v_range_2194_, lean_object* v_b_2195_, lean_object* v_i_2196_){
_start:
{
lean_object* v_stop_2198_; lean_object* v_step_2199_; lean_object* v_a_2201_; uint8_t v___x_2204_; 
v_stop_2198_ = lean_ctor_get(v_range_2194_, 1);
v_step_2199_ = lean_ctor_get(v_range_2194_, 2);
v___x_2204_ = lean_nat_dec_lt(v_i_2196_, v_stop_2198_);
if (v___x_2204_ == 0)
{
lean_object* v___x_2205_; 
lean_dec(v_i_2196_);
lean_dec_ref(v_pass_2193_);
v___x_2205_ = lean_alloc_ctor(0, 1, 0);
lean_ctor_set(v___x_2205_, 0, v_b_2195_);
return v___x_2205_;
}
else
{
lean_object* v___x_2206_; lean_object* v___x_2207_; lean_object* v___x_2208_; uint32_t v___x_2209_; lean_object* v___x_2210_; lean_object* v___x_2211_; 
v___x_2206_ = lean_io_mono_nanos_now();
v___x_2207_ = lean_unsigned_to_nat(1u);
v___x_2208_ = lean_nat_add(v_i_2196_, v___x_2207_);
v___x_2209_ = lean_uint32_of_nat(v___x_2208_);
lean_dec(v___x_2208_);
v___x_2210_ = lean_box_uint32(v___x_2209_);
lean_inc_ref(v_pass_2193_);
v___x_2211_ = lean_apply_2(v_pass_2193_, v___x_2210_, lean_box(0));
if (lean_obj_tag(v___x_2211_) == 0)
{
lean_object* v_a_2212_; lean_object* v___x_2213_; lean_object* v_ns_2214_; lean_object* v___x_2215_; uint32_t v___x_2219_; uint32_t v___x_2220_; uint8_t v___x_2221_; 
v_a_2212_ = lean_ctor_get(v___x_2211_, 0);
lean_inc(v_a_2212_);
lean_dec_ref_known(v___x_2211_, 1);
v___x_2213_ = lean_io_mono_nanos_now();
v_ns_2214_ = lean_unsigned_to_nat(0u);
v___x_2215_ = lean_nat_sub(v___x_2213_, v___x_2206_);
lean_dec(v___x_2206_);
lean_dec(v___x_2213_);
v___x_2219_ = 4294967295;
v___x_2220_ = lean_unbox_uint32(v_a_2212_);
lean_dec(v_a_2212_);
v___x_2221_ = lean_uint32_dec_eq(v___x_2220_, v___x_2219_);
if (v___x_2221_ == 0)
{
goto v___jp_2216_;
}
else
{
lean_object* v___x_2222_; lean_object* v___x_2223_; 
v___x_2222_ = ((lean_object*)(lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00Bench_Suite_measure_spec__0___redArg___closed__0));
v___x_2223_ = lp_batteries_IO_println___at___00Batteries_Tactic_Lint_lintCore_spec__4(v___x_2222_);
if (lean_obj_tag(v___x_2223_) == 0)
{
lean_dec_ref_known(v___x_2223_, 1);
goto v___jp_2216_;
}
else
{
lean_object* v_a_2224_; lean_object* v___x_2226_; uint8_t v_isShared_2227_; uint8_t v_isSharedCheck_2231_; 
lean_dec(v___x_2215_);
lean_dec(v_i_2196_);
lean_dec(v_b_2195_);
lean_dec_ref(v_pass_2193_);
v_a_2224_ = lean_ctor_get(v___x_2223_, 0);
v_isSharedCheck_2231_ = !lean_is_exclusive(v___x_2223_);
if (v_isSharedCheck_2231_ == 0)
{
v___x_2226_ = v___x_2223_;
v_isShared_2227_ = v_isSharedCheck_2231_;
goto v_resetjp_2225_;
}
else
{
lean_inc(v_a_2224_);
lean_dec(v___x_2223_);
v___x_2226_ = lean_box(0);
v_isShared_2227_ = v_isSharedCheck_2231_;
goto v_resetjp_2225_;
}
v_resetjp_2225_:
{
lean_object* v___x_2229_; 
if (v_isShared_2227_ == 0)
{
v___x_2229_ = v___x_2226_;
goto v_reusejp_2228_;
}
else
{
lean_object* v_reuseFailAlloc_2230_; 
v_reuseFailAlloc_2230_ = lean_alloc_ctor(1, 1, 0);
lean_ctor_set(v_reuseFailAlloc_2230_, 0, v_a_2224_);
v___x_2229_ = v_reuseFailAlloc_2230_;
goto v_reusejp_2228_;
}
v_reusejp_2228_:
{
return v___x_2229_;
}
}
}
}
v___jp_2216_:
{
uint8_t v___x_2217_; 
v___x_2217_ = lean_nat_dec_eq(v_b_2195_, v_ns_2214_);
if (v___x_2217_ == 0)
{
uint8_t v___x_2218_; 
v___x_2218_ = lean_nat_dec_lt(v___x_2215_, v_b_2195_);
if (v___x_2218_ == 0)
{
lean_dec(v___x_2215_);
v_a_2201_ = v_b_2195_;
goto v___jp_2200_;
}
else
{
lean_dec(v_b_2195_);
v_a_2201_ = v___x_2215_;
goto v___jp_2200_;
}
}
else
{
lean_dec(v_b_2195_);
v_a_2201_ = v___x_2215_;
goto v___jp_2200_;
}
}
}
else
{
lean_object* v_a_2232_; lean_object* v___x_2234_; uint8_t v_isShared_2235_; uint8_t v_isSharedCheck_2239_; 
lean_dec(v___x_2206_);
lean_dec(v_i_2196_);
lean_dec(v_b_2195_);
lean_dec_ref(v_pass_2193_);
v_a_2232_ = lean_ctor_get(v___x_2211_, 0);
v_isSharedCheck_2239_ = !lean_is_exclusive(v___x_2211_);
if (v_isSharedCheck_2239_ == 0)
{
v___x_2234_ = v___x_2211_;
v_isShared_2235_ = v_isSharedCheck_2239_;
goto v_resetjp_2233_;
}
else
{
lean_inc(v_a_2232_);
lean_dec(v___x_2211_);
v___x_2234_ = lean_box(0);
v_isShared_2235_ = v_isSharedCheck_2239_;
goto v_resetjp_2233_;
}
v_resetjp_2233_:
{
lean_object* v___x_2237_; 
if (v_isShared_2235_ == 0)
{
v___x_2237_ = v___x_2234_;
goto v_reusejp_2236_;
}
else
{
lean_object* v_reuseFailAlloc_2238_; 
v_reuseFailAlloc_2238_ = lean_alloc_ctor(1, 1, 0);
lean_ctor_set(v_reuseFailAlloc_2238_, 0, v_a_2232_);
v___x_2237_ = v_reuseFailAlloc_2238_;
goto v_reusejp_2236_;
}
v_reusejp_2236_:
{
return v___x_2237_;
}
}
}
}
v___jp_2200_:
{
lean_object* v___x_2202_; 
v___x_2202_ = lean_nat_add(v_i_2196_, v_step_2199_);
lean_dec(v_i_2196_);
v_b_2195_ = v_a_2201_;
v_i_2196_ = v___x_2202_;
goto _start;
}
}
}
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00Bench_Suite_measure_spec__0___redArg___boxed(lean_object* v_pass_2240_, lean_object* v_range_2241_, lean_object* v_b_2242_, lean_object* v_i_2243_, lean_object* v___y_2244_){
_start:
{
lean_object* v_res_2245_; 
v_res_2245_ = lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00Bench_Suite_measure_spec__0___redArg(v_pass_2240_, v_range_2241_, v_b_2242_, v_i_2243_);
lean_dec_ref(v_range_2241_);
return v_res_2245_;
}
}
static lean_object* _init_lp_competition_Bench_Suite_measure___boxed__const__1(void){
_start:
{
uint32_t v___x_2249_; lean_object* v___x_2250_; 
v___x_2249_ = 0;
v___x_2250_ = lean_box_uint32(v___x_2249_);
return v___x_2250_;
}
}
LEAN_EXPORT lean_object* lp_competition_Bench_Suite_measure(lean_object* v_c_2251_, lean_object* v_inner_2252_, lean_object* v_pass_2253_){
_start:
{
lean_object* v___x_2255_; lean_object* v___x_2256_; 
v___x_2255_ = lp_competition_Bench_Suite_measure___boxed__const__1;
lean_inc_ref(v_pass_2253_);
v___x_2256_ = lean_apply_2(v_pass_2253_, v___x_2255_, lean_box(0));
if (lean_obj_tag(v___x_2256_) == 0)
{
lean_object* v_a_2257_; lean_object* v___y_2259_; lean_object* v___y_2260_; lean_object* v___y_2261_; lean_object* v___y_2262_; lean_object* v_name_2273_; uint8_t v_timed_2274_; lean_object* v_ns_2276_; lean_object* v_ns_2281_; 
v_a_2257_ = lean_ctor_get(v___x_2256_, 0);
lean_inc(v_a_2257_);
lean_dec_ref_known(v___x_2256_, 1);
v_name_2273_ = lean_ctor_get(v_c_2251_, 0);
lean_inc_ref(v_name_2273_);
v_timed_2274_ = lean_ctor_get_uint8(v_c_2251_, sizeof(void*)*29);
lean_dec_ref(v_c_2251_);
v_ns_2281_ = lean_unsigned_to_nat(0u);
if (v_timed_2274_ == 0)
{
lean_dec_ref(v_pass_2253_);
lean_dec(v_inner_2252_);
v_ns_2276_ = v_ns_2281_;
goto v___jp_2275_;
}
else
{
lean_object* v___x_2282_; lean_object* v___x_2283_; lean_object* v___x_2284_; 
v___x_2282_ = lean_unsigned_to_nat(1u);
v___x_2283_ = lean_alloc_ctor(0, 3, 0);
lean_ctor_set(v___x_2283_, 0, v_ns_2281_);
lean_ctor_set(v___x_2283_, 1, v_inner_2252_);
lean_ctor_set(v___x_2283_, 2, v___x_2282_);
v___x_2284_ = lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00Bench_Suite_measure_spec__0___redArg(v_pass_2253_, v___x_2283_, v_ns_2281_, v_ns_2281_);
lean_dec_ref_known(v___x_2283_, 3);
if (lean_obj_tag(v___x_2284_) == 0)
{
lean_object* v_a_2285_; 
v_a_2285_ = lean_ctor_get(v___x_2284_, 0);
lean_inc(v_a_2285_);
lean_dec_ref_known(v___x_2284_, 1);
v_ns_2276_ = v_a_2285_;
goto v___jp_2275_;
}
else
{
lean_object* v_a_2286_; lean_object* v___x_2288_; uint8_t v_isShared_2289_; uint8_t v_isSharedCheck_2293_; 
lean_dec_ref(v_name_2273_);
lean_dec(v_a_2257_);
v_a_2286_ = lean_ctor_get(v___x_2284_, 0);
v_isSharedCheck_2293_ = !lean_is_exclusive(v___x_2284_);
if (v_isSharedCheck_2293_ == 0)
{
v___x_2288_ = v___x_2284_;
v_isShared_2289_ = v_isSharedCheck_2293_;
goto v_resetjp_2287_;
}
else
{
lean_inc(v_a_2286_);
lean_dec(v___x_2284_);
v___x_2288_ = lean_box(0);
v_isShared_2289_ = v_isSharedCheck_2293_;
goto v_resetjp_2287_;
}
v_resetjp_2287_:
{
lean_object* v___x_2291_; 
if (v_isShared_2289_ == 0)
{
v___x_2291_ = v___x_2288_;
goto v_reusejp_2290_;
}
else
{
lean_object* v_reuseFailAlloc_2292_; 
v_reuseFailAlloc_2292_ = lean_alloc_ctor(1, 1, 0);
lean_ctor_set(v_reuseFailAlloc_2292_, 0, v_a_2286_);
v___x_2291_ = v_reuseFailAlloc_2292_;
goto v_reusejp_2290_;
}
v_reusejp_2290_:
{
return v___x_2291_;
}
}
}
}
v___jp_2258_:
{
lean_object* v___x_2263_; lean_object* v___x_2264_; lean_object* v___x_2265_; lean_object* v___x_2266_; lean_object* v___x_2267_; uint32_t v___x_2268_; lean_object* v___x_2269_; lean_object* v___x_2270_; lean_object* v___x_2271_; lean_object* v___x_2272_; 
v___x_2263_ = lean_string_append(v___y_2261_, v___y_2262_);
v___x_2264_ = lean_string_append(v___x_2263_, v___y_2260_);
v___x_2265_ = l_Nat_reprFast(v___y_2259_);
v___x_2266_ = lean_string_append(v___x_2264_, v___x_2265_);
lean_dec_ref(v___x_2265_);
v___x_2267_ = lean_string_append(v___x_2266_, v___y_2260_);
v___x_2268_ = lean_unbox_uint32(v_a_2257_);
lean_dec(v_a_2257_);
v___x_2269_ = lean_uint32_to_nat(v___x_2268_);
v___x_2270_ = l_Nat_reprFast(v___x_2269_);
v___x_2271_ = lean_string_append(v___x_2267_, v___x_2270_);
lean_dec_ref(v___x_2270_);
v___x_2272_ = lp_batteries_IO_println___at___00Batteries_Tactic_Lint_lintCore_spec__4(v___x_2271_);
return v___x_2272_;
}
v___jp_2275_:
{
lean_object* v___x_2277_; lean_object* v___x_2278_; 
v___x_2277_ = ((lean_object*)(lp_competition_Bench_Suite_measure___closed__0));
v___x_2278_ = lean_string_append(v_name_2273_, v___x_2277_);
if (v_timed_2274_ == 0)
{
lean_object* v___x_2279_; 
v___x_2279_ = ((lean_object*)(lp_competition_Bench_Suite_measure___closed__1));
v___y_2259_ = v_ns_2276_;
v___y_2260_ = v___x_2277_;
v___y_2261_ = v___x_2278_;
v___y_2262_ = v___x_2279_;
goto v___jp_2258_;
}
else
{
lean_object* v___x_2280_; 
v___x_2280_ = ((lean_object*)(lp_competition_Bench_Suite_measure___closed__2));
v___y_2259_ = v_ns_2276_;
v___y_2260_ = v___x_2277_;
v___y_2261_ = v___x_2278_;
v___y_2262_ = v___x_2280_;
goto v___jp_2258_;
}
}
}
else
{
lean_object* v_a_2294_; lean_object* v___x_2296_; uint8_t v_isShared_2297_; uint8_t v_isSharedCheck_2301_; 
lean_dec_ref(v_pass_2253_);
lean_dec(v_inner_2252_);
lean_dec_ref(v_c_2251_);
v_a_2294_ = lean_ctor_get(v___x_2256_, 0);
v_isSharedCheck_2301_ = !lean_is_exclusive(v___x_2256_);
if (v_isSharedCheck_2301_ == 0)
{
v___x_2296_ = v___x_2256_;
v_isShared_2297_ = v_isSharedCheck_2301_;
goto v_resetjp_2295_;
}
else
{
lean_inc(v_a_2294_);
lean_dec(v___x_2256_);
v___x_2296_ = lean_box(0);
v_isShared_2297_ = v_isSharedCheck_2301_;
goto v_resetjp_2295_;
}
v_resetjp_2295_:
{
lean_object* v___x_2299_; 
if (v_isShared_2297_ == 0)
{
v___x_2299_ = v___x_2296_;
goto v_reusejp_2298_;
}
else
{
lean_object* v_reuseFailAlloc_2300_; 
v_reuseFailAlloc_2300_ = lean_alloc_ctor(1, 1, 0);
lean_ctor_set(v_reuseFailAlloc_2300_, 0, v_a_2294_);
v___x_2299_ = v_reuseFailAlloc_2300_;
goto v_reusejp_2298_;
}
v_reusejp_2298_:
{
return v___x_2299_;
}
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_Bench_Suite_measure___boxed(lean_object* v_c_2302_, lean_object* v_inner_2303_, lean_object* v_pass_2304_, lean_object* v_a_2305_){
_start:
{
lean_object* v_res_2306_; 
v_res_2306_ = lp_competition_Bench_Suite_measure(v_c_2302_, v_inner_2303_, v_pass_2304_);
return v_res_2306_;
}
}
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00Bench_Suite_measure_spec__0(lean_object* v_pass_2307_, lean_object* v_range_2308_, lean_object* v_b_2309_, lean_object* v_i_2310_, lean_object* v_hs_2311_, lean_object* v_hl_2312_){
_start:
{
lean_object* v___x_2314_; 
v___x_2314_ = lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00Bench_Suite_measure_spec__0___redArg(v_pass_2307_, v_range_2308_, v_b_2309_, v_i_2310_);
return v___x_2314_;
}
}
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00Bench_Suite_measure_spec__0___boxed(lean_object* v_pass_2315_, lean_object* v_range_2316_, lean_object* v_b_2317_, lean_object* v_i_2318_, lean_object* v_hs_2319_, lean_object* v_hl_2320_, lean_object* v___y_2321_){
_start:
{
lean_object* v_res_2322_; 
v_res_2322_ = lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00Bench_Suite_measure_spec__0(v_pass_2315_, v_range_2316_, v_b_2317_, v_i_2318_, v_hs_2319_, v_hl_2320_);
lean_dec_ref(v_range_2316_);
return v_res_2322_;
}
}
LEAN_EXPORT lean_object* lp_competition_Bench_Suite_runScalar___lam__0(lean_object* v_c_2323_, lean_object* v_i_2324_){
_start:
{
lean_object* v___x_2325_; lean_object* v___x_2326_; uint32_t v_a_2327_; uint32_t v___x_2328_; lean_object* v___x_2329_; lean_object* v___x_2330_; lean_object* v___x_2331_; 
v___x_2325_ = lean_unsigned_to_nat(0u);
v___x_2326_ = lean_unsigned_to_nat(31u);
lean_inc_ref(v_c_2323_);
v_a_2327_ = lp_competition_Bench_Suite_element(v_c_2323_, v_i_2324_, v___x_2325_, v___x_2326_);
v___x_2328_ = lp_competition_Bench_Suite_partner(v_c_2323_, v_i_2324_, v_a_2327_);
v___x_2329_ = lean_box_uint32(v_a_2327_);
v___x_2330_ = lean_box_uint32(v___x_2328_);
v___x_2331_ = lean_alloc_ctor(0, 2, 0);
lean_ctor_set(v___x_2331_, 0, v___x_2329_);
lean_ctor_set(v___x_2331_, 1, v___x_2330_);
return v___x_2331_;
}
}
LEAN_EXPORT lean_object* lp_competition_Bench_Suite_runScalar___lam__0___boxed(lean_object* v_c_2332_, lean_object* v_i_2333_){
_start:
{
lean_object* v_res_2334_; 
v_res_2334_ = lp_competition_Bench_Suite_runScalar___lam__0(v_c_2332_, v_i_2333_);
lean_dec(v_i_2333_);
return v_res_2334_;
}
}
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00Bench_Suite_runScalar_spec__0(lean_object* v_kernel_2335_, lean_object* v_as_2336_, size_t v_sz_2337_, size_t v_i_2338_, uint32_t v_b_2339_){
_start:
{
uint8_t v___x_2341_; 
v___x_2341_ = lean_usize_dec_lt(v_i_2338_, v_sz_2337_);
if (v___x_2341_ == 0)
{
lean_object* v___x_2342_; lean_object* v___x_2343_; 
lean_dec_ref(v_kernel_2335_);
v___x_2342_ = lean_box_uint32(v_b_2339_);
v___x_2343_ = lean_alloc_ctor(0, 1, 0);
lean_ctor_set(v___x_2343_, 0, v___x_2342_);
return v___x_2343_;
}
else
{
lean_object* v_a_2344_; lean_object* v_fst_2345_; lean_object* v_snd_2346_; lean_object* v___x_2347_; uint32_t v___x_2348_; uint32_t v___x_2349_; uint32_t v___x_2350_; uint32_t v___x_2351_; size_t v___x_2352_; size_t v___x_2353_; 
v_a_2344_ = lean_array_uget_borrowed(v_as_2336_, v_i_2338_);
v_fst_2345_ = lean_ctor_get(v_a_2344_, 0);
v_snd_2346_ = lean_ctor_get(v_a_2344_, 1);
lean_inc_ref(v_kernel_2335_);
lean_inc(v_snd_2346_);
lean_inc(v_fst_2345_);
v___x_2347_ = lean_apply_2(v_kernel_2335_, v_fst_2345_, v_snd_2346_);
v___x_2348_ = lean_unbox_uint32(v___x_2347_);
lean_dec(v___x_2347_);
v___x_2349_ = lean_uint32_xor(v_b_2339_, v___x_2348_);
v___x_2350_ = 16777619;
v___x_2351_ = lean_uint32_mul(v___x_2349_, v___x_2350_);
v___x_2352_ = ((size_t)1ULL);
v___x_2353_ = lean_usize_add(v_i_2338_, v___x_2352_);
v_i_2338_ = v___x_2353_;
v_b_2339_ = v___x_2351_;
goto _start;
}
}
}
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00Bench_Suite_runScalar_spec__0___boxed(lean_object* v_kernel_2355_, lean_object* v_as_2356_, lean_object* v_sz_2357_, lean_object* v_i_2358_, lean_object* v_b_2359_, lean_object* v___y_2360_){
_start:
{
size_t v_sz_boxed_2361_; size_t v_i_boxed_2362_; uint32_t v_b_boxed_2363_; lean_object* v_res_2364_; 
v_sz_boxed_2361_ = lean_unbox_usize(v_sz_2357_);
lean_dec(v_sz_2357_);
v_i_boxed_2362_ = lean_unbox_usize(v_i_2358_);
lean_dec(v_i_2358_);
v_b_boxed_2363_ = lean_unbox_uint32(v_b_2359_);
lean_dec(v_b_2359_);
v_res_2364_ = lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00Bench_Suite_runScalar_spec__0(v_kernel_2355_, v_as_2356_, v_sz_boxed_2361_, v_i_boxed_2362_, v_b_boxed_2363_);
lean_dec_ref(v_as_2356_);
return v_res_2364_;
}
}
LEAN_EXPORT lean_object* lp_competition_Bench_Suite_runScalar___lam__1(lean_object* v_xs_2365_, lean_object* v_kernel_2366_, uint32_t v_seed_2367_){
_start:
{
size_t v_sz_2369_; size_t v___x_2370_; lean_object* v___x_2371_; 
v_sz_2369_ = lean_array_size(v_xs_2365_);
v___x_2370_ = ((size_t)0ULL);
v___x_2371_ = lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00Bench_Suite_runScalar_spec__0(v_kernel_2366_, v_xs_2365_, v_sz_2369_, v___x_2370_, v_seed_2367_);
return v___x_2371_;
}
}
LEAN_EXPORT lean_object* lp_competition_Bench_Suite_runScalar___lam__1___boxed(lean_object* v_xs_2372_, lean_object* v_kernel_2373_, lean_object* v_seed_2374_, lean_object* v___y_2375_){
_start:
{
uint32_t v_seed_boxed_2376_; lean_object* v_res_2377_; 
v_seed_boxed_2376_ = lean_unbox_uint32(v_seed_2374_);
lean_dec(v_seed_2374_);
v_res_2377_ = lp_competition_Bench_Suite_runScalar___lam__1(v_xs_2372_, v_kernel_2373_, v_seed_boxed_2376_);
lean_dec_ref(v_xs_2372_);
return v_res_2377_;
}
}
LEAN_EXPORT lean_object* lp_competition_Bench_Suite_runScalar(lean_object* v_c_2378_, lean_object* v_inner_2379_, lean_object* v_kernel_2380_){
_start:
{
lean_object* v_work_2382_; lean_object* v___f_2383_; lean_object* v_xs_2384_; lean_object* v___f_2385_; lean_object* v___x_2386_; 
v_work_2382_ = lean_ctor_get(v_c_2378_, 28);
lean_inc_ref(v_c_2378_);
v___f_2383_ = lean_alloc_closure((void*)(lp_competition_Bench_Suite_runScalar___lam__0___boxed), 2, 1);
lean_closure_set(v___f_2383_, 0, v_c_2378_);
lean_inc(v_work_2382_);
v_xs_2384_ = l_Array_ofFn___redArg(v_work_2382_, v___f_2383_);
v___f_2385_ = lean_alloc_closure((void*)(lp_competition_Bench_Suite_runScalar___lam__1___boxed), 4, 2);
lean_closure_set(v___f_2385_, 0, v_xs_2384_);
lean_closure_set(v___f_2385_, 1, v_kernel_2380_);
v___x_2386_ = lp_competition_Bench_Suite_measure(v_c_2378_, v_inner_2379_, v___f_2385_);
return v___x_2386_;
}
}
LEAN_EXPORT lean_object* lp_competition_Bench_Suite_runScalar___boxed(lean_object* v_c_2387_, lean_object* v_inner_2388_, lean_object* v_kernel_2389_, lean_object* v_a_2390_){
_start:
{
lean_object* v_res_2391_; 
v_res_2391_ = lp_competition_Bench_Suite_runScalar(v_c_2387_, v_inner_2388_, v_kernel_2389_);
return v_res_2391_;
}
}
LEAN_EXPORT uint32_t lp_competition_Bench_Suite_runSum___lam__0(lean_object* v_b_2392_, lean_object* v_length_2393_, lean_object* v_c_2394_, lean_object* v_i_2395_){
_start:
{
lean_object* v___x_2396_; lean_object* v___x_2397_; lean_object* v___x_2398_; uint32_t v___x_2399_; 
v___x_2396_ = lean_nat_mul(v_b_2392_, v_length_2393_);
v___x_2397_ = lean_nat_add(v___x_2396_, v_i_2395_);
lean_dec(v___x_2396_);
v___x_2398_ = lean_unsigned_to_nat(0u);
v___x_2399_ = lp_competition_Bench_Suite_element(v_c_2394_, v___x_2397_, v___x_2398_, v_length_2393_);
lean_dec(v___x_2397_);
return v___x_2399_;
}
}
LEAN_EXPORT lean_object* lp_competition_Bench_Suite_runSum___lam__0___boxed(lean_object* v_b_2400_, lean_object* v_length_2401_, lean_object* v_c_2402_, lean_object* v_i_2403_){
_start:
{
uint32_t v_res_2404_; lean_object* v_r_2405_; 
v_res_2404_ = lp_competition_Bench_Suite_runSum___lam__0(v_b_2400_, v_length_2401_, v_c_2402_, v_i_2403_);
lean_dec(v_i_2403_);
lean_dec(v_length_2401_);
lean_dec(v_b_2400_);
v_r_2405_ = lean_box_uint32(v_res_2404_);
return v_r_2405_;
}
}
LEAN_EXPORT lean_object* lp_competition_Bench_Suite_runSum___lam__1(lean_object* v_length_2406_, lean_object* v_c_2407_, lean_object* v_b_2408_){
_start:
{
lean_object* v___f_2409_; lean_object* v___x_2410_; 
lean_inc(v_length_2406_);
v___f_2409_ = lean_alloc_closure((void*)(lp_competition_Bench_Suite_runSum___lam__0___boxed), 4, 3);
lean_closure_set(v___f_2409_, 0, v_b_2408_);
lean_closure_set(v___f_2409_, 1, v_length_2406_);
lean_closure_set(v___f_2409_, 2, v_c_2407_);
v___x_2410_ = l_Array_ofFn___redArg(v_length_2406_, v___f_2409_);
return v___x_2410_;
}
}
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00Bench_Suite_runSum_spec__0(lean_object* v_c_2411_, lean_object* v_kernel_2412_, lean_object* v_as_2413_, size_t v_sz_2414_, size_t v_i_2415_, uint32_t v_b_2416_){
_start:
{
uint8_t v___x_2418_; 
v___x_2418_ = lean_usize_dec_lt(v_i_2415_, v_sz_2414_);
if (v___x_2418_ == 0)
{
lean_object* v___x_2419_; lean_object* v___x_2420_; 
lean_dec_ref(v_kernel_2412_);
lean_dec_ref(v_c_2411_);
v___x_2419_ = lean_box_uint32(v_b_2416_);
v___x_2420_ = lean_alloc_ctor(0, 1, 0);
lean_ctor_set(v___x_2420_, 0, v___x_2419_);
return v___x_2420_;
}
else
{
lean_object* v_length_2421_; lean_object* v_a_2422_; lean_object* v___x_2423_; uint32_t v___x_2424_; uint32_t v___x_2425_; uint32_t v___x_2426_; uint32_t v___x_2427_; size_t v___x_2428_; size_t v___x_2429_; 
v_length_2421_ = lean_ctor_get(v_c_2411_, 23);
v_a_2422_ = lean_array_uget_borrowed(v_as_2413_, v_i_2415_);
lean_inc_ref(v_kernel_2412_);
lean_inc(v_a_2422_);
lean_inc(v_length_2421_);
v___x_2423_ = lean_apply_2(v_kernel_2412_, v_length_2421_, v_a_2422_);
v___x_2424_ = lean_unbox_uint32(v___x_2423_);
lean_dec(v___x_2423_);
v___x_2425_ = lean_uint32_xor(v_b_2416_, v___x_2424_);
v___x_2426_ = 16777619;
v___x_2427_ = lean_uint32_mul(v___x_2425_, v___x_2426_);
v___x_2428_ = ((size_t)1ULL);
v___x_2429_ = lean_usize_add(v_i_2415_, v___x_2428_);
v_i_2415_ = v___x_2429_;
v_b_2416_ = v___x_2427_;
goto _start;
}
}
}
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00Bench_Suite_runSum_spec__0___boxed(lean_object* v_c_2431_, lean_object* v_kernel_2432_, lean_object* v_as_2433_, lean_object* v_sz_2434_, lean_object* v_i_2435_, lean_object* v_b_2436_, lean_object* v___y_2437_){
_start:
{
size_t v_sz_boxed_2438_; size_t v_i_boxed_2439_; uint32_t v_b_boxed_2440_; lean_object* v_res_2441_; 
v_sz_boxed_2438_ = lean_unbox_usize(v_sz_2434_);
lean_dec(v_sz_2434_);
v_i_boxed_2439_ = lean_unbox_usize(v_i_2435_);
lean_dec(v_i_2435_);
v_b_boxed_2440_ = lean_unbox_uint32(v_b_2436_);
lean_dec(v_b_2436_);
v_res_2441_ = lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00Bench_Suite_runSum_spec__0(v_c_2431_, v_kernel_2432_, v_as_2433_, v_sz_boxed_2438_, v_i_boxed_2439_, v_b_boxed_2440_);
lean_dec_ref(v_as_2433_);
return v_res_2441_;
}
}
LEAN_EXPORT lean_object* lp_competition_Bench_Suite_runSum___lam__2(lean_object* v_xs_2442_, lean_object* v_c_2443_, lean_object* v_kernel_2444_, uint32_t v_seed_2445_){
_start:
{
size_t v_sz_2447_; size_t v___x_2448_; lean_object* v___x_2449_; 
v_sz_2447_ = lean_array_size(v_xs_2442_);
v___x_2448_ = ((size_t)0ULL);
v___x_2449_ = lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00Bench_Suite_runSum_spec__0(v_c_2443_, v_kernel_2444_, v_xs_2442_, v_sz_2447_, v___x_2448_, v_seed_2445_);
return v___x_2449_;
}
}
LEAN_EXPORT lean_object* lp_competition_Bench_Suite_runSum___lam__2___boxed(lean_object* v_xs_2450_, lean_object* v_c_2451_, lean_object* v_kernel_2452_, lean_object* v_seed_2453_, lean_object* v___y_2454_){
_start:
{
uint32_t v_seed_boxed_2455_; lean_object* v_res_2456_; 
v_seed_boxed_2455_ = lean_unbox_uint32(v_seed_2453_);
lean_dec(v_seed_2453_);
v_res_2456_ = lp_competition_Bench_Suite_runSum___lam__2(v_xs_2450_, v_c_2451_, v_kernel_2452_, v_seed_boxed_2455_);
lean_dec_ref(v_xs_2450_);
return v_res_2456_;
}
}
LEAN_EXPORT lean_object* lp_competition_Bench_Suite_runSum(lean_object* v_c_2457_, lean_object* v_inner_2458_, lean_object* v_kernel_2459_){
_start:
{
lean_object* v_length_2461_; lean_object* v_batch_2462_; lean_object* v___f_2463_; lean_object* v_xs_2464_; lean_object* v___f_2465_; lean_object* v___x_2466_; 
v_length_2461_ = lean_ctor_get(v_c_2457_, 23);
v_batch_2462_ = lean_ctor_get(v_c_2457_, 27);
lean_inc_ref_n(v_c_2457_, 2);
lean_inc(v_length_2461_);
v___f_2463_ = lean_alloc_closure((void*)(lp_competition_Bench_Suite_runSum___lam__1), 3, 2);
lean_closure_set(v___f_2463_, 0, v_length_2461_);
lean_closure_set(v___f_2463_, 1, v_c_2457_);
lean_inc(v_batch_2462_);
v_xs_2464_ = l_Array_ofFn___redArg(v_batch_2462_, v___f_2463_);
v___f_2465_ = lean_alloc_closure((void*)(lp_competition_Bench_Suite_runSum___lam__2___boxed), 5, 3);
lean_closure_set(v___f_2465_, 0, v_xs_2464_);
lean_closure_set(v___f_2465_, 1, v_c_2457_);
lean_closure_set(v___f_2465_, 2, v_kernel_2459_);
v___x_2466_ = lp_competition_Bench_Suite_measure(v_c_2457_, v_inner_2458_, v___f_2465_);
return v___x_2466_;
}
}
LEAN_EXPORT lean_object* lp_competition_Bench_Suite_runSum___boxed(lean_object* v_c_2467_, lean_object* v_inner_2468_, lean_object* v_kernel_2469_, lean_object* v_a_2470_){
_start:
{
lean_object* v_res_2471_; 
v_res_2471_ = lp_competition_Bench_Suite_runSum(v_c_2467_, v_inner_2468_, v_kernel_2469_);
return v_res_2471_;
}
}
LEAN_EXPORT uint32_t lp_competition_Bench_Suite_runBmm___lam__0(lean_object* v_c_2472_, lean_object* v_p_2473_, lean_object* v_i_2474_){
_start:
{
lean_object* v___x_2475_; uint32_t v___x_2476_; 
v___x_2475_ = lean_unsigned_to_nat(1u);
v___x_2476_ = lp_competition_Bench_Suite_element(v_c_2472_, v_i_2474_, v___x_2475_, v_p_2473_);
return v___x_2476_;
}
}
LEAN_EXPORT lean_object* lp_competition_Bench_Suite_runBmm___lam__0___boxed(lean_object* v_c_2477_, lean_object* v_p_2478_, lean_object* v_i_2479_){
_start:
{
uint32_t v_res_2480_; lean_object* v_r_2481_; 
v_res_2480_ = lp_competition_Bench_Suite_runBmm___lam__0(v_c_2477_, v_p_2478_, v_i_2479_);
lean_dec(v_i_2479_);
lean_dec(v_p_2478_);
v_r_2481_ = lean_box_uint32(v_res_2480_);
return v_r_2481_;
}
}
LEAN_EXPORT uint32_t lp_competition_Bench_Suite_runBmm___lam__1(lean_object* v_c_2482_, lean_object* v_n_2483_, lean_object* v_i_2484_){
_start:
{
lean_object* v___x_2485_; uint32_t v___x_2486_; 
v___x_2485_ = lean_unsigned_to_nat(0u);
v___x_2486_ = lp_competition_Bench_Suite_element(v_c_2482_, v_i_2484_, v___x_2485_, v_n_2483_);
return v___x_2486_;
}
}
LEAN_EXPORT lean_object* lp_competition_Bench_Suite_runBmm___lam__1___boxed(lean_object* v_c_2487_, lean_object* v_n_2488_, lean_object* v_i_2489_){
_start:
{
uint32_t v_res_2490_; lean_object* v_r_2491_; 
v_res_2490_ = lp_competition_Bench_Suite_runBmm___lam__1(v_c_2487_, v_n_2488_, v_i_2489_);
lean_dec(v_i_2489_);
lean_dec(v_n_2488_);
v_r_2491_ = lean_box_uint32(v_res_2490_);
return v_r_2491_;
}
}
LEAN_EXPORT lean_object* lp_competition_Bench_Suite_runBmm___lam__2(lean_object* v_kernel_2492_, lean_object* v_batch_2493_, lean_object* v_m_2494_, lean_object* v_n_2495_, lean_object* v_p_2496_, lean_object* v_a_2497_, lean_object* v_b_2498_, uint32_t v_seed_2499_){
_start:
{
lean_object* v___x_2501_; size_t v_sz_2502_; size_t v___x_2503_; lean_object* v___x_2504_; 
v___x_2501_ = lean_apply_6(v_kernel_2492_, v_batch_2493_, v_m_2494_, v_n_2495_, v_p_2496_, v_a_2497_, v_b_2498_);
v_sz_2502_ = lean_array_size(v___x_2501_);
v___x_2503_ = ((size_t)0ULL);
v___x_2504_ = lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00Bench_runBmm_spec__0(v___x_2501_, v_sz_2502_, v___x_2503_, v_seed_2499_);
lean_dec_ref(v___x_2501_);
return v___x_2504_;
}
}
LEAN_EXPORT lean_object* lp_competition_Bench_Suite_runBmm___lam__2___boxed(lean_object* v_kernel_2505_, lean_object* v_batch_2506_, lean_object* v_m_2507_, lean_object* v_n_2508_, lean_object* v_p_2509_, lean_object* v_a_2510_, lean_object* v_b_2511_, lean_object* v_seed_2512_, lean_object* v___y_2513_){
_start:
{
uint32_t v_seed_boxed_2514_; lean_object* v_res_2515_; 
v_seed_boxed_2514_ = lean_unbox_uint32(v_seed_2512_);
lean_dec(v_seed_2512_);
v_res_2515_ = lp_competition_Bench_Suite_runBmm___lam__2(v_kernel_2505_, v_batch_2506_, v_m_2507_, v_n_2508_, v_p_2509_, v_a_2510_, v_b_2511_, v_seed_boxed_2514_);
return v_res_2515_;
}
}
LEAN_EXPORT lean_object* lp_competition_Bench_Suite_runBmm(lean_object* v_c_2516_, lean_object* v_inner_2517_, lean_object* v_kernel_2518_){
_start:
{
lean_object* v_m_2520_; lean_object* v_n_2521_; lean_object* v_p_2522_; lean_object* v_batch_2523_; lean_object* v___f_2524_; lean_object* v___f_2525_; lean_object* v___x_2526_; lean_object* v___x_2527_; lean_object* v_a_2528_; lean_object* v___x_2529_; lean_object* v___x_2530_; lean_object* v_b_2531_; lean_object* v___f_2532_; lean_object* v___x_2533_; 
v_m_2520_ = lean_ctor_get(v_c_2516_, 24);
v_n_2521_ = lean_ctor_get(v_c_2516_, 25);
v_p_2522_ = lean_ctor_get(v_c_2516_, 26);
v_batch_2523_ = lean_ctor_get(v_c_2516_, 27);
lean_inc_n(v_p_2522_, 2);
lean_inc_ref_n(v_c_2516_, 2);
v___f_2524_ = lean_alloc_closure((void*)(lp_competition_Bench_Suite_runBmm___lam__0___boxed), 3, 2);
lean_closure_set(v___f_2524_, 0, v_c_2516_);
lean_closure_set(v___f_2524_, 1, v_p_2522_);
lean_inc_n(v_n_2521_, 2);
v___f_2525_ = lean_alloc_closure((void*)(lp_competition_Bench_Suite_runBmm___lam__1___boxed), 3, 2);
lean_closure_set(v___f_2525_, 0, v_c_2516_);
lean_closure_set(v___f_2525_, 1, v_n_2521_);
v___x_2526_ = lean_nat_mul(v_batch_2523_, v_m_2520_);
v___x_2527_ = lean_nat_mul(v___x_2526_, v_n_2521_);
lean_dec(v___x_2526_);
v_a_2528_ = l_Array_ofFn___redArg(v___x_2527_, v___f_2525_);
v___x_2529_ = lean_nat_mul(v_batch_2523_, v_n_2521_);
v___x_2530_ = lean_nat_mul(v___x_2529_, v_p_2522_);
lean_dec(v___x_2529_);
v_b_2531_ = l_Array_ofFn___redArg(v___x_2530_, v___f_2524_);
lean_inc(v_m_2520_);
lean_inc(v_batch_2523_);
v___f_2532_ = lean_alloc_closure((void*)(lp_competition_Bench_Suite_runBmm___lam__2___boxed), 9, 7);
lean_closure_set(v___f_2532_, 0, v_kernel_2518_);
lean_closure_set(v___f_2532_, 1, v_batch_2523_);
lean_closure_set(v___f_2532_, 2, v_m_2520_);
lean_closure_set(v___f_2532_, 3, v_n_2521_);
lean_closure_set(v___f_2532_, 4, v_p_2522_);
lean_closure_set(v___f_2532_, 5, v_a_2528_);
lean_closure_set(v___f_2532_, 6, v_b_2531_);
v___x_2533_ = lp_competition_Bench_Suite_measure(v_c_2516_, v_inner_2517_, v___f_2532_);
return v___x_2533_;
}
}
LEAN_EXPORT lean_object* lp_competition_Bench_Suite_runBmm___boxed(lean_object* v_c_2534_, lean_object* v_inner_2535_, lean_object* v_kernel_2536_, lean_object* v_a_2537_){
_start:
{
lean_object* v_res_2538_; 
v_res_2538_ = lp_competition_Bench_Suite_runBmm(v_c_2534_, v_inner_2535_, v_kernel_2536_);
return v_res_2538_;
}
}
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00Bench_Suite_run_spec__0(lean_object* v_a_2546_, lean_object* v_bmm_2547_, lean_object* v_sum_2548_, lean_object* v_mul_2549_, lean_object* v_add_2550_, lean_object* v_as_2551_, size_t v_sz_2552_, size_t v_i_2553_, lean_object* v_b_2554_){
_start:
{
lean_object* v_a_2557_; uint8_t v___x_2561_; 
v___x_2561_ = lean_usize_dec_lt(v_i_2553_, v_sz_2552_);
if (v___x_2561_ == 0)
{
lean_object* v___x_2562_; 
lean_dec_ref(v_add_2550_);
lean_dec_ref(v_mul_2549_);
lean_dec_ref(v_sum_2548_);
lean_dec_ref(v_bmm_2547_);
lean_dec(v_a_2546_);
v___x_2562_ = lean_alloc_ctor(0, 1, 0);
lean_ctor_set(v___x_2562_, 0, v_b_2554_);
return v___x_2562_;
}
else
{
lean_object* v_a_2563_; lean_object* v_length_2570_; lean_object* v_work_2571_; lean_object* v___x_2572_; uint8_t v___y_2574_; lean_object* v___x_2601_; uint8_t v___x_2602_; 
v_a_2563_ = lean_array_uget_borrowed(v_as_2551_, v_i_2553_);
v_length_2570_ = lean_ctor_get(v_a_2563_, 23);
v_work_2571_ = lean_ctor_get(v_a_2563_, 28);
v___x_2572_ = lean_box(0);
v___x_2601_ = lean_unsigned_to_nat(0u);
v___x_2602_ = lean_nat_dec_eq(v_work_2571_, v___x_2601_);
if (v___x_2602_ == 0)
{
uint8_t v___x_2603_; 
v___x_2603_ = lean_nat_dec_eq(v_length_2570_, v___x_2601_);
v___y_2574_ = v___x_2603_;
goto v___jp_2573_;
}
else
{
v___y_2574_ = v___x_2602_;
goto v___jp_2573_;
}
v___jp_2564_:
{
lean_object* v_name_2565_; lean_object* v___x_2566_; lean_object* v___x_2567_; lean_object* v___x_2568_; lean_object* v___x_2569_; 
v_name_2565_ = lean_ctor_get(v_a_2563_, 0);
v___x_2566_ = ((lean_object*)(lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00Bench_Suite_run_spec__0___closed__0));
v___x_2567_ = lean_string_append(v___x_2566_, v_name_2565_);
v___x_2568_ = lean_alloc_ctor(18, 1, 0);
lean_ctor_set(v___x_2568_, 0, v___x_2567_);
v___x_2569_ = lean_alloc_ctor(1, 1, 0);
lean_ctor_set(v___x_2569_, 0, v___x_2568_);
return v___x_2569_;
}
v___jp_2573_:
{
if (v___y_2574_ == 0)
{
lean_object* v_kernel_2575_; lean_object* v_zeroCluster_2576_; lean_object* v_subBlock_2577_; lean_object* v_specPeriod_2578_; lean_object* v_specBurst_2579_; lean_object* v_batch_2580_; lean_object* v___x_2581_; uint8_t v___x_2582_; 
v_kernel_2575_ = lean_ctor_get(v_a_2563_, 1);
v_zeroCluster_2576_ = lean_ctor_get(v_a_2563_, 12);
v_subBlock_2577_ = lean_ctor_get(v_a_2563_, 15);
v_specPeriod_2578_ = lean_ctor_get(v_a_2563_, 18);
v_specBurst_2579_ = lean_ctor_get(v_a_2563_, 19);
v_batch_2580_ = lean_ctor_get(v_a_2563_, 27);
v___x_2581_ = lean_unsigned_to_nat(0u);
v___x_2582_ = lean_nat_dec_eq(v_batch_2580_, v___x_2581_);
if (v___x_2582_ == 0)
{
uint8_t v___x_2583_; 
v___x_2583_ = lean_nat_dec_eq(v_specPeriod_2578_, v___x_2581_);
if (v___x_2583_ == 0)
{
uint8_t v___x_2584_; 
v___x_2584_ = lean_nat_dec_eq(v_specBurst_2579_, v___x_2581_);
if (v___x_2584_ == 0)
{
uint8_t v___x_2585_; 
v___x_2585_ = lean_nat_dec_eq(v_zeroCluster_2576_, v___x_2581_);
if (v___x_2585_ == 0)
{
uint8_t v___x_2586_; 
v___x_2586_ = lean_nat_dec_eq(v_subBlock_2577_, v___x_2581_);
if (v___x_2586_ == 0)
{
lean_object* v___x_2587_; uint8_t v___x_2588_; 
v___x_2587_ = ((lean_object*)(lp_competition_Bench_Suite_partner___closed__0));
v___x_2588_ = lean_string_dec_eq(v_kernel_2575_, v___x_2587_);
if (v___x_2588_ == 0)
{
lean_object* v___x_2589_; uint8_t v___x_2590_; 
v___x_2589_ = ((lean_object*)(lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00Bench_Suite_run_spec__0___closed__1));
v___x_2590_ = lean_string_dec_eq(v_kernel_2575_, v___x_2589_);
if (v___x_2590_ == 0)
{
lean_object* v___x_2591_; uint8_t v___x_2592_; 
v___x_2591_ = ((lean_object*)(lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00Bench_Suite_run_spec__0___closed__2));
v___x_2592_ = lean_string_dec_eq(v_kernel_2575_, v___x_2591_);
if (v___x_2592_ == 0)
{
lean_object* v___x_2593_; uint8_t v___x_2594_; 
v___x_2593_ = ((lean_object*)(lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00Bench_Suite_run_spec__0___closed__3));
v___x_2594_ = lean_string_dec_eq(v_kernel_2575_, v___x_2593_);
if (v___x_2594_ == 0)
{
lean_object* v___x_2595_; lean_object* v___x_2596_; 
lean_dec_ref(v_add_2550_);
lean_dec_ref(v_mul_2549_);
lean_dec_ref(v_sum_2548_);
lean_dec_ref(v_bmm_2547_);
lean_dec(v_a_2546_);
v___x_2595_ = ((lean_object*)(lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00Bench_Suite_run_spec__0___closed__5));
v___x_2596_ = lean_alloc_ctor(1, 1, 0);
lean_ctor_set(v___x_2596_, 0, v___x_2595_);
return v___x_2596_;
}
else
{
lean_object* v___x_2597_; 
lean_inc_ref(v_bmm_2547_);
lean_inc(v_a_2546_);
lean_inc(v_a_2563_);
v___x_2597_ = lp_competition_Bench_Suite_runBmm(v_a_2563_, v_a_2546_, v_bmm_2547_);
if (lean_obj_tag(v___x_2597_) == 0)
{
lean_dec_ref_known(v___x_2597_, 1);
v_a_2557_ = v___x_2572_;
goto v___jp_2556_;
}
else
{
lean_dec_ref(v_add_2550_);
lean_dec_ref(v_mul_2549_);
lean_dec_ref(v_sum_2548_);
lean_dec_ref(v_bmm_2547_);
lean_dec(v_a_2546_);
return v___x_2597_;
}
}
}
else
{
lean_object* v___x_2598_; 
lean_inc_ref(v_sum_2548_);
lean_inc(v_a_2546_);
lean_inc(v_a_2563_);
v___x_2598_ = lp_competition_Bench_Suite_runSum(v_a_2563_, v_a_2546_, v_sum_2548_);
if (lean_obj_tag(v___x_2598_) == 0)
{
lean_dec_ref_known(v___x_2598_, 1);
v_a_2557_ = v___x_2572_;
goto v___jp_2556_;
}
else
{
lean_dec_ref(v_add_2550_);
lean_dec_ref(v_mul_2549_);
lean_dec_ref(v_sum_2548_);
lean_dec_ref(v_bmm_2547_);
lean_dec(v_a_2546_);
return v___x_2598_;
}
}
}
else
{
lean_object* v___x_2599_; 
lean_inc_ref(v_mul_2549_);
lean_inc(v_a_2546_);
lean_inc(v_a_2563_);
v___x_2599_ = lp_competition_Bench_Suite_runScalar(v_a_2563_, v_a_2546_, v_mul_2549_);
if (lean_obj_tag(v___x_2599_) == 0)
{
lean_dec_ref_known(v___x_2599_, 1);
v_a_2557_ = v___x_2572_;
goto v___jp_2556_;
}
else
{
lean_dec_ref(v_add_2550_);
lean_dec_ref(v_mul_2549_);
lean_dec_ref(v_sum_2548_);
lean_dec_ref(v_bmm_2547_);
lean_dec(v_a_2546_);
return v___x_2599_;
}
}
}
else
{
lean_object* v___x_2600_; 
lean_inc_ref(v_add_2550_);
lean_inc(v_a_2546_);
lean_inc(v_a_2563_);
v___x_2600_ = lp_competition_Bench_Suite_runScalar(v_a_2563_, v_a_2546_, v_add_2550_);
if (lean_obj_tag(v___x_2600_) == 0)
{
lean_dec_ref_known(v___x_2600_, 1);
v_a_2557_ = v___x_2572_;
goto v___jp_2556_;
}
else
{
lean_dec_ref(v_add_2550_);
lean_dec_ref(v_mul_2549_);
lean_dec_ref(v_sum_2548_);
lean_dec_ref(v_bmm_2547_);
lean_dec(v_a_2546_);
return v___x_2600_;
}
}
}
else
{
lean_dec_ref(v_add_2550_);
lean_dec_ref(v_mul_2549_);
lean_dec_ref(v_sum_2548_);
lean_dec_ref(v_bmm_2547_);
lean_dec(v_a_2546_);
goto v___jp_2564_;
}
}
else
{
lean_dec_ref(v_add_2550_);
lean_dec_ref(v_mul_2549_);
lean_dec_ref(v_sum_2548_);
lean_dec_ref(v_bmm_2547_);
lean_dec(v_a_2546_);
goto v___jp_2564_;
}
}
else
{
lean_dec_ref(v_add_2550_);
lean_dec_ref(v_mul_2549_);
lean_dec_ref(v_sum_2548_);
lean_dec_ref(v_bmm_2547_);
lean_dec(v_a_2546_);
goto v___jp_2564_;
}
}
else
{
lean_dec_ref(v_add_2550_);
lean_dec_ref(v_mul_2549_);
lean_dec_ref(v_sum_2548_);
lean_dec_ref(v_bmm_2547_);
lean_dec(v_a_2546_);
goto v___jp_2564_;
}
}
else
{
lean_dec_ref(v_add_2550_);
lean_dec_ref(v_mul_2549_);
lean_dec_ref(v_sum_2548_);
lean_dec_ref(v_bmm_2547_);
lean_dec(v_a_2546_);
goto v___jp_2564_;
}
}
else
{
lean_dec_ref(v_add_2550_);
lean_dec_ref(v_mul_2549_);
lean_dec_ref(v_sum_2548_);
lean_dec_ref(v_bmm_2547_);
lean_dec(v_a_2546_);
goto v___jp_2564_;
}
}
}
v___jp_2556_:
{
size_t v___x_2558_; size_t v___x_2559_; 
v___x_2558_ = ((size_t)1ULL);
v___x_2559_ = lean_usize_add(v_i_2553_, v___x_2558_);
v_i_2553_ = v___x_2559_;
v_b_2554_ = v_a_2557_;
goto _start;
}
}
}
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00Bench_Suite_run_spec__0___boxed(lean_object* v_a_2604_, lean_object* v_bmm_2605_, lean_object* v_sum_2606_, lean_object* v_mul_2607_, lean_object* v_add_2608_, lean_object* v_as_2609_, lean_object* v_sz_2610_, lean_object* v_i_2611_, lean_object* v_b_2612_, lean_object* v___y_2613_){
_start:
{
size_t v_sz_boxed_2614_; size_t v_i_boxed_2615_; lean_object* v_res_2616_; 
v_sz_boxed_2614_ = lean_unbox_usize(v_sz_2610_);
lean_dec(v_sz_2610_);
v_i_boxed_2615_ = lean_unbox_usize(v_i_2611_);
lean_dec(v_i_2611_);
v_res_2616_ = lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00Bench_Suite_run_spec__0(v_a_2604_, v_bmm_2605_, v_sum_2606_, v_mul_2607_, v_add_2608_, v_as_2609_, v_sz_boxed_2614_, v_i_boxed_2615_, v_b_2612_);
lean_dec_ref(v_as_2609_);
return v_res_2616_;
}
}
LEAN_EXPORT lean_object* lp_competition_Bench_Suite_run(lean_object* v_add_2630_, lean_object* v_mul_2631_, lean_object* v_sum_2632_, lean_object* v_bmm_2633_){
_start:
{
lean_object* v___x_2635_; lean_object* v___x_2636_; lean_object* v_a_2638_; 
v___x_2635_ = ((lean_object*)(lp_competition_Bench_Suite_run___closed__0));
v___x_2636_ = lean_io_getenv(v___x_2635_);
if (lean_obj_tag(v___x_2636_) == 1)
{
lean_object* v_val_2643_; lean_object* v___x_2644_; 
v_val_2643_ = lean_ctor_get(v___x_2636_, 0);
lean_inc(v_val_2643_);
lean_dec_ref_known(v___x_2636_, 1);
v___x_2644_ = l_Lean_Json_parse(v_val_2643_);
if (lean_obj_tag(v___x_2644_) == 0)
{
lean_object* v_a_2645_; 
lean_dec_ref(v_bmm_2633_);
lean_dec_ref(v_sum_2632_);
lean_dec_ref(v_mul_2631_);
lean_dec_ref(v_add_2630_);
v_a_2645_ = lean_ctor_get(v___x_2644_, 0);
lean_inc(v_a_2645_);
lean_dec_ref_known(v___x_2644_, 1);
v_a_2638_ = v_a_2645_;
goto v___jp_2637_;
}
else
{
lean_object* v_a_2646_; lean_object* v___x_2647_; 
v_a_2646_ = lean_ctor_get(v___x_2644_, 0);
lean_inc(v_a_2646_);
lean_dec_ref_known(v___x_2644_, 1);
v___x_2647_ = lp_competition_Bench_Suite_instFromJsonPlan_fromJson(v_a_2646_);
if (lean_obj_tag(v___x_2647_) == 0)
{
lean_object* v_a_2648_; 
lean_dec_ref(v_bmm_2633_);
lean_dec_ref(v_sum_2632_);
lean_dec_ref(v_mul_2631_);
lean_dec_ref(v_add_2630_);
v_a_2648_ = lean_ctor_get(v___x_2647_, 0);
lean_inc(v_a_2648_);
lean_dec_ref_known(v___x_2647_, 1);
v_a_2638_ = v_a_2648_;
goto v___jp_2637_;
}
else
{
lean_object* v_a_2649_; lean_object* v___x_2651_; uint8_t v_isShared_2652_; uint8_t v_isSharedCheck_2696_; 
v_a_2649_ = lean_ctor_get(v___x_2647_, 0);
v_isSharedCheck_2696_ = !lean_is_exclusive(v___x_2647_);
if (v_isSharedCheck_2696_ == 0)
{
v___x_2651_ = v___x_2647_;
v_isShared_2652_ = v_isSharedCheck_2696_;
goto v_resetjp_2650_;
}
else
{
lean_inc(v_a_2649_);
lean_dec(v___x_2647_);
v___x_2651_ = lean_box(0);
v_isShared_2652_ = v_isSharedCheck_2696_;
goto v_resetjp_2650_;
}
v_resetjp_2650_:
{
lean_object* v_version_2653_; lean_object* v_cases_2654_; lean_object* v___x_2655_; uint8_t v___x_2656_; 
v_version_2653_ = lean_ctor_get(v_a_2649_, 0);
lean_inc_ref(v_version_2653_);
v_cases_2654_ = lean_ctor_get(v_a_2649_, 1);
lean_inc_ref(v_cases_2654_);
lean_dec(v_a_2649_);
v___x_2655_ = ((lean_object*)(lp_competition_Bench_Suite_run___closed__2));
v___x_2656_ = lean_string_dec_eq(v_version_2653_, v___x_2655_);
lean_dec_ref(v_version_2653_);
if (v___x_2656_ == 0)
{
lean_object* v___x_2657_; lean_object* v___x_2659_; 
lean_dec_ref(v_cases_2654_);
lean_dec_ref(v_bmm_2633_);
lean_dec_ref(v_sum_2632_);
lean_dec_ref(v_mul_2631_);
lean_dec_ref(v_add_2630_);
v___x_2657_ = ((lean_object*)(lp_competition_Bench_Suite_run___closed__4));
if (v_isShared_2652_ == 0)
{
lean_ctor_set(v___x_2651_, 0, v___x_2657_);
v___x_2659_ = v___x_2651_;
goto v_reusejp_2658_;
}
else
{
lean_object* v_reuseFailAlloc_2660_; 
v_reuseFailAlloc_2660_ = lean_alloc_ctor(1, 1, 0);
lean_ctor_set(v_reuseFailAlloc_2660_, 0, v___x_2657_);
v___x_2659_ = v_reuseFailAlloc_2660_;
goto v_reusejp_2658_;
}
v_reusejp_2658_:
{
return v___x_2659_;
}
}
else
{
lean_object* v___x_2661_; lean_object* v___x_2662_; lean_object* v___x_2663_; lean_object* v_a_2664_; lean_object* v___x_2666_; uint8_t v_isShared_2667_; uint8_t v_isSharedCheck_2695_; 
lean_del_object(v___x_2651_);
v___x_2661_ = ((lean_object*)(lp_competition_Bench_Suite_run___closed__5));
v___x_2662_ = lean_unsigned_to_nat(3u);
v___x_2663_ = lp_competition_Bench_envNat(v___x_2661_, v___x_2662_);
v_a_2664_ = lean_ctor_get(v___x_2663_, 0);
v_isSharedCheck_2695_ = !lean_is_exclusive(v___x_2663_);
if (v_isSharedCheck_2695_ == 0)
{
v___x_2666_ = v___x_2663_;
v_isShared_2667_ = v_isSharedCheck_2695_;
goto v_resetjp_2665_;
}
else
{
lean_inc(v_a_2664_);
lean_dec(v___x_2663_);
v___x_2666_ = lean_box(0);
v_isShared_2667_ = v_isSharedCheck_2695_;
goto v_resetjp_2665_;
}
v_resetjp_2665_:
{
lean_object* v___x_2668_; uint8_t v___x_2669_; 
v___x_2668_ = lean_unsigned_to_nat(0u);
v___x_2669_ = lean_nat_dec_eq(v_a_2664_, v___x_2668_);
if (v___x_2669_ == 0)
{
lean_object* v___x_2670_; size_t v_sz_2671_; size_t v___x_2672_; lean_object* v___x_2673_; 
lean_del_object(v___x_2666_);
v___x_2670_ = lean_box(0);
v_sz_2671_ = lean_array_size(v_cases_2654_);
v___x_2672_ = ((size_t)0ULL);
v___x_2673_ = lp_competition___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop___at___00Bench_Suite_run_spec__0(v_a_2664_, v_bmm_2633_, v_sum_2632_, v_mul_2631_, v_add_2630_, v_cases_2654_, v_sz_2671_, v___x_2672_, v___x_2670_);
lean_dec_ref(v_cases_2654_);
if (lean_obj_tag(v___x_2673_) == 0)
{
lean_object* v___x_2675_; uint8_t v_isShared_2676_; uint8_t v_isSharedCheck_2681_; 
v_isSharedCheck_2681_ = !lean_is_exclusive(v___x_2673_);
if (v_isSharedCheck_2681_ == 0)
{
lean_object* v_unused_2682_; 
v_unused_2682_ = lean_ctor_get(v___x_2673_, 0);
lean_dec(v_unused_2682_);
v___x_2675_ = v___x_2673_;
v_isShared_2676_ = v_isSharedCheck_2681_;
goto v_resetjp_2674_;
}
else
{
lean_dec(v___x_2673_);
v___x_2675_ = lean_box(0);
v_isShared_2676_ = v_isSharedCheck_2681_;
goto v_resetjp_2674_;
}
v_resetjp_2674_:
{
lean_object* v___x_2677_; lean_object* v___x_2679_; 
v___x_2677_ = lp_competition_Bench_Suite_measure___boxed__const__1;
if (v_isShared_2676_ == 0)
{
lean_ctor_set(v___x_2675_, 0, v___x_2677_);
v___x_2679_ = v___x_2675_;
goto v_reusejp_2678_;
}
else
{
lean_object* v_reuseFailAlloc_2680_; 
v_reuseFailAlloc_2680_ = lean_alloc_ctor(0, 1, 0);
lean_ctor_set(v_reuseFailAlloc_2680_, 0, v___x_2677_);
v___x_2679_ = v_reuseFailAlloc_2680_;
goto v_reusejp_2678_;
}
v_reusejp_2678_:
{
return v___x_2679_;
}
}
}
else
{
lean_object* v_a_2683_; lean_object* v___x_2685_; uint8_t v_isShared_2686_; uint8_t v_isSharedCheck_2690_; 
v_a_2683_ = lean_ctor_get(v___x_2673_, 0);
v_isSharedCheck_2690_ = !lean_is_exclusive(v___x_2673_);
if (v_isSharedCheck_2690_ == 0)
{
v___x_2685_ = v___x_2673_;
v_isShared_2686_ = v_isSharedCheck_2690_;
goto v_resetjp_2684_;
}
else
{
lean_inc(v_a_2683_);
lean_dec(v___x_2673_);
v___x_2685_ = lean_box(0);
v_isShared_2686_ = v_isSharedCheck_2690_;
goto v_resetjp_2684_;
}
v_resetjp_2684_:
{
lean_object* v___x_2688_; 
if (v_isShared_2686_ == 0)
{
v___x_2688_ = v___x_2685_;
goto v_reusejp_2687_;
}
else
{
lean_object* v_reuseFailAlloc_2689_; 
v_reuseFailAlloc_2689_ = lean_alloc_ctor(1, 1, 0);
lean_ctor_set(v_reuseFailAlloc_2689_, 0, v_a_2683_);
v___x_2688_ = v_reuseFailAlloc_2689_;
goto v_reusejp_2687_;
}
v_reusejp_2687_:
{
return v___x_2688_;
}
}
}
}
else
{
lean_object* v___x_2691_; lean_object* v___x_2693_; 
lean_dec(v_a_2664_);
lean_dec_ref(v_cases_2654_);
lean_dec_ref(v_bmm_2633_);
lean_dec_ref(v_sum_2632_);
lean_dec_ref(v_mul_2631_);
lean_dec_ref(v_add_2630_);
v___x_2691_ = ((lean_object*)(lp_competition_Bench_Suite_run___closed__7));
if (v_isShared_2667_ == 0)
{
lean_ctor_set_tag(v___x_2666_, 1);
lean_ctor_set(v___x_2666_, 0, v___x_2691_);
v___x_2693_ = v___x_2666_;
goto v_reusejp_2692_;
}
else
{
lean_object* v_reuseFailAlloc_2694_; 
v_reuseFailAlloc_2694_ = lean_alloc_ctor(1, 1, 0);
lean_ctor_set(v_reuseFailAlloc_2694_, 0, v___x_2691_);
v___x_2693_ = v_reuseFailAlloc_2694_;
goto v_reusejp_2692_;
}
v_reusejp_2692_:
{
return v___x_2693_;
}
}
}
}
}
}
}
}
else
{
lean_object* v___x_2697_; lean_object* v___x_2698_; 
lean_dec(v___x_2636_);
lean_dec_ref(v_bmm_2633_);
lean_dec_ref(v_sum_2632_);
lean_dec_ref(v_mul_2631_);
lean_dec_ref(v_add_2630_);
v___x_2697_ = ((lean_object*)(lp_competition_Bench_Suite_run___closed__9));
v___x_2698_ = lean_alloc_ctor(1, 1, 0);
lean_ctor_set(v___x_2698_, 0, v___x_2697_);
return v___x_2698_;
}
v___jp_2637_:
{
lean_object* v___x_2639_; lean_object* v___x_2640_; lean_object* v___x_2641_; lean_object* v___x_2642_; 
v___x_2639_ = ((lean_object*)(lp_competition_Bench_Suite_run___closed__1));
v___x_2640_ = lean_string_append(v___x_2639_, v_a_2638_);
lean_dec_ref(v_a_2638_);
v___x_2641_ = lean_alloc_ctor(18, 1, 0);
lean_ctor_set(v___x_2641_, 0, v___x_2640_);
v___x_2642_ = lean_alloc_ctor(1, 1, 0);
lean_ctor_set(v___x_2642_, 0, v___x_2641_);
return v___x_2642_;
}
}
}
LEAN_EXPORT lean_object* lp_competition_Bench_Suite_run___boxed(lean_object* v_add_2699_, lean_object* v_mul_2700_, lean_object* v_sum_2701_, lean_object* v_bmm_2702_, lean_object* v_a_2703_){
_start:
{
lean_object* v_res_2704_; 
v_res_2704_ = lp_competition_Bench_Suite_run(v_add_2699_, v_mul_2700_, v_sum_2701_, v_bmm_2702_);
return v_res_2704_;
}
}
lean_object* initialize_Init(uint8_t builtin);
lean_object* initialize_Init(uint8_t builtin);
lean_object* initialize_competition_BenchBmm(uint8_t builtin);
lean_object* initialize_Lean_Data_Json(uint8_t builtin);
void lean_initialize();
static bool _G_initialized = false;
LEAN_EXPORT lean_object* initialize_competition_BenchSuite(uint8_t builtin) {
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
res = initialize_competition_BenchBmm(builtin);
if (lean_io_result_is_error(res)) return res;
lean_dec_ref(res);
res = initialize_Lean_Data_Json(builtin);
if (lean_io_result_is_error(res)) return res;
lean_dec_ref(res);
lp_competition_Bench_Suite_measure___boxed__const__1 = _init_lp_competition_Bench_Suite_measure___boxed__const__1();
lean_mark_persistent(lp_competition_Bench_Suite_measure___boxed__const__1);
return lean_io_result_mk_ok(lean_box(0));
}
#ifdef __cplusplus
}
#endif
