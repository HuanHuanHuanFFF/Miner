// Lean compiler output
// Module: R26NativeMain
// Imports: public import Init public meta import Init public import ExactSuite public import Submission
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
uint8_t lean_nat_dec_lt(lean_object*, lean_object*);
lean_object* lean_io_mono_nanos_now();
lean_object* lean_mk_empty_array_with_capacity(lean_object*);
extern lean_object* lp_competition_Submission_kernels;
lean_object* lp_competition_ExactSuite_runPrepared(lean_object*, lean_object*, lean_object*);
lean_object* l_IO_lazyPure___redArg(lean_object*);
lean_object* lean_nat_add(lean_object*, lean_object*);
uint32_t lp_competition_ExactSuite_hashArr(lean_object*);
lean_object* lean_nat_sub(lean_object*, lean_object*);
uint8_t lean_nat_dec_eq(lean_object*, lean_object*);
lean_object* l_List_reverse___redArg(lean_object*);
lean_object* l_String_splitOnAux(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
lean_object* lp_competition_ExactSuite_Cell_name(lean_object*);
uint8_t lp_mathlib_List_elem___at___00Mathlib_Linter_TextBased_modulesOSForbidden_spec__4(lean_object*, lean_object*);
lean_object* lean_string_utf8_byte_size(lean_object*);
lean_object* l_String_Slice_toNat_x3f(lean_object*);
uint32_t lean_uint32_of_nat(lean_object*);
lean_object* l_List_appendTR___redArg(lean_object*, lean_object*);
uint8_t lean_nat_dec_le(lean_object*, lean_object*);
lean_object* lp_competition_ExactSuite_prepareProfile(lean_object*, uint32_t, lean_object*);
lean_object* lean_string_append(lean_object*, lean_object*);
lean_object* l_Nat_reprFast(lean_object*);
lean_object* lean_uint32_to_nat(uint32_t);
lean_object* lp_mathlib_IO_println___at___00printNameHashMap_spec__1(lean_object*);
uint8_t lean_string_dec_eq(lean_object*, lean_object*);
uint8_t l_List_isEmpty___redArg(lean_object*);
lean_object* lean_io_getenv(lean_object*);
lean_object* lean_array_to_list(lean_object*);
lean_object* lean_array_push(lean_object*, lean_object*);
extern lean_object* lp_competition_ExactSuite_cells;
lean_object* l_List_lengthTR___redArg(lean_object*);
lean_object* lp_batteries_List_eraseDups___at___00__private_Batteries_Tactic_HelpCmd_0__Batteries_Tactic_elabHelpCat_spec__3(lean_object*);
static const lean_string_object lp_competition_List_filterMapTR_go___at___00parseReps_spec__0___closed__0_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 2, .m_capacity = 2, .m_length = 1, .m_data = "="};
static const lean_object* lp_competition_List_filterMapTR_go___at___00parseReps_spec__0___closed__0 = (const lean_object*)&lp_competition_List_filterMapTR_go___at___00parseReps_spec__0___closed__0_value;
LEAN_EXPORT lean_object* lp_competition_List_filterMapTR_go___at___00parseReps_spec__0(lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_List_filterMapTR_go___at___00parseReps_spec__0___boxed(lean_object*, lean_object*);
static const lean_string_object lp_competition_parseReps___closed__0_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 2, .m_capacity = 2, .m_length = 1, .m_data = ","};
static const lean_object* lp_competition_parseReps___closed__0 = (const lean_object*)&lp_competition_parseReps___closed__0_value;
static const lean_array_object lp_competition_parseReps___closed__1_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_array_object) + sizeof(void*)*0, .m_other = 0, .m_tag = 246}, .m_size = 0, .m_capacity = 0, .m_data = {}};
static const lean_object* lp_competition_parseReps___closed__1 = (const lean_object*)&lp_competition_parseReps___closed__1_value;
LEAN_EXPORT lean_object* lp_competition_parseReps(lean_object*);
LEAN_EXPORT lean_object* lp_competition_parseReps___boxed(lean_object*);
LEAN_EXPORT lean_object* lp_competition_List_filterTR_loop___at___00main_spec__7(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_List_filterTR_loop___at___00main_spec__7___boxed(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00main_spec__2___redArg___lam__0(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00main_spec__2___redArg___lam__0___boxed(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00main_spec__2___redArg(lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00main_spec__2___redArg___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
static const lean_array_object lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00main_spec__3___redArg___closed__0_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_array_object) + sizeof(void*)*0, .m_other = 0, .m_tag = 246}, .m_size = 0, .m_capacity = 0, .m_data = {}};
static const lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00main_spec__3___redArg___closed__0 = (const lean_object*)&lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00main_spec__3___redArg___closed__0_value;
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00main_spec__3___redArg(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00main_spec__3___redArg___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_List_find_x3f___at___00main_spec__4(lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_List_find_x3f___at___00main_spec__4___boxed(lean_object*, lean_object*);
static const lean_string_object lp_competition_List_forIn_x27_loop___at___00main_spec__5___redArg___closed__0_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 2, .m_capacity = 2, .m_length = 1, .m_data = "|"};
static const lean_object* lp_competition_List_forIn_x27_loop___at___00main_spec__5___redArg___closed__0 = (const lean_object*)&lp_competition_List_forIn_x27_loop___at___00main_spec__5___redArg___closed__0_value;
LEAN_EXPORT lean_object* lp_competition_List_forIn_x27_loop___at___00main_spec__5___redArg___closed__1___boxed__const__1;
static lean_once_cell_t lp_competition_List_forIn_x27_loop___at___00main_spec__5___redArg___closed__1_once = LEAN_ONCE_CELL_INITIALIZER;
static lean_object* lp_competition_List_forIn_x27_loop___at___00main_spec__5___redArg___closed__1;
static const lean_string_object lp_competition_List_forIn_x27_loop___at___00main_spec__5___redArg___closed__2_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 7, .m_capacity = 7, .m_length = 6, .m_data = " true "};
static const lean_object* lp_competition_List_forIn_x27_loop___at___00main_spec__5___redArg___closed__2 = (const lean_object*)&lp_competition_List_forIn_x27_loop___at___00main_spec__5___redArg___closed__2_value;
static const lean_string_object lp_competition_List_forIn_x27_loop___at___00main_spec__5___redArg___closed__3_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 2, .m_capacity = 2, .m_length = 1, .m_data = " "};
static const lean_object* lp_competition_List_forIn_x27_loop___at___00main_spec__5___redArg___closed__3 = (const lean_object*)&lp_competition_List_forIn_x27_loop___at___00main_spec__5___redArg___closed__3_value;
static const lean_string_object lp_competition_List_forIn_x27_loop___at___00main_spec__5___redArg___closed__4_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 29, .m_capacity = 29, .m_length = 28, .m_data = "repetitions must be positive"};
static const lean_object* lp_competition_List_forIn_x27_loop___at___00main_spec__5___redArg___closed__4 = (const lean_object*)&lp_competition_List_forIn_x27_loop___at___00main_spec__5___redArg___closed__4_value;
static const lean_ctor_object lp_competition_List_forIn_x27_loop___at___00main_spec__5___redArg___closed__5_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_ctor_object) + sizeof(void*)*1 + 0, .m_other = 1, .m_tag = 18}, .m_objs = {((lean_object*)&lp_competition_List_forIn_x27_loop___at___00main_spec__5___redArg___closed__4_value)}};
static const lean_object* lp_competition_List_forIn_x27_loop___at___00main_spec__5___redArg___closed__5 = (const lean_object*)&lp_competition_List_forIn_x27_loop___at___00main_spec__5___redArg___closed__5_value;
LEAN_EXPORT lean_object* lp_competition_List_forIn_x27_loop___at___00main_spec__5___redArg(uint32_t, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_List_forIn_x27_loop___at___00main_spec__5___redArg___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_List_forIn_x27_loop___at___00main_spec__6___redArg(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_List_forIn_x27_loop___at___00main_spec__6___redArg___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
static const lean_string_object lp_competition_List_forIn_x27_loop___at___00main_spec__0___redArg___closed__0_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 17, .m_capacity = 17, .m_length = 16, .m_data = "invalid workload"};
static const lean_object* lp_competition_List_forIn_x27_loop___at___00main_spec__0___redArg___closed__0 = (const lean_object*)&lp_competition_List_forIn_x27_loop___at___00main_spec__0___redArg___closed__0_value;
static const lean_ctor_object lp_competition_List_forIn_x27_loop___at___00main_spec__0___redArg___closed__1_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_ctor_object) + sizeof(void*)*1 + 0, .m_other = 1, .m_tag = 18}, .m_objs = {((lean_object*)&lp_competition_List_forIn_x27_loop___at___00main_spec__0___redArg___closed__0_value)}};
static const lean_object* lp_competition_List_forIn_x27_loop___at___00main_spec__0___redArg___closed__1 = (const lean_object*)&lp_competition_List_forIn_x27_loop___at___00main_spec__0___redArg___closed__1_value;
static const lean_string_object lp_competition_List_forIn_x27_loop___at___00main_spec__0___redArg___closed__2_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 23, .m_capacity = 23, .m_length = 22, .m_data = "invalid workload token"};
static const lean_object* lp_competition_List_forIn_x27_loop___at___00main_spec__0___redArg___closed__2 = (const lean_object*)&lp_competition_List_forIn_x27_loop___at___00main_spec__0___redArg___closed__2_value;
static const lean_ctor_object lp_competition_List_forIn_x27_loop___at___00main_spec__0___redArg___closed__3_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_ctor_object) + sizeof(void*)*1 + 0, .m_other = 1, .m_tag = 18}, .m_objs = {((lean_object*)&lp_competition_List_forIn_x27_loop___at___00main_spec__0___redArg___closed__2_value)}};
static const lean_object* lp_competition_List_forIn_x27_loop___at___00main_spec__0___redArg___closed__3 = (const lean_object*)&lp_competition_List_forIn_x27_loop___at___00main_spec__0___redArg___closed__3_value;
static const lean_string_object lp_competition_List_forIn_x27_loop___at___00main_spec__0___redArg___closed__4_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 2, .m_capacity = 2, .m_length = 1, .m_data = ":"};
static const lean_object* lp_competition_List_forIn_x27_loop___at___00main_spec__0___redArg___closed__4 = (const lean_object*)&lp_competition_List_forIn_x27_loop___at___00main_spec__0___redArg___closed__4_value;
static const lean_string_object lp_competition_List_forIn_x27_loop___at___00main_spec__0___redArg___closed__5_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 7, .m_capacity = 7, .m_length = 6, .m_data = "legacy"};
static const lean_object* lp_competition_List_forIn_x27_loop___at___00main_spec__0___redArg___closed__5 = (const lean_object*)&lp_competition_List_forIn_x27_loop___at___00main_spec__0___redArg___closed__5_value;
static const lean_string_object lp_competition_List_forIn_x27_loop___at___00main_spec__0___redArg___closed__6_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 8, .m_capacity = 8, .m_length = 7, .m_data = "typical"};
static const lean_object* lp_competition_List_forIn_x27_loop___at___00main_spec__0___redArg___closed__6 = (const lean_object*)&lp_competition_List_forIn_x27_loop___at___00main_spec__0___redArg___closed__6_value;
static const lean_string_object lp_competition_List_forIn_x27_loop___at___00main_spec__0___redArg___closed__7_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 6, .m_capacity = 6, .m_length = 5, .m_data = "scale"};
static const lean_object* lp_competition_List_forIn_x27_loop___at___00main_spec__0___redArg___closed__7 = (const lean_object*)&lp_competition_List_forIn_x27_loop___at___00main_spec__0___redArg___closed__7_value;
static const lean_string_object lp_competition_List_forIn_x27_loop___at___00main_spec__0___redArg___closed__8_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 9, .m_capacity = 9, .m_length = 8, .m_data = "boundary"};
static const lean_object* lp_competition_List_forIn_x27_loop___at___00main_spec__0___redArg___closed__8 = (const lean_object*)&lp_competition_List_forIn_x27_loop___at___00main_spec__0___redArg___closed__8_value;
static const lean_string_object lp_competition_List_forIn_x27_loop___at___00main_spec__0___redArg___closed__9_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 13, .m_capacity = 13, .m_length = 12, .m_data = "invalid seed"};
static const lean_object* lp_competition_List_forIn_x27_loop___at___00main_spec__0___redArg___closed__9 = (const lean_object*)&lp_competition_List_forIn_x27_loop___at___00main_spec__0___redArg___closed__9_value;
static const lean_ctor_object lp_competition_List_forIn_x27_loop___at___00main_spec__0___redArg___closed__10_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_ctor_object) + sizeof(void*)*1 + 0, .m_other = 1, .m_tag = 18}, .m_objs = {((lean_object*)&lp_competition_List_forIn_x27_loop___at___00main_spec__0___redArg___closed__9_value)}};
static const lean_object* lp_competition_List_forIn_x27_loop___at___00main_spec__0___redArg___closed__10 = (const lean_object*)&lp_competition_List_forIn_x27_loop___at___00main_spec__0___redArg___closed__10_value;
LEAN_EXPORT lean_object* lp_competition_List_forIn_x27_loop___at___00main_spec__0___redArg(lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_List_forIn_x27_loop___at___00main_spec__0___redArg___boxed(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_List_mapTR_loop___at___00main_spec__1(lean_object*, lean_object*);
static const lean_string_object lp_competition_main___closed__0_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 19, .m_capacity = 19, .m_length = 18, .m_data = "duplicate workload"};
static const lean_object* lp_competition_main___closed__0 = (const lean_object*)&lp_competition_main___closed__0_value;
static const lean_ctor_object lp_competition_main___closed__1_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_ctor_object) + sizeof(void*)*1 + 0, .m_other = 1, .m_tag = 18}, .m_objs = {((lean_object*)&lp_competition_main___closed__0_value)}};
static const lean_object* lp_competition_main___closed__1 = (const lean_object*)&lp_competition_main___closed__1_value;
static const lean_string_object lp_competition_main___closed__2_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 21, .m_capacity = 21, .m_length = 20, .m_data = "empty cell selection"};
static const lean_object* lp_competition_main___closed__2 = (const lean_object*)&lp_competition_main___closed__2_value;
static const lean_ctor_object lp_competition_main___closed__3_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_ctor_object) + sizeof(void*)*1 + 0, .m_other = 1, .m_tag = 18}, .m_objs = {((lean_object*)&lp_competition_main___closed__2_value)}};
static const lean_object* lp_competition_main___closed__3 = (const lean_object*)&lp_competition_main___closed__3_value;
static const lean_string_object lp_competition_main___closed__4_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 12, .m_capacity = 12, .m_length = 11, .m_data = "BENCH_CELLS"};
static const lean_object* lp_competition_main___closed__4 = (const lean_object*)&lp_competition_main___closed__4_value;
static const lean_string_object lp_competition_main___closed__5_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 11, .m_capacity = 11, .m_length = 10, .m_data = "BENCH_REPS"};
static const lean_object* lp_competition_main___closed__5 = (const lean_object*)&lp_competition_main___closed__5_value;
static const lean_string_object lp_competition_main___closed__6_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 1, .m_capacity = 1, .m_length = 0, .m_data = ""};
static const lean_object* lp_competition_main___closed__6 = (const lean_object*)&lp_competition_main___closed__6_value;
static const lean_string_object lp_competition_main___closed__7_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 12, .m_capacity = 12, .m_length = 11, .m_data = "BENCH_INNER"};
static const lean_object* lp_competition_main___closed__7 = (const lean_object*)&lp_competition_main___closed__7_value;
static const lean_string_object lp_competition_main___closed__8_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 16, .m_capacity = 16, .m_length = 15, .m_data = "BENCH_WORKLOADS"};
static const lean_object* lp_competition_main___closed__8 = (const lean_object*)&lp_competition_main___closed__8_value;
static const lean_string_object lp_competition_main___closed__9_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 13, .m_capacity = 13, .m_length = 12, .m_data = "s0:42:legacy"};
static const lean_object* lp_competition_main___closed__9 = (const lean_object*)&lp_competition_main___closed__9_value;
static const lean_string_object lp_competition_main___closed__10_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 23, .m_capacity = 23, .m_length = 22, .m_data = "inner must be positive"};
static const lean_object* lp_competition_main___closed__10 = (const lean_object*)&lp_competition_main___closed__10_value;
static const lean_ctor_object lp_competition_main___closed__11_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_ctor_object) + sizeof(void*)*1 + 0, .m_other = 1, .m_tag = 18}, .m_objs = {((lean_object*)&lp_competition_main___closed__10_value)}};
static const lean_object* lp_competition_main___closed__11 = (const lean_object*)&lp_competition_main___closed__11_value;
LEAN_EXPORT lean_object* _lean_main();
LEAN_EXPORT lean_object* lp_competition_main___boxed(lean_object*);
LEAN_EXPORT lean_object* lp_competition_List_forIn_x27_loop___at___00main_spec__0(lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_List_forIn_x27_loop___at___00main_spec__0___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00main_spec__2(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00main_spec__2___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00main_spec__3(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00main_spec__3___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_List_forIn_x27_loop___at___00main_spec__5(uint32_t, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_List_forIn_x27_loop___at___00main_spec__5___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_List_forIn_x27_loop___at___00main_spec__6(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_List_forIn_x27_loop___at___00main_spec__6___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_competition_List_filterMapTR_go___at___00parseReps_spec__0(lean_object* v_a_2_, lean_object* v_a_3_){
_start:
{
if (lean_obj_tag(v_a_2_) == 0)
{
lean_object* v___x_4_; 
v___x_4_ = lean_array_to_list(v_a_3_);
return v___x_4_;
}
else
{
lean_object* v_head_5_; lean_object* v_tail_6_; lean_object* v___x_7_; lean_object* v___x_8_; lean_object* v___x_9_; lean_object* v___x_10_; 
v_head_5_ = lean_ctor_get(v_a_2_, 0);
v_tail_6_ = lean_ctor_get(v_a_2_, 1);
v___x_7_ = ((lean_object*)(lp_competition_List_filterMapTR_go___at___00parseReps_spec__0___closed__0));
v___x_8_ = lean_unsigned_to_nat(0u);
v___x_9_ = lean_box(0);
v___x_10_ = l_String_splitOnAux(v_head_5_, v___x_7_, v___x_8_, v___x_8_, v___x_8_, v___x_9_);
if (lean_obj_tag(v___x_10_) == 1)
{
lean_object* v_tail_11_; 
v_tail_11_ = lean_ctor_get(v___x_10_, 1);
lean_inc(v_tail_11_);
if (lean_obj_tag(v_tail_11_) == 1)
{
lean_object* v_tail_12_; 
v_tail_12_ = lean_ctor_get(v_tail_11_, 1);
if (lean_obj_tag(v_tail_12_) == 0)
{
lean_object* v_head_13_; lean_object* v_head_14_; lean_object* v___x_16_; uint8_t v_isShared_17_; uint8_t v_isSharedCheck_28_; 
v_head_13_ = lean_ctor_get(v___x_10_, 0);
lean_inc(v_head_13_);
lean_dec_ref_known(v___x_10_, 2);
v_head_14_ = lean_ctor_get(v_tail_11_, 0);
v_isSharedCheck_28_ = !lean_is_exclusive(v_tail_11_);
if (v_isSharedCheck_28_ == 0)
{
lean_object* v_unused_29_; 
v_unused_29_ = lean_ctor_get(v_tail_11_, 1);
lean_dec(v_unused_29_);
v___x_16_ = v_tail_11_;
v_isShared_17_ = v_isSharedCheck_28_;
goto v_resetjp_15_;
}
else
{
lean_inc(v_head_14_);
lean_dec(v_tail_11_);
v___x_16_ = lean_box(0);
v_isShared_17_ = v_isSharedCheck_28_;
goto v_resetjp_15_;
}
v_resetjp_15_:
{
lean_object* v___x_18_; lean_object* v___x_19_; lean_object* v___x_20_; 
v___x_18_ = lean_string_utf8_byte_size(v_head_14_);
v___x_19_ = lean_alloc_ctor(0, 3, 0);
lean_ctor_set(v___x_19_, 0, v_head_14_);
lean_ctor_set(v___x_19_, 1, v___x_8_);
lean_ctor_set(v___x_19_, 2, v___x_18_);
v___x_20_ = l_String_Slice_toNat_x3f(v___x_19_);
lean_dec_ref_known(v___x_19_, 3);
if (lean_obj_tag(v___x_20_) == 0)
{
lean_del_object(v___x_16_);
lean_dec(v_head_13_);
v_a_2_ = v_tail_6_;
goto _start;
}
else
{
lean_object* v_val_22_; lean_object* v___x_24_; 
v_val_22_ = lean_ctor_get(v___x_20_, 0);
lean_inc(v_val_22_);
lean_dec_ref_known(v___x_20_, 1);
if (v_isShared_17_ == 0)
{
lean_ctor_set_tag(v___x_16_, 0);
lean_ctor_set(v___x_16_, 1, v_val_22_);
lean_ctor_set(v___x_16_, 0, v_head_13_);
v___x_24_ = v___x_16_;
goto v_reusejp_23_;
}
else
{
lean_object* v_reuseFailAlloc_27_; 
v_reuseFailAlloc_27_ = lean_alloc_ctor(0, 2, 0);
lean_ctor_set(v_reuseFailAlloc_27_, 0, v_head_13_);
lean_ctor_set(v_reuseFailAlloc_27_, 1, v_val_22_);
v___x_24_ = v_reuseFailAlloc_27_;
goto v_reusejp_23_;
}
v_reusejp_23_:
{
lean_object* v___x_25_; 
v___x_25_ = lean_array_push(v_a_3_, v___x_24_);
v_a_2_ = v_tail_6_;
v_a_3_ = v___x_25_;
goto _start;
}
}
}
}
else
{
lean_dec_ref_known(v_tail_11_, 2);
lean_dec_ref_known(v___x_10_, 2);
v_a_2_ = v_tail_6_;
goto _start;
}
}
else
{
lean_dec(v_tail_11_);
lean_dec_ref_known(v___x_10_, 2);
v_a_2_ = v_tail_6_;
goto _start;
}
}
else
{
lean_dec(v___x_10_);
v_a_2_ = v_tail_6_;
goto _start;
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_List_filterMapTR_go___at___00parseReps_spec__0___boxed(lean_object* v_a_33_, lean_object* v_a_34_){
_start:
{
lean_object* v_res_35_; 
v_res_35_ = lp_competition_List_filterMapTR_go___at___00parseReps_spec__0(v_a_33_, v_a_34_);
lean_dec(v_a_33_);
return v_res_35_;
}
}
LEAN_EXPORT lean_object* lp_competition_parseReps(lean_object* v_text_39_){
_start:
{
lean_object* v___x_40_; lean_object* v___x_41_; lean_object* v___x_42_; lean_object* v___x_43_; lean_object* v___x_44_; lean_object* v___x_45_; 
v___x_40_ = ((lean_object*)(lp_competition_parseReps___closed__0));
v___x_41_ = lean_unsigned_to_nat(0u);
v___x_42_ = lean_box(0);
v___x_43_ = l_String_splitOnAux(v_text_39_, v___x_40_, v___x_41_, v___x_41_, v___x_41_, v___x_42_);
v___x_44_ = ((lean_object*)(lp_competition_parseReps___closed__1));
v___x_45_ = lp_competition_List_filterMapTR_go___at___00parseReps_spec__0(v___x_43_, v___x_44_);
lean_dec(v___x_43_);
return v___x_45_;
}
}
LEAN_EXPORT lean_object* lp_competition_parseReps___boxed(lean_object* v_text_46_){
_start:
{
lean_object* v_res_47_; 
v_res_47_ = lp_competition_parseReps(v_text_46_);
lean_dec_ref(v_text_46_);
return v_res_47_;
}
}
LEAN_EXPORT lean_object* lp_competition_List_filterTR_loop___at___00main_spec__7(lean_object* v_val_48_, lean_object* v_a_49_, lean_object* v_a_50_){
_start:
{
if (lean_obj_tag(v_a_49_) == 0)
{
lean_object* v___x_51_; 
v___x_51_ = l_List_reverse___redArg(v_a_50_);
return v___x_51_;
}
else
{
lean_object* v_head_52_; lean_object* v_tail_53_; lean_object* v___x_55_; uint8_t v_isShared_56_; uint8_t v_isSharedCheck_68_; 
v_head_52_ = lean_ctor_get(v_a_49_, 0);
v_tail_53_ = lean_ctor_get(v_a_49_, 1);
v_isSharedCheck_68_ = !lean_is_exclusive(v_a_49_);
if (v_isSharedCheck_68_ == 0)
{
v___x_55_ = v_a_49_;
v_isShared_56_ = v_isSharedCheck_68_;
goto v_resetjp_54_;
}
else
{
lean_inc(v_tail_53_);
lean_inc(v_head_52_);
lean_dec(v_a_49_);
v___x_55_ = lean_box(0);
v_isShared_56_ = v_isSharedCheck_68_;
goto v_resetjp_54_;
}
v_resetjp_54_:
{
lean_object* v___x_57_; lean_object* v___x_58_; lean_object* v___x_59_; lean_object* v___x_60_; lean_object* v___x_61_; uint8_t v___x_62_; 
v___x_57_ = ((lean_object*)(lp_competition_parseReps___closed__0));
v___x_58_ = lean_unsigned_to_nat(0u);
v___x_59_ = lean_box(0);
v___x_60_ = l_String_splitOnAux(v_val_48_, v___x_57_, v___x_58_, v___x_58_, v___x_58_, v___x_59_);
lean_inc(v_head_52_);
v___x_61_ = lp_competition_ExactSuite_Cell_name(v_head_52_);
v___x_62_ = lp_mathlib_List_elem___at___00Mathlib_Linter_TextBased_modulesOSForbidden_spec__4(v___x_61_, v___x_60_);
lean_dec(v___x_60_);
lean_dec_ref(v___x_61_);
if (v___x_62_ == 0)
{
lean_del_object(v___x_55_);
lean_dec(v_head_52_);
v_a_49_ = v_tail_53_;
goto _start;
}
else
{
lean_object* v___x_65_; 
if (v_isShared_56_ == 0)
{
lean_ctor_set(v___x_55_, 1, v_a_50_);
v___x_65_ = v___x_55_;
goto v_reusejp_64_;
}
else
{
lean_object* v_reuseFailAlloc_67_; 
v_reuseFailAlloc_67_ = lean_alloc_ctor(1, 2, 0);
lean_ctor_set(v_reuseFailAlloc_67_, 0, v_head_52_);
lean_ctor_set(v_reuseFailAlloc_67_, 1, v_a_50_);
v___x_65_ = v_reuseFailAlloc_67_;
goto v_reusejp_64_;
}
v_reusejp_64_:
{
v_a_49_ = v_tail_53_;
v_a_50_ = v___x_65_;
goto _start;
}
}
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_List_filterTR_loop___at___00main_spec__7___boxed(lean_object* v_val_69_, lean_object* v_a_70_, lean_object* v_a_71_){
_start:
{
lean_object* v_res_72_; 
v_res_72_ = lp_competition_List_filterTR_loop___at___00main_spec__7(v_val_69_, v_a_70_, v_a_71_);
lean_dec_ref(v_val_69_);
return v_res_72_;
}
}
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00main_spec__2___redArg___lam__0(lean_object* v___x_73_, lean_object* v_i_74_, lean_object* v_x_75_){
_start:
{
lean_object* v___x_76_; lean_object* v___x_77_; 
v___x_76_ = lp_competition_Submission_kernels;
v___x_77_ = lp_competition_ExactSuite_runPrepared(v___x_76_, v___x_73_, v_i_74_);
return v___x_77_;
}
}
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00main_spec__2___redArg___lam__0___boxed(lean_object* v___x_78_, lean_object* v_i_79_, lean_object* v_x_80_){
_start:
{
lean_object* v_res_81_; 
v_res_81_ = lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00main_spec__2___redArg___lam__0(v___x_78_, v_i_79_, v_x_80_);
lean_dec(v_i_79_);
return v_res_81_;
}
}
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00main_spec__2___redArg(lean_object* v___x_82_, lean_object* v_range_83_, lean_object* v_b_84_, lean_object* v_i_85_){
_start:
{
lean_object* v_stop_87_; lean_object* v_step_88_; uint8_t v___x_89_; 
v_stop_87_ = lean_ctor_get(v_range_83_, 1);
v_step_88_ = lean_ctor_get(v_range_83_, 2);
v___x_89_ = lean_nat_dec_lt(v_i_85_, v_stop_87_);
if (v___x_89_ == 0)
{
lean_object* v___x_90_; 
lean_dec(v_i_85_);
lean_dec_ref(v___x_82_);
v___x_90_ = lean_alloc_ctor(0, 1, 0);
lean_ctor_set(v___x_90_, 0, v_b_84_);
return v___x_90_;
}
else
{
lean_object* v___f_91_; lean_object* v___x_92_; lean_object* v_a_93_; lean_object* v___x_94_; 
lean_dec_ref(v_b_84_);
lean_inc(v_i_85_);
lean_inc_ref(v___x_82_);
v___f_91_ = lean_alloc_closure((void*)(lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00main_spec__2___redArg___lam__0___boxed), 3, 2);
lean_closure_set(v___f_91_, 0, v___x_82_);
lean_closure_set(v___f_91_, 1, v_i_85_);
v___x_92_ = l_IO_lazyPure___redArg(v___f_91_);
v_a_93_ = lean_ctor_get(v___x_92_, 0);
lean_inc(v_a_93_);
lean_dec_ref(v___x_92_);
v___x_94_ = lean_nat_add(v_i_85_, v_step_88_);
lean_dec(v_i_85_);
v_b_84_ = v_a_93_;
v_i_85_ = v___x_94_;
goto _start;
}
}
}
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00main_spec__2___redArg___boxed(lean_object* v___x_96_, lean_object* v_range_97_, lean_object* v_b_98_, lean_object* v_i_99_, lean_object* v___y_100_){
_start:
{
lean_object* v_res_101_; 
v_res_101_ = lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00main_spec__2___redArg(v___x_96_, v_range_97_, v_b_98_, v_i_99_);
lean_dec_ref(v_range_97_);
return v_res_101_;
}
}
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00main_spec__3___redArg(lean_object* v___y_104_, lean_object* v___x_105_, lean_object* v_range_106_, lean_object* v_b_107_, lean_object* v_i_108_){
_start:
{
lean_object* v_stop_110_; lean_object* v_step_111_; uint8_t v___x_112_; 
v_stop_110_ = lean_ctor_get(v_range_106_, 1);
v_step_111_ = lean_ctor_get(v_range_106_, 2);
v___x_112_ = lean_nat_dec_lt(v_i_108_, v_stop_110_);
if (v___x_112_ == 0)
{
lean_object* v___x_113_; 
lean_dec(v_i_108_);
lean_dec_ref(v___x_105_);
lean_dec(v___y_104_);
v___x_113_ = lean_alloc_ctor(0, 1, 0);
lean_ctor_set(v___x_113_, 0, v_b_107_);
return v___x_113_;
}
else
{
lean_object* v___x_114_; lean_object* v___x_115_; lean_object* v___x_116_; lean_object* v___x_117_; lean_object* v___x_118_; lean_object* v___x_119_; lean_object* v_a_120_; lean_object* v___x_121_; lean_object* v_fst_122_; lean_object* v___x_124_; uint8_t v_isShared_125_; uint8_t v_isSharedCheck_141_; 
v___x_114_ = lean_io_mono_nanos_now();
v___x_115_ = lean_unsigned_to_nat(0u);
v___x_116_ = lean_unsigned_to_nat(1u);
v___x_117_ = ((lean_object*)(lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00main_spec__3___redArg___closed__0));
lean_inc(v___y_104_);
v___x_118_ = lean_alloc_ctor(0, 3, 0);
lean_ctor_set(v___x_118_, 0, v___x_115_);
lean_ctor_set(v___x_118_, 1, v___y_104_);
lean_ctor_set(v___x_118_, 2, v___x_116_);
lean_inc_ref(v___x_105_);
v___x_119_ = lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00main_spec__2___redArg(v___x_105_, v___x_118_, v___x_117_, v___x_115_);
lean_dec_ref_known(v___x_118_, 3);
v_a_120_ = lean_ctor_get(v___x_119_, 0);
lean_inc(v_a_120_);
lean_dec_ref(v___x_119_);
v___x_121_ = lean_io_mono_nanos_now();
v_fst_122_ = lean_ctor_get(v_b_107_, 0);
v_isSharedCheck_141_ = !lean_is_exclusive(v_b_107_);
if (v_isSharedCheck_141_ == 0)
{
lean_object* v_unused_142_; 
v_unused_142_ = lean_ctor_get(v_b_107_, 1);
lean_dec(v_unused_142_);
v___x_124_ = v_b_107_;
v_isShared_125_ = v_isSharedCheck_141_;
goto v_resetjp_123_;
}
else
{
lean_inc(v_fst_122_);
lean_dec(v_b_107_);
v___x_124_ = lean_box(0);
v_isShared_125_ = v_isSharedCheck_141_;
goto v_resetjp_123_;
}
v_resetjp_123_:
{
uint32_t v___x_126_; lean_object* v___y_128_; uint8_t v___y_136_; uint8_t v___x_138_; 
v___x_126_ = lp_competition_ExactSuite_hashArr(v_a_120_);
lean_dec(v_a_120_);
v___x_138_ = lean_nat_dec_eq(v_fst_122_, v___x_115_);
if (v___x_138_ == 0)
{
lean_object* v___x_139_; uint8_t v___x_140_; 
v___x_139_ = lean_nat_sub(v___x_121_, v___x_114_);
v___x_140_ = lean_nat_dec_lt(v___x_139_, v_fst_122_);
lean_dec(v___x_139_);
v___y_136_ = v___x_140_;
goto v___jp_135_;
}
else
{
v___y_136_ = v___x_138_;
goto v___jp_135_;
}
v___jp_127_:
{
lean_object* v___x_129_; lean_object* v___x_131_; 
v___x_129_ = lean_box_uint32(v___x_126_);
if (v_isShared_125_ == 0)
{
lean_ctor_set(v___x_124_, 1, v___x_129_);
lean_ctor_set(v___x_124_, 0, v___y_128_);
v___x_131_ = v___x_124_;
goto v_reusejp_130_;
}
else
{
lean_object* v_reuseFailAlloc_134_; 
v_reuseFailAlloc_134_ = lean_alloc_ctor(0, 2, 0);
lean_ctor_set(v_reuseFailAlloc_134_, 0, v___y_128_);
lean_ctor_set(v_reuseFailAlloc_134_, 1, v___x_129_);
v___x_131_ = v_reuseFailAlloc_134_;
goto v_reusejp_130_;
}
v_reusejp_130_:
{
lean_object* v___x_132_; 
v___x_132_ = lean_nat_add(v_i_108_, v_step_111_);
lean_dec(v_i_108_);
v_b_107_ = v___x_131_;
v_i_108_ = v___x_132_;
goto _start;
}
}
v___jp_135_:
{
if (v___y_136_ == 0)
{
lean_dec(v___x_121_);
lean_dec(v___x_114_);
v___y_128_ = v_fst_122_;
goto v___jp_127_;
}
else
{
lean_object* v___x_137_; 
lean_dec(v_fst_122_);
v___x_137_ = lean_nat_sub(v___x_121_, v___x_114_);
lean_dec(v___x_114_);
lean_dec(v___x_121_);
v___y_128_ = v___x_137_;
goto v___jp_127_;
}
}
}
}
}
}
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00main_spec__3___redArg___boxed(lean_object* v___y_143_, lean_object* v___x_144_, lean_object* v_range_145_, lean_object* v_b_146_, lean_object* v_i_147_, lean_object* v___y_148_){
_start:
{
lean_object* v_res_149_; 
v_res_149_ = lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00main_spec__3___redArg(v___y_143_, v___x_144_, v_range_145_, v_b_146_, v_i_147_);
lean_dec_ref(v_range_145_);
return v_res_149_;
}
}
LEAN_EXPORT lean_object* lp_competition_List_find_x3f___at___00main_spec__4(lean_object* v___x_150_, lean_object* v_x_151_){
_start:
{
if (lean_obj_tag(v_x_151_) == 0)
{
lean_object* v___x_152_; 
v___x_152_ = lean_box(0);
return v___x_152_;
}
else
{
lean_object* v_head_153_; lean_object* v_tail_154_; lean_object* v_fst_155_; uint8_t v___x_156_; 
v_head_153_ = lean_ctor_get(v_x_151_, 0);
v_tail_154_ = lean_ctor_get(v_x_151_, 1);
v_fst_155_ = lean_ctor_get(v_head_153_, 0);
v___x_156_ = lean_string_dec_eq(v_fst_155_, v___x_150_);
if (v___x_156_ == 0)
{
v_x_151_ = v_tail_154_;
goto _start;
}
else
{
lean_object* v___x_158_; 
lean_inc(v_head_153_);
v___x_158_ = lean_alloc_ctor(1, 1, 0);
lean_ctor_set(v___x_158_, 0, v_head_153_);
return v___x_158_;
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_List_find_x3f___at___00main_spec__4___boxed(lean_object* v___x_159_, lean_object* v_x_160_){
_start:
{
lean_object* v_res_161_; 
v_res_161_ = lp_competition_List_find_x3f___at___00main_spec__4(v___x_159_, v_x_160_);
lean_dec(v_x_160_);
lean_dec_ref(v___x_159_);
return v_res_161_;
}
}
static lean_object* _init_lp_competition_List_forIn_x27_loop___at___00main_spec__5___redArg___closed__1___boxed__const__1(void){
_start:
{
uint32_t v___x_163_; lean_object* v___x_164_; 
v___x_163_ = 0;
v___x_164_ = lean_box_uint32(v___x_163_);
return v___x_164_;
}
}
static lean_object* _init_lp_competition_List_forIn_x27_loop___at___00main_spec__5___redArg___closed__1(void){
_start:
{
lean_object* v___x_165_; lean_object* v___x_166_; lean_object* v___x_167_; 
v___x_165_ = lean_unsigned_to_nat(0u);
v___x_166_ = lp_competition_List_forIn_x27_loop___at___00main_spec__5___redArg___closed__1___boxed__const__1;
v___x_167_ = lean_alloc_ctor(0, 2, 0);
lean_ctor_set(v___x_167_, 0, v___x_165_);
lean_ctor_set(v___x_167_, 1, v___x_166_);
return v___x_167_;
}
}
LEAN_EXPORT lean_object* lp_competition_List_forIn_x27_loop___at___00main_spec__5___redArg(uint32_t v_fst_173_, lean_object* v_snd_174_, lean_object* v_fst_175_, lean_object* v___y_176_, lean_object* v___x_177_, lean_object* v_as_x27_178_, lean_object* v_b_179_){
_start:
{
if (lean_obj_tag(v_as_x27_178_) == 0)
{
lean_object* v___x_181_; 
lean_dec(v___y_176_);
lean_dec_ref(v_fst_175_);
v___x_181_ = lean_alloc_ctor(0, 1, 0);
lean_ctor_set(v___x_181_, 0, v_b_179_);
return v___x_181_;
}
else
{
lean_object* v_head_182_; lean_object* v_tail_183_; lean_object* v___x_184_; lean_object* v___x_185_; lean_object* v___x_186_; lean_object* v___x_187_; lean_object* v___x_188_; lean_object* v___x_189_; lean_object* v___y_191_; lean_object* v___x_223_; 
v_head_182_ = lean_ctor_get(v_as_x27_178_, 0);
v_tail_183_ = lean_ctor_get(v_as_x27_178_, 1);
v___x_184_ = lean_box(0);
lean_inc_n(v_head_182_, 2);
v___x_185_ = lp_competition_ExactSuite_prepareProfile(v_head_182_, v_fst_173_, v_snd_174_);
v___x_186_ = ((lean_object*)(lp_competition_List_forIn_x27_loop___at___00main_spec__5___redArg___closed__0));
lean_inc_ref(v_fst_175_);
v___x_187_ = lean_string_append(v_fst_175_, v___x_186_);
v___x_188_ = lp_competition_ExactSuite_Cell_name(v_head_182_);
v___x_189_ = lean_string_append(v___x_187_, v___x_188_);
lean_dec_ref(v___x_188_);
v___x_223_ = lp_competition_List_find_x3f___at___00main_spec__4(v___x_189_, v___x_177_);
if (lean_obj_tag(v___x_223_) == 0)
{
lean_object* v___x_224_; 
v___x_224_ = lean_unsigned_to_nat(1u);
v___y_191_ = v___x_224_;
goto v___jp_190_;
}
else
{
lean_object* v_val_225_; lean_object* v_snd_226_; 
v_val_225_ = lean_ctor_get(v___x_223_, 0);
lean_inc(v_val_225_);
lean_dec_ref_known(v___x_223_, 1);
v_snd_226_ = lean_ctor_get(v_val_225_, 1);
lean_inc(v_snd_226_);
lean_dec(v_val_225_);
v___y_191_ = v_snd_226_;
goto v___jp_190_;
}
v___jp_190_:
{
lean_object* v___x_192_; uint8_t v___x_193_; 
v___x_192_ = lean_unsigned_to_nat(0u);
v___x_193_ = lean_nat_dec_eq(v___y_191_, v___x_192_);
if (v___x_193_ == 0)
{
lean_object* v___x_194_; lean_object* v___x_195_; lean_object* v___x_196_; lean_object* v___x_197_; 
v___x_194_ = lean_unsigned_to_nat(1u);
lean_inc(v___y_176_);
v___x_195_ = lean_alloc_ctor(0, 3, 0);
lean_ctor_set(v___x_195_, 0, v___x_192_);
lean_ctor_set(v___x_195_, 1, v___y_176_);
lean_ctor_set(v___x_195_, 2, v___x_194_);
v___x_196_ = lean_obj_once(&lp_competition_List_forIn_x27_loop___at___00main_spec__5___redArg___closed__1, &lp_competition_List_forIn_x27_loop___at___00main_spec__5___redArg___closed__1_once, _init_lp_competition_List_forIn_x27_loop___at___00main_spec__5___redArg___closed__1);
v___x_197_ = lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00main_spec__3___redArg(v___y_191_, v___x_185_, v___x_195_, v___x_196_, v___x_192_);
lean_dec_ref_known(v___x_195_, 3);
if (lean_obj_tag(v___x_197_) == 0)
{
lean_object* v_a_198_; lean_object* v_fst_199_; lean_object* v_snd_200_; lean_object* v___x_201_; lean_object* v___x_202_; lean_object* v___x_203_; lean_object* v___x_204_; lean_object* v___x_205_; lean_object* v___x_206_; uint32_t v___x_207_; lean_object* v___x_208_; lean_object* v___x_209_; lean_object* v___x_210_; lean_object* v___x_211_; 
v_a_198_ = lean_ctor_get(v___x_197_, 0);
lean_inc(v_a_198_);
lean_dec_ref_known(v___x_197_, 1);
v_fst_199_ = lean_ctor_get(v_a_198_, 0);
lean_inc(v_fst_199_);
v_snd_200_ = lean_ctor_get(v_a_198_, 1);
lean_inc(v_snd_200_);
lean_dec(v_a_198_);
v___x_201_ = ((lean_object*)(lp_competition_List_forIn_x27_loop___at___00main_spec__5___redArg___closed__2));
v___x_202_ = lean_string_append(v___x_189_, v___x_201_);
v___x_203_ = l_Nat_reprFast(v_fst_199_);
v___x_204_ = lean_string_append(v___x_202_, v___x_203_);
lean_dec_ref(v___x_203_);
v___x_205_ = ((lean_object*)(lp_competition_List_forIn_x27_loop___at___00main_spec__5___redArg___closed__3));
v___x_206_ = lean_string_append(v___x_204_, v___x_205_);
v___x_207_ = lean_unbox_uint32(v_snd_200_);
lean_dec(v_snd_200_);
v___x_208_ = lean_uint32_to_nat(v___x_207_);
v___x_209_ = l_Nat_reprFast(v___x_208_);
v___x_210_ = lean_string_append(v___x_206_, v___x_209_);
lean_dec_ref(v___x_209_);
v___x_211_ = lp_mathlib_IO_println___at___00printNameHashMap_spec__1(v___x_210_);
if (lean_obj_tag(v___x_211_) == 0)
{
lean_dec_ref_known(v___x_211_, 1);
v_as_x27_178_ = v_tail_183_;
v_b_179_ = v___x_184_;
goto _start;
}
else
{
lean_dec(v___y_176_);
lean_dec_ref(v_fst_175_);
return v___x_211_;
}
}
else
{
lean_object* v_a_213_; lean_object* v___x_215_; uint8_t v_isShared_216_; uint8_t v_isSharedCheck_220_; 
lean_dec_ref(v___x_189_);
lean_dec(v___y_176_);
lean_dec_ref(v_fst_175_);
v_a_213_ = lean_ctor_get(v___x_197_, 0);
v_isSharedCheck_220_ = !lean_is_exclusive(v___x_197_);
if (v_isSharedCheck_220_ == 0)
{
v___x_215_ = v___x_197_;
v_isShared_216_ = v_isSharedCheck_220_;
goto v_resetjp_214_;
}
else
{
lean_inc(v_a_213_);
lean_dec(v___x_197_);
v___x_215_ = lean_box(0);
v_isShared_216_ = v_isSharedCheck_220_;
goto v_resetjp_214_;
}
v_resetjp_214_:
{
lean_object* v___x_218_; 
if (v_isShared_216_ == 0)
{
v___x_218_ = v___x_215_;
goto v_reusejp_217_;
}
else
{
lean_object* v_reuseFailAlloc_219_; 
v_reuseFailAlloc_219_ = lean_alloc_ctor(1, 1, 0);
lean_ctor_set(v_reuseFailAlloc_219_, 0, v_a_213_);
v___x_218_ = v_reuseFailAlloc_219_;
goto v_reusejp_217_;
}
v_reusejp_217_:
{
return v___x_218_;
}
}
}
}
else
{
lean_object* v___x_221_; lean_object* v___x_222_; 
lean_dec(v___y_191_);
lean_dec_ref(v___x_189_);
lean_dec_ref(v___x_185_);
lean_dec(v___y_176_);
lean_dec_ref(v_fst_175_);
v___x_221_ = ((lean_object*)(lp_competition_List_forIn_x27_loop___at___00main_spec__5___redArg___closed__5));
v___x_222_ = lean_alloc_ctor(1, 1, 0);
lean_ctor_set(v___x_222_, 0, v___x_221_);
return v___x_222_;
}
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_List_forIn_x27_loop___at___00main_spec__5___redArg___boxed(lean_object* v_fst_227_, lean_object* v_snd_228_, lean_object* v_fst_229_, lean_object* v___y_230_, lean_object* v___x_231_, lean_object* v_as_x27_232_, lean_object* v_b_233_, lean_object* v___y_234_){
_start:
{
uint32_t v_fst_8587__boxed_235_; lean_object* v_res_236_; 
v_fst_8587__boxed_235_ = lean_unbox_uint32(v_fst_227_);
lean_dec(v_fst_227_);
v_res_236_ = lp_competition_List_forIn_x27_loop___at___00main_spec__5___redArg(v_fst_8587__boxed_235_, v_snd_228_, v_fst_229_, v___y_230_, v___x_231_, v_as_x27_232_, v_b_233_);
lean_dec(v_as_x27_232_);
lean_dec(v___x_231_);
lean_dec_ref(v_snd_228_);
return v_res_236_;
}
}
LEAN_EXPORT lean_object* lp_competition_List_forIn_x27_loop___at___00main_spec__6___redArg(lean_object* v___y_237_, lean_object* v___x_238_, lean_object* v___y_239_, lean_object* v_as_x27_240_, lean_object* v_b_241_){
_start:
{
if (lean_obj_tag(v_as_x27_240_) == 0)
{
lean_object* v___x_243_; 
lean_dec(v___y_237_);
v___x_243_ = lean_alloc_ctor(0, 1, 0);
lean_ctor_set(v___x_243_, 0, v_b_241_);
return v___x_243_;
}
else
{
lean_object* v_head_244_; lean_object* v_snd_245_; lean_object* v_tail_246_; lean_object* v_fst_247_; lean_object* v_fst_248_; lean_object* v_snd_249_; lean_object* v___x_250_; uint32_t v___x_251_; lean_object* v___x_252_; 
v_head_244_ = lean_ctor_get(v_as_x27_240_, 0);
v_snd_245_ = lean_ctor_get(v_head_244_, 1);
v_tail_246_ = lean_ctor_get(v_as_x27_240_, 1);
v_fst_247_ = lean_ctor_get(v_head_244_, 0);
v_fst_248_ = lean_ctor_get(v_snd_245_, 0);
v_snd_249_ = lean_ctor_get(v_snd_245_, 1);
v___x_250_ = lean_box(0);
v___x_251_ = lean_unbox_uint32(v_fst_248_);
lean_inc(v___y_237_);
lean_inc(v_fst_247_);
v___x_252_ = lp_competition_List_forIn_x27_loop___at___00main_spec__5___redArg(v___x_251_, v_snd_249_, v_fst_247_, v___y_237_, v___x_238_, v___y_239_, v___x_250_);
if (lean_obj_tag(v___x_252_) == 0)
{
lean_dec_ref_known(v___x_252_, 1);
v_as_x27_240_ = v_tail_246_;
v_b_241_ = v___x_250_;
goto _start;
}
else
{
lean_dec(v___y_237_);
return v___x_252_;
}
}
}
}
LEAN_EXPORT lean_object* lp_competition_List_forIn_x27_loop___at___00main_spec__6___redArg___boxed(lean_object* v___y_254_, lean_object* v___x_255_, lean_object* v___y_256_, lean_object* v_as_x27_257_, lean_object* v_b_258_, lean_object* v___y_259_){
_start:
{
lean_object* v_res_260_; 
v_res_260_ = lp_competition_List_forIn_x27_loop___at___00main_spec__6___redArg(v___y_254_, v___x_255_, v___y_256_, v_as_x27_257_, v_b_258_);
lean_dec(v_as_x27_257_);
lean_dec(v___y_256_);
lean_dec(v___x_255_);
return v_res_260_;
}
}
LEAN_EXPORT lean_object* lp_competition_List_forIn_x27_loop___at___00main_spec__0___redArg(lean_object* v_as_x27_275_, lean_object* v_b_276_){
_start:
{
if (lean_obj_tag(v_as_x27_275_) == 0)
{
lean_object* v___x_284_; 
v___x_284_ = lean_alloc_ctor(0, 1, 0);
lean_ctor_set(v___x_284_, 0, v_b_276_);
return v___x_284_;
}
else
{
lean_object* v_head_285_; lean_object* v_tail_286_; lean_object* v___x_287_; lean_object* v___x_288_; lean_object* v___x_289_; lean_object* v___x_290_; 
v_head_285_ = lean_ctor_get(v_as_x27_275_, 0);
v_tail_286_ = lean_ctor_get(v_as_x27_275_, 1);
v___x_287_ = ((lean_object*)(lp_competition_List_forIn_x27_loop___at___00main_spec__0___redArg___closed__4));
v___x_288_ = lean_unsigned_to_nat(0u);
v___x_289_ = lean_box(0);
v___x_290_ = l_String_splitOnAux(v_head_285_, v___x_287_, v___x_288_, v___x_288_, v___x_288_, v___x_289_);
if (lean_obj_tag(v___x_290_) == 1)
{
lean_object* v_tail_291_; 
v_tail_291_ = lean_ctor_get(v___x_290_, 1);
lean_inc(v_tail_291_);
if (lean_obj_tag(v_tail_291_) == 1)
{
lean_object* v_tail_292_; 
v_tail_292_ = lean_ctor_get(v_tail_291_, 1);
lean_inc(v_tail_292_);
if (lean_obj_tag(v_tail_292_) == 1)
{
lean_object* v_tail_293_; 
v_tail_293_ = lean_ctor_get(v_tail_292_, 1);
lean_inc(v_tail_293_);
if (lean_obj_tag(v_tail_293_) == 0)
{
lean_object* v_head_294_; lean_object* v___x_296_; uint8_t v_isShared_297_; uint8_t v_isSharedCheck_344_; 
v_head_294_ = lean_ctor_get(v___x_290_, 0);
v_isSharedCheck_344_ = !lean_is_exclusive(v___x_290_);
if (v_isSharedCheck_344_ == 0)
{
lean_object* v_unused_345_; 
v_unused_345_ = lean_ctor_get(v___x_290_, 1);
lean_dec(v_unused_345_);
v___x_296_ = v___x_290_;
v_isShared_297_ = v_isSharedCheck_344_;
goto v_resetjp_295_;
}
else
{
lean_inc(v_head_294_);
lean_dec(v___x_290_);
v___x_296_ = lean_box(0);
v_isShared_297_ = v_isSharedCheck_344_;
goto v_resetjp_295_;
}
v_resetjp_295_:
{
lean_object* v_head_298_; lean_object* v___x_300_; uint8_t v_isShared_301_; uint8_t v_isSharedCheck_342_; 
v_head_298_ = lean_ctor_get(v_tail_291_, 0);
v_isSharedCheck_342_ = !lean_is_exclusive(v_tail_291_);
if (v_isSharedCheck_342_ == 0)
{
lean_object* v_unused_343_; 
v_unused_343_ = lean_ctor_get(v_tail_291_, 1);
lean_dec(v_unused_343_);
v___x_300_ = v_tail_291_;
v_isShared_301_ = v_isSharedCheck_342_;
goto v_resetjp_299_;
}
else
{
lean_inc(v_head_298_);
lean_dec(v_tail_291_);
v___x_300_ = lean_box(0);
v_isShared_301_ = v_isSharedCheck_342_;
goto v_resetjp_299_;
}
v_resetjp_299_:
{
lean_object* v_head_302_; lean_object* v___x_304_; uint8_t v_isShared_305_; uint8_t v_isSharedCheck_340_; 
v_head_302_ = lean_ctor_get(v_tail_292_, 0);
v_isSharedCheck_340_ = !lean_is_exclusive(v_tail_292_);
if (v_isSharedCheck_340_ == 0)
{
lean_object* v_unused_341_; 
v_unused_341_ = lean_ctor_get(v_tail_292_, 1);
lean_dec(v_unused_341_);
v___x_304_ = v_tail_292_;
v_isShared_305_ = v_isSharedCheck_340_;
goto v_resetjp_303_;
}
else
{
lean_inc(v_head_302_);
lean_dec(v_tail_292_);
v___x_304_ = lean_box(0);
v_isShared_305_ = v_isSharedCheck_340_;
goto v_resetjp_303_;
}
v_resetjp_303_:
{
lean_object* v___x_306_; lean_object* v___x_307_; lean_object* v___x_308_; 
v___x_306_ = lean_string_utf8_byte_size(v_head_298_);
v___x_307_ = lean_alloc_ctor(0, 3, 0);
lean_ctor_set(v___x_307_, 0, v_head_298_);
lean_ctor_set(v___x_307_, 1, v___x_288_);
lean_ctor_set(v___x_307_, 2, v___x_306_);
v___x_308_ = l_String_Slice_toNat_x3f(v___x_307_);
lean_dec_ref_known(v___x_307_, 3);
if (lean_obj_tag(v___x_308_) == 1)
{
lean_object* v_val_309_; uint8_t v___y_311_; lean_object* v___x_334_; uint8_t v___x_335_; 
v_val_309_ = lean_ctor_get(v___x_308_, 0);
lean_inc(v_val_309_);
lean_dec_ref_known(v___x_308_, 1);
v___x_334_ = lean_string_utf8_byte_size(v_head_294_);
v___x_335_ = lean_nat_dec_eq(v___x_334_, v___x_288_);
if (v___x_335_ == 0)
{
lean_object* v___x_336_; uint8_t v___x_337_; 
v___x_336_ = lean_cstr_to_nat("4294967296");
v___x_337_ = lean_nat_dec_le(v___x_336_, v_val_309_);
v___y_311_ = v___x_337_;
goto v___jp_310_;
}
else
{
v___y_311_ = v___x_335_;
goto v___jp_310_;
}
v___jp_310_:
{
if (v___y_311_ == 0)
{
lean_object* v___x_312_; lean_object* v___x_313_; lean_object* v___x_314_; lean_object* v___x_315_; lean_object* v___x_317_; 
v___x_312_ = ((lean_object*)(lp_competition_List_forIn_x27_loop___at___00main_spec__0___redArg___closed__5));
v___x_313_ = ((lean_object*)(lp_competition_List_forIn_x27_loop___at___00main_spec__0___redArg___closed__6));
v___x_314_ = ((lean_object*)(lp_competition_List_forIn_x27_loop___at___00main_spec__0___redArg___closed__7));
v___x_315_ = ((lean_object*)(lp_competition_List_forIn_x27_loop___at___00main_spec__0___redArg___closed__8));
if (v_isShared_305_ == 0)
{
lean_ctor_set(v___x_304_, 0, v___x_315_);
v___x_317_ = v___x_304_;
goto v_reusejp_316_;
}
else
{
lean_object* v_reuseFailAlloc_333_; 
v_reuseFailAlloc_333_ = lean_alloc_ctor(1, 2, 0);
lean_ctor_set(v_reuseFailAlloc_333_, 0, v___x_315_);
lean_ctor_set(v_reuseFailAlloc_333_, 1, v_tail_293_);
v___x_317_ = v_reuseFailAlloc_333_;
goto v_reusejp_316_;
}
v_reusejp_316_:
{
lean_object* v___x_319_; 
if (v_isShared_301_ == 0)
{
lean_ctor_set(v___x_300_, 1, v___x_317_);
lean_ctor_set(v___x_300_, 0, v___x_314_);
v___x_319_ = v___x_300_;
goto v_reusejp_318_;
}
else
{
lean_object* v_reuseFailAlloc_332_; 
v_reuseFailAlloc_332_ = lean_alloc_ctor(1, 2, 0);
lean_ctor_set(v_reuseFailAlloc_332_, 0, v___x_314_);
lean_ctor_set(v_reuseFailAlloc_332_, 1, v___x_317_);
v___x_319_ = v_reuseFailAlloc_332_;
goto v_reusejp_318_;
}
v_reusejp_318_:
{
lean_object* v___x_321_; 
if (v_isShared_297_ == 0)
{
lean_ctor_set(v___x_296_, 1, v___x_319_);
lean_ctor_set(v___x_296_, 0, v___x_313_);
v___x_321_ = v___x_296_;
goto v_reusejp_320_;
}
else
{
lean_object* v_reuseFailAlloc_331_; 
v_reuseFailAlloc_331_ = lean_alloc_ctor(1, 2, 0);
lean_ctor_set(v_reuseFailAlloc_331_, 0, v___x_313_);
lean_ctor_set(v_reuseFailAlloc_331_, 1, v___x_319_);
v___x_321_ = v_reuseFailAlloc_331_;
goto v_reusejp_320_;
}
v_reusejp_320_:
{
lean_object* v___x_322_; uint8_t v___x_323_; 
v___x_322_ = lean_alloc_ctor(1, 2, 0);
lean_ctor_set(v___x_322_, 0, v___x_312_);
lean_ctor_set(v___x_322_, 1, v___x_321_);
v___x_323_ = lp_mathlib_List_elem___at___00Mathlib_Linter_TextBased_modulesOSForbidden_spec__4(v_head_302_, v___x_322_);
lean_dec_ref_known(v___x_322_, 2);
if (v___x_323_ == 0)
{
lean_dec(v_val_309_);
lean_dec(v_head_302_);
lean_dec(v_head_294_);
lean_dec(v_b_276_);
goto v___jp_278_;
}
else
{
uint32_t v___x_324_; lean_object* v___x_325_; lean_object* v___x_326_; lean_object* v___x_327_; lean_object* v___x_328_; lean_object* v___x_329_; 
v___x_324_ = lean_uint32_of_nat(v_val_309_);
lean_dec(v_val_309_);
v___x_325_ = lean_box_uint32(v___x_324_);
v___x_326_ = lean_alloc_ctor(0, 2, 0);
lean_ctor_set(v___x_326_, 0, v___x_325_);
lean_ctor_set(v___x_326_, 1, v_head_302_);
v___x_327_ = lean_alloc_ctor(0, 2, 0);
lean_ctor_set(v___x_327_, 0, v_head_294_);
lean_ctor_set(v___x_327_, 1, v___x_326_);
v___x_328_ = lean_alloc_ctor(1, 2, 0);
lean_ctor_set(v___x_328_, 0, v___x_327_);
lean_ctor_set(v___x_328_, 1, v___x_289_);
v___x_329_ = l_List_appendTR___redArg(v_b_276_, v___x_328_);
v_as_x27_275_ = v_tail_286_;
v_b_276_ = v___x_329_;
goto _start;
}
}
}
}
}
else
{
lean_dec(v_val_309_);
lean_del_object(v___x_304_);
lean_dec(v_head_302_);
lean_del_object(v___x_300_);
lean_del_object(v___x_296_);
lean_dec(v_head_294_);
lean_dec(v_b_276_);
goto v___jp_278_;
}
}
}
else
{
lean_object* v___x_338_; lean_object* v___x_339_; 
lean_dec(v___x_308_);
lean_del_object(v___x_304_);
lean_dec(v_head_302_);
lean_del_object(v___x_300_);
lean_del_object(v___x_296_);
lean_dec(v_head_294_);
lean_dec(v_b_276_);
v___x_338_ = ((lean_object*)(lp_competition_List_forIn_x27_loop___at___00main_spec__0___redArg___closed__10));
v___x_339_ = lean_alloc_ctor(1, 1, 0);
lean_ctor_set(v___x_339_, 0, v___x_338_);
return v___x_339_;
}
}
}
}
}
else
{
lean_dec_ref_known(v_tail_292_, 2);
lean_dec(v_tail_293_);
lean_dec_ref_known(v_tail_291_, 2);
lean_dec_ref_known(v___x_290_, 2);
lean_dec(v_b_276_);
goto v___jp_281_;
}
}
else
{
lean_dec_ref_known(v_tail_291_, 2);
lean_dec(v_tail_292_);
lean_dec_ref_known(v___x_290_, 2);
lean_dec(v_b_276_);
goto v___jp_281_;
}
}
else
{
lean_dec(v_tail_291_);
lean_dec_ref_known(v___x_290_, 2);
lean_dec(v_b_276_);
goto v___jp_281_;
}
}
else
{
lean_dec(v___x_290_);
lean_dec(v_b_276_);
goto v___jp_281_;
}
}
v___jp_278_:
{
lean_object* v___x_279_; lean_object* v___x_280_; 
v___x_279_ = ((lean_object*)(lp_competition_List_forIn_x27_loop___at___00main_spec__0___redArg___closed__1));
v___x_280_ = lean_alloc_ctor(1, 1, 0);
lean_ctor_set(v___x_280_, 0, v___x_279_);
return v___x_280_;
}
v___jp_281_:
{
lean_object* v___x_282_; lean_object* v___x_283_; 
v___x_282_ = ((lean_object*)(lp_competition_List_forIn_x27_loop___at___00main_spec__0___redArg___closed__3));
v___x_283_ = lean_alloc_ctor(1, 1, 0);
lean_ctor_set(v___x_283_, 0, v___x_282_);
return v___x_283_;
}
}
}
LEAN_EXPORT lean_object* lp_competition_List_forIn_x27_loop___at___00main_spec__0___redArg___boxed(lean_object* v_as_x27_346_, lean_object* v_b_347_, lean_object* v___y_348_){
_start:
{
lean_object* v_res_349_; 
v_res_349_ = lp_competition_List_forIn_x27_loop___at___00main_spec__0___redArg(v_as_x27_346_, v_b_347_);
lean_dec(v_as_x27_346_);
return v_res_349_;
}
}
LEAN_EXPORT lean_object* lp_competition_List_mapTR_loop___at___00main_spec__1(lean_object* v_a_350_, lean_object* v_a_351_){
_start:
{
if (lean_obj_tag(v_a_350_) == 0)
{
lean_object* v___x_352_; 
v___x_352_ = l_List_reverse___redArg(v_a_351_);
return v___x_352_;
}
else
{
lean_object* v_head_353_; lean_object* v_tail_354_; lean_object* v___x_356_; uint8_t v_isShared_357_; uint8_t v_isSharedCheck_363_; 
v_head_353_ = lean_ctor_get(v_a_350_, 0);
v_tail_354_ = lean_ctor_get(v_a_350_, 1);
v_isSharedCheck_363_ = !lean_is_exclusive(v_a_350_);
if (v_isSharedCheck_363_ == 0)
{
v___x_356_ = v_a_350_;
v_isShared_357_ = v_isSharedCheck_363_;
goto v_resetjp_355_;
}
else
{
lean_inc(v_tail_354_);
lean_inc(v_head_353_);
lean_dec(v_a_350_);
v___x_356_ = lean_box(0);
v_isShared_357_ = v_isSharedCheck_363_;
goto v_resetjp_355_;
}
v_resetjp_355_:
{
lean_object* v_fst_358_; lean_object* v___x_360_; 
v_fst_358_ = lean_ctor_get(v_head_353_, 0);
lean_inc(v_fst_358_);
lean_dec(v_head_353_);
if (v_isShared_357_ == 0)
{
lean_ctor_set(v___x_356_, 1, v_a_351_);
lean_ctor_set(v___x_356_, 0, v_fst_358_);
v___x_360_ = v___x_356_;
goto v_reusejp_359_;
}
else
{
lean_object* v_reuseFailAlloc_362_; 
v_reuseFailAlloc_362_ = lean_alloc_ctor(1, 2, 0);
lean_ctor_set(v_reuseFailAlloc_362_, 0, v_fst_358_);
lean_ctor_set(v_reuseFailAlloc_362_, 1, v_a_351_);
v___x_360_ = v_reuseFailAlloc_362_;
goto v_reusejp_359_;
}
v_reusejp_359_:
{
v_a_350_ = v_tail_354_;
v_a_351_ = v___x_360_;
goto _start;
}
}
}
}
}
LEAN_EXPORT lean_object* _lean_main(){
_start:
{
lean_object* v___y_384_; lean_object* v___y_385_; lean_object* v___y_386_; lean_object* v___y_387_; lean_object* v___y_411_; lean_object* v___y_412_; lean_object* v___y_413_; uint8_t v___y_423_; lean_object* v___y_424_; lean_object* v___y_425_; lean_object* v___y_426_; lean_object* v___x_449_; lean_object* v___x_450_; lean_object* v___y_452_; 
v___x_449_ = ((lean_object*)(lp_competition_main___closed__7));
v___x_450_ = lean_io_getenv(v___x_449_);
if (lean_obj_tag(v___x_450_) == 0)
{
goto v___jp_461_;
}
else
{
lean_object* v_val_463_; lean_object* v___x_464_; lean_object* v___x_465_; lean_object* v___x_466_; lean_object* v___x_467_; 
v_val_463_ = lean_ctor_get(v___x_450_, 0);
lean_inc(v_val_463_);
lean_dec_ref_known(v___x_450_, 1);
v___x_464_ = lean_unsigned_to_nat(0u);
v___x_465_ = lean_string_utf8_byte_size(v_val_463_);
v___x_466_ = lean_alloc_ctor(0, 3, 0);
lean_ctor_set(v___x_466_, 0, v_val_463_);
lean_ctor_set(v___x_466_, 1, v___x_464_);
lean_ctor_set(v___x_466_, 2, v___x_465_);
v___x_467_ = l_String_Slice_toNat_x3f(v___x_466_);
lean_dec_ref_known(v___x_466_, 3);
if (lean_obj_tag(v___x_467_) == 0)
{
goto v___jp_461_;
}
else
{
lean_object* v_val_468_; 
v_val_468_ = lean_ctor_get(v___x_467_, 0);
lean_inc(v_val_468_);
lean_dec_ref_known(v___x_467_, 1);
v___y_452_ = v_val_468_;
goto v___jp_451_;
}
}
v___jp_380_:
{
lean_object* v___x_381_; lean_object* v___x_382_; 
v___x_381_ = ((lean_object*)(lp_competition_main___closed__1));
v___x_382_ = lean_alloc_ctor(1, 1, 0);
lean_ctor_set(v___x_382_, 0, v___x_381_);
return v___x_382_;
}
v___jp_383_:
{
uint8_t v___x_388_; 
v___x_388_ = l_List_isEmpty___redArg(v___y_387_);
if (v___x_388_ == 0)
{
lean_object* v___x_389_; lean_object* v___x_390_; 
v___x_389_ = lean_box(0);
v___x_390_ = lp_competition_List_forIn_x27_loop___at___00main_spec__6___redArg(v___y_384_, v___y_385_, v___y_387_, v___y_386_, v___x_389_);
lean_dec(v___y_386_);
lean_dec(v___y_387_);
lean_dec(v___y_385_);
if (lean_obj_tag(v___x_390_) == 0)
{
lean_object* v___x_392_; uint8_t v_isShared_393_; uint8_t v_isSharedCheck_398_; 
v_isSharedCheck_398_ = !lean_is_exclusive(v___x_390_);
if (v_isSharedCheck_398_ == 0)
{
lean_object* v_unused_399_; 
v_unused_399_ = lean_ctor_get(v___x_390_, 0);
lean_dec(v_unused_399_);
v___x_392_ = v___x_390_;
v_isShared_393_ = v_isSharedCheck_398_;
goto v_resetjp_391_;
}
else
{
lean_dec(v___x_390_);
v___x_392_ = lean_box(0);
v_isShared_393_ = v_isSharedCheck_398_;
goto v_resetjp_391_;
}
v_resetjp_391_:
{
lean_object* v___x_394_; lean_object* v___x_396_; 
v___x_394_ = lp_competition_List_forIn_x27_loop___at___00main_spec__5___redArg___closed__1___boxed__const__1;
if (v_isShared_393_ == 0)
{
lean_ctor_set(v___x_392_, 0, v___x_394_);
v___x_396_ = v___x_392_;
goto v_reusejp_395_;
}
else
{
lean_object* v_reuseFailAlloc_397_; 
v_reuseFailAlloc_397_ = lean_alloc_ctor(0, 1, 0);
lean_ctor_set(v_reuseFailAlloc_397_, 0, v___x_394_);
v___x_396_ = v_reuseFailAlloc_397_;
goto v_reusejp_395_;
}
v_reusejp_395_:
{
return v___x_396_;
}
}
}
else
{
lean_object* v_a_400_; lean_object* v___x_402_; uint8_t v_isShared_403_; uint8_t v_isSharedCheck_407_; 
v_a_400_ = lean_ctor_get(v___x_390_, 0);
v_isSharedCheck_407_ = !lean_is_exclusive(v___x_390_);
if (v_isSharedCheck_407_ == 0)
{
v___x_402_ = v___x_390_;
v_isShared_403_ = v_isSharedCheck_407_;
goto v_resetjp_401_;
}
else
{
lean_inc(v_a_400_);
lean_dec(v___x_390_);
v___x_402_ = lean_box(0);
v_isShared_403_ = v_isSharedCheck_407_;
goto v_resetjp_401_;
}
v_resetjp_401_:
{
lean_object* v___x_405_; 
if (v_isShared_403_ == 0)
{
v___x_405_ = v___x_402_;
goto v_reusejp_404_;
}
else
{
lean_object* v_reuseFailAlloc_406_; 
v_reuseFailAlloc_406_ = lean_alloc_ctor(1, 1, 0);
lean_ctor_set(v_reuseFailAlloc_406_, 0, v_a_400_);
v___x_405_ = v_reuseFailAlloc_406_;
goto v_reusejp_404_;
}
v_reusejp_404_:
{
return v___x_405_;
}
}
}
}
else
{
lean_object* v___x_408_; lean_object* v___x_409_; 
lean_dec(v___y_387_);
lean_dec(v___y_386_);
lean_dec(v___y_385_);
lean_dec(v___y_384_);
v___x_408_ = ((lean_object*)(lp_competition_main___closed__3));
v___x_409_ = lean_alloc_ctor(1, 1, 0);
lean_ctor_set(v___x_409_, 0, v___x_408_);
return v___x_409_;
}
}
v___jp_410_:
{
lean_object* v___x_414_; lean_object* v___x_415_; lean_object* v___x_416_; 
v___x_414_ = ((lean_object*)(lp_competition_main___closed__4));
v___x_415_ = lean_io_getenv(v___x_414_);
v___x_416_ = lp_competition_parseReps(v___y_413_);
lean_dec_ref(v___y_413_);
if (lean_obj_tag(v___x_415_) == 0)
{
lean_object* v___x_417_; 
v___x_417_ = lp_competition_ExactSuite_cells;
v___y_384_ = v___y_411_;
v___y_385_ = v___x_416_;
v___y_386_ = v___y_412_;
v___y_387_ = v___x_417_;
goto v___jp_383_;
}
else
{
lean_object* v_val_418_; lean_object* v___x_419_; lean_object* v___x_420_; lean_object* v___x_421_; 
v_val_418_ = lean_ctor_get(v___x_415_, 0);
lean_inc(v_val_418_);
lean_dec_ref_known(v___x_415_, 1);
v___x_419_ = lp_competition_ExactSuite_cells;
v___x_420_ = lean_box(0);
v___x_421_ = lp_competition_List_filterTR_loop___at___00main_spec__7(v_val_418_, v___x_419_, v___x_420_);
lean_dec(v_val_418_);
v___y_384_ = v___y_411_;
v___y_385_ = v___x_416_;
v___y_386_ = v___y_412_;
v___y_387_ = v___x_421_;
goto v___jp_383_;
}
}
v___jp_422_:
{
lean_object* v___x_427_; lean_object* v___x_428_; lean_object* v___x_429_; lean_object* v___x_430_; 
v___x_427_ = lean_box(0);
v___x_428_ = ((lean_object*)(lp_competition_parseReps___closed__0));
lean_inc_n(v___y_424_, 2);
v___x_429_ = l_String_splitOnAux(v___y_426_, v___x_428_, v___y_424_, v___y_424_, v___y_424_, v___x_427_);
lean_dec_ref(v___y_426_);
v___x_430_ = lp_competition_List_forIn_x27_loop___at___00main_spec__0___redArg(v___x_429_, v___x_427_);
lean_dec(v___x_429_);
if (lean_obj_tag(v___x_430_) == 0)
{
lean_object* v_a_431_; lean_object* v___x_432_; lean_object* v___x_433_; lean_object* v___x_434_; lean_object* v___x_435_; uint8_t v___x_436_; 
v_a_431_ = lean_ctor_get(v___x_430_, 0);
lean_inc_n(v_a_431_, 2);
lean_dec_ref_known(v___x_430_, 1);
v___x_432_ = lp_competition_List_mapTR_loop___at___00main_spec__1(v_a_431_, v___x_427_);
v___x_433_ = l_List_lengthTR___redArg(v___x_432_);
v___x_434_ = lp_batteries_List_eraseDups___at___00__private_Batteries_Tactic_HelpCmd_0__Batteries_Tactic_elabHelpCat_spec__3(v___x_432_);
v___x_435_ = l_List_lengthTR___redArg(v___x_434_);
lean_dec(v___x_434_);
v___x_436_ = lean_nat_dec_eq(v___x_433_, v___x_435_);
lean_dec(v___x_435_);
lean_dec(v___x_433_);
if (v___x_436_ == 0)
{
lean_dec(v_a_431_);
lean_dec(v___y_425_);
goto v___jp_380_;
}
else
{
if (v___y_423_ == 0)
{
lean_object* v___x_437_; lean_object* v___x_438_; 
v___x_437_ = ((lean_object*)(lp_competition_main___closed__5));
v___x_438_ = lean_io_getenv(v___x_437_);
if (lean_obj_tag(v___x_438_) == 0)
{
lean_object* v___x_439_; 
v___x_439_ = ((lean_object*)(lp_competition_main___closed__6));
v___y_411_ = v___y_425_;
v___y_412_ = v_a_431_;
v___y_413_ = v___x_439_;
goto v___jp_410_;
}
else
{
lean_object* v_val_440_; 
v_val_440_ = lean_ctor_get(v___x_438_, 0);
lean_inc(v_val_440_);
lean_dec_ref_known(v___x_438_, 1);
v___y_411_ = v___y_425_;
v___y_412_ = v_a_431_;
v___y_413_ = v_val_440_;
goto v___jp_410_;
}
}
else
{
lean_dec(v_a_431_);
lean_dec(v___y_425_);
goto v___jp_380_;
}
}
}
else
{
lean_object* v_a_441_; lean_object* v___x_443_; uint8_t v_isShared_444_; uint8_t v_isSharedCheck_448_; 
lean_dec(v___y_425_);
v_a_441_ = lean_ctor_get(v___x_430_, 0);
v_isSharedCheck_448_ = !lean_is_exclusive(v___x_430_);
if (v_isSharedCheck_448_ == 0)
{
v___x_443_ = v___x_430_;
v_isShared_444_ = v_isSharedCheck_448_;
goto v_resetjp_442_;
}
else
{
lean_inc(v_a_441_);
lean_dec(v___x_430_);
v___x_443_ = lean_box(0);
v_isShared_444_ = v_isSharedCheck_448_;
goto v_resetjp_442_;
}
v_resetjp_442_:
{
lean_object* v___x_446_; 
if (v_isShared_444_ == 0)
{
v___x_446_ = v___x_443_;
goto v_reusejp_445_;
}
else
{
lean_object* v_reuseFailAlloc_447_; 
v_reuseFailAlloc_447_ = lean_alloc_ctor(1, 1, 0);
lean_ctor_set(v_reuseFailAlloc_447_, 0, v_a_441_);
v___x_446_ = v_reuseFailAlloc_447_;
goto v_reusejp_445_;
}
v_reusejp_445_:
{
return v___x_446_;
}
}
}
}
v___jp_451_:
{
lean_object* v___x_453_; uint8_t v___x_454_; 
v___x_453_ = lean_unsigned_to_nat(0u);
v___x_454_ = lean_nat_dec_eq(v___y_452_, v___x_453_);
if (v___x_454_ == 0)
{
lean_object* v___x_455_; lean_object* v___x_456_; 
v___x_455_ = ((lean_object*)(lp_competition_main___closed__8));
v___x_456_ = lean_io_getenv(v___x_455_);
if (lean_obj_tag(v___x_456_) == 0)
{
lean_object* v___x_457_; 
v___x_457_ = ((lean_object*)(lp_competition_main___closed__9));
v___y_423_ = v___x_454_;
v___y_424_ = v___x_453_;
v___y_425_ = v___y_452_;
v___y_426_ = v___x_457_;
goto v___jp_422_;
}
else
{
lean_object* v_val_458_; 
v_val_458_ = lean_ctor_get(v___x_456_, 0);
lean_inc(v_val_458_);
lean_dec_ref_known(v___x_456_, 1);
v___y_423_ = v___x_454_;
v___y_424_ = v___x_453_;
v___y_425_ = v___y_452_;
v___y_426_ = v_val_458_;
goto v___jp_422_;
}
}
else
{
lean_object* v___x_459_; lean_object* v___x_460_; 
lean_dec(v___y_452_);
v___x_459_ = ((lean_object*)(lp_competition_main___closed__11));
v___x_460_ = lean_alloc_ctor(1, 1, 0);
lean_ctor_set(v___x_460_, 0, v___x_459_);
return v___x_460_;
}
}
v___jp_461_:
{
lean_object* v___x_462_; 
v___x_462_ = lean_unsigned_to_nat(3u);
v___y_452_ = v___x_462_;
goto v___jp_451_;
}
}
}
LEAN_EXPORT lean_object* lp_competition_main___boxed(lean_object* v_a_469_){
_start:
{
lean_object* v_res_470_; 
v_res_470_ = _lean_main();
return v_res_470_;
}
}
LEAN_EXPORT lean_object* lp_competition_List_forIn_x27_loop___at___00main_spec__0(lean_object* v_as_471_, lean_object* v_as_x27_472_, lean_object* v_b_473_, lean_object* v_a_474_){
_start:
{
lean_object* v___x_476_; 
v___x_476_ = lp_competition_List_forIn_x27_loop___at___00main_spec__0___redArg(v_as_x27_472_, v_b_473_);
return v___x_476_;
}
}
LEAN_EXPORT lean_object* lp_competition_List_forIn_x27_loop___at___00main_spec__0___boxed(lean_object* v_as_477_, lean_object* v_as_x27_478_, lean_object* v_b_479_, lean_object* v_a_480_, lean_object* v___y_481_){
_start:
{
lean_object* v_res_482_; 
v_res_482_ = lp_competition_List_forIn_x27_loop___at___00main_spec__0(v_as_477_, v_as_x27_478_, v_b_479_, v_a_480_);
lean_dec(v_as_x27_478_);
lean_dec(v_as_477_);
return v_res_482_;
}
}
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00main_spec__2(lean_object* v___x_483_, lean_object* v_range_484_, lean_object* v_b_485_, lean_object* v_i_486_, lean_object* v_hs_487_, lean_object* v_hl_488_){
_start:
{
lean_object* v___x_490_; 
v___x_490_ = lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00main_spec__2___redArg(v___x_483_, v_range_484_, v_b_485_, v_i_486_);
return v___x_490_;
}
}
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00main_spec__2___boxed(lean_object* v___x_491_, lean_object* v_range_492_, lean_object* v_b_493_, lean_object* v_i_494_, lean_object* v_hs_495_, lean_object* v_hl_496_, lean_object* v___y_497_){
_start:
{
lean_object* v_res_498_; 
v_res_498_ = lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00main_spec__2(v___x_491_, v_range_492_, v_b_493_, v_i_494_, v_hs_495_, v_hl_496_);
lean_dec_ref(v_range_492_);
return v_res_498_;
}
}
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00main_spec__3(lean_object* v___y_499_, lean_object* v___x_500_, lean_object* v_range_501_, lean_object* v_b_502_, lean_object* v_i_503_, lean_object* v_hs_504_, lean_object* v_hl_505_){
_start:
{
lean_object* v___x_507_; 
v___x_507_ = lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00main_spec__3___redArg(v___y_499_, v___x_500_, v_range_501_, v_b_502_, v_i_503_);
return v___x_507_;
}
}
LEAN_EXPORT lean_object* lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00main_spec__3___boxed(lean_object* v___y_508_, lean_object* v___x_509_, lean_object* v_range_510_, lean_object* v_b_511_, lean_object* v_i_512_, lean_object* v_hs_513_, lean_object* v_hl_514_, lean_object* v___y_515_){
_start:
{
lean_object* v_res_516_; 
v_res_516_ = lp_competition___private_Init_Data_Range_Basic_0__Std_Legacy_Range_forIn_x27_loop___at___00main_spec__3(v___y_508_, v___x_509_, v_range_510_, v_b_511_, v_i_512_, v_hs_513_, v_hl_514_);
lean_dec_ref(v_range_510_);
return v_res_516_;
}
}
LEAN_EXPORT lean_object* lp_competition_List_forIn_x27_loop___at___00main_spec__5(uint32_t v_fst_517_, lean_object* v_snd_518_, lean_object* v_fst_519_, lean_object* v___y_520_, lean_object* v___x_521_, lean_object* v_as_522_, lean_object* v_as_x27_523_, lean_object* v_b_524_, lean_object* v_a_525_){
_start:
{
lean_object* v___x_527_; 
v___x_527_ = lp_competition_List_forIn_x27_loop___at___00main_spec__5___redArg(v_fst_517_, v_snd_518_, v_fst_519_, v___y_520_, v___x_521_, v_as_x27_523_, v_b_524_);
return v___x_527_;
}
}
LEAN_EXPORT lean_object* lp_competition_List_forIn_x27_loop___at___00main_spec__5___boxed(lean_object* v_fst_528_, lean_object* v_snd_529_, lean_object* v_fst_530_, lean_object* v___y_531_, lean_object* v___x_532_, lean_object* v_as_533_, lean_object* v_as_x27_534_, lean_object* v_b_535_, lean_object* v_a_536_, lean_object* v___y_537_){
_start:
{
uint32_t v_fst_9211__boxed_538_; lean_object* v_res_539_; 
v_fst_9211__boxed_538_ = lean_unbox_uint32(v_fst_528_);
lean_dec(v_fst_528_);
v_res_539_ = lp_competition_List_forIn_x27_loop___at___00main_spec__5(v_fst_9211__boxed_538_, v_snd_529_, v_fst_530_, v___y_531_, v___x_532_, v_as_533_, v_as_x27_534_, v_b_535_, v_a_536_);
lean_dec(v_as_x27_534_);
lean_dec(v_as_533_);
lean_dec(v___x_532_);
lean_dec_ref(v_snd_529_);
return v_res_539_;
}
}
LEAN_EXPORT lean_object* lp_competition_List_forIn_x27_loop___at___00main_spec__6(lean_object* v___y_540_, lean_object* v___x_541_, lean_object* v___y_542_, lean_object* v_as_543_, lean_object* v_as_x27_544_, lean_object* v_b_545_, lean_object* v_a_546_){
_start:
{
lean_object* v___x_548_; 
v___x_548_ = lp_competition_List_forIn_x27_loop___at___00main_spec__6___redArg(v___y_540_, v___x_541_, v___y_542_, v_as_x27_544_, v_b_545_);
return v___x_548_;
}
}
LEAN_EXPORT lean_object* lp_competition_List_forIn_x27_loop___at___00main_spec__6___boxed(lean_object* v___y_549_, lean_object* v___x_550_, lean_object* v___y_551_, lean_object* v_as_552_, lean_object* v_as_x27_553_, lean_object* v_b_554_, lean_object* v_a_555_, lean_object* v___y_556_){
_start:
{
lean_object* v_res_557_; 
v_res_557_ = lp_competition_List_forIn_x27_loop___at___00main_spec__6(v___y_549_, v___x_550_, v___y_551_, v_as_552_, v_as_x27_553_, v_b_554_, v_a_555_);
lean_dec(v_as_x27_553_);
lean_dec(v_as_552_);
lean_dec(v___y_551_);
lean_dec(v___x_550_);
return v_res_557_;
}
}
lean_object* initialize_Init(uint8_t builtin);
lean_object* initialize_Init(uint8_t builtin);
lean_object* initialize_competition_ExactSuite(uint8_t builtin);
lean_object* initialize_competition_Submission(uint8_t builtin);
void lean_initialize();
static bool _G_initialized = false;
LEAN_EXPORT lean_object* initialize_competition_R26NativeMain(uint8_t builtin) {
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
res = initialize_competition_ExactSuite(builtin);
if (lean_io_result_is_error(res)) return res;
lean_dec_ref(res);
res = initialize_competition_Submission(builtin);
if (lean_io_result_is_error(res)) return res;
lean_dec_ref(res);
lp_competition_List_forIn_x27_loop___at___00main_spec__5___redArg___closed__1___boxed__const__1 = _init_lp_competition_List_forIn_x27_loop___at___00main_spec__5___redArg___closed__1___boxed__const__1();
lean_mark_persistent(lp_competition_List_forIn_x27_loop___at___00main_spec__5___redArg___closed__1___boxed__const__1);
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
  res = initialize_competition_R26NativeMain(1 /* builtin */);
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
